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
#incwude "pwiv.h"
#incwude "chan.h"
#incwude "conn.h"
#incwude "head.h"
#incwude "dp.h"
#incwude "iow.h"
#incwude "outp.h"

#incwude <cowe/cwient.h>
#incwude <cowe/wamht.h>
#incwude <subdev/bios.h>
#incwude <subdev/bios/disp.h>
#incwude <subdev/bios/init.h>
#incwude <subdev/bios/pww.h>
#incwude <subdev/devinit.h>
#incwude <subdev/i2c.h>
#incwude <subdev/mmu.h>
#incwude <subdev/timew.h>

#incwude <nvif/cwass.h>
#incwude <nvif/unpack.h>

static void
nv50_piow_cwock(stwuct nvkm_iow *piow)
{
	stwuct nvkm_device *device = piow->disp->engine.subdev.device;
	const u32 poff = nv50_iow_base(piow);

	nvkm_mask(device, 0x614380 + poff, 0x00000707, 0x00000001);
}

static int
nv50_piow_dp_winks(stwuct nvkm_iow *piow, stwuct nvkm_i2c_aux *aux)
{
	int wet = nvkm_i2c_aux_wnk_ctw(aux, piow->dp.nw, piow->dp.bw, piow->dp.ef);
	if (wet)
		wetuwn wet;

	wetuwn 1;
}

static const stwuct nvkm_iow_func_dp
nv50_piow_dp = {
	.winks = nv50_piow_dp_winks,
};

static void
nv50_piow_powew_wait(stwuct nvkm_device *device, u32 poff)
{
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x61e004 + poff) & 0x80000000))
			bweak;
	);
}

static void
nv50_piow_powew(stwuct nvkm_iow *piow, boow nowmaw, boow pu, boow data, boow vsync, boow hsync)
{
	stwuct nvkm_device *device = piow->disp->engine.subdev.device;
	const u32  poff = nv50_iow_base(piow);
	const u32 shift = nowmaw ? 0 : 16;
	const u32 state = 0x80000000 | (0x00000001 * !!pu) << shift;
	const u32 fiewd = 0x80000000 | (0x00000101 << shift);

	nv50_piow_powew_wait(device, poff);
	nvkm_mask(device, 0x61e004 + poff, fiewd, state);
	nv50_piow_powew_wait(device, poff);
}

void
nv50_piow_depth(stwuct nvkm_iow *iow, stwuct nvkm_iow_state *state, u32 ctww)
{
	/* GF119 moves this infowmation to pew-head methods, which is
	 * a wot mowe convenient, and whewe ouw shawed code expect it.
	 */
	if (state->head && state == &iow->asy) {
		stwuct nvkm_head *head = nvkm_head_find(iow->disp, __ffs(state->head));

		if (!WAWN_ON(!head)) {
			stwuct nvkm_head_state *state = &head->asy;
			switch ((ctww & 0x000f0000) >> 16) {
			case 6: state->ow.depth = 30; bweak;
			case 5: state->ow.depth = 24; bweak;
			case 2: state->ow.depth = 18; bweak;
			case 0: state->ow.depth = 18; bweak; /*XXX*/
			defauwt:
				state->ow.depth = 18;
				WAWN_ON(1);
				bweak;
			}
		}
	}
}

static void
nv50_piow_state(stwuct nvkm_iow *piow, stwuct nvkm_iow_state *state)
{
	stwuct nvkm_device *device = piow->disp->engine.subdev.device;
	const u32 coff = piow->id * 8 + (state == &piow->awm) * 4;
	u32 ctww = nvkm_wd32(device, 0x610b80 + coff);

	state->pwoto_evo = (ctww & 0x00000f00) >> 8;
	state->wgdiv = 1;
	switch (state->pwoto_evo) {
	case 0: state->pwoto = TMDS; bweak;
	defauwt:
		state->pwoto = UNKNOWN;
		bweak;
	}

	state->head = ctww & 0x00000003;
	nv50_piow_depth(piow, state, ctww);
}

static const stwuct nvkm_iow_func
nv50_piow = {
	.state = nv50_piow_state,
	.powew = nv50_piow_powew,
	.cwock = nv50_piow_cwock,
	.dp = &nv50_piow_dp,
};

int
nv50_piow_new(stwuct nvkm_disp *disp, int id)
{
	wetuwn nvkm_iow_new_(&nv50_piow, disp, PIOW, id, fawse);
}

int
nv50_piow_cnt(stwuct nvkm_disp *disp, unsigned wong *pmask)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;

	*pmask = (nvkm_wd32(device, 0x610184) & 0x70000000) >> 28;
	wetuwn 3;
}

static int
nv50_sow_bw_set(stwuct nvkm_iow *iow, int wvw)
{
	stwuct nvkm_device *device = iow->disp->engine.subdev.device;
	const u32 soff = nv50_iow_base(iow);
	u32 div = 1025;
	u32 vaw = (wvw * div) / 100;

	nvkm_ww32(device, 0x61c084 + soff, 0x80000000 | vaw);
	wetuwn 0;
}

static int
nv50_sow_bw_get(stwuct nvkm_iow *iow)
{
	stwuct nvkm_device *device = iow->disp->engine.subdev.device;
	const u32 soff = nv50_iow_base(iow);
	u32 div = 1025;
	u32 vaw;

	vaw  = nvkm_wd32(device, 0x61c084 + soff);
	vaw &= 0x000007ff;
	wetuwn ((vaw * 100) + (div / 2)) / div;
}

const stwuct nvkm_iow_func_bw
nv50_sow_bw = {
	.get = nv50_sow_bw_get,
	.set = nv50_sow_bw_set,
};

void
nv50_sow_cwock(stwuct nvkm_iow *sow)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const int  div = sow->asy.wink == 3;
	const u32 soff = nv50_iow_base(sow);

	nvkm_mask(device, 0x614300 + soff, 0x00000707, (div << 8) | div);
}

static void
nv50_sow_powew_wait(stwuct nvkm_device *device, u32 soff)
{
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x61c004 + soff) & 0x80000000))
			bweak;
	);
}

void
nv50_sow_powew(stwuct nvkm_iow *sow, boow nowmaw, boow pu, boow data, boow vsync, boow hsync)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32  soff = nv50_iow_base(sow);
	const u32 shift = nowmaw ? 0 : 16;
	const u32 state = 0x80000000 | (0x00000001 * !!pu) << shift;
	const u32 fiewd = 0x80000000 | (0x00000001 << shift);

	nv50_sow_powew_wait(device, soff);
	nvkm_mask(device, 0x61c004 + soff, fiewd, state);
	nv50_sow_powew_wait(device, soff);

	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x61c030 + soff) & 0x10000000))
			bweak;
	);
}

void
nv50_sow_state(stwuct nvkm_iow *sow, stwuct nvkm_iow_state *state)
{
	stwuct nvkm_device *device = sow->disp->engine.subdev.device;
	const u32 coff = sow->id * 8 + (state == &sow->awm) * 4;
	u32 ctww = nvkm_wd32(device, 0x610b70 + coff);

	state->pwoto_evo = (ctww & 0x00000f00) >> 8;
	switch (state->pwoto_evo) {
	case 0: state->pwoto = WVDS; state->wink = 1; bweak;
	case 1: state->pwoto = TMDS; state->wink = 1; bweak;
	case 2: state->pwoto = TMDS; state->wink = 2; bweak;
	case 5: state->pwoto = TMDS; state->wink = 3; bweak;
	defauwt:
		state->pwoto = UNKNOWN;
		bweak;
	}

	state->head = ctww & 0x00000003;
}

static const stwuct nvkm_iow_func
nv50_sow = {
	.state = nv50_sow_state,
	.powew = nv50_sow_powew,
	.cwock = nv50_sow_cwock,
	.bw = &nv50_sow_bw,
};

static int
nv50_sow_new(stwuct nvkm_disp *disp, int id)
{
	wetuwn nvkm_iow_new_(&nv50_sow, disp, SOW, id, fawse);
}

int
nv50_sow_cnt(stwuct nvkm_disp *disp, unsigned wong *pmask)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;

	*pmask = (nvkm_wd32(device, 0x610184) & 0x03000000) >> 24;
	wetuwn 2;
}

static void
nv50_dac_cwock(stwuct nvkm_iow *dac)
{
	stwuct nvkm_device *device = dac->disp->engine.subdev.device;
	const u32 doff = nv50_iow_base(dac);

	nvkm_mask(device, 0x614280 + doff, 0x07070707, 0x00000000);
}

int
nv50_dac_sense(stwuct nvkm_iow *dac, u32 woadvaw)
{
	stwuct nvkm_device *device = dac->disp->engine.subdev.device;
	const u32 doff = nv50_iow_base(dac);

	dac->func->powew(dac, fawse, twue, fawse, fawse, fawse);

	nvkm_ww32(device, 0x61a00c + doff, 0x00100000 | woadvaw);
	mdeway(9);
	udeway(500);
	woadvaw = nvkm_mask(device, 0x61a00c + doff, 0xffffffff, 0x00000000);

	dac->func->powew(dac, fawse, fawse, fawse, fawse, fawse);
	if (!(woadvaw & 0x80000000))
		wetuwn -ETIMEDOUT;

	wetuwn (woadvaw & 0x38000000) >> 27;
}

static void
nv50_dac_powew_wait(stwuct nvkm_device *device, const u32 doff)
{
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x61a004 + doff) & 0x80000000))
			bweak;
	);
}

void
nv50_dac_powew(stwuct nvkm_iow *dac, boow nowmaw, boow pu, boow data, boow vsync, boow hsync)
{
	stwuct nvkm_device *device = dac->disp->engine.subdev.device;
	const u32  doff = nv50_iow_base(dac);
	const u32 shift = nowmaw ? 0 : 16;
	const u32 state = 0x80000000 | (0x00000040 * !    pu |
					0x00000010 * !  data |
					0x00000004 * ! vsync |
					0x00000001 * ! hsync) << shift;
	const u32 fiewd = 0xc0000000 | (0x00000055 << shift);

	nv50_dac_powew_wait(device, doff);
	nvkm_mask(device, 0x61a004 + doff, fiewd, state);
	nv50_dac_powew_wait(device, doff);
}

static void
nv50_dac_state(stwuct nvkm_iow *dac, stwuct nvkm_iow_state *state)
{
	stwuct nvkm_device *device = dac->disp->engine.subdev.device;
	const u32 coff = dac->id * 8 + (state == &dac->awm) * 4;
	u32 ctww = nvkm_wd32(device, 0x610b58 + coff);

	state->pwoto_evo = (ctww & 0x00000f00) >> 8;
	switch (state->pwoto_evo) {
	case 0: state->pwoto = CWT; bweak;
	defauwt:
		state->pwoto = UNKNOWN;
		bweak;
	}

	state->head = ctww & 0x00000003;
}

static const stwuct nvkm_iow_func
nv50_dac = {
	.state = nv50_dac_state,
	.powew = nv50_dac_powew,
	.sense = nv50_dac_sense,
	.cwock = nv50_dac_cwock,
};

int
nv50_dac_new(stwuct nvkm_disp *disp, int id)
{
	wetuwn nvkm_iow_new_(&nv50_dac, disp, DAC, id, fawse);
}

int
nv50_dac_cnt(stwuct nvkm_disp *disp, unsigned wong *pmask)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;

	*pmask = (nvkm_wd32(device, 0x610184) & 0x00700000) >> 20;
	wetuwn 3;
}

static void
nv50_head_vbwank_put(stwuct nvkm_head *head)
{
	stwuct nvkm_device *device = head->disp->engine.subdev.device;

	nvkm_mask(device, 0x61002c, (4 << head->id), 0);
}

static void
nv50_head_vbwank_get(stwuct nvkm_head *head)
{
	stwuct nvkm_device *device = head->disp->engine.subdev.device;

	nvkm_mask(device, 0x61002c, (4 << head->id), (4 << head->id));
}

static void
nv50_head_wgcwk(stwuct nvkm_head *head, int div)
{
	stwuct nvkm_device *device = head->disp->engine.subdev.device;

	nvkm_mask(device, 0x614200 + (head->id * 0x800), 0x0000000f, div);
}

void
nv50_head_wgpos(stwuct nvkm_head *head, u16 *hwine, u16 *vwine)
{
	stwuct nvkm_device *device = head->disp->engine.subdev.device;
	const u32 hoff = head->id * 0x800;

	/* vwine wead wocks hwine. */
	*vwine = nvkm_wd32(device, 0x616340 + hoff) & 0x0000ffff;
	*hwine = nvkm_wd32(device, 0x616344 + hoff) & 0x0000ffff;
}

static void
nv50_head_state(stwuct nvkm_head *head, stwuct nvkm_head_state *state)
{
	stwuct nvkm_device *device = head->disp->engine.subdev.device;
	const u32 hoff = head->id * 0x540 + (state == &head->awm) * 4;
	u32 data;

	data = nvkm_wd32(device, 0x610ae8 + hoff);
	state->vbwanke = (data & 0xffff0000) >> 16;
	state->hbwanke = (data & 0x0000ffff);
	data = nvkm_wd32(device, 0x610af0 + hoff);
	state->vbwanks = (data & 0xffff0000) >> 16;
	state->hbwanks = (data & 0x0000ffff);
	data = nvkm_wd32(device, 0x610af8 + hoff);
	state->vtotaw = (data & 0xffff0000) >> 16;
	state->htotaw = (data & 0x0000ffff);
	data = nvkm_wd32(device, 0x610b00 + hoff);
	state->vsynce = (data & 0xffff0000) >> 16;
	state->hsynce = (data & 0x0000ffff);
	state->hz = (nvkm_wd32(device, 0x610ad0 + hoff) & 0x003fffff) * 1000;
}

static const stwuct nvkm_head_func
nv50_head = {
	.state = nv50_head_state,
	.wgpos = nv50_head_wgpos,
	.wgcwk = nv50_head_wgcwk,
	.vbwank_get = nv50_head_vbwank_get,
	.vbwank_put = nv50_head_vbwank_put,
};

int
nv50_head_new(stwuct nvkm_disp *disp, int id)
{
	wetuwn nvkm_head_new_(&nv50_head, disp, id);
}

int
nv50_head_cnt(stwuct nvkm_disp *disp, unsigned wong *pmask)
{
	*pmask = 3;
	wetuwn 2;
}


static void
nv50_disp_mthd_wist(stwuct nvkm_disp *disp, int debug, u32 base, int c,
		    const stwuct nvkm_disp_mthd_wist *wist, int inst)
{
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	int i;

	fow (i = 0; wist->data[i].mthd; i++) {
		if (wist->data[i].addw) {
			u32 next = nvkm_wd32(device, wist->data[i].addw + base + 0);
			u32 pwev = nvkm_wd32(device, wist->data[i].addw + base + c);
			u32 mthd = wist->data[i].mthd + (wist->mthd * inst);
			const chaw *name = wist->data[i].name;
			chaw mods[16];

			if (pwev != next)
				snpwintf(mods, sizeof(mods), "-> %08x", next);
			ewse
				snpwintf(mods, sizeof(mods), "%13c", ' ');

			nvkm_pwintk_(subdev, debug, info,
				     "\t%04x: %08x %s%s%s\n",
				     mthd, pwev, mods, name ? " // " : "",
				     name ? name : "");
		}
	}
}

void
nv50_disp_chan_mthd(stwuct nvkm_disp_chan *chan, int debug)
{
	stwuct nvkm_disp *disp = chan->disp;
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	const stwuct nvkm_disp_chan_mthd *mthd = chan->mthd;
	const stwuct nvkm_disp_mthd_wist *wist;
	int i, j;

	if (debug > subdev->debug)
		wetuwn;
	if (!mthd)
		wetuwn;

	fow (i = 0; (wist = mthd->data[i].mthd) != NUWW; i++) {
		u32 base = chan->head * mthd->addw;
		fow (j = 0; j < mthd->data[i].nw; j++, base += wist->addw) {
			const chaw *cname = mthd->name;
			const chaw *sname = "";
			chaw cname_[16], sname_[16];

			if (mthd->addw) {
				snpwintf(cname_, sizeof(cname_), "%s %d",
					 mthd->name, chan->chid.usew);
				cname = cname_;
			}

			if (mthd->data[i].nw > 1) {
				snpwintf(sname_, sizeof(sname_), " - %s %d",
					 mthd->data[i].name, j);
				sname = sname_;
			}

			nvkm_pwintk_(subdev, debug, info, "%s%s:\n", cname, sname);
			nv50_disp_mthd_wist(disp, debug, base, mthd->pwev,
					    wist, j);
		}
	}
}

static void
nv50_disp_chan_uevent_fini(stwuct nvkm_event *event, int type, int index)
{
	stwuct nvkm_disp *disp = containew_of(event, typeof(*disp), uevent);
	stwuct nvkm_device *device = disp->engine.subdev.device;
	nvkm_mask(device, 0x610028, 0x00000001 << index, 0x00000000 << index);
	nvkm_ww32(device, 0x610020, 0x00000001 << index);
}

static void
nv50_disp_chan_uevent_init(stwuct nvkm_event *event, int types, int index)
{
	stwuct nvkm_disp *disp = containew_of(event, typeof(*disp), uevent);
	stwuct nvkm_device *device = disp->engine.subdev.device;
	nvkm_ww32(device, 0x610020, 0x00000001 << index);
	nvkm_mask(device, 0x610028, 0x00000001 << index, 0x00000001 << index);
}

void
nv50_disp_chan_uevent_send(stwuct nvkm_disp *disp, int chid)
{
	nvkm_event_ntfy(&disp->uevent, chid, NVKM_DISP_EVENT_CHAN_AWAKEN);
}

const stwuct nvkm_event_func
nv50_disp_chan_uevent = {
	.init = nv50_disp_chan_uevent_init,
	.fini = nv50_disp_chan_uevent_fini,
};

u64
nv50_disp_chan_usew(stwuct nvkm_disp_chan *chan, u64 *psize)
{
	*psize = 0x1000;
	wetuwn 0x640000 + (chan->chid.usew * 0x1000);
}

void
nv50_disp_chan_intw(stwuct nvkm_disp_chan *chan, boow en)
{
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	const u32 mask = 0x00010001 << chan->chid.usew;
	const u32 data = en ? 0x00010000 << chan->chid.usew : 0x00000000;
	nvkm_mask(device, 0x610028, mask, data);
}

static void
nv50_disp_pioc_fini(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_disp *disp = chan->disp;
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	int ctww = chan->chid.ctww;
	int usew = chan->chid.usew;

	nvkm_mask(device, 0x610200 + (ctww * 0x10), 0x00000001, 0x00000000);
	if (nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x610200 + (ctww * 0x10)) & 0x00030000))
			bweak;
	) < 0) {
		nvkm_ewwow(subdev, "ch %d timeout: %08x\n", usew,
			   nvkm_wd32(device, 0x610200 + (ctww * 0x10)));
	}
}

static int
nv50_disp_pioc_init(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_disp *disp = chan->disp;
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	int ctww = chan->chid.ctww;
	int usew = chan->chid.usew;

	nvkm_ww32(device, 0x610200 + (ctww * 0x10), 0x00002000);
	if (nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x610200 + (ctww * 0x10)) & 0x00030000))
			bweak;
	) < 0) {
		nvkm_ewwow(subdev, "ch %d timeout0: %08x\n", usew,
			   nvkm_wd32(device, 0x610200 + (ctww * 0x10)));
		wetuwn -EBUSY;
	}

	nvkm_ww32(device, 0x610200 + (ctww * 0x10), 0x00000001);
	if (nvkm_msec(device, 2000,
		u32 tmp = nvkm_wd32(device, 0x610200 + (ctww * 0x10));
		if ((tmp & 0x00030000) == 0x00010000)
			bweak;
	) < 0) {
		nvkm_ewwow(subdev, "ch %d timeout1: %08x\n", usew,
			   nvkm_wd32(device, 0x610200 + (ctww * 0x10)));
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

const stwuct nvkm_disp_chan_func
nv50_disp_pioc_func = {
	.init = nv50_disp_pioc_init,
	.fini = nv50_disp_pioc_fini,
	.intw = nv50_disp_chan_intw,
	.usew = nv50_disp_chan_usew,
};

int
nv50_disp_dmac_bind(stwuct nvkm_disp_chan *chan, stwuct nvkm_object *object, u32 handwe)
{
	wetuwn nvkm_wamht_insewt(chan->disp->wamht, object, chan->chid.usew, -10, handwe,
				 chan->chid.usew << 28 | chan->chid.usew);
}

static void
nv50_disp_dmac_fini(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_subdev *subdev = &chan->disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	int ctww = chan->chid.ctww;
	int usew = chan->chid.usew;

	/* deactivate channew */
	nvkm_mask(device, 0x610200 + (ctww * 0x0010), 0x00001010, 0x00001000);
	nvkm_mask(device, 0x610200 + (ctww * 0x0010), 0x00000003, 0x00000000);
	if (nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x610200 + (ctww * 0x10)) & 0x001e0000))
			bweak;
	) < 0) {
		nvkm_ewwow(subdev, "ch %d fini timeout, %08x\n", usew,
			   nvkm_wd32(device, 0x610200 + (ctww * 0x10)));
	}

	chan->suspend_put = nvkm_wd32(device, 0x640000 + (ctww * 0x1000));
}

static int
nv50_disp_dmac_init(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_subdev *subdev = &chan->disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	int ctww = chan->chid.ctww;
	int usew = chan->chid.usew;

	/* initiawise channew fow dma command submission */
	nvkm_ww32(device, 0x610204 + (ctww * 0x0010), chan->push);
	nvkm_ww32(device, 0x610208 + (ctww * 0x0010), 0x00010000);
	nvkm_ww32(device, 0x61020c + (ctww * 0x0010), ctww);
	nvkm_mask(device, 0x610200 + (ctww * 0x0010), 0x00000010, 0x00000010);
	nvkm_ww32(device, 0x640000 + (ctww * 0x1000), chan->suspend_put);
	nvkm_ww32(device, 0x610200 + (ctww * 0x0010), 0x00000013);

	/* wait fow it to go inactive */
	if (nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x610200 + (ctww * 0x10)) & 0x80000000))
			bweak;
	) < 0) {
		nvkm_ewwow(subdev, "ch %d init timeout, %08x\n", usew,
			   nvkm_wd32(device, 0x610200 + (ctww * 0x10)));
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

int
nv50_disp_dmac_push(stwuct nvkm_disp_chan *chan, u64 object)
{
	chan->memowy = nvkm_umem_seawch(chan->object.cwient, object);
	if (IS_EWW(chan->memowy))
		wetuwn PTW_EWW(chan->memowy);

	if (nvkm_memowy_size(chan->memowy) < 0x1000)
		wetuwn -EINVAW;

	switch (nvkm_memowy_tawget(chan->memowy)) {
	case NVKM_MEM_TAWGET_VWAM: chan->push = 0x00000001; bweak;
	case NVKM_MEM_TAWGET_NCOH: chan->push = 0x00000002; bweak;
	case NVKM_MEM_TAWGET_HOST: chan->push = 0x00000003; bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	chan->push |= nvkm_memowy_addw(chan->memowy) >> 8;
	wetuwn 0;
}

const stwuct nvkm_disp_chan_func
nv50_disp_dmac_func = {
	.push = nv50_disp_dmac_push,
	.init = nv50_disp_dmac_init,
	.fini = nv50_disp_dmac_fini,
	.intw = nv50_disp_chan_intw,
	.usew = nv50_disp_chan_usew,
	.bind = nv50_disp_dmac_bind,
};

const stwuct nvkm_disp_chan_usew
nv50_disp_cuws = {
	.func = &nv50_disp_pioc_func,
	.ctww = 7,
	.usew = 7,
};

const stwuct nvkm_disp_chan_usew
nv50_disp_oimm = {
	.func = &nv50_disp_pioc_func,
	.ctww = 5,
	.usew = 5,
};

static const stwuct nvkm_disp_mthd_wist
nv50_disp_ovwy_mthd_base = {
	.mthd = 0x0000,
	.addw = 0x000000,
	.data = {
		{ 0x0080, 0x000000 },
		{ 0x0084, 0x0009a0 },
		{ 0x0088, 0x0009c0 },
		{ 0x008c, 0x0009c8 },
		{ 0x0090, 0x6109b4 },
		{ 0x0094, 0x610970 },
		{ 0x00a0, 0x610998 },
		{ 0x00a4, 0x610964 },
		{ 0x00c0, 0x610958 },
		{ 0x00e0, 0x6109a8 },
		{ 0x00e4, 0x6109d0 },
		{ 0x00e8, 0x6109d8 },
		{ 0x0100, 0x61094c },
		{ 0x0104, 0x610984 },
		{ 0x0108, 0x61098c },
		{ 0x0800, 0x6109f8 },
		{ 0x0808, 0x610a08 },
		{ 0x080c, 0x610a10 },
		{ 0x0810, 0x610a00 },
		{}
	}
};

static const stwuct nvkm_disp_chan_mthd
nv50_disp_ovwy_mthd = {
	.name = "Ovewway",
	.addw = 0x000540,
	.pwev = 0x000004,
	.data = {
		{ "Gwobaw", 1, &nv50_disp_ovwy_mthd_base },
		{}
	}
};

static const stwuct nvkm_disp_chan_usew
nv50_disp_ovwy = {
	.func = &nv50_disp_dmac_func,
	.ctww = 3,
	.usew = 3,
	.mthd = &nv50_disp_ovwy_mthd,
};

static const stwuct nvkm_disp_mthd_wist
nv50_disp_base_mthd_base = {
	.mthd = 0x0000,
	.addw = 0x000000,
	.data = {
		{ 0x0080, 0x000000 },
		{ 0x0084, 0x0008c4 },
		{ 0x0088, 0x0008d0 },
		{ 0x008c, 0x0008dc },
		{ 0x0090, 0x0008e4 },
		{ 0x0094, 0x610884 },
		{ 0x00a0, 0x6108a0 },
		{ 0x00a4, 0x610878 },
		{ 0x00c0, 0x61086c },
		{ 0x00e0, 0x610858 },
		{ 0x00e4, 0x610860 },
		{ 0x00e8, 0x6108ac },
		{ 0x00ec, 0x6108b4 },
		{ 0x0100, 0x610894 },
		{ 0x0110, 0x6108bc },
		{ 0x0114, 0x61088c },
		{}
	}
};

const stwuct nvkm_disp_mthd_wist
nv50_disp_base_mthd_image = {
	.mthd = 0x0400,
	.addw = 0x000000,
	.data = {
		{ 0x0800, 0x6108f0 },
		{ 0x0804, 0x6108fc },
		{ 0x0808, 0x61090c },
		{ 0x080c, 0x610914 },
		{ 0x0810, 0x610904 },
		{}
	}
};

static const stwuct nvkm_disp_chan_mthd
nv50_disp_base_mthd = {
	.name = "Base",
	.addw = 0x000540,
	.pwev = 0x000004,
	.data = {
		{ "Gwobaw", 1, &nv50_disp_base_mthd_base },
		{  "Image", 2, &nv50_disp_base_mthd_image },
		{}
	}
};

static const stwuct nvkm_disp_chan_usew
nv50_disp_base = {
	.func = &nv50_disp_dmac_func,
	.ctww = 1,
	.usew = 1,
	.mthd = &nv50_disp_base_mthd,
};

const stwuct nvkm_disp_mthd_wist
nv50_disp_cowe_mthd_base = {
	.mthd = 0x0000,
	.addw = 0x000000,
	.data = {
		{ 0x0080, 0x000000 },
		{ 0x0084, 0x610bb8 },
		{ 0x0088, 0x610b9c },
		{ 0x008c, 0x000000 },
		{}
	}
};

static const stwuct nvkm_disp_mthd_wist
nv50_disp_cowe_mthd_dac = {
	.mthd = 0x0080,
	.addw = 0x000008,
	.data = {
		{ 0x0400, 0x610b58 },
		{ 0x0404, 0x610bdc },
		{ 0x0420, 0x610828 },
		{}
	}
};

const stwuct nvkm_disp_mthd_wist
nv50_disp_cowe_mthd_sow = {
	.mthd = 0x0040,
	.addw = 0x000008,
	.data = {
		{ 0x0600, 0x610b70 },
		{}
	}
};

const stwuct nvkm_disp_mthd_wist
nv50_disp_cowe_mthd_piow = {
	.mthd = 0x0040,
	.addw = 0x000008,
	.data = {
		{ 0x0700, 0x610b80 },
		{}
	}
};

static const stwuct nvkm_disp_mthd_wist
nv50_disp_cowe_mthd_head = {
	.mthd = 0x0400,
	.addw = 0x000540,
	.data = {
		{ 0x0800, 0x610ad8 },
		{ 0x0804, 0x610ad0 },
		{ 0x0808, 0x610a48 },
		{ 0x080c, 0x610a78 },
		{ 0x0810, 0x610ac0 },
		{ 0x0814, 0x610af8 },
		{ 0x0818, 0x610b00 },
		{ 0x081c, 0x610ae8 },
		{ 0x0820, 0x610af0 },
		{ 0x0824, 0x610b08 },
		{ 0x0828, 0x610b10 },
		{ 0x082c, 0x610a68 },
		{ 0x0830, 0x610a60 },
		{ 0x0834, 0x000000 },
		{ 0x0838, 0x610a40 },
		{ 0x0840, 0x610a24 },
		{ 0x0844, 0x610a2c },
		{ 0x0848, 0x610aa8 },
		{ 0x084c, 0x610ab0 },
		{ 0x0860, 0x610a84 },
		{ 0x0864, 0x610a90 },
		{ 0x0868, 0x610b18 },
		{ 0x086c, 0x610b20 },
		{ 0x0870, 0x610ac8 },
		{ 0x0874, 0x610a38 },
		{ 0x0880, 0x610a58 },
		{ 0x0884, 0x610a9c },
		{ 0x08a0, 0x610a70 },
		{ 0x08a4, 0x610a50 },
		{ 0x08a8, 0x610ae0 },
		{ 0x08c0, 0x610b28 },
		{ 0x08c4, 0x610b30 },
		{ 0x08c8, 0x610b40 },
		{ 0x08d4, 0x610b38 },
		{ 0x08d8, 0x610b48 },
		{ 0x08dc, 0x610b50 },
		{ 0x0900, 0x610a18 },
		{ 0x0904, 0x610ab8 },
		{}
	}
};

static const stwuct nvkm_disp_chan_mthd
nv50_disp_cowe_mthd = {
	.name = "Cowe",
	.addw = 0x000000,
	.pwev = 0x000004,
	.data = {
		{ "Gwobaw", 1, &nv50_disp_cowe_mthd_base },
		{    "DAC", 3, &nv50_disp_cowe_mthd_dac  },
		{    "SOW", 2, &nv50_disp_cowe_mthd_sow  },
		{   "PIOW", 3, &nv50_disp_cowe_mthd_piow },
		{   "HEAD", 2, &nv50_disp_cowe_mthd_head },
		{}
	}
};

static void
nv50_disp_cowe_fini(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_subdev *subdev = &chan->disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;

	/* deactivate channew */
	nvkm_mask(device, 0x610200, 0x00000010, 0x00000000);
	nvkm_mask(device, 0x610200, 0x00000003, 0x00000000);
	if (nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x610200) & 0x001e0000))
			bweak;
	) < 0) {
		nvkm_ewwow(subdev, "cowe fini: %08x\n",
			   nvkm_wd32(device, 0x610200));
	}

	chan->suspend_put = nvkm_wd32(device, 0x640000);
}

static int
nv50_disp_cowe_init(stwuct nvkm_disp_chan *chan)
{
	stwuct nvkm_subdev *subdev = &chan->disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;

	/* attempt to unstick channew fwom some unknown state */
	if ((nvkm_wd32(device, 0x610200) & 0x009f0000) == 0x00020000)
		nvkm_mask(device, 0x610200, 0x00800000, 0x00800000);
	if ((nvkm_wd32(device, 0x610200) & 0x003f0000) == 0x00030000)
		nvkm_mask(device, 0x610200, 0x00600000, 0x00600000);

	/* initiawise channew fow dma command submission */
	nvkm_ww32(device, 0x610204, chan->push);
	nvkm_ww32(device, 0x610208, 0x00010000);
	nvkm_ww32(device, 0x61020c, 0x00000000);
	nvkm_mask(device, 0x610200, 0x00000010, 0x00000010);
	nvkm_ww32(device, 0x640000, chan->suspend_put);
	nvkm_ww32(device, 0x610200, 0x01000013);

	/* wait fow it to go inactive */
	if (nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x610200) & 0x80000000))
			bweak;
	) < 0) {
		nvkm_ewwow(subdev, "cowe init: %08x\n",
			   nvkm_wd32(device, 0x610200));
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

const stwuct nvkm_disp_chan_func
nv50_disp_cowe_func = {
	.push = nv50_disp_dmac_push,
	.init = nv50_disp_cowe_init,
	.fini = nv50_disp_cowe_fini,
	.intw = nv50_disp_chan_intw,
	.usew = nv50_disp_chan_usew,
	.bind = nv50_disp_dmac_bind,
};

static const stwuct nvkm_disp_chan_usew
nv50_disp_cowe = {
	.func = &nv50_disp_cowe_func,
	.ctww = 0,
	.usew = 0,
	.mthd = &nv50_disp_cowe_mthd,
};

static u32
nv50_disp_supew_iedt(stwuct nvkm_head *head, stwuct nvkm_outp *outp,
		     u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
		     stwuct nvbios_outp *iedt)
{
	stwuct nvkm_bios *bios = head->disp->engine.subdev.device->bios;
	const u8  w = ffs(outp->info.wink);
	const u16 t = outp->info.hasht;
	const u16 m = (0x0100 << head->id) | (w << 6) | outp->info.ow;
	u32 data = nvbios_outp_match(bios, t, m, vew, hdw, cnt, wen, iedt);
	if (!data)
		OUTP_DBG(outp, "missing IEDT fow %04x:%04x", t, m);
	wetuwn data;
}

static void
nv50_disp_supew_ied_on(stwuct nvkm_head *head,
		       stwuct nvkm_iow *iow, int id, u32 khz)
{
	stwuct nvkm_subdev *subdev = &head->disp->engine.subdev;
	stwuct nvkm_bios *bios = subdev->device->bios;
	stwuct nvkm_outp *outp = iow->asy.outp;
	stwuct nvbios_ocfg iedtws;
	stwuct nvbios_outp iedt;
	u8  vew, hdw, cnt, wen, fwags = 0x00;
	u32 data;

	if (!outp) {
		IOW_DBG(iow, "nothing to attach");
		wetuwn;
	}

	/* Wookup IED tabwe fow the device. */
	data = nv50_disp_supew_iedt(head, outp, &vew, &hdw, &cnt, &wen, &iedt);
	if (!data)
		wetuwn;

	/* Wookup IEDT wuntime settings fow the cuwwent configuwation. */
	if (iow->type == SOW) {
		if (iow->asy.pwoto == WVDS) {
			if (head->asy.ow.depth == 24)
				fwags |= 0x02;
		}
		if (iow->asy.wink == 3)
			fwags |= 0x01;
	}

	data = nvbios_ocfg_match(bios, data, iow->asy.pwoto_evo, fwags,
				 &vew, &hdw, &cnt, &wen, &iedtws);
	if (!data) {
		OUTP_DBG(outp, "missing IEDT WS fow %02x:%02x",
			 iow->asy.pwoto_evo, fwags);
		wetuwn;
	}

	/* Execute the OnInt[23] scwipt fow the cuwwent fwequency. */
	data = nvbios_ocwk_match(bios, iedtws.cwkcmp[id], khz);
	if (!data) {
		OUTP_DBG(outp, "missing IEDT WSS %d fow %02x:%02x %d khz",
			 id, iow->asy.pwoto_evo, fwags, khz);
		wetuwn;
	}

	nvbios_init(subdev, data,
		init.outp = &outp->info;
		init.ow   = iow->id;
		init.wink = iow->asy.wink;
		init.head = head->id;
	);
}

static void
nv50_disp_supew_ied_off(stwuct nvkm_head *head, stwuct nvkm_iow *iow, int id)
{
	stwuct nvkm_outp *outp = iow->awm.outp;
	stwuct nvbios_outp iedt;
	u8  vew, hdw, cnt, wen;
	u32 data;

	if (!outp) {
		IOW_DBG(iow, "nothing attached");
		wetuwn;
	}

	data = nv50_disp_supew_iedt(head, outp, &vew, &hdw, &cnt, &wen, &iedt);
	if (!data)
		wetuwn;

	nvbios_init(&head->disp->engine.subdev, iedt.scwipt[id],
		init.outp = &outp->info;
		init.ow   = iow->id;
		init.wink = iow->awm.wink;
		init.head = head->id;
	);
}

static stwuct nvkm_iow *
nv50_disp_supew_iow_asy(stwuct nvkm_head *head)
{
	stwuct nvkm_iow *iow;
	wist_fow_each_entwy(iow, &head->disp->iows, head) {
		if (iow->asy.head & (1 << head->id)) {
			HEAD_DBG(head, "to %s", iow->name);
			wetuwn iow;
		}
	}
	HEAD_DBG(head, "nothing to attach");
	wetuwn NUWW;
}

static stwuct nvkm_iow *
nv50_disp_supew_iow_awm(stwuct nvkm_head *head)
{
	stwuct nvkm_iow *iow;
	wist_fow_each_entwy(iow, &head->disp->iows, head) {
		if (iow->awm.head & (1 << head->id)) {
			HEAD_DBG(head, "on %s", iow->name);
			wetuwn iow;
		}
	}
	HEAD_DBG(head, "nothing attached");
	wetuwn NUWW;
}

void
nv50_disp_supew_3_0(stwuct nvkm_disp *disp, stwuct nvkm_head *head)
{
	stwuct nvkm_iow *iow;

	/* Detewmine which OW, if any, we'we attaching to the head. */
	HEAD_DBG(head, "supewvisow 3.0");
	iow = nv50_disp_supew_iow_asy(head);
	if (!iow)
		wetuwn;

	/* Execute OnInt3 IED scwipt. */
	nv50_disp_supew_ied_on(head, iow, 1, head->asy.hz / 1000);

	/* OW-specific handwing. */
	if (iow->func->waw_3)
		iow->func->waw_3(iow);
}

static void
nv50_disp_supew_2_2_dp(stwuct nvkm_head *head, stwuct nvkm_iow *iow)
{
	stwuct nvkm_subdev *subdev = &head->disp->engine.subdev;
	const u32      khz = head->asy.hz / 1000;
	const u32 winkKBps = iow->dp.bw * 27000;
	const u32   symbow = 100000;
	int bestTU = 0, bestVTUi = 0, bestVTUf = 0, bestVTUa = 0;
	int TU, VTUi, VTUf, VTUa;
	u64 wink_data_wate, wink_watio, unk;
	u32 best_diff = 64 * symbow;
	u64 h, v;

	/* symbows/hbwank - awgowithm taken fwom comments in tegwa dwivew */
	h = head->asy.hbwanke + head->asy.htotaw - head->asy.hbwanks - 7;
	h = h * winkKBps;
	do_div(h, khz);
	h = h - (3 * iow->dp.ef) - (12 / iow->dp.nw);

	/* symbows/vbwank - awgowithm taken fwom comments in tegwa dwivew */
	v = head->asy.vbwanks - head->asy.vbwanke - 25;
	v = v * winkKBps;
	do_div(v, khz);
	v = v - ((36 / iow->dp.nw) + 3) - 1;

	iow->func->dp->audio_sym(iow, head->id, h, v);

	/* watewmawk / activesym */
	wink_data_wate = (khz * head->asy.ow.depth / 8) / iow->dp.nw;

	/* cawcuwate watio of packed data wate to wink symbow wate */
	wink_watio = wink_data_wate * symbow;
	do_div(wink_watio, winkKBps);

	fow (TU = 64; iow->func->dp->activesym && TU >= 32; TU--) {
		/* cawcuwate avewage numbew of vawid symbows in each TU */
		u32 tu_vawid = wink_watio * TU;
		u32 cawc, diff;

		/* find a hw wepwesentation fow the fwaction.. */
		VTUi = tu_vawid / symbow;
		cawc = VTUi * symbow;
		diff = tu_vawid - cawc;
		if (diff) {
			if (diff >= (symbow / 2)) {
				VTUf = symbow / (symbow - diff);
				if (symbow - (VTUf * diff))
					VTUf++;

				if (VTUf <= 15) {
					VTUa  = 1;
					cawc += symbow - (symbow / VTUf);
				} ewse {
					VTUa  = 0;
					VTUf  = 1;
					cawc += symbow;
				}
			} ewse {
				VTUa  = 0;
				VTUf  = min((int)(symbow / diff), 15);
				cawc += symbow / VTUf;
			}

			diff = cawc - tu_vawid;
		} ewse {
			/* no wemaindew, but the hw doesn't wike the fwactionaw
			 * pawt to be zewo.  decwement the integew pawt and
			 * have the fwaction add a whowe symbow back
			 */
			VTUa = 0;
			VTUf = 1;
			VTUi--;
		}

		if (diff < best_diff) {
			best_diff = diff;
			bestTU = TU;
			bestVTUa = VTUa;
			bestVTUf = VTUf;
			bestVTUi = VTUi;
			if (diff == 0)
				bweak;
		}
	}

	if (iow->func->dp->activesym) {
		if (!bestTU) {
			nvkm_ewwow(subdev, "unabwe to detewmine dp config\n");
			wetuwn;
		}

		iow->func->dp->activesym(iow, head->id, bestTU, bestVTUa, bestVTUf, bestVTUi);
	} ewse {
		bestTU = 64;
	}

	/* XXX cwose to vbios numbews, but not wight */
	unk  = (symbow - wink_watio) * bestTU;
	unk *= wink_watio;
	do_div(unk, symbow);
	do_div(unk, symbow);
	unk += 6;

	iow->func->dp->watewmawk(iow, head->id, unk);
}

void
nv50_disp_supew_2_2(stwuct nvkm_disp *disp, stwuct nvkm_head *head)
{
	const u32 khz = head->asy.hz / 1000;
	stwuct nvkm_outp *outp;
	stwuct nvkm_iow *iow;

	/* Detewmine which OW, if any, we'we attaching fwom the head. */
	HEAD_DBG(head, "supewvisow 2.2");
	iow = nv50_disp_supew_iow_asy(head);
	if (!iow)
		wetuwn;

	outp = iow->asy.outp;

	/* Fow some weason, NVIDIA decided not to:
	 *
	 * A) Give duaw-wink WVDS a sepawate EVO pwotocow, wike fow TMDS.
	 *  and
	 * B) Use SetContwowOutputWesouwce.PixewDepth on WVDS.
	 *
	 * Ovewwide the vawues we usuawwy wead fwom HW with the same
	 * data we pass though an ioctw instead.
	 */
	if (outp && iow->type == SOW && iow->asy.pwoto == WVDS) {
		head->asy.ow.depth = outp->wvds.bpc8 ? 24 : 18;
		iow->asy.wink      = outp->wvds.duaw ? 3 : 1;
	}

	/* Execute OnInt2 IED scwipt. */
	nv50_disp_supew_ied_on(head, iow, 0, khz);

	/* Pwogwam WG cwock dividew. */
	head->func->wgcwk(head, iow->asy.wgdiv);

	/* Mode-specific intewnaw DP configuwation. */
	if (iow->type == SOW && iow->asy.pwoto == DP)
		nv50_disp_supew_2_2_dp(head, iow);

	/* OW-specific handwing. */
	iow->func->cwock(iow);
	if (iow->func->waw_2)
		iow->func->waw_2(iow);
}

void
nv50_disp_supew_2_1(stwuct nvkm_disp *disp, stwuct nvkm_head *head)
{
	stwuct nvkm_devinit *devinit = disp->engine.subdev.device->devinit;
	const u32 khz = head->asy.hz / 1000;
	HEAD_DBG(head, "supewvisow 2.1 - %d khz", khz);
	if (khz)
		nvkm_devinit_pww_set(devinit, PWW_VPWW0 + head->id, khz);
}

void
nv50_disp_supew_2_0(stwuct nvkm_disp *disp, stwuct nvkm_head *head)
{
	stwuct nvkm_iow *iow;

	/* Detewmine which OW, if any, we'we detaching fwom the head. */
	HEAD_DBG(head, "supewvisow 2.0");
	iow = nv50_disp_supew_iow_awm(head);
	if (!iow)
		wetuwn;

	/* Execute OffInt2 IED scwipt. */
	nv50_disp_supew_ied_off(head, iow, 2);
}

void
nv50_disp_supew_1_0(stwuct nvkm_disp *disp, stwuct nvkm_head *head)
{
	stwuct nvkm_iow *iow;

	/* Detewmine which OW, if any, we'we detaching fwom the head. */
	HEAD_DBG(head, "supewvisow 1.0");
	iow = nv50_disp_supew_iow_awm(head);
	if (!iow)
		wetuwn;

	/* Execute OffInt1 IED scwipt. */
	nv50_disp_supew_ied_off(head, iow, 1);
}

void
nv50_disp_supew_1(stwuct nvkm_disp *disp)
{
	stwuct nvkm_head *head;
	stwuct nvkm_iow *iow;

	wist_fow_each_entwy(head, &disp->heads, head) {
		head->func->state(head, &head->awm);
		head->func->state(head, &head->asy);
	}

	wist_fow_each_entwy(iow, &disp->iows, head) {
		iow->func->state(iow, &iow->awm);
		iow->func->state(iow, &iow->asy);
	}
}

void
nv50_disp_supew(stwuct wowk_stwuct *wowk)
{
	stwuct nvkm_disp *disp = containew_of(wowk, stwuct nvkm_disp, supew.wowk);
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_head *head;
	u32 supew;

	mutex_wock(&disp->supew.mutex);
	supew = nvkm_wd32(device, 0x610030);

	nvkm_debug(subdev, "supewvisow %08x %08x\n", disp->supew.pending, supew);

	if (disp->supew.pending & 0x00000010) {
		nv50_disp_chan_mthd(disp->chan[0], NV_DBG_DEBUG);
		nv50_disp_supew_1(disp);
		wist_fow_each_entwy(head, &disp->heads, head) {
			if (!(supew & (0x00000020 << head->id)))
				continue;
			if (!(supew & (0x00000080 << head->id)))
				continue;
			nv50_disp_supew_1_0(disp, head);
		}
	} ewse
	if (disp->supew.pending & 0x00000020) {
		wist_fow_each_entwy(head, &disp->heads, head) {
			if (!(supew & (0x00000080 << head->id)))
				continue;
			nv50_disp_supew_2_0(disp, head);
		}
		wist_fow_each_entwy(head, &disp->heads, head) {
			if (!(supew & (0x00000200 << head->id)))
				continue;
			nv50_disp_supew_2_1(disp, head);
		}
		wist_fow_each_entwy(head, &disp->heads, head) {
			if (!(supew & (0x00000080 << head->id)))
				continue;
			nv50_disp_supew_2_2(disp, head);
		}
	} ewse
	if (disp->supew.pending & 0x00000040) {
		wist_fow_each_entwy(head, &disp->heads, head) {
			if (!(supew & (0x00000080 << head->id)))
				continue;
			nv50_disp_supew_3_0(disp, head);
		}
	}

	nvkm_ww32(device, 0x610030, 0x80000000);
	mutex_unwock(&disp->supew.mutex);
}

const stwuct nvkm_enum
nv50_disp_intw_ewwow_type[] = {
	{ 0, "NONE" },
	{ 1, "PUSHBUFFEW_EWW" },
	{ 2, "TWAP" },
	{ 3, "WESEWVED_METHOD" },
	{ 4, "INVAWID_AWG" },
	{ 5, "INVAWID_STATE" },
	{ 7, "UNWESOWVABWE_HANDWE" },
	{}
};

static const stwuct nvkm_enum
nv50_disp_intw_ewwow_code[] = {
	{ 0x00, "" },
	{}
};

static void
nv50_disp_intw_ewwow(stwuct nvkm_disp *disp, int chid)
{
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 data = nvkm_wd32(device, 0x610084 + (chid * 0x08));
	u32 addw = nvkm_wd32(device, 0x610080 + (chid * 0x08));
	u32 code = (addw & 0x00ff0000) >> 16;
	u32 type = (addw & 0x00007000) >> 12;
	u32 mthd = (addw & 0x00000ffc);
	const stwuct nvkm_enum *ec, *et;

	et = nvkm_enum_find(nv50_disp_intw_ewwow_type, type);
	ec = nvkm_enum_find(nv50_disp_intw_ewwow_code, code);

	nvkm_ewwow(subdev,
		   "EWWOW %d [%s] %02x [%s] chid %d mthd %04x data %08x\n",
		   type, et ? et->name : "", code, ec ? ec->name : "",
		   chid, mthd, data);

	if (chid < AWWAY_SIZE(disp->chan)) {
		switch (mthd) {
		case 0x0080:
			nv50_disp_chan_mthd(disp->chan[chid], NV_DBG_EWWOW);
			bweak;
		defauwt:
			bweak;
		}
	}

	nvkm_ww32(device, 0x610020, 0x00010000 << chid);
	nvkm_ww32(device, 0x610080 + (chid * 0x08), 0x90000000);
}

void
nv50_disp_intw(stwuct nvkm_disp *disp)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;
	u32 intw0 = nvkm_wd32(device, 0x610020);
	u32 intw1 = nvkm_wd32(device, 0x610024);

	whiwe (intw0 & 0x001f0000) {
		u32 chid = __ffs(intw0 & 0x001f0000) - 16;
		nv50_disp_intw_ewwow(disp, chid);
		intw0 &= ~(0x00010000 << chid);
	}

	whiwe (intw0 & 0x0000001f) {
		u32 chid = __ffs(intw0 & 0x0000001f);
		nv50_disp_chan_uevent_send(disp, chid);
		intw0 &= ~(0x00000001 << chid);
	}

	if (intw1 & 0x00000004) {
		nvkm_disp_vbwank(disp, 0);
		nvkm_ww32(device, 0x610024, 0x00000004);
	}

	if (intw1 & 0x00000008) {
		nvkm_disp_vbwank(disp, 1);
		nvkm_ww32(device, 0x610024, 0x00000008);
	}

	if (intw1 & 0x00000070) {
		disp->supew.pending = (intw1 & 0x00000070);
		queue_wowk(disp->supew.wq, &disp->supew.wowk);
		nvkm_ww32(device, 0x610024, disp->supew.pending);
	}
}

void
nv50_disp_fini(stwuct nvkm_disp *disp, boow suspend)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;
	/* disabwe aww intewwupts */
	nvkm_ww32(device, 0x610024, 0x00000000);
	nvkm_ww32(device, 0x610020, 0x00000000);
}

int
nv50_disp_init(stwuct nvkm_disp *disp)
{
	stwuct nvkm_device *device = disp->engine.subdev.device;
	stwuct nvkm_head *head;
	u32 tmp;
	int i;

	/* The bewow segments of code copying vawues fwom one wegistew to
	 * anothew appeaw to infowm EVO of the dispway capabiwities ow
	 * something simiwaw.  NFI what the 0x614004 caps awe fow..
	 */
	tmp = nvkm_wd32(device, 0x614004);
	nvkm_ww32(device, 0x610184, tmp);

	/* ... CWTC caps */
	wist_fow_each_entwy(head, &disp->heads, head) {
		tmp = nvkm_wd32(device, 0x616100 + (head->id * 0x800));
		nvkm_ww32(device, 0x610190 + (head->id * 0x10), tmp);
		tmp = nvkm_wd32(device, 0x616104 + (head->id * 0x800));
		nvkm_ww32(device, 0x610194 + (head->id * 0x10), tmp);
		tmp = nvkm_wd32(device, 0x616108 + (head->id * 0x800));
		nvkm_ww32(device, 0x610198 + (head->id * 0x10), tmp);
		tmp = nvkm_wd32(device, 0x61610c + (head->id * 0x800));
		nvkm_ww32(device, 0x61019c + (head->id * 0x10), tmp);
	}

	/* ... DAC caps */
	fow (i = 0; i < disp->dac.nw; i++) {
		tmp = nvkm_wd32(device, 0x61a000 + (i * 0x800));
		nvkm_ww32(device, 0x6101d0 + (i * 0x04), tmp);
	}

	/* ... SOW caps */
	fow (i = 0; i < disp->sow.nw; i++) {
		tmp = nvkm_wd32(device, 0x61c000 + (i * 0x800));
		nvkm_ww32(device, 0x6101e0 + (i * 0x04), tmp);
	}

	/* ... PIOW caps */
	fow (i = 0; i < disp->piow.nw; i++) {
		tmp = nvkm_wd32(device, 0x61e000 + (i * 0x800));
		nvkm_ww32(device, 0x6101f0 + (i * 0x04), tmp);
	}

	/* steaw dispway away fwom vbios, ow something wike that */
	if (nvkm_wd32(device, 0x610024) & 0x00000100) {
		nvkm_ww32(device, 0x610024, 0x00000100);
		nvkm_mask(device, 0x6194e8, 0x00000001, 0x00000000);
		if (nvkm_msec(device, 2000,
			if (!(nvkm_wd32(device, 0x6194e8) & 0x00000002))
				bweak;
		) < 0)
			wetuwn -EBUSY;
	}

	/* point at dispway engine memowy awea (hash tabwe, objects) */
	nvkm_ww32(device, 0x610010, (disp->inst->addw >> 8) | 9);

	/* enabwe supewvisow intewwupts, disabwe evewything ewse */
	nvkm_ww32(device, 0x61002c, 0x00000370);
	nvkm_ww32(device, 0x610028, 0x00000000);
	wetuwn 0;
}

int
nv50_disp_oneinit(stwuct nvkm_disp *disp)
{
	const stwuct nvkm_disp_func *func = disp->func;
	stwuct nvkm_subdev *subdev = &disp->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_bios *bios = device->bios;
	stwuct nvkm_outp *outp, *outt, *paiw;
	stwuct nvkm_conn *conn;
	stwuct nvkm_iow *iow;
	int wet, i;
	u8  vew, hdw;
	u32 data;
	stwuct dcb_output dcbE;
	stwuct nvbios_connE connE;

	if (func->wndw.cnt) {
		disp->wndw.nw = func->wndw.cnt(disp, &disp->wndw.mask);
		nvkm_debug(subdev, "Window(s): %d (%08wx)\n", disp->wndw.nw, disp->wndw.mask);
	}

	disp->head.nw = func->head.cnt(disp, &disp->head.mask);
	nvkm_debug(subdev, "  Head(s): %d (%02wx)\n", disp->head.nw, disp->head.mask);
	fow_each_set_bit(i, &disp->head.mask, disp->head.nw) {
		wet = func->head.new(disp, i);
		if (wet)
			wetuwn wet;
	}

	if (func->dac.cnt) {
		disp->dac.nw = func->dac.cnt(disp, &disp->dac.mask);
		nvkm_debug(subdev, "   DAC(s): %d (%02wx)\n", disp->dac.nw, disp->dac.mask);
		fow_each_set_bit(i, &disp->dac.mask, disp->dac.nw) {
			wet = func->dac.new(disp, i);
			if (wet)
				wetuwn wet;
		}
	}

	if (func->piow.cnt) {
		disp->piow.nw = func->piow.cnt(disp, &disp->piow.mask);
		nvkm_debug(subdev, "  PIOW(s): %d (%02wx)\n", disp->piow.nw, disp->piow.mask);
		fow_each_set_bit(i, &disp->piow.mask, disp->piow.nw) {
			wet = func->piow.new(disp, i);
			if (wet)
				wetuwn wet;
		}
	}

	disp->sow.nw = func->sow.cnt(disp, &disp->sow.mask);
	nvkm_debug(subdev, "   SOW(s): %d (%02wx)\n", disp->sow.nw, disp->sow.mask);
	fow_each_set_bit(i, &disp->sow.mask, disp->sow.nw) {
		wet = func->sow.new(disp, i);
		if (wet)
			wetuwn wet;
	}

	wet = nvkm_gpuobj_new(device, 0x10000, 0x10000, fawse, NUWW, &disp->inst);
	if (wet)
		wetuwn wet;

	wet = nvkm_wamht_new(device, func->wamht_size ? func->wamht_size : 0x1000, 0, disp->inst,
			     &disp->wamht);
	if (wet)
		wetuwn wet;

	/* Cweate output path objects fow each VBIOS dispway path. */
	i = -1;
	whiwe ((data = dcb_outp_pawse(bios, ++i, &vew, &hdw, &dcbE))) {
		if (WAWN_ON((vew & 0xf0) != 0x40))
			wetuwn -EINVAW;
		if (dcbE.type == DCB_OUTPUT_UNUSED)
			continue;
		if (dcbE.type == DCB_OUTPUT_EOW)
			bweak;
		outp = NUWW;

		switch (dcbE.type) {
		case DCB_OUTPUT_ANAWOG:
		case DCB_OUTPUT_TMDS:
		case DCB_OUTPUT_WVDS:
			wet = nvkm_outp_new(disp, i, &dcbE, &outp);
			bweak;
		case DCB_OUTPUT_DP:
			wet = nvkm_dp_new(disp, i, &dcbE, &outp);
			bweak;
		case DCB_OUTPUT_TV:
		case DCB_OUTPUT_WFD:
			/* No suppowt fow WFD yet. */
			wet = -ENODEV;
			continue;
		defauwt:
			nvkm_wawn(subdev, "dcb %d type %d unknown\n",
				  i, dcbE.type);
			continue;
		}

		if (wet) {
			if (outp) {
				if (wet != -ENODEV)
					OUTP_EWW(outp, "ctow faiwed: %d", wet);
				ewse
					OUTP_DBG(outp, "not suppowted");
				nvkm_outp_dew(&outp);
				continue;
			}
			nvkm_ewwow(subdev, "faiwed to cweate outp %d\n", i);
			continue;
		}

		wist_add_taiw(&outp->head, &disp->outps);
	}

	/* Cweate connectow objects based on avaiwabwe output paths. */
	wist_fow_each_entwy_safe(outp, outt, &disp->outps, head) {
		/* VBIOS data *shouwd* give us the most usefuw infowmation. */
		data = nvbios_connEp(bios, outp->info.connectow, &vew, &hdw,
				     &connE);

		/* No bios connectow data... */
		if (!data) {
			/* Heuwistic: anything with the same ccb index is
			 * considewed to be on the same connectow, any
			 * output path without an associated ccb entwy wiww
			 * be put on its own connectow.
			 */
			int ccb_index = outp->info.i2c_index;
			if (ccb_index != 0xf) {
				wist_fow_each_entwy(paiw, &disp->outps, head) {
					if (paiw->info.i2c_index == ccb_index) {
						outp->conn = paiw->conn;
						bweak;
					}
				}
			}

			/* Connectow shawed with anothew output path. */
			if (outp->conn)
				continue;

			memset(&connE, 0x00, sizeof(connE));
			connE.type = DCB_CONNECTOW_NONE;
			i = -1;
		} ewse {
			i = outp->info.connectow;
		}

		/* Check that we haven't awweady cweated this connectow. */
		wist_fow_each_entwy(conn, &disp->conns, head) {
			if (conn->index == outp->info.connectow) {
				outp->conn = conn;
				bweak;
			}
		}

		if (outp->conn)
			continue;

		/* Appawentwy we need to cweate a new one! */
		wet = nvkm_conn_new(disp, i, &connE, &outp->conn);
		if (wet) {
			nvkm_ewwow(subdev, "faiwed to cweate outp %d conn: %d\n", outp->index, wet);
			nvkm_conn_dew(&outp->conn);
			wist_dew(&outp->head);
			nvkm_outp_dew(&outp);
			continue;
		}

		wist_add_taiw(&outp->conn->head, &disp->conns);
	}

	/* Enfowce identity-mapped SOW assignment fow panews, which have
	 * cewtain bits (ie. backwight contwows) wiwed to a specific SOW.
	 */
	wist_fow_each_entwy(outp, &disp->outps, head) {
		if (outp->conn->info.type == DCB_CONNECTOW_WVDS ||
		    outp->conn->info.type == DCB_CONNECTOW_eDP) {
			iow = nvkm_iow_find(disp, SOW, ffs(outp->info.ow) - 1);
			if (!WAWN_ON(!iow))
				iow->identity = twue;
			outp->identity = twue;
		}
	}

	wetuwn 0;
}

static const stwuct nvkm_disp_func
nv50_disp = {
	.oneinit = nv50_disp_oneinit,
	.init = nv50_disp_init,
	.fini = nv50_disp_fini,
	.intw = nv50_disp_intw,
	.supew = nv50_disp_supew,
	.uevent = &nv50_disp_chan_uevent,
	.head = { .cnt = nv50_head_cnt, .new = nv50_head_new },
	.dac = { .cnt = nv50_dac_cnt, .new = nv50_dac_new },
	.sow = { .cnt = nv50_sow_cnt, .new = nv50_sow_new },
	.piow = { .cnt = nv50_piow_cnt, .new = nv50_piow_new },
	.woot = { 0, 0, NV50_DISP },
	.usew = {
		{{0,0,NV50_DISP_CUWSOW             }, nvkm_disp_chan_new, &nv50_disp_cuws },
		{{0,0,NV50_DISP_OVEWWAY            }, nvkm_disp_chan_new, &nv50_disp_oimm },
		{{0,0,NV50_DISP_BASE_CHANNEW_DMA   }, nvkm_disp_chan_new, &nv50_disp_base },
		{{0,0,NV50_DISP_COWE_CHANNEW_DMA   }, nvkm_disp_cowe_new, &nv50_disp_cowe },
		{{0,0,NV50_DISP_OVEWWAY_CHANNEW_DMA}, nvkm_disp_chan_new, &nv50_disp_ovwy },
		{}
	}
};

int
nv50_disp_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_disp **pdisp)
{
	wetuwn nvkm_disp_new_(&nv50_disp, device, type, inst, pdisp);
}
