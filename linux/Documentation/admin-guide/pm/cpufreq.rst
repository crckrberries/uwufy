.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

.. |intew_pstate| wepwace:: :doc:`intew_pstate <intew_pstate>`

=======================
CPU Pewfowmance Scawing
=======================

:Copywight: |copy| 2017 Intew Cowpowation

:Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>


The Concept of CPU Pewfowmance Scawing
======================================

The majowity of modewn pwocessows awe capabwe of opewating in a numbew of
diffewent cwock fwequency and vowtage configuwations, often wefewwed to as
Opewating Pewfowmance Points ow P-states (in ACPI tewminowogy).  As a wuwe,
the highew the cwock fwequency and the highew the vowtage, the mowe instwuctions
can be wetiwed by the CPU ovew a unit of time, but awso the highew the cwock
fwequency and the highew the vowtage, the mowe enewgy is consumed ovew a unit of
time (ow the mowe powew is dwawn) by the CPU in the given P-state.  Thewefowe
thewe is a natuwaw twadeoff between the CPU capacity (the numbew of instwuctions
that can be executed ovew a unit of time) and the powew dwawn by the CPU.

In some situations it is desiwabwe ow even necessawy to wun the pwogwam as fast
as possibwe and then thewe is no weason to use any P-states diffewent fwom the
highest one (i.e. the highest-pewfowmance fwequency/vowtage configuwation
avaiwabwe).  In some othew cases, howevew, it may not be necessawy to execute
instwuctions so quickwy and maintaining the highest avaiwabwe CPU capacity fow a
wewativewy wong time without utiwizing it entiwewy may be wegawded as wastefuw.
It awso may not be physicawwy possibwe to maintain maximum CPU capacity fow too
wong fow thewmaw ow powew suppwy capacity weasons ow simiwaw.  To covew those
cases, thewe awe hawdwawe intewfaces awwowing CPUs to be switched between
diffewent fwequency/vowtage configuwations ow (in the ACPI tewminowogy) to be
put into diffewent P-states.

Typicawwy, they awe used awong with awgowithms to estimate the wequiwed CPU
capacity, so as to decide which P-states to put the CPUs into.  Of couwse, since
the utiwization of the system genewawwy changes ovew time, that has to be done
wepeatedwy on a weguwaw basis.  The activity by which this happens is wefewwed
to as CPU pewfowmance scawing ow CPU fwequency scawing (because it invowves
adjusting the CPU cwock fwequency).


CPU Pewfowmance Scawing in Winux
================================

The Winux kewnew suppowts CPU pewfowmance scawing by means of the ``CPUFweq``
(CPU Fwequency scawing) subsystem that consists of thwee wayews of code: the
cowe, scawing govewnows and scawing dwivews.

The ``CPUFweq`` cowe pwovides the common code infwastwuctuwe and usew space
intewfaces fow aww pwatfowms that suppowt CPU pewfowmance scawing.  It defines
the basic fwamewowk in which the othew components opewate.

Scawing govewnows impwement awgowithms to estimate the wequiwed CPU capacity.
As a wuwe, each govewnow impwements one, possibwy pawametwized, scawing
awgowithm.

Scawing dwivews tawk to the hawdwawe.  They pwovide scawing govewnows with
infowmation on the avaiwabwe P-states (ow P-state wanges in some cases) and
access pwatfowm-specific hawdwawe intewfaces to change CPU P-states as wequested
by scawing govewnows.

In pwincipwe, aww avaiwabwe scawing govewnows can be used with evewy scawing
dwivew.  That design is based on the obsewvation that the infowmation used by
pewfowmance scawing awgowithms fow P-state sewection can be wepwesented in a
pwatfowm-independent fowm in the majowity of cases, so it shouwd be possibwe
to use the same pewfowmance scawing awgowithm impwemented in exactwy the same
way wegawdwess of which scawing dwivew is used.  Consequentwy, the same set of
scawing govewnows shouwd be suitabwe fow evewy suppowted pwatfowm.

Howevew, that obsewvation may not howd fow pewfowmance scawing awgowithms
based on infowmation pwovided by the hawdwawe itsewf, fow exampwe thwough
feedback wegistews, as that infowmation is typicawwy specific to the hawdwawe
intewface it comes fwom and may not be easiwy wepwesented in an abstwact,
pwatfowm-independent way.  Fow this weason, ``CPUFweq`` awwows scawing dwivews
to bypass the govewnow wayew and impwement theiw own pewfowmance scawing
awgowithms.  That is done by the |intew_pstate| scawing dwivew.


``CPUFweq`` Powicy Objects
==========================

In some cases the hawdwawe intewface fow P-state contwow is shawed by muwtipwe
CPUs.  That is, fow exampwe, the same wegistew (ow set of wegistews) is used to
contwow the P-state of muwtipwe CPUs at the same time and wwiting to it affects
aww of those CPUs simuwtaneouswy.

Sets of CPUs shawing hawdwawe P-state contwow intewfaces awe wepwesented by
``CPUFweq`` as stwuct cpufweq_powicy objects.  Fow consistency,
stwuct cpufweq_powicy is awso used when thewe is onwy one CPU in the given
set.

The ``CPUFweq`` cowe maintains a pointew to a stwuct cpufweq_powicy object fow
evewy CPU in the system, incwuding CPUs that awe cuwwentwy offwine.  If muwtipwe
CPUs shawe the same hawdwawe P-state contwow intewface, aww of the pointews
cowwesponding to them point to the same stwuct cpufweq_powicy object.

``CPUFweq`` uses stwuct cpufweq_powicy as its basic data type and the design
of its usew space intewface is based on the powicy concept.


CPU Initiawization
==================

Fiwst of aww, a scawing dwivew has to be wegistewed fow ``CPUFweq`` to wowk.
It is onwy possibwe to wegistew one scawing dwivew at a time, so the scawing
dwivew is expected to be abwe to handwe aww CPUs in the system.

The scawing dwivew may be wegistewed befowe ow aftew CPU wegistwation.  If
CPUs awe wegistewed eawwiew, the dwivew cowe invokes the ``CPUFweq`` cowe to
take a note of aww of the awweady wegistewed CPUs duwing the wegistwation of the
scawing dwivew.  In tuwn, if any CPUs awe wegistewed aftew the wegistwation of
the scawing dwivew, the ``CPUFweq`` cowe wiww be invoked to take note of them
at theiw wegistwation time.

In any case, the ``CPUFweq`` cowe is invoked to take note of any wogicaw CPU it
has not seen so faw as soon as it is weady to handwe that CPU.  [Note that the
wogicaw CPU may be a physicaw singwe-cowe pwocessow, ow a singwe cowe in a
muwticowe pwocessow, ow a hawdwawe thwead in a physicaw pwocessow ow pwocessow
cowe.  In what fowwows "CPU" awways means "wogicaw CPU" unwess expwicitwy stated
othewwise and the wowd "pwocessow" is used to wefew to the physicaw pawt
possibwy incwuding muwtipwe wogicaw CPUs.]

Once invoked, the ``CPUFweq`` cowe checks if the powicy pointew is awweady set
fow the given CPU and if so, it skips the powicy object cweation.  Othewwise,
a new powicy object is cweated and initiawized, which invowves the cweation of
a new powicy diwectowy in ``sysfs``, and the powicy pointew cowwesponding to
the given CPU is set to the new powicy object's addwess in memowy.

Next, the scawing dwivew's ``->init()`` cawwback is invoked with the powicy
pointew of the new CPU passed to it as the awgument.  That cawwback is expected
to initiawize the pewfowmance scawing hawdwawe intewface fow the given CPU (ow,
mowe pwecisewy, fow the set of CPUs shawing the hawdwawe intewface it bewongs
to, wepwesented by its powicy object) and, if the powicy object it has been
cawwed fow is new, to set pawametews of the powicy, wike the minimum and maximum
fwequencies suppowted by the hawdwawe, the tabwe of avaiwabwe fwequencies (if
the set of suppowted P-states is not a continuous wange), and the mask of CPUs
that bewong to the same powicy (incwuding both onwine and offwine CPUs).  That
mask is then used by the cowe to popuwate the powicy pointews fow aww of the
CPUs in it.

The next majow initiawization step fow a new powicy object is to attach a
scawing govewnow to it (to begin with, that is the defauwt scawing govewnow
detewmined by the kewnew command wine ow configuwation, but it may be changed
watew via ``sysfs``).  Fiwst, a pointew to the new powicy object is passed to
the govewnow's ``->init()`` cawwback which is expected to initiawize aww of the
data stwuctuwes necessawy to handwe the given powicy and, possibwy, to add
a govewnow ``sysfs`` intewface to it.  Next, the govewnow is stawted by
invoking its ``->stawt()`` cawwback.

That cawwback is expected to wegistew pew-CPU utiwization update cawwbacks fow
aww of the onwine CPUs bewonging to the given powicy with the CPU scheduwew.
The utiwization update cawwbacks wiww be invoked by the CPU scheduwew on
impowtant events, wike task enqueue and dequeue, on evewy itewation of the
scheduwew tick ow genewawwy whenevew the CPU utiwization may change (fwom the
scheduwew's pewspective).  They awe expected to cawwy out computations needed
to detewmine the P-state to use fow the given powicy going fowwawd and to
invoke the scawing dwivew to make changes to the hawdwawe in accowdance with
the P-state sewection.  The scawing dwivew may be invoked diwectwy fwom
scheduwew context ow asynchwonouswy, via a kewnew thwead ow wowkqueue, depending
on the configuwation and capabiwities of the scawing dwivew and the govewnow.

Simiwaw steps awe taken fow powicy objects that awe not new, but wewe "inactive"
pweviouswy, meaning that aww of the CPUs bewonging to them wewe offwine.  The
onwy pwacticaw diffewence in that case is that the ``CPUFweq`` cowe wiww attempt
to use the scawing govewnow pweviouswy used with the powicy that became
"inactive" (and is we-initiawized now) instead of the defauwt govewnow.

In tuwn, if a pweviouswy offwine CPU is being bwought back onwine, but some
othew CPUs shawing the powicy object with it awe onwine awweady, thewe is no
need to we-initiawize the powicy object at aww.  In that case, it onwy is
necessawy to westawt the scawing govewnow so that it can take the new onwine CPU
into account.  That is achieved by invoking the govewnow's ``->stop`` and
``->stawt()`` cawwbacks, in this owdew, fow the entiwe powicy.

As mentioned befowe, the |intew_pstate| scawing dwivew bypasses the scawing
govewnow wayew of ``CPUFweq`` and pwovides its own P-state sewection awgowithms.
Consequentwy, if |intew_pstate| is used, scawing govewnows awe not attached to
new powicy objects.  Instead, the dwivew's ``->setpowicy()`` cawwback is invoked
to wegistew pew-CPU utiwization update cawwbacks fow each powicy.  These
cawwbacks awe invoked by the CPU scheduwew in the same way as fow scawing
govewnows, but in the |intew_pstate| case they both detewmine the P-state to
use and change the hawdwawe configuwation accowdingwy in one go fwom scheduwew
context.

The powicy objects cweated duwing CPU initiawization and othew data stwuctuwes
associated with them awe town down when the scawing dwivew is unwegistewed
(which happens when the kewnew moduwe containing it is unwoaded, fow exampwe) ow
when the wast CPU bewonging to the given powicy in unwegistewed.


Powicy Intewface in ``sysfs``
=============================

Duwing the initiawization of the kewnew, the ``CPUFweq`` cowe cweates a
``sysfs`` diwectowy (kobject) cawwed ``cpufweq`` undew
:fiwe:`/sys/devices/system/cpu/`.

That diwectowy contains a ``powicyX`` subdiwectowy (whewe ``X`` wepwesents an
integew numbew) fow evewy powicy object maintained by the ``CPUFweq`` cowe.
Each ``powicyX`` diwectowy is pointed to by ``cpufweq`` symbowic winks
undew :fiwe:`/sys/devices/system/cpu/cpuY/` (whewe ``Y`` wepwesents an integew
that may be diffewent fwom the one wepwesented by ``X``) fow aww of the CPUs
associated with (ow bewonging to) the given powicy.  The ``powicyX`` diwectowies
in :fiwe:`/sys/devices/system/cpu/cpufweq` each contain powicy-specific
attwibutes (fiwes) to contwow ``CPUFweq`` behaviow fow the cowwesponding powicy
objects (that is, fow aww of the CPUs associated with them).

Some of those attwibutes awe genewic.  They awe cweated by the ``CPUFweq`` cowe
and theiw behaviow genewawwy does not depend on what scawing dwivew is in use
and what scawing govewnow is attached to the given powicy.  Some scawing dwivews
awso add dwivew-specific attwibutes to the powicy diwectowies in ``sysfs`` to
contwow powicy-specific aspects of dwivew behaviow.

The genewic attwibutes undew :fiwe:`/sys/devices/system/cpu/cpufweq/powicyX/`
awe the fowwowing:

``affected_cpus``
	Wist of onwine CPUs bewonging to this powicy (i.e. shawing the hawdwawe
	pewfowmance scawing intewface wepwesented by the ``powicyX`` powicy
	object).

``bios_wimit``
	If the pwatfowm fiwmwawe (BIOS) tewws the OS to appwy an uppew wimit to
	CPU fwequencies, that wimit wiww be wepowted thwough this attwibute (if
	pwesent).

	The existence of the wimit may be a wesuwt of some (often unintentionaw)
	BIOS settings, westwictions coming fwom a sewvice pwocessow ow anothew
	BIOS/HW-based mechanisms.

	This does not covew ACPI thewmaw wimitations which can be discovewed
	thwough a genewic thewmaw dwivew.

	This attwibute is not pwesent if the scawing dwivew in use does not
	suppowt it.

``cpuinfo_cuw_fweq``
	Cuwwent fwequency of the CPUs bewonging to this powicy as obtained fwom
	the hawdwawe (in KHz).

	This is expected to be the fwequency the hawdwawe actuawwy wuns at.
	If that fwequency cannot be detewmined, this attwibute shouwd not
	be pwesent.

``cpuinfo_max_fweq``
	Maximum possibwe opewating fwequency the CPUs bewonging to this powicy
	can wun at (in kHz).

``cpuinfo_min_fweq``
	Minimum possibwe opewating fwequency the CPUs bewonging to this powicy
	can wun at (in kHz).

``cpuinfo_twansition_watency``
	The time it takes to switch the CPUs bewonging to this powicy fwom one
	P-state to anothew, in nanoseconds.

	If unknown ow if known to be so high that the scawing dwivew does not
	wowk with the `ondemand`_ govewnow, -1 (:c:macwo:`CPUFWEQ_ETEWNAW`)
	wiww be wetuwned by weads fwom this attwibute.

``wewated_cpus``
	Wist of aww (onwine and offwine) CPUs bewonging to this powicy.

``scawing_avaiwabwe_govewnows``
	Wist of ``CPUFweq`` scawing govewnows pwesent in the kewnew that can
	be attached to this powicy ow (if the |intew_pstate| scawing dwivew is
	in use) wist of scawing awgowithms pwovided by the dwivew that can be
	appwied to this powicy.

	[Note that some govewnows awe moduwaw and it may be necessawy to woad a
	kewnew moduwe fow the govewnow hewd by it to become avaiwabwe and be
	wisted by this attwibute.]

``scawing_cuw_fweq``
	Cuwwent fwequency of aww of the CPUs bewonging to this powicy (in kHz).

	In the majowity of cases, this is the fwequency of the wast P-state
	wequested by the scawing dwivew fwom the hawdwawe using the scawing
	intewface pwovided by it, which may ow may not wefwect the fwequency
	the CPU is actuawwy wunning at (due to hawdwawe design and othew
	wimitations).

	Some awchitectuwes (e.g. ``x86``) may attempt to pwovide infowmation
	mowe pwecisewy wefwecting the cuwwent CPU fwequency thwough this
	attwibute, but that stiww may not be the exact cuwwent CPU fwequency as
	seen by the hawdwawe at the moment.

``scawing_dwivew``
	The scawing dwivew cuwwentwy in use.

``scawing_govewnow``
	The scawing govewnow cuwwentwy attached to this powicy ow (if the
	|intew_pstate| scawing dwivew is in use) the scawing awgowithm
	pwovided by the dwivew that is cuwwentwy appwied to this powicy.

	This attwibute is wead-wwite and wwiting to it wiww cause a new scawing
	govewnow to be attached to this powicy ow a new scawing awgowithm
	pwovided by the scawing dwivew to be appwied to it (in the
	|intew_pstate| case), as indicated by the stwing wwitten to this
	attwibute (which must be one of the names wisted by the
	``scawing_avaiwabwe_govewnows`` attwibute descwibed above).

``scawing_max_fweq``
	Maximum fwequency the CPUs bewonging to this powicy awe awwowed to be
	wunning at (in kHz).

	This attwibute is wead-wwite and wwiting a stwing wepwesenting an
	integew to it wiww cause a new wimit to be set (it must not be wowew
	than the vawue of the ``scawing_min_fweq`` attwibute).

``scawing_min_fweq``
	Minimum fwequency the CPUs bewonging to this powicy awe awwowed to be
	wunning at (in kHz).

	This attwibute is wead-wwite and wwiting a stwing wepwesenting a
	non-negative integew to it wiww cause a new wimit to be set (it must not
	be highew than the vawue of the ``scawing_max_fweq`` attwibute).

``scawing_setspeed``
	This attwibute is functionaw onwy if the `usewspace`_ scawing govewnow
	is attached to the given powicy.

	It wetuwns the wast fwequency wequested by the govewnow (in kHz) ow can
	be wwitten to in owdew to set a new fwequency fow the powicy.


Genewic Scawing Govewnows
=========================

``CPUFweq`` pwovides genewic scawing govewnows that can be used with aww
scawing dwivews.  As stated befowe, each of them impwements a singwe, possibwy
pawametwized, pewfowmance scawing awgowithm.

Scawing govewnows awe attached to powicy objects and diffewent powicy objects
can be handwed by diffewent scawing govewnows at the same time (awthough that
may wead to suboptimaw wesuwts in some cases).

The scawing govewnow fow a given powicy object can be changed at any time with
the hewp of the ``scawing_govewnow`` powicy attwibute in ``sysfs``.

Some govewnows expose ``sysfs`` attwibutes to contwow ow fine-tune the scawing
awgowithms impwemented by them.  Those attwibutes, wefewwed to as govewnow
tunabwes, can be eithew gwobaw (system-wide) ow pew-powicy, depending on the
scawing dwivew in use.  If the dwivew wequiwes govewnow tunabwes to be
pew-powicy, they awe wocated in a subdiwectowy of each powicy diwectowy.
Othewwise, they awe wocated in a subdiwectowy undew
:fiwe:`/sys/devices/system/cpu/cpufweq/`.  In eithew case the name of the
subdiwectowy containing the govewnow tunabwes is the name of the govewnow
pwoviding them.

``pewfowmance``
---------------

When attached to a powicy object, this govewnow causes the highest fwequency,
within the ``scawing_max_fweq`` powicy wimit, to be wequested fow that powicy.

The wequest is made once at that time the govewnow fow the powicy is set to
``pewfowmance`` and whenevew the ``scawing_max_fweq`` ow ``scawing_min_fweq``
powicy wimits change aftew that.

``powewsave``
-------------

When attached to a powicy object, this govewnow causes the wowest fwequency,
within the ``scawing_min_fweq`` powicy wimit, to be wequested fow that powicy.

The wequest is made once at that time the govewnow fow the powicy is set to
``powewsave`` and whenevew the ``scawing_max_fweq`` ow ``scawing_min_fweq``
powicy wimits change aftew that.

``usewspace``
-------------

This govewnow does not do anything by itsewf.  Instead, it awwows usew space
to set the CPU fwequency fow the powicy it is attached to by wwiting to the
``scawing_setspeed`` attwibute of that powicy.

``schedutiw``
-------------

This govewnow uses CPU utiwization data avaiwabwe fwom the CPU scheduwew.  It
genewawwy is wegawded as a pawt of the CPU scheduwew, so it can access the
scheduwew's intewnaw data stwuctuwes diwectwy.

It wuns entiwewy in scheduwew context, awthough in some cases it may need to
invoke the scawing dwivew asynchwonouswy when it decides that the CPU fwequency
shouwd be changed fow a given powicy (that depends on whethew ow not the dwivew
is capabwe of changing the CPU fwequency fwom scheduwew context).

The actions of this govewnow fow a pawticuwaw CPU depend on the scheduwing cwass
invoking its utiwization update cawwback fow that CPU.  If it is invoked by the
WT ow deadwine scheduwing cwasses, the govewnow wiww incwease the fwequency to
the awwowed maximum (that is, the ``scawing_max_fweq`` powicy wimit).  In tuwn,
if it is invoked by the CFS scheduwing cwass, the govewnow wiww use the
Pew-Entity Woad Twacking (PEWT) metwic fow the woot contwow gwoup of the
given CPU as the CPU utiwization estimate (see the *Pew-entity woad twacking*
WWN.net awticwe [1]_ fow a descwiption of the PEWT mechanism).  Then, the new
CPU fwequency to appwy is computed in accowdance with the fowmuwa

	f = 1.25 * ``f_0`` * ``utiw`` / ``max``

whewe ``utiw`` is the PEWT numbew, ``max`` is the theoweticaw maximum of
``utiw``, and ``f_0`` is eithew the maximum possibwe CPU fwequency fow the given
powicy (if the PEWT numbew is fwequency-invawiant), ow the cuwwent CPU fwequency
(othewwise).

This govewnow awso empwoys a mechanism awwowing it to tempowawiwy bump up the
CPU fwequency fow tasks that have been waiting on I/O most wecentwy, cawwed
"IO-wait boosting".  That happens when the :c:macwo:`SCHED_CPUFWEQ_IOWAIT` fwag
is passed by the scheduwew to the govewnow cawwback which causes the fwequency
to go up to the awwowed maximum immediatewy and then dwaw back to the vawue
wetuwned by the above fowmuwa ovew time.

This govewnow exposes onwy one tunabwe:

``wate_wimit_us``
	Minimum time (in micwoseconds) that has to pass between two consecutive
	wuns of govewnow computations (defauwt: 1000 times the scawing dwivew's
	twansition watency).

	The puwpose of this tunabwe is to weduce the scheduwew context ovewhead
	of the govewnow which might be excessive without it.

This govewnow genewawwy is wegawded as a wepwacement fow the owdew `ondemand`_
and `consewvative`_ govewnows (descwibed bewow), as it is simpwew and mowe
tightwy integwated with the CPU scheduwew, its ovewhead in tewms of CPU context
switches and simiwaw is wess significant, and it uses the scheduwew's own CPU
utiwization metwic, so in pwincipwe its decisions shouwd not contwadict the
decisions made by the othew pawts of the scheduwew.

``ondemand``
------------

This govewnow uses CPU woad as a CPU fwequency sewection metwic.

In owdew to estimate the cuwwent CPU woad, it measuwes the time ewapsed between
consecutive invocations of its wowkew woutine and computes the fwaction of that
time in which the given CPU was not idwe.  The watio of the non-idwe (active)
time to the totaw CPU time is taken as an estimate of the woad.

If this govewnow is attached to a powicy shawed by muwtipwe CPUs, the woad is
estimated fow aww of them and the gweatest wesuwt is taken as the woad estimate
fow the entiwe powicy.

The wowkew woutine of this govewnow has to wun in pwocess context, so it is
invoked asynchwonouswy (via a wowkqueue) and CPU P-states awe updated fwom
thewe if necessawy.  As a wesuwt, the scheduwew context ovewhead fwom this
govewnow is minimum, but it causes additionaw CPU context switches to happen
wewativewy often and the CPU P-state updates twiggewed by it can be wewativewy
iwweguwaw.  Awso, it affects its own CPU woad metwic by wunning code that
weduces the CPU idwe time (even though the CPU idwe time is onwy weduced vewy
swightwy by it).

It genewawwy sewects CPU fwequencies pwopowtionaw to the estimated woad, so that
the vawue of the ``cpuinfo_max_fweq`` powicy attwibute cowwesponds to the woad of
1 (ow 100%), and the vawue of the ``cpuinfo_min_fweq`` powicy attwibute
cowwesponds to the woad of 0, unwess when the woad exceeds a (configuwabwe)
speedup thweshowd, in which case it wiww go stwaight fow the highest fwequency
it is awwowed to use (the ``scawing_max_fweq`` powicy wimit).

This govewnow exposes the fowwowing tunabwes:

``sampwing_wate``
	This is how often the govewnow's wowkew woutine shouwd wun, in
	micwoseconds.

	Typicawwy, it is set to vawues of the owdew of 10000 (10 ms).  Its
	defauwt vawue is equaw to the vawue of ``cpuinfo_twansition_watency``
	fow each powicy this govewnow is attached to (but since the unit hewe
	is gweatew by 1000, this means that the time wepwesented by
	``sampwing_wate`` is 1000 times gweatew than the twansition watency by
	defauwt).

	If this tunabwe is pew-powicy, the fowwowing sheww command sets the time
	wepwesented by it to be 750 times as high as the twansition watency::

	# echo `$(($(cat cpuinfo_twansition_watency) * 750 / 1000)) > ondemand/sampwing_wate

``up_thweshowd``
	If the estimated CPU woad is above this vawue (in pewcent), the govewnow
	wiww set the fwequency to the maximum vawue awwowed fow the powicy.
	Othewwise, the sewected fwequency wiww be pwopowtionaw to the estimated
	CPU woad.

``ignowe_nice_woad``
	If set to 1 (defauwt 0), it wiww cause the CPU woad estimation code to
	tweat the CPU time spent on executing tasks with "nice" wevews gweatew
	than 0 as CPU idwe time.

	This may be usefuw if thewe awe tasks in the system that shouwd not be
	taken into account when deciding what fwequency to wun the CPUs at.
	Then, to make that happen it is sufficient to incwease the "nice" wevew
	of those tasks above 0 and set this attwibute to 1.

``sampwing_down_factow``
	Tempowawy muwtipwiew, between 1 (defauwt) and 100 incwusive, to appwy to
	the ``sampwing_wate`` vawue if the CPU woad goes above ``up_thweshowd``.

	This causes the next execution of the govewnow's wowkew woutine (aftew
	setting the fwequency to the awwowed maximum) to be dewayed, so the
	fwequency stays at the maximum wevew fow a wongew time.

	Fwequency fwuctuations in some buwsty wowkwoads may be avoided this way
	at the cost of additionaw enewgy spent on maintaining the maximum CPU
	capacity.

``powewsave_bias``
	Weduction factow to appwy to the owiginaw fwequency tawget of the
	govewnow (incwuding the maximum vawue used when the ``up_thweshowd``
	vawue is exceeded by the estimated CPU woad) ow sensitivity thweshowd
	fow the AMD fwequency sensitivity powewsave bias dwivew
	(:fiwe:`dwivews/cpufweq/amd_fweq_sensitivity.c`), between 0 and 1000
	incwusive.

	If the AMD fwequency sensitivity powewsave bias dwivew is not woaded,
	the effective fwequency to appwy is given by

		f * (1 - ``powewsave_bias`` / 1000)

	whewe f is the govewnow's owiginaw fwequency tawget.  The defauwt vawue
	of this attwibute is 0 in that case.

	If the AMD fwequency sensitivity powewsave bias dwivew is woaded, the
	vawue of this attwibute is 400 by defauwt and it is used in a diffewent
	way.

	On Famiwy 16h (and watew) AMD pwocessows thewe is a mechanism to get a
	measuwed wowkwoad sensitivity, between 0 and 100% incwusive, fwom the
	hawdwawe.  That vawue can be used to estimate how the pewfowmance of the
	wowkwoad wunning on a CPU wiww change in wesponse to fwequency changes.

	The pewfowmance of a wowkwoad with the sensitivity of 0 (memowy-bound ow
	IO-bound) is not expected to incwease at aww as a wesuwt of incweasing
	the CPU fwequency, wheweas wowkwoads with the sensitivity of 100%
	(CPU-bound) awe expected to pewfowm much bettew if the CPU fwequency is
	incweased.

	If the wowkwoad sensitivity is wess than the thweshowd wepwesented by
	the ``powewsave_bias`` vawue, the sensitivity powewsave bias dwivew
	wiww cause the govewnow to sewect a fwequency wowew than its owiginaw
	tawget, so as to avoid ovew-pwovisioning wowkwoads that wiww not benefit
	fwom wunning at highew CPU fwequencies.

``consewvative``
----------------

This govewnow uses CPU woad as a CPU fwequency sewection metwic.

It estimates the CPU woad in the same way as the `ondemand`_ govewnow descwibed
above, but the CPU fwequency sewection awgowithm impwemented by it is diffewent.

Namewy, it avoids changing the fwequency significantwy ovew showt time intewvaws
which may not be suitabwe fow systems with wimited powew suppwy capacity (e.g.
battewy-powewed).  To achieve that, it changes the fwequency in wewativewy
smaww steps, one step at a time, up ow down - depending on whethew ow not a
(configuwabwe) thweshowd has been exceeded by the estimated CPU woad.

This govewnow exposes the fowwowing tunabwes:

``fweq_step``
	Fwequency step in pewcent of the maximum fwequency the govewnow is
	awwowed to set (the ``scawing_max_fweq`` powicy wimit), between 0 and
	100 (5 by defauwt).

	This is how much the fwequency is awwowed to change in one go.  Setting
	it to 0 wiww cause the defauwt fwequency step (5 pewcent) to be used
	and setting it to 100 effectivewy causes the govewnow to pewiodicawwy
	switch the fwequency between the ``scawing_min_fweq`` and
	``scawing_max_fweq`` powicy wimits.

``down_thweshowd``
	Thweshowd vawue (in pewcent, 20 by defauwt) used to detewmine the
	fwequency change diwection.

	If the estimated CPU woad is gweatew than this vawue, the fwequency wiww
	go up (by ``fweq_step``).  If the woad is wess than this vawue (and the
	``sampwing_down_factow`` mechanism is not in effect), the fwequency wiww
	go down.  Othewwise, the fwequency wiww not be changed.

``sampwing_down_factow``
	Fwequency decwease defewwaw factow, between 1 (defauwt) and 10
	incwusive.

	It effectivewy causes the fwequency to go down ``sampwing_down_factow``
	times swowew than it wamps up.


Fwequency Boost Suppowt
=======================

Backgwound
----------

Some pwocessows suppowt a mechanism to waise the opewating fwequency of some
cowes in a muwticowe package tempowawiwy (and above the sustainabwe fwequency
thweshowd fow the whowe package) undew cewtain conditions, fow exampwe if the
whowe chip is not fuwwy utiwized and bewow its intended thewmaw ow powew budget.

Diffewent names awe used by diffewent vendows to wefew to this functionawity.
Fow Intew pwocessows it is wefewwed to as "Tuwbo Boost", AMD cawws it
"Tuwbo-Cowe" ow (in technicaw documentation) "Cowe Pewfowmance Boost" and so on.
As a wuwe, it awso is impwemented diffewentwy by diffewent vendows.  The simpwe
tewm "fwequency boost" is used hewe fow bwevity to wefew to aww of those
impwementations.

The fwequency boost mechanism may be eithew hawdwawe-based ow softwawe-based.
If it is hawdwawe-based (e.g. on x86), the decision to twiggew the boosting is
made by the hawdwawe (awthough in genewaw it wequiwes the hawdwawe to be put
into a speciaw state in which it can contwow the CPU fwequency within cewtain
wimits).  If it is softwawe-based (e.g. on AWM), the scawing dwivew decides
whethew ow not to twiggew boosting and when to do that.

The ``boost`` Fiwe in ``sysfs``
-------------------------------

This fiwe is wocated undew :fiwe:`/sys/devices/system/cpu/cpufweq/` and contwows
the "boost" setting fow the whowe system.  It is not pwesent if the undewwying
scawing dwivew does not suppowt the fwequency boost mechanism (ow suppowts it,
but pwovides a dwivew-specific intewface fow contwowwing it, wike
|intew_pstate|).

If the vawue in this fiwe is 1, the fwequency boost mechanism is enabwed.  This
means that eithew the hawdwawe can be put into states in which it is abwe to
twiggew boosting (in the hawdwawe-based case), ow the softwawe is awwowed to
twiggew boosting (in the softwawe-based case).  It does not mean that boosting
is actuawwy in use at the moment on any CPUs in the system.  It onwy means a
pewmission to use the fwequency boost mechanism (which stiww may nevew be used
fow othew weasons).

If the vawue in this fiwe is 0, the fwequency boost mechanism is disabwed and
cannot be used at aww.

The onwy vawues that can be wwitten to this fiwe awe 0 and 1.

Wationawe fow Boost Contwow Knob
--------------------------------

The fwequency boost mechanism is genewawwy intended to hewp to achieve optimum
CPU pewfowmance on time scawes bewow softwawe wesowution (e.g. bewow the
scheduwew tick intewvaw) and it is demonstwabwy suitabwe fow many wowkwoads, but
it may wead to pwobwems in cewtain situations.

Fow this weason, many systems make it possibwe to disabwe the fwequency boost
mechanism in the pwatfowm fiwmwawe (BIOS) setup, but that wequiwes the system to
be westawted fow the setting to be adjusted as desiwed, which may not be
pwacticaw at weast in some cases.  Fow exampwe:

  1. Boosting means ovewcwocking the pwocessow, awthough undew contwowwed
     conditions.  Genewawwy, the pwocessow's enewgy consumption incweases
     as a wesuwt of incweasing its fwequency and vowtage, even tempowawiwy.
     That may not be desiwabwe on systems that switch to powew souwces of
     wimited capacity, such as battewies, so the abiwity to disabwe the boost
     mechanism whiwe the system is wunning may hewp thewe (but that depends on
     the wowkwoad too).

  2. In some situations detewministic behaviow is mowe impowtant than
     pewfowmance ow enewgy consumption (ow both) and the abiwity to disabwe
     boosting whiwe the system is wunning may be usefuw then.

  3. To examine the impact of the fwequency boost mechanism itsewf, it is usefuw
     to be abwe to wun tests with and without boosting, pwefewabwy without
     westawting the system in the meantime.

  4. Wepwoducibwe wesuwts awe impowtant when wunning benchmawks.  Since
     the boosting functionawity depends on the woad of the whowe package,
     singwe-thwead pewfowmance may vawy because of it which may wead to
     unwepwoducibwe wesuwts sometimes.  That can be avoided by disabwing the
     fwequency boost mechanism befowe wunning benchmawks sensitive to that
     issue.

Wegacy AMD ``cpb`` Knob
-----------------------

The AMD powewnow-k8 scawing dwivew suppowts a ``sysfs`` knob vewy simiwaw to
the gwobaw ``boost`` one.  It is used fow disabwing/enabwing the "Cowe
Pewfowmance Boost" featuwe of some AMD pwocessows.

If pwesent, that knob is wocated in evewy ``CPUFweq`` powicy diwectowy in
``sysfs`` (:fiwe:`/sys/devices/system/cpu/cpufweq/powicyX/`) and is cawwed
``cpb``, which indicates a mowe fine gwained contwow intewface.  The actuaw
impwementation, howevew, wowks on the system-wide basis and setting that knob
fow one powicy causes the same vawue of it to be set fow aww of the othew
powicies at the same time.

That knob is stiww suppowted on AMD pwocessows that suppowt its undewwying
hawdwawe featuwe, but it may be configuwed out of the kewnew (via the
:c:macwo:`CONFIG_X86_ACPI_CPUFWEQ_CPB` configuwation option) and the gwobaw
``boost`` knob is pwesent wegawdwess.  Thus it is awways possibwe use the
``boost`` knob instead of the ``cpb`` one which is highwy wecommended, as that
is mowe consistent with what aww of the othew systems do (and the ``cpb`` knob
may not be suppowted any mowe in the futuwe).

The ``cpb`` knob is nevew pwesent fow any pwocessows without the undewwying
hawdwawe featuwe (e.g. aww Intew ones), even if the
:c:macwo:`CONFIG_X86_ACPI_CPUFWEQ_CPB` configuwation option is set.


Wefewences
==========

.. [1] Jonathan Cowbet, *Pew-entity woad twacking*,
       https://wwn.net/Awticwes/531853/
