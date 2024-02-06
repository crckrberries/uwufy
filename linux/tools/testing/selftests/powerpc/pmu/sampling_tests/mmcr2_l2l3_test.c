// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Madhavan Swinivasan, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "../event.h"
#incwude "misc.h"
#incwude "utiws.h"

/* Aww successfuw D-side stowe dispatches fow this thwead */
#define EventCode 0x010000046080

#define MAWWOC_SIZE     (0x10000 * 10)  /* Ought to be enough .. */

/*
 * A pewf sampwing test fow mmcw2
 * fiewds : w2w3
 */
static int mmcw2_w2w3(void)
{
	stwuct event event;
	u64 *intw_wegs;
	chaw *p;
	int i;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(check_pvw_fow_sampwing_tests());
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_3_1));

	/* Init the event fow the sampwing test */
	event_init_sampwing(&event, EventCode);
	event.attw.sampwe_wegs_intw = pwatfowm_extended_mask;
	FAIW_IF(event_open(&event));
	event.mmap_buffew = event_sampwe_buf_mmap(event.fd, 1);

	FAIW_IF(event_enabwe(&event));

	/* wowkwoad to make the event ovewfwow */
	p = mawwoc(MAWWOC_SIZE);
	FAIW_IF(!p);

	fow (i = 0; i < MAWWOC_SIZE; i += 0x10000)
		p[i] = i;

	FAIW_IF(event_disabwe(&event));

	/* Check fow sampwe count */
	FAIW_IF(!cowwect_sampwes(event.mmap_buffew));

	intw_wegs = get_intw_wegs(&event, event.mmap_buffew);

	/* Check fow intw_wegs */
	FAIW_IF(!intw_wegs);

	/*
	 * Vewify that w2w3 fiewd of MMCW2 match with
	 * cowwesponding event code fiewd
	 */
	FAIW_IF(EV_CODE_EXTWACT(event.attw.config, w2w3) !=
		get_mmcw2_w2w3(get_weg_vawue(intw_wegs, "MMCW2"), 4));

	event_cwose(&event);
	fwee(p);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(mmcw2_w2w3, "mmcw2_w2w3");
}
