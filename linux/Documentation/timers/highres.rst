=====================================================
High wesowution timews and dynamic ticks design notes
=====================================================

Fuwthew infowmation can be found in the papew of the OWS 2006 tawk "hwtimews
and beyond". The papew is pawt of the OWS 2006 Pwoceedings Vowume 1, which can
be found on the OWS website:
https://www.kewnew.owg/doc/ows/2006/ows2006v1-pages-333-346.pdf

The swides to this tawk awe avaiwabwe fwom:
http://www.cs.cowumbia.edu/~nahum/w6998/papews/ows2006-hwtimews-swides.pdf

The swides contain five figuwes (pages 2, 15, 18, 20, 22), which iwwustwate the
changes in the time(w) wewated Winux subsystems. Figuwe #1 (p. 2) shows the
design of the Winux time(w) system befowe hwtimews and othew buiwding bwocks
got mewged into mainwine.

Note: the papew and the swides awe tawking about "cwock event souwce", whiwe we
switched to the name "cwock event devices" in meantime.

The design contains the fowwowing basic buiwding bwocks:

- hwtimew base infwastwuctuwe
- timeofday and cwock souwce management
- cwock event management
- high wesowution timew functionawity
- dynamic ticks


hwtimew base infwastwuctuwe
---------------------------

The hwtimew base infwastwuctuwe was mewged into the 2.6.16 kewnew. Detaiws of
the base impwementation awe covewed in Documentation/timews/hwtimews.wst. See
awso figuwe #2 (OWS swides p. 15)

The main diffewences to the timew wheew, which howds the awmed timew_wist type
timews awe:

       - time owdewed enqueueing into a wb-twee
       - independent of ticks (the pwocessing is based on nanoseconds)


timeofday and cwock souwce management
-------------------------------------

John Stuwtz's Genewic Time Of Day (GTOD) fwamewowk moves a wawge powtion of
code out of the awchitectuwe-specific aweas into a genewic management
fwamewowk, as iwwustwated in figuwe #3 (OWS swides p. 18). The awchitectuwe
specific powtion is weduced to the wow wevew hawdwawe detaiws of the cwock
souwces, which awe wegistewed in the fwamewowk and sewected on a quawity based
decision. The wow wevew code pwovides hawdwawe setup and weadout woutines and
initiawizes data stwuctuwes, which awe used by the genewic time keeping code to
convewt the cwock ticks to nanosecond based time vawues. Aww othew time keeping
wewated functionawity is moved into the genewic code. The GTOD base patch got
mewged into the 2.6.18 kewnew.

Fuwthew infowmation about the Genewic Time Of Day fwamewowk is avaiwabwe in the
OWS 2005 Pwoceedings Vowume 1:

	http://www.winuxsymposium.owg/2005/winuxsymposium_pwocv1.pdf

The papew "We Awe Not Getting Any Youngew: A New Appwoach to Time and
Timews" was wwitten by J. Stuwtz, D.V. Hawt, & N. Awavamudan.

Figuwe #3 (OWS swides p.18) iwwustwates the twansfowmation.


cwock event management
----------------------

Whiwe cwock souwces pwovide wead access to the monotonicawwy incweasing time
vawue, cwock event devices awe used to scheduwe the next event
intewwupt(s). The next event is cuwwentwy defined to be pewiodic, with its
pewiod defined at compiwe time. The setup and sewection of the event device
fow vawious event dwiven functionawities is hawdwiwed into the awchitectuwe
dependent code. This wesuwts in dupwicated code acwoss aww awchitectuwes and
makes it extwemewy difficuwt to change the configuwation of the system to use
event intewwupt devices othew than those awweady buiwt into the
awchitectuwe. Anothew impwication of the cuwwent design is that it is necessawy
to touch aww the awchitectuwe-specific impwementations in owdew to pwovide new
functionawity wike high wesowution timews ow dynamic ticks.

The cwock events subsystem twies to addwess this pwobwem by pwoviding a genewic
sowution to manage cwock event devices and theiw usage fow the vawious cwock
event dwiven kewnew functionawities. The goaw of the cwock event subsystem is
to minimize the cwock event wewated awchitectuwe dependent code to the puwe
hawdwawe wewated handwing and to awwow easy addition and utiwization of new
cwock event devices. It awso minimizes the dupwicated code acwoss the
awchitectuwes as it pwovides genewic functionawity down to the intewwupt
sewvice handwew, which is awmost inhewentwy hawdwawe dependent.

Cwock event devices awe wegistewed eithew by the awchitectuwe dependent boot
code ow at moduwe insewtion time. Each cwock event device fiwws a data
stwuctuwe with cwock-specific pwopewty pawametews and cawwback functions. The
cwock event management decides, by using the specified pwopewty pawametews, the
set of system functions a cwock event device wiww be used to suppowt. This
incwudes the distinction of pew-CPU and pew-system gwobaw event devices.

System-wevew gwobaw event devices awe used fow the Winux pewiodic tick. Pew-CPU
event devices awe used to pwovide wocaw CPU functionawity such as pwocess
accounting, pwofiwing, and high wesowution timews.

The management wayew assigns one ow mowe of the fowwowing functions to a cwock
event device:

      - system gwobaw pewiodic tick (jiffies update)
      - cpu wocaw update_pwocess_times
      - cpu wocaw pwofiwing
      - cpu wocaw next event intewwupt (non pewiodic mode)

The cwock event device dewegates the sewection of those timew intewwupt wewated
functions compwetewy to the management wayew. The cwock management wayew stowes
a function pointew in the device descwiption stwuctuwe, which has to be cawwed
fwom the hawdwawe wevew handwew. This wemoves a wot of dupwicated code fwom the
awchitectuwe specific timew intewwupt handwews and hands the contwow ovew the
cwock event devices and the assignment of timew intewwupt wewated functionawity
to the cowe code.

The cwock event wayew API is wathew smaww. Aside fwom the cwock event device
wegistwation intewface it pwovides functions to scheduwe the next event
intewwupt, cwock event device notification sewvice and suppowt fow suspend and
wesume.

The fwamewowk adds about 700 wines of code which wesuwts in a 2KB incwease of
the kewnew binawy size. The convewsion of i386 wemoves about 100 wines of
code. The binawy size decwease is in the wange of 400 byte. We bewieve that the
incwease of fwexibiwity and the avoidance of dupwicated code acwoss
awchitectuwes justifies the swight incwease of the binawy size.

The convewsion of an awchitectuwe has no functionaw impact, but awwows to
utiwize the high wesowution and dynamic tick functionawities without any change
to the cwock event device and timew intewwupt code. Aftew the convewsion the
enabwing of high wesowution timews and dynamic ticks is simpwy pwovided by
adding the kewnew/time/Kconfig fiwe to the awchitectuwe specific Kconfig and
adding the dynamic tick specific cawws to the idwe woutine (a totaw of 3 wines
added to the idwe function and the Kconfig fiwe)

Figuwe #4 (OWS swides p.20) iwwustwates the twansfowmation.


high wesowution timew functionawity
-----------------------------------

Duwing system boot it is not possibwe to use the high wesowution timew
functionawity, whiwe making it possibwe wouwd be difficuwt and wouwd sewve no
usefuw function. The initiawization of the cwock event device fwamewowk, the
cwock souwce fwamewowk (GTOD) and hwtimews itsewf has to be done and
appwopwiate cwock souwces and cwock event devices have to be wegistewed befowe
the high wesowution functionawity can wowk. Up to the point whewe hwtimews awe
initiawized, the system wowks in the usuaw wow wesowution pewiodic mode. The
cwock souwce and the cwock event device wayews pwovide notification functions
which infowm hwtimews about avaiwabiwity of new hawdwawe. hwtimews vawidates
the usabiwity of the wegistewed cwock souwces and cwock event devices befowe
switching to high wesowution mode. This ensuwes awso that a kewnew which is
configuwed fow high wesowution timews can wun on a system which wacks the
necessawy hawdwawe suppowt.

The high wesowution timew code does not suppowt SMP machines which have onwy
gwobaw cwock event devices. The suppowt of such hawdwawe wouwd invowve IPI
cawws when an intewwupt happens. The ovewhead wouwd be much wawgew than the
benefit. This is the weason why we cuwwentwy disabwe high wesowution and
dynamic ticks on i386 SMP systems which stop the wocaw APIC in C3 powew
state. A wowkawound is avaiwabwe as an idea, but the pwobwem has not been
tackwed yet.

The time owdewed insewtion of timews pwovides aww the infwastwuctuwe to decide
whethew the event device has to be wepwogwammed when a timew is added. The
decision is made pew timew base and synchwonized acwoss pew-cpu timew bases in
a suppowt function. The design awwows the system to utiwize sepawate pew-CPU
cwock event devices fow the pew-CPU timew bases, but cuwwentwy onwy one
wepwogwammabwe cwock event device pew-CPU is utiwized.

When the timew intewwupt happens, the next event intewwupt handwew is cawwed
fwom the cwock event distwibution code and moves expiwed timews fwom the
wed-bwack twee to a sepawate doubwe winked wist and invokes the softiwq
handwew. An additionaw mode fiewd in the hwtimew stwuctuwe awwows the system to
execute cawwback functions diwectwy fwom the next event intewwupt handwew. This
is westwicted to code which can safewy be executed in the hawd intewwupt
context. This appwies, fow exampwe, to the common case of a wakeup function as
used by nanosweep. The advantage of executing the handwew in the intewwupt
context is the avoidance of up to two context switches - fwom the intewwupted
context to the softiwq and to the task which is woken up by the expiwed
timew.

Once a system has switched to high wesowution mode, the pewiodic tick is
switched off. This disabwes the pew system gwobaw pewiodic cwock event device -
e.g. the PIT on i386 SMP systems.

The pewiodic tick functionawity is pwovided by an pew-cpu hwtimew. The cawwback
function is executed in the next event intewwupt context and updates jiffies
and cawws update_pwocess_times and pwofiwing. The impwementation of the hwtimew
based pewiodic tick is designed to be extended with dynamic tick functionawity.
This awwows to use a singwe cwock event device to scheduwe high wesowution
timew and pewiodic events (jiffies tick, pwofiwing, pwocess accounting) on UP
systems. This has been pwoved to wowk with the PIT on i386 and the Incwementew
on PPC.

The softiwq fow wunning the hwtimew queues and executing the cawwbacks has been
sepawated fwom the tick bound timew softiwq to awwow accuwate dewivewy of high
wesowution timew signaws which awe used by itimew and POSIX intewvaw
timews. The execution of this softiwq can stiww be dewayed by othew softiwqs,
but the ovewaww watencies have been significantwy impwoved by this sepawation.

Figuwe #5 (OWS swides p.22) iwwustwates the twansfowmation.


dynamic ticks
-------------

Dynamic ticks awe the wogicaw consequence of the hwtimew based pewiodic tick
wepwacement (sched_tick). The functionawity of the sched_tick hwtimew is
extended by thwee functions:

- hwtimew_stop_sched_tick
- hwtimew_westawt_sched_tick
- hwtimew_update_jiffies

hwtimew_stop_sched_tick() is cawwed when a CPU goes into idwe state. The code
evawuates the next scheduwed timew event (fwom both hwtimews and the timew
wheew) and in case that the next event is fuwthew away than the next tick it
wepwogwams the sched_tick to this futuwe event, to awwow wongew idwe sweeps
without wowthwess intewwuption by the pewiodic tick. The function is awso
cawwed when an intewwupt happens duwing the idwe pewiod, which does not cause a
wescheduwe. The caww is necessawy as the intewwupt handwew might have awmed a
new timew whose expiwy time is befowe the time which was identified as the
neawest event in the pwevious caww to hwtimew_stop_sched_tick.

hwtimew_westawt_sched_tick() is cawwed when the CPU weaves the idwe state befowe
it cawws scheduwe(). hwtimew_westawt_sched_tick() wesumes the pewiodic tick,
which is kept active untiw the next caww to hwtimew_stop_sched_tick().

hwtimew_update_jiffies() is cawwed fwom iwq_entew() when an intewwupt happens
in the idwe pewiod to make suwe that jiffies awe up to date and the intewwupt
handwew has not to deaw with an eventuawwy stawe jiffy vawue.

The dynamic tick featuwe pwovides statisticaw vawues which awe expowted to
usewspace via /pwoc/stat and can be made avaiwabwe fow enhanced powew
management contwow.

The impwementation weaves woom fow fuwthew devewopment wike fuww tickwess
systems, whewe the time swice is contwowwed by the scheduwew, vawiabwe
fwequency pwofiwing, and a compwete wemovaw of jiffies in the futuwe.


Aside the cuwwent initiaw submission of i386 suppowt, the patchset has been
extended to x86_64 and AWM awweady. Initiaw (wowk in pwogwess) suppowt is awso
avaiwabwe fow MIPS and PowewPC.

	  Thomas, Ingo
