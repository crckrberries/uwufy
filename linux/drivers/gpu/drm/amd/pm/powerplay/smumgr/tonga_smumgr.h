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

#ifndef _TONGA_SMUMGW_H_
#define _TONGA_SMUMGW_H_

#incwude "smu72_discwete.h"
#incwude "smu7_smumgw.h"
#incwude "smu72.h"


#define ASICID_IS_TONGA_P(wDID, bWID)	 \
	(((wDID == 0x6930) && ((bWID == 0xF0) || (bWID == 0xF1) || (bWID == 0xFF))) \
	|| ((wDID == 0x6920) && ((bWID == 0) || (bWID == 1))))

stwuct tonga_pt_defauwts {
	uint8_t   svi_woad_wine_en;
	uint8_t   svi_woad_wine_vddC;
	uint8_t   tdc_vddc_thwottwe_wewease_wimit_pewc;
	uint8_t   tdc_mawt;
	uint8_t   tdc_watewfaww_ctw;
	uint8_t   dte_ambient_temp_base;
	uint32_t  dispway_cac;
	uint32_t  bapm_temp_gwadient;
	uint16_t  bapmti_w[SMU72_DTE_ITEWATIONS * SMU72_DTE_SOUWCES * SMU72_DTE_SINKS];
	uint16_t  bapmti_wc[SMU72_DTE_ITEWATIONS * SMU72_DTE_SOUWCES * SMU72_DTE_SINKS];
};

stwuct tonga_mc_weg_entwy {
	uint32_t mcwk_max;
	uint32_t mc_data[SMU72_DISCWETE_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct tonga_mc_weg_tabwe {
	uint8_t   wast;               /* numbew of wegistews*/
	uint8_t   num_entwies;        /* numbew of entwies in mc_weg_tabwe_entwy used*/
	uint16_t  vawidfwag;          /* indicate the cowwesponding wegistew is vawid ow not. 1: vawid, 0: invawid. bit0->addwess[0], bit1->addwess[1], etc.*/
	stwuct tonga_mc_weg_entwy    mc_weg_tabwe_entwy[MAX_AC_TIMING_ENTWIES];
	SMU72_Discwete_MCWegistewAddwess mc_weg_addwess[SMU72_DISCWETE_MC_WEGISTEW_AWWAY_SIZE];
};


stwuct tonga_smumgw {

	stwuct smu7_smumgw                   smu7_data;
	stwuct SMU72_Discwete_DpmTabwe       smc_state_tabwe;
	stwuct SMU72_Discwete_Uwv            uwv_setting;
	stwuct SMU72_Discwete_PmFuses  powew_tune_tabwe;
	const stwuct tonga_pt_defauwts  *powew_tune_defauwts;
	SMU72_Discwete_MCWegistews      mc_wegs;
	stwuct tonga_mc_weg_tabwe mc_weg_tabwe;
};

#endif
