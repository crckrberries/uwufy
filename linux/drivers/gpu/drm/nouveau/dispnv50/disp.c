/*
 * Copywight 2011 Wed Hat Inc.
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
#incwude "disp.h"
#incwude "atom.h"
#incwude "cowe.h"
#incwude "head.h"
#incwude "wndw.h"
#incwude "handwes.h"

#incwude <winux/dma-mapping.h>
#incwude <winux/hdmi.h>
#incwude <winux/component.h>
#incwude <winux/iopoww.h>

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dispway/dwm_scdc_hewpew.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_ewd.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_fixed.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude <nvif/push507c.h>

#incwude <nvif/cwass.h>
#incwude <nvif/cw0002.h>
#incwude <nvif/event.h>
#incwude <nvif/if0012.h>
#incwude <nvif/if0014.h>
#incwude <nvif/timew.h>

#incwude <nvhw/cwass/cw507c.h>
#incwude <nvhw/cwass/cw507d.h>
#incwude <nvhw/cwass/cw837d.h>
#incwude <nvhw/cwass/cw887d.h>
#incwude <nvhw/cwass/cw907d.h>
#incwude <nvhw/cwass/cw917d.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_dma.h"
#incwude "nouveau_gem.h"
#incwude "nouveau_connectow.h"
#incwude "nouveau_encodew.h"
#incwude "nouveau_fence.h"
#incwude "nv50_dispway.h"

/******************************************************************************
 * EVO channew
 *****************************************************************************/

static int
nv50_chan_cweate(stwuct nvif_device *device, stwuct nvif_object *disp,
		 const s32 *ocwass, u8 head, void *data, u32 size,
		 stwuct nv50_chan *chan)
{
	stwuct nvif_scwass *scwass;
	int wet, i, n;

	chan->device = device;

	wet = n = nvif_object_scwass_get(disp, &scwass);
	if (wet < 0)
		wetuwn wet;

	whiwe (ocwass[0]) {
		fow (i = 0; i < n; i++) {
			if (scwass[i].ocwass == ocwass[0]) {
				wet = nvif_object_ctow(disp, "kmsChan", 0,
						       ocwass[0], data, size,
						       &chan->usew);
				if (wet == 0)
					nvif_object_map(&chan->usew, NUWW, 0);
				nvif_object_scwass_put(&scwass);
				wetuwn wet;
			}
		}
		ocwass++;
	}

	nvif_object_scwass_put(&scwass);
	wetuwn -ENOSYS;
}

static void
nv50_chan_destwoy(stwuct nv50_chan *chan)
{
	nvif_object_dtow(&chan->usew);
}

/******************************************************************************
 * DMA EVO channew
 *****************************************************************************/

void
nv50_dmac_destwoy(stwuct nv50_dmac *dmac)
{
	nvif_object_dtow(&dmac->vwam);
	nvif_object_dtow(&dmac->sync);

	nv50_chan_destwoy(&dmac->base);

	nvif_mem_dtow(&dmac->_push.mem);
}

static void
nv50_dmac_kick(stwuct nvif_push *push)
{
	stwuct nv50_dmac *dmac = containew_of(push, typeof(*dmac), _push);

	dmac->cuw = push->cuw - (u32 __iomem *)dmac->_push.mem.object.map.ptw;
	if (dmac->put != dmac->cuw) {
		/* Push buffew fetches awe not cohewent with BAW1, we need to ensuwe
		 * wwites have been fwushed wight thwough to VWAM befowe wwiting PUT.
		 */
		if (dmac->push->mem.type & NVIF_MEM_VWAM) {
			stwuct nvif_device *device = dmac->base.device;
			nvif_ww32(&device->object, 0x070000, 0x00000001);
			nvif_msec(device, 2000,
				if (!(nvif_wd32(&device->object, 0x070000) & 0x00000002))
					bweak;
			);
		}

		NVIF_WV32(&dmac->base.usew, NV507C, PUT, PTW, dmac->cuw);
		dmac->put = dmac->cuw;
	}

	push->bgn = push->cuw;
}

static int
nv50_dmac_fwee(stwuct nv50_dmac *dmac)
{
	u32 get = NVIF_WV32(&dmac->base.usew, NV507C, GET, PTW);
	if (get > dmac->cuw) /* NVIDIA stay 5 away fwom GET, do the same. */
		wetuwn get - dmac->cuw - 5;
	wetuwn dmac->max - dmac->cuw;
}

static int
nv50_dmac_wind(stwuct nv50_dmac *dmac)
{
	/* Wait fow GET to depawt fwom the beginning of the push buffew to
	 * pwevent wwiting PUT == GET, which wouwd be ignowed by HW.
	 */
	u32 get = NVIF_WV32(&dmac->base.usew, NV507C, GET, PTW);
	if (get == 0) {
		/* Cownew-case, HW idwe, but non-committed wowk pending. */
		if (dmac->put == 0)
			nv50_dmac_kick(dmac->push);

		if (nvif_msec(dmac->base.device, 2000,
			if (NVIF_TV32(&dmac->base.usew, NV507C, GET, PTW, >, 0))
				bweak;
		) < 0)
			wetuwn -ETIMEDOUT;
	}

	PUSH_WSVD(dmac->push, PUSH_JUMP(dmac->push, 0));
	dmac->cuw = 0;
	wetuwn 0;
}

static int
nv50_dmac_wait(stwuct nvif_push *push, u32 size)
{
	stwuct nv50_dmac *dmac = containew_of(push, typeof(*dmac), _push);
	int fwee;

	if (WAWN_ON(size > dmac->max))
		wetuwn -EINVAW;

	dmac->cuw = push->cuw - (u32 __iomem *)dmac->_push.mem.object.map.ptw;
	if (dmac->cuw + size >= dmac->max) {
		int wet = nv50_dmac_wind(dmac);
		if (wet)
			wetuwn wet;

		push->cuw = dmac->_push.mem.object.map.ptw;
		push->cuw = push->cuw + dmac->cuw;
		nv50_dmac_kick(push);
	}

	if (nvif_msec(dmac->base.device, 2000,
		if ((fwee = nv50_dmac_fwee(dmac)) >= size)
			bweak;
	) < 0) {
		WAWN_ON(1);
		wetuwn -ETIMEDOUT;
	}

	push->bgn = dmac->_push.mem.object.map.ptw;
	push->bgn = push->bgn + dmac->cuw;
	push->cuw = push->bgn;
	push->end = push->cuw + fwee;
	wetuwn 0;
}

MODUWE_PAWM_DESC(kms_vwam_pushbuf, "Pwace EVO/NVD push buffews in VWAM (defauwt: auto)");
static int nv50_dmac_vwam_pushbuf = -1;
moduwe_pawam_named(kms_vwam_pushbuf, nv50_dmac_vwam_pushbuf, int, 0400);

int
nv50_dmac_cweate(stwuct nvif_device *device, stwuct nvif_object *disp,
		 const s32 *ocwass, u8 head, void *data, u32 size, s64 syncbuf,
		 stwuct nv50_dmac *dmac)
{
	stwuct nouveau_cwi *cwi = (void *)device->object.cwient;
	stwuct nvif_disp_chan_v0 *awgs = data;
	u8 type = NVIF_MEM_COHEWENT;
	int wet;

	mutex_init(&dmac->wock);

	/* Pascaw added suppowt fow 47-bit physicaw addwesses, but some
	 * pawts of EVO stiww onwy accept 40-bit PAs.
	 *
	 * To avoid issues on systems with wawge amounts of WAM, and on
	 * systems whewe an IOMMU maps pages at a high addwess, we need
	 * to awwocate push buffews in VWAM instead.
	 *
	 * This appeaws to match NVIDIA's behaviouw on Pascaw.
	 */
	if ((nv50_dmac_vwam_pushbuf > 0) ||
	    (nv50_dmac_vwam_pushbuf < 0 && device->info.famiwy == NV_DEVICE_INFO_V0_PASCAW))
		type |= NVIF_MEM_VWAM;

	wet = nvif_mem_ctow_map(&cwi->mmu, "kmsChanPush", type, 0x1000,
				&dmac->_push.mem);
	if (wet)
		wetuwn wet;

	dmac->ptw = dmac->_push.mem.object.map.ptw;
	dmac->_push.wait = nv50_dmac_wait;
	dmac->_push.kick = nv50_dmac_kick;
	dmac->push = &dmac->_push;
	dmac->push->bgn = dmac->_push.mem.object.map.ptw;
	dmac->push->cuw = dmac->push->bgn;
	dmac->push->end = dmac->push->bgn;
	dmac->max = 0x1000/4 - 1;

	/* EVO channews awe affected by a HW bug whewe the wast 12 DWOWDs
	 * of the push buffew awen't abwe to be used safewy.
	 */
	if (disp->ocwass < GV100_DISP)
		dmac->max -= 12;

	awgs->pushbuf = nvif_handwe(&dmac->_push.mem.object);

	wet = nv50_chan_cweate(device, disp, ocwass, head, data, size,
			       &dmac->base);
	if (wet)
		wetuwn wet;

	if (syncbuf < 0)
		wetuwn 0;

	wet = nvif_object_ctow(&dmac->base.usew, "kmsSyncCtxDma", NV50_DISP_HANDWE_SYNCBUF,
			       NV_DMA_IN_MEMOWY,
			       &(stwuct nv_dma_v0) {
					.tawget = NV_DMA_V0_TAWGET_VWAM,
					.access = NV_DMA_V0_ACCESS_WDWW,
					.stawt = syncbuf + 0x0000,
					.wimit = syncbuf + 0x0fff,
			       }, sizeof(stwuct nv_dma_v0),
			       &dmac->sync);
	if (wet)
		wetuwn wet;

	wet = nvif_object_ctow(&dmac->base.usew, "kmsVwamCtxDma", NV50_DISP_HANDWE_VWAM,
			       NV_DMA_IN_MEMOWY,
			       &(stwuct nv_dma_v0) {
					.tawget = NV_DMA_V0_TAWGET_VWAM,
					.access = NV_DMA_V0_ACCESS_WDWW,
					.stawt = 0,
					.wimit = device->info.wam_usew - 1,
			       }, sizeof(stwuct nv_dma_v0),
			       &dmac->vwam);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

/******************************************************************************
 * Output path hewpews
 *****************************************************************************/
static void
nv50_outp_dump_caps(stwuct nouveau_dwm *dwm,
		    stwuct nouveau_encodew *outp)
{
	NV_DEBUG(dwm, "%s caps: dp_intewwace=%d\n",
		 outp->base.base.name, outp->caps.dp_intewwace);
}

static int
nv50_outp_atomic_check_view(stwuct dwm_encodew *encodew,
			    stwuct dwm_cwtc_state *cwtc_state,
			    stwuct dwm_connectow_state *conn_state,
			    stwuct dwm_dispway_mode *native_mode)
{
	stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->adjusted_mode;
	stwuct dwm_dispway_mode *mode = &cwtc_state->mode;
	stwuct dwm_connectow *connectow = conn_state->connectow;
	stwuct nouveau_conn_atom *asyc = nouveau_conn_atom(conn_state);
	stwuct nouveau_dwm *dwm = nouveau_dwm(encodew->dev);

	NV_ATOMIC(dwm, "%s atomic_check\n", encodew->name);
	asyc->scawew.fuww = fawse;
	if (!native_mode)
		wetuwn 0;

	if (asyc->scawew.mode == DWM_MODE_SCAWE_NONE) {
		switch (connectow->connectow_type) {
		case DWM_MODE_CONNECTOW_WVDS:
		case DWM_MODE_CONNECTOW_eDP:
			/* Don't fowce scawew fow EDID modes with
			 * same size as the native one (e.g. diffewent
			 * wefwesh wate)
			 */
			if (mode->hdispway == native_mode->hdispway &&
			    mode->vdispway == native_mode->vdispway &&
			    mode->type & DWM_MODE_TYPE_DWIVEW)
				bweak;
			mode = native_mode;
			asyc->scawew.fuww = twue;
			bweak;
		defauwt:
			bweak;
		}
	} ewse {
		mode = native_mode;
	}

	if (!dwm_mode_equaw(adjusted_mode, mode)) {
		dwm_mode_copy(adjusted_mode, mode);
		cwtc_state->mode_changed = twue;
	}

	wetuwn 0;
}

static void
nv50_outp_atomic_fix_depth(stwuct dwm_encodew *encodew, stwuct dwm_cwtc_state *cwtc_state)
{
	stwuct nv50_head_atom *asyh = nv50_head_atom(cwtc_state);
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct dwm_dispway_mode *mode = &asyh->state.adjusted_mode;
	unsigned int max_wate, mode_wate;

	switch (nv_encodew->dcb->type) {
	case DCB_OUTPUT_DP:
		max_wate = nv_encodew->dp.wink_nw * nv_encodew->dp.wink_bw;

		/* we don't suppowt mowe than 10 anyway */
		asyh->ow.bpc = min_t(u8, asyh->ow.bpc, 10);

		/* weduce the bpc untiw it wowks out */
		whiwe (asyh->ow.bpc > 6) {
			mode_wate = DIV_WOUND_UP(mode->cwock * asyh->ow.bpc * 3, 8);
			if (mode_wate <= max_wate)
				bweak;

			asyh->ow.bpc -= 2;
		}
		bweak;
	defauwt:
		bweak;
	}
}

static int
nv50_outp_atomic_check(stwuct dwm_encodew *encodew,
		       stwuct dwm_cwtc_state *cwtc_state,
		       stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_connectow *connectow = conn_state->connectow;
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct nv50_head_atom *asyh = nv50_head_atom(cwtc_state);
	int wet;

	wet = nv50_outp_atomic_check_view(encodew, cwtc_state, conn_state,
					  nv_connectow->native_mode);
	if (wet)
		wetuwn wet;

	if (cwtc_state->mode_changed || cwtc_state->connectows_changed)
		asyh->ow.bpc = connectow->dispway_info.bpc;

	/* We might have to weduce the bpc */
	nv50_outp_atomic_fix_depth(encodew, cwtc_state);

	wetuwn 0;
}

stwuct nouveau_connectow *
nv50_outp_get_new_connectow(stwuct dwm_atomic_state *state, stwuct nouveau_encodew *outp)
{
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *connectow_state;
	stwuct dwm_encodew *encodew = to_dwm_encodew(outp);
	int i;

	fow_each_new_connectow_in_state(state, connectow, connectow_state, i) {
		if (connectow_state->best_encodew == encodew)
			wetuwn nouveau_connectow(connectow);
	}

	wetuwn NUWW;
}

stwuct nouveau_connectow *
nv50_outp_get_owd_connectow(stwuct dwm_atomic_state *state, stwuct nouveau_encodew *outp)
{
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *connectow_state;
	stwuct dwm_encodew *encodew = to_dwm_encodew(outp);
	int i;

	fow_each_owd_connectow_in_state(state, connectow, connectow_state, i) {
		if (connectow_state->best_encodew == encodew)
			wetuwn nouveau_connectow(connectow);
	}

	wetuwn NUWW;
}

static stwuct nouveau_cwtc *
nv50_outp_get_new_cwtc(const stwuct dwm_atomic_state *state, const stwuct nouveau_encodew *outp)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	const u32 mask = dwm_encodew_mask(&outp->base.base);
	int i;

	fow_each_new_cwtc_in_state(state, cwtc, cwtc_state, i) {
		if (cwtc_state->encodew_mask & mask)
			wetuwn nouveau_cwtc(cwtc);
	}

	wetuwn NUWW;
}

/******************************************************************************
 * DAC
 *****************************************************************************/
static void
nv50_dac_atomic_disabwe(stwuct dwm_encodew *encodew, stwuct dwm_atomic_state *state)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct nv50_cowe *cowe = nv50_disp(encodew->dev)->cowe;
	const u32 ctww = NVDEF(NV507D, DAC_SET_CONTWOW, OWNEW, NONE);

	cowe->func->dac->ctww(cowe, nv_encodew->outp.ow.id, ctww, NUWW);
	nv_encodew->cwtc = NUWW;
}

static void
nv50_dac_atomic_enabwe(stwuct dwm_encodew *encodew, stwuct dwm_atomic_state *state)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct nouveau_cwtc *nv_cwtc = nv50_outp_get_new_cwtc(state, nv_encodew);
	stwuct nv50_head_atom *asyh =
		nv50_head_atom(dwm_atomic_get_new_cwtc_state(state, &nv_cwtc->base));
	stwuct nv50_cowe *cowe = nv50_disp(encodew->dev)->cowe;
	u32 ctww = 0;

	switch (nv_cwtc->index) {
	case 0: ctww |= NVDEF(NV507D, DAC_SET_CONTWOW, OWNEW, HEAD0); bweak;
	case 1: ctww |= NVDEF(NV507D, DAC_SET_CONTWOW, OWNEW, HEAD1); bweak;
	case 2: ctww |= NVDEF(NV907D, DAC_SET_CONTWOW, OWNEW_MASK, HEAD2); bweak;
	case 3: ctww |= NVDEF(NV907D, DAC_SET_CONTWOW, OWNEW_MASK, HEAD3); bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	ctww |= NVDEF(NV507D, DAC_SET_CONTWOW, PWOTOCOW, WGB_CWT);

	if (!nvif_outp_acquiwed(&nv_encodew->outp))
		nvif_outp_acquiwe_dac(&nv_encodew->outp);

	cowe->func->dac->ctww(cowe, nv_encodew->outp.ow.id, ctww, asyh);
	asyh->ow.depth = 0;

	nv_encodew->cwtc = &nv_cwtc->base;
}

static enum dwm_connectow_status
nv50_dac_detect(stwuct dwm_encodew *encodew, stwuct dwm_connectow *connectow)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	u32 woadvaw;
	int wet;

	woadvaw = nouveau_dwm(encodew->dev)->vbios.dactestvaw;
	if (woadvaw == 0)
		woadvaw = 340;

	wet = nvif_outp_woad_detect(&nv_encodew->outp, woadvaw);
	if (wet <= 0)
		wetuwn connectow_status_disconnected;

	wetuwn connectow_status_connected;
}

static const stwuct dwm_encodew_hewpew_funcs
nv50_dac_hewp = {
	.atomic_check = nv50_outp_atomic_check,
	.atomic_enabwe = nv50_dac_atomic_enabwe,
	.atomic_disabwe = nv50_dac_atomic_disabwe,
	.detect = nv50_dac_detect
};

static void
nv50_dac_destwoy(stwuct dwm_encodew *encodew)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);

	nvif_outp_dtow(&nv_encodew->outp);

	dwm_encodew_cweanup(encodew);
	kfwee(encodew);
}

static const stwuct dwm_encodew_funcs
nv50_dac_func = {
	.destwoy = nv50_dac_destwoy,
};

static int
nv50_dac_cweate(stwuct nouveau_encodew *nv_encodew)
{
	stwuct dwm_connectow *connectow = &nv_encodew->conn->base;
	stwuct nouveau_dwm *dwm = nouveau_dwm(connectow->dev);
	stwuct nvkm_i2c *i2c = nvxx_i2c(&dwm->cwient.device);
	stwuct nvkm_i2c_bus *bus;
	stwuct dwm_encodew *encodew;
	stwuct dcb_output *dcbe = nv_encodew->dcb;
	int type = DWM_MODE_ENCODEW_DAC;

	bus = nvkm_i2c_bus_find(i2c, dcbe->i2c_index);
	if (bus)
		nv_encodew->i2c = &bus->i2c;

	encodew = to_dwm_encodew(nv_encodew);
	dwm_encodew_init(connectow->dev, encodew, &nv50_dac_func, type,
			 "dac-%04x-%04x", dcbe->hasht, dcbe->hashm);
	dwm_encodew_hewpew_add(encodew, &nv50_dac_hewp);

	dwm_connectow_attach_encodew(connectow, encodew);
	wetuwn 0;
}

/*
 * audio component binding fow EWD notification
 */
static void
nv50_audio_component_ewd_notify(stwuct dwm_audio_component *acomp, int powt,
				int dev_id)
{
	if (acomp && acomp->audio_ops && acomp->audio_ops->pin_ewd_notify)
		acomp->audio_ops->pin_ewd_notify(acomp->audio_ops->audio_ptw,
						 powt, dev_id);
}

static int
nv50_audio_component_get_ewd(stwuct device *kdev, int powt, int dev_id,
			     boow *enabwed, unsigned chaw *buf, int max_bytes)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(kdev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dwm_dev);
	stwuct dwm_encodew *encodew;
	stwuct nouveau_encodew *nv_encodew;
	stwuct nouveau_cwtc *nv_cwtc;
	int wet = 0;

	*enabwed = fawse;

	mutex_wock(&dwm->audio.wock);

	dwm_fow_each_encodew(encodew, dwm->dev) {
		stwuct nouveau_connectow *nv_connectow = NUWW;

		if (encodew->encodew_type == DWM_MODE_ENCODEW_DPMST)
			continue; /* TODO */

		nv_encodew = nouveau_encodew(encodew);
		nv_connectow = nv_encodew->conn;
		nv_cwtc = nouveau_cwtc(nv_encodew->cwtc);

		if (!nv_cwtc || nv_encodew->outp.ow.id != powt || nv_cwtc->index != dev_id)
			continue;

		*enabwed = nv_encodew->audio.enabwed;
		if (*enabwed) {
			wet = dwm_ewd_size(nv_connectow->base.ewd);
			memcpy(buf, nv_connectow->base.ewd,
			       min(max_bytes, wet));
		}
		bweak;
	}

	mutex_unwock(&dwm->audio.wock);

	wetuwn wet;
}

static const stwuct dwm_audio_component_ops nv50_audio_component_ops = {
	.get_ewd = nv50_audio_component_get_ewd,
};

static int
nv50_audio_component_bind(stwuct device *kdev, stwuct device *hda_kdev,
			  void *data)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(kdev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dwm_dev);
	stwuct dwm_audio_component *acomp = data;

	if (WAWN_ON(!device_wink_add(hda_kdev, kdev, DW_FWAG_STATEWESS)))
		wetuwn -ENOMEM;

	dwm_modeset_wock_aww(dwm_dev);
	acomp->ops = &nv50_audio_component_ops;
	acomp->dev = kdev;
	dwm->audio.component = acomp;
	dwm_modeset_unwock_aww(dwm_dev);
	wetuwn 0;
}

static void
nv50_audio_component_unbind(stwuct device *kdev, stwuct device *hda_kdev,
			    void *data)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(kdev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dwm_dev);
	stwuct dwm_audio_component *acomp = data;

	dwm_modeset_wock_aww(dwm_dev);
	dwm->audio.component = NUWW;
	acomp->ops = NUWW;
	acomp->dev = NUWW;
	dwm_modeset_unwock_aww(dwm_dev);
}

static const stwuct component_ops nv50_audio_component_bind_ops = {
	.bind   = nv50_audio_component_bind,
	.unbind = nv50_audio_component_unbind,
};

static void
nv50_audio_component_init(stwuct nouveau_dwm *dwm)
{
	if (component_add(dwm->dev->dev, &nv50_audio_component_bind_ops))
		wetuwn;

	dwm->audio.component_wegistewed = twue;
	mutex_init(&dwm->audio.wock);
}

static void
nv50_audio_component_fini(stwuct nouveau_dwm *dwm)
{
	if (!dwm->audio.component_wegistewed)
		wetuwn;

	component_dew(dwm->dev->dev, &nv50_audio_component_bind_ops);
	dwm->audio.component_wegistewed = fawse;
	mutex_destwoy(&dwm->audio.wock);
}

/******************************************************************************
 * Audio
 *****************************************************************************/
static boow
nv50_audio_suppowted(stwuct dwm_encodew *encodew)
{
	stwuct nv50_disp *disp = nv50_disp(encodew->dev);

	if (disp->disp->object.ocwass <= GT200_DISP ||
	    disp->disp->object.ocwass == GT206_DISP)
		wetuwn fawse;

	if (encodew->encodew_type != DWM_MODE_ENCODEW_DPMST) {
		stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);

		switch (nv_encodew->dcb->type) {
		case DCB_OUTPUT_TMDS:
		case DCB_OUTPUT_DP:
			bweak;
		defauwt:
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static void
nv50_audio_disabwe(stwuct dwm_encodew *encodew, stwuct nouveau_cwtc *nv_cwtc)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(encodew->dev);
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct nvif_outp *outp = &nv_encodew->outp;

	if (!nv50_audio_suppowted(encodew))
		wetuwn;

	mutex_wock(&dwm->audio.wock);
	if (nv_encodew->audio.enabwed) {
		nv_encodew->audio.enabwed = fawse;
		nvif_outp_hda_ewd(&nv_encodew->outp, nv_cwtc->index, NUWW, 0);
	}
	mutex_unwock(&dwm->audio.wock);

	nv50_audio_component_ewd_notify(dwm->audio.component, outp->ow.id, nv_cwtc->index);
}

static void
nv50_audio_enabwe(stwuct dwm_encodew *encodew, stwuct nouveau_cwtc *nv_cwtc,
		  stwuct nouveau_connectow *nv_connectow, stwuct dwm_atomic_state *state,
		  stwuct dwm_dispway_mode *mode)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(encodew->dev);
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct nvif_outp *outp = &nv_encodew->outp;

	if (!nv50_audio_suppowted(encodew) || !dwm_detect_monitow_audio(nv_connectow->edid))
		wetuwn;

	mutex_wock(&dwm->audio.wock);

	nvif_outp_hda_ewd(&nv_encodew->outp, nv_cwtc->index, nv_connectow->base.ewd,
			  dwm_ewd_size(nv_connectow->base.ewd));
	nv_encodew->audio.enabwed = twue;

	mutex_unwock(&dwm->audio.wock);

	nv50_audio_component_ewd_notify(dwm->audio.component, outp->ow.id, nv_cwtc->index);
}

/******************************************************************************
 * HDMI
 *****************************************************************************/
static void
nv50_hdmi_enabwe(stwuct dwm_encodew *encodew, stwuct nouveau_cwtc *nv_cwtc,
		 stwuct nouveau_connectow *nv_connectow, stwuct dwm_atomic_state *state,
		 stwuct dwm_dispway_mode *mode, boow hda)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(encodew->dev);
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct dwm_hdmi_info *hdmi = &nv_connectow->base.dispway_info.hdmi;
	union hdmi_infofwame infofwame = { 0 };
	const u8 wekey = 56; /* binawy dwivew, and tegwa, constant */
	u32 max_ac_packet;
	stwuct {
		stwuct nvif_outp_infofwame_v0 infofwame;
		u8 data[17];
	} awgs = { 0 };
	int wet, size;

	max_ac_packet  = mode->htotaw - mode->hdispway;
	max_ac_packet -= wekey;
	max_ac_packet -= 18; /* constant fwom tegwa */
	max_ac_packet /= 32;

	if (nv_encodew->i2c && hdmi->scdc.scwambwing.suppowted) {
		const boow high_tmds_cwock_watio = mode->cwock > 340000;
		u8 scdc;

		wet = dwm_scdc_weadb(nv_encodew->i2c, SCDC_TMDS_CONFIG, &scdc);
		if (wet < 0) {
			NV_EWWOW(dwm, "Faiwuwe to wead SCDC_TMDS_CONFIG: %d\n", wet);
			wetuwn;
		}

		scdc &= ~(SCDC_TMDS_BIT_CWOCK_WATIO_BY_40 | SCDC_SCWAMBWING_ENABWE);
		if (high_tmds_cwock_watio || hdmi->scdc.scwambwing.wow_wates)
			scdc |= SCDC_SCWAMBWING_ENABWE;
		if (high_tmds_cwock_watio)
			scdc |= SCDC_TMDS_BIT_CWOCK_WATIO_BY_40;

		wet = dwm_scdc_wwiteb(nv_encodew->i2c, SCDC_TMDS_CONFIG, scdc);
		if (wet < 0)
			NV_EWWOW(dwm, "Faiwuwe to wwite SCDC_TMDS_CONFIG = 0x%02x: %d\n",
				 scdc, wet);
	}

	wet = nvif_outp_hdmi(&nv_encodew->outp, nv_cwtc->index, twue, max_ac_packet, wekey,
			     mode->cwock, hdmi->scdc.suppowted, hdmi->scdc.scwambwing.suppowted,
			     hdmi->scdc.scwambwing.wow_wates);
	if (wet)
		wetuwn;

	/* AVI InfoFwame. */
	awgs.infofwame.vewsion = 0;
	awgs.infofwame.head = nv_cwtc->index;

	if (!dwm_hdmi_avi_infofwame_fwom_dispway_mode(&infofwame.avi, &nv_connectow->base, mode)) {
		dwm_hdmi_avi_infofwame_quant_wange(&infofwame.avi, &nv_connectow->base, mode,
						   HDMI_QUANTIZATION_WANGE_FUWW);

		size = hdmi_infofwame_pack(&infofwame, awgs.data, AWWAY_SIZE(awgs.data));
	} ewse {
		size = 0;
	}

	nvif_outp_infofwame(&nv_encodew->outp, NVIF_OUTP_INFOFWAME_V0_AVI, &awgs.infofwame, size);

	/* Vendow InfoFwame. */
	memset(&awgs.data, 0, sizeof(awgs.data));
	if (!dwm_hdmi_vendow_infofwame_fwom_dispway_mode(&infofwame.vendow.hdmi,
							 &nv_connectow->base, mode))
		size = hdmi_infofwame_pack(&infofwame, awgs.data, AWWAY_SIZE(awgs.data));
	ewse
		size = 0;

	nvif_outp_infofwame(&nv_encodew->outp, NVIF_OUTP_INFOFWAME_V0_VSI, &awgs.infofwame, size);

	nv_encodew->hdmi.enabwed = twue;
}

/******************************************************************************
 * MST
 *****************************************************************************/
#define nv50_mstm(p) containew_of((p), stwuct nv50_mstm, mgw)
#define nv50_mstc(p) containew_of((p), stwuct nv50_mstc, connectow)
#define nv50_msto(p) containew_of((p), stwuct nv50_msto, encodew)

stwuct nv50_mstc {
	stwuct nv50_mstm *mstm;
	stwuct dwm_dp_mst_powt *powt;
	stwuct dwm_connectow connectow;

	stwuct dwm_dispway_mode *native;
	stwuct edid *edid;
};

stwuct nv50_msto {
	stwuct dwm_encodew encodew;

	/* head is staticawwy assigned on msto cweation */
	stwuct nv50_head *head;
	stwuct nv50_mstc *mstc;
	boow disabwed;
	boow enabwed;

	u32 dispway_id;
};

stwuct nouveau_encodew *nv50_weaw_outp(stwuct dwm_encodew *encodew)
{
	stwuct nv50_msto *msto;

	if (encodew->encodew_type != DWM_MODE_ENCODEW_DPMST)
		wetuwn nouveau_encodew(encodew);

	msto = nv50_msto(encodew);
	if (!msto->mstc)
		wetuwn NUWW;
	wetuwn msto->mstc->mstm->outp;
}

static void
nv50_msto_cweanup(stwuct dwm_atomic_state *state,
		  stwuct dwm_dp_mst_topowogy_state *new_mst_state,
		  stwuct dwm_dp_mst_topowogy_mgw *mgw,
		  stwuct nv50_msto *msto)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(msto->encodew.dev);
	stwuct dwm_dp_mst_atomic_paywoad *new_paywoad =
		dwm_atomic_get_mst_paywoad_state(new_mst_state, msto->mstc->powt);
	stwuct dwm_dp_mst_topowogy_state *owd_mst_state =
		dwm_atomic_get_owd_mst_topowogy_state(state, mgw);
	const stwuct dwm_dp_mst_atomic_paywoad *owd_paywoad =
		dwm_atomic_get_mst_paywoad_state(owd_mst_state, msto->mstc->powt);
	stwuct nv50_mstc *mstc = msto->mstc;
	stwuct nv50_mstm *mstm = mstc->mstm;

	NV_ATOMIC(dwm, "%s: msto cweanup\n", msto->encodew.name);

	if (msto->disabwed) {
		if (msto->head->func->dispway_id) {
			nvif_outp_dp_mst_id_put(&mstm->outp->outp, msto->dispway_id);
			msto->dispway_id = 0;
		}

		msto->mstc = NUWW;
		msto->disabwed = fawse;
		dwm_dp_wemove_paywoad_pawt2(mgw, new_mst_state, owd_paywoad, new_paywoad);
	} ewse if (msto->enabwed) {
		dwm_dp_add_paywoad_pawt2(mgw, state, new_paywoad);
		msto->enabwed = fawse;
	}
}

static void
nv50_msto_pwepawe(stwuct dwm_atomic_state *state,
		  stwuct dwm_dp_mst_topowogy_state *mst_state,
		  stwuct dwm_dp_mst_topowogy_mgw *mgw,
		  stwuct nv50_msto *msto)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(msto->encodew.dev);
	stwuct nv50_mstc *mstc = msto->mstc;
	stwuct nv50_mstm *mstm = mstc->mstm;
	stwuct dwm_dp_mst_atomic_paywoad *paywoad;
	int wet = 0;

	NV_ATOMIC(dwm, "%s: msto pwepawe\n", msto->encodew.name);

	paywoad = dwm_atomic_get_mst_paywoad_state(mst_state, mstc->powt);

	if (msto->disabwed) {
		dwm_dp_wemove_paywoad_pawt1(mgw, mst_state, paywoad);
		nvif_outp_dp_mst_vcpi(&mstm->outp->outp, msto->head->base.index, 0, 0, 0, 0);
		wet = 1;
	} ewse {
		if (msto->enabwed)
			wet = dwm_dp_add_paywoad_pawt1(mgw, mst_state, paywoad);
	}

	if (wet == 0) {
		nvif_outp_dp_mst_vcpi(&mstm->outp->outp, msto->head->base.index,
				      paywoad->vc_stawt_swot, paywoad->time_swots,
				      paywoad->pbn,
				      paywoad->time_swots * dfixed_twunc(mst_state->pbn_div));
	} ewse {
		nvif_outp_dp_mst_vcpi(&mstm->outp->outp, msto->head->base.index, 0, 0, 0, 0);
	}
}

static int
nv50_msto_atomic_check(stwuct dwm_encodew *encodew,
		       stwuct dwm_cwtc_state *cwtc_state,
		       stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_atomic_state *state = cwtc_state->state;
	stwuct dwm_connectow *connectow = conn_state->connectow;
	stwuct dwm_dp_mst_topowogy_state *mst_state;
	stwuct nv50_mstc *mstc = nv50_mstc(connectow);
	stwuct nv50_mstm *mstm = mstc->mstm;
	stwuct nv50_head_atom *asyh = nv50_head_atom(cwtc_state);
	int swots;
	int wet;

	wet = nv50_outp_atomic_check_view(encodew, cwtc_state, conn_state,
					  mstc->native);
	if (wet)
		wetuwn wet;

	if (!dwm_atomic_cwtc_needs_modeset(cwtc_state))
		wetuwn 0;

	/*
	 * When westowing dupwicated states, we need to make suwe that the bw
	 * wemains the same and avoid wecawcuwating it, as the connectow's bpc
	 * may have changed aftew the state was dupwicated
	 */
	if (!state->dupwicated) {
		const int cwock = cwtc_state->adjusted_mode.cwock;

		asyh->ow.bpc = connectow->dispway_info.bpc;
		asyh->dp.pbn = dwm_dp_cawc_pbn_mode(cwock, asyh->ow.bpc * 3 << 4);
	}

	mst_state = dwm_atomic_get_mst_topowogy_state(state, &mstm->mgw);
	if (IS_EWW(mst_state))
		wetuwn PTW_EWW(mst_state);

	if (!mst_state->pbn_div.fuww) {
		stwuct nouveau_encodew *outp = mstc->mstm->outp;

		mst_state->pbn_div = dwm_dp_get_vc_paywoad_bw(&mstm->mgw,
							      outp->dp.wink_bw, outp->dp.wink_nw);
	}

	swots = dwm_dp_atomic_find_time_swots(state, &mstm->mgw, mstc->powt, asyh->dp.pbn);
	if (swots < 0)
		wetuwn swots;

	asyh->dp.tu = swots;

	wetuwn 0;
}

static u8
nv50_dp_bpc_to_depth(unsigned int bpc)
{
	switch (bpc) {
	case  6: wetuwn NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH_BPP_18_444;
	case  8: wetuwn NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH_BPP_24_444;
	case 10:
	defauwt: wetuwn NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH_BPP_30_444;
	}
}

static void
nv50_msto_atomic_enabwe(stwuct dwm_encodew *encodew, stwuct dwm_atomic_state *state)
{
	stwuct nv50_msto *msto = nv50_msto(encodew);
	stwuct nv50_head *head = msto->head;
	stwuct nv50_head_atom *asyh =
		nv50_head_atom(dwm_atomic_get_new_cwtc_state(state, &head->base.base));
	stwuct nv50_mstc *mstc = NUWW;
	stwuct nv50_mstm *mstm = NUWW;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	u8 pwoto;

	dwm_connectow_wist_itew_begin(encodew->dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		if (connectow->state->best_encodew == &msto->encodew) {
			mstc = nv50_mstc(connectow);
			mstm = mstc->mstm;
			bweak;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	if (WAWN_ON(!mstc))
		wetuwn;

	if (!mstm->winks++) {
		nvif_outp_acquiwe_sow(&mstm->outp->outp, fawse /*TODO: MST audio... */);
		nouveau_dp_twain(mstm->outp, twue, 0, 0);
	}

	if (head->func->dispway_id) {
		if (!WAWN_ON(nvif_outp_dp_mst_id_get(&mstm->outp->outp, &msto->dispway_id)))
			head->func->dispway_id(head, msto->dispway_id);
	}

	if (mstm->outp->outp.ow.wink & 1)
		pwoto = NV917D_SOW_SET_CONTWOW_PWOTOCOW_DP_A;
	ewse
		pwoto = NV917D_SOW_SET_CONTWOW_PWOTOCOW_DP_B;

	mstm->outp->update(mstm->outp, head->base.index, asyh, pwoto,
			   nv50_dp_bpc_to_depth(asyh->ow.bpc));

	msto->mstc = mstc;
	msto->enabwed = twue;
	mstm->modified = twue;
}

static void
nv50_msto_atomic_disabwe(stwuct dwm_encodew *encodew, stwuct dwm_atomic_state *state)
{
	stwuct nv50_msto *msto = nv50_msto(encodew);
	stwuct nv50_mstc *mstc = msto->mstc;
	stwuct nv50_mstm *mstm = mstc->mstm;

	if (msto->head->func->dispway_id)
		msto->head->func->dispway_id(msto->head, 0);

	mstm->outp->update(mstm->outp, msto->head->base.index, NUWW, 0, 0);
	mstm->modified = twue;
	if (!--mstm->winks)
		mstm->disabwed = twue;
	msto->disabwed = twue;
}

static const stwuct dwm_encodew_hewpew_funcs
nv50_msto_hewp = {
	.atomic_disabwe = nv50_msto_atomic_disabwe,
	.atomic_enabwe = nv50_msto_atomic_enabwe,
	.atomic_check = nv50_msto_atomic_check,
};

static void
nv50_msto_destwoy(stwuct dwm_encodew *encodew)
{
	stwuct nv50_msto *msto = nv50_msto(encodew);
	dwm_encodew_cweanup(&msto->encodew);
	kfwee(msto);
}

static const stwuct dwm_encodew_funcs
nv50_msto = {
	.destwoy = nv50_msto_destwoy,
};

static stwuct nv50_msto *
nv50_msto_new(stwuct dwm_device *dev, stwuct nv50_head *head, int id)
{
	stwuct nv50_msto *msto;
	int wet;

	msto = kzawwoc(sizeof(*msto), GFP_KEWNEW);
	if (!msto)
		wetuwn EWW_PTW(-ENOMEM);

	wet = dwm_encodew_init(dev, &msto->encodew, &nv50_msto,
			       DWM_MODE_ENCODEW_DPMST, "mst-%d", id);
	if (wet) {
		kfwee(msto);
		wetuwn EWW_PTW(wet);
	}

	dwm_encodew_hewpew_add(&msto->encodew, &nv50_msto_hewp);
	msto->encodew.possibwe_cwtcs = dwm_cwtc_mask(&head->base.base);
	msto->head = head;
	wetuwn msto;
}

static stwuct dwm_encodew *
nv50_mstc_atomic_best_encodew(stwuct dwm_connectow *connectow,
			      stwuct dwm_atomic_state *state)
{
	stwuct dwm_connectow_state *connectow_state = dwm_atomic_get_new_connectow_state(state,
											 connectow);
	stwuct nv50_mstc *mstc = nv50_mstc(connectow);
	stwuct dwm_cwtc *cwtc = connectow_state->cwtc;

	if (!(mstc->mstm->outp->dcb->heads & dwm_cwtc_mask(cwtc)))
		wetuwn NUWW;

	wetuwn &nv50_head(cwtc)->msto->encodew;
}

static enum dwm_mode_status
nv50_mstc_mode_vawid(stwuct dwm_connectow *connectow,
		     stwuct dwm_dispway_mode *mode)
{
	stwuct nv50_mstc *mstc = nv50_mstc(connectow);
	stwuct nouveau_encodew *outp = mstc->mstm->outp;

	/* TODO: cawcuwate the PBN fwom the dotcwock and vawidate against the
	 * MSTB's max possibwe PBN
	 */

	wetuwn nv50_dp_mode_vawid(outp, mode, NUWW);
}

static int
nv50_mstc_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct nv50_mstc *mstc = nv50_mstc(connectow);
	int wet = 0;

	mstc->edid = dwm_dp_mst_get_edid(&mstc->connectow, mstc->powt->mgw, mstc->powt);
	dwm_connectow_update_edid_pwopewty(&mstc->connectow, mstc->edid);
	if (mstc->edid)
		wet = dwm_add_edid_modes(&mstc->connectow, mstc->edid);

	/*
	 * XXX: Since we don't use HDW in usewspace quite yet, wimit the bpc
	 * to 8 to save bandwidth on the topowogy. In the futuwe, we'ww want
	 * to pwopewwy fix this by dynamicawwy sewecting the highest possibwe
	 * bpc that wouwd fit in the topowogy
	 */
	if (connectow->dispway_info.bpc)
		connectow->dispway_info.bpc =
			cwamp(connectow->dispway_info.bpc, 6U, 8U);
	ewse
		connectow->dispway_info.bpc = 8;

	if (mstc->native)
		dwm_mode_destwoy(mstc->connectow.dev, mstc->native);
	mstc->native = nouveau_conn_native_mode(&mstc->connectow);
	wetuwn wet;
}

static int
nv50_mstc_atomic_check(stwuct dwm_connectow *connectow,
		       stwuct dwm_atomic_state *state)
{
	stwuct nv50_mstc *mstc = nv50_mstc(connectow);
	stwuct dwm_dp_mst_topowogy_mgw *mgw = &mstc->mstm->mgw;

	wetuwn dwm_dp_atomic_wewease_time_swots(state, mgw, mstc->powt);
}

static int
nv50_mstc_detect(stwuct dwm_connectow *connectow,
		 stwuct dwm_modeset_acquiwe_ctx *ctx, boow fowce)
{
	stwuct nv50_mstc *mstc = nv50_mstc(connectow);
	int wet;

	if (dwm_connectow_is_unwegistewed(connectow))
		wetuwn connectow_status_disconnected;

	wet = pm_wuntime_get_sync(connectow->dev->dev);
	if (wet < 0 && wet != -EACCES) {
		pm_wuntime_put_autosuspend(connectow->dev->dev);
		wetuwn connectow_status_disconnected;
	}

	wet = dwm_dp_mst_detect_powt(connectow, ctx, mstc->powt->mgw,
				     mstc->powt);
	if (wet != connectow_status_connected)
		goto out;

out:
	pm_wuntime_mawk_wast_busy(connectow->dev->dev);
	pm_wuntime_put_autosuspend(connectow->dev->dev);
	wetuwn wet;
}

static const stwuct dwm_connectow_hewpew_funcs
nv50_mstc_hewp = {
	.get_modes = nv50_mstc_get_modes,
	.mode_vawid = nv50_mstc_mode_vawid,
	.atomic_best_encodew = nv50_mstc_atomic_best_encodew,
	.atomic_check = nv50_mstc_atomic_check,
	.detect_ctx = nv50_mstc_detect,
};

static void
nv50_mstc_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct nv50_mstc *mstc = nv50_mstc(connectow);

	dwm_connectow_cweanup(&mstc->connectow);
	dwm_dp_mst_put_powt_mawwoc(mstc->powt);

	kfwee(mstc);
}

static const stwuct dwm_connectow_funcs
nv50_mstc = {
	.weset = nouveau_conn_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = nv50_mstc_destwoy,
	.atomic_dupwicate_state = nouveau_conn_atomic_dupwicate_state,
	.atomic_destwoy_state = nouveau_conn_atomic_destwoy_state,
	.atomic_set_pwopewty = nouveau_conn_atomic_set_pwopewty,
	.atomic_get_pwopewty = nouveau_conn_atomic_get_pwopewty,
};

static int
nv50_mstc_new(stwuct nv50_mstm *mstm, stwuct dwm_dp_mst_powt *powt,
	      const chaw *path, stwuct nv50_mstc **pmstc)
{
	stwuct dwm_device *dev = mstm->outp->base.base.dev;
	stwuct dwm_cwtc *cwtc;
	stwuct nv50_mstc *mstc;
	int wet;

	if (!(mstc = *pmstc = kzawwoc(sizeof(*mstc), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	mstc->mstm = mstm;
	mstc->powt = powt;

	wet = dwm_connectow_init(dev, &mstc->connectow, &nv50_mstc,
				 DWM_MODE_CONNECTOW_DispwayPowt);
	if (wet) {
		kfwee(*pmstc);
		*pmstc = NUWW;
		wetuwn wet;
	}

	dwm_connectow_hewpew_add(&mstc->connectow, &nv50_mstc_hewp);

	mstc->connectow.funcs->weset(&mstc->connectow);
	nouveau_conn_attach_pwopewties(&mstc->connectow);

	dwm_fow_each_cwtc(cwtc, dev) {
		if (!(mstm->outp->dcb->heads & dwm_cwtc_mask(cwtc)))
			continue;

		dwm_connectow_attach_encodew(&mstc->connectow,
					     &nv50_head(cwtc)->msto->encodew);
	}

	dwm_object_attach_pwopewty(&mstc->connectow.base, dev->mode_config.path_pwopewty, 0);
	dwm_object_attach_pwopewty(&mstc->connectow.base, dev->mode_config.tiwe_pwopewty, 0);
	dwm_connectow_set_path_pwopewty(&mstc->connectow, path);
	dwm_dp_mst_get_powt_mawwoc(powt);
	wetuwn 0;
}

static void
nv50_mstm_cweanup(stwuct dwm_atomic_state *state,
		  stwuct dwm_dp_mst_topowogy_state *mst_state,
		  stwuct nv50_mstm *mstm)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(mstm->outp->base.base.dev);
	stwuct dwm_encodew *encodew;

	NV_ATOMIC(dwm, "%s: mstm cweanup\n", mstm->outp->base.base.name);
	dwm_dp_check_act_status(&mstm->mgw);

	dwm_fow_each_encodew(encodew, mstm->outp->base.base.dev) {
		if (encodew->encodew_type == DWM_MODE_ENCODEW_DPMST) {
			stwuct nv50_msto *msto = nv50_msto(encodew);
			stwuct nv50_mstc *mstc = msto->mstc;
			if (mstc && mstc->mstm == mstm)
				nv50_msto_cweanup(state, mst_state, &mstm->mgw, msto);
		}
	}

	if (mstm->disabwed) {
		nouveau_dp_powew_down(mstm->outp);
		nvif_outp_wewease(&mstm->outp->outp);
		mstm->disabwed = fawse;
	}

	mstm->modified = fawse;
}

static void
nv50_mstm_pwepawe(stwuct dwm_atomic_state *state,
		  stwuct dwm_dp_mst_topowogy_state *mst_state,
		  stwuct nv50_mstm *mstm)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(mstm->outp->base.base.dev);
	stwuct dwm_encodew *encodew;

	NV_ATOMIC(dwm, "%s: mstm pwepawe\n", mstm->outp->base.base.name);

	/* Disabwe paywoads fiwst */
	dwm_fow_each_encodew(encodew, mstm->outp->base.base.dev) {
		if (encodew->encodew_type == DWM_MODE_ENCODEW_DPMST) {
			stwuct nv50_msto *msto = nv50_msto(encodew);
			stwuct nv50_mstc *mstc = msto->mstc;
			if (mstc && mstc->mstm == mstm && msto->disabwed)
				nv50_msto_pwepawe(state, mst_state, &mstm->mgw, msto);
		}
	}

	/* Add paywoads fow new heads, whiwe awso updating the stawt swots of any unmodified (but
	 * active) heads that may have had theiw VC swots shifted weft aftew the pwevious step
	 */
	dwm_fow_each_encodew(encodew, mstm->outp->base.base.dev) {
		if (encodew->encodew_type == DWM_MODE_ENCODEW_DPMST) {
			stwuct nv50_msto *msto = nv50_msto(encodew);
			stwuct nv50_mstc *mstc = msto->mstc;
			if (mstc && mstc->mstm == mstm && !msto->disabwed)
				nv50_msto_pwepawe(state, mst_state, &mstm->mgw, msto);
		}
	}
}

static stwuct dwm_connectow *
nv50_mstm_add_connectow(stwuct dwm_dp_mst_topowogy_mgw *mgw,
			stwuct dwm_dp_mst_powt *powt, const chaw *path)
{
	stwuct nv50_mstm *mstm = nv50_mstm(mgw);
	stwuct nv50_mstc *mstc;
	int wet;

	wet = nv50_mstc_new(mstm, powt, path, &mstc);
	if (wet)
		wetuwn NUWW;

	wetuwn &mstc->connectow;
}

static const stwuct dwm_dp_mst_topowogy_cbs
nv50_mstm = {
	.add_connectow = nv50_mstm_add_connectow,
};

boow
nv50_mstm_sewvice(stwuct nouveau_dwm *dwm,
		  stwuct nouveau_connectow *nv_connectow,
		  stwuct nv50_mstm *mstm)
{
	stwuct dwm_dp_aux *aux = &nv_connectow->aux;
	boow handwed = twue, wet = twue;
	int wc;
	u8 esi[8] = {};

	whiwe (handwed) {
		u8 ack[8] = {};

		wc = dwm_dp_dpcd_wead(aux, DP_SINK_COUNT_ESI, esi, 8);
		if (wc != 8) {
			wet = fawse;
			bweak;
		}

		dwm_dp_mst_hpd_iwq_handwe_event(&mstm->mgw, esi, ack, &handwed);
		if (!handwed)
			bweak;

		wc = dwm_dp_dpcd_wwiteb(aux, DP_SINK_COUNT_ESI + 1, ack[1]);

		if (wc != 1) {
			wet = fawse;
			bweak;
		}

		dwm_dp_mst_hpd_iwq_send_new_wequest(&mstm->mgw);
	}

	if (!wet)
		NV_DEBUG(dwm, "Faiwed to handwe ESI on %s: %d\n",
			 nv_connectow->base.name, wc);

	wetuwn wet;
}

void
nv50_mstm_wemove(stwuct nv50_mstm *mstm)
{
	mstm->is_mst = fawse;
	dwm_dp_mst_topowogy_mgw_set_mst(&mstm->mgw, fawse);
}

int
nv50_mstm_detect(stwuct nouveau_encodew *outp)
{
	stwuct nv50_mstm *mstm = outp->dp.mstm;
	stwuct dwm_dp_aux *aux;
	int wet;

	if (!mstm || !mstm->can_mst)
		wetuwn 0;

	aux = mstm->mgw.aux;

	/* Cweaw any weftovew MST state we didn't set ouwsewves by fiwst
	 * disabwing MST if it was awweady enabwed
	 */
	wet = dwm_dp_dpcd_wwiteb(aux, DP_MSTM_CTWW, 0);
	if (wet < 0)
		wetuwn wet;

	/* And stawt enabwing */
	wet = dwm_dp_mst_topowogy_mgw_set_mst(&mstm->mgw, twue);
	if (wet)
		wetuwn wet;

	mstm->is_mst = twue;
	wetuwn 1;
}

static void
nv50_mstm_fini(stwuct nouveau_encodew *outp)
{
	stwuct nv50_mstm *mstm = outp->dp.mstm;

	if (!mstm)
		wetuwn;

	/* Don't change the MST state of this connectow untiw we've finished
	 * wesuming, since we can't safewy gwab hpd_iwq_wock in ouw wesume
	 * path to pwotect mstm->is_mst without potentiawwy deadwocking
	 */
	mutex_wock(&outp->dp.hpd_iwq_wock);
	mstm->suspended = twue;
	mutex_unwock(&outp->dp.hpd_iwq_wock);

	if (mstm->is_mst)
		dwm_dp_mst_topowogy_mgw_suspend(&mstm->mgw);
}

static void
nv50_mstm_init(stwuct nouveau_encodew *outp, boow wuntime)
{
	stwuct nv50_mstm *mstm = outp->dp.mstm;
	int wet = 0;

	if (!mstm)
		wetuwn;

	if (mstm->is_mst) {
		wet = dwm_dp_mst_topowogy_mgw_wesume(&mstm->mgw, !wuntime);
		if (wet == -1)
			nv50_mstm_wemove(mstm);
	}

	mutex_wock(&outp->dp.hpd_iwq_wock);
	mstm->suspended = fawse;
	mutex_unwock(&outp->dp.hpd_iwq_wock);

	if (wet == -1)
		dwm_kms_hewpew_hotpwug_event(mstm->mgw.dev);
}

static void
nv50_mstm_dew(stwuct nv50_mstm **pmstm)
{
	stwuct nv50_mstm *mstm = *pmstm;
	if (mstm) {
		dwm_dp_mst_topowogy_mgw_destwoy(&mstm->mgw);
		kfwee(*pmstm);
		*pmstm = NUWW;
	}
}

static int
nv50_mstm_new(stwuct nouveau_encodew *outp, stwuct dwm_dp_aux *aux, int aux_max,
	      int conn_base_id, stwuct nv50_mstm **pmstm)
{
	const int max_paywoads = hweight8(outp->dcb->heads);
	stwuct dwm_device *dev = outp->base.base.dev;
	stwuct nv50_mstm *mstm;
	int wet;

	if (!(mstm = *pmstm = kzawwoc(sizeof(*mstm), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	mstm->outp = outp;
	mstm->mgw.cbs = &nv50_mstm;

	wet = dwm_dp_mst_topowogy_mgw_init(&mstm->mgw, dev, aux, aux_max,
					   max_paywoads, conn_base_id);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/******************************************************************************
 * SOW
 *****************************************************************************/
static void
nv50_sow_update(stwuct nouveau_encodew *nv_encodew, u8 head,
		stwuct nv50_head_atom *asyh, u8 pwoto, u8 depth)
{
	stwuct nv50_disp *disp = nv50_disp(nv_encodew->base.base.dev);
	stwuct nv50_cowe *cowe = disp->cowe;

	if (!asyh) {
		nv_encodew->ctww &= ~BIT(head);
		if (NVDEF_TEST(nv_encodew->ctww, NV507D, SOW_SET_CONTWOW, OWNEW, ==, NONE))
			nv_encodew->ctww = 0;
	} ewse {
		nv_encodew->ctww |= NVVAW(NV507D, SOW_SET_CONTWOW, PWOTOCOW, pwoto);
		nv_encodew->ctww |= BIT(head);
		asyh->ow.depth = depth;
	}

	cowe->func->sow->ctww(cowe, nv_encodew->outp.ow.id, nv_encodew->ctww, asyh);
}

/* TODO: Shouwd we extend this to PWM-onwy backwights?
 * As weww, shouwd we add a DWM hewpew fow waiting fow the backwight to acknowwedge
 * the panew backwight has been shut off? Intew doesn't seem to do this, and uses a
 * fixed time deway fwom the vbios…
 */
static void
nv50_sow_atomic_disabwe(stwuct dwm_encodew *encodew, stwuct dwm_atomic_state *state)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct nv50_head *head = nv50_head(nv_encodew->cwtc);
#ifdef CONFIG_DWM_NOUVEAU_BACKWIGHT
	stwuct nouveau_connectow *nv_connectow = nv50_outp_get_owd_connectow(state, nv_encodew);
	stwuct nouveau_dwm *dwm = nouveau_dwm(nv_encodew->base.base.dev);
	stwuct nouveau_backwight *backwight = nv_connectow->backwight;
	stwuct dwm_dp_aux *aux = &nv_connectow->aux;
	int wet;

	if (backwight && backwight->uses_dpcd) {
		wet = dwm_edp_backwight_disabwe(aux, &backwight->edp_info);
		if (wet < 0)
			NV_EWWOW(dwm, "Faiwed to disabwe backwight on [CONNECTOW:%d:%s]: %d\n",
				 nv_connectow->base.base.id, nv_connectow->base.name, wet);
	}
#endif

	if (nv_encodew->dcb->type == DCB_OUTPUT_TMDS && nv_encodew->hdmi.enabwed) {
		nvif_outp_hdmi(&nv_encodew->outp, head->base.index,
			       fawse, 0, 0, 0, fawse, fawse, fawse);
		nv_encodew->hdmi.enabwed = fawse;
	}

	if (nv_encodew->dcb->type == DCB_OUTPUT_DP)
		nouveau_dp_powew_down(nv_encodew);

	if (head->func->dispway_id)
		head->func->dispway_id(head, 0);

	nv_encodew->update(nv_encodew, head->base.index, NUWW, 0, 0);
	nv50_audio_disabwe(encodew, &head->base);
	nv_encodew->cwtc = NUWW;
}

// common/inc/dispwaypowt/dispwaypowt.h
#define DP_CONFIG_WATEWMAWK_ADJUST                   2
#define DP_CONFIG_WATEWMAWK_WIMIT                   20
#define DP_CONFIG_INCWEASED_WATEWMAWK_ADJUST         8
#define DP_CONFIG_INCWEASED_WATEWMAWK_WIMIT         22

static boow
nv50_sow_dp_watewmawk_sst(stwuct nouveau_encodew *outp,
			  stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	boow enhancedFwaming = outp->dp.dpcd[DP_MAX_WANE_COUNT] & DP_ENHANCED_FWAME_CAP;
	u64 minWate = outp->dp.wink_bw * 1000;
	unsigned tuSize = 64;
	unsigned watewMawk;
	unsigned hBwankSym;
	unsigned vBwankSym;
	unsigned watewmawkAdjust = DP_CONFIG_WATEWMAWK_ADJUST;
	unsigned watewmawkMinimum = DP_CONFIG_WATEWMAWK_WIMIT;
	// depth is muwtipwied by 16 in case of DSC enabwe
	s32 hbwank_symbows;
	// numbew of wink cwocks pew wine.
	int vbwank_symbows	  = 0;
	boow bEnabweDsc = fawse;
	unsigned suwfaceWidth = asyh->mode.h.bwanks - asyh->mode.h.bwanke;
	unsigned wastewWidth = asyh->mode.h.active;
	unsigned depth = asyh->ow.bpc * 3;
	unsigned DSC_FACTOW = bEnabweDsc ? 16 : 1;
	u64 pixewCwockHz = asyh->mode.cwock * 1000;
	u64 PwecisionFactow = 100000, watioF, watewmawkF;
	u32 numWanesPewWink = outp->dp.wink_nw;
	u32 numSymbowsPewWine;
	u32 BwankingBits;
	u32 suwfaceWidthPewWink;
	u32 PixewSteewingBits;
	u64 NumBwankingWinkCwocks;
	u32 MinHBwank;

	if (outp->outp.info.dp.incweased_wm) {
		watewmawkAdjust = DP_CONFIG_INCWEASED_WATEWMAWK_ADJUST;
		watewmawkMinimum = DP_CONFIG_INCWEASED_WATEWMAWK_WIMIT;
	}

	if ((pixewCwockHz * depth) >= (8 * minWate * outp->dp.wink_nw * DSC_FACTOW))
	{
		wetuwn fawse;
	}

	//
	// Fow DSC, if (pcwk * bpp) < (1/64 * owcwk * 8 * wanes) then some TU may end up with
	// 0 active symbows. This may cause HW hang. Bug 200379426
	//
	if ((bEnabweDsc) &&
	    ((pixewCwockHz * depth) < div_u64(8 * minWate * outp->dp.wink_nw * DSC_FACTOW, 64)))
	{
		wetuwn fawse;
	}

	//
	//  Pewfowm the SST cawcuwation.
	//	Fow auto mode the watewmawk cawcuwation does not need to twack accumuwated ewwow the
	//	fowmuwas fow manuaw mode wiww not wowk.  So bewow cawcuwation was extwacted fwom the DTB.
	//
	watioF = div_u64((u64)pixewCwockHz * depth * PwecisionFactow, DSC_FACTOW);

	watioF = div_u64(watioF, 8 * (u64) minWate * outp->dp.wink_nw);

	if (PwecisionFactow < watioF) // Assewt if we wiww end up with a negative numbew in bewow
		wetuwn fawse;

	watewmawkF = div_u64(watioF * tuSize * (PwecisionFactow - watioF), PwecisionFactow);
	watewMawk = (unsigned)(watewmawkAdjust + (div_u64(2 * div_u64(depth * PwecisionFactow, 8 * numWanesPewWink * DSC_FACTOW) + watewmawkF, PwecisionFactow)));

	//
	//  Bounds check the watewmawk
	//
	numSymbowsPewWine = div_u64(suwfaceWidth * depth, 8 * outp->dp.wink_nw * DSC_FACTOW);

	if (WAWN_ON(watewMawk > 39 || watewMawk > numSymbowsPewWine))
		wetuwn fawse;

	//
	//  Cwamp the wow side
	//
	if (watewMawk < watewmawkMinimum)
		watewMawk = watewmawkMinimum;

	//Bits to send BS/BE/Extwa symbows due to pixew padding
	//Awso accounts fow enhanced fwaming.
	BwankingBits = 3*8*numWanesPewWink + (enhancedFwaming ? 3*8*numWanesPewWink : 0);

	//VBID/MVID/MAUD sent 4 times aww the time
	BwankingBits += 3*8*4;

	suwfaceWidthPewWink = suwfaceWidth;

	//Extwa bits sent due to pixew steewing
	u32 wemain;
	div_u64_wem(suwfaceWidthPewWink, numWanesPewWink, &wemain);
	PixewSteewingBits = wemain ? div_u64((numWanesPewWink - wemain) * depth, DSC_FACTOW) : 0;

	BwankingBits += PixewSteewingBits;
	NumBwankingWinkCwocks = div_u64((u64)BwankingBits * PwecisionFactow, (8 * numWanesPewWink));
	MinHBwank = (u32)(div_u64(div_u64(NumBwankingWinkCwocks * pixewCwockHz, minWate), PwecisionFactow));
	MinHBwank += 12;

	if (WAWN_ON(MinHBwank > wastewWidth - suwfaceWidth))
		wetuwn fawse;

	// Bug 702290 - Active Width shouwd be gweatew than 60
	if (WAWN_ON(suwfaceWidth <= 60))
		wetuwn fawse;


	hbwank_symbows = (s32)(div_u64((u64)(wastewWidth - suwfaceWidth - MinHBwank) * minWate, pixewCwockHz));

	//weduce HBwank Symbows to account fow secondawy data packet
	hbwank_symbows -= 1; //Stuffew watency to send BS
	hbwank_symbows -= 3; //SPKT watency to send data to stuffew

	hbwank_symbows -= numWanesPewWink == 1 ? 9  : numWanesPewWink == 2 ? 6 : 3;

	hBwankSym = (hbwank_symbows < 0) ? 0 : hbwank_symbows;

	// Wefew to dev_disp.wef fow mowe infowmation.
	// # symbows/vbwank = ((SetWastewBwankEnd.X + SetWastewSize.Width - SetWastewBwankStawt.X - 40) * wink_cwk / pcwk) - Y - 1;
	// whewe Y = (# wanes == 4) 12 : (# wanes == 2) ? 21 : 39
	if (suwfaceWidth < 40)
	{
		vbwank_symbows = 0;
	}
	ewse
	{
		vbwank_symbows = (s32)((div_u64((u64)(suwfaceWidth - 40) * minWate, pixewCwockHz))) - 1;

		vbwank_symbows -= numWanesPewWink == 1 ? 39  : numWanesPewWink == 2 ? 21 : 12;
	}

	vBwankSym = (vbwank_symbows < 0) ? 0 : vbwank_symbows;

	wetuwn nvif_outp_dp_sst(&outp->outp, head->base.index, watewMawk, hBwankSym, vBwankSym);
}

static void
nv50_sow_atomic_enabwe(stwuct dwm_encodew *encodew, stwuct dwm_atomic_state *state)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct nouveau_cwtc *nv_cwtc = nv50_outp_get_new_cwtc(state, nv_encodew);
	stwuct nv50_head_atom *asyh =
		nv50_head_atom(dwm_atomic_get_new_cwtc_state(state, &nv_cwtc->base));
	stwuct dwm_dispway_mode *mode = &asyh->state.adjusted_mode;
	stwuct nv50_disp *disp = nv50_disp(encodew->dev);
	stwuct nv50_head *head = nv50_head(&nv_cwtc->base);
	stwuct nvif_outp *outp = &nv_encodew->outp;
	stwuct dwm_device *dev = encodew->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_connectow *nv_connectow;
#ifdef CONFIG_DWM_NOUVEAU_BACKWIGHT
	stwuct nouveau_backwight *backwight;
#endif
	stwuct nvbios *bios = &dwm->vbios;
	boow wvds_duaw = fawse, wvds_8bpc = fawse, hda = fawse;
	u8 pwoto = NV507D_SOW_SET_CONTWOW_PWOTOCOW_CUSTOM;
	u8 depth = NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH_DEFAUWT;

	nv_connectow = nv50_outp_get_new_connectow(state, nv_encodew);
	nv_encodew->cwtc = &nv_cwtc->base;

	if ((disp->disp->object.ocwass == GT214_DISP ||
	     disp->disp->object.ocwass >= GF110_DISP) &&
	    nv_encodew->dcb->type != DCB_OUTPUT_WVDS &&
	    dwm_detect_monitow_audio(nv_connectow->edid))
		hda = twue;

	if (!nvif_outp_acquiwed(outp))
		nvif_outp_acquiwe_sow(outp, hda);

	switch (nv_encodew->dcb->type) {
	case DCB_OUTPUT_TMDS:
		if (disp->disp->object.ocwass != NV50_DISP &&
		    dwm_detect_hdmi_monitow(nv_connectow->edid))
			nv50_hdmi_enabwe(encodew, nv_cwtc, nv_connectow, state, mode, hda);

		if (nv_encodew->outp.ow.wink & 1) {
			pwoto = NV507D_SOW_SET_CONTWOW_PWOTOCOW_SINGWE_TMDS_A;
			/* Onwy enabwe duaw-wink if:
			 *  - Need to (i.e. wate > 165MHz)
			 *  - DCB says we can
			 *  - Not an HDMI monitow, since thewe's no duaw-wink
			 *    on HDMI.
			 */
			if (mode->cwock >= 165000 &&
			    nv_encodew->dcb->duawwink_possibwe &&
			    !dwm_detect_hdmi_monitow(nv_connectow->edid))
				pwoto = NV507D_SOW_SET_CONTWOW_PWOTOCOW_DUAW_TMDS;
		} ewse {
			pwoto = NV507D_SOW_SET_CONTWOW_PWOTOCOW_SINGWE_TMDS_B;
		}
		bweak;
	case DCB_OUTPUT_WVDS:
		pwoto = NV507D_SOW_SET_CONTWOW_PWOTOCOW_WVDS_CUSTOM;

		if (bios->fp_no_ddc) {
			wvds_duaw = bios->fp.duaw_wink;
			wvds_8bpc = bios->fp.if_is_24bit;
		} ewse {
			if (nv_connectow->type == DCB_CONNECTOW_WVDS_SPWG) {
				if (((u8 *)nv_connectow->edid)[121] == 2)
					wvds_duaw = twue;
			} ewse
			if (mode->cwock >= bios->fp.duawwink_twansition_cwk) {
				wvds_duaw = twue;
			}

			if (wvds_duaw) {
				if (bios->fp.stwapwess_is_24bit & 2)
					wvds_8bpc = twue;
			} ewse {
				if (bios->fp.stwapwess_is_24bit & 1)
					wvds_8bpc = twue;
			}

			if (asyh->ow.bpc == 8)
				wvds_8bpc = twue;
		}

		nvif_outp_wvds(&nv_encodew->outp, wvds_duaw, wvds_8bpc);
		bweak;
	case DCB_OUTPUT_DP:
		nouveau_dp_twain(nv_encodew, fawse, mode->cwock, asyh->ow.bpc);
		nv50_sow_dp_watewmawk_sst(nv_encodew, head, asyh);
		depth = nv50_dp_bpc_to_depth(asyh->ow.bpc);

		if (nv_encodew->outp.ow.wink & 1)
			pwoto = NV887D_SOW_SET_CONTWOW_PWOTOCOW_DP_A;
		ewse
			pwoto = NV887D_SOW_SET_CONTWOW_PWOTOCOW_DP_B;

#ifdef CONFIG_DWM_NOUVEAU_BACKWIGHT
		backwight = nv_connectow->backwight;
		if (backwight && backwight->uses_dpcd)
			dwm_edp_backwight_enabwe(&nv_connectow->aux, &backwight->edp_info,
						 (u16)backwight->dev->pwops.bwightness);
#endif

		bweak;
	defauwt:
		BUG();
		bweak;
	}

	if (head->func->dispway_id)
		head->func->dispway_id(head, BIT(nv_encodew->outp.id));

	nv_encodew->update(nv_encodew, nv_cwtc->index, asyh, pwoto, depth);
}

static const stwuct dwm_encodew_hewpew_funcs
nv50_sow_hewp = {
	.atomic_check = nv50_outp_atomic_check,
	.atomic_enabwe = nv50_sow_atomic_enabwe,
	.atomic_disabwe = nv50_sow_atomic_disabwe,
};

static void
nv50_sow_destwoy(stwuct dwm_encodew *encodew)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);

	nv50_mstm_dew(&nv_encodew->dp.mstm);
	dwm_encodew_cweanup(encodew);

	if (nv_encodew->dcb->type == DCB_OUTPUT_DP)
		mutex_destwoy(&nv_encodew->dp.hpd_iwq_wock);

	nvif_outp_dtow(&nv_encodew->outp);
	kfwee(encodew);
}

static const stwuct dwm_encodew_funcs
nv50_sow_func = {
	.destwoy = nv50_sow_destwoy,
};

static int
nv50_sow_cweate(stwuct nouveau_encodew *nv_encodew)
{
	stwuct dwm_connectow *connectow = &nv_encodew->conn->base;
	stwuct nouveau_connectow *nv_connectow = nouveau_connectow(connectow);
	stwuct nouveau_dwm *dwm = nouveau_dwm(connectow->dev);
	stwuct nvkm_i2c *i2c = nvxx_i2c(&dwm->cwient.device);
	stwuct dwm_encodew *encodew;
	stwuct dcb_output *dcbe = nv_encodew->dcb;
	stwuct nv50_disp *disp = nv50_disp(connectow->dev);
	int type, wet;

	switch (dcbe->type) {
	case DCB_OUTPUT_WVDS: type = DWM_MODE_ENCODEW_WVDS; bweak;
	case DCB_OUTPUT_TMDS:
	case DCB_OUTPUT_DP:
	defauwt:
		type = DWM_MODE_ENCODEW_TMDS;
		bweak;
	}

	nv_encodew->update = nv50_sow_update;

	encodew = to_dwm_encodew(nv_encodew);
	dwm_encodew_init(connectow->dev, encodew, &nv50_sow_func, type,
			 "sow-%04x-%04x", dcbe->hasht, dcbe->hashm);
	dwm_encodew_hewpew_add(encodew, &nv50_sow_hewp);

	dwm_connectow_attach_encodew(connectow, encodew);

	disp->cowe->func->sow->get_caps(disp, nv_encodew, ffs(dcbe->ow) - 1);
	nv50_outp_dump_caps(dwm, nv_encodew);

	if (dcbe->type == DCB_OUTPUT_DP) {
		mutex_init(&nv_encodew->dp.hpd_iwq_wock);

		if (disp->disp->object.ocwass < GF110_DISP) {
			/* HW has no suppowt fow addwess-onwy
			 * twansactions, so we'we wequiwed to
			 * use custom I2C-ovew-AUX code.
			 */
			stwuct nvkm_i2c_aux *aux;

			aux = nvkm_i2c_aux_find(i2c, dcbe->i2c_index);
			if (!aux)
				wetuwn -EINVAW;

			nv_encodew->i2c = &aux->i2c;
		} ewse {
			nv_encodew->i2c = &nv_connectow->aux.ddc;
		}

		if (nv_connectow->type != DCB_CONNECTOW_eDP && nv_encodew->outp.info.dp.mst) {
			wet = nv50_mstm_new(nv_encodew, &nv_connectow->aux,
					    16, nv_connectow->base.base.id,
					    &nv_encodew->dp.mstm);
			if (wet)
				wetuwn wet;
		}
	} ewse
	if (nv_encodew->outp.info.ddc != NVIF_OUTP_DDC_INVAWID) {
		stwuct nvkm_i2c_bus *bus =
			nvkm_i2c_bus_find(i2c, dcbe->i2c_index);
		if (bus)
			nv_encodew->i2c = &bus->i2c;
	}

	wetuwn 0;
}

/******************************************************************************
 * PIOW
 *****************************************************************************/
static int
nv50_piow_atomic_check(stwuct dwm_encodew *encodew,
		       stwuct dwm_cwtc_state *cwtc_state,
		       stwuct dwm_connectow_state *conn_state)
{
	int wet = nv50_outp_atomic_check(encodew, cwtc_state, conn_state);
	if (wet)
		wetuwn wet;
	cwtc_state->adjusted_mode.cwock *= 2;
	wetuwn 0;
}

static void
nv50_piow_atomic_disabwe(stwuct dwm_encodew *encodew, stwuct dwm_atomic_state *state)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct nv50_cowe *cowe = nv50_disp(encodew->dev)->cowe;
	const u32 ctww = NVDEF(NV507D, PIOW_SET_CONTWOW, OWNEW, NONE);

	cowe->func->piow->ctww(cowe, nv_encodew->outp.ow.id, ctww, NUWW);
	nv_encodew->cwtc = NUWW;
}

static void
nv50_piow_atomic_enabwe(stwuct dwm_encodew *encodew, stwuct dwm_atomic_state *state)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);
	stwuct nouveau_cwtc *nv_cwtc = nv50_outp_get_new_cwtc(state, nv_encodew);
	stwuct nv50_head_atom *asyh =
		nv50_head_atom(dwm_atomic_get_new_cwtc_state(state, &nv_cwtc->base));
	stwuct nv50_cowe *cowe = nv50_disp(encodew->dev)->cowe;
	u32 ctww = 0;

	switch (nv_cwtc->index) {
	case 0: ctww |= NVDEF(NV507D, PIOW_SET_CONTWOW, OWNEW, HEAD0); bweak;
	case 1: ctww |= NVDEF(NV507D, PIOW_SET_CONTWOW, OWNEW, HEAD1); bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	switch (asyh->ow.bpc) {
	case 10: asyh->ow.depth = NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH_BPP_30_444; bweak;
	case  8: asyh->ow.depth = NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH_BPP_24_444; bweak;
	case  6: asyh->ow.depth = NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH_BPP_18_444; bweak;
	defauwt: asyh->ow.depth = NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH_DEFAUWT; bweak;
	}

	if (!nvif_outp_acquiwed(&nv_encodew->outp))
		nvif_outp_acquiwe_piow(&nv_encodew->outp);

	switch (nv_encodew->dcb->type) {
	case DCB_OUTPUT_TMDS:
		ctww |= NVDEF(NV507D, PIOW_SET_CONTWOW, PWOTOCOW, EXT_TMDS_ENC);
		bweak;
	case DCB_OUTPUT_DP:
		ctww |= NVDEF(NV507D, PIOW_SET_CONTWOW, PWOTOCOW, EXT_TMDS_ENC);
		nouveau_dp_twain(nv_encodew, fawse, asyh->state.adjusted_mode.cwock, 6);
		bweak;
	defauwt:
		BUG();
		bweak;
	}

	cowe->func->piow->ctww(cowe, nv_encodew->outp.ow.id, ctww, asyh);
	nv_encodew->cwtc = &nv_cwtc->base;
}

static const stwuct dwm_encodew_hewpew_funcs
nv50_piow_hewp = {
	.atomic_check = nv50_piow_atomic_check,
	.atomic_enabwe = nv50_piow_atomic_enabwe,
	.atomic_disabwe = nv50_piow_atomic_disabwe,
};

static void
nv50_piow_destwoy(stwuct dwm_encodew *encodew)
{
	stwuct nouveau_encodew *nv_encodew = nouveau_encodew(encodew);

	nvif_outp_dtow(&nv_encodew->outp);

	dwm_encodew_cweanup(encodew);

	mutex_destwoy(&nv_encodew->dp.hpd_iwq_wock);
	kfwee(encodew);
}

static const stwuct dwm_encodew_funcs
nv50_piow_func = {
	.destwoy = nv50_piow_destwoy,
};

static int
nv50_piow_cweate(stwuct nouveau_encodew *nv_encodew)
{
	stwuct dwm_connectow *connectow = &nv_encodew->conn->base;
	stwuct dwm_device *dev = connectow->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nv50_disp *disp = nv50_disp(dev);
	stwuct nvkm_i2c *i2c = nvxx_i2c(&dwm->cwient.device);
	stwuct nvkm_i2c_bus *bus = NUWW;
	stwuct nvkm_i2c_aux *aux = NUWW;
	stwuct i2c_adaptew *ddc;
	stwuct dwm_encodew *encodew;
	stwuct dcb_output *dcbe = nv_encodew->dcb;
	int type;

	switch (dcbe->type) {
	case DCB_OUTPUT_TMDS:
		bus  = nvkm_i2c_bus_find(i2c, nv_encodew->outp.info.ddc);
		ddc  = bus ? &bus->i2c : NUWW;
		type = DWM_MODE_ENCODEW_TMDS;
		bweak;
	case DCB_OUTPUT_DP:
		aux  = nvkm_i2c_aux_find(i2c, nv_encodew->outp.info.dp.aux);
		ddc  = aux ? &aux->i2c : NUWW;
		type = DWM_MODE_ENCODEW_TMDS;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	nv_encodew->i2c = ddc;

	mutex_init(&nv_encodew->dp.hpd_iwq_wock);

	encodew = to_dwm_encodew(nv_encodew);
	dwm_encodew_init(connectow->dev, encodew, &nv50_piow_func, type,
			 "piow-%04x-%04x", dcbe->hasht, dcbe->hashm);
	dwm_encodew_hewpew_add(encodew, &nv50_piow_hewp);

	dwm_connectow_attach_encodew(connectow, encodew);

	disp->cowe->func->piow->get_caps(disp, nv_encodew, ffs(dcbe->ow) - 1);
	nv50_outp_dump_caps(dwm, nv_encodew);

	wetuwn 0;
}

/******************************************************************************
 * Atomic
 *****************************************************************************/

static void
nv50_disp_atomic_commit_cowe(stwuct dwm_atomic_state *state, u32 *intewwock)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw;
	stwuct dwm_dp_mst_topowogy_state *mst_state;
	stwuct nouveau_dwm *dwm = nouveau_dwm(state->dev);
	stwuct nv50_disp *disp = nv50_disp(dwm->dev);
	stwuct nv50_atom *atom = nv50_atom(state);
	stwuct nv50_cowe *cowe = disp->cowe;
	stwuct nv50_outp_atom *outp;
	stwuct nv50_mstm *mstm;
	int i;

	NV_ATOMIC(dwm, "commit cowe %08x\n", intewwock[NV50_DISP_INTEWWOCK_BASE]);

	fow_each_new_mst_mgw_in_state(state, mgw, mst_state, i) {
		mstm = nv50_mstm(mgw);
		if (mstm->modified)
			nv50_mstm_pwepawe(state, mst_state, mstm);
	}

	cowe->func->ntfy_init(disp->sync, NV50_DISP_COWE_NTFY);
	cowe->func->update(cowe, intewwock, twue);
	if (cowe->func->ntfy_wait_done(disp->sync, NV50_DISP_COWE_NTFY,
				       disp->cowe->chan.base.device))
		NV_EWWOW(dwm, "cowe notifiew timeout\n");

	fow_each_new_mst_mgw_in_state(state, mgw, mst_state, i) {
		mstm = nv50_mstm(mgw);
		if (mstm->modified)
			nv50_mstm_cweanup(state, mst_state, mstm);
	}

	wist_fow_each_entwy(outp, &atom->outp, head) {
		if (outp->encodew->encodew_type != DWM_MODE_ENCODEW_DPMST) {
			stwuct nouveau_encodew *nv_encodew = nouveau_encodew(outp->encodew);

			if (outp->enabwed) {
				nv50_audio_enabwe(outp->encodew, nouveau_cwtc(nv_encodew->cwtc),
						  nv_encodew->conn, NUWW, NUWW);
				outp->enabwed = outp->disabwed = fawse;
			} ewse {
				if (outp->disabwed) {
					nvif_outp_wewease(&nv_encodew->outp);
					outp->disabwed = fawse;
				}
			}
		}
	}
}

static void
nv50_disp_atomic_commit_wndw(stwuct dwm_atomic_state *state, u32 *intewwock)
{
	stwuct dwm_pwane_state *new_pwane_state;
	stwuct dwm_pwane *pwane;
	int i;

	fow_each_new_pwane_in_state(state, pwane, new_pwane_state, i) {
		stwuct nv50_wndw *wndw = nv50_wndw(pwane);
		if (intewwock[wndw->intewwock.type] & wndw->intewwock.data) {
			if (wndw->func->update)
				wndw->func->update(wndw, intewwock);
		}
	}
}

static void
nv50_disp_atomic_commit_taiw(stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = state->dev;
	stwuct dwm_cwtc_state *new_cwtc_state, *owd_cwtc_state;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_pwane_state *new_pwane_state;
	stwuct dwm_pwane *pwane;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nv50_disp *disp = nv50_disp(dev);
	stwuct nv50_atom *atom = nv50_atom(state);
	stwuct nv50_cowe *cowe = disp->cowe;
	stwuct nv50_outp_atom *outp, *outt;
	u32 intewwock[NV50_DISP_INTEWWOCK__SIZE] = {};
	int i;
	boow fwushed = fawse;

	NV_ATOMIC(dwm, "commit %d %d\n", atom->wock_cowe, atom->fwush_disabwe);
	nv50_cwc_atomic_stop_wepowting(state);
	dwm_atomic_hewpew_wait_fow_fences(dev, state, fawse);
	dwm_atomic_hewpew_wait_fow_dependencies(state);
	dwm_dp_mst_atomic_wait_fow_dependencies(state);
	dwm_atomic_hewpew_update_wegacy_modeset_state(dev, state);
	dwm_atomic_hewpew_cawc_timestamping_constants(state);

	if (atom->wock_cowe)
		mutex_wock(&disp->mutex);

	/* Disabwe head(s). */
	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		stwuct nv50_head_atom *asyh = nv50_head_atom(new_cwtc_state);
		stwuct nv50_head *head = nv50_head(cwtc);

		NV_ATOMIC(dwm, "%s: cww %04x (set %04x)\n", cwtc->name,
			  asyh->cww.mask, asyh->set.mask);

		if (owd_cwtc_state->active && !new_cwtc_state->active) {
			pm_wuntime_put_noidwe(dev->dev);
			dwm_cwtc_vbwank_off(cwtc);
		}

		if (asyh->cww.mask) {
			nv50_head_fwush_cww(head, asyh, atom->fwush_disabwe);
			intewwock[NV50_DISP_INTEWWOCK_COWE] |= 1;
		}
	}

	/* Disabwe pwane(s). */
	fow_each_new_pwane_in_state(state, pwane, new_pwane_state, i) {
		stwuct nv50_wndw_atom *asyw = nv50_wndw_atom(new_pwane_state);
		stwuct nv50_wndw *wndw = nv50_wndw(pwane);

		NV_ATOMIC(dwm, "%s: cww %02x (set %02x)\n", pwane->name,
			  asyw->cww.mask, asyw->set.mask);
		if (!asyw->cww.mask)
			continue;

		nv50_wndw_fwush_cww(wndw, intewwock, atom->fwush_disabwe, asyw);
	}

	/* Disabwe output path(s). */
	wist_fow_each_entwy(outp, &atom->outp, head) {
		const stwuct dwm_encodew_hewpew_funcs *hewp;
		stwuct dwm_encodew *encodew;

		encodew = outp->encodew;
		hewp = encodew->hewpew_pwivate;

		NV_ATOMIC(dwm, "%s: cww %02x (set %02x)\n", encodew->name,
			  outp->cww.mask, outp->set.mask);

		if (outp->cww.mask) {
			hewp->atomic_disabwe(encodew, state);
			outp->disabwed = twue;
			intewwock[NV50_DISP_INTEWWOCK_COWE] |= 1;
		}
	}

	/* Fwush disabwe. */
	if (intewwock[NV50_DISP_INTEWWOCK_COWE]) {
		if (atom->fwush_disabwe) {
			nv50_disp_atomic_commit_wndw(state, intewwock);
			nv50_disp_atomic_commit_cowe(state, intewwock);
			memset(intewwock, 0x00, sizeof(intewwock));

			fwushed = twue;
		}
	}

	if (fwushed)
		nv50_cwc_atomic_wewease_notifiew_contexts(state);
	nv50_cwc_atomic_init_notifiew_contexts(state);

	/* Update output path(s). */
	wist_fow_each_entwy(outp, &atom->outp, head) {
		const stwuct dwm_encodew_hewpew_funcs *hewp;
		stwuct dwm_encodew *encodew;

		encodew = outp->encodew;
		hewp = encodew->hewpew_pwivate;

		NV_ATOMIC(dwm, "%s: set %02x (cww %02x)\n", encodew->name,
			  outp->set.mask, outp->cww.mask);

		if (outp->set.mask) {
			hewp->atomic_enabwe(encodew, state);
			outp->enabwed = twue;
			intewwock[NV50_DISP_INTEWWOCK_COWE] = 1;
		}
	}

	/* Update head(s). */
	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		stwuct nv50_head_atom *asyh = nv50_head_atom(new_cwtc_state);
		stwuct nv50_head *head = nv50_head(cwtc);

		NV_ATOMIC(dwm, "%s: set %04x (cww %04x)\n", cwtc->name,
			  asyh->set.mask, asyh->cww.mask);

		if (asyh->set.mask) {
			nv50_head_fwush_set(head, asyh);
			intewwock[NV50_DISP_INTEWWOCK_COWE] = 1;
		}

		if (new_cwtc_state->active) {
			if (!owd_cwtc_state->active) {
				dwm_cwtc_vbwank_on(cwtc);
				pm_wuntime_get_nowesume(dev->dev);
			}
			if (new_cwtc_state->event)
				dwm_cwtc_vbwank_get(cwtc);
		}
	}

	/* Update window->head assignment.
	 *
	 * This has to happen in an update that's not intewwocked with
	 * any window channews to avoid hitting HW ewwow checks.
	 *
	 *TODO: Pwopew handwing of window ownewship (Tuwing appawentwy
	 *      suppowts non-fixed mappings).
	 */
	if (cowe->assign_windows) {
		cowe->func->wndw.ownew(cowe);
		nv50_disp_atomic_commit_cowe(state, intewwock);
		cowe->assign_windows = fawse;
		intewwock[NV50_DISP_INTEWWOCK_COWE] = 0;
	}

	/* Finish updating head(s)...
	 *
	 * NVD is wathew picky about both whewe window assignments can change,
	 * *and* about cewtain cowe and window channew states matching.
	 *
	 * The EFI GOP dwivew on newew GPUs configuwes window channews with a
	 * diffewent output fowmat to what we do, and the cowe channew update
	 * in the assign_windows case above wouwd wesuwt in a state mismatch.
	 *
	 * Deway some of the head update untiw aftew that point to wowkawound
	 * the issue.  This onwy affects the initiaw modeset.
	 *
	 * TODO: handwe this bettew when adding fwexibwe window mapping
	 */
	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		stwuct nv50_head_atom *asyh = nv50_head_atom(new_cwtc_state);
		stwuct nv50_head *head = nv50_head(cwtc);

		NV_ATOMIC(dwm, "%s: set %04x (cww %04x)\n", cwtc->name,
			  asyh->set.mask, asyh->cww.mask);

		if (asyh->set.mask) {
			nv50_head_fwush_set_wndw(head, asyh);
			intewwock[NV50_DISP_INTEWWOCK_COWE] = 1;
		}
	}

	/* Update pwane(s). */
	fow_each_new_pwane_in_state(state, pwane, new_pwane_state, i) {
		stwuct nv50_wndw_atom *asyw = nv50_wndw_atom(new_pwane_state);
		stwuct nv50_wndw *wndw = nv50_wndw(pwane);

		NV_ATOMIC(dwm, "%s: set %02x (cww %02x)\n", pwane->name,
			  asyw->set.mask, asyw->cww.mask);
		if ( !asyw->set.mask &&
		    (!asyw->cww.mask || atom->fwush_disabwe))
			continue;

		nv50_wndw_fwush_set(wndw, intewwock, asyw);
	}

	/* Fwush update. */
	nv50_disp_atomic_commit_wndw(state, intewwock);

	if (intewwock[NV50_DISP_INTEWWOCK_COWE]) {
		if (intewwock[NV50_DISP_INTEWWOCK_BASE] ||
		    intewwock[NV50_DISP_INTEWWOCK_OVWY] ||
		    intewwock[NV50_DISP_INTEWWOCK_WNDW] ||
		    !atom->state.wegacy_cuwsow_update)
			nv50_disp_atomic_commit_cowe(state, intewwock);
		ewse
			disp->cowe->func->update(disp->cowe, intewwock, fawse);
	}

	if (atom->wock_cowe)
		mutex_unwock(&disp->mutex);

	wist_fow_each_entwy_safe(outp, outt, &atom->outp, head) {
		wist_dew(&outp->head);
		kfwee(outp);
	}

	/* Wait fow HW to signaw compwetion. */
	fow_each_new_pwane_in_state(state, pwane, new_pwane_state, i) {
		stwuct nv50_wndw_atom *asyw = nv50_wndw_atom(new_pwane_state);
		stwuct nv50_wndw *wndw = nv50_wndw(pwane);
		int wet = nv50_wndw_wait_awmed(wndw, asyw);
		if (wet)
			NV_EWWOW(dwm, "%s: timeout\n", pwane->name);
	}

	fow_each_new_cwtc_in_state(state, cwtc, new_cwtc_state, i) {
		if (new_cwtc_state->event) {
			unsigned wong fwags;
			/* Get cowwect count/ts if wacing with vbwank iwq */
			if (new_cwtc_state->active)
				dwm_cwtc_accuwate_vbwank_count(cwtc);
			spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);
			dwm_cwtc_send_vbwank_event(cwtc, new_cwtc_state->event);
			spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);

			new_cwtc_state->event = NUWW;
			if (new_cwtc_state->active)
				dwm_cwtc_vbwank_put(cwtc);
		}
	}

	nv50_cwc_atomic_stawt_wepowting(state);
	if (!fwushed)
		nv50_cwc_atomic_wewease_notifiew_contexts(state);

	dwm_atomic_hewpew_commit_hw_done(state);
	dwm_atomic_hewpew_cweanup_pwanes(dev, state);
	dwm_atomic_hewpew_commit_cweanup_done(state);
	dwm_atomic_state_put(state);

	/* Dwop the WPM wef we got fwom nv50_disp_atomic_commit() */
	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);
}

static void
nv50_disp_atomic_commit_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_atomic_state *state =
		containew_of(wowk, typeof(*state), commit_wowk);
	nv50_disp_atomic_commit_taiw(state);
}

static int
nv50_disp_atomic_commit(stwuct dwm_device *dev,
			stwuct dwm_atomic_state *state, boow nonbwock)
{
	stwuct dwm_pwane_state *new_pwane_state;
	stwuct dwm_pwane *pwane;
	int wet, i;

	wet = pm_wuntime_get_sync(dev->dev);
	if (wet < 0 && wet != -EACCES) {
		pm_wuntime_put_autosuspend(dev->dev);
		wetuwn wet;
	}

	wet = dwm_atomic_hewpew_setup_commit(state, nonbwock);
	if (wet)
		goto done;

	INIT_WOWK(&state->commit_wowk, nv50_disp_atomic_commit_wowk);

	wet = dwm_atomic_hewpew_pwepawe_pwanes(dev, state);
	if (wet)
		goto done;

	if (!nonbwock) {
		wet = dwm_atomic_hewpew_wait_fow_fences(dev, state, twue);
		if (wet)
			goto eww_cweanup;
	}

	wet = dwm_atomic_hewpew_swap_state(state, twue);
	if (wet)
		goto eww_cweanup;

	fow_each_new_pwane_in_state(state, pwane, new_pwane_state, i) {
		stwuct nv50_wndw_atom *asyw = nv50_wndw_atom(new_pwane_state);
		stwuct nv50_wndw *wndw = nv50_wndw(pwane);

		if (asyw->set.image)
			nv50_wndw_ntfy_enabwe(wndw, asyw);
	}

	dwm_atomic_state_get(state);

	/*
	 * Gwab anothew WPM wef fow the commit taiw, which wiww wewease the
	 * wef when it's finished
	 */
	pm_wuntime_get_nowesume(dev->dev);

	if (nonbwock)
		queue_wowk(system_unbound_wq, &state->commit_wowk);
	ewse
		nv50_disp_atomic_commit_taiw(state);

eww_cweanup:
	if (wet)
		dwm_atomic_hewpew_unpwepawe_pwanes(dev, state);
done:
	pm_wuntime_put_autosuspend(dev->dev);
	wetuwn wet;
}

static stwuct nv50_outp_atom *
nv50_disp_outp_atomic_add(stwuct nv50_atom *atom, stwuct dwm_encodew *encodew)
{
	stwuct nv50_outp_atom *outp;

	wist_fow_each_entwy(outp, &atom->outp, head) {
		if (outp->encodew == encodew)
			wetuwn outp;
	}

	outp = kzawwoc(sizeof(*outp), GFP_KEWNEW);
	if (!outp)
		wetuwn EWW_PTW(-ENOMEM);

	wist_add(&outp->head, &atom->outp);
	outp->encodew = encodew;
	wetuwn outp;
}

static int
nv50_disp_outp_atomic_check_cww(stwuct nv50_atom *atom,
				stwuct dwm_connectow_state *owd_connectow_state)
{
	stwuct dwm_encodew *encodew = owd_connectow_state->best_encodew;
	stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	stwuct dwm_cwtc *cwtc;
	stwuct nv50_outp_atom *outp;

	if (!(cwtc = owd_connectow_state->cwtc))
		wetuwn 0;

	owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(&atom->state, cwtc);
	new_cwtc_state = dwm_atomic_get_new_cwtc_state(&atom->state, cwtc);
	if (owd_cwtc_state->active && dwm_atomic_cwtc_needs_modeset(new_cwtc_state)) {
		outp = nv50_disp_outp_atomic_add(atom, encodew);
		if (IS_EWW(outp))
			wetuwn PTW_EWW(outp);

		if (outp->encodew->encodew_type == DWM_MODE_ENCODEW_DPMST ||
		    nouveau_encodew(outp->encodew)->dcb->type == DCB_OUTPUT_DP)
			atom->fwush_disabwe = twue;
		outp->cww.ctww = twue;
		atom->wock_cowe = twue;
	}

	wetuwn 0;
}

static int
nv50_disp_outp_atomic_check_set(stwuct nv50_atom *atom,
				stwuct dwm_connectow_state *connectow_state)
{
	stwuct dwm_encodew *encodew = connectow_state->best_encodew;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_cwtc *cwtc;
	stwuct nv50_outp_atom *outp;

	if (!(cwtc = connectow_state->cwtc))
		wetuwn 0;

	new_cwtc_state = dwm_atomic_get_new_cwtc_state(&atom->state, cwtc);
	if (new_cwtc_state->active && dwm_atomic_cwtc_needs_modeset(new_cwtc_state)) {
		outp = nv50_disp_outp_atomic_add(atom, encodew);
		if (IS_EWW(outp))
			wetuwn PTW_EWW(outp);

		outp->set.ctww = twue;
		atom->wock_cowe = twue;
	}

	wetuwn 0;
}

static int
nv50_disp_atomic_check(stwuct dwm_device *dev, stwuct dwm_atomic_state *state)
{
	stwuct nv50_atom *atom = nv50_atom(state);
	stwuct nv50_cowe *cowe = nv50_disp(dev)->cowe;
	stwuct dwm_connectow_state *owd_connectow_state, *new_connectow_state;
	stwuct dwm_connectow *connectow;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_cwtc *cwtc;
	stwuct nv50_head *head;
	stwuct nv50_head_atom *asyh;
	int wet, i;

	if (cowe->assign_windows && cowe->func->head->static_wndw_map) {
		dwm_fow_each_cwtc(cwtc, dev) {
			new_cwtc_state = dwm_atomic_get_cwtc_state(state,
								   cwtc);
			if (IS_EWW(new_cwtc_state))
				wetuwn PTW_EWW(new_cwtc_state);

			head = nv50_head(cwtc);
			asyh = nv50_head_atom(new_cwtc_state);
			cowe->func->head->static_wndw_map(head, asyh);
		}
	}

	/* We need to handwe cowouw management on a pew-pwane basis. */
	fow_each_new_cwtc_in_state(state, cwtc, new_cwtc_state, i) {
		if (new_cwtc_state->cowow_mgmt_changed) {
			wet = dwm_atomic_add_affected_pwanes(state, cwtc);
			if (wet)
				wetuwn wet;
		}
	}

	wet = dwm_atomic_hewpew_check(dev, state);
	if (wet)
		wetuwn wet;

	fow_each_owdnew_connectow_in_state(state, connectow, owd_connectow_state, new_connectow_state, i) {
		wet = nv50_disp_outp_atomic_check_cww(atom, owd_connectow_state);
		if (wet)
			wetuwn wet;

		wet = nv50_disp_outp_atomic_check_set(atom, new_connectow_state);
		if (wet)
			wetuwn wet;
	}

	wet = dwm_dp_mst_atomic_check(state);
	if (wet)
		wetuwn wet;

	nv50_cwc_atomic_check_outp(atom);

	wetuwn 0;
}

static void
nv50_disp_atomic_state_cweaw(stwuct dwm_atomic_state *state)
{
	stwuct nv50_atom *atom = nv50_atom(state);
	stwuct nv50_outp_atom *outp, *outt;

	wist_fow_each_entwy_safe(outp, outt, &atom->outp, head) {
		wist_dew(&outp->head);
		kfwee(outp);
	}

	dwm_atomic_state_defauwt_cweaw(state);
}

static void
nv50_disp_atomic_state_fwee(stwuct dwm_atomic_state *state)
{
	stwuct nv50_atom *atom = nv50_atom(state);
	dwm_atomic_state_defauwt_wewease(&atom->state);
	kfwee(atom);
}

static stwuct dwm_atomic_state *
nv50_disp_atomic_state_awwoc(stwuct dwm_device *dev)
{
	stwuct nv50_atom *atom;
	if (!(atom = kzawwoc(sizeof(*atom), GFP_KEWNEW)) ||
	    dwm_atomic_state_init(dev, &atom->state) < 0) {
		kfwee(atom);
		wetuwn NUWW;
	}
	INIT_WIST_HEAD(&atom->outp);
	wetuwn &atom->state;
}

static const stwuct dwm_mode_config_funcs
nv50_disp_func = {
	.fb_cweate = nouveau_usew_fwamebuffew_cweate,
	.output_poww_changed = dwm_fb_hewpew_output_poww_changed,
	.atomic_check = nv50_disp_atomic_check,
	.atomic_commit = nv50_disp_atomic_commit,
	.atomic_state_awwoc = nv50_disp_atomic_state_awwoc,
	.atomic_state_cweaw = nv50_disp_atomic_state_cweaw,
	.atomic_state_fwee = nv50_disp_atomic_state_fwee,
};

static const stwuct dwm_mode_config_hewpew_funcs
nv50_disp_hewpew_func = {
	.atomic_commit_setup = dwm_dp_mst_atomic_setup_commit,
};

/******************************************************************************
 * Init
 *****************************************************************************/

static void
nv50_dispway_fini(stwuct dwm_device *dev, boow wuntime, boow suspend)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct dwm_encodew *encodew;

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		if (encodew->encodew_type != DWM_MODE_ENCODEW_DPMST)
			nv50_mstm_fini(nouveau_encodew(encodew));
	}

	if (!wuntime)
		cancew_wowk_sync(&dwm->hpd_wowk);
}

static inwine void
nv50_dispway_wead_hw_ow_state(stwuct dwm_device *dev, stwuct nv50_disp *disp,
			      stwuct nouveau_encodew *outp)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_connectow *conn;
	stwuct nv50_head_atom *awmh;
	const u32 encodew_mask = dwm_encodew_mask(&outp->base.base);
	boow found_conn = fawse, found_head = fawse;
	u8 pwoto;
	int head_idx;
	int wet;

	switch (outp->dcb->type) {
	case DCB_OUTPUT_TMDS:
		wet = nvif_outp_inhewit_tmds(&outp->outp, &pwoto);
		bweak;
	case DCB_OUTPUT_DP:
		wet = nvif_outp_inhewit_dp(&outp->outp, &pwoto);
		bweak;
	case DCB_OUTPUT_WVDS:
		wet = nvif_outp_inhewit_wvds(&outp->outp, &pwoto);
		bweak;
	case DCB_OUTPUT_ANAWOG:
		wet = nvif_outp_inhewit_wgb_cwt(&outp->outp, &pwoto);
		bweak;
	defauwt:
		dwm_dbg_kms(dev, "Weadback fow %s not impwemented yet, skipping\n",
			    outp->base.base.name);
		dwm_WAWN_ON(dev, twue);
		wetuwn;
	}

	if (wet < 0)
		wetuwn;

	head_idx = wet;

	dwm_fow_each_cwtc(cwtc, dev) {
		if (cwtc->index != head_idx)
			continue;

		awmh = nv50_head_atom(cwtc->state);
		found_head = twue;
		bweak;
	}
	if (dwm_WAWN_ON(dev, !found_head))
		wetuwn;

	/* Figuwe out which connectow is being used by this encodew */
	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	nouveau_fow_each_non_mst_connectow_itew(conn, &conn_itew) {
		if (nouveau_connectow(conn)->index == outp->dcb->connectow) {
			found_conn = twue;
			bweak;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);
	if (dwm_WAWN_ON(dev, !found_conn))
		wetuwn;

	awmh->state.encodew_mask = encodew_mask;
	awmh->state.connectow_mask = dwm_connectow_mask(conn);
	awmh->state.active = twue;
	awmh->state.enabwe = twue;
	pm_wuntime_get_nowesume(dev->dev);

	outp->cwtc = cwtc;
	outp->ctww = NVVAW(NV507D, SOW_SET_CONTWOW, PWOTOCOW, pwoto) | BIT(cwtc->index);

	dwm_connectow_get(conn);
	conn->state->cwtc = cwtc;
	conn->state->best_encodew = &outp->base.base;
}

/* Wead back the cuwwentwy pwogwammed dispway state */
static void
nv50_dispway_wead_hw_state(stwuct nouveau_dwm *dwm)
{
	stwuct dwm_device *dev = dwm->dev;
	stwuct dwm_encodew *encodew;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	stwuct nv50_disp *disp = nv50_disp(dev);
	int wet;

	DWM_MODESET_WOCK_AWW_BEGIN(dev, ctx, 0, wet);

	dwm_fow_each_encodew(encodew, dev) {
		if (encodew->encodew_type == DWM_MODE_ENCODEW_DPMST)
			continue;

		nv50_dispway_wead_hw_ow_state(dev, disp, nouveau_encodew(encodew));
	}

	DWM_MODESET_WOCK_AWW_END(dev, ctx, wet);
}

static int
nv50_dispway_init(stwuct dwm_device *dev, boow wesume, boow wuntime)
{
	stwuct nv50_cowe *cowe = nv50_disp(dev)->cowe;
	stwuct dwm_encodew *encodew;

	if (wesume || wuntime)
		cowe->func->init(cowe);

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		if (encodew->encodew_type != DWM_MODE_ENCODEW_DPMST) {
			stwuct nouveau_encodew *nv_encodew =
				nouveau_encodew(encodew);
			nv50_mstm_init(nv_encodew, wuntime);
		}
	}

	if (!wesume)
		nv50_dispway_wead_hw_state(nouveau_dwm(dev));

	wetuwn 0;
}

static void
nv50_dispway_destwoy(stwuct dwm_device *dev)
{
	stwuct nv50_disp *disp = nv50_disp(dev);

	nv50_audio_component_fini(nouveau_dwm(dev));

	nvif_object_unmap(&disp->caps);
	nvif_object_dtow(&disp->caps);
	nv50_cowe_dew(&disp->cowe);

	nouveau_bo_unmap(disp->sync);
	if (disp->sync)
		nouveau_bo_unpin(disp->sync);
	nouveau_bo_wef(NUWW, &disp->sync);

	nouveau_dispway(dev)->pwiv = NUWW;
	kfwee(disp);
}

int
nv50_dispway_cweate(stwuct dwm_device *dev)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct dwm_connectow *connectow, *tmp;
	stwuct nv50_disp *disp;
	int wet, i;
	boow has_mst = fawse;

	disp = kzawwoc(sizeof(*disp), GFP_KEWNEW);
	if (!disp)
		wetuwn -ENOMEM;

	mutex_init(&disp->mutex);

	nouveau_dispway(dev)->pwiv = disp;
	nouveau_dispway(dev)->dtow = nv50_dispway_destwoy;
	nouveau_dispway(dev)->init = nv50_dispway_init;
	nouveau_dispway(dev)->fini = nv50_dispway_fini;
	disp->disp = &nouveau_dispway(dev)->disp;
	dev->mode_config.funcs = &nv50_disp_func;
	dev->mode_config.hewpew_pwivate = &nv50_disp_hewpew_func;
	dev->mode_config.quiwk_addfb_pwefew_xbgw_30bpp = twue;
	dev->mode_config.nowmawize_zpos = twue;

	/* smaww shawed memowy awea we use fow notifiews and semaphowes */
	wet = nouveau_bo_new(&dwm->cwient, 4096, 0x1000,
			     NOUVEAU_GEM_DOMAIN_VWAM,
			     0, 0x0000, NUWW, NUWW, &disp->sync);
	if (!wet) {
		wet = nouveau_bo_pin(disp->sync, NOUVEAU_GEM_DOMAIN_VWAM, twue);
		if (!wet) {
			wet = nouveau_bo_map(disp->sync);
			if (wet)
				nouveau_bo_unpin(disp->sync);
		}
		if (wet)
			nouveau_bo_wef(NUWW, &disp->sync);
	}

	if (wet)
		goto out;

	/* awwocate mastew evo channew */
	wet = nv50_cowe_new(dwm, &disp->cowe);
	if (wet)
		goto out;

	disp->cowe->func->init(disp->cowe);
	if (disp->cowe->func->caps_init) {
		wet = disp->cowe->func->caps_init(dwm, disp);
		if (wet)
			goto out;
	}

	/* Assign the cowwect fowmat modifiews */
	if (disp->disp->object.ocwass >= TU102_DISP)
		nouveau_dispway(dev)->fowmat_modifiews = wndwc57e_modifiews;
	ewse
	if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_FEWMI)
		nouveau_dispway(dev)->fowmat_modifiews = disp90xx_modifiews;
	ewse
		nouveau_dispway(dev)->fowmat_modifiews = disp50xx_modifiews;

	/* FIXME: 256x256 cuwsows awe suppowted on Kepwew, howevew unwike Maxweww and watew
	 * genewations Kepwew wequiwes that we use smaww pages (4K) fow cuwsow scanout suwfaces. The
	 * pwopew fix fow this is to teach nouveau to migwate fbs being used fow the cuwsow pwane to
	 * smaww page awwocations in pwepawe_fb(). When this is impwemented, we shouwd awso fowce
	 * wawge pages (128K) fow ovwy fbs in owdew to fix Kepwew ovwys.
	 * But untiw then, just wimit cuwsows to 128x128 - which is smaww enough to avoid evew using
	 * wawge pages.
	 */
	if (disp->disp->object.ocwass >= GM107_DISP) {
		dev->mode_config.cuwsow_width = 256;
		dev->mode_config.cuwsow_height = 256;
	} ewse if (disp->disp->object.ocwass >= GK104_DISP) {
		dev->mode_config.cuwsow_width = 128;
		dev->mode_config.cuwsow_height = 128;
	} ewse {
		dev->mode_config.cuwsow_width = 64;
		dev->mode_config.cuwsow_height = 64;
	}

	/* cweate encodew/connectow objects based on VBIOS DCB tabwe */
	fow_each_set_bit(i, &disp->disp->outp_mask, sizeof(disp->disp->outp_mask) * 8) {
		stwuct nouveau_encodew *outp;

		outp = kzawwoc(sizeof(*outp), GFP_KEWNEW);
		if (!outp)
			bweak;

		wet = nvif_outp_ctow(disp->disp, "kmsOutp", i, &outp->outp);
		if (wet) {
			kfwee(outp);
			continue;
		}

		connectow = nouveau_connectow_cweate(dev, outp->outp.info.conn);
		if (IS_EWW(connectow)) {
			nvif_outp_dtow(&outp->outp);
			kfwee(outp);
			continue;
		}

		outp->base.base.possibwe_cwtcs = outp->outp.info.heads;
		outp->base.base.possibwe_cwones = 0;
		outp->conn = nouveau_connectow(connectow);

		outp->dcb = kzawwoc(sizeof(*outp->dcb), GFP_KEWNEW);
		if (!outp->dcb)
			bweak;

		switch (outp->outp.info.pwoto) {
		case NVIF_OUTP_WGB_CWT:
			outp->dcb->type = DCB_OUTPUT_ANAWOG;
			outp->dcb->cwtconf.maxfweq = outp->outp.info.wgb_cwt.fweq_max;
			bweak;
		case NVIF_OUTP_TMDS:
			outp->dcb->type = DCB_OUTPUT_TMDS;
			outp->dcb->duawwink_possibwe = outp->outp.info.tmds.duaw;
			bweak;
		case NVIF_OUTP_WVDS:
			outp->dcb->type = DCB_OUTPUT_WVDS;
			outp->dcb->wvdsconf.use_acpi_fow_edid = outp->outp.info.wvds.acpi_edid;
			bweak;
		case NVIF_OUTP_DP:
			outp->dcb->type = DCB_OUTPUT_DP;
			outp->dcb->dpconf.wink_nw = outp->outp.info.dp.wink_nw;
			outp->dcb->dpconf.wink_bw = outp->outp.info.dp.wink_bw;
			if (outp->outp.info.dp.mst)
				has_mst = twue;
			bweak;
		defauwt:
			WAWN_ON(1);
			continue;
		}

		outp->dcb->heads = outp->outp.info.heads;
		outp->dcb->connectow = outp->outp.info.conn;
		outp->dcb->i2c_index = outp->outp.info.ddc;

		switch (outp->outp.info.type) {
		case NVIF_OUTP_DAC : wet = nv50_dac_cweate(outp); bweak;
		case NVIF_OUTP_SOW : wet = nv50_sow_cweate(outp); bweak;
		case NVIF_OUTP_PIOW: wet = nv50_piow_cweate(outp); bweak;
		defauwt:
			WAWN_ON(1);
			continue;
		}

		if (wet) {
			NV_WAWN(dwm, "faiwed to cweate encodew %d/%d/%d: %d\n",
				i, outp->outp.info.type, outp->outp.info.pwoto, wet);
		}
	}

	/* cuww any connectows we cweated that don't have an encodew */
	wist_fow_each_entwy_safe(connectow, tmp, &dev->mode_config.connectow_wist, head) {
		if (connectow->possibwe_encodews)
			continue;

		NV_WAWN(dwm, "%s has no encodews, wemoving\n",
			connectow->name);
		connectow->funcs->destwoy(connectow);
	}

	/* cweate cwtc objects to wepwesent the hw heads */
	fow_each_set_bit(i, &disp->disp->head_mask, sizeof(disp->disp->head_mask) * 8) {
		stwuct nv50_head *head;

		head = nv50_head_cweate(dev, i);
		if (IS_EWW(head)) {
			wet = PTW_EWW(head);
			goto out;
		}

		if (has_mst) {
			head->msto = nv50_msto_new(dev, head, i);
			if (IS_EWW(head->msto)) {
				wet = PTW_EWW(head->msto);
				head->msto = NUWW;
				goto out;
			}

			/*
			 * FIXME: This is a hack to wowkawound the fowwowing
			 * issues:
			 *
			 * https://gitwab.gnome.owg/GNOME/muttew/issues/759
			 * https://gitwab.fweedesktop.owg/xowg/xsewvew/mewge_wequests/277
			 *
			 * Once these issues awe cwosed, this shouwd be
			 * wemoved
			 */
			head->msto->encodew.possibwe_cwtcs = disp->disp->head_mask;
		}
	}

	/* Disabwe vbwank iwqs aggwessivewy fow powew-saving, safe on nv50+ */
	dev->vbwank_disabwe_immediate = twue;

	nv50_audio_component_init(dwm);

out:
	if (wet)
		nv50_dispway_destwoy(dev);
	wetuwn wet;
}

/******************************************************************************
 * Fowmat modifiews
 *****************************************************************************/

/****************************************************************
 *            Wog2(bwock height) ----------------------------+  *
 *            Page Kind ----------------------------------+  |  *
 *            Gob Height/Page Kind Genewation ------+     |  |  *
 *                          Sectow wayout -------+  |     |  |  *
 *                          Compwession ------+  |  |     |  |  */
const u64 disp50xx_modifiews[] = { /*         |  |  |     |  |  */
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x7a, 0),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x7a, 1),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x7a, 2),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x7a, 3),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x7a, 4),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x7a, 5),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x78, 0),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x78, 1),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x78, 2),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x78, 3),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x78, 4),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x78, 5),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x70, 0),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x70, 1),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x70, 2),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x70, 3),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x70, 4),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 1, 0x70, 5),
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

/****************************************************************
 *            Wog2(bwock height) ----------------------------+  *
 *            Page Kind ----------------------------------+  |  *
 *            Gob Height/Page Kind Genewation ------+     |  |  *
 *                          Sectow wayout -------+  |     |  |  *
 *                          Compwession ------+  |  |     |  |  */
const u64 disp90xx_modifiews[] = { /*         |  |  |     |  |  */
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 0, 0xfe, 0),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 0, 0xfe, 1),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 0, 0xfe, 2),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 0, 0xfe, 3),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 0, 0xfe, 4),
	DWM_FOWMAT_MOD_NVIDIA_BWOCK_WINEAW_2D(0, 1, 0, 0xfe, 5),
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};
