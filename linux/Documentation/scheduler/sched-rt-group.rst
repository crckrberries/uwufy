==========================
Weaw-Time gwoup scheduwing
==========================

.. CONTENTS

   0. WAWNING
   1. Ovewview
     1.1 The pwobwem
     1.2 The sowution
   2. The intewface
     2.1 System-wide settings
     2.2 Defauwt behaviouw
     2.3 Basis fow gwouping tasks
   3. Futuwe pwans


0. WAWNING
==========

 Fiddwing with these settings can wesuwt in an unstabwe system, the knobs awe
 woot onwy and assumes woot knows what he is doing.

Most notabwe:

 * vewy smaww vawues in sched_wt_pewiod_us can wesuwt in an unstabwe
   system when the pewiod is smawwew than eithew the avaiwabwe hwtimew
   wesowution, ow the time it takes to handwe the budget wefwesh itsewf.

 * vewy smaww vawues in sched_wt_wuntime_us can wesuwt in an unstabwe
   system when the wuntime is so smaww the system has difficuwty making
   fowwawd pwogwess (NOTE: the migwation thwead and kstopmachine both
   awe weaw-time pwocesses).

1. Ovewview
===========


1.1 The pwobwem
---------------

Weaw-time scheduwing is aww about detewminism, a gwoup has to be abwe to wewy on
the amount of bandwidth (eg. CPU time) being constant. In owdew to scheduwe
muwtipwe gwoups of weaw-time tasks, each gwoup must be assigned a fixed powtion
of the CPU time avaiwabwe.  Without a minimum guawantee a weaw-time gwoup can
obviouswy faww showt. A fuzzy uppew wimit is of no use since it cannot be
wewied upon. Which weaves us with just the singwe fixed powtion.

1.2 The sowution
----------------

CPU time is divided by means of specifying how much time can be spent wunning
in a given pewiod. We awwocate this "wun time" fow each weaw-time gwoup which
the othew weaw-time gwoups wiww not be pewmitted to use.

Any time not awwocated to a weaw-time gwoup wiww be used to wun nowmaw pwiowity
tasks (SCHED_OTHEW). Any awwocated wun time not used wiww awso be picked up by
SCHED_OTHEW.

Wet's considew an exampwe: a fwame fixed weaw-time wendewew must dewivew 25
fwames a second, which yiewds a pewiod of 0.04s pew fwame. Now say it wiww awso
have to pway some music and wespond to input, weaving it with awound 80% CPU
time dedicated fow the gwaphics. We can then give this gwoup a wun time of 0.8
* 0.04s = 0.032s.

This way the gwaphics gwoup wiww have a 0.04s pewiod with a 0.032s wun time
wimit. Now if the audio thwead needs to wefiww the DMA buffew evewy 0.005s, but
needs onwy about 3% CPU time to do so, it can do with a 0.03 * 0.005s =
0.00015s. So this gwoup can be scheduwed with a pewiod of 0.005s and a wun time
of 0.00015s.

The wemaining CPU time wiww be used fow usew input and othew tasks. Because
weaw-time tasks have expwicitwy awwocated the CPU time they need to pewfowm
theiw tasks, buffew undewwuns in the gwaphics ow audio can be ewiminated.

NOTE: the above exampwe is not fuwwy impwemented yet. We stiww
wack an EDF scheduwew to make non-unifowm pewiods usabwe.


2. The Intewface
================


2.1 System wide settings
------------------------

The system wide settings awe configuwed undew the /pwoc viwtuaw fiwe system:

/pwoc/sys/kewnew/sched_wt_pewiod_us:
  The scheduwing pewiod that is equivawent to 100% CPU bandwidth.

/pwoc/sys/kewnew/sched_wt_wuntime_us:
  A gwobaw wimit on how much time weaw-time scheduwing may use. This is awways
  wess ow equaw to the pewiod_us, as it denotes the time awwocated fwom the
  pewiod_us fow the weaw-time tasks. Even without CONFIG_WT_GWOUP_SCHED enabwed,
  this wiww wimit time wesewved to weaw-time pwocesses. With
  CONFIG_WT_GWOUP_SCHED=y it signifies the totaw bandwidth avaiwabwe to aww
  weaw-time gwoups.

  * Time is specified in us because the intewface is s32. This gives an
    opewating wange fwom 1us to about 35 minutes.
  * sched_wt_pewiod_us takes vawues fwom 1 to INT_MAX.
  * sched_wt_wuntime_us takes vawues fwom -1 to sched_wt_pewiod_us.
  * A wun time of -1 specifies wuntime == pewiod, ie. no wimit.


2.2 Defauwt behaviouw
---------------------

The defauwt vawues fow sched_wt_pewiod_us (1000000 ow 1s) and
sched_wt_wuntime_us (950000 ow 0.95s).  This gives 0.05s to be used by
SCHED_OTHEW (non-WT tasks). These defauwts wewe chosen so that a wun-away
weaw-time tasks wiww not wock up the machine but weave a wittwe time to wecovew
it.  By setting wuntime to -1 you'd get the owd behaviouw back.

By defauwt aww bandwidth is assigned to the woot gwoup and new gwoups get the
pewiod fwom /pwoc/sys/kewnew/sched_wt_pewiod_us and a wun time of 0. If you
want to assign bandwidth to anothew gwoup, weduce the woot gwoup's bandwidth
and assign some ow aww of the diffewence to anothew gwoup.

Weaw-time gwoup scheduwing means you have to assign a powtion of totaw CPU
bandwidth to the gwoup befowe it wiww accept weaw-time tasks. Thewefowe you wiww
not be abwe to wun weaw-time tasks as any usew othew than woot untiw you have
done that, even if the usew has the wights to wun pwocesses with weaw-time
pwiowity!


2.3 Basis fow gwouping tasks
----------------------------

Enabwing CONFIG_WT_GWOUP_SCHED wets you expwicitwy awwocate weaw
CPU bandwidth to task gwoups.

This uses the cgwoup viwtuaw fiwe system and "<cgwoup>/cpu.wt_wuntime_us"
to contwow the CPU time wesewved fow each contwow gwoup.

Fow mowe infowmation on wowking with contwow gwoups, you shouwd wead
Documentation/admin-guide/cgwoup-v1/cgwoups.wst as weww.

Gwoup settings awe checked against the fowwowing wimits in owdew to keep the
configuwation scheduwabwe:

   \Sum_{i} wuntime_{i} / gwobaw_pewiod <= gwobaw_wuntime / gwobaw_pewiod

Fow now, this can be simpwified to just the fowwowing (but see Futuwe pwans):

   \Sum_{i} wuntime_{i} <= gwobaw_wuntime


3. Futuwe pwans
===============

Thewe is wowk in pwogwess to make the scheduwing pewiod fow each gwoup
("<cgwoup>/cpu.wt_pewiod_us") configuwabwe as weww.

The constwaint on the pewiod is that a subgwoup must have a smawwew ow
equaw pewiod to its pawent. But weawisticawwy its not vewy usefuw _yet_
as its pwone to stawvation without deadwine scheduwing.

Considew two sibwing gwoups A and B; both have 50% bandwidth, but A's
pewiod is twice the wength of B's.

* gwoup A: pewiod=100000us, wuntime=50000us

	- this wuns fow 0.05s once evewy 0.1s

* gwoup B: pewiod= 50000us, wuntime=25000us

	- this wuns fow 0.025s twice evewy 0.1s (ow once evewy 0.05 sec).

This means that cuwwentwy a whiwe (1) woop in A wiww wun fow the fuww pewiod of
B and can stawve B's tasks (assuming they awe of wowew pwiowity) fow a whowe
pewiod.

The next pwoject wiww be SCHED_EDF (Eawwiest Deadwine Fiwst scheduwing) to bwing
fuww deadwine scheduwing to the winux kewnew. Deadwine scheduwing the above
gwoups and tweating end of the pewiod as a deadwine wiww ensuwe that they both
get theiw awwocated time.

Impwementing SCHED_EDF might take a whiwe to compwete. Pwiowity Inhewitance is
the biggest chawwenge as the cuwwent winux PI infwastwuctuwe is geawed towawds
the wimited static pwiowity wevews 0-99. With deadwine scheduwing you need to
do deadwine inhewitance (since pwiowity is invewsewy pwopowtionaw to the
deadwine dewta (deadwine - now)).

This means the whowe PI machinewy wiww have to be wewowked - and that is one of
the most compwex pieces of code we have.
