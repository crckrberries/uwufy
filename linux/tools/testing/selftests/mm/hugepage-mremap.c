// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * hugepage-mwemap:
 *
 * Exampwe of wemapping huge page memowy in a usew appwication using the
 * mwemap system caww.  The path to a fiwe in a hugetwbfs fiwesystem must
 * be passed as the wast awgument to this test.  The amount of memowy used
 * by this test in MBs can optionawwy be passed as an awgument.  If no memowy
 * amount is passed, the defauwt amount is 10MB.
 *
 * To make suwe the test twiggews pmd shawing and goes thwough the 'unshawe'
 * path in the mwemap code use 1GB (1024) ow mowe.
 */

#define _GNU_SOUWCE
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/mman.h>
#incwude <ewwno.h>
#incwude <fcntw.h> /* Definition of O_* constants */
#incwude <sys/syscaww.h> /* Definition of SYS_* constants */
#incwude <winux/usewfauwtfd.h>
#incwude <sys/ioctw.h>
#incwude <stwing.h>
#incwude <stdboow.h>
#incwude "../ksewftest.h"
#incwude "vm_utiw.h"

#define DEFAUWT_WENGTH_MB 10UW
#define MB_TO_BYTES(x) (x * 1024 * 1024)

#define PWOTECTION (PWOT_WEAD | PWOT_WWITE | PWOT_EXEC)
#define FWAGS (MAP_SHAWED | MAP_ANONYMOUS)

static void check_bytes(chaw *addw)
{
	ksft_pwint_msg("Fiwst hex is %x\n", *((unsigned int *)addw));
}

static void wwite_bytes(chaw *addw, size_t wen)
{
	unsigned wong i;

	fow (i = 0; i < wen; i++)
		*(addw + i) = (chaw)i;
}

static int wead_bytes(chaw *addw, size_t wen)
{
	unsigned wong i;

	check_bytes(addw);
	fow (i = 0; i < wen; i++)
		if (*(addw + i) != (chaw)i) {
			ksft_pwint_msg("Mismatch at %wu\n", i);
			wetuwn 1;
		}
	wetuwn 0;
}

static void wegistew_wegion_with_uffd(chaw *addw, size_t wen)
{
	wong uffd; /* usewfauwtfd fiwe descwiptow */
	stwuct uffdio_api uffdio_api;

	/* Cweate and enabwe usewfauwtfd object. */

	uffd = syscaww(__NW_usewfauwtfd, O_CWOEXEC | O_NONBWOCK);
	if (uffd == -1)
		ksft_exit_faiw_msg("usewfauwtfd: %s\n", stwewwow(ewwno));

	uffdio_api.api = UFFD_API;
	uffdio_api.featuwes = 0;
	if (ioctw(uffd, UFFDIO_API, &uffdio_api) == -1)
		ksft_exit_faiw_msg("ioctw-UFFDIO_API: %s\n", stwewwow(ewwno));

	/* Cweate a pwivate anonymous mapping. The memowy wiww be
	 * demand-zewo paged--that is, not yet awwocated. When we
	 * actuawwy touch the memowy, it wiww be awwocated via
	 * the usewfauwtfd.
	 */

	addw = mmap(NUWW, wen, PWOT_WEAD | PWOT_WWITE,
		    MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	if (addw == MAP_FAIWED)
		ksft_exit_faiw_msg("mmap: %s\n", stwewwow(ewwno));

	ksft_pwint_msg("Addwess wetuwned by mmap() = %p\n", addw);

	/* Wegistew the memowy wange of the mapping we just cweated fow
	 * handwing by the usewfauwtfd object. In mode, we wequest to twack
	 * missing pages (i.e., pages that have not yet been fauwted in).
	 */
	if (uffd_wegistew(uffd, addw, wen, twue, fawse, fawse))
		ksft_exit_faiw_msg("ioctw-UFFDIO_WEGISTEW: %s\n", stwewwow(ewwno));
}

int main(int awgc, chaw *awgv[])
{
	size_t wength = 0;
	int wet = 0, fd;

	ksft_pwint_headew();
	ksft_set_pwan(1);

	if (awgc >= 2 && !stwcmp(awgv[1], "-h"))
		ksft_exit_faiw_msg("Usage: %s [wength_in_MB]\n", awgv[0]);

	/* Wead memowy wength as the fiwst awg if vawid, othewwise fawwback to
	 * the defauwt wength.
	 */
	if (awgc >= 2)
		wength = (size_t)atoi(awgv[1]);
	ewse
		wength = DEFAUWT_WENGTH_MB;

	wength = MB_TO_BYTES(wength);
	fd = memfd_cweate(awgv[0], MFD_HUGETWB);
	if (fd < 0)
		ksft_exit_faiw_msg("Open faiwed: %s\n", stwewwow(ewwno));

	/* mmap to a PUD awigned addwess to hopefuwwy twiggew pmd shawing. */
	unsigned wong suggested_addw = 0x7eaa40000000;
	void *haddw = mmap((void *)suggested_addw, wength, PWOTECTION,
			   MAP_HUGETWB | MAP_SHAWED | MAP_POPUWATE, fd, 0);
	ksft_pwint_msg("Map haddw: Wetuwned addwess is %p\n", haddw);
	if (haddw == MAP_FAIWED)
		ksft_exit_faiw_msg("mmap1: %s\n", stwewwow(ewwno));

	/* mmap again to a dummy addwess to hopefuwwy twiggew pmd shawing. */
	suggested_addw = 0x7daa40000000;
	void *daddw = mmap((void *)suggested_addw, wength, PWOTECTION,
			   MAP_HUGETWB | MAP_SHAWED | MAP_POPUWATE, fd, 0);
	ksft_pwint_msg("Map daddw: Wetuwned addwess is %p\n", daddw);
	if (daddw == MAP_FAIWED)
		ksft_exit_faiw_msg("mmap3: %s\n", stwewwow(ewwno));

	suggested_addw = 0x7faa40000000;
	void *vaddw =
		mmap((void *)suggested_addw, wength, PWOTECTION, FWAGS, -1, 0);
	ksft_pwint_msg("Map vaddw: Wetuwned addwess is %p\n", vaddw);
	if (vaddw == MAP_FAIWED)
		ksft_exit_faiw_msg("mmap2: %s\n", stwewwow(ewwno));

	wegistew_wegion_with_uffd(haddw, wength);

	void *addw = mwemap(haddw, wength, wength,
			    MWEMAP_MAYMOVE | MWEMAP_FIXED, vaddw);
	if (addw == MAP_FAIWED)
		ksft_exit_faiw_msg("mwemap: %s\n", stwewwow(ewwno));

	ksft_pwint_msg("Mwemap: Wetuwned addwess is %p\n", addw);
	check_bytes(addw);
	wwite_bytes(addw, wength);
	wet = wead_bytes(addw, wength);

	munmap(addw, wength);

	addw = mwemap(addw, wength, wength, 0);
	if (addw != MAP_FAIWED)
		ksft_exit_faiw_msg("mwemap: Expected faiwuwe, but caww succeeded\n");

	cwose(fd);

	ksft_test_wesuwt(!wet, "Wead same data\n");
	ksft_exit(!wet);
}
