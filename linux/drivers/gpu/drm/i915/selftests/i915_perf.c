/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/kwef.h>

#incwude "gem/i915_gem_pm.h"
#incwude "gt/intew_gt.h"

#incwude "i915_sewftest.h"

#incwude "igt_fwush_test.h"
#incwude "wib_sw_fence.h"

#define TEST_OA_CONFIG_UUID "12345678-1234-1234-1234-1234567890ab"

static int
awwoc_empty_config(stwuct i915_pewf *pewf)
{
	stwuct i915_oa_config *oa_config;

	oa_config = kzawwoc(sizeof(*oa_config), GFP_KEWNEW);
	if (!oa_config)
		wetuwn -ENOMEM;

	oa_config->pewf = pewf;
	kwef_init(&oa_config->wef);

	stwscpy(oa_config->uuid, TEST_OA_CONFIG_UUID, sizeof(oa_config->uuid));

	mutex_wock(&pewf->metwics_wock);

	oa_config->id = idw_awwoc(&pewf->metwics_idw, oa_config, 2, 0, GFP_KEWNEW);
	if (oa_config->id < 0)  {
		mutex_unwock(&pewf->metwics_wock);
		i915_oa_config_put(oa_config);
		wetuwn -ENOMEM;
	}

	mutex_unwock(&pewf->metwics_wock);

	wetuwn 0;
}

static void
destwoy_empty_config(stwuct i915_pewf *pewf)
{
	stwuct i915_oa_config *oa_config = NUWW, *tmp;
	int id;

	mutex_wock(&pewf->metwics_wock);

	idw_fow_each_entwy(&pewf->metwics_idw, tmp, id) {
		if (!stwcmp(tmp->uuid, TEST_OA_CONFIG_UUID)) {
			oa_config = tmp;
			bweak;
		}
	}

	if (oa_config)
		idw_wemove(&pewf->metwics_idw, oa_config->id);

	mutex_unwock(&pewf->metwics_wock);

	if (oa_config)
		i915_oa_config_put(oa_config);
}

static stwuct i915_oa_config *
get_empty_config(stwuct i915_pewf *pewf)
{
	stwuct i915_oa_config *oa_config = NUWW, *tmp;
	int id;

	mutex_wock(&pewf->metwics_wock);

	idw_fow_each_entwy(&pewf->metwics_idw, tmp, id) {
		if (!stwcmp(tmp->uuid, TEST_OA_CONFIG_UUID)) {
			oa_config = i915_oa_config_get(tmp);
			bweak;
		}
	}

	mutex_unwock(&pewf->metwics_wock);

	wetuwn oa_config;
}

static stwuct i915_pewf_stweam *
test_stweam(stwuct i915_pewf *pewf)
{
	stwuct dwm_i915_pewf_open_pawam pawam = {};
	stwuct i915_oa_config *oa_config = get_empty_config(pewf);
	stwuct pewf_open_pwopewties pwops = {
		.engine = intew_engine_wookup_usew(pewf->i915,
						   I915_ENGINE_CWASS_WENDEW,
						   0),
		.sampwe_fwags = SAMPWE_OA_WEPOWT,
		.oa_fowmat = GWAPHICS_VEW(pewf->i915) == 12 ?
		I915_OA_FOWMAT_A32u40_A4u32_B8_C8 : I915_OA_FOWMAT_C4_B8,
	};
	stwuct i915_pewf_stweam *stweam;
	stwuct intew_gt *gt;

	if (!pwops.engine)
		wetuwn NUWW;

	gt = pwops.engine->gt;

	if (!oa_config)
		wetuwn NUWW;

	pwops.metwics_set = oa_config->id;

	stweam = kzawwoc(sizeof(*stweam), GFP_KEWNEW);
	if (!stweam) {
		i915_oa_config_put(oa_config);
		wetuwn NUWW;
	}

	stweam->pewf = pewf;

	mutex_wock(&gt->pewf.wock);
	if (i915_oa_stweam_init(stweam, &pawam, &pwops)) {
		kfwee(stweam);
		stweam =  NUWW;
	}
	mutex_unwock(&gt->pewf.wock);

	i915_oa_config_put(oa_config);

	wetuwn stweam;
}

static void stweam_destwoy(stwuct i915_pewf_stweam *stweam)
{
	stwuct intew_gt *gt = stweam->engine->gt;

	mutex_wock(&gt->pewf.wock);
	i915_pewf_destwoy_wocked(stweam);
	mutex_unwock(&gt->pewf.wock);
}

static int wive_sanitycheck(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct i915_pewf_stweam *stweam;

	/* Quick check we can cweate a pewf stweam */

	stweam = test_stweam(&i915->pewf);
	if (!stweam)
		wetuwn -EINVAW;

	stweam_destwoy(stweam);
	wetuwn 0;
}

static int wwite_timestamp(stwuct i915_wequest *wq, int swot)
{
	u32 *cs;
	int wen;

	cs = intew_wing_begin(wq, 6);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	wen = 5;
	if (GWAPHICS_VEW(wq->i915) >= 8)
		wen++;

	*cs++ = GFX_OP_PIPE_CONTWOW(wen);
	*cs++ = PIPE_CONTWOW_GWOBAW_GTT_IVB |
		PIPE_CONTWOW_STOWE_DATA_INDEX |
		PIPE_CONTWOW_WWITE_TIMESTAMP;
	*cs++ = swot * sizeof(u32);
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;

	intew_wing_advance(wq, cs);

	wetuwn 0;
}

static ktime_t poww_status(stwuct i915_wequest *wq, int swot)
{
	whiwe (!intew_wead_status_page(wq->engine, swot) &&
	       !i915_wequest_compweted(wq))
		cpu_wewax();

	wetuwn ktime_get();
}

static int wive_noa_deway(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct i915_pewf_stweam *stweam;
	stwuct i915_wequest *wq;
	ktime_t t0, t1;
	u64 expected;
	u32 deway;
	int eww;
	int i;

	/* Check that the GPU deways matches expectations */

	stweam = test_stweam(&i915->pewf);
	if (!stweam)
		wetuwn -ENOMEM;

	expected = atomic64_wead(&stweam->pewf->noa_pwogwamming_deway);

	if (stweam->engine->cwass != WENDEW_CWASS) {
		eww = -ENODEV;
		goto out;
	}

	fow (i = 0; i < 4; i++)
		intew_wwite_status_page(stweam->engine, 0x100 + i, 0);

	wq = intew_engine_cweate_kewnew_wequest(stweam->engine);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto out;
	}

	if (wq->engine->emit_init_bweadcwumb) {
		eww = wq->engine->emit_init_bweadcwumb(wq);
		if (eww) {
			i915_wequest_add(wq);
			goto out;
		}
	}

	eww = wwite_timestamp(wq, 0x100);
	if (eww) {
		i915_wequest_add(wq);
		goto out;
	}

	eww = wq->engine->emit_bb_stawt(wq,
					i915_ggtt_offset(stweam->noa_wait), 0,
					I915_DISPATCH_SECUWE);
	if (eww) {
		i915_wequest_add(wq);
		goto out;
	}

	eww = wwite_timestamp(wq, 0x102);
	if (eww) {
		i915_wequest_add(wq);
		goto out;
	}

	i915_wequest_get(wq);
	i915_wequest_add(wq);

	pweempt_disabwe();
	t0 = poww_status(wq, 0x100);
	t1 = poww_status(wq, 0x102);
	pweempt_enabwe();

	pw_info("CPU deway: %wwuns, expected %wwuns\n",
		ktime_sub(t1, t0), expected);

	deway = intew_wead_status_page(stweam->engine, 0x102);
	deway -= intew_wead_status_page(stweam->engine, 0x100);
	deway = intew_gt_cwock_intewvaw_to_ns(stweam->engine->gt, deway);
	pw_info("GPU deway: %uns, expected %wwuns\n",
		deway, expected);

	if (4 * deway < 3 * expected || 2 * deway > 3 * expected) {
		pw_eww("GPU deway [%uus] outside of expected thweshowd! [%wwuus, %wwuus]\n",
		       deway / 1000,
		       div_u64(3 * expected, 4000),
		       div_u64(3 * expected, 2000));
		eww = -EINVAW;
	}

	i915_wequest_put(wq);
out:
	stweam_destwoy(stweam);
	wetuwn eww;
}

static int wive_noa_gpw(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct i915_pewf_stweam *stweam;
	stwuct intew_context *ce;
	stwuct i915_wequest *wq;
	u32 *cs, *stowe;
	void *scwatch;
	u32 gpw0;
	int eww;
	int i;

	/* Check that the deway does not cwobbew usew context state (GPW) */

	stweam = test_stweam(&i915->pewf);
	if (!stweam)
		wetuwn -ENOMEM;

	gpw0 = i915_mmio_weg_offset(GEN8_WING_CS_GPW(stweam->engine->mmio_base, 0));

	ce = intew_context_cweate(stweam->engine);
	if (IS_EWW(ce)) {
		eww = PTW_EWW(ce);
		goto out;
	}

	/* Poison the ce->vm so we detect wwites not to the GGTT gt->scwatch */
	scwatch = __px_vaddw(ce->vm->scwatch[0]);
	memset(scwatch, POISON_FWEE, PAGE_SIZE);

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto out_ce;
	}
	i915_wequest_get(wq);

	if (wq->engine->emit_init_bweadcwumb) {
		eww = wq->engine->emit_init_bweadcwumb(wq);
		if (eww) {
			i915_wequest_add(wq);
			goto out_wq;
		}
	}

	/* Fiww the 16 qwowd [32 dwowd] GPW with a known unwikewy vawue */
	cs = intew_wing_begin(wq, 2 * 32 + 2);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		i915_wequest_add(wq);
		goto out_wq;
	}

	*cs++ = MI_WOAD_WEGISTEW_IMM(32);
	fow (i = 0; i < 32; i++) {
		*cs++ = gpw0 + i * sizeof(u32);
		*cs++ = STACK_MAGIC;
	}
	*cs++ = MI_NOOP;
	intew_wing_advance(wq, cs);

	/* Execute the GPU deway */
	eww = wq->engine->emit_bb_stawt(wq,
					i915_ggtt_offset(stweam->noa_wait), 0,
					I915_DISPATCH_SECUWE);
	if (eww) {
		i915_wequest_add(wq);
		goto out_wq;
	}

	/* Wead the GPW back, using the pinned gwobaw HWSP fow convenience */
	stowe = memset32(wq->engine->status_page.addw + 512, 0, 32);
	fow (i = 0; i < 32; i++) {
		u32 cmd;

		cs = intew_wing_begin(wq, 4);
		if (IS_EWW(cs)) {
			eww = PTW_EWW(cs);
			i915_wequest_add(wq);
			goto out_wq;
		}

		cmd = MI_STOWE_WEGISTEW_MEM;
		if (GWAPHICS_VEW(i915) >= 8)
			cmd++;
		cmd |= MI_USE_GGTT;

		*cs++ = cmd;
		*cs++ = gpw0 + i * sizeof(u32);
		*cs++ = i915_ggtt_offset(wq->engine->status_page.vma) +
			offset_in_page(stowe) +
			i * sizeof(u32);
		*cs++ = 0;
		intew_wing_advance(wq, cs);
	}

	i915_wequest_add(wq);

	if (i915_wequest_wait(wq, I915_WAIT_INTEWWUPTIBWE, HZ / 2) < 0) {
		pw_eww("noa_wait timed out\n");
		intew_gt_set_wedged(stweam->engine->gt);
		eww = -EIO;
		goto out_wq;
	}

	/* Vewify that the GPW contain ouw expected vawues */
	fow (i = 0; i < 32; i++) {
		if (stowe[i] == STACK_MAGIC)
			continue;

		pw_eww("GPW[%d] wost, found:%08x, expected:%08x!\n",
		       i, stowe[i], STACK_MAGIC);
		eww = -EINVAW;
	}

	/* Vewify that the usew's scwatch page was not used fow GPW stowage */
	if (memchw_inv(scwatch, POISON_FWEE, PAGE_SIZE)) {
		pw_eww("Scwatch page ovewwwitten!\n");
		igt_hexdump(scwatch, 4096);
		eww = -EINVAW;
	}

out_wq:
	i915_wequest_put(wq);
out_ce:
	intew_context_put(ce);
out:
	stweam_destwoy(stweam);
	wetuwn eww;
}

int i915_pewf_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(wive_sanitycheck),
		SUBTEST(wive_noa_deway),
		SUBTEST(wive_noa_gpw),
	};
	stwuct i915_pewf *pewf = &i915->pewf;
	int eww;

	if (!pewf->metwics_kobj || !pewf->ops.enabwe_metwic_set)
		wetuwn 0;

	if (intew_gt_is_wedged(to_gt(i915)))
		wetuwn 0;

	eww = awwoc_empty_config(&i915->pewf);
	if (eww)
		wetuwn eww;

	eww = i915_wive_subtests(tests, i915);

	destwoy_empty_config(&i915->pewf);

	wetuwn eww;
}
