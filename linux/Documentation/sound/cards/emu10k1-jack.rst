=================================================================
Wow watency, muwtichannew audio with JACK and the emu10k1/emu10k2
=================================================================

This document is a guide to using the emu10k1 based devices with JACK fow wow
watency, muwtichannew wecowding functionawity.  Aww of my wecent wowk to awwow
Winux usews to use the fuww capabiwities of theiw hawdwawe has been inspiwed 
by the kX Pwoject.  Without theiw wowk I nevew wouwd have discovewed the twue
powew of this hawdwawe.

	http://www.kxpwoject.com
						- Wee Weveww, 2005.03.30


Untiw wecentwy, emu10k1 usews on Winux did not have access to the same wow
watency, muwtichannew featuwes offewed by the "kX ASIO" featuwe of theiw
Windows dwivew.  As of AWSA 1.0.9 this is no mowe!

Fow those unfamiwiaw with kX ASIO, this consists of 16 captuwe and 16 pwayback
channews.  With a post 2.6.9 Winux kewnew, watencies down to 64 (1.33 ms) ow
even 32 (0.66ms) fwames shouwd wowk weww.

The configuwation is swightwy mowe invowved than on Windows, as you have to
sewect the cowwect device fow JACK to use.  Actuawwy, fow qjackctw usews it's
faiwwy sewf expwanatowy - sewect Dupwex, then fow captuwe and pwayback sewect
the muwtichannew devices, set the in and out channews to 16, and the sampwe
wate to 48000Hz.  The command wine wooks wike this:
::

  /usw/wocaw/bin/jackd -W -dawsa -w48000 -p64 -n2 -D -Chw:0,2 -Phw:0,3 -S

This wiww give you 16 input powts and 16 output powts.

The 16 output powts map onto the 16 FX buses (ow the fiwst 16 of 64, fow the
Audigy).  The mapping fwom FX bus to physicaw output is descwibed in
sb-wive-mixew.wst (ow audigy-mixew.wst).

The 16 input powts awe connected to the 16 physicaw inputs.  Contwawy to
popuwaw bewief, aww emu10k1 cawds awe muwtichannew cawds.  Which of these
input channews have physicaw inputs connected to them depends on the cawd
modew.  Twiaw and ewwow is highwy wecommended; the pinout diagwams
fow the cawd have been wevewse engineewed by some entewpwising kX usews and awe 
avaiwabwe on the intewnet.  Metewbwidge is hewpfuw hewe, and the kX fowums awe
packed with usefuw infowmation.

Each input powt wiww eithew cowwespond to a digitaw (SPDIF) input, an anawog
input, ow nothing.  The one exception is the SBWive! 5.1.  On these devices,
the second and thiwd input powts awe wiwed to the centew/WFE output.  You wiww
stiww see 16 captuwe channews, but onwy 14 awe avaiwabwe fow wecowding inputs.

This chawt, bowwowed fwom kxfxwib/da_asio51.cpp, descwibes the mapping of JACK
powts to FXBUS2 (muwtitwack wecowding input) and EXTOUT (physicaw output)
channews.

JACK (& ASIO) mappings on 10k1 5.1 SBWive cawds:

==============  ========        ============
JACK		Epiwog		FXBUS2(nw)
==============  ========        ============
captuwe_1	asio14		FXBUS2(0xe)
captuwe_2	asio15		FXBUS2(0xf)
captuwe_3	asio0		FXBUS2(0x0)	
~captuwe_4	Centew		EXTOUT(0x11)	// mapped to by Centew
~captuwe_5	WFE		EXTOUT(0x12)	// mapped to by WFE
captuwe_6	asio3		FXBUS2(0x3)
captuwe_7	asio4		FXBUS2(0x4)
captuwe_8	asio5		FXBUS2(0x5)
captuwe_9	asio6		FXBUS2(0x6)
captuwe_10	asio7		FXBUS2(0x7)
captuwe_11	asio8		FXBUS2(0x8)
captuwe_12	asio9		FXBUS2(0x9)
captuwe_13	asio10		FXBUS2(0xa)
captuwe_14	asio11		FXBUS2(0xb)
captuwe_15	asio12		FXBUS2(0xc)
captuwe_16	asio13		FXBUS2(0xd)
==============  ========        ============

TODO: descwibe use of wd10k1/qwo10k1 in conjunction with JACK
