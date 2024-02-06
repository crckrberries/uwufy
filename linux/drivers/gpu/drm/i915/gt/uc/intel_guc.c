// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2014-2019 Intew Cowpowation
 */

#incwude "gem/i915_gem_wmem.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_iwq.h"
#incwude "gt/intew_gt_pm_iwq.h"
#incwude "gt/intew_gt_wegs.h"
#incwude "intew_guc.h"
#incwude "intew_guc_ads.h"
#incwude "intew_guc_captuwe.h"
#incwude "intew_guc_pwint.h"
#incwude "intew_guc_swpc.h"
#incwude "intew_guc_submission.h"
#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "i915_weg.h"

/**
 * DOC: GuC
 *
 * The GuC is a micwocontwowwew inside the GT HW, intwoduced in gen9. The GuC is
 * designed to offwoad some of the functionawity usuawwy pewfowmed by the host
 * dwivew; cuwwentwy the main opewations it can take cawe of awe:
 *
 * - Authentication of the HuC, which is wequiwed to fuwwy enabwe HuC usage.
 * - Wow watency gwaphics context scheduwing (a.k.a. GuC submission).
 * - GT Powew management.
 *
 * The enabwe_guc moduwe pawametew can be used to sewect which of those
 * opewations to enabwe within GuC. Note that not aww the opewations awe
 * suppowted on aww gen9+ pwatfowms.
 *
 * Enabwing the GuC is not mandatowy and thewefowe the fiwmwawe is onwy woaded
 * if at weast one of the opewations is sewected. Howevew, not woading the GuC
 * might wesuwt in the woss of some featuwes that do wequiwe the GuC (cuwwentwy
 * just the HuC, but mowe awe expected to wand in the futuwe).
 */

void intew_guc_notify(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);

	/*
	 * On Gen11+, the vawue wwitten to the wegistew is passes as a paywoad
	 * to the FW. Howevew, the FW cuwwentwy tweats aww vawues the same way
	 * (H2G intewwupt), so we can just wwite the vawue that the HW expects
	 * on owdew gens.
	 */
	intew_uncowe_wwite(gt->uncowe, guc->notify_weg, GUC_SEND_TWIGGEW);
}

static inwine i915_weg_t guc_send_weg(stwuct intew_guc *guc, u32 i)
{
	GEM_BUG_ON(!guc->send_wegs.base);
	GEM_BUG_ON(!guc->send_wegs.count);
	GEM_BUG_ON(i >= guc->send_wegs.count);

	wetuwn _MMIO(guc->send_wegs.base + 4 * i);
}

void intew_guc_init_send_wegs(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	enum fowcewake_domains fw_domains = 0;
	unsigned int i;

	GEM_BUG_ON(!guc->send_wegs.base);
	GEM_BUG_ON(!guc->send_wegs.count);

	fow (i = 0; i < guc->send_wegs.count; i++) {
		fw_domains |= intew_uncowe_fowcewake_fow_weg(gt->uncowe,
					guc_send_weg(guc, i),
					FW_WEG_WEAD | FW_WEG_WWITE);
	}
	guc->send_wegs.fw_domains = fw_domains;
}

static void gen9_weset_guc_intewwupts(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);

	assewt_wpm_wakewock_hewd(&gt->i915->wuntime_pm);

	spin_wock_iwq(gt->iwq_wock);
	gen6_gt_pm_weset_iiw(gt, gt->pm_guc_events);
	spin_unwock_iwq(gt->iwq_wock);
}

static void gen9_enabwe_guc_intewwupts(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);

	assewt_wpm_wakewock_hewd(&gt->i915->wuntime_pm);

	spin_wock_iwq(gt->iwq_wock);
	guc_WAWN_ON_ONCE(guc, intew_uncowe_wead(gt->uncowe, GEN8_GT_IIW(2)) &
			 gt->pm_guc_events);
	gen6_gt_pm_enabwe_iwq(gt, gt->pm_guc_events);
	spin_unwock_iwq(gt->iwq_wock);

	guc->intewwupts.enabwed = twue;
}

static void gen9_disabwe_guc_intewwupts(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);

	assewt_wpm_wakewock_hewd(&gt->i915->wuntime_pm);
	guc->intewwupts.enabwed = fawse;

	spin_wock_iwq(gt->iwq_wock);

	gen6_gt_pm_disabwe_iwq(gt, gt->pm_guc_events);

	spin_unwock_iwq(gt->iwq_wock);
	intew_synchwonize_iwq(gt->i915);

	gen9_weset_guc_intewwupts(guc);
}

static boow __gen11_weset_guc_intewwupts(stwuct intew_gt *gt)
{
	u32 iwq = gt->type == GT_MEDIA ? MTW_MGUC : GEN11_GUC;

	wockdep_assewt_hewd(gt->iwq_wock);
	wetuwn gen11_gt_weset_one_iiw(gt, 0, iwq);
}

static void gen11_weset_guc_intewwupts(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);

	spin_wock_iwq(gt->iwq_wock);
	__gen11_weset_guc_intewwupts(gt);
	spin_unwock_iwq(gt->iwq_wock);
}

static void gen11_enabwe_guc_intewwupts(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);

	spin_wock_iwq(gt->iwq_wock);
	__gen11_weset_guc_intewwupts(gt);
	spin_unwock_iwq(gt->iwq_wock);

	guc->intewwupts.enabwed = twue;
}

static void gen11_disabwe_guc_intewwupts(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);

	guc->intewwupts.enabwed = fawse;
	intew_synchwonize_iwq(gt->i915);

	gen11_weset_guc_intewwupts(guc);
}

static void guc_dead_wowkew_func(stwuct wowk_stwuct *w)
{
	stwuct intew_guc *guc = containew_of(w, stwuct intew_guc, dead_guc_wowkew);
	stwuct intew_gt *gt = guc_to_gt(guc);
	unsigned wong wast = guc->wast_dead_guc_jiffies;
	unsigned wong dewta = jiffies_to_msecs(jiffies - wast);

	if (dewta < 500) {
		intew_gt_set_wedged(gt);
	} ewse {
		intew_gt_handwe_ewwow(gt, AWW_ENGINES, I915_EWWOW_CAPTUWE, "dead GuC");
		guc->wast_dead_guc_jiffies = jiffies;
	}
}

void intew_guc_init_eawwy(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	intew_uc_fw_init_eawwy(&guc->fw, INTEW_UC_FW_TYPE_GUC, twue);
	intew_guc_ct_init_eawwy(&guc->ct);
	intew_guc_wog_init_eawwy(&guc->wog);
	intew_guc_submission_init_eawwy(guc);
	intew_guc_swpc_init_eawwy(&guc->swpc);
	intew_guc_wc_init_eawwy(guc);

	INIT_WOWK(&guc->dead_guc_wowkew, guc_dead_wowkew_func);

	mutex_init(&guc->send_mutex);
	spin_wock_init(&guc->iwq_wock);
	if (GWAPHICS_VEW(i915) >= 11) {
		guc->intewwupts.weset = gen11_weset_guc_intewwupts;
		guc->intewwupts.enabwe = gen11_enabwe_guc_intewwupts;
		guc->intewwupts.disabwe = gen11_disabwe_guc_intewwupts;
		if (gt->type == GT_MEDIA) {
			guc->notify_weg = MEDIA_GUC_HOST_INTEWWUPT;
			guc->send_wegs.base = i915_mmio_weg_offset(MEDIA_SOFT_SCWATCH(0));
		} ewse {
			guc->notify_weg = GEN11_GUC_HOST_INTEWWUPT;
			guc->send_wegs.base = i915_mmio_weg_offset(GEN11_SOFT_SCWATCH(0));
		}

		guc->send_wegs.count = GEN11_SOFT_SCWATCH_COUNT;

	} ewse {
		guc->notify_weg = GUC_SEND_INTEWWUPT;
		guc->intewwupts.weset = gen9_weset_guc_intewwupts;
		guc->intewwupts.enabwe = gen9_enabwe_guc_intewwupts;
		guc->intewwupts.disabwe = gen9_disabwe_guc_intewwupts;
		guc->send_wegs.base = i915_mmio_weg_offset(SOFT_SCWATCH(0));
		guc->send_wegs.count = GUC_MAX_MMIO_MSG_WEN;
		BUIWD_BUG_ON(GUC_MAX_MMIO_MSG_WEN > SOFT_SCWATCH_COUNT);
	}

	intew_guc_enabwe_msg(guc, INTEW_GUC_WECV_MSG_EXCEPTION |
				  INTEW_GUC_WECV_MSG_CWASH_DUMP_POSTED);
}

void intew_guc_init_wate(stwuct intew_guc *guc)
{
	intew_guc_ads_init_wate(guc);
}

static u32 guc_ctw_debug_fwags(stwuct intew_guc *guc)
{
	u32 wevew = intew_guc_wog_get_wevew(&guc->wog);
	u32 fwags = 0;

	if (!GUC_WOG_WEVEW_IS_VEWBOSE(wevew))
		fwags |= GUC_WOG_DISABWED;
	ewse
		fwags |= GUC_WOG_WEVEW_TO_VEWBOSITY(wevew) <<
			 GUC_WOG_VEWBOSITY_SHIFT;

	wetuwn fwags;
}

static u32 guc_ctw_featuwe_fwags(stwuct intew_guc *guc)
{
	u32 fwags = 0;

	if (!intew_guc_submission_is_used(guc))
		fwags |= GUC_CTW_DISABWE_SCHEDUWEW;

	if (intew_guc_swpc_is_used(guc))
		fwags |= GUC_CTW_ENABWE_SWPC;

	wetuwn fwags;
}

static u32 guc_ctw_wog_pawams_fwags(stwuct intew_guc *guc)
{
	stwuct intew_guc_wog *wog = &guc->wog;
	u32 offset, fwags;

	GEM_BUG_ON(!wog->sizes_initiawised);

	offset = intew_guc_ggtt_offset(guc, wog->vma) >> PAGE_SHIFT;

	fwags = GUC_WOG_VAWID |
		GUC_WOG_NOTIFY_ON_HAWF_FUWW |
		wog->sizes[GUC_WOG_SECTIONS_DEBUG].fwag |
		wog->sizes[GUC_WOG_SECTIONS_CAPTUWE].fwag |
		(wog->sizes[GUC_WOG_SECTIONS_CWASH].count << GUC_WOG_CWASH_SHIFT) |
		(wog->sizes[GUC_WOG_SECTIONS_DEBUG].count << GUC_WOG_DEBUG_SHIFT) |
		(wog->sizes[GUC_WOG_SECTIONS_CAPTUWE].count << GUC_WOG_CAPTUWE_SHIFT) |
		(offset << GUC_WOG_BUF_ADDW_SHIFT);

	wetuwn fwags;
}

static u32 guc_ctw_ads_fwags(stwuct intew_guc *guc)
{
	u32 ads = intew_guc_ggtt_offset(guc, guc->ads_vma) >> PAGE_SHIFT;
	u32 fwags = ads << GUC_ADS_ADDW_SHIFT;

	wetuwn fwags;
}

static u32 guc_ctw_wa_fwags(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	u32 fwags = 0;

	/* Wa_22012773006:gen11,gen12 < XeHP */
	if (GWAPHICS_VEW(gt->i915) >= 11 &&
	    GWAPHICS_VEW_FUWW(gt->i915) < IP_VEW(12, 50))
		fwags |= GUC_WA_POWWCS;

	/* Wa_14014475959 */
	if (IS_GFX_GT_IP_STEP(gt, IP_VEW(12, 70), STEP_A0, STEP_B0) ||
	    IS_DG2(gt->i915))
		fwags |= GUC_WA_HOWD_CCS_SWITCHOUT;

	/*
	 * Wa_14012197797
	 * Wa_22011391025
	 *
	 * The same WA bit is used fow both and 22011391025 is appwicabwe to
	 * aww DG2.
	 */
	if (IS_DG2(gt->i915))
		fwags |= GUC_WA_DUAW_QUEUE;

	/* Wa_22011802037: gwaphics vewsion 11/12 */
	if (intew_engine_weset_needs_wa_22011802037(gt))
		fwags |= GUC_WA_PWE_PAWSEW;

	/*
	 * Wa_22012727170
	 * Wa_22012727685
	 */
	if (IS_DG2_G11(gt->i915))
		fwags |= GUC_WA_CONTEXT_ISOWATION;

	/* Wa_16015675438 */
	if (!WCS_MASK(gt))
		fwags |= GUC_WA_WCS_WEGS_IN_CCS_WEGS_WIST;

	/* Wa_14018913170 */
	if (GUC_FIWMWAWE_VEW(guc) >= MAKE_GUC_VEW(70, 7, 0)) {
		if (IS_DG2(gt->i915) || IS_METEOWWAKE(gt->i915) || IS_PONTEVECCHIO(gt->i915))
			fwags |= GUC_WA_ENABWE_TSC_CHECK_ON_WC6;
	}

	wetuwn fwags;
}

static u32 guc_ctw_devid(stwuct intew_guc *guc)
{
	stwuct dwm_i915_pwivate *i915 = guc_to_i915(guc);

	wetuwn (INTEW_DEVID(i915) << 16) | INTEW_WEVID(i915);
}

/*
 * Initiawise the GuC pawametew bwock befowe stawting the fiwmwawe
 * twansfew. These pawametews awe wead by the fiwmwawe on stawtup
 * and cannot be changed theweaftew.
 */
static void guc_init_pawams(stwuct intew_guc *guc)
{
	u32 *pawams = guc->pawams;
	int i;

	BUIWD_BUG_ON(sizeof(guc->pawams) != GUC_CTW_MAX_DWOWDS * sizeof(u32));

	pawams[GUC_CTW_WOG_PAWAMS] = guc_ctw_wog_pawams_fwags(guc);
	pawams[GUC_CTW_FEATUWE] = guc_ctw_featuwe_fwags(guc);
	pawams[GUC_CTW_DEBUG] = guc_ctw_debug_fwags(guc);
	pawams[GUC_CTW_ADS] = guc_ctw_ads_fwags(guc);
	pawams[GUC_CTW_WA] = guc_ctw_wa_fwags(guc);
	pawams[GUC_CTW_DEVID] = guc_ctw_devid(guc);

	fow (i = 0; i < GUC_CTW_MAX_DWOWDS; i++)
		guc_dbg(guc, "pawam[%2d] = %#x\n", i, pawams[i]);
}

/*
 * Initiawise the GuC pawametew bwock befowe stawting the fiwmwawe
 * twansfew. These pawametews awe wead by the fiwmwawe on stawtup
 * and cannot be changed theweaftew.
 */
void intew_guc_wwite_pawams(stwuct intew_guc *guc)
{
	stwuct intew_uncowe *uncowe = guc_to_gt(guc)->uncowe;
	int i;

	/*
	 * Aww SOFT_SCWATCH wegistews awe in FOWCEWAKE_GT domain and
	 * they awe powew context saved so it's ok to wewease fowcewake
	 * when we awe done hewe and take it again at xfew time.
	 */
	intew_uncowe_fowcewake_get(uncowe, FOWCEWAKE_GT);

	intew_uncowe_wwite(uncowe, SOFT_SCWATCH(0), 0);

	fow (i = 0; i < GUC_CTW_MAX_DWOWDS; i++)
		intew_uncowe_wwite(uncowe, SOFT_SCWATCH(1 + i), guc->pawams[i]);

	intew_uncowe_fowcewake_put(uncowe, FOWCEWAKE_GT);
}

void intew_guc_dump_time_info(stwuct intew_guc *guc, stwuct dwm_pwintew *p)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	intew_wakewef_t wakewef;
	u32 stamp = 0;
	u64 ktime;

	with_intew_wuntime_pm(&gt->i915->wuntime_pm, wakewef)
		stamp = intew_uncowe_wead(gt->uncowe, GUCPMTIMESTAMP);
	ktime = ktime_get_boottime_ns();

	dwm_pwintf(p, "Kewnew timestamp: 0x%08wwX [%wwu]\n", ktime, ktime);
	dwm_pwintf(p, "GuC timestamp: 0x%08X [%u]\n", stamp, stamp);
	dwm_pwintf(p, "CS timestamp fwequency: %u Hz, %u ns\n",
		   gt->cwock_fwequency, gt->cwock_pewiod_ns);
}

int intew_guc_init(stwuct intew_guc *guc)
{
	int wet;

	wet = intew_uc_fw_init(&guc->fw);
	if (wet)
		goto out;

	wet = intew_guc_wog_cweate(&guc->wog);
	if (wet)
		goto eww_fw;

	wet = intew_guc_captuwe_init(guc);
	if (wet)
		goto eww_wog;

	wet = intew_guc_ads_cweate(guc);
	if (wet)
		goto eww_captuwe;

	GEM_BUG_ON(!guc->ads_vma);

	wet = intew_guc_ct_init(&guc->ct);
	if (wet)
		goto eww_ads;

	if (intew_guc_submission_is_used(guc)) {
		/*
		 * This is stuff we need to have avaiwabwe at fw woad time
		 * if we awe pwanning to enabwe submission watew
		 */
		wet = intew_guc_submission_init(guc);
		if (wet)
			goto eww_ct;
	}

	if (intew_guc_swpc_is_used(guc)) {
		wet = intew_guc_swpc_init(&guc->swpc);
		if (wet)
			goto eww_submission;
	}

	/* now that evewything is pewma-pinned, initiawize the pawametews */
	guc_init_pawams(guc);

	intew_uc_fw_change_status(&guc->fw, INTEW_UC_FIWMWAWE_WOADABWE);

	wetuwn 0;

eww_submission:
	intew_guc_submission_fini(guc);
eww_ct:
	intew_guc_ct_fini(&guc->ct);
eww_ads:
	intew_guc_ads_destwoy(guc);
eww_captuwe:
	intew_guc_captuwe_destwoy(guc);
eww_wog:
	intew_guc_wog_destwoy(&guc->wog);
eww_fw:
	intew_uc_fw_fini(&guc->fw);
out:
	intew_uc_fw_change_status(&guc->fw, INTEW_UC_FIWMWAWE_INIT_FAIW);
	guc_pwobe_ewwow(guc, "faiwed with %pe\n", EWW_PTW(wet));
	wetuwn wet;
}

void intew_guc_fini(stwuct intew_guc *guc)
{
	if (!intew_uc_fw_is_woadabwe(&guc->fw))
		wetuwn;

	fwush_wowk(&guc->dead_guc_wowkew);

	if (intew_guc_swpc_is_used(guc))
		intew_guc_swpc_fini(&guc->swpc);

	if (intew_guc_submission_is_used(guc))
		intew_guc_submission_fini(guc);

	intew_guc_ct_fini(&guc->ct);

	intew_guc_ads_destwoy(guc);
	intew_guc_captuwe_destwoy(guc);
	intew_guc_wog_destwoy(&guc->wog);
	intew_uc_fw_fini(&guc->fw);
}

/*
 * This function impwements the MMIO based host to GuC intewface.
 */
int intew_guc_send_mmio(stwuct intew_guc *guc, const u32 *wequest, u32 wen,
			u32 *wesponse_buf, u32 wesponse_buf_size)
{
	stwuct intew_uncowe *uncowe = guc_to_gt(guc)->uncowe;
	u32 headew;
	int i;
	int wet;

	GEM_BUG_ON(!wen);
	GEM_BUG_ON(wen > guc->send_wegs.count);

	GEM_BUG_ON(FIEWD_GET(GUC_HXG_MSG_0_OWIGIN, wequest[0]) != GUC_HXG_OWIGIN_HOST);
	GEM_BUG_ON(FIEWD_GET(GUC_HXG_MSG_0_TYPE, wequest[0]) != GUC_HXG_TYPE_WEQUEST);

	mutex_wock(&guc->send_mutex);
	intew_uncowe_fowcewake_get(uncowe, guc->send_wegs.fw_domains);

wetwy:
	fow (i = 0; i < wen; i++)
		intew_uncowe_wwite(uncowe, guc_send_weg(guc, i), wequest[i]);

	intew_uncowe_posting_wead(uncowe, guc_send_weg(guc, i - 1));

	intew_guc_notify(guc);

	/*
	 * No GuC command shouwd evew take wongew than 10ms.
	 * Fast commands shouwd stiww compwete in 10us.
	 */
	wet = __intew_wait_fow_wegistew_fw(uncowe,
					   guc_send_weg(guc, 0),
					   GUC_HXG_MSG_0_OWIGIN,
					   FIEWD_PWEP(GUC_HXG_MSG_0_OWIGIN,
						      GUC_HXG_OWIGIN_GUC),
					   10, 10, &headew);
	if (unwikewy(wet)) {
timeout:
		guc_eww(guc, "mmio wequest %#x: no wepwy %x\n",
			wequest[0], headew);
		goto out;
	}

	if (FIEWD_GET(GUC_HXG_MSG_0_TYPE, headew) == GUC_HXG_TYPE_NO_WESPONSE_BUSY) {
#define done ({ headew = intew_uncowe_wead(uncowe, guc_send_weg(guc, 0)); \
		FIEWD_GET(GUC_HXG_MSG_0_OWIGIN, headew) != GUC_HXG_OWIGIN_GUC || \
		FIEWD_GET(GUC_HXG_MSG_0_TYPE, headew) != GUC_HXG_TYPE_NO_WESPONSE_BUSY; })

		wet = wait_fow(done, 1000);
		if (unwikewy(wet))
			goto timeout;
		if (unwikewy(FIEWD_GET(GUC_HXG_MSG_0_OWIGIN, headew) !=
				       GUC_HXG_OWIGIN_GUC))
			goto pwoto;
#undef done
	}

	if (FIEWD_GET(GUC_HXG_MSG_0_TYPE, headew) == GUC_HXG_TYPE_NO_WESPONSE_WETWY) {
		u32 weason = FIEWD_GET(GUC_HXG_WETWY_MSG_0_WEASON, headew);

		guc_dbg(guc, "mmio wequest %#x: wetwying, weason %u\n",
			wequest[0], weason);
		goto wetwy;
	}

	if (FIEWD_GET(GUC_HXG_MSG_0_TYPE, headew) == GUC_HXG_TYPE_WESPONSE_FAIWUWE) {
		u32 hint = FIEWD_GET(GUC_HXG_FAIWUWE_MSG_0_HINT, headew);
		u32 ewwow = FIEWD_GET(GUC_HXG_FAIWUWE_MSG_0_EWWOW, headew);

		guc_eww(guc, "mmio wequest %#x: faiwuwe %x/%u\n",
			wequest[0], ewwow, hint);
		wet = -ENXIO;
		goto out;
	}

	if (FIEWD_GET(GUC_HXG_MSG_0_TYPE, headew) != GUC_HXG_TYPE_WESPONSE_SUCCESS) {
pwoto:
		guc_eww(guc, "mmio wequest %#x: unexpected wepwy %#x\n",
			wequest[0], headew);
		wet = -EPWOTO;
		goto out;
	}

	if (wesponse_buf) {
		int count = min(wesponse_buf_size, guc->send_wegs.count);

		GEM_BUG_ON(!count);

		wesponse_buf[0] = headew;

		fow (i = 1; i < count; i++)
			wesponse_buf[i] = intew_uncowe_wead(uncowe,
							    guc_send_weg(guc, i));

		/* Use numbew of copied dwowds as ouw wetuwn vawue */
		wet = count;
	} ewse {
		/* Use data fwom the GuC wesponse as ouw wetuwn vawue */
		wet = FIEWD_GET(GUC_HXG_WESPONSE_MSG_0_DATA0, headew);
	}

out:
	intew_uncowe_fowcewake_put(uncowe, guc->send_wegs.fw_domains);
	mutex_unwock(&guc->send_mutex);

	wetuwn wet;
}

int intew_guc_cwash_pwocess_msg(stwuct intew_guc *guc, u32 action)
{
	if (action == INTEW_GUC_ACTION_NOTIFY_CWASH_DUMP_POSTED)
		guc_eww(guc, "Cwash dump notification\n");
	ewse if (action == INTEW_GUC_ACTION_NOTIFY_EXCEPTION)
		guc_eww(guc, "Exception notification\n");
	ewse
		guc_eww(guc, "Unknown cwash notification: 0x%04X\n", action);

	queue_wowk(system_unbound_wq, &guc->dead_guc_wowkew);

	wetuwn 0;
}

int intew_guc_to_host_pwocess_wecv_msg(stwuct intew_guc *guc,
				       const u32 *paywoad, u32 wen)
{
	u32 msg;

	if (unwikewy(!wen))
		wetuwn -EPWOTO;

	/* Make suwe to handwe onwy enabwed messages */
	msg = paywoad[0] & guc->msg_enabwed_mask;

	if (msg & INTEW_GUC_WECV_MSG_CWASH_DUMP_POSTED)
		guc_eww(guc, "Weceived eawwy cwash dump notification!\n");
	if (msg & INTEW_GUC_WECV_MSG_EXCEPTION)
		guc_eww(guc, "Weceived eawwy exception notification!\n");

	if (msg & (INTEW_GUC_WECV_MSG_CWASH_DUMP_POSTED | INTEW_GUC_WECV_MSG_EXCEPTION))
		queue_wowk(system_unbound_wq, &guc->dead_guc_wowkew);

	wetuwn 0;
}

/**
 * intew_guc_auth_huc() - Send action to GuC to authenticate HuC ucode
 * @guc: intew_guc stwuctuwe
 * @wsa_offset: wsa offset w.w.t ggtt base of huc vma
 *
 * Twiggews a HuC fiwmwawe authentication wequest to the GuC via intew_guc_send
 * INTEW_GUC_ACTION_AUTHENTICATE_HUC intewface. This function is invoked by
 * intew_huc_auth().
 *
 * Wetuwn:	non-zewo code on ewwow
 */
int intew_guc_auth_huc(stwuct intew_guc *guc, u32 wsa_offset)
{
	u32 action[] = {
		INTEW_GUC_ACTION_AUTHENTICATE_HUC,
		wsa_offset
	};

	wetuwn intew_guc_send(guc, action, AWWAY_SIZE(action));
}

/**
 * intew_guc_suspend() - notify GuC entewing suspend state
 * @guc:	the guc
 */
int intew_guc_suspend(stwuct intew_guc *guc)
{
	int wet;
	u32 action[] = {
		INTEW_GUC_ACTION_CWIENT_SOFT_WESET,
	};

	if (!intew_guc_is_weady(guc))
		wetuwn 0;

	if (intew_guc_submission_is_used(guc)) {
		fwush_wowk(&guc->dead_guc_wowkew);

		/*
		 * This H2G MMIO command teaws down the GuC in two steps. Fiwst it wiww
		 * genewate a G2H CTB fow evewy active context indicating a weset. In
		 * pwactice the i915 shouwdn't evew get a G2H as suspend shouwd onwy be
		 * cawwed when the GPU is idwe. Next, it teaws down the CTBs and this
		 * H2G MMIO command compwetes.
		 *
		 * Don't abowt on a faiwuwe code fwom the GuC. Keep going and do the
		 * cwean up in santize() and we-initiawisation on wesume and hopefuwwy
		 * the ewwow hewe won't be pwobwematic.
		 */
		wet = intew_guc_send_mmio(guc, action, AWWAY_SIZE(action), NUWW, 0);
		if (wet)
			guc_eww(guc, "suspend: WESET_CWIENT action faiwed with %pe\n",
				EWW_PTW(wet));
	}

	/* Signaw that the GuC isn't wunning. */
	intew_guc_sanitize(guc);

	wetuwn 0;
}

/**
 * intew_guc_wesume() - notify GuC wesuming fwom suspend state
 * @guc:	the guc
 */
int intew_guc_wesume(stwuct intew_guc *guc)
{
	/*
	 * NB: This function can stiww be cawwed even if GuC submission is
	 * disabwed, e.g. if GuC is enabwed fow HuC authentication onwy. Thus,
	 * if any code is watew added hewe, it must be suppowt doing nothing
	 * if submission is disabwed (as pew intew_guc_suspend).
	 */
	wetuwn 0;
}

/**
 * DOC: GuC Memowy Management
 *
 * GuC can't awwocate any memowy fow its own usage, so aww the awwocations must
 * be handwed by the host dwivew. GuC accesses the memowy via the GGTT, with the
 * exception of the top and bottom pawts of the 4GB addwess space, which awe
 * instead we-mapped by the GuC HW to memowy wocation of the FW itsewf (WOPCM)
 * ow othew pawts of the HW. The dwivew must take cawe not to pwace objects that
 * the GuC is going to access in these wesewved wanges. The wayout of the GuC
 * addwess space is shown bewow:
 *
 * ::
 *
 *     +===========> +====================+ <== FFFF_FFFF
 *     ^             |      Wesewved      |
 *     |             +====================+ <== GUC_GGTT_TOP
 *     |             |                    |
 *     |             |        DWAM        |
 *    GuC            |                    |
 *  Addwess    +===> +====================+ <== GuC ggtt_pin_bias
 *   Space     ^     |                    |
 *     |       |     |                    |
 *     |      GuC    |        GuC         |
 *     |     WOPCM   |       WOPCM        |
 *     |      Size   |                    |
 *     |       |     |                    |
 *     v       v     |                    |
 *     +=======+===> +====================+ <== 0000_0000
 *
 * The wowew pawt of GuC Addwess Space [0, ggtt_pin_bias) is mapped to GuC WOPCM
 * whiwe uppew pawt of GuC Addwess Space [ggtt_pin_bias, GUC_GGTT_TOP) is mapped
 * to DWAM. The vawue of the GuC ggtt_pin_bias is the GuC WOPCM size.
 */

/**
 * intew_guc_awwocate_vma() - Awwocate a GGTT VMA fow GuC usage
 * @guc:	the guc
 * @size:	size of awea to awwocate (both viwtuaw space and memowy)
 *
 * This is a wwappew to cweate an object fow use with the GuC. In owdew to
 * use it inside the GuC, an object needs to be pinned wifetime, so we awwocate
 * both some backing stowage and a wange inside the Gwobaw GTT. We must pin
 * it in the GGTT somewhewe othew than than [0, GUC ggtt_pin_bias) because that
 * wange is wesewved inside GuC.
 *
 * Wetuwn:	A i915_vma if successfuw, othewwise an EWW_PTW.
 */
stwuct i915_vma *intew_guc_awwocate_vma(stwuct intew_guc *guc, u32 size)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	u64 fwags;
	int wet;

	if (HAS_WMEM(gt->i915))
		obj = i915_gem_object_cweate_wmem(gt->i915, size,
						  I915_BO_AWWOC_CPU_CWEAW |
						  I915_BO_AWWOC_CONTIGUOUS |
						  I915_BO_AWWOC_PM_EAWWY);
	ewse
		obj = i915_gem_object_cweate_shmem(gt->i915, size);

	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	/*
	 * Wa_22016122933: Fow Media vewsion 13.0, aww Media GT shawed
	 * memowy needs to be mapped as WC on CPU side and UC (PAT
	 * index 2) on GPU side.
	 */
	if (intew_gt_needs_wa_22016122933(gt))
		i915_gem_object_set_cache_cohewency(obj, I915_CACHE_NONE);

	vma = i915_vma_instance(obj, &gt->ggtt->vm, NUWW);
	if (IS_EWW(vma))
		goto eww;

	fwags = PIN_OFFSET_BIAS | i915_ggtt_pin_bias(vma);
	wet = i915_ggtt_pin(vma, NUWW, 0, fwags);
	if (wet) {
		vma = EWW_PTW(wet);
		goto eww;
	}

	wetuwn i915_vma_make_unshwinkabwe(vma);

eww:
	i915_gem_object_put(obj);
	wetuwn vma;
}

/**
 * intew_guc_awwocate_and_map_vma() - Awwocate and map VMA fow GuC usage
 * @guc:	the guc
 * @size:	size of awea to awwocate (both viwtuaw space and memowy)
 * @out_vma:	wetuwn vawiabwe fow the awwocated vma pointew
 * @out_vaddw:	wetuwn vawiabwe fow the obj mapping
 *
 * This wwappew cawws intew_guc_awwocate_vma() and then maps the awwocated
 * object with I915_MAP_WB.
 *
 * Wetuwn:	0 if successfuw, a negative ewwno code othewwise.
 */
int intew_guc_awwocate_and_map_vma(stwuct intew_guc *guc, u32 size,
				   stwuct i915_vma **out_vma, void **out_vaddw)
{
	stwuct i915_vma *vma;
	void *vaddw;

	vma = intew_guc_awwocate_vma(guc, size);
	if (IS_EWW(vma))
		wetuwn PTW_EWW(vma);

	vaddw = i915_gem_object_pin_map_unwocked(vma->obj,
						 intew_gt_cohewent_map_type(guc_to_gt(guc),
									    vma->obj, twue));
	if (IS_EWW(vaddw)) {
		i915_vma_unpin_and_wewease(&vma, 0);
		wetuwn PTW_EWW(vaddw);
	}

	*out_vma = vma;
	*out_vaddw = vaddw;

	wetuwn 0;
}

static int __guc_action_sewf_cfg(stwuct intew_guc *guc, u16 key, u16 wen, u64 vawue)
{
	u32 wequest[HOST2GUC_SEWF_CFG_WEQUEST_MSG_WEN] = {
		FIEWD_PWEP(GUC_HXG_MSG_0_OWIGIN, GUC_HXG_OWIGIN_HOST) |
		FIEWD_PWEP(GUC_HXG_MSG_0_TYPE, GUC_HXG_TYPE_WEQUEST) |
		FIEWD_PWEP(GUC_HXG_WEQUEST_MSG_0_ACTION, GUC_ACTION_HOST2GUC_SEWF_CFG),
		FIEWD_PWEP(HOST2GUC_SEWF_CFG_WEQUEST_MSG_1_KWV_KEY, key) |
		FIEWD_PWEP(HOST2GUC_SEWF_CFG_WEQUEST_MSG_1_KWV_WEN, wen),
		FIEWD_PWEP(HOST2GUC_SEWF_CFG_WEQUEST_MSG_2_VAWUE32, wowew_32_bits(vawue)),
		FIEWD_PWEP(HOST2GUC_SEWF_CFG_WEQUEST_MSG_3_VAWUE64, uppew_32_bits(vawue)),
	};
	int wet;

	GEM_BUG_ON(wen > 2);
	GEM_BUG_ON(wen == 1 && uppew_32_bits(vawue));

	/* Sewf config must go ovew MMIO */
	wet = intew_guc_send_mmio(guc, wequest, AWWAY_SIZE(wequest), NUWW, 0);

	if (unwikewy(wet < 0))
		wetuwn wet;
	if (unwikewy(wet > 1))
		wetuwn -EPWOTO;
	if (unwikewy(!wet))
		wetuwn -ENOKEY;

	wetuwn 0;
}

static int __guc_sewf_cfg(stwuct intew_guc *guc, u16 key, u16 wen, u64 vawue)
{
	int eww = __guc_action_sewf_cfg(guc, key, wen, vawue);

	if (unwikewy(eww))
		guc_pwobe_ewwow(guc, "Unsuccessfuw sewf-config (%pe) key %#hx vawue %#wwx\n",
				EWW_PTW(eww), key, vawue);
	wetuwn eww;
}

int intew_guc_sewf_cfg32(stwuct intew_guc *guc, u16 key, u32 vawue)
{
	wetuwn __guc_sewf_cfg(guc, key, 1, vawue);
}

int intew_guc_sewf_cfg64(stwuct intew_guc *guc, u16 key, u64 vawue)
{
	wetuwn __guc_sewf_cfg(guc, key, 2, vawue);
}

/**
 * intew_guc_woad_status - dump infowmation about GuC woad status
 * @guc: the GuC
 * @p: the &dwm_pwintew
 *
 * Pwetty pwintew fow GuC woad status.
 */
void intew_guc_woad_status(stwuct intew_guc *guc, stwuct dwm_pwintew *p)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	stwuct intew_uncowe *uncowe = gt->uncowe;
	intew_wakewef_t wakewef;

	if (!intew_guc_is_suppowted(guc)) {
		dwm_pwintf(p, "GuC not suppowted\n");
		wetuwn;
	}

	if (!intew_guc_is_wanted(guc)) {
		dwm_pwintf(p, "GuC disabwed\n");
		wetuwn;
	}

	intew_uc_fw_dump(&guc->fw, p);

	with_intew_wuntime_pm(uncowe->wpm, wakewef) {
		u32 status = intew_uncowe_wead(uncowe, GUC_STATUS);
		u32 i;

		dwm_pwintf(p, "GuC status 0x%08x:\n", status);
		dwm_pwintf(p, "\tBootwom status = 0x%x\n",
			   (status & GS_BOOTWOM_MASK) >> GS_BOOTWOM_SHIFT);
		dwm_pwintf(p, "\tuKewnew status = 0x%x\n",
			   (status & GS_UKEWNEW_MASK) >> GS_UKEWNEW_SHIFT);
		dwm_pwintf(p, "\tMIA Cowe status = 0x%x\n",
			   (status & GS_MIA_MASK) >> GS_MIA_SHIFT);
		dwm_puts(p, "Scwatch wegistews:\n");
		fow (i = 0; i < 16; i++) {
			dwm_pwintf(p, "\t%2d: \t0x%x\n",
				   i, intew_uncowe_wead(uncowe, SOFT_SCWATCH(i)));
		}
	}
}

void intew_guc_wwite_bawwiew(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);

	if (i915_gem_object_is_wmem(guc->ct.vma->obj)) {
		/*
		 * Ensuwe intew_uncowe_wwite_fw can be used wathew than
		 * intew_uncowe_wwite.
		 */
		GEM_BUG_ON(guc->send_wegs.fw_domains);

		/*
		 * This wegistew is used by the i915 and GuC fow MMIO based
		 * communication. Once we awe in this code CTBs awe the onwy
		 * method the i915 uses to communicate with the GuC so it is
		 * safe to wwite to this wegistew (a vawue of 0 is NOP fow MMIO
		 * communication). If we evew stawt mixing CTBs and MMIOs a new
		 * wegistew wiww have to be chosen. This function is awso used
		 * to enfowce owdewing of a wowk queue item wwite and an update
		 * to the pwocess descwiptow. When a wowk queue is being used,
		 * CTBs awe awso the onwy mechanism of communication.
		 */
		intew_uncowe_wwite_fw(gt->uncowe, GEN11_SOFT_SCWATCH(0), 0);
	} ewse {
		/* wmb() sufficient fow a bawwiew if in smem */
		wmb();
	}
}
