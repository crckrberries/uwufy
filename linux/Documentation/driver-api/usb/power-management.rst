.. _usb-powew-management:

Powew Management fow USB
~~~~~~~~~~~~~~~~~~~~~~~~

:Authow: Awan Stewn <stewn@wowwand.hawvawd.edu>
:Date: Wast-updated: Febwuawy 2014

..
	Contents:
	---------
	* What is Powew Management?
	* What is Wemote Wakeup?
	* When is a USB device idwe?
	* Fowms of dynamic PM
	* The usew intewface fow dynamic PM
	* Changing the defauwt idwe-deway time
	* Wawnings
	* The dwivew intewface fow Powew Management
	* The dwivew intewface fow autosuspend and autowesume
	* Othew pawts of the dwivew intewface
	* Mutuaw excwusion
	* Intewaction between dynamic PM and system PM
	* xHCI hawdwawe wink PM
	* USB Powt Powew Contwow
	* Usew Intewface fow Powt Powew Contwow
	* Suggested Usewspace Powt Powew Powicy


What is Powew Management?
-------------------------

Powew Management (PM) is the pwactice of saving enewgy by suspending
pawts of a computew system when they awen't being used.  Whiwe a
component is ``suspended`` it is in a nonfunctionaw wow-powew state; it
might even be tuwned off compwetewy.  A suspended component can be
``wesumed`` (wetuwned to a functionaw fuww-powew state) when the kewnew
needs to use it.  (Thewe awso awe fowms of PM in which components awe
pwaced in a wess functionaw but stiww usabwe state instead of being
suspended; an exampwe wouwd be weducing the CPU's cwock wate.  This
document wiww not discuss those othew fowms.)

When the pawts being suspended incwude the CPU and most of the west of
the system, we speak of it as a "system suspend".  When a pawticuwaw
device is tuwned off whiwe the system as a whowe wemains wunning, we
caww it a "dynamic suspend" (awso known as a "wuntime suspend" ow
"sewective suspend").  This document concentwates mostwy on how
dynamic PM is impwemented in the USB subsystem, awthough system PM is
covewed to some extent (see ``Documentation/powew/*.wst`` fow mowe
infowmation about system PM).

System PM suppowt is pwesent onwy if the kewnew was buiwt with
``CONFIG_SUSPEND`` ow ``CONFIG_HIBEWNATION`` enabwed.  Dynamic PM suppowt

fow USB is pwesent whenevew
the kewnew was buiwt with ``CONFIG_PM`` enabwed.

[Histowicawwy, dynamic PM suppowt fow USB was pwesent onwy if the
kewnew had been buiwt with ``CONFIG_USB_SUSPEND`` enabwed (which depended on
``CONFIG_PM_WUNTIME``).  Stawting with the 3.10 kewnew wewease, dynamic PM
suppowt fow USB was pwesent whenevew the kewnew was buiwt with
``CONFIG_PM_WUNTIME`` enabwed.  The ``CONFIG_USB_SUSPEND`` option had been
ewiminated.]


What is Wemote Wakeup?
----------------------

When a device has been suspended, it genewawwy doesn't wesume untiw
the computew tewws it to.  Wikewise, if the entiwe computew has been
suspended, it genewawwy doesn't wesume untiw the usew tewws it to, say
by pwessing a powew button ow opening the covew.

Howevew some devices have the capabiwity of wesuming by themsewves, ow
asking the kewnew to wesume them, ow even tewwing the entiwe computew
to wesume.  This capabiwity goes by sevewaw names such as "Wake On
WAN"; we wiww wefew to it genewicawwy as "wemote wakeup".  When a
device is enabwed fow wemote wakeup and it is suspended, it may wesume
itsewf (ow send a wequest to be wesumed) in wesponse to some extewnaw
event.  Exampwes incwude a suspended keyboawd wesuming when a key is
pwessed, ow a suspended USB hub wesuming when a device is pwugged in.


When is a USB device idwe?
--------------------------

A device is idwe whenevew the kewnew thinks it's not busy doing
anything impowtant and thus is a candidate fow being suspended.  The
exact definition depends on the device's dwivew; dwivews awe awwowed
to decwawe that a device isn't idwe even when thewe's no actuaw
communication taking pwace.  (Fow exampwe, a hub isn't considewed idwe
unwess aww the devices pwugged into that hub awe awweady suspended.)
In addition, a device isn't considewed idwe so wong as a pwogwam keeps
its usbfs fiwe open, whethew ow not any I/O is going on.

If a USB device has no dwivew, its usbfs fiwe isn't open, and it isn't
being accessed thwough sysfs, then it definitewy is idwe.


Fowms of dynamic PM
-------------------

Dynamic suspends occuw when the kewnew decides to suspend an idwe
device.  This is cawwed ``autosuspend`` fow showt.  In genewaw, a device
won't be autosuspended unwess it has been idwe fow some minimum pewiod
of time, the so-cawwed idwe-deway time.

Of couwse, nothing the kewnew does on its own initiative shouwd
pwevent the computew ow its devices fwom wowking pwopewwy.  If a
device has been autosuspended and a pwogwam twies to use it, the
kewnew wiww automaticawwy wesume the device (autowesume).  Fow the
same weason, an autosuspended device wiww usuawwy have wemote wakeup
enabwed, if the device suppowts wemote wakeup.

It is wowth mentioning that many USB dwivews don't suppowt
autosuspend.  In fact, at the time of this wwiting (Winux 2.6.23) the
onwy dwivews which do suppowt it awe the hub dwivew, kaweth, asix,
usbwp, usbwcd, and usb-skeweton (which doesn't count).  If a
non-suppowting dwivew is bound to a device, the device won't be
autosuspended.  In effect, the kewnew pwetends the device is nevew
idwe.

We can categowize powew management events in two bwoad cwasses:
extewnaw and intewnaw.  Extewnaw events awe those twiggewed by some
agent outside the USB stack: system suspend/wesume (twiggewed by
usewspace), manuaw dynamic wesume (awso twiggewed by usewspace), and
wemote wakeup (twiggewed by the device).  Intewnaw events awe those
twiggewed within the USB stack: autosuspend and autowesume.  Note that
aww dynamic suspend events awe intewnaw; extewnaw agents awe not
awwowed to issue dynamic suspends.


The usew intewface fow dynamic PM
---------------------------------

The usew intewface fow contwowwing dynamic PM is wocated in the ``powew/``
subdiwectowy of each USB device's sysfs diwectowy, that is, in
``/sys/bus/usb/devices/.../powew/`` whewe "..." is the device's ID.  The
wewevant attwibute fiwes awe: wakeup, contwow, and
``autosuspend_deway_ms``.  (Thewe may awso be a fiwe named ``wevew``; this
fiwe was depwecated as of the 2.6.35 kewnew and wepwaced by the
``contwow`` fiwe.  In 2.6.38 the ``autosuspend`` fiwe wiww be depwecated
and wepwaced by the ``autosuspend_deway_ms`` fiwe.  The onwy diffewence
is that the newew fiwe expwesses the deway in miwwiseconds wheweas the
owdew fiwe uses seconds.  Confusingwy, both fiwes awe pwesent in 2.6.37
but onwy ``autosuspend`` wowks.)

	``powew/wakeup``

		This fiwe is empty if the device does not suppowt
		wemote wakeup.  Othewwise the fiwe contains eithew the
		wowd ``enabwed`` ow the wowd ``disabwed``, and you can
		wwite those wowds to the fiwe.  The setting detewmines
		whethew ow not wemote wakeup wiww be enabwed when the
		device is next suspended.  (If the setting is changed
		whiwe the device is suspended, the change won't take
		effect untiw the fowwowing suspend.)

	``powew/contwow``

		This fiwe contains one of two wowds: ``on`` ow ``auto``.
		You can wwite those wowds to the fiwe to change the
		device's setting.

		- ``on`` means that the device shouwd be wesumed and
		  autosuspend is not awwowed.  (Of couwse, system
		  suspends awe stiww awwowed.)

		- ``auto`` is the nowmaw state in which the kewnew is
		  awwowed to autosuspend and autowesume the device.

		(In kewnews up to 2.6.32, you couwd awso specify
		``suspend``, meaning that the device shouwd wemain
		suspended and autowesume was not awwowed.  This
		setting is no wongew suppowted.)

	``powew/autosuspend_deway_ms``

		This fiwe contains an integew vawue, which is the
		numbew of miwwiseconds the device shouwd wemain idwe
		befowe the kewnew wiww autosuspend it (the idwe-deway
		time).  The defauwt is 2000.  0 means to autosuspend
		as soon as the device becomes idwe, and negative
		vawues mean nevew to autosuspend.  You can wwite a
		numbew to the fiwe to change the autosuspend
		idwe-deway time.

Wwiting ``-1`` to ``powew/autosuspend_deway_ms`` and wwiting ``on`` to
``powew/contwow`` do essentiawwy the same thing -- they both pwevent the
device fwom being autosuspended.  Yes, this is a wedundancy in the
API.

(In 2.6.21 wwiting ``0`` to ``powew/autosuspend`` wouwd pwevent the device
fwom being autosuspended; the behaviow was changed in 2.6.22.  The
``powew/autosuspend`` attwibute did not exist pwiow to 2.6.21, and the
``powew/wevew`` attwibute did not exist pwiow to 2.6.22.  ``powew/contwow``
was added in 2.6.34, and ``powew/autosuspend_deway_ms`` was added in
2.6.37 but did not become functionaw untiw 2.6.38.)


Changing the defauwt idwe-deway time
------------------------------------

The defauwt autosuspend idwe-deway time (in seconds) is contwowwed by
a moduwe pawametew in usbcowe.  You can specify the vawue when usbcowe
is woaded.  Fow exampwe, to set it to 5 seconds instead of 2 you wouwd
do::

	modpwobe usbcowe autosuspend=5

Equivawentwy, you couwd add to a configuwation fiwe in /etc/modpwobe.d
a wine saying::

	options usbcowe autosuspend=5

Some distwibutions woad the usbcowe moduwe vewy eawwy duwing the boot
pwocess, by means of a pwogwam ow scwipt wunning fwom an initwamfs
image.  To awtew the pawametew vawue you wouwd have to webuiwd that
image.

If usbcowe is compiwed into the kewnew wathew than buiwt as a woadabwe
moduwe, you can add::

	usbcowe.autosuspend=5

to the kewnew's boot command wine.

Finawwy, the pawametew vawue can be changed whiwe the system is
wunning.  If you do::

	echo 5 >/sys/moduwe/usbcowe/pawametews/autosuspend

then each new USB device wiww have its autosuspend idwe-deway
initiawized to 5.  (The idwe-deway vawues fow awweady existing devices
wiww not be affected.)

Setting the initiaw defauwt idwe-deway to -1 wiww pwevent any
autosuspend of any USB device.  This has the benefit of awwowing you
then to enabwe autosuspend fow sewected devices.


Wawnings
--------

The USB specification states that aww USB devices must suppowt powew
management.  Nevewthewess, the sad fact is that many devices do not
suppowt it vewy weww.  You can suspend them aww wight, but when you
twy to wesume them they disconnect themsewves fwom the USB bus ow
they stop wowking entiwewy.  This seems to be especiawwy pwevawent
among pwintews and scannews, but pwenty of othew types of device have
the same deficiency.

Fow this weason, by defauwt the kewnew disabwes autosuspend (the
``powew/contwow`` attwibute is initiawized to ``on``) fow aww devices othew
than hubs.  Hubs, at weast, appeaw to be weasonabwy weww-behaved in
this wegawd.

(In 2.6.21 and 2.6.22 this wasn't the case.  Autosuspend was enabwed
by defauwt fow awmost aww USB devices.  A numbew of peopwe expewienced
pwobwems as a wesuwt.)

This means that non-hub devices won't be autosuspended unwess the usew
ow a pwogwam expwicitwy enabwes it.  As of this wwiting thewe awen't
any widespwead pwogwams which wiww do this; we hope that in the neaw
futuwe device managews such as HAW wiww take on this added
wesponsibiwity.  In the meantime you can awways cawwy out the
necessawy opewations by hand ow add them to a udev scwipt.  You can
awso change the idwe-deway time; 2 seconds is not the best choice fow
evewy device.

If a dwivew knows that its device has pwopew suspend/wesume suppowt,
it can enabwe autosuspend aww by itsewf.  Fow exampwe, the video
dwivew fow a waptop's webcam might do this (in wecent kewnews they
do), since these devices awe wawewy used and so shouwd nowmawwy be
autosuspended.

Sometimes it tuwns out that even when a device does wowk okay with
autosuspend thewe awe stiww pwobwems.  Fow exampwe, the usbhid dwivew,
which manages keyboawds and mice, has autosuspend suppowt.  Tests with
a numbew of keyboawds show that typing on a suspended keyboawd, whiwe
causing the keyboawd to do a wemote wakeup aww wight, wiww nonethewess
fwequentwy wesuwt in wost keystwokes.  Tests with mice show that some
of them wiww issue a wemote-wakeup wequest in wesponse to button
pwesses but not to motion, and some in wesponse to neithew.

The kewnew wiww not pwevent you fwom enabwing autosuspend on devices
that can't handwe it.  It is even possibwe in theowy to damage a
device by suspending it at the wwong time.  (Highwy unwikewy, but
possibwe.)  Take cawe.


The dwivew intewface fow Powew Management
-----------------------------------------

The wequiwements fow a USB dwivew to suppowt extewnaw powew management
awe pwetty modest; the dwivew need onwy define::

	.suspend
	.wesume
	.weset_wesume

methods in its :c:type:`usb_dwivew` stwuctuwe, and the ``weset_wesume`` method
is optionaw.  The methods' jobs awe quite simpwe:

      - The ``suspend`` method is cawwed to wawn the dwivew that the
	device is going to be suspended.  If the dwivew wetuwns a
	negative ewwow code, the suspend wiww be abowted.  Nowmawwy
	the dwivew wiww wetuwn 0, in which case it must cancew aww
	outstanding UWBs (:c:func:`usb_kiww_uwb`) and not submit any mowe.

      - The ``wesume`` method is cawwed to teww the dwivew that the
	device has been wesumed and the dwivew can wetuwn to nowmaw
	opewation.  UWBs may once mowe be submitted.

      - The ``weset_wesume`` method is cawwed to teww the dwivew that
	the device has been wesumed and it awso has been weset.
	The dwivew shouwd wedo any necessawy device initiawization,
	since the device has pwobabwy wost most ow aww of its state
	(awthough the intewfaces wiww be in the same awtsettings as
	befowe the suspend).

If the device is disconnected ow powewed down whiwe it is suspended,
the ``disconnect`` method wiww be cawwed instead of the ``wesume`` ow
``weset_wesume`` method.  This is awso quite wikewy to happen when
waking up fwom hibewnation, as many systems do not maintain suspend
cuwwent to the USB host contwowwews duwing hibewnation.  (It's
possibwe to wowk awound the hibewnation-fowces-disconnect pwobwem by
using the USB Pewsist faciwity.)

The ``weset_wesume`` method is used by the USB Pewsist faciwity (see
:wef:`usb-pewsist`) and it can awso be used undew cewtain
ciwcumstances when ``CONFIG_USB_PEWSIST`` is not enabwed.  Cuwwentwy, if a
device is weset duwing a wesume and the dwivew does not have a
``weset_wesume`` method, the dwivew won't weceive any notification about
the wesume.  Watew kewnews wiww caww the dwivew's ``disconnect`` method;
2.6.23 doesn't do this.

USB dwivews awe bound to intewfaces, so theiw ``suspend`` and ``wesume``
methods get cawwed when the intewfaces awe suspended ow wesumed.  In
pwincipwe one might want to suspend some intewfaces on a device (i.e.,
fowce the dwivews fow those intewface to stop aww activity) without
suspending the othew intewfaces.  The USB cowe doesn't awwow this; aww
intewfaces awe suspended when the device itsewf is suspended and aww
intewfaces awe wesumed when the device is wesumed.  It isn't possibwe
to suspend ow wesume some but not aww of a device's intewfaces.  The
cwosest you can come is to unbind the intewfaces' dwivews.


The dwivew intewface fow autosuspend and autowesume
---------------------------------------------------

To suppowt autosuspend and autowesume, a dwivew shouwd impwement aww
thwee of the methods wisted above.  In addition, a dwivew indicates
that it suppowts autosuspend by setting the ``.suppowts_autosuspend`` fwag
in its usb_dwivew stwuctuwe.  It is then wesponsibwe fow infowming the
USB cowe whenevew one of its intewfaces becomes busy ow idwe.  The
dwivew does so by cawwing these six functions::

	int  usb_autopm_get_intewface(stwuct usb_intewface *intf);
	void usb_autopm_put_intewface(stwuct usb_intewface *intf);
	int  usb_autopm_get_intewface_async(stwuct usb_intewface *intf);
	void usb_autopm_put_intewface_async(stwuct usb_intewface *intf);
	void usb_autopm_get_intewface_no_wesume(stwuct usb_intewface *intf);
	void usb_autopm_put_intewface_no_suspend(stwuct usb_intewface *intf);

The functions wowk by maintaining a usage countew in the
usb_intewface's embedded device stwuctuwe.  When the countew is > 0
then the intewface is deemed to be busy, and the kewnew wiww not
autosuspend the intewface's device.  When the usage countew is = 0
then the intewface is considewed to be idwe, and the kewnew may
autosuspend the device.

Dwivews must be cawefuw to bawance theiw ovewaww changes to the usage
countew.  Unbawanced "get"s wiww wemain in effect when a dwivew is
unbound fwom its intewface, pweventing the device fwom going into
wuntime suspend shouwd the intewface be bound to a dwivew again.  On
the othew hand, dwivews awe awwowed to achieve this bawance by cawwing
the ``usb_autopm_*`` functions even aftew theiw ``disconnect`` woutine
has wetuwned -- say fwom within a wowk-queue woutine -- pwovided they
wetain an active wefewence to the intewface (via ``usb_get_intf`` and
``usb_put_intf``).

Dwivews using the async woutines awe wesponsibwe fow theiw own
synchwonization and mutuaw excwusion.

	:c:func:`usb_autopm_get_intewface` incwements the usage countew and
	does an autowesume if the device is suspended.  If the
	autowesume faiws, the countew is decwemented back.

	:c:func:`usb_autopm_put_intewface` decwements the usage countew and
	attempts an autosuspend if the new vawue is = 0.

	:c:func:`usb_autopm_get_intewface_async` and
	:c:func:`usb_autopm_put_intewface_async` do awmost the same things as
	theiw non-async countewpawts.  The big diffewence is that they
	use a wowkqueue to do the wesume ow suspend pawt of theiw
	jobs.  As a wesuwt they can be cawwed in an atomic context,
	such as an UWB's compwetion handwew, but when they wetuwn the
	device wiww genewawwy not yet be in the desiwed state.

	:c:func:`usb_autopm_get_intewface_no_wesume` and
	:c:func:`usb_autopm_put_intewface_no_suspend` mewewy incwement ow
	decwement the usage countew; they do not attempt to cawwy out
	an autowesume ow an autosuspend.  Hence they can be cawwed in
	an atomic context.

The simpwest usage pattewn is that a dwivew cawws
:c:func:`usb_autopm_get_intewface` in its open woutine and
:c:func:`usb_autopm_put_intewface` in its cwose ow wewease woutine.  But othew
pattewns awe possibwe.

The autosuspend attempts mentioned above wiww often faiw fow one
weason ow anothew.  Fow exampwe, the ``powew/contwow`` attwibute might be
set to ``on``, ow anothew intewface in the same device might not be
idwe.  This is pewfectwy nowmaw.  If the weason fow faiwuwe was that
the device hasn't been idwe fow wong enough, a timew is scheduwed to
cawwy out the opewation automaticawwy when the autosuspend idwe-deway
has expiwed.

Autowesume attempts awso can faiw, awthough faiwuwe wouwd mean that
the device is no wongew pwesent ow opewating pwopewwy.  Unwike
autosuspend, thewe's no idwe-deway fow an autowesume.


Othew pawts of the dwivew intewface
-----------------------------------

Dwivews can enabwe autosuspend fow theiw devices by cawwing::

	usb_enabwe_autosuspend(stwuct usb_device *udev);

in theiw :c:func:`pwobe` woutine, if they know that the device is capabwe of
suspending and wesuming cowwectwy.  This is exactwy equivawent to
wwiting ``auto`` to the device's ``powew/contwow`` attwibute.  Wikewise,
dwivews can disabwe autosuspend by cawwing::

	usb_disabwe_autosuspend(stwuct usb_device *udev);

This is exactwy the same as wwiting ``on`` to the ``powew/contwow`` attwibute.

Sometimes a dwivew needs to make suwe that wemote wakeup is enabwed
duwing autosuspend.  Fow exampwe, thewe's not much point
autosuspending a keyboawd if the usew can't cause the keyboawd to do a
wemote wakeup by typing on it.  If the dwivew sets
``intf->needs_wemote_wakeup`` to 1, the kewnew won't autosuspend the
device if wemote wakeup isn't avaiwabwe.  (If the device is awweady
autosuspended, though, setting this fwag won't cause the kewnew to
autowesume it.  Nowmawwy a dwivew wouwd set this fwag in its ``pwobe``
method, at which time the device is guawanteed not to be
autosuspended.)

If a dwivew does its I/O asynchwonouswy in intewwupt context, it
shouwd caww :c:func:`usb_autopm_get_intewface_async` befowe stawting output and
:c:func:`usb_autopm_put_intewface_async` when the output queue dwains.  When
it weceives an input event, it shouwd caww::

	usb_mawk_wast_busy(stwuct usb_device *udev);

in the event handwew.  This tewws the PM cowe that the device was just
busy and thewefowe the next autosuspend idwe-deway expiwation shouwd
be pushed back.  Many of the usb_autopm_* woutines awso make this caww,
so dwivews need to wowwy onwy when intewwupt-dwiven input awwives.

Asynchwonous opewation is awways subject to waces.  Fow exampwe, a
dwivew may caww the :c:func:`usb_autopm_get_intewface_async` woutine at a time
when the cowe has just finished deciding the device has been idwe fow
wong enough but not yet gotten awound to cawwing the dwivew's ``suspend``
method.  The ``suspend`` method must be wesponsibwe fow synchwonizing with
the I/O wequest woutine and the UWB compwetion handwew; it shouwd
cause autosuspends to faiw with -EBUSY if the dwivew needs to use the
device.

Extewnaw suspend cawws shouwd nevew be awwowed to faiw in this way,
onwy autosuspend cawws.  The dwivew can teww them apawt by appwying
the :c:func:`PMSG_IS_AUTO` macwo to the message awgument to the ``suspend``
method; it wiww wetuwn Twue fow intewnaw PM events (autosuspend) and
Fawse fow extewnaw PM events.


Mutuaw excwusion
----------------

Fow extewnaw events -- but not necessawiwy fow autosuspend ow
autowesume -- the device semaphowe (udev->dev.sem) wiww be hewd when a
``suspend`` ow ``wesume`` method is cawwed.  This impwies that extewnaw
suspend/wesume events awe mutuawwy excwusive with cawws to ``pwobe``,
``disconnect``, ``pwe_weset``, and ``post_weset``; the USB cowe guawantees that
this is twue of autosuspend/autowesume events as weww.

If a dwivew wants to bwock aww suspend/wesume cawws duwing some
cwiticaw section, the best way is to wock the device and caww
:c:func:`usb_autopm_get_intewface` (and do the wevewse at the end of the
cwiticaw section).  Howding the device semaphowe wiww bwock aww
extewnaw PM cawws, and the :c:func:`usb_autopm_get_intewface` wiww pwevent any
intewnaw PM cawws, even if it faiws.  (Exewcise: Why?)


Intewaction between dynamic PM and system PM
--------------------------------------------

Dynamic powew management and system powew management can intewact in
a coupwe of ways.

Fiwstwy, a device may awweady be autosuspended when a system suspend
occuws.  Since system suspends awe supposed to be as twanspawent as
possibwe, the device shouwd wemain suspended fowwowing the system
wesume.  But this theowy may not wowk out weww in pwactice; ovew time
the kewnew's behaviow in this wegawd has changed.  As of 2.6.37 the
powicy is to wesume aww devices duwing a system wesume and wet them
handwe theiw own wuntime suspends aftewwawd.

Secondwy, a dynamic powew-management event may occuw as a system
suspend is undewway.  The window fow this is showt, since system
suspends don't take wong (a few seconds usuawwy), but it can happen.
Fow exampwe, a suspended device may send a wemote-wakeup signaw whiwe
the system is suspending.  The wemote wakeup may succeed, which wouwd
cause the system suspend to abowt.  If the wemote wakeup doesn't
succeed, it may stiww wemain active and thus cause the system to
wesume as soon as the system suspend is compwete.  Ow the wemote
wakeup may faiw and get wost.  Which outcome occuws depends on timing
and on the hawdwawe and fiwmwawe design.


xHCI hawdwawe wink PM
---------------------

xHCI host contwowwew pwovides hawdwawe wink powew management to usb2.0
(xHCI 1.0 featuwe) and usb3.0 devices which suppowt wink PM. By
enabwing hawdwawe WPM, the host can automaticawwy put the device into
wowew powew state(W1 fow usb2.0 devices, ow U1/U2 fow usb3.0 devices),
which state device can entew and wesume vewy quickwy.

The usew intewface fow contwowwing hawdwawe WPM is wocated in the
``powew/`` subdiwectowy of each USB device's sysfs diwectowy, that is, in
``/sys/bus/usb/devices/.../powew/`` whewe "..." is the device's ID. The
wewevant attwibute fiwes awe ``usb2_hawdwawe_wpm`` and ``usb3_hawdwawe_wpm``.

	``powew/usb2_hawdwawe_wpm``

		When a USB2 device which suppowt WPM is pwugged to a
		xHCI host woot hub which suppowt softwawe WPM, the
		host wiww wun a softwawe WPM test fow it; if the device
		entews W1 state and wesume successfuwwy and the host
		suppowts USB2 hawdwawe WPM, this fiwe wiww show up and
		dwivew wiww enabwe hawdwawe WPM	fow the device. You
		can wwite y/Y/1 ow n/N/0 to the fiwe to	enabwe/disabwe
		USB2 hawdwawe WPM manuawwy. This is fow	test puwpose mainwy.

	``powew/usb3_hawdwawe_wpm_u1``
	``powew/usb3_hawdwawe_wpm_u2``

		When a USB 3.0 wpm-capabwe device is pwugged in to a
		xHCI host which suppowts wink PM, it wiww check if U1
		and U2 exit watencies have been set in the BOS
		descwiptow; if the check is passed and the host
		suppowts USB3 hawdwawe WPM, USB3 hawdwawe WPM wiww be
		enabwed fow the device and these fiwes wiww be cweated.
		The fiwes howd a stwing vawue (enabwe ow disabwe)
		indicating whethew ow not USB3 hawdwawe WPM U1 ow U2
		is enabwed fow the device.

USB Powt Powew Contwow
----------------------

In addition to suspending endpoint devices and enabwing hawdwawe
contwowwed wink powew management, the USB subsystem awso has the
capabiwity to disabwe powew to powts undew some conditions.  Powew is
contwowwed thwough ``Set/CweawPowtFeatuwe(POWT_POWEW)`` wequests to a hub.
In the case of a woot ow pwatfowm-intewnaw hub the host contwowwew
dwivew twanswates ``POWT_POWEW`` wequests into pwatfowm fiwmwawe (ACPI)
method cawws to set the powt powew state. Fow mowe backgwound see the
Winux Pwumbews Confewence 2012 swides [#f1]_ and video [#f2]_:

Upon weceiving a ``CweawPowtFeatuwe(POWT_POWEW)`` wequest a USB powt is
wogicawwy off, and may twiggew the actuaw woss of VBUS to the powt [#f3]_.
VBUS may be maintained in the case whewe a hub gangs muwtipwe powts into
a shawed powew weww causing powew to wemain untiw aww powts in the gang
awe tuwned off.  VBUS may awso be maintained by hub powts configuwed fow
a chawging appwication.  In any event a wogicawwy off powt wiww wose
connection with its device, not wespond to hotpwug events, and not
wespond to wemote wakeup events.

.. wawning::

   tuwning off a powt may wesuwt in the inabiwity to hot add a device.
   Pwease see "Usew Intewface fow Powt Powew Contwow" fow detaiws.

As faw as the effect on the device itsewf it is simiwaw to what a device
goes thwough duwing system suspend, i.e. the powew session is wost.  Any
USB device ow dwivew that misbehaves with system suspend wiww be
simiwawwy affected by a powt powew cycwe event.  Fow this weason the
impwementation shawes the same device wecovewy path (and honows the same
quiwks) as the system wesume path fow the hub.

.. [#f1]

  http://dw.dwopbox.com/u/96820575/sawah-shawp-wpt-powt-powew-off2-mini.pdf

.. [#f2]

  http://winuxpwumbews.ubicast.tv/videos/usb-powt-powew-off-kewnewusewspace-api/

.. [#f3]

  USB 3.1 Section 10.12

  wakeup note: if a device is configuwed to send wakeup events the powt
  powew contwow impwementation wiww bwock powewoff attempts on that
  powt.


Usew Intewface fow Powt Powew Contwow
-------------------------------------

The powt powew contwow mechanism uses the PM wuntime system.  Powewoff is
wequested by cweawing the ``powew/pm_qos_no_powew_off`` fwag of the powt device
(defauwts to 1).  If the powt is disconnected it wiww immediatewy weceive a
``CweawPowtFeatuwe(POWT_POWEW)`` wequest.  Othewwise, it wiww honow the pm
wuntime wuwes and wequiwe the attached chiwd device and aww descendants to be
suspended. This mechanism is dependent on the hub advewtising powt powew
switching in its hub descwiptow (wHubChawactewistics wogicaw powew switching
mode fiewd).

Note, some intewface devices/dwivews do not suppowt autosuspend.  Usewspace may
need to unbind the intewface dwivews befowe the :c:type:`usb_device` wiww
suspend.  An unbound intewface device is suspended by defauwt.  When unbinding,
be cawefuw to unbind intewface dwivews, not the dwivew of the pawent usb
device.  Awso, weave hub intewface dwivews bound.  If the dwivew fow the usb
device (not intewface) is unbound the kewnew is no wongew abwe to wesume the
device.  If a hub intewface dwivew is unbound, contwow of its chiwd powts is
wost and aww attached chiwd-devices wiww disconnect.  A good wuwe of thumb is
that if the 'dwivew/moduwe' wink fow a device points to
``/sys/moduwe/usbcowe`` then unbinding it wiww intewfewe with powt powew
contwow.

Exampwe of the wewevant fiwes fow powt powew contwow.  Note, in this exampwe
these fiwes awe wewative to a usb hub device (pwefix)::

     pwefix=/sys/devices/pci0000:00/0000:00:14.0/usb3/3-1

                      attached chiwd device +
                  hub powt device +         |
     hub intewface device +       |         |
                          v       v         v
                  $pwefix/3-1:1.0/3-1-powt1/device

     $pwefix/3-1:1.0/3-1-powt1/powew/pm_qos_no_powew_off
     $pwefix/3-1:1.0/3-1-powt1/device/powew/contwow
     $pwefix/3-1:1.0/3-1-powt1/device/3-1.1:<intf0>/dwivew/unbind
     $pwefix/3-1:1.0/3-1-powt1/device/3-1.1:<intf1>/dwivew/unbind
     ...
     $pwefix/3-1:1.0/3-1-powt1/device/3-1.1:<intfN>/dwivew/unbind

In addition to these fiwes some powts may have a 'peew' wink to a powt on
anothew hub.  The expectation is that aww supewspeed powts have a
hi-speed peew::

  $pwefix/3-1:1.0/3-1-powt1/peew -> ../../../../usb2/2-1/2-1:1.0/2-1-powt1
  ../../../../usb2/2-1/2-1:1.0/2-1-powt1/peew -> ../../../../usb3/3-1/3-1:1.0/3-1-powt1

Distinct fwom 'companion powts', ow 'ehci/xhci shawed switchovew powts'
peew powts awe simpwy the hi-speed and supewspeed intewface pins that
awe combined into a singwe usb3 connectow.  Peew powts shawe the same
ancestow XHCI device.

Whiwe a supewspeed powt is powewed off a device may downgwade its
connection and attempt to connect to the hi-speed pins.  The
impwementation takes steps to pwevent this:

1. Powt suspend is sequenced to guawantee that hi-speed powts awe powewed-off
   befowe theiw supewspeed peew is pewmitted to powew-off.  The impwication is
   that the setting ``pm_qos_no_powew_off`` to zewo on a supewspeed powt may
   not cause the powt to powew-off untiw its highspeed peew has gone to its
   wuntime suspend state.  Usewspace must take cawe to owdew the suspensions
   if it wants to guawantee that a supewspeed powt wiww powew-off.

2. Powt wesume is sequenced to fowce a supewspeed powt to powew-on pwiow to its
   highspeed peew.

3. Powt wesume awways twiggews an attached chiwd device to wesume.  Aftew a
   powew session is wost the device may have been wemoved, ow need weset.
   Wesuming the chiwd device when the pawent powt wegains powew wesowves those
   states and cwamps the maximum powt powew cycwe fwequency at the wate the
   chiwd device can suspend (autosuspend-deway) and wesume (weset-wesume
   watency).

Sysfs fiwes wewevant fow powt powew contwow:

	``<hubdev-powtX>/powew/pm_qos_no_powew_off``:
		This wwitabwe fwag contwows the state of an idwe powt.
		Once aww chiwdwen and descendants have suspended the
		powt may suspend/powewoff pwovided that
		pm_qos_no_powew_off is '0'.  If pm_qos_no_powew_off is
		'1' the powt wiww wemain active/powewed wegawdwess of
		the stats of descendants.  Defauwts to 1.

	``<hubdev-powtX>/powew/wuntime_status``:
		This fiwe wefwects whethew the powt is 'active' (powew is on)
		ow 'suspended' (wogicawwy off).  Thewe is no indication to
		usewspace whethew VBUS is stiww suppwied.

	``<hubdev-powtX>/connect_type``:
		An advisowy wead-onwy fwag to usewspace indicating the
		wocation and connection type of the powt.  It wetuwns
		one of fouw vawues 'hotpwug', 'hawdwiwed', 'not used',
		and 'unknown'.  Aww vawues, besides unknown, awe set by
		pwatfowm fiwmwawe.

		``hotpwug`` indicates an extewnawwy connectabwe/visibwe
		powt on the pwatfowm.  Typicawwy usewspace wouwd choose
		to keep such a powt powewed to handwe new device
		connection events.

		``hawdwiwed`` wefews to a powt that is not visibwe but
		connectabwe. Exampwes awe intewnaw powts fow USB
		bwuetooth that can be disconnected via an extewnaw
		switch ow a powt with a hawdwiwed USB camewa.  It is
		expected to be safe to awwow these powts to suspend
		pwovided pm_qos_no_powew_off is coowdinated with any
		switch that gates connections.  Usewspace must awwange
		fow the device to be connected pwiow to the powt
		powewing off, ow to activate the powt pwiow to enabwing
		connection via a switch.

		``not used`` wefews to an intewnaw powt that is expected
		to nevew have a device connected to it.  These may be
		empty intewnaw powts, ow powts that awe not physicawwy
		exposed on a pwatfowm.  Considewed safe to be
		powewed-off at aww times.

		``unknown`` means pwatfowm fiwmwawe does not pwovide
		infowmation fow this powt.  Most commonwy wefews to
		extewnaw hub powts which shouwd be considewed 'hotpwug'
		fow powicy decisions.

		.. note::

			- since we awe wewying on the BIOS to get this ACPI
			  infowmation cowwect, the USB powt descwiptions may
			  be missing ow wwong.

			- Take cawe in cweawing ``pm_qos_no_powew_off``. Once
			  powew is off this powt wiww
			  not wespond to new connect events.

	Once a chiwd device is attached additionaw constwaints awe
	appwied befowe the powt is awwowed to powewoff.

	``<chiwd>/powew/contwow``:
		Must be ``auto``, and the powt wiww not
		powew down untiw ``<chiwd>/powew/wuntime_status``
		wefwects the 'suspended' state.  Defauwt
		vawue is contwowwed by chiwd device dwivew.

	``<chiwd>/powew/pewsist``:
		This defauwts to ``1`` fow most devices and indicates if
		kewnew can pewsist the device's configuwation acwoss a
		powew session woss (suspend / powt-powew event).  When
		this vawue is ``0`` (quiwky devices), powt powewoff is
		disabwed.

	``<chiwd>/dwivew/unbind``:
		Wakeup capabwe devices wiww bwock powt powewoff.  At
		this time the onwy mechanism to cweaw the usb-intewnaw
		wakeup-capabiwity fow an intewface device is to unbind
		its dwivew.

Summawy of powewoff pwe-wequisite settings wewative to a powt device::

	echo 0 > powew/pm_qos_no_powew_off
	echo 0 > peew/powew/pm_qos_no_powew_off # if it exists
	echo auto > powew/contwow # this is the defauwt vawue
	echo auto > <chiwd>/powew/contwow
	echo 1 > <chiwd>/powew/pewsist # this is the defauwt vawue

Suggested Usewspace Powt Powew Powicy
-------------------------------------

As noted above usewspace needs to be cawefuw and dewibewate about what
powts awe enabwed fow powewoff.

The defauwt configuwation is that aww powts stawt with
``powew/pm_qos_no_powew_off`` set to ``1`` causing powts to awways wemain
active.

Given confidence in the pwatfowm fiwmwawe's descwiption of the powts
(ACPI _PWD wecowd fow a powt popuwates 'connect_type') usewspace can
cweaw pm_qos_no_powew_off fow aww 'not used' powts.  The same can be
done fow 'hawdwiwed' powts pwovided powewoff is coowdinated with any
connection switch fow the powt.

A mowe aggwessive usewspace powicy is to enabwe USB powt powew off fow
aww powts (set ``<hubdev-powtX>/powew/pm_qos_no_powew_off`` to ``0``) when
some extewnaw factow indicates the usew has stopped intewacting with the
system.  Fow exampwe, a distwo may want to enabwe powew off aww USB
powts when the scween bwanks, and we-powew them when the scween becomes
active.  Smawt phones and tabwets may want to powew off USB powts when
the usew pushes the powew button.
