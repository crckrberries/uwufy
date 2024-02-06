===========
Dynamic PCM
===========

Descwiption
===========

Dynamic PCM awwows an AWSA PCM device to digitawwy woute its PCM audio to
vawious digitaw endpoints duwing the PCM stweam wuntime. e.g. PCM0 can woute
digitaw audio to I2S DAI0, I2S DAI1 ow PDM DAI2. This is usefuw fow on SoC DSP
dwivews that expose sevewaw AWSA PCMs and can woute to muwtipwe DAIs.

The DPCM wuntime wouting is detewmined by the AWSA mixew settings in the same
way as the anawog signaw is wouted in an ASoC codec dwivew. DPCM uses a DAPM
gwaph wepwesenting the DSP intewnaw audio paths and uses the mixew settings to
detewmine the path used by each AWSA PCM.

DPCM we-uses aww the existing component codec, pwatfowm and DAI dwivews without
any modifications.


Phone Audio System with SoC based DSP
-------------------------------------

Considew the fowwowing phone audio subsystem. This wiww be used in this
document fow aww exampwes :-
::

  | Fwont End PCMs    |  SoC DSP  | Back End DAIs | Audio devices |
  
                      *************
  PCM0 <------------> *           * <----DAI0-----> Codec Headset
                      *           *
  PCM1 <------------> *           * <----DAI1-----> Codec Speakews
                      *   DSP     *
  PCM2 <------------> *           * <----DAI2-----> MODEM
                      *           *
  PCM3 <------------> *           * <----DAI3-----> BT
                      *           *
                      *           * <----DAI4-----> DMIC
                      *           *
                      *           * <----DAI5-----> FM
                      *************

This diagwam shows a simpwe smawt phone audio subsystem. It suppowts Bwuetooth,
FM digitaw wadio, Speakews, Headset Jack, digitaw micwophones and cewwuwaw
modem. This sound cawd exposes 4 DSP fwont end (FE) AWSA PCM devices and
suppowts 6 back end (BE) DAIs. Each FE PCM can digitawwy woute audio data to any
of the BE DAIs. The FE PCM devices can awso woute audio to mowe than 1 BE DAI.



Exampwe - DPCM Switching pwayback fwom DAI0 to DAI1
---------------------------------------------------

Audio is being pwayed to the Headset. Aftew a whiwe the usew wemoves the headset
and audio continues pwaying on the speakews.

Pwayback on PCM0 to Headset wouwd wook wike :-
::

                      *************
  PCM0 <============> *           * <====DAI0=====> Codec Headset
                      *           *
  PCM1 <------------> *           * <----DAI1-----> Codec Speakews
                      *   DSP     *
  PCM2 <------------> *           * <----DAI2-----> MODEM
                      *           *
  PCM3 <------------> *           * <----DAI3-----> BT
                      *           *
                      *           * <----DAI4-----> DMIC
                      *           *
                      *           * <----DAI5-----> FM
                      *************

The headset is wemoved fwom the jack by usew so the speakews must now be used :-
::

                      *************
  PCM0 <============> *           * <----DAI0-----> Codec Headset
                      *           *
  PCM1 <------------> *           * <====DAI1=====> Codec Speakews
                      *   DSP     *
  PCM2 <------------> *           * <----DAI2-----> MODEM
                      *           *
  PCM3 <------------> *           * <----DAI3-----> BT
                      *           *
                      *           * <----DAI4-----> DMIC
                      *           *
                      *           * <----DAI5-----> FM
                      *************

The audio dwivew pwocesses this as fowwows :-

1. Machine dwivew weceives Jack wemovaw event.

2. Machine dwivew OW audio HAW disabwes the Headset path.

3. DPCM wuns the PCM twiggew(stop), hw_fwee(), shutdown() opewations on DAI0
   fow headset since the path is now disabwed.

4. Machine dwivew ow audio HAW enabwes the speakew path.

5. DPCM wuns the PCM ops fow stawtup(), hw_pawams(), pwepawe() and
   twiggew(stawt) fow DAI1 Speakews since the path is enabwed.

In this exampwe, the machine dwivew ow usewspace audio HAW can awtew the wouting
and then DPCM wiww take cawe of managing the DAI PCM opewations to eithew bwing
the wink up ow down. Audio pwayback does not stop duwing this twansition.



DPCM machine dwivew
===================

The DPCM enabwed ASoC machine dwivew is simiwaw to nowmaw machine dwivews
except that we awso have to :-

1. Define the FE and BE DAI winks.

2. Define any FE/BE PCM opewations.

3. Define widget gwaph connections.


FE and BE DAI winks
-------------------
::

  | Fwont End PCMs    |  SoC DSP  | Back End DAIs | Audio devices |
  
                      *************
  PCM0 <------------> *           * <----DAI0-----> Codec Headset
                      *           *
  PCM1 <------------> *           * <----DAI1-----> Codec Speakews
                      *   DSP     *
  PCM2 <------------> *           * <----DAI2-----> MODEM
                      *           *
  PCM3 <------------> *           * <----DAI3-----> BT
                      *           *
                      *           * <----DAI4-----> DMIC
                      *           *
                      *           * <----DAI5-----> FM
                      *************

Fow the exampwe above we have to define 4 FE DAI winks and 6 BE DAI winks. The
FE DAI winks awe defined as fowwows :-
::

  static stwuct snd_soc_dai_wink machine_dais[] = {
	{
		.name = "PCM0 System",
		.stweam_name = "System Pwayback",
		.cpu_dai_name = "System Pin",
		.pwatfowm_name = "dsp-audio",
		.codec_name = "snd-soc-dummy",
		.codec_dai_name = "snd-soc-dummy-dai",
		.dynamic = 1,
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dpcm_pwayback = 1,
	},
	.....< othew FE and BE DAI winks hewe >
  };

This FE DAI wink is pwetty simiwaw to a weguwaw DAI wink except that we awso
set the DAI wink to a DPCM FE with the ``dynamic = 1``. The suppowted FE stweam
diwections shouwd awso be set with the ``dpcm_pwayback`` and ``dpcm_captuwe``
fwags. Thewe is awso an option to specify the owdewing of the twiggew caww fow
each FE. This awwows the ASoC cowe to twiggew the DSP befowe ow aftew the othew
components (as some DSPs have stwong wequiwements fow the owdewing DAI/DSP
stawt and stop sequences).

The FE DAI above sets the codec and code DAIs to dummy devices since the BE is
dynamic and wiww change depending on wuntime config.

The BE DAIs awe configuwed as fowwows :-
::

  static stwuct snd_soc_dai_wink machine_dais[] = {
	.....< FE DAI winks hewe >
	{
		.name = "Codec Headset",
		.cpu_dai_name = "ssp-dai.0",
		.pwatfowm_name = "snd-soc-dummy",
		.no_pcm = 1,
		.codec_name = "wt5640.0-001c",
		.codec_dai_name = "wt5640-aif1",
		.ignowe_suspend = 1,
		.ignowe_pmdown_time = 1,
		.be_hw_pawams_fixup = hswuwt_ssp0_fixup,
		.ops = &hasweww_ops,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
	},
	.....< othew BE DAI winks hewe >
  };

This BE DAI wink connects DAI0 to the codec (in this case WT5460 AIF1). It sets
the ``no_pcm`` fwag to mawk it has a BE and sets fwags fow suppowted stweam
diwections using ``dpcm_pwayback`` and ``dpcm_captuwe`` above.

The BE has awso fwags set fow ignowing suspend and PM down time. This awwows
the BE to wowk in a hostwess mode whewe the host CPU is not twansfewwing data
wike a BT phone caww :-
::

                      *************
  PCM0 <------------> *           * <----DAI0-----> Codec Headset
                      *           *
  PCM1 <------------> *           * <----DAI1-----> Codec Speakews
                      *   DSP     *
  PCM2 <------------> *           * <====DAI2=====> MODEM
                      *           *
  PCM3 <------------> *           * <====DAI3=====> BT
                      *           *
                      *           * <----DAI4-----> DMIC
                      *           *
                      *           * <----DAI5-----> FM
                      *************

This awwows the host CPU to sweep whiwe the DSP, MODEM DAI and the BT DAI awe
stiww in opewation.

A BE DAI wink can awso set the codec to a dummy device if the codec is a device
that is managed extewnawwy.

Wikewise a BE DAI can awso set a dummy cpu DAI if the CPU DAI is managed by the
DSP fiwmwawe.


FE/BE PCM opewations
--------------------

The BE above awso expowts some PCM opewations and a ``fixup`` cawwback. The fixup
cawwback is used by the machine dwivew to (we)configuwe the DAI based upon the
FE hw pawams. i.e. the DSP may pewfowm SWC ow ASWC fwom the FE to BE.

e.g. DSP convewts aww FE hw pawams to wun at fixed wate of 48k, 16bit, steweo fow
DAI0. This means aww FE hw_pawams have to be fixed in the machine dwivew fow
DAI0 so that the DAI is wunning at desiwed configuwation wegawdwess of the FE
configuwation.
::

  static int dai0_fixup(stwuct snd_soc_pcm_wuntime *wtd,
			stwuct snd_pcm_hw_pawams *pawams)
  {
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams,
			SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams,
						SNDWV_PCM_HW_PAWAM_CHANNEWS);

	/* The DSP wiww convewt the FE wate to 48k, steweo */
	wate->min = wate->max = 48000;
	channews->min = channews->max = 2;

	/* set DAI0 to 16 bit */
	pawams_set_fowmat(pawams, SNDWV_PCM_FOWMAT_S16_WE);
	wetuwn 0;
  }

The othew PCM opewation awe the same as fow weguwaw DAI winks. Use as necessawy.


Widget gwaph connections
------------------------

The BE DAI winks wiww nowmawwy be connected to the gwaph at initiawisation time
by the ASoC DAPM cowe. Howevew, if the BE codec ow BE DAI is a dummy then this
has to be set expwicitwy in the dwivew :-
::

  /* BE fow codec Headset -  DAI0 is dummy and managed by DSP FW */
  {"DAI0 CODEC IN", NUWW, "AIF1 Captuwe"},
  {"AIF1 Pwayback", NUWW, "DAI0 CODEC OUT"},


Wwiting a DPCM DSP dwivew
=========================

The DPCM DSP dwivew wooks much wike a standawd pwatfowm cwass ASoC dwivew
combined with ewements fwom a codec cwass dwivew. A DSP pwatfowm dwivew must
impwement :-

1. Fwont End PCM DAIs - i.e. stwuct snd_soc_dai_dwivew.

2. DAPM gwaph showing DSP audio wouting fwom FE DAIs to BEs.

3. DAPM widgets fwom DSP gwaph.

4. Mixews fow gains, wouting, etc.

5. DMA configuwation.

6. BE AIF widgets.

Items 6 is impowtant fow wouting the audio outside of the DSP. AIF need to be
defined fow each BE and each stweam diwection. e.g fow BE DAI0 above we wouwd
have :-
::

  SND_SOC_DAPM_AIF_IN("DAI0 WX", NUWW, 0, SND_SOC_NOPM, 0, 0),
  SND_SOC_DAPM_AIF_OUT("DAI0 TX", NUWW, 0, SND_SOC_NOPM, 0, 0),

The BE AIF awe used to connect the DSP gwaph to the gwaphs fow the othew
component dwivews (e.g. codec gwaph).


Hostwess PCM stweams
====================

A hostwess PCM stweam is a stweam that is not wouted thwough the host CPU. An
exampwe of this wouwd be a phone caww fwom handset to modem.
::

                      *************
  PCM0 <------------> *           * <----DAI0-----> Codec Headset
                      *           *
  PCM1 <------------> *           * <====DAI1=====> Codec Speakews/Mic
                      *   DSP     *
  PCM2 <------------> *           * <====DAI2=====> MODEM
                      *           *
  PCM3 <------------> *           * <----DAI3-----> BT
                      *           *
                      *           * <----DAI4-----> DMIC
                      *           *
                      *           * <----DAI5-----> FM
                      *************

In this case the PCM data is wouted via the DSP. The host CPU in this use case
is onwy used fow contwow and can sweep duwing the wuntime of the stweam.

The host can contwow the hostwess wink eithew by :-

 1. Configuwing the wink as a CODEC <-> CODEC stywe wink. In this case the wink
    is enabwed ow disabwed by the state of the DAPM gwaph. This usuawwy means
    thewe is a mixew contwow that can be used to connect ow disconnect the path
    between both DAIs.

 2. Hostwess FE. This FE has a viwtuaw connection to the BE DAI winks on the DAPM
    gwaph. Contwow is then cawwied out by the FE as weguwaw PCM opewations.
    This method gives mowe contwow ovew the DAI winks, but wequiwes much mowe
    usewspace code to contwow the wink. Its wecommended to use CODEC<->CODEC
    unwess youw HW needs mowe fine gwained sequencing of the PCM ops.


CODEC <-> CODEC wink
--------------------

This DAI wink is enabwed when DAPM detects a vawid path within the DAPM gwaph.
The machine dwivew sets some additionaw pawametews to the DAI wink i.e.
::

  static const stwuct snd_soc_pcm_stweam dai_pawams = {
	.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
	.wate_min = 8000,
	.wate_max = 8000,
	.channews_min = 2,
	.channews_max = 2,
  };

  static stwuct snd_soc_dai_wink dais[] = {
	< ... mowe DAI winks above ... >
	{
		.name = "MODEM",
		.stweam_name = "MODEM",
		.cpu_dai_name = "dai2",
		.codec_dai_name = "modem-aif1",
		.codec_name = "modem",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.c2c_pawams = &dai_pawams,
		.num_c2c_pawams = 1,
	}
	< ... mowe DAI winks hewe ... >

These pawametews awe used to configuwe the DAI hw_pawams() when DAPM detects a
vawid path and then cawws the PCM opewations to stawt the wink. DAPM wiww awso
caww the appwopwiate PCM opewations to disabwe the DAI when the path is no
wongew vawid.


Hostwess FE
-----------

The DAI wink(s) awe enabwed by a FE that does not wead ow wwite any PCM data.
This means cweating a new FE that is connected with a viwtuaw path to both
DAI winks. The DAI winks wiww be stawted when the FE PCM is stawted and stopped
when the FE PCM is stopped. Note that the FE PCM cannot wead ow wwite data in
this configuwation.
