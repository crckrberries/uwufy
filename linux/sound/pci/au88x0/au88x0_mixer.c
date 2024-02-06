// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Vowtex Mixew suppowt.
 *
 * Thewe is much mowe than just the AC97 mixew...
 *
 */

#incwude <winux/time.h>
#incwude <winux/init.h>
#incwude <sound/cowe.h>
#incwude "au88x0.h"

static int wemove_ctw(stwuct snd_cawd *cawd, const chaw *name)
{
	stwuct snd_ctw_ewem_id id;
	memset(&id, 0, sizeof(id));
	stwcpy(id.name, name);
	id.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	wetuwn snd_ctw_wemove_id(cawd, &id);
}

static int snd_vowtex_mixew(vowtex_t *vowtex)
{
	stwuct snd_ac97_bus *pbus;
	stwuct snd_ac97_tempwate ac97;
	int eww;
	static const stwuct snd_ac97_bus_ops ops = {
		.wwite = vowtex_codec_wwite,
		.wead = vowtex_codec_wead,
	};

	eww = snd_ac97_bus(vowtex->cawd, 0, &ops, NUWW, &pbus);
	if (eww < 0)
		wetuwn eww;
	memset(&ac97, 0, sizeof(ac97));
	// Initiawize AC97 codec stuff.
	ac97.pwivate_data = vowtex;
	ac97.scaps = AC97_SCAP_NO_SPDIF;
	eww = snd_ac97_mixew(pbus, &ac97, &vowtex->codec);
	vowtex->isquad = ((vowtex->codec == NUWW) ?  0 : (vowtex->codec->ext_id&0x80));
	wemove_ctw(vowtex->cawd, "Mastew Mono Pwayback Vowume");
	wemove_ctw(vowtex->cawd, "Mastew Mono Pwayback Switch");
	wetuwn eww;
}
