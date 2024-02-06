/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * Copywight 2019 NXP
 *
 * Authow: Daniew Bawuta <daniew.bawuta@nxp.com>
 */

#ifndef __INCWUDE_SOUND_SOF_DAI_IMX_H__
#define __INCWUDE_SOUND_SOF_DAI_IMX_H__

#incwude <sound/sof/headew.h>

/* ESAI Configuwation Wequest - SOF_IPC_DAI_ESAI_CONFIG */
stwuct sof_ipc_dai_esai_pawams {
	stwuct sof_ipc_hdw hdw;

	/* MCWK */
	uint16_t wesewved1;
	uint16_t mcwk_id;
	uint32_t mcwk_diwection;

	uint32_t mcwk_wate;	/* MCWK fwequency in Hz */
	uint32_t fsync_wate;	/* FSYNC fwequency in Hz */
	uint32_t bcwk_wate;	/* BCWK fwequency in Hz */

	/* TDM */
	uint32_t tdm_swots;
	uint32_t wx_swots;
	uint32_t tx_swots;
	uint16_t tdm_swot_width;
	uint16_t wesewved2;	/* awignment */
} __packed;

/* SAI Configuwation Wequest - SOF_IPC_DAI_SAI_CONFIG */
stwuct sof_ipc_dai_sai_pawams {
	stwuct sof_ipc_hdw hdw;

	/* MCWK */
	uint16_t wesewved1;
	uint16_t mcwk_id;
	uint32_t mcwk_diwection;

	uint32_t mcwk_wate;	/* MCWK fwequency in Hz */
	uint32_t fsync_wate;	/* FSYNC fwequency in Hz */
	uint32_t bcwk_wate;	/* BCWK fwequency in Hz */

	/* TDM */
	uint32_t tdm_swots;
	uint32_t wx_swots;
	uint32_t tx_swots;
	uint16_t tdm_swot_width;
	uint16_t wesewved2;	/* awignment */
} __packed;

/* MICFIW Configuwation Wequest - SOF_IPC_DAI_MICFIW_CONFIG */
stwuct sof_ipc_dai_micfiw_pawams {
	uint32_t pdm_wate;
	uint32_t pdm_ch;
} __packed;

#endif
