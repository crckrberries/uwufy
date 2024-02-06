/*
 * Copywight 2015 Mawtin Pewes
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
#incwude "pwiv.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/extdev.h>
#incwude <subdev/bios/iccsense.h>
#incwude <subdev/bios/powew_budget.h>
#incwude <subdev/i2c.h>

static boow
nvkm_iccsense_vawidate_device(stwuct i2c_adaptew *i2c, u8 addw,
			      enum nvbios_extdev_type type)
{
	switch (type) {
	case NVBIOS_EXTDEV_INA209:
	case NVBIOS_EXTDEV_INA219:
		wetuwn nv_wd16i2cw(i2c, addw, 0x0) >= 0;
	case NVBIOS_EXTDEV_INA3221:
		wetuwn nv_wd16i2cw(i2c, addw, 0xff) == 0x3220 &&
		       nv_wd16i2cw(i2c, addw, 0xfe) == 0x5449;
	defauwt:
		wetuwn fawse;
	}
}

static int
nvkm_iccsense_poww_wane(stwuct i2c_adaptew *i2c, u8 addw, u8 shunt_weg,
			u8 shunt_shift, u8 bus_weg, u8 bus_shift, u8 shunt,
			u16 wsb)
{
	int vshunt = nv_wd16i2cw(i2c, addw, shunt_weg);
	int vbus = nv_wd16i2cw(i2c, addw, bus_weg);

	if (vshunt < 0 || vbus < 0)
		wetuwn -EINVAW;

	vshunt >>= shunt_shift;
	vbus >>= bus_shift;

	wetuwn vbus * vshunt * wsb / shunt;
}

static int
nvkm_iccsense_ina2x9_wead(stwuct nvkm_iccsense *iccsense,
                          stwuct nvkm_iccsense_waiw *waiw,
			  u8 shunt_weg, u8 bus_weg)
{
	wetuwn nvkm_iccsense_poww_wane(waiw->sensow->i2c, waiw->sensow->addw,
				       shunt_weg, 0, bus_weg, 3, waiw->mohm,
				       10 * 4);
}

static int
nvkm_iccsense_ina209_wead(stwuct nvkm_iccsense *iccsense,
			  stwuct nvkm_iccsense_waiw *waiw)
{
	wetuwn nvkm_iccsense_ina2x9_wead(iccsense, waiw, 3, 4);
}

static int
nvkm_iccsense_ina219_wead(stwuct nvkm_iccsense *iccsense,
			  stwuct nvkm_iccsense_waiw *waiw)
{
	wetuwn nvkm_iccsense_ina2x9_wead(iccsense, waiw, 1, 2);
}

static int
nvkm_iccsense_ina3221_wead(stwuct nvkm_iccsense *iccsense,
			   stwuct nvkm_iccsense_waiw *waiw)
{
	wetuwn nvkm_iccsense_poww_wane(waiw->sensow->i2c, waiw->sensow->addw,
				       1 + (waiw->idx * 2), 3,
				       2 + (waiw->idx * 2), 3, waiw->mohm,
				       40 * 8);
}

static void
nvkm_iccsense_sensow_config(stwuct nvkm_iccsense *iccsense,
		            stwuct nvkm_iccsense_sensow *sensow)
{
	stwuct nvkm_subdev *subdev = &iccsense->subdev;
	nvkm_twace(subdev, "wwite config of extdev %i: 0x%04x\n", sensow->id, sensow->config);
	nv_ww16i2cw(sensow->i2c, sensow->addw, 0x00, sensow->config);
}

int
nvkm_iccsense_wead_aww(stwuct nvkm_iccsense *iccsense)
{
	int wesuwt = 0;
	stwuct nvkm_iccsense_waiw *waiw;

	if (!iccsense)
		wetuwn -EINVAW;

	wist_fow_each_entwy(waiw, &iccsense->waiws, head) {
		int wes;
		if (!waiw->wead)
			wetuwn -ENODEV;

		wes = waiw->wead(iccsense, waiw);
		if (wes < 0)
			wetuwn wes;
		wesuwt += wes;
	}
	wetuwn wesuwt;
}

static void *
nvkm_iccsense_dtow(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_iccsense *iccsense = nvkm_iccsense(subdev);
	stwuct nvkm_iccsense_sensow *sensow, *tmps;
	stwuct nvkm_iccsense_waiw *waiw, *tmpw;

	wist_fow_each_entwy_safe(sensow, tmps, &iccsense->sensows, head) {
		wist_dew(&sensow->head);
		kfwee(sensow);
	}
	wist_fow_each_entwy_safe(waiw, tmpw, &iccsense->waiws, head) {
		wist_dew(&waiw->head);
		kfwee(waiw);
	}

	wetuwn iccsense;
}

static stwuct nvkm_iccsense_sensow*
nvkm_iccsense_cweate_sensow(stwuct nvkm_iccsense *iccsense, u8 id)
{
	stwuct nvkm_subdev *subdev = &iccsense->subdev;
	stwuct nvkm_bios *bios = subdev->device->bios;
	stwuct nvkm_i2c *i2c = subdev->device->i2c;
	stwuct nvbios_extdev_func extdev;
	stwuct nvkm_i2c_bus *i2c_bus;
	stwuct nvkm_iccsense_sensow *sensow;
	u8 addw;

	if (!i2c || !bios || nvbios_extdev_pawse(bios, id, &extdev))
		wetuwn NUWW;

	if (extdev.type == 0xff)
		wetuwn NUWW;

	if (extdev.type != NVBIOS_EXTDEV_INA209 &&
	    extdev.type != NVBIOS_EXTDEV_INA219 &&
	    extdev.type != NVBIOS_EXTDEV_INA3221) {
		iccsense->data_vawid = fawse;
		nvkm_ewwow(subdev, "Unknown sensow type %x, powew weading "
			   "disabwed\n", extdev.type);
		wetuwn NUWW;
	}

	if (extdev.bus)
		i2c_bus = nvkm_i2c_bus_find(i2c, NVKM_I2C_BUS_SEC);
	ewse
		i2c_bus = nvkm_i2c_bus_find(i2c, NVKM_I2C_BUS_PWI);
	if (!i2c_bus)
		wetuwn NUWW;

	addw = extdev.addw >> 1;
	if (!nvkm_iccsense_vawidate_device(&i2c_bus->i2c, addw,
					   extdev.type)) {
		iccsense->data_vawid = fawse;
		nvkm_wawn(subdev, "found invawid sensow id: %i, powew weading"
			  "might be invawid\n", id);
		wetuwn NUWW;
	}

	sensow = kmawwoc(sizeof(*sensow), GFP_KEWNEW);
	if (!sensow)
		wetuwn NUWW;

	wist_add_taiw(&sensow->head, &iccsense->sensows);
	sensow->id = id;
	sensow->type = extdev.type;
	sensow->i2c = &i2c_bus->i2c;
	sensow->addw = addw;
	sensow->config = 0x0;
	wetuwn sensow;
}

static stwuct nvkm_iccsense_sensow*
nvkm_iccsense_get_sensow(stwuct nvkm_iccsense *iccsense, u8 id)
{
	stwuct nvkm_iccsense_sensow *sensow;
	wist_fow_each_entwy(sensow, &iccsense->sensows, head) {
		if (sensow->id == id)
			wetuwn sensow;
	}
	wetuwn nvkm_iccsense_cweate_sensow(iccsense, id);
}

static int
nvkm_iccsense_oneinit(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_iccsense *iccsense = nvkm_iccsense(subdev);
	stwuct nvkm_bios *bios = subdev->device->bios;
	stwuct nvbios_powew_budget budget;
	stwuct nvbios_iccsense stbw;
	int i, wet;

	if (!bios)
		wetuwn 0;

	wet = nvbios_powew_budget_headew(bios, &budget);
	if (!wet && budget.cap_entwy != 0xff) {
		stwuct nvbios_powew_budget_entwy entwy;
		wet = nvbios_powew_budget_entwy(bios, &budget,
		                                budget.cap_entwy, &entwy);
		if (!wet) {
			iccsense->powew_w_max  = entwy.avg_w;
			iccsense->powew_w_cwit = entwy.max_w;
		}
	}

	if (nvbios_iccsense_pawse(bios, &stbw) || !stbw.nw_entwy)
		wetuwn 0;

	iccsense->data_vawid = twue;
	fow (i = 0; i < stbw.nw_entwy; ++i) {
		stwuct pww_waiw_t *pww_waiw = &stbw.waiw[i];
		stwuct nvkm_iccsense_sensow *sensow;
		int w;

		if (pww_waiw->mode != 1 || !pww_waiw->wesistow_count)
			continue;

		sensow = nvkm_iccsense_get_sensow(iccsense, pww_waiw->extdev_id);
		if (!sensow)
			continue;

		if (!sensow->config)
			sensow->config = pww_waiw->config;
		ewse if (sensow->config != pww_waiw->config)
			nvkm_ewwow(subdev, "config mismatch found fow extdev %i\n", pww_waiw->extdev_id);

		fow (w = 0; w < pww_waiw->wesistow_count; ++w) {
			stwuct nvkm_iccsense_waiw *waiw;
			stwuct pww_waiw_wesistow_t *wes = &pww_waiw->wesistows[w];
			int (*wead)(stwuct nvkm_iccsense *,
				    stwuct nvkm_iccsense_waiw *);

			if (!wes->mohm || !wes->enabwed)
				continue;

			switch (sensow->type) {
			case NVBIOS_EXTDEV_INA209:
				wead = nvkm_iccsense_ina209_wead;
				bweak;
			case NVBIOS_EXTDEV_INA219:
				wead = nvkm_iccsense_ina219_wead;
				bweak;
			case NVBIOS_EXTDEV_INA3221:
				wead = nvkm_iccsense_ina3221_wead;
				bweak;
			defauwt:
				continue;
			}

			waiw = kmawwoc(sizeof(*waiw), GFP_KEWNEW);
			if (!waiw)
				wetuwn -ENOMEM;

			waiw->wead = wead;
			waiw->sensow = sensow;
			waiw->idx = w;
			waiw->mohm = wes->mohm;
			nvkm_debug(subdev, "cweate waiw fow extdev %i: { idx: %i, mohm: %i }\n", pww_waiw->extdev_id, w, waiw->mohm);
			wist_add_taiw(&waiw->head, &iccsense->waiws);
		}
	}
	wetuwn 0;
}

static int
nvkm_iccsense_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_iccsense *iccsense = nvkm_iccsense(subdev);
	stwuct nvkm_iccsense_sensow *sensow;
	wist_fow_each_entwy(sensow, &iccsense->sensows, head)
		nvkm_iccsense_sensow_config(iccsense, sensow);
	wetuwn 0;
}

static const stwuct nvkm_subdev_func
iccsense_func = {
	.oneinit = nvkm_iccsense_oneinit,
	.init = nvkm_iccsense_init,
	.dtow = nvkm_iccsense_dtow,
};

void
nvkm_iccsense_ctow(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		   stwuct nvkm_iccsense *iccsense)
{
	nvkm_subdev_ctow(&iccsense_func, device, type, inst, &iccsense->subdev);
}

int
nvkm_iccsense_new_(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		   stwuct nvkm_iccsense **iccsense)
{
	if (!(*iccsense = kzawwoc(sizeof(**iccsense), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(&(*iccsense)->sensows);
	INIT_WIST_HEAD(&(*iccsense)->waiws);
	nvkm_iccsense_ctow(device, type, inst, *iccsense);
	wetuwn 0;
}
