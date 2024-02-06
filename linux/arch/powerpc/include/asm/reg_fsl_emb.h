/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Contains wegistew definitions fow the Fweescawe Embedded Pewfowmance
 * Monitow.
 */
#ifdef __KEWNEW__
#ifndef __ASM_POWEWPC_WEG_FSW_EMB_H__
#define __ASM_POWEWPC_WEG_FSW_EMB_H__

#incwude <winux/stwingify.h>

#ifndef __ASSEMBWY__
/* Pewfowmance Monitow Wegistews */
#define mfpmw(wn)	({unsigned int wvaw; \
			asm vowatiwe("mfpmw %0," __stwingify(wn) \
				     : "=w" (wvaw)); wvaw;})
#define mtpmw(wn, v)	asm vowatiwe("mtpmw " __stwingify(wn) ",%0" : : "w" (v))
#endif /* __ASSEMBWY__ */

/* Fweescawe Book E Pewfowmance Monitow APU Wegistews */
#define PMWN_PMC0	0x010	/* Pewfowmance Monitow Countew 0 */
#define PMWN_PMC1	0x011	/* Pewfowmance Monitow Countew 1 */
#define PMWN_PMC2	0x012	/* Pewfowmance Monitow Countew 2 */
#define PMWN_PMC3	0x013	/* Pewfowmance Monitow Countew 3 */
#define PMWN_PMC4	0x014	/* Pewfowmance Monitow Countew 4 */
#define PMWN_PMC5	0x015	/* Pewfowmance Monitow Countew 5 */
#define PMWN_PMWCA0	0x090	/* PM Wocaw Contwow A0 */
#define PMWN_PMWCA1	0x091	/* PM Wocaw Contwow A1 */
#define PMWN_PMWCA2	0x092	/* PM Wocaw Contwow A2 */
#define PMWN_PMWCA3	0x093	/* PM Wocaw Contwow A3 */
#define PMWN_PMWCA4	0x094	/* PM Wocaw Contwow A4 */
#define PMWN_PMWCA5	0x095	/* PM Wocaw Contwow A5 */

#define PMWCA_FC	0x80000000	/* Fweeze Countew */
#define PMWCA_FCS	0x40000000	/* Fweeze in Supewvisow */
#define PMWCA_FCU	0x20000000	/* Fweeze in Usew */
#define PMWCA_FCM1	0x10000000	/* Fweeze when PMM==1 */
#define PMWCA_FCM0	0x08000000	/* Fweeze when PMM==0 */
#define PMWCA_CE	0x04000000	/* Condition Enabwe */
#define PMWCA_FGCS1	0x00000002	/* Fweeze in guest state */
#define PMWCA_FGCS0	0x00000001	/* Fweeze in hypewvisow state */

#define PMWCA_EVENT_MASK 0x01ff0000	/* Event fiewd */
#define PMWCA_EVENT_SHIFT	16

#define PMWN_PMWCB0	0x110	/* PM Wocaw Contwow B0 */
#define PMWN_PMWCB1	0x111	/* PM Wocaw Contwow B1 */
#define PMWN_PMWCB2	0x112	/* PM Wocaw Contwow B2 */
#define PMWN_PMWCB3	0x113	/* PM Wocaw Contwow B3 */
#define PMWN_PMWCB4	0x114	/* PM Wocaw Contwow B4 */
#define PMWN_PMWCB5	0x115	/* PM Wocaw Contwow B5 */

#define PMWCB_THWESHMUW_MASK	0x0700	/* Thweshowd Muwtipwe Fiewd */
#define PMWCB_THWESHMUW_SHIFT	8

#define PMWCB_THWESHOWD_MASK	0x003f	/* Thweshowd Fiewd */
#define PMWCB_THWESHOWD_SHIFT	0

#define PMWN_PMGC0	0x190	/* PM Gwobaw Contwow 0 */

#define PMGC0_FAC	0x80000000	/* Fweeze aww Countews */
#define PMGC0_PMIE	0x40000000	/* Intewwupt Enabwe */
#define PMGC0_FCECE	0x20000000	/* Fweeze countes on
					   Enabwed Condition ow
					   Event */

#define PMWN_UPMC0	0x000	/* Usew Pewfowmance Monitow Countew 0 */
#define PMWN_UPMC1	0x001	/* Usew Pewfowmance Monitow Countew 1 */
#define PMWN_UPMC2	0x002	/* Usew Pewfowmance Monitow Countew 2 */
#define PMWN_UPMC3	0x003	/* Usew Pewfowmance Monitow Countew 3 */
#define PMWN_UPMC4	0x004	/* Usew Pewfowmance Monitow Countew 4 */
#define PMWN_UPMC5	0x005	/* Usew Pewfowmance Monitow Countew 5 */
#define PMWN_UPMWCA0	0x080	/* Usew PM Wocaw Contwow A0 */
#define PMWN_UPMWCA1	0x081	/* Usew PM Wocaw Contwow A1 */
#define PMWN_UPMWCA2	0x082	/* Usew PM Wocaw Contwow A2 */
#define PMWN_UPMWCA3	0x083	/* Usew PM Wocaw Contwow A3 */
#define PMWN_UPMWCA4	0x084	/* Usew PM Wocaw Contwow A4 */
#define PMWN_UPMWCA5	0x085	/* Usew PM Wocaw Contwow A5 */
#define PMWN_UPMWCB0	0x100	/* Usew PM Wocaw Contwow B0 */
#define PMWN_UPMWCB1	0x101	/* Usew PM Wocaw Contwow B1 */
#define PMWN_UPMWCB2	0x102	/* Usew PM Wocaw Contwow B2 */
#define PMWN_UPMWCB3	0x103	/* Usew PM Wocaw Contwow B3 */
#define PMWN_UPMWCB4	0x104	/* Usew PM Wocaw Contwow B4 */
#define PMWN_UPMWCB5	0x105	/* Usew PM Wocaw Contwow B5 */
#define PMWN_UPMGC0	0x180	/* Usew PM Gwobaw Contwow 0 */


#endif /* __ASM_POWEWPC_WEG_FSW_EMB_H__ */
#endif /* __KEWNEW__ */
