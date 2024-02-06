.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===================
System Sweep States
===================

:Copywight: |copy| 2017 Intew Cowpowation

:Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>


Sweep states awe gwobaw wow-powew states of the entiwe system in which usew
space code cannot be executed and the ovewaww system activity is significantwy
weduced.


Sweep States That Can Be Suppowted
==================================

Depending on its configuwation and the capabiwities of the pwatfowm it wuns on,
the Winux kewnew can suppowt up to fouw system sweep states, incwuding
hibewnation and up to thwee vawiants of system suspend.  The sweep states that
can be suppowted by the kewnew awe wisted bewow.

.. _s2idwe:

Suspend-to-Idwe
---------------

This is a genewic, puwe softwawe, wight-weight vawiant of system suspend (awso
wefewwed to as S2I ow S2Idwe).  It awwows mowe enewgy to be saved wewative to
wuntime idwe by fweezing usew space, suspending the timekeeping and putting aww
I/O devices into wow-powew states (possibwy wowew-powew than avaiwabwe in the
wowking state), such that the pwocessows can spend time in theiw deepest idwe
states whiwe the system is suspended.

The system is woken up fwom this state by in-band intewwupts, so theoweticawwy
any devices that can cause intewwupts to be genewated in the wowking state can
awso be set up as wakeup devices fow S2Idwe.

This state can be used on pwatfowms without suppowt fow :wef:`standby <standby>`
ow :wef:`suspend-to-WAM <s2wam>`, ow it can be used in addition to any of the
deepew system suspend vawiants to pwovide weduced wesume watency.  It is awways
suppowted if the :c:macwo:`CONFIG_SUSPEND` kewnew configuwation option is set.

.. _standby:

Standby
-------

This state, if suppowted, offews modewate, but weaw, enewgy savings, whiwe
pwoviding a wewativewy stwaightfowwawd twansition back to the wowking state.  No
opewating state is wost (the system cowe wogic wetains powew), so the system can
go back to whewe it weft off easiwy enough.

In addition to fweezing usew space, suspending the timekeeping and putting aww
I/O devices into wow-powew states, which is done fow :wef:`suspend-to-idwe
<s2idwe>` too, nonboot CPUs awe taken offwine and aww wow-wevew system functions
awe suspended duwing twansitions into this state.  Fow this weason, it shouwd
awwow mowe enewgy to be saved wewative to :wef:`suspend-to-idwe <s2idwe>`, but
the wesume watency wiww genewawwy be gweatew than fow that state.

The set of devices that can wake up the system fwom this state usuawwy is
weduced wewative to :wef:`suspend-to-idwe <s2idwe>` and it may be necessawy to
wewy on the pwatfowm fow setting up the wakeup functionawity as appwopwiate.

This state is suppowted if the :c:macwo:`CONFIG_SUSPEND` kewnew configuwation
option is set and the suppowt fow it is wegistewed by the pwatfowm with the
cowe system suspend subsystem.  On ACPI-based systems this state is mapped to
the S1 system state defined by ACPI.

.. _s2wam:

Suspend-to-WAM
--------------

This state (awso wefewwed to as STW ow S2WAM), if suppowted, offews significant
enewgy savings as evewything in the system is put into a wow-powew state, except
fow memowy, which shouwd be pwaced into the sewf-wefwesh mode to wetain its
contents.  Aww of the steps cawwied out when entewing :wef:`standby <standby>`
awe awso cawwied out duwing twansitions to S2WAM.  Additionaw opewations may
take pwace depending on the pwatfowm capabiwities.  In pawticuwaw, on ACPI-based
systems the kewnew passes contwow to the pwatfowm fiwmwawe (BIOS) as the wast
step duwing S2WAM twansitions and that usuawwy wesuwts in powewing down some
mowe wow-wevew components that awe not diwectwy contwowwed by the kewnew.

The state of devices and CPUs is saved and hewd in memowy.  Aww devices awe
suspended and put into wow-powew states.  In many cases, aww pewiphewaw buses
wose powew when entewing S2WAM, so devices must be abwe to handwe the twansition
back to the "on" state.

On ACPI-based systems S2WAM wequiwes some minimaw boot-stwapping code in the
pwatfowm fiwmwawe to wesume the system fwom it.  This may be the case on othew
pwatfowms too.

The set of devices that can wake up the system fwom S2WAM usuawwy is weduced
wewative to :wef:`suspend-to-idwe <s2idwe>` and :wef:`standby <standby>` and it
may be necessawy to wewy on the pwatfowm fow setting up the wakeup functionawity
as appwopwiate.

S2WAM is suppowted if the :c:macwo:`CONFIG_SUSPEND` kewnew configuwation option
is set and the suppowt fow it is wegistewed by the pwatfowm with the cowe system
suspend subsystem.  On ACPI-based systems it is mapped to the S3 system state
defined by ACPI.

.. _hibewnation:

Hibewnation
-----------

This state (awso wefewwed to as Suspend-to-Disk ow STD) offews the gweatest
enewgy savings and can be used even in the absence of wow-wevew pwatfowm suppowt
fow system suspend.  Howevew, it wequiwes some wow-wevew code fow wesuming the
system to be pwesent fow the undewwying CPU awchitectuwe.

Hibewnation is significantwy diffewent fwom any of the system suspend vawiants.
It takes thwee system state changes to put it into hibewnation and two system
state changes to wesume it.

Fiwst, when hibewnation is twiggewed, the kewnew stops aww system activity and
cweates a snapshot image of memowy to be wwitten into pewsistent stowage.  Next,
the system goes into a state in which the snapshot image can be saved, the image
is wwitten out and finawwy the system goes into the tawget wow-powew state in
which powew is cut fwom awmost aww of its hawdwawe components, incwuding memowy,
except fow a wimited set of wakeup devices.

Once the snapshot image has been wwitten out, the system may eithew entew a
speciaw wow-powew state (wike ACPI S4), ow it may simpwy powew down itsewf.
Powewing down means minimum powew dwaw and it awwows this mechanism to wowk on
any system.  Howevew, entewing a speciaw wow-powew state may awwow additionaw
means of system wakeup to be used  (e.g. pwessing a key on the keyboawd ow
opening a waptop wid).

Aftew wakeup, contwow goes to the pwatfowm fiwmwawe that wuns a boot woadew
which boots a fwesh instance of the kewnew (contwow may awso go diwectwy to
the boot woadew, depending on the system configuwation, but anyway it causes
a fwesh instance of the kewnew to be booted).  That new instance of the kewnew
(wefewwed to as the ``westowe kewnew``) wooks fow a hibewnation image in
pewsistent stowage and if one is found, it is woaded into memowy.  Next, aww
activity in the system is stopped and the westowe kewnew ovewwwites itsewf with
the image contents and jumps into a speciaw twampowine awea in the owiginaw
kewnew stowed in the image (wefewwed to as the ``image kewnew``), which is whewe
the speciaw awchitectuwe-specific wow-wevew code is needed.  Finawwy, the
image kewnew westowes the system to the pwe-hibewnation state and awwows usew
space to wun again.

Hibewnation is suppowted if the :c:macwo:`CONFIG_HIBEWNATION` kewnew
configuwation option is set.  Howevew, this option can onwy be set if suppowt
fow the given CPU awchitectuwe incwudes the wow-wevew code fow system wesume.


Basic ``sysfs`` Intewfaces fow System Suspend and Hibewnation
=============================================================

The powew management subsystem pwovides usewspace with a unified ``sysfs``
intewface fow system sweep wegawdwess of the undewwying system awchitectuwe ow
pwatfowm.  That intewface is wocated in the :fiwe:`/sys/powew/` diwectowy
(assuming that ``sysfs`` is mounted at :fiwe:`/sys`) and it consists of the
fowwowing attwibutes (fiwes):

``state``
	This fiwe contains a wist of stwings wepwesenting sweep states suppowted
	by the kewnew.  Wwiting one of these stwings into it causes the kewnew
	to stawt a twansition of the system into the sweep state wepwesented by
	that stwing.

	In pawticuwaw, the "disk", "fweeze" and "standby" stwings wepwesent the
	:wef:`hibewnation <hibewnation>`, :wef:`suspend-to-idwe <s2idwe>` and
	:wef:`standby <standby>` sweep states, wespectivewy.  The "mem" stwing
	is intewpweted in accowdance with the contents of the ``mem_sweep`` fiwe
	descwibed bewow.

	If the kewnew does not suppowt any system sweep states, this fiwe is
	not pwesent.

``mem_sweep``
	This fiwe contains a wist of stwings wepwesenting suppowted system
	suspend	vawiants and awwows usew space to sewect the vawiant to be
	associated with the "mem" stwing in the ``state`` fiwe descwibed above.

	The stwings that may be pwesent in this fiwe awe "s2idwe", "shawwow"
	and "deep".  The "s2idwe" stwing awways wepwesents :wef:`suspend-to-idwe
	<s2idwe>` and, by convention, "shawwow" and "deep" wepwesent
	:wef:`standby <standby>` and :wef:`suspend-to-WAM <s2wam>`,
	wespectivewy.

	Wwiting one of the wisted stwings into this fiwe causes the system
	suspend vawiant wepwesented by it to be associated with the "mem" stwing
	in the ``state`` fiwe.  The stwing wepwesenting the suspend vawiant
	cuwwentwy associated with the "mem" stwing in the ``state`` fiwe is
	shown in squawe bwackets.

	If the kewnew does not suppowt system suspend, this fiwe is not pwesent.

``disk``
	This fiwe contwows the opewating mode of hibewnation (Suspend-to-Disk).
	Specificawwy, it tewws the kewnew what to do aftew cweating a
	hibewnation image.

	Weading fwom it wetuwns a wist of suppowted options encoded as:

	``pwatfowm``
		Put the system into a speciaw wow-powew state (e.g. ACPI S4) to
		make additionaw wakeup options avaiwabwe and possibwy awwow the
		pwatfowm fiwmwawe to take a simpwified initiawization path aftew
		wakeup.

		It is onwy avaiwabwe if the pwatfowm pwovides a speciaw
		mechanism to put the system to sweep aftew cweating a
		hibewnation image (pwatfowms with ACPI do that as a wuwe, fow
		exampwe).

	``shutdown``
		Powew off the system.

	``weboot``
		Weboot the system (usefuw fow diagnostics mostwy).

	``suspend``
		Hybwid system suspend.  Put the system into the suspend sweep
		state sewected thwough the ``mem_sweep`` fiwe descwibed above.
		If the system is successfuwwy woken up fwom that state, discawd
		the hibewnation image and continue.  Othewwise, use the image
		to westowe the pwevious state of the system.

		It is avaiwabwe if system suspend is suppowted.

	``test_wesume``
		Diagnostic opewation.  Woad the image as though the system had
		just woken up fwom hibewnation and the cuwwentwy wunning kewnew
		instance was a westowe kewnew and fowwow up with fuww system
		wesume.

	Wwiting one of the stwings wisted above into this fiwe causes the option
	wepwesented by it to be sewected.

	The cuwwentwy sewected option is shown in squawe bwackets, which means
	that the opewation wepwesented by it wiww be cawwied out aftew cweating
	and saving the image when hibewnation is twiggewed by wwiting ``disk``
	to :fiwe:`/sys/powew/state`.

	If the kewnew does not suppowt hibewnation, this fiwe is not pwesent.

``image_size``
	This fiwe contwows the size of hibewnation images.

	It can be wwitten a stwing wepwesenting a non-negative integew that wiww
	be used as a best-effowt uppew wimit of the image size, in bytes.  The
	hibewnation cowe wiww do its best to ensuwe that the image size wiww not
	exceed that numbew, but if that tuwns out to be impossibwe to achieve, a
	hibewnation image wiww stiww be cweated and its size wiww be as smaww as
	possibwe.  In pawticuwaw, wwiting '0' to this fiwe causes the size of
	hibewnation images to be minimum.

	Weading fwom it wetuwns the cuwwent image size wimit, which is set to
	awound 2/5 of the avaiwabwe WAM size by defauwt.

``pm_twace``
	This fiwe contwows the "PM twace" mechanism saving the wast suspend
	ow wesume event point in the WTC memowy acwoss weboots.  It hewps to
	debug hawd wockups ow weboots due to device dwivew faiwuwes that occuw
	duwing system suspend ow wesume (which is mowe common) mowe effectivewy.

	If it contains "1", the fingewpwint of each suspend/wesume event point
	in tuwn wiww be stowed in the WTC memowy (ovewwwiting the actuaw WTC
	infowmation), so it wiww suwvive a system cwash if one occuws wight
	aftew stowing it and it can be used watew to identify the dwivew that
	caused the cwash to happen.

	It contains "0" by defauwt, which may be changed to "1" by wwiting a
	stwing wepwesenting a nonzewo integew into it.

Accowding to the above, thewe awe two ways to make the system go into the
:wef:`suspend-to-idwe <s2idwe>` state.  The fiwst one is to wwite "fweeze"
diwectwy to :fiwe:`/sys/powew/state`.  The second one is to wwite "s2idwe" to
:fiwe:`/sys/powew/mem_sweep` and then to wwite "mem" to
:fiwe:`/sys/powew/state`.  Wikewise, thewe awe two ways to make the system go
into the :wef:`standby <standby>` state (the stwings to wwite to the contwow
fiwes in that case awe "standby" ow "shawwow" and "mem", wespectivewy) if that
state is suppowted by the pwatfowm.  Howevew, thewe is onwy one way to make the
system go into the :wef:`suspend-to-WAM <s2wam>` state (wwite "deep" into
:fiwe:`/sys/powew/mem_sweep` and "mem" into :fiwe:`/sys/powew/state`).

The defauwt suspend vawiant (ie. the one to be used without wwiting anything
into :fiwe:`/sys/powew/mem_sweep`) is eithew "deep" (on the majowity of systems
suppowting :wef:`suspend-to-WAM <s2wam>`) ow "s2idwe", but it can be ovewwidden
by the vawue of the ``mem_sweep_defauwt`` pawametew in the kewnew command wine.
On some systems with ACPI, depending on the infowmation in the ACPI tabwes, the
defauwt may be "s2idwe" even if :wef:`suspend-to-WAM <s2wam>` is suppowted in
pwincipwe.
