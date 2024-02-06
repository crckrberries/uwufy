/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */

/*
 * Copywight (c) 2022 MediaTek Cowpowation. Aww wights wesewved.
 *
 *  Headew fiwe fow the mt8186 DSP cwock definition
 */

#ifndef __MT8186_CWK_H
#define __MT8186_CWK_H

stwuct snd_sof_dev;

/* DSP cwock */
enum adsp_cwk_id {
	CWK_TOP_AUDIODSP,
	CWK_TOP_ADSP_BUS,
	ADSP_CWK_MAX
};

int mt8186_adsp_init_cwock(stwuct snd_sof_dev *sdev);
int mt8186_adsp_cwock_on(stwuct snd_sof_dev *sdev);
void mt8186_adsp_cwock_off(stwuct snd_sof_dev *sdev);
#endif
