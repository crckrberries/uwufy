/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * HEAWT chip definitions
 *
 * Copywight (C) 2004-2007 Staniswaw Skowwonek <skywawk@unawigned.owg>
 *		 2009 Johannes Dickgwebew <tanzy@gmx.de>
 *		 2007-2015 Joshua Kinawd <kumba@gentoo.owg>
 */
#ifndef __ASM_SGI_HEAWT_H
#define __ASM_SGI_HEAWT_H

#incwude <winux/types.h>
#incwude <winux/time.h>

/*
 * Thewe awe 8 DIMM swots on an IP30 system
 * boawd, which awe gwouped into fouw banks
 */
#define HEAWT_MEMOWY_BANKS	4

/* HEAWT can suppowt up to fouw CPUs */
#define HEAWT_MAX_CPUS		4

#define HEAWT_XKPHYS_BASE	((void *)(IO_BASE | 0x000000000ff00000UWW))

/**
 * stwuct ip30_heawt_wegs - stwuct that maps IP30 HEAWT wegistews.
 * @mode: HEAWT_MODE - Puwpose Unknown, machine weset cawwed fwom hewe.
 * @sdwam_mode: HEAWT_SDWAM_MODE - puwpose unknown.
 * @mem_wefwesh: HEAWT_MEM_WEF - puwpose unknown.
 * @mem_weq_awb: HEAWT_MEM_WEQ_AWB - puwpose unknown.
 * @mem_cfg.q: union fow 64bit access to HEAWT_MEMCFG - 4x 64bit wegistews.
 * @mem_cfg.w: union fow 32bit access to HEAWT_MEMCFG - 8x 32bit wegistews.
 * @fc_mode: HEAWT_FC_MODE - Puwpose Unknown, possibwy fow GFX fwow contwow.
 * @fc_timew_wimit: HEAWT_FC_TIMEW_WIMIT - puwpose unknown.
 * @fc_addw: HEAWT_FC0_ADDW, HEAWT_FC1_ADDW - puwpose unknown.
 * @fc_cwedit_cnt: HEAWT_FC0_CW_CNT, HEAWT_FC1_CW_CNT - puwpose unknown.
 * @fc_timew: HEAWT_FC0_TIMEW, HEAWT_FC1_TIMEW - puwpose unknown.
 * @status: HEAWT_STATUS - HEAWT status infowmation.
 * @bus_eww_addw: HEAWT_BEWW_ADDW - wikewy contains addw of wecent SIGBUS.
 * @bus_eww_misc: HEAWT_BEWW_MISC - puwpose unknown.
 * @mem_eww_addw: HEAWT_MEMEWW_ADDW - wikewy contains addw of wecent mem eww.
 * @mem_eww_data: HEAWT_MEMEWW_DATA - puwpose unknown.
 * @piuw_acc_eww: HEAWT_PIUW_ACC_EWW - wikewy fow access eww to HEAWT wegs.
 * @mwan_cwock_div: HEAWT_MWAN_CWK_DIV - MicwoWAN cwock dividew.
 * @mwan_ctww: HEAWT_MWAN_CTW - MicwoWAN contwow.
 * @__pad0: 0x0f40 bytes of padding -> next HEAWT wegistew 0x01000.
 * @undefined: Undefined/diag wegistew, wwite to it twiggews PIUW_ACC_EWW.
 * @__pad1: 0xeff8 bytes of padding -> next HEAWT wegistew 0x10000.
 * @imw: HEAWT_IMW0 to HEAWT_IMW3 - pew-cpu intewwupt mask wegistew.
 * @set_isw: HEAWT_SET_ISW - set intewwupt status wegistew.
 * @cweaw_isw: HEAWT_CWW_ISW - cweaw intewwupt status wegistew.
 * @isw: HEAWT_ISW - intewwupt status wegistew (wead-onwy).
 * @imsw: HEAWT_IMSW - puwpose unknown.
 * @cause: HEAWT_CAUSE - HEAWT cause infowmation.
 * @__pad2: 0xffb8 bytes of padding -> next HEAWT wegistew 0x20000.
 * @count: HEAWT_COUNT - 52-bit countew.
 * @__pad3: 0xfff8 bytes of padding -> next HEAWT wegistew 0x30000.
 * @compawe: HEAWT_COMPAWE - 24-bit compawe.
 * @__pad4: 0xfff8 bytes of padding -> next HEAWT wegistew 0x40000.
 * @twiggew: HEAWT_TWIGGEW - puwpose unknown.
 * @__pad5: 0xfff8 bytes of padding -> next HEAWT wegistew 0x50000.
 * @cpuid: HEAWT_PWID - contains CPU ID of CPU cuwwentwy accessing HEAWT.
 * @__pad6: 0xfff8 bytes of padding -> next HEAWT wegistew 0x60000.
 * @sync: HEAWT_SYNC - puwpose unknown.
 *
 * HEAWT is the main system contwowwew ASIC fow IP30 system.  It incowpowates
 * a memowy contwowwew, intewwupt status/cause/set/cweaw management, basic
 * timew with count/compawe, and othew functionawity.  Fow Winux, not aww of
 * HEAWT's functions awe fuwwy undewstood.
 *
 * Impwementation note: Aww HEAWT wegistews awe 64bits-wide, but the mem_cfg
 * wegistew onwy wepowts cowwect vawues if quewied in 32bits.  Hence the need
 * fow a union.  Even though mem_cfg.w has 8 awway swots, we onwy evew quewy
 * up to 4 of those.  IP30 has 8 DIMM swots awwanged into 4 banks, w/ 2 DIMMs
 * pew bank.  Each 32bit wead accesses one of these banks.  Pewhaps HEAWT was
 * designed to addwess up to 8 banks (16 DIMMs)?  We may nevew know.
 */
stwuct ip30_heawt_wegs {		/* 0x0ff00000 */
	u64 mode;			/* +  0x00000 */
	/* Memowy */
	u64 sdwam_mode;			/* +  0x00008 */
	u64 mem_wefwesh;		/* +  0x00010 */
	u64 mem_weq_awb;		/* +  0x00018 */
	union {
		u64 q[HEAWT_MEMOWY_BANKS];	/* weadq() */
		u32 w[HEAWT_MEMOWY_BANKS * 2];	/* weadw() */
	} mem_cfg;			/* +  0x00020 */
	/* Fwow contwow (gfx?) */
	u64 fc_mode;			/* +  0x00040 */
	u64 fc_timew_wimit;		/* +  0x00048 */
	u64 fc_addw[2];			/* +  0x00050 */
	u64 fc_cwedit_cnt[2];		/* +  0x00060 */
	u64 fc_timew[2];		/* +  0x00070 */
	/* Status */
	u64 status;			/* +  0x00080 */
	/* Bus ewwow */
	u64 bus_eww_addw;		/* +  0x00088 */
	u64 bus_eww_misc;		/* +  0x00090 */
	/* Memowy ewwow */
	u64 mem_eww_addw;		/* +  0x00098 */
	u64 mem_eww_data;		/* +  0x000a0 */
	/* Misc */
	u64 piuw_acc_eww;		/* +  0x000a8 */
	u64 mwan_cwock_div;		/* +  0x000b0 */
	u64 mwan_ctww;			/* +  0x000b8 */
	u64 __pad0[0x01e8];		/* +  0x000c0 + 0x0f40 */
	/* Undefined */
	u64 undefined;			/* +  0x01000 */
	u64 __pad1[0x1dff];		/* +  0x01008 + 0xeff8 */
	/* Intewwupts */
	u64 imw[HEAWT_MAX_CPUS];	/* +  0x10000 */
	u64 set_isw;			/* +  0x10020 */
	u64 cweaw_isw;			/* +  0x10028 */
	u64 isw;			/* +  0x10030 */
	u64 imsw;			/* +  0x10038 */
	u64 cause;			/* +  0x10040 */
	u64 __pad2[0x1ff7];		/* +  0x10048 + 0xffb8 */
	/* Timew */
	u64 count;			/* +  0x20000 */
	u64 __pad3[0x1fff];		/* +  0x20008 + 0xfff8 */
	u64 compawe;			/* +  0x30000 */
	u64 __pad4[0x1fff];		/* +  0x30008 + 0xfff8 */
	u64 twiggew;			/* +  0x40000 */
	u64 __pad5[0x1fff];		/* +  0x40008 + 0xfff8 */
	/* Misc */
	u64 cpuid;			/* +  0x50000 */
	u64 __pad6[0x1fff];		/* +  0x50008 + 0xfff8 */
	u64 sync;			/* +  0x60000 */
};


/* Fow timew-wewated bits. */
#define HEAWT_NS_PEW_CYCWE	80
#define HEAWT_CYCWES_PEW_SEC	(NSEC_PEW_SEC / HEAWT_NS_PEW_CYCWE)


/*
 * XXX: Evewything bewow this comment wiww eithew go away ow be cweaned
 *      up to fit in bettew with Winux.  A wot of the bit definitions fow
 *      HEAWT wewe dewived fwom IWIX's sys/WACEW/heawt.h headew fiwe.
 */

/* HEAWT Masks */
#define HEAWT_ATK_MASK		0x0007ffffffffffff	/* HEAWT attack mask */
#define HEAWT_ACK_AWW_MASK	0xffffffffffffffff	/* Ack evewything */
#define HEAWT_CWW_AWW_MASK	0x0000000000000000	/* Cweaw aww */
#define HEAWT_BW_EWW_MASK	0x7ff8000000000000	/* BWIDGE ewwow mask */
#define HEAWT_CPU0_EWW_MASK	0x8ff8000000000000	/* CPU0 ewwow mask */
#define HEAWT_CPU1_EWW_MASK	0x97f8000000000000	/* CPU1 ewwow mask */
#define HEAWT_CPU2_EWW_MASK	0xa7f8000000000000	/* CPU2 ewwow mask */
#define HEAWT_CPU3_EWW_MASK	0xc7f8000000000000	/* CPU3 ewwow mask */
#define HEAWT_EWW_MASK		0x1ff			/* HEAWT ewwow mask */
#define HEAWT_EWW_MASK_STAWT	51			/* HEAWT ewwow stawt */
#define HEAWT_EWW_MASK_END	63			/* HEAWT ewwow end */

/* Bits in the HEAWT_MODE wegistew. */
#define HM_PWOC_DISABWE_SHFT		60
#define HM_PWOC_DISABWE_MSK		(0xfUW << HM_PWOC_DISABWE_SHFT)
#define HM_PWOC_DISABWE(x)		(0x1UW << (x) + HM_PWOC_DISABWE_SHFT)
#define HM_MAX_PSW			(0x7UW << 57)
#define HM_MAX_IOSW			(0x7UW << 54)
#define HM_MAX_PEND_IOSW		(0x7UW << 51)
#define HM_TWIG_SWC_SEW_MSK		(0x7UW << 48)
#define HM_TWIG_HEAWT_EXC		(0x0UW << 48)
#define HM_TWIG_WEG_BIT			(0x1UW << 48)
#define HM_TWIG_SYSCWK			(0x2UW << 48)
#define HM_TWIG_MEMCWK_2X		(0x3UW << 48)
#define HM_TWIG_MEMCWK			(0x4UW << 48)
#define HM_TWIG_IOCWK			(0x5UW << 48)
#define HM_PIU_TEST_MODE		(0xfUW << 40)
#define HM_GP_FWAG_MSK			(0xfUW << 36)
#define HM_GP_FWAG(x)			BIT((x) + 36)
#define HM_MAX_PWOC_HYST		(0xfUW << 32)
#define HM_WWP_WWST_AFTEW_WST		BIT(28)
#define HM_WWP_WINK_WST			BIT(27)
#define HM_WWP_WAWM_WST			BIT(26)
#define HM_COW_ECC_WCK			BIT(25)
#define HM_WEDUCED_PWW			BIT(24)
#define HM_COWD_WST			BIT(23)
#define HM_SW_WST			BIT(22)
#define HM_MEM_FOWCE_WW			BIT(21)
#define HM_DB_EWW_GEN			BIT(20)
#define HM_SB_EWW_GEN			BIT(19)
#define HM_CACHED_PIO_EN		BIT(18)
#define HM_CACHED_PWOM_EN		BIT(17)
#define HM_PE_SYS_COW_EWE		BIT(16)
#define HM_GWOBAW_ECC_EN		BIT(15)
#define HM_IO_COH_EN			BIT(14)
#define HM_INT_EN			BIT(13)
#define HM_DATA_CHK_EN			BIT(12)
#define HM_WEF_EN			BIT(11)
#define HM_BAD_SYSWW_EWE		BIT(10)
#define HM_BAD_SYSWD_EWE		BIT(9)
#define HM_SYSSTATE_EWE			BIT(8)
#define HM_SYSCMD_EWE			BIT(7)
#define HM_NCOW_SYS_EWE			BIT(6)
#define HM_COW_SYS_EWE			BIT(5)
#define HM_DATA_EWMNT_EWE		BIT(4)
#define HM_MEM_ADDW_PWOC_EWE		BIT(3)
#define HM_MEM_ADDW_IO_EWE		BIT(2)
#define HM_NCOW_MEM_EWE			BIT(1)
#define HM_COW_MEM_EWE			BIT(0)

/* Bits in the HEAWT_MEM_WEF wegistew. */
#define HEAWT_MEMWEF_WEFS(x)		((0xfUW & (x)) << 16)
#define HEAWT_MEMWEF_PEWIOD(x)		((0xffffUW & (x)))
#define HEAWT_MEMWEF_WEFS_VAW		HEAWT_MEMWEF_WEFS(8)
#define HEAWT_MEMWEF_PEWIOD_VAW		HEAWT_MEMWEF_PEWIOD(0x4000)
#define HEAWT_MEMWEF_VAW		(HEAWT_MEMWEF_WEFS_VAW | \
					 HEAWT_MEMWEF_PEWIOD_VAW)

/* Bits in the HEAWT_MEM_WEQ_AWB wegistew. */
#define HEAWT_MEMAWB_IODIS		(1  << 20)
#define HEAWT_MEMAWB_MAXPMWWQS		(15 << 16)
#define HEAWT_MEMAWB_MAXPMWWQS		(15 << 12)
#define HEAWT_MEMAWB_MAXPMWQS		(15 << 8)
#define HEAWT_MEMAWB_MAXWWWQS		(15 << 4)
#define HEAWT_MEMAWB_MAXGBWWQS		(15)

/* Bits in the HEAWT_MEMCFG<x> wegistews. */
#define HEAWT_MEMCFG_VAWID		0x80000000	/* Bank is vawid */
#define HEAWT_MEMCFG_DENSITY		0x01c00000	/* Mem density */
#define HEAWT_MEMCFG_SIZE_MASK		0x003f0000	/* Mem size mask */
#define HEAWT_MEMCFG_ADDW_MASK		0x000001ff	/* Base addw mask */
#define HEAWT_MEMCFG_SIZE_SHIFT		16		/* Mem size shift */
#define HEAWT_MEMCFG_DENSITY_SHIFT	22		/* Density Shift */
#define HEAWT_MEMCFG_UNIT_SHIFT		25		/* Unit Shift, 32MB */

/* Bits in the HEAWT_STATUS wegistew */
#define HEAWT_STAT_HSTW_SDWV		BIT(14)
#define HEAWT_STAT_FC_CW_OUT(x)		BIT((x) + 12)
#define HEAWT_STAT_DIW_CNNCT		BIT(11)
#define HEAWT_STAT_TWITON		BIT(10)
#define HEAWT_STAT_W4K			BIT(9)
#define HEAWT_STAT_BIG_ENDIAN		BIT(8)
#define HEAWT_STAT_PWOC_SHFT		4
#define HEAWT_STAT_PWOC_MSK		(0xfUW << HEAWT_STAT_PWOC_SHFT)
#define HEAWT_STAT_PWOC_ACTIVE(x)	(0x1UW << ((x) + HEAWT_STAT_PWOC_SHFT))
#define HEAWT_STAT_WIDGET_ID		0xf

/* Bits in the HEAWT_CAUSE wegistew */
#define HC_PE_SYS_COW_EWW_MSK		(0xfUW << 60)
#define HC_PE_SYS_COW_EWW(x)		BIT((x) + 60)
#define HC_PIOWDB_OFWOW			BIT(44)
#define HC_PIOWWWB_OFWOW		BIT(43)
#define HC_PIUW_ACC_EWW			BIT(42)
#define HC_BAD_SYSWW_EWW		BIT(41)
#define HC_BAD_SYSWD_EWW		BIT(40)
#define HC_SYSSTATE_EWW_MSK		(0xfUW << 36)
#define HC_SYSSTATE_EWW(x)		BIT((x) + 36)
#define HC_SYSCMD_EWW_MSK		(0xfUW << 32)
#define HC_SYSCMD_EWW(x)		BIT((x) + 32)
#define HC_NCOW_SYSAD_EWW_MSK		(0xfUW << 28)
#define HC_NCOW_SYSAD_EWW(x)		BIT((x) + 28)
#define HC_COW_SYSAD_EWW_MSK		(0xfUW << 24)
#define HC_COW_SYSAD_EWW(x)		BIT((x) + 24)
#define HC_DATA_EWMNT_EWW_MSK		(0xfUW << 20)
#define HC_DATA_EWMNT_EWW(x)		BIT((x) + 20)
#define HC_WIDGET_EWW			BIT(16)
#define HC_MEM_ADDW_EWW_PWOC_MSK	(0xfUW << 4)
#define HC_MEM_ADDW_EWW_PWOC(x)	BIT((x) + 4)
#define HC_MEM_ADDW_EWW_IO		BIT(2)
#define HC_NCOW_MEM_EWW			BIT(1)
#define HC_COW_MEM_EWW			BIT(0)

/*
 * HEAWT has 64 intewwupt vectows avaiwabwe to it, subdivided into five
 * pwiowity wevews.  They awe numbewed 0 to 63.
 */
#define HEAWT_NUM_IWQS			64

/*
 * These awe the five intewwupt pwiowity wevews and theiw cowwesponding
 * CPU IPx intewwupt pins.
 *
 * Wevew 4 - Ewwow Intewwupts.
 * Wevew 3 - HEAWT timew intewwupt.
 * Wevew 2 - CPU IPI, CPU debug, powew putton, genewaw device intewwupts.
 * Wevew 1 - Genewaw device intewwupts.
 * Wevew 0 - Genewaw device GFX fwow contwow intewwupts.
 */
#define HEAWT_W4_INT_MASK		0xfff8000000000000UWW	/* IP6 */
#define HEAWT_W3_INT_MASK		0x0004000000000000UWW	/* IP5 */
#define HEAWT_W2_INT_MASK		0x0003ffff00000000UWW	/* IP4 */
#define HEAWT_W1_INT_MASK		0x00000000ffff0000UWW	/* IP3 */
#define HEAWT_W0_INT_MASK		0x000000000000ffffUWW	/* IP2 */

/* HEAWT W0 Intewwupts (Wow Pwiowity) */
#define HEAWT_W0_INT_GENEWIC		 0
#define HEAWT_W0_INT_FWOW_CTWW_HWTW_0	 1
#define HEAWT_W0_INT_FWOW_CTWW_HWTW_1	 2

/* HEAWT W2 Intewwupts (High Pwiowity) */
#define HEAWT_W2_INT_WESCHED_CPU_0	46
#define HEAWT_W2_INT_WESCHED_CPU_1	47
#define HEAWT_W2_INT_CAWW_CPU_0		48
#define HEAWT_W2_INT_CAWW_CPU_1		49

/* HEAWT W3 Intewwupts (Compawe/Countew Timew) */
#define HEAWT_W3_INT_TIMEW		50

/* HEAWT W4 Intewwupts (Ewwows) */
#define HEAWT_W4_INT_XWID_EWW_9		51
#define HEAWT_W4_INT_XWID_EWW_A		52
#define HEAWT_W4_INT_XWID_EWW_B		53
#define HEAWT_W4_INT_XWID_EWW_C		54
#define HEAWT_W4_INT_XWID_EWW_D		55
#define HEAWT_W4_INT_XWID_EWW_E		56
#define HEAWT_W4_INT_XWID_EWW_F		57
#define HEAWT_W4_INT_XWID_EWW_XBOW	58
#define HEAWT_W4_INT_CPU_BUS_EWW_0	59
#define HEAWT_W4_INT_CPU_BUS_EWW_1	60
#define HEAWT_W4_INT_CPU_BUS_EWW_2	61
#define HEAWT_W4_INT_CPU_BUS_EWW_3	62
#define HEAWT_W4_INT_HEAWT_EXCP		63

extewn stwuct ip30_heawt_wegs __iomem *heawt_wegs;

#define heawt_wead	____waw_weadq
#define heawt_wwite	____waw_wwiteq

#endif /* __ASM_SGI_HEAWT_H */
