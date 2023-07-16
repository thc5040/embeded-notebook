## 前言

+ core reset马上运行的代码就是Boot Code，这是裸机程序，OS还没加载运行。负责进行一些初始化操作
+ bootloader是如何加载和运行linux系统的。bootloader就是一段裸机程序







## u-boot简介

+ bootloader 是 boot引导 + loader加载两部分。boot引导的作用是初始化硬件等等，loader是加载OS，结束之后bootloader也就消失无用了
+ bootloader的目的就是加载OS，然后就转交系统控制权。为了完成这点，必须先要进行一些core、外设、内存等的初始化工作。换句话说，bootloader初始化一部分必须的硬件，然后加载OS，最后转件控制权给OS
+ u-boot支持多种架构的处理器，如ARM, x86, MIPS等
+ u-boot支持多种启动方式，如USB, SD Card, Nor flash, NAND flash等，还支持FTP网络启动linux kernel
+ u-boot支持命令行操作，可以配置 u-boot 

## u-boot的两个阶段

+ u-boot编译后，会生成两个image文件，分别是第一阶段的 MLO 和第二阶段的 u-boot.img。
+ 系统上电后，先执行SoC内部ROM的产商固话的代码，用来加载bootloader程序，比如STM32MP153这部分ROM就有128KB。这段代码通过检测特定引脚的状态（跳线帽设置），用来确定启动方式。SPL首先被加载进来，第二阶段的img由SPL加载
+ 第一阶段的bootloader也称为SPL(secondaly program loader)，是一段很小的代码。SPL会初始化一些硬件，然后将剩余的u-boot加载进来。比如，SPL会初始化内存控制器和SDRAM，因为后续代码的执行都需要这个环境，还初始化一些其余的必须得设备。



## Boot的四个阶段

Boot从头到尾来说，应该包括了四个阶段

1. ROM
2. Secondary Program Loader (SPL)
3. Thrtiary Program Loader （TPL，u-boot， SPL与u-boot一起?) 
4. Kernel level 

####  ROM step

ROM中包含了上电reset后首先运行的代码，芯片产商将一部分代码固话在ROM中，不可修改。这部分代码是为下一阶段做准备，比如检测特定的引脚，定位到SPL所在的位置（如emmc, NANA flash, SD 卡），那么显然，ROM也要做一部分硬件初始化工作才可以完成这部分工作。然后将SPL加载进SRAM中（此时DRAM还没有初始化，不可以使用）。为何不把u-boot整一块放进来？因为芯片内部的SRAM大小空间是很有限的，可能不能把U-boot整一块拿到内部的SRAM中，所以分开了2部分。SPL是其中更小的一部分，进行前期的一些Boot工作。在ROM阶段结束后，SPL已经放入到了SRAM中，ROM跳转到SRAM中的SPL中

#### The SPL Step

SPL配置内存控制器，DRAM和一些其他的组件，然后将TPL加载进DRAM中。SPL通常是不能与用户互动的（如命令行），直接执行到底。在这个阶段结束，DRAM中已经包含了TPL，然后SPL跳转到该处

#### The TPL Step

这个阶段一般认为就是u-boot执行阶段。此时可以用命令行进行交互，配置等。并将kernel放入到DRAM中，然后就跳转到kernel执行。在后续阶段，bootloader就消失了，相关内存就被清理掉。

![](.\markdown src\boot\boot process1.png)







