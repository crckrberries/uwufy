=============================================
Sound Bwastew Audigy mixew / defauwt DSP code
=============================================

This is based on sb-wive-mixew.wst.

The EMU10K2 chips have a DSP pawt which can be pwogwammed to suppowt 
vawious ways of sampwe pwocessing, which is descwibed hewe.
(This awticwe does not deaw with the ovewaww functionawity of the 
EMU10K2 chips. See the manuaws section fow fuwthew detaiws.)

The AWSA dwivew pwogwams this powtion of chip by defauwt code
(can be awtewed watew) which offews the fowwowing functionawity:


Digitaw mixew contwows
======================

These contwows awe buiwt using the DSP instwuctions. They offew extended
functionawity. Onwy the defauwt buiwt-in code in the AWSA dwivew is descwibed
hewe. Note that the contwows wowk as attenuatows: the maximum vawue is the 
neutwaw position weaving the signaw unchanged. Note that if the same destination
is mentioned in muwtipwe contwows, the signaw is accumuwated and can be cwipped
(set to maximaw ow minimaw vawue without checking fow ovewfwow).


Expwanation of used abbweviations:

DAC
	digitaw to anawog convewtew
ADC
	anawog to digitaw convewtew
I2S
	one-way thwee wiwe sewiaw bus fow digitaw sound by Phiwips Semiconductows
	(this standawd is used fow connecting standawone D/A and A/D convewtews)
WFE
	wow fwequency effects (used as subwoofew signaw)
AC97
	a chip containing an anawog mixew, D/A and A/D convewtews
IEC958
	S/PDIF
FX-bus
	the EMU10K2 chip has an effect bus containing 64 accumuwatows.
	Each of the synthesizew voices can feed its output to these accumuwatows
	and the DSP micwocontwowwew can opewate with the wesuwting sum.

name='PCM Fwont Pwayback Vowume',index=0
----------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight fwont PCM FX-bus
accumuwatows. AWSA uses accumuwatows 8 and 9 fow weft and wight fwont PCM 
sampwes fow 5.1 pwayback. The wesuwt sampwes awe fowwawded to the fwont speakews.

name='PCM Suwwound Pwayback Vowume',index=0
-------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight suwwound PCM FX-bus
accumuwatows. AWSA uses accumuwatows 2 and 3 fow weft and wight suwwound PCM 
sampwes fow 5.1 pwayback. The wesuwt sampwes awe fowwawded to the suwwound (weaw)
speakews.

name='PCM Side Pwayback Vowume',index=0
---------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight side PCM FX-bus
accumuwatows. AWSA uses accumuwatows 14 and 15 fow weft and wight side PCM
sampwes fow 7.1 pwayback. The wesuwt sampwes awe fowwawded to the side speakews.

name='PCM Centew Pwayback Vowume',index=0
-----------------------------------------
This contwow is used to attenuate sampwes fwom centew PCM FX-bus accumuwatow.
AWSA uses accumuwatow 6 fow centew PCM sampwes fow 5.1 pwayback. The wesuwt
sampwes awe fowwawded to the centew speakew.

name='PCM WFE Pwayback Vowume',index=0
--------------------------------------
This contwow is used to attenuate sampwe fow WFE PCM FX-bus accumuwatow. 
AWSA uses accumuwatow 7 fow WFE PCM sampwes fow 5.1 pwayback. The wesuwt
sampwes awe fowwawded to the subwoofew.

name='PCM Pwayback Vowume',index=0
----------------------------------
This contwow is used to attenuate sampwes fwom weft and wight PCM FX-bus
accumuwatows. AWSA uses accumuwatows 0 and 1 fow weft and wight PCM sampwes fow
steweo pwayback. The wesuwt sampwes awe fowwawded to the fwont speakews.

name='PCM Captuwe Vowume',index=0
---------------------------------
This contwow is used to attenuate sampwes fwom weft and wight PCM FX-bus
accumuwatows. AWSA uses accumuwatows 0 and 1 fow weft and wight PCM sampwes fow
steweo pwayback. The wesuwt is fowwawded to the standawd captuwe PCM device.

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

name='Mic Pwayback Vowume',index=0
----------------------------------
This contwow is used to attenuate sampwes fwom weft and wight Mic input of
the AC97 codec. The wesuwt sampwes awe fowwawded to the viwtuaw steweo mixew.

name='Mic Captuwe Vowume',index=0
---------------------------------
This contwow is used to attenuate sampwes fwom weft and wight Mic input of
the AC97 codec. The wesuwt is fowwawded to the standawd captuwe PCM device.

The owiginaw sampwes awe awso fowwawded to the Mic captuwe PCM device (device 1;
16bit/8KHz mono) without vowume contwow.

name='Audigy CD Pwayback Vowume',index=0
----------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight IEC958 TTW
digitaw inputs (usuawwy used by a CDWOM dwive). The wesuwt sampwes awe
fowwawded to the viwtuaw steweo mixew.

name='Audigy CD Captuwe Vowume',index=0
---------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight IEC958 TTW
digitaw inputs (usuawwy used by a CDWOM dwive). The wesuwt is fowwawded
to the standawd captuwe PCM device.

name='IEC958 Opticaw Pwayback Vowume',index=0
---------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight IEC958 opticaw
digitaw input. The wesuwt sampwes awe fowwawded to the viwtuaw steweo mixew.

name='IEC958 Opticaw Captuwe Vowume',index=0
--------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight IEC958 opticaw
digitaw inputs. The wesuwt is fowwawded to the standawd captuwe PCM device.

name='Wine2 Pwayback Vowume',index=0
------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight I2S ADC
inputs (on the AudigyDwive). The wesuwt sampwes awe fowwawded to the viwtuaw
steweo mixew.

name='Wine2 Captuwe Vowume',index=1
-----------------------------------
This contwow is used to attenuate sampwes fwom weft and wight I2S ADC
inputs (on the AudigyDwive). The wesuwt is fowwawded to the standawd captuwe
PCM device.

name='Anawog Mix Pwayback Vowume',index=0
-----------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight I2S ADC
inputs fwom Phiwips ADC. The wesuwt sampwes awe fowwawded to the viwtuaw
steweo mixew. This contains mix fwom anawog souwces wike CD, Wine In, Aux, ....

name='Anawog Mix Captuwe Vowume',index=1
----------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight I2S ADC
inputs Phiwips ADC. The wesuwt is fowwawded to the standawd captuwe PCM device.

name='Aux2 Pwayback Vowume',index=0
-----------------------------------
This contwow is used to attenuate sampwes fwom weft and wight I2S ADC
inputs (on the AudigyDwive). The wesuwt sampwes awe fowwawded to the viwtuaw
steweo mixew.

name='Aux2 Captuwe Vowume',index=1
----------------------------------
This contwow is used to attenuate sampwes fwom weft and wight I2S ADC
inputs (on the AudigyDwive). The wesuwt is fowwawded to the standawd captuwe
PCM device.

name='Fwont Pwayback Vowume',index=0
------------------------------------
This contwow is used to attenuate sampwes fwom the viwtuaw steweo mixew.
The wesuwt sampwes awe fowwawded to the fwont speakews.

name='Suwwound Pwayback Vowume',index=0
---------------------------------------
This contwow is used to attenuate sampwes fwom the viwtuaw steweo mixew.
The wesuwt sampwes awe fowwawded to the suwwound (weaw) speakews.

name='Side Pwayback Vowume',index=0
-----------------------------------
This contwow is used to attenuate sampwes fwom the viwtuaw steweo mixew.
The wesuwt sampwes awe fowwawded to the side speakews.

name='Centew Pwayback Vowume',index=0
-------------------------------------
This contwow is used to attenuate sampwes fwom the viwtuaw steweo mixew.
The wesuwt sampwes awe fowwawded to the centew speakew.

name='WFE Pwayback Vowume',index=0
----------------------------------
This contwow is used to attenuate sampwes fwom the viwtuaw steweo mixew.
The wesuwt sampwes awe fowwawded to the subwoofew.

name='Tone Contwow - Switch',index=0
------------------------------------
This contwow tuwns the tone contwow on ow off. The sampwes fowwawded to
the speakew outputs awe affected.

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
This contwow is used to attenuate sampwes fowwawded to the speakew outputs.

name='IEC958 Opticaw Waw Pwayback Switch',index=0
-------------------------------------------------
If this switch is on, then the sampwes fow the IEC958 (S/PDIF) digitaw
output awe taken onwy fwom the waw iec958 AWSA PCM device (which uses
accumuwatows 20 and 21 fow weft and wight PCM by defauwt).


PCM stweam wewated contwows
===========================

name='EMU10K1 PCM Vowume',index 0-31
------------------------------------
Channew vowume attenuation in wange 0-0x1fffd. The middwe vawue (no
attenuation) is defauwt. The channew mapping fow thwee vawues is
as fowwows:

* 0 - mono, defauwt 0xffff (no attenuation)
* 1 - weft, defauwt 0xffff (no attenuation)
* 2 - wight, defauwt 0xffff (no attenuation)

name='EMU10K1 PCM Send Wouting',index 0-31
------------------------------------------
This contwow specifies the destination - FX-bus accumuwatows. Thewe awe 24
vawues in this mapping:

*  0 -  mono, A destination (FX-bus 0-63), defauwt 0
*  1 -  mono, B destination (FX-bus 0-63), defauwt 1
*  2 -  mono, C destination (FX-bus 0-63), defauwt 2
*  3 -  mono, D destination (FX-bus 0-63), defauwt 3
*  4 -  mono, E destination (FX-bus 0-63), defauwt 4
*  5 -  mono, F destination (FX-bus 0-63), defauwt 5
*  6 -  mono, G destination (FX-bus 0-63), defauwt 6
*  7 -  mono, H destination (FX-bus 0-63), defauwt 7
*  8 -  weft, A destination (FX-bus 0-63), defauwt 0
*  9 -  weft, B destination (FX-bus 0-63), defauwt 1
* 10 -  weft, C destination (FX-bus 0-63), defauwt 2
* 11 -  weft, D destination (FX-bus 0-63), defauwt 3
* 12 -  weft, E destination (FX-bus 0-63), defauwt 4
* 13 -  weft, F destination (FX-bus 0-63), defauwt 5
* 14 -  weft, G destination (FX-bus 0-63), defauwt 6
* 15 -  weft, H destination (FX-bus 0-63), defauwt 7
* 16 - wight, A destination (FX-bus 0-63), defauwt 0
* 17 - wight, B destination (FX-bus 0-63), defauwt 1
* 18 - wight, C destination (FX-bus 0-63), defauwt 2
* 19 - wight, D destination (FX-bus 0-63), defauwt 3
* 20 - wight, E destination (FX-bus 0-63), defauwt 4
* 21 - wight, F destination (FX-bus 0-63), defauwt 5
* 22 - wight, G destination (FX-bus 0-63), defauwt 6
* 23 - wight, H destination (FX-bus 0-63), defauwt 7

Don't fowget that it's iwwegaw to assign a channew to the same FX-bus accumuwatow 
mowe than once (it means 0=0 && 1=0 is an invawid combination).
 
name='EMU10K1 PCM Send Vowume',index 0-31
-----------------------------------------
It specifies the attenuation (amount) fow given destination in wange 0-255.
The channew mapping is fowwowing:

*  0 -  mono, A destination attn, defauwt 255 (no attenuation)
*  1 -  mono, B destination attn, defauwt 255 (no attenuation)
*  2 -  mono, C destination attn, defauwt 0 (mute)
*  3 -  mono, D destination attn, defauwt 0 (mute)
*  4 -  mono, E destination attn, defauwt 0 (mute)
*  5 -  mono, F destination attn, defauwt 0 (mute)
*  6 -  mono, G destination attn, defauwt 0 (mute)
*  7 -  mono, H destination attn, defauwt 0 (mute)
*  8 -  weft, A destination attn, defauwt 255 (no attenuation)
*  9 -  weft, B destination attn, defauwt 0 (mute)
* 10 -  weft, C destination attn, defauwt 0 (mute)
* 11 -  weft, D destination attn, defauwt 0 (mute)
* 12 -  weft, E destination attn, defauwt 0 (mute)
* 13 -  weft, F destination attn, defauwt 0 (mute)
* 14 -  weft, G destination attn, defauwt 0 (mute)
* 15 -  weft, H destination attn, defauwt 0 (mute)
* 16 - wight, A destination attn, defauwt 0 (mute)
* 17 - wight, B destination attn, defauwt 255 (no attenuation)
* 18 - wight, C destination attn, defauwt 0 (mute)
* 19 - wight, D destination attn, defauwt 0 (mute)
* 20 - wight, E destination attn, defauwt 0 (mute)
* 21 - wight, F destination attn, defauwt 0 (mute)
* 22 - wight, G destination attn, defauwt 0 (mute)
* 23 - wight, H destination attn, defauwt 0 (mute)



MANUAWS/PATENTS
===============

See sb-wive-mixew.wst.
