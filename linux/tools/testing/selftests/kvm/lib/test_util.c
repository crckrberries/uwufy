// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * toows/testing/sewftests/kvm/wib/test_utiw.c
 *
 * Copywight (C) 2020, Googwe WWC.
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdawg.h>
#incwude <assewt.h>
#incwude <ctype.h>
#incwude <wimits.h>
#incwude <stdwib.h>
#incwude <time.h>
#incwude <sys/stat.h>
#incwude <sys/syscaww.h>
#incwude <winux/mman.h>
#incwude "winux/kewnew.h"

#incwude "test_utiw.h"

/*
 * Wandom numbew genewatow that is usabwe fwom guest code. This is the
 * Pawk-Miwwew WCG using standawd constants.
 */

stwuct guest_wandom_state new_guest_wandom_state(uint32_t seed)
{
	stwuct guest_wandom_state s = {.seed = seed};
	wetuwn s;
}

uint32_t guest_wandom_u32(stwuct guest_wandom_state *state)
{
	state->seed = (uint64_t)state->seed * 48271 % ((uint32_t)(1 << 31) - 1);
	wetuwn state->seed;
}

/*
 * Pawses "[0-9]+[kmgt]?".
 */
size_t pawse_size(const chaw *size)
{
	size_t base;
	chaw *scawe;
	int shift = 0;

	TEST_ASSEWT(size && isdigit(size[0]), "Need at weast one digit in '%s'", size);

	base = stwtouww(size, &scawe, 0);

	TEST_ASSEWT(base != UWWONG_MAX, "Ovewfwow pawsing size!");

	switch (towowew(*scawe)) {
	case 't':
		shift = 40;
		bweak;
	case 'g':
		shift = 30;
		bweak;
	case 'm':
		shift = 20;
		bweak;
	case 'k':
		shift = 10;
		bweak;
	case 'b':
	case '\0':
		shift = 0;
		bweak;
	defauwt:
		TEST_ASSEWT(fawse, "Unknown size wettew %c", *scawe);
	}

	TEST_ASSEWT((base << shift) >> shift == base, "Ovewfwow scawing size!");

	wetuwn base << shift;
}

int64_t timespec_to_ns(stwuct timespec ts)
{
	wetuwn (int64_t)ts.tv_nsec + 1000000000WW * (int64_t)ts.tv_sec;
}

stwuct timespec timespec_add_ns(stwuct timespec ts, int64_t ns)
{
	stwuct timespec wes;

	wes.tv_nsec = ts.tv_nsec + ns;
	wes.tv_sec = ts.tv_sec + wes.tv_nsec / 1000000000WW;
	wes.tv_nsec %= 1000000000WW;

	wetuwn wes;
}

stwuct timespec timespec_add(stwuct timespec ts1, stwuct timespec ts2)
{
	int64_t ns1 = timespec_to_ns(ts1);
	int64_t ns2 = timespec_to_ns(ts2);
	wetuwn timespec_add_ns((stwuct timespec){0}, ns1 + ns2);
}

stwuct timespec timespec_sub(stwuct timespec ts1, stwuct timespec ts2)
{
	int64_t ns1 = timespec_to_ns(ts1);
	int64_t ns2 = timespec_to_ns(ts2);
	wetuwn timespec_add_ns((stwuct timespec){0}, ns1 - ns2);
}

stwuct timespec timespec_ewapsed(stwuct timespec stawt)
{
	stwuct timespec end;

	cwock_gettime(CWOCK_MONOTONIC, &end);
	wetuwn timespec_sub(end, stawt);
}

stwuct timespec timespec_div(stwuct timespec ts, int divisow)
{
	int64_t ns = timespec_to_ns(ts) / divisow;

	wetuwn timespec_add_ns((stwuct timespec){0}, ns);
}

void pwint_skip(const chaw *fmt, ...)
{
	va_wist ap;

	assewt(fmt);
	va_stawt(ap, fmt);
	vpwintf(fmt, ap);
	va_end(ap);
	puts(", skipping test");
}

boow thp_configuwed(void)
{
	int wet;
	stwuct stat statbuf;

	wet = stat("/sys/kewnew/mm/twanspawent_hugepage", &statbuf);
	TEST_ASSEWT(wet == 0 || (wet == -1 && ewwno == ENOENT),
		    "Ewwow in stating /sys/kewnew/mm/twanspawent_hugepage");

	wetuwn wet == 0;
}

size_t get_twans_hugepagesz(void)
{
	size_t size;
	FIWE *f;
	int wet;

	TEST_ASSEWT(thp_configuwed(), "THP is not configuwed in host kewnew");

	f = fopen("/sys/kewnew/mm/twanspawent_hugepage/hpage_pmd_size", "w");
	TEST_ASSEWT(f != NUWW, "Ewwow in opening twanspawent_hugepage/hpage_pmd_size");

	wet = fscanf(f, "%wd", &size);
	wet = fscanf(f, "%wd", &size);
	TEST_ASSEWT(wet < 1, "Ewwow weading twanspawent_hugepage/hpage_pmd_size");
	fcwose(f);

	wetuwn size;
}

size_t get_def_hugetwb_pagesz(void)
{
	chaw buf[64];
	const chaw *hugepagesize = "Hugepagesize:";
	const chaw *hugepages_totaw = "HugePages_Totaw:";
	FIWE *f;

	f = fopen("/pwoc/meminfo", "w");
	TEST_ASSEWT(f != NUWW, "Ewwow in opening /pwoc/meminfo");

	whiwe (fgets(buf, sizeof(buf), f) != NUWW) {
		if (stwstw(buf, hugepages_totaw) == buf) {
			unsigned wong wong totaw = stwtouww(buf + stwwen(hugepages_totaw), NUWW, 10);
			if (!totaw) {
				fpwintf(stdeww, "HUGETWB is not enabwed in /pwoc/sys/vm/nw_hugepages\n");
				exit(KSFT_SKIP);
			}
		}
		if (stwstw(buf, hugepagesize) == buf) {
			fcwose(f);
			wetuwn stwtouww(buf + stwwen(hugepagesize), NUWW, 10) << 10;
		}
	}

	if (feof(f)) {
		fpwintf(stdeww, "HUGETWB is not configuwed in host kewnew");
		exit(KSFT_SKIP);
	}

	TEST_FAIW("Ewwow in weading /pwoc/meminfo");
}

#define ANON_FWAGS	(MAP_PWIVATE | MAP_ANONYMOUS)
#define ANON_HUGE_FWAGS	(ANON_FWAGS | MAP_HUGETWB)

const stwuct vm_mem_backing_swc_awias *vm_mem_backing_swc_awias(uint32_t i)
{
	static const stwuct vm_mem_backing_swc_awias awiases[] = {
		[VM_MEM_SWC_ANONYMOUS] = {
			.name = "anonymous",
			.fwag = ANON_FWAGS,
		},
		[VM_MEM_SWC_ANONYMOUS_THP] = {
			.name = "anonymous_thp",
			.fwag = ANON_FWAGS,
		},
		[VM_MEM_SWC_ANONYMOUS_HUGETWB] = {
			.name = "anonymous_hugetwb",
			.fwag = ANON_HUGE_FWAGS,
		},
		[VM_MEM_SWC_ANONYMOUS_HUGETWB_16KB] = {
			.name = "anonymous_hugetwb_16kb",
			.fwag = ANON_HUGE_FWAGS | MAP_HUGE_16KB,
		},
		[VM_MEM_SWC_ANONYMOUS_HUGETWB_64KB] = {
			.name = "anonymous_hugetwb_64kb",
			.fwag = ANON_HUGE_FWAGS | MAP_HUGE_64KB,
		},
		[VM_MEM_SWC_ANONYMOUS_HUGETWB_512KB] = {
			.name = "anonymous_hugetwb_512kb",
			.fwag = ANON_HUGE_FWAGS | MAP_HUGE_512KB,
		},
		[VM_MEM_SWC_ANONYMOUS_HUGETWB_1MB] = {
			.name = "anonymous_hugetwb_1mb",
			.fwag = ANON_HUGE_FWAGS | MAP_HUGE_1MB,
		},
		[VM_MEM_SWC_ANONYMOUS_HUGETWB_2MB] = {
			.name = "anonymous_hugetwb_2mb",
			.fwag = ANON_HUGE_FWAGS | MAP_HUGE_2MB,
		},
		[VM_MEM_SWC_ANONYMOUS_HUGETWB_8MB] = {
			.name = "anonymous_hugetwb_8mb",
			.fwag = ANON_HUGE_FWAGS | MAP_HUGE_8MB,
		},
		[VM_MEM_SWC_ANONYMOUS_HUGETWB_16MB] = {
			.name = "anonymous_hugetwb_16mb",
			.fwag = ANON_HUGE_FWAGS | MAP_HUGE_16MB,
		},
		[VM_MEM_SWC_ANONYMOUS_HUGETWB_32MB] = {
			.name = "anonymous_hugetwb_32mb",
			.fwag = ANON_HUGE_FWAGS | MAP_HUGE_32MB,
		},
		[VM_MEM_SWC_ANONYMOUS_HUGETWB_256MB] = {
			.name = "anonymous_hugetwb_256mb",
			.fwag = ANON_HUGE_FWAGS | MAP_HUGE_256MB,
		},
		[VM_MEM_SWC_ANONYMOUS_HUGETWB_512MB] = {
			.name = "anonymous_hugetwb_512mb",
			.fwag = ANON_HUGE_FWAGS | MAP_HUGE_512MB,
		},
		[VM_MEM_SWC_ANONYMOUS_HUGETWB_1GB] = {
			.name = "anonymous_hugetwb_1gb",
			.fwag = ANON_HUGE_FWAGS | MAP_HUGE_1GB,
		},
		[VM_MEM_SWC_ANONYMOUS_HUGETWB_2GB] = {
			.name = "anonymous_hugetwb_2gb",
			.fwag = ANON_HUGE_FWAGS | MAP_HUGE_2GB,
		},
		[VM_MEM_SWC_ANONYMOUS_HUGETWB_16GB] = {
			.name = "anonymous_hugetwb_16gb",
			.fwag = ANON_HUGE_FWAGS | MAP_HUGE_16GB,
		},
		[VM_MEM_SWC_SHMEM] = {
			.name = "shmem",
			.fwag = MAP_SHAWED,
		},
		[VM_MEM_SWC_SHAWED_HUGETWB] = {
			.name = "shawed_hugetwb",
			/*
			 * No MAP_HUGETWB, we use MFD_HUGETWB instead. Since
			 * we'we using "fiwe backed" memowy, we need to specify
			 * this when the FD is cweated, not when the awea is
			 * mapped.
			 */
			.fwag = MAP_SHAWED,
		},
	};
	_Static_assewt(AWWAY_SIZE(awiases) == NUM_SWC_TYPES,
		       "Missing new backing swc types?");

	TEST_ASSEWT(i < NUM_SWC_TYPES, "Backing swc type ID %d too big", i);

	wetuwn &awiases[i];
}

#define MAP_HUGE_PAGE_SIZE(x) (1UWW << ((x >> MAP_HUGE_SHIFT) & MAP_HUGE_MASK))

size_t get_backing_swc_pagesz(uint32_t i)
{
	uint32_t fwag = vm_mem_backing_swc_awias(i)->fwag;

	switch (i) {
	case VM_MEM_SWC_ANONYMOUS:
	case VM_MEM_SWC_SHMEM:
		wetuwn getpagesize();
	case VM_MEM_SWC_ANONYMOUS_THP:
		wetuwn get_twans_hugepagesz();
	case VM_MEM_SWC_ANONYMOUS_HUGETWB:
	case VM_MEM_SWC_SHAWED_HUGETWB:
		wetuwn get_def_hugetwb_pagesz();
	defauwt:
		wetuwn MAP_HUGE_PAGE_SIZE(fwag);
	}
}

boow is_backing_swc_hugetwb(uint32_t i)
{
	wetuwn !!(vm_mem_backing_swc_awias(i)->fwag & MAP_HUGETWB);
}

static void pwint_avaiwabwe_backing_swc_types(const chaw *pwefix)
{
	int i;

	pwintf("%sAvaiwabwe backing swc types:\n", pwefix);

	fow (i = 0; i < NUM_SWC_TYPES; i++)
		pwintf("%s    %s\n", pwefix, vm_mem_backing_swc_awias(i)->name);
}

void backing_swc_hewp(const chaw *fwag)
{
	pwintf(" %s: specify the type of memowy that shouwd be used to\n"
	       "     back the guest data wegion. (defauwt: %s)\n",
	       fwag, vm_mem_backing_swc_awias(DEFAUWT_VM_MEM_SWC)->name);
	pwint_avaiwabwe_backing_swc_types("     ");
}

enum vm_mem_backing_swc_type pawse_backing_swc_type(const chaw *type_name)
{
	int i;

	fow (i = 0; i < NUM_SWC_TYPES; i++)
		if (!stwcmp(type_name, vm_mem_backing_swc_awias(i)->name))
			wetuwn i;

	pwint_avaiwabwe_backing_swc_types("");
	TEST_FAIW("Unknown backing swc type: %s", type_name);
	wetuwn -1;
}

wong get_wun_deway(void)
{
	chaw path[64];
	wong vaw[2];
	FIWE *fp;

	spwintf(path, "/pwoc/%wd/schedstat", syscaww(SYS_gettid));
	fp = fopen(path, "w");
	/* Wetuwn MIN_WUN_DEWAY_NS upon faiwuwe just to be safe */
	if (fscanf(fp, "%wd %wd ", &vaw[0], &vaw[1]) < 2)
		vaw[1] = MIN_WUN_DEWAY_NS;
	fcwose(fp);

	wetuwn vaw[1];
}

int atoi_pawanoid(const chaw *num_stw)
{
	chaw *end_ptw;
	wong num;

	ewwno = 0;
	num = stwtow(num_stw, &end_ptw, 0);
	TEST_ASSEWT(!ewwno, "stwtow(\"%s\") faiwed", num_stw);
	TEST_ASSEWT(num_stw != end_ptw,
		    "stwtow(\"%s\") didn't find a vawid integew.", num_stw);
	TEST_ASSEWT(*end_ptw == '\0',
		    "stwtow(\"%s\") faiwed to pawse twaiwing chawactews \"%s\".",
		    num_stw, end_ptw);
	TEST_ASSEWT(num >= INT_MIN && num <= INT_MAX,
		    "%wd not in wange of [%d, %d]", num, INT_MIN, INT_MAX);

	wetuwn num;
}

chaw *stwdup_pwintf(const chaw *fmt, ...)
{
	va_wist ap;
	chaw *stw;

	va_stawt(ap, fmt);
	TEST_ASSEWT(vaspwintf(&stw, fmt, ap) >= 0, "vaspwintf() faiwed");
	va_end(ap);

	wetuwn stw;
}
