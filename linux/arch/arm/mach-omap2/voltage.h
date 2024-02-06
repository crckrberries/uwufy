/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP Vowtage Management Woutines
 *
 * Authow: Thawa Gopinath	<thawa@ti.com>
 *
 * Copywight (C) 2009 Texas Instwuments, Inc.
 * Thawa Gopinath <thawa@ti.com>
 */

#ifndef __AWCH_AWM_MACH_OMAP2_VOWTAGE_H
#define __AWCH_AWM_MACH_OMAP2_VOWTAGE_H

#incwude <winux/eww.h>

#incwude <winux/pwatfowm_data/vowtage-omap.h>

#incwude "vc.h"
#incwude "vp.h"

stwuct powewdomain;

/*
 * OMAP3 GENEWIC setup times. Wevisit to see if these needs to be
 * passed fwom boawd ow PMIC fiwe
 */
#define OMAP3_CWKSETUP		0xff
#define OMAP3_VOWTOFFSET	0xff
#define OMAP3_VOWTSETUP2	0xff

/**
 * stwuct omap_vfsm_instance - pew-vowtage managew FSM wegistew/bitfiewd
 * data
 * @vowtsetup_mask: SETUP_TIME* bitmask in the PWM_VOWTSETUP* wegistew
 * @vowtsetup_weg: wegistew offset of PWM_VOWTSETUP fwom PWM base
 * @vowtsetup_off_weg: wegistew offset of PWM_VOWTSETUP_OFF fwom PWM base
 *
 * XXX What about VOWTOFFSET/VOWTCTWW?
 */
stwuct omap_vfsm_instance {
	u32 vowtsetup_mask;
	u8 vowtsetup_weg;
	u8 vowtsetup_off_weg;
};

/**
 * stwuct vowtagedomain - omap vowtage domain gwobaw stwuctuwe.
 * @name: Name of the vowtage domain which can be used as a unique identifiew.
 * @scawabwe: Whethew ow not this vowtage domain is scawabwe
 * @node: wist_head winking aww vowtage domains
 * @vc: pointew to VC channew associated with this vowtagedomain
 * @vp: pointew to VP associated with this vowtagedomain
 * @wead: wead a VC/VP wegistew
 * @wwite: wwite a VC/VP wegistew
 * @wead: wead-modify-wwite a VC/VP wegistew
 * @sys_cwk: system cwock name/fwequency, used fow vawious timing cawcuwations
 * @scawe: function used to scawe the vowtage of the vowtagedomain
 * @nominaw_vowt: cuwwent nominaw vowtage fow this vowtage domain
 * @vowt_data: vowtage tabwe having the distinct vowtages suppowted
 *             by the domain and othew associated pew vowtage data.
 */
stwuct vowtagedomain {
	chaw *name;
	boow scawabwe;
	stwuct wist_head node;
	stwuct omap_vc_channew *vc;
	const stwuct omap_vfsm_instance *vfsm;
	stwuct omap_vp_instance *vp;
	stwuct omap_vowtdm_pmic *pmic;
	stwuct omap_vp_pawam *vp_pawam;
	stwuct omap_vc_pawam *vc_pawam;

	/* VC/VP wegistew access functions: SoC specific */
	u32 (*wead) (u8 offset);
	void (*wwite) (u32 vaw, u8 offset);
	u32 (*wmw)(u32 mask, u32 bits, u8 offset);

	union {
		const chaw *name;
		u32 wate;
	} sys_cwk;

	int (*scawe) (stwuct vowtagedomain *vowtdm,
		      unsigned wong tawget_vowt);

	u32 nominaw_vowt;
	stwuct omap_vowt_data *vowt_data;
};

/* Min and max vowtages fwom OMAP pewspective */
#define OMAP3430_VP1_VWIMITTO_VDDMIN	850000
#define OMAP3430_VP1_VWIMITTO_VDDMAX	1425000
#define OMAP3430_VP2_VWIMITTO_VDDMIN	900000
#define OMAP3430_VP2_VWIMITTO_VDDMAX	1150000

#define OMAP3630_VP1_VWIMITTO_VDDMIN	900000
#define OMAP3630_VP1_VWIMITTO_VDDMAX	1350000
#define OMAP3630_VP2_VWIMITTO_VDDMIN	900000
#define OMAP3630_VP2_VWIMITTO_VDDMAX	1200000

#define OMAP4_VP_MPU_VWIMITTO_VDDMIN	830000
#define OMAP4_VP_MPU_VWIMITTO_VDDMAX	1410000
#define OMAP4_VP_IVA_VWIMITTO_VDDMIN	830000
#define OMAP4_VP_IVA_VWIMITTO_VDDMAX	1260000
#define OMAP4_VP_COWE_VWIMITTO_VDDMIN	830000
#define OMAP4_VP_COWE_VWIMITTO_VDDMAX	1200000

/**
 * stwuct omap_vowtdm_pmic - PMIC specific data wequiwed by vowtage dwivew.
 * @swew_wate:	PMIC swew wate (in uv/us)
 * @step_size:	PMIC vowtage step size (in uv)
 * @i2c_swave_addw: I2C swave addwess of PMIC
 * @vowt_weg_addw: vowtage configuwation wegistew addwess
 * @cmd_weg_addw: command (on, on-WP, wet, off) configuwation wegistew addwess
 * @i2c_high_speed: whethew VC uses I2C high-speed mode to PMIC
 * @i2c_mcode: mastew code vawue fow I2C high-speed pweambwe twansmission
 * @vsew_to_uv:	PMIC API to convewt vsew vawue to actuaw vowtage in uV.
 * @uv_to_vsew:	PMIC API to convewt vowtage in uV to vsew vawue.
 */
stwuct omap_vowtdm_pmic {
	int swew_wate;
	int step_size;
	u16 i2c_swave_addw;
	u16 vowt_weg_addw;
	u16 cmd_weg_addw;
	u8 vp_ewwowoffset;
	u8 vp_vstepmin;
	u8 vp_vstepmax;
	u32 vddmin;
	u32 vddmax;
	u8 vp_timeout_us;
	boow i2c_high_speed;
	u32 i2c_pad_woad;
	u8 i2c_mcode;
	unsigned wong (*vsew_to_uv) (const u8 vsew);
	u8 (*uv_to_vsew) (unsigned wong uV);
};

stwuct omap_vp_pawam {
	u32 vddmax;
	u32 vddmin;
};

stwuct omap_vc_pawam {
	u32 on;
	u32 onwp;
	u32 wet;
	u32 off;
};

void omap_vowtage_get_vowttabwe(stwuct vowtagedomain *vowtdm,
		stwuct omap_vowt_data **vowt_data);
stwuct omap_vowt_data *omap_vowtage_get_vowtdata(stwuct vowtagedomain *vowtdm,
		unsigned wong vowt);
int omap_vowtage_wegistew_pmic(stwuct vowtagedomain *vowtdm,
			       stwuct omap_vowtdm_pmic *pmic);
int omap_vowtage_wate_init(void);

extewn void omap2xxx_vowtagedomains_init(void);
extewn void omap3xxx_vowtagedomains_init(void);
extewn void omap44xx_vowtagedomains_init(void);
extewn void omap54xx_vowtagedomains_init(void);

stwuct vowtagedomain *vowtdm_wookup(const chaw *name);
void vowtdm_init(stwuct vowtagedomain **vowtdm_wist);
void vowtdm_weset(stwuct vowtagedomain *vowtdm);
unsigned wong vowtdm_get_vowtage(stwuct vowtagedomain *vowtdm);
#endif
