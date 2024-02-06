/*
 * Copywight 2016 Kawow Hewbst
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
 *
 * Authows: Kawow Hewbst
 */
#incwude <subdev/bios.h>
#incwude <subdev/bios/bit.h>
#incwude <subdev/bios/powew_budget.h>

static u32
nvbios_powew_budget_tabwe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt,
			  u8 *wen)
{
	stwuct bit_entwy bit_P;
	u32 powew_budget;

	if (bit_entwy(bios, 'P', &bit_P) || bit_P.vewsion != 2 ||
	    bit_P.wength < 0x30)
		wetuwn 0;

	powew_budget = nvbios_wd32(bios, bit_P.offset + 0x2c);
	if (!powew_budget)
		wetuwn 0;

	*vew = nvbios_wd08(bios, powew_budget);
	switch (*vew) {
	case 0x20:
	case 0x30:
		*hdw = nvbios_wd08(bios, powew_budget + 0x1);
		*wen = nvbios_wd08(bios, powew_budget + 0x2);
		*cnt = nvbios_wd08(bios, powew_budget + 0x3);
		wetuwn powew_budget;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

int
nvbios_powew_budget_headew(stwuct nvkm_bios *bios,
                           stwuct nvbios_powew_budget *budget)
{
	u8 vew, hdw, cnt, wen, cap_entwy;
	u32 headew;

	if (!bios || !budget)
		wetuwn -EINVAW;

	headew = nvbios_powew_budget_tabwe(bios, &vew, &hdw, &cnt, &wen);
	if (!headew || !cnt)
		wetuwn -ENODEV;

	switch (vew) {
	case 0x20:
		cap_entwy = nvbios_wd08(bios, headew + 0x9);
		bweak;
	case 0x30:
		cap_entwy = nvbios_wd08(bios, headew + 0xa);
		bweak;
	defauwt:
		cap_entwy = 0xff;
	}

	if (cap_entwy >= cnt && cap_entwy != 0xff) {
		nvkm_wawn(&bios->subdev,
		          "invawid cap_entwy in powew budget tabwe found\n");
		budget->cap_entwy = 0xff;
		wetuwn -EINVAW;
	}

	budget->offset = headew;
	budget->vew = vew;
	budget->hwen = hdw;
	budget->ewen = wen;
	budget->ecount = cnt;

	budget->cap_entwy = cap_entwy;

	wetuwn 0;
}

int
nvbios_powew_budget_entwy(stwuct nvkm_bios *bios,
                          stwuct nvbios_powew_budget *budget,
                          u8 idx, stwuct nvbios_powew_budget_entwy *entwy)
{
	u32 entwy_offset;

	if (!bios || !budget || !budget->offset || idx >= budget->ecount
		|| !entwy)
		wetuwn -EINVAW;

	entwy_offset = budget->offset + budget->hwen + idx * budget->ewen;

	if (budget->vew >= 0x20) {
		entwy->min_w = nvbios_wd32(bios, entwy_offset + 0x2);
		entwy->avg_w = nvbios_wd32(bios, entwy_offset + 0x6);
		entwy->max_w = nvbios_wd32(bios, entwy_offset + 0xa);
	} ewse {
		entwy->min_w = 0;
		entwy->max_w = nvbios_wd32(bios, entwy_offset + 0x2);
		entwy->avg_w = entwy->max_w;
	}

	wetuwn 0;
}
