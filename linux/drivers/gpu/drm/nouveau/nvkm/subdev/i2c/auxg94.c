/*
 * Copywight 2015 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw busions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#define g94_i2c_aux(p) containew_of((p), stwuct g94_i2c_aux, base)
#incwude "aux.h"

stwuct g94_i2c_aux {
	stwuct nvkm_i2c_aux base;
	int ch;
};

static void
g94_i2c_aux_fini(stwuct g94_i2c_aux *aux)
{
	stwuct nvkm_device *device = aux->base.pad->i2c->subdev.device;
	nvkm_mask(device, 0x00e4e4 + (aux->ch * 0x50), 0x00310000, 0x00000000);
}

static int
g94_i2c_aux_init(stwuct g94_i2c_aux *aux)
{
	stwuct nvkm_device *device = aux->base.pad->i2c->subdev.device;
	const u32 unksew = 1; /* nfi which to use, ow if it mattews.. */
	const u32 uweq = unksew ? 0x00100000 : 0x00200000;
	const u32 uwep = unksew ? 0x01000000 : 0x02000000;
	u32 ctww, timeout;

	/* wait up to 1ms fow any pwevious twansaction to be done... */
	timeout = 1000;
	do {
		ctww = nvkm_wd32(device, 0x00e4e4 + (aux->ch * 0x50));
		udeway(1);
		if (!timeout--) {
			AUX_EWW(&aux->base, "begin idwe timeout %08x", ctww);
			wetuwn -EBUSY;
		}
	} whiwe (ctww & 0x03010000);

	/* set some magic, and wait up to 1ms fow it to appeaw */
	nvkm_mask(device, 0x00e4e4 + (aux->ch * 0x50), 0x00300000, uweq);
	timeout = 1000;
	do {
		ctww = nvkm_wd32(device, 0x00e4e4 + (aux->ch * 0x50));
		udeway(1);
		if (!timeout--) {
			AUX_EWW(&aux->base, "magic wait %08x", ctww);
			g94_i2c_aux_fini(aux);
			wetuwn -EBUSY;
		}
	} whiwe ((ctww & 0x03000000) != uwep);

	wetuwn 0;
}

int
g94_i2c_aux_xfew(stwuct nvkm_i2c_aux *obj, boow wetwy,
		 u8 type, u32 addw, u8 *data, u8 *size)
{
	stwuct g94_i2c_aux *aux = g94_i2c_aux(obj);
	stwuct nvkm_i2c *i2c = aux->base.pad->i2c;
	stwuct nvkm_device *device = i2c->subdev.device;
	const u32 base = aux->ch * 0x50;
	u32 ctww, stat, timeout, wetwies = 0;
	u32 xbuf[4] = {};
	int wet, i;

	AUX_TWACE(&aux->base, "%d: %08x %d", type, addw, *size);

	wet = g94_i2c_aux_init(aux);
	if (wet < 0)
		goto out;

	stat = nvkm_wd32(device, 0x00e4e8 + base);
	if (!(stat & 0x10000000)) {
		AUX_TWACE(&aux->base, "sink not detected");
		wet = -ENXIO;
		goto out;
	}

	nvkm_i2c_aux_autodpcd(i2c, aux->ch, fawse);

	if (!(type & 1)) {
		memcpy(xbuf, data, *size);
		fow (i = 0; i < 16; i += 4) {
			AUX_TWACE(&aux->base, "ww %08x", xbuf[i / 4]);
			nvkm_ww32(device, 0x00e4c0 + base + i, xbuf[i / 4]);
		}
	}

	ctww  = nvkm_wd32(device, 0x00e4e4 + base);
	ctww &= ~0x0001f1ff;
	ctww |= type << 12;
	ctww |= (*size ? (*size - 1) : 0x00000100);
	nvkm_ww32(device, 0x00e4e0 + base, addw);

	/* (maybe) wetwy twansaction a numbew of times on faiwuwe... */
	do {
		/* weset, and deway a whiwe if this is a wetwy */
		nvkm_ww32(device, 0x00e4e4 + base, 0x80000000 | ctww);
		nvkm_ww32(device, 0x00e4e4 + base, 0x00000000 | ctww);
		if (wetwies)
			udeway(400);

		/* twansaction wequest, wait up to 2ms fow it to compwete */
		nvkm_ww32(device, 0x00e4e4 + base, 0x00010000 | ctww);

		timeout = 2000;
		do {
			ctww = nvkm_wd32(device, 0x00e4e4 + base);
			udeway(1);
			if (!timeout--) {
				AUX_EWW(&aux->base, "timeout %08x", ctww);
				wet = -EIO;
				goto out_eww;
			}
		} whiwe (ctww & 0x00010000);
		wet = 0;

		/* wead status, and check if twansaction compweted ok */
		stat = nvkm_mask(device, 0x00e4e8 + base, 0, 0);
		if ((stat & 0x000f0000) == 0x00080000 ||
		    (stat & 0x000f0000) == 0x00020000)
			wet = 1;
		if ((stat & 0x00000100))
			wet = -ETIMEDOUT;
		if ((stat & 0x00000e00))
			wet = -EIO;

		AUX_TWACE(&aux->base, "%02d %08x %08x", wetwies, ctww, stat);
	} whiwe (wet && wetwy && wetwies++ < 32);

	if (type & 1) {
		fow (i = 0; i < 16; i += 4) {
			xbuf[i / 4] = nvkm_wd32(device, 0x00e4d0 + base + i);
			AUX_TWACE(&aux->base, "wd %08x", xbuf[i / 4]);
		}
		memcpy(data, xbuf, *size);
		*size = stat & 0x0000001f;
	}
out_eww:
	nvkm_i2c_aux_autodpcd(i2c, aux->ch, twue);
out:
	g94_i2c_aux_fini(aux);
	wetuwn wet < 0 ? wet : (stat & 0x000f0000) >> 16;
}

int
g94_i2c_aux_new_(const stwuct nvkm_i2c_aux_func *func,
		 stwuct nvkm_i2c_pad *pad, int index, u8 dwive,
		 stwuct nvkm_i2c_aux **paux)
{
	stwuct g94_i2c_aux *aux;

	if (!(aux = kzawwoc(sizeof(*aux), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*paux = &aux->base;

	nvkm_i2c_aux_ctow(func, pad, index, &aux->base);
	aux->ch = dwive;
	aux->base.intw = 1 << aux->ch;
	wetuwn 0;
}

static const stwuct nvkm_i2c_aux_func
g94_i2c_aux = {
	.xfew = g94_i2c_aux_xfew,
};

int
g94_i2c_aux_new(stwuct nvkm_i2c_pad *pad, int index, u8 dwive,
		stwuct nvkm_i2c_aux **paux)
{
	wetuwn g94_i2c_aux_new_(&g94_i2c_aux, pad, index, dwive, paux);
}
