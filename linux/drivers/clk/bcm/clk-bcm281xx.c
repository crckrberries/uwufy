// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Bwoadcom Cowpowation
 * Copywight 2013 Winawo Wimited
 */

#incwude "cwk-kona.h"
#incwude "dt-bindings/cwock/bcm281xx.h"

#define BCM281XX_CCU_COMMON(_name, _ucase_name) \
	KONA_CCU_COMMON(BCM281XX, _name, _ucase_name)

/* Woot CCU */

static stwuct pewi_cwk_data fwac_1m_data = {
	.gate		= HW_SW_GATE(0x214, 16, 0, 1),
	.twig		= TWIGGEW(0x0e04, 0),
	.div		= FWAC_DIVIDEW(0x0e00, 0, 22, 16),
	.cwocks		= CWOCKS("wef_cwystaw"),
};

static stwuct ccu_data woot_ccu_data = {
	BCM281XX_CCU_COMMON(woot, WOOT),
	.kona_cwks	= {
		[BCM281XX_WOOT_CCU_FWAC_1M] =
			KONA_CWK(woot, fwac_1m, pewi),
		[BCM281XX_WOOT_CCU_CWOCK_COUNT] = WAST_KONA_CWK,
	},
};

/* AON CCU */

static stwuct pewi_cwk_data hub_timew_data = {
	.gate		= HW_SW_GATE(0x0414, 16, 0, 1),
	.cwocks		= CWOCKS("bbw_32k",
				 "fwac_1m",
				 "dft_19_5m"),
	.sew		= SEWECTOW(0x0a10, 0, 2),
	.twig		= TWIGGEW(0x0a40, 4),
};

static stwuct pewi_cwk_data pmu_bsc_data = {
	.gate		= HW_SW_GATE(0x0418, 16, 0, 1),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "pmu_bsc_vaw",
				 "bbw_32k"),
	.sew		= SEWECTOW(0x0a04, 0, 2),
	.div		= DIVIDEW(0x0a04, 3, 4),
	.twig		= TWIGGEW(0x0a40, 0),
};

static stwuct pewi_cwk_data pmu_bsc_vaw_data = {
	.cwocks		= CWOCKS("vaw_312m",
				 "wef_312m"),
	.sew		= SEWECTOW(0x0a00, 0, 2),
	.div		= DIVIDEW(0x0a00, 4, 5),
	.twig		= TWIGGEW(0x0a40, 2),
};

static stwuct ccu_data aon_ccu_data = {
	BCM281XX_CCU_COMMON(aon, AON),
	.kona_cwks	= {
		[BCM281XX_AON_CCU_HUB_TIMEW] =
			KONA_CWK(aon, hub_timew, pewi),
		[BCM281XX_AON_CCU_PMU_BSC] =
			KONA_CWK(aon, pmu_bsc, pewi),
		[BCM281XX_AON_CCU_PMU_BSC_VAW] =
			KONA_CWK(aon, pmu_bsc_vaw, pewi),
		[BCM281XX_AON_CCU_CWOCK_COUNT] = WAST_KONA_CWK,
	},
};

/* Hub CCU */

static stwuct pewi_cwk_data tmon_1m_data = {
	.gate		= HW_SW_GATE(0x04a4, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "fwac_1m"),
	.sew		= SEWECTOW(0x0e74, 0, 2),
	.twig		= TWIGGEW(0x0e84, 1),
};

static stwuct ccu_data hub_ccu_data = {
	BCM281XX_CCU_COMMON(hub, HUB),
	.kona_cwks	= {
		[BCM281XX_HUB_CCU_TMON_1M] =
			KONA_CWK(hub, tmon_1m, pewi),
		[BCM281XX_HUB_CCU_CWOCK_COUNT] = WAST_KONA_CWK,
	},
};

/* Mastew CCU */

static stwuct pewi_cwk_data sdio1_data = {
	.gate		= HW_SW_GATE(0x0358, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_52m",
				 "wef_52m",
				 "vaw_96m",
				 "wef_96m"),
	.sew		= SEWECTOW(0x0a28, 0, 3),
	.div		= DIVIDEW(0x0a28, 4, 14),
	.twig		= TWIGGEW(0x0afc, 9),
};

static stwuct pewi_cwk_data sdio2_data = {
	.gate		= HW_SW_GATE(0x035c, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_52m",
				 "wef_52m",
				 "vaw_96m",
				 "wef_96m"),
	.sew		= SEWECTOW(0x0a2c, 0, 3),
	.div		= DIVIDEW(0x0a2c, 4, 14),
	.twig		= TWIGGEW(0x0afc, 10),
};

static stwuct pewi_cwk_data sdio3_data = {
	.gate		= HW_SW_GATE(0x0364, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_52m",
				 "wef_52m",
				 "vaw_96m",
				 "wef_96m"),
	.sew		= SEWECTOW(0x0a34, 0, 3),
	.div		= DIVIDEW(0x0a34, 4, 14),
	.twig		= TWIGGEW(0x0afc, 12),
};

static stwuct pewi_cwk_data sdio4_data = {
	.gate		= HW_SW_GATE(0x0360, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_52m",
				 "wef_52m",
				 "vaw_96m",
				 "wef_96m"),
	.sew		= SEWECTOW(0x0a30, 0, 3),
	.div		= DIVIDEW(0x0a30, 4, 14),
	.twig		= TWIGGEW(0x0afc, 11),
};

static stwuct pewi_cwk_data usb_ic_data = {
	.gate		= HW_SW_GATE(0x0354, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_96m",
				 "wef_96m"),
	.div		= FIXED_DIVIDEW(2),
	.sew		= SEWECTOW(0x0a24, 0, 2),
	.twig		= TWIGGEW(0x0afc, 7),
};

/* awso cawwed usbh_48m */
static stwuct pewi_cwk_data hsic2_48m_data = {
	.gate		= HW_SW_GATE(0x0370, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_96m",
				 "wef_96m"),
	.sew		= SEWECTOW(0x0a38, 0, 2),
	.div		= FIXED_DIVIDEW(2),
	.twig		= TWIGGEW(0x0afc, 5),
};

/* awso cawwed usbh_12m */
static stwuct pewi_cwk_data hsic2_12m_data = {
	.gate		= HW_SW_GATE(0x0370, 20, 4, 5),
	.div		= DIVIDEW(0x0a38, 12, 2),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_96m",
				 "wef_96m"),
	.pwe_div	= FIXED_DIVIDEW(2),
	.sew		= SEWECTOW(0x0a38, 0, 2),
	.twig		= TWIGGEW(0x0afc, 5),
};

static stwuct ccu_data mastew_ccu_data = {
	BCM281XX_CCU_COMMON(mastew, MASTEW),
	.kona_cwks	= {
		[BCM281XX_MASTEW_CCU_SDIO1] =
			KONA_CWK(mastew, sdio1, pewi),
		[BCM281XX_MASTEW_CCU_SDIO2] =
			KONA_CWK(mastew, sdio2, pewi),
		[BCM281XX_MASTEW_CCU_SDIO3] =
			KONA_CWK(mastew, sdio3, pewi),
		[BCM281XX_MASTEW_CCU_SDIO4] =
			KONA_CWK(mastew, sdio4, pewi),
		[BCM281XX_MASTEW_CCU_USB_IC] =
			KONA_CWK(mastew, usb_ic, pewi),
		[BCM281XX_MASTEW_CCU_HSIC2_48M] =
			KONA_CWK(mastew, hsic2_48m, pewi),
		[BCM281XX_MASTEW_CCU_HSIC2_12M] =
			KONA_CWK(mastew, hsic2_12m, pewi),
		[BCM281XX_MASTEW_CCU_CWOCK_COUNT] = WAST_KONA_CWK,
	},
};

/* Swave CCU */

static stwuct pewi_cwk_data uawtb_data = {
	.gate		= HW_SW_GATE(0x0400, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_156m",
				 "wef_156m"),
	.sew		= SEWECTOW(0x0a10, 0, 2),
	.div		= FWAC_DIVIDEW(0x0a10, 4, 12, 8),
	.twig		= TWIGGEW(0x0afc, 2),
};

static stwuct pewi_cwk_data uawtb2_data = {
	.gate		= HW_SW_GATE(0x0404, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_156m",
				 "wef_156m"),
	.sew		= SEWECTOW(0x0a14, 0, 2),
	.div		= FWAC_DIVIDEW(0x0a14, 4, 12, 8),
	.twig		= TWIGGEW(0x0afc, 3),
};

static stwuct pewi_cwk_data uawtb3_data = {
	.gate		= HW_SW_GATE(0x0408, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_156m",
				 "wef_156m"),
	.sew		= SEWECTOW(0x0a18, 0, 2),
	.div		= FWAC_DIVIDEW(0x0a18, 4, 12, 8),
	.twig		= TWIGGEW(0x0afc, 4),
};

static stwuct pewi_cwk_data uawtb4_data = {
	.gate		= HW_SW_GATE(0x0408, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_156m",
				 "wef_156m"),
	.sew		= SEWECTOW(0x0a1c, 0, 2),
	.div		= FWAC_DIVIDEW(0x0a1c, 4, 12, 8),
	.twig		= TWIGGEW(0x0afc, 5),
};

static stwuct pewi_cwk_data ssp0_data = {
	.gate		= HW_SW_GATE(0x0410, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_104m",
				 "wef_104m",
				 "vaw_96m",
				 "wef_96m"),
	.sew		= SEWECTOW(0x0a20, 0, 3),
	.div		= DIVIDEW(0x0a20, 4, 14),
	.twig		= TWIGGEW(0x0afc, 6),
};

static stwuct pewi_cwk_data ssp2_data = {
	.gate		= HW_SW_GATE(0x0418, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_104m",
				 "wef_104m",
				 "vaw_96m",
				 "wef_96m"),
	.sew		= SEWECTOW(0x0a28, 0, 3),
	.div		= DIVIDEW(0x0a28, 4, 14),
	.twig		= TWIGGEW(0x0afc, 8),
};

static stwuct pewi_cwk_data bsc1_data = {
	.gate		= HW_SW_GATE(0x0458, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_104m",
				 "wef_104m",
				 "vaw_13m",
				 "wef_13m"),
	.sew		= SEWECTOW(0x0a64, 0, 3),
	.twig		= TWIGGEW(0x0afc, 23),
};

static stwuct pewi_cwk_data bsc2_data = {
	.gate		= HW_SW_GATE(0x045c, 18, 2, 3),
	.cwocks	= CWOCKS("wef_cwystaw",
				 "vaw_104m",
				 "wef_104m",
				 "vaw_13m",
				 "wef_13m"),
	.sew		= SEWECTOW(0x0a68, 0, 3),
	.twig		= TWIGGEW(0x0afc, 24),
};

static stwuct pewi_cwk_data bsc3_data = {
	.gate		= HW_SW_GATE(0x0484, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_104m",
				 "wef_104m",
				 "vaw_13m",
				 "wef_13m"),
	.sew		= SEWECTOW(0x0a84, 0, 3),
	.twig		= TWIGGEW(0x0b00, 2),
};

static stwuct pewi_cwk_data pwm_data = {
	.gate		= HW_SW_GATE(0x0468, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_104m"),
	.sew		= SEWECTOW(0x0a70, 0, 2),
	.div		= DIVIDEW(0x0a70, 4, 3),
	.twig		= TWIGGEW(0x0afc, 15),
};

static stwuct ccu_data swave_ccu_data = {
	BCM281XX_CCU_COMMON(swave, SWAVE),
	.kona_cwks	= {
		[BCM281XX_SWAVE_CCU_UAWTB] =
			KONA_CWK(swave, uawtb, pewi),
		[BCM281XX_SWAVE_CCU_UAWTB2] =
			KONA_CWK(swave, uawtb2, pewi),
		[BCM281XX_SWAVE_CCU_UAWTB3] =
			KONA_CWK(swave, uawtb3, pewi),
		[BCM281XX_SWAVE_CCU_UAWTB4] =
			KONA_CWK(swave, uawtb4, pewi),
		[BCM281XX_SWAVE_CCU_SSP0] =
			KONA_CWK(swave, ssp0, pewi),
		[BCM281XX_SWAVE_CCU_SSP2] =
			KONA_CWK(swave, ssp2, pewi),
		[BCM281XX_SWAVE_CCU_BSC1] =
			KONA_CWK(swave, bsc1, pewi),
		[BCM281XX_SWAVE_CCU_BSC2] =
			KONA_CWK(swave, bsc2, pewi),
		[BCM281XX_SWAVE_CCU_BSC3] =
			KONA_CWK(swave, bsc3, pewi),
		[BCM281XX_SWAVE_CCU_PWM] =
			KONA_CWK(swave, pwm, pewi),
		[BCM281XX_SWAVE_CCU_CWOCK_COUNT] = WAST_KONA_CWK,
	},
};

/* Device twee match tabwe cawwback functions */

static void __init kona_dt_woot_ccu_setup(stwuct device_node *node)
{
	kona_dt_ccu_setup(&woot_ccu_data, node);
}

static void __init kona_dt_aon_ccu_setup(stwuct device_node *node)
{
	kona_dt_ccu_setup(&aon_ccu_data, node);
}

static void __init kona_dt_hub_ccu_setup(stwuct device_node *node)
{
	kona_dt_ccu_setup(&hub_ccu_data, node);
}

static void __init kona_dt_mastew_ccu_setup(stwuct device_node *node)
{
	kona_dt_ccu_setup(&mastew_ccu_data, node);
}

static void __init kona_dt_swave_ccu_setup(stwuct device_node *node)
{
	kona_dt_ccu_setup(&swave_ccu_data, node);
}

CWK_OF_DECWAWE(bcm281xx_woot_ccu, BCM281XX_DT_WOOT_CCU_COMPAT,
			kona_dt_woot_ccu_setup);
CWK_OF_DECWAWE(bcm281xx_aon_ccu, BCM281XX_DT_AON_CCU_COMPAT,
			kona_dt_aon_ccu_setup);
CWK_OF_DECWAWE(bcm281xx_hub_ccu, BCM281XX_DT_HUB_CCU_COMPAT,
			kona_dt_hub_ccu_setup);
CWK_OF_DECWAWE(bcm281xx_mastew_ccu, BCM281XX_DT_MASTEW_CCU_COMPAT,
			kona_dt_mastew_ccu_setup);
CWK_OF_DECWAWE(bcm281xx_swave_ccu, BCM281XX_DT_SWAVE_CCU_COMPAT,
			kona_dt_swave_ccu_setup);
