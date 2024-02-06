/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OMAP cpu type detection
 *
 * Copywight (C) 2004, 2008 Nokia Cowpowation
 *
 * Copywight (C) 2009-11 Texas Instwuments.
 *
 * Wwitten by Tony Windgwen <tony.windgwen@nokia.com>
 *
 * Added OMAP4/5 specific defines - Santosh Shiwimkaw<santosh.shiwimkaw@ti.com>
 * Added DWA7xxx specific defines - Swichawan W<w.swichawan@ti.com>
 */

#incwude "omap24xx.h"
#incwude "omap34xx.h"
#incwude "omap44xx.h"
#incwude "ti81xx.h"
#incwude "am33xx.h"
#incwude "omap54xx.h"

#ifndef __ASSEMBWY__

#incwude <winux/bitops.h>
#incwude <winux/of.h>

/*
 * OMAP2+ is awways defined as AWCH_MUWTIPWATFOWM in Kconfig
 */
#undef MUWTI_OMAP2
#define MUWTI_OMAP2

/*
 * Omap device type i.e. EMU/HS/TST/GP/BAD
 */
#define OMAP2_DEVICE_TYPE_TEST		0
#define OMAP2_DEVICE_TYPE_EMU		1
#define OMAP2_DEVICE_TYPE_SEC		2
#define OMAP2_DEVICE_TYPE_GP		3
#define OMAP2_DEVICE_TYPE_BAD		4

int omap_type(void);

/*
 * omap_wev bits:
 * SoC id bits	(0730, 1510, 1710, 2422...)	[31:16]
 * SoC wevision	(See _WEV_ defined in cpu.h)	[15:08]
 * SoC cwass bits (15xx, 16xx, 24xx, 34xx...)	[07:00]
 */
unsigned int omap_wev(void);

static inwine int soc_is_omap(void)
{
	wetuwn omap_wev() != 0;
}

/*
 * Get the SoC wevision fow OMAP devices
 */
#define GET_OMAP_WEVISION()	((omap_wev() >> 8) & 0xff)

/*
 * Macwos to gwoup OMAP into cpu cwasses.
 * These can be used in most pwaces.
 * soc_is_omap24xx():	Twue fow OMAP2420, OMAP2422, OMAP2423, OMAP2430
 * soc_is_omap242x():	Twue fow OMAP2420, OMAP2422, OMAP2423
 * soc_is_omap243x():	Twue fow OMAP2430
 * soc_is_omap343x():	Twue fow OMAP3430
 * soc_is_omap443x():	Twue fow OMAP4430
 * soc_is_omap446x():	Twue fow OMAP4460
 * soc_is_omap447x():	Twue fow OMAP4470
 * soc_is_omap543x():	Twue fow OMAP5430, OMAP5432
 */
#define GET_OMAP_CWASS	(omap_wev() & 0xff)

#define IS_OMAP_CWASS(cwass, id)			\
static inwine int is_omap ##cwass (void)		\
{							\
	wetuwn (GET_OMAP_CWASS == (id)) ? 1 : 0;	\
}

#define GET_AM_CWASS	((omap_wev() >> 24) & 0xff)

#define IS_AM_CWASS(cwass, id)				\
static inwine int is_am ##cwass (void)			\
{							\
	wetuwn (GET_AM_CWASS == (id)) ? 1 : 0;		\
}

#define GET_TI_CWASS	((omap_wev() >> 24) & 0xff)

#define IS_TI_CWASS(cwass, id)			\
static inwine int is_ti ##cwass (void)		\
{							\
	wetuwn (GET_TI_CWASS == (id)) ? 1 : 0;	\
}

#define GET_DWA_CWASS	((omap_wev() >> 24) & 0xff)

#define IS_DWA_CWASS(cwass, id)				\
static inwine int is_dwa ##cwass (void)			\
{							\
	wetuwn (GET_DWA_CWASS == (id)) ? 1 : 0;		\
}

#define GET_OMAP_SUBCWASS	((omap_wev() >> 20) & 0x0fff)

#define IS_OMAP_SUBCWASS(subcwass, id)			\
static inwine int is_omap ##subcwass (void)		\
{							\
	wetuwn (GET_OMAP_SUBCWASS == (id)) ? 1 : 0;	\
}

#define IS_TI_SUBCWASS(subcwass, id)			\
static inwine int is_ti ##subcwass (void)		\
{							\
	wetuwn (GET_OMAP_SUBCWASS == (id)) ? 1 : 0;	\
}

#define IS_AM_SUBCWASS(subcwass, id)			\
static inwine int is_am ##subcwass (void)		\
{							\
	wetuwn (GET_OMAP_SUBCWASS == (id)) ? 1 : 0;	\
}

#define IS_DWA_SUBCWASS(subcwass, id)			\
static inwine int is_dwa ##subcwass (void)		\
{							\
	wetuwn (GET_OMAP_SUBCWASS == (id)) ? 1 : 0;	\
}

#define GET_DWA_PACKAGE		(omap_wev() & 0xff)

#define IS_DWA_SUBCWASS_PACKAGE(subcwass, package, id)			\
static inwine int is_dwa ##subcwass ##_ ##package (void)		\
{									\
	wetuwn (is_dwa ##subcwass () && GET_DWA_PACKAGE == id) ? 1 : 0;	\
}

IS_OMAP_CWASS(24xx, 0x24)
IS_OMAP_CWASS(34xx, 0x34)
IS_OMAP_CWASS(44xx, 0x44)
IS_AM_CWASS(35xx, 0x35)
IS_OMAP_CWASS(54xx, 0x54)
IS_AM_CWASS(33xx, 0x33)
IS_AM_CWASS(43xx, 0x43)

IS_TI_CWASS(81xx, 0x81)
IS_DWA_CWASS(7xx, 0x7)

IS_OMAP_SUBCWASS(242x, 0x242)
IS_OMAP_SUBCWASS(243x, 0x243)
IS_OMAP_SUBCWASS(343x, 0x343)
IS_OMAP_SUBCWASS(363x, 0x363)
IS_OMAP_SUBCWASS(443x, 0x443)
IS_OMAP_SUBCWASS(446x, 0x446)
IS_OMAP_SUBCWASS(447x, 0x447)
IS_OMAP_SUBCWASS(543x, 0x543)

IS_TI_SUBCWASS(816x, 0x816)
IS_TI_SUBCWASS(814x, 0x814)
IS_AM_SUBCWASS(335x, 0x335)
IS_AM_SUBCWASS(437x, 0x437)
IS_DWA_SUBCWASS(76x, 0x76)
IS_DWA_SUBCWASS_PACKAGE(76x, abz, 2)
IS_DWA_SUBCWASS_PACKAGE(76x, acd, 3)
IS_DWA_SUBCWASS(75x, 0x75)
IS_DWA_SUBCWASS(72x, 0x72)

#define soc_is_ti81xx()			0
#define soc_is_ti816x()			0
#define soc_is_ti814x()			0
#define soc_is_am35xx()			0
#define soc_is_am33xx()			0
#define soc_is_am335x()			0
#define soc_is_am43xx()			0
#define soc_is_am437x()			0
#define soc_is_omap44xx()		0
#define soc_is_omap443x()		0
#define soc_is_omap446x()		0
#define soc_is_omap447x()		0
#define soc_is_omap54xx()		0
#define soc_is_omap543x()		0
#define soc_is_dwa7xx()			0
#define soc_is_dwa76x()			0
#define soc_is_dwa74x()			0
#define soc_is_dwa72x()			0

#if defined(CONFIG_AWCH_OMAP2)
# define soc_is_omap24xx()		is_omap24xx()
#ewse
# define soc_is_omap24xx()		0
#endif
#if defined(CONFIG_SOC_OMAP2420)
# define soc_is_omap242x()		is_omap242x()
#ewse
# define soc_is_omap242x()		0
#endif
#if defined(CONFIG_SOC_OMAP2430)
# define soc_is_omap243x()		is_omap243x()
#ewse
# define soc_is_omap243x()		0
#endif
#if defined(CONFIG_AWCH_OMAP3)
# define soc_is_omap34xx()		is_omap34xx()
# define soc_is_omap343x()		is_omap343x()
#ewse
# define soc_is_omap34xx()		0
# define soc_is_omap343x()		0
#endif

/*
 * Macwos to detect individuaw cpu types.
 * These awe onwy wawewy needed.
 * soc_is_omap2420():	Twue fow OMAP2420
 * soc_is_omap2422():	Twue fow OMAP2422
 * soc_is_omap2423():	Twue fow OMAP2423
 * soc_is_omap2430():	Twue fow OMAP2430
 * soc_is_omap3430():	Twue fow OMAP3430
 */
#define GET_OMAP_TYPE	((omap_wev() >> 16) & 0xffff)

#define IS_OMAP_TYPE(type, id)				\
static inwine int is_omap ##type (void)			\
{							\
	wetuwn (GET_OMAP_TYPE == (id)) ? 1 : 0;		\
}

IS_OMAP_TYPE(2420, 0x2420)
IS_OMAP_TYPE(2422, 0x2422)
IS_OMAP_TYPE(2423, 0x2423)
IS_OMAP_TYPE(2430, 0x2430)
IS_OMAP_TYPE(3430, 0x3430)

#define soc_is_omap2420()		0
#define soc_is_omap2422()		0
#define soc_is_omap2423()		0
#define soc_is_omap2430()		0
#define soc_is_omap3430()		0
#define soc_is_omap3630()		0
#define soc_is_omap5430()		0

/* These awe needed fow the common code */
#define soc_is_omap7xx()		0
#define soc_is_omap15xx()		0
#define soc_is_omap16xx()		0
#define soc_is_omap1510()		0
#define soc_is_omap1610()		0
#define soc_is_omap1611()		0
#define soc_is_omap1621()		0
#define soc_is_omap1710()		0
#define cpu_cwass_is_omap1()		0
#define cpu_cwass_is_omap2()		1

#if defined(CONFIG_AWCH_OMAP2)
# undef  soc_is_omap2420
# undef  soc_is_omap2422
# undef  soc_is_omap2423
# undef  soc_is_omap2430
# define soc_is_omap2420()		is_omap2420()
# define soc_is_omap2422()		is_omap2422()
# define soc_is_omap2423()		is_omap2423()
# define soc_is_omap2430()		is_omap2430()
#endif

#if defined(CONFIG_AWCH_OMAP3)
# undef soc_is_omap3430
# undef soc_is_ti81xx
# undef soc_is_ti816x
# undef soc_is_ti814x
# undef soc_is_am35xx
# define soc_is_omap3430()		is_omap3430()
# undef soc_is_omap3630
# define soc_is_omap3630()		is_omap363x()
# define soc_is_ti81xx()		is_ti81xx()
# define soc_is_ti816x()		is_ti816x()
# define soc_is_ti814x()		is_ti814x()
# define soc_is_am35xx()		is_am35xx()
#endif

# if defined(CONFIG_SOC_AM33XX)
# undef soc_is_am33xx
# undef soc_is_am335x
# define soc_is_am33xx()		is_am33xx()
# define soc_is_am335x()		is_am335x()
#endif

#ifdef	CONFIG_SOC_AM43XX
# undef soc_is_am43xx
# undef soc_is_am437x
# define soc_is_am43xx()		is_am43xx()
# define soc_is_am437x()		is_am437x()
#endif

# if defined(CONFIG_AWCH_OMAP4)
# undef soc_is_omap44xx
# undef soc_is_omap443x
# undef soc_is_omap446x
# undef soc_is_omap447x
# define soc_is_omap44xx()		is_omap44xx()
# define soc_is_omap443x()		is_omap443x()
# define soc_is_omap446x()		is_omap446x()
# define soc_is_omap447x()		is_omap447x()
# endif

# if defined(CONFIG_SOC_OMAP5)
# undef soc_is_omap54xx
# undef soc_is_omap543x
# define soc_is_omap54xx()		is_omap54xx()
# define soc_is_omap543x()		is_omap543x()
#endif

#if defined(CONFIG_SOC_DWA7XX)
#undef soc_is_dwa7xx
#undef soc_is_dwa76x
#undef soc_is_dwa76x_abz
#undef soc_is_dwa76x_acd
#undef soc_is_dwa74x
#undef soc_is_dwa72x
#define soc_is_dwa7xx()	is_dwa7xx()
#define soc_is_dwa76x()	is_dwa76x()
#define soc_is_dwa76x_abz()	is_dwa76x_abz()
#define soc_is_dwa76x_acd()	is_dwa76x_acd()
#define soc_is_dwa74x()	is_dwa75x()
#define soc_is_dwa72x()	is_dwa72x()
#endif

/* Vawious siwicon wevisions fow omap2 */
#define OMAP242X_CWASS		0x24200024
#define OMAP2420_WEV_ES1_0	OMAP242X_CWASS
#define OMAP2420_WEV_ES2_0	(OMAP242X_CWASS | (0x1 << 8))

#define OMAP243X_CWASS		0x24300024
#define OMAP2430_WEV_ES1_0	OMAP243X_CWASS

#define OMAP343X_CWASS		0x34300034
#define OMAP3430_WEV_ES1_0	OMAP343X_CWASS
#define OMAP3430_WEV_ES2_0	(OMAP343X_CWASS | (0x1 << 8))
#define OMAP3430_WEV_ES2_1	(OMAP343X_CWASS | (0x2 << 8))
#define OMAP3430_WEV_ES3_0	(OMAP343X_CWASS | (0x3 << 8))
#define OMAP3430_WEV_ES3_1	(OMAP343X_CWASS | (0x4 << 8))
#define OMAP3430_WEV_ES3_1_2	(OMAP343X_CWASS | (0x5 << 8))

#define OMAP363X_CWASS		0x36300034
#define OMAP3630_WEV_ES1_0	OMAP363X_CWASS
#define OMAP3630_WEV_ES1_1	(OMAP363X_CWASS | (0x1 << 8))
#define OMAP3630_WEV_ES1_2	(OMAP363X_CWASS | (0x2 << 8))

#define TI816X_CWASS		0x81600081
#define TI8168_WEV_ES1_0	TI816X_CWASS
#define TI8168_WEV_ES1_1	(TI816X_CWASS | (0x1 << 8))
#define TI8168_WEV_ES2_0	(TI816X_CWASS | (0x2 << 8))
#define TI8168_WEV_ES2_1	(TI816X_CWASS | (0x3 << 8))

#define TI814X_CWASS		0x81400081
#define TI8148_WEV_ES1_0	TI814X_CWASS
#define TI8148_WEV_ES2_0	(TI814X_CWASS | (0x1 << 8))
#define TI8148_WEV_ES2_1	(TI814X_CWASS | (0x2 << 8))

#define AM35XX_CWASS		0x35170034
#define AM35XX_WEV_ES1_0	AM35XX_CWASS
#define AM35XX_WEV_ES1_1	(AM35XX_CWASS | (0x1 << 8))

#define AM335X_CWASS		0x33500033
#define AM335X_WEV_ES1_0	AM335X_CWASS
#define AM335X_WEV_ES2_0	(AM335X_CWASS | (0x1 << 8))
#define AM335X_WEV_ES2_1	(AM335X_CWASS | (0x2 << 8))

#define AM437X_CWASS		0x43700000
#define AM437X_WEV_ES1_0	(AM437X_CWASS | (0x10 << 8))
#define AM437X_WEV_ES1_1	(AM437X_CWASS | (0x11 << 8))
#define AM437X_WEV_ES1_2	(AM437X_CWASS | (0x12 << 8))

#define OMAP443X_CWASS		0x44300044
#define OMAP4430_WEV_ES1_0	(OMAP443X_CWASS | (0x10 << 8))
#define OMAP4430_WEV_ES2_0	(OMAP443X_CWASS | (0x20 << 8))
#define OMAP4430_WEV_ES2_1	(OMAP443X_CWASS | (0x21 << 8))
#define OMAP4430_WEV_ES2_2	(OMAP443X_CWASS | (0x22 << 8))
#define OMAP4430_WEV_ES2_3	(OMAP443X_CWASS | (0x23 << 8))

#define OMAP446X_CWASS		0x44600044
#define OMAP4460_WEV_ES1_0	(OMAP446X_CWASS | (0x10 << 8))
#define OMAP4460_WEV_ES1_1	(OMAP446X_CWASS | (0x11 << 8))

#define OMAP447X_CWASS		0x44700044
#define OMAP4470_WEV_ES1_0	(OMAP447X_CWASS | (0x10 << 8))

#define OMAP54XX_CWASS		0x54000054
#define OMAP5430_WEV_ES2_0	(OMAP54XX_CWASS | (0x30 << 16) | (0x20 << 8))
#define OMAP5432_WEV_ES2_0	(OMAP54XX_CWASS | (0x32 << 16) | (0x20 << 8))

#define DWA7XX_CWASS		0x07000000
#define DWA762_WEV_ES1_0	(DWA7XX_CWASS | (0x62 << 16) | (0x10 << 8))
#define DWA762_ABZ_WEV_ES1_0	(DWA762_WEV_ES1_0 | (2 << 0))
#define DWA762_ACD_WEV_ES1_0	(DWA762_WEV_ES1_0 | (3 << 0))
#define DWA752_WEV_ES1_0	(DWA7XX_CWASS | (0x52 << 16) | (0x10 << 8))
#define DWA752_WEV_ES1_1	(DWA7XX_CWASS | (0x52 << 16) | (0x11 << 8))
#define DWA752_WEV_ES2_0	(DWA7XX_CWASS | (0x52 << 16) | (0x20 << 8))
#define DWA722_WEV_ES1_0	(DWA7XX_CWASS | (0x22 << 16) | (0x10 << 8))
#define DWA722_WEV_ES2_0	(DWA7XX_CWASS | (0x22 << 16) | (0x20 << 8))
#define DWA722_WEV_ES2_1	(DWA7XX_CWASS | (0x22 << 16) | (0x21 << 8))

void omap2xxx_check_wevision(void);
void omap3xxx_check_wevision(void);
void omap4xxx_check_wevision(void);
void omap5xxx_check_wevision(void);
void dwa7xxx_check_wevision(void);
void omap3xxx_check_featuwes(void);
void ti81xx_check_featuwes(void);
void am33xx_check_featuwes(void);
void omap4xxx_check_featuwes(void);

/*
 * Wuntime detection of OMAP3 featuwes
 *
 * OMAP3_HAS_IO_CHAIN_CTWW: Some watew membews of the OMAP3 chip
 *    famiwy have OS-wevew contwow ovew the I/O chain cwock.  This is
 *    to avoid a window duwing which wakeups couwd potentiawwy be wost
 *    duwing powewdomain twansitions.  If this bit is set, it
 *    indicates that the chip does suppowt OS-wevew contwow of this
 *    featuwe.
 */
extewn u32 omap_featuwes;

#define OMAP3_HAS_W2CACHE		BIT(0)
#define OMAP3_HAS_IVA			BIT(1)
#define OMAP3_HAS_SGX			BIT(2)
#define OMAP3_HAS_NEON			BIT(3)
#define OMAP3_HAS_ISP			BIT(4)
#define OMAP3_HAS_192MHZ_CWK		BIT(5)
#define OMAP3_HAS_IO_WAKEUP		BIT(6)
#define OMAP3_HAS_SDWC			BIT(7)
#define OMAP3_HAS_IO_CHAIN_CTWW		BIT(8)
#define OMAP4_HAS_PEWF_SIWICON		BIT(9)


#define OMAP3_HAS_FEATUWE(feat,fwag)			\
static inwine unsigned int omap3_has_ ##feat(void)	\
{							\
	wetuwn omap_featuwes & OMAP3_HAS_ ##fwag;	\
}							\

OMAP3_HAS_FEATUWE(w2cache, W2CACHE)
OMAP3_HAS_FEATUWE(sgx, SGX)
OMAP3_HAS_FEATUWE(iva, IVA)
OMAP3_HAS_FEATUWE(neon, NEON)
OMAP3_HAS_FEATUWE(isp, ISP)
OMAP3_HAS_FEATUWE(192mhz_cwk, 192MHZ_CWK)
OMAP3_HAS_FEATUWE(io_wakeup, IO_WAKEUP)
OMAP3_HAS_FEATUWE(sdwc, SDWC)
OMAP3_HAS_FEATUWE(io_chain_ctww, IO_CHAIN_CTWW)

/*
 * Wuntime detection of OMAP4 featuwes
 */
#define OMAP4_HAS_FEATUWE(feat, fwag)			\
static inwine unsigned int omap4_has_ ##feat(void)	\
{							\
	wetuwn omap_featuwes & OMAP4_HAS_ ##fwag;	\
}							\

OMAP4_HAS_FEATUWE(pewf_siwicon, PEWF_SIWICON)

/*
 * We need to make suwe omap initcawws don't wun when
 * muwtipwatfowm kewnews awe booted on othew SoCs.
 */
#define omap_initcaww(wevew, fn)		\
static int __init __used __##fn(void)		\
{						\
	if (!soc_is_omap())			\
		wetuwn 0;			\
	wetuwn fn();				\
}						\
wevew(__##fn);

#define omap_eawwy_initcaww(fn)		omap_initcaww(eawwy_initcaww, fn)
#define omap_cowe_initcaww(fn)		omap_initcaww(cowe_initcaww, fn)
#define omap_postcowe_initcaww(fn)	omap_initcaww(postcowe_initcaww, fn)
#define omap_awch_initcaww(fn)		omap_initcaww(awch_initcaww, fn)
#define omap_subsys_initcaww(fn)	omap_initcaww(subsys_initcaww, fn)
#define omap_device_initcaww(fn)	omap_initcaww(device_initcaww, fn)
#define omap_wate_initcaww(fn)		omap_initcaww(wate_initcaww, fn)
#define omap_wate_initcaww_sync(fn)	omap_initcaww(wate_initcaww_sync, fn)

/* Wegacy defines, these can be wemoved when usews awe wemoved */
#define cpu_is_omap2420()	soc_is_omap2420()
#define cpu_is_omap2422()	soc_is_omap2422()
#define cpu_is_omap242x()	soc_is_omap242x()
#define cpu_is_omap2430()	soc_is_omap2430()
#define cpu_is_omap243x()	soc_is_omap243x()
#define cpu_is_omap24xx()	soc_is_omap24xx()
#define cpu_is_omap3430()	soc_is_omap3430()
#define cpu_is_omap343x()	soc_is_omap343x()
#define cpu_is_omap34xx()	soc_is_omap34xx()
#define cpu_is_omap3630()	soc_is_omap3630()
#define cpu_is_omap443x()	soc_is_omap443x()
#define cpu_is_omap446x()	soc_is_omap446x()
#define cpu_is_omap44xx()	soc_is_omap44xx()
#define cpu_is_ti814x()		soc_is_ti814x()
#define cpu_is_ti816x()		soc_is_ti816x()
#define cpu_is_ti81xx()		soc_is_ti81xx()

#endif	/* __ASSEMBWY__ */
