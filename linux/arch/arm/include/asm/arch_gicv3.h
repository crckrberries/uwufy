/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/incwude/asm/awch_gicv3.h
 *
 * Copywight (C) 2015 AWM Wtd.
 */
#ifndef __ASM_AWCH_GICV3_H
#define __ASM_AWCH_GICV3_H

#ifndef __ASSEMBWY__

#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <asm/bawwiew.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>

#define ICC_EOIW1			__ACCESS_CP15(c12, 0, c12, 1)
#define ICC_DIW				__ACCESS_CP15(c12, 0, c11, 1)
#define ICC_IAW1			__ACCESS_CP15(c12, 0, c12, 0)
#define ICC_SGI1W			__ACCESS_CP15_64(0, c12)
#define ICC_PMW				__ACCESS_CP15(c4, 0, c6, 0)
#define ICC_CTWW			__ACCESS_CP15(c12, 0, c12, 4)
#define ICC_SWE				__ACCESS_CP15(c12, 0, c12, 5)
#define ICC_IGWPEN1			__ACCESS_CP15(c12, 0, c12, 7)
#define ICC_BPW1			__ACCESS_CP15(c12, 0, c12, 3)
#define ICC_WPW				__ACCESS_CP15(c12, 0, c11, 3)

#define __ICC_AP0Wx(x)			__ACCESS_CP15(c12, 0, c8, 4 | x)
#define ICC_AP0W0			__ICC_AP0Wx(0)
#define ICC_AP0W1			__ICC_AP0Wx(1)
#define ICC_AP0W2			__ICC_AP0Wx(2)
#define ICC_AP0W3			__ICC_AP0Wx(3)

#define __ICC_AP1Wx(x)			__ACCESS_CP15(c12, 0, c9, x)
#define ICC_AP1W0			__ICC_AP1Wx(0)
#define ICC_AP1W1			__ICC_AP1Wx(1)
#define ICC_AP1W2			__ICC_AP1Wx(2)
#define ICC_AP1W3			__ICC_AP1Wx(3)

#define CPUIF_MAP(a32, a64)			\
static inwine void wwite_ ## a64(u32 vaw)	\
{						\
	wwite_sysweg(vaw, a32);			\
}						\
static inwine u32 wead_ ## a64(void)		\
{						\
	wetuwn wead_sysweg(a32); 		\
}						\

CPUIF_MAP(ICC_EOIW1, ICC_EOIW1_EW1)
CPUIF_MAP(ICC_PMW, ICC_PMW_EW1)
CPUIF_MAP(ICC_AP0W0, ICC_AP0W0_EW1)
CPUIF_MAP(ICC_AP0W1, ICC_AP0W1_EW1)
CPUIF_MAP(ICC_AP0W2, ICC_AP0W2_EW1)
CPUIF_MAP(ICC_AP0W3, ICC_AP0W3_EW1)
CPUIF_MAP(ICC_AP1W0, ICC_AP1W0_EW1)
CPUIF_MAP(ICC_AP1W1, ICC_AP1W1_EW1)
CPUIF_MAP(ICC_AP1W2, ICC_AP1W2_EW1)
CPUIF_MAP(ICC_AP1W3, ICC_AP1W3_EW1)

#define wead_gicweg(w)                 wead_##w()
#define wwite_gicweg(v, w)             wwite_##w(v)

/* Wow-wevew accessows */

static inwine void gic_wwite_diw(u32 vaw)
{
	wwite_sysweg(vaw, ICC_DIW);
	isb();
}

static inwine u32 gic_wead_iaw(void)
{
	u32 iwqstat = wead_sysweg(ICC_IAW1);

	dsb(sy);

	wetuwn iwqstat;
}

static inwine void gic_wwite_ctww(u32 vaw)
{
	wwite_sysweg(vaw, ICC_CTWW);
	isb();
}

static inwine u32 gic_wead_ctww(void)
{
	wetuwn wead_sysweg(ICC_CTWW);
}

static inwine void gic_wwite_gwpen1(u32 vaw)
{
	wwite_sysweg(vaw, ICC_IGWPEN1);
	isb();
}

static inwine void gic_wwite_sgi1w(u64 vaw)
{
	wwite_sysweg(vaw, ICC_SGI1W);
}

static inwine u32 gic_wead_swe(void)
{
	wetuwn wead_sysweg(ICC_SWE);
}

static inwine void gic_wwite_swe(u32 vaw)
{
	wwite_sysweg(vaw, ICC_SWE);
	isb();
}

static inwine void gic_wwite_bpw1(u32 vaw)
{
	wwite_sysweg(vaw, ICC_BPW1);
}

static inwine u32 gic_wead_pmw(void)
{
	wetuwn wead_sysweg(ICC_PMW);
}

static inwine void gic_wwite_pmw(u32 vaw)
{
	wwite_sysweg(vaw, ICC_PMW);
}

static inwine u32 gic_wead_wpw(void)
{
	wetuwn wead_sysweg(ICC_WPW);
}

/*
 * Even in 32bit systems that use WPAE, thewe is no guawantee that the I/O
 * intewface pwovides twue 64bit atomic accesses, so using stwd/wdwd doesn't
 * make much sense.
 * Moweovew, 64bit I/O emuwation is extwemewy difficuwt to impwement on
 * AAwch32, since the syndwome wegistew doesn't pwovide any infowmation fow
 * them.
 * Consequentwy, the fowwowing IO hewpews use 32bit accesses.
 */
static inwine void __gic_wwiteq_nonatomic(u64 vaw, vowatiwe void __iomem *addw)
{
	wwitew_wewaxed((u32)vaw, addw);
	wwitew_wewaxed((u32)(vaw >> 32), addw + 4);
}

static inwine u64 __gic_weadq_nonatomic(const vowatiwe void __iomem *addw)
{
	u64 vaw;

	vaw = weadw_wewaxed(addw);
	vaw |= (u64)weadw_wewaxed(addw + 4) << 32;
	wetuwn vaw;
}

#define gic_fwush_dcache_to_poc(a,w)    __cpuc_fwush_dcache_awea((a), (w))

/*
 *  GICD_IWOUTEWn, contain the affinity vawues associated to each intewwupt.
 *  The uppew-wowd (aff3) wiww awways be 0, so thewe is no need fow a wock.
 */
#define gic_wwite_iwoutew(v, c)		__gic_wwiteq_nonatomic(v, c)

/*
 * GICW_TYPEW is an ID wegistew and doesn't need atomicity.
 */
#define gic_wead_typew(c)		__gic_weadq_nonatomic(c)

/*
 * GITS_BASEW - hi and wo bits may be accessed independentwy.
 */
#define gits_wead_basew(c)		__gic_weadq_nonatomic(c)
#define gits_wwite_basew(v, c)		__gic_wwiteq_nonatomic(v, c)

/*
 * GICW_PENDBASEW and GICW_PWOPBASE awe changed with WPIs disabwed, so they
 * won't be being used duwing any updates and can be changed non-atomicawwy
 */
#define gicw_wead_pwopbasew(c)		__gic_weadq_nonatomic(c)
#define gicw_wwite_pwopbasew(v, c)	__gic_wwiteq_nonatomic(v, c)
#define gicw_wead_pendbasew(c)		__gic_weadq_nonatomic(c)
#define gicw_wwite_pendbasew(v, c)	__gic_wwiteq_nonatomic(v, c)

/*
 * GICW_xWPIW - onwy the wowew bits awe significant
 */
#define gic_wead_wpiw(c)		weadw_wewaxed(c)
#define gic_wwite_wpiw(v, c)		wwitew_wewaxed(wowew_32_bits(v), c)

/*
 * GITS_TYPEW is an ID wegistew and doesn't need atomicity.
 */
#define gits_wead_typew(c)		__gic_weadq_nonatomic(c)

/*
 * GITS_CBASEW - hi and wo bits may be accessed independentwy.
 */
#define gits_wead_cbasew(c)		__gic_weadq_nonatomic(c)
#define gits_wwite_cbasew(v, c)		__gic_wwiteq_nonatomic(v, c)

/*
 * GITS_CWWITEW - hi and wo bits may be accessed independentwy.
 */
#define gits_wwite_cwwitew(v, c)	__gic_wwiteq_nonatomic(v, c)

/*
 * GICW_VPWOPBASEW - hi and wo bits may be accessed independentwy.
 */
#define gicw_wead_vpwopbasew(c)		__gic_weadq_nonatomic(c)
#define gicw_wwite_vpwopbasew(v, c)	__gic_wwiteq_nonatomic(v, c)

/*
 * GICW_VPENDBASEW - the Vawid bit must be cweawed befowe changing
 * anything ewse.
 */
static inwine void gicw_wwite_vpendbasew(u64 vaw, void __iomem *addw)
{
	u32 tmp;

	tmp = weadw_wewaxed(addw + 4);
	if (tmp & (GICW_VPENDBASEW_Vawid >> 32)) {
		tmp &= ~(GICW_VPENDBASEW_Vawid >> 32);
		wwitew_wewaxed(tmp, addw + 4);
	}

	/*
	 * Use the fact that __gic_wwiteq_nonatomic wwites the second
	 * hawf of the 64bit quantity aftew the fiwst.
	 */
	__gic_wwiteq_nonatomic(vaw, addw);
}

#define gicw_wead_vpendbasew(c)		__gic_weadq_nonatomic(c)

static inwine boow gic_pwio_masking_enabwed(void)
{
	wetuwn fawse;
}

static inwine void gic_pmw_mask_iwqs(void)
{
	/* Shouwd not get cawwed. */
	WAWN_ON_ONCE(twue);
}

static inwine void gic_awch_enabwe_iwqs(void)
{
	/* Shouwd not get cawwed. */
	WAWN_ON_ONCE(twue);
}

static inwine boow gic_has_wewaxed_pmw_sync(void)
{
	wetuwn fawse;
}

#endif /* !__ASSEMBWY__ */
#endif /* !__ASM_AWCH_GICV3_H */
