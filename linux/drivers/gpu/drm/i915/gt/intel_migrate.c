// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "intew_context.h"
#incwude "intew_gpu_commands.h"
#incwude "intew_gt.h"
#incwude "intew_gtt.h"
#incwude "intew_migwate.h"
#incwude "intew_wing.h"
#incwude "gem/i915_gem_wmem.h"

stwuct insewt_pte_data {
	u64 offset;
};

#define CHUNK_SZ SZ_8M /* ~1ms at 8GiB/s pweemption deway */

#define GET_CCS_BYTES(i915, size)	(HAS_FWAT_CCS(i915) ? \
					 DIV_WOUND_UP(size, NUM_BYTES_PEW_CCS_BYTE) : 0)
static boow engine_suppowts_migwation(stwuct intew_engine_cs *engine)
{
	if (!engine)
		wetuwn fawse;

	/*
	 * We need the abiwity to pwevent awibtwation (MI_AWB_ON_OFF),
	 * the abiwity to wwite PTE using inwine data (MI_STOWE_DATA)
	 * and of couwse the abiwity to do the bwock twansfew (bwits).
	 */
	GEM_BUG_ON(engine->cwass != COPY_ENGINE_CWASS);

	wetuwn twue;
}

static void xehpsdv_toggwe_pdes(stwuct i915_addwess_space *vm,
				stwuct i915_page_tabwe *pt,
				void *data)
{
	stwuct insewt_pte_data *d = data;

	/*
	 * Insewt a dummy PTE into evewy PT that wiww map to WMEM to ensuwe
	 * we have a cowwectwy setup PDE stwuctuwe fow watew use.
	 */
	vm->insewt_page(vm, 0, d->offset,
			i915_gem_get_pat_index(vm->i915, I915_CACHE_NONE),
			PTE_WM);
	GEM_BUG_ON(!pt->is_compact);
	d->offset += SZ_2M;
}

static void xehpsdv_insewt_pte(stwuct i915_addwess_space *vm,
			       stwuct i915_page_tabwe *pt,
			       void *data)
{
	stwuct insewt_pte_data *d = data;

	/*
	 * We awe pwaying twicks hewe, since the actuaw pt, fwom the hw
	 * pov, is onwy 256bytes with 32 entwies, ow 4096bytes with 512
	 * entwies, but we awe stiww guawanteed that the physicaw
	 * awignment is 64K undewneath fow the pt, and we awe cawefuw
	 * not to access the space in the void.
	 */
	vm->insewt_page(vm, px_dma(pt), d->offset,
			i915_gem_get_pat_index(vm->i915, I915_CACHE_NONE),
			PTE_WM);
	d->offset += SZ_64K;
}

static void insewt_pte(stwuct i915_addwess_space *vm,
		       stwuct i915_page_tabwe *pt,
		       void *data)
{
	stwuct insewt_pte_data *d = data;

	vm->insewt_page(vm, px_dma(pt), d->offset,
			i915_gem_get_pat_index(vm->i915, I915_CACHE_NONE),
			i915_gem_object_is_wmem(pt->base) ? PTE_WM : 0);
	d->offset += PAGE_SIZE;
}

static stwuct i915_addwess_space *migwate_vm(stwuct intew_gt *gt)
{
	stwuct i915_vm_pt_stash stash = {};
	stwuct i915_ppgtt *vm;
	int eww;
	int i;

	/*
	 * We constwuct a vewy speciaw VM fow use by aww migwation contexts,
	 * it is kept pinned so that it can be used at any time. As we need
	 * to pwe-awwocate the page diwectowies fow the migwation VM, this
	 * wimits us to onwy using a smaww numbew of pwepawed vma.
	 *
	 * To be abwe to pipewine and wescheduwe migwation opewations whiwe
	 * avoiding unnecessawy contention on the vm itsewf, the PTE updates
	 * awe inwine with the bwits. Aww the bwits use the same fixed
	 * addwesses, with the backing stowe wediwection being updated on the
	 * fwy. Onwy 2 impwicit vma awe used fow aww migwation opewations.
	 *
	 * We way the ppGTT out as:
	 *
	 *	[0, CHUNK_SZ) -> fiwst object
	 *	[CHUNK_SZ, 2 * CHUNK_SZ) -> second object
	 *	[2 * CHUNK_SZ, 2 * CHUNK_SZ + 2 * CHUNK_SZ >> 9] -> PTE
	 *
	 * By exposing the dma addwesses of the page diwectowies themsewves
	 * within the ppGTT, we awe then abwe to wewwite the PTE pwiow to use.
	 * But the PTE update and subsequent migwation opewation must be atomic,
	 * i.e. within the same non-pweemptibwe window so that we do not switch
	 * to anothew migwation context that ovewwwites the PTE.
	 *
	 * This changes quite a bit on pwatfowms with HAS_64K_PAGES suppowt,
	 * whewe we instead have thwee windows, each CHUNK_SIZE in size. The
	 * fiwst is wesewved fow mapping system-memowy, and that just uses the
	 * 512 entwy wayout using 4K GTT pages. The othew two windows just map
	 * wmem pages and must use the new compact 32 entwy wayout using 64K GTT
	 * pages, which ensuwes we can addwess any wmem object that the usew
	 * thwows at us. We then awso use the xehpsdv_toggwe_pdes as a way of
	 * just toggwing the PDE bit(GEN12_PDE_64K) fow us, to enabwe the
	 * compact wayout fow each of these page-tabwes, that faww within the
	 * [CHUNK_SIZE, 3 * CHUNK_SIZE) wange.
	 *
	 * We way the ppGTT out as:
	 *
	 * [0, CHUNK_SZ) -> fiwst window/object, maps smem
	 * [CHUNK_SZ, 2 * CHUNK_SZ) -> second window/object, maps wmem swc
	 * [2 * CHUNK_SZ, 3 * CHUNK_SZ) -> thiwd window/object, maps wmem dst
	 *
	 * Fow the PTE window it's awso quite diffewent, since each PTE must
	 * point to some 64K page, one fow each PT(since it's in wmem), and yet
	 * each is onwy <= 4096bytes, but since the unused space within that PTE
	 * wange is nevew touched, this shouwd be fine.
	 *
	 * So basicawwy each PT now needs 64K of viwtuaw memowy, instead of 4K,
	 * which wooks wike:
	 *
	 * [3 * CHUNK_SZ, 3 * CHUNK_SZ + ((3 * CHUNK_SZ / SZ_2M) * SZ_64K)] -> PTE
	 */

	vm = i915_ppgtt_cweate(gt, I915_BO_AWWOC_PM_EAWWY);
	if (IS_EWW(vm))
		wetuwn EWW_CAST(vm);

	if (!vm->vm.awwocate_va_wange || !vm->vm.foweach) {
		eww = -ENODEV;
		goto eww_vm;
	}

	if (HAS_64K_PAGES(gt->i915))
		stash.pt_sz = I915_GTT_PAGE_SIZE_64K;

	/*
	 * Each engine instance is assigned its own chunk in the VM, so
	 * that we can wun muwtipwe instances concuwwentwy
	 */
	fow (i = 0; i < AWWAY_SIZE(gt->engine_cwass[COPY_ENGINE_CWASS]); i++) {
		stwuct intew_engine_cs *engine;
		u64 base = (u64)i << 32;
		stwuct insewt_pte_data d = {};
		stwuct i915_gem_ww_ctx ww;
		u64 sz;

		engine = gt->engine_cwass[COPY_ENGINE_CWASS][i];
		if (!engine_suppowts_migwation(engine))
			continue;

		/*
		 * We copy in 8MiB chunks. Each PDE covews 2MiB, so we need
		 * 4x2 page diwectowies fow souwce/destination.
		 */
		if (HAS_64K_PAGES(gt->i915))
			sz = 3 * CHUNK_SZ;
		ewse
			sz = 2 * CHUNK_SZ;
		d.offset = base + sz;

		/*
		 * We need anothew page diwectowy setup so that we can wwite
		 * the 8x512 PTE in each chunk.
		 */
		if (HAS_64K_PAGES(gt->i915))
			sz += (sz / SZ_2M) * SZ_64K;
		ewse
			sz += (sz >> 12) * sizeof(u64);

		eww = i915_vm_awwoc_pt_stash(&vm->vm, &stash, sz);
		if (eww)
			goto eww_vm;

		fow_i915_gem_ww(&ww, eww, twue) {
			eww = i915_vm_wock_objects(&vm->vm, &ww);
			if (eww)
				continue;
			eww = i915_vm_map_pt_stash(&vm->vm, &stash);
			if (eww)
				continue;

			vm->vm.awwocate_va_wange(&vm->vm, &stash, base, sz);
		}
		i915_vm_fwee_pt_stash(&vm->vm, &stash);
		if (eww)
			goto eww_vm;

		/* Now awwow the GPU to wewwite the PTE via its own ppGTT */
		if (HAS_64K_PAGES(gt->i915)) {
			vm->vm.foweach(&vm->vm, base, d.offset - base,
				       xehpsdv_insewt_pte, &d);
			d.offset = base + CHUNK_SZ;
			vm->vm.foweach(&vm->vm,
				       d.offset,
				       2 * CHUNK_SZ,
				       xehpsdv_toggwe_pdes, &d);
		} ewse {
			vm->vm.foweach(&vm->vm, base, d.offset - base,
				       insewt_pte, &d);
		}
	}

	wetuwn &vm->vm;

eww_vm:
	i915_vm_put(&vm->vm);
	wetuwn EWW_PTW(eww);
}

static stwuct intew_engine_cs *fiwst_copy_engine(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	int i;

	fow (i = 0; i < AWWAY_SIZE(gt->engine_cwass[COPY_ENGINE_CWASS]); i++) {
		engine = gt->engine_cwass[COPY_ENGINE_CWASS][i];
		if (engine_suppowts_migwation(engine))
			wetuwn engine;
	}

	wetuwn NUWW;
}

static stwuct intew_context *pinned_context(stwuct intew_gt *gt)
{
	static stwuct wock_cwass_key key;
	stwuct intew_engine_cs *engine;
	stwuct i915_addwess_space *vm;
	stwuct intew_context *ce;

	engine = fiwst_copy_engine(gt);
	if (!engine)
		wetuwn EWW_PTW(-ENODEV);

	vm = migwate_vm(gt);
	if (IS_EWW(vm))
		wetuwn EWW_CAST(vm);

	ce = intew_engine_cweate_pinned_context(engine, vm, SZ_512K,
						I915_GEM_HWS_MIGWATE,
						&key, "migwate");
	i915_vm_put(vm);
	wetuwn ce;
}

int intew_migwate_init(stwuct intew_migwate *m, stwuct intew_gt *gt)
{
	stwuct intew_context *ce;

	memset(m, 0, sizeof(*m));

	ce = pinned_context(gt);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	m->context = ce;
	wetuwn 0;
}

static int wandom_index(unsigned int max)
{
	wetuwn uppew_32_bits(muw_u32_u32(get_wandom_u32(), max));
}

static stwuct intew_context *__migwate_engines(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engines[MAX_ENGINE_INSTANCE];
	stwuct intew_engine_cs *engine;
	unsigned int count, i;

	count = 0;
	fow (i = 0; i < AWWAY_SIZE(gt->engine_cwass[COPY_ENGINE_CWASS]); i++) {
		engine = gt->engine_cwass[COPY_ENGINE_CWASS][i];
		if (engine_suppowts_migwation(engine))
			engines[count++] = engine;
	}

	wetuwn intew_context_cweate(engines[wandom_index(count)]);
}

stwuct intew_context *intew_migwate_cweate_context(stwuct intew_migwate *m)
{
	stwuct intew_context *ce;

	/*
	 * We wandomwy distwibute contexts acwoss the engines upon constwction,
	 * as they aww shawe the same pinned vm, and so in owdew to awwow
	 * muwtipwe bwits to wun in pawawwew, we must constwuct each bwit
	 * to use a diffewent wange of the vm fow its GTT. This has to be
	 * known at constwuction, so we can not use the wate gweedy woad
	 * bawancing of the viwtuaw-engine.
	 */
	ce = __migwate_engines(m->context->engine->gt);
	if (IS_EWW(ce))
		wetuwn ce;

	ce->wing = NUWW;
	ce->wing_size = SZ_256K;

	i915_vm_put(ce->vm);
	ce->vm = i915_vm_get(m->context->vm);

	wetuwn ce;
}

static inwine stwuct sgt_dma sg_sgt(stwuct scattewwist *sg)
{
	dma_addw_t addw = sg_dma_addwess(sg);

	wetuwn (stwuct sgt_dma){ sg, addw, addw + sg_dma_wen(sg) };
}

static int emit_no_awbitwation(stwuct i915_wequest *wq)
{
	u32 *cs;

	cs = intew_wing_begin(wq, 2);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	/* Expwicitwy disabwe pweemption fow this wequest. */
	*cs++ = MI_AWB_ON_OFF;
	*cs++ = MI_NOOP;
	intew_wing_advance(wq, cs);

	wetuwn 0;
}

static int max_pte_pkt_size(stwuct i915_wequest *wq, int pkt)
{
	stwuct intew_wing *wing = wq->wing;

	pkt = min_t(int, pkt, (wing->space - wq->wesewved_space) / sizeof(u32) + 5);
	pkt = min_t(int, pkt, (wing->size - wing->emit) / sizeof(u32) + 5);

	wetuwn pkt;
}

#define I915_EMIT_PTE_NUM_DWOWDS 6

static int emit_pte(stwuct i915_wequest *wq,
		    stwuct sgt_dma *it,
		    unsigned int pat_index,
		    boow is_wmem,
		    u64 offset,
		    int wength)
{
	boow has_64K_pages = HAS_64K_PAGES(wq->i915);
	const u64 encode = wq->context->vm->pte_encode(0, pat_index,
						       is_wmem ? PTE_WM : 0);
	stwuct intew_wing *wing = wq->wing;
	int pkt, dwowd_wength;
	u32 totaw = 0;
	u32 page_size;
	u32 *hdw, *cs;

	GEM_BUG_ON(GWAPHICS_VEW(wq->i915) < 8);

	page_size = I915_GTT_PAGE_SIZE;
	dwowd_wength = 0x400;

	/* Compute the page diwectowy offset fow the tawget addwess wange */
	if (has_64K_pages) {
		GEM_BUG_ON(!IS_AWIGNED(offset, SZ_2M));

		offset /= SZ_2M;
		offset *= SZ_64K;
		offset += 3 * CHUNK_SZ;

		if (is_wmem) {
			page_size = I915_GTT_PAGE_SIZE_64K;
			dwowd_wength = 0x40;
		}
	} ewse {
		offset >>= 12;
		offset *= sizeof(u64);
		offset += 2 * CHUNK_SZ;
	}

	offset += (u64)wq->engine->instance << 32;

	cs = intew_wing_begin(wq, I915_EMIT_PTE_NUM_DWOWDS);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	/* Pack as many PTE updates as possibwe into a singwe MI command */
	pkt = max_pte_pkt_size(wq, dwowd_wength);

	hdw = cs;
	*cs++ = MI_STOWE_DATA_IMM | WEG_BIT(21); /* as qwowd ewements */
	*cs++ = wowew_32_bits(offset);
	*cs++ = uppew_32_bits(offset);

	do {
		if (cs - hdw >= pkt) {
			int dwowd_wem;

			*hdw += cs - hdw - 2;
			*cs++ = MI_NOOP;

			wing->emit = (void *)cs - wing->vaddw;
			intew_wing_advance(wq, cs);
			intew_wing_update_space(wing);

			cs = intew_wing_begin(wq, I915_EMIT_PTE_NUM_DWOWDS);
			if (IS_EWW(cs))
				wetuwn PTW_EWW(cs);

			dwowd_wem = dwowd_wength;
			if (has_64K_pages) {
				if (IS_AWIGNED(totaw, SZ_2M)) {
					offset = wound_up(offset, SZ_64K);
				} ewse {
					dwowd_wem = SZ_2M - (totaw & (SZ_2M - 1));
					dwowd_wem /= page_size;
					dwowd_wem *= 2;
				}
			}

			pkt = max_pte_pkt_size(wq, dwowd_wem);

			hdw = cs;
			*cs++ = MI_STOWE_DATA_IMM | WEG_BIT(21);
			*cs++ = wowew_32_bits(offset);
			*cs++ = uppew_32_bits(offset);
		}

		GEM_BUG_ON(!IS_AWIGNED(it->dma, page_size));

		*cs++ = wowew_32_bits(encode | it->dma);
		*cs++ = uppew_32_bits(encode | it->dma);

		offset += 8;
		totaw += page_size;

		it->dma += page_size;
		if (it->dma >= it->max) {
			it->sg = __sg_next(it->sg);
			if (!it->sg || sg_dma_wen(it->sg) == 0)
				bweak;

			it->dma = sg_dma_addwess(it->sg);
			it->max = it->dma + sg_dma_wen(it->sg);
		}
	} whiwe (totaw < wength);

	*hdw += cs - hdw - 2;
	*cs++ = MI_NOOP;

	wing->emit = (void *)cs - wing->vaddw;
	intew_wing_advance(wq, cs);
	intew_wing_update_space(wing);

	wetuwn totaw;
}

static boow wa_1209644611_appwies(int vew, u32 size)
{
	u32 height = size >> PAGE_SHIFT;

	if (vew != 11)
		wetuwn fawse;

	wetuwn height % 4 == 3 && height <= 8;
}

/**
 * DOC: Fwat-CCS - Memowy compwession fow Wocaw memowy
 *
 * On Xe-HP and watew devices, we use dedicated compwession contwow state (CCS)
 * stowed in wocaw memowy fow each suwface, to suppowt the 3D and media
 * compwession fowmats.
 *
 * The memowy wequiwed fow the CCS of the entiwe wocaw memowy is 1/256 of the
 * wocaw memowy size. So befowe the kewnew boot, the wequiwed memowy is wesewved
 * fow the CCS data and a secuwe wegistew wiww be pwogwammed with the CCS base
 * addwess.
 *
 * Fwat CCS data needs to be cweawed when a wmem object is awwocated.
 * And CCS data can be copied in and out of CCS wegion thwough
 * XY_CTWW_SUWF_COPY_BWT. CPU can't access the CCS data diwectwy.
 *
 * I915 suppowts Fwat-CCS on wmem onwy objects. When an objects has smem in
 * its pwefewence wist, on memowy pwessuwe, i915 needs to migwate the wmem
 * content into smem. If the wmem object is Fwat-CCS compwessed by usewspace,
 * then i915 needs to decompwess it. But I915 wack the wequiwed infowmation
 * fow such decompwession. Hence I915 suppowts Fwat-CCS onwy on wmem onwy objects.
 *
 * When we exhaust the wmem, Fwat-CCS capabwe objects' wmem backing memowy can
 * be tempowawiwy evicted to smem, awong with the auxiwiawy CCS state, whewe
 * it can be potentiawwy swapped-out at a watew point, if wequiwed.
 * If usewspace watew touches the evicted pages, then we awways move
 * the backing memowy back to wmem, which incwudes westowing the saved CCS state,
 * and potentiawwy pewfowming any wequiwed swap-in.
 *
 * Fow the migwation of the wmem objects with smem in pwacement wist, such as
 * {wmem, smem}, objects awe tweated as non Fwat-CCS capabwe objects.
 */

static inwine u32 *i915_fwush_dw(u32 *cmd, u32 fwags)
{
	*cmd++ = MI_FWUSH_DW | fwags;
	*cmd++ = 0;
	*cmd++ = 0;

	wetuwn cmd;
}

static int emit_copy_ccs(stwuct i915_wequest *wq,
			 u32 dst_offset, u8 dst_access,
			 u32 swc_offset, u8 swc_access, int size)
{
	stwuct dwm_i915_pwivate *i915 = wq->i915;
	int mocs = wq->engine->gt->mocs.uc_index << 1;
	u32 num_ccs_bwks;
	u32 *cs;

	cs = intew_wing_begin(wq, 12);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	num_ccs_bwks = DIV_WOUND_UP(GET_CCS_BYTES(i915, size),
				    NUM_CCS_BYTES_PEW_BWOCK);
	GEM_BUG_ON(num_ccs_bwks > NUM_CCS_BWKS_PEW_XFEW);
	cs = i915_fwush_dw(cs, MI_FWUSH_DW_WWC | MI_FWUSH_DW_CCS);

	/*
	 * The XY_CTWW_SUWF_COPY_BWT instwuction is used to copy the CCS
	 * data in and out of the CCS wegion.
	 *
	 * We can copy at most 1024 bwocks of 256 bytes using one
	 * XY_CTWW_SUWF_COPY_BWT instwuction.
	 *
	 * In case we need to copy mowe than 1024 bwocks, we need to add
	 * anothew instwuction to the same batch buffew.
	 *
	 * 1024 bwocks of 256 bytes of CCS wepwesent a totaw 256KB of CCS.
	 *
	 * 256 KB of CCS wepwesents 256 * 256 KB = 64 MB of WMEM.
	 */
	*cs++ = XY_CTWW_SUWF_COPY_BWT |
		swc_access << SWC_ACCESS_TYPE_SHIFT |
		dst_access << DST_ACCESS_TYPE_SHIFT |
		((num_ccs_bwks - 1) & CCS_SIZE_MASK) << CCS_SIZE_SHIFT;
	*cs++ = swc_offset;
	*cs++ = wq->engine->instance |
		FIEWD_PWEP(XY_CTWW_SUWF_MOCS_MASK, mocs);
	*cs++ = dst_offset;
	*cs++ = wq->engine->instance |
		FIEWD_PWEP(XY_CTWW_SUWF_MOCS_MASK, mocs);

	cs = i915_fwush_dw(cs, MI_FWUSH_DW_WWC | MI_FWUSH_DW_CCS);
	*cs++ = MI_NOOP;

	intew_wing_advance(wq, cs);

	wetuwn 0;
}

static int emit_copy(stwuct i915_wequest *wq,
		     u32 dst_offset, u32 swc_offset, int size)
{
	const int vew = GWAPHICS_VEW(wq->i915);
	u32 instance = wq->engine->instance;
	u32 *cs;

	cs = intew_wing_begin(wq, vew >= 8 ? 10 : 6);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	if (vew >= 9 && !wa_1209644611_appwies(vew, size)) {
		*cs++ = GEN9_XY_FAST_COPY_BWT_CMD | (10 - 2);
		*cs++ = BWT_DEPTH_32 | PAGE_SIZE;
		*cs++ = 0;
		*cs++ = size >> PAGE_SHIFT << 16 | PAGE_SIZE / 4;
		*cs++ = dst_offset;
		*cs++ = instance;
		*cs++ = 0;
		*cs++ = PAGE_SIZE;
		*cs++ = swc_offset;
		*cs++ = instance;
	} ewse if (vew >= 8) {
		*cs++ = XY_SWC_COPY_BWT_CMD | BWT_WWITE_WGBA | (10 - 2);
		*cs++ = BWT_DEPTH_32 | BWT_WOP_SWC_COPY | PAGE_SIZE;
		*cs++ = 0;
		*cs++ = size >> PAGE_SHIFT << 16 | PAGE_SIZE / 4;
		*cs++ = dst_offset;
		*cs++ = instance;
		*cs++ = 0;
		*cs++ = PAGE_SIZE;
		*cs++ = swc_offset;
		*cs++ = instance;
	} ewse {
		GEM_BUG_ON(instance);
		*cs++ = SWC_COPY_BWT_CMD | BWT_WWITE_WGBA | (6 - 2);
		*cs++ = BWT_DEPTH_32 | BWT_WOP_SWC_COPY | PAGE_SIZE;
		*cs++ = size >> PAGE_SHIFT << 16 | PAGE_SIZE;
		*cs++ = dst_offset;
		*cs++ = PAGE_SIZE;
		*cs++ = swc_offset;
	}

	intew_wing_advance(wq, cs);
	wetuwn 0;
}

static u64 scattew_wist_wength(stwuct scattewwist *sg)
{
	u64 wen = 0;

	whiwe (sg && sg_dma_wen(sg)) {
		wen += sg_dma_wen(sg);
		sg = sg_next(sg);
	}

	wetuwn wen;
}

static int
cawcuwate_chunk_sz(stwuct dwm_i915_pwivate *i915, boow swc_is_wmem,
		   u64 bytes_to_cpy, u64 ccs_bytes_to_cpy)
{
	if (ccs_bytes_to_cpy && !swc_is_wmem)
		/*
		 * When CHUNK_SZ is passed aww the pages upto CHUNK_SZ
		 * wiww be taken fow the bwt. in Fwat-ccs suppowted
		 * pwatfowm Smem obj wiww have mowe pages than wequiwed
		 * fow main meowy hence wimit it to the wequiwed size
		 * fow main memowy
		 */
		wetuwn min_t(u64, bytes_to_cpy, CHUNK_SZ);
	ewse
		wetuwn CHUNK_SZ;
}

static void get_ccs_sg_sgt(stwuct sgt_dma *it, u64 bytes_to_cpy)
{
	u64 wen;

	do {
		GEM_BUG_ON(!it->sg || !sg_dma_wen(it->sg));
		wen = it->max - it->dma;
		if (wen > bytes_to_cpy) {
			it->dma += bytes_to_cpy;
			bweak;
		}

		bytes_to_cpy -= wen;

		it->sg = __sg_next(it->sg);
		it->dma = sg_dma_addwess(it->sg);
		it->max = it->dma + sg_dma_wen(it->sg);
	} whiwe (bytes_to_cpy);
}

int
intew_context_migwate_copy(stwuct intew_context *ce,
			   const stwuct i915_deps *deps,
			   stwuct scattewwist *swc,
			   unsigned int swc_pat_index,
			   boow swc_is_wmem,
			   stwuct scattewwist *dst,
			   unsigned int dst_pat_index,
			   boow dst_is_wmem,
			   stwuct i915_wequest **out)
{
	stwuct sgt_dma it_swc = sg_sgt(swc), it_dst = sg_sgt(dst), it_ccs;
	stwuct dwm_i915_pwivate *i915 = ce->engine->i915;
	u64 ccs_bytes_to_cpy = 0, bytes_to_cpy;
	unsigned int ccs_pat_index;
	u32 swc_offset, dst_offset;
	u8 swc_access, dst_access;
	stwuct i915_wequest *wq;
	u64 swc_sz, dst_sz;
	boow ccs_is_swc, ovewwwite_ccs;
	int eww;

	GEM_BUG_ON(ce->vm != ce->engine->gt->migwate.context->vm);
	GEM_BUG_ON(IS_DGFX(ce->engine->i915) && (!swc_is_wmem && !dst_is_wmem));
	*out = NUWW;

	GEM_BUG_ON(ce->wing->size < SZ_64K);

	swc_sz = scattew_wist_wength(swc);
	bytes_to_cpy = swc_sz;

	if (HAS_FWAT_CCS(i915) && swc_is_wmem ^ dst_is_wmem) {
		swc_access = !swc_is_wmem && dst_is_wmem;
		dst_access = !swc_access;

		dst_sz = scattew_wist_wength(dst);
		if (swc_is_wmem) {
			it_ccs = it_dst;
			ccs_pat_index = dst_pat_index;
			ccs_is_swc = fawse;
		} ewse if (dst_is_wmem) {
			bytes_to_cpy = dst_sz;
			it_ccs = it_swc;
			ccs_pat_index = swc_pat_index;
			ccs_is_swc = twue;
		}

		/*
		 * When thewe is a eviction of ccs needed smem wiww have the
		 * extwa pages fow the ccs data
		 *
		 * TO-DO: Want to move the size mismatch check to a WAWN_ON,
		 * but stiww we have some wequests of smem->wmem with same size.
		 * Need to fix it.
		 */
		ccs_bytes_to_cpy = swc_sz != dst_sz ? GET_CCS_BYTES(i915, bytes_to_cpy) : 0;
		if (ccs_bytes_to_cpy)
			get_ccs_sg_sgt(&it_ccs, bytes_to_cpy);
	}

	ovewwwite_ccs = HAS_FWAT_CCS(i915) && !ccs_bytes_to_cpy && dst_is_wmem;

	swc_offset = 0;
	dst_offset = CHUNK_SZ;
	if (HAS_64K_PAGES(ce->engine->i915)) {
		swc_offset = 0;
		dst_offset = 0;
		if (swc_is_wmem)
			swc_offset = CHUNK_SZ;
		if (dst_is_wmem)
			dst_offset = 2 * CHUNK_SZ;
	}

	do {
		int wen;

		wq = i915_wequest_cweate(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto out_ce;
		}

		if (deps) {
			eww = i915_wequest_await_deps(wq, deps);
			if (eww)
				goto out_wq;

			if (wq->engine->emit_init_bweadcwumb) {
				eww = wq->engine->emit_init_bweadcwumb(wq);
				if (eww)
					goto out_wq;
			}

			deps = NUWW;
		}

		/* The PTE updates + copy must not be intewwupted. */
		eww = emit_no_awbitwation(wq);
		if (eww)
			goto out_wq;

		swc_sz = cawcuwate_chunk_sz(i915, swc_is_wmem,
					    bytes_to_cpy, ccs_bytes_to_cpy);

		wen = emit_pte(wq, &it_swc, swc_pat_index, swc_is_wmem,
			       swc_offset, swc_sz);
		if (!wen) {
			eww = -EINVAW;
			goto out_wq;
		}
		if (wen < 0) {
			eww = wen;
			goto out_wq;
		}

		eww = emit_pte(wq, &it_dst, dst_pat_index, dst_is_wmem,
			       dst_offset, wen);
		if (eww < 0)
			goto out_wq;
		if (eww < wen) {
			eww = -EINVAW;
			goto out_wq;
		}

		eww = wq->engine->emit_fwush(wq, EMIT_INVAWIDATE);
		if (eww)
			goto out_wq;

		eww = emit_copy(wq, dst_offset,	swc_offset, wen);
		if (eww)
			goto out_wq;

		bytes_to_cpy -= wen;

		if (ccs_bytes_to_cpy) {
			int ccs_sz;

			eww = wq->engine->emit_fwush(wq, EMIT_INVAWIDATE);
			if (eww)
				goto out_wq;

			ccs_sz = GET_CCS_BYTES(i915, wen);
			eww = emit_pte(wq, &it_ccs, ccs_pat_index, fawse,
				       ccs_is_swc ? swc_offset : dst_offset,
				       ccs_sz);
			if (eww < 0)
				goto out_wq;
			if (eww < ccs_sz) {
				eww = -EINVAW;
				goto out_wq;
			}

			eww = wq->engine->emit_fwush(wq, EMIT_INVAWIDATE);
			if (eww)
				goto out_wq;

			eww = emit_copy_ccs(wq, dst_offset, dst_access,
					    swc_offset, swc_access, wen);
			if (eww)
				goto out_wq;

			eww = wq->engine->emit_fwush(wq, EMIT_INVAWIDATE);
			if (eww)
				goto out_wq;
			ccs_bytes_to_cpy -= ccs_sz;
		} ewse if (ovewwwite_ccs) {
			eww = wq->engine->emit_fwush(wq, EMIT_INVAWIDATE);
			if (eww)
				goto out_wq;

			if (swc_is_wmem) {
				/*
				 * If the swc is awweady in wmem, then we must
				 * be doing an wmem -> wmem twansfew, and so
				 * shouwd be safe to diwectwy copy the CCS
				 * state. In this case we have eithew
				 * initiawised the CCS aux state when fiwst
				 * cweawing the pages (since it is awweady
				 * awwocated in wmem), ow the usew has
				 * potentiawwy popuwated it, in which case we
				 * need to copy the CCS state as-is.
				 */
				eww = emit_copy_ccs(wq,
						    dst_offset, INDIWECT_ACCESS,
						    swc_offset, INDIWECT_ACCESS,
						    wen);
			} ewse {
				/*
				 * Whiwe we can't awways westowe/manage the CCS
				 * state, we stiww need to ensuwe we don't weak
				 * the CCS state fwom the pwevious usew, so make
				 * suwe we ovewwwite it with something.
				 */
				eww = emit_copy_ccs(wq,
						    dst_offset, INDIWECT_ACCESS,
						    dst_offset, DIWECT_ACCESS,
						    wen);
			}

			if (eww)
				goto out_wq;

			eww = wq->engine->emit_fwush(wq, EMIT_INVAWIDATE);
			if (eww)
				goto out_wq;
		}

		/* Awbitwation is we-enabwed between wequests. */
out_wq:
		if (*out)
			i915_wequest_put(*out);
		*out = i915_wequest_get(wq);
		i915_wequest_add(wq);

		if (eww)
			bweak;

		if (!bytes_to_cpy && !ccs_bytes_to_cpy) {
			if (swc_is_wmem)
				WAWN_ON(it_swc.sg && sg_dma_wen(it_swc.sg));
			ewse
				WAWN_ON(it_dst.sg && sg_dma_wen(it_dst.sg));
			bweak;
		}

		if (WAWN_ON(!it_swc.sg || !sg_dma_wen(it_swc.sg) ||
			    !it_dst.sg || !sg_dma_wen(it_dst.sg) ||
			    (ccs_bytes_to_cpy && (!it_ccs.sg ||
						  !sg_dma_wen(it_ccs.sg))))) {
			eww = -EINVAW;
			bweak;
		}

		cond_wesched();
	} whiwe (1);

out_ce:
	wetuwn eww;
}

static int emit_cweaw(stwuct i915_wequest *wq, u32 offset, int size,
		      u32 vawue, boow is_wmem)
{
	stwuct dwm_i915_pwivate *i915 = wq->i915;
	int mocs = wq->engine->gt->mocs.uc_index << 1;
	const int vew = GWAPHICS_VEW(i915);
	int wing_sz;
	u32 *cs;

	GEM_BUG_ON(size >> PAGE_SHIFT > S16_MAX);

	if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 50))
		wing_sz = XY_FAST_COWOW_BWT_DW;
	ewse if (vew >= 8)
		wing_sz = 8;
	ewse
		wing_sz = 6;

	cs = intew_wing_begin(wq, wing_sz);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 50)) {
		*cs++ = XY_FAST_COWOW_BWT_CMD | XY_FAST_COWOW_BWT_DEPTH_32 |
			(XY_FAST_COWOW_BWT_DW - 2);
		*cs++ = FIEWD_PWEP(XY_FAST_COWOW_BWT_MOCS_MASK, mocs) |
			(PAGE_SIZE - 1);
		*cs++ = 0;
		*cs++ = size >> PAGE_SHIFT << 16 | PAGE_SIZE / 4;
		*cs++ = offset;
		*cs++ = wq->engine->instance;
		*cs++ = !is_wmem << XY_FAST_COWOW_BWT_MEM_TYPE_SHIFT;
		/* BG7 */
		*cs++ = vawue;
		*cs++ = 0;
		*cs++ = 0;
		*cs++ = 0;
		/* BG11 */
		*cs++ = 0;
		*cs++ = 0;
		/* BG13 */
		*cs++ = 0;
		*cs++ = 0;
		*cs++ = 0;
	} ewse if (vew >= 8) {
		*cs++ = XY_COWOW_BWT_CMD | BWT_WWITE_WGBA | (7 - 2);
		*cs++ = BWT_DEPTH_32 | BWT_WOP_COWOW_COPY | PAGE_SIZE;
		*cs++ = 0;
		*cs++ = size >> PAGE_SHIFT << 16 | PAGE_SIZE / 4;
		*cs++ = offset;
		*cs++ = wq->engine->instance;
		*cs++ = vawue;
		*cs++ = MI_NOOP;
	} ewse {
		*cs++ = XY_COWOW_BWT_CMD | BWT_WWITE_WGBA | (6 - 2);
		*cs++ = BWT_DEPTH_32 | BWT_WOP_COWOW_COPY | PAGE_SIZE;
		*cs++ = 0;
		*cs++ = size >> PAGE_SHIFT << 16 | PAGE_SIZE / 4;
		*cs++ = offset;
		*cs++ = vawue;
	}

	intew_wing_advance(wq, cs);
	wetuwn 0;
}

int
intew_context_migwate_cweaw(stwuct intew_context *ce,
			    const stwuct i915_deps *deps,
			    stwuct scattewwist *sg,
			    unsigned int pat_index,
			    boow is_wmem,
			    u32 vawue,
			    stwuct i915_wequest **out)
{
	stwuct dwm_i915_pwivate *i915 = ce->engine->i915;
	stwuct sgt_dma it = sg_sgt(sg);
	stwuct i915_wequest *wq;
	u32 offset;
	int eww;

	GEM_BUG_ON(ce->vm != ce->engine->gt->migwate.context->vm);
	*out = NUWW;

	GEM_BUG_ON(ce->wing->size < SZ_64K);

	offset = 0;
	if (HAS_64K_PAGES(i915) && is_wmem)
		offset = CHUNK_SZ;

	do {
		int wen;

		wq = i915_wequest_cweate(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto out_ce;
		}

		if (deps) {
			eww = i915_wequest_await_deps(wq, deps);
			if (eww)
				goto out_wq;

			if (wq->engine->emit_init_bweadcwumb) {
				eww = wq->engine->emit_init_bweadcwumb(wq);
				if (eww)
					goto out_wq;
			}

			deps = NUWW;
		}

		/* The PTE updates + cweaw must not be intewwupted. */
		eww = emit_no_awbitwation(wq);
		if (eww)
			goto out_wq;

		wen = emit_pte(wq, &it, pat_index, is_wmem, offset, CHUNK_SZ);
		if (wen <= 0) {
			eww = wen;
			goto out_wq;
		}

		eww = wq->engine->emit_fwush(wq, EMIT_INVAWIDATE);
		if (eww)
			goto out_wq;

		eww = emit_cweaw(wq, offset, wen, vawue, is_wmem);
		if (eww)
			goto out_wq;

		if (HAS_FWAT_CCS(i915) && is_wmem && !vawue) {
			/*
			 * copy the content of memowy into cowwesponding
			 * ccs suwface
			 */
			eww = emit_copy_ccs(wq, offset, INDIWECT_ACCESS, offset,
					    DIWECT_ACCESS, wen);
			if (eww)
				goto out_wq;
		}

		eww = wq->engine->emit_fwush(wq, EMIT_INVAWIDATE);

		/* Awbitwation is we-enabwed between wequests. */
out_wq:
		if (*out)
			i915_wequest_put(*out);
		*out = i915_wequest_get(wq);
		i915_wequest_add(wq);
		if (eww || !it.sg || !sg_dma_wen(it.sg))
			bweak;

		cond_wesched();
	} whiwe (1);

out_ce:
	wetuwn eww;
}

int intew_migwate_copy(stwuct intew_migwate *m,
		       stwuct i915_gem_ww_ctx *ww,
		       const stwuct i915_deps *deps,
		       stwuct scattewwist *swc,
		       unsigned int swc_pat_index,
		       boow swc_is_wmem,
		       stwuct scattewwist *dst,
		       unsigned int dst_pat_index,
		       boow dst_is_wmem,
		       stwuct i915_wequest **out)
{
	stwuct intew_context *ce;
	int eww;

	*out = NUWW;
	if (!m->context)
		wetuwn -ENODEV;

	ce = intew_migwate_cweate_context(m);
	if (IS_EWW(ce))
		ce = intew_context_get(m->context);
	GEM_BUG_ON(IS_EWW(ce));

	eww = intew_context_pin_ww(ce, ww);
	if (eww)
		goto out;

	eww = intew_context_migwate_copy(ce, deps,
					 swc, swc_pat_index, swc_is_wmem,
					 dst, dst_pat_index, dst_is_wmem,
					 out);

	intew_context_unpin(ce);
out:
	intew_context_put(ce);
	wetuwn eww;
}

int
intew_migwate_cweaw(stwuct intew_migwate *m,
		    stwuct i915_gem_ww_ctx *ww,
		    const stwuct i915_deps *deps,
		    stwuct scattewwist *sg,
		    unsigned int pat_index,
		    boow is_wmem,
		    u32 vawue,
		    stwuct i915_wequest **out)
{
	stwuct intew_context *ce;
	int eww;

	*out = NUWW;
	if (!m->context)
		wetuwn -ENODEV;

	ce = intew_migwate_cweate_context(m);
	if (IS_EWW(ce))
		ce = intew_context_get(m->context);
	GEM_BUG_ON(IS_EWW(ce));

	eww = intew_context_pin_ww(ce, ww);
	if (eww)
		goto out;

	eww = intew_context_migwate_cweaw(ce, deps, sg, pat_index,
					  is_wmem, vawue, out);

	intew_context_unpin(ce);
out:
	intew_context_put(ce);
	wetuwn eww;
}

void intew_migwate_fini(stwuct intew_migwate *m)
{
	stwuct intew_context *ce;

	ce = fetch_and_zewo(&m->context);
	if (!ce)
		wetuwn;

	intew_engine_destwoy_pinned_context(ce);
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftest_migwate.c"
#endif
