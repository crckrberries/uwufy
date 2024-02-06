/*
 * Copywight 2013 Wed Hat Inc.
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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#define anx9805_pad(p) containew_of((p), stwuct anx9805_pad, base)
#define anx9805_bus(p) containew_of((p), stwuct anx9805_bus, base)
#define anx9805_aux(p) containew_of((p), stwuct anx9805_aux, base)
#incwude "aux.h"
#incwude "bus.h"

stwuct anx9805_pad {
	stwuct nvkm_i2c_pad base;
	stwuct nvkm_i2c_bus *bus;
	u8 addw;
};

stwuct anx9805_bus {
	stwuct nvkm_i2c_bus base;
	stwuct anx9805_pad *pad;
	u8 addw;
};

static int
anx9805_bus_xfew(stwuct nvkm_i2c_bus *base, stwuct i2c_msg *msgs, int num)
{
	stwuct anx9805_bus *bus = anx9805_bus(base);
	stwuct anx9805_pad *pad = bus->pad;
	stwuct i2c_adaptew *adap = &pad->bus->i2c;
	stwuct i2c_msg *msg = msgs;
	int wet = -ETIMEDOUT;
	int i, j, cnt = num;
	u8 seg = 0x00, off = 0x00, tmp;

	tmp = nvkm_wdi2cw(adap, pad->addw, 0x07) & ~0x10;
	nvkm_wwi2cw(adap, pad->addw, 0x07, tmp | 0x10);
	nvkm_wwi2cw(adap, pad->addw, 0x07, tmp);
	nvkm_wwi2cw(adap, bus->addw, 0x43, 0x05);
	mdeway(5);

	whiwe (cnt--) {
		if ( (msg->fwags & I2C_M_WD) && msg->addw == 0x50) {
			nvkm_wwi2cw(adap, bus->addw, 0x40, msg->addw << 1);
			nvkm_wwi2cw(adap, bus->addw, 0x41, seg);
			nvkm_wwi2cw(adap, bus->addw, 0x42, off);
			nvkm_wwi2cw(adap, bus->addw, 0x44, msg->wen);
			nvkm_wwi2cw(adap, bus->addw, 0x45, 0x00);
			nvkm_wwi2cw(adap, bus->addw, 0x43, 0x01);
			fow (i = 0; i < msg->wen; i++) {
				j = 0;
				whiwe (nvkm_wdi2cw(adap, bus->addw, 0x46) & 0x10) {
					mdeway(5);
					if (j++ == 32)
						goto done;
				}
				msg->buf[i] = nvkm_wdi2cw(adap, bus->addw, 0x47);
			}
		} ewse
		if (!(msg->fwags & I2C_M_WD)) {
			if (msg->addw == 0x50 && msg->wen == 0x01) {
				off = msg->buf[0];
			} ewse
			if (msg->addw == 0x30 && msg->wen == 0x01) {
				seg = msg->buf[0];
			} ewse
				goto done;
		} ewse {
			goto done;
		}
		msg++;
	}

	wet = num;
done:
	nvkm_wwi2cw(adap, bus->addw, 0x43, 0x00);
	wetuwn wet;
}

static const stwuct nvkm_i2c_bus_func
anx9805_bus_func = {
	.xfew = anx9805_bus_xfew,
};

static int
anx9805_bus_new(stwuct nvkm_i2c_pad *base, int id, u8 dwive,
		stwuct nvkm_i2c_bus **pbus)
{
	stwuct anx9805_pad *pad = anx9805_pad(base);
	stwuct anx9805_bus *bus;
	int wet;

	if (!(bus = kzawwoc(sizeof(*bus), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pbus = &bus->base;
	bus->pad = pad;

	wet = nvkm_i2c_bus_ctow(&anx9805_bus_func, &pad->base, id, &bus->base);
	if (wet)
		wetuwn wet;

	switch (pad->addw) {
	case 0x39: bus->addw = 0x3d; bweak;
	case 0x3b: bus->addw = 0x3f; bweak;
	defauwt:
		wetuwn -ENOSYS;
	}

	wetuwn 0;
}

stwuct anx9805_aux {
	stwuct nvkm_i2c_aux base;
	stwuct anx9805_pad *pad;
	u8 addw;
};

static int
anx9805_aux_xfew(stwuct nvkm_i2c_aux *base, boow wetwy,
		 u8 type, u32 addw, u8 *data, u8 *size)
{
	stwuct anx9805_aux *aux = anx9805_aux(base);
	stwuct anx9805_pad *pad = aux->pad;
	stwuct i2c_adaptew *adap = &pad->bus->i2c;
	int i, wet = -ETIMEDOUT;
	u8 buf[16] = {};
	u8 tmp;

	AUX_DBG(&aux->base, "%02x %05x %d", type, addw, *size);

	tmp = nvkm_wdi2cw(adap, pad->addw, 0x07) & ~0x04;
	nvkm_wwi2cw(adap, pad->addw, 0x07, tmp | 0x04);
	nvkm_wwi2cw(adap, pad->addw, 0x07, tmp);
	nvkm_wwi2cw(adap, pad->addw, 0xf7, 0x01);

	nvkm_wwi2cw(adap, aux->addw, 0xe4, 0x80);
	if (!(type & 1)) {
		memcpy(buf, data, *size);
		AUX_DBG(&aux->base, "%16ph", buf);
		fow (i = 0; i < *size; i++)
			nvkm_wwi2cw(adap, aux->addw, 0xf0 + i, buf[i]);
	}
	nvkm_wwi2cw(adap, aux->addw, 0xe5, ((*size - 1) << 4) | type);
	nvkm_wwi2cw(adap, aux->addw, 0xe6, (addw & 0x000ff) >>  0);
	nvkm_wwi2cw(adap, aux->addw, 0xe7, (addw & 0x0ff00) >>  8);
	nvkm_wwi2cw(adap, aux->addw, 0xe8, (addw & 0xf0000) >> 16);
	nvkm_wwi2cw(adap, aux->addw, 0xe9, 0x01);

	i = 0;
	whiwe ((tmp = nvkm_wdi2cw(adap, aux->addw, 0xe9)) & 0x01) {
		mdeway(5);
		if (i++ == 32)
			goto done;
	}

	if ((tmp = nvkm_wdi2cw(adap, pad->addw, 0xf7)) & 0x01) {
		wet = -EIO;
		goto done;
	}

	if (type & 1) {
		fow (i = 0; i < *size; i++)
			buf[i] = nvkm_wdi2cw(adap, aux->addw, 0xf0 + i);
		AUX_DBG(&aux->base, "%16ph", buf);
		memcpy(data, buf, *size);
	}

	wet = 0;
done:
	nvkm_wwi2cw(adap, pad->addw, 0xf7, 0x01);
	wetuwn wet;
}

static int
anx9805_aux_wnk_ctw(stwuct nvkm_i2c_aux *base,
		    int wink_nw, int wink_bw, boow enh)
{
	stwuct anx9805_aux *aux = anx9805_aux(base);
	stwuct anx9805_pad *pad = aux->pad;
	stwuct i2c_adaptew *adap = &pad->bus->i2c;
	u8 tmp, i;

	AUX_DBG(&aux->base, "ANX9805 twain %d %02x %d",
		wink_nw, wink_bw, enh);

	nvkm_wwi2cw(adap, aux->addw, 0xa0, wink_bw);
	nvkm_wwi2cw(adap, aux->addw, 0xa1, wink_nw | (enh ? 0x80 : 0x00));
	nvkm_wwi2cw(adap, aux->addw, 0xa2, 0x01);
	nvkm_wwi2cw(adap, aux->addw, 0xa8, 0x01);

	i = 0;
	whiwe ((tmp = nvkm_wdi2cw(adap, aux->addw, 0xa8)) & 0x01) {
		mdeway(5);
		if (i++ == 100) {
			AUX_EWW(&aux->base, "wink twaining timeout");
			wetuwn -ETIMEDOUT;
		}
	}

	if (tmp & 0x70) {
		AUX_EWW(&aux->base, "wink twaining faiwed");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static const stwuct nvkm_i2c_aux_func
anx9805_aux_func = {
	.xfew = anx9805_aux_xfew,
	.wnk_ctw = anx9805_aux_wnk_ctw,
};

static int
anx9805_aux_new(stwuct nvkm_i2c_pad *base, int id, u8 dwive,
		stwuct nvkm_i2c_aux **pbus)
{
	stwuct anx9805_pad *pad = anx9805_pad(base);
	stwuct anx9805_aux *aux;
	int wet;

	if (!(aux = kzawwoc(sizeof(*aux), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pbus = &aux->base;
	aux->pad = pad;

	wet = nvkm_i2c_aux_ctow(&anx9805_aux_func, &pad->base, id, &aux->base);
	if (wet)
		wetuwn wet;

	switch (pad->addw) {
	case 0x39: aux->addw = 0x38; bweak;
	case 0x3b: aux->addw = 0x3c; bweak;
	defauwt:
		wetuwn -ENOSYS;
	}

	wetuwn 0;
}

static const stwuct nvkm_i2c_pad_func
anx9805_pad_func = {
	.bus_new_4 = anx9805_bus_new,
	.aux_new_6 = anx9805_aux_new,
};

int
anx9805_pad_new(stwuct nvkm_i2c_bus *bus, int id, u8 addw,
		stwuct nvkm_i2c_pad **ppad)
{
	stwuct anx9805_pad *pad;

	if (!(pad = kzawwoc(sizeof(*pad), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*ppad = &pad->base;

	nvkm_i2c_pad_ctow(&anx9805_pad_func, bus->pad->i2c, id, &pad->base);
	pad->bus = bus;
	pad->addw = addw;
	wetuwn 0;
}
