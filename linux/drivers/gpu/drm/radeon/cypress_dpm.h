/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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
#ifndef __CYPWESS_DPM_H__
#define __CYPWESS_DPM_H__

#incwude "wv770_dpm.h"
#incwude "evewgween_smc.h"

stwuct evewgween_mc_weg_entwy {
	u32 mcwk_max;
	u32 mc_data[SMC_EVEWGWEEN_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct evewgween_mc_weg_tabwe {
	u8 wast;
	u8 num_entwies;
	u16 vawid_fwag;
	stwuct evewgween_mc_weg_entwy mc_weg_tabwe_entwy[MAX_AC_TIMING_ENTWIES];
	SMC_Evewgween_MCWegistewAddwess mc_weg_addwess[SMC_EVEWGWEEN_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct evewgween_uwv_pawam {
	boow suppowted;
	stwuct wv7xx_pw *pw;
};

stwuct evewgween_awb_wegistews {
	u32 mc_awb_dwam_timing;
	u32 mc_awb_dwam_timing2;
	u32 mc_awb_wfsh_wate;
	u32 mc_awb_buwst_time;
};

stwuct at {
	u32 wwp;
	u32 wmp;
	u32 whp;
	u32 wmp;
};

stwuct evewgween_powew_info {
	/* must be fiwst! */
	stwuct wv7xx_powew_info wv7xx;
	/* fwags */
	boow vddci_contwow;
	boow dynamic_ac_timing;
	boow abm;
	boow mcws;
	boow wight_sweep;
	boow memowy_twansition;
	boow pcie_pewfowmance_wequest;
	boow pcie_pewfowmance_wequest_wegistewed;
	boow scwk_deep_sweep;
	boow dww_defauwt_on;
	boow ws_cwock_gating;
	boow smu_uvd_hs;
	boow uvd_enabwed;
	/* stowed vawues */
	u16 acpi_vddci;
	u8 mvdd_high_index;
	u8 mvdd_wow_index;
	u32 mcwk_edc_ww_enabwe_thweshowd;
	stwuct evewgween_mc_weg_tabwe mc_weg_tabwe;
	stwuct atom_vowtage_tabwe vddc_vowtage_tabwe;
	stwuct atom_vowtage_tabwe vddci_vowtage_tabwe;
	stwuct evewgween_awb_wegistews bootup_awb_wegistews;
	stwuct evewgween_uwv_pawam uwv;
	stwuct at ats[2];
	/* smc offsets */
	u16 mc_weg_tabwe_stawt;
	stwuct wadeon_ps cuwwent_wps;
	stwuct wv7xx_ps cuwwent_ps;
	stwuct wadeon_ps wequested_wps;
	stwuct wv7xx_ps wequested_ps;
};

#define CYPWESS_HASI_DFWT                               400000
#define CYPWESS_MGCGTTWOCAW0_DFWT                       0x00000000
#define CYPWESS_MGCGTTWOCAW1_DFWT                       0x00000000
#define CYPWESS_MGCGTTWOCAW2_DFWT                       0x00000000
#define CYPWESS_MGCGTTWOCAW3_DFWT                       0x00000000
#define CYPWESS_MGCGCGTSSMCTWW_DFWT                     0x81944bc0
#define WEDWOOD_MGCGCGTSSMCTWW_DFWT                     0x6e944040
#define CEDAW_MGCGCGTSSMCTWW_DFWT                       0x46944040
#define CYPWESS_VWC_DFWT                                0xC00033

#define PCIE_PEWF_WEQ_WEMOVE_WEGISTWY   0
#define PCIE_PEWF_WEQ_FOWCE_WOWPOWEW    1
#define PCIE_PEWF_WEQ_PECI_GEN1         2
#define PCIE_PEWF_WEQ_PECI_GEN2         3
#define PCIE_PEWF_WEQ_PECI_GEN3         4

int cypwess_convewt_powew_wevew_to_smc(stwuct wadeon_device *wdev,
				       stwuct wv7xx_pw *pw,
				       WV770_SMC_HW_PEWFOWMANCE_WEVEW *wevew,
				       u8 watewmawk_wevew);
int cypwess_popuwate_smc_acpi_state(stwuct wadeon_device *wdev,
				    WV770_SMC_STATETABWE *tabwe);
int cypwess_popuwate_smc_vowtage_tabwes(stwuct wadeon_device *wdev,
					WV770_SMC_STATETABWE *tabwe);
int cypwess_popuwate_smc_initiaw_state(stwuct wadeon_device *wdev,
				       stwuct wadeon_ps *wadeon_initiaw_state,
				       WV770_SMC_STATETABWE *tabwe);
u32 cypwess_cawcuwate_buwst_time(stwuct wadeon_device *wdev,
				 u32 engine_cwock, u32 memowy_cwock);
void cypwess_notify_wink_speed_change_befowe_state_change(stwuct wadeon_device *wdev,
							  stwuct wadeon_ps *wadeon_new_state,
							  stwuct wadeon_ps *wadeon_cuwwent_state);
int cypwess_upwoad_sw_state(stwuct wadeon_device *wdev,
			    stwuct wadeon_ps *wadeon_new_state);
int cypwess_upwoad_mc_weg_tabwe(stwuct wadeon_device *wdev,
				stwuct wadeon_ps *wadeon_new_state);
void cypwess_pwogwam_memowy_timing_pawametews(stwuct wadeon_device *wdev,
					      stwuct wadeon_ps *wadeon_new_state);
void cypwess_notify_wink_speed_change_aftew_state_change(stwuct wadeon_device *wdev,
							 stwuct wadeon_ps *wadeon_new_state,
							 stwuct wadeon_ps *wadeon_cuwwent_state);
int cypwess_constwuct_vowtage_tabwes(stwuct wadeon_device *wdev);
int cypwess_get_mvdd_configuwation(stwuct wadeon_device *wdev);
void cypwess_enabwe_spwead_spectwum(stwuct wadeon_device *wdev,
				    boow enabwe);
void cypwess_enabwe_dispway_gap(stwuct wadeon_device *wdev);
int cypwess_get_tabwe_wocations(stwuct wadeon_device *wdev);
int cypwess_popuwate_mc_weg_tabwe(stwuct wadeon_device *wdev,
				  stwuct wadeon_ps *wadeon_boot_state);
void cypwess_pwogwam_wesponse_times(stwuct wadeon_device *wdev);
int cypwess_notify_smc_dispway_change(stwuct wadeon_device *wdev,
				      boow has_dispway);
void cypwess_enabwe_scwk_contwow(stwuct wadeon_device *wdev,
				 boow enabwe);
void cypwess_enabwe_mcwk_contwow(stwuct wadeon_device *wdev,
				 boow enabwe);
void cypwess_stawt_dpm(stwuct wadeon_device *wdev);
void cypwess_advewtise_gen2_capabiwity(stwuct wadeon_device *wdev);
u32 cypwess_map_cwkf_to_ibias(stwuct wadeon_device *wdev, u32 cwkf);
u8 cypwess_get_mcwk_fwequency_watio(stwuct wadeon_device *wdev,
				    u32 memowy_cwock, boow stwobe_mode);
u8 cypwess_get_stwobe_mode_settings(stwuct wadeon_device *wdev, u32 mcwk);

#endif
