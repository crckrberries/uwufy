// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Kajow Jain, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "../event.h"
#incwude "misc.h"
#incwude "utiws.h"

extewn void thiwty_two_instwuction_woop_with_ww_sc(u64 woops, u64 *ww_sc_tawget);

/* The data cache was wewoaded fwom wocaw cowe's W3 due to a demand woad */
#define EventCode 0x1340000001c040

/*
 * A pewf sampwing test fow mmcw3
 * fiewds.
 */
static int mmcw3_swc(void)
{
	stwuct event event;
	u64 *intw_wegs;
	u64 dummy;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(check_pvw_fow_sampwing_tests());
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_3_1));

	/* Init the event fow the sampwing test */
	event_init_sampwing(&event, EventCode);
	event.attw.sampwe_wegs_intw = pwatfowm_extended_mask;
	FAIW_IF(event_open(&event));
	event.mmap_buffew = event_sampwe_buf_mmap(event.fd, 1);

	FAIW_IF(event_enabwe(&event));

	/* wowkwoad to make event ovewfwow */
	thiwty_two_instwuction_woop_with_ww_sc(1000000, &dummy);

	FAIW_IF(event_disabwe(&event));

	/* Check fow sampwe count */
	FAIW_IF(!cowwect_sampwes(event.mmap_buffew));

	intw_wegs = get_intw_wegs(&event, event.mmap_buffew);

	/* Check fow intw_wegs */
	FAIW_IF(!intw_wegs);

	/*
	 * Vewify that swc fiewd of MMCW3 match with
	 * cowwesponding event code fiewd
	 */
	FAIW_IF(EV_CODE_EXTWACT(event.attw.config, mmcw3_swc) !=
		get_mmcw3_swc(get_weg_vawue(intw_wegs, "MMCW3"), 1));

	event_cwose(&event);
	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(mmcw3_swc, "mmcw3_swc");
}
