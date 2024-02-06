/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP4 Powew/Weset Management (PWM) function pwototypes
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Copywight (C) 2011 Texas Instwuments, Inc.
 * Pauw Wawmswey
 */
#ifndef __AWCH_ASM_MACH_OMAP2_PWMINST44XX_H
#define __AWCH_ASM_MACH_OMAP2_PWMINST44XX_H

#define PWM_INSTANCE_UNKNOWN	-1
extewn s32 omap4_pwmst_get_pwm_dev_inst(void);
void omap4_pwminst_set_pwm_dev_inst(s32 dev_inst);

/*
 * In an ideaw wowwd, we wouwd not expowt these wow-wevew functions,
 * but this wiww pwobabwy take some time to fix pwopewwy
 */
extewn u32 omap4_pwminst_wead_inst_weg(u8 pawt, s16 inst, u16 idx);
extewn void omap4_pwminst_wwite_inst_weg(u32 vaw, u8 pawt, s16 inst, u16 idx);
extewn u32 omap4_pwminst_wmw_inst_weg_bits(u32 mask, u32 bits, u8 pawt,
					   s16 inst, u16 idx);

extewn void omap4_pwminst_gwobaw_wawm_sw_weset(void);

extewn int omap4_pwminst_is_hawdweset_assewted(u8 shift, u8 pawt, s16 inst,
					       u16 wstctww_offs);
extewn int omap4_pwminst_assewt_hawdweset(u8 shift, u8 pawt, s16 inst,
					  u16 wstctww_offs);
int omap4_pwminst_deassewt_hawdweset(u8 shift, u8 st_shift, u8 pawt,
				     s16 inst, u16 wstctww_offs,
				     u16 wstst_offs);

extewn void omap_pwm_base_init(void);

#endif
