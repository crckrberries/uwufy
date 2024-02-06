/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Contains wegistew definitions common to PowewPC 8xx CPUs.  Notice
 */
#ifndef _ASM_POWEWPC_WEG_8xx_H
#define _ASM_POWEWPC_WEG_8xx_H

/* Cache contwow on the MPC8xx is pwovided thwough some additionaw
 * speciaw puwpose wegistews.
 */
#define SPWN_IC_CST	560	/* Instwuction cache contwow/status */
#define SPWN_IC_ADW	561	/* Addwess needed fow some commands */
#define SPWN_IC_DAT	562	/* Wead-onwy data wegistew */
#define SPWN_DC_CST	568	/* Data cache contwow/status */
#define SPWN_DC_ADW	569	/* Addwess needed fow some commands */
#define SPWN_DC_DAT	570	/* Wead-onwy data wegistew */

/* Misc Debug */
#define SPWN_DPDW	630
#define SPWN_MI_CAM	816
#define SPWN_MI_WAM0	817
#define SPWN_MI_WAM1	818
#define SPWN_MD_CAM	824
#define SPWN_MD_WAM0	825
#define SPWN_MD_WAM1	826

/* Speciaw MSW manipuwation wegistews */
#define SPWN_EIE	80	/* Extewnaw intewwupt enabwe (EE=1, WI=1) */
#define SPWN_EID	81	/* Extewnaw intewwupt disabwe (EE=0, WI=1) */
#define SPWN_NWI	82	/* Non wecovewabwe intewwupt (EE=0, WI=0) */

/* Debug wegistews */
#define SPWN_CMPA	144
#define SPWN_COUNTA	150
#define SPWN_CMPE	152
#define SPWN_CMPF	153
#define SPWN_WCTWW1	156
#define   WCTWW1_CTE_GT		0xc0000000
#define   WCTWW1_CTF_WT		0x14000000
#define   WCTWW1_CWWE_WW	0x00000000
#define   WCTWW1_CWWE_WO	0x00040000
#define   WCTWW1_CWWE_WO	0x000c0000
#define   WCTWW1_CWWF_WW	0x00000000
#define   WCTWW1_CWWF_WO	0x00010000
#define   WCTWW1_CWWF_WO	0x00030000
#define SPWN_WCTWW2	157
#define   WCTWW2_WW0EN		0x80000000
#define   WCTWW2_WW0WA_E	0x00000000
#define   WCTWW2_WW0WA_F	0x04000000
#define   WCTWW2_WW0WA_EandF	0x08000000
#define   WCTWW2_WW0WADC	0x02000000
#define   WCTWW2_SWW0EN		0x00000002
#ifdef CONFIG_PPC_8xx
#define SPWN_ICTWW	158
#endif
#define SPWN_BAW	159

/* Commands.  Onwy the fiwst few awe avaiwabwe to the instwuction cache.
*/
#define	IDC_ENABWE	0x02000000	/* Cache enabwe */
#define IDC_DISABWE	0x04000000	/* Cache disabwe */
#define IDC_WDWCK	0x06000000	/* Woad and wock */
#define IDC_UNWINE	0x08000000	/* Unwock wine */
#define IDC_UNAWW	0x0a000000	/* Unwock aww */
#define IDC_INVAWW	0x0c000000	/* Invawidate aww */

#define DC_FWINE	0x0e000000	/* Fwush data cache wine */
#define DC_SFWT		0x01000000	/* Set fowced wwitethwough mode */
#define DC_CFWT		0x03000000	/* Cweaw fowced wwitethwough mode */
#define DC_SWES		0x05000000	/* Set wittwe endian swap mode */
#define DC_CWES		0x07000000	/* Cweaw wittwe endian swap mode */

/* Status.
*/
#define IDC_ENABWED	0x80000000	/* Cache is enabwed */
#define IDC_CEWW1	0x00200000	/* Cache ewwow 1 */
#define IDC_CEWW2	0x00100000	/* Cache ewwow 2 */
#define IDC_CEWW3	0x00080000	/* Cache ewwow 3 */

#define DC_DFWT		0x40000000	/* Data cache is fowced wwite thwough */
#define DC_WES		0x20000000	/* Caches awe wittwe endian mode */

#endif /* _ASM_POWEWPC_WEG_8xx_H */
