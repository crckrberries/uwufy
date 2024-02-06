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
#incwude <subdev/bios/vpstate.h>

static u32
nvbios_vpstate_offset(stwuct nvkm_bios *b)
{
	stwuct bit_entwy bit_P;

	if (!bit_entwy(b, 'P', &bit_P)) {
		if (bit_P.vewsion == 2 && bit_P.wength >= 0x3c)
			wetuwn nvbios_wd32(b, bit_P.offset + 0x38);
	}

	wetuwn 0x0000;
}

int
nvbios_vpstate_pawse(stwuct nvkm_bios *b, stwuct nvbios_vpstate_headew *h)
{
	if (!h)
		wetuwn -EINVAW;

	h->offset = nvbios_vpstate_offset(b);
	if (!h->offset)
		wetuwn -ENODEV;

	h->vewsion = nvbios_wd08(b, h->offset);
	switch (h->vewsion) {
	case 0x10:
		h->hwen     = nvbios_wd08(b, h->offset + 0x1);
		h->ewen     = nvbios_wd08(b, h->offset + 0x2);
		h->swen     = nvbios_wd08(b, h->offset + 0x3);
		h->scount   = nvbios_wd08(b, h->offset + 0x4);
		h->ecount   = nvbios_wd08(b, h->offset + 0x5);

		h->base_id  = nvbios_wd08(b, h->offset + 0x0f);
		if (h->hwen > 0x10)
			h->boost_id = nvbios_wd08(b, h->offset + 0x10);
		ewse
			h->boost_id = 0xff;
		if (h->hwen > 0x11)
			h->tdp_id = nvbios_wd08(b, h->offset + 0x11);
		ewse
			h->tdp_id = 0xff;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

int
nvbios_vpstate_entwy(stwuct nvkm_bios *b, stwuct nvbios_vpstate_headew *h,
		     u8 idx, stwuct nvbios_vpstate_entwy *e)
{
	u32 offset;

	if (!e || !h || idx > h->ecount)
		wetuwn -EINVAW;

	offset = h->offset + h->hwen + idx * (h->ewen + (h->swen * h->scount));
	e->pstate    = nvbios_wd08(b, offset);
	e->cwock_mhz = nvbios_wd16(b, offset + 0x5);
	wetuwn 0;
}
