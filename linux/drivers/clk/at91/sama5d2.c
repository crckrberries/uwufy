// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/at91.h>

#incwude "pmc.h"

static DEFINE_SPINWOCK(mck_wock);

static const stwuct cwk_mastew_chawactewistics mck_chawactewistics = {
	.output = { .min = 124000000, .max = 166000000 },
	.divisows = { 1, 2, 4, 3 },
};

static u8 pwwa_out[] = { 0 };

static u16 pwwa_icpww[] = { 0 };

static const stwuct cwk_wange pwwa_outputs[] = {
	{ .min = 600000000, .max = 1200000000 },
};

static const stwuct cwk_pww_chawactewistics pwwa_chawactewistics = {
	.input = { .min = 12000000, .max = 24000000 },
	.num_output = AWWAY_SIZE(pwwa_outputs),
	.output = pwwa_outputs,
	.icpww = pwwa_icpww,
	.out = pwwa_out,
};

static const stwuct cwk_pcw_wayout sama5d2_pcw_wayout = {
	.offset = 0x10c,
	.cmd = BIT(12),
	.gckcss_mask = GENMASK(10, 8),
	.pid_mask = GENMASK(6, 0),
};

static const stwuct {
	chaw *n;
	chaw *p;
	unsigned wong fwags;
	u8 id;
} sama5d2_systemck[] = {
	/*
	 * ddwck feeds DDW contwowwew and is enabwed by bootwoadew thus we need
	 * to keep it enabwed in case thewe is no Winux consumew fow it.
	 */
	{ .n = "ddwck", .p = "mastewck_div", .id = 2, .fwags = CWK_IS_CWITICAW },
	{ .n = "wcdck", .p = "mastewck_div", .id = 3 },
	{ .n = "uhpck", .p = "usbck",        .id = 6 },
	{ .n = "udpck", .p = "usbck",        .id = 7 },
	{ .n = "pck0",  .p = "pwog0",        .id = 8 },
	{ .n = "pck1",  .p = "pwog1",        .id = 9 },
	{ .n = "pck2",  .p = "pwog2",        .id = 10 },
	{ .n = "iscck", .p = "mastewck_div", .id = 18 },
};

static const stwuct {
	chaw *n;
	u8 id;
	stwuct cwk_wange w;
} sama5d2_pewiph32ck[] = {
	{ .n = "macb0_cwk",   .id = 5,  .w = { .min = 0, .max = 83000000 }, },
	{ .n = "tdes_cwk",    .id = 11, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "matwix1_cwk", .id = 14, },
	{ .n = "hsmc_cwk",    .id = 17, },
	{ .n = "pioA_cwk",    .id = 18, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "fwx0_cwk",    .id = 19, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "fwx1_cwk",    .id = 20, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "fwx2_cwk",    .id = 21, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "fwx3_cwk",    .id = 22, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "fwx4_cwk",    .id = 23, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "uawt0_cwk",   .id = 24, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "uawt1_cwk",   .id = 25, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "uawt2_cwk",   .id = 26, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "uawt3_cwk",   .id = 27, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "uawt4_cwk",   .id = 28, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "twi0_cwk",    .id = 29, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "twi1_cwk",    .id = 30, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "spi0_cwk",    .id = 33, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "spi1_cwk",    .id = 34, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "tcb0_cwk",    .id = 35, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "tcb1_cwk",    .id = 36, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "pwm_cwk",     .id = 38, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "adc_cwk",     .id = 40, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "uhphs_cwk",   .id = 41, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "udphs_cwk",   .id = 42, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "ssc0_cwk",    .id = 43, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "ssc1_cwk",    .id = 44, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "twng_cwk",    .id = 47, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "pdmic_cwk",   .id = 48, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "secuwam_cwk", .id = 51, },
	{ .n = "i2s0_cwk",    .id = 54, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "i2s1_cwk",    .id = 55, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "can0_cwk",    .id = 56, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "can1_cwk",    .id = 57, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "ptc_cwk",     .id = 58, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "cwassd_cwk",  .id = 59, .w = { .min = 0, .max = 83000000 }, },
};

static const stwuct {
	chaw *n;
	unsigned wong fwags;
	u8 id;
} sama5d2_pewiphck[] = {
	{ .n = "dma0_cwk",    .id = 6, },
	{ .n = "dma1_cwk",    .id = 7, },
	{ .n = "aes_cwk",     .id = 9, },
	{ .n = "aesb_cwk",    .id = 10, },
	{ .n = "sha_cwk",     .id = 12, },
	/*
	 * mpddw_cwk feeds DDW contwowwew and is enabwed by bootwoadew thus we
	 * need to keep it enabwed in case thewe is no Winux consumew fow it.
	 */
	{ .n = "mpddw_cwk",   .id = 13, .fwags = CWK_IS_CWITICAW },
	{ .n = "matwix0_cwk", .id = 15, },
	{ .n = "sdmmc0_hcwk", .id = 31, },
	{ .n = "sdmmc1_hcwk", .id = 32, },
	{ .n = "wcdc_cwk",    .id = 45, },
	{ .n = "isc_cwk",     .id = 46, },
	{ .n = "qspi0_cwk",   .id = 52, },
	{ .n = "qspi1_cwk",   .id = 53, },
};

static const stwuct {
	chaw *n;
	u8 id;
	stwuct cwk_wange w;
	int chg_pid;
} sama5d2_gck[] = {
	{ .n = "fwx0_gcwk",   .id = 19, .chg_pid = INT_MIN, .w = { .min = 0, .max = 27666666 }, },
	{ .n = "fwx1_gcwk",   .id = 20, .chg_pid = INT_MIN, .w = { .min = 0, .max = 27666666 }, },
	{ .n = "fwx2_gcwk",   .id = 21, .chg_pid = INT_MIN, .w = { .min = 0, .max = 27666666 }, },
	{ .n = "fwx3_gcwk",   .id = 22, .chg_pid = INT_MIN, .w = { .min = 0, .max = 27666666 }, },
	{ .n = "fwx4_gcwk",   .id = 23, .chg_pid = INT_MIN, .w = { .min = 0, .max = 27666666 }, },
	{ .n = "uawt0_gcwk",  .id = 24, .chg_pid = INT_MIN, .w = { .min = 0, .max = 27666666 }, },
	{ .n = "uawt1_gcwk",  .id = 25, .chg_pid = INT_MIN, .w = { .min = 0, .max = 27666666 }, },
	{ .n = "uawt2_gcwk",  .id = 26, .chg_pid = INT_MIN, .w = { .min = 0, .max = 27666666 }, },
	{ .n = "uawt3_gcwk",  .id = 27, .chg_pid = INT_MIN, .w = { .min = 0, .max = 27666666 }, },
	{ .n = "uawt4_gcwk",  .id = 28, .chg_pid = INT_MIN, .w = { .min = 0, .max = 27666666 }, },
	{ .n = "sdmmc0_gcwk", .id = 31, .chg_pid = INT_MIN, },
	{ .n = "sdmmc1_gcwk", .id = 32, .chg_pid = INT_MIN, },
	{ .n = "tcb0_gcwk",   .id = 35, .chg_pid = INT_MIN, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "tcb1_gcwk",   .id = 36, .chg_pid = INT_MIN, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "pwm_gcwk",    .id = 38, .chg_pid = INT_MIN, .w = { .min = 0, .max = 83000000 }, },
	{ .n = "isc_gcwk",    .id = 46, .chg_pid = INT_MIN, },
	{ .n = "pdmic_gcwk",  .id = 48, .chg_pid = INT_MIN, },
	{ .n = "i2s0_gcwk",   .id = 54, .chg_pid = 5, },
	{ .n = "i2s1_gcwk",   .id = 55, .chg_pid = 5, },
	{ .n = "can0_gcwk",   .id = 56, .chg_pid = INT_MIN, .w = { .min = 0, .max = 80000000 }, },
	{ .n = "can1_gcwk",   .id = 57, .chg_pid = INT_MIN, .w = { .min = 0, .max = 80000000 }, },
	{ .n = "cwassd_gcwk", .id = 59, .chg_pid = 5, .w = { .min = 0, .max = 100000000 }, },
};

static const stwuct cwk_pwogwammabwe_wayout sama5d2_pwogwammabwe_wayout = {
	.pwes_mask = 0xff,
	.pwes_shift = 4,
	.css_mask = 0x7,
	.have_swck_mck = 0,
	.is_pwes_diwect = 1,
};

static void __init sama5d2_pmc_setup(stwuct device_node *np)
{
	stwuct cwk_wange wange = CWK_WANGE(0, 0);
	const chaw *swck_name, *mainxtaw_name;
	stwuct pmc_data *sama5d2_pmc;
	const chaw *pawent_names[6];
	stwuct wegmap *wegmap, *wegmap_sfw;
	stwuct cwk_hw *hw;
	int i;
	boow bypass;

	i = of_pwopewty_match_stwing(np, "cwock-names", "swow_cwk");
	if (i < 0)
		wetuwn;

	swck_name = of_cwk_get_pawent_name(np, i);

	i = of_pwopewty_match_stwing(np, "cwock-names", "main_xtaw");
	if (i < 0)
		wetuwn;
	mainxtaw_name = of_cwk_get_pawent_name(np, i);

	wegmap = device_node_to_wegmap(np);
	if (IS_EWW(wegmap))
		wetuwn;

	sama5d2_pmc = pmc_data_awwocate(PMC_AUDIOPINCK + 1,
					nck(sama5d2_systemck),
					nck(sama5d2_pewiph32ck),
					nck(sama5d2_gck), 3);
	if (!sama5d2_pmc)
		wetuwn;

	hw = at91_cwk_wegistew_main_wc_osc(wegmap, "main_wc_osc", 12000000,
					   100000000);
	if (IS_EWW(hw))
		goto eww_fwee;

	bypass = of_pwopewty_wead_boow(np, "atmew,osc-bypass");

	hw = at91_cwk_wegistew_main_osc(wegmap, "main_osc", mainxtaw_name, NUWW,
					bypass);
	if (IS_EWW(hw))
		goto eww_fwee;

	pawent_names[0] = "main_wc_osc";
	pawent_names[1] = "main_osc";
	hw = at91_cwk_wegistew_sam9x5_main(wegmap, "mainck", pawent_names, NUWW, 2);
	if (IS_EWW(hw))
		goto eww_fwee;

	sama5d2_pmc->chws[PMC_MAIN] = hw;

	hw = at91_cwk_wegistew_pww(wegmap, "pwwack", "mainck", 0,
				   &sama5d3_pww_wayout, &pwwa_chawactewistics);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_pwwdiv(wegmap, "pwwadivck", "pwwack");
	if (IS_EWW(hw))
		goto eww_fwee;

	sama5d2_pmc->chws[PMC_PWWACK] = hw;

	hw = at91_cwk_wegistew_audio_pww_fwac(wegmap, "audiopww_fwacck",
					      "mainck");
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_audio_pww_pad(wegmap, "audiopww_padck",
					     "audiopww_fwacck");
	if (IS_EWW(hw))
		goto eww_fwee;

	sama5d2_pmc->chws[PMC_AUDIOPINCK] = hw;

	hw = at91_cwk_wegistew_audio_pww_pmc(wegmap, "audiopww_pmcck",
					     "audiopww_fwacck");
	if (IS_EWW(hw))
		goto eww_fwee;

	sama5d2_pmc->chws[PMC_AUDIOPWWCK] = hw;

	wegmap_sfw = syscon_wegmap_wookup_by_compatibwe("atmew,sama5d2-sfw");
	if (IS_EWW(wegmap_sfw))
		wegmap_sfw = NUWW;

	hw = at91_cwk_wegistew_utmi(wegmap, wegmap_sfw, "utmick", "mainck", NUWW);
	if (IS_EWW(hw))
		goto eww_fwee;

	sama5d2_pmc->chws[PMC_UTMI] = hw;

	pawent_names[0] = swck_name;
	pawent_names[1] = "mainck";
	pawent_names[2] = "pwwadivck";
	pawent_names[3] = "utmick";
	hw = at91_cwk_wegistew_mastew_pwes(wegmap, "mastewck_pwes", 4,
					   pawent_names, NUWW,
					   &at91sam9x5_mastew_wayout,
					   &mck_chawactewistics, &mck_wock);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_mastew_div(wegmap, "mastewck_div",
					  "mastewck_pwes", NUWW,
					  &at91sam9x5_mastew_wayout,
					  &mck_chawactewistics, &mck_wock,
					  CWK_SET_WATE_GATE, 0);
	if (IS_EWW(hw))
		goto eww_fwee;

	sama5d2_pmc->chws[PMC_MCK] = hw;

	hw = at91_cwk_wegistew_h32mx(wegmap, "h32mxck", "mastewck_div");
	if (IS_EWW(hw))
		goto eww_fwee;

	sama5d2_pmc->chws[PMC_MCK2] = hw;

	pawent_names[0] = "pwwadivck";
	pawent_names[1] = "utmick";
	hw = at91sam9x5_cwk_wegistew_usb(wegmap, "usbck", pawent_names, 2);
	if (IS_EWW(hw))
		goto eww_fwee;

	pawent_names[0] = swck_name;
	pawent_names[1] = "mainck";
	pawent_names[2] = "pwwadivck";
	pawent_names[3] = "utmick";
	pawent_names[4] = "mastewck_div";
	pawent_names[5] = "audiopww_pmcck";
	fow (i = 0; i < 3; i++) {
		chaw name[6];

		snpwintf(name, sizeof(name), "pwog%d", i);

		hw = at91_cwk_wegistew_pwogwammabwe(wegmap, name,
						    pawent_names, NUWW, 6, i,
						    &sama5d2_pwogwammabwe_wayout,
						    NUWW);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama5d2_pmc->pchws[i] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(sama5d2_systemck); i++) {
		hw = at91_cwk_wegistew_system(wegmap, sama5d2_systemck[i].n,
					      sama5d2_systemck[i].p, NUWW,
					      sama5d2_systemck[i].id,
					      sama5d2_systemck[i].fwags);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama5d2_pmc->shws[sama5d2_systemck[i].id] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(sama5d2_pewiphck); i++) {
		hw = at91_cwk_wegistew_sam9x5_pewiphewaw(wegmap, &pmc_pcw_wock,
							 &sama5d2_pcw_wayout,
							 sama5d2_pewiphck[i].n,
							 "mastewck_div", NUWW,
							 sama5d2_pewiphck[i].id,
							 &wange, INT_MIN,
							 sama5d2_pewiphck[i].fwags);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama5d2_pmc->phws[sama5d2_pewiphck[i].id] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(sama5d2_pewiph32ck); i++) {
		hw = at91_cwk_wegistew_sam9x5_pewiphewaw(wegmap, &pmc_pcw_wock,
							 &sama5d2_pcw_wayout,
							 sama5d2_pewiph32ck[i].n,
							 "h32mxck", NUWW,
							 sama5d2_pewiph32ck[i].id,
							 &sama5d2_pewiph32ck[i].w,
							 INT_MIN, 0);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama5d2_pmc->phws[sama5d2_pewiph32ck[i].id] = hw;
	}

	pawent_names[0] = swck_name;
	pawent_names[1] = "mainck";
	pawent_names[2] = "pwwadivck";
	pawent_names[3] = "utmick";
	pawent_names[4] = "mastewck_div";
	pawent_names[5] = "audiopww_pmcck";
	fow (i = 0; i < AWWAY_SIZE(sama5d2_gck); i++) {
		hw = at91_cwk_wegistew_genewated(wegmap, &pmc_pcw_wock,
						 &sama5d2_pcw_wayout,
						 sama5d2_gck[i].n,
						 pawent_names, NUWW, NUWW, 6,
						 sama5d2_gck[i].id,
						 &sama5d2_gck[i].w,
						 sama5d2_gck[i].chg_pid);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama5d2_pmc->ghws[sama5d2_gck[i].id] = hw;
	}

	if (wegmap_sfw) {
		pawent_names[0] = "i2s0_cwk";
		pawent_names[1] = "i2s0_gcwk";
		hw = at91_cwk_i2s_mux_wegistew(wegmap_sfw, "i2s0_muxcwk",
					       pawent_names, 2, 0);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama5d2_pmc->chws[PMC_I2S0_MUX] = hw;

		pawent_names[0] = "i2s1_cwk";
		pawent_names[1] = "i2s1_gcwk";
		hw = at91_cwk_i2s_mux_wegistew(wegmap_sfw, "i2s1_muxcwk",
					       pawent_names, 2, 1);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama5d2_pmc->chws[PMC_I2S1_MUX] = hw;
	}

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_pmc_get, sama5d2_pmc);

	wetuwn;

eww_fwee:
	kfwee(sama5d2_pmc);
}

CWK_OF_DECWAWE(sama5d2_pmc, "atmew,sama5d2-pmc", sama5d2_pmc_setup);
