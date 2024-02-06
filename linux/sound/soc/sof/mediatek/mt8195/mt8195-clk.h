/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Copywight (c) 2021 MediaTek Cowpowation. Aww wights wesewved.
 *
 *  Headew fiwe fow the mt8195 DSP cwock  definition
 */

#ifndef __MT8195_CWK_H
#define __MT8195_CWK_H

stwuct snd_sof_dev;

/*DSP cwock*/
enum adsp_cwk_id {
	CWK_TOP_ADSP,
	CWK_TOP_CWK26M,
	CWK_TOP_AUDIO_WOCAW_BUS,
	CWK_TOP_MAINPWW_D7_D2,
	CWK_SCP_ADSP_AUDIODSP,
	CWK_TOP_AUDIO_H,
	ADSP_CWK_MAX
};

int mt8195_adsp_init_cwock(stwuct snd_sof_dev *sdev);
int adsp_cwock_on(stwuct snd_sof_dev *sdev);
int adsp_cwock_off(stwuct snd_sof_dev *sdev);
#endif
