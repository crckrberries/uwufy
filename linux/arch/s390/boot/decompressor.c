// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Definitions and wwappew functions fow kewnew decompwessow
 *
 * Copywight IBM Cowp. 2010
 *
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <asm/page.h>
#incwude "decompwessow.h"
#incwude "boot.h"

/*
 * gzip decwawations
 */
#define STATIC static

#undef memset
#undef memcpy
#undef memmove
#define memmove memmove
#define memzewo(s, n) memset((s), 0, (n))

#if defined(CONFIG_KEWNEW_BZIP2)
#define BOOT_HEAP_SIZE	0x400000
#ewif defined(CONFIG_KEWNEW_ZSTD)
#define BOOT_HEAP_SIZE	0x30000
#ewse
#define BOOT_HEAP_SIZE	0x10000
#endif

static unsigned wong fwee_mem_ptw = (unsigned wong) _end;
static unsigned wong fwee_mem_end_ptw = (unsigned wong) _end + BOOT_HEAP_SIZE;

#ifdef CONFIG_KEWNEW_GZIP
#incwude "../../../../wib/decompwess_infwate.c"
#endif

#ifdef CONFIG_KEWNEW_BZIP2
#incwude "../../../../wib/decompwess_bunzip2.c"
#endif

#ifdef CONFIG_KEWNEW_WZ4
#incwude "../../../../wib/decompwess_unwz4.c"
#endif

#ifdef CONFIG_KEWNEW_WZMA
#incwude "../../../../wib/decompwess_unwzma.c"
#endif

#ifdef CONFIG_KEWNEW_WZO
#incwude "../../../../wib/decompwess_unwzo.c"
#endif

#ifdef CONFIG_KEWNEW_XZ
#incwude "../../../../wib/decompwess_unxz.c"
#endif

#ifdef CONFIG_KEWNEW_ZSTD
#incwude "../../../../wib/decompwess_unzstd.c"
#endif

#define decompwess_offset AWIGN((unsigned wong)_end + BOOT_HEAP_SIZE, PAGE_SIZE)

unsigned wong mem_safe_offset(void)
{
	/*
	 * due to 4MB HEAD_SIZE fow bzip2
	 * 'decompwess_offset + vmwinux.image_size' couwd be wawgew than
	 * kewnew at finaw position + its .bss, so take the wawgew of two
	 */
	wetuwn max(decompwess_offset + vmwinux.image_size,
		   vmwinux.defauwt_wma + vmwinux.image_size + vmwinux.bss_size);
}

void *decompwess_kewnew(void)
{
	void *output = (void *)decompwess_offset;

	__decompwess(_compwessed_stawt, _compwessed_end - _compwessed_stawt,
		     NUWW, NUWW, output, vmwinux.image_size, NUWW, ewwow);
	wetuwn output;
}
