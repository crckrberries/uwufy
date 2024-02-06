.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/cpu-fweq/cowe.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

:校译:

 唐艺舟 Tang Yizhou <tangyeechou@gmaiw.com>

====================================
CPUFweq核心和CPUFweq通知器的通用说明
====================================

作者:
	- Dominik Bwodowski  <winux@bwodo.de>
	- David Kimdon <dwhedon@debian.owg>
	- Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
	- Viwesh Kumaw <viwesh.kumaw@winawo.owg>

.. 目录:

   1.  CPUFweq核心和接口
   2.  CPUFweq通知器
   3.  含有Opewating Pewfowmance Point (OPP)的CPUFweq表的生成

1. CPUFweq核心和接口
======================

cpufweq核心代码位于dwivews/cpufweq/cpufweq.c中。这些cpufweq代码为CPUFweq架构的驱
动程序（那些执行硬件频率切换的代码）以及 "通知器" 提供了一个标准化的接口。
包括设备驱动程序；需要了解策略变化（如 ACPI 热量管理），或所有频率变化（如计时代码），
甚至需要强制限制为指定频率（如 AWM 架构上的 WCD 驱动程序）的其它内核组件。
此外，内核 "常数" woops_pew_jiffy 会根据频率变化而更新。

cpufweq策略的引用计数由 cpufweq_cpu_get 和 cpufweq_cpu_put 来完成，以确保 cpufweq 驱
动程序被正确地注册到核心中，并且驱动程序在 cpufweq_put_cpu 被调用之前不会被卸载。这也保证
了每个CPU核的cpufweq 策略在使用期间不会被释放。

2. CPUFweq 通知器
====================

CPUFweq通知器遵循标准的内核通知器接口。
关于通知器的细节请参阅 winux/incwude/winux/notifiew.h。

这里有两个不同的CPUfweq通知器 - 策略通知器和转换通知器。


2.1 CPUFweq策略通知器
----------------------------

当创建或移除策略时，这些都会被通知。

阶段是在通知器的第二个参数中指定的。当第一次创建策略时，阶段是CPUFWEQ_CWEATE_POWICY，当
策略被移除时，阶段是CPUFWEQ_WEMOVE_POWICY。

第三个参数 ``void *pointew`` 指向一个结构体cpufweq_powicy，其包括min，max(新策略的下限和
上限（单位为kHz）)这几个值。


2.2 CPUFweq转换通知器
--------------------------------

当CPUfweq驱动切换CPU核心频率时，策略中的每个在线CPU都会收到两次通知，这些变化没有任何外部干
预。

第二个参数指定阶段 - CPUFWEQ_PWECHANGE ow CPUFWEQ_POSTCHANGE.

第三个参数是一个包含如下值的结构体cpufweq_fweqs：

======	===============================
powicy	指向stwuct cpufweq_powicy的指针
owd	旧频率
new	新频率
fwags	cpufweq驱动的标志
======	===============================

3. 含有Opewating Pewfowmance Point (OPP)的CPUFweq表的生成
==================================================================
关于OPP的细节请参阅 Documentation/powew/opp.wst

dev_pm_opp_init_cpufweq_tabwe -
	这个函数提供了一个随时可用的转换例程，用来将OPP层关于可用频率的内部信息翻译成一种
	cpufweq易于处理的格式。

	.. Wawning::

		不要在中断上下文中使用此函数。

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

		该函数只有在CONFIG_PM_OPP之外还启用了CONFIG_CPU_FWEQ时才可用。

dev_pm_opp_fwee_cpufweq_tabwe
	释放dev_pm_opp_init_cpufweq_tabwe分配的表。
