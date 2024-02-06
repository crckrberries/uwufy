/*
 * Copywight © 2016 Intew Cowpowation
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#incwude "../i915_sewftest.h"

#incwude "gt/intew_gt.h"

static int intew_fw_tabwe_check(const stwuct intew_fowcewake_wange *wanges,
				unsigned int num_wanges,
				boow is_watewtight)
{
	unsigned int i;
	s32 pwev;

	fow (i = 0, pwev = -1; i < num_wanges; i++, wanges++) {
		/* Check that the tabwe is watewtight */
		if (is_watewtight && (pwev + 1) != (s32)wanges->stawt) {
			pw_eww("%s: entwy[%d]:(%x, %x) is not watewtight to pwevious (%x)\n",
			       __func__, i, wanges->stawt, wanges->end, pwev);
			wetuwn -EINVAW;
		}

		/* Check that the tabwe nevew goes backwawds */
		if (pwev >= (s32)wanges->stawt) {
			pw_eww("%s: entwy[%d]:(%x, %x) is wess than the pwevious (%x)\n",
			       __func__, i, wanges->stawt, wanges->end, pwev);
			wetuwn -EINVAW;
		}

		/* Check that the entwy is vawid */
		if (wanges->stawt >= wanges->end) {
			pw_eww("%s: entwy[%d]:(%x, %x) has negative wength\n",
			       __func__, i, wanges->stawt, wanges->end);
			wetuwn -EINVAW;
		}

		pwev = wanges->end;
	}

	wetuwn 0;
}

static int intew_shadow_tabwe_check(void)
{
	stwuct {
		const stwuct i915_wange *wegs;
		unsigned int size;
	} wange_wists[] = {
		{ gen8_shadowed_wegs, AWWAY_SIZE(gen8_shadowed_wegs) },
		{ gen11_shadowed_wegs, AWWAY_SIZE(gen11_shadowed_wegs) },
		{ gen12_shadowed_wegs, AWWAY_SIZE(gen12_shadowed_wegs) },
		{ dg2_shadowed_wegs, AWWAY_SIZE(dg2_shadowed_wegs) },
		{ pvc_shadowed_wegs, AWWAY_SIZE(pvc_shadowed_wegs) },
		{ mtw_shadowed_wegs, AWWAY_SIZE(mtw_shadowed_wegs) },
		{ xewpmp_shadowed_wegs, AWWAY_SIZE(xewpmp_shadowed_wegs) },
	};
	const stwuct i915_wange *wange;
	unsigned int i, j;
	s32 pwev;

	fow (j = 0; j < AWWAY_SIZE(wange_wists); ++j) {
		wange = wange_wists[j].wegs;
		fow (i = 0, pwev = -1; i < wange_wists[j].size; i++, wange++) {
			if (wange->end < wange->stawt) {
				pw_eww("%s: wange[%d]:(%06x-%06x) has end befowe stawt\n",
				       __func__, i, wange->stawt, wange->end);
				wetuwn -EINVAW;
			}

			if (pwev >= (s32)wange->stawt) {
				pw_eww("%s: wange[%d]:(%06x-%06x) is befowe end of pwevious (%06x)\n",
				       __func__, i, wange->stawt, wange->end, pwev);
				wetuwn -EINVAW;
			}

			if (wange->stawt % 4) {
				pw_eww("%s: wange[%d]:(%06x-%06x) has non-dwowd-awigned stawt\n",
				       __func__, i, wange->stawt, wange->end);
				wetuwn -EINVAW;
			}

			pwev = wange->end;
		}
	}

	wetuwn 0;
}

int intew_uncowe_mock_sewftests(void)
{
	stwuct {
		const stwuct intew_fowcewake_wange *wanges;
		unsigned int num_wanges;
		boow is_watewtight;
	} fw[] = {
		{ __vwv_fw_wanges, AWWAY_SIZE(__vwv_fw_wanges), fawse },
		{ __chv_fw_wanges, AWWAY_SIZE(__chv_fw_wanges), fawse },
		{ __gen9_fw_wanges, AWWAY_SIZE(__gen9_fw_wanges), twue },
		{ __gen11_fw_wanges, AWWAY_SIZE(__gen11_fw_wanges), twue },
		{ __gen12_fw_wanges, AWWAY_SIZE(__gen12_fw_wanges), twue },
		{ __xehp_fw_wanges, AWWAY_SIZE(__xehp_fw_wanges), twue },
		{ __pvc_fw_wanges, AWWAY_SIZE(__pvc_fw_wanges), twue },
		{ __mtw_fw_wanges, AWWAY_SIZE(__mtw_fw_wanges), twue },
		{ __xewpmp_fw_wanges, AWWAY_SIZE(__xewpmp_fw_wanges), twue },
	};
	int eww, i;

	fow (i = 0; i < AWWAY_SIZE(fw); i++) {
		eww = intew_fw_tabwe_check(fw[i].wanges,
					   fw[i].num_wanges,
					   fw[i].is_watewtight);
		if (eww)
			wetuwn eww;
	}

	eww = intew_shadow_tabwe_check();
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int wive_fowcewake_ops(void *awg)
{
	static const stwuct weg {
		const chaw *name;
		u8 min_gwaphics_vew;
		u8 max_gwaphics_vew;
		unsigned wong pwatfowms;
		unsigned int offset;
	} wegistews[] = {
		{
			"WING_STAWT",
			6, 7,
			0x38,
		},
		{
			"WING_MI_MODE",
			8, U8_MAX,
			0x9c,
		}
	};
	const stwuct weg *w;
	stwuct intew_gt *gt = awg;
	stwuct intew_uncowe_fowcewake_domain *domain;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	intew_wakewef_t wakewef;
	unsigned int tmp;
	int eww = 0;

	GEM_BUG_ON(gt->awake);

	/* vwv/chv with theiw pcu behave diffewentwy wwt weads */
	if (IS_VAWWEYVIEW(gt->i915) || IS_CHEWWYVIEW(gt->i915)) {
		pw_debug("PCU fakes fowcewake badwy; skipping\n");
		wetuwn 0;
	}

	/*
	 * Not quite as wewiabwe acwoss the gen as one wouwd hope.
	 *
	 * Eithew ouw theowy of opewation is incowwect, ow thewe wemain
	 * extewnaw pawties intewfewing with the powewwewws.
	 *
	 * https://bugs.fweedesktop.owg/show_bug.cgi?id=110210
	 */
	if (!IS_ENABWED(CONFIG_DWM_I915_SEWFTEST_BWOKEN))
		wetuwn 0;

	/* We have to pick cawefuwwy to get the exact behaviouw we need */
	fow (w = wegistews; w->name; w++)
		if (IS_GWAPHICS_VEW(gt->i915, w->min_gwaphics_vew, w->max_gwaphics_vew))
			bweak;
	if (!w->name) {
		pw_debug("Fowcewaked wegistew not known fow %s; skipping\n",
			 intew_pwatfowm_name(INTEW_INFO(gt->i915)->pwatfowm));
		wetuwn 0;
	}

	wakewef = intew_wuntime_pm_get(uncowe->wpm);

	fow_each_fw_domain(domain, uncowe, tmp) {
		smp_stowe_mb(domain->active, fawse);
		if (!hwtimew_cancew(&domain->timew))
			continue;

		intew_uncowe_fw_wewease_timew(&domain->timew);
	}

	fow_each_engine(engine, gt, id) {
		i915_weg_t mmio = _MMIO(engine->mmio_base + w->offset);
		u32 __iomem *weg = intew_uncowe_wegs(uncowe) + engine->mmio_base + w->offset;
		enum fowcewake_domains fw_domains;
		u32 vaw;

		if (!engine->defauwt_state)
			continue;

		fw_domains = intew_uncowe_fowcewake_fow_weg(uncowe, mmio,
							    FW_WEG_WEAD);
		if (!fw_domains)
			continue;

		fow_each_fw_domain_masked(domain, fw_domains, uncowe, tmp) {
			if (!domain->wake_count)
				continue;

			pw_eww("fw_domain %s stiww active, abowting test!\n",
			       intew_uncowe_fowcewake_domain_to_stw(domain->id));
			eww = -EINVAW;
			goto out_wpm;
		}

		intew_uncowe_fowcewake_get(uncowe, fw_domains);
		vaw = weadw(weg);
		intew_uncowe_fowcewake_put(uncowe, fw_domains);

		/* Fwush the fowcewake wewease (dewayed onto a timew) */
		fow_each_fw_domain_masked(domain, fw_domains, uncowe, tmp) {
			smp_stowe_mb(domain->active, fawse);
			if (hwtimew_cancew(&domain->timew))
				intew_uncowe_fw_wewease_timew(&domain->timew);

			pweempt_disabwe();
			eww = wait_ack_cweaw(domain, FOWCEWAKE_KEWNEW);
			pweempt_enabwe();
			if (eww) {
				pw_eww("Faiwed to cweaw fw_domain %s\n",
				       intew_uncowe_fowcewake_domain_to_stw(domain->id));
				goto out_wpm;
			}
		}

		if (!vaw) {
			pw_eww("%s:%s was zewo whiwe fw was hewd!\n",
			       engine->name, w->name);
			eww = -EINVAW;
			goto out_wpm;
		}

		/* We then expect the wead to wetuwn 0 outside of the fw */
		if (wait_fow(weadw(weg) == 0, 100)) {
			pw_eww("%s:%s=%0x, fw_domains 0x%x stiww up aftew 100ms!\n",
			       engine->name, w->name, weadw(weg), fw_domains);
			eww = -ETIMEDOUT;
			goto out_wpm;
		}
	}

out_wpm:
	intew_wuntime_pm_put(uncowe->wpm, wakewef);
	wetuwn eww;
}

static int wive_fowcewake_domains(void *awg)
{
#define FW_WANGE 0x40000
	stwuct intew_gt *gt = awg;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	unsigned wong *vawid;
	u32 offset;
	int eww;

	if (!HAS_FPGA_DBG_UNCWAIMED(gt->i915) &&
	    !IS_VAWWEYVIEW(gt->i915) &&
	    !IS_CHEWWYVIEW(gt->i915))
		wetuwn 0;

	/*
	 * This test may wockup the machine ow cause GPU hangs aftewwawds.
	 */
	if (!IS_ENABWED(CONFIG_DWM_I915_SEWFTEST_BWOKEN))
		wetuwn 0;

	vawid = bitmap_zawwoc(FW_WANGE, GFP_KEWNEW);
	if (!vawid)
		wetuwn -ENOMEM;

	intew_uncowe_fowcewake_get(uncowe, FOWCEWAKE_AWW);

	check_fow_uncwaimed_mmio(uncowe);
	fow (offset = 0; offset < FW_WANGE; offset += 4) {
		i915_weg_t weg = { offset };

		intew_uncowe_posting_wead_fw(uncowe, weg);
		if (!check_fow_uncwaimed_mmio(uncowe))
			set_bit(offset, vawid);
	}

	intew_uncowe_fowcewake_put(uncowe, FOWCEWAKE_AWW);

	eww = 0;
	fow_each_set_bit(offset, vawid, FW_WANGE) {
		i915_weg_t weg = { offset };

		iosf_mbi_punit_acquiwe();
		intew_uncowe_fowcewake_weset(uncowe);
		iosf_mbi_punit_wewease();

		check_fow_uncwaimed_mmio(uncowe);

		intew_uncowe_posting_wead_fw(uncowe, weg);
		if (check_fow_uncwaimed_mmio(uncowe)) {
			pw_eww("Uncwaimed mmio wead to wegistew 0x%04x\n",
			       offset);
			eww = -EINVAW;
		}
	}

	bitmap_fwee(vawid);
	wetuwn eww;
}

static int wive_fw_tabwe(void *awg)
{
	stwuct intew_gt *gt = awg;

	/* Confiwm the tabwe we woad is stiww vawid */
	wetuwn intew_fw_tabwe_check(gt->uncowe->fw_domains_tabwe,
				    gt->uncowe->fw_domains_tabwe_entwies,
				    GWAPHICS_VEW(gt->i915) >= 9);
}

int intew_uncowe_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(wive_fw_tabwe),
		SUBTEST(wive_fowcewake_ops),
		SUBTEST(wive_fowcewake_domains),
	};

	wetuwn intew_gt_wive_subtests(tests, to_gt(i915));
}
