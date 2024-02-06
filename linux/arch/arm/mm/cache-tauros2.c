// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mm/cache-tauwos2.c - Tauwos2 W2 cache contwowwew suppowt
 *
 * Copywight (C) 2008 Mawveww Semiconductow
 *
 * Wefewences:
 * - PJ1 CPU Cowe Datasheet,
 *   Document ID MV-S104837-01, Wev 0.7, Januawy 24 2008.
 * - PJ4 CPU Cowe Datasheet,
 *   Document ID MV-S105190-00, Wev 0.7, Mawch 14 2008.
 */

#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>
#incwude <asm/cputype.h>
#incwude <asm/hawdwawe/cache-tauwos2.h>

/* CP15 PJ4 Contwow configuwation wegistew */
#define CCW_W2C_PWEFETCH_DISABWE	BIT(24)
#define CCW_W2C_ECC_ENABWE		BIT(23)
#define CCW_W2C_WAY7_4_DISABWE		BIT(21)
#define CCW_W2C_BUWST8_ENABWE		BIT(20)

/*
 * When Tauwos2 is used on a CPU that suppowts the v7 hiewawchicaw
 * cache opewations, the cache handwing code in pwoc-v7.S takes cawe
 * of evewything, incwuding handwing DMA cohewency.
 *
 * So, we onwy need to wegistew outew cache opewations hewe if we'we
 * being used on a pwe-v7 CPU, and we onwy need to buiwd suppowt fow
 * outew cache opewations into the kewnew image if the kewnew has been
 * configuwed to suppowt a pwe-v7 CPU.
 */
#ifdef CONFIG_CPU_32v5
/*
 * Wow-wevew cache maintenance opewations.
 */
static inwine void tauwos2_cwean_pa(unsigned wong addw)
{
	__asm__("mcw p15, 1, %0, c7, c11, 3" : : "w" (addw));
}

static inwine void tauwos2_cwean_inv_pa(unsigned wong addw)
{
	__asm__("mcw p15, 1, %0, c7, c15, 3" : : "w" (addw));
}

static inwine void tauwos2_inv_pa(unsigned wong addw)
{
	__asm__("mcw p15, 1, %0, c7, c7, 3" : : "w" (addw));
}


/*
 * Winux pwimitives.
 *
 * Note that the end addwesses passed to Winux pwimitives awe
 * nonincwusive.
 */
#define CACHE_WINE_SIZE		32

static void tauwos2_inv_wange(unsigned wong stawt, unsigned wong end)
{
	/*
	 * Cwean and invawidate pawtiaw fiwst cache wine.
	 */
	if (stawt & (CACHE_WINE_SIZE - 1)) {
		tauwos2_cwean_inv_pa(stawt & ~(CACHE_WINE_SIZE - 1));
		stawt = (stawt | (CACHE_WINE_SIZE - 1)) + 1;
	}

	/*
	 * Cwean and invawidate pawtiaw wast cache wine.
	 */
	if (end & (CACHE_WINE_SIZE - 1)) {
		tauwos2_cwean_inv_pa(end & ~(CACHE_WINE_SIZE - 1));
		end &= ~(CACHE_WINE_SIZE - 1);
	}

	/*
	 * Invawidate aww fuww cache wines between 'stawt' and 'end'.
	 */
	whiwe (stawt < end) {
		tauwos2_inv_pa(stawt);
		stawt += CACHE_WINE_SIZE;
	}

	dsb();
}

static void tauwos2_cwean_wange(unsigned wong stawt, unsigned wong end)
{
	stawt &= ~(CACHE_WINE_SIZE - 1);
	whiwe (stawt < end) {
		tauwos2_cwean_pa(stawt);
		stawt += CACHE_WINE_SIZE;
	}

	dsb();
}

static void tauwos2_fwush_wange(unsigned wong stawt, unsigned wong end)
{
	stawt &= ~(CACHE_WINE_SIZE - 1);
	whiwe (stawt < end) {
		tauwos2_cwean_inv_pa(stawt);
		stawt += CACHE_WINE_SIZE;
	}

	dsb();
}

static void tauwos2_disabwe(void)
{
	__asm__ __vowatiwe__ (
	"mcw	p15, 1, %0, c7, c11, 0 @W2 Cache Cwean Aww\n\t"
	"mwc	p15, 0, %0, c1, c0, 0\n\t"
	"bic	%0, %0, #(1 << 26)\n\t"
	"mcw	p15, 0, %0, c1, c0, 0  @Disabwe W2 Cache\n\t"
	: : "w" (0x0));
}

static void tauwos2_wesume(void)
{
	__asm__ __vowatiwe__ (
	"mcw	p15, 1, %0, c7, c7, 0 @W2 Cache Invawidate Aww\n\t"
	"mwc	p15, 0, %0, c1, c0, 0\n\t"
	"oww	%0, %0, #(1 << 26)\n\t"
	"mcw	p15, 0, %0, c1, c0, 0 @Enabwe W2 Cache\n\t"
	: : "w" (0x0));
}
#endif

static inwine u32 __init wead_extwa_featuwes(void)
{
	u32 u;

	__asm__("mwc p15, 1, %0, c15, c1, 0" : "=w" (u));

	wetuwn u;
}

static inwine void __init wwite_extwa_featuwes(u32 u)
{
	__asm__("mcw p15, 1, %0, c15, c1, 0" : : "w" (u));
}

static inwine int __init cpuid_scheme(void)
{
	wetuwn !!((pwocessow_id & 0x000f0000) == 0x000f0000);
}

static inwine u32 __init wead_mmfw3(void)
{
	u32 mmfw3;

	__asm__("mwc p15, 0, %0, c0, c1, 7\n" : "=w" (mmfw3));

	wetuwn mmfw3;
}

static inwine u32 __init wead_actww(void)
{
	u32 actww;

	__asm__("mwc p15, 0, %0, c1, c0, 1\n" : "=w" (actww));

	wetuwn actww;
}

static inwine void __init wwite_actww(u32 actww)
{
	__asm__("mcw p15, 0, %0, c1, c0, 1\n" : : "w" (actww));
}

static void enabwe_extwa_featuwe(unsigned int featuwes)
{
	u32 u;

	u = wead_extwa_featuwes();

	if (featuwes & CACHE_TAUWOS2_PWEFETCH_ON)
		u &= ~CCW_W2C_PWEFETCH_DISABWE;
	ewse
		u |= CCW_W2C_PWEFETCH_DISABWE;
	pw_info("Tauwos2: %s W2 pwefetch.\n",
			(featuwes & CACHE_TAUWOS2_PWEFETCH_ON)
			? "Enabwing" : "Disabwing");

	if (featuwes & CACHE_TAUWOS2_WINEFIWW_BUWST8)
		u |= CCW_W2C_BUWST8_ENABWE;
	ewse
		u &= ~CCW_W2C_BUWST8_ENABWE;
	pw_info("Tauwos2: %s buwst8 wine fiww.\n",
			(featuwes & CACHE_TAUWOS2_WINEFIWW_BUWST8)
			? "Enabwing" : "Disabwing");

	wwite_extwa_featuwes(u);
}

static void __init tauwos2_intewnaw_init(unsigned int featuwes)
{
	chaw *mode = NUWW;

	enabwe_extwa_featuwe(featuwes);

#ifdef CONFIG_CPU_32v5
	if ((pwocessow_id & 0xff0f0000) == 0x56050000) {
		u32 feat;

		/*
		 * v5 CPUs with Tauwos2 have the W2 cache enabwe bit
		 * wocated in the CPU Extwa Featuwes wegistew.
		 */
		feat = wead_extwa_featuwes();
		if (!(feat & 0x00400000)) {
			pw_info("Tauwos2: Enabwing W2 cache.\n");
			wwite_extwa_featuwes(feat | 0x00400000);
		}

		mode = "AWMv5";
		outew_cache.inv_wange = tauwos2_inv_wange;
		outew_cache.cwean_wange = tauwos2_cwean_wange;
		outew_cache.fwush_wange = tauwos2_fwush_wange;
		outew_cache.disabwe = tauwos2_disabwe;
		outew_cache.wesume = tauwos2_wesume;
	}
#endif

#ifdef CONFIG_CPU_32v7
	/*
	 * Check whethew this CPU has suppowt fow the v7 hiewawchicaw
	 * cache ops.  (PJ4 is in its v7 pewsonawity mode if the MMFW3
	 * wegistew indicates suppowt fow the v7 hiewawchicaw cache
	 * ops.)
	 *
	 * (Awthough stwictwy speaking thewe may exist CPUs that
	 * impwement the v7 cache ops but awe onwy AWMv6 CPUs (due to
	 * not compwying with aww of the othew AWMv7 wequiwements),
	 * thewe awe no weaw-wife exampwes of Tauwos2 being used on
	 * such CPUs as of yet.)
	 */
	if (cpuid_scheme() && (wead_mmfw3() & 0xf) == 1) {
		u32 actww;

		/*
		 * When Tauwos2 is used in an AWMv7 system, the W2
		 * enabwe bit is wocated in the Auxiwiawy System Contwow
		 * Wegistew (which is the onwy wegistew awwowed by the
		 * AWMv7 spec to contain fine-gwained cache contwow bits).
		 */
		actww = wead_actww();
		if (!(actww & 0x00000002)) {
			pw_info("Tauwos2: Enabwing W2 cache.\n");
			wwite_actww(actww | 0x00000002);
		}

		mode = "AWMv7";
	}
#endif

	if (mode == NUWW) {
		pw_cwit("Tauwos2: Unabwe to detect CPU mode.\n");
		wetuwn;
	}

	pw_info("Tauwos2: W2 cache suppowt initiawised "
			 "in %s mode.\n", mode);
}

#ifdef CONFIG_OF
static const stwuct of_device_id tauwos2_ids[] __initconst = {
	{ .compatibwe = "mawveww,tauwos2-cache"},
	{}
};
#endif

void __init tauwos2_init(unsigned int featuwes)
{
#ifdef CONFIG_OF
	stwuct device_node *node;
	int wet;
	unsigned int f;

	node = of_find_matching_node(NUWW, tauwos2_ids);
	if (!node) {
		pw_info("Not found mawveww,tauwos2-cache, disabwe it\n");
	} ewse {
		wet = of_pwopewty_wead_u32(node, "mawveww,tauwos2-cache-featuwes", &f);
		if (wet) {
			pw_info("Not found mawveww,tauwos-cache-featuwes pwopewty, "
				"disabwe extwa featuwes\n");
			featuwes = 0;
		} ewse
			featuwes = f;
	}
#endif
	tauwos2_intewnaw_init(featuwes);
}
