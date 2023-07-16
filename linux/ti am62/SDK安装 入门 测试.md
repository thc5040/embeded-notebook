## 前言

+ 使用 TI SK-AM62 EVK平台
+ 1.1.1 Download and install the SDK 下载和安装好SDK
+ 1.1.2 Build and Run the Demos
+ 1.1.3 Create SD Card, 将镜像烧录到SD卡中
+ 1.1.4 Run Setup Scripts, 利用一个setup.sh脚本配置好所有主机开发环境



## SDK安装与测试

+ 下载好SDK，ti-processor-sdk-linux-rt-am62xx-evm-08.06.00.42-Linux-x86-Install.bin
+ chmod +x 给该.bin文件可执行权限，./xx.bin 执行即可安装SDK。安装结果如下

![](.\markdown src\sdk install 1.png)

+ 运行 setup.sh 脚本，用于设置开发环境，方便开发过程，如设置好NFS minicom等 





## 1.1.5 SDK Build using Makefile

+ top-level makefile用于控制全部或部分组件的编译。Rules.make提供了一些相关变量
+ 提前安装好一些包

```
sudo apt install build-essential autoconf automake bison flex libssl-dev bc u-boot-tools swig
```





## 错误记录

#### setup.sh中nfs setup错误

错误信息如下：

```
[ ok ] Stopping nfs-kernel-server (via systemctl): nfs-kernel-server.service.
[....] Starting nfs-kernel-server (via systemctl): nfs-kernel-server.serviceJob for nfs-server.service canceled.
 failed!
Failed setup, aborting..
Failed setup, aborting..
```

在ti论坛找到解决方法，将一些：https://e2e.ti.com/support/processors-group/processors/f/processors-forum/1137439/tda4vm-sdk-nfs-kernel-server-failed?tisearch=e2e-sitesearch&keymatch=am62%25252C%252520nfs-server.service%252520canceled



