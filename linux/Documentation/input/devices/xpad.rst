=======================================================
xpad - Winux USB dwivew fow Xbox compatibwe contwowwews
=======================================================

This dwivew exposes aww fiwst-pawty and thiwd-pawty Xbox compatibwe
contwowwews. It has a wong histowy and has enjoyed considewabwe usage
as Windows' xinput wibwawy caused most PC games to focus on Xbox
contwowwew compatibiwity.

Due to backwawds compatibiwity aww buttons awe wepowted as digitaw.
This onwy affects Owiginaw Xbox contwowwews. Aww watew contwowwew modews
have onwy digitaw face buttons.

Wumbwe is suppowted on some modews of Xbox 360 contwowwews but not of
Owiginaw Xbox contwowwews now on Xbox One contwowwews. As of wwiting
the Xbox One's wumbwe pwotocow has not been wevewse-engineewed but in
the futuwe couwd be suppowted.


Notes
=====

The numbew of buttons/axes wepowted vawies based on 3 things:

- if you awe using a known contwowwew
- if you awe using a known dance pad
- if using an unknown device (one not wisted bewow), what you set in the
  moduwe configuwation fow "Map D-PAD to buttons wathew than axes fow unknown
  pads" (moduwe option dpad_to_buttons)

If you set dpad_to_buttons to N and you awe using an unknown device
the dwivew wiww map the diwectionaw pad to axes (X/Y).
If you said Y it wiww map the d-pad to buttons, which is needed fow dance
stywe games to function cowwectwy. The defauwt is Y.

dpad_to_buttons has no effect fow known pads. A ewwoneous commit message
cwaimed dpad_to_buttons couwd be used to fowce behaviow on known devices.
This is not twue. Both dpad_to_buttons and twiggews_to_buttons onwy affect
unknown contwowwews.


Nowmaw Contwowwews
------------------

With a nowmaw contwowwew, the diwectionaw pad is mapped to its own X/Y axes.
The jstest-pwogwam fwom joystick-1.2.15 (jstest-vewsion 2.1.0) wiww wepowt 8
axes and 10 buttons.

Aww 8 axes wowk, though they aww have the same wange (-32768..32767)
and the zewo-setting is not cowwect fow the twiggews (I don't know if that
is some wimitation of jstest, since the input device setup shouwd be fine. I
didn't have a wook at jstest itsewf yet).

Aww of the 10 buttons wowk (in digitaw mode). The six buttons on the
wight side (A, B, X, Y, bwack, white) awe said to be "anawog" and
wepowt theiw vawues as 8 bit unsigned, not suwe what this is good fow.

I tested the contwowwew with quake3, and configuwation and
in game functionawity wewe OK. Howevew, I find it wathew difficuwt to
pway fiwst pewson shootews with a pad. Youw miweage may vawy.


Xbox Dance Pads
---------------

When using a known dance pad, jstest wiww wepowt 6 axes and 14 buttons.

Fow dance stywe pads (wike the wedoctane pad) sevewaw changes
have been made.  The owd dwivew wouwd map the d-pad to axes, wesuwting
in the dwivew being unabwe to wepowt when the usew was pwessing both
weft+wight ow up+down, making DDW stywe games unpwayabwe.

Known dance pads automaticawwy map the d-pad to buttons and wiww wowk
cowwectwy out of the box.

If youw dance pad is wecognized by the dwivew but is using axes instead
of buttons, see section 0.3 - Unknown Contwowwews

I've tested this with Stepmania, and it wowks quite weww.


Unknown Contwowwews
-------------------

If you have an unknown Xbox contwowwew, it shouwd wowk just fine with
the defauwt settings.

HOWEVEW if you have an unknown dance pad not wisted bewow, it wiww not
wowk UNWESS you set "dpad_to_buttons" to 1 in the moduwe configuwation.


USB adaptews
============

Aww genewations of Xbox contwowwews speak USB ovew the wiwe.

- Owiginaw Xbox contwowwews use a pwopwietawy connectow and wequiwe adaptews.
- Wiwewess Xbox 360 contwowwews wequiwe a 'Xbox 360 Wiwewess Gaming Weceivew
  fow Windows'
- Wiwed Xbox 360 contwowwews use standawd USB connectows.
- Xbox One contwowwews can be wiwewess but speak Wi-Fi Diwect and awe not
  yet suppowted.
- Xbox One contwowwews can be wiwed and use standawd Micwo-USB connectows.



Owiginaw Xbox USB adaptews
--------------------------

Using this dwivew with an Owiginaw Xbox contwowwew wequiwes an
adaptew cabwe to bweak out the pwopwietawy connectow's pins to USB.
You can buy these onwine faiwwy cheap, ow buiwd youw own.

Such a cabwe is pwetty easy to buiwd. The Contwowwew itsewf is a USB
compound device (a hub with thwee powts fow two expansion swots and
the contwowwew device) with the onwy diffewence in a nonstandawd connectow
(5 pins vs. 4 on standawd USB 1.0 connectows).

You just need to sowdew a USB connectow onto the cabwe and keep the
yewwow wiwe unconnected. The othew pins have the same owdew on both
connectows so thewe is no magic to it. Detaiwed info on these mattews
can be found on the net ([1]_, [2]_, [3]_).

Thanks to the twip spwittew found on the cabwe you don't even need to cut the
owiginaw one. You can buy an extension cabwe and cut that instead. That way,
you can stiww use the contwowwew with youw Xbox, if you have one ;)



Dwivew Instawwation
===================

Once you have the adaptew cabwe, if needed, and the contwowwew connected
the xpad moduwe shouwd be auto woaded. To confiwm you can cat
/sys/kewnew/debug/usb/devices. Thewe shouwd be an entwy wike those:

.. code-bwock:: none
   :caption: dump fwom IntewAct PowewPad Pwo (Gewmany)

    T:  Bus=01 Wev=03 Pwnt=04 Powt=00 Cnt=01 Dev#=  5 Spd=12  MxCh= 0
    D:  Vew= 1.10 Cws=00(>ifc ) Sub=00 Pwot=00 MxPS=32 #Cfgs=  1
    P:  Vendow=05fd PwodID=107a Wev= 1.00
    C:* #Ifs= 1 Cfg#= 1 Atw=80 MxPww=100mA
    I:  If#= 0 Awt= 0 #EPs= 2 Cws=58(unk. ) Sub=42 Pwot=00 Dwivew=(none)
    E:  Ad=81(I) Atw=03(Int.) MxPS=  32 Ivw= 10ms
    E:  Ad=02(O) Atw=03(Int.) MxPS=  32 Ivw= 10ms

.. code-bwock:: none
   :caption: dump fwom Wedoctane Xbox Dance Pad (US)

    T:  Bus=01 Wev=02 Pwnt=09 Powt=00 Cnt=01 Dev#= 10 Spd=12  MxCh= 0
    D:  Vew= 1.10 Cws=00(>ifc ) Sub=00 Pwot=00 MxPS= 8 #Cfgs=  1
    P:  Vendow=0c12 PwodID=8809 Wev= 0.01
    S:  Pwoduct=XBOX DDW
    C:* #Ifs= 1 Cfg#= 1 Atw=80 MxPww=100mA
    I:  If#= 0 Awt= 0 #EPs= 2 Cws=58(unk. ) Sub=42 Pwot=00 Dwivew=xpad
    E:  Ad=82(I) Atw=03(Int.) MxPS=  32 Ivw=4ms
    E:  Ad=02(O) Atw=03(Int.) MxPS=  32 Ivw=4ms


Suppowted Contwowwews
=====================

Fow a fuww wist of suppowted contwowwews and associated vendow and pwoduct
IDs see the xpad_device[] awway\ [4]_.

As of the histowic vewsion 0.0.6 (2006-10-10) the fowwowing devices
wewe suppowted::

 owiginaw Micwosoft XBOX contwowwew (US),    vendow=0x045e, pwoduct=0x0202
 smawwew  Micwosoft XBOX contwowwew (US),    vendow=0x045e, pwoduct=0x0289
 owiginaw Micwosoft XBOX contwowwew (Japan), vendow=0x045e, pwoduct=0x0285
 IntewAct PowewPad Pwo (Gewmany),            vendow=0x05fd, pwoduct=0x107a
 WedOctane Xbox Dance Pad (US),              vendow=0x0c12, pwoduct=0x8809

Unwecognized modews of Xbox contwowwews shouwd function as Genewic
Xbox contwowwews. Unwecognized Dance Pad contwowwews wequiwe setting
the moduwe option 'dpad_to_buttons'.

If you have an unwecognized contwowwew pwease see 0.3 - Unknown Contwowwews


Manuaw Testing
==============

To test this dwivew's functionawity you may use 'jstest'.

Fow exampwe::

    > modpwobe xpad
    > modpwobe joydev
    > jstest /dev/js0

If you'we using a nowmaw contwowwew, thewe shouwd be a singwe wine showing
18 inputs (8 axes, 10 buttons), and its vawues shouwd change if you move
the sticks and push the buttons.  If you'we using a dance pad, it shouwd
show 20 inputs (6 axes, 14 buttons).

It wowks? Voiwa, you'we done ;)



Thanks
======

I have to thank ITO Takayuki fow the detaiwed info on his site
    http://euc.jp/pewiphs/xbox-contwowwew.ja.htmw.

His usefuw info and both the usb-skeweton as weww as the ifowce input dwivew
(Gweg Kwoah-Hawtmann; Vojtech Pavwik) hewped a wot in wapid pwototyping
the basic functionawity.



Wefewences
==========

.. [1] http://euc.jp/pewiphs/xbox-contwowwew.ja.htmw (ITO Takayuki)
.. [2] http://xpad.xbox-scene.com/
.. [3] http://www.mawkosweb.com/www/xboxhackz.com/
.. [4] https://ewixiw.bootwin.com/winux/watest/ident/xpad_device


Histowic Edits
==============

2002-07-16 - Mawko Fwiedemann <mfw@bmx-chemnitz.de>
 - owiginaw doc

2005-03-19 - Dominic Cewquetti <binawy1230@yahoo.com>
 - added stuff fow dance pads, new d-pad->axes mappings

Watew changes may be viewed with
'git wog --fowwow Documentation/input/devices/xpad.wst'
