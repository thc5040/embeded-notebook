## fastdds 入门

#### 1.source+cmake+local方式在linux下安装

+ 结合官方文档看

+ 安装依赖工具

```bash
sudo apt install cmake g++ python3-pip wget git 
sudo apt install libasio-dev libtinyxml2-dev
sudo apt install libp11-dev libengine-pkcs11-openssl
```

+ cmake + local installation
+ 官方文档是以 ~/Fast-DDS 为安装目录，为了灵活，路径自己改变，我自己的安装路径是 ~/ros2/fastDDS。下载过程有可能会出现网络问题访问下载不了，换个翻墙节点多试试

```bash
# 在这个目录下操作
cd ~/ros2/fastDDS	

# Foonathan memory 安装 cmake编译   DCMAKE_INSTALL_PREFIX 预先准备好install路径
cd ~/ros2/fastDDS	
git clone https://github.com/eProsima/foonathan_memory_vendor.git
mkdir foonathan_memory_vendor/build
cd foonathan_memory_vendor/build
cmake .. -DCMAKE_INSTALL_PREFIX=~/ros2/fastDDS/install -DBUILD_SHARED_LIBS=ON
cmake --build . --target install

# Fast CDR 安装 cmake编译
cd ~/ros2/fastDDS	
git clone https://github.com/eProsima/Fast-CDR.git
mkdir Fast-CDR/build
cd Fast-CDR/build
cmake .. -DCMAKE_INSTALL_PREFIX=~/ros2/fastDDS/install
cmake --build . --target install

# Fast DDS 最重要的来了
cd ~/ros2/fastDDS	
git clone https://github.com/eProsima/Fast-DDS.git
mkdir Fast-DDS/build
cd Fast-DDS/build
cmake ..  -DCMAKE_INSTALL_PREFIX=~/ros2/fastDDS/install
cmake --build . --target install

# DDS-Gen 代码生成工具，非常重要 这个工具是由java写的，所以需要安装jdk
sudo apt install openjdk-11-jdk
cd ~/ros2/fastDDS	
git clone --recursive https://github.com/eProsima/Fast-DDS-Gen.git
cd Fast-DDS-Gen
./gradlew assemble
```

+ 以下是安装的结果

![](.\markdown src\fastdds_install_result1.png)

+ 在运行 fast DDS 的程序时，必须要链接到安装库lib

```bash
echo 'export LD_LIBRARY_PATH=/home/thc/ros2/fastDDS/install/lib/' >> ~/.bashrc
```

#### 2 source+cmake+global方式在linux下安装

+ 方便起见，global安装方式将程序安装在 /usr/local 目录下，免去了找不到头文件，链接库等的问题
+ 需要sudo权限

```bash
# 在这个目录下操作
cd ~/ros2/fastDDS	

# Foonathan memory 安装 cmake编译   DCMAKE_INSTALL_PREFIX 预先准备好install路径
cd ~/ros2/fastDDS	
git clone https://github.com/eProsima/foonathan_memory_vendor.git
mkdir foonathan_memory_vendor/build
cd foonathan_memory_vendor/build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local/ -DBUILD_SHARED_LIBS=ON
sudo cmake --build . --target install

# Fast CDR 安装 cmake编译
cd ~/ros2/fastDDS	
git clone https://github.com/eProsima/Fast-CDR.git
mkdir Fast-CDR/build
cd Fast-CDR/build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local/
sudo cmake --build . --target install

# Fast DDS 最重要的来了
cd ~/ros2/fastDDS	
git clone https://github.com/eProsima/Fast-DDS.git
mkdir Fast-DDS/build
cd Fast-DDS/build
cmake ..  -DCMAKE_INSTALL_PREFIX=/usr/local/
sudo cmake --build . --target install

# DDS-Gen 代码生成工具，非常重要 这个工具是由java写的，所以需要安装jdk
sudo apt install openjdk-11-jdk
cd ~/ros2/fastDDS	
git clone --recursive https://github.com/eProsima/Fast-DDS-Gen.git
cd Fast-DDS-Gen
./gradlew assemble
```



#### 3. DDS-Gen + Build a publish/subscibe application

+ 通过 DDS-Gen工具，我们可以简单编写一个 IDL文件 即可实现一个 publish/subscription 应用
+ 在自己的方便的工作目录下进行，我自己是 ~/ros2/dds_exmaple

```bash
cd ~/ros2/dds_exmaple

mkdir FastDDSGenHelloWorld && cd FastDDSGenHelloWorld
mkdir build

# 新建一个 HelloWorld.idl 文件，内容如下
struct HelloWorld
{
    string message;
};
```

+ 然后使用 DDS-Gen 代码生成工具，可以生成一个 c++的 custom topic，同时还会有一个使用这个topic的示例程序

```bash
/home/thc/ros2/fastDDS/Fast-DDS-Gen/scripts/fastddsgen -example CMake HelloWorld.idl

# 然后编译
cd build
cmake ..
make
```

+ 最后编译结果如下

![](.\markdown src\fast dds gen result1.png)

+ 在两个终端下运行，可以看到一个简单的 publisher/subscriber例子

![](.\markdown src\fast dds gen result2.png)

## 一些坑

#### 下载错误

一般是网络原因，换节点，多试试

#### fast-dds exmaple 编译错误

例如错误信息，一直说没找到哦啊 fastdds::optionparser：

```
CMake Error at cpp/dds/AdvancedConfigurationExample/CMakeLists.txt:42 (add_executable):
  Target "AdvancedConfigurationExample" links to target
  "fastdds::optionparser" but the target was not found.  Perhaps a
  find_package() call is missing for an IMPORTED target, or an ALIAS target
  is missing?
```

猜测可能与 ROS2的 fastDDS 冲突？ 卸载了 ROS2 还是有问题

经过分析，头文件包含的问题，比如在HelloWorld_main.cpp中，可以看到关于optionparser的头文件包含是

```
#include <optionparser.hpp>
```

但是实际上我们将fastDDS安装在了 /usr/local文件夹下，所以g++默认头文件包含是 /usr/local/include，但是ls查看该文件夹可以发现:

```
ls /usr/local/include

fastcdr  fastdds  fastrtps  foonathan_memory
```

可以看到该路径下并没有optionparser.hpp文件，实际上该文件的路径是/usr/local/include/fastdds/thirdparty/optionparser/optionparser.hpp，所以是头文件包含的问题，所以解决方法有：

1. 修改.cpp代码，这部分的头文件包含修改

```
// #include <optionparser.hpp>
#include <fastdds/thirdparty/optionparser/optionparser.hpp>
```

2. 在.bashrc文件中，添加 CPLUS_INCLUDE_PATH，并重新打开终端，或者手动source ~/.bashrc

```

```

使用以下命令可以看到g++的默认路径包含头文件，此时应该可以看到 /usr/local----/optionparser路径

```
echo | g++ -v -x c++ -E -
```



## fast DDS  helloWorld例程分析

+ 分析 Fast-DDS/examples/cpp/dds/HelloWorldExample
+ 例程运行结果如下，创建2个终端，使用命令运行 

```
 ./DDSHelloWorldExample publisher
 ./DDSHelloWorldExample subscriber
```

![](.\markdown src\dds exmaple helloworld1.png)

![](.\markdown src\dds exmaple helloworld2.png)

+ 例程的文件结构如下

![](.\markdown src\dds exmaple helloworld3.png)

HelloWorld.idl 是传输数据的定义，这个例子定义了一个字符串，和一个整形

```c
struct HelloWorld
{
	unsigned long index;
	string message;
};
```

该文件可以通过fast-ddsGen工具生成相应的传输消息类，方便直接使用，如：

```
HelloWorld.h, HelloWorld.cxx
是 HelloWorld.idl生成的 HelloWorld类
This header file contains the declaration of the described types in the IDL file.
This source file contains the definition of the described types in the IDL file.

HelloWorldPubSubTypes.h, HelloWorldPubSubTypes.cxx
也是工具生成的代码
This header file contains the implementation of the serialization functions.

HelloWorld_main.cpp, HelloWorldPublisher.cpp/.h， HelloWorldSubscriber.cpp/.h 
是一个简单的使用HelloWorld类进行消息传输的例程，也就是上面的运行例程

HelloWorldPublisher类主要有2个函数,init和run,init就是做一些初始化工作，然后run里面开辟一个子线程，每个一小段时间就publish一个消息。 里面会实现一个PubListener子类，继承自DataWriterListener,里面会实现一个on_publication_matched方法，比较重要

HelloWorldSubscriber类也有2个函数,init和run,init就是做一些初始化工作,run却是空的。因为里面会实现一个子类SubListener,继承自DataReaderListener,里面会实现on_data_avaiable方法和on_subscription_matched方法，每次得到消息都会自动调用 on_subscription方法，从里面解析message
```



## 参考资料

官方文档：https://fast-dds.docs.eprosima.com/en/latest/index.html

还有官方github



