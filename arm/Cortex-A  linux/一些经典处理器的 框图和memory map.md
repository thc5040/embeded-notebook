## i.MX 6ULL

![](.\markdown src\i.MX 6ULL block diagram.png)

| Start address | End address |  Size   | Description                  |
| ------------- | ----------- | :-----: | ---------------------------- |
| 0000_0000     | 0001_6FFF   |  92 KB  | Boot ROM (ROMCP)             |
| 0001_7000     | 0001_7FFF   |  4 KB   | Boot ROM—Protected 4 KB area |
|               |             |         |                              |
| 0090_0000     | 0091_FFFF   | 128 KB  | OCRAM 128 KB                 |
|               |             |         |                              |
| 8000_0000     | FFFF_FFFF   | 2048 MB | MMDC—x16 DDR Controller.     |



+ The Multi-Mode DDR Controller is a dedicated interface to DDR3/DDR3L/LPDDR2 SDRAM. 

## STM32MP153

![](.\markdown src\STM32MP153 memory map.png)

![](E:\technique doc\embeded-notebook\arm\Cortex-A  linux\markdown src\STM32MP153 memory map2.png)



## AM335x

![](.\markdown src\am335x block diagram.png)

| Start address | End address | Size  | Description            |
| ------------- | ----------- | :---: | ---------------------- |
| 0x0000_0000   | 0x1FFF_FFFF | 512MB | GPMC (External Memory) |
|               |             |       |                        |
| 0x4000_0000   | 0x4001_FFFF | 128KB | Boot ROM               |
| 0x4002_0000   | 0x4002_BFFF | 48KB  |                        |
|               |             |       |                        |
| 0x402F_0400   | 0x402F_FFFF | 64KB  | SRAM internal          |
| 0x4030_0000   | 0x4030_FFFF |       | L3 OCMC0               |



## i.MX 8MM

![](E:\technique doc\embeded-notebook\arm\Cortex-A  linux\markdown src\i.MX 8MM block diagram.png)

| Start address | End address |  Size  | Description                |
| ------------- | ----------- | :----: | -------------------------- |
| 0000_0000     | 0003_EFFF   | 252KB  | Boot ROM                   |
| 0003_F000     | 0003_FFFF   |  4KB   |                            |
|               |             |        |                            |
| 0018_0000     | 0018_7FFF   |  32KB  | OCRAM_S                    |
|               |             |        |                            |
| 0092_0000     | 0093_FFFF   | 128KB  | OCRAM 128KB                |
| 0090_0000     | 0091_FFFF   | 128KB  | OCRAM 128KB                |
|               |             |        |                            |
| 4000_0000     | FFFF_FFFF   | 3072MB | DDR Memory (All modules)   |
| 1_0000_0000   | 2_3FFF_FFFF | 5120MB | DDR Memory (Quad-A53 only) |







