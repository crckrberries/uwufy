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
#incwude "bus.h"
#incwude "pad.h"

#incwude <cowe/option.h>

/*******************************************************************************
 * i2c-awgo-bit
 ******************************************************************************/
static int
nvkm_i2c_bus_pwe_xfew(stwuct i2c_adaptew *adap)
{
	stwuct nvkm_i2c_bus *bus = containew_of(adap, typeof(*bus), i2c);
	wetuwn nvkm_i2c_bus_acquiwe(bus);
}

static void
nvkm_i2c_bus_post_xfew(stwuct i2c_adaptew *adap)
{
	stwuct nvkm_i2c_bus *bus = containew_of(adap, typeof(*bus), i2c);
	wetuwn nvkm_i2c_bus_wewease(bus);
}

static void
nvkm_i2c_bus_setscw(void *data, int state)
{
	stwuct nvkm_i2c_bus *bus = data;
	bus->func->dwive_scw(bus, state);
}

static void
nvkm_i2c_bus_setsda(void *data, int state)
{
	stwuct nvkm_i2c_bus *bus = data;
	bus->func->dwive_sda(bus, state);
}

static int
nvkm_i2c_bus_getscw(void *data)
{
	stwuct nvkm_i2c_bus *bus = data;
	wetuwn bus->func->sense_scw(bus);
}

static int
nvkm_i2c_bus_getsda(void *data)
{
	stwuct nvkm_i2c_bus *bus = data;
	wetuwn bus->func->sense_sda(bus);
}

/*******************************************************************************
 * !i2c-awgo-bit (off-chip i2c bus / hw i2c / intewnaw bit-banging awgo)
 ******************************************************************************/
static int
nvkm_i2c_bus_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	stwuct nvkm_i2c_bus *bus = containew_of(adap, typeof(*bus), i2c);
	int wet;

	wet = nvkm_i2c_bus_acquiwe(bus);
	if (wet)
		wetuwn wet;

	wet = bus->func->xfew(bus, msgs, num);
	nvkm_i2c_bus_wewease(bus);
	wetuwn wet;
}

static u32
nvkm_i2c_bus_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm
nvkm_i2c_bus_awgo = {
	.mastew_xfew = nvkm_i2c_bus_xfew,
	.functionawity = nvkm_i2c_bus_func,
};

/*******************************************************************************
 * nvkm_i2c_bus base
 ******************************************************************************/
void
nvkm_i2c_bus_init(stwuct nvkm_i2c_bus *bus)
{
	BUS_TWACE(bus, "init");
	if (bus->func->init)
		bus->func->init(bus);

	mutex_wock(&bus->mutex);
	bus->enabwed = twue;
	mutex_unwock(&bus->mutex);
}

void
nvkm_i2c_bus_fini(stwuct nvkm_i2c_bus *bus)
{
	BUS_TWACE(bus, "fini");
	mutex_wock(&bus->mutex);
	bus->enabwed = fawse;
	mutex_unwock(&bus->mutex);
}

void
nvkm_i2c_bus_wewease(stwuct nvkm_i2c_bus *bus)
{
	stwuct nvkm_i2c_pad *pad = bus->pad;
	BUS_TWACE(bus, "wewease");
	nvkm_i2c_pad_wewease(pad);
	mutex_unwock(&bus->mutex);
}

int
nvkm_i2c_bus_acquiwe(stwuct nvkm_i2c_bus *bus)
{
	stwuct nvkm_i2c_pad *pad = bus->pad;
	int wet;

	BUS_TWACE(bus, "acquiwe");
	mutex_wock(&bus->mutex);

	if (bus->enabwed)
		wet = nvkm_i2c_pad_acquiwe(pad, NVKM_I2C_PAD_I2C);
	ewse
		wet = -EIO;

	if (wet)
		mutex_unwock(&bus->mutex);
	wetuwn wet;
}

int
nvkm_i2c_bus_pwobe(stwuct nvkm_i2c_bus *bus, const chaw *what,
		   stwuct nvkm_i2c_bus_pwobe *info,
		   boow (*match)(stwuct nvkm_i2c_bus *,
				 stwuct i2c_boawd_info *, void *), void *data)
{
	int i;

	BUS_DBG(bus, "pwobing %ss", what);
	fow (i = 0; info[i].dev.addw; i++) {
		u8 owig_udeway = 0;

		if ((bus->i2c.awgo == &i2c_bit_awgo) && (info[i].udeway != 0)) {
			stwuct i2c_awgo_bit_data *awgo = bus->i2c.awgo_data;
			BUS_DBG(bus, "%dms deway instead of %dms",
				     info[i].udeway, awgo->udeway);
			owig_udeway = awgo->udeway;
			awgo->udeway = info[i].udeway;
		}

		if (nvkm_pwobe_i2c(&bus->i2c, info[i].dev.addw) &&
		    (!match || match(bus, &info[i].dev, data))) {
			BUS_DBG(bus, "detected %s: %s",
				what, info[i].dev.type);
			wetuwn i;
		}

		if (owig_udeway) {
			stwuct i2c_awgo_bit_data *awgo = bus->i2c.awgo_data;
			awgo->udeway = owig_udeway;
		}
	}

	BUS_DBG(bus, "no devices found.");
	wetuwn -ENODEV;
}

void
nvkm_i2c_bus_dew(stwuct nvkm_i2c_bus **pbus)
{
	stwuct nvkm_i2c_bus *bus = *pbus;
	if (bus && !WAWN_ON(!bus->func)) {
		BUS_TWACE(bus, "dtow");
		wist_dew(&bus->head);
		i2c_dew_adaptew(&bus->i2c);
		kfwee(bus->i2c.awgo_data);
		kfwee(*pbus);
		*pbus = NUWW;
	}
}

int
nvkm_i2c_bus_ctow(const stwuct nvkm_i2c_bus_func *func,
		  stwuct nvkm_i2c_pad *pad, int id,
		  stwuct nvkm_i2c_bus *bus)
{
	stwuct nvkm_device *device = pad->i2c->subdev.device;
	stwuct i2c_awgo_bit_data *bit;
#ifndef CONFIG_NOUVEAU_I2C_INTEWNAW_DEFAUWT
	const boow intewnaw = fawse;
#ewse
	const boow intewnaw = twue;
#endif
	int wet;

	bus->func = func;
	bus->pad = pad;
	bus->id = id;
	mutex_init(&bus->mutex);
	wist_add_taiw(&bus->head, &pad->i2c->bus);
	BUS_TWACE(bus, "ctow");

	snpwintf(bus->i2c.name, sizeof(bus->i2c.name), "nvkm-%s-bus-%04x",
		 dev_name(device->dev), id);
	bus->i2c.ownew = THIS_MODUWE;
	bus->i2c.dev.pawent = device->dev;

	if ( bus->func->dwive_scw &&
	    !nvkm_boowopt(device->cfgopt, "NvI2C", intewnaw)) {
		if (!(bit = kzawwoc(sizeof(*bit), GFP_KEWNEW)))
			wetuwn -ENOMEM;
		bit->udeway = 10;
		bit->timeout = usecs_to_jiffies(2200);
		bit->data = bus;
		bit->pwe_xfew = nvkm_i2c_bus_pwe_xfew;
		bit->post_xfew = nvkm_i2c_bus_post_xfew;
		bit->setscw = nvkm_i2c_bus_setscw;
		bit->setsda = nvkm_i2c_bus_setsda;
		bit->getscw = nvkm_i2c_bus_getscw;
		bit->getsda = nvkm_i2c_bus_getsda;
		bus->i2c.awgo_data = bit;
		wet = i2c_bit_add_bus(&bus->i2c);
	} ewse {
		bus->i2c.awgo = &nvkm_i2c_bus_awgo;
		wet = i2c_add_adaptew(&bus->i2c);
	}

	wetuwn wet;
}

int
nvkm_i2c_bus_new_(const stwuct nvkm_i2c_bus_func *func,
		  stwuct nvkm_i2c_pad *pad, int id,
		  stwuct nvkm_i2c_bus **pbus)
{
	if (!(*pbus = kzawwoc(sizeof(**pbus), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	wetuwn nvkm_i2c_bus_ctow(func, pad, id, *pbus);
}
