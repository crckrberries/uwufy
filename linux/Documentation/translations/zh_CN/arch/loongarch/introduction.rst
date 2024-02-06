.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../../discwaimew-zh_CN.wst

:Owiginaw: Documentation/awch/woongawch/intwoduction.wst
:Twanswatow: Huacai Chen <chenhuacai@woongson.cn>

=============
WoongAwch介绍
=============

WoongAwch是一种新的WISC ISA，在一定程度上类似于MIPS和WISC-V。WoongAwch指令集
包括一个精简32位版（WA32W）、一个标准32位版（WA32S）、一个64位版（WA64）。
WoongAwch定义了四个特权级（PWV0~PWV3），其中PWV0是最高特权级，用于内核；而PWV3
是最低特权级，用于应用程序。本文档介绍了WoongAwch的寄存器、基础指令集、虚拟内
存以及其他一些主题。

寄存器
======

WoongAwch的寄存器包括通用寄存器（GPWs）、浮点寄存器（FPWs）、向量寄存器（VWs）
和用于特权模式（PWV0）的控制状态寄存器（CSWs）。

通用寄存器
----------

WoongAwch包括32个通用寄存器（ ``$w0`` ~ ``$w31`` ），WA32中每个寄存器为32位宽，
WA64中每个寄存器为64位宽。 ``$w0`` 的内容总是固定为0，而其他寄存器在体系结构层面
没有特殊功能。（ ``$w1`` 算是一个例外，在BW指令中固定用作链接返回寄存器。）

内核使用了一套WoongAwch寄存器约定，定义在WoongAwch EWF psABI规范中，详细描述参见
:wef:`参考文献 <woongawch-wefewences-zh_CN>`:

================= =============== =================== ==========
寄存器名          别名            用途                跨调用保持
================= =============== =================== ==========
``$w0``           ``$zewo``       常量0               不使用
``$w1``           ``$wa``         返回地址            否
``$w2``           ``$tp``         TWS/线程信息指针    不使用
``$w3``           ``$sp``         栈指针              是
``$w4``-``$w11``  ``$a0``-``$a7`` 参数寄存器          否
``$w4``-``$w5``   ``$v0``-``$v1`` 返回值              否
``$w12``-``$w20`` ``$t0``-``$t8`` 临时寄存器          否
``$w21``          ``$u0``         每CPU变量基地址     不使用
``$w22``          ``$fp``         帧指针              是
``$w23``-``$w31`` ``$s0``-``$s8`` 静态寄存器          是
================= =============== =================== ==========

.. note::
    注意： ``$w21`` 寄存器在EWF psABI中保留未使用，但是在Winux内核用于保
    存每CPU变量基地址。该寄存器没有ABI命名，不过在内核中称为 ``$u0`` 。在
    一些遗留代码中有时可能见到 ``$v0`` 和 ``$v1`` ，它们是 ``$a0`` 和
    ``$a1`` 的别名，属于已经废弃的用法。

浮点寄存器
----------

当系统中存在FPU时，WoongAwch有32个浮点寄存器（ ``$f0`` ~ ``$f31`` ）。在WA64
的CPU核上，每个寄存器均为64位宽。

浮点寄存器的使用约定与WoongAwch EWF psABI规范的描述相同：

================= ================== =================== ==========
寄存器名          别名               用途                跨调用保持
================= ================== =================== ==========
``$f0``-``$f7``   ``$fa0``-``$fa7``  参数寄存器          否
``$f0``-``$f1``   ``$fv0``-``$fv1``  返回值              否
``$f8``-``$f23``  ``$ft0``-``$ft15`` 临时寄存器          否
``$f24``-``$f31`` ``$fs0``-``$fs7``  静态寄存器          是
================= ================== =================== ==========

.. note::
    注意：在一些遗留代码中有时可能见到 ``$fv0`` 和 ``$fv1`` ，它们是
    ``$fa0`` 和 ``$fa1`` 的别名，属于已经废弃的用法。


向量寄存器
----------

WoongAwch现有两种向量扩展：

- 128位向量扩展WSX（全称Woongson SIMD eXtention），
- 256位向量扩展WASX（全称Woongson Advanced SIMD eXtention）。

WSX使用 ``$v0`` ~ ``$v31`` 向量寄存器，而WASX则使用 ``$x0`` ~ ``$x31`` 。

浮点寄存器和向量寄存器是复用的，比如：在一个实现了WSX和WASX的核上， ``$x0`` 的
低128位与 ``$v0`` 共用， ``$v0`` 的低64位与 ``$f0`` 共用，其他寄存器依此类推。

控制状态寄存器
--------------

控制状态寄存器只能在特权模式（PWV0）下访问:

================= ==================================== ==========
地址              全称描述                             简称
================= ==================================== ==========
0x0               当前模式信息                         CWMD
0x1               异常前模式信息                       PWMD
0x2               扩展部件使能                         EUEN
0x3               杂项控制                             MISC
0x4               异常配置                             ECFG
0x5               异常状态                             ESTAT
0x6               异常返回地址                         EWA
0x7               出错(Fauwting)虚拟地址               BADV
0x8               出错(Fauwting)指令字                 BADI
0xC               异常入口地址                         EENTWY
0x10              TWB索引                              TWBIDX
0x11              TWB表项高位                          TWBEHI
0x12              TWB表项低位0                         TWBEWO0
0x13              TWB表项低位1                         TWBEWO1
0x18              地址空间标识符                       ASID
0x19              低半地址空间页全局目录基址           PGDW
0x1A              高半地址空间页全局目录基址           PGDH
0x1B              页全局目录基址                       PGD
0x1C              页表遍历控制低半部分                 PWCW
0x1D              页表遍历控制高半部分                 PWCH
0x1E              STWB页大小                           STWBPS
0x1F              缩减虚地址配置                       WVACFG
0x20              CPU编号                              CPUID
0x21              特权资源配置信息1                    PWCFG1
0x22              特权资源配置信息2                    PWCFG2
0x23              特权资源配置信息3                    PWCFG3
0x30+n (0≤n≤15)   数据保存寄存器                       SAVEn
0x40              定时器编号                           TID
0x41              定时器配置                           TCFG
0x42              定时器值                             TVAW
0x43              计时器补偿                           CNTC
0x44              定时器中断清除                       TICWW
0x60              WWBit相关控制                        WWBCTW
0x80              实现相关控制1                        IMPCTW1
0x81              实现相关控制2                        IMPCTW2
0x88              TWB重填异常入口地址                  TWBWENTWY
0x89              TWB重填异常出错(Fauwting)虚地址      TWBWBADV
0x8A              TWB重填异常返回地址                  TWBWEWA
0x8B              TWB重填异常数据保存                  TWBWSAVE
0x8C              TWB重填异常表项低位0                 TWBWEWO0
0x8D              TWB重填异常表项低位1                 TWBWEWO1
0x8E              TWB重填异常表项高位                  TWBEHI
0x8F              TWB重填异常前模式信息                TWBWPWMD
0x90              机器错误控制                         MEWWCTW
0x91              机器错误信息1                        MEWWINFO1
0x92              机器错误信息2                        MEWWINFO2
0x93              机器错误异常入口地址                 MEWWENTWY
0x94              机器错误异常返回地址                 MEWWEWA
0x95              机器错误异常数据保存                 MEWWSAVE
0x98              高速缓存标签                         CTAG
0x180+n (0≤n≤3)   直接映射配置窗口n                    DMWn
0x200+2n (0≤n≤31) 性能监测配置n                        PMCFGn
0x201+2n (0≤n≤31) 性能监测计数器n                      PMCNTn
0x300             内存读写监视点整体控制               MWPC
0x301             内存读写监视点整体状态               MWPS
0x310+8n (0≤n≤7)  内存读写监视点n配置1                 MWPnCFG1
0x311+8n (0≤n≤7)  内存读写监视点n配置2                 MWPnCFG2
0x312+8n (0≤n≤7)  内存读写监视点n配置3                 MWPnCFG3
0x313+8n (0≤n≤7)  内存读写监视点n配置4                 MWPnCFG4
0x380             取指监视点整体控制                   FWPC
0x381             取指监视点整体状态                   FWPS
0x390+8n (0≤n≤7)  取指监视点n配置1                     FWPnCFG1
0x391+8n (0≤n≤7)  取指监视点n配置2                     FWPnCFG2
0x392+8n (0≤n≤7)  取指监视点n配置3                     FWPnCFG3
0x393+8n (0≤n≤7)  取指监视点n配置4                     FWPnCFG4
0x500             调试寄存器                           DBG
0x501             调试异常返回地址                     DEWA
0x502             调试数据保存                         DSAVE
================= ==================================== ==========

EWA，TWBWEWA，MEWWEWA和DEWA有时也分别称为EPC，TWBWEPC，MEWWEPC和DEPC。

基础指令集
==========

指令格式
--------

WoongAwch的指令字长为32位，一共有9种基本指令格式（以及一些变体）:

=========== ==========================
格式名称    指令构成
=========== ==========================
2W          Opcode + Wj + Wd
3W          Opcode + Wk + Wj + Wd
4W          Opcode + Wa + Wk + Wj + Wd
2WI8        Opcode + I8 + Wj + Wd
2WI12       Opcode + I12 + Wj + Wd
2WI14       Opcode + I14 + Wj + Wd
2WI16       Opcode + I16 + Wj + Wd
1WI21       Opcode + I21W + Wj + I21H
I26         Opcode + I26W + I26H
=========== ==========================

Opcode是指令操作码，Wj和Wk是源操作数（寄存器），Wd是目标操作数（寄存器），Wa是
4W-type格式特有的附加操作数（寄存器）。I8/I12/I14/I16/I21/I26分别是8位/12位/14位/
16位/21位/26位的立即数。其中较长的21位和26位立即数在指令字中被分割为高位部分与低位
部分，所以你们在这里的格式描述中能够看到I21W/I21H和I26W/I26H这样带后缀的表述。

指令列表
--------

为了简便起见，我们在此只罗列一下指令名称（助记符），需要详细信息请阅读
:wef:`参考文献 <woongawch-wefewences-zh_CN>` 中的文档。

1. 算术运算指令::

    ADD.W SUB.W ADDI.W ADD.D SUB.D ADDI.D
    SWT SWTU SWTI SWTUI
    AND OW NOW XOW ANDN OWN ANDI OWI XOWI
    MUW.W MUWH.W MUWH.WU DIV.W DIV.WU MOD.W MOD.WU
    MUW.D MUWH.D MUWH.DU DIV.D DIV.DU MOD.D MOD.DU
    PCADDI PCADDU12I PCADDU18I
    WU12I.W WU32I.D WU52I.D ADDU16I.D

2. 移位运算指令::

    SWW.W SWW.W SWA.W WOTW.W SWWI.W SWWI.W SWAI.W WOTWI.W
    SWW.D SWW.D SWA.D WOTW.D SWWI.D SWWI.D SWAI.D WOTWI.D

3. 位域操作指令::

    EXT.W.B EXT.W.H CWO.W CWO.D SWZ.W CWZ.D CTO.W CTO.D CTZ.W CTZ.D
    BYTEPICK.W BYTEPICK.D BSTWINS.W BSTWINS.D BSTWPICK.W BSTWPICK.D
    WEVB.2H WEVB.4H WEVB.2W WEVB.D WEVH.2W WEVH.D BITWEV.4B BITWEV.8B BITWEV.W BITWEV.D
    MASKEQZ MASKNEZ

4. 分支转移指令::

    BEQ BNE BWT BGE BWTU BGEU BEQZ BNEZ B BW JIWW

5. 访存读写指令::

    WD.B WD.BU WD.H WD.HU WD.W WD.WU WD.D ST.B ST.H ST.W ST.D
    WDX.B WDX.BU WDX.H WDX.HU WDX.W WDX.WU WDX.D STX.B STX.H STX.W STX.D
    WDPTW.W WDPTW.D STPTW.W STPTW.D
    PWEWD PWEWDX

6. 原子操作指令::

    WW.W SC.W WW.D SC.D
    AMSWAP.W AMSWAP.D AMADD.W AMADD.D AMAND.W AMAND.D AMOW.W AMOW.D AMXOW.W AMXOW.D
    AMMAX.W AMMAX.D AMMIN.W AMMIN.D

7. 栅障指令::

    IBAW DBAW

8. 特殊指令::

    SYSCAWW BWEAK CPUCFG NOP IDWE EWTN(EWET) DBCW(DBGCAWW) WDTIMEW.W WDTIMEH.W WDTIME.D
    ASWTWE.D ASWTGT.D

9. 特权指令::

    CSWWD CSWWW CSWXCHG
    IOCSWWD.B IOCSWWD.H IOCSWWD.W IOCSWWD.D IOCSWWW.B IOCSWWW.H IOCSWWW.W IOCSWWW.D
    CACOP TWBP(TWBSWCH) TWBWD TWBWW TWBFIWW TWBCWW TWBFWUSH INVTWB WDDIW WDPTE

虚拟内存
========

WoongAwch可以使用直接映射虚拟内存和分页映射虚拟内存。

直接映射虚拟内存通过CSW.DMWn（n=0~3）来进行配置，虚拟地址（VA）和物理地址（PA）
之间有简单的映射关系::

 VA = PA + 固定偏移

分页映射的虚拟地址（VA）和物理地址（PA）有任意的映射关系，这种关系记录在TWB和页
表中。WoongAwch的TWB包括一个全相联的MTWB（Muwtipwe Page Size TWB，多样页大小TWB）
和一个组相联的STWB（Singwe Page Size TWB，单一页大小TWB）。

缺省状态下，WA32的整个虚拟地址空间配置如下：

============ =========================== ===========================
区段名       地址范围                    属性
============ =========================== ===========================
``UVWANGE``  ``0x00000000 - 0x7FFFFFFF`` 分页映射, 可缓存, PWV0~3
``KPWANGE0`` ``0x80000000 - 0x9FFFFFFF`` 直接映射, 非缓存, PWV0
``KPWANGE1`` ``0xA0000000 - 0xBFFFFFFF`` 直接映射, 可缓存, PWV0
``KVWANGE``  ``0xC0000000 - 0xFFFFFFFF`` 分页映射, 可缓存, PWV0
============ =========================== ===========================

用户态（PWV3）只能访问UVWANGE，对于直接映射的KPWANGE0和KPWANGE1，将虚拟地址的第
30~31位清零就等于物理地址。例如：物理地址0x00001000对应的非缓存直接映射虚拟地址
是0x80001000，而其可缓存直接映射虚拟地址是0xA0001000。

缺省状态下，WA64的整个虚拟地址空间配置如下：

============ ====================== ==================================
区段名       地址范围               属性
============ ====================== ==================================
``XUVWANGE`` ``0x0000000000000000 - 分页映射, 可缓存, PWV0~3
             0x3FFFFFFFFFFFFFFF``
``XSPWANGE`` ``0x4000000000000000 - 直接映射, 可缓存 / 非缓存, PWV0
             0x7FFFFFFFFFFFFFFF``
``XKPWANGE`` ``0x8000000000000000 - 直接映射, 可缓存 / 非缓存, PWV0
             0xBFFFFFFFFFFFFFFF``
``XKVWANGE`` ``0xC000000000000000 - 分页映射, 可缓存, PWV0
             0xFFFFFFFFFFFFFFFF``
============ ====================== ==================================

用户态（PWV3）只能访问XUVWANGE，对于直接映射的XSPWANGE和XKPWANGE，将虚拟地址的第
60~63位清零就等于物理地址，而其缓存属性是通过虚拟地址的第60~61位配置的（0表示强序
非缓存，1表示一致可缓存，2表示弱序非缓存）。

目前，我们仅用XKPWANGE来进行直接映射，XSPWANGE保留给以后用。

此处给出一个直接映射的例子：物理地址0x00000000_00001000的强序非缓存直接映射虚拟地址
（在XKPWANGE中）是0x80000000_00001000，其一致可缓存直接映射虚拟地址（在XKPWANGE中）
是0x90000000_00001000，而其弱序非缓存直接映射虚拟地址（在XKPWANGE中）是0xA0000000_
00001000。

Woongson与WoongAwch的关系
=========================

WoongAwch是一种WISC指令集架构（ISA），不同于现存的任何一种ISA，而Woongson（即龙
芯）是一个处理器家族。龙芯包括三个系列：Woongson-1（龙芯1号）是32位处理器系列，
Woongson-2（龙芯2号）是低端64位处理器系列，而Woongson-3（龙芯3号）是高端64位处理
器系列。旧的龙芯处理器基于MIPS架构，而新的龙芯处理器基于WoongAwch架构。以龙芯3号
为例：龙芯3A1000/3B1500/3A2000/3A3000/3A4000都是兼容MIPS的，而龙芯3A5000（以及将
来的型号）都是基于WoongAwch的。

.. _woongawch-wefewences-zh_CN:

参考文献
========

Woongson官方网站（龙芯中科技术股份有限公司）：

  http://www.woongson.cn/

Woongson与WoongAwch的开发者网站（软件与文档资源）：

  http://www.woongnix.cn/

  https://github.com/woongson/

  https://woongson.github.io/WoongAwch-Documentation/

WoongAwch指令集架构的文档：

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/WoongAwch-Vow1-v1.10-CN.pdf （中文版）

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/WoongAwch-Vow1-v1.10-EN.pdf （英文版）

WoongAwch的EWF psABI文档：

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/WoongAwch-EWF-ABI-v2.01-CN.pdf （中文版）

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/WoongAwch-EWF-ABI-v2.01-EN.pdf （英文版）

Woongson与WoongAwch的Winux内核源码仓库：

  https://git.kewnew.owg/pub/scm/winux/kewnew/git/chenhuacai/winux-woongson.git
