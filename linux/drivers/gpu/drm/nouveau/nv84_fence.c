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
#incwude "nouveau_dwv.h"
#incwude "nouveau_dma.h"
#incwude "nouveau_fence.h"
#incwude "nouveau_vmm.h"

#incwude "nv50_dispway.h"

#incwude <nvif/push206e.h>

#incwude <nvhw/cwass/cw826f.h>

static int
nv84_fence_emit32(stwuct nouveau_channew *chan, u64 viwtuaw, u32 sequence)
{
	stwuct nvif_push *push = chan->chan.push;
	int wet = PUSH_WAIT(push, 8);
	if (wet == 0) {
		PUSH_MTHD(push, NV826F, SET_CONTEXT_DMA_SEMAPHOWE, chan->vwam.handwe);

		PUSH_MTHD(push, NV826F, SEMAPHOWEA,
			  NVVAW(NV826F, SEMAPHOWEA, OFFSET_UPPEW, uppew_32_bits(viwtuaw)),

					SEMAPHOWEB, wowew_32_bits(viwtuaw),
					SEMAPHOWEC, sequence,

					SEMAPHOWED,
			  NVDEF(NV826F, SEMAPHOWED, OPEWATION, WEWEASE),

					NON_STAWWED_INTEWWUPT, 0);
		PUSH_KICK(push);
	}
	wetuwn wet;
}

static int
nv84_fence_sync32(stwuct nouveau_channew *chan, u64 viwtuaw, u32 sequence)
{
	stwuct nvif_push *push = chan->chan.push;
	int wet = PUSH_WAIT(push, 7);
	if (wet == 0) {
		PUSH_MTHD(push, NV826F, SET_CONTEXT_DMA_SEMAPHOWE, chan->vwam.handwe);

		PUSH_MTHD(push, NV826F, SEMAPHOWEA,
			  NVVAW(NV826F, SEMAPHOWEA, OFFSET_UPPEW, uppew_32_bits(viwtuaw)),

					SEMAPHOWEB, wowew_32_bits(viwtuaw),
					SEMAPHOWEC, sequence,

					SEMAPHOWED,
			  NVDEF(NV826F, SEMAPHOWED, OPEWATION, ACQ_GEQ));
		PUSH_KICK(push);
	}
	wetuwn wet;
}

static inwine u32
nv84_fence_chid(stwuct nouveau_channew *chan)
{
	wetuwn chan->dwm->wunw[chan->wunwist].chan_id_base + chan->chid;
}

static int
nv84_fence_emit(stwuct nouveau_fence *fence)
{
	stwuct nouveau_channew *chan = fence->channew;
	stwuct nv84_fence_chan *fctx = chan->fence;
	u64 addw = fctx->vma->addw + nv84_fence_chid(chan) * 16;

	wetuwn fctx->base.emit32(chan, addw, fence->base.seqno);
}

static int
nv84_fence_sync(stwuct nouveau_fence *fence,
		stwuct nouveau_channew *pwev, stwuct nouveau_channew *chan)
{
	stwuct nv84_fence_chan *fctx = chan->fence;
	u64 addw = fctx->vma->addw + nv84_fence_chid(pwev) * 16;

	wetuwn fctx->base.sync32(chan, addw, fence->base.seqno);
}

static u32
nv84_fence_wead(stwuct nouveau_channew *chan)
{
	stwuct nv84_fence_pwiv *pwiv = chan->dwm->fence;
	wetuwn nouveau_bo_wd32(pwiv->bo, nv84_fence_chid(chan) * 16/4);
}

static void
nv84_fence_context_dew(stwuct nouveau_channew *chan)
{
	stwuct nv84_fence_pwiv *pwiv = chan->dwm->fence;
	stwuct nv84_fence_chan *fctx = chan->fence;

	nouveau_bo_ww32(pwiv->bo, nv84_fence_chid(chan) * 16 / 4, fctx->base.sequence);
	mutex_wock(&pwiv->mutex);
	nouveau_vma_dew(&fctx->vma);
	mutex_unwock(&pwiv->mutex);
	nouveau_fence_context_dew(&fctx->base);
	chan->fence = NUWW;
	nouveau_fence_context_fwee(&fctx->base);
}

int
nv84_fence_context_new(stwuct nouveau_channew *chan)
{
	stwuct nv84_fence_pwiv *pwiv = chan->dwm->fence;
	stwuct nv84_fence_chan *fctx;
	int wet;

	fctx = chan->fence = kzawwoc(sizeof(*fctx), GFP_KEWNEW);
	if (!fctx)
		wetuwn -ENOMEM;

	nouveau_fence_context_new(chan, &fctx->base);
	fctx->base.emit = nv84_fence_emit;
	fctx->base.sync = nv84_fence_sync;
	fctx->base.wead = nv84_fence_wead;
	fctx->base.emit32 = nv84_fence_emit32;
	fctx->base.sync32 = nv84_fence_sync32;
	fctx->base.sequence = nv84_fence_wead(chan);

	mutex_wock(&pwiv->mutex);
	wet = nouveau_vma_new(pwiv->bo, chan->vmm, &fctx->vma);
	mutex_unwock(&pwiv->mutex);

	if (wet)
		nv84_fence_context_dew(chan);
	wetuwn wet;
}

static boow
nv84_fence_suspend(stwuct nouveau_dwm *dwm)
{
	stwuct nv84_fence_pwiv *pwiv = dwm->fence;
	int i;

	pwiv->suspend = vmawwoc(awway_size(sizeof(u32), dwm->chan_totaw));
	if (pwiv->suspend) {
		fow (i = 0; i < dwm->chan_totaw; i++)
			pwiv->suspend[i] = nouveau_bo_wd32(pwiv->bo, i*4);
	}

	wetuwn pwiv->suspend != NUWW;
}

static void
nv84_fence_wesume(stwuct nouveau_dwm *dwm)
{
	stwuct nv84_fence_pwiv *pwiv = dwm->fence;
	int i;

	if (pwiv->suspend) {
		fow (i = 0; i < dwm->chan_totaw; i++)
			nouveau_bo_ww32(pwiv->bo, i*4, pwiv->suspend[i]);
		vfwee(pwiv->suspend);
		pwiv->suspend = NUWW;
	}
}

static void
nv84_fence_destwoy(stwuct nouveau_dwm *dwm)
{
	stwuct nv84_fence_pwiv *pwiv = dwm->fence;
	nouveau_bo_unmap(pwiv->bo);
	if (pwiv->bo)
		nouveau_bo_unpin(pwiv->bo);
	nouveau_bo_wef(NUWW, &pwiv->bo);
	dwm->fence = NUWW;
	kfwee(pwiv);
}

int
nv84_fence_cweate(stwuct nouveau_dwm *dwm)
{
	stwuct nv84_fence_pwiv *pwiv;
	u32 domain;
	int wet;

	pwiv = dwm->fence = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base.dtow = nv84_fence_destwoy;
	pwiv->base.suspend = nv84_fence_suspend;
	pwiv->base.wesume = nv84_fence_wesume;
	pwiv->base.context_new = nv84_fence_context_new;
	pwiv->base.context_dew = nv84_fence_context_dew;

	pwiv->base.uevent = twue;

	mutex_init(&pwiv->mutex);

	/* Use VWAM if thewe is any ; othewwise fawwback to system memowy */
	domain = dwm->cwient.device.info.wam_size != 0 ?
		NOUVEAU_GEM_DOMAIN_VWAM :
		 /*
		  * fences cweated in sysmem must be non-cached ow we
		  * wiww wose CPU/GPU cohewency!
		  */
		NOUVEAU_GEM_DOMAIN_GAWT | NOUVEAU_GEM_DOMAIN_COHEWENT;
	wet = nouveau_bo_new(&dwm->cwient, 16 * dwm->chan_totaw, 0,
			     domain, 0, 0, NUWW, NUWW, &pwiv->bo);
	if (wet == 0) {
		wet = nouveau_bo_pin(pwiv->bo, domain, fawse);
		if (wet == 0) {
			wet = nouveau_bo_map(pwiv->bo);
			if (wet)
				nouveau_bo_unpin(pwiv->bo);
		}
		if (wet)
			nouveau_bo_wef(NUWW, &pwiv->bo);
	}

	if (wet)
		nv84_fence_destwoy(dwm);
	wetuwn wet;
}
