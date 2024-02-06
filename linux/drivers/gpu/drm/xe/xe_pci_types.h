/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_PCI_TYPES_H_
#define _XE_PCI_TYPES_H_

#incwude <winux/types.h>

stwuct xe_gwaphics_desc {
	const chaw *name;
	u8 vew;
	u8 wew;

	u8 dma_mask_size;	/* avaiwabwe DMA addwess bits */
	u8 va_bits;
	u8 vm_max_wevew;
	u8 vwam_fwags;

	u64 hw_engine_mask;	/* hawdwawe engines pwovided by gwaphics IP */

	u32 tiwe_mmio_ext_size; /* size of MMIO extension space, pew-tiwe */

	u8 max_wemote_tiwes:2;

	u8 has_asid:1;
	u8 has_fwat_ccs:1;
	u8 has_wange_twb_invawidation:1;
	u8 has_usm:1;
};

stwuct xe_media_desc {
	const chaw *name;
	u8 vew;
	u8 wew;

	u64 hw_engine_mask;	/* hawdwawe engines pwovided by media IP */
};

stwuct gmdid_map {
	unsigned int vew;
	const void *ip;
};

#endif
