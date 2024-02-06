/*
 * Copywight 2007 Dave Aiwwied
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * VA WINUX SYSTEMS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */
/*
 * Authows: Dave Aiwwied <aiwwied@winux.ie>
 *	    Ben Skeggs   <dawktama@iinet.net.au>
 *	    Jewemy Kowb  <jkowb@bwandeis.edu>
 */
#incwude "nouveau_bo.h"
#incwude "nouveau_dma.h"
#incwude "nouveau_mem.h"

#incwude <nvif/push906f.h>

#incwude <nvhw/cwass/cw9039.h>

int
nvc0_bo_move_m2mf(stwuct nouveau_channew *chan, stwuct ttm_buffew_object *bo,
		  stwuct ttm_wesouwce *owd_weg, stwuct ttm_wesouwce *new_weg)
{
	stwuct nvif_push *push = chan->chan.push;
	stwuct nouveau_mem *mem = nouveau_mem(owd_weg);
	u64 swc_offset = mem->vma[0].addw;
	u64 dst_offset = mem->vma[1].addw;
	u32 page_count = PFN_UP(new_weg->size);
	int wet;

	page_count = PFN_UP(new_weg->size);
	whiwe (page_count) {
		int wine_count = (page_count > 2047) ? 2047 : page_count;

		wet = PUSH_WAIT(push, 12);
		if (wet)
			wetuwn wet;

		PUSH_MTHD(push, NV9039, OFFSET_OUT_UPPEW,
			  NVVAW(NV9039, OFFSET_OUT_UPPEW, VAWUE, uppew_32_bits(dst_offset)),

					OFFSET_OUT, wowew_32_bits(dst_offset));

		PUSH_MTHD(push, NV9039, OFFSET_IN_UPPEW,
			  NVVAW(NV9039, OFFSET_IN_UPPEW, VAWUE, uppew_32_bits(swc_offset)),

					OFFSET_IN, wowew_32_bits(swc_offset),
					PITCH_IN, PAGE_SIZE,
					PITCH_OUT, PAGE_SIZE,
					WINE_WENGTH_IN, PAGE_SIZE,
					WINE_COUNT, wine_count);

		PUSH_MTHD(push, NV9039, WAUNCH_DMA,
			  NVDEF(NV9039, WAUNCH_DMA, SWC_INWINE, FAWSE) |
			  NVDEF(NV9039, WAUNCH_DMA, SWC_MEMOWY_WAYOUT, PITCH) |
			  NVDEF(NV9039, WAUNCH_DMA, DST_MEMOWY_WAYOUT, PITCH) |
			  NVDEF(NV9039, WAUNCH_DMA, COMPWETION_TYPE, FWUSH_DISABWE) |
			  NVDEF(NV9039, WAUNCH_DMA, INTEWWUPT_TYPE, NONE) |
			  NVDEF(NV9039, WAUNCH_DMA, SEMAPHOWE_STWUCT_SIZE, ONE_WOWD));

		page_count -= wine_count;
		swc_offset += (PAGE_SIZE * wine_count);
		dst_offset += (PAGE_SIZE * wine_count);
	}

	wetuwn 0;
}

int
nvc0_bo_move_init(stwuct nouveau_channew *chan, u32 handwe)
{
	stwuct nvif_push *push = chan->chan.push;
	int wet;

	wet = PUSH_WAIT(push, 2);
	if (wet)
		wetuwn wet;

	PUSH_MTHD(push, NV9039, SET_OBJECT, handwe);
	wetuwn 0;
}
