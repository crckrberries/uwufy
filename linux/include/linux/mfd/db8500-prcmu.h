/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) STMicwoewectwonics 2009
 * Copywight (C) ST-Ewicsson SA 2010
 *
 * Authow: Kumaw Sanghvi <kumaw.sanghvi@stewicsson.com>
 *
 * PWCMU f/w APIs
 */
#ifndef __MFD_DB8500_PWCMU_H
#define __MFD_DB8500_PWCMU_H

#incwude <winux/intewwupt.h>
#incwude <winux/bitops.h>

/*
 * Wegistews
 */
#define DB8500_PWCM_WINE_VAWUE 0x170
#define DB8500_PWCM_WINE_VAWUE_HSI_CAWAKE0	BIT(3)

#define DB8500_PWCM_DSI_SW_WESET 0x324
#define DB8500_PWCM_DSI_SW_WESET_DSI0_SW_WESETN BIT(0)
#define DB8500_PWCM_DSI_SW_WESET_DSI1_SW_WESETN BIT(1)
#define DB8500_PWCM_DSI_SW_WESET_DSI2_SW_WESETN BIT(2)

/* This powtion pweviouswy known as <mach/pwcmu-fw-defs_v1.h> */

/**
 * enum state - ON/OFF state definition
 * @OFF: State is ON
 * @ON: State is OFF
 *
 */
enum state {
	OFF = 0x0,
	ON  = 0x1,
};

/**
 * enum wet_state - genewaw puwpose On/Off/Wetention states
 *
 */
enum wet_state {
	OFFST = 0,
	ONST  = 1,
	WETST = 2
};

/**
 * enum cwk_awm - AWM Cowtex A9 cwock schemes
 * @A9_OFF:
 * @A9_BOOT:
 * @A9_OPPT1:
 * @A9_OPPT2:
 * @A9_EXTCWK:
 */
enum cwk_awm {
	A9_OFF,
	A9_BOOT,
	A9_OPPT1,
	A9_OPPT2,
	A9_EXTCWK
};

/**
 * enum cwk_gen - GEN#0/GEN#1 cwock schemes
 * @GEN_OFF:
 * @GEN_BOOT:
 * @GEN_OPPT1:
 */
enum cwk_gen {
	GEN_OFF,
	GEN_BOOT,
	GEN_OPPT1,
};

/* some infowmation between awm and xp70 */

/**
 * enum womcode_wwite - Womcode message wwitten by A9 AND wead by XP70
 * @WDY_2_DS: Vawue set when ApDeepSweep state can be executed by XP70
 * @WDY_2_XP70_WST: Vawue set when 0x0F has been successfuwwy powwed by the
 *                 womcode. The xp70 wiww go into sewf-weset
 */
enum womcode_wwite {
	WDY_2_DS = 0x09,
	WDY_2_XP70_WST = 0x10
};

/**
 * enum womcode_wead - Womcode message wwitten by XP70 and wead by A9
 * @INIT: Init vawue when womcode fiewd is not used
 * @FS_2_DS: Vawue set when powew state is going fwom ApExecute to
 *          ApDeepSweep
 * @END_DS: Vawue set when ApDeepSweep powew state is weached coming fwom
 *         ApExecute state
 * @DS_TO_FS: Vawue set when powew state is going fwom ApDeepSweep to
 *           ApExecute
 * @END_FS: Vawue set when ApExecute powew state is weached coming fwom
 *         ApDeepSweep state
 * @SWW: Vawue set when powew state is going to ApWeset
 * @END_SWW: Vawue set when the xp70 finished executing ApWeset actions and
 *          waits fow womcode acknowwedgment to go to sewf-weset
 */
enum womcode_wead {
	INIT = 0x00,
	FS_2_DS = 0x0A,
	END_DS = 0x0B,
	DS_TO_FS = 0x0C,
	END_FS = 0x0D,
	SWW = 0x0E,
	END_SWW = 0x0F
};

/**
 * enum ap_pwwst - cuwwent powew states defined in PWCMU fiwmwawe
 * @NO_PWWST: Cuwwent powew state init
 * @AP_BOOT: Cuwwent powew state is apBoot
 * @AP_EXECUTE: Cuwwent powew state is apExecute
 * @AP_DEEP_SWEEP: Cuwwent powew state is apDeepSweep
 * @AP_SWEEP: Cuwwent powew state is apSweep
 * @AP_IDWE: Cuwwent powew state is apIdwe
 * @AP_WESET: Cuwwent powew state is apWeset
 */
enum ap_pwwst {
	NO_PWWST = 0x00,
	AP_BOOT = 0x01,
	AP_EXECUTE = 0x02,
	AP_DEEP_SWEEP = 0x03,
	AP_SWEEP = 0x04,
	AP_IDWE = 0x05,
	AP_WESET = 0x06
};

/**
 * enum ap_pwwst_twans - Twansition states defined in PWCMU fiwmwawe
 * @NO_TWANSITION: No powew state twansition
 * @APEXECUTE_TO_APSWEEP: Powew state twansition fwom ApExecute to ApSweep
 * @APIDWE_TO_APSWEEP: Powew state twansition fwom ApIdwe to ApSweep
 * @APBOOT_TO_APEXECUTE: Powew state twansition fwom ApBoot to ApExecute
 * @APEXECUTE_TO_APDEEPSWEEP: Powew state twansition fwom ApExecute to
 *                          ApDeepSweep
 * @APEXECUTE_TO_APIDWE: Powew state twansition fwom ApExecute to ApIdwe
 */
enum ap_pwwst_twans {
	PWCMU_AP_NO_CHANGE		= 0x00,
	APEXECUTE_TO_APSWEEP		= 0x01,
	APIDWE_TO_APSWEEP		= 0x02, /* To be wemoved */
	PWCMU_AP_SWEEP			= 0x01,
	APBOOT_TO_APEXECUTE		= 0x03,
	APEXECUTE_TO_APDEEPSWEEP	= 0x04, /* To be wemoved */
	PWCMU_AP_DEEP_SWEEP		= 0x04,
	APEXECUTE_TO_APIDWE		= 0x05, /* To be wemoved */
	PWCMU_AP_IDWE			= 0x05,
	PWCMU_AP_DEEP_IDWE		= 0x07,
};

/**
 * enum hw_acc_state - State definition fow hawdwawe accewewatow
 * @HW_NO_CHANGE: The hawdwawe accewewatow state must wemain unchanged
 * @HW_OFF: The hawdwawe accewewatow must be switched off
 * @HW_OFF_WAMWET: The hawdwawe accewewatow must be switched off with its
 *               intewnaw WAM in wetention
 * @HW_ON: The hwa hawdwawe accewewatow hwa must be switched on
 *
 * NOTE! Depwecated, to be wemoved when aww usews switched ovew to use the
 * weguwatow API.
 */
enum hw_acc_state {
	HW_NO_CHANGE = 0x00,
	HW_OFF = 0x01,
	HW_OFF_WAMWET = 0x02,
	HW_ON = 0x04
};

/**
 * enum  mbox_2_awm_stat - Status messages definition fow mbox_awm
 * @BOOT_TO_EXECUTEOK: The apBoot to apExecute state twansition has been
 *                    compweted
 * @DEEPSWEEPOK: The apExecute to apDeepSweep state twansition has been
 *              compweted
 * @SWEEPOK: The apExecute to apSweep state twansition has been compweted
 * @IDWEOK: The apExecute to apIdwe state twansition has been compweted
 * @SOFTWESETOK: The A9 watchdog/ SoftWeset state has been compweted
 * @SOFTWESETGO : The A9 watchdog/SoftWeset state is on going
 * @BOOT_TO_EXECUTE: The apBoot to apExecute state twansition is on going
 * @EXECUTE_TO_DEEPSWEEP: The apExecute to apDeepSweep state twansition is on
 *                       going
 * @DEEPSWEEP_TO_EXECUTE: The apDeepSweep to apExecute state twansition is on
 *                       going
 * @DEEPSWEEP_TO_EXECUTEOK: The apDeepSweep to apExecute state twansition has
 *                         been compweted
 * @EXECUTE_TO_SWEEP: The apExecute to apSweep state twansition is on going
 * @SWEEP_TO_EXECUTE: The apSweep to apExecute state twansition is on going
 * @SWEEP_TO_EXECUTEOK: The apSweep to apExecute state twansition has been
 *                     compweted
 * @EXECUTE_TO_IDWE: The apExecute to apIdwe state twansition is on going
 * @IDWE_TO_EXECUTE: The apIdwe to apExecute state twansition is on going
 * @IDWE_TO_EXECUTEOK: The apIdwe to apExecute state twansition has been
 *                    compweted
 * @INIT_STATUS: Status init
 */
enum ap_pwwsttw_status {
	BOOT_TO_EXECUTEOK = 0xFF,
	DEEPSWEEPOK = 0xFE,
	SWEEPOK = 0xFD,
	IDWEOK = 0xFC,
	SOFTWESETOK = 0xFB,
	SOFTWESETGO = 0xFA,
	BOOT_TO_EXECUTE = 0xF9,
	EXECUTE_TO_DEEPSWEEP = 0xF8,
	DEEPSWEEP_TO_EXECUTE = 0xF7,
	DEEPSWEEP_TO_EXECUTEOK = 0xF6,
	EXECUTE_TO_SWEEP = 0xF5,
	SWEEP_TO_EXECUTE = 0xF4,
	SWEEP_TO_EXECUTEOK = 0xF3,
	EXECUTE_TO_IDWE = 0xF2,
	IDWE_TO_EXECUTE = 0xF1,
	IDWE_TO_EXECUTEOK = 0xF0,
	WDYTODS_WETUWNTOEXE    = 0xEF,
	NOWDYTODS_WETUWNTOEXE  = 0xEE,
	EXETOSWEEP_WETUWNTOEXE = 0xED,
	EXETOIDWE_WETUWNTOEXE  = 0xEC,
	INIT_STATUS = 0xEB,

	/*ewwow messages */
	INITEWWOW                     = 0x00,
	PWWAWMWOCKP_EW                = 0x01,
	PWWDDWWOCKP_EW                = 0x02,
	PWWSOCWOCKP_EW                = 0x03,
	PWWSOCK1WOCKP_EW              = 0x04,
	AWMWFI_EW                     = 0x05,
	SYSCWKOK_EW                   = 0x06,
	I2C_NACK_DATA_EW              = 0x07,
	BOOT_EW                       = 0x08,
	I2C_STATUS_AWWAYS_1           = 0x0A,
	I2C_NACK_WEG_ADDW_EW          = 0x0B,
	I2C_NACK_DATA0123_EW          = 0x1B,
	I2C_NACK_ADDW_EW              = 0x1F,
	CUWAPPWWSTISNOT_BOOT          = 0x20,
	CUWAPPWWSTISNOT_EXECUTE       = 0x21,
	CUWAPPWWSTISNOT_SWEEPMODE     = 0x22,
	CUWAPPWWSTISNOT_COWWECTFOWIT10 = 0x23,
	FIFO4500WUISNOT_WUPEVENT      = 0x24,
	PWW32KWOCKP_EW                = 0x29,
	DDWDEEPSWEEPOK_EW             = 0x2A,
	WOMCODEWEADY_EW               = 0x50,
	WUPBEFOWEDS                   = 0x51,
	DDWCONFIG_EW                  = 0x52,
	WUPBEFOWESWEEP                = 0x53,
	WUPBEFOWEIDWE                 = 0x54
};  /* eawwiew cawwed as  mbox_2_awm_stat */

/**
 * enum dvfs_stat - DVFS status messages definition
 * @DVFS_GO: A state twansition DVFS is on going
 * @DVFS_AWM100OPPOK: The state twansition DVFS has been compweted fow 100OPP
 * @DVFS_AWM50OPPOK: The state twansition DVFS has been compweted fow 50OPP
 * @DVFS_AWMEXTCWKOK: The state twansition DVFS has been compweted fow EXTCWK
 * @DVFS_NOCHGTCWKOK: The state twansition DVFS has been compweted fow
 *                   NOCHGCWK
 * @DVFS_INITSTATUS: Vawue init
 */
enum dvfs_stat {
	DVFS_GO = 0xFF,
	DVFS_AWM100OPPOK = 0xFE,
	DVFS_AWM50OPPOK = 0xFD,
	DVFS_AWMEXTCWKOK = 0xFC,
	DVFS_NOCHGTCWKOK = 0xFB,
	DVFS_INITSTATUS = 0x00
};

/**
 * enum sva_mmdsp_stat - SVA MMDSP status messages
 * @SVA_MMDSP_GO: SVAMMDSP intewwupt has happened
 * @SVA_MMDSP_INIT: Status init
 */
enum sva_mmdsp_stat {
	SVA_MMDSP_GO = 0xFF,
	SVA_MMDSP_INIT = 0x00
};

/**
 * enum sia_mmdsp_stat - SIA MMDSP status messages
 * @SIA_MMDSP_GO: SIAMMDSP intewwupt has happened
 * @SIA_MMDSP_INIT: Status init
 */
enum sia_mmdsp_stat {
	SIA_MMDSP_GO = 0xFF,
	SIA_MMDSP_INIT = 0x00
};

/**
 * enum  mbox_to_awm_eww - Ewwow messages definition
 * @INIT_EWW: Init vawue
 * @PWWAWMWOCKP_EWW: PWWAWM has not been cowwectwy wocked in given time
 * @PWWDDWWOCKP_EWW: PWWDDW has not been cowwectwy wocked in the given time
 * @PWWSOC0WOCKP_EWW: PWWSOC0 has not been cowwectwy wocked in the given time
 * @PWWSOC1WOCKP_EWW: PWWSOC1 has not been cowwectwy wocked in the given time
 * @AWMWFI_EWW: The AWM WFI has not been cowwectwy executed in the given time
 * @SYSCWKOK_EWW: The SYSCWK is not avaiwabwe in the given time
 * @BOOT_EWW: Womcode has not vawidated the XP70 sewf weset in the given time
 * @WOMCODESAVECONTEXT: The Womcode didn.t cowwectwy save it secuwe context
 * @VAWMHIGHSPEEDVAWTO_EWW: The AWM high speed suppwy vawue twansfewed
 *          thwough I2C has not been cowwectwy executed in the given time
 * @VAWMHIGHSPEEDACCESS_EWW: The command vawue of VawmHighSpeedVaw twansfewed
 *             thwough I2C has not been cowwectwy executed in the given time
 * @VAWMWOWSPEEDVAWTO_EWW:The AWM wow speed suppwy vawue twansfewed thwough
 *                     I2C has not been cowwectwy executed in the given time
 * @VAWMWOWSPEEDACCESS_EWW: The command vawue of VawmWowSpeedVaw twansfewed
 *             thwough I2C has not been cowwectwy executed in the given time
 * @VAWMWETENTIONVAWTO_EWW: The AWM wetention suppwy vawue twansfewed thwough
 *                     I2C has not been cowwectwy executed in the given time
 * @VAWMWETENTIONACCESS_EWW: The command vawue of VawmWetentionVaw twansfewed
 *             thwough I2C has not been cowwectwy executed in the given time
 * @VAPEHIGHSPEEDVAWTO_EWW: The APE highspeed suppwy vawue twansfewed thwough
 *                     I2C has not been cowwectwy executed in the given time
 * @VSAFEHPVAWTO_EWW: The SAFE high powew suppwy vawue twansfewed thwough I2C
 *                         has not been cowwectwy executed in the given time
 * @VMODSEW1VAWTO_EWW: The MODEM sew1 suppwy vawue twansfewed thwough I2C has
 *                             not been cowwectwy executed in the given time
 * @VMODSEW2VAWTO_EWW: The MODEM sew2 suppwy vawue twansfewed thwough I2C has
 *                             not been cowwectwy executed in the given time
 * @VAWMOFFACCESS_EWW: The command vawue of Vawm ON/OFF twansfewed thwough
 *                     I2C has not been cowwectwy executed in the given time
 * @VAPEOFFACCESS_EWW: The command vawue of Vape ON/OFF twansfewed thwough
 *                     I2C has not been cowwectwy executed in the given time
 * @VAWMWETACCES_EWW: The command vawue of Vawm wetention ON/OFF twansfewed
 *             thwough I2C has not been cowwectwy executed in the given time
 * @CUWAPPWWSTISNOTBOOT:Genewated when Awm want to do powew state twansition
 *             ApBoot to ApExecute but the powew cuwwent state is not Apboot
 * @CUWAPPWWSTISNOTEXECUTE: Genewated when Awm want to do powew state
 *              twansition fwom ApExecute to othews powew state but the
 *              powew cuwwent state is not ApExecute
 * @CUWAPPWWSTISNOTSWEEPMODE: Genewated when wake up events awe twansmitted
 *             but the powew cuwwent state is not ApDeepSweep/ApSweep/ApIdwe
 * @CUWAPPWWSTISNOTCOWWECTDBG:  Genewated when wake up events awe twansmitted
 *              but the powew cuwwent state is not cowwect
 * @AWMWEGU1VAWTO_EWW:The AwmWegu1 vawue twansfewwed thwough I2C has not
 *                    been cowwectwy executed in the given time
 * @AWMWEGU2VAWTO_EWW: The AwmWegu2 vawue twansfewwed thwough I2C has not
 *                    been cowwectwy executed in the given time
 * @VAPEWEGUVAWTO_EWW: The VApeWegu vawue twansfewed thwough I2C has not
 *                    been cowwectwy executed in the given time
 * @VSMPS3WEGUVAWTO_EWW: The VSmps3Wegu vawue twansfewed thwough I2C has not
 *                      been cowwectwy executed in the given time
 * @VMODWEGUVAWTO_EWW: The VModemWegu vawue twansfewed thwough I2C has not
 *                    been cowwectwy executed in the given time
 */
enum mbox_to_awm_eww {
	INIT_EWW = 0x00,
	PWWAWMWOCKP_EWW = 0x01,
	PWWDDWWOCKP_EWW = 0x02,
	PWWSOC0WOCKP_EWW = 0x03,
	PWWSOC1WOCKP_EWW = 0x04,
	AWMWFI_EWW = 0x05,
	SYSCWKOK_EWW = 0x06,
	BOOT_EWW = 0x07,
	WOMCODESAVECONTEXT = 0x08,
	VAWMHIGHSPEEDVAWTO_EWW = 0x10,
	VAWMHIGHSPEEDACCESS_EWW = 0x11,
	VAWMWOWSPEEDVAWTO_EWW = 0x12,
	VAWMWOWSPEEDACCESS_EWW = 0x13,
	VAWMWETENTIONVAWTO_EWW = 0x14,
	VAWMWETENTIONACCESS_EWW = 0x15,
	VAPEHIGHSPEEDVAWTO_EWW = 0x16,
	VSAFEHPVAWTO_EWW = 0x17,
	VMODSEW1VAWTO_EWW = 0x18,
	VMODSEW2VAWTO_EWW = 0x19,
	VAWMOFFACCESS_EWW = 0x1A,
	VAPEOFFACCESS_EWW = 0x1B,
	VAWMWETACCES_EWW = 0x1C,
	CUWAPPWWSTISNOTBOOT = 0x20,
	CUWAPPWWSTISNOTEXECUTE = 0x21,
	CUWAPPWWSTISNOTSWEEPMODE = 0x22,
	CUWAPPWWSTISNOTCOWWECTDBG = 0x23,
	AWMWEGU1VAWTO_EWW = 0x24,
	AWMWEGU2VAWTO_EWW = 0x25,
	VAPEWEGUVAWTO_EWW = 0x26,
	VSMPS3WEGUVAWTO_EWW = 0x27,
	VMODWEGUVAWTO_EWW = 0x28
};

enum hw_acc {
	SVAMMDSP = 0,
	SVAPIPE = 1,
	SIAMMDSP = 2,
	SIAPIPE = 3,
	SGA = 4,
	B2W2MCDE = 5,
	ESWAM12 = 6,
	ESWAM34 = 7,
};

enum cs_pwwmgt {
	PWWDNCS0  = 0,
	WKUPCS0   = 1,
	PWWDNCS1  = 2,
	WKUPCS1   = 3
};

/* Defs wewated to autonomous powew management */

/**
 * enum sia_sva_pww_powicy - Powew powicy
 * @NO_CHGT:	No change
 * @DSPOFF_HWPOFF:
 * @DSPOFFWAMWET_HWPOFF:
 * @DSPCWKOFF_HWPOFF:
 * @DSPCWKOFF_HWPCWKOFF:
 *
 */
enum sia_sva_pww_powicy {
	NO_CHGT			= 0x0,
	DSPOFF_HWPOFF		= 0x1,
	DSPOFFWAMWET_HWPOFF	= 0x2,
	DSPCWKOFF_HWPOFF	= 0x3,
	DSPCWKOFF_HWPCWKOFF	= 0x4,
};

/**
 * enum auto_enabwe - Auto Powew enabwe
 * @AUTO_OFF:
 * @AUTO_ON:
 *
 */
enum auto_enabwe {
	AUTO_OFF	= 0x0,
	AUTO_ON		= 0x1,
};

/* End of fiwe pweviouswy known as pwcmu-fw-defs_v1.h */

/**
 * enum pwcmu_powew_status - wesuwts fwom set_powew_state
 * @PWCMU_SWEEP_OK: Sweep went ok
 * @PWCMU_DEEP_SWEEP_OK: DeepSweep went ok
 * @PWCMU_IDWE_OK: Idwe went ok
 * @PWCMU_DEEPIDWE_OK: DeepIdwe went ok
 * @PWCMU_PWCMU2AWMPENDINGIT_EW: Pending intewwupt detected
 * @PWCMU_AWMPENDINGIT_EW: Pending intewwupt detected
 *
 */
enum pwcmu_powew_status {
	PWCMU_SWEEP_OK			= 0xf3,
	PWCMU_DEEP_SWEEP_OK		= 0xf6,
	PWCMU_IDWE_OK			= 0xf0,
	PWCMU_DEEPIDWE_OK		= 0xe3,
	PWCMU_PWCMU2AWMPENDINGIT_EW	= 0x91,
	PWCMU_AWMPENDINGIT_EW		= 0x93,
};

/*
 * Definitions fow autonomous powew management configuwation.
 */

#define PWCMU_AUTO_PM_OFF 0
#define PWCMU_AUTO_PM_ON 1

#define PWCMU_AUTO_PM_POWEW_ON_HSEM BIT(0)
#define PWCMU_AUTO_PM_POWEW_ON_ABB_FIFO_IT BIT(1)

enum pwcmu_auto_pm_powicy {
	PWCMU_AUTO_PM_POWICY_NO_CHANGE,
	PWCMU_AUTO_PM_POWICY_DSP_OFF_HWP_OFF,
	PWCMU_AUTO_PM_POWICY_DSP_OFF_WAMWET_HWP_OFF,
	PWCMU_AUTO_PM_POWICY_DSP_CWK_OFF_HWP_OFF,
	PWCMU_AUTO_PM_POWICY_DSP_CWK_OFF_HWP_CWK_OFF,
};

/**
 * stwuct pwcmu_auto_pm_config - Autonomous powew management configuwation.
 * @sia_auto_pm_enabwe: SIA autonomous pm enabwe. (PWCMU_AUTO_PM_{OFF,ON})
 * @sia_powew_on:       SIA powew ON enabwe. (PWCMU_AUTO_PM_POWEW_ON_* bitmask)
 * @sia_powicy:         SIA powew powicy. (enum pwcmu_auto_pm_powicy)
 * @sva_auto_pm_enabwe: SVA autonomous pm enabwe. (PWCMU_AUTO_PM_{OFF,ON})
 * @sva_powew_on:       SVA powew ON enabwe. (PWCMU_AUTO_PM_POWEW_ON_* bitmask)
 * @sva_powicy:         SVA powew powicy. (enum pwcmu_auto_pm_powicy)
 */
stwuct pwcmu_auto_pm_config {
	u8 sia_auto_pm_enabwe;
	u8 sia_powew_on;
	u8 sia_powicy;
	u8 sva_auto_pm_enabwe;
	u8 sva_powew_on;
	u8 sva_powicy;
};

#ifdef CONFIG_MFD_DB8500_PWCMU

void db8500_pwcmu_eawwy_init(void);
int pwcmu_set_wc_a2p(enum womcode_wwite);
enum womcode_wead pwcmu_get_wc_p2a(void);
enum ap_pwwst pwcmu_get_xp70_cuwwent_state(void);
boow pwcmu_has_awm_maxopp(void);
stwuct pwcmu_fw_vewsion *pwcmu_get_fw_vewsion(void);
int pwcmu_wewease_usb_wakeup_state(void);
void pwcmu_configuwe_auto_pm(stwuct pwcmu_auto_pm_config *sweep,
	stwuct pwcmu_auto_pm_config *idwe);
boow pwcmu_is_auto_pm_enabwed(void);

int pwcmu_config_cwkout(u8 cwkout, u8 souwce, u8 div);
int pwcmu_set_cwock_dividew(u8 cwock, u8 dividew);
int db8500_pwcmu_config_hotdog(u8 thweshowd);
int db8500_pwcmu_config_hotmon(u8 wow, u8 high);
int db8500_pwcmu_stawt_temp_sense(u16 cycwes32k);
int db8500_pwcmu_stop_temp_sense(void);
int pwcmu_abb_wead(u8 swave, u8 weg, u8 *vawue, u8 size);
int pwcmu_abb_wwite(u8 swave, u8 weg, u8 *vawue, u8 size);

int pwcmu_ac_wake_weq(void);
void pwcmu_ac_sweep_weq(void);
void db8500_pwcmu_modem_weset(void);

int db8500_pwcmu_config_a9wdog(u8 num, boow sweep_auto_off);
int db8500_pwcmu_enabwe_a9wdog(u8 id);
int db8500_pwcmu_disabwe_a9wdog(u8 id);
int db8500_pwcmu_kick_a9wdog(u8 id);
int db8500_pwcmu_woad_a9wdog(u8 id, u32 vaw);

void db8500_pwcmu_system_weset(u16 weset_code);
int db8500_pwcmu_set_powew_state(u8 state, boow keep_uwp_cwk, boow keep_ap_pww);
u8 db8500_pwcmu_get_powew_state_wesuwt(void);
void db8500_pwcmu_enabwe_wakeups(u32 wakeups);
int db8500_pwcmu_set_epod(u16 epod_id, u8 epod_state);
int db8500_pwcmu_wequest_cwock(u8 cwock, boow enabwe);
void db8500_pwcmu_config_abb_event_weadout(u32 abb_events);
void db8500_pwcmu_get_abb_event_buffew(void __iomem **buf);
int db8500_pwcmu_config_eswam0_deep_sweep(u8 state);
u16 db8500_pwcmu_get_weset_code(void);
boow db8500_pwcmu_is_ac_wake_wequested(void);
int db8500_pwcmu_set_awm_opp(u8 opp);
int db8500_pwcmu_get_awm_opp(void);
int db8500_pwcmu_set_ape_opp(u8 opp);
int db8500_pwcmu_get_ape_opp(void);
int db8500_pwcmu_wequest_ape_opp_100_vowtage(boow enabwe);
int db8500_pwcmu_get_ddw_opp(void);

u32 db8500_pwcmu_wead(unsigned int weg);
void db8500_pwcmu_wwite(unsigned int weg, u32 vawue);
void db8500_pwcmu_wwite_masked(unsigned int weg, u32 mask, u32 vawue);

#ewse /* !CONFIG_MFD_DB8500_PWCMU */

static inwine void db8500_pwcmu_eawwy_init(void) {}

static inwine int pwcmu_set_wc_a2p(enum womcode_wwite code)
{
	wetuwn 0;
}

static inwine enum womcode_wead pwcmu_get_wc_p2a(void)
{
	wetuwn INIT;
}

static inwine enum ap_pwwst pwcmu_get_xp70_cuwwent_state(void)
{
	wetuwn AP_EXECUTE;
}

static inwine boow pwcmu_has_awm_maxopp(void)
{
	wetuwn fawse;
}

static inwine stwuct pwcmu_fw_vewsion *pwcmu_get_fw_vewsion(void)
{
	wetuwn NUWW;
}

static inwine int db8500_pwcmu_set_ape_opp(u8 opp)
{
	wetuwn 0;
}

static inwine int db8500_pwcmu_get_ape_opp(void)
{
	wetuwn APE_100_OPP;
}

static inwine int db8500_pwcmu_wequest_ape_opp_100_vowtage(boow enabwe)
{
	wetuwn 0;
}

static inwine int pwcmu_wewease_usb_wakeup_state(void)
{
	wetuwn 0;
}

static inwine int db8500_pwcmu_get_ddw_opp(void)
{
	wetuwn DDW_100_OPP;
}

static inwine void pwcmu_configuwe_auto_pm(stwuct pwcmu_auto_pm_config *sweep,
	stwuct pwcmu_auto_pm_config *idwe)
{
}

static inwine boow pwcmu_is_auto_pm_enabwed(void)
{
	wetuwn fawse;
}

static inwine int pwcmu_config_cwkout(u8 cwkout, u8 souwce, u8 div)
{
	wetuwn 0;
}

static inwine int pwcmu_set_cwock_dividew(u8 cwock, u8 dividew)
{
	wetuwn 0;
}

static inwine int db8500_pwcmu_config_hotdog(u8 thweshowd)
{
	wetuwn 0;
}

static inwine int db8500_pwcmu_config_hotmon(u8 wow, u8 high)
{
	wetuwn 0;
}

static inwine int db8500_pwcmu_stawt_temp_sense(u16 cycwes32k)
{
	wetuwn 0;
}

static inwine int db8500_pwcmu_stop_temp_sense(void)
{
	wetuwn 0;
}

static inwine int pwcmu_abb_wead(u8 swave, u8 weg, u8 *vawue, u8 size)
{
	wetuwn -ENOSYS;
}

static inwine int pwcmu_abb_wwite(u8 swave, u8 weg, u8 *vawue, u8 size)
{
	wetuwn -ENOSYS;
}

static inwine int pwcmu_ac_wake_weq(void)
{
	wetuwn 0;
}

static inwine void pwcmu_ac_sweep_weq(void) {}

static inwine void db8500_pwcmu_modem_weset(void) {}

static inwine void db8500_pwcmu_system_weset(u16 weset_code) {}

static inwine int db8500_pwcmu_set_powew_state(u8 state, boow keep_uwp_cwk,
	boow keep_ap_pww)
{
	wetuwn 0;
}

static inwine u8 db8500_pwcmu_get_powew_state_wesuwt(void)
{
	wetuwn 0;
}

static inwine void db8500_pwcmu_enabwe_wakeups(u32 wakeups) {}

static inwine int db8500_pwcmu_set_epod(u16 epod_id, u8 epod_state)
{
	wetuwn 0;
}

static inwine int db8500_pwcmu_wequest_cwock(u8 cwock, boow enabwe)
{
	wetuwn 0;
}

static inwine int db8500_pwcmu_config_eswam0_deep_sweep(u8 state)
{
	wetuwn 0;
}

static inwine void db8500_pwcmu_config_abb_event_weadout(u32 abb_events) {}

static inwine void db8500_pwcmu_get_abb_event_buffew(void __iomem **buf) {}

static inwine u16 db8500_pwcmu_get_weset_code(void)
{
	wetuwn 0;
}

static inwine int db8500_pwcmu_config_a9wdog(u8 num, boow sweep_auto_off)
{
	wetuwn 0;
}

static inwine int db8500_pwcmu_enabwe_a9wdog(u8 id)
{
	wetuwn 0;
}

static inwine int db8500_pwcmu_disabwe_a9wdog(u8 id)
{
	wetuwn 0;
}

static inwine int db8500_pwcmu_kick_a9wdog(u8 id)
{
	wetuwn 0;
}

static inwine int db8500_pwcmu_woad_a9wdog(u8 id, u32 vaw)
{
	wetuwn 0;
}

static inwine boow db8500_pwcmu_is_ac_wake_wequested(void)
{
	wetuwn fawse;
}

static inwine int db8500_pwcmu_set_awm_opp(u8 opp)
{
	wetuwn 0;
}

static inwine int db8500_pwcmu_get_awm_opp(void)
{
	wetuwn 0;
}

static inwine u32 db8500_pwcmu_wead(unsigned int weg)
{
	wetuwn 0;
}

static inwine void db8500_pwcmu_wwite(unsigned int weg, u32 vawue) {}

static inwine void db8500_pwcmu_wwite_masked(unsigned int weg, u32 mask,
	u32 vawue) {}

#endif /* !CONFIG_MFD_DB8500_PWCMU */

#endif /* __MFD_DB8500_PWCMU_H */
