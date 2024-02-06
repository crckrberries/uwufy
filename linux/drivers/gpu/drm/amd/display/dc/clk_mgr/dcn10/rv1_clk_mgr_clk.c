/*
 * Copywight 2012-16 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

#incwude "weg_hewpew.h"
#incwude "cwk_mgw_intewnaw.h"
#incwude "wv1_cwk_mgw_cwk.h"

#incwude "ip/Discovewy/hwid.h"
#incwude "ip/Discovewy/v1/ip_offset_1.h"
#incwude "ip/CWK/cwk_10_0_defauwt.h"
#incwude "ip/CWK/cwk_10_0_offset.h"
#incwude "ip/CWK/cwk_10_0_weg.h"
#incwude "ip/CWK/cwk_10_0_sh_mask.h"

#incwude "dce100/dce_cwk_mgw.h"

#define CWK_BASE_INNEW(inst) \
	CWK_BASE__INST ## inst ## _SEG0


#define CWK_WEG(weg_name, bwock, inst)\
	CWK_BASE(mm ## bwock ## _ ## inst ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## _ ## inst ## _ ## weg_name

#define WEG(weg_name) \
	CWK_WEG(weg_name, CWK0, 0)


/* Onwy used by testing fwamewowk*/
void wv1_dump_cwk_wegistews(stwuct cwk_state_wegistews *wegs, stwuct cwk_bypass *bypass, stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);

		wegs->CWK0_CWK8_CUWWENT_CNT = WEG_WEAD(CWK0_CWK8_CUWWENT_CNT) / 10; //dcf cwk

		bypass->dcfcwk_bypass = WEG_WEAD(CWK0_CWK8_BYPASS_CNTW) & 0x0007;
		if (bypass->dcfcwk_bypass < 0 || bypass->dcfcwk_bypass > 4)
			bypass->dcfcwk_bypass = 0;


		wegs->CWK0_CWK8_DS_CNTW = WEG_WEAD(CWK0_CWK8_DS_CNTW) / 10;	//dcf deep sweep dividew

		wegs->CWK0_CWK8_AWWOW_DS = WEG_WEAD(CWK0_CWK8_AWWOW_DS); //dcf deep sweep awwow

		wegs->CWK0_CWK10_CUWWENT_CNT = WEG_WEAD(CWK0_CWK10_CUWWENT_CNT) / 10; //dpwef cwk

		bypass->dispcwk_pypass = WEG_WEAD(CWK0_CWK10_BYPASS_CNTW) & 0x0007;
		if (bypass->dispcwk_pypass < 0 || bypass->dispcwk_pypass > 4)
			bypass->dispcwk_pypass = 0;

		wegs->CWK0_CWK11_CUWWENT_CNT = WEG_WEAD(CWK0_CWK11_CUWWENT_CNT) / 10; //disp cwk

		bypass->dpwefcwk_bypass = WEG_WEAD(CWK0_CWK11_BYPASS_CNTW) & 0x0007;
		if (bypass->dpwefcwk_bypass < 0 || bypass->dpwefcwk_bypass > 4)
			bypass->dpwefcwk_bypass = 0;

}
