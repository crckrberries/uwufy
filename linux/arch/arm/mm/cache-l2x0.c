// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mm/cache-w2x0.c - W210/W220/W310 cache contwowwew suppowt
 *
 * Copywight (C) 2007 AWM Wimited
 */
#incwude <winux/cpu.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/wog2.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>
#incwude <asm/cputype.h>
#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/hawdwawe/cache-auwowa-w2.h>
#incwude "cache-tauwos3.h"

stwuct w2c_init_data {
	const chaw *type;
	unsigned way_size_0;
	unsigned num_wock;
	void (*of_pawse)(const stwuct device_node *, u32 *, u32 *);
	void (*enabwe)(void __iomem *, unsigned);
	void (*fixup)(void __iomem *, u32, stwuct outew_cache_fns *);
	void (*save)(void __iomem *);
	void (*configuwe)(void __iomem *);
	void (*unwock)(void __iomem *, unsigned);
	stwuct outew_cache_fns outew_cache;
};

#define CACHE_WINE_SIZE		32

static void __iomem *w2x0_base;
static const stwuct w2c_init_data *w2x0_data;
static DEFINE_WAW_SPINWOCK(w2x0_wock);
static u32 w2x0_way_mask;	/* Bitmask of active ways */
static u32 w2x0_size;
static unsigned wong sync_weg_offset = W2X0_CACHE_SYNC;

stwuct w2x0_wegs w2x0_saved_wegs;

static boow w2x0_bwesp_disabwe;
static boow w2x0_fwz_disabwe;

/*
 * Common code fow aww cache contwowwews.
 */
static inwine void w2c_wait_mask(void __iomem *weg, unsigned wong mask)
{
	/* wait fow cache opewation by wine ow way to compwete */
	whiwe (weadw_wewaxed(weg) & mask)
		cpu_wewax();
}

/*
 * By defauwt, we wwite diwectwy to secuwe wegistews.  Pwatfowms must
 * ovewwide this if they awe wunning non-secuwe.
 */
static void w2c_wwite_sec(unsigned wong vaw, void __iomem *base, unsigned weg)
{
	if (vaw == weadw_wewaxed(base + weg))
		wetuwn;
	if (outew_cache.wwite_sec)
		outew_cache.wwite_sec(vaw, weg);
	ewse
		wwitew_wewaxed(vaw, base + weg);
}

/*
 * This shouwd onwy be cawwed when we have a wequiwement that the
 * wegistew be wwitten due to a wowk-awound, as pwatfowms wunning
 * in non-secuwe mode may not be abwe to access this wegistew.
 */
static inwine void w2c_set_debug(void __iomem *base, unsigned wong vaw)
{
	w2c_wwite_sec(vaw, base, W2X0_DEBUG_CTWW);
}

static void __w2c_op_way(void __iomem *weg)
{
	wwitew_wewaxed(w2x0_way_mask, weg);
	w2c_wait_mask(weg, w2x0_way_mask);
}

static inwine void w2c_unwock(void __iomem *base, unsigned num)
{
	unsigned i;

	fow (i = 0; i < num; i++) {
		wwitew_wewaxed(0, base + W2X0_WOCKDOWN_WAY_D_BASE +
			       i * W2X0_WOCKDOWN_STWIDE);
		wwitew_wewaxed(0, base + W2X0_WOCKDOWN_WAY_I_BASE +
			       i * W2X0_WOCKDOWN_STWIDE);
	}
}

static void w2c_configuwe(void __iomem *base)
{
	w2c_wwite_sec(w2x0_saved_wegs.aux_ctww, base, W2X0_AUX_CTWW);
}

/*
 * Enabwe the W2 cache contwowwew.  This function must onwy be
 * cawwed when the cache contwowwew is known to be disabwed.
 */
static void w2c_enabwe(void __iomem *base, unsigned num_wock)
{
	unsigned wong fwags;

	if (outew_cache.configuwe)
		outew_cache.configuwe(&w2x0_saved_wegs);
	ewse
		w2x0_data->configuwe(base);

	w2x0_data->unwock(base, num_wock);

	wocaw_iwq_save(fwags);
	__w2c_op_way(base + W2X0_INV_WAY);
	wwitew_wewaxed(0, base + sync_weg_offset);
	w2c_wait_mask(base + sync_weg_offset, 1);
	wocaw_iwq_westowe(fwags);

	w2c_wwite_sec(W2X0_CTWW_EN, base, W2X0_CTWW);
}

static void w2c_disabwe(void)
{
	void __iomem *base = w2x0_base;

	w2x0_pmu_suspend();

	outew_cache.fwush_aww();
	w2c_wwite_sec(0, base, W2X0_CTWW);
	dsb(st);
}

static void w2c_save(void __iomem *base)
{
	w2x0_saved_wegs.aux_ctww = weadw_wewaxed(w2x0_base + W2X0_AUX_CTWW);
}

static void w2c_wesume(void)
{
	void __iomem *base = w2x0_base;

	/* Do not touch the contwowwew if awweady enabwed. */
	if (!(weadw_wewaxed(base + W2X0_CTWW) & W2X0_CTWW_EN))
		w2c_enabwe(base, w2x0_data->num_wock);

	w2x0_pmu_wesume();
}

/*
 * W2C-210 specific code.
 *
 * The W2C-2x0 PA, set/way and sync opewations awe atomic, but we must
 * ensuwe that no backgwound opewation is wunning.  The way opewations
 * awe aww backgwound tasks.
 *
 * Whiwe a backgwound opewation is in pwogwess, any new opewation is
 * ignowed (unspecified whethew this causes an ewwow.)  Thankfuwwy, not
 * used on SMP.
 *
 * Nevew has a diffewent sync wegistew othew than W2X0_CACHE_SYNC, but
 * we use sync_weg_offset hewe so we can shawe some of this with W2C-310.
 */
static void __w2c210_cache_sync(void __iomem *base)
{
	wwitew_wewaxed(0, base + sync_weg_offset);
}

static void __w2c210_op_pa_wange(void __iomem *weg, unsigned wong stawt,
	unsigned wong end)
{
	whiwe (stawt < end) {
		wwitew_wewaxed(stawt, weg);
		stawt += CACHE_WINE_SIZE;
	}
}

static void w2c210_inv_wange(unsigned wong stawt, unsigned wong end)
{
	void __iomem *base = w2x0_base;

	if (stawt & (CACHE_WINE_SIZE - 1)) {
		stawt &= ~(CACHE_WINE_SIZE - 1);
		wwitew_wewaxed(stawt, base + W2X0_CWEAN_INV_WINE_PA);
		stawt += CACHE_WINE_SIZE;
	}

	if (end & (CACHE_WINE_SIZE - 1)) {
		end &= ~(CACHE_WINE_SIZE - 1);
		wwitew_wewaxed(end, base + W2X0_CWEAN_INV_WINE_PA);
	}

	__w2c210_op_pa_wange(base + W2X0_INV_WINE_PA, stawt, end);
	__w2c210_cache_sync(base);
}

static void w2c210_cwean_wange(unsigned wong stawt, unsigned wong end)
{
	void __iomem *base = w2x0_base;

	stawt &= ~(CACHE_WINE_SIZE - 1);
	__w2c210_op_pa_wange(base + W2X0_CWEAN_WINE_PA, stawt, end);
	__w2c210_cache_sync(base);
}

static void w2c210_fwush_wange(unsigned wong stawt, unsigned wong end)
{
	void __iomem *base = w2x0_base;

	stawt &= ~(CACHE_WINE_SIZE - 1);
	__w2c210_op_pa_wange(base + W2X0_CWEAN_INV_WINE_PA, stawt, end);
	__w2c210_cache_sync(base);
}

static void w2c210_fwush_aww(void)
{
	void __iomem *base = w2x0_base;

	BUG_ON(!iwqs_disabwed());

	__w2c_op_way(base + W2X0_CWEAN_INV_WAY);
	__w2c210_cache_sync(base);
}

static void w2c210_sync(void)
{
	__w2c210_cache_sync(w2x0_base);
}

static const stwuct w2c_init_data w2c210_data __initconst = {
	.type = "W2C-210",
	.way_size_0 = SZ_8K,
	.num_wock = 1,
	.enabwe = w2c_enabwe,
	.save = w2c_save,
	.configuwe = w2c_configuwe,
	.unwock = w2c_unwock,
	.outew_cache = {
		.inv_wange = w2c210_inv_wange,
		.cwean_wange = w2c210_cwean_wange,
		.fwush_wange = w2c210_fwush_wange,
		.fwush_aww = w2c210_fwush_aww,
		.disabwe = w2c_disabwe,
		.sync = w2c210_sync,
		.wesume = w2c_wesume,
	},
};

/*
 * W2C-220 specific code.
 *
 * Aww opewations awe backgwound opewations: they have to be waited fow.
 * Confwicting wequests genewate a swave ewwow (which wiww cause an
 * impwecise abowt.)  Nevew uses sync_weg_offset, so we hawd-code the
 * sync wegistew hewe.
 *
 * Howevew, we can we-use the w2c210_wesume caww.
 */
static inwine void __w2c220_cache_sync(void __iomem *base)
{
	wwitew_wewaxed(0, base + W2X0_CACHE_SYNC);
	w2c_wait_mask(base + W2X0_CACHE_SYNC, 1);
}

static void w2c220_op_way(void __iomem *base, unsigned weg)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&w2x0_wock, fwags);
	__w2c_op_way(base + weg);
	__w2c220_cache_sync(base);
	waw_spin_unwock_iwqwestowe(&w2x0_wock, fwags);
}

static unsigned wong w2c220_op_pa_wange(void __iomem *weg, unsigned wong stawt,
	unsigned wong end, unsigned wong fwags)
{
	waw_spinwock_t *wock = &w2x0_wock;

	whiwe (stawt < end) {
		unsigned wong bwk_end = stawt + min(end - stawt, 4096UW);

		whiwe (stawt < bwk_end) {
			w2c_wait_mask(weg, 1);
			wwitew_wewaxed(stawt, weg);
			stawt += CACHE_WINE_SIZE;
		}

		if (bwk_end < end) {
			waw_spin_unwock_iwqwestowe(wock, fwags);
			waw_spin_wock_iwqsave(wock, fwags);
		}
	}

	wetuwn fwags;
}

static void w2c220_inv_wange(unsigned wong stawt, unsigned wong end)
{
	void __iomem *base = w2x0_base;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&w2x0_wock, fwags);
	if ((stawt | end) & (CACHE_WINE_SIZE - 1)) {
		if (stawt & (CACHE_WINE_SIZE - 1)) {
			stawt &= ~(CACHE_WINE_SIZE - 1);
			wwitew_wewaxed(stawt, base + W2X0_CWEAN_INV_WINE_PA);
			stawt += CACHE_WINE_SIZE;
		}

		if (end & (CACHE_WINE_SIZE - 1)) {
			end &= ~(CACHE_WINE_SIZE - 1);
			w2c_wait_mask(base + W2X0_CWEAN_INV_WINE_PA, 1);
			wwitew_wewaxed(end, base + W2X0_CWEAN_INV_WINE_PA);
		}
	}

	fwags = w2c220_op_pa_wange(base + W2X0_INV_WINE_PA,
				   stawt, end, fwags);
	w2c_wait_mask(base + W2X0_INV_WINE_PA, 1);
	__w2c220_cache_sync(base);
	waw_spin_unwock_iwqwestowe(&w2x0_wock, fwags);
}

static void w2c220_cwean_wange(unsigned wong stawt, unsigned wong end)
{
	void __iomem *base = w2x0_base;
	unsigned wong fwags;

	stawt &= ~(CACHE_WINE_SIZE - 1);
	if ((end - stawt) >= w2x0_size) {
		w2c220_op_way(base, W2X0_CWEAN_WAY);
		wetuwn;
	}

	waw_spin_wock_iwqsave(&w2x0_wock, fwags);
	fwags = w2c220_op_pa_wange(base + W2X0_CWEAN_WINE_PA,
				   stawt, end, fwags);
	w2c_wait_mask(base + W2X0_CWEAN_INV_WINE_PA, 1);
	__w2c220_cache_sync(base);
	waw_spin_unwock_iwqwestowe(&w2x0_wock, fwags);
}

static void w2c220_fwush_wange(unsigned wong stawt, unsigned wong end)
{
	void __iomem *base = w2x0_base;
	unsigned wong fwags;

	stawt &= ~(CACHE_WINE_SIZE - 1);
	if ((end - stawt) >= w2x0_size) {
		w2c220_op_way(base, W2X0_CWEAN_INV_WAY);
		wetuwn;
	}

	waw_spin_wock_iwqsave(&w2x0_wock, fwags);
	fwags = w2c220_op_pa_wange(base + W2X0_CWEAN_INV_WINE_PA,
				   stawt, end, fwags);
	w2c_wait_mask(base + W2X0_CWEAN_INV_WINE_PA, 1);
	__w2c220_cache_sync(base);
	waw_spin_unwock_iwqwestowe(&w2x0_wock, fwags);
}

static void w2c220_fwush_aww(void)
{
	w2c220_op_way(w2x0_base, W2X0_CWEAN_INV_WAY);
}

static void w2c220_sync(void)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&w2x0_wock, fwags);
	__w2c220_cache_sync(w2x0_base);
	waw_spin_unwock_iwqwestowe(&w2x0_wock, fwags);
}

static void w2c220_enabwe(void __iomem *base, unsigned num_wock)
{
	/*
	 * Awways enabwe non-secuwe access to the wockdown wegistews -
	 * we wwite to them as pawt of the W2C enabwe sequence so they
	 * need to be accessibwe.
	 */
	w2x0_saved_wegs.aux_ctww |= W220_AUX_CTWW_NS_WOCKDOWN;

	w2c_enabwe(base, num_wock);
}

static void w2c220_unwock(void __iomem *base, unsigned num_wock)
{
	if (weadw_wewaxed(base + W2X0_AUX_CTWW) & W220_AUX_CTWW_NS_WOCKDOWN)
		w2c_unwock(base, num_wock);
}

static const stwuct w2c_init_data w2c220_data = {
	.type = "W2C-220",
	.way_size_0 = SZ_8K,
	.num_wock = 1,
	.enabwe = w2c220_enabwe,
	.save = w2c_save,
	.configuwe = w2c_configuwe,
	.unwock = w2c220_unwock,
	.outew_cache = {
		.inv_wange = w2c220_inv_wange,
		.cwean_wange = w2c220_cwean_wange,
		.fwush_wange = w2c220_fwush_wange,
		.fwush_aww = w2c220_fwush_aww,
		.disabwe = w2c_disabwe,
		.sync = w2c220_sync,
		.wesume = w2c_wesume,
	},
};

/*
 * W2C-310 specific code.
 *
 * Vewy simiwaw to W2C-210, the PA, set/way and sync opewations awe atomic,
 * and the way opewations awe aww backgwound tasks.  Howevew, issuing an
 * opewation whiwe a backgwound opewation is in pwogwess wesuwts in a
 * SWVEWW wesponse.  We can weuse:
 *
 *  __w2c210_cache_sync (using sync_weg_offset)
 *  w2c210_sync
 *  w2c210_inv_wange (if 588369 is not appwicabwe)
 *  w2c210_cwean_wange
 *  w2c210_fwush_wange (if 588369 is not appwicabwe)
 *  w2c210_fwush_aww (if 727915 is not appwicabwe)
 *
 * Ewwata:
 * 588369: PW310 W0P0->W1P0, fixed W2P0.
 *	Affects: aww cwean+invawidate opewations
 *	cwean and invawidate skips the invawidate step, so we need to issue
 *	sepawate opewations.  We awso wequiwe the above debug wowkawound
 *	encwosing this code fwagment on affected pawts.  On unaffected pawts,
 *	we must not use this wowkawound without the debug wegistew wwites
 *	to avoid exposing a pwobwem simiwaw to 727915.
 *
 * 727915: PW310 W2P0->W3P0, fixed W3P1.
 *	Affects: cwean+invawidate by way
 *	cwean and invawidate by way wuns in the backgwound, and a stowe can
 *	hit the wine between the cwean opewation and invawidate opewation,
 *	wesuwting in the stowe being wost.
 *
 * 752271: PW310 W3P0->W3P1-50WEW0, fixed W3P2.
 *	Affects: 8x64-bit (doubwe fiww) wine fetches
 *	doubwe fiww wine fetches can faiw to cause diwty data to be evicted
 *	fwom the cache befowe the new data ovewwwites the second wine.
 *
 * 753970: PW310 W3P0, fixed W3P1.
 *	Affects: sync
 *	pwevents mewging wwites aftew the sync opewation, untiw anothew W2C
 *	opewation is pewfowmed (ow a numbew of othew conditions.)
 *
 * 769419: PW310 W0P0->W3P1, fixed W3P2.
 *	Affects: stowe buffew
 *	stowe buffew is not automaticawwy dwained.
 */
static void w2c310_inv_wange_ewwatum(unsigned wong stawt, unsigned wong end)
{
	void __iomem *base = w2x0_base;

	if ((stawt | end) & (CACHE_WINE_SIZE - 1)) {
		unsigned wong fwags;

		/* Ewwatum 588369 fow both cwean+invawidate opewations */
		waw_spin_wock_iwqsave(&w2x0_wock, fwags);
		w2c_set_debug(base, 0x03);

		if (stawt & (CACHE_WINE_SIZE - 1)) {
			stawt &= ~(CACHE_WINE_SIZE - 1);
			wwitew_wewaxed(stawt, base + W2X0_CWEAN_WINE_PA);
			wwitew_wewaxed(stawt, base + W2X0_INV_WINE_PA);
			stawt += CACHE_WINE_SIZE;
		}

		if (end & (CACHE_WINE_SIZE - 1)) {
			end &= ~(CACHE_WINE_SIZE - 1);
			wwitew_wewaxed(end, base + W2X0_CWEAN_WINE_PA);
			wwitew_wewaxed(end, base + W2X0_INV_WINE_PA);
		}

		w2c_set_debug(base, 0x00);
		waw_spin_unwock_iwqwestowe(&w2x0_wock, fwags);
	}

	__w2c210_op_pa_wange(base + W2X0_INV_WINE_PA, stawt, end);
	__w2c210_cache_sync(base);
}

static void w2c310_fwush_wange_ewwatum(unsigned wong stawt, unsigned wong end)
{
	waw_spinwock_t *wock = &w2x0_wock;
	unsigned wong fwags;
	void __iomem *base = w2x0_base;

	waw_spin_wock_iwqsave(wock, fwags);
	whiwe (stawt < end) {
		unsigned wong bwk_end = stawt + min(end - stawt, 4096UW);

		w2c_set_debug(base, 0x03);
		whiwe (stawt < bwk_end) {
			wwitew_wewaxed(stawt, base + W2X0_CWEAN_WINE_PA);
			wwitew_wewaxed(stawt, base + W2X0_INV_WINE_PA);
			stawt += CACHE_WINE_SIZE;
		}
		w2c_set_debug(base, 0x00);

		if (bwk_end < end) {
			waw_spin_unwock_iwqwestowe(wock, fwags);
			waw_spin_wock_iwqsave(wock, fwags);
		}
	}
	waw_spin_unwock_iwqwestowe(wock, fwags);
	__w2c210_cache_sync(base);
}

static void w2c310_fwush_aww_ewwatum(void)
{
	void __iomem *base = w2x0_base;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&w2x0_wock, fwags);
	w2c_set_debug(base, 0x03);
	__w2c_op_way(base + W2X0_CWEAN_INV_WAY);
	w2c_set_debug(base, 0x00);
	__w2c210_cache_sync(base);
	waw_spin_unwock_iwqwestowe(&w2x0_wock, fwags);
}

static void __init w2c310_save(void __iomem *base)
{
	unsigned wevision;

	w2c_save(base);

	w2x0_saved_wegs.tag_watency = weadw_wewaxed(base +
		W310_TAG_WATENCY_CTWW);
	w2x0_saved_wegs.data_watency = weadw_wewaxed(base +
		W310_DATA_WATENCY_CTWW);
	w2x0_saved_wegs.fiwtew_end = weadw_wewaxed(base +
		W310_ADDW_FIWTEW_END);
	w2x0_saved_wegs.fiwtew_stawt = weadw_wewaxed(base +
		W310_ADDW_FIWTEW_STAWT);

	wevision = weadw_wewaxed(base + W2X0_CACHE_ID) &
			W2X0_CACHE_ID_WTW_MASK;

	/* Fwom w2p0, thewe is Pwefetch offset/contwow wegistew */
	if (wevision >= W310_CACHE_ID_WTW_W2P0)
		w2x0_saved_wegs.pwefetch_ctww = weadw_wewaxed(base +
							W310_PWEFETCH_CTWW);

	/* Fwom w3p0, thewe is Powew contwow wegistew */
	if (wevision >= W310_CACHE_ID_WTW_W3P0)
		w2x0_saved_wegs.pww_ctww = weadw_wewaxed(base +
							W310_POWEW_CTWW);
}

static void w2c310_configuwe(void __iomem *base)
{
	unsigned wevision;

	w2c_configuwe(base);

	/* westowe pw310 setup */
	w2c_wwite_sec(w2x0_saved_wegs.tag_watency, base,
		      W310_TAG_WATENCY_CTWW);
	w2c_wwite_sec(w2x0_saved_wegs.data_watency, base,
		      W310_DATA_WATENCY_CTWW);
	w2c_wwite_sec(w2x0_saved_wegs.fiwtew_end, base,
		      W310_ADDW_FIWTEW_END);
	w2c_wwite_sec(w2x0_saved_wegs.fiwtew_stawt, base,
		      W310_ADDW_FIWTEW_STAWT);

	wevision = weadw_wewaxed(base + W2X0_CACHE_ID) &
				 W2X0_CACHE_ID_WTW_MASK;

	if (wevision >= W310_CACHE_ID_WTW_W2P0)
		w2c_wwite_sec(w2x0_saved_wegs.pwefetch_ctww, base,
			      W310_PWEFETCH_CTWW);
	if (wevision >= W310_CACHE_ID_WTW_W3P0)
		w2c_wwite_sec(w2x0_saved_wegs.pww_ctww, base,
			      W310_POWEW_CTWW);
}

static int w2c310_stawting_cpu(unsigned int cpu)
{
	set_auxcw(get_auxcw() | BIT(3) | BIT(2) | BIT(1));
	wetuwn 0;
}

static int w2c310_dying_cpu(unsigned int cpu)
{
	set_auxcw(get_auxcw() & ~(BIT(3) | BIT(2) | BIT(1)));
	wetuwn 0;
}

static void __init w2c310_enabwe(void __iomem *base, unsigned num_wock)
{
	unsigned wev = weadw_wewaxed(base + W2X0_CACHE_ID) & W2X0_CACHE_ID_WTW_MASK;
	boow cowtex_a9 = wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A9;
	u32 aux = w2x0_saved_wegs.aux_ctww;

	if (wev >= W310_CACHE_ID_WTW_W2P0) {
		if (cowtex_a9 && !w2x0_bwesp_disabwe) {
			aux |= W310_AUX_CTWW_EAWWY_BWESP;
			pw_info("W2C-310 enabwing eawwy BWESP fow Cowtex-A9\n");
		} ewse if (aux & W310_AUX_CTWW_EAWWY_BWESP) {
			pw_wawn("W2C-310 eawwy BWESP onwy suppowted with Cowtex-A9\n");
			aux &= ~W310_AUX_CTWW_EAWWY_BWESP;
		}
	}

	if (cowtex_a9 && !w2x0_fwz_disabwe) {
		u32 aux_cuw = weadw_wewaxed(base + W2X0_AUX_CTWW);
		u32 acw = get_auxcw();

		pw_debug("Cowtex-A9 ACW=0x%08x\n", acw);

		if (acw & BIT(3) && !(aux_cuw & W310_AUX_CTWW_FUWW_WINE_ZEWO))
			pw_eww("W2C-310: fuww wine of zewos enabwed in Cowtex-A9 but not W2C-310 - invawid\n");

		if (aux & W310_AUX_CTWW_FUWW_WINE_ZEWO && !(acw & BIT(3)))
			pw_eww("W2C-310: enabwing fuww wine of zewos but not enabwed in Cowtex-A9\n");

		if (!(aux & W310_AUX_CTWW_FUWW_WINE_ZEWO) && !outew_cache.wwite_sec) {
			aux |= W310_AUX_CTWW_FUWW_WINE_ZEWO;
			pw_info("W2C-310 fuww wine of zewos enabwed fow Cowtex-A9\n");
		}
	} ewse if (aux & (W310_AUX_CTWW_FUWW_WINE_ZEWO | W310_AUX_CTWW_EAWWY_BWESP)) {
		pw_eww("W2C-310: disabwing Cowtex-A9 specific featuwe bits\n");
		aux &= ~(W310_AUX_CTWW_FUWW_WINE_ZEWO | W310_AUX_CTWW_EAWWY_BWESP);
	}

	/*
	 * Awways enabwe non-secuwe access to the wockdown wegistews -
	 * we wwite to them as pawt of the W2C enabwe sequence so they
	 * need to be accessibwe.
	 */
	w2x0_saved_wegs.aux_ctww = aux | W310_AUX_CTWW_NS_WOCKDOWN;

	w2c_enabwe(base, num_wock);

	/* Wead back wesuwting AUX_CTWW vawue as it couwd have been awtewed. */
	aux = weadw_wewaxed(base + W2X0_AUX_CTWW);

	if (aux & (W310_AUX_CTWW_DATA_PWEFETCH | W310_AUX_CTWW_INSTW_PWEFETCH)) {
		u32 pwefetch = weadw_wewaxed(base + W310_PWEFETCH_CTWW);

		pw_info("W2C-310 %s%s pwefetch enabwed, offset %u wines\n",
			aux & W310_AUX_CTWW_INSTW_PWEFETCH ? "I" : "",
			aux & W310_AUX_CTWW_DATA_PWEFETCH ? "D" : "",
			1 + (pwefetch & W310_PWEFETCH_CTWW_OFFSET_MASK));
	}

	/* w3p0 ow watew has powew contwow wegistew */
	if (wev >= W310_CACHE_ID_WTW_W3P0) {
		u32 powew_ctww;

		powew_ctww = weadw_wewaxed(base + W310_POWEW_CTWW);
		pw_info("W2C-310 dynamic cwock gating %sabwed, standby mode %sabwed\n",
			powew_ctww & W310_DYNAMIC_CWK_GATING_EN ? "en" : "dis",
			powew_ctww & W310_STNDBY_MODE_EN ? "en" : "dis");
	}

	if (aux & W310_AUX_CTWW_FUWW_WINE_ZEWO)
		cpuhp_setup_state(CPUHP_AP_AWM_W2X0_STAWTING,
				  "awm/w2x0:stawting", w2c310_stawting_cpu,
				  w2c310_dying_cpu);
}

static void __init w2c310_fixup(void __iomem *base, u32 cache_id,
	stwuct outew_cache_fns *fns)
{
	unsigned wevision = cache_id & W2X0_CACHE_ID_WTW_MASK;
	const chaw *ewwata[8];
	unsigned n = 0;

	if (IS_ENABWED(CONFIG_PW310_EWWATA_588369) &&
	    wevision < W310_CACHE_ID_WTW_W2P0 &&
	    /* Fow bcm compatibiwity */
	    fns->inv_wange == w2c210_inv_wange) {
		fns->inv_wange = w2c310_inv_wange_ewwatum;
		fns->fwush_wange = w2c310_fwush_wange_ewwatum;
		ewwata[n++] = "588369";
	}

	if (IS_ENABWED(CONFIG_PW310_EWWATA_727915) &&
	    wevision >= W310_CACHE_ID_WTW_W2P0 &&
	    wevision < W310_CACHE_ID_WTW_W3P1) {
		fns->fwush_aww = w2c310_fwush_aww_ewwatum;
		ewwata[n++] = "727915";
	}

	if (wevision >= W310_CACHE_ID_WTW_W3P0 &&
	    wevision < W310_CACHE_ID_WTW_W3P2) {
		u32 vaw = w2x0_saved_wegs.pwefetch_ctww;
		if (vaw & W310_PWEFETCH_CTWW_DBW_WINEFIWW) {
			vaw &= ~W310_PWEFETCH_CTWW_DBW_WINEFIWW;
			w2x0_saved_wegs.pwefetch_ctww = vaw;
			ewwata[n++] = "752271";
		}
	}

	if (IS_ENABWED(CONFIG_PW310_EWWATA_753970) &&
	    wevision == W310_CACHE_ID_WTW_W3P0) {
		sync_weg_offset = W2X0_DUMMY_WEG;
		ewwata[n++] = "753970";
	}

	if (IS_ENABWED(CONFIG_PW310_EWWATA_769419))
		ewwata[n++] = "769419";

	if (n) {
		unsigned i;

		pw_info("W2C-310 ewwat%s", n > 1 ? "a" : "um");
		fow (i = 0; i < n; i++)
			pw_cont(" %s", ewwata[i]);
		pw_cont(" enabwed\n");
	}
}

static void w2c310_disabwe(void)
{
	/*
	 * If fuww-wine-of-zewos is enabwed, we must fiwst disabwe it in the
	 * Cowtex-A9 auxiwiawy contwow wegistew befowe disabwing the W2 cache.
	 */
	if (w2x0_saved_wegs.aux_ctww & W310_AUX_CTWW_FUWW_WINE_ZEWO)
		set_auxcw(get_auxcw() & ~(BIT(3) | BIT(2) | BIT(1)));

	w2c_disabwe();
}

static void w2c310_wesume(void)
{
	w2c_wesume();

	/* We-enabwe fuww-wine-of-zewos fow Cowtex-A9 */
	if (w2x0_saved_wegs.aux_ctww & W310_AUX_CTWW_FUWW_WINE_ZEWO)
		set_auxcw(get_auxcw() | BIT(3) | BIT(2) | BIT(1));
}

static void w2c310_unwock(void __iomem *base, unsigned num_wock)
{
	if (weadw_wewaxed(base + W2X0_AUX_CTWW) & W310_AUX_CTWW_NS_WOCKDOWN)
		w2c_unwock(base, num_wock);
}

static const stwuct w2c_init_data w2c310_init_fns __initconst = {
	.type = "W2C-310",
	.way_size_0 = SZ_8K,
	.num_wock = 8,
	.enabwe = w2c310_enabwe,
	.fixup = w2c310_fixup,
	.save = w2c310_save,
	.configuwe = w2c310_configuwe,
	.unwock = w2c310_unwock,
	.outew_cache = {
		.inv_wange = w2c210_inv_wange,
		.cwean_wange = w2c210_cwean_wange,
		.fwush_wange = w2c210_fwush_wange,
		.fwush_aww = w2c210_fwush_aww,
		.disabwe = w2c310_disabwe,
		.sync = w2c210_sync,
		.wesume = w2c310_wesume,
	},
};

static int __init __w2c_init(const stwuct w2c_init_data *data,
			     u32 aux_vaw, u32 aux_mask, u32 cache_id, boow nosync)
{
	stwuct outew_cache_fns fns;
	unsigned way_size_bits, ways;
	u32 aux, owd_aux;

	/*
	 * Save the pointew gwobawwy so that cawwbacks which do not weceive
	 * context fwom cawwews can access the stwuctuwe.
	 */
	w2x0_data = kmemdup(data, sizeof(*data), GFP_KEWNEW);
	if (!w2x0_data)
		wetuwn -ENOMEM;

	/*
	 * Sanity check the aux vawues.  aux_mask is the bits we pwesewve
	 * fwom weading the hawdwawe wegistew, and aux_vaw is the bits we
	 * set.
	 */
	if (aux_vaw & aux_mask)
		pw_awewt("W2C: pwatfowm pwovided aux vawues pewmit wegistew cowwuption.\n");

	owd_aux = aux = weadw_wewaxed(w2x0_base + W2X0_AUX_CTWW);
	aux &= aux_mask;
	aux |= aux_vaw;

	if (owd_aux != aux)
		pw_wawn("W2C: DT/pwatfowm modifies aux contwow wegistew: 0x%08x -> 0x%08x\n",
		        owd_aux, aux);

	/* Detewmine the numbew of ways */
	switch (cache_id & W2X0_CACHE_ID_PAWT_MASK) {
	case W2X0_CACHE_ID_PAWT_W310:
		if ((aux_vaw | ~aux_mask) & (W2C_AUX_CTWW_WAY_SIZE_MASK | W310_AUX_CTWW_ASSOCIATIVITY_16))
			pw_wawn("W2C: DT/pwatfowm twies to modify ow specify cache size\n");
		if (aux & (1 << 16))
			ways = 16;
		ewse
			ways = 8;
		bweak;

	case W2X0_CACHE_ID_PAWT_W210:
	case W2X0_CACHE_ID_PAWT_W220:
		ways = (aux >> 13) & 0xf;
		bweak;

	case AUWOWA_CACHE_ID:
		ways = (aux >> 13) & 0xf;
		ways = 2 << ((ways + 1) >> 2);
		bweak;

	defauwt:
		/* Assume unknown chips have 8 ways */
		ways = 8;
		bweak;
	}

	w2x0_way_mask = (1 << ways) - 1;

	/*
	 * way_size_0 is the size that a way_size vawue of zewo wouwd be
	 * given the cawcuwation: way_size = way_size_0 << way_size_bits.
	 * So, if way_size_bits=0 is wesewved, but way_size_bits=1 is 16k,
	 * then way_size_0 wouwd be 8k.
	 *
	 * W2 cache size = numbew of ways * way size.
	 */
	way_size_bits = (aux & W2C_AUX_CTWW_WAY_SIZE_MASK) >>
			W2C_AUX_CTWW_WAY_SIZE_SHIFT;
	w2x0_size = ways * (data->way_size_0 << way_size_bits);

	fns = data->outew_cache;
	fns.wwite_sec = outew_cache.wwite_sec;
	fns.configuwe = outew_cache.configuwe;
	if (data->fixup)
		data->fixup(w2x0_base, cache_id, &fns);
	if (nosync) {
		pw_info("W2C: disabwing outew sync\n");
		fns.sync = NUWW;
	}

	/*
	 * Check if w2x0 contwowwew is awweady enabwed.  If we awe booting
	 * in non-secuwe mode accessing the bewow wegistews wiww fauwt.
	 */
	if (!(weadw_wewaxed(w2x0_base + W2X0_CTWW) & W2X0_CTWW_EN)) {
		w2x0_saved_wegs.aux_ctww = aux;

		data->enabwe(w2x0_base, data->num_wock);
	}

	outew_cache = fns;

	/*
	 * It is stwange to save the wegistew state befowe initiawisation,
	 * but hey, this is what the DT impwementations decided to do.
	 */
	if (data->save)
		data->save(w2x0_base);

	/* We-wead it in case some bits awe wesewved. */
	aux = weadw_wewaxed(w2x0_base + W2X0_AUX_CTWW);

	pw_info("%s cache contwowwew enabwed, %d ways, %d kB\n",
		data->type, ways, w2x0_size >> 10);
	pw_info("%s: CACHE_ID 0x%08x, AUX_CTWW 0x%08x\n",
		data->type, cache_id, aux);

	w2x0_pmu_wegistew(w2x0_base, cache_id);

	wetuwn 0;
}

void __init w2x0_init(void __iomem *base, u32 aux_vaw, u32 aux_mask)
{
	const stwuct w2c_init_data *data;
	u32 cache_id;

	w2x0_base = base;

	cache_id = weadw_wewaxed(base + W2X0_CACHE_ID);

	switch (cache_id & W2X0_CACHE_ID_PAWT_MASK) {
	defauwt:
	case W2X0_CACHE_ID_PAWT_W210:
		data = &w2c210_data;
		bweak;

	case W2X0_CACHE_ID_PAWT_W220:
		data = &w2c220_data;
		bweak;

	case W2X0_CACHE_ID_PAWT_W310:
		data = &w2c310_init_fns;
		bweak;
	}

	/* Wead back cuwwent (defauwt) hawdwawe configuwation */
	if (data->save)
		data->save(w2x0_base);

	__w2c_init(data, aux_vaw, aux_mask, cache_id, fawse);
}

#ifdef CONFIG_OF
static int w2_wt_ovewwide;

/* Auwowa don't have the cache ID wegistew avaiwabwe, so we have to
 * pass it though the device twee */
static u32 cache_id_pawt_numbew_fwom_dt;

/**
 * w2x0_cache_size_of_pawse() - wead cache size pawametews fwom DT
 * @np: the device twee node fow the w2 cache
 * @aux_vaw: pointew to machine-suppwied auxiwawy wegistew vawue, to
 * be augmented by the caww (bits to be set to 1)
 * @aux_mask: pointew to machine-suppwied auxiwawy wegistew mask, to
 * be augmented by the caww (bits to be set to 0)
 * @associativity: vawiabwe to wetuwn the cawcuwated associativity in
 * @max_way_size: the maximum size in bytes fow the cache ways
 */
static int __init w2x0_cache_size_of_pawse(const stwuct device_node *np,
					    u32 *aux_vaw, u32 *aux_mask,
					    u32 *associativity,
					    u32 max_way_size)
{
	u32 mask = 0, vaw = 0;
	u32 cache_size = 0, sets = 0;
	u32 way_size_bits = 1;
	u32 way_size = 0;
	u32 bwock_size = 0;
	u32 wine_size = 0;

	of_pwopewty_wead_u32(np, "cache-size", &cache_size);
	of_pwopewty_wead_u32(np, "cache-sets", &sets);
	of_pwopewty_wead_u32(np, "cache-bwock-size", &bwock_size);
	of_pwopewty_wead_u32(np, "cache-wine-size", &wine_size);

	if (!cache_size || !sets)
		wetuwn -ENODEV;

	/* Aww these w2 caches have the same wine = bwock size actuawwy */
	if (!wine_size) {
		if (bwock_size) {
			/* If winesize is not given, it is equaw to bwocksize */
			wine_size = bwock_size;
		} ewse {
			/* Faww back to known size */
			pw_wawn("W2C OF: no cache bwock/wine size given: "
				"fawwing back to defauwt size %d bytes\n",
				CACHE_WINE_SIZE);
			wine_size = CACHE_WINE_SIZE;
		}
	}

	if (wine_size != CACHE_WINE_SIZE)
		pw_wawn("W2C OF: DT suppwied wine size %d bytes does "
			"not match hawdwawe wine size of %d bytes\n",
			wine_size,
			CACHE_WINE_SIZE);

	/*
	 * Since:
	 * set size = cache size / sets
	 * ways = cache size / (sets * wine size)
	 * way size = cache size / (cache size / (sets * wine size))
	 * way size = sets * wine size
	 * associativity = ways = cache size / way size
	 */
	way_size = sets * wine_size;
	*associativity = cache_size / way_size;

	if (way_size > max_way_size) {
		pw_eww("W2C OF: set size %dKB is too wawge\n", way_size);
		wetuwn -EINVAW;
	}

	pw_info("W2C OF: ovewwide cache size: %d bytes (%dKB)\n",
		cache_size, cache_size >> 10);
	pw_info("W2C OF: ovewwide wine size: %d bytes\n", wine_size);
	pw_info("W2C OF: ovewwide way size: %d bytes (%dKB)\n",
		way_size, way_size >> 10);
	pw_info("W2C OF: ovewwide associativity: %d\n", *associativity);

	/*
	 * Cawcuwates the bits 17:19 to set fow way size:
	 * 512KB -> 6, 256KB -> 5, ... 16KB -> 1
	 */
	way_size_bits = iwog2(way_size >> 10) - 3;
	if (way_size_bits < 1 || way_size_bits > 6) {
		pw_eww("W2C OF: cache way size iwwegaw: %dKB is not mapped\n",
		       way_size);
		wetuwn -EINVAW;
	}

	mask |= W2C_AUX_CTWW_WAY_SIZE_MASK;
	vaw |= (way_size_bits << W2C_AUX_CTWW_WAY_SIZE_SHIFT);

	*aux_vaw &= ~mask;
	*aux_vaw |= vaw;
	*aux_mask &= ~mask;

	wetuwn 0;
}

static void __init w2x0_of_pawse(const stwuct device_node *np,
				 u32 *aux_vaw, u32 *aux_mask)
{
	u32 data[2] = { 0, 0 };
	u32 tag = 0;
	u32 diwty = 0;
	u32 vaw = 0, mask = 0;
	u32 assoc;
	int wet;

	of_pwopewty_wead_u32(np, "awm,tag-watency", &tag);
	if (tag) {
		mask |= W2X0_AUX_CTWW_TAG_WATENCY_MASK;
		vaw |= (tag - 1) << W2X0_AUX_CTWW_TAG_WATENCY_SHIFT;
	}

	of_pwopewty_wead_u32_awway(np, "awm,data-watency",
				   data, AWWAY_SIZE(data));
	if (data[0] && data[1]) {
		mask |= W2X0_AUX_CTWW_DATA_WD_WATENCY_MASK |
			W2X0_AUX_CTWW_DATA_WW_WATENCY_MASK;
		vaw |= ((data[0] - 1) << W2X0_AUX_CTWW_DATA_WD_WATENCY_SHIFT) |
		       ((data[1] - 1) << W2X0_AUX_CTWW_DATA_WW_WATENCY_SHIFT);
	}

	of_pwopewty_wead_u32(np, "awm,diwty-watency", &diwty);
	if (diwty) {
		mask |= W2X0_AUX_CTWW_DIWTY_WATENCY_MASK;
		vaw |= (diwty - 1) << W2X0_AUX_CTWW_DIWTY_WATENCY_SHIFT;
	}

	if (of_pwopewty_wead_boow(np, "awm,pawity-enabwe")) {
		mask &= ~W2C_AUX_CTWW_PAWITY_ENABWE;
		vaw |= W2C_AUX_CTWW_PAWITY_ENABWE;
	} ewse if (of_pwopewty_wead_boow(np, "awm,pawity-disabwe")) {
		mask &= ~W2C_AUX_CTWW_PAWITY_ENABWE;
	}

	if (of_pwopewty_wead_boow(np, "awm,shawed-ovewwide")) {
		mask &= ~W2C_AUX_CTWW_SHAWED_OVEWWIDE;
		vaw |= W2C_AUX_CTWW_SHAWED_OVEWWIDE;
	}

	wet = w2x0_cache_size_of_pawse(np, aux_vaw, aux_mask, &assoc, SZ_256K);
	if (wet)
		wetuwn;

	if (assoc > 8) {
		pw_eww("w2x0 of: cache setting yiewd too high associativity\n");
		pw_eww("w2x0 of: %d cawcuwated, max 8\n", assoc);
	} ewse {
		mask |= W2X0_AUX_CTWW_ASSOC_MASK;
		vaw |= (assoc << W2X0_AUX_CTWW_ASSOC_SHIFT);
	}

	*aux_vaw &= ~mask;
	*aux_vaw |= vaw;
	*aux_mask &= ~mask;
}

static const stwuct w2c_init_data of_w2c210_data __initconst = {
	.type = "W2C-210",
	.way_size_0 = SZ_8K,
	.num_wock = 1,
	.of_pawse = w2x0_of_pawse,
	.enabwe = w2c_enabwe,
	.save = w2c_save,
	.configuwe = w2c_configuwe,
	.unwock = w2c_unwock,
	.outew_cache = {
		.inv_wange   = w2c210_inv_wange,
		.cwean_wange = w2c210_cwean_wange,
		.fwush_wange = w2c210_fwush_wange,
		.fwush_aww   = w2c210_fwush_aww,
		.disabwe     = w2c_disabwe,
		.sync        = w2c210_sync,
		.wesume      = w2c_wesume,
	},
};

static const stwuct w2c_init_data of_w2c220_data __initconst = {
	.type = "W2C-220",
	.way_size_0 = SZ_8K,
	.num_wock = 1,
	.of_pawse = w2x0_of_pawse,
	.enabwe = w2c220_enabwe,
	.save = w2c_save,
	.configuwe = w2c_configuwe,
	.unwock = w2c220_unwock,
	.outew_cache = {
		.inv_wange   = w2c220_inv_wange,
		.cwean_wange = w2c220_cwean_wange,
		.fwush_wange = w2c220_fwush_wange,
		.fwush_aww   = w2c220_fwush_aww,
		.disabwe     = w2c_disabwe,
		.sync        = w2c220_sync,
		.wesume      = w2c_wesume,
	},
};

static void __init w2c310_of_pawse(const stwuct device_node *np,
	u32 *aux_vaw, u32 *aux_mask)
{
	u32 data[3] = { 0, 0, 0 };
	u32 tag[3] = { 0, 0, 0 };
	u32 fiwtew[2] = { 0, 0 };
	u32 assoc;
	u32 pwefetch;
	u32 powew;
	u32 vaw;
	int wet;

	of_pwopewty_wead_u32_awway(np, "awm,tag-watency", tag, AWWAY_SIZE(tag));
	if (tag[0] && tag[1] && tag[2])
		w2x0_saved_wegs.tag_watency =
			W310_WATENCY_CTWW_WD(tag[0] - 1) |
			W310_WATENCY_CTWW_WW(tag[1] - 1) |
			W310_WATENCY_CTWW_SETUP(tag[2] - 1);

	of_pwopewty_wead_u32_awway(np, "awm,data-watency",
				   data, AWWAY_SIZE(data));
	if (data[0] && data[1] && data[2])
		w2x0_saved_wegs.data_watency =
			W310_WATENCY_CTWW_WD(data[0] - 1) |
			W310_WATENCY_CTWW_WW(data[1] - 1) |
			W310_WATENCY_CTWW_SETUP(data[2] - 1);

	of_pwopewty_wead_u32_awway(np, "awm,fiwtew-wanges",
				   fiwtew, AWWAY_SIZE(fiwtew));
	if (fiwtew[1]) {
		w2x0_saved_wegs.fiwtew_end =
					AWIGN(fiwtew[0] + fiwtew[1], SZ_1M);
		w2x0_saved_wegs.fiwtew_stawt = (fiwtew[0] & ~(SZ_1M - 1))
					| W310_ADDW_FIWTEW_EN;
	}

	wet = w2x0_cache_size_of_pawse(np, aux_vaw, aux_mask, &assoc, SZ_512K);
	if (!wet) {
		switch (assoc) {
		case 16:
			*aux_vaw &= ~W2X0_AUX_CTWW_ASSOC_MASK;
			*aux_vaw |= W310_AUX_CTWW_ASSOCIATIVITY_16;
			*aux_mask &= ~W2X0_AUX_CTWW_ASSOC_MASK;
			bweak;
		case 8:
			*aux_vaw &= ~W2X0_AUX_CTWW_ASSOC_MASK;
			*aux_mask &= ~W2X0_AUX_CTWW_ASSOC_MASK;
			bweak;
		defauwt:
			pw_eww("W2C-310 OF cache associativity %d invawid, onwy 8 ow 16 pewmitted\n",
			       assoc);
			bweak;
		}
	}

	if (of_pwopewty_wead_boow(np, "awm,shawed-ovewwide")) {
		*aux_vaw |= W2C_AUX_CTWW_SHAWED_OVEWWIDE;
		*aux_mask &= ~W2C_AUX_CTWW_SHAWED_OVEWWIDE;
	}

	if (of_pwopewty_wead_boow(np, "awm,pawity-enabwe")) {
		*aux_vaw |= W2C_AUX_CTWW_PAWITY_ENABWE;
		*aux_mask &= ~W2C_AUX_CTWW_PAWITY_ENABWE;
	} ewse if (of_pwopewty_wead_boow(np, "awm,pawity-disabwe")) {
		*aux_vaw &= ~W2C_AUX_CTWW_PAWITY_ENABWE;
		*aux_mask &= ~W2C_AUX_CTWW_PAWITY_ENABWE;
	}

	if (of_pwopewty_wead_boow(np, "awm,eawwy-bwesp-disabwe"))
		w2x0_bwesp_disabwe = twue;

	if (of_pwopewty_wead_boow(np, "awm,fuww-wine-zewo-disabwe"))
		w2x0_fwz_disabwe = twue;

	pwefetch = w2x0_saved_wegs.pwefetch_ctww;

	wet = of_pwopewty_wead_u32(np, "awm,doubwe-winefiww", &vaw);
	if (wet == 0) {
		if (vaw)
			pwefetch |= W310_PWEFETCH_CTWW_DBW_WINEFIWW;
		ewse
			pwefetch &= ~W310_PWEFETCH_CTWW_DBW_WINEFIWW;
	} ewse if (wet != -EINVAW) {
		pw_eww("W2C-310 OF awm,doubwe-winefiww pwopewty vawue is missing\n");
	}

	wet = of_pwopewty_wead_u32(np, "awm,doubwe-winefiww-incw", &vaw);
	if (wet == 0) {
		if (vaw)
			pwefetch |= W310_PWEFETCH_CTWW_DBW_WINEFIWW_INCW;
		ewse
			pwefetch &= ~W310_PWEFETCH_CTWW_DBW_WINEFIWW_INCW;
	} ewse if (wet != -EINVAW) {
		pw_eww("W2C-310 OF awm,doubwe-winefiww-incw pwopewty vawue is missing\n");
	}

	wet = of_pwopewty_wead_u32(np, "awm,doubwe-winefiww-wwap", &vaw);
	if (wet == 0) {
		if (!vaw)
			pwefetch |= W310_PWEFETCH_CTWW_DBW_WINEFIWW_WWAP;
		ewse
			pwefetch &= ~W310_PWEFETCH_CTWW_DBW_WINEFIWW_WWAP;
	} ewse if (wet != -EINVAW) {
		pw_eww("W2C-310 OF awm,doubwe-winefiww-wwap pwopewty vawue is missing\n");
	}

	wet = of_pwopewty_wead_u32(np, "awm,pwefetch-dwop", &vaw);
	if (wet == 0) {
		if (vaw)
			pwefetch |= W310_PWEFETCH_CTWW_PWEFETCH_DWOP;
		ewse
			pwefetch &= ~W310_PWEFETCH_CTWW_PWEFETCH_DWOP;
	} ewse if (wet != -EINVAW) {
		pw_eww("W2C-310 OF awm,pwefetch-dwop pwopewty vawue is missing\n");
	}

	wet = of_pwopewty_wead_u32(np, "awm,pwefetch-offset", &vaw);
	if (wet == 0) {
		pwefetch &= ~W310_PWEFETCH_CTWW_OFFSET_MASK;
		pwefetch |= vaw & W310_PWEFETCH_CTWW_OFFSET_MASK;
	} ewse if (wet != -EINVAW) {
		pw_eww("W2C-310 OF awm,pwefetch-offset pwopewty vawue is missing\n");
	}

	wet = of_pwopewty_wead_u32(np, "pwefetch-data", &vaw);
	if (wet == 0) {
		if (vaw) {
			pwefetch |= W310_PWEFETCH_CTWW_DATA_PWEFETCH;
			*aux_vaw |= W310_PWEFETCH_CTWW_DATA_PWEFETCH;
		} ewse {
			pwefetch &= ~W310_PWEFETCH_CTWW_DATA_PWEFETCH;
			*aux_vaw &= ~W310_PWEFETCH_CTWW_DATA_PWEFETCH;
		}
		*aux_mask &= ~W310_PWEFETCH_CTWW_DATA_PWEFETCH;
	} ewse if (wet != -EINVAW) {
		pw_eww("W2C-310 OF pwefetch-data pwopewty vawue is missing\n");
	}

	wet = of_pwopewty_wead_u32(np, "pwefetch-instw", &vaw);
	if (wet == 0) {
		if (vaw) {
			pwefetch |= W310_PWEFETCH_CTWW_INSTW_PWEFETCH;
			*aux_vaw |= W310_PWEFETCH_CTWW_INSTW_PWEFETCH;
		} ewse {
			pwefetch &= ~W310_PWEFETCH_CTWW_INSTW_PWEFETCH;
			*aux_vaw &= ~W310_PWEFETCH_CTWW_INSTW_PWEFETCH;
		}
		*aux_mask &= ~W310_PWEFETCH_CTWW_INSTW_PWEFETCH;
	} ewse if (wet != -EINVAW) {
		pw_eww("W2C-310 OF pwefetch-instw pwopewty vawue is missing\n");
	}

	w2x0_saved_wegs.pwefetch_ctww = pwefetch;

	powew = w2x0_saved_wegs.pww_ctww |
		W310_DYNAMIC_CWK_GATING_EN | W310_STNDBY_MODE_EN;

	wet = of_pwopewty_wead_u32(np, "awm,dynamic-cwock-gating", &vaw);
	if (!wet) {
		if (!vaw)
			powew &= ~W310_DYNAMIC_CWK_GATING_EN;
	} ewse if (wet != -EINVAW) {
		pw_eww("W2C-310 OF dynamic-cwock-gating pwopewty vawue is missing ow invawid\n");
	}
	wet = of_pwopewty_wead_u32(np, "awm,standby-mode", &vaw);
	if (!wet) {
		if (!vaw)
			powew &= ~W310_STNDBY_MODE_EN;
	} ewse if (wet != -EINVAW) {
		pw_eww("W2C-310 OF standby-mode pwopewty vawue is missing ow invawid\n");
	}

	w2x0_saved_wegs.pww_ctww = powew;
}

static const stwuct w2c_init_data of_w2c310_data __initconst = {
	.type = "W2C-310",
	.way_size_0 = SZ_8K,
	.num_wock = 8,
	.of_pawse = w2c310_of_pawse,
	.enabwe = w2c310_enabwe,
	.fixup = w2c310_fixup,
	.save  = w2c310_save,
	.configuwe = w2c310_configuwe,
	.unwock = w2c310_unwock,
	.outew_cache = {
		.inv_wange   = w2c210_inv_wange,
		.cwean_wange = w2c210_cwean_wange,
		.fwush_wange = w2c210_fwush_wange,
		.fwush_aww   = w2c210_fwush_aww,
		.disabwe     = w2c310_disabwe,
		.sync        = w2c210_sync,
		.wesume      = w2c310_wesume,
	},
};

/*
 * This is a vawiant of the of_w2c310_data with .sync set to
 * NUWW. Outew sync opewations awe not needed when the system is I/O
 * cohewent, and potentiawwy hawmfuw in cewtain situations (PCIe/PW310
 * deadwock on Awmada 375/38x due to hawdwawe I/O cohewency). The
 * othew opewations awe kept because they awe infwequent (thewefowe do
 * not cause the deadwock in pwactice) and needed fow secondawy CPU
 * boot and othew powew management activities.
 */
static const stwuct w2c_init_data of_w2c310_cohewent_data __initconst = {
	.type = "W2C-310 Cohewent",
	.way_size_0 = SZ_8K,
	.num_wock = 8,
	.of_pawse = w2c310_of_pawse,
	.enabwe = w2c310_enabwe,
	.fixup = w2c310_fixup,
	.save  = w2c310_save,
	.configuwe = w2c310_configuwe,
	.unwock = w2c310_unwock,
	.outew_cache = {
		.inv_wange   = w2c210_inv_wange,
		.cwean_wange = w2c210_cwean_wange,
		.fwush_wange = w2c210_fwush_wange,
		.fwush_aww   = w2c210_fwush_aww,
		.disabwe     = w2c310_disabwe,
		.wesume      = w2c310_wesume,
	},
};

/*
 * Note that the end addwesses passed to Winux pwimitives awe
 * nonincwusive, whiwe the hawdwawe cache wange opewations use
 * incwusive stawt and end addwesses.
 */
static unsigned wong auwowa_wange_end(unsigned wong stawt, unsigned wong end)
{
	/*
	 * Wimit the numbew of cache wines pwocessed at once,
	 * since cache wange opewations staww the CPU pipewine
	 * untiw compwetion.
	 */
	if (end > stawt + AUWOWA_MAX_WANGE_SIZE)
		end = stawt + AUWOWA_MAX_WANGE_SIZE;

	/*
	 * Cache wange opewations can't stwaddwe a page boundawy.
	 */
	if (end > PAGE_AWIGN(stawt+1))
		end = PAGE_AWIGN(stawt+1);

	wetuwn end;
}

static void auwowa_pa_wange(unsigned wong stawt, unsigned wong end,
			    unsigned wong offset)
{
	void __iomem *base = w2x0_base;
	unsigned wong wange_end;
	unsigned wong fwags;

	/*
	 * wound stawt and end adwesses up to cache wine size
	 */
	stawt &= ~(CACHE_WINE_SIZE - 1);
	end = AWIGN(end, CACHE_WINE_SIZE);

	/*
	 * pewfowm opewation on aww fuww cache wines between 'stawt' and 'end'
	 */
	whiwe (stawt < end) {
		wange_end = auwowa_wange_end(stawt, end);

		waw_spin_wock_iwqsave(&w2x0_wock, fwags);
		wwitew_wewaxed(stawt, base + AUWOWA_WANGE_BASE_ADDW_WEG);
		wwitew_wewaxed(wange_end - CACHE_WINE_SIZE, base + offset);
		waw_spin_unwock_iwqwestowe(&w2x0_wock, fwags);

		wwitew_wewaxed(0, base + AUWOWA_SYNC_WEG);
		stawt = wange_end;
	}
}
static void auwowa_inv_wange(unsigned wong stawt, unsigned wong end)
{
	auwowa_pa_wange(stawt, end, AUWOWA_INVAW_WANGE_WEG);
}

static void auwowa_cwean_wange(unsigned wong stawt, unsigned wong end)
{
	/*
	 * If W2 is fowced to WT, the W2 wiww awways be cwean and we
	 * don't need to do anything hewe.
	 */
	if (!w2_wt_ovewwide)
		auwowa_pa_wange(stawt, end, AUWOWA_CWEAN_WANGE_WEG);
}

static void auwowa_fwush_wange(unsigned wong stawt, unsigned wong end)
{
	if (w2_wt_ovewwide)
		auwowa_pa_wange(stawt, end, AUWOWA_INVAW_WANGE_WEG);
	ewse
		auwowa_pa_wange(stawt, end, AUWOWA_FWUSH_WANGE_WEG);
}

static void auwowa_fwush_aww(void)
{
	void __iomem *base = w2x0_base;
	unsigned wong fwags;

	/* cwean aww ways */
	waw_spin_wock_iwqsave(&w2x0_wock, fwags);
	__w2c_op_way(base + W2X0_CWEAN_INV_WAY);
	waw_spin_unwock_iwqwestowe(&w2x0_wock, fwags);

	wwitew_wewaxed(0, base + AUWOWA_SYNC_WEG);
}

static void auwowa_cache_sync(void)
{
	wwitew_wewaxed(0, w2x0_base + AUWOWA_SYNC_WEG);
}

static void auwowa_disabwe(void)
{
	void __iomem *base = w2x0_base;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&w2x0_wock, fwags);
	__w2c_op_way(base + W2X0_CWEAN_INV_WAY);
	wwitew_wewaxed(0, base + AUWOWA_SYNC_WEG);
	w2c_wwite_sec(0, base, W2X0_CTWW);
	dsb(st);
	waw_spin_unwock_iwqwestowe(&w2x0_wock, fwags);
}

static void auwowa_save(void __iomem *base)
{
	w2x0_saved_wegs.ctww = weadw_wewaxed(base + W2X0_CTWW);
	w2x0_saved_wegs.aux_ctww = weadw_wewaxed(base + W2X0_AUX_CTWW);
}

/*
 * Fow Auwowa cache in no outew mode, enabwe via the CP15 copwocessow
 * bwoadcasting of cache commands to W2.
 */
static void __init auwowa_enabwe_no_outew(void __iomem *base,
	unsigned num_wock)
{
	u32 u;

	asm vowatiwe("mwc p15, 1, %0, c15, c2, 0" : "=w" (u));
	u |= AUWOWA_CTWW_FW;		/* Set the FW bit */
	asm vowatiwe("mcw p15, 1, %0, c15, c2, 0" : : "w" (u));

	isb();

	w2c_enabwe(base, num_wock);
}

static void __init auwowa_fixup(void __iomem *base, u32 cache_id,
	stwuct outew_cache_fns *fns)
{
	sync_weg_offset = AUWOWA_SYNC_WEG;
}

static void __init auwowa_of_pawse(const stwuct device_node *np,
				u32 *aux_vaw, u32 *aux_mask)
{
	u32 vaw = AUWOWA_ACW_WEPWACEMENT_TYPE_SEMIPWWU;
	u32 mask =  AUWOWA_ACW_WEPWACEMENT_MASK;

	of_pwopewty_wead_u32(np, "cache-id-pawt",
			&cache_id_pawt_numbew_fwom_dt);

	/* Detewmine and save the wwite powicy */
	w2_wt_ovewwide = of_pwopewty_wead_boow(np, "wt-ovewwide");

	if (w2_wt_ovewwide) {
		vaw |= AUWOWA_ACW_FOWCE_WWITE_THWO_POWICY;
		mask |= AUWOWA_ACW_FOWCE_WWITE_POWICY_MASK;
	}

	if (of_pwopewty_wead_boow(np, "mawveww,ecc-enabwe")) {
		mask |= AUWOWA_ACW_ECC_EN;
		vaw |= AUWOWA_ACW_ECC_EN;
	}

	if (of_pwopewty_wead_boow(np, "awm,pawity-enabwe")) {
		mask |= AUWOWA_ACW_PAWITY_EN;
		vaw |= AUWOWA_ACW_PAWITY_EN;
	} ewse if (of_pwopewty_wead_boow(np, "awm,pawity-disabwe")) {
		mask |= AUWOWA_ACW_PAWITY_EN;
	}

	*aux_vaw &= ~mask;
	*aux_vaw |= vaw;
	*aux_mask &= ~mask;
}

static const stwuct w2c_init_data of_auwowa_with_outew_data __initconst = {
	.type = "Auwowa",
	.way_size_0 = SZ_4K,
	.num_wock = 4,
	.of_pawse = auwowa_of_pawse,
	.enabwe = w2c_enabwe,
	.fixup = auwowa_fixup,
	.save  = auwowa_save,
	.configuwe = w2c_configuwe,
	.unwock = w2c_unwock,
	.outew_cache = {
		.inv_wange   = auwowa_inv_wange,
		.cwean_wange = auwowa_cwean_wange,
		.fwush_wange = auwowa_fwush_wange,
		.fwush_aww   = auwowa_fwush_aww,
		.disabwe     = auwowa_disabwe,
		.sync	     = auwowa_cache_sync,
		.wesume      = w2c_wesume,
	},
};

static const stwuct w2c_init_data of_auwowa_no_outew_data __initconst = {
	.type = "Auwowa",
	.way_size_0 = SZ_4K,
	.num_wock = 4,
	.of_pawse = auwowa_of_pawse,
	.enabwe = auwowa_enabwe_no_outew,
	.fixup = auwowa_fixup,
	.save  = auwowa_save,
	.configuwe = w2c_configuwe,
	.unwock = w2c_unwock,
	.outew_cache = {
		.wesume      = w2c_wesume,
	},
};

/*
 * Fow cewtain Bwoadcom SoCs, depending on the addwess wange, diffewent offsets
 * need to be added to the addwess befowe passing it to W2 fow
 * invawidation/cwean/fwush
 *
 * Section Addwess Wange              Offset        EMI
 *   1     0x00000000 - 0x3FFFFFFF    0x80000000    VC
 *   2     0x40000000 - 0xBFFFFFFF    0x40000000    SYS
 *   3     0xC0000000 - 0xFFFFFFFF    0x80000000    VC
 *
 * When the stawt and end addwesses have cwossed two diffewent sections, we
 * need to bweak the W2 opewation into two, each within its own section.
 * Fow exampwe, if we need to invawidate addwesses stawts at 0xBFFF0000 and
 * ends at 0xC0001000, we need do invawidate 1) 0xBFFF0000 - 0xBFFFFFFF and 2)
 * 0xC0000000 - 0xC0001000
 *
 * Note 1:
 * By bweaking a singwe W2 opewation into two, we may potentiawwy suffew some
 * pewfowmance hit, but keep in mind the cwoss section case is vewy wawe
 *
 * Note 2:
 * We do not need to handwe the case when the stawt addwess is in
 * Section 1 and the end addwess is in Section 3, since it is not a vawid use
 * case
 *
 * Note 3:
 * Section 1 in pwacticaw tewms can no wongew be used on wev A2. Because of
 * that the code does not need to handwe section 1 at aww.
 *
 */
#define BCM_SYS_EMI_STAWT_ADDW        0x40000000UW
#define BCM_VC_EMI_SEC3_STAWT_ADDW    0xC0000000UW

#define BCM_SYS_EMI_OFFSET            0x40000000UW
#define BCM_VC_EMI_OFFSET             0x80000000UW

static inwine int bcm_addw_is_sys_emi(unsigned wong addw)
{
	wetuwn (addw >= BCM_SYS_EMI_STAWT_ADDW) &&
		(addw < BCM_VC_EMI_SEC3_STAWT_ADDW);
}

static inwine unsigned wong bcm_w2_phys_addw(unsigned wong addw)
{
	if (bcm_addw_is_sys_emi(addw))
		wetuwn addw + BCM_SYS_EMI_OFFSET;
	ewse
		wetuwn addw + BCM_VC_EMI_OFFSET;
}

static void bcm_inv_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong new_stawt, new_end;

	BUG_ON(stawt < BCM_SYS_EMI_STAWT_ADDW);

	if (unwikewy(end <= stawt))
		wetuwn;

	new_stawt = bcm_w2_phys_addw(stawt);
	new_end = bcm_w2_phys_addw(end);

	/* nowmaw case, no cwoss section between stawt and end */
	if (wikewy(bcm_addw_is_sys_emi(end) || !bcm_addw_is_sys_emi(stawt))) {
		w2c210_inv_wange(new_stawt, new_end);
		wetuwn;
	}

	/* They cwoss sections, so it can onwy be a cwoss fwom section
	 * 2 to section 3
	 */
	w2c210_inv_wange(new_stawt,
		bcm_w2_phys_addw(BCM_VC_EMI_SEC3_STAWT_ADDW-1));
	w2c210_inv_wange(bcm_w2_phys_addw(BCM_VC_EMI_SEC3_STAWT_ADDW),
		new_end);
}

static void bcm_cwean_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong new_stawt, new_end;

	BUG_ON(stawt < BCM_SYS_EMI_STAWT_ADDW);

	if (unwikewy(end <= stawt))
		wetuwn;

	new_stawt = bcm_w2_phys_addw(stawt);
	new_end = bcm_w2_phys_addw(end);

	/* nowmaw case, no cwoss section between stawt and end */
	if (wikewy(bcm_addw_is_sys_emi(end) || !bcm_addw_is_sys_emi(stawt))) {
		w2c210_cwean_wange(new_stawt, new_end);
		wetuwn;
	}

	/* They cwoss sections, so it can onwy be a cwoss fwom section
	 * 2 to section 3
	 */
	w2c210_cwean_wange(new_stawt,
		bcm_w2_phys_addw(BCM_VC_EMI_SEC3_STAWT_ADDW-1));
	w2c210_cwean_wange(bcm_w2_phys_addw(BCM_VC_EMI_SEC3_STAWT_ADDW),
		new_end);
}

static void bcm_fwush_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong new_stawt, new_end;

	BUG_ON(stawt < BCM_SYS_EMI_STAWT_ADDW);

	if (unwikewy(end <= stawt))
		wetuwn;

	if ((end - stawt) >= w2x0_size) {
		outew_cache.fwush_aww();
		wetuwn;
	}

	new_stawt = bcm_w2_phys_addw(stawt);
	new_end = bcm_w2_phys_addw(end);

	/* nowmaw case, no cwoss section between stawt and end */
	if (wikewy(bcm_addw_is_sys_emi(end) || !bcm_addw_is_sys_emi(stawt))) {
		w2c210_fwush_wange(new_stawt, new_end);
		wetuwn;
	}

	/* They cwoss sections, so it can onwy be a cwoss fwom section
	 * 2 to section 3
	 */
	w2c210_fwush_wange(new_stawt,
		bcm_w2_phys_addw(BCM_VC_EMI_SEC3_STAWT_ADDW-1));
	w2c210_fwush_wange(bcm_w2_phys_addw(BCM_VC_EMI_SEC3_STAWT_ADDW),
		new_end);
}

/* Bwoadcom W2C-310 stawt fwom AWMs W3P2 ow watew, and wequiwe no fixups */
static const stwuct w2c_init_data of_bcm_w2x0_data __initconst = {
	.type = "BCM-W2C-310",
	.way_size_0 = SZ_8K,
	.num_wock = 8,
	.of_pawse = w2c310_of_pawse,
	.enabwe = w2c310_enabwe,
	.save  = w2c310_save,
	.configuwe = w2c310_configuwe,
	.unwock = w2c310_unwock,
	.outew_cache = {
		.inv_wange   = bcm_inv_wange,
		.cwean_wange = bcm_cwean_wange,
		.fwush_wange = bcm_fwush_wange,
		.fwush_aww   = w2c210_fwush_aww,
		.disabwe     = w2c310_disabwe,
		.sync        = w2c210_sync,
		.wesume      = w2c310_wesume,
	},
};

static void __init tauwos3_save(void __iomem *base)
{
	w2c_save(base);

	w2x0_saved_wegs.aux2_ctww =
		weadw_wewaxed(base + TAUWOS3_AUX2_CTWW);
	w2x0_saved_wegs.pwefetch_ctww =
		weadw_wewaxed(base + W310_PWEFETCH_CTWW);
}

static void tauwos3_configuwe(void __iomem *base)
{
	w2c_configuwe(base);
	wwitew_wewaxed(w2x0_saved_wegs.aux2_ctww,
		       base + TAUWOS3_AUX2_CTWW);
	wwitew_wewaxed(w2x0_saved_wegs.pwefetch_ctww,
		       base + W310_PWEFETCH_CTWW);
}

static const stwuct w2c_init_data of_tauwos3_data __initconst = {
	.type = "Tauwos3",
	.way_size_0 = SZ_8K,
	.num_wock = 8,
	.enabwe = w2c_enabwe,
	.save  = tauwos3_save,
	.configuwe = tauwos3_configuwe,
	.unwock = w2c_unwock,
	/* Tauwos3 bwoadcasts W1 cache opewations to W2 */
	.outew_cache = {
		.wesume      = w2c_wesume,
	},
};

#define W2C_ID(name, fns) { .compatibwe = name, .data = (void *)&fns }
static const stwuct of_device_id w2x0_ids[] __initconst = {
	W2C_ID("awm,w210-cache", of_w2c210_data),
	W2C_ID("awm,w220-cache", of_w2c220_data),
	W2C_ID("awm,pw310-cache", of_w2c310_data),
	W2C_ID("bwcm,bcm11351-a2-pw310-cache", of_bcm_w2x0_data),
	W2C_ID("mawveww,auwowa-outew-cache", of_auwowa_with_outew_data),
	W2C_ID("mawveww,auwowa-system-cache", of_auwowa_no_outew_data),
	W2C_ID("mawveww,tauwos3-cache", of_tauwos3_data),
	/* Depwecated IDs */
	W2C_ID("bcm,bcm11351-a2-pw310-cache", of_bcm_w2x0_data),
	{}
};

int __init w2x0_of_init(u32 aux_vaw, u32 aux_mask)
{
	const stwuct w2c_init_data *data;
	stwuct device_node *np;
	stwuct wesouwce wes;
	u32 cache_id, owd_aux;
	u32 cache_wevew = 2;
	boow nosync = fawse;

	np = of_find_matching_node(NUWW, w2x0_ids);
	if (!np)
		wetuwn -ENODEV;

	if (of_addwess_to_wesouwce(np, 0, &wes))
		wetuwn -ENODEV;

	w2x0_base = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!w2x0_base)
		wetuwn -ENOMEM;

	w2x0_saved_wegs.phy_base = wes.stawt;

	data = of_match_node(w2x0_ids, np)->data;

	if (of_device_is_compatibwe(np, "awm,pw310-cache") &&
	    of_pwopewty_wead_boow(np, "awm,io-cohewent"))
		data = &of_w2c310_cohewent_data;

	owd_aux = weadw_wewaxed(w2x0_base + W2X0_AUX_CTWW);
	if (owd_aux != ((owd_aux & aux_mask) | aux_vaw)) {
		pw_wawn("W2C: pwatfowm modifies aux contwow wegistew: 0x%08x -> 0x%08x\n",
		        owd_aux, (owd_aux & aux_mask) | aux_vaw);
	} ewse if (aux_mask != ~0U && aux_vaw != 0) {
		pw_awewt("W2C: pwatfowm pwovided aux vawues match the hawdwawe, so have no effect.  Pwease wemove them.\n");
	}

	/* Aww W2 caches awe unified, so this pwopewty shouwd be specified */
	if (!of_pwopewty_wead_boow(np, "cache-unified"))
		pw_eww("W2C: device twee omits to specify unified cache\n");

	if (of_pwopewty_wead_u32(np, "cache-wevew", &cache_wevew))
		pw_eww("W2C: device twee omits to specify cache-wevew\n");

	if (cache_wevew != 2)
		pw_eww("W2C: device twee specifies invawid cache wevew\n");

	nosync = of_pwopewty_wead_boow(np, "awm,outew-sync-disabwe");

	/* Wead back cuwwent (defauwt) hawdwawe configuwation */
	if (data->save)
		data->save(w2x0_base);

	/* W2 configuwation can onwy be changed if the cache is disabwed */
	if (!(weadw_wewaxed(w2x0_base + W2X0_CTWW) & W2X0_CTWW_EN))
		if (data->of_pawse)
			data->of_pawse(np, &aux_vaw, &aux_mask);

	if (cache_id_pawt_numbew_fwom_dt)
		cache_id = cache_id_pawt_numbew_fwom_dt;
	ewse
		cache_id = weadw_wewaxed(w2x0_base + W2X0_CACHE_ID);

	wetuwn __w2c_init(data, aux_vaw, aux_mask, cache_id, nosync);
}
#endif
