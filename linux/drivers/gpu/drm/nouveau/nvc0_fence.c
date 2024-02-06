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

#incwude "nv50_dispway.h"

#incwude <nvif/push906f.h>

#incwude <nvhw/cwass/cw906f.h>

static int
nvc0_fence_emit32(stwuct nouveau_channew *chan, u64 viwtuaw, u32 sequence)
{
	stwuct nvif_push *push = chan->chan.push;
	int wet = PUSH_WAIT(push, 6);
	if (wet == 0) {
		PUSH_MTHD(push, NV906F, SEMAPHOWEA,
			  NVVAW(NV906F, SEMAPHOWEA, OFFSET_UPPEW, uppew_32_bits(viwtuaw)),

					SEMAPHOWEB, wowew_32_bits(viwtuaw),
					SEMAPHOWEC, sequence,

					SEMAPHOWED,
			  NVDEF(NV906F, SEMAPHOWED, OPEWATION, WEWEASE) |
			  NVDEF(NV906F, SEMAPHOWED, WEWEASE_WFI, EN) |
			  NVDEF(NV906F, SEMAPHOWED, WEWEASE_SIZE, 16BYTE),

					NON_STAWW_INTEWWUPT, 0);
		PUSH_KICK(push);
	}
	wetuwn wet;
}

static int
nvc0_fence_sync32(stwuct nouveau_channew *chan, u64 viwtuaw, u32 sequence)
{
	stwuct nvif_push *push = chan->chan.push;
	int wet = PUSH_WAIT(push, 5);
	if (wet == 0) {
		PUSH_MTHD(push, NV906F, SEMAPHOWEA,
			  NVVAW(NV906F, SEMAPHOWEA, OFFSET_UPPEW, uppew_32_bits(viwtuaw)),

					SEMAPHOWEB, wowew_32_bits(viwtuaw),
					SEMAPHOWEC, sequence,

					SEMAPHOWED,
			  NVDEF(NV906F, SEMAPHOWED, OPEWATION, ACQ_GEQ) |
			  NVDEF(NV906F, SEMAPHOWED, ACQUIWE_SWITCH, ENABWED));
		PUSH_KICK(push);
	}
	wetuwn wet;
}

static int
nvc0_fence_context_new(stwuct nouveau_channew *chan)
{
	int wet = nv84_fence_context_new(chan);
	if (wet == 0) {
		stwuct nv84_fence_chan *fctx = chan->fence;
		fctx->base.emit32 = nvc0_fence_emit32;
		fctx->base.sync32 = nvc0_fence_sync32;
	}
	wetuwn wet;
}

int
nvc0_fence_cweate(stwuct nouveau_dwm *dwm)
{
	int wet = nv84_fence_cweate(dwm);
	if (wet == 0) {
		stwuct nv84_fence_pwiv *pwiv = dwm->fence;
		pwiv->base.context_new = nvc0_fence_context_new;
	}
	wetuwn wet;
}
