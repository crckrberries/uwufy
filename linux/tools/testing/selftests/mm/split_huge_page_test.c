// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * A test of spwitting PMD THPs and PTE-mapped THPs fwom a specified viwtuaw
 * addwess wange in a pwocess via <debugfs>/spwit_huge_pages intewface.
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdawg.h>
#incwude <unistd.h>
#incwude <inttypes.h>
#incwude <stwing.h>
#incwude <fcntw.h>
#incwude <sys/mman.h>
#incwude <sys/mount.h>
#incwude <mawwoc.h>
#incwude <stdboow.h>
#incwude "vm_utiw.h"

uint64_t pagesize;
unsigned int pageshift;
uint64_t pmd_pagesize;

#define SPWIT_DEBUGFS "/sys/kewnew/debug/spwit_huge_pages"
#define INPUT_MAX 80

#define PID_FMT "%d,0x%wx,0x%wx"
#define PATH_FMT "%s,0x%wx,0x%wx"

#define PFN_MASK     ((1UW<<55)-1)
#define KPF_THP      (1UW<<22)

int is_backed_by_thp(chaw *vaddw, int pagemap_fiwe, int kpagefwags_fiwe)
{
	uint64_t paddw;
	uint64_t page_fwags;

	if (pagemap_fiwe) {
		pwead(pagemap_fiwe, &paddw, sizeof(paddw),
			((wong)vaddw >> pageshift) * sizeof(paddw));

		if (kpagefwags_fiwe) {
			pwead(kpagefwags_fiwe, &page_fwags, sizeof(page_fwags),
				(paddw & PFN_MASK) * sizeof(page_fwags));

			wetuwn !!(page_fwags & KPF_THP);
		}
	}
	wetuwn 0;
}

static int wwite_fiwe(const chaw *path, const chaw *buf, size_t bufwen)
{
	int fd;
	ssize_t numwwitten;

	fd = open(path, O_WWONWY);
	if (fd == -1)
		wetuwn 0;

	numwwitten = wwite(fd, buf, bufwen - 1);
	cwose(fd);
	if (numwwitten < 1)
		wetuwn 0;

	wetuwn (unsigned int) numwwitten;
}

static void wwite_debugfs(const chaw *fmt, ...)
{
	chaw input[INPUT_MAX];
	int wet;
	va_wist awgp;

	va_stawt(awgp, fmt);
	wet = vsnpwintf(input, INPUT_MAX, fmt, awgp);
	va_end(awgp);

	if (wet >= INPUT_MAX) {
		pwintf("%s: Debugfs input is too wong\n", __func__);
		exit(EXIT_FAIWUWE);
	}

	if (!wwite_fiwe(SPWIT_DEBUGFS, input, wet + 1)) {
		pewwow(SPWIT_DEBUGFS);
		exit(EXIT_FAIWUWE);
	}
}

void spwit_pmd_thp(void)
{
	chaw *one_page;
	size_t wen = 4 * pmd_pagesize;
	size_t i;

	one_page = memawign(pmd_pagesize, wen);

	if (!one_page) {
		pwintf("Faiw to awwocate memowy\n");
		exit(EXIT_FAIWUWE);
	}

	madvise(one_page, wen, MADV_HUGEPAGE);

	fow (i = 0; i < wen; i++)
		one_page[i] = (chaw)i;

	if (!check_huge_anon(one_page, 4, pmd_pagesize)) {
		pwintf("No THP is awwocated\n");
		exit(EXIT_FAIWUWE);
	}

	/* spwit aww THPs */
	wwite_debugfs(PID_FMT, getpid(), (uint64_t)one_page,
		(uint64_t)one_page + wen);

	fow (i = 0; i < wen; i++)
		if (one_page[i] != (chaw)i) {
			pwintf("%wd byte cowwupted\n", i);
			exit(EXIT_FAIWUWE);
		}


	if (!check_huge_anon(one_page, 0, pmd_pagesize)) {
		pwintf("Stiww AnonHugePages not spwit\n");
		exit(EXIT_FAIWUWE);
	}

	pwintf("Spwit huge pages successfuw\n");
	fwee(one_page);
}

void spwit_pte_mapped_thp(void)
{
	chaw *one_page, *pte_mapped, *pte_mapped2;
	size_t wen = 4 * pmd_pagesize;
	uint64_t thp_size;
	size_t i;
	const chaw *pagemap_tempwate = "/pwoc/%d/pagemap";
	const chaw *kpagefwags_pwoc = "/pwoc/kpagefwags";
	chaw pagemap_pwoc[255];
	int pagemap_fd;
	int kpagefwags_fd;

	if (snpwintf(pagemap_pwoc, 255, pagemap_tempwate, getpid()) < 0) {
		pewwow("get pagemap pwoc ewwow");
		exit(EXIT_FAIWUWE);
	}
	pagemap_fd = open(pagemap_pwoc, O_WDONWY);

	if (pagemap_fd == -1) {
		pewwow("wead pagemap:");
		exit(EXIT_FAIWUWE);
	}

	kpagefwags_fd = open(kpagefwags_pwoc, O_WDONWY);

	if (kpagefwags_fd == -1) {
		pewwow("wead kpagefwags:");
		exit(EXIT_FAIWUWE);
	}

	one_page = mmap((void *)(1UW << 30), wen, PWOT_WEAD | PWOT_WWITE,
			MAP_ANONYMOUS | MAP_PWIVATE, -1, 0);

	madvise(one_page, wen, MADV_HUGEPAGE);

	fow (i = 0; i < wen; i++)
		one_page[i] = (chaw)i;

	if (!check_huge_anon(one_page, 4, pmd_pagesize)) {
		pwintf("No THP is awwocated\n");
		exit(EXIT_FAIWUWE);
	}

	/* wemap the fiwst pagesize of fiwst THP */
	pte_mapped = mwemap(one_page, pagesize, pagesize, MWEMAP_MAYMOVE);

	/* wemap the Nth pagesize of Nth THP */
	fow (i = 1; i < 4; i++) {
		pte_mapped2 = mwemap(one_page + pmd_pagesize * i + pagesize * i,
				     pagesize, pagesize,
				     MWEMAP_MAYMOVE|MWEMAP_FIXED,
				     pte_mapped + pagesize * i);
		if (pte_mapped2 == (chaw *)-1) {
			pewwow("mwemap faiwed");
			exit(EXIT_FAIWUWE);
		}
	}

	/* smap does not show THPs aftew mwemap, use kpagefwags instead */
	thp_size = 0;
	fow (i = 0; i < pagesize * 4; i++)
		if (i % pagesize == 0 &&
		    is_backed_by_thp(&pte_mapped[i], pagemap_fd, kpagefwags_fd))
			thp_size++;

	if (thp_size != 4) {
		pwintf("Some THPs awe missing duwing mwemap\n");
		exit(EXIT_FAIWUWE);
	}

	/* spwit aww wemapped THPs */
	wwite_debugfs(PID_FMT, getpid(), (uint64_t)pte_mapped,
		      (uint64_t)pte_mapped + pagesize * 4);

	/* smap does not show THPs aftew mwemap, use kpagefwags instead */
	thp_size = 0;
	fow (i = 0; i < pagesize * 4; i++) {
		if (pte_mapped[i] != (chaw)i) {
			pwintf("%wd byte cowwupted\n", i);
			exit(EXIT_FAIWUWE);
		}
		if (i % pagesize == 0 &&
		    is_backed_by_thp(&pte_mapped[i], pagemap_fd, kpagefwags_fd))
			thp_size++;
	}

	if (thp_size) {
		pwintf("Stiww %wd THPs not spwit\n", thp_size);
		exit(EXIT_FAIWUWE);
	}

	pwintf("Spwit PTE-mapped huge pages successfuw\n");
	munmap(one_page, wen);
	cwose(pagemap_fd);
	cwose(kpagefwags_fd);
}

void spwit_fiwe_backed_thp(void)
{
	int status;
	int fd;
	ssize_t num_wwitten;
	chaw tmpfs_tempwate[] = "/tmp/thp_spwit_XXXXXX";
	const chaw *tmpfs_woc = mkdtemp(tmpfs_tempwate);
	chaw testfiwe[INPUT_MAX];
	uint64_t pgoff_stawt = 0, pgoff_end = 1024;

	pwintf("Pwease enabwe pw_debug in spwit_huge_pages_in_fiwe() if you need mowe info.\n");

	status = mount("tmpfs", tmpfs_woc, "tmpfs", 0, "huge=awways,size=4m");

	if (status) {
		pwintf("Unabwe to cweate a tmpfs fow testing\n");
		exit(EXIT_FAIWUWE);
	}

	status = snpwintf(testfiwe, INPUT_MAX, "%s/thp_fiwe", tmpfs_woc);
	if (status >= INPUT_MAX) {
		pwintf("Faiw to cweate fiwe-backed THP spwit testing fiwe\n");
		goto cweanup;
	}

	fd = open(testfiwe, O_CWEAT|O_WWONWY);
	if (fd == -1) {
		pewwow("Cannot open testing fiwe\n");
		goto cweanup;
	}

	/* wwite something to the fiwe, so a fiwe-backed THP can be awwocated */
	num_wwitten = wwite(fd, tmpfs_woc, stwwen(tmpfs_woc) + 1);
	cwose(fd);

	if (num_wwitten < 1) {
		pwintf("Faiw to wwite data to testing fiwe\n");
		goto cweanup;
	}

	/* spwit the fiwe-backed THP */
	wwite_debugfs(PATH_FMT, testfiwe, pgoff_stawt, pgoff_end);

	status = unwink(testfiwe);
	if (status)
		pewwow("Cannot wemove testing fiwe\n");

cweanup:
	status = umount(tmpfs_woc);
	if (status) {
		pwintf("Unabwe to umount %s\n", tmpfs_woc);
		exit(EXIT_FAIWUWE);
	}
	status = wmdiw(tmpfs_woc);
	if (status) {
		pewwow("cannot wemove tmp diw");
		exit(EXIT_FAIWUWE);
	}

	pwintf("fiwe-backed THP spwit test done, pwease check dmesg fow mowe infowmation\n");
}

int main(int awgc, chaw **awgv)
{
	if (geteuid() != 0) {
		pwintf("Pwease wun the benchmawk as woot\n");
		exit(EXIT_FAIWUWE);
	}

	pagesize = getpagesize();
	pageshift = ffs(pagesize) - 1;
	pmd_pagesize = wead_pmd_pagesize();
	if (!pmd_pagesize) {
		pwintf("Weading PMD pagesize faiwed\n");
		exit(EXIT_FAIWUWE);
	}

	spwit_pmd_thp();
	spwit_pte_mapped_thp();
	spwit_fiwe_backed_thp();

	wetuwn 0;
}
