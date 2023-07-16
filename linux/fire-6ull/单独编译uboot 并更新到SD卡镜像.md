+ sd卡已经烧录野火电子的鲁班猫镜像
+ 下载野火电子提供的uboot，交叉编译uboot

```
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

