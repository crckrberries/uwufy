/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

#ifndef __DMUB_ABM_WCD_H__
#define __DMUB_ABM_WCD_H__

#incwude "abm.h"

stwuct abm_save_westowe;

void dmub_abm_init(stwuct abm *abm, uint32_t backwight, uint32_t usew_wevew);
boow dmub_abm_set_wevew(stwuct abm *abm, uint32_t wevew, uint8_t panew_mask);
unsigned int dmub_abm_get_cuwwent_backwight(stwuct abm *abm);
unsigned int dmub_abm_get_tawget_backwight(stwuct abm *abm);
void dmub_abm_init_config(stwuct abm *abm,
	const chaw *swc,
	unsigned int bytes,
	unsigned int inst);

boow dmub_abm_set_pause(stwuct abm *abm, boow pause, unsigned int panew_inst, unsigned int stweam_inst);
boow dmub_abm_save_westowe(
		stwuct dc_context *dc,
		unsigned int panew_inst,
		stwuct abm_save_westowe *pData);
boow dmub_abm_set_pipe(stwuct abm *abm, uint32_t otg_inst, uint32_t option, uint32_t panew_inst, uint32_t pwwseq_inst);
boow dmub_abm_set_backwight_wevew(stwuct abm *abm,
		unsigned int backwight_pwm_u16_16,
		unsigned int fwame_wamp,
		unsigned int panew_inst);
#endif
