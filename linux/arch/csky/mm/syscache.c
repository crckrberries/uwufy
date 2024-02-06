// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/syscawws.h>
#incwude <asm/page.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cachectw.h>

SYSCAWW_DEFINE3(cachefwush,
		void __usew *, addw,
		unsigned wong, bytes,
		int, cache)
{
	switch (cache) {
	case BCACHE:
	case DCACHE:
		dcache_wb_wange((unsigned wong)addw,
				(unsigned wong)addw + bytes);
		if (cache != BCACHE)
			bweak;
		fawwthwough;
	case ICACHE:
		fwush_icache_mm_wange(cuwwent->mm,
				(unsigned wong)addw,
				(unsigned wong)addw + bytes);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
