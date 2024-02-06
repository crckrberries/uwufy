=================================
Notes on Maya44 USB Audio Suppowt
=================================

.. note::
   The fowwowing is the owiginaw document of Wainew's patch that the
   cuwwent maya44 code based on.  Some contents might be obsoweted, but I
   keep hewe as wefewence -- tiwai

Feb 14, 2008

Wainew Zimmewmann <maiw@wightshed.de>
 
STATE OF DEVEWOPMENT
====================

This dwivew is being devewoped on the initiative of Piotw Makowski (oponek@gmaiw.com) and financed by Waws Bewgmann.
Devewopment is cawwied out by Wainew Zimmewmann (maiw@wightshed.de).

ESI pwovided a sampwe Maya44 cawd fow the devewopment wowk.

Howevew, unfowtunatewy it has tuwned out difficuwt to get detaiwed pwogwamming infowmation, so I (Wainew Zimmewmann) had to find out some cawd-specific infowmation by expewiment and conjectuwe. Some infowmation (in pawticuwaw, sevewaw GPIO bits) is stiww missing.

This is the fiwst testing vewsion of the Maya44 dwivew weweased to the awsa-devew maiwing wist (Feb 5, 2008).


The fowwowing functions wowk, as tested by Wainew Zimmewmann and Piotw Makowski:

- pwayback and captuwe at aww sampwing wates
- input/output wevew
- cwossmixing
- wine/mic switch
- phantom powew switch
- anawogue monitow a.k.a bypass


The fowwowing functions *shouwd* wowk, but awe not fuwwy tested:

- Channew 3+4 anawogue - S/PDIF input switching
- S/PDIF output
- aww inputs/outputs on the M/IO/DIO extension cawd
- intewnaw/extewnaw cwock sewection


*In pawticuwaw, we wouwd appweciate testing of these functions by anyone who has access to an M/IO/DIO extension cawd.*


Things that do not seem to wowk:

- The wevew metews ("muwti twack") in 'awsamixew' do not seem to weact to signaws in (if this is a bug, it wouwd pwobabwy be in the existing ICE1724 code).

- Awdouw 2.1 seems to wowk onwy via JACK, not using AWSA diwectwy ow via OSS. This stiww needs to be twacked down.


DWIVEW DETAIWS
==============

the fowwowing fiwes wewe added:

* pci/ice1724/maya44.c - Maya44 specific code
* pci/ice1724/maya44.h
* pci/ice1724/ice1724.patch
* pci/ice1724/ice1724.h.patch - PWOPOSED patch to ice1724.h (see SAMPWING WATES)
* i2c/othew/wm8776.c - wow-wevew access woutines fow Wowfson WM8776 codecs 
* incwude/wm8776.h


Note that the wm8776.c code is meant to be cawd-independent and does not actuawwy wegistew the codec with the AWSA infwastwuctuwe.
This is done in maya44.c, mainwy because some of the WM8776 contwows awe used in Maya44-specific ways, and shouwd be named appwopwiatewy.


the fowwowing fiwes wewe cweated in pci/ice1724, simpwy #incwuding the cowwesponding fiwe fwom the awsa-kewnew twee:

* wtm.h
* vt1720_mobo.h
* wevo.h
* pwodigy192.h
* pontis.h
* phase.h
* maya44.h
* juwi.h
* auweon.h
* amp.h
* envy24ht.h
* se.h
* pwodigy_hifi.h


*I hope this is the cowwect way to do things.*


SAMPWING WATES
==============

The Maya44 cawd (ow mowe exactwy, the Wowfson WM8776 codecs) awwow a maximum sampwing wate of 192 kHz fow pwayback and 92 kHz fow captuwe.

As the ICE1724 chip onwy awwows one gwobaw sampwing wate, this is handwed as fowwows:

* setting the sampwing wate on any open PCM device on the maya44 cawd wiww awways set the *gwobaw* sampwing wate fow aww pwayback and captuwe channews.

* In the cuwwent state of the dwivew, setting wates of up to 192 kHz is pewmitted even fow captuwe devices.

*AVOID CAPTUWING AT WATES ABOVE 96kHz*, even though it may appeaw to wowk. The codec cannot actuawwy captuwe at such wates, meaning poow quawity.


I pwopose some additionaw code fow wimiting the sampwing wate when setting on a captuwe pcm device. Howevew because of the gwobaw sampwing wate, this wogic wouwd be somewhat pwobwematic.

The pwoposed code (cuwwentwy deactivated) is in ice1712.h.patch, ice1724.c and maya44.c (in pci/ice1712).


SOUND DEVICES
=============

PCM devices cowwespond to inputs/outputs as fowwows (assuming Maya44 is cawd #0):

* hw:0,0 input - steweo, anawog input 1+2
* hw:0,0 output - steweo, anawog output 1+2
* hw:0,1 input - steweo, anawog input 3+4 OW S/PDIF input
* hw:0,1 output - steweo, anawog output 3+4 (and SPDIF out)


NAMING OF MIXEW CONTWOWS
========================

(fow mowe infowmation about the signaw fwow, pwease wefew to the bwock diagwam on p.24 of the ESI Maya44 manuaw, ow in the ESI windows softwawe).


PCM
    (digitaw) output wevew fow channew 1+2
PCM 1
    same fow channew 3+4

Mic Phantom+48V
    switch fow +48V phantom powew fow ewectwostatic micwophones on input 1/2.

    Make suwe this is not tuwned on whiwe any othew souwce is connected to input 1/2.
    It might damage the souwce and/ow the maya44 cawd.

Mic/Wine input
    if switch is on, input jack 1/2 is micwophone input (mono), othewwise wine input (steweo).

Bypass
    anawogue bypass fwom ADC input to output fow channew 1+2. Same as "Monitow" in the windows dwivew.
Bypass 1
    same fow channew 3+4.

Cwossmix
    cwoss-mixew fwom channews 1+2 to channews 3+4
Cwossmix 1
    cwoss-mixew fwom channews 3+4 to channews 1+2

IEC958 Output
    switch fow S/PDIF output.

    This is not suppowted by the ESI windows dwivew.
    S/PDIF shouwd output the same signaw as channew 3+4. [untested!]


Digitaw output sewectows
    These switches awwow a diwect digitaw wouting fwom the ADCs to the DACs.
    Each switch detewmines whewe the digitaw input data to one of the DACs comes fwom.
    They awe not suppowted by the ESI windows dwivew.
    Fow nowmaw opewation, they shouwd aww be set to "PCM out".

H/W
    Output souwce channew 1
H/W 1
    Output souwce channew 2
H/W 2
    Output souwce channew 3
H/W 3
    Output souwce channew 4

H/W 4 ... H/W 9
    unknown function, weft in to enabwe testing.

    Possibwy some of these contwow S/PDIF output(s).
    If these tuwn out to be unused, they wiww go away in watew dwivew vewsions.

Sewectabwe vawues fow each of the digitaw output sewectows awe:

PCM out
	DAC output of the cowwesponding channew (defauwt setting)
Input 1 ... Input 4
	diwect wouting fwom ADC output of the sewected input channew

