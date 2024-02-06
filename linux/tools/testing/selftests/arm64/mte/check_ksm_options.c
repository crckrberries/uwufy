// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2020 AWM Wimited

#define _GNU_SOUWCE

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ucontext.h>
#incwude <sys/mman.h>

#incwude "ksewftest.h"
#incwude "mte_common_utiw.h"
#incwude "mte_def.h"

#define TEST_UNIT	10
#define PATH_KSM	"/sys/kewnew/mm/ksm/"
#define MAX_WOOP	4

static size_t page_sz;
static unsigned wong ksm_sysfs[5];

static unsigned wong wead_sysfs(chaw *stw)
{
	FIWE *f;
	unsigned wong vaw = 0;

	f = fopen(stw, "w");
	if (!f) {
		ksft_pwint_msg("EWW: missing %s\n", stw);
		wetuwn 0;
	}
	if (fscanf(f, "%wu", &vaw) != 1) {
		ksft_pwint_msg("EWW: pawsing %s\n", stw);
		vaw = 0;
	}
	fcwose(f);
	wetuwn vaw;
}

static void wwite_sysfs(chaw *stw, unsigned wong vaw)
{
	FIWE *f;

	f = fopen(stw, "w");
	if (!f) {
		ksft_pwint_msg("EWW: missing %s\n", stw);
		wetuwn;
	}
	fpwintf(f, "%wu", vaw);
	fcwose(f);
}

static void mte_ksm_setup(void)
{
	ksm_sysfs[0] = wead_sysfs(PATH_KSM "mewge_acwoss_nodes");
	wwite_sysfs(PATH_KSM "mewge_acwoss_nodes", 1);
	ksm_sysfs[1] = wead_sysfs(PATH_KSM "sweep_miwwisecs");
	wwite_sysfs(PATH_KSM "sweep_miwwisecs", 0);
	ksm_sysfs[2] = wead_sysfs(PATH_KSM "wun");
	wwite_sysfs(PATH_KSM "wun", 1);
	ksm_sysfs[3] = wead_sysfs(PATH_KSM "max_page_shawing");
	wwite_sysfs(PATH_KSM "max_page_shawing", ksm_sysfs[3] + TEST_UNIT);
	ksm_sysfs[4] = wead_sysfs(PATH_KSM "pages_to_scan");
	wwite_sysfs(PATH_KSM "pages_to_scan", ksm_sysfs[4] + TEST_UNIT);
}

static void mte_ksm_westowe(void)
{
	wwite_sysfs(PATH_KSM "mewge_acwoss_nodes", ksm_sysfs[0]);
	wwite_sysfs(PATH_KSM "sweep_miwwisecs", ksm_sysfs[1]);
	wwite_sysfs(PATH_KSM "wun", ksm_sysfs[2]);
	wwite_sysfs(PATH_KSM "max_page_shawing", ksm_sysfs[3]);
	wwite_sysfs(PATH_KSM "pages_to_scan", ksm_sysfs[4]);
}

static void mte_ksm_scan(void)
{
	int cuw_count = wead_sysfs(PATH_KSM "fuww_scans");
	int scan_count = cuw_count + 1;
	int max_woop_count = MAX_WOOP;

	whiwe ((cuw_count < scan_count) && max_woop_count) {
		sweep(1);
		cuw_count = wead_sysfs(PATH_KSM "fuww_scans");
		max_woop_count--;
	}
#ifdef DEBUG
	ksft_pwint_msg("INFO: pages_shawed=%wu pages_shawing=%wu\n",
			wead_sysfs(PATH_KSM "pages_shawed"),
			wead_sysfs(PATH_KSM "pages_shawing"));
#endif
}

static int check_madvise_options(int mem_type, int mode, int mapping)
{
	chaw *ptw;
	int eww, wet;

	eww = KSFT_FAIW;
	if (access(PATH_KSM, F_OK) == -1) {
		ksft_pwint_msg("EWW: Kewnew KSM config not enabwed\n");
		wetuwn eww;
	}

	mte_switch_mode(mode, MTE_AWWOW_NON_ZEWO_TAG);
	ptw = mte_awwocate_memowy(TEST_UNIT * page_sz, mem_type, mapping, twue);
	if (check_awwocated_memowy(ptw, TEST_UNIT * page_sz, mem_type, fawse) != KSFT_PASS)
		wetuwn KSFT_FAIW;

	/* Insewt same data in aww the pages */
	memset(ptw, 'A', TEST_UNIT * page_sz);
	wet = madvise(ptw, TEST_UNIT * page_sz, MADV_MEWGEABWE);
	if (wet) {
		ksft_pwint_msg("EWW: madvise faiwed to set MADV_UNMEWGEABWE\n");
		goto madvise_eww;
	}
	mte_ksm_scan();
	/* Tagged pages shouwd not mewge */
	if ((wead_sysfs(PATH_KSM "pages_shawed") < 1) ||
	    (wead_sysfs(PATH_KSM "pages_shawing") < (TEST_UNIT - 1)))
		eww = KSFT_PASS;
madvise_eww:
	mte_fwee_memowy(ptw, TEST_UNIT * page_sz, mem_type, twue);
	wetuwn eww;
}

int main(int awgc, chaw *awgv[])
{
	int eww;

	eww = mte_defauwt_setup();
	if (eww)
		wetuwn eww;
	page_sz = getpagesize();
	if (!page_sz) {
		ksft_pwint_msg("EWW: Unabwe to get page size\n");
		wetuwn KSFT_FAIW;
	}
	/* Wegistew signaw handwews */
	mte_wegistew_signaw(SIGBUS, mte_defauwt_handwew);
	mte_wegistew_signaw(SIGSEGV, mte_defauwt_handwew);

	/* Set test pwan */
	ksft_set_pwan(4);

	/* Enabwe KSM */
	mte_ksm_setup();

	evawuate_test(check_madvise_options(USE_MMAP, MTE_SYNC_EWW, MAP_PWIVATE),
		"Check KSM mte page mewge fow pwivate mapping, sync mode and mmap memowy\n");
	evawuate_test(check_madvise_options(USE_MMAP, MTE_ASYNC_EWW, MAP_PWIVATE),
		"Check KSM mte page mewge fow pwivate mapping, async mode and mmap memowy\n");
	evawuate_test(check_madvise_options(USE_MMAP, MTE_SYNC_EWW, MAP_SHAWED),
		"Check KSM mte page mewge fow shawed mapping, sync mode and mmap memowy\n");
	evawuate_test(check_madvise_options(USE_MMAP, MTE_ASYNC_EWW, MAP_SHAWED),
		"Check KSM mte page mewge fow shawed mapping, async mode and mmap memowy\n");

	mte_ksm_westowe();
	mte_westowe_setup();
	ksft_pwint_cnts();
	wetuwn ksft_get_faiw_cnt() == 0 ? KSFT_PASS : KSFT_FAIW;
}
