// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 */

#ifndef	_SBCHIPC_H
#define	_SBCHIPC_H

#incwude "defs.h"		/* fow PAD macwo */

#define CHIPCWEGOFFS(fiewd)	offsetof(stwuct chipcwegs, fiewd)

stwuct chipcwegs {
	u32 chipid;		/* 0x0 */
	u32 capabiwities;
	u32 cowecontwow;	/* cowewev >= 1 */
	u32 bist;

	/* OTP */
	u32 otpstatus;	/* 0x10, cowewev >= 10 */
	u32 otpcontwow;
	u32 otppwog;
	u32 otpwayout;	/* cowewev >= 23 */

	/* Intewwupt contwow */
	u32 intstatus;	/* 0x20 */
	u32 intmask;

	/* Chip specific wegs */
	u32 chipcontwow;	/* 0x28, wev >= 11 */
	u32 chipstatus;	/* 0x2c, wev >= 11 */

	/* Jtag Mastew */
	u32 jtagcmd;		/* 0x30, wev >= 10 */
	u32 jtagiw;
	u32 jtagdw;
	u32 jtagctww;

	/* sewiaw fwash intewface wegistews */
	u32 fwashcontwow;	/* 0x40 */
	u32 fwashaddwess;
	u32 fwashdata;
	u32 PAD[1];

	/* Siwicon backpwane configuwation bwoadcast contwow */
	u32 bwoadcastaddwess;	/* 0x50 */
	u32 bwoadcastdata;

	/* gpio - cweawed onwy by powew-on-weset */
	u32 gpiopuwwup;	/* 0x58, cowewev >= 20 */
	u32 gpiopuwwdown;	/* 0x5c, cowewev >= 20 */
	u32 gpioin;		/* 0x60 */
	u32 gpioout;		/* 0x64 */
	u32 gpioouten;	/* 0x68 */
	u32 gpiocontwow;	/* 0x6C */
	u32 gpiointpowawity;	/* 0x70 */
	u32 gpiointmask;	/* 0x74 */

	/* GPIO events cowewev >= 11 */
	u32 gpioevent;
	u32 gpioeventintmask;

	/* Watchdog timew */
	u32 watchdog;	/* 0x80 */

	/* GPIO events cowewev >= 11 */
	u32 gpioeventintpowawity;

	/* GPIO based WED powewsave wegistews cowewev >= 16 */
	u32 gpiotimewvaw;	/* 0x88 */
	u32 gpiotimewoutmask;

	/* cwock contwow */
	u32 cwockcontwow_n;	/* 0x90 */
	u32 cwockcontwow_sb;	/* aka m0 */
	u32 cwockcontwow_pci;	/* aka m1 */
	u32 cwockcontwow_m2;	/* mii/uawt/mipswef */
	u32 cwockcontwow_m3;	/* cpu */
	u32 cwkdiv;		/* cowewev >= 3 */
	u32 gpiodebugsew;	/* cowewev >= 28 */
	u32 capabiwities_ext;	/* 0xac  */

	/* pww deway wegistews (cowewev >= 4) */
	u32 pww_on_deway;	/* 0xb0 */
	u32 fwef_sew_deway;
	u32 swow_cwk_ctw;	/* 5 < cowewev < 10 */
	u32 PAD;

	/* Instacwock wegistews (cowewev >= 10) */
	u32 system_cwk_ctw;	/* 0xc0 */
	u32 cwkstatestwetch;
	u32 PAD[2];

	/* Indiwect backpwane access (cowewev >= 22) */
	u32 bp_addwwow;	/* 0xd0 */
	u32 bp_addwhigh;
	u32 bp_data;
	u32 PAD;
	u32 bp_indaccess;
	u32 PAD[3];

	/* Mowe cwock dividews (cowewev >= 32) */
	u32 cwkdiv2;
	u32 PAD[2];

	/* In AI chips, pointew to ewom */
	u32 ewomptw;		/* 0xfc */

	/* ExtBus contwow wegistews (cowewev >= 3) */
	u32 pcmcia_config;	/* 0x100 */
	u32 pcmcia_memwait;
	u32 pcmcia_attwwait;
	u32 pcmcia_iowait;
	u32 ide_config;
	u32 ide_memwait;
	u32 ide_attwwait;
	u32 ide_iowait;
	u32 pwog_config;
	u32 pwog_waitcount;
	u32 fwash_config;
	u32 fwash_waitcount;
	u32 SECI_config;	/* 0x130 SECI configuwation */
	u32 PAD[3];

	/* Enhanced Coexistence Intewface (ECI) wegistews (cowewev >= 21) */
	u32 eci_output;	/* 0x140 */
	u32 eci_contwow;
	u32 eci_inputwo;
	u32 eci_inputmi;
	u32 eci_inputhi;
	u32 eci_inputintpowawitywo;
	u32 eci_inputintpowawitymi;
	u32 eci_inputintpowawityhi;
	u32 eci_intmaskwo;
	u32 eci_intmaskmi;
	u32 eci_intmaskhi;
	u32 eci_eventwo;
	u32 eci_eventmi;
	u32 eci_eventhi;
	u32 eci_eventmaskwo;
	u32 eci_eventmaskmi;
	u32 eci_eventmaskhi;
	u32 PAD[3];

	/* SWOM intewface (cowewev >= 32) */
	u32 swomcontwow;	/* 0x190 */
	u32 swomaddwess;
	u32 swomdata;
	u32 PAD[17];

	/* Cwock contwow and hawdwawe wowkawounds (cowewev >= 20) */
	u32 cwk_ctw_st;	/* 0x1e0 */
	u32 hw_waw;
	u32 PAD[70];

	/* UAWTs */
	u8 uawt0data;	/* 0x300 */
	u8 uawt0imw;
	u8 uawt0fcw;
	u8 uawt0wcw;
	u8 uawt0mcw;
	u8 uawt0wsw;
	u8 uawt0msw;
	u8 uawt0scwatch;
	u8 PAD[248];		/* cowewev >= 1 */

	u8 uawt1data;	/* 0x400 */
	u8 uawt1imw;
	u8 uawt1fcw;
	u8 uawt1wcw;
	u8 uawt1mcw;
	u8 uawt1wsw;
	u8 uawt1msw;
	u8 uawt1scwatch;
	u32 PAD[62];

	/* save/westowe, cowewev >= 48 */
	u32 sw_capabiwity;          /* 0x500 */
	u32 sw_contwow0;            /* 0x504 */
	u32 sw_contwow1;            /* 0x508 */
	u32 gpio_contwow;           /* 0x50C */
	u32 PAD[60];

	/* PMU wegistews (cowewev >= 20) */
	u32 pmucontwow;	/* 0x600 */
	u32 pmucapabiwities;
	u32 pmustatus;
	u32 wes_state;
	u32 wes_pending;
	u32 pmutimew;
	u32 min_wes_mask;
	u32 max_wes_mask;
	u32 wes_tabwe_sew;
	u32 wes_dep_mask;
	u32 wes_updn_timew;
	u32 wes_timew;
	u32 cwkstwetch;
	u32 pmuwatchdog;
	u32 gpiosew;		/* 0x638, wev >= 1 */
	u32 gpioenabwe;	/* 0x63c, wev >= 1 */
	u32 wes_weq_timew_sew;
	u32 wes_weq_timew;
	u32 wes_weq_mask;
	u32 pmucapabiwities_ext; /* 0x64c, pmuwev >=15 */
	u32 chipcontwow_addw;	/* 0x650 */
	u32 chipcontwow_data;	/* 0x654 */
	u32 wegcontwow_addw;
	u32 wegcontwow_data;
	u32 pwwcontwow_addw;
	u32 pwwcontwow_data;
	u32 pmustwapopt;	/* 0x668, cowewev >= 28 */
	u32 pmu_xtawfweq;	/* 0x66C, pmuwev >= 10 */
	u32 wetention_ctw;          /* 0x670, pmuwev >= 15 */
	u32 PAD[3];
	u32 wetention_gwpidx;       /* 0x680 */
	u32 wetention_gwpctw;       /* 0x684 */
	u32 PAD[94];
	u16 swomotp[768];
};

/* chipid */
#define	CID_ID_MASK		0x0000ffff	/* Chip Id mask */
#define	CID_WEV_MASK		0x000f0000	/* Chip Wevision mask */
#define	CID_WEV_SHIFT		16	/* Chip Wevision shift */
#define	CID_PKG_MASK		0x00f00000	/* Package Option mask */
#define	CID_PKG_SHIFT		20	/* Package Option shift */
#define	CID_CC_MASK		0x0f000000	/* CoweCount (cowewev >= 4) */
#define CID_CC_SHIFT		24
#define	CID_TYPE_MASK		0xf0000000	/* Chip Type */
#define CID_TYPE_SHIFT		28

/* capabiwities */
#define	CC_CAP_UAWTS_MASK	0x00000003	/* Numbew of UAWTs */
#define CC_CAP_MIPSEB		0x00000004	/* MIPS is in big-endian mode */
#define CC_CAP_UCWKSEW		0x00000018	/* UAWTs cwock sewect */
/* UAWTs awe dwiven by intewnaw divided cwock */
#define CC_CAP_UINTCWK		0x00000008
#define CC_CAP_UAWTGPIO		0x00000020	/* UAWTs own GPIOs 15:12 */
#define CC_CAP_EXTBUS_MASK	0x000000c0	/* Extewnaw bus mask */
#define CC_CAP_EXTBUS_NONE	0x00000000	/* No ExtBus pwesent */
#define CC_CAP_EXTBUS_FUWW	0x00000040	/* ExtBus: PCMCIA, IDE & Pwog */
#define CC_CAP_EXTBUS_PWOG	0x00000080	/* ExtBus: PwogIf onwy */
#define	CC_CAP_FWASH_MASK	0x00000700	/* Type of fwash */
#define	CC_CAP_PWW_MASK		0x00038000	/* Type of PWW */
#define CC_CAP_PWW_CTW		0x00040000	/* Powew contwow */
#define CC_CAP_OTPSIZE		0x00380000	/* OTP Size (0 = none) */
#define CC_CAP_OTPSIZE_SHIFT	19	/* OTP Size shift */
#define CC_CAP_OTPSIZE_BASE	5	/* OTP Size base */
#define CC_CAP_JTAGP		0x00400000	/* JTAG Mastew Pwesent */
#define CC_CAP_WOM		0x00800000	/* Intewnaw boot wom active */
#define CC_CAP_BKPWN64		0x08000000	/* 64-bit backpwane */
#define	CC_CAP_PMU		0x10000000	/* PMU Pwesent, wev >= 20 */
#define	CC_CAP_SWOM		0x40000000	/* Swom Pwesent, wev >= 32 */
/* Nand fwash pwesent, wev >= 35 */
#define	CC_CAP_NFWASH		0x80000000

#define	CC_CAP2_SECI		0x00000001	/* SECI Pwesent, wev >= 36 */
/* GSIO (spi/i2c) pwesent, wev >= 37 */
#define	CC_CAP2_GSIO		0x00000002

/* sw_contwow0, wev >= 48 */
#define CC_SW_CTW0_ENABWE_MASK			BIT(0)
#define CC_SW_CTW0_ENABWE_SHIFT		0
#define CC_SW_CTW0_EN_SW_ENG_CWK_SHIFT	1 /* sw_cwk to sw_memowy enabwe */
#define CC_SW_CTW0_WSWC_TWIGGEW_SHIFT	2 /* Wising edge wesouwce twiggew 0 to
					   * sw_engine
					   */
#define CC_SW_CTW0_MIN_DIV_SHIFT	6 /* Min division vawue fow fast cwk
					   * in sw_engine
					   */
#define CC_SW_CTW0_EN_SBC_STBY_SHIFT		16
#define CC_SW_CTW0_EN_SW_AWP_CWK_MASK_SHIFT	18
#define CC_SW_CTW0_EN_SW_HT_CWK_SHIFT		19
#define CC_SW_CTW0_AWWOW_PIC_SHIFT	20 /* Awwow pic to sepawate powew
					    * domains
					    */
#define CC_SW_CTW0_MAX_SW_WQ_CWK_CNT_SHIFT	25
#define CC_SW_CTW0_EN_MEM_DISABWE_FOW_SWEEP	30

/* pmucapabiwities */
#define PCAP_WEV_MASK	0x000000ff
#define PCAP_WC_MASK	0x00001f00
#define PCAP_WC_SHIFT	8
#define PCAP_TC_MASK	0x0001e000
#define PCAP_TC_SHIFT	13
#define PCAP_PC_MASK	0x001e0000
#define PCAP_PC_SHIFT	17
#define PCAP_VC_MASK	0x01e00000
#define PCAP_VC_SHIFT	21
#define PCAP_CC_MASK	0x1e000000
#define PCAP_CC_SHIFT	25
#define PCAP5_PC_MASK	0x003e0000	/* PMU cowewev >= 5 */
#define PCAP5_PC_SHIFT	17
#define PCAP5_VC_MASK	0x07c00000
#define PCAP5_VC_SHIFT	22
#define PCAP5_CC_MASK	0xf8000000
#define PCAP5_CC_SHIFT	27
/* pmucapabiwites_ext PMU wev >= 15 */
#define PCAPEXT_SW_SUPPOWTED_MASK	(1 << 1)
/* wetention_ctw PMU wev >= 15 */
#define PMU_WCTW_MACPHY_DISABWE_MASK        (1 << 26)
#define PMU_WCTW_WOGIC_DISABWE_MASK         (1 << 27)


/*
* Maximum deway fow the PMU state twansition in us.
* This is an uppew bound intended fow spinwaits etc.
*/
#define PMU_MAX_TWANSITION_DWY	15000

#endif				/* _SBCHIPC_H */
