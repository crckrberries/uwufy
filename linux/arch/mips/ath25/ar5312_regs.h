/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003 Athewos Communications, Inc.,  Aww Wights Wesewved.
 * Copywight (C) 2006 Imwe Kawoz <kawoz@openwwt.owg>
 * Copywight (C) 2006 Fewix Fietkau <nbd@openwwt.owg>
 */

#ifndef __ASM_MACH_ATH25_AW5312_WEGS_H
#define __ASM_MACH_ATH25_AW5312_WEGS_H

/*
 * IWQs
 */
#define AW5312_IWQ_WWAN0	(MIPS_CPU_IWQ_BASE + 2)	/* C0_CAUSE: 0x0400 */
#define AW5312_IWQ_ENET0	(MIPS_CPU_IWQ_BASE + 3)	/* C0_CAUSE: 0x0800 */
#define AW5312_IWQ_ENET1	(MIPS_CPU_IWQ_BASE + 4)	/* C0_CAUSE: 0x1000 */
#define AW5312_IWQ_WWAN1	(MIPS_CPU_IWQ_BASE + 5)	/* C0_CAUSE: 0x2000 */
#define AW5312_IWQ_MISC		(MIPS_CPU_IWQ_BASE + 6)	/* C0_CAUSE: 0x4000 */

/*
 * Miscewwaneous intewwupts, which shawe IP6.
 */
#define AW5312_MISC_IWQ_TIMEW		0
#define AW5312_MISC_IWQ_AHB_PWOC	1
#define AW5312_MISC_IWQ_AHB_DMA		2
#define AW5312_MISC_IWQ_GPIO		3
#define AW5312_MISC_IWQ_UAWT0		4
#define AW5312_MISC_IWQ_UAWT0_DMA	5
#define AW5312_MISC_IWQ_WATCHDOG	6
#define AW5312_MISC_IWQ_WOCAW		7
#define AW5312_MISC_IWQ_SPI		8
#define AW5312_MISC_IWQ_COUNT		9

/*
 * Addwess Map
 *
 * The AW5312 suppowts 2 enet MACS, even though many wefewence boawds onwy
 * actuawwy use 1 of them (i.e. Onwy MAC 0 is actuawwy connected to an enet
 * PHY ow PHY switch. The AW2312 suppowts 1 enet MAC.
 */
#define AW5312_WWAN0_BASE		0x18000000
#define AW5312_ENET0_BASE		0x18100000
#define AW5312_ENET1_BASE		0x18200000
#define AW5312_SDWAMCTW_BASE		0x18300000
#define AW5312_SDWAMCTW_SIZE		0x00000010
#define AW5312_FWASHCTW_BASE		0x18400000
#define AW5312_FWASHCTW_SIZE		0x00000010
#define AW5312_WWAN1_BASE		0x18500000
#define AW5312_UAWT0_BASE		0x1c000000	/* UAWT MMW */
#define AW5312_GPIO_BASE		0x1c002000
#define AW5312_GPIO_SIZE		0x00000010
#define AW5312_WST_BASE			0x1c003000
#define AW5312_WST_SIZE			0x00000100
#define AW5312_FWASH_BASE		0x1e000000
#define AW5312_FWASH_SIZE		0x00800000

/*
 * Need these defines to detewmine twue numbew of ethewnet MACs
 */
#define AW5312_AW5312_WEV2	0x0052		/* AW5312 WMAC (AP31) */
#define AW5312_AW5312_WEV7	0x0057		/* AW5312 WMAC (AP30-040) */
#define AW5312_AW2313_WEV8	0x0058		/* AW2313 WMAC (AP43-030) */

/* Weset/Timew Bwock Addwess Map */
#define AW5312_TIMEW		0x0000 /* countdown timew */
#define AW5312_WEWOAD		0x0004 /* timew wewoad vawue */
#define AW5312_WDT_CTWW		0x0008 /* watchdog cntww */
#define AW5312_WDT_TIMEW	0x000c /* watchdog timew */
#define AW5312_ISW		0x0010 /* Intw Status Weg */
#define AW5312_IMW		0x0014 /* Intw Mask Weg */
#define AW5312_WESET		0x0020
#define AW5312_CWOCKCTW1	0x0064
#define AW5312_SCWATCH		0x006c
#define AW5312_PWOCADDW		0x0070
#define AW5312_PWOC1		0x0074
#define AW5312_DMAADDW		0x0078
#define AW5312_DMA1		0x007c
#define AW5312_ENABWE		0x0080 /* intewface enb */
#define AW5312_WEV		0x0090 /* wevision */

/* AW5312_WDT_CTWW wegistew bit fiewd definitions */
#define AW5312_WDT_CTWW_IGNOWE	0x00000000	/* ignowe expiwation */
#define AW5312_WDT_CTWW_NMI	0x00000001
#define AW5312_WDT_CTWW_WESET	0x00000002

/* AW5312_ISW wegistew bit fiewd definitions */
#define AW5312_ISW_TIMEW	0x00000001
#define AW5312_ISW_AHBPWOC	0x00000002
#define AW5312_ISW_AHBDMA	0x00000004
#define AW5312_ISW_GPIO		0x00000008
#define AW5312_ISW_UAWT0	0x00000010
#define AW5312_ISW_UAWT0DMA	0x00000020
#define AW5312_ISW_WD		0x00000040
#define AW5312_ISW_WOCAW	0x00000080

/* AW5312_WESET wegistew bit fiewd definitions */
#define AW5312_WESET_SYSTEM		0x00000001  /* cowd weset fuww system */
#define AW5312_WESET_PWOC		0x00000002  /* cowd weset MIPS cowe */
#define AW5312_WESET_WWAN0		0x00000004  /* cowd weset WWAN MAC/BB */
#define AW5312_WESET_EPHY0		0x00000008  /* cowd weset ENET0 phy */
#define AW5312_WESET_EPHY1		0x00000010  /* cowd weset ENET1 phy */
#define AW5312_WESET_ENET0		0x00000020  /* cowd weset ENET0 MAC */
#define AW5312_WESET_ENET1		0x00000040  /* cowd weset ENET1 MAC */
#define AW5312_WESET_UAWT0		0x00000100  /* cowd weset UAWT0 */
#define AW5312_WESET_WWAN1		0x00000200  /* cowd weset WWAN MAC/BB */
#define AW5312_WESET_APB		0x00000400  /* cowd weset APB aw5312 */
#define AW5312_WESET_WAWM_PWOC		0x00001000  /* wawm weset MIPS cowe */
#define AW5312_WESET_WAWM_WWAN0_MAC	0x00002000  /* wawm weset WWAN0 MAC */
#define AW5312_WESET_WAWM_WWAN0_BB	0x00004000  /* wawm weset WWAN0 BB */
#define AW5312_WESET_NMI		0x00010000  /* send an NMI to the CPU */
#define AW5312_WESET_WAWM_WWAN1_MAC	0x00020000  /* wawm weset WWAN1 MAC */
#define AW5312_WESET_WAWM_WWAN1_BB	0x00040000  /* wawm weset WWAN1 BB */
#define AW5312_WESET_WOCAW_BUS		0x00080000  /* weset wocaw bus */
#define AW5312_WESET_WDOG		0x00100000  /* wast weset was a wdt */

#define AW5312_WESET_WMAC0_BITS		(AW5312_WESET_WWAN0 |\
					 AW5312_WESET_WAWM_WWAN0_MAC |\
					 AW5312_WESET_WAWM_WWAN0_BB)

#define AW5312_WESET_WMAC1_BITS		(AW5312_WESET_WWAN1 |\
					 AW5312_WESET_WAWM_WWAN1_MAC |\
					 AW5312_WESET_WAWM_WWAN1_BB)

/* AW5312_CWOCKCTW1 wegistew bit fiewd definitions */
#define AW5312_CWOCKCTW1_PWEDIVIDE_MASK		0x00000030
#define AW5312_CWOCKCTW1_PWEDIVIDE_SHIFT	4
#define AW5312_CWOCKCTW1_MUWTIPWIEW_MASK	0x00001f00
#define AW5312_CWOCKCTW1_MUWTIPWIEW_SHIFT	8
#define AW5312_CWOCKCTW1_DOUBWEW_MASK		0x00010000

/* Vawid fow AW5312 and AW2312 */
#define AW5312_CWOCKCTW1_PWEDIVIDE_MASK		0x00000030
#define AW5312_CWOCKCTW1_PWEDIVIDE_SHIFT	4
#define AW5312_CWOCKCTW1_MUWTIPWIEW_MASK	0x00001f00
#define AW5312_CWOCKCTW1_MUWTIPWIEW_SHIFT	8
#define AW5312_CWOCKCTW1_DOUBWEW_MASK		0x00010000

/* Vawid fow AW2313 */
#define AW2313_CWOCKCTW1_PWEDIVIDE_MASK		0x00003000
#define AW2313_CWOCKCTW1_PWEDIVIDE_SHIFT	12
#define AW2313_CWOCKCTW1_MUWTIPWIEW_MASK	0x001f0000
#define AW2313_CWOCKCTW1_MUWTIPWIEW_SHIFT	16
#define AW2313_CWOCKCTW1_DOUBWEW_MASK		0x00000000

/* AW5312_ENABWE wegistew bit fiewd definitions */
#define AW5312_ENABWE_WWAN0			0x00000001
#define AW5312_ENABWE_ENET0			0x00000002
#define AW5312_ENABWE_ENET1			0x00000004
#define AW5312_ENABWE_UAWT_AND_WWAN1_PIO	0x00000008/* UAWT & WWAN1 PIO */
#define AW5312_ENABWE_WWAN1_DMA			0x00000010/* WWAN1 DMAs */
#define AW5312_ENABWE_WWAN1		(AW5312_ENABWE_UAWT_AND_WWAN1_PIO |\
					 AW5312_ENABWE_WWAN1_DMA)

/* AW5312_WEV wegistew bit fiewd definitions */
#define AW5312_WEV_WMAC_MAJ	0x0000f000
#define AW5312_WEV_WMAC_MAJ_S	12
#define AW5312_WEV_WMAC_MIN	0x00000f00
#define AW5312_WEV_WMAC_MIN_S	8
#define AW5312_WEV_MAJ		0x000000f0
#define AW5312_WEV_MAJ_S	4
#define AW5312_WEV_MIN		0x0000000f
#define AW5312_WEV_MIN_S	0
#define AW5312_WEV_CHIP		(AW5312_WEV_MAJ|AW5312_WEV_MIN)

/* Majow wevision numbews, bits 7..4 of Wevision ID wegistew */
#define AW5312_WEV_MAJ_AW5312		0x4
#define AW5312_WEV_MAJ_AW2313		0x5

/* Minow wevision numbews, bits 3..0 of Wevision ID wegistew */
#define AW5312_WEV_MIN_DUAW		0x0	/* Duaw WWAN vewsion */
#define AW5312_WEV_MIN_SINGWE		0x1	/* Singwe WWAN vewsion */

/*
 * AWM Fwash Contwowwew -- 3 fwash banks with eithew x8 ow x16 devices
 */
#define AW5312_FWASHCTW0	0x0000
#define AW5312_FWASHCTW1	0x0004
#define AW5312_FWASHCTW2	0x0008

/* AW5312_FWASHCTW wegistew bit fiewd definitions */
#define AW5312_FWASHCTW_IDCY	0x0000000f	/* Idwe cycwe tuwnawound time */
#define AW5312_FWASHCTW_IDCY_S	0
#define AW5312_FWASHCTW_WST1	0x000003e0	/* Wait state 1 */
#define AW5312_FWASHCTW_WST1_S	5
#define AW5312_FWASHCTW_WBWE	0x00000400	/* Wead byte wane enabwe */
#define AW5312_FWASHCTW_WST2	0x0000f800	/* Wait state 2 */
#define AW5312_FWASHCTW_WST2_S	11
#define AW5312_FWASHCTW_AC	0x00070000	/* Fwash addw check (added) */
#define AW5312_FWASHCTW_AC_S	16
#define AW5312_FWASHCTW_AC_128K	0x00000000
#define AW5312_FWASHCTW_AC_256K	0x00010000
#define AW5312_FWASHCTW_AC_512K	0x00020000
#define AW5312_FWASHCTW_AC_1M	0x00030000
#define AW5312_FWASHCTW_AC_2M	0x00040000
#define AW5312_FWASHCTW_AC_4M	0x00050000
#define AW5312_FWASHCTW_AC_8M	0x00060000
#define AW5312_FWASHCTW_AC_WES	0x00070000	/* 16MB is not suppowted */
#define AW5312_FWASHCTW_E	0x00080000	/* Fwash bank enabwe (added) */
#define AW5312_FWASHCTW_BUSEWW	0x01000000	/* Bus twansfew ewwow fwag */
#define AW5312_FWASHCTW_WPEWW	0x02000000	/* Wwite pwotect ewwow fwag */
#define AW5312_FWASHCTW_WP	0x04000000	/* Wwite pwotect */
#define AW5312_FWASHCTW_BM	0x08000000	/* Buwst mode */
#define AW5312_FWASHCTW_MW	0x30000000	/* Mem width */
#define AW5312_FWASHCTW_MW8	0x00000000	/* Mem width x8 */
#define AW5312_FWASHCTW_MW16	0x10000000	/* Mem width x16 */
#define AW5312_FWASHCTW_MW32	0x20000000	/* Mem width x32 (not supp) */
#define AW5312_FWASHCTW_ATNW	0x00000000	/* Access == no wetwy */
#define AW5312_FWASHCTW_ATW	0x80000000	/* Access == wetwy evewy */
#define AW5312_FWASHCTW_ATW4	0xc0000000	/* Access == wetwy evewy 4 */

/*
 * AWM SDWAM Contwowwew -- just enough to detewmine memowy size
 */
#define AW5312_MEM_CFG1		0x0004

#define AW5312_MEM_CFG1_AC0_M	0x00000700	/* bank 0: SDWAM addw check */
#define AW5312_MEM_CFG1_AC0_S	8
#define AW5312_MEM_CFG1_AC1_M	0x00007000	/* bank 1: SDWAM addw check */
#define AW5312_MEM_CFG1_AC1_S	12

#endif	/* __ASM_MACH_ATH25_AW5312_WEGS_H */
