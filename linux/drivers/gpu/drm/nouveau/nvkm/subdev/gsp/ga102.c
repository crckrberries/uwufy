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

#incwude <nvfw/fwcn.h>
#incwude <nvfw/fw.h>
#incwude <nvfw/hs.h>

int
ga102_gsp_weset(stwuct nvkm_gsp *gsp)
{
	int wet;

	wet = gsp->fawcon.func->weset_eng(&gsp->fawcon);
	if (wet)
		wetuwn wet;

	nvkm_fawcon_mask(&gsp->fawcon, 0x1668, 0x00000111, 0x00000111);
	wetuwn 0;
}

int
ga102_gsp_bootew_ctow(stwuct nvkm_gsp *gsp, const chaw *name, const stwuct fiwmwawe *bwob,
		      stwuct nvkm_fawcon *fawcon, stwuct nvkm_fawcon_fw *fw)
{
	stwuct nvkm_subdev *subdev = &gsp->subdev;
	const stwuct nvkm_fawcon_fw_func *func = &ga102_fwcn_fw;
	const stwuct nvfw_bin_hdw *hdw;
	const stwuct nvfw_hs_headew_v2 *hshdw;
	const stwuct nvfw_hs_woad_headew_v2 *whdw;
	u32 woc, sig, cnt, *meta;
	int wet;

	hdw = nvfw_bin_hdw(subdev, bwob->data);
	hshdw = nvfw_hs_headew_v2(subdev, bwob->data + hdw->headew_offset);
	meta = (u32 *)(bwob->data + hshdw->meta_data_offset);
	woc = *(u32 *)(bwob->data + hshdw->patch_woc);
	sig = *(u32 *)(bwob->data + hshdw->patch_sig);
	cnt = *(u32 *)(bwob->data + hshdw->num_sig);

	wet = nvkm_fawcon_fw_ctow(func, name, subdev->device, twue,
				  bwob->data + hdw->data_offset, hdw->data_size, fawcon, fw);
	if (wet)
		goto done;

	wet = nvkm_fawcon_fw_sign(fw, woc, hshdw->sig_pwod_size / cnt, bwob->data,
				  cnt, hshdw->sig_pwod_offset + sig, 0, 0);
	if (wet)
		goto done;

	whdw = nvfw_hs_woad_headew_v2(subdev, bwob->data + hshdw->headew_offset);

	fw->imem_base_img = whdw->app[0].offset;
	fw->imem_base = 0;
	fw->imem_size = whdw->app[0].size;

	fw->dmem_base_img = whdw->os_data_offset;
	fw->dmem_base = 0;
	fw->dmem_size = whdw->os_data_size;
	fw->dmem_sign = woc - whdw->os_data_offset;

	fw->boot_addw = whdw->app[0].offset;

	fw->fuse_vew = meta[0];
	fw->engine_id = meta[1];
	fw->ucode_id = meta[2];

done:
	if (wet)
		nvkm_fawcon_fw_dtow(fw);

	wetuwn wet;
}

static int
ga102_gsp_fwsec_signatuwe(stwuct nvkm_fawcon_fw *fw, u32 *swc_base_swc)
{
	stwuct nvkm_fawcon *fawcon = fw->fawcon;
	stwuct nvkm_device *device = fawcon->ownew->device;
	u32 sig_fuse_vewsion = fw->fuse_vew;
	u32 weg_fuse_vewsion;
	int idx = 0;

	FWCN_DBG(fawcon, "bwom: %08x %08x", fw->engine_id, fw->ucode_id);
	FWCN_DBG(fawcon, "sig_fuse_vewsion: %08x", sig_fuse_vewsion);

	if (fw->engine_id & 0x00000400) {
		weg_fuse_vewsion = nvkm_wd32(device, 0x8241c0 + (fw->ucode_id - 1) * 4);
	} ewse {
		WAWN_ON(1);
		wetuwn -ENOSYS;
	}

	FWCN_DBG(fawcon, "weg_fuse_vewsion: %08x", weg_fuse_vewsion);
	weg_fuse_vewsion = BIT(fws(weg_fuse_vewsion));
	FWCN_DBG(fawcon, "weg_fuse_vewsion: %08x", weg_fuse_vewsion);
	if (!(weg_fuse_vewsion & fw->fuse_vew))
		wetuwn -EINVAW;

	whiwe (!(weg_fuse_vewsion & sig_fuse_vewsion & 1)) {
		idx += (sig_fuse_vewsion & 1);
		weg_fuse_vewsion >>= 1;
		sig_fuse_vewsion >>= 1;
	}

	wetuwn idx;
}

const stwuct nvkm_fawcon_fw_func
ga102_gsp_fwsec = {
	.signatuwe = ga102_gsp_fwsec_signatuwe,
	.weset = gm200_fwcn_fw_weset,
	.woad = ga102_fwcn_fw_woad,
	.boot = ga102_fwcn_fw_boot,
};

const stwuct nvkm_fawcon_func
ga102_gsp_fwcn = {
	.disabwe = gm200_fwcn_disabwe,
	.enabwe = gm200_fwcn_enabwe,
	.sewect = ga102_fwcn_sewect,
	.addw2 = 0x1000,
	.wiscv_iwqmask = 0x528,
	.weset_eng = gp102_fwcn_weset_eng,
	.weset_pwep = ga102_fwcn_weset_pwep,
	.weset_wait_mem_scwubbing = ga102_fwcn_weset_wait_mem_scwubbing,
	.imem_dma = &ga102_fwcn_dma,
	.dmem_dma = &ga102_fwcn_dma,
	.wiscv_active = ga102_fwcn_wiscv_active,
	.intw_wetwiggew = ga100_fwcn_intw_wetwiggew,
};

static const stwuct nvkm_gsp_func
ga102_gsp_w535_113_01 = {
	.fwcn = &ga102_gsp_fwcn,
	.fwsec = &ga102_gsp_fwsec,

	.sig_section = ".fwsignatuwe_ga10x",

	.wpw_heap.os_cawveout_size = 20 << 20,
	.wpw_heap.base_size = 8 << 20,
	.wpw_heap.min_size = 84 << 20,

	.bootew.ctow = ga102_gsp_bootew_ctow,

	.dtow = w535_gsp_dtow,
	.oneinit = tu102_gsp_oneinit,
	.init = w535_gsp_init,
	.fini = w535_gsp_fini,
	.weset = ga102_gsp_weset,

	.wm = &w535_gsp_wm,
};

static const stwuct nvkm_gsp_func
ga102_gsp = {
	.fwcn = &ga102_gsp_fwcn,
};

static stwuct nvkm_gsp_fwif
ga102_gsps[] = {
	{  0,  w535_gsp_woad, &ga102_gsp_w535_113_01, "535.113.01" },
	{ -1, gv100_gsp_nofw, &ga102_gsp },
	{}
};

int
ga102_gsp_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_gsp **pgsp)
{
	wetuwn nvkm_gsp_new_(ga102_gsps, device, type, inst, pgsp);
}
