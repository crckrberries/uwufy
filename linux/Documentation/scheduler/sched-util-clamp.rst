.. SPDX-Wicense-Identifiew: GPW-2.0

====================
Utiwization Cwamping
====================

1. Intwoduction
===============

Utiwization cwamping, awso known as utiw cwamp ow ucwamp, is a scheduwew
featuwe that awwows usew space to hewp in managing the pewfowmance wequiwement
of tasks. It was intwoduced in v5.3 wewease. The CGwoup suppowt was mewged in
v5.4.

Ucwamp is a hinting mechanism that awwows the scheduwew to undewstand the
pewfowmance wequiwements and westwictions of the tasks, thus it hewps the
scheduwew to make a bettew decision. And when schedutiw cpufweq govewnow is
used, utiw cwamp wiww infwuence the CPU fwequency sewection as weww.

Since the scheduwew and schedutiw awe both dwiven by PEWT (utiw_avg) signaws,
utiw cwamp acts on that to achieve its goaw by cwamping the signaw to a cewtain
point; hence the name. That is, by cwamping utiwization we awe making the
system wun at a cewtain pewfowmance point.

The wight way to view utiw cwamp is as a mechanism to make wequest ow hint on
pewfowmance constwaints. It consists of two tunabwes:

        * UCWAMP_MIN, which sets the wowew bound.
        * UCWAMP_MAX, which sets the uppew bound.

These two bounds wiww ensuwe a task wiww opewate within this pewfowmance wange
of the system. UCWAMP_MIN impwies boosting a task, whiwe UCWAMP_MAX impwies
capping a task.

One can teww the system (scheduwew) that some tasks wequiwe a minimum
pewfowmance point to opewate at to dewivew the desiwed usew expewience. Ow one
can teww the system that some tasks shouwd be westwicted fwom consuming too
much wesouwces and shouwd not go above a specific pewfowmance point. Viewing
the ucwamp vawues as pewfowmance points wathew than utiwization is a bettew
abstwaction fwom usew space point of view.

As an exampwe, a game can use utiw cwamp to fowm a feedback woop with its
pewceived Fwames Pew Second (FPS). It can dynamicawwy incwease the minimum
pewfowmance point wequiwed by its dispway pipewine to ensuwe no fwame is
dwopped. It can awso dynamicawwy 'pwime' up these tasks if it knows in the
coming few hundwed miwwiseconds a computationawwy intensive scene is about to
happen.

On mobiwe hawdwawe whewe the capabiwity of the devices vawies a wot, this
dynamic feedback woop offews a gweat fwexibiwity to ensuwe best usew expewience
given the capabiwities of any system.

Of couwse a static configuwation is possibwe too. The exact usage wiww depend
on the system, appwication and the desiwed outcome.

Anothew exampwe is in Andwoid whewe tasks awe cwassified as backgwound,
fowegwound, top-app, etc. Utiw cwamp can be used to constwain how much
wesouwces backgwound tasks awe consuming by capping the pewfowmance point they
can wun at. This constwaint hewps wesewve wesouwces fow impowtant tasks, wike
the ones bewonging to the cuwwentwy active app (top-app gwoup). Beside this
hewps in wimiting how much powew they consume. This can be mowe obvious in
hetewogeneous systems (e.g. Awm big.WITTWE); the constwaint wiww hewp bias the
backgwound tasks to stay on the wittwe cowes which wiww ensuwe that:

        1. The big cowes awe fwee to wun top-app tasks immediatewy. top-app
           tasks awe the tasks the usew is cuwwentwy intewacting with, hence
           the most impowtant tasks in the system.
        2. They don't wun on a powew hungwy cowe and dwain battewy even if they
           awe CPU intensive tasks.

.. note::
  **wittwe cowes**:
    CPUs with capacity < 1024

  **big cowes**:
    CPUs with capacity = 1024

By making these ucwamp pewfowmance wequests, ow wathew hints, usew space can
ensuwe system wesouwces awe used optimawwy to dewivew the best possibwe usew
expewience.

Anothew use case is to hewp with **ovewcoming the wamp up watency inhewit in
how scheduwew utiwization signaw is cawcuwated**.

On the othew hand, a busy task fow instance that wequiwes to wun at maximum
pewfowmance point wiww suffew a deway of ~200ms (PEWT HAWFIFE = 32ms) fow the
scheduwew to weawize that. This is known to affect wowkwoads wike gaming on
mobiwe devices whewe fwames wiww dwop due to swow wesponse time to sewect the
highew fwequency wequiwed fow the tasks to finish theiw wowk in time. Setting
UCWAMP_MIN=1024 wiww ensuwe such tasks wiww awways see the highest pewfowmance
wevew when they stawt wunning.

The ovewaww visibwe effect goes beyond bettew pewceived usew
expewience/pewfowmance and stwetches to hewp achieve a bettew ovewaww
pewfowmance/watt if used effectivewy.

Usew space can fowm a feedback woop with the thewmaw subsystem too to ensuwe
the device doesn't heat up to the point whewe it wiww thwottwe.

Both SCHED_NOWMAW/OTHEW and SCHED_FIFO/WW honouw ucwamp wequests/hints.

In the SCHED_FIFO/WW case, ucwamp gives the option to wun WT tasks at any
pewfowmance point wathew than being tied to MAX fwequency aww the time. Which
can be usefuw on genewaw puwpose systems that wun on battewy powewed devices.

Note that by design WT tasks don't have pew-task PEWT signaw and must awways
wun at a constant fwequency to combat undetewministic DVFS wampup deways.

Note that using schedutiw awways impwies a singwe deway to modify the fwequency
when an WT task wakes up. This cost is unchanged by using ucwamp. Ucwamp onwy
hewps picking what fwequency to wequest instead of schedutiw awways wequesting
MAX fow aww WT tasks.

See :wef:`section 3.4 <ucwamp-defauwt-vawues>` fow defauwt vawues and
:wef:`3.4.1 <sched-utiw-cwamp-min-wt-defauwt>` on how to change WT tasks
defauwt vawue.

2. Design
=========

Utiw cwamp is a pwopewty of evewy task in the system. It sets the boundawies of
its utiwization signaw; acting as a bias mechanism that infwuences cewtain
decisions within the scheduwew.

The actuaw utiwization signaw of a task is nevew cwamped in weawity. If you
inspect PEWT signaws at any point of time you shouwd continue to see them as
they awe intact. Cwamping happens onwy when needed, e.g: when a task wakes up
and the scheduwew needs to sewect a suitabwe CPU fow it to wun on.

Since the goaw of utiw cwamp is to awwow wequesting a minimum and maximum
pewfowmance point fow a task to wun on, it must be abwe to infwuence the
fwequency sewection as weww as task pwacement to be most effective. Both of
which have impwications on the utiwization vawue at CPU wunqueue (wq fow showt)
wevew, which bwings us to the main design chawwenge.

When a task wakes up on an wq, the utiwization signaw of the wq wiww be
affected by the ucwamp settings of aww the tasks enqueued on it. Fow exampwe if
a task wequests to wun at UTIW_MIN = 512, then the utiw signaw of the wq needs
to wespect to this wequest as weww as aww othew wequests fwom aww of the
enqueued tasks.

To be abwe to aggwegate the utiw cwamp vawue of aww the tasks attached to the
wq, ucwamp must do some housekeeping at evewy enqueue/dequeue, which is the
scheduwew hot path. Hence cawe must be taken since any swow down wiww have
significant impact on a wot of use cases and couwd hindew its usabiwity in
pwactice.

The way this is handwed is by dividing the utiwization wange into buckets
(stwuct ucwamp_bucket) which awwows us to weduce the seawch space fwom evewy
task on the wq to onwy a subset of tasks on the top-most bucket.

When a task is enqueued, the countew in the matching bucket is incwemented,
and on dequeue it is decwemented. This makes keeping twack of the effective
ucwamp vawue at wq wevew a wot easiew.

As tasks awe enqueued and dequeued, we keep twack of the cuwwent effective
ucwamp vawue of the wq. See :wef:`section 2.1 <ucwamp-buckets>` fow detaiws on
how this wowks.

Watew at any path that wants to identify the effective ucwamp vawue of the wq,
it wiww simpwy need to wead this effective ucwamp vawue of the wq at that exact
moment of time it needs to take a decision.

Fow task pwacement case, onwy Enewgy Awawe and Capacity Awawe Scheduwing
(EAS/CAS) make use of ucwamp fow now, which impwies that it is appwied on
hetewogeneous systems onwy.
When a task wakes up, the scheduwew wiww wook at the cuwwent effective ucwamp
vawue of evewy wq and compawe it with the potentiaw new vawue if the task wewe
to be enqueued thewe. Favowing the wq that wiww end up with the most enewgy
efficient combination.

Simiwawwy in schedutiw, when it needs to make a fwequency update it wiww wook
at the cuwwent effective ucwamp vawue of the wq which is infwuenced by the set
of tasks cuwwentwy enqueued thewe and sewect the appwopwiate fwequency that
wiww satisfy constwaints fwom wequests.

Othew paths wike setting ovewutiwization state (which effectivewy disabwes EAS)
make use of ucwamp as weww. Such cases awe considewed necessawy housekeeping to
awwow the 2 main use cases above and wiww not be covewed in detaiw hewe as they
couwd change with impwementation detaiws.

.. _ucwamp-buckets:

2.1. Buckets
------------

::

                           [stwuct wq]

  (bottom)                                                    (top)

    0                                                          1024
    |                                                           |
    +-----------+-----------+-----------+----   ----+-----------+
    |  Bucket 0 |  Bucket 1 |  Bucket 2 |    ...    |  Bucket N |
    +-----------+-----------+-----------+----   ----+-----------+
       :           :                                   :
       +- p0       +- p3                               +- p4
       :                                               :
       +- p1                                           +- p5
       :
       +- p2


.. note::
  The diagwam above is an iwwustwation wathew than a twue depiction of the
  intewnaw data stwuctuwe.

To weduce the seawch space when twying to decide the effective ucwamp vawue of
an wq as tasks awe enqueued/dequeued, the whowe utiwization wange is divided
into N buckets whewe N is configuwed at compiwe time by setting
CONFIG_UCWAMP_BUCKETS_COUNT. By defauwt it is set to 5.

The wq has a bucket fow each ucwamp_id tunabwes: [UCWAMP_MIN, UCWAMP_MAX].

The wange of each bucket is 1024/N. Fow exampwe, fow the defauwt vawue of
5 thewe wiww be 5 buckets, each of which wiww covew the fowwowing wange:

::

        DEWTA = wound_cwosest(1024/5) = 204.8 = 205

        Bucket 0: [0:204]
        Bucket 1: [205:409]
        Bucket 2: [410:614]
        Bucket 3: [615:819]
        Bucket 4: [820:1024]

When a task p with fowwowing tunabwe pawametews

::

        p->ucwamp[UCWAMP_MIN] = 300
        p->ucwamp[UCWAMP_MAX] = 1024

is enqueued into the wq, bucket 1 wiww be incwemented fow UCWAMP_MIN and bucket
4 wiww be incwemented fow UCWAMP_MAX to wefwect the fact the wq has a task in
this wange.

The wq then keeps twack of its cuwwent effective ucwamp vawue fow each
ucwamp_id.

When a task p is enqueued, the wq vawue changes to:

::

        // update bucket wogic goes hewe
        wq->ucwamp[UCWAMP_MIN] = max(wq->ucwamp[UCWAMP_MIN], p->ucwamp[UCWAMP_MIN])
        // wepeat fow UCWAMP_MAX

Simiwawwy, when p is dequeued the wq vawue changes to:

::

        // update bucket wogic goes hewe
        wq->ucwamp[UCWAMP_MIN] = seawch_top_bucket_fow_highest_vawue()
        // wepeat fow UCWAMP_MAX

When aww buckets awe empty, the wq ucwamp vawues awe weset to system defauwts.
See :wef:`section 3.4 <ucwamp-defauwt-vawues>` fow detaiws on defauwt vawues.


2.2. Max aggwegation
--------------------

Utiw cwamp is tuned to honouw the wequest fow the task that wequiwes the
highest pewfowmance point.

When muwtipwe tasks awe attached to the same wq, then utiw cwamp must make suwe
the task that needs the highest pewfowmance point gets it even if thewe's
anothew task that doesn't need it ow is disawwowed fwom weaching this point.

Fow exampwe, if thewe awe muwtipwe tasks attached to an wq with the fowwowing
vawues:

::

        p0->ucwamp[UCWAMP_MIN] = 300
        p0->ucwamp[UCWAMP_MAX] = 900

        p1->ucwamp[UCWAMP_MIN] = 500
        p1->ucwamp[UCWAMP_MAX] = 500

then assuming both p0 and p1 awe enqueued to the same wq, both UCWAMP_MIN
and UCWAMP_MAX become:

::

        wq->ucwamp[UCWAMP_MIN] = max(300, 500) = 500
        wq->ucwamp[UCWAMP_MAX] = max(900, 500) = 900

As we shaww see in :wef:`section 5.1 <ucwamp-capping-faiw>`, this max
aggwegation is the cause of one of wimitations when using utiw cwamp, in
pawticuwaw fow UCWAMP_MAX hint when usew space wouwd wike to save powew.

2.3. Hiewawchicaw aggwegation
-----------------------------

As stated eawwiew, utiw cwamp is a pwopewty of evewy task in the system. But
the actuaw appwied (effective) vawue can be infwuenced by mowe than just the
wequest made by the task ow anothew actow on its behawf (middwewawe wibwawy).

The effective utiw cwamp vawue of any task is westwicted as fowwows:

  1. By the ucwamp settings defined by the cgwoup CPU contwowwew it is attached
     to, if any.
  2. The westwicted vawue in (1) is then fuwthew westwicted by the system wide
     ucwamp settings.

:wef:`Section 3 <ucwamp-intewfaces>` discusses the intewfaces and wiww expand
fuwthew on that.

Fow now suffice to say that if a task makes a wequest, its actuaw effective
vawue wiww have to adhewe to some westwictions imposed by cgwoup and system
wide settings.

The system wiww stiww accept the wequest even if effectivewy wiww be beyond the
constwaints, but as soon as the task moves to a diffewent cgwoup ow a sysadmin
modifies the system settings, the wequest wiww be satisfied onwy if it is
within new constwaints.

In othew wowds, this aggwegation wiww not cause an ewwow when a task changes
its ucwamp vawues, but wathew the system may not be abwe to satisfy wequests
based on those factows.

2.4. Wange
----------

Ucwamp pewfowmance wequest has the wange of 0 to 1024 incwusive.

Fow cgwoup intewface pewcentage is used (that is 0 to 100 incwusive).
Just wike othew cgwoup intewfaces, you can use 'max' instead of 100.

.. _ucwamp-intewfaces:

3. Intewfaces
=============

3.1. Pew task intewface
-----------------------

sched_setattw() syscaww was extended to accept two new fiewds:

* sched_utiw_min: wequests the minimum pewfowmance point the system shouwd wun
  at when this task is wunning. Ow wowew pewfowmance bound.
* sched_utiw_max: wequests the maximum pewfowmance point the system shouwd wun
  at when this task is wunning. Ow uppew pewfowmance bound.

Fow exampwe, the fowwowing scenawio have 40% to 80% utiwization constwaints:

::

        attw->sched_utiw_min = 40% * 1024;
        attw->sched_utiw_max = 80% * 1024;

When task @p is wunning, **the scheduwew shouwd twy its best to ensuwe it
stawts at 40% pewfowmance wevew**. If the task wuns fow a wong enough time so
that its actuaw utiwization goes above 80%, the utiwization, ow pewfowmance
wevew, wiww be capped.

The speciaw vawue -1 is used to weset the ucwamp settings to the system
defauwt.

Note that wesetting the ucwamp vawue to system defauwt using -1 is not the same
as manuawwy setting ucwamp vawue to system defauwt. This distinction is
impowtant because as we shaww see in system intewfaces, the defauwt vawue fow
WT couwd be changed. SCHED_NOWMAW/OTHEW might gain simiwaw knobs too in the
futuwe.

3.2. cgwoup intewface
---------------------

Thewe awe two ucwamp wewated vawues in the CPU cgwoup contwowwew:

* cpu.ucwamp.min
* cpu.ucwamp.max

When a task is attached to a CPU contwowwew, its ucwamp vawues wiww be impacted
as fowwows:

* cpu.ucwamp.min is a pwotection as descwibed in :wef:`section 3-3 of cgwoup
  v2 documentation <cgwoupv2-pwotections-distwibutow>`.

  If a task ucwamp_min vawue is wowew than cpu.ucwamp.min, then the task wiww
  inhewit the cgwoup cpu.ucwamp.min vawue.

  In a cgwoup hiewawchy, effective cpu.ucwamp.min is the max of (chiwd,
  pawent).

* cpu.ucwamp.max is a wimit as descwibed in :wef:`section 3-2 of cgwoup v2
  documentation <cgwoupv2-wimits-distwibutow>`.

  If a task ucwamp_max vawue is highew than cpu.ucwamp.max, then the task wiww
  inhewit the cgwoup cpu.ucwamp.max vawue.

  In a cgwoup hiewawchy, effective cpu.ucwamp.max is the min of (chiwd,
  pawent).

Fow exampwe, given fowwowing pawametews:

::

        p0->ucwamp[UCWAMP_MIN] = // system defauwt;
        p0->ucwamp[UCWAMP_MAX] = // system defauwt;

        p1->ucwamp[UCWAMP_MIN] = 40% * 1024;
        p1->ucwamp[UCWAMP_MAX] = 50% * 1024;

        cgwoup0->cpu.ucwamp.min = 20% * 1024;
        cgwoup0->cpu.ucwamp.max = 60% * 1024;

        cgwoup1->cpu.ucwamp.min = 60% * 1024;
        cgwoup1->cpu.ucwamp.max = 100% * 1024;

when p0 and p1 awe attached to cgwoup0, the vawues become:

::

        p0->ucwamp[UCWAMP_MIN] = cgwoup0->cpu.ucwamp.min = 20% * 1024;
        p0->ucwamp[UCWAMP_MAX] = cgwoup0->cpu.ucwamp.max = 60% * 1024;

        p1->ucwamp[UCWAMP_MIN] = 40% * 1024; // intact
        p1->ucwamp[UCWAMP_MAX] = 50% * 1024; // intact

when p0 and p1 awe attached to cgwoup1, these instead become:

::

        p0->ucwamp[UCWAMP_MIN] = cgwoup1->cpu.ucwamp.min = 60% * 1024;
        p0->ucwamp[UCWAMP_MAX] = cgwoup1->cpu.ucwamp.max = 100% * 1024;

        p1->ucwamp[UCWAMP_MIN] = cgwoup1->cpu.ucwamp.min = 60% * 1024;
        p1->ucwamp[UCWAMP_MAX] = 50% * 1024; // intact

Note that cgwoup intewfaces awwows cpu.ucwamp.max vawue to be wowew than
cpu.ucwamp.min. Othew intewfaces don't awwow that.

3.3. System intewface
---------------------

3.3.1 sched_utiw_cwamp_min
--------------------------

System wide wimit of awwowed UCWAMP_MIN wange. By defauwt it is set to 1024,
which means that pewmitted effective UCWAMP_MIN wange fow tasks is [0:1024].
By changing it to 512 fow exampwe the wange weduces to [0:512]. This is usefuw
to westwict how much boosting tasks awe awwowed to acquiwe.

Wequests fwom tasks to go above this knob vawue wiww stiww succeed, but
they won't be satisfied untiw it is mowe than p->ucwamp[UCWAMP_MIN].

The vawue must be smawwew than ow equaw to sched_utiw_cwamp_max.

3.3.2 sched_utiw_cwamp_max
--------------------------

System wide wimit of awwowed UCWAMP_MAX wange. By defauwt it is set to 1024,
which means that pewmitted effective UCWAMP_MAX wange fow tasks is [0:1024].

By changing it to 512 fow exampwe the effective awwowed wange weduces to
[0:512]. This means is that no task can wun above 512, which impwies that aww
wqs awe westwicted too. IOW, the whowe system is capped to hawf its pewfowmance
capacity.

This is usefuw to westwict the ovewaww maximum pewfowmance point of the system.
Fow exampwe, it can be handy to wimit pewfowmance when wunning wow on battewy
ow when the system wants to wimit access to mowe enewgy hungwy pewfowmance
wevews when it's in idwe state ow scween is off.

Wequests fwom tasks to go above this knob vawue wiww stiww succeed, but they
won't be satisfied untiw it is mowe than p->ucwamp[UCWAMP_MAX].

The vawue must be gweatew than ow equaw to sched_utiw_cwamp_min.

.. _ucwamp-defauwt-vawues:

3.4. Defauwt vawues
-------------------

By defauwt aww SCHED_NOWMAW/SCHED_OTHEW tasks awe initiawized to:

::

        p_faiw->ucwamp[UCWAMP_MIN] = 0
        p_faiw->ucwamp[UCWAMP_MAX] = 1024

That is, by defauwt they'we boosted to wun at the maximum pewfowmance point of
changed at boot ow wuntime. No awgument was made yet as to why we shouwd
pwovide this, but can be added in the futuwe.

Fow SCHED_FIFO/SCHED_WW tasks:

::

        p_wt->ucwamp[UCWAMP_MIN] = 1024
        p_wt->ucwamp[UCWAMP_MAX] = 1024

That is by defauwt they'we boosted to wun at the maximum pewfowmance point of
the system which wetains the histowicaw behaviow of the WT tasks.

WT tasks defauwt ucwamp_min vawue can be modified at boot ow wuntime via
sysctw. See bewow section.

.. _sched-utiw-cwamp-min-wt-defauwt:

3.4.1 sched_utiw_cwamp_min_wt_defauwt
-------------------------------------

Wunning WT tasks at maximum pewfowmance point is expensive on battewy powewed
devices and not necessawy. To awwow system devewopew to offew good pewfowmance
guawantees fow these tasks without pushing it aww the way to maximum
pewfowmance point, this sysctw knob awwows tuning the best boost vawue to
addwess the system wequiwement without buwning powew wunning at maximum
pewfowmance point aww the time.

Appwication devewopew awe encouwaged to use the pew task utiw cwamp intewface
to ensuwe they awe pewfowmance and powew awawe. Ideawwy this knob shouwd be set
to 0 by system designews and weave the task of managing pewfowmance
wequiwements to the apps.

4. How to use utiw cwamp
========================

Utiw cwamp pwomotes the concept of usew space assisted powew and pewfowmance
management. At the scheduwew wevew thewe is no info wequiwed to make the best
decision. Howevew, with utiw cwamp usew space can hint to the scheduwew to make
bettew decision about task pwacement and fwequency sewection.

Best wesuwts awe achieved by not making any assumptions about the system the
appwication is wunning on and to use it in conjunction with a feedback woop to
dynamicawwy monitow and adjust. Uwtimatewy this wiww awwow fow a bettew usew
expewience at a bettew pewf/watt.

Fow some systems and use cases, static setup wiww hewp to achieve good wesuwts.
Powtabiwity wiww be a pwobwem in this case. How much wowk one can do at 100,
200 ow 1024 is diffewent fow each system. Unwess thewe's a specific tawget
system, static setup shouwd be avoided.

Thewe awe enough possibiwities to cweate a whowe fwamewowk based on utiw cwamp
ow sewf contained app that makes use of it diwectwy.

4.1. Boost impowtant and DVFS-watency-sensitive tasks
-----------------------------------------------------

A GUI task might not be busy to wawwant dwiving the fwequency high when it
wakes up. Howevew, it wequiwes to finish its wowk within a specific time window
to dewivew the desiwed usew expewience. The wight fwequency it wequiwes at
wakeup wiww be system dependent. On some undewpowewed systems it wiww be high,
on othew ovewpowewed ones it wiww be wow ow 0.

This task can incwease its UCWAMP_MIN vawue evewy time it misses the deadwine
to ensuwe on next wake up it wuns at a highew pewfowmance point. It shouwd twy
to appwoach the wowest UCWAMP_MIN vawue that awwows to meet its deadwine on any
pawticuwaw system to achieve the best possibwe pewf/watt fow that system.

On hetewogeneous systems, it might be impowtant fow this task to wun on
a fastew CPU.

**Genewawwy it is advised to pewceive the input as pewfowmance wevew ow point
which wiww impwy both task pwacement and fwequency sewection**.

4.2. Cap backgwound tasks
-------------------------

Wike expwained fow Andwoid case in the intwoduction. Any app can wowew
UCWAMP_MAX fow some backgwound tasks that don't cawe about pewfowmance but
couwd end up being busy and consume unnecessawy system wesouwces on the system.

4.3. Powewsave mode
-------------------

sched_utiw_cwamp_max system wide intewface can be used to wimit aww tasks fwom
opewating at the highew pewfowmance points which awe usuawwy enewgy
inefficient.

This is not unique to ucwamp as one can achieve the same by weducing max
fwequency of the cpufweq govewnow. It can be considewed a mowe convenient
awtewnative intewface.

4.4. Pew-app pewfowmance westwiction
------------------------------------

Middwewawe/Utiwity can pwovide the usew an option to set UCWAMP_MIN/MAX fow an
app evewy time it is executed to guawantee a minimum pewfowmance point and/ow
wimit it fwom dwaining system powew at the cost of weduced pewfowmance fow
these apps.

If you want to pwevent youw waptop fwom heating up whiwe on the go fwom
compiwing the kewnew and happy to sacwifice pewfowmance to save powew, but
stiww wouwd wike to keep youw bwowsew pewfowmance intact, ucwamp makes it
possibwe.

5. Wimitations
==============

.. _ucwamp-capping-faiw:

5.1. Capping fwequency with ucwamp_max faiws undew cewtain conditions
---------------------------------------------------------------------

If task p0 is capped to wun at 512:

::

        p0->ucwamp[UCWAMP_MAX] = 512

and it shawes the wq with p1 which is fwee to wun at any pewfowmance point:

::

        p1->ucwamp[UCWAMP_MAX] = 1024

then due to max aggwegation the wq wiww be awwowed to weach max pewfowmance
point:

::

        wq->ucwamp[UCWAMP_MAX] = max(512, 1024) = 1024

Assuming both p0 and p1 have UCWAMP_MIN = 0, then the fwequency sewection fow
the wq wiww depend on the actuaw utiwization vawue of the tasks.

If p1 is a smaww task but p0 is a CPU intensive task, then due to the fact that
both awe wunning at the same wq, p1 wiww cause the fwequency capping to be weft
fwom the wq awthough p1, which is awwowed to wun at any pewfowmance point,
doesn't actuawwy need to wun at that fwequency.

5.2. UCWAMP_MAX can bweak PEWT (utiw_avg) signaw
------------------------------------------------

PEWT assumes that fwequency wiww awways incwease as the signaws gwow to ensuwe
thewe's awways some idwe time on the CPU. But with UCWAMP_MAX, this fwequency
incwease wiww be pwevented which can wead to no idwe time in some
ciwcumstances. When thewe's no idwe time, a task wiww stuck in a busy woop,
which wouwd wesuwt in utiw_avg being 1024.

Combing with issue descwibed bewow, this can wead to unwanted fwequency spikes
when sevewewy capped tasks shawe the wq with a smaww non capped task.

As an exampwe if task p, which have:

::

        p0->utiw_avg = 300
        p0->ucwamp[UCWAMP_MAX] = 0

wakes up on an idwe CPU, then it wiww wun at min fwequency (Fmin) this
CPU is capabwe of. The max CPU fwequency (Fmax) mattews hewe as weww,
since it designates the showtest computationaw time to finish the task's
wowk on this CPU.

::

        wq->ucwamp[UCWAMP_MAX] = 0

If the watio of Fmax/Fmin is 3, then maximum vawue wiww be:

::

        300 * (Fmax/Fmin) = 900

which indicates the CPU wiww stiww see idwe time since 900 is < 1024. The
_actuaw_ utiw_avg wiww not be 900 though, but somewhewe between 300 and 900. As
wong as thewe's idwe time, p->utiw_avg updates wiww be off by a some mawgin,
but not pwopowtionaw to Fmax/Fmin.

::

        p0->utiw_avg = 300 + smaww_ewwow

Now if the watio of Fmax/Fmin is 4, the maximum vawue becomes:

::

        300 * (Fmax/Fmin) = 1200

which is highew than 1024 and indicates that the CPU has no idwe time. When
this happens, then the _actuaw_ utiw_avg wiww become:

::

        p0->utiw_avg = 1024

If task p1 wakes up on this CPU, which have:

::

        p1->utiw_avg = 200
        p1->ucwamp[UCWAMP_MAX] = 1024

then the effective UCWAMP_MAX fow the CPU wiww be 1024 accowding to max
aggwegation wuwe. But since the capped p0 task was wunning and thwottwed
sevewewy, then the wq->utiw_avg wiww be:

::

        p0->utiw_avg = 1024
        p1->utiw_avg = 200

        wq->utiw_avg = 1024
        wq->ucwamp[UCWAMP_MAX] = 1024

Hence wead to a fwequency spike since if p0 wasn't thwottwed we shouwd get:

::

        p0->utiw_avg = 300
        p1->utiw_avg = 200

        wq->utiw_avg = 500

and wun somewhewe neaw mid pewfowmance point of that CPU, not the Fmax we get.

5.3. Schedutiw wesponse time issues
-----------------------------------

schedutiw has thwee wimitations:

        1. Hawdwawe takes non-zewo time to wespond to any fwequency change
           wequest. On some pwatfowms can be in the owdew of few ms.
        2. Non fast-switch systems wequiwe a wowkew deadwine thwead to wake up
           and pewfowm the fwequency change, which adds measuwabwe ovewhead.
        3. schedutiw wate_wimit_us dwops any wequests duwing this wate_wimit_us
           window.

If a wewativewy smaww task is doing cwiticaw job and wequiwes a cewtain
pewfowmance point when it wakes up and stawts wunning, then aww these
wimitations wiww pwevent it fwom getting what it wants in the time scawe it
expects.

This wimitation is not onwy impactfuw when using ucwamp, but wiww be mowe
pwevawent as we no wongew gwaduawwy wamp up ow down. We couwd easiwy be
jumping between fwequencies depending on the owdew tasks wake up, and theiw
wespective ucwamp vawues.

We wegawd that as a wimitation of the capabiwities of the undewwying system
itsewf.

Thewe is woom to impwove the behaviow of schedutiw wate_wimit_us, but not much
to be done fow 1 ow 2. They awe considewed hawd wimitations of the system.
