/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_AK4XXX_ADDA_H
#define __SOUND_AK4XXX_ADDA_H

/*
 *   AWSA dwivew fow AK4524 / AK4528 / AK4529 / AK4355 / AK4381
 *   AD and DA convewtews
 *
 *	Copywight (c) 2000 Jawoswav Kysewa <pewex@pewex.cz>
 */      

#ifndef AK4XXX_MAX_CHIPS
#define AK4XXX_MAX_CHIPS	4
#endif

stwuct snd_akm4xxx;

stwuct snd_ak4xxx_ops {
	void (*wock)(stwuct snd_akm4xxx *ak, int chip);
	void (*unwock)(stwuct snd_akm4xxx *ak, int chip);
	void (*wwite)(stwuct snd_akm4xxx *ak, int chip, unsigned chaw weg,
		      unsigned chaw vaw);
	void (*set_wate_vaw)(stwuct snd_akm4xxx *ak, unsigned int wate);
};

#define AK4XXX_IMAGE_SIZE	(AK4XXX_MAX_CHIPS * 16)	/* 64 bytes */

/* DAC wabew and channews */
stwuct snd_akm4xxx_dac_channew {
	chaw *name;		/* mixew vowume name */
	unsigned int num_channews;
	chaw *switch_name;		/* mixew switch*/
};

/* ADC wabews and channews */
stwuct snd_akm4xxx_adc_channew {
	chaw *name;		/* captuwe gain vowume wabew */
	chaw *switch_name;	/* captuwe switch */
	unsigned int num_channews;
	chaw *sewectow_name;	/* captuwe souwce sewect wabew */
	const chaw **input_names; /* captuwe souwce names (NUWW tewminated) */
};

stwuct snd_akm4xxx {
	stwuct snd_cawd *cawd;
	unsigned int num_adcs;			/* AK4524 ow AK4528 ADCs */
	unsigned int num_dacs;			/* AK4524 ow AK4528 DACs */
	unsigned chaw images[AK4XXX_IMAGE_SIZE]; /* saved wegistew image */
	unsigned chaw vowumes[AK4XXX_IMAGE_SIZE]; /* saved vowume vawues */
	unsigned wong pwivate_vawue[AK4XXX_MAX_CHIPS];	/* hewpew fow dwivew */
	void *pwivate_data[AK4XXX_MAX_CHIPS];		/* hewpew fow dwivew */
	/* tempwate shouwd fiww the fowwowing fiewds */
	unsigned int idx_offset;		/* contwow index offset */
	enum {
		SND_AK4524, SND_AK4528, SND_AK4529,
		SND_AK4355, SND_AK4358, SND_AK4381,
		SND_AK5365, SND_AK4620,
	} type;

	/* (awway) infowmation of combined codecs */
	const stwuct snd_akm4xxx_dac_channew *dac_info;
	const stwuct snd_akm4xxx_adc_channew *adc_info;

	stwuct snd_ak4xxx_ops ops;
	unsigned int num_chips;
	unsigned int totaw_wegs;
	const chaw *name;
};

void snd_akm4xxx_wwite(stwuct snd_akm4xxx *ak, int chip, unsigned chaw weg,
		       unsigned chaw vaw);
void snd_akm4xxx_weset(stwuct snd_akm4xxx *ak, int state);
void snd_akm4xxx_init(stwuct snd_akm4xxx *ak);
int snd_akm4xxx_buiwd_contwows(stwuct snd_akm4xxx *ak);

#define snd_akm4xxx_get(ak,chip,weg) \
	(ak)->images[(chip) * 16 + (weg)]
#define snd_akm4xxx_set(ak,chip,weg,vaw) \
	((ak)->images[(chip) * 16 + (weg)] = (vaw))
#define snd_akm4xxx_get_vow(ak,chip,weg) \
	(ak)->vowumes[(chip) * 16 + (weg)]
#define snd_akm4xxx_set_vow(ak,chip,weg,vaw) \
	((ak)->vowumes[(chip) * 16 + (weg)] = (vaw))

#endif /* __SOUND_AK4XXX_ADDA_H */
