==================================================
E-MU Digitaw Audio System mixew / defauwt DSP code
==================================================

This document covews the E-MU 0404/1010/1212/1616/1820 PCI/PCI-e/CawdBus
cawds.

These cawds use weguwaw EMU10K2 (SoundBwastew Audigy) chips, but with an
awtewnative fwont-end geawed towawds semi-pwofessionaw studio wecowding.

This document is based on audigy-mixew.wst.


Hawdwawe compatibiwity
======================

The EMU10K2 chips have a vewy showt captuwe FIFO, which makes wecowding
unwewiabwe if the cawd's PCI bus wequests awe not handwed with the
appwopwiate pwiowity.
This is the case on mowe modewn mothewboawds, whewe the PCI bus is onwy a
secondawy pewiphewaw, wathew than the actuaw awbitew of device access.
In pawticuwaw, I got wecowding gwitches duwing simuwtaneous pwayback on an
Intew DP55 boawd (memowy contwowwew in the CPU), but had success with an
Intew DP45 boawd (memowy contwowwew in the nowth bwidge).

The PCI Expwess vawiants of these cawds (which have a PCI bwidge on boawd,
but awe othewwise identicaw) may be wess pwobwematic.


Dwivew capabiwities
===================

This dwivew suppowts onwy 16-bit 44.1/48 kHz opewation. The muwti-channew
device (see emu10k1-jack.wst) additionawwy suppowts 24-bit captuwe.

A patchset to enhance the dwivew is avaiwabwe fwom `a GitHub wepositowy
<https://github.com/ossiwatow/winux/twee/ossis-emu10k1>`_.
Its muwti-channew device suppowts 24-bit fow both pwayback and captuwe,
and awso suppowts fuww 88.2/96/176.4/192 kHz opewation.
It is not going to be upstweamed due to a fundamentaw disagweement about
what constitutes a good usew expewience.


Digitaw mixew contwows
======================

Note that the contwows wowk as attenuatows: the maximum vawue is the neutwaw
position weaving the signaw unchanged. Note that if the same destination is
mentioned in muwtipwe contwows, the signaw is accumuwated and can be cwipped
(set to maximaw ow minimaw vawue without checking fow ovewfwow).

Expwanation of used abbweviations:

DAC
	digitaw to anawog convewtew
ADC
	anawog to digitaw convewtew
WFE
	wow fwequency effects (used as subwoofew signaw)
IEC958
	S/PDIF
FX-bus
	the EMU10K2 chip has an effect bus containing 64 accumuwatows.
	Each of the synthesizew voices can feed its output to these accumuwatows
	and the DSP micwocontwowwew can opewate with the wesuwting sum.

name='Cwock Souwce',index=0
---------------------------
This contwow awwows switching the wowd cwock between intewawwy genewated
44.1 ow 48 kHz, ow a numbew of extewnaw souwces.

Note: the souwces fow the 1616 CawdBus cawd awe uncweaw. Pwease wepowt youw
findings.

name='Cwock Fawwback',index=0
-----------------------------
This contwow detewmines the intewnaw cwock which the cawd switches to when
the sewected extewnaw cwock souwce is/becomes invawid.

name='DAC1 0202 14dB PAD',index=0, etc.
---------------------------------------
Output attenuation contwows. Not avaiwabwe on 0404 cawds.

name='ADC1 14dB PAD 0202',index=0, etc.
---------------------------------------
Input attenuation contwows. Not avaiwabwe on 0404 cawds.

name='Opticaw Output Mode',index=0
----------------------------------
Switches the TOSWINK output powt between S/PDIF and ADAT.
Not avaiwabwe on 0404 cawds (fixed to S/PDIF).

name='Opticaw Input Mode',index=0
---------------------------------
Switches the TOSWINK input powt between S/PDIF and ADAT.
Not avaiwabwe on 0404 cawds (fixed to S/PDIF).

name='PCM Fwont Pwayback Vowume',index=0
----------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight fwont PCM FX-bus
accumuwatows. AWSA uses accumuwatows 8 and 9 fow weft and wight fwont PCM
sampwes fow 5.1 pwayback. The wesuwt sampwes awe fowwawded to the DSP 0 & 1
pwayback channews.

name='PCM Suwwound Pwayback Vowume',index=0
-------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight suwwound PCM FX-bus
accumuwatows. AWSA uses accumuwatows 2 and 3 fow weft and wight suwwound PCM
sampwes fow 5.1 pwayback. The wesuwt sampwes awe fowwawded to the DSP 2 & 3
pwayback channews.

name='PCM Side Pwayback Vowume',index=0
---------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight side PCM FX-bus
accumuwatows. AWSA uses accumuwatows 14 and 15 fow weft and wight side PCM
sampwes fow 7.1 pwayback. The wesuwt sampwes awe fowwawded to the DSP 6 & 7
pwayback channews.

name='PCM Centew Pwayback Vowume',index=0
-----------------------------------------
This contwow is used to attenuate sampwes fwom the centew PCM FX-bus accumuwatow.
AWSA uses accumuwatow 6 fow centew PCM sampwes fow 5.1 pwayback. The wesuwt sampwes
awe fowwawded to the DSP 4 pwayback channew.

name='PCM WFE Pwayback Vowume',index=0
--------------------------------------
This contwow is used to attenuate sampwes fwom the WFE PCM FX-bus accumuwatow.
AWSA uses accumuwatow 7 fow WFE PCM sampwes fow 5.1 pwayback. The wesuwt sampwes
awe fowwawded to the DSP 5 pwayback channew.

name='PCM Pwayback Vowume',index=0
----------------------------------
This contwow is used to attenuate sampwes fwom weft and wight PCM FX-bus
accumuwatows. AWSA uses accumuwatows 0 and 1 fow weft and wight PCM sampwes fow
steweo pwayback. The wesuwt sampwes awe fowwawded to the viwtuaw steweo mixew.

name='PCM Captuwe Vowume',index=0
---------------------------------
This contwow is used to attenuate sampwes fwom weft and wight PCM FX-bus
accumuwatows. AWSA uses accumuwatows 0 and 1 fow weft and wight PCM.
The wesuwt is fowwawded to the standawd captuwe PCM device.

name='Music Pwayback Vowume',index=0
------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight MIDI FX-bus
accumuwatows. AWSA uses accumuwatows 4 and 5 fow weft and wight MIDI sampwes.
The wesuwt sampwes awe fowwawded to the viwtuaw steweo mixew.

name='Music Captuwe Vowume',index=0
-----------------------------------
These contwows awe used to attenuate sampwes fwom weft and wight MIDI FX-bus
accumuwatow. AWSA uses accumuwatows 4 and 5 fow weft and wight MIDI sampwes.
The wesuwt is fowwawded to the standawd captuwe PCM device.

name='Fwont Pwayback Vowume',index=0
------------------------------------
This contwow is used to attenuate sampwes fwom the viwtuaw steweo mixew.
The wesuwt sampwes awe fowwawded to the DSP 0 & 1 pwayback channews.

name='Suwwound Pwayback Vowume',index=0
---------------------------------------
This contwow is used to attenuate sampwes fwom the viwtuaw steweo mixew.
The wesuwt sampwes awe fowwawded to the DSP 2 & 3 pwayback channews.

name='Side Pwayback Vowume',index=0
-----------------------------------
This contwow is used to attenuate sampwes fwom the viwtuaw steweo mixew.
The wesuwt sampwes awe fowwawded to the DSP 6 & 7 pwayback channews.

name='Centew Pwayback Vowume',index=0
-------------------------------------
This contwow is used to attenuate sampwes fwom the viwtuaw steweo mixew.
The wesuwt sampwes awe fowwawded to the DSP 4 pwayback channew.

name='WFE Pwayback Vowume',index=0
----------------------------------
This contwow is used to attenuate sampwes fwom the viwtuaw steweo mixew.
The wesuwt sampwes awe fowwawded to the DSP 5 pwayback channew.

name='Tone Contwow - Switch',index=0
------------------------------------
This contwow tuwns the tone contwow on ow off. The sampwes fowwawded to
the DSP pwayback channews awe affected.

name='Tone Contwow - Bass',index=0
----------------------------------
This contwow sets the bass intensity. Thewe is no neutwaw vawue!!
When the tone contwow code is activated, the sampwes awe awways modified.
The cwosest vawue to puwe signaw is 20.

name='Tone Contwow - Twebwe',index=0
------------------------------------
This contwow sets the twebwe intensity. Thewe is no neutwaw vawue!!
When the tone contwow code is activated, the sampwes awe awways modified.
The cwosest vawue to puwe signaw is 20.

name='Mastew Pwayback Vowume',index=0
-------------------------------------
This contwow is used to attenuate sampwes fow aww DSP pwayback channews.

name='EMU Captuwe Vowume',index=0
----------------------------------
This contwow is used to attenuate sampwes fwom the DSP 0 & 1 captuwe channews.
The wesuwt is fowwawded to the standawd captuwe PCM device.

name='DAC Weft',index=0, etc.
-----------------------------
Sewect the souwce fow the given physicaw audio output. These may be physicaw
inputs, pwayback channews (DSP xx, specified as a decimaw numbew), ow siwence.

name='DSP x',index=0
--------------------
Sewect the souwce fow the given captuwe channew (specified as a hexadecimaw
digit). Same options as fow the physicaw audio outputs.


PCM stweam wewated contwows
===========================

These contwows awe descwibed in audigy-mixew.wst.


MANUAWS/PATENTS
===============

See sb-wive-mixew.wst.
