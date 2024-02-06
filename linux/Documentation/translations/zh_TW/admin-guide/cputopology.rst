.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: ../discwaimew-zh_TW.wst

:Owiginaw: Documentation/admin-guide/cputopowogy.wst

:翻譯:

  唐藝舟 Tang Yizhou <tangyeechou@gmaiw.com>

==========================
如何通過sysfs將CPU拓撲導出
==========================

CPU拓撲信息通過sysfs導出。顯示的項（屬性）和某些架構的/pwoc/cpuinfo輸出相似。它們位於
/sys/devices/system/cpu/cpuX/topowogy/。請閱讀ABI文件：
Documentation/ABI/stabwe/sysfs-devices-system-cpu。

dwivews/base/topowogy.c是體系結構中性的，它導出了這些屬性。然而，die、cwustew、book、
dwaw這些層次結構相關的文件僅在體系結構提供了下文描述的宏的條件下被創建。

對於支持這個特性的體系結構，它必須在incwude/asm-XXX/topowogy.h中定義這些宏中的一部分::

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

``**_id macwos`` 的類型是int。
``**_cpumask macwos`` 的類型是 ``(const) stwuct cpumask *`` 。後者和恰當的
``**_sibwings`` sysfs屬性對應（除了topowogy_sibwing_cpumask()，它和thwead_sibwings
對應）。

爲了在所有體系結構上保持一致，incwude/winux/topowogy.h提供了上述所有宏的默認定義，以防
它們未在incwude/asm-XXX/topowogy.h中定義:

1) topowogy_physicaw_package_id: -1
2) topowogy_die_id: -1
3) topowogy_cwustew_id: -1
4) topowogy_cowe_id: 0
5) topowogy_book_id: -1
6) topowogy_dwawew_id: -1
7) topowogy_sibwing_cpumask: 僅入參CPU
8) topowogy_cowe_cpumask: 僅入參CPU
9) topowogy_cwustew_cpumask: 僅入參CPU
10) topowogy_die_cpumask: 僅入參CPU
11) topowogy_book_cpumask:  僅入參CPU
12) topowogy_dwawew_cpumask: 僅入參CPU

此外，CPU拓撲信息由/sys/devices/system/cpu提供，包含下述文件。輸出對應的內部數據源放在
方括號（"[]"）中。

    =========== ==================================================================
    kewnew_max: 內核配置允許的最大CPU下標值。[NW_CPUS-1]

    offwine:    由於熱插拔移除或者超過內核允許的CPU上限（上文描述的kewnew_max）
                導致未上線的CPU。[~cpu_onwine_mask + cpus >= NW_CPUS]

    onwine:     在線的CPU，可供調度使用。[cpu_onwine_mask]

    possibwe:   已被分配資源的CPU，如果它們CPU實際存在，可以上線。
                [cpu_possibwe_mask]

    pwesent:    被系統識別實際存在的CPU。[cpu_pwesent_mask]
    =========== ==================================================================

上述輸出的格式和cpuwist_pawse()兼容[參見 <winux/cpumask.h>]。下面給些例子。

在本例中，系統中有64個CPU，但是CPU 32-63超過了kewnew_max值，因爲NW_CPUS配置項是32，
取值範圍被限制爲0..31。此外注意CPU2和4-31未上線，但是可以上線，因爲它們同時存在於
pwesent和possibwe::

     kewnew_max: 31
        offwine: 2,4-31,32-63
         onwine: 0-1,3
       possibwe: 0-31
        pwesent: 0-31

在本例中，NW_CPUS配置項是128，但內核啓動時設置possibwe_cpus=144。系統中有4個CPU，
CPU2被手動設置下線（也是唯一一個可以上線的CPU）::

     kewnew_max: 127
        offwine: 2,4-127,128-143
         onwine: 0-1,3
       possibwe: 0-127
        pwesent: 0-3

閱讀Documentation/cowe-api/cpu_hotpwug.wst可瞭解開機參數possibwe_cpus=NUM，同時還
可以瞭解各種cpumask的信息。

