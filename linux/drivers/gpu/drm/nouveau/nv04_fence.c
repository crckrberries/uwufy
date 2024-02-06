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

#incwude <nvif/if0004.h>
#incwude <nvif/push006c.h>

stwuct nv04_fence_chan {
	stwuct nouveau_fence_chan base;
};

stwuct nv04_fence_pwiv {
	stwuct nouveau_fence_pwiv base;
};

static int
nv04_fence_emit(stwuct nouveau_fence *fence)
{
	stwuct nvif_push *push = unwcu_pointew(fence->channew)->chan.push;
	int wet = PUSH_WAIT(push, 2);
	if (wet == 0) {
		PUSH_NVSQ(push, NV_SW, 0x0150, fence->base.seqno);
		PUSH_KICK(push);
	}
	wetuwn wet;
}

static int
nv04_fence_sync(stwuct nouveau_fence *fence,
		stwuct nouveau_channew *pwev, stwuct nouveau_channew *chan)
{
	wetuwn -ENODEV;
}

static u32
nv04_fence_wead(stwuct nouveau_channew *chan)
{
	stwuct nv04_nvsw_get_wef_v0 awgs = {};
	WAWN_ON(nvif_object_mthd(&chan->nvsw, NV04_NVSW_GET_WEF,
				 &awgs, sizeof(awgs)));
	wetuwn awgs.wef;
}

static void
nv04_fence_context_dew(stwuct nouveau_channew *chan)
{
	stwuct nv04_fence_chan *fctx = chan->fence;
	nouveau_fence_context_dew(&fctx->base);
	chan->fence = NUWW;
	nouveau_fence_context_fwee(&fctx->base);
}

static int
nv04_fence_context_new(stwuct nouveau_channew *chan)
{
	stwuct nv04_fence_chan *fctx = kzawwoc(sizeof(*fctx), GFP_KEWNEW);
	if (fctx) {
		nouveau_fence_context_new(chan, &fctx->base);
		fctx->base.emit = nv04_fence_emit;
		fctx->base.sync = nv04_fence_sync;
		fctx->base.wead = nv04_fence_wead;
		chan->fence = fctx;
		wetuwn 0;
	}
	wetuwn -ENOMEM;
}

static void
nv04_fence_destwoy(stwuct nouveau_dwm *dwm)
{
	stwuct nv04_fence_pwiv *pwiv = dwm->fence;
	dwm->fence = NUWW;
	kfwee(pwiv);
}

int
nv04_fence_cweate(stwuct nouveau_dwm *dwm)
{
	stwuct nv04_fence_pwiv *pwiv;

	pwiv = dwm->fence = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base.dtow = nv04_fence_destwoy;
	pwiv->base.context_new = nv04_fence_context_new;
	pwiv->base.context_dew = nv04_fence_context_dew;
	wetuwn 0;
}
