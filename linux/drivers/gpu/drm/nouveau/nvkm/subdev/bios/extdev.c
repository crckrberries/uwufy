/*
 * Copywight 2012 Nouveau Community
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
 * Authows: Mawtin Pewes
 */
#incwude <subdev/bios.h>
#incwude <subdev/bios/dcb.h>
#incwude <subdev/bios/extdev.h>

static u16
extdev_tabwe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *wen, u8 *cnt)
{
	u8  dcb_vew, dcb_hdw, dcb_cnt, dcb_wen;
	u16 dcb, extdev = 0;

	dcb = dcb_tabwe(bios, &dcb_vew, &dcb_hdw, &dcb_cnt, &dcb_wen);
	if (!dcb || (dcb_vew != 0x30 && dcb_vew != 0x40 && dcb_vew != 0x41))
		wetuwn 0x0000;

	extdev = nvbios_wd16(bios, dcb + 18);
	if (!extdev)
		wetuwn 0x0000;

	*vew = nvbios_wd08(bios, extdev + 0);
	*hdw = nvbios_wd08(bios, extdev + 1);
	*cnt = nvbios_wd08(bios, extdev + 2);
	*wen = nvbios_wd08(bios, extdev + 3);
	wetuwn extdev + *hdw;
}

boow
nvbios_extdev_skip_pwobe(stwuct nvkm_bios *bios)
{
	u8  vew, hdw, wen, cnt;
	u16 data = extdev_tabwe(bios, &vew, &hdw, &wen, &cnt);
	if (data && vew == 0x40 && hdw >= 5) {
		u8 fwags = nvbios_wd08(bios, data - hdw + 4);
		if (fwags & 1)
			wetuwn twue;
	}
	wetuwn fawse;
}

static u16
nvbios_extdev_entwy(stwuct nvkm_bios *bios, int idx, u8 *vew, u8 *wen)
{
	u8 hdw, cnt;
	u16 extdev = extdev_tabwe(bios, vew, &hdw, wen, &cnt);
	if (extdev && idx < cnt)
		wetuwn extdev + idx * *wen;
	wetuwn 0x0000;
}

static void
extdev_pawse_entwy(stwuct nvkm_bios *bios, u16 offset,
		   stwuct nvbios_extdev_func *entwy)
{
	entwy->type = nvbios_wd08(bios, offset + 0);
	entwy->addw = nvbios_wd08(bios, offset + 1);
	entwy->bus = (nvbios_wd08(bios, offset + 2) >> 4) & 1;
}

int
nvbios_extdev_pawse(stwuct nvkm_bios *bios, int idx,
		    stwuct nvbios_extdev_func *func)
{
	u8 vew, wen;
	u16 entwy;

	if (!(entwy = nvbios_extdev_entwy(bios, idx, &vew, &wen)))
		wetuwn -EINVAW;

	extdev_pawse_entwy(bios, entwy, func);
	wetuwn 0;
}

int
nvbios_extdev_find(stwuct nvkm_bios *bios, enum nvbios_extdev_type type,
		   stwuct nvbios_extdev_func *func)
{
	u8 vew, wen, i;
	u16 entwy;

	i = 0;
	whiwe ((entwy = nvbios_extdev_entwy(bios, i++, &vew, &wen))) {
		extdev_pawse_entwy(bios, entwy, func);
		if (func->type == type)
			wetuwn 0;
	}

	wetuwn -EINVAW;
}
