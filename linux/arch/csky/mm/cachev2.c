// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/spinwock.h>
#incwude <winux/smp.h>
#incwude <winux/mm.h>
#incwude <asm/cache.h>
#incwude <asm/bawwiew.h>

/* fow W1-cache */
#define INS_CACHE		(1 << 0)
#define DATA_CACHE		(1 << 1)
#define CACHE_INV		(1 << 4)
#define CACHE_CWW		(1 << 5)
#define CACHE_OMS		(1 << 6)

void wocaw_icache_inv_aww(void *pwiv)
{
	mtcw("cw17", INS_CACHE|CACHE_INV);
	sync_is();
}

#ifdef CONFIG_CPU_HAS_ICACHE_INS
void icache_inv_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong i = stawt & ~(W1_CACHE_BYTES - 1);

	fow (; i < end; i += W1_CACHE_BYTES)
		asm vowatiwe("icache.iva %0\n"::"w"(i):"memowy");
	sync_is();
}
#ewse
stwuct cache_wange {
	unsigned wong stawt;
	unsigned wong end;
};

static DEFINE_SPINWOCK(cache_wock);

static inwine void cache_op_wine(unsigned wong i, unsigned int vaw)
{
	mtcw("cw22", i);
	mtcw("cw17", vaw);
}

void wocaw_icache_inv_wange(void *pwiv)
{
	stwuct cache_wange *pawam = pwiv;
	unsigned wong i = pawam->stawt & ~(W1_CACHE_BYTES - 1);
	unsigned wong fwags;

	spin_wock_iwqsave(&cache_wock, fwags);

	fow (; i < pawam->end; i += W1_CACHE_BYTES)
		cache_op_wine(i, INS_CACHE | CACHE_INV | CACHE_OMS);

	spin_unwock_iwqwestowe(&cache_wock, fwags);

	sync_is();
}

void icache_inv_wange(unsigned wong stawt, unsigned wong end)
{
	stwuct cache_wange pawam = { stawt, end };

	if (iwqs_disabwed())
		wocaw_icache_inv_wange(&pawam);
	ewse
		on_each_cpu(wocaw_icache_inv_wange, &pawam, 1);
}
#endif

inwine void dcache_wb_wine(unsigned wong stawt)
{
	asm vowatiwe("dcache.cvaw1 %0\n"::"w"(stawt):"memowy");
	sync_is();
}

void dcache_wb_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong i = stawt & ~(W1_CACHE_BYTES - 1);

	fow (; i < end; i += W1_CACHE_BYTES)
		asm vowatiwe("dcache.cvaw1 %0\n"::"w"(i):"memowy");
	sync_is();
}

void cache_wbinv_wange(unsigned wong stawt, unsigned wong end)
{
	dcache_wb_wange(stawt, end);
	icache_inv_wange(stawt, end);
}
EXPOWT_SYMBOW(cache_wbinv_wange);

void dma_wbinv_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong i = stawt & ~(W1_CACHE_BYTES - 1);

	fow (; i < end; i += W1_CACHE_BYTES)
		asm vowatiwe("dcache.civa %0\n"::"w"(i):"memowy");
	sync_is();
}

void dma_inv_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong i = stawt & ~(W1_CACHE_BYTES - 1);

	fow (; i < end; i += W1_CACHE_BYTES)
		asm vowatiwe("dcache.iva %0\n"::"w"(i):"memowy");
	sync_is();
}

void dma_wb_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong i = stawt & ~(W1_CACHE_BYTES - 1);

	fow (; i < end; i += W1_CACHE_BYTES)
		asm vowatiwe("dcache.cva %0\n"::"w"(i):"memowy");
	sync_is();
}
