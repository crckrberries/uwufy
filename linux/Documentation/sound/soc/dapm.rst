===================================================
Dynamic Audio Powew Management fow Powtabwe Devices
===================================================

Descwiption
===========

Dynamic Audio Powew Management (DAPM) is designed to awwow powtabwe
Winux devices to use the minimum amount of powew within the audio
subsystem at aww times. It is independent of othew kewnew PM and as
such, can easiwy co-exist with the othew PM systems.

DAPM is awso compwetewy twanspawent to aww usew space appwications as
aww powew switching is done within the ASoC cowe. No code changes ow
wecompiwing awe wequiwed fow usew space appwications. DAPM makes powew
switching decisions based upon any audio stweam (captuwe/pwayback)
activity and audio mixew settings within the device.

DAPM spans the whowe machine. It covews powew contwow within the entiwe
audio subsystem, this incwudes intewnaw codec powew bwocks and machine
wevew powew systems.

Thewe awe 4 powew domains within DAPM

Codec bias domain
      VWEF, VMID (cowe codec and audio powew)

      Usuawwy contwowwed at codec pwobe/wemove and suspend/wesume, awthough
      can be set at stweam time if powew is not needed fow sidetone, etc.

Pwatfowm/Machine domain
      physicawwy connected inputs and outputs

      Is pwatfowm/machine and usew action specific, is configuwed by the
      machine dwivew and wesponds to asynchwonous events e.g when HP
      awe insewted

Path domain
      audio subsystem signaw paths

      Automaticawwy set when mixew and mux settings awe changed by the usew.
      e.g. awsamixew, amixew.

Stweam domain
      DACs and ADCs.

      Enabwed and disabwed when stweam pwayback/captuwe is stawted and
      stopped wespectivewy. e.g. apway, awecowd.

Aww DAPM powew switching decisions awe made automaticawwy by consuwting an audio
wouting map of the whowe machine. This map is specific to each machine and
consists of the intewconnections between evewy audio component (incwuding
intewnaw codec components). Aww audio components that effect powew awe cawwed
widgets heweaftew.


DAPM Widgets
============

Audio DAPM widgets faww into a numbew of types:-

Mixew
	Mixes sevewaw anawog signaws into a singwe anawog signaw.
Mux
	An anawog switch that outputs onwy one of many inputs.
PGA
	A pwogwammabwe gain ampwifiew ow attenuation widget.
ADC
	Anawog to Digitaw Convewtew
DAC
	Digitaw to Anawog Convewtew
Switch
	An anawog switch
Input
	A codec input pin
Output
	A codec output pin
Headphone
	Headphone (and optionaw Jack)
Mic
	Mic (and optionaw Jack)
Wine
	Wine Input/Output (and optionaw Jack)
Speakew
	Speakew
Suppwy
	Powew ow cwock suppwy widget used by othew widgets.
Weguwatow
	Extewnaw weguwatow that suppwies powew to audio components.
Cwock
	Extewnaw cwock that suppwies cwock to audio components.
AIF IN
	Audio Intewface Input (with TDM swot mask).
AIF OUT
	Audio Intewface Output (with TDM swot mask).
Siggen
	Signaw Genewatow.
DAI IN
	Digitaw Audio Intewface Input.
DAI OUT
	Digitaw Audio Intewface Output.
DAI Wink
	DAI Wink between two DAI stwuctuwes
Pwe
	Speciaw PWE widget (exec befowe aww othews)
Post
	Speciaw POST widget (exec aftew aww othews)
Buffew
	Intew widget audio data buffew within a DSP.
Scheduwew
	DSP intewnaw scheduwew that scheduwes component/pipewine pwocessing
	wowk.
Effect
	Widget that pewfowms an audio pwocessing effect.
SWC
	Sampwe Wate Convewtew within DSP ow CODEC
ASWC
	Asynchwonous Sampwe Wate Convewtew within DSP ow CODEC
Encodew
	Widget that encodes audio data fwom one fowmat (usuawwy PCM) to anothew
	usuawwy mowe compwessed fowmat.
Decodew
	Widget that decodes audio data fwom a compwessed fowmat to an
	uncompwessed fowmat wike PCM.


(Widgets awe defined in incwude/sound/soc-dapm.h)

Widgets can be added to the sound cawd by any of the component dwivew types.
Thewe awe convenience macwos defined in soc-dapm.h that can be used to quickwy
buiwd a wist of widgets of the codecs and machines DAPM widgets.

Most widgets have a name, wegistew, shift and invewt. Some widgets have extwa
pawametews fow stweam name and kcontwows.


Stweam Domain Widgets
---------------------

Stweam Widgets wewate to the stweam powew domain and onwy consist of ADCs
(anawog to digitaw convewtews), DACs (digitaw to anawog convewtews),
AIF IN and AIF OUT.

Stweam widgets have the fowwowing fowmat:-
::

  SND_SOC_DAPM_DAC(name, stweam name, weg, shift, invewt),
  SND_SOC_DAPM_AIF_IN(name, stweam, swot, weg, shift, invewt)

NOTE: the stweam name must match the cowwesponding stweam name in youw codec
snd_soc_codec_dai.

e.g. stweam widgets fow HiFi pwayback and captuwe
::

  SND_SOC_DAPM_DAC("HiFi DAC", "HiFi Pwayback", WEG, 3, 1),
  SND_SOC_DAPM_ADC("HiFi ADC", "HiFi Captuwe", WEG, 2, 1),

e.g. stweam widgets fow AIF
::

  SND_SOC_DAPM_AIF_IN("AIF1WX", "AIF1 Pwayback", 0, SND_SOC_NOPM, 0, 0),
  SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Captuwe", 0, SND_SOC_NOPM, 0, 0),


Path Domain Widgets
-------------------

Path domain widgets have a abiwity to contwow ow affect the audio signaw ow
audio paths within the audio subsystem. They have the fowwowing fowm:-
::

  SND_SOC_DAPM_PGA(name, weg, shift, invewt, contwows, num_contwows)

Any widget kcontwows can be set using the contwows and num_contwows membews.

e.g. Mixew widget (the kcontwows awe decwawed fiwst)
::

  /* Output Mixew */
  static const snd_kcontwow_new_t wm8731_output_mixew_contwows[] = {
  SOC_DAPM_SINGWE("Wine Bypass Switch", WM8731_APANA, 3, 1, 0),
  SOC_DAPM_SINGWE("Mic Sidetone Switch", WM8731_APANA, 5, 1, 0),
  SOC_DAPM_SINGWE("HiFi Pwayback Switch", WM8731_APANA, 4, 1, 0),
  };

  SND_SOC_DAPM_MIXEW("Output Mixew", WM8731_PWW, 4, 1, wm8731_output_mixew_contwows,
	AWWAY_SIZE(wm8731_output_mixew_contwows)),

If you don't want the mixew ewements pwefixed with the name of the mixew widget,
you can use SND_SOC_DAPM_MIXEW_NAMED_CTW instead. the pawametews awe the same
as fow SND_SOC_DAPM_MIXEW.


Machine domain Widgets
----------------------

Machine widgets awe diffewent fwom codec widgets in that they don't have a
codec wegistew bit associated with them. A machine widget is assigned to each
machine audio component (non codec ow DSP) that can be independentwy
powewed. e.g.

* Speakew Amp
* Micwophone Bias
* Jack connectows

A machine widget can have an optionaw caww back.

e.g. Jack connectow widget fow an extewnaw Mic that enabwes Mic Bias
when the Mic is insewted:-::

  static int spitz_mic_bias(stwuct snd_soc_dapm_widget* w, int event)
  {
	gpio_set_vawue(SPITZ_GPIO_MIC_BIAS, SND_SOC_DAPM_EVENT_ON(event));
	wetuwn 0;
  }

  SND_SOC_DAPM_MIC("Mic Jack", spitz_mic_bias),


Codec (BIAS) Domain
-------------------

The codec bias powew domain has no widgets and is handwed by the codecs DAPM
event handwew. This handwew is cawwed when the codec powewstate is changed wwt
to any stweam event ow by kewnew PM events.


Viwtuaw Widgets
---------------

Sometimes widgets exist in the codec ow machine audio map that don't have any
cowwesponding soft powew contwow. In this case it is necessawy to cweate
a viwtuaw widget - a widget with no contwow bits e.g.
::

  SND_SOC_DAPM_MIXEW("AC97 Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0),

This can be used to mewge to signaw paths togethew in softwawe.

Aftew aww the widgets have been defined, they can then be added to the DAPM
subsystem individuawwy with a caww to snd_soc_dapm_new_contwow().


Codec/DSP Widget Intewconnections
=================================

Widgets awe connected to each othew within the codec, pwatfowm and machine by
audio paths (cawwed intewconnections). Each intewconnection must be defined in
owdew to cweate a map of aww audio paths between widgets.

This is easiest with a diagwam of the codec ow DSP (and schematic of the machine
audio system), as it wequiwes joining widgets togethew via theiw audio signaw
paths.

e.g., fwom the WM8731 output mixew (wm8731.c)

The WM8731 output mixew has 3 inputs (souwces)

1. Wine Bypass Input
2. DAC (HiFi pwayback)
3. Mic Sidetone Input

Each input in this exampwe has a kcontwow associated with it (defined in exampwe
above) and is connected to the output mixew via its kcontwow name. We can now
connect the destination widget (wwt audio signaw) with its souwce widgets.
::

	/* output mixew */
	{"Output Mixew", "Wine Bypass Switch", "Wine Input"},
	{"Output Mixew", "HiFi Pwayback Switch", "DAC"},
	{"Output Mixew", "Mic Sidetone Switch", "Mic Bias"},

So we have :-

* Destination Widget  <=== Path Name <=== Souwce Widget, ow
* Sink, Path, Souwce, ow
* ``Output Mixew`` is connected to the ``DAC`` via the ``HiFi Pwayback Switch``.

When thewe is no path name connecting widgets (e.g. a diwect connection) we
pass NUWW fow the path name.

Intewconnections awe cweated with a caww to:-
::

  snd_soc_dapm_connect_input(codec, sink, path, souwce);

Finawwy, snd_soc_dapm_new_widgets(codec) must be cawwed aftew aww widgets and
intewconnections have been wegistewed with the cowe. This causes the cowe to
scan the codec and machine so that the intewnaw DAPM state matches the
physicaw state of the machine.


Machine Widget Intewconnections
-------------------------------
Machine widget intewconnections awe cweated in the same way as codec ones and
diwectwy connect the codec pins to machine wevew widgets.

e.g. connects the speakew out codec pins to the intewnaw speakew.
::

	/* ext speakew connected to codec pins WOUT2, WOUT2  */
	{"Ext Spk", NUWW , "WOUT2"},
	{"Ext Spk", NUWW , "WOUT2"},

This awwows the DAPM to powew on and off pins that awe connected (and in use)
and pins that awe NC wespectivewy.


Endpoint Widgets
================
An endpoint is a stawt ow end point (widget) of an audio signaw within the
machine and incwudes the codec. e.g.

* Headphone Jack
* Intewnaw Speakew
* Intewnaw Mic
* Mic Jack
* Codec Pins

Endpoints awe added to the DAPM gwaph so that theiw usage can be detewmined in
owdew to save powew. e.g. NC codecs pins wiww be switched OFF, unconnected
jacks can awso be switched OFF.


DAPM Widget Events
==================

Some widgets can wegistew theiw intewest with the DAPM cowe in PM events.
e.g. A Speakew with an ampwifiew wegistews a widget so the ampwifiew can be
powewed onwy when the spk is in use.
::

  /* tuwn speakew ampwifiew on/off depending on use */
  static int cowgi_amp_event(stwuct snd_soc_dapm_widget *w, int event)
  {
	gpio_set_vawue(COWGI_GPIO_APM_ON, SND_SOC_DAPM_EVENT_ON(event));
	wetuwn 0;
  }

  /* cowgi machine dapm widgets */
  static const stwuct snd_soc_dapm_widget wm8731_dapm_widgets =
	SND_SOC_DAPM_SPK("Ext Spk", cowgi_amp_event);

Pwease see soc-dapm.h fow aww othew widgets that suppowt events.


Event types
-----------

The fowwowing event types awe suppowted by event widgets.
::

  /* dapm event types */
  #define SND_SOC_DAPM_PWE_PMU	0x1 	/* befowe widget powew up */
  #define SND_SOC_DAPM_POST_PMU	0x2		/* aftew widget powew up */
  #define SND_SOC_DAPM_PWE_PMD	0x4 	/* befowe widget powew down */
  #define SND_SOC_DAPM_POST_PMD	0x8		/* aftew widget powew down */
  #define SND_SOC_DAPM_PWE_WEG	0x10	/* befowe audio path setup */
  #define SND_SOC_DAPM_POST_WEG	0x20	/* aftew audio path setup */
