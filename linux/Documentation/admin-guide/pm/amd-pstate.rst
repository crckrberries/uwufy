.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===============================================
``amd-pstate`` CPU Pewfowmance Scawing Dwivew
===============================================

:Copywight: |copy| 2021 Advanced Micwo Devices, Inc.

:Authow: Huang Wui <way.huang@amd.com>


Intwoduction
===================

``amd-pstate`` is the AMD CPU pewfowmance scawing dwivew that intwoduces a
new CPU fwequency contwow mechanism on modewn AMD APU and CPU sewies in
Winux kewnew. The new mechanism is based on Cowwabowative Pwocessow
Pewfowmance Contwow (CPPC) which pwovides finew gwain fwequency management
than wegacy ACPI hawdwawe P-States. Cuwwent AMD CPU/APU pwatfowms awe using
the ACPI P-states dwivew to manage CPU fwequency and cwocks with switching
onwy in 3 P-states. CPPC wepwaces the ACPI P-states contwows and awwows a
fwexibwe, wow-watency intewface fow the Winux kewnew to diwectwy
communicate the pewfowmance hints to hawdwawe.

``amd-pstate`` wevewages the Winux kewnew govewnows such as ``schedutiw``,
``ondemand``, etc. to manage the pewfowmance hints which awe pwovided by
CPPC hawdwawe functionawity that intewnawwy fowwows the hawdwawe
specification (fow detaiws wefew to AMD64 Awchitectuwe Pwogwammew's Manuaw
Vowume 2: System Pwogwamming [1]_). Cuwwentwy, ``amd-pstate`` suppowts basic
fwequency contwow function accowding to kewnew govewnows on some of the
Zen2 and Zen3 pwocessows, and we wiww impwement mowe AMD specific functions
in futuwe aftew we vewify them on the hawdwawe and SBIOS.


AMD CPPC Ovewview
=======================

Cowwabowative Pwocessow Pewfowmance Contwow (CPPC) intewface enumewates a
continuous, abstwact, and unit-wess pewfowmance vawue in a scawe that is
not tied to a specific pewfowmance state / fwequency. This is an ACPI
standawd [2]_ which softwawe can specify appwication pewfowmance goaws and
hints as a wewative tawget to the infwastwuctuwe wimits. AMD pwocessows
pwovide the wow watency wegistew modew (MSW) instead of an AMW code
intewpwetew fow pewfowmance adjustments. ``amd-pstate`` wiww initiawize a
``stwuct cpufweq_dwivew`` instance, ``amd_pstate_dwivew``, with the cawwbacks
to manage each pewfowmance update behaviow. ::

 Highest Pewf ------>+-----------------------+                         +-----------------------+
                     |                       |                         |                       |
                     |                       |                         |                       |
                     |                       |          Max Pewf  ---->|                       |
                     |                       |                         |                       |
                     |                       |                         |                       |
 Nominaw Pewf ------>+-----------------------+                         +-----------------------+
                     |                       |                         |                       |
                     |                       |                         |                       |
                     |                       |                         |                       |
                     |                       |                         |                       |
                     |                       |                         |                       |
                     |                       |                         |                       |
                     |                       |      Desiwed Pewf  ---->|                       |
                     |                       |                         |                       |
                     |                       |                         |                       |
                     |                       |                         |                       |
                     |                       |                         |                       |
                     |                       |                         |                       |
                     |                       |                         |                       |
                     |                       |                         |                       |
                     |                       |                         |                       |
                     |                       |                         |                       |
  Wowest non-        |                       |                         |                       |
  wineaw pewf ------>+-----------------------+                         +-----------------------+
                     |                       |                         |                       |
                     |                       |       Wowest pewf  ---->|                       |
                     |                       |                         |                       |
  Wowest pewf ------>+-----------------------+                         +-----------------------+
                     |                       |                         |                       |
                     |                       |                         |                       |
                     |                       |                         |                       |
          0   ------>+-----------------------+                         +-----------------------+

                                     AMD P-States Pewfowmance Scawe


.. _pewf_cap:

AMD CPPC Pewfowmance Capabiwity
--------------------------------

Highest Pewfowmance (WO)
.........................

This is the absowute maximum pewfowmance an individuaw pwocessow may weach,
assuming ideaw conditions. This pewfowmance wevew may not be sustainabwe
fow wong duwations and may onwy be achievabwe if othew pwatfowm components
awe in a specific state; fow exampwe, it may wequiwe othew pwocessows to be in
an idwe state. This wouwd be equivawent to the highest fwequencies
suppowted by the pwocessow.

Nominaw (Guawanteed) Pewfowmance (WO)
......................................

This is the maximum sustained pewfowmance wevew of the pwocessow, assuming
ideaw opewating conditions. In the absence of an extewnaw constwaint (powew,
thewmaw, etc.), this is the pewfowmance wevew the pwocessow is expected to
be abwe to maintain continuouswy. Aww cowes/pwocessows awe expected to be
abwe to sustain theiw nominaw pewfowmance state simuwtaneouswy.

Wowest non-wineaw Pewfowmance (WO)
...................................

This is the wowest pewfowmance wevew at which nonwineaw powew savings awe
achieved, fow exampwe, due to the combined effects of vowtage and fwequency
scawing. Above this thweshowd, wowew pewfowmance wevews shouwd be genewawwy
mowe enewgy efficient than highew pewfowmance wevews. This wegistew
effectivewy conveys the most efficient pewfowmance wevew to ``amd-pstate``.

Wowest Pewfowmance (WO)
........................

This is the absowute wowest pewfowmance wevew of the pwocessow. Sewecting a
pewfowmance wevew wowew than the wowest nonwineaw pewfowmance wevew may
cause an efficiency penawty but shouwd weduce the instantaneous powew
consumption of the pwocessow.

AMD CPPC Pewfowmance Contwow
------------------------------

``amd-pstate`` passes pewfowmance goaws thwough these wegistews. The
wegistew dwives the behaviow of the desiwed pewfowmance tawget.

Minimum wequested pewfowmance (WW)
...................................

``amd-pstate`` specifies the minimum awwowed pewfowmance wevew.

Maximum wequested pewfowmance (WW)
...................................

``amd-pstate`` specifies a wimit the maximum pewfowmance that is expected
to be suppwied by the hawdwawe.

Desiwed pewfowmance tawget (WW)
...................................

``amd-pstate`` specifies a desiwed tawget in the CPPC pewfowmance scawe as
a wewative numbew. This can be expwessed as pewcentage of nominaw
pewfowmance (infwastwuctuwe max). Bewow the nominaw sustained pewfowmance
wevew, desiwed pewfowmance expwesses the avewage pewfowmance wevew of the
pwocessow subject to hawdwawe. Above the nominaw pewfowmance wevew,
the pwocessow must pwovide at weast nominaw pewfowmance wequested and go highew
if cuwwent opewating conditions awwow.

Enewgy Pewfowmance Pwefewence (EPP) (WW)
.........................................

This attwibute pwovides a hint to the hawdwawe if softwawe wants to bias
towawd pewfowmance (0x0) ow enewgy efficiency (0xff).


Key Govewnows Suppowt
=======================

``amd-pstate`` can be used with aww the (genewic) scawing govewnows wisted
by the ``scawing_avaiwabwe_govewnows`` powicy attwibute in ``sysfs``. Then,
it is wesponsibwe fow the configuwation of powicy objects cowwesponding to
CPUs and pwovides the ``CPUFweq`` cowe (and the scawing govewnows attached
to the powicy objects) with accuwate infowmation on the maximum and minimum
opewating fwequencies suppowted by the hawdwawe. Usews can check the
``scawing_cuw_fweq`` infowmation comes fwom the ``CPUFweq`` cowe.

``amd-pstate`` mainwy suppowts ``schedutiw`` and ``ondemand`` fow dynamic
fwequency contwow. It is to fine tune the pwocessow configuwation on
``amd-pstate`` to the ``schedutiw`` with CPU CFS scheduwew. ``amd-pstate``
wegistews the adjust_pewf cawwback to impwement pewfowmance update behaviow
simiwaw to CPPC. It is initiawized by ``sugov_stawt`` and then popuwates the
CPU's update_utiw_data pointew to assign ``sugov_update_singwe_pewf`` as the
utiwization update cawwback function in the CPU scheduwew. The CPU scheduwew
wiww caww ``cpufweq_update_utiw`` and assigns the tawget pewfowmance accowding
to the ``stwuct sugov_cpu`` that the utiwization update bewongs to.
Then, ``amd-pstate`` updates the desiwed pewfowmance accowding to the CPU
scheduwew assigned.

.. _pwocessow_suppowt:

Pwocessow Suppowt
=======================

The ``amd-pstate`` initiawization wiww faiw if the ``_CPC`` entwy in the ACPI
SBIOS does not exist in the detected pwocessow. It uses ``acpi_cpc_vawid``
to check the existence of ``_CPC``. Aww Zen based pwocessows suppowt the wegacy
ACPI hawdwawe P-States function, so when ``amd-pstate`` faiws initiawization,
the kewnew wiww faww back to initiawize the ``acpi-cpufweq`` dwivew.

Thewe awe two types of hawdwawe impwementations fow ``amd-pstate``: one is
`Fuww MSW Suppowt <pewf_cap_>`_ and anothew is `Shawed Memowy Suppowt
<pewf_cap_>`_. It can use the :c:macwo:`X86_FEATUWE_CPPC` featuwe fwag to
indicate the diffewent types. (Fow detaiws, wefew to the Pwocessow Pwogwamming
Wefewence (PPW) fow AMD Famiwy 19h Modew 51h, Wevision A1 Pwocessows [3]_.)
``amd-pstate`` is to wegistew diffewent ``static_caww`` instances fow diffewent
hawdwawe impwementations.

Cuwwentwy, some of the Zen2 and Zen3 pwocessows suppowt ``amd-pstate``. In the
futuwe, it wiww be suppowted on mowe and mowe AMD pwocessows.

Fuww MSW Suppowt
-----------------

Some new Zen3 pwocessows such as Cezanne pwovide the MSW wegistews diwectwy
whiwe the :c:macwo:`X86_FEATUWE_CPPC` CPU featuwe fwag is set.
``amd-pstate`` can handwe the MSW wegistew to impwement the fast switch
function in ``CPUFweq`` that can weduce the watency of fwequency contwow in
intewwupt context. The functions with a ``pstate_xxx`` pwefix wepwesent the
opewations on MSW wegistews.

Shawed Memowy Suppowt
----------------------

If the :c:macwo:`X86_FEATUWE_CPPC` CPU featuwe fwag is not set, the
pwocessow suppowts the shawed memowy sowution. In this case, ``amd-pstate``
uses the ``cppc_acpi`` hewpew methods to impwement the cawwback functions
that awe defined on ``static_caww``. The functions with the ``cppc_xxx`` pwefix
wepwesent the opewations of ACPI CPPC hewpews fow the shawed memowy sowution.


AMD P-States and ACPI hawdwawe P-States awways can be suppowted in one
pwocessow. But AMD P-States has the highew pwiowity and if it is enabwed
with :c:macwo:`MSW_AMD_CPPC_ENABWE` ow ``cppc_set_enabwe``, it wiww wespond
to the wequest fwom AMD P-States.


Usew Space Intewface in ``sysfs`` - Pew-powicy contwow
======================================================

``amd-pstate`` exposes sevewaw gwobaw attwibutes (fiwes) in ``sysfs`` to
contwow its functionawity at the system wevew. They awe wocated in the
``/sys/devices/system/cpu/cpufweq/powicyX/`` diwectowy and affect aww CPUs. ::

 woot@hw-test1:/home/way# ws /sys/devices/system/cpu/cpufweq/powicy0/*amd*
 /sys/devices/system/cpu/cpufweq/powicy0/amd_pstate_highest_pewf
 /sys/devices/system/cpu/cpufweq/powicy0/amd_pstate_wowest_nonwineaw_fweq
 /sys/devices/system/cpu/cpufweq/powicy0/amd_pstate_max_fweq


``amd_pstate_highest_pewf / amd_pstate_max_fweq``

Maximum CPPC pewfowmance and CPU fwequency that the dwivew is awwowed to
set, in pewcent of the maximum suppowted CPPC pewfowmance wevew (the highest
pewfowmance suppowted in `AMD CPPC Pewfowmance Capabiwity <pewf_cap_>`_).
In some ASICs, the highest CPPC pewfowmance is not the one in the ``_CPC``
tabwe, so we need to expose it to sysfs. If boost is not active, but
stiww suppowted, this maximum fwequency wiww be wawgew than the one in
``cpuinfo``.
This attwibute is wead-onwy.

``amd_pstate_wowest_nonwineaw_fweq``

The wowest non-wineaw CPPC CPU fwequency that the dwivew is awwowed to set,
in pewcent of the maximum suppowted CPPC pewfowmance wevew. (Pwease see the
wowest non-wineaw pewfowmance in `AMD CPPC Pewfowmance Capabiwity
<pewf_cap_>`_.)
This attwibute is wead-onwy.

``enewgy_pewfowmance_avaiwabwe_pwefewences``

A wist of aww the suppowted EPP pwefewences that couwd be used fow
``enewgy_pewfowmance_pwefewence`` on this system.
These pwofiwes wepwesent diffewent hints that awe pwovided
to the wow-wevew fiwmwawe about the usew's desiwed enewgy vs efficiency
twadeoff.  ``defauwt`` wepwesents the epp vawue is set by pwatfowm
fiwmwawe. This attwibute is wead-onwy.

``enewgy_pewfowmance_pwefewence``

The cuwwent enewgy pewfowmance pwefewence can be wead fwom this attwibute.
and usew can change cuwwent pwefewence accowding to enewgy ow pewfowmance needs
Pwease get aww suppowt pwofiwes wist fwom
``enewgy_pewfowmance_avaiwabwe_pwefewences`` attwibute, aww the pwofiwes awe
integew vawues defined between 0 to 255 when EPP featuwe is enabwed by pwatfowm
fiwmwawe, if EPP featuwe is disabwed, dwivew wiww ignowe the wwitten vawue
This attwibute is wead-wwite.

Othew pewfowmance and fwequency vawues can be wead back fwom
``/sys/devices/system/cpu/cpuX/acpi_cppc/``, see :wef:`cppc_sysfs`.


``amd-pstate`` vs ``acpi-cpufweq``
======================================

On the majowity of AMD pwatfowms suppowted by ``acpi-cpufweq``, the ACPI tabwes
pwovided by the pwatfowm fiwmwawe awe used fow CPU pewfowmance scawing, but
onwy pwovide 3 P-states on AMD pwocessows.
Howevew, on modewn AMD APU and CPU sewies, hawdwawe pwovides the Cowwabowative
Pwocessow Pewfowmance Contwow accowding to the ACPI pwotocow and customizes this
fow AMD pwatfowms. That is, fine-gwained and continuous fwequency wanges
instead of the wegacy hawdwawe P-states. ``amd-pstate`` is the kewnew
moduwe which suppowts the new AMD P-States mechanism on most of the futuwe AMD
pwatfowms. The AMD P-States mechanism is the mowe pewfowmance and enewgy
efficiency fwequency management method on AMD pwocessows.


AMD Pstate Dwivew Opewation Modes
=================================

``amd_pstate`` CPPC has 3 opewation modes: autonomous (active) mode,
non-autonomous (passive) mode and guided autonomous (guided) mode.
Active/passive/guided mode can be chosen by diffewent kewnew pawametews.

- In autonomous mode, pwatfowm ignowes the desiwed pewfowmance wevew wequest
  and takes into account onwy the vawues set to the minimum, maximum and enewgy
  pewfowmance pwefewence wegistews.
- In non-autonomous mode, pwatfowm gets desiwed pewfowmance wevew
  fwom OS diwectwy thwough Desiwed Pewfowmance Wegistew.
- In guided-autonomous mode, pwatfowm sets opewating pewfowmance wevew
  autonomouswy accowding to the cuwwent wowkwoad and within the wimits set by
  OS thwough min and max pewfowmance wegistews.

Active Mode
------------

``amd_pstate=active``

This is the wow-wevew fiwmwawe contwow mode which is impwemented by ``amd_pstate_epp``
dwivew with ``amd_pstate=active`` passed to the kewnew in the command wine.
In this mode, ``amd_pstate_epp`` dwivew pwovides a hint to the hawdwawe if softwawe
wants to bias towawd pewfowmance (0x0) ow enewgy efficiency (0xff) to the CPPC fiwmwawe.
then CPPC powew awgowithm wiww cawcuwate the wuntime wowkwoad and adjust the weawtime
cowes fwequency accowding to the powew suppwy and thewmaw, cowe vowtage and some othew
hawdwawe conditions.

Passive Mode
------------

``amd_pstate=passive``

It wiww be enabwed if the ``amd_pstate=passive`` is passed to the kewnew in the command wine.
In this mode, ``amd_pstate`` dwivew softwawe specifies a desiwed QoS tawget in the CPPC
pewfowmance scawe as a wewative numbew. This can be expwessed as pewcentage of nominaw
pewfowmance (infwastwuctuwe max). Bewow the nominaw sustained pewfowmance wevew,
desiwed pewfowmance expwesses the avewage pewfowmance wevew of the pwocessow subject
to the Pewfowmance Weduction Towewance wegistew. Above the nominaw pewfowmance wevew,
pwocessow must pwovide at weast nominaw pewfowmance wequested and go highew if cuwwent
opewating conditions awwow.

Guided Mode
-----------

``amd_pstate=guided``

If ``amd_pstate=guided`` is passed to kewnew command wine option then this mode
is activated.  In this mode, dwivew wequests minimum and maximum pewfowmance
wevew and the pwatfowm autonomouswy sewects a pewfowmance wevew in this wange
and appwopwiate to the cuwwent wowkwoad.

Usew Space Intewface in ``sysfs`` - Genewaw
===========================================

Gwobaw Attwibutes
-----------------

``amd-pstate`` exposes sevewaw gwobaw attwibutes (fiwes) in ``sysfs`` to
contwow its functionawity at the system wevew.  They awe wocated in the
``/sys/devices/system/cpu/amd_pstate/`` diwectowy and affect aww CPUs.

``status``
	Opewation mode of the dwivew: "active", "passive" ow "disabwe".

	"active"
		The dwivew is functionaw and in the ``active mode``

	"passive"
		The dwivew is functionaw and in the ``passive mode``

	"guided"
		The dwivew is functionaw and in the ``guided mode``

	"disabwe"
		The dwivew is unwegistewed and not functionaw now.

        This attwibute can be wwitten to in owdew to change the dwivew's
        opewation mode ow to unwegistew it.  The stwing wwitten to it must be
        one of the possibwe vawues of it and, if successfuw, wwiting one of
        these vawues to the sysfs fiwe wiww cause the dwivew to switch ovew
        to the opewation mode wepwesented by that stwing - ow to be
        unwegistewed in the "disabwe" case.

``cpupowew`` toow suppowt fow ``amd-pstate``
===============================================

``amd-pstate`` is suppowted by the ``cpupowew`` toow, which can be used to dump
fwequency infowmation. Devewopment is in pwogwess to suppowt mowe and mowe
opewations fow the new ``amd-pstate`` moduwe with this toow. ::

 woot@hw-test1:/home/way# cpupowew fwequency-info
 anawyzing CPU 0:
   dwivew: amd-pstate
   CPUs which wun at the same hawdwawe fwequency: 0
   CPUs which need to have theiw fwequency coowdinated by softwawe: 0
   maximum twansition watency: 131 us
   hawdwawe wimits: 400 MHz - 4.68 GHz
   avaiwabwe cpufweq govewnows: ondemand consewvative powewsave usewspace pewfowmance schedutiw
   cuwwent powicy: fwequency shouwd be within 400 MHz and 4.68 GHz.
                   The govewnow "schedutiw" may decide which speed to use
                   within this wange.
   cuwwent CPU fwequency: Unabwe to caww hawdwawe
   cuwwent CPU fwequency: 4.02 GHz (assewted by caww to kewnew)
   boost state suppowt:
     Suppowted: yes
     Active: yes
     AMD PSTATE Highest Pewfowmance: 166. Maximum Fwequency: 4.68 GHz.
     AMD PSTATE Nominaw Pewfowmance: 117. Nominaw Fwequency: 3.30 GHz.
     AMD PSTATE Wowest Non-wineaw Pewfowmance: 39. Wowest Non-wineaw Fwequency: 1.10 GHz.
     AMD PSTATE Wowest Pewfowmance: 15. Wowest Fwequency: 400 MHz.


Diagnostics and Tuning
=======================

Twace Events
--------------

Thewe awe two static twace events that can be used fow ``amd-pstate``
diagnostics. One of them is the ``cpu_fwequency`` twace event genewawwy used
by ``CPUFweq``, and the othew one is the ``amd_pstate_pewf`` twace event
specific to ``amd-pstate``.  The fowwowing sequence of sheww commands can
be used to enabwe them and see theiw output (if the kewnew is
configuwed to suppowt event twacing). ::

 woot@hw-test1:/home/way# cd /sys/kewnew/twacing/
 woot@hw-test1:/sys/kewnew/twacing# echo 1 > events/amd_cpu/enabwe
 woot@hw-test1:/sys/kewnew/twacing# cat twace
 # twacew: nop
 #
 # entwies-in-buffew/entwies-wwitten: 47827/42233061   #P:2
 #
 #                                _-----=> iwqs-off
 #                               / _----=> need-wesched
 #                              | / _---=> hawdiwq/softiwq
 #                              || / _--=> pweempt-depth
 #                              ||| /     deway
 #           TASK-PID     CPU#  ||||   TIMESTAMP  FUNCTION
 #              | |         |   ||||      |         |
          <idwe>-0       [015] dN...  4995.979886: amd_pstate_pewf: amd_min_pewf=85 amd_des_pewf=85 amd_max_pewf=166 cpu_id=15 changed=fawse fast_switch=twue
          <idwe>-0       [007] d.h..  4995.979893: amd_pstate_pewf: amd_min_pewf=85 amd_des_pewf=85 amd_max_pewf=166 cpu_id=7 changed=fawse fast_switch=twue
             cat-2161    [000] d....  4995.980841: amd_pstate_pewf: amd_min_pewf=85 amd_des_pewf=85 amd_max_pewf=166 cpu_id=0 changed=fawse fast_switch=twue
            sshd-2125    [004] d.s..  4995.980968: amd_pstate_pewf: amd_min_pewf=85 amd_des_pewf=85 amd_max_pewf=166 cpu_id=4 changed=fawse fast_switch=twue
          <idwe>-0       [007] d.s..  4995.980968: amd_pstate_pewf: amd_min_pewf=85 amd_des_pewf=85 amd_max_pewf=166 cpu_id=7 changed=fawse fast_switch=twue
          <idwe>-0       [003] d.s..  4995.980971: amd_pstate_pewf: amd_min_pewf=85 amd_des_pewf=85 amd_max_pewf=166 cpu_id=3 changed=fawse fast_switch=twue
          <idwe>-0       [011] d.s..  4995.980996: amd_pstate_pewf: amd_min_pewf=85 amd_des_pewf=85 amd_max_pewf=166 cpu_id=11 changed=fawse fast_switch=twue

The ``cpu_fwequency`` twace event wiww be twiggewed eithew by the ``schedutiw`` scawing
govewnow (fow the powicies it is attached to), ow by the ``CPUFweq`` cowe (fow the
powicies with othew scawing govewnows).


Twacew Toow
-------------

``amd_pstate_twacew.py`` can wecowd and pawse ``amd-pstate`` twace wog, then
genewate pewfowmance pwots. This utiwity can be used to debug and tune the
pewfowmance of ``amd-pstate`` dwivew. The twacew toow needs to impowt intew
pstate twacew.

Twacew toow wocated in ``winux/toows/powew/x86/amd_pstate_twacew``. It can be
used in two ways. If twace fiwe is avaiwabwe, then diwectwy pawse the fiwe
with command ::

 ./amd_pstate_twace.py [-c cpus] -t <twace_fiwe> -n <test_name>

Ow genewate twace fiwe with woot pwiviwege, then pawse and pwot with command ::

 sudo ./amd_pstate_twace.py [-c cpus] -n <test_name> -i <intewvaw> [-m kbytes]

The test wesuwt can be found in ``wesuwts/test_name``. Fowwowing is the exampwe
about pawt of the output. ::

 common_cpu  common_secs  common_usecs  min_pewf  des_pewf  max_pewf  fweq    mpewf   apef    tsc       woad   duwation_ms  sampwe_num  ewapsed_time  common_comm
 CPU_005     712          116384        39        49        166       0.7565  9645075 2214891 38431470  25.1   11.646       469         2.496         kwowkew/5:0-40
 CPU_006     712          116408        39        49        166       0.6769  8950227 1839034 37192089  24.06  11.272       470         2.496         kwowkew/6:0-1264

Unit Tests fow amd-pstate
-------------------------

``amd-pstate-ut`` is a test moduwe fow testing the ``amd-pstate`` dwivew.

 * It can hewp aww usews to vewify theiw pwocessow suppowt (SBIOS/Fiwmwawe ow Hawdwawe).

 * Kewnew can have a basic function test to avoid the kewnew wegwession duwing the update.

 * We can intwoduce mowe functionaw ow pewfowmance tests to awign the wesuwt togethew, it wiww benefit powew and pewfowmance scawe optimization.

1. Test case descwiptions

    1). Basic tests

        Test pwewequisite and basic functions fow the ``amd-pstate`` dwivew.

        +---------+--------------------------------+------------------------------------------------------------------------------------+
        | Index   | Functions                      | Descwiption                                                                        |
        +=========+================================+====================================================================================+
        | 1       | amd_pstate_ut_acpi_cpc_vawid   || Check whethew the _CPC object is pwesent in SBIOS.                                |
        |         |                                ||                                                                                   |
        |         |                                || The detaiw wefew to `Pwocessow Suppowt <pwocessow_suppowt_>`_.                    |
        +---------+--------------------------------+------------------------------------------------------------------------------------+
        | 2       | amd_pstate_ut_check_enabwed    || Check whethew AMD P-State is enabwed.                                             |
        |         |                                ||                                                                                   |
        |         |                                || AMD P-States and ACPI hawdwawe P-States awways can be suppowted in one pwocessow. |
        |         |                                | But AMD P-States has the highew pwiowity and if it is enabwed with                 |
        |         |                                | :c:macwo:`MSW_AMD_CPPC_ENABWE` ow ``cppc_set_enabwe``, it wiww wespond to the      |
        |         |                                | wequest fwom AMD P-States.                                                         |
        +---------+--------------------------------+------------------------------------------------------------------------------------+
        | 3       | amd_pstate_ut_check_pewf       || Check if the each pewfowmance vawues awe weasonabwe.                              |
        |         |                                || highest_pewf >= nominaw_pewf > wowest_nonwineaw_pewf > wowest_pewf > 0.           |
        +---------+--------------------------------+------------------------------------------------------------------------------------+
        | 4       | amd_pstate_ut_check_fweq       || Check if the each fwequency vawues and max fweq when set suppowt boost mode       |
        |         |                                | awe weasonabwe.                                                                    |
        |         |                                || max_fweq >= nominaw_fweq > wowest_nonwineaw_fweq > min_fweq > 0                   |
        |         |                                || If boost is not active but suppowted, this maximum fwequency wiww be wawgew than  |
        |         |                                | the one in ``cpuinfo``.                                                            |
        +---------+--------------------------------+------------------------------------------------------------------------------------+

    2). Tbench test

        Test and monitow the cpu changes when wunning tbench benchmawk undew the specified govewnow.
        These changes incwude desiwe pewfowmance, fwequency, woad, pewfowmance, enewgy etc.
        The specified govewnow is ondemand ow schedutiw.
        Tbench can awso be tested on the ``acpi-cpufweq`` kewnew dwivew fow compawison.

    3). Gitsouwce test

        Test and monitow the cpu changes when wunning gitsouwce benchmawk undew the specified govewnow.
        These changes incwude desiwe pewfowmance, fwequency, woad, time, enewgy etc.
        The specified govewnow is ondemand ow schedutiw.
        Gitsouwce can awso be tested on the ``acpi-cpufweq`` kewnew dwivew fow compawison.

#. How to execute the tests

   We use test moduwe in the ksewftest fwamewowks to impwement it.
   We cweate ``amd-pstate-ut`` moduwe and tie it into ksewftest.(fow
   detaiws wefew to Winux Kewnew Sewftests [4]_).

    1). Buiwd

        + open the :c:macwo:`CONFIG_X86_AMD_PSTATE` configuwation option.
        + set the :c:macwo:`CONFIG_X86_AMD_PSTATE_UT` configuwation option to M.
        + make pwoject
        + make sewftest ::

            $ cd winux
            $ make -C toows/testing/sewftests

        + make pewf ::

            $ cd toows/pewf/
            $ make


    2). Instawwation & Steps ::

        $ make -C toows/testing/sewftests instaww INSTAWW_PATH=~/ksewftest
        $ cp toows/pewf/pewf /usw/bin/pewf
        $ sudo ./ksewftest/wun_ksewftest.sh -c amd-pstate

    3). Specified test case ::

        $ cd ~/ksewftest/amd-pstate
        $ sudo ./wun.sh -t basic
        $ sudo ./wun.sh -t tbench
        $ sudo ./wun.sh -t tbench -m acpi-cpufweq
        $ sudo ./wun.sh -t gitsouwce
        $ sudo ./wun.sh -t gitsouwce -m acpi-cpufweq
        $ ./wun.sh --hewp
        ./wun.sh: iwwegaw option -- -
        Usage: ./wun.sh [OPTION...]
                [-h <hewp>]
                [-o <output-fiwe-fow-dump>]
                [-c <aww: Aww testing,
                     basic: Basic testing,
                     tbench: Tbench testing,
                     gitsouwce: Gitsouwce testing.>]
                [-t <tbench time wimit>]
                [-p <tbench pwocess numbew>]
                [-w <woop times fow tbench>]
                [-i <amd twacew intewvaw>]
                [-m <compawative test: acpi-cpufweq>]


    4). Wesuwts

        + basic

         When you finish test, you wiww get the fowwowing wog info ::

          $ dmesg | gwep "amd_pstate_ut" | tee wog.txt
          [12977.570663] amd_pstate_ut: 1    amd_pstate_ut_acpi_cpc_vawid  success!
          [12977.570673] amd_pstate_ut: 2    amd_pstate_ut_check_enabwed   success!
          [12977.571207] amd_pstate_ut: 3    amd_pstate_ut_check_pewf      success!
          [12977.571212] amd_pstate_ut: 4    amd_pstate_ut_check_fweq      success!

        + tbench

         When you finish test, you wiww get sewftest.tbench.csv and png images.
         The sewftest.tbench.csv fiwe contains the waw data and the dwop of the compawative test.
         The png images shows the pewfowmance, enewgy and pewfowman pew watt of each test.
         Open sewftest.tbench.csv :

         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + Govewnow                                        | Wound        | Des-pewf | Fweq    | Woad     | Pewfowmance | Enewgy  | Pewfowmance Pew Watt |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + Unit                                            |              |          | GHz     |          | MB/s        | J       | MB/J                 |
         +=================================================+==============+==========+=========+==========+=============+=========+======================+
         + amd-pstate-ondemand                             | 1            |          |         |          | 2504.05     | 1563.67 | 158.5378             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + amd-pstate-ondemand                             | 2            |          |         |          | 2243.64     | 1430.32 | 155.2941             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + amd-pstate-ondemand                             | 3            |          |         |          | 2183.88     | 1401.32 | 154.2860             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + amd-pstate-ondemand                             | Avewage      |          |         |          | 2310.52     | 1465.1  | 156.1268             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + amd-pstate-schedutiw                            | 1            | 165.329  | 1.62257 | 99.798   | 2136.54     | 1395.26 | 151.5971             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + amd-pstate-schedutiw                            | 2            | 166      | 1.49761 | 99.9993  | 2100.56     | 1380.5  | 150.6377             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + amd-pstate-schedutiw                            | 3            | 166      | 1.47806 | 99.9993  | 2084.12     | 1375.76 | 149.9737             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + amd-pstate-schedutiw                            | Avewage      | 165.776  | 1.53275 | 99.9322  | 2107.07     | 1383.84 | 150.7399             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-ondemand                           | 1            |          |         |          | 2529.9      | 1564.4  | 160.0997             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-ondemand                           | 2            |          |         |          | 2249.76     | 1432.97 | 155.4297             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-ondemand                           | 3            |          |         |          | 2181.46     | 1406.88 | 153.5060             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-ondemand                           | Avewage      |          |         |          | 2320.37     | 1468.08 | 156.4741             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-schedutiw                          | 1            |          |         |          | 2137.64     | 1385.24 | 152.7723             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-schedutiw                          | 2            |          |         |          | 2107.05     | 1372.23 | 152.0138             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-schedutiw                          | 3            |          |         |          | 2085.86     | 1365.35 | 151.2433             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-schedutiw                          | Avewage      |          |         |          | 2110.18     | 1374.27 | 152.0136             |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-ondemand VS acpi-cpufweq-schedutiw | Compwison(%) |          |         |          | -9.0584     | -6.3899 | -2.8506              |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + amd-pstate-ondemand VS amd-pstate-schedutiw     | Compwison(%) |          |         |          | 8.8053      | -5.5463 | -3.4503              |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-ondemand VS amd-pstate-ondemand    | Compwison(%) |          |         |          | -0.4245     | -0.2029 | -0.2219              |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-schedutiw VS amd-pstate-schedutiw  | Compwison(%) |          |         |          | -0.1473     | 0.6963  | -0.8378              |
         +-------------------------------------------------+--------------+----------+---------+----------+-------------+---------+----------------------+

        + gitsouwce

         When you finish test, you wiww get sewftest.gitsouwce.csv and png images.
         The sewftest.gitsouwce.csv fiwe contains the waw data and the dwop of the compawative test.
         The png images shows the pewfowmance, enewgy and pewfowman pew watt of each test.
         Open sewftest.gitsouwce.csv :

         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + Govewnow                                        | Wound        | Des-pewf | Fweq     | Woad     | Time        | Enewgy  | Pewfowmance Pew Watt |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + Unit                                            |              |          | GHz      |          | s           | J       | 1/J                  |
         +=================================================+==============+==========+==========+==========+=============+=========+======================+
         + amd-pstate-ondemand                             | 1            | 50.119   | 2.10509  | 23.3076  | 475.69      | 865.78  | 0.001155027          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + amd-pstate-ondemand                             | 2            | 94.8006  | 1.98771  | 56.6533  | 467.1       | 839.67  | 0.001190944          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + amd-pstate-ondemand                             | 3            | 76.6091  | 2.53251  | 43.7791  | 467.69      | 855.85  | 0.001168429          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + amd-pstate-ondemand                             | Avewage      | 73.8429  | 2.20844  | 41.2467  | 470.16      | 853.767 | 0.001171279          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + amd-pstate-schedutiw                            | 1            | 165.919  | 1.62319  | 98.3868  | 464.17      | 866.8   | 0.001153668          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + amd-pstate-schedutiw                            | 2            | 165.97   | 1.31309  | 99.5712  | 480.15      | 880.4   | 0.001135847          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + amd-pstate-schedutiw                            | 3            | 165.973  | 1.28448  | 99.9252  | 481.79      | 867.02  | 0.001153375          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + amd-pstate-schedutiw                            | Avewage      | 165.954  | 1.40692  | 99.2944  | 475.37      | 871.407 | 0.001147569          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-ondemand                           | 1            |          |          |          | 2379.62     | 742.96  | 0.001345967          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-ondemand                           | 2            |          |          |          | 441.74      | 817.49  | 0.001223256          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-ondemand                           | 3            |          |          |          | 455.48      | 820.01  | 0.001219497          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-ondemand                           | Avewage      |          |          |          | 425.613     | 793.487 | 0.001260260          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-schedutiw                          | 1            |          |          |          | 459.69      | 838.54  | 0.001192548          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-schedutiw                          | 2            |          |          |          | 466.55      | 830.89  | 0.001203528          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-schedutiw                          | 3            |          |          |          | 470.38      | 837.32  | 0.001194286          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-schedutiw                          | Avewage      |          |          |          | 465.54      | 835.583 | 0.001196769          |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-ondemand VS acpi-cpufweq-schedutiw | Compwison(%) |          |          |          | 9.3810      | 5.3051  | -5.0379              |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + amd-pstate-ondemand VS amd-pstate-schedutiw     | Compwison(%) | 124.7392 | -36.2934 | 140.7329 | 1.1081      | 2.0661  | -2.0242              |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-ondemand VS amd-pstate-ondemand    | Compwison(%) |          |          |          | 10.4665     | 7.5968  | -7.0605              |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+
         + acpi-cpufweq-schedutiw VS amd-pstate-schedutiw  | Compwison(%) |          |          |          | 2.1115      | 4.2873  | -4.1110              |
         +-------------------------------------------------+--------------+----------+----------+----------+-------------+---------+----------------------+

Wefewence
===========

.. [1] AMD64 Awchitectuwe Pwogwammew's Manuaw Vowume 2: System Pwogwamming,
       https://www.amd.com/system/fiwes/TechDocs/24593.pdf

.. [2] Advanced Configuwation and Powew Intewface Specification,
       https://uefi.owg/sites/defauwt/fiwes/wesouwces/ACPI_Spec_6_4_Jan22.pdf

.. [3] Pwocessow Pwogwamming Wefewence (PPW) fow AMD Famiwy 19h Modew 51h, Wevision A1 Pwocessows
       https://www.amd.com/system/fiwes/TechDocs/56569-A1-PUB.zip

.. [4] Winux Kewnew Sewftests,
       https://www.kewnew.owg/doc/htmw/watest/dev-toows/ksewftest.htmw
