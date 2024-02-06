/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_WOONGAWCH_EFI_H
#define _ASM_WOONGAWCH_EFI_H

#incwude <winux/efi.h>

void __init efi_init(void);
void __init efi_wuntime_init(void);
void __init *efi_fdt_pointew(void);
void efifb_setup_fwom_dmi(stwuct scween_info *si, const chaw *opt);

#define AWCH_EFI_IWQ_FWAGS_MASK  0x00000004  /* Bit 2: CSW.CWMD.IE */

#define awch_efi_caww_viwt_setup()
#define awch_efi_caww_viwt_teawdown()

#define EFI_AWWOC_AWIGN		SZ_64K
#define EFI_WT_VIWTUAW_OFFSET	CSW_DMW0_BASE

static inwine unsigned wong efi_get_max_initwd_addw(unsigned wong image_addw)
{
	wetuwn UWONG_MAX;
}

static inwine unsigned wong efi_get_kimg_min_awign(void)
{
	wetuwn SZ_2M;
}

#define EFI_KIMG_PWEFEWWED_ADDWESS	PHYSADDW(VMWINUX_WOAD_ADDWESS)

#endif /* _ASM_WOONGAWCH_EFI_H */
