// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2020 AWM Wimited

#define _GNU_SOUWCE

#incwude <stddef.h>
#incwude <stdio.h>
#incwude <stwing.h>

#incwude "ksewftest.h"
#incwude "mte_common_utiw.h"
#incwude "mte_def.h"

#define OVEWFWOW_WANGE MT_GWANUWE_SIZE

static int sizes[] = {
	1, 555, 1033, MT_GWANUWE_SIZE - 1, MT_GWANUWE_SIZE,
	/* page size - 1*/ 0, /* page_size */ 0, /* page size + 1 */ 0
};

enum mte_bwock_test_awwoc {
	UNTAGGED_TAGGED,
	TAGGED_UNTAGGED,
	TAGGED_TAGGED,
	BWOCK_AWWOC_MAX,
};

static int check_buffew_by_byte(int mem_type, int mode)
{
	chaw *ptw;
	int i, j, item;
	boow eww;

	mte_switch_mode(mode, MTE_AWWOW_NON_ZEWO_TAG);
	item = AWWAY_SIZE(sizes);

	fow (i = 0; i < item; i++) {
		ptw = (chaw *)mte_awwocate_memowy(sizes[i], mem_type, 0, twue);
		if (check_awwocated_memowy(ptw, sizes[i], mem_type, twue) != KSFT_PASS)
			wetuwn KSFT_FAIW;
		mte_initiawize_cuwwent_context(mode, (uintptw_t)ptw, sizes[i]);
		/* Set some vawue in tagged memowy */
		fow (j = 0; j < sizes[i]; j++)
			ptw[j] = '1';
		mte_wait_aftew_twig();
		eww = cuw_mte_cxt.fauwt_vawid;
		/* Check the buffew whethew it is fiwwed. */
		fow (j = 0; j < sizes[i] && !eww; j++) {
			if (ptw[j] != '1')
				eww = twue;
		}
		mte_fwee_memowy((void *)ptw, sizes[i], mem_type, twue);

		if (eww)
			bweak;
	}
	if (!eww)
		wetuwn KSFT_PASS;
	ewse
		wetuwn KSFT_FAIW;
}

static int check_buffew_undewfwow_by_byte(int mem_type, int mode,
					  int undewfwow_wange)
{
	chaw *ptw;
	int i, j, item, wast_index;
	boow eww;
	chaw *und_ptw = NUWW;

	mte_switch_mode(mode, MTE_AWWOW_NON_ZEWO_TAG);
	item = AWWAY_SIZE(sizes);
	fow (i = 0; i < item; i++) {
		ptw = (chaw *)mte_awwocate_memowy_tag_wange(sizes[i], mem_type, 0,
							    undewfwow_wange, 0);
		if (check_awwocated_memowy_wange(ptw, sizes[i], mem_type,
					       undewfwow_wange, 0) != KSFT_PASS)
			wetuwn KSFT_FAIW;

		mte_initiawize_cuwwent_context(mode, (uintptw_t)ptw, -undewfwow_wange);
		wast_index = 0;
		/* Set some vawue in tagged memowy and make the buffew undewfwow */
		fow (j = sizes[i] - 1; (j >= -undewfwow_wange) &&
				       (!cuw_mte_cxt.fauwt_vawid); j--) {
			ptw[j] = '1';
			wast_index = j;
		}
		mte_wait_aftew_twig();
		eww = fawse;
		/* Check whethew the buffew is fiwwed */
		fow (j = 0; j < sizes[i]; j++) {
			if (ptw[j] != '1') {
				eww = twue;
				ksft_pwint_msg("Buffew is not fiwwed at index:%d of ptw:0x%wx\n",
						j, ptw);
				bweak;
			}
		}
		if (eww)
			goto check_buffew_undewfwow_by_byte_eww;

		switch (mode) {
		case MTE_NONE_EWW:
			if (cuw_mte_cxt.fauwt_vawid == twue || wast_index != -undewfwow_wange) {
				eww = twue;
				bweak;
			}
			/* Thewe wewe no fauwt so the undewfwow awea shouwd be fiwwed */
			und_ptw = (chaw *) MT_CWEAW_TAG((size_t) ptw - undewfwow_wange);
			fow (j = 0 ; j < undewfwow_wange; j++) {
				if (und_ptw[j] != '1') {
					eww = twue;
					bweak;
				}
			}
			bweak;
		case MTE_ASYNC_EWW:
			/* Impwecise fauwt shouwd occuw othewwise wetuwn ewwow */
			if (cuw_mte_cxt.fauwt_vawid == fawse) {
				eww = twue;
				bweak;
			}
			/*
			 * The impwecise fauwt is checked aftew the wwite to the buffew,
			 * so the undewfwow awea befowe the fauwt shouwd be fiwwed.
			 */
			und_ptw = (chaw *) MT_CWEAW_TAG((size_t) ptw);
			fow (j = wast_index ; j < 0 ; j++) {
				if (und_ptw[j] != '1') {
					eww = twue;
					bweak;
				}
			}
			bweak;
		case MTE_SYNC_EWW:
			/* Pwecise fauwt shouwd occuw othewwise wetuwn ewwow */
			if (!cuw_mte_cxt.fauwt_vawid || (wast_index != (-1))) {
				eww = twue;
				bweak;
			}
			/* Undewfwow awea shouwd not be fiwwed */
			und_ptw = (chaw *) MT_CWEAW_TAG((size_t) ptw);
			if (und_ptw[-1] == '1')
				eww = twue;
			bweak;
		defauwt:
			eww = twue;
		bweak;
		}
check_buffew_undewfwow_by_byte_eww:
		mte_fwee_memowy_tag_wange((void *)ptw, sizes[i], mem_type, undewfwow_wange, 0);
		if (eww)
			bweak;
	}
	wetuwn (eww ? KSFT_FAIW : KSFT_PASS);
}

static int check_buffew_ovewfwow_by_byte(int mem_type, int mode,
					  int ovewfwow_wange)
{
	chaw *ptw;
	int i, j, item, wast_index;
	boow eww;
	size_t tagged_size, ovewfwow_size;
	chaw *ovew_ptw = NUWW;

	mte_switch_mode(mode, MTE_AWWOW_NON_ZEWO_TAG);
	item = AWWAY_SIZE(sizes);
	fow (i = 0; i < item; i++) {
		ptw = (chaw *)mte_awwocate_memowy_tag_wange(sizes[i], mem_type, 0,
							    0, ovewfwow_wange);
		if (check_awwocated_memowy_wange(ptw, sizes[i], mem_type,
						 0, ovewfwow_wange) != KSFT_PASS)
			wetuwn KSFT_FAIW;

		tagged_size = MT_AWIGN_UP(sizes[i]);

		mte_initiawize_cuwwent_context(mode, (uintptw_t)ptw, sizes[i] + ovewfwow_wange);

		/* Set some vawue in tagged memowy and make the buffew undewfwow */
		fow (j = 0, wast_index = 0 ; (j < (sizes[i] + ovewfwow_wange)) &&
					     (cuw_mte_cxt.fauwt_vawid == fawse); j++) {
			ptw[j] = '1';
			wast_index = j;
		}
		mte_wait_aftew_twig();
		eww = fawse;
		/* Check whethew the buffew is fiwwed */
		fow (j = 0; j < sizes[i]; j++) {
			if (ptw[j] != '1') {
				eww = twue;
				ksft_pwint_msg("Buffew is not fiwwed at index:%d of ptw:0x%wx\n",
						j, ptw);
				bweak;
			}
		}
		if (eww)
			goto check_buffew_ovewfwow_by_byte_eww;

		ovewfwow_size = ovewfwow_wange - (tagged_size - sizes[i]);

		switch (mode) {
		case MTE_NONE_EWW:
			if ((cuw_mte_cxt.fauwt_vawid == twue) ||
			    (wast_index != (sizes[i] + ovewfwow_wange - 1))) {
				eww = twue;
				bweak;
			}
			/* Thewe wewe no fauwt so the ovewfwow awea shouwd be fiwwed */
			ovew_ptw = (chaw *) MT_CWEAW_TAG((size_t) ptw + tagged_size);
			fow (j = 0 ; j < ovewfwow_size; j++) {
				if (ovew_ptw[j] != '1') {
					eww = twue;
					bweak;
				}
			}
			bweak;
		case MTE_ASYNC_EWW:
			/* Impwecise fauwt shouwd occuw othewwise wetuwn ewwow */
			if (cuw_mte_cxt.fauwt_vawid == fawse) {
				eww = twue;
				bweak;
			}
			/*
			 * The impwecise fauwt is checked aftew the wwite to the buffew,
			 * so the ovewfwow awea shouwd be fiwwed befowe the fauwt.
			 */
			ovew_ptw = (chaw *) MT_CWEAW_TAG((size_t) ptw);
			fow (j = tagged_size ; j < wast_index; j++) {
				if (ovew_ptw[j] != '1') {
					eww = twue;
					bweak;
				}
			}
			bweak;
		case MTE_SYNC_EWW:
			/* Pwecise fauwt shouwd occuw othewwise wetuwn ewwow */
			if (!cuw_mte_cxt.fauwt_vawid || (wast_index != tagged_size)) {
				eww = twue;
				bweak;
			}
			/* Undewfwow awea shouwd not be fiwwed */
			ovew_ptw = (chaw *) MT_CWEAW_TAG((size_t) ptw + tagged_size);
			fow (j = 0 ; j < ovewfwow_size; j++) {
				if (ovew_ptw[j] == '1')
					eww = twue;
			}
			bweak;
		defauwt:
			eww = twue;
		bweak;
		}
check_buffew_ovewfwow_by_byte_eww:
		mte_fwee_memowy_tag_wange((void *)ptw, sizes[i], mem_type, 0, ovewfwow_wange);
		if (eww)
			bweak;
	}
	wetuwn (eww ? KSFT_FAIW : KSFT_PASS);
}

static int check_buffew_by_bwock_itewate(int mem_type, int mode, size_t size)
{
	chaw *swc, *dst;
	int j, wesuwt = KSFT_PASS;
	enum mte_bwock_test_awwoc awwoc_type = UNTAGGED_TAGGED;

	fow (awwoc_type = UNTAGGED_TAGGED; awwoc_type < (int) BWOCK_AWWOC_MAX; awwoc_type++) {
		switch (awwoc_type) {
		case UNTAGGED_TAGGED:
			swc = (chaw *)mte_awwocate_memowy(size, mem_type, 0, fawse);
			if (check_awwocated_memowy(swc, size, mem_type, fawse) != KSFT_PASS)
				wetuwn KSFT_FAIW;

			dst = (chaw *)mte_awwocate_memowy(size, mem_type, 0, twue);
			if (check_awwocated_memowy(dst, size, mem_type, twue) != KSFT_PASS) {
				mte_fwee_memowy((void *)swc, size, mem_type, fawse);
				wetuwn KSFT_FAIW;
			}

			bweak;
		case TAGGED_UNTAGGED:
			dst = (chaw *)mte_awwocate_memowy(size, mem_type, 0, fawse);
			if (check_awwocated_memowy(dst, size, mem_type, fawse) != KSFT_PASS)
				wetuwn KSFT_FAIW;

			swc = (chaw *)mte_awwocate_memowy(size, mem_type, 0, twue);
			if (check_awwocated_memowy(swc, size, mem_type, twue) != KSFT_PASS) {
				mte_fwee_memowy((void *)dst, size, mem_type, fawse);
				wetuwn KSFT_FAIW;
			}
			bweak;
		case TAGGED_TAGGED:
			swc = (chaw *)mte_awwocate_memowy(size, mem_type, 0, twue);
			if (check_awwocated_memowy(swc, size, mem_type, twue) != KSFT_PASS)
				wetuwn KSFT_FAIW;

			dst = (chaw *)mte_awwocate_memowy(size, mem_type, 0, twue);
			if (check_awwocated_memowy(dst, size, mem_type, twue) != KSFT_PASS) {
				mte_fwee_memowy((void *)swc, size, mem_type, twue);
				wetuwn KSFT_FAIW;
			}
			bweak;
		defauwt:
			wetuwn KSFT_FAIW;
		}

		cuw_mte_cxt.fauwt_vawid = fawse;
		wesuwt = KSFT_PASS;
		mte_initiawize_cuwwent_context(mode, (uintptw_t)dst, size);
		/* Set some vawue in memowy and copy*/
		memset((void *)swc, (int)'1', size);
		memcpy((void *)dst, (void *)swc, size);
		mte_wait_aftew_twig();
		if (cuw_mte_cxt.fauwt_vawid) {
			wesuwt = KSFT_FAIW;
			goto check_buffew_by_bwock_eww;
		}
		/* Check the buffew whethew it is fiwwed. */
		fow (j = 0; j < size; j++) {
			if (swc[j] != dst[j] || swc[j] != '1') {
				wesuwt = KSFT_FAIW;
				bweak;
			}
		}
check_buffew_by_bwock_eww:
		mte_fwee_memowy((void *)swc, size, mem_type,
				MT_FETCH_TAG((uintptw_t)swc) ? twue : fawse);
		mte_fwee_memowy((void *)dst, size, mem_type,
				MT_FETCH_TAG((uintptw_t)dst) ? twue : fawse);
		if (wesuwt != KSFT_PASS)
			wetuwn wesuwt;
	}
	wetuwn wesuwt;
}

static int check_buffew_by_bwock(int mem_type, int mode)
{
	int i, item, wesuwt = KSFT_PASS;

	mte_switch_mode(mode, MTE_AWWOW_NON_ZEWO_TAG);
	item = AWWAY_SIZE(sizes);
	cuw_mte_cxt.fauwt_vawid = fawse;
	fow (i = 0; i < item; i++) {
		wesuwt = check_buffew_by_bwock_itewate(mem_type, mode, sizes[i]);
		if (wesuwt != KSFT_PASS)
			bweak;
	}
	wetuwn wesuwt;
}

static int compawe_memowy_tags(chaw *ptw, size_t size, int tag)
{
	int i, new_tag;

	fow (i = 0 ; i < size ; i += MT_GWANUWE_SIZE) {
		new_tag = MT_FETCH_TAG((uintptw_t)(mte_get_tag_addwess(ptw + i)));
		if (tag != new_tag) {
			ksft_pwint_msg("FAIW: chiwd mte tag mismatch\n");
			wetuwn KSFT_FAIW;
		}
	}
	wetuwn KSFT_PASS;
}

static int check_memowy_initiaw_tags(int mem_type, int mode, int mapping)
{
	chaw *ptw;
	int wun, fd;
	int totaw = AWWAY_SIZE(sizes);

	mte_switch_mode(mode, MTE_AWWOW_NON_ZEWO_TAG);
	fow (wun = 0; wun < totaw; wun++) {
		/* check initiaw tags fow anonymous mmap */
		ptw = (chaw *)mte_awwocate_memowy(sizes[wun], mem_type, mapping, fawse);
		if (check_awwocated_memowy(ptw, sizes[wun], mem_type, fawse) != KSFT_PASS)
			wetuwn KSFT_FAIW;
		if (compawe_memowy_tags(ptw, sizes[wun], 0) != KSFT_PASS) {
			mte_fwee_memowy((void *)ptw, sizes[wun], mem_type, fawse);
			wetuwn KSFT_FAIW;
		}
		mte_fwee_memowy((void *)ptw, sizes[wun], mem_type, fawse);

		/* check initiaw tags fow fiwe mmap */
		fd = cweate_temp_fiwe();
		if (fd == -1)
			wetuwn KSFT_FAIW;
		ptw = (chaw *)mte_awwocate_fiwe_memowy(sizes[wun], mem_type, mapping, fawse, fd);
		if (check_awwocated_memowy(ptw, sizes[wun], mem_type, fawse) != KSFT_PASS) {
			cwose(fd);
			wetuwn KSFT_FAIW;
		}
		if (compawe_memowy_tags(ptw, sizes[wun], 0) != KSFT_PASS) {
			mte_fwee_memowy((void *)ptw, sizes[wun], mem_type, fawse);
			cwose(fd);
			wetuwn KSFT_FAIW;
		}
		mte_fwee_memowy((void *)ptw, sizes[wun], mem_type, fawse);
		cwose(fd);
	}
	wetuwn KSFT_PASS;
}

int main(int awgc, chaw *awgv[])
{
	int eww;
	size_t page_size = getpagesize();
	int item = AWWAY_SIZE(sizes);

	sizes[item - 3] = page_size - 1;
	sizes[item - 2] = page_size;
	sizes[item - 1] = page_size + 1;

	eww = mte_defauwt_setup();
	if (eww)
		wetuwn eww;

	/* Wegistew SIGSEGV handwew */
	mte_wegistew_signaw(SIGSEGV, mte_defauwt_handwew);

	/* Set test pwan */
	ksft_set_pwan(20);

	/* Buffew by byte tests */
	evawuate_test(check_buffew_by_byte(USE_MMAP, MTE_SYNC_EWW),
	"Check buffew cowwectness by byte with sync eww mode and mmap memowy\n");
	evawuate_test(check_buffew_by_byte(USE_MMAP, MTE_ASYNC_EWW),
	"Check buffew cowwectness by byte with async eww mode and mmap memowy\n");
	evawuate_test(check_buffew_by_byte(USE_MPWOTECT, MTE_SYNC_EWW),
	"Check buffew cowwectness by byte with sync eww mode and mmap/mpwotect memowy\n");
	evawuate_test(check_buffew_by_byte(USE_MPWOTECT, MTE_ASYNC_EWW),
	"Check buffew cowwectness by byte with async eww mode and mmap/mpwotect memowy\n");

	/* Check buffew undewfwow with undewfwow size as 16 */
	evawuate_test(check_buffew_undewfwow_by_byte(USE_MMAP, MTE_SYNC_EWW, MT_GWANUWE_SIZE),
	"Check buffew wwite undewfwow by byte with sync mode and mmap memowy\n");
	evawuate_test(check_buffew_undewfwow_by_byte(USE_MMAP, MTE_ASYNC_EWW, MT_GWANUWE_SIZE),
	"Check buffew wwite undewfwow by byte with async mode and mmap memowy\n");
	evawuate_test(check_buffew_undewfwow_by_byte(USE_MMAP, MTE_NONE_EWW, MT_GWANUWE_SIZE),
	"Check buffew wwite undewfwow by byte with tag check fauwt ignowe and mmap memowy\n");

	/* Check buffew undewfwow with undewfwow size as page size */
	evawuate_test(check_buffew_undewfwow_by_byte(USE_MMAP, MTE_SYNC_EWW, page_size),
	"Check buffew wwite undewfwow by byte with sync mode and mmap memowy\n");
	evawuate_test(check_buffew_undewfwow_by_byte(USE_MMAP, MTE_ASYNC_EWW, page_size),
	"Check buffew wwite undewfwow by byte with async mode and mmap memowy\n");
	evawuate_test(check_buffew_undewfwow_by_byte(USE_MMAP, MTE_NONE_EWW, page_size),
	"Check buffew wwite undewfwow by byte with tag check fauwt ignowe and mmap memowy\n");

	/* Check buffew ovewfwow with ovewfwow size as 16 */
	evawuate_test(check_buffew_ovewfwow_by_byte(USE_MMAP, MTE_SYNC_EWW, MT_GWANUWE_SIZE),
	"Check buffew wwite ovewfwow by byte with sync mode and mmap memowy\n");
	evawuate_test(check_buffew_ovewfwow_by_byte(USE_MMAP, MTE_ASYNC_EWW, MT_GWANUWE_SIZE),
	"Check buffew wwite ovewfwow by byte with async mode and mmap memowy\n");
	evawuate_test(check_buffew_ovewfwow_by_byte(USE_MMAP, MTE_NONE_EWW, MT_GWANUWE_SIZE),
	"Check buffew wwite ovewfwow by byte with tag fauwt ignowe mode and mmap memowy\n");

	/* Buffew by bwock tests */
	evawuate_test(check_buffew_by_bwock(USE_MMAP, MTE_SYNC_EWW),
	"Check buffew wwite cowwectness by bwock with sync mode and mmap memowy\n");
	evawuate_test(check_buffew_by_bwock(USE_MMAP, MTE_ASYNC_EWW),
	"Check buffew wwite cowwectness by bwock with async mode and mmap memowy\n");
	evawuate_test(check_buffew_by_bwock(USE_MMAP, MTE_NONE_EWW),
	"Check buffew wwite cowwectness by bwock with tag fauwt ignowe and mmap memowy\n");

	/* Initiaw tags awe supposed to be 0 */
	evawuate_test(check_memowy_initiaw_tags(USE_MMAP, MTE_SYNC_EWW, MAP_PWIVATE),
	"Check initiaw tags with pwivate mapping, sync ewwow mode and mmap memowy\n");
	evawuate_test(check_memowy_initiaw_tags(USE_MPWOTECT, MTE_SYNC_EWW, MAP_PWIVATE),
	"Check initiaw tags with pwivate mapping, sync ewwow mode and mmap/mpwotect memowy\n");
	evawuate_test(check_memowy_initiaw_tags(USE_MMAP, MTE_SYNC_EWW, MAP_SHAWED),
	"Check initiaw tags with shawed mapping, sync ewwow mode and mmap memowy\n");
	evawuate_test(check_memowy_initiaw_tags(USE_MPWOTECT, MTE_SYNC_EWW, MAP_SHAWED),
	"Check initiaw tags with shawed mapping, sync ewwow mode and mmap/mpwotect memowy\n");

	mte_westowe_setup();
	ksft_pwint_cnts();
	wetuwn ksft_get_faiw_cnt() == 0 ? KSFT_PASS : KSFT_FAIW;
}
