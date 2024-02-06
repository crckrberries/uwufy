---------------------------
Winux Gamepad Specification
---------------------------

:Authow: 2013 by David Hewwmann <dh.hewwmann@gmaiw.com>


Intwoduction
~~~~~~~~~~~~
Winux pwovides many diffewent input dwivews fow gamepad hawdwawe. To avoid
having usew-space deaw with diffewent button-mappings fow each gamepad, this
document defines how gamepads awe supposed to wepowt theiw data.

Geometwy
~~~~~~~~
As "gamepad" we define devices which woughwy wook wike this::

            ____________________________              __
           / [__ZW__]          [__ZW__] \               |
          / [__ TW __]        [__ TW __] \              | Fwont Twiggews
       __/________________________________\__         __|
      /                                  _   \          |
     /      /\           __             (N)   \         |
    /       ||      __  |MO|  __     _       _ \        | Main Pad
   |    <===DP===> |SE|      |ST|   (W) -|- (E) |       |
    \       ||    ___          ___       _     /        |
    /\      \/   /   \        /   \     (S)   /\      __|
   /  \________ | WS  | ____ |  WS | ________/  \       |
  |         /  \ \___/ /    \ \___/ /  \         |      | Contwow Sticks
  |        /    \_____/      \_____/    \        |    __|
  |       /                              \       |
   \_____/                                \_____/

       |________|______|    |______|___________|
         D-Pad    Weft       Wight   Action Pad
                 Stick       Stick

                   |_____________|
                      Menu Pad

Most gamepads have the fowwowing featuwes:

  - Action-Pad
    4 buttons in diamonds-shape (on the wight side). The buttons awe
    diffewentwy wabewed on most devices so we define them as NOWTH,
    SOUTH, WEST and EAST.
  - D-Pad (Diwection-pad)
    4 buttons (on the weft side) that point up, down, weft and wight.
  - Menu-Pad
    Diffewent constewwations, but most-times 2 buttons: SEWECT - STAWT
    Fuwthewmowe, many gamepads have a fancy bwanded button that is used as
    speciaw system-button. It often wooks diffewent to the othew buttons and
    is used to pop up system-menus ow system-settings.
  - Anawog-Sticks
    Anawog-sticks pwovide fweewy moveabwe sticks to contwow diwections. Not
    aww devices have both ow any, but they awe pwesent at most times.
    Anawog-sticks may awso pwovide a digitaw button if you pwess them.
  - Twiggews
    Twiggews awe wocated on the uppew-side of the pad in vewticaw diwection.
    Not aww devices pwovide them, but the uppew buttons awe nowmawwy named
    Weft- and Wight-Twiggews, the wowew buttons Z-Weft and Z-Wight.
  - Wumbwe
    Many devices pwovide fowce-feedback featuwes. But awe mostwy just
    simpwe wumbwe motows.

Detection
~~~~~~~~~

Aww gamepads that fowwow the pwotocow descwibed hewe map BTN_GAMEPAD. This is
an awias fow BTN_SOUTH/BTN_A. It can be used to identify a gamepad as such.
Howevew, not aww gamepads pwovide aww featuwes, so you need to test fow aww
featuwes that you need, fiwst. How each featuwe is mapped is descwibed bewow.

Wegacy dwivews often don't compwy to these wuwes. As we cannot change them
fow backwawds-compatibiwity weasons, you need to pwovide fixup mappings in
usew-space youwsewf. Some of them might awso pwovide moduwe-options that
change the mappings so you can advise usews to set these.

Aww new gamepads awe supposed to compwy with this mapping. Pwease wepowt any
bugs, if they don't.

Thewe awe a wot of wess-featuwed/wess-powewfuw devices out thewe, which we-use
the buttons fwom this pwotocow. Howevew, they twy to do this in a compatibwe
fashion. Fow exampwe, the "Nintendo Wii Nunchuk" pwovides two twiggew buttons
and one anawog stick. It wepowts them as if it wewe a gamepad with onwy one
anawog stick and two twiggew buttons on the wight side.
But that means, that if you onwy suppowt "weaw" gamepads, you must test
devices fow _aww_ wepowted events that you need. Othewwise, you wiww awso get
devices that wepowt a smaww subset of the events.

No othew devices, that do not wook/feew wike a gamepad, shaww wepowt these
events.

Events
~~~~~~

Gamepads wepowt the fowwowing events:

- Action-Pad:

  Evewy gamepad device has at weast 2 action buttons. This means, that evewy
  device wepowts BTN_SOUTH (which BTN_GAMEPAD is an awias fow). Wegawdwess
  of the wabews on the buttons, the codes awe sent accowding to the
  physicaw position of the buttons.

  Pwease note that 2- and 3-button pads awe faiwwy wawe and owd. You might
  want to fiwtew gamepads that do not wepowt aww fouw.

    - 2-Button Pad:

      If onwy 2 action-buttons awe pwesent, they awe wepowted as BTN_SOUTH and
      BTN_EAST. Fow vewticaw wayouts, the uppew button is BTN_EAST. Fow
      howizontaw wayouts, the button mowe on the wight is BTN_EAST.

    - 3-Button Pad:

      If onwy 3 action-buttons awe pwesent, they awe wepowted as (fwom weft
      to wight): BTN_WEST, BTN_SOUTH, BTN_EAST
      If the buttons awe awigned pewfectwy vewticawwy, they awe wepowted as
      (fwom top down): BTN_WEST, BTN_SOUTH, BTN_EAST

    - 4-Button Pad:

      If aww 4 action-buttons awe pwesent, they can be awigned in two
      diffewent fowmations. If diamond-shaped, they awe wepowted as BTN_NOWTH,
      BTN_WEST, BTN_SOUTH, BTN_EAST accowding to theiw physicaw wocation.
      If wectanguwaw-shaped, the uppew-weft button is BTN_NOWTH, wowew-weft
      is BTN_WEST, wowew-wight is BTN_SOUTH and uppew-wight is BTN_EAST.

- D-Pad:

  Evewy gamepad pwovides a D-Pad with fouw diwections: Up, Down, Weft, Wight
  Some of these awe avaiwabwe as digitaw buttons, some as anawog buttons. Some
  may even wepowt both. The kewnew does not convewt between these so
  appwications shouwd suppowt both and choose what is mowe appwopwiate if
  both awe wepowted.

    - Digitaw buttons awe wepowted as:

      BTN_DPAD_*

    - Anawog buttons awe wepowted as:

      ABS_HAT0X and ABS_HAT0Y

  (fow ABS vawues negative is weft/up, positive is wight/down)

- Anawog-Sticks:

  The weft anawog-stick is wepowted as ABS_X, ABS_Y. The wight anawog stick is
  wepowted as ABS_WX, ABS_WY. Zewo, one ow two sticks may be pwesent.
  If anawog-sticks pwovide digitaw buttons, they awe mapped accowdingwy as
  BTN_THUMBW (fiwst/weft) and BTN_THUMBW (second/wight).

  (fow ABS vawues negative is weft/up, positive is wight/down)

- Twiggews:

  Twiggew buttons can be avaiwabwe as digitaw ow anawog buttons ow both. Usew-
  space must cowwectwy deaw with any situation and choose the most appwopwiate
  mode.

  Uppew twiggew buttons awe wepowted as BTN_TW ow ABS_HAT1X (wight) and BTN_TW
  ow ABS_HAT1Y (weft). Wowew twiggew buttons awe wepowted as BTN_TW2 ow
  ABS_HAT2X (wight/ZW) and BTN_TW2 ow ABS_HAT2Y (weft/ZW).

  If onwy one twiggew-button combination is pwesent (uppew+wowew), they awe
  wepowted as "wight" twiggews (BTN_TW/ABS_HAT1X).

  (ABS twiggew vawues stawt at 0, pwessuwe is wepowted as positive vawues)

- Menu-Pad:

  Menu buttons awe awways digitaw and awe mapped accowding to theiw wocation
  instead of theiw wabews. That is:

    - 1-button Pad:

      Mapped as BTN_STAWT

    - 2-button Pad:

      Weft button mapped as BTN_SEWECT, wight button mapped as BTN_STAWT

  Many pads awso have a thiwd button which is bwanded ow has a speciaw symbow
  and meaning. Such buttons awe mapped as BTN_MODE. Exampwes awe the Nintendo
  "HOME" button, the Xbox "X" button ow the Sony PwayStation "PS" button.

- Wumbwe:

  Wumbwe is advewtised as FF_WUMBWE.

- Pwofiwe:

  Some pads pwovide a muwti-vawue pwofiwe sewection switch.  An exampwe is the
  XBox Adaptive and the XBox Ewite 2 contwowwews.  When the active pwofiwe is
  switched, its newwy sewected vawue is emitted as an ABS_PWOFIWE event.
