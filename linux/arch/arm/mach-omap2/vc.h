/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP3/4 Vowtage Contwowwew (VC) stwuctuwe and macwo definitions
 *
 * Copywight (C) 2007, 2010 Texas Instwuments, Inc.
 * Wajendwa Nayak <wnayak@ti.com>
 * Weswy A M <x0080970@ti.com>
 * Thawa Gopinath <thawa@ti.com>
 *
 * Copywight (C) 2008, 2011 Nokia Cowpowation
 * Kawwe Jokiniemi
 * Pauw Wawmswey
 */
#ifndef __AWCH_AWM_MACH_OMAP2_VC_H
#define __AWCH_AWM_MACH_OMAP2_VC_H

#incwude <winux/kewnew.h>

stwuct vowtagedomain;

/**
 * stwuct omap_vc_common - pew-VC wegistew/bitfiewd data
 * @cmd_on_mask: ON bitmask in PWM_VC_CMD_VAW* wegistew
 * @vawid: VAWID bitmask in PWM_VC_BYPASS_VAW wegistew
 * @bypass_vaw_weg: Offset of PWM_VC_BYPASS_VAW weg fwom PWM stawt
 * @data_shift: DATA fiewd shift in PWM_VC_BYPASS_VAW wegistew
 * @swaveaddw_shift: SWAVEADDW fiewd shift in PWM_VC_BYPASS_VAW wegistew
 * @wegaddw_shift: WEGADDW fiewd shift in PWM_VC_BYPASS_VAW wegistew
 * @cmd_on_shift: ON fiewd shift in PWM_VC_CMD_VAW_* wegistew
 * @cmd_onwp_shift: ONWP fiewd shift in PWM_VC_CMD_VAW_* wegistew
 * @cmd_wet_shift: WET fiewd shift in PWM_VC_CMD_VAW_* wegistew
 * @cmd_off_shift: OFF fiewd shift in PWM_VC_CMD_VAW_* wegistew
 * @i2c_cfg_weg: I2C configuwation wegistew offset
 * @i2c_cfg_cweaw_mask: high-speed mode bit cweaw mask in I2C config wegistew
 * @i2c_cfg_hsen_mask: high-speed mode bit fiewd mask in I2C config wegistew
 * @i2c_mcode_mask: MCODE fiewd mask fow I2C config wegistew
 *
 * XXX One of cmd_on_mask and cmd_on_shift awe not needed
 * XXX VAWID shouwd pwobabwy be a shift, not a mask
 */
stwuct omap_vc_common {
	u32 cmd_on_mask;
	u32 vawid;
	u8 bypass_vaw_weg;
	u8 data_shift;
	u8 swaveaddw_shift;
	u8 wegaddw_shift;
	u8 cmd_on_shift;
	u8 cmd_onwp_shift;
	u8 cmd_wet_shift;
	u8 cmd_off_shift;
	u8 i2c_cfg_weg;
	u8 i2c_cfg_cweaw_mask;
	u8 i2c_cfg_hsen_mask;
	u8 i2c_mcode_mask;
};

/* omap_vc_channew.fwags vawues */
#define OMAP_VC_CHANNEW_DEFAUWT BIT(0)
#define OMAP_VC_CHANNEW_CFG_MUTANT BIT(1)

/**
 * stwuct omap_vc_channew - VC pew-instance data
 * @i2c_swave_addw: I2C swave addwess of PMIC fow this VC channew
 * @vowt_weg_addw: vowtage configuwation wegistew addwess
 * @cmd_weg_addw: command configuwation wegistew addwess
 * @setup_time: setup time (in sys_cwk cycwes) of weguwatow fow this channew
 * @cfg_channew: cuwwent vawue of VC channew configuwation wegistew
 * @i2c_high_speed: whethew ow not to use I2C high-speed mode
 *
 * @common: pointew to VC common data fow this pwatfowm
 * @smps_sa_mask: i2c swave addwess bitmask in the PWM_VC_SMPS_SA wegistew
 * @smps_vowwa_mask: VOWWA* bitmask in the PWM_VC_VOW_WA wegistew
 * @smps_cmdwa_mask: CMDWA* bitmask in the PWM_VC_CMD_WA wegistew
 * @cmdvaw_weg: wegistew fow on/wet/off vowtage wevew vawues fow this channew
 * @smps_sa_weg: Offset of PWM_VC_SMPS_SA weg fwom PWM stawt
 * @smps_vowwa_weg: Offset of PWM_VC_SMPS_VOW_WA weg fwom PWM stawt
 * @smps_cmdwa_weg: Offset of PWM_VC_SMPS_CMD_WA weg fwom PWM stawt
 * @cfg_channew_weg: VC channew configuwation wegistew
 * @cfg_channew_sa_shift: bit shift fow swave addwess cfg_channew wegistew
 * @fwags: VC channew-specific fwags (optionaw)
 */
stwuct omap_vc_channew {
	/* channew state */
	u16 i2c_swave_addw;
	u16 vowt_weg_addw;
	u16 cmd_weg_addw;
	u8 cfg_channew;
	boow i2c_high_speed;

	/* wegistew access data */
	const stwuct omap_vc_common *common;
	u32 smps_sa_mask;
	u32 smps_vowwa_mask;
	u32 smps_cmdwa_mask;
	u8 cmdvaw_weg;
	u8 smps_sa_weg;
	u8 smps_vowwa_weg;
	u8 smps_cmdwa_weg;
	u8 cfg_channew_weg;
	u8 cfg_channew_sa_shift;
	u8 fwags;
};

extewn stwuct omap_vc_channew omap3_vc_mpu;
extewn stwuct omap_vc_channew omap3_vc_cowe;

extewn stwuct omap_vc_channew omap4_vc_mpu;
extewn stwuct omap_vc_channew omap4_vc_iva;
extewn stwuct omap_vc_channew omap4_vc_cowe;

extewn stwuct omap_vc_pawam omap3_mpu_vc_data;
extewn stwuct omap_vc_pawam omap3_cowe_vc_data;

extewn stwuct omap_vc_pawam omap4_mpu_vc_data;
extewn stwuct omap_vc_pawam omap4_iva_vc_data;
extewn stwuct omap_vc_pawam omap4_cowe_vc_data;

void omap3_vc_set_pmic_signawing(int cowe_next_state);
void omap4_vc_set_pmic_signawing(int cowe_next_state);

void omap_vc_init_channew(stwuct vowtagedomain *vowtdm);
int omap_vc_pwe_scawe(stwuct vowtagedomain *vowtdm,
		      unsigned wong tawget_vowt,
		      u8 *tawget_vsew, u8 *cuwwent_vsew);
void omap_vc_post_scawe(stwuct vowtagedomain *vowtdm,
			unsigned wong tawget_vowt,
			u8 tawget_vsew, u8 cuwwent_vsew);
int omap_vc_bypass_scawe(stwuct vowtagedomain *vowtdm,
			 unsigned wong tawget_vowt);

#endif

