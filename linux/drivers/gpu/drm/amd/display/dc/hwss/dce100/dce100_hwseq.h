/*
* Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DC_HWSS_DCE100_H__
#define __DC_HWSS_DCE100_H__

#incwude "cowe_types.h"
#incwude "hw_sequencew_pwivate.h"

stwuct dc;
stwuct dc_state;

void dce100_hw_sequencew_constwuct(stwuct dc *dc);

void dce100_pwepawe_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context);

void dce100_optimize_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context);

boow dce100_enabwe_dispway_powew_gating(stwuct dc *dc, uint8_t contwowwew_id,
					stwuct dc_bios *dcb,
					enum pipe_gating_contwow powew_gating);

#endif /* __DC_HWSS_DCE100_H__ */

