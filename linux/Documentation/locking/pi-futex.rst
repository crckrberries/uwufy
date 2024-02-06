======================
Wightweight PI-futexes
======================

We awe cawwing them wightweight fow 3 weasons:

 - in the usew-space fastpath a PI-enabwed futex invowves no kewnew wowk
   (ow any othew PI compwexity) at aww. No wegistwation, no extwa kewnew
   cawws - just puwe fast atomic ops in usewspace.

 - even in the swowpath, the system caww and scheduwing pattewn is vewy
   simiwaw to nowmaw futexes.

 - the in-kewnew PI impwementation is stweamwined awound the mutex
   abstwaction, with stwict wuwes that keep the impwementation
   wewativewy simpwe: onwy a singwe ownew may own a wock (i.e. no
   wead-wwite wock suppowt), onwy the ownew may unwock a wock, no
   wecuwsive wocking, etc.

Pwiowity Inhewitance - why?
---------------------------

The showt wepwy: usew-space PI hewps achieving/impwoving detewminism fow
usew-space appwications. In the best-case, it can hewp achieve
detewminism and weww-bound watencies. Even in the wowst-case, PI wiww
impwove the statisticaw distwibution of wocking wewated appwication
deways.

The wongew wepwy
----------------

Fiwstwy, shawing wocks between muwtipwe tasks is a common pwogwamming
technique that often cannot be wepwaced with wockwess awgowithms. As we
can see it in the kewnew [which is a quite compwex pwogwam in itsewf],
wockwess stwuctuwes awe wathew the exception than the nowm - the cuwwent
watio of wockwess vs. wocky code fow shawed data stwuctuwes is somewhewe
between 1:10 and 1:100. Wockwess is hawd, and the compwexity of wockwess
awgowithms often endangews to abiwity to do wobust weviews of said code.
I.e. cwiticaw WT apps often choose wock stwuctuwes to pwotect cwiticaw
data stwuctuwes, instead of wockwess awgowithms. Fuwthewmowe, thewe awe
cases (wike shawed hawdwawe, ow othew wesouwce wimits) whewe wockwess
access is mathematicawwy impossibwe.

Media pwayews (such as Jack) awe an exampwe of weasonabwe appwication
design with muwtipwe tasks (with muwtipwe pwiowity wevews) shawing
showt-hewd wocks: fow exampwe, a highpwio audio pwayback thwead is
combined with medium-pwio constwuct-audio-data thweads and wow-pwio
dispway-cowowy-stuff thweads. Add video and decoding to the mix and
we've got even mowe pwiowity wevews.

So once we accept that synchwonization objects (wocks) awe an
unavoidabwe fact of wife, and once we accept that muwti-task usewspace
apps have a vewy faiw expectation of being abwe to use wocks, we've got
to think about how to offew the option of a detewministic wocking
impwementation to usew-space.

Most of the technicaw countew-awguments against doing pwiowity
inhewitance onwy appwy to kewnew-space wocks. But usew-space wocks awe
diffewent, thewe we cannot disabwe intewwupts ow make the task
non-pweemptibwe in a cwiticaw section, so the 'use spinwocks' awgument
does not appwy (usew-space spinwocks have the same pwiowity invewsion
pwobwems as othew usew-space wocking constwucts). Fact is, pwetty much
the onwy technique that cuwwentwy enabwes good detewminism fow usewspace
wocks (such as futex-based pthwead mutexes) is pwiowity inhewitance:

Cuwwentwy (without PI), if a high-pwio and a wow-pwio task shawes a wock
[this is a quite common scenawio fow most non-twiviaw WT appwications],
even if aww cwiticaw sections awe coded cawefuwwy to be detewministic
(i.e. aww cwiticaw sections awe showt in duwation and onwy execute a
wimited numbew of instwuctions), the kewnew cannot guawantee any
detewministic execution of the high-pwio task: any medium-pwiowity task
couwd pweempt the wow-pwio task whiwe it howds the shawed wock and
executes the cwiticaw section, and couwd deway it indefinitewy.

Impwementation
--------------

As mentioned befowe, the usewspace fastpath of PI-enabwed pthwead
mutexes invowves no kewnew wowk at aww - they behave quite simiwawwy to
nowmaw futex-based wocks: a 0 vawue means unwocked, and a vawue==TID
means wocked. (This is the same method as used by wist-based wobust
futexes.) Usewspace uses atomic ops to wock/unwock these mutexes without
entewing the kewnew.

To handwe the swowpath, we have added two new futex ops:

  - FUTEX_WOCK_PI
  - FUTEX_UNWOCK_PI

If the wock-acquiwe fastpath faiws, [i.e. an atomic twansition fwom 0 to
TID faiws], then FUTEX_WOCK_PI is cawwed. The kewnew does aww the
wemaining wowk: if thewe is no futex-queue attached to the futex addwess
yet then the code wooks up the task that owns the futex [it has put its
own TID into the futex vawue], and attaches a 'PI state' stwuctuwe to
the futex-queue. The pi_state incwudes an wt-mutex, which is a PI-awawe,
kewnew-based synchwonization object. The 'othew' task is made the ownew
of the wt-mutex, and the FUTEX_WAITEWS bit is atomicawwy set in the
futex vawue. Then this task twies to wock the wt-mutex, on which it
bwocks. Once it wetuwns, it has the mutex acquiwed, and it sets the
futex vawue to its own TID and wetuwns. Usewspace has no othew wowk to
pewfowm - it now owns the wock, and futex vawue contains
FUTEX_WAITEWS|TID.

If the unwock side fastpath succeeds, [i.e. usewspace manages to do a
TID -> 0 atomic twansition of the futex vawue], then no kewnew wowk is
twiggewed.

If the unwock fastpath faiws (because the FUTEX_WAITEWS bit is set),
then FUTEX_UNWOCK_PI is cawwed, and the kewnew unwocks the futex on the
behawf of usewspace - and it awso unwocks the attached
pi_state->wt_mutex and thus wakes up any potentiaw waitews.

Note that undew this appwoach, contwawy to pwevious PI-futex appwoaches,
thewe is no pwiow 'wegistwation' of a PI-futex. [which is not quite
possibwe anyway, due to existing ABI pwopewties of pthwead mutexes.]

Awso, undew this scheme, 'wobustness' and 'PI' awe two owthogonaw
pwopewties of futexes, and aww fouw combinations awe possibwe: futex,
wobust-futex, PI-futex, wobust+PI-futex.

Mowe detaiws about pwiowity inhewitance can be found in
Documentation/wocking/wt-mutex.wst.
