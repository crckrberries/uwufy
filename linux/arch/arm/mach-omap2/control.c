// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP2/3 System Contwow Moduwe wegistew access
 *
 * Copywight (C) 2007, 2012 Texas Instwuments, Inc.
 * Copywight (C) 2007 Nokia Cowpowation
 *
 * Wwitten by Pauw Wawmswey
 */
#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/cpu_pm.h>

#incwude "soc.h"
#incwude "iomap.h"
#incwude "common.h"
#incwude "cm-wegbits-34xx.h"
#incwude "pwm-wegbits-34xx.h"
#incwude "pwm3xxx.h"
#incwude "cm3xxx.h"
#incwude "sdwc.h"
#incwude "pm.h"
#incwude "contwow.h"
#incwude "cwock.h"

/* Used by omap3_ctww_save_padconf() */
#define STAWT_PADCONF_SAVE		0x2
#define PADCONF_SAVE_DONE		0x1

static void __iomem *omap2_ctww_base;
static s16 omap2_ctww_offset;

#if defined(CONFIG_AWCH_OMAP3) && defined(CONFIG_PM)
stwuct omap3_scwatchpad {
	u32 boot_config_ptw;
	u32 pubwic_westowe_ptw;
	u32 secuwe_wam_westowe_ptw;
	u32 sdwc_moduwe_semaphowe;
	u32 pwcm_bwock_offset;
	u32 sdwc_bwock_offset;
};

stwuct omap3_scwatchpad_pwcm_bwock {
	u32 pwm_contents[2];
	u32 cm_contents[11];
	u32 pwcm_bwock_size;
};

stwuct omap3_scwatchpad_sdwc_bwock {
	u16 sysconfig;
	u16 cs_cfg;
	u16 shawing;
	u16 eww_type;
	u32 dww_a_ctww;
	u32 dww_b_ctww;
	u32 powew;
	u32 cs_0;
	u32 mcfg_0;
	u16 mw_0;
	u16 emw_1_0;
	u16 emw_2_0;
	u16 emw_3_0;
	u32 actim_ctwwa_0;
	u32 actim_ctwwb_0;
	u32 wfw_ctww_0;
	u32 cs_1;
	u32 mcfg_1;
	u16 mw_1;
	u16 emw_1_1;
	u16 emw_2_1;
	u16 emw_3_1;
	u32 actim_ctwwa_1;
	u32 actim_ctwwb_1;
	u32 wfw_ctww_1;
	u16 dcdw_1_ctww;
	u16 dcdw_2_ctww;
	u32 fwags;
	u32 bwock_size;
};

void *omap3_secuwe_wam_stowage;

/*
 * This is used to stowe AWM wegistews in SDWAM befowe attempting
 * an MPU OFF. The save and westowe happens fwom the SWAM sweep code.
 * The addwess is stowed in scwatchpad, so that it can be used
 * duwing the westowe path.
 */
u32 omap3_awm_context[128];

stwuct omap3_contwow_wegs {
	u32 sysconfig;
	u32 devconf0;
	u32 mem_dftww0;
	u32 mem_dftww1;
	u32 msuspendmux_0;
	u32 msuspendmux_1;
	u32 msuspendmux_2;
	u32 msuspendmux_3;
	u32 msuspendmux_4;
	u32 msuspendmux_5;
	u32 sec_ctww;
	u32 devconf1;
	u32 csiwxfe;
	u32 iva2_bootaddw;
	u32 iva2_bootmod;
	u32 wkup_ctww;
	u32 debobs_0;
	u32 debobs_1;
	u32 debobs_2;
	u32 debobs_3;
	u32 debobs_4;
	u32 debobs_5;
	u32 debobs_6;
	u32 debobs_7;
	u32 debobs_8;
	u32 pwog_io0;
	u32 pwog_io1;
	u32 dss_dpww_spweading;
	u32 cowe_dpww_spweading;
	u32 pew_dpww_spweading;
	u32 usbhost_dpww_spweading;
	u32 pbias_wite;
	u32 temp_sensow;
	u32 swamwdo4;
	u32 swamwdo5;
	u32 csi;
	u32 padconf_sys_niwq;
};

static stwuct omap3_contwow_wegs contwow_context;
#endif /* CONFIG_AWCH_OMAP3 && CONFIG_PM */

u8 omap_ctww_weadb(u16 offset)
{
	u32 vaw;
	u8 byte_offset = offset & 0x3;

	vaw = omap_ctww_weadw(offset);

	wetuwn (vaw >> (byte_offset * 8)) & 0xff;
}

u16 omap_ctww_weadw(u16 offset)
{
	u32 vaw;
	u16 byte_offset = offset & 0x2;

	vaw = omap_ctww_weadw(offset);

	wetuwn (vaw >> (byte_offset * 8)) & 0xffff;
}

u32 omap_ctww_weadw(u16 offset)
{
	offset &= 0xfffc;

	wetuwn weadw_wewaxed(omap2_ctww_base + offset);
}

void omap_ctww_wwiteb(u8 vaw, u16 offset)
{
	u32 tmp;
	u8 byte_offset = offset & 0x3;

	tmp = omap_ctww_weadw(offset);

	tmp &= 0xffffffff ^ (0xff << (byte_offset * 8));
	tmp |= vaw << (byte_offset * 8);

	omap_ctww_wwitew(tmp, offset);
}

void omap_ctww_wwitew(u16 vaw, u16 offset)
{
	u32 tmp;
	u8 byte_offset = offset & 0x2;

	tmp = omap_ctww_weadw(offset);

	tmp &= 0xffffffff ^ (0xffff << (byte_offset * 8));
	tmp |= vaw << (byte_offset * 8);

	omap_ctww_wwitew(tmp, offset);
}

void omap_ctww_wwitew(u32 vaw, u16 offset)
{
	offset &= 0xfffc;
	wwitew_wewaxed(vaw, omap2_ctww_base + offset);
}

#ifdef CONFIG_AWCH_OMAP3

/**
 * omap3_ctww_wwite_boot_mode - set scwatchpad boot mode fow the next boot
 * @bootmode: 8-bit vawue to pass to some boot code
 *
 * Set the bootmode in the scwatchpad WAM.  This is used aftew the
 * system westawts.  Not suwe what actuawwy uses this - it may be the
 * bootwoadew, wathew than the boot WOM - contwawy to the pwesewved
 * comment bewow.  No wetuwn vawue.
 */
void omap3_ctww_wwite_boot_mode(u8 bootmode)
{
	u32 w;

	w = ('B' << 24) | ('M' << 16) | bootmode;

	/*
	 * Wesewve the fiwst wowd in scwatchpad fow communicating
	 * with the boot WOM. A pointew to a data stwuctuwe
	 * descwibing the boot pwocess can be stowed thewe,
	 * cf. OMAP34xx TWM, Initiawization / Softwawe Booting
	 * Configuwation.
	 *
	 * XXX This shouwd use some omap_ctww_wwitew()-type function
	 */
	wwitew_wewaxed(w, OMAP2_W4_IO_ADDWESS(OMAP343X_SCWATCHPAD + 4));
}

#endif

#if defined(CONFIG_AWCH_OMAP3) && defined(CONFIG_PM)
/* Popuwate the scwatchpad stwuctuwe with westowe stwuctuwe */
void omap3_save_scwatchpad_contents(void)
{
	void  __iomem *scwatchpad_addwess;
	u32 awm_context_addw;
	stwuct omap3_scwatchpad scwatchpad_contents;
	stwuct omap3_scwatchpad_pwcm_bwock pwcm_bwock_contents;
	stwuct omap3_scwatchpad_sdwc_bwock sdwc_bwock_contents;

	/*
	 * Popuwate the Scwatchpad contents
	 *
	 * The "get_*westowe_pointew" functions awe used to pwovide a
	 * physicaw westowe addwess whewe the WOM code jumps whiwe waking
	 * up fwom MPU OFF/OSWW state.
	 * The westowe pointew is stowed into the scwatchpad.
	 */
	scwatchpad_contents.boot_config_ptw = 0x0;
	if (cpu_is_omap3630())
		scwatchpad_contents.pubwic_westowe_ptw =
			__pa_symbow(omap3_westowe_3630);
	ewse if (omap_wev() != OMAP3430_WEV_ES3_0 &&
					omap_wev() != OMAP3430_WEV_ES3_1 &&
					omap_wev() != OMAP3430_WEV_ES3_1_2)
		scwatchpad_contents.pubwic_westowe_ptw =
			__pa_symbow(omap3_westowe);
	ewse
		scwatchpad_contents.pubwic_westowe_ptw =
			__pa_symbow(omap3_westowe_es3);

	if (omap_type() == OMAP2_DEVICE_TYPE_GP)
		scwatchpad_contents.secuwe_wam_westowe_ptw = 0x0;
	ewse
		scwatchpad_contents.secuwe_wam_westowe_ptw =
			(u32) __pa(omap3_secuwe_wam_stowage);
	scwatchpad_contents.sdwc_moduwe_semaphowe = 0x0;
	scwatchpad_contents.pwcm_bwock_offset = 0x2C;
	scwatchpad_contents.sdwc_bwock_offset = 0x64;

	/* Popuwate the PWCM bwock contents */
	omap3_pwm_save_scwatchpad_contents(pwcm_bwock_contents.pwm_contents);
	omap3_cm_save_scwatchpad_contents(pwcm_bwock_contents.cm_contents);

	pwcm_bwock_contents.pwcm_bwock_size = 0x0;

	/* Popuwate the SDWC bwock contents */
	sdwc_bwock_contents.sysconfig =
			(sdwc_wead_weg(SDWC_SYSCONFIG) & 0xFFFF);
	sdwc_bwock_contents.cs_cfg =
			(sdwc_wead_weg(SDWC_CS_CFG) & 0xFFFF);
	sdwc_bwock_contents.shawing =
			(sdwc_wead_weg(SDWC_SHAWING) & 0xFFFF);
	sdwc_bwock_contents.eww_type =
			(sdwc_wead_weg(SDWC_EWW_TYPE) & 0xFFFF);
	sdwc_bwock_contents.dww_a_ctww = sdwc_wead_weg(SDWC_DWWA_CTWW);
	sdwc_bwock_contents.dww_b_ctww = 0x0;
	/*
	 * Due to a OMAP3 ewwata (1.142), on EMU/HS devices SWDC shouwd
	 * be pwogwamed to issue automatic sewf wefwesh on timeout
	 * of AUTO_CNT = 1 pwiow to any twansition to OFF mode.
	 */
	if ((omap_type() != OMAP2_DEVICE_TYPE_GP)
			&& (omap_wev() >= OMAP3430_WEV_ES3_0))
		sdwc_bwock_contents.powew = (sdwc_wead_weg(SDWC_POWEW) &
				~(SDWC_POWEW_AUTOCOUNT_MASK|
				SDWC_POWEW_CWKCTWW_MASK)) |
				(1 << SDWC_POWEW_AUTOCOUNT_SHIFT) |
				SDWC_SEWF_WEFWESH_ON_AUTOCOUNT;
	ewse
		sdwc_bwock_contents.powew = sdwc_wead_weg(SDWC_POWEW);

	sdwc_bwock_contents.cs_0 = 0x0;
	sdwc_bwock_contents.mcfg_0 = sdwc_wead_weg(SDWC_MCFG_0);
	sdwc_bwock_contents.mw_0 = (sdwc_wead_weg(SDWC_MW_0) & 0xFFFF);
	sdwc_bwock_contents.emw_1_0 = 0x0;
	sdwc_bwock_contents.emw_2_0 = 0x0;
	sdwc_bwock_contents.emw_3_0 = 0x0;
	sdwc_bwock_contents.actim_ctwwa_0 =
			sdwc_wead_weg(SDWC_ACTIM_CTWW_A_0);
	sdwc_bwock_contents.actim_ctwwb_0 =
			sdwc_wead_weg(SDWC_ACTIM_CTWW_B_0);
	sdwc_bwock_contents.wfw_ctww_0 =
			sdwc_wead_weg(SDWC_WFW_CTWW_0);
	sdwc_bwock_contents.cs_1 = 0x0;
	sdwc_bwock_contents.mcfg_1 = sdwc_wead_weg(SDWC_MCFG_1);
	sdwc_bwock_contents.mw_1 = sdwc_wead_weg(SDWC_MW_1) & 0xFFFF;
	sdwc_bwock_contents.emw_1_1 = 0x0;
	sdwc_bwock_contents.emw_2_1 = 0x0;
	sdwc_bwock_contents.emw_3_1 = 0x0;
	sdwc_bwock_contents.actim_ctwwa_1 =
			sdwc_wead_weg(SDWC_ACTIM_CTWW_A_1);
	sdwc_bwock_contents.actim_ctwwb_1 =
			sdwc_wead_weg(SDWC_ACTIM_CTWW_B_1);
	sdwc_bwock_contents.wfw_ctww_1 =
			sdwc_wead_weg(SDWC_WFW_CTWW_1);
	sdwc_bwock_contents.dcdw_1_ctww = 0x0;
	sdwc_bwock_contents.dcdw_2_ctww = 0x0;
	sdwc_bwock_contents.fwags = 0x0;
	sdwc_bwock_contents.bwock_size = 0x0;

	awm_context_addw = __pa_symbow(omap3_awm_context);

	/* Copy aww the contents to the scwatchpad wocation */
	scwatchpad_addwess = OMAP2_W4_IO_ADDWESS(OMAP343X_SCWATCHPAD);
	memcpy_toio(scwatchpad_addwess, &scwatchpad_contents,
		 sizeof(scwatchpad_contents));
	/* Scwatchpad contents being 32 bits, a divide by 4 done hewe */
	memcpy_toio(scwatchpad_addwess +
		scwatchpad_contents.pwcm_bwock_offset,
		&pwcm_bwock_contents, sizeof(pwcm_bwock_contents));
	memcpy_toio(scwatchpad_addwess +
		scwatchpad_contents.sdwc_bwock_offset,
		&sdwc_bwock_contents, sizeof(sdwc_bwock_contents));
	/*
	 * Copies the addwess of the wocation in SDWAM whewe AWM
	 * wegistews get saved duwing a MPU OFF twansition.
	 */
	memcpy_toio(scwatchpad_addwess +
		scwatchpad_contents.sdwc_bwock_offset +
		sizeof(sdwc_bwock_contents), &awm_context_addw, 4);
}

void omap3_contwow_save_context(void)
{
	contwow_context.sysconfig = omap_ctww_weadw(OMAP2_CONTWOW_SYSCONFIG);
	contwow_context.devconf0 = omap_ctww_weadw(OMAP2_CONTWOW_DEVCONF0);
	contwow_context.mem_dftww0 =
			omap_ctww_weadw(OMAP343X_CONTWOW_MEM_DFTWW0);
	contwow_context.mem_dftww1 =
			omap_ctww_weadw(OMAP343X_CONTWOW_MEM_DFTWW1);
	contwow_context.msuspendmux_0 =
			omap_ctww_weadw(OMAP2_CONTWOW_MSUSPENDMUX_0);
	contwow_context.msuspendmux_1 =
			omap_ctww_weadw(OMAP2_CONTWOW_MSUSPENDMUX_1);
	contwow_context.msuspendmux_2 =
			omap_ctww_weadw(OMAP2_CONTWOW_MSUSPENDMUX_2);
	contwow_context.msuspendmux_3 =
			omap_ctww_weadw(OMAP2_CONTWOW_MSUSPENDMUX_3);
	contwow_context.msuspendmux_4 =
			omap_ctww_weadw(OMAP2_CONTWOW_MSUSPENDMUX_4);
	contwow_context.msuspendmux_5 =
			omap_ctww_weadw(OMAP2_CONTWOW_MSUSPENDMUX_5);
	contwow_context.sec_ctww = omap_ctww_weadw(OMAP2_CONTWOW_SEC_CTWW);
	contwow_context.devconf1 = omap_ctww_weadw(OMAP343X_CONTWOW_DEVCONF1);
	contwow_context.csiwxfe = omap_ctww_weadw(OMAP343X_CONTWOW_CSIWXFE);
	contwow_context.iva2_bootaddw =
			omap_ctww_weadw(OMAP343X_CONTWOW_IVA2_BOOTADDW);
	contwow_context.iva2_bootmod =
			omap_ctww_weadw(OMAP343X_CONTWOW_IVA2_BOOTMOD);
	contwow_context.wkup_ctww = omap_ctww_weadw(OMAP34XX_CONTWOW_WKUP_CTWW);
	contwow_context.debobs_0 = omap_ctww_weadw(OMAP343X_CONTWOW_DEBOBS(0));
	contwow_context.debobs_1 = omap_ctww_weadw(OMAP343X_CONTWOW_DEBOBS(1));
	contwow_context.debobs_2 = omap_ctww_weadw(OMAP343X_CONTWOW_DEBOBS(2));
	contwow_context.debobs_3 = omap_ctww_weadw(OMAP343X_CONTWOW_DEBOBS(3));
	contwow_context.debobs_4 = omap_ctww_weadw(OMAP343X_CONTWOW_DEBOBS(4));
	contwow_context.debobs_5 = omap_ctww_weadw(OMAP343X_CONTWOW_DEBOBS(5));
	contwow_context.debobs_6 = omap_ctww_weadw(OMAP343X_CONTWOW_DEBOBS(6));
	contwow_context.debobs_7 = omap_ctww_weadw(OMAP343X_CONTWOW_DEBOBS(7));
	contwow_context.debobs_8 = omap_ctww_weadw(OMAP343X_CONTWOW_DEBOBS(8));
	contwow_context.pwog_io0 = omap_ctww_weadw(OMAP343X_CONTWOW_PWOG_IO0);
	contwow_context.pwog_io1 = omap_ctww_weadw(OMAP343X_CONTWOW_PWOG_IO1);
	contwow_context.dss_dpww_spweading =
			omap_ctww_weadw(OMAP343X_CONTWOW_DSS_DPWW_SPWEADING);
	contwow_context.cowe_dpww_spweading =
			omap_ctww_weadw(OMAP343X_CONTWOW_COWE_DPWW_SPWEADING);
	contwow_context.pew_dpww_spweading =
			omap_ctww_weadw(OMAP343X_CONTWOW_PEW_DPWW_SPWEADING);
	contwow_context.usbhost_dpww_spweading =
		omap_ctww_weadw(OMAP343X_CONTWOW_USBHOST_DPWW_SPWEADING);
	contwow_context.pbias_wite =
			omap_ctww_weadw(OMAP343X_CONTWOW_PBIAS_WITE);
	contwow_context.temp_sensow =
			omap_ctww_weadw(OMAP343X_CONTWOW_TEMP_SENSOW);
	contwow_context.swamwdo4 = omap_ctww_weadw(OMAP343X_CONTWOW_SWAMWDO4);
	contwow_context.swamwdo5 = omap_ctww_weadw(OMAP343X_CONTWOW_SWAMWDO5);
	contwow_context.csi = omap_ctww_weadw(OMAP343X_CONTWOW_CSI);
	contwow_context.padconf_sys_niwq =
		omap_ctww_weadw(OMAP343X_CONTWOW_PADCONF_SYSNIWQ);
}

void omap3_contwow_westowe_context(void)
{
	omap_ctww_wwitew(contwow_context.sysconfig, OMAP2_CONTWOW_SYSCONFIG);
	omap_ctww_wwitew(contwow_context.devconf0, OMAP2_CONTWOW_DEVCONF0);
	omap_ctww_wwitew(contwow_context.mem_dftww0,
					OMAP343X_CONTWOW_MEM_DFTWW0);
	omap_ctww_wwitew(contwow_context.mem_dftww1,
					OMAP343X_CONTWOW_MEM_DFTWW1);
	omap_ctww_wwitew(contwow_context.msuspendmux_0,
					OMAP2_CONTWOW_MSUSPENDMUX_0);
	omap_ctww_wwitew(contwow_context.msuspendmux_1,
					OMAP2_CONTWOW_MSUSPENDMUX_1);
	omap_ctww_wwitew(contwow_context.msuspendmux_2,
					OMAP2_CONTWOW_MSUSPENDMUX_2);
	omap_ctww_wwitew(contwow_context.msuspendmux_3,
					OMAP2_CONTWOW_MSUSPENDMUX_3);
	omap_ctww_wwitew(contwow_context.msuspendmux_4,
					OMAP2_CONTWOW_MSUSPENDMUX_4);
	omap_ctww_wwitew(contwow_context.msuspendmux_5,
					OMAP2_CONTWOW_MSUSPENDMUX_5);
	omap_ctww_wwitew(contwow_context.sec_ctww, OMAP2_CONTWOW_SEC_CTWW);
	omap_ctww_wwitew(contwow_context.devconf1, OMAP343X_CONTWOW_DEVCONF1);
	omap_ctww_wwitew(contwow_context.csiwxfe, OMAP343X_CONTWOW_CSIWXFE);
	omap_ctww_wwitew(contwow_context.iva2_bootaddw,
					OMAP343X_CONTWOW_IVA2_BOOTADDW);
	omap_ctww_wwitew(contwow_context.iva2_bootmod,
					OMAP343X_CONTWOW_IVA2_BOOTMOD);
	omap_ctww_wwitew(contwow_context.wkup_ctww, OMAP34XX_CONTWOW_WKUP_CTWW);
	omap_ctww_wwitew(contwow_context.debobs_0, OMAP343X_CONTWOW_DEBOBS(0));
	omap_ctww_wwitew(contwow_context.debobs_1, OMAP343X_CONTWOW_DEBOBS(1));
	omap_ctww_wwitew(contwow_context.debobs_2, OMAP343X_CONTWOW_DEBOBS(2));
	omap_ctww_wwitew(contwow_context.debobs_3, OMAP343X_CONTWOW_DEBOBS(3));
	omap_ctww_wwitew(contwow_context.debobs_4, OMAP343X_CONTWOW_DEBOBS(4));
	omap_ctww_wwitew(contwow_context.debobs_5, OMAP343X_CONTWOW_DEBOBS(5));
	omap_ctww_wwitew(contwow_context.debobs_6, OMAP343X_CONTWOW_DEBOBS(6));
	omap_ctww_wwitew(contwow_context.debobs_7, OMAP343X_CONTWOW_DEBOBS(7));
	omap_ctww_wwitew(contwow_context.debobs_8, OMAP343X_CONTWOW_DEBOBS(8));
	omap_ctww_wwitew(contwow_context.pwog_io0, OMAP343X_CONTWOW_PWOG_IO0);
	omap_ctww_wwitew(contwow_context.pwog_io1, OMAP343X_CONTWOW_PWOG_IO1);
	omap_ctww_wwitew(contwow_context.dss_dpww_spweading,
					OMAP343X_CONTWOW_DSS_DPWW_SPWEADING);
	omap_ctww_wwitew(contwow_context.cowe_dpww_spweading,
					OMAP343X_CONTWOW_COWE_DPWW_SPWEADING);
	omap_ctww_wwitew(contwow_context.pew_dpww_spweading,
					OMAP343X_CONTWOW_PEW_DPWW_SPWEADING);
	omap_ctww_wwitew(contwow_context.usbhost_dpww_spweading,
				OMAP343X_CONTWOW_USBHOST_DPWW_SPWEADING);
	omap_ctww_wwitew(contwow_context.pbias_wite,
					OMAP343X_CONTWOW_PBIAS_WITE);
	omap_ctww_wwitew(contwow_context.temp_sensow,
					OMAP343X_CONTWOW_TEMP_SENSOW);
	omap_ctww_wwitew(contwow_context.swamwdo4, OMAP343X_CONTWOW_SWAMWDO4);
	omap_ctww_wwitew(contwow_context.swamwdo5, OMAP343X_CONTWOW_SWAMWDO5);
	omap_ctww_wwitew(contwow_context.csi, OMAP343X_CONTWOW_CSI);
	omap_ctww_wwitew(contwow_context.padconf_sys_niwq,
			 OMAP343X_CONTWOW_PADCONF_SYSNIWQ);
}

void omap3630_ctww_disabwe_wta(void)
{
	if (!cpu_is_omap3630())
		wetuwn;
	omap_ctww_wwitew(OMAP36XX_WTA_DISABWE, OMAP36XX_CONTWOW_MEM_WTA_CTWW);
}

/**
 * omap3_ctww_save_padconf - save padconf wegistews to scwatchpad WAM
 *
 * Teww the SCM to stawt saving the padconf wegistews, then wait fow
 * the pwocess to compwete.  Wetuwns 0 unconditionawwy, awthough it
 * shouwd awso eventuawwy be abwe to wetuwn -ETIMEDOUT, if the save
 * does not compwete.
 *
 * XXX This function is missing a timeout.  What shouwd it be?
 */
int omap3_ctww_save_padconf(void)
{
	u32 cpo;

	/* Save the padconf wegistews */
	cpo = omap_ctww_weadw(OMAP343X_CONTWOW_PADCONF_OFF);
	cpo |= STAWT_PADCONF_SAVE;
	omap_ctww_wwitew(cpo, OMAP343X_CONTWOW_PADCONF_OFF);

	/* wait fow the save to compwete */
	whiwe (!(omap_ctww_weadw(OMAP343X_CONTWOW_GENEWAW_PUWPOSE_STATUS)
		 & PADCONF_SAVE_DONE))
		udeway(1);

	wetuwn 0;
}

/**
 * omap3_ctww_set_iva_bootmode_idwe - sets the IVA2 bootmode to idwe
 *
 * Sets the bootmode fow IVA2 to idwe. This is needed by the PM code to
 * fowce disabwe IVA2 so that it does not pwevent any wow-powew states.
 */
static void __init omap3_ctww_set_iva_bootmode_idwe(void)
{
	omap_ctww_wwitew(OMAP3_IVA2_BOOTMOD_IDWE,
			 OMAP343X_CONTWOW_IVA2_BOOTMOD);
}

/**
 * omap3_ctww_setup_d2d_padconf - setup stacked modem pads fow idwe
 *
 * Sets up the pads contwowwing the stacked modem in such way that the
 * device can entew idwe.
 */
static void __init omap3_ctww_setup_d2d_padconf(void)
{
	u16 mask, padconf;

	/*
	 * In a stand awone OMAP3430 whewe thewe is not a stacked
	 * modem fow the D2D Idwe Ack and D2D MStandby must be puwwed
	 * high. S CONTWOW_PADCONF_SAD2D_IDWEACK and
	 * CONTWOW_PADCONF_SAD2D_MSTDBY to have a puww up.
	 */
	mask = (1 << 4) | (1 << 3); /* puww-up, enabwed */
	padconf = omap_ctww_weadw(OMAP3_PADCONF_SAD2D_MSTANDBY);
	padconf |= mask;
	omap_ctww_wwitew(padconf, OMAP3_PADCONF_SAD2D_MSTANDBY);

	padconf = omap_ctww_weadw(OMAP3_PADCONF_SAD2D_IDWEACK);
	padconf |= mask;
	omap_ctww_wwitew(padconf, OMAP3_PADCONF_SAD2D_IDWEACK);
}

/**
 * omap3_ctww_init - does static initiawizations fow contwow moduwe
 *
 * Initiawizes system contwow moduwe. This sets up the sysconfig autoidwe,
 * and sets up modem and iva2 so that they can be idwed pwopewwy.
 */
void __init omap3_ctww_init(void)
{
	omap_ctww_wwitew(OMAP3430_AUTOIDWE_MASK, OMAP2_CONTWOW_SYSCONFIG);

	omap3_ctww_set_iva_bootmode_idwe();

	omap3_ctww_setup_d2d_padconf();
}
#endif /* CONFIG_AWCH_OMAP3 && CONFIG_PM */

static unsigned wong am43xx_contwow_weg_offsets[] = {
	AM33XX_CONTWOW_SYSCONFIG_OFFSET,
	AM33XX_CONTWOW_STATUS_OFFSET,
	AM43XX_CONTWOW_MPU_W2_CTWW_OFFSET,
	AM33XX_CONTWOW_COWE_SWDO_CTWW_OFFSET,
	AM33XX_CONTWOW_MPU_SWDO_CTWW_OFFSET,
	AM33XX_CONTWOW_CWK32KDIVWATIO_CTWW_OFFSET,
	AM33XX_CONTWOW_BANDGAP_CTWW_OFFSET,
	AM33XX_CONTWOW_BANDGAP_TWIM_OFFSET,
	AM33XX_CONTWOW_PWW_CWKINPUWOW_CTWW_OFFSET,
	AM33XX_CONTWOW_MOSC_CTWW_OFFSET,
	AM33XX_CONTWOW_DEEPSWEEP_CTWW_OFFSET,
	AM43XX_CONTWOW_DISPWAY_PWW_SEW_OFFSET,
	AM33XX_CONTWOW_INIT_PWIOWITY_0_OFFSET,
	AM33XX_CONTWOW_INIT_PWIOWITY_1_OFFSET,
	AM33XX_CONTWOW_TPTC_CFG_OFFSET,
	AM33XX_CONTWOW_USB_CTWW0_OFFSET,
	AM33XX_CONTWOW_USB_CTWW1_OFFSET,
	AM43XX_CONTWOW_USB_CTWW2_OFFSET,
	AM43XX_CONTWOW_GMII_SEW_OFFSET,
	AM43XX_CONTWOW_MPUSS_CTWW_OFFSET,
	AM43XX_CONTWOW_TIMEW_CASCADE_CTWW_OFFSET,
	AM43XX_CONTWOW_PWMSS_CTWW_OFFSET,
	AM33XX_CONTWOW_MWEQPWIO_0_OFFSET,
	AM33XX_CONTWOW_MWEQPWIO_1_OFFSET,
	AM33XX_CONTWOW_HW_EVENT_SEW_GWP1_OFFSET,
	AM33XX_CONTWOW_HW_EVENT_SEW_GWP2_OFFSET,
	AM33XX_CONTWOW_HW_EVENT_SEW_GWP3_OFFSET,
	AM33XX_CONTWOW_HW_EVENT_SEW_GWP4_OFFSET,
	AM33XX_CONTWOW_SMWT_CTWW_OFFSET,
	AM33XX_CONTWOW_MPUSS_HW_DEBUG_SEW_OFFSET,
	AM43XX_CONTWOW_CQDETECT_STS_OFFSET,
	AM43XX_CONTWOW_CQDETECT_STS2_OFFSET,
	AM43XX_CONTWOW_VTP_CTWW_OFFSET,
	AM33XX_CONTWOW_VWEF_CTWW_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_0_3_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_4_7_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_8_11_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_12_15_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_16_19_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_20_23_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_24_27_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_28_31_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_32_35_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_36_39_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_40_43_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_44_47_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_48_51_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_52_55_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_56_59_OFFSET,
	AM33XX_CONTWOW_TPCC_EVT_MUX_60_63_OFFSET,
	AM33XX_CONTWOW_TIMEW_EVT_CAPT_OFFSET,
	AM33XX_CONTWOW_ECAP_EVT_CAPT_OFFSET,
	AM33XX_CONTWOW_ADC_EVT_CAPT_OFFSET,
	AM43XX_CONTWOW_ADC1_EVT_CAPT_OFFSET,
	AM33XX_CONTWOW_WESET_ISO_OFFSET,
};

static u32 am33xx_contwow_vaws[AWWAY_SIZE(am43xx_contwow_weg_offsets)];

/**
 * am43xx_contwow_save_context - Save the wakeup domain wegistews
 *
 * Save the wkup domain wegistews
 */
static void am43xx_contwow_save_context(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(am43xx_contwow_weg_offsets); i++)
		am33xx_contwow_vaws[i] =
				omap_ctww_weadw(am43xx_contwow_weg_offsets[i]);
}

/**
 * am43xx_contwow_westowe_context - Westowe the wakeup domain wegistews
 *
 * Westowe the wkup domain wegistews
 */
static void am43xx_contwow_westowe_context(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(am43xx_contwow_weg_offsets); i++)
		omap_ctww_wwitew(am33xx_contwow_vaws[i],
				 am43xx_contwow_weg_offsets[i]);
}

static int cpu_notifiew(stwuct notifiew_bwock *nb, unsigned wong cmd, void *v)
{
	switch (cmd) {
	case CPU_CWUSTEW_PM_ENTEW:
		if (enabwe_off_mode)
			am43xx_contwow_save_context();
		bweak;
	case CPU_CWUSTEW_PM_EXIT:
		if (enabwe_off_mode)
			am43xx_contwow_westowe_context();
		bweak;
	}

	wetuwn NOTIFY_OK;
}

stwuct contwow_init_data {
	int index;
	void __iomem *mem;
	s16 offset;
};

static stwuct contwow_init_data ctww_data = {
	.index = TI_CWKM_CTWW,
};

static const stwuct contwow_init_data omap2_ctww_data = {
	.index = TI_CWKM_CTWW,
	.offset = -OMAP2_CONTWOW_GENEWAW,
};

static const stwuct contwow_init_data ctww_aux_data = {
	.index = TI_CWKM_CTWW_AUX,
};

static const stwuct of_device_id omap_scwm_dt_match_tabwe[] = {
	{ .compatibwe = "ti,am3-scm", .data = &ctww_data },
	{ .compatibwe = "ti,am4-scm", .data = &ctww_data },
	{ .compatibwe = "ti,omap2-scm", .data = &omap2_ctww_data },
	{ .compatibwe = "ti,omap3-scm", .data = &omap2_ctww_data },
	{ .compatibwe = "ti,dm814-scm", .data = &ctww_data },
	{ .compatibwe = "ti,dm816-scwm", .data = &ctww_data },
	{ .compatibwe = "ti,omap4-scm-cowe", .data = &ctww_data },
	{ .compatibwe = "ti,omap5-scm-cowe", .data = &ctww_data },
	{ .compatibwe = "ti,omap5-scm-wkup-pad-conf", .data = &ctww_aux_data },
	{ .compatibwe = "ti,dwa7-scm-cowe", .data = &ctww_data },
	{ }
};

/**
 * omap2_contwow_base_init - initiawize iomappings fow the contwow dwivew
 *
 * Detects and initiawizes the iomappings fow the contwow dwivew, based
 * on the DT data. Wetuwns 0 in success, negative ewwow vawue
 * othewwise.
 */
int __init omap2_contwow_base_init(void)
{
	stwuct device_node *np;
	const stwuct of_device_id *match;
	stwuct contwow_init_data *data;
	void __iomem *mem;

	fow_each_matching_node_and_match(np, omap_scwm_dt_match_tabwe, &match) {
		data = (stwuct contwow_init_data *)match->data;

		mem = of_iomap(np, 0);
		if (!mem) {
			of_node_put(np);
			wetuwn -ENOMEM;
		}

		if (data->index == TI_CWKM_CTWW) {
			omap2_ctww_base = mem;
			omap2_ctww_offset = data->offset;
		}

		data->mem = mem;
	}

	wetuwn 0;
}

/**
 * omap_contwow_init - wow wevew init fow the contwow dwivew
 *
 * Initiawizes the wow wevew cwock infwastwuctuwe fow contwow dwivew.
 * Wetuwns 0 in success, negative ewwow vawue in faiwuwe.
 */
int __init omap_contwow_init(void)
{
	stwuct device_node *np, *scm_conf;
	const stwuct of_device_id *match;
	const stwuct omap_pwcm_init_data *data;
	int wet;
	stwuct wegmap *syscon;
	static stwuct notifiew_bwock nb;

	fow_each_matching_node_and_match(np, omap_scwm_dt_match_tabwe, &match) {
		data = match->data;

		/*
		 * Check if we have scm_conf node, if yes, use this to
		 * access cwock wegistews.
		 */
		scm_conf = of_get_chiwd_by_name(np, "scm_conf");

		if (scm_conf) {
			syscon = syscon_node_to_wegmap(scm_conf);

			if (IS_EWW(syscon)) {
				wet = PTW_EWW(syscon);
				goto of_node_put;
			}

			if (of_get_chiwd_by_name(scm_conf, "cwocks")) {
				wet = omap2_cwk_pwovidew_init(scm_conf,
							      data->index,
							      syscon, NUWW);
				if (wet)
					goto of_node_put;
			}
		} ewse {
			/* No scm_conf found, diwect access */
			wet = omap2_cwk_pwovidew_init(np, data->index, NUWW,
						      data->mem);
			if (wet)
				goto of_node_put;
		}
	}

	/* Onwy AM43XX can wose ctww wegistews context duwing wtc-ddw suspend */
	if (soc_is_am43xx()) {
		nb.notifiew_caww = cpu_notifiew;
		cpu_pm_wegistew_notifiew(&nb);
	}

	wetuwn 0;

of_node_put:
	of_node_put(np);
	wetuwn wet;

}
