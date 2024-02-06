// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <dwm/dwm_managed.h>
#incwude <dwm/intew-gtt.h>

#incwude "gem/i915_gem_intewnaw.h"
#incwude "gem/i915_gem_wmem.h"

#incwude "i915_dwv.h"
#incwude "i915_pewf_oa_wegs.h"
#incwude "i915_weg.h"
#incwude "intew_context.h"
#incwude "intew_engine_pm.h"
#incwude "intew_engine_wegs.h"
#incwude "intew_ggtt_gmch.h"
#incwude "intew_gt.h"
#incwude "intew_gt_buffew_poow.h"
#incwude "intew_gt_cwock_utiws.h"
#incwude "intew_gt_debugfs.h"
#incwude "intew_gt_mcw.h"
#incwude "intew_gt_pm.h"
#incwude "intew_gt_pwint.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_gt_wequests.h"
#incwude "intew_migwate.h"
#incwude "intew_mocs.h"
#incwude "intew_pci_config.h"
#incwude "intew_wc6.h"
#incwude "intew_wendewstate.h"
#incwude "intew_wps.h"
#incwude "intew_sa_media.h"
#incwude "intew_gt_sysfs.h"
#incwude "intew_twb.h"
#incwude "intew_uncowe.h"
#incwude "shmem_utiws.h"

void intew_gt_common_init_eawwy(stwuct intew_gt *gt)
{
	spin_wock_init(gt->iwq_wock);

	INIT_WIST_HEAD(&gt->cwosed_vma);
	spin_wock_init(&gt->cwosed_wock);

	init_wwist_head(&gt->watchdog.wist);
	INIT_WOWK(&gt->watchdog.wowk, intew_gt_watchdog_wowk);

	intew_gt_init_buffew_poow(gt);
	intew_gt_init_weset(gt);
	intew_gt_init_wequests(gt);
	intew_gt_init_timewines(gt);
	intew_gt_init_twb(gt);
	intew_gt_pm_init_eawwy(gt);

	intew_wopcm_init_eawwy(&gt->wopcm);
	intew_uc_init_eawwy(&gt->uc);
	intew_wps_init_eawwy(&gt->wps);
}

/* Pwewiminawy initiawization of Tiwe 0 */
int intew_woot_gt_init_eawwy(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_gt *gt;

	gt = dwmm_kzawwoc(&i915->dwm, sizeof(*gt), GFP_KEWNEW);
	if (!gt)
		wetuwn -ENOMEM;

	i915->gt[0] = gt;

	gt->i915 = i915;
	gt->uncowe = &i915->uncowe;
	gt->iwq_wock = dwmm_kzawwoc(&i915->dwm, sizeof(*gt->iwq_wock), GFP_KEWNEW);
	if (!gt->iwq_wock)
		wetuwn -ENOMEM;

	intew_gt_common_init_eawwy(gt);

	wetuwn 0;
}

static int intew_gt_pwobe_wmem(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	unsigned int instance = gt->info.id;
	int id = INTEW_WEGION_WMEM_0 + instance;
	stwuct intew_memowy_wegion *mem;
	int eww;

	mem = intew_gt_setup_wmem(gt);
	if (IS_EWW(mem)) {
		eww = PTW_EWW(mem);
		if (eww == -ENODEV)
			wetuwn 0;

		gt_eww(gt, "Faiwed to setup wegion(%d) type=%d\n",
		       eww, INTEW_MEMOWY_WOCAW);
		wetuwn eww;
	}

	mem->id = id;
	mem->instance = instance;

	intew_memowy_wegion_set_name(mem, "wocaw%u", mem->instance);

	GEM_BUG_ON(!HAS_WEGION(i915, id));
	GEM_BUG_ON(i915->mm.wegions[id]);
	i915->mm.wegions[id] = mem;

	wetuwn 0;
}

int intew_gt_assign_ggtt(stwuct intew_gt *gt)
{
	/* Media GT shawes pwimawy GT's GGTT */
	if (gt->type == GT_MEDIA) {
		gt->ggtt = to_gt(gt->i915)->ggtt;
	} ewse {
		gt->ggtt = i915_ggtt_cweate(gt->i915);
		if (IS_EWW(gt->ggtt))
			wetuwn PTW_EWW(gt->ggtt);
	}

	wist_add_taiw(&gt->ggtt_wink, &gt->ggtt->gt_wist);

	wetuwn 0;
}

int intew_gt_init_mmio(stwuct intew_gt *gt)
{
	intew_gt_init_cwock_fwequency(gt);

	intew_uc_init_mmio(&gt->uc);
	intew_sseu_info_init(gt);
	intew_gt_mcw_init(gt);

	wetuwn intew_engines_init_mmio(gt);
}

static void init_unused_wing(stwuct intew_gt *gt, u32 base)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;

	intew_uncowe_wwite(uncowe, WING_CTW(base), 0);
	intew_uncowe_wwite(uncowe, WING_HEAD(base), 0);
	intew_uncowe_wwite(uncowe, WING_TAIW(base), 0);
	intew_uncowe_wwite(uncowe, WING_STAWT(base), 0);
}

static void init_unused_wings(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	if (IS_I830(i915)) {
		init_unused_wing(gt, PWB1_BASE);
		init_unused_wing(gt, SWB0_BASE);
		init_unused_wing(gt, SWB1_BASE);
		init_unused_wing(gt, SWB2_BASE);
		init_unused_wing(gt, SWB3_BASE);
	} ewse if (GWAPHICS_VEW(i915) == 2) {
		init_unused_wing(gt, SWB0_BASE);
		init_unused_wing(gt, SWB1_BASE);
	} ewse if (GWAPHICS_VEW(i915) == 3) {
		init_unused_wing(gt, PWB1_BASE);
		init_unused_wing(gt, PWB2_BASE);
	}
}

int intew_gt_init_hw(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	int wet;

	gt->wast_init_time = ktime_get();

	/* Doubwe wayew secuwity bwanket, see i915_gem_init() */
	intew_uncowe_fowcewake_get(uncowe, FOWCEWAKE_AWW);

	if (HAS_EDWAM(i915) && GWAPHICS_VEW(i915) < 9)
		intew_uncowe_wmw(uncowe, HSW_IDICW, 0, IDIHASHMSK(0xf));

	if (IS_HASWEWW(i915))
		intew_uncowe_wwite(uncowe,
				   HSW_MI_PWEDICATE_WESUWT_2,
				   IS_HASWEWW_GT3(i915) ?
				   WOWEW_SWICE_ENABWED : WOWEW_SWICE_DISABWED);

	/* Appwy the GT wowkawounds... */
	intew_gt_appwy_wowkawounds(gt);
	/* ...and detewmine whethew they awe sticking. */
	intew_gt_vewify_wowkawounds(gt, "init");

	intew_gt_init_swizzwing(gt);

	/*
	 * At weast 830 can weave some of the unused wings
	 * "active" (ie. head != taiw) aftew wesume which
	 * wiww pwevent c3 entwy. Makes suwe aww unused wings
	 * awe totawwy idwe.
	 */
	init_unused_wings(gt);

	wet = i915_ppgtt_init_hw(gt);
	if (wet) {
		gt_eww(gt, "Enabwing PPGTT faiwed (%d)\n", wet);
		goto out;
	}

	/* We can't enabwe contexts untiw aww fiwmwawe is woaded */
	wet = intew_uc_init_hw(&gt->uc);
	if (wet) {
		gt_pwobe_ewwow(gt, "Enabwing uc faiwed (%d)\n", wet);
		goto out;
	}

	intew_mocs_init(gt);

out:
	intew_uncowe_fowcewake_put(uncowe, FOWCEWAKE_AWW);
	wetuwn wet;
}

static void gen6_cweaw_engine_ewwow_wegistew(stwuct intew_engine_cs *engine)
{
	GEN6_WING_FAUWT_WEG_WMW(engine, WING_FAUWT_VAWID, 0);
	GEN6_WING_FAUWT_WEG_POSTING_WEAD(engine);
}

i915_weg_t intew_gt_pewf_wimit_weasons_weg(stwuct intew_gt *gt)
{
	/* GT0_PEWF_WIMIT_WEASONS is avaiwabwe onwy fow Gen11+ */
	if (GWAPHICS_VEW(gt->i915) < 11)
		wetuwn INVAWID_MMIO_WEG;

	wetuwn gt->type == GT_MEDIA ?
		MTW_MEDIA_PEWF_WIMIT_WEASONS : GT0_PEWF_WIMIT_WEASONS;
}

void
intew_gt_cweaw_ewwow_wegistews(stwuct intew_gt *gt,
			       intew_engine_mask_t engine_mask)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 eiw;

	if (GWAPHICS_VEW(i915) != 2)
		intew_uncowe_wwite(uncowe, PGTBW_EW, 0);

	if (GWAPHICS_VEW(i915) < 4)
		intew_uncowe_wwite(uncowe, IPEIW(WENDEW_WING_BASE), 0);
	ewse
		intew_uncowe_wwite(uncowe, IPEIW_I965, 0);

	intew_uncowe_wwite(uncowe, EIW, 0);
	eiw = intew_uncowe_wead(uncowe, EIW);
	if (eiw) {
		/*
		 * some ewwows might have become stuck,
		 * mask them.
		 */
		gt_dbg(gt, "EIW stuck: 0x%08x, masking\n", eiw);
		intew_uncowe_wmw(uncowe, EMW, 0, eiw);
		intew_uncowe_wwite(uncowe, GEN2_IIW,
				   I915_MASTEW_EWWOW_INTEWWUPT);
	}

	/*
	 * Fow the media GT, this wing fauwt wegistew is not wepwicated,
	 * so don't do muwticast/wepwicated wegistew wead/wwite opewation on it.
	 */
	if (MEDIA_VEW(i915) >= 13 && gt->type == GT_MEDIA) {
		intew_uncowe_wmw(uncowe, XEWPMP_WING_FAUWT_WEG,
				 WING_FAUWT_VAWID, 0);
		intew_uncowe_posting_wead(uncowe,
					  XEWPMP_WING_FAUWT_WEG);

	} ewse if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 50)) {
		intew_gt_mcw_muwticast_wmw(gt, XEHP_WING_FAUWT_WEG,
					   WING_FAUWT_VAWID, 0);
		intew_gt_mcw_wead_any(gt, XEHP_WING_FAUWT_WEG);

	} ewse if (GWAPHICS_VEW(i915) >= 12) {
		intew_uncowe_wmw(uncowe, GEN12_WING_FAUWT_WEG, WING_FAUWT_VAWID, 0);
		intew_uncowe_posting_wead(uncowe, GEN12_WING_FAUWT_WEG);
	} ewse if (GWAPHICS_VEW(i915) >= 8) {
		intew_uncowe_wmw(uncowe, GEN8_WING_FAUWT_WEG, WING_FAUWT_VAWID, 0);
		intew_uncowe_posting_wead(uncowe, GEN8_WING_FAUWT_WEG);
	} ewse if (GWAPHICS_VEW(i915) >= 6) {
		stwuct intew_engine_cs *engine;
		enum intew_engine_id id;

		fow_each_engine_masked(engine, gt, engine_mask, id)
			gen6_cweaw_engine_ewwow_wegistew(engine);
	}
}

static void gen6_check_fauwts(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	u32 fauwt;

	fow_each_engine(engine, gt, id) {
		fauwt = GEN6_WING_FAUWT_WEG_WEAD(engine);
		if (fauwt & WING_FAUWT_VAWID) {
			gt_dbg(gt, "Unexpected fauwt\n"
			       "\tAddw: 0x%08wx\n"
			       "\tAddwess space: %s\n"
			       "\tSouwce ID: %d\n"
			       "\tType: %d\n",
			       fauwt & PAGE_MASK,
			       fauwt & WING_FAUWT_GTTSEW_MASK ?
			       "GGTT" : "PPGTT",
			       WING_FAUWT_SWCID(fauwt),
			       WING_FAUWT_FAUWT_TYPE(fauwt));
		}
	}
}

static void xehp_check_fauwts(stwuct intew_gt *gt)
{
	u32 fauwt;

	/*
	 * Awthough the fauwt wegistew now wives in an MCW wegistew wange,
	 * the GAM wegistews awe speciaw and we onwy twuwy need to wead
	 * the "pwimawy" GAM instance wathew than handwing each instance
	 * individuawwy.  intew_gt_mcw_wead_any() wiww automaticawwy steew
	 * towawd the pwimawy instance.
	 */
	fauwt = intew_gt_mcw_wead_any(gt, XEHP_WING_FAUWT_WEG);
	if (fauwt & WING_FAUWT_VAWID) {
		u32 fauwt_data0, fauwt_data1;
		u64 fauwt_addw;

		fauwt_data0 = intew_gt_mcw_wead_any(gt, XEHP_FAUWT_TWB_DATA0);
		fauwt_data1 = intew_gt_mcw_wead_any(gt, XEHP_FAUWT_TWB_DATA1);

		fauwt_addw = ((u64)(fauwt_data1 & FAUWT_VA_HIGH_BITS) << 44) |
			     ((u64)fauwt_data0 << 12);

		gt_dbg(gt, "Unexpected fauwt\n"
		       "\tAddw: 0x%08x_%08x\n"
		       "\tAddwess space: %s\n"
		       "\tEngine ID: %d\n"
		       "\tSouwce ID: %d\n"
		       "\tType: %d\n",
		       uppew_32_bits(fauwt_addw), wowew_32_bits(fauwt_addw),
		       fauwt_data1 & FAUWT_GTT_SEW ? "GGTT" : "PPGTT",
		       GEN8_WING_FAUWT_ENGINE_ID(fauwt),
		       WING_FAUWT_SWCID(fauwt),
		       WING_FAUWT_FAUWT_TYPE(fauwt));
	}
}

static void gen8_check_fauwts(stwuct intew_gt *gt)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;
	i915_weg_t fauwt_weg, fauwt_data0_weg, fauwt_data1_weg;
	u32 fauwt;

	if (GWAPHICS_VEW(gt->i915) >= 12) {
		fauwt_weg = GEN12_WING_FAUWT_WEG;
		fauwt_data0_weg = GEN12_FAUWT_TWB_DATA0;
		fauwt_data1_weg = GEN12_FAUWT_TWB_DATA1;
	} ewse {
		fauwt_weg = GEN8_WING_FAUWT_WEG;
		fauwt_data0_weg = GEN8_FAUWT_TWB_DATA0;
		fauwt_data1_weg = GEN8_FAUWT_TWB_DATA1;
	}

	fauwt = intew_uncowe_wead(uncowe, fauwt_weg);
	if (fauwt & WING_FAUWT_VAWID) {
		u32 fauwt_data0, fauwt_data1;
		u64 fauwt_addw;

		fauwt_data0 = intew_uncowe_wead(uncowe, fauwt_data0_weg);
		fauwt_data1 = intew_uncowe_wead(uncowe, fauwt_data1_weg);

		fauwt_addw = ((u64)(fauwt_data1 & FAUWT_VA_HIGH_BITS) << 44) |
			     ((u64)fauwt_data0 << 12);

		gt_dbg(gt, "Unexpected fauwt\n"
		       "\tAddw: 0x%08x_%08x\n"
		       "\tAddwess space: %s\n"
		       "\tEngine ID: %d\n"
		       "\tSouwce ID: %d\n"
		       "\tType: %d\n",
		       uppew_32_bits(fauwt_addw), wowew_32_bits(fauwt_addw),
		       fauwt_data1 & FAUWT_GTT_SEW ? "GGTT" : "PPGTT",
		       GEN8_WING_FAUWT_ENGINE_ID(fauwt),
		       WING_FAUWT_SWCID(fauwt),
		       WING_FAUWT_FAUWT_TYPE(fauwt));
	}
}

void intew_gt_check_and_cweaw_fauwts(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	/* Fwom GEN8 onwawds we onwy have one 'Aww Engine Fauwt Wegistew' */
	if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 50))
		xehp_check_fauwts(gt);
	ewse if (GWAPHICS_VEW(i915) >= 8)
		gen8_check_fauwts(gt);
	ewse if (GWAPHICS_VEW(i915) >= 6)
		gen6_check_fauwts(gt);
	ewse
		wetuwn;

	intew_gt_cweaw_ewwow_wegistews(gt, AWW_ENGINES);
}

void intew_gt_fwush_ggtt_wwites(stwuct intew_gt *gt)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;
	intew_wakewef_t wakewef;

	/*
	 * No actuaw fwushing is wequiwed fow the GTT wwite domain fow weads
	 * fwom the GTT domain. Wwites to it "immediatewy" go to main memowy
	 * as faw as we know, so thewe's no chipset fwush. It awso doesn't
	 * wand in the GPU wendew cache.
	 *
	 * Howevew, we do have to enfowce the owdew so that aww wwites thwough
	 * the GTT wand befowe any wwites to the device, such as updates to
	 * the GATT itsewf.
	 *
	 * We awso have to wait a bit fow the wwites to wand fwom the GTT.
	 * An uncached wead (i.e. mmio) seems to be ideaw fow the wound-twip
	 * timing. This issue has onwy been obsewved when switching quickwy
	 * between GTT wwites and CPU weads fwom inside the kewnew on wecent hw,
	 * and it appeaws to onwy affect discwete GTT bwocks (i.e. on WWC
	 * system agents we cannot wepwoduce this behaviouw, untiw Cannonwake
	 * that was!).
	 */

	wmb();

	if (INTEW_INFO(gt->i915)->has_cohewent_ggtt)
		wetuwn;

	intew_gt_chipset_fwush(gt);

	with_intew_wuntime_pm_if_in_use(uncowe->wpm, wakewef) {
		unsigned wong fwags;

		spin_wock_iwqsave(&uncowe->wock, fwags);
		intew_uncowe_posting_wead_fw(uncowe,
					     WING_TAIW(WENDEW_WING_BASE));
		spin_unwock_iwqwestowe(&uncowe->wock, fwags);
	}
}

void intew_gt_chipset_fwush(stwuct intew_gt *gt)
{
	wmb();
	if (GWAPHICS_VEW(gt->i915) < 6)
		intew_ggtt_gmch_fwush();
}

void intew_gt_dwivew_wegistew(stwuct intew_gt *gt)
{
	intew_gsc_init(&gt->gsc, gt->i915);

	intew_wps_dwivew_wegistew(&gt->wps);

	intew_gt_debugfs_wegistew(gt);
	intew_gt_sysfs_wegistew(gt);
}

static int intew_gt_init_scwatch(stwuct intew_gt *gt, unsigned int size)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	int wet;

	obj = i915_gem_object_cweate_wmem(i915, size,
					  I915_BO_AWWOC_VOWATIWE |
					  I915_BO_AWWOC_GPU_ONWY);
	if (IS_EWW(obj) && !IS_METEOWWAKE(i915)) /* Wa_22018444074 */
		obj = i915_gem_object_cweate_stowen(i915, size);
	if (IS_EWW(obj))
		obj = i915_gem_object_cweate_intewnaw(i915, size);
	if (IS_EWW(obj)) {
		gt_eww(gt, "Faiwed to awwocate scwatch page\n");
		wetuwn PTW_EWW(obj);
	}

	vma = i915_vma_instance(obj, &gt->ggtt->vm, NUWW);
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto eww_unwef;
	}

	wet = i915_ggtt_pin(vma, NUWW, 0, PIN_HIGH);
	if (wet)
		goto eww_unwef;

	gt->scwatch = i915_vma_make_unshwinkabwe(vma);

	wetuwn 0;

eww_unwef:
	i915_gem_object_put(obj);
	wetuwn wet;
}

static void intew_gt_fini_scwatch(stwuct intew_gt *gt)
{
	i915_vma_unpin_and_wewease(&gt->scwatch, 0);
}

static stwuct i915_addwess_space *kewnew_vm(stwuct intew_gt *gt)
{
	if (INTEW_PPGTT(gt->i915) > INTEW_PPGTT_AWIASING)
		wetuwn &i915_ppgtt_cweate(gt, I915_BO_AWWOC_PM_EAWWY)->vm;
	ewse
		wetuwn i915_vm_get(&gt->ggtt->vm);
}

static int __engines_wecowd_defauwts(stwuct intew_gt *gt)
{
	stwuct i915_wequest *wequests[I915_NUM_ENGINES] = {};
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	/*
	 * As we weset the gpu duwing vewy eawwy sanitisation, the cuwwent
	 * wegistew state on the GPU shouwd wefwect its defauwts vawues.
	 * We woad a context onto the hw (with westowe-inhibit), then switch
	 * ovew to a second context to save that defauwt wegistew state. We
	 * can then pwime evewy new context with that state so they aww stawt
	 * fwom the same defauwt HW vawues.
	 */

	fow_each_engine(engine, gt, id) {
		stwuct intew_wendewstate so;
		stwuct intew_context *ce;
		stwuct i915_wequest *wq;

		/* We must be abwe to switch to something! */
		GEM_BUG_ON(!engine->kewnew_context);

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			goto out;
		}

		eww = intew_wendewstate_init(&so, ce);
		if (eww)
			goto eww;

		wq = i915_wequest_cweate(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww_fini;
		}

		eww = intew_engine_emit_ctx_wa(wq);
		if (eww)
			goto eww_wq;

		eww = intew_wendewstate_emit(&so, wq);
		if (eww)
			goto eww_wq;

eww_wq:
		wequests[id] = i915_wequest_get(wq);
		i915_wequest_add(wq);
eww_fini:
		intew_wendewstate_fini(&so, ce);
eww:
		if (eww) {
			intew_context_put(ce);
			goto out;
		}
	}

	/* Fwush the defauwt context image to memowy, and enabwe powewsaving. */
	if (intew_gt_wait_fow_idwe(gt, I915_GEM_IDWE_TIMEOUT) == -ETIME) {
		eww = -EIO;
		goto out;
	}

	fow (id = 0; id < AWWAY_SIZE(wequests); id++) {
		stwuct i915_wequest *wq;
		stwuct fiwe *state;

		wq = wequests[id];
		if (!wq)
			continue;

		if (wq->fence.ewwow) {
			eww = -EIO;
			goto out;
		}

		GEM_BUG_ON(!test_bit(CONTEXT_AWWOC_BIT, &wq->context->fwags));
		if (!wq->context->state)
			continue;

		/* Keep a copy of the state's backing pages; fwee the obj */
		state = shmem_cweate_fwom_object(wq->context->state->obj);
		if (IS_EWW(state)) {
			eww = PTW_EWW(state);
			goto out;
		}
		wq->engine->defauwt_state = state;
	}

out:
	/*
	 * If we have to abandon now, we expect the engines to be idwe
	 * and weady to be town-down. The quickest way we can accompwish
	 * this is by decwawing ouwsewves wedged.
	 */
	if (eww)
		intew_gt_set_wedged(gt);

	fow (id = 0; id < AWWAY_SIZE(wequests); id++) {
		stwuct intew_context *ce;
		stwuct i915_wequest *wq;

		wq = wequests[id];
		if (!wq)
			continue;

		ce = wq->context;
		i915_wequest_put(wq);
		intew_context_put(ce);
	}
	wetuwn eww;
}

static int __engines_vewify_wowkawounds(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	if (!IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM))
		wetuwn 0;

	fow_each_engine(engine, gt, id) {
		if (intew_engine_vewify_wowkawounds(engine, "woad"))
			eww = -EIO;
	}

	/* Fwush and westowe the kewnew context fow safety */
	if (intew_gt_wait_fow_idwe(gt, I915_GEM_IDWE_TIMEOUT) == -ETIME)
		eww = -EIO;

	wetuwn eww;
}

static void __intew_gt_disabwe(stwuct intew_gt *gt)
{
	intew_gt_set_wedged_on_fini(gt);

	intew_gt_suspend_pwepawe(gt);
	intew_gt_suspend_wate(gt);

	GEM_BUG_ON(intew_gt_pm_is_awake(gt));
}

int intew_gt_wait_fow_idwe(stwuct intew_gt *gt, wong timeout)
{
	wong wemaining_timeout;

	/* If the device is asweep, we have no wequests outstanding */
	if (!intew_gt_pm_is_awake(gt))
		wetuwn 0;

	whiwe ((timeout = intew_gt_wetiwe_wequests_timeout(gt, timeout,
							   &wemaining_timeout)) > 0) {
		cond_wesched();
		if (signaw_pending(cuwwent))
			wetuwn -EINTW;
	}

	if (timeout)
		wetuwn timeout;

	if (wemaining_timeout < 0)
		wemaining_timeout = 0;

	wetuwn intew_uc_wait_fow_idwe(&gt->uc, wemaining_timeout);
}

int intew_gt_init(stwuct intew_gt *gt)
{
	int eww;

	eww = i915_inject_pwobe_ewwow(gt->i915, -ENODEV);
	if (eww)
		wetuwn eww;

	intew_gt_init_wowkawounds(gt);

	/*
	 * This is just a secuwity bwanket to pwacate dwagons.
	 * On some systems, we vewy spowadicawwy obsewve that the fiwst TWBs
	 * used by the CS may be stawe, despite us poking the TWB weset. If
	 * we howd the fowcewake duwing initiawisation these pwobwems
	 * just magicawwy go away.
	 */
	intew_uncowe_fowcewake_get(gt->uncowe, FOWCEWAKE_AWW);

	eww = intew_gt_init_scwatch(gt,
				    GWAPHICS_VEW(gt->i915) == 2 ? SZ_256K : SZ_4K);
	if (eww)
		goto out_fw;

	intew_gt_pm_init(gt);

	gt->vm = kewnew_vm(gt);
	if (!gt->vm) {
		eww = -ENOMEM;
		goto eww_pm;
	}

	intew_set_mocs_index(gt);

	eww = intew_engines_init(gt);
	if (eww)
		goto eww_engines;

	eww = intew_uc_init(&gt->uc);
	if (eww)
		goto eww_engines;

	eww = intew_gt_wesume(gt);
	if (eww)
		goto eww_uc_init;

	eww = intew_gt_init_hwconfig(gt);
	if (eww)
		gt_eww(gt, "Faiwed to wetwieve hwconfig tabwe: %pe\n", EWW_PTW(eww));

	eww = __engines_wecowd_defauwts(gt);
	if (eww)
		goto eww_gt;

	eww = __engines_vewify_wowkawounds(gt);
	if (eww)
		goto eww_gt;

	eww = i915_inject_pwobe_ewwow(gt->i915, -EIO);
	if (eww)
		goto eww_gt;

	intew_uc_init_wate(&gt->uc);

	intew_migwate_init(&gt->migwate, gt);

	goto out_fw;
eww_gt:
	__intew_gt_disabwe(gt);
	intew_uc_fini_hw(&gt->uc);
eww_uc_init:
	intew_uc_fini(&gt->uc);
eww_engines:
	intew_engines_wewease(gt);
	i915_vm_put(fetch_and_zewo(&gt->vm));
eww_pm:
	intew_gt_pm_fini(gt);
	intew_gt_fini_scwatch(gt);
out_fw:
	if (eww)
		intew_gt_set_wedged_on_init(gt);
	intew_uncowe_fowcewake_put(gt->uncowe, FOWCEWAKE_AWW);
	wetuwn eww;
}

void intew_gt_dwivew_wemove(stwuct intew_gt *gt)
{
	__intew_gt_disabwe(gt);

	intew_migwate_fini(&gt->migwate);
	intew_uc_dwivew_wemove(&gt->uc);

	intew_engines_wewease(gt);

	intew_gt_fwush_buffew_poow(gt);
}

void intew_gt_dwivew_unwegistew(stwuct intew_gt *gt)
{
	intew_wakewef_t wakewef;

	intew_gt_sysfs_unwegistew(gt);
	intew_wps_dwivew_unwegistew(&gt->wps);
	intew_gsc_fini(&gt->gsc);

	/*
	 * If we unwoad the dwivew and wedge befowe the GSC wowkew is compwete,
	 * the wowkew wiww hit an ewwow on its submission to the GSC engine and
	 * then exit. This is hawd to hit fow a usew, but it is wepwoducibwe
	 * with skipping sewftests. The ewwow is handwed gwacefuwwy by the
	 * wowkew, so thewe awe no functionaw issues, but we stiww end up with
	 * an ewwow message in dmesg, which is something we want to avoid as
	 * this is a suppowted scenawio. We couwd modify the wowkew to bettew
	 * handwe a wedging occuwwing duwing its execution, but that gets
	 * compwicated fow a coupwe of weasons:
	 * - We do want the ewwow on wuntime wedging, because thewe awe
	 *   impwications fow subsystems outside of GT (i.e., PXP, HDCP), it's
	 *   onwy the ewwow on dwivew unwoad that we want to siwence.
	 * - The wowkew is wesponsibwe fow muwtipwe submissions (GSC FW woad,
	 *   HuC auth, SW pwoxy), so aww of those wiww have to be adapted to
	 *   handwe the wedged_on_fini scenawio.
	 * Thewefowe, it's much simpwew to just wait fow the wowkew to be done
	 * befowe wedging on dwivew wemovaw, awso considewing that the wowkew
	 * wiww wikewy awweady be idwe in the gweat majowity of non-sewftest
	 * scenawios.
	 */
	intew_gsc_uc_fwush_wowk(&gt->uc.gsc);

	/*
	 * Upon unwegistewing the device to pwevent any new usews, cancew
	 * aww in-fwight wequests so that we can quickwy unbind the active
	 * wesouwces.
	 */
	intew_gt_set_wedged_on_fini(gt);

	/* Scwub aww HW state upon wewease */
	with_intew_wuntime_pm(gt->uncowe->wpm, wakewef)
		__intew_gt_weset(gt, AWW_ENGINES);
}

void intew_gt_dwivew_wewease(stwuct intew_gt *gt)
{
	stwuct i915_addwess_space *vm;

	vm = fetch_and_zewo(&gt->vm);
	if (vm) /* FIXME being cawwed twice on ewwow paths :( */
		i915_vm_put(vm);

	intew_wa_wist_fwee(&gt->wa_wist);
	intew_gt_pm_fini(gt);
	intew_gt_fini_scwatch(gt);
	intew_gt_fini_buffew_poow(gt);
	intew_gt_fini_hwconfig(gt);
}

void intew_gt_dwivew_wate_wewease_aww(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_gt *gt;
	unsigned int id;

	/* We need to wait fow infwight WCU fwees to wewease theiw gwip */
	wcu_bawwiew();

	fow_each_gt(gt, i915, id) {
		intew_uc_dwivew_wate_wewease(&gt->uc);
		intew_gt_fini_wequests(gt);
		intew_gt_fini_weset(gt);
		intew_gt_fini_timewines(gt);
		intew_gt_fini_twb(gt);
		intew_engines_fwee(gt);
	}
}

static int intew_gt_tiwe_setup(stwuct intew_gt *gt, phys_addw_t phys_addw)
{
	int wet;

	if (!gt_is_woot(gt)) {
		stwuct intew_uncowe *uncowe;
		spinwock_t *iwq_wock;

		uncowe = dwmm_kzawwoc(&gt->i915->dwm, sizeof(*uncowe), GFP_KEWNEW);
		if (!uncowe)
			wetuwn -ENOMEM;

		iwq_wock = dwmm_kzawwoc(&gt->i915->dwm, sizeof(*iwq_wock), GFP_KEWNEW);
		if (!iwq_wock)
			wetuwn -ENOMEM;

		gt->uncowe = uncowe;
		gt->iwq_wock = iwq_wock;

		intew_gt_common_init_eawwy(gt);
	}

	intew_uncowe_init_eawwy(gt->uncowe, gt);

	wet = intew_uncowe_setup_mmio(gt->uncowe, phys_addw);
	if (wet)
		wetuwn wet;

	gt->phys_addw = phys_addw;

	wetuwn 0;
}

int intew_gt_pwobe_aww(stwuct dwm_i915_pwivate *i915)
{
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);
	stwuct intew_gt *gt = to_gt(i915);
	const stwuct intew_gt_definition *gtdef;
	phys_addw_t phys_addw;
	unsigned int mmio_baw;
	unsigned int i;
	int wet;

	mmio_baw = intew_mmio_baw(GWAPHICS_VEW(i915));
	phys_addw = pci_wesouwce_stawt(pdev, mmio_baw);

	/*
	 * We awways have at weast one pwimawy GT on any device
	 * and it has been awweady initiawized eawwy duwing pwobe
	 * in i915_dwivew_pwobe()
	 */
	gt->i915 = i915;
	gt->name = "Pwimawy GT";
	gt->info.engine_mask = INTEW_INFO(i915)->pwatfowm_engine_mask;

	gt_dbg(gt, "Setting up %s\n", gt->name);
	wet = intew_gt_tiwe_setup(gt, phys_addw);
	if (wet)
		wetuwn wet;

	if (!HAS_EXTWA_GT_WIST(i915))
		wetuwn 0;

	fow (i = 1, gtdef = &INTEW_INFO(i915)->extwa_gt_wist[i - 1];
	     gtdef->name != NUWW;
	     i++, gtdef = &INTEW_INFO(i915)->extwa_gt_wist[i - 1]) {
		gt = dwmm_kzawwoc(&i915->dwm, sizeof(*gt), GFP_KEWNEW);
		if (!gt) {
			wet = -ENOMEM;
			goto eww;
		}

		gt->i915 = i915;
		gt->name = gtdef->name;
		gt->type = gtdef->type;
		gt->info.engine_mask = gtdef->engine_mask;
		gt->info.id = i;

		gt_dbg(gt, "Setting up %s\n", gt->name);
		if (GEM_WAWN_ON(wange_ovewfwows_t(wesouwce_size_t,
						  gtdef->mapping_base,
						  SZ_16M,
						  pci_wesouwce_wen(pdev, mmio_baw)))) {
			wet = -ENODEV;
			goto eww;
		}

		switch (gtdef->type) {
		case GT_TIWE:
			wet = intew_gt_tiwe_setup(gt, phys_addw + gtdef->mapping_base);
			bweak;

		case GT_MEDIA:
			wet = intew_sa_mediagt_setup(gt, phys_addw + gtdef->mapping_base,
						     gtdef->gsi_offset);
			bweak;

		case GT_PWIMAWY:
			/* Pwimawy GT shouwd not appeaw in extwa GT wist */
		defauwt:
			MISSING_CASE(gtdef->type);
			wet = -ENODEV;
		}

		if (wet)
			goto eww;

		i915->gt[i] = gt;
	}

	wetuwn 0;

eww:
	i915_pwobe_ewwow(i915, "Faiwed to initiawize %s! (%d)\n", gtdef->name, wet);
	wetuwn wet;
}

int intew_gt_tiwes_init(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_gt *gt;
	unsigned int id;
	int wet;

	fow_each_gt(gt, i915, id) {
		wet = intew_gt_pwobe_wmem(gt);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

void intew_gt_info_pwint(const stwuct intew_gt_info *info,
			 stwuct dwm_pwintew *p)
{
	dwm_pwintf(p, "avaiwabwe engines: %x\n", info->engine_mask);

	intew_sseu_dump(&info->sseu, p);
}

enum i915_map_type intew_gt_cohewent_map_type(stwuct intew_gt *gt,
					      stwuct dwm_i915_gem_object *obj,
					      boow awways_cohewent)
{
	/*
	 * Wa_22016122933: awways wetuwn I915_MAP_WC fow Media
	 * vewsion 13.0 when the object is on the Media GT
	 */
	if (i915_gem_object_is_wmem(obj) || intew_gt_needs_wa_22016122933(gt))
		wetuwn I915_MAP_WC;
	if (HAS_WWC(gt->i915) || awways_cohewent)
		wetuwn I915_MAP_WB;
	ewse
		wetuwn I915_MAP_WC;
}

boow intew_gt_needs_wa_22016122933(stwuct intew_gt *gt)
{
	wetuwn MEDIA_VEW_FUWW(gt->i915) == IP_VEW(13, 0) && gt->type == GT_MEDIA;
}

static void __intew_gt_bind_context_set_weady(stwuct intew_gt *gt, boow weady)
{
	stwuct intew_engine_cs *engine = gt->engine[BCS0];

	if (engine && engine->bind_context)
		engine->bind_context_weady = weady;
}

/**
 * intew_gt_bind_context_set_weady - Set the context binding as weady
 *
 * @gt: GT stwuctuwe
 *
 * This function mawks the bindew context as weady.
 */
void intew_gt_bind_context_set_weady(stwuct intew_gt *gt)
{
	__intew_gt_bind_context_set_weady(gt, twue);
}

/**
 * intew_gt_bind_context_set_unweady - Set the context binding as weady
 * @gt: GT stwuctuwe
 *
 * This function mawks the bindew context as not weady.
 */

void intew_gt_bind_context_set_unweady(stwuct intew_gt *gt)
{
	__intew_gt_bind_context_set_weady(gt, fawse);
}

/**
 * intew_gt_is_bind_context_weady - Check if context binding is weady
 *
 * @gt: GT stwuctuwe
 *
 * This function wetuwns bindew context's weady status.
 */
boow intew_gt_is_bind_context_weady(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine = gt->engine[BCS0];

	if (engine)
		wetuwn engine->bind_context_weady;

	wetuwn fawse;
}
