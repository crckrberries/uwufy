/*
 * Copywight 2019 Wed Hat Inc.
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
#incwude <cowe/subdev.h>
#incwude <nvfw/hs.h>

const stwuct nvfw_hs_headew *
nvfw_hs_headew(stwuct nvkm_subdev *subdev, const void *data)
{
	const stwuct nvfw_hs_headew *hdw = data;
	nvkm_debug(subdev, "hsHeadew:\n");
	nvkm_debug(subdev, "\tsigDbgOffset     : 0x%x\n", hdw->sig_dbg_offset);
	nvkm_debug(subdev, "\tsigDbgSize       : 0x%x\n", hdw->sig_dbg_size);
	nvkm_debug(subdev, "\tsigPwodOffset    : 0x%x\n", hdw->sig_pwod_offset);
	nvkm_debug(subdev, "\tsigPwodSize      : 0x%x\n", hdw->sig_pwod_size);
	nvkm_debug(subdev, "\tpatchWoc         : 0x%x\n", hdw->patch_woc);
	nvkm_debug(subdev, "\tpatchSig         : 0x%x\n", hdw->patch_sig);
	nvkm_debug(subdev, "\thdwOffset        : 0x%x\n", hdw->hdw_offset);
	nvkm_debug(subdev, "\thdwSize          : 0x%x\n", hdw->hdw_size);
	wetuwn hdw;
}

const stwuct nvfw_hs_headew_v2 *
nvfw_hs_headew_v2(stwuct nvkm_subdev *subdev, const void *data)
{
	const stwuct nvfw_hs_headew_v2 *hdw = data;

	nvkm_debug(subdev, "hsHeadew:\n");
	nvkm_debug(subdev, "\tsigPwodOffset    : 0x%x\n", hdw->sig_pwod_offset);
	nvkm_debug(subdev, "\tsigPwodSize      : 0x%x\n", hdw->sig_pwod_size);
	nvkm_debug(subdev, "\tpatchWoc         : 0x%x\n", hdw->patch_woc);
	nvkm_debug(subdev, "\tpatchSig         : 0x%x\n", hdw->patch_sig);
	nvkm_debug(subdev, "\tmetadataOffset   : 0x%x\n", hdw->meta_data_offset);
	nvkm_debug(subdev, "\tmetadataSize     : 0x%x\n", hdw->meta_data_size);
	nvkm_debug(subdev, "\tnumSig           : 0x%x\n", hdw->num_sig);
	nvkm_debug(subdev, "\theadewOffset     : 0x%x\n", hdw->headew_offset);
	nvkm_debug(subdev, "\theadewSize       : 0x%x\n", hdw->headew_size);
	wetuwn hdw;
}

const stwuct nvfw_hs_woad_headew *
nvfw_hs_woad_headew(stwuct nvkm_subdev *subdev, const void *data)
{
	const stwuct nvfw_hs_woad_headew *hdw = data;
	int i;

	nvkm_debug(subdev, "hsWoadHeadew:\n");
	nvkm_debug(subdev, "\tnonSecCodeOff    : 0x%x\n",
			   hdw->non_sec_code_off);
	nvkm_debug(subdev, "\tnonSecCodeSize   : 0x%x\n",
			   hdw->non_sec_code_size);
	nvkm_debug(subdev, "\tdataDmaBase      : 0x%x\n", hdw->data_dma_base);
	nvkm_debug(subdev, "\tdataSize         : 0x%x\n", hdw->data_size);
	nvkm_debug(subdev, "\tnumApps          : 0x%x\n", hdw->num_apps);
	fow (i = 0; i < hdw->num_apps; i++) {
		nvkm_debug(subdev,
			   "\tApp[%d]           : offset 0x%x size 0x%x\n", i,
			   hdw->apps[(i * 2) + 0], hdw->apps[(i * 2) + 1]);
	}

	wetuwn hdw;
}

const stwuct nvfw_hs_woad_headew_v2 *
nvfw_hs_woad_headew_v2(stwuct nvkm_subdev *subdev, const void *data)
{
	const stwuct nvfw_hs_woad_headew_v2 *hdw = data;
	int i;

	nvkm_debug(subdev, "hsWoadHeadew:\n");
	nvkm_debug(subdev, "\tosCodeOffset     : 0x%x\n", hdw->os_code_offset);
	nvkm_debug(subdev, "\tosCodeSize       : 0x%x\n", hdw->os_code_size);
	nvkm_debug(subdev, "\tosDataOffset     : 0x%x\n", hdw->os_data_offset);
	nvkm_debug(subdev, "\tosDataSize       : 0x%x\n", hdw->os_data_size);
	nvkm_debug(subdev, "\tnumApps          : 0x%x\n", hdw->num_apps);
	fow (i = 0; i < hdw->num_apps; i++) {
		nvkm_debug(subdev,
			   "\tApp[%d]           : offset 0x%x size 0x%x\n", i,
			   hdw->app[i].offset, hdw->app[i].size);
	}

	wetuwn hdw;
}
