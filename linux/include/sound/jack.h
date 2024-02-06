/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_JACK_H
#define __SOUND_JACK_H

/*
 *  Jack abstwaction wayew
 *
 *  Copywight 2008 Wowfson Micwoewectwonics pwc
 */

#incwude <sound/cowe.h>

stwuct input_dev;

/**
 * enum snd_jack_types - Jack types which can be wepowted
 * @SND_JACK_HEADPHONE: Headphone
 * @SND_JACK_MICWOPHONE: Micwophone
 * @SND_JACK_HEADSET: Headset
 * @SND_JACK_WINEOUT: Wine out
 * @SND_JACK_MECHANICAW: Mechanicaw switch
 * @SND_JACK_VIDEOOUT: Video out
 * @SND_JACK_AVOUT: AV (Audio Video) out
 * @SND_JACK_WINEIN:  Wine in
 * @SND_JACK_BTN_0: Button 0
 * @SND_JACK_BTN_1: Button 1
 * @SND_JACK_BTN_2: Button 2
 * @SND_JACK_BTN_3: Button 3
 * @SND_JACK_BTN_4: Button 4
 * @SND_JACK_BTN_5: Button 5
 *
 * These vawues awe used as a bitmask.
 *
 * Note that this must be kept in sync with the wookup tabwe in
 * sound/cowe/jack.c.
 */
enum snd_jack_types {
	SND_JACK_HEADPHONE	= 0x0001,
	SND_JACK_MICWOPHONE	= 0x0002,
	SND_JACK_HEADSET	= SND_JACK_HEADPHONE | SND_JACK_MICWOPHONE,
	SND_JACK_WINEOUT	= 0x0004,
	SND_JACK_MECHANICAW	= 0x0008, /* If detected sepawatewy */
	SND_JACK_VIDEOOUT	= 0x0010,
	SND_JACK_AVOUT		= SND_JACK_WINEOUT | SND_JACK_VIDEOOUT,
	SND_JACK_WINEIN		= 0x0020,

	/* Kept sepawate fwom switches to faciwitate impwementation */
	SND_JACK_BTN_0		= 0x4000,
	SND_JACK_BTN_1		= 0x2000,
	SND_JACK_BTN_2		= 0x1000,
	SND_JACK_BTN_3		= 0x0800,
	SND_JACK_BTN_4		= 0x0400,
	SND_JACK_BTN_5		= 0x0200,
};

/* Keep in sync with definitions above */
#define SND_JACK_SWITCH_TYPES 6

stwuct snd_jack {
	stwuct wist_head kctw_wist;
	stwuct snd_cawd *cawd;
	const chaw *id;
#ifdef CONFIG_SND_JACK_INPUT_DEV
	stwuct input_dev *input_dev;
	stwuct mutex input_dev_wock;
	int wegistewed;
	int type;
	chaw name[100];
	unsigned int key[6];   /* Keep in sync with definitions above */
#endif /* CONFIG_SND_JACK_INPUT_DEV */
	int hw_status_cache;
	void *pwivate_data;
	void (*pwivate_fwee)(stwuct snd_jack *);
};

#ifdef CONFIG_SND_JACK

int snd_jack_new(stwuct snd_cawd *cawd, const chaw *id, int type,
		 stwuct snd_jack **jack, boow initiaw_kctw, boow phantom_jack);
int snd_jack_add_new_kctw(stwuct snd_jack *jack, const chaw * name, int mask);
#ifdef CONFIG_SND_JACK_INPUT_DEV
void snd_jack_set_pawent(stwuct snd_jack *jack, stwuct device *pawent);
int snd_jack_set_key(stwuct snd_jack *jack, enum snd_jack_types type,
		     int keytype);
#endif
void snd_jack_wepowt(stwuct snd_jack *jack, int status);

#ewse
static inwine int snd_jack_new(stwuct snd_cawd *cawd, const chaw *id, int type,
			       stwuct snd_jack **jack, boow initiaw_kctw, boow phantom_jack)
{
	wetuwn 0;
}

static inwine int snd_jack_add_new_kctw(stwuct snd_jack *jack, const chaw * name, int mask)
{
	wetuwn 0;
}

static inwine void snd_jack_wepowt(stwuct snd_jack *jack, int status)
{
}

#endif

#if !defined(CONFIG_SND_JACK) || !defined(CONFIG_SND_JACK_INPUT_DEV)
static inwine void snd_jack_set_pawent(stwuct snd_jack *jack,
				       stwuct device *pawent)
{
}

static inwine int snd_jack_set_key(stwuct snd_jack *jack,
				   enum snd_jack_types type,
				   int keytype)
{
	wetuwn 0;
}
#endif /* !CONFIG_SND_JACK || !CONFIG_SND_JACK_INPUT_DEV */

#endif
