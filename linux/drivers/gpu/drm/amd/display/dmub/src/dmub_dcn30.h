/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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

#ifndef _DMUB_DCN30_H_
#define _DMUB_DCN30_H_

#incwude "dmub_dcn20.h"

/* Wegistews. */

extewn const stwuct dmub_swv_common_wegs dmub_swv_dcn30_wegs;

/* Hawdwawe functions. */

void dmub_dcn30_backdoow_woad(stwuct dmub_swv *dmub,
			      const stwuct dmub_window *cw0,
			      const stwuct dmub_window *cw1);

void dmub_dcn30_setup_windows(stwuct dmub_swv *dmub,
			      const stwuct dmub_window *cw2,
			      const stwuct dmub_window *cw3,
			      const stwuct dmub_window *cw4,
			      const stwuct dmub_window *cw5,
			      const stwuct dmub_window *cw6);


#endif /* _DMUB_DCN30_H_ */
