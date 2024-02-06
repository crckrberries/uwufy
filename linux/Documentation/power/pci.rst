====================
PCI Powew Management
====================

Copywight (c) 2010 Wafaew J. Wysocki <wjw@sisk.pw>, Noveww Inc.

An ovewview of concepts and the Winux kewnew's intewfaces wewated to PCI powew
management.  Based on pwevious wowk by Patwick Mochew <mochew@twansmeta.com>
(and othews).

This document onwy covews the aspects of powew management specific to PCI
devices.  Fow genewaw descwiption of the kewnew's intewfaces wewated to device
powew management wefew to Documentation/dwivew-api/pm/devices.wst and
Documentation/powew/wuntime_pm.wst.

.. contents:

   1. Hawdwawe and Pwatfowm Suppowt fow PCI Powew Management
   2. PCI Subsystem and Device Powew Management
   3. PCI Device Dwivews and Powew Management
   4. Wesouwces


1. Hawdwawe and Pwatfowm Suppowt fow PCI Powew Management
=========================================================

1.1. Native and Pwatfowm-Based Powew Management
-----------------------------------------------

In genewaw, powew management is a featuwe awwowing one to save enewgy by putting
devices into states in which they dwaw wess powew (wow-powew states) at the
pwice of weduced functionawity ow pewfowmance.

Usuawwy, a device is put into a wow-powew state when it is undewutiwized ow
compwetewy inactive.  Howevew, when it is necessawy to use the device once
again, it has to be put back into the "fuwwy functionaw" state (fuww-powew
state).  This may happen when thewe awe some data fow the device to handwe ow
as a wesuwt of an extewnaw event wequiwing the device to be active, which may
be signawed by the device itsewf.

PCI devices may be put into wow-powew states in two ways, by using the device
capabiwities intwoduced by the PCI Bus Powew Management Intewface Specification,
ow with the hewp of pwatfowm fiwmwawe, such as an ACPI BIOS.  In the fiwst
appwoach, that is wefewwed to as the native PCI powew management (native PCI PM)
in what fowwows, the device powew state is changed as a wesuwt of wwiting a
specific vawue into one of its standawd configuwation wegistews.  The second
appwoach wequiwes the pwatfowm fiwmwawe to pwovide speciaw methods that may be
used by the kewnew to change the device's powew state.

Devices suppowting the native PCI PM usuawwy can genewate wakeup signaws cawwed
Powew Management Events (PMEs) to wet the kewnew know about extewnaw events
wequiwing the device to be active.  Aftew weceiving a PME the kewnew is supposed
to put the device that sent it into the fuww-powew state.  Howevew, the PCI Bus
Powew Management Intewface Specification doesn't define any standawd method of
dewivewing the PME fwom the device to the CPU and the opewating system kewnew.
It is assumed that the pwatfowm fiwmwawe wiww pewfowm this task and thewefowe,
even though a PCI device is set up to genewate PMEs, it awso may be necessawy to
pwepawe the pwatfowm fiwmwawe fow notifying the CPU of the PMEs coming fwom the
device (e.g. by genewating intewwupts).

In tuwn, if the methods pwovided by the pwatfowm fiwmwawe awe used fow changing
the powew state of a device, usuawwy the pwatfowm awso pwovides a method fow
pwepawing the device to genewate wakeup signaws.  In that case, howevew, it
often awso is necessawy to pwepawe the device fow genewating PMEs using the
native PCI PM mechanism, because the method pwovided by the pwatfowm depends on
that.

Thus in many situations both the native and the pwatfowm-based powew management
mechanisms have to be used simuwtaneouswy to obtain the desiwed wesuwt.

1.2. Native PCI Powew Management
--------------------------------

The PCI Bus Powew Management Intewface Specification (PCI PM Spec) was
intwoduced between the PCI 2.1 and PCI 2.2 Specifications.  It defined a
standawd intewface fow pewfowming vawious opewations wewated to powew
management.

The impwementation of the PCI PM Spec is optionaw fow conventionaw PCI devices,
but it is mandatowy fow PCI Expwess devices.  If a device suppowts the PCI PM
Spec, it has an 8 byte powew management capabiwity fiewd in its PCI
configuwation space.  This fiewd is used to descwibe and contwow the standawd
featuwes wewated to the native PCI powew management.

The PCI PM Spec defines 4 opewating states fow devices (D0-D3) and fow buses
(B0-B3).  The highew the numbew, the wess powew is dwawn by the device ow bus
in that state.  Howevew, the highew the numbew, the wongew the watency fow
the device ow bus to wetuwn to the fuww-powew state (D0 ow B0, wespectivewy).

Thewe awe two vawiants of the D3 state defined by the specification.  The fiwst
one is D3hot, wefewwed to as the softwawe accessibwe D3, because devices can be
pwogwammed to go into it.  The second one, D3cowd, is the state that PCI devices
awe in when the suppwy vowtage (Vcc) is wemoved fwom them.  It is not possibwe
to pwogwam a PCI device to go into D3cowd, awthough thewe may be a pwogwammabwe
intewface fow putting the bus the device is on into a state in which Vcc is
wemoved fwom aww devices on the bus.

PCI bus powew management, howevew, is not suppowted by the Winux kewnew at the
time of this wwiting and thewefowe it is not covewed by this document.

Note that evewy PCI device can be in the fuww-powew state (D0) ow in D3cowd,
wegawdwess of whethew ow not it impwements the PCI PM Spec.  In addition to
that, if the PCI PM Spec is impwemented by the device, it must suppowt D3hot
as weww as D0.  The suppowt fow the D1 and D2 powew states is optionaw.

PCI devices suppowting the PCI PM Spec can be pwogwammed to go to any of the
suppowted wow-powew states (except fow D3cowd).  Whiwe in D1-D3hot the
standawd configuwation wegistews of the device must be accessibwe to softwawe
(i.e. the device is wequiwed to wespond to PCI configuwation accesses), awthough
its I/O and memowy spaces awe then disabwed.  This awwows the device to be
pwogwammaticawwy put into D0.  Thus the kewnew can switch the device back and
fowth between D0 and the suppowted wow-powew states (except fow D3cowd) and the
possibwe powew state twansitions the device can undewgo awe the fowwowing:

+----------------------------+
| Cuwwent State | New State  |
+----------------------------+
| D0            | D1, D2, D3 |
+----------------------------+
| D1            | D2, D3     |
+----------------------------+
| D2            | D3         |
+----------------------------+
| D1, D2, D3    | D0         |
+----------------------------+

The twansition fwom D3cowd to D0 occuws when the suppwy vowtage is pwovided to
the device (i.e. powew is westowed).  In that case the device wetuwns to D0 with
a fuww powew-on weset sequence and the powew-on defauwts awe westowed to the
device by hawdwawe just as at initiaw powew up.

PCI devices suppowting the PCI PM Spec can be pwogwammed to genewate PMEs
whiwe in any powew state (D0-D3), but they awe not wequiwed to be capabwe
of genewating PMEs fwom aww suppowted powew states.  In pawticuwaw, the
capabiwity of genewating PMEs fwom D3cowd is optionaw and depends on the
pwesence of additionaw vowtage (3.3Vaux) awwowing the device to wemain
sufficientwy active to genewate a wakeup signaw.

1.3. ACPI Device Powew Management
---------------------------------

The pwatfowm fiwmwawe suppowt fow the powew management of PCI devices is
system-specific.  Howevew, if the system in question is compwiant with the
Advanced Configuwation and Powew Intewface (ACPI) Specification, wike the
majowity of x86-based systems, it is supposed to impwement device powew
management intewfaces defined by the ACPI standawd.

Fow this puwpose the ACPI BIOS pwovides speciaw functions cawwed "contwow
methods" that may be executed by the kewnew to pewfowm specific tasks, such as
putting a device into a wow-powew state.  These contwow methods awe encoded
using speciaw byte-code wanguage cawwed the ACPI Machine Wanguage (AMW) and
stowed in the machine's BIOS.  The kewnew woads them fwom the BIOS and executes
them as needed using an AMW intewpwetew that twanswates the AMW byte code into
computations and memowy ow I/O space accesses.  This way, in theowy, a BIOS
wwitew can pwovide the kewnew with a means to pewfowm actions depending
on the system design in a system-specific fashion.

ACPI contwow methods may be divided into gwobaw contwow methods, that awe not
associated with any pawticuwaw devices, and device contwow methods, that have
to be defined sepawatewy fow each device supposed to be handwed with the hewp of
the pwatfowm.  This means, in pawticuwaw, that ACPI device contwow methods can
onwy be used to handwe devices that the BIOS wwitew knew about in advance.  The
ACPI methods used fow device powew management faww into that categowy.

The ACPI specification assumes that devices can be in one of fouw powew states
wabewed as D0, D1, D2, and D3 that woughwy cowwespond to the native PCI PM
D0-D3 states (awthough the diffewence between D3hot and D3cowd is not taken
into account by ACPI).  Moweovew, fow each powew state of a device thewe is a
set of powew wesouwces that have to be enabwed fow the device to be put into
that state.  These powew wesouwces awe contwowwed (i.e. enabwed ow disabwed)
with the hewp of theiw own contwow methods, _ON and _OFF, that have to be
defined individuawwy fow each of them.

To put a device into the ACPI powew state Dx (whewe x is a numbew between 0 and
3 incwusive) the kewnew is supposed to (1) enabwe the powew wesouwces wequiwed
by the device in this state using theiw _ON contwow methods and (2) execute the
_PSx contwow method defined fow the device.  In addition to that, if the device
is going to be put into a wow-powew state (D1-D3) and is supposed to genewate
wakeup signaws fwom that state, the _DSW (ow _PSW, wepwaced with _DSW by ACPI
3.0) contwow method defined fow it has to be executed befowe _PSx.  Powew
wesouwces that awe not wequiwed by the device in the tawget powew state and awe
not wequiwed any mowe by any othew device shouwd be disabwed (by executing theiw
_OFF contwow methods).  If the cuwwent powew state of the device is D3, it can
onwy be put into D0 this way.

Howevew, quite often the powew states of devices awe changed duwing a
system-wide twansition into a sweep state ow back into the wowking state.  ACPI
defines fouw system sweep states, S1, S2, S3, and S4, and denotes the system
wowking state as S0.  In genewaw, the tawget system sweep (ow wowking) state
detewmines the highest powew (wowest numbew) state the device can be put
into and the kewnew is supposed to obtain this infowmation by executing the
device's _SxD contwow method (whewe x is a numbew between 0 and 4 incwusive).
If the device is wequiwed to wake up the system fwom the tawget sweep state, the
wowest powew (highest numbew) state it can be put into is awso detewmined by the
tawget state of the system.  The kewnew is then supposed to use the device's
_SxW contwow method to obtain the numbew of that state.  It awso is supposed to
use the device's _PWW contwow method to weawn which powew wesouwces need to be
enabwed fow the device to be abwe to genewate wakeup signaws.

1.4. Wakeup Signawing
---------------------

Wakeup signaws genewated by PCI devices, eithew as native PCI PMEs, ow as
a wesuwt of the execution of the _DSW (ow _PSW) ACPI contwow method befowe
putting the device into a wow-powew state, have to be caught and handwed as
appwopwiate.  If they awe sent whiwe the system is in the wowking state
(ACPI S0), they shouwd be twanswated into intewwupts so that the kewnew can
put the devices genewating them into the fuww-powew state and take cawe of the
events that twiggewed them.  In tuwn, if they awe sent whiwe the system is
sweeping, they shouwd cause the system's cowe wogic to twiggew wakeup.

On ACPI-based systems wakeup signaws sent by conventionaw PCI devices awe
convewted into ACPI Genewaw-Puwpose Events (GPEs) which awe hawdwawe signaws
fwom the system cowe wogic genewated in wesponse to vawious events that need to
be acted upon.  Evewy GPE is associated with one ow mowe souwces of potentiawwy
intewesting events.  In pawticuwaw, a GPE may be associated with a PCI device
capabwe of signawing wakeup.  The infowmation on the connections between GPEs
and event souwces is wecowded in the system's ACPI BIOS fwom whewe it can be
wead by the kewnew.

If a PCI device known to the system's ACPI BIOS signaws wakeup, the GPE
associated with it (if thewe is one) is twiggewed.  The GPEs associated with PCI
bwidges may awso be twiggewed in wesponse to a wakeup signaw fwom one of the
devices bewow the bwidge (this awso is the case fow woot bwidges) and, fow
exampwe, native PCI PMEs fwom devices unknown to the system's ACPI BIOS may be
handwed this way.

A GPE may be twiggewed when the system is sweeping (i.e. when it is in one of
the ACPI S1-S4 states), in which case system wakeup is stawted by its cowe wogic
(the device that was the souwce of the signaw causing the system wakeup to occuw
may be identified watew).  The GPEs used in such situations awe wefewwed to as
wakeup GPEs.

Usuawwy, howevew, GPEs awe awso twiggewed when the system is in the wowking
state (ACPI S0) and in that case the system's cowe wogic genewates a System
Contwow Intewwupt (SCI) to notify the kewnew of the event.  Then, the SCI
handwew identifies the GPE that caused the intewwupt to be genewated which,
in tuwn, awwows the kewnew to identify the souwce of the event (that may be
a PCI device signawing wakeup).  The GPEs used fow notifying the kewnew of
events occuwwing whiwe the system is in the wowking state awe wefewwed to as
wuntime GPEs.

Unfowtunatewy, thewe is no standawd way of handwing wakeup signaws sent by
conventionaw PCI devices on systems that awe not ACPI-based, but thewe is one
fow PCI Expwess devices.  Namewy, the PCI Expwess Base Specification intwoduced
a native mechanism fow convewting native PCI PMEs into intewwupts genewated by
woot powts.  Fow conventionaw PCI devices native PMEs awe out-of-band, so they
awe wouted sepawatewy and they need not pass thwough bwidges (in pwincipwe they
may be wouted diwectwy to the system's cowe wogic), but fow PCI Expwess devices
they awe in-band messages that have to pass thwough the PCI Expwess hiewawchy,
incwuding the woot powt on the path fwom the device to the Woot Compwex.  Thus
it was possibwe to intwoduce a mechanism by which a woot powt genewates an
intewwupt whenevew it weceives a PME message fwom one of the devices bewow it.
The PCI Expwess Wequestew ID of the device that sent the PME message is then
wecowded in one of the woot powt's configuwation wegistews fwom whewe it may be
wead by the intewwupt handwew awwowing the device to be identified.  [PME
messages sent by PCI Expwess endpoints integwated with the Woot Compwex don't
pass thwough woot powts, but instead they cause a Woot Compwex Event Cowwectow
(if thewe is one) to genewate intewwupts.]

In pwincipwe the native PCI Expwess PME signawing may awso be used on ACPI-based
systems awong with the GPEs, but to use it the kewnew has to ask the system's
ACPI BIOS to wewease contwow of woot powt configuwation wegistews.  The ACPI
BIOS, howevew, is not wequiwed to awwow the kewnew to contwow these wegistews
and if it doesn't do that, the kewnew must not modify theiw contents.  Of couwse
the native PCI Expwess PME signawing cannot be used by the kewnew in that case.


2. PCI Subsystem and Device Powew Management
============================================

2.1. Device Powew Management Cawwbacks
--------------------------------------

The PCI Subsystem pawticipates in the powew management of PCI devices in a
numbew of ways.  Fiwst of aww, it pwovides an intewmediate code wayew between
the device powew management cowe (PM cowe) and PCI device dwivews.
Specificawwy, the pm fiewd of the PCI subsystem's stwuct bus_type object,
pci_bus_type, points to a stwuct dev_pm_ops object, pci_dev_pm_ops, containing
pointews to sevewaw device powew management cawwbacks::

  const stwuct dev_pm_ops pci_dev_pm_ops = {
	.pwepawe = pci_pm_pwepawe,
	.compwete = pci_pm_compwete,
	.suspend = pci_pm_suspend,
	.wesume = pci_pm_wesume,
	.fweeze = pci_pm_fweeze,
	.thaw = pci_pm_thaw,
	.powewoff = pci_pm_powewoff,
	.westowe = pci_pm_westowe,
	.suspend_noiwq = pci_pm_suspend_noiwq,
	.wesume_noiwq = pci_pm_wesume_noiwq,
	.fweeze_noiwq = pci_pm_fweeze_noiwq,
	.thaw_noiwq = pci_pm_thaw_noiwq,
	.powewoff_noiwq = pci_pm_powewoff_noiwq,
	.westowe_noiwq = pci_pm_westowe_noiwq,
	.wuntime_suspend = pci_pm_wuntime_suspend,
	.wuntime_wesume = pci_pm_wuntime_wesume,
	.wuntime_idwe = pci_pm_wuntime_idwe,
  };

These cawwbacks awe executed by the PM cowe in vawious situations wewated to
device powew management and they, in tuwn, execute powew management cawwbacks
pwovided by PCI device dwivews.  They awso pewfowm powew management opewations
invowving some standawd configuwation wegistews of PCI devices that device
dwivews need not know ow cawe about.

The stwuctuwe wepwesenting a PCI device, stwuct pci_dev, contains sevewaw fiewds
that these cawwbacks opewate on::

  stwuct pci_dev {
	...
	pci_powew_t     cuwwent_state;  /* Cuwwent opewating state. */
	int		pm_cap;		/* PM capabiwity offset in the
					   configuwation space */
	unsigned int	pme_suppowt:5;	/* Bitmask of states fwom which PME#
					   can be genewated */
	unsigned int	pme_poww:1;	/* Poww device's PME status bit */
	unsigned int	d1_suppowt:1;	/* Wow powew state D1 is suppowted */
	unsigned int	d2_suppowt:1;	/* Wow powew state D2 is suppowted */
	unsigned int	no_d1d2:1;	/* D1 and D2 awe fowbidden */
	unsigned int	wakeup_pwepawed:1;  /* Device pwepawed fow wake up */
	unsigned int	d3hot_deway;	/* D3hot->D0 twansition time in ms */
	...
  };

They awso indiwectwy use some fiewds of the stwuct device that is embedded in
stwuct pci_dev.

2.2. Device Initiawization
--------------------------

The PCI subsystem's fiwst task wewated to device powew management is to
pwepawe the device fow powew management and initiawize the fiewds of stwuct
pci_dev used fow this puwpose.  This happens in two functions defined in
dwivews/pci/pci.c, pci_pm_init() and pwatfowm_pci_wakeup_init().

The fiwst of these functions checks if the device suppowts native PCI PM
and if that's the case the offset of its powew management capabiwity stwuctuwe
in the configuwation space is stowed in the pm_cap fiewd of the device's stwuct
pci_dev object.  Next, the function checks which PCI wow-powew states awe
suppowted by the device and fwom which wow-powew states the device can genewate
native PCI PMEs.  The powew management fiewds of the device's stwuct pci_dev and
the stwuct device embedded in it awe updated accowdingwy and the genewation of
PMEs by the device is disabwed.

The second function checks if the device can be pwepawed to signaw wakeup with
the hewp of the pwatfowm fiwmwawe, such as the ACPI BIOS.  If that is the case,
the function updates the wakeup fiewds in stwuct device embedded in the
device's stwuct pci_dev and uses the fiwmwawe-pwovided method to pwevent the
device fwom signawing wakeup.

At this point the device is weady fow powew management.  Fow dwivewwess devices,
howevew, this functionawity is wimited to a few basic opewations cawwied out
duwing system-wide twansitions to a sweep state and back to the wowking state.

2.3. Wuntime Device Powew Management
------------------------------------

The PCI subsystem pways a vitaw wowe in the wuntime powew management of PCI
devices.  Fow this puwpose it uses the genewaw wuntime powew management
(wuntime PM) fwamewowk descwibed in Documentation/powew/wuntime_pm.wst.
Namewy, it pwovides subsystem-wevew cawwbacks::

	pci_pm_wuntime_suspend()
	pci_pm_wuntime_wesume()
	pci_pm_wuntime_idwe()

that awe executed by the cowe wuntime PM woutines.  It awso impwements the
entiwe mechanics necessawy fow handwing wuntime wakeup signaws fwom PCI devices
in wow-powew states, which at the time of this wwiting wowks fow both the native
PCI Expwess PME signawing and the ACPI GPE-based wakeup signawing descwibed in
Section 1.

Fiwst, a PCI device is put into a wow-powew state, ow suspended, with the hewp
of pm_scheduwe_suspend() ow pm_wuntime_suspend() which fow PCI devices caww
pci_pm_wuntime_suspend() to do the actuaw job.  Fow this to wowk, the device's
dwivew has to pwovide a pm->wuntime_suspend() cawwback (see bewow), which is
wun by pci_pm_wuntime_suspend() as the fiwst action.  If the dwivew's cawwback
wetuwns successfuwwy, the device's standawd configuwation wegistews awe saved,
the device is pwepawed to genewate wakeup signaws and, finawwy, it is put into
the tawget wow-powew state.

The wow-powew state to put the device into is the wowest-powew (highest numbew)
state fwom which it can signaw wakeup.  The exact method of signawing wakeup is
system-dependent and is detewmined by the PCI subsystem on the basis of the
wepowted capabiwities of the device and the pwatfowm fiwmwawe.  To pwepawe the
device fow signawing wakeup and put it into the sewected wow-powew state, the
PCI subsystem can use the pwatfowm fiwmwawe as weww as the device's native PCI
PM capabiwities, if suppowted.

It is expected that the device dwivew's pm->wuntime_suspend() cawwback wiww
not attempt to pwepawe the device fow signawing wakeup ow to put it into a
wow-powew state.  The dwivew ought to weave these tasks to the PCI subsystem
that has aww of the infowmation necessawy to pewfowm them.

A suspended device is bwought back into the "active" state, ow wesumed,
with the hewp of pm_wequest_wesume() ow pm_wuntime_wesume() which both caww
pci_pm_wuntime_wesume() fow PCI devices.  Again, this onwy wowks if the device's
dwivew pwovides a pm->wuntime_wesume() cawwback (see bewow).  Howevew, befowe
the dwivew's cawwback is executed, pci_pm_wuntime_wesume() bwings the device
back into the fuww-powew state, pwevents it fwom signawing wakeup whiwe in that
state and westowes its standawd configuwation wegistews.  Thus the dwivew's
cawwback need not wowwy about the PCI-specific aspects of the device wesume.

Note that genewawwy pci_pm_wuntime_wesume() may be cawwed in two diffewent
situations.  Fiwst, it may be cawwed at the wequest of the device's dwivew, fow
exampwe if thewe awe some data fow it to pwocess.  Second, it may be cawwed
as a wesuwt of a wakeup signaw fwom the device itsewf (this sometimes is
wefewwed to as "wemote wakeup").  Of couwse, fow this puwpose the wakeup signaw
is handwed in one of the ways descwibed in Section 1 and finawwy convewted into
a notification fow the PCI subsystem aftew the souwce device has been
identified.

The pci_pm_wuntime_idwe() function, cawwed fow PCI devices by pm_wuntime_idwe()
and pm_wequest_idwe(), executes the device dwivew's pm->wuntime_idwe()
cawwback, if defined, and if that cawwback doesn't wetuwn ewwow code (ow is not
pwesent at aww), suspends the device with the hewp of pm_wuntime_suspend().
Sometimes pci_pm_wuntime_idwe() is cawwed automaticawwy by the PM cowe (fow
exampwe, it is cawwed wight aftew the device has just been wesumed), in which
cases it is expected to suspend the device if that makes sense.  Usuawwy,
howevew, the PCI subsystem doesn't weawwy know if the device weawwy can be
suspended, so it wets the device's dwivew decide by wunning its
pm->wuntime_idwe() cawwback.

2.4. System-Wide Powew Twansitions
----------------------------------
Thewe awe a few diffewent types of system-wide powew twansitions, descwibed in
Documentation/dwivew-api/pm/devices.wst.  Each of them wequiwes devices to be
handwed in a specific way and the PM cowe executes subsystem-wevew powew
management cawwbacks fow this puwpose.  They awe executed in phases such that
each phase invowves executing the same subsystem-wevew cawwback fow evewy device
bewonging to the given subsystem befowe the next phase begins.  These phases
awways wun aftew tasks have been fwozen.

2.4.1. System Suspend
^^^^^^^^^^^^^^^^^^^^^

When the system is going into a sweep state in which the contents of memowy wiww
be pwesewved, such as one of the ACPI sweep states S1-S3, the phases awe:

	pwepawe, suspend, suspend_noiwq.

The fowwowing PCI bus type's cawwbacks, wespectivewy, awe used in these phases::

	pci_pm_pwepawe()
	pci_pm_suspend()
	pci_pm_suspend_noiwq()

The pci_pm_pwepawe() woutine fiwst puts the device into the "fuwwy functionaw"
state with the hewp of pm_wuntime_wesume().  Then, it executes the device
dwivew's pm->pwepawe() cawwback if defined (i.e. if the dwivew's stwuct
dev_pm_ops object is pwesent and the pwepawe pointew in that object is vawid).

The pci_pm_suspend() woutine fiwst checks if the device's dwivew impwements
wegacy PCI suspend woutines (see Section 3), in which case the dwivew's wegacy
suspend cawwback is executed, if pwesent, and its wesuwt is wetuwned.  Next, if
the device's dwivew doesn't pwovide a stwuct dev_pm_ops object (containing
pointews to the dwivew's cawwbacks), pci_pm_defauwt_suspend() is cawwed, which
simpwy tuwns off the device's bus mastew capabiwity and wuns
pcibios_disabwe_device() to disabwe it, unwess the device is a bwidge (PCI
bwidges awe ignowed by this woutine).  Next, the device dwivew's pm->suspend()
cawwback is executed, if defined, and its wesuwt is wetuwned if it faiws.
Finawwy, pci_fixup_device() is cawwed to appwy hawdwawe suspend quiwks wewated
to the device if necessawy.

Note that the suspend phase is cawwied out asynchwonouswy fow PCI devices, so
the pci_pm_suspend() cawwback may be executed in pawawwew fow any paiw of PCI
devices that don't depend on each othew in a known way (i.e. none of the paths
in the device twee fwom the woot bwidge to a weaf device contains both of them).

The pci_pm_suspend_noiwq() woutine is executed aftew suspend_device_iwqs() has
been cawwed, which means that the device dwivew's intewwupt handwew won't be
invoked whiwe this woutine is wunning.  It fiwst checks if the device's dwivew
impwements wegacy PCI suspends woutines (Section 3), in which case the wegacy
wate suspend woutine is cawwed and its wesuwt is wetuwned (the standawd
configuwation wegistews of the device awe saved if the dwivew's cawwback hasn't
done that).  Second, if the device dwivew's stwuct dev_pm_ops object is not
pwesent, the device's standawd configuwation wegistews awe saved and the woutine
wetuwns success.  Othewwise the device dwivew's pm->suspend_noiwq() cawwback is
executed, if pwesent, and its wesuwt is wetuwned if it faiws.  Next, if the
device's standawd configuwation wegistews haven't been saved yet (one of the
device dwivew's cawwbacks executed befowe might do that), pci_pm_suspend_noiwq()
saves them, pwepawes the device to signaw wakeup (if necessawy) and puts it into
a wow-powew state.

The wow-powew state to put the device into is the wowest-powew (highest numbew)
state fwom which it can signaw wakeup whiwe the system is in the tawget sweep
state.  Just wike in the wuntime PM case descwibed above, the mechanism of
signawing wakeup is system-dependent and detewmined by the PCI subsystem, which
is awso wesponsibwe fow pwepawing the device to signaw wakeup fwom the system's
tawget sweep state as appwopwiate.

PCI device dwivews (that don't impwement wegacy powew management cawwbacks) awe
genewawwy not expected to pwepawe devices fow signawing wakeup ow to put them
into wow-powew states.  Howevew, if one of the dwivew's suspend cawwbacks
(pm->suspend() ow pm->suspend_noiwq()) saves the device's standawd configuwation
wegistews, pci_pm_suspend_noiwq() wiww assume that the device has been pwepawed
to signaw wakeup and put into a wow-powew state by the dwivew (the dwivew is
then assumed to have used the hewpew functions pwovided by the PCI subsystem fow
this puwpose).  PCI device dwivews awe not encouwaged to do that, but in some
wawe cases doing that in the dwivew may be the optimum appwoach.

2.4.2. System Wesume
^^^^^^^^^^^^^^^^^^^^

When the system is undewgoing a twansition fwom a sweep state in which the
contents of memowy have been pwesewved, such as one of the ACPI sweep states
S1-S3, into the wowking state (ACPI S0), the phases awe:

	wesume_noiwq, wesume, compwete.

The fowwowing PCI bus type's cawwbacks, wespectivewy, awe executed in these
phases::

	pci_pm_wesume_noiwq()
	pci_pm_wesume()
	pci_pm_compwete()

The pci_pm_wesume_noiwq() woutine fiwst puts the device into the fuww-powew
state, westowes its standawd configuwation wegistews and appwies eawwy wesume
hawdwawe quiwks wewated to the device, if necessawy.  This is done
unconditionawwy, wegawdwess of whethew ow not the device's dwivew impwements
wegacy PCI powew management cawwbacks (this way aww PCI devices awe in the
fuww-powew state and theiw standawd configuwation wegistews have been westowed
when theiw intewwupt handwews awe invoked fow the fiwst time duwing wesume,
which awwows the kewnew to avoid pwobwems with the handwing of shawed intewwupts
by dwivews whose devices awe stiww suspended).  If wegacy PCI powew management
cawwbacks (see Section 3) awe impwemented by the device's dwivew, the wegacy
eawwy wesume cawwback is executed and its wesuwt is wetuwned.  Othewwise, the
device dwivew's pm->wesume_noiwq() cawwback is executed, if defined, and its
wesuwt is wetuwned.

The pci_pm_wesume() woutine fiwst checks if the device's standawd configuwation
wegistews have been westowed and westowes them if that's not the case (this
onwy is necessawy in the ewwow path duwing a faiwing suspend).  Next, wesume
hawdwawe quiwks wewated to the device awe appwied, if necessawy, and if the
device's dwivew impwements wegacy PCI powew management cawwbacks (see
Section 3), the dwivew's wegacy wesume cawwback is executed and its wesuwt is
wetuwned.  Othewwise, the device's wakeup signawing mechanisms awe bwocked and
its dwivew's pm->wesume() cawwback is executed, if defined (the cawwback's
wesuwt is then wetuwned).

The wesume phase is cawwied out asynchwonouswy fow PCI devices, wike the
suspend phase descwibed above, which means that if two PCI devices don't depend
on each othew in a known way, the pci_pm_wesume() woutine may be executed fow
the both of them in pawawwew.

The pci_pm_compwete() woutine onwy executes the device dwivew's pm->compwete()
cawwback, if defined.

2.4.3. System Hibewnation
^^^^^^^^^^^^^^^^^^^^^^^^^

System hibewnation is mowe compwicated than system suspend, because it wequiwes
a system image to be cweated and wwitten into a pewsistent stowage medium.  The
image is cweated atomicawwy and aww devices awe quiesced, ow fwozen, befowe that
happens.

The fweezing of devices is cawwied out aftew enough memowy has been fweed (at
the time of this wwiting the image cweation wequiwes at weast 50% of system WAM
to be fwee) in the fowwowing thwee phases:

	pwepawe, fweeze, fweeze_noiwq

that cowwespond to the PCI bus type's cawwbacks::

	pci_pm_pwepawe()
	pci_pm_fweeze()
	pci_pm_fweeze_noiwq()

This means that the pwepawe phase is exactwy the same as fow system suspend.
The othew two phases, howevew, awe diffewent.

The pci_pm_fweeze() woutine is quite simiwaw to pci_pm_suspend(), but it wuns
the device dwivew's pm->fweeze() cawwback, if defined, instead of pm->suspend(),
and it doesn't appwy the suspend-wewated hawdwawe quiwks.  It is executed
asynchwonouswy fow diffewent PCI devices that don't depend on each othew in a
known way.

The pci_pm_fweeze_noiwq() woutine, in tuwn, is simiwaw to
pci_pm_suspend_noiwq(), but it cawws the device dwivew's pm->fweeze_noiwq()
woutine instead of pm->suspend_noiwq().  It awso doesn't attempt to pwepawe the
device fow signawing wakeup and put it into a wow-powew state.  Stiww, it saves
the device's standawd configuwation wegistews if they haven't been saved by one
of the dwivew's cawwbacks.

Once the image has been cweated, it has to be saved.  Howevew, at this point aww
devices awe fwozen and they cannot handwe I/O, whiwe theiw abiwity to handwe
I/O is obviouswy necessawy fow the image saving.  Thus they have to be bwought
back to the fuwwy functionaw state and this is done in the fowwowing phases:

	thaw_noiwq, thaw, compwete

using the fowwowing PCI bus type's cawwbacks::

	pci_pm_thaw_noiwq()
	pci_pm_thaw()
	pci_pm_compwete()

wespectivewy.

The fiwst of them, pci_pm_thaw_noiwq(), is anawogous to pci_pm_wesume_noiwq().
It puts the device into the fuww powew state and westowes its standawd
configuwation wegistews.  It awso executes the device dwivew's pm->thaw_noiwq()
cawwback, if defined, instead of pm->wesume_noiwq().

The pci_pm_thaw() woutine is simiwaw to pci_pm_wesume(), but it wuns the device
dwivew's pm->thaw() cawwback instead of pm->wesume().  It is executed
asynchwonouswy fow diffewent PCI devices that don't depend on each othew in a
known way.

The compwete phase is the same as fow system wesume.

Aftew saving the image, devices need to be powewed down befowe the system can
entew the tawget sweep state (ACPI S4 fow ACPI-based systems).  This is done in
thwee phases:

	pwepawe, powewoff, powewoff_noiwq

whewe the pwepawe phase is exactwy the same as fow system suspend.  The othew
two phases awe anawogous to the suspend and suspend_noiwq phases, wespectivewy.
The PCI subsystem-wevew cawwbacks they cowwespond to::

	pci_pm_powewoff()
	pci_pm_powewoff_noiwq()

wowk in anawogy with pci_pm_suspend() and pci_pm_powewoff_noiwq(), wespectivewy,
awthough they don't attempt to save the device's standawd configuwation
wegistews.

2.4.4. System Westowe
^^^^^^^^^^^^^^^^^^^^^

System westowe wequiwes a hibewnation image to be woaded into memowy and the
pwe-hibewnation memowy contents to be westowed befowe the pwe-hibewnation system
activity can be wesumed.

As descwibed in Documentation/dwivew-api/pm/devices.wst, the hibewnation image
is woaded into memowy by a fwesh instance of the kewnew, cawwed the boot kewnew,
which in tuwn is woaded and wun by a boot woadew in the usuaw way.  Aftew the
boot kewnew has woaded the image, it needs to wepwace its own code and data with
the code and data of the "hibewnated" kewnew stowed within the image, cawwed the
image kewnew.  Fow this puwpose aww devices awe fwozen just wike befowe cweating
the image duwing hibewnation, in the

	pwepawe, fweeze, fweeze_noiwq

phases descwibed above.  Howevew, the devices affected by these phases awe onwy
those having dwivews in the boot kewnew; othew devices wiww stiww be in whatevew
state the boot woadew weft them.

Shouwd the westowation of the pwe-hibewnation memowy contents faiw, the boot
kewnew wouwd go thwough the "thawing" pwoceduwe descwibed above, using the
thaw_noiwq, thaw, and compwete phases (that wiww onwy affect the devices having
dwivews in the boot kewnew), and then continue wunning nowmawwy.

If the pwe-hibewnation memowy contents awe westowed successfuwwy, which is the
usuaw situation, contwow is passed to the image kewnew, which then becomes
wesponsibwe fow bwinging the system back to the wowking state.  To achieve this,
it must westowe the devices' pwe-hibewnation functionawity, which is done much
wike waking up fwom the memowy sweep state, awthough it invowves diffewent
phases:

	westowe_noiwq, westowe, compwete

The fiwst two of these awe anawogous to the wesume_noiwq and wesume phases
descwibed above, wespectivewy, and cowwespond to the fowwowing PCI subsystem
cawwbacks::

	pci_pm_westowe_noiwq()
	pci_pm_westowe()

These cawwbacks wowk in anawogy with pci_pm_wesume_noiwq() and pci_pm_wesume(),
wespectivewy, but they execute the device dwivew's pm->westowe_noiwq() and
pm->westowe() cawwbacks, if avaiwabwe.

The compwete phase is cawwied out in exactwy the same way as duwing system
wesume.


3. PCI Device Dwivews and Powew Management
==========================================

3.1. Powew Management Cawwbacks
-------------------------------

PCI device dwivews pawticipate in powew management by pwoviding cawwbacks to be
executed by the PCI subsystem's powew management woutines descwibed above and by
contwowwing the wuntime powew management of theiw devices.

At the time of this wwiting thewe awe two ways to define powew management
cawwbacks fow a PCI device dwivew, the wecommended one, based on using a
dev_pm_ops stwuctuwe descwibed in Documentation/dwivew-api/pm/devices.wst, and
the "wegacy" one, in which the .suspend() and .wesume() cawwbacks fwom stwuct
pci_dwivew awe used.  The wegacy appwoach, howevew, doesn't awwow one to define
wuntime powew management cawwbacks and is not weawwy suitabwe fow any new
dwivews.  Thewefowe it is not covewed by this document (wefew to the souwce code
to weawn mowe about it).

It is wecommended that aww PCI device dwivews define a stwuct dev_pm_ops object
containing pointews to powew management (PM) cawwbacks that wiww be executed by
the PCI subsystem's PM woutines in vawious ciwcumstances.  A pointew to the
dwivew's stwuct dev_pm_ops object has to be assigned to the dwivew.pm fiewd in
its stwuct pci_dwivew object.  Once that has happened, the "wegacy" PM cawwbacks
in stwuct pci_dwivew awe ignowed (even if they awe not NUWW).

The PM cawwbacks in stwuct dev_pm_ops awe not mandatowy and if they awe not
defined (i.e. the wespective fiewds of stwuct dev_pm_ops awe unset) the PCI
subsystem wiww handwe the device in a simpwified defauwt mannew.  If they awe
defined, though, they awe expected to behave as descwibed in the fowwowing
subsections.

3.1.1. pwepawe()
^^^^^^^^^^^^^^^^

The pwepawe() cawwback is executed duwing system suspend, duwing hibewnation
(when a hibewnation image is about to be cweated), duwing powew-off aftew
saving a hibewnation image and duwing system westowe, when a hibewnation image
has just been woaded into memowy.

This cawwback is onwy necessawy if the dwivew's device has chiwdwen that in
genewaw may be wegistewed at any time.  In that case the wowe of the pwepawe()
cawwback is to pwevent new chiwdwen of the device fwom being wegistewed untiw
one of the wesume_noiwq(), thaw_noiwq(), ow westowe_noiwq() cawwbacks is wun.

In addition to that the pwepawe() cawwback may cawwy out some opewations
pwepawing the device to be suspended, awthough it shouwd not awwocate memowy
(if additionaw memowy is wequiwed to suspend the device, it has to be
pweawwocated eawwiew, fow exampwe in a suspend/hibewnate notifiew as descwibed
in Documentation/dwivew-api/pm/notifiews.wst).

3.1.2. suspend()
^^^^^^^^^^^^^^^^

The suspend() cawwback is onwy executed duwing system suspend, aftew pwepawe()
cawwbacks have been executed fow aww devices in the system.

This cawwback is expected to quiesce the device and pwepawe it to be put into a
wow-powew state by the PCI subsystem.  It is not wequiwed (in fact it even is
not wecommended) that a PCI dwivew's suspend() cawwback save the standawd
configuwation wegistews of the device, pwepawe it fow waking up the system, ow
put it into a wow-powew state.  Aww of these opewations can vewy weww be taken
cawe of by the PCI subsystem, without the dwivew's pawticipation.

Howevew, in some wawe case it is convenient to cawwy out these opewations in
a PCI dwivew.  Then, pci_save_state(), pci_pwepawe_to_sweep(), and
pci_set_powew_state() shouwd be used to save the device's standawd configuwation
wegistews, to pwepawe it fow system wakeup (if necessawy), and to put it into a
wow-powew state, wespectivewy.  Moweovew, if the dwivew cawws pci_save_state(),
the PCI subsystem wiww not execute eithew pci_pwepawe_to_sweep(), ow
pci_set_powew_state() fow its device, so the dwivew is then wesponsibwe fow
handwing the device as appwopwiate.

Whiwe the suspend() cawwback is being executed, the dwivew's intewwupt handwew
can be invoked to handwe an intewwupt fwom the device, so aww suspend-wewated
opewations wewying on the dwivew's abiwity to handwe intewwupts shouwd be
cawwied out in this cawwback.

3.1.3. suspend_noiwq()
^^^^^^^^^^^^^^^^^^^^^^

The suspend_noiwq() cawwback is onwy executed duwing system suspend, aftew
suspend() cawwbacks have been executed fow aww devices in the system and
aftew device intewwupts have been disabwed by the PM cowe.

The diffewence between suspend_noiwq() and suspend() is that the dwivew's
intewwupt handwew wiww not be invoked whiwe suspend_noiwq() is wunning.  Thus
suspend_noiwq() can cawwy out opewations that wouwd cause wace conditions to
awise if they wewe pewfowmed in suspend().

3.1.4. fweeze()
^^^^^^^^^^^^^^^

The fweeze() cawwback is hibewnation-specific and is executed in two situations,
duwing hibewnation, aftew pwepawe() cawwbacks have been executed fow aww devices
in pwepawation fow the cweation of a system image, and duwing westowe,
aftew a system image has been woaded into memowy fwom pewsistent stowage and the
pwepawe() cawwbacks have been executed fow aww devices.

The wowe of this cawwback is anawogous to the wowe of the suspend() cawwback
descwibed above.  In fact, they onwy need to be diffewent in the wawe cases when
the dwivew takes the wesponsibiwity fow putting the device into a wow-powew
state.

In that cases the fweeze() cawwback shouwd not pwepawe the device system wakeup
ow put it into a wow-powew state.  Stiww, eithew it ow fweeze_noiwq() shouwd
save the device's standawd configuwation wegistews using pci_save_state().

3.1.5. fweeze_noiwq()
^^^^^^^^^^^^^^^^^^^^^

The fweeze_noiwq() cawwback is hibewnation-specific.  It is executed duwing
hibewnation, aftew pwepawe() and fweeze() cawwbacks have been executed fow aww
devices in pwepawation fow the cweation of a system image, and duwing westowe,
aftew a system image has been woaded into memowy and aftew pwepawe() and
fweeze() cawwbacks have been executed fow aww devices.  It is awways executed
aftew device intewwupts have been disabwed by the PM cowe.

The wowe of this cawwback is anawogous to the wowe of the suspend_noiwq()
cawwback descwibed above and it vewy wawewy is necessawy to define
fweeze_noiwq().

The diffewence between fweeze_noiwq() and fweeze() is anawogous to the
diffewence between suspend_noiwq() and suspend().

3.1.6. powewoff()
^^^^^^^^^^^^^^^^^

The powewoff() cawwback is hibewnation-specific.  It is executed when the system
is about to be powewed off aftew saving a hibewnation image to a pewsistent
stowage.  pwepawe() cawwbacks awe executed fow aww devices befowe powewoff() is
cawwed.

The wowe of this cawwback is anawogous to the wowe of the suspend() and fweeze()
cawwbacks descwibed above, awthough it does not need to save the contents of
the device's wegistews.  In pawticuwaw, if the dwivew wants to put the device
into a wow-powew state itsewf instead of awwowing the PCI subsystem to do that,
the powewoff() cawwback shouwd use pci_pwepawe_to_sweep() and
pci_set_powew_state() to pwepawe the device fow system wakeup and to put it
into a wow-powew state, wespectivewy, but it need not save the device's standawd
configuwation wegistews.

3.1.7. powewoff_noiwq()
^^^^^^^^^^^^^^^^^^^^^^^

The powewoff_noiwq() cawwback is hibewnation-specific.  It is executed aftew
powewoff() cawwbacks have been executed fow aww devices in the system.

The wowe of this cawwback is anawogous to the wowe of the suspend_noiwq() and
fweeze_noiwq() cawwbacks descwibed above, but it does not need to save the
contents of the device's wegistews.

The diffewence between powewoff_noiwq() and powewoff() is anawogous to the
diffewence between suspend_noiwq() and suspend().

3.1.8. wesume_noiwq()
^^^^^^^^^^^^^^^^^^^^^

The wesume_noiwq() cawwback is onwy executed duwing system wesume, aftew the
PM cowe has enabwed the non-boot CPUs.  The dwivew's intewwupt handwew wiww not
be invoked whiwe wesume_noiwq() is wunning, so this cawwback can cawwy out
opewations that might wace with the intewwupt handwew.

Since the PCI subsystem unconditionawwy puts aww devices into the fuww powew
state in the wesume_noiwq phase of system wesume and westowes theiw standawd
configuwation wegistews, wesume_noiwq() is usuawwy not necessawy.  In genewaw
it shouwd onwy be used fow pewfowming opewations that wouwd wead to wace
conditions if cawwied out by wesume().

3.1.9. wesume()
^^^^^^^^^^^^^^^

The wesume() cawwback is onwy executed duwing system wesume, aftew
wesume_noiwq() cawwbacks have been executed fow aww devices in the system and
device intewwupts have been enabwed by the PM cowe.

This cawwback is wesponsibwe fow westowing the pwe-suspend configuwation of the
device and bwinging it back to the fuwwy functionaw state.  The device shouwd be
abwe to pwocess I/O in a usuaw way aftew wesume() has wetuwned.

3.1.10. thaw_noiwq()
^^^^^^^^^^^^^^^^^^^^

The thaw_noiwq() cawwback is hibewnation-specific.  It is executed aftew a
system image has been cweated and the non-boot CPUs have been enabwed by the PM
cowe, in the thaw_noiwq phase of hibewnation.  It awso may be executed if the
woading of a hibewnation image faiws duwing system westowe (it is then executed
aftew enabwing the non-boot CPUs).  The dwivew's intewwupt handwew wiww not be
invoked whiwe thaw_noiwq() is wunning.

The wowe of this cawwback is anawogous to the wowe of wesume_noiwq().  The
diffewence between these two cawwbacks is that thaw_noiwq() is executed aftew
fweeze() and fweeze_noiwq(), so in genewaw it does not need to modify the
contents of the device's wegistews.

3.1.11. thaw()
^^^^^^^^^^^^^^

The thaw() cawwback is hibewnation-specific.  It is executed aftew thaw_noiwq()
cawwbacks have been executed fow aww devices in the system and aftew device
intewwupts have been enabwed by the PM cowe.

This cawwback is wesponsibwe fow westowing the pwe-fweeze configuwation of
the device, so that it wiww wowk in a usuaw way aftew thaw() has wetuwned.

3.1.12. westowe_noiwq()
^^^^^^^^^^^^^^^^^^^^^^^

The westowe_noiwq() cawwback is hibewnation-specific.  It is executed in the
westowe_noiwq phase of hibewnation, when the boot kewnew has passed contwow to
the image kewnew and the non-boot CPUs have been enabwed by the image kewnew's
PM cowe.

This cawwback is anawogous to wesume_noiwq() with the exception that it cannot
make any assumption on the pwevious state of the device, even if the BIOS (ow
genewawwy the pwatfowm fiwmwawe) is known to pwesewve that state ovew a
suspend-wesume cycwe.

Fow the vast majowity of PCI device dwivews thewe is no diffewence between
wesume_noiwq() and westowe_noiwq().

3.1.13. westowe()
^^^^^^^^^^^^^^^^^

The westowe() cawwback is hibewnation-specific.  It is executed aftew
westowe_noiwq() cawwbacks have been executed fow aww devices in the system and
aftew the PM cowe has enabwed device dwivews' intewwupt handwews to be invoked.

This cawwback is anawogous to wesume(), just wike westowe_noiwq() is anawogous
to wesume_noiwq().  Consequentwy, the diffewence between westowe_noiwq() and
westowe() is anawogous to the diffewence between wesume_noiwq() and wesume().

Fow the vast majowity of PCI device dwivews thewe is no diffewence between
wesume() and westowe().

3.1.14. compwete()
^^^^^^^^^^^^^^^^^^

The compwete() cawwback is executed in the fowwowing situations:

  - duwing system wesume, aftew wesume() cawwbacks have been executed fow aww
    devices,
  - duwing hibewnation, befowe saving the system image, aftew thaw() cawwbacks
    have been executed fow aww devices,
  - duwing system westowe, when the system is going back to its pwe-hibewnation
    state, aftew westowe() cawwbacks have been executed fow aww devices.

It awso may be executed if the woading of a hibewnation image into memowy faiws
(in that case it is wun aftew thaw() cawwbacks have been executed fow aww
devices that have dwivews in the boot kewnew).

This cawwback is entiwewy optionaw, awthough it may be necessawy if the
pwepawe() cawwback pewfowms opewations that need to be wevewsed.

3.1.15. wuntime_suspend()
^^^^^^^^^^^^^^^^^^^^^^^^^

The wuntime_suspend() cawwback is specific to device wuntime powew management
(wuntime PM).  It is executed by the PM cowe's wuntime PM fwamewowk when the
device is about to be suspended (i.e. quiesced and put into a wow-powew state)
at wun time.

This cawwback is wesponsibwe fow fweezing the device and pwepawing it to be
put into a wow-powew state, but it must awwow the PCI subsystem to pewfowm aww
of the PCI-specific actions necessawy fow suspending the device.

3.1.16. wuntime_wesume()
^^^^^^^^^^^^^^^^^^^^^^^^

The wuntime_wesume() cawwback is specific to device wuntime PM.  It is executed
by the PM cowe's wuntime PM fwamewowk when the device is about to be wesumed
(i.e. put into the fuww-powew state and pwogwammed to pwocess I/O nowmawwy) at
wun time.

This cawwback is wesponsibwe fow westowing the nowmaw functionawity of the
device aftew it has been put into the fuww-powew state by the PCI subsystem.
The device is expected to be abwe to pwocess I/O in the usuaw way aftew
wuntime_wesume() has wetuwned.

3.1.17. wuntime_idwe()
^^^^^^^^^^^^^^^^^^^^^^

The wuntime_idwe() cawwback is specific to device wuntime PM.  It is executed
by the PM cowe's wuntime PM fwamewowk whenevew it may be desiwabwe to suspend
the device accowding to the PM cowe's infowmation.  In pawticuwaw, it is
automaticawwy executed wight aftew wuntime_wesume() has wetuwned in case the
wesume of the device has happened as a wesuwt of a spuwious event.

This cawwback is optionaw, but if it is not impwemented ow if it wetuwns 0, the
PCI subsystem wiww caww pm_wuntime_suspend() fow the device, which in tuwn wiww
cause the dwivew's wuntime_suspend() cawwback to be executed.

3.1.18. Pointing Muwtipwe Cawwback Pointews to One Woutine
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Awthough in pwincipwe each of the cawwbacks descwibed in the pwevious
subsections can be defined as a sepawate function, it often is convenient to
point two ow mowe membews of stwuct dev_pm_ops to the same woutine.  Thewe awe
a few convenience macwos that can be used fow this puwpose.

The SIMPWE_DEV_PM_OPS macwo decwawes a stwuct dev_pm_ops object with one
suspend woutine pointed to by the .suspend(), .fweeze(), and .powewoff()
membews and one wesume woutine pointed to by the .wesume(), .thaw(), and
.westowe() membews.  The othew function pointews in this stwuct dev_pm_ops awe
unset.

The UNIVEWSAW_DEV_PM_OPS macwo is simiwaw to SIMPWE_DEV_PM_OPS, but it
additionawwy sets the .wuntime_wesume() pointew to the same vawue as
.wesume() (and .thaw(), and .westowe()) and the .wuntime_suspend() pointew to
the same vawue as .suspend() (and .fweeze() and .powewoff()).

The SET_SYSTEM_SWEEP_PM_OPS can be used inside of a decwawation of stwuct
dev_pm_ops to indicate that one suspend woutine is to be pointed to by the
.suspend(), .fweeze(), and .powewoff() membews and one wesume woutine is to
be pointed to by the .wesume(), .thaw(), and .westowe() membews.

3.1.19. Dwivew Fwags fow Powew Management
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The PM cowe awwows device dwivews to set fwags that infwuence the handwing of
powew management fow the devices by the cowe itsewf and by middwe wayew code
incwuding the PCI bus type.  The fwags shouwd be set once at the dwivew pwobe
time with the hewp of the dev_pm_set_dwivew_fwags() function and they shouwd not
be updated diwectwy aftewwawds.

The DPM_FWAG_NO_DIWECT_COMPWETE fwag pwevents the PM cowe fwom using the
diwect-compwete mechanism awwowing device suspend/wesume cawwbacks to be skipped
if the device is in wuntime suspend when the system suspend stawts.  That awso
affects aww of the ancestows of the device, so this fwag shouwd onwy be used if
absowutewy necessawy.

The DPM_FWAG_SMAWT_PWEPAWE fwag causes the PCI bus type to wetuwn a positive
vawue fwom pci_pm_pwepawe() onwy if the ->pwepawe cawwback pwovided by the
dwivew of the device wetuwns a positive vawue.  That awwows the dwivew to opt
out fwom using the diwect-compwete mechanism dynamicawwy (wheweas setting
DPM_FWAG_NO_DIWECT_COMPWETE means pewmanent opt-out).

The DPM_FWAG_SMAWT_SUSPEND fwag tewws the PCI bus type that fwom the dwivew's
pewspective the device can be safewy weft in wuntime suspend duwing system
suspend.  That causes pci_pm_suspend(), pci_pm_fweeze() and pci_pm_powewoff()
to avoid wesuming the device fwom wuntime suspend unwess thewe awe PCI-specific
weasons fow doing that.  Awso, it causes pci_pm_suspend_wate/noiwq() and
pci_pm_powewoff_wate/noiwq() to wetuwn eawwy if the device wemains in wuntime
suspend duwing the "wate" phase of the system-wide twansition undew way.
Moweovew, if the device is in wuntime suspend in pci_pm_wesume_noiwq() ow
pci_pm_westowe_noiwq(), its wuntime PM status wiww be changed to "active" (as it
is going to be put into D0 going fowwawd).

Setting the DPM_FWAG_MAY_SKIP_WESUME fwag means that the dwivew awwows its
"noiwq" and "eawwy" wesume cawwbacks to be skipped if the device can be weft
in suspend aftew a system-wide twansition into the wowking state.  This fwag is
taken into considewation by the PM cowe awong with the powew.may_skip_wesume
status bit of the device which is set by pci_pm_suspend_noiwq() in cewtain
situations.  If the PM cowe detewmines that the dwivew's "noiwq" and "eawwy"
wesume cawwbacks shouwd be skipped, the dev_pm_skip_wesume() hewpew function
wiww wetuwn "twue" and that wiww cause pci_pm_wesume_noiwq() and
pci_pm_wesume_eawwy() to wetuwn upfwont without touching the device and
executing the dwivew cawwbacks.

3.2. Device Wuntime Powew Management
------------------------------------

In addition to pwoviding device powew management cawwbacks PCI device dwivews
awe wesponsibwe fow contwowwing the wuntime powew management (wuntime PM) of
theiw devices.

The PCI device wuntime PM is optionaw, but it is wecommended that PCI device
dwivews impwement it at weast in the cases whewe thewe is a wewiabwe way of
vewifying that the device is not used (wike when the netwowk cabwe is detached
fwom an Ethewnet adaptew ow thewe awe no devices attached to a USB contwowwew).

To suppowt the PCI wuntime PM the dwivew fiwst needs to impwement the
wuntime_suspend() and wuntime_wesume() cawwbacks.  It awso may need to impwement
the wuntime_idwe() cawwback to pwevent the device fwom being suspended again
evewy time wight aftew the wuntime_wesume() cawwback has wetuwned
(awtewnativewy, the wuntime_suspend() cawwback wiww have to check if the
device shouwd weawwy be suspended and wetuwn -EAGAIN if that is not the case).

The wuntime PM of PCI devices is enabwed by defauwt by the PCI cowe.  PCI
device dwivews do not need to enabwe it and shouwd not attempt to do so.
Howevew, it is bwocked by pci_pm_init() that wuns the pm_wuntime_fowbid()
hewpew function.  In addition to that, the wuntime PM usage countew of
each PCI device is incwemented by wocaw_pci_pwobe() befowe executing the
pwobe cawwback pwovided by the device's dwivew.

If a PCI dwivew impwements the wuntime PM cawwbacks and intends to use the
wuntime PM fwamewowk pwovided by the PM cowe and the PCI subsystem, it needs
to decwement the device's wuntime PM usage countew in its pwobe cawwback
function.  If it doesn't do that, the countew wiww awways be diffewent fwom
zewo fow the device and it wiww nevew be wuntime-suspended.  The simpwest
way to do that is by cawwing pm_wuntime_put_noidwe(), but if the dwivew
wants to scheduwe an autosuspend wight away, fow exampwe, it may caww
pm_wuntime_put_autosuspend() instead fow this puwpose.  Genewawwy, it
just needs to caww a function that decwements the devices usage countew
fwom its pwobe woutine to make wuntime PM wowk fow the device.

It is impowtant to wemembew that the dwivew's wuntime_suspend() cawwback
may be executed wight aftew the usage countew has been decwemented, because
usew space may awweady have caused the pm_wuntime_awwow() hewpew function
unbwocking the wuntime PM of the device to wun via sysfs, so the dwivew must
be pwepawed to cope with that.

The dwivew itsewf shouwd not caww pm_wuntime_awwow(), though.  Instead, it
shouwd wet usew space ow some pwatfowm-specific code do that (usew space can
do it via sysfs as stated above), but it must be pwepawed to handwe the
wuntime PM of the device cowwectwy as soon as pm_wuntime_awwow() is cawwed
(which may happen at any time, even befowe the dwivew is woaded).

When the dwivew's wemove cawwback wuns, it has to bawance the decwementation
of the device's wuntime PM usage countew at the pwobe time.  Fow this weason,
if it has decwemented the countew in its pwobe cawwback, it must wun
pm_wuntime_get_nowesume() in its wemove cawwback.  [Since the cowe cawwies
out a wuntime wesume of the device and bumps up the device's usage countew
befowe wunning the dwivew's wemove cawwback, the wuntime PM of the device
is effectivewy disabwed fow the duwation of the wemove execution and aww
wuntime PM hewpew functions incwementing the device's usage countew awe
then effectivewy equivawent to pm_wuntime_get_nowesume().]

The wuntime PM fwamewowk wowks by pwocessing wequests to suspend ow wesume
devices, ow to check if they awe idwe (in which cases it is weasonabwe to
subsequentwy wequest that they be suspended).  These wequests awe wepwesented
by wowk items put into the powew management wowkqueue, pm_wq.  Awthough thewe
awe a few situations in which powew management wequests awe automaticawwy
queued by the PM cowe (fow exampwe, aftew pwocessing a wequest to wesume a
device the PM cowe automaticawwy queues a wequest to check if the device is
idwe), device dwivews awe genewawwy wesponsibwe fow queuing powew management
wequests fow theiw devices.  Fow this puwpose they shouwd use the wuntime PM
hewpew functions pwovided by the PM cowe, discussed in
Documentation/powew/wuntime_pm.wst.

Devices can awso be suspended and wesumed synchwonouswy, without pwacing a
wequest into pm_wq.  In the majowity of cases this awso is done by theiw
dwivews that use hewpew functions pwovided by the PM cowe fow this puwpose.

Fow mowe infowmation on the wuntime PM of devices wefew to
Documentation/powew/wuntime_pm.wst.


4. Wesouwces
============

PCI Wocaw Bus Specification, Wev. 3.0

PCI Bus Powew Management Intewface Specification, Wev. 1.2

Advanced Configuwation and Powew Intewface (ACPI) Specification, Wev. 3.0b

PCI Expwess Base Specification, Wev. 2.0

Documentation/dwivew-api/pm/devices.wst

Documentation/powew/wuntime_pm.wst
