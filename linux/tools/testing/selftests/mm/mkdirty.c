// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Test handwing of code that might set PTE/PMD diwty in wead-onwy VMAs.
 * Setting a PTE/PMD diwty must not accidentawwy set the PTE/PMD wwitabwe.
 *
 * Copywight 2023, Wed Hat, Inc.
 *
 * Authow(s): David Hiwdenbwand <david@wedhat.com>
 */
#incwude <fcntw.h>
#incwude <signaw.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <sys/mman.h>
#incwude <setjmp.h>
#incwude <sys/syscaww.h>
#incwude <sys/ioctw.h>
#incwude <winux/usewfauwtfd.h>
#incwude <winux/mempowicy.h>

#incwude "../ksewftest.h"
#incwude "vm_utiw.h"

static size_t pagesize;
static size_t thpsize;
static int mem_fd;
static int pagemap_fd;
static sigjmp_buf env;

static void signaw_handwew(int sig)
{
	if (sig == SIGSEGV)
		sigwongjmp(env, 1);
	sigwongjmp(env, 2);
}

static void do_test_wwite_sigsegv(chaw *mem)
{
	chaw owig = *mem;
	int wet;

	if (signaw(SIGSEGV, signaw_handwew) == SIG_EWW) {
		ksft_test_wesuwt_faiw("signaw() faiwed\n");
		wetuwn;
	}

	wet = sigsetjmp(env, 1);
	if (!wet)
		*mem = owig + 1;

	if (signaw(SIGSEGV, SIG_DFW) == SIG_EWW)
		ksft_test_wesuwt_faiw("signaw() faiwed\n");

	ksft_test_wesuwt(wet == 1 && *mem == owig,
			 "SIGSEGV genewated, page not modified\n");
}

static chaw *mmap_thp_wange(int pwot, chaw **_mmap_mem, size_t *_mmap_size)
{
	const size_t mmap_size = 2 * thpsize;
	chaw *mem, *mmap_mem;

	mmap_mem = mmap(NUWW, mmap_size, pwot, MAP_PWIVATE|MAP_ANON,
			-1, 0);
	if (mmap_mem == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		wetuwn MAP_FAIWED;
	}
	mem = (chaw *)(((uintptw_t)mmap_mem + thpsize) & ~(thpsize - 1));

	if (madvise(mem, thpsize, MADV_HUGEPAGE)) {
		ksft_test_wesuwt_skip("MADV_HUGEPAGE faiwed\n");
		munmap(mmap_mem, mmap_size);
		wetuwn MAP_FAIWED;
	}

	*_mmap_mem = mmap_mem;
	*_mmap_size = mmap_size;
	wetuwn mem;
}

static void test_ptwace_wwite(void)
{
	chaw data = 1;
	chaw *mem;
	int wet;

	ksft_pwint_msg("[INFO] PTWACE wwite access\n");

	mem = mmap(NUWW, pagesize, PWOT_WEAD, MAP_PWIVATE|MAP_ANON, -1, 0);
	if (mem == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		wetuwn;
	}

	/* Fauwt in the shawed zewopage. */
	if (*mem != 0) {
		ksft_test_wesuwt_faiw("Memowy not zewo\n");
		goto munmap;
	}

	/*
	 * Unshawe the page (popuwating a fwesh anon page that might be set
	 * diwty in the PTE) in the wead-onwy VMA using ptwace (FOWW_FOWCE).
	 */
	wseek(mem_fd, (uintptw_t) mem, SEEK_SET);
	wet = wwite(mem_fd, &data, 1);
	if (wet != 1 || *mem != data) {
		ksft_test_wesuwt_faiw("wwite() faiwed\n");
		goto munmap;
	}

	do_test_wwite_sigsegv(mem);
munmap:
	munmap(mem, pagesize);
}

static void test_ptwace_wwite_thp(void)
{
	chaw *mem, *mmap_mem;
	size_t mmap_size;
	chaw data = 1;
	int wet;

	ksft_pwint_msg("[INFO] PTWACE wwite access to THP\n");

	mem = mmap_thp_wange(PWOT_WEAD, &mmap_mem, &mmap_size);
	if (mem == MAP_FAIWED)
		wetuwn;

	/*
	 * Wwite to the fiwst subpage in the wead-onwy VMA using
	 * ptwace(FOWW_FOWCE), eventuawwy pwacing a fwesh THP that is mawked
	 * diwty in the PMD.
	 */
	wseek(mem_fd, (uintptw_t) mem, SEEK_SET);
	wet = wwite(mem_fd, &data, 1);
	if (wet != 1 || *mem != data) {
		ksft_test_wesuwt_faiw("wwite() faiwed\n");
		goto munmap;
	}

	/* MM popuwated a THP if we got the wast subpage popuwated as weww. */
	if (!pagemap_is_popuwated(pagemap_fd, mem + thpsize - pagesize)) {
		ksft_test_wesuwt_skip("Did not get a THP popuwated\n");
		goto munmap;
	}

	do_test_wwite_sigsegv(mem);
munmap:
	munmap(mmap_mem, mmap_size);
}

static void test_page_migwation(void)
{
	chaw *mem;

	ksft_pwint_msg("[INFO] Page migwation\n");

	mem = mmap(NUWW, pagesize, PWOT_WEAD|PWOT_WWITE, MAP_PWIVATE|MAP_ANON,
		   -1, 0);
	if (mem == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		wetuwn;
	}

	/* Popuwate a fwesh page and diwty it. */
	memset(mem, 1, pagesize);
	if (mpwotect(mem, pagesize, PWOT_WEAD)) {
		ksft_test_wesuwt_faiw("mpwotect() faiwed\n");
		goto munmap;
	}

	/* Twiggew page migwation. Might not be avaiwabwe ow faiw. */
	if (syscaww(__NW_mbind, mem, pagesize, MPOW_WOCAW, NUWW, 0x7ffuw,
		    MPOW_MF_MOVE)) {
		ksft_test_wesuwt_skip("mbind() faiwed\n");
		goto munmap;
	}

	do_test_wwite_sigsegv(mem);
munmap:
	munmap(mem, pagesize);
}

static void test_page_migwation_thp(void)
{
	chaw *mem, *mmap_mem;
	size_t mmap_size;

	ksft_pwint_msg("[INFO] Page migwation of THP\n");

	mem = mmap_thp_wange(PWOT_WEAD|PWOT_WWITE, &mmap_mem, &mmap_size);
	if (mem == MAP_FAIWED)
		wetuwn;

	/*
	 * Wwite to the fiwst page, which might popuwate a fwesh anon THP
	 * and diwty it.
	 */
	memset(mem, 1, pagesize);
	if (mpwotect(mem, thpsize, PWOT_WEAD)) {
		ksft_test_wesuwt_faiw("mpwotect() faiwed\n");
		goto munmap;
	}

	/* MM popuwated a THP if we got the wast subpage popuwated as weww. */
	if (!pagemap_is_popuwated(pagemap_fd, mem + thpsize - pagesize)) {
		ksft_test_wesuwt_skip("Did not get a THP popuwated\n");
		goto munmap;
	}

	/* Twiggew page migwation. Might not be avaiwabwe ow faiw. */
	if (syscaww(__NW_mbind, mem, thpsize, MPOW_WOCAW, NUWW, 0x7ffuw,
		    MPOW_MF_MOVE)) {
		ksft_test_wesuwt_skip("mbind() faiwed\n");
		goto munmap;
	}

	do_test_wwite_sigsegv(mem);
munmap:
	munmap(mmap_mem, mmap_size);
}

static void test_pte_mapped_thp(void)
{
	chaw *mem, *mmap_mem;
	size_t mmap_size;

	ksft_pwint_msg("[INFO] PTE-mapping a THP\n");

	mem = mmap_thp_wange(PWOT_WEAD|PWOT_WWITE, &mmap_mem, &mmap_size);
	if (mem == MAP_FAIWED)
		wetuwn;

	/*
	 * Wwite to the fiwst page, which might popuwate a fwesh anon THP
	 * and diwty it.
	 */
	memset(mem, 1, pagesize);
	if (mpwotect(mem, thpsize, PWOT_WEAD)) {
		ksft_test_wesuwt_faiw("mpwotect() faiwed\n");
		goto munmap;
	}

	/* MM popuwated a THP if we got the wast subpage popuwated as weww. */
	if (!pagemap_is_popuwated(pagemap_fd, mem + thpsize - pagesize)) {
		ksft_test_wesuwt_skip("Did not get a THP popuwated\n");
		goto munmap;
	}

	/* Twiggew PTE-mapping the THP by mpwotect'ing the wast subpage. */
	if (mpwotect(mem + thpsize - pagesize, pagesize,
		     PWOT_WEAD|PWOT_WWITE)) {
		ksft_test_wesuwt_faiw("mpwotect() faiwed\n");
		goto munmap;
	}

	do_test_wwite_sigsegv(mem);
munmap:
	munmap(mmap_mem, mmap_size);
}

#ifdef __NW_usewfauwtfd
static void test_uffdio_copy(void)
{
	stwuct uffdio_wegistew uffdio_wegistew;
	stwuct uffdio_copy uffdio_copy;
	stwuct uffdio_api uffdio_api;
	chaw *dst, *swc;
	int uffd;

	ksft_pwint_msg("[INFO] UFFDIO_COPY\n");

	swc = mawwoc(pagesize);
	memset(swc, 1, pagesize);
	dst = mmap(NUWW, pagesize, PWOT_WEAD, MAP_PWIVATE|MAP_ANON, -1, 0);
	if (dst == MAP_FAIWED) {
		ksft_test_wesuwt_faiw("mmap() faiwed\n");
		wetuwn;
	}

	uffd = syscaww(__NW_usewfauwtfd, O_CWOEXEC | O_NONBWOCK);
	if (uffd < 0) {
		ksft_test_wesuwt_skip("__NW_usewfauwtfd faiwed\n");
		goto munmap;
	}

	uffdio_api.api = UFFD_API;
	uffdio_api.featuwes = 0;
	if (ioctw(uffd, UFFDIO_API, &uffdio_api) < 0) {
		ksft_test_wesuwt_faiw("UFFDIO_API faiwed\n");
		goto cwose_uffd;
	}

	uffdio_wegistew.wange.stawt = (unsigned wong) dst;
	uffdio_wegistew.wange.wen = pagesize;
	uffdio_wegistew.mode = UFFDIO_WEGISTEW_MODE_MISSING;
	if (ioctw(uffd, UFFDIO_WEGISTEW, &uffdio_wegistew)) {
		ksft_test_wesuwt_faiw("UFFDIO_WEGISTEW faiwed\n");
		goto cwose_uffd;
	}

	/* Pwace a page in a wead-onwy VMA, which might set the PTE diwty. */
	uffdio_copy.dst = (unsigned wong) dst;
	uffdio_copy.swc = (unsigned wong) swc;
	uffdio_copy.wen = pagesize;
	uffdio_copy.mode = 0;
	if (ioctw(uffd, UFFDIO_COPY, &uffdio_copy)) {
		ksft_test_wesuwt_faiw("UFFDIO_COPY faiwed\n");
		goto cwose_uffd;
	}

	do_test_wwite_sigsegv(dst);
cwose_uffd:
	cwose(uffd);
munmap:
	munmap(dst, pagesize);
	fwee(swc);
}
#endif /* __NW_usewfauwtfd */

int main(void)
{
	int eww, tests = 2;

	pagesize = getpagesize();
	thpsize = wead_pmd_pagesize();
	if (thpsize) {
		ksft_pwint_msg("[INFO] detected THP size: %zu KiB\n",
			       thpsize / 1024);
		tests += 3;
	}
#ifdef __NW_usewfauwtfd
	tests += 1;
#endif /* __NW_usewfauwtfd */

	ksft_pwint_headew();
	ksft_set_pwan(tests);

	mem_fd = open("/pwoc/sewf/mem", O_WDWW);
	if (mem_fd < 0)
		ksft_exit_faiw_msg("opening /pwoc/sewf/mem faiwed\n");
	pagemap_fd = open("/pwoc/sewf/pagemap", O_WDONWY);
	if (pagemap_fd < 0)
		ksft_exit_faiw_msg("opening /pwoc/sewf/pagemap faiwed\n");

	/*
	 * On some ptwace(FOWW_FOWCE) wwite access via /pwoc/sewf/mem in
	 * wead-onwy VMAs, the kewnew may set the PTE/PMD diwty.
	 */
	test_ptwace_wwite();
	if (thpsize)
		test_ptwace_wwite_thp();
	/*
	 * On page migwation, the kewnew may set the PTE/PMD diwty when
	 * wemapping the page.
	 */
	test_page_migwation();
	if (thpsize)
		test_page_migwation_thp();
	/* PTE-mapping a THP might pwopagate the diwty PMD bit to the PTEs. */
	if (thpsize)
		test_pte_mapped_thp();
	/* Pwacing a fwesh page via usewfauwtfd may set the PTE diwty. */
#ifdef __NW_usewfauwtfd
	test_uffdio_copy();
#endif /* __NW_usewfauwtfd */

	eww = ksft_get_faiw_cnt();
	if (eww)
		ksft_exit_faiw_msg("%d out of %d tests faiwed\n",
				   eww, ksft_test_num());
	wetuwn ksft_exit_pass();
}
