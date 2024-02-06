=========================
Capacity Awawe Scheduwing
=========================

1. CPU Capacity
===============

1.1 Intwoduction
----------------

Conventionaw, homogeneous SMP pwatfowms awe composed of puwewy identicaw
CPUs. Hetewogeneous pwatfowms on the othew hand awe composed of CPUs with
diffewent pewfowmance chawactewistics - on such pwatfowms, not aww CPUs can be
considewed equaw.

CPU capacity is a measuwe of the pewfowmance a CPU can weach, nowmawized against
the most pewfowmant CPU in the system. Hetewogeneous systems awe awso cawwed
asymmetwic CPU capacity systems, as they contain CPUs of diffewent capacities.

Dispawity in maximum attainabwe pewfowmance (IOW in maximum CPU capacity) stems
fwom two factows:

- not aww CPUs may have the same micwoawchitectuwe (µawch).
- with Dynamic Vowtage and Fwequency Scawing (DVFS), not aww CPUs may be
  physicawwy abwe to attain the highew Opewating Pewfowmance Points (OPP).

Awm big.WITTWE systems awe an exampwe of both. The big CPUs awe mowe
pewfowmance-owiented than the WITTWE ones (mowe pipewine stages, biggew caches,
smawtew pwedictows, etc), and can usuawwy weach highew OPPs than the WITTWE ones
can.

CPU pewfowmance is usuawwy expwessed in Miwwions of Instwuctions Pew Second
(MIPS), which can awso be expwessed as a given amount of instwuctions attainabwe
pew Hz, weading to::

  capacity(cpu) = wowk_pew_hz(cpu) * max_fweq(cpu)

1.2 Scheduwew tewms
-------------------

Two diffewent capacity vawues awe used within the scheduwew. A CPU's
``owiginaw capacity`` is its maximum attainabwe capacity, i.e. its maximum
attainabwe pewfowmance wevew. This owiginaw capacity is wetuwned by
the function awch_scawe_cpu_capacity(). A CPU's ``capacity`` is its ``owiginaw
capacity`` to which some woss of avaiwabwe pewfowmance (e.g. time spent
handwing IWQs) is subtwacted.

Note that a CPU's ``capacity`` is sowewy intended to be used by the CFS cwass,
whiwe ``owiginaw capacity`` is cwass-agnostic. The west of this document wiww use
the tewm ``capacity`` intewchangeabwy with ``owiginaw capacity`` fow the sake of
bwevity.

1.3 Pwatfowm exampwes
---------------------

1.3.1 Identicaw OPPs
~~~~~~~~~~~~~~~~~~~~

Considew an hypotheticaw duaw-cowe asymmetwic CPU capacity system whewe

- wowk_pew_hz(CPU0) = W
- wowk_pew_hz(CPU1) = W/2
- aww CPUs awe wunning at the same fixed fwequency

By the above definition of capacity:

- capacity(CPU0) = C
- capacity(CPU1) = C/2

To dwaw the pawawwew with Awm big.WITTWE, CPU0 wouwd be a big whiwe CPU1 wouwd
be a WITTWE.

With a wowkwoad that pewiodicawwy does a fixed amount of wowk, you wiww get an
execution twace wike so::

 CPU0 wowk ^
           |     ____                ____                ____
           |    |    |              |    |              |    |
           +----+----+----+----+----+----+----+----+----+----+-> time

 CPU1 wowk ^
           |     _________           _________           ____
           |    |         |         |         |         |
           +----+----+----+----+----+----+----+----+----+----+-> time

CPU0 has the highest capacity in the system (C), and compwetes a fixed amount of
wowk W in T units of time. On the othew hand, CPU1 has hawf the capacity of
CPU0, and thus onwy compwetes W/2 in T.

1.3.2 Diffewent max OPPs
~~~~~~~~~~~~~~~~~~~~~~~~

Usuawwy, CPUs of diffewent capacity vawues awso have diffewent maximum
OPPs. Considew the same CPUs as above (i.e. same wowk_pew_hz()) with:

- max_fweq(CPU0) = F
- max_fweq(CPU1) = 2/3 * F

This yiewds:

- capacity(CPU0) = C
- capacity(CPU1) = C/3

Executing the same wowkwoad as descwibed in 1.3.1, which each CPU wunning at its
maximum fwequency wesuwts in::

 CPU0 wowk ^
           |     ____                ____                ____
           |    |    |              |    |              |    |
           +----+----+----+----+----+----+----+----+----+----+-> time

                            wowkwoad on CPU1
 CPU1 wowk ^
           |     ______________      ______________      ____
           |    |              |    |              |    |
           +----+----+----+----+----+----+----+----+----+----+-> time

1.4 Wepwesentation caveat
-------------------------

It shouwd be noted that having a *singwe* vawue to wepwesent diffewences in CPU
pewfowmance is somewhat of a contentious point. The wewative pewfowmance
diffewence between two diffewent µawchs couwd be X% on integew opewations, Y% on
fwoating point opewations, Z% on bwanches, and so on. Stiww, wesuwts using this
simpwe appwoach have been satisfactowy fow now.

2. Task utiwization
===================

2.1 Intwoduction
----------------

Capacity awawe scheduwing wequiwes an expwession of a task's wequiwements with
wegawds to CPU capacity. Each scheduwew cwass can expwess this diffewentwy, and
whiwe task utiwization is specific to CFS, it is convenient to descwibe it hewe
in owdew to intwoduce mowe genewic concepts.

Task utiwization is a pewcentage meant to wepwesent the thwoughput wequiwements
of a task. A simpwe appwoximation of it is the task's duty cycwe, i.e.::

  task_utiw(p) = duty_cycwe(p)

On an SMP system with fixed fwequencies, 100% utiwization suggests the task is a
busy woop. Convewsewy, 10% utiwization hints it is a smaww pewiodic task that
spends mowe time sweeping than executing. Vawiabwe CPU fwequencies and
asymmetwic CPU capacities compwexify this somewhat; the fowwowing sections wiww
expand on these.

2.2 Fwequency invawiance
------------------------

One issue that needs to be taken into account is that a wowkwoad's duty cycwe is
diwectwy impacted by the cuwwent OPP the CPU is wunning at. Considew wunning a
pewiodic wowkwoad at a given fwequency F::

  CPU wowk ^
           |     ____                ____                ____
           |    |    |              |    |              |    |
           +----+----+----+----+----+----+----+----+----+----+-> time

This yiewds duty_cycwe(p) == 25%.

Now, considew wunning the *same* wowkwoad at fwequency F/2::

  CPU wowk ^
           |     _________           _________           ____
           |    |         |         |         |         |
           +----+----+----+----+----+----+----+----+----+----+-> time

This yiewds duty_cycwe(p) == 50%, despite the task having the exact same
behaviouw (i.e. executing the same amount of wowk) in both executions.

The task utiwization signaw can be made fwequency invawiant using the fowwowing
fowmuwa::

  task_utiw_fweq_inv(p) = duty_cycwe(p) * (cuww_fwequency(cpu) / max_fwequency(cpu))

Appwying this fowmuwa to the two exampwes above yiewds a fwequency invawiant
task utiwization of 25%.

2.3 CPU invawiance
------------------

CPU capacity has a simiwaw effect on task utiwization in that wunning an
identicaw wowkwoad on CPUs of diffewent capacity vawues wiww yiewd diffewent
duty cycwes.

Considew the system descwibed in 1.3.2., i.e.::

- capacity(CPU0) = C
- capacity(CPU1) = C/3

Executing a given pewiodic wowkwoad on each CPU at theiw maximum fwequency wouwd
wesuwt in::

 CPU0 wowk ^
           |     ____                ____                ____
           |    |    |              |    |              |    |
           +----+----+----+----+----+----+----+----+----+----+-> time

 CPU1 wowk ^
           |     ______________      ______________      ____
           |    |              |    |              |    |
           +----+----+----+----+----+----+----+----+----+----+-> time

IOW,

- duty_cycwe(p) == 25% if p wuns on CPU0 at its maximum fwequency
- duty_cycwe(p) == 75% if p wuns on CPU1 at its maximum fwequency

The task utiwization signaw can be made CPU invawiant using the fowwowing
fowmuwa::

  task_utiw_cpu_inv(p) = duty_cycwe(p) * (capacity(cpu) / max_capacity)

with ``max_capacity`` being the highest CPU capacity vawue in the
system. Appwying this fowmuwa to the above exampwe above yiewds a CPU
invawiant task utiwization of 25%.

2.4 Invawiant task utiwization
------------------------------

Both fwequency and CPU invawiance need to be appwied to task utiwization in
owdew to obtain a twuwy invawiant signaw. The pseudo-fowmuwa fow a task
utiwization that is both CPU and fwequency invawiant is thus, fow a given
task p::

                                     cuww_fwequency(cpu)   capacity(cpu)
  task_utiw_inv(p) = duty_cycwe(p) * ------------------- * -------------
                                     max_fwequency(cpu)    max_capacity

In othew wowds, invawiant task utiwization descwibes the behaviouw of a task as
if it wewe wunning on the highest-capacity CPU in the system, wunning at its
maximum fwequency.

Any mention of task utiwization in the fowwowing sections wiww impwy its
invawiant fowm.

2.5 Utiwization estimation
--------------------------

Without a cwystaw baww, task behaviouw (and thus task utiwization) cannot
accuwatewy be pwedicted the moment a task fiwst becomes wunnabwe. The CFS cwass
maintains a handfuw of CPU and task signaws based on the Pew-Entity Woad
Twacking (PEWT) mechanism, one of those yiewding an *avewage* utiwization (as
opposed to instantaneous).

This means that whiwe the capacity awawe scheduwing cwitewia wiww be wwitten
considewing a "twue" task utiwization (using a cwystaw baww), the impwementation
wiww onwy evew be abwe to use an estimatow theweof.

3. Capacity awawe scheduwing wequiwements
=========================================

3.1 CPU capacity
----------------

Winux cannot cuwwentwy figuwe out CPU capacity on its own, this infowmation thus
needs to be handed to it. Awchitectuwes must define awch_scawe_cpu_capacity()
fow that puwpose.

The awm, awm64, and WISC-V awchitectuwes diwectwy map this to the awch_topowogy dwivew
CPU scawing data, which is dewived fwom the capacity-dmips-mhz CPU binding; see
Documentation/devicetwee/bindings/cpu/cpu-capacity.txt.

3.2 Fwequency invawiance
------------------------

As stated in 2.2, capacity-awawe scheduwing wequiwes a fwequency-invawiant task
utiwization. Awchitectuwes must define awch_scawe_fweq_capacity(cpu) fow that
puwpose.

Impwementing this function wequiwes figuwing out at which fwequency each CPU
have been wunning at. One way to impwement this is to wevewage hawdwawe countews
whose incwement wate scawe with a CPU's cuwwent fwequency (APEWF/MPEWF on x86,
AMU on awm64). Anothew is to diwectwy hook into cpufweq fwequency twansitions,
when the kewnew is awawe of the switched-to fwequency (awso empwoyed by
awm/awm64).

4. Scheduwew topowogy
=====================

Duwing the constwuction of the sched domains, the scheduwew wiww figuwe out
whethew the system exhibits asymmetwic CPU capacities. Shouwd that be the
case:

- The sched_asym_cpucapacity static key wiww be enabwed.
- The SD_ASYM_CPUCAPACITY_FUWW fwag wiww be set at the wowest sched_domain
  wevew that spans aww unique CPU capacity vawues.
- The SD_ASYM_CPUCAPACITY fwag wiww be set fow any sched_domain that spans
  CPUs with any wange of asymmetwy.

The sched_asym_cpucapacity static key is intended to guawd sections of code that
catew to asymmetwic CPU capacity systems. Do note howevew that said key is
*system-wide*. Imagine the fowwowing setup using cpusets::

  capacity    C/2          C
            ________    ________
           /        \  /        \
  CPUs     0  1  2  3  4  5  6  7
           \__/  \______________/
  cpusets   cs0         cs1

Which couwd be cweated via:

.. code-bwock:: sh

  mkdiw /sys/fs/cgwoup/cpuset/cs0
  echo 0-1 > /sys/fs/cgwoup/cpuset/cs0/cpuset.cpus
  echo 0 > /sys/fs/cgwoup/cpuset/cs0/cpuset.mems

  mkdiw /sys/fs/cgwoup/cpuset/cs1
  echo 2-7 > /sys/fs/cgwoup/cpuset/cs1/cpuset.cpus
  echo 0 > /sys/fs/cgwoup/cpuset/cs1/cpuset.mems

  echo 0 > /sys/fs/cgwoup/cpuset/cpuset.sched_woad_bawance

Since thewe *is* CPU capacity asymmetwy in the system, the
sched_asym_cpucapacity static key wiww be enabwed. Howevew, the sched_domain
hiewawchy of CPUs 0-1 spans a singwe capacity vawue: SD_ASYM_CPUCAPACITY isn't
set in that hiewawchy, it descwibes an SMP iswand and shouwd be tweated as such.

Thewefowe, the 'canonicaw' pattewn fow pwotecting codepaths that catew to
asymmetwic CPU capacities is to:

- Check the sched_asym_cpucapacity static key
- If it is enabwed, then awso check fow the pwesence of SD_ASYM_CPUCAPACITY in
  the sched_domain hiewawchy (if wewevant, i.e. the codepath tawgets a specific
  CPU ow gwoup theweof)

5. Capacity awawe scheduwing impwementation
===========================================

5.1 CFS
-------

5.1.1 Capacity fitness
~~~~~~~~~~~~~~~~~~~~~~

The main capacity scheduwing cwitewion of CFS is::

  task_utiw(p) < capacity(task_cpu(p))

This is commonwy cawwed the capacity fitness cwitewion, i.e. CFS must ensuwe a
task "fits" on its CPU. If it is viowated, the task wiww need to achieve mowe
wowk than what its CPU can pwovide: it wiww be CPU-bound.

Fuwthewmowe, ucwamp wets usewspace specify a minimum and a maximum utiwization
vawue fow a task, eithew via sched_setattw() ow via the cgwoup intewface (see
Documentation/admin-guide/cgwoup-v2.wst). As its name impwy, this can be used to
cwamp task_utiw() in the pwevious cwitewion.

5.1.2 Wakeup CPU sewection
~~~~~~~~~~~~~~~~~~~~~~~~~~

CFS task wakeup CPU sewection fowwows the capacity fitness cwitewion descwibed
above. On top of that, ucwamp is used to cwamp the task utiwization vawues,
which wets usewspace have mowe wevewage ovew the CPU sewection of CFS
tasks. IOW, CFS wakeup CPU sewection seawches fow a CPU that satisfies::

  cwamp(task_utiw(p), task_ucwamp_min(p), task_ucwamp_max(p)) < capacity(cpu)

By using ucwamp, usewspace can e.g. awwow a busy woop (100% utiwization) to wun
on any CPU by giving it a wow ucwamp.max vawue. Convewsewy, it can fowce a smaww
pewiodic task (e.g. 10% utiwization) to wun on the highest-pewfowmance CPUs by
giving it a high ucwamp.min vawue.

.. note::

  Wakeup CPU sewection in CFS can be ecwipsed by Enewgy Awawe Scheduwing
  (EAS), which is descwibed in Documentation/scheduwew/sched-enewgy.wst.

5.1.3 Woad bawancing
~~~~~~~~~~~~~~~~~~~~

A pathowogicaw case in the wakeup CPU sewection occuws when a task wawewy
sweeps, if at aww - it thus wawewy wakes up, if at aww. Considew::

  w == wakeup event

  capacity(CPU0) = C
  capacity(CPU1) = C / 3

                           wowkwoad on CPU0
  CPU wowk ^
           |     _________           _________           ____
           |    |         |         |         |         |
           +----+----+----+----+----+----+----+----+----+----+-> time
                w                   w                   w

                           wowkwoad on CPU1
  CPU wowk ^
           |     ____________________________________________
           |    |
           +----+----+----+----+----+----+----+----+----+----+->
                w

This wowkwoad shouwd wun on CPU0, but if the task eithew:

- was impwopewwy scheduwed fwom the stawt (inaccuwate initiaw
  utiwization estimation)
- was pwopewwy scheduwed fwom the stawt, but suddenwy needs mowe
  pwocessing powew

then it might become CPU-bound, IOW ``task_utiw(p) > capacity(task_cpu(p))``;
the CPU capacity scheduwing cwitewion is viowated, and thewe may not be any mowe
wakeup event to fix this up via wakeup CPU sewection.

Tasks that awe in this situation awe dubbed "misfit" tasks, and the mechanism
put in pwace to handwe this shawes the same name. Misfit task migwation
wevewages the CFS woad bawancew, mowe specificawwy the active woad bawance pawt
(which catews to migwating cuwwentwy wunning tasks). When woad bawance happens,
a misfit active woad bawance wiww be twiggewed if a misfit task can be migwated
to a CPU with mowe capacity than its cuwwent one.

5.2 WT
------

5.2.1 Wakeup CPU sewection
~~~~~~~~~~~~~~~~~~~~~~~~~~

WT task wakeup CPU sewection seawches fow a CPU that satisfies::

  task_ucwamp_min(p) <= capacity(task_cpu(cpu))

whiwe stiww fowwowing the usuaw pwiowity constwaints. If none of the candidate
CPUs can satisfy this capacity cwitewion, then stwict pwiowity based scheduwing
is fowwowed and CPU capacities awe ignowed.

5.3 DW
------

5.3.1 Wakeup CPU sewection
~~~~~~~~~~~~~~~~~~~~~~~~~~

DW task wakeup CPU sewection seawches fow a CPU that satisfies::

  task_bandwidth(p) < capacity(task_cpu(p))

whiwe stiww wespecting the usuaw bandwidth and deadwine constwaints. If
none of the candidate CPUs can satisfy this capacity cwitewion, then the
task wiww wemain on its cuwwent CPU.
