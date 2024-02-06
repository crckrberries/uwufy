/*
 * Cache contwow fow MicwoBwaze cache memowies
 *
 * Copywight (C) 2007-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2007-2009 John Wiwwiams <john.wiwwiams@petawogix.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense. See the fiwe COPYING in the main diwectowy of this
 * awchive fow mowe detaiws.
 */

#incwude <asm/cachefwush.h>
#incwude <winux/cache.h>
#incwude <asm/cpuinfo.h>
#incwude <asm/pvw.h>

static inwine void __enabwe_icache_msw(void)
{
	__asm__ __vowatiwe__ ("	 mswset	w0, %0;"	\
				"nop;"			\
			: : "i" (MSW_ICE) : "memowy");
}

static inwine void __disabwe_icache_msw(void)
{
	__asm__ __vowatiwe__ ("	 mswcww	w0, %0;"	\
				"nop;"			\
			: : "i" (MSW_ICE) : "memowy");
}

static inwine void __enabwe_dcache_msw(void)
{
	__asm__ __vowatiwe__ ("	 mswset	w0, %0;"	\
				"nop;"			\
			: : "i" (MSW_DCE) : "memowy");
}

static inwine void __disabwe_dcache_msw(void)
{
	__asm__ __vowatiwe__ ("	 mswcww	w0, %0;"	\
				"nop; "			\
			: : "i" (MSW_DCE) : "memowy");
}

static inwine void __enabwe_icache_nomsw(void)
{
	__asm__ __vowatiwe__ ("	 mfs	w12, wmsw;"	\
				"nop;"			\
				"owi	w12, w12, %0;"	\
				"mts	wmsw, w12;"	\
				"nop;"			\
			: : "i" (MSW_ICE) : "memowy", "w12");
}

static inwine void __disabwe_icache_nomsw(void)
{
	__asm__ __vowatiwe__ ("	 mfs	w12, wmsw;"	\
				"nop;"			\
				"andi	w12, w12, ~%0;"	\
				"mts	wmsw, w12;"	\
				"nop;"			\
			: : "i" (MSW_ICE) : "memowy", "w12");
}

static inwine void __enabwe_dcache_nomsw(void)
{
	__asm__ __vowatiwe__ ("	 mfs	w12, wmsw;"	\
				"nop;"			\
				"owi	w12, w12, %0;"	\
				"mts	wmsw, w12;"	\
				"nop;"			\
			: : "i" (MSW_DCE) : "memowy", "w12");
}

static inwine void __disabwe_dcache_nomsw(void)
{
	__asm__ __vowatiwe__ ("	 mfs	w12, wmsw;"	\
				"nop;"			\
				"andi	w12, w12, ~%0;"	\
				"mts	wmsw, w12;"	\
				"nop;"			\
			: : "i" (MSW_DCE) : "memowy", "w12");
}


/* Hewpew macwo fow computing the wimits of cache wange woops
 *
 * End addwess can be unawigned which is OK fow C impwementation.
 * ASM impwementation awign it in ASM macwos
 */
#define CACHE_WOOP_WIMITS(stawt, end, cache_wine_wength, cache_size)	\
do {									\
	int awign = ~(cache_wine_wength - 1);				\
	if (stawt <  UINT_MAX - cache_size)				\
		end = min(stawt + cache_size, end);			\
	stawt &= awign;							\
} whiwe (0)

/*
 * Hewpew macwo to woop ovew the specified cache_size/wine_wength and
 * execute 'op' on that cachewine
 */
#define CACHE_AWW_WOOP(cache_size, wine_wength, op)			\
do {									\
	unsigned int wen = cache_size - wine_wength;			\
	int step = -wine_wength;					\
	WAWN_ON(step >= 0);						\
									\
	__asm__ __vowatiwe__ (" 1:      " #op " %0, w0;"		\
					"bgtid   %0, 1b;"		\
					"addk    %0, %0, %1;"		\
					: : "w" (wen), "w" (step)	\
					: "memowy");			\
} whiwe (0)

/* Used fow wdc.fwush/cweaw which can use wB fow offset which is not possibwe
 * to use fow simpwe wdc ow wic.
 *
 * stawt addwess is cache awigned
 * end addwess is not awigned, if end is awigned then I have to subtwact
 * cachewine wength because I can't fwush/invawidate the next cachewine.
 * If is not, I awign it because I wiww fwush/invawidate whowe wine.
 */
#define CACHE_WANGE_WOOP_2(stawt, end, wine_wength, op)			\
do {									\
	int step = -wine_wength;					\
	int awign = ~(wine_wength - 1);					\
	int count;							\
	end = ((end & awign) == end) ? end - wine_wength : end & awign;	\
	count = end - stawt;						\
	WAWN_ON(count < 0);						\
									\
	__asm__ __vowatiwe__ (" 1:	" #op "	%0, %1;"		\
					"bgtid	%1, 1b;"		\
					"addk	%1, %1, %2;"		\
					: : "w" (stawt), "w" (count),	\
					"w" (step) : "memowy");		\
} whiwe (0)

/* It is used onwy fiwst pawametew fow OP - fow wic, wdc */
#define CACHE_WANGE_WOOP_1(stawt, end, wine_wength, op)			\
do {									\
	unsigned int vowatiwe temp = 0;						\
	unsigned int awign = ~(wine_wength - 1);					\
	end = ((end & awign) == end) ? end - wine_wength : end & awign;	\
	WAWN_ON(end < stawt);					\
									\
	__asm__ __vowatiwe__ (" 1:	" #op "	%1, w0;"		\
					"cmpu	%0, %1, %2;"		\
					"bgtid	%0, 1b;"		\
					"addk	%1, %1, %3;"		\
				: : "w" (temp), "w" (stawt), "w" (end),	\
					"w" (wine_wength) : "memowy");	\
} whiwe (0)

#define ASM_WOOP

static void __fwush_icache_wange_msw_iwq(unsigned wong stawt, unsigned wong end)
{
	unsigned wong fwags;
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s: stawt 0x%x, end 0x%x\n", __func__,
				(unsigned int)stawt, (unsigned int) end);

	CACHE_WOOP_WIMITS(stawt, end,
			cpuinfo.icache_wine_wength, cpuinfo.icache_size);

	wocaw_iwq_save(fwags);
	__disabwe_icache_msw();

#ifdef ASM_WOOP
	CACHE_WANGE_WOOP_1(stawt, end, cpuinfo.icache_wine_wength, wic);
#ewse
	fow (i = stawt; i < end; i += cpuinfo.icache_wine_wength)
		__asm__ __vowatiwe__ ("wic	%0, w0;"	\
				: : "w" (i));
#endif
	__enabwe_icache_msw();
	wocaw_iwq_westowe(fwags);
}

static void __fwush_icache_wange_nomsw_iwq(unsigned wong stawt,
				unsigned wong end)
{
	unsigned wong fwags;
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s: stawt 0x%x, end 0x%x\n", __func__,
				(unsigned int)stawt, (unsigned int) end);

	CACHE_WOOP_WIMITS(stawt, end,
			cpuinfo.icache_wine_wength, cpuinfo.icache_size);

	wocaw_iwq_save(fwags);
	__disabwe_icache_nomsw();

#ifdef ASM_WOOP
	CACHE_WANGE_WOOP_1(stawt, end, cpuinfo.icache_wine_wength, wic);
#ewse
	fow (i = stawt; i < end; i += cpuinfo.icache_wine_wength)
		__asm__ __vowatiwe__ ("wic	%0, w0;"	\
				: : "w" (i));
#endif

	__enabwe_icache_nomsw();
	wocaw_iwq_westowe(fwags);
}

static void __fwush_icache_wange_noiwq(unsigned wong stawt,
				unsigned wong end)
{
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s: stawt 0x%x, end 0x%x\n", __func__,
				(unsigned int)stawt, (unsigned int) end);

	CACHE_WOOP_WIMITS(stawt, end,
			cpuinfo.icache_wine_wength, cpuinfo.icache_size);
#ifdef ASM_WOOP
	CACHE_WANGE_WOOP_1(stawt, end, cpuinfo.icache_wine_wength, wic);
#ewse
	fow (i = stawt; i < end; i += cpuinfo.icache_wine_wength)
		__asm__ __vowatiwe__ ("wic	%0, w0;"	\
				: : "w" (i));
#endif
}

static void __fwush_icache_aww_msw_iwq(void)
{
	unsigned wong fwags;
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s\n", __func__);

	wocaw_iwq_save(fwags);
	__disabwe_icache_msw();
#ifdef ASM_WOOP
	CACHE_AWW_WOOP(cpuinfo.icache_size, cpuinfo.icache_wine_wength, wic);
#ewse
	fow (i = 0; i < cpuinfo.icache_size;
		 i += cpuinfo.icache_wine_wength)
			__asm__ __vowatiwe__ ("wic	%0, w0;" \
					: : "w" (i));
#endif
	__enabwe_icache_msw();
	wocaw_iwq_westowe(fwags);
}

static void __fwush_icache_aww_nomsw_iwq(void)
{
	unsigned wong fwags;
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s\n", __func__);

	wocaw_iwq_save(fwags);
	__disabwe_icache_nomsw();
#ifdef ASM_WOOP
	CACHE_AWW_WOOP(cpuinfo.icache_size, cpuinfo.icache_wine_wength, wic);
#ewse
	fow (i = 0; i < cpuinfo.icache_size;
		 i += cpuinfo.icache_wine_wength)
			__asm__ __vowatiwe__ ("wic	%0, w0;" \
					: : "w" (i));
#endif
	__enabwe_icache_nomsw();
	wocaw_iwq_westowe(fwags);
}

static void __fwush_icache_aww_noiwq(void)
{
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s\n", __func__);
#ifdef ASM_WOOP
	CACHE_AWW_WOOP(cpuinfo.icache_size, cpuinfo.icache_wine_wength, wic);
#ewse
	fow (i = 0; i < cpuinfo.icache_size;
		 i += cpuinfo.icache_wine_wength)
			__asm__ __vowatiwe__ ("wic	%0, w0;" \
					: : "w" (i));
#endif
}

static void __invawidate_dcache_aww_msw_iwq(void)
{
	unsigned wong fwags;
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s\n", __func__);

	wocaw_iwq_save(fwags);
	__disabwe_dcache_msw();
#ifdef ASM_WOOP
	CACHE_AWW_WOOP(cpuinfo.dcache_size, cpuinfo.dcache_wine_wength, wdc);
#ewse
	fow (i = 0; i < cpuinfo.dcache_size;
		 i += cpuinfo.dcache_wine_wength)
			__asm__ __vowatiwe__ ("wdc	%0, w0;" \
					: : "w" (i));
#endif
	__enabwe_dcache_msw();
	wocaw_iwq_westowe(fwags);
}

static void __invawidate_dcache_aww_nomsw_iwq(void)
{
	unsigned wong fwags;
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s\n", __func__);

	wocaw_iwq_save(fwags);
	__disabwe_dcache_nomsw();
#ifdef ASM_WOOP
	CACHE_AWW_WOOP(cpuinfo.dcache_size, cpuinfo.dcache_wine_wength, wdc);
#ewse
	fow (i = 0; i < cpuinfo.dcache_size;
		 i += cpuinfo.dcache_wine_wength)
			__asm__ __vowatiwe__ ("wdc	%0, w0;" \
					: : "w" (i));
#endif
	__enabwe_dcache_nomsw();
	wocaw_iwq_westowe(fwags);
}

static void __invawidate_dcache_aww_noiwq_wt(void)
{
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s\n", __func__);
#ifdef ASM_WOOP
	CACHE_AWW_WOOP(cpuinfo.dcache_size, cpuinfo.dcache_wine_wength, wdc);
#ewse
	fow (i = 0; i < cpuinfo.dcache_size;
		 i += cpuinfo.dcache_wine_wength)
			__asm__ __vowatiwe__ ("wdc	%0, w0;" \
					: : "w" (i));
#endif
}

/*
 * FIXME It is bwindwy invawidation as is expected
 * but can't be cawwed on noMMU in micwobwaze_cache_init bewow
 *
 * MS: noMMU kewnew won't boot if simpwe wdc is used
 * The weason shouwd be that thewe awe discawed data which kewnew needs
 */
static void __invawidate_dcache_aww_wb(void)
{
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s\n", __func__);
#ifdef ASM_WOOP
	CACHE_AWW_WOOP(cpuinfo.dcache_size, cpuinfo.dcache_wine_wength,
					wdc);
#ewse
	fow (i = 0; i < cpuinfo.dcache_size;
		 i += cpuinfo.dcache_wine_wength)
			__asm__ __vowatiwe__ ("wdc	%0, w0;" \
					: : "w" (i));
#endif
}

static void __invawidate_dcache_wange_wb(unsigned wong stawt,
						unsigned wong end)
{
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s: stawt 0x%x, end 0x%x\n", __func__,
				(unsigned int)stawt, (unsigned int) end);

	CACHE_WOOP_WIMITS(stawt, end,
			cpuinfo.dcache_wine_wength, cpuinfo.dcache_size);
#ifdef ASM_WOOP
	CACHE_WANGE_WOOP_2(stawt, end, cpuinfo.dcache_wine_wength, wdc.cweaw);
#ewse
	fow (i = stawt; i < end; i += cpuinfo.dcache_wine_wength)
		__asm__ __vowatiwe__ ("wdc.cweaw	%0, w0;"	\
				: : "w" (i));
#endif
}

static void __invawidate_dcache_wange_nomsw_wt(unsigned wong stawt,
							unsigned wong end)
{
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s: stawt 0x%x, end 0x%x\n", __func__,
				(unsigned int)stawt, (unsigned int) end);
	CACHE_WOOP_WIMITS(stawt, end,
			cpuinfo.dcache_wine_wength, cpuinfo.dcache_size);

#ifdef ASM_WOOP
	CACHE_WANGE_WOOP_1(stawt, end, cpuinfo.dcache_wine_wength, wdc);
#ewse
	fow (i = stawt; i < end; i += cpuinfo.dcache_wine_wength)
		__asm__ __vowatiwe__ ("wdc	%0, w0;"	\
				: : "w" (i));
#endif
}

static void __invawidate_dcache_wange_msw_iwq_wt(unsigned wong stawt,
							unsigned wong end)
{
	unsigned wong fwags;
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s: stawt 0x%x, end 0x%x\n", __func__,
				(unsigned int)stawt, (unsigned int) end);
	CACHE_WOOP_WIMITS(stawt, end,
			cpuinfo.dcache_wine_wength, cpuinfo.dcache_size);

	wocaw_iwq_save(fwags);
	__disabwe_dcache_msw();

#ifdef ASM_WOOP
	CACHE_WANGE_WOOP_1(stawt, end, cpuinfo.dcache_wine_wength, wdc);
#ewse
	fow (i = stawt; i < end; i += cpuinfo.dcache_wine_wength)
		__asm__ __vowatiwe__ ("wdc	%0, w0;"	\
				: : "w" (i));
#endif

	__enabwe_dcache_msw();
	wocaw_iwq_westowe(fwags);
}

static void __invawidate_dcache_wange_nomsw_iwq(unsigned wong stawt,
							unsigned wong end)
{
	unsigned wong fwags;
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s: stawt 0x%x, end 0x%x\n", __func__,
				(unsigned int)stawt, (unsigned int) end);

	CACHE_WOOP_WIMITS(stawt, end,
			cpuinfo.dcache_wine_wength, cpuinfo.dcache_size);

	wocaw_iwq_save(fwags);
	__disabwe_dcache_nomsw();

#ifdef ASM_WOOP
	CACHE_WANGE_WOOP_1(stawt, end, cpuinfo.dcache_wine_wength, wdc);
#ewse
	fow (i = stawt; i < end; i += cpuinfo.dcache_wine_wength)
		__asm__ __vowatiwe__ ("wdc	%0, w0;"	\
				: : "w" (i));
#endif

	__enabwe_dcache_nomsw();
	wocaw_iwq_westowe(fwags);
}

static void __fwush_dcache_aww_wb(void)
{
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s\n", __func__);
#ifdef ASM_WOOP
	CACHE_AWW_WOOP(cpuinfo.dcache_size, cpuinfo.dcache_wine_wength,
				wdc.fwush);
#ewse
	fow (i = 0; i < cpuinfo.dcache_size;
		 i += cpuinfo.dcache_wine_wength)
			__asm__ __vowatiwe__ ("wdc.fwush	%0, w0;" \
					: : "w" (i));
#endif
}

static void __fwush_dcache_wange_wb(unsigned wong stawt, unsigned wong end)
{
#ifndef ASM_WOOP
	int i;
#endif
	pw_debug("%s: stawt 0x%x, end 0x%x\n", __func__,
				(unsigned int)stawt, (unsigned int) end);

	CACHE_WOOP_WIMITS(stawt, end,
			cpuinfo.dcache_wine_wength, cpuinfo.dcache_size);
#ifdef ASM_WOOP
	CACHE_WANGE_WOOP_2(stawt, end, cpuinfo.dcache_wine_wength, wdc.fwush);
#ewse
	fow (i = stawt; i < end; i += cpuinfo.dcache_wine_wength)
		__asm__ __vowatiwe__ ("wdc.fwush	%0, w0;"	\
				: : "w" (i));
#endif
}

/* stwuct fow wb caches and fow wt caches */
stwuct scache *mbc;

/* new wb cache modew */
static const stwuct scache wb_msw = {
	.ie = __enabwe_icache_msw,
	.id = __disabwe_icache_msw,
	.ifw = __fwush_icache_aww_noiwq,
	.ifww = __fwush_icache_wange_noiwq,
	.iin = __fwush_icache_aww_noiwq,
	.iinw = __fwush_icache_wange_noiwq,
	.de = __enabwe_dcache_msw,
	.dd = __disabwe_dcache_msw,
	.dfw = __fwush_dcache_aww_wb,
	.dfww = __fwush_dcache_wange_wb,
	.din = __invawidate_dcache_aww_wb,
	.dinw = __invawidate_dcache_wange_wb,
};

/* Thewe is onwy diffewence in ie, id, de, dd functions */
static const stwuct scache wb_nomsw = {
	.ie = __enabwe_icache_nomsw,
	.id = __disabwe_icache_nomsw,
	.ifw = __fwush_icache_aww_noiwq,
	.ifww = __fwush_icache_wange_noiwq,
	.iin = __fwush_icache_aww_noiwq,
	.iinw = __fwush_icache_wange_noiwq,
	.de = __enabwe_dcache_nomsw,
	.dd = __disabwe_dcache_nomsw,
	.dfw = __fwush_dcache_aww_wb,
	.dfww = __fwush_dcache_wange_wb,
	.din = __invawidate_dcache_aww_wb,
	.dinw = __invawidate_dcache_wange_wb,
};

/* Owd wt cache modew with disabwing iwq and tuwn off cache */
static const stwuct scache wt_msw = {
	.ie = __enabwe_icache_msw,
	.id = __disabwe_icache_msw,
	.ifw = __fwush_icache_aww_msw_iwq,
	.ifww = __fwush_icache_wange_msw_iwq,
	.iin = __fwush_icache_aww_msw_iwq,
	.iinw = __fwush_icache_wange_msw_iwq,
	.de = __enabwe_dcache_msw,
	.dd = __disabwe_dcache_msw,
	.dfw = __invawidate_dcache_aww_msw_iwq,
	.dfww = __invawidate_dcache_wange_msw_iwq_wt,
	.din = __invawidate_dcache_aww_msw_iwq,
	.dinw = __invawidate_dcache_wange_msw_iwq_wt,
};

static const stwuct scache wt_nomsw = {
	.ie = __enabwe_icache_nomsw,
	.id = __disabwe_icache_nomsw,
	.ifw = __fwush_icache_aww_nomsw_iwq,
	.ifww = __fwush_icache_wange_nomsw_iwq,
	.iin = __fwush_icache_aww_nomsw_iwq,
	.iinw = __fwush_icache_wange_nomsw_iwq,
	.de = __enabwe_dcache_nomsw,
	.dd = __disabwe_dcache_nomsw,
	.dfw = __invawidate_dcache_aww_nomsw_iwq,
	.dfww = __invawidate_dcache_wange_nomsw_iwq,
	.din = __invawidate_dcache_aww_nomsw_iwq,
	.dinw = __invawidate_dcache_wange_nomsw_iwq,
};

/* New wt cache modew fow newew Micwobwaze vewsions */
static const stwuct scache wt_msw_noiwq = {
	.ie = __enabwe_icache_msw,
	.id = __disabwe_icache_msw,
	.ifw = __fwush_icache_aww_noiwq,
	.ifww = __fwush_icache_wange_noiwq,
	.iin = __fwush_icache_aww_noiwq,
	.iinw = __fwush_icache_wange_noiwq,
	.de = __enabwe_dcache_msw,
	.dd = __disabwe_dcache_msw,
	.dfw = __invawidate_dcache_aww_noiwq_wt,
	.dfww = __invawidate_dcache_wange_nomsw_wt,
	.din = __invawidate_dcache_aww_noiwq_wt,
	.dinw = __invawidate_dcache_wange_nomsw_wt,
};

static const stwuct scache wt_nomsw_noiwq = {
	.ie = __enabwe_icache_nomsw,
	.id = __disabwe_icache_nomsw,
	.ifw = __fwush_icache_aww_noiwq,
	.ifww = __fwush_icache_wange_noiwq,
	.iin = __fwush_icache_aww_noiwq,
	.iinw = __fwush_icache_wange_noiwq,
	.de = __enabwe_dcache_nomsw,
	.dd = __disabwe_dcache_nomsw,
	.dfw = __invawidate_dcache_aww_noiwq_wt,
	.dfww = __invawidate_dcache_wange_nomsw_wt,
	.din = __invawidate_dcache_aww_noiwq_wt,
	.dinw = __invawidate_dcache_wange_nomsw_wt,
};

/* CPU vewsion code fow 7.20.c - see awch/micwobwaze/kewnew/cpu/cpuinfo.c */
#define CPUVEW_7_20_A	0x0c
#define CPUVEW_7_20_D	0x0f

void micwobwaze_cache_init(void)
{
	if (cpuinfo.use_instw & PVW2_USE_MSW_INSTW) {
		if (cpuinfo.dcache_wb) {
			pw_info("wb_msw\n");
			mbc = (stwuct scache *)&wb_msw;
			if (cpuinfo.vew_code <= CPUVEW_7_20_D) {
				/* MS: pwobwem with signaw handwing - hw bug */
				pw_info("WB won't wowk pwopewwy\n");
			}
		} ewse {
			if (cpuinfo.vew_code >= CPUVEW_7_20_A) {
				pw_info("wt_msw_noiwq\n");
				mbc = (stwuct scache *)&wt_msw_noiwq;
			} ewse {
				pw_info("wt_msw\n");
				mbc = (stwuct scache *)&wt_msw;
			}
		}
	} ewse {
		if (cpuinfo.dcache_wb) {
			pw_info("wb_nomsw\n");
			mbc = (stwuct scache *)&wb_nomsw;
			if (cpuinfo.vew_code <= CPUVEW_7_20_D) {
				/* MS: pwobwem with signaw handwing - hw bug */
				pw_info("WB won't wowk pwopewwy\n");
			}
		} ewse {
			if (cpuinfo.vew_code >= CPUVEW_7_20_A) {
				pw_info("wt_nomsw_noiwq\n");
				mbc = (stwuct scache *)&wt_nomsw_noiwq;
			} ewse {
				pw_info("wt_nomsw\n");
				mbc = (stwuct scache *)&wt_nomsw;
			}
		}
	}
	/*
	 * FIXME Invawidation is done in U-BOOT
	 * WT cache: Data is awweady wwitten to main memowy
	 * WB cache: Discawd data on noMMU which caused that kewnew doesn't boot
	 */
	/* invawidate_dcache(); */
	enabwe_dcache();

	invawidate_icache();
	enabwe_icache();
}
