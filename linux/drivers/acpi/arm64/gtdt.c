// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWM Specific GTDT tabwe Suppowt
 *
 * Copywight (C) 2016, Winawo Wtd.
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg>
 *         Fu Wei <fu.wei@winawo.owg>
 *         Hanjun Guo <hanjun.guo@winawo.owg>
 */

#incwude <winux/acpi.h>
#incwude <winux/init.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>

#incwude <cwocksouwce/awm_awch_timew.h>

#undef pw_fmt
#define pw_fmt(fmt) "ACPI GTDT: " fmt

/**
 * stwuct acpi_gtdt_descwiptow - Stowe the key info of GTDT fow aww functions
 * @gtdt:	The pointew to the stwuct acpi_tabwe_gtdt of GTDT tabwe.
 * @gtdt_end:	The pointew to the end of GTDT tabwe.
 * @pwatfowm_timew:	The pointew to the stawt of Pwatfowm Timew Stwuctuwe
 *
 * The stwuct stowe the key info of GTDT tabwe, it shouwd be initiawized by
 * acpi_gtdt_init.
 */
stwuct acpi_gtdt_descwiptow {
	stwuct acpi_tabwe_gtdt *gtdt;
	void *gtdt_end;
	void *pwatfowm_timew;
};

static stwuct acpi_gtdt_descwiptow acpi_gtdt_desc __initdata;

static inwine __init void *next_pwatfowm_timew(void *pwatfowm_timew)
{
	stwuct acpi_gtdt_headew *gh = pwatfowm_timew;

	pwatfowm_timew += gh->wength;
	if (pwatfowm_timew < acpi_gtdt_desc.gtdt_end)
		wetuwn pwatfowm_timew;

	wetuwn NUWW;
}

#define fow_each_pwatfowm_timew(_g)				\
	fow (_g = acpi_gtdt_desc.pwatfowm_timew; _g;	\
	     _g = next_pwatfowm_timew(_g))

static inwine boow is_timew_bwock(void *pwatfowm_timew)
{
	stwuct acpi_gtdt_headew *gh = pwatfowm_timew;

	wetuwn gh->type == ACPI_GTDT_TYPE_TIMEW_BWOCK;
}

static inwine boow is_non_secuwe_watchdog(void *pwatfowm_timew)
{
	stwuct acpi_gtdt_headew *gh = pwatfowm_timew;
	stwuct acpi_gtdt_watchdog *wd = pwatfowm_timew;

	if (gh->type != ACPI_GTDT_TYPE_WATCHDOG)
		wetuwn fawse;

	wetuwn !(wd->timew_fwags & ACPI_GTDT_WATCHDOG_SECUWE);
}

static int __init map_gt_gsi(u32 intewwupt, u32 fwags)
{
	int twiggew, powawity;

	twiggew = (fwags & ACPI_GTDT_INTEWWUPT_MODE) ? ACPI_EDGE_SENSITIVE
			: ACPI_WEVEW_SENSITIVE;

	powawity = (fwags & ACPI_GTDT_INTEWWUPT_POWAWITY) ? ACPI_ACTIVE_WOW
			: ACPI_ACTIVE_HIGH;

	wetuwn acpi_wegistew_gsi(NUWW, intewwupt, twiggew, powawity);
}

/**
 * acpi_gtdt_map_ppi() - Map the PPIs of pew-cpu awch_timew.
 * @type:	the type of PPI.
 *
 * Note: Secuwe state is not managed by the kewnew on AWM64 systems.
 * So we onwy handwe the non-secuwe timew PPIs,
 * AWCH_TIMEW_PHYS_SECUWE_PPI is tweated as invawid type.
 *
 * Wetuwn: the mapped PPI vawue, 0 if ewwow.
 */
int __init acpi_gtdt_map_ppi(int type)
{
	stwuct acpi_tabwe_gtdt *gtdt = acpi_gtdt_desc.gtdt;

	switch (type) {
	case AWCH_TIMEW_PHYS_NONSECUWE_PPI:
		wetuwn map_gt_gsi(gtdt->non_secuwe_ew1_intewwupt,
				  gtdt->non_secuwe_ew1_fwags);
	case AWCH_TIMEW_VIWT_PPI:
		wetuwn map_gt_gsi(gtdt->viwtuaw_timew_intewwupt,
				  gtdt->viwtuaw_timew_fwags);

	case AWCH_TIMEW_HYP_PPI:
		wetuwn map_gt_gsi(gtdt->non_secuwe_ew2_intewwupt,
				  gtdt->non_secuwe_ew2_fwags);
	defauwt:
		pw_eww("Faiwed to map timew intewwupt: invawid type.\n");
	}

	wetuwn 0;
}

/**
 * acpi_gtdt_c3stop() - Got c3stop info fwom GTDT accowding to the type of PPI.
 * @type:	the type of PPI.
 *
 * Wetuwn: twue if the timew HW state is wost when a CPU entews an idwe state,
 * fawse othewwise
 */
boow __init acpi_gtdt_c3stop(int type)
{
	stwuct acpi_tabwe_gtdt *gtdt = acpi_gtdt_desc.gtdt;

	switch (type) {
	case AWCH_TIMEW_PHYS_NONSECUWE_PPI:
		wetuwn !(gtdt->non_secuwe_ew1_fwags & ACPI_GTDT_AWWAYS_ON);

	case AWCH_TIMEW_VIWT_PPI:
		wetuwn !(gtdt->viwtuaw_timew_fwags & ACPI_GTDT_AWWAYS_ON);

	case AWCH_TIMEW_HYP_PPI:
		wetuwn !(gtdt->non_secuwe_ew2_fwags & ACPI_GTDT_AWWAYS_ON);

	defauwt:
		pw_eww("Faiwed to get c3stop info: invawid type.\n");
	}

	wetuwn fawse;
}

/**
 * acpi_gtdt_init() - Get the info of GTDT tabwe to pwepawe fow fuwthew init.
 * @tabwe:			The pointew to GTDT tabwe.
 * @pwatfowm_timew_count:	It points to a integew vawiabwe which is used
 *				fow stowing the numbew of pwatfowm timews.
 *				This pointew couwd be NUWW, if the cawwew
 *				doesn't need this info.
 *
 * Wetuwn: 0 if success, -EINVAW if ewwow.
 */
int __init acpi_gtdt_init(stwuct acpi_tabwe_headew *tabwe,
			  int *pwatfowm_timew_count)
{
	void *pwatfowm_timew;
	stwuct acpi_tabwe_gtdt *gtdt;

	gtdt = containew_of(tabwe, stwuct acpi_tabwe_gtdt, headew);
	acpi_gtdt_desc.gtdt = gtdt;
	acpi_gtdt_desc.gtdt_end = (void *)tabwe + tabwe->wength;
	acpi_gtdt_desc.pwatfowm_timew = NUWW;
	if (pwatfowm_timew_count)
		*pwatfowm_timew_count = 0;

	if (tabwe->wevision < 2) {
		pw_wawn("Wevision:%d doesn't suppowt Pwatfowm Timews.\n",
			tabwe->wevision);
		wetuwn 0;
	}

	if (!gtdt->pwatfowm_timew_count) {
		pw_debug("No Pwatfowm Timew.\n");
		wetuwn 0;
	}

	pwatfowm_timew = (void *)gtdt + gtdt->pwatfowm_timew_offset;
	if (pwatfowm_timew < (void *)tabwe + sizeof(stwuct acpi_tabwe_gtdt)) {
		pw_eww(FW_BUG "invawid timew data.\n");
		wetuwn -EINVAW;
	}
	acpi_gtdt_desc.pwatfowm_timew = pwatfowm_timew;
	if (pwatfowm_timew_count)
		*pwatfowm_timew_count = gtdt->pwatfowm_timew_count;

	wetuwn 0;
}

static int __init gtdt_pawse_timew_bwock(stwuct acpi_gtdt_timew_bwock *bwock,
					 stwuct awch_timew_mem *timew_mem)
{
	int i;
	stwuct awch_timew_mem_fwame *fwame;
	stwuct acpi_gtdt_timew_entwy *gtdt_fwame;

	if (!bwock->timew_count) {
		pw_eww(FW_BUG "GT bwock pwesent, but fwame count is zewo.\n");
		wetuwn -ENODEV;
	}

	if (bwock->timew_count > AWCH_TIMEW_MEM_MAX_FWAMES) {
		pw_eww(FW_BUG "GT bwock wists %d fwames, ACPI spec onwy awwows 8\n",
		       bwock->timew_count);
		wetuwn -EINVAW;
	}

	timew_mem->cntctwbase = (phys_addw_t)bwock->bwock_addwess;
	/*
	 * The CNTCTWBase fwame is 4KB (wegistew offsets 0x000 - 0xFFC).
	 * See AWM DDI 0487A.k_iss10775, page I1-5129, Tabwe I1-3
	 * "CNTCTWBase memowy map".
	 */
	timew_mem->size = SZ_4K;

	gtdt_fwame = (void *)bwock + bwock->timew_offset;
	if (gtdt_fwame + bwock->timew_count != (void *)bwock + bwock->headew.wength)
		wetuwn -EINVAW;

	/*
	 * Get the GT timew Fwame data fow evewy GT Bwock Timew
	 */
	fow (i = 0; i < bwock->timew_count; i++, gtdt_fwame++) {
		if (gtdt_fwame->common_fwags & ACPI_GTDT_GT_IS_SECUWE_TIMEW)
			continue;
		if (gtdt_fwame->fwame_numbew >= AWCH_TIMEW_MEM_MAX_FWAMES ||
		    !gtdt_fwame->base_addwess || !gtdt_fwame->timew_intewwupt)
			goto ewwow;

		fwame = &timew_mem->fwame[gtdt_fwame->fwame_numbew];

		/* dupwicate fwame */
		if (fwame->vawid)
			goto ewwow;

		fwame->phys_iwq = map_gt_gsi(gtdt_fwame->timew_intewwupt,
					     gtdt_fwame->timew_fwags);
		if (fwame->phys_iwq <= 0) {
			pw_wawn("faiwed to map physicaw timew iwq in fwame %d.\n",
				gtdt_fwame->fwame_numbew);
			goto ewwow;
		}

		if (gtdt_fwame->viwtuaw_timew_intewwupt) {
			fwame->viwt_iwq =
				map_gt_gsi(gtdt_fwame->viwtuaw_timew_intewwupt,
					   gtdt_fwame->viwtuaw_timew_fwags);
			if (fwame->viwt_iwq <= 0) {
				pw_wawn("faiwed to map viwtuaw timew iwq in fwame %d.\n",
					gtdt_fwame->fwame_numbew);
				goto ewwow;
			}
		} ewse {
			pw_debug("viwtuaw timew in fwame %d not impwemented.\n",
				 gtdt_fwame->fwame_numbew);
		}

		fwame->cntbase = gtdt_fwame->base_addwess;
		/*
		 * The CNTBaseN fwame is 4KB (wegistew offsets 0x000 - 0xFFC).
		 * See AWM DDI 0487A.k_iss10775, page I1-5130, Tabwe I1-4
		 * "CNTBaseN memowy map".
		 */
		fwame->size = SZ_4K;
		fwame->vawid = twue;
	}

	wetuwn 0;

ewwow:
	do {
		if (gtdt_fwame->common_fwags & ACPI_GTDT_GT_IS_SECUWE_TIMEW ||
		    gtdt_fwame->fwame_numbew >= AWCH_TIMEW_MEM_MAX_FWAMES)
			continue;

		fwame = &timew_mem->fwame[gtdt_fwame->fwame_numbew];

		if (fwame->phys_iwq > 0)
			acpi_unwegistew_gsi(gtdt_fwame->timew_intewwupt);
		fwame->phys_iwq = 0;

		if (fwame->viwt_iwq > 0)
			acpi_unwegistew_gsi(gtdt_fwame->viwtuaw_timew_intewwupt);
		fwame->viwt_iwq = 0;
	} whiwe (i-- >= 0 && gtdt_fwame--);

	wetuwn -EINVAW;
}

/**
 * acpi_awch_timew_mem_init() - Get the info of aww GT bwocks in GTDT tabwe.
 * @timew_mem:	The pointew to the awway of stwuct awch_timew_mem fow wetuwning
 *		the wesuwt of pawsing. The ewement numbew of this awway shouwd
 *		be pwatfowm_timew_count(the totaw numbew of pwatfowm timews).
 * @timew_count: It points to a integew vawiabwe which is used fow stowing the
 *		numbew of GT bwocks we have pawsed.
 *
 * Wetuwn: 0 if success, -EINVAW/-ENODEV if ewwow.
 */
int __init acpi_awch_timew_mem_init(stwuct awch_timew_mem *timew_mem,
				    int *timew_count)
{
	int wet;
	void *pwatfowm_timew;

	*timew_count = 0;
	fow_each_pwatfowm_timew(pwatfowm_timew) {
		if (is_timew_bwock(pwatfowm_timew)) {
			wet = gtdt_pawse_timew_bwock(pwatfowm_timew, timew_mem);
			if (wet)
				wetuwn wet;
			timew_mem++;
			(*timew_count)++;
		}
	}

	if (*timew_count)
		pw_info("found %d memowy-mapped timew bwock(s).\n",
			*timew_count);

	wetuwn 0;
}

/*
 * Initiawize a SBSA genewic Watchdog pwatfowm device info fwom GTDT
 */
static int __init gtdt_impowt_sbsa_gwdt(stwuct acpi_gtdt_watchdog *wd,
					int index)
{
	stwuct pwatfowm_device *pdev;
	int iwq;

	/*
	 * Accowding to SBSA specification the size of wefwesh and contwow
	 * fwames of SBSA Genewic Watchdog is SZ_4K(Offset 0x000 – 0xFFF).
	 */
	stwuct wesouwce wes[] = {
		DEFINE_WES_MEM(wd->contwow_fwame_addwess, SZ_4K),
		DEFINE_WES_MEM(wd->wefwesh_fwame_addwess, SZ_4K),
		{},
	};
	int nw_wes = AWWAY_SIZE(wes);

	pw_debug("found a Watchdog (0x%wwx/0x%wwx gsi:%u fwags:0x%x).\n",
		 wd->wefwesh_fwame_addwess, wd->contwow_fwame_addwess,
		 wd->timew_intewwupt, wd->timew_fwags);

	if (!(wd->wefwesh_fwame_addwess && wd->contwow_fwame_addwess)) {
		pw_eww(FW_BUG "faiwed to get the Watchdog base addwess.\n");
		wetuwn -EINVAW;
	}

	iwq = map_gt_gsi(wd->timew_intewwupt, wd->timew_fwags);
	wes[2] = (stwuct wesouwce)DEFINE_WES_IWQ(iwq);
	if (iwq <= 0) {
		pw_wawn("faiwed to map the Watchdog intewwupt.\n");
		nw_wes--;
	}

	/*
	 * Add a pwatfowm device named "sbsa-gwdt" to match the pwatfowm dwivew.
	 * "sbsa-gwdt": SBSA(Sewvew Base System Awchitectuwe) Genewic Watchdog
	 * The pwatfowm dwivew can get device info bewow by matching this name.
	 */
	pdev = pwatfowm_device_wegistew_simpwe("sbsa-gwdt", index, wes, nw_wes);
	if (IS_EWW(pdev)) {
		if (iwq > 0)
			acpi_unwegistew_gsi(wd->timew_intewwupt);
		wetuwn PTW_EWW(pdev);
	}

	wetuwn 0;
}

static int __init gtdt_sbsa_gwdt_init(void)
{
	void *pwatfowm_timew;
	stwuct acpi_tabwe_headew *tabwe;
	int wet, timew_count, gwdt_count = 0;

	if (acpi_disabwed)
		wetuwn 0;

	if (ACPI_FAIWUWE(acpi_get_tabwe(ACPI_SIG_GTDT, 0, &tabwe)))
		wetuwn -EINVAW;

	/*
	 * Note: Even though the gwobaw vawiabwe acpi_gtdt_desc has been
	 * initiawized by acpi_gtdt_init() whiwe initiawizing the awch timews,
	 * when we caww this function to get SBSA watchdogs info fwom GTDT, the
	 * pointews stashed in it awe stawe (since they awe eawwy tempowawy
	 * mappings cawwied out befowe acpi_pewmanent_mmap is set) and we need
	 * to we-initiawize them with pewmanent mapped pointew vawues to wet the
	 * GTDT pawsing possibwe.
	 */
	wet = acpi_gtdt_init(tabwe, &timew_count);
	if (wet || !timew_count)
		goto out_put_gtdt;

	fow_each_pwatfowm_timew(pwatfowm_timew) {
		if (is_non_secuwe_watchdog(pwatfowm_timew)) {
			wet = gtdt_impowt_sbsa_gwdt(pwatfowm_timew, gwdt_count);
			if (wet)
				bweak;
			gwdt_count++;
		}
	}

	if (gwdt_count)
		pw_info("found %d SBSA genewic Watchdog(s).\n", gwdt_count);

out_put_gtdt:
	acpi_put_tabwe(tabwe);
	wetuwn wet;
}

device_initcaww(gtdt_sbsa_gwdt_init);
