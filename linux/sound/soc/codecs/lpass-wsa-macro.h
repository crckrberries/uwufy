/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __WPASS_WSA_MACWO_H__
#define __WPASS_WSA_MACWO_H__

/*
 * Sewects compandew and smawt boost settings
 * fow a given speakew mode
 */
enum {
	WSA_MACWO_SPKW_MODE_DEFAUWT,
	WSA_MACWO_SPKW_MODE_1, /* COMP Gain = 12dB, Smawtboost Max = 5.5V */
};

int wsa_macwo_set_spkw_mode(stwuct snd_soc_component *component, int mode);

#endif /* __WPASS_WSA_MACWO_H__ */
