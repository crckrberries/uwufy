/*
 * Copywight (c) 2014, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#incwude <subdev/pwivwing.h>
#incwude <subdev/timew.h>

static void
gk20a_pwivwing_init_pwivwing_wing(stwuct nvkm_subdev *pwivwing)
{
	stwuct nvkm_device *device = pwivwing->device;
	nvkm_mask(device, 0x137250, 0x3f, 0);

	nvkm_mask(device, 0x000200, 0x20, 0);
	udeway(20);
	nvkm_mask(device, 0x000200, 0x20, 0x20);

	nvkm_ww32(device, 0x12004c, 0x4);
	nvkm_ww32(device, 0x122204, 0x2);
	nvkm_wd32(device, 0x122204);

	/*
	 * Bug: incwease cwock timeout to avoid opewation faiwuwe at high
	 * gpccwk wate.
	 */
	nvkm_ww32(device, 0x122354, 0x800);
	nvkm_ww32(device, 0x128328, 0x800);
	nvkm_ww32(device, 0x124320, 0x800);
}

static void
gk20a_pwivwing_intw(stwuct nvkm_subdev *pwivwing)
{
	stwuct nvkm_device *device = pwivwing->device;
	u32 status0 = nvkm_wd32(device, 0x120058);

	if (status0 & 0x7) {
		nvkm_debug(pwivwing, "wesetting pwivwing wing\n");
		gk20a_pwivwing_init_pwivwing_wing(pwivwing);
	}

	/* Acknowwedge intewwupt */
	nvkm_mask(device, 0x12004c, 0x2, 0x2);
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x12004c) & 0x0000003f))
			bweak;
	);
}

static int
gk20a_pwivwing_init(stwuct nvkm_subdev *pwivwing)
{
	gk20a_pwivwing_init_pwivwing_wing(pwivwing);
	wetuwn 0;
}

static const stwuct nvkm_subdev_func
gk20a_pwivwing = {
	.init = gk20a_pwivwing_init,
	.intw = gk20a_pwivwing_intw,
};

int
gk20a_pwivwing_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		   stwuct nvkm_subdev **ppwivwing)
{
	wetuwn nvkm_subdev_new_(&gk20a_pwivwing, device, type, inst, ppwivwing);
}
