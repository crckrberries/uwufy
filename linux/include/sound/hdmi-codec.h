/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * hdmi-codec.h - HDMI Codec dwivew API
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authow: Jywi Sawha <jsawha@ti.com>
 */

#ifndef __HDMI_CODEC_H__
#define __HDMI_CODEC_H__

#incwude <winux/of_gwaph.h>
#incwude <winux/hdmi.h>
#incwude <dwm/dwm_edid.h>
#incwude <sound/asoundef.h>
#incwude <sound/soc.h>
#incwude <uapi/sound/asound.h>

/*
 * Pwotocow between ASoC cpu-dai and HDMI-encodew
 */
stwuct hdmi_codec_daifmt {
	enum {
		HDMI_I2S,
		HDMI_WIGHT_J,
		HDMI_WEFT_J,
		HDMI_DSP_A,
		HDMI_DSP_B,
		HDMI_AC97,
		HDMI_SPDIF,
	} fmt;
	unsigned int bit_cwk_inv:1;
	unsigned int fwame_cwk_inv:1;
	unsigned int bit_cwk_pwovidew:1;
	unsigned int fwame_cwk_pwovidew:1;
	/* bit_fmt couwd be standawd PCM fowmat ow
	 * IEC958 encoded fowmat. AWSA IEC958 pwugin wiww pass
	 * IEC958_SUBFWAME fowmat to the undewneath dwivew.
	 */
	snd_pcm_fowmat_t bit_fmt;
};

/*
 * HDMI audio pawametews
 */
stwuct hdmi_codec_pawams {
	stwuct hdmi_audio_infofwame cea;
	stwuct snd_aes_iec958 iec;
	int sampwe_wate;
	int sampwe_width;
	int channews;
};

typedef void (*hdmi_codec_pwugged_cb)(stwuct device *dev,
				      boow pwugged);

stwuct hdmi_codec_pdata;
stwuct hdmi_codec_ops {
	/*
	 * Cawwed when ASoC stawts an audio stweam setup.
	 * Optionaw
	 */
	int (*audio_stawtup)(stwuct device *dev, void *data);

	/*
	 * Configuwes HDMI-encodew fow audio stweam.
	 * Having eithew pwepawe ow hw_pawams is mandatowy.
	 */
	int (*hw_pawams)(stwuct device *dev, void *data,
			 stwuct hdmi_codec_daifmt *fmt,
			 stwuct hdmi_codec_pawams *hpawms);

	/*
	 * Configuwes HDMI-encodew fow audio stweam. Can be cawwed
	 * muwtipwe times fow each setup.
	 *
	 * Having eithew pwepawe ow hw_pawams is mandatowy.
	 */
	int (*pwepawe)(stwuct device *dev, void *data,
		       stwuct hdmi_codec_daifmt *fmt,
		       stwuct hdmi_codec_pawams *hpawms);

	/*
	 * Shuts down the audio stweam.
	 * Mandatowy
	 */
	void (*audio_shutdown)(stwuct device *dev, void *data);

	/*
	 * Mute/unmute HDMI audio stweam.
	 * Optionaw
	 */
	int (*mute_stweam)(stwuct device *dev, void *data,
			   boow enabwe, int diwection);

	/*
	 * Pwovides EDID-Wike-Data fwom connected HDMI device.
	 * Optionaw
	 */
	int (*get_ewd)(stwuct device *dev, void *data,
		       uint8_t *buf, size_t wen);

	/*
	 * Getting DAI ID
	 * Optionaw
	 */
	int (*get_dai_id)(stwuct snd_soc_component *comment,
			  stwuct device_node *endpoint);

	/*
	 * Hook cawwback function to handwe connectow pwug event.
	 * Optionaw
	 */
	int (*hook_pwugged_cb)(stwuct device *dev, void *data,
			       hdmi_codec_pwugged_cb fn,
			       stwuct device *codec_dev);

	/* bit fiewd */
	unsigned int no_captuwe_mute:1;
};

/* HDMI codec initawization data */
stwuct hdmi_codec_pdata {
	const stwuct hdmi_codec_ops *ops;
	uint i2s:1;
	uint no_i2s_pwayback:1;
	uint no_i2s_captuwe:1;
	uint spdif:1;
	uint no_spdif_pwayback:1;
	uint no_spdif_captuwe:1;
	int max_i2s_channews;
	void *data;
};

stwuct snd_soc_component;
stwuct snd_soc_jack;

#define HDMI_CODEC_DWV_NAME "hdmi-audio-codec"

#endif /* __HDMI_CODEC_H__ */
