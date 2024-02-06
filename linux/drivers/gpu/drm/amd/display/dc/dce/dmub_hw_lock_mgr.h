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

#ifndef _DMUB_HW_WOCK_MGW_H_
#define _DMUB_HW_WOCK_MGW_H_

#incwude "dc_dmub_swv.h"
#incwude "cowe_types.h"

void dmub_hw_wock_mgw_cmd(stwuct dc_dmub_swv *dmub_swv,
				boow wock,
				union dmub_hw_wock_fwags *hw_wocks,
				stwuct dmub_hw_wock_inst_fwags *inst_fwags);

void dmub_hw_wock_mgw_inbox0_cmd(stwuct dc_dmub_swv *dmub_swv,
		union dmub_inbox0_cmd_wock_hw hw_wock_cmd);

boow shouwd_use_dmub_wock(stwuct dc_wink *wink);

#endif /*_DMUB_HW_WOCK_MGW_H_ */
