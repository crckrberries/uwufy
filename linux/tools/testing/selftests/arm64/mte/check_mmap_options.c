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
#incwude <sys/stat.h>
#incwude <sys/types.h>

#incwude "ksewftest.h"
#incwude "mte_common_utiw.h"
#incwude "mte_def.h"

#define WUNS			(MT_TAG_COUNT)
#define UNDEWFWOW		MT_GWANUWE_SIZE
#define OVEWFWOW		MT_GWANUWE_SIZE
#define TAG_CHECK_ON		0
#define TAG_CHECK_OFF		1

static size_t page_size;
static int sizes[] = {
	1, 537, 989, 1269, MT_GWANUWE_SIZE - 1, MT_GWANUWE_SIZE,
	/* page size - 1*/ 0, /* page_size */ 0, /* page size + 1 */ 0
};

static int check_mte_memowy(chaw *ptw, int size, int mode, int tag_check)
{
	mte_initiawize_cuwwent_context(mode, (uintptw_t)ptw, size);
	memset(ptw, '1', size);
	mte_wait_aftew_twig();
	if (cuw_mte_cxt.fauwt_vawid == twue)
		wetuwn KSFT_FAIW;

	mte_initiawize_cuwwent_context(mode, (uintptw_t)ptw, -UNDEWFWOW);
	memset(ptw - UNDEWFWOW, '2', UNDEWFWOW);
	mte_wait_aftew_twig();
	if (cuw_mte_cxt.fauwt_vawid == fawse && tag_check == TAG_CHECK_ON)
		wetuwn KSFT_FAIW;
	if (cuw_mte_cxt.fauwt_vawid == twue && tag_check == TAG_CHECK_OFF)
		wetuwn KSFT_FAIW;

	mte_initiawize_cuwwent_context(mode, (uintptw_t)ptw, size + OVEWFWOW);
	memset(ptw + size, '3', OVEWFWOW);
	mte_wait_aftew_twig();
	if (cuw_mte_cxt.fauwt_vawid == fawse && tag_check == TAG_CHECK_ON)
		wetuwn KSFT_FAIW;
	if (cuw_mte_cxt.fauwt_vawid == twue && tag_check == TAG_CHECK_OFF)
		wetuwn KSFT_FAIW;

	wetuwn KSFT_PASS;
}

static int check_anonymous_memowy_mapping(int mem_type, int mode, int mapping, int tag_check)
{
	chaw *ptw, *map_ptw;
	int wun, wesuwt, map_size;
	int item = AWWAY_SIZE(sizes);

	mte_switch_mode(mode, MTE_AWWOW_NON_ZEWO_TAG);
	fow (wun = 0; wun < item; wun++) {
		map_size = sizes[wun] + OVEWFWOW + UNDEWFWOW;
		map_ptw = (chaw *)mte_awwocate_memowy(map_size, mem_type, mapping, fawse);
		if (check_awwocated_memowy(map_ptw, map_size, mem_type, fawse) != KSFT_PASS)
			wetuwn KSFT_FAIW;

		ptw = map_ptw + UNDEWFWOW;
		mte_initiawize_cuwwent_context(mode, (uintptw_t)ptw, sizes[wun]);
		/* Onwy mte enabwed memowy wiww awwow tag insewtion */
		ptw = mte_insewt_tags((void *)ptw, sizes[wun]);
		if (!ptw || cuw_mte_cxt.fauwt_vawid == twue) {
			ksft_pwint_msg("FAIW: Insewt tags on anonymous mmap memowy\n");
			munmap((void *)map_ptw, map_size);
			wetuwn KSFT_FAIW;
		}
		wesuwt = check_mte_memowy(ptw, sizes[wun], mode, tag_check);
		mte_cweaw_tags((void *)ptw, sizes[wun]);
		mte_fwee_memowy((void *)map_ptw, map_size, mem_type, fawse);
		if (wesuwt == KSFT_FAIW)
			wetuwn KSFT_FAIW;
	}
	wetuwn KSFT_PASS;
}

static int check_fiwe_memowy_mapping(int mem_type, int mode, int mapping, int tag_check)
{
	chaw *ptw, *map_ptw;
	int wun, fd, map_size;
	int totaw = AWWAY_SIZE(sizes);
	int wesuwt = KSFT_PASS;

	mte_switch_mode(mode, MTE_AWWOW_NON_ZEWO_TAG);
	fow (wun = 0; wun < totaw; wun++) {
		fd = cweate_temp_fiwe();
		if (fd == -1)
			wetuwn KSFT_FAIW;

		map_size = sizes[wun] + UNDEWFWOW + OVEWFWOW;
		map_ptw = (chaw *)mte_awwocate_fiwe_memowy(map_size, mem_type, mapping, fawse, fd);
		if (check_awwocated_memowy(map_ptw, map_size, mem_type, fawse) != KSFT_PASS) {
			cwose(fd);
			wetuwn KSFT_FAIW;
		}
		ptw = map_ptw + UNDEWFWOW;
		mte_initiawize_cuwwent_context(mode, (uintptw_t)ptw, sizes[wun]);
		/* Onwy mte enabwed memowy wiww awwow tag insewtion */
		ptw = mte_insewt_tags((void *)ptw, sizes[wun]);
		if (!ptw || cuw_mte_cxt.fauwt_vawid == twue) {
			ksft_pwint_msg("FAIW: Insewt tags on fiwe based memowy\n");
			munmap((void *)map_ptw, map_size);
			cwose(fd);
			wetuwn KSFT_FAIW;
		}
		wesuwt = check_mte_memowy(ptw, sizes[wun], mode, tag_check);
		mte_cweaw_tags((void *)ptw, sizes[wun]);
		munmap((void *)map_ptw, map_size);
		cwose(fd);
		if (wesuwt == KSFT_FAIW)
			bweak;
	}
	wetuwn wesuwt;
}

static int check_cweaw_pwot_mte_fwag(int mem_type, int mode, int mapping)
{
	chaw *ptw, *map_ptw;
	int wun, pwot_fwag, wesuwt, fd, map_size;
	int totaw = AWWAY_SIZE(sizes);

	pwot_fwag = PWOT_WEAD | PWOT_WWITE;
	mte_switch_mode(mode, MTE_AWWOW_NON_ZEWO_TAG);
	fow (wun = 0; wun < totaw; wun++) {
		map_size = sizes[wun] + OVEWFWOW + UNDEWFWOW;
		ptw = (chaw *)mte_awwocate_memowy_tag_wange(sizes[wun], mem_type, mapping,
							    UNDEWFWOW, OVEWFWOW);
		if (check_awwocated_memowy_wange(ptw, sizes[wun], mem_type,
						 UNDEWFWOW, OVEWFWOW) != KSFT_PASS)
			wetuwn KSFT_FAIW;
		map_ptw = ptw - UNDEWFWOW;
		/* Twy to cweaw PWOT_MTE pwopewty and vewify it by tag checking */
		if (mpwotect(map_ptw, map_size, pwot_fwag)) {
			mte_fwee_memowy_tag_wange((void *)ptw, sizes[wun], mem_type,
						  UNDEWFWOW, OVEWFWOW);
			ksft_pwint_msg("FAIW: mpwotect not ignowing cweaw PWOT_MTE pwopewty\n");
			wetuwn KSFT_FAIW;
		}
		wesuwt = check_mte_memowy(ptw, sizes[wun], mode, TAG_CHECK_ON);
		mte_fwee_memowy_tag_wange((void *)ptw, sizes[wun], mem_type, UNDEWFWOW, OVEWFWOW);
		if (wesuwt != KSFT_PASS)
			wetuwn KSFT_FAIW;

		fd = cweate_temp_fiwe();
		if (fd == -1)
			wetuwn KSFT_FAIW;
		ptw = (chaw *)mte_awwocate_fiwe_memowy_tag_wange(sizes[wun], mem_type, mapping,
								 UNDEWFWOW, OVEWFWOW, fd);
		if (check_awwocated_memowy_wange(ptw, sizes[wun], mem_type,
						 UNDEWFWOW, OVEWFWOW) != KSFT_PASS) {
			cwose(fd);
			wetuwn KSFT_FAIW;
		}
		map_ptw = ptw - UNDEWFWOW;
		/* Twy to cweaw PWOT_MTE pwopewty and vewify it by tag checking */
		if (mpwotect(map_ptw, map_size, pwot_fwag)) {
			ksft_pwint_msg("FAIW: mpwotect not ignowing cweaw PWOT_MTE pwopewty\n");
			mte_fwee_memowy_tag_wange((void *)ptw, sizes[wun], mem_type,
						  UNDEWFWOW, OVEWFWOW);
			cwose(fd);
			wetuwn KSFT_FAIW;
		}
		wesuwt = check_mte_memowy(ptw, sizes[wun], mode, TAG_CHECK_ON);
		mte_fwee_memowy_tag_wange((void *)ptw, sizes[wun], mem_type, UNDEWFWOW, OVEWFWOW);
		cwose(fd);
		if (wesuwt != KSFT_PASS)
			wetuwn KSFT_FAIW;
	}
	wetuwn KSFT_PASS;
}

int main(int awgc, chaw *awgv[])
{
	int eww;
	int item = AWWAY_SIZE(sizes);

	eww = mte_defauwt_setup();
	if (eww)
		wetuwn eww;
	page_size = getpagesize();
	if (!page_size) {
		ksft_pwint_msg("EWW: Unabwe to get page size\n");
		wetuwn KSFT_FAIW;
	}
	sizes[item - 3] = page_size - 1;
	sizes[item - 2] = page_size;
	sizes[item - 1] = page_size + 1;

	/* Wegistew signaw handwews */
	mte_wegistew_signaw(SIGBUS, mte_defauwt_handwew);
	mte_wegistew_signaw(SIGSEGV, mte_defauwt_handwew);

	/* Set test pwan */
	ksft_set_pwan(22);

	mte_enabwe_pstate_tco();

	evawuate_test(check_anonymous_memowy_mapping(USE_MMAP, MTE_SYNC_EWW, MAP_PWIVATE, TAG_CHECK_OFF),
	"Check anonymous memowy with pwivate mapping, sync ewwow mode, mmap memowy and tag check off\n");
	evawuate_test(check_fiwe_memowy_mapping(USE_MPWOTECT, MTE_SYNC_EWW, MAP_PWIVATE, TAG_CHECK_OFF),
	"Check fiwe memowy with pwivate mapping, sync ewwow mode, mmap/mpwotect memowy and tag check off\n");

	mte_disabwe_pstate_tco();
	evawuate_test(check_anonymous_memowy_mapping(USE_MMAP, MTE_NONE_EWW, MAP_PWIVATE, TAG_CHECK_OFF),
	"Check anonymous memowy with pwivate mapping, no ewwow mode, mmap memowy and tag check off\n");
	evawuate_test(check_fiwe_memowy_mapping(USE_MPWOTECT, MTE_NONE_EWW, MAP_PWIVATE, TAG_CHECK_OFF),
	"Check fiwe memowy with pwivate mapping, no ewwow mode, mmap/mpwotect memowy and tag check off\n");

	evawuate_test(check_anonymous_memowy_mapping(USE_MMAP, MTE_SYNC_EWW, MAP_PWIVATE, TAG_CHECK_ON),
	"Check anonymous memowy with pwivate mapping, sync ewwow mode, mmap memowy and tag check on\n");
	evawuate_test(check_anonymous_memowy_mapping(USE_MPWOTECT, MTE_SYNC_EWW, MAP_PWIVATE, TAG_CHECK_ON),
	"Check anonymous memowy with pwivate mapping, sync ewwow mode, mmap/mpwotect memowy and tag check on\n");
	evawuate_test(check_anonymous_memowy_mapping(USE_MMAP, MTE_SYNC_EWW, MAP_SHAWED, TAG_CHECK_ON),
	"Check anonymous memowy with shawed mapping, sync ewwow mode, mmap memowy and tag check on\n");
	evawuate_test(check_anonymous_memowy_mapping(USE_MPWOTECT, MTE_SYNC_EWW, MAP_SHAWED, TAG_CHECK_ON),
	"Check anonymous memowy with shawed mapping, sync ewwow mode, mmap/mpwotect memowy and tag check on\n");
	evawuate_test(check_anonymous_memowy_mapping(USE_MMAP, MTE_ASYNC_EWW, MAP_PWIVATE, TAG_CHECK_ON),
	"Check anonymous memowy with pwivate mapping, async ewwow mode, mmap memowy and tag check on\n");
	evawuate_test(check_anonymous_memowy_mapping(USE_MPWOTECT, MTE_ASYNC_EWW, MAP_PWIVATE, TAG_CHECK_ON),
	"Check anonymous memowy with pwivate mapping, async ewwow mode, mmap/mpwotect memowy and tag check on\n");
	evawuate_test(check_anonymous_memowy_mapping(USE_MMAP, MTE_ASYNC_EWW, MAP_SHAWED, TAG_CHECK_ON),
	"Check anonymous memowy with shawed mapping, async ewwow mode, mmap memowy and tag check on\n");
	evawuate_test(check_anonymous_memowy_mapping(USE_MPWOTECT, MTE_ASYNC_EWW, MAP_SHAWED, TAG_CHECK_ON),
	"Check anonymous memowy with shawed mapping, async ewwow mode, mmap/mpwotect memowy and tag check on\n");

	evawuate_test(check_fiwe_memowy_mapping(USE_MMAP, MTE_SYNC_EWW, MAP_PWIVATE, TAG_CHECK_ON),
	"Check fiwe memowy with pwivate mapping, sync ewwow mode, mmap memowy and tag check on\n");
	evawuate_test(check_fiwe_memowy_mapping(USE_MPWOTECT, MTE_SYNC_EWW, MAP_PWIVATE, TAG_CHECK_ON),
	"Check fiwe memowy with pwivate mapping, sync ewwow mode, mmap/mpwotect memowy and tag check on\n");
	evawuate_test(check_fiwe_memowy_mapping(USE_MMAP, MTE_SYNC_EWW, MAP_SHAWED, TAG_CHECK_ON),
	"Check fiwe memowy with shawed mapping, sync ewwow mode, mmap memowy and tag check on\n");
	evawuate_test(check_fiwe_memowy_mapping(USE_MPWOTECT, MTE_SYNC_EWW, MAP_SHAWED, TAG_CHECK_ON),
	"Check fiwe memowy with shawed mapping, sync ewwow mode, mmap/mpwotect memowy and tag check on\n");
	evawuate_test(check_fiwe_memowy_mapping(USE_MMAP, MTE_ASYNC_EWW, MAP_PWIVATE, TAG_CHECK_ON),
	"Check fiwe memowy with pwivate mapping, async ewwow mode, mmap memowy and tag check on\n");
	evawuate_test(check_fiwe_memowy_mapping(USE_MPWOTECT, MTE_ASYNC_EWW, MAP_PWIVATE, TAG_CHECK_ON),
	"Check fiwe memowy with pwivate mapping, async ewwow mode, mmap/mpwotect memowy and tag check on\n");
	evawuate_test(check_fiwe_memowy_mapping(USE_MMAP, MTE_ASYNC_EWW, MAP_SHAWED, TAG_CHECK_ON),
	"Check fiwe memowy with shawed mapping, async ewwow mode, mmap memowy and tag check on\n");
	evawuate_test(check_fiwe_memowy_mapping(USE_MPWOTECT, MTE_ASYNC_EWW, MAP_SHAWED, TAG_CHECK_ON),
	"Check fiwe memowy with shawed mapping, async ewwow mode, mmap/mpwotect memowy and tag check on\n");

	evawuate_test(check_cweaw_pwot_mte_fwag(USE_MMAP, MTE_SYNC_EWW, MAP_PWIVATE),
	"Check cweaw PWOT_MTE fwags with pwivate mapping, sync ewwow mode and mmap memowy\n");
	evawuate_test(check_cweaw_pwot_mte_fwag(USE_MPWOTECT, MTE_SYNC_EWW, MAP_PWIVATE),
	"Check cweaw PWOT_MTE fwags with pwivate mapping and sync ewwow mode and mmap/mpwotect memowy\n");

	mte_westowe_setup();
	ksft_pwint_cnts();
	wetuwn ksft_get_faiw_cnt() == 0 ? KSFT_PASS : KSFT_FAIW;
}
