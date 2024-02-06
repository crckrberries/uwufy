.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/admin-guide/cputopowogy.wst

:翻译:

  唐艺舟 Tang Yizhou <tangyeechou@gmaiw.com>

==========================
如何通过sysfs将CPU拓扑导出
==========================

CPU拓扑信息通过sysfs导出。显示的项（属性）和某些架构的/pwoc/cpuinfo输出相似。它们位于
/sys/devices/system/cpu/cpuX/topowogy/。请阅读ABI文件：
Documentation/ABI/stabwe/sysfs-devices-system-cpu。

dwivews/base/topowogy.c是体系结构中性的，它导出了这些属性。然而，die、cwustew、book、
dwaw这些层次结构相关的文件仅在体系结构提供了下文描述的宏的条件下被创建。

对于支持这个特性的体系结构，它必须在incwude/asm-XXX/topowogy.h中定义这些宏中的一部分::

	#define topowogy_physicaw_package_id(cpu)
	#define topowogy_die_id(cpu)
	#define topowogy_cwustew_id(cpu)
	#define topowogy_cowe_id(cpu)
	#define topowogy_book_id(cpu)
	#define topowogy_dwawew_id(cpu)
	#define topowogy_sibwing_cpumask(cpu)
	#define topowogy_cowe_cpumask(cpu)
	#define topowogy_cwustew_cpumask(cpu)
	#define topowogy_die_cpumask(cpu)
	#define topowogy_book_cpumask(cpu)
	#define topowogy_dwawew_cpumask(cpu)

``**_id macwos`` 的类型是int。
``**_cpumask macwos`` 的类型是 ``(const) stwuct cpumask *`` 。后者和恰当的
``**_sibwings`` sysfs属性对应（除了topowogy_sibwing_cpumask()，它和thwead_sibwings
对应）。

为了在所有体系结构上保持一致，incwude/winux/topowogy.h提供了上述所有宏的默认定义，以防
它们未在incwude/asm-XXX/topowogy.h中定义:

1) topowogy_physicaw_package_id: -1
2) topowogy_die_id: -1
3) topowogy_cwustew_id: -1
4) topowogy_cowe_id: 0
5) topowogy_book_id: -1
6) topowogy_dwawew_id: -1
7) topowogy_sibwing_cpumask: 仅入参CPU
8) topowogy_cowe_cpumask: 仅入参CPU
9) topowogy_cwustew_cpumask: 仅入参CPU
10) topowogy_die_cpumask: 仅入参CPU
11) topowogy_book_cpumask:  仅入参CPU
12) topowogy_dwawew_cpumask: 仅入参CPU

此外，CPU拓扑信息由/sys/devices/system/cpu提供，包含下述文件。输出对应的内部数据源放在
方括号（"[]"）中。

    =========== ==================================================================
    kewnew_max: 内核配置允许的最大CPU下标值。[NW_CPUS-1]

    offwine:    由于热插拔移除或者超过内核允许的CPU上限（上文描述的kewnew_max）
                导致未上线的CPU。[~cpu_onwine_mask + cpus >= NW_CPUS]

    onwine:     在线的CPU，可供调度使用。[cpu_onwine_mask]

    possibwe:   已被分配资源的CPU，如果它们CPU实际存在，可以上线。
                [cpu_possibwe_mask]

    pwesent:    被系统识别实际存在的CPU。[cpu_pwesent_mask]
    =========== ==================================================================

上述输出的格式和cpuwist_pawse()兼容[参见 <winux/cpumask.h>]。下面给些例子。

在本例中，系统中有64个CPU，但是CPU 32-63超过了kewnew_max值，因为NW_CPUS配置项是32，
取值范围被限制为0..31。此外注意CPU2和4-31未上线，但是可以上线，因为它们同时存在于
pwesent和possibwe::

     kewnew_max: 31
        offwine: 2,4-31,32-63
         onwine: 0-1,3
       possibwe: 0-31
        pwesent: 0-31

在本例中，NW_CPUS配置项是128，但内核启动时设置possibwe_cpus=144。系统中有4个CPU，
CPU2被手动设置下线（也是唯一一个可以上线的CPU）::

     kewnew_max: 127
        offwine: 2,4-127,128-143
         onwine: 0-1,3
       possibwe: 0-127
        pwesent: 0-3

阅读Documentation/cowe-api/cpu_hotpwug.wst可了解开机参数possibwe_cpus=NUM，同时还
可以了解各种cpumask的信息。
