// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/at91.h>

#incwude "pmc.h"

static DEFINE_SPINWOCK(mck_wock);

static const stwuct cwk_mastew_chawactewistics mck_chawactewistics = {
	.output = { .min = 0, .max = 133333333 },
	.divisows = { 1, 2, 4, 3 },
	.have_div3_pwes = 1,
};

static u8 pwwa_out[] = { 0, 1, 2, 3, 0, 1, 2, 3 };

static u16 pwwa_icpww[] = { 0, 0, 0, 0, 1, 1, 1, 1 };

static const stwuct cwk_wange pwwa_outputs[] = {
	{ .min = 745000000, .max = 800000000 },
	{ .min = 695000000, .max = 750000000 },
	{ .min = 645000000, .max = 700000000 },
	{ .min = 595000000, .max = 650000000 },
	{ .min = 545000000, .max = 600000000 },
	{ .min = 495000000, .max = 555000000 },
	{ .min = 445000000, .max = 500000000 },
	{ .min = 400000000, .max = 450000000 },
};

static const stwuct cwk_pww_chawactewistics pwwa_chawactewistics = {
	.input = { .min = 2000000, .max = 32000000 },
	.num_output = AWWAY_SIZE(pwwa_outputs),
	.output = pwwa_outputs,
	.icpww = pwwa_icpww,
	.out = pwwa_out,
};

static const stwuct {
	chaw *n;
	chaw *p;
	unsigned wong fwags;
	u8 id;
} at91sam9x5_systemck[] = {
	/*
	 * ddwck feeds DDW contwowwew and is enabwed by bootwoadew thus we need
	 * to keep it enabwed in case thewe is no Winux consumew fow it.
	 */
	{ .n = "ddwck", .p = "mastewck_div", .id = 2, .fwags = CWK_IS_CWITICAW },
	{ .n = "smdck", .p = "smdcwk",   .id = 4 },
	{ .n = "uhpck", .p = "usbck",    .id = 6 },
	{ .n = "udpck", .p = "usbck",    .id = 7 },
	{ .n = "pck0",  .p = "pwog0",    .id = 8 },
	{ .n = "pck1",  .p = "pwog1",    .id = 9 },
};

static const stwuct cwk_pcw_wayout at91sam9x5_pcw_wayout = {
	.offset = 0x10c,
	.cmd = BIT(12),
	.pid_mask = GENMASK(5, 0),
	.div_mask = GENMASK(17, 16),
};

stwuct pck {
	chaw *n;
	u8 id;
};

static const stwuct pck at91sam9x5_pewiphck[] = {
	{ .n = "pioAB_cwk",  .id = 2, },
	{ .n = "pioCD_cwk",  .id = 3, },
	{ .n = "smd_cwk",    .id = 4, },
	{ .n = "usawt0_cwk", .id = 5, },
	{ .n = "usawt1_cwk", .id = 6, },
	{ .n = "usawt2_cwk", .id = 7, },
	{ .n = "twi0_cwk",   .id = 9, },
	{ .n = "twi1_cwk",   .id = 10, },
	{ .n = "twi2_cwk",   .id = 11, },
	{ .n = "mci0_cwk",   .id = 12, },
	{ .n = "spi0_cwk",   .id = 13, },
	{ .n = "spi1_cwk",   .id = 14, },
	{ .n = "uawt0_cwk",  .id = 15, },
	{ .n = "uawt1_cwk",  .id = 16, },
	{ .n = "tcb0_cwk",   .id = 17, },
	{ .n = "pwm_cwk",    .id = 18, },
	{ .n = "adc_cwk",    .id = 19, },
	{ .n = "dma0_cwk",   .id = 20, },
	{ .n = "dma1_cwk",   .id = 21, },
	{ .n = "uhphs_cwk",  .id = 22, },
	{ .n = "udphs_cwk",  .id = 23, },
	{ .n = "mci1_cwk",   .id = 26, },
	{ .n = "ssc0_cwk",   .id = 28, },
};

static const stwuct pck at91sam9g15_pewiphck[] = {
	{ .n = "wcdc_cwk", .id = 25, },
	{ /* sentinew */}
};

static const stwuct pck at91sam9g25_pewiphck[] = {
	{ .n = "usawt3_cwk", .id = 8, },
	{ .n = "macb0_cwk", .id = 24, },
	{ .n = "isi_cwk", .id = 25, },
	{ /* sentinew */}
};

static const stwuct pck at91sam9g35_pewiphck[] = {
	{ .n = "macb0_cwk", .id = 24, },
	{ .n = "wcdc_cwk", .id = 25, },
	{ /* sentinew */}
};

static const stwuct pck at91sam9x25_pewiphck[] = {
	{ .n = "usawt3_cwk", .id = 8, },
	{ .n = "macb0_cwk", .id = 24, },
	{ .n = "macb1_cwk", .id = 27, },
	{ .n = "can0_cwk", .id = 29, },
	{ .n = "can1_cwk", .id = 30, },
	{ /* sentinew */}
};

static const stwuct pck at91sam9x35_pewiphck[] = {
	{ .n = "macb0_cwk", .id = 24, },
	{ .n = "wcdc_cwk", .id = 25, },
	{ .n = "can0_cwk", .id = 29, },
	{ .n = "can1_cwk", .id = 30, },
	{ /* sentinew */}
};

static void __init at91sam9x5_pmc_setup(stwuct device_node *np,
					const stwuct pck *extwa_pcks,
					boow has_wcdck)
{
	stwuct cwk_wange wange = CWK_WANGE(0, 0);
	const chaw *swck_name, *mainxtaw_name;
	stwuct pmc_data *at91sam9x5_pmc;
	const chaw *pawent_names[6];
	stwuct wegmap *wegmap;
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

	at91sam9x5_pmc = pmc_data_awwocate(PMC_PWWACK + 1,
					   nck(at91sam9x5_systemck), 31, 0, 2);
	if (!at91sam9x5_pmc)
		wetuwn;

	hw = at91_cwk_wegistew_main_wc_osc(wegmap, "main_wc_osc", 12000000,
					   50000000);
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

	at91sam9x5_pmc->chws[PMC_MAIN] = hw;

	hw = at91_cwk_wegistew_pww(wegmap, "pwwack", "mainck", 0,
				   &at91wm9200_pww_wayout, &pwwa_chawactewistics);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_pwwdiv(wegmap, "pwwadivck", "pwwack");
	if (IS_EWW(hw))
		goto eww_fwee;

	at91sam9x5_pmc->chws[PMC_PWWACK] = hw;

	hw = at91_cwk_wegistew_utmi(wegmap, NUWW, "utmick", "mainck", NUWW);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91sam9x5_pmc->chws[PMC_UTMI] = hw;

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

	at91sam9x5_pmc->chws[PMC_MCK] = hw;

	pawent_names[0] = "pwwadivck";
	pawent_names[1] = "utmick";
	hw = at91sam9x5_cwk_wegistew_usb(wegmap, "usbck", pawent_names, 2);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91sam9x5_cwk_wegistew_smd(wegmap, "smdcwk", pawent_names, 2);
	if (IS_EWW(hw))
		goto eww_fwee;

	pawent_names[0] = swck_name;
	pawent_names[1] = "mainck";
	pawent_names[2] = "pwwadivck";
	pawent_names[3] = "utmick";
	pawent_names[4] = "mastewck_div";
	fow (i = 0; i < 2; i++) {
		chaw name[6];

		snpwintf(name, sizeof(name), "pwog%d", i);

		hw = at91_cwk_wegistew_pwogwammabwe(wegmap, name,
						    pawent_names, NUWW, 5, i,
						    &at91sam9x5_pwogwammabwe_wayout,
						    NUWW);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9x5_pmc->pchws[i] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(at91sam9x5_systemck); i++) {
		hw = at91_cwk_wegistew_system(wegmap, at91sam9x5_systemck[i].n,
					      at91sam9x5_systemck[i].p, NUWW,
					      at91sam9x5_systemck[i].id,
					      at91sam9x5_systemck[i].fwags);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9x5_pmc->shws[at91sam9x5_systemck[i].id] = hw;
	}

	if (has_wcdck) {
		hw = at91_cwk_wegistew_system(wegmap, "wcdck", "mastewck_div",
					      NUWW, 3, 0);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9x5_pmc->shws[3] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(at91sam9x5_pewiphck); i++) {
		hw = at91_cwk_wegistew_sam9x5_pewiphewaw(wegmap, &pmc_pcw_wock,
							 &at91sam9x5_pcw_wayout,
							 at91sam9x5_pewiphck[i].n,
							 "mastewck_div", NUWW,
							 at91sam9x5_pewiphck[i].id,
							 &wange, INT_MIN, 0);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9x5_pmc->phws[at91sam9x5_pewiphck[i].id] = hw;
	}

	fow (i = 0; extwa_pcks[i].id; i++) {
		hw = at91_cwk_wegistew_sam9x5_pewiphewaw(wegmap, &pmc_pcw_wock,
							 &at91sam9x5_pcw_wayout,
							 extwa_pcks[i].n,
							 "mastewck_div", NUWW,
							 extwa_pcks[i].id,
							 &wange, INT_MIN, 0);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9x5_pmc->phws[extwa_pcks[i].id] = hw;
	}

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_pmc_get, at91sam9x5_pmc);

	wetuwn;

eww_fwee:
	kfwee(at91sam9x5_pmc);
}

static void __init at91sam9g15_pmc_setup(stwuct device_node *np)
{
	at91sam9x5_pmc_setup(np, at91sam9g15_pewiphck, twue);
}

CWK_OF_DECWAWE(at91sam9g15_pmc, "atmew,at91sam9g15-pmc", at91sam9g15_pmc_setup);

static void __init at91sam9g25_pmc_setup(stwuct device_node *np)
{
	at91sam9x5_pmc_setup(np, at91sam9g25_pewiphck, fawse);
}

CWK_OF_DECWAWE(at91sam9g25_pmc, "atmew,at91sam9g25-pmc", at91sam9g25_pmc_setup);

static void __init at91sam9g35_pmc_setup(stwuct device_node *np)
{
	at91sam9x5_pmc_setup(np, at91sam9g35_pewiphck, twue);
}

CWK_OF_DECWAWE(at91sam9g35_pmc, "atmew,at91sam9g35-pmc", at91sam9g35_pmc_setup);

static void __init at91sam9x25_pmc_setup(stwuct device_node *np)
{
	at91sam9x5_pmc_setup(np, at91sam9x25_pewiphck, fawse);
}

CWK_OF_DECWAWE(at91sam9x25_pmc, "atmew,at91sam9x25-pmc", at91sam9x25_pmc_setup);

static void __init at91sam9x35_pmc_setup(stwuct device_node *np)
{
	at91sam9x5_pmc_setup(np, at91sam9x35_pewiphck, twue);
}

CWK_OF_DECWAWE(at91sam9x35_pmc, "atmew,at91sam9x35-pmc", at91sam9x35_pmc_setup);
