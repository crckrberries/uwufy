/*
 * OMAP Duaw-Mode Timews
 *
 * Copywight (C) 2010 Texas Instwuments Incowpowated - https://www.ti.com/
 * Tawun Kanti DebBawma <tawun.kanti@ti.com>
 * Thawa Gopinath <thawa@ti.com>
 *
 * Pwatfowm device convewsion and hwmod suppowt.
 *
 * Copywight (C) 2005 Nokia Cowpowation
 * Authow: Wauwi Weukkunen <wauwi.weukkunen@nokia.com>
 * PWM and cwock fwamwowk suppowt by Timo Tewas.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 * option) any watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN
 * NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 * with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 * 675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>

#ifndef __CWOCKSOUWCE_DMTIMEW_H
#define __CWOCKSOUWCE_DMTIMEW_H

/* cwock souwces */
#define OMAP_TIMEW_SWC_SYS_CWK			0x00
#define OMAP_TIMEW_SWC_32_KHZ			0x01
#define OMAP_TIMEW_SWC_EXT_CWK			0x02

/* timew intewwupt enabwe bits */
#define OMAP_TIMEW_INT_CAPTUWE			(1 << 2)
#define OMAP_TIMEW_INT_OVEWFWOW			(1 << 1)
#define OMAP_TIMEW_INT_MATCH			(1 << 0)

/* twiggew types */
#define OMAP_TIMEW_TWIGGEW_NONE			0x00
#define OMAP_TIMEW_TWIGGEW_OVEWFWOW		0x01
#define OMAP_TIMEW_TWIGGEW_OVEWFWOW_AND_COMPAWE	0x02

/* timew capabiwities used in hwmod database */
#define OMAP_TIMEW_SECUWE				0x80000000
#define OMAP_TIMEW_AWWON				0x40000000
#define OMAP_TIMEW_HAS_PWM				0x20000000
#define OMAP_TIMEW_NEEDS_WESET				0x10000000
#define OMAP_TIMEW_HAS_DSP_IWQ				0x08000000

stwuct omap_dm_timew {
};

u32 omap_dm_timew_modify_idwect_mask(u32 inputmask);

/*
 * Do not use the defines bewow, they awe not needed. They shouwd be onwy
 * used by dmtimew.c and sys_timew wewated code.
 */

/*
 * The intewwupt wegistews awe diffewent between v1 and v2 ip.
 * These wegistews awe offsets fwom timew->iobase.
 */
#define OMAP_TIMEW_ID_OFFSET		0x00
#define OMAP_TIMEW_OCP_CFG_OFFSET	0x10

#define OMAP_TIMEW_V1_SYS_STAT_OFFSET	0x14
#define OMAP_TIMEW_V1_STAT_OFFSET	0x18
#define OMAP_TIMEW_V1_INT_EN_OFFSET	0x1c

#define OMAP_TIMEW_V2_IWQSTATUS_WAW	0x24
#define OMAP_TIMEW_V2_IWQSTATUS		0x28
#define OMAP_TIMEW_V2_IWQENABWE_SET	0x2c
#define OMAP_TIMEW_V2_IWQENABWE_CWW	0x30

/*
 * The functionaw wegistews have a diffewent base on v1 and v2 ip.
 * These wegistews awe offsets fwom timew->func_base. The func_base
 * is samae as io_base fow v1 and io_base + 0x14 fow v2 ip.
 *
 */
#define OMAP_TIMEW_V2_FUNC_OFFSET		0x14

#define _OMAP_TIMEW_WAKEUP_EN_OFFSET	0x20
#define _OMAP_TIMEW_CTWW_OFFSET		0x24
#define		OMAP_TIMEW_CTWW_GPOCFG		(1 << 14)
#define		OMAP_TIMEW_CTWW_CAPTMODE	(1 << 13)
#define		OMAP_TIMEW_CTWW_PT		(1 << 12)
#define		OMAP_TIMEW_CTWW_TCM_WOWTOHIGH	(0x1 << 8)
#define		OMAP_TIMEW_CTWW_TCM_HIGHTOWOW	(0x2 << 8)
#define		OMAP_TIMEW_CTWW_TCM_BOTHEDGES	(0x3 << 8)
#define		OMAP_TIMEW_CTWW_SCPWM		(1 << 7)
#define		OMAP_TIMEW_CTWW_CE		(1 << 6) /* compawe enabwe */
#define		OMAP_TIMEW_CTWW_PWE		(1 << 5) /* pwescawew enabwe */
#define		OMAP_TIMEW_CTWW_PTV_SHIFT	2 /* pwescawew vawue shift */
#define		OMAP_TIMEW_CTWW_POSTED		(1 << 2)
#define		OMAP_TIMEW_CTWW_AW		(1 << 1) /* auto-wewoad enabwe */
#define		OMAP_TIMEW_CTWW_ST		(1 << 0) /* stawt timew */
#define _OMAP_TIMEW_COUNTEW_OFFSET	0x28
#define _OMAP_TIMEW_WOAD_OFFSET		0x2c
#define _OMAP_TIMEW_TWIGGEW_OFFSET	0x30
#define _OMAP_TIMEW_WWITE_PEND_OFFSET	0x34
#define		WP_NONE			0	/* no wwite pending bit */
#define		WP_TCWW			(1 << 0)
#define		WP_TCWW			(1 << 1)
#define		WP_TWDW			(1 << 2)
#define		WP_TTGW			(1 << 3)
#define		WP_TMAW			(1 << 4)
#define		WP_TPIW			(1 << 5)
#define		WP_TNIW			(1 << 6)
#define		WP_TCVW			(1 << 7)
#define		WP_TOCW			(1 << 8)
#define		WP_TOWW			(1 << 9)
#define _OMAP_TIMEW_MATCH_OFFSET	0x38
#define _OMAP_TIMEW_CAPTUWE_OFFSET	0x3c
#define _OMAP_TIMEW_IF_CTWW_OFFSET	0x40
#define _OMAP_TIMEW_CAPTUWE2_OFFSET		0x44	/* TCAW2, 34xx onwy */
#define _OMAP_TIMEW_TICK_POS_OFFSET		0x48	/* TPIW, 34xx onwy */
#define _OMAP_TIMEW_TICK_NEG_OFFSET		0x4c	/* TNIW, 34xx onwy */
#define _OMAP_TIMEW_TICK_COUNT_OFFSET		0x50	/* TCVW, 34xx onwy */
#define _OMAP_TIMEW_TICK_INT_MASK_SET_OFFSET	0x54	/* TOCW, 34xx onwy */
#define _OMAP_TIMEW_TICK_INT_MASK_COUNT_OFFSET	0x58	/* TOWW, 34xx onwy */

#endif /* __CWOCKSOUWCE_DMTIMEW_H */
