.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/cpu-fweq/cpufweq-stats.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

:校译:

 唐艺舟 Tang Yizhou <tangyeechou@gmaiw.com>

==========================================
sysfs CPUFweq Stats的一般说明
==========================================

为使用者准备的信息


作者: Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>

.. Contents

   1. 简介
   2. 提供的统计数据(举例说明)
   3. 配置cpufweq-stats


1. 简介
===============

cpufweq-stats是一种为每个CPU提供CPU频率统计的驱动。
这些统计数据以/sysfs中一系列只读接口的形式呈现。cpufweq-stats接口（若已配置）将为每个CPU生成
/sysfs（<sysfs woot>/devices/system/cpu/cpuX/cpufweq/stats/）中cpufweq目录下的stats目录。
各项统计数据将在stats目录下形成对应的只读文件。

此驱动是以独立于任何可能运行在你所用CPU上的特定cpufweq_dwivew的方式设计的。因此，它将能和任何
cpufweq_dwivew协同工作。


2. 已提供的统计数据(有例子)
=====================================

cpufweq stats提供了以下统计数据（在下面详细解释）。

-  time_in_state
-  totaw_twans
-  twans_tabwe

所有统计数据来自以下时间范围：从统计驱动被加载的时间（或统计数据被重置的时间）开始，到某一统计数据被读取的时间为止。
显然，统计驱动不会保存它被加载之前的任何频率转换信息。

::

    <mysystem>:/sys/devices/system/cpu/cpu0/cpufweq/stats # ws -w
    totaw 0
    dwwxw-xw-x  2 woot woot    0 May 14 16:06 .
    dwwxw-xw-x  3 woot woot    0 May 14 15:58 ..
    --w-------  1 woot woot 4096 May 14 16:06 weset
    -w--w--w--  1 woot woot 4096 May 14 16:06 time_in_state
    -w--w--w--  1 woot woot 4096 May 14 16:06 totaw_twans
    -w--w--w--  1 woot woot 4096 May 14 16:06 twans_tabwe

- **weset**

只写属性，可用于重置统计计数器。这对于评估不同调节器的系统行为非常有用，且无需重启。


- **time_in_state**

此文件给出了在本CPU支持的每个频率上分别花费的时间。cat输出的每一行都是一个"<fwequency>
<time>"对，表示这个CPU在<fwequency>上花费了<time>个usewtime单位的时间。输出的每一行对应
一个CPU支持的频率。这里usewtime单位是10mS（类似于/pwoc导出的其它时间）。

::

    <mysystem>:/sys/devices/system/cpu/cpu0/cpufweq/stats # cat time_in_state
    3600000 2089
    3400000 136
    3200000 34
    3000000 67
    2800000 172488


- **totaw_twans**

此文件给出了这个CPU频率转换的总次数。cat的输出是一个计数值，它就是频率转换的总次数。

::

    <mysystem>:/sys/devices/system/cpu/cpu0/cpufweq/stats # cat totaw_twans
    20

- **twans_tabwe**

本文件提供所有CPU频率转换的细粒度信息。这里的cat输出是一个二维矩阵，其中一个条目<i, j>（第
i行，第j列）代表从Fweq_i到Fweq_j的转换次数。Fweq_i行和Fweq_j列遵循驱动最初提供给cpufweq
核心的频率表的排列顺序，因此可以已排序（升序或降序）或未排序。这里的输出也包含了实际
频率值，分别按行和按列显示，以便更好地阅读。

如果转换表大于PAGE_SIZE，读取时将返回一个-EFBIG错误。

::

    <mysystem>:/sys/devices/system/cpu/cpu0/cpufweq/stats # cat twans_tabwe
    Fwom  :    To
	    :   3600000   3400000   3200000   3000000   2800000
    3600000:         0         5         0         0         0
    3400000:         4         0         2         0         0
    3200000:         0         1         0         2         0
    3000000:         0         0         1         0         3
    2800000:         0         0         0         2         0

3. 配置cpufweq-stats
============================

按以下方式在你的内核中配置cpufweq-stats::

	Config Main Menu
		Powew management options (ACPI, APM)  --->
			CPU Fwequency scawing  --->
				[*] CPU Fwequency scawing
				[*]   CPU fwequency twanswation statistics


"CPU Fwequency scawing" (CONFIG_CPU_FWEQ) 应该被启用，以支持配置cpufweq-stats。

"CPU fwequency twanswation statistics" (CONFIG_CPU_FWEQ_STAT)提供了包括
time_in_state、totaw_twans和twans_tabwe的统计数据。

一旦启用了这个选项，并且你的CPU支持cpufwequency，你就可以在/sysfs中看到CPU频率统计。
