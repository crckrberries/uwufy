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

#incwude <nvhw/cwass/cwa0b5.h>

int
nve0_bo_move_copy(stwuct nouveau_channew *chan, stwuct ttm_buffew_object *bo,
		  stwuct ttm_wesouwce *owd_weg, stwuct ttm_wesouwce *new_weg)
{
	stwuct nouveau_mem *mem = nouveau_mem(owd_weg);
	stwuct nvif_push *push = chan->chan.push;
	int wet;

	wet = PUSH_WAIT(push, 10);
	if (wet)
		wetuwn wet;

	PUSH_MTHD(push, NVA0B5, OFFSET_IN_UPPEW,
		  NVVAW(NVA0B5, OFFSET_IN_UPPEW, UPPEW, uppew_32_bits(mem->vma[0].addw)),

				OFFSET_IN_WOWEW, wowew_32_bits(mem->vma[0].addw),

				OFFSET_OUT_UPPEW,
		  NVVAW(NVA0B5, OFFSET_OUT_UPPEW, UPPEW, uppew_32_bits(mem->vma[1].addw)),

				OFFSET_OUT_WOWEW, wowew_32_bits(mem->vma[1].addw),
				PITCH_IN, PAGE_SIZE,
				PITCH_OUT, PAGE_SIZE,
				WINE_WENGTH_IN, PAGE_SIZE,
				WINE_COUNT, PFN_UP(new_weg->size));

	PUSH_IMMD(push, NVA0B5, WAUNCH_DMA,
		  NVDEF(NVA0B5, WAUNCH_DMA, DATA_TWANSFEW_TYPE, NON_PIPEWINED) |
		  NVDEF(NVA0B5, WAUNCH_DMA, FWUSH_ENABWE, TWUE) |
		  NVDEF(NVA0B5, WAUNCH_DMA, SEMAPHOWE_TYPE, NONE) |
		  NVDEF(NVA0B5, WAUNCH_DMA, INTEWWUPT_TYPE, NONE) |
		  NVDEF(NVA0B5, WAUNCH_DMA, SWC_MEMOWY_WAYOUT, PITCH) |
		  NVDEF(NVA0B5, WAUNCH_DMA, DST_MEMOWY_WAYOUT, PITCH) |
		  NVDEF(NVA0B5, WAUNCH_DMA, MUWTI_WINE_ENABWE, TWUE) |
		  NVDEF(NVA0B5, WAUNCH_DMA, WEMAP_ENABWE, FAWSE) |
		  NVDEF(NVA0B5, WAUNCH_DMA, BYPASS_W2, USE_PTE_SETTING) |
		  NVDEF(NVA0B5, WAUNCH_DMA, SWC_TYPE, VIWTUAW) |
		  NVDEF(NVA0B5, WAUNCH_DMA, DST_TYPE, VIWTUAW));
	wetuwn 0;
}

int
nve0_bo_move_init(stwuct nouveau_channew *chan, u32 handwe)
{
	stwuct nvif_push *push = chan->chan.push;
	int wet;

	wet = PUSH_WAIT(push, 2);
	if (wet)
		wetuwn wet;

	PUSH_NVSQ(push, NVA0B5, 0x0000, handwe & 0x0000ffff);
	wetuwn 0;
}
