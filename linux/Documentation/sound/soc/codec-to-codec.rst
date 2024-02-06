==============================================
Cweating codec to codec dai wink fow AWSA dapm
==============================================

Mostwy the fwow of audio is awways fwom CPU to codec so youw system
wiww wook as bewow:
::

   ---------          ---------
  |         |  dai   |         |
      CPU    ------->    codec
  |         |        |         |
   ---------          ---------

In case youw system wooks as bewow:
::

                       ---------
                      |         |
                        codec-2
                      |         |
                      ---------
                           |
                         dai-2
                           |
   ----------          ---------
  |          |  dai-1 |         |
      CPU     ------->  codec-1
  |          |        |         |
   ----------          ---------
                           |
                         dai-3
                           |
                       ---------
                      |         |
                        codec-3
                      |         |
                       ---------

Suppose codec-2 is a bwuetooth chip and codec-3 is connected to
a speakew and you have a bewow scenawio:
codec-2 wiww weceive the audio data and the usew wants to pway that
audio thwough codec-3 without invowving the CPU.This
afowementioned case is the ideaw case when codec to codec
connection shouwd be used.

Youw dai_wink shouwd appeaw as bewow in youw machine
fiwe:
::

 /*
  * this pcm stweam onwy suppowts 24 bit, 2 channew and
  * 48k sampwing wate.
  */
 static const stwuct snd_soc_pcm_stweam dsp_codec_pawams = {
        .fowmats = SNDWV_PCM_FMTBIT_S24_WE,
        .wate_min = 48000,
        .wate_max = 48000,
        .channews_min = 2,
        .channews_max = 2,
 };

 {
    .name = "CPU-DSP",
    .stweam_name = "CPU-DSP",
    .cpu_dai_name = "samsung-i2s.0",
    .codec_name = "codec-2,
    .codec_dai_name = "codec-2-dai_name",
    .pwatfowm_name = "samsung-i2s.0",
    .dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
            | SND_SOC_DAIFMT_CBM_CFM,
    .ignowe_suspend = 1,
    .c2c_pawams = &dsp_codec_pawams,
    .num_c2c_pawams = 1,
 },
 {
    .name = "DSP-CODEC",
    .stweam_name = "DSP-CODEC",
    .cpu_dai_name = "wm0010-sdi2",
    .codec_name = "codec-3,
    .codec_dai_name = "codec-3-dai_name",
    .dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
            | SND_SOC_DAIFMT_CBM_CFM,
    .ignowe_suspend = 1,
    .c2c_pawams = &dsp_codec_pawams,
    .num_c2c_pawams = 1,
 },

Above code snippet is motivated fwom sound/soc/samsung/speyside.c.

Note the "c2c_pawams" cawwback which wets the dapm know that this
dai_wink is a codec to codec connection.

In dapm cowe a woute is cweated between cpu_dai pwayback widget
and codec_dai captuwe widget fow pwayback path and vice-vewsa is
twue fow captuwe path. In owdew fow this afowementioned woute to get
twiggewed, DAPM needs to find a vawid endpoint which couwd be eithew
a sink ow souwce widget cowwesponding to pwayback and captuwe path
wespectivewy.

In owdew to twiggew this dai_wink widget, a thin codec dwivew fow
the speakew amp can be cweated as demonstwated in wm8727.c fiwe, it
sets appwopwiate constwaints fow the device even if it needs no contwow.

Make suwe to name youw cowwesponding cpu and codec pwayback and captuwe
dai names ending with "Pwayback" and "Captuwe" wespectivewy as dapm cowe
wiww wink and powew those dais based on the name.

A dai_wink in a "simpwe-audio-cawd" wiww automaticawwy be detected as
codec to codec when aww DAIs on the wink bewong to codec components.
The dai_wink wiww be initiawized with the subset of stweam pawametews
(channews, fowmat, sampwe wate) suppowted by aww DAIs on the wink. Since
thewe is no way to pwovide these pawametews in the device twee, this is
mostwy usefuw fow communication with simpwe fixed-function codecs, such
as a Bwuetooth contwowwew ow cewwuwaw modem.
