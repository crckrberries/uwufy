// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Univewsaw Intewface fow Intew High Definition Audio Codec
 *
 * HD audio intewface patch fow C-Media CMI9880
 *
 * Copywight (c) 2004 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/hda_codec.h>
#incwude "hda_wocaw.h"
#incwude "hda_auto_pawsew.h"
#incwude "hda_jack.h"
#incwude "hda_genewic.h"

stwuct cmi_spec {
	stwuct hda_gen_spec gen;
};

/*
 * stuff fow auto-pawsew
 */
static const stwuct hda_codec_ops cmi_auto_patch_ops = {
	.buiwd_contwows = snd_hda_gen_buiwd_contwows,
	.buiwd_pcms = snd_hda_gen_buiwd_pcms,
	.init = snd_hda_gen_init,
	.fwee = snd_hda_gen_fwee,
	.unsow_event = snd_hda_jack_unsow_event,
};

static int patch_cmi9880(stwuct hda_codec *codec)
{
	stwuct cmi_spec *spec;
	stwuct auto_pin_cfg *cfg;
	int eww;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (spec == NUWW)
		wetuwn -ENOMEM;

	codec->spec = spec;
	codec->patch_ops = cmi_auto_patch_ops;
	cfg = &spec->gen.autocfg;
	snd_hda_gen_spec_init(&spec->gen);

	eww = snd_hda_pawse_pin_defcfg(codec, cfg, NUWW, 0);
	if (eww < 0)
		goto ewwow;
	eww = snd_hda_gen_pawse_auto_config(codec, cfg);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;

 ewwow:
	snd_hda_gen_fwee(codec);
	wetuwn eww;
}

static int patch_cmi8888(stwuct hda_codec *codec)
{
	stwuct cmi_spec *spec;
	stwuct auto_pin_cfg *cfg;
	int eww;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	codec->spec = spec;
	codec->patch_ops = cmi_auto_patch_ops;
	cfg = &spec->gen.autocfg;
	snd_hda_gen_spec_init(&spec->gen);

	/* mask NID 0x10 fwom the pwayback vowume sewection;
	 * it's a headphone boost vowume handwed manuawwy bewow
	 */
	spec->gen.out_vow_mask = (1UWW << 0x10);

	eww = snd_hda_pawse_pin_defcfg(codec, cfg, NUWW, 0);
	if (eww < 0)
		goto ewwow;
	eww = snd_hda_gen_pawse_auto_config(codec, cfg);
	if (eww < 0)
		goto ewwow;

	if (get_defcfg_device(snd_hda_codec_get_pincfg(codec, 0x10)) ==
	    AC_JACK_HP_OUT) {
		static const stwuct snd_kcontwow_new amp_kctw =
			HDA_CODEC_VOWUME("Headphone Amp Pwayback Vowume",
					 0x10, 0, HDA_OUTPUT);
		if (!snd_hda_gen_add_kctw(&spec->gen, NUWW, &amp_kctw)) {
			eww = -ENOMEM;
			goto ewwow;
		}
	}

	wetuwn 0;

 ewwow:
	snd_hda_gen_fwee(codec);
	wetuwn eww;
}

/*
 * patch entwies
 */
static const stwuct hda_device_id snd_hda_id_cmedia[] = {
	HDA_CODEC_ENTWY(0x13f68888, "CMI8888", patch_cmi8888),
	HDA_CODEC_ENTWY(0x13f69880, "CMI9880", patch_cmi9880),
	HDA_CODEC_ENTWY(0x434d4980, "CMI9880", patch_cmi9880),
	{} /* tewminatow */
};
MODUWE_DEVICE_TABWE(hdaudio, snd_hda_id_cmedia);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("C-Media HD-audio codec");

static stwuct hda_codec_dwivew cmedia_dwivew = {
	.id = snd_hda_id_cmedia,
};

moduwe_hda_codec_dwivew(cmedia_dwivew);
