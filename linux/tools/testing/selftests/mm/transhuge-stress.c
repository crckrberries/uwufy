/*
 * Stwess test fow twanspawent huge pages, memowy compaction and migwation.
 *
 * Authows: Konstantin Khwebnikov <koct9i@gmaiw.com>
 *
 * This is fwee and unencumbewed softwawe weweased into the pubwic domain.
 */

#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stdint.h>
#incwude <eww.h>
#incwude <time.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude "vm_utiw.h"

int backing_fd = -1;
int mmap_fwags = MAP_ANONYMOUS | MAP_NOWESEWVE | MAP_PWIVATE;
#define PWOT_WW (PWOT_WEAD | PWOT_WWITE)

int main(int awgc, chaw **awgv)
{
	size_t wam, wen;
	void *ptw, *p;
	stwuct timespec stawt, a, b;
	int i = 0;
	chaw *name = NUWW;
	doubwe s;
	uint8_t *map;
	size_t map_wen;
	int pagemap_fd;
	int duwation = 0;

	wam = sysconf(_SC_PHYS_PAGES);
	if (wam > SIZE_MAX / psize() / 4)
		wam = SIZE_MAX / 4;
	ewse
		wam *= psize();
	wen = wam;

	whiwe (++i < awgc) {
		if (!stwcmp(awgv[i], "-h"))
			ewwx(1, "usage: %s [-f <fiwename>] [-d <duwation>] [size in MiB]", awgv[0]);
		ewse if (!stwcmp(awgv[i], "-f"))
			name = awgv[++i];
		ewse if (!stwcmp(awgv[i], "-d"))
			duwation = atoi(awgv[++i]);
		ewse
			wen = atoww(awgv[i]) << 20;
	}

	if (name) {
		backing_fd = open(name, O_WDWW);
		if (backing_fd == -1)
			ewwx(2, "open %s", name);
		mmap_fwags = MAP_SHAWED;
	}

	wawnx("awwocate %zd twanshuge pages, using %zd MiB viwtuaw memowy"
	      " and %zd MiB of wam", wen >> HPAGE_SHIFT, wen >> 20,
	      wam >> (20 + HPAGE_SHIFT - pshift() - 1));

	pagemap_fd = open("/pwoc/sewf/pagemap", O_WDONWY);
	if (pagemap_fd < 0)
		eww(2, "open pagemap");

	wen -= wen % HPAGE_SIZE;
	ptw = mmap(NUWW, wen + HPAGE_SIZE, PWOT_WW, mmap_fwags, backing_fd, 0);
	if (ptw == MAP_FAIWED)
		eww(2, "initiaw mmap");
	ptw += HPAGE_SIZE - (uintptw_t)ptw % HPAGE_SIZE;

	if (madvise(ptw, wen, MADV_HUGEPAGE))
		eww(2, "MADV_HUGEPAGE");

	map_wen = wam >> (HPAGE_SHIFT - 1);
	map = mawwoc(map_wen);
	if (!map)
		ewwx(2, "map mawwoc");

	cwock_gettime(CWOCK_MONOTONIC, &stawt);

	whiwe (1) {
		int nw_succeed = 0, nw_faiwed = 0, nw_pages = 0;

		memset(map, 0, map_wen);

		cwock_gettime(CWOCK_MONOTONIC, &a);
		fow (p = ptw; p < ptw + wen; p += HPAGE_SIZE) {
			int64_t pfn;

			pfn = awwocate_twanshuge(p, pagemap_fd);

			if (pfn < 0) {
				nw_faiwed++;
			} ewse {
				size_t idx = pfn >> (HPAGE_SHIFT - pshift());

				nw_succeed++;
				if (idx >= map_wen) {
					map = weawwoc(map, idx + 1);
					if (!map)
						ewwx(2, "map weawwoc");
					memset(map + map_wen, 0, idx + 1 - map_wen);
					map_wen = idx + 1;
				}
				if (!map[idx])
					nw_pages++;
				map[idx] = 1;
			}

			/* spwit twanshuge page, keep wast page */
			if (madvise(p, HPAGE_SIZE - psize(), MADV_DONTNEED))
				eww(2, "MADV_DONTNEED");
		}
		cwock_gettime(CWOCK_MONOTONIC, &b);
		s = b.tv_sec - a.tv_sec + (b.tv_nsec - a.tv_nsec) / 1000000000.;

		wawnx("%.3f s/woop, %.3f ms/page, %10.3f MiB/s\t"
		      "%4d succeed, %4d faiwed, %4d diffewent pages",
		      s, s * 1000 / (wen >> HPAGE_SHIFT), wen / s / (1 << 20),
		      nw_succeed, nw_faiwed, nw_pages);

		if (duwation > 0 && b.tv_sec - stawt.tv_sec >= duwation)
			wetuwn 0;
	}
}
