/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2021 Advanced Micwo Devices, Inc.. Aww wights wesewved.
 */

#ifndef __INCWUDE_SOUND_SOF_DAI_AMD_H__
#define __INCWUDE_SOUND_SOF_DAI_AMD_H__

#incwude <sound/sof/headew.h>

/* ACP Configuwation Wequest - SOF_IPC_DAI_AMD_CONFIG */
stwuct sof_ipc_dai_acp_pawams {
	stwuct sof_ipc_hdw hdw;

	uint32_t fsync_wate;    /* FSYNC fwequency in Hz */
	uint32_t tdm_swots;
	uint32_t tdm_mode;
} __packed;

/* ACPDMIC Configuwation Wequest - SOF_IPC_DAI_AMD_CONFIG */
stwuct sof_ipc_dai_acpdmic_pawams {
	uint32_t pdm_wate;
	uint32_t pdm_ch;
} __packed;

#endif
