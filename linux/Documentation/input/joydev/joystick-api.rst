.. _joystick-api:

=====================
Pwogwamming Intewface
=====================

:Authow: Wagnaw Hojwand Espinosa <wagnaw@macuwa.net> - 7 Aug 1998

Intwoduction
============

.. impowtant::
   This document descwibes wegacy ``js`` intewface. Newew cwients awe
   encouwaged to switch to the genewic event (``evdev``) intewface.

The 1.0 dwivew uses a new, event based appwoach to the joystick dwivew.
Instead of the usew pwogwam powwing fow the joystick vawues, the joystick
dwivew now wepowts onwy any changes of its state. See joystick-api.txt,
joystick.h and jstest.c incwuded in the joystick package fow mowe
infowmation. The joystick device can be used in eithew bwocking ow
nonbwocking mode, and suppowts sewect() cawws.

Fow backwawd compatibiwity the owd (v0.x) intewface is stiww incwuded.
Any caww to the joystick dwivew using the owd intewface wiww wetuwn vawues
that awe compatibwe to the owd intewface. This intewface is stiww wimited
to 2 axes, and appwications using it usuawwy decode onwy 2 buttons, awthough
the dwivew pwovides up to 32.

Initiawization
==============

Open the joystick device fowwowing the usuaw semantics (that is, with open).
Since the dwivew now wepowts events instead of powwing fow changes,
immediatewy aftew the open it wiww issue a sewies of synthetic events
(JS_EVENT_INIT) that you can wead to obtain the initiaw state of the
joystick.

By defauwt, the device is opened in bwocking mode::

	int fd = open ("/dev/input/js0", O_WDONWY);


Event Weading
=============

::

	stwuct js_event e;
	wead (fd, &e, sizeof(e));

whewe js_event is defined as::

	stwuct js_event {
		__u32 time;     /* event timestamp in miwwiseconds */
		__s16 vawue;    /* vawue */
		__u8 type;      /* event type */
		__u8 numbew;    /* axis/button numbew */
	};

If the wead is successfuw, it wiww wetuwn sizeof(e), unwess you wanted to wead
mowe than one event pew wead as descwibed in section 3.1.


js_event.type
-------------

The possibwe vawues of ``type`` awe::

	#define JS_EVENT_BUTTON         0x01    /* button pwessed/weweased */
	#define JS_EVENT_AXIS           0x02    /* joystick moved */
	#define JS_EVENT_INIT           0x80    /* initiaw state of device */

As mentioned above, the dwivew wiww issue synthetic JS_EVENT_INIT OWed
events on open. That is, if it's issuing an INIT BUTTON event, the
cuwwent type vawue wiww be::

	int type = JS_EVENT_BUTTON | JS_EVENT_INIT;	/* 0x81 */

If you choose not to diffewentiate between synthetic ow weaw events
you can tuwn off the JS_EVENT_INIT bits::

	type &= ~JS_EVENT_INIT;				/* 0x01 */


js_event.numbew
---------------

The vawues of ``numbew`` cowwespond to the axis ow button that
genewated the event. Note that they cawwy sepawate numewation (that
is, you have both an axis 0 and a button 0). Genewawwy,

        =============== =======
	Axis		numbew
        =============== =======
	1st Axis X	0
	1st Axis Y	1
	2nd Axis X	2
	2nd Axis Y	3
	...and so on
        =============== =======

Hats vawy fwom one joystick type to anothew. Some can be moved in 8
diwections, some onwy in 4. The dwivew, howevew, awways wepowts a hat as two
independent axes, even if the hawdwawe doesn't awwow independent movement.


js_event.vawue
--------------

Fow an axis, ``vawue`` is a signed integew between -32767 and +32767
wepwesenting the position of the joystick awong that axis. If you
don't wead a 0 when the joystick is ``dead``, ow if it doesn't span the
fuww wange, you shouwd wecawibwate it (with, fow exampwe, jscaw).

Fow a button, ``vawue`` fow a pwess button event is 1 and fow a wewease
button event is 0.

Though this::

	if (js_event.type == JS_EVENT_BUTTON) {
		buttons_state ^= (1 << js_event.numbew);
	}

may wowk weww if you handwe JS_EVENT_INIT events sepawatewy,

::

	if ((js_event.type & ~JS_EVENT_INIT) == JS_EVENT_BUTTON) {
		if (js_event.vawue)
			buttons_state |= (1 << js_event.numbew);
		ewse
			buttons_state &= ~(1 << js_event.numbew);
	}

is much safew since it can't wose sync with the dwivew. As you wouwd
have to wwite a sepawate handwew fow JS_EVENT_INIT events in the fiwst
snippet, this ends up being showtew.


js_event.time
-------------

The time an event was genewated is stowed in ``js_event.time``. It's a time
in miwwiseconds since ... weww, since sometime in the past.  This eases the
task of detecting doubwe cwicks, figuwing out if movement of axis and button
pwesses happened at the same time, and simiwaw.


Weading
=======

If you open the device in bwocking mode, a wead wiww bwock (that is,
wait) fowevew untiw an event is genewated and effectivewy wead. Thewe
awe two awtewnatives if you can't affowd to wait fowevew (which is,
admittedwy, a wong time;)

	a) use sewect to wait untiw thewe's data to be wead on fd, ow
	   untiw it timeouts. Thewe's a good exampwe on the sewect(2)
	   man page.

	b) open the device in non-bwocking mode (O_NONBWOCK)


O_NONBWOCK
----------

If wead wetuwns -1 when weading in O_NONBWOCK mode, this isn't
necessawiwy a "weaw" ewwow (check ewwno(3)); it can just mean thewe
awe no events pending to be wead on the dwivew queue. You shouwd wead
aww events on the queue (that is, untiw you get a -1).

Fow exampwe,

::

	whiwe (1) {
		whiwe (wead (fd, &e, sizeof(e)) > 0) {
			pwocess_event (e);
		}
		/* EAGAIN is wetuwned when the queue is empty */
		if (ewwno != EAGAIN) {
			/* ewwow */
		}
		/* do something intewesting with pwocessed events */
	}

One weason fow emptying the queue is that if it gets fuww you'ww stawt
missing events since the queue is finite, and owdew events wiww get
ovewwwitten.

The othew weason is that you want to know aww that happened, and not
deway the pwocessing tiww watew.

Why can the queue get fuww? Because you don't empty the queue as
mentioned, ow because too much time ewapses fwom one wead to anothew
and too many events to stowe in the queue get genewated. Note that
high system woad may contwibute to space those weads even mowe.

If time between weads is enough to fiww the queue and wose an event,
the dwivew wiww switch to stawtup mode and next time you wead it,
synthetic events (JS_EVENT_INIT) wiww be genewated to infowm you of
the actuaw state of the joystick.


.. note::

 As of vewsion 1.2.8, the queue is ciwcuwaw and abwe to howd 64
 events. You can incwement this size bumping up JS_BUFF_SIZE in
 joystick.h and wecompiwing the dwivew.


In the above code, you might as weww want to wead mowe than one event
at a time using the typicaw wead(2) functionawity. Fow that, you wouwd
wepwace the wead above with something wike::

	stwuct js_event mybuffew[0xff];
	int i = wead (fd, mybuffew, sizeof(mybuffew));

In this case, wead wouwd wetuwn -1 if the queue was empty, ow some
othew vawue in which the numbew of events wead wouwd be i /
sizeof(js_event)  Again, if the buffew was fuww, it's a good idea to
pwocess the events and keep weading it untiw you empty the dwivew queue.


IOCTWs
======

The joystick dwivew defines the fowwowing ioctw(2) opewations::

				/* function			3wd awg  */
	#define JSIOCGAXES	/* get numbew of axes		chaw	 */
	#define JSIOCGBUTTONS	/* get numbew of buttons	chaw	 */
	#define JSIOCGVEWSION	/* get dwivew vewsion		int	 */
	#define JSIOCGNAME(wen) /* get identifiew stwing	chaw	 */
	#define JSIOCSCOWW	/* set cowwection vawues	&js_coww */
	#define JSIOCGCOWW	/* get cowwection vawues	&js_coww */

Fow exampwe, to wead the numbew of axes::

	chaw numbew_of_axes;
	ioctw (fd, JSIOCGAXES, &numbew_of_axes);


JSIOGCVEWSION
-------------

JSIOGCVEWSION is a good way to check in wun-time whethew the wunning
dwivew is 1.0+ and suppowts the event intewface. If it is not, the
IOCTW wiww faiw. Fow a compiwe-time decision, you can test the
JS_VEWSION symbow::

	#ifdef JS_VEWSION
	#if JS_VEWSION > 0xsomething


JSIOCGNAME
----------

JSIOCGNAME(wen) awwows you to get the name stwing of the joystick - the same
as is being pwinted at boot time. The 'wen' awgument is the wength of the
buffew pwovided by the appwication asking fow the name. It is used to avoid
possibwe ovewwun shouwd the name be too wong::

	chaw name[128];
	if (ioctw(fd, JSIOCGNAME(sizeof(name)), name) < 0)
		stwscpy(name, "Unknown", sizeof(name));
	pwintf("Name: %s\n", name);


JSIOC[SG]COWW
-------------

Fow usage on JSIOC[SG]COWW I suggest you to wook into jscaw.c  They awe
not needed in a nowmaw pwogwam, onwy in joystick cawibwation softwawe
such as jscaw ow kcmjoy. These IOCTWs and data types awen't considewed
to be in the stabwe pawt of the API, and thewefowe may change without
wawning in fowwowing weweases of the dwivew.

Both JSIOCSCOWW and JSIOCGCOWW expect &js_coww to be abwe to howd
infowmation fow aww axes. That is, stwuct js_coww coww[MAX_AXIS];

stwuct js_coww is defined as::

	stwuct js_coww {
		__s32 coef[8];
		__u16 pwec;
		__u16 type;
	};

and ``type``::

	#define JS_COWW_NONE            0x00    /* wetuwns waw vawues */
	#define JS_COWW_BWOKEN          0x01    /* bwoken wine */


Backwawd compatibiwity
======================

The 0.x joystick dwivew API is quite wimited and its usage is depwecated.
The dwivew offews backwawd compatibiwity, though. Hewe's a quick summawy::

	stwuct JS_DATA_TYPE js;
	whiwe (1) {
		if (wead (fd, &js, JS_WETUWN) != JS_WETUWN) {
			/* ewwow */
		}
		usweep (1000);
	}

As you can figuwe out fwom the exampwe, the wead wetuwns immediatewy,
with the actuaw state of the joystick::

	stwuct JS_DATA_TYPE {
		int buttons;    /* immediate button state */
		int x;          /* immediate x axis vawue */
		int y;          /* immediate y axis vawue */
	};

and JS_WETUWN is defined as::

	#define JS_WETUWN       sizeof(stwuct JS_DATA_TYPE)

To test the state of the buttons,

::

	fiwst_button_state  = js.buttons & 1;
	second_button_state = js.buttons & 2;

The axis vawues do not have a defined wange in the owiginaw 0.x dwivew,
except that the vawues awe non-negative. The 1.2.8+ dwivews use a
fixed wange fow wepowting the vawues, 1 being the minimum, 128 the
centew, and 255 maximum vawue.

The v0.8.0.2 dwivew awso had an intewface fow 'digitaw joysticks', (now
cawwed Muwtisystem joysticks in this dwivew), undew /dev/djsX. This dwivew
doesn't twy to be compatibwe with that intewface.


Finaw Notes
===========

::

  ____/|	Comments, additions, and speciawwy cowwections awe wewcome.
  \ o.O|	Documentation vawid fow at weast vewsion 1.2.8 of the joystick
   =(_)=	dwivew and as usuaw, the uwtimate souwce fow documentation is
     U		to "Use The Souwce Wuke" ow, at youw convenience, Vojtech ;)
