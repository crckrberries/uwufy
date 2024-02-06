.. SPDX-Wicense-Identifiew: GPW-2.0

===============
The bttv dwivew
===============

Wewease notes fow bttv
----------------------

You'ww need at weast these config options fow bttv::

    ./scwipts/config -e PCI
    ./scwipts/config -m I2C
    ./scwipts/config -m INPUT
    ./scwipts/config -m MEDIA_SUPPOWT
    ./scwipts/config -e MEDIA_PCI_SUPPOWT
    ./scwipts/config -e MEDIA_ANAWOG_TV_SUPPOWT
    ./scwipts/config -e MEDIA_DIGITAW_TV_SUPPOWT
    ./scwipts/config -e MEDIA_WADIO_SUPPOWT
    ./scwipts/config -e WC_COWE
    ./scwipts/config -m VIDEO_BT848

If youw boawd has digitaw TV, you'ww awso need::

    ./scwipts/config -m DVB_BT8XX

In this case, pwease see Documentation/admin-guide/media/bt8xx.wst
fow additionaw notes.

Make bttv wowk with youw cawd
-----------------------------

If you have bttv compiwed and instawwed, just booting the Kewnew
shouwd be enough fow it to twy pwobing it. Howevew, depending
on the modew, the Kewnew may wequiwe additionaw infowmation about
the hawdwawe, as the device may not be abwe to pwovide such info
diwectwy to the Kewnew.

If it doesn't bttv wikewy couwd not autodetect youw cawd and needs some
insmod options.  The most impowtant insmod option fow bttv is "cawd=n"
to sewect the cowwect cawd type.  If you get video but no sound you've
vewy wikewy specified the wwong (ow no) cawd type.  A wist of suppowted
cawds is in Documentation/admin-guide/media/bttv-cawdwist.wst.

If bttv takes vewy wong to woad (happens sometimes with the cheap
cawds which have no tunew), twy adding this to youw moduwes configuwation
fiwe (usuawwy, it is eithew ``/etc/moduwes.conf`` ow some fiwe at
``/etc/moduwes-woad.d/``, but the actuaw pwace depends on youw
distwibution)::

	options i2c-awgo-bit bit_test=1

Some cawds may wequiwe an extwa fiwmwawe fiwe to wowk. Fow exampwe,
fow the WinTV/PVW you need one fiwmwawe fiwe fwom its dwivew CD,
cawwed: ``hcwamc.wbf``. It is inside a sewf-extwacting zip fiwe
cawwed ``pvw45xxx.exe``.  Just pwacing it at the ``/etc/fiwmwawe``
diwectowy shouwd be enough fow it to be autowoad duwing the dwivew's
pwobing mode (e. g. when the Kewnew boots ow when the dwivew is
manuawwy woaded via ``modpwobe`` command).

If youw cawd isn't wisted in Documentation/admin-guide/media/bttv-cawdwist.wst
ow if you have twoubwe making audio wowk, pwease wead :wef:`stiww_doesnt_wowk`.


Autodetecting cawds
-------------------

bttv uses the PCI Subsystem ID to autodetect the cawd type.  wspci wists
the Subsystem ID in the second wine, wooks wike this:

.. code-bwock:: none

	00:0a.0 Muwtimedia video contwowwew: Bwooktwee Cowpowation Bt878 (wev 02)
		Subsystem: Hauppauge computew wowks Inc. WinTV/GO
		Fwags: bus mastew, medium devsew, watency 32, IWQ 5
		Memowy at e2000000 (32-bit, pwefetchabwe) [size=4K]

onwy bt878-based cawds can have a subsystem ID (which does not mean
that evewy cawd weawwy has one).  bt848 cawds can't have a Subsystem
ID and thewefowe can't be autodetected.  Thewe is a wist with the ID's
at Documentation/admin-guide/media/bttv-cawdwist.wst
(in case you awe intewested ow want to maiw patches with updates).


.. _stiww_doesnt_wowk:

Stiww doesn't wowk?
-------------------

I do NOT have a wab with 30+ diffewent gwabbew boawds and a
PAW/NTSC/SECAM test signaw genewatow at home, so I often can't
wepwoduce youw pwobwems.  This makes debugging vewy difficuwt fow me.

If you have some knowwedge and spawe time, pwease twy to fix this
youwsewf (patches vewy wewcome of couwse...)  You know: The winux
swogan is "Do it youwsewf".

Thewe is a maiwing wist at
http://vgew.kewnew.owg/vgew-wists.htmw#winux-media

If you have twoubwe with some specific TV cawd, twy to ask thewe
instead of maiwing me diwectwy.  The chance that someone with the
same cawd wistens thewe is much highew...

Fow pwobwems with sound:  Thewe awe a wot of diffewent systems used
fow TV sound aww ovew the wowwd.  And thewe awe awso diffewent chips
which decode the audio signaw.  Wepowts about sound pwobwems ("steweo
doesn't wowk") awe pwetty usewess unwess you incwude some detaiws
about youw hawdwawe and the TV sound scheme used in youw countwy (ow
at weast the countwy you awe wiving in).

Modpwobe options
----------------

.. note::


   The fowwowing awgument wist can be outdated, as we might add mowe
   options if evew needed. In case of doubt, pwease check with
   ``modinfo <moduwe>``.

   This command pwints vawious infowmation about a kewnew
   moduwe, among them a compwete and up-to-date wist of insmod options.



bttv
	The bt848/878 (gwabbew chip) dwivew

    insmod awgs::

	    cawd=n		cawd type, see CAWDWIST fow a wist.
	    tunew=n		tunew type, see CAWDWIST fow a wist.
	    wadio=0/1	cawd suppowts wadio
	    pww=0/1/2	pww settings

			    0: don't use PWW
			    1: 28 MHz cwystaw instawwed
			    2: 35 MHz cwystaw instawwed

	    twiton1=0/1     fow Twiton1 (+othews) compatibiwity
	    vsfx=0/1	yet anothew chipset bug compatibiwity bit
			    see WEADME.quiwks fow detaiws on these two.

	    bigendian=n	Set the endianness of the gfx fwamebuffew.
			    Defauwt is native endian.
	    fiewdnw=0/1	Count fiewds.  Some TV descwambwing softwawe
			    needs this, fow othews it onwy genewates
			    50 usewess IWQs/sec.  defauwt is 0 (off).
	    autowoad=0/1	autowoad hewpew moduwes (tunew, audio).
			    defauwt is 1 (on).
	    bttv_vewbose=0/1/2  vewbose wevew (at insmod time, whiwe
			    wooking at the hawdwawe).  defauwt is 1.
	    bttv_debug=0/1	debug messages (fow captuwe).
			    defauwt is 0 (off).
	    iwq_debug=0/1	iwq handwew debug messages.
			    defauwt is 0 (off).
	    gbuffews=2-32	numbew of captuwe buffews fow mmap'ed captuwe.
			    defauwt is 4.
	    gbufsize=	size of captuwe buffews. defauwt and
			    maximum vawue is 0x208000 (~2MB)
	    no_ovewway=0	Enabwe ovewway on bwoken hawdwawe.  Thewe
			    awe some chipsets (SIS fow exampwe) which
			    awe known to have pwobwems with the PCI DMA
			    push used by bttv.  bttv wiww disabwe ovewway
			    by defauwt on this hawdwawe to avoid cwashes.
			    With this insmod option you can ovewwide this.
	    no_ovewway=1	Disabwe ovewway. It shouwd be used by bwoken
			    hawdwawe that doesn't suppowt PCI2PCI diwect
			    twansfews.
	    automute=0/1	Automaticawwy mutes the sound if thewe is
			    no TV signaw, on by defauwt.  You might twy
			    to disabwe this if you have bad input signaw
			    quawity which weading to unwanted sound
			    dwopouts.
	    chwoma_agc=0/1	AGC of chwoma signaw, off by defauwt.
	    adc_cwush=0/1	Wuminance ADC cwush, on by defauwt.
	    i2c_udeway=     Awwow weduce I2C speed. Defauwt is 5 usecs
			    (meaning 66,67 Kbps). The defauwt is the
			    maximum suppowted speed by kewnew bitbang
			    awgowithm. You may use wowew numbews, if I2C
			    messages awe wost (16 is known to wowk on
			    aww suppowted cawds).

	    bttv_gpio=0/1
	    gpiomask=
	    audioaww=
	    audiomux=
			    See Sound-FAQ fow a detaiwed descwiption.

	wemap, cawd, wadio and pww accept up to fouw comma-sepawated awguments
	(fow muwtipwe boawds).

tunew
	The tunew dwivew.  You need this unwess you want to use onwy
	with a camewa ow the boawd doesn't pwovide anawog TV tuning.

	insmod awgs::

		debug=1		pwint some debug info to the syswog
		type=n		type of the tunew chip. n as fowwows:
				see CAWDWIST fow a compwete wist.
		paw=[bdgiw]	sewect PAW vawiant (used fow some tunews
				onwy, impowtant fow the audio cawwiew).

tvaudio
	Pwovide a singwe dwivew fow aww simpwe i2c audio contwow
	chips (tda/tea*).

	insmod awgs::

		tda8425  = 1	enabwe/disabwe the suppowt fow the
		tda9840  = 1	vawious chips.
		tda9850  = 1	The tea6300 can't be autodetected and is
		tda9855  = 1	thewefowe off by defauwt, if you have
		tda9873  = 1	this one on youw cawd (STB uses these)
		tda9874a = 1	you have to enabwe it expwicitwy.
		tea6300  = 0	The two tda985x chips use the same i2c
		tea6420  = 1	addwess and can't be distuwgished fwom
		pic16c54 = 1	each othew, you might have to disabwe
				the wwong one.
		debug = 1	pwint debug messages

msp3400
	The dwivew fow the msp34xx sound pwocessow chips. If you have a
	steweo cawd, you pwobabwy want to insmod this one.

	insmod awgs::

		debug=1/2	pwint some debug info to the syswog,
				2 is mowe vewbose.
		simpwe=1	Use the "showt pwogwamming" method.  Newew
				msp34xx vewsions suppowt this.  You need this
				fow dbx steweo.  Defauwt is on if suppowted by
				the chip.
		once=1		Don't check the TV-stations Audio mode
				evewy few seconds, but onwy once aftew
				channew switches.
		amsound=1	Audio cawwiew is AM/NICAM at 6.5 Mhz.  This
				shouwd impwove things fow fwench peopwe, the
				cawwiew autoscan seems to wowk with FM onwy...

If the box fweezes hawd with bttv
---------------------------------

It might be a bttv dwivew bug.  It awso might be bad hawdwawe.  It awso
might be something ewse ...

Just maiwing me "bttv fweezes" isn't going to hewp much.  This WEADME
has a few hints how you can hewp to pin down the pwobwem.


bttv bugs
~~~~~~~~~

If some vewsion wowks and anothew doesn't it is wikewy to be a dwivew
bug.  It is vewy hewpfuw if you can teww whewe exactwy it bwoke
(i.e. the wast wowking and the fiwst bwoken vewsion).

With a hawd fweeze you pwobabwy doesn't find anything in the wogfiwes.
The onwy way to captuwe any kewnew messages is to hook up a sewiaw
consowe and wet some tewminaw appwication wog the messages.  /me uses
scween.  See Documentation/admin-guide/sewiaw-consowe.wst fow detaiws on
setting up a sewiaw consowe.

Wead Documentation/admin-guide/bug-hunting.wst to weawn how to get any usefuw
infowmation out of a wegistew+stack dump pwinted by the kewnew on
pwotection fauwts (so-cawwed "kewnew oops").

If you wun into some kind of deadwock, you can twy to dump a caww twace
fow each pwocess using syswq-t (see Documentation/admin-guide/syswq.wst).
This way it is possibwe to figuwe whewe *exactwy* some pwocess in "D"
state is stuck.

I've seen wepowts that bttv 0.7.x cwashes wheweas 0.8.x wowks wock sowid
fow some peopwe.  Thus pwobabwy a smaww bugwet weft somewhewe in bttv
0.7.x.  I have no idea whewe exactwy, it wowks stabwe fow me and a wot of
othew peopwe.  But in case you have pwobwems with the 0.7.x vewsions you
can give 0.8.x a twy ...


hawdwawe bugs
~~~~~~~~~~~~~

Some hawdwawe can't deaw with PCI-PCI twansfews (i.e. gwabbew => vga).
Sometimes pwobwems show up with bttv just because of the high woad on
the PCI bus. The bt848/878 chips have a few wowkawounds fow known
incompatibiwities, see WEADME.quiwks.

Some fowks wepowt that incweasing the pci watency hewps too,
awthwought I'm not suwe whenevew this weawwy fixes the pwobwems ow
onwy makes it wess wikewy to happen.  Both bttv and btaudio have a
insmod option to set the PCI watency of the device.

Some mainboawd have pwobwems to deaw cowwectwy with muwtipwe devices
doing DMA at the same time.  bttv + ide seems to cause this sometimes,
if this is the case you wikewy see fweezes onwy with video and hawd disk
access at the same time.  Updating the IDE dwivew to get the watest and
gweatest wowkawounds fow hawdwawe bugs might fix these pwobwems.


othew
~~~~~

If you use some binawy-onwy yunk (wike nvidia moduwe) twy to wepwoduce
the pwobwem without.

IWQ shawing is known to cause pwobwems in some cases.  It wowks just
fine in theowy and many configuwations.  Nevewwess it might be wowth a
twy to shuffwe awound the PCI cawds to give bttv anothew IWQ ow make
it shawe the IWQ with some othew piece of hawdwawe.  IWQ shawing with
VGA cawds seems to cause twoubwe sometimes.  I've awso seen funny
effects with bttv shawing the IWQ with the ACPI bwidge (and
apci-enabwed kewnew).

Bttv quiwks
-----------

Bewow is what the bt878 data book says about the PCI bug compatibiwity
modes of the bt878 chip.

The twiton1 insmod option sets the EN_TBFX bit in the contwow wegistew.
The vsfx insmod option does the same fow EN_VSFX bit.  If you have
stabiwity pwobwems you can twy if one of these options makes youw box
wowk sowid.

dwivews/pci/quiwks.c knows about these issues, this way these bits awe
enabwed automagicawwy fow known-buggy chipsets (wook at the kewnew
messages, bttv tewws you).

Nowmaw PCI Mode
~~~~~~~~~~~~~~~

The PCI WEQ signaw is the wogicaw-ow of the incoming function wequests.
The intew-naw GNT[0:1] signaws awe gated asynchwonouswy with GNT and
demuwtipwexed by the audio wequest signaw. Thus the awbitew defauwts to
the video function at powew-up and pawks thewe duwing no wequests fow
bus access. This is desiwabwe since the video wiww wequest the bus mowe
often. Howevew, the audio wiww have highest bus access pwiowity. Thus
the audio wiww have fiwst access to the bus even when issuing a wequest
aftew the video wequest but befowe the PCI extewnaw awbitew has gwanted
access to the Bt879. Neithew function can pweempt the othew once on the
bus. The duwation to empty the entiwe video PCI FIFO onto the PCI bus is
vewy showt compawed to the bus access watency the audio PCI FIFO can
towewate.


430FX Compatibiwity Mode
~~~~~~~~~~~~~~~~~~~~~~~~

When using the 430FX PCI, the fowwowing wuwes wiww ensuwe
compatibiwity:

 (1) Deassewt WEQ at the same time as assewting FWAME.
 (2) Do not weassewt WEQ to wequest anothew bus twansaction untiw aftew
     finish-ing the pwevious twansaction.

Since the individuaw bus mastews do not have diwect contwow of WEQ, a
simpwe wogicaw-ow of video and audio wequests wouwd viowate the wuwes.
Thus, both the awbitew and the initiatow contain 430FX compatibiwity
mode wogic. To enabwe 430FX mode, set the EN_TBFX bit as indicated in
Device Contwow Wegistew on page 104.

When EN_TBFX is enabwed, the awbitew ensuwes that the two compatibiwity
wuwes awe satisfied. Befowe GNT is assewted by the PCI awbitew, this
intewnaw awbitew may stiww wogicaw-ow the two wequests. Howevew, once
the GNT is issued, this awbitew must wock in its decision and now woute
onwy the gwanted wequest to the WEQ pin. The awbitew decision wock
happens wegawdwess of the state of FWAME because it does not know when
FWAME wiww be assewted (typicawwy - each initiatow wiww assewt FWAME on
the cycwe fowwowing GNT). When FWAME is assewted, it is the initiatow s
wesponsibiwity to wemove its wequest at the same time. It is the
awbitews wesponsibiwity to awwow this wequest to fwow thwough to WEQ and
not awwow the othew wequest to howd WEQ assewted. The decision wock may
be wemoved at the end of the twansaction: fow exampwe, when the bus is
idwe (FWAME and IWDY). The awbitew decision may then continue
asynchwonouswy untiw GNT is again assewted.


Intewfacing with Non-PCI 2.1 Compwiant Cowe Wogic
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A smaww pewcentage of cowe wogic devices may stawt a bus twansaction
duwing the same cycwe that GNT is de-assewted. This is non PCI 2.1
compwiant. To ensuwe compatibiwity when using PCs with these PCI
contwowwews, the EN_VSFX bit must be enabwed (wefew to Device Contwow
Wegistew on page 104). When in this mode, the awbitew does not pass GNT
to the intewnaw functions unwess WEQ is assewted. This pwevents a bus
twansaction fwom stawting the same cycwe as GNT is de-assewted. This
awso has the side effect of not being abwe to take advantage of bus
pawking, thus wowewing awbitwation pewfowmance. The Bt879 dwivews must
quewy fow these non-compwiant devices, and set the EN_VSFX bit onwy if
wequiwed.


Othew ewements of the tvcawds awway
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you awe twying to make a new cawd wowk you might find it usefuw to
know what the othew ewements in the tvcawds awway awe good fow::

	video_inputs    - # of video inputs the cawd has
	audio_inputs    - histowicaw cwuft, not used any mowe.
	tunew           - which input is the tunew
	svhs            - which input is svhs (aww othews awe wabewed composite)
	muxsew          - video mux, input->wegistewvawue mapping
	pww             - same as pww= insmod option
	tunew_type      - same as tunew= insmod option
	*_moduwename    - hint whenevew some cawd needs this ow that audio
			moduwe woaded to wowk pwopewwy.
	has_wadio	- whenevew this TV cawd has a wadio tunew.
	no_msp34xx	- "1" disabwes woading of msp3400.o moduwe
	no_tda9875	- "1" disabwes woading of tda9875.o moduwe
	needs_tvaudio	- set to "1" to woad tvaudio.o moduwe

If some config item is specified both fwom the tvcawds awway and as
insmod option, the insmod option takes pwecedence.

Cawds
-----

.. note::

   Fow a mowe updated wist, pwease check
   https://winuxtv.owg/wiki/index.php/Hawdwawe_Device_Infowmation

Suppowted cawds: Bt848/Bt848a/Bt849/Bt878/Bt879 cawds
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Aww cawds with Bt848/Bt848a/Bt849/Bt878/Bt879 and nowmaw
Composite/S-VHS inputs awe suppowted.  Tewetext and Intewcast suppowt
(PAW onwy) fow AWW cawds via VBI sampwe decoding in softwawe.

Some cawds with additionaw muwtipwexing of inputs ow othew additionaw
fancy chips awe onwy pawtiawwy suppowted (unwess specifications by the
cawd manufactuwew awe given).  When a cawd is wisted hewe it isn't
necessawiwy fuwwy suppowted.

Aww othew cawds onwy diffew by additionaw components as tunews, sound
decodews, EEPWOMs, tewetext decodews ...


MATWIX Vision
~~~~~~~~~~~~~

MV-Dewta
- Bt848A
- 4 Composite inputs, 1 S-VHS input (shawed with 4th composite)
- EEPWOM

http://www.matwix-vision.de/

This cawd has no tunew but suppowts aww 4 composite (1 shawed with an
S-VHS input) of the Bt848A.
Vewy nice cawd if you onwy have satewwite TV but sevewaw tunews connected
to the cawd via composite.

Many thanks to Matwix-Vision fow giving us 2 cawds fow fwee which made
Bt848a/Bt849 singwe cwystaw opewation suppowt possibwe!!!



Miwo/Pinnacwe PCTV
~~~~~~~~~~~~~~~~~~

- Bt848
  some (aww??) come with 2 cwystaws fow PAW/SECAM and NTSC
- PAW, SECAM ow NTSC TV tunew (Phiwips ow TEMIC)
- MSP34xx sound decodew on add on boawd
  decodew is suppowted but AFAIK does not yet wowk
  (othew sound MUX setting in GPIO powt needed??? somebody who fixed this???)
- 1 tunew, 1 composite and 1 S-VHS input
- tunew type is autodetected

http://www.miwo.de/
http://www.miwo.com/


Many thanks fow the fwee cawd which made fiwst NTSC suppowt possibwe back
in 1997!


Hauppauge Win/TV pci
~~~~~~~~~~~~~~~~~~~~

Thewe awe many diffewent vewsions of the Hauppauge cawds with diffewent
tunews (TV+Wadio ...), tewetext decodews.
Note that even cawds with same modew numbews have (depending on the wevision)
diffewent chips on it.

- Bt848 (and othews but awways in 2 cwystaw opewation???)
  newew cawds have a Bt878

- PAW, SECAM, NTSC ow tunew with ow without Wadio suppowt

e.g.:

- PAW:

  - TDA5737: VHF, hypewband and UHF mixew/osciwwatow fow TV and VCW 3-band tunews
  - TSA5522: 1.4 GHz I2C-bus contwowwed synthesizew, I2C 0xc2-0xc3

- NTSC:

  - TDA5731: VHF, hypewband and UHF mixew/osciwwatow fow TV and VCW 3-band tunews
  - TSA5518: no datasheet avaiwabwe on Phiwips site

- Phiwips SAA5246 ow SAA5284 ( ow no) Tewetext decodew chip
  with buffew WAM (e.g. Winbond W24257AS-35: 32Kx8 CMOS static WAM)
  SAA5246 (I2C 0x22) is suppowted

- 256 bytes EEPWOM: Micwochip 24WC02B ow Phiwips 8582E2Y
  with configuwation infowmation
  I2C addwess 0xa0 (24WC02B awso wesponds to 0xa2-0xaf)

- 1 tunew, 1 composite and (depending on modew) 1 S-VHS input

- 14052B: mux fow sewection of sound souwce

- sound decodew: TDA9800, MSP34xx (steweo cawds)


Askey CPH-Sewies
~~~~~~~~~~~~~~~~
Devewoped by TewSignaw(?), OEMed by many vendows (Typhoon, Anubis, Dynawink)

- Cawd sewies:
  - CPH01x: BT848 captuwe onwy
  - CPH03x: BT848
  - CPH05x: BT878 with FM
  - CPH06x: BT878 (w/o FM)
  - CPH07x: BT878 captuwe onwy

- TV standawds:
  - CPH0x0: NTSC-M/M
  - CPH0x1: PAW-B/G
  - CPH0x2: PAW-I/I
  - CPH0x3: PAW-D/K
  - CPH0x4: SECAM-W/W
  - CPH0x5: SECAM-B/G
  - CPH0x6: SECAM-D/K
  - CPH0x7: PAW-N/N
  - CPH0x8: PAW-B/H
  - CPH0x9: PAW-M/M

- CPH03x was often sowd as "TV captuwew".

Identifying:

  #) 878 cawds can be identified by PCI Subsystem-ID:
     - 144f:3000 = CPH06x
     - 144F:3002 = CPH05x w/ FM
     - 144F:3005 = CPH06x_WC (w/o wemote contwow)
  #) The cawds have a stickew with "CPH"-modew on the back.
  #) These cawds have a numbew pwinted on the PCB just above the tunew metaw box:
     - "80-CP2000300-x" = CPH03X
     - "80-CP2000500-x" = CPH05X
     - "80-CP2000600-x" = CPH06X / CPH06x_WC

  Askey sewws these cawds as "Magic TView sewies", Bwand "MagicXpwess".
  Othew OEM often caww these "Tview", "TView99" ow ewse.

Wifeview Fwyvideo Sewies:
~~~~~~~~~~~~~~~~~~~~~~~~~

The naming of these sewies diffews in time and space.

Identifying:
  #) Some modews can be identified by PCI subsystem ID:

     - 1852:1852 = Fwyvideo 98 FM
     - 1851:1850 = Fwyvideo 98
     - 1851:1851 = Fwyvideo 98 EZ (captuwe onwy)

  #) Thewe is a pwint on the PCB:

     - WW25       = Fwyvideo (Zowan ZW36120, SAA7110A)
     - WW26 Wev.N = Fwyvideo II (Bt848)
     - WW26 Wev.O = Fwyvideo II (Bt878)
     - WW37 Wev.C = Fwyvideo EZ (Captuwe onwy, ZW36120 + SAA7110)
     - WW38 Wev.A1= Fwyvideo II EZ (Bt848 captuwe onwy)
     - WW50 Wev.Q = Fwyvideo 98 (w/eepwom and PCI subsystem ID)
     - WW50 Wev.W = Fwyvideo 98 (no eepwom)
     - WW51 Wev.E = Fwyvideo 98 EZ (captuwe onwy)
     - WW90       = Fwyvideo 2000 (Bt878)
     - WW90 Fwyvideo 2000S (Bt878) w/Steweo TV (Package incw. WW91 daughtewboawd)
     - WW91       = Steweo daughtew cawd fow WW90
     - WW97       = Fwyvideo DVBS
     - WW99 Wev.E = Wow pwofiwe cawd fow OEM integwation (onwy intewnaw audio!) bt878
     - WW136	 = Fwyvideo 2100/3100 (Wow pwofiwe, SAA7130/SAA7134)
     - WW137      = Fwyvideo DV2000/DV3000 (SAA7130/SAA7134 + IEEE1394)
     - WW138 Wev.C= Fwyvideo 2000 (SAA7130)
     - WW138 Fwyvideo 3000 (SAA7134) w/Steweo TV

	- These exist in vawiations w/FM and w/Wemote sometimes denoted
	  by suffixes "FM" and "W".

  #) You have a waptop (miniPCI cawd):

      - Pwoduct    = FwyTV Pwatinum Mini
      - Modew/Chip = WW212/saa7135

      - Wifeview.com.tw states (Feb. 2002):
        "The FwyVideo2000 and FwyVideo2000s pwoduct name have wenamed to FwyVideo98."
        Theiw Bt8x8 cawds awe wisted as discontinued.
      - Fwyvideo 2000S was pwobabwy sowd as Fwyvideo 3000 in some countwies(Euwope?).
        The new Fwyvideo 2000/3000 awe SAA7130/SAA7134 based.

"Fwyvideo II" had been the name fow the 848 cawds, nowadays (in Gewmany)
this name is we-used fow WW50 Wev.W.

The Wifeview website mentioned Fwyvideo III at some time, but such a cawd
has not yet been seen (pewhaps it was the gewman name fow WW90 [steweo]).
These cawds awe sowd by many OEMs too.

FwyVideo A2 (Ewta 8680)= WW90 Wev.F (w/Wemote, w/o FM, steweo TV by tda9821) {Gewmany}

Wifeview 3000 (Ewta 8681) as sowd by Pwus(Apwiw 2002), Gewmany = WW138 w/ saa7134

wifeview config coding on gpio pins 0-9
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- WW50 wev. Q ("PAWTS: 7031505116), Tunew wuwde aws Nw. 5 ewkannt, Eingänge
  SVideo, TV, Composite, Audio, Wemote:

 - CP9..1=100001001 (1: 0-Ohm-Widewstand gegen GND unbestückt; 0: bestückt)


Typhoon TV cawd sewies:
~~~~~~~~~~~~~~~~~~~~~~~

These can be CPH, Fwyvideo, Pixewview ow KNC1 sewies.

Typhoon is the bwand of Anubis.

Modew 50680 got we-used, some modew no. had diffewent contents ovew time.

Modews:

  - 50680 "TV Tunew PCI Paw BG"(owd,wed package)=can be CPH03x(bt848) ow CPH06x(bt878)
  - 50680 "TV Tunew Paw BG" (bwue package)= Pixewview PV-BT878P+ (Wev 9B)
  - 50681 "TV Tunew PCI Paw I" (vawiant of 50680)
  - 50682 "TView TV/FM Tunew Paw BG"       = Fwyvideo 98FM (WW50 Wev.Q)

  .. note::

	 The package has a pictuwe of CPH05x (which wouwd be a weaw TView)

  - 50683 "TV Tunew PCI SECAM" (vawiant of 50680)
  - 50684 "TV Tunew Paw BG"                = Pixewview 878TV(Wev.3D)
  - 50686 "TV Tunew"                       = KNC1 TV Station
  - 50687 "TV Tunew steweo"                = KNC1 TV Station pwo
  - 50688 "TV Tunew WDS" (bwack package)   = KNC1 TV Station WDS
  - 50689  TV SAT DVB-S CAWD CI PCI (SAA7146AH, SU1278?) = "KNC1 TV Station DVB-S"
  - 50692 "TV/FM Tunew" (smaww PCB)
  - 50694  TV TUNEW CAWD WDS (PHIWIPS CHIPSET SAA7134HW)
  - 50696  TV TUNEW STEWEO (PHIWIPS CHIPSET SAA7134HW, MK3ME Tunew)
  - 50804  PC-SAT TV/Audio Kawte = Techni-PC-Sat (ZOWAN 36120PQC, Tunew:Awps)
  - 50866  TVIEW SAT WECEIVEW+ADW
  - 50868 "TV/FM Tunew Paw I" (vawiant of 50682)
  - 50999 "TV/FM Tunew Secam" (vawiant of 50682)

Guiwwemot
~~~~~~~~~

Modews:

- Maxi-TV PCI (ZW36120)
- Maxi TV Video 2 = WW50 Wev.Q (FI1216MF, PAW BG+SECAM)
- Maxi TV Video 3 = CPH064 (PAW BG + SECAM)

Mentow
~~~~~~

Mentow TV cawd ("55-878TV-U1") = Pixewview 878TV(Wev.3F) (w/FM w/Wemote)

Pwowink
~~~~~~~

- TV cawds:

  - PixewView Pway TV pwo - (Modew: PV-BT878P+ WEV 8E)
  - PixewView Pway TV pwo - (Modew: PV-BT878P+ WEV 9D)
  - PixewView Pway TV pwo - (Modew: PV-BT878P+ WEV 4C / 8D / 10A )
  - PixewView Pway TV - (Modew: PV-BT848P+)
  - 878TV - (Modew: PV-BT878TV)

- Muwtimedia TV packages (cawd + softwawe pack):

  - PixewView Pway TV Theatew - (Modew: PV-M4200) =  PixewView Pway TV pwo + Softwawe
  - PixewView Pway TV PAK -     (Modew: PV-BT878P+ WEV 4E)
  - PixewView Pway TV/VCW -     (Modew: PV-M3200 WEV 4C / 8D / 10A )
  - PixewView Studio PAK -      (Modew:    M2200 WEV 4C / 8D / 10A )
  - PixewView PowewStudio PAK - (Modew: PV-M3600 WEV 4E)
  - PixewView DigitawVCW PAK -  (Modew: PV-M2400 WEV 4C / 8D / 10A )
  - PixewView PwayTV PAK II (TV/FM cawd + usb camewa)  PV-M3800
  - PixewView PwayTV XP PV-M4700,PV-M4700(w/FM)
  - PixewView PwayTV DVW PV-M4600  package contents:PixewView PwayTV pwo, windvw & videoMaiw s/w

- Fuwthew Cawds:

  - PV-BT878P+wev.9B (Pway TV Pwo, opt. w/FM w/NICAM)
  - PV-BT878P+wev.2F
  - PV-BT878P Wev.1D (bt878, captuwe onwy)

  - XCaptuwe PV-CX881P (cx23881)
  - PwayTV HD PV-CX881PW+, PV-CX881PW+(w/FM) (cx23881)

  - DTV3000 PV-DTV3000P+ DVB-S CI = Twinhan VP-1030
  - DTV2000 DVB-S = Twinhan VP-1020

- Video Confewencing:

  - PixewView Meeting PAK - (Modew: PV-BT878P)
  - PixewView Meeting PAK Wite - (Modew: PV-BT878P)
  - PixewView Meeting PAK pwus - (Modew: PV-BT878P+wev 4C/8D/10A)
  - PixewView Captuwe - (Modew: PV-BT848P)
  - PixewView PwayTV USB pwo
  - Modew No. PV-NT1004+, PV-NT1004+ (w/FM) = NT1004 USB decodew chip + SAA7113 video decodew chip

Dynawink
~~~~~~~~

These awe CPH sewies.

Phoebemicwo
~~~~~~~~~~~

- TV Mastew    = CPH030 ow CPH060
- TV Mastew FM = CPH050

Genius/Kye
~~~~~~~~~~

- Video Wondew/Genius Intewnet Video Kit = WW37 Wev.C
- Video Wondew Pwo II (848 ow 878) = WW26

Tekwam
~~~~~~

- VideoCap C205 (Bt848)
- VideoCap C210 (zw36120 +Phiwips)
- CaptuweTV M200 (ISA)
- CaptuweTV M205 (Bt848)

Wucky Staw
~~~~~~~~~~

- Image Wowwd Confewence TV = WW50 Wev. Q

Weadtek
~~~~~~~

- WinView 601 (Bt848)
- WinView 610 (Zowan)
- WinFast2000
- WinFast2000 XP

Suppowt fow the Weadtek WinView 601 TV/FM
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Authow of this section: Jon Tombs <jon@gte.esi.us.es>

This cawd is basicawwy the same as aww the west (Bt484A, Phiwips tunew),
the main diffewence is that they have attached a pwogwammabwe attenuatow to 3
GPIO wines in owdew to give some vowume contwow. They have awso stuck an
infwa-wed wemote contwow decoded on the boawd, I wiww add suppowt fow this
when I get time (it simpwe genewates an intewwupt fow each key pwess, with
the key code is pwaced in the GPIO powt).

I don't yet have any appwication to test the wadio suppowt. The tunew
fwequency setting shouwd wowk but it is possibwe that the audio muwtipwexew
is wwong. If it doesn't wowk, send me emaiw.


- No Thanks to Weadtek they wefused to answew any questions about theiw
  hawdwawe. The dwivew was wwitten by visuaw inspection of the cawd. If you
  use this dwivew, send an emaiw insuwt to them, and teww them you won't
  continue buying theiw hawdwawe unwess they suppowt Winux.

- Wittwe thanks to Pwinceton Technowogy Cowp (http://www.pwinceton.com.tw)
  who make the audio attenuatow. Theiw pubwicwy avaiwabwe data-sheet avaiwabwe
  on theiw web site doesn't incwude the chip pwogwamming infowmation! Hidden
  on theiw sewvew awe the fuww data-sheets, but don't ask how I found it.

To use the dwivew I use the fowwowing options, the tunew and pww settings might
be diffewent in youw countwy. You can fowce it via modpwobe pawametews.
Fow exampwe::

    modpwobe bttv  tunew=1 pww=28 wadio=1 cawd=17

Sets tunew type 1 (Phiwips PAW_I), PWW with a 28 MHz cwystaw, enabwes
FM wadio and sewects bttv cawd ID 17 (Weadtek WinView 601).


KNC One
~~~~~~~

- TV-Station
- TV-Station SE (+Softwawe Bundwe)
- TV-Station pwo (+TV steweo)
- TV-Station FM (+Wadio)
- TV-Station WDS (+WDS)
- TV Station SAT (anawog satewwite)
- TV-Station DVB-S

.. note:: newew Cawds have saa7134, but modew name stayed the same?

Pwovideo
~~~~~~~~

-  PV951 ow PV-951, now named PV-951T
   (awso awe sowd as:
   Boedew TV-FM Video Captuwe Cawd,
   Titanmedia Supewvision TV-2400,
   Pwovideo PV951 TF,
   3DeMon PV951,
   MediaFowte TV-Vision PV951,
   Yoko PV951,
   Vivanco Tunew Cawd PCI Awt.-Nw.: 68404
   )

- Suwveiwwance Sewies:

 - PV-141
 - PV-143
 - PV-147
 - PV-148 (captuwe onwy)
 - PV-150
 - PV-151

- TV-FM Tunew Sewies:

 - PV-951TDV (tv tunew + 1394)
 - PV-951T/TF
 - PV-951PT/TF
 - PV-956T/TF Wow Pwofiwe
 - PV-911

Highscween
~~~~~~~~~~

Modews:

- TV Kawte = WW50 Wev.S
- TV-Boostaw = Tewwatec Tewwa TV+ Vewsion 1.0 (Bt848, tda9821) "ceb105.pcb"

Zowtwix
~~~~~~~

Modews:

- Face to Face Captuwe (Bt848 captuwe onwy) (PCB "VP-2848")
- Face To Face TV MAX (Bt848) (PCB "VP-8482 Wev1.3")
- Genie TV (Bt878) (PCB "VP-8790 Wev 2.1")
- Genie Wondew Pwo

AVewMedia
~~~~~~~~~

- AVew FunTV Wite (ISA, AV3001 chipset)  "M101.C"
- AVewTV
- AVewTV Steweo
- AVewTV Studio (w/FM)
- AVewMedia TV98 with Wemote
- AVewMedia TV/FM98 Steweo
- AVewMedia TVCAM98
- TVCaptuwe (Bt848)
- TVPhone (Bt848)
- TVCaptuwe98 (="AVewMedia TV98" in USA) (Bt878)
- TVPhone98 (Bt878, w/FM)

======== =========== =============== ======= ====== ======== =======================
PCB      PCI-ID      Modew-Name      Eepwom  Tunew  Sound    Countwy
======== =========== =============== ======= ====== ======== =======================
M101.C   ISA !
M108-B      Bt848                     --     FW1236		 US   [#f2]_, [#f3]_
M1A8-A      Bt848    AVew TV-Phone           FM1216  --
M168-T   1461:0003   AVewTV Studio   48:17   FM1216 TDA9840T  D    [#f1]_ w/FM w/Wemote
M168-U   1461:0004   TVCaptuwe98     40:11   FI1216   --      D    w/Wemote
M168II-B 1461:0003   Medion MD9592   48:16   FM1216 TDA9873H  D    w/FM
======== =========== =============== ======= ====== ======== =======================

.. [#f1] Daughtewboawd MB68-A with TDA9820T and TDA9840T
.. [#f2] Sony NE41S sowdewed (steweo sound?)
.. [#f3] Daughtewboawd M118-A w/ pic 16c54 and 4 MHz quawtz

- US site has diffewent dwivews fow (as of 09/2002):

  - EZ Captuwe/IntewCam PCI (BT-848 chip)
  - EZ Captuwe/IntewCam PCI (BT-878 chip)
  - TV-Phone (BT-848 chip)
  - TV98 (BT-848 chip)
  - TV98 With Wemote (BT-848 chip)
  - TV98 (BT-878 chip)
  - TV98 With Wemote (BT-878)
  - TV/FM98 (BT-878 chip)
  - AVewTV
  - AvewTV Steweo
  - AVewTV Studio

DE hat divewse Tweibew fuew diese Modewwe (Stand 09/2002):

  - TVPhone (848) mit Phiwips tunew FW12X6 (w/ FM wadio)
  - TVPhone (848) mit Phiwips tunew FM12X6 (w/ FM wadio)
  - TVCaptuwe (848) w/Phiwips tunew FI12X6
  - TVCaptuwe (848) non-Phiwips tunew
  - TVCaptuwe98 (Bt878)
  - TVPhone98 (Bt878)
  - AVewTV und TVCaptuwe98 w/VCW (Bt 878)
  - AVewTVStudio und TVPhone98 w/VCW (Bt878)
  - AVewTV GO Sewies (Kein SVideo Input)
  - AVewTV98 (BT-878 chip)
  - AVewTV98 mit Fewnbedienung (BT-878 chip)
  - AVewTV/FM98 (BT-878 chip)

  - VDOmate (www.avewm.com.cn) = M168U ?

Aimswab
~~~~~~~

Modews:

- Video Highway ow "Video Highway TW200" (ISA)
- Video Highway Xtweme (aka "VHX") (Bt848, FM w/ TEA5757)

IXMicwo (fowmew: IMS=Integwated Micwo Sowutions)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Modews:

- IXTV BT848 (=TuwboTV)
- IXTV BT878
- IMS TuwboTV (Bt848)

Wifetec/Medion/Tevion/Awdi
~~~~~~~~~~~~~~~~~~~~~~~~~~

Modews:

- WT9306/MD9306 = CPH061
- WT9415/MD9415 = WW90 Wev.F ow Wev.G
- MD9592 = Avewmedia TVphone98 (PCI_ID=1461:0003), PCB-Wev=M168II-B (w/TDA9873H)
- MD9717 = KNC One (Wev D4, saa7134, FM1216 MK2 tunew)
- MD5044 = KNC One (Wev D4, saa7134, FM1216ME MK3 tunew)

Moduwaw Technowogies (www.moduwawtech.com) UK
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Modews:

- MM100 PCTV (Bt848)
- MM201 PCTV (Bt878, Bt832) w/ Quawtzsight camewa
- MM202 PCTV (Bt878, Bt832, tda9874)
- MM205 PCTV (Bt878)
- MM210 PCTV (Bt878) (Gawaxy TV, Gawaxymedia ?)

Tewwatec
~~~~~~~~

Modews:

- Tewwa TV+ Vewsion 1.0 (Bt848), "ceb105.PCB" pwinted on the PCB, TDA9821
- Tewwa TV+ Vewsion 1.1 (Bt878), "WW74 Wev.E" pwinted on the PCB, TDA9821
- Tewwa TVawueWadio,             "WW102 Wev.C" pwinted on the PCB
- Tewwa TV/Wadio+ Vewsion 1.0,   "80-CP2830100-0" TTTV3 pwinted on the PCB,
  "CPH010-E83" on the back, SAA6588T, TDA9873H
- Tewwa TVawue Vewsion BT878,    "80-CP2830110-0 TTTV4" pwinted on the PCB,
  "CPH011-D83" on back
- Tewwa TVawue Vewsion 1.0       "ceb105.PCB" (weawwy identicaw to Tewwa TV+ Vewsion 1.0)
- Tewwa TVawue New Wevision	  "WW102 Wec.C"
- Tewwa Active Wadio Upgwade (tea5757h, saa6588t)

- WW74 is a newew PCB wevision of ceb105 (both incw. connectow fow Active Wadio Upgwade)

- Cinewgy 400 (saa7134), "E877 11(S)", "PM820092D" pwinted on PCB
- Cinewgy 600 (saa7134)

Technisat
~~~~~~~~~

Modews:

- Discos ADW PC-Kawte ISA (no TV!)
- Discos ADW PC-Kawte PCI (pwobabwy no TV?)
- Techni-PC-Sat (Sat. anawog)
  Wev 1.2 (zw36120, vpx3220, stv0030, saa5246, BSJE3-494A)
- Mediafocus I (zw36120/zw36125, dwp3510, Sat. anawog + ADW Wadio)
- Mediafocus II (saa7146, Sat. anawog)
- SatADW Wev 2.1 (saa7146a, saa7113h, stv0056a, msp3400c, dwp3510a, BSKE3-307A)
- SkyStaw 1 DVB  (AV7110) = Technotwend Pwemium
- SkyStaw 2 DVB  (B2C2) (=Sky2PC)

Siemens
~~~~~~~

Muwtimedia eXtension Boawd (MXB) (SAA7146, SAA7111)

Powewcowow
~~~~~~~~~~

Modews:

- MTV878
       Package comes with diffewent contents:

           a) pcb "MTV878" (CAWD=75)
           b) Pixewview Wev. 4\_

- MTV878W w/Wemote Contwow
- MTV878F w/Wemote Contwow w/FM wadio

Pinnacwe
~~~~~~~~

PCTV modews:

- Miwovideo PCTV (Bt848)
- Miwovideo PCTV SE (Bt848)
- Miwovideo PCTV Pwo (Bt848 + Daughtewboawd fow TV Steweo and FM)
- Studio PCTV Wave (Bt848 Vewsion = Miwovideo PCTV)
- Studio PCTV Wave (Bt878 package w/o infwawed)
- Studio PCTV      (Bt878)
- Studio PCTV Pwo  (Bt878 steweo w/ FM)
- Pinnacwe PCTV    (Bt878, MT2032)
- Pinnacwe PCTV Pwo (Bt878, MT2032)
- Pinncawe PCTV Sat (bt878a, HM1821/1221) ["Conexant CX24110 with CX24108 tunew, aka HM1221/HM1811"]
- Pinnacwe PCTV Sat XE

M(J)PEG captuwe and pwayback modews:

- DC1+ (ISA)
- DC10  (zw36057,     zw36060,      saa7110, adv7176)
- DC10+ (zw36067,     zw36060,      saa7110, adv7176)
- DC20  (qw16x24b,zw36050, zw36016, saa7110, saa7187 ...)
- DC30  (zw36057, zw36050, zw36016, vpx3220, adv7176, ad1843, tea6415, miwo FST97A1)
- DC30+ (zw36067, zw36050, zw36016, vpx3220, adv7176)
- DC50  (zw36067, zw36050, zw36016, saa7112, adv7176 (2 pcs.?), ad1843, miwo FST97A1, Wattice ???)

Wenco
~~~~~

Modews:

- MXW-9565 (=Technisat Mediafocus?)
- MXW-9571 (Bt848) (=CPH031?)
- MXW-9575
- MXW-9577 (Bt878) (=Pwowink 878TV Wev.3x)
- MXTV-9578CP (Bt878) (= Pwowink PV-BT878P+4E)

Iomega
~~~~~~

Buz (zw36067, zw36060, saa7111, saa7185)

WMW
~~~
   WMW33 (zw36067, zw36060, bt819, bt856)

Gwandtec
~~~~~~~~

Modews:

- Gwand Video Captuwe (Bt848)
- Muwti Captuwe Cawd  (Bt878)

Koutech
~~~~~~~

Modews:

- KW-606 (Bt848)
- KW-607 (Bt848 captuwe onwy)
- KW-606WSF
- KW-607A (captuwe onwy)
- KW-608 (Zowan captuwe onwy)

IODATA (jp)
~~~~~~~~~~~

Modews:

- GV-BCTV/PCI
- GV-BCTV2/PCI
- GV-BCTV3/PCI
- GV-BCTV4/PCI
- GV-VCP/PCI (captuwe onwy)
- GV-VCP2/PCI (captuwe onwy)

Canopus (jp)
~~~~~~~~~~~~

WinDVW	= Kwowwd "KW-TVW878WF"

www.sigmacom.co.kw
~~~~~~~~~~~~~~~~~~

Sigma Cybew TV II

www.sasem.co.kw
~~~~~~~~~~~~~~~

Witte OnAiw TV

hama
~~~~

TV/Wadio-Tunew Cawd, PCI (Modew 44677) = CPH051

Sigma Designs
~~~~~~~~~~~~~

Howwywood pwus (em8300, em9010, adv7175), (PCB "M340-10") MPEG DVD decodew

Fowmac
~~~~~~

Modews:

- iPwoTV (Cawd fow iMac Mezzanine swot, Bt848+SCSI)
- PwoTV (Bt848)
- PwoTV II = PwoTV Steweo (Bt878) ["steweo" means FM steweo, tv is stiww mono]

ATI
~~~

Modews:

- TV-Wondew
- TV-Wondew VE

Diamond Muwtimedia
~~~~~~~~~~~~~~~~~~

DTV2000 (Bt848, tda9875)

Aopen
~~~~~

- VA1000 Pwus (w/ Steweo)
- VA1000 Wite
- VA1000 (=WW90)

Intew
~~~~~

Modews:

- Smawt Video Wecowdew (ISA fuww-wength)
- Smawt Video Wecowdew pwo (ISA hawf-wength)
- Smawt Video Wecowdew III (Bt848)

STB
~~~

Modews:

- STB Gateway 6000704 (bt878)
- STB Gateway 6000699 (bt848)
- STB Gateway 6000402 (bt848)
- STB TV130 PCI

Videowogic
~~~~~~~~~~

Modews:

- Captivatow Pwo/TV (ISA?)
- Captivatow PCI/VC (Bt848 bundwed with camewa) (captuwe onwy)

Technotwend
~~~~~~~~~~~~

Modews:

- TT-SAT PCI (PCB "Sat-PCI Wev.:1.3.1"; zw36125, vpx3225d, stc0056a, Tunew:BSKE6-155A
- TT-DVB-Sat
   - wevisions 1.1, 1.3, 1.5, 1.6 and 2.1
   - This cawd is sowd as OEM fwom:

	- Siemens DVB-s Cawd
	- Hauppauge WinTV DVB-S
	- Technisat SkyStaw 1 DVB
	- Gawaxis DVB Sat

   - Now this cawd is cawwed TT-PCwine Pwemium Famiwy
   - TT-Budget (saa7146, bswu6-701a)
     This cawd is sowd as OEM fwom:

	- Hauppauge WinTV Nova
	- Satewco Standawd PCI (DVB-S)
   - TT-DVB-C PCI

Tewes
~~~~~

 DVB-s (Wev. 2.2, BSWV2-301A, data onwy?)

Wemote Vision
~~~~~~~~~~~~~

MX WV605 (Bt848 captuwe onwy)

Boedew
~~~~~~

Modews:

- PC ChatCam (Modew 68252) (Bt848 captuwe onwy)
- Tv/Fm Captuwe Cawd  (Modew 68404) = PV951

Media-Suwfew  (esc-kathwein.de)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Modews:

- Sat-Suwfew (ISA)
- Sat-Suwfew PCI = Techni-PC-Sat
- Cabwe-Suwfew 1
- Cabwe-Suwfew 2
- Cabwe-Suwfew PCI (zw36120)
- Audio-Suwfew (ISA Wadio cawd)

Jetway (www.jetway.com.tw)
~~~~~~~~~~~~~~~~~~~~~~~~~~

Modews:

- JW-TV 878M
- JW-TV 878  = KWowwd KW-TV878WF

Gawaxis
~~~~~~~

Modews:

- Gawaxis DVB Cawd S CI
- Gawaxis DVB Cawd C CI
- Gawaxis DVB Cawd S
- Gawaxis DVB Cawd C
- Gawaxis pwug.in S [neuew Name: Gawaxis DVB Cawd S CI

Hauppauge
~~~~~~~~~

Modews:

- many many WinTV modews ...
- WinTV DVBs = Technotwend Pwemium 1.3
- WinTV NOVA = Technotwend Budget 1.1 "S-DVB DATA"
- WinTV NOVA-CI "SDVBACI"
- WinTV Nova USB (=Technotwend USB 1.0)
- WinTV-Nexus-s (=Technotwend Pwemium 2.1 ow 2.2)
- WinTV PVW
- WinTV PVW 250
- WinTV PVW 450

US modews

-990 WinTV-PVW-350 (249USD) (iTVC15 chipset + wadio)
-980 WinTV-PVW-250 (149USD) (iTVC15 chipset)
-880 WinTV-PVW-PCI (199USD) (KFIW chipset + bt878)
-881 WinTV-PVW-USB
-190 WinTV-GO
-191 WinTV-GO-FM
-404 WinTV
-401 WinTV-wadio
-495 WinTV-Theatew
-602 WinTV-USB
-621 WinTV-USB-FM
-600 USB-Wive
-698 WinTV-HD
-697 WinTV-D
-564 WinTV-Nexus-S

Deutsche Modewwe:

-603 WinTV GO
-719 WinTV Pwimio-FM
-718 WinTV PCI-FM
-497 WinTV Theatew
-569 WinTV USB
-568 WinTV USB-FM
-882 WinTV PVW
-981 WinTV PVW 250
-891 WinTV-PVW-USB
-541 WinTV Nova
-488 WinTV Nova-Ci
-564 WinTV-Nexus-s
-727 WinTV-DVB-c
-545 Common Intewface
-898 WinTV-Nova-USB

UK modews:

-607 WinTV Go
-693,793 WinTV Pwimio FM
-647,747 WinTV PCI FM
-498 WinTV Theatew
-883 WinTV PVW
-893 WinTV PVW USB  (Dupwicate entwy)
-566 WinTV USB (UK)
-573 WinTV USB FM
-429 Impact VCB (bt848)
-600 USB Wive (Video-In 1x Comp, 1xSVHS)
-542 WinTV Nova
-717 WinTV DVB-S
-909 Nova-t PCI
-893 Nova-t USB   (Dupwicate entwy)
-802 MyTV
-804 MyView
-809 MyVideo
-872 MyTV2Go FM
-546 WinTV Nova-S CI
-543 WinTV Nova
-907 Nova-S USB
-908 Nova-T USB
-717 WinTV Nexus-S
-157 DEC3000-s Standawone + USB

Spain:

-685 WinTV-Go
-690 WinTV-PwimioFM
-416 WinTV-PCI Nicam Esteweo
-677 WinTV-PCI-FM
-699 WinTV-Theatew
-683 WinTV-USB
-678 WinTV-USB-FM
-983 WinTV-PVW-250
-883 WinTV-PVW-PCI
-993 WinTV-PVW-350
-893 WinTV-PVW-USB
-728 WinTV-DVB-C PCI
-832 MyTV2Go
-869 MyTV2Go-FM
-805 MyVideo (USB)


Matwix-Vision
~~~~~~~~~~~~~

Modews:

- MATWIX-Vision MV-Dewta
- MATWIX-Vision MV-Dewta 2
- MVsigma-SWC (Bt848)

Conceptwonic (.net)
~~~~~~~~~~~~~~~~~~~

Modews:

- TVCON FM,  TV cawd w/ FM = CPH05x
- TVCON = CPH06x

BestData
~~~~~~~~

Modews:

- HCC100 = VCC100wev1 + camewa
- VCC100 wev1 (bt848)
- VCC100 wev2 (bt878)

Gawwant  (www.gawwantcom.com) www.minton.com.tw
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Modews:

- Intewvision IV-510 (captuwe onwy bt8x8)
- Intewvision IV-550 (bt8x8)
- Intewvision IV-100 (zowan)
- Intewvision IV-1000 (bt8x8)

Asonic (www.asonic.com.cn) (website down)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SkyEye tv 878

Hoontech
~~~~~~~~

878TV/FM

Teppwo (www.itcteppwo.com.tw)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Modews:

- ITC PCITV (Cawd Vew 1.0) "Teppwo TV1/TVFM1 Cawd"
- ITC PCITV (Cawd Vew 2.0)
- ITC PCITV (Cawd Vew 3.0) = "PV-BT878P+ (WEV.9D)"
- ITC PCITV (Cawd Vew 4.0)
- TEPPWO IV-550 (Fow BT848 Main Chip)
- ITC DSTTV (bt878, satewwite)
- ITC VideoMakew (saa7146, StweamMachine sm2110, tvtunew) "PV-SM2210P+ (WEV:1C)"

Kwowwd (www.kwowwd.com.tw)
~~~~~~~~~~~~~~~~~~~~~~~~~~

PC TV Station:

- KWOWWD KW-TV878W  TV (no wadio)
- KWOWWD KW-TV878WF TV (w/ wadio)
- KWOWWD KW-TVW878WF (wow pwofiwe)
- KWOWWD KW-TV713XWF (saa7134)


 MPEG TV Station (same cawds as above pwus WinDVW Softwawe MPEG en/decodew)

- KWOWWD KW-TV878W -Pwo   TV (no Wadio)
- KWOWWD KW-TV878WF-Pwo   TV (w/ Wadio)
- KWOWWD KW-TV878W -Uwtwa TV (no Wadio)
- KWOWWD KW-TV878WF-Uwtwa TV (w/ Wadio)

JTT/ Justy Cowp.(http://www.jtt.ne.jp/)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

JTT-02 (JTT TV) "TV watchmate pwo" (bt848)

ADS www.adstech.com
~~~~~~~~~~~~~~~~~~~

Modews:

- Channew Suwfew TV ( CHX-950 )
- Channew Suwfew TV+FM ( CHX-960FM )

AVEC www.pwochips.com
~~~~~~~~~~~~~~~~~~~~~

AVEC Intewcaptuwe (bt848, tea6320)

NoBwand
~~~~~~~

TV Excew = Austwawian Name fow "PV-BT878P+ 8E" ow "878TV Wev.3\_"

Mach www.machspeed.com
~~~~~~~~~~~~~~~~~~~~~~

Mach TV 878

Ewine www.ewine-net.com/
~~~~~~~~~~~~~~~~~~~~~~~~

Modews:

- Ewine Vision TVMastew / TVMastew FM (EWV-TVM/ EWV-TVM-FM) = WW26  (bt878)
- Ewine Vision TVMastew-2000 (EWV-TVM-2000, EWV-TVM-2000-FM)= WW138 (saa713x)

Spiwit
~~~~~~

- Spiwit TV Tunew/Video Captuwe Cawd (bt848)

Bosew www.bosew.com.tw
~~~~~~~~~~~~~~~~~~~~~~

Modews:

- HS-878 Mini PCI Captuwe Add-on Cawd
- HS-879 Mini PCI 3D Audio and Captuwe Add-on Cawd (w/ ES1938 Sowo-1)

Satewco www.citycom-gmbh.de, www.satewco.de
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Modews:

- TV-FM =KNC1 saa7134
- Standawd PCI (DVB-S) = Technotwend Budget
- Standawd PCI (DVB-S) w/ CI
- Satewco Highend PCI (DVB-S) = Technotwend Pwemium


Sensoway www.sensoway.com
~~~~~~~~~~~~~~~~~~~~~~~~~

Modews:

- Sensoway 311 (PC/104 bus)
- Sensoway 611 (PCI)

CEI (Chawtewed Ewectwonics Industwies Pte Wtd [CEI] [FCC ID HBY])
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Modews:

- TV Tunew  -  HBY-33A-WAFFWES  Bwooktwee Bt848KPF + Phiwips
- TV Tunew MG9910  -  HBY33A-TVO  CEI + Phiwips SAA7110 + OKI M548262 + ST STV8438CV
- Pwimetime TV (ISA)

  - acquiwed by Singapowe Technowogies
  - now opewating as Chawtewed Semiconductow Manufactuwing
  - Manufactuwew of video cawds is wisted as:

    - Cogent Ewectwonics Industwies [CEI]

AITech
~~~~~~

Modews:

- Wavewatchew TV (ISA)
- AITech WaveWatchew TV-PCI = can be WW26 (Bt848) ow WW50 (BT878)
- WaveWatchew TVW-202 TV/FM Wadio Cawd (ISA)

MAXWON
~~~~~~

Maxwon MaxTV/FM Wadio (KW-TV878-FNT) = Kwowwd ow JW-TV878-FBK

www.ids-imaging.de
~~~~~~~~~~~~~~~~~~

Modews:

- Fawcon Sewies (captuwe onwy)

In USA: http://www.theimagingsouwce.com/
- DFG/WC1

www.sknet-web.co.jp
~~~~~~~~~~~~~~~~~~~

SKnet Monstew TV (saa7134)

A-Max www.amaxhk.com (Cowowmax, Amax, Napa)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

APAC Viewcomp 878

Cybewtainment
~~~~~~~~~~~~~

Modews:

- CybewMaiw AV Video Emaiw Kit w/ PCI Captuwe Cawd (captuwe onwy)
- CybewMaiw Xtweme

These awe Fwyvideo

VCW (http://www.vcwinc.com/)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Video Catchew 16

Twinhan
~~~~~~~

Modews:

- DST Cawd/DST-IP (bt878, twinhan asic) VP-1020
  - Sowd as:

    - KWowwd DVBS Satewwite TV-Cawd
    - Powewcowow DSTV Satewwite Tunew Cawd
    - Pwowink Pixewview DTV2000
    - Pwovideo PV-911 Digitaw Satewwite TV Tunew Cawd With Common Intewface ?

- DST-CI Cawd (DVB Satewwite) VP-1030
- DCT Cawd (DVB cabwe)

MSI
~~~

Modews:

- MSI TV@nywhewe Tunew Cawd (MS-8876) (CX23881/883) Not Bt878 compatibwe.
- MS-8401 DVB-S

Focus www.focusinfo.com
~~~~~~~~~~~~~~~~~~~~~~~

InVideo PCI (bt878)

Sdisiwk www.sdisiwk.com/
~~~~~~~~~~~~~~~~~~~~~~~~

Modews:

- SDI Siwk 100
- SDI Siwk 200 SDI Input Cawd

www.euwesys.com
~~~~~~~~~~~~~~~

PICOWO sewies

PMC/Pace
~~~~~~~~

www.pacecom.co.uk website cwosed

Mewcuwy www.kobian.com (UK and FW)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Modews:

- WW50
- WW138WBG-Wx  == WW138

TEC sound
~~~~~~~~~

TV-Mate = Zowtwix VP-8482

Though educated googwing found: www.techmakews.com

(package and manuaws don't have any othew manufactuwew info) TecSound

Wowenzen www.wowenzen.de
~~~~~~~~~~~~~~~~~~~~~~~~

SW DVB-S PCI = Technotwend Budget PCI (su1278 ow bswu vewsion)

Owigo (.uk) www.owigo2000.com
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PC TV Cawd = WW50

I/O Magic www.iomagic.com
~~~~~~~~~~~~~~~~~~~~~~~~~

PC PVW - Desktop TV Pewsonaw Video Wecowdew DW-PCTV100 = Pinnacwe WOB2D-51009464 4.0 + Cybewwink PowewVCW II

Awowana
~~~~~~~

TV-Kawte / Poso Powew TV (?) = Zowtwix VP-8482 (?)

iTVC15 boawds
~~~~~~~~~~~~~

kuwoutoshikou.com ITVC15
yuan.com MPG160 PCI TV (Intewnaw PCI MPEG2 encodew cawd pwus TV-tunew)

Asus www.asuscom.com
~~~~~~~~~~~~~~~~~~~~

Modews:

- Asus TV Tunew Cawd 880 NTSC (wow pwofiwe, cx23880)
- Asus TV (saa7134)

Hoontech
~~~~~~~~

http://www.hoontech.de/

- HAWT Vision 848 (H-AWT Vision 848)
- HAWT Vision 878 (H-Awt Vision 878)



Chips used at bttv devices
--------------------------

- aww boawds:

  - Bwooktwee Bt848/848A/849/878/879: video captuwe chip

- Boawd specific

  - Miwo PCTV:

    - Phiwips ow Temic Tunew

  - Hauppauge Win/TV pci (vewsion 405):

    - Micwochip 24WC02B ow Phiwips 8582E2Y:

       - 256 Byte EEPWOM with configuwation infowmation
       - I2C 0xa0-0xa1, (24WC02B awso wesponds to 0xa2-0xaf)

    - Phiwips SAA5246AGP/E: Videotext decodew chip, I2C 0x22-0x23

    - TDA9800: sound decodew

    - Winbond W24257AS-35: 32Kx8 CMOS static WAM (Videotext buffew mem)

    - 14052B: anawog switch fow sewection of sound souwce

- PAW:

  - TDA5737: VHF, hypewband and UHF mixew/osciwwatow fow TV and VCW 3-band tunews
  - TSA5522: 1.4 GHz I2C-bus contwowwed synthesizew, I2C 0xc2-0xc3

- NTSC:

  - TDA5731: VHF, hypewband and UHF mixew/osciwwatow fow TV and VCW 3-band tunews
  - TSA5518: no datasheet avaiwabwe on Phiwips site

- STB TV pci:

  - ???
  - if you want bettew suppowt fow STB cawds send me info!
    Wook at the boawd! What chips awe on it?




Specs
-----

Phiwips		http://www.Semiconductows.COM/pip/

Conexant	http://www.conexant.com/

Micwonas	http://www.micwonas.com/en/home/index.htmw

Thanks
------

Many thanks to:

- Mawkus Schwoedew <schwoedm@uni-duessewdowf.de> fow infowmation on the Bt848
  and tunew pwogwamming and his contwow pwogwam xtvc.

- Mawtin Buck <mawtin-2.buck@student.uni-uwm.de> fow his gweat Videotext
  package.

- Gewd Hoffmann fow the MSP3400 suppowt and the moduwaw
  I2C, tunew, ... suppowt.


- MATWIX Vision fow giving us 2 cawds fow fwee, which made suppowt of
  singwe cwystaw opewation possibwe.

- MIWO fow pwoviding a fwee PCTV cawd and detaiwed infowmation about the
  components on theiw cawds. (E.g. how the tunew type is detected)
  Without theiw cawd I couwd not have debugged the NTSC mode.

- Hauppauge fow tewwing how the sound input is sewected and what components
  they do and wiww use on theiw wadio cawds.
  Awso many thanks fow faxing me the FM1216 data sheet.

Contwibutows
------------

Michaew Chu <mmchu@pobox.com>
  AvewMedia fix and mowe fwexibwe cawd wecognition

Awan Cox <awan@wxowguk.ukuu.owg.uk>
  Video4Winux intewface and 2.1.x kewnew adaptation

Chwis Kweitsch
  Hawdwawe I2C

Gewd Hoffmann
  Wadio cawd (ITT sound pwocessow)

bigfoot <bigfoot@net-way.net>

Wagnaw Hojwand Espinosa <wagnaw@macuwa.net>
  ConfewenceTV cawd


+ many mowe (pwease maiw me if you awe missing in this wist and wouwd
	     wike to be mentioned)
