## 前言

+ cache用来弥补处理器的处理速度和main memory的读写速度之前存在的巨大差异，造成性能浪费
+ cache是处理器芯片片内的一小块SRAM，这块SRAM的速度很快，比main memory的DRAM快了成百上千倍，但是造价昂贵，同样也比main memory的DRAM贵了上千倍，并且SRAM的电路体积也很大
+ 处理器先将main memory的指令数据缓存到cache中，实际上一般处理器是从cache拿指令和数据的，即cache的内容是main memory的一份拷贝

![](.\markdown src\cache\figure8-1.png)

+ CPU首先是从cache拿指令和数据的，这样速度就很快，不需要去接触很慢的DRAM
+ cache几乎是在背后默默工作的，对大部分程序员来说是透明的
+ 由于程序的空间局部性和时间局部性原理，所以cache往往工作的很好，提高处理速度。
+ write buffer也是一个重要的区域。处理器在执行store相关指令的时候，不需要直接将数据写到main memory中，因为这样很慢。反而是处理器将相关的地址、控制和写入数据这些相关的东西放到write buffer中，由write buffer区域将数据写入到main memory中。这就释放了CPU，去执行下一部分的指令

## 8.1 Why do caches help?

+ 因为程序局部性原理，所以cache可以工作的很好，即便刚开始的部分程序是比较慢的，但是后面就会将这部分相邻的指令、数据缓存到cache中，后续的运行就非常快
+ cache只能缓存一部分的main memory，所以需要一种方法快速地找到这个地址的数据/指令是否在cache中

## 8.2 Cache drawbacks

+ cache也带来了一部分缺点。
+ 如程序的执行时间变得不可确定。因为如果cache已经满了话，那就需要有cache替换操作，还要重新缓存。对于程序来说，几乎不可能知道自己什么时候一定在cache中。
+ 所以即便是执行同一段代码，执行时间可能也很不一样，这对于一些硬实时系统来说是不可接受的
+ 还需要一种控制方法，连接CPU和cache，cache和main memory。cache如何分配
+ cache和main memory的内容可能是不一致的。当CPU更新了cache的内容后，但却没有更新main memory。另外，也可能main memory被更新了，但是cache还是旧的内容。这个是缓存一致性问题，特别是在多核处理器和使用DMA控制器的时候尤为突出

## 8.3 Memory hierarchy

+ 内存的金字塔层级结构
+ L1 cache是最靠近core内部的cache。对于哈佛结构来说，L1同时分别有数据cache, 指令cache

![](.\markdown src\cache\figure8-2.png)

+ L1 cache一般可以为16KB or 32KB（数据或指令），因为这么大的cache足以为1G Hz主频以上的处理器加速
+ L2 cache则更大，比如 256KB 512KB 1MB，L2会慢一些，但空间更大，会同时存放数据和指令
+ 可以实现多核处理器，将多个core融在一个clusters中，各个core有自己的L1 cache，但共用L2 cache。此时特别是要实现缓存一致性，当一个core修改了共享的数据后，其他core也要观察到这种改变

## 8.4 Cache architecture

+ I-cache, D-cache就特指了L1，对于ARM来说，因为是哈佛结构
+ cache要保存一些地址、数据、状态信息。主存中地址的高位部分叫做 tag；tag是需要存储在cache 中的 tag RAM中的。
+ cache一次缓存一个cache line的数据，一般为32 64字节。地址的中间部分称为 index，用来在cache中找到这个地址在那个cache line中。当这个cache line缓存了主存的数据，就为valid状态，否则是invalid
+ 地址的尾部几位是offset，也就是找到cache line后使用offset定位到具体哪个字节。offset的长度与cache line的大小有关。当时32字节时-offset就是5bits， 64字节就是6bits
+ 每个cache line还有一个或多个status bits，用来表明这个line是valid还是invalid的。对于数据cache，还需要一个或多个dirty bits用来指示这个数据是已经在cache更改过了，但是在main memory中还没改变。
+ figure8-3是cache中的一些名词。
+ line是指cache一次缓存多个连续的字节
+ index用来索引到这个地址在哪个cache line中
+ way将cache分成多个相同的部分，防止内存颠簸问题。way中相同index索引到的多个cache line叫set。当只有一个way时，cache是直接映射缓存结构；当有多个way时，是多路组相连缓存结构
+ tag存储在cache中，用来最终比较标识这个地址是否位于这个cache line中

![](.\markdown src\cache\figure8-3.png)

#### 8.4.2 Direct mapped caches

+ 在这种情况下每个地址的数据只可能缓存到cache中的某个地方
+ 会产生内存颠簸问题。比如下面这个例子中，0x000 0x0040 0x0080都只能缓存在cache的第一行中，那么如果程序不断同时使用 0x000 0x0040 0x0080的数据，就只能不断地更新这个cache line，性能反而降低

![](.\markdown src\cache\figure8-4.png)

#### 8.4.3 Set associative caches

+ 多路组向量，这是ARM的实际情况。通过多个way，最大可能避免了直接映射结构的内存颠簸问题
+ 这种情况下，index可能索引到多个cache line，进行多个tag的比较，最终定位到具体哪个way的cache line

![](.\markdown src\cache\figure8-6.png)

#### 8.4.4 A real-life example

+ figure8-7是一个实际的例子。一个data cache有32KB，分成4-way。每一个cache line能存放32字节数据。那么可以计算出一个way是8KB大小，有256个cache line。那么offset就是低5位，index就是中间占据8位，其余的高19位就是tag

![](.\markdown src\cache\figure8-7.png)

#### 8.4.5 Cache controller

+ cache控制器用于负责管理cache memory，自动的将main memory的指令数据写入到cache中。负责将core的读写内存需求作用到cache中或者main memory中
+ 当core发出一个地址后，cache控制器需要去对比这个地址的指令数据是否已经缓存在cache中，这个过程叫cache look-up。当在相应的way和cache line中成功匹配到tag部分后，并且是valid状态，就是cache hit。
+ 否则就是 cache miss，此时需要进一步到L2 cache或者main memory中找到相应地址的内容，然后拷贝一份到cache中，然后就将指令数据返回给core。core不需要完全等待linefill这个过程，实际上cache控制器会将这个line的数据中的 critical word 部分数据直接返回给core，core就可以继续执行下去不用等待。而cache控制器继续默默地进行linefill过程。

#### 8.4.6 Virtual and physical tags and indexs

+ cache实际工作中肯定要与MMU、虚拟地址、物理地址这些打交道的
+ 在旧的ARM中，使用虚拟地址的index和tag区查找cache（Virtually Indexed, Virtually Tagged）。这种方法的好处是不需要将虚拟地址翻译成物理地址，直接就可以去查cache，速度快。但问题是在多进程OS中，切换了进程后，core会发出与上一个进程相同的虚拟地址，那这样查找到cache的数据就是上一个进程的数据，会出错。所以只能在切换进程的时候同时将cache clean或invalidated。但这会严重影响性能。
+ 现在非常常用的一种方法是VIPT（Virtually Indexed, Physically Tagged），这种方法使用虚拟地址的index去查找cache line，同时MMU进行虚拟地址翻译成物理地址，找到具体物理地址后，就可以用tag去cache line中比较tag，看是否命中。使用物理tag的好处是当虚拟地址到物理地址的映射改变后（进程切换），cache不需要失效。同时cache控制器在查找cache line的过程时，MMU也可以进行地址翻译过程，同时工作，速度大大加快。当然，这要求虚拟地址和物理地址的中间index字段是要相同的才可以
+ 然而，VIPT也有缺点，限制了cache的容量。比如一个32KB的4路组相连结构，一个cache line是64bytes，那么一way就有8KB，有128个cache line。那么cache要求bit[5:0]是offset，bit[12:6]位是index，这里就要用到地址的bit[12]。但是如果MMU采取4KB的页大小，那么虚拟地址和物理地址的bit[11:0]是一样的，但是bit[12]并不是一样的，那么就会出问题
+ 解决这个问题可以用OS的内核软件去解决，另一种方法是采用（Physically Indexed, Physically Taged) PIPT. Cortex-A的data cache都是采用了PIPT的方式，但此时硬件的复杂度会更高

## 8.5 Cache policies

+ allocation policy：什么时候将main memory的内存拷贝到cache中
+ replacement policy：选择哪一个cache line
+ write policy：在写操作的时候怎么办

#### 8.5.1 Allocation policy

+ read allocate，读分配。至于当读操作的时候发生cache miss，然后才从main memory中找到该数据拷贝到cache中。当写的时候cache miss了不会，而是直接继续写入到下一级cache 或 到达 main memory
+ wirte allocate, 写分配，或者叫 read-write-allocate。此时不管是读 写发生了miss，都会拷贝到cache中。这通常与wirte policy中的write-back策略搭配使用

#### 8.5.2 Replacement policy

+ 当需要copy进cache中，需要选择一个cache line，这个cache line叫做 victim（受害者），当victim是valid 并且是dirty的时候，这个victim在被驱逐出去的时候还必须将数据写回到main memory或者下一级cache中
+ 地址的index部分用来选择哪个set，如果只有一路的话，那么就是它了。如果是多路组相连结构，还需要replacement policy去选择一个set替换
+ Round-robin / cyclic 循环替换，大家轮流来
+ Pseudo-random 随机替换
+ Least Recently used (LRU) 近期最少使用，将最旧使用的那个set替换

#### 8.5.3 Write policy

+ 写操作要改变memory的值，所以要注意怎么办
+ Write-through，直写，在改变cache内容的同时，也改变main memory的内容，这样可以保证缓存一致性。但通常这个速度很慢。这里不管hit 还是 miss都是一样的
+ Write-back，回写，只写到cache中，而不写到main memory中。优点是速度快，不需要频繁跟main memory打交道。但缺点是cache中的是新数据，main memory中的是旧数据，这时有缓存一致性问题。此时必须维护一个dirty bit，用来标记新旧数据。驱逐dirty bit的cache line时，必须要将其写回到下一级内存。这时如果hit了就没什么问题。如果miss的话就比较麻烦，如果采用的是write-allocate，那么miss后就回将main memory的内容拷贝到cache中，然后修改cache，和置dirty bit。如果不是这种的话，那就将数据写入到下一级内容中（由于有write buffer的存在，所以也不会有性能损失）

## 8.6 Write and Fetch buffers

+ write buffer是一个在core内的写缓冲区，目的是让core在执行store写操作的时候不用等待，将其暂写入到一个高速的write buffer中，这样core就继续执行后续指令，而write buffer 将这些数据排放到memory中
+ write buffer与cache是很类似的，目的都是为了加速，降低core和memory的差距。但是cache 主要是为了暂时存放数据，要用的时候快速的从cache中拿出来，所以叫缓存，台湾省的翻译叫 快取。
+ 一个疑惑是cache 和 write buffer怎么区分，cache不是也有write功能吗？比如cache需要驱逐一个cache line，而缓存新的数据的时候，如果这个cache line是dirty的，那么就要将cache line的数据写回到下一级memory中。如果等待这个先将这个cache line写入到memory，然后再缓存cache，最后将内容读到core 寄存器，那时间太慢了。这时首先将cach line的内容是写到wirte buffer中的，而再由write buffer慢慢地写回到下一级memory。
+ 所以可以看出，cache主要是为了read操作更快，当然也可以write 都cache中，速度也非常快。write buffer主要是弥补write 到 main memory或者下一级memory的速度
+ 但write buffer有可能会造成危险，特别是一些跟外设打交道的时候。比如我们想将数据write 到 外设的某些寄存器，但是core是将其写到了write buffer中，而不是memory，就又去执行下面的指令了。如果后续的指令要求上面的操作首先彻底完成才能正常进行，这可能会出错。这时候可能要停止等待，直到写操作完成

## 8.7 Cache performance and hit rete

+ hit rete, miss rate。显然，hit rate越高，说明性能越好
+ 经可能去使能cache 和 write buffer可以加速巨大，通常所有的RAM/DDR ROM/flash，都要可以被缓存，但是外设通常不要被缓存
+ 编写cache-friendly的代码，即连续使用连续的数据和代码，因为每次缓存的都是一个cache line，也就是将连续一部分的内存都缓存进去。如果使用内存相邻的数据，那么往往cache带来的增益是很大的。比如使用连续的数组数据结构。比如链表就不是连续的内存空间，可能会慢。

## 8.8 Invalidating and cleaning cache memory



## 8.9 Point of coherency and unification



## 8.10 Level 2 cache controller



## 8.11 Parity and ECC in caches

























