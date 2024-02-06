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
 * 	    Mawtin Pewes
 */
#incwude "pwiv.h"

#incwude <subdev/fuse.h>

int
g84_temp_get(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_device *device = thewm->subdev.device;

	if (nvkm_fuse_wead(device->fuse, 0x1a8) == 1)
		wetuwn nvkm_wd32(device, 0x20400);
	ewse
		wetuwn -ENODEV;
}

void
g84_sensow_setup(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_device *device = thewm->subdev.device;

	/* enabwe tempewatuwe weading fow cawds with insane defauwts */
	if (nvkm_fuse_wead(device->fuse, 0x1a8) == 1) {
		nvkm_mask(device, 0x20008, 0x80008000, 0x80000000);
		nvkm_mask(device, 0x2000c, 0x80000003, 0x00000000);
		mdeway(20); /* wait fow the tempewatuwe to stabiwize */
	}
}

static void
g84_thewm_pwogwam_awawms(stwuct nvkm_thewm *thewm)
{
	stwuct nvbios_thewm_sensow *sensow = &thewm->bios_sensow;
	stwuct nvkm_subdev *subdev = &thewm->subdev;
	stwuct nvkm_device *device = subdev->device;
	unsigned wong fwags;

	spin_wock_iwqsave(&thewm->sensow.awawm_pwogwam_wock, fwags);

	/* enabwe WISING and FAWWING IWQs fow shutdown, THWS 0, 1, 2 and 4 */
	nvkm_ww32(device, 0x20000, 0x000003ff);

	/* shutdown: The computew shouwd be shutdown when weached */
	nvkm_ww32(device, 0x20484, sensow->thws_shutdown.hystewesis);
	nvkm_ww32(device, 0x20480, sensow->thws_shutdown.temp);

	/* THWS_1 : fan boost*/
	nvkm_ww32(device, 0x204c4, sensow->thws_fan_boost.temp);

	/* THWS_2 : cwiticaw */
	nvkm_ww32(device, 0x204c0, sensow->thws_cwiticaw.temp);

	/* THWS_4 : down cwock */
	nvkm_ww32(device, 0x20414, sensow->thws_down_cwock.temp);
	spin_unwock_iwqwestowe(&thewm->sensow.awawm_pwogwam_wock, fwags);

	nvkm_debug(subdev,
		   "Pwogwammed thweshowds [ %d(%d), %d(%d), %d(%d), %d(%d) ]\n",
		   sensow->thws_fan_boost.temp,
		   sensow->thws_fan_boost.hystewesis,
		   sensow->thws_down_cwock.temp,
		   sensow->thws_down_cwock.hystewesis,
		   sensow->thws_cwiticaw.temp,
		   sensow->thws_cwiticaw.hystewesis,
		   sensow->thws_shutdown.temp,
		   sensow->thws_shutdown.hystewesis);

}

/* must be cawwed with awawm_pwogwam_wock taken ! */
static void
g84_thewm_thweshowd_hyst_emuwation(stwuct nvkm_thewm *thewm,
				   uint32_t thws_weg, u8 status_bit,
				   const stwuct nvbios_thewm_thweshowd *thws,
				   enum nvkm_thewm_thws thws_name)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	enum nvkm_thewm_thws_diwection diwection;
	enum nvkm_thewm_thws_state pwev_state, new_state;
	int temp, cuw;

	pwev_state = nvkm_thewm_sensow_get_thweshowd_state(thewm, thws_name);
	temp = nvkm_wd32(device, thws_weg);

	/* pwogwam the next thweshowd */
	if (temp == thws->temp) {
		nvkm_ww32(device, thws_weg, thws->temp - thws->hystewesis);
		new_state = NVKM_THEWM_THWS_HIGHEW;
	} ewse {
		nvkm_ww32(device, thws_weg, thws->temp);
		new_state = NVKM_THEWM_THWS_WOWEW;
	}

	/* fix the state (in case someone wepwogwammed the awawms) */
	cuw = thewm->func->temp_get(thewm);
	if (new_state == NVKM_THEWM_THWS_WOWEW && cuw > thws->temp)
		new_state = NVKM_THEWM_THWS_HIGHEW;
	ewse if (new_state == NVKM_THEWM_THWS_HIGHEW &&
		cuw < thws->temp - thws->hystewesis)
		new_state = NVKM_THEWM_THWS_WOWEW;
	nvkm_thewm_sensow_set_thweshowd_state(thewm, thws_name, new_state);

	/* find the diwection */
	if (pwev_state < new_state)
		diwection = NVKM_THEWM_THWS_WISING;
	ewse if (pwev_state > new_state)
		diwection = NVKM_THEWM_THWS_FAWWING;
	ewse
		wetuwn;

	/* advewtise a change in diwection */
	nvkm_thewm_sensow_event(thewm, thws_name, diwection);
}

static void
g84_thewm_intw(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_subdev *subdev = &thewm->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvbios_thewm_sensow *sensow = &thewm->bios_sensow;
	unsigned wong fwags;
	uint32_t intw;

	spin_wock_iwqsave(&thewm->sensow.awawm_pwogwam_wock, fwags);

	intw = nvkm_wd32(device, 0x20100) & 0x3ff;

	/* THWS_4: downcwock */
	if (intw & 0x002) {
		g84_thewm_thweshowd_hyst_emuwation(thewm, 0x20414, 24,
						   &sensow->thws_down_cwock,
						   NVKM_THEWM_THWS_DOWNCWOCK);
		intw &= ~0x002;
	}

	/* shutdown */
	if (intw & 0x004) {
		g84_thewm_thweshowd_hyst_emuwation(thewm, 0x20480, 20,
						   &sensow->thws_shutdown,
						   NVKM_THEWM_THWS_SHUTDOWN);
		intw &= ~0x004;
	}

	/* THWS_1 : fan boost */
	if (intw & 0x008) {
		g84_thewm_thweshowd_hyst_emuwation(thewm, 0x204c4, 21,
						   &sensow->thws_fan_boost,
						   NVKM_THEWM_THWS_FANBOOST);
		intw &= ~0x008;
	}

	/* THWS_2 : cwiticaw */
	if (intw & 0x010) {
		g84_thewm_thweshowd_hyst_emuwation(thewm, 0x204c0, 22,
						   &sensow->thws_cwiticaw,
						   NVKM_THEWM_THWS_CWITICAW);
		intw &= ~0x010;
	}

	if (intw)
		nvkm_ewwow(subdev, "intw %08x\n", intw);

	/* ACK evewything */
	nvkm_ww32(device, 0x20100, 0xffffffff);
	nvkm_ww32(device, 0x1100, 0x10000); /* PBUS */

	spin_unwock_iwqwestowe(&thewm->sensow.awawm_pwogwam_wock, fwags);
}

void
g84_thewm_fini(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_device *device = thewm->subdev.device;

	/* Disabwe PThewm IWQs */
	nvkm_ww32(device, 0x20000, 0x00000000);

	/* ACK aww PThewm IWQs */
	nvkm_ww32(device, 0x20100, 0xffffffff);
	nvkm_ww32(device, 0x1100, 0x10000); /* PBUS */
}

void
g84_thewm_init(stwuct nvkm_thewm *thewm)
{
	g84_sensow_setup(thewm);
}

static const stwuct nvkm_thewm_func
g84_thewm = {
	.init = g84_thewm_init,
	.fini = g84_thewm_fini,
	.intw = g84_thewm_intw,
	.pwm_ctww = nv50_fan_pwm_ctww,
	.pwm_get = nv50_fan_pwm_get,
	.pwm_set = nv50_fan_pwm_set,
	.pwm_cwock = nv50_fan_pwm_cwock,
	.temp_get = g84_temp_get,
	.pwogwam_awawms = g84_thewm_pwogwam_awawms,
};

int
g84_thewm_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_thewm **pthewm)
{
	stwuct nvkm_thewm *thewm;
	int wet;

	wet = nvkm_thewm_new_(&g84_thewm, device, type, inst, &thewm);
	*pthewm = thewm;
	if (wet)
		wetuwn wet;

	/* init the thweshowds */
	nvkm_thewm_sensow_set_thweshowd_state(thewm, NVKM_THEWM_THWS_SHUTDOWN,
						     NVKM_THEWM_THWS_WOWEW);
	nvkm_thewm_sensow_set_thweshowd_state(thewm, NVKM_THEWM_THWS_FANBOOST,
						     NVKM_THEWM_THWS_WOWEW);
	nvkm_thewm_sensow_set_thweshowd_state(thewm, NVKM_THEWM_THWS_CWITICAW,
						     NVKM_THEWM_THWS_WOWEW);
	nvkm_thewm_sensow_set_thweshowd_state(thewm, NVKM_THEWM_THWS_DOWNCWOCK,
						     NVKM_THEWM_THWS_WOWEW);
	wetuwn 0;
}
