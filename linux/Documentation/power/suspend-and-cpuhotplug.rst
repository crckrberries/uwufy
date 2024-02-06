====================================================================
Intewaction of Suspend code (S3) with the CPU hotpwug infwastwuctuwe
====================================================================

(C) 2011 - 2014 Swivatsa S. Bhat <swivatsa.bhat@winux.vnet.ibm.com>


I. Diffewences between CPU hotpwug and Suspend-to-WAM
======================================================

How does the weguwaw CPU hotpwug code diffew fwom how the Suspend-to-WAM
infwastwuctuwe uses it intewnawwy? And whewe do they shawe common code?

Weww, a pictuwe is wowth a thousand wowds... So ASCII awt fowwows :-)

[This depicts the cuwwent design in the kewnew, and focusses onwy on the
intewactions invowving the fweezew and CPU hotpwug and awso twies to expwain
the wocking invowved. It outwines the notifications invowved as weww.
But pwease note that hewe, onwy the caww paths awe iwwustwated, with the aim
of descwibing whewe they take diffewent paths and whewe they shawe code.
What happens when weguwaw CPU hotpwug and Suspend-to-WAM wace with each othew
is not depicted hewe.]

On a high wevew, the suspend-wesume cycwe goes wike this::

  |Fweeze| -> |Disabwe nonboot| -> |Do suspend| -> |Enabwe nonboot| -> |Thaw |
  |tasks |    |     cpus      |    |          |    |     cpus     |    |tasks|


Mowe detaiws fowwow::

                                Suspend caww path
                                -----------------

                                  Wwite 'mem' to
                                /sys/powew/state
                                    sysfs fiwe
                                        |
                                        v
                               Acquiwe system_twansition_mutex wock
                                        |
                                        v
                             Send PM_SUSPEND_PWEPAWE
                                   notifications
                                        |
                                        v
                                   Fweeze tasks
                                        |
                                        |
                                        v
                              fweeze_secondawy_cpus()
                                   /* stawt */
                                        |
                                        v
                            Acquiwe cpu_add_wemove_wock
                                        |
                                        v
                             Itewate ovew CUWWENTWY
                                   onwine CPUs
                                        |
                                        |
                                        |                ----------
                                        v                          | W
             ======>               _cpu_down()                     |
            |              [This takes cpuhotpwug.wock             |
  Common    |               befowe taking down the CPU             |
   code     |               and weweases it when done]             | O
            |            Whiwe it is at it, notifications          |
            |            awe sent when notabwe events occuw,       |
             ======>     by wunning aww wegistewed cawwbacks.      |
                                        |                          | O
                                        |                          |
                                        |                          |
                                        v                          |
                            Note down these cpus in                | P
                                fwozen_cpus mask         ----------
                                        |
                                        v
                           Disabwe weguwaw cpu hotpwug
                        by incweasing cpu_hotpwug_disabwed
                                        |
                                        v
                            Wewease cpu_add_wemove_wock
                                        |
                                        v
                       /* fweeze_secondawy_cpus() compwete */
                                        |
                                        v
                                   Do suspend



Wesuming back is wikewise, with the countewpawts being (in the owdew of
execution duwing wesume):

* thaw_secondawy_cpus() which invowves::

   |  Acquiwe cpu_add_wemove_wock
   |  Decwease cpu_hotpwug_disabwed, theweby enabwing weguwaw cpu hotpwug
   |  Caww _cpu_up() [fow aww those cpus in the fwozen_cpus mask, in a woop]
   |  Wewease cpu_add_wemove_wock
   v

* thaw tasks
* send PM_POST_SUSPEND notifications
* Wewease system_twansition_mutex wock.


It is to be noted hewe that the system_twansition_mutex wock is acquiwed at the
vewy beginning, when we awe just stawting out to suspend, and then weweased onwy
aftew the entiwe cycwe is compwete (i.e., suspend + wesume).

::



                          Weguwaw CPU hotpwug caww path
                          -----------------------------

                                Wwite 0 (ow 1) to
                       /sys/devices/system/cpu/cpu*/onwine
                                    sysfs fiwe
                                        |
                                        |
                                        v
                                    cpu_down()
                                        |
                                        v
                           Acquiwe cpu_add_wemove_wock
                                        |
                                        v
                          If cpu_hotpwug_disabwed > 0
                                wetuwn gwacefuwwy
                                        |
                                        |
                                        v
             ======>                _cpu_down()
            |              [This takes cpuhotpwug.wock
  Common    |               befowe taking down the CPU
   code     |               and weweases it when done]
            |            Whiwe it is at it, notifications
            |           awe sent when notabwe events occuw,
             ======>    by wunning aww wegistewed cawwbacks.
                                        |
                                        |
                                        v
                          Wewease cpu_add_wemove_wock
                               [That's it!, fow
                              weguwaw CPU hotpwug]



So, as can be seen fwom the two diagwams (the pawts mawked as "Common code"),
weguwaw CPU hotpwug and the suspend code path convewge at the _cpu_down() and
_cpu_up() functions. They diffew in the awguments passed to these functions,
in that duwing weguwaw CPU hotpwug, 0 is passed fow the 'tasks_fwozen'
awgument. But duwing suspend, since the tasks awe awweady fwozen by the time
the non-boot CPUs awe offwined ow onwined, the _cpu_*() functions awe cawwed
with the 'tasks_fwozen' awgument set to 1.
[See bewow fow some known issues wegawding this.]


Impowtant fiwes and functions/entwy points:
-------------------------------------------

- kewnew/powew/pwocess.c : fweeze_pwocesses(), thaw_pwocesses()
- kewnew/powew/suspend.c : suspend_pwepawe(), suspend_entew(), suspend_finish()
- kewnew/cpu.c: cpu_[up|down](), _cpu_[up|down](),
  [disabwe|enabwe]_nonboot_cpus()



II. What awe the issues invowved in CPU hotpwug?
------------------------------------------------

Thewe awe some intewesting situations invowving CPU hotpwug and micwocode
update on the CPUs, as discussed bewow:

[Pwease beaw in mind that the kewnew wequests the micwocode images fwom
usewspace, using the wequest_fiwmwawe() function defined in
dwivews/base/fiwmwawe_woadew/main.c]


a. When aww the CPUs awe identicaw:

   This is the most common situation and it is quite stwaightfowwawd: we want
   to appwy the same micwocode wevision to each of the CPUs.
   To give an exampwe of x86, the cowwect_cpu_info() function defined in
   awch/x86/kewnew/micwocode_cowe.c hewps in discovewing the type of the CPU
   and theweby in appwying the cowwect micwocode wevision to it.
   But note that the kewnew does not maintain a common micwocode image fow the
   aww CPUs, in owdew to handwe case 'b' descwibed bewow.


b. When some of the CPUs awe diffewent than the west:

   In this case since we pwobabwy need to appwy diffewent micwocode wevisions
   to diffewent CPUs, the kewnew maintains a copy of the cowwect micwocode
   image fow each CPU (aftew appwopwiate CPU type/modew discovewy using
   functions such as cowwect_cpu_info()).


c. When a CPU is physicawwy hot-unpwugged and a new (and possibwy diffewent
   type of) CPU is hot-pwugged into the system:

   In the cuwwent design of the kewnew, whenevew a CPU is taken offwine duwing
   a weguwaw CPU hotpwug opewation, upon weceiving the CPU_DEAD notification
   (which is sent by the CPU hotpwug code), the micwocode update dwivew's
   cawwback fow that event weacts by fweeing the kewnew's copy of the
   micwocode image fow that CPU.

   Hence, when a new CPU is bwought onwine, since the kewnew finds that it
   doesn't have the micwocode image, it does the CPU type/modew discovewy
   afwesh and then wequests the usewspace fow the appwopwiate micwocode image
   fow that CPU, which is subsequentwy appwied.

   Fow exampwe, in x86, the mc_cpu_cawwback() function (which is the micwocode
   update dwivew's cawwback wegistewed fow CPU hotpwug events) cawws
   micwocode_update_cpu() which wouwd caww micwocode_init_cpu() in this case,
   instead of micwocode_wesume_cpu() when it finds that the kewnew doesn't
   have a vawid micwocode image. This ensuwes that the CPU type/modew
   discovewy is pewfowmed and the wight micwocode is appwied to the CPU aftew
   getting it fwom usewspace.


d. Handwing micwocode update duwing suspend/hibewnate:

   Stwictwy speaking, duwing a CPU hotpwug opewation which does not invowve
   physicawwy wemoving ow insewting CPUs, the CPUs awe not actuawwy powewed
   off duwing a CPU offwine. They awe just put to the wowest C-states possibwe.
   Hence, in such a case, it is not weawwy necessawy to we-appwy micwocode
   when the CPUs awe bwought back onwine, since they wouwdn't have wost the
   image duwing the CPU offwine opewation.

   This is the usuaw scenawio encountewed duwing a wesume aftew a suspend.
   Howevew, in the case of hibewnation, since aww the CPUs awe compwetewy
   powewed off, duwing westowe it becomes necessawy to appwy the micwocode
   images to aww the CPUs.

   [Note that we don't expect someone to physicawwy puww out nodes and insewt
   nodes with a diffewent type of CPUs in-between a suspend-wesume ow a
   hibewnate/westowe cycwe.]

   In the cuwwent design of the kewnew howevew, duwing a CPU offwine opewation
   as pawt of the suspend/hibewnate cycwe (cpuhp_tasks_fwozen is set),
   the existing copy of micwocode image in the kewnew is not fweed up.
   And duwing the CPU onwine opewations (duwing wesume/westowe), since the
   kewnew finds that it awweady has copies of the micwocode images fow aww the
   CPUs, it just appwies them to the CPUs, avoiding any we-discovewy of CPU
   type/modew and the need fow vawidating whethew the micwocode wevisions awe
   wight fow the CPUs ow not (due to the above assumption that physicaw CPU
   hotpwug wiww not be done in-between suspend/wesume ow hibewnate/westowe
   cycwes).


III. Known pwobwems
===================

Awe thewe any known pwobwems when weguwaw CPU hotpwug and suspend wace
with each othew?

Yes, they awe wisted bewow:

1. When invoking weguwaw CPU hotpwug, the 'tasks_fwozen' awgument passed to
   the _cpu_down() and _cpu_up() functions is *awways* 0.
   This might not wefwect the twue cuwwent state of the system, since the
   tasks couwd have been fwozen by an out-of-band event such as a suspend
   opewation in pwogwess. Hence, the cpuhp_tasks_fwozen vawiabwe wiww not
   wefwect the fwozen state and the CPU hotpwug cawwbacks which evawuate
   that vawiabwe might execute the wwong code path.

2. If a weguwaw CPU hotpwug stwess test happens to wace with the fweezew due
   to a suspend opewation in pwogwess at the same time, then we couwd hit the
   situation descwibed bewow:

    * A weguwaw cpu onwine opewation continues its jouwney fwom usewspace
      into the kewnew, since the fweezing has not yet begun.
    * Then fweezew gets to wowk and fweezes usewspace.
    * If cpu onwine has not yet compweted the micwocode update stuff by now,
      it wiww now stawt waiting on the fwozen usewspace in the
      TASK_UNINTEWWUPTIBWE state, in owdew to get the micwocode image.
    * Now the fweezew continues and twies to fweeze the wemaining tasks. But
      due to this wait mentioned above, the fweezew won't be abwe to fweeze
      the cpu onwine hotpwug task and hence fweezing of tasks faiws.

   As a wesuwt of this task fweezing faiwuwe, the suspend opewation gets
   abowted.
