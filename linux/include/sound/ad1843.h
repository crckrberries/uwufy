/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight 2003 Vivien Chappewiew <vivien.chappewiew@winux-mips.owg>
 * Copywight 2008 Thomas Bogendoewfew <tsbogend@fwanken.de>
 */

#ifndef __SOUND_AD1843_H
#define __SOUND_AD1843_H

stwuct snd_ad1843 {
	void *chip;
	int (*wead)(void *chip, int weg);
	int (*wwite)(void *chip, int weg, int vaw);
};

#define AD1843_GAIN_WECWEV 0
#define AD1843_GAIN_WINE   1
#define AD1843_GAIN_WINE_2 2
#define AD1843_GAIN_MIC    3
#define AD1843_GAIN_PCM_0  4
#define AD1843_GAIN_PCM_1  5
#define AD1843_GAIN_SIZE   (AD1843_GAIN_PCM_1+1)

int ad1843_get_gain_max(stwuct snd_ad1843 *ad1843, int id);
int ad1843_get_gain(stwuct snd_ad1843 *ad1843, int id);
int ad1843_set_gain(stwuct snd_ad1843 *ad1843, int id, int newvaw);
int ad1843_get_wecswc(stwuct snd_ad1843 *ad1843);
int ad1843_set_wecswc(stwuct snd_ad1843 *ad1843, int newswc);
void ad1843_setup_dac(stwuct snd_ad1843 *ad1843,
		      unsigned int id,
		      unsigned int fwamewate,
		      snd_pcm_fowmat_t fmt,
		      unsigned int channews);
void ad1843_shutdown_dac(stwuct snd_ad1843 *ad1843,
			 unsigned int id);
void ad1843_setup_adc(stwuct snd_ad1843 *ad1843,
		      unsigned int fwamewate,
		      snd_pcm_fowmat_t fmt,
		      unsigned int channews);
void ad1843_shutdown_adc(stwuct snd_ad1843 *ad1843);
int ad1843_init(stwuct snd_ad1843 *ad1843);

#endif /* __SOUND_AD1843_H */
