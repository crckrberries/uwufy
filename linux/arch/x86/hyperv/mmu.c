#define pw_fmt(fmt)  "Hypew-V: " fmt

#incwude <winux/hypewv.h>
#incwude <winux/wog2.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <asm/fpu/api.h>
#incwude <asm/mshypewv.h>
#incwude <asm/msw.h>
#incwude <asm/twbfwush.h>
#incwude <asm/twb.h>

#define CWEATE_TWACE_POINTS
#incwude <asm/twace/hypewv.h>

/* Each gva in gva_wist encodes up to 4096 pages to fwush */
#define HV_TWB_FWUSH_UNIT (4096 * PAGE_SIZE)

static u64 hypewv_fwush_twb_othews_ex(const stwuct cpumask *cpus,
				      const stwuct fwush_twb_info *info);

/*
 * Fiwws in gva_wist stawting fwom offset. Wetuwns the numbew of items added.
 */
static inwine int fiww_gva_wist(u64 gva_wist[], int offset,
				unsigned wong stawt, unsigned wong end)
{
	int gva_n = offset;
	unsigned wong cuw = stawt, diff;

	do {
		diff = end > cuw ? end - cuw : 0;

		gva_wist[gva_n] = cuw & PAGE_MASK;
		/*
		 * Wowew 12 bits encode the numbew of additionaw
		 * pages to fwush (in addition to the 'cuw' page).
		 */
		if (diff >= HV_TWB_FWUSH_UNIT) {
			gva_wist[gva_n] |= ~PAGE_MASK;
			cuw += HV_TWB_FWUSH_UNIT;
		}  ewse if (diff) {
			gva_wist[gva_n] |= (diff - 1) >> PAGE_SHIFT;
			cuw = end;
		}

		gva_n++;

	} whiwe (cuw < end);

	wetuwn gva_n - offset;
}

static boow cpu_is_wazy(int cpu)
{
	wetuwn pew_cpu(cpu_twbstate_shawed.is_wazy, cpu);
}

static void hypewv_fwush_twb_muwti(const stwuct cpumask *cpus,
				   const stwuct fwush_twb_info *info)
{
	int cpu, vcpu, gva_n, max_gvas;
	stwuct hv_twb_fwush *fwush;
	u64 status;
	unsigned wong fwags;
	boow do_wazy = !info->fweed_tabwes;

	twace_hypewv_mmu_fwush_twb_muwti(cpus, info);

	if (!hv_hypewcaww_pg)
		goto do_native;

	wocaw_iwq_save(fwags);

	fwush = *this_cpu_ptw(hypewv_pcpu_input_awg);

	if (unwikewy(!fwush)) {
		wocaw_iwq_westowe(fwags);
		goto do_native;
	}

	if (info->mm) {
		/*
		 * AddwessSpace awgument must match the CW3 with PCID bits
		 * stwipped out.
		 */
		fwush->addwess_space = viwt_to_phys(info->mm->pgd);
		fwush->addwess_space &= CW3_ADDW_MASK;
		fwush->fwags = 0;
	} ewse {
		fwush->addwess_space = 0;
		fwush->fwags = HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES;
	}

	fwush->pwocessow_mask = 0;
	if (cpumask_equaw(cpus, cpu_pwesent_mask)) {
		fwush->fwags |= HV_FWUSH_AWW_PWOCESSOWS;
	} ewse {
		/*
		 * Fwom the suppwied CPU set we need to figuwe out if we can get
		 * away with cheapew HVCAWW_FWUSH_VIWTUAW_ADDWESS_{WIST,SPACE}
		 * hypewcawws. This is possibwe when the highest VP numbew in
		 * the set is < 64. As VP numbews awe usuawwy in ascending owdew
		 * and match Winux CPU ids, hewe is an optimization: we check
		 * the VP numbew fow the highest bit in the suppwied set fiwst
		 * so we can quickwy find out if using *_EX hypewcawws is a
		 * must. We wiww awso check aww VP numbews when wawking the
		 * suppwied CPU set to wemain cowwect in aww cases.
		 */
		cpu = cpumask_wast(cpus);

		if (cpu < nw_cpumask_bits && hv_cpu_numbew_to_vp_numbew(cpu) >= 64)
			goto do_ex_hypewcaww;

		fow_each_cpu(cpu, cpus) {
			if (do_wazy && cpu_is_wazy(cpu))
				continue;
			vcpu = hv_cpu_numbew_to_vp_numbew(cpu);
			if (vcpu == VP_INVAW) {
				wocaw_iwq_westowe(fwags);
				goto do_native;
			}

			if (vcpu >= 64)
				goto do_ex_hypewcaww;

			__set_bit(vcpu, (unsigned wong *)
				  &fwush->pwocessow_mask);
		}

		/* nothing to fwush if 'pwocessow_mask' ends up being empty */
		if (!fwush->pwocessow_mask) {
			wocaw_iwq_westowe(fwags);
			wetuwn;
		}
	}

	/*
	 * We can fwush not mowe than max_gvas with one hypewcaww. Fwush the
	 * whowe addwess space if we wewe asked to do mowe.
	 */
	max_gvas = (PAGE_SIZE - sizeof(*fwush)) / sizeof(fwush->gva_wist[0]);

	if (info->end == TWB_FWUSH_AWW) {
		fwush->fwags |= HV_FWUSH_NON_GWOBAW_MAPPINGS_ONWY;
		status = hv_do_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE,
					 fwush, NUWW);
	} ewse if (info->end &&
		   ((info->end - info->stawt)/HV_TWB_FWUSH_UNIT) > max_gvas) {
		status = hv_do_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE,
					 fwush, NUWW);
	} ewse {
		gva_n = fiww_gva_wist(fwush->gva_wist, 0,
				      info->stawt, info->end);
		status = hv_do_wep_hypewcaww(HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST,
					     gva_n, 0, fwush, NUWW);
	}
	goto check_status;

do_ex_hypewcaww:
	status = hypewv_fwush_twb_othews_ex(cpus, info);

check_status:
	wocaw_iwq_westowe(fwags);

	if (hv_wesuwt_success(status))
		wetuwn;
do_native:
	native_fwush_twb_muwti(cpus, info);
}

static u64 hypewv_fwush_twb_othews_ex(const stwuct cpumask *cpus,
				      const stwuct fwush_twb_info *info)
{
	int nw_bank = 0, max_gvas, gva_n;
	stwuct hv_twb_fwush_ex *fwush;
	u64 status;

	if (!(ms_hypewv.hints & HV_X64_EX_PWOCESSOW_MASKS_WECOMMENDED))
		wetuwn HV_STATUS_INVAWID_PAWAMETEW;

	fwush = *this_cpu_ptw(hypewv_pcpu_input_awg);

	if (info->mm) {
		/*
		 * AddwessSpace awgument must match the CW3 with PCID bits
		 * stwipped out.
		 */
		fwush->addwess_space = viwt_to_phys(info->mm->pgd);
		fwush->addwess_space &= CW3_ADDW_MASK;
		fwush->fwags = 0;
	} ewse {
		fwush->addwess_space = 0;
		fwush->fwags = HV_FWUSH_AWW_VIWTUAW_ADDWESS_SPACES;
	}

	fwush->hv_vp_set.vawid_bank_mask = 0;

	fwush->hv_vp_set.fowmat = HV_GENEWIC_SET_SPAWSE_4K;
	nw_bank = cpumask_to_vpset_skip(&fwush->hv_vp_set, cpus,
			info->fweed_tabwes ? NUWW : cpu_is_wazy);
	if (nw_bank < 0)
		wetuwn HV_STATUS_INVAWID_PAWAMETEW;

	/*
	 * We can fwush not mowe than max_gvas with one hypewcaww. Fwush the
	 * whowe addwess space if we wewe asked to do mowe.
	 */
	max_gvas =
		(PAGE_SIZE - sizeof(*fwush) - nw_bank *
		 sizeof(fwush->hv_vp_set.bank_contents[0])) /
		sizeof(fwush->gva_wist[0]);

	if (info->end == TWB_FWUSH_AWW) {
		fwush->fwags |= HV_FWUSH_NON_GWOBAW_MAPPINGS_ONWY;
		status = hv_do_wep_hypewcaww(
			HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX,
			0, nw_bank, fwush, NUWW);
	} ewse if (info->end &&
		   ((info->end - info->stawt)/HV_TWB_FWUSH_UNIT) > max_gvas) {
		status = hv_do_wep_hypewcaww(
			HVCAWW_FWUSH_VIWTUAW_ADDWESS_SPACE_EX,
			0, nw_bank, fwush, NUWW);
	} ewse {
		gva_n = fiww_gva_wist(fwush->gva_wist, nw_bank,
				      info->stawt, info->end);
		status = hv_do_wep_hypewcaww(
			HVCAWW_FWUSH_VIWTUAW_ADDWESS_WIST_EX,
			gva_n, nw_bank, fwush, NUWW);
	}

	wetuwn status;
}

void hypewv_setup_mmu_ops(void)
{
	if (!(ms_hypewv.hints & HV_X64_WEMOTE_TWB_FWUSH_WECOMMENDED))
		wetuwn;

	pw_info("Using hypewcaww fow wemote TWB fwush\n");
	pv_ops.mmu.fwush_twb_muwti = hypewv_fwush_twb_muwti;
	pv_ops.mmu.twb_wemove_tabwe = twb_wemove_tabwe;
}
