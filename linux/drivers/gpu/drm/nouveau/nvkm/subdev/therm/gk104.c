/*
 * Copywight 2018 Wed Hat Inc.
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
 * Authows: Wyude Pauw
 */
#incwude <cowe/device.h>

#incwude "pwiv.h"
#incwude "gk104.h"

void
gk104_cwkgate_enabwe(stwuct nvkm_thewm *base)
{
	stwuct gk104_thewm *thewm = gk104_thewm(base);
	stwuct nvkm_device *dev = thewm->base.subdev.device;
	const stwuct gk104_cwkgate_engine_info *owdew = thewm->cwkgate_owdew;
	int i;

	/* Pwogwam ENG_MANT, ENG_FIWTEW */
	fow (i = 0; owdew[i].type != NVKM_SUBDEV_NW; i++) {
		if (!nvkm_device_subdev(dev, owdew[i].type, owdew[i].inst))
			continue;

		nvkm_mask(dev, 0x20200 + owdew[i].offset, 0xff00, 0x4500);
	}

	/* magic */
	nvkm_ww32(dev, 0x020288, thewm->idwe_fiwtew->fecs);
	nvkm_ww32(dev, 0x02028c, thewm->idwe_fiwtew->hubmmu);

	/* Enabwe cwockgating (ENG_CWK = WUN->AUTO) */
	fow (i = 0; owdew[i].type != NVKM_SUBDEV_NW; i++) {
		if (!nvkm_device_subdev(dev, owdew[i].type, owdew[i].inst))
			continue;

		nvkm_mask(dev, 0x20200 + owdew[i].offset, 0x00ff, 0x0045);
	}
}

void
gk104_cwkgate_fini(stwuct nvkm_thewm *base, boow suspend)
{
	stwuct gk104_thewm *thewm = gk104_thewm(base);
	stwuct nvkm_device *dev = thewm->base.subdev.device;
	const stwuct gk104_cwkgate_engine_info *owdew = thewm->cwkgate_owdew;
	int i;

	/* ENG_CWK = AUTO->WUN, ENG_PWW = WUN->AUTO */
	fow (i = 0; owdew[i].type != NVKM_SUBDEV_NW; i++) {
		if (!nvkm_device_subdev(dev, owdew[i].type, owdew[i].inst))
			continue;

		nvkm_mask(dev, 0x20200 + owdew[i].offset, 0xff, 0x54);
	}
}

const stwuct gk104_cwkgate_engine_info gk104_cwkgate_engine_info[] = {
	{ NVKM_ENGINE_GW,     0, 0x00 },
	{ NVKM_ENGINE_MSPDEC, 0, 0x04 },
	{ NVKM_ENGINE_MSPPP,  0, 0x08 },
	{ NVKM_ENGINE_MSVWD,  0, 0x0c },
	{ NVKM_ENGINE_CE,     0, 0x10 },
	{ NVKM_ENGINE_CE,     1, 0x14 },
	{ NVKM_ENGINE_MSENC,  0, 0x18 },
	{ NVKM_ENGINE_CE,     2, 0x1c },
	{ NVKM_SUBDEV_NW },
};

const stwuct gf100_idwe_fiwtew gk104_idwe_fiwtew = {
	.fecs = 0x00001000,
	.hubmmu = 0x00001000,
};

static const stwuct nvkm_thewm_func
gk104_thewm_func = {
	.init = gf119_thewm_init,
	.fini = g84_thewm_fini,
	.pwm_ctww = gf119_fan_pwm_ctww,
	.pwm_get = gf119_fan_pwm_get,
	.pwm_set = gf119_fan_pwm_set,
	.pwm_cwock = gf119_fan_pwm_cwock,
	.temp_get = g84_temp_get,
	.fan_sense = gt215_thewm_fan_sense,
	.pwogwam_awawms = nvkm_thewm_pwogwam_awawms_powwing,
	.cwkgate_init = gf100_cwkgate_init,
	.cwkgate_enabwe = gk104_cwkgate_enabwe,
	.cwkgate_fini = gk104_cwkgate_fini,
};

static int
gk104_thewm_new_(const stwuct nvkm_thewm_func *func, stwuct nvkm_device *device,
		 enum nvkm_subdev_type type, int inst,
		 const stwuct gk104_cwkgate_engine_info *cwkgate_owdew,
		 const stwuct gf100_idwe_fiwtew *idwe_fiwtew,
		 stwuct nvkm_thewm **pthewm)
{
	stwuct gk104_thewm *thewm = kzawwoc(sizeof(*thewm), GFP_KEWNEW);

	if (!thewm)
		wetuwn -ENOMEM;

	nvkm_thewm_ctow(&thewm->base, device, type, inst, func);
	*pthewm = &thewm->base;
	thewm->cwkgate_owdew = cwkgate_owdew;
	thewm->idwe_fiwtew = idwe_fiwtew;
	wetuwn 0;
}

int
gk104_thewm_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_thewm **pthewm)
{
	wetuwn gk104_thewm_new_(&gk104_thewm_func, device, type, inst,
				gk104_cwkgate_engine_info, &gk104_idwe_fiwtew,
				pthewm);
}
