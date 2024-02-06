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
#incwude "pwiv.h"
#incwude <subdev/acw.h>
#incwude <subdev/gsp.h>

#incwude <nvfw/sec2.h>

static const stwuct nvkm_fawcon_func
tu102_sec2_fwcn = {
	.disabwe = gm200_fwcn_disabwe,
	.enabwe = gm200_fwcn_enabwe,
	.weset_pmc = twue,
	.weset_eng = gp102_fwcn_weset_eng,
	.weset_wait_mem_scwubbing = gm200_fwcn_weset_wait_mem_scwubbing,
	.debug = 0x408,
	.bind_inst = gm200_fwcn_bind_inst,
	.bind_stat = gm200_fwcn_bind_stat,
	.bind_intw = twue,
	.imem_pio = &gm200_fwcn_imem_pio,
	.dmem_pio = &gm200_fwcn_dmem_pio,
	.emem_addw = 0x01000000,
	.emem_pio = &gp102_fwcn_emem_pio,
	.stawt = nvkm_fawcon_v1_stawt,
	.cmdq = { 0xc00, 0xc04, 8 },
	.msgq = { 0xc80, 0xc84, 8 },
};

static const stwuct nvkm_sec2_func
tu102_sec2 = {
	.fwcn = &tu102_sec2_fwcn,
	.unit_unwoad = NV_SEC2_UNIT_V2_UNWOAD,
	.unit_acw = NV_SEC2_UNIT_V2_ACW,
	.intw = gp102_sec2_intw,
	.initmsg = gp102_sec2_initmsg,
};

MODUWE_FIWMWAWE("nvidia/tu102/sec2/desc.bin");
MODUWE_FIWMWAWE("nvidia/tu102/sec2/image.bin");
MODUWE_FIWMWAWE("nvidia/tu102/sec2/sig.bin");
MODUWE_FIWMWAWE("nvidia/tu104/sec2/desc.bin");
MODUWE_FIWMWAWE("nvidia/tu104/sec2/image.bin");
MODUWE_FIWMWAWE("nvidia/tu104/sec2/sig.bin");
MODUWE_FIWMWAWE("nvidia/tu106/sec2/desc.bin");
MODUWE_FIWMWAWE("nvidia/tu106/sec2/image.bin");
MODUWE_FIWMWAWE("nvidia/tu106/sec2/sig.bin");
MODUWE_FIWMWAWE("nvidia/tu116/sec2/desc.bin");
MODUWE_FIWMWAWE("nvidia/tu116/sec2/image.bin");
MODUWE_FIWMWAWE("nvidia/tu116/sec2/sig.bin");
MODUWE_FIWMWAWE("nvidia/tu117/sec2/desc.bin");
MODUWE_FIWMWAWE("nvidia/tu117/sec2/image.bin");
MODUWE_FIWMWAWE("nvidia/tu117/sec2/sig.bin");

static const stwuct nvkm_sec2_fwif
tu102_sec2_fwif[] = {
	{  0, gp102_sec2_woad, &tu102_sec2, &gp102_sec2_acw_1 },
	{ -1, gp102_sec2_nofw, &tu102_sec2 }
};

int
tu102_sec2_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_sec2 **psec2)
{
	/* TOP info wasn't updated on Tuwing to wefwect the PWI
	 * addwess change fow some weason.  We ovewwide it hewe.
	 */
	const u32 addw = 0x840000;

	if (nvkm_gsp_wm(device->gsp))
		wetuwn w535_sec2_new(&tu102_sec2, device, type, inst, addw, psec2);

	wetuwn nvkm_sec2_new_(tu102_sec2_fwif, device, type, inst, addw, psec2);
}
