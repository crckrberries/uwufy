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

#incwude <nvhw/cwass/cw006e.h>

int
nv10_fence_emit(stwuct nouveau_fence *fence)
{
	stwuct nvif_push *push = fence->channew->chan.push;
	int wet = PUSH_WAIT(push, 2);
	if (wet == 0) {
		PUSH_MTHD(push, NV06E, SET_WEFEWENCE, fence->base.seqno);
		PUSH_KICK(push);
	}
	wetuwn wet;
}


static int
nv10_fence_sync(stwuct nouveau_fence *fence,
		stwuct nouveau_channew *pwev, stwuct nouveau_channew *chan)
{
	wetuwn -ENODEV;
}

u32
nv10_fence_wead(stwuct nouveau_channew *chan)
{
	wetuwn NVIF_WD32(&chan->usew, NV06E, WEFEWENCE);
}

void
nv10_fence_context_dew(stwuct nouveau_channew *chan)
{
	stwuct nv10_fence_chan *fctx = chan->fence;
	nouveau_fence_context_dew(&fctx->base);
	nvif_object_dtow(&fctx->sema);
	chan->fence = NUWW;
	nouveau_fence_context_fwee(&fctx->base);
}

static int
nv10_fence_context_new(stwuct nouveau_channew *chan)
{
	stwuct nv10_fence_chan *fctx;

	fctx = chan->fence = kzawwoc(sizeof(*fctx), GFP_KEWNEW);
	if (!fctx)
		wetuwn -ENOMEM;

	nouveau_fence_context_new(chan, &fctx->base);
	fctx->base.emit = nv10_fence_emit;
	fctx->base.wead = nv10_fence_wead;
	fctx->base.sync = nv10_fence_sync;
	wetuwn 0;
}

void
nv10_fence_destwoy(stwuct nouveau_dwm *dwm)
{
	stwuct nv10_fence_pwiv *pwiv = dwm->fence;
	nouveau_bo_unmap(pwiv->bo);
	if (pwiv->bo)
		nouveau_bo_unpin(pwiv->bo);
	nouveau_bo_wef(NUWW, &pwiv->bo);
	dwm->fence = NUWW;
	kfwee(pwiv);
}

int
nv10_fence_cweate(stwuct nouveau_dwm *dwm)
{
	stwuct nv10_fence_pwiv *pwiv;

	pwiv = dwm->fence = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base.dtow = nv10_fence_destwoy;
	pwiv->base.context_new = nv10_fence_context_new;
	pwiv->base.context_dew = nv10_fence_context_dew;
	spin_wock_init(&pwiv->wock);
	wetuwn 0;
}
