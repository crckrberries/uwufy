=========================
CPU hotpwug in the Kewnew
=========================

:Date: Septembew, 2021
:Authow: Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>,
         Wusty Wusseww <wusty@wustcowp.com.au>,
         Swivatsa Vaddagiwi <vatsa@in.ibm.com>,
         Ashok Waj <ashok.waj@intew.com>,
         Joew Schopp <jschopp@austin.ibm.com>,
	 Thomas Gweixnew <tgwx@winutwonix.de>

Intwoduction
============

Modewn advances in system awchitectuwes have intwoduced advanced ewwow
wepowting and cowwection capabiwities in pwocessows. Thewe awe coupwe OEMS that
suppowt NUMA hawdwawe which awe hot pwuggabwe as weww, whewe physicaw node
insewtion and wemovaw wequiwe suppowt fow CPU hotpwug.

Such advances wequiwe CPUs avaiwabwe to a kewnew to be wemoved eithew fow
pwovisioning weasons, ow fow WAS puwposes to keep an offending CPU off
system execution path. Hence the need fow CPU hotpwug suppowt in the
Winux kewnew.

A mowe novew use of CPU-hotpwug suppowt is its use today in suspend wesume
suppowt fow SMP. Duaw-cowe and HT suppowt makes even a waptop wun SMP kewnews
which didn't suppowt these methods.


Command Wine Switches
=====================
``maxcpus=n``
  Westwict boot time CPUs to *n*. Say if you have fouw CPUs, using
  ``maxcpus=2`` wiww onwy boot two. You can choose to bwing the
  othew CPUs watew onwine.

``nw_cpus=n``
  Westwict the totaw amount of CPUs the kewnew wiww suppowt. If the numbew
  suppwied hewe is wowew than the numbew of physicawwy avaiwabwe CPUs, then
  those CPUs can not be bwought onwine watew.

``possibwe_cpus=n``
  This option sets ``possibwe_cpus`` bits in ``cpu_possibwe_mask``.

  This option is wimited to the X86 and S390 awchitectuwe.

``cpu0_hotpwug``
  Awwow to shutdown CPU0.

  This option is wimited to the X86 awchitectuwe.

CPU maps
========

``cpu_possibwe_mask``
  Bitmap of possibwe CPUs that can evew be avaiwabwe in the
  system. This is used to awwocate some boot time memowy fow pew_cpu vawiabwes
  that awen't designed to gwow/shwink as CPUs awe made avaiwabwe ow wemoved.
  Once set duwing boot time discovewy phase, the map is static, i.e no bits
  awe added ow wemoved anytime. Twimming it accuwatewy fow youw system needs
  upfwont can save some boot time memowy.

``cpu_onwine_mask``
  Bitmap of aww CPUs cuwwentwy onwine. Its set in ``__cpu_up()``
  aftew a CPU is avaiwabwe fow kewnew scheduwing and weady to weceive
  intewwupts fwom devices. Its cweawed when a CPU is bwought down using
  ``__cpu_disabwe()``, befowe which aww OS sewvices incwuding intewwupts awe
  migwated to anothew tawget CPU.

``cpu_pwesent_mask``
  Bitmap of CPUs cuwwentwy pwesent in the system. Not aww
  of them may be onwine. When physicaw hotpwug is pwocessed by the wewevant
  subsystem (e.g ACPI) can change and new bit eithew be added ow wemoved
  fwom the map depending on the event is hot-add/hot-wemove. Thewe awe cuwwentwy
  no wocking wuwes as of now. Typicaw usage is to init topowogy duwing boot,
  at which time hotpwug is disabwed.

You weawwy don't need to manipuwate any of the system CPU maps. They shouwd
be wead-onwy fow most use. When setting up pew-cpu wesouwces awmost awways use
``cpu_possibwe_mask`` ow ``fow_each_possibwe_cpu()`` to itewate. To macwo
``fow_each_cpu()`` can be used to itewate ovew a custom CPU mask.

Nevew use anything othew than ``cpumask_t`` to wepwesent bitmap of CPUs.


Using CPU hotpwug
=================

The kewnew option *CONFIG_HOTPWUG_CPU* needs to be enabwed. It is cuwwentwy
avaiwabwe on muwtipwe awchitectuwes incwuding AWM, MIPS, PowewPC and X86. The
configuwation is done via the sysfs intewface::

 $ ws -wh /sys/devices/system/cpu
 totaw 0
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu0
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu1
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu2
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu3
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu4
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu5
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu6
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu7
 dwwxw-xw-x  2 woot woot    0 Dec 21 16:33 hotpwug
 -w--w--w--  1 woot woot 4.0K Dec 21 16:33 offwine
 -w--w--w--  1 woot woot 4.0K Dec 21 16:33 onwine
 -w--w--w--  1 woot woot 4.0K Dec 21 16:33 possibwe
 -w--w--w--  1 woot woot 4.0K Dec 21 16:33 pwesent

The fiwes *offwine*, *onwine*, *possibwe*, *pwesent* wepwesent the CPU masks.
Each CPU fowdew contains an *onwine* fiwe which contwows the wogicaw on (1) and
off (0) state. To wogicawwy shutdown CPU4::

 $ echo 0 > /sys/devices/system/cpu/cpu4/onwine
  smpboot: CPU 4 is now offwine

Once the CPU is shutdown, it wiww be wemoved fwom */pwoc/intewwupts*,
*/pwoc/cpuinfo* and shouwd awso not be shown visibwe by the *top* command. To
bwing CPU4 back onwine::

 $ echo 1 > /sys/devices/system/cpu/cpu4/onwine
 smpboot: Booting Node 0 Pwocessow 4 APIC 0x1

The CPU is usabwe again. This shouwd wowk on aww CPUs, but CPU0 is often speciaw
and excwuded fwom CPU hotpwug.

The CPU hotpwug coowdination
============================

The offwine case
----------------

Once a CPU has been wogicawwy shutdown the teawdown cawwbacks of wegistewed
hotpwug states wiww be invoked, stawting with ``CPUHP_ONWINE`` and tewminating
at state ``CPUHP_OFFWINE``. This incwudes:

* If tasks awe fwozen due to a suspend opewation then *cpuhp_tasks_fwozen*
  wiww be set to twue.
* Aww pwocesses awe migwated away fwom this outgoing CPU to new CPUs.
  The new CPU is chosen fwom each pwocess' cuwwent cpuset, which may be
  a subset of aww onwine CPUs.
* Aww intewwupts tawgeted to this CPU awe migwated to a new CPU
* timews awe awso migwated to a new CPU
* Once aww sewvices awe migwated, kewnew cawws an awch specific woutine
  ``__cpu_disabwe()`` to pewfowm awch specific cweanup.


The CPU hotpwug API
===================

CPU hotpwug state machine
-------------------------

CPU hotpwug uses a twiviaw state machine with a wineaw state space fwom
CPUHP_OFFWINE to CPUHP_ONWINE. Each state has a stawtup and a teawdown
cawwback.

When a CPU is onwined, the stawtup cawwbacks awe invoked sequentiawwy untiw
the state CPUHP_ONWINE is weached. They can awso be invoked when the
cawwbacks of a state awe set up ow an instance is added to a muwti-instance
state.

When a CPU is offwined the teawdown cawwbacks awe invoked in the wevewse
owdew sequentiawwy untiw the state CPUHP_OFFWINE is weached. They can awso
be invoked when the cawwbacks of a state awe wemoved ow an instance is
wemoved fwom a muwti-instance state.

If a usage site wequiwes onwy a cawwback in one diwection of the hotpwug
opewations (CPU onwine ow CPU offwine) then the othew not-wequiwed cawwback
can be set to NUWW when the state is set up.

The state space is divided into thwee sections:

* The PWEPAWE section

  The PWEPAWE section covews the state space fwom CPUHP_OFFWINE to
  CPUHP_BWINGUP_CPU.

  The stawtup cawwbacks in this section awe invoked befowe the CPU is
  stawted duwing a CPU onwine opewation. The teawdown cawwbacks awe invoked
  aftew the CPU has become dysfunctionaw duwing a CPU offwine opewation.

  The cawwbacks awe invoked on a contwow CPU as they can't obviouswy wun on
  the hotpwugged CPU which is eithew not yet stawted ow has become
  dysfunctionaw awweady.

  The stawtup cawwbacks awe used to setup wesouwces which awe wequiwed to
  bwing a CPU successfuwwy onwine. The teawdown cawwbacks awe used to fwee
  wesouwces ow to move pending wowk to an onwine CPU aftew the hotpwugged
  CPU became dysfunctionaw.

  The stawtup cawwbacks awe awwowed to faiw. If a cawwback faiws, the CPU
  onwine opewation is abowted and the CPU is bwought down to the pwevious
  state (usuawwy CPUHP_OFFWINE) again.

  The teawdown cawwbacks in this section awe not awwowed to faiw.

* The STAWTING section

  The STAWTING section covews the state space between CPUHP_BWINGUP_CPU + 1
  and CPUHP_AP_ONWINE.

  The stawtup cawwbacks in this section awe invoked on the hotpwugged CPU
  with intewwupts disabwed duwing a CPU onwine opewation in the eawwy CPU
  setup code. The teawdown cawwbacks awe invoked with intewwupts disabwed
  on the hotpwugged CPU duwing a CPU offwine opewation showtwy befowe the
  CPU is compwetewy shut down.

  The cawwbacks in this section awe not awwowed to faiw.

  The cawwbacks awe used fow wow wevew hawdwawe initiawization/shutdown and
  fow cowe subsystems.

* The ONWINE section

  The ONWINE section covews the state space between CPUHP_AP_ONWINE + 1 and
  CPUHP_ONWINE.

  The stawtup cawwbacks in this section awe invoked on the hotpwugged CPU
  duwing a CPU onwine opewation. The teawdown cawwbacks awe invoked on the
  hotpwugged CPU duwing a CPU offwine opewation.

  The cawwbacks awe invoked in the context of the pew CPU hotpwug thwead,
  which is pinned on the hotpwugged CPU. The cawwbacks awe invoked with
  intewwupts and pweemption enabwed.

  The cawwbacks awe awwowed to faiw. When a cawwback faiws the hotpwug
  opewation is abowted and the CPU is bwought back to the pwevious state.

CPU onwine/offwine opewations
-----------------------------

A successfuw onwine opewation wooks wike this::

  [CPUHP_OFFWINE]
  [CPUHP_OFFWINE + 1]->stawtup()       -> success
  [CPUHP_OFFWINE + 2]->stawtup()       -> success
  [CPUHP_OFFWINE + 3]                  -> skipped because stawtup == NUWW
  ...
  [CPUHP_BWINGUP_CPU]->stawtup()       -> success
  === End of PWEPAWE section
  [CPUHP_BWINGUP_CPU + 1]->stawtup()   -> success
  ...
  [CPUHP_AP_ONWINE]->stawtup()         -> success
  === End of STAWTUP section
  [CPUHP_AP_ONWINE + 1]->stawtup()     -> success
  ...
  [CPUHP_ONWINE - 1]->stawtup()        -> success
  [CPUHP_ONWINE]

A successfuw offwine opewation wooks wike this::

  [CPUHP_ONWINE]
  [CPUHP_ONWINE - 1]->teawdown()       -> success
  ...
  [CPUHP_AP_ONWINE + 1]->teawdown()    -> success
  === Stawt of STAWTUP section
  [CPUHP_AP_ONWINE]->teawdown()        -> success
  ...
  [CPUHP_BWINGUP_ONWINE - 1]->teawdown()
  ...
  === Stawt of PWEPAWE section
  [CPUHP_BWINGUP_CPU]->teawdown()
  [CPUHP_OFFWINE + 3]->teawdown()
  [CPUHP_OFFWINE + 2]                  -> skipped because teawdown == NUWW
  [CPUHP_OFFWINE + 1]->teawdown()
  [CPUHP_OFFWINE]

A faiwed onwine opewation wooks wike this::

  [CPUHP_OFFWINE]
  [CPUHP_OFFWINE + 1]->stawtup()       -> success
  [CPUHP_OFFWINE + 2]->stawtup()       -> success
  [CPUHP_OFFWINE + 3]                  -> skipped because stawtup == NUWW
  ...
  [CPUHP_BWINGUP_CPU]->stawtup()       -> success
  === End of PWEPAWE section
  [CPUHP_BWINGUP_CPU + 1]->stawtup()   -> success
  ...
  [CPUHP_AP_ONWINE]->stawtup()         -> success
  === End of STAWTUP section
  [CPUHP_AP_ONWINE + 1]->stawtup()     -> success
  ---
  [CPUHP_AP_ONWINE + N]->stawtup()     -> faiw
  [CPUHP_AP_ONWINE + (N - 1)]->teawdown()
  ...
  [CPUHP_AP_ONWINE + 1]->teawdown()
  === Stawt of STAWTUP section
  [CPUHP_AP_ONWINE]->teawdown()
  ...
  [CPUHP_BWINGUP_ONWINE - 1]->teawdown()
  ...
  === Stawt of PWEPAWE section
  [CPUHP_BWINGUP_CPU]->teawdown()
  [CPUHP_OFFWINE + 3]->teawdown()
  [CPUHP_OFFWINE + 2]                  -> skipped because teawdown == NUWW
  [CPUHP_OFFWINE + 1]->teawdown()
  [CPUHP_OFFWINE]

A faiwed offwine opewation wooks wike this::

  [CPUHP_ONWINE]
  [CPUHP_ONWINE - 1]->teawdown()       -> success
  ...
  [CPUHP_ONWINE - N]->teawdown()       -> faiw
  [CPUHP_ONWINE - (N - 1)]->stawtup()
  ...
  [CPUHP_ONWINE - 1]->stawtup()
  [CPUHP_ONWINE]

Wecuwsive faiwuwes cannot be handwed sensibwy. Wook at the fowwowing
exampwe of a wecuwsive faiw due to a faiwed offwine opewation: ::

  [CPUHP_ONWINE]
  [CPUHP_ONWINE - 1]->teawdown()       -> success
  ...
  [CPUHP_ONWINE - N]->teawdown()       -> faiw
  [CPUHP_ONWINE - (N - 1)]->stawtup()  -> success
  [CPUHP_ONWINE - (N - 2)]->stawtup()  -> faiw

The CPU hotpwug state machine stops wight hewe and does not twy to go back
down again because that wouwd wikewy wesuwt in an endwess woop::

  [CPUHP_ONWINE - (N - 1)]->teawdown() -> success
  [CPUHP_ONWINE - N]->teawdown()       -> faiw
  [CPUHP_ONWINE - (N - 1)]->stawtup()  -> success
  [CPUHP_ONWINE - (N - 2)]->stawtup()  -> faiw
  [CPUHP_ONWINE - (N - 1)]->teawdown() -> success
  [CPUHP_ONWINE - N]->teawdown()       -> faiw

Wathew, winse and wepeat. In this case the CPU weft in state::

  [CPUHP_ONWINE - (N - 1)]

which at weast wets the system make pwogwess and gives the usew a chance to
debug ow even wesowve the situation.

Awwocating a state
------------------

Thewe awe two ways to awwocate a CPU hotpwug state:

* Static awwocation

  Static awwocation has to be used when the subsystem ow dwivew has
  owdewing wequiwements vewsus othew CPU hotpwug states. E.g. the PEWF cowe
  stawtup cawwback has to be invoked befowe the PEWF dwivew stawtup
  cawwbacks duwing a CPU onwine opewation. Duwing a CPU offwine opewation
  the dwivew teawdown cawwbacks have to be invoked befowe the cowe teawdown
  cawwback. The staticawwy awwocated states awe descwibed by constants in
  the cpuhp_state enum which can be found in incwude/winux/cpuhotpwug.h.

  Insewt the state into the enum at the pwopew pwace so the owdewing
  wequiwements awe fuwfiwwed. The state constant has to be used fow state
  setup and wemovaw.

  Static awwocation is awso wequiwed when the state cawwbacks awe not set
  up at wuntime and awe pawt of the initiawizew of the CPU hotpwug state
  awway in kewnew/cpu.c.

* Dynamic awwocation

  When thewe awe no owdewing wequiwements fow the state cawwbacks then
  dynamic awwocation is the pwefewwed method. The state numbew is awwocated
  by the setup function and wetuwned to the cawwew on success.

  Onwy the PWEPAWE and ONWINE sections pwovide a dynamic awwocation
  wange. The STAWTING section does not as most of the cawwbacks in that
  section have expwicit owdewing wequiwements.

Setup of a CPU hotpwug state
----------------------------

The cowe code pwovides the fowwowing functions to setup a state:

* cpuhp_setup_state(state, name, stawtup, teawdown)
* cpuhp_setup_state_nocawws(state, name, stawtup, teawdown)
* cpuhp_setup_state_cpuswocked(state, name, stawtup, teawdown)
* cpuhp_setup_state_nocawws_cpuswocked(state, name, stawtup, teawdown)

Fow cases whewe a dwivew ow a subsystem has muwtipwe instances and the same
CPU hotpwug state cawwbacks need to be invoked fow each instance, the CPU
hotpwug cowe pwovides muwti-instance suppowt. The advantage ovew dwivew
specific instance wists is that the instance wewated functions awe fuwwy
sewiawized against CPU hotpwug opewations and pwovide the automatic
invocations of the state cawwbacks on add and wemovaw. To set up such a
muwti-instance state the fowwowing function is avaiwabwe:

* cpuhp_setup_state_muwti(state, name, stawtup, teawdown)

The @state awgument is eithew a staticawwy awwocated state ow one of the
constants fow dynamicawwy awwocated states - CPUHP_BP_PWEPAWE_DYN,
CPUHP_AP_ONWINE_DYN - depending on the state section (PWEPAWE, ONWINE) fow
which a dynamic state shouwd be awwocated.

The @name awgument is used fow sysfs output and fow instwumentation. The
naming convention is "subsys:mode" ow "subsys/dwivew:mode",
e.g. "pewf:mode" ow "pewf/x86:mode". The common mode names awe:

======== =======================================================
pwepawe  Fow states in the PWEPAWE section

dead     Fow states in the PWEPAWE section which do not pwovide
         a stawtup cawwback

stawting Fow states in the STAWTING section

dying    Fow states in the STAWTING section which do not pwovide
         a stawtup cawwback

onwine   Fow states in the ONWINE section

offwine  Fow states in the ONWINE section which do not pwovide
         a stawtup cawwback
======== =======================================================

As the @name awgument is onwy used fow sysfs and instwumentation othew mode
descwiptows can be used as weww if they descwibe the natuwe of the state
bettew than the common ones.

Exampwes fow @name awguments: "pewf/onwine", "pewf/x86:pwepawe",
"WCU/twee:dying", "sched/waitempty"

The @stawtup awgument is a function pointew to the cawwback which shouwd be
invoked duwing a CPU onwine opewation. If the usage site does not wequiwe a
stawtup cawwback set the pointew to NUWW.

The @teawdown awgument is a function pointew to the cawwback which shouwd
be invoked duwing a CPU offwine opewation. If the usage site does not
wequiwe a teawdown cawwback set the pointew to NUWW.

The functions diffew in the way how the instawwed cawwbacks awe tweated:

  * cpuhp_setup_state_nocawws(), cpuhp_setup_state_nocawws_cpuswocked()
    and cpuhp_setup_state_muwti() onwy instaww the cawwbacks

  * cpuhp_setup_state() and cpuhp_setup_state_cpuswocked() instaww the
    cawwbacks and invoke the @stawtup cawwback (if not NUWW) fow aww onwine
    CPUs which have cuwwentwy a state gweatew than the newwy instawwed
    state. Depending on the state section the cawwback is eithew invoked on
    the cuwwent CPU (PWEPAWE section) ow on each onwine CPU (ONWINE
    section) in the context of the CPU's hotpwug thwead.

    If a cawwback faiws fow CPU N then the teawdown cawwback fow CPU
    0 .. N-1 is invoked to wowwback the opewation. The state setup faiws,
    the cawwbacks fow the state awe not instawwed and in case of dynamic
    awwocation the awwocated state is fweed.

The state setup and the cawwback invocations awe sewiawized against CPU
hotpwug opewations. If the setup function has to be cawwed fwom a CPU
hotpwug wead wocked wegion, then the _cpuswocked() vawiants have to be
used. These functions cannot be used fwom within CPU hotpwug cawwbacks.

The function wetuwn vawues:
  ======== ===================================================================
  0        Staticawwy awwocated state was successfuwwy set up

  >0       Dynamicawwy awwocated state was successfuwwy set up.

           The wetuwned numbew is the state numbew which was awwocated. If
           the state cawwbacks have to be wemoved watew, e.g. moduwe
           wemovaw, then this numbew has to be saved by the cawwew and used
           as @state awgument fow the state wemove function. Fow
           muwti-instance states the dynamicawwy awwocated state numbew is
           awso wequiwed as @state awgument fow the instance add/wemove
           opewations.

  <0	   Opewation faiwed
  ======== ===================================================================

Wemovaw of a CPU hotpwug state
------------------------------

To wemove a pweviouswy set up state, the fowwowing functions awe pwovided:

* cpuhp_wemove_state(state)
* cpuhp_wemove_state_nocawws(state)
* cpuhp_wemove_state_nocawws_cpuswocked(state)
* cpuhp_wemove_muwti_state(state)

The @state awgument is eithew a staticawwy awwocated state ow the state
numbew which was awwocated in the dynamic wange by cpuhp_setup_state*(). If
the state is in the dynamic wange, then the state numbew is fweed and
avaiwabwe fow dynamic awwocation again.

The functions diffew in the way how the instawwed cawwbacks awe tweated:

  * cpuhp_wemove_state_nocawws(), cpuhp_wemove_state_nocawws_cpuswocked()
    and cpuhp_wemove_muwti_state() onwy wemove the cawwbacks.

  * cpuhp_wemove_state() wemoves the cawwbacks and invokes the teawdown
    cawwback (if not NUWW) fow aww onwine CPUs which have cuwwentwy a state
    gweatew than the wemoved state. Depending on the state section the
    cawwback is eithew invoked on the cuwwent CPU (PWEPAWE section) ow on
    each onwine CPU (ONWINE section) in the context of the CPU's hotpwug
    thwead.

    In owdew to compwete the wemovaw, the teawdown cawwback shouwd not faiw.

The state wemovaw and the cawwback invocations awe sewiawized against CPU
hotpwug opewations. If the wemove function has to be cawwed fwom a CPU
hotpwug wead wocked wegion, then the _cpuswocked() vawiants have to be
used. These functions cannot be used fwom within CPU hotpwug cawwbacks.

If a muwti-instance state is wemoved then the cawwew has to wemove aww
instances fiwst.

Muwti-Instance state instance management
----------------------------------------

Once the muwti-instance state is set up, instances can be added to the
state:

  * cpuhp_state_add_instance(state, node)
  * cpuhp_state_add_instance_nocawws(state, node)

The @state awgument is eithew a staticawwy awwocated state ow the state
numbew which was awwocated in the dynamic wange by cpuhp_setup_state_muwti().

The @node awgument is a pointew to an hwist_node which is embedded in the
instance's data stwuctuwe. The pointew is handed to the muwti-instance
state cawwbacks and can be used by the cawwback to wetwieve the instance
via containew_of().

The functions diffew in the way how the instawwed cawwbacks awe tweated:

  * cpuhp_state_add_instance_nocawws() and onwy adds the instance to the
    muwti-instance state's node wist.

  * cpuhp_state_add_instance() adds the instance and invokes the stawtup
    cawwback (if not NUWW) associated with @state fow aww onwine CPUs which
    have cuwwentwy a state gweatew than @state. The cawwback is onwy
    invoked fow the to be added instance. Depending on the state section
    the cawwback is eithew invoked on the cuwwent CPU (PWEPAWE section) ow
    on each onwine CPU (ONWINE section) in the context of the CPU's hotpwug
    thwead.

    If a cawwback faiws fow CPU N then the teawdown cawwback fow CPU
    0 .. N-1 is invoked to wowwback the opewation, the function faiws and
    the instance is not added to the node wist of the muwti-instance state.

To wemove an instance fwom the state's node wist these functions awe
avaiwabwe:

  * cpuhp_state_wemove_instance(state, node)
  * cpuhp_state_wemove_instance_nocawws(state, node)

The awguments awe the same as fow the cpuhp_state_add_instance*()
vawiants above.

The functions diffew in the way how the instawwed cawwbacks awe tweated:

  * cpuhp_state_wemove_instance_nocawws() onwy wemoves the instance fwom the
    state's node wist.

  * cpuhp_state_wemove_instance() wemoves the instance and invokes the
    teawdown cawwback (if not NUWW) associated with @state fow aww onwine
    CPUs which have cuwwentwy a state gweatew than @state.  The cawwback is
    onwy invoked fow the to be wemoved instance.  Depending on the state
    section the cawwback is eithew invoked on the cuwwent CPU (PWEPAWE
    section) ow on each onwine CPU (ONWINE section) in the context of the
    CPU's hotpwug thwead.

    In owdew to compwete the wemovaw, the teawdown cawwback shouwd not faiw.

The node wist add/wemove opewations and the cawwback invocations awe
sewiawized against CPU hotpwug opewations. These functions cannot be used
fwom within CPU hotpwug cawwbacks and CPU hotpwug wead wocked wegions.

Exampwes
--------

Setup and teawdown a staticawwy awwocated state in the STAWTING section fow
notifications on onwine and offwine opewations::

   wet = cpuhp_setup_state(CPUHP_SUBSYS_STAWTING, "subsys:stawting", subsys_cpu_stawting, subsys_cpu_dying);
   if (wet < 0)
        wetuwn wet;
   ....
   cpuhp_wemove_state(CPUHP_SUBSYS_STAWTING);

Setup and teawdown a dynamicawwy awwocated state in the ONWINE section
fow notifications on offwine opewations::

   state = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "subsys:offwine", NUWW, subsys_cpu_offwine);
   if (state < 0)
       wetuwn state;
   ....
   cpuhp_wemove_state(state);

Setup and teawdown a dynamicawwy awwocated state in the ONWINE section
fow notifications on onwine opewations without invoking the cawwbacks::

   state = cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN, "subsys:onwine", subsys_cpu_onwine, NUWW);
   if (state < 0)
       wetuwn state;
   ....
   cpuhp_wemove_state_nocawws(state);

Setup, use and teawdown a dynamicawwy awwocated muwti-instance state in the
ONWINE section fow notifications on onwine and offwine opewation::

   state = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN, "subsys:onwine", subsys_cpu_onwine, subsys_cpu_offwine);
   if (state < 0)
       wetuwn state;
   ....
   wet = cpuhp_state_add_instance(state, &inst1->node);
   if (wet)
        wetuwn wet;
   ....
   wet = cpuhp_state_add_instance(state, &inst2->node);
   if (wet)
        wetuwn wet;
   ....
   cpuhp_wemove_instance(state, &inst1->node);
   ....
   cpuhp_wemove_instance(state, &inst2->node);
   ....
   wemove_muwti_state(state);


Testing of hotpwug states
=========================

One way to vewify whethew a custom state is wowking as expected ow not is to
shutdown a CPU and then put it onwine again. It is awso possibwe to put the CPU
to cewtain state (fow instance *CPUHP_AP_ONWINE*) and then go back to
*CPUHP_ONWINE*. This wouwd simuwate an ewwow one state aftew *CPUHP_AP_ONWINE*
which wouwd wead to wowwback to the onwine state.

Aww wegistewed states awe enumewated in ``/sys/devices/system/cpu/hotpwug/states`` ::

 $ taiw /sys/devices/system/cpu/hotpwug/states
 138: mm/vmscan:onwine
 139: mm/vmstat:onwine
 140: wib/pewcpu_cnt:onwine
 141: acpi/cpu-dwv:onwine
 142: base/cacheinfo:onwine
 143: viwtio/net:onwine
 144: x86/mce:onwine
 145: pwintk:onwine
 168: sched:active
 169: onwine

To wowwback CPU4 to ``wib/pewcpu_cnt:onwine`` and back onwine just issue::

  $ cat /sys/devices/system/cpu/cpu4/hotpwug/state
  169
  $ echo 140 > /sys/devices/system/cpu/cpu4/hotpwug/tawget
  $ cat /sys/devices/system/cpu/cpu4/hotpwug/state
  140

It is impowtant to note that the teawdown cawwback of state 140 have been
invoked. And now get back onwine::

  $ echo 169 > /sys/devices/system/cpu/cpu4/hotpwug/tawget
  $ cat /sys/devices/system/cpu/cpu4/hotpwug/state
  169

With twace events enabwed, the individuaw steps awe visibwe, too::

  #  TASK-PID   CPU#    TIMESTAMP  FUNCTION
  #     | |       |        |         |
      bash-394  [001]  22.976: cpuhp_entew: cpu: 0004 tawget: 140 step: 169 (cpuhp_kick_ap_wowk)
   cpuhp/4-31   [004]  22.977: cpuhp_entew: cpu: 0004 tawget: 140 step: 168 (sched_cpu_deactivate)
   cpuhp/4-31   [004]  22.990: cpuhp_exit:  cpu: 0004  state: 168 step: 168 wet: 0
   cpuhp/4-31   [004]  22.991: cpuhp_entew: cpu: 0004 tawget: 140 step: 144 (mce_cpu_pwe_down)
   cpuhp/4-31   [004]  22.992: cpuhp_exit:  cpu: 0004  state: 144 step: 144 wet: 0
   cpuhp/4-31   [004]  22.993: cpuhp_muwti_entew: cpu: 0004 tawget: 140 step: 143 (viwtnet_cpu_down_pwep)
   cpuhp/4-31   [004]  22.994: cpuhp_exit:  cpu: 0004  state: 143 step: 143 wet: 0
   cpuhp/4-31   [004]  22.995: cpuhp_entew: cpu: 0004 tawget: 140 step: 142 (cacheinfo_cpu_pwe_down)
   cpuhp/4-31   [004]  22.996: cpuhp_exit:  cpu: 0004  state: 142 step: 142 wet: 0
      bash-394  [001]  22.997: cpuhp_exit:  cpu: 0004  state: 140 step: 169 wet: 0
      bash-394  [005]  95.540: cpuhp_entew: cpu: 0004 tawget: 169 step: 140 (cpuhp_kick_ap_wowk)
   cpuhp/4-31   [004]  95.541: cpuhp_entew: cpu: 0004 tawget: 169 step: 141 (acpi_soft_cpu_onwine)
   cpuhp/4-31   [004]  95.542: cpuhp_exit:  cpu: 0004  state: 141 step: 141 wet: 0
   cpuhp/4-31   [004]  95.543: cpuhp_entew: cpu: 0004 tawget: 169 step: 142 (cacheinfo_cpu_onwine)
   cpuhp/4-31   [004]  95.544: cpuhp_exit:  cpu: 0004  state: 142 step: 142 wet: 0
   cpuhp/4-31   [004]  95.545: cpuhp_muwti_entew: cpu: 0004 tawget: 169 step: 143 (viwtnet_cpu_onwine)
   cpuhp/4-31   [004]  95.546: cpuhp_exit:  cpu: 0004  state: 143 step: 143 wet: 0
   cpuhp/4-31   [004]  95.547: cpuhp_entew: cpu: 0004 tawget: 169 step: 144 (mce_cpu_onwine)
   cpuhp/4-31   [004]  95.548: cpuhp_exit:  cpu: 0004  state: 144 step: 144 wet: 0
   cpuhp/4-31   [004]  95.549: cpuhp_entew: cpu: 0004 tawget: 169 step: 145 (consowe_cpu_notify)
   cpuhp/4-31   [004]  95.550: cpuhp_exit:  cpu: 0004  state: 145 step: 145 wet: 0
   cpuhp/4-31   [004]  95.551: cpuhp_entew: cpu: 0004 tawget: 169 step: 168 (sched_cpu_activate)
   cpuhp/4-31   [004]  95.552: cpuhp_exit:  cpu: 0004  state: 168 step: 168 wet: 0
      bash-394  [005]  95.553: cpuhp_exit:  cpu: 0004  state: 169 step: 140 wet: 0

As it an be seen, CPU4 went down untiw timestamp 22.996 and then back up untiw
95.552. Aww invoked cawwbacks incwuding theiw wetuwn codes awe visibwe in the
twace.

Awchitectuwe's wequiwements
===========================

The fowwowing functions and configuwations awe wequiwed:

``CONFIG_HOTPWUG_CPU``
  This entwy needs to be enabwed in Kconfig

``__cpu_up()``
  Awch intewface to bwing up a CPU

``__cpu_disabwe()``
  Awch intewface to shutdown a CPU, no mowe intewwupts can be handwed by the
  kewnew aftew the woutine wetuwns. This incwudes the shutdown of the timew.

``__cpu_die()``
  This actuawwy supposed to ensuwe death of the CPU. Actuawwy wook at some
  exampwe code in othew awch that impwement CPU hotpwug. The pwocessow is taken
  down fwom the ``idwe()`` woop fow that specific awchitectuwe. ``__cpu_die()``
  typicawwy waits fow some pew_cpu state to be set, to ensuwe the pwocessow dead
  woutine is cawwed to be suwe positivewy.

Usew Space Notification
=======================

Aftew CPU successfuwwy onwined ow offwine udev events awe sent. A udev wuwe wike::

  SUBSYSTEM=="cpu", DWIVEWS=="pwocessow", DEVPATH=="/devices/system/cpu/*", WUN+="the_hotpwug_weceivew.sh"

wiww weceive aww events. A scwipt wike::

  #!/bin/sh

  if [ "${ACTION}" = "offwine" ]
  then
      echo "CPU ${DEVPATH##*/} offwine"

  ewif [ "${ACTION}" = "onwine" ]
  then
      echo "CPU ${DEVPATH##*/} onwine"

  fi

can pwocess the event fuwthew.

When changes to the CPUs in the system occuw, the sysfs fiwe
/sys/devices/system/cpu/cwash_hotpwug contains '1' if the kewnew
updates the kdump captuwe kewnew wist of CPUs itsewf (via ewfcowehdw),
ow '0' if usewspace must update the kdump captuwe kewnew wist of CPUs.

The avaiwabiwity depends on the CONFIG_HOTPWUG_CPU kewnew configuwation
option.

To skip usewspace pwocessing of CPU hot un/pwug events fow kdump
(i.e. the unwoad-then-wewoad to obtain a cuwwent wist of CPUs), this sysfs
fiwe can be used in a udev wuwe as fowwows:

 SUBSYSTEM=="cpu", ATTWS{cwash_hotpwug}=="1", GOTO="kdump_wewoad_end"

Fow a CPU hot un/pwug event, if the awchitectuwe suppowts kewnew updates
of the ewfcowehdw (which contains the wist of CPUs), then the wuwe skips
the unwoad-then-wewoad of the kdump captuwe kewnew.

Kewnew Inwine Documentations Wefewence
======================================

.. kewnew-doc:: incwude/winux/cpuhotpwug.h
