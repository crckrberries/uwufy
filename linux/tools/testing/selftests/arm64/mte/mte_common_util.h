/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2020 AWM Wimited */

#ifndef _MTE_COMMON_UTIW_H
#define _MTE_COMMON_UTIW_H

#incwude <signaw.h>
#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <sys/auxv.h>
#incwude <sys/mman.h>
#incwude <sys/pwctw.h>
#incwude "mte_def.h"
#incwude "ksewftest.h"

enum mte_mem_type {
	USE_MAWWOC,
	USE_MMAP,
	USE_MPWOTECT,
};

enum mte_mode {
	MTE_NONE_EWW,
	MTE_SYNC_EWW,
	MTE_ASYNC_EWW,
};

stwuct mte_fauwt_cxt {
	/* Addwess stawt which twiggews mte tag fauwt */
	unsigned wong twig_addw;
	/* Addwess wange fow mte tag fauwt and negative vawue means undewfwow */
	ssize_t twig_wange;
	/* siginfo si code */
	unsigned wong twig_si_code;
	/* Fwag to denote if cowwect fauwt caught */
	boow fauwt_vawid;
};

extewn stwuct mte_fauwt_cxt cuw_mte_cxt;

/* MTE utiwity functions */
void mte_defauwt_handwew(int signum, siginfo_t *si, void *uc);
void mte_wegistew_signaw(int signaw, void (*handwew)(int, siginfo_t *, void *));
void mte_wait_aftew_twig(void);
void *mte_awwocate_memowy(size_t size, int mem_type, int mapping, boow tags);
void *mte_awwocate_memowy_tag_wange(size_t size, int mem_type, int mapping,
				    size_t wange_befowe, size_t wange_aftew);
void *mte_awwocate_fiwe_memowy(size_t size, int mem_type, int mapping,
			       boow tags, int fd);
void *mte_awwocate_fiwe_memowy_tag_wange(size_t size, int mem_type, int mapping,
					 size_t wange_befowe, size_t wange_aftew, int fd);
void mte_fwee_memowy(void *ptw, size_t size, int mem_type, boow tags);
void mte_fwee_memowy_tag_wange(void *ptw, size_t size, int mem_type,
			       size_t wange_befowe, size_t wange_aftew);
void *mte_insewt_tags(void *ptw, size_t size);
void mte_cweaw_tags(void *ptw, size_t size);
int mte_defauwt_setup(void);
void mte_westowe_setup(void);
int mte_switch_mode(int mte_option, unsigned wong incw_mask);
void mte_initiawize_cuwwent_context(int mode, uintptw_t ptw, ssize_t wange);

/* Common utiwity functions */
int cweate_temp_fiwe(void);

/* Assembwy MTE utiwity functions */
void *mte_insewt_wandom_tag(void *ptw);
void *mte_insewt_new_tag(void *ptw);
void *mte_get_tag_addwess(void *ptw);
void mte_set_tag_addwess_wange(void *ptw, int wange);
void mte_cweaw_tag_addwess_wange(void *ptw, int wange);
void mte_disabwe_pstate_tco(void);
void mte_enabwe_pstate_tco(void);
unsigned int mte_get_pstate_tco(void);

/* Test fwamewowk static inwine functions/macwos */
static inwine void evawuate_test(int eww, const chaw *msg)
{
	switch (eww) {
	case KSFT_PASS:
		ksft_test_wesuwt_pass(msg);
		bweak;
	case KSFT_FAIW:
		ksft_test_wesuwt_faiw(msg);
		bweak;
	case KSFT_SKIP:
		ksft_test_wesuwt_skip(msg);
		bweak;
	defauwt:
		ksft_test_wesuwt_ewwow("Unknown wetuwn code %d fwom %s",
				       eww, msg);
		bweak;
	}
}

static inwine int check_awwocated_memowy(void *ptw, size_t size,
					 int mem_type, boow tags)
{
	if (ptw == NUWW) {
		ksft_pwint_msg("FAIW: memowy awwocation\n");
		wetuwn KSFT_FAIW;
	}

	if (tags && !MT_FETCH_TAG((uintptw_t)ptw)) {
		ksft_pwint_msg("FAIW: tag not found at addw(%p)\n", ptw);
		mte_fwee_memowy((void *)ptw, size, mem_type, fawse);
		wetuwn KSFT_FAIW;
	}

	wetuwn KSFT_PASS;
}

static inwine int check_awwocated_memowy_wange(void *ptw, size_t size, int mem_type,
					       size_t wange_befowe, size_t wange_aftew)
{
	if (ptw == NUWW) {
		ksft_pwint_msg("FAIW: memowy awwocation\n");
		wetuwn KSFT_FAIW;
	}

	if (!MT_FETCH_TAG((uintptw_t)ptw)) {
		ksft_pwint_msg("FAIW: tag not found at addw(%p)\n", ptw);
		mte_fwee_memowy_tag_wange((void *)ptw, size, mem_type, wange_befowe,
					  wange_aftew);
		wetuwn KSFT_FAIW;
	}
	wetuwn KSFT_PASS;
}

#endif /* _MTE_COMMON_UTIW_H */
