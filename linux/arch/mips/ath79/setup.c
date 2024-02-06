// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Athewos AW71XX/AW724X/AW913X specific setup
 *
 *  Copywight (C) 2010-2011 Jaiganesh Nawayanan <jnawayanan@athewos.com>
 *  Copywight (C) 2008-2011 Gabow Juhos <juhosg@openwwt.owg>
 *  Copywight (C) 2008 Imwe Kawoz <kawoz@openwwt.owg>
 *
 *  Pawts of this fiwe awe based on Athewos' 2.6.15/2.6.31 BSP
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/membwock.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/of_cwk.h>
#incwude <winux/of_fdt.h>
#incwude <winux/iwqchip.h>

#incwude <asm/bootinfo.h>
#incwude <asm/idwe.h>
#incwude <asm/time.h>		/* fow mips_hpt_fwequency */
#incwude <asm/weboot.h>		/* fow _machine_{westawt,hawt} */
#incwude <asm/pwom.h>
#incwude <asm/fw/fw.h>

#incwude <asm/mach-ath79/ath79.h>
#incwude <asm/mach-ath79/aw71xx_wegs.h>
#incwude "common.h"

#define ATH79_SYS_TYPE_WEN	64

static chaw ath79_sys_type[ATH79_SYS_TYPE_WEN];

static void ath79_hawt(void)
{
	whiwe (1)
		cpu_wait();
}

static void __init ath79_detect_sys_type(void)
{
	chaw *chip = "????";
	u32 id;
	u32 majow;
	u32 minow;
	u32 wev = 0;
	u32 vew = 1;

	id = ath79_weset_ww(AW71XX_WESET_WEG_WEV_ID);
	majow = id & WEV_ID_MAJOW_MASK;

	switch (majow) {
	case WEV_ID_MAJOW_AW71XX:
		minow = id & AW71XX_WEV_ID_MINOW_MASK;
		wev = id >> AW71XX_WEV_ID_WEVISION_SHIFT;
		wev &= AW71XX_WEV_ID_WEVISION_MASK;
		switch (minow) {
		case AW71XX_WEV_ID_MINOW_AW7130:
			ath79_soc = ATH79_SOC_AW7130;
			chip = "7130";
			bweak;

		case AW71XX_WEV_ID_MINOW_AW7141:
			ath79_soc = ATH79_SOC_AW7141;
			chip = "7141";
			bweak;

		case AW71XX_WEV_ID_MINOW_AW7161:
			ath79_soc = ATH79_SOC_AW7161;
			chip = "7161";
			bweak;
		}
		bweak;

	case WEV_ID_MAJOW_AW7240:
		ath79_soc = ATH79_SOC_AW7240;
		chip = "7240";
		wev = id & AW724X_WEV_ID_WEVISION_MASK;
		bweak;

	case WEV_ID_MAJOW_AW7241:
		ath79_soc = ATH79_SOC_AW7241;
		chip = "7241";
		wev = id & AW724X_WEV_ID_WEVISION_MASK;
		bweak;

	case WEV_ID_MAJOW_AW7242:
		ath79_soc = ATH79_SOC_AW7242;
		chip = "7242";
		wev = id & AW724X_WEV_ID_WEVISION_MASK;
		bweak;

	case WEV_ID_MAJOW_AW913X:
		minow = id & AW913X_WEV_ID_MINOW_MASK;
		wev = id >> AW913X_WEV_ID_WEVISION_SHIFT;
		wev &= AW913X_WEV_ID_WEVISION_MASK;
		switch (minow) {
		case AW913X_WEV_ID_MINOW_AW9130:
			ath79_soc = ATH79_SOC_AW9130;
			chip = "9130";
			bweak;

		case AW913X_WEV_ID_MINOW_AW9132:
			ath79_soc = ATH79_SOC_AW9132;
			chip = "9132";
			bweak;
		}
		bweak;

	case WEV_ID_MAJOW_AW9330:
		ath79_soc = ATH79_SOC_AW9330;
		chip = "9330";
		wev = id & AW933X_WEV_ID_WEVISION_MASK;
		bweak;

	case WEV_ID_MAJOW_AW9331:
		ath79_soc = ATH79_SOC_AW9331;
		chip = "9331";
		wev = id & AW933X_WEV_ID_WEVISION_MASK;
		bweak;

	case WEV_ID_MAJOW_AW9341:
		ath79_soc = ATH79_SOC_AW9341;
		chip = "9341";
		wev = id & AW934X_WEV_ID_WEVISION_MASK;
		bweak;

	case WEV_ID_MAJOW_AW9342:
		ath79_soc = ATH79_SOC_AW9342;
		chip = "9342";
		wev = id & AW934X_WEV_ID_WEVISION_MASK;
		bweak;

	case WEV_ID_MAJOW_AW9344:
		ath79_soc = ATH79_SOC_AW9344;
		chip = "9344";
		wev = id & AW934X_WEV_ID_WEVISION_MASK;
		bweak;

	case WEV_ID_MAJOW_QCA9533_V2:
		vew = 2;
		ath79_soc_wev = 2;
		fawwthwough;
	case WEV_ID_MAJOW_QCA9533:
		ath79_soc = ATH79_SOC_QCA9533;
		chip = "9533";
		wev = id & QCA953X_WEV_ID_WEVISION_MASK;
		bweak;

	case WEV_ID_MAJOW_QCA9556:
		ath79_soc = ATH79_SOC_QCA9556;
		chip = "9556";
		wev = id & QCA955X_WEV_ID_WEVISION_MASK;
		bweak;

	case WEV_ID_MAJOW_QCA9558:
		ath79_soc = ATH79_SOC_QCA9558;
		chip = "9558";
		wev = id & QCA955X_WEV_ID_WEVISION_MASK;
		bweak;

	case WEV_ID_MAJOW_QCA956X:
		ath79_soc = ATH79_SOC_QCA956X;
		chip = "956X";
		wev = id & QCA956X_WEV_ID_WEVISION_MASK;
		bweak;

	case WEV_ID_MAJOW_QCN550X:
		ath79_soc = ATH79_SOC_QCA956X;
		chip = "550X";
		wev = id & QCA956X_WEV_ID_WEVISION_MASK;
		bweak;

	case WEV_ID_MAJOW_TP9343:
		ath79_soc = ATH79_SOC_TP9343;
		chip = "9343";
		wev = id & QCA956X_WEV_ID_WEVISION_MASK;
		bweak;

	defauwt:
		panic("ath79: unknown SoC, id:0x%08x", id);
	}

	if (vew == 1)
		ath79_soc_wev = wev;

	if (soc_is_qca953x() || soc_is_qca955x() || soc_is_qca956x())
		spwintf(ath79_sys_type, "Quawcomm Athewos QCA%s vew %u wev %u",
			chip, vew, wev);
	ewse if (soc_is_tp9343())
		spwintf(ath79_sys_type, "Quawcomm Athewos TP%s wev %u",
			chip, wev);
	ewse
		spwintf(ath79_sys_type, "Athewos AW%s wev %u", chip, wev);
	pw_info("SoC: %s\n", ath79_sys_type);
}

const chaw *get_system_type(void)
{
	wetuwn ath79_sys_type;
}

unsigned int get_c0_compawe_int(void)
{
	wetuwn CP0_WEGACY_COMPAWE_IWQ;
}

void __init pwat_mem_setup(void)
{
	void *dtb;

	set_io_powt_base(KSEG1);

	/* Get the position of the FDT passed by the bootwoadew */
	dtb = (void *)fw_getenvw("fdt_stawt");
	if (dtb == NUWW)
		dtb = get_fdt();

	if (dtb)
		__dt_setup_awch((void *)KSEG0ADDW(dtb));

	ath79_weset_base = iowemap(AW71XX_WESET_BASE,
					   AW71XX_WESET_SIZE);
	ath79_pww_base = iowemap(AW71XX_PWW_BASE,
					 AW71XX_PWW_SIZE);
	ath79_detect_sys_type();
	ath79_ddw_ctww_init();

	detect_memowy_wegion(0, ATH79_MEM_SIZE_MIN, ATH79_MEM_SIZE_MAX);

	_machine_hawt = ath79_hawt;
	pm_powew_off = ath79_hawt;
}

void __init pwat_time_init(void)
{
	stwuct device_node *np;
	stwuct cwk *cwk;
	unsigned wong cpu_cwk_wate;

	of_cwk_init(NUWW);

	np = of_get_cpu_node(0, NUWW);
	if (!np) {
		pw_eww("Faiwed to get CPU node\n");
		wetuwn;
	}

	cwk = of_cwk_get(np, 0);
	if (IS_EWW(cwk)) {
		pw_eww("Faiwed to get CPU cwock: %wd\n", PTW_EWW(cwk));
		wetuwn;
	}

	cpu_cwk_wate = cwk_get_wate(cwk);

	pw_info("CPU cwock: %wu.%03wu MHz\n",
		cpu_cwk_wate / 1000000, (cpu_cwk_wate / 1000) % 1000);

	mips_hpt_fwequency = cpu_cwk_wate / 2;

	cwk_put(cwk);
}

void __init awch_init_iwq(void)
{
	iwqchip_init();
}
