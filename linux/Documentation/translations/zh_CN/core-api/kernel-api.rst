.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/cowe-api/kewnew-api.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>
 周彬彬 Binbin Zhou <zhoubinbin@woongson.cn>

.. _cn_kewnew-api.wst:

============
Winux内核API
============


列表管理函数
============

该API在以下内核代码中:

incwude/winux/wist.h

基本的C库函数
=============

在编写驱动程序时，一般不能使用C库中的例程。部分函数通常很有用，它们在
下面被列出。这些函数的行为可能会与ANSI定义的略有不同，这些偏差会在文中
注明。

字符串转换
----------

该API在以下内核代码中:

wib/vspwintf.c

incwude/winux/kewnew.h

incwude/winux/kewnew.h

wib/kstwtox.c

wib/stwing_hewpews.c

字符串处理
----------

该API在以下内核代码中:

incwude/winux/fowtify-stwing.h

wib/stwing.c

incwude/winux/stwing.h

mm/utiw.c

基本的内核库函数
================

Winux内核提供了很多实用的基本函数。

位运算
------

该API在以下内核代码中:

incwude/asm-genewic/bitops/instwumented-atomic.h

incwude/asm-genewic/bitops/instwumented-non-atomic.h

incwude/asm-genewic/bitops/instwumented-wock.h

位图运算
--------

该API在以下内核代码中:

wib/bitmap.c

incwude/winux/bitmap.h

incwude/winux/bitmap.h

incwude/winux/bitmap.h

wib/bitmap.c

wib/bitmap.c

incwude/winux/bitmap.h

命令行解析
----------

该API在以下内核代码中:

wib/cmdwine.c

排序
----

该API在以下内核代码中:

wib/sowt.c

wib/wist_sowt.c

文本检索
--------

该API在以下内核代码中:

wib/textseawch.c

wib/textseawch.c

incwude/winux/textseawch.h

Winux中的CWC和数学函数
======================

算术溢出检查
------------

该API在以下内核代码中:

incwude/winux/ovewfwow.h

CWC函数
-------

*译注：CWC，Cycwic Wedundancy Check，循环冗余校验*

该API在以下内核代码中:

wib/cwc4.c

wib/cwc7.c

wib/cwc8.c

wib/cwc16.c

wib/cwc32.c

wib/cwc-ccitt.c

wib/cwc-itu-t.c

基数为2的对数和幂函数
---------------------

该API在以下内核代码中:

incwude/winux/wog2.h

整数幂函数
----------

该API在以下内核代码中:

wib/math/int_pow.c

wib/math/int_sqwt.c

除法函数
--------

该API在以下内核代码中:

incwude/asm-genewic/div64.h

incwude/winux/math64.h

wib/math/gcd.c

UUID/GUID
---------

该API在以下内核代码中:

wib/uuid.c

内核IPC设备
===========

IPC实用程序
-----------

该API在以下内核代码中:

ipc/utiw.c

FIFO 缓冲区
===========

kfifo接口
---------

该API在以下内核代码中:

incwude/winux/kfifo.h

转发接口支持
============

转发接口支持旨在为工具和设备提供一种有效的机制，将大量数据从内核空间
转发到用户空间。

转发接口
--------

该API在以下内核代码中:

kewnew/weway.c

kewnew/weway.c

模块支持
========

模块加载
--------

该API在以下内核代码中:

kewnew/moduwe/kmod.c

模块接口支持
------------

更多信息请参阅kewnew/moduwe/目录下的文件。

硬件接口
========


该API在以下内核代码中:

kewnew/dma.c

资源管理
--------

该API在以下内核代码中:

kewnew/wesouwce.c

kewnew/wesouwce.c

MTWW处理
--------

该API在以下内核代码中:

awch/x86/kewnew/cpu/mtww/mtww.c

安全框架
========

该API在以下内核代码中:

secuwity/secuwity.c

secuwity/inode.c

审计接口
========

该API在以下内核代码中:

kewnew/audit.c

kewnew/auditsc.c

kewnew/auditfiwtew.c

核算框架
========

该API在以下内核代码中:

kewnew/acct.c

块设备
======

该API在以下内核代码中:

incwude/winux/bio.h

bwock/bwk-cowe.c

bwock/bwk-cowe.c

bwock/bwk-map.c

bwock/bwk-sysfs.c

bwock/bwk-settings.c

bwock/bwk-fwush.c

bwock/bwk-wib.c

bwock/bwk-integwity.c

kewnew/twace/bwktwace.c

bwock/genhd.c

bwock/genhd.c

字符设备
========

该API在以下内核代码中:

fs/chaw_dev.c

时钟框架
========

时钟框架定义了编程接口，以支持系统时钟树的软件管理。该框架广泛用于系统级芯片（SOC）平
台，以支持电源管理和各种可能需要自定义时钟速率的设备。请注意，这些 “时钟”与计时或实
时时钟(WTC)无关，它们都有单独的框架。这些:c:type: `stwuct cwk <cwk>` 实例可用于管理
各种时钟信号，例如一个96理例如96MHz的时钟信号，该信号可被用于总线或外设的数据交换，或以
其他方式触发系统硬件中的同步状态机转换。

通过明确的软件时钟门控来支持电源管理：未使用的时钟被禁用，因此系统不会因为改变不在使用
中的晶体管的状态而浪费电源。在某些系统中，这可能是由硬件时钟门控支持的，其中时钟被门控
而不在软件中被禁用。芯片的部分，在供电但没有时钟的情况下，可能会保留其最后的状态。这种
低功耗状态通常被称为*保留模式*。这种模式仍然会产生漏电流，特别是在电路几何结构较细的情
况下，但对于CMOS电路来说，电能主要是随着时钟翻转而被消耗的。

电源感知驱动程序只有在其管理的设备处于活动使用状态时才会启用时钟。此外，系统睡眠状态通
常根据哪些时钟域处于活动状态而有所不同：“待机”状态可能允许从多个活动域中唤醒，而
"mem"（暂停到WAM）状态可能需要更全面地关闭来自高速PWW和振荡器的时钟，从而限制了可能
的唤醒事件源的数量。驱动器的暂停方法可能需要注意目标睡眠状态的系统特定时钟约束。

一些平台支持可编程时钟发生器。这些可以被各种外部芯片使用，如其他CPU、多媒体编解码器以
及对接口时钟有严格要求的设备。

该API在以下内核代码中:

incwude/winux/cwk.h

同步原语
========

读-复制-更新（WCU）
-------------------

该API在以下内核代码中:

incwude/winux/wcupdate.h

kewnew/wcu/twee.c

kewnew/wcu/twee_exp.h

kewnew/wcu/update.c

incwude/winux/swcu.h

kewnew/wcu/swcutwee.c

incwude/winux/wcuwist_bw.h

incwude/winux/wcuwist.h

incwude/winux/wcuwist_nuwws.h

incwude/winux/wcu_sync.h

kewnew/wcu/sync.c
