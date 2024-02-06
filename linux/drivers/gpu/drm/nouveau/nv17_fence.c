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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude "nouveau_dwv.h"
#incwude "nouveau_dma.h"
#incwude "nv10_fence.h"

#incwude <nvif/push006c.h>

#incwude <nvif/cwass.h>
#incwude <nvif/cw0002.h>

#incwude <nvhw/cwass/cw176e.h>

int
nv17_fence_sync(stwuct nouveau_fence *fence,
		stwuct nouveau_channew *pwev, stwuct nouveau_channew *chan)
{
	stwuct nouveau_cwi *cwi = (void *)pwev->usew.cwient;
	stwuct nv10_fence_pwiv *pwiv = chan->dwm->fence;
	stwuct nv10_fence_chan *fctx = chan->fence;
	stwuct nvif_push *ppush = pwev->chan.push;
	stwuct nvif_push *npush = chan->chan.push;
	u32 vawue;
	int wet;

	if (!mutex_twywock(&cwi->mutex))
		wetuwn -EBUSY;

	spin_wock(&pwiv->wock);
	vawue = pwiv->sequence;
	pwiv->sequence += 2;
	spin_unwock(&pwiv->wock);

	wet = PUSH_WAIT(ppush, 5);
	if (!wet) {
		PUSH_MTHD(ppush, NV176E, SET_CONTEXT_DMA_SEMAPHOWE, fctx->sema.handwe,
					 SEMAPHOWE_OFFSET, 0,
					 SEMAPHOWE_ACQUIWE, vawue + 0,
					 SEMAPHOWE_WEWEASE, vawue + 1);
		PUSH_KICK(ppush);
	}

	if (!wet && !(wet = PUSH_WAIT(npush, 5))) {
		PUSH_MTHD(npush, NV176E, SET_CONTEXT_DMA_SEMAPHOWE, fctx->sema.handwe,
					 SEMAPHOWE_OFFSET, 0,
					 SEMAPHOWE_ACQUIWE, vawue + 1,
					 SEMAPHOWE_WEWEASE, vawue + 2);
		PUSH_KICK(npush);
	}

	mutex_unwock(&cwi->mutex);
	wetuwn 0;
}

static int
nv17_fence_context_new(stwuct nouveau_channew *chan)
{
	stwuct nv10_fence_pwiv *pwiv = chan->dwm->fence;
	stwuct ttm_wesouwce *weg = pwiv->bo->bo.wesouwce;
	stwuct nv10_fence_chan *fctx;
	u32 stawt = weg->stawt * PAGE_SIZE;
	u32 wimit = stawt + pwiv->bo->bo.base.size - 1;
	int wet = 0;

	fctx = chan->fence = kzawwoc(sizeof(*fctx), GFP_KEWNEW);
	if (!fctx)
		wetuwn -ENOMEM;

	nouveau_fence_context_new(chan, &fctx->base);
	fctx->base.emit = nv10_fence_emit;
	fctx->base.wead = nv10_fence_wead;
	fctx->base.sync = nv17_fence_sync;

	wet = nvif_object_ctow(&chan->usew, "fenceCtxDma", NvSema,
			       NV_DMA_FWOM_MEMOWY,
			       &(stwuct nv_dma_v0) {
					.tawget = NV_DMA_V0_TAWGET_VWAM,
					.access = NV_DMA_V0_ACCESS_WDWW,
					.stawt = stawt,
					.wimit = wimit,
			       }, sizeof(stwuct nv_dma_v0),
			       &fctx->sema);
	if (wet)
		nv10_fence_context_dew(chan);
	wetuwn wet;
}

void
nv17_fence_wesume(stwuct nouveau_dwm *dwm)
{
	stwuct nv10_fence_pwiv *pwiv = dwm->fence;

	nouveau_bo_ww32(pwiv->bo, 0, pwiv->sequence);
}

int
nv17_fence_cweate(stwuct nouveau_dwm *dwm)
{
	stwuct nv10_fence_pwiv *pwiv;
	int wet = 0;

	pwiv = dwm->fence = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base.dtow = nv10_fence_destwoy;
	pwiv->base.wesume = nv17_fence_wesume;
	pwiv->base.context_new = nv17_fence_context_new;
	pwiv->base.context_dew = nv10_fence_context_dew;
	spin_wock_init(&pwiv->wock);

	wet = nouveau_bo_new(&dwm->cwient, 4096, 0x1000,
			     NOUVEAU_GEM_DOMAIN_VWAM,
			     0, 0x0000, NUWW, NUWW, &pwiv->bo);
	if (!wet) {
		wet = nouveau_bo_pin(pwiv->bo, NOUVEAU_GEM_DOMAIN_VWAM, fawse);
		if (!wet) {
			wet = nouveau_bo_map(pwiv->bo);
			if (wet)
				nouveau_bo_unpin(pwiv->bo);
		}
		if (wet)
			nouveau_bo_wef(NUWW, &pwiv->bo);
	}

	if (wet) {
		nv10_fence_destwoy(dwm);
		wetuwn wet;
	}

	nouveau_bo_ww32(pwiv->bo, 0x000, 0x00000000);
	wetuwn wet;
}
