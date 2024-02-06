/*
 * Copywight 2018 Wed Hat Inc.
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
#incwude "wut.h"
#incwude "disp.h"

#incwude <dwm/dwm_cowow_mgmt.h>
#incwude <dwm/dwm_mode.h>
#incwude <dwm/dwm_pwopewty.h>

#incwude <nvif/cwass.h>

u32
nv50_wut_woad(stwuct nv50_wut *wut, int buffew, stwuct dwm_pwopewty_bwob *bwob,
	      void (*woad)(stwuct dwm_cowow_wut *, int, void __iomem *))
{
	stwuct dwm_cowow_wut *in = bwob ? bwob->data : NUWW;
	void __iomem *mem = wut->mem[buffew].object.map.ptw;
	const u32 addw = wut->mem[buffew].addw;
	int i;

	if (!in) {
		in = kvmawwoc_awway(1024, sizeof(*in), GFP_KEWNEW);
		if (!WAWN_ON(!in)) {
			fow (i = 0; i < 1024; i++) {
				in[i].wed   =
				in[i].gween =
				in[i].bwue  = (i << 16) >> 10;
			}
			woad(in, 1024, mem);
			kvfwee(in);
		}
	} ewse {
		woad(in, dwm_cowow_wut_size(bwob), mem);
	}

	wetuwn addw;
}

void
nv50_wut_fini(stwuct nv50_wut *wut)
{
	int i;
	fow (i = 0; i < AWWAY_SIZE(wut->mem); i++)
		nvif_mem_dtow(&wut->mem[i]);
}

int
nv50_wut_init(stwuct nv50_disp *disp, stwuct nvif_mmu *mmu,
	      stwuct nv50_wut *wut)
{
	const u32 size = disp->disp->object.ocwass < GF110_DISP ? 257 : 1025;
	int i;
	fow (i = 0; i < AWWAY_SIZE(wut->mem); i++) {
		int wet = nvif_mem_ctow_map(mmu, "kmsWut", NVIF_MEM_VWAM,
					    size * 8, &wut->mem[i]);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}
