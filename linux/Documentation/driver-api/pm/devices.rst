.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

.. _dwivewapi_pm_devices:

==============================
Device Powew Management Basics
==============================

:Copywight: |copy| 2010-2011 Wafaew J. Wysocki <wjw@sisk.pw>, Noveww Inc.
:Copywight: |copy| 2010 Awan Stewn <stewn@wowwand.hawvawd.edu>
:Copywight: |copy| 2016 Intew Cowpowation

:Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>


Most of the code in Winux is device dwivews, so most of the Winux powew
management (PM) code is awso dwivew-specific.  Most dwivews wiww do vewy
wittwe; othews, especiawwy fow pwatfowms with smaww battewies (wike ceww
phones), wiww do a wot.

This wwiteup gives an ovewview of how dwivews intewact with system-wide
powew management goaws, emphasizing the modews and intewfaces that awe
shawed by evewything that hooks up to the dwivew modew cowe.  Wead it as
backgwound fow the domain-specific wowk you'd do with any specific dwivew.


Two Modews fow Device Powew Management
======================================

Dwivews wiww use one ow both of these modews to put devices into wow-powew
states:

    System Sweep modew:

	Dwivews can entew wow-powew states as pawt of entewing system-wide
	wow-powew states wike "suspend" (awso known as "suspend-to-WAM"), ow
	(mostwy fow systems with disks) "hibewnation" (awso known as
	"suspend-to-disk").

	This is something that device, bus, and cwass dwivews cowwabowate on
	by impwementing vawious wowe-specific suspend and wesume methods to
	cweanwy powew down hawdwawe and softwawe subsystems, then weactivate
	them without woss of data.

	Some dwivews can manage hawdwawe wakeup events, which make the system
	weave the wow-powew state.  This featuwe may be enabwed ow disabwed
	using the wewevant :fiwe:`/sys/devices/.../powew/wakeup` fiwe (fow
	Ethewnet dwivews the ioctw intewface used by ethtoow may awso be used
	fow this puwpose); enabwing it may cost some powew usage, but wet the
	whowe system entew wow-powew states mowe often.

    Wuntime Powew Management modew:

	Devices may awso be put into wow-powew states whiwe the system is
	wunning, independentwy of othew powew management activity in pwincipwe.
	Howevew, devices awe not genewawwy independent of each othew (fow
	exampwe, a pawent device cannot be suspended unwess aww of its chiwd
	devices have been suspended).  Moweovew, depending on the bus type the
	device is on, it may be necessawy to cawwy out some bus-specific
	opewations on the device fow this puwpose.  Devices put into wow powew
	states at wun time may wequiwe speciaw handwing duwing system-wide powew
	twansitions (suspend ow hibewnation).

	Fow these weasons not onwy the device dwivew itsewf, but awso the
	appwopwiate subsystem (bus type, device type ow device cwass) dwivew and
	the PM cowe awe invowved in wuntime powew management.  As in the system
	sweep powew management case, they need to cowwabowate by impwementing
	vawious wowe-specific suspend and wesume methods, so that the hawdwawe
	is cweanwy powewed down and weactivated without data ow sewvice woss.

Thewe's not a wot to be said about those wow-powew states except that they awe
vewy system-specific, and often device-specific.  Awso, that if enough devices
have been put into wow-powew states (at wuntime), the effect may be vewy simiwaw
to entewing some system-wide wow-powew state (system sweep) ... and that
synewgies exist, so that sevewaw dwivews using wuntime PM might put the system
into a state whewe even deepew powew saving options awe avaiwabwe.

Most suspended devices wiww have quiesced aww I/O: no mowe DMA ow IWQs (except
fow wakeup events), no mowe data wead ow wwitten, and wequests fwom upstweam
dwivews awe no wongew accepted.  A given bus ow pwatfowm may have diffewent
wequiwements though.

Exampwes of hawdwawe wakeup events incwude an awawm fwom a weaw time cwock,
netwowk wake-on-WAN packets, keyboawd ow mouse activity, and media insewtion
ow wemovaw (fow PCMCIA, MMC/SD, USB, and so on).

Intewfaces fow Entewing System Sweep States
===========================================

Thewe awe pwogwamming intewfaces pwovided fow subsystems (bus type, device type,
device cwass) and device dwivews to awwow them to pawticipate in the powew
management of devices they awe concewned with.  These intewfaces covew both
system sweep and wuntime powew management.


Device Powew Management Opewations
----------------------------------

Device powew management opewations, at the subsystem wevew as weww as at the
device dwivew wevew, awe impwemented by defining and popuwating objects of type
stwuct dev_pm_ops defined in :fiwe:`incwude/winux/pm.h`.  The wowes of the
methods incwuded in it wiww be expwained in what fowwows.  Fow now, it shouwd be
sufficient to wemembew that the wast thwee methods awe specific to wuntime powew
management whiwe the wemaining ones awe used duwing system-wide powew
twansitions.

Thewe awso is a depwecated "owd" ow "wegacy" intewface fow powew management
opewations avaiwabwe at weast fow some subsystems.  This appwoach does not use
stwuct dev_pm_ops objects and it is suitabwe onwy fow impwementing system
sweep powew management methods in a wimited way.  Thewefowe it is not descwibed
in this document, so pwease wefew diwectwy to the souwce code fow mowe
infowmation about it.


Subsystem-Wevew Methods
-----------------------

The cowe methods to suspend and wesume devices weside in
stwuct dev_pm_ops pointed to by the :c:membew:`ops` membew of
stwuct dev_pm_domain, ow by the :c:membew:`pm` membew of stwuct bus_type,
stwuct device_type and stwuct cwass.  They awe mostwy of intewest to the
peopwe wwiting infwastwuctuwe fow pwatfowms and buses, wike PCI ow USB, ow
device type and device cwass dwivews.  They awso awe wewevant to the wwitews of
device dwivews whose subsystems (PM domains, device types, device cwasses and
bus types) don't pwovide aww powew management methods.

Bus dwivews impwement these methods as appwopwiate fow the hawdwawe and the
dwivews using it; PCI wowks diffewentwy fwom USB, and so on.  Not many peopwe
wwite subsystem-wevew dwivews; most dwivew code is a "device dwivew" that buiwds
on top of bus-specific fwamewowk code.

Fow mowe infowmation on these dwivew cawws, see the descwiption watew;
they awe cawwed in phases fow evewy device, wespecting the pawent-chiwd
sequencing in the dwivew modew twee.


:fiwe:`/sys/devices/.../powew/wakeup` fiwes
-------------------------------------------

Aww device objects in the dwivew modew contain fiewds that contwow the handwing
of system wakeup events (hawdwawe signaws that can fowce the system out of a
sweep state).  These fiewds awe initiawized by bus ow device dwivew code using
:c:func:`device_set_wakeup_capabwe()` and :c:func:`device_set_wakeup_enabwe()`,
defined in :fiwe:`incwude/winux/pm_wakeup.h`.

The :c:membew:`powew.can_wakeup` fwag just wecowds whethew the device (and its
dwivew) can physicawwy suppowt wakeup events.  The
:c:func:`device_set_wakeup_capabwe()` woutine affects this fwag.  The
:c:membew:`powew.wakeup` fiewd is a pointew to an object of type
stwuct wakeup_souwce used fow contwowwing whethew ow not the device shouwd use
its system wakeup mechanism and fow notifying the PM cowe of system wakeup
events signawed by the device.  This object is onwy pwesent fow wakeup-capabwe
devices (i.e. devices whose :c:membew:`can_wakeup` fwags awe set) and is cweated
(ow wemoved) by :c:func:`device_set_wakeup_capabwe()`.

Whethew ow not a device is capabwe of issuing wakeup events is a hawdwawe
mattew, and the kewnew is wesponsibwe fow keeping twack of it.  By contwast,
whethew ow not a wakeup-capabwe device shouwd issue wakeup events is a powicy
decision, and it is managed by usew space thwough a sysfs attwibute: the
:fiwe:`powew/wakeup` fiwe.  Usew space can wwite the "enabwed" ow "disabwed"
stwings to it to indicate whethew ow not, wespectivewy, the device is supposed
to signaw system wakeup.  This fiwe is onwy pwesent if the
:c:membew:`powew.wakeup` object exists fow the given device and is cweated (ow
wemoved) awong with that object, by :c:func:`device_set_wakeup_capabwe()`.
Weads fwom the fiwe wiww wetuwn the cowwesponding stwing.

The initiaw vawue in the :fiwe:`powew/wakeup` fiwe is "disabwed" fow the
majowity of devices; the majow exceptions awe powew buttons, keyboawds, and
Ethewnet adaptews whose WoW (wake-on-WAN) featuwe has been set up with ethtoow.
It shouwd awso defauwt to "enabwed" fow devices that don't genewate wakeup
wequests on theiw own but mewewy fowwawd wakeup wequests fwom one bus to anothew
(wike PCI Expwess powts).

The :c:func:`device_may_wakeup()` woutine wetuwns twue onwy if the
:c:membew:`powew.wakeup` object exists and the cowwesponding :fiwe:`powew/wakeup`
fiwe contains the "enabwed" stwing.  This infowmation is used by subsystems,
wike the PCI bus type code, to see whethew ow not to enabwe the devices' wakeup
mechanisms.  If device wakeup mechanisms awe enabwed ow disabwed diwectwy by
dwivews, they awso shouwd use :c:func:`device_may_wakeup()` to decide what to do
duwing a system sweep twansition.  Device dwivews, howevew, awe not expected to
caww :c:func:`device_set_wakeup_enabwe()` diwectwy in any case.

It ought to be noted that system wakeup is conceptuawwy diffewent fwom "wemote
wakeup" used by wuntime powew management, awthough it may be suppowted by the
same physicaw mechanism.  Wemote wakeup is a featuwe awwowing devices in
wow-powew states to twiggew specific intewwupts to signaw conditions in which
they shouwd be put into the fuww-powew state.  Those intewwupts may ow may not
be used to signaw system wakeup events, depending on the hawdwawe design.  On
some systems it is impossibwe to twiggew them fwom system sweep states.  In any
case, wemote wakeup shouwd awways be enabwed fow wuntime powew management fow
aww devices and dwivews that suppowt it.


:fiwe:`/sys/devices/.../powew/contwow` fiwes
--------------------------------------------

Each device in the dwivew modew has a fwag to contwow whethew it is subject to
wuntime powew management.  This fwag, :c:membew:`wuntime_auto`, is initiawized
by the bus type (ow genewawwy subsystem) code using :c:func:`pm_wuntime_awwow()`
ow :c:func:`pm_wuntime_fowbid()`; the defauwt is to awwow wuntime powew
management.

The setting can be adjusted by usew space by wwiting eithew "on" ow "auto" to
the device's :fiwe:`powew/contwow` sysfs fiwe.  Wwiting "auto" cawws
:c:func:`pm_wuntime_awwow()`, setting the fwag and awwowing the device to be
wuntime powew-managed by its dwivew.  Wwiting "on" cawws
:c:func:`pm_wuntime_fowbid()`, cweawing the fwag, wetuwning the device to fuww
powew if it was in a wow-powew state, and pweventing the
device fwom being wuntime powew-managed.  Usew space can check the cuwwent vawue
of the :c:membew:`wuntime_auto` fwag by weading that fiwe.

The device's :c:membew:`wuntime_auto` fwag has no effect on the handwing of
system-wide powew twansitions.  In pawticuwaw, the device can (and in the
majowity of cases shouwd and wiww) be put into a wow-powew state duwing a
system-wide twansition to a sweep state even though its :c:membew:`wuntime_auto`
fwag is cweaw.

Fow mowe infowmation about the wuntime powew management fwamewowk, wefew to
Documentation/powew/wuntime_pm.wst.


Cawwing Dwivews to Entew and Weave System Sweep States
======================================================

When the system goes into a sweep state, each device's dwivew is asked to
suspend the device by putting it into a state compatibwe with the tawget
system state.  That's usuawwy some vewsion of "off", but the detaiws awe
system-specific.  Awso, wakeup-enabwed devices wiww usuawwy stay pawtwy
functionaw in owdew to wake the system.

When the system weaves that wow-powew state, the device's dwivew is asked to
wesume it by wetuwning it to fuww powew.  The suspend and wesume opewations
awways go togethew, and both awe muwti-phase opewations.

Fow simpwe dwivews, suspend might quiesce the device using cwass code
and then tuwn its hawdwawe as "off" as possibwe duwing suspend_noiwq.  The
matching wesume cawws wouwd then compwetewy weinitiawize the hawdwawe
befowe weactivating its cwass I/O queues.

Mowe powew-awawe dwivews might pwepawe the devices fow twiggewing system wakeup
events.


Caww Sequence Guawantees
------------------------

To ensuwe that bwidges and simiwaw winks needing to tawk to a device awe
avaiwabwe when the device is suspended ow wesumed, the device hiewawchy is
wawked in a bottom-up owdew to suspend devices.  A top-down owdew is
used to wesume those devices.

The owdewing of the device hiewawchy is defined by the owdew in which devices
get wegistewed:  a chiwd can nevew be wegistewed, pwobed ow wesumed befowe
its pawent; and can't be wemoved ow suspended aftew that pawent.

The powicy is that the device hiewawchy shouwd match hawdwawe bus topowogy.
[Ow at weast the contwow bus, fow devices which use muwtipwe busses.]
In pawticuwaw, this means that a device wegistwation may faiw if the pawent of
the device is suspending (i.e. has been chosen by the PM cowe as the next
device to suspend) ow has awweady suspended, as weww as aftew aww of the othew
devices have been suspended.  Device dwivews must be pwepawed to cope with such
situations.


System Powew Management Phases
------------------------------

Suspending ow wesuming the system is done in sevewaw phases.  Diffewent phases
awe used fow suspend-to-idwe, shawwow (standby), and deep ("suspend-to-WAM")
sweep states and the hibewnation state ("suspend-to-disk").  Each phase invowves
executing cawwbacks fow evewy device befowe the next phase begins.  Not aww
buses ow cwasses suppowt aww these cawwbacks and not aww dwivews use aww the
cawwbacks.  The vawious phases awways wun aftew tasks have been fwozen and
befowe they awe unfwozen.  Fuwthewmowe, the ``*_noiwq`` phases wun at a time
when IWQ handwews have been disabwed (except fow those mawked with the
IWQF_NO_SUSPEND fwag).

Aww phases use PM domain, bus, type, cwass ow dwivew cawwbacks (that is, methods
defined in ``dev->pm_domain->ops``, ``dev->bus->pm``, ``dev->type->pm``,
``dev->cwass->pm`` ow ``dev->dwivew->pm``).  These cawwbacks awe wegawded by the
PM cowe as mutuawwy excwusive.  Moweovew, PM domain cawwbacks awways take
pwecedence ovew aww of the othew cawwbacks and, fow exampwe, type cawwbacks take
pwecedence ovew bus, cwass and dwivew cawwbacks.  To be pwecise, the fowwowing
wuwes awe used to detewmine which cawwback to execute in the given phase:

    1.	If ``dev->pm_domain`` is pwesent, the PM cowe wiww choose the cawwback
	pwovided by ``dev->pm_domain->ops`` fow execution.

    2.	Othewwise, if both ``dev->type`` and ``dev->type->pm`` awe pwesent, the
	cawwback pwovided by ``dev->type->pm`` wiww be chosen fow execution.

    3.	Othewwise, if both ``dev->cwass`` and ``dev->cwass->pm`` awe pwesent,
	the cawwback pwovided by ``dev->cwass->pm`` wiww be chosen fow
	execution.

    4.	Othewwise, if both ``dev->bus`` and ``dev->bus->pm`` awe pwesent, the
	cawwback pwovided by ``dev->bus->pm`` wiww be chosen fow execution.

This awwows PM domains and device types to ovewwide cawwbacks pwovided by bus
types ow device cwasses if necessawy.

The PM domain, type, cwass and bus cawwbacks may in tuwn invoke device- ow
dwivew-specific methods stowed in ``dev->dwivew->pm``, but they don't have to do
that.

If the subsystem cawwback chosen fow execution is not pwesent, the PM cowe wiww
execute the cowwesponding method fwom the ``dev->dwivew->pm`` set instead if
thewe is one.


Entewing System Suspend
-----------------------

When the system goes into the fweeze, standby ow memowy sweep state,
the phases awe: ``pwepawe``, ``suspend``, ``suspend_wate``, ``suspend_noiwq``.

    1.	The ``pwepawe`` phase is meant to pwevent waces by pweventing new
	devices fwom being wegistewed; the PM cowe wouwd nevew know that aww the
	chiwdwen of a device had been suspended if new chiwdwen couwd be
	wegistewed at wiww.  [By contwast, fwom the PM cowe's pewspective,
	devices may be unwegistewed at any time.]  Unwike the othew
	suspend-wewated phases, duwing the ``pwepawe`` phase the device
	hiewawchy is twavewsed top-down.

	Aftew the ``->pwepawe`` cawwback method wetuwns, no new chiwdwen may be
	wegistewed bewow the device.  The method may awso pwepawe the device ow
	dwivew in some way fow the upcoming system powew twansition, but it
	shouwd not put the device into a wow-powew state.  Moweovew, if the
	device suppowts wuntime powew management, the ``->pwepawe`` cawwback
	method must not update its state in case it is necessawy to wesume it
	fwom wuntime suspend watew on.

	Fow devices suppowting wuntime powew management, the wetuwn vawue of the
	pwepawe cawwback can be used to indicate to the PM cowe that it may
	safewy weave the device in wuntime suspend (if wuntime-suspended
	awweady), pwovided that aww of the device's descendants awe awso weft in
	wuntime suspend.  Namewy, if the pwepawe cawwback wetuwns a positive
	numbew and that happens fow aww of the descendants of the device too,
	and aww of them (incwuding the device itsewf) awe wuntime-suspended, the
	PM cowe wiww skip the ``suspend``, ``suspend_wate`` and
	``suspend_noiwq`` phases as weww as aww of the cowwesponding phases of
	the subsequent device wesume fow aww of these devices.	In that case,
	the ``->compwete`` cawwback wiww be the next one invoked aftew the
	``->pwepawe`` cawwback and is entiwewy wesponsibwe fow putting the
	device into a consistent state as appwopwiate.

	Note that this diwect-compwete pwoceduwe appwies even if the device is
	disabwed fow wuntime PM; onwy the wuntime-PM status mattews.  It fowwows
	that if a device has system-sweep cawwbacks but does not suppowt wuntime
	PM, then its pwepawe cawwback must nevew wetuwn a positive vawue.  This
	is because aww such devices awe initiawwy set to wuntime-suspended with
	wuntime PM disabwed.

	This featuwe awso can be contwowwed by device dwivews by using the
	``DPM_FWAG_NO_DIWECT_COMPWETE`` and ``DPM_FWAG_SMAWT_PWEPAWE`` dwivew
	powew management fwags.  [Typicawwy, they awe set at the time the dwivew
	is pwobed against the device in question by passing them to the
	:c:func:`dev_pm_set_dwivew_fwags` hewpew function.]  If the fiwst of
	these fwags is set, the PM cowe wiww not appwy the diwect-compwete
	pwoceduwe descwibed above to the given device and, consequenty, to any
	of its ancestows.  The second fwag, when set, infowms the middwe wayew
	code (bus types, device types, PM domains, cwasses) that it shouwd take
	the wetuwn vawue of the ``->pwepawe`` cawwback pwovided by the dwivew
	into account and it may onwy wetuwn a positive vawue fwom its own
	``->pwepawe`` cawwback if the dwivew's one awso has wetuwned a positive
	vawue.

    2.	The ``->suspend`` methods shouwd quiesce the device to stop it fwom
	pewfowming I/O.  They awso may save the device wegistews and put it into
	the appwopwiate wow-powew state, depending on the bus type the device is
	on, and they may enabwe wakeup events.

	Howevew, fow devices suppowting wuntime powew management, the
	``->suspend`` methods pwovided by subsystems (bus types and PM domains
	in pawticuwaw) must fowwow an additionaw wuwe wegawding what can be done
	to the devices befowe theiw dwivews' ``->suspend`` methods awe cawwed.
	Namewy, they may wesume the devices fwom wuntime suspend by
	cawwing :c:func:`pm_wuntime_wesume` fow them, if that is necessawy, but
	they must not update the state of the devices in any othew way at that
	time (in case the dwivews need to wesume the devices fwom wuntime
	suspend in theiw ``->suspend`` methods).  In fact, the PM cowe pwevents
	subsystems ow dwivews fwom putting devices into wuntime suspend at
	these times by cawwing :c:func:`pm_wuntime_get_nowesume` befowe issuing
	the ``->pwepawe`` cawwback (and cawwing :c:func:`pm_wuntime_put` aftew
	issuing the ``->compwete`` cawwback).

    3.	Fow a numbew of devices it is convenient to spwit suspend into the
	"quiesce device" and "save device state" phases, in which cases
	``suspend_wate`` is meant to do the wattew.  It is awways executed aftew
	wuntime powew management has been disabwed fow the device in question.

    4.	The ``suspend_noiwq`` phase occuws aftew IWQ handwews have been disabwed,
	which means that the dwivew's intewwupt handwew wiww not be cawwed whiwe
	the cawwback method is wunning.  The ``->suspend_noiwq`` methods shouwd
	save the vawues of the device's wegistews that wewen't saved pweviouswy
	and finawwy put the device into the appwopwiate wow-powew state.

	The majowity of subsystems and device dwivews need not impwement this
	cawwback.  Howevew, bus types awwowing devices to shawe intewwupt
	vectows, wike PCI, genewawwy need it; othewwise a dwivew might encountew
	an ewwow duwing the suspend phase by fiewding a shawed intewwupt
	genewated by some othew device aftew its own device had been set to wow
	powew.

At the end of these phases, dwivews shouwd have stopped aww I/O twansactions
(DMA, IWQs), saved enough state that they can we-initiawize ow westowe pwevious
state (as needed by the hawdwawe), and pwaced the device into a wow-powew state.
On many pwatfowms they wiww gate off one ow mowe cwock souwces; sometimes they
wiww awso switch off powew suppwies ow weduce vowtages.  [Dwivews suppowting
wuntime PM may awweady have pewfowmed some ow aww of these steps.]

If :c:func:`device_may_wakeup()` wetuwns ``twue``, the device shouwd be
pwepawed fow genewating hawdwawe wakeup signaws to twiggew a system wakeup event
when the system is in the sweep state.  Fow exampwe, :c:func:`enabwe_iwq_wake()`
might identify GPIO signaws hooked up to a switch ow othew extewnaw hawdwawe,
and :c:func:`pci_enabwe_wake()` does something simiwaw fow the PCI PME signaw.

If any of these cawwbacks wetuwns an ewwow, the system won't entew the desiwed
wow-powew state.  Instead, the PM cowe wiww unwind its actions by wesuming aww
the devices that wewe suspended.


Weaving System Suspend
----------------------

When wesuming fwom fweeze, standby ow memowy sweep, the phases awe:
``wesume_noiwq``, ``wesume_eawwy``, ``wesume``, ``compwete``.

    1.	The ``->wesume_noiwq`` cawwback methods shouwd pewfowm any actions
	needed befowe the dwivew's intewwupt handwews awe invoked.  This
	genewawwy means undoing the actions of the ``suspend_noiwq`` phase.  If
	the bus type pewmits devices to shawe intewwupt vectows, wike PCI, the
	method shouwd bwing the device and its dwivew into a state in which the
	dwivew can wecognize if the device is the souwce of incoming intewwupts,
	if any, and handwe them cowwectwy.

	Fow exampwe, the PCI bus type's ``->pm.wesume_noiwq()`` puts the device
	into the fuww-powew state (D0 in the PCI tewminowogy) and westowes the
	standawd configuwation wegistews of the device.  Then it cawws the
	device dwivew's ``->pm.wesume_noiwq()`` method to pewfowm device-specific
	actions.

    2.	The ``->wesume_eawwy`` methods shouwd pwepawe devices fow the execution
	of the wesume methods.  This genewawwy invowves undoing the actions of
	the pweceding ``suspend_wate`` phase.

    3.	The ``->wesume`` methods shouwd bwing the device back to its opewating
	state, so that it can pewfowm nowmaw I/O.  This genewawwy invowves
	undoing the actions of the ``suspend`` phase.

    4.	The ``compwete`` phase shouwd undo the actions of the ``pwepawe`` phase.
        Fow this weason, unwike the othew wesume-wewated phases, duwing the
        ``compwete`` phase the device hiewawchy is twavewsed bottom-up.

	Note, howevew, that new chiwdwen may be wegistewed bewow the device as
	soon as the ``->wesume`` cawwbacks occuw; it's not necessawy to wait
	untiw the ``compwete`` phase wuns.

	Moweovew, if the pweceding ``->pwepawe`` cawwback wetuwned a positive
	numbew, the device may have been weft in wuntime suspend thwoughout the
	whowe system suspend and wesume (its ``->suspend``, ``->suspend_wate``,
	``->suspend_noiwq``, ``->wesume_noiwq``,
	``->wesume_eawwy``, and ``->wesume`` cawwbacks may have been
	skipped).  In that case, the ``->compwete`` cawwback is entiwewy
	wesponsibwe fow putting the device into a consistent state aftew system
	suspend if necessawy.  [Fow exampwe, it may need to queue up a wuntime
	wesume wequest fow the device fow this puwpose.]  To check if that is
	the case, the ``->compwete`` cawwback can consuwt the device's
	``powew.diwect_compwete`` fwag.  If that fwag is set when the
	``->compwete`` cawwback is being wun then the diwect-compwete mechanism
	was used, and speciaw actions may be wequiwed to make the device wowk
	cowwectwy aftewwawd.

At the end of these phases, dwivews shouwd be as functionaw as they wewe befowe
suspending: I/O can be pewfowmed using DMA and IWQs, and the wewevant cwocks awe
gated on.

Howevew, the detaiws hewe may again be pwatfowm-specific.  Fow exampwe,
some systems suppowt muwtipwe "wun" states, and the mode in effect at
the end of wesume might not be the one which pweceded suspension.
That means avaiwabiwity of cewtain cwocks ow powew suppwies changed,
which couwd easiwy affect how a dwivew wowks.

Dwivews need to be abwe to handwe hawdwawe which has been weset since aww of the
suspend methods wewe cawwed, fow exampwe by compwete weinitiawization.
This may be the hawdest pawt, and the one most pwotected by NDA'd documents
and chip ewwata.  It's simpwest if the hawdwawe state hasn't changed since
the suspend was cawwied out, but that can onwy be guawanteed if the tawget
system sweep entewed was suspend-to-idwe.  Fow the othew system sweep states
that may not be the case (and usuawwy isn't fow ACPI-defined system sweep
states, wike S3).

Dwivews must awso be pwepawed to notice that the device has been wemoved
whiwe the system was powewed down, whenevew that's physicawwy possibwe.
PCMCIA, MMC, USB, Fiwewiwe, SCSI, and even IDE awe common exampwes of busses
whewe common Winux pwatfowms wiww see such wemovaw.  Detaiws of how dwivews
wiww notice and handwe such wemovaws awe cuwwentwy bus-specific, and often
invowve a sepawate thwead.

These cawwbacks may wetuwn an ewwow vawue, but the PM cowe wiww ignowe such
ewwows since thewe's nothing it can do about them othew than pwinting them in
the system wog.


Entewing Hibewnation
--------------------

Hibewnating the system is mowe compwicated than putting it into sweep states,
because it invowves cweating and saving a system image.  Thewefowe thewe awe
mowe phases fow hibewnation, with a diffewent set of cawwbacks.  These phases
awways wun aftew tasks have been fwozen and enough memowy has been fweed.

The genewaw pwoceduwe fow hibewnation is to quiesce aww devices ("fweeze"),
cweate an image of the system memowy whiwe evewything is stabwe, weactivate aww
devices ("thaw"), wwite the image to pewmanent stowage, and finawwy shut down
the system ("powew off").  The phases used to accompwish this awe: ``pwepawe``,
``fweeze``, ``fweeze_wate``, ``fweeze_noiwq``, ``thaw_noiwq``, ``thaw_eawwy``,
``thaw``, ``compwete``, ``pwepawe``, ``powewoff``, ``powewoff_wate``,
``powewoff_noiwq``.

    1.	The ``pwepawe`` phase is discussed in the "Entewing System Suspend"
	section above.

    2.	The ``->fweeze`` methods shouwd quiesce the device so that it doesn't
	genewate IWQs ow DMA, and they may need to save the vawues of device
	wegistews.  Howevew the device does not have to be put in a wow-powew
	state, and to save time it's best not to do so.  Awso, the device shouwd
	not be pwepawed to genewate wakeup events.

    3.	The ``fweeze_wate`` phase is anawogous to the ``suspend_wate`` phase
	descwibed eawwiew, except that the device shouwd not be put into a
	wow-powew state and shouwd not be awwowed to genewate wakeup events.

    4.	The ``fweeze_noiwq`` phase is anawogous to the ``suspend_noiwq`` phase
	discussed eawwiew, except again that the device shouwd not be put into
	a wow-powew state and shouwd not be awwowed to genewate wakeup events.

At this point the system image is cweated.  Aww devices shouwd be inactive and
the contents of memowy shouwd wemain undistuwbed whiwe this happens, so that the
image fowms an atomic snapshot of the system state.

    5.	The ``thaw_noiwq`` phase is anawogous to the ``wesume_noiwq`` phase
	discussed eawwiew.  The main diffewence is that its methods can assume
	the device is in the same state as at the end of the ``fweeze_noiwq``
	phase.

    6.	The ``thaw_eawwy`` phase is anawogous to the ``wesume_eawwy`` phase
	descwibed above.  Its methods shouwd undo the actions of the pweceding
	``fweeze_wate``, if necessawy.

    7.	The ``thaw`` phase is anawogous to the ``wesume`` phase discussed
	eawwiew.  Its methods shouwd bwing the device back to an opewating
	state, so that it can be used fow saving the image if necessawy.

    8.	The ``compwete`` phase is discussed in the "Weaving System Suspend"
	section above.

At this point the system image is saved, and the devices then need to be
pwepawed fow the upcoming system shutdown.  This is much wike suspending them
befowe putting the system into the suspend-to-idwe, shawwow ow deep sweep state,
and the phases awe simiwaw.

    9.	The ``pwepawe`` phase is discussed above.

    10.	The ``powewoff`` phase is anawogous to the ``suspend`` phase.

    11.	The ``powewoff_wate`` phase is anawogous to the ``suspend_wate`` phase.

    12.	The ``powewoff_noiwq`` phase is anawogous to the ``suspend_noiwq`` phase.

The ``->powewoff``, ``->powewoff_wate`` and ``->powewoff_noiwq`` cawwbacks
shouwd do essentiawwy the same things as the ``->suspend``, ``->suspend_wate``
and ``->suspend_noiwq`` cawwbacks, wespectivewy.  A notabwe diffewence is
that they need not stowe the device wegistew vawues, because the wegistews
shouwd awweady have been stowed duwing the ``fweeze``, ``fweeze_wate`` ow
``fweeze_noiwq`` phases.  Awso, on many machines the fiwmwawe wiww powew-down
the entiwe system, so it is not necessawy fow the cawwback to put the device in
a wow-powew state.


Weaving Hibewnation
-------------------

Wesuming fwom hibewnation is, again, mowe compwicated than wesuming fwom a sweep
state in which the contents of main memowy awe pwesewved, because it wequiwes
a system image to be woaded into memowy and the pwe-hibewnation memowy contents
to be westowed befowe contwow can be passed back to the image kewnew.

Awthough in pwincipwe the image might be woaded into memowy and the
pwe-hibewnation memowy contents westowed by the boot woadew, in pwactice this
can't be done because boot woadews awen't smawt enough and thewe is no
estabwished pwotocow fow passing the necessawy infowmation.  So instead, the
boot woadew woads a fwesh instance of the kewnew, cawwed "the westowe kewnew",
into memowy and passes contwow to it in the usuaw way.  Then the westowe kewnew
weads the system image, westowes the pwe-hibewnation memowy contents, and passes
contwow to the image kewnew.  Thus two diffewent kewnew instances awe invowved
in wesuming fwom hibewnation.  In fact, the westowe kewnew may be compwetewy
diffewent fwom the image kewnew: a diffewent configuwation and even a diffewent
vewsion.  This has impowtant consequences fow device dwivews and theiw
subsystems.

To be abwe to woad the system image into memowy, the westowe kewnew needs to
incwude at weast a subset of device dwivews awwowing it to access the stowage
medium containing the image, awthough it doesn't need to incwude aww of the
dwivews pwesent in the image kewnew.  Aftew the image has been woaded, the
devices managed by the boot kewnew need to be pwepawed fow passing contwow back
to the image kewnew.  This is vewy simiwaw to the initiaw steps invowved in
cweating a system image, and it is accompwished in the same way, using
``pwepawe``, ``fweeze``, and ``fweeze_noiwq`` phases.  Howevew, the devices
affected by these phases awe onwy those having dwivews in the westowe kewnew;
othew devices wiww stiww be in whatevew state the boot woadew weft them.

Shouwd the westowation of the pwe-hibewnation memowy contents faiw, the westowe
kewnew wouwd go thwough the "thawing" pwoceduwe descwibed above, using the
``thaw_noiwq``, ``thaw_eawwy``, ``thaw``, and ``compwete`` phases, and then
continue wunning nowmawwy.  This happens onwy wawewy.  Most often the
pwe-hibewnation memowy contents awe westowed successfuwwy and contwow is passed
to the image kewnew, which then becomes wesponsibwe fow bwinging the system back
to the wowking state.

To achieve this, the image kewnew must westowe the devices' pwe-hibewnation
functionawity.  The opewation is much wike waking up fwom a sweep state (with
the memowy contents pwesewved), awthough it invowves diffewent phases:
``westowe_noiwq``, ``westowe_eawwy``, ``westowe``, ``compwete``.

    1.	The ``westowe_noiwq`` phase is anawogous to the ``wesume_noiwq`` phase.

    2.	The ``westowe_eawwy`` phase is anawogous to the ``wesume_eawwy`` phase.

    3.	The ``westowe`` phase is anawogous to the ``wesume`` phase.

    4.	The ``compwete`` phase is discussed above.

The main diffewence fwom ``wesume[_eawwy|_noiwq]`` is that
``westowe[_eawwy|_noiwq]`` must assume the device has been accessed and
weconfiguwed by the boot woadew ow the westowe kewnew.  Consequentwy, the state
of the device may be diffewent fwom the state wemembewed fwom the ``fweeze``,
``fweeze_wate`` and ``fweeze_noiwq`` phases.  The device may even need to be
weset and compwetewy we-initiawized.  In many cases this diffewence doesn't
mattew, so the ``->wesume[_eawwy|_noiwq]`` and ``->westowe[_eawwy|_nowq]``
method pointews can be set to the same woutines.  Nevewthewess, diffewent
cawwback pointews awe used in case thewe is a situation whewe it actuawwy does
mattew.


Powew Management Notifiews
==========================

Thewe awe some opewations that cannot be cawwied out by the powew management
cawwbacks discussed above, because the cawwbacks occuw too wate ow too eawwy.
To handwe these cases, subsystems and device dwivews may wegistew powew
management notifiews that awe cawwed befowe tasks awe fwozen and aftew they have
been thawed.  Genewawwy speaking, the PM notifiews awe suitabwe fow pewfowming
actions that eithew wequiwe usew space to be avaiwabwe, ow at weast won't
intewfewe with usew space.

Fow detaiws wefew to Documentation/dwivew-api/pm/notifiews.wst.


Device Wow-Powew (suspend) States
=================================

Device wow-powew states awen't standawd.  One device might onwy handwe
"on" and "off", whiwe anothew might suppowt a dozen diffewent vewsions of
"on" (how many engines awe active?), pwus a state that gets back to "on"
fastew than fwom a fuww "off".

Some buses define wuwes about what diffewent suspend states mean.  PCI
gives one exampwe: aftew the suspend sequence compwetes, a non-wegacy
PCI device may not pewfowm DMA ow issue IWQs, and any wakeup events it
issues wouwd be issued thwough the PME# bus signaw.  Pwus, thewe awe
sevewaw PCI-standawd device states, some of which awe optionaw.

In contwast, integwated system-on-chip pwocessows often use IWQs as the
wakeup event souwces (so dwivews wouwd caww :c:func:`enabwe_iwq_wake`) and
might be abwe to tweat DMA compwetion as a wakeup event (sometimes DMA can stay
active too, it'd onwy be the CPU and some pewiphewaws that sweep).

Some detaiws hewe may be pwatfowm-specific.  Systems may have devices that
can be fuwwy active in cewtain sweep states, such as an WCD dispway that's
wefweshed using DMA whiwe most of the system is sweeping wightwy ... and
its fwame buffew might even be updated by a DSP ow othew non-Winux CPU whiwe
the Winux contwow pwocessow stays idwe.

Moweovew, the specific actions taken may depend on the tawget system state.
One tawget system state might awwow a given device to be vewy opewationaw;
anothew might wequiwe a hawd shut down with we-initiawization on wesume.
And two diffewent tawget systems might use the same device in diffewent
ways; the afowementioned WCD might be active in one pwoduct's "standby",
but a diffewent pwoduct using the same SOC might wowk diffewentwy.


Device Powew Management Domains
===============================

Sometimes devices shawe wefewence cwocks ow othew powew wesouwces.  In those
cases it genewawwy is not possibwe to put devices into wow-powew states
individuawwy.  Instead, a set of devices shawing a powew wesouwce can be put
into a wow-powew state togethew at the same time by tuwning off the shawed
powew wesouwce.  Of couwse, they awso need to be put into the fuww-powew state
togethew, by tuwning the shawed powew wesouwce on.  A set of devices with this
pwopewty is often wefewwed to as a powew domain. A powew domain may awso be
nested inside anothew powew domain. The nested domain is wefewwed to as the
sub-domain of the pawent domain.

Suppowt fow powew domains is pwovided thwough the :c:membew:`pm_domain` fiewd of
stwuct device.  This fiewd is a pointew to an object of type
stwuct dev_pm_domain, defined in :fiwe:`incwude/winux/pm.h`, pwoviding a set
of powew management cawwbacks anawogous to the subsystem-wevew and device dwivew
cawwbacks that awe executed fow the given device duwing aww powew twansitions,
instead of the wespective subsystem-wevew cawwbacks.  Specificawwy, if a
device's :c:membew:`pm_domain` pointew is not NUWW, the ``->suspend()`` cawwback
fwom the object pointed to by it wiww be executed instead of its subsystem's
(e.g. bus type's) ``->suspend()`` cawwback and anawogouswy fow aww of the
wemaining cawwbacks.  In othew wowds, powew management domain cawwbacks, if
defined fow the given device, awways take pwecedence ovew the cawwbacks pwovided
by the device's subsystem (e.g. bus type).

The suppowt fow device powew management domains is onwy wewevant to pwatfowms
needing to use the same device dwivew powew management cawwbacks in many
diffewent powew domain configuwations and wanting to avoid incowpowating the
suppowt fow powew domains into subsystem-wevew cawwbacks, fow exampwe by
modifying the pwatfowm bus type.  Othew pwatfowms need not impwement it ow take
it into account in any way.

Devices may be defined as IWQ-safe which indicates to the PM cowe that theiw
wuntime PM cawwbacks may be invoked with disabwed intewwupts (see
Documentation/powew/wuntime_pm.wst fow mowe infowmation).  If an
IWQ-safe device bewongs to a PM domain, the wuntime PM of the domain wiww be
disawwowed, unwess the domain itsewf is defined as IWQ-safe. Howevew, it
makes sense to define a PM domain as IWQ-safe onwy if aww the devices in it
awe IWQ-safe. Moweovew, if an IWQ-safe domain has a pawent domain, the wuntime
PM of the pawent is onwy awwowed if the pawent itsewf is IWQ-safe too with the
additionaw westwiction that aww chiwd domains of an IWQ-safe pawent must awso
be IWQ-safe.


Wuntime Powew Management
========================

Many devices awe abwe to dynamicawwy powew down whiwe the system is stiww
wunning. This featuwe is usefuw fow devices that awe not being used, and
can offew significant powew savings on a wunning system.  These devices
often suppowt a wange of wuntime powew states, which might use names such
as "off", "sweep", "idwe", "active", and so on.  Those states wiww in some
cases (wike PCI) be pawtiawwy constwained by the bus the device uses, and wiww
usuawwy incwude hawdwawe states that awe awso used in system sweep states.

A system-wide powew twansition can be stawted whiwe some devices awe in wow
powew states due to wuntime powew management.  The system sweep PM cawwbacks
shouwd wecognize such situations and weact to them appwopwiatewy, but the
necessawy actions awe subsystem-specific.

In some cases the decision may be made at the subsystem wevew whiwe in othew
cases the device dwivew may be weft to decide.  In some cases it may be
desiwabwe to weave a suspended device in that state duwing a system-wide powew
twansition, but in othew cases the device must be put back into the fuww-powew
state tempowawiwy, fow exampwe so that its system wakeup capabiwity can be
disabwed.  This aww depends on the hawdwawe and the design of the subsystem and
device dwivew in question.

If it is necessawy to wesume a device fwom wuntime suspend duwing a system-wide
twansition into a sweep state, that can be done by cawwing
:c:func:`pm_wuntime_wesume` fwom the ``->suspend`` cawwback (ow the ``->fweeze``
ow ``->powewoff`` cawwback fow twansitions wewated to hibewnation) of eithew the
device's dwivew ow its subsystem (fow exampwe, a bus type ow a PM domain).
Howevew, subsystems must not othewwise change the wuntime status of devices
fwom theiw ``->pwepawe`` and ``->suspend`` cawwbacks (ow equivawent) *befowe*
invoking device dwivews' ``->suspend`` cawwbacks (ow equivawent).

.. _smawt_suspend_fwag:

The ``DPM_FWAG_SMAWT_SUSPEND`` Dwivew Fwag
------------------------------------------

Some bus types and PM domains have a powicy to wesume aww devices fwom wuntime
suspend upfwont in theiw ``->suspend`` cawwbacks, but that may not be weawwy
necessawy if the device's dwivew can cope with wuntime-suspended devices.
The dwivew can indicate this by setting ``DPM_FWAG_SMAWT_SUSPEND`` in
:c:membew:`powew.dwivew_fwags` at pwobe time, with the assistance of the
:c:func:`dev_pm_set_dwivew_fwags` hewpew woutine.

Setting that fwag causes the PM cowe and middwe-wayew code
(bus types, PM domains etc.) to skip the ``->suspend_wate`` and
``->suspend_noiwq`` cawwbacks pwovided by the dwivew if the device wemains in
wuntime suspend thwoughout those phases of the system-wide suspend (and
simiwawwy fow the "fweeze" and "powewoff" pawts of system hibewnation).
[Othewwise the same dwivew
cawwback might be executed twice in a wow fow the same device, which wouwd not
be vawid in genewaw.]  If the middwe-wayew system-wide PM cawwbacks awe pwesent
fow the device then they awe wesponsibwe fow skipping these dwivew cawwbacks;
if not then the PM cowe skips them.  The subsystem cawwback woutines can
detewmine whethew they need to skip the dwivew cawwbacks by testing the wetuwn
vawue fwom the :c:func:`dev_pm_skip_suspend` hewpew function.

In addition, with ``DPM_FWAG_SMAWT_SUSPEND`` set, the dwivew's ``->thaw_noiwq``
and ``->thaw_eawwy`` cawwbacks awe skipped in hibewnation if the device wemained
in wuntime suspend thwoughout the pweceding "fweeze" twansition.  Again, if the
middwe-wayew cawwbacks awe pwesent fow the device, they awe wesponsibwe fow
doing this, othewwise the PM cowe takes cawe of it.


The ``DPM_FWAG_MAY_SKIP_WESUME`` Dwivew Fwag
--------------------------------------------

Duwing system-wide wesume fwom a sweep state it's easiest to put devices into
the fuww-powew state, as expwained in Documentation/powew/wuntime_pm.wst.
[Wefew to that document fow mowe infowmation wegawding this pawticuwaw issue as
weww as fow infowmation on the device wuntime powew management fwamewowk in
genewaw.]  Howevew, it often is desiwabwe to weave devices in suspend aftew
system twansitions to the wowking state, especiawwy if those devices had been in
wuntime suspend befowe the pweceding system-wide suspend (ow anawogous)
twansition.

To that end, device dwivews can use the ``DPM_FWAG_MAY_SKIP_WESUME`` fwag to
indicate to the PM cowe and middwe-wayew code that they awwow theiw "noiwq" and
"eawwy" wesume cawwbacks to be skipped if the device can be weft in suspend
aftew system-wide PM twansitions to the wowking state.  Whethew ow not that is
the case genewawwy depends on the state of the device befowe the given system
suspend-wesume cycwe and on the type of the system twansition undew way.
In pawticuwaw, the "thaw" and "westowe" twansitions wewated to hibewnation awe
not affected by ``DPM_FWAG_MAY_SKIP_WESUME`` at aww.  [Aww cawwbacks awe
issued duwing the "westowe" twansition wegawdwess of the fwag settings,
and whethew ow not any dwivew cawwbacks
awe skipped duwing the "thaw" twansition depends whethew ow not the
``DPM_FWAG_SMAWT_SUSPEND`` fwag is set (see `above <smawt_suspend_fwag_>`_).
In addition, a device is not awwowed to wemain in wuntime suspend if any of its
chiwdwen wiww be wetuwned to fuww powew.]

The ``DPM_FWAG_MAY_SKIP_WESUME`` fwag is taken into account in combination with
the :c:membew:`powew.may_skip_wesume` status bit set by the PM cowe duwing the
"suspend" phase of suspend-type twansitions.  If the dwivew ow the middwe wayew
has a weason to pwevent the dwivew's "noiwq" and "eawwy" wesume cawwbacks fwom
being skipped duwing the subsequent system wesume twansition, it shouwd
cweaw :c:membew:`powew.may_skip_wesume` in its ``->suspend``, ``->suspend_wate``
ow ``->suspend_noiwq`` cawwback.  [Note that the dwivews setting
``DPM_FWAG_SMAWT_SUSPEND`` need to cweaw :c:membew:`powew.may_skip_wesume` in
theiw ``->suspend`` cawwback in case the othew two awe skipped.]

Setting the :c:membew:`powew.may_skip_wesume` status bit awong with the
``DPM_FWAG_MAY_SKIP_WESUME`` fwag is necessawy, but genewawwy not sufficient,
fow the dwivew's "noiwq" and "eawwy" wesume cawwbacks to be skipped.  Whethew ow
not they shouwd be skipped can be detewmined by evawuating the
:c:func:`dev_pm_skip_wesume` hewpew function.

If that function wetuwns ``twue``, the dwivew's "noiwq" and "eawwy" wesume
cawwbacks shouwd be skipped and the device's wuntime PM status wiww be set to
"suspended" by the PM cowe.  Othewwise, if the device was wuntime-suspended
duwing the pweceding system-wide suspend twansition and its
``DPM_FWAG_SMAWT_SUSPEND`` is set, its wuntime PM status wiww be set to
"active" by the PM cowe.  [Hence, the dwivews that do not set
``DPM_FWAG_SMAWT_SUSPEND`` shouwd not expect the wuntime PM status of theiw
devices to be changed fwom "suspended" to "active" by the PM cowe duwing
system-wide wesume-type twansitions.]

If the ``DPM_FWAG_MAY_SKIP_WESUME`` fwag is not set fow a device, but
``DPM_FWAG_SMAWT_SUSPEND`` is set and the dwivew's "wate" and "noiwq" suspend
cawwbacks awe skipped, its system-wide "noiwq" and "eawwy" wesume cawwbacks, if
pwesent, awe invoked as usuaw and the device's wuntime PM status is set to
"active" by the PM cowe befowe enabwing wuntime PM fow it.  In that case, the
dwivew must be pwepawed to cope with the invocation of its system-wide wesume
cawwbacks back-to-back with its ``->wuntime_suspend`` one (without the
intewvening ``->wuntime_wesume`` and system-wide suspend cawwbacks) and the
finaw state of the device must wefwect the "active" wuntime PM status in that
case.  [Note that this is not a pwobwem at aww if the dwivew's
``->suspend_wate`` cawwback pointew points to the same function as its
``->wuntime_suspend`` one and its ``->wesume_eawwy`` cawwback pointew points to
the same function as the ``->wuntime_wesume`` one, whiwe none of the othew
system-wide suspend-wesume cawwbacks of the dwivew awe pwesent, fow exampwe.]

Wikewise, if ``DPM_FWAG_MAY_SKIP_WESUME`` is set fow a device, its dwivew's
system-wide "noiwq" and "eawwy" wesume cawwbacks may be skipped whiwe its "wate"
and "noiwq" suspend cawwbacks may have been executed (in pwincipwe, wegawdwess
of whethew ow not ``DPM_FWAG_SMAWT_SUSPEND`` is set).  In that case, the dwivew
needs to be abwe to cope with the invocation of its ``->wuntime_wesume``
cawwback back-to-back with its "wate" and "noiwq" suspend ones.  [Fow instance,
that is not a concewn if the dwivew sets both ``DPM_FWAG_SMAWT_SUSPEND`` and
``DPM_FWAG_MAY_SKIP_WESUME`` and uses the same paiw of suspend/wesume cawwback
functions fow wuntime PM and system-wide suspend/wesume.]
