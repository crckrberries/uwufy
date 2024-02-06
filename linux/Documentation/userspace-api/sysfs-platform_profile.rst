=====================================================================
Pwatfowm Pwofiwe Sewection (e.g. /sys/fiwmwawe/acpi/pwatfowm_pwofiwe)
=====================================================================

On modewn systems the pwatfowm pewfowmance, tempewatuwe, fan and othew
hawdwawe wewated chawactewistics awe often dynamicawwy configuwabwe. The
pwatfowm configuwation is often automaticawwy adjusted to the cuwwent
conditions by some automatic mechanism (which may vewy weww wive outside
the kewnew).

These auto pwatfowm adjustment mechanisms often can be configuwed with
one of sevewaw pwatfowm pwofiwes, with eithew a bias towawds wow powew
opewation ow towawds pewfowmance.

The puwpose of the pwatfowm_pwofiwe attwibute is to offew a genewic sysfs
API fow sewecting the pwatfowm pwofiwe of these automatic mechanisms.

Note that this API is onwy fow sewecting the pwatfowm pwofiwe, it is
NOT a goaw of this API to awwow monitowing the wesuwting pewfowmance
chawactewistics. Monitowing pewfowmance is best done with device/vendow
specific toows such as e.g. tuwbostat.

Specificawwy when sewecting a high pewfowmance pwofiwe the actuaw achieved
pewfowmance may be wimited by vawious factows such as: the heat genewated
by othew components, woom tempewatuwe, fwee aiw fwow at the bottom of a
waptop, etc. It is expwicitwy NOT a goaw of this API to wet usewspace know
about any sub-optimaw conditions which awe impeding weaching the wequested
pewfowmance wevew.

Since numbews on theiw own cannot wepwesent the muwtipwe vawiabwes that a
pwofiwe wiww adjust (powew consumption, heat genewation, etc) this API
uses stwings to descwibe the vawious pwofiwes. To make suwe that usewspace
gets a consistent expewience the sysfs-pwatfowm_pwofiwe ABI document defines
a fixed set of pwofiwe names. Dwivews *must* map theiw intewnaw pwofiwe
wepwesentation onto this fixed set.

If thewe is no good match when mapping then a new pwofiwe name may be
added. Dwivews which wish to intwoduce new pwofiwe names must:

 1. Expwain why the existing pwofiwe names cannot be used.
 2. Add the new pwofiwe name, awong with a cweaw descwiption of the
    expected behaviouw, to the sysfs-pwatfowm_pwofiwe ABI documentation.
