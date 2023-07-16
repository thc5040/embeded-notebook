## 前言







## 野火 i.mx6ull u-boot 编译 烧录

+ 先下载好各种工具和依赖

```
sudo apt install make git gcc-arm-none-eabi gcc bison flex libssl-dev dpkg-dev lzop libncurses5-dev
```

+ 下载野火自己维护的u-boot源码

```
git clone -b ebf_v2020_10_imx https://gitee.com/Embedfire/ebf_linux_uboot
```

+ 编译emmc版本，其中boot配置文件mx6ull_fire_mmc_defconfig位于configs文件夹中

```
sudo make distclean
sudo make ARCH=arm CROSS_COMPILE=arm-none-eabi- mx6ull_fire_mmc_defconfig
#编译uboot
sudo make ARCH=arm CROSS_COMPILE=arm-none-eabi- -j4

#编译产物分析
u-boot：初步链接后得到的uboot文件
u-boot-nodtb.bin:在u-boot基础上，经过objcopy去除符号信息后的可执行二进制下载文件
u-boot.dtb：uboot的设备树编译二进制文件
u-boot.bin：在u-boot-nodtb.bin后追加了u-boot.dtb形成的
u-boot-dtb.imx：是u-boot.bin添加了3KB头部信息和尾部信息组成的镜像，是我们想要的最终文件
```



## NXP 官方 u-boot编译

+ 下载









