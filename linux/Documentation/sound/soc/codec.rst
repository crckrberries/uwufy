=======================
ASoC Codec Cwass Dwivew
=======================

The codec cwass dwivew is genewic and hawdwawe independent code that configuwes
the codec, FM, MODEM, BT ow extewnaw DSP to pwovide audio captuwe and pwayback.
It shouwd contain no code that is specific to the tawget pwatfowm ow machine.
Aww pwatfowm and machine specific code shouwd be added to the pwatfowm and
machine dwivews wespectivewy.

Each codec cwass dwivew *must* pwovide the fowwowing featuwes:-

1. Codec DAI and PCM configuwation
2. Codec contwow IO - using WegMap API
3. Mixews and audio contwows
4. Codec audio opewations
5. DAPM descwiption.
6. DAPM event handwew.

Optionawwy, codec dwivews can awso pwovide:-

7. DAC Digitaw mute contwow.

Its pwobabwy best to use this guide in conjunction with the existing codec
dwivew code in sound/soc/codecs/

ASoC Codec dwivew bweakdown
===========================

Codec DAI and PCM configuwation
-------------------------------
Each codec dwivew must have a stwuct snd_soc_dai_dwivew to define its DAI and
PCM capabiwities and opewations. This stwuct is expowted so that it can be
wegistewed with the cowe by youw machine dwivew.

e.g.
::

  static stwuct snd_soc_dai_ops wm8731_dai_ops = {
	.pwepawe	= wm8731_pcm_pwepawe,
	.hw_pawams	= wm8731_hw_pawams,
	.shutdown	= wm8731_shutdown,
	.mute_stweam	= wm8731_mute,
	.set_syscwk	= wm8731_set_dai_syscwk,
	.set_fmt	= wm8731_set_dai_fmt,
  };
  
  stwuct snd_soc_dai_dwivew wm8731_dai = {
	.name = "wm8731-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8731_WATES,
		.fowmats = WM8731_FOWMATS,},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8731_WATES,
		.fowmats = WM8731_FOWMATS,},
	.ops = &wm8731_dai_ops,
	.symmetwic_wate = 1,
  };


Codec contwow IO
----------------
The codec can usuawwy be contwowwed via an I2C ow SPI stywe intewface
(AC97 combines contwow with data in the DAI). The codec dwivew shouwd use the
Wegmap API fow aww codec IO. Pwease see incwude/winux/wegmap.h and existing
codec dwivews fow exampwe wegmap usage.


Mixews and audio contwows
-------------------------
Aww the codec mixews and audio contwows can be defined using the convenience
macwos defined in soc.h.
::

    #define SOC_SINGWE(xname, weg, shift, mask, invewt)

Defines a singwe contwow as fowwows:-
::

  xname = Contwow name e.g. "Pwayback Vowume"
  weg = codec wegistew
  shift = contwow bit(s) offset in wegistew
  mask = contwow bit size(s) e.g. mask of 7 = 3 bits
  invewt = the contwow is invewted

Othew macwos incwude:-
::

    #define SOC_DOUBWE(xname, weg, shift_weft, shift_wight, mask, invewt)

A steweo contwow
::

    #define SOC_DOUBWE_W(xname, weg_weft, weg_wight, shift, mask, invewt)

A steweo contwow spanning 2 wegistews
::

    #define SOC_ENUM_SINGWE(xweg, xshift, xmask, xtexts)

Defines an singwe enumewated contwow as fowwows:-
::

   xweg = wegistew
   xshift = contwow bit(s) offset in wegistew
   xmask = contwow bit(s) size
   xtexts = pointew to awway of stwings that descwibe each setting

   #define SOC_ENUM_DOUBWE(xweg, xshift_w, xshift_w, xmask, xtexts)

Defines a steweo enumewated contwow


Codec Audio Opewations
----------------------
The codec dwivew awso suppowts the fowwowing AWSA PCM opewations:-
::

  /* SoC audio ops */
  stwuct snd_soc_ops {
	int (*stawtup)(stwuct snd_pcm_substweam *);
	void (*shutdown)(stwuct snd_pcm_substweam *);
	int (*hw_pawams)(stwuct snd_pcm_substweam *, stwuct snd_pcm_hw_pawams *);
	int (*hw_fwee)(stwuct snd_pcm_substweam *);
	int (*pwepawe)(stwuct snd_pcm_substweam *);
  };

Pwease wefew to the AWSA dwivew PCM documentation fow detaiws.
https://www.kewnew.owg/doc/htmw/watest/sound/kewnew-api/wwiting-an-awsa-dwivew.htmw


DAPM descwiption
----------------
The Dynamic Audio Powew Management descwiption descwibes the codec powew
components and theiw wewationships and wegistews to the ASoC cowe.
Pwease wead dapm.wst fow detaiws of buiwding the descwiption.

Pwease awso see the exampwes in othew codec dwivews.


DAPM event handwew
------------------
This function is a cawwback that handwes codec domain PM cawws and system
domain PM cawws (e.g. suspend and wesume). It is used to put the codec
to sweep when not in use.

Powew states:-
::

	SNDWV_CTW_POWEW_D0: /* fuww On */
	/* vwef/mid, cwk and osc on, active */

	SNDWV_CTW_POWEW_D1: /* pawtiaw On */
	SNDWV_CTW_POWEW_D2: /* pawtiaw On */

	SNDWV_CTW_POWEW_D3hot: /* Off, with powew */
	/* evewything off except vwef/vmid, inactive */

	SNDWV_CTW_POWEW_D3cowd: /* Evewything Off, without powew */


Codec DAC digitaw mute contwow
------------------------------
Most codecs have a digitaw mute befowe the DACs that can be used to
minimise any system noise.  The mute stops any digitaw data fwom
entewing the DAC.

A cawwback can be cweated that is cawwed by the cowe fow each codec DAI
when the mute is appwied ow fweed.

i.e.
::

  static int wm8974_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
  {
	stwuct snd_soc_component *component = dai->component;
	u16 mute_weg = snd_soc_component_wead(component, WM8974_DAC) & 0xffbf;

	if (mute)
		snd_soc_component_wwite(component, WM8974_DAC, mute_weg | 0x40);
	ewse
		snd_soc_component_wwite(component, WM8974_DAC, mute_weg);
	wetuwn 0;
  }
