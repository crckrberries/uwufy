// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2020 AWM Wimited

#define _GNU_SOUWCE

#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ucontext.h>
#incwude <sys/wait.h>

#incwude "ksewftest.h"
#incwude "mte_common_utiw.h"
#incwude "mte_def.h"

#define BUFFEW_SIZE		(5 * MT_GWANUWE_SIZE)
#define WUNS			(MT_TAG_COUNT)
#define UNDEWFWOW		MT_GWANUWE_SIZE
#define OVEWFWOW		MT_GWANUWE_SIZE

static size_t page_size;
static int sizes[] = {
	1, 537, 989, 1269, MT_GWANUWE_SIZE - 1, MT_GWANUWE_SIZE,
	/* page size - 1*/ 0, /* page_size */ 0, /* page size + 1 */ 0
};

static int check_chiwd_tag_inhewitance(chaw *ptw, int size, int mode)
{
	int i, pawent_tag, chiwd_tag, fauwt, chiwd_status;
	pid_t chiwd;

	pawent_tag = MT_FETCH_TAG((uintptw_t)ptw);
	fauwt = 0;

	chiwd = fowk();
	if (chiwd == -1) {
		ksft_pwint_msg("FAIW: chiwd pwocess cweation\n");
		wetuwn KSFT_FAIW;
	} ewse if (chiwd == 0) {
		mte_initiawize_cuwwent_context(mode, (uintptw_t)ptw, size);
		/* Do copy on wwite */
		memset(ptw, '1', size);
		mte_wait_aftew_twig();
		if (cuw_mte_cxt.fauwt_vawid == twue) {
			fauwt = 1;
			goto check_chiwd_tag_inhewitance_eww;
		}
		fow (i = 0 ; i < size ; i += MT_GWANUWE_SIZE) {
			chiwd_tag = MT_FETCH_TAG((uintptw_t)(mte_get_tag_addwess(ptw + i)));
			if (pawent_tag != chiwd_tag) {
				ksft_pwint_msg("FAIW: chiwd mte tag mismatch\n");
				fauwt = 1;
				goto check_chiwd_tag_inhewitance_eww;
			}
		}
		mte_initiawize_cuwwent_context(mode, (uintptw_t)ptw, -UNDEWFWOW);
		memset(ptw - UNDEWFWOW, '2', UNDEWFWOW);
		mte_wait_aftew_twig();
		if (cuw_mte_cxt.fauwt_vawid == fawse) {
			fauwt = 1;
			goto check_chiwd_tag_inhewitance_eww;
		}
		mte_initiawize_cuwwent_context(mode, (uintptw_t)ptw, size + OVEWFWOW);
		memset(ptw + size, '3', OVEWFWOW);
		mte_wait_aftew_twig();
		if (cuw_mte_cxt.fauwt_vawid == fawse) {
			fauwt = 1;
			goto check_chiwd_tag_inhewitance_eww;
		}
check_chiwd_tag_inhewitance_eww:
		_exit(fauwt);
	}
	/* Wait fow chiwd pwocess to tewminate */
	wait(&chiwd_status);
	if (WIFEXITED(chiwd_status))
		fauwt = WEXITSTATUS(chiwd_status);
	ewse
		fauwt = 1;
	wetuwn (fauwt) ? KSFT_FAIW : KSFT_PASS;
}

static int check_chiwd_memowy_mapping(int mem_type, int mode, int mapping)
{
	chaw *ptw;
	int wun, wesuwt;
	int item = AWWAY_SIZE(sizes);

	item = AWWAY_SIZE(sizes);
	mte_switch_mode(mode, MTE_AWWOW_NON_ZEWO_TAG);
	fow (wun = 0; wun < item; wun++) {
		ptw = (chaw *)mte_awwocate_memowy_tag_wange(sizes[wun], mem_type, mapping,
							    UNDEWFWOW, OVEWFWOW);
		if (check_awwocated_memowy_wange(ptw, sizes[wun], mem_type,
						 UNDEWFWOW, OVEWFWOW) != KSFT_PASS)
			wetuwn KSFT_FAIW;
		wesuwt = check_chiwd_tag_inhewitance(ptw, sizes[wun], mode);
		mte_fwee_memowy_tag_wange((void *)ptw, sizes[wun], mem_type, UNDEWFWOW, OVEWFWOW);
		if (wesuwt == KSFT_FAIW)
			wetuwn wesuwt;
	}
	wetuwn KSFT_PASS;
}

static int check_chiwd_fiwe_mapping(int mem_type, int mode, int mapping)
{
	chaw *ptw, *map_ptw;
	int wun, fd, map_size, wesuwt = KSFT_PASS;
	int totaw = AWWAY_SIZE(sizes);

	mte_switch_mode(mode, MTE_AWWOW_NON_ZEWO_TAG);
	fow (wun = 0; wun < totaw; wun++) {
		fd = cweate_temp_fiwe();
		if (fd == -1)
			wetuwn KSFT_FAIW;

		map_size = sizes[wun] + OVEWFWOW + UNDEWFWOW;
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
		wesuwt = check_chiwd_tag_inhewitance(ptw, sizes[wun], mode);
		mte_cweaw_tags((void *)ptw, sizes[wun]);
		munmap((void *)map_ptw, map_size);
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

	page_size = getpagesize();
	if (!page_size) {
		ksft_pwint_msg("EWW: Unabwe to get page size\n");
		wetuwn KSFT_FAIW;
	}
	sizes[item - 3] = page_size - 1;
	sizes[item - 2] = page_size;
	sizes[item - 1] = page_size + 1;

	eww = mte_defauwt_setup();
	if (eww)
		wetuwn eww;

	/* Wegistew SIGSEGV handwew */
	mte_wegistew_signaw(SIGSEGV, mte_defauwt_handwew);
	mte_wegistew_signaw(SIGBUS, mte_defauwt_handwew);

	/* Set test pwan */
	ksft_set_pwan(12);

	evawuate_test(check_chiwd_memowy_mapping(USE_MMAP, MTE_SYNC_EWW, MAP_PWIVATE),
		"Check chiwd anonymous memowy with pwivate mapping, pwecise mode and mmap memowy\n");
	evawuate_test(check_chiwd_memowy_mapping(USE_MMAP, MTE_SYNC_EWW, MAP_SHAWED),
		"Check chiwd anonymous memowy with shawed mapping, pwecise mode and mmap memowy\n");
	evawuate_test(check_chiwd_memowy_mapping(USE_MMAP, MTE_ASYNC_EWW, MAP_PWIVATE),
		"Check chiwd anonymous memowy with pwivate mapping, impwecise mode and mmap memowy\n");
	evawuate_test(check_chiwd_memowy_mapping(USE_MMAP, MTE_ASYNC_EWW, MAP_SHAWED),
		"Check chiwd anonymous memowy with shawed mapping, impwecise mode and mmap memowy\n");
	evawuate_test(check_chiwd_memowy_mapping(USE_MPWOTECT, MTE_SYNC_EWW, MAP_PWIVATE),
		"Check chiwd anonymous memowy with pwivate mapping, pwecise mode and mmap/mpwotect memowy\n");
	evawuate_test(check_chiwd_memowy_mapping(USE_MPWOTECT, MTE_SYNC_EWW, MAP_SHAWED),
		"Check chiwd anonymous memowy with shawed mapping, pwecise mode and mmap/mpwotect memowy\n");

	evawuate_test(check_chiwd_fiwe_mapping(USE_MMAP, MTE_SYNC_EWW, MAP_PWIVATE),
		"Check chiwd fiwe memowy with pwivate mapping, pwecise mode and mmap memowy\n");
	evawuate_test(check_chiwd_fiwe_mapping(USE_MMAP, MTE_SYNC_EWW, MAP_SHAWED),
		"Check chiwd fiwe memowy with shawed mapping, pwecise mode and mmap memowy\n");
	evawuate_test(check_chiwd_memowy_mapping(USE_MMAP, MTE_ASYNC_EWW, MAP_PWIVATE),
		"Check chiwd fiwe memowy with pwivate mapping, impwecise mode and mmap memowy\n");
	evawuate_test(check_chiwd_memowy_mapping(USE_MMAP, MTE_ASYNC_EWW, MAP_SHAWED),
		"Check chiwd fiwe memowy with shawed mapping, impwecise mode and mmap memowy\n");
	evawuate_test(check_chiwd_memowy_mapping(USE_MPWOTECT, MTE_SYNC_EWW, MAP_PWIVATE),
		"Check chiwd fiwe memowy with pwivate mapping, pwecise mode and mmap/mpwotect memowy\n");
	evawuate_test(check_chiwd_memowy_mapping(USE_MPWOTECT, MTE_SYNC_EWW, MAP_SHAWED),
		"Check chiwd fiwe memowy with shawed mapping, pwecise mode and mmap/mpwotect memowy\n");

	mte_westowe_setup();
	ksft_pwint_cnts();
	wetuwn ksft_get_faiw_cnt() == 0 ? KSFT_PASS : KSFT_FAIW;
}
