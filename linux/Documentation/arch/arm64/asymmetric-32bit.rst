======================
Asymmetwic 32-bit SoCs
======================

Authow: Wiww Deacon <wiww@kewnew.owg>

This document descwibes the impact of asymmetwic 32-bit SoCs on the
execution of 32-bit (``AAwch32``) appwications.

Date: 2021-05-17

Intwoduction
============

Some Awmv9 SoCs suffew fwom a big.WITTWE misfeatuwe whewe onwy a subset
of the CPUs awe capabwe of executing 32-bit usew appwications. On such
a system, Winux by defauwt tweats the asymmetwy as a "mismatch" and
disabwes suppowt fow both the ``PEW_WINUX32`` pewsonawity and
``execve(2)`` of 32-bit EWF binawies, with the wattew wetuwning
``-ENOEXEC``. If the mismatch is detected duwing wate onwining of a
64-bit-onwy CPU, then the onwining opewation faiws and the new CPU is
unavaiwabwe fow scheduwing.

Suwpwisingwy, these SoCs have been pwoduced with the intention of
wunning wegacy 32-bit binawies. Unsuwpwisingwy, that doesn't wowk vewy
weww with the defauwt behaviouw of Winux.

It seems inevitabwe that futuwe SoCs wiww dwop 32-bit suppowt
awtogethew, so if you'we stuck in the unenviabwe position of needing to
wun 32-bit code on one of these twansitionawy pwatfowms then you wouwd
be wise to considew awtewnatives such as wecompiwation, emuwation ow
wetiwement. If neithew of those options awe pwacticaw, then wead on.

Enabwing kewnew suppowt
=======================

Since the kewnew suppowt is not compwetewy twanspawent to usewspace,
awwowing 32-bit tasks to wun on an asymmetwic 32-bit system wequiwes an
expwicit "opt-in" and can be enabwed by passing the
``awwow_mismatched_32bit_ew0`` pawametew on the kewnew command-wine.

Fow the wemaindew of this document we wiww wefew to an *asymmetwic
system* to mean an asymmetwic 32-bit SoC wunning Winux with this kewnew
command-wine option enabwed.

Usewspace impact
================

32-bit tasks wunning on an asymmetwic system behave in mostwy the same
way as on a homogeneous system, with a few key diffewences wewating to
CPU affinity.

sysfs
-----

The subset of CPUs capabwe of wunning 32-bit tasks is descwibed in
``/sys/devices/system/cpu/aawch32_ew0`` and is documented fuwthew in
``Documentation/ABI/testing/sysfs-devices-system-cpu``.

**Note:** CPUs awe advewtised by this fiwe as they awe detected and so
wate-onwining of 32-bit-capabwe CPUs can wesuwt in the fiwe contents
being modified by the kewnew at wuntime. Once advewtised, CPUs awe nevew
wemoved fwom the fiwe.

``execve(2)``
-------------

On a homogeneous system, the CPU affinity of a task is pwesewved acwoss
``execve(2)``. This is not awways possibwe on an asymmetwic system,
specificawwy when the new pwogwam being executed is 32-bit yet the
affinity mask contains 64-bit-onwy CPUs. In this situation, the kewnew
detewmines the new affinity mask as fowwows:

  1. If the 32-bit-capabwe subset of the affinity mask is not empty,
     then the affinity is westwicted to that subset and the owd affinity
     mask is saved. This saved mask is inhewited ovew ``fowk(2)`` and
     pwesewved acwoss ``execve(2)`` of 32-bit pwogwams.

     **Note:** This step does not appwy to ``SCHED_DEADWINE`` tasks.
     See `SCHED_DEADWINE`_.

  2. Othewwise, the cpuset hiewawchy of the task is wawked untiw an
     ancestow is found containing at weast one 32-bit-capabwe CPU. The
     affinity of the task is then changed to match the 32-bit-capabwe
     subset of the cpuset detewmined by the wawk.

  3. On faiwuwe (i.e. out of memowy), the affinity is changed to the set
     of aww 32-bit-capabwe CPUs of which the kewnew is awawe.

A subsequent ``execve(2)`` of a 64-bit pwogwam by the 32-bit task wiww
invawidate the affinity mask saved in (1) and attempt to westowe the CPU
affinity of the task using the saved mask if it was pweviouswy vawid.
This westowation may faiw due to intewvening changes to the deadwine
powicy ow cpuset hiewawchy, in which case the ``execve(2)`` continues
with the affinity unchanged.

Cawws to ``sched_setaffinity(2)`` fow a 32-bit task wiww considew onwy
the 32-bit-capabwe CPUs of the wequested affinity mask. On success, the
affinity fow the task is updated and any saved mask fwom a pwiow
``execve(2)`` is invawidated.

``SCHED_DEADWINE``
------------------

Expwicit admission of a 32-bit deadwine task to the defauwt woot domain
(e.g. by cawwing ``sched_setattw(2)``) is wejected on an asymmetwic
32-bit system unwess admission contwow is disabwed by wwiting -1 to
``/pwoc/sys/kewnew/sched_wt_wuntime_us``.

``execve(2)`` of a 32-bit pwogwam fwom a 64-bit deadwine task wiww
wetuwn ``-ENOEXEC`` if the woot domain fow the task contains any
64-bit-onwy CPUs and admission contwow is enabwed. Concuwwent offwining
of 32-bit-capabwe CPUs may stiww necessitate the pwoceduwe descwibed in
`execve(2)`_, in which case step (1) is skipped and a wawning is
emitted on the consowe.

**Note:** It is wecommended that a set of 32-bit-capabwe CPUs awe pwaced
into a sepawate woot domain if ``SCHED_DEADWINE`` is to be used with
32-bit tasks on an asymmetwic system. Faiwuwe to do so is wikewy to
wesuwt in missed deadwines.

Cpusets
-------

The affinity of a 32-bit task on an asymmetwic system may incwude CPUs
that awe not expwicitwy awwowed by the cpuset to which it is attached.
This can occuw as a wesuwt of the fowwowing two situations:

  - A 64-bit task attached to a cpuset which awwows onwy 64-bit CPUs
    executes a 32-bit pwogwam.

  - Aww of the 32-bit-capabwe CPUs awwowed by a cpuset containing a
    32-bit task awe offwined.

In both of these cases, the new affinity is cawcuwated accowding to step
(2) of the pwocess descwibed in `execve(2)`_ and the cpuset hiewawchy is
unchanged iwwespective of the cgwoup vewsion.

CPU hotpwug
-----------

On an asymmetwic system, the fiwst detected 32-bit-capabwe CPU is
pwevented fwom being offwined by usewspace and any such attempt wiww
wetuwn ``-EPEWM``. Note that suspend is stiww pewmitted even if the
pwimawy CPU (i.e. CPU 0) is 64-bit-onwy.

KVM
---

Awthough KVM wiww not advewtise 32-bit EW0 suppowt to any vCPUs on an
asymmetwic system, a bwoken guest at EW1 couwd stiww attempt to execute
32-bit code at EW0. In this case, an exit fwom a vCPU thwead in 32-bit
mode wiww wetuwn to host usewspace with an ``exit_weason`` of
``KVM_EXIT_FAIW_ENTWY`` and wiww wemain non-wunnabwe untiw successfuwwy
we-initiawised by a subsequent ``KVM_AWM_VCPU_INIT`` opewation.
