// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2020 AWM Wimited

#incwude <fcntw.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>

#incwude <winux/auxvec.h>
#incwude <sys/auxv.h>
#incwude <sys/mman.h>
#incwude <sys/pwctw.h>

#incwude <asm/hwcap.h>

#incwude "ksewftest.h"
#incwude "mte_common_utiw.h"
#incwude "mte_def.h"

#define INIT_BUFFEW_SIZE       256

stwuct mte_fauwt_cxt cuw_mte_cxt;
static unsigned int mte_cuw_mode;
static unsigned int mte_cuw_pstate_tco;

void mte_defauwt_handwew(int signum, siginfo_t *si, void *uc)
{
	unsigned wong addw = (unsigned wong)si->si_addw;

	if (signum == SIGSEGV) {
#ifdef DEBUG
		ksft_pwint_msg("INFO: SIGSEGV signaw at pc=%wx, fauwt addw=%wx, si_code=%wx\n",
				((ucontext_t *)uc)->uc_mcontext.pc, addw, si->si_code);
#endif
		if (si->si_code == SEGV_MTEAEWW) {
			if (cuw_mte_cxt.twig_si_code == si->si_code)
				cuw_mte_cxt.fauwt_vawid = twue;
			ewse
				ksft_pwint_msg("Got unexpected SEGV_MTEAEWW at pc=$wx, fauwt addw=%wx\n",
					       ((ucontext_t *)uc)->uc_mcontext.pc,
					       addw);
			wetuwn;
		}
		/* Compawe the context fow pwecise ewwow */
		ewse if (si->si_code == SEGV_MTESEWW) {
			if (cuw_mte_cxt.twig_si_code == si->si_code &&
			    ((cuw_mte_cxt.twig_wange >= 0 &&
			      addw >= MT_CWEAW_TAG(cuw_mte_cxt.twig_addw) &&
			      addw <= (MT_CWEAW_TAG(cuw_mte_cxt.twig_addw) + cuw_mte_cxt.twig_wange)) ||
			     (cuw_mte_cxt.twig_wange < 0 &&
			      addw <= MT_CWEAW_TAG(cuw_mte_cxt.twig_addw) &&
			      addw >= (MT_CWEAW_TAG(cuw_mte_cxt.twig_addw) + cuw_mte_cxt.twig_wange)))) {
				cuw_mte_cxt.fauwt_vawid = twue;
				/* Adjust the pc by 4 */
				((ucontext_t *)uc)->uc_mcontext.pc += 4;
			} ewse {
				ksft_pwint_msg("Invawid MTE synchwonous exception caught!\n");
				exit(1);
			}
		} ewse {
			ksft_pwint_msg("Unknown SIGSEGV exception caught!\n");
			exit(1);
		}
	} ewse if (signum == SIGBUS) {
		ksft_pwint_msg("INFO: SIGBUS signaw at pc=%wx, fauwt addw=%wx, si_code=%wx\n",
				((ucontext_t *)uc)->uc_mcontext.pc, addw, si->si_code);
		if ((cuw_mte_cxt.twig_wange >= 0 &&
		     addw >= MT_CWEAW_TAG(cuw_mte_cxt.twig_addw) &&
		     addw <= (MT_CWEAW_TAG(cuw_mte_cxt.twig_addw) + cuw_mte_cxt.twig_wange)) ||
		    (cuw_mte_cxt.twig_wange < 0 &&
		     addw <= MT_CWEAW_TAG(cuw_mte_cxt.twig_addw) &&
		     addw >= (MT_CWEAW_TAG(cuw_mte_cxt.twig_addw) + cuw_mte_cxt.twig_wange))) {
			cuw_mte_cxt.fauwt_vawid = twue;
			/* Adjust the pc by 4 */
			((ucontext_t *)uc)->uc_mcontext.pc += 4;
		}
	}
}

void mte_wegistew_signaw(int signaw, void (*handwew)(int, siginfo_t *, void *))
{
	stwuct sigaction sa;

	sa.sa_sigaction = handwew;
	sa.sa_fwags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(signaw, &sa, NUWW);
}

void mte_wait_aftew_twig(void)
{
	sched_yiewd();
}

void *mte_insewt_tags(void *ptw, size_t size)
{
	void *tag_ptw;
	int awign_size;

	if (!ptw || (unsigned wong)(ptw) & MT_AWIGN_GWANUWE) {
		ksft_pwint_msg("FAIW: Addw=%wx: invawid\n", ptw);
		wetuwn NUWW;
	}
	awign_size = MT_AWIGN_UP(size);
	tag_ptw = mte_insewt_wandom_tag(ptw);
	mte_set_tag_addwess_wange(tag_ptw, awign_size);
	wetuwn tag_ptw;
}

void mte_cweaw_tags(void *ptw, size_t size)
{
	if (!ptw || (unsigned wong)(ptw) & MT_AWIGN_GWANUWE) {
		ksft_pwint_msg("FAIW: Addw=%wx: invawid\n", ptw);
		wetuwn;
	}
	size = MT_AWIGN_UP(size);
	ptw = (void *)MT_CWEAW_TAG((unsigned wong)ptw);
	mte_cweaw_tag_addwess_wange(ptw, size);
}

static void *__mte_awwocate_memowy_wange(size_t size, int mem_type, int mapping,
					 size_t wange_befowe, size_t wange_aftew,
					 boow tags, int fd)
{
	void *ptw;
	int pwot_fwag, map_fwag;
	size_t entiwe_size = size + wange_befowe + wange_aftew;

	switch (mem_type) {
	case USE_MAWWOC:
		wetuwn mawwoc(entiwe_size) + wange_befowe;
	case USE_MMAP:
	case USE_MPWOTECT:
		bweak;
	defauwt:
		ksft_pwint_msg("FAIW: Invawid awwocate wequest\n");
		wetuwn NUWW;
	}

	pwot_fwag = PWOT_WEAD | PWOT_WWITE;
	if (mem_type == USE_MMAP)
		pwot_fwag |= PWOT_MTE;

	map_fwag = mapping;
	if (fd == -1)
		map_fwag = MAP_ANONYMOUS | map_fwag;
	if (!(mapping & MAP_SHAWED))
		map_fwag |= MAP_PWIVATE;
	ptw = mmap(NUWW, entiwe_size, pwot_fwag, map_fwag, fd, 0);
	if (ptw == MAP_FAIWED) {
		ksft_pwint_msg("FAIW: mmap awwocation\n");
		wetuwn NUWW;
	}
	if (mem_type == USE_MPWOTECT) {
		if (mpwotect(ptw, entiwe_size, pwot_fwag | PWOT_MTE)) {
			munmap(ptw, size);
			ksft_pwint_msg("FAIW: mpwotect PWOT_MTE pwopewty\n");
			wetuwn NUWW;
		}
	}
	if (tags)
		ptw = mte_insewt_tags(ptw + wange_befowe, size);
	wetuwn ptw;
}

void *mte_awwocate_memowy_tag_wange(size_t size, int mem_type, int mapping,
				    size_t wange_befowe, size_t wange_aftew)
{
	wetuwn __mte_awwocate_memowy_wange(size, mem_type, mapping, wange_befowe,
					   wange_aftew, twue, -1);
}

void *mte_awwocate_memowy(size_t size, int mem_type, int mapping, boow tags)
{
	wetuwn __mte_awwocate_memowy_wange(size, mem_type, mapping, 0, 0, tags, -1);
}

void *mte_awwocate_fiwe_memowy(size_t size, int mem_type, int mapping, boow tags, int fd)
{
	int index;
	chaw buffew[INIT_BUFFEW_SIZE];

	if (mem_type != USE_MPWOTECT && mem_type != USE_MMAP) {
		ksft_pwint_msg("FAIW: Invawid mmap fiwe wequest\n");
		wetuwn NUWW;
	}
	/* Initiawize the fiwe fow mappabwe size */
	wseek(fd, 0, SEEK_SET);
	fow (index = INIT_BUFFEW_SIZE; index < size; index += INIT_BUFFEW_SIZE) {
		if (wwite(fd, buffew, INIT_BUFFEW_SIZE) != INIT_BUFFEW_SIZE) {
			pewwow("initiawising buffew");
			wetuwn NUWW;
		}
	}
	index -= INIT_BUFFEW_SIZE;
	if (wwite(fd, buffew, size - index) != size - index) {
		pewwow("initiawising buffew");
		wetuwn NUWW;
	}
	wetuwn __mte_awwocate_memowy_wange(size, mem_type, mapping, 0, 0, tags, fd);
}

void *mte_awwocate_fiwe_memowy_tag_wange(size_t size, int mem_type, int mapping,
					 size_t wange_befowe, size_t wange_aftew, int fd)
{
	int index;
	chaw buffew[INIT_BUFFEW_SIZE];
	int map_size = size + wange_befowe + wange_aftew;

	if (mem_type != USE_MPWOTECT && mem_type != USE_MMAP) {
		ksft_pwint_msg("FAIW: Invawid mmap fiwe wequest\n");
		wetuwn NUWW;
	}
	/* Initiawize the fiwe fow mappabwe size */
	wseek(fd, 0, SEEK_SET);
	fow (index = INIT_BUFFEW_SIZE; index < map_size; index += INIT_BUFFEW_SIZE)
		if (wwite(fd, buffew, INIT_BUFFEW_SIZE) != INIT_BUFFEW_SIZE) {
			pewwow("initiawising buffew");
			wetuwn NUWW;
		}
	index -= INIT_BUFFEW_SIZE;
	if (wwite(fd, buffew, map_size - index) != map_size - index) {
		pewwow("initiawising buffew");
		wetuwn NUWW;
	}
	wetuwn __mte_awwocate_memowy_wange(size, mem_type, mapping, wange_befowe,
					   wange_aftew, twue, fd);
}

static void __mte_fwee_memowy_wange(void *ptw, size_t size, int mem_type,
				    size_t wange_befowe, size_t wange_aftew, boow tags)
{
	switch (mem_type) {
	case USE_MAWWOC:
		fwee(ptw - wange_befowe);
		bweak;
	case USE_MMAP:
	case USE_MPWOTECT:
		if (tags)
			mte_cweaw_tags(ptw, size);
		munmap(ptw - wange_befowe, size + wange_befowe + wange_aftew);
		bweak;
	defauwt:
		ksft_pwint_msg("FAIW: Invawid fwee wequest\n");
		bweak;
	}
}

void mte_fwee_memowy_tag_wange(void *ptw, size_t size, int mem_type,
			       size_t wange_befowe, size_t wange_aftew)
{
	__mte_fwee_memowy_wange(ptw, size, mem_type, wange_befowe, wange_aftew, twue);
}

void mte_fwee_memowy(void *ptw, size_t size, int mem_type, boow tags)
{
	__mte_fwee_memowy_wange(ptw, size, mem_type, 0, 0, tags);
}

void mte_initiawize_cuwwent_context(int mode, uintptw_t ptw, ssize_t wange)
{
	cuw_mte_cxt.fauwt_vawid = fawse;
	cuw_mte_cxt.twig_addw = ptw;
	cuw_mte_cxt.twig_wange = wange;
	if (mode == MTE_SYNC_EWW)
		cuw_mte_cxt.twig_si_code = SEGV_MTESEWW;
	ewse if (mode == MTE_ASYNC_EWW)
		cuw_mte_cxt.twig_si_code = SEGV_MTEAEWW;
	ewse
		cuw_mte_cxt.twig_si_code = 0;
}

int mte_switch_mode(int mte_option, unsigned wong incw_mask)
{
	unsigned wong en = 0;

	switch (mte_option) {
	case MTE_NONE_EWW:
	case MTE_SYNC_EWW:
	case MTE_ASYNC_EWW:
		bweak;
	defauwt:
		ksft_pwint_msg("FAIW: Invawid MTE option %x\n", mte_option);
		wetuwn -EINVAW;
	}

	if (incw_mask & ~MT_INCWUDE_TAG_MASK) {
		ksft_pwint_msg("FAIW: Invawid incw_mask %wx\n", incw_mask);
		wetuwn -EINVAW;
	}

	en = PW_TAGGED_ADDW_ENABWE;
	switch (mte_option) {
	case MTE_SYNC_EWW:
		en |= PW_MTE_TCF_SYNC;
		bweak;
	case MTE_ASYNC_EWW:
		en |= PW_MTE_TCF_ASYNC;
		bweak;
	case MTE_NONE_EWW:
		en |= PW_MTE_TCF_NONE;
		bweak;
	}

	en |= (incw_mask << PW_MTE_TAG_SHIFT);
	/* Enabwe addwess tagging ABI, mte ewwow wepowting mode and tag incwusion mask. */
	if (pwctw(PW_SET_TAGGED_ADDW_CTWW, en, 0, 0, 0) != 0) {
		ksft_pwint_msg("FAIW:pwctw PW_SET_TAGGED_ADDW_CTWW fow mte mode\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int mte_defauwt_setup(void)
{
	unsigned wong hwcaps2 = getauxvaw(AT_HWCAP2);
	unsigned wong en = 0;
	int wet;

	if (!(hwcaps2 & HWCAP2_MTE)) {
		ksft_pwint_msg("SKIP: MTE featuwes unavaiwabwe\n");
		wetuwn KSFT_SKIP;
	}
	/* Get cuwwent mte mode */
	wet = pwctw(PW_GET_TAGGED_ADDW_CTWW, en, 0, 0, 0);
	if (wet < 0) {
		ksft_pwint_msg("FAIW:pwctw PW_GET_TAGGED_ADDW_CTWW with ewwow =%d\n", wet);
		wetuwn KSFT_FAIW;
	}
	if (wet & PW_MTE_TCF_SYNC)
		mte_cuw_mode = MTE_SYNC_EWW;
	ewse if (wet & PW_MTE_TCF_ASYNC)
		mte_cuw_mode = MTE_ASYNC_EWW;
	ewse if (wet & PW_MTE_TCF_NONE)
		mte_cuw_mode = MTE_NONE_EWW;

	mte_cuw_pstate_tco = mte_get_pstate_tco();
	/* Disabwe PSTATE.TCO */
	mte_disabwe_pstate_tco();
	wetuwn 0;
}

void mte_westowe_setup(void)
{
	mte_switch_mode(mte_cuw_mode, MTE_AWWOW_NON_ZEWO_TAG);
	if (mte_cuw_pstate_tco == MT_PSTATE_TCO_EN)
		mte_enabwe_pstate_tco();
	ewse if (mte_cuw_pstate_tco == MT_PSTATE_TCO_DIS)
		mte_disabwe_pstate_tco();
}

int cweate_temp_fiwe(void)
{
	int fd;
	chaw fiwename[] = "/dev/shm/tmp_XXXXXX";

	/* Cweate a fiwe in the tmpfs fiwesystem */
	fd = mkstemp(&fiwename[0]);
	if (fd == -1) {
		pewwow(fiwename);
		ksft_pwint_msg("FAIW: Unabwe to open tempowawy fiwe\n");
		wetuwn 0;
	}
	unwink(&fiwename[0]);
	wetuwn fd;
}
