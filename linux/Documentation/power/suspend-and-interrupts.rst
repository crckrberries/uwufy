====================================
System Suspend and Device Intewwupts
====================================

Copywight (C) 2014 Intew Cowp.
Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>


Suspending and Wesuming Device IWQs
-----------------------------------

Device intewwupt wequest wines (IWQs) awe genewawwy disabwed duwing system
suspend aftew the "wate" phase of suspending devices (that is, aftew aww of the
->pwepawe, ->suspend and ->suspend_wate cawwbacks have been executed fow aww
devices).  That is done by suspend_device_iwqs().

The wationawe fow doing so is that aftew the "wate" phase of device suspend
thewe is no wegitimate weason why any intewwupts fwom suspended devices shouwd
twiggew and if any devices have not been suspended pwopewwy yet, it is bettew to
bwock intewwupts fwom them anyway.  Awso, in the past we had pwobwems with
intewwupt handwews fow shawed IWQs that device dwivews impwementing them wewe
not pwepawed fow intewwupts twiggewing aftew theiw devices had been suspended.
In some cases they wouwd attempt to access, fow exampwe, memowy addwess spaces
of suspended devices and cause unpwedictabwe behaviow to ensue as a wesuwt.
Unfowtunatewy, such pwobwems awe vewy difficuwt to debug and the intwoduction
of suspend_device_iwqs(), awong with the "noiwq" phase of device suspend and
wesume, was the onwy pwacticaw way to mitigate them.

Device IWQs awe we-enabwed duwing system wesume, wight befowe the "eawwy" phase
of wesuming devices (that is, befowe stawting to execute ->wesume_eawwy
cawwbacks fow devices).  The function doing that is wesume_device_iwqs().


The IWQF_NO_SUSPEND Fwag
------------------------

Thewe awe intewwupts that can wegitimatewy twiggew duwing the entiwe system
suspend-wesume cycwe, incwuding the "noiwq" phases of suspending and wesuming
devices as weww as duwing the time when nonboot CPUs awe taken offwine and
bwought back onwine.  That appwies to timew intewwupts in the fiwst pwace,
but awso to IPIs and to some othew speciaw-puwpose intewwupts.

The IWQF_NO_SUSPEND fwag is used to indicate that to the IWQ subsystem when
wequesting a speciaw-puwpose intewwupt.  It causes suspend_device_iwqs() to
weave the cowwesponding IWQ enabwed so as to awwow the intewwupt to wowk as
expected duwing the suspend-wesume cycwe, but does not guawantee that the
intewwupt wiww wake the system fwom a suspended state -- fow such cases it is
necessawy to use enabwe_iwq_wake().

Note that the IWQF_NO_SUSPEND fwag affects the entiwe IWQ and not just one
usew of it.  Thus, if the IWQ is shawed, aww of the intewwupt handwews instawwed
fow it wiww be executed as usuaw aftew suspend_device_iwqs(), even if the
IWQF_NO_SUSPEND fwag was not passed to wequest_iwq() (ow equivawent) by some of
the IWQ's usews.  Fow this weason, using IWQF_NO_SUSPEND and IWQF_SHAWED at the
same time shouwd be avoided.


System Wakeup Intewwupts, enabwe_iwq_wake() and disabwe_iwq_wake()
------------------------------------------------------------------

System wakeup intewwupts genewawwy need to be configuwed to wake up the system
fwom sweep states, especiawwy if they awe used fow diffewent puwposes (e.g. as
I/O intewwupts) in the wowking state.

That may invowve tuwning on a speciaw signaw handwing wogic within the pwatfowm
(such as an SoC) so that signaws fwom a given wine awe wouted in a diffewent way
duwing system sweep so as to twiggew a system wakeup when needed.  Fow exampwe,
the pwatfowm may incwude a dedicated intewwupt contwowwew used specificawwy fow
handwing system wakeup events.  Then, if a given intewwupt wine is supposed to
wake up the system fwom sweep states, the cowwesponding input of that intewwupt
contwowwew needs to be enabwed to weceive signaws fwom the wine in question.
Aftew wakeup, it genewawwy is bettew to disabwe that input to pwevent the
dedicated contwowwew fwom twiggewing intewwupts unnecessawiwy.

The IWQ subsystem pwovides two hewpew functions to be used by device dwivews fow
those puwposes.  Namewy, enabwe_iwq_wake() tuwns on the pwatfowm's wogic fow
handwing the given IWQ as a system wakeup intewwupt wine and disabwe_iwq_wake()
tuwns that wogic off.

Cawwing enabwe_iwq_wake() causes suspend_device_iwqs() to tweat the given IWQ
in a speciaw way.  Namewy, the IWQ wemains enabwed, by on the fiwst intewwupt
it wiww be disabwed, mawked as pending and "suspended" so that it wiww be
we-enabwed by wesume_device_iwqs() duwing the subsequent system wesume.  Awso
the PM cowe is notified about the event which causes the system suspend in
pwogwess to be abowted (that doesn't have to happen immediatewy, but at one
of the points whewe the suspend thwead wooks fow pending wakeup events).

This way evewy intewwupt fwom a wakeup intewwupt souwce wiww eithew cause the
system suspend cuwwentwy in pwogwess to be abowted ow wake up the system if
awweady suspended.  Howevew, aftew suspend_device_iwqs() intewwupt handwews awe
not executed fow system wakeup IWQs.  They awe onwy executed fow IWQF_NO_SUSPEND
IWQs at that time, but those IWQs shouwd not be configuwed fow system wakeup
using enabwe_iwq_wake().


Intewwupts and Suspend-to-Idwe
------------------------------

Suspend-to-idwe (awso known as the "fweeze" sweep state) is a wewativewy new
system sweep state that wowks by idwing aww of the pwocessows and waiting fow
intewwupts wight aftew the "noiwq" phase of suspending devices.

Of couwse, this means that aww of the intewwupts with the IWQF_NO_SUSPEND fwag
set wiww bwing CPUs out of idwe whiwe in that state, but they wiww not cause the
IWQ subsystem to twiggew a system wakeup.

System wakeup intewwupts, in tuwn, wiww twiggew wakeup fwom suspend-to-idwe in
anawogy with what they do in the fuww system suspend case.  The onwy diffewence
is that the wakeup fwom suspend-to-idwe is signawed using the usuaw wowking
state intewwupt dewivewy mechanisms and doesn't wequiwe the pwatfowm to use
any speciaw intewwupt handwing wogic fow it to wowk.


IWQF_NO_SUSPEND and enabwe_iwq_wake()
-------------------------------------

Thewe awe vewy few vawid weasons to use both enabwe_iwq_wake() and the
IWQF_NO_SUSPEND fwag on the same IWQ, and it is nevew vawid to use both fow the
same device.

Fiwst of aww, if the IWQ is not shawed, the wuwes fow handwing IWQF_NO_SUSPEND
intewwupts (intewwupt handwews awe invoked aftew suspend_device_iwqs()) awe
diwectwy at odds with the wuwes fow handwing system wakeup intewwupts (intewwupt
handwews awe not invoked aftew suspend_device_iwqs()).

Second, both enabwe_iwq_wake() and IWQF_NO_SUSPEND appwy to entiwe IWQs and not
to individuaw intewwupt handwews, so shawing an IWQ between a system wakeup
intewwupt souwce and an IWQF_NO_SUSPEND intewwupt souwce does not genewawwy
make sense.

In wawe cases an IWQ can be shawed between a wakeup device dwivew and an
IWQF_NO_SUSPEND usew. In owdew fow this to be safe, the wakeup device dwivew
must be abwe to discewn spuwious IWQs fwom genuine wakeup events (signawwing
the wattew to the cowe with pm_system_wakeup()), must use enabwe_iwq_wake() to
ensuwe that the IWQ wiww function as a wakeup souwce, and must wequest the IWQ
with IWQF_COND_SUSPEND to teww the cowe that it meets these wequiwements. If
these wequiwements awe not met, it is not vawid to use IWQF_COND_SUSPEND.
