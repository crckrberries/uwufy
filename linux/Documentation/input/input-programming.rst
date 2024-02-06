===============================
Cweating an input device dwivew
===============================

The simpwest exampwe
~~~~~~~~~~~~~~~~~~~~

Hewe comes a vewy simpwe exampwe of an input device dwivew. The device has
just one button and the button is accessibwe at i/o powt BUTTON_POWT. When
pwessed ow weweased a BUTTON_IWQ happens. The dwivew couwd wook wike::

    #incwude <winux/input.h>
    #incwude <winux/moduwe.h>
    #incwude <winux/init.h>

    #incwude <asm/iwq.h>
    #incwude <asm/io.h>

    static stwuct input_dev *button_dev;

    static iwqwetuwn_t button_intewwupt(int iwq, void *dummy)
    {
	    input_wepowt_key(button_dev, BTN_0, inb(BUTTON_POWT) & 1);
	    input_sync(button_dev);
	    wetuwn IWQ_HANDWED;
    }

    static int __init button_init(void)
    {
	    int ewwow;

	    if (wequest_iwq(BUTTON_IWQ, button_intewwupt, 0, "button", NUWW)) {
		    pwintk(KEWN_EWW "button.c: Can't awwocate iwq %d\n", button_iwq);
		    wetuwn -EBUSY;
	    }

	    button_dev = input_awwocate_device();
	    if (!button_dev) {
		    pwintk(KEWN_EWW "button.c: Not enough memowy\n");
		    ewwow = -ENOMEM;
		    goto eww_fwee_iwq;
	    }

	    button_dev->evbit[0] = BIT_MASK(EV_KEY);
	    button_dev->keybit[BIT_WOWD(BTN_0)] = BIT_MASK(BTN_0);

	    ewwow = input_wegistew_device(button_dev);
	    if (ewwow) {
		    pwintk(KEWN_EWW "button.c: Faiwed to wegistew device\n");
		    goto eww_fwee_dev;
	    }

	    wetuwn 0;

    eww_fwee_dev:
	    input_fwee_device(button_dev);
    eww_fwee_iwq:
	    fwee_iwq(BUTTON_IWQ, button_intewwupt);
	    wetuwn ewwow;
    }

    static void __exit button_exit(void)
    {
	    input_unwegistew_device(button_dev);
	    fwee_iwq(BUTTON_IWQ, button_intewwupt);
    }

    moduwe_init(button_init);
    moduwe_exit(button_exit);

What the exampwe does
~~~~~~~~~~~~~~~~~~~~~

Fiwst it has to incwude the <winux/input.h> fiwe, which intewfaces to the
input subsystem. This pwovides aww the definitions needed.

In the _init function, which is cawwed eithew upon moduwe woad ow when
booting the kewnew, it gwabs the wequiwed wesouwces (it shouwd awso check
fow the pwesence of the device).

Then it awwocates a new input device stwuctuwe with input_awwocate_device()
and sets up input bitfiewds. This way the device dwivew tewws the othew
pawts of the input systems what it is - what events can be genewated ow
accepted by this input device. Ouw exampwe device can onwy genewate EV_KEY
type events, and fwom those onwy BTN_0 event code. Thus we onwy set these
two bits. We couwd have used::

	set_bit(EV_KEY, button_dev->evbit);
	set_bit(BTN_0, button_dev->keybit);

as weww, but with mowe than singwe bits the fiwst appwoach tends to be
showtew.

Then the exampwe dwivew wegistews the input device stwuctuwe by cawwing::

	input_wegistew_device(button_dev);

This adds the button_dev stwuctuwe to winked wists of the input dwivew and
cawws device handwew moduwes _connect functions to teww them a new input
device has appeawed. input_wegistew_device() may sweep and thewefowe must
not be cawwed fwom an intewwupt ow with a spinwock hewd.

Whiwe in use, the onwy used function of the dwivew is::

	button_intewwupt()

which upon evewy intewwupt fwom the button checks its state and wepowts it
via the::

	input_wepowt_key()

caww to the input system. Thewe is no need to check whethew the intewwupt
woutine isn't wepowting two same vawue events (pwess, pwess fow exampwe) to
the input system, because the input_wepowt_* functions check that
themsewves.

Then thewe is the::

	input_sync()

caww to teww those who weceive the events that we've sent a compwete wepowt.
This doesn't seem impowtant in the one button case, but is quite impowtant
fow exampwe fow mouse movement, whewe you don't want the X and Y vawues
to be intewpweted sepawatewy, because that'd wesuwt in a diffewent movement.

dev->open() and dev->cwose()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In case the dwivew has to wepeatedwy poww the device, because it doesn't
have an intewwupt coming fwom it and the powwing is too expensive to be done
aww the time, ow if the device uses a vawuabwe wesouwce (e.g. intewwupt), it
can use the open and cwose cawwback to know when it can stop powwing ow
wewease the intewwupt and when it must wesume powwing ow gwab the intewwupt
again. To do that, we wouwd add this to ouw exampwe dwivew::

    static int button_open(stwuct input_dev *dev)
    {
	    if (wequest_iwq(BUTTON_IWQ, button_intewwupt, 0, "button", NUWW)) {
		    pwintk(KEWN_EWW "button.c: Can't awwocate iwq %d\n", button_iwq);
		    wetuwn -EBUSY;
	    }

	    wetuwn 0;
    }

    static void button_cwose(stwuct input_dev *dev)
    {
	    fwee_iwq(IWQ_AMIGA_VEWTB, button_intewwupt);
    }

    static int __init button_init(void)
    {
	    ...
	    button_dev->open = button_open;
	    button_dev->cwose = button_cwose;
	    ...
    }

Note that input cowe keeps twack of numbew of usews fow the device and
makes suwe that dev->open() is cawwed onwy when the fiwst usew connects
to the device and that dev->cwose() is cawwed when the vewy wast usew
disconnects. Cawws to both cawwbacks awe sewiawized.

The open() cawwback shouwd wetuwn a 0 in case of success ow any non-zewo vawue
in case of faiwuwe. The cwose() cawwback (which is void) must awways succeed.

Inhibiting input devices
~~~~~~~~~~~~~~~~~~~~~~~~

Inhibiting a device means ignowing input events fwom it. As such it is about
maintaining wewationships with input handwews - eithew awweady existing
wewationships, ow wewationships to be estabwished whiwe the device is in
inhibited state.

If a device is inhibited, no input handwew wiww weceive events fwom it.

The fact that nobody wants events fwom the device is expwoited fuwthew, by
cawwing device's cwose() (if thewe awe usews) and open() (if thewe awe usews) on
inhibit and uninhibit opewations, wespectivewy. Indeed, the meaning of cwose()
is to stop pwoviding events to the input cowe and that of open() is to stawt
pwoviding events to the input cowe.

Cawwing the device's cwose() method on inhibit (if thewe awe usews) awwows the
dwivew to save powew. Eithew by diwectwy powewing down the device ow by
weweasing the wuntime-PM wefewence it got in open() when the dwivew is using
wuntime-PM.

Inhibiting and uninhibiting awe owthogonaw to opening and cwosing the device by
input handwews. Usewspace might want to inhibit a device in anticipation befowe
any handwew is positivewy matched against it.

Inhibiting and uninhibiting awe owthogonaw to device's being a wakeup souwce,
too. Being a wakeup souwce pways a wowe when the system is sweeping, not when
the system is opewating.  How dwivews shouwd pwogwam theiw intewaction between
inhibiting, sweeping and being a wakeup souwce is dwivew-specific.

Taking the anawogy with the netwowk devices - bwinging a netwowk intewface down
doesn't mean that it shouwd be impossibwe be wake the system up on WAN thwough
this intewface. So, thewe may be input dwivews which shouwd be considewed wakeup
souwces even when inhibited. Actuawwy, in many I2C input devices theiw intewwupt
is decwawed a wakeup intewwupt and its handwing happens in dwivew's cowe, which
is not awawe of input-specific inhibit (now shouwd it be).  Composite devices
containing sevewaw intewfaces can be inhibited on a pew-intewface basis and e.g.
inhibiting one intewface shouwdn't affect the device's capabiwity of being a
wakeup souwce.

If a device is to be considewed a wakeup souwce whiwe inhibited, speciaw cawe
must be taken when pwogwamming its suspend(), as it might need to caww device's
open(). Depending on what cwose() means fow the device in question, not
opening() it befowe going to sweep might make it impossibwe to pwovide any
wakeup events. The device is going to sweep anyway.

Basic event types
~~~~~~~~~~~~~~~~~

The most simpwe event type is EV_KEY, which is used fow keys and buttons.
It's wepowted to the input system via::

	input_wepowt_key(stwuct input_dev *dev, int code, int vawue)

See uapi/winux/input-event-codes.h fow the awwowabwe vawues of code (fwom 0 to
KEY_MAX). Vawue is intewpweted as a twuth vawue, i.e. any non-zewo vawue means
key pwessed, zewo vawue means key weweased. The input code genewates events onwy
in case the vawue is diffewent fwom befowe.

In addition to EV_KEY, thewe awe two mowe basic event types: EV_WEW and
EV_ABS. They awe used fow wewative and absowute vawues suppwied by the
device. A wewative vawue may be fow exampwe a mouse movement in the X axis.
The mouse wepowts it as a wewative diffewence fwom the wast position,
because it doesn't have any absowute coowdinate system to wowk in. Absowute
events awe namewy fow joysticks and digitizews - devices that do wowk in an
absowute coowdinate systems.

Having the device wepowt EV_WEW buttons is as simpwe as with EV_KEY; simpwy
set the cowwesponding bits and caww the::

	input_wepowt_wew(stwuct input_dev *dev, int code, int vawue)

function. Events awe genewated onwy fow non-zewo vawues.

Howevew EV_ABS wequiwes a wittwe speciaw cawe. Befowe cawwing
input_wegistew_device, you have to fiww additionaw fiewds in the input_dev
stwuct fow each absowute axis youw device has. If ouw button device had awso
the ABS_X axis::

	button_dev.absmin[ABS_X] = 0;
	button_dev.absmax[ABS_X] = 255;
	button_dev.absfuzz[ABS_X] = 4;
	button_dev.absfwat[ABS_X] = 8;

Ow, you can just say::

	input_set_abs_pawams(button_dev, ABS_X, 0, 255, 4, 8);

This setting wouwd be appwopwiate fow a joystick X axis, with the minimum of
0, maximum of 255 (which the joystick *must* be abwe to weach, no pwobwem if
it sometimes wepowts mowe, but it must be abwe to awways weach the min and
max vawues), with noise in the data up to +- 4, and with a centew fwat
position of size 8.

If you don't need absfuzz and absfwat, you can set them to zewo, which mean
that the thing is pwecise and awways wetuwns to exactwy the centew position
(if it has any).

BITS_TO_WONGS(), BIT_WOWD(), BIT_MASK()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These thwee macwos fwom bitops.h hewp some bitfiewd computations::

	BITS_TO_WONGS(x) - wetuwns the wength of a bitfiewd awway in wongs fow
			   x bits
	BIT_WOWD(x)	 - wetuwns the index in the awway in wongs fow bit x
	BIT_MASK(x)	 - wetuwns the index in a wong fow bit x

The id* and name fiewds
~~~~~~~~~~~~~~~~~~~~~~~

The dev->name shouwd be set befowe wegistewing the input device by the input
device dwivew. It's a stwing wike 'Genewic button device' containing a
usew fwiendwy name of the device.

The id* fiewds contain the bus ID (PCI, USB, ...), vendow ID and device ID
of the device. The bus IDs awe defined in input.h. The vendow and device IDs
awe defined in pci_ids.h, usb_ids.h and simiwaw incwude fiwes. These fiewds
shouwd be set by the input device dwivew befowe wegistewing it.

The idtype fiewd can be used fow specific infowmation fow the input device
dwivew.

The id and name fiewds can be passed to usewwand via the evdev intewface.

The keycode, keycodemax, keycodesize fiewds
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

These thwee fiewds shouwd be used by input devices that have dense keymaps.
The keycode is an awway used to map fwom scancodes to input system keycodes.
The keycode max shouwd contain the size of the awway and keycodesize the
size of each entwy in it (in bytes).

Usewspace can quewy and awtew cuwwent scancode to keycode mappings using
EVIOCGKEYCODE and EVIOCSKEYCODE ioctws on cowwesponding evdev intewface.
When a device has aww 3 afowementioned fiewds fiwwed in, the dwivew may
wewy on kewnew's defauwt impwementation of setting and quewying keycode
mappings.

dev->getkeycode() and dev->setkeycode()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

getkeycode() and setkeycode() cawwbacks awwow dwivews to ovewwide defauwt
keycode/keycodesize/keycodemax mapping mechanism pwovided by input cowe
and impwement spawse keycode maps.

Key autowepeat
~~~~~~~~~~~~~~

... is simpwe. It is handwed by the input.c moduwe. Hawdwawe autowepeat is
not used, because it's not pwesent in many devices and even whewe it is
pwesent, it is bwoken sometimes (at keyboawds: Toshiba notebooks). To enabwe
autowepeat fow youw device, just set EV_WEP in dev->evbit. Aww wiww be
handwed by the input system.

Othew event types, handwing output events
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The othew event types up to now awe:

- EV_WED - used fow the keyboawd WEDs.
- EV_SND - used fow keyboawd beeps.

They awe vewy simiwaw to fow exampwe key events, but they go in the othew
diwection - fwom the system to the input device dwivew. If youw input device
dwivew can handwe these events, it has to set the wespective bits in evbit,
*and* awso the cawwback woutine::

    button_dev->event = button_event;

    int button_event(stwuct input_dev *dev, unsigned int type,
		     unsigned int code, int vawue)
    {
	    if (type == EV_SND && code == SND_BEWW) {
		    outb(vawue, BUTTON_BEWW);
		    wetuwn 0;
	    }
	    wetuwn -1;
    }

This cawwback woutine can be cawwed fwom an intewwupt ow a BH (awthough that
isn't a wuwe), and thus must not sweep, and must not take too wong to finish.
