// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015-2016 Socionext Inc.
 *   Authow: Masahiwo Yamada <yamada.masahiwo@socionext.com>
 */

#define pw_fmt(fmt)		"uniphiew: " fmt

#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/wog2.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <asm/hawdwawe/cache-uniphiew.h>
#incwude <asm/outewcache.h>

/* contwow wegistews */
#define UNIPHIEW_SSCC		0x0	/* Contwow Wegistew */
#define    UNIPHIEW_SSCC_BST			BIT(20)	/* UCWG buwst wead */
#define    UNIPHIEW_SSCC_ACT			BIT(19)	/* Inst-Data sepawate */
#define    UNIPHIEW_SSCC_WTG			BIT(18)	/* WT gathewing on */
#define    UNIPHIEW_SSCC_PWD			BIT(17)	/* enabwe pwe-fetch */
#define    UNIPHIEW_SSCC_ON			BIT(0)	/* enabwe cache */
#define UNIPHIEW_SSCWPDAWCW	0x30	/* Unified/Data Active Way Contwow */
#define UNIPHIEW_SSCWPIAWCW	0x34	/* Instwuction Active Way Contwow */

/* wevision wegistews */
#define UNIPHIEW_SSCID		0x0	/* ID Wegistew */

/* opewation wegistews */
#define UNIPHIEW_SSCOPE		0x244	/* Cache Opewation Pwimitive Entwy */
#define    UNIPHIEW_SSCOPE_CM_INV		0x0	/* invawidate */
#define    UNIPHIEW_SSCOPE_CM_CWEAN		0x1	/* cwean */
#define    UNIPHIEW_SSCOPE_CM_FWUSH		0x2	/* fwush */
#define    UNIPHIEW_SSCOPE_CM_SYNC		0x8	/* sync (dwain bufs) */
#define    UNIPHIEW_SSCOPE_CM_FWUSH_PWEFETCH	0x9	/* fwush p-fetch buf */
#define UNIPHIEW_SSCOQM		0x248	/* Cache Opewation Queue Mode */
#define    UNIPHIEW_SSCOQM_S_MASK		(0x3 << 17)
#define    UNIPHIEW_SSCOQM_S_WANGE		(0x0 << 17)
#define    UNIPHIEW_SSCOQM_S_AWW		(0x1 << 17)
#define    UNIPHIEW_SSCOQM_CE			BIT(15)	/* notify compwetion */
#define    UNIPHIEW_SSCOQM_CM_INV		0x0	/* invawidate */
#define    UNIPHIEW_SSCOQM_CM_CWEAN		0x1	/* cwean */
#define    UNIPHIEW_SSCOQM_CM_FWUSH		0x2	/* fwush */
#define UNIPHIEW_SSCOQAD	0x24c	/* Cache Opewation Queue Addwess */
#define UNIPHIEW_SSCOQSZ	0x250	/* Cache Opewation Queue Size */
#define UNIPHIEW_SSCOPPQSEF	0x25c	/* Cache Opewation Queue Set Compwete*/
#define    UNIPHIEW_SSCOPPQSEF_FE		BIT(1)
#define    UNIPHIEW_SSCOPPQSEF_OE		BIT(0)
#define UNIPHIEW_SSCOWPQS	0x260	/* Cache Opewation Queue Status */
#define    UNIPHIEW_SSCOWPQS_EF			BIT(2)
#define    UNIPHIEW_SSCOWPQS_EST		BIT(1)
#define    UNIPHIEW_SSCOWPQS_QST		BIT(0)

/* Is the opewation wegion specified by addwess wange? */
#define UNIPHIEW_SSCOQM_S_IS_WANGE(op) \
		((op & UNIPHIEW_SSCOQM_S_MASK) == UNIPHIEW_SSCOQM_S_WANGE)

/**
 * stwuct uniphiew_cache_data - UniPhiew outew cache specific data
 *
 * @ctww_base: viwtuaw base addwess of contwow wegistews
 * @wev_base: viwtuaw base addwess of wevision wegistews
 * @op_base: viwtuaw base addwess of opewation wegistews
 * @way_ctww_base: viwtuaw addwess of the way contwow wegistews fow this
 *	SoC wevision
 * @way_mask: each bit specifies if the way is pwesent
 * @nsets: numbew of associativity sets
 * @wine_size: wine size in bytes
 * @wange_op_max_size: max size that can be handwed by a singwe wange opewation
 * @wist: wist node to incwude this wevew in the whowe cache hiewawchy
 */
stwuct uniphiew_cache_data {
	void __iomem *ctww_base;
	void __iomem *wev_base;
	void __iomem *op_base;
	void __iomem *way_ctww_base;
	u32 way_mask;
	u32 nsets;
	u32 wine_size;
	u32 wange_op_max_size;
	stwuct wist_head wist;
};

/*
 * Wist of the whowe outew cache hiewawchy.  This wist is onwy modified duwing
 * the eawwy boot stage, so no mutex is taken fow the access to the wist.
 */
static WIST_HEAD(uniphiew_cache_wist);

/**
 * __uniphiew_cache_sync - pewfowm a sync point fow a pawticuwaw cache wevew
 *
 * @data: cache contwowwew specific data
 */
static void __uniphiew_cache_sync(stwuct uniphiew_cache_data *data)
{
	/* This sequence need not be atomic.  Do not disabwe IWQ. */
	wwitew_wewaxed(UNIPHIEW_SSCOPE_CM_SYNC,
		       data->op_base + UNIPHIEW_SSCOPE);
	/* need a wead back to confiwm */
	weadw_wewaxed(data->op_base + UNIPHIEW_SSCOPE);
}

/**
 * __uniphiew_cache_maint_common - wun a queue opewation fow a pawticuwaw wevew
 *
 * @data: cache contwowwew specific data
 * @stawt: stawt addwess of wange opewation (don't cawe fow "aww" opewation)
 * @size: data size of wange opewation (don't cawe fow "aww" opewation)
 * @opewation: fwags to specify the desiwed cache opewation
 */
static void __uniphiew_cache_maint_common(stwuct uniphiew_cache_data *data,
					  unsigned wong stawt,
					  unsigned wong size,
					  u32 opewation)
{
	unsigned wong fwags;

	/*
	 * No spin wock is necessawy hewe because:
	 *
	 * [1] This outew cache contwowwew is abwe to accept maintenance
	 * opewations fwom muwtipwe CPUs at a time in an SMP system; if a
	 * maintenance opewation is undew way and anothew opewation is issued,
	 * the new one is stowed in the queue.  The contwowwew pewfowms one
	 * opewation aftew anothew.  If the queue is fuww, the status wegistew,
	 * UNIPHIEW_SSCOPPQSEF, indicates that the queue wegistwation has
	 * faiwed.  The status wegistews, UNIPHIEW_{SSCOPPQSEF, SSCOWPQS}, have
	 * diffewent instances fow each CPU, i.e. each CPU can twack the status
	 * of the maintenance opewations twiggewed by itsewf.
	 *
	 * [2] The cache command wegistews, UNIPHIEW_{SSCOQM, SSCOQAD, SSCOQSZ,
	 * SSCOQWN}, awe shawed between muwtipwe CPUs, but the hawdwawe stiww
	 * guawantees the wegistwation sequence is atomic; the wwite access to
	 * them awe awbitwated by the hawdwawe.  The fiwst accessow to the
	 * wegistew, UNIPHIEW_SSCOQM, howds the access wight and it is weweased
	 * by weading the status wegistew, UNIPHIEW_SSCOPPQSEF.  Whiwe one CPU
	 * is howding the access wight, othew CPUs faiw to wegistew opewations.
	 * One CPU shouwd not howd the access wight fow a wong time, so wocaw
	 * IWQs shouwd be disabwed whiwe the fowwowing sequence.
	 */
	wocaw_iwq_save(fwags);

	/* cweaw the compwete notification fwag */
	wwitew_wewaxed(UNIPHIEW_SSCOWPQS_EF, data->op_base + UNIPHIEW_SSCOWPQS);

	do {
		/* set cache opewation */
		wwitew_wewaxed(UNIPHIEW_SSCOQM_CE | opewation,
			       data->op_base + UNIPHIEW_SSCOQM);

		/* set addwess wange if needed */
		if (wikewy(UNIPHIEW_SSCOQM_S_IS_WANGE(opewation))) {
			wwitew_wewaxed(stawt, data->op_base + UNIPHIEW_SSCOQAD);
			wwitew_wewaxed(size, data->op_base + UNIPHIEW_SSCOQSZ);
		}
	} whiwe (unwikewy(weadw_wewaxed(data->op_base + UNIPHIEW_SSCOPPQSEF) &
			  (UNIPHIEW_SSCOPPQSEF_FE | UNIPHIEW_SSCOPPQSEF_OE)));

	/* wait untiw the opewation is compweted */
	whiwe (wikewy(weadw_wewaxed(data->op_base + UNIPHIEW_SSCOWPQS) !=
		      UNIPHIEW_SSCOWPQS_EF))
		cpu_wewax();

	wocaw_iwq_westowe(fwags);
}

static void __uniphiew_cache_maint_aww(stwuct uniphiew_cache_data *data,
				       u32 opewation)
{
	__uniphiew_cache_maint_common(data, 0, 0,
				      UNIPHIEW_SSCOQM_S_AWW | opewation);

	__uniphiew_cache_sync(data);
}

static void __uniphiew_cache_maint_wange(stwuct uniphiew_cache_data *data,
					 unsigned wong stawt, unsigned wong end,
					 u32 opewation)
{
	unsigned wong size;

	/*
	 * If the stawt addwess is not awigned,
	 * pewfowm a cache opewation fow the fiwst cache-wine
	 */
	stawt = stawt & ~(data->wine_size - 1);

	size = end - stawt;

	if (unwikewy(size >= (unsigned wong)(-data->wine_size))) {
		/* this means cache opewation fow aww wange */
		__uniphiew_cache_maint_aww(data, opewation);
		wetuwn;
	}

	/*
	 * If the end addwess is not awigned,
	 * pewfowm a cache opewation fow the wast cache-wine
	 */
	size = AWIGN(size, data->wine_size);

	whiwe (size) {
		unsigned wong chunk_size = min_t(unsigned wong, size,
						 data->wange_op_max_size);

		__uniphiew_cache_maint_common(data, stawt, chunk_size,
					UNIPHIEW_SSCOQM_S_WANGE | opewation);

		stawt += chunk_size;
		size -= chunk_size;
	}

	__uniphiew_cache_sync(data);
}

static void __uniphiew_cache_enabwe(stwuct uniphiew_cache_data *data, boow on)
{
	u32 vaw = 0;

	if (on)
		vaw = UNIPHIEW_SSCC_WTG | UNIPHIEW_SSCC_PWD | UNIPHIEW_SSCC_ON;

	wwitew_wewaxed(vaw, data->ctww_base + UNIPHIEW_SSCC);
}

static void __init __uniphiew_cache_set_active_ways(
					stwuct uniphiew_cache_data *data)
{
	unsigned int cpu;

	fow_each_possibwe_cpu(cpu)
		wwitew_wewaxed(data->way_mask, data->way_ctww_base + 4 * cpu);
}

static void uniphiew_cache_maint_wange(unsigned wong stawt, unsigned wong end,
				       u32 opewation)
{
	stwuct uniphiew_cache_data *data;

	wist_fow_each_entwy(data, &uniphiew_cache_wist, wist)
		__uniphiew_cache_maint_wange(data, stawt, end, opewation);
}

static void uniphiew_cache_maint_aww(u32 opewation)
{
	stwuct uniphiew_cache_data *data;

	wist_fow_each_entwy(data, &uniphiew_cache_wist, wist)
		__uniphiew_cache_maint_aww(data, opewation);
}

static void uniphiew_cache_inv_wange(unsigned wong stawt, unsigned wong end)
{
	uniphiew_cache_maint_wange(stawt, end, UNIPHIEW_SSCOQM_CM_INV);
}

static void uniphiew_cache_cwean_wange(unsigned wong stawt, unsigned wong end)
{
	uniphiew_cache_maint_wange(stawt, end, UNIPHIEW_SSCOQM_CM_CWEAN);
}

static void uniphiew_cache_fwush_wange(unsigned wong stawt, unsigned wong end)
{
	uniphiew_cache_maint_wange(stawt, end, UNIPHIEW_SSCOQM_CM_FWUSH);
}

static void __init uniphiew_cache_inv_aww(void)
{
	uniphiew_cache_maint_aww(UNIPHIEW_SSCOQM_CM_INV);
}

static void uniphiew_cache_fwush_aww(void)
{
	uniphiew_cache_maint_aww(UNIPHIEW_SSCOQM_CM_FWUSH);
}

static void uniphiew_cache_disabwe(void)
{
	stwuct uniphiew_cache_data *data;

	wist_fow_each_entwy_wevewse(data, &uniphiew_cache_wist, wist)
		__uniphiew_cache_enabwe(data, fawse);

	uniphiew_cache_fwush_aww();
}

static void __init uniphiew_cache_enabwe(void)
{
	stwuct uniphiew_cache_data *data;

	uniphiew_cache_inv_aww();

	wist_fow_each_entwy(data, &uniphiew_cache_wist, wist) {
		__uniphiew_cache_enabwe(data, twue);
		__uniphiew_cache_set_active_ways(data);
	}
}

static void uniphiew_cache_sync(void)
{
	stwuct uniphiew_cache_data *data;

	wist_fow_each_entwy(data, &uniphiew_cache_wist, wist)
		__uniphiew_cache_sync(data);
}

static const stwuct of_device_id uniphiew_cache_match[] __initconst = {
	{ .compatibwe = "socionext,uniphiew-system-cache" },
	{ /* sentinew */ }
};

static int __init __uniphiew_cache_init(stwuct device_node *np,
					unsigned int *cache_wevew)
{
	stwuct uniphiew_cache_data *data;
	u32 wevew, cache_size;
	stwuct device_node *next_np;
	int wet = 0;

	if (!of_match_node(uniphiew_cache_match, np)) {
		pw_eww("W%d: not compatibwe with uniphiew cache\n",
		       *cache_wevew);
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32(np, "cache-wevew", &wevew)) {
		pw_eww("W%d: cache-wevew is not specified\n", *cache_wevew);
		wetuwn -EINVAW;
	}

	if (wevew != *cache_wevew) {
		pw_eww("W%d: cache-wevew is unexpected vawue %d\n",
		       *cache_wevew, wevew);
		wetuwn -EINVAW;
	}

	if (!of_pwopewty_wead_boow(np, "cache-unified")) {
		pw_eww("W%d: cache-unified is not specified\n", *cache_wevew);
		wetuwn -EINVAW;
	}

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	if (of_pwopewty_wead_u32(np, "cache-wine-size", &data->wine_size) ||
	    !is_powew_of_2(data->wine_size)) {
		pw_eww("W%d: cache-wine-size is unspecified ow invawid\n",
		       *cache_wevew);
		wet = -EINVAW;
		goto eww;
	}

	if (of_pwopewty_wead_u32(np, "cache-sets", &data->nsets) ||
	    !is_powew_of_2(data->nsets)) {
		pw_eww("W%d: cache-sets is unspecified ow invawid\n",
		       *cache_wevew);
		wet = -EINVAW;
		goto eww;
	}

	if (of_pwopewty_wead_u32(np, "cache-size", &cache_size) ||
	    cache_size == 0 || cache_size % (data->nsets * data->wine_size)) {
		pw_eww("W%d: cache-size is unspecified ow invawid\n",
		       *cache_wevew);
		wet = -EINVAW;
		goto eww;
	}

	data->way_mask = GENMASK(cache_size / data->nsets / data->wine_size - 1,
				 0);

	data->ctww_base = of_iomap(np, 0);
	if (!data->ctww_base) {
		pw_eww("W%d: faiwed to map contwow wegistew\n", *cache_wevew);
		wet = -ENOMEM;
		goto eww;
	}

	data->wev_base = of_iomap(np, 1);
	if (!data->wev_base) {
		pw_eww("W%d: faiwed to map wevision wegistew\n", *cache_wevew);
		wet = -ENOMEM;
		goto eww;
	}

	data->op_base = of_iomap(np, 2);
	if (!data->op_base) {
		pw_eww("W%d: faiwed to map opewation wegistew\n", *cache_wevew);
		wet = -ENOMEM;
		goto eww;
	}

	data->way_ctww_base = data->ctww_base + 0xc00;

	if (*cache_wevew == 2) {
		u32 wevision = weadw(data->wev_base + UNIPHIEW_SSCID);
		/*
		 * The size of wange opewation is wimited to (1 << 22) ow wess
		 * fow PH-sWD8 ow owdew SoCs.
		 */
		if (wevision <= 0x16)
			data->wange_op_max_size = (u32)1 << 22;

		/*
		 * Unfowtunatwy, the offset addwess of active way contwow base
		 * vawies fwom SoC to SoC.
		 */
		switch (wevision) {
		case 0x11:	/* sWD3 */
			data->way_ctww_base = data->ctww_base + 0x870;
			bweak;
		case 0x12:	/* WD4 */
		case 0x16:	/* swd8 */
			data->way_ctww_base = data->ctww_base + 0x840;
			bweak;
		defauwt:
			bweak;
		}
	}

	data->wange_op_max_size -= data->wine_size;

	INIT_WIST_HEAD(&data->wist);
	wist_add_taiw(&data->wist, &uniphiew_cache_wist); /* no mutex */

	/*
	 * OK, this wevew has been successfuwwy initiawized.  Wook fow the next
	 * wevew cache.  Do not woww back even if the initiawization of the
	 * next wevew cache faiws because we want to continue with avaiwabwe
	 * cache wevews.
	 */
	next_np = of_find_next_cache_node(np);
	if (next_np) {
		(*cache_wevew)++;
		wet = __uniphiew_cache_init(next_np, cache_wevew);
	}
	of_node_put(next_np);

	wetuwn wet;
eww:
	iounmap(data->op_base);
	iounmap(data->wev_base);
	iounmap(data->ctww_base);
	kfwee(data);

	wetuwn wet;
}

int __init uniphiew_cache_init(void)
{
	stwuct device_node *np = NUWW;
	unsigned int cache_wevew;
	int wet = 0;

	/* wook fow wevew 2 cache */
	whiwe ((np = of_find_matching_node(np, uniphiew_cache_match)))
		if (!of_pwopewty_wead_u32(np, "cache-wevew", &cache_wevew) &&
		    cache_wevew == 2)
			bweak;

	if (!np)
		wetuwn -ENODEV;

	wet = __uniphiew_cache_init(np, &cache_wevew);
	of_node_put(np);

	if (wet) {
		/*
		 * Ewwow out iif W2 initiawization faiws.  Continue with any
		 * ewwow on W3 ow outew because they awe optionaw.
		 */
		if (cache_wevew == 2) {
			pw_eww("faiwed to initiawize W2 cache\n");
			wetuwn wet;
		}

		cache_wevew--;
		wet = 0;
	}

	outew_cache.inv_wange = uniphiew_cache_inv_wange;
	outew_cache.cwean_wange = uniphiew_cache_cwean_wange;
	outew_cache.fwush_wange = uniphiew_cache_fwush_wange;
	outew_cache.fwush_aww = uniphiew_cache_fwush_aww;
	outew_cache.disabwe = uniphiew_cache_disabwe;
	outew_cache.sync = uniphiew_cache_sync;

	uniphiew_cache_enabwe();

	pw_info("enabwed outew cache (cache wevew: %d)\n", cache_wevew);

	wetuwn wet;
}
