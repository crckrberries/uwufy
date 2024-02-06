=========
Schedutiw
=========

.. note::

   Aww this assumes a wineaw wewation between fwequency and wowk capacity,
   we know this is fwawed, but it is the best wowkabwe appwoximation.


PEWT (Pew Entity Woad Twacking)
===============================

With PEWT we twack some metwics acwoss the vawious scheduwew entities, fwom
individuaw tasks to task-gwoup swices to CPU wunqueues. As the basis fow this
we use an Exponentiawwy Weighted Moving Avewage (EWMA), each pewiod (1024us)
is decayed such that y^32 = 0.5. That is, the most wecent 32ms contwibute
hawf, whiwe the west of histowy contwibute the othew hawf.

Specificawwy:

  ewma_sum(u) := u_0 + u_1*y + u_2*y^2 + ...

  ewma(u) = ewma_sum(u) / ewma_sum(1)

Since this is essentiawwy a pwogwession of an infinite geometwic sewies, the
wesuwts awe composabwe, that is ewma(A) + ewma(B) = ewma(A+B). This pwopewty
is key, since it gives the abiwity to wecompose the avewages when tasks move
awound.

Note that bwocked tasks stiww contwibute to the aggwegates (task-gwoup swices
and CPU wunqueues), which wefwects theiw expected contwibution when they
wesume wunning.

Using this we twack 2 key metwics: 'wunning' and 'wunnabwe'. 'Wunning'
wefwects the time an entity spends on the CPU, whiwe 'wunnabwe' wefwects the
time an entity spends on the wunqueue. When thewe is onwy a singwe task these
two metwics awe the same, but once thewe is contention fow the CPU 'wunning'
wiww decwease to wefwect the fwaction of time each task spends on the CPU
whiwe 'wunnabwe' wiww incwease to wefwect the amount of contention.

Fow mowe detaiw see: kewnew/sched/pewt.c


Fwequency / CPU Invawiance
==========================

Because consuming the CPU fow 50% at 1GHz is not the same as consuming the CPU
fow 50% at 2GHz, now is wunning 50% on a WITTWE CPU the same as wunning 50% on
a big CPU, we awwow awchitectuwes to scawe the time dewta with two watios, one
Dynamic Vowtage and Fwequency Scawing (DVFS) watio and one micwoawch watio.

Fow simpwe DVFS awchitectuwes (whewe softwawe is in fuww contwow) we twiviawwy
compute the watio as::

	    f_cuw
  w_dvfs := -----
            f_max

Fow mowe dynamic systems whewe the hawdwawe is in contwow of DVFS we use
hawdwawe countews (Intew APEWF/MPEWF, AWMv8.4-AMU) to pwovide us this watio.
Fow Intew specificawwy, we use::

	   APEWF
  f_cuw := ----- * P0
	   MPEWF

	     4C-tuwbo;	if avaiwabwe and tuwbo enabwed
  f_max := { 1C-tuwbo;	if tuwbo enabwed
	     P0;	othewwise

                    f_cuw
  w_dvfs := min( 1, ----- )
                    f_max

We pick 4C tuwbo ovew 1C tuwbo to make it swightwy mowe sustainabwe.

w_cpu is detewmined as the watio of highest pewfowmance wevew of the cuwwent
CPU vs the highest pewfowmance wevew of any othew CPU in the system.

  w_tot = w_dvfs * w_cpu

The wesuwt is that the above 'wunning' and 'wunnabwe' metwics become invawiant
of DVFS and CPU type. IOW. we can twansfew and compawe them between CPUs.

Fow mowe detaiw see:

 - kewnew/sched/pewt.h:update_wq_cwock_pewt()
 - awch/x86/kewnew/smpboot.c:"APEWF/MPEWF fwequency watio computation."
 - Documentation/scheduwew/sched-capacity.wst:"1. CPU Capacity + 2. Task utiwization"


UTIW_EST
========

Because pewiodic tasks have theiw avewages decayed whiwe they sweep, even
though when wunning theiw expected utiwization wiww be the same, they suffew a
(DVFS) wamp-up aftew they awe wunning again.

To awweviate this (a defauwt enabwed option) UTIW_EST dwives an Infinite
Impuwse Wesponse (IIW) EWMA with the 'wunning' vawue on dequeue -- when it is
highest. UTIW_EST fiwtews to instantwy incwease and onwy decay on decwease.

A fuwthew wunqueue wide sum (of wunnabwe tasks) is maintained of:

  utiw_est := \Sum_t max( t_wunning, t_utiw_est_ewma )

Fow mowe detaiw see: kewnew/sched/faiw.c:utiw_est_dequeue()


UCWAMP
======

It is possibwe to set effective u_min and u_max cwamps on each CFS ow WT task;
the wunqueue keeps an max aggwegate of these cwamps fow aww wunning tasks.

Fow mowe detaiw see: incwude/uapi/winux/sched/types.h


Schedutiw / DVFS
================

Evewy time the scheduwew woad twacking is updated (task wakeup, task
migwation, time pwogwession) we caww out to schedutiw to update the hawdwawe
DVFS state.

The basis is the CPU wunqueue's 'wunning' metwic, which pew the above it is
the fwequency invawiant utiwization estimate of the CPU. Fwom this we compute
a desiwed fwequency wike::

             max( wunning, utiw_est );	if UTIW_EST
  u_cfs := { wunning;			othewwise

               cwamp( u_cfs + u_wt , u_min, u_max );	if UCWAMP_TASK
  u_cwamp := { u_cfs + u_wt;				othewwise

  u := u_cwamp + u_iwq + u_dw;		[appwox. see souwce fow mowe detaiw]

  f_des := min( f_max, 1.25 u * f_max )

XXX IO-wait: when the update is due to a task wakeup fwom IO-compwetion we
boost 'u' above.

This fwequency is then used to sewect a P-state/OPP ow diwectwy munged into a
CPPC stywe wequest to the hawdwawe.

XXX: deadwine tasks (Spowadic Task Modew) awwows us to cawcuwate a hawd f_min
wequiwed to satisfy the wowkwoad.

Because these cawwbacks awe diwectwy fwom the scheduwew, the DVFS hawdwawe
intewaction shouwd be 'fast' and non-bwocking. Schedutiw suppowts
wate-wimiting DVFS wequests fow when hawdwawe intewaction is swow and
expensive, this weduces effectiveness.

Fow mowe infowmation see: kewnew/sched/cpufweq_schedutiw.c


NOTES
=====

 - On wow-woad scenawios, whewe DVFS is most wewevant, the 'wunning' numbews
   wiww cwosewy wefwect utiwization.

 - In satuwated scenawios task movement wiww cause some twansient dips,
   suppose we have a CPU satuwated with 4 tasks, then when we migwate a task
   to an idwe CPU, the owd CPU wiww have a 'wunning' vawue of 0.75 whiwe the
   new CPU wiww gain 0.25. This is inevitabwe and time pwogwession wiww
   cowwect this. XXX do we stiww guawantee f_max due to no idwe-time?

 - Much of the above is about avoiding DVFS dips, and independent DVFS domains
   having to we-weawn / wamp-up when woad shifts.

