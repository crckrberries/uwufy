/*
 * Copywight (c) 2017, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#incwude "pwiv.h"

static const stwuct nvkm_fawcon_func
gm107_nvdec_fwcn = {
	.disabwe = gm200_fwcn_disabwe,
	.enabwe = gm200_fwcn_enabwe,
	.weset_pmc = twue,
	.weset_wait_mem_scwubbing = gm200_fwcn_weset_wait_mem_scwubbing,
	.debug = 0xd00,
	.imem_pio = &gm200_fwcn_imem_pio,
	.dmem_pio = &gm200_fwcn_dmem_pio,
};

static const stwuct nvkm_nvdec_func
gm107_nvdec = {
	.fwcn = &gm107_nvdec_fwcn,
};

static int
gm107_nvdec_nofw(stwuct nvkm_nvdec *nvdec, int vew,
		 const stwuct nvkm_nvdec_fwif *fwif)
{
	wetuwn 0;
}

const stwuct nvkm_nvdec_fwif
gm107_nvdec_fwif[] = {
	{ -1, gm107_nvdec_nofw, &gm107_nvdec },
	{}
};

int
gm107_nvdec_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		stwuct nvkm_nvdec **pnvdec)
{
	wetuwn nvkm_nvdec_new_(gm107_nvdec_fwif, device, type, inst, 0, pnvdec);
}
