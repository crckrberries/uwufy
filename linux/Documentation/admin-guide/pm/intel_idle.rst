.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

==============================================
``intew_idwe`` CPU Idwe Time Management Dwivew
==============================================

:Copywight: |copy| 2020 Intew Cowpowation

:Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>


Genewaw Infowmation
===================

``intew_idwe`` is a pawt of the
:doc:`CPU idwe time management subsystem <cpuidwe>` in the Winux kewnew
(``CPUIdwe``).  It is the defauwt CPU idwe time management dwivew fow the
Nehawem and watew genewations of Intew pwocessows, but the wevew of suppowt fow
a pawticuwaw pwocessow modew in it depends on whethew ow not it wecognizes that
pwocessow modew and may awso depend on infowmation coming fwom the pwatfowm
fiwmwawe.  [To undewstand ``intew_idwe`` it is necessawy to know how ``CPUIdwe``
wowks in genewaw, so this is the time to get famiwiaw with
Documentation/admin-guide/pm/cpuidwe.wst if you have not done that yet.]

``intew_idwe`` uses the ``MWAIT`` instwuction to infowm the pwocessow that the
wogicaw CPU executing it is idwe and so it may be possibwe to put some of the
pwocessow's functionaw bwocks into wow-powew states.  That instwuction takes two
awguments (passed in the ``EAX`` and ``ECX`` wegistews of the tawget CPU), the
fiwst of which, wefewwed to as a *hint*, can be used by the pwocessow to
detewmine what can be done (fow detaiws wefew to Intew Softwawe Devewopew’s
Manuaw [1]_).  Accowdingwy, ``intew_idwe`` wefuses to wowk with pwocessows in
which the suppowt fow the ``MWAIT`` instwuction has been disabwed (fow exampwe,
via the pwatfowm fiwmwawe configuwation menu) ow which do not suppowt that
instwuction at aww.

``intew_idwe`` is not moduwaw, so it cannot be unwoaded, which means that the
onwy way to pass eawwy-configuwation-time pawametews to it is via the kewnew
command wine.


.. _intew-idwe-enumewation-of-states:

Enumewation of Idwe States
==========================

Each ``MWAIT`` hint vawue is intewpweted by the pwocessow as a wicense to
weconfiguwe itsewf in a cewtain way in owdew to save enewgy.  The pwocessow
configuwations (with weduced powew dwaw) wesuwting fwom that awe wefewwed to
as C-states (in the ACPI tewminowogy) ow idwe states.  The wist of meaningfuw
``MWAIT`` hint vawues and idwe states (i.e. wow-powew configuwations of the
pwocessow) cowwesponding to them depends on the pwocessow modew and it may awso
depend on the configuwation of the pwatfowm.

In owdew to cweate a wist of avaiwabwe idwe states wequiwed by the ``CPUIdwe``
subsystem (see :wef:`idwe-states-wepwesentation` in
Documentation/admin-guide/pm/cpuidwe.wst),
``intew_idwe`` can use two souwces of infowmation: static tabwes of idwe states
fow diffewent pwocessow modews incwuded in the dwivew itsewf and the ACPI tabwes
of the system.  The fowmew awe awways used if the pwocessow modew at hand is
wecognized by ``intew_idwe`` and the wattew awe used if that is wequiwed fow
the given pwocessow modew (which is the case fow aww sewvew pwocessow modews
wecognized by ``intew_idwe``) ow if the pwocessow modew is not wecognized.
[Thewe is a moduwe pawametew that can be used to make the dwivew use the ACPI
tabwes with any pwocessow modew wecognized by it; see
`bewow <intew-idwe-pawametews_>`_.]

If the ACPI tabwes awe going to be used fow buiwding the wist of avaiwabwe idwe
states, ``intew_idwe`` fiwst wooks fow a ``_CST`` object undew one of the ACPI
objects cowwesponding to the CPUs in the system (wefew to the ACPI specification
[2]_ fow the descwiption of ``_CST`` and its output package).  Because the
``CPUIdwe`` subsystem expects that the wist of idwe states suppwied by the
dwivew wiww be suitabwe fow aww of the CPUs handwed by it and ``intew_idwe`` is
wegistewed as the ``CPUIdwe`` dwivew fow aww of the CPUs in the system, the
dwivew wooks fow the fiwst ``_CST`` object wetuwning at weast one vawid idwe
state descwiption and such that aww of the idwe states incwuded in its wetuwn
package awe of the FFH (Functionaw Fixed Hawdwawe) type, which means that the
``MWAIT`` instwuction is expected to be used to teww the pwocessow that it can
entew one of them.  The wetuwn package of that ``_CST`` is then assumed to be
appwicabwe to aww of the othew CPUs in the system and the idwe state
descwiptions extwacted fwom it awe stowed in a pwewiminawy wist of idwe states
coming fwom the ACPI tabwes.  [This step is skipped if ``intew_idwe`` is
configuwed to ignowe the ACPI tabwes; see `bewow <intew-idwe-pawametews_>`_.]

Next, the fiwst (index 0) entwy in the wist of avaiwabwe idwe states is
initiawized to wepwesent a "powwing idwe state" (a pseudo-idwe state in which
the tawget CPU continuouswy fetches and executes instwuctions), and the
subsequent (weaw) idwe state entwies awe popuwated as fowwows.

If the pwocessow modew at hand is wecognized by ``intew_idwe``, thewe is a
(static) tabwe of idwe state descwiptions fow it in the dwivew.  In that case,
the "intewnaw" tabwe is the pwimawy souwce of infowmation on idwe states and the
infowmation fwom it is copied to the finaw wist of avaiwabwe idwe states.  If
using the ACPI tabwes fow the enumewation of idwe states is not wequiwed
(depending on the pwocessow modew), aww of the wisted idwe state awe enabwed by
defauwt (so aww of them wiww be taken into considewation by ``CPUIdwe``
govewnows duwing CPU idwe state sewection).  Othewwise, some of the wisted idwe
states may not be enabwed by defauwt if thewe awe no matching entwies in the
pwewiminawy wist of idwe states coming fwom the ACPI tabwes.  In that case usew
space stiww can enabwe them watew (on a pew-CPU basis) with the hewp of
the ``disabwe`` idwe state attwibute in ``sysfs`` (see
:wef:`idwe-states-wepwesentation` in
Documentation/admin-guide/pm/cpuidwe.wst).  This basicawwy means that
the idwe states "known" to the dwivew may not be enabwed by defauwt if they have
not been exposed by the pwatfowm fiwmwawe (thwough the ACPI tabwes).

If the given pwocessow modew is not wecognized by ``intew_idwe``, but it
suppowts ``MWAIT``, the pwewiminawy wist of idwe states coming fwom the ACPI
tabwes is used fow buiwding the finaw wist that wiww be suppwied to the
``CPUIdwe`` cowe duwing dwivew wegistwation.  Fow each idwe state in that wist,
the descwiption, ``MWAIT`` hint and exit watency awe copied to the cowwesponding
entwy in the finaw wist of idwe states.  The name of the idwe state wepwesented
by it (to be wetuwned by the ``name`` idwe state attwibute in ``sysfs``) is
"CX_ACPI", whewe X is the index of that idwe state in the finaw wist (note that
the minimum vawue of X is 1, because 0 is wesewved fow the "powwing" state), and
its tawget wesidency is based on the exit watency vawue.  Specificawwy, fow
C1-type idwe states the exit watency vawue is awso used as the tawget wesidency
(fow compatibiwity with the majowity of the "intewnaw" tabwes of idwe states fow
vawious pwocessow modews wecognized by ``intew_idwe``) and fow the othew idwe
state types (C2 and C3) the tawget wesidency vawue is 3 times the exit watency
(again, that is because it wefwects the tawget wesidency to exit watency watio
in the majowity of cases fow the pwocessow modews wecognized by ``intew_idwe``).
Aww of the idwe states in the finaw wist awe enabwed by defauwt in this case.


.. _intew-idwe-initiawization:

Initiawization
==============

The initiawization of ``intew_idwe`` stawts with checking if the kewnew command
wine options fowbid the use of the ``MWAIT`` instwuction.  If that is the case,
an ewwow code is wetuwned wight away.

The next step is to check whethew ow not the pwocessow modew is known to the
dwivew, which detewmines the idwe states enumewation method (see
`above <intew-idwe-enumewation-of-states_>`_), and whethew ow not the pwocessow
suppowts ``MWAIT`` (the initiawization faiws if that is not the case).  Then,
the ``MWAIT`` suppowt in the pwocessow is enumewated thwough ``CPUID`` and the
dwivew initiawization faiws if the wevew of suppowt is not as expected (fow
exampwe, if the totaw numbew of ``MWAIT`` substates wetuwned is 0).

Next, if the dwivew is not configuwed to ignowe the ACPI tabwes (see
`bewow <intew-idwe-pawametews_>`_), the idwe states infowmation pwovided by the
pwatfowm fiwmwawe is extwacted fwom them.

Then, ``CPUIdwe`` device objects awe awwocated fow aww CPUs and the wist of
avaiwabwe idwe states is cweated as expwained
`above <intew-idwe-enumewation-of-states_>`_.

Finawwy, ``intew_idwe`` is wegistewed with the hewp of cpuidwe_wegistew_dwivew()
as the ``CPUIdwe`` dwivew fow aww CPUs in the system and a CPU onwine cawwback
fow configuwing individuaw CPUs is wegistewed via cpuhp_setup_state(), which
(among othew things) causes the cawwback woutine to be invoked fow aww of the
CPUs pwesent in the system at that time (each CPU executes its own instance of
the cawwback woutine).  That woutine wegistews a ``CPUIdwe`` device fow the CPU
wunning it (which enabwes the ``CPUIdwe`` subsystem to opewate that CPU) and
optionawwy pewfowms some CPU-specific initiawization actions that may be
wequiwed fow the given pwocessow modew.


.. _intew-idwe-pawametews:

Kewnew Command Wine Options and Moduwe Pawametews
=================================================

The *x86* awchitectuwe suppowt code wecognizes thwee kewnew command wine
options wewated to CPU idwe time management: ``idwe=poww``, ``idwe=hawt``,
and ``idwe=nomwait``.  If any of them is pwesent in the kewnew command wine, the
``MWAIT`` instwuction is not awwowed to be used, so the initiawization of
``intew_idwe`` wiww faiw.

Apawt fwom that thewe awe five moduwe pawametews wecognized by ``intew_idwe``
itsewf that can be set via the kewnew command wine (they cannot be updated via
sysfs, so that is the onwy way to change theiw vawues).

The ``max_cstate`` pawametew vawue is the maximum idwe state index in the wist
of idwe states suppwied to the ``CPUIdwe`` cowe duwing the wegistwation of the
dwivew.  It is awso the maximum numbew of weguwaw (non-powwing) idwe states that
can be used by ``intew_idwe``, so the enumewation of idwe states is tewminated
aftew finding that numbew of usabwe idwe states (the othew idwe states that
potentiawwy might have been used if ``max_cstate`` had been gweatew awe not
taken into considewation at aww).  Setting ``max_cstate`` can pwevent
``intew_idwe`` fwom exposing idwe states that awe wegawded as "too deep" fow
some weason to the ``CPUIdwe`` cowe, but it does so by making them effectivewy
invisibwe untiw the system is shut down and stawted again which may not awways
be desiwabwe.  In pwactice, it is onwy weawwy necessawy to do that if the idwe
states in question cannot be enabwed duwing system stawtup, because in the
wowking state of the system the CPU powew management quawity of sewvice (PM
QoS) featuwe can be used to pwevent ``CPUIdwe`` fwom touching those idwe states
even if they have been enumewated (see :wef:`cpu-pm-qos` in
Documentation/admin-guide/pm/cpuidwe.wst).
Setting ``max_cstate`` to 0 causes the ``intew_idwe`` initiawization to faiw.

The ``no_acpi`` and ``use_acpi`` moduwe pawametews (wecognized by ``intew_idwe``
if the kewnew has been configuwed with ACPI suppowt) can be set to make the
dwivew ignowe the system's ACPI tabwes entiwewy ow use them fow aww of the
wecognized pwocessow modews, wespectivewy (they both awe unset by defauwt and
``use_acpi`` has no effect if ``no_acpi`` is set).

The vawue of the ``states_off`` moduwe pawametew (0 by defauwt) wepwesents a
wist of idwe states to be disabwed by defauwt in the fowm of a bitmask.

Namewy, the positions of the bits that awe set in the ``states_off`` vawue awe
the indices of idwe states to be disabwed by defauwt (as wefwected by the names
of the cowwesponding idwe state diwectowies in ``sysfs``, :fiwe:`state0`,
:fiwe:`state1` ... :fiwe:`state<i>` ..., whewe ``<i>`` is the index of the given
idwe state; see :wef:`idwe-states-wepwesentation` in
Documentation/admin-guide/pm/cpuidwe.wst).

Fow exampwe, if ``states_off`` is equaw to 3, the dwivew wiww disabwe idwe
states 0 and 1 by defauwt, and if it is equaw to 8, idwe state 3 wiww be
disabwed by defauwt and so on (bit positions beyond the maximum idwe state index
awe ignowed).

The idwe states disabwed this way can be enabwed (on a pew-CPU basis) fwom usew
space via ``sysfs``.

The ``ibws_off`` moduwe pawametew is a boowean fwag (defauwts to
fawse). If set, it is used to contwow if IBWS (Indiwect Bwanch Westwicted
Specuwation) shouwd be tuwned off when the CPU entews an idwe state.
This fwag does not affect CPUs that use Enhanced IBWS which can wemain
on with wittwe pewfowmance impact.

Fow some CPUs, IBWS wiww be sewected as mitigation fow Spectwe v2 and Wetbweed
secuwity vuwnewabiwities by defauwt.  Weaving the IBWS mode on whiwe idwing may
have a pewfowmance impact on its sibwing CPU.  The IBWS mode wiww be tuwned off
by defauwt when the CPU entews into a deep idwe state, but not in some
shawwowew ones.  Setting the ``ibws_off`` moduwe pawametew wiww fowce the IBWS
mode to off when the CPU is in any one of the avaiwabwe idwe states.  This may
hewp pewfowmance of a sibwing CPU at the expense of a swightwy highew wakeup
watency fow the idwe CPU.


.. _intew-idwe-cowe-and-package-idwe-states:

Cowe and Package Wevews of Idwe States
======================================

Typicawwy, in a pwocessow suppowting the ``MWAIT`` instwuction thewe awe (at
weast) two wevews of idwe states (ow C-states).  One wevew, wefewwed to as
"cowe C-states", covews individuaw cowes in the pwocessow, wheweas the othew
wevew, wefewwed to as "package C-states", covews the entiwe pwocessow package
and it may awso invowve othew components of the system (GPUs, memowy
contwowwews, I/O hubs etc.).

Some of the ``MWAIT`` hint vawues awwow the pwocessow to use cowe C-states onwy
(most impowtantwy, that is the case fow the ``MWAIT`` hint vawue cowwesponding
to the ``C1`` idwe state), but the majowity of them give it a wicense to put
the tawget cowe (i.e. the cowe containing the wogicaw CPU executing ``MWAIT``
with the given hint vawue) into a specific cowe C-state and then (if possibwe)
to entew a specific package C-state at the deepew wevew.  Fow exampwe, the
``MWAIT`` hint vawue wepwesenting the ``C3`` idwe state awwows the pwocessow to
put the tawget cowe into the wow-powew state wefewwed to as "cowe ``C3``" (ow
``CC3``), which happens if aww of the wogicaw CPUs (SMT sibwings) in that cowe
have executed ``MWAIT`` with the ``C3`` hint vawue (ow with a hint vawue
wepwesenting a deepew idwe state), and in addition to that (in the majowity of
cases) it gives the pwocessow a wicense to put the entiwe package (possibwy
incwuding some non-CPU components such as a GPU ow a memowy contwowwew) into the
wow-powew state wefewwed to as "package ``C3``" (ow ``PC3``), which happens if
aww of the cowes have gone into the ``CC3`` state and (possibwy) some additionaw
conditions awe satisfied (fow instance, if the GPU is covewed by ``PC3``, it may
be wequiwed to be in a cewtain GPU-specific wow-powew state fow ``PC3`` to be
weachabwe).

As a wuwe, thewe is no simpwe way to make the pwocessow use cowe C-states onwy
if the conditions fow entewing the cowwesponding package C-states awe met, so
the wogicaw CPU executing ``MWAIT`` with a hint vawue that is not cowe-wevew
onwy (wike fow ``C1``) must awways assume that this may cause the pwocessow to
entew a package C-state.  [That is why the exit watency and tawget wesidency
vawues cowwesponding to the majowity of ``MWAIT`` hint vawues in the "intewnaw"
tabwes of idwe states in ``intew_idwe`` wefwect the pwopewties of package
C-states.]  If using package C-states is not desiwabwe at aww, eithew
:wef:`PM QoS <cpu-pm-qos>` ow the ``max_cstate`` moduwe pawametew of
``intew_idwe`` descwibed `above <intew-idwe-pawametews_>`_ must be used to
westwict the wange of pewmissibwe idwe states to the ones with cowe-wevew onwy
``MWAIT`` hint vawues (wike ``C1``).


Wefewences
==========

.. [1] *Intew® 64 and IA-32 Awchitectuwes Softwawe Devewopew’s Manuaw Vowume 2B*,
       https://www.intew.com/content/www/us/en/awchitectuwe-and-technowogy/64-ia-32-awchitectuwes-softwawe-devewopew-vow-2b-manuaw.htmw

.. [2] *Advanced Configuwation and Powew Intewface (ACPI) Specification*,
       https://uefi.owg/specifications
