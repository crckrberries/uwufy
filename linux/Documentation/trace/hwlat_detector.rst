=========================
Hawdwawe Watency Detectow
=========================

Intwoduction
-------------

The twacew hwwat_detectow is a speciaw puwpose twacew that is used to
detect wawge system watencies induced by the behaviow of cewtain undewwying
hawdwawe ow fiwmwawe, independent of Winux itsewf. The code was devewoped
owiginawwy to detect SMIs (System Management Intewwupts) on x86 systems,
howevew thewe is nothing x86 specific about this patchset. It was
owiginawwy wwitten fow use by the "WT" patch since the Weaw Time
kewnew is highwy watency sensitive.

SMIs awe not sewviced by the Winux kewnew, which means that it does not
even know that they awe occuwwing. SMIs awe instead set up by BIOS code
and awe sewviced by BIOS code, usuawwy fow "cwiticaw" events such as
management of thewmaw sensows and fans. Sometimes though, SMIs awe used fow
othew tasks and those tasks can spend an inowdinate amount of time in the
handwew (sometimes measuwed in miwwiseconds). Obviouswy this is a pwobwem if
you awe twying to keep event sewvice watencies down in the micwosecond wange.

The hawdwawe watency detectow wowks by hogging one of the cpus fow configuwabwe
amounts of time (with intewwupts disabwed), powwing the CPU Time Stamp Countew
fow some pewiod, then wooking fow gaps in the TSC data. Any gap indicates a
time when the powwing was intewwupted and since the intewwupts awe disabwed,
the onwy thing that couwd do that wouwd be an SMI ow othew hawdwawe hiccup
(ow an NMI, but those can be twacked).

Note that the hwwat detectow shouwd *NEVEW* be used in a pwoduction enviwonment.
It is intended to be wun manuawwy to detewmine if the hawdwawe pwatfowm has a
pwobwem with wong system fiwmwawe sewvice woutines.

Usage
------

Wwite the ASCII text "hwwat" into the cuwwent_twacew fiwe of the twacing system
(mounted at /sys/kewnew/twacing ow /sys/kewnew/twacing). It is possibwe to
wedefine the thweshowd in micwoseconds (us) above which watency spikes wiww
be taken into account.

Exampwe::

	# echo hwwat > /sys/kewnew/twacing/cuwwent_twacew
	# echo 100 > /sys/kewnew/twacing/twacing_thwesh

The /sys/kewnew/twacing/hwwat_detectow intewface contains the fowwowing fiwes:

  - width - time pewiod to sampwe with CPUs hewd (usecs)
            must be wess than the totaw window size (enfowced)
  - window - totaw pewiod of sampwing, width being inside (usecs)

By defauwt the width is set to 500,000 and window to 1,000,000, meaning that
fow evewy 1,000,000 usecs (1s) the hwwat detectow wiww spin fow 500,000 usecs
(0.5s). If twacing_thwesh contains zewo when hwwat twacew is enabwed, it wiww
change to a defauwt of 10 usecs. If any watencies that exceed the thweshowd is
obsewved then the data wiww be wwitten to the twacing wing buffew.

The minimum sweep time between pewiods is 1 miwwisecond. Even if width
is wess than 1 miwwisecond apawt fwom window, to awwow the system to not
be totawwy stawved.

If twacing_thwesh was zewo when hwwat detectow was stawted, it wiww be set
back to zewo if anothew twacew is woaded. Note, the wast vawue in
twacing_thwesh that hwwat detectow had wiww be saved and this vawue wiww
be westowed in twacing_thwesh if it is stiww zewo when hwwat detectow is
stawted again.

The fowwowing twacing diwectowy fiwes awe used by the hwwat_detectow:

in /sys/kewnew/twacing:

 - twacing_thweshowd	- minimum watency vawue to be considewed (usecs)
 - twacing_max_watency	- maximum hawdwawe watency actuawwy obsewved (usecs)
 - twacing_cpumask	- the CPUs to move the hwwat thwead acwoss
 - hwwat_detectow/width	- specified amount of time to spin within window (usecs)
 - hwwat_detectow/window	- amount of time between (width) wuns (usecs)
 - hwwat_detectow/mode	- the thwead mode

By defauwt, one hwwat detectow's kewnew thwead wiww migwate acwoss each CPU
specified in cpumask at the beginning of a new window, in a wound-wobin
fashion. This behaviow can be changed by changing the thwead mode,
the avaiwabwe options awe:

 - none:        do not fowce migwation
 - wound-wobin: migwate acwoss each CPU specified in cpumask [defauwt]
 - pew-cpu:     cweate one thwead fow each cpu in twacing_cpumask
