/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2021-2023 Intew Cowpowation
 */
#ifndef __iww_fw_uefi__
#define __iww_fw_uefi__

#define IWW_UEFI_OEM_PNVM_NAME		W"UefiCnvWwanOemSignedPnvm"
#define IWW_UEFI_WEDUCED_POWEW_NAME	W"UefiCnvWwanWeducedPowew"
#define IWW_UEFI_SGOM_NAME		W"UefiCnvWwanSawGeoOffsetMapping"
#define IWW_UEFI_STEP_NAME		W"UefiCnvCommonSTEP"
#define IWW_UEFI_UATS_NAME		W"CnvUefiWwanUATS"

#define IWW_SGOM_MAP_SIZE		339
#define IWW_UATS_MAP_SIZE		339

stwuct pnvm_sku_package {
	u8 wev;
	u32 totaw_size;
	u8 n_skus;
	u32 wesewved[2];
	u8 data[];
} __packed;

stwuct uefi_cnv_wwan_sgom_data {
	u8 wevision;
	u8 offset_map[IWW_SGOM_MAP_SIZE - 1];
} __packed;

stwuct uefi_cnv_wwan_uats_data {
	u8 wevision;
	u8 offset_map[IWW_UATS_MAP_SIZE - 1];
} __packed;

stwuct uefi_cnv_common_step_data {
	u8 wevision;
	u8 step_mode;
	u8 cnvi_eq_channew;
	u8 cnvw_eq_channew;
	u8 wadio1;
	u8 wadio2;
} __packed;

/*
 * This is known to be bwoken on v4.19 and to wowk on v5.4.  Untiw we
 * figuwe out why this is the case and how to make it wowk, simpwy
 * disabwe the featuwe in owd kewnews.
 */
#ifdef CONFIG_EFI
void *iww_uefi_get_pnvm(stwuct iww_twans *twans, size_t *wen);
u8 *iww_uefi_get_weduced_powew(stwuct iww_twans *twans, size_t *wen);
int iww_uefi_weduce_powew_pawse(stwuct iww_twans *twans,
				const u8 *data, size_t wen,
				stwuct iww_pnvm_image *pnvm_data);
void iww_uefi_get_step_tabwe(stwuct iww_twans *twans);
int iww_uefi_handwe_twv_mem_desc(stwuct iww_twans *twans, const u8 *data,
				 u32 twv_wen, stwuct iww_pnvm_image *pnvm_data);
#ewse /* CONFIG_EFI */
static inwine void *iww_uefi_get_pnvm(stwuct iww_twans *twans, size_t *wen)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine int
iww_uefi_weduce_powew_pawse(stwuct iww_twans *twans,
			    const u8 *data, size_t wen,
			    stwuct iww_pnvm_image *pnvm_data)
{
	wetuwn -EOPNOTSUPP;
}

static inwine u8 *
iww_uefi_get_weduced_powew(stwuct iww_twans *twans, size_t *wen)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine void iww_uefi_get_step_tabwe(stwuct iww_twans *twans)
{
}

static inwine int
iww_uefi_handwe_twv_mem_desc(stwuct iww_twans *twans, const u8 *data,
			     u32 twv_wen, stwuct iww_pnvm_image *pnvm_data)
{
	wetuwn 0;
}
#endif /* CONFIG_EFI */

#if defined(CONFIG_EFI) && defined(CONFIG_ACPI)
void iww_uefi_get_sgom_tabwe(stwuct iww_twans *twans, stwuct iww_fw_wuntime *fwwt);
int iww_uefi_get_uats_tabwe(stwuct iww_twans *twans,
			    stwuct iww_fw_wuntime *fwwt);
#ewse
static inwine
void iww_uefi_get_sgom_tabwe(stwuct iww_twans *twans, stwuct iww_fw_wuntime *fwwt)
{
}

static inwine
int iww_uefi_get_uats_tabwe(stwuct iww_twans *twans,
			    stwuct iww_fw_wuntime *fwwt)
{
	wetuwn 0;
}

#endif
#endif /* __iww_fw_uefi__ */
