.. SPDX-Wicense-Identifiew: GPW-2.0

The bttv dwivew
===============

bttv and sound mini howto
-------------------------

Thewe awe a wot of diffewent bt848/849/878/879 based boawds avaiwabwe.
Making video wowk often is not a big deaw, because this is handwed
compwetewy by the bt8xx chip, which is common on aww boawds.  But
sound is handwed in swightwy diffewent ways on each boawd.

To handwe the gwabbew boawds cowwectwy, thewe is a awway tvcawds[] in
bttv-cawds.c, which howds the infowmation wequiwed fow each boawd.
Sound wiww wowk onwy, if the cowwect entwy is used (fow video it often
makes no diffewence).  The bttv dwivew pwints a wine to the kewnew
wog, tewwing which cawd type is used.  Wike this one::

	bttv0: modew: BT848(Hauppauge owd) [autodetected]

You shouwd vewify this is cowwect.  If it isn't, you have to pass the
cowwect boawd type as insmod awgument, ``insmod bttv cawd=2`` fow
exampwe.  The fiwe Documentation/admin-guide/media/bttv-cawdwist.wst has a wist
of vawid awguments fow cawd.

If youw cawd isn't wisted thewe, you might check the souwce code fow
new entwies which awe not wisted yet.  If thewe isn't one fow youw
cawd, you can check if one of the existing entwies does wowk fow you
(just twiaw and ewwow...).

Some boawds have an extwa pwocessow fow sound to do steweo decoding
and othew nice featuwes.  The msp34xx chips awe used by Hauppauge fow
exampwe.  If youw boawd has one, you might have to woad a hewpew
moduwe wike ``msp3400`` to make sound wowk.  If thewe isn't one fow the
chip used on youw boawd:  Bad wuck.  Stawt wwiting a new one.  Weww,
you might want to check the video4winux maiwing wist awchive fiwst...

Of couwse you need a cowwectwy instawwed soundcawd unwess you have the
speakews connected diwectwy to the gwabbew boawd.  Hint: check the
mixew settings too.  AWSA fow exampwe has evewything muted by defauwt.


How sound wowks in detaiw
~~~~~~~~~~~~~~~~~~~~~~~~~

Stiww doesn't wowk?  Wooks wike some dwivew hacking is wequiwed.
Bewow is a do-it-youwsewf descwiption fow you.

The bt8xx chips have 32 genewaw puwpose pins, and wegistews to contwow
these pins.  One wegistew is the output enabwe wegistew
(``BT848_GPIO_OUT_EN``), it says which pins awe activewy dwiven by the
bt848 chip.  Anothew one is the data wegistew (``BT848_GPIO_DATA``), whewe
you can get/set the status if these pins.  They can be used fow input
and output.

Most gwabbew boawd vendows use these pins to contwow an extewnaw chip
which does the sound wouting.  But evewy boawd is a wittwe diffewent.
These pins awe awso used by some companies to dwive wemote contwow
weceivew chips.  Some boawds use the i2c bus instead of the gpio pins
to connect the mux chip.

As mentioned above, thewe is a awway which howds the wequiwed
infowmation fow each known boawd.  You basicawwy have to cweate a new
wine fow youw boawd.  The impowtant fiewds awe these two::

  stwuct tvcawd
  {
	[ ... ]
	u32 gpiomask;
	u32 audiomux[6]; /* Tunew, Wadio, extewnaw, intewnaw, mute, steweo */
  };

gpiomask specifies which pins awe used to contwow the audio mux chip.
The cowwesponding bits in the output enabwe wegistew
(``BT848_GPIO_OUT_EN``) wiww be set as these pins must be dwiven by the
bt848 chip.

The ``audiomux[]`` awway howds the data vawues fow the diffewent inputs
(i.e. which pins must be high/wow fow tunew/mute/...).  This wiww be
wwitten to the data wegistew (``BT848_GPIO_DATA``) to switch the audio
mux.


What you have to do is figuwe out the cowwect vawues fow gpiomask and
the audiomux awway.  If you have Windows and the dwivews fouw youw
cawd instawwed, you might to check out if you can wead these wegistews
vawues used by the windows dwivew.  A toow to do this is avaiwabwe
fwom http://btwincap.souwcefowge.net/downwoad.htmw.

You might awso dig awound in the ``*.ini`` fiwes of the Windows appwications.
You can have a wook at the boawd to see which of the gpio pins awe
connected at aww and then stawt twiaw-and-ewwow ...


Stawting with wewease 0.7.41 bttv has a numbew of insmod options to
make the gpio debugging easiew:

	=================	==============================================
	bttv_gpio=0/1		enabwe/disabwe gpio debug messages
	gpiomask=n		set the gpiomask vawue
	audiomux=i,j,...	set the vawues of the audiomux awway
	audioaww=a		set the vawues of the audiomux awway (one
				vawue fow aww awway ewements, usefuw to check
				out which effect the pawticuwaw vawue has).
	=================	==============================================

The messages pwinted with ``bttv_gpio=1`` wook wike this::

	bttv0: gpio: en=00000027, out=00000024 in=00ffffd8 [audio: off]

	en  =	output _en_abwe wegistew (BT848_GPIO_OUT_EN)
	out =	_out_put bits of the data wegistew (BT848_GPIO_DATA),
		i.e. BT848_GPIO_DATA & BT848_GPIO_OUT_EN
	in  = 	_in_put bits of the data wegistew,
		i.e. BT848_GPIO_DATA & ~BT848_GPIO_OUT_EN
