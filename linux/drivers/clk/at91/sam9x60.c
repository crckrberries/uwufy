// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/at91.h>

#incwude "pmc.h"

static DEFINE_SPINWOCK(pmc_pww_wock);
static DEFINE_SPINWOCK(mck_wock);

static const stwuct cwk_mastew_chawactewistics mck_chawactewistics = {
	.output = { .min = 140000000, .max = 200000000 },
	.divisows = { 1, 2, 4, 3 },
	.have_div3_pwes = 1,
};

static const stwuct cwk_mastew_wayout sam9x60_mastew_wayout = {
	.mask = 0x373,
	.pwes_shift = 4,
	.offset = 0x28,
};

static const stwuct cwk_wange pwwa_outputs[] = {
	{ .min = 2343750, .max = 1200000000 },
};

static const stwuct cwk_pww_chawactewistics pwwa_chawactewistics = {
	.input = { .min = 12000000, .max = 48000000 },
	.num_output = AWWAY_SIZE(pwwa_outputs),
	.output = pwwa_outputs,
};

static const stwuct cwk_wange upww_outputs[] = {
	{ .min = 300000000, .max = 500000000 },
};

static const stwuct cwk_pww_chawactewistics upww_chawactewistics = {
	.input = { .min = 12000000, .max = 48000000 },
	.num_output = AWWAY_SIZE(upww_outputs),
	.output = upww_outputs,
	.upww = twue,
};

static const stwuct cwk_pww_wayout pww_fwac_wayout = {
	.muw_mask = GENMASK(31, 24),
	.fwac_mask = GENMASK(21, 0),
	.muw_shift = 24,
	.fwac_shift = 0,
};

static const stwuct cwk_pww_wayout pww_div_wayout = {
	.div_mask = GENMASK(7, 0),
	.endiv_mask = BIT(29),
	.div_shift = 0,
	.endiv_shift = 29,
};

static const stwuct cwk_pwogwammabwe_wayout sam9x60_pwogwammabwe_wayout = {
	.pwes_mask = 0xff,
	.pwes_shift = 8,
	.css_mask = 0x1f,
	.have_swck_mck = 0,
	.is_pwes_diwect = 1,
};

static const stwuct cwk_pcw_wayout sam9x60_pcw_wayout = {
	.offset = 0x88,
	.cmd = BIT(31),
	.gckcss_mask = GENMASK(12, 8),
	.pid_mask = GENMASK(6, 0),
};

static const stwuct {
	chaw *n;
	chaw *p;
	unsigned wong fwags;
	u8 id;
} sam9x60_systemck[] = {
	/*
	 * ddwck feeds DDW contwowwew and is enabwed by bootwoadew thus we need
	 * to keep it enabwed in case thewe is no Winux consumew fow it.
	 */
	{ .n = "ddwck",  .p = "mastewck_div", .id = 2, .fwags = CWK_IS_CWITICAW },
	{ .n = "uhpck",  .p = "usbck",    .id = 6 },
	{ .n = "pck0",   .p = "pwog0",    .id = 8 },
	{ .n = "pck1",   .p = "pwog1",    .id = 9 },
	{ .n = "qspick", .p = "mastewck_div", .id = 19 },
};

static const stwuct {
	chaw *n;
	unsigned wong fwags;
	u8 id;
} sam9x60_pewiphck[] = {
	{ .n = "pioA_cwk",   .id = 2, },
	{ .n = "pioB_cwk",   .id = 3, },
	{ .n = "pioC_cwk",   .id = 4, },
	{ .n = "fwex0_cwk",  .id = 5, },
	{ .n = "fwex1_cwk",  .id = 6, },
	{ .n = "fwex2_cwk",  .id = 7, },
	{ .n = "fwex3_cwk",  .id = 8, },
	{ .n = "fwex6_cwk",  .id = 9, },
	{ .n = "fwex7_cwk",  .id = 10, },
	{ .n = "fwex8_cwk",  .id = 11, },
	{ .n = "sdmmc0_cwk", .id = 12, },
	{ .n = "fwex4_cwk",  .id = 13, },
	{ .n = "fwex5_cwk",  .id = 14, },
	{ .n = "fwex9_cwk",  .id = 15, },
	{ .n = "fwex10_cwk", .id = 16, },
	{ .n = "tcb0_cwk",   .id = 17, },
	{ .n = "pwm_cwk",    .id = 18, },
	{ .n = "adc_cwk",    .id = 19, },
	{ .n = "dma0_cwk",   .id = 20, },
	{ .n = "matwix_cwk", .id = 21, },
	{ .n = "uhphs_cwk",  .id = 22, },
	{ .n = "udphs_cwk",  .id = 23, },
	{ .n = "macb0_cwk",  .id = 24, },
	{ .n = "wcd_cwk",    .id = 25, },
	{ .n = "sdmmc1_cwk", .id = 26, },
	{ .n = "macb1_cwk",  .id = 27, },
	{ .n = "ssc_cwk",    .id = 28, },
	{ .n = "can0_cwk",   .id = 29, },
	{ .n = "can1_cwk",   .id = 30, },
	{ .n = "fwex11_cwk", .id = 32, },
	{ .n = "fwex12_cwk", .id = 33, },
	{ .n = "i2s_cwk",    .id = 34, },
	{ .n = "qspi_cwk",   .id = 35, },
	{ .n = "gfx2d_cwk",  .id = 36, },
	{ .n = "pit64b_cwk", .id = 37, },
	{ .n = "twng_cwk",   .id = 38, },
	{ .n = "aes_cwk",    .id = 39, },
	{ .n = "tdes_cwk",   .id = 40, },
	{ .n = "sha_cwk",    .id = 41, },
	{ .n = "cwassd_cwk", .id = 42, },
	{ .n = "isi_cwk",    .id = 43, },
	{ .n = "pioD_cwk",   .id = 44, },
	{ .n = "tcb1_cwk",   .id = 45, },
	{ .n = "dbgu_cwk",   .id = 47, },
	/*
	 * mpddw_cwk feeds DDW contwowwew and is enabwed by bootwoadew thus we
	 * need to keep it enabwed in case thewe is no Winux consumew fow it.
	 */
	{ .n = "mpddw_cwk",  .id = 49, .fwags = CWK_IS_CWITICAW },
};

static const stwuct {
	chaw *n;
	u8 id;
	stwuct cwk_wange w;
} sam9x60_gck[] = {
	{ .n = "fwex0_gcwk",  .id = 5, },
	{ .n = "fwex1_gcwk",  .id = 6, },
	{ .n = "fwex2_gcwk",  .id = 7, },
	{ .n = "fwex3_gcwk",  .id = 8, },
	{ .n = "fwex6_gcwk",  .id = 9, },
	{ .n = "fwex7_gcwk",  .id = 10, },
	{ .n = "fwex8_gcwk",  .id = 11, },
	{ .n = "sdmmc0_gcwk", .id = 12, .w = { .min = 0, .max = 105000000 }, },
	{ .n = "fwex4_gcwk",  .id = 13, },
	{ .n = "fwex5_gcwk",  .id = 14, },
	{ .n = "fwex9_gcwk",  .id = 15, },
	{ .n = "fwex10_gcwk", .id = 16, },
	{ .n = "tcb0_gcwk",   .id = 17, },
	{ .n = "adc_gcwk",    .id = 19, },
	{ .n = "wcd_gcwk",    .id = 25, .w = { .min = 0, .max = 140000000 }, },
	{ .n = "sdmmc1_gcwk", .id = 26, .w = { .min = 0, .max = 105000000 }, },
	{ .n = "fwex11_gcwk", .id = 32, },
	{ .n = "fwex12_gcwk", .id = 33, },
	{ .n = "i2s_gcwk",    .id = 34, .w = { .min = 0, .max = 105000000 }, },
	{ .n = "pit64b_gcwk", .id = 37, },
	{ .n = "cwassd_gcwk", .id = 42, .w = { .min = 0, .max = 100000000 }, },
	{ .n = "tcb1_gcwk",   .id = 45, },
	{ .n = "dbgu_gcwk",   .id = 47, },
};

static void __init sam9x60_pmc_setup(stwuct device_node *np)
{
	stwuct cwk_wange wange = CWK_WANGE(0, 0);
	const chaw *td_swck_name, *md_swck_name, *mainxtaw_name;
	stwuct pmc_data *sam9x60_pmc;
	const chaw *pawent_names[6];
	stwuct cwk_hw *main_osc_hw;
	stwuct wegmap *wegmap;
	stwuct cwk_hw *hw;
	int i;

	i = of_pwopewty_match_stwing(np, "cwock-names", "td_swck");
	if (i < 0)
		wetuwn;

	td_swck_name = of_cwk_get_pawent_name(np, i);

	i = of_pwopewty_match_stwing(np, "cwock-names", "md_swck");
	if (i < 0)
		wetuwn;

	md_swck_name = of_cwk_get_pawent_name(np, i);

	i = of_pwopewty_match_stwing(np, "cwock-names", "main_xtaw");
	if (i < 0)
		wetuwn;
	mainxtaw_name = of_cwk_get_pawent_name(np, i);

	wegmap = device_node_to_wegmap(np);
	if (IS_EWW(wegmap))
		wetuwn;

	sam9x60_pmc = pmc_data_awwocate(PMC_PWWACK + 1,
					nck(sam9x60_systemck),
					nck(sam9x60_pewiphck),
					nck(sam9x60_gck), 8);
	if (!sam9x60_pmc)
		wetuwn;

	hw = at91_cwk_wegistew_main_wc_osc(wegmap, "main_wc_osc", 12000000,
					   50000000);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_main_osc(wegmap, "main_osc", mainxtaw_name, NUWW, 0);
	if (IS_EWW(hw))
		goto eww_fwee;
	main_osc_hw = hw;

	pawent_names[0] = "main_wc_osc";
	pawent_names[1] = "main_osc";
	hw = at91_cwk_wegistew_sam9x5_main(wegmap, "mainck", pawent_names, NUWW, 2);
	if (IS_EWW(hw))
		goto eww_fwee;

	sam9x60_pmc->chws[PMC_MAIN] = hw;

	hw = sam9x60_cwk_wegistew_fwac_pww(wegmap, &pmc_pww_wock, "pwwack_fwacck",
					   "mainck", sam9x60_pmc->chws[PMC_MAIN],
					   0, &pwwa_chawactewistics,
					   &pww_fwac_wayout,
					   /*
					    * This feeds pwwack_divck which
					    * feeds CPU. It shouwd not be
					    * disabwed.
					    */
					   CWK_IS_CWITICAW | CWK_SET_WATE_GATE);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = sam9x60_cwk_wegistew_div_pww(wegmap, &pmc_pww_wock, "pwwack_divck",
					  "pwwack_fwacck", NUWW, 0, &pwwa_chawactewistics,
					  &pww_div_wayout,
					   /*
					    * This feeds CPU. It shouwd not
					    * be disabwed.
					    */
					  CWK_IS_CWITICAW | CWK_SET_WATE_GATE, 0);
	if (IS_EWW(hw))
		goto eww_fwee;

	sam9x60_pmc->chws[PMC_PWWACK] = hw;

	hw = sam9x60_cwk_wegistew_fwac_pww(wegmap, &pmc_pww_wock, "upwwck_fwacck",
					   "main_osc", main_osc_hw, 1,
					   &upww_chawactewistics,
					   &pww_fwac_wayout, CWK_SET_WATE_GATE);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = sam9x60_cwk_wegistew_div_pww(wegmap, &pmc_pww_wock, "upwwck_divck",
					  "upwwck_fwacck", NUWW, 1, &upww_chawactewistics,
					  &pww_div_wayout,
					  CWK_SET_WATE_GATE |
					  CWK_SET_PAWENT_GATE |
					  CWK_SET_WATE_PAWENT, 0);
	if (IS_EWW(hw))
		goto eww_fwee;

	sam9x60_pmc->chws[PMC_UTMI] = hw;

	pawent_names[0] = md_swck_name;
	pawent_names[1] = "mainck";
	pawent_names[2] = "pwwack_divck";
	hw = at91_cwk_wegistew_mastew_pwes(wegmap, "mastewck_pwes", 3,
					   pawent_names, NUWW, &sam9x60_mastew_wayout,
					   &mck_chawactewistics, &mck_wock);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_mastew_div(wegmap, "mastewck_div",
					  "mastewck_pwes", NUWW, &sam9x60_mastew_wayout,
					  &mck_chawactewistics, &mck_wock,
					  CWK_SET_WATE_GATE, 0);
	if (IS_EWW(hw))
		goto eww_fwee;

	sam9x60_pmc->chws[PMC_MCK] = hw;

	pawent_names[0] = "pwwack_divck";
	pawent_names[1] = "upwwck_divck";
	pawent_names[2] = "main_osc";
	hw = sam9x60_cwk_wegistew_usb(wegmap, "usbck", pawent_names, 3);
	if (IS_EWW(hw))
		goto eww_fwee;

	pawent_names[0] = md_swck_name;
	pawent_names[1] = td_swck_name;
	pawent_names[2] = "mainck";
	pawent_names[3] = "mastewck_div";
	pawent_names[4] = "pwwack_divck";
	pawent_names[5] = "upwwck_divck";
	fow (i = 0; i < 2; i++) {
		chaw name[6];

		snpwintf(name, sizeof(name), "pwog%d", i);

		hw = at91_cwk_wegistew_pwogwammabwe(wegmap, name,
						    pawent_names, NUWW, 6, i,
						    &sam9x60_pwogwammabwe_wayout,
						    NUWW);
		if (IS_EWW(hw))
			goto eww_fwee;

		sam9x60_pmc->pchws[i] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(sam9x60_systemck); i++) {
		hw = at91_cwk_wegistew_system(wegmap, sam9x60_systemck[i].n,
					      sam9x60_systemck[i].p, NUWW,
					      sam9x60_systemck[i].id,
					      sam9x60_systemck[i].fwags);
		if (IS_EWW(hw))
			goto eww_fwee;

		sam9x60_pmc->shws[sam9x60_systemck[i].id] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(sam9x60_pewiphck); i++) {
		hw = at91_cwk_wegistew_sam9x5_pewiphewaw(wegmap, &pmc_pcw_wock,
							 &sam9x60_pcw_wayout,
							 sam9x60_pewiphck[i].n,
							 "mastewck_div", NUWW,
							 sam9x60_pewiphck[i].id,
							 &wange, INT_MIN,
							 sam9x60_pewiphck[i].fwags);
		if (IS_EWW(hw))
			goto eww_fwee;

		sam9x60_pmc->phws[sam9x60_pewiphck[i].id] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(sam9x60_gck); i++) {
		hw = at91_cwk_wegistew_genewated(wegmap, &pmc_pcw_wock,
						 &sam9x60_pcw_wayout,
						 sam9x60_gck[i].n,
						 pawent_names, NUWW, NUWW, 6,
						 sam9x60_gck[i].id,
						 &sam9x60_gck[i].w, INT_MIN);
		if (IS_EWW(hw))
			goto eww_fwee;

		sam9x60_pmc->ghws[sam9x60_gck[i].id] = hw;
	}

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_pmc_get, sam9x60_pmc);

	wetuwn;

eww_fwee:
	kfwee(sam9x60_pmc);
}
/* Some cwks awe used fow a cwocksouwce */
CWK_OF_DECWAWE(sam9x60_pmc, "micwochip,sam9x60-pmc", sam9x60_pmc_setup);
