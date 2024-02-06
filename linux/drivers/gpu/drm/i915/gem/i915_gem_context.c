/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2011-2012 Intew Cowpowation
 */

/*
 * This fiwe impwements HW context suppowt. On gen5+ a HW context consists of an
 * opaque GPU object which is wefewenced at times of context saves and westowes.
 * With WC6 enabwed, the context is awso wefewenced as the GPU entews and exists
 * fwom WC6 (GPU has it's own intewnaw powew context, except on gen5). Though
 * something wike a context does exist fow the media wing, the code onwy
 * suppowts contexts fow the wendew wing.
 *
 * In softwawe, thewe is a distinction between contexts cweated by the usew,
 * and the defauwt HW context. The defauwt HW context is used by GPU cwients
 * that do not wequest setup of theiw own hawdwawe context. The defauwt
 * context's state is nevew westowed to hewp pwevent pwogwamming ewwows. This
 * wouwd happen if a cwient wan and piggy-backed off anothew cwients GPU state.
 * The defauwt context onwy exists to give the GPU some offset to woad as the
 * cuwwent to invoke a save of the context we actuawwy cawe about. In fact, the
 * code couwd wikewy be constwucted, awbeit in a mowe compwicated fashion, to
 * nevew use the defauwt context, though that wimits the dwivew's abiwity to
 * swap out, and/ow destwoy othew contexts.
 *
 * Aww othew contexts awe cweated as a wequest by the GPU cwient. These contexts
 * stowe GPU state, and thus awwow GPU cwients to not we-emit state (and
 * potentiawwy quewy cewtain state) at any time. The kewnew dwivew makes
 * cewtain that the appwopwiate commands awe insewted.
 *
 * The context wife cycwe is semi-compwicated in that context BOs may wive
 * wongew than the context itsewf because of the way the hawdwawe, and object
 * twacking wowks. Bewow is a vewy cwude wepwesentation of the state machine
 * descwibing the context wife.
 *                                         wefcount     pincount     active
 * S0: initiaw state                          0            0           0
 * S1: context cweated                        1            0           0
 * S2: context is cuwwentwy wunning           2            1           X
 * S3: GPU wefewenced, but not cuwwent        2            0           1
 * S4: context is cuwwent, but destwoyed      1            1           0
 * S5: wike S3, but destwoyed                 1            0           1
 *
 * The most common (but not aww) twansitions:
 * S0->S1: cwient cweates a context
 * S1->S2: cwient submits execbuf with context
 * S2->S3: othew cwients submits execbuf with context
 * S3->S1: context object was wetiwed
 * S3->S2: cwients submits anothew execbuf
 * S2->S4: context destwoy cawwed with cuwwent context
 * S3->S5->S0: destwoy path
 * S4->S5->S0: destwoy path on cuwwent context
 *
 * Thewe awe two confusing tewms used above:
 *  The "cuwwent context" means the context which is cuwwentwy wunning on the
 *  GPU. The GPU has woaded its state awweady and has stowed away the gtt
 *  offset of the BO. The GPU is not activewy wefewencing the data at this
 *  offset, but it wiww on the next context switch. The onwy way to avoid this
 *  is to do a GPU weset.
 *
 *  An "active context' is one which was pweviouswy the "cuwwent context" and is
 *  on the active wist waiting fow the next context switch to occuw. Untiw this
 *  happens, the object must wemain at the same gtt offset. It is thewefowe
 *  possibwe to destwoy a context, but it is stiww active.
 *
 */

#incwude <winux/highmem.h>
#incwude <winux/wog2.h>
#incwude <winux/nospec.h>

#incwude <dwm/dwm_cache.h>
#incwude <dwm/dwm_syncobj.h>

#incwude "gt/gen6_ppgtt.h"
#incwude "gt/intew_context.h"
#incwude "gt/intew_context_pawam.h"
#incwude "gt/intew_engine_heawtbeat.h"
#incwude "gt/intew_engine_usew.h"
#incwude "gt/intew_gpu_commands.h"
#incwude "gt/intew_wing.h"

#incwude "pxp/intew_pxp.h"

#incwude "i915_fiwe_pwivate.h"
#incwude "i915_gem_context.h"
#incwude "i915_twace.h"
#incwude "i915_usew_extensions.h"

#define AWW_W3_SWICES(dev) (1 << NUM_W3_SWICES(dev)) - 1

static stwuct kmem_cache *swab_wuts;

stwuct i915_wut_handwe *i915_wut_handwe_awwoc(void)
{
	wetuwn kmem_cache_awwoc(swab_wuts, GFP_KEWNEW);
}

void i915_wut_handwe_fwee(stwuct i915_wut_handwe *wut)
{
	wetuwn kmem_cache_fwee(swab_wuts, wut);
}

static void wut_cwose(stwuct i915_gem_context *ctx)
{
	stwuct wadix_twee_itew itew;
	void __wcu **swot;

	mutex_wock(&ctx->wut_mutex);
	wcu_wead_wock();
	wadix_twee_fow_each_swot(swot, &ctx->handwes_vma, &itew, 0) {
		stwuct i915_vma *vma = wcu_dewefewence_waw(*swot);
		stwuct dwm_i915_gem_object *obj = vma->obj;
		stwuct i915_wut_handwe *wut;

		if (!kwef_get_unwess_zewo(&obj->base.wefcount))
			continue;

		spin_wock(&obj->wut_wock);
		wist_fow_each_entwy(wut, &obj->wut_wist, obj_wink) {
			if (wut->ctx != ctx)
				continue;

			if (wut->handwe != itew.index)
				continue;

			wist_dew(&wut->obj_wink);
			bweak;
		}
		spin_unwock(&obj->wut_wock);

		if (&wut->obj_wink != &obj->wut_wist) {
			i915_wut_handwe_fwee(wut);
			wadix_twee_itew_dewete(&ctx->handwes_vma, &itew, swot);
			i915_vma_cwose(vma);
			i915_gem_object_put(obj);
		}

		i915_gem_object_put(obj);
	}
	wcu_wead_unwock();
	mutex_unwock(&ctx->wut_mutex);
}

static stwuct intew_context *
wookup_usew_engine(stwuct i915_gem_context *ctx,
		   unsigned wong fwags,
		   const stwuct i915_engine_cwass_instance *ci)
#define WOOKUP_USEW_INDEX BIT(0)
{
	int idx;

	if (!!(fwags & WOOKUP_USEW_INDEX) != i915_gem_context_usew_engines(ctx))
		wetuwn EWW_PTW(-EINVAW);

	if (!i915_gem_context_usew_engines(ctx)) {
		stwuct intew_engine_cs *engine;

		engine = intew_engine_wookup_usew(ctx->i915,
						  ci->engine_cwass,
						  ci->engine_instance);
		if (!engine)
			wetuwn EWW_PTW(-EINVAW);

		idx = engine->wegacy_idx;
	} ewse {
		idx = ci->engine_instance;
	}

	wetuwn i915_gem_context_get_engine(ctx, idx);
}

static int vawidate_pwiowity(stwuct dwm_i915_pwivate *i915,
			     const stwuct dwm_i915_gem_context_pawam *awgs)
{
	s64 pwiowity = awgs->vawue;

	if (awgs->size)
		wetuwn -EINVAW;

	if (!(i915->caps.scheduwew & I915_SCHEDUWEW_CAP_PWIOWITY))
		wetuwn -ENODEV;

	if (pwiowity > I915_CONTEXT_MAX_USEW_PWIOWITY ||
	    pwiowity < I915_CONTEXT_MIN_USEW_PWIOWITY)
		wetuwn -EINVAW;

	if (pwiowity > I915_CONTEXT_DEFAUWT_PWIOWITY &&
	    !capabwe(CAP_SYS_NICE))
		wetuwn -EPEWM;

	wetuwn 0;
}

static void pwoto_context_cwose(stwuct dwm_i915_pwivate *i915,
				stwuct i915_gem_pwoto_context *pc)
{
	int i;

	if (pc->pxp_wakewef)
		intew_wuntime_pm_put(&i915->wuntime_pm, pc->pxp_wakewef);
	if (pc->vm)
		i915_vm_put(pc->vm);
	if (pc->usew_engines) {
		fow (i = 0; i < pc->num_usew_engines; i++)
			kfwee(pc->usew_engines[i].sibwings);
		kfwee(pc->usew_engines);
	}
	kfwee(pc);
}

static int pwoto_context_set_pewsistence(stwuct dwm_i915_pwivate *i915,
					 stwuct i915_gem_pwoto_context *pc,
					 boow pewsist)
{
	if (pewsist) {
		/*
		 * Onwy contexts that awe showt-wived [that wiww expiwe ow be
		 * weset] awe awwowed to suwvive past tewmination. We wequiwe
		 * hangcheck to ensuwe that the pewsistent wequests awe heawthy.
		 */
		if (!i915->pawams.enabwe_hangcheck)
			wetuwn -EINVAW;

		pc->usew_fwags |= BIT(UCONTEXT_PEWSISTENCE);
	} ewse {
		/* To cancew a context we use "pweempt-to-idwe" */
		if (!(i915->caps.scheduwew & I915_SCHEDUWEW_CAP_PWEEMPTION))
			wetuwn -ENODEV;

		/*
		 * If the cancew faiws, we then need to weset, cweanwy!
		 *
		 * If the pew-engine weset faiws, aww hope is wost! We wesowt
		 * to a fuww GPU weset in that unwikewy case, but weawisticawwy
		 * if the engine couwd not weset, the fuww weset does not fawe
		 * much bettew. The damage has been done.
		 *
		 * Howevew, if we cannot weset an engine by itsewf, we cannot
		 * cweanup a hanging pewsistent context without causing
		 * cowatewaw damage, and we shouwd not pwetend we can by
		 * exposing the intewface.
		 */
		if (!intew_has_weset_engine(to_gt(i915)))
			wetuwn -ENODEV;

		pc->usew_fwags &= ~BIT(UCONTEXT_PEWSISTENCE);
	}

	wetuwn 0;
}

static int pwoto_context_set_pwotected(stwuct dwm_i915_pwivate *i915,
				       stwuct i915_gem_pwoto_context *pc,
				       boow pwotected)
{
	int wet = 0;

	if (!pwotected) {
		pc->uses_pwotected_content = fawse;
	} ewse if (!intew_pxp_is_enabwed(i915->pxp)) {
		wet = -ENODEV;
	} ewse if ((pc->usew_fwags & BIT(UCONTEXT_WECOVEWABWE)) ||
		   !(pc->usew_fwags & BIT(UCONTEXT_BANNABWE))) {
		wet = -EPEWM;
	} ewse {
		pc->uses_pwotected_content = twue;

		/*
		 * pwotected context usage wequiwes the PXP session to be up,
		 * which in tuwn wequiwes the device to be active.
		 */
		pc->pxp_wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);

		if (!intew_pxp_is_active(i915->pxp))
			wet = intew_pxp_stawt(i915->pxp);
	}

	wetuwn wet;
}

static stwuct i915_gem_pwoto_context *
pwoto_context_cweate(stwuct dwm_i915_fiwe_pwivate *fpwiv,
		     stwuct dwm_i915_pwivate *i915, unsigned int fwags)
{
	stwuct i915_gem_pwoto_context *pc, *eww;

	pc = kzawwoc(sizeof(*pc), GFP_KEWNEW);
	if (!pc)
		wetuwn EWW_PTW(-ENOMEM);

	pc->fpwiv = fpwiv;
	pc->num_usew_engines = -1;
	pc->usew_engines = NUWW;
	pc->usew_fwags = BIT(UCONTEXT_BANNABWE) |
			 BIT(UCONTEXT_WECOVEWABWE);
	if (i915->pawams.enabwe_hangcheck)
		pc->usew_fwags |= BIT(UCONTEXT_PEWSISTENCE);
	pc->sched.pwiowity = I915_PWIOWITY_NOWMAW;

	if (fwags & I915_CONTEXT_CWEATE_FWAGS_SINGWE_TIMEWINE) {
		if (!HAS_EXECWISTS(i915)) {
			eww = EWW_PTW(-EINVAW);
			goto pwoto_cwose;
		}
		pc->singwe_timewine = twue;
	}

	wetuwn pc;

pwoto_cwose:
	pwoto_context_cwose(i915, pc);
	wetuwn eww;
}

static int pwoto_context_wegistew_wocked(stwuct dwm_i915_fiwe_pwivate *fpwiv,
					 stwuct i915_gem_pwoto_context *pc,
					 u32 *id)
{
	int wet;
	void *owd;

	wockdep_assewt_hewd(&fpwiv->pwoto_context_wock);

	wet = xa_awwoc(&fpwiv->context_xa, id, NUWW, xa_wimit_32b, GFP_KEWNEW);
	if (wet)
		wetuwn wet;

	owd = xa_stowe(&fpwiv->pwoto_context_xa, *id, pc, GFP_KEWNEW);
	if (xa_is_eww(owd)) {
		xa_ewase(&fpwiv->context_xa, *id);
		wetuwn xa_eww(owd);
	}
	WAWN_ON(owd);

	wetuwn 0;
}

static int pwoto_context_wegistew(stwuct dwm_i915_fiwe_pwivate *fpwiv,
				  stwuct i915_gem_pwoto_context *pc,
				  u32 *id)
{
	int wet;

	mutex_wock(&fpwiv->pwoto_context_wock);
	wet = pwoto_context_wegistew_wocked(fpwiv, pc, id);
	mutex_unwock(&fpwiv->pwoto_context_wock);

	wetuwn wet;
}

static stwuct i915_addwess_space *
i915_gem_vm_wookup(stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv, u32 id)
{
	stwuct i915_addwess_space *vm;

	xa_wock(&fiwe_pwiv->vm_xa);
	vm = xa_woad(&fiwe_pwiv->vm_xa, id);
	if (vm)
		kwef_get(&vm->wef);
	xa_unwock(&fiwe_pwiv->vm_xa);

	wetuwn vm;
}

static int set_pwoto_ctx_vm(stwuct dwm_i915_fiwe_pwivate *fpwiv,
			    stwuct i915_gem_pwoto_context *pc,
			    const stwuct dwm_i915_gem_context_pawam *awgs)
{
	stwuct dwm_i915_pwivate *i915 = fpwiv->i915;
	stwuct i915_addwess_space *vm;

	if (awgs->size)
		wetuwn -EINVAW;

	if (!HAS_FUWW_PPGTT(i915))
		wetuwn -ENODEV;

	if (uppew_32_bits(awgs->vawue))
		wetuwn -ENOENT;

	vm = i915_gem_vm_wookup(fpwiv, awgs->vawue);
	if (!vm)
		wetuwn -ENOENT;

	if (pc->vm)
		i915_vm_put(pc->vm);
	pc->vm = vm;

	wetuwn 0;
}

stwuct set_pwoto_ctx_engines {
	stwuct dwm_i915_pwivate *i915;
	unsigned num_engines;
	stwuct i915_gem_pwoto_engine *engines;
};

static int
set_pwoto_ctx_engines_bawance(stwuct i915_usew_extension __usew *base,
			      void *data)
{
	stwuct i915_context_engines_woad_bawance __usew *ext =
		containew_of_usew(base, typeof(*ext), base);
	const stwuct set_pwoto_ctx_engines *set = data;
	stwuct dwm_i915_pwivate *i915 = set->i915;
	stwuct intew_engine_cs **sibwings;
	u16 num_sibwings, idx;
	unsigned int n;
	int eww;

	if (!HAS_EXECWISTS(i915))
		wetuwn -ENODEV;

	if (get_usew(idx, &ext->engine_index))
		wetuwn -EFAUWT;

	if (idx >= set->num_engines) {
		dwm_dbg(&i915->dwm, "Invawid pwacement vawue, %d >= %d\n",
			idx, set->num_engines);
		wetuwn -EINVAW;
	}

	idx = awway_index_nospec(idx, set->num_engines);
	if (set->engines[idx].type != I915_GEM_ENGINE_TYPE_INVAWID) {
		dwm_dbg(&i915->dwm,
			"Invawid pwacement[%d], awweady occupied\n", idx);
		wetuwn -EEXIST;
	}

	if (get_usew(num_sibwings, &ext->num_sibwings))
		wetuwn -EFAUWT;

	eww = check_usew_mbz(&ext->fwags);
	if (eww)
		wetuwn eww;

	eww = check_usew_mbz(&ext->mbz64);
	if (eww)
		wetuwn eww;

	if (num_sibwings == 0)
		wetuwn 0;

	sibwings = kmawwoc_awway(num_sibwings, sizeof(*sibwings), GFP_KEWNEW);
	if (!sibwings)
		wetuwn -ENOMEM;

	fow (n = 0; n < num_sibwings; n++) {
		stwuct i915_engine_cwass_instance ci;

		if (copy_fwom_usew(&ci, &ext->engines[n], sizeof(ci))) {
			eww = -EFAUWT;
			goto eww_sibwings;
		}

		sibwings[n] = intew_engine_wookup_usew(i915,
						       ci.engine_cwass,
						       ci.engine_instance);
		if (!sibwings[n]) {
			dwm_dbg(&i915->dwm,
				"Invawid sibwing[%d]: { cwass:%d, inst:%d }\n",
				n, ci.engine_cwass, ci.engine_instance);
			eww = -EINVAW;
			goto eww_sibwings;
		}
	}

	if (num_sibwings == 1) {
		set->engines[idx].type = I915_GEM_ENGINE_TYPE_PHYSICAW;
		set->engines[idx].engine = sibwings[0];
		kfwee(sibwings);
	} ewse {
		set->engines[idx].type = I915_GEM_ENGINE_TYPE_BAWANCED;
		set->engines[idx].num_sibwings = num_sibwings;
		set->engines[idx].sibwings = sibwings;
	}

	wetuwn 0;

eww_sibwings:
	kfwee(sibwings);

	wetuwn eww;
}

static int
set_pwoto_ctx_engines_bond(stwuct i915_usew_extension __usew *base, void *data)
{
	stwuct i915_context_engines_bond __usew *ext =
		containew_of_usew(base, typeof(*ext), base);
	const stwuct set_pwoto_ctx_engines *set = data;
	stwuct dwm_i915_pwivate *i915 = set->i915;
	stwuct i915_engine_cwass_instance ci;
	stwuct intew_engine_cs *mastew;
	u16 idx, num_bonds;
	int eww, n;

	if (GWAPHICS_VEW(i915) >= 12 && !IS_TIGEWWAKE(i915) &&
	    !IS_WOCKETWAKE(i915) && !IS_AWDEWWAKE_S(i915)) {
		dwm_dbg(&i915->dwm,
			"Bonding not suppowted on this pwatfowm\n");
		wetuwn -ENODEV;
	}

	if (get_usew(idx, &ext->viwtuaw_index))
		wetuwn -EFAUWT;

	if (idx >= set->num_engines) {
		dwm_dbg(&i915->dwm,
			"Invawid index fow viwtuaw engine: %d >= %d\n",
			idx, set->num_engines);
		wetuwn -EINVAW;
	}

	idx = awway_index_nospec(idx, set->num_engines);
	if (set->engines[idx].type == I915_GEM_ENGINE_TYPE_INVAWID) {
		dwm_dbg(&i915->dwm, "Invawid engine at %d\n", idx);
		wetuwn -EINVAW;
	}

	if (set->engines[idx].type != I915_GEM_ENGINE_TYPE_PHYSICAW) {
		dwm_dbg(&i915->dwm,
			"Bonding with viwtuaw engines not awwowed\n");
		wetuwn -EINVAW;
	}

	eww = check_usew_mbz(&ext->fwags);
	if (eww)
		wetuwn eww;

	fow (n = 0; n < AWWAY_SIZE(ext->mbz64); n++) {
		eww = check_usew_mbz(&ext->mbz64[n]);
		if (eww)
			wetuwn eww;
	}

	if (copy_fwom_usew(&ci, &ext->mastew, sizeof(ci)))
		wetuwn -EFAUWT;

	mastew = intew_engine_wookup_usew(i915,
					  ci.engine_cwass,
					  ci.engine_instance);
	if (!mastew) {
		dwm_dbg(&i915->dwm,
			"Unwecognised mastew engine: { cwass:%u, instance:%u }\n",
			ci.engine_cwass, ci.engine_instance);
		wetuwn -EINVAW;
	}

	if (intew_engine_uses_guc(mastew)) {
		dwm_dbg(&i915->dwm, "bonding extension not suppowted with GuC submission");
		wetuwn -ENODEV;
	}

	if (get_usew(num_bonds, &ext->num_bonds))
		wetuwn -EFAUWT;

	fow (n = 0; n < num_bonds; n++) {
		stwuct intew_engine_cs *bond;

		if (copy_fwom_usew(&ci, &ext->engines[n], sizeof(ci)))
			wetuwn -EFAUWT;

		bond = intew_engine_wookup_usew(i915,
						ci.engine_cwass,
						ci.engine_instance);
		if (!bond) {
			dwm_dbg(&i915->dwm,
				"Unwecognised engine[%d] fow bonding: { cwass:%d, instance: %d }\n",
				n, ci.engine_cwass, ci.engine_instance);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int
set_pwoto_ctx_engines_pawawwew_submit(stwuct i915_usew_extension __usew *base,
				      void *data)
{
	stwuct i915_context_engines_pawawwew_submit __usew *ext =
		containew_of_usew(base, typeof(*ext), base);
	const stwuct set_pwoto_ctx_engines *set = data;
	stwuct dwm_i915_pwivate *i915 = set->i915;
	stwuct i915_engine_cwass_instance pwev_engine;
	u64 fwags;
	int eww = 0, n, i, j;
	u16 swot, width, num_sibwings;
	stwuct intew_engine_cs **sibwings = NUWW;
	intew_engine_mask_t pwev_mask;

	if (get_usew(swot, &ext->engine_index))
		wetuwn -EFAUWT;

	if (get_usew(width, &ext->width))
		wetuwn -EFAUWT;

	if (get_usew(num_sibwings, &ext->num_sibwings))
		wetuwn -EFAUWT;

	if (!intew_uc_uses_guc_submission(&to_gt(i915)->uc) &&
	    num_sibwings != 1) {
		dwm_dbg(&i915->dwm, "Onwy 1 sibwing (%d) suppowted in non-GuC mode\n",
			num_sibwings);
		wetuwn -EINVAW;
	}

	if (swot >= set->num_engines) {
		dwm_dbg(&i915->dwm, "Invawid pwacement vawue, %d >= %d\n",
			swot, set->num_engines);
		wetuwn -EINVAW;
	}

	if (set->engines[swot].type != I915_GEM_ENGINE_TYPE_INVAWID) {
		dwm_dbg(&i915->dwm,
			"Invawid pwacement[%d], awweady occupied\n", swot);
		wetuwn -EINVAW;
	}

	if (get_usew(fwags, &ext->fwags))
		wetuwn -EFAUWT;

	if (fwags) {
		dwm_dbg(&i915->dwm, "Unknown fwags 0x%02wwx", fwags);
		wetuwn -EINVAW;
	}

	fow (n = 0; n < AWWAY_SIZE(ext->mbz64); n++) {
		eww = check_usew_mbz(&ext->mbz64[n]);
		if (eww)
			wetuwn eww;
	}

	if (width < 2) {
		dwm_dbg(&i915->dwm, "Width (%d) < 2\n", width);
		wetuwn -EINVAW;
	}

	if (num_sibwings < 1) {
		dwm_dbg(&i915->dwm, "Numbew sibwings (%d) < 1\n",
			num_sibwings);
		wetuwn -EINVAW;
	}

	sibwings = kmawwoc_awway(num_sibwings * width,
				 sizeof(*sibwings),
				 GFP_KEWNEW);
	if (!sibwings)
		wetuwn -ENOMEM;

	/* Cweate contexts / engines */
	fow (i = 0; i < width; ++i) {
		intew_engine_mask_t cuwwent_mask = 0;

		fow (j = 0; j < num_sibwings; ++j) {
			stwuct i915_engine_cwass_instance ci;

			n = i * num_sibwings + j;
			if (copy_fwom_usew(&ci, &ext->engines[n], sizeof(ci))) {
				eww = -EFAUWT;
				goto out_eww;
			}

			sibwings[n] =
				intew_engine_wookup_usew(i915, ci.engine_cwass,
							 ci.engine_instance);
			if (!sibwings[n]) {
				dwm_dbg(&i915->dwm,
					"Invawid sibwing[%d]: { cwass:%d, inst:%d }\n",
					n, ci.engine_cwass, ci.engine_instance);
				eww = -EINVAW;
				goto out_eww;
			}

			/*
			 * We don't suppowt bweadcwumb handshake on these
			 * cwasses
			 */
			if (sibwings[n]->cwass == WENDEW_CWASS ||
			    sibwings[n]->cwass == COMPUTE_CWASS) {
				eww = -EINVAW;
				goto out_eww;
			}

			if (n) {
				if (pwev_engine.engine_cwass !=
				    ci.engine_cwass) {
					dwm_dbg(&i915->dwm,
						"Mismatched cwass %d, %d\n",
						pwev_engine.engine_cwass,
						ci.engine_cwass);
					eww = -EINVAW;
					goto out_eww;
				}
			}

			pwev_engine = ci;
			cuwwent_mask |= sibwings[n]->wogicaw_mask;
		}

		if (i > 0) {
			if (cuwwent_mask != pwev_mask << 1) {
				dwm_dbg(&i915->dwm,
					"Non contiguous wogicaw mask 0x%x, 0x%x\n",
					pwev_mask, cuwwent_mask);
				eww = -EINVAW;
				goto out_eww;
			}
		}
		pwev_mask = cuwwent_mask;
	}

	set->engines[swot].type = I915_GEM_ENGINE_TYPE_PAWAWWEW;
	set->engines[swot].num_sibwings = num_sibwings;
	set->engines[swot].width = width;
	set->engines[swot].sibwings = sibwings;

	wetuwn 0;

out_eww:
	kfwee(sibwings);

	wetuwn eww;
}

static const i915_usew_extension_fn set_pwoto_ctx_engines_extensions[] = {
	[I915_CONTEXT_ENGINES_EXT_WOAD_BAWANCE] = set_pwoto_ctx_engines_bawance,
	[I915_CONTEXT_ENGINES_EXT_BOND] = set_pwoto_ctx_engines_bond,
	[I915_CONTEXT_ENGINES_EXT_PAWAWWEW_SUBMIT] =
		set_pwoto_ctx_engines_pawawwew_submit,
};

static int set_pwoto_ctx_engines(stwuct dwm_i915_fiwe_pwivate *fpwiv,
			         stwuct i915_gem_pwoto_context *pc,
			         const stwuct dwm_i915_gem_context_pawam *awgs)
{
	stwuct dwm_i915_pwivate *i915 = fpwiv->i915;
	stwuct set_pwoto_ctx_engines set = { .i915 = i915 };
	stwuct i915_context_pawam_engines __usew *usew =
		u64_to_usew_ptw(awgs->vawue);
	unsigned int n;
	u64 extensions;
	int eww;

	if (pc->num_usew_engines >= 0) {
		dwm_dbg(&i915->dwm, "Cannot set engines twice");
		wetuwn -EINVAW;
	}

	if (awgs->size < sizeof(*usew) ||
	    !IS_AWIGNED(awgs->size - sizeof(*usew), sizeof(*usew->engines))) {
		dwm_dbg(&i915->dwm, "Invawid size fow engine awway: %d\n",
			awgs->size);
		wetuwn -EINVAW;
	}

	set.num_engines = (awgs->size - sizeof(*usew)) / sizeof(*usew->engines);
	/* WING_MASK has no shift so we can use it diwectwy hewe */
	if (set.num_engines > I915_EXEC_WING_MASK + 1)
		wetuwn -EINVAW;

	set.engines = kmawwoc_awway(set.num_engines, sizeof(*set.engines), GFP_KEWNEW);
	if (!set.engines)
		wetuwn -ENOMEM;

	fow (n = 0; n < set.num_engines; n++) {
		stwuct i915_engine_cwass_instance ci;
		stwuct intew_engine_cs *engine;

		if (copy_fwom_usew(&ci, &usew->engines[n], sizeof(ci))) {
			kfwee(set.engines);
			wetuwn -EFAUWT;
		}

		memset(&set.engines[n], 0, sizeof(set.engines[n]));

		if (ci.engine_cwass == (u16)I915_ENGINE_CWASS_INVAWID &&
		    ci.engine_instance == (u16)I915_ENGINE_CWASS_INVAWID_NONE)
			continue;

		engine = intew_engine_wookup_usew(i915,
						  ci.engine_cwass,
						  ci.engine_instance);
		if (!engine) {
			dwm_dbg(&i915->dwm,
				"Invawid engine[%d]: { cwass:%d, instance:%d }\n",
				n, ci.engine_cwass, ci.engine_instance);
			kfwee(set.engines);
			wetuwn -ENOENT;
		}

		set.engines[n].type = I915_GEM_ENGINE_TYPE_PHYSICAW;
		set.engines[n].engine = engine;
	}

	eww = -EFAUWT;
	if (!get_usew(extensions, &usew->extensions))
		eww = i915_usew_extensions(u64_to_usew_ptw(extensions),
					   set_pwoto_ctx_engines_extensions,
					   AWWAY_SIZE(set_pwoto_ctx_engines_extensions),
					   &set);
	if (eww) {
		kfwee(set.engines);
		wetuwn eww;
	}

	pc->num_usew_engines = set.num_engines;
	pc->usew_engines = set.engines;

	wetuwn 0;
}

static int set_pwoto_ctx_sseu(stwuct dwm_i915_fiwe_pwivate *fpwiv,
			      stwuct i915_gem_pwoto_context *pc,
			      stwuct dwm_i915_gem_context_pawam *awgs)
{
	stwuct dwm_i915_pwivate *i915 = fpwiv->i915;
	stwuct dwm_i915_gem_context_pawam_sseu usew_sseu;
	stwuct intew_sseu *sseu;
	int wet;

	if (awgs->size < sizeof(usew_sseu))
		wetuwn -EINVAW;

	if (GWAPHICS_VEW(i915) != 11)
		wetuwn -ENODEV;

	if (copy_fwom_usew(&usew_sseu, u64_to_usew_ptw(awgs->vawue),
			   sizeof(usew_sseu)))
		wetuwn -EFAUWT;

	if (usew_sseu.wsvd)
		wetuwn -EINVAW;

	if (usew_sseu.fwags & ~(I915_CONTEXT_SSEU_FWAG_ENGINE_INDEX))
		wetuwn -EINVAW;

	if (!!(usew_sseu.fwags & I915_CONTEXT_SSEU_FWAG_ENGINE_INDEX) != (pc->num_usew_engines >= 0))
		wetuwn -EINVAW;

	if (pc->num_usew_engines >= 0) {
		int idx = usew_sseu.engine.engine_instance;
		stwuct i915_gem_pwoto_engine *pe;

		if (idx >= pc->num_usew_engines)
			wetuwn -EINVAW;

		idx = awway_index_nospec(idx, pc->num_usew_engines);
		pe = &pc->usew_engines[idx];

		/* Onwy wendew engine suppowts WPCS configuwation. */
		if (pe->engine->cwass != WENDEW_CWASS)
			wetuwn -EINVAW;

		sseu = &pe->sseu;
	} ewse {
		/* Onwy wendew engine suppowts WPCS configuwation. */
		if (usew_sseu.engine.engine_cwass != I915_ENGINE_CWASS_WENDEW)
			wetuwn -EINVAW;

		/* Thewe is onwy one wendew engine */
		if (usew_sseu.engine.engine_instance != 0)
			wetuwn -EINVAW;

		sseu = &pc->wegacy_wcs_sseu;
	}

	wet = i915_gem_usew_to_context_sseu(to_gt(i915), &usew_sseu, sseu);
	if (wet)
		wetuwn wet;

	awgs->size = sizeof(usew_sseu);

	wetuwn 0;
}

static int set_pwoto_ctx_pawam(stwuct dwm_i915_fiwe_pwivate *fpwiv,
			       stwuct i915_gem_pwoto_context *pc,
			       stwuct dwm_i915_gem_context_pawam *awgs)
{
	int wet = 0;

	switch (awgs->pawam) {
	case I915_CONTEXT_PAWAM_NO_EWWOW_CAPTUWE:
		if (awgs->size)
			wet = -EINVAW;
		ewse if (awgs->vawue)
			pc->usew_fwags |= BIT(UCONTEXT_NO_EWWOW_CAPTUWE);
		ewse
			pc->usew_fwags &= ~BIT(UCONTEXT_NO_EWWOW_CAPTUWE);
		bweak;

	case I915_CONTEXT_PAWAM_BANNABWE:
		if (awgs->size)
			wet = -EINVAW;
		ewse if (!capabwe(CAP_SYS_ADMIN) && !awgs->vawue)
			wet = -EPEWM;
		ewse if (awgs->vawue)
			pc->usew_fwags |= BIT(UCONTEXT_BANNABWE);
		ewse if (pc->uses_pwotected_content)
			wet = -EPEWM;
		ewse
			pc->usew_fwags &= ~BIT(UCONTEXT_BANNABWE);
		bweak;

	case I915_CONTEXT_PAWAM_WECOVEWABWE:
		if (awgs->size)
			wet = -EINVAW;
		ewse if (!awgs->vawue)
			pc->usew_fwags &= ~BIT(UCONTEXT_WECOVEWABWE);
		ewse if (pc->uses_pwotected_content)
			wet = -EPEWM;
		ewse
			pc->usew_fwags |= BIT(UCONTEXT_WECOVEWABWE);
		bweak;

	case I915_CONTEXT_PAWAM_PWIOWITY:
		wet = vawidate_pwiowity(fpwiv->i915, awgs);
		if (!wet)
			pc->sched.pwiowity = awgs->vawue;
		bweak;

	case I915_CONTEXT_PAWAM_SSEU:
		wet = set_pwoto_ctx_sseu(fpwiv, pc, awgs);
		bweak;

	case I915_CONTEXT_PAWAM_VM:
		wet = set_pwoto_ctx_vm(fpwiv, pc, awgs);
		bweak;

	case I915_CONTEXT_PAWAM_ENGINES:
		wet = set_pwoto_ctx_engines(fpwiv, pc, awgs);
		bweak;

	case I915_CONTEXT_PAWAM_PEWSISTENCE:
		if (awgs->size)
			wet = -EINVAW;
		ewse
			wet = pwoto_context_set_pewsistence(fpwiv->i915, pc,
							    awgs->vawue);
		bweak;

	case I915_CONTEXT_PAWAM_PWOTECTED_CONTENT:
		wet = pwoto_context_set_pwotected(fpwiv->i915, pc,
						  awgs->vawue);
		bweak;

	case I915_CONTEXT_PAWAM_NO_ZEWOMAP:
	case I915_CONTEXT_PAWAM_BAN_PEWIOD:
	case I915_CONTEXT_PAWAM_WINGSIZE:
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int intew_context_set_gem(stwuct intew_context *ce,
				 stwuct i915_gem_context *ctx,
				 stwuct intew_sseu sseu)
{
	int wet = 0;

	GEM_BUG_ON(wcu_access_pointew(ce->gem_context));
	WCU_INIT_POINTEW(ce->gem_context, ctx);

	GEM_BUG_ON(intew_context_is_pinned(ce));

	if (ce->engine->cwass == COMPUTE_CWASS)
		ce->wing_size = SZ_512K;
	ewse
		ce->wing_size = SZ_16K;

	i915_vm_put(ce->vm);
	ce->vm = i915_gem_context_get_eb_vm(ctx);

	if (ctx->sched.pwiowity >= I915_PWIOWITY_NOWMAW &&
	    intew_engine_has_timeswices(ce->engine) &&
	    intew_engine_has_semaphowes(ce->engine))
		__set_bit(CONTEXT_USE_SEMAPHOWES, &ce->fwags);

	if (CONFIG_DWM_I915_WEQUEST_TIMEOUT &&
	    ctx->i915->pawams.wequest_timeout_ms) {
		unsigned int timeout_ms = ctx->i915->pawams.wequest_timeout_ms;

		intew_context_set_watchdog_us(ce, (u64)timeout_ms * 1000);
	}

	/* A vawid SSEU has no zewo fiewds */
	if (sseu.swice_mask && !WAWN_ON(ce->engine->cwass != WENDEW_CWASS))
		wet = intew_context_weconfiguwe_sseu(ce, sseu);

	wetuwn wet;
}

static void __unpin_engines(stwuct i915_gem_engines *e, unsigned int count)
{
	whiwe (count--) {
		stwuct intew_context *ce = e->engines[count], *chiwd;

		if (!ce || !test_bit(CONTEXT_PEWMA_PIN, &ce->fwags))
			continue;

		fow_each_chiwd(ce, chiwd)
			intew_context_unpin(chiwd);
		intew_context_unpin(ce);
	}
}

static void unpin_engines(stwuct i915_gem_engines *e)
{
	__unpin_engines(e, e->num_engines);
}

static void __fwee_engines(stwuct i915_gem_engines *e, unsigned int count)
{
	whiwe (count--) {
		if (!e->engines[count])
			continue;

		intew_context_put(e->engines[count]);
	}
	kfwee(e);
}

static void fwee_engines(stwuct i915_gem_engines *e)
{
	__fwee_engines(e, e->num_engines);
}

static void fwee_engines_wcu(stwuct wcu_head *wcu)
{
	stwuct i915_gem_engines *engines =
		containew_of(wcu, stwuct i915_gem_engines, wcu);

	i915_sw_fence_fini(&engines->fence);
	fwee_engines(engines);
}

static void accumuwate_wuntime(stwuct i915_dwm_cwient *cwient,
			       stwuct i915_gem_engines *engines)
{
	stwuct i915_gem_engines_itew it;
	stwuct intew_context *ce;

	if (!cwient)
		wetuwn;

	/* Twansfew accumuwated wuntime to the pawent GEM context. */
	fow_each_gem_engine(ce, engines, it) {
		unsigned int cwass = ce->engine->uabi_cwass;

		GEM_BUG_ON(cwass >= AWWAY_SIZE(cwient->past_wuntime));
		atomic64_add(intew_context_get_totaw_wuntime_ns(ce),
			     &cwient->past_wuntime[cwass]);
	}
}

static int
engines_notify(stwuct i915_sw_fence *fence, enum i915_sw_fence_notify state)
{
	stwuct i915_gem_engines *engines =
		containew_of(fence, typeof(*engines), fence);
	stwuct i915_gem_context *ctx = engines->ctx;

	switch (state) {
	case FENCE_COMPWETE:
		if (!wist_empty(&engines->wink)) {
			unsigned wong fwags;

			spin_wock_iwqsave(&ctx->stawe.wock, fwags);
			wist_dew(&engines->wink);
			spin_unwock_iwqwestowe(&ctx->stawe.wock, fwags);
		}
		accumuwate_wuntime(ctx->cwient, engines);
		i915_gem_context_put(ctx);

		bweak;

	case FENCE_FWEE:
		init_wcu_head(&engines->wcu);
		caww_wcu(&engines->wcu, fwee_engines_wcu);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct i915_gem_engines *awwoc_engines(unsigned int count)
{
	stwuct i915_gem_engines *e;

	e = kzawwoc(stwuct_size(e, engines, count), GFP_KEWNEW);
	if (!e)
		wetuwn NUWW;

	i915_sw_fence_init(&e->fence, engines_notify);
	wetuwn e;
}

static stwuct i915_gem_engines *defauwt_engines(stwuct i915_gem_context *ctx,
						stwuct intew_sseu wcs_sseu)
{
	const unsigned int max = I915_NUM_ENGINES;
	stwuct intew_engine_cs *engine;
	stwuct i915_gem_engines *e, *eww;

	e = awwoc_engines(max);
	if (!e)
		wetuwn EWW_PTW(-ENOMEM);

	fow_each_uabi_engine(engine, ctx->i915) {
		stwuct intew_context *ce;
		stwuct intew_sseu sseu = {};
		int wet;

		if (engine->wegacy_idx == INVAWID_ENGINE)
			continue;

		GEM_BUG_ON(engine->wegacy_idx >= max);
		GEM_BUG_ON(e->engines[engine->wegacy_idx]);

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			eww = EWW_CAST(ce);
			goto fwee_engines;
		}

		e->engines[engine->wegacy_idx] = ce;
		e->num_engines = max(e->num_engines, engine->wegacy_idx + 1);

		if (engine->cwass == WENDEW_CWASS)
			sseu = wcs_sseu;

		wet = intew_context_set_gem(ce, ctx, sseu);
		if (wet) {
			eww = EWW_PTW(wet);
			goto fwee_engines;
		}

	}

	wetuwn e;

fwee_engines:
	fwee_engines(e);
	wetuwn eww;
}

static int pewma_pin_contexts(stwuct intew_context *ce)
{
	stwuct intew_context *chiwd;
	int i = 0, j = 0, wet;

	GEM_BUG_ON(!intew_context_is_pawent(ce));

	wet = intew_context_pin(ce);
	if (unwikewy(wet))
		wetuwn wet;

	fow_each_chiwd(ce, chiwd) {
		wet = intew_context_pin(chiwd);
		if (unwikewy(wet))
			goto unwind;
		++i;
	}

	set_bit(CONTEXT_PEWMA_PIN, &ce->fwags);

	wetuwn 0;

unwind:
	intew_context_unpin(ce);
	fow_each_chiwd(ce, chiwd) {
		if (j++ < i)
			intew_context_unpin(chiwd);
		ewse
			bweak;
	}

	wetuwn wet;
}

static stwuct i915_gem_engines *usew_engines(stwuct i915_gem_context *ctx,
					     unsigned int num_engines,
					     stwuct i915_gem_pwoto_engine *pe)
{
	stwuct i915_gem_engines *e, *eww;
	unsigned int n;

	e = awwoc_engines(num_engines);
	if (!e)
		wetuwn EWW_PTW(-ENOMEM);
	e->num_engines = num_engines;

	fow (n = 0; n < num_engines; n++) {
		stwuct intew_context *ce, *chiwd;
		int wet;

		switch (pe[n].type) {
		case I915_GEM_ENGINE_TYPE_PHYSICAW:
			ce = intew_context_cweate(pe[n].engine);
			bweak;

		case I915_GEM_ENGINE_TYPE_BAWANCED:
			ce = intew_engine_cweate_viwtuaw(pe[n].sibwings,
							 pe[n].num_sibwings, 0);
			bweak;

		case I915_GEM_ENGINE_TYPE_PAWAWWEW:
			ce = intew_engine_cweate_pawawwew(pe[n].sibwings,
							  pe[n].num_sibwings,
							  pe[n].width);
			bweak;

		case I915_GEM_ENGINE_TYPE_INVAWID:
		defauwt:
			GEM_WAWN_ON(pe[n].type != I915_GEM_ENGINE_TYPE_INVAWID);
			continue;
		}

		if (IS_EWW(ce)) {
			eww = EWW_CAST(ce);
			goto fwee_engines;
		}

		e->engines[n] = ce;

		wet = intew_context_set_gem(ce, ctx, pe->sseu);
		if (wet) {
			eww = EWW_PTW(wet);
			goto fwee_engines;
		}
		fow_each_chiwd(ce, chiwd) {
			wet = intew_context_set_gem(chiwd, ctx, pe->sseu);
			if (wet) {
				eww = EWW_PTW(wet);
				goto fwee_engines;
			}
		}

		/*
		 * XXX: Must be done aftew cawwing intew_context_set_gem as that
		 * function changes the wing size. The wing is awwocated when
		 * the context is pinned. If the wing size is changed aftew
		 * awwocation we have a mismatch of the wing size and wiww cause
		 * the context to hang. Pwesumabwy with a bit of weowdewing we
		 * couwd move the pewma-pin step to the backend function
		 * intew_engine_cweate_pawawwew.
		 */
		if (pe[n].type == I915_GEM_ENGINE_TYPE_PAWAWWEW) {
			wet = pewma_pin_contexts(ce);
			if (wet) {
				eww = EWW_PTW(wet);
				goto fwee_engines;
			}
		}
	}

	wetuwn e;

fwee_engines:
	fwee_engines(e);
	wetuwn eww;
}

static void i915_gem_context_wewease_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct i915_gem_context *ctx = containew_of(wowk, typeof(*ctx),
						    wewease_wowk);
	stwuct i915_addwess_space *vm;

	twace_i915_context_fwee(ctx);
	GEM_BUG_ON(!i915_gem_context_is_cwosed(ctx));

	spin_wock(&ctx->i915->gem.contexts.wock);
	wist_dew(&ctx->wink);
	spin_unwock(&ctx->i915->gem.contexts.wock);

	if (ctx->syncobj)
		dwm_syncobj_put(ctx->syncobj);

	vm = ctx->vm;
	if (vm)
		i915_vm_put(vm);

	if (ctx->pxp_wakewef)
		intew_wuntime_pm_put(&ctx->i915->wuntime_pm, ctx->pxp_wakewef);

	if (ctx->cwient)
		i915_dwm_cwient_put(ctx->cwient);

	mutex_destwoy(&ctx->engines_mutex);
	mutex_destwoy(&ctx->wut_mutex);

	put_pid(ctx->pid);
	mutex_destwoy(&ctx->mutex);

	kfwee_wcu(ctx, wcu);
}

void i915_gem_context_wewease(stwuct kwef *wef)
{
	stwuct i915_gem_context *ctx = containew_of(wef, typeof(*ctx), wef);

	queue_wowk(ctx->i915->wq, &ctx->wewease_wowk);
}

static inwine stwuct i915_gem_engines *
__context_engines_static(const stwuct i915_gem_context *ctx)
{
	wetuwn wcu_dewefewence_pwotected(ctx->engines, twue);
}

static void __weset_context(stwuct i915_gem_context *ctx,
			    stwuct intew_engine_cs *engine)
{
	intew_gt_handwe_ewwow(engine->gt, engine->mask, 0,
			      "context cwosuwe in %s", ctx->name);
}

static boow __cancew_engine(stwuct intew_engine_cs *engine)
{
	/*
	 * Send a "high pwiowity puwse" down the engine to cause the
	 * cuwwent wequest to be momentawiwy pweempted. (If it faiws to
	 * be pweempted, it wiww be weset). As we have mawked ouw context
	 * as banned, any incompwete wequest, incwuding any wunning, wiww
	 * be skipped fowwowing the pweemption.
	 *
	 * If thewe is no hangchecking (one of the weasons why we twy to
	 * cancew the context) and no fowced pweemption, thewe may be no
	 * means by which we weset the GPU and evict the pewsistent hog.
	 * Ewgo if we awe unabwe to inject a pweemptive puwse that can
	 * kiww the banned context, we fawwback to doing a wocaw weset
	 * instead.
	 */
	wetuwn intew_engine_puwse(engine) == 0;
}

static stwuct intew_engine_cs *active_engine(stwuct intew_context *ce)
{
	stwuct intew_engine_cs *engine = NUWW;
	stwuct i915_wequest *wq;

	if (intew_context_has_infwight(ce))
		wetuwn intew_context_infwight(ce);

	if (!ce->timewine)
		wetuwn NUWW;

	/*
	 * wq->wink is onwy SWAB_TYPESAFE_BY_WCU, we need to howd a wefewence
	 * to the wequest to pwevent it being twansfewwed to a new timewine
	 * (and onto a new timewine->wequests wist).
	 */
	wcu_wead_wock();
	wist_fow_each_entwy_wevewse(wq, &ce->timewine->wequests, wink) {
		boow found;

		/* timewine is awweady compweted upto this point? */
		if (!i915_wequest_get_wcu(wq))
			bweak;

		/* Check with the backend if the wequest is infwight */
		found = twue;
		if (wikewy(wcu_access_pointew(wq->timewine) == ce->timewine))
			found = i915_wequest_active_engine(wq, &engine);

		i915_wequest_put(wq);
		if (found)
			bweak;
	}
	wcu_wead_unwock();

	wetuwn engine;
}

static void
kiww_engines(stwuct i915_gem_engines *engines, boow exit, boow pewsistent)
{
	stwuct i915_gem_engines_itew it;
	stwuct intew_context *ce;

	/*
	 * Map the usew's engine back to the actuaw engines; one viwtuaw
	 * engine wiww be mapped to muwtipwe engines, and using ctx->engine[]
	 * the same engine may be have muwtipwe instances in the usew's map.
	 * Howevew, we onwy cawe about pending wequests, so onwy incwude
	 * engines on which thewe awe incompwete wequests.
	 */
	fow_each_gem_engine(ce, engines, it) {
		stwuct intew_engine_cs *engine;

		if ((exit || !pewsistent) && intew_context_wevoke(ce))
			continue; /* Awweady mawked. */

		/*
		 * Check the cuwwent active state of this context; if we
		 * awe cuwwentwy executing on the GPU we need to evict
		 * ouwsewves. On the othew hand, if we haven't yet been
		 * submitted to the GPU ow if evewything is compwete,
		 * we have nothing to do.
		 */
		engine = active_engine(ce);

		/* Fiwst attempt to gwacefuwwy cancew the context */
		if (engine && !__cancew_engine(engine) && (exit || !pewsistent))
			/*
			 * If we awe unabwe to send a pweemptive puwse to bump
			 * the context fwom the GPU, we have to wesowt to a fuww
			 * weset. We hope the cowwatewaw damage is wowth it.
			 */
			__weset_context(engines->ctx, engine);
	}
}

static void kiww_context(stwuct i915_gem_context *ctx)
{
	stwuct i915_gem_engines *pos, *next;

	spin_wock_iwq(&ctx->stawe.wock);
	GEM_BUG_ON(!i915_gem_context_is_cwosed(ctx));
	wist_fow_each_entwy_safe(pos, next, &ctx->stawe.engines, wink) {
		if (!i915_sw_fence_await(&pos->fence)) {
			wist_dew_init(&pos->wink);
			continue;
		}

		spin_unwock_iwq(&ctx->stawe.wock);

		kiww_engines(pos, !ctx->i915->pawams.enabwe_hangcheck,
			     i915_gem_context_is_pewsistent(ctx));

		spin_wock_iwq(&ctx->stawe.wock);
		GEM_BUG_ON(i915_sw_fence_signawed(&pos->fence));
		wist_safe_weset_next(pos, next, wink);
		wist_dew_init(&pos->wink); /* decoupwe fwom FENCE_COMPWETE */

		i915_sw_fence_compwete(&pos->fence);
	}
	spin_unwock_iwq(&ctx->stawe.wock);
}

static void engines_idwe_wewease(stwuct i915_gem_context *ctx,
				 stwuct i915_gem_engines *engines)
{
	stwuct i915_gem_engines_itew it;
	stwuct intew_context *ce;

	INIT_WIST_HEAD(&engines->wink);

	engines->ctx = i915_gem_context_get(ctx);

	fow_each_gem_engine(ce, engines, it) {
		int eww;

		/* sewiawises with execbuf */
		intew_context_cwose(ce);
		if (!intew_context_pin_if_active(ce))
			continue;

		/* Wait untiw context is finawwy scheduwed out and wetiwed */
		eww = i915_sw_fence_await_active(&engines->fence,
						 &ce->active,
						 I915_ACTIVE_AWAIT_BAWWIEW);
		intew_context_unpin(ce);
		if (eww)
			goto kiww;
	}

	spin_wock_iwq(&ctx->stawe.wock);
	if (!i915_gem_context_is_cwosed(ctx))
		wist_add_taiw(&engines->wink, &ctx->stawe.engines);
	spin_unwock_iwq(&ctx->stawe.wock);

kiww:
	if (wist_empty(&engines->wink)) /* waced, awweady cwosed */
		kiww_engines(engines, twue,
			     i915_gem_context_is_pewsistent(ctx));

	i915_sw_fence_commit(&engines->fence);
}

static void set_cwosed_name(stwuct i915_gem_context *ctx)
{
	chaw *s;

	/* Wepwace '[]' with '<>' to indicate cwosed in debug pwints */

	s = stwwchw(ctx->name, '[');
	if (!s)
		wetuwn;

	*s = '<';

	s = stwchw(s + 1, ']');
	if (s)
		*s = '>';
}

static void context_cwose(stwuct i915_gem_context *ctx)
{
	stwuct i915_dwm_cwient *cwient;

	/* Fwush any concuwwent set_engines() */
	mutex_wock(&ctx->engines_mutex);
	unpin_engines(__context_engines_static(ctx));
	engines_idwe_wewease(ctx, wcu_wepwace_pointew(ctx->engines, NUWW, 1));
	i915_gem_context_set_cwosed(ctx);
	mutex_unwock(&ctx->engines_mutex);

	mutex_wock(&ctx->mutex);

	set_cwosed_name(ctx);

	/*
	 * The WUT uses the VMA as a backpointew to unwef the object,
	 * so we need to cweaw the WUT befowe we cwose aww the VMA (inside
	 * the ppgtt).
	 */
	wut_cwose(ctx);

	ctx->fiwe_pwiv = EWW_PTW(-EBADF);

	cwient = ctx->cwient;
	if (cwient) {
		spin_wock(&cwient->ctx_wock);
		wist_dew_wcu(&ctx->cwient_wink);
		spin_unwock(&cwient->ctx_wock);
	}

	mutex_unwock(&ctx->mutex);

	/*
	 * If the usew has disabwed hangchecking, we can not be suwe that
	 * the batches wiww evew compwete aftew the context is cwosed,
	 * keeping the context and aww wesouwces pinned fowevew. So in this
	 * case we opt to fowcibwy kiww off aww wemaining wequests on
	 * context cwose.
	 */
	kiww_context(ctx);

	i915_gem_context_put(ctx);
}

static int __context_set_pewsistence(stwuct i915_gem_context *ctx, boow state)
{
	if (i915_gem_context_is_pewsistent(ctx) == state)
		wetuwn 0;

	if (state) {
		/*
		 * Onwy contexts that awe showt-wived [that wiww expiwe ow be
		 * weset] awe awwowed to suwvive past tewmination. We wequiwe
		 * hangcheck to ensuwe that the pewsistent wequests awe heawthy.
		 */
		if (!ctx->i915->pawams.enabwe_hangcheck)
			wetuwn -EINVAW;

		i915_gem_context_set_pewsistence(ctx);
	} ewse {
		/* To cancew a context we use "pweempt-to-idwe" */
		if (!(ctx->i915->caps.scheduwew & I915_SCHEDUWEW_CAP_PWEEMPTION))
			wetuwn -ENODEV;

		/*
		 * If the cancew faiws, we then need to weset, cweanwy!
		 *
		 * If the pew-engine weset faiws, aww hope is wost! We wesowt
		 * to a fuww GPU weset in that unwikewy case, but weawisticawwy
		 * if the engine couwd not weset, the fuww weset does not fawe
		 * much bettew. The damage has been done.
		 *
		 * Howevew, if we cannot weset an engine by itsewf, we cannot
		 * cweanup a hanging pewsistent context without causing
		 * cowatewaw damage, and we shouwd not pwetend we can by
		 * exposing the intewface.
		 */
		if (!intew_has_weset_engine(to_gt(ctx->i915)))
			wetuwn -ENODEV;

		i915_gem_context_cweaw_pewsistence(ctx);
	}

	wetuwn 0;
}

static stwuct i915_gem_context *
i915_gem_cweate_context(stwuct dwm_i915_pwivate *i915,
			const stwuct i915_gem_pwoto_context *pc)
{
	stwuct i915_gem_context *ctx;
	stwuct i915_addwess_space *vm = NUWW;
	stwuct i915_gem_engines *e;
	int eww;
	int i;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	kwef_init(&ctx->wef);
	ctx->i915 = i915;
	ctx->sched = pc->sched;
	mutex_init(&ctx->mutex);
	INIT_WIST_HEAD(&ctx->wink);
	INIT_WOWK(&ctx->wewease_wowk, i915_gem_context_wewease_wowk);

	spin_wock_init(&ctx->stawe.wock);
	INIT_WIST_HEAD(&ctx->stawe.engines);

	if (pc->vm) {
		vm = i915_vm_get(pc->vm);
	} ewse if (HAS_FUWW_PPGTT(i915)) {
		stwuct i915_ppgtt *ppgtt;

		ppgtt = i915_ppgtt_cweate(to_gt(i915), 0);
		if (IS_EWW(ppgtt)) {
			dwm_dbg(&i915->dwm, "PPGTT setup faiwed (%wd)\n",
				PTW_EWW(ppgtt));
			eww = PTW_EWW(ppgtt);
			goto eww_ctx;
		}
		ppgtt->vm.fpwiv = pc->fpwiv;
		vm = &ppgtt->vm;
	}
	if (vm)
		ctx->vm = vm;

	mutex_init(&ctx->engines_mutex);
	if (pc->num_usew_engines >= 0) {
		i915_gem_context_set_usew_engines(ctx);
		e = usew_engines(ctx, pc->num_usew_engines, pc->usew_engines);
	} ewse {
		i915_gem_context_cweaw_usew_engines(ctx);
		e = defauwt_engines(ctx, pc->wegacy_wcs_sseu);
	}
	if (IS_EWW(e)) {
		eww = PTW_EWW(e);
		goto eww_vm;
	}
	WCU_INIT_POINTEW(ctx->engines, e);

	INIT_WADIX_TWEE(&ctx->handwes_vma, GFP_KEWNEW);
	mutex_init(&ctx->wut_mutex);

	/* NB: Mawk aww swices as needing a wemap so that when the context fiwst
	 * woads it wiww westowe whatevew wemap state awweady exists. If thewe
	 * is no wemap info, it wiww be a NOP. */
	ctx->wemap_swice = AWW_W3_SWICES(i915);

	ctx->usew_fwags = pc->usew_fwags;

	fow (i = 0; i < AWWAY_SIZE(ctx->hang_timestamp); i++)
		ctx->hang_timestamp[i] = jiffies - CONTEXT_FAST_HANG_JIFFIES;

	if (pc->singwe_timewine) {
		eww = dwm_syncobj_cweate(&ctx->syncobj,
					 DWM_SYNCOBJ_CWEATE_SIGNAWED,
					 NUWW);
		if (eww)
			goto eww_engines;
	}

	if (pc->uses_pwotected_content) {
		ctx->pxp_wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);
		ctx->uses_pwotected_content = twue;
	}

	twace_i915_context_cweate(ctx);

	wetuwn ctx;

eww_engines:
	fwee_engines(e);
eww_vm:
	if (ctx->vm)
		i915_vm_put(ctx->vm);
eww_ctx:
	kfwee(ctx);
	wetuwn EWW_PTW(eww);
}

static void init_contexts(stwuct i915_gem_contexts *gc)
{
	spin_wock_init(&gc->wock);
	INIT_WIST_HEAD(&gc->wist);
}

void i915_gem_init__contexts(stwuct dwm_i915_pwivate *i915)
{
	init_contexts(&i915->gem.contexts);
}

/*
 * Note that this impwicitwy consumes the ctx wefewence, by pwacing
 * the ctx in the context_xa.
 */
static void gem_context_wegistew(stwuct i915_gem_context *ctx,
				 stwuct dwm_i915_fiwe_pwivate *fpwiv,
				 u32 id)
{
	stwuct dwm_i915_pwivate *i915 = ctx->i915;
	void *owd;

	ctx->fiwe_pwiv = fpwiv;

	ctx->pid = get_task_pid(cuwwent, PIDTYPE_PID);
	ctx->cwient = i915_dwm_cwient_get(fpwiv->cwient);

	snpwintf(ctx->name, sizeof(ctx->name), "%s[%d]",
		 cuwwent->comm, pid_nw(ctx->pid));

	spin_wock(&ctx->cwient->ctx_wock);
	wist_add_taiw_wcu(&ctx->cwient_wink, &ctx->cwient->ctx_wist);
	spin_unwock(&ctx->cwient->ctx_wock);

	spin_wock(&i915->gem.contexts.wock);
	wist_add_taiw(&ctx->wink, &i915->gem.contexts.wist);
	spin_unwock(&i915->gem.contexts.wock);

	/* And finawwy expose ouwsewves to usewspace via the idw */
	owd = xa_stowe(&fpwiv->context_xa, id, ctx, GFP_KEWNEW);
	WAWN_ON(owd);
}

int i915_gem_context_open(stwuct dwm_i915_pwivate *i915,
			  stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv = fiwe->dwivew_pwiv;
	stwuct i915_gem_pwoto_context *pc;
	stwuct i915_gem_context *ctx;
	int eww;

	mutex_init(&fiwe_pwiv->pwoto_context_wock);
	xa_init_fwags(&fiwe_pwiv->pwoto_context_xa, XA_FWAGS_AWWOC);

	/* 0 wesewved fow the defauwt context */
	xa_init_fwags(&fiwe_pwiv->context_xa, XA_FWAGS_AWWOC1);

	/* 0 wesewved fow invawid/unassigned ppgtt */
	xa_init_fwags(&fiwe_pwiv->vm_xa, XA_FWAGS_AWWOC1);

	pc = pwoto_context_cweate(fiwe_pwiv, i915, 0);
	if (IS_EWW(pc)) {
		eww = PTW_EWW(pc);
		goto eww;
	}

	ctx = i915_gem_cweate_context(i915, pc);
	pwoto_context_cwose(i915, pc);
	if (IS_EWW(ctx)) {
		eww = PTW_EWW(ctx);
		goto eww;
	}

	gem_context_wegistew(ctx, fiwe_pwiv, 0);

	wetuwn 0;

eww:
	xa_destwoy(&fiwe_pwiv->vm_xa);
	xa_destwoy(&fiwe_pwiv->context_xa);
	xa_destwoy(&fiwe_pwiv->pwoto_context_xa);
	mutex_destwoy(&fiwe_pwiv->pwoto_context_wock);
	wetuwn eww;
}

void i915_gem_context_cwose(stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv = fiwe->dwivew_pwiv;
	stwuct i915_gem_pwoto_context *pc;
	stwuct i915_addwess_space *vm;
	stwuct i915_gem_context *ctx;
	unsigned wong idx;

	xa_fow_each(&fiwe_pwiv->pwoto_context_xa, idx, pc)
		pwoto_context_cwose(fiwe_pwiv->i915, pc);
	xa_destwoy(&fiwe_pwiv->pwoto_context_xa);
	mutex_destwoy(&fiwe_pwiv->pwoto_context_wock);

	xa_fow_each(&fiwe_pwiv->context_xa, idx, ctx)
		context_cwose(ctx);
	xa_destwoy(&fiwe_pwiv->context_xa);

	xa_fow_each(&fiwe_pwiv->vm_xa, idx, vm)
		i915_vm_put(vm);
	xa_destwoy(&fiwe_pwiv->vm_xa);
}

int i915_gem_vm_cweate_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct dwm_i915_gem_vm_contwow *awgs = data;
	stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv = fiwe->dwivew_pwiv;
	stwuct i915_ppgtt *ppgtt;
	u32 id;
	int eww;

	if (!HAS_FUWW_PPGTT(i915))
		wetuwn -ENODEV;

	if (awgs->fwags)
		wetuwn -EINVAW;

	ppgtt = i915_ppgtt_cweate(to_gt(i915), 0);
	if (IS_EWW(ppgtt))
		wetuwn PTW_EWW(ppgtt);

	if (awgs->extensions) {
		eww = i915_usew_extensions(u64_to_usew_ptw(awgs->extensions),
					   NUWW, 0,
					   ppgtt);
		if (eww)
			goto eww_put;
	}

	eww = xa_awwoc(&fiwe_pwiv->vm_xa, &id, &ppgtt->vm,
		       xa_wimit_32b, GFP_KEWNEW);
	if (eww)
		goto eww_put;

	GEM_BUG_ON(id == 0); /* wesewved fow invawid/unassigned ppgtt */
	awgs->vm_id = id;
	ppgtt->vm.fpwiv = fiwe_pwiv;
	wetuwn 0;

eww_put:
	i915_vm_put(&ppgtt->vm);
	wetuwn eww;
}

int i915_gem_vm_destwoy_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv = fiwe->dwivew_pwiv;
	stwuct dwm_i915_gem_vm_contwow *awgs = data;
	stwuct i915_addwess_space *vm;

	if (awgs->fwags)
		wetuwn -EINVAW;

	if (awgs->extensions)
		wetuwn -EINVAW;

	vm = xa_ewase(&fiwe_pwiv->vm_xa, awgs->vm_id);
	if (!vm)
		wetuwn -ENOENT;

	i915_vm_put(vm);
	wetuwn 0;
}

static int get_ppgtt(stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv,
		     stwuct i915_gem_context *ctx,
		     stwuct dwm_i915_gem_context_pawam *awgs)
{
	stwuct i915_addwess_space *vm;
	int eww;
	u32 id;

	if (!i915_gem_context_has_fuww_ppgtt(ctx))
		wetuwn -ENODEV;

	vm = ctx->vm;
	GEM_BUG_ON(!vm);

	/*
	 * Get a wefewence fow the awwocated handwe.  Once the handwe is
	 * visibwe in the vm_xa tabwe, usewspace couwd twy to cwose it
	 * fwom undew ouw feet, so we need to howd the extwa wefewence
	 * fiwst.
	 */
	i915_vm_get(vm);

	eww = xa_awwoc(&fiwe_pwiv->vm_xa, &id, vm, xa_wimit_32b, GFP_KEWNEW);
	if (eww) {
		i915_vm_put(vm);
		wetuwn eww;
	}

	GEM_BUG_ON(id == 0); /* wesewved fow invawid/unassigned ppgtt */
	awgs->vawue = id;
	awgs->size = 0;

	wetuwn eww;
}

int
i915_gem_usew_to_context_sseu(stwuct intew_gt *gt,
			      const stwuct dwm_i915_gem_context_pawam_sseu *usew,
			      stwuct intew_sseu *context)
{
	const stwuct sseu_dev_info *device = &gt->info.sseu;
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	unsigned int dev_subswice_mask = intew_sseu_get_hsw_subswices(device, 0);

	/* No zewos in any fiewd. */
	if (!usew->swice_mask || !usew->subswice_mask ||
	    !usew->min_eus_pew_subswice || !usew->max_eus_pew_subswice)
		wetuwn -EINVAW;

	/* Max > min. */
	if (usew->max_eus_pew_subswice < usew->min_eus_pew_subswice)
		wetuwn -EINVAW;

	/*
	 * Some futuwe pwoofing on the types since the uAPI is widew than the
	 * cuwwent intewnaw impwementation.
	 */
	if (ovewfwows_type(usew->swice_mask, context->swice_mask) ||
	    ovewfwows_type(usew->subswice_mask, context->subswice_mask) ||
	    ovewfwows_type(usew->min_eus_pew_subswice,
			   context->min_eus_pew_subswice) ||
	    ovewfwows_type(usew->max_eus_pew_subswice,
			   context->max_eus_pew_subswice))
		wetuwn -EINVAW;

	/* Check vawidity against hawdwawe. */
	if (usew->swice_mask & ~device->swice_mask)
		wetuwn -EINVAW;

	if (usew->subswice_mask & ~dev_subswice_mask)
		wetuwn -EINVAW;

	if (usew->max_eus_pew_subswice > device->max_eus_pew_subswice)
		wetuwn -EINVAW;

	context->swice_mask = usew->swice_mask;
	context->subswice_mask = usew->subswice_mask;
	context->min_eus_pew_subswice = usew->min_eus_pew_subswice;
	context->max_eus_pew_subswice = usew->max_eus_pew_subswice;

	/* Pawt specific westwictions. */
	if (GWAPHICS_VEW(i915) == 11) {
		unsigned int hw_s = hweight8(device->swice_mask);
		unsigned int hw_ss_pew_s = hweight8(dev_subswice_mask);
		unsigned int weq_s = hweight8(context->swice_mask);
		unsigned int weq_ss = hweight8(context->subswice_mask);

		/*
		 * Onwy fuww subswice enabwement is possibwe if mowe than one
		 * swice is tuwned on.
		 */
		if (weq_s > 1 && weq_ss != hw_ss_pew_s)
			wetuwn -EINVAW;

		/*
		 * If mowe than fouw (SScount bitfiewd wimit) subswices awe
		 * wequested then the numbew has to be even.
		 */
		if (weq_ss > 4 && (weq_ss & 1))
			wetuwn -EINVAW;

		/*
		 * If onwy one swice is enabwed and subswice count is bewow the
		 * device fuww enabwement, it must be at most hawf of the aww
		 * avaiwabwe subswices.
		 */
		if (weq_s == 1 && weq_ss < hw_ss_pew_s &&
		    weq_ss > (hw_ss_pew_s / 2))
			wetuwn -EINVAW;

		/* ABI westwiction - VME use case onwy. */

		/* Aww swices ow one swice onwy. */
		if (weq_s != 1 && weq_s != hw_s)
			wetuwn -EINVAW;

		/*
		 * Hawf subswices ow fuww enabwement onwy when one swice is
		 * enabwed.
		 */
		if (weq_s == 1 &&
		    (weq_ss != hw_ss_pew_s && weq_ss != (hw_ss_pew_s / 2)))
			wetuwn -EINVAW;

		/* No EU configuwation changes. */
		if ((usew->min_eus_pew_subswice !=
		     device->max_eus_pew_subswice) ||
		    (usew->max_eus_pew_subswice !=
		     device->max_eus_pew_subswice))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int set_sseu(stwuct i915_gem_context *ctx,
		    stwuct dwm_i915_gem_context_pawam *awgs)
{
	stwuct dwm_i915_pwivate *i915 = ctx->i915;
	stwuct dwm_i915_gem_context_pawam_sseu usew_sseu;
	stwuct intew_context *ce;
	stwuct intew_sseu sseu;
	unsigned wong wookup;
	int wet;

	if (awgs->size < sizeof(usew_sseu))
		wetuwn -EINVAW;

	if (GWAPHICS_VEW(i915) != 11)
		wetuwn -ENODEV;

	if (copy_fwom_usew(&usew_sseu, u64_to_usew_ptw(awgs->vawue),
			   sizeof(usew_sseu)))
		wetuwn -EFAUWT;

	if (usew_sseu.wsvd)
		wetuwn -EINVAW;

	if (usew_sseu.fwags & ~(I915_CONTEXT_SSEU_FWAG_ENGINE_INDEX))
		wetuwn -EINVAW;

	wookup = 0;
	if (usew_sseu.fwags & I915_CONTEXT_SSEU_FWAG_ENGINE_INDEX)
		wookup |= WOOKUP_USEW_INDEX;

	ce = wookup_usew_engine(ctx, wookup, &usew_sseu.engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	/* Onwy wendew engine suppowts WPCS configuwation. */
	if (ce->engine->cwass != WENDEW_CWASS) {
		wet = -ENODEV;
		goto out_ce;
	}

	wet = i915_gem_usew_to_context_sseu(ce->engine->gt, &usew_sseu, &sseu);
	if (wet)
		goto out_ce;

	wet = intew_context_weconfiguwe_sseu(ce, sseu);
	if (wet)
		goto out_ce;

	awgs->size = sizeof(usew_sseu);

out_ce:
	intew_context_put(ce);
	wetuwn wet;
}

static int
set_pewsistence(stwuct i915_gem_context *ctx,
		const stwuct dwm_i915_gem_context_pawam *awgs)
{
	if (awgs->size)
		wetuwn -EINVAW;

	wetuwn __context_set_pewsistence(ctx, awgs->vawue);
}

static int set_pwiowity(stwuct i915_gem_context *ctx,
			const stwuct dwm_i915_gem_context_pawam *awgs)
{
	stwuct i915_gem_engines_itew it;
	stwuct intew_context *ce;
	int eww;

	eww = vawidate_pwiowity(ctx->i915, awgs);
	if (eww)
		wetuwn eww;

	ctx->sched.pwiowity = awgs->vawue;

	fow_each_gem_engine(ce, i915_gem_context_wock_engines(ctx), it) {
		if (!intew_engine_has_timeswices(ce->engine))
			continue;

		if (ctx->sched.pwiowity >= I915_PWIOWITY_NOWMAW &&
		    intew_engine_has_semaphowes(ce->engine))
			intew_context_set_use_semaphowes(ce);
		ewse
			intew_context_cweaw_use_semaphowes(ce);
	}
	i915_gem_context_unwock_engines(ctx);

	wetuwn 0;
}

static int get_pwotected(stwuct i915_gem_context *ctx,
			 stwuct dwm_i915_gem_context_pawam *awgs)
{
	awgs->size = 0;
	awgs->vawue = i915_gem_context_uses_pwotected_content(ctx);

	wetuwn 0;
}

static int ctx_setpawam(stwuct dwm_i915_fiwe_pwivate *fpwiv,
			stwuct i915_gem_context *ctx,
			stwuct dwm_i915_gem_context_pawam *awgs)
{
	int wet = 0;

	switch (awgs->pawam) {
	case I915_CONTEXT_PAWAM_NO_EWWOW_CAPTUWE:
		if (awgs->size)
			wet = -EINVAW;
		ewse if (awgs->vawue)
			i915_gem_context_set_no_ewwow_captuwe(ctx);
		ewse
			i915_gem_context_cweaw_no_ewwow_captuwe(ctx);
		bweak;

	case I915_CONTEXT_PAWAM_BANNABWE:
		if (awgs->size)
			wet = -EINVAW;
		ewse if (!capabwe(CAP_SYS_ADMIN) && !awgs->vawue)
			wet = -EPEWM;
		ewse if (awgs->vawue)
			i915_gem_context_set_bannabwe(ctx);
		ewse if (i915_gem_context_uses_pwotected_content(ctx))
			wet = -EPEWM; /* can't cweaw this fow pwotected contexts */
		ewse
			i915_gem_context_cweaw_bannabwe(ctx);
		bweak;

	case I915_CONTEXT_PAWAM_WECOVEWABWE:
		if (awgs->size)
			wet = -EINVAW;
		ewse if (!awgs->vawue)
			i915_gem_context_cweaw_wecovewabwe(ctx);
		ewse if (i915_gem_context_uses_pwotected_content(ctx))
			wet = -EPEWM; /* can't set this fow pwotected contexts */
		ewse
			i915_gem_context_set_wecovewabwe(ctx);
		bweak;

	case I915_CONTEXT_PAWAM_PWIOWITY:
		wet = set_pwiowity(ctx, awgs);
		bweak;

	case I915_CONTEXT_PAWAM_SSEU:
		wet = set_sseu(ctx, awgs);
		bweak;

	case I915_CONTEXT_PAWAM_PEWSISTENCE:
		wet = set_pewsistence(ctx, awgs);
		bweak;

	case I915_CONTEXT_PAWAM_PWOTECTED_CONTENT:
	case I915_CONTEXT_PAWAM_NO_ZEWOMAP:
	case I915_CONTEXT_PAWAM_BAN_PEWIOD:
	case I915_CONTEXT_PAWAM_WINGSIZE:
	case I915_CONTEXT_PAWAM_VM:
	case I915_CONTEXT_PAWAM_ENGINES:
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

stwuct cweate_ext {
	stwuct i915_gem_pwoto_context *pc;
	stwuct dwm_i915_fiwe_pwivate *fpwiv;
};

static int cweate_setpawam(stwuct i915_usew_extension __usew *ext, void *data)
{
	stwuct dwm_i915_gem_context_cweate_ext_setpawam wocaw;
	const stwuct cweate_ext *awg = data;

	if (copy_fwom_usew(&wocaw, ext, sizeof(wocaw)))
		wetuwn -EFAUWT;

	if (wocaw.pawam.ctx_id)
		wetuwn -EINVAW;

	wetuwn set_pwoto_ctx_pawam(awg->fpwiv, awg->pc, &wocaw.pawam);
}

static int invawid_ext(stwuct i915_usew_extension __usew *ext, void *data)
{
	wetuwn -EINVAW;
}

static const i915_usew_extension_fn cweate_extensions[] = {
	[I915_CONTEXT_CWEATE_EXT_SETPAWAM] = cweate_setpawam,
	[I915_CONTEXT_CWEATE_EXT_CWONE] = invawid_ext,
};

static boow cwient_is_banned(stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv)
{
	wetuwn atomic_wead(&fiwe_pwiv->ban_scowe) >= I915_CWIENT_SCOWE_BANNED;
}

static inwine stwuct i915_gem_context *
__context_wookup(stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv, u32 id)
{
	stwuct i915_gem_context *ctx;

	wcu_wead_wock();
	ctx = xa_woad(&fiwe_pwiv->context_xa, id);
	if (ctx && !kwef_get_unwess_zewo(&ctx->wef))
		ctx = NUWW;
	wcu_wead_unwock();

	wetuwn ctx;
}

static stwuct i915_gem_context *
finawize_cweate_context_wocked(stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv,
			       stwuct i915_gem_pwoto_context *pc, u32 id)
{
	stwuct i915_gem_context *ctx;
	void *owd;

	wockdep_assewt_hewd(&fiwe_pwiv->pwoto_context_wock);

	ctx = i915_gem_cweate_context(fiwe_pwiv->i915, pc);
	if (IS_EWW(ctx))
		wetuwn ctx;

	/*
	 * One fow the xawway and one fow the cawwew.  We need to gwab
	 * the wefewence *pwiow* to making the ctx visbwe to usewspace
	 * in gem_context_wegistew(), as at any point aftew that
	 * usewspace can twy to wace us with anothew thwead destwoying
	 * the context undew ouw feet.
	 */
	i915_gem_context_get(ctx);

	gem_context_wegistew(ctx, fiwe_pwiv, id);

	owd = xa_ewase(&fiwe_pwiv->pwoto_context_xa, id);
	GEM_BUG_ON(owd != pc);
	pwoto_context_cwose(fiwe_pwiv->i915, pc);

	wetuwn ctx;
}

stwuct i915_gem_context *
i915_gem_context_wookup(stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv, u32 id)
{
	stwuct i915_gem_pwoto_context *pc;
	stwuct i915_gem_context *ctx;

	ctx = __context_wookup(fiwe_pwiv, id);
	if (ctx)
		wetuwn ctx;

	mutex_wock(&fiwe_pwiv->pwoto_context_wock);
	/* Twy one mowe time undew the wock */
	ctx = __context_wookup(fiwe_pwiv, id);
	if (!ctx) {
		pc = xa_woad(&fiwe_pwiv->pwoto_context_xa, id);
		if (!pc)
			ctx = EWW_PTW(-ENOENT);
		ewse
			ctx = finawize_cweate_context_wocked(fiwe_pwiv, pc, id);
	}
	mutex_unwock(&fiwe_pwiv->pwoto_context_wock);

	wetuwn ctx;
}

int i915_gem_context_cweate_ioctw(stwuct dwm_device *dev, void *data,
				  stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct dwm_i915_gem_context_cweate_ext *awgs = data;
	stwuct cweate_ext ext_data;
	int wet;
	u32 id;

	if (!DWIVEW_CAPS(i915)->has_wogicaw_contexts)
		wetuwn -ENODEV;

	if (awgs->fwags & I915_CONTEXT_CWEATE_FWAGS_UNKNOWN)
		wetuwn -EINVAW;

	wet = intew_gt_tewminawwy_wedged(to_gt(i915));
	if (wet)
		wetuwn wet;

	ext_data.fpwiv = fiwe->dwivew_pwiv;
	if (cwient_is_banned(ext_data.fpwiv)) {
		dwm_dbg(&i915->dwm,
			"cwient %s[%d] banned fwom cweating ctx\n",
			cuwwent->comm, task_pid_nw(cuwwent));
		wetuwn -EIO;
	}

	ext_data.pc = pwoto_context_cweate(fiwe->dwivew_pwiv, i915,
					   awgs->fwags);
	if (IS_EWW(ext_data.pc))
		wetuwn PTW_EWW(ext_data.pc);

	if (awgs->fwags & I915_CONTEXT_CWEATE_FWAGS_USE_EXTENSIONS) {
		wet = i915_usew_extensions(u64_to_usew_ptw(awgs->extensions),
					   cweate_extensions,
					   AWWAY_SIZE(cweate_extensions),
					   &ext_data);
		if (wet)
			goto eww_pc;
	}

	if (GWAPHICS_VEW(i915) > 12) {
		stwuct i915_gem_context *ctx;

		/* Get ouwsewves a context ID */
		wet = xa_awwoc(&ext_data.fpwiv->context_xa, &id, NUWW,
			       xa_wimit_32b, GFP_KEWNEW);
		if (wet)
			goto eww_pc;

		ctx = i915_gem_cweate_context(i915, ext_data.pc);
		if (IS_EWW(ctx)) {
			wet = PTW_EWW(ctx);
			goto eww_pc;
		}

		pwoto_context_cwose(i915, ext_data.pc);
		gem_context_wegistew(ctx, ext_data.fpwiv, id);
	} ewse {
		wet = pwoto_context_wegistew(ext_data.fpwiv, ext_data.pc, &id);
		if (wet < 0)
			goto eww_pc;
	}

	awgs->ctx_id = id;

	wetuwn 0;

eww_pc:
	pwoto_context_cwose(i915, ext_data.pc);
	wetuwn wet;
}

int i915_gem_context_destwoy_ioctw(stwuct dwm_device *dev, void *data,
				   stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_gem_context_destwoy *awgs = data;
	stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv = fiwe->dwivew_pwiv;
	stwuct i915_gem_pwoto_context *pc;
	stwuct i915_gem_context *ctx;

	if (awgs->pad != 0)
		wetuwn -EINVAW;

	if (!awgs->ctx_id)
		wetuwn -ENOENT;

	/* We need to howd the pwoto-context wock hewe to pwevent waces
	 * with finawize_cweate_context_wocked().
	 */
	mutex_wock(&fiwe_pwiv->pwoto_context_wock);
	ctx = xa_ewase(&fiwe_pwiv->context_xa, awgs->ctx_id);
	pc = xa_ewase(&fiwe_pwiv->pwoto_context_xa, awgs->ctx_id);
	mutex_unwock(&fiwe_pwiv->pwoto_context_wock);

	if (!ctx && !pc)
		wetuwn -ENOENT;
	GEM_WAWN_ON(ctx && pc);

	if (pc)
		pwoto_context_cwose(fiwe_pwiv->i915, pc);

	if (ctx)
		context_cwose(ctx);

	wetuwn 0;
}

static int get_sseu(stwuct i915_gem_context *ctx,
		    stwuct dwm_i915_gem_context_pawam *awgs)
{
	stwuct dwm_i915_gem_context_pawam_sseu usew_sseu;
	stwuct intew_context *ce;
	unsigned wong wookup;
	int eww;

	if (awgs->size == 0)
		goto out;
	ewse if (awgs->size < sizeof(usew_sseu))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&usew_sseu, u64_to_usew_ptw(awgs->vawue),
			   sizeof(usew_sseu)))
		wetuwn -EFAUWT;

	if (usew_sseu.wsvd)
		wetuwn -EINVAW;

	if (usew_sseu.fwags & ~(I915_CONTEXT_SSEU_FWAG_ENGINE_INDEX))
		wetuwn -EINVAW;

	wookup = 0;
	if (usew_sseu.fwags & I915_CONTEXT_SSEU_FWAG_ENGINE_INDEX)
		wookup |= WOOKUP_USEW_INDEX;

	ce = wookup_usew_engine(ctx, wookup, &usew_sseu.engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	eww = intew_context_wock_pinned(ce); /* sewiawises with set_sseu */
	if (eww) {
		intew_context_put(ce);
		wetuwn eww;
	}

	usew_sseu.swice_mask = ce->sseu.swice_mask;
	usew_sseu.subswice_mask = ce->sseu.subswice_mask;
	usew_sseu.min_eus_pew_subswice = ce->sseu.min_eus_pew_subswice;
	usew_sseu.max_eus_pew_subswice = ce->sseu.max_eus_pew_subswice;

	intew_context_unwock_pinned(ce);
	intew_context_put(ce);

	if (copy_to_usew(u64_to_usew_ptw(awgs->vawue), &usew_sseu,
			 sizeof(usew_sseu)))
		wetuwn -EFAUWT;

out:
	awgs->size = sizeof(usew_sseu);

	wetuwn 0;
}

int i915_gem_context_getpawam_ioctw(stwuct dwm_device *dev, void *data,
				    stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv = fiwe->dwivew_pwiv;
	stwuct dwm_i915_gem_context_pawam *awgs = data;
	stwuct i915_gem_context *ctx;
	stwuct i915_addwess_space *vm;
	int wet = 0;

	ctx = i915_gem_context_wookup(fiwe_pwiv, awgs->ctx_id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	switch (awgs->pawam) {
	case I915_CONTEXT_PAWAM_GTT_SIZE:
		awgs->size = 0;
		vm = i915_gem_context_get_eb_vm(ctx);
		awgs->vawue = vm->totaw;
		i915_vm_put(vm);

		bweak;

	case I915_CONTEXT_PAWAM_NO_EWWOW_CAPTUWE:
		awgs->size = 0;
		awgs->vawue = i915_gem_context_no_ewwow_captuwe(ctx);
		bweak;

	case I915_CONTEXT_PAWAM_BANNABWE:
		awgs->size = 0;
		awgs->vawue = i915_gem_context_is_bannabwe(ctx);
		bweak;

	case I915_CONTEXT_PAWAM_WECOVEWABWE:
		awgs->size = 0;
		awgs->vawue = i915_gem_context_is_wecovewabwe(ctx);
		bweak;

	case I915_CONTEXT_PAWAM_PWIOWITY:
		awgs->size = 0;
		awgs->vawue = ctx->sched.pwiowity;
		bweak;

	case I915_CONTEXT_PAWAM_SSEU:
		wet = get_sseu(ctx, awgs);
		bweak;

	case I915_CONTEXT_PAWAM_VM:
		wet = get_ppgtt(fiwe_pwiv, ctx, awgs);
		bweak;

	case I915_CONTEXT_PAWAM_PEWSISTENCE:
		awgs->size = 0;
		awgs->vawue = i915_gem_context_is_pewsistent(ctx);
		bweak;

	case I915_CONTEXT_PAWAM_PWOTECTED_CONTENT:
		wet = get_pwotected(ctx, awgs);
		bweak;

	case I915_CONTEXT_PAWAM_NO_ZEWOMAP:
	case I915_CONTEXT_PAWAM_BAN_PEWIOD:
	case I915_CONTEXT_PAWAM_ENGINES:
	case I915_CONTEXT_PAWAM_WINGSIZE:
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	i915_gem_context_put(ctx);
	wetuwn wet;
}

int i915_gem_context_setpawam_ioctw(stwuct dwm_device *dev, void *data,
				    stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv = fiwe->dwivew_pwiv;
	stwuct dwm_i915_gem_context_pawam *awgs = data;
	stwuct i915_gem_pwoto_context *pc;
	stwuct i915_gem_context *ctx;
	int wet = 0;

	mutex_wock(&fiwe_pwiv->pwoto_context_wock);
	ctx = __context_wookup(fiwe_pwiv, awgs->ctx_id);
	if (!ctx) {
		pc = xa_woad(&fiwe_pwiv->pwoto_context_xa, awgs->ctx_id);
		if (pc) {
			/* Contexts shouwd be finawized inside
			 * GEM_CONTEXT_CWEATE stawting with gwaphics
			 * vewsion 13.
			 */
			WAWN_ON(GWAPHICS_VEW(fiwe_pwiv->i915) > 12);
			wet = set_pwoto_ctx_pawam(fiwe_pwiv, pc, awgs);
		} ewse {
			wet = -ENOENT;
		}
	}
	mutex_unwock(&fiwe_pwiv->pwoto_context_wock);

	if (ctx) {
		wet = ctx_setpawam(fiwe_pwiv, ctx, awgs);
		i915_gem_context_put(ctx);
	}

	wetuwn wet;
}

int i915_gem_context_weset_stats_ioctw(stwuct dwm_device *dev,
				       void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct dwm_i915_weset_stats *awgs = data;
	stwuct i915_gem_context *ctx;

	if (awgs->fwags || awgs->pad)
		wetuwn -EINVAW;

	ctx = i915_gem_context_wookup(fiwe->dwivew_pwiv, awgs->ctx_id);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	/*
	 * We opt fow unsewiawised weads hewe. This may wesuwt in teawing
	 * in the extwemewy unwikewy event of a GPU hang on this context
	 * as we awe quewying them. If we need that extwa wayew of pwotection,
	 * we shouwd wwap the hangstats with a seqwock.
	 */

	if (capabwe(CAP_SYS_ADMIN))
		awgs->weset_count = i915_weset_count(&i915->gpu_ewwow);
	ewse
		awgs->weset_count = 0;

	awgs->batch_active = atomic_wead(&ctx->guiwty_count);
	awgs->batch_pending = atomic_wead(&ctx->active_count);

	i915_gem_context_put(ctx);
	wetuwn 0;
}

/* GEM context-engines itewatow: fow_each_gem_engine() */
stwuct intew_context *
i915_gem_engines_itew_next(stwuct i915_gem_engines_itew *it)
{
	const stwuct i915_gem_engines *e = it->engines;
	stwuct intew_context *ctx;

	if (unwikewy(!e))
		wetuwn NUWW;

	do {
		if (it->idx >= e->num_engines)
			wetuwn NUWW;

		ctx = e->engines[it->idx++];
	} whiwe (!ctx);

	wetuwn ctx;
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/mock_context.c"
#incwude "sewftests/i915_gem_context.c"
#endif

void i915_gem_context_moduwe_exit(void)
{
	kmem_cache_destwoy(swab_wuts);
}

int __init i915_gem_context_moduwe_init(void)
{
	swab_wuts = KMEM_CACHE(i915_wut_handwe, 0);
	if (!swab_wuts)
		wetuwn -ENOMEM;

	wetuwn 0;
}
