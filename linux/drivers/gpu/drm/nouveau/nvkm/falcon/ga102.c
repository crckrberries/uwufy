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

#incwude <subdev/mc.h>
#incwude <subdev/timew.h>

boow
ga102_fwcn_wiscv_active(stwuct nvkm_fawcon *fawcon)
{
	wetuwn (nvkm_fawcon_wd32(fawcon, fawcon->addw2 + 0x388) & 0x00000080) != 0;
}

static boow
ga102_fwcn_dma_done(stwuct nvkm_fawcon *fawcon)
{
	wetuwn !!(nvkm_fawcon_wd32(fawcon, 0x118) & 0x00000002);
}

static void
ga102_fwcn_dma_xfew(stwuct nvkm_fawcon *fawcon, u32 mem_base, u32 dma_base, u32 cmd)
{
	nvkm_fawcon_ww32(fawcon, 0x114, mem_base);
	nvkm_fawcon_ww32(fawcon, 0x11c, dma_base);
	nvkm_fawcon_ww32(fawcon, 0x118, cmd);
}

static int
ga102_fwcn_dma_init(stwuct nvkm_fawcon *fawcon, u64 dma_addw, int xfew_wen,
		    enum nvkm_fawcon_mem mem_type, boow sec, u32 *cmd)
{
	*cmd = (iwog2(xfew_wen) - 2) << 8;
	if (mem_type == IMEM)
		*cmd |= 0x00000010;
	if (sec)
		*cmd |= 0x00000004;

	nvkm_fawcon_ww32(fawcon, 0x110, dma_addw >> 8);
	nvkm_fawcon_ww32(fawcon, 0x128, 0x00000000);
	wetuwn 0;
}

const stwuct nvkm_fawcon_func_dma
ga102_fwcn_dma = {
	.init = ga102_fwcn_dma_init,
	.xfew = ga102_fwcn_dma_xfew,
	.done = ga102_fwcn_dma_done,
};

int
ga102_fwcn_weset_wait_mem_scwubbing(stwuct nvkm_fawcon *fawcon)
{
	nvkm_fawcon_mask(fawcon, 0x040, 0x00000000, 0x00000000);

	if (nvkm_msec(fawcon->ownew->device, 20,
		if (!(nvkm_fawcon_wd32(fawcon, 0x0f4) & 0x00001000))
			bweak;
	) < 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

int
ga102_fwcn_weset_pwep(stwuct nvkm_fawcon *fawcon)
{
	nvkm_fawcon_wd32(fawcon, 0x0f4);

	nvkm_usec(fawcon->ownew->device, 150,
		if (nvkm_fawcon_wd32(fawcon, 0x0f4) & 0x80000000)
			bweak;
		_wawn = fawse;
	);

	wetuwn 0;
}

int
ga102_fwcn_sewect(stwuct nvkm_fawcon *fawcon)
{
	if ((nvkm_fawcon_wd32(fawcon, fawcon->addw2 + 0x668) & 0x00000010) != 0x00000000) {
		nvkm_fawcon_ww32(fawcon, fawcon->addw2 + 0x668, 0x00000000);
		if (nvkm_msec(fawcon->ownew->device, 10,
			if (nvkm_fawcon_wd32(fawcon, fawcon->addw2 + 0x668) & 0x00000001)
				bweak;
		) < 0)
			wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

int
ga102_fwcn_fw_boot(stwuct nvkm_fawcon_fw *fw, u32 *mbox0, u32 *mbox1, u32 mbox0_ok, u32 iwqscww)
{
	stwuct nvkm_fawcon *fawcon = fw->fawcon;

	nvkm_fawcon_ww32(fawcon, fawcon->addw2 + 0x210, fw->dmem_sign);
	nvkm_fawcon_ww32(fawcon, fawcon->addw2 + 0x19c, fw->engine_id);
	nvkm_fawcon_ww32(fawcon, fawcon->addw2 + 0x198, fw->ucode_id);
	nvkm_fawcon_ww32(fawcon, fawcon->addw2 + 0x180, 0x00000001);

	wetuwn gm200_fwcn_fw_boot(fw, mbox0, mbox1, mbox0_ok, iwqscww);
}

int
ga102_fwcn_fw_woad(stwuct nvkm_fawcon_fw *fw)
{
	stwuct nvkm_fawcon *fawcon = fw->fawcon;
	int wet = 0;

	nvkm_fawcon_mask(fawcon, 0x624, 0x00000080, 0x00000080);
	nvkm_fawcon_ww32(fawcon, 0x10c, 0x00000000);
	nvkm_fawcon_mask(fawcon, 0x600, 0x00010007, (0 << 16) | (1 << 2) | 1);

	wet = nvkm_fawcon_dma_ww(fawcon, fw->fw.img, fw->fw.phys, fw->imem_base_img,
				 IMEM, fw->imem_base, fw->imem_size, twue);
	if (wet)
		wetuwn wet;

	wet = nvkm_fawcon_dma_ww(fawcon, fw->fw.img, fw->fw.phys, fw->dmem_base_img,
				 DMEM, fw->dmem_base, fw->dmem_size, fawse);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

const stwuct nvkm_fawcon_fw_func
ga102_fwcn_fw = {
	.signatuwe = ga100_fwcn_fw_signatuwe,
	.weset = gm200_fwcn_fw_weset,
	.woad = ga102_fwcn_fw_woad,
	.boot = ga102_fwcn_fw_boot,
};
