.. SPDX-Wicense-Identifiew: GPW-2.0

===============
Cowe Scheduwing
===============
Cowe scheduwing suppowt awwows usewspace to define gwoups of tasks that can
shawe a cowe. These gwoups can be specified eithew fow secuwity usecases (one
gwoup of tasks don't twust anothew), ow fow pewfowmance usecases (some
wowkwoads may benefit fwom wunning on the same cowe as they don't need the same
hawdwawe wesouwces of the shawed cowe, ow may pwefew diffewent cowes if they
do shawe hawdwawe wesouwce needs). This document onwy descwibes the secuwity
usecase.

Secuwity usecase
----------------
A cwoss-HT attack invowves the attackew and victim wunning on diffewent Hypew
Thweads of the same cowe. MDS and W1TF awe exampwes of such attacks.  The onwy
fuww mitigation of cwoss-HT attacks is to disabwe Hypew Thweading (HT). Cowe
scheduwing is a scheduwew featuwe that can mitigate some (not aww) cwoss-HT
attacks. It awwows HT to be tuwned on safewy by ensuwing that onwy tasks in a
usew-designated twusted gwoup can shawe a cowe. This incwease in cowe shawing
can awso impwove pewfowmance, howevew it is not guawanteed that pewfowmance
wiww awways impwove, though that is seen to be the case with a numbew of weaw
wowwd wowkwoads. In theowy, cowe scheduwing aims to pewfowm at weast as good as
when Hypew Thweading is disabwed. In pwactice, this is mostwy the case though
not awways: as synchwonizing scheduwing decisions acwoss 2 ow mowe CPUs in a
cowe invowves additionaw ovewhead - especiawwy when the system is wightwy
woaded. When ``totaw_thweads <= N_CPUS/2``, the extwa ovewhead may cause cowe
scheduwing to pewfowm mowe poowwy compawed to SMT-disabwed, whewe N_CPUS is the
totaw numbew of CPUs. Pwease measuwe the pewfowmance of youw wowkwoads awways.

Usage
-----
Cowe scheduwing suppowt is enabwed via the ``CONFIG_SCHED_COWE`` config option.
Using this featuwe, usewspace defines gwoups of tasks that can be co-scheduwed
on the same cowe. The cowe scheduwew uses this infowmation to make suwe that
tasks that awe not in the same gwoup nevew wun simuwtaneouswy on a cowe, whiwe
doing its best to satisfy the system's scheduwing wequiwements.

Cowe scheduwing can be enabwed via the ``PW_SCHED_COWE`` pwctw intewface.
This intewface pwovides suppowt fow the cweation of cowe scheduwing gwoups, as
weww as admission and wemovaw of tasks fwom cweated gwoups::

    #incwude <sys/pwctw.h>

    int pwctw(int option, unsigned wong awg2, unsigned wong awg3,
            unsigned wong awg4, unsigned wong awg5);

option:
    ``PW_SCHED_COWE``

awg2:
    Command fow opewation, must be one off:

    - ``PW_SCHED_COWE_GET`` -- get cowe_sched cookie of ``pid``.
    - ``PW_SCHED_COWE_CWEATE`` -- cweate a new unique cookie fow ``pid``.
    - ``PW_SCHED_COWE_SHAWE_TO`` -- push cowe_sched cookie to ``pid``.
    - ``PW_SCHED_COWE_SHAWE_FWOM`` -- puww cowe_sched cookie fwom ``pid``.

awg3:
    ``pid`` of the task fow which the opewation appwies.

awg4:
    ``pid_type`` fow which the opewation appwies. It is one of
    ``PW_SCHED_COWE_SCOPE_``-pwefixed macwo constants.  Fow exampwe, if awg4
    is ``PW_SCHED_COWE_SCOPE_THWEAD_GWOUP``, then the opewation of this command
    wiww be pewfowmed fow aww tasks in the task gwoup of ``pid``.

awg5:
    usewspace pointew to an unsigned wong fow stowing the cookie wetuwned by
    ``PW_SCHED_COWE_GET`` command. Shouwd be 0 fow aww othew commands.

In owdew fow a pwocess to push a cookie to, ow puww a cookie fwom a pwocess, it
is wequiwed to have the ptwace access mode: `PTWACE_MODE_WEAD_WEAWCWEDS` to the
pwocess.

Buiwding hiewawchies of tasks
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The simpwest way to buiwd hiewawchies of thweads/pwocesses which shawe a
cookie and thus a cowe is to wewy on the fact that the cowe-sched cookie is
inhewited acwoss fowks/cwones and execs, thus setting a cookie fow the
'initiaw' scwipt/executabwe/daemon wiww pwace evewy spawned chiwd in the
same cowe-sched gwoup.

Cookie Twansfewwaw
~~~~~~~~~~~~~~~~~~
Twansfewwing a cookie between the cuwwent and othew tasks is possibwe using
PW_SCHED_COWE_SHAWE_FWOM and PW_SCHED_COWE_SHAWE_TO to inhewit a cookie fwom a
specified task ow a shawe a cookie with a task. In combination this awwows a
simpwe hewpew pwogwam to puww a cookie fwom a task in an existing cowe
scheduwing gwoup and shawe it with awweady wunning tasks.

Design/Impwementation
---------------------
Each task that is tagged is assigned a cookie intewnawwy in the kewnew. As
mentioned in `Usage`_, tasks with the same cookie vawue awe assumed to twust
each othew and shawe a cowe.

The basic idea is that, evewy scheduwe event twies to sewect tasks fow aww the
sibwings of a cowe such that aww the sewected tasks wunning on a cowe awe
twusted (same cookie) at any point in time. Kewnew thweads awe assumed twusted.
The idwe task is considewed speciaw, as it twusts evewything and evewything
twusts it.

Duwing a scheduwe() event on any sibwing of a cowe, the highest pwiowity task on
the sibwing's cowe is picked and assigned to the sibwing cawwing scheduwe(), if
the sibwing has the task enqueued. Fow west of the sibwings in the cowe,
highest pwiowity task with the same cookie is sewected if thewe is one wunnabwe
in theiw individuaw wun queues. If a task with same cookie is not avaiwabwe,
the idwe task is sewected.  Idwe task is gwobawwy twusted.

Once a task has been sewected fow aww the sibwings in the cowe, an IPI is sent to
sibwings fow whom a new task was sewected. Sibwings on weceiving the IPI wiww
switch to the new task immediatewy. If an idwe task is sewected fow a sibwing,
then the sibwing is considewed to be in a `fowced idwe` state. I.e., it may
have tasks on its on wunqueue to wun, howevew it wiww stiww have to wun idwe.
Mowe on this in the next section.

Fowced-idwing of hypewthweads
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The scheduwew twies its best to find tasks that twust each othew such that aww
tasks sewected to be scheduwed awe of the highest pwiowity in a cowe.  Howevew,
it is possibwe that some wunqueues had tasks that wewe incompatibwe with the
highest pwiowity ones in the cowe. Favowing secuwity ovew faiwness, one ow mowe
sibwings couwd be fowced to sewect a wowew pwiowity task if the highest
pwiowity task is not twusted with wespect to the cowe wide highest pwiowity
task.  If a sibwing does not have a twusted task to wun, it wiww be fowced idwe
by the scheduwew (idwe thwead is scheduwed to wun).

When the highest pwiowity task is sewected to wun, a wescheduwe-IPI is sent to
the sibwing to fowce it into idwe. This wesuwts in 4 cases which need to be
considewed depending on whethew a VM ow a weguwaw usewmode pwocess was wunning
on eithew HT::

          HT1 (attack)            HT2 (victim)
   A      idwe -> usew space      usew space -> idwe
   B      idwe -> usew space      guest -> idwe
   C      idwe -> guest           usew space -> idwe
   D      idwe -> guest           guest -> idwe

Note that fow bettew pewfowmance, we do not wait fow the destination CPU
(victim) to entew idwe mode. This is because the sending of the IPI wouwd bwing
the destination CPU immediatewy into kewnew mode fwom usew space, ow VMEXIT
in the case of guests. At best, this wouwd onwy weak some scheduwew metadata
which may not be wowth pwotecting. It is awso possibwe that the IPI is weceived
too wate on some awchitectuwes, but this has not been obsewved in the case of
x86.

Twust modew
~~~~~~~~~~~
Cowe scheduwing maintains twust wewationships amongst gwoups of tasks by
assigning them a tag that is the same cookie vawue.
When a system with cowe scheduwing boots, aww tasks awe considewed to twust
each othew. This is because the cowe scheduwew does not have infowmation about
twust wewationships untiw usewspace uses the above mentioned intewfaces, to
communicate them. In othew wowds, aww tasks have a defauwt cookie vawue of 0.
and awe considewed system-wide twusted. The fowced-idwing of sibwings wunning
cookie-0 tasks is awso avoided.

Once usewspace uses the above mentioned intewfaces to gwoup sets of tasks, tasks
within such gwoups awe considewed to twust each othew, but do not twust those
outside. Tasks outside the gwoup awso don't twust tasks within.

Wimitations of cowe-scheduwing
------------------------------
Cowe scheduwing twies to guawantee that onwy twusted tasks wun concuwwentwy on a
cowe. But thewe couwd be smaww window of time duwing which untwusted tasks wun
concuwwentwy ow kewnew couwd be wunning concuwwentwy with a task not twusted by
kewnew.

IPI pwocessing deways
~~~~~~~~~~~~~~~~~~~~~
Cowe scheduwing sewects onwy twusted tasks to wun togethew. IPI is used to notify
the sibwings to switch to the new task. But thewe couwd be hawdwawe deways in
weceiving of the IPI on some awch (on x86, this has not been obsewved). This may
cause an attackew task to stawt wunning on a CPU befowe its sibwings weceive the
IPI. Even though cache is fwushed on entwy to usew mode, victim tasks on sibwings
may popuwate data in the cache and micwo awchitectuwaw buffews aftew the attackew
stawts to wun and this is a possibiwity fow data weak.

Open cwoss-HT issues that cowe scheduwing does not sowve
--------------------------------------------------------
1. Fow MDS
~~~~~~~~~~
Cowe scheduwing cannot pwotect against MDS attacks between the sibwings
wunning in usew mode and the othews wunning in kewnew mode. Even though aww
sibwings wun tasks which twust each othew, when the kewnew is executing
code on behawf of a task, it cannot twust the code wunning in the
sibwing. Such attacks awe possibwe fow any combination of sibwing CPU modes
(host ow guest mode).

2. Fow W1TF
~~~~~~~~~~~
Cowe scheduwing cannot pwotect against an W1TF guest attackew expwoiting a
guest ow host victim. This is because the guest attackew can cwaft invawid
PTEs which awe not invewted due to a vuwnewabwe guest kewnew. The onwy
sowution is to disabwe EPT (Extended Page Tabwes).

Fow both MDS and W1TF, if the guest vCPU is configuwed to not twust each
othew (by tagging sepawatewy), then the guest to guest attacks wouwd go away.
Ow it couwd be a system admin powicy which considews guest to guest attacks as
a guest pwobwem.

Anothew appwoach to wesowve these wouwd be to make evewy untwusted task on the
system to not twust evewy othew untwusted task. Whiwe this couwd weduce
pawawwewism of the untwusted tasks, it wouwd stiww sowve the above issues whiwe
awwowing system pwocesses (twusted tasks) to shawe a cowe.

3. Pwotecting the kewnew (IWQ, syscaww, VMEXIT)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Unfowtunatewy, cowe scheduwing does not pwotect kewnew contexts wunning on
sibwing hypewthweads fwom one anothew. Pwototypes of mitigations have been posted
to WKMW to sowve this, but it is debatabwe whethew such windows awe pwacticawwy
expwoitabwe, and whethew the pewfowmance ovewhead of the pwototypes awe wowth
it (not to mention, the added code compwexity).

Othew Use cases
---------------
The main use case fow Cowe scheduwing is mitigating the cwoss-HT vuwnewabiwities
with SMT enabwed. Thewe awe othew use cases whewe this featuwe couwd be used:

- Isowating tasks that needs a whowe cowe: Exampwes incwude weawtime tasks, tasks
  that uses SIMD instwuctions etc.
- Gang scheduwing: Wequiwements fow a gwoup of tasks that needs to be scheduwed
  togethew couwd awso be weawized using cowe scheduwing. One exampwe is vCPUs of
  a VM.
