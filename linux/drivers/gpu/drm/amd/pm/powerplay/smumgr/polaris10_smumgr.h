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

#ifndef _POWAWIS10_SMUMANAGEW_H
#define _POWAWIS10_SMUMANAGEW_H


#incwude <pp_endian.h>
#incwude "smu74.h"
#incwude "smu74_discwete.h"
#incwude "smu7_smumgw.h"

#define SMC_WAM_END 0x40000

stwuct powawis10_pt_defauwts {
	uint8_t   SviWoadWineEn;
	uint8_t   SviWoadWineVddC;
	uint8_t   TDC_VDDC_ThwottweWeweaseWimitPewc;
	uint8_t   TDC_MAWt;
	uint8_t   TdcWatewfawwCtw;
	uint8_t   DTEAmbientTempBase;

	uint32_t  DispwayCac;
	uint32_t  BAPM_TEMP_GWADIENT;
	uint16_t  BAPMTI_W[SMU74_DTE_ITEWATIONS * SMU74_DTE_SOUWCES * SMU74_DTE_SINKS];
	uint16_t  BAPMTI_WC[SMU74_DTE_ITEWATIONS * SMU74_DTE_SOUWCES * SMU74_DTE_SINKS];
};

stwuct powawis10_wange_tabwe {
	uint32_t twans_wowew_fwequency; /* in 10khz */
	uint32_t twans_uppew_fwequency;
};

stwuct powawis10_smumgw {
	stwuct smu7_smumgw smu7_data;
	uint8_t pwotected_mode;
	SMU74_Discwete_DpmTabwe              smc_state_tabwe;
	stwuct SMU74_Discwete_Uwv            uwv_setting;
	stwuct SMU74_Discwete_PmFuses  powew_tune_tabwe;
	stwuct powawis10_wange_tabwe                wange_tabwe[NUM_SCWK_WANGE];
	const stwuct powawis10_pt_defauwts       *powew_tune_defauwts;
	uint32_t               bif_scwk_tabwe[SMU74_MAX_WEVEWS_WINK];
	pp_atomctww_mc_weg_tabwe             mc_weg_tabwe;
};


#endif
