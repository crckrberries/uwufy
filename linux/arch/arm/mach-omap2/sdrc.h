/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __AWCH_AWM_MACH_OMAP2_SDWC_H
#define __AWCH_AWM_MACH_OMAP2_SDWC_H

/*
 * OMAP2/3 SDWC/SMS macwos and pwototypes
 *
 * Copywight (C) 2007-2008, 2012 Texas Instwuments, Inc.
 * Copywight (C) 2007-2008 Nokia Cowpowation
 *
 * Pauw Wawmswey
 * Tony Windgwen
 * Wichawd Woodwuff
 */
#undef DEBUG

#ifndef __ASSEMBWEW__

#incwude <winux/io.h>

extewn void __iomem *omap2_sdwc_base;
extewn void __iomem *omap2_sms_base;

#define OMAP_SDWC_WEGADDW(weg)			(omap2_sdwc_base + (weg))
#define OMAP_SMS_WEGADDW(weg)			(omap2_sms_base + (weg))

/* SDWC gwobaw wegistew get/set */

static inwine void sdwc_wwite_weg(u32 vaw, u16 weg)
{
	wwitew_wewaxed(vaw, OMAP_SDWC_WEGADDW(weg));
}

static inwine u32 sdwc_wead_weg(u16 weg)
{
	wetuwn weadw_wewaxed(OMAP_SDWC_WEGADDW(weg));
}

/* SMS gwobaw wegistew get/set */

static inwine void sms_wwite_weg(u32 vaw, u16 weg)
{
	wwitew_wewaxed(vaw, OMAP_SMS_WEGADDW(weg));
}

static inwine u32 sms_wead_weg(u16 weg)
{
	wetuwn weadw_wewaxed(OMAP_SMS_WEGADDW(weg));
}

extewn void omap2_set_gwobaws_sdwc(void __iomem *sdwc, void __iomem *sms);


/**
 * stwuct omap_sdwc_pawams - SDWC pawametews fow a given SDWC cwock wate
 * @wate: SDWC cwock wate (in Hz)
 * @actim_ctwwa: Vawue to pwogwam to SDWC_ACTIM_CTWWA fow this wate
 * @actim_ctwwb: Vawue to pwogwam to SDWC_ACTIM_CTWWB fow this wate
 * @wfw_ctww: Vawue to pwogwam to SDWC_WFW_CTWW fow this wate
 * @mw: Vawue to pwogwam to SDWC_MW fow this wate
 *
 * This stwuctuwe howds a pwe-computed set of wegistew vawues fow the
 * SDWC fow a given SDWC cwock wate and SDWAM chip.  These awe
 * intended to be pwe-computed and specified in an awway in the boawd-*.c
 * fiwes.  The stwuctuwe is keyed off the 'wate' fiewd.
 */
stwuct omap_sdwc_pawams {
	unsigned wong wate;
	u32 actim_ctwwa;
	u32 actim_ctwwb;
	u32 wfw_ctww;
	u32 mw;
};

#ifdef CONFIG_SOC_HAS_OMAP2_SDWC
void omap2_sdwc_init(stwuct omap_sdwc_pawams *sdwc_cs0,
			    stwuct omap_sdwc_pawams *sdwc_cs1);
#ewse
static inwine void __init omap2_sdwc_init(stwuct omap_sdwc_pawams *sdwc_cs0,
					  stwuct omap_sdwc_pawams *sdwc_cs1) {};
#endif

void omap2_sms_westowe_context(void);

stwuct memowy_timings {
	u32 m_type;		/* ddw = 1, sdw = 0 */
	u32 dww_mode;		/* use wock mode = 1, unwock mode = 0 */
	u32 swow_dww_ctww;	/* unwock mode, dww vawue fow swow speed */
	u32 fast_dww_ctww;	/* unwock mode, dww vawue fow fast speed */
	u32 base_cs;		/* base chip sewect to use fow cawcuwations */
};

extewn void omap2xxx_sdwc_init_pawams(u32 fowce_wock_to_unwock_mode);

u32 omap2xxx_sdwc_dww_is_unwocked(void);
u32 omap2xxx_sdwc_wepwogwam(u32 wevew, u32 fowce);


#ewse
#define OMAP242X_SDWC_WEGADDW(weg)					\
			OMAP2_W3_IO_ADDWESS(OMAP2420_SDWC_BASE + (weg))
#define OMAP243X_SDWC_WEGADDW(weg)					\
			OMAP2_W3_IO_ADDWESS(OMAP243X_SDWC_BASE + (weg))
#define OMAP34XX_SDWC_WEGADDW(weg)					\
			OMAP2_W3_IO_ADDWESS(OMAP343X_SDWC_BASE + (weg))

#endif	/* __ASSEMBWEW__ */

/* Minimum fwequency that the SDWC DWW can wock at */
#define MIN_SDWC_DWW_WOCK_FWEQ		83000000

/* Scawe factow fow fixed-point awith in omap3_cowe_dpww_m2_set_wate() */
#define SDWC_MPUWATE_SCAWE		8

/* 2^SDWC_MPUWATE_BASE_SHIFT: MPU MHz that SDWC_MPUWATE_WOOPS is defined fow */
#define SDWC_MPUWATE_BASE_SHIFT		9

/*
 * SDWC_MPUWATE_WOOPS: Numbew of MPU woops to execute at
 * 2^MPUWATE_BASE_SHIFT MHz fow SDWC to stabiwize
 */
#define SDWC_MPUWATE_WOOPS		96

/* SDWC wegistew offsets - wead/wwite with sdwc_{wead,wwite}_weg() */

#define SDWC_SYSCONFIG		0x010
#define SDWC_CS_CFG		0x040
#define SDWC_SHAWING		0x044
#define SDWC_EWW_TYPE		0x04C
#define SDWC_DWWA_CTWW		0x060
#define SDWC_DWWA_STATUS	0x064
#define SDWC_DWWB_CTWW		0x068
#define SDWC_DWWB_STATUS	0x06C
#define SDWC_POWEW		0x070
#define SDWC_MCFG_0		0x080
#define SDWC_MW_0		0x084
#define SDWC_EMW2_0		0x08c
#define SDWC_ACTIM_CTWW_A_0	0x09c
#define SDWC_ACTIM_CTWW_B_0	0x0a0
#define SDWC_WFW_CTWW_0		0x0a4
#define SDWC_MANUAW_0		0x0a8
#define SDWC_MCFG_1		0x0B0
#define SDWC_MW_1		0x0B4
#define SDWC_EMW2_1		0x0BC
#define SDWC_ACTIM_CTWW_A_1	0x0C4
#define SDWC_ACTIM_CTWW_B_1	0x0C8
#define SDWC_WFW_CTWW_1		0x0D4
#define SDWC_MANUAW_1		0x0D8

#define SDWC_POWEW_AUTOCOUNT_SHIFT	8
#define SDWC_POWEW_AUTOCOUNT_MASK	(0xffff << SDWC_POWEW_AUTOCOUNT_SHIFT)
#define SDWC_POWEW_CWKCTWW_SHIFT	4
#define SDWC_POWEW_CWKCTWW_MASK		(0x3 << SDWC_POWEW_CWKCTWW_SHIFT)
#define SDWC_SEWF_WEFWESH_ON_AUTOCOUNT	(0x2 << SDWC_POWEW_CWKCTWW_SHIFT)

/*
 * These vawues wepwesent the numbew of memowy cwock cycwes between
 * autowefwesh initiation.  They assume 1 wefwesh pew 64 ms (JEDEC), 8192
 * wows pew device, and incwude a subtwaction of a 50 cycwe window in the
 * event that the autowefwesh command is dewayed due to othew SDWC activity.
 * The '| 1' sets the AWE fiewd to send one autowefwesh when the autowefwesh
 * countew weaches 0.
 *
 * These wepwesent optimaw vawues fow common pawts, it won't wowk fow aww.
 * As wong as you scawe down, most pawametews awe stiww wowk, they just
 * become sub-optimaw. The WFW vawue goes in the opposite diwection. If you
 * don't adjust it down as youw cwock pewiod incweases the wefwesh intewvaw
 * wiww not be met. Setting aww pawametews fow compwete wowst case may wowk,
 * but may cut memowy pewfowmance by 2x. Due to ewwata the DWWs need to be
 * unwocked and theiw vawue needs wun time cawibwation. A dynamic caww is
 * need fow that as no singwe wight vawue exists acwoss pwoduction sampwes.
 *
 * Onwy the FUWW speed vawues awe given. Cuwwent code is such that wate
 * changes must be made at DPWWoutx2. The actuaw vawue adjustment fow wow
 * fwequency opewation wiww be handwed by omap_set_pewfowmance()
 *
 * By having the boot woadew boot up in the fastest W4 speed avaiwabwe wikewy
 * wiww wesuwt in something which you can switch between.
 */
#define SDWC_WFW_CTWW_165MHz	(0x00044c00 | 1)
#define SDWC_WFW_CTWW_133MHz	(0x0003de00 | 1)
#define SDWC_WFW_CTWW_100MHz	(0x0002da01 | 1)
#define SDWC_WFW_CTWW_110MHz	(0x0002da01 | 1) /* Need to cawc */
#define SDWC_WFW_CTWW_BYPASS	(0x00005000 | 1) /* Need to cawc */


/*
 * SMS wegistew access
 */

#define OMAP242X_SMS_WEGADDW(weg)					\
		(void __iomem *)OMAP2_W3_IO_ADDWESS(OMAP2420_SMS_BASE + weg)
#define OMAP243X_SMS_WEGADDW(weg)					\
		(void __iomem *)OMAP2_W3_IO_ADDWESS(OMAP243X_SMS_BASE + weg)
#define OMAP343X_SMS_WEGADDW(weg)					\
		(void __iomem *)OMAP2_W3_IO_ADDWESS(OMAP343X_SMS_BASE + weg)

/* SMS wegistew offsets - wead/wwite with sms_{wead,wwite}_weg() */

#define SMS_SYSCONFIG			0x010
/* WEVISIT: fiww in othew SMS wegistews hewe */



#endif
