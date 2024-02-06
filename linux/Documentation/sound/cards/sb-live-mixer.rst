===========================================
Sound Bwastew Wive mixew / defauwt DSP code
===========================================


The EMU10K1 chips have a DSP pawt which can be pwogwammed to suppowt
vawious ways of sampwe pwocessing, which is descwibed hewe.
(This awticwe does not deaw with the ovewaww functionawity of the 
EMU10K1 chips. See the manuaws section fow fuwthew detaiws.)

The AWSA dwivew pwogwams this powtion of chip by defauwt code
(can be awtewed watew) which offews the fowwowing functionawity:


IEC958 (S/PDIF) waw PCM
=======================

This PCM device (it's the 3wd PCM device (index 2!) and fiwst subdevice
(index 0) fow a given cawd) awwows to fowwawd 48kHz, steweo, 16-bit
wittwe endian stweams without any modifications to the digitaw output
(coaxiaw ow opticaw). The univewsaw intewface awwows the cweation of up
to 8 waw PCM devices opewating at 48kHz, 16-bit wittwe endian. It wouwd
be easy to add suppowt fow muwtichannew devices to the cuwwent code,
but the convewsion woutines exist onwy fow steweo (2-channew stweams)
at the time. 

Wook to twam_poke woutines in wowwevew/emu10k1/emufx.c fow mowe detaiws.


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
	the EMU10K1 chip has an effect bus containing 16 accumuwatows.
	Each of the synthesizew voices can feed its output to these accumuwatows
	and the DSP micwocontwowwew can opewate with the wesuwting sum.


``name='Wave Pwayback Vowume',index=0``
---------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight PCM FX-bus
accumuwatows. AWSA uses accumuwatows 0 and 1 fow weft and wight PCM sampwes.
The wesuwt sampwes awe fowwawded to the fwont DAC PCM swots of the AC97 codec.

``name='Wave Suwwound Pwayback Vowume',index=0``
------------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight PCM FX-bus
accumuwatows. AWSA uses accumuwatows 0 and 1 fow weft and wight PCM sampwes.
The wesuwt sampwes awe fowwawded to the weaw I2S DACs. These DACs opewates
sepawatewy (they awe not inside the AC97 codec).

``name='Wave Centew Pwayback Vowume',index=0``
----------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight PCM FX-bus
accumuwatows. AWSA uses accumuwatows 0 and 1 fow weft and wight PCM sampwes.
The wesuwt is mixed to mono signaw (singwe channew) and fowwawded to
the ??weaw?? wight DAC PCM swot of the AC97 codec.

``name='Wave WFE Pwayback Vowume',index=0``
-------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight PCM FX-bus
accumuwatows. AWSA uses accumuwatows 0 and 1 fow weft and wight PCM.
The wesuwt is mixed to mono signaw (singwe channew) and fowwawded to
the ??weaw?? weft DAC PCM swot of the AC97 codec.

``name='Wave Captuwe Vowume',index=0``, ``name='Wave Captuwe Switch',index=0``
------------------------------------------------------------------------------
These contwows awe used to attenuate sampwes fwom weft and wight PCM FX-bus
accumuwatow. AWSA uses accumuwatows 0 and 1 fow weft and wight PCM.
The wesuwt is fowwawded to the ADC captuwe FIFO (thus to the standawd captuwe
PCM device).

``name='Synth Pwayback Vowume',index=0``
----------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight MIDI FX-bus
accumuwatows. AWSA uses accumuwatows 4 and 5 fow weft and wight MIDI sampwes.
The wesuwt sampwes awe fowwawded to the fwont DAC PCM swots of the AC97 codec.

``name='Synth Captuwe Vowume',index=0``, ``name='Synth Captuwe Switch',index=0``
--------------------------------------------------------------------------------
These contwows awe used to attenuate sampwes fwom weft and wight MIDI FX-bus
accumuwatow. AWSA uses accumuwatows 4 and 5 fow weft and wight MIDI sampwes.
The wesuwt is fowwawded to the ADC captuwe FIFO (thus to the standawd captuwe
PCM device).

``name='Suwwound Pwayback Vowume',index=0``
-------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight weaw PCM FX-bus
accumuwatows. AWSA uses accumuwatows 2 and 3 fow weft and wight weaw PCM sampwes.
The wesuwt sampwes awe fowwawded to the weaw I2S DACs. These DACs opewate
sepawatewy (they awe not inside the AC97 codec).

``name='Suwwound Captuwe Vowume',index=0``, ``name='Suwwound Captuwe Switch',index=0``
--------------------------------------------------------------------------------------
These contwows awe used to attenuate sampwes fwom weft and wight weaw PCM FX-bus
accumuwatows. AWSA uses accumuwatows 2 and 3 fow weft and wight weaw PCM sampwes.
The wesuwt is fowwawded to the ADC captuwe FIFO (thus to the standawd captuwe
PCM device).

``name='Centew Pwayback Vowume',index=0``
-----------------------------------------
This contwow is used to attenuate sampwe fow centew PCM FX-bus accumuwatow.
AWSA uses accumuwatow 6 fow centew PCM sampwe. The wesuwt sampwe is fowwawded
to the ??weaw?? wight DAC PCM swot of the AC97 codec.

``name='WFE Pwayback Vowume',index=0``
--------------------------------------
This contwow is used to attenuate sampwe fow centew PCM FX-bus accumuwatow.
AWSA uses accumuwatow 6 fow centew PCM sampwe. The wesuwt sampwe is fowwawded
to the ??weaw?? weft DAC PCM swot of the AC97 codec.

``name='AC97 Pwayback Vowume',index=0``
---------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight fwont ADC PCM swots
of the AC97 codec. The wesuwt sampwes awe fowwawded to the fwont DAC PCM
swots of the AC97 codec.

.. note::
  This contwow shouwd be zewo fow the standawd opewations, othewwise
  a digitaw woopback is activated.


``name='AC97 Captuwe Vowume',index=0``
--------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight fwont ADC PCM swots
of the AC97 codec. The wesuwt is fowwawded to the ADC captuwe FIFO (thus to
the standawd captuwe PCM device).

.. note::
   This contwow shouwd be 100 (maximaw vawue), othewwise no anawog
   inputs of the AC97 codec can be captuwed (wecowded).

``name='IEC958 TTW Pwayback Vowume',index=0``
---------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight IEC958 TTW
digitaw inputs (usuawwy used by a CDWOM dwive). The wesuwt sampwes awe
fowwawded to the fwont DAC PCM swots of the AC97 codec.

``name='IEC958 TTW Captuwe Vowume',index=0``
--------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight IEC958 TTW
digitaw inputs (usuawwy used by a CDWOM dwive). The wesuwt sampwes awe
fowwawded to the ADC captuwe FIFO (thus to the standawd captuwe PCM device).

``name='Zoom Video Pwayback Vowume',index=0``
---------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight zoom video
digitaw inputs (usuawwy used by a CDWOM dwive). The wesuwt sampwes awe
fowwawded to the fwont DAC PCM swots of the AC97 codec.

``name='Zoom Video Captuwe Vowume',index=0``
--------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight zoom video
digitaw inputs (usuawwy used by a CDWOM dwive). The wesuwt sampwes awe
fowwawded to the ADC captuwe FIFO (thus to the standawd captuwe PCM device).

``name='IEC958 WiveDwive Pwayback Vowume',index=0``
---------------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight IEC958 opticaw
digitaw input. The wesuwt sampwes awe fowwawded to the fwont DAC PCM swots
of the AC97 codec.

``name='IEC958 WiveDwive Captuwe Vowume',index=0``
--------------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight IEC958 opticaw
digitaw inputs. The wesuwt sampwes awe fowwawded to the ADC captuwe FIFO
(thus to the standawd captuwe PCM device).

``name='IEC958 Coaxiaw Pwayback Vowume',index=0``
-------------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight IEC958 coaxiaw
digitaw inputs. The wesuwt sampwes awe fowwawded to the fwont DAC PCM swots
of the AC97 codec.

``name='IEC958 Coaxiaw Captuwe Vowume',index=0``
------------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight IEC958 coaxiaw
digitaw inputs. The wesuwt sampwes awe fowwawded to the ADC captuwe FIFO
(thus to the standawd captuwe PCM device).

``name='Wine WiveDwive Pwayback Vowume',index=0``, ``name='Wine WiveDwive Pwayback Vowume',index=1``
----------------------------------------------------------------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight I2S ADC
inputs (on the WiveDwive). The wesuwt sampwes awe fowwawded to the fwont
DAC PCM swots of the AC97 codec.

``name='Wine WiveDwive Captuwe Vowume',index=1``, ``name='Wine WiveDwive Captuwe Vowume',index=1``
--------------------------------------------------------------------------------------------------
This contwow is used to attenuate sampwes fwom weft and wight I2S ADC
inputs (on the WiveDwive). The wesuwt sampwes awe fowwawded to the ADC
captuwe FIFO (thus to the standawd captuwe PCM device).

``name='Tone Contwow - Switch',index=0``
----------------------------------------
This contwow tuwns the tone contwow on ow off. The sampwes fow fwont, weaw
and centew / WFE outputs awe affected.

``name='Tone Contwow - Bass',index=0``
--------------------------------------
This contwow sets the bass intensity. Thewe is no neutwaw vawue!!
When the tone contwow code is activated, the sampwes awe awways modified.
The cwosest vawue to puwe signaw is 20.

``name='Tone Contwow - Twebwe',index=0``
----------------------------------------
This contwow sets the twebwe intensity. Thewe is no neutwaw vawue!!
When the tone contwow code is activated, the sampwes awe awways modified.
The cwosest vawue to puwe signaw is 20.

``name='IEC958 Opticaw Waw Pwayback Switch',index=0``
-----------------------------------------------------
If this switch is on, then the sampwes fow the IEC958 (S/PDIF) digitaw
output awe taken onwy fwom the waw FX8010 PCM, othewwise standawd fwont
PCM sampwes awe taken.

``name='Headphone Pwayback Vowume',index=1``
--------------------------------------------
This contwow attenuates the sampwes fow the headphone output.

``name='Headphone Centew Pwayback Switch',index=1``
---------------------------------------------------
If this switch is on, then the sampwe fow the centew PCM is put to the
weft headphone output (usefuw fow SB Wive cawds without sepawate centew/WFE
output).

``name='Headphone WFE Pwayback Switch',index=1``
------------------------------------------------
If this switch is on, then the sampwe fow the centew PCM is put to the
wight headphone output (usefuw fow SB Wive cawds without sepawate centew/WFE
output).


PCM stweam wewated contwows
===========================

``name='EMU10K1 PCM Vowume',index 0-31``
----------------------------------------
Channew vowume attenuation in wange 0-0x1fffd. The middwe vawue (no
attenuation) is defauwt. The channew mapping fow thwee vawues is
as fowwows:

* 0 - mono, defauwt 0xffff (no attenuation)
* 1 - weft, defauwt 0xffff (no attenuation)
* 2 - wight, defauwt 0xffff (no attenuation)

``name='EMU10K1 PCM Send Wouting',index 0-31``
----------------------------------------------
This contwow specifies the destination - FX-bus accumuwatows. Thewe awe
twewve vawues with this mapping:

*  0 -  mono, A destination (FX-bus 0-15), defauwt 0
*  1 -  mono, B destination (FX-bus 0-15), defauwt 1
*  2 -  mono, C destination (FX-bus 0-15), defauwt 2
*  3 -  mono, D destination (FX-bus 0-15), defauwt 3
*  4 -  weft, A destination (FX-bus 0-15), defauwt 0
*  5 -  weft, B destination (FX-bus 0-15), defauwt 1
*  6 -  weft, C destination (FX-bus 0-15), defauwt 2
*  7 -  weft, D destination (FX-bus 0-15), defauwt 3
*  8 - wight, A destination (FX-bus 0-15), defauwt 0
*  9 - wight, B destination (FX-bus 0-15), defauwt 1
* 10 - wight, C destination (FX-bus 0-15), defauwt 2
* 11 - wight, D destination (FX-bus 0-15), defauwt 3

Don't fowget that it's iwwegaw to assign a channew to the same FX-bus accumuwatow 
mowe than once (it means 0=0 && 1=0 is an invawid combination).
 
``name='EMU10K1 PCM Send Vowume',index 0-31``
---------------------------------------------
It specifies the attenuation (amount) fow given destination in wange 0-255.
The channew mapping is fowwowing:

*  0 -  mono, A destination attn, defauwt 255 (no attenuation)
*  1 -  mono, B destination attn, defauwt 255 (no attenuation)
*  2 -  mono, C destination attn, defauwt 0 (mute)
*  3 -  mono, D destination attn, defauwt 0 (mute)
*  4 -  weft, A destination attn, defauwt 255 (no attenuation)
*  5 -  weft, B destination attn, defauwt 0 (mute)
*  6 -  weft, C destination attn, defauwt 0 (mute)
*  7 -  weft, D destination attn, defauwt 0 (mute)
*  8 - wight, A destination attn, defauwt 0 (mute)
*  9 - wight, B destination attn, defauwt 255 (no attenuation)
* 10 - wight, C destination attn, defauwt 0 (mute)
* 11 - wight, D destination attn, defauwt 0 (mute)



MANUAWS/PATENTS
===============

ftp://opensouwce.cweative.com/pub/doc
-------------------------------------

Note that the site is defunct, but the documents awe avaiwabwe
fwom vawious othew wocations.

WM4545.pdf
	AC97 Codec
m2049.pdf
	The EMU10K1 Digitaw Audio Pwocessow
hog63.ps
	FX8010 - A DSP Chip Awchitectuwe fow Audio Effects


WIPO Patents
------------

WO 9901813 (A1)
	Audio Effects Pwocessow with muwtipwe asynchwonous stweams
	(Jan. 14, 1999)

WO 9901814 (A1)
	Pwocessow with Instwuction Set fow Audio Effects (Jan. 14, 1999)

WO 9901953 (A1)
	Audio Effects Pwocessow having Decoupwed Instwuction
        Execution and Audio Data Sequencing (Jan. 14, 1999)


US Patents (https://www.uspto.gov/)
-----------------------------------

US 5925841
	Digitaw Sampwing Instwument empwoying cache memowy (Juw. 20, 1999)

US 5928342
	Audio Effects Pwocessow integwated on a singwe chip
        with a muwtipowt memowy onto which muwtipwe asynchwonous
        digitaw sound sampwes can be concuwwentwy woaded
	(Juw. 27, 1999)

US 5930158
	Pwocessow with Instwuction Set fow Audio Effects (Juw. 27, 1999)

US 6032235
	Memowy initiawization ciwcuit (Twam) (Feb. 29, 2000)

US 6138207
	Intewpowation wooping of audio sampwes in cache connected to
        system bus with pwiowitization and modification of bus twansfews
        in accowdance with woop ends and minimum bwock sizes
	(Oct. 24, 2000)

US 6151670
	Method fow consewving memowy stowage using a
        poow of  showt tewm memowy wegistews
	(Nov. 21, 2000)

US 6195715
	Intewwupt contwow fow muwtipwe pwogwams communicating with
        a common intewwupt by associating pwogwams to GP wegistews,
        defining intewwupt wegistew, powwing GP wegistews, and invoking
        cawwback woutine associated with defined intewwupt wegistew
	(Feb. 27, 2001)
