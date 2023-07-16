## ubuntu创建root用户

+ ubuntu虚拟机初始可能su root切换到root失败，这是因为root还没有设置密码，按如下操作即可

```shell
sudo passwd root  # 设置root密码

su root
```

## 创建普通用户

```
使用 adduser 命令，按提出即可

如果您希望新创建的用户具有管理权限，请将用户添加到sudo组，否则无法使用sudo执行相关操作：
sudo usermod -aG sudo username

```



## ubuntu apt

+ apt是一个命令行包管理器



## ubuntu 修改软件源

1. 图形界面修改
2. 配置文件与命令行修改

```
软件源的配置文件在 /etc/apt/sources.list

cd /etc/apt
1. 先备份原始文件
sudo cp sources.list sources.list.backup

2.使用vim或vi打开文件，修改文件
sudo vim sources.list

# 阿里云软件源，将sources.list文件清空，然后填入以下内容
deb http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse

# 更新软件源
sudo apt update
sudo apt upgrade

```



## 开机安装

```
# 更换软件源

sudo apt update

sudo apt upgrade

sudo apt install net-tools openssh-server gcc g++ build-essential cmake make git vim

# 米尔电子推荐安装
sudo apt install gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat libsdl1.2-dev libsdl1.2-dev xterm sed cvs subversion coreutils texi2html docbook-utils python-pysqlite2 help2man make gcc g++ desktop-file-utils libgl1-mesa-dev libglu1-mesa-dev mercurial autoconf automake groff curl lzop asciidoc u-boot-tools python3-pip u-boot-tools
```



## VMware ubuntu虚拟机设置ip地址





## win主机、ubuntu虚拟机、开发板 网络设置以及互ping

+ 使用VMware
+ 虚拟机使用桥接网络模式
+ win, 虚拟机, 开发板的要在同一个子网下，即ip地址除了最后一段外，前3段都要相同，比如192.168.1.xxx。所有的子网掩码都设置为255.255.255.0



## 解决方法：Ubuntu 22.04网络无法连接，没有网络图标

 https://blog.csdn.net/qq_36347513/article/details/126573588









