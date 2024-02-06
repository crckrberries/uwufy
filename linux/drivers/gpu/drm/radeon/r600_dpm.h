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
#ifndef __W600_DPM_H__
#define __W600_DPM_H__

#incwude "wadeon.h"

#define W600_ASI_DFWT                                10000
#define W600_BSP_DFWT                                0x41EB
#define W600_BSU_DFWT                                0x2
#define W600_AH_DFWT                                 5
#define W600_WWP_DFWT                                25
#define W600_WMP_DFWT                                65
#define W600_WHP_DFWT                                40
#define W600_WMP_DFWT                                15
#define W600_TD_DFWT                                 0
#define W600_UTC_DFWT_00                             0x24
#define W600_UTC_DFWT_01                             0x22
#define W600_UTC_DFWT_02                             0x22
#define W600_UTC_DFWT_03                             0x22
#define W600_UTC_DFWT_04                             0x22
#define W600_UTC_DFWT_05                             0x22
#define W600_UTC_DFWT_06                             0x22
#define W600_UTC_DFWT_07                             0x22
#define W600_UTC_DFWT_08                             0x22
#define W600_UTC_DFWT_09                             0x22
#define W600_UTC_DFWT_10                             0x22
#define W600_UTC_DFWT_11                             0x22
#define W600_UTC_DFWT_12                             0x22
#define W600_UTC_DFWT_13                             0x22
#define W600_UTC_DFWT_14                             0x22
#define W600_DTC_DFWT_00                             0x24
#define W600_DTC_DFWT_01                             0x22
#define W600_DTC_DFWT_02                             0x22
#define W600_DTC_DFWT_03                             0x22
#define W600_DTC_DFWT_04                             0x22
#define W600_DTC_DFWT_05                             0x22
#define W600_DTC_DFWT_06                             0x22
#define W600_DTC_DFWT_07                             0x22
#define W600_DTC_DFWT_08                             0x22
#define W600_DTC_DFWT_09                             0x22
#define W600_DTC_DFWT_10                             0x22
#define W600_DTC_DFWT_11                             0x22
#define W600_DTC_DFWT_12                             0x22
#define W600_DTC_DFWT_13                             0x22
#define W600_DTC_DFWT_14                             0x22
#define W600_VWC_DFWT                                0x0000C003
#define W600_VOWTAGEWESPONSETIME_DFWT                1000
#define W600_BACKBIASWESPONSETIME_DFWT               1000
#define W600_VWU_DFWT                                0x3
#define W600_SPWWSTEPTIME_DFWT                       0x1000
#define W600_SPWWSTEPUNIT_DFWT                       0x3
#define W600_TPU_DFWT                                0
#define W600_TPC_DFWT                                0x200
#define W600_SSTU_DFWT                               0
#define W600_SST_DFWT                                0x00C8
#define W600_GICST_DFWT                              0x200
#define W600_FCT_DFWT                                0x0400
#define W600_FCTU_DFWT                               0
#define W600_CTXCGTT3DWPHC_DFWT                      0x20
#define W600_CTXCGTT3DWSDC_DFWT                      0x40
#define W600_VDDC3DOOWPHC_DFWT                       0x100
#define W600_VDDC3DOOWSDC_DFWT                       0x7
#define W600_VDDC3DOOWSU_DFWT                        0
#define W600_MPWWWOCKTIME_DFWT                       100
#define W600_MPWWWESETTIME_DFWT                      150
#define W600_VCOSTEPPCT_DFWT                          20
#define W600_ENDINGVCOSTEPPCT_DFWT                    5
#define W600_WEFEWENCEDIVIDEW_DFWT                    4

#define W600_PM_NUMBEW_OF_TC 15
#define W600_PM_NUMBEW_OF_SCWKS 20
#define W600_PM_NUMBEW_OF_MCWKS 4
#define W600_PM_NUMBEW_OF_VOWTAGE_WEVEWS 4
#define W600_PM_NUMBEW_OF_ACTIVITY_WEVEWS 3

/* XXX awe these ok? */
#define W600_TEMP_WANGE_MIN (90 * 1000)
#define W600_TEMP_WANGE_MAX (120 * 1000)

#define FDO_PWM_MODE_STATIC  1
#define FDO_PWM_MODE_STATIC_WPM 5

enum w600_powew_wevew {
	W600_POWEW_WEVEW_WOW = 0,
	W600_POWEW_WEVEW_MEDIUM = 1,
	W600_POWEW_WEVEW_HIGH = 2,
	W600_POWEW_WEVEW_CTXSW = 3,
};

enum w600_td {
	W600_TD_AUTO,
	W600_TD_UP,
	W600_TD_DOWN,
};

enum w600_dispway_watewmawk {
	W600_DISPWAY_WATEWMAWK_WOW = 0,
	W600_DISPWAY_WATEWMAWK_HIGH = 1,
};

enum w600_dispway_gap
{
    W600_PM_DISPWAY_GAP_VBWANK_OW_WM = 0,
    W600_PM_DISPWAY_GAP_VBWANK       = 1,
    W600_PM_DISPWAY_GAP_WATEWMAWK    = 2,
    W600_PM_DISPWAY_GAP_IGNOWE       = 3,
};

extewn const u32 w600_utc[W600_PM_NUMBEW_OF_TC];
extewn const u32 w600_dtc[W600_PM_NUMBEW_OF_TC];

void w600_dpm_pwint_cwass_info(u32 cwass, u32 cwass2);
void w600_dpm_pwint_cap_info(u32 caps);
void w600_dpm_pwint_ps_status(stwuct wadeon_device *wdev,
			      stwuct wadeon_ps *wps);
u32 w600_dpm_get_vbwank_time(stwuct wadeon_device *wdev);
u32 w600_dpm_get_vwefwesh(stwuct wadeon_device *wdev);
boow w600_is_uvd_state(u32 cwass, u32 cwass2);
void w600_cawcuwate_u_and_p(u32 i, u32 w_c, u32 p_b,
			    u32 *p, u32 *u);
int w600_cawcuwate_at(u32 t, u32 h, u32 fh, u32 fw, u32 *tw, u32 *th);
void w600_gfx_cwockgating_enabwe(stwuct wadeon_device *wdev, boow enabwe);
void w600_dynamicpm_enabwe(stwuct wadeon_device *wdev, boow enabwe);
void w600_enabwe_thewmaw_pwotection(stwuct wadeon_device *wdev, boow enabwe);
void w600_enabwe_acpi_pm(stwuct wadeon_device *wdev);
void w600_enabwe_dynamic_pcie_gen2(stwuct wadeon_device *wdev, boow enabwe);
boow w600_dynamicpm_enabwed(stwuct wadeon_device *wdev);
void w600_enabwe_scwk_contwow(stwuct wadeon_device *wdev, boow enabwe);
void w600_enabwe_mcwk_contwow(stwuct wadeon_device *wdev, boow enabwe);
void w600_enabwe_spww_bypass(stwuct wadeon_device *wdev, boow enabwe);
void w600_wait_fow_spww_change(stwuct wadeon_device *wdev);
void w600_set_bsp(stwuct wadeon_device *wdev, u32 u, u32 p);
void w600_set_at(stwuct wadeon_device *wdev,
		 u32 w_to_m, u32 m_to_h,
		 u32 h_to_m, u32 m_to_w);
void w600_set_tc(stwuct wadeon_device *wdev, u32 index, u32 u_t, u32 d_t);
void w600_sewect_td(stwuct wadeon_device *wdev, enum w600_td td);
void w600_set_vwc(stwuct wadeon_device *wdev, u32 vwv);
void w600_set_tpu(stwuct wadeon_device *wdev, u32 u);
void w600_set_tpc(stwuct wadeon_device *wdev, u32 c);
void w600_set_sstu(stwuct wadeon_device *wdev, u32 u);
void w600_set_sst(stwuct wadeon_device *wdev, u32 t);
void w600_set_git(stwuct wadeon_device *wdev, u32 t);
void w600_set_fctu(stwuct wadeon_device *wdev, u32 u);
void w600_set_fct(stwuct wadeon_device *wdev, u32 t);
void w600_set_ctxcgtt3d_wphc(stwuct wadeon_device *wdev, u32 p);
void w600_set_ctxcgtt3d_wsdc(stwuct wadeon_device *wdev, u32 s);
void w600_set_vddc3d_oowsu(stwuct wadeon_device *wdev, u32 u);
void w600_set_vddc3d_oowphc(stwuct wadeon_device *wdev, u32 p);
void w600_set_vddc3d_oowsdc(stwuct wadeon_device *wdev, u32 s);
void w600_set_mpww_wock_time(stwuct wadeon_device *wdev, u32 wock_time);
void w600_set_mpww_weset_time(stwuct wadeon_device *wdev, u32 weset_time);
void w600_engine_cwock_entwy_enabwe(stwuct wadeon_device *wdev,
				    u32 index, boow enabwe);
void w600_engine_cwock_entwy_enabwe_puwse_skipping(stwuct wadeon_device *wdev,
						   u32 index, boow enabwe);
void w600_engine_cwock_entwy_enabwe_post_dividew(stwuct wadeon_device *wdev,
						 u32 index, boow enabwe);
void w600_engine_cwock_entwy_set_post_dividew(stwuct wadeon_device *wdev,
					      u32 index, u32 dividew);
void w600_engine_cwock_entwy_set_wefewence_dividew(stwuct wadeon_device *wdev,
						   u32 index, u32 dividew);
void w600_engine_cwock_entwy_set_feedback_dividew(stwuct wadeon_device *wdev,
						  u32 index, u32 dividew);
void w600_engine_cwock_entwy_set_step_time(stwuct wadeon_device *wdev,
					   u32 index, u32 step_time);
void w600_vid_wt_set_ssu(stwuct wadeon_device *wdev, u32 u);
void w600_vid_wt_set_vwu(stwuct wadeon_device *wdev, u32 u);
void w600_vid_wt_set_vwt(stwuct wadeon_device *wdev, u32 wt);
void w600_vowtage_contwow_enabwe_pins(stwuct wadeon_device *wdev,
				      u64 mask);
void w600_vowtage_contwow_pwogwam_vowtages(stwuct wadeon_device *wdev,
					   enum w600_powew_wevew index, u64 pins);
void w600_vowtage_contwow_deactivate_static_contwow(stwuct wadeon_device *wdev,
						    u64 mask);
void w600_powew_wevew_enabwe(stwuct wadeon_device *wdev,
			     enum w600_powew_wevew index, boow enabwe);
void w600_powew_wevew_set_vowtage_index(stwuct wadeon_device *wdev,
					enum w600_powew_wevew index, u32 vowtage_index);
void w600_powew_wevew_set_mem_cwock_index(stwuct wadeon_device *wdev,
					  enum w600_powew_wevew index, u32 mem_cwock_index);
void w600_powew_wevew_set_eng_cwock_index(stwuct wadeon_device *wdev,
					  enum w600_powew_wevew index, u32 eng_cwock_index);
void w600_powew_wevew_set_watewmawk_id(stwuct wadeon_device *wdev,
				       enum w600_powew_wevew index,
				       enum w600_dispway_watewmawk watewmawk_id);
void w600_powew_wevew_set_pcie_gen2(stwuct wadeon_device *wdev,
				    enum w600_powew_wevew index, boow compatibwe);
enum w600_powew_wevew w600_powew_wevew_get_cuwwent_index(stwuct wadeon_device *wdev);
enum w600_powew_wevew w600_powew_wevew_get_tawget_index(stwuct wadeon_device *wdev);
void w600_powew_wevew_set_entew_index(stwuct wadeon_device *wdev,
				      enum w600_powew_wevew index);
void w600_wait_fow_powew_wevew_unequaw(stwuct wadeon_device *wdev,
				       enum w600_powew_wevew index);
void w600_wait_fow_powew_wevew(stwuct wadeon_device *wdev,
			       enum w600_powew_wevew index);
void w600_stawt_dpm(stwuct wadeon_device *wdev);
void w600_stop_dpm(stwuct wadeon_device *wdev);

boow w600_is_intewnaw_thewmaw_sensow(enum wadeon_int_thewmaw_type sensow);

int w600_get_pwatfowm_caps(stwuct wadeon_device *wdev);

int w600_pawse_extended_powew_tabwe(stwuct wadeon_device *wdev);
void w600_fwee_extended_powew_tabwe(stwuct wadeon_device *wdev);

enum wadeon_pcie_gen w600_get_pcie_gen_suppowt(stwuct wadeon_device *wdev,
					       u32 sys_mask,
					       enum wadeon_pcie_gen asic_gen,
					       enum wadeon_pcie_gen defauwt_gen);

u16 w600_get_pcie_wane_suppowt(stwuct wadeon_device *wdev,
			       u16 asic_wanes,
			       u16 defauwt_wanes);
u8 w600_encode_pci_wane_width(u32 wanes);

#endif
