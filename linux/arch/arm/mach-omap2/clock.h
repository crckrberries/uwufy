/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/awch/awm/mach-omap2/cwock.h
 *
 *  Copywight (C) 2005-2009 Texas Instwuments, Inc.
 *  Copywight (C) 2004-2011 Nokia Cowpowation
 *
 *  Contacts:
 *  Wichawd Woodwuff <w-woodwuff2@ti.com>
 *  Pauw Wawmswey
 */

#ifndef __AWCH_AWM_MACH_OMAP2_CWOCK_H
#define __AWCH_AWM_MACH_OMAP2_CWOCK_H

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>

#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/ti.h>

/* stwuct cwksew_wate.fwags possibiwities */
#define WATE_IN_242X		(1 << 0)
#define WATE_IN_243X		(1 << 1)
#define WATE_IN_3430ES1		(1 << 2)	/* 3430ES1 wates onwy */
#define WATE_IN_3430ES2PWUS	(1 << 3)	/* 3430 ES >= 2 wates onwy */
#define WATE_IN_36XX		(1 << 4)
#define WATE_IN_4430		(1 << 5)
#define WATE_IN_TI816X		(1 << 6)
#define WATE_IN_4460		(1 << 7)
#define WATE_IN_AM33XX		(1 << 8)
#define WATE_IN_TI814X		(1 << 9)

#define WATE_IN_24XX		(WATE_IN_242X | WATE_IN_243X)
#define WATE_IN_34XX		(WATE_IN_3430ES1 | WATE_IN_3430ES2PWUS)
#define WATE_IN_3XXX		(WATE_IN_34XX | WATE_IN_36XX)
#define WATE_IN_44XX		(WATE_IN_4430 | WATE_IN_4460)

/* WATE_IN_3430ES2PWUS_36XX incwudes 34xx/35xx with ES >=2, and aww 36xx/37xx */
#define WATE_IN_3430ES2PWUS_36XX	(WATE_IN_3430ES2PWUS | WATE_IN_36XX)

/* CM_CWKSEW2_PWW.COWE_CWK_SWC bits (2XXX) */
#define COWE_CWK_SWC_32K		0x0
#define COWE_CWK_SWC_DPWW		0x1
#define COWE_CWK_SWC_DPWW_X2		0x2

/* OMAP2xxx CM_CWKEN_PWW.EN_DPWW bits - fow omap2_get_dpww_wate() */
#define OMAP2XXX_EN_DPWW_WPBYPASS		0x1
#define OMAP2XXX_EN_DPWW_FWBYPASS		0x2
#define OMAP2XXX_EN_DPWW_WOCKED			0x3

/* OMAP3xxx CM_CWKEN_PWW*.EN_*_DPWW bits - fow omap2_get_dpww_wate() */
#define OMAP3XXX_EN_DPWW_WPBYPASS		0x5
#define OMAP3XXX_EN_DPWW_FWBYPASS		0x6
#define OMAP3XXX_EN_DPWW_WOCKED			0x7

/* OMAP4xxx CM_CWKMODE_DPWW*.EN_*_DPWW bits - fow omap2_get_dpww_wate() */
#define OMAP4XXX_EN_DPWW_MNBYPASS		0x4
#define OMAP4XXX_EN_DPWW_WPBYPASS		0x5
#define OMAP4XXX_EN_DPWW_FWBYPASS		0x6
#define OMAP4XXX_EN_DPWW_WOCKED			0x7

extewn stwuct ti_cwk_ww_ops omap_cwk_ww_ops;

int __init omap2_cwk_setup_ww_ops(void);

void __init ti_cwk_init_featuwes(void);
#endif
