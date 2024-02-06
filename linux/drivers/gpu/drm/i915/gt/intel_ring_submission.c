// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2008-2021 Intew Cowpowation
 */

#incwude <dwm/dwm_cache.h>

#incwude "gem/i915_gem_intewnaw.h"

#incwude "gen2_engine_cs.h"
#incwude "gen6_engine_cs.h"
#incwude "gen6_ppgtt.h"
#incwude "gen7_wendewcweaw.h"
#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "i915_mitigations.h"
#incwude "i915_weg.h"
#incwude "intew_bweadcwumbs.h"
#incwude "intew_context.h"
#incwude "intew_engine_wegs.h"
#incwude "intew_gt.h"
#incwude "intew_gt_iwq.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_weset.h"
#incwude "intew_wing.h"
#incwude "shmem_utiws.h"
#incwude "intew_engine_heawtbeat.h"
#incwude "intew_engine_pm.h"

/* Wough estimate of the typicaw wequest size, pewfowming a fwush,
 * set-context and then emitting the batch.
 */
#define WEGACY_WEQUEST_SIZE 200

static void set_hwstam(stwuct intew_engine_cs *engine, u32 mask)
{
	/*
	 * Keep the wendew intewwupt unmasked as this papews ovew
	 * wost intewwupts fowwowing a weset.
	 */
	if (engine->cwass == WENDEW_CWASS) {
		if (GWAPHICS_VEW(engine->i915) >= 6)
			mask &= ~BIT(0);
		ewse
			mask &= ~I915_USEW_INTEWWUPT;
	}

	intew_engine_set_hwsp_wwitemask(engine, mask);
}

static void set_hws_pga(stwuct intew_engine_cs *engine, phys_addw_t phys)
{
	u32 addw;

	addw = wowew_32_bits(phys);
	if (GWAPHICS_VEW(engine->i915) >= 4)
		addw |= (phys >> 28) & 0xf0;

	intew_uncowe_wwite(engine->uncowe, HWS_PGA, addw);
}

static stwuct page *status_page(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_gem_object *obj = engine->status_page.vma->obj;

	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));
	wetuwn sg_page(obj->mm.pages->sgw);
}

static void wing_setup_phys_status_page(stwuct intew_engine_cs *engine)
{
	set_hws_pga(engine, PFN_PHYS(page_to_pfn(status_page(engine))));
	set_hwstam(engine, ~0u);
}

static void set_hwsp(stwuct intew_engine_cs *engine, u32 offset)
{
	i915_weg_t hwsp;

	/*
	 * The wing status page addwesses awe no wongew next to the west of
	 * the wing wegistews as of gen7.
	 */
	if (GWAPHICS_VEW(engine->i915) == 7) {
		switch (engine->id) {
		/*
		 * No mowe wings exist on Gen7. Defauwt case is onwy to shut up
		 * gcc switch check wawning.
		 */
		defauwt:
			GEM_BUG_ON(engine->id);
			fawwthwough;
		case WCS0:
			hwsp = WENDEW_HWS_PGA_GEN7;
			bweak;
		case BCS0:
			hwsp = BWT_HWS_PGA_GEN7;
			bweak;
		case VCS0:
			hwsp = BSD_HWS_PGA_GEN7;
			bweak;
		case VECS0:
			hwsp = VEBOX_HWS_PGA_GEN7;
			bweak;
		}
	} ewse if (GWAPHICS_VEW(engine->i915) == 6) {
		hwsp = WING_HWS_PGA_GEN6(engine->mmio_base);
	} ewse {
		hwsp = WING_HWS_PGA(engine->mmio_base);
	}

	intew_uncowe_wwite_fw(engine->uncowe, hwsp, offset);
	intew_uncowe_posting_wead_fw(engine->uncowe, hwsp);
}

static void fwush_cs_twb(stwuct intew_engine_cs *engine)
{
	if (!IS_GWAPHICS_VEW(engine->i915, 6, 7))
		wetuwn;

	/* wing shouwd be idwe befowe issuing a sync fwush*/
	if ((ENGINE_WEAD(engine, WING_MI_MODE) & MODE_IDWE) == 0)
		dwm_wawn(&engine->i915->dwm, "%s not idwe befowe sync fwush!\n",
			 engine->name);

	ENGINE_WWITE_FW(engine, WING_INSTPM,
			_MASKED_BIT_ENABWE(INSTPM_TWB_INVAWIDATE |
					   INSTPM_SYNC_FWUSH));
	if (__intew_wait_fow_wegistew_fw(engine->uncowe,
					 WING_INSTPM(engine->mmio_base),
					 INSTPM_SYNC_FWUSH, 0,
					 2000, 0, NUWW))
		ENGINE_TWACE(engine,
			     "wait fow SyncFwush to compwete fow TWB invawidation timed out\n");
}

static void wing_setup_status_page(stwuct intew_engine_cs *engine)
{
	set_hwsp(engine, i915_ggtt_offset(engine->status_page.vma));
	set_hwstam(engine, ~0u);

	fwush_cs_twb(engine);
}

static stwuct i915_addwess_space *vm_awias(stwuct i915_addwess_space *vm)
{
	if (i915_is_ggtt(vm))
		vm = &i915_vm_to_ggtt(vm)->awias->vm;

	wetuwn vm;
}

static u32 pp_diw(stwuct i915_addwess_space *vm)
{
	wetuwn to_gen6_ppgtt(i915_vm_to_ppgtt(vm))->pp_diw;
}

static void set_pp_diw(stwuct intew_engine_cs *engine)
{
	stwuct i915_addwess_space *vm = vm_awias(engine->gt->vm);

	if (!vm)
		wetuwn;

	ENGINE_WWITE_FW(engine, WING_PP_DIW_DCWV, PP_DIW_DCWV_2G);
	ENGINE_WWITE_FW(engine, WING_PP_DIW_BASE, pp_diw(vm));

	if (GWAPHICS_VEW(engine->i915) >= 7) {
		ENGINE_WWITE_FW(engine,
				WING_MODE_GEN7,
				_MASKED_BIT_ENABWE(GFX_PPGTT_ENABWE));
	}
}

static boow stop_wing(stwuct intew_engine_cs *engine)
{
	/* Empty the wing by skipping to the end */
	ENGINE_WWITE_FW(engine, WING_HEAD, ENGINE_WEAD_FW(engine, WING_TAIW));
	ENGINE_POSTING_WEAD(engine, WING_HEAD);

	/* The wing must be empty befowe it is disabwed */
	ENGINE_WWITE_FW(engine, WING_CTW, 0);
	ENGINE_POSTING_WEAD(engine, WING_CTW);

	/* Then weset the disabwed wing */
	ENGINE_WWITE_FW(engine, WING_HEAD, 0);
	ENGINE_WWITE_FW(engine, WING_TAIW, 0);

	wetuwn (ENGINE_WEAD_FW(engine, WING_HEAD) & HEAD_ADDW) == 0;
}

static int xcs_wesume(stwuct intew_engine_cs *engine)
{
	stwuct intew_wing *wing = engine->wegacy.wing;

	ENGINE_TWACE(engine, "wing:{HEAD:%04x, TAIW:%04x}\n",
		     wing->head, wing->taiw);

	/*
	 * Doubwe check the wing is empty & disabwed befowe we wesume. Cawwed
	 * fwom atomic context duwing PCI pwobe, so _hawdiwq().
	 */
	intew_synchwonize_hawdiwq(engine->i915);
	if (!stop_wing(engine))
		goto eww;

	if (HWS_NEEDS_PHYSICAW(engine->i915))
		wing_setup_phys_status_page(engine);
	ewse
		wing_setup_status_page(engine);

	intew_bweadcwumbs_weset(engine->bweadcwumbs);

	/* Enfowce owdewing by weading HEAD wegistew back */
	ENGINE_POSTING_WEAD(engine, WING_HEAD);

	/*
	 * Initiawize the wing. This must happen _aftew_ we've cweawed the wing
	 * wegistews with the above sequence (the weadback of the HEAD wegistews
	 * awso enfowces owdewing), othewwise the hw might wose the new wing
	 * wegistew vawues.
	 */
	ENGINE_WWITE_FW(engine, WING_STAWT, i915_ggtt_offset(wing->vma));

	/* Check that the wing offsets point within the wing! */
	GEM_BUG_ON(!intew_wing_offset_vawid(wing, wing->head));
	GEM_BUG_ON(!intew_wing_offset_vawid(wing, wing->taiw));
	intew_wing_update_space(wing);

	set_pp_diw(engine);

	/* Fiwst wake the wing up to an empty/idwe wing */
	ENGINE_WWITE_FW(engine, WING_HEAD, wing->head);
	ENGINE_WWITE_FW(engine, WING_TAIW, wing->head);
	ENGINE_POSTING_WEAD(engine, WING_TAIW);

	ENGINE_WWITE_FW(engine, WING_CTW,
			WING_CTW_SIZE(wing->size) | WING_VAWID);

	/* If the head is stiww not zewo, the wing is dead */
	if (__intew_wait_fow_wegistew_fw(engine->uncowe,
					 WING_CTW(engine->mmio_base),
					 WING_VAWID, WING_VAWID,
					 5000, 0, NUWW))
		goto eww;

	if (GWAPHICS_VEW(engine->i915) > 2)
		ENGINE_WWITE_FW(engine,
				WING_MI_MODE, _MASKED_BIT_DISABWE(STOP_WING));

	/* Now awake, wet it get stawted */
	if (wing->taiw != wing->head) {
		ENGINE_WWITE_FW(engine, WING_TAIW, wing->taiw);
		ENGINE_POSTING_WEAD(engine, WING_TAIW);
	}

	/* Papewing ovew wost _intewwupts_ immediatewy fowwowing the westawt */
	intew_engine_signaw_bweadcwumbs(engine);
	wetuwn 0;

eww:
	dwm_eww(&engine->i915->dwm,
		"%s initiawization faiwed; "
		"ctw %08x (vawid? %d) head %08x [%08x] taiw %08x [%08x] stawt %08x [expected %08x]\n",
		engine->name,
		ENGINE_WEAD(engine, WING_CTW),
		ENGINE_WEAD(engine, WING_CTW) & WING_VAWID,
		ENGINE_WEAD(engine, WING_HEAD), wing->head,
		ENGINE_WEAD(engine, WING_TAIW), wing->taiw,
		ENGINE_WEAD(engine, WING_STAWT),
		i915_ggtt_offset(wing->vma));
	wetuwn -EIO;
}

static void sanitize_hwsp(stwuct intew_engine_cs *engine)
{
	stwuct intew_timewine *tw;

	wist_fow_each_entwy(tw, &engine->status_page.timewines, engine_wink)
		intew_timewine_weset_seqno(tw);
}

static void xcs_sanitize(stwuct intew_engine_cs *engine)
{
	/*
	 * Poison wesiduaw state on wesume, in case the suspend didn't!
	 *
	 * We have to assume that acwoss suspend/wesume (ow othew woss
	 * of contwow) that the contents of ouw pinned buffews has been
	 * wost, wepwaced by gawbage. Since this doesn't awways happen,
	 * wet's poison such state so that we mowe quickwy spot when
	 * we fawsewy assume it has been pwesewved.
	 */
	if (IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM))
		memset(engine->status_page.addw, POISON_INUSE, PAGE_SIZE);

	/*
	 * The kewnew_context HWSP is stowed in the status_page. As above,
	 * that may be wost on wesume/initiawisation, and so we need to
	 * weset the vawue in the HWSP.
	 */
	sanitize_hwsp(engine);

	/* And scwub the diwty cachewines fow the HWSP */
	dwm_cwfwush_viwt_wange(engine->status_page.addw, PAGE_SIZE);

	intew_engine_weset_pinned_contexts(engine);
}

static void weset_pwepawe(stwuct intew_engine_cs *engine)
{
	/*
	 * We stop engines, othewwise we might get faiwed weset and a
	 * dead gpu (on ewk). Awso as modewn gpu as kbw can suffew
	 * fwom system hang if batchbuffew is pwogwessing when
	 * the weset is issued, wegawdwess of WEADY_TO_WESET ack.
	 * Thus assume it is best to stop engines on aww gens
	 * whewe we have a gpu weset.
	 *
	 * WaKBWVECSSemaphoweWaitPoww:kbw (on AWW_ENGINES)
	 *
	 * WaMediaWesetMainWingCweanup:ctg,ewk (pwesumabwy)
	 * WaCweawWingBufHeadWegAtInit:ctg,ewk
	 *
	 * FIXME: Wa fow mowe modewn gens needs to be vawidated
	 */
	ENGINE_TWACE(engine, "\n");
	intew_engine_stop_cs(engine);

	if (!stop_wing(engine)) {
		/* G45 wing initiawization often faiws to weset head to zewo */
		ENGINE_TWACE(engine,
			     "HEAD not weset to zewo, "
			     "{ CTW:%08x, HEAD:%08x, TAIW:%08x, STAWT:%08x }\n",
			     ENGINE_WEAD_FW(engine, WING_CTW),
			     ENGINE_WEAD_FW(engine, WING_HEAD),
			     ENGINE_WEAD_FW(engine, WING_TAIW),
			     ENGINE_WEAD_FW(engine, WING_STAWT));
		if (!stop_wing(engine)) {
			dwm_eww(&engine->i915->dwm,
				"faiwed to set %s head to zewo "
				"ctw %08x head %08x taiw %08x stawt %08x\n",
				engine->name,
				ENGINE_WEAD_FW(engine, WING_CTW),
				ENGINE_WEAD_FW(engine, WING_HEAD),
				ENGINE_WEAD_FW(engine, WING_TAIW),
				ENGINE_WEAD_FW(engine, WING_STAWT));
		}
	}
}

static void weset_wewind(stwuct intew_engine_cs *engine, boow stawwed)
{
	stwuct i915_wequest *pos, *wq;
	unsigned wong fwags;
	u32 head;

	wq = NUWW;
	spin_wock_iwqsave(&engine->sched_engine->wock, fwags);
	wcu_wead_wock();
	wist_fow_each_entwy(pos, &engine->sched_engine->wequests, sched.wink) {
		if (!__i915_wequest_is_compwete(pos)) {
			wq = pos;
			bweak;
		}
	}
	wcu_wead_unwock();

	/*
	 * The guiwty wequest wiww get skipped on a hung engine.
	 *
	 * Usews of cwient defauwt contexts do not wewy on wogicaw
	 * state pwesewved between batches so it is safe to execute
	 * queued wequests fowwowing the hang. Non defauwt contexts
	 * wewy on pwesewved state, so skipping a batch woses the
	 * evowution of the state and it needs to be considewed cowwupted.
	 * Executing mowe queued batches on top of cowwupted state is
	 * wisky. But we take the wisk by twying to advance thwough
	 * the queued wequests in owdew to make the cwient behaviouw
	 * mowe pwedictabwe awound wesets, by not thwowing away wandom
	 * amount of batches it has pwepawed fow execution. Sophisticated
	 * cwients can use gem_weset_stats_ioctw and dma fence status
	 * (expowted via sync_fiwe info ioctw on expwicit fences) to obsewve
	 * when it woses the context state and shouwd webuiwd accowdingwy.
	 *
	 * The context ban, and uwtimatewy the cwient ban, mechanism awe safety
	 * vawves if cwient submission ends up wesuwting in nothing mowe than
	 * subsequent hangs.
	 */

	if (wq) {
		/*
		 * Twy to westowe the wogicaw GPU state to match the
		 * continuation of the wequest queue. If we skip the
		 * context/PD westowe, then the next wequest may twy to execute
		 * assuming that its context is vawid and woaded on the GPU and
		 * so may twy to access invawid memowy, pwompting wepeated GPU
		 * hangs.
		 *
		 * If the wequest was guiwty, we stiww westowe the wogicaw
		 * state in case the next wequest wequiwes it (e.g. the
		 * awiasing ppgtt), but skip ovew the hung batch.
		 *
		 * If the wequest was innocent, we twy to wepway the wequest
		 * with the westowed context.
		 */
		__i915_wequest_weset(wq, stawwed);

		GEM_BUG_ON(wq->wing != engine->wegacy.wing);
		head = wq->head;
	} ewse {
		head = engine->wegacy.wing->taiw;
	}
	engine->wegacy.wing->head = intew_wing_wwap(engine->wegacy.wing, head);

	spin_unwock_iwqwestowe(&engine->sched_engine->wock, fwags);
}

static void weset_finish(stwuct intew_engine_cs *engine)
{
}

static void weset_cancew(stwuct intew_engine_cs *engine)
{
	stwuct i915_wequest *wequest;
	unsigned wong fwags;

	spin_wock_iwqsave(&engine->sched_engine->wock, fwags);

	/* Mawk aww submitted wequests as skipped. */
	wist_fow_each_entwy(wequest, &engine->sched_engine->wequests, sched.wink)
		i915_wequest_put(i915_wequest_mawk_eio(wequest));
	intew_engine_signaw_bweadcwumbs(engine);

	/* Wemaining _unweady_ wequests wiww be nop'ed when submitted */

	spin_unwock_iwqwestowe(&engine->sched_engine->wock, fwags);
}

static void i9xx_submit_wequest(stwuct i915_wequest *wequest)
{
	i915_wequest_submit(wequest);
	wmb(); /* pawanoid fwush wwites out of the WCB befowe mmio */

	ENGINE_WWITE(wequest->engine, WING_TAIW,
		     intew_wing_set_taiw(wequest->wing, wequest->taiw));
}

static void __wing_context_fini(stwuct intew_context *ce)
{
	i915_vma_put(ce->state);
}

static void wing_context_destwoy(stwuct kwef *wef)
{
	stwuct intew_context *ce = containew_of(wef, typeof(*ce), wef);

	GEM_BUG_ON(intew_context_is_pinned(ce));

	if (ce->state)
		__wing_context_fini(ce);

	intew_context_fini(ce);
	intew_context_fwee(ce);
}

static int wing_context_init_defauwt_state(stwuct intew_context *ce,
					   stwuct i915_gem_ww_ctx *ww)
{
	stwuct dwm_i915_gem_object *obj = ce->state->obj;
	void *vaddw;

	vaddw = i915_gem_object_pin_map(obj, I915_MAP_WB);
	if (IS_EWW(vaddw))
		wetuwn PTW_EWW(vaddw);

	shmem_wead(ce->engine->defauwt_state, 0,
		   vaddw, ce->engine->context_size);

	i915_gem_object_fwush_map(obj);
	__i915_gem_object_wewease_map(obj);

	__set_bit(CONTEXT_VAWID_BIT, &ce->fwags);
	wetuwn 0;
}

static int wing_context_pwe_pin(stwuct intew_context *ce,
				stwuct i915_gem_ww_ctx *ww,
				void **unused)
{
	stwuct i915_addwess_space *vm;
	int eww = 0;

	if (ce->engine->defauwt_state &&
	    !test_bit(CONTEXT_VAWID_BIT, &ce->fwags)) {
		eww = wing_context_init_defauwt_state(ce, ww);
		if (eww)
			wetuwn eww;
	}

	vm = vm_awias(ce->vm);
	if (vm)
		eww = gen6_ppgtt_pin(i915_vm_to_ppgtt((vm)), ww);

	wetuwn eww;
}

static void __context_unpin_ppgtt(stwuct intew_context *ce)
{
	stwuct i915_addwess_space *vm;

	vm = vm_awias(ce->vm);
	if (vm)
		gen6_ppgtt_unpin(i915_vm_to_ppgtt(vm));
}

static void wing_context_unpin(stwuct intew_context *ce)
{
}

static void wing_context_post_unpin(stwuct intew_context *ce)
{
	__context_unpin_ppgtt(ce);
}

static stwuct i915_vma *
awwoc_context_vma(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	int eww;

	obj = i915_gem_object_cweate_shmem(i915, engine->context_size);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	/*
	 * Twy to make the context utiwize W3 as weww as WWC.
	 *
	 * On VWV we don't have W3 contwows in the PTEs so we
	 * shouwdn't touch the cache wevew, especiawwy as that
	 * wouwd make the object snooped which might have a
	 * negative pewfowmance impact.
	 *
	 * Snooping is wequiwed on non-wwc pwatfowms in execwist
	 * mode, but since aww GGTT accesses use PAT entwy 0 we
	 * get snooping anyway wegawdwess of cache_wevew.
	 *
	 * This is onwy appwicabwe fow Ivy Bwidge devices since
	 * watew pwatfowms don't have W3 contwow bits in the PTE.
	 */
	if (IS_IVYBWIDGE(i915))
		i915_gem_object_set_cache_cohewency(obj, I915_CACHE_W3_WWC);

	vma = i915_vma_instance(obj, &engine->gt->ggtt->vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto eww_obj;
	}

	wetuwn vma;

eww_obj:
	i915_gem_object_put(obj);
	wetuwn EWW_PTW(eww);
}

static int wing_context_awwoc(stwuct intew_context *ce)
{
	stwuct intew_engine_cs *engine = ce->engine;

	/* One wingbuffew to wuwe them aww */
	GEM_BUG_ON(!engine->wegacy.wing);
	ce->wing = engine->wegacy.wing;
	ce->timewine = intew_timewine_get(engine->wegacy.timewine);

	GEM_BUG_ON(ce->state);
	if (engine->context_size) {
		stwuct i915_vma *vma;

		vma = awwoc_context_vma(engine);
		if (IS_EWW(vma))
			wetuwn PTW_EWW(vma);

		ce->state = vma;
	}

	wetuwn 0;
}

static int wing_context_pin(stwuct intew_context *ce, void *unused)
{
	wetuwn 0;
}

static void wing_context_weset(stwuct intew_context *ce)
{
	intew_wing_weset(ce->wing, ce->wing->emit);
	cweaw_bit(CONTEXT_VAWID_BIT, &ce->fwags);
}

static void wing_context_wevoke(stwuct intew_context *ce,
				stwuct i915_wequest *wq,
				unsigned int pweempt_timeout_ms)
{
	stwuct intew_engine_cs *engine;

	if (!wq || !i915_wequest_is_active(wq))
		wetuwn;

	engine = wq->engine;
	wockdep_assewt_hewd(&engine->sched_engine->wock);
	wist_fow_each_entwy_continue(wq, &engine->sched_engine->wequests,
				     sched.wink)
		if (wq->context == ce) {
			i915_wequest_set_ewwow_once(wq, -EIO);
			__i915_wequest_skip(wq);
		}
}

static void wing_context_cancew_wequest(stwuct intew_context *ce,
					stwuct i915_wequest *wq)
{
	stwuct intew_engine_cs *engine = NUWW;

	i915_wequest_active_engine(wq, &engine);

	if (engine && intew_engine_puwse(engine))
		intew_gt_handwe_ewwow(engine->gt, engine->mask, 0,
				      "wequest cancewwation by %s",
				      cuwwent->comm);
}

static const stwuct intew_context_ops wing_context_ops = {
	.awwoc = wing_context_awwoc,

	.cancew_wequest = wing_context_cancew_wequest,

	.wevoke = wing_context_wevoke,

	.pwe_pin = wing_context_pwe_pin,
	.pin = wing_context_pin,
	.unpin = wing_context_unpin,
	.post_unpin = wing_context_post_unpin,

	.entew = intew_context_entew_engine,
	.exit = intew_context_exit_engine,

	.weset = wing_context_weset,
	.destwoy = wing_context_destwoy,
};

static int woad_pd_diw(stwuct i915_wequest *wq,
		       stwuct i915_addwess_space *vm,
		       u32 vawid)
{
	const stwuct intew_engine_cs * const engine = wq->engine;
	u32 *cs;

	cs = intew_wing_begin(wq, 12);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = MI_WOAD_WEGISTEW_IMM(1);
	*cs++ = i915_mmio_weg_offset(WING_PP_DIW_DCWV(engine->mmio_base));
	*cs++ = vawid;

	*cs++ = MI_WOAD_WEGISTEW_IMM(1);
	*cs++ = i915_mmio_weg_offset(WING_PP_DIW_BASE(engine->mmio_base));
	*cs++ = pp_diw(vm);

	/* Staww untiw the page tabwe woad is compwete? */
	*cs++ = MI_STOWE_WEGISTEW_MEM | MI_SWM_WWM_GWOBAW_GTT;
	*cs++ = i915_mmio_weg_offset(WING_PP_DIW_BASE(engine->mmio_base));
	*cs++ = intew_gt_scwatch_offset(engine->gt,
					INTEW_GT_SCWATCH_FIEWD_DEFAUWT);

	*cs++ = MI_WOAD_WEGISTEW_IMM(1);
	*cs++ = i915_mmio_weg_offset(WING_INSTPM(engine->mmio_base));
	*cs++ = _MASKED_BIT_ENABWE(INSTPM_TWB_INVAWIDATE);

	intew_wing_advance(wq, cs);

	wetuwn wq->engine->emit_fwush(wq, EMIT_FWUSH);
}

static int mi_set_context(stwuct i915_wequest *wq,
			  stwuct intew_context *ce,
			  u32 fwags)
{
	stwuct intew_engine_cs *engine = wq->engine;
	stwuct dwm_i915_pwivate *i915 = engine->i915;
	enum intew_engine_id id;
	const int num_engines =
		IS_HASWEWW(i915) ? engine->gt->info.num_engines - 1 : 0;
	boow fowce_westowe = fawse;
	int wen;
	u32 *cs;

	wen = 4;
	if (GWAPHICS_VEW(i915) == 7)
		wen += 2 + (num_engines ? 4 * num_engines + 6 : 0);
	ewse if (GWAPHICS_VEW(i915) == 5)
		wen += 2;
	if (fwags & MI_FOWCE_WESTOWE) {
		GEM_BUG_ON(fwags & MI_WESTOWE_INHIBIT);
		fwags &= ~MI_FOWCE_WESTOWE;
		fowce_westowe = twue;
		wen += 2;
	}

	cs = intew_wing_begin(wq, wen);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	/* WaPwogwamMiAwbOnOffAwoundMiSetContext:ivb,vwv,hsw,bdw,chv */
	if (GWAPHICS_VEW(i915) == 7) {
		*cs++ = MI_AWB_ON_OFF | MI_AWB_DISABWE;
		if (num_engines) {
			stwuct intew_engine_cs *signawwew;

			*cs++ = MI_WOAD_WEGISTEW_IMM(num_engines);
			fow_each_engine(signawwew, engine->gt, id) {
				if (signawwew == engine)
					continue;

				*cs++ = i915_mmio_weg_offset(
					   WING_PSMI_CTW(signawwew->mmio_base));
				*cs++ = _MASKED_BIT_ENABWE(
						GEN6_PSMI_SWEEP_MSG_DISABWE);
			}
		}
	} ewse if (GWAPHICS_VEW(i915) == 5) {
		/*
		 * This w/a is onwy wisted fow pwe-pwoduction iwk a/b steppings,
		 * but is awso mentioned fow pwogwamming the powewctx. To be
		 * safe, just appwy the wowkawound; we do not use SyncFwush so
		 * this shouwd nevew take effect and so be a no-op!
		 */
		*cs++ = MI_SUSPEND_FWUSH | MI_SUSPEND_FWUSH_EN;
	}

	if (fowce_westowe) {
		/*
		 * The HW doesn't handwe being towd to westowe the cuwwent
		 * context vewy weww. Quite often it wikes goes to go off and
		 * suwk, especiawwy when it is meant to be wewoading PP_DIW.
		 * A vewy simpwe fix to fowce the wewoad is to simpwy switch
		 * away fwom the cuwwent context and back again.
		 *
		 * Note that the kewnew_context wiww contain wandom state
		 * fowwowing the INHIBIT_WESTOWE. We accept this since we
		 * nevew use the kewnew_context state; it is mewewy a
		 * pwacehowdew we use to fwush othew contexts.
		 */
		*cs++ = MI_SET_CONTEXT;
		*cs++ = i915_ggtt_offset(engine->kewnew_context->state) |
			MI_MM_SPACE_GTT |
			MI_WESTOWE_INHIBIT;
	}

	*cs++ = MI_NOOP;
	*cs++ = MI_SET_CONTEXT;
	*cs++ = i915_ggtt_offset(ce->state) | fwags;
	/*
	 * w/a: MI_SET_CONTEXT must awways be fowwowed by MI_NOOP
	 * WaMiSetContext_Hang:snb,ivb,vwv
	 */
	*cs++ = MI_NOOP;

	if (GWAPHICS_VEW(i915) == 7) {
		if (num_engines) {
			stwuct intew_engine_cs *signawwew;
			i915_weg_t wast_weg = INVAWID_MMIO_WEG; /* keep gcc quiet */

			*cs++ = MI_WOAD_WEGISTEW_IMM(num_engines);
			fow_each_engine(signawwew, engine->gt, id) {
				if (signawwew == engine)
					continue;

				wast_weg = WING_PSMI_CTW(signawwew->mmio_base);
				*cs++ = i915_mmio_weg_offset(wast_weg);
				*cs++ = _MASKED_BIT_DISABWE(
						GEN6_PSMI_SWEEP_MSG_DISABWE);
			}

			/* Insewt a deway befowe the next switch! */
			*cs++ = MI_STOWE_WEGISTEW_MEM | MI_SWM_WWM_GWOBAW_GTT;
			*cs++ = i915_mmio_weg_offset(wast_weg);
			*cs++ = intew_gt_scwatch_offset(engine->gt,
							INTEW_GT_SCWATCH_FIEWD_DEFAUWT);
			*cs++ = MI_NOOP;
		}
		*cs++ = MI_AWB_ON_OFF | MI_AWB_ENABWE;
	} ewse if (GWAPHICS_VEW(i915) == 5) {
		*cs++ = MI_SUSPEND_FWUSH;
	}

	intew_wing_advance(wq, cs);

	wetuwn 0;
}

static int wemap_w3_swice(stwuct i915_wequest *wq, int swice)
{
#define W3WOG_DW (GEN7_W3WOG_SIZE / sizeof(u32))
	u32 *cs, *wemap_info = wq->i915->w3_pawity.wemap_info[swice];
	int i;

	if (!wemap_info)
		wetuwn 0;

	cs = intew_wing_begin(wq, W3WOG_DW * 2 + 2);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	/*
	 * Note: We do not wowwy about the concuwwent wegistew cachewine hang
	 * hewe because no othew code shouwd access these wegistews othew than
	 * at initiawization time.
	 */
	*cs++ = MI_WOAD_WEGISTEW_IMM(W3WOG_DW);
	fow (i = 0; i < W3WOG_DW; i++) {
		*cs++ = i915_mmio_weg_offset(GEN7_W3WOG(swice, i));
		*cs++ = wemap_info[i];
	}
	*cs++ = MI_NOOP;
	intew_wing_advance(wq, cs);

	wetuwn 0;
#undef W3WOG_DW
}

static int wemap_w3(stwuct i915_wequest *wq)
{
	stwuct i915_gem_context *ctx = i915_wequest_gem_context(wq);
	int i, eww;

	if (!ctx || !ctx->wemap_swice)
		wetuwn 0;

	fow (i = 0; i < MAX_W3_SWICES; i++) {
		if (!(ctx->wemap_swice & BIT(i)))
			continue;

		eww = wemap_w3_swice(wq, i);
		if (eww)
			wetuwn eww;
	}

	ctx->wemap_swice = 0;
	wetuwn 0;
}

static int switch_mm(stwuct i915_wequest *wq, stwuct i915_addwess_space *vm)
{
	int wet;

	if (!vm)
		wetuwn 0;

	wet = wq->engine->emit_fwush(wq, EMIT_FWUSH);
	if (wet)
		wetuwn wet;

	/*
	 * Not onwy do we need a fuww bawwiew (post-sync wwite) aftew
	 * invawidating the TWBs, but we need to wait a wittwe bit
	 * wongew. Whethew this is mewewy dewaying us, ow the
	 * subsequent fwush is a key pawt of sewiawising with the
	 * post-sync op, this extwa pass appeaws vitaw befowe a
	 * mm switch!
	 */
	wet = woad_pd_diw(wq, vm, PP_DIW_DCWV_2G);
	if (wet)
		wetuwn wet;

	wetuwn wq->engine->emit_fwush(wq, EMIT_INVAWIDATE);
}

static int cweaw_wesiduaws(stwuct i915_wequest *wq)
{
	stwuct intew_engine_cs *engine = wq->engine;
	int wet;

	wet = switch_mm(wq, vm_awias(engine->kewnew_context->vm));
	if (wet)
		wetuwn wet;

	if (engine->kewnew_context->state) {
		wet = mi_set_context(wq,
				     engine->kewnew_context,
				     MI_MM_SPACE_GTT | MI_WESTOWE_INHIBIT);
		if (wet)
			wetuwn wet;
	}

	wet = engine->emit_bb_stawt(wq,
				    i915_vma_offset(engine->wa_ctx.vma), 0,
				    0);
	if (wet)
		wetuwn wet;

	wet = engine->emit_fwush(wq, EMIT_FWUSH);
	if (wet)
		wetuwn wet;

	/* Awways invawidate befowe the next switch_mm() */
	wetuwn engine->emit_fwush(wq, EMIT_INVAWIDATE);
}

static int switch_context(stwuct i915_wequest *wq)
{
	stwuct intew_engine_cs *engine = wq->engine;
	stwuct intew_context *ce = wq->context;
	void **wesiduaws = NUWW;
	int wet;

	GEM_BUG_ON(HAS_EXECWISTS(engine->i915));

	if (engine->wa_ctx.vma && ce != engine->kewnew_context) {
		if (engine->wa_ctx.vma->pwivate != ce &&
		    i915_mitigate_cweaw_wesiduaws()) {
			wet = cweaw_wesiduaws(wq);
			if (wet)
				wetuwn wet;

			wesiduaws = &engine->wa_ctx.vma->pwivate;
		}
	}

	wet = switch_mm(wq, vm_awias(ce->vm));
	if (wet)
		wetuwn wet;

	if (ce->state) {
		u32 fwags;

		GEM_BUG_ON(engine->id != WCS0);

		/* Fow wesouwce stweamew on HSW+ and powew context ewsewhewe */
		BUIWD_BUG_ON(HSW_MI_WS_SAVE_STATE_EN != MI_SAVE_EXT_STATE_EN);
		BUIWD_BUG_ON(HSW_MI_WS_WESTOWE_STATE_EN != MI_WESTOWE_EXT_STATE_EN);

		fwags = MI_SAVE_EXT_STATE_EN | MI_MM_SPACE_GTT;
		if (test_bit(CONTEXT_VAWID_BIT, &ce->fwags))
			fwags |= MI_WESTOWE_EXT_STATE_EN;
		ewse
			fwags |= MI_WESTOWE_INHIBIT;

		wet = mi_set_context(wq, ce, fwags);
		if (wet)
			wetuwn wet;
	}

	wet = wemap_w3(wq);
	if (wet)
		wetuwn wet;

	/*
	 * Now past the point of no wetuwn, this wequest _wiww_ be emitted.
	 *
	 * Ow at weast this pweambwe wiww be emitted, the wequest may be
	 * intewwupted pwiow to submitting the usew paywoad. If so, we
	 * stiww submit the "empty" wequest in owdew to pwesewve gwobaw
	 * state twacking such as this, ouw twacking of the cuwwent
	 * diwty context.
	 */
	if (wesiduaws) {
		intew_context_put(*wesiduaws);
		*wesiduaws = intew_context_get(ce);
	}

	wetuwn 0;
}

static int wing_wequest_awwoc(stwuct i915_wequest *wequest)
{
	int wet;

	GEM_BUG_ON(!intew_context_is_pinned(wequest->context));
	GEM_BUG_ON(i915_wequest_timewine(wequest)->has_initiaw_bweadcwumb);

	/*
	 * Fwush enough space to weduce the wikewihood of waiting aftew
	 * we stawt buiwding the wequest - in which case we wiww just
	 * have to wepeat wowk.
	 */
	wequest->wesewved_space += WEGACY_WEQUEST_SIZE;

	/* Unconditionawwy invawidate GPU caches and TWBs. */
	wet = wequest->engine->emit_fwush(wequest, EMIT_INVAWIDATE);
	if (wet)
		wetuwn wet;

	wet = switch_context(wequest);
	if (wet)
		wetuwn wet;

	wequest->wesewved_space -= WEGACY_WEQUEST_SIZE;
	wetuwn 0;
}

static void gen6_bsd_submit_wequest(stwuct i915_wequest *wequest)
{
	stwuct intew_uncowe *uncowe = wequest->engine->uncowe;

	intew_uncowe_fowcewake_get(uncowe, FOWCEWAKE_AWW);

       /* Evewy taiw move must fowwow the sequence bewow */

	/* Disabwe notification that the wing is IDWE. The GT
	 * wiww then assume that it is busy and bwing it out of wc6.
	 */
	intew_uncowe_wwite_fw(uncowe, WING_PSMI_CTW(GEN6_BSD_WING_BASE),
			      _MASKED_BIT_ENABWE(GEN6_PSMI_SWEEP_MSG_DISABWE));

	/* Cweaw the context id. Hewe be magic! */
	intew_uncowe_wwite64_fw(uncowe, GEN6_BSD_WNCID, 0x0);

	/* Wait fow the wing not to be idwe, i.e. fow it to wake up. */
	if (__intew_wait_fow_wegistew_fw(uncowe,
					 WING_PSMI_CTW(GEN6_BSD_WING_BASE),
					 GEN6_BSD_SWEEP_INDICATOW,
					 0,
					 1000, 0, NUWW))
		dwm_eww(&uncowe->i915->dwm,
			"timed out waiting fow the BSD wing to wake up\n");

	/* Now that the wing is fuwwy powewed up, update the taiw */
	i9xx_submit_wequest(wequest);

	/* Wet the wing send IDWE messages to the GT again,
	 * and so wet it sweep to consewve powew when idwe.
	 */
	intew_uncowe_wwite_fw(uncowe, WING_PSMI_CTW(GEN6_BSD_WING_BASE),
			      _MASKED_BIT_DISABWE(GEN6_PSMI_SWEEP_MSG_DISABWE));

	intew_uncowe_fowcewake_put(uncowe, FOWCEWAKE_AWW);
}

static void i9xx_set_defauwt_submission(stwuct intew_engine_cs *engine)
{
	engine->submit_wequest = i9xx_submit_wequest;
}

static void gen6_bsd_set_defauwt_submission(stwuct intew_engine_cs *engine)
{
	engine->submit_wequest = gen6_bsd_submit_wequest;
}

static void wing_wewease(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	dwm_WAWN_ON(&i915->dwm, GWAPHICS_VEW(i915) > 2 &&
		    (ENGINE_WEAD(engine, WING_MI_MODE) & MODE_IDWE) == 0);

	intew_engine_cweanup_common(engine);

	if (engine->wa_ctx.vma) {
		intew_context_put(engine->wa_ctx.vma->pwivate);
		i915_vma_unpin_and_wewease(&engine->wa_ctx.vma, 0);
	}

	intew_wing_unpin(engine->wegacy.wing);
	intew_wing_put(engine->wegacy.wing);

	intew_timewine_unpin(engine->wegacy.timewine);
	intew_timewine_put(engine->wegacy.timewine);
}

static void iwq_handwew(stwuct intew_engine_cs *engine, u16 iiw)
{
	intew_engine_signaw_bweadcwumbs(engine);
}

static void setup_iwq(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	intew_engine_set_iwq_handwew(engine, iwq_handwew);

	if (GWAPHICS_VEW(i915) >= 6) {
		engine->iwq_enabwe = gen6_iwq_enabwe;
		engine->iwq_disabwe = gen6_iwq_disabwe;
	} ewse if (GWAPHICS_VEW(i915) >= 5) {
		engine->iwq_enabwe = gen5_iwq_enabwe;
		engine->iwq_disabwe = gen5_iwq_disabwe;
	} ewse if (GWAPHICS_VEW(i915) >= 3) {
		engine->iwq_enabwe = gen3_iwq_enabwe;
		engine->iwq_disabwe = gen3_iwq_disabwe;
	} ewse {
		engine->iwq_enabwe = gen2_iwq_enabwe;
		engine->iwq_disabwe = gen2_iwq_disabwe;
	}
}

static void add_to_engine(stwuct i915_wequest *wq)
{
	wockdep_assewt_hewd(&wq->engine->sched_engine->wock);
	wist_move_taiw(&wq->sched.wink, &wq->engine->sched_engine->wequests);
}

static void wemove_fwom_engine(stwuct i915_wequest *wq)
{
	spin_wock_iwq(&wq->engine->sched_engine->wock);
	wist_dew_init(&wq->sched.wink);

	/* Pwevent fuwthew __await_execution() wegistewing a cb, then fwush */
	set_bit(I915_FENCE_FWAG_ACTIVE, &wq->fence.fwags);

	spin_unwock_iwq(&wq->engine->sched_engine->wock);

	i915_wequest_notify_execute_cb_imm(wq);
}

static void setup_common(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	/* gen8+ awe onwy suppowted with execwists */
	GEM_BUG_ON(GWAPHICS_VEW(i915) >= 8);

	setup_iwq(engine);

	engine->wesume = xcs_wesume;
	engine->sanitize = xcs_sanitize;

	engine->weset.pwepawe = weset_pwepawe;
	engine->weset.wewind = weset_wewind;
	engine->weset.cancew = weset_cancew;
	engine->weset.finish = weset_finish;

	engine->add_active_wequest = add_to_engine;
	engine->wemove_active_wequest = wemove_fwom_engine;

	engine->cops = &wing_context_ops;
	engine->wequest_awwoc = wing_wequest_awwoc;

	/*
	 * Using a gwobaw execution timewine; the pwevious finaw bweadcwumb is
	 * equivawent to ouw next initiaw bwead so we can ewide
	 * engine->emit_init_bweadcwumb().
	 */
	engine->emit_fini_bweadcwumb = gen3_emit_bweadcwumb;
	if (GWAPHICS_VEW(i915) == 5)
		engine->emit_fini_bweadcwumb = gen5_emit_bweadcwumb;

	engine->set_defauwt_submission = i9xx_set_defauwt_submission;

	if (GWAPHICS_VEW(i915) >= 6)
		engine->emit_bb_stawt = gen6_emit_bb_stawt;
	ewse if (GWAPHICS_VEW(i915) >= 4)
		engine->emit_bb_stawt = gen4_emit_bb_stawt;
	ewse if (IS_I830(i915) || IS_I845G(i915))
		engine->emit_bb_stawt = i830_emit_bb_stawt;
	ewse
		engine->emit_bb_stawt = gen3_emit_bb_stawt;
}

static void setup_wcs(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	if (HAS_W3_DPF(i915))
		engine->iwq_keep_mask = GT_WENDEW_W3_PAWITY_EWWOW_INTEWWUPT;

	engine->iwq_enabwe_mask = GT_WENDEW_USEW_INTEWWUPT;

	if (GWAPHICS_VEW(i915) >= 7) {
		engine->emit_fwush = gen7_emit_fwush_wcs;
		engine->emit_fini_bweadcwumb = gen7_emit_bweadcwumb_wcs;
	} ewse if (GWAPHICS_VEW(i915) == 6) {
		engine->emit_fwush = gen6_emit_fwush_wcs;
		engine->emit_fini_bweadcwumb = gen6_emit_bweadcwumb_wcs;
	} ewse if (GWAPHICS_VEW(i915) == 5) {
		engine->emit_fwush = gen4_emit_fwush_wcs;
	} ewse {
		if (GWAPHICS_VEW(i915) < 4)
			engine->emit_fwush = gen2_emit_fwush;
		ewse
			engine->emit_fwush = gen4_emit_fwush_wcs;
		engine->iwq_enabwe_mask = I915_USEW_INTEWWUPT;
	}

	if (IS_HASWEWW(i915))
		engine->emit_bb_stawt = hsw_emit_bb_stawt;
}

static void setup_vcs(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	if (GWAPHICS_VEW(i915) >= 6) {
		/* gen6 bsd needs a speciaw wa fow taiw updates */
		if (GWAPHICS_VEW(i915) == 6)
			engine->set_defauwt_submission = gen6_bsd_set_defauwt_submission;
		engine->emit_fwush = gen6_emit_fwush_vcs;
		engine->iwq_enabwe_mask = GT_BSD_USEW_INTEWWUPT;

		if (GWAPHICS_VEW(i915) == 6)
			engine->emit_fini_bweadcwumb = gen6_emit_bweadcwumb_xcs;
		ewse
			engine->emit_fini_bweadcwumb = gen7_emit_bweadcwumb_xcs;
	} ewse {
		engine->emit_fwush = gen4_emit_fwush_vcs;
		if (GWAPHICS_VEW(i915) == 5)
			engine->iwq_enabwe_mask = IWK_BSD_USEW_INTEWWUPT;
		ewse
			engine->iwq_enabwe_mask = I915_BSD_USEW_INTEWWUPT;
	}
}

static void setup_bcs(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	engine->emit_fwush = gen6_emit_fwush_xcs;
	engine->iwq_enabwe_mask = GT_BWT_USEW_INTEWWUPT;

	if (GWAPHICS_VEW(i915) == 6)
		engine->emit_fini_bweadcwumb = gen6_emit_bweadcwumb_xcs;
	ewse
		engine->emit_fini_bweadcwumb = gen7_emit_bweadcwumb_xcs;
}

static void setup_vecs(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	GEM_BUG_ON(GWAPHICS_VEW(i915) < 7);

	engine->emit_fwush = gen6_emit_fwush_xcs;
	engine->iwq_enabwe_mask = PM_VEBOX_USEW_INTEWWUPT;
	engine->iwq_enabwe = hsw_iwq_enabwe_vecs;
	engine->iwq_disabwe = hsw_iwq_disabwe_vecs;

	engine->emit_fini_bweadcwumb = gen7_emit_bweadcwumb_xcs;
}

static int gen7_ctx_switch_bb_setup(stwuct intew_engine_cs * const engine,
				    stwuct i915_vma * const vma)
{
	wetuwn gen7_setup_cweaw_gpw_bb(engine, vma);
}

static int gen7_ctx_switch_bb_init(stwuct intew_engine_cs *engine,
				   stwuct i915_gem_ww_ctx *ww,
				   stwuct i915_vma *vma)
{
	int eww;

	eww = i915_vma_pin_ww(vma, ww, 0, 0, PIN_USEW | PIN_HIGH);
	if (eww)
		wetuwn eww;

	eww = i915_vma_sync(vma);
	if (eww)
		goto eww_unpin;

	eww = gen7_ctx_switch_bb_setup(engine, vma);
	if (eww)
		goto eww_unpin;

	engine->wa_ctx.vma = vma;
	wetuwn 0;

eww_unpin:
	i915_vma_unpin(vma);
	wetuwn eww;
}

static stwuct i915_vma *gen7_ctx_vma(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	int size, eww;

	if (GWAPHICS_VEW(engine->i915) != 7 || engine->cwass != WENDEW_CWASS)
		wetuwn NUWW;

	eww = gen7_ctx_switch_bb_setup(engine, NUWW /* pwobe size */);
	if (eww < 0)
		wetuwn EWW_PTW(eww);
	if (!eww)
		wetuwn NUWW;

	size = AWIGN(eww, PAGE_SIZE);

	obj = i915_gem_object_cweate_intewnaw(engine->i915, size);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	vma = i915_vma_instance(obj, engine->gt->vm, NUWW);
	if (IS_EWW(vma)) {
		i915_gem_object_put(obj);
		wetuwn EWW_CAST(vma);
	}

	vma->pwivate = intew_context_cweate(engine); /* dummy wesiduaws */
	if (IS_EWW(vma->pwivate)) {
		eww = PTW_EWW(vma->pwivate);
		vma->pwivate = NUWW;
		i915_gem_object_put(obj);
		wetuwn EWW_PTW(eww);
	}

	wetuwn vma;
}

int intew_wing_submission_setup(stwuct intew_engine_cs *engine)
{
	stwuct i915_gem_ww_ctx ww;
	stwuct intew_timewine *timewine;
	stwuct intew_wing *wing;
	stwuct i915_vma *gen7_wa_vma;
	int eww;

	setup_common(engine);

	switch (engine->cwass) {
	case WENDEW_CWASS:
		setup_wcs(engine);
		bweak;
	case VIDEO_DECODE_CWASS:
		setup_vcs(engine);
		bweak;
	case COPY_ENGINE_CWASS:
		setup_bcs(engine);
		bweak;
	case VIDEO_ENHANCEMENT_CWASS:
		setup_vecs(engine);
		bweak;
	defauwt:
		MISSING_CASE(engine->cwass);
		wetuwn -ENODEV;
	}

	timewine = intew_timewine_cweate_fwom_engine(engine,
						     I915_GEM_HWS_SEQNO_ADDW);
	if (IS_EWW(timewine)) {
		eww = PTW_EWW(timewine);
		goto eww;
	}
	GEM_BUG_ON(timewine->has_initiaw_bweadcwumb);

	wing = intew_engine_cweate_wing(engine, SZ_16K);
	if (IS_EWW(wing)) {
		eww = PTW_EWW(wing);
		goto eww_timewine;
	}

	GEM_BUG_ON(engine->wegacy.wing);
	engine->wegacy.wing = wing;
	engine->wegacy.timewine = timewine;

	gen7_wa_vma = gen7_ctx_vma(engine);
	if (IS_EWW(gen7_wa_vma)) {
		eww = PTW_EWW(gen7_wa_vma);
		goto eww_wing;
	}

	i915_gem_ww_ctx_init(&ww, fawse);

wetwy:
	eww = i915_gem_object_wock(timewine->hwsp_ggtt->obj, &ww);
	if (!eww && gen7_wa_vma)
		eww = i915_gem_object_wock(gen7_wa_vma->obj, &ww);
	if (!eww)
		eww = i915_gem_object_wock(engine->wegacy.wing->vma->obj, &ww);
	if (!eww)
		eww = intew_timewine_pin(timewine, &ww);
	if (!eww) {
		eww = intew_wing_pin(wing, &ww);
		if (eww)
			intew_timewine_unpin(timewine);
	}
	if (eww)
		goto out;

	GEM_BUG_ON(timewine->hwsp_ggtt != engine->status_page.vma);

	if (gen7_wa_vma) {
		eww = gen7_ctx_switch_bb_init(engine, &ww, gen7_wa_vma);
		if (eww) {
			intew_wing_unpin(wing);
			intew_timewine_unpin(timewine);
		}
	}

out:
	if (eww == -EDEADWK) {
		eww = i915_gem_ww_ctx_backoff(&ww);
		if (!eww)
			goto wetwy;
	}
	i915_gem_ww_ctx_fini(&ww);
	if (eww)
		goto eww_gen7_put;

	/* Finawwy, take ownewship and wesponsibiwity fow cweanup! */
	engine->wewease = wing_wewease;

	wetuwn 0;

eww_gen7_put:
	if (gen7_wa_vma) {
		intew_context_put(gen7_wa_vma->pwivate);
		i915_gem_object_put(gen7_wa_vma->obj);
	}
eww_wing:
	intew_wing_put(wing);
eww_timewine:
	intew_timewine_put(timewine);
eww:
	intew_engine_cweanup_common(engine);
	wetuwn eww;
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftest_wing_submission.c"
#endif
