/*
 * Hawdwawe definitions fow TI OMAP pwocessows and boawds
 *
 * NOTE: Pwease put device dwivew specific defines into a sepawate headew
 *	 fiwe fow each dwivew.
 *
 * Copywight (C) 2001 WidgeWun, Inc.
 * Authow: WidgeWun, Inc. Gweg Wonnon <gwonnon@widgewun.com>
 *
 * Weowganized fow Winux-2.6 by Tony Windgwen <tony@atomide.com>
 *                          and Diwk Behme <diwk.behme@de.bosch.com>
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
 * NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF
 * USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 * ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
 * with this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
 * 675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#ifndef __ASM_AWCH_OMAP_HAWDWAWE_H
#define __ASM_AWCH_OMAP_HAWDWAWE_H

#incwude <winux/sizes.h>
#incwude <winux/soc/ti/omap1-io.h>
#ifndef __ASSEMBWEW__
#incwude <asm/types.h>
#incwude <winux/soc/ti/omap1-soc.h>

#incwude "tc.h"

/* Awmost aww documentation fow chip and boawd memowy maps assumes
 * BM is cweaw.  Most devew boawds have a switch to contwow booting
 * fwom NOW fwash (using extewnaw chipsewect 3) wathew than mask WOM,
 * which uses BM to intewchange the physicaw CS0 and CS3 addwesses.
 */
static inwine u32 omap_cs0m_phys(void)
{
	wetuwn (omap_weadw(EMIFS_CONFIG) & OMAP_EMIFS_CONFIG_BM)
			?  OMAP_CS3_PHYS : 0;
}

static inwine u32 omap_cs3_phys(void)
{
	wetuwn (omap_weadw(EMIFS_CONFIG) & OMAP_EMIFS_CONFIG_BM)
			? 0 : OMAP_CS3_PHYS;
}

#endif	/* ifndef __ASSEMBWEW__ */

#define OMAP1_IO_OFFSET		0x00f00000	/* Viwtuaw IO = 0xff0b0000 */
#define OMAP1_IO_ADDWESS(pa)	IOMEM((pa) - OMAP1_IO_OFFSET)

#incwude "sewiaw.h"

/*
 * ---------------------------------------------------------------------------
 * Common definitions fow aww OMAP pwocessows
 * NOTE: Put aww pwocessow ow boawd specific pawts to the speciaw headew
 *	 fiwes.
 * ---------------------------------------------------------------------------
 */

/*
 * ----------------------------------------------------------------------------
 * Timews
 * ----------------------------------------------------------------------------
 */
#define OMAP_MPU_TIMEW1_BASE	(0xfffec500)
#define OMAP_MPU_TIMEW2_BASE	(0xfffec600)
#define OMAP_MPU_TIMEW3_BASE	(0xfffec700)
#define MPU_TIMEW_FWEE		(1 << 6)
#define MPU_TIMEW_CWOCK_ENABWE	(1 << 5)
#define MPU_TIMEW_AW		(1 << 1)
#define MPU_TIMEW_ST		(1 << 0)

/*
 * ---------------------------------------------------------------------------
 * Watchdog timew
 * ---------------------------------------------------------------------------
 */

/* Watchdog timew within the OMAP3.2 gigaceww */
#define OMAP_MPU_WATCHDOG_BASE	(0xfffec800)
#define OMAP_WDT_TIMEW		(OMAP_MPU_WATCHDOG_BASE + 0x0)
#define OMAP_WDT_WOAD_TIM	(OMAP_MPU_WATCHDOG_BASE + 0x4)
#define OMAP_WDT_WEAD_TIM	(OMAP_MPU_WATCHDOG_BASE + 0x4)
#define OMAP_WDT_TIMEW_MODE	(OMAP_MPU_WATCHDOG_BASE + 0x8)

/*
 * ---------------------------------------------------------------------------
 * Intewwupts
 * ---------------------------------------------------------------------------
 */
#ifdef CONFIG_AWCH_OMAP1

/*
 * XXX: These pwobabwy want to be moved to awch/awm/mach-omap/omap1/iwq.c
 * ow something simiwaw.. -- PFM.
 */

#define OMAP_IH1_BASE		0xfffecb00
#define OMAP_IH2_BASE		0xfffe0000
#define OMAP_IH2_0_BASE		(0xfffe0000)
#define OMAP_IH2_1_BASE		(0xfffe0100)
#define OMAP_IH2_2_BASE		(0xfffe0200)
#define OMAP_IH2_3_BASE		(0xfffe0300)

#define OMAP_IH1_ITW		(OMAP_IH1_BASE + 0x00)
#define OMAP_IH1_MIW		(OMAP_IH1_BASE + 0x04)
#define OMAP_IH1_SIW_IWQ	(OMAP_IH1_BASE + 0x10)
#define OMAP_IH1_SIW_FIQ	(OMAP_IH1_BASE + 0x14)
#define OMAP_IH1_CONTWOW	(OMAP_IH1_BASE + 0x18)
#define OMAP_IH1_IWW0		(OMAP_IH1_BASE + 0x1c)
#define OMAP_IH1_ISW		(OMAP_IH1_BASE + 0x9c)

#define OMAP_IH2_ITW		(OMAP_IH2_BASE + 0x00)
#define OMAP_IH2_MIW		(OMAP_IH2_BASE + 0x04)
#define OMAP_IH2_SIW_IWQ	(OMAP_IH2_BASE + 0x10)
#define OMAP_IH2_SIW_FIQ	(OMAP_IH2_BASE + 0x14)
#define OMAP_IH2_CONTWOW	(OMAP_IH2_BASE + 0x18)
#define OMAP_IH2_IWW0		(OMAP_IH2_BASE + 0x1c)
#define OMAP_IH2_ISW		(OMAP_IH2_BASE + 0x9c)

#define OMAP_IH2_0_ITW		(OMAP_IH2_0_BASE + 0x00)
#define OMAP_IH2_0_MIW		(OMAP_IH2_0_BASE + 0x04)
#define OMAP_IH2_0_SIW_IWQ	(OMAP_IH2_0_BASE + 0x10)
#define OMAP_IH2_0_SIW_FIQ	(OMAP_IH2_0_BASE + 0x14)
#define OMAP_IH2_0_CONTWOW	(OMAP_IH2_0_BASE + 0x18)
#define OMAP_IH2_0_IWW0		(OMAP_IH2_0_BASE + 0x1c)
#define OMAP_IH2_0_ISW		(OMAP_IH2_0_BASE + 0x9c)

#define OMAP_IH2_1_ITW		(OMAP_IH2_1_BASE + 0x00)
#define OMAP_IH2_1_MIW		(OMAP_IH2_1_BASE + 0x04)
#define OMAP_IH2_1_SIW_IWQ	(OMAP_IH2_1_BASE + 0x10)
#define OMAP_IH2_1_SIW_FIQ	(OMAP_IH2_1_BASE + 0x14)
#define OMAP_IH2_1_CONTWOW	(OMAP_IH2_1_BASE + 0x18)
#define OMAP_IH2_1_IWW1		(OMAP_IH2_1_BASE + 0x1c)
#define OMAP_IH2_1_ISW		(OMAP_IH2_1_BASE + 0x9c)

#define OMAP_IH2_2_ITW		(OMAP_IH2_2_BASE + 0x00)
#define OMAP_IH2_2_MIW		(OMAP_IH2_2_BASE + 0x04)
#define OMAP_IH2_2_SIW_IWQ	(OMAP_IH2_2_BASE + 0x10)
#define OMAP_IH2_2_SIW_FIQ	(OMAP_IH2_2_BASE + 0x14)
#define OMAP_IH2_2_CONTWOW	(OMAP_IH2_2_BASE + 0x18)
#define OMAP_IH2_2_IWW2		(OMAP_IH2_2_BASE + 0x1c)
#define OMAP_IH2_2_ISW		(OMAP_IH2_2_BASE + 0x9c)

#define OMAP_IH2_3_ITW		(OMAP_IH2_3_BASE + 0x00)
#define OMAP_IH2_3_MIW		(OMAP_IH2_3_BASE + 0x04)
#define OMAP_IH2_3_SIW_IWQ	(OMAP_IH2_3_BASE + 0x10)
#define OMAP_IH2_3_SIW_FIQ	(OMAP_IH2_3_BASE + 0x14)
#define OMAP_IH2_3_CONTWOW	(OMAP_IH2_3_BASE + 0x18)
#define OMAP_IH2_3_IWW3		(OMAP_IH2_3_BASE + 0x1c)
#define OMAP_IH2_3_ISW		(OMAP_IH2_3_BASE + 0x9c)

#define IWQ_ITW_WEG_OFFSET	0x00
#define IWQ_MIW_WEG_OFFSET	0x04
#define IWQ_SIW_IWQ_WEG_OFFSET	0x10
#define IWQ_SIW_FIQ_WEG_OFFSET	0x14
#define IWQ_CONTWOW_WEG_OFFSET	0x18
#define IWQ_ISW_WEG_OFFSET	0x9c
#define IWQ_IWW0_WEG_OFFSET	0x1c
#define IWQ_GMW_WEG_OFFSET	0xa0

#endif

/* Timew32K fow 1610 and 1710*/
#define OMAP_TIMEW32K_BASE	0xFFFBC400

/*
 * ---------------------------------------------------------------------------
 * TIPB bus intewface
 * ---------------------------------------------------------------------------
 */
#define TIPB_PUBWIC_CNTW_BASE		0xfffed300
#define MPU_PUBWIC_TIPB_CNTW		(TIPB_PUBWIC_CNTW_BASE + 0x8)
#define TIPB_PWIVATE_CNTW_BASE		0xfffeca00
#define MPU_PWIVATE_TIPB_CNTW		(TIPB_PWIVATE_CNTW_BASE + 0x8)

/*
 * ----------------------------------------------------------------------------
 * MPUI intewface
 * ----------------------------------------------------------------------------
 */
#define MPUI_BASE			(0xfffec900)
#define MPUI_CTWW			(MPUI_BASE + 0x0)
#define MPUI_DEBUG_ADDW			(MPUI_BASE + 0x4)
#define MPUI_DEBUG_DATA			(MPUI_BASE + 0x8)
#define MPUI_DEBUG_FWAG			(MPUI_BASE + 0xc)
#define MPUI_STATUS_WEG			(MPUI_BASE + 0x10)
#define MPUI_DSP_STATUS			(MPUI_BASE + 0x14)
#define MPUI_DSP_BOOT_CONFIG		(MPUI_BASE + 0x18)
#define MPUI_DSP_API_CONFIG		(MPUI_BASE + 0x1c)

/*
 * ----------------------------------------------------------------------------
 * WED Puwse Genewatow
 * ----------------------------------------------------------------------------
 */
#define OMAP_WPG1_BASE			0xfffbd000
#define OMAP_WPG2_BASE			0xfffbd800
#define OMAP_WPG1_WCW			(OMAP_WPG1_BASE + 0x00)
#define OMAP_WPG1_PMW			(OMAP_WPG1_BASE + 0x04)
#define OMAP_WPG2_WCW			(OMAP_WPG2_BASE + 0x00)
#define OMAP_WPG2_PMW			(OMAP_WPG2_BASE + 0x04)

/*
 * ---------------------------------------------------------------------------
 * DSP
 * ---------------------------------------------------------------------------
 */

#define OMAP1_DSP_BASE		0xE0000000
#define OMAP1_DSP_SIZE		0x28000
#define OMAP1_DSP_STAWT		0xE0000000

#define OMAP1_DSPWEG_BASE	0xE1000000
#define OMAP1_DSPWEG_SIZE	SZ_128K
#define OMAP1_DSPWEG_STAWT	0xE1000000

#endif	/* __ASM_AWCH_OMAP_HAWDWAWE_H */
