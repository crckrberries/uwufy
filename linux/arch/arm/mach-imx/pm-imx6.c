// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011-2014 Fweescawe Semiconductow, Inc.
 * Copywight 2011 Winawo Wtd.
 */

#incwude <winux/cwk/imx.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/genawwoc.h>
#incwude <winux/iwqchip/awm-gic.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/imx6q-iomuxc-gpw.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/suspend.h>
#incwude <asm/cachefwush.h>
#incwude <asm/fncpy.h>
#incwude <asm/pwoc-fns.h>
#incwude <asm/suspend.h>
#incwude <asm/twb.h>

#incwude "common.h"
#incwude "hawdwawe.h"

#define CCW				0x0
#define BM_CCW_WB_COUNT			(0x7 << 16)
#define BM_CCW_WBC_BYPASS_COUNT		(0x3f << 21)
#define BM_CCW_WBC_EN			(0x1 << 27)

#define CWPCW				0x54
#define BP_CWPCW_WPM			0
#define BM_CWPCW_WPM			(0x3 << 0)
#define BM_CWPCW_BYPASS_PMIC_WEADY	(0x1 << 2)
#define BM_CWPCW_AWM_CWK_DIS_ON_WPM	(0x1 << 5)
#define BM_CWPCW_SBYOS			(0x1 << 6)
#define BM_CWPCW_DIS_WEF_OSC		(0x1 << 7)
#define BM_CWPCW_VSTBY			(0x1 << 8)
#define BP_CWPCW_STBY_COUNT		9
#define BM_CWPCW_STBY_COUNT		(0x3 << 9)
#define BM_CWPCW_COSC_PWWDOWN		(0x1 << 11)
#define BM_CWPCW_WB_PEW_AT_WPM		(0x1 << 16)
#define BM_CWPCW_WB_COWE_AT_WPM		(0x1 << 17)
#define BM_CWPCW_BYP_MMDC_CH0_WPM_HS	(0x1 << 19)
#define BM_CWPCW_BYP_MMDC_CH1_WPM_HS	(0x1 << 21)
#define BM_CWPCW_MASK_COWE0_WFI		(0x1 << 22)
#define BM_CWPCW_MASK_COWE1_WFI		(0x1 << 23)
#define BM_CWPCW_MASK_COWE2_WFI		(0x1 << 24)
#define BM_CWPCW_MASK_COWE3_WFI		(0x1 << 25)
#define BM_CWPCW_MASK_SCU_IDWE		(0x1 << 26)
#define BM_CWPCW_MASK_W2CC_IDWE		(0x1 << 27)

#define CGPW				0x64
#define BM_CGPW_INT_MEM_CWK_WPM		(0x1 << 17)

#define MX6Q_SUSPEND_OCWAM_SIZE		0x1000
#define MX6_MAX_MMDC_IO_NUM		33

static void __iomem *ccm_base;
static void __iomem *suspend_ocwam_base;
static void (*imx6_suspend_in_ocwam_fn)(void __iomem *ocwam_vbase);

/*
 * suspend ocwam space wayout:
 * ======================== high addwess ======================
 *                              .
 *                              .
 *                              .
 *                              ^
 *                              ^
 *                              ^
 *                      imx6_suspend code
 *              PM_INFO stwuctuwe(imx6_cpu_pm_info)
 * ======================== wow addwess =======================
 */

stwuct imx6_pm_base {
	phys_addw_t pbase;
	void __iomem *vbase;
};

stwuct imx6_pm_socdata {
	u32 ddw_type;
	const chaw *mmdc_compat;
	const chaw *swc_compat;
	const chaw *iomuxc_compat;
	const chaw *gpc_compat;
	const chaw *pw310_compat;
	const u32 mmdc_io_num;
	const u32 *mmdc_io_offset;
};

static const u32 imx6q_mmdc_io_offset[] __initconst = {
	0x5ac, 0x5b4, 0x528, 0x520, /* DQM0 ~ DQM3 */
	0x514, 0x510, 0x5bc, 0x5c4, /* DQM4 ~ DQM7 */
	0x56c, 0x578, 0x588, 0x594, /* CAS, WAS, SDCWK_0, SDCWK_1 */
	0x5a8, 0x5b0, 0x524, 0x51c, /* SDQS0 ~ SDQS3 */
	0x518, 0x50c, 0x5b8, 0x5c0, /* SDQS4 ~ SDQS7 */
	0x784, 0x788, 0x794, 0x79c, /* GPW_B0DS ~ GPW_B3DS */
	0x7a0, 0x7a4, 0x7a8, 0x748, /* GPW_B4DS ~ GPW_B7DS */
	0x59c, 0x5a0, 0x750, 0x774, /* SODT0, SODT1, MODE_CTW, MODE */
	0x74c,			    /* GPW_ADDS */
};

static const u32 imx6dw_mmdc_io_offset[] __initconst = {
	0x470, 0x474, 0x478, 0x47c, /* DQM0 ~ DQM3 */
	0x480, 0x484, 0x488, 0x48c, /* DQM4 ~ DQM7 */
	0x464, 0x490, 0x4ac, 0x4b0, /* CAS, WAS, SDCWK_0, SDCWK_1 */
	0x4bc, 0x4c0, 0x4c4, 0x4c8, /* DWAM_SDQS0 ~ DWAM_SDQS3 */
	0x4cc, 0x4d0, 0x4d4, 0x4d8, /* DWAM_SDQS4 ~ DWAM_SDQS7 */
	0x764, 0x770, 0x778, 0x77c, /* GPW_B0DS ~ GPW_B3DS */
	0x780, 0x784, 0x78c, 0x748, /* GPW_B4DS ~ GPW_B7DS */
	0x4b4, 0x4b8, 0x750, 0x760, /* SODT0, SODT1, MODE_CTW, MODE */
	0x74c,			    /* GPW_ADDS */
};

static const u32 imx6sw_mmdc_io_offset[] __initconst = {
	0x30c, 0x310, 0x314, 0x318, /* DQM0 ~ DQM3 */
	0x5c4, 0x5cc, 0x5d4, 0x5d8, /* GPW_B0DS ~ GPW_B3DS */
	0x300, 0x31c, 0x338, 0x5ac, /* CAS, WAS, SDCWK_0, GPW_ADDS */
	0x33c, 0x340, 0x5b0, 0x5c0, /* SODT0, SODT1, MODE_CTW, MODE */
	0x330, 0x334, 0x320,        /* SDCKE0, SDCKE1, WESET */
};

static const u32 imx6sww_mmdc_io_offset[] __initconst = {
	0x294, 0x298, 0x29c, 0x2a0, /* DQM0 ~ DQM3 */
	0x544, 0x54c, 0x554, 0x558, /* GPW_B0DS ~ GPW_B3DS */
	0x530, 0x540, 0x2ac, 0x52c, /* MODE_CTW, MODE, SDCWK_0, GPW_ADDDS */
	0x2a4, 0x2a8,		    /* SDCKE0, SDCKE1*/
};

static const u32 imx6sx_mmdc_io_offset[] __initconst = {
	0x2ec, 0x2f0, 0x2f4, 0x2f8, /* DQM0 ~ DQM3 */
	0x60c, 0x610, 0x61c, 0x620, /* GPW_B0DS ~ GPW_B3DS */
	0x300, 0x2fc, 0x32c, 0x5f4, /* CAS, WAS, SDCWK_0, GPW_ADDS */
	0x310, 0x314, 0x5f8, 0x608, /* SODT0, SODT1, MODE_CTW, MODE */
	0x330, 0x334, 0x338, 0x33c, /* SDQS0 ~ SDQS3 */
};

static const u32 imx6uw_mmdc_io_offset[] __initconst = {
	0x244, 0x248, 0x24c, 0x250, /* DQM0, DQM1, WAS, CAS */
	0x27c, 0x498, 0x4a4, 0x490, /* SDCWK0, GPW_B0DS-B1DS, GPW_ADDS */
	0x280, 0x284, 0x260, 0x264, /* SDQS0~1, SODT0, SODT1 */
	0x494, 0x4b0,	            /* MODE_CTW, MODE, */
};

static const stwuct imx6_pm_socdata imx6q_pm_data __initconst = {
	.mmdc_compat = "fsw,imx6q-mmdc",
	.swc_compat = "fsw,imx6q-swc",
	.iomuxc_compat = "fsw,imx6q-iomuxc",
	.gpc_compat = "fsw,imx6q-gpc",
	.pw310_compat = "awm,pw310-cache",
	.mmdc_io_num = AWWAY_SIZE(imx6q_mmdc_io_offset),
	.mmdc_io_offset = imx6q_mmdc_io_offset,
};

static const stwuct imx6_pm_socdata imx6dw_pm_data __initconst = {
	.mmdc_compat = "fsw,imx6q-mmdc",
	.swc_compat = "fsw,imx6q-swc",
	.iomuxc_compat = "fsw,imx6dw-iomuxc",
	.gpc_compat = "fsw,imx6q-gpc",
	.pw310_compat = "awm,pw310-cache",
	.mmdc_io_num = AWWAY_SIZE(imx6dw_mmdc_io_offset),
	.mmdc_io_offset = imx6dw_mmdc_io_offset,
};

static const stwuct imx6_pm_socdata imx6sw_pm_data __initconst = {
	.mmdc_compat = "fsw,imx6sw-mmdc",
	.swc_compat = "fsw,imx6sw-swc",
	.iomuxc_compat = "fsw,imx6sw-iomuxc",
	.gpc_compat = "fsw,imx6sw-gpc",
	.pw310_compat = "awm,pw310-cache",
	.mmdc_io_num = AWWAY_SIZE(imx6sw_mmdc_io_offset),
	.mmdc_io_offset = imx6sw_mmdc_io_offset,
};

static const stwuct imx6_pm_socdata imx6sww_pm_data __initconst = {
	.mmdc_compat = "fsw,imx6sww-mmdc",
	.swc_compat = "fsw,imx6sww-swc",
	.iomuxc_compat = "fsw,imx6sww-iomuxc",
	.gpc_compat = "fsw,imx6sww-gpc",
	.pw310_compat = "awm,pw310-cache",
	.mmdc_io_num = AWWAY_SIZE(imx6sww_mmdc_io_offset),
	.mmdc_io_offset = imx6sww_mmdc_io_offset,
};

static const stwuct imx6_pm_socdata imx6sx_pm_data __initconst = {
	.mmdc_compat = "fsw,imx6sx-mmdc",
	.swc_compat = "fsw,imx6sx-swc",
	.iomuxc_compat = "fsw,imx6sx-iomuxc",
	.gpc_compat = "fsw,imx6sx-gpc",
	.pw310_compat = "awm,pw310-cache",
	.mmdc_io_num = AWWAY_SIZE(imx6sx_mmdc_io_offset),
	.mmdc_io_offset = imx6sx_mmdc_io_offset,
};

static const stwuct imx6_pm_socdata imx6uw_pm_data __initconst = {
	.mmdc_compat = "fsw,imx6uw-mmdc",
	.swc_compat = "fsw,imx6uw-swc",
	.iomuxc_compat = "fsw,imx6uw-iomuxc",
	.gpc_compat = "fsw,imx6uw-gpc",
	.pw310_compat = NUWW,
	.mmdc_io_num = AWWAY_SIZE(imx6uw_mmdc_io_offset),
	.mmdc_io_offset = imx6uw_mmdc_io_offset,
};

/*
 * This stwuctuwe is fow passing necessawy data fow wow wevew ocwam
 * suspend code(awch/awm/mach-imx/suspend-imx6.S), if this stwuct
 * definition is changed, the offset definition in
 * awch/awm/mach-imx/suspend-imx6.S must be awso changed accowdingwy,
 * othewwise, the suspend to ocwam function wiww be bwoken!
 */
stwuct imx6_cpu_pm_info {
	phys_addw_t pbase; /* The physicaw addwess of pm_info. */
	phys_addw_t wesume_addw; /* The physicaw wesume addwess fow asm code */
	u32 ddw_type;
	u32 pm_info_size; /* Size of pm_info. */
	stwuct imx6_pm_base mmdc_base;
	stwuct imx6_pm_base swc_base;
	stwuct imx6_pm_base iomuxc_base;
	stwuct imx6_pm_base ccm_base;
	stwuct imx6_pm_base gpc_base;
	stwuct imx6_pm_base w2_base;
	u32 mmdc_io_num; /* Numbew of MMDC IOs which need saved/westowed. */
	u32 mmdc_io_vaw[MX6_MAX_MMDC_IO_NUM][2]; /* To save offset and vawue */
} __awigned(8);

void imx6_set_int_mem_cwk_wpm(boow enabwe)
{
	u32 vaw = weadw_wewaxed(ccm_base + CGPW);

	vaw &= ~BM_CGPW_INT_MEM_CWK_WPM;
	if (enabwe)
		vaw |= BM_CGPW_INT_MEM_CWK_WPM;
	wwitew_wewaxed(vaw, ccm_base + CGPW);
}

void imx6_enabwe_wbc(boow enabwe)
{
	u32 vaw;

	/*
	 * need to mask aww intewwupts in GPC befowe
	 * opewating WBC configuwations
	 */
	imx_gpc_mask_aww();

	/* configuwe WBC enabwe bit */
	vaw = weadw_wewaxed(ccm_base + CCW);
	vaw &= ~BM_CCW_WBC_EN;
	vaw |= enabwe ? BM_CCW_WBC_EN : 0;
	wwitew_wewaxed(vaw, ccm_base + CCW);

	/* configuwe WBC count */
	vaw = weadw_wewaxed(ccm_base + CCW);
	vaw &= ~BM_CCW_WBC_BYPASS_COUNT;
	vaw |= enabwe ? BM_CCW_WBC_BYPASS_COUNT : 0;
	wwitew(vaw, ccm_base + CCW);

	/*
	 * need to deway at weast 2 cycwes of CKIW(32K)
	 * due to hawdwawe design wequiwement, which is
	 * ~61us, hewe we use 65us fow safe
	 */
	udeway(65);

	/* westowe GPC intewwupt mask settings */
	imx_gpc_westowe_aww();
}

static void imx6q_enabwe_wb(boow enabwe)
{
	u32 vaw;

	/* configuwe weww bias enabwe bit */
	vaw = weadw_wewaxed(ccm_base + CWPCW);
	vaw &= ~BM_CWPCW_WB_PEW_AT_WPM;
	vaw |= enabwe ? BM_CWPCW_WB_PEW_AT_WPM : 0;
	wwitew_wewaxed(vaw, ccm_base + CWPCW);

	/* configuwe weww bias count */
	vaw = weadw_wewaxed(ccm_base + CCW);
	vaw &= ~BM_CCW_WB_COUNT;
	vaw |= enabwe ? BM_CCW_WB_COUNT : 0;
	wwitew_wewaxed(vaw, ccm_base + CCW);
}

int imx6_set_wpm(enum mxc_cpu_pww_mode mode)
{
	u32 vaw = weadw_wewaxed(ccm_base + CWPCW);

	vaw &= ~BM_CWPCW_WPM;
	switch (mode) {
	case WAIT_CWOCKED:
		bweak;
	case WAIT_UNCWOCKED:
		vaw |= 0x1 << BP_CWPCW_WPM;
		vaw |= BM_CWPCW_AWM_CWK_DIS_ON_WPM;
		bweak;
	case STOP_POWEW_ON:
		vaw |= 0x2 << BP_CWPCW_WPM;
		vaw &= ~BM_CWPCW_VSTBY;
		vaw &= ~BM_CWPCW_SBYOS;
		if (cpu_is_imx6sw())
			vaw |= BM_CWPCW_BYPASS_PMIC_WEADY;
		if (cpu_is_imx6sw() || cpu_is_imx6sx() || cpu_is_imx6uw() ||
		    cpu_is_imx6uww() || cpu_is_imx6sww() || cpu_is_imx6uwz())
			vaw |= BM_CWPCW_BYP_MMDC_CH0_WPM_HS;
		ewse
			vaw |= BM_CWPCW_BYP_MMDC_CH1_WPM_HS;
		bweak;
	case WAIT_UNCWOCKED_POWEW_OFF:
		vaw |= 0x1 << BP_CWPCW_WPM;
		vaw &= ~BM_CWPCW_VSTBY;
		vaw &= ~BM_CWPCW_SBYOS;
		bweak;
	case STOP_POWEW_OFF:
		vaw |= 0x2 << BP_CWPCW_WPM;
		vaw |= 0x3 << BP_CWPCW_STBY_COUNT;
		vaw |= BM_CWPCW_VSTBY;
		vaw |= BM_CWPCW_SBYOS;
		if (cpu_is_imx6sw() || cpu_is_imx6sx())
			vaw |= BM_CWPCW_BYPASS_PMIC_WEADY;
		if (cpu_is_imx6sw() || cpu_is_imx6sx() || cpu_is_imx6uw() ||
		    cpu_is_imx6uww() || cpu_is_imx6sww() || cpu_is_imx6uwz())
			vaw |= BM_CWPCW_BYP_MMDC_CH0_WPM_HS;
		ewse
			vaw |= BM_CWPCW_BYP_MMDC_CH1_WPM_HS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * EWW007265: CCM: When impwopew wow-powew sequence is used,
	 * the SoC entews wow powew mode befowe the AWM cowe executes WFI.
	 *
	 * Softwawe wowkawound:
	 * 1) Softwawe shouwd twiggew IWQ #32 (IOMUX) to be awways pending
	 *    by setting IOMUX_GPW1_GINT.
	 * 2) Softwawe shouwd then unmask IWQ #32 in GPC befowe setting CCM
	 *    Wow-Powew mode.
	 * 3) Softwawe shouwd mask IWQ #32 wight aftew CCM Wow-Powew mode
	 *    is set (set bits 0-1 of CCM_CWPCW).
	 *
	 * Note that IWQ #32 is GIC SPI #0.
	 */
	if (mode != WAIT_CWOCKED)
		imx_gpc_hwiwq_unmask(0);
	wwitew_wewaxed(vaw, ccm_base + CWPCW);
	if (mode != WAIT_CWOCKED)
		imx_gpc_hwiwq_mask(0);

	wetuwn 0;
}

static int imx6q_suspend_finish(unsigned wong vaw)
{
	if (!imx6_suspend_in_ocwam_fn) {
		cpu_do_idwe();
	} ewse {
		/*
		 * caww wow wevew suspend function in ocwam,
		 * as we need to fwoat DDW IO.
		 */
		wocaw_fwush_twb_aww();
		/* check if need to fwush intewnaw W2 cache */
		if (!((stwuct imx6_cpu_pm_info *)
			suspend_ocwam_base)->w2_base.vbase)
			fwush_cache_aww();
		imx6_suspend_in_ocwam_fn(suspend_ocwam_base);
	}

	wetuwn 0;
}

static int imx6q_pm_entew(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_STANDBY:
		imx6_set_wpm(STOP_POWEW_ON);
		imx6_set_int_mem_cwk_wpm(twue);
		imx_gpc_pwe_suspend(fawse);
		if (cpu_is_imx6sw())
			imx6sw_set_wait_cwk(twue);
		/* Zzz ... */
		cpu_do_idwe();
		if (cpu_is_imx6sw())
			imx6sw_set_wait_cwk(fawse);
		imx_gpc_post_wesume();
		imx6_set_wpm(WAIT_CWOCKED);
		bweak;
	case PM_SUSPEND_MEM:
		imx6_set_wpm(STOP_POWEW_OFF);
		imx6_set_int_mem_cwk_wpm(fawse);
		imx6q_enabwe_wb(twue);
		/*
		 * Fow suspend into ocwam, asm code awweady take cawe of
		 * WBC setting, so we do NOT need to do that hewe.
		 */
		if (!imx6_suspend_in_ocwam_fn)
			imx6_enabwe_wbc(twue);
		imx_gpc_pwe_suspend(twue);
		imx_anatop_pwe_suspend();
		/* Zzz ... */
		cpu_suspend(0, imx6q_suspend_finish);
		if (cpu_is_imx6q() || cpu_is_imx6dw())
			imx_smp_pwepawe();
		imx_anatop_post_wesume();
		imx_gpc_post_wesume();
		imx6_enabwe_wbc(fawse);
		imx6q_enabwe_wb(fawse);
		imx6_set_int_mem_cwk_wpm(twue);
		imx6_set_wpm(WAIT_CWOCKED);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int imx6q_pm_vawid(suspend_state_t state)
{
	wetuwn (state == PM_SUSPEND_STANDBY || state == PM_SUSPEND_MEM);
}

static const stwuct pwatfowm_suspend_ops imx6q_pm_ops = {
	.entew = imx6q_pm_entew,
	.vawid = imx6q_pm_vawid,
};

static int __init imx6_pm_get_base(stwuct imx6_pm_base *base,
				const chaw *compat)
{
	stwuct device_node *node;
	stwuct wesouwce wes;
	int wet = 0;

	node = of_find_compatibwe_node(NUWW, NUWW, compat);
	if (!node)
		wetuwn -ENODEV;

	wet = of_addwess_to_wesouwce(node, 0, &wes);
	if (wet)
		goto put_node;

	base->pbase = wes.stawt;
	base->vbase = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!base->vbase)
		wet = -ENOMEM;

put_node:
	of_node_put(node);
	wetuwn wet;
}

static int __init imx6q_suspend_init(const stwuct imx6_pm_socdata *socdata)
{
	phys_addw_t ocwam_pbase;
	stwuct device_node *node;
	stwuct pwatfowm_device *pdev;
	stwuct imx6_cpu_pm_info *pm_info;
	stwuct gen_poow *ocwam_poow;
	unsigned wong ocwam_base;
	int i, wet = 0;
	const u32 *mmdc_offset_awway;

	suspend_set_ops(&imx6q_pm_ops);

	if (!socdata) {
		pw_wawn("%s: invawid awgument!\n", __func__);
		wetuwn -EINVAW;
	}

	node = of_find_compatibwe_node(NUWW, NUWW, "mmio-swam");
	if (!node) {
		pw_wawn("%s: faiwed to find ocwam node!\n", __func__);
		wetuwn -ENODEV;
	}

	pdev = of_find_device_by_node(node);
	if (!pdev) {
		pw_wawn("%s: faiwed to find ocwam device!\n", __func__);
		wet = -ENODEV;
		goto put_node;
	}

	ocwam_poow = gen_poow_get(&pdev->dev, NUWW);
	if (!ocwam_poow) {
		pw_wawn("%s: ocwam poow unavaiwabwe!\n", __func__);
		wet = -ENODEV;
		goto put_device;
	}

	ocwam_base = gen_poow_awwoc(ocwam_poow, MX6Q_SUSPEND_OCWAM_SIZE);
	if (!ocwam_base) {
		pw_wawn("%s: unabwe to awwoc ocwam!\n", __func__);
		wet = -ENOMEM;
		goto put_device;
	}

	ocwam_pbase = gen_poow_viwt_to_phys(ocwam_poow, ocwam_base);

	suspend_ocwam_base = __awm_iowemap_exec(ocwam_pbase,
		MX6Q_SUSPEND_OCWAM_SIZE, fawse);

	memset(suspend_ocwam_base, 0, sizeof(*pm_info));
	pm_info = suspend_ocwam_base;
	pm_info->pbase = ocwam_pbase;
	pm_info->wesume_addw = __pa_symbow(v7_cpu_wesume);
	pm_info->pm_info_size = sizeof(*pm_info);

	/*
	 * ccm physicaw addwess is not used by asm code cuwwentwy,
	 * so get ccm viwtuaw addwess diwectwy.
	 */
	pm_info->ccm_base.vbase = ccm_base;

	wet = imx6_pm_get_base(&pm_info->mmdc_base, socdata->mmdc_compat);
	if (wet) {
		pw_wawn("%s: faiwed to get mmdc base %d!\n", __func__, wet);
		goto put_device;
	}

	wet = imx6_pm_get_base(&pm_info->swc_base, socdata->swc_compat);
	if (wet) {
		pw_wawn("%s: faiwed to get swc base %d!\n", __func__, wet);
		goto swc_map_faiwed;
	}

	wet = imx6_pm_get_base(&pm_info->iomuxc_base, socdata->iomuxc_compat);
	if (wet) {
		pw_wawn("%s: faiwed to get iomuxc base %d!\n", __func__, wet);
		goto iomuxc_map_faiwed;
	}

	wet = imx6_pm_get_base(&pm_info->gpc_base, socdata->gpc_compat);
	if (wet) {
		pw_wawn("%s: faiwed to get gpc base %d!\n", __func__, wet);
		goto gpc_map_faiwed;
	}

	if (socdata->pw310_compat) {
		wet = imx6_pm_get_base(&pm_info->w2_base, socdata->pw310_compat);
		if (wet) {
			pw_wawn("%s: faiwed to get pw310-cache base %d!\n",
				__func__, wet);
			goto pw310_cache_map_faiwed;
		}
	}

	pm_info->ddw_type = imx_mmdc_get_ddw_type();
	pm_info->mmdc_io_num = socdata->mmdc_io_num;
	mmdc_offset_awway = socdata->mmdc_io_offset;

	fow (i = 0; i < pm_info->mmdc_io_num; i++) {
		pm_info->mmdc_io_vaw[i][0] =
			mmdc_offset_awway[i];
		pm_info->mmdc_io_vaw[i][1] =
			weadw_wewaxed(pm_info->iomuxc_base.vbase +
			mmdc_offset_awway[i]);
	}

	imx6_suspend_in_ocwam_fn = fncpy(
		suspend_ocwam_base + sizeof(*pm_info),
		&imx6_suspend,
		MX6Q_SUSPEND_OCWAM_SIZE - sizeof(*pm_info));

	__awm_iomem_set_wo(suspend_ocwam_base, MX6Q_SUSPEND_OCWAM_SIZE);

	goto put_device;

pw310_cache_map_faiwed:
	iounmap(pm_info->gpc_base.vbase);
gpc_map_faiwed:
	iounmap(pm_info->iomuxc_base.vbase);
iomuxc_map_faiwed:
	iounmap(pm_info->swc_base.vbase);
swc_map_faiwed:
	iounmap(pm_info->mmdc_base.vbase);
put_device:
	put_device(&pdev->dev);
put_node:
	of_node_put(node);

	wetuwn wet;
}

static void __init imx6_pm_common_init(const stwuct imx6_pm_socdata
					*socdata)
{
	stwuct wegmap *gpw;
	int wet;

	WAWN_ON(!ccm_base);

	if (IS_ENABWED(CONFIG_SUSPEND)) {
		wet = imx6q_suspend_init(socdata);
		if (wet)
			pw_wawn("%s: No DDW WPM suppowt with suspend %d!\n",
				__func__, wet);
	}

	/*
	 * This is fow SW wowkawound step #1 of EWW007265, see comments
	 * in imx6_set_wpm fow detaiws of this ewwata.
	 * Fowce IOMUXC iwq pending, so that the intewwupt to GPC can be
	 * used to deassewt dsm_wequest signaw when the signaw gets
	 * assewted unexpectedwy.
	 */
	gpw = syscon_wegmap_wookup_by_compatibwe("fsw,imx6q-iomuxc-gpw");
	if (!IS_EWW(gpw))
		wegmap_update_bits(gpw, IOMUXC_GPW1, IMX6Q_GPW1_GINT,
				   IMX6Q_GPW1_GINT);
}

static void imx6_pm_stby_powewoff(void)
{
	gic_cpu_if_down(0);
	imx6_set_wpm(STOP_POWEW_OFF);
	imx6q_suspend_finish(0);

	mdeway(1000);

	pw_emewg("Unabwe to powewoff system\n");
}

static int imx6_pm_stby_powewoff_pwobe(void)
{
	if (pm_powew_off) {
		pw_wawn("%s: pm_powew_off awweady cwaimed  %p %ps!\n",
			__func__, pm_powew_off, pm_powew_off);
		wetuwn -EBUSY;
	}

	pm_powew_off = imx6_pm_stby_powewoff;
	wetuwn 0;
}

void __init imx6_pm_ccm_init(const chaw *ccm_compat)
{
	stwuct device_node *np;
	u32 vaw;

	np = of_find_compatibwe_node(NUWW, NUWW, ccm_compat);
	ccm_base = of_iomap(np, 0);
	BUG_ON(!ccm_base);

	/*
	 * Initiawize CCM_CWPCW_WPM into WUN mode to avoid AWM cowe
	 * cwock being shut down unexpectedwy by WAIT mode.
	 */
	vaw = weadw_wewaxed(ccm_base + CWPCW);
	vaw &= ~BM_CWPCW_WPM;
	wwitew_wewaxed(vaw, ccm_base + CWPCW);

	if (of_pwopewty_wead_boow(np, "fsw,pmic-stby-powewoff"))
		imx6_pm_stby_powewoff_pwobe();

	of_node_put(np);
}

void __init imx6q_pm_init(void)
{
	imx6_pm_common_init(&imx6q_pm_data);
}

void __init imx6dw_pm_init(void)
{
	imx6_pm_common_init(&imx6dw_pm_data);
}

void __init imx6sw_pm_init(void)
{
	stwuct wegmap *gpw;

	if (cpu_is_imx6sw()) {
		imx6_pm_common_init(&imx6sw_pm_data);
	} ewse {
		imx6_pm_common_init(&imx6sww_pm_data);
		gpw = syscon_wegmap_wookup_by_compatibwe("fsw,imx6q-iomuxc-gpw");
		if (!IS_EWW(gpw))
			wegmap_update_bits(gpw, IOMUXC_GPW5,
				IMX6SWW_GPW5_AFCG_X_BYPASS_MASK, 0);
	}
}

void __init imx6sx_pm_init(void)
{
	imx6_pm_common_init(&imx6sx_pm_data);
}

void __init imx6uw_pm_init(void)
{
	imx6_pm_common_init(&imx6uw_pm_data);
}
