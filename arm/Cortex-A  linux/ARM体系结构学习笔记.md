## 前言

ARM-v7A



## 总体

#### 1. 一个ARM体系结构应该关注的点

+ 处理器的操作模式、寄存器组是怎样的
+ 处理器是多少位的，指令集是怎样的，汇编语言
+ 对浮点数的支持，SIMD，NEON
+ Cache排列是怎样的，多少级Cache，容量多大，Cache的组织方式，读写方式
+ 内存排列，分布，管理情况，虚拟内存，MMU
+ 异常、中断，一个异常如何触发、处理、返回，中断向量表寻址
+ 上电后的启动顺序，执行情况，boot

#### 2. 一个典型的Cortex-A7框架图

![](.\markdown src\Cortex-A7 processor 1.png)



## 9. The Memory Management Unit

+ 最重要的就是MMU，将虚拟地址转化为物理地址，让进程以为自己独占正片连续的内存空间
+ 操作系统负责对MMU进行编程，进行这两种地址的转换
+ ![](.\markdown src\MMU 1.png)
+ 转换过程借助TLB完成
+ 页表，多级页表
+ 处理器生成的是虚拟地址，MMU将虚拟地址的某些为更改，就成了物理地址
+ 页表存储在内存中，MMU中的专用硬件可以读取内存中的TLB，这个过程为 translation table walking
+ 初始时MMU是没有被其用的，必须enable MMU
+ 如果MMU没有找到页表项，表示转换失败，产生一个缺页异常，测试OS检测到后，应该处理这个异常，分配物理地址，分配页表
+ 每次从内存拿页表做转换时很慢的，MMU内部有专门的cache用来缓存页表，叫TLB
+ 页大小选择，页越小，对内存控制越精细，越节约，但是需要的页表数量就越多，容易导致cache miss；那么页越大，可能就会更浪费内存，但是更容易cache hit。
+ ARM采用2级页表。第一级页表将4GB的内存空间氛围4096*1MB，那么一级页表就有4096个，每页占1MB内存。那么虚拟机制的高12位是一级页表的Table Offset，其余的

![](.\markdown src\MMU 2.png)





## 参考

+ ARM V8-A编程手册
+ （番外一）Arm32 中虚拟地址机制分析（Arm cortex-A系列 MMU工作机制分析）:

https://blog.csdn.net/qq_41957544/article/details/109108364