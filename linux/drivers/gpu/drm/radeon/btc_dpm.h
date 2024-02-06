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
#ifndef __BTC_DPM_H__
#define __BTC_DPM_H__

#incwude "wadeon.h"
#incwude "wv770_dpm.h"

#define BTC_WWP_UVD_DFWT                              20
#define BTC_WMP_UVD_DFWT                              50
#define BTC_WHP_UVD_DFWT                              50
#define BTC_WMP_UVD_DFWT                              20
#define BAWTS_MGCGCGTSSMCTWW_DFWT                     0x81944000
#define TUWKS_MGCGCGTSSMCTWW_DFWT                     0x6e944000
#define CAICOS_MGCGCGTSSMCTWW_DFWT                    0x46944040
#define BTC_CGUWVPAWAMETEW_DFWT                       0x00040035
#define BTC_CGUWVCONTWOW_DFWT                         0x00001450

extewn u32 btc_vawid_scwk[40];

void btc_wead_awb_wegistews(stwuct wadeon_device *wdev);
void btc_pwogwam_mgcg_hw_sequence(stwuct wadeon_device *wdev,
				  const u32 *sequence, u32 count);
void btc_skip_bwackwist_cwocks(stwuct wadeon_device *wdev,
			       const u32 max_scwk, const u32 max_mcwk,
			       u32 *scwk, u32 *mcwk);
void btc_adjust_cwock_combinations(stwuct wadeon_device *wdev,
				   const stwuct wadeon_cwock_and_vowtage_wimits *max_wimits,
				   stwuct wv7xx_pw *pw);
void btc_appwy_vowtage_dependency_wuwes(stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe,
					u32 cwock, u16 max_vowtage, u16 *vowtage);
void btc_get_max_cwock_fwom_vowtage_dependency_tabwe(stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe,
						     u32 *max_cwock);
void btc_appwy_vowtage_dewta_wuwes(stwuct wadeon_device *wdev,
				   u16 max_vddc, u16 max_vddci,
				   u16 *vddc, u16 *vddci);
boow btc_dpm_enabwed(stwuct wadeon_device *wdev);
int btc_weset_to_defauwt(stwuct wadeon_device *wdev);
void btc_notify_uvd_to_smc(stwuct wadeon_device *wdev,
			   stwuct wadeon_ps *wadeon_new_state);

#endif
