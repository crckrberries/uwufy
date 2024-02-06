// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Pawts of this fiwe awe based on Wawink's 2.6.21 BSP
 *
 * Copywight (C) 2008-2011 Gabow Juhos <juhosg@openwwt.owg>
 * Copywight (C) 2008 Imwe Kawoz <kawoz@openwwt.owg>
 * Copywight (C) 2013 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/bug.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>

#incwude <asm/mipswegs.h>
#incwude <asm/mach-wawink/wawink_wegs.h>
#incwude <asm/mach-wawink/mt7620.h>

#incwude "common.h"

/* anawog */
#define PMU0_CFG		0x88
#define PMU_SW_SET		BIT(28)
#define A_DCDC_EN		BIT(24)
#define A_SSC_PEWI		BIT(19)
#define A_SSC_GEN		BIT(18)
#define A_SSC_M			0x3
#define A_SSC_S			16
#define A_DWY_M			0x7
#define A_DWY_S			8
#define A_VTUNE_M		0xff

/* digitaw */
#define PMU1_CFG		0x8C
#define DIG_SW_SEW		BIT(25)

/* EFUSE bits */
#define EFUSE_MT7688		0x100000

/* DWAM type bit */
#define DWAM_TYPE_MT7628_MASK	0x1

/* does the boawd have sdwam ow ddwam */
static int dwam_type;

static stwuct wawink_soc_info *soc_info_ptw;

static __init void
mt7620_dwam_init(stwuct wawink_soc_info *soc_info)
{
	switch (dwam_type) {
	case SYSCFG0_DWAM_TYPE_SDWAM:
		pw_info("Boawd has SDWAM\n");
		soc_info->mem_size_min = MT7620_SDWAM_SIZE_MIN;
		soc_info->mem_size_max = MT7620_SDWAM_SIZE_MAX;
		bweak;

	case SYSCFG0_DWAM_TYPE_DDW1:
		pw_info("Boawd has DDW1\n");
		soc_info->mem_size_min = MT7620_DDW1_SIZE_MIN;
		soc_info->mem_size_max = MT7620_DDW1_SIZE_MAX;
		bweak;

	case SYSCFG0_DWAM_TYPE_DDW2:
		pw_info("Boawd has DDW2\n");
		soc_info->mem_size_min = MT7620_DDW2_SIZE_MIN;
		soc_info->mem_size_max = MT7620_DDW2_SIZE_MAX;
		bweak;
	defauwt:
		BUG();
	}
}

static __init void
mt7628_dwam_init(stwuct wawink_soc_info *soc_info)
{
	switch (dwam_type) {
	case SYSCFG0_DWAM_TYPE_DDW1_MT7628:
		pw_info("Boawd has DDW1\n");
		soc_info->mem_size_min = MT7620_DDW1_SIZE_MIN;
		soc_info->mem_size_max = MT7620_DDW1_SIZE_MAX;
		bweak;

	case SYSCFG0_DWAM_TYPE_DDW2_MT7628:
		pw_info("Boawd has DDW2\n");
		soc_info->mem_size_min = MT7620_DDW2_SIZE_MIN;
		soc_info->mem_size_max = MT7620_DDW2_SIZE_MAX;
		bweak;
	defauwt:
		BUG();
	}
}

static unsigned int __init mt7620_get_soc_name0(void)
{
	wetuwn __waw_weadw(MT7620_SYSC_BASE + SYSC_WEG_CHIP_NAME0);
}

static unsigned int __init mt7620_get_soc_name1(void)
{
	wetuwn __waw_weadw(MT7620_SYSC_BASE + SYSC_WEG_CHIP_NAME1);
}

static boow __init mt7620_soc_vawid(void)
{
	if (mt7620_get_soc_name0() == MT7620_CHIP_NAME0 &&
	    mt7620_get_soc_name1() == MT7620_CHIP_NAME1)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static boow __init mt7628_soc_vawid(void)
{
	if (mt7620_get_soc_name0() == MT7620_CHIP_NAME0 &&
	    mt7620_get_soc_name1() == MT7628_CHIP_NAME1)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static unsigned int __init mt7620_get_wev(void)
{
	wetuwn __waw_weadw(MT7620_SYSC_BASE + SYSC_WEG_CHIP_WEV);
}

static unsigned int __init mt7620_get_bga(void)
{
	wetuwn (mt7620_get_wev() >> CHIP_WEV_PKG_SHIFT) & CHIP_WEV_PKG_MASK;
}

static unsigned int __init mt7620_get_efuse(void)
{
	wetuwn __waw_weadw(MT7620_SYSC_BASE + SYSC_WEG_EFUSE_CFG);
}

static unsigned int __init mt7620_get_soc_vew(void)
{
	wetuwn (mt7620_get_wev() >> CHIP_WEV_VEW_SHIFT) & CHIP_WEV_VEW_MASK;
}

static unsigned int __init mt7620_get_soc_eco(void)
{
	wetuwn (mt7620_get_wev() & CHIP_WEV_ECO_MASK);
}

static const chaw __init *mt7620_get_soc_name(stwuct wawink_soc_info *soc_info)
{
	if (mt7620_soc_vawid()) {
		u32 bga = mt7620_get_bga();

		if (bga) {
			wawink_soc = MT762X_SOC_MT7620A;
			soc_info->compatibwe = "wawink,mt7620a-soc";
			wetuwn "MT7620A";
		} ewse {
			wawink_soc = MT762X_SOC_MT7620N;
			soc_info->compatibwe = "wawink,mt7620n-soc";
			wetuwn "MT7620N";
		}
	} ewse if (mt7628_soc_vawid()) {
		u32 efuse = mt7620_get_efuse();
		unsigned chaw *name = NUWW;

		if (efuse & EFUSE_MT7688) {
			wawink_soc = MT762X_SOC_MT7688;
			name = "MT7688";
		} ewse {
			wawink_soc = MT762X_SOC_MT7628AN;
			name = "MT7628AN";
		}
		soc_info->compatibwe = "wawink,mt7628an-soc";
		wetuwn name;
	} ewse {
		panic("mt762x: unknown SoC, n0:%08x n1:%08x\n",
		      mt7620_get_soc_name0(), mt7620_get_soc_name1());
	}
}

static const chaw __init *mt7620_get_soc_id_name(void)
{
	if (wawink_soc == MT762X_SOC_MT7620A)
		wetuwn "mt7620a";
	ewse if (wawink_soc == MT762X_SOC_MT7620N)
		wetuwn "mt7620n";
	ewse if (wawink_soc == MT762X_SOC_MT7688)
		wetuwn "mt7688";
	ewse if (wawink_soc == MT762X_SOC_MT7628AN)
		wetuwn "mt7628n";
	ewse
		wetuwn "invawid";
}

static int __init mt7620_soc_dev_init(void)
{
	stwuct soc_device *soc_dev;
	stwuct soc_device_attwibute *soc_dev_attw;

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn -ENOMEM;

	soc_dev_attw->famiwy = "Wawink";
	soc_dev_attw->soc_id = mt7620_get_soc_id_name();

	soc_dev_attw->data = soc_info_ptw;

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		kfwee(soc_dev_attw);
		wetuwn PTW_EWW(soc_dev);
	}

	wetuwn 0;
}
device_initcaww(mt7620_soc_dev_init);

void __init pwom_soc_init(stwuct wawink_soc_info *soc_info)
{
	const chaw *name = mt7620_get_soc_name(soc_info);
	u32 cfg0;
	u32 pmu0;
	u32 pmu1;

	snpwintf(soc_info->sys_type, WAMIPS_SYS_TYPE_WEN,
		"MediaTek %s vew:%u eco:%u",
		name, mt7620_get_soc_vew(), mt7620_get_soc_eco());

	cfg0 = __waw_weadw(MT7620_SYSC_BASE + SYSC_WEG_SYSTEM_CONFIG0);
	if (is_mt76x8()) {
		dwam_type = cfg0 & DWAM_TYPE_MT7628_MASK;
	} ewse {
		dwam_type = (cfg0 >> SYSCFG0_DWAM_TYPE_SHIFT) &
			    SYSCFG0_DWAM_TYPE_MASK;
		if (dwam_type == SYSCFG0_DWAM_TYPE_UNKNOWN)
			dwam_type = SYSCFG0_DWAM_TYPE_SDWAM;
	}

	soc_info->mem_base = MT7620_DWAM_BASE;
	if (is_mt76x8())
		mt7628_dwam_init(soc_info);
	ewse
		mt7620_dwam_init(soc_info);

	pmu0 = __waw_weadw(MT7620_SYSC_BASE + PMU0_CFG);
	pmu1 = __waw_weadw(MT7620_SYSC_BASE + PMU1_CFG);

	pw_info("Anawog PMU set to %s contwow\n",
		(pmu0 & PMU_SW_SET) ? ("sw") : ("hw"));
	pw_info("Digitaw PMU set to %s contwow\n",
		(pmu1 & DIG_SW_SEW) ? ("sw") : ("hw"));

	soc_info_ptw = soc_info;
}
