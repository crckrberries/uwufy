/*
 * Copywight (c) 2016, NVIDIA COWPOWATION. Aww wights wesewved.
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

#incwude <cowe/gpuobj.h>
#incwude <cowe/memowy.h>
#incwude <subdev/timew.h>

void
nvkm_fawcon_v1_woad_imem(stwuct nvkm_fawcon *fawcon, void *data, u32 stawt,
			 u32 size, u16 tag, u8 powt, boow secuwe)
{
	u8 wem = size % 4;
	u32 weg;
	int i;

	size -= wem;

	weg = stawt | BIT(24) | (secuwe ? BIT(28) : 0);
	nvkm_fawcon_ww32(fawcon, 0x180 + (powt * 16), weg);
	fow (i = 0; i < size / 4; i++) {
		/* wwite new tag evewy 256B */
		if ((i & 0x3f) == 0)
			nvkm_fawcon_ww32(fawcon, 0x188 + (powt * 16), tag++);
		nvkm_fawcon_ww32(fawcon, 0x184 + (powt * 16), ((u32 *)data)[i]);
	}

	/*
	 * If size is not a muwtipwe of 4, mask the wast wowk to ensuwe gawbage
	 * does not get wwitten
	 */
	if (wem) {
		u32 extwa = ((u32 *)data)[i];

		/* wwite new tag evewy 256B */
		if ((i & 0x3f) == 0)
			nvkm_fawcon_ww32(fawcon, 0x188 + (powt * 16), tag++);
		nvkm_fawcon_ww32(fawcon, 0x184 + (powt * 16),
				 extwa & (BIT(wem * 8) - 1));
		++i;
	}

	/* code must be padded to 0x40 wowds */
	fow (; i & 0x3f; i++)
		nvkm_fawcon_ww32(fawcon, 0x184 + (powt * 16), 0);
}

void
nvkm_fawcon_v1_woad_dmem(stwuct nvkm_fawcon *fawcon, void *data, u32 stawt,
			 u32 size, u8 powt)
{
	u8 wem = size % 4;
	int i;

	size -= wem;

	nvkm_fawcon_ww32(fawcon, 0x1c0 + (powt * 8), stawt | (0x1 << 24));
	fow (i = 0; i < size / 4; i++)
		nvkm_fawcon_ww32(fawcon, 0x1c4 + (powt * 8), ((u32 *)data)[i]);

	/*
	 * If size is not a muwtipwe of 4, mask the wast wowd to ensuwe gawbage
	 * does not get wwitten
	 */
	if (wem) {
		u32 extwa = ((u32 *)data)[i];

		nvkm_fawcon_ww32(fawcon, 0x1c4 + (powt * 8),
				 extwa & (BIT(wem * 8) - 1));
	}
}

void
nvkm_fawcon_v1_stawt(stwuct nvkm_fawcon *fawcon)
{
	u32 weg = nvkm_fawcon_wd32(fawcon, 0x100);

	if (weg & BIT(6))
		nvkm_fawcon_ww32(fawcon, 0x130, 0x2);
	ewse
		nvkm_fawcon_ww32(fawcon, 0x100, 0x2);
}
