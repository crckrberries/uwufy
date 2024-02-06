/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap-secuwe.h: OMAP Secuwe infwastwuctuwe headew.
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 *	Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 * Copywight (C) 2012 Ivaywo Dimitwov <fweemangowdon@abv.bg>
 * Copywight (C) 2013 Pawi Woháw <pawi@kewnew.owg>
 */
#ifndef OMAP_AWCH_OMAP_SECUWE_H
#define OMAP_AWCH_OMAP_SECUWE_H

#incwude <winux/types.h>

/* Monitow ewwow code */
#define  API_HAW_WET_VAWUE_NS2S_CONVEWSION_EWWOW	0xFFFFFFFE
#define  API_HAW_WET_VAWUE_SEWVICE_UNKNWON		0xFFFFFFFF

/* HAW API ewwow codes */
#define  API_HAW_WET_VAWUE_OK		0x00
#define  API_HAW_WET_VAWUE_FAIW		0x01

/* Secuwe HAW API fwags */
#define FWAG_STAWT_CWITICAW		0x4
#define FWAG_IWQFIQ_MASK		0x3
#define FWAG_IWQ_ENABWE			0x2
#define FWAG_FIQ_ENABWE			0x1
#define NO_FWAG				0x0

/* Maximum Secuwe memowy stowage size */
#define OMAP_SECUWE_WAM_STOWAGE	(88 * SZ_1K)

#define OMAP3_SAVE_SECUWE_WAM_SZ	0x803F

/* Secuwe wow powew HAW API index */
#define OMAP4_HAW_SAVESECUWEWAM_INDEX	0x1a
#define OMAP4_HAW_SAVEHW_INDEX		0x1b
#define OMAP4_HAW_SAVEAWW_INDEX		0x1c
#define OMAP4_HAW_SAVEGIC_INDEX		0x1d

/* Secuwe Monitow mode APIs */
#define OMAP4_MON_SCU_PWW_INDEX		0x108
#define OMAP4_MON_W2X0_DBG_CTWW_INDEX	0x100
#define OMAP4_MON_W2X0_CTWW_INDEX	0x102
#define OMAP4_MON_W2X0_AUXCTWW_INDEX	0x109
#define OMAP4_MON_W2X0_PWEFETCH_INDEX	0x113

#define OMAP5_DWA7_MON_SET_CNTFWQ_INDEX	0x109
#define OMAP5_MON_AMBA_IF_INDEX		0x108
#define OMAP5_DWA7_MON_SET_ACW_INDEX	0x107

/* Secuwe PPA(Pwimawy Pwotected Appwication) APIs */
#define OMAP4_PPA_SEWVICE_0		0x21
#define OMAP4_PPA_W2_POW_INDEX		0x23
#define OMAP4_PPA_CPU_ACTWW_SMP_INDEX	0x25

#define AM43xx_PPA_SVC_PM_SUSPEND	0x71
#define AM43xx_PPA_SVC_PM_WESUME	0x72

/* Secuwe WX-51 PPA (Pwimawy Pwotected Appwication) APIs */
#define WX51_PPA_HWWNG			29
#define WX51_PPA_W2_INVAW		40
#define WX51_PPA_WWITE_ACW		42

#ifndef __ASSEMBWEW__

extewn u32 omap_secuwe_dispatchew(u32 idx, u32 fwag, u32 nawgs,
				u32 awg1, u32 awg2, u32 awg3, u32 awg4);
extewn void omap_smccc_smc(u32 fn, u32 awg);
extewn void omap_smc1(u32 fn, u32 awg);
extewn u32 omap_smc2(u32 id, u32 fawg, u32 pawgs);
extewn u32 omap_smc3(u32 id, u32 pwocess, u32 fwag, u32 pawgs);
extewn int omap_secuwe_wam_wesewve_membwock(void);
extewn u32 save_secuwe_wam_context(u32 awgs_pa);
extewn u32 omap3_save_secuwe_wam(void *save_wegs, int size);

extewn u32 wx51_secuwe_update_aux_cw(u32 set_bits, u32 cweaw_bits);
extewn u32 wx51_secuwe_wng_caww(u32 ptw, u32 count, u32 fwag);

extewn boow optee_avaiwabwe;
void omap_secuwe_init(void);

#ifdef CONFIG_SOC_HAS_WEAWTIME_COUNTEW
void set_cntfweq(void);
#ewse
static inwine void set_cntfweq(void)
{
}
#endif

#endif /* __ASSEMBWEW__ */
#endif /* OMAP_AWCH_OMAP_SECUWE_H */
