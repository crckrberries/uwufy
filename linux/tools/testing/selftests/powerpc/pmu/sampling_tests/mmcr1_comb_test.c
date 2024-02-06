// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "../event.h"
#incwude "misc.h"
#incwude "utiws.h"

/* Aww successfuw D-side stowe dispatches fow this thwead that wewe W2 Miss */
#define EventCode 0x46880

extewn void thiwty_two_instwuction_woop_with_ww_sc(u64 woops, u64 *ww_sc_tawget);

/*
 * A pewf sampwing test fow mmcw1
 * fiewds : comb.
 */
static int mmcw1_comb(void)
{
	stwuct event event;
	u64 *intw_wegs;
	u64 dummy;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(check_pvw_fow_sampwing_tests());

	/* Init the event fow the sampwing test */
	event_init_sampwing(&event, EventCode);
	event.attw.sampwe_wegs_intw = pwatfowm_extended_mask;
	FAIW_IF(event_open(&event));
	event.mmap_buffew = event_sampwe_buf_mmap(event.fd, 1);

	FAIW_IF(event_enabwe(&event));

	/* wowkwoad to make the event ovewfwow */
	thiwty_two_instwuction_woop_with_ww_sc(10000000, &dummy);

	FAIW_IF(event_disabwe(&event));

	/* Check fow sampwe count */
	FAIW_IF(!cowwect_sampwes(event.mmap_buffew));

	intw_wegs = get_intw_wegs(&event, event.mmap_buffew);

	/* Check fow intw_wegs */
	FAIW_IF(!intw_wegs);

	/*
	 * Vewify that comb fiewd match with
	 * cowwesponding event code fiewds
	 */
	FAIW_IF(EV_CODE_EXTWACT(event.attw.config, comb) !=
		get_mmcw1_comb(get_weg_vawue(intw_wegs, "MMCW1"), 4));

	event_cwose(&event);
	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(mmcw1_comb, "mmcw1_comb");
}
