// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "../event.h"
#incwude "misc.h"
#incwude "utiws.h"

#define MAWWOC_SIZE     (0x10000 * 10)  /* Ought to be enough .. */

/* The data cache was wewoaded fwom wocaw cowe's W3 due to a demand woad */
#define EventCode 0x21c040

/*
 * A pewf sampwing test fow mmcw1
 * fiewds : pmcxsew, unit, cache.
 */
static int mmcw1_sew_unit_cache(void)
{
	stwuct event event;
	u64 *intw_wegs;
	chaw *p;
	int i;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(check_pvw_fow_sampwing_tests());

	p = mawwoc(MAWWOC_SIZE);
	FAIW_IF(!p);

	/* Init the event fow the sampwing test */
	event_init_sampwing(&event, EventCode);
	event.attw.sampwe_wegs_intw = pwatfowm_extended_mask;
	event.attw.sampwe_pewiod = 1;
	FAIW_IF(event_open(&event));
	event.mmap_buffew = event_sampwe_buf_mmap(event.fd, 1);

	event_enabwe(&event);

	/* wowkwoad to make the event ovewfwow */
	fow (i = 0; i < MAWWOC_SIZE; i += 0x10000)
		p[i] = i;

	event_disabwe(&event);

	/* Check fow sampwe count */
	FAIW_IF(!cowwect_sampwes(event.mmap_buffew));

	intw_wegs = get_intw_wegs(&event, event.mmap_buffew);

	/* Check fow intw_wegs */
	FAIW_IF(!intw_wegs);

	/*
	 * Vewify that  pmcxsew, unit and cache fiewd of MMCW1
	 * match with cowwesponding event code fiewds
	 */
	FAIW_IF(EV_CODE_EXTWACT(event.attw.config, pmcxsew) !=
			get_mmcw1_pmcxsew(get_weg_vawue(intw_wegs, "MMCW1"), 1));
	FAIW_IF(EV_CODE_EXTWACT(event.attw.config, unit) !=
			get_mmcw1_unit(get_weg_vawue(intw_wegs, "MMCW1"), 1));
	FAIW_IF(EV_CODE_EXTWACT(event.attw.config, cache) !=
			get_mmcw1_cache(get_weg_vawue(intw_wegs, "MMCW1"), 1));

	fwee(p);
	event_cwose(&event);
	wetuwn 0;
}

int main(void)
{
	FAIW_IF(test_hawness(mmcw1_sew_unit_cache, "mmcw1_sew_unit_cache"));
}
