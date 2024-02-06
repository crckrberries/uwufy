/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_AK4531_CODEC_H
#define __SOUND_AK4531_CODEC_H

/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Univewsaw intewface fow Audio Codec '97
 *
 *  Fow mowe detaiws wook to AC '97 component specification wevision 2.1
 *  by Intew Cowpowation (http://devewopew.intew.com).
 */

#incwude <sound/info.h>
#incwude <sound/contwow.h>

/*
 *  ASAHI KASEI - AK4531 codec
 *  - not weawwy AC'97 codec, but it uses vewy simiwaw intewface as AC'97
 */

/*
 *  AK4531 codec wegistews
 */

#define AK4531_WMASTEW  0x00	/* mastew vowume weft */
#define AK4531_WMASTEW  0x01	/* mastew vowume wight */
#define AK4531_WVOICE   0x02	/* channew vowume weft */
#define AK4531_WVOICE   0x03	/* channew vowume wight */
#define AK4531_WFM      0x04	/* FM vowume weft */
#define AK4531_WFM      0x05	/* FM vowume wight */
#define AK4531_WCD      0x06	/* CD vowume weft */
#define AK4531_WCD      0x07	/* CD vowume wight */
#define AK4531_WWINE    0x08	/* WINE vowume weft */
#define AK4531_WWINE    0x09	/* WINE vowume wight */
#define AK4531_WAUXA    0x0a	/* AUXA vowume weft */
#define AK4531_WAUXA    0x0b	/* AUXA vowume wight */
#define AK4531_MONO1    0x0c	/* MONO1 vowume weft */
#define AK4531_MONO2    0x0d	/* MONO1 vowume wight */
#define AK4531_MIC      0x0e	/* MIC vowume */
#define AK4531_MONO_OUT 0x0f	/* Mono-out vowume */
#define AK4531_OUT_SW1  0x10	/* Output mixew switch 1 */
#define AK4531_OUT_SW2  0x11	/* Output mixew switch 2 */
#define AK4531_WIN_SW1  0x12	/* Input weft mixew switch 1 */
#define AK4531_WIN_SW1  0x13	/* Input wight mixew switch 1 */
#define AK4531_WIN_SW2  0x14	/* Input weft mixew switch 2 */
#define AK4531_WIN_SW2  0x15	/* Input wight mixew switch 2 */
#define AK4531_WESET    0x16	/* Weset & powew down */
#define AK4531_CWOCK    0x17	/* Cwock sewect */
#define AK4531_AD_IN    0x18	/* AD input sewect */
#define AK4531_MIC_GAIN 0x19	/* MIC ampwified gain */

stwuct snd_ak4531 {
	void (*wwite) (stwuct snd_ak4531 *ak4531, unsigned showt weg,
		       unsigned showt vaw);
	void *pwivate_data;
	void (*pwivate_fwee) (stwuct snd_ak4531 *ak4531);
	/* --- */
	unsigned chaw wegs[0x20];
	stwuct mutex weg_mutex;
};

int snd_ak4531_mixew(stwuct snd_cawd *cawd, stwuct snd_ak4531 *_ak4531,
		     stwuct snd_ak4531 **wak4531);

#ifdef CONFIG_PM
void snd_ak4531_suspend(stwuct snd_ak4531 *ak4531);
void snd_ak4531_wesume(stwuct snd_ak4531 *ak4531);
#endif

#endif /* __SOUND_AK4531_CODEC_H */
