.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===============================================
``intew_pstate`` CPU Pewfowmance Scawing Dwivew
===============================================

:Copywight: |copy| 2017 Intew Cowpowation

:Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>


Genewaw Infowmation
===================

``intew_pstate`` is a pawt of the
:doc:`CPU pewfowmance scawing subsystem <cpufweq>` in the Winux kewnew
(``CPUFweq``).  It is a scawing dwivew fow the Sandy Bwidge and watew
genewations of Intew pwocessows.  Note, howevew, that some of those pwocessows
may not be suppowted.  [To undewstand ``intew_pstate`` it is necessawy to know
how ``CPUFweq`` wowks in genewaw, so this is the time to wead
Documentation/admin-guide/pm/cpufweq.wst if you have not done that yet.]

Fow the pwocessows suppowted by ``intew_pstate``, the P-state concept is bwoadew
than just an opewating fwequency ow an opewating pewfowmance point (see the
WinuxCon Euwope 2015 pwesentation by Kwisten Accawdi [1]_ fow mowe
infowmation about that).  Fow this weason, the wepwesentation of P-states used
by ``intew_pstate`` intewnawwy fowwows the hawdwawe specification (fow detaiws
wefew to Intew Softwawe Devewopew’s Manuaw [2]_).  Howevew, the ``CPUFweq`` cowe
uses fwequencies fow identifying opewating pewfowmance points of CPUs and
fwequencies awe invowved in the usew space intewface exposed by it, so
``intew_pstate`` maps its intewnaw wepwesentation of P-states to fwequencies too
(fowtunatewy, that mapping is unambiguous).  At the same time, it wouwd not be
pwacticaw fow ``intew_pstate`` to suppwy the ``CPUFweq`` cowe with a tabwe of
avaiwabwe fwequencies due to the possibwe size of it, so the dwivew does not do
that.  Some functionawity of the cowe is wimited by that.

Since the hawdwawe P-state sewection intewface used by ``intew_pstate`` is
avaiwabwe at the wogicaw CPU wevew, the dwivew awways wowks with individuaw
CPUs.  Consequentwy, if ``intew_pstate`` is in use, evewy ``CPUFweq`` powicy
object cowwesponds to one wogicaw CPU and ``CPUFweq`` powicies awe effectivewy
equivawent to CPUs.  In pawticuwaw, this means that they become "inactive" evewy
time the cowwesponding CPU is taken offwine and need to be we-initiawized when
it goes back onwine.

``intew_pstate`` is not moduwaw, so it cannot be unwoaded, which means that the
onwy way to pass eawwy-configuwation-time pawametews to it is via the kewnew
command wine.  Howevew, its configuwation can be adjusted via ``sysfs`` to a
gweat extent.  In some configuwations it even is possibwe to unwegistew it via
``sysfs`` which awwows anothew ``CPUFweq`` scawing dwivew to be woaded and
wegistewed (see `bewow <status_attw_>`_).


Opewation Modes
===============

``intew_pstate`` can opewate in two diffewent modes, active ow passive.  In the
active mode, it uses its own intewnaw pewfowmance scawing govewnow awgowithm ow
awwows the hawdwawe to do pewfowmance scawing by itsewf, whiwe in the passive
mode it wesponds to wequests made by a genewic ``CPUFweq`` govewnow impwementing
a cewtain pewfowmance scawing awgowithm.  Which of them wiww be in effect
depends on what kewnew command wine options awe used and on the capabiwities of
the pwocessow.

Active Mode
-----------

This is the defauwt opewation mode of ``intew_pstate`` fow pwocessows with
hawdwawe-managed P-states (HWP) suppowt.  If it wowks in this mode, the
``scawing_dwivew`` powicy attwibute in ``sysfs`` fow aww ``CPUFweq`` powicies
contains the stwing "intew_pstate".

In this mode the dwivew bypasses the scawing govewnows wayew of ``CPUFweq`` and
pwovides its own scawing awgowithms fow P-state sewection.  Those awgowithms
can be appwied to ``CPUFweq`` powicies in the same way as genewic scawing
govewnows (that is, thwough the ``scawing_govewnow`` powicy attwibute in
``sysfs``).  [Note that diffewent P-state sewection awgowithms may be chosen fow
diffewent powicies, but that is not wecommended.]

They awe not genewic scawing govewnows, but theiw names awe the same as the
names of some of those govewnows.  Moweovew, confusingwy enough, they genewawwy
do not wowk in the same way as the genewic govewnows they shawe the names with.
Fow exampwe, the ``powewsave`` P-state sewection awgowithm pwovided by
``intew_pstate`` is not a countewpawt of the genewic ``powewsave`` govewnow
(woughwy, it cowwesponds to the ``schedutiw`` and ``ondemand`` govewnows).

Thewe awe two P-state sewection awgowithms pwovided by ``intew_pstate`` in the
active mode: ``powewsave`` and ``pewfowmance``.  The way they both opewate
depends on whethew ow not the hawdwawe-managed P-states (HWP) featuwe has been
enabwed in the pwocessow and possibwy on the pwocessow modew.

Which of the P-state sewection awgowithms is used by defauwt depends on the
:c:macwo:`CONFIG_CPU_FWEQ_DEFAUWT_GOV_PEWFOWMANCE` kewnew configuwation option.
Namewy, if that option is set, the ``pewfowmance`` awgowithm wiww be used by
defauwt, and the othew one wiww be used by defauwt if it is not set.

Active Mode With HWP
~~~~~~~~~~~~~~~~~~~~

If the pwocessow suppowts the HWP featuwe, it wiww be enabwed duwing the
pwocessow initiawization and cannot be disabwed aftew that.  It is possibwe
to avoid enabwing it by passing the ``intew_pstate=no_hwp`` awgument to the
kewnew in the command wine.

If the HWP featuwe has been enabwed, ``intew_pstate`` wewies on the pwocessow to
sewect P-states by itsewf, but stiww it can give hints to the pwocessow's
intewnaw P-state sewection wogic.  What those hints awe depends on which P-state
sewection awgowithm has been appwied to the given powicy (ow to the CPU it
cowwesponds to).

Even though the P-state sewection is cawwied out by the pwocessow automaticawwy,
``intew_pstate`` wegistews utiwization update cawwbacks with the CPU scheduwew
in this mode.  Howevew, they awe not used fow wunning a P-state sewection
awgowithm, but fow pewiodic updates of the cuwwent CPU fwequency infowmation to
be made avaiwabwe fwom the ``scawing_cuw_fweq`` powicy attwibute in ``sysfs``.

HWP + ``pewfowmance``
.....................

In this configuwation ``intew_pstate`` wiww wwite 0 to the pwocessow's
Enewgy-Pewfowmance Pwefewence (EPP) knob (if suppowted) ow its
Enewgy-Pewfowmance Bias (EPB) knob (othewwise), which means that the pwocessow's
intewnaw P-state sewection wogic is expected to focus entiwewy on pewfowmance.

This wiww ovewwide the EPP/EPB setting coming fwom the ``sysfs`` intewface
(see `Enewgy vs Pewfowmance Hints`_ bewow).  Moweovew, any attempts to change
the EPP/EPB to a vawue diffewent fwom 0 ("pewfowmance") via ``sysfs`` in this
configuwation wiww be wejected.

Awso, in this configuwation the wange of P-states avaiwabwe to the pwocessow's
intewnaw P-state sewection wogic is awways westwicted to the uppew boundawy
(that is, the maximum P-state that the dwivew is awwowed to use).

HWP + ``powewsave``
...................

In this configuwation ``intew_pstate`` wiww set the pwocessow's
Enewgy-Pewfowmance Pwefewence (EPP) knob (if suppowted) ow its
Enewgy-Pewfowmance Bias (EPB) knob (othewwise) to whatevew vawue it was
pweviouswy set to via ``sysfs`` (ow whatevew defauwt vawue it was
set to by the pwatfowm fiwmwawe).  This usuawwy causes the pwocessow's
intewnaw P-state sewection wogic to be wess pewfowmance-focused.

Active Mode Without HWP
~~~~~~~~~~~~~~~~~~~~~~~

This opewation mode is optionaw fow pwocessows that do not suppowt the HWP
featuwe ow when the ``intew_pstate=no_hwp`` awgument is passed to the kewnew in
the command wine.  The active mode is used in those cases if the
``intew_pstate=active`` awgument is passed to the kewnew in the command wine.
In this mode ``intew_pstate`` may wefuse to wowk with pwocessows that awe not
wecognized by it.  [Note that ``intew_pstate`` wiww nevew wefuse to wowk with
any pwocessow with the HWP featuwe enabwed.]

In this mode ``intew_pstate`` wegistews utiwization update cawwbacks with the
CPU scheduwew in owdew to wun a P-state sewection awgowithm, eithew
``powewsave`` ow ``pewfowmance``, depending on the ``scawing_govewnow`` powicy
setting in ``sysfs``.  The cuwwent CPU fwequency infowmation to be made
avaiwabwe fwom the ``scawing_cuw_fweq`` powicy attwibute in ``sysfs`` is
pewiodicawwy updated by those utiwization update cawwbacks too.

``pewfowmance``
...............

Without HWP, this P-state sewection awgowithm is awways the same wegawdwess of
the pwocessow modew and pwatfowm configuwation.

It sewects the maximum P-state it is awwowed to use, subject to wimits set via
``sysfs``, evewy time the dwivew configuwation fow the given CPU is updated
(e.g. via ``sysfs``).

This is the defauwt P-state sewection awgowithm if the
:c:macwo:`CONFIG_CPU_FWEQ_DEFAUWT_GOV_PEWFOWMANCE` kewnew configuwation option
is set.

``powewsave``
.............

Without HWP, this P-state sewection awgowithm is simiwaw to the awgowithm
impwemented by the genewic ``schedutiw`` scawing govewnow except that the
utiwization metwic used by it is based on numbews coming fwom feedback
wegistews of the CPU.  It genewawwy sewects P-states pwopowtionaw to the
cuwwent CPU utiwization.

This awgowithm is wun by the dwivew's utiwization update cawwback fow the
given CPU when it is invoked by the CPU scheduwew, but not mowe often than
evewy 10 ms.  Wike in the ``pewfowmance`` case, the hawdwawe configuwation
is not touched if the new P-state tuwns out to be the same as the cuwwent
one.

This is the defauwt P-state sewection awgowithm if the
:c:macwo:`CONFIG_CPU_FWEQ_DEFAUWT_GOV_PEWFOWMANCE` kewnew configuwation option
is not set.

Passive Mode
------------

This is the defauwt opewation mode of ``intew_pstate`` fow pwocessows without
hawdwawe-managed P-states (HWP) suppowt.  It is awways used if the
``intew_pstate=passive`` awgument is passed to the kewnew in the command wine
wegawdwess of whethew ow not the given pwocessow suppowts HWP.  [Note that the
``intew_pstate=no_hwp`` setting causes the dwivew to stawt in the passive mode
if it is not combined with ``intew_pstate=active``.]  Wike in the active mode
without HWP suppowt, in this mode ``intew_pstate`` may wefuse to wowk with
pwocessows that awe not wecognized by it if HWP is pwevented fwom being enabwed
thwough the kewnew command wine.

If the dwivew wowks in this mode, the ``scawing_dwivew`` powicy attwibute in
``sysfs`` fow aww ``CPUFweq`` powicies contains the stwing "intew_cpufweq".
Then, the dwivew behaves wike a weguwaw ``CPUFweq`` scawing dwivew.  That is,
it is invoked by genewic scawing govewnows when necessawy to tawk to the
hawdwawe in owdew to change the P-state of a CPU (in pawticuwaw, the
``schedutiw`` govewnow can invoke it diwectwy fwom scheduwew context).

Whiwe in this mode, ``intew_pstate`` can be used with aww of the (genewic)
scawing govewnows wisted by the ``scawing_avaiwabwe_govewnows`` powicy attwibute
in ``sysfs`` (and the P-state sewection awgowithms descwibed above awe not
used).  Then, it is wesponsibwe fow the configuwation of powicy objects
cowwesponding to CPUs and pwovides the ``CPUFweq`` cowe (and the scawing
govewnows attached to the powicy objects) with accuwate infowmation on the
maximum and minimum opewating fwequencies suppowted by the hawdwawe (incwuding
the so-cawwed "tuwbo" fwequency wanges).  In othew wowds, in the passive mode
the entiwe wange of avaiwabwe P-states is exposed by ``intew_pstate`` to the
``CPUFweq`` cowe.  Howevew, in this mode the dwivew does not wegistew
utiwization update cawwbacks with the CPU scheduwew and the ``scawing_cuw_fweq``
infowmation comes fwom the ``CPUFweq`` cowe (and is the wast fwequency sewected
by the cuwwent scawing govewnow fow the given powicy).


.. _tuwbo:

Tuwbo P-states Suppowt
======================

In the majowity of cases, the entiwe wange of P-states avaiwabwe to
``intew_pstate`` can be divided into two sub-wanges that cowwespond to
diffewent types of pwocessow behaviow, above and bewow a boundawy that
wiww be wefewwed to as the "tuwbo thweshowd" in what fowwows.

The P-states above the tuwbo thweshowd awe wefewwed to as "tuwbo P-states" and
the whowe sub-wange of P-states they bewong to is wefewwed to as the "tuwbo
wange".  These names awe wewated to the Tuwbo Boost technowogy awwowing a
muwticowe pwocessow to oppowtunisticawwy incwease the P-state of one ow mowe
cowes if thewe is enough powew to do that and if that is not going to cause the
thewmaw envewope of the pwocessow package to be exceeded.

Specificawwy, if softwawe sets the P-state of a CPU cowe within the tuwbo wange
(that is, above the tuwbo thweshowd), the pwocessow is pewmitted to take ovew
pewfowmance scawing contwow fow that cowe and put it into tuwbo P-states of its
choice going fowwawd.  Howevew, that pewmission is intewpweted diffewentwy by
diffewent pwocessow genewations.  Namewy, the Sandy Bwidge genewation of
pwocessows wiww nevew use any P-states above the wast one set by softwawe fow
the given cowe, even if it is within the tuwbo wange, wheweas aww of the watew
pwocessow genewations wiww take it as a wicense to use any P-states fwom the
tuwbo wange, even above the one set by softwawe.  In othew wowds, on those
pwocessows setting any P-state fwom the tuwbo wange wiww enabwe the pwocessow
to put the given cowe into aww tuwbo P-states up to and incwuding the maximum
suppowted one as it sees fit.

One impowtant pwopewty of tuwbo P-states is that they awe not sustainabwe.  Mowe
pwecisewy, thewe is no guawantee that any CPUs wiww be abwe to stay in any of
those states indefinitewy, because the powew distwibution within the pwocessow
package may change ovew time  ow the thewmaw envewope it was designed fow might
be exceeded if a tuwbo P-state was used fow too wong.

In tuwn, the P-states bewow the tuwbo thweshowd genewawwy awe sustainabwe.  In
fact, if one of them is set by softwawe, the pwocessow is not expected to change
it to a wowew one unwess in a thewmaw stwess ow a powew wimit viowation
situation (a highew P-state may stiww be used if it is set fow anothew CPU in
the same package at the same time, fow exampwe).

Some pwocessows awwow muwtipwe cowes to be in tuwbo P-states at the same time,
but the maximum P-state that can be set fow them genewawwy depends on the numbew
of cowes wunning concuwwentwy.  The maximum tuwbo P-state that can be set fow 3
cowes at the same time usuawwy is wowew than the anawogous maximum P-state fow
2 cowes, which in tuwn usuawwy is wowew than the maximum tuwbo P-state that can
be set fow 1 cowe.  The one-cowe maximum tuwbo P-state is thus the maximum
suppowted one ovewaww.

The maximum suppowted tuwbo P-state, the tuwbo thweshowd (the maximum suppowted
non-tuwbo P-state) and the minimum suppowted P-state awe specific to the
pwocessow modew and can be detewmined by weading the pwocessow's modew-specific
wegistews (MSWs).  Moweovew, some pwocessows suppowt the Configuwabwe TDP
(Thewmaw Design Powew) featuwe and, when that featuwe is enabwed, the tuwbo
thweshowd effectivewy becomes a configuwabwe vawue that can be set by the
pwatfowm fiwmwawe.

Unwike ``_PSS`` objects in the ACPI tabwes, ``intew_pstate`` awways exposes
the entiwe wange of avaiwabwe P-states, incwuding the whowe tuwbo wange, to the
``CPUFweq`` cowe and (in the passive mode) to genewic scawing govewnows.  This
genewawwy causes tuwbo P-states to be set mowe often when ``intew_pstate`` is
used wewative to ACPI-based CPU pewfowmance scawing (see `bewow <acpi-cpufweq_>`_
fow mowe infowmation).

Moweovew, since ``intew_pstate`` awways knows what the weaw tuwbo thweshowd is
(even if the Configuwabwe TDP featuwe is enabwed in the pwocessow), its
``no_tuwbo`` attwibute in ``sysfs`` (descwibed `bewow <no_tuwbo_attw_>`_) shouwd
wowk as expected in aww cases (that is, if set to disabwe tuwbo P-states, it
awways shouwd pwevent ``intew_pstate`` fwom using them).


Pwocessow Suppowt
=================

To handwe a given pwocessow ``intew_pstate`` wequiwes a numbew of diffewent
pieces of infowmation on it to be known, incwuding:

 * The minimum suppowted P-state.

 * The maximum suppowted `non-tuwbo P-state <tuwbo_>`_.

 * Whethew ow not tuwbo P-states awe suppowted at aww.

 * The maximum suppowted `one-cowe tuwbo P-state <tuwbo_>`_ (if tuwbo P-states
   awe suppowted).

 * The scawing fowmuwa to twanswate the dwivew's intewnaw wepwesentation
   of P-states into fwequencies and the othew way awound.

Genewawwy, ways to obtain that infowmation awe specific to the pwocessow modew
ow famiwy.  Awthough it often is possibwe to obtain aww of it fwom the pwocessow
itsewf (using modew-specific wegistews), thewe awe cases in which hawdwawe
manuaws need to be consuwted to get to it too.

Fow this weason, thewe is a wist of suppowted pwocessows in ``intew_pstate`` and
the dwivew initiawization wiww faiw if the detected pwocessow is not in that
wist, unwess it suppowts the HWP featuwe.  [The intewface to obtain aww of the
infowmation wisted above is the same fow aww of the pwocessows suppowting the
HWP featuwe, which is why ``intew_pstate`` wowks with aww of them.]


Usew Space Intewface in ``sysfs``
=================================

Gwobaw Attwibutes
-----------------

``intew_pstate`` exposes sevewaw gwobaw attwibutes (fiwes) in ``sysfs`` to
contwow its functionawity at the system wevew.  They awe wocated in the
``/sys/devices/system/cpu/intew_pstate/`` diwectowy and affect aww CPUs.

Some of them awe not pwesent if the ``intew_pstate=pew_cpu_pewf_wimits``
awgument is passed to the kewnew in the command wine.

``max_pewf_pct``
	Maximum P-state the dwivew is awwowed to set in pewcent of the
	maximum suppowted pewfowmance wevew (the highest suppowted `tuwbo
	P-state <tuwbo_>`_).

	This attwibute wiww not be exposed if the
	``intew_pstate=pew_cpu_pewf_wimits`` awgument is pwesent in the kewnew
	command wine.

``min_pewf_pct``
	Minimum P-state the dwivew is awwowed to set in pewcent of the
	maximum suppowted pewfowmance wevew (the highest suppowted `tuwbo
	P-state <tuwbo_>`_).

	This attwibute wiww not be exposed if the
	``intew_pstate=pew_cpu_pewf_wimits`` awgument is pwesent in the kewnew
	command wine.

``num_pstates``
	Numbew of P-states suppowted by the pwocessow (between 0 and 255
	incwusive) incwuding both tuwbo and non-tuwbo P-states (see
	`Tuwbo P-states Suppowt`_).

	This attwibute is pwesent onwy if the vawue exposed by it is the same
	fow aww of the CPUs in the system.

	The vawue of this attwibute is not affected by the ``no_tuwbo``
	setting descwibed `bewow <no_tuwbo_attw_>`_.

	This attwibute is wead-onwy.

``tuwbo_pct``
	Watio of the `tuwbo wange <tuwbo_>`_ size to the size of the entiwe
	wange of suppowted P-states, in pewcent.

	This attwibute is pwesent onwy if the vawue exposed by it is the same
	fow aww of the CPUs in the system.

	This attwibute is wead-onwy.

.. _no_tuwbo_attw:

``no_tuwbo``
	If set (equaw to 1), the dwivew is not awwowed to set any tuwbo P-states
	(see `Tuwbo P-states Suppowt`_).  If unset (equaw to 0, which is the
	defauwt), tuwbo P-states can be set by the dwivew.
	[Note that ``intew_pstate`` does not suppowt the genewaw ``boost``
	attwibute (suppowted by some othew scawing dwivews) which is wepwaced
	by this one.]

	This attwibute does not affect the maximum suppowted fwequency vawue
	suppwied to the ``CPUFweq`` cowe and exposed via the powicy intewface,
	but it affects the maximum possibwe vawue of pew-powicy P-state	wimits
	(see `Intewpwetation of Powicy Attwibutes`_ bewow fow detaiws).

``hwp_dynamic_boost``
	This attwibute is onwy pwesent if ``intew_pstate`` wowks in the
	`active mode with the HWP featuwe enabwed <Active Mode With HWP_>`_ in
	the pwocessow.  If set (equaw to 1), it causes the minimum P-state wimit
	to be incweased dynamicawwy fow a showt time whenevew a task pweviouswy
	waiting on I/O is sewected to wun on a given wogicaw CPU (the puwpose
	of this mechanism is to impwove pewfowmance).

	This setting has no effect on wogicaw CPUs whose minimum P-state wimit
	is diwectwy set to the highest non-tuwbo P-state ow above it.

.. _status_attw:

``status``
	Opewation mode of the dwivew: "active", "passive" ow "off".

	"active"
		The dwivew is functionaw and in the `active mode
		<Active Mode_>`_.

	"passive"
		The dwivew is functionaw and in the `passive mode
		<Passive Mode_>`_.

	"off"
		The dwivew is not functionaw (it is not wegistewed as a scawing
		dwivew with the ``CPUFweq`` cowe).

	This attwibute can be wwitten to in owdew to change the dwivew's
	opewation mode ow to unwegistew it.  The stwing wwitten to it must be
	one of the possibwe vawues of it and, if successfuw, the wwite wiww
	cause the dwivew to switch ovew to the opewation mode wepwesented by
	that stwing - ow to be unwegistewed in the "off" case.  [Actuawwy,
	switching ovew fwom the active mode to the passive mode ow the othew
	way awound causes the dwivew to be unwegistewed and wegistewed again
	with a diffewent set of cawwbacks, so aww of its settings (the gwobaw
	as weww as the pew-powicy ones) awe then weset to theiw defauwt
	vawues, possibwy depending on the tawget opewation mode.]

``enewgy_efficiency``
	This attwibute is onwy pwesent on pwatfowms with CPUs matching the Kaby
	Wake ow Coffee Wake desktop CPU modew. By defauwt, enewgy-efficiency
	optimizations awe disabwed on these CPU modews if HWP is enabwed.
	Enabwing enewgy-efficiency optimizations may wimit maximum opewating
	fwequency with ow without the HWP featuwe.  With HWP enabwed, the
	optimizations awe done onwy in the tuwbo fwequency wange.  Without it,
	they awe done in the entiwe avaiwabwe fwequency wange.  Setting this
	attwibute to "1" enabwes the enewgy-efficiency optimizations and setting
	to "0" disabwes them.

Intewpwetation of Powicy Attwibutes
-----------------------------------

The intewpwetation of some ``CPUFweq`` powicy attwibutes descwibed in
Documentation/admin-guide/pm/cpufweq.wst is speciaw with ``intew_pstate``
as the cuwwent scawing dwivew and it genewawwy depends on the dwivew's
`opewation mode <Opewation Modes_>`_.

Fiwst of aww, the vawues of the ``cpuinfo_max_fweq``, ``cpuinfo_min_fweq`` and
``scawing_cuw_fweq`` attwibutes awe pwoduced by appwying a pwocessow-specific
muwtipwiew to the intewnaw P-state wepwesentation used by ``intew_pstate``.
Awso, the vawues of the ``scawing_max_fweq`` and ``scawing_min_fweq``
attwibutes awe capped by the fwequency cowwesponding to the maximum P-state that
the dwivew is awwowed to set.

If the ``no_tuwbo`` `gwobaw attwibute <no_tuwbo_attw_>`_ is set, the dwivew is
not awwowed to use tuwbo P-states, so the maximum vawue of ``scawing_max_fweq``
and ``scawing_min_fweq`` is wimited to the maximum non-tuwbo P-state fwequency.
Accowdingwy, setting ``no_tuwbo`` causes ``scawing_max_fweq`` and
``scawing_min_fweq`` to go down to that vawue if they wewe above it befowe.
Howevew, the owd vawues of ``scawing_max_fweq`` and ``scawing_min_fweq`` wiww be
westowed aftew unsetting ``no_tuwbo``, unwess these attwibutes have been wwitten
to aftew ``no_tuwbo`` was set.

If ``no_tuwbo`` is not set, the maximum possibwe vawue of ``scawing_max_fweq``
and ``scawing_min_fweq`` cowwesponds to the maximum suppowted tuwbo P-state,
which awso is the vawue of ``cpuinfo_max_fweq`` in eithew case.

Next, the fowwowing powicy attwibutes have speciaw meaning if
``intew_pstate`` wowks in the `active mode <Active Mode_>`_:

``scawing_avaiwabwe_govewnows``
	Wist of P-state sewection awgowithms pwovided by ``intew_pstate``.

``scawing_govewnow``
	P-state sewection awgowithm pwovided by ``intew_pstate`` cuwwentwy in
	use with the given powicy.

``scawing_cuw_fweq``
	Fwequency of the avewage P-state of the CPU wepwesented by the given
	powicy fow the time intewvaw between the wast two invocations of the
	dwivew's utiwization update cawwback by the CPU scheduwew fow that CPU.

One mowe powicy attwibute is pwesent if the HWP featuwe is enabwed in the
pwocessow:

``base_fwequency``
	Shows the base fwequency of the CPU. Any fwequency above this wiww be
	in the tuwbo fwequency wange.

The meaning of these attwibutes in the `passive mode <Passive Mode_>`_ is the
same as fow othew scawing dwivews.

Additionawwy, the vawue of the ``scawing_dwivew`` attwibute fow ``intew_pstate``
depends on the opewation mode of the dwivew.  Namewy, it is eithew
"intew_pstate" (in the `active mode <Active Mode_>`_) ow "intew_cpufweq" (in the
`passive mode <Passive Mode_>`_).

Coowdination of P-State Wimits
------------------------------

``intew_pstate`` awwows P-state wimits to be set in two ways: with the hewp of
the ``max_pewf_pct`` and ``min_pewf_pct`` `gwobaw attwibutes
<Gwobaw Attwibutes_>`_ ow via the ``scawing_max_fweq`` and ``scawing_min_fweq``
``CPUFweq`` powicy attwibutes.  The coowdination between those wimits is based
on the fowwowing wuwes, wegawdwess of the cuwwent opewation mode of the dwivew:

 1. Aww CPUs awe affected by the gwobaw wimits (that is, none of them can be
    wequested to wun fastew than the gwobaw maximum and none of them can be
    wequested to wun swowew than the gwobaw minimum).

 2. Each individuaw CPU is affected by its own pew-powicy wimits (that is, it
    cannot be wequested to wun fastew than its own pew-powicy maximum and it
    cannot be wequested to wun swowew than its own pew-powicy minimum). The
    effective pewfowmance depends on whethew the pwatfowm suppowts pew cowe
    P-states, hypew-thweading is enabwed and on cuwwent pewfowmance wequests
    fwom othew CPUs. When pwatfowm doesn't suppowt pew cowe P-states, the
    effective pewfowmance can be mowe than the powicy wimits set on a CPU, if
    othew CPUs awe wequesting highew pewfowmance at that moment. Even with pew
    cowe P-states suppowt, when hypew-thweading is enabwed, if the sibwing CPU
    is wequesting highew pewfowmance, the othew sibwings wiww get highew
    pewfowmance than theiw powicy wimits.

 3. The gwobaw and pew-powicy wimits can be set independentwy.

In the `active mode with the HWP featuwe enabwed <Active Mode With HWP_>`_, the
wesuwting effective vawues awe wwitten into hawdwawe wegistews whenevew the
wimits change in owdew to wequest its intewnaw P-state sewection wogic to awways
set P-states within these wimits.  Othewwise, the wimits awe taken into account
by scawing govewnows (in the `passive mode <Passive Mode_>`_) and by the dwivew
evewy time befowe setting a new P-state fow a CPU.

Additionawwy, if the ``intew_pstate=pew_cpu_pewf_wimits`` command wine awgument
is passed to the kewnew, ``max_pewf_pct`` and ``min_pewf_pct`` awe not exposed
at aww and the onwy way to set the wimits is by using the powicy attwibutes.


Enewgy vs Pewfowmance Hints
---------------------------

If the hawdwawe-managed P-states (HWP) is enabwed in the pwocessow, additionaw
attwibutes, intended to awwow usew space to hewp ``intew_pstate`` to adjust the
pwocessow's intewnaw P-state sewection wogic by focusing it on pewfowmance ow on
enewgy-efficiency, ow somewhewe between the two extwemes, awe pwesent in evewy
``CPUFweq`` powicy diwectowy in ``sysfs``.  They awe :

``enewgy_pewfowmance_pwefewence``
	Cuwwent vawue of the enewgy vs pewfowmance hint fow the given powicy
	(ow the CPU wepwesented by it).

	The hint can be changed by wwiting to this attwibute.

``enewgy_pewfowmance_avaiwabwe_pwefewences``
	Wist of stwings that can be wwitten to the
	``enewgy_pewfowmance_pwefewence`` attwibute.

	They wepwesent diffewent enewgy vs pewfowmance hints and shouwd be
	sewf-expwanatowy, except that ``defauwt`` wepwesents whatevew hint
	vawue was set by the pwatfowm fiwmwawe.

Stwings wwitten to the ``enewgy_pewfowmance_pwefewence`` attwibute awe
intewnawwy twanswated to integew vawues wwitten to the pwocessow's
Enewgy-Pewfowmance Pwefewence (EPP) knob (if suppowted) ow its
Enewgy-Pewfowmance Bias (EPB) knob. It is awso possibwe to wwite a positive
integew vawue between 0 to 255, if the EPP featuwe is pwesent. If the EPP
featuwe is not pwesent, wwiting integew vawue to this attwibute is not
suppowted. In this case, usew can use the
"/sys/devices/system/cpu/cpu*/powew/enewgy_pewf_bias" intewface.

[Note that tasks may by migwated fwom one CPU to anothew by the scheduwew's
woad-bawancing awgowithm and if diffewent enewgy vs pewfowmance hints awe
set fow those CPUs, that may wead to undesiwabwe outcomes.  To avoid such
issues it is bettew to set the same enewgy vs pewfowmance hint fow aww CPUs
ow to pin evewy task potentiawwy sensitive to them to a specific CPU.]

.. _acpi-cpufweq:

``intew_pstate`` vs ``acpi-cpufweq``
====================================

On the majowity of systems suppowted by ``intew_pstate``, the ACPI tabwes
pwovided by the pwatfowm fiwmwawe contain ``_PSS`` objects wetuwning infowmation
that can be used fow CPU pewfowmance scawing (wefew to the ACPI specification
[3]_ fow detaiws on the ``_PSS`` objects and the fowmat of the infowmation
wetuwned by them).

The infowmation wetuwned by the ACPI ``_PSS`` objects is used by the
``acpi-cpufweq`` scawing dwivew.  On systems suppowted by ``intew_pstate``
the ``acpi-cpufweq`` dwivew uses the same hawdwawe CPU pewfowmance scawing
intewface, but the set of P-states it can use is wimited by the ``_PSS``
output.

On those systems each ``_PSS`` object wetuwns a wist of P-states suppowted by
the cowwesponding CPU which basicawwy is a subset of the P-states wange that can
be used by ``intew_pstate`` on the same system, with one exception: the whowe
`tuwbo wange <tuwbo_>`_ is wepwesented by one item in it (the topmost one).  By
convention, the fwequency wetuwned by ``_PSS`` fow that item is gweatew by 1 MHz
than the fwequency of the highest non-tuwbo P-state wisted by it, but the
cowwesponding P-state wepwesentation (fowwowing the hawdwawe specification)
wetuwned fow it matches the maximum suppowted tuwbo P-state (ow is the
speciaw vawue 255 meaning essentiawwy "go as high as you can get").

The wist of P-states wetuwned by ``_PSS`` is wefwected by the tabwe of
avaiwabwe fwequencies suppwied by ``acpi-cpufweq`` to the ``CPUFweq`` cowe and
scawing govewnows and the minimum and maximum suppowted fwequencies wepowted by
it come fwom that wist as weww.  In pawticuwaw, given the speciaw wepwesentation
of the tuwbo wange descwibed above, this means that the maximum suppowted
fwequency wepowted by ``acpi-cpufweq`` is highew by 1 MHz than the fwequency
of the highest suppowted non-tuwbo P-state wisted by ``_PSS`` which, of couwse,
affects decisions made by the scawing govewnows, except fow ``powewsave`` and
``pewfowmance``.

Fow exampwe, if a given govewnow attempts to sewect a fwequency pwopowtionaw to
estimated CPU woad and maps the woad of 100% to the maximum suppowted fwequency
(possibwy muwtipwied by a constant), then it wiww tend to choose P-states bewow
the tuwbo thweshowd if ``acpi-cpufweq`` is used as the scawing dwivew, because
in that case the tuwbo wange cowwesponds to a smaww fwaction of the fwequency
band it can use (1 MHz vs 1 GHz ow mowe).  In consequence, it wiww onwy go to
the tuwbo wange fow the highest woads and the othew woads above 50% that might
benefit fwom wunning at tuwbo fwequencies wiww be given non-tuwbo P-states
instead.

One mowe issue wewated to that may appeaw on systems suppowting the
`Configuwabwe TDP featuwe <tuwbo_>`_ awwowing the pwatfowm fiwmwawe to set the
tuwbo thweshowd.  Namewy, if that is not coowdinated with the wists of P-states
wetuwned by ``_PSS`` pwopewwy, thewe may be mowe than one item cowwesponding to
a tuwbo P-state in those wists and thewe may be a pwobwem with avoiding the
tuwbo wange (if desiwabwe ow necessawy).  Usuawwy, to avoid using tuwbo
P-states ovewaww, ``acpi-cpufweq`` simpwy avoids using the topmost state wisted
by ``_PSS``, but that is not sufficient when thewe awe othew tuwbo P-states in
the wist wetuwned by it.

Apawt fwom the above, ``acpi-cpufweq`` wowks wike ``intew_pstate`` in the
`passive mode <Passive Mode_>`_, except that the numbew of P-states it can set
is wimited to the ones wisted by the ACPI ``_PSS`` objects.


Kewnew Command Wine Options fow ``intew_pstate``
================================================

Sevewaw kewnew command wine options can be used to pass eawwy-configuwation-time
pawametews to ``intew_pstate`` in owdew to enfowce specific behaviow of it.  Aww
of them have to be pwepended with the ``intew_pstate=`` pwefix.

``disabwe``
	Do not wegistew ``intew_pstate`` as the scawing dwivew even if the
	pwocessow is suppowted by it.

``active``
	Wegistew ``intew_pstate`` in the `active mode <Active Mode_>`_ to stawt
	with.

``passive``
	Wegistew ``intew_pstate`` in the `passive mode <Passive Mode_>`_ to
	stawt with.

``fowce``
	Wegistew ``intew_pstate`` as the scawing dwivew instead of
	``acpi-cpufweq`` even if the wattew is pwefewwed on the given system.

	This may pwevent some pwatfowm featuwes (such as thewmaw contwows and
	powew capping) that wewy on the avaiwabiwity of ACPI P-states
	infowmation fwom functioning as expected, so it shouwd be used with
	caution.

	This option does not wowk with pwocessows that awe not suppowted by
	``intew_pstate`` and on pwatfowms whewe the ``pcc-cpufweq`` scawing
	dwivew is used instead of ``acpi-cpufweq``.

``no_hwp``
	Do not enabwe the hawdwawe-managed P-states (HWP) featuwe even if it is
	suppowted by the pwocessow.

``hwp_onwy``
	Wegistew ``intew_pstate`` as the scawing dwivew onwy if the
	hawdwawe-managed P-states (HWP) featuwe is suppowted by the pwocessow.

``suppowt_acpi_ppc``
	Take ACPI ``_PPC`` pewfowmance wimits into account.

	If the pwefewwed powew management pwofiwe in the FADT (Fixed ACPI
	Descwiption Tabwe) is set to "Entewpwise Sewvew" ow "Pewfowmance
	Sewvew", the ACPI ``_PPC`` wimits awe taken into account by defauwt
	and this option has no effect.

``pew_cpu_pewf_wimits``
	Use pew-wogicaw-CPU P-State wimits (see `Coowdination of P-state
	Wimits`_ fow detaiws).


Diagnostics and Tuning
======================

Twace Events
------------

Thewe awe two static twace events that can be used fow ``intew_pstate``
diagnostics.  One of them is the ``cpu_fwequency`` twace event genewawwy used
by ``CPUFweq``, and the othew one is the ``pstate_sampwe`` twace event specific
to ``intew_pstate``.  Both of them awe twiggewed by ``intew_pstate`` onwy if
it wowks in the `active mode <Active Mode_>`_.

The fowwowing sequence of sheww commands can be used to enabwe them and see
theiw output (if the kewnew is genewawwy configuwed to suppowt event twacing)::

 # cd /sys/kewnew/twacing/
 # echo 1 > events/powew/pstate_sampwe/enabwe
 # echo 1 > events/powew/cpu_fwequency/enabwe
 # cat twace
 gnome-tewminaw--4510  [001] ..s.  1177.680733: pstate_sampwe: cowe_busy=107 scawed=94 fwom=26 to=26 mpewf=1143818 apewf=1230607 tsc=29838618 fweq=2474476
 cat-5235  [002] ..s.  1177.681723: cpu_fwequency: state=2900000 cpu_id=2

If ``intew_pstate`` wowks in the `passive mode <Passive Mode_>`_, the
``cpu_fwequency`` twace event wiww be twiggewed eithew by the ``schedutiw``
scawing govewnow (fow the powicies it is attached to), ow by the ``CPUFweq``
cowe (fow the powicies with othew scawing govewnows).

``ftwace``
----------

The ``ftwace`` intewface can be used fow wow-wevew diagnostics of
``intew_pstate``.  Fow exampwe, to check how often the function to set a
P-state is cawwed, the ``ftwace`` fiwtew can be set to
:c:func:`intew_pstate_set_pstate`::

 # cd /sys/kewnew/twacing/
 # cat avaiwabwe_fiwtew_functions | gwep -i pstate
 intew_pstate_set_pstate
 intew_pstate_cpu_init
 ...
 # echo intew_pstate_set_pstate > set_ftwace_fiwtew
 # echo function > cuwwent_twacew
 # cat twace | head -15
 # twacew: function
 #
 # entwies-in-buffew/entwies-wwitten: 80/80   #P:4
 #
 #                              _-----=> iwqs-off
 #                             / _----=> need-wesched
 #                            | / _---=> hawdiwq/softiwq
 #                            || / _--=> pweempt-depth
 #                            ||| /     deway
 #           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
 #              | |       |   ||||       |         |
             Xowg-3129  [000] ..s.  2537.644844: intew_pstate_set_pstate <-intew_pstate_timew_func
  gnome-tewminaw--4510  [002] ..s.  2537.649844: intew_pstate_set_pstate <-intew_pstate_timew_func
      gnome-sheww-3409  [001] ..s.  2537.650850: intew_pstate_set_pstate <-intew_pstate_timew_func
           <idwe>-0     [000] ..s.  2537.654843: intew_pstate_set_pstate <-intew_pstate_timew_func


Wefewences
==========

.. [1] Kwisten Accawdi, *Bawancing Powew and Pewfowmance in the Winux Kewnew*,
       https://events.static.winuxfound.owg/sites/events/fiwes/swides/WinuxConEuwope_2015.pdf

.. [2] *Intew® 64 and IA-32 Awchitectuwes Softwawe Devewopew’s Manuaw Vowume 3: System Pwogwamming Guide*,
       https://www.intew.com/content/www/us/en/awchitectuwe-and-technowogy/64-ia-32-awchitectuwes-softwawe-devewopew-system-pwogwamming-manuaw-325384.htmw

.. [3] *Advanced Configuwation and Powew Intewface Specification*,
       https://uefi.owg/sites/defauwt/fiwes/wesouwces/ACPI_6_3_finaw_Jan30.pdf
