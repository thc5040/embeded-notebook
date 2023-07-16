## 前言

+ Memory Management Unit（MMU）与进程结合起来，让每个进程都感觉自己独占一片连续的内存空间。核心的作用就是将虚拟内存翻译成物理内存。
+ 除此之外，MMU还控制每块区域内存的范围权限、内存顺序、cache策略等，即管理内存
+ 在一个多任务/进程的计算机系统中，往往需要对整块内存进行分块，并且给每一个块内存进行权限、属性定义。在linux这些非常复杂的OS中，往往需要对内存进行很多控制
+ MMU可以让应用程序不需要知道物理内存中的相关知识也能很好工作，简化编程。应用程序中操作的都是虚拟地址，而硬件系统对内存的操作是物理地址
+ OS负责对MMU进行编程，以映射虚拟内存和物理内存，如下图

![](.\markdown src\MMU\Virtual and physical memory.png)

+ MMU刚开始是disabled的，此时操作的是物理地址。当MMU开始工作后，如果转换地址失败，就会给出一个异常（缺页异常），那么OS就要去处理

## 9.1 Virtual memory

+ 每个进程都有一个虚拟地址，OS负责将进程的代码/数据信息放在具体的物理内存中，但这对进程/应用来说是隐秘的，透明的
+ 地址转换过程借助 translation tables / page tables 完成，也就是页表。每个进程都有一个页表，每个页表有多个页表项(按行排列)，每一项都负责映射一块内存
+ MMU在观念上，如下图所示。CPU生成的是虚拟地址，页表存储在memory中，MMU从memory中定位到具体进程的页表基地址，然后根据虚拟地址，翻译出实际的物理地址。为了加快速度和利用局部性原理，MMU中有cache来临时缓存页表项，称为TLB （Translation lookaside Buffer）

## 9.2 Translation Lookaside Buffer

+ TLB是MMU内用来缓存页表的一块cache。CPU发出虚拟地址后，首先会从TLB中找，如果找到了，就是cache hit，那么可以马上直接拿出物理地址。如果没找到，就是cache miss，那么就得从memory中缓存一个页表项TLB。这个过程跟普通的cache是很类似的
+ TLB cache hit的话，那么是没有额外开销的，速度非常块，TLB的结构如下图所示，里面直接就存储着虚拟地址和物理地址
+ 有cache的地方就有缓存一致性问题，TLB也不例外，当直接修改页表项时，必须在TLB中失效这个页表项

![](.\markdown src\MMU\llustration of TLB structure.png)

## 9.3 Choice of page sizes

+ 页大小的选择是很重要的。如果一页很大，那么控制的细粒度就很差，浪费内存的情况也较大，但是此时页表项就比较好，很容易cache hit，速度快。页小的时候，优缺点刚好反着来
+ ARM-v7A 一般情况下可以选2种，一种是一级页表，每个页占1MB内存大小。一种是两级页表，每个页是4KB内存

## 9.4 First level address translation

+ 一级页表翻译过程，第一步要先找到该虚拟地址的页表项
+ 一级页表将4GB内存分成4096份(section)，每一份1MB的虚拟地址空间，那么一级页表就有4096个页表项，每个页表项大小事4 bytes, 那么一个一级页表占了 16K Bytes内存
+ 每个页表项都有一个指针去指向二级页表的基地址或者直接就是那转换的1MB内存区域。如果只使用了一级页表，那么这个页表项就有一个指针指向那1MB物理内存页
+ 虚拟地址和物理地址的低位都是相同的，因为这是一个相对于base address的offset。ARM V7A最多支持两级页表，每一级页表都使用short-descriptor描述一些功能
+ 一级页表的表基地址 translation table base address放在寄存器CP15 c2，必须16KB对齐(后14位为0)
+ 在翻译的时候，虚拟地址的高12位作为index从页表基地址中找到具体的页表项，12位是因为一个一级页表有4096项
+ 以下图为例。假设一级页表基地址为 0x12300000, 处理器发出一个虚拟地址为 0x00100000，这个虚拟地址的高12位用来索引具体的页表项位置，也就是 0x001，那么这个虚拟地址的页表项就是 0x1230000 + 0x001*4 = 0x12300004 ，现在就可以用这个页表项里面的内容定位到具体的物理地址

![](.\markdown src\MMU\Finding the address of the level 1 translation table entry.png)

+ 一级页表的页表项有以下4种形式，最重要的当然是中间的两种，指向二级页表基地址或者直接就是那块物理内存的基地址

![](.\markdown src\MMU\level 1 translation table entry format.png)

+ 下图简单地说明了虚拟地址通过一级页表直接翻译到物理地址的过程。一级页表基地址已知存在了寄存器内，虚拟地址的高12位就用来index找到具体的页表项，从页表项中找到物理地址的基地址，然后再与后20位组合在一起，就成为了最终物理地址。所以这种情况下物理地址与虚拟地址的后20位是相同的，后20位也可以叫做page index 和 section index

![](.\markdown src\MMU\first level address translation.png)

+ 页表项中包含了将虚拟地址翻译成物理地址的基地址（高12位部分）。除此之外，还包含一些页表属性，如access permissions, cacheable, bufferable等，这就管理了这一页内存
+ 下图展示了翻译的具体过程。通过页表基地址和虚拟地址的高12位，定位到具体的页表项 first level descriptor address，然后从中拿出页表项中的一部分section base address（另一部分是页表项的一些属性）作为物理地址的高12位，再与虚拟地址的低20位组成了新的物理地址

![](.\markdown src\MMU\figure9-7.png)

## 9.5 Level 2 translation tables

+ 每个二级页表有256个页表项，每个页表项占4bytes，那么就每个二级页表在memory中就占据了1KB内存。并且二级页表基地址必须是1KB对齐的（后10位全为0）。每个页表项包含了一个4KB的虚拟地址到物理地址内存空间的转换，4KB一页也意味着虚拟地址和物理地址共用低12位。
+ 二级页表项其实有3中类型，如下所示，但一般我们理解第二种，每个页表项指向一个4KB的内存区即可，也就是一页4KB大小。页表项中除了包含页的基地址外，还有一些页表属性

![](.\markdown src\MMU\figure 9-8.png)

+ 二级页表项的翻译过程如下图所示，由一级页表中获得。虚拟地址的高12位检索到对应的一级页表项，里面包含了二级页表的基地址。虚拟地址的次8位作为index，结合二级页表的基地址获得二级页表项的地址。

![](.\markdown src\MMU\figure9-9.png)

+ 完整的二级页表翻译过程如下图所示，看懂了这幅图就知道了MMU中虚拟地址到物理地址的转换过程。里面有很多细节，如如何找到页表的基地址（高位）？如果找到一级页表项？如何从一级页表项的内容找到二级页表项？如何根据二级页表项的内容最终得到物理地址？页表占据空间多大？页表存放在哪里？MMU如何找到页表？TLB如何缓存页表？页表项的属性如何管理内存块？缺页异常？如何给进程分配页表？进程中的页表需要多少内存存储？

![](.\markdown src\MMU\figure 9-10.png)

## 9.6 Memory attributes 

+ 页表项除了用于翻译地址外，其中还有很多属性字段去管理该页内存，包括 访问权限、内存类型、cache策略
+ 各种访问权限如下图所示。当访问权限fault后，会产生一个异常，异常的原因和异常状态等会存储在CP15寄存器中。异常中断处理函数可以根据这些信息去纠正这个问题，并且返回之前的应用程序入口。或者直接应用程序出错了终止程序。访问权限是非常有用的，比如代码段的访问权限在非特权是就可以设置为只读，这样代码指令就不会被修改

![](.\markdown src\MMU\table 9-1.png)

+ 内存类型有3中，strongly-ordered, device, normal。normal是大部分内存类型，表示架构允许对这些内存进行推测数据读取访问，顺序不一定是一样的。device是外设内存映射。

![](E:\technique doc\embeded-notebook\arm\markdown src\MMU\table 9-2.png)

+ 以下的一些bits设置了页表项的内存类型，和cache策略。Outer policy指的是L2 L3的cache策略，inner 指的是L1 cache策略

![](E:\technique doc\embeded-notebook\arm\markdown src\MMU\table 9-3.png)

+ Execute never
+ Domains

## 9.7 Multi-tasking and OS usage of translation tables

+ 在应用启动运行时，OS就给它分配一组页表项以映射物理-虚拟内存。如果在后面应用映射到额外的代码或者数据（如malloc），那么就会修改哪些页表项。当应用完成后，OS会回收这些页表项和该部分物理内存。在多线程切换时，不同线程的页表项也是不同的，互不干扰。
+ Address Spaces ID（ASID）。如果使能了页表中的nG bit，那么在地址翻译的时候，还会用到一个ASID value。在使能这个时，TLB中缓存的页表项中不仅包含虚拟-物理地址，还包含ASID。翻译的过程不仅要虚拟地址匹配上了，还要求ASID是该进程的ASID才行。这个的作用是为了降低上下文切换带来的不断需要缓存页表的开销。
+ 如下图所示，假设A B C三个线程都有一个虚拟地址为0x000。这里每个进程都有ASID作为额外的标识，所以即便这个三个虚拟地址均为0x000，但可以同时存在TLB中，这样就减少了上下文切换过程中，页表项失效带来大量的cache miss的速度降低

![](E:\technique doc\embeded-notebook\arm\markdown src\MMU\table 9-11.png)

+ 寄存器TTBR0  TTBR1的作用

















