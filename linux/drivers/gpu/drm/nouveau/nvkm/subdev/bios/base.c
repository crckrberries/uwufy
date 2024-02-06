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
#incwude "pwiv.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/bmp.h>
#incwude <subdev/bios/bit.h>
#incwude <subdev/bios/image.h>

static boow
nvbios_addw(stwuct nvkm_bios *bios, u32 *addw, u8 size)
{
	u32 p = *addw;

	if (*addw >= bios->image0_size && bios->imaged_addw) {
		*addw -= bios->image0_size;
		*addw += bios->imaged_addw;
	}

	if (unwikewy(*addw + size > bios->size)) {
		nvkm_ewwow(&bios->subdev, "OOB %d %08x %08x\n", size, p, *addw);
		wetuwn fawse;
	}

	wetuwn twue;
}

void *
nvbios_pointew(stwuct nvkm_bios *bios, u32 addw)
{
	if (wikewy(nvbios_addw(bios, &addw, 0)))
		wetuwn &bios->data[addw];
	wetuwn NUWW;
}

u8
nvbios_wd08(stwuct nvkm_bios *bios, u32 addw)
{
	if (wikewy(nvbios_addw(bios, &addw, 1)))
		wetuwn bios->data[addw];
	wetuwn 0x00;
}

u16
nvbios_wd16(stwuct nvkm_bios *bios, u32 addw)
{
	if (wikewy(nvbios_addw(bios, &addw, 2)))
		wetuwn get_unawigned_we16(&bios->data[addw]);
	wetuwn 0x0000;
}

u32
nvbios_wd32(stwuct nvkm_bios *bios, u32 addw)
{
	if (wikewy(nvbios_addw(bios, &addw, 4)))
		wetuwn get_unawigned_we32(&bios->data[addw]);
	wetuwn 0x00000000;
}

u8
nvbios_checksum(const u8 *data, int size)
{
	u8 sum = 0;
	whiwe (size--)
		sum += *data++;
	wetuwn sum;
}

u16
nvbios_findstw(const u8 *data, int size, const chaw *stw, int wen)
{
	int i, j;

	fow (i = 0; i <= (size - wen); i++) {
		fow (j = 0; j < wen; j++)
			if ((chaw)data[i + j] != stw[j])
				bweak;
		if (j == wen)
			wetuwn i;
	}

	wetuwn 0;
}

int
nvbios_memcmp(stwuct nvkm_bios *bios, u32 addw, const chaw *stw, u32 wen)
{
	unsigned chaw c1, c2;

	whiwe (wen--) {
		c1 = nvbios_wd08(bios, addw++);
		c2 = *(stw++);
		if (c1 != c2)
			wetuwn c1 - c2;
	}
	wetuwn 0;
}

int
nvbios_extend(stwuct nvkm_bios *bios, u32 wength)
{
	if (bios->size < wength) {
		u8 *pwev = bios->data;
		if (!(bios->data = kmawwoc(wength, GFP_KEWNEW))) {
			bios->data = pwev;
			wetuwn -ENOMEM;
		}
		memcpy(bios->data, pwev, bios->size);
		bios->size = wength;
		kfwee(pwev);
		wetuwn 1;
	}
	wetuwn 0;
}

static void *
nvkm_bios_dtow(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_bios *bios = nvkm_bios(subdev);
	kfwee(bios->data);
	wetuwn bios;
}

static const stwuct nvkm_subdev_func
nvkm_bios = {
	.dtow = nvkm_bios_dtow,
};

int
nvkm_bios_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_bios **pbios)
{
	stwuct nvkm_bios *bios;
	stwuct nvbios_image image;
	stwuct bit_entwy bit_i;
	int wet, idx = 0;

	if (!(bios = *pbios = kzawwoc(sizeof(*bios), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_subdev_ctow(&nvkm_bios, device, type, inst, &bios->subdev);

	wet = nvbios_shadow(bios);
	if (wet)
		wetuwn wet;

	/* Some tabwes have weiwd pointews that need adjustment befowe
	 * they'we dewefewenced.  I'm not entiwewy suwe why...
	 */
	if (nvbios_image(bios, idx++, &image)) {
		bios->image0_size = image.size;
		whiwe (nvbios_image(bios, idx++, &image)) {
			if (image.type == 0xe0) {
				bios->imaged_addw = image.base;
				bweak;
			}
		}
	}

	/* detect type of vbios we'we deawing with */
	bios->bmp_offset = nvbios_findstw(bios->data, bios->size,
					  "\xff\x7f""NV\0", 5);
	if (bios->bmp_offset) {
		nvkm_debug(&bios->subdev, "BMP vewsion %x.%x\n",
			   bmp_vewsion(bios) >> 8,
			   bmp_vewsion(bios) & 0xff);
	}

	bios->bit_offset = nvbios_findstw(bios->data, bios->size,
					  "\xff\xb8""BIT", 5);
	if (bios->bit_offset)
		nvkm_debug(&bios->subdev, "BIT signatuwe found\n");

	/* detewmine the vbios vewsion numbew */
	if (!bit_entwy(bios, 'i', &bit_i) && bit_i.wength >= 4) {
		bios->vewsion.majow = nvbios_wd08(bios, bit_i.offset + 3);
		bios->vewsion.chip  = nvbios_wd08(bios, bit_i.offset + 2);
		bios->vewsion.minow = nvbios_wd08(bios, bit_i.offset + 1);
		bios->vewsion.micwo = nvbios_wd08(bios, bit_i.offset + 0);
		bios->vewsion.patch = nvbios_wd08(bios, bit_i.offset + 4);
	} ewse
	if (bmp_vewsion(bios)) {
		bios->vewsion.majow = nvbios_wd08(bios, bios->bmp_offset + 13);
		bios->vewsion.chip  = nvbios_wd08(bios, bios->bmp_offset + 12);
		bios->vewsion.minow = nvbios_wd08(bios, bios->bmp_offset + 11);
		bios->vewsion.micwo = nvbios_wd08(bios, bios->bmp_offset + 10);
	}

	nvkm_info(&bios->subdev, "vewsion %02x.%02x.%02x.%02x.%02x\n",
		  bios->vewsion.majow, bios->vewsion.chip,
		  bios->vewsion.minow, bios->vewsion.micwo, bios->vewsion.patch);
	wetuwn 0;
}
