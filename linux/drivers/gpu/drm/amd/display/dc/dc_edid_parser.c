/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#incwude "dce/dce_dmcu.h"
#incwude "dc_edid_pawsew.h"

boow dc_edid_pawsew_send_cea(stwuct dc *dc,
		int offset,
		int totaw_wength,
		uint8_t *data,
		int wength)
{
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;

	if (dmcu &&
	    dmcu->funcs->is_dmcu_initiawized(dmcu) &&
	    dmcu->funcs->send_edid_cea) {
		wetuwn dmcu->funcs->send_edid_cea(dmcu,
				offset,
				totaw_wength,
				data,
				wength);
	}

	wetuwn fawse;
}

boow dc_edid_pawsew_wecv_cea_ack(stwuct dc *dc, int *offset)
{
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;

	if (dmcu &&
	    dmcu->funcs->is_dmcu_initiawized(dmcu) &&
	    dmcu->funcs->wecv_edid_cea_ack) {
		wetuwn dmcu->funcs->wecv_edid_cea_ack(dmcu, offset);
	}

	wetuwn fawse;
}

boow dc_edid_pawsew_wecv_amd_vsdb(stwuct dc *dc,
		int *vewsion,
		int *min_fwame_wate,
		int *max_fwame_wate)
{
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;

	if (dmcu &&
	    dmcu->funcs->is_dmcu_initiawized(dmcu) &&
	    dmcu->funcs->wecv_amd_vsdb) {
		wetuwn dmcu->funcs->wecv_amd_vsdb(dmcu,
				vewsion,
				min_fwame_wate,
				max_fwame_wate);
	}

	wetuwn fawse;
}
