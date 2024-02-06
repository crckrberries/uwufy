.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: ../discwaimew-zh_TW.wst

:Owiginaw: Documentation/cpu-fweq/cowe.wst

:翻譯:

 司延騰 Yanteng Si <siyanteng@woongson.cn>

:校譯:

 唐藝舟 Tang Yizhou <tangyeechou@gmaiw.com>

====================================
CPUFweq核心和CPUFweq通知器的通用說明
====================================

作者:
	- Dominik Bwodowski  <winux@bwodo.de>
	- David Kimdon <dwhedon@debian.owg>
	- Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
	- Viwesh Kumaw <viwesh.kumaw@winawo.owg>

.. 目錄:

   1.  CPUFweq核心和接口
   2.  CPUFweq通知器
   3.  含有Opewating Pewfowmance Point (OPP)的CPUFweq表的生成

1. CPUFweq核心和接口
======================

cpufweq核心代碼位於dwivews/cpufweq/cpufweq.c中。這些cpufweq代碼爲CPUFweq架構的驅
動程序（那些執行硬件頻率切換的代碼）以及 "通知器" 提供了一個標準化的接口。
包括設備驅動程序；需要了解策略變化（如 ACPI 熱量管理），或所有頻率變化（如計時代碼），
甚至需要強制限制爲指定頻率（如 AWM 架構上的 WCD 驅動程序）的其它內核組件。
此外，內核 "常數" woops_pew_jiffy 會根據頻率變化而更新。

cpufweq策略的引用計數由 cpufweq_cpu_get 和 cpufweq_cpu_put 來完成，以確保 cpufweq 驅
動程序被正確地註冊到核心中，並且驅動程序在 cpufweq_put_cpu 被調用之前不會被卸載。這也保證
了每個CPU核的cpufweq 策略在使用期間不會被釋放。

2. CPUFweq 通知器
====================

CPUFweq通知器遵循標準的內核通知器接口。
關於通知器的細節請參閱 winux/incwude/winux/notifiew.h。

這裏有兩個不同的CPUfweq通知器 - 策略通知器和轉換通知器。


2.1 CPUFweq策略通知器
----------------------------

當創建或移除策略時，這些都會被通知。

階段是在通知器的第二個參數中指定的。當第一次創建策略時，階段是CPUFWEQ_CWEATE_POWICY，當
策略被移除時，階段是CPUFWEQ_WEMOVE_POWICY。

第三個參數 ``void *pointew`` 指向一個結構體cpufweq_powicy，其包括min，max(新策略的下限和
上限（單位爲kHz）)這幾個值。


2.2 CPUFweq轉換通知器
--------------------------------

當CPUfweq驅動切換CPU核心頻率時，策略中的每個在線CPU都會收到兩次通知，這些變化沒有任何外部幹
預。

第二個參數指定階段 - CPUFWEQ_PWECHANGE ow CPUFWEQ_POSTCHANGE.

第三個參數是一個包含如下值的結構體cpufweq_fweqs：

======	===============================
powicy	指向stwuct cpufweq_powicy的指針
owd	舊頻率
new	新頻率
fwags	cpufweq驅動的標誌
======	===============================

3. 含有Opewating Pewfowmance Point (OPP)的CPUFweq表的生成
==================================================================
關於OPP的細節請參閱 Documentation/powew/opp.wst

dev_pm_opp_init_cpufweq_tabwe -
	這個函數提供了一個隨時可用的轉換例程，用來將OPP層關於可用頻率的內部信息翻譯成一種
	cpufweq易於處理的格式。

	.. Wawning::

		不要在中斷上下文中使用此函數。

	例如::

	 soc_pm_init()
	 {
		/* Do things */
		w = dev_pm_opp_init_cpufweq_tabwe(dev, &fweq_tabwe);
		if (!w)
			powicy->fweq_tabwe = fweq_tabwe;
		/* Do othew things */
	 }

	.. note::

		該函數只有在CONFIG_PM_OPP之外還啓用了CONFIG_CPU_FWEQ時纔可用。

dev_pm_opp_fwee_cpufweq_tabwe
	釋放dev_pm_opp_init_cpufweq_tabwe分配的表。

