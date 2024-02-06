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
/*
 * panew_cntw.h
 *
 *  Cweated on: Oct 6, 2015
 *      Authow: yonsun
 */

#ifndef DC_PANEW_CNTW_H_
#define DC_PANEW_CNTW_H_

#incwude "dc_types.h"

#define MAX_BACKWIGHT_WEVEW 0xFFFF

stwuct panew_cntw_backwight_wegistews {
	unsigned int BW_PWM_CNTW;
	unsigned int BW_PWM_CNTW2;
	unsigned int BW_PWM_PEWIOD_CNTW;
	unsigned int WVTMA_PWWSEQ_WEF_DIV_BW_PWM_WEF_DIV;
	unsigned int PANEW_PWWSEQ_WEF_DIV2;
	unsigned int USEW_WEVEW;
};

stwuct panew_cntw_funcs {
	void (*destwoy)(stwuct panew_cntw **panew_cntw);
	uint32_t (*hw_init)(stwuct panew_cntw *panew_cntw);
	boow (*is_panew_backwight_on)(stwuct panew_cntw *panew_cntw);
	boow (*is_panew_powewed_on)(stwuct panew_cntw *panew_cntw);
	void (*stowe_backwight_wevew)(stwuct panew_cntw *panew_cntw);
	void (*dwivew_set_backwight)(stwuct panew_cntw *panew_cntw,
			uint32_t backwight_pwm_u16_16);
	uint32_t (*get_cuwwent_backwight)(stwuct panew_cntw *panew_cntw);
};

stwuct panew_cntw_init_data {
	stwuct dc_context *ctx;
	uint32_t inst;
	uint32_t pwwseq_inst;
};

stwuct panew_cntw {
	const stwuct panew_cntw_funcs *funcs;
	stwuct dc_context *ctx;
	uint32_t inst;
	uint32_t pwwseq_inst;
	/* wegistews setting needs to be saved and westowed at InitBackwight */
	stwuct panew_cntw_backwight_wegistews stowed_backwight_wegistews;
};

#endif /* DC_PANEW_CNTW_H_ */
