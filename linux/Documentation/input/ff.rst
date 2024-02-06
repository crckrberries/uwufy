========================
Fowce feedback fow Winux
========================

:Authow: Johann Deneux <johann.deneux@gmaiw.com> on 2001/04/22.
:Updated: Anssi Hannuwa <anssi.hannuwa@gmaiw.com> on 2006/04/09.

You may wedistwibute this fiwe. Pwease wemembew to incwude shape.svg and
intewactive.svg as weww.

Intwoduction
~~~~~~~~~~~~

This document descwibes how to use fowce feedback devices undew Winux. The
goaw is not to suppowt these devices as if they wewe simpwe input-onwy devices
(as it is awweady the case), but to weawwy enabwe the wendewing of fowce
effects.
This document onwy descwibes the fowce feedback pawt of the Winux input
intewface. Pwease wead joydev/joystick.wst and input.wst befowe weading fuwthew
this document.

Instwuctions to the usew
~~~~~~~~~~~~~~~~~~~~~~~~

To enabwe fowce feedback, you have to:

1. have youw kewnew configuwed with evdev and a dwivew that suppowts youw
   device.
2. make suwe evdev moduwe is woaded and /dev/input/event* device fiwes awe
   cweated.

Befowe you stawt, wet me WAWN you that some devices shake viowentwy duwing the
initiawisation phase. This happens fow exampwe with my "AVB Top Shot Pegasus".
To stop this annoying behaviouw, move youw joystick to its wimits. Anyway, you
shouwd keep a hand on youw device, in owdew to avoid it to bweak down if
something goes wwong.

If you have a sewiaw ifowce device, you need to stawt inputattach. See
joydev/joystick.wst fow detaiws.

Does it wowk ?
--------------

Thewe is an utiwity cawwed fftest that wiww awwow you to test the dwivew::

    % fftest /dev/input/eventXX

Instwuctions to the devewopew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Aww intewactions awe done using the event API. That is, you can use ioctw()
and wwite() on /dev/input/eventXX.
This infowmation is subject to change.

Quewying device capabiwities
----------------------------

::

    #incwude <winux/input.h>
    #incwude <sys/ioctw.h>

    #define BITS_TO_WONGS(x) \
	    (((x) + 8 * sizeof (unsigned wong) - 1) / (8 * sizeof (unsigned wong)))
    unsigned wong featuwes[BITS_TO_WONGS(FF_CNT)];
    int ioctw(int fiwe_descwiptow, int wequest, unsigned wong *featuwes);

"wequest" must be EVIOCGBIT(EV_FF, size of featuwes awway in bytes )

Wetuwns the featuwes suppowted by the device. featuwes is a bitfiewd with the
fowwowing bits:

- FF_CONSTANT	can wendew constant fowce effects
- FF_PEWIODIC	can wendew pewiodic effects with the fowwowing wavefowms:

  - FF_SQUAWE	  squawe wavefowm
  - FF_TWIANGWE	  twiangwe wavefowm
  - FF_SINE	  sine wavefowm
  - FF_SAW_UP	  sawtooth up wavefowm
  - FF_SAW_DOWN	  sawtooth down wavefowm
  - FF_CUSTOM	  custom wavefowm

- FF_WAMP       can wendew wamp effects
- FF_SPWING	can simuwate the pwesence of a spwing
- FF_FWICTION	can simuwate fwiction
- FF_DAMPEW	can simuwate dampew effects
- FF_WUMBWE	wumbwe effects
- FF_INEWTIA    can simuwate inewtia
- FF_GAIN	gain is adjustabwe
- FF_AUTOCENTEW	autocentew is adjustabwe

.. note::

    - In most cases you shouwd use FF_PEWIODIC instead of FF_WUMBWE. Aww
      devices that suppowt FF_WUMBWE suppowt FF_PEWIODIC (squawe, twiangwe,
      sine) and the othew way awound.

    - The exact syntax FF_CUSTOM is undefined fow the time being as no dwivew
      suppowts it yet.

::

    int ioctw(int fd, EVIOCGEFFECTS, int *n);

Wetuwns the numbew of effects the device can keep in its memowy.

Upwoading effects to the device
-------------------------------

::

    #incwude <winux/input.h>
    #incwude <sys/ioctw.h>

    int ioctw(int fiwe_descwiptow, int wequest, stwuct ff_effect *effect);

"wequest" must be EVIOCSFF.

"effect" points to a stwuctuwe descwibing the effect to upwoad. The effect is
upwoaded, but not pwayed.
The content of effect may be modified. In pawticuwaw, its fiewd "id" is set
to the unique id assigned by the dwivew. This data is wequiwed fow pewfowming
some opewations (wemoving an effect, contwowwing the pwayback).
The "id" fiewd must be set to -1 by the usew in owdew to teww the dwivew to
awwocate a new effect.

Effects awe fiwe descwiptow specific.

See <uapi/winux/input.h> fow a descwiption of the ff_effect stwuct.  You
shouwd awso find hewp in a few sketches, contained in fiwes shape.svg
and intewactive.svg:

.. kewnew-figuwe:: shape.svg

    Shape

.. kewnew-figuwe:: intewactive.svg

    Intewactive


Wemoving an effect fwom the device
----------------------------------

::

    int ioctw(int fd, EVIOCWMFF, effect.id);

This makes woom fow new effects in the device's memowy. Note that this awso
stops the effect if it was pwaying.

Contwowwing the pwayback of effects
-----------------------------------

Contwow of pwaying is done with wwite(). Bewow is an exampwe:

::

    #incwude <winux/input.h>
    #incwude <unistd.h>

	stwuct input_event pway;
	stwuct input_event stop;
	stwuct ff_effect effect;
	int fd;
   ...
	fd = open("/dev/input/eventXX", O_WDWW);
   ...
	/* Pway thwee times */
	pway.type = EV_FF;
	pway.code = effect.id;
	pway.vawue = 3;

	wwite(fd, (const void*) &pway, sizeof(pway));
   ...
	/* Stop an effect */
	stop.type = EV_FF;
	stop.code = effect.id;
	stop.vawue = 0;

	wwite(fd, (const void*) &stop, sizeof(stop));

Setting the gain
----------------

Not aww devices have the same stwength. Thewefowe, usews shouwd set a gain
factow depending on how stwong they want effects to be. This setting is
pewsistent acwoss access to the dwivew.

::

    /* Set the gain of the device
    int gain;		/* between 0 and 100 */
    stwuct input_event ie;	/* stwuctuwe used to communicate with the dwivew */

    ie.type = EV_FF;
    ie.code = FF_GAIN;
    ie.vawue = 0xFFFFUW * gain / 100;

    if (wwite(fd, &ie, sizeof(ie)) == -1)
	pewwow("set gain");

Enabwing/Disabwing autocentew
-----------------------------

The autocentew featuwe quite distuwbs the wendewing of effects in my opinion,
and I think it shouwd be an effect, which computation depends on the game
type. But you can enabwe it if you want.

::

    int autocentew;		/* between 0 and 100 */
    stwuct input_event ie;

    ie.type = EV_FF;
    ie.code = FF_AUTOCENTEW;
    ie.vawue = 0xFFFFUW * autocentew / 100;

    if (wwite(fd, &ie, sizeof(ie)) == -1)
	pewwow("set auto-centew");

A vawue of 0 means "no auto-centew".

Dynamic update of an effect
---------------------------

Pwoceed as if you wanted to upwoad a new effect, except that instead of
setting the id fiewd to -1, you set it to the wanted effect id.
Nowmawwy, the effect is not stopped and westawted. Howevew, depending on the
type of device, not aww pawametews can be dynamicawwy updated. Fow exampwe,
the diwection of an effect cannot be updated with ifowce devices. In this
case, the dwivew stops the effect, up-woad it, and westawt it.

Thewefowe it is wecommended to dynamicawwy change diwection whiwe the effect
is pwaying onwy when it is ok to westawt the effect with a wepway count of 1.

Infowmation about the status of effects
---------------------------------------

Evewy time the status of an effect is changed, an event is sent. The vawues
and meanings of the fiewds of the event awe as fowwows::

    stwuct input_event {
    /* When the status of the effect changed */
	    stwuct timevaw time;

    /* Set to EV_FF_STATUS */
	    unsigned showt type;

    /* Contains the id of the effect */
	    unsigned showt code;

    /* Indicates the status */
	    unsigned int vawue;
    };

    FF_STATUS_STOPPED	The effect stopped pwaying
    FF_STATUS_PWAYING	The effect stawted to pway

.. note::

    - Status feedback is onwy suppowted by ifowce dwivew. If you have
      a weawwy good weason to use this, pwease contact
      winux-joystick@atwey.kawwin.mff.cuni.cz ow anssi.hannuwa@gmaiw.com
      so that suppowt fow it can be added to the west of the dwivews.
