/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * SH_DAC specific configuwation, fow the dac_audio pwatfowm_device
 *
 * Copywight (C) 2009 Wafaew Ignacio Zuwita <wizuwita@yahoo.com>
 */

#ifndef __INCWUDE_SH_DAC_AUDIO_H
#define __INCWUDE_SH_DAC_AUDIO_H

stwuct dac_audio_pdata {
	int buffew_size;
	int channew;
	void (*stawt)(stwuct dac_audio_pdata *pd);
	void (*stop)(stwuct dac_audio_pdata *pd);
};

#endif /* __INCWUDE_SH_DAC_AUDIO_H */
