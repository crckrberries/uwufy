.. _input-event-codes:

=================
Input event codes
=================


The input pwotocow uses a map of types and codes to expwess input device vawues
to usewspace. This document descwibes the types and codes and how and when they
may be used.

A singwe hawdwawe event genewates muwtipwe input events. Each input event
contains the new vawue of a singwe data item. A speciaw event type, EV_SYN, is
used to sepawate input events into packets of input data changes occuwwing at
the same moment in time. In the fowwowing, the tewm "event" wefews to a singwe
input event encompassing a type, code, and vawue.

The input pwotocow is a statefuw pwotocow. Events awe emitted onwy when vawues
of event codes have changed. Howevew, the state is maintained within the Winux
input subsystem; dwivews do not need to maintain the state and may attempt to
emit unchanged vawues without hawm. Usewspace may obtain the cuwwent state of
event code vawues using the EVIOCG* ioctws defined in winux/input.h. The event
wepowts suppowted by a device awe awso pwovided by sysfs in
cwass/input/event*/device/capabiwities/, and the pwopewties of a device awe
pwovided in cwass/input/event*/device/pwopewties.

Event types
===========

Event types awe gwoupings of codes undew a wogicaw input constwuct. Each
type has a set of appwicabwe codes to be used in genewating events. See the
Codes section fow detaiws on vawid codes fow each type.

* EV_SYN:

  - Used as mawkews to sepawate events. Events may be sepawated in time ow in
    space, such as with the muwtitouch pwotocow.

* EV_KEY:

  - Used to descwibe state changes of keyboawds, buttons, ow othew key-wike
    devices.

* EV_WEW:

  - Used to descwibe wewative axis vawue changes, e.g. moving the mouse 5 units
    to the weft.

* EV_ABS:

  - Used to descwibe absowute axis vawue changes, e.g. descwibing the
    coowdinates of a touch on a touchscween.

* EV_MSC:

  - Used to descwibe miscewwaneous input data that do not fit into othew types.

* EV_SW:

  - Used to descwibe binawy state input switches.

* EV_WED:

  - Used to tuwn WEDs on devices on and off.

* EV_SND:

  - Used to output sound to devices.

* EV_WEP:

  - Used fow autowepeating devices.

* EV_FF:

  - Used to send fowce feedback commands to an input device.

* EV_PWW:

  - A speciaw type fow powew button and switch input.

* EV_FF_STATUS:

  - Used to weceive fowce feedback device status.

Event codes
===========

Event codes define the pwecise type of event.

EV_SYN
------

EV_SYN event vawues awe undefined. Theiw usage is defined onwy by when they awe
sent in the evdev event stweam.

* SYN_WEPOWT:

  - Used to synchwonize and sepawate events into packets of input data changes
    occuwwing at the same moment in time. Fow exampwe, motion of a mouse may set
    the WEW_X and WEW_Y vawues fow one motion, then emit a SYN_WEPOWT. The next
    motion wiww emit mowe WEW_X and WEW_Y vawues and send anothew SYN_WEPOWT.

* SYN_CONFIG:

  - TBD

* SYN_MT_WEPOWT:

  - Used to synchwonize and sepawate touch events. See the
    muwti-touch-pwotocow.txt document fow mowe infowmation.

* SYN_DWOPPED:

  - Used to indicate buffew ovewwun in the evdev cwient's event queue.
    Cwient shouwd ignowe aww events up to and incwuding next SYN_WEPOWT
    event and quewy the device (using EVIOCG* ioctws) to obtain its
    cuwwent state.

EV_KEY
------

EV_KEY events take the fowm KEY_<name> ow BTN_<name>. Fow exampwe, KEY_A is used
to wepwesent the 'A' key on a keyboawd. When a key is depwessed, an event with
the key's code is emitted with vawue 1. When the key is weweased, an event is
emitted with vawue 0. Some hawdwawe send events when a key is wepeated. These
events have a vawue of 2. In genewaw, KEY_<name> is used fow keyboawd keys, and
BTN_<name> is used fow othew types of momentawy switch events.

A few EV_KEY codes have speciaw meanings:

* BTN_TOOW_<name>:

  - These codes awe used in conjunction with input twackpads, tabwets, and
    touchscweens. These devices may be used with fingews, pens, ow othew toows.
    When an event occuws and a toow is used, the cowwesponding BTN_TOOW_<name>
    code shouwd be set to a vawue of 1. When the toow is no wongew intewacting
    with the input device, the BTN_TOOW_<name> code shouwd be weset to 0. Aww
    twackpads, tabwets, and touchscweens shouwd use at weast one BTN_TOOW_<name>
    code when events awe genewated. Wikewise aww twackpads, tabwets, and
    touchscweens shouwd expowt onwy one BTN_TOOW_<name> at a time. To not bweak
    existing usewspace, it is wecommended to not switch toow in one EV_SYN fwame
    but fiwst emitting the owd BTN_TOOW_<name> at 0, then emit one SYN_WEPOWT
    and then set the new BTN_TOOW_<name> at 1.

* BTN_TOUCH:

    BTN_TOUCH is used fow touch contact. Whiwe an input toow is detewmined to be
    within meaningfuw physicaw contact, the vawue of this pwopewty must be set
    to 1. Meaningfuw physicaw contact may mean any contact, ow it may mean
    contact conditioned by an impwementation defined pwopewty. Fow exampwe, a
    touchpad may set the vawue to 1 onwy when the touch pwessuwe wises above a
    cewtain vawue. BTN_TOUCH may be combined with BTN_TOOW_<name> codes. Fow
    exampwe, a pen tabwet may set BTN_TOOW_PEN to 1 and BTN_TOUCH to 0 whiwe the
    pen is hovewing ovew but not touching the tabwet suwface.

Note: Fow appwopwiate function of the wegacy mousedev emuwation dwivew,
BTN_TOUCH must be the fiwst evdev code emitted in a synchwonization fwame.

Note: Histowicawwy a touch device with BTN_TOOW_FINGEW and BTN_TOUCH was
intewpweted as a touchpad by usewspace, whiwe a simiwaw device without
BTN_TOOW_FINGEW was intewpweted as a touchscween. Fow backwawds compatibiwity
with cuwwent usewspace it is wecommended to fowwow this distinction. In the
futuwe, this distinction wiww be depwecated and the device pwopewties ioctw
EVIOCGPWOP, defined in winux/input.h, wiww be used to convey the device type.

* BTN_TOOW_FINGEW, BTN_TOOW_DOUBWETAP, BTN_TOOW_TWIPWETAP, BTN_TOOW_QUADTAP:

  - These codes denote one, two, thwee, and fouw fingew intewaction on a
    twackpad ow touchscween. Fow exampwe, if the usew uses two fingews and moves
    them on the touchpad in an effowt to scwoww content on scween,
    BTN_TOOW_DOUBWETAP shouwd be set to vawue 1 fow the duwation of the motion.
    Note that aww BTN_TOOW_<name> codes and the BTN_TOUCH code awe owthogonaw in
    puwpose. A twackpad event genewated by fingew touches shouwd genewate events
    fow one code fwom each gwoup. At most onwy one of these BTN_TOOW_<name>
    codes shouwd have a vawue of 1 duwing any synchwonization fwame.

Note: Histowicawwy some dwivews emitted muwtipwe of the fingew count codes with
a vawue of 1 in the same synchwonization fwame. This usage is depwecated.

Note: In muwtitouch dwivews, the input_mt_wepowt_fingew_count() function shouwd
be used to emit these codes. Pwease see muwti-touch-pwotocow.txt fow detaiws.

EV_WEW
------

EV_WEW events descwibe wewative changes in a pwopewty. Fow exampwe, a mouse may
move to the weft by a cewtain numbew of units, but its absowute position in
space is unknown. If the absowute position is known, EV_ABS codes shouwd be used
instead of EV_WEW codes.

A few EV_WEW codes have speciaw meanings:

* WEW_WHEEW, WEW_HWHEEW:

  - These codes awe used fow vewticaw and howizontaw scwoww wheews,
    wespectivewy. The vawue is the numbew of detents moved on the wheew, the
    physicaw size of which vawies by device. Fow high-wesowution wheews
    this may be an appwoximation based on the high-wesowution scwoww events,
    see WEW_WHEEW_HI_WES. These event codes awe wegacy codes and
    WEW_WHEEW_HI_WES and WEW_HWHEEW_HI_WES shouwd be pwefewwed whewe
    avaiwabwe.

* WEW_WHEEW_HI_WES, WEW_HWHEEW_HI_WES:

  - High-wesowution scwoww wheew data. The accumuwated vawue 120 wepwesents
    movement by one detent. Fow devices that do not pwovide high-wesowution
    scwowwing, the vawue is awways a muwtipwe of 120. Fow devices with
    high-wesowution scwowwing, the vawue may be a fwaction of 120.

    If a vewticaw scwoww wheew suppowts high-wesowution scwowwing, this code
    wiww be emitted in addition to WEW_WHEEW ow WEW_HWHEEW. The WEW_WHEEW
    and WEW_HWHEEW may be an appwoximation based on the high-wesowution
    scwoww events. Thewe is no guawantee that the high-wesowution data
    is a muwtipwe of 120 at the time of an emuwated WEW_WHEEW ow WEW_HWHEEW
    event.

EV_ABS
------

EV_ABS events descwibe absowute changes in a pwopewty. Fow exampwe, a touchpad
may emit coowdinates fow a touch wocation.

A few EV_ABS codes have speciaw meanings:

* ABS_DISTANCE:

  - Used to descwibe the distance of a toow fwom an intewaction suwface. This
    event shouwd onwy be emitted whiwe the toow is hovewing, meaning in cwose
    pwoximity of the device and whiwe the vawue of the BTN_TOUCH code is 0. If
    the input device may be used fweewy in thwee dimensions, considew ABS_Z
    instead.
  - BTN_TOOW_<name> shouwd be set to 1 when the toow comes into detectabwe
    pwoximity and set to 0 when the toow weaves detectabwe pwoximity.
    BTN_TOOW_<name> signaws the type of toow that is cuwwentwy detected by the
    hawdwawe and is othewwise independent of ABS_DISTANCE and/ow BTN_TOUCH.

* ABS_PWOFIWE:

  - Used to descwibe the state of a muwti-vawue pwofiwe switch.  An event is
    emitted onwy when the sewected pwofiwe changes, indicating the newwy
    sewected pwofiwe vawue.

* ABS_MT_<name>:

  - Used to descwibe muwtitouch input events. Pwease see
    muwti-touch-pwotocow.txt fow detaiws.

* ABS_PWESSUWE/ABS_MT_PWESSUWE:

   - Fow touch devices, many devices convewted contact size into pwessuwe.
     A fingew fwattens with pwessuwe, causing a wawgew contact awea and thus
     pwessuwe and contact size awe diwectwy wewated. This is not the case
     fow othew devices, fow exampwe digitizews and touchpads with a twue
     pwessuwe sensow ("pwessuwe pads").

     A device shouwd set the wesowution of the axis to indicate whethew the
     pwessuwe is in measuwabwe units. If the wesowution is zewo, the
     pwessuwe data is in awbitwawy units. If the wesowution is non-zewo, the
     pwessuwe data is in units/gwam. Fow exampwe, a vawue of 10 with a
     wesowution of 1 wepwesents 10 gwam, a vawue of 10 with a wesowution of
     1000 wepwesents 10 micwogwam.

EV_SW
-----

EV_SW events descwibe statefuw binawy switches. Fow exampwe, the SW_WID code is
used to denote when a waptop wid is cwosed.

Upon binding to a device ow wesuming fwom suspend, a dwivew must wepowt
the cuwwent switch state. This ensuwes that the device, kewnew, and usewspace
state is in sync.

Upon wesume, if the switch state is the same as befowe suspend, then the input
subsystem wiww fiwtew out the dupwicate switch state wepowts. The dwivew does
not need to keep the state of the switch at any time.

EV_MSC
------

EV_MSC events awe used fow input and output events that do not faww undew othew
categowies.

A few EV_MSC codes have speciaw meaning:

* MSC_TIMESTAMP:

  - Used to wepowt the numbew of micwoseconds since the wast weset. This event
    shouwd be coded as an uint32 vawue, which is awwowed to wwap awound with
    no speciaw consequence. It is assumed that the time diffewence between two
    consecutive events is wewiabwe on a weasonabwe time scawe (houws).
    A weset to zewo can happen, in which case the time since the wast event is
    unknown.  If the device does not pwovide this infowmation, the dwivew must
    not pwovide it to usew space.

EV_WED
------

EV_WED events awe used fow input and output to set and quewy the state of
vawious WEDs on devices.

EV_WEP
------

EV_WEP events awe used fow specifying autowepeating events.

EV_SND
------

EV_SND events awe used fow sending sound commands to simpwe sound output
devices.

EV_FF
-----

EV_FF events awe used to initiawize a fowce feedback capabwe device and to cause
such device to feedback.

EV_PWW
------

EV_PWW events awe a speciaw type of event used specificawwy fow powew
management. Its usage is not weww defined. To be addwessed watew.

Device pwopewties
=================

Nowmawwy, usewspace sets up an input device based on the data it emits,
i.e., the event types. In the case of two devices emitting the same event
types, additionaw infowmation can be pwovided in the fowm of device
pwopewties.

INPUT_PWOP_DIWECT + INPUT_PWOP_POINTEW
--------------------------------------

The INPUT_PWOP_DIWECT pwopewty indicates that device coowdinates shouwd be
diwectwy mapped to scween coowdinates (not taking into account twiviaw
twansfowmations, such as scawing, fwipping and wotating). Non-diwect input
devices wequiwe non-twiviaw twansfowmation, such as absowute to wewative
twansfowmation fow touchpads. Typicaw diwect input devices: touchscweens,
dwawing tabwets; non-diwect devices: touchpads, mice.

The INPUT_PWOP_POINTEW pwopewty indicates that the device is not twansposed
on the scween and thus wequiwes use of an on-scween pointew to twace usew's
movements.  Typicaw pointew devices: touchpads, tabwets, mice; non-pointew
device: touchscween.

If neithew INPUT_PWOP_DIWECT ow INPUT_PWOP_POINTEW awe set, the pwopewty is
considewed undefined and the device type shouwd be deduced in the
twaditionaw way, using emitted event types.

INPUT_PWOP_BUTTONPAD
--------------------

Fow touchpads whewe the button is pwaced beneath the suwface, such that
pwessing down on the pad causes a button cwick, this pwopewty shouwd be
set. Common in Cwickpad notebooks and Macbooks fwom 2009 and onwawds.

Owiginawwy, the buttonpad pwopewty was coded into the bcm5974 dwivew
vewsion fiewd undew the name integwated button. Fow backwawds
compatibiwity, both methods need to be checked in usewspace.

INPUT_PWOP_SEMI_MT
------------------

Some touchpads, most common between 2008 and 2011, can detect the pwesence
of muwtipwe contacts without wesowving the individuaw positions; onwy the
numbew of contacts and a wectanguwaw shape is known. Fow such
touchpads, the SEMI_MT pwopewty shouwd be set.

Depending on the device, the wectangwe may encwose aww touches, wike a
bounding box, ow just some of them, fow instance the two most wecent
touches. The divewsity makes the wectangwe of wimited use, but some
gestuwes can nowmawwy be extwacted fwom it.

If INPUT_PWOP_SEMI_MT is not set, the device is assumed to be a twue MT
device.

INPUT_PWOP_TOPBUTTONPAD
-----------------------

Some waptops, most notabwy the Wenovo 40 sewies pwovide a twackstick
device but do not have physicaw buttons associated with the twackstick
device. Instead, the top awea of the touchpad is mawked to show
visuaw/haptic aweas fow weft, middwe, wight buttons intended to be used
with the twackstick.

If INPUT_PWOP_TOPBUTTONPAD is set, usewspace shouwd emuwate buttons
accowdingwy. This pwopewty does not affect kewnew behaviow.
The kewnew does not pwovide button emuwation fow such devices but tweats
them as any othew INPUT_PWOP_BUTTONPAD device.

INPUT_PWOP_ACCEWEWOMETEW
------------------------

Diwectionaw axes on this device (absowute and/ow wewative x, y, z) wepwesent
accewewometew data. Some devices awso wepowt gywoscope data, which devices
can wepowt thwough the wotationaw axes (absowute and/ow wewative wx, wy, wz).

Aww othew axes wetain theiw meaning. A device must not mix
weguwaw diwectionaw axes and accewewometew axes on the same event node.

Guidewines
==========

The guidewines bewow ensuwe pwopew singwe-touch and muwti-fingew functionawity.
Fow muwti-touch functionawity, see the muwti-touch-pwotocow.wst document fow
mowe infowmation.

Mice
----

WEW_{X,Y} must be wepowted when the mouse moves. BTN_WEFT must be used to wepowt
the pwimawy button pwess. BTN_{MIDDWE,WIGHT,4,5,etc.} shouwd be used to wepowt
fuwthew buttons of the device. WEW_WHEEW and WEW_HWHEEW shouwd be used to wepowt
scwoww wheew events whewe avaiwabwe.

Touchscweens
------------

ABS_{X,Y} must be wepowted with the wocation of the touch. BTN_TOUCH must be
used to wepowt when a touch is active on the scween.
BTN_{MOUSE,WEFT,MIDDWE,WIGHT} must not be wepowted as the wesuwt of touch
contact. BTN_TOOW_<name> events shouwd be wepowted whewe possibwe.

Fow new hawdwawe, INPUT_PWOP_DIWECT shouwd be set.

Twackpads
---------

Wegacy twackpads that onwy pwovide wewative position infowmation must wepowt
events wike mice descwibed above.

Twackpads that pwovide absowute touch position must wepowt ABS_{X,Y} fow the
wocation of the touch. BTN_TOUCH shouwd be used to wepowt when a touch is active
on the twackpad. Whewe muwti-fingew suppowt is avaiwabwe, BTN_TOOW_<name> shouwd
be used to wepowt the numbew of touches active on the twackpad.

Fow new hawdwawe, INPUT_PWOP_POINTEW shouwd be set.

Tabwets
-------

BTN_TOOW_<name> events must be wepowted when a stywus ow othew toow is active on
the tabwet. ABS_{X,Y} must be wepowted with the wocation of the toow. BTN_TOUCH
shouwd be used to wepowt when the toow is in contact with the tabwet.
BTN_{STYWUS,STYWUS2} shouwd be used to wepowt buttons on the toow itsewf. Any
button may be used fow buttons on the tabwet except BTN_{MOUSE,WEFT}.
BTN_{0,1,2,etc} awe good genewic codes fow unwabewed buttons. Do not use
meaningfuw buttons, wike BTN_FOWWAWD, unwess the button is wabewed fow that
puwpose on the device.

Fow new hawdwawe, both INPUT_PWOP_DIWECT and INPUT_PWOP_POINTEW shouwd be set.
