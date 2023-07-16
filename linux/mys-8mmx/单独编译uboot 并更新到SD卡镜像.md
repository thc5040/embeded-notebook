+ sd卡已经烧录米尔电子提供的yocto制作的镜像
+ 下载米尔电子提供的uboot，交叉编译uboot
+ 但是编译错误，正常来说就是这么编译的

```
# 安装前置工具
sudo apt install gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat libsdl1.2-dev libsdl1.2-dev xterm sed cvs subversion coreutils texi2html docbook-utils python-pysqlite2 help2man make gcc g++ desktop-file-utils libgl1-mesa-dev libglu1-mesa-dev mercurial autoconf automake groff curl lzop asciidoc u-boot-tools python3-pip u-boot-tools

# 安装交叉编译器
sudo apt install gcc-aarch64-linux-gnu 

# 下载uboot
git clone https://github.com/MYiR-Dev/myir-imx-uboot.git -b develop

cd myir-imx-uboot

# uboot defconfig文件
make ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- mys_iot_imx8mm_v20_ddr4_evk_defconfig

# 清空之前的编译信息
make distclean

# uboot defconfig 配置
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- mys_iot_imx8mm_v20_ddr4_evk_defconfig

# 编译
make ARCH=arm CROSS_COMPILE=aarch64-linux-gnu- -j4
```

