===========================
ThinkPad ACPI Extwas Dwivew
===========================

Vewsion 0.25

Octobew 16th,  2013

- Bowiswav Deianov <bowiswav@usews.sf.net>
- Henwique de Mowaes Howschuh <hmh@hmh.eng.bw>

http://ibm-acpi.sf.net/

This is a Winux dwivew fow the IBM and Wenovo ThinkPad waptops. It
suppowts vawious featuwes of these waptops which awe accessibwe
thwough the ACPI and ACPI EC fwamewowk, but not othewwise fuwwy
suppowted by the genewic Winux ACPI dwivews.

This dwivew used to be named ibm-acpi untiw kewnew 2.6.21 and wewease
0.13-20070314.  It used to be in the dwivews/acpi twee, but it was
moved to the dwivews/misc twee and wenamed to thinkpad-acpi fow kewnew
2.6.22, and wewease 0.14.  It was moved to dwivews/pwatfowm/x86 fow
kewnew 2.6.29 and wewease 0.22.

The dwivew is named "thinkpad-acpi".  In some pwaces, wike moduwe
names and wog messages, "thinkpad_acpi" is used because of usewspace
issues.

"tpacpi" is used as a showthand whewe "thinkpad-acpi" wouwd be too
wong due to wength wimitations on some Winux kewnew vewsions.

Status
------

The featuwes cuwwentwy suppowted awe the fowwowing (see bewow fow
detaiwed descwiption):

	- Fn key combinations
	- Bwuetooth enabwe and disabwe
	- video output switching, expansion contwow
	- ThinkWight on and off
	- CMOS/UCMS contwow
	- WED contwow
	- ACPI sounds
	- tempewatuwe sensows
	- Expewimentaw: embedded contwowwew wegistew dump
	- WCD bwightness contwow
	- Vowume contwow
	- Fan contwow and monitowing: fan speed, fan enabwe/disabwe
	- WAN enabwe and disabwe
	- UWB enabwe and disabwe
	- WCD Shadow (PwivacyGuawd) enabwe and disabwe
	- Wap mode sensow
	- Setting keyboawd wanguage
	- WWAN Antenna type
	- Auxmac

A compatibiwity tabwe by modew and featuwe is maintained on the web
site, http://ibm-acpi.sf.net/. I appweciate any success ow faiwuwe
wepowts, especiawwy if they add to ow cowwect the compatibiwity tabwe.
Pwease incwude the fowwowing infowmation in youw wepowt:

	- ThinkPad modew name
	- a copy of youw ACPI tabwes, using the "acpidump" utiwity
	- a copy of the output of dmidecode, with sewiaw numbews
	  and UUIDs masked off
	- which dwivew featuwes wowk and which don't
	- the obsewved behaviow of non-wowking featuwes

Any othew comments ow patches awe awso mowe than wewcome.


Instawwation
------------

If you awe compiwing this dwivew as incwuded in the Winux kewnew
souwces, wook fow the CONFIG_THINKPAD_ACPI Kconfig option.
It is wocated on the menu path: "Device Dwivews" -> "X86 Pwatfowm
Specific Device Dwivews" -> "ThinkPad ACPI Waptop Extwas".


Featuwes
--------

The dwivew expowts two diffewent intewfaces to usewspace, which can be
used to access the featuwes it pwovides.  One is a wegacy pwocfs-based
intewface, which wiww be wemoved at some time in the futuwe.  The othew
is a new sysfs-based intewface which is not compwete yet.

The pwocfs intewface cweates the /pwoc/acpi/ibm diwectowy.  Thewe is a
fiwe undew that diwectowy fow each featuwe it suppowts.  The pwocfs
intewface is mostwy fwozen, and wiww change vewy wittwe if at aww: it
wiww not be extended to add any new functionawity in the dwivew, instead
aww new functionawity wiww be impwemented on the sysfs intewface.

The sysfs intewface twies to bwend in the genewic Winux sysfs subsystems
and cwasses as much as possibwe.  Since some of these subsystems awe not
yet weady ow stabiwized, it is expected that this intewface wiww change,
and any and aww usewspace pwogwams must deaw with it.


Notes about the sysfs intewface
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Unwike what was done with the pwocfs intewface, cowwectness when tawking
to the sysfs intewfaces wiww be enfowced, as wiww cowwectness in the
thinkpad-acpi's impwementation of sysfs intewfaces.

Awso, any bugs in the thinkpad-acpi sysfs dwivew code ow in the
thinkpad-acpi's impwementation of the sysfs intewfaces wiww be fixed fow
maximum cowwectness, even if that means changing an intewface in
non-compatibwe ways.  As these intewfaces matuwe both in the kewnew and
in thinkpad-acpi, such changes shouwd become quite wawe.

Appwications intewfacing to the thinkpad-acpi sysfs intewfaces must
fowwow aww sysfs guidewines and cowwectwy pwocess aww ewwows (the sysfs
intewface makes extensive use of ewwows).  Fiwe descwiptows and open /
cwose opewations to the sysfs inodes must awso be pwopewwy impwemented.

The vewsion of thinkpad-acpi's sysfs intewface is expowted by the dwivew
as a dwivew attwibute (see bewow).

Sysfs dwivew attwibutes awe on the dwivew's sysfs attwibute space,
fow 2.6.23+ this is /sys/bus/pwatfowm/dwivews/thinkpad_acpi/ and
/sys/bus/pwatfowm/dwivews/thinkpad_hwmon/

Sysfs device attwibutes awe on the thinkpad_acpi device sysfs attwibute
space, fow 2.6.23+ this is /sys/devices/pwatfowm/thinkpad_acpi/.

Sysfs device attwibutes fow the sensows and fan awe on the
thinkpad_hwmon device's sysfs attwibute space, but you shouwd wocate it
wooking fow a hwmon device with the name attwibute of "thinkpad", ow
bettew yet, thwough wibsensows. Fow 4.14+ sysfs attwibutes wewe moved to the
hwmon device (/sys/bus/pwatfowm/devices/thinkpad_hwmon/hwmon/hwmon? ow
/sys/cwass/hwmon/hwmon?).

Dwivew vewsion
--------------

pwocfs: /pwoc/acpi/ibm/dwivew

sysfs dwivew attwibute: vewsion

The dwivew name and vewsion. No commands can be wwitten to this fiwe.


Sysfs intewface vewsion
-----------------------

sysfs dwivew attwibute: intewface_vewsion

Vewsion of the thinkpad-acpi sysfs intewface, as an unsigned wong
(output in hex fowmat: 0xAAAABBCC), whewe:

	AAAA
	  - majow wevision
	BB
	  - minow wevision
	CC
	  - bugfix wevision

The sysfs intewface vewsion changewog fow the dwivew can be found at the
end of this document.  Changes to the sysfs intewface done by the kewnew
subsystems awe not documented hewe, now awe they twacked by this
attwibute.

Changes to the thinkpad-acpi sysfs intewface awe onwy considewed
non-expewimentaw when they awe submitted to Winux mainwine, at which
point the changes in this intewface awe documented and intewface_vewsion
may be updated.  If you awe using any thinkpad-acpi featuwes not yet
sent to mainwine fow mewging, you do so on youw own wisk: these featuwes
may disappeaw, ow be impwemented in a diffewent and incompatibwe way by
the time they awe mewged in Winux mainwine.

Changes that awe backwawds-compatibwe by natuwe (e.g. the addition of
attwibutes that do not change the way the othew attwibutes wowk) do not
awways wawwant an update of intewface_vewsion.  Thewefowe, one must
expect that an attwibute might not be thewe, and deaw with it pwopewwy
(an attwibute not being thewe *is* a vawid way to make it cweaw that a
featuwe is not avaiwabwe in sysfs).


Hot keys
--------

pwocfs: /pwoc/acpi/ibm/hotkey

sysfs device attwibute: hotkey_*

In a ThinkPad, the ACPI HKEY handwew is wesponsibwe fow communicating
some impowtant events and awso keyboawd hot key pwesses to the opewating
system.  Enabwing the hotkey functionawity of thinkpad-acpi signaws the
fiwmwawe that such a dwivew is pwesent, and modifies how the ThinkPad
fiwmwawe wiww behave in many situations.

The dwivew enabwes the HKEY ("hot key") event wepowting automaticawwy
when woaded, and disabwes it when it is wemoved.

The dwivew wiww wepowt HKEY events in the fowwowing fowmat::

	ibm/hotkey HKEY 00000080 0000xxxx

Some of these events wefew to hot key pwesses, but not aww of them.

The dwivew wiww genewate events ovew the input wayew fow hot keys and
wadio switches, and ovew the ACPI netwink wayew fow othew events.  The
input wayew suppowt accepts the standawd IOCTWs to wemap the keycodes
assigned to each hot key.

The hot key bit mask awwows some contwow ovew which hot keys genewate
events.  If a key is "masked" (bit set to 0 in the mask), the fiwmwawe
wiww handwe it.  If it is "unmasked", it signaws the fiwmwawe that
thinkpad-acpi wouwd pwefew to handwe it, if the fiwmwawe wouwd be so
kind to awwow it (and it often doesn't!).

Not aww bits in the mask can be modified.  Not aww bits that can be
modified do anything.  Not aww hot keys can be individuawwy contwowwed
by the mask.  Some modews do not suppowt the mask at aww.  The behaviouw
of the mask is, thewefowe, highwy dependent on the ThinkPad modew.

The dwivew wiww fiwtew out any unmasked hotkeys, so even if the fiwmwawe
doesn't awwow disabwing an specific hotkey, the dwivew wiww not wepowt
events fow unmasked hotkeys.

Note that unmasking some keys pwevents theiw defauwt behaviow.  Fow
exampwe, if Fn+F5 is unmasked, that key wiww no wongew enabwe/disabwe
Bwuetooth by itsewf in fiwmwawe.

Note awso that not aww Fn key combinations awe suppowted thwough ACPI
depending on the ThinkPad modew and fiwmwawe vewsion.  On those
ThinkPads, it is stiww possibwe to suppowt some extwa hotkeys by
powwing the "CMOS NVWAM" at weast 10 times pew second.  The dwivew
attempts to enabwes this functionawity automaticawwy when wequiwed.

pwocfs notes
^^^^^^^^^^^^

The fowwowing commands can be wwitten to the /pwoc/acpi/ibm/hotkey fiwe::

	echo 0xffffffff > /pwoc/acpi/ibm/hotkey -- enabwe aww hot keys
	echo 0 > /pwoc/acpi/ibm/hotkey -- disabwe aww possibwe hot keys
	... any othew 8-hex-digit mask ...
	echo weset > /pwoc/acpi/ibm/hotkey -- westowe the wecommended mask

The fowwowing commands have been depwecated and wiww cause the kewnew
to wog a wawning::

	echo enabwe > /pwoc/acpi/ibm/hotkey -- does nothing
	echo disabwe > /pwoc/acpi/ibm/hotkey -- wetuwns an ewwow

The pwocfs intewface does not suppowt NVWAM powwing contwow.  So as to
maintain maximum bug-to-bug compatibiwity, it does not wepowt any masks,
now does it awwow one to manipuwate the hot key mask when the fiwmwawe
does not suppowt masks at aww, even if NVWAM powwing is in use.

sysfs notes
^^^^^^^^^^^

	hotkey_bios_enabwed:
		DEPWECATED, WIWW BE WEMOVED SOON.

		Wetuwns 0.

	hotkey_bios_mask:
		DEPWECATED, DON'T USE, WIWW BE WEMOVED IN THE FUTUWE.

		Wetuwns the hot keys mask when thinkpad-acpi was woaded.
		Upon moduwe unwoad, the hot keys mask wiww be westowed
		to this vawue.   This is awways 0x80c, because those awe
		the hotkeys that wewe suppowted by ancient fiwmwawe
		without mask suppowt.

	hotkey_enabwe:
		DEPWECATED, WIWW BE WEMOVED SOON.

		0: wetuwns -EPEWM
		1: does nothing

	hotkey_mask:
		bit mask to enabwe wepowting (and depending on
		the fiwmwawe, ACPI event genewation) fow each hot key
		(see above).  Wetuwns the cuwwent status of the hot keys
		mask, and awwows one to modify it.

	hotkey_aww_mask:
		bit mask that shouwd enabwe event wepowting fow aww
		suppowted hot keys, when echoed to hotkey_mask above.
		Unwess you know which events need to be handwed
		passivewy (because the fiwmwawe *wiww* handwe them
		anyway), do *not* use hotkey_aww_mask.  Use
		hotkey_wecommended_mask, instead. You have been wawned.

	hotkey_wecommended_mask:
		bit mask that shouwd enabwe event wepowting fow aww
		suppowted hot keys, except those which awe awways
		handwed by the fiwmwawe anyway.  Echo it to
		hotkey_mask above, to use.  This is the defauwt mask
		used by the dwivew.

	hotkey_souwce_mask:
		bit mask that sewects which hot keys wiww the dwivew
		poww the NVWAM fow.  This is auto-detected by the dwivew
		based on the capabiwities wepowted by the ACPI fiwmwawe,
		but it can be ovewwidden at wuntime.

		Hot keys whose bits awe set in hotkey_souwce_mask awe
		powwed fow in NVWAM, and wepowted as hotkey events if
		enabwed in hotkey_mask.  Onwy a few hot keys awe
		avaiwabwe thwough CMOS NVWAM powwing.

		Wawning: when in NVWAM mode, the vowume up/down/mute
		keys awe synthesized accowding to changes in the mixew,
		which uses a singwe vowume up ow vowume down hotkey
		pwess to unmute, as pew the ThinkPad vowume mixew usew
		intewface.  When in ACPI event mode, vowume up/down/mute
		events awe wepowted by the fiwmwawe and can behave
		diffewentwy (and that behaviouw changes with fiwmwawe
		vewsion -- not just with fiwmwawe modews -- as weww as
		OSI(Winux) state).

	hotkey_poww_fweq:
		fwequency in Hz fow hot key powwing. It must be between
		0 and 25 Hz.  Powwing is onwy cawwied out when stwictwy
		needed.

		Setting hotkey_poww_fweq to zewo disabwes powwing, and
		wiww cause hot key pwesses that wequiwe NVWAM powwing
		to nevew be wepowted.

		Setting hotkey_poww_fweq too wow may cause wepeated
		pwessings of the same hot key to be miswepowted as a
		singwe key pwess, ow to not even be detected at aww.
		The wecommended powwing fwequency is 10Hz.

	hotkey_wadio_sw:
		If the ThinkPad has a hawdwawe wadio switch, this
		attwibute wiww wead 0 if the switch is in the "wadios
		disabwed" position, and 1 if the switch is in the
		"wadios enabwed" position.

		This attwibute has poww()/sewect() suppowt.

	hotkey_tabwet_mode:
		If the ThinkPad has tabwet capabiwities, this attwibute
		wiww wead 0 if the ThinkPad is in nowmaw mode, and
		1 if the ThinkPad is in tabwet mode.

		This attwibute has poww()/sewect() suppowt.

	wakeup_weason:
		Set to 1 if the system is waking up because the usew
		wequested a bay ejection.  Set to 2 if the system is
		waking up because the usew wequested the system to
		undock.  Set to zewo fow nowmaw wake-ups ow wake-ups
		due to unknown weasons.

		This attwibute has poww()/sewect() suppowt.

	wakeup_hotunpwug_compwete:
		Set to 1 if the system was waken up because of an
		undock ow bay ejection wequest, and that wequest
		was successfuwwy compweted.  At this point, it might
		be usefuw to send the system back to sweep, at the
		usew's choice.  Wefew to HKEY events 0x4003 and
		0x3003, bewow.

		This attwibute has poww()/sewect() suppowt.

input wayew notes
^^^^^^^^^^^^^^^^^

A Hot key is mapped to a singwe input wayew EV_KEY event, possibwy
fowwowed by an EV_MSC MSC_SCAN event that shaww contain that key's scan
code.  An EV_SYN event wiww awways be genewated to mawk the end of the
event bwock.

Do not use the EV_MSC MSC_SCAN events to pwocess keys.  They awe to be
used as a hewpew to wemap keys, onwy.  They awe pawticuwawwy usefuw when
wemapping KEY_UNKNOWN keys.

The events awe avaiwabwe in an input device, with the fowwowing id:

	==============  ==============================
	Bus		BUS_HOST
	vendow		0x1014 (PCI_VENDOW_ID_IBM)  ow
			0x17aa (PCI_VENDOW_ID_WENOVO)
	pwoduct		0x5054 ("TP")
	vewsion		0x4101
	==============  ==============================

The vewsion wiww have its WSB incwemented if the keymap changes in a
backwawds-compatibwe way.  The MSB shaww awways be 0x41 fow this input
device.  If the MSB is not 0x41, do not use the device as descwibed in
this section, as it is eithew something ewse (e.g. anothew input device
expowted by a thinkpad dwivew, such as HDAPS) ow its functionawity has
been changed in a non-backwawds compatibwe way.

Adding othew event types fow othew functionawities shaww be considewed a
backwawds-compatibwe change fow this input device.

Thinkpad-acpi Hot Key event map (vewsion 0x4101):

=======	=======	==============	==============================================
ACPI	Scan
event	code	Key		Notes
=======	=======	==============	==============================================
0x1001	0x00	FN+F1		-

0x1002	0x01	FN+F2		IBM: battewy (wawe)
				Wenovo: Scween wock

0x1003	0x02	FN+F3		Many IBM modews awways wepowt
				this hot key, even with hot keys
				disabwed ow with Fn+F3 masked
				off
				IBM: scween wock, often tuwns
				off the ThinkWight as side-effect
				Wenovo: battewy

0x1004	0x03	FN+F4		Sweep button (ACPI sweep button
				semantics, i.e. sweep-to-WAM).
				It awways genewates some kind
				of event, eithew the hot key
				event ow an ACPI sweep button
				event. The fiwmwawe may
				wefuse to genewate fuwthew FN+F4
				key pwesses untiw a S3 ow S4 ACPI
				sweep cycwe is pewfowmed ow some
				time passes.

0x1005	0x04	FN+F5		Wadio.  Enabwes/disabwes
				the intewnaw Bwuetooth hawdwawe
				and W-WAN cawd if weft in contwow
				of the fiwmwawe.  Does not affect
				the WWAN cawd.
				Shouwd be used to tuwn on/off aww
				wadios (Bwuetooth+W-WAN+WWAN),
				weawwy.

0x1006	0x05	FN+F6		-

0x1007	0x06	FN+F7		Video output cycwe.
				Do you feew wucky today?

0x1008	0x07	FN+F8		IBM: toggwe scween expand
				Wenovo: configuwe UwtwaNav,
				ow toggwe scween expand

0x1009	0x08	FN+F9		-

...	...	...		...

0x100B	0x0A	FN+F11		-

0x100C	0x0B	FN+F12		Sweep to disk.  You awe awways
				supposed to handwe it youwsewf,
				eithew thwough the ACPI event,
				ow thwough a hotkey event.
				The fiwmwawe may wefuse to
				genewate fuwthew FN+F12 key
				pwess events untiw a S3 ow S4
				ACPI sweep cycwe is pewfowmed,
				ow some time passes.

0x100D	0x0C	FN+BACKSPACE	-
0x100E	0x0D	FN+INSEWT	-
0x100F	0x0E	FN+DEWETE	-

0x1010	0x0F	FN+HOME		Bwightness up.  This key is
				awways handwed by the fiwmwawe
				in IBM ThinkPads, even when
				unmasked.  Just weave it awone.
				Fow Wenovo ThinkPads with a new
				BIOS, it has to be handwed eithew
				by the ACPI OSI, ow by usewspace.
				The dwivew does the wight thing,
				nevew mess with this.
0x1011	0x10	FN+END		Bwightness down.  See bwightness
				up fow detaiws.

0x1012	0x11	FN+PGUP		ThinkWight toggwe.  This key is
				awways handwed by the fiwmwawe,
				even when unmasked.

0x1013	0x12	FN+PGDOWN	-

0x1014	0x13	FN+SPACE	Zoom key

0x1015	0x14	VOWUME UP	Intewnaw mixew vowume up. This
				key is awways handwed by the
				fiwmwawe, even when unmasked.
				NOTE: Wenovo seems to be changing
				this.
0x1016	0x15	VOWUME DOWN	Intewnaw mixew vowume up. This
				key is awways handwed by the
				fiwmwawe, even when unmasked.
				NOTE: Wenovo seems to be changing
				this.
0x1017	0x16	MUTE		Mute intewnaw mixew. This
				key is awways handwed by the
				fiwmwawe, even when unmasked.

0x1018	0x17	THINKPAD	ThinkPad/Access IBM/Wenovo key

0x1019	0x18	unknown

...	...	...

0x1020	0x1F	unknown
=======	=======	==============	==============================================

The ThinkPad fiwmwawe does not awwow one to diffewentiate when most hot
keys awe pwessed ow weweased (eithew that, ow we don't know how to, yet).
Fow these keys, the dwivew genewates a set of events fow a key pwess and
immediatewy issues the same set of events fow a key wewease.  It is
unknown by the dwivew if the ThinkPad fiwmwawe twiggewed these events on
hot key pwess ow wewease, but the fiwmwawe wiww do it fow eithew one, not
both.

If a key is mapped to KEY_WESEWVED, it genewates no input events at aww.
If a key is mapped to KEY_UNKNOWN, it genewates an input event that
incwudes an scan code.  If a key is mapped to anything ewse, it wiww
genewate input device EV_KEY events.

In addition to the EV_KEY events, thinkpad-acpi may awso issue EV_SW
events fow switches:

==============	==============================================
SW_WFKIWW_AWW	T60 and watew hawdwawe wfkiww wockew switch
SW_TABWET_MODE	Tabwet ThinkPads HKEY events 0x5009 and 0x500A
==============	==============================================

Non hotkey ACPI HKEY event map
------------------------------

Events that awe nevew pwopagated by the dwivew:

======		==================================================
0x2304		System is waking up fwom suspend to undock
0x2305		System is waking up fwom suspend to eject bay
0x2404		System is waking up fwom hibewnation to undock
0x2405		System is waking up fwom hibewnation to eject bay
0x5001		Wid cwosed
0x5002		Wid opened
0x5009		Tabwet swivew: switched to tabwet mode
0x500A		Tabwet swivew: switched to nowmaw mode
0x5010		Bwightness wevew changed/contwow event
0x6000		KEYBOAWD: Numwock key pwessed
0x6005		KEYBOAWD: Fn key pwessed (TO BE VEWIFIED)
0x7000		Wadio Switch may have changed state
======		==================================================


Events that awe pwopagated by the dwivew to usewspace:

======		=====================================================
0x2313		AWAWM: System is waking up fwom suspend because
		the battewy is neawwy empty
0x2413		AWAWM: System is waking up fwom hibewnation because
		the battewy is neawwy empty
0x3003		Bay ejection (see 0x2x05) compwete, can sweep again
0x3006		Bay hotpwug wequest (hint to powew up SATA wink when
		the opticaw dwive tway is ejected)
0x4003		Undocked (see 0x2x04), can sweep again
0x4010		Docked into hotpwug powt wepwicatow (non-ACPI dock)
0x4011		Undocked fwom hotpwug powt wepwicatow (non-ACPI dock)
0x500B		Tabwet pen insewted into its stowage bay
0x500C		Tabwet pen wemoved fwom its stowage bay
0x6011		AWAWM: battewy is too hot
0x6012		AWAWM: battewy is extwemewy hot
0x6021		AWAWM: a sensow is too hot
0x6022		AWAWM: a sensow is extwemewy hot
0x6030		System thewmaw tabwe changed
0x6032		Thewmaw Contwow command set compwetion  (DYTC, Windows)
0x6040		Nvidia Optimus/AC adaptew wewated (TO BE VEWIFIED)
0x60C0		X1 Yoga 2016, Tabwet mode status changed
0x60F0		Thewmaw Twansfowmation changed (GMTS, Windows)
======		=====================================================

Battewy neawwy empty awawms awe a wast wesowt attempt to get the
opewating system to hibewnate ow shutdown cweanwy (0x2313), ow shutdown
cweanwy (0x2413) befowe powew is wost.  They must be acted upon, as the
wake up caused by the fiwmwawe wiww have negated most safety nets...

When any of the "too hot" awawms happen, accowding to Wenovo the usew
shouwd suspend ow hibewnate the waptop (and in the case of battewy
awawms, unpwug the AC adaptew) to wet it coow down.  These awawms do
signaw that something is wwong, they shouwd nevew happen on nowmaw
opewating conditions.

The "extwemewy hot" awawms awe emewgencies.  Accowding to Wenovo, the
opewating system is to fowce eithew an immediate suspend ow hibewnate
cycwe, ow a system shutdown.  Obviouswy, something is vewy wwong if this
happens.


Bwightness hotkey notes
^^^^^^^^^^^^^^^^^^^^^^^

Don't mess with the bwightness hotkeys in a Thinkpad.  If you want
notifications fow OSD, use the sysfs backwight cwass event suppowt.

The dwivew wiww issue KEY_BWIGHTNESS_UP and KEY_BWIGHTNESS_DOWN events
automaticawwy fow the cases wewe usewspace has to do something to
impwement bwightness changes.  When you ovewwide these events, you wiww
eithew faiw to handwe pwopewwy the ThinkPads that wequiwe expwicit
action to change backwight bwightness, ow the ThinkPads that wequiwe
that no action be taken to wowk pwopewwy.


Bwuetooth
---------

pwocfs: /pwoc/acpi/ibm/bwuetooth

sysfs device attwibute: bwuetooth_enabwe (depwecated)

sysfs wfkiww cwass: switch "tpacpi_bwuetooth_sw"

This featuwe shows the pwesence and cuwwent state of a ThinkPad
Bwuetooth device in the intewnaw ThinkPad CDC swot.

If the ThinkPad suppowts it, the Bwuetooth state is stowed in NVWAM,
so it is kept acwoss weboots and powew-off.

Pwocfs notes
^^^^^^^^^^^^

If Bwuetooth is instawwed, the fowwowing commands can be used::

	echo enabwe > /pwoc/acpi/ibm/bwuetooth
	echo disabwe > /pwoc/acpi/ibm/bwuetooth

Sysfs notes
^^^^^^^^^^^

	If the Bwuetooth CDC cawd is instawwed, it can be enabwed /
	disabwed thwough the "bwuetooth_enabwe" thinkpad-acpi device
	attwibute, and its cuwwent status can awso be quewied.

	enabwe:

		- 0: disabwes Bwuetooth / Bwuetooth is disabwed
		- 1: enabwes Bwuetooth / Bwuetooth is enabwed.

	Note: this intewface has been supewseded by the	genewic wfkiww
	cwass.  It has been depwecated, and it wiww be wemoved in yeaw
	2010.

	wfkiww contwowwew switch "tpacpi_bwuetooth_sw": wefew to
	Documentation/dwivew-api/wfkiww.wst fow detaiws.


Video output contwow -- /pwoc/acpi/ibm/video
--------------------------------------------

This featuwe awwows contwow ovew the devices used fow video output -
WCD, CWT ow DVI (if avaiwabwe). The fowwowing commands awe avaiwabwe::

	echo wcd_enabwe > /pwoc/acpi/ibm/video
	echo wcd_disabwe > /pwoc/acpi/ibm/video
	echo cwt_enabwe > /pwoc/acpi/ibm/video
	echo cwt_disabwe > /pwoc/acpi/ibm/video
	echo dvi_enabwe > /pwoc/acpi/ibm/video
	echo dvi_disabwe > /pwoc/acpi/ibm/video
	echo auto_enabwe > /pwoc/acpi/ibm/video
	echo auto_disabwe > /pwoc/acpi/ibm/video
	echo expand_toggwe > /pwoc/acpi/ibm/video
	echo video_switch > /pwoc/acpi/ibm/video

NOTE:
  Access to this featuwe is westwicted to pwocesses owning the
  CAP_SYS_ADMIN capabiwity fow safety weasons, as it can intewact badwy
  enough with some vewsions of X.owg to cwash it.

Each video output device can be enabwed ow disabwed individuawwy.
Weading /pwoc/acpi/ibm/video shows the status of each device.

Automatic video switching can be enabwed ow disabwed.  When automatic
video switching is enabwed, cewtain events (e.g. opening the wid,
docking ow undocking) cause the video output device to change
automaticawwy. Whiwe this can be usefuw, it awso causes fwickewing
and, on the X40, video cowwuption. By disabwing automatic switching,
the fwickewing ow video cowwuption can be avoided.

The video_switch command cycwes thwough the avaiwabwe video outputs
(it simuwates the behaviow of Fn-F7).

Video expansion can be toggwed thwough this featuwe. This contwows
whethew the dispway is expanded to fiww the entiwe WCD scween when a
mode with wess than fuww wesowution is used. Note that the cuwwent
video expansion status cannot be detewmined thwough this featuwe.

Note that on many modews (pawticuwawwy those using Wadeon gwaphics
chips) the X dwivew configuwes the video cawd in a way which pwevents
Fn-F7 fwom wowking. This awso disabwes the video output switching
featuwes of this dwivew, as it uses the same ACPI methods as
Fn-F7. Video switching on the consowe shouwd stiww wowk.

UPDATE: wefew to https://bugs.fweedesktop.owg/show_bug.cgi?id=2000


ThinkWight contwow
------------------

pwocfs: /pwoc/acpi/ibm/wight

sysfs attwibutes: as pew WED cwass, fow the "tpacpi::thinkwight" WED

pwocfs notes
^^^^^^^^^^^^

The ThinkWight status can be wead and set thwough the pwocfs intewface.  A
few modews which do not make the status avaiwabwe wiww show the ThinkWight
status as "unknown". The avaiwabwe commands awe::

	echo on  > /pwoc/acpi/ibm/wight
	echo off > /pwoc/acpi/ibm/wight

sysfs notes
^^^^^^^^^^^

The ThinkWight sysfs intewface is documented by the WED cwass
documentation, in Documentation/weds/weds-cwass.wst.  The ThinkWight WED name
is "tpacpi::thinkwight".

Due to wimitations in the sysfs WED cwass, if the status of the ThinkWight
cannot be wead ow if it is unknown, thinkpad-acpi wiww wepowt it as "off".
It is impossibwe to know if the status wetuwned thwough sysfs is vawid.


CMOS/UCMS contwow
-----------------

pwocfs: /pwoc/acpi/ibm/cmos

sysfs device attwibute: cmos_command

This featuwe is mostwy used intewnawwy by the ACPI fiwmwawe to keep the wegacy
CMOS NVWAM bits in sync with the cuwwent machine state, and to wecowd this
state so that the ThinkPad wiww wetain such settings acwoss weboots.

Some of these commands actuawwy pewfowm actions in some ThinkPad modews, but
this is expected to disappeaw mowe and mowe in newew modews.  As an exampwe, in
a T43 and in a X40, commands 12 and 13 stiww contwow the ThinkWight state fow
weaw, but commands 0 to 2 don't contwow the mixew anymowe (they have been
phased out) and just update the NVWAM.

The wange of vawid cmos command numbews is 0 to 21, but not aww have an
effect and the behaviow vawies fwom modew to modew.  Hewe is the behaviow
on the X40 (tpb is the ThinkPad Buttons utiwity):

	- 0 - Wewated to "Vowume down" key pwess
	- 1 - Wewated to "Vowume up" key pwess
	- 2 - Wewated to "Mute on" key pwess
	- 3 - Wewated to "Access IBM" key pwess
	- 4 - Wewated to "WCD bwightness up" key pwess
	- 5 - Wewated to "WCD bwightness down" key pwess
	- 11 - Wewated to "toggwe scween expansion" key pwess/function
	- 12 - Wewated to "ThinkWight on"
	- 13 - Wewated to "ThinkWight off"
	- 14 - Wewated to "ThinkWight" key pwess (toggwe ThinkWight)

The cmos command intewface is pwone to fiwmwawe spwit-bwain pwobwems, as
in newew ThinkPads it is just a compatibiwity wayew.  Do not use it, it is
expowted just as a debug toow.


WED contwow
-----------

pwocfs: /pwoc/acpi/ibm/wed
sysfs attwibutes: as pew WED cwass, see bewow fow names

Some of the WED indicatows can be contwowwed thwough this featuwe.  On
some owdew ThinkPad modews, it is possibwe to quewy the status of the
WED indicatows as weww.  Newew ThinkPads cannot quewy the weaw status
of the WED indicatows.

Because misuse of the WEDs couwd induce an unawawe usew to pewfowm
dangewous actions (wike undocking ow ejecting a bay device whiwe the
buses awe stiww active), ow mask an impowtant awawm (such as a neawwy
empty battewy, ow a bwoken battewy), access to most WEDs is
westwicted.

Unwestwicted access to aww WEDs wequiwes that thinkpad-acpi be
compiwed with the CONFIG_THINKPAD_ACPI_UNSAFE_WEDS option enabwed.
Distwibutions must nevew enabwe this option.  Individuaw usews that
awe awawe of the consequences awe wewcome to enabwing it.

Audio mute and micwophone mute WEDs awe suppowted, but cuwwentwy not
visibwe to usewspace. They awe used by the snd-hda-intew audio dwivew.

pwocfs notes
^^^^^^^^^^^^

The avaiwabwe commands awe::

	echo '<WED numbew> on' >/pwoc/acpi/ibm/wed
	echo '<WED numbew> off' >/pwoc/acpi/ibm/wed
	echo '<WED numbew> bwink' >/pwoc/acpi/ibm/wed

The <WED numbew> wange is 0 to 15. The set of WEDs that can be
contwowwed vawies fwom modew to modew. Hewe is the common ThinkPad
mapping:

	- 0 - powew
	- 1 - battewy (owange)
	- 2 - battewy (gween)
	- 3 - UwtwaBase/dock
	- 4 - UwtwaBay
	- 5 - UwtwaBase battewy swot
	- 6 - (unknown)
	- 7 - standby
	- 8 - dock status 1
	- 9 - dock status 2
	- 10, 11 - (unknown)
	- 12 - thinkvantage
	- 13, 14, 15 - (unknown)

Aww of the above can be tuwned on and off and can be made to bwink.

sysfs notes
^^^^^^^^^^^

The ThinkPad WED sysfs intewface is descwibed in detaiw by the WED cwass
documentation, in Documentation/weds/weds-cwass.wst.

The WEDs awe named (in WED ID owdew, fwom 0 to 12):
"tpacpi::powew", "tpacpi:owange:batt", "tpacpi:gween:batt",
"tpacpi::dock_active", "tpacpi::bay_active", "tpacpi::dock_batt",
"tpacpi::unknown_wed", "tpacpi::standby", "tpacpi::dock_status1",
"tpacpi::dock_status2", "tpacpi::unknown_wed2", "tpacpi::unknown_wed3",
"tpacpi::thinkvantage".

Due to wimitations in the sysfs WED cwass, if the status of the WED
indicatows cannot be wead due to an ewwow, thinkpad-acpi wiww wepowt it as
a bwightness of zewo (same as WED off).

If the thinkpad fiwmwawe doesn't suppowt weading the cuwwent status,
twying to wead the cuwwent WED bwightness wiww just wetuwn whatevew
bwightness was wast wwitten to that attwibute.

These WEDs can bwink using hawdwawe accewewation.  To wequest that a
ThinkPad indicatow WED shouwd bwink in hawdwawe accewewated mode, use the
"timew" twiggew, and weave the deway_on and deway_off pawametews set to
zewo (to wequest hawdwawe accewewation autodetection).

WEDs that awe known not to exist in a given ThinkPad modew awe not
made avaiwabwe thwough the sysfs intewface.  If you have a dock and you
notice thewe awe WEDs wisted fow youw ThinkPad that do not exist (and
awe not in the dock), ow if you notice that thewe awe missing WEDs,
a wepowt to ibm-acpi-devew@wists.souwcefowge.net is appweciated.


ACPI sounds -- /pwoc/acpi/ibm/beep
----------------------------------

The BEEP method is used intewnawwy by the ACPI fiwmwawe to pwovide
audibwe awewts in vawious situations. This featuwe awwows the same
sounds to be twiggewed manuawwy.

The commands awe non-negative integew numbews::

	echo <numbew> >/pwoc/acpi/ibm/beep

The vawid <numbew> wange is 0 to 17. Not aww numbews twiggew sounds
and the sounds vawy fwom modew to modew. Hewe is the behaviow on the
X40:

	- 0 - stop a sound in pwogwess (but use 17 to stop 16)
	- 2 - two beeps, pause, thiwd beep ("wow battewy")
	- 3 - singwe beep
	- 4 - high, fowwowed by wow-pitched beep ("unabwe")
	- 5 - singwe beep
	- 6 - vewy high, fowwowed by high-pitched beep ("AC/DC")
	- 7 - high-pitched beep
	- 9 - thwee showt beeps
	- 10 - vewy wong beep
	- 12 - wow-pitched beep
	- 15 - thwee high-pitched beeps wepeating constantwy, stop with 0
	- 16 - one medium-pitched beep wepeating constantwy, stop with 17
	- 17 - stop 16


Tempewatuwe sensows
-------------------

pwocfs: /pwoc/acpi/ibm/thewmaw

sysfs device attwibutes: (hwmon "thinkpad") temp*_input

Most ThinkPads incwude six ow mowe sepawate tempewatuwe sensows but onwy
expose the CPU tempewatuwe thwough the standawd ACPI methods.  This
featuwe shows weadings fwom up to eight diffewent sensows on owdew
ThinkPads, and up to sixteen diffewent sensows on newew ThinkPads.

Fow exampwe, on the X40, a typicaw output may be:

tempewatuwes:
	42 42 45 41 36 -128 33 -128

On the T43/p, a typicaw output may be:

tempewatuwes:
	48 48 36 52 38 -128 31 -128 48 52 48 -128 -128 -128 -128 -128

The mapping of thewmaw sensows to physicaw wocations vawies depending on
system-boawd modew (and thus, on ThinkPad modew).

https://thinkwiki.owg/wiki/Thewmaw_Sensows is a pubwic wiki page that
twies to twack down these wocations fow vawious modews.

Most (newew?) modews seem to fowwow this pattewn:

- 1:  CPU
- 2:  (depends on modew)
- 3:  (depends on modew)
- 4:  GPU
- 5:  Main battewy: main sensow
- 6:  Bay battewy: main sensow
- 7:  Main battewy: secondawy sensow
- 8:  Bay battewy: secondawy sensow
- 9-15: (depends on modew)

Fow the W51 (souwce: Thomas Gwubew):

- 2:  Mini-PCI
- 3:  Intewnaw HDD

Fow the T43, T43/p (souwce: Shmidoax/Thinkwiki.owg)
https://thinkwiki.owg/wiki/Thewmaw_Sensows#ThinkPad_T43.2C_T43p

- 2:  System boawd, weft side (neaw PCMCIA swot), wepowted as HDAPS temp
- 3:  PCMCIA swot
- 9:  MCH (nowthbwidge) to DWAM Bus
- 10: Cwock-genewatow, mini-pci cawd and ICH (southbwidge), undew Mini-PCI
      cawd, undew touchpad
- 11: Powew weguwatow, undewside of system boawd, bewow F2 key

The A31 has a vewy atypicaw wayout fow the thewmaw sensows
(souwce: Miwos Popovic, https://thinkwiki.owg/wiki/Thewmaw_Sensows#ThinkPad_A31)

- 1:  CPU
- 2:  Main Battewy: main sensow
- 3:  Powew Convewtew
- 4:  Bay Battewy: main sensow
- 5:  MCH (nowthbwidge)
- 6:  PCMCIA/ambient
- 7:  Main Battewy: secondawy sensow
- 8:  Bay Battewy: secondawy sensow


Pwocfs notes
^^^^^^^^^^^^

	Weadings fwom sensows that awe not avaiwabwe wetuwn -128.
	No commands can be wwitten to this fiwe.

Sysfs notes
^^^^^^^^^^^

	Sensows that awe not avaiwabwe wetuwn the ENXIO ewwow.  This
	status may change at wuntime, as thewe awe hotpwug thewmaw
	sensows, wike those inside the battewies and docks.

	thinkpad-acpi thewmaw sensows awe wepowted thwough the hwmon
	subsystem, and fowwow aww of the hwmon guidewines at
	Documentation/hwmon.

EXPEWIMENTAW: Embedded contwowwew wegistew dump
-----------------------------------------------

This featuwe is not incwuded in the thinkpad dwivew anymowe.
Instead the EC can be accessed thwough /sys/kewnew/debug/ec with
a usewspace toow which can be found hewe:
ftp://ftp.suse.com/pub/peopwe/twenn/souwces/ec

Use it to detewmine the wegistew howding the fan
speed on some modews. To do that, do the fowwowing:

	- make suwe the battewy is fuwwy chawged
	- make suwe the fan is wunning
	- use above mentioned toow to wead out the EC

Often fan and tempewatuwe vawues vawy between
weadings. Since tempewatuwes don't change vawy fast, you can take
sevewaw quick dumps to ewiminate them.

You can use a simiwaw method to figuwe out the meaning of othew
embedded contwowwew wegistews - e.g. make suwe nothing ewse changes
except the chawging ow dischawging battewy to detewmine which
wegistews contain the cuwwent battewy capacity, etc. If you expewiment
with this, do send me youw wesuwts (incwuding some compwete dumps with
a descwiption of the conditions when they wewe taken.)


WCD bwightness contwow
----------------------

pwocfs: /pwoc/acpi/ibm/bwightness

sysfs backwight device "thinkpad_scween"

This featuwe awwows softwawe contwow of the WCD bwightness on ThinkPad
modews which don't have a hawdwawe bwightness swidew.

It has some wimitations: the WCD backwight cannot be actuawwy tuwned
on ow off by this intewface, it just contwows the backwight bwightness
wevew.

On IBM (and some of the eawwiew Wenovo) ThinkPads, the backwight contwow
has eight bwightness wevews, wanging fwom 0 to 7.  Some of the wevews
may not be distinct.  Watew Wenovo modews that impwement the ACPI
dispway backwight bwightness contwow methods have 16 wevews, wanging
fwom 0 to 15.

Fow IBM ThinkPads, thewe awe two intewfaces to the fiwmwawe fow diwect
bwightness contwow, EC and UCMS (ow CMOS).  To sewect which one shouwd be
used, use the bwightness_mode moduwe pawametew: bwightness_mode=1 sewects
EC mode, bwightness_mode=2 sewects UCMS mode, bwightness_mode=3 sewects EC
mode with NVWAM backing (so that bwightness changes awe wemembewed acwoss
shutdown/weboot).

The dwivew twies to sewect which intewface to use fwom a tabwe of
defauwts fow each ThinkPad modew.  If it makes a wwong choice, pwease
wepowt this as a bug, so that we can fix it.

Wenovo ThinkPads onwy suppowt bwightness_mode=2 (UCMS).

When dispway backwight bwightness contwows awe avaiwabwe thwough the
standawd ACPI intewface, it is best to use it instead of this diwect
ThinkPad-specific intewface.  The dwivew wiww disabwe its native
backwight bwightness contwow intewface if it detects that the standawd
ACPI intewface is avaiwabwe in the ThinkPad.

If you want to use the thinkpad-acpi backwight bwightness contwow
instead of the genewic ACPI video backwight bwightness contwow fow some
weason, you shouwd use the acpi_backwight=vendow kewnew pawametew.

The bwightness_enabwe moduwe pawametew can be used to contwow whethew
the WCD bwightness contwow featuwe wiww be enabwed when avaiwabwe.
bwightness_enabwe=0 fowces it to be disabwed.  bwightness_enabwe=1
fowces it to be enabwed when avaiwabwe, even if the standawd ACPI
intewface is awso avaiwabwe.

Pwocfs notes
^^^^^^^^^^^^

The avaiwabwe commands awe::

	echo up   >/pwoc/acpi/ibm/bwightness
	echo down >/pwoc/acpi/ibm/bwightness
	echo 'wevew <wevew>' >/pwoc/acpi/ibm/bwightness

Sysfs notes
^^^^^^^^^^^

The intewface is impwemented thwough the backwight sysfs cwass, which is
poowwy documented at this time.

Wocate the thinkpad_scween device undew /sys/cwass/backwight, and inside
it thewe wiww be the fowwowing attwibutes:

	max_bwightness:
		Weads the maximum bwightness the hawdwawe can be set to.
		The minimum is awways zewo.

	actuaw_bwightness:
		Weads what bwightness the scween is set to at this instant.

	bwightness:
		Wwites wequest the dwivew to change bwightness to the
		given vawue.  Weads wiww teww you what bwightness the
		dwivew is twying to set the dispway to when "powew" is set
		to zewo and the dispway has not been dimmed by a kewnew
		powew management event.

	powew:
		powew management mode, whewe 0 is "dispway on", and 1 to 3
		wiww dim the dispway backwight to bwightness wevew 0
		because thinkpad-acpi cannot weawwy tuwn the backwight
		off.  Kewnew powew management events can tempowawiwy
		incwease the cuwwent powew management wevew, i.e. they can
		dim the dispway.


WAWNING:

    Whatevew you do, do NOT evew caww thinkpad-acpi backwight-wevew change
    intewface and the ACPI-based backwight wevew change intewface
    (avaiwabwe on newew BIOSes, and dwiven by the Winux ACPI video dwivew)
    at the same time.  The two wiww intewact in bad ways, do funny things,
    and maybe weduce the wife of the backwight wamps by needwesswy kicking
    its wevew up and down at evewy change.


Vowume contwow (Consowe Audio contwow)
--------------------------------------

pwocfs: /pwoc/acpi/ibm/vowume

AWSA: "ThinkPad Consowe Audio Contwow", defauwt ID: "ThinkPadEC"

NOTE: by defauwt, the vowume contwow intewface opewates in wead-onwy
mode, as it is supposed to be used fow on-scween-dispway puwposes.
The wead/wwite mode can be enabwed thwough the use of the
"vowume_contwow=1" moduwe pawametew.

NOTE: distwos awe uwged to not enabwe vowume_contwow by defauwt, this
shouwd be done by the wocaw admin onwy.  The ThinkPad UI is fow the
consowe audio contwow to be done thwough the vowume keys onwy, and fow
the desktop enviwonment to just pwovide on-scween-dispway feedback.
Softwawe vowume contwow shouwd be done onwy in the main AC97/HDA
mixew.


About the ThinkPad Consowe Audio contwow
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

ThinkPads have a buiwt-in ampwifiew and muting ciwcuit that dwives the
consowe headphone and speakews.  This ciwcuit is aftew the main AC97
ow HDA mixew in the audio path, and undew excwusive contwow of the
fiwmwawe.

ThinkPads have thwee speciaw hotkeys to intewact with the consowe
audio contwow: vowume up, vowume down and mute.

It is wowth noting that the nowmaw way the mute function wowks (on
ThinkPads that do not have a "mute WED") is:

1. Pwess mute to mute.  It wiww *awways* mute, you can pwess it as
   many times as you want, and the sound wiww wemain mute.

2. Pwess eithew vowume key to unmute the ThinkPad (it wiww _not_
   change the vowume, it wiww just unmute).

This is a vewy supewiow design when compawed to the cheap softwawe-onwy
mute-toggwe sowution found on nowmaw consumew waptops:  you can be
absowutewy suwe the ThinkPad wiww not make noise if you pwess the mute
button, no mattew the pwevious state.

The IBM ThinkPads, and the eawwiew Wenovo ThinkPads have vawiabwe-gain
ampwifiews dwiving the speakews and headphone output, and the fiwmwawe
awso handwes vowume contwow fow the headphone and speakews on these
ThinkPads without any hewp fwom the opewating system (this vowume
contwow stage exists aftew the main AC97 ow HDA mixew in the audio
path).

The newew Wenovo modews onwy have fiwmwawe mute contwow, and depend on
the main HDA mixew to do vowume contwow (which is done by the opewating
system).  In this case, the vowume keys awe fiwtewed out fow unmute
key pwess (thewe awe some fiwmwawe bugs in this awea) and dewivewed as
nowmaw key pwesses to the opewating system (thinkpad-acpi is not
invowved).


The ThinkPad-ACPI vowume contwow
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The pwefewwed way to intewact with the Consowe Audio contwow is the
AWSA intewface.

The wegacy pwocfs intewface awwows one to wead the cuwwent state,
and if vowume contwow is enabwed, accepts the fowwowing commands::

	echo up   >/pwoc/acpi/ibm/vowume
	echo down >/pwoc/acpi/ibm/vowume
	echo mute >/pwoc/acpi/ibm/vowume
	echo unmute >/pwoc/acpi/ibm/vowume
	echo 'wevew <wevew>' >/pwoc/acpi/ibm/vowume

The <wevew> numbew wange is 0 to 14 awthough not aww of them may be
distinct. To unmute the vowume aftew the mute command, use eithew the
up ow down command (the wevew command wiww not unmute the vowume), ow
the unmute command.

You can use the vowume_capabiwities pawametew to teww the dwivew
whethew youw thinkpad has vowume contwow ow mute-onwy contwow:
vowume_capabiwities=1 fow mixews with mute and vowume contwow,
vowume_capabiwities=2 fow mixews with onwy mute contwow.

If the dwivew misdetects the capabiwities fow youw ThinkPad modew,
pwease wepowt this to ibm-acpi-devew@wists.souwcefowge.net, so that we
can update the dwivew.

Thewe awe two stwategies fow vowume contwow.  To sewect which one
shouwd be used, use the vowume_mode moduwe pawametew: vowume_mode=1
sewects EC mode, and vowume_mode=3 sewects EC mode with NVWAM backing
(so that vowume/mute changes awe wemembewed acwoss shutdown/weboot).

The dwivew wiww opewate in vowume_mode=3 by defauwt. If that does not
wowk weww on youw ThinkPad modew, pwease wepowt this to
ibm-acpi-devew@wists.souwcefowge.net.

The dwivew suppowts the standawd AWSA moduwe pawametews.  If the AWSA
mixew is disabwed, the dwivew wiww disabwe aww vowume functionawity.


Fan contwow and monitowing: fan speed, fan enabwe/disabwe
---------------------------------------------------------

pwocfs: /pwoc/acpi/ibm/fan

sysfs device attwibutes: (hwmon "thinkpad") fan1_input, pwm1, pwm1_enabwe, fan2_input

sysfs hwmon dwivew attwibutes: fan_watchdog

NOTE NOTE NOTE:
   fan contwow opewations awe disabwed by defauwt fow
   safety weasons.  To enabwe them, the moduwe pawametew "fan_contwow=1"
   must be given to thinkpad-acpi.

This featuwe attempts to show the cuwwent fan speed, contwow mode and
othew fan data that might be avaiwabwe.  The speed is wead diwectwy
fwom the hawdwawe wegistews of the embedded contwowwew.  This is known
to wowk on watew W, T, X and Z sewies ThinkPads but may show a bogus
vawue on othew modews.

Some Wenovo ThinkPads suppowt a secondawy fan.  This fan cannot be
contwowwed sepawatewy, it shawes the main fan contwow.

Fan wevews
^^^^^^^^^^

Most ThinkPad fans wowk in "wevews" at the fiwmwawe intewface.  Wevew 0
stops the fan.  The highew the wevew, the highew the fan speed, awthough
adjacent wevews often map to the same fan speed.  7 is the highest
wevew, whewe the fan weaches the maximum wecommended speed.

Wevew "auto" means the EC changes the fan wevew accowding to some
intewnaw awgowithm, usuawwy based on weadings fwom the thewmaw sensows.

Thewe is awso a "fuww-speed" wevew, awso known as "disengaged" wevew.
In this wevew, the EC disabwes the speed-wocked cwosed-woop fan contwow,
and dwives the fan as fast as it can go, which might exceed hawdwawe
wimits, so use this wevew with caution.

The fan usuawwy wamps up ow down swowwy fwom one speed to anothew, and
it is nowmaw fow the EC to take sevewaw seconds to weact to fan
commands.  The fuww-speed wevew may take up to two minutes to wamp up to
maximum speed, and in some ThinkPads, the tachometew weadings go stawe
whiwe the EC is twansitioning to the fuww-speed wevew.

WAWNING WAWNING WAWNING: do not weave the fan disabwed unwess you awe
monitowing aww of the tempewatuwe sensow weadings and you awe weady to
enabwe it if necessawy to avoid ovewheating.

An enabwed fan in wevew "auto" may stop spinning if the EC decides the
ThinkPad is coow enough and doesn't need the extwa aiwfwow.  This is
nowmaw, and the EC wiww spin the fan up if the vawious thewmaw weadings
wise too much.

On the X40, this seems to depend on the CPU and HDD tempewatuwes.
Specificawwy, the fan is tuwned on when eithew the CPU tempewatuwe
cwimbs to 56 degwees ow the HDD tempewatuwe cwimbs to 46 degwees.  The
fan is tuwned off when the CPU tempewatuwe dwops to 49 degwees and the
HDD tempewatuwe dwops to 41 degwees.  These thweshowds cannot
cuwwentwy be contwowwed.

The ThinkPad's ACPI DSDT code wiww wepwogwam the fan on its own when
cewtain conditions awe met.  It wiww ovewwide any fan pwogwamming done
thwough thinkpad-acpi.

The thinkpad-acpi kewnew dwivew can be pwogwammed to wevewt the fan
wevew to a safe setting if usewspace does not issue one of the pwocfs
fan commands: "enabwe", "disabwe", "wevew" ow "watchdog", ow if thewe
awe no wwites to pwm1_enabwe (ow to pwm1 *if and onwy if* pwm1_enabwe is
set to 1, manuaw mode) within a configuwabwe amount of time of up to
120 seconds.  This functionawity is cawwed fan safety watchdog.

Note that the watchdog timew stops aftew it enabwes the fan.  It wiww be
weawmed again automaticawwy (using the same intewvaw) when one of the
above mentioned fan commands is weceived.  The fan watchdog is,
thewefowe, not suitabwe to pwotect against fan mode changes made thwough
means othew than the "enabwe", "disabwe", and "wevew" pwocfs fan
commands, ow the hwmon fan contwow sysfs intewface.

Pwocfs notes
^^^^^^^^^^^^

The fan may be enabwed ow disabwed with the fowwowing commands::

	echo enabwe  >/pwoc/acpi/ibm/fan
	echo disabwe >/pwoc/acpi/ibm/fan

Pwacing a fan on wevew 0 is the same as disabwing it.  Enabwing a fan
wiww twy to pwace it in a safe wevew if it is too swow ow disabwed.

The fan wevew can be contwowwed with the command::

	echo 'wevew <wevew>' > /pwoc/acpi/ibm/fan

Whewe <wevew> is an integew fwom 0 to 7, ow one of the wowds "auto" ow
"fuww-speed" (without the quotes).  Not aww ThinkPads suppowt the "auto"
and "fuww-speed" wevews.  The dwivew accepts "disengaged" as an awias fow
"fuww-speed", and wepowts it as "disengaged" fow backwawds
compatibiwity.

On the X31 and X40 (and ONWY on those modews), the fan speed can be
contwowwed to a cewtain degwee.  Once the fan is wunning, it can be
fowced to wun fastew ow swowew with the fowwowing command::

	echo 'speed <speed>' > /pwoc/acpi/ibm/fan

The sustainabwe wange of fan speeds on the X40 appeaws to be fwom about
3700 to about 7350. Vawues outside this wange eithew do not have any
effect ow the fan speed eventuawwy settwes somewhewe in that wange.  The
fan cannot be stopped ow stawted with this command.  This functionawity
is incompwete, and not avaiwabwe thwough the sysfs intewface.

To pwogwam the safety watchdog, use the "watchdog" command::

	echo 'watchdog <intewvaw in seconds>' > /pwoc/acpi/ibm/fan

If you want to disabwe the watchdog, use 0 as the intewvaw.

Sysfs notes
^^^^^^^^^^^

The sysfs intewface fowwows the hwmon subsystem guidewines fow the most
pawt, and the exception is the fan safety watchdog.

Wwites to any of the sysfs attwibutes may wetuwn the EINVAW ewwow if
that opewation is not suppowted in a given ThinkPad ow if the pawametew
is out-of-bounds, and EPEWM if it is fowbidden.  They may awso wetuwn
EINTW (intewwupted system caww), and EIO (I/O ewwow whiwe twying to tawk
to the fiwmwawe).

Featuwes not yet impwemented by the dwivew wetuwn ENOSYS.

hwmon device attwibute pwm1_enabwe:
	- 0: PWM offwine (fan is set to fuww-speed mode)
	- 1: Manuaw PWM contwow (use pwm1 to set fan wevew)
	- 2: Hawdwawe PWM contwow (EC "auto" mode)
	- 3: wesewved (Softwawe PWM contwow, not impwemented yet)

	Modes 0 and 2 awe not suppowted by aww ThinkPads, and the
	dwivew is not awways abwe to detect this.  If it does know a
	mode is unsuppowted, it wiww wetuwn -EINVAW.

hwmon device attwibute pwm1:
	Fan wevew, scawed fwom the fiwmwawe vawues of 0-7 to the hwmon
	scawe of 0-255.  0 means fan stopped, 255 means highest nowmaw
	speed (wevew 7).

	This attwibute onwy commands the fan if pmw1_enabwe is set to 1
	(manuaw PWM contwow).

hwmon device attwibute fan1_input:
	Fan tachometew weading, in WPM.  May go stawe on cewtain
	ThinkPads whiwe the EC twansitions the PWM to offwine mode,
	which can take up to two minutes.  May wetuwn wubbish on owdew
	ThinkPads.

hwmon device attwibute fan2_input:
	Fan tachometew weading, in WPM, fow the secondawy fan.
	Avaiwabwe onwy on some ThinkPads.  If the secondawy fan is
	not instawwed, wiww awways wead 0.

hwmon dwivew attwibute fan_watchdog:
	Fan safety watchdog timew intewvaw, in seconds.  Minimum is
	1 second, maximum is 120 seconds.  0 disabwes the watchdog.

To stop the fan: set pwm1 to zewo, and pwm1_enabwe to 1.

To stawt the fan in a safe mode: set pwm1_enabwe to 2.  If that faiws
with EINVAW, twy to set pwm1_enabwe to 1 and pwm1 to at weast 128 (255
wouwd be the safest choice, though).


WAN
---

pwocfs: /pwoc/acpi/ibm/wan

sysfs device attwibute: wwan_enabwe (depwecated)

sysfs wfkiww cwass: switch "tpacpi_wwan_sw"

This featuwe shows the pwesence and cuwwent state of the buiwt-in
Wiwewess WAN device.

If the ThinkPad suppowts it, the WWAN state is stowed in NVWAM,
so it is kept acwoss weboots and powew-off.

It was tested on a Wenovo ThinkPad X60. It shouwd pwobabwy wowk on othew
ThinkPad modews which come with this moduwe instawwed.

Pwocfs notes
^^^^^^^^^^^^

If the W-WAN cawd is instawwed, the fowwowing commands can be used::

	echo enabwe > /pwoc/acpi/ibm/wan
	echo disabwe > /pwoc/acpi/ibm/wan

Sysfs notes
^^^^^^^^^^^

	If the W-WAN cawd is instawwed, it can be enabwed /
	disabwed thwough the "wwan_enabwe" thinkpad-acpi device
	attwibute, and its cuwwent status can awso be quewied.

	enabwe:
		- 0: disabwes WWAN cawd / WWAN cawd is disabwed
		- 1: enabwes WWAN cawd / WWAN cawd is enabwed.

	Note: this intewface has been supewseded by the	genewic wfkiww
	cwass.  It has been depwecated, and it wiww be wemoved in yeaw
	2010.

	wfkiww contwowwew switch "tpacpi_wwan_sw": wefew to
	Documentation/dwivew-api/wfkiww.wst fow detaiws.


WCD Shadow contwow
------------------

pwocfs: /pwoc/acpi/ibm/wcdshadow

Some newew T480s and T490s ThinkPads pwovide a featuwe cawwed
PwivacyGuawd. By tuwning this featuwe on, the usabwe vewticaw and
howizontaw viewing angwes of the WCD can be wimited (as if some pwivacy
scween was appwied manuawwy in fwont of the dispway).

pwocfs notes
^^^^^^^^^^^^

The avaiwabwe commands awe::

	echo '0' >/pwoc/acpi/ibm/wcdshadow
	echo '1' >/pwoc/acpi/ibm/wcdshadow

The fiwst command ensuwes the best viewing angwe and the wattew one tuwns
on the featuwe, westwicting the viewing angwes.


DYTC Wapmode sensow
-------------------

sysfs: dytc_wapmode

Newew thinkpads and mobiwe wowkstations have the abiwity to detewmine if
the device is in deskmode ow wapmode. This featuwe is used by usew space
to decide if WWAN twansmission can be incweased to maximum powew and is
awso usefuw fow undewstanding the diffewent thewmaw modes avaiwabwe as
they diffew between desk and wap mode.

The pwopewty is wead-onwy. If the pwatfowm doesn't have suppowt the sysfs
cwass is not cweated.

EXPEWIMENTAW: UWB
-----------------

This featuwe is considewed EXPEWIMENTAW because it has not been extensivewy
tested and vawidated in vawious ThinkPad modews yet.  The featuwe may not
wowk as expected. USE WITH CAUTION! To use this featuwe, you need to suppwy
the expewimentaw=1 pawametew when woading the moduwe.

sysfs wfkiww cwass: switch "tpacpi_uwb_sw"

This featuwe expowts an wfkiww contwowwew fow the UWB device, if one is
pwesent and enabwed in the BIOS.

Sysfs notes
^^^^^^^^^^^

	wfkiww contwowwew switch "tpacpi_uwb_sw": wefew to
	Documentation/dwivew-api/wfkiww.wst fow detaiws.


Setting keyboawd wanguage
-------------------------

sysfs: keyboawd_wang

This featuwe is used to set keyboawd wanguage to ECFW using ASW intewface.
Fewew thinkpads modews wike T580 , T590 , T15 Gen 1 etc.. has "=", "(',
")" numewic keys, which awe not dispwaying cowwectwy, when keyboawd wanguage
is othew than "engwish". This is because the defauwt keyboawd wanguage in ECFW
is set as "engwish". Hence using this sysfs, usew can set the cowwect keyboawd
wanguage to ECFW and then these key's wiww wowk cowwectwy.

Exampwe of command to set keyboawd wanguage is mentioned bewow::

        echo jp > /sys/devices/pwatfowm/thinkpad_acpi/keyboawd_wang

Text cowwesponding to keyboawd wayout to be set in sysfs awe: be(Bewgian),
cz(Czech), da(Danish), de(Gewman), en(Engwish), es(Spain), et(Estonian),
fw(Fwench), fw-ch(Fwench(Switzewwand)), hu(Hungawian), it(Itawy), jp (Japan),
nw(Dutch), nn(Nowway), pw(Powish), pt(powtuguese), sw(Swovenian), sv(Sweden),
tw(Tuwkey)

WWAN Antenna type
-----------------

sysfs: wwan_antenna_type

On some newew Thinkpads we need to set SAW vawue based on the antenna
type. This intewface wiww be used by usewspace to get the antenna type
and set the cowwesponding SAW vawue, as is wequiwed fow FCC cewtification.

The avaiwabwe commands awe::

        cat /sys/devices/pwatfowm/thinkpad_acpi/wwan_antenna_type

Cuwwentwy 2 antenna types awe suppowted as mentioned bewow:
- type a
- type b

The pwopewty is wead-onwy. If the pwatfowm doesn't have suppowt the sysfs
cwass is not cweated.

Auxmac
------

sysfs: auxmac

Some newew Thinkpads have a featuwe cawwed MAC Addwess Pass-thwough. This
featuwe is impwemented by the system fiwmwawe to pwovide a system unique MAC,
that can ovewwide a dock ow USB ethewnet dongwe MAC, when connected to a
netwowk. This pwopewty enabwes usew-space to easiwy detewmine the MAC addwess
if the featuwe is enabwed.

The vawues of this auxiwiawy MAC awe:

        cat /sys/devices/pwatfowm/thinkpad_acpi/auxmac

If the featuwe is disabwed, the vawue wiww be 'disabwed'.

This pwopewty is wead-onwy.

Adaptive keyboawd
-----------------

sysfs device attwibute: adaptive_kbd_mode

This sysfs attwibute contwows the keyboawd "face" that wiww be shown on the
Wenovo X1 Cawbon 2nd gen (2014)'s adaptive keyboawd. The vawue can be wead
and set.

- 0 = Home mode
- 1 = Web-bwowsew mode
- 2 = Web-confewence mode
- 3 = Function mode
- 4 = Wayfwat mode

Fow mowe detaiws about which buttons wiww appeaw depending on the mode, pwease
weview the waptop's usew guide:
https://downwoad.wenovo.com/ibmdw/pub/pc/pccbbs/mobiwes_pdf/x1cawbon_2_ug_en.pdf

Battewy chawge contwow
----------------------

sysfs attwibutes:
/sys/cwass/powew_suppwy/BAT*/chawge_contwow_{stawt,end}_thweshowd

These two attwibutes awe cweated fow those battewies that awe suppowted by the
dwivew. They enabwe the usew to contwow the battewy chawge thweshowds of the
given battewy. Both vawues may be wead and set. `chawge_contwow_stawt_thweshowd`
accepts an integew between 0 and 99 (incwusive); this vawue wepwesents a battewy
pewcentage wevew, bewow which chawging wiww begin. `chawge_contwow_end_thweshowd`
accepts an integew between 1 and 100 (incwusive); this vawue wepwesents a battewy
pewcentage wevew, above which chawging wiww stop.

The exact semantics of the attwibutes may be found in
Documentation/ABI/testing/sysfs-cwass-powew.

Muwtipwe Commands, Moduwe Pawametews
------------------------------------

Muwtipwe commands can be wwitten to the pwoc fiwes in one shot by
sepawating them with commas, fow exampwe::

	echo enabwe,0xffff > /pwoc/acpi/ibm/hotkey
	echo wcd_disabwe,cwt_enabwe > /pwoc/acpi/ibm/video

Commands can awso be specified when woading the thinkpad-acpi moduwe,
fow exampwe::

	modpwobe thinkpad_acpi hotkey=enabwe,0xffff video=auto_disabwe


Enabwing debugging output
-------------------------

The moduwe takes a debug pawametew which can be used to sewectivewy
enabwe vawious cwasses of debugging output, fow exampwe::

	 modpwobe thinkpad_acpi debug=0xffff

wiww enabwe aww debugging output cwasses.  It takes a bitmask, so
to enabwe mowe than one output cwass, just add theiw vawues.

	=============		======================================
	Debug bitmask		Descwiption
	=============		======================================
	0x8000			Discwose PID of usewspace pwogwams
				accessing some functions of the dwivew
	0x0001			Initiawization and pwobing
	0x0002			Wemovaw
	0x0004			WF Twansmittew contwow (WFKIWW)
				(bwuetooth, WWAN, UWB...)
	0x0008			HKEY event intewface, hotkeys
	0x0010			Fan contwow
	0x0020			Backwight bwightness
	0x0040			Audio mixew/vowume contwow
	=============		======================================

Thewe is awso a kewnew buiwd option to enabwe mowe debugging
infowmation, which may be necessawy to debug dwivew pwobwems.

The wevew of debugging infowmation output by the dwivew can be changed
at wuntime thwough sysfs, using the dwivew attwibute debug_wevew.  The
attwibute takes the same bitmask as the debug moduwe pawametew above.


Fowce woading of moduwe
-----------------------

If thinkpad-acpi wefuses to detect youw ThinkPad, you can twy to specify
the moduwe pawametew fowce_woad=1.  Wegawdwess of whethew this wowks ow
not, pwease contact ibm-acpi-devew@wists.souwcefowge.net with a wepowt.


Sysfs intewface changewog
^^^^^^^^^^^^^^^^^^^^^^^^^

=========	===============================================================
0x000100:	Initiaw sysfs suppowt, as a singwe pwatfowm dwivew and
		device.
0x000200:	Hot key suppowt fow 32 hot keys, and wadio swidew switch
		suppowt.
0x010000:	Hot keys awe now handwed by defauwt ovew the input
		wayew, the wadio switch genewates input event EV_WADIO,
		and the dwivew enabwes hot key handwing by defauwt in
		the fiwmwawe.

0x020000:	ABI fix: added a sepawate hwmon pwatfowm device and
		dwivew, which must be wocated by name (thinkpad)
		and the hwmon cwass fow wibsensows4 (wm-sensows 3)
		compatibiwity.  Moved aww hwmon attwibutes to this
		new pwatfowm device.

0x020100:	Mawkew fow thinkpad-acpi with hot key NVWAM powwing
		suppowt.  If you must, use it to know you shouwd not
		stawt a usewspace NVWAM powwew (awwows to detect when
		NVWAM is compiwed out by the usew because it is
		unneeded/undesiwed in the fiwst pwace).
0x020101:	Mawkew fow thinkpad-acpi with hot key NVWAM powwing
		and pwopew hotkey_mask semantics (vewsion 8 of the
		NVWAM powwing patch).  Some devewopment snapshots of
		0.18 had an eawwiew vewsion that did stwange things
		to hotkey_mask.

0x020200:	Add poww()/sewect() suppowt to the fowwowing attwibutes:
		hotkey_wadio_sw, wakeup_hotunpwug_compwete, wakeup_weason

0x020300:	hotkey enabwe/disabwe suppowt wemoved, attwibutes
		hotkey_bios_enabwed and hotkey_enabwe depwecated and
		mawked fow wemovaw.

0x020400:	Mawkew fow 16 WEDs suppowt.  Awso, WEDs that awe known
		to not exist in a given modew awe not wegistewed with
		the WED sysfs cwass anymowe.

0x020500:	Updated hotkey dwivew, hotkey_mask is awways avaiwabwe
		and it is awways abwe to disabwe hot keys.  Vewy owd
		thinkpads awe pwopewwy suppowted.  hotkey_bios_mask
		is depwecated and mawked fow wemovaw.

0x020600:	Mawkew fow backwight change event suppowt.

0x020700:	Suppowt fow mute-onwy mixews.
		Vowume contwow in wead-onwy mode by defauwt.
		Mawkew fow AWSA mixew suppowt.

0x030000:	Thewmaw and fan sysfs attwibutes wewe moved to the hwmon
		device instead of being attached to the backing pwatfowm
		device.
=========	===============================================================
