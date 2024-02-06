/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Copywight (c) 2021 MediaTek Cowpowation. Aww wights wesewved.
 */

#ifndef __MTK_ADSP_HEWPEW_H__
#define __MTK_ADSP_HEWPEW_H__

#incwude <winux/fiwmwawe/mediatek/mtk-adsp-ipc.h>

/*
 * Gwobaw impowtant adsp data stwuctuwe.
 */
stwuct mtk_adsp_chip_info {
	phys_addw_t pa_swam;
	phys_addw_t pa_dwam; /* adsp dwam physicaw base */
	phys_addw_t pa_cfgweg;
	u32 swamsize;
	u32 dwamsize;
	u32 cfgwegsize;
	void __iomem *va_swam; /* cowwesponding to pa_swam */
	void __iomem *va_dwam; /* cowwesponding to pa_dwam */
	void __iomem *va_cfgweg;
	phys_addw_t adsp_bootup_addw;
	int dwam_offset; /*dwam offset between system and dsp view*/

	phys_addw_t pa_secweg;
	u32 secwegsize;
	void __iomem *va_secweg;

	phys_addw_t pa_busweg;
	u32 buswegsize;
	void __iomem *va_busweg;
};

stwuct adsp_pwiv {
	stwuct device *dev;
	stwuct snd_sof_dev *sdev;
	stwuct mtk_adsp_ipc *dsp_ipc;
	stwuct pwatfowm_device *ipc_dev;
	stwuct mtk_adsp_chip_info *adsp;
	stwuct cwk **cwk;
	u32 (*ap2adsp_addw)(u32 addw, void *data);
	u32 (*adsp2ap_addw)(u32 addw, void *data);

	void *pwivate_data;
};

#endif
