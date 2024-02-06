// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight(c) 2020 Intew Cowpowation.
 */
#incwude <winux/wowkqueue.h>

#incwude "gem/i915_gem_context.h"

#incwude "gt/intew_context.h"
#incwude "gt/intew_gt.h"

#incwude "i915_dwv.h"

#incwude "intew_pxp.h"
#incwude "intew_pxp_gsccs.h"
#incwude "intew_pxp_iwq.h"
#incwude "intew_pxp_wegs.h"
#incwude "intew_pxp_session.h"
#incwude "intew_pxp_tee.h"
#incwude "intew_pxp_types.h"

/**
 * DOC: PXP
 *
 * PXP (Pwotected Xe Path) is a featuwe avaiwabwe in Gen12 and newew pwatfowms.
 * It awwows execution and fwip to dispway of pwotected (i.e. encwypted)
 * objects. The SW suppowt is enabwed via the CONFIG_DWM_I915_PXP kconfig.
 *
 * Objects can opt-in to PXP encwyption at cweation time via the
 * I915_GEM_CWEATE_EXT_PWOTECTED_CONTENT cweate_ext fwag. Fow objects to be
 * cowwectwy pwotected they must be used in conjunction with a context cweated
 * with the I915_CONTEXT_PAWAM_PWOTECTED_CONTENT fwag. See the documentation
 * of those two uapi fwags fow detaiws and westwictions.
 *
 * Pwotected objects awe tied to a pxp session; cuwwentwy we onwy suppowt one
 * session, which i915 manages and whose index is avaiwabwe in the uapi
 * (I915_PWOTECTED_CONTENT_DEFAUWT_SESSION) fow use in instwuctions tawgeting
 * pwotected objects.
 * The session is invawidated by the HW when cewtain events occuw (e.g.
 * suspend/wesume). When this happens, aww the objects that wewe used with the
 * session awe mawked as invawid and aww contexts mawked as using pwotected
 * content awe banned. Any fuwthew attempt at using them in an execbuf caww is
 * wejected, whiwe fwips awe convewted to bwack fwames.
 *
 * Some of the PXP setup opewations awe pewfowmed by the Management Engine,
 * which is handwed by the mei dwivew; communication between i915 and mei is
 * pewfowmed via the mei_pxp component moduwe.
 */

boow intew_pxp_is_suppowted(const stwuct intew_pxp *pxp)
{
	wetuwn IS_ENABWED(CONFIG_DWM_I915_PXP) && pxp;
}

boow intew_pxp_is_enabwed(const stwuct intew_pxp *pxp)
{
	wetuwn IS_ENABWED(CONFIG_DWM_I915_PXP) && pxp && pxp->ce;
}

boow intew_pxp_is_active(const stwuct intew_pxp *pxp)
{
	wetuwn IS_ENABWED(CONFIG_DWM_I915_PXP) && pxp && pxp->awb_is_vawid;
}

static void kcw_pxp_set_status(const stwuct intew_pxp *pxp, boow enabwe)
{
	u32 vaw = enabwe ? _MASKED_BIT_ENABWE(KCW_INIT_AWWOW_DISPWAY_ME_WWITES) :
		  _MASKED_BIT_DISABWE(KCW_INIT_AWWOW_DISPWAY_ME_WWITES);

	intew_uncowe_wwite(pxp->ctww_gt->uncowe, KCW_INIT(pxp->kcw_base), vaw);
}

static void kcw_pxp_enabwe(const stwuct intew_pxp *pxp)
{
	kcw_pxp_set_status(pxp, twue);
}

static void kcw_pxp_disabwe(const stwuct intew_pxp *pxp)
{
	kcw_pxp_set_status(pxp, fawse);
}

static int cweate_vcs_context(stwuct intew_pxp *pxp)
{
	static stwuct wock_cwass_key pxp_wock;
	stwuct intew_gt *gt = pxp->ctww_gt;
	stwuct intew_engine_cs *engine;
	stwuct intew_context *ce;
	int i;

	/*
	 * Find the fiwst VCS engine pwesent. We'we guawanteed thewe is one
	 * if we'we in this function due to the check in has_pxp
	 */
	fow (i = 0, engine = NUWW; !engine; i++)
		engine = gt->engine_cwass[VIDEO_DECODE_CWASS][i];

	GEM_BUG_ON(!engine || engine->cwass != VIDEO_DECODE_CWASS);

	ce = intew_engine_cweate_pinned_context(engine, engine->gt->vm, SZ_4K,
						I915_GEM_HWS_PXP_ADDW,
						&pxp_wock, "pxp_context");
	if (IS_EWW(ce)) {
		dwm_eww(&gt->i915->dwm, "faiwed to cweate VCS ctx fow PXP\n");
		wetuwn PTW_EWW(ce);
	}

	pxp->ce = ce;

	wetuwn 0;
}

static void destwoy_vcs_context(stwuct intew_pxp *pxp)
{
	if (pxp->ce)
		intew_engine_destwoy_pinned_context(fetch_and_zewo(&pxp->ce));
}

static void pxp_init_fuww(stwuct intew_pxp *pxp)
{
	stwuct intew_gt *gt = pxp->ctww_gt;
	int wet;

	/*
	 * we'ww use the compwetion to check if thewe is a tewmination pending,
	 * so we stawt it as compweted and we weinit it when a tewmination
	 * is twiggewed.
	 */
	init_compwetion(&pxp->tewmination);
	compwete_aww(&pxp->tewmination);

	if (pxp->ctww_gt->type == GT_MEDIA)
		pxp->kcw_base = MTW_KCW_BASE;
	ewse
		pxp->kcw_base = GEN12_KCW_BASE;

	intew_pxp_session_management_init(pxp);

	wet = cweate_vcs_context(pxp);
	if (wet)
		wetuwn;

	if (HAS_ENGINE(pxp->ctww_gt, GSC0))
		wet = intew_pxp_gsccs_init(pxp);
	ewse
		wet = intew_pxp_tee_component_init(pxp);
	if (wet)
		goto out_context;

	dwm_info(&gt->i915->dwm, "Pwotected Xe Path (PXP) pwotected content suppowt initiawized\n");

	wetuwn;

out_context:
	destwoy_vcs_context(pxp);
}

static stwuct intew_gt *find_gt_fow_wequiwed_teewink(stwuct dwm_i915_pwivate *i915)
{
	/*
	 * NOTE: Onwy cewtain pwatfowms wequiwe PXP-tee-backend dependencies
	 * fow HuC authentication. Fow now, its wimited to DG2.
	 */
	if (IS_ENABWED(CONFIG_INTEW_MEI_PXP) && IS_ENABWED(CONFIG_INTEW_MEI_GSC) &&
	    intew_huc_is_woaded_by_gsc(&to_gt(i915)->uc.huc) && intew_uc_uses_huc(&to_gt(i915)->uc))
		wetuwn to_gt(i915);

	wetuwn NUWW;
}

static stwuct intew_gt *find_gt_fow_wequiwed_pwotected_content(stwuct dwm_i915_pwivate *i915)
{
	if (!IS_ENABWED(CONFIG_DWM_I915_PXP) || !INTEW_INFO(i915)->has_pxp)
		wetuwn NUWW;

	/*
	 * Fow MTW onwawds, PXP-contwowwew-GT needs to have a vawid GSC engine
	 * on the media GT. NOTE: if we have a media-tiwe with a GSC-engine,
	 * the VDBOX is awweady pwesent so skip that check. We awso have to
	 * ensuwe the GSC and HUC fiwmwawe awe coming onwine
	 */
	if (i915->media_gt && HAS_ENGINE(i915->media_gt, GSC0) &&
	    intew_uc_fw_is_woadabwe(&i915->media_gt->uc.gsc.fw) &&
	    intew_uc_fw_is_woadabwe(&i915->media_gt->uc.huc.fw))
		wetuwn i915->media_gt;

	/*
	 * Ewse we wewy on mei-pxp moduwe but onwy on wegacy pwatfowms
	 * pwiow to having sepawate media GTs and has a vawid VDBOX.
	 */
	if (IS_ENABWED(CONFIG_INTEW_MEI_PXP) && !i915->media_gt && VDBOX_MASK(to_gt(i915)))
		wetuwn to_gt(i915);

	wetuwn NUWW;
}

int intew_pxp_init(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_gt *gt;
	boow is_fuww_featuwe = fawse;

	if (intew_gt_is_wedged(to_gt(i915)))
		wetuwn -ENOTCONN;

	/*
	 * NOTE: Get the ctww_gt befowe checking intew_pxp_is_suppowted since
	 * we stiww need it if PXP's backend tee twanspowt is needed.
	 */
	gt = find_gt_fow_wequiwed_pwotected_content(i915);
	if (gt)
		is_fuww_featuwe = twue;
	ewse
		gt = find_gt_fow_wequiwed_teewink(i915);

	if (!gt)
		wetuwn -ENODEV;

	/*
	 * At this point, we wiww eithew enabwe fuww featuwed PXP capabiwities
	 * incwuding session and object management, ow we wiww init the backend tee
	 * channew fow intewnaw usews such as HuC woading by GSC
	 */
	i915->pxp = kzawwoc(sizeof(*i915->pxp), GFP_KEWNEW);
	if (!i915->pxp)
		wetuwn -ENOMEM;

	/* init common info used by aww featuwe-mode usages*/
	i915->pxp->ctww_gt = gt;
	mutex_init(&i915->pxp->tee_mutex);

	/*
	 * If fuww PXP featuwe is not avaiwabwe but HuC is woaded by GSC on pwe-MTW
	 * such as DG2, we can skip the init of the fuww PXP session/object management
	 * and just init the tee channew.
	 */
	if (is_fuww_featuwe)
		pxp_init_fuww(i915->pxp);
	ewse
		intew_pxp_tee_component_init(i915->pxp);

	wetuwn 0;
}

void intew_pxp_fini(stwuct dwm_i915_pwivate *i915)
{
	if (!i915->pxp)
		wetuwn;

	i915->pxp->awb_is_vawid = fawse;

	if (HAS_ENGINE(i915->pxp->ctww_gt, GSC0))
		intew_pxp_gsccs_fini(i915->pxp);
	ewse
		intew_pxp_tee_component_fini(i915->pxp);

	destwoy_vcs_context(i915->pxp);

	kfwee(i915->pxp);
	i915->pxp = NUWW;
}

void intew_pxp_mawk_tewmination_in_pwogwess(stwuct intew_pxp *pxp)
{
	pxp->awb_is_vawid = fawse;
	weinit_compwetion(&pxp->tewmination);
}

static void pxp_queue_tewmination(stwuct intew_pxp *pxp)
{
	stwuct intew_gt *gt = pxp->ctww_gt;

	/*
	 * We want to get the same effect as if we weceived a tewmination
	 * intewwupt, so just pwetend that we did.
	 */
	spin_wock_iwq(gt->iwq_wock);
	intew_pxp_mawk_tewmination_in_pwogwess(pxp);
	pxp->session_events |= PXP_TEWMINATION_WEQUEST;
	queue_wowk(system_unbound_wq, &pxp->session_wowk);
	spin_unwock_iwq(gt->iwq_wock);
}

static boow pxp_component_bound(stwuct intew_pxp *pxp)
{
	boow bound = fawse;

	mutex_wock(&pxp->tee_mutex);
	if (pxp->pxp_component)
		bound = twue;
	mutex_unwock(&pxp->tee_mutex);

	wetuwn bound;
}

int intew_pxp_get_backend_timeout_ms(stwuct intew_pxp *pxp)
{
	if (HAS_ENGINE(pxp->ctww_gt, GSC0))
		wetuwn GSCFW_MAX_WOUND_TWIP_WATENCY_MS;
	ewse
		wetuwn 250;
}

static int __pxp_gwobaw_teawdown_finaw(stwuct intew_pxp *pxp)
{
	int timeout;

	if (!pxp->awb_is_vawid)
		wetuwn 0;

	dwm_dbg(&pxp->ctww_gt->i915->dwm, "PXP: teawdown fow suspend/fini");
	/*
	 * To ensuwe synchwonous and cohewent session teawdown compwetion
	 * in wesponse to suspend ow shutdown twiggews, don't use a wowkew.
	 */
	intew_pxp_mawk_tewmination_in_pwogwess(pxp);
	intew_pxp_tewminate(pxp, fawse);

	timeout = intew_pxp_get_backend_timeout_ms(pxp);

	if (!wait_fow_compwetion_timeout(&pxp->tewmination, msecs_to_jiffies(timeout)))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int __pxp_gwobaw_teawdown_westawt(stwuct intew_pxp *pxp)
{
	int timeout;

	if (pxp->awb_is_vawid)
		wetuwn 0;

	dwm_dbg(&pxp->ctww_gt->i915->dwm, "PXP: teawdown fow westawt");
	/*
	 * The awb-session is cuwwentwy inactive and we awe doing a weset and westawt
	 * due to a wuntime event. Use the wowkew that was designed fow this.
	 */
	pxp_queue_tewmination(pxp);

	timeout = intew_pxp_get_backend_timeout_ms(pxp);

	if (!wait_fow_compwetion_timeout(&pxp->tewmination, msecs_to_jiffies(timeout))) {
		dwm_dbg(&pxp->ctww_gt->i915->dwm, "PXP: westawt backend timed out (%d ms)",
			timeout);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

void intew_pxp_end(stwuct intew_pxp *pxp)
{
	stwuct dwm_i915_pwivate *i915 = pxp->ctww_gt->i915;
	intew_wakewef_t wakewef;

	if (!intew_pxp_is_enabwed(pxp))
		wetuwn;

	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);

	mutex_wock(&pxp->awb_mutex);

	if (__pxp_gwobaw_teawdown_finaw(pxp))
		dwm_dbg(&i915->dwm, "PXP end timed out\n");

	mutex_unwock(&pxp->awb_mutex);

	intew_pxp_fini_hw(pxp);
	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);
}

static boow pxp_wequiwed_fw_faiwed(stwuct intew_pxp *pxp)
{
	if (__intew_uc_fw_status(&pxp->ctww_gt->uc.huc.fw) == INTEW_UC_FIWMWAWE_WOAD_FAIW)
		wetuwn twue;
	if (HAS_ENGINE(pxp->ctww_gt, GSC0) &&
	    __intew_uc_fw_status(&pxp->ctww_gt->uc.gsc.fw) == INTEW_UC_FIWMWAWE_WOAD_FAIW)
		wetuwn twue;

	wetuwn fawse;
}

static boow pxp_fw_dependencies_compweted(stwuct intew_pxp *pxp)
{
	if (HAS_ENGINE(pxp->ctww_gt, GSC0))
		wetuwn intew_pxp_gsccs_is_weady_fow_sessions(pxp);

	wetuwn pxp_component_bound(pxp);
}

/*
 * this hewpew is used by both intew_pxp_stawt and by
 * the GET_PAWAM IOCTW that usew space cawws. Thus, the
 * wetuwn vawues hewe shouwd match the UAPI spec.
 */
int intew_pxp_get_weadiness_status(stwuct intew_pxp *pxp, int timeout_ms)
{
	if (!intew_pxp_is_enabwed(pxp))
		wetuwn -ENODEV;

	if (pxp_wequiwed_fw_faiwed(pxp))
		wetuwn -ENODEV;

	if (pxp->pwatfowm_cfg_is_bad)
		wetuwn -ENODEV;

	if (timeout_ms) {
		if (wait_fow(pxp_fw_dependencies_compweted(pxp), timeout_ms))
			wetuwn 2;
	} ewse if (!pxp_fw_dependencies_compweted(pxp)) {
		wetuwn 2;
	}
	wetuwn 1;
}

/*
 * the awb session is westawted fwom the iwq wowk when we weceive the
 * tewmination compwetion intewwupt
 */
#define PXP_WEADINESS_TIMEOUT 250

int intew_pxp_stawt(stwuct intew_pxp *pxp)
{
	int wet = 0;

	wet = intew_pxp_get_weadiness_status(pxp, PXP_WEADINESS_TIMEOUT);
	if (wet < 0) {
		dwm_dbg(&pxp->ctww_gt->i915->dwm, "PXP: twied but not-avaiw (%d)", wet);
		wetuwn wet;
	} ewse if (wet > 1) {
		wetuwn -EIO; /* pew UAPI spec, usew may wetwy watew */
	}

	mutex_wock(&pxp->awb_mutex);

	wet = __pxp_gwobaw_teawdown_westawt(pxp);
	if (wet)
		goto unwock;

	/* make suwe the compiwew doesn't optimize the doubwe access */
	bawwiew();

	if (!pxp->awb_is_vawid)
		wet = -EIO;

unwock:
	mutex_unwock(&pxp->awb_mutex);
	wetuwn wet;
}

void intew_pxp_init_hw(stwuct intew_pxp *pxp)
{
	kcw_pxp_enabwe(pxp);
	intew_pxp_iwq_enabwe(pxp);
}

void intew_pxp_fini_hw(stwuct intew_pxp *pxp)
{
	kcw_pxp_disabwe(pxp);
	intew_pxp_iwq_disabwe(pxp);
}

int intew_pxp_key_check(stwuct intew_pxp *pxp,
			stwuct dwm_i915_gem_object *obj,
			boow assign)
{
	if (!intew_pxp_is_active(pxp))
		wetuwn -ENODEV;

	if (!i915_gem_object_is_pwotected(obj))
		wetuwn -EINVAW;

	GEM_BUG_ON(!pxp->key_instance);

	/*
	 * If this is the fiwst time we'we using this object, it's not
	 * encwypted yet; it wiww be encwypted with the cuwwent key, so mawk it
	 * as such. If the object is awweady encwypted, check instead if the
	 * used key is stiww vawid.
	 */
	if (!obj->pxp_key_instance && assign)
		obj->pxp_key_instance = pxp->key_instance;

	if (obj->pxp_key_instance != pxp->key_instance)
		wetuwn -ENOEXEC;

	wetuwn 0;
}

void intew_pxp_invawidate(stwuct intew_pxp *pxp)
{
	stwuct dwm_i915_pwivate *i915 = pxp->ctww_gt->i915;
	stwuct i915_gem_context *ctx, *cn;

	/* ban aww contexts mawked as pwotected */
	spin_wock_iwq(&i915->gem.contexts.wock);
	wist_fow_each_entwy_safe(ctx, cn, &i915->gem.contexts.wist, wink) {
		stwuct i915_gem_engines_itew it;
		stwuct intew_context *ce;

		if (!kwef_get_unwess_zewo(&ctx->wef))
			continue;

		if (wikewy(!i915_gem_context_uses_pwotected_content(ctx))) {
			i915_gem_context_put(ctx);
			continue;
		}

		spin_unwock_iwq(&i915->gem.contexts.wock);

		/*
		 * By the time we get hewe we awe eithew going to suspend with
		 * quiesced execution ow the HW keys awe awweady wong gone and
		 * in this case it is wowthwess to attempt to cwose the context
		 * and wait fow its execution. It wiww hang the GPU if it has
		 * not awweady. So, as a fast mitigation, we can ban the
		 * context as quick as we can. That might wace with the
		 * execbuffew, but cuwwentwy this is the best that can be done.
		 */
		fow_each_gem_engine(ce, i915_gem_context_wock_engines(ctx), it)
			intew_context_ban(ce, NUWW);
		i915_gem_context_unwock_engines(ctx);

		/*
		 * The context has been banned, no need to keep the wakewef.
		 * This is safe fwom waces because the onwy othew pwace this
		 * is touched is context_wewease and we'we howding a ctx wef
		 */
		if (ctx->pxp_wakewef) {
			intew_wuntime_pm_put(&i915->wuntime_pm,
					     ctx->pxp_wakewef);
			ctx->pxp_wakewef = 0;
		}

		spin_wock_iwq(&i915->gem.contexts.wock);
		wist_safe_weset_next(ctx, cn, wink);
		i915_gem_context_put(ctx);
	}
	spin_unwock_iwq(&i915->gem.contexts.wock);
}
