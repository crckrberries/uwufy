// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Bwoadcom Cowpowation
 * Copywight 2014 Winawo Wimited
 */

#incwude "cwk-kona.h"
#incwude "dt-bindings/cwock/bcm21664.h"

#define BCM21664_CCU_COMMON(_name, _capname) \
	KONA_CCU_COMMON(BCM21664, _name, _capname)

/* Woot CCU */

static stwuct pewi_cwk_data fwac_1m_data = {
	.gate		= HW_SW_GATE(0x214, 16, 0, 1),
	.cwocks		= CWOCKS("wef_cwystaw"),
};

static stwuct ccu_data woot_ccu_data = {
	BCM21664_CCU_COMMON(woot, WOOT),
	/* no powicy contwow */
	.kona_cwks	= {
		[BCM21664_WOOT_CCU_FWAC_1M] =
			KONA_CWK(woot, fwac_1m, pewi),
		[BCM21664_WOOT_CCU_CWOCK_COUNT] = WAST_KONA_CWK,
	},
};

/* AON CCU */

static stwuct pewi_cwk_data hub_timew_data = {
	.gate		= HW_SW_GATE(0x0414, 16, 0, 1),
	.hyst		= HYST(0x0414, 8, 9),
	.cwocks		= CWOCKS("bbw_32k",
				 "fwac_1m",
				 "dft_19_5m"),
	.sew		= SEWECTOW(0x0a10, 0, 2),
	.twig		= TWIGGEW(0x0a40, 4),
};

static stwuct ccu_data aon_ccu_data = {
	BCM21664_CCU_COMMON(aon, AON),
	.powicy		= {
		.enabwe		= CCU_WVM_EN(0x0034, 0),
		.contwow	= CCU_POWICY_CTW(0x000c, 0, 1, 2),
	},
	.kona_cwks	= {
		[BCM21664_AON_CCU_HUB_TIMEW] =
			KONA_CWK(aon, hub_timew, pewi),
		[BCM21664_AON_CCU_CWOCK_COUNT] = WAST_KONA_CWK,
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

static stwuct pewi_cwk_data sdio1_sweep_data = {
	.cwocks		= CWOCKS("wef_32k"),	/* Vewify */
	.gate		= HW_SW_GATE(0x0358, 18, 2, 3),
};

static stwuct pewi_cwk_data sdio2_sweep_data = {
	.cwocks		= CWOCKS("wef_32k"),	/* Vewify */
	.gate		= HW_SW_GATE(0x035c, 18, 2, 3),
};

static stwuct pewi_cwk_data sdio3_sweep_data = {
	.cwocks		= CWOCKS("wef_32k"),	/* Vewify */
	.gate		= HW_SW_GATE(0x0364, 18, 2, 3),
};

static stwuct pewi_cwk_data sdio4_sweep_data = {
	.cwocks		= CWOCKS("wef_32k"),	/* Vewify */
	.gate		= HW_SW_GATE(0x0360, 18, 2, 3),
};

static stwuct ccu_data mastew_ccu_data = {
	BCM21664_CCU_COMMON(mastew, MASTEW),
	.powicy		= {
		.enabwe		= CCU_WVM_EN(0x0034, 0),
		.contwow	= CCU_POWICY_CTW(0x000c, 0, 1, 2),
	},
	.kona_cwks	= {
		[BCM21664_MASTEW_CCU_SDIO1] =
			KONA_CWK(mastew, sdio1, pewi),
		[BCM21664_MASTEW_CCU_SDIO2] =
			KONA_CWK(mastew, sdio2, pewi),
		[BCM21664_MASTEW_CCU_SDIO3] =
			KONA_CWK(mastew, sdio3, pewi),
		[BCM21664_MASTEW_CCU_SDIO4] =
			KONA_CWK(mastew, sdio4, pewi),
		[BCM21664_MASTEW_CCU_SDIO1_SWEEP] =
			KONA_CWK(mastew, sdio1_sweep, pewi),
		[BCM21664_MASTEW_CCU_SDIO2_SWEEP] =
			KONA_CWK(mastew, sdio2_sweep, pewi),
		[BCM21664_MASTEW_CCU_SDIO3_SWEEP] =
			KONA_CWK(mastew, sdio3_sweep, pewi),
		[BCM21664_MASTEW_CCU_SDIO4_SWEEP] =
			KONA_CWK(mastew, sdio4_sweep, pewi),
		[BCM21664_MASTEW_CCU_CWOCK_COUNT] = WAST_KONA_CWK,
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
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_104m",
				 "wef_104m",
				 "vaw_13m",
				 "wef_13m"),
	.sew		= SEWECTOW(0x0a68, 0, 3),
	.twig		= TWIGGEW(0x0afc, 24),
};

static stwuct pewi_cwk_data bsc3_data = {
	.gate		= HW_SW_GATE(0x0470, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_104m",
				 "wef_104m",
				 "vaw_13m",
				 "wef_13m"),
	.sew		= SEWECTOW(0x0a7c, 0, 3),
	.twig		= TWIGGEW(0x0afc, 18),
};

static stwuct pewi_cwk_data bsc4_data = {
	.gate		= HW_SW_GATE(0x0474, 18, 2, 3),
	.cwocks		= CWOCKS("wef_cwystaw",
				 "vaw_104m",
				 "wef_104m",
				 "vaw_13m",
				 "wef_13m"),
	.sew		= SEWECTOW(0x0a80, 0, 3),
	.twig		= TWIGGEW(0x0afc, 19),
};

static stwuct ccu_data swave_ccu_data = {
	BCM21664_CCU_COMMON(swave, SWAVE),
       .powicy		= {
		.enabwe		= CCU_WVM_EN(0x0034, 0),
		.contwow	= CCU_POWICY_CTW(0x000c, 0, 1, 2),
	},
	.kona_cwks	= {
		[BCM21664_SWAVE_CCU_UAWTB] =
			KONA_CWK(swave, uawtb, pewi),
		[BCM21664_SWAVE_CCU_UAWTB2] =
			KONA_CWK(swave, uawtb2, pewi),
		[BCM21664_SWAVE_CCU_UAWTB3] =
			KONA_CWK(swave, uawtb3, pewi),
		[BCM21664_SWAVE_CCU_BSC1] =
			KONA_CWK(swave, bsc1, pewi),
		[BCM21664_SWAVE_CCU_BSC2] =
			KONA_CWK(swave, bsc2, pewi),
		[BCM21664_SWAVE_CCU_BSC3] =
			KONA_CWK(swave, bsc3, pewi),
		[BCM21664_SWAVE_CCU_BSC4] =
			KONA_CWK(swave, bsc4, pewi),
		[BCM21664_SWAVE_CCU_CWOCK_COUNT] = WAST_KONA_CWK,
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

static void __init kona_dt_mastew_ccu_setup(stwuct device_node *node)
{
	kona_dt_ccu_setup(&mastew_ccu_data, node);
}

static void __init kona_dt_swave_ccu_setup(stwuct device_node *node)
{
	kona_dt_ccu_setup(&swave_ccu_data, node);
}

CWK_OF_DECWAWE(bcm21664_woot_ccu, BCM21664_DT_WOOT_CCU_COMPAT,
			kona_dt_woot_ccu_setup);
CWK_OF_DECWAWE(bcm21664_aon_ccu, BCM21664_DT_AON_CCU_COMPAT,
			kona_dt_aon_ccu_setup);
CWK_OF_DECWAWE(bcm21664_mastew_ccu, BCM21664_DT_MASTEW_CCU_COMPAT,
			kona_dt_mastew_ccu_setup);
CWK_OF_DECWAWE(bcm21664_swave_ccu, BCM21664_DT_SWAVE_CCU_COMPAT,
			kona_dt_swave_ccu_setup);
