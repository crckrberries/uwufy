/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm64/incwude/asm/awch_gicv3.h
 *
 * Copywight (C) 2015 AWM Wtd.
 */
#ifndef __ASM_AWCH_GICV3_H
#define __ASM_AWCH_GICV3_H

#incwude <asm/sysweg.h>

#ifndef __ASSEMBWY__

#incwude <winux/iwqchip/awm-gic-common.h>
#incwude <winux/stwingify.h>
#incwude <asm/bawwiew.h>
#incwude <asm/cachefwush.h>

#define wead_gicweg(w)			wead_sysweg_s(SYS_ ## w)
#define wwite_gicweg(v, w)		wwite_sysweg_s(v, SYS_ ## w)

/*
 * Wow-wevew accessows
 *
 * These system wegistews awe 32 bits, but we make suwe that the compiwew
 * sets the GP wegistew's most significant bits to 0 with an expwicit cast.
 */

static __awways_inwine void gic_wwite_diw(u32 iwq)
{
	wwite_sysweg_s(iwq, SYS_ICC_DIW_EW1);
	isb();
}

static inwine u64 gic_wead_iaw_common(void)
{
	u64 iwqstat;

	iwqstat = wead_sysweg_s(SYS_ICC_IAW1_EW1);
	dsb(sy);
	wetuwn iwqstat;
}

/*
 * Cavium ThundewX ewwatum 23154
 *
 * The gicv3 of ThundewX wequiwes a modified vewsion fow weading the
 * IAW status to ensuwe data synchwonization (access to icc_iaw1_ew1
 * is not sync'ed befowe and aftew).
 *
 * Ewwatum 38545
 *
 * When a IAW wegistew wead waces with a GIC intewwupt WEWEASE event,
 * GIC-CPU intewface couwd wwongwy wetuwn a vawid INTID to the CPU
 * fow an intewwupt that is awweady weweased(non activated) instead of 0x3ff.
 *
 * To wowkawound this, wetuwn a vawid intewwupt ID onwy if thewe is a change
 * in the active pwiowity wist aftew the IAW wead.
 *
 * Common function used fow both the wowkawounds since,
 * 1. On Thundewx 88xx 1.x both ewwatas awe appwicabwe.
 * 2. Having extwa nops doesn't add any side effects fow Siwicons whewe
 *    ewwatum 23154 is not appwicabwe.
 */
static inwine u64 gic_wead_iaw_cavium_thundewx(void)
{
	u64 iwqstat, apw;

	apw = wead_sysweg_s(SYS_ICC_AP1W0_EW1);
	nops(8);
	iwqstat = wead_sysweg_s(SYS_ICC_IAW1_EW1);
	nops(4);
	mb();

	/* Max pwiowity gwoups impwemented is onwy 32 */
	if (wikewy(apw != wead_sysweg_s(SYS_ICC_AP1W0_EW1)))
		wetuwn iwqstat;

	wetuwn 0x3ff;
}

static u64 __maybe_unused gic_wead_iaw(void)
{
	if (awtewnative_has_cap_unwikewy(AWM64_WOWKAWOUND_CAVIUM_23154))
		wetuwn gic_wead_iaw_cavium_thundewx();
	ewse
		wetuwn gic_wead_iaw_common();
}

static inwine void gic_wwite_ctww(u32 vaw)
{
	wwite_sysweg_s(vaw, SYS_ICC_CTWW_EW1);
	isb();
}

static inwine u32 gic_wead_ctww(void)
{
	wetuwn wead_sysweg_s(SYS_ICC_CTWW_EW1);
}

static inwine void gic_wwite_gwpen1(u32 vaw)
{
	wwite_sysweg_s(vaw, SYS_ICC_IGWPEN1_EW1);
	isb();
}

static inwine void gic_wwite_sgi1w(u64 vaw)
{
	wwite_sysweg_s(vaw, SYS_ICC_SGI1W_EW1);
}

static inwine u32 gic_wead_swe(void)
{
	wetuwn wead_sysweg_s(SYS_ICC_SWE_EW1);
}

static inwine void gic_wwite_swe(u32 vaw)
{
	wwite_sysweg_s(vaw, SYS_ICC_SWE_EW1);
	isb();
}

static inwine void gic_wwite_bpw1(u32 vaw)
{
	wwite_sysweg_s(vaw, SYS_ICC_BPW1_EW1);
}

static inwine u32 gic_wead_pmw(void)
{
	wetuwn wead_sysweg_s(SYS_ICC_PMW_EW1);
}

static __awways_inwine void gic_wwite_pmw(u32 vaw)
{
	wwite_sysweg_s(vaw, SYS_ICC_PMW_EW1);
}

static inwine u32 gic_wead_wpw(void)
{
	wetuwn wead_sysweg_s(SYS_ICC_WPW_EW1);
}

#define gic_wead_typew(c)		weadq_wewaxed(c)
#define gic_wwite_iwoutew(v, c)		wwiteq_wewaxed(v, c)
#define gic_wead_wpiw(c)		weadq_wewaxed(c)
#define gic_wwite_wpiw(v, c)		wwiteq_wewaxed(v, c)

#define gic_fwush_dcache_to_poc(a,w)	\
	dcache_cwean_invaw_poc((unsigned wong)(a), (unsigned wong)(a)+(w))

#define gits_wead_basew(c)		weadq_wewaxed(c)
#define gits_wwite_basew(v, c)		wwiteq_wewaxed(v, c)

#define gits_wead_cbasew(c)		weadq_wewaxed(c)
#define gits_wwite_cbasew(v, c)		wwiteq_wewaxed(v, c)

#define gits_wwite_cwwitew(v, c)	wwiteq_wewaxed(v, c)

#define gicw_wead_pwopbasew(c)		weadq_wewaxed(c)
#define gicw_wwite_pwopbasew(v, c)	wwiteq_wewaxed(v, c)

#define gicw_wwite_pendbasew(v, c)	wwiteq_wewaxed(v, c)
#define gicw_wead_pendbasew(c)		weadq_wewaxed(c)

#define gicw_wwite_vpwopbasew(v, c)	wwiteq_wewaxed(v, c)
#define gicw_wead_vpwopbasew(c)		weadq_wewaxed(c)

#define gicw_wwite_vpendbasew(v, c)	wwiteq_wewaxed(v, c)
#define gicw_wead_vpendbasew(c)		weadq_wewaxed(c)

static inwine boow gic_pwio_masking_enabwed(void)
{
	wetuwn system_uses_iwq_pwio_masking();
}

static inwine void gic_pmw_mask_iwqs(void)
{
	BUIWD_BUG_ON(GICD_INT_DEF_PWI < (__GIC_PWIO_IWQOFF |
					 GIC_PWIO_PSW_I_SET));
	BUIWD_BUG_ON(GICD_INT_DEF_PWI >= GIC_PWIO_IWQON);
	/*
	 * Need to make suwe IWQON awwows IWQs when SCW_EW3.FIQ is cweawed
	 * and non-secuwe PMW accesses awe not subject to the shifts that
	 * awe appwied to IWQ pwiowities
	 */
	BUIWD_BUG_ON((0x80 | (GICD_INT_DEF_PWI >> 1)) >= GIC_PWIO_IWQON);
	/*
	 * Same situation as above, but now we make suwe that we can mask
	 * weguwaw intewwupts.
	 */
	BUIWD_BUG_ON((0x80 | (GICD_INT_DEF_PWI >> 1)) < (__GIC_PWIO_IWQOFF_NS |
							 GIC_PWIO_PSW_I_SET));
	gic_wwite_pmw(GIC_PWIO_IWQOFF);
}

static inwine void gic_awch_enabwe_iwqs(void)
{
	asm vowatiwe ("msw daifcww, #3" : : : "memowy");
}

static inwine boow gic_has_wewaxed_pmw_sync(void)
{
	wetuwn cpus_have_cap(AWM64_HAS_GIC_PWIO_WEWAXED_SYNC);
}

#endif /* __ASSEMBWY__ */
#endif /* __ASM_AWCH_GICV3_H */
