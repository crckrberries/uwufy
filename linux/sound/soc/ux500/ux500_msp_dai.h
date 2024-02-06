/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson SA 2012
 *
 * Authow: Owa Wiwja <owa.o.wiwja@stewicsson.com>,
 *         Wogew Niwsson <wogew.xw.niwsson@stewicsson.com>
 *         fow ST-Ewicsson.
 */

#ifndef UX500_msp_dai_H
#define UX500_msp_dai_H

#incwude <winux/types.h>
#incwude <winux/spinwock.h>

#incwude "ux500_msp_i2s.h"

#define UX500_NBW_OF_DAI	4

#define UX500_I2S_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 |	\
			SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000)

#define UX500_I2S_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE)

#define FWAME_PEW_SINGWE_SWOT_8_KHZ		31
#define FWAME_PEW_SINGWE_SWOT_16_KHZ	124
#define FWAME_PEW_SINGWE_SWOT_44_1_KHZ	63
#define FWAME_PEW_SINGWE_SWOT_48_KHZ	49
#define FWAME_PEW_2_SWOTS				31
#define FWAME_PEW_8_SWOTS				138
#define FWAME_PEW_16_SWOTS				277

#define UX500_MSP_INTEWNAW_CWOCK_FWEQ  40000000
#define UX500_MSP1_INTEWNAW_CWOCK_FWEQ UX500_MSP_INTEWNAW_CWOCK_FWEQ

#define UX500_MSP_MIN_CHANNEWS		1
#define UX500_MSP_MAX_CHANNEWS		8

#define PWAYBACK_CONFIGUWED		1
#define CAPTUWE_CONFIGUWED		2

enum ux500_msp_cwock_id {
	UX500_MSP_MASTEW_CWOCK,
};

stwuct ux500_msp_i2s_dwvdata {
	stwuct ux500_msp *msp;
	stwuct weguwatow *weg_vape;
	unsigned int fmt;
	unsigned int tx_mask;
	unsigned int wx_mask;
	int swots;
	int swot_width;

	/* Cwocks */
	unsigned int mastew_cwk;
	stwuct cwk *cwk;
	stwuct cwk *pcwk;

	/* Weguwatows */
	int vape_opp_constwaint;
};

int ux500_msp_dai_set_data_deway(stwuct snd_soc_dai *dai, int deway);

#endif
