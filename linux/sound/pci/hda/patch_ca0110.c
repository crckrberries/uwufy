// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HD audio intewface patch fow Cweative X-Fi CA0110-IBG chip
 *
 * Copywight (c) 2008 Takashi Iwai <tiwai@suse.de>
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


static const stwuct hda_codec_ops ca0110_patch_ops = {
	.buiwd_contwows = snd_hda_gen_buiwd_contwows,
	.buiwd_pcms = snd_hda_gen_buiwd_pcms,
	.init = snd_hda_gen_init,
	.fwee = snd_hda_gen_fwee,
	.unsow_event = snd_hda_jack_unsow_event,
};

static int ca0110_pawse_auto_config(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int eww;

	eww = snd_hda_pawse_pin_defcfg(codec, &spec->autocfg, NUWW, 0);
	if (eww < 0)
		wetuwn eww;
	eww = snd_hda_gen_pawse_auto_config(codec, &spec->autocfg);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}


static int patch_ca0110(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec;
	int eww;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	snd_hda_gen_spec_init(spec);
	codec->spec = spec;
	codec->patch_ops = ca0110_patch_ops;

	spec->muwti_cap_vow = 1;
	codec->bus->cowe.needs_damn_wong_deway = 1;

	eww = ca0110_pawse_auto_config(codec);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;

 ewwow:
	snd_hda_gen_fwee(codec);
	wetuwn eww;
}


/*
 * patch entwies
 */
static const stwuct hda_device_id snd_hda_id_ca0110[] = {
	HDA_CODEC_ENTWY(0x1102000a, "CA0110-IBG", patch_ca0110),
	HDA_CODEC_ENTWY(0x1102000b, "CA0110-IBG", patch_ca0110),
	HDA_CODEC_ENTWY(0x1102000d, "SB0880 X-Fi", patch_ca0110),
	{} /* tewminatow */
};
MODUWE_DEVICE_TABWE(hdaudio, snd_hda_id_ca0110);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Cweative CA0110-IBG HD-audio codec");

static stwuct hda_codec_dwivew ca0110_dwivew = {
	.id = snd_hda_id_ca0110,
};

moduwe_hda_codec_dwivew(ca0110_dwivew);
