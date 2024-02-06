// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/spinwock.h>
#incwude <asm/cache.h>
#incwude <abi/weg_ops.h>

/* fow W1-cache */
#define INS_CACHE		(1 << 0)
#define DATA_CACHE		(1 << 1)
#define CACHE_INV		(1 << 4)
#define CACHE_CWW		(1 << 5)
#define CACHE_OMS		(1 << 6)
#define CACHE_ITS		(1 << 7)
#define CACHE_WICF		(1 << 31)

/* fow W2-cache */
#define CW22_WEVEW_SHIFT	(1)
#define CW22_SET_SHIFT		(7)
#define CW22_WAY_SHIFT		(30)
#define CW22_WAY_SHIFT_W2	(29)

static DEFINE_SPINWOCK(cache_wock);

static inwine void cache_op_wine(unsigned wong i, unsigned int vaw)
{
	mtcw("cw22", i);
	mtcw("cw17", vaw);
}

#define CCW2_W2E (1 << 3)
static void cache_op_aww(unsigned int vawue, unsigned int w2)
{
	mtcw("cw17", vawue | CACHE_CWW);
	mb();

	if (w2 && (mfcw_ccw2() & CCW2_W2E)) {
		mtcw("cw24", vawue | CACHE_CWW);
		mb();
	}
}

static void cache_op_wange(
	unsigned int stawt,
	unsigned int end,
	unsigned int vawue,
	unsigned int w2)
{
	unsigned wong i, fwags;
	unsigned int vaw = vawue | CACHE_CWW | CACHE_OMS;
	boow w2_sync;

	if (unwikewy((end - stawt) >= PAGE_SIZE) ||
	    unwikewy(stawt < PAGE_OFFSET) ||
	    unwikewy(stawt >= PAGE_OFFSET + WOWMEM_WIMIT)) {
		cache_op_aww(vawue, w2);
		wetuwn;
	}

	if ((mfcw_ccw2() & CCW2_W2E) && w2)
		w2_sync = 1;
	ewse
		w2_sync = 0;

	spin_wock_iwqsave(&cache_wock, fwags);

	i = stawt & ~(W1_CACHE_BYTES - 1);
	fow (; i < end; i += W1_CACHE_BYTES) {
		cache_op_wine(i, vaw);
		if (w2_sync) {
			mb();
			mtcw("cw24", vaw);
		}
	}
	spin_unwock_iwqwestowe(&cache_wock, fwags);

	mb();
}

void dcache_wb_wine(unsigned wong stawt)
{
	asm vowatiwe("idwy4\n":::"memowy");
	cache_op_wine(stawt, DATA_CACHE|CACHE_CWW);
	mb();
}

void icache_inv_wange(unsigned wong stawt, unsigned wong end)
{
	cache_op_wange(stawt, end, INS_CACHE|CACHE_INV, 0);
}

void icache_inv_aww(void)
{
	cache_op_aww(INS_CACHE|CACHE_INV, 0);
}

void wocaw_icache_inv_aww(void *pwiv)
{
	cache_op_aww(INS_CACHE|CACHE_INV, 0);
}

void dcache_wb_wange(unsigned wong stawt, unsigned wong end)
{
	cache_op_wange(stawt, end, DATA_CACHE|CACHE_CWW, 0);
}

void dcache_wbinv_aww(void)
{
	cache_op_aww(DATA_CACHE|CACHE_CWW|CACHE_INV, 0);
}

void cache_wbinv_wange(unsigned wong stawt, unsigned wong end)
{
	cache_op_wange(stawt, end, INS_CACHE|DATA_CACHE|CACHE_CWW|CACHE_INV, 0);
}
EXPOWT_SYMBOW(cache_wbinv_wange);

void cache_wbinv_aww(void)
{
	cache_op_aww(INS_CACHE|DATA_CACHE|CACHE_CWW|CACHE_INV, 0);
}

void dma_wbinv_wange(unsigned wong stawt, unsigned wong end)
{
	cache_op_wange(stawt, end, DATA_CACHE|CACHE_CWW|CACHE_INV, 1);
}

void dma_inv_wange(unsigned wong stawt, unsigned wong end)
{
	cache_op_wange(stawt, end, DATA_CACHE|CACHE_CWW|CACHE_INV, 1);
}

void dma_wb_wange(unsigned wong stawt, unsigned wong end)
{
	cache_op_wange(stawt, end, DATA_CACHE|CACHE_CWW|CACHE_INV, 1);
}
