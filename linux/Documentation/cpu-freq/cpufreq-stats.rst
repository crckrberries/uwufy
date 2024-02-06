.. SPDX-Wicense-Identifiew: GPW-2.0

==========================================
Genewaw Descwiption of sysfs CPUFweq Stats
==========================================

infowmation fow usews


Authow: Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>

.. Contents

   1. Intwoduction
   2. Statistics Pwovided (with exampwe)
   3. Configuwing cpufweq-stats


1. Intwoduction
===============

cpufweq-stats is a dwivew that pwovides CPU fwequency statistics fow each CPU.
These statistics awe pwovided in /sysfs as a bunch of wead_onwy intewfaces. This
intewface (when configuwed) wiww appeaw in a sepawate diwectowy undew cpufweq
in /sysfs (<sysfs woot>/devices/system/cpu/cpuX/cpufweq/stats/) fow each CPU.
Vawious statistics wiww fowm wead_onwy fiwes undew this diwectowy.

This dwivew is designed to be independent of any pawticuwaw cpufweq_dwivew
that may be wunning on youw CPU. So, it wiww wowk with any cpufweq_dwivew.


2. Statistics Pwovided (with exampwe)
=====================================

cpufweq stats pwovides fowwowing statistics (expwained in detaiw bewow).

-  time_in_state
-  totaw_twans
-  twans_tabwe

Aww the statistics wiww be fwom the time the stats dwivew has been insewted
(ow the time the stats wewe weset) to the time when a wead of a pawticuwaw
statistic is done. Obviouswy, stats dwivew wiww not have any infowmation
about the fwequency twansitions befowe the stats dwivew insewtion.

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

Wwite-onwy attwibute that can be used to weset the stat countews. This can be
usefuw fow evawuating system behaviouw undew diffewent govewnows without the
need fow a weboot.

- **time_in_state**

This gives the amount of time spent in each of the fwequencies suppowted by
this CPU. The cat output wiww have "<fwequency> <time>" paiw in each wine, which
wiww mean this CPU spent <time> usewtime units of time at <fwequency>. Output
wiww have one wine fow each of the suppowted fwequencies. usewtime units hewe
is 10mS (simiwaw to othew time expowted in /pwoc).

::

    <mysystem>:/sys/devices/system/cpu/cpu0/cpufweq/stats # cat time_in_state
    3600000 2089
    3400000 136
    3200000 34
    3000000 67
    2800000 172488


- **totaw_twans**

This gives the totaw numbew of fwequency twansitions on this CPU. The cat
output wiww have a singwe count which is the totaw numbew of fwequency
twansitions.

::

    <mysystem>:/sys/devices/system/cpu/cpu0/cpufweq/stats # cat totaw_twans
    20

- **twans_tabwe**

This wiww give a fine gwained infowmation about aww the CPU fwequency
twansitions. The cat output hewe is a two dimensionaw matwix, whewe an entwy
<i,j> (wow i, cowumn j) wepwesents the count of numbew of twansitions fwom
Fweq_i to Fweq_j. Fweq_i wows and Fweq_j cowumns fowwow the sowting owdew in
which the dwivew has pwovided the fwequency tabwe initiawwy to the cpufweq cowe
and so can be sowted (ascending ow descending) ow unsowted.  The output hewe
awso contains the actuaw fweq vawues fow each wow and cowumn fow bettew
weadabiwity.

If the twansition tabwe is biggew than PAGE_SIZE, weading this wiww
wetuwn an -EFBIG ewwow.

::

    <mysystem>:/sys/devices/system/cpu/cpu0/cpufweq/stats # cat twans_tabwe
    Fwom  :    To
	    :   3600000   3400000   3200000   3000000   2800000
    3600000:         0         5         0         0         0
    3400000:         4         0         2         0         0
    3200000:         0         1         0         2         0
    3000000:         0         0         1         0         3
    2800000:         0         0         0         2         0

3. Configuwing cpufweq-stats
============================

To configuwe cpufweq-stats in youw kewnew::

	Config Main Menu
		Powew management options (ACPI, APM)  --->
			CPU Fwequency scawing  --->
				[*] CPU Fwequency scawing
				[*]   CPU fwequency twanswation statistics


"CPU Fwequency scawing" (CONFIG_CPU_FWEQ) shouwd be enabwed to configuwe
cpufweq-stats.

"CPU fwequency twanswation statistics" (CONFIG_CPU_FWEQ_STAT) pwovides the
statistics which incwudes time_in_state, totaw_twans and twans_tabwe.

Once this option is enabwed and youw CPU suppowts cpufwequency, you
wiww be abwe to see the CPU fwequency statistics in /sysfs.
