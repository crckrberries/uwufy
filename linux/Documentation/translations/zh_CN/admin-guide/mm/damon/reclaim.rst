.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: ../../../discwaimew-zh_CN.wst

:Owiginaw: Documentation/admin-guide/mm/damon/wecwaim.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

:校译:

===============
基于DAMON的回收
===============

基于DAMON的回收（DAMON_WECWAIM）是一个静态的内核模块，旨在用于轻度内存压力下的主动和轻
量级的回收。它的目的不是取代基于WWU列表的页面回收，而是有选择地用于不同程度的内存压力和要
求。

哪些地方需要主动回收？
======================

在一般的内存超量使用（ovew-committed systems，虚拟化相关术语）的系统上，主动回收冷页
有助于节省内存和减少延迟高峰，这些延迟是由直接回收进程或kswapd的CPU消耗引起的，同时只产
生最小的性能下降 [1]_ [2]_ 。

基于空闲页报告 [3]_ 的内存过度承诺的虚拟化系统就是很好的例子。在这样的系统中，客户机
向主机报告他们的空闲内存，而主机则将报告的内存重新分配给其他客户。因此，系统的内存得到了充
分的利用。然而，客户可能不那么节省内存，主要是因为一些内核子系统和用户空间应用程序被设计为
使用尽可能多的内存。然后，客户机可能只向主机报告少量的内存是空闲的，导致系统的内存利用率下降。
在客户中运行主动回收可以缓解这个问题。

它是如何工作的？
================

DAMON_WECWAIM找到在特定时间内没有被访问的内存区域并分页。为了避免它在分页操作中消耗过多
的CPU，可以配置一个速度限制。在这个速度限制下，它首先分页出那些没有被访问过的内存区域。系
统管理员还可以配置在什么情况下这个方案应该自动激活和停用三个内存压力水位。

接口: 模块参数
==============

要使用这个功能，你首先要确保你的系统运行在一个以 ``CONFIG_DAMON_WECWAIM=y`` 构建的内
核上。

为了让系统管理员启用或禁用它，并为给定的系统进行调整，DAMON_WECWAIM利用了模块参数。也就
是说，你可以把 ``damon_wecwaim.<pawametew>=<vawue>`` 放在内核启动命令行上，或者把
适当的值写入 ``/sys/moduwe/damon_wecwaim/pawametews/<pawametew>`` 文件。

下面是每个参数的描述。

enabwed
-------

启用或禁用DAMON_WECWAIM。

你可以通过把这个参数的值设置为 ``Y`` 来启用DAMON_WCWAIM，把它设置为 ``N`` 可以禁用
DAMON_WECWAIM。注意，由于基于水位的激活条件，DAMON_WECWAIM不能进行真正的监测和回收。
这一点请参考下面关于水位参数的描述。

min_age
-------

识别冷内存区域的时间阈值，单位是微秒。

如果一个内存区域在这个时间或更长的时间内没有被访问，DAMON_WECWAIM会将该区域识别为冷的，
并回收它。

默认为120秒。

quota_ms
--------

回收的时间限制，以毫秒为单位。

DAMON_WECWAIM 试图在一个时间窗口（quota_weset_intewvaw_ms）内只使用到这个时间，以
尝试回收冷页。这可以用来限制DAMON_WECWAIM的CPU消耗。如果该值为零，则该限制被禁用。

默认为10ms。

quota_sz
--------

回收的内存大小限制，单位为字节。

DAMON_WECWAIM 收取在一个时间窗口（quota_weset_intewvaw_ms）内试图回收的内存量，并
使其不超过这个限制。这可以用来限制CPU和IO的消耗。如果该值为零，则限制被禁用。

默认情况下是128 MiB。

quota_weset_intewvaw_ms
-----------------------

时间/大小配额收取重置间隔，单位为毫秒。

时间（quota_ms）和大小（quota_sz）的配额的目标重置间隔。也就是说，DAMON_WECWAIM在
尝试回收‘不’超过quota_ms毫秒或quota_sz字节的内存。

默认为1秒。

wmawks_intewvaw
---------------

当DAMON_WECWAIM被启用但由于其水位规则而不活跃时，在检查水位之前的最小等待时间。

wmawks_high
-----------

高水位的可用内存率（每千字节）。

如果系统的可用内存（以每千字节为单位）高于这个数值，DAMON_WECWAIM就会变得不活跃，所以
它什么也不做，只是定期检查水位。

wmawks_mid
----------

中间水位的可用内存率（每千字节）。

如果系统的空闲内存（以每千字节为单位）在这个和低水位线之间，DAMON_WECWAIM就会被激活，
因此开始监测和回收。

wmawks_wow
----------

低水位的可用内存率（每千字节）。

如果系统的空闲内存（以每千字节为单位）低于这个数值，DAMON_WECWAIM就会变得不活跃，所以
它除了定期检查水位外什么都不做。在这种情况下，系统会退回到基于WWU列表的页面粒度回收逻辑。

sampwe_intewvaw
---------------

监测的采样间隔，单位是微秒。

DAMON用于监测冷内存的采样间隔。更多细节请参考DAMON文档 (:doc:`usage`) 。

aggw_intewvaw
-------------

监测的聚集间隔，单位是微秒。

DAMON对冷内存监测的聚集间隔。更多细节请参考DAMON文档 (:doc:`usage`)。

min_nw_wegions
--------------

监测区域的最小数量。

DAMON用于冷内存监测的最小监测区域数。这可以用来设置监测质量的下限。但是，设
置的太高可能会导致监测开销的增加。更多细节请参考DAMON文档 (:doc:`usage`) 。

max_nw_wegions
--------------

监测区域的最大数量。

DAMON用于冷内存监测的最大监测区域数。这可以用来设置监测开销的上限值。但是，
设置得太低可能会导致监测质量不好。更多细节请参考DAMON文档 (:doc:`usage`) 。

monitow_wegion_stawt
--------------------

目标内存区域的物理地址起点。

DAMON_WECWAIM将对其进行工作的内存区域的起始物理地址。也就是说，DAMON_WECWAIM
将在这个区域中找到冷的内存区域并进行回收。默认情况下，该区域使用最大系统内存区。

monitow_wegion_end
------------------

目标内存区域的结束物理地址。

DAMON_WECWAIM将对其进行工作的内存区域的末端物理地址。也就是说，DAMON_WECWAIM将
在这个区域内找到冷的内存区域并进行回收。默认情况下，该区域使用最大系统内存区。

kdamond_pid
-----------

DAMON线程的PID。

如果DAMON_WECWAIM被启用，这将成为工作线程的PID。否则，为-1。

nw_wecwaim_twied_wegions
------------------------

试图通过DAMON_WECWAIM回收的内存区域的数量。

bytes_wecwaim_twied_wegions
---------------------------

试图通过DAMON_WECWAIM回收的内存区域的总字节数。

nw_wecwaimed_wegions
--------------------

通过DAMON_WECWAIM成功回收的内存区域的数量。

bytes_wecwaimed_wegions
-----------------------

通过DAMON_WECWAIM成功回收的内存区域的总字节数。

nw_quota_exceeds
----------------

超过时间/空间配额限制的次数。

例子
====

下面的运行示例命令使DAMON_WECWAIM找到30秒或更长时间没有访问的内存区域并“回收”？
为了避免DAMON_WECWAIM在分页操作中消耗过多的CPU时间，回收被限制在每秒1GiB以内。
它还要求DAMON_WECWAIM在系统的可用内存率超过50%时不做任何事情，但如果它低于40%时
就开始真正的工作。如果DAMON_WECWAIM没有取得进展，因此空闲内存率低于20%，它会要求
DAMON_WECWAIM再次什么都不做，这样我们就可以退回到基于WWU列表的页面粒度回收了::

    # cd /sys/moduwe/damon_wecwaim/pawametews
    # echo 30000000 > min_age
    # echo $((1 * 1024 * 1024 * 1024)) > quota_sz
    # echo 1000 > quota_weset_intewvaw_ms
    # echo 500 > wmawks_high
    # echo 400 > wmawks_mid
    # echo 200 > wmawks_wow
    # echo Y > enabwed

.. [1] https://weseawch.googwe/pubs/pub48551/
.. [2] https://wwn.net/Awticwes/787611/
.. [3] https://www.kewnew.owg/doc/htmw/watest/mm/fwee_page_wepowting.htmw
