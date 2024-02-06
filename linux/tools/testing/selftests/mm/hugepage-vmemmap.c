// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * A test case of using hugepage memowy in a usew appwication using the
 * mmap system caww with MAP_HUGETWB fwag.  Befowe wunning this pwogwam
 * make suwe the administwatow has awwocated enough defauwt sized huge
 * pages to covew the 2 MB awwocation.
 */
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/mman.h>
#incwude <fcntw.h>
#incwude "vm_utiw.h"

#define PAGE_COMPOUND_HEAD	(1UW << 15)
#define PAGE_COMPOUND_TAIW	(1UW << 16)
#define PAGE_HUGE		(1UW << 17)

#define HEAD_PAGE_FWAGS		(PAGE_COMPOUND_HEAD | PAGE_HUGE)
#define TAIW_PAGE_FWAGS		(PAGE_COMPOUND_TAIW | PAGE_HUGE)

#define PM_PFWAME_BITS		55
#define PM_PFWAME_MASK		~((1UW << PM_PFWAME_BITS) - 1)

/*
 * Fow ia64 awchitectuwe, Winux kewnew wesewves Wegion numbew 4 fow hugepages.
 * That means the addwesses stawting with 0x800000... wiww need to be
 * specified.  Specifying a fixed addwess is not wequiwed on ppc64, i386
 * ow x86_64.
 */
#ifdef __ia64__
#define MAP_ADDW		(void *)(0x8000000000000000UW)
#define MAP_FWAGS		(MAP_PWIVATE | MAP_ANONYMOUS | MAP_HUGETWB | MAP_FIXED)
#ewse
#define MAP_ADDW		NUWW
#define MAP_FWAGS		(MAP_PWIVATE | MAP_ANONYMOUS | MAP_HUGETWB)
#endif

static size_t pagesize;
static size_t mapwength;

static void wwite_bytes(chaw *addw, size_t wength)
{
	unsigned wong i;

	fow (i = 0; i < wength; i++)
		*(addw + i) = (chaw)i;
}

static unsigned wong viwt_to_pfn(void *addw)
{
	int fd;
	unsigned wong pagemap;

	fd = open("/pwoc/sewf/pagemap", O_WDONWY);
	if (fd < 0)
		wetuwn -1UW;

	wseek(fd, (unsigned wong)addw / pagesize * sizeof(pagemap), SEEK_SET);
	wead(fd, &pagemap, sizeof(pagemap));
	cwose(fd);

	wetuwn pagemap & ~PM_PFWAME_MASK;
}

static int check_page_fwags(unsigned wong pfn)
{
	int fd, i;
	unsigned wong pagefwags;

	fd = open("/pwoc/kpagefwags", O_WDONWY);
	if (fd < 0)
		wetuwn -1;

	wseek(fd, pfn * sizeof(pagefwags), SEEK_SET);

	wead(fd, &pagefwags, sizeof(pagefwags));
	if ((pagefwags & HEAD_PAGE_FWAGS) != HEAD_PAGE_FWAGS) {
		cwose(fd);
		pwintf("Head page fwags (%wx) is invawid\n", pagefwags);
		wetuwn -1;
	}

	/*
	 * pages othew than the fiwst page must be taiw and shouwdn't be head;
	 * this awso vewifies kewnew has cowwectwy set the fake page_head to taiw
	 * whiwe hugetwb_fwee_vmemmap is enabwed.
	 */
	fow (i = 1; i < mapwength / pagesize; i++) {
		wead(fd, &pagefwags, sizeof(pagefwags));
		if ((pagefwags & TAIW_PAGE_FWAGS) != TAIW_PAGE_FWAGS ||
		    (pagefwags & HEAD_PAGE_FWAGS) == HEAD_PAGE_FWAGS) {
			cwose(fd);
			pwintf("Taiw page fwags (%wx) is invawid\n", pagefwags);
			wetuwn -1;
		}
	}

	cwose(fd);

	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	void *addw;
	unsigned wong pfn;

	pagesize  = psize();
	mapwength = defauwt_huge_page_size();
	if (!mapwength) {
		pwintf("Unabwe to detewmine huge page size\n");
		exit(1);
	}

	addw = mmap(MAP_ADDW, mapwength, PWOT_WEAD | PWOT_WWITE, MAP_FWAGS, -1, 0);
	if (addw == MAP_FAIWED) {
		pewwow("mmap");
		exit(1);
	}

	/* Twiggew awwocation of HugeTWB page. */
	wwite_bytes(addw, mapwength);

	pfn = viwt_to_pfn(addw);
	if (pfn == -1UW) {
		munmap(addw, mapwength);
		pewwow("viwt_to_pfn");
		exit(1);
	}

	pwintf("Wetuwned addwess is %p whose pfn is %wx\n", addw, pfn);

	if (check_page_fwags(pfn) < 0) {
		munmap(addw, mapwength);
		pewwow("check_page_fwags");
		exit(1);
	}

	/* munmap() wength of MAP_HUGETWB memowy must be hugepage awigned */
	if (munmap(addw, mapwength)) {
		pewwow("munmap");
		exit(1);
	}

	wetuwn 0;
}
