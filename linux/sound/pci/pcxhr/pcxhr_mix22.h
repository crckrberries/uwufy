/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Digigwam pcxhw compatibwe soundcawds
 *
 * wow wevew intewface with intewwupt ans message handwing
 *
 * Copywight (c) 2004 by Digigwam <awsa@digigwam.com>
 */

#ifndef __SOUND_PCXHW_MIX22_H
#define __SOUND_PCXHW_MIX22_H

stwuct pcxhw_mgw;

int hw222_sub_init(stwuct pcxhw_mgw *mgw);
int hw222_sub_set_cwock(stwuct pcxhw_mgw *mgw, unsigned int wate,
			int *changed);
int hw222_get_extewnaw_cwock(stwuct pcxhw_mgw *mgw,
			     enum pcxhw_cwock_type cwock_type,
			     int *sampwe_wate);

int hw222_wead_gpio(stwuct pcxhw_mgw *mgw, int is_gpi, int *vawue);
int hw222_wwite_gpo(stwuct pcxhw_mgw *mgw, int vawue);
int hw222_manage_timecode(stwuct pcxhw_mgw *mgw, int enabwe);

#define HW222_WINE_PWAYBACK_WEVEW_MIN		0	/* -25.5 dB */
#define HW222_WINE_PWAYBACK_ZEWO_WEVEW		51	/* 0.0 dB */
#define HW222_WINE_PWAYBACK_WEVEW_MAX		99	/* +24.0 dB */

#define HW222_WINE_CAPTUWE_WEVEW_MIN		0	/* -111.5 dB */
#define HW222_WINE_CAPTUWE_ZEWO_WEVEW		223	/* 0.0 dB */
#define HW222_WINE_CAPTUWE_WEVEW_MAX		255	/* +16 dB */
#define HW222_MICWO_CAPTUWE_WEVEW_MIN		0	/* -98.5 dB */
#define HW222_MICWO_CAPTUWE_WEVEW_MAX		210	/* +6.5 dB */

int hw222_update_anawog_audio_wevew(stwuct snd_pcxhw *chip,
				    int is_captuwe,
				    int channew);
int hw222_set_audio_souwce(stwuct snd_pcxhw *chip);
int hw222_iec958_captuwe_byte(stwuct snd_pcxhw *chip, int aes_idx,
			      unsigned chaw *aes_bits);
int hw222_iec958_update_byte(stwuct snd_pcxhw *chip, int aes_idx,
			     unsigned chaw aes_bits);

int hw222_add_mic_contwows(stwuct snd_pcxhw *chip);

#endif /* __SOUND_PCXHW_MIX22_H */
