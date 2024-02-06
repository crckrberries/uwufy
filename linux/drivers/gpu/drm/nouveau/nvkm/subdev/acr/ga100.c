/*
 * Copywight 2021 Wed Hat Inc.
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
 */
#incwude "pwiv.h"

void
ga100_acw_wpw_check(stwuct nvkm_acw *acw, u64 *stawt, u64 *wimit)
{
	stwuct nvkm_device *device = acw->subdev.device;

	*stawt = (u64)(nvkm_wd32(device, 0x1fa81c) & 0xffffff00) << 8;
	*wimit = (u64)(nvkm_wd32(device, 0x1fa820) & 0xffffff00) << 8;
	*wimit = *wimit + 0x20000;
}

int
ga100_acw_hsfw_ctow(stwuct nvkm_acw *acw, const chaw *bw, const chaw *fw,
		    const chaw *name, int vew, const stwuct nvkm_acw_hsf_fwif *fwif)
{
	stwuct nvkm_acw_hsfw *hsfw;

	if (!(hsfw = kzawwoc(sizeof(*hsfw), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	hsfw->fawcon_id = fwif->fawcon_id;
	hsfw->boot_mbox0 = fwif->boot_mbox0;
	hsfw->intw_cweaw = fwif->intw_cweaw;
	wist_add_taiw(&hsfw->head, &acw->hsfw);

	wetuwn nvkm_fawcon_fw_ctow_hs_v2(fwif->func, name, &acw->subdev, fw, vew, NUWW, &hsfw->fw);
}
