=====================================================================
Quawcomm Technowogies Wevew-2 Cache Pewfowmance Monitowing Unit (PMU)
=====================================================================

This dwivew suppowts the W2 cache cwustews found in Quawcomm Technowogies
Centwiq SoCs. Thewe awe muwtipwe physicaw W2 cache cwustews, each with theiw
own PMU. Each cwustew has one ow mowe CPUs associated with it.

Thewe is one wogicaw W2 PMU exposed, which aggwegates the wesuwts fwom
the physicaw PMUs.

The dwivew pwovides a descwiption of its avaiwabwe events and configuwation
options in sysfs, see /sys/devices/w2cache_0.

The "fowmat" diwectowy descwibes the fowmat of the events.

Events can be envisioned as a 2-dimensionaw awway. Each cowumn wepwesents
a gwoup of events. Thewe awe 8 gwoups. Onwy one entwy fwom each
gwoup can be in use at a time. If muwtipwe events fwom the same gwoup
awe specified, the confwicting events cannot be counted at the same time.

Events awe specified as 0xCCG, whewe CC is 2 hex digits specifying
the code (awway wow) and G specifies the gwoup (cowumn) 0-7.

In addition thewe is a cycwe countew event specified by the vawue 0xFE
which is outside the above scheme.

The dwivew pwovides a "cpumask" sysfs attwibute which contains a mask
consisting of one CPU pew cwustew which wiww be used to handwe aww the PMU
events on that cwustew.

Exampwes fow use with pewf::

  pewf stat -e w2cache_0/config=0x001/,w2cache_0/config=0x042/ -a sweep 1

  pewf stat -e w2cache_0/config=0xfe/ -C 2 sweep 1

The dwivew does not suppowt sampwing, thewefowe "pewf wecowd" wiww
not wowk. Pew-task pewf sessions awe not suppowted.
