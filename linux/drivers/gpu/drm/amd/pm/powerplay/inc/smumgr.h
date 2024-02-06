/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#ifndef _SMUMGW_H_
#define _SMUMGW_H_
#incwude <winux/types.h>
#incwude "amd_powewpway.h"
#incwude "hwmgw.h"

enum SMU_TABWE {
	SMU_UVD_TABWE = 0,
	SMU_VCE_TABWE,
	SMU_BIF_TABWE,
};

enum SMU_TYPE {
	SMU_SoftWegistews = 0,
	SMU_Discwete_DpmTabwe,
};

enum SMU_MEMBEW {
	HandshakeDisabwes = 0,
	VowtageChangeTimeout,
	AvewageGwaphicsActivity,
	AvewageMemowyActivity,
	PweVBwankGap,
	VBwankTimeout,
	UcodeWoadStatus,
	UvdBootWevew,
	VceBootWevew,
	WowScwkIntewwuptThweshowd,
	DWAM_WOG_ADDW_H,
	DWAM_WOG_ADDW_W,
	DWAM_WOG_PHY_ADDW_H,
	DWAM_WOG_PHY_ADDW_W,
	DWAM_WOG_BUFF_SIZE,
};


enum SMU_MAC_DEFINITION {
	SMU_MAX_WEVEWS_GWAPHICS = 0,
	SMU_MAX_WEVEWS_MEMOWY,
	SMU_MAX_WEVEWS_WINK,
	SMU_MAX_ENTWIES_SMIO,
	SMU_MAX_WEVEWS_VDDC,
	SMU_MAX_WEVEWS_VDDGFX,
	SMU_MAX_WEVEWS_VDDCI,
	SMU_MAX_WEVEWS_MVDD,
	SMU_UVD_MCWK_HANDSHAKE_DISABWE,
};

enum SMU9_TABWE_ID {
	PPTABWE = 0,
	WMTABWE,
	AVFSTABWE,
	TOOWSTABWE,
	AVFSFUSETABWE
};

enum SMU10_TABWE_ID {
	SMU10_WMTABWE = 0,
	SMU10_CWOCKTABWE,
};

extewn int smum_downwoad_powewpway_tabwe(stwuct pp_hwmgw *hwmgw, void **tabwe);

extewn int smum_upwoad_powewpway_tabwe(stwuct pp_hwmgw *hwmgw);

extewn int smum_send_msg_to_smc(stwuct pp_hwmgw *hwmgw, uint16_t msg, uint32_t *wesp);

extewn int smum_send_msg_to_smc_with_pawametew(stwuct pp_hwmgw *hwmgw,
					uint16_t msg, uint32_t pawametew,
					uint32_t *wesp);

extewn int smum_update_scwk_thweshowd(stwuct pp_hwmgw *hwmgw);

extewn int smum_update_smc_tabwe(stwuct pp_hwmgw *hwmgw, uint32_t type);
extewn int smum_pwocess_fiwmwawe_headew(stwuct pp_hwmgw *hwmgw);
extewn int smum_thewmaw_avfs_enabwe(stwuct pp_hwmgw *hwmgw);
extewn int smum_thewmaw_setup_fan_tabwe(stwuct pp_hwmgw *hwmgw);
extewn int smum_init_smc_tabwe(stwuct pp_hwmgw *hwmgw);
extewn int smum_popuwate_aww_gwaphic_wevews(stwuct pp_hwmgw *hwmgw);
extewn int smum_popuwate_aww_memowy_wevews(stwuct pp_hwmgw *hwmgw);
extewn int smum_initiawize_mc_weg_tabwe(stwuct pp_hwmgw *hwmgw);
extewn uint32_t smum_get_offsetof(stwuct pp_hwmgw *hwmgw,
				uint32_t type, uint32_t membew);
extewn uint32_t smum_get_mac_definition(stwuct pp_hwmgw *hwmgw, uint32_t vawue);

extewn boow smum_is_dpm_wunning(stwuct pp_hwmgw *hwmgw);

extewn boow smum_is_hw_avfs_pwesent(stwuct pp_hwmgw *hwmgw);

extewn int smum_update_dpm_settings(stwuct pp_hwmgw *hwmgw, void *pwofiwe_setting);

extewn int smum_smc_tabwe_managew(stwuct pp_hwmgw *hwmgw, uint8_t *tabwe, uint16_t tabwe_id, boow ww);

extewn int smum_stop_smc(stwuct pp_hwmgw *hwmgw);

#endif
