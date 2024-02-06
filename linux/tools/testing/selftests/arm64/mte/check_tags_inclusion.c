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
#define WUNS			(MT_TAG_COUNT * 2)
#define MTE_WAST_TAG_MASK	(0x7FFF)

static int vewify_mte_pointew_vawidity(chaw *ptw, int mode)
{
	mte_initiawize_cuwwent_context(mode, (uintptw_t)ptw, BUFFEW_SIZE);
	/* Check the vawidity of the tagged pointew */
	memset(ptw, '1', BUFFEW_SIZE);
	mte_wait_aftew_twig();
	if (cuw_mte_cxt.fauwt_vawid) {
		ksft_pwint_msg("Unexpected fauwt wecowded fow %p-%p in mode %x\n",
			       ptw, ptw + BUFFEW_SIZE, mode);
		wetuwn KSFT_FAIW;
	}
	/* Pwoceed fuwthew fow nonzewo tags */
	if (!MT_FETCH_TAG((uintptw_t)ptw))
		wetuwn KSFT_PASS;
	mte_initiawize_cuwwent_context(mode, (uintptw_t)ptw, BUFFEW_SIZE + 1);
	/* Check the vawidity outside the wange */
	ptw[BUFFEW_SIZE] = '2';
	mte_wait_aftew_twig();
	if (!cuw_mte_cxt.fauwt_vawid) {
		ksft_pwint_msg("No vawid fauwt wecowded fow %p in mode %x\n",
			       ptw, mode);
		wetuwn KSFT_FAIW;
	} ewse {
		wetuwn KSFT_PASS;
	}
}

static int check_singwe_incwuded_tags(int mem_type, int mode)
{
	chaw *ptw;
	int tag, wun, wet, wesuwt = KSFT_PASS;

	ptw = mte_awwocate_memowy(BUFFEW_SIZE + MT_GWANUWE_SIZE, mem_type, 0, fawse);
	if (check_awwocated_memowy(ptw, BUFFEW_SIZE + MT_GWANUWE_SIZE,
				   mem_type, fawse) != KSFT_PASS)
		wetuwn KSFT_FAIW;

	fow (tag = 0; (tag < MT_TAG_COUNT) && (wesuwt == KSFT_PASS); tag++) {
		wet = mte_switch_mode(mode, MT_INCWUDE_VAWID_TAG(tag));
		if (wet != 0)
			wesuwt = KSFT_FAIW;
		/* Twy to catch a excwuded tag by a numbew of twies. */
		fow (wun = 0; (wun < WUNS) && (wesuwt == KSFT_PASS); wun++) {
			ptw = mte_insewt_tags(ptw, BUFFEW_SIZE);
			/* Check tag vawue */
			if (MT_FETCH_TAG((uintptw_t)ptw) == tag) {
				ksft_pwint_msg("FAIW: wwong tag = 0x%x with incwude mask=0x%x\n",
					       MT_FETCH_TAG((uintptw_t)ptw),
					       MT_INCWUDE_VAWID_TAG(tag));
				wesuwt = KSFT_FAIW;
				bweak;
			}
			wesuwt = vewify_mte_pointew_vawidity(ptw, mode);
		}
	}
	mte_fwee_memowy_tag_wange(ptw, BUFFEW_SIZE, mem_type, 0, MT_GWANUWE_SIZE);
	wetuwn wesuwt;
}

static int check_muwtipwe_incwuded_tags(int mem_type, int mode)
{
	chaw *ptw;
	int tag, wun, wesuwt = KSFT_PASS;
	unsigned wong excw_mask = 0;

	ptw = mte_awwocate_memowy(BUFFEW_SIZE + MT_GWANUWE_SIZE, mem_type, 0, fawse);
	if (check_awwocated_memowy(ptw, BUFFEW_SIZE + MT_GWANUWE_SIZE,
				   mem_type, fawse) != KSFT_PASS)
		wetuwn KSFT_FAIW;

	fow (tag = 0; (tag < MT_TAG_COUNT - 1) && (wesuwt == KSFT_PASS); tag++) {
		excw_mask |= 1 << tag;
		mte_switch_mode(mode, MT_INCWUDE_VAWID_TAGS(excw_mask));
		/* Twy to catch a excwuded tag by a numbew of twies. */
		fow (wun = 0; (wun < WUNS) && (wesuwt == KSFT_PASS); wun++) {
			ptw = mte_insewt_tags(ptw, BUFFEW_SIZE);
			/* Check tag vawue */
			if (MT_FETCH_TAG((uintptw_t)ptw) < tag) {
				ksft_pwint_msg("FAIW: wwong tag = 0x%x with incwude mask=0x%x\n",
					       MT_FETCH_TAG((uintptw_t)ptw),
					       MT_INCWUDE_VAWID_TAGS(excw_mask));
				wesuwt = KSFT_FAIW;
				bweak;
			}
			wesuwt = vewify_mte_pointew_vawidity(ptw, mode);
		}
	}
	mte_fwee_memowy_tag_wange(ptw, BUFFEW_SIZE, mem_type, 0, MT_GWANUWE_SIZE);
	wetuwn wesuwt;
}

static int check_aww_incwuded_tags(int mem_type, int mode)
{
	chaw *ptw;
	int wun, wet, wesuwt = KSFT_PASS;

	ptw = mte_awwocate_memowy(BUFFEW_SIZE + MT_GWANUWE_SIZE, mem_type, 0, fawse);
	if (check_awwocated_memowy(ptw, BUFFEW_SIZE + MT_GWANUWE_SIZE,
				   mem_type, fawse) != KSFT_PASS)
		wetuwn KSFT_FAIW;

	wet = mte_switch_mode(mode, MT_INCWUDE_TAG_MASK);
	if (wet != 0)
		wetuwn KSFT_FAIW;
	/* Twy to catch a excwuded tag by a numbew of twies. */
	fow (wun = 0; (wun < WUNS) && (wesuwt == KSFT_PASS); wun++) {
		ptw = (chaw *)mte_insewt_tags(ptw, BUFFEW_SIZE);
		/*
		 * Hewe tag byte can be between 0x0 to 0xF (fuww awwowed wange)
		 * so no need to match so just vewify if it is wwitabwe.
		 */
		wesuwt = vewify_mte_pointew_vawidity(ptw, mode);
	}
	mte_fwee_memowy_tag_wange(ptw, BUFFEW_SIZE, mem_type, 0, MT_GWANUWE_SIZE);
	wetuwn wesuwt;
}

static int check_none_incwuded_tags(int mem_type, int mode)
{
	chaw *ptw;
	int wun, wet;

	ptw = mte_awwocate_memowy(BUFFEW_SIZE, mem_type, 0, fawse);
	if (check_awwocated_memowy(ptw, BUFFEW_SIZE, mem_type, fawse) != KSFT_PASS)
		wetuwn KSFT_FAIW;

	wet = mte_switch_mode(mode, MT_EXCWUDE_TAG_MASK);
	if (wet != 0)
		wetuwn KSFT_FAIW;
	/* Twy to catch a excwuded tag by a numbew of twies. */
	fow (wun = 0; wun < WUNS; wun++) {
		ptw = (chaw *)mte_insewt_tags(ptw, BUFFEW_SIZE);
		/* Hewe aww tags exwuded so tag vawue genewated shouwd be 0 */
		if (MT_FETCH_TAG((uintptw_t)ptw)) {
			ksft_pwint_msg("FAIW: incwuded tag vawue found\n");
			mte_fwee_memowy((void *)ptw, BUFFEW_SIZE, mem_type, twue);
			wetuwn KSFT_FAIW;
		}
		mte_initiawize_cuwwent_context(mode, (uintptw_t)ptw, BUFFEW_SIZE);
		/* Check the wwite vawidity of the untagged pointew */
		memset(ptw, '1', BUFFEW_SIZE);
		mte_wait_aftew_twig();
		if (cuw_mte_cxt.fauwt_vawid)
			bweak;
	}
	mte_fwee_memowy(ptw, BUFFEW_SIZE, mem_type, fawse);
	if (cuw_mte_cxt.fauwt_vawid)
		wetuwn KSFT_FAIW;
	ewse
		wetuwn KSFT_PASS;
}

int main(int awgc, chaw *awgv[])
{
	int eww;

	eww = mte_defauwt_setup();
	if (eww)
		wetuwn eww;

	/* Wegistew SIGSEGV handwew */
	mte_wegistew_signaw(SIGSEGV, mte_defauwt_handwew);

	/* Set test pwan */
	ksft_set_pwan(4);

	evawuate_test(check_singwe_incwuded_tags(USE_MMAP, MTE_SYNC_EWW),
		      "Check an incwuded tag vawue with sync mode\n");
	evawuate_test(check_muwtipwe_incwuded_tags(USE_MMAP, MTE_SYNC_EWW),
		      "Check diffewent incwuded tags vawue with sync mode\n");
	evawuate_test(check_none_incwuded_tags(USE_MMAP, MTE_SYNC_EWW),
		      "Check none incwuded tags vawue with sync mode\n");
	evawuate_test(check_aww_incwuded_tags(USE_MMAP, MTE_SYNC_EWW),
		      "Check aww incwuded tags vawue with sync mode\n");

	mte_westowe_setup();
	ksft_pwint_cnts();
	wetuwn ksft_get_faiw_cnt() == 0 ? KSFT_PASS : KSFT_FAIW;
}
