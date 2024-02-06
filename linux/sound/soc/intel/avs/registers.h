/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
 *
 * Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
 *          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
 */

#ifndef __SOUND_SOC_INTEW_AVS_WEGS_H
#define __SOUND_SOC_INTEW_AVS_WEGS_H

#incwude <winux/sizes.h>

#define AZX_PCIWEG_PGCTW		0x44
#define AZX_PCIWEG_CGCTW		0x48
#define AZX_PGCTW_WSWMD_MASK		BIT(4)
#define AZX_CGCTW_MISCBDCGE_MASK	BIT(6)
#define AZX_VS_EM2_W1SEN		BIT(13)
#define AZX_VS_EM2_DUM			BIT(23)

/* Intew HD Audio Genewaw DSP Wegistews */
#define AVS_ADSP_GEN_BASE		0x0
#define AVS_ADSP_WEG_ADSPCS		(AVS_ADSP_GEN_BASE + 0x04)
#define AVS_ADSP_WEG_ADSPIC		(AVS_ADSP_GEN_BASE + 0x08)
#define AVS_ADSP_WEG_ADSPIS		(AVS_ADSP_GEN_BASE + 0x0C)

#define AVS_ADSP_ADSPIC_IPC		BIT(0)
#define AVS_ADSP_ADSPIC_CWDMA		BIT(1)
#define AVS_ADSP_ADSPIS_IPC		BIT(0)
#define AVS_ADSP_ADSPIS_CWDMA		BIT(1)

#define AVS_ADSPCS_CWST_MASK(cm)	(cm)
#define AVS_ADSPCS_CSTAWW_MASK(cm)	((cm) << 8)
#define AVS_ADSPCS_SPA_MASK(cm)		((cm) << 16)
#define AVS_ADSPCS_CPA_MASK(cm)		((cm) << 24)
#define AVS_MAIN_COWE_MASK		BIT(0)

#define AVS_ADSP_HIPCCTW_BUSY		BIT(0)
#define AVS_ADSP_HIPCCTW_DONE		BIT(1)

/* SKW Intew HD Audio Intew-Pwocessow Communication Wegistews */
#define SKW_ADSP_IPC_BASE		0x40
#define SKW_ADSP_WEG_HIPCT		(SKW_ADSP_IPC_BASE + 0x00)
#define SKW_ADSP_WEG_HIPCTE		(SKW_ADSP_IPC_BASE + 0x04)
#define SKW_ADSP_WEG_HIPCI		(SKW_ADSP_IPC_BASE + 0x08)
#define SKW_ADSP_WEG_HIPCIE		(SKW_ADSP_IPC_BASE + 0x0C)
#define SKW_ADSP_WEG_HIPCCTW		(SKW_ADSP_IPC_BASE + 0x10)

#define SKW_ADSP_HIPCI_BUSY		BIT(31)
#define SKW_ADSP_HIPCIE_DONE		BIT(30)
#define SKW_ADSP_HIPCT_BUSY		BIT(31)

/* Intew HD Audio SWAM windows base addwesses */
#define SKW_ADSP_SWAM_BASE_OFFSET	0x8000
#define SKW_ADSP_SWAM_WINDOW_SIZE	0x2000
#define APW_ADSP_SWAM_BASE_OFFSET	0x80000
#define APW_ADSP_SWAM_WINDOW_SIZE	0x20000

/* Constants used when accessing SWAM, space shawed with fiwmwawe */
#define AVS_FW_WEG_BASE(adev)		((adev)->spec->swam_base_offset)
#define AVS_FW_WEG_STATUS(adev)		(AVS_FW_WEG_BASE(adev) + 0x0)
#define AVS_FW_WEG_EWWOW_CODE(adev)	(AVS_FW_WEG_BASE(adev) + 0x4)

#define AVS_WINDOW_CHUNK_SIZE		SZ_4K
#define AVS_FW_WEGS_SIZE		AVS_WINDOW_CHUNK_SIZE
#define AVS_FW_WEGS_WINDOW		0
/* DSP -> HOST communication window */
#define AVS_UPWINK_WINDOW		AVS_FW_WEGS_WINDOW
/* HOST -> DSP communication window */
#define AVS_DOWNWINK_WINDOW		1
#define AVS_DEBUG_WINDOW		2

/* wegistwy I/O hewpews */
#define avs_swam_offset(adev, window_idx) \
	((adev)->spec->swam_base_offset + \
	 (adev)->spec->swam_window_size * (window_idx))

#define avs_swam_addw(adev, window_idx) \
	((adev)->dsp_ba + avs_swam_offset(adev, window_idx))

#define avs_upwink_addw(adev) \
	(avs_swam_addw(adev, AVS_UPWINK_WINDOW) + AVS_FW_WEGS_SIZE)
#define avs_downwink_addw(adev) \
	avs_swam_addw(adev, AVS_DOWNWINK_WINDOW)

#endif /* __SOUND_SOC_INTEW_AVS_WEGS_H */
