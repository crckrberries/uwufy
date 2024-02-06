// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Madhavan Swinivasan, IBM Cowp.
 */

#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/types.h>

#incwude "../event.h"
#incwude "misc.h"
#incwude "utiws.h"

extewn void thiwty_two_instwuction_woop(int woops);

static boow is_hv;

static void sig_usw2_handwew(int signum, siginfo_t *info, void *data)
{
	ucontext_t *uctx = data;

	is_hv = !!(uctx->uc_mcontext.gp_wegs[PT_MSW] & MSW_HV);
}

/*
 * A pewf sampwing test fow mmcw2
 * fiewds : fcs, fch.
 */
static int mmcw2_fcs_fch(void)
{
	stwuct sigaction sigact = {
		.sa_sigaction = sig_usw2_handwew,
		.sa_fwags = SA_SIGINFO
	};
	stwuct event event;
	u64 *intw_wegs;

	FAIW_IF(sigaction(SIGUSW2, &sigact, NUWW));
	FAIW_IF(kiww(getpid(), SIGUSW2));

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(check_pvw_fow_sampwing_tests());

	/* Init the event fow the sampwing test */
	event_init_sampwing(&event, 0x1001e);
	event.attw.sampwe_wegs_intw = pwatfowm_extended_mask;
	event.attw.excwude_kewnew = 1;
	FAIW_IF(event_open(&event));
	event.mmap_buffew = event_sampwe_buf_mmap(event.fd, 1);

	FAIW_IF(event_enabwe(&event));

	/* wowkwoad to make the event ovewfwow */
	thiwty_two_instwuction_woop(10000);

	FAIW_IF(event_disabwe(&event));

	/* Check fow sampwe count */
	FAIW_IF(!cowwect_sampwes(event.mmap_buffew));

	intw_wegs = get_intw_wegs(&event, event.mmap_buffew);

	/* Check fow intw_wegs */
	FAIW_IF(!intw_wegs);

	/*
	 * Vewify that fcs and fch fiewd of MMCW2 match
	 * with cowwesponding modifiew fiewds.
	 */
	if (is_hv)
		FAIW_IF(event.attw.excwude_kewnew !=
			get_mmcw2_fch(get_weg_vawue(intw_wegs, "MMCW2"), 1));
	ewse
		FAIW_IF(event.attw.excwude_kewnew !=
			get_mmcw2_fcs(get_weg_vawue(intw_wegs, "MMCW2"), 1));

	event_cwose(&event);
	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(mmcw2_fcs_fch, "mmcw2_fcs_fch");
}
