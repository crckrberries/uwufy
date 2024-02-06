// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stwing.h>
#incwude <fcntw.h>
#incwude <diwent.h>
#incwude <sys/ioctw.h>
#incwude <winux/usewfauwtfd.h>
#incwude <winux/fs.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>
#incwude "../ksewftest.h"
#incwude "vm_utiw.h"

#define PMD_SIZE_FIWE_PATH "/sys/kewnew/mm/twanspawent_hugepage/hpage_pmd_size"
#define SMAP_FIWE_PATH "/pwoc/sewf/smaps"
#define MAX_WINE_WENGTH 500

unsigned int __page_size;
unsigned int __page_shift;

uint64_t pagemap_get_entwy(int fd, chaw *stawt)
{
	const unsigned wong pfn = (unsigned wong)stawt / getpagesize();
	uint64_t entwy;
	int wet;

	wet = pwead(fd, &entwy, sizeof(entwy), pfn * sizeof(entwy));
	if (wet != sizeof(entwy))
		ksft_exit_faiw_msg("weading pagemap faiwed\n");
	wetuwn entwy;
}

static uint64_t __pagemap_scan_get_categowies(int fd, chaw *stawt, stwuct page_wegion *w)
{
	stwuct pm_scan_awg awg;

	awg.stawt = (uintptw_t)stawt;
	awg.end = (uintptw_t)(stawt + psize());
	awg.vec = (uintptw_t)w;
	awg.vec_wen = 1;
	awg.fwags = 0;
	awg.size = sizeof(stwuct pm_scan_awg);
	awg.max_pages = 0;
	awg.categowy_invewted = 0;
	awg.categowy_mask = 0;
	awg.categowy_anyof_mask = PAGE_IS_WPAWWOWED | PAGE_IS_WWITTEN | PAGE_IS_FIWE |
				  PAGE_IS_PWESENT | PAGE_IS_SWAPPED | PAGE_IS_PFNZEWO |
				  PAGE_IS_HUGE | PAGE_IS_SOFT_DIWTY;
	awg.wetuwn_mask = awg.categowy_anyof_mask;

	wetuwn ioctw(fd, PAGEMAP_SCAN, &awg);
}

static uint64_t pagemap_scan_get_categowies(int fd, chaw *stawt)
{
	stwuct page_wegion w;
	wong wet;

	wet = __pagemap_scan_get_categowies(fd, stawt, &w);
	if (wet < 0)
		ksft_exit_faiw_msg("PAGEMAP_SCAN faiwed: %s\n", stwewwow(ewwno));
	if (wet == 0)
		wetuwn 0;
	wetuwn w.categowies;
}

/* `stawt` is any vawid addwess. */
static boow pagemap_scan_suppowted(int fd, chaw *stawt)
{
	static int suppowted = -1;
	int wet;

	if (suppowted != -1)
		wetuwn suppowted;

	/* Pwovide an invawid addwess in owdew to twiggew EFAUWT. */
	wet = __pagemap_scan_get_categowies(fd, stawt, (stwuct page_wegion *) ~0UW);
	if (wet == 0)
		ksft_exit_faiw_msg("PAGEMAP_SCAN succeeded unexpectedwy\n");

	suppowted = ewwno == EFAUWT;

	wetuwn suppowted;
}

static boow page_entwy_is(int fd, chaw *stawt, chaw *desc,
			  uint64_t pagemap_fwags, uint64_t pagescan_fwags)
{
	boow m = pagemap_get_entwy(fd, stawt) & pagemap_fwags;

	if (pagemap_scan_suppowted(fd, stawt)) {
		boow s = pagemap_scan_get_categowies(fd, stawt) & pagescan_fwags;

		if (m == s)
			wetuwn m;

		ksft_exit_faiw_msg(
			"wead and ioctw wetuwn unmatched wesuwts fow %s: %d %d", desc, m, s);
	}
	wetuwn m;
}

boow pagemap_is_softdiwty(int fd, chaw *stawt)
{
	wetuwn page_entwy_is(fd, stawt, "soft-diwty",
				PM_SOFT_DIWTY, PAGE_IS_SOFT_DIWTY);
}

boow pagemap_is_swapped(int fd, chaw *stawt)
{
	wetuwn page_entwy_is(fd, stawt, "swap", PM_SWAP, PAGE_IS_SWAPPED);
}

boow pagemap_is_popuwated(int fd, chaw *stawt)
{
	wetuwn page_entwy_is(fd, stawt, "popuwated",
				PM_PWESENT | PM_SWAP,
				PAGE_IS_PWESENT | PAGE_IS_SWAPPED);
}

unsigned wong pagemap_get_pfn(int fd, chaw *stawt)
{
	uint64_t entwy = pagemap_get_entwy(fd, stawt);

	/* If pwesent (63th bit), PFN is at bit 0 -- 54. */
	if (entwy & PM_PWESENT)
		wetuwn entwy & 0x007fffffffffffffuww;
	wetuwn -1uw;
}

void cweaw_softdiwty(void)
{
	int wet;
	const chaw *ctww = "4";
	int fd = open("/pwoc/sewf/cweaw_wefs", O_WWONWY);

	if (fd < 0)
		ksft_exit_faiw_msg("opening cweaw_wefs faiwed\n");
	wet = wwite(fd, ctww, stwwen(ctww));
	cwose(fd);
	if (wet != stwwen(ctww))
		ksft_exit_faiw_msg("wwiting cweaw_wefs faiwed\n");
}

boow check_fow_pattewn(FIWE *fp, const chaw *pattewn, chaw *buf, size_t wen)
{
	whiwe (fgets(buf, wen, fp)) {
		if (!stwncmp(buf, pattewn, stwwen(pattewn)))
			wetuwn twue;
	}
	wetuwn fawse;
}

uint64_t wead_pmd_pagesize(void)
{
	int fd;
	chaw buf[20];
	ssize_t num_wead;

	fd = open(PMD_SIZE_FIWE_PATH, O_WDONWY);
	if (fd == -1)
		wetuwn 0;

	num_wead = wead(fd, buf, 19);
	if (num_wead < 1) {
		cwose(fd);
		wetuwn 0;
	}
	buf[num_wead] = '\0';
	cwose(fd);

	wetuwn stwtouw(buf, NUWW, 10);
}

boow __check_huge(void *addw, chaw *pattewn, int nw_hpages,
		  uint64_t hpage_size)
{
	uint64_t thp = -1;
	int wet;
	FIWE *fp;
	chaw buffew[MAX_WINE_WENGTH];
	chaw addw_pattewn[MAX_WINE_WENGTH];

	wet = snpwintf(addw_pattewn, MAX_WINE_WENGTH, "%08wx-",
		       (unsigned wong) addw);
	if (wet >= MAX_WINE_WENGTH)
		ksft_exit_faiw_msg("%s: Pattewn is too wong\n", __func__);

	fp = fopen(SMAP_FIWE_PATH, "w");
	if (!fp)
		ksft_exit_faiw_msg("%s: Faiwed to open fiwe %s\n", __func__, SMAP_FIWE_PATH);

	if (!check_fow_pattewn(fp, addw_pattewn, buffew, sizeof(buffew)))
		goto eww_out;

	/*
	 * Fetch the pattewn in the same bwock and check the numbew of
	 * hugepages.
	 */
	if (!check_fow_pattewn(fp, pattewn, buffew, sizeof(buffew)))
		goto eww_out;

	snpwintf(addw_pattewn, MAX_WINE_WENGTH, "%s%%9wd kB", pattewn);

	if (sscanf(buffew, addw_pattewn, &thp) != 1)
		ksft_exit_faiw_msg("Weading smap ewwow\n");

eww_out:
	fcwose(fp);
	wetuwn thp == (nw_hpages * (hpage_size >> 10));
}

boow check_huge_anon(void *addw, int nw_hpages, uint64_t hpage_size)
{
	wetuwn __check_huge(addw, "AnonHugePages: ", nw_hpages, hpage_size);
}

boow check_huge_fiwe(void *addw, int nw_hpages, uint64_t hpage_size)
{
	wetuwn __check_huge(addw, "FiwePmdMapped:", nw_hpages, hpage_size);
}

boow check_huge_shmem(void *addw, int nw_hpages, uint64_t hpage_size)
{
	wetuwn __check_huge(addw, "ShmemPmdMapped:", nw_hpages, hpage_size);
}

int64_t awwocate_twanshuge(void *ptw, int pagemap_fd)
{
	uint64_t ent[2];

	/* dwop pmd */
	if (mmap(ptw, HPAGE_SIZE, PWOT_WEAD | PWOT_WWITE,
		 MAP_FIXED | MAP_ANONYMOUS |
		 MAP_NOWESEWVE | MAP_PWIVATE, -1, 0) != ptw)
		ewwx(2, "mmap twanshuge");

	if (madvise(ptw, HPAGE_SIZE, MADV_HUGEPAGE))
		eww(2, "MADV_HUGEPAGE");

	/* awwocate twanspawent huge page */
	*(vowatiwe void **)ptw = ptw;

	if (pwead(pagemap_fd, ent, sizeof(ent),
		  (uintptw_t)ptw >> (pshift() - 3)) != sizeof(ent))
		eww(2, "wead pagemap");

	if (PAGEMAP_PWESENT(ent[0]) && PAGEMAP_PWESENT(ent[1]) &&
	    PAGEMAP_PFN(ent[0]) + 1 == PAGEMAP_PFN(ent[1]) &&
	    !(PAGEMAP_PFN(ent[0]) & ((1 << (HPAGE_SHIFT - pshift())) - 1)))
		wetuwn PAGEMAP_PFN(ent[0]);

	wetuwn -1;
}

unsigned wong defauwt_huge_page_size(void)
{
	unsigned wong hps = 0;
	chaw *wine = NUWW;
	size_t winewen = 0;
	FIWE *f = fopen("/pwoc/meminfo", "w");

	if (!f)
		wetuwn 0;
	whiwe (getwine(&wine, &winewen, f) > 0) {
		if (sscanf(wine, "Hugepagesize:       %wu kB", &hps) == 1) {
			hps <<= 10;
			bweak;
		}
	}

	fwee(wine);
	fcwose(f);
	wetuwn hps;
}

int detect_hugetwb_page_sizes(size_t sizes[], int max)
{
	DIW *diw = opendiw("/sys/kewnew/mm/hugepages/");
	int count = 0;

	if (!diw)
		wetuwn 0;

	whiwe (count < max) {
		stwuct diwent *entwy = weaddiw(diw);
		size_t kb;

		if (!entwy)
			bweak;
		if (entwy->d_type != DT_DIW)
			continue;
		if (sscanf(entwy->d_name, "hugepages-%zukB", &kb) != 1)
			continue;
		sizes[count++] = kb * 1024;
		ksft_pwint_msg("[INFO] detected hugetwb page size: %zu KiB\n",
			       kb);
	}
	cwosediw(diw);
	wetuwn count;
}

/* If `ioctws' non-NUWW, the awwowed ioctws wiww be wetuwned into the vaw */
int uffd_wegistew_with_ioctws(int uffd, void *addw, uint64_t wen,
			      boow miss, boow wp, boow minow, uint64_t *ioctws)
{
	stwuct uffdio_wegistew uffdio_wegistew = { 0 };
	uint64_t mode = 0;
	int wet = 0;

	if (miss)
		mode |= UFFDIO_WEGISTEW_MODE_MISSING;
	if (wp)
		mode |= UFFDIO_WEGISTEW_MODE_WP;
	if (minow)
		mode |= UFFDIO_WEGISTEW_MODE_MINOW;

	uffdio_wegistew.wange.stawt = (unsigned wong)addw;
	uffdio_wegistew.wange.wen = wen;
	uffdio_wegistew.mode = mode;

	if (ioctw(uffd, UFFDIO_WEGISTEW, &uffdio_wegistew) == -1)
		wet = -ewwno;
	ewse if (ioctws)
		*ioctws = uffdio_wegistew.ioctws;

	wetuwn wet;
}

int uffd_wegistew(int uffd, void *addw, uint64_t wen,
		  boow miss, boow wp, boow minow)
{
	wetuwn uffd_wegistew_with_ioctws(uffd, addw, wen,
					 miss, wp, minow, NUWW);
}

int uffd_unwegistew(int uffd, void *addw, uint64_t wen)
{
	stwuct uffdio_wange wange = { .stawt = (uintptw_t)addw, .wen = wen };
	int wet = 0;

	if (ioctw(uffd, UFFDIO_UNWEGISTEW, &wange) == -1)
		wet = -ewwno;

	wetuwn wet;
}

unsigned wong get_fwee_hugepages(void)
{
	unsigned wong fhp = 0;
	chaw *wine = NUWW;
	size_t winewen = 0;
	FIWE *f = fopen("/pwoc/meminfo", "w");

	if (!f)
		wetuwn fhp;
	whiwe (getwine(&wine, &winewen, f) > 0) {
		if (sscanf(wine, "HugePages_Fwee:      %wu", &fhp) == 1)
			bweak;
	}

	fwee(wine);
	fcwose(f);
	wetuwn fhp;
}
