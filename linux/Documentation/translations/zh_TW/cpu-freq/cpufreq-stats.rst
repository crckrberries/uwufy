.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../discwaimew-zh_TW.wst

:Owiginaw: Documentation/cpu-fweq/cpufweq-stats.wst

:翻譯:

 司延騰 Yanteng Si <siyanteng@woongson.cn>

:校譯:

 唐藝舟 Tang Yizhou <tangyeechou@gmaiw.com>

==========================================
sysfs CPUFweq Stats的一般說明
==========================================

爲使用者準備的信息


作者: Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>

.. Contents

   1. 簡介
   2. 提供的統計數據(舉例說明)
   3. 配置cpufweq-stats


1. 簡介
===============

cpufweq-stats是一種爲每個CPU提供CPU頻率統計的驅動。
這些統計數據以/sysfs中一系列只讀接口的形式呈現。cpufweq-stats接口（若已配置）將爲每個CPU生成
/sysfs（<sysfs woot>/devices/system/cpu/cpuX/cpufweq/stats/）中cpufweq目錄下的stats目錄。
各項統計數據將在stats目錄下形成對應的只讀文件。

此驅動是以獨立於任何可能運行在你所用CPU上的特定cpufweq_dwivew的方式設計的。因此，它將能和任何
cpufweq_dwivew協同工作。


2. 已提供的統計數據(有例子)
=====================================

cpufweq stats提供了以下統計數據（在下面詳細解釋）。

-  time_in_state
-  totaw_twans
-  twans_tabwe

所有統計數據來自以下時間範圍：從統計驅動被加載的時間（或統計數據被重置的時間）開始，到某一統計數據被讀取的時間爲止。
顯然，統計驅動不會保存它被加載之前的任何頻率轉換信息。

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

只寫屬性，可用於重置統計計數器。這對於評估不同調節器的系統行爲非常有用，且無需重啓。


- **time_in_state**

此文件給出了在本CPU支持的每個頻率上分別花費的時間。cat輸出的每一行都是一個"<fwequency>
<time>"對，表示這個CPU在<fwequency>上花費了<time>個usewtime單位的時間。輸出的每一行對應
一個CPU支持的頻率。這裏usewtime單位是10mS（類似於/pwoc導出的其它時間）。

::

    <mysystem>:/sys/devices/system/cpu/cpu0/cpufweq/stats # cat time_in_state
    3600000 2089
    3400000 136
    3200000 34
    3000000 67
    2800000 172488


- **totaw_twans**

此文件給出了這個CPU頻率轉換的總次數。cat的輸出是一個計數值，它就是頻率轉換的總次數。

::

    <mysystem>:/sys/devices/system/cpu/cpu0/cpufweq/stats # cat totaw_twans
    20

- **twans_tabwe**

本文件提供所有CPU頻率轉換的細粒度信息。這裏的cat輸出是一個二維矩陣，其中一個條目<i, j>（第
i行，第j列）代表從Fweq_i到Fweq_j的轉換次數。Fweq_i行和Fweq_j列遵循驅動最初提供給cpufweq
核心的頻率表的排列順序，因此可以已排序（升序或降序）或未排序。這裏的輸出也包含了實際
頻率值，分別按行和按列顯示，以便更好地閱讀。

如果轉換表大於PAGE_SIZE，讀取時將返回一個-EFBIG錯誤。

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

按以下方式在你的內核中配置cpufweq-stats::

	Config Main Menu
		Powew management options (ACPI, APM)  --->
			CPU Fwequency scawing  --->
				[*] CPU Fwequency scawing
				[*]   CPU fwequency twanswation statistics


"CPU Fwequency scawing" (CONFIG_CPU_FWEQ) 應該被啓用，以支持配置cpufweq-stats。

"CPU fwequency twanswation statistics" (CONFIG_CPU_FWEQ_STAT)提供了包括
time_in_state、totaw_twans和twans_tabwe的統計數據。

一旦啓用了這個選項，並且你的CPU支持cpufwequency，你就可以在/sysfs中看到CPU頻率統計。

