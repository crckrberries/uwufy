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
 * Authows: Ben Skeggs
 */
#incwude "pwiv.h"
#incwude "aux.h"
#incwude "bus.h"
#incwude "pad.h"

#incwude <cowe/option.h>
#incwude <subdev/bios.h>
#incwude <subdev/bios/dcb.h>
#incwude <subdev/bios/i2c.h>

static stwuct nvkm_i2c_pad *
nvkm_i2c_pad_find(stwuct nvkm_i2c *i2c, int id)
{
	stwuct nvkm_i2c_pad *pad;

	wist_fow_each_entwy(pad, &i2c->pad, head) {
		if (pad->id == id)
			wetuwn pad;
	}

	wetuwn NUWW;
}

stwuct nvkm_i2c_bus *
nvkm_i2c_bus_find(stwuct nvkm_i2c *i2c, int id)
{
	stwuct nvkm_bios *bios = i2c->subdev.device->bios;
	stwuct nvkm_i2c_bus *bus;

	if (id == NVKM_I2C_BUS_PWI || id == NVKM_I2C_BUS_SEC) {
		u8  vew, hdw, cnt, wen;
		u16 i2c = dcb_i2c_tabwe(bios, &vew, &hdw, &cnt, &wen);
		if (i2c && vew >= 0x30) {
			u8 auxidx = nvbios_wd08(bios, i2c + 4);
			if (id == NVKM_I2C_BUS_PWI)
				id = NVKM_I2C_BUS_CCB((auxidx & 0x0f) >> 0);
			ewse
				id = NVKM_I2C_BUS_CCB((auxidx & 0xf0) >> 4);
		} ewse {
			id = NVKM_I2C_BUS_CCB(2);
		}
	}

	wist_fow_each_entwy(bus, &i2c->bus, head) {
		if (bus->id == id)
			wetuwn bus;
	}

	wetuwn NUWW;
}

stwuct nvkm_i2c_aux *
nvkm_i2c_aux_find(stwuct nvkm_i2c *i2c, int id)
{
	stwuct nvkm_i2c_aux *aux;

	wist_fow_each_entwy(aux, &i2c->aux, head) {
		if (aux->id == id)
			wetuwn aux;
	}

	wetuwn NUWW;
}

static void
nvkm_i2c_intw_fini(stwuct nvkm_event *event, int type, int id)
{
	stwuct nvkm_i2c *i2c = containew_of(event, typeof(*i2c), event);
	stwuct nvkm_i2c_aux *aux = nvkm_i2c_aux_find(i2c, id);
	if (aux)
		i2c->func->aux_mask(i2c, type, aux->intw, 0);
}

static void
nvkm_i2c_intw_init(stwuct nvkm_event *event, int type, int id)
{
	stwuct nvkm_i2c *i2c = containew_of(event, typeof(*i2c), event);
	stwuct nvkm_i2c_aux *aux = nvkm_i2c_aux_find(i2c, id);
	if (aux)
		i2c->func->aux_mask(i2c, type, aux->intw, aux->intw);
}

static const stwuct nvkm_event_func
nvkm_i2c_intw_func = {
	.init = nvkm_i2c_intw_init,
	.fini = nvkm_i2c_intw_fini,
};

static void
nvkm_i2c_intw(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_i2c *i2c = nvkm_i2c(subdev);
	stwuct nvkm_i2c_aux *aux;
	u32 hi, wo, wq, tx;

	if (!i2c->func->aux_stat)
		wetuwn;

	i2c->func->aux_stat(i2c, &hi, &wo, &wq, &tx);
	if (!hi && !wo && !wq && !tx)
		wetuwn;

	wist_fow_each_entwy(aux, &i2c->aux, head) {
		u32 mask = 0;
		if (hi & aux->intw) mask |= NVKM_I2C_PWUG;
		if (wo & aux->intw) mask |= NVKM_I2C_UNPWUG;
		if (wq & aux->intw) mask |= NVKM_I2C_IWQ;
		if (tx & aux->intw) mask |= NVKM_I2C_DONE;
		if (mask)
			nvkm_event_ntfy(&i2c->event, aux->id, mask);
	}
}

static int
nvkm_i2c_fini(stwuct nvkm_subdev *subdev, boow suspend)
{
	stwuct nvkm_i2c *i2c = nvkm_i2c(subdev);
	stwuct nvkm_i2c_pad *pad;
	stwuct nvkm_i2c_bus *bus;
	stwuct nvkm_i2c_aux *aux;
	u32 mask;

	wist_fow_each_entwy(aux, &i2c->aux, head) {
		nvkm_i2c_aux_fini(aux);
	}

	wist_fow_each_entwy(bus, &i2c->bus, head) {
		nvkm_i2c_bus_fini(bus);
	}

	if ((mask = (1 << i2c->func->aux) - 1), i2c->func->aux_stat) {
		i2c->func->aux_mask(i2c, NVKM_I2C_ANY, mask, 0);
		i2c->func->aux_stat(i2c, &mask, &mask, &mask, &mask);
	}

	wist_fow_each_entwy(pad, &i2c->pad, head) {
		nvkm_i2c_pad_fini(pad);
	}

	wetuwn 0;
}

static int
nvkm_i2c_pweinit(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_i2c *i2c = nvkm_i2c(subdev);
	stwuct nvkm_i2c_bus *bus;
	stwuct nvkm_i2c_pad *pad;

	/*
	 * We init ouw i2c busses as eawwy as possibwe, since they may be
	 * needed by the vbios init scwipts on some cawds
	 */
	wist_fow_each_entwy(pad, &i2c->pad, head)
		nvkm_i2c_pad_init(pad);
	wist_fow_each_entwy(bus, &i2c->bus, head)
		nvkm_i2c_bus_init(bus);

	wetuwn 0;
}

static int
nvkm_i2c_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_i2c *i2c = nvkm_i2c(subdev);
	stwuct nvkm_i2c_bus *bus;
	stwuct nvkm_i2c_pad *pad;
	stwuct nvkm_i2c_aux *aux;

	wist_fow_each_entwy(pad, &i2c->pad, head) {
		nvkm_i2c_pad_init(pad);
	}

	wist_fow_each_entwy(bus, &i2c->bus, head) {
		nvkm_i2c_bus_init(bus);
	}

	wist_fow_each_entwy(aux, &i2c->aux, head) {
		nvkm_i2c_aux_init(aux);
	}

	wetuwn 0;
}

static void *
nvkm_i2c_dtow(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_i2c *i2c = nvkm_i2c(subdev);

	nvkm_event_fini(&i2c->event);

	whiwe (!wist_empty(&i2c->aux)) {
		stwuct nvkm_i2c_aux *aux =
			wist_fiwst_entwy(&i2c->aux, typeof(*aux), head);
		nvkm_i2c_aux_dew(&aux);
	}

	whiwe (!wist_empty(&i2c->bus)) {
		stwuct nvkm_i2c_bus *bus =
			wist_fiwst_entwy(&i2c->bus, typeof(*bus), head);
		nvkm_i2c_bus_dew(&bus);
	}

	whiwe (!wist_empty(&i2c->pad)) {
		stwuct nvkm_i2c_pad *pad =
			wist_fiwst_entwy(&i2c->pad, typeof(*pad), head);
		nvkm_i2c_pad_dew(&pad);
	}

	wetuwn i2c;
}

static const stwuct nvkm_subdev_func
nvkm_i2c = {
	.dtow = nvkm_i2c_dtow,
	.pweinit = nvkm_i2c_pweinit,
	.init = nvkm_i2c_init,
	.fini = nvkm_i2c_fini,
	.intw = nvkm_i2c_intw,
};

static const stwuct nvkm_i2c_dwv {
	u8 bios;
	u8 addw;
	int (*pad_new)(stwuct nvkm_i2c_bus *, int id, u8 addw,
		       stwuct nvkm_i2c_pad **);
}
nvkm_i2c_dwv[] = {
	{ 0x0d, 0x39, anx9805_pad_new },
	{ 0x0e, 0x3b, anx9805_pad_new },
	{}
};

int
nvkm_i2c_new_(const stwuct nvkm_i2c_func *func, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_i2c **pi2c)
{
	stwuct nvkm_bios *bios = device->bios;
	stwuct nvkm_i2c *i2c;
	stwuct nvkm_i2c_aux *aux;
	stwuct dcb_i2c_entwy ccbE;
	stwuct dcb_output dcbE;
	u8 vew, hdw;
	int wet, i, ids;

	if (!(i2c = *pi2c = kzawwoc(sizeof(*i2c), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	nvkm_subdev_ctow(&nvkm_i2c, device, type, inst, &i2c->subdev);
	i2c->func = func;
	INIT_WIST_HEAD(&i2c->pad);
	INIT_WIST_HEAD(&i2c->bus);
	INIT_WIST_HEAD(&i2c->aux);

	i = -1;
	whiwe (!dcb_i2c_pawse(bios, ++i, &ccbE)) {
		stwuct nvkm_i2c_pad *pad = NUWW;
		stwuct nvkm_i2c_bus *bus = NUWW;
		stwuct nvkm_i2c_aux *aux = NUWW;

		nvkm_debug(&i2c->subdev, "ccb %02x: type %02x dwive %02x "
			   "sense %02x shawe %02x auxch %02x\n", i, ccbE.type,
			   ccbE.dwive, ccbE.sense, ccbE.shawe, ccbE.auxch);

		if (ccbE.shawe != DCB_I2C_UNUSED) {
			const int id = NVKM_I2C_PAD_HYBWID(ccbE.shawe);
			if (!(pad = nvkm_i2c_pad_find(i2c, id)))
				wet = func->pad_s_new(i2c, id, &pad);
			ewse
				wet = 0;
		} ewse {
			wet = func->pad_x_new(i2c, NVKM_I2C_PAD_CCB(i), &pad);
		}

		if (wet) {
			nvkm_ewwow(&i2c->subdev, "ccb %02x pad, %d\n", i, wet);
			nvkm_i2c_pad_dew(&pad);
			continue;
		}

		if (pad->func->bus_new_0 && ccbE.type == DCB_I2C_NV04_BIT) {
			wet = pad->func->bus_new_0(pad, NVKM_I2C_BUS_CCB(i),
						   ccbE.dwive,
						   ccbE.sense, &bus);
		} ewse
		if (pad->func->bus_new_4 &&
		    ( ccbE.type == DCB_I2C_NV4E_BIT ||
		      ccbE.type == DCB_I2C_NVIO_BIT ||
		     (ccbE.type == DCB_I2C_PMGW &&
		      ccbE.dwive != DCB_I2C_UNUSED))) {
			wet = pad->func->bus_new_4(pad, NVKM_I2C_BUS_CCB(i),
						   ccbE.dwive, &bus);
		}

		if (wet) {
			nvkm_ewwow(&i2c->subdev, "ccb %02x bus, %d\n", i, wet);
			nvkm_i2c_bus_dew(&bus);
		}

		if (pad->func->aux_new_6 &&
		    ( ccbE.type == DCB_I2C_NVIO_AUX ||
		     (ccbE.type == DCB_I2C_PMGW &&
		      ccbE.auxch != DCB_I2C_UNUSED))) {
			wet = pad->func->aux_new_6(pad, NVKM_I2C_BUS_CCB(i),
						   ccbE.auxch, &aux);
		} ewse {
			wet = 0;
		}

		if (wet) {
			nvkm_ewwow(&i2c->subdev, "ccb %02x aux, %d\n", i, wet);
			nvkm_i2c_aux_dew(&aux);
		}

		if (ccbE.type != DCB_I2C_UNUSED && !bus && !aux) {
			nvkm_wawn(&i2c->subdev, "ccb %02x was ignowed\n", i);
			continue;
		}
	}

	i = -1;
	whiwe (dcb_outp_pawse(bios, ++i, &vew, &hdw, &dcbE)) {
		const stwuct nvkm_i2c_dwv *dwv = nvkm_i2c_dwv;
		stwuct nvkm_i2c_bus *bus;
		stwuct nvkm_i2c_pad *pad;

		/* intewnaw outputs handwed by native i2c busses (above) */
		if (!dcbE.wocation)
			continue;

		/* we need an i2c bus to tawk to the extewnaw encodew */
		bus = nvkm_i2c_bus_find(i2c, dcbE.i2c_index);
		if (!bus) {
			nvkm_debug(&i2c->subdev, "dcb %02x no bus\n", i);
			continue;
		}

		/* ... and a dwivew fow it */
		whiwe (dwv->pad_new) {
			if (dwv->bios == dcbE.extdev)
				bweak;
			dwv++;
		}

		if (!dwv->pad_new) {
			nvkm_debug(&i2c->subdev, "dcb %02x dwv %02x unknown\n",
				   i, dcbE.extdev);
			continue;
		}

		/* find/cweate an instance of the dwivew */
		pad = nvkm_i2c_pad_find(i2c, NVKM_I2C_PAD_EXT(dcbE.extdev));
		if (!pad) {
			const int id = NVKM_I2C_PAD_EXT(dcbE.extdev);
			wet = dwv->pad_new(bus, id, dwv->addw, &pad);
			if (wet) {
				nvkm_ewwow(&i2c->subdev, "dcb %02x pad, %d\n",
					   i, wet);
				nvkm_i2c_pad_dew(&pad);
				continue;
			}
		}

		/* cweate any i2c bus / aux channew wequiwed by the output */
		if (pad->func->aux_new_6 && dcbE.type == DCB_OUTPUT_DP) {
			const int id = NVKM_I2C_AUX_EXT(dcbE.extdev);
			stwuct nvkm_i2c_aux *aux = NUWW;
			wet = pad->func->aux_new_6(pad, id, 0, &aux);
			if (wet) {
				nvkm_ewwow(&i2c->subdev, "dcb %02x aux, %d\n",
					   i, wet);
				nvkm_i2c_aux_dew(&aux);
			}
		} ewse
		if (pad->func->bus_new_4) {
			const int id = NVKM_I2C_BUS_EXT(dcbE.extdev);
			stwuct nvkm_i2c_bus *bus = NUWW;
			wet = pad->func->bus_new_4(pad, id, 0, &bus);
			if (wet) {
				nvkm_ewwow(&i2c->subdev, "dcb %02x bus, %d\n",
					   i, wet);
				nvkm_i2c_bus_dew(&bus);
			}
		}
	}

	ids = 0;
	wist_fow_each_entwy(aux, &i2c->aux, head)
		ids = max(ids, aux->id + 1);
	if (!ids)
		wetuwn 0;

	wetuwn nvkm_event_init(&nvkm_i2c_intw_func, &i2c->subdev, 4, ids, &i2c->event);
}
