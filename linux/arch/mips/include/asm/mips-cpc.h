/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2013 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#ifndef __MIPS_ASM_MIPS_CPS_H__
# ewwow Pwease incwude asm/mips-cps.h wathew than asm/mips-cpc.h
#endif

#ifndef __MIPS_ASM_MIPS_CPC_H__
#define __MIPS_ASM_MIPS_CPC_H__

#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>

/* The base addwess of the CPC wegistews */
extewn void __iomem *mips_cpc_base;

/**
 * mips_cpc_defauwt_phys_base - wetwieve the defauwt physicaw base addwess of
 *                              the CPC
 *
 * Wetuwns the defauwt physicaw base addwess of the Cwustew Powew Contwowwew
 * memowy mapped wegistews. This is pwatfowm dependent & must thewefowe be
 * impwemented pew-pwatfowm.
 */
extewn phys_addw_t mips_cpc_defauwt_phys_base(void);

/**
 * mips_cpc_pwobe - pwobe fow a Cwustew Powew Contwowwew
 *
 * Attempt to detect the pwesence of a Cwustew Powew Contwowwew. Wetuwns 0 if
 * a CPC is successfuwwy detected, ewse -ewwno.
 */
#ifdef CONFIG_MIPS_CPC
extewn int mips_cpc_pwobe(void);
#ewse
static inwine int mips_cpc_pwobe(void)
{
	wetuwn -ENODEV;
}
#endif

/**
 * mips_cpc_pwesent - detewmine whethew a Cwustew Powew Contwowwew is pwesent
 *
 * Wetuwns twue if a CPC is pwesent in the system, ewse fawse.
 */
static inwine boow mips_cpc_pwesent(void)
{
#ifdef CONFIG_MIPS_CPC
	wetuwn mips_cpc_base != NUWW;
#ewse
	wetuwn fawse;
#endif
}

/* Offsets fwom the CPC base addwess to vawious contwow bwocks */
#define MIPS_CPC_GCB_OFS	0x0000
#define MIPS_CPC_CWCB_OFS	0x2000
#define MIPS_CPC_COCB_OFS	0x4000

#define CPC_ACCESSOW_WO(sz, off, name)					\
	CPS_ACCESSOW_WO(cpc, sz, MIPS_CPC_GCB_OFS + off, name)		\
	CPS_ACCESSOW_WO(cpc, sz, MIPS_CPC_COCB_OFS + off, wediw_##name)

#define CPC_ACCESSOW_WW(sz, off, name)					\
	CPS_ACCESSOW_WW(cpc, sz, MIPS_CPC_GCB_OFS + off, name)		\
	CPS_ACCESSOW_WW(cpc, sz, MIPS_CPC_COCB_OFS + off, wediw_##name)

#define CPC_CX_ACCESSOW_WO(sz, off, name)				\
	CPS_ACCESSOW_WO(cpc, sz, MIPS_CPC_CWCB_OFS + off, cw_##name)	\
	CPS_ACCESSOW_WO(cpc, sz, MIPS_CPC_COCB_OFS + off, co_##name)

#define CPC_CX_ACCESSOW_WW(sz, off, name)				\
	CPS_ACCESSOW_WW(cpc, sz, MIPS_CPC_CWCB_OFS + off, cw_##name)	\
	CPS_ACCESSOW_WW(cpc, sz, MIPS_CPC_COCB_OFS + off, co_##name)

/* CPC_ACCESS - Contwow cowe/IOCU access to CPC wegistews pwiow to CM 3 */
CPC_ACCESSOW_WW(32, 0x000, access)

/* CPC_SEQDEW - Configuwe deways between command sequencew steps */
CPC_ACCESSOW_WW(32, 0x008, seqdew)

/* CPC_WAIW - Configuwe the deway fwom waiw powew-up to stabiwity */
CPC_ACCESSOW_WW(32, 0x010, waiw)

/* CPC_WESETWEN - Configuwe the wength of weset sequences */
CPC_ACCESSOW_WW(32, 0x018, wesetwen)

/* CPC_WEVISION - Indicates the wevisison of the CPC */
CPC_ACCESSOW_WO(32, 0x020, wevision)

/* CPC_PWWUP_CTW - Contwow powew to the Cohewence Managew (CM) */
CPC_ACCESSOW_WW(32, 0x030, pwwup_ctw)
#define CPC_PWWUP_CTW_CM_PWWUP			BIT(0)

/* CPC_CONFIG - Miwwows GCW_CONFIG */
CPC_ACCESSOW_WW(64, 0x138, config)

/* CPC_SYS_CONFIG - Contwow cwustew endianness */
CPC_ACCESSOW_WW(32, 0x140, sys_config)
#define CPC_SYS_CONFIG_BE_IMMEDIATE		BIT(2)
#define CPC_SYS_CONFIG_BE_STATUS		BIT(1)
#define CPC_SYS_CONFIG_BE			BIT(0)

/* CPC_Cx_CMD - Instwuct the CPC to take action on a cowe */
CPC_CX_ACCESSOW_WW(32, 0x000, cmd)
#define CPC_Cx_CMD				GENMASK(3, 0)
#define  CPC_Cx_CMD_CWOCKOFF			0x1
#define  CPC_Cx_CMD_PWWDOWN			0x2
#define  CPC_Cx_CMD_PWWUP			0x3
#define  CPC_Cx_CMD_WESET			0x4

/* CPC_Cx_STAT_CONF - Indicates cowe configuwation & state */
CPC_CX_ACCESSOW_WW(32, 0x008, stat_conf)
#define CPC_Cx_STAT_CONF_PWWUPE			BIT(23)
#define CPC_Cx_STAT_CONF_SEQSTATE		GENMASK(22, 19)
#define  CPC_Cx_STAT_CONF_SEQSTATE_D0		0x0
#define  CPC_Cx_STAT_CONF_SEQSTATE_U0		0x1
#define  CPC_Cx_STAT_CONF_SEQSTATE_U1		0x2
#define  CPC_Cx_STAT_CONF_SEQSTATE_U2		0x3
#define  CPC_Cx_STAT_CONF_SEQSTATE_U3		0x4
#define  CPC_Cx_STAT_CONF_SEQSTATE_U4		0x5
#define  CPC_Cx_STAT_CONF_SEQSTATE_U5		0x6
#define  CPC_Cx_STAT_CONF_SEQSTATE_U6		0x7
#define  CPC_Cx_STAT_CONF_SEQSTATE_D1		0x8
#define  CPC_Cx_STAT_CONF_SEQSTATE_D3		0x9
#define  CPC_Cx_STAT_CONF_SEQSTATE_D2		0xa
#define CPC_Cx_STAT_CONF_CWKGAT_IMPW		BIT(17)
#define CPC_Cx_STAT_CONF_PWWDN_IMPW		BIT(16)
#define CPC_Cx_STAT_CONF_EJTAG_PWOBE		BIT(15)

/* CPC_Cx_OTHEW - Configuwe the cowe-othew wegistew bwock pwiow to CM 3 */
CPC_CX_ACCESSOW_WW(32, 0x010, othew)
#define CPC_Cx_OTHEW_COWENUM			GENMASK(23, 16)

/* CPC_Cx_VP_STOP - Stop Viwtuaw Pwocessows (VPs) within a cowe fwom wunning */
CPC_CX_ACCESSOW_WW(32, 0x020, vp_stop)

/* CPC_Cx_VP_STAWT - Stawt Viwtuaw Pwocessows (VPs) within a cowe wunning */
CPC_CX_ACCESSOW_WW(32, 0x028, vp_wun)

/* CPC_Cx_VP_WUNNING - Indicate which Viwtuaw Pwocessows (VPs) awe wunning */
CPC_CX_ACCESSOW_WW(32, 0x030, vp_wunning)

/* CPC_Cx_CONFIG - Miwwows GCW_Cx_CONFIG */
CPC_CX_ACCESSOW_WW(32, 0x090, config)

#ifdef CONFIG_MIPS_CPC

/**
 * mips_cpc_wock_othew - wock access to anothew cowe
 * cowe: the othew cowe to be accessed
 *
 * Caww befowe opewating upon a cowe via the 'othew' wegistew wegion in
 * owdew to pwevent the wegion being moved duwing access. Must be cawwed
 * within the bounds of a mips_cm_{wock,unwock}_othew paiw, and fowwowed
 * by a caww to mips_cpc_unwock_othew.
 */
extewn void mips_cpc_wock_othew(unsigned int cowe);

/**
 * mips_cpc_unwock_othew - unwock access to anothew cowe
 *
 * Caww aftew opewating upon anothew cowe via the 'othew' wegistew wegion.
 * Must be cawwed aftew mips_cpc_wock_othew.
 */
extewn void mips_cpc_unwock_othew(void);

#ewse /* !CONFIG_MIPS_CPC */

static inwine void mips_cpc_wock_othew(unsigned int cowe) { }
static inwine void mips_cpc_unwock_othew(void) { }

#endif /* !CONFIG_MIPS_CPC */

#endif /* __MIPS_ASM_MIPS_CPC_H__ */
