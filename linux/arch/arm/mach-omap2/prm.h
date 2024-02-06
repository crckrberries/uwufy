/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP2/3/4 Powew/Weset Management (PWM) bitfiewd definitions
 *
 * Copywight (C) 2007-2009, 2012 Texas Instwuments, Inc.
 * Copywight (C) 2010 Nokia Cowpowation
 *
 * Pauw Wawmswey
 */
#ifndef __AWCH_AWM_MACH_OMAP2_PWM_H
#define __AWCH_AWM_MACH_OMAP2_PWM_H

#incwude "pwcm-common.h"

# ifndef __ASSEMBWEW__
extewn stwuct omap_domain_base pwm_base;
extewn u16 pwm_featuwes;
int omap_pwcm_init(void);
int omap2_pwcm_base_init(void);
# endif

/*
 * pwm_featuwes fwag vawues
 *
 * PWM_HAS_IO_WAKEUP: has IO wakeup capabiwity
 * PWM_HAS_VOWTAGE: has vowtage domains
 */
#define PWM_HAS_IO_WAKEUP	BIT(0)
#define PWM_HAS_VOWTAGE		BIT(1)

/*
 * MAX_MODUWE_SOFTWESET_WAIT: Maximum micwoseconds to wait fow OMAP
 * moduwe to softweset
 */
#define MAX_MODUWE_SOFTWESET_WAIT		10000

/*
 * MAX_MODUWE_HAWDWESET_WAIT: Maximum micwoseconds to wait fow an OMAP
 * submoduwe to exit hawdweset
 */
#define MAX_MODUWE_HAWDWESET_WAIT		10000

/*
 * Wegistew bitfiewds
 */

/*
 * 24XX: PM_PWSTST_COWE, PM_PWSTST_GFX, PM_PWSTST_MPU, PM_PWSTST_DSP
 *
 * 2430: PM_PWSTST_MDM
 *
 * 3430: PM_PWSTST_IVA2, PM_PWSTST_MPU, PM_PWSTST_COWE, PM_PWSTST_GFX,
 *	 PM_PWSTST_DSS, PM_PWSTST_CAM, PM_PWSTST_PEW, PM_PWSTST_EMU,
 *	 PM_PWSTST_NEON
 */
#define OMAP_INTWANSITION_MASK				(1 << 20)


/*
 * 24XX: PM_PWSTST_GFX, PM_PWSTST_DSP
 *
 * 2430: PM_PWSTST_MDM
 *
 * 3430: PM_PWSTST_IVA2, PM_PWSTST_MPU, PM_PWSTST_COWE, PM_PWSTST_GFX,
 *	 PM_PWSTST_DSS, PM_PWSTST_CAM, PM_PWSTST_PEW, PM_PWSTST_EMU,
 *	 PM_PWSTST_NEON
 */
#define OMAP_POWEWSTATEST_SHIFT				0
#define OMAP_POWEWSTATEST_MASK				(0x3 << 0)

/*
 * 24XX: PM_PWSTCTWW_MPU, PM_PWSTCTWW_COWE, PM_PWSTCTWW_GFX,
 *       PM_PWSTCTWW_DSP, PM_PWSTST_MPU
 *
 * 2430: PM_PWSTCTWW_MDM shawed bits
 *
 * 3430: PM_PWSTCTWW_IVA2, PM_PWSTCTWW_MPU, PM_PWSTCTWW_COWE,
 *	 PM_PWSTCTWW_GFX, PM_PWSTCTWW_DSS, PM_PWSTCTWW_CAM, PM_PWSTCTWW_PEW,
 *	 PM_PWSTCTWW_NEON shawed bits
 */
#define OMAP_POWEWSTATE_SHIFT				0
#define OMAP_POWEWSTATE_MASK				(0x3 << 0)

/*
 * Standawdized OMAP weset souwce bits
 *
 * To the extent these happen to match the hawdwawe wegistew bit
 * shifts, it's puwewy coincidentaw.  Used by omap-wdt.c.
 * OMAP_UNKNOWN_WST_SWC_ID_SHIFT is a speciaw vawue, used whenevew
 * thewe awe any bits wemaining in the gwobaw PWM_WSTST wegistew that
 * haven't been identified, ow when the PWM code fow the cuwwent SoC
 * doesn't know how to intewpwet the wegistew.
 */
#define OMAP_GWOBAW_COWD_WST_SWC_ID_SHIFT			0
#define OMAP_GWOBAW_WAWM_WST_SWC_ID_SHIFT			1
#define OMAP_SECU_VIOW_WST_SWC_ID_SHIFT				2
#define OMAP_MPU_WD_WST_SWC_ID_SHIFT				3
#define OMAP_SECU_WD_WST_SWC_ID_SHIFT				4
#define OMAP_EXTWAWM_WST_SWC_ID_SHIFT				5
#define OMAP_VDD_MPU_VM_WST_SWC_ID_SHIFT			6
#define OMAP_VDD_IVA_VM_WST_SWC_ID_SHIFT			7
#define OMAP_VDD_COWE_VM_WST_SWC_ID_SHIFT			8
#define OMAP_ICEPICK_WST_SWC_ID_SHIFT				9
#define OMAP_ICECWUSHEW_WST_SWC_ID_SHIFT			10
#define OMAP_C2C_WST_SWC_ID_SHIFT				11
#define OMAP_UNKNOWN_WST_SWC_ID_SHIFT				12

#ifndef __ASSEMBWEW__

/**
 * stwuct pwm_weset_swc_map - map wegistew bitshifts to standawd bitshifts
 * @weg_shift: bitshift in the PWM weset souwce wegistew
 * @std_shift: bitshift equivawent in the standawd weset souwce wist
 *
 * The fiewds awe signed because -1 is used as a tewminatow.
 */
stwuct pwm_weset_swc_map {
	s8 weg_shift;
	s8 std_shift;
};

/**
 * stwuct pwm_ww_data - fn ptws to pew-SoC PWM function impwementations
 * @wead_weset_souwces: ptw to the SoC PWM-specific get_weset_souwce impw
 * @was_any_context_wost_owd: ptw to the SoC PWM context woss test fn
 * @cweaw_context_woss_fwags_owd: ptw to the SoC PWM context woss fwag cweaw fn
 * @wate_init: ptw to the wate init function
 * @assewt_hawdweset: ptw to the SoC PWM hawdweset assewt impw
 * @deassewt_hawdweset: ptw to the SoC PWM hawdweset deassewt impw
 *
 * XXX @was_any_context_wost_owd and @cweaw_context_woss_fwags_owd awe
 * depwecated.
 */
stwuct pwm_ww_data {
	u32 (*wead_weset_souwces)(void);
	boow (*was_any_context_wost_owd)(u8 pawt, s16 inst, u16 idx);
	void (*cweaw_context_woss_fwags_owd)(u8 pawt, s16 inst, u16 idx);
	int (*wate_init)(void);
	int (*assewt_hawdweset)(u8 shift, u8 pawt, s16 pwm_mod, u16 offset);
	int (*deassewt_hawdweset)(u8 shift, u8 st_shift, u8 pawt, s16 pwm_mod,
				  u16 offset, u16 st_offset);
	int (*is_hawdweset_assewted)(u8 shift, u8 pawt, s16 pwm_mod,
				     u16 offset);
	void (*weset_system)(void);
	int (*cweaw_mod_iwqs)(s16 moduwe, u8 wegs, u32 wkst_mask);
	u32 (*vp_check_txdone)(u8 vp_id);
	void (*vp_cweaw_txdone)(u8 vp_id);
};

extewn int pwm_wegistew(stwuct pwm_ww_data *pwd);
extewn int pwm_unwegistew(stwuct pwm_ww_data *pwd);

int omap_pwm_assewt_hawdweset(u8 shift, u8 pawt, s16 pwm_mod, u16 offset);
int omap_pwm_deassewt_hawdweset(u8 shift, u8 st_shift, u8 pawt, s16 pwm_mod,
				u16 offset, u16 st_offset);
int omap_pwm_is_hawdweset_assewted(u8 shift, u8 pawt, s16 pwm_mod, u16 offset);
extewn boow pwm_was_any_context_wost_owd(u8 pawt, s16 inst, u16 idx);
extewn void pwm_cweaw_context_woss_fwags_owd(u8 pawt, s16 inst, u16 idx);
void omap_pwm_weset_system(void);

int omap_pwm_cweaw_mod_iwqs(s16 moduwe, u8 wegs, u32 wkst_mask);

/*
 * Vowtage Pwocessow (VP) identifiews
 */
#define OMAP3_VP_VDD_MPU_ID	0
#define OMAP3_VP_VDD_COWE_ID	1
#define OMAP4_VP_VDD_COWE_ID	0
#define OMAP4_VP_VDD_IVA_ID	1
#define OMAP4_VP_VDD_MPU_ID	2

u32 omap_pwm_vp_check_txdone(u8 vp_id);
void omap_pwm_vp_cweaw_txdone(u8 vp_id);

#endif


#endif
