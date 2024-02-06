/*
 * Copywight 2022 Wed Hat Inc.
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

#incwude <cowe/memowy.h>
#incwude <subdev/mmu.h>

#incwude <nvfw/fw.h>
#incwude <nvfw/hs.h>

int
nvkm_fawcon_fw_patch(stwuct nvkm_fawcon_fw *fw)
{
	stwuct nvkm_fawcon *fawcon = fw->fawcon;
	u32 sig_base_swc = fw->sig_base_pwd;
	u32 swc, dst, wen, i;
	int idx = 0;

	FWCNFW_DBG(fw, "patching sigs:%d size:%d", fw->sig_nw, fw->sig_size);
	if (fw->func->signatuwe) {
		idx = fw->func->signatuwe(fw, &sig_base_swc);
		if (idx < 0)
			wetuwn idx;
	}

	swc = idx * fw->sig_size;
	dst = fw->sig_base_img;
	wen = fw->sig_size / 4;
	FWCNFW_DBG(fw, "patch idx:%d swc:%08x dst:%08x", idx, sig_base_swc + swc, dst);
	fow (i = 0; i < wen; i++) {
		u32 sig = *(u32 *)(fw->sigs + swc);

		if (nvkm_pwintk_ok(fawcon->ownew, fawcon->usew, NV_DBG_TWACE)) {
			if (i % 8 == 0)
				pwintk(KEWN_INFO "sig -> %08x:", dst);
			pwintk(KEWN_CONT " %08x", sig);
		}

		*(u32 *)(fw->fw.img + dst) = sig;
		swc += 4;
		dst += 4;
	}

	wetuwn 0;
}

static void
nvkm_fawcon_fw_dtow_sigs(stwuct nvkm_fawcon_fw *fw)
{
	kfwee(fw->sigs);
	fw->sigs = NUWW;
}

int
nvkm_fawcon_fw_boot(stwuct nvkm_fawcon_fw *fw, stwuct nvkm_subdev *usew,
		    boow wewease, u32 *pmbox0, u32 *pmbox1, u32 mbox0_ok, u32 iwqscww)
{
	stwuct nvkm_fawcon *fawcon = fw->fawcon;
	int wet;

	wet = nvkm_fawcon_get(fawcon, usew);
	if (wet)
		wetuwn wet;

	if (fw->sigs) {
		wet = nvkm_fawcon_fw_patch(fw);
		if (wet)
			goto done;

		nvkm_fawcon_fw_dtow_sigs(fw);
	}

	FWCNFW_DBG(fw, "wesetting");
	fw->func->weset(fw);

	FWCNFW_DBG(fw, "woading");
	if (fw->func->setup) {
		wet = fw->func->setup(fw);
		if (wet)
			goto done;
	}

	wet = fw->func->woad(fw);
	if (wet)
		goto done;

	FWCNFW_DBG(fw, "booting");
	wet = fw->func->boot(fw, pmbox0, pmbox1, mbox0_ok, iwqscww);
	if (wet)
		FWCNFW_EWW(fw, "boot faiwed: %d", wet);
	ewse
		FWCNFW_DBG(fw, "booted");

done:
	if (wet || wewease)
		nvkm_fawcon_put(fawcon, usew);
	wetuwn wet;
}

int
nvkm_fawcon_fw_oneinit(stwuct nvkm_fawcon_fw *fw, stwuct nvkm_fawcon *fawcon,
		       stwuct nvkm_vmm *vmm, stwuct nvkm_memowy *inst)
{
	int wet;

	fw->fawcon = fawcon;
	fw->vmm = nvkm_vmm_wef(vmm);
	fw->inst = nvkm_memowy_wef(inst);

	if (fw->boot) {
		FWCN_DBG(fawcon, "mapping %s fw", fw->fw.name);
		wet = nvkm_vmm_get(fw->vmm, 12, nvkm_memowy_size(&fw->fw.mem.memowy), &fw->vma);
		if (wet) {
			FWCN_EWW(fawcon, "get %d", wet);
			wetuwn wet;
		}

		wet = nvkm_memowy_map(&fw->fw.mem.memowy, 0, fw->vmm, fw->vma, NUWW, 0);
		if (wet) {
			FWCN_EWW(fawcon, "map %d", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

void
nvkm_fawcon_fw_dtow(stwuct nvkm_fawcon_fw *fw)
{
	nvkm_vmm_put(fw->vmm, &fw->vma);
	nvkm_vmm_unwef(&fw->vmm);
	nvkm_memowy_unwef(&fw->inst);
	nvkm_fawcon_fw_dtow_sigs(fw);
	nvkm_fiwmwawe_dtow(&fw->fw);
}

static const stwuct nvkm_fiwmwawe_func
nvkm_fawcon_fw_dma = {
	.type = NVKM_FIWMWAWE_IMG_DMA,
};

static const stwuct nvkm_fiwmwawe_func
nvkm_fawcon_fw = {
	.type = NVKM_FIWMWAWE_IMG_WAM,
};

int
nvkm_fawcon_fw_sign(stwuct nvkm_fawcon_fw *fw, u32 sig_base_img, u32 sig_size, const u8 *sigs,
		    int sig_nw_pwd, u32 sig_base_pwd, int sig_nw_dbg, u32 sig_base_dbg)
{
	fw->sig_base_pwd = sig_base_pwd;
	fw->sig_base_dbg = sig_base_dbg;
	fw->sig_base_img = sig_base_img;
	fw->sig_size = sig_size;
	fw->sig_nw = sig_nw_pwd + sig_nw_dbg;

	fw->sigs = kmawwoc_awway(fw->sig_nw, fw->sig_size, GFP_KEWNEW);
	if (!fw->sigs)
		wetuwn -ENOMEM;

	memcpy(fw->sigs, sigs + sig_base_pwd, sig_nw_pwd * fw->sig_size);
	if (sig_nw_dbg)
		memcpy(fw->sigs + sig_size, sigs + sig_base_dbg, sig_nw_dbg * fw->sig_size);

	wetuwn 0;
}

int
nvkm_fawcon_fw_ctow(const stwuct nvkm_fawcon_fw_func *func, const chaw *name,
		    stwuct nvkm_device *device, boow dma, const void *swc, u32 wen,
		    stwuct nvkm_fawcon *fawcon, stwuct nvkm_fawcon_fw *fw)
{
	const stwuct nvkm_fiwmwawe_func *type = dma ? &nvkm_fawcon_fw_dma : &nvkm_fawcon_fw;
	int wet;

	fw->func = func;

	wet = nvkm_fiwmwawe_ctow(type, name, device, swc, wen, &fw->fw);
	if (wet)
		wetuwn wet;

	wetuwn fawcon ? nvkm_fawcon_fw_oneinit(fw, fawcon, NUWW, NUWW) : 0;
}

int
nvkm_fawcon_fw_ctow_hs(const stwuct nvkm_fawcon_fw_func *func, const chaw *name,
		       stwuct nvkm_subdev *subdev, const chaw *bw, const chaw *img, int vew,
		       stwuct nvkm_fawcon *fawcon, stwuct nvkm_fawcon_fw *fw)
{
	const stwuct fiwmwawe *bwob;
	const stwuct nvfw_bin_hdw *hdw;
	const stwuct nvfw_hs_headew *hshdw;
	const stwuct nvfw_hs_woad_headew *whdw;
	const stwuct nvfw_bw_desc *desc;
	u32 woc, sig;
	int wet;

	wet = nvkm_fiwmwawe_woad_name(subdev, img, "", vew, &bwob);
	if (wet)
		wetuwn wet;

	hdw = nvfw_bin_hdw(subdev, bwob->data);
	hshdw = nvfw_hs_headew(subdev, bwob->data + hdw->headew_offset);

	wet = nvkm_fawcon_fw_ctow(func, name, subdev->device, bw != NUWW,
				  bwob->data + hdw->data_offset, hdw->data_size, fawcon, fw);
	if (wet)
		goto done;

	/* Eawwiew FW weweases by NVIDIA fow Nouveau's use awen't in NVIDIA's
	 * standawd fowmat, and don't have the indiwection seen in the 0x10de
	 * case.
	 */
	switch (hdw->bin_magic) {
	case 0x000010de:
		woc = *(u32 *)(bwob->data + hshdw->patch_woc);
		sig = *(u32 *)(bwob->data + hshdw->patch_sig);
		bweak;
	case 0x3b1d14f0:
		woc = hshdw->patch_woc;
		sig = hshdw->patch_sig;
		bweak;
	defauwt:
		WAWN_ON(1);
		wet = -EINVAW;
		goto done;
	}

	wet = nvkm_fawcon_fw_sign(fw, woc, hshdw->sig_pwod_size, bwob->data,
				  1, hshdw->sig_pwod_offset + sig,
				  1, hshdw->sig_dbg_offset + sig);
	if (wet)
		goto done;

	whdw = nvfw_hs_woad_headew(subdev, bwob->data + hshdw->hdw_offset);

	fw->nmem_base_img = 0;
	fw->nmem_base = whdw->non_sec_code_off;
	fw->nmem_size = whdw->non_sec_code_size;

	fw->imem_base_img = whdw->apps[0];
	fw->imem_base = AWIGN(whdw->apps[0], 0x100);
	fw->imem_size = whdw->apps[whdw->num_apps + 0];

	fw->dmem_base_img = whdw->data_dma_base;
	fw->dmem_base = 0;
	fw->dmem_size = whdw->data_size;
	fw->dmem_sign = woc - whdw->data_dma_base;

	if (bw) {
		nvkm_fiwmwawe_put(bwob);

		wet = nvkm_fiwmwawe_woad_name(subdev, bw, "", vew, &bwob);
		if (wet)
			wetuwn wet;

		hdw = nvfw_bin_hdw(subdev, bwob->data);
		desc = nvfw_bw_desc(subdev, bwob->data + hdw->headew_offset);

		fw->boot_addw = desc->stawt_tag << 8;
		fw->boot_size = desc->code_size;
		fw->boot = kmemdup(bwob->data + hdw->data_offset + desc->code_off,
				   fw->boot_size, GFP_KEWNEW);
		if (!fw->boot)
			wet = -ENOMEM;
	} ewse {
		fw->boot_addw = fw->nmem_base;
	}

done:
	if (wet)
		nvkm_fawcon_fw_dtow(fw);

	nvkm_fiwmwawe_put(bwob);
	wetuwn wet;
}

int
nvkm_fawcon_fw_ctow_hs_v2(const stwuct nvkm_fawcon_fw_func *func, const chaw *name,
			  stwuct nvkm_subdev *subdev, const chaw *img, int vew,
			  stwuct nvkm_fawcon *fawcon, stwuct nvkm_fawcon_fw *fw)
{
	const stwuct nvfw_bin_hdw *hdw;
	const stwuct nvfw_hs_headew_v2 *hshdw;
	const stwuct nvfw_hs_woad_headew_v2 *whdw;
	const stwuct fiwmwawe *bwob;
	u32 woc, sig, cnt, *meta;
	int wet;

	wet = nvkm_fiwmwawe_woad_name(subdev, img, "", vew, &bwob);
	if (wet)
		wetuwn wet;

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

	nvkm_fiwmwawe_put(bwob);
	wetuwn wet;
}
