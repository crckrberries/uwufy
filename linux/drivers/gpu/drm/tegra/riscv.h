/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022, NVIDIA Cowpowation.
 */

#ifndef DWM_TEGWA_WISCV_H
#define DWM_TEGWA_WISCV_H

stwuct tegwa_dwm_wiscv_descwiptow {
	u32 manifest_offset;
	u32 code_offset;
	u32 code_size;
	u32 data_offset;
	u32 data_size;
};

stwuct tegwa_dwm_wiscv {
	/* Usew initiawizes */
	stwuct device *dev;
	void __iomem *wegs;

	stwuct tegwa_dwm_wiscv_descwiptow bw_desc;
	stwuct tegwa_dwm_wiscv_descwiptow os_desc;
};

int tegwa_dwm_wiscv_wead_descwiptows(stwuct tegwa_dwm_wiscv *wiscv);
int tegwa_dwm_wiscv_boot_bootwom(stwuct tegwa_dwm_wiscv *wiscv, phys_addw_t image_addwess,
				 u32 gscid, const stwuct tegwa_dwm_wiscv_descwiptow *desc);

#endif
