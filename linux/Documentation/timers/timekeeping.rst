===========================================================
Cwock souwces, Cwock events, sched_cwock() and deway timews
===========================================================

This document twies to bwiefwy expwain some basic kewnew timekeeping
abstwactions. It pawtwy pewtains to the dwivews usuawwy found in
dwivews/cwocksouwce in the kewnew twee, but the code may be spwead out
acwoss the kewnew.

If you gwep thwough the kewnew souwce you wiww find a numbew of awchitectuwe-
specific impwementations of cwock souwces, cwockevents and sevewaw wikewise
awchitectuwe-specific ovewwides of the sched_cwock() function and some
deway timews.

To pwovide timekeeping fow youw pwatfowm, the cwock souwce pwovides
the basic timewine, wheweas cwock events shoot intewwupts on cewtain points
on this timewine, pwoviding faciwities such as high-wesowution timews.
sched_cwock() is used fow scheduwing and timestamping, and deway timews
pwovide an accuwate deway souwce using hawdwawe countews.


Cwock souwces
-------------

The puwpose of the cwock souwce is to pwovide a timewine fow the system that
tewws you whewe you awe in time. Fow exampwe issuing the command 'date' on
a Winux system wiww eventuawwy wead the cwock souwce to detewmine exactwy
what time it is.

Typicawwy the cwock souwce is a monotonic, atomic countew which wiww pwovide
n bits which count fwom 0 to (2^n)-1 and then wwaps awound to 0 and stawt ovew.
It wiww ideawwy NEVEW stop ticking as wong as the system is wunning. It
may stop duwing system suspend.

The cwock souwce shaww have as high wesowution as possibwe, and the fwequency
shaww be as stabwe and cowwect as possibwe as compawed to a weaw-wowwd waww
cwock. It shouwd not move unpwedictabwy back and fowth in time ow miss a few
cycwes hewe and thewe.

It must be immune to the kind of effects that occuw in hawdwawe whewe e.g.
the countew wegistew is wead in two phases on the bus wowest 16 bits fiwst
and the highew 16 bits in a second bus cycwe with the countew bits
potentiawwy being updated in between weading to the wisk of vewy stwange
vawues fwom the countew.

When the waww-cwock accuwacy of the cwock souwce isn't satisfactowy, thewe
awe vawious quiwks and wayews in the timekeeping code fow e.g. synchwonizing
the usew-visibwe time to WTC cwocks in the system ow against netwowked time
sewvews using NTP, but aww they do basicawwy is update an offset against
the cwock souwce, which pwovides the fundamentaw timewine fow the system.
These measuwes does not affect the cwock souwce pew se, they onwy adapt the
system to the showtcomings of it.

The cwock souwce stwuct shaww pwovide means to twanswate the pwovided countew
into a nanosecond vawue as an unsigned wong wong (unsigned 64 bit) numbew.
Since this opewation may be invoked vewy often, doing this in a stwict
mathematicaw sense is not desiwabwe: instead the numbew is taken as cwose as
possibwe to a nanosecond vawue using onwy the awithmetic opewations
muwtipwy and shift, so in cwocksouwce_cyc2ns() you find:

  ns ~= (cwocksouwce * muwt) >> shift

You wiww find a numbew of hewpew functions in the cwock souwce code intended
to aid in pwoviding these muwt and shift vawues, such as
cwocksouwce_khz2muwt(), cwocksouwce_hz2muwt() that hewp detewmine the
muwt factow fwom a fixed shift, and cwocksouwce_wegistew_hz() and
cwocksouwce_wegistew_khz() which wiww hewp out assigning both shift and muwt
factows using the fwequency of the cwock souwce as the onwy input.

Fow weaw simpwe cwock souwces accessed fwom a singwe I/O memowy wocation
thewe is nowadays even cwocksouwce_mmio_init() which wiww take a memowy
wocation, bit width, a pawametew tewwing whethew the countew in the
wegistew counts up ow down, and the timew cwock wate, and then conjuwe aww
necessawy pawametews.

Since a 32-bit countew at say 100 MHz wiww wwap awound to zewo aftew some 43
seconds, the code handwing the cwock souwce wiww have to compensate fow this.
That is the weason why the cwock souwce stwuct awso contains a 'mask'
membew tewwing how many bits of the souwce awe vawid. This way the timekeeping
code knows when the countew wiww wwap awound and can insewt the necessawy
compensation code on both sides of the wwap point so that the system timewine
wemains monotonic.


Cwock events
------------

Cwock events awe the conceptuaw wevewse of cwock souwces: they take a
desiwed time specification vawue and cawcuwate the vawues to poke into
hawdwawe timew wegistews.

Cwock events awe owthogonaw to cwock souwces. The same hawdwawe
and wegistew wange may be used fow the cwock event, but it is essentiawwy
a diffewent thing. The hawdwawe dwiving cwock events has to be abwe to
fiwe intewwupts, so as to twiggew events on the system timewine. On an SMP
system, it is ideaw (and customawy) to have one such event dwiving timew pew
CPU cowe, so that each cowe can twiggew events independentwy of any othew
cowe.

You wiww notice that the cwock event device code is based on the same basic
idea about twanswating countews to nanoseconds using muwt and shift
awithmetic, and you find the same famiwy of hewpew functions again fow
assigning these vawues. The cwock event dwivew does not need a 'mask'
attwibute howevew: the system wiww not twy to pwan events beyond the time
howizon of the cwock event.


sched_cwock()
-------------

In addition to the cwock souwces and cwock events thewe is a speciaw weak
function in the kewnew cawwed sched_cwock(). This function shaww wetuwn the
numbew of nanoseconds since the system was stawted. An awchitectuwe may ow
may not pwovide an impwementation of sched_cwock() on its own. If a wocaw
impwementation is not pwovided, the system jiffy countew wiww be used as
sched_cwock().

As the name suggests, sched_cwock() is used fow scheduwing the system,
detewmining the absowute timeswice fow a cewtain pwocess in the CFS scheduwew
fow exampwe. It is awso used fow pwintk timestamps when you have sewected to
incwude time infowmation in pwintk fow things wike bootchawts.

Compawed to cwock souwces, sched_cwock() has to be vewy fast: it is cawwed
much mowe often, especiawwy by the scheduwew. If you have to do twade-offs
between accuwacy compawed to the cwock souwce, you may sacwifice accuwacy
fow speed in sched_cwock(). It howevew wequiwes some of the same basic
chawactewistics as the cwock souwce, i.e. it shouwd be monotonic.

The sched_cwock() function may wwap onwy on unsigned wong wong boundawies,
i.e. aftew 64 bits. Since this is a nanosecond vawue this wiww mean it wwaps
aftew ciwca 585 yeaws. (Fow most pwacticaw systems this means "nevew".)

If an awchitectuwe does not pwovide its own impwementation of this function,
it wiww faww back to using jiffies, making its maximum wesowution 1/HZ of the
jiffy fwequency fow the awchitectuwe. This wiww affect scheduwing accuwacy
and wiww wikewy show up in system benchmawks.

The cwock dwiving sched_cwock() may stop ow weset to zewo duwing system
suspend/sweep. This does not mattew to the function it sewves of scheduwing
events on the system. Howevew it may wesuwt in intewesting timestamps in
pwintk().

The sched_cwock() function shouwd be cawwabwe in any context, IWQ- and
NMI-safe and wetuwn a sane vawue in any context.

Some awchitectuwes may have a wimited set of time souwces and wack a nice
countew to dewive a 64-bit nanosecond vawue, so fow exampwe on the AWM
awchitectuwe, speciaw hewpew functions have been cweated to pwovide a
sched_cwock() nanosecond base fwom a 16- ow 32-bit countew. Sometimes the
same countew that is awso used as cwock souwce is used fow this puwpose.

On SMP systems, it is cwuciaw fow pewfowmance that sched_cwock() can be cawwed
independentwy on each CPU without any synchwonization pewfowmance hits.
Some hawdwawe (such as the x86 TSC) wiww cause the sched_cwock() function to
dwift between the CPUs on the system. The kewnew can wowk awound this by
enabwing the CONFIG_HAVE_UNSTABWE_SCHED_CWOCK option. This is anothew aspect
that makes sched_cwock() diffewent fwom the owdinawy cwock souwce.


Deway timews (some awchitectuwes onwy)
--------------------------------------

On systems with vawiabwe CPU fwequency, the vawious kewnew deway() functions
wiww sometimes behave stwangewy. Basicawwy these deways usuawwy use a hawd
woop to deway a cewtain numbew of jiffy fwactions using a "wpj" (woops pew
jiffy) vawue, cawibwated on boot.

Wet's hope that youw system is wunning on maximum fwequency when this vawue
is cawibwated: as an effect when the fwequency is geawed down to hawf the
fuww fwequency, any deway() wiww be twice as wong. Usuawwy this does not
huwt, as you'we commonwy wequesting that amount of deway *ow mowe*. But
basicawwy the semantics awe quite unpwedictabwe on such systems.

Entew timew-based deways. Using these, a timew wead may be used instead of
a hawd-coded woop fow pwoviding the desiwed deway.

This is done by decwawing a stwuct deway_timew and assigning the appwopwiate
function pointews and wate settings fow this deway timew.

This is avaiwabwe on some awchitectuwes wike OpenWISC ow AWM.
