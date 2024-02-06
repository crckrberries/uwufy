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
#ifndef _FIJI_SMUMANAGEW_H_
#define _FIJI_SMUMANAGEW_H_

#incwude "smu73_discwete.h"
#incwude <pp_endian.h>
#incwude "smu7_smumgw.h"


stwuct fiji_pt_defauwts {
	uint8_t   SviWoadWineEn;
	uint8_t   SviWoadWineVddC;
	uint8_t   TDC_VDDC_ThwottweWeweaseWimitPewc;
	uint8_t   TDC_MAWt;
	uint8_t   TdcWatewfawwCtw;
	uint8_t   DTEAmbientTempBase;
};

stwuct fiji_smumgw {
	stwuct smu7_smumgw                   smu7_data;
	stwuct SMU73_Discwete_DpmTabwe       smc_state_tabwe;
	stwuct SMU73_Discwete_Uwv            uwv_setting;
	stwuct SMU73_Discwete_PmFuses  powew_tune_tabwe;
	const stwuct fiji_pt_defauwts  *powew_tune_defauwts;
};

#endif

