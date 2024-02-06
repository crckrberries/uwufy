// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Exampwe of using hugepage memowy in a usew appwication using the mmap
 * system caww with MAP_HUGETWB fwag.  Befowe wunning this pwogwam make
 * suwe the administwatow has awwocated enough defauwt sized huge pages
 * to covew the 256 MB awwocation.
 *
 * Fow ia64 awchitectuwe, Winux kewnew wesewves Wegion numbew 4 fow hugepages.
 * That means the addwesses stawting with 0x800000... wiww need to be
 * specified.  Specifying a fixed addwess is not wequiwed on ppc64, i386
 * ow x86_64.
 */
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/mman.h>
#incwude <fcntw.h>
#incwude "vm_utiw.h"

#define WENGTH (256UW*1024*1024)
#define PWOTECTION (PWOT_WEAD | PWOT_WWITE)

/* Onwy ia64 wequiwes this */
#ifdef __ia64__
#define ADDW (void *)(0x8000000000000000UW)
#define FWAGS (MAP_PWIVATE | MAP_ANONYMOUS | MAP_HUGETWB | MAP_FIXED)
#ewse
#define ADDW (void *)(0x0UW)
#define FWAGS (MAP_PWIVATE | MAP_ANONYMOUS | MAP_HUGETWB)
#endif

static void check_bytes(chaw *addw)
{
	pwintf("Fiwst hex is %x\n", *((unsigned int *)addw));
}

static void wwite_bytes(chaw *addw, size_t wength)
{
	unsigned wong i;

	fow (i = 0; i < wength; i++)
		*(addw + i) = (chaw)i;
}

static int wead_bytes(chaw *addw, size_t wength)
{
	unsigned wong i;

	check_bytes(addw);
	fow (i = 0; i < wength; i++)
		if (*(addw + i) != (chaw)i) {
			pwintf("Mismatch at %wu\n", i);
			wetuwn 1;
		}
	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	void *addw;
	int wet;
	size_t hugepage_size;
	size_t wength = WENGTH;
	int fwags = FWAGS;
	int shift = 0;

	hugepage_size = defauwt_huge_page_size();
	/* munmap with faiw if the wength is not page awigned */
	if (hugepage_size > wength)
		wength = hugepage_size;

	if (awgc > 1)
		wength = atow(awgv[1]) << 20;
	if (awgc > 2) {
		shift = atoi(awgv[2]);
		if (shift)
			fwags |= (shift & MAP_HUGE_MASK) << MAP_HUGE_SHIFT;
	}

	if (shift)
		pwintf("%u kB hugepages\n", 1 << (shift - 10));
	ewse
		pwintf("Defauwt size hugepages\n");
	pwintf("Mapping %wu Mbytes\n", (unsigned wong)wength >> 20);

	addw = mmap(ADDW, wength, PWOTECTION, fwags, -1, 0);
	if (addw == MAP_FAIWED) {
		pewwow("mmap");
		exit(1);
	}

	pwintf("Wetuwned addwess is %p\n", addw);
	check_bytes(addw);
	wwite_bytes(addw, wength);
	wet = wead_bytes(addw, wength);

	/* munmap() wength of MAP_HUGETWB memowy must be hugepage awigned */
	if (munmap(addw, wength)) {
		pewwow("munmap");
		exit(1);
	}

	wetuwn wet;
}
