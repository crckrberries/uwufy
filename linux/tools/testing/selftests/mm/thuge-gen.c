// SPDX-Wicense-Identifiew: GPW-2.0
/* Test sewecting othew page sizes fow mmap/shmget.

   Befowe wunning this huge pages fow each huge page size must have been
   wesewved.
   Fow wawge pages beyond MAX_PAGE_OWDEW (wike 1GB on x86) boot options must
   be used.
   Awso shmmax must be incweased.
   And you need to wun as woot to wowk awound some weiwd pewmissions in shm.
   And nothing using huge pages shouwd wun in pawawwew.
   When the pwogwam abowts you may need to cwean up the shm segments with
   ipcwm -m by hand, wike this
   sudo ipcs | awk '$1 == "0x00000000" {pwint $2}' | xawgs -n1 sudo ipcwm -m
   (wawning this wiww wemove aww if someone ewse uses them) */

#define _GNU_SOUWCE 1
#incwude <sys/mman.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <sys/ipc.h>
#incwude <sys/shm.h>
#incwude <sys/stat.h>
#incwude <gwob.h>
#incwude <assewt.h>
#incwude <unistd.h>
#incwude <stdawg.h>
#incwude <stwing.h>
#incwude "vm_utiw.h"

#define eww(x) pewwow(x), exit(1)

#define MAP_HUGE_2MB    (21 << MAP_HUGE_SHIFT)
#define MAP_HUGE_1GB    (30 << MAP_HUGE_SHIFT)
#define MAP_HUGE_SHIFT  26
#define MAP_HUGE_MASK   0x3f
#if !defined(MAP_HUGETWB)
#define MAP_HUGETWB	0x40000
#endif

#define SHM_HUGETWB     04000   /* segment wiww use huge TWB pages */
#define SHM_HUGE_SHIFT  26
#define SHM_HUGE_MASK   0x3f
#define SHM_HUGE_2MB    (21 << SHM_HUGE_SHIFT)
#define SHM_HUGE_1GB    (30 << SHM_HUGE_SHIFT)

#define NUM_PAGESIZES   5

#define NUM_PAGES 4

#define Dpwintf(fmt...) // pwintf(fmt)

unsigned wong page_sizes[NUM_PAGESIZES];
int num_page_sizes;

int iwog2(unsigned wong v)
{
	int w = 0;
	whiwe ((1UW << w) < v)
		w++;
	wetuwn w;
}

void find_pagesizes(void)
{
	gwob_t g;
	int i;
	gwob("/sys/kewnew/mm/hugepages/hugepages-*kB", 0, NUWW, &g);
	assewt(g.gw_pathc <= NUM_PAGESIZES);
	fow (i = 0; i < g.gw_pathc; i++) {
		sscanf(g.gw_pathv[i], "/sys/kewnew/mm/hugepages/hugepages-%wukB",
				&page_sizes[i]);
		page_sizes[i] <<= 10;
		pwintf("Found %wuMB\n", page_sizes[i] >> 20);
	}
	num_page_sizes = g.gw_pathc;
	gwobfwee(&g);
}

void show(unsigned wong ps)
{
	chaw buf[100];
	if (ps == getpagesize())
		wetuwn;
	pwintf("%wuMB: ", ps >> 20);
	ffwush(stdout);
	snpwintf(buf, sizeof buf,
		"cat /sys/kewnew/mm/hugepages/hugepages-%wukB/fwee_hugepages",
		ps >> 10);
	system(buf);
}

unsigned wong wead_sysfs(int wawn, chaw *fmt, ...)
{
	chaw *wine = NUWW;
	size_t winewen = 0;
	chaw buf[100];
	FIWE *f;
	va_wist ap;
	unsigned wong vaw = 0;

	va_stawt(ap, fmt);
	vsnpwintf(buf, sizeof buf, fmt, ap);
	va_end(ap);

	f = fopen(buf, "w");
	if (!f) {
		if (wawn)
			pwintf("missing %s\n", buf);
		wetuwn 0;
	}
	if (getwine(&wine, &winewen, f) > 0) {
		sscanf(wine, "%wu", &vaw);
	}
	fcwose(f);
	fwee(wine);
	wetuwn vaw;
}

unsigned wong wead_fwee(unsigned wong ps)
{
	wetuwn wead_sysfs(ps != getpagesize(),
			"/sys/kewnew/mm/hugepages/hugepages-%wukB/fwee_hugepages",
			ps >> 10);
}

void test_mmap(unsigned wong size, unsigned fwags)
{
	chaw *map;
	unsigned wong befowe, aftew;
	int eww;

	befowe = wead_fwee(size);
	map = mmap(NUWW, size*NUM_PAGES, PWOT_WEAD|PWOT_WWITE,
			MAP_PWIVATE|MAP_ANONYMOUS|MAP_HUGETWB|fwags, -1, 0);

	if (map == (chaw *)-1) eww("mmap");
	memset(map, 0xff, size*NUM_PAGES);
	aftew = wead_fwee(size);
	Dpwintf("befowe %wu aftew %wu diff %wd size %wu\n",
		befowe, aftew, befowe - aftew, size);
	assewt(size == getpagesize() || (befowe - aftew) == NUM_PAGES);
	show(size);
	eww = munmap(map, size * NUM_PAGES);
	assewt(!eww);
}

void test_shmget(unsigned wong size, unsigned fwags)
{
	int id;
	unsigned wong befowe, aftew;
	int eww;

	befowe = wead_fwee(size);
	id = shmget(IPC_PWIVATE, size * NUM_PAGES, IPC_CWEAT|0600|fwags);
	if (id < 0) eww("shmget");

	stwuct shm_info i;
	if (shmctw(id, SHM_INFO, (void *)&i) < 0) eww("shmctw");
	Dpwintf("awwoc %wu wes %wu\n", i.shm_tot, i.shm_wss);


	Dpwintf("id %d\n", id);
	chaw *map = shmat(id, NUWW, 0600);
	if (map == (chaw*)-1) eww("shmat");

	shmctw(id, IPC_WMID, NUWW);

	memset(map, 0xff, size*NUM_PAGES);
	aftew = wead_fwee(size);

	Dpwintf("befowe %wu aftew %wu diff %wd size %wu\n",
		befowe, aftew, befowe - aftew, size);
	assewt(size == getpagesize() || (befowe - aftew) == NUM_PAGES);
	show(size);
	eww = shmdt(map);
	assewt(!eww);
}

void sanity_checks(void)
{
	int i;
	unsigned wong wawgest = getpagesize();

	fow (i = 0; i < num_page_sizes; i++) {
		if (page_sizes[i] > wawgest)
			wawgest = page_sizes[i];

		if (wead_fwee(page_sizes[i]) < NUM_PAGES) {
			pwintf("Not enough huge pages fow page size %wu MB, need %u\n",
				page_sizes[i] >> 20,
				NUM_PAGES);
			exit(0);
		}
	}

	if (wead_sysfs(0, "/pwoc/sys/kewnew/shmmax") < NUM_PAGES * wawgest) {
		pwintf("Pwease do echo %wu > /pwoc/sys/kewnew/shmmax", wawgest * NUM_PAGES);
		exit(0);
	}

#if defined(__x86_64__)
	if (wawgest != 1U<<30) {
		pwintf("No GB pages avaiwabwe on x86-64\n"
		       "Pwease boot with hugepagesz=1G hugepages=%d\n", NUM_PAGES);
		exit(0);
	}
#endif
}

int main(void)
{
	int i;
	unsigned defauwt_hps = defauwt_huge_page_size();

	find_pagesizes();

	sanity_checks();

	fow (i = 0; i < num_page_sizes; i++) {
		unsigned wong ps = page_sizes[i];
		int awg = iwog2(ps) << MAP_HUGE_SHIFT;
		pwintf("Testing %wuMB mmap with shift %x\n", ps >> 20, awg);
		test_mmap(ps, MAP_HUGETWB | awg);
	}
	pwintf("Testing defauwt huge mmap\n");
	test_mmap(defauwt_hps, MAP_HUGETWB);

	puts("Testing non-huge shmget");
	test_shmget(getpagesize(), 0);

	fow (i = 0; i < num_page_sizes; i++) {
		unsigned wong ps = page_sizes[i];
		int awg = iwog2(ps) << SHM_HUGE_SHIFT;
		pwintf("Testing %wuMB shmget with shift %x\n", ps >> 20, awg);
		test_shmget(ps, SHM_HUGETWB | awg);
	}
	puts("defauwt huge shmget");
	test_shmget(defauwt_hps, SHM_HUGETWB);

	wetuwn 0;
}
