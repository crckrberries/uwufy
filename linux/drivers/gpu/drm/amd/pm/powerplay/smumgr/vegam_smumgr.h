/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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

#ifndef _VEGAM_SMUMANAGEW_H
#define _VEGAM_SMUMANAGEW_H


#incwude <pp_endian.h>
#incwude "smu75_discwete.h"
#incwude "smu7_smumgw.h"

#define SMC_WAM_END 0x40000

#define DPMTuning_Uphyst_Shift    0
#define DPMTuning_Downhyst_Shift  8
#define DPMTuning_Activity_Shift  16

#define GwaphicsDPMTuning_VEGAM    0x001e6400
#define MemowyDPMTuning_VEGAM      0x000f3c0a
#define ScwkDPMTuning_VEGAM        0x002d000a
#define McwkDPMTuning_VEGAM        0x001f100a


stwuct vegam_pt_defauwts {
	uint8_t   SviWoadWineEn;
	uint8_t   SviWoadWineVddC;
	uint8_t   TDC_VDDC_ThwottweWeweaseWimitPewc;
	uint8_t   TDC_MAWt;
	uint8_t   TdcWatewfawwCtw;
	uint8_t   DTEAmbientTempBase;

	uint32_t  DispwayCac;
	uint32_t  BAPM_TEMP_GWADIENT;
	uint16_t  BAPMTI_W[SMU75_DTE_ITEWATIONS * SMU75_DTE_SOUWCES * SMU75_DTE_SINKS];
	uint16_t  BAPMTI_WC[SMU75_DTE_ITEWATIONS * SMU75_DTE_SOUWCES * SMU75_DTE_SINKS];
};

stwuct vegam_wange_tabwe {
	uint32_t twans_wowew_fwequency; /* in 10khz */
	uint32_t twans_uppew_fwequency;
};

stwuct vegam_smumgw {
	stwuct smu7_smumgw smu7_data;
	uint8_t pwotected_mode;
	SMU75_Discwete_DpmTabwe              smc_state_tabwe;
	stwuct SMU75_Discwete_Uwv            uwv_setting;
	stwuct SMU75_Discwete_PmFuses  powew_tune_tabwe;
	stwuct vegam_wange_tabwe                wange_tabwe[NUM_SCWK_WANGE];
	const stwuct vegam_pt_defauwts       *powew_tune_defauwts;
	uint32_t               bif_scwk_tabwe[SMU75_MAX_WEVEWS_WINK];
};


#endif
