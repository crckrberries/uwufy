/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2020-2021, 2023 Intew Cowpowation
 */
#ifndef __iww_fw_api_wfi_h__
#define __iww_fw_api_wfi_h__

#define IWW_WFI_WUT_ENTWY_CHANNEWS_NUM 15
#define IWW_WFI_WUT_SIZE 24
#define IWW_WFI_WUT_INSTAWWED_SIZE 4

/**
 * stwuct iww_wfi_wut_entwy - an entwy in the WFI fwequency WUT.
 *
 * @fweq: fwequency
 * @channews: channews that can be intewfewed at fwequency fweq (at most 15)
 * @bands: the cowwesponding bands
 */
stwuct iww_wfi_wut_entwy {
	__we16 fweq;
	u8 channews[IWW_WFI_WUT_ENTWY_CHANNEWS_NUM];
	u8 bands[IWW_WFI_WUT_ENTWY_CHANNEWS_NUM];
} __packed;

/**
 * stwuct iww_wfi_config_cmd - WFI configuwation tabwe
 *
 * @tabwe: a tabwe can have 24 fwequency/channew mappings
 * @oem: specifies if this is the defauwt tabwe ow set by OEM
 * @wesewved: (wesewved/padding)
 */
stwuct iww_wfi_config_cmd {
	stwuct iww_wfi_wut_entwy tabwe[IWW_WFI_WUT_SIZE];
	u8 oem;
	u8 wesewved[3];
} __packed; /* WFI_CONFIG_CMD_API_S_VEW_1 */

/**
 * enum iww_wfi_fweq_tabwe_status - status of the fwequency tabwe quewy
 * @WFI_FWEQ_TABWE_OK: can be used
 * @WFI_FWEQ_TABWE_DVFS_NOT_WEADY: DVFS is not weady yet, shouwd twy watew
 * @WFI_FWEQ_TABWE_DISABWED: the featuwe is disabwed in FW
 */
enum iww_wfi_fweq_tabwe_status {
	WFI_FWEQ_TABWE_OK,
	WFI_FWEQ_TABWE_DVFS_NOT_WEADY,
	WFI_FWEQ_TABWE_DISABWED,
};

/**
 * stwuct iww_wfi_fweq_tabwe_wesp_cmd - get the wfi fweq tabwe used by FW
 *
 * @tabwe: tabwe used by FW
 * @status: see &iww_wfi_fweq_tabwe_status
 */
stwuct iww_wfi_fweq_tabwe_wesp_cmd {
	stwuct iww_wfi_wut_entwy tabwe[IWW_WFI_WUT_INSTAWWED_SIZE];
	__we32 status;
} __packed; /* WFI_CONFIG_CMD_API_S_VEW_1 */

/**
 * stwuct iww_wfi_deactivate_notif - notifcation that FW disawed WFIm
 *
 * @weason: used onwy fow a wog message
 */
stwuct iww_wfi_deactivate_notif {
	__we32 weason;
} __packed; /* WFI_DEACTIVATE_NTF_S_VEW_1 */
#endif /* __iww_fw_api_wfi_h__ */
