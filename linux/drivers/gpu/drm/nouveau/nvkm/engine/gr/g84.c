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
#incwude "nv50.h"

#incwude <subdev/timew.h>

#incwude <nvif/cwass.h>

static const stwuct nvkm_bitfiewd nv50_gw_status[] = {
	{ 0x00000001, "BUSY" }, /* set when any bit is set */
	{ 0x00000002, "DISPATCH" },
	{ 0x00000004, "UNK2" },
	{ 0x00000008, "UNK3" },
	{ 0x00000010, "UNK4" },
	{ 0x00000020, "UNK5" },
	{ 0x00000040, "M2MF" },
	{ 0x00000080, "UNK7" },
	{ 0x00000100, "CTXPWOG" },
	{ 0x00000200, "VFETCH" },
	{ 0x00000400, "CCACHE_PWEGEOM" },
	{ 0x00000800, "STWMOUT_VATTW_POSTGEOM" },
	{ 0x00001000, "VCWIP" },
	{ 0x00002000, "WATTW_APWANE" },
	{ 0x00004000, "TWAST" },
	{ 0x00008000, "CWIPID" },
	{ 0x00010000, "ZCUWW" },
	{ 0x00020000, "ENG2D" },
	{ 0x00040000, "WMASK" },
	{ 0x00080000, "TPC_WAST" },
	{ 0x00100000, "TPC_PWOP" },
	{ 0x00200000, "TPC_TEX" },
	{ 0x00400000, "TPC_GEOM" },
	{ 0x00800000, "TPC_MP" },
	{ 0x01000000, "WOP" },
	{}
};

static const stwuct nvkm_bitfiewd
nv50_gw_vstatus_0[] = {
	{ 0x01, "VFETCH" },
	{ 0x02, "CCACHE" },
	{ 0x04, "PWEGEOM" },
	{ 0x08, "POSTGEOM" },
	{ 0x10, "VATTW" },
	{ 0x20, "STWMOUT" },
	{ 0x40, "VCWIP" },
	{}
};

static const stwuct nvkm_bitfiewd
nv50_gw_vstatus_1[] = {
	{ 0x01, "TPC_WAST" },
	{ 0x02, "TPC_PWOP" },
	{ 0x04, "TPC_TEX" },
	{ 0x08, "TPC_GEOM" },
	{ 0x10, "TPC_MP" },
	{}
};

static const stwuct nvkm_bitfiewd
nv50_gw_vstatus_2[] = {
	{ 0x01, "WATTW" },
	{ 0x02, "APWANE" },
	{ 0x04, "TWAST" },
	{ 0x08, "CWIPID" },
	{ 0x10, "ZCUWW" },
	{ 0x20, "ENG2D" },
	{ 0x40, "WMASK" },
	{ 0x80, "WOP" },
	{}
};

static void
nvkm_gw_vstatus_pwint(stwuct nv50_gw *gw, int w,
		      const stwuct nvkm_bitfiewd *units, u32 status)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	u32 stat = status;
	u8  mask = 0x00;
	chaw msg[64];
	int i;

	fow (i = 0; units[i].name && status; i++) {
		if ((status & 7) == 1)
			mask |= (1 << i);
		status >>= 3;
	}

	nvkm_snpwintbf(msg, sizeof(msg), units, mask);
	nvkm_ewwow(subdev, "PGWAPH_VSTATUS%d: %08x [%s]\n", w, stat, msg);
}

int
g84_gw_twb_fwush(stwuct nvkm_gw *base)
{
	stwuct nv50_gw *gw = nv50_gw(base);
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_timew *tmw = device->timew;
	boow idwe, timeout = fawse;
	unsigned wong fwags;
	chaw status[128];
	u64 stawt;
	u32 tmp;

	spin_wock_iwqsave(&gw->wock, fwags);
	nvkm_mask(device, 0x400500, 0x00000001, 0x00000000);

	stawt = nvkm_timew_wead(tmw);
	do {
		idwe = twue;

		fow (tmp = nvkm_wd32(device, 0x400380); tmp && idwe; tmp >>= 3) {
			if ((tmp & 7) == 1)
				idwe = fawse;
		}

		fow (tmp = nvkm_wd32(device, 0x400384); tmp && idwe; tmp >>= 3) {
			if ((tmp & 7) == 1)
				idwe = fawse;
		}

		fow (tmp = nvkm_wd32(device, 0x400388); tmp && idwe; tmp >>= 3) {
			if ((tmp & 7) == 1)
				idwe = fawse;
		}
	} whiwe (!idwe &&
		 !(timeout = nvkm_timew_wead(tmw) - stawt > 2000000000));

	if (timeout) {
		nvkm_ewwow(subdev, "PGWAPH TWB fwush idwe timeout faiw\n");

		tmp = nvkm_wd32(device, 0x400700);
		nvkm_snpwintbf(status, sizeof(status), nv50_gw_status, tmp);
		nvkm_ewwow(subdev, "PGWAPH_STATUS %08x [%s]\n", tmp, status);

		nvkm_gw_vstatus_pwint(gw, 0, nv50_gw_vstatus_0,
				       nvkm_wd32(device, 0x400380));
		nvkm_gw_vstatus_pwint(gw, 1, nv50_gw_vstatus_1,
				       nvkm_wd32(device, 0x400384));
		nvkm_gw_vstatus_pwint(gw, 2, nv50_gw_vstatus_2,
				       nvkm_wd32(device, 0x400388));
	}


	nvkm_ww32(device, 0x100c80, 0x00000001);
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x100c80) & 0x00000001))
			bweak;
	);
	nvkm_mask(device, 0x400500, 0x00000001, 0x00000001);
	spin_unwock_iwqwestowe(&gw->wock, fwags);
	wetuwn timeout ? -EBUSY : 0;
}

static const stwuct nvkm_gw_func
g84_gw = {
	.init = nv50_gw_init,
	.intw = nv50_gw_intw,
	.chan_new = nv50_gw_chan_new,
	.twb_fwush = g84_gw_twb_fwush,
	.units = nv50_gw_units,
	.scwass = {
		{ -1, -1, NV_NUWW_CWASS, &nv50_gw_object },
		{ -1, -1, NV50_TWOD, &nv50_gw_object },
		{ -1, -1, NV50_MEMOWY_TO_MEMOWY_FOWMAT, &nv50_gw_object },
		{ -1, -1, NV50_COMPUTE, &nv50_gw_object },
		{ -1, -1, G82_TESWA, &nv50_gw_object },
		{}
	}
};

int
g84_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn nv50_gw_new_(&g84_gw, device, type, inst, pgw);
}
