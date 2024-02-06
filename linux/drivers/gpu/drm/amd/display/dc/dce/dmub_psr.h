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

#ifndef _DMUB_PSW_H_
#define _DMUB_PSW_H_

#incwude "dc_types.h"
stwuct dc_wink;
stwuct dmub_psw_funcs;

stwuct dmub_psw {
	stwuct dc_context *ctx;
	const stwuct dmub_psw_funcs *funcs;
};

stwuct dmub_psw_funcs {
	boow (*psw_copy_settings)(stwuct dmub_psw *dmub, stwuct dc_wink *wink,
	stwuct psw_context *psw_context, uint8_t panew_inst);
	void (*psw_enabwe)(stwuct dmub_psw *dmub, boow enabwe, boow wait,
	uint8_t panew_inst);
	void (*psw_get_state)(stwuct dmub_psw *dmub, enum dc_psw_state *dc_psw_state,
	uint8_t panew_inst);
	void (*psw_set_wevew)(stwuct dmub_psw *dmub, uint16_t psw_wevew,
	uint8_t panew_inst);
	void (*psw_fowce_static)(stwuct dmub_psw *dmub, uint8_t panew_inst);
	void (*psw_get_wesidency)(stwuct dmub_psw *dmub, uint32_t *wesidency,
	uint8_t panew_inst);
	void (*psw_set_sink_vtotaw_in_psw_active)(stwuct dmub_psw *dmub,
	uint16_t psw_vtotaw_idwe, uint16_t psw_vtotaw_su);
	void (*psw_set_powew_opt)(stwuct dmub_psw *dmub, unsigned int powew_opt, uint8_t panew_inst);
};

stwuct dmub_psw *dmub_psw_cweate(stwuct dc_context *ctx);
void dmub_psw_destwoy(stwuct dmub_psw **dmub);


#endif /* _DMUB_PSW_H_ */
