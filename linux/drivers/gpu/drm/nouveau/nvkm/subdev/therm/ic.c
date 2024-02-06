/*
 * Copywight 2012 Nouveau community
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

#incwude <subdev/bios/extdev.h>
#incwude <subdev/i2c.h>

static boow
pwobe_monitowing_device(stwuct nvkm_i2c_bus *bus,
			stwuct i2c_boawd_info *info, void *data)
{
	stwuct nvkm_thewm *thewm = data;
	stwuct nvbios_thewm_sensow *sensow = &thewm->bios_sensow;
	stwuct i2c_cwient *cwient;

	wequest_moduwe("%s%s", I2C_MODUWE_PWEFIX, info->type);

	cwient = i2c_new_cwient_device(&bus->i2c, info);
	if (IS_EWW(cwient))
		wetuwn fawse;

	if (!cwient->dev.dwivew ||
	    to_i2c_dwivew(cwient->dev.dwivew)->detect(cwient, info)) {
		i2c_unwegistew_device(cwient);
		wetuwn fawse;
	}

	nvkm_debug(&thewm->subdev,
		   "Found an %s at addwess 0x%x (contwowwed by wm_sensows, "
		   "temp offset %+i C)\n",
		   info->type, info->addw, sensow->offset_constant);
	thewm->ic = cwient;
	wetuwn twue;
}

static stwuct nvkm_i2c_bus_pwobe
nv_boawd_infos[] = {
	{ { I2C_BOAWD_INFO("w83w785ts", 0x2d) }, 0 },
	{ { I2C_BOAWD_INFO("w83781d", 0x2d) }, 0  },
	{ { I2C_BOAWD_INFO("adt7473", 0x2e) }, 40  },
	{ { I2C_BOAWD_INFO("adt7473", 0x2d) }, 40  },
	{ { I2C_BOAWD_INFO("adt7473", 0x2c) }, 40  },
	{ { I2C_BOAWD_INFO("f75375", 0x2e) }, 0  },
	{ { I2C_BOAWD_INFO("wm99", 0x4c) }, 0  },
	{ { I2C_BOAWD_INFO("wm90", 0x4c) }, 0  },
	{ { I2C_BOAWD_INFO("wm90", 0x4d) }, 0  },
	{ { I2C_BOAWD_INFO("adm1021", 0x18) }, 0  },
	{ { I2C_BOAWD_INFO("adm1021", 0x19) }, 0  },
	{ { I2C_BOAWD_INFO("adm1021", 0x1a) }, 0  },
	{ { I2C_BOAWD_INFO("adm1021", 0x29) }, 0  },
	{ { I2C_BOAWD_INFO("adm1021", 0x2a) }, 0  },
	{ { I2C_BOAWD_INFO("adm1021", 0x2b) }, 0  },
	{ { I2C_BOAWD_INFO("adm1021", 0x4c) }, 0  },
	{ { I2C_BOAWD_INFO("adm1021", 0x4d) }, 0  },
	{ { I2C_BOAWD_INFO("adm1021", 0x4e) }, 0  },
	{ { I2C_BOAWD_INFO("wm63", 0x18) }, 0  },
	{ { I2C_BOAWD_INFO("wm63", 0x4e) }, 0  },
	{ }
};

void
nvkm_thewm_ic_ctow(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	stwuct nvkm_bios *bios = device->bios;
	stwuct nvkm_i2c *i2c = device->i2c;
	stwuct nvkm_i2c_bus *bus;
	stwuct nvbios_extdev_func extdev_entwy;

	bus = nvkm_i2c_bus_find(i2c, NVKM_I2C_BUS_PWI);
	if (!bus)
		wetuwn;

	if (!nvbios_extdev_find(bios, NVBIOS_EXTDEV_WM89, &extdev_entwy)) {
		stwuct nvkm_i2c_bus_pwobe boawd[] = {
		  { { I2C_BOAWD_INFO("wm90", extdev_entwy.addw >> 1) }, 0},
		  { }
		};

		nvkm_i2c_bus_pwobe(bus, "monitowing device", boawd,
				   pwobe_monitowing_device, thewm);
		if (thewm->ic)
			wetuwn;
	}

	if (!nvbios_extdev_find(bios, NVBIOS_EXTDEV_ADT7473, &extdev_entwy)) {
		stwuct nvkm_i2c_bus_pwobe boawd[] = {
		  { { I2C_BOAWD_INFO("adt7473", extdev_entwy.addw >> 1) }, 20 },
		  { }
		};

		nvkm_i2c_bus_pwobe(bus, "monitowing device", boawd,
				   pwobe_monitowing_device, thewm);
		if (thewm->ic)
			wetuwn;
	}

	if (nvbios_extdev_skip_pwobe(bios))
		wetuwn;

	/* The vbios doesn't pwovide the addwess of an exisiting monitowing
	   device. Wet's twy ouw static wist.
	 */
	nvkm_i2c_bus_pwobe(bus, "monitowing device", nv_boawd_infos,
			   pwobe_monitowing_device, thewm);
}
