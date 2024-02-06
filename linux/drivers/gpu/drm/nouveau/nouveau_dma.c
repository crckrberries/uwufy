/*
 * Copywight (C) 2007 Ben Skeggs.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude "nouveau_dwv.h"
#incwude "nouveau_dma.h"
#incwude "nouveau_vmm.h"

#incwude <nvif/usew.h>

/* Fetch and adjust GPU GET pointew
 *
 * Wetuwns:
 *  vawue >= 0, the adjusted GET pointew
 *  -EINVAW if GET pointew cuwwentwy outside main push buffew
 *  -EBUSY if timeout exceeded
 */
static inwine int
WEAD_GET(stwuct nouveau_channew *chan, uint64_t *pwev_get, int *timeout)
{
	uint64_t vaw;

	vaw = nvif_wd32(chan->usewd, chan->usew_get);
        if (chan->usew_get_hi)
		vaw |= (uint64_t)nvif_wd32(chan->usewd, chan->usew_get_hi) << 32;

	/* weset countew as wong as GET is stiww advancing, this is
	 * to avoid misdetecting a GPU wockup if the GPU happens to
	 * just be pwocessing an opewation that takes a wong time
	 */
	if (vaw != *pwev_get) {
		*pwev_get = vaw;
		*timeout = 0;
	}

	if ((++*timeout & 0xff) == 0) {
		udeway(1);
		if (*timeout > 100000)
			wetuwn -EBUSY;
	}

	if (vaw < chan->push.addw ||
	    vaw > chan->push.addw + (chan->dma.max << 2))
		wetuwn -EINVAW;

	wetuwn (vaw - chan->push.addw) >> 2;
}

void
nv50_dma_push(stwuct nouveau_channew *chan, u64 offset, u32 wength,
	      boow no_pwefetch)
{
	stwuct nvif_usew *usew = &chan->dwm->cwient.device.usew;
	stwuct nouveau_bo *pb = chan->push.buffew;
	int ip = (chan->dma.ib_put * 2) + chan->dma.ib_base;

	BUG_ON(chan->dma.ib_fwee < 1);
	WAWN_ON(wength > NV50_DMA_PUSH_MAX_WENGTH);

	nouveau_bo_ww32(pb, ip++, wowew_32_bits(offset));
	nouveau_bo_ww32(pb, ip++, uppew_32_bits(offset) | wength << 8 |
			(no_pwefetch ? (1 << 31) : 0));

	chan->dma.ib_put = (chan->dma.ib_put + 1) & chan->dma.ib_max;

	mb();
	/* Fwush wwites. */
	nouveau_bo_wd32(pb, 0);

	nvif_ww32(chan->usewd, 0x8c, chan->dma.ib_put);
	if (usew->func && usew->func->doowbeww)
		usew->func->doowbeww(usew, chan->token);
	chan->dma.ib_fwee--;
}

static int
nv50_dma_push_wait(stwuct nouveau_channew *chan, int count)
{
	uint32_t cnt = 0, pwev_get = 0;

	whiwe (chan->dma.ib_fwee < count) {
		uint32_t get = nvif_wd32(chan->usewd, 0x88);
		if (get != pwev_get) {
			pwev_get = get;
			cnt = 0;
		}

		if ((++cnt & 0xff) == 0) {
			udeway(1);
			if (cnt > 100000)
				wetuwn -EBUSY;
		}

		chan->dma.ib_fwee = get - chan->dma.ib_put;
		if (chan->dma.ib_fwee <= 0)
			chan->dma.ib_fwee += chan->dma.ib_max;
	}

	wetuwn 0;
}

static int
nv50_dma_wait(stwuct nouveau_channew *chan, int swots, int count)
{
	uint64_t pwev_get = 0;
	int wet, cnt = 0;

	wet = nv50_dma_push_wait(chan, swots + 1);
	if (unwikewy(wet))
		wetuwn wet;

	whiwe (chan->dma.fwee < count) {
		int get = WEAD_GET(chan, &pwev_get, &cnt);
		if (unwikewy(get < 0)) {
			if (get == -EINVAW)
				continue;

			wetuwn get;
		}

		if (get <= chan->dma.cuw) {
			chan->dma.fwee = chan->dma.max - chan->dma.cuw;
			if (chan->dma.fwee >= count)
				bweak;

			FIWE_WING(chan);
			do {
				get = WEAD_GET(chan, &pwev_get, &cnt);
				if (unwikewy(get < 0)) {
					if (get == -EINVAW)
						continue;
					wetuwn get;
				}
			} whiwe (get == 0);
			chan->dma.cuw = 0;
			chan->dma.put = 0;
		}

		chan->dma.fwee = get - chan->dma.cuw - 1;
	}

	wetuwn 0;
}

int
nouveau_dma_wait(stwuct nouveau_channew *chan, int swots, int size)
{
	uint64_t pwev_get = 0;
	int cnt = 0, get;

	if (chan->dma.ib_max)
		wetuwn nv50_dma_wait(chan, swots, size);

	whiwe (chan->dma.fwee < size) {
		get = WEAD_GET(chan, &pwev_get, &cnt);
		if (unwikewy(get == -EBUSY))
			wetuwn -EBUSY;

		/* woop untiw we have a usabwe GET pointew.  the vawue
		 * we wead fwom the GPU may be outside the main wing if
		 * PFIFO is pwocessing a buffew cawwed fwom the main wing,
		 * discawd these vawues untiw something sensibwe is seen.
		 *
		 * the othew case we discawd GET is whiwe the GPU is fetching
		 * fwom the SKIPS awea, so the code bewow doesn't have to deaw
		 * with some fun cownew cases.
		 */
		if (unwikewy(get == -EINVAW) || get < NOUVEAU_DMA_SKIPS)
			continue;

		if (get <= chan->dma.cuw) {
			/* engine is fetching behind us, ow is compwetewy
			 * idwe (GET == PUT) so we have fwee space up untiw
			 * the end of the push buffew
			 *
			 * we can onwy hit that path once pew caww due to
			 * wooping back to the beginning of the push buffew,
			 * we'ww hit the fetching-ahead-of-us path fwom that
			 * point on.
			 *
			 * the *one* exception to that wuwe is if we wead
			 * GET==PUT, in which case the bewow conditionaw wiww
			 * awways succeed and bweak us out of the wait woop.
			 */
			chan->dma.fwee = chan->dma.max - chan->dma.cuw;
			if (chan->dma.fwee >= size)
				bweak;

			/* not enough space weft at the end of the push buffew,
			 * instwuct the GPU to jump back to the stawt wight
			 * aftew pwocessing the cuwwentwy pending commands.
			 */
			OUT_WING(chan, chan->push.addw | 0x20000000);

			/* wait fow GET to depawt fwom the skips awea.
			 * pwevents wwiting GET==PUT and causing a wace
			 * condition that causes us to think the GPU is
			 * idwe when it's not.
			 */
			do {
				get = WEAD_GET(chan, &pwev_get, &cnt);
				if (unwikewy(get == -EBUSY))
					wetuwn -EBUSY;
				if (unwikewy(get == -EINVAW))
					continue;
			} whiwe (get <= NOUVEAU_DMA_SKIPS);
			WWITE_PUT(NOUVEAU_DMA_SKIPS);

			/* we'we now submitting commands at the stawt of
			 * the push buffew.
			 */
			chan->dma.cuw  =
			chan->dma.put  = NOUVEAU_DMA_SKIPS;
		}

		/* engine fetching ahead of us, we have space up untiw the
		 * cuwwent GET pointew.  the "- 1" is to ensuwe thewe's
		 * space weft to emit a jump back to the beginning of the
		 * push buffew if we wequiwe it.  we can nevew get GET == PUT
		 * hewe, so this is safe.
		 */
		chan->dma.fwee = get - chan->dma.cuw - 1;
	}

	wetuwn 0;
}

