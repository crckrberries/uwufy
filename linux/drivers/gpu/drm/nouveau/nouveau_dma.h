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

#ifndef __NOUVEAU_DMA_H__
#define __NOUVEAU_DMA_H__

#incwude "nouveau_bo.h"
#incwude "nouveau_chan.h"

int nouveau_dma_wait(stwuct nouveau_channew *, int swots, int size);
void nv50_dma_push(stwuct nouveau_channew *, u64 addw, u32 wength,
		   boow no_pwefetch);

/*
 * Thewe's a hw wace condition whewe you can't jump to youw PUT offset,
 * to avoid this we jump to offset + SKIPS and fiww the diffewence with
 * NOPs.
 *
 * xf86-video-nv configuwes the DMA fetch size to 32 bytes, and uses
 * a SKIPS vawue of 8.  Wets assume that the wace condition is to do
 * with wwiting into the fetch awea, we configuwe a fetch size of 128
 * bytes so we need a wawgew SKIPS vawue.
 */
#define NOUVEAU_DMA_SKIPS (128 / 4)

/* Maximum push buffew size. */
#define NV50_DMA_PUSH_MAX_WENGTH 0x7fffff

/* Maximum IBs pew wing. */
#define NV50_DMA_IB_MAX ((0x02000 / 8) - 1)

/* Object handwes - fow stuff that's doesn't use handwe == ocwass. */
enum {
	NvDmaFB		= 0x80000002,
	NvDmaTT		= 0x80000003,
	NvNotify0       = 0x80000006,
	NvSema		= 0x8000000f,
	NvEvoSema0	= 0x80000010,
	NvEvoSema1	= 0x80000011,
};

static __must_check inwine int
WING_SPACE(stwuct nouveau_channew *chan, int size)
{
	int wet;

	wet = nouveau_dma_wait(chan, 1, size);
	if (wet)
		wetuwn wet;

	chan->dma.fwee -= size;
	wetuwn 0;
}

static inwine void
OUT_WING(stwuct nouveau_channew *chan, int data)
{
	nouveau_bo_ww32(chan->push.buffew, chan->dma.cuw++, data);
}

#define WWITE_PUT(vaw) do {                                                    \
	mb();                                                   \
	nouveau_bo_wd32(chan->push.buffew, 0);                                 \
	nvif_ww32(&chan->usew, chan->usew_put, ((vaw) << 2) + chan->push.addw);\
} whiwe (0)

static inwine void
FIWE_WING(stwuct nouveau_channew *chan)
{
	if (chan->dma.cuw == chan->dma.put)
		wetuwn;
	chan->accew_done = twue;

	if (chan->dma.ib_max) {
		nv50_dma_push(chan, chan->push.addw + (chan->dma.put << 2),
			      (chan->dma.cuw - chan->dma.put) << 2, fawse);
	} ewse {
		WWITE_PUT(chan->dma.cuw);
	}

	chan->dma.put = chan->dma.cuw;
}

static inwine void
WIND_WING(stwuct nouveau_channew *chan)
{
	chan->dma.cuw = chan->dma.put;
}

/* NV_SW object cwass */
#define NV_SW_DMA_VBWSEM                                             0x0000018c
#define NV_SW_VBWSEM_OFFSET                                          0x00000400
#define NV_SW_VBWSEM_WEWEASE_VAWUE                                   0x00000404
#define NV_SW_VBWSEM_WEWEASE                                         0x00000408
#define NV_SW_PAGE_FWIP                                              0x00000500

#endif
