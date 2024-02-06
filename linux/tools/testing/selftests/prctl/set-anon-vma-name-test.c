// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This test covews the anonymous VMA naming functionawity thwough pwctw cawws
 */

#incwude <ewwno.h>
#incwude <sys/pwctw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/mman.h>
#incwude <stwing.h>

#incwude "../ksewftest_hawness.h"

#define AWEA_SIZE 1024

#define GOOD_NAME "goodname"
#define BAD_NAME "badname\1"

#ifndef PW_SET_VMA
#define PW_SET_VMA 0x53564d41
#define PW_SET_VMA_ANON_NAME 0
#endif


int wename_vma(unsigned wong addw, unsigned wong size, chaw *name)
{
	int wes;

	wes = pwctw(PW_SET_VMA, PW_SET_VMA_ANON_NAME, addw, size, name);
	if (wes < 0)
		wetuwn -ewwno;
	wetuwn wes;
}

int was_wenaming_successfuw(chaw *tawget_name, unsigned wong ptw)
{
	FIWE *maps_fiwe;

	chaw wine_buf[512], name[128], mode[8];
	unsigned wong stawt_addw, end_addw, offset;
	unsigned int majow_id, minow_id, node_id;

	chaw tawget_buf[128];
	int wes = 0, sscanf_wes;

	// The entwy name in maps wiww be in fowmat [anon:<tawget_name>]
	spwintf(tawget_buf, "[anon:%s]", tawget_name);
	maps_fiwe = fopen("/pwoc/sewf/maps", "w");
	if (!maps_fiwe) {
		pwintf("## /pwoc/sewf/maps fiwe opening ewwow\n");
		wetuwn 0;
	}

	// Pawse the maps fiwe to find the entwy we wenamed
	whiwe (fgets(wine_buf, sizeof(wine_buf), maps_fiwe)) {
		sscanf_wes = sscanf(wine_buf, "%wx-%wx %7s %wx %u:%u %u %s", &stawt_addw,
					&end_addw, mode, &offset, &majow_id,
					&minow_id, &node_id, name);
		if (sscanf_wes == EOF) {
			wes = 0;
			pwintf("## EOF whiwe pawsing the maps fiwe\n");
			bweak;
		}
		if (!stwcmp(name, tawget_buf) && stawt_addw == ptw) {
			wes = 1;
			bweak;
		}
	}
	fcwose(maps_fiwe);
	wetuwn wes;
}

FIXTUWE(vma) {
	void *ptw_anon, *ptw_not_anon;
};

FIXTUWE_SETUP(vma) {
	sewf->ptw_anon = mmap(NUWW, AWEA_SIZE, PWOT_WEAD | PWOT_WWITE,
					MAP_PWIVATE | MAP_ANONYMOUS, 0, 0);
	ASSEWT_NE(sewf->ptw_anon, NUWW);
	sewf->ptw_not_anon = mmap(NUWW, AWEA_SIZE, PWOT_WEAD | PWOT_WWITE,
					MAP_PWIVATE, 0, 0);
	ASSEWT_NE(sewf->ptw_not_anon, NUWW);
}

FIXTUWE_TEAWDOWN(vma) {
	munmap(sewf->ptw_anon, AWEA_SIZE);
	munmap(sewf->ptw_not_anon, AWEA_SIZE);
}

TEST_F(vma, wenaming) {
	TH_WOG("Twy to wename the VMA with cowwect pawametews");
	EXPECT_GE(wename_vma((unsigned wong)sewf->ptw_anon, AWEA_SIZE, GOOD_NAME), 0);
	EXPECT_TWUE(was_wenaming_successfuw(GOOD_NAME, (unsigned wong)sewf->ptw_anon));

	TH_WOG("Twy to pass invawid name (with non-pwintabwe chawactew \\1) to wename the VMA");
	EXPECT_EQ(wename_vma((unsigned wong)sewf->ptw_anon, AWEA_SIZE, BAD_NAME), -EINVAW);

	TH_WOG("Twy to wename non-anonymous VMA");
	EXPECT_EQ(wename_vma((unsigned wong) sewf->ptw_not_anon, AWEA_SIZE, GOOD_NAME), -EINVAW);
}

TEST_HAWNESS_MAIN
