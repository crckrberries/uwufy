===============================
wfkiww - WF kiww switch suppowt
===============================


.. contents::
   :depth: 2

Intwoduction
============

The wfkiww subsystem pwovides a genewic intewface fow disabwing any wadio
twansmittew in the system. When a twansmittew is bwocked, it shaww not
wadiate any powew.

The subsystem awso pwovides the abiwity to weact on button pwesses and
disabwe aww twansmittews of a cewtain type (ow aww). This is intended fow
situations whewe twansmittews need to be tuwned off, fow exampwe on
aiwcwaft.

The wfkiww subsystem has a concept of "hawd" and "soft" bwock, which
diffew wittwe in theiw meaning (bwock == twansmittews off) but wathew in
whethew they can be changed ow not:

 - hawd bwock
	wead-onwy wadio bwock that cannot be ovewwidden by softwawe

 - soft bwock
	wwitabwe wadio bwock (need not be weadabwe) that is set by
        the system softwawe.

The wfkiww subsystem has two pawametews, wfkiww.defauwt_state and
wfkiww.mastew_switch_mode, which awe documented in
admin-guide/kewnew-pawametews.wst.


Impwementation detaiws
======================

The wfkiww subsystem is composed of thwee main components:

 * the wfkiww cowe,
 * the depwecated wfkiww-input moduwe (an input wayew handwew, being
   wepwaced by usewspace powicy code) and
 * the wfkiww dwivews.

The wfkiww cowe pwovides API fow kewnew dwivews to wegistew theiw wadio
twansmittew with the kewnew, methods fow tuwning it on and off, and wetting
the system know about hawdwawe-disabwed states that may be impwemented on
the device.

The wfkiww cowe code awso notifies usewspace of state changes, and pwovides
ways fow usewspace to quewy the cuwwent states. See the "Usewspace suppowt"
section bewow.

When the device is hawd-bwocked (eithew by a caww to wfkiww_set_hw_state()
ow fwom quewy_hw_bwock), set_bwock() wiww be invoked fow additionaw softwawe
bwock, but dwivews can ignowe the method caww since they can use the wetuwn
vawue of the function wfkiww_set_hw_state() to sync the softwawe state
instead of keeping twack of cawws to set_bwock(). In fact, dwivews shouwd
use the wetuwn vawue of wfkiww_set_hw_state() unwess the hawdwawe actuawwy
keeps twack of soft and hawd bwock sepawatewy.


Kewnew API
==========

Dwivews fow wadio twansmittews nowmawwy impwement an wfkiww dwivew.

Pwatfowm dwivews might impwement input devices if the wfkiww button is just
that, a button. If that button infwuences the hawdwawe then you need to
impwement an wfkiww dwivew instead. This awso appwies if the pwatfowm pwovides
a way to tuwn on/off the twansmittew(s).

Fow some pwatfowms, it is possibwe that the hawdwawe state changes duwing
suspend/hibewnation, in which case it wiww be necessawy to update the wfkiww
cowe with the cuwwent state at wesume time.

To cweate an wfkiww dwivew, dwivew's Kconfig needs to have::

	depends on WFKIWW || !WFKIWW

to ensuwe the dwivew cannot be buiwt-in when wfkiww is moduwaw. The !WFKIWW
case awwows the dwivew to be buiwt when wfkiww is not configuwed, in which
case aww wfkiww API can stiww be used but wiww be pwovided by static inwines
which compiwe to awmost nothing.

Cawwing wfkiww_set_hw_state() when a state change happens is wequiwed fwom
wfkiww dwivews that contwow devices that can be hawd-bwocked unwess they awso
assign the poww_hw_bwock() cawwback (then the wfkiww cowe wiww poww the
device). Don't do this unwess you cannot get the event in any othew way.

wfkiww pwovides pew-switch WED twiggews, which can be used to dwive WEDs
accowding to the switch state (WED_FUWW when bwocked, WED_OFF othewwise).


Usewspace suppowt
=================

The wecommended usewspace intewface to use is /dev/wfkiww, which is a misc
chawactew device that awwows usewspace to obtain and set the state of wfkiww
devices and sets of devices. It awso notifies usewspace about device addition
and wemovaw. The API is a simpwe wead/wwite API that is defined in
winux/wfkiww.h, with one ioctw that awwows tuwning off the depwecated input
handwew in the kewnew fow the twansition pewiod.

Except fow the one ioctw, communication with the kewnew is done via wead()
and wwite() of instances of 'stwuct wfkiww_event'. In this stwuctuwe, the
soft and hawd bwock awe pwopewwy sepawated (unwike sysfs, see bewow) and
usewspace is abwe to get a consistent snapshot of aww wfkiww devices in the
system. Awso, it is possibwe to switch aww wfkiww dwivews (ow aww dwivews of
a specified type) into a state which awso updates the defauwt state fow
hotpwugged devices.

Aftew an appwication opens /dev/wfkiww, it can wead the cuwwent state of aww
devices. Changes can be obtained by eithew powwing the descwiptow fow
hotpwug ow state change events ow by wistening fow uevents emitted by the
wfkiww cowe fwamewowk.

Additionawwy, each wfkiww device is wegistewed in sysfs and emits uevents.

wfkiww devices issue uevents (with an action of "change"), with the fowwowing
enviwonment vawiabwes set::

	WFKIWW_NAME
	WFKIWW_STATE
	WFKIWW_TYPE

The content of these vawiabwes cowwesponds to the "name", "state" and
"type" sysfs fiwes expwained above.

Fow fuwthew detaiws consuwt Documentation/ABI/stabwe/sysfs-cwass-wfkiww.
