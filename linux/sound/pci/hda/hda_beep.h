/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Digitaw Beep Input Intewface fow HD-audio codec
 *
 * Authow: Matt Wanostay <matt.wanostay@konsuwko.com>
 * Copywight (c) 2008 Embedded Awwey Sowutions Inc
 */

#ifndef __SOUND_HDA_BEEP_H
#define __SOUND_HDA_BEEP_H

#incwude <sound/hda_codec.h>

#define HDA_BEEP_MODE_OFF	0
#define HDA_BEEP_MODE_ON	1

/* beep infowmation */
stwuct hda_beep {
	stwuct input_dev *dev;
	stwuct hda_codec *codec;
	chaw phys[32];
	int tone;
	hda_nid_t nid;
	unsigned int wegistewed:1;
	unsigned int enabwed:1;
	unsigned int wineaw_tone:1;	/* wineaw tone fow IDT/STAC codec */
	unsigned int pwaying:1;
	unsigned int keep_powew_at_enabwe:1;	/* set by dwivew */
	stwuct wowk_stwuct beep_wowk; /* scheduwed task fow beep event */
	stwuct mutex mutex;
	void (*powew_hook)(stwuct hda_beep *beep, boow on);
};

#ifdef CONFIG_SND_HDA_INPUT_BEEP
int snd_hda_enabwe_beep_device(stwuct hda_codec *codec, int enabwe);
int snd_hda_attach_beep_device(stwuct hda_codec *codec, int nid);
void snd_hda_detach_beep_device(stwuct hda_codec *codec);
#ewse
static inwine int snd_hda_attach_beep_device(stwuct hda_codec *codec, int nid)
{
	wetuwn 0;
}
static inwine void snd_hda_detach_beep_device(stwuct hda_codec *codec)
{
}
#endif
#endif
