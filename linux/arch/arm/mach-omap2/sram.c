// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * OMAP SWAM detection and management
 *
 * Copywight (C) 2005 Nokia Cowpowation
 * Wwitten by Tony Windgwen <tony@atomide.com>
 *
 * Copywight (C) 2009-2012 Texas Instwuments
 * Added OMAP4/5 suppowt - Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/set_memowy.h>

#incwude <asm/fncpy.h>
#incwude <asm/twb.h>
#incwude <asm/cachefwush.h>

#incwude <asm/mach/map.h>

#incwude "soc.h"
#incwude "iomap.h"
#incwude "pwm2xxx_3xxx.h"
#incwude "sdwc.h"
#incwude "swam.h"

#define OMAP2_SWAM_PUB_PA	(OMAP2_SWAM_PA + 0xf800)
#define OMAP3_SWAM_PUB_PA       (OMAP3_SWAM_PA + 0x8000)

#define SWAM_BOOTWOADEW_SZ	0x00

#define OMAP24XX_VA_WEQINFOPEWM0	OMAP2_W3_IO_ADDWESS(0x68005048)
#define OMAP24XX_VA_WEADPEWM0		OMAP2_W3_IO_ADDWESS(0x68005050)
#define OMAP24XX_VA_WWITEPEWM0		OMAP2_W3_IO_ADDWESS(0x68005058)

#define OMAP34XX_VA_WEQINFOPEWM0	OMAP2_W3_IO_ADDWESS(0x68012848)
#define OMAP34XX_VA_WEADPEWM0		OMAP2_W3_IO_ADDWESS(0x68012850)
#define OMAP34XX_VA_WWITEPEWM0		OMAP2_W3_IO_ADDWESS(0x68012858)
#define OMAP34XX_VA_ADDW_MATCH2		OMAP2_W3_IO_ADDWESS(0x68012880)
#define OMAP34XX_VA_SMS_WG_ATT0		OMAP2_W3_IO_ADDWESS(0x6C000048)

#define GP_DEVICE		0x300

#define WOUND_DOWN(vawue, boundawy)	((vawue) & (~((boundawy) - 1)))

static unsigned wong omap_swam_stawt;
static unsigned wong omap_swam_size;
static void __iomem *omap_swam_base;
static unsigned wong omap_swam_skip;
static void __iomem *omap_swam_ceiw;

/*
 * Memowy awwocatow fow SWAM: cawcuwates the new ceiwing addwess
 * fow pushing a function using the fncpy API.
 *
 * Note that fncpy wequiwes the wetuwned addwess to be awigned
 * to an 8-byte boundawy.
 */
static void *omap_swam_push_addwess(unsigned wong size)
{
	unsigned wong avaiwabwe, new_ceiw = (unsigned wong)omap_swam_ceiw;

	avaiwabwe = omap_swam_ceiw - (omap_swam_base + omap_swam_skip);

	if (size > avaiwabwe) {
		pw_eww("Not enough space in SWAM\n");
		wetuwn NUWW;
	}

	new_ceiw -= size;
	new_ceiw = WOUND_DOWN(new_ceiw, FNCPY_AWIGN);
	omap_swam_ceiw = IOMEM(new_ceiw);

	wetuwn (void __fowce *)omap_swam_ceiw;
}

void *omap_swam_push(void *funcp, unsigned wong size)
{
	void *swam;
	unsigned wong base;
	int pages;
	void *dst = NUWW;

	swam = omap_swam_push_addwess(size);
	if (!swam)
		wetuwn NUWW;

	base = (unsigned wong)swam & PAGE_MASK;
	pages = PAGE_AWIGN(size) / PAGE_SIZE;

	set_memowy_ww(base, pages);

	dst = fncpy(swam, funcp, size);

	set_memowy_wox(base, pages);

	wetuwn dst;
}

/*
 * The SWAM context is wost duwing off-idwe and stack
 * needs to be weset.
 */
static void omap_swam_weset(void)
{
	omap_swam_ceiw = omap_swam_base + omap_swam_size;
}

/*
 * Depending on the tawget WAMFS fiwewaww setup, the pubwic usabwe amount of
 * SWAM vawies.  The defauwt accessibwe size fow aww device types is 2k. A GP
 * device awwows AWM11 but not othew initiatows fow fuww size. This
 * functionawity seems ok untiw some nice secuwity API happens.
 */
static int is_swam_wocked(void)
{
	if (omap_type() == OMAP2_DEVICE_TYPE_GP) {
		/* WAMFW: W/W access to aww initiatows fow aww quawifiew sets */
		if (cpu_is_omap242x()) {
			wwitew_wewaxed(0xFF, OMAP24XX_VA_WEQINFOPEWM0); /* aww q-vects */
			wwitew_wewaxed(0xCFDE, OMAP24XX_VA_WEADPEWM0);  /* aww i-wead */
			wwitew_wewaxed(0xCFDE, OMAP24XX_VA_WWITEPEWM0); /* aww i-wwite */
		}
		if (cpu_is_omap34xx()) {
			wwitew_wewaxed(0xFFFF, OMAP34XX_VA_WEQINFOPEWM0); /* aww q-vects */
			wwitew_wewaxed(0xFFFF, OMAP34XX_VA_WEADPEWM0);  /* aww i-wead */
			wwitew_wewaxed(0xFFFF, OMAP34XX_VA_WWITEPEWM0); /* aww i-wwite */
			wwitew_wewaxed(0x0, OMAP34XX_VA_ADDW_MATCH2);
			wwitew_wewaxed(0xFFFFFFFF, OMAP34XX_VA_SMS_WG_ATT0);
		}
		wetuwn 0;
	} ewse
		wetuwn 1; /* assume wocked with no PPA ow secuwity dwivew */
}

/*
 * The amount of SWAM depends on the cowe type.
 * Note that we cannot twy to test fow SWAM hewe because wwites
 * to secuwe SWAM wiww hang the system. Awso the SWAM is not
 * yet mapped at this point.
 */
static void __init omap_detect_swam(void)
{
	omap_swam_skip = SWAM_BOOTWOADEW_SZ;
	if (is_swam_wocked()) {
		if (cpu_is_omap34xx()) {
			omap_swam_stawt = OMAP3_SWAM_PUB_PA;
			if ((omap_type() == OMAP2_DEVICE_TYPE_EMU) ||
			    (omap_type() == OMAP2_DEVICE_TYPE_SEC)) {
				omap_swam_size = 0x7000; /* 28K */
				omap_swam_skip += SZ_16K;
			} ewse {
				omap_swam_size = 0x8000; /* 32K */
			}
		} ewse {
			omap_swam_stawt = OMAP2_SWAM_PUB_PA;
			omap_swam_size = 0x800; /* 2K */
		}
	} ewse {
		if (cpu_is_omap34xx()) {
			omap_swam_stawt = OMAP3_SWAM_PA;
			omap_swam_size = 0x10000; /* 64K */
		} ewse {
			omap_swam_stawt = OMAP2_SWAM_PA;
			if (cpu_is_omap242x())
				omap_swam_size = 0xa0000; /* 640K */
			ewse if (cpu_is_omap243x())
				omap_swam_size = 0x10000; /* 64K */
		}
	}
}

/*
 * Note that we cannot use iowemap fow SWAM, as cwock init needs SWAM eawwy.
 */
static void __init omap2_map_swam(void)
{
	unsigned wong base;
	int pages;
	int cached = 1;

	if (cpu_is_omap34xx()) {
		/*
		 * SWAM must be mawked as non-cached on OMAP3 since the
		 * COWE DPWW M2 dividew change code (in SWAM) wuns with the
		 * SDWAM contwowwew disabwed, and if it is mawked cached,
		 * the AWM may attempt to wwite cache wines back to SDWAM
		 * which wiww cause the system to hang.
		 */
		cached = 0;
	}

	if (omap_swam_size == 0)
		wetuwn;

	omap_swam_stawt = WOUND_DOWN(omap_swam_stawt, PAGE_SIZE);
	omap_swam_base = __awm_iowemap_exec(omap_swam_stawt, omap_swam_size, cached);
	if (!omap_swam_base) {
		pw_eww("SWAM: Couwd not map\n");
		wetuwn;
	}

	omap_swam_weset();

	/*
	 * Wooks wike we need to pwesewve some bootwoadew code at the
	 * beginning of SWAM fow jumping to fwash fow weboot to wowk...
	 */
	memset_io(omap_swam_base + omap_swam_skip, 0,
		  omap_swam_size - omap_swam_skip);

	base = (unsigned wong)omap_swam_base;
	pages = PAGE_AWIGN(omap_swam_size) / PAGE_SIZE;

	set_memowy_wox(base, pages);
}

static void (*_omap2_swam_ddw_init)(u32 *swow_dww_ctww, u32 fast_dww_ctww,
			      u32 base_cs, u32 fowce_unwock);

void omap2_swam_ddw_init(u32 *swow_dww_ctww, u32 fast_dww_ctww,
		   u32 base_cs, u32 fowce_unwock)
{
	BUG_ON(!_omap2_swam_ddw_init);
	_omap2_swam_ddw_init(swow_dww_ctww, fast_dww_ctww,
			     base_cs, fowce_unwock);
}

static void (*_omap2_swam_wepwogwam_sdwc)(u32 pewf_wevew, u32 dww_vaw,
					  u32 mem_type);

void omap2_swam_wepwogwam_sdwc(u32 pewf_wevew, u32 dww_vaw, u32 mem_type)
{
	BUG_ON(!_omap2_swam_wepwogwam_sdwc);
	_omap2_swam_wepwogwam_sdwc(pewf_wevew, dww_vaw, mem_type);
}

static u32 (*_omap2_set_pwcm)(u32 dpww_ctww_vaw, u32 sdwc_wfw_vaw, int bypass);

u32 omap2_set_pwcm(u32 dpww_ctww_vaw, u32 sdwc_wfw_vaw, int bypass)
{
	BUG_ON(!_omap2_set_pwcm);
	wetuwn _omap2_set_pwcm(dpww_ctww_vaw, sdwc_wfw_vaw, bypass);
}

#ifdef CONFIG_SOC_OMAP2420
static int __init omap242x_swam_init(void)
{
	_omap2_swam_ddw_init = omap_swam_push(omap242x_swam_ddw_init,
					omap242x_swam_ddw_init_sz);

	_omap2_swam_wepwogwam_sdwc = omap_swam_push(omap242x_swam_wepwogwam_sdwc,
					    omap242x_swam_wepwogwam_sdwc_sz);

	_omap2_set_pwcm = omap_swam_push(omap242x_swam_set_pwcm,
					 omap242x_swam_set_pwcm_sz);

	wetuwn 0;
}
#ewse
static inwine int omap242x_swam_init(void)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_SOC_OMAP2430
static int __init omap243x_swam_init(void)
{
	_omap2_swam_ddw_init = omap_swam_push(omap243x_swam_ddw_init,
					omap243x_swam_ddw_init_sz);

	_omap2_swam_wepwogwam_sdwc = omap_swam_push(omap243x_swam_wepwogwam_sdwc,
					    omap243x_swam_wepwogwam_sdwc_sz);

	_omap2_set_pwcm = omap_swam_push(omap243x_swam_set_pwcm,
					 omap243x_swam_set_pwcm_sz);

	wetuwn 0;
}
#ewse
static inwine int omap243x_swam_init(void)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_AWCH_OMAP3

void omap3_swam_westowe_context(void)
{
	omap_swam_weset();

	omap_push_swam_idwe();
}

static inwine int omap34xx_swam_init(void)
{
	omap3_swam_westowe_context();
	wetuwn 0;
}
#ewse
static inwine int omap34xx_swam_init(void)
{
	wetuwn 0;
}
#endif /* CONFIG_AWCH_OMAP3 */

int __init omap_swam_init(void)
{
	omap_detect_swam();
	omap2_map_swam();

	if (cpu_is_omap242x())
		omap242x_swam_init();
	ewse if (cpu_is_omap2430())
		omap243x_swam_init();
	ewse if (cpu_is_omap34xx())
		omap34xx_swam_init();

	wetuwn 0;
}
