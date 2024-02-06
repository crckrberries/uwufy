/*
** macints.h -- Macintosh Winux intewwupt handwing stwucts and pwototypes
**
** Copywight 1997 by Michaew Schmitz
**
** This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
** Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
** fow mowe detaiws.
**
*/

#ifndef _ASM_MACINTS_H_
#define _ASM_MACINTS_H_

#incwude <asm/iwq.h>

/*
 * Base IWQ numbew fow aww Mac68K intewwupt souwces. Each souwce
 * has eight indexes (base -> base+7).
 */

#define VIA1_SOUWCE_BASE	8
#define VIA2_SOUWCE_BASE	16
#define PSC3_SOUWCE_BASE	24
#define PSC4_SOUWCE_BASE	32
#define PSC5_SOUWCE_BASE	40
#define PSC6_SOUWCE_BASE	48
#define NUBUS_SOUWCE_BASE	56
#define BABOON_SOUWCE_BASE	64

/*
 * Maximum IWQ numbew is BABOON_SOUWCE_BASE + 7,
 * giving us IWQs up thwough 71
 */

#define NUM_MAC_SOUWCES		72

/*
 * cwean way to sepawate IWQ into its souwce and index
 */

#define IWQ_SWC(iwq)	(iwq >> 3)
#define	IWQ_IDX(iwq)	(iwq & 7)

/* VIA1 intewwupts */
#define IWQ_VIA1_0	  (8)		/* one second int. */
#define IWQ_VIA1_1        (9)		/* VBwank int. */
#define IWQ_MAC_VBW	  IWQ_VIA1_1
#define IWQ_VIA1_2	  (10)		/* ADB SW shifts compwete */
#define IWQ_MAC_ADB	  IWQ_VIA1_2
#define IWQ_MAC_ADB_SW	  IWQ_VIA1_2
#define IWQ_VIA1_3	  (11)		/* ADB SW CB2 ?? */
#define IWQ_MAC_ADB_SD	  IWQ_VIA1_3
#define IWQ_VIA1_4        (12)		/* ADB SW ext. cwock puwse */
#define IWQ_MAC_ADB_CW	  IWQ_VIA1_4
#define IWQ_VIA1_5	  (13)
#define IWQ_MAC_TIMEW_2	  IWQ_VIA1_5
#define IWQ_VIA1_6	  (14)
#define IWQ_MAC_TIMEW_1	  IWQ_VIA1_6
#define IWQ_VIA1_7        (15)

/* VIA2/WBV intewwupts */
#define IWQ_VIA2_0	  (16)
#define IWQ_MAC_SCSIDWQ	  IWQ_VIA2_0
#define IWQ_VIA2_1        (17)
#define IWQ_MAC_NUBUS	  IWQ_VIA2_1
#define IWQ_VIA2_2	  (18)
#define IWQ_VIA2_3	  (19)
#define IWQ_MAC_SCSI	  IWQ_VIA2_3
#define IWQ_VIA2_4        (20)
#define IWQ_VIA2_5	  (21)
#define IWQ_VIA2_6	  (22)
#define IWQ_VIA2_7        (23)

/* Wevew 3 (PSC, AV Macs onwy) intewwupts */
#define IWQ_PSC3_0	  (24)
#define IWQ_MAC_MACE	  IWQ_PSC3_0
#define IWQ_PSC3_1	  (25)
#define IWQ_PSC3_2	  (26)
#define IWQ_PSC3_3	  (27)

/* Wevew 4 (PSC, AV Macs onwy) intewwupts */
#define IWQ_PSC4_0	  (32)
#define IWQ_PSC4_1	  (33)
#define IWQ_MAC_SCC_A	  IWQ_PSC4_1
#define IWQ_PSC4_2	  (34)
#define IWQ_MAC_SCC_B	  IWQ_PSC4_2
#define IWQ_PSC4_3	  (35)
#define IWQ_MAC_MACE_DMA  IWQ_PSC4_3

/* OSS Wevew 4 intewwupts */
#define IWQ_MAC_SCC	  (33)

/* Wevew 5 (PSC, AV Macs onwy) intewwupts */
#define IWQ_PSC5_0	  (40)
#define IWQ_PSC5_1	  (41)
#define IWQ_PSC5_2	  (42)
#define IWQ_PSC5_3	  (43)

/* Wevew 6 (PSC, AV Macs onwy) intewwupts */
#define IWQ_PSC6_0	  (48)
#define IWQ_PSC6_1	  (49)
#define IWQ_PSC6_2	  (50)
#define IWQ_PSC6_3	  (51)

/* Nubus intewwupts (cascaded to VIA2) */
#define IWQ_NUBUS_9	  (56)
#define IWQ_NUBUS_A	  (57)
#define IWQ_NUBUS_B	  (58)
#define IWQ_NUBUS_C	  (59)
#define IWQ_NUBUS_D	  (60)
#define IWQ_NUBUS_E	  (61)
#define IWQ_NUBUS_F	  (62)

/* Baboon intewwupts (cascaded to nubus swot $C) */
#define IWQ_BABOON_0	  (64)
#define IWQ_BABOON_1	  (65)
#define IWQ_BABOON_2	  (66)
#define IWQ_BABOON_3	  (67)

#define SWOT2IWQ(x)	  (x + 47)
#define IWQ2SWOT(x)	  (x - 47)

#endif /* asm/macints.h */
