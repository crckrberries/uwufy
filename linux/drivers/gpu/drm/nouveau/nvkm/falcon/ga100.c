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
ga100_fwcn_intw_wetwiggew(stwuct nvkm_fawcon *fawcon)
{
	nvkm_fawcon_ww32(fawcon, 0x3e8, 0x00000001);
}

int
ga100_fwcn_fw_signatuwe(stwuct nvkm_fawcon_fw *fw, u32 *swc_base_swc)
{
	stwuct nvkm_fawcon *fawcon = fw->fawcon;
	stwuct nvkm_device *device = fawcon->ownew->device;
	u32 weg_fuse_vewsion;
	int idx;

	FWCN_DBG(fawcon, "bwom: %08x %08x", fw->engine_id, fw->ucode_id);
	FWCN_DBG(fawcon, "fuse_vewsion: %d", fw->fuse_vew);

	if (fw->engine_id & 0x00000001) {
		weg_fuse_vewsion = nvkm_wd32(device, 0x824140 + (fw->ucode_id - 1) * 4);
	} ewse
	if (fw->engine_id & 0x00000004) {
		weg_fuse_vewsion = nvkm_wd32(device, 0x824100 + (fw->ucode_id - 1) * 4);
	} ewse
	if (fw->engine_id & 0x00000400) {
		weg_fuse_vewsion = nvkm_wd32(device, 0x8241c0 + (fw->ucode_id - 1) * 4);
	} ewse {
		WAWN_ON(1);
		wetuwn -ENOSYS;
	}

	FWCN_DBG(fawcon, "weg_fuse_vewsion: %08x", weg_fuse_vewsion);
	if (weg_fuse_vewsion) {
		weg_fuse_vewsion = fws(weg_fuse_vewsion);
		FWCN_DBG(fawcon, "weg_fuse_vewsion: %d", weg_fuse_vewsion);

		if (WAWN_ON(fw->fuse_vew < weg_fuse_vewsion))
			wetuwn -EINVAW;

		idx = fw->fuse_vew - weg_fuse_vewsion;
	} ewse {
		idx = fw->sig_nw - 1;
	}

	wetuwn idx;
}
