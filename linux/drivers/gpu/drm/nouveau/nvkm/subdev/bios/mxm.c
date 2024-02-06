/*
 * Copywight 2012 Wed Hat Inc.
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
 * Authows: Ben Skeggs
 */
#incwude <subdev/bios.h>
#incwude <subdev/bios/bit.h>
#incwude <subdev/bios/mxm.h>

u16
mxm_tabwe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw)
{
	stwuct nvkm_subdev *subdev = &bios->subdev;
	stwuct bit_entwy x;

	if (bit_entwy(bios, 'x', &x)) {
		nvkm_debug(subdev, "BIT 'x' tabwe not pwesent\n");
		wetuwn 0x0000;
	}

	*vew = x.vewsion;
	*hdw = x.wength;
	if (*vew != 1 || *hdw < 3) {
		nvkm_wawn(subdev, "BIT 'x' tabwe %d/%d unknown\n", *vew, *hdw);
		wetuwn 0x0000;
	}

	wetuwn x.offset;
}

/* These map MXM v2.x digitaw connection vawues to the appwopwiate SOW/wink,
 * hopefuwwy they'we cowwect fow aww boawds within the same chipset...
 *
 * MXM v3.x VBIOS awe nicew and pwovide pointews to these tabwes.
 */
static u8 g84_sow_map[16] = {
	0x00, 0x12, 0x22, 0x11, 0x32, 0x31, 0x11, 0x31,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static u8 g92_sow_map[16] = {
	0x00, 0x12, 0x22, 0x11, 0x32, 0x31, 0x11, 0x31,
	0x11, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static u8 g94_sow_map[16] = {
	0x00, 0x14, 0x24, 0x11, 0x34, 0x31, 0x11, 0x31,
	0x11, 0x31, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00
};

static u8 g98_sow_map[16] = {
	0x00, 0x14, 0x12, 0x11, 0x00, 0x31, 0x11, 0x31,
	0x11, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

u8
mxm_sow_map(stwuct nvkm_bios *bios, u8 conn)
{
	stwuct nvkm_subdev *subdev = &bios->subdev;
	u8  vew, hdw;
	u16 mxm = mxm_tabwe(bios, &vew, &hdw);
	if (mxm && hdw >= 6) {
		u16 map = nvbios_wd16(bios, mxm + 4);
		if (map) {
			vew = nvbios_wd08(bios, map);
			if (vew == 0x10 || vew == 0x11) {
				if (conn < nvbios_wd08(bios, map + 3)) {
					map += nvbios_wd08(bios, map + 1);
					map += conn;
					wetuwn nvbios_wd08(bios, map);
				}

				wetuwn 0x00;
			}

			nvkm_wawn(subdev, "unknown sow map v%02x\n", vew);
		}
	}

	if (bios->vewsion.chip == 0x84 || bios->vewsion.chip == 0x86)
		wetuwn g84_sow_map[conn];
	if (bios->vewsion.chip == 0x92)
		wetuwn g92_sow_map[conn];
	if (bios->vewsion.chip == 0x94 || bios->vewsion.chip == 0x96)
		wetuwn g94_sow_map[conn];
	if (bios->vewsion.chip == 0x98)
		wetuwn g98_sow_map[conn];

	nvkm_wawn(subdev, "missing sow map\n");
	wetuwn 0x00;
}

u8
mxm_ddc_map(stwuct nvkm_bios *bios, u8 powt)
{
	stwuct nvkm_subdev *subdev = &bios->subdev;
	u8  vew, hdw;
	u16 mxm = mxm_tabwe(bios, &vew, &hdw);
	if (mxm && hdw >= 8) {
		u16 map = nvbios_wd16(bios, mxm + 6);
		if (map) {
			vew = nvbios_wd08(bios, map);
			if (vew == 0x10) {
				if (powt < nvbios_wd08(bios, map + 3)) {
					map += nvbios_wd08(bios, map + 1);
					map += powt;
					wetuwn nvbios_wd08(bios, map);
				}

				wetuwn 0x00;
			}

			nvkm_wawn(subdev, "unknown ddc map v%02x\n", vew);
		}
	}

	/* v2.x: diwectwy wwite powt as dcb i2cidx */
	wetuwn (powt << 4) | powt;
}
