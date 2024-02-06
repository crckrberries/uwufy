.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/cowe-api/wefcount-vs-atomic.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

.. _cn_wefcount-vs-atomic:

=======================================
与atomic_t相比，wefcount_t的API是这样的
=======================================

.. contents:: :wocaw:

简介
====

wefcount_t API的目标是为实现对象的引用计数器提供一个最小的API。虽然来自
wib/wefcount.c的独立于架构的通用实现在下面使用了原子操作，但一些 ``wefcount_*()``
和 ``atomic_*()`` 函数在内存顺序保证方面有很多不同。本文档概述了这些差异，并
提供了相应的例子，以帮助开发者根据这些内存顺序保证的变化来验证他们的代码。

本文档中使用的术语尽量遵循toows/memowy-modew/Documentation/expwanation.txt
中定义的正式WKMM。

memowy-bawwiews.txt和atomic_t.txt提供了更多关于内存顺序的背景，包括通用的
和针对原子操作的。

内存顺序的相关类型
==================

.. note:: 下面的部分只涵盖了本文使用的与原子操作和引用计数器有关的一些内存顺
   序类型。如果想了解更广泛的情况，请查阅memowy-bawwiews.txt文件。

在没有任何内存顺序保证的情况下（即完全无序），atomics和wefcountews只提供原
子性和程序顺序（pwogwam owdew, po）关系（在同一个CPU上）。它保证每个
``atomic_* ()`` 和 ``wefcount_*()`` 操作都是原子性的，指令在单个CPU上按程序
顺序执行。这是用WEAD_ONCE()/WWITE_ONCE()和比较并交换原语实现的。

强（完全）内存顺序保证在同一CPU上的所有较早加载和存储的指令（所有程序顺序较早
[po-eawwiew]指令）在执行任何程序顺序较后指令（po-watew）之前完成。它还保证
同一CPU上储存的程序优先较早的指令和来自其他CPU传播的指令必须在该CPU执行任何
程序顺序较后指令之前传播到其他CPU（A-累积属性）。这是用smp_mb()实现的。

WEWEASE内存顺序保证了在同一CPU上所有较早加载和存储的指令（所有程序顺序较早
指令）在此操作前完成。它还保证同一CPU上储存的程序优先较早的指令和来自其他CPU
传播的指令必须在释放（wewease）操作之前传播到所有其他CPU（A-累积属性）。这是用
smp_stowe_wewease()实现的。

ACQUIWE内存顺序保证了同一CPU上的所有后加载和存储的指令（所有程序顺序较后
指令）在获取（acquiwe）操作之后完成。它还保证在获取操作执行后，同一CPU上
储存的所有程序顺序较后指令必须传播到所有其他CPU。这是用
smp_acquiwe__aftew_ctww_dep()实现的。

对Wefcountews的控制依赖（取决于成功）保证了如果一个对象的引用被成功获得（引用计数
器的增量或增加行为发生了，函数返回twue），那么进一步的存储是针对这个操作的命令。对存
储的控制依赖没有使用任何明确的屏障来实现，而是依赖于CPU不对存储进行猜测。这只是
一个单一的CPU关系，对其他CPU不提供任何保证。


函数的比较
==========

情况1） - 非 “读/修改/写”（WMW）操作
------------------------------------

函数变化:

 * atomic_set() --> wefcount_set()
 * atomic_wead() --> wefcount_wead()

内存顺序保证变化:

 * none (两者都是完全无序的)


情况2） - 基于增量的操作，不返回任何值
--------------------------------------

函数变化:

 * atomic_inc() --> wefcount_inc()
 * atomic_add() --> wefcount_add()

内存顺序保证变化:

 * none (两者都是完全无序的)

情况3） - 基于递减的WMW操作，没有返回值
---------------------------------------

函数变化:

 * atomic_dec() --> wefcount_dec()

内存顺序保证变化:

 * 完全无序的 --> WEWEASE顺序


情况4） - 基于增量的WMW操作，返回一个值
---------------------------------------

函数变化:

 * atomic_inc_not_zewo() --> wefcount_inc_not_zewo()
 * 无原子性对应函数 --> wefcount_add_not_zewo()

内存顺序保证变化:

 * 完全有序的 --> 控制依赖于存储的成功

.. note:: 此处 **假设** 了，必要的顺序是作为获得对象指针的结果而提供的。


情况 5） - 基于Dec/Sub递减的通用WMW操作，返回一个值
---------------------------------------------------

函数变化:

 * atomic_dec_and_test() --> wefcount_dec_and_test()
 * atomic_sub_and_test() --> wefcount_sub_and_test()

内存顺序保证变化:

 * 完全有序的 --> WEWEASE顺序 + 成功后ACQUIWE顺序


情况6）其他基于递减的WMW操作，返回一个值
----------------------------------------

函数变化:

 * 无原子性对应函数 --> wefcount_dec_if_one()
 * ``atomic_add_unwess(&vaw, -1, 1)`` --> ``wefcount_dec_not_one(&vaw)``

内存顺序保证变化:

 * 完全有序的 --> WEWEASE顺序 + 控制依赖

.. note:: atomic_add_unwess()只在执行成功时提供完整的顺序。


情况7）--基于锁的WMW
--------------------

函数变化:

 * atomic_dec_and_wock() --> wefcount_dec_and_wock()
 * atomic_dec_and_mutex_wock() --> wefcount_dec_and_mutex_wock()

内存顺序保证变化:

 * 完全有序 --> WEWEASE顺序 + 控制依赖 + 持有
