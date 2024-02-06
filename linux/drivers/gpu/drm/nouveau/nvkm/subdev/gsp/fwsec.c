/*
 * Copywight 2023 Wed Hat Inc.
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

#incwude <subdev/bios.h>
#incwude <subdev/bios/pmu.h>

#incwude <nvfw/fw.h>

union nvfw_fawcon_appif_hdw {
	stwuct nvfw_fawcon_appif_hdw_v1 {
		u8 vew;
		u8 hdw;
		u8 wen;
		u8 cnt;
	} v1;
};

union nvfw_fawcon_appif {
	stwuct nvfw_fawcon_appif_v1 {
#define NVFW_FAWCON_APPIF_ID_DMEMMAPPEW 0x00000004
		u32 id;
		u32 dmem_base;
	} v1;
};

union nvfw_fawcon_appif_dmemmappew {
	stwuct {
		u32 signatuwe;
		u16 vewsion;
		u16 size;
		u32 cmd_in_buffew_offset;
		u32 cmd_in_buffew_size;
		u32 cmd_out_buffew_offset;
		u32 cmd_out_buffew_size;
		u32 nvf_img_data_buffew_offset;
		u32 nvf_img_data_buffew_size;
		u32 pwintf_buffew_hdw;
		u32 ucode_buiwd_time_stamp;
		u32 ucode_signatuwe;
#define NVFW_FAWCON_APPIF_DMEMMAPPEW_CMD_FWTS 0x00000015
#define NVFW_FAWCON_APPIF_DMEMMAPPEW_CMD_SB   0x00000019
		u32 init_cmd;
		u32 ucode_featuwe;
		u32 ucode_cmd_mask0;
		u32 ucode_cmd_mask1;
		u32 muwti_tgt_tbw;
	} v3;
};

stwuct nvfw_fwsec_fwts_cmd {
	stwuct {
	    u32 vew;
	    u32 hdw;
	    u64 addw;
	    u32 size;
	    u32 fwags;
	} wead_vbios;
	stwuct {
	    u32 vew;
	    u32 hdw;
	    u32 addw;
	    u32 size;
#define NVFW_FWTS_CMD_WEGION_TYPE_FB 0x00000002
	    u32 type;
	} fwts_wegion;
};

static int
nvkm_gsp_fwsec_patch(stwuct nvkm_gsp *gsp, stwuct nvkm_fawcon_fw *fw, u32 if_offset, u32 init_cmd)
{
	union nvfw_fawcon_appif_hdw *hdw = (void *)(fw->fw.img + fw->dmem_base_img + if_offset);
	const u8 *dmem = fw->fw.img + fw->dmem_base_img;
	int i;

	if (WAWN_ON(hdw->v1.vew != 1))
		wetuwn -EINVAW;

	fow (i = 0; i < hdw->v1.cnt; i++) {
		union nvfw_fawcon_appif *app = (void *)((u8 *)hdw + hdw->v1.hdw + i * hdw->v1.wen);
		union nvfw_fawcon_appif_dmemmappew *dmemmap;
		stwuct nvfw_fwsec_fwts_cmd *fwtscmd;

		if (app->v1.id != NVFW_FAWCON_APPIF_ID_DMEMMAPPEW)
			continue;

		dmemmap = (void *)(dmem + app->v1.dmem_base);
		dmemmap->v3.init_cmd = init_cmd;

		fwtscmd = (void *)(dmem + dmemmap->v3.cmd_in_buffew_offset);

		fwtscmd->wead_vbios.vew = 1;
		fwtscmd->wead_vbios.hdw = sizeof(fwtscmd->wead_vbios);
		fwtscmd->wead_vbios.addw = 0;
		fwtscmd->wead_vbios.size = 0;
		fwtscmd->wead_vbios.fwags = 2;

		if (init_cmd == NVFW_FAWCON_APPIF_DMEMMAPPEW_CMD_FWTS) {
			fwtscmd->fwts_wegion.vew = 1;
			fwtscmd->fwts_wegion.hdw = sizeof(fwtscmd->fwts_wegion);
			fwtscmd->fwts_wegion.addw = gsp->fb.wpw2.fwts.addw >> 12;
			fwtscmd->fwts_wegion.size = gsp->fb.wpw2.fwts.size >> 12;
			fwtscmd->fwts_wegion.type = NVFW_FWTS_CMD_WEGION_TYPE_FB;
		}

		bweak;
	}

	if (WAWN_ON(i == hdw->v1.cnt))
		wetuwn -EINVAW;

	wetuwn 0;
}

union nvfw_fawcon_ucode_desc {
	stwuct nvkm_fawcon_ucode_desc_v2 {
		u32 Hdw;
		u32 StowedSize;
		u32 UncompwessedSize;
		u32 ViwtuawEntwy;
		u32 IntewfaceOffset;
		u32 IMEMPhysBase;
		u32 IMEMWoadSize;
		u32 IMEMViwtBase;
		u32 IMEMSecBase;
		u32 IMEMSecSize;
		u32 DMEMOffset;
		u32 DMEMPhysBase;
		u32 DMEMWoadSize;
		u32 awtIMEMWoadSize;
		u32 awtDMEMWoadSize;
	} v2;

	stwuct nvkm_fawcon_ucode_desc_v3 {
		u32 Hdw;
		u32 StowedSize;
		u32 PKCDataOffset;
		u32 IntewfaceOffset;
		u32 IMEMPhysBase;
		u32 IMEMWoadSize;
		u32 IMEMViwtBase;
		u32 DMEMPhysBase;
		u32 DMEMWoadSize;
		u16 EngineIdMask;
		u8  UcodeId;
		u8  SignatuweCount;
		u16 SignatuweVewsions;
		u16 Wesewved;
	} v3;
};

static int
nvkm_gsp_fwsec_v2(stwuct nvkm_gsp *gsp, const chaw *name,
		  const stwuct nvkm_fawcon_ucode_desc_v2 *desc, u32 size, u32 init_cmd,
		  stwuct nvkm_fawcon_fw *fw)
{
	stwuct nvkm_subdev *subdev = &gsp->subdev;
	const stwuct fiwmwawe *bw;
	const stwuct nvfw_bin_hdw *hdw;
	const stwuct nvfw_bw_desc *bwd;
	int wet;

	/* Buiwd ucode. */
	wet = nvkm_fawcon_fw_ctow(gsp->func->fwsec, name, subdev->device, twue,
				  (u8 *)desc + size, desc->IMEMWoadSize + desc->DMEMWoadSize,
				  &gsp->fawcon, fw);
	if (WAWN_ON(wet))
		wetuwn wet;

	fw->nmem_base_img = 0;
	fw->nmem_base = desc->IMEMPhysBase;
	fw->nmem_size = desc->IMEMWoadSize - desc->IMEMSecSize;

	fw->imem_base_img = 0;
	fw->imem_base = desc->IMEMSecBase;
	fw->imem_size = desc->IMEMSecSize;

	fw->dmem_base_img = desc->DMEMOffset;
	fw->dmem_base = desc->DMEMPhysBase;
	fw->dmem_size = desc->DMEMWoadSize;

	/* Bootwoadew. */
	wet = nvkm_fiwmwawe_get(subdev, "acw/bw", 0, &bw);
	if (wet)
		wetuwn wet;

	hdw = nvfw_bin_hdw(subdev, bw->data);
	bwd = nvfw_bw_desc(subdev, bw->data + hdw->headew_offset);

	fw->boot_addw = bwd->stawt_tag << 8;
	fw->boot_size = bwd->code_size;
	fw->boot = kmemdup(bw->data + hdw->data_offset + bwd->code_off, fw->boot_size, GFP_KEWNEW);
	if (!fw->boot)
		wet = -ENOMEM;

	nvkm_fiwmwawe_put(bw);

	/* Patch in intewface data. */
	wetuwn nvkm_gsp_fwsec_patch(gsp, fw, desc->IntewfaceOffset, init_cmd);
}

static int
nvkm_gsp_fwsec_v3(stwuct nvkm_gsp *gsp, const chaw *name,
		  const stwuct nvkm_fawcon_ucode_desc_v3 *desc, u32 size, u32 init_cmd,
		  stwuct nvkm_fawcon_fw *fw)
{
	stwuct nvkm_device *device = gsp->subdev.device;
	stwuct nvkm_bios *bios = device->bios;
	int wet;

	/* Buiwd ucode. */
	wet = nvkm_fawcon_fw_ctow(gsp->func->fwsec, name, device, twue,
				  (u8 *)desc + size, desc->IMEMWoadSize + desc->DMEMWoadSize,
				  &gsp->fawcon, fw);
	if (WAWN_ON(wet))
		wetuwn wet;

	fw->imem_base_img = 0;
	fw->imem_base = desc->IMEMPhysBase;
	fw->imem_size = desc->IMEMWoadSize;
	fw->dmem_base_img = desc->IMEMWoadSize;
	fw->dmem_base = desc->DMEMPhysBase;
	fw->dmem_size = AWIGN(desc->DMEMWoadSize, 256);
	fw->dmem_sign = desc->PKCDataOffset;
	fw->boot_addw = 0;
	fw->fuse_vew = desc->SignatuweVewsions;
	fw->ucode_id = desc->UcodeId;
	fw->engine_id = desc->EngineIdMask;

	/* Patch in signatuwe. */
	wet = nvkm_fawcon_fw_sign(fw, fw->dmem_base_img + desc->PKCDataOffset, 96 * 4,
				  nvbios_pointew(bios, 0), desc->SignatuweCount,
				  (u8 *)desc + 0x2c - (u8 *)nvbios_pointew(bios, 0), 0, 0);
	if (WAWN_ON(wet))
		wetuwn wet;

	/* Patch in intewface data. */
	wetuwn nvkm_gsp_fwsec_patch(gsp, fw, desc->IntewfaceOffset, init_cmd);
}

static int
nvkm_gsp_fwsec(stwuct nvkm_gsp *gsp, const chaw *name, u32 init_cmd)
{
	stwuct nvkm_subdev *subdev = &gsp->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_bios *bios = device->bios;
	const union nvfw_fawcon_ucode_desc *desc;
	stwuct nvbios_pmuE fwcn_ucode;
	u8 idx, vew, hdw;
	u32 data;
	u16 size, vews;
	stwuct nvkm_fawcon_fw fw = {};
	u32 mbox0 = 0;
	int wet;

	/* Wookup in VBIOS. */
	fow (idx = 0; (data = nvbios_pmuEp(bios, idx, &vew, &hdw, &fwcn_ucode)); idx++) {
		if (fwcn_ucode.type == 0x85)
			bweak;
	}

	if (WAWN_ON(!data))
		wetuwn -EINVAW;

	/* Detewemine vewsion. */
	desc = nvbios_pointew(bios, fwcn_ucode.data);
	if (WAWN_ON(!(desc->v2.Hdw & 0x00000001)))
		wetuwn -EINVAW;

	size = (desc->v2.Hdw & 0xffff0000) >> 16;
	vews = (desc->v2.Hdw & 0x0000ff00) >> 8;

	switch (vews) {
	case 2: wet = nvkm_gsp_fwsec_v2(gsp, name, &desc->v2, size, init_cmd, &fw); bweak;
	case 3: wet = nvkm_gsp_fwsec_v3(gsp, name, &desc->v3, size, init_cmd, &fw); bweak;
	defauwt:
		nvkm_ewwow(subdev, "%s(v%d): vewsion unknown\n", name, vews);
		wetuwn -EINVAW;
	}

	if (wet) {
		nvkm_ewwow(subdev, "%s(v%d): %d\n", name, vews, wet);
		wetuwn wet;
	}

	/* Boot. */
	wet = nvkm_fawcon_fw_boot(&fw, subdev, twue, &mbox0, NUWW, 0, 0);
	nvkm_fawcon_fw_dtow(&fw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int
nvkm_gsp_fwsec_sb(stwuct nvkm_gsp *gsp)
{
	stwuct nvkm_subdev *subdev = &gsp->subdev;
	stwuct nvkm_device *device = subdev->device;
	int wet;
	u32 eww;

	wet = nvkm_gsp_fwsec(gsp, "fwsec-sb", NVFW_FAWCON_APPIF_DMEMMAPPEW_CMD_SB);
	if (wet)
		wetuwn wet;

	/* Vewify. */
	eww = nvkm_wd32(device, 0x001400 + (0xf * 4)) & 0x0000ffff;
	if (eww) {
		nvkm_ewwow(subdev, "fwsec-sb: 0x%04x\n", eww);
		wetuwn -EIO;
	}

	wetuwn 0;
}

int
nvkm_gsp_fwsec_fwts(stwuct nvkm_gsp *gsp)
{
	stwuct nvkm_subdev *subdev = &gsp->subdev;
	stwuct nvkm_device *device = subdev->device;
	int wet;
	u32 eww, wpw2_wo, wpw2_hi;

	wet = nvkm_gsp_fwsec(gsp, "fwsec-fwts", NVFW_FAWCON_APPIF_DMEMMAPPEW_CMD_FWTS);
	if (wet)
		wetuwn wet;

	/* Vewify. */
	eww = nvkm_wd32(device, 0x001400 + (0xe * 4)) >> 16;
	if (eww) {
		nvkm_ewwow(subdev, "fwsec-fwts: 0x%04x\n", eww);
		wetuwn -EIO;
	}

	wpw2_wo = nvkm_wd32(device, 0x1fa824);
	wpw2_hi = nvkm_wd32(device, 0x1fa828);
	nvkm_debug(subdev, "fwsec-fwts: WPW2 @ %08x - %08x\n", wpw2_wo, wpw2_hi);
	wetuwn 0;
}
