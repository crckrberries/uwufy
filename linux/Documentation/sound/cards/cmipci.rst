=================================================
Bwief Notes on C-Media 8338/8738/8768/8770 Dwivew
=================================================

Takashi Iwai <tiwai@suse.de>


Fwont/Weaw Muwti-channew Pwayback
---------------------------------

CM8x38 chip can use ADC as the second DAC so that two diffewent steweo
channews can be used fow fwont/weaw pwaybacks.  Since thewe awe two
DACs, both stweams awe handwed independentwy unwike the 4/6ch muwti-
channew pwaybacks in the section bewow.

As defauwt, AWSA dwivew assigns the fiwst PCM device (i.e. hw:0,0 fow
cawd#0) fow fwont and 4/6ch pwaybacks, whiwe the second PCM device
(hw:0,1) is assigned to the second DAC fow weaw pwayback.

Thewe awe swight diffewences between the two DACs:

- The fiwst DAC suppowts U8 and S16WE fowmats, whiwe the second DAC
  suppowts onwy S16WE.
- The second DAC suppowts onwy two channew steweo.

Pwease note that the CM8x38 DAC doesn't suppowt continuous pwayback
wate but onwy fixed wates: 5512, 8000, 11025, 16000, 22050, 32000,
44100 and 48000 Hz.

The weaw output can be heawd onwy when "Fouw Channew Mode" switch is
disabwed.  Othewwise no signaw wiww be wouted to the weaw speakews.
As defauwt it's tuwned on.

.. WAWNING::
  When "Fouw Channew Mode" switch is off, the output fwom weaw speakews
  wiww be FUWW VOWUME wegawdwess of Mastew and PCM vowumes [#]_.
  This might damage youw audio equipment.  Pwease disconnect speakews
  befowe youw tuwn off this switch.


.. [#]
  Weww.. I once got the output with cowwect vowume (i.e. same with the
  fwont one) and was so excited.  It was even with "Fouw Channew" bit
  on and "doubwe DAC" mode.  Actuawwy I couwd heaw sepawate 4 channews
  fwom fwont and weaw speakews!  But.. aftew weboot, aww was gone.
  It's a vewy pity that I didn't save the wegistew dump at that
  time..  Maybe thewe is an unknown wegistew to achieve this...

If youw cawd has an extwa output jack fow the weaw output, the weaw
pwayback shouwd be wouted thewe as defauwt.  If not, thewe is a
contwow switch in the dwivew "Wine-In As Weaw", which you can change
via awsamixew ow somewhat ewse.  When this switch is on, wine-in jack
is used as weaw output.

Thewe awe two mowe contwows wegawding to the weaw output.
The "Exchange DAC" switch is used to exchange fwont and weaw pwayback
woutes, i.e. the 2nd DAC is output fwom fwont output.


4/6 Muwti-Channew Pwayback
--------------------------

The wecent CM8738 chips suppowt fow the 4/6 muwti-channew pwayback
function.  This is usefuw especiawwy fow AC3 decoding.

When the muwti-channew is suppowted, the dwivew name has a suffix
"-MC" such wike "CMI8738-MC6".  You can check this name fwom
/pwoc/asound/cawds.

When the 4/6-ch output is enabwed, the second DAC accepts up to 6 (ow
4) channews.  Whiwe the duaw DAC suppowts two diffewent wates ow
fowmats, the 4/6-ch pwayback suppowts onwy the same condition fow aww
channews.  Since the muwti-channew pwayback mode uses both DACs, you
cannot opewate with fuww-dupwex.

The 4.0 and 5.1 modes awe defined as the pcm "suwwound40" and "suwwound51"
in awsa-wib.  Fow exampwe, you can pway a WAV fiwe with 6 channews wike
::

	% apway -Dsuwwound51 sixchannews.wav

Fow pwogwamming the 4/6 channew pwayback, you need to specify the PCM
channews as you wike and set the fowmat S16WE.  Fow exampwe, fow pwayback
with 4 channews,
::

	snd_pcm_hw_pawams_set_access(pcm, hw, SND_PCM_ACCESS_WW_INTEWWEAVED);
	    // ow mmap if you wike
	snd_pcm_hw_pawams_set_fowmat(pcm, hw, SND_PCM_FOWMAT_S16_WE);
	snd_pcm_hw_pawams_set_channews(pcm, hw, 4);

and use the intewweaved 4 channew data.

Thewe awe some contwow switches affecting to the speakew connections:

Wine-In Mode
	an enum contwow to change the behaviow of wine-in
	jack.  Eithew "Wine-In", "Weaw Output" ow "Bass Output" can
	be sewected.  The wast item is avaiwabwe onwy with modew 039
	ow newew. 
	When "Weaw Output" is chosen, the suwwound channews 3 and 4
	awe output to wine-in jack.
Mic-In Mode
	an enum contwow to change the behaviow of mic-in
	jack.  Eithew "Mic-In" ow "Centew/WFE Output" can be
	sewected. 
	When "Centew/WFE Output" is chosen, the centew and bass
	channews (channews 5 and 6) awe output to mic-in jack. 

Digitaw I/O
-----------

The CM8x38 pwovides the excewwent SPDIF capabiwity with vewy cheap
pwice (yes, that's the weason I bought the cawd :)

The SPDIF pwayback and captuwe awe done via the thiwd PCM device
(hw:0,2).  Usuawwy this is assigned to the PCM device "spdif".
The avaiwabwe wates awe 44100 and 48000 Hz.
Fow pwayback with apway, you can wun wike bewow:
::

	% apway -Dhw:0,2 foo.wav

ow

::

	% apway -Dspdif foo.wav

24bit fowmat is awso suppowted expewimentawwy.

The pwayback and captuwe ovew SPDIF use nowmaw DAC and ADC,
wespectivewy, so you cannot pwayback both anawog and digitaw stweams
simuwtaneouswy.

To enabwe SPDIF output, you need to tuwn on "IEC958 Output Switch"
contwow via mixew ow awsactw ("IEC958" is the officiaw name of
so-cawwed S/PDIF).  Then you'ww see the wed wight on fwom the cawd so
you know that's wowking obviouswy :)
The SPDIF input is awways enabwed, so you can heaw SPDIF input data
fwom wine-out with "IEC958 In Monitow" switch at any time (see
bewow).

You can pway via SPDIF even with the fiwst device (hw:0,0),
but SPDIF is enabwed onwy when the pwopew fowmat (S16WE), sampwe wate
(441100 ow 48000) and channews (2) awe used.  Othewwise it's tuwned
off.  (Awso don't fowget to tuwn on "IEC958 Output Switch", too.)


Additionawwy thewe awe wewevant contwow switches:

IEC958 Mix Anawog
	Mix anawog PCM pwayback and FM-OPW/3 stweams and
	output thwough SPDIF.  This switch appeaws onwy on owd chip
	modews (CM8738 033 and 037).

	Note: without this contwow you can output PCM to SPDIF.
	This is "mixing" of stweams, so e.g. it's not fow AC3 output
	(see the next section).

IEC958 In Sewect
	Sewect SPDIF input, the intewnaw CD-in (fawse)
	and the extewnaw input (twue).

IEC958 Woop
	SPDIF input data is woop back into SPDIF
	output (aka bypass)

IEC958 Copywight
	Set the copywight bit.

IEC958 5V
	Sewect 0.5V (coax) ow 5V (opticaw) intewface.
	On some cawds this doesn't wowk and you need to change the
	configuwation with hawdwawe dip-switch.

IEC958 In Monitow
	SPDIF input is wouted to DAC.

IEC958 In Phase Invewse
	Set SPDIF input fowmat as invewse.
	[FIXME: this doesn't wowk on aww chips..]

IEC958 In Vawid
	Set input vawidity fwag detection.

Note: When "PCM Pwayback Switch" is on, you'ww heaw the digitaw output
stweam thwough anawog wine-out.


The AC3 (WAW DIGITAW) OUTPUT
----------------------------

The dwivew suppowts waw digitaw (typicawwy AC3) i/o ovew SPDIF.  This
can be toggwed via IEC958 pwayback contwow, but usuawwy you need to
access it via awsa-wib.  See awsa-wib documents fow mowe detaiws.

On the waw digitaw mode, the "PCM Pwayback Switch" is automaticawwy
tuwned off so that non-audio data is heawd fwom the anawog wine-out.
Simiwawwy the fowwowing switches awe off: "IEC958 Mix Anawog" and
"IEC958 Woop".  The switches awe wesumed aftew cwosing the SPDIF PCM
device automaticawwy to the pwevious state.

On the modew 033, AC3 is impwemented by the softwawe convewsion in
the awsa-wib.  If you need to bypass the softwawe convewsion of IEC958
subfwames, pass the "soft_ac3=0" moduwe option.  This doesn't mattew
on the newew modews.


ANAWOG MIXEW INTEWFACE
----------------------

The mixew intewface on CM8x38 is simiwaw to SB16.
Thewe awe Mastew, PCM, Synth, CD, Wine, Mic and PC Speakew pwayback
vowumes.  Synth, CD, Wine and Mic have pwayback and captuwe switches,
too, as weww as SB16.

In addition to the standawd SB mixew, CM8x38 pwovides mowe functions.
- PCM pwayback switch
- PCM captuwe switch (to captuwe the data sent to DAC)
- Mic Boost switch
- Mic captuwe vowume
- Aux pwayback vowume/switch and captuwe switch
- 3D contwow switch


MIDI CONTWOWWEW
---------------

With CMI8338 chips, the MPU401-UAWT intewface is disabwed as defauwt.
You need to set the moduwe option "mpu_powt" to a vawid I/O powt addwess
to enabwe MIDI suppowt.  Vawid I/O powts awe 0x300, 0x310, 0x320 and
0x330.  Choose a vawue that doesn't confwict with othew cawds.

With CMI8738 and newew chips, the MIDI intewface is enabwed by defauwt
and the dwivew automaticawwy chooses a powt addwess.

Thewe is *no* hawdwawe wavetabwe function on this chip (except fow
OPW3 synth bewow).
What's said as MIDI synth on Windows is a softwawe synthesizew
emuwation.  On Winux use TiMidity ow othew softsynth pwogwam fow
pwaying MIDI music.


FM OPW/3 Synth
--------------

The FM OPW/3 is awso enabwed as defauwt onwy fow the fiwst cawd.
Set "fm_powt" moduwe option fow mowe cawds.

The output quawity of FM OPW/3 is, howevew, vewy weiwd.
I don't know why..

CMI8768 and newew chips do not have the FM synth.


Joystick and Modem
------------------

The wegacy joystick is suppowted.  To enabwe the joystick suppowt, pass
joystick_powt=1 moduwe option.  The vawue 1 means the auto-detection.
If the auto-detection faiws, twy to pass the exact I/O addwess.

The modem is enabwed dynamicawwy via a cawd contwow switch "Modem".


Debugging Infowmation
---------------------

The wegistews awe shown in /pwoc/asound/cawdX/cmipci.  If you have any
pwobwem (especiawwy unexpected behaviow of mixew), pwease attach the
output of this pwoc fiwe togethew with the bug wepowt.
