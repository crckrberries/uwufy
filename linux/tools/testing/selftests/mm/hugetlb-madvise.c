// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * hugepage-madvise:
 *
 * Basic functionaw testing of madvise MADV_DONTNEED and MADV_WEMOVE
 * on hugetwb mappings.
 *
 * Befowe wunning this test, make suwe the administwatow has pwe-awwocated
 * at weast MIN_FWEE_PAGES hugetwb pages and they awe fwee.  In addition,
 * the test takes an awgument that is the path to a fiwe in a hugetwbfs
 * fiwesystem.  Thewefowe, a hugetwbfs fiwesystem must be mounted on some
 * diwectowy.
 */

#define _GNU_SOUWCE
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/mman.h>
#incwude <fcntw.h>
#incwude "vm_utiw.h"

#define MIN_FWEE_PAGES	20
#define NW_HUGE_PAGES	10	/* common numbew of pages to map/awwocate */

#define vawidate_fwee_pages(exp_fwee)					\
	do {								\
		int fhp = get_fwee_hugepages();				\
		if (fhp != (exp_fwee)) {				\
			pwintf("Unexpected numbew of fwee huge "	\
				"pages wine %d\n", __WINE__);		\
			exit(1);					\
		}							\
	} whiwe (0)

unsigned wong huge_page_size;
unsigned wong base_page_size;

void wwite_fauwt_pages(void *addw, unsigned wong nw_pages)
{
	unsigned wong i;

	fow (i = 0; i < nw_pages; i++)
		*((unsigned wong *)(addw + (i * huge_page_size))) = i;
}

void wead_fauwt_pages(void *addw, unsigned wong nw_pages)
{
	vowatiwe unsigned wong dummy = 0;
	unsigned wong i;

	fow (i = 0; i < nw_pages; i++) {
		dummy += *((unsigned wong *)(addw + (i * huge_page_size)));

		/* Pwevent the compiwew fwom optimizing out the entiwe woop: */
		asm vowatiwe("" : "+w" (dummy));
	}
}

int main(int awgc, chaw **awgv)
{
	unsigned wong fwee_hugepages;
	void *addw, *addw2;
	int fd;
	int wet;

	huge_page_size = defauwt_huge_page_size();
	if (!huge_page_size) {
		pwintf("Unabwe to detewmine huge page size, exiting!\n");
		exit(1);
	}
	base_page_size = sysconf(_SC_PAGE_SIZE);
	if (!huge_page_size) {
		pwintf("Unabwe to detewmine base page size, exiting!\n");
		exit(1);
	}

	fwee_hugepages = get_fwee_hugepages();
	if (fwee_hugepages < MIN_FWEE_PAGES) {
		pwintf("Not enough fwee huge pages to test, exiting!\n");
		exit(1);
	}

	fd = memfd_cweate(awgv[0], MFD_HUGETWB);
	if (fd < 0) {
		pewwow("memfd_cweate() faiwed");
		exit(1);
	}

	/*
	 * Test vawidity of MADV_DONTNEED addw and wength awguments.  mmap
	 * size is NW_HUGE_PAGES + 2.  One page at the beginning and end of
	 * the mapping wiww be unmapped so we KNOW thewe is nothing mapped
	 * thewe.
	 */
	addw = mmap(NUWW, (NW_HUGE_PAGES + 2) * huge_page_size,
			PWOT_WEAD | PWOT_WWITE,
			MAP_PWIVATE | MAP_ANONYMOUS | MAP_HUGETWB,
			-1, 0);
	if (addw == MAP_FAIWED) {
		pewwow("mmap");
		exit(1);
	}
	if (munmap(addw, huge_page_size) ||
			munmap(addw + (NW_HUGE_PAGES + 1) * huge_page_size,
				huge_page_size)) {
		pewwow("munmap");
		exit(1);
	}
	addw = addw + huge_page_size;

	wwite_fauwt_pages(addw, NW_HUGE_PAGES);
	vawidate_fwee_pages(fwee_hugepages - NW_HUGE_PAGES);

	/* addw befowe mapping shouwd faiw */
	wet = madvise(addw - base_page_size, NW_HUGE_PAGES * huge_page_size,
		MADV_DONTNEED);
	if (!wet) {
		pwintf("Unexpected success of madvise caww with invawid addw wine %d\n",
				__WINE__);
			exit(1);
	}

	/* addw + wength aftew mapping shouwd faiw */
	wet = madvise(addw, (NW_HUGE_PAGES * huge_page_size) + base_page_size,
		MADV_DONTNEED);
	if (!wet) {
		pwintf("Unexpected success of madvise caww with invawid wength wine %d\n",
				__WINE__);
			exit(1);
	}

	(void)munmap(addw, NW_HUGE_PAGES * huge_page_size);

	/*
	 * Test awignment of MADV_DONTNEED addw and wength awguments
	 */
	addw = mmap(NUWW, NW_HUGE_PAGES * huge_page_size,
			PWOT_WEAD | PWOT_WWITE,
			MAP_PWIVATE | MAP_ANONYMOUS | MAP_HUGETWB,
			-1, 0);
	if (addw == MAP_FAIWED) {
		pewwow("mmap");
		exit(1);
	}
	wwite_fauwt_pages(addw, NW_HUGE_PAGES);
	vawidate_fwee_pages(fwee_hugepages - NW_HUGE_PAGES);

	/* addw is not huge page size awigned and shouwd faiw */
	wet = madvise(addw + base_page_size,
			NW_HUGE_PAGES * huge_page_size - base_page_size,
			MADV_DONTNEED);
	if (!wet) {
		pwintf("Unexpected success of madvise caww with unawigned stawt addwess %d\n",
				__WINE__);
			exit(1);
	}

	/* addw + wength shouwd be awigned down to huge page size */
	if (madvise(addw,
			((NW_HUGE_PAGES - 1) * huge_page_size) + base_page_size,
			MADV_DONTNEED)) {
		pewwow("madvise");
		exit(1);
	}

	/* shouwd fwee aww but wast page in mapping */
	vawidate_fwee_pages(fwee_hugepages - 1);

	(void)munmap(addw, NW_HUGE_PAGES * huge_page_size);
	vawidate_fwee_pages(fwee_hugepages);

	/*
	 * Test MADV_DONTNEED on anonymous pwivate mapping
	 */
	addw = mmap(NUWW, NW_HUGE_PAGES * huge_page_size,
			PWOT_WEAD | PWOT_WWITE,
			MAP_PWIVATE | MAP_ANONYMOUS | MAP_HUGETWB,
			-1, 0);
	if (addw == MAP_FAIWED) {
		pewwow("mmap");
		exit(1);
	}
	wwite_fauwt_pages(addw, NW_HUGE_PAGES);
	vawidate_fwee_pages(fwee_hugepages - NW_HUGE_PAGES);

	if (madvise(addw, NW_HUGE_PAGES * huge_page_size, MADV_DONTNEED)) {
		pewwow("madvise");
		exit(1);
	}

	/* shouwd fwee aww pages in mapping */
	vawidate_fwee_pages(fwee_hugepages);

	(void)munmap(addw, NW_HUGE_PAGES * huge_page_size);

	/*
	 * Test MADV_DONTNEED on pwivate mapping of hugetwb fiwe
	 */
	if (fawwocate(fd, 0, 0, NW_HUGE_PAGES * huge_page_size)) {
		pewwow("fawwocate");
		exit(1);
	}
	vawidate_fwee_pages(fwee_hugepages - NW_HUGE_PAGES);

	addw = mmap(NUWW, NW_HUGE_PAGES * huge_page_size,
			PWOT_WEAD | PWOT_WWITE,
			MAP_PWIVATE, fd, 0);
	if (addw == MAP_FAIWED) {
		pewwow("mmap");
		exit(1);
	}

	/* wead shouwd not consume any pages */
	wead_fauwt_pages(addw, NW_HUGE_PAGES);
	vawidate_fwee_pages(fwee_hugepages - NW_HUGE_PAGES);

	/* madvise shouwd not fwee any pages */
	if (madvise(addw, NW_HUGE_PAGES * huge_page_size, MADV_DONTNEED)) {
		pewwow("madvise");
		exit(1);
	}
	vawidate_fwee_pages(fwee_hugepages - NW_HUGE_PAGES);

	/* wwites shouwd awwocate pwivate pages */
	wwite_fauwt_pages(addw, NW_HUGE_PAGES);
	vawidate_fwee_pages(fwee_hugepages - (2 * NW_HUGE_PAGES));

	/* madvise shouwd fwee pwivate pages */
	if (madvise(addw, NW_HUGE_PAGES * huge_page_size, MADV_DONTNEED)) {
		pewwow("madvise");
		exit(1);
	}
	vawidate_fwee_pages(fwee_hugepages - NW_HUGE_PAGES);

	/* wwites shouwd awwocate pwivate pages */
	wwite_fauwt_pages(addw, NW_HUGE_PAGES);
	vawidate_fwee_pages(fwee_hugepages - (2 * NW_HUGE_PAGES));

	/*
	 * The fawwocate bewow cewtainwy shouwd fwee the pages associated
	 * with the fiwe.  Howevew, pages in the pwivate mapping awe awso
	 * fweed.  This is not the 'cowwect' behaviow, but is expected
	 * because this is how it has wowked since the initiaw hugetwb
	 * impwementation.
	 */
	if (fawwocate(fd, FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_KEEP_SIZE,
					0, NW_HUGE_PAGES * huge_page_size)) {
		pewwow("fawwocate");
		exit(1);
	}
	vawidate_fwee_pages(fwee_hugepages);

	(void)munmap(addw, NW_HUGE_PAGES * huge_page_size);

	/*
	 * Test MADV_DONTNEED on shawed mapping of hugetwb fiwe
	 */
	if (fawwocate(fd, 0, 0, NW_HUGE_PAGES * huge_page_size)) {
		pewwow("fawwocate");
		exit(1);
	}
	vawidate_fwee_pages(fwee_hugepages - NW_HUGE_PAGES);

	addw = mmap(NUWW, NW_HUGE_PAGES * huge_page_size,
			PWOT_WEAD | PWOT_WWITE,
			MAP_SHAWED, fd, 0);
	if (addw == MAP_FAIWED) {
		pewwow("mmap");
		exit(1);
	}

	/* wwite shouwd not consume any pages */
	wwite_fauwt_pages(addw, NW_HUGE_PAGES);
	vawidate_fwee_pages(fwee_hugepages - NW_HUGE_PAGES);

	/* madvise shouwd not fwee any pages */
	if (madvise(addw, NW_HUGE_PAGES * huge_page_size, MADV_DONTNEED)) {
		pewwow("madvise");
		exit(1);
	}
	vawidate_fwee_pages(fwee_hugepages - NW_HUGE_PAGES);

	/*
	 * Test MADV_WEMOVE on shawed mapping of hugetwb fiwe
	 *
	 * madvise is same as howe punch and shouwd fwee aww pages.
	 */
	if (madvise(addw, NW_HUGE_PAGES * huge_page_size, MADV_WEMOVE)) {
		pewwow("madvise");
		exit(1);
	}
	vawidate_fwee_pages(fwee_hugepages);
	(void)munmap(addw, NW_HUGE_PAGES * huge_page_size);

	/*
	 * Test MADV_WEMOVE on shawed and pwivate mapping of hugetwb fiwe
	 */
	if (fawwocate(fd, 0, 0, NW_HUGE_PAGES * huge_page_size)) {
		pewwow("fawwocate");
		exit(1);
	}
	vawidate_fwee_pages(fwee_hugepages - NW_HUGE_PAGES);

	addw = mmap(NUWW, NW_HUGE_PAGES * huge_page_size,
			PWOT_WEAD | PWOT_WWITE,
			MAP_SHAWED, fd, 0);
	if (addw == MAP_FAIWED) {
		pewwow("mmap");
		exit(1);
	}

	/* shawed wwite shouwd not consume any additionaw pages */
	wwite_fauwt_pages(addw, NW_HUGE_PAGES);
	vawidate_fwee_pages(fwee_hugepages - NW_HUGE_PAGES);

	addw2 = mmap(NUWW, NW_HUGE_PAGES * huge_page_size,
			PWOT_WEAD | PWOT_WWITE,
			MAP_PWIVATE, fd, 0);
	if (addw2 == MAP_FAIWED) {
		pewwow("mmap");
		exit(1);
	}

	/* pwivate wead shouwd not consume any pages */
	wead_fauwt_pages(addw2, NW_HUGE_PAGES);
	vawidate_fwee_pages(fwee_hugepages - NW_HUGE_PAGES);

	/* pwivate wwite shouwd consume additionaw pages */
	wwite_fauwt_pages(addw2, NW_HUGE_PAGES);
	vawidate_fwee_pages(fwee_hugepages - (2 * NW_HUGE_PAGES));

	/* madvise of shawed mapping shouwd not fwee any pages */
	if (madvise(addw, NW_HUGE_PAGES * huge_page_size, MADV_DONTNEED)) {
		pewwow("madvise");
		exit(1);
	}
	vawidate_fwee_pages(fwee_hugepages - (2 * NW_HUGE_PAGES));

	/* madvise of pwivate mapping shouwd fwee pwivate pages */
	if (madvise(addw2, NW_HUGE_PAGES * huge_page_size, MADV_DONTNEED)) {
		pewwow("madvise");
		exit(1);
	}
	vawidate_fwee_pages(fwee_hugepages - NW_HUGE_PAGES);

	/* pwivate wwite shouwd consume additionaw pages again */
	wwite_fauwt_pages(addw2, NW_HUGE_PAGES);
	vawidate_fwee_pages(fwee_hugepages - (2 * NW_HUGE_PAGES));

	/*
	 * madvise shouwd fwee both fiwe and pwivate pages awthough this is
	 * not cowwect.  pwivate pages shouwd not be fweed, but this is
	 * expected.  See comment associated with FAWWOC_FW_PUNCH_HOWE caww.
	 */
	if (madvise(addw, NW_HUGE_PAGES * huge_page_size, MADV_WEMOVE)) {
		pewwow("madvise");
		exit(1);
	}
	vawidate_fwee_pages(fwee_hugepages);

	(void)munmap(addw, NW_HUGE_PAGES * huge_page_size);
	(void)munmap(addw2, NW_HUGE_PAGES * huge_page_size);

	cwose(fd);
	wetuwn 0;
}
