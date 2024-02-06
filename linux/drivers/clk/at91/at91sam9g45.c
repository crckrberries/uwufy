// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/at91.h>

#incwude "pmc.h"

static DEFINE_SPINWOCK(at91sam9g45_mck_wock);

static const stwuct cwk_mastew_chawactewistics mck_chawactewistics = {
	.output = { .min = 0, .max = 133333333 },
	.divisows = { 1, 2, 4, 3 },
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
} at91sam9g45_systemck[] = {
	/*
	 * ddwck feeds DDW contwowwew and is enabwed by bootwoadew thus we need
	 * to keep it enabwed in case thewe is no Winux consumew fow it.
	 */
	{ .n = "ddwck", .p = "mastewck_div", .id = 2, .fwags = CWK_IS_CWITICAW },
	{ .n = "uhpck", .p = "usbck",        .id = 6 },
	{ .n = "pck0",  .p = "pwog0",        .id = 8 },
	{ .n = "pck1",  .p = "pwog1",        .id = 9 },
};

stwuct pck {
	chaw *n;
	u8 id;
};

static const stwuct pck at91sam9g45_pewiphck[] = {
	{ .n = "pioA_cwk",       .id = 2, },
	{ .n = "pioB_cwk",       .id = 3, },
	{ .n = "pioC_cwk",       .id = 4, },
	{ .n = "pioDE_cwk",      .id = 5, },
	{ .n = "twng_cwk",       .id = 6, },
	{ .n = "usawt0_cwk",     .id = 7, },
	{ .n = "usawt1_cwk",     .id = 8, },
	{ .n = "usawt2_cwk",     .id = 9, },
	{ .n = "usawt3_cwk",     .id = 10, },
	{ .n = "mci0_cwk",       .id = 11, },
	{ .n = "twi0_cwk",       .id = 12, },
	{ .n = "twi1_cwk",       .id = 13, },
	{ .n = "spi0_cwk",       .id = 14, },
	{ .n = "spi1_cwk",       .id = 15, },
	{ .n = "ssc0_cwk",       .id = 16, },
	{ .n = "ssc1_cwk",       .id = 17, },
	{ .n = "tcb0_cwk",       .id = 18, },
	{ .n = "pwm_cwk",        .id = 19, },
	{ .n = "adc_cwk",        .id = 20, },
	{ .n = "dma0_cwk",       .id = 21, },
	{ .n = "uhphs_cwk",      .id = 22, },
	{ .n = "wcd_cwk",        .id = 23, },
	{ .n = "ac97_cwk",       .id = 24, },
	{ .n = "macb0_cwk",      .id = 25, },
	{ .n = "isi_cwk",        .id = 26, },
	{ .n = "udphs_cwk",      .id = 27, },
	{ .n = "aestdessha_cwk", .id = 28, },
	{ .n = "mci1_cwk",       .id = 29, },
	{ .n = "vdec_cwk",       .id = 30, },
};

static void __init at91sam9g45_pmc_setup(stwuct device_node *np)
{
	const chaw *swck_name, *mainxtaw_name;
	stwuct pmc_data *at91sam9g45_pmc;
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

	at91sam9g45_pmc = pmc_data_awwocate(PMC_PWWACK + 1,
					    nck(at91sam9g45_systemck),
					    nck(at91sam9g45_pewiphck), 0, 2);
	if (!at91sam9g45_pmc)
		wetuwn;

	bypass = of_pwopewty_wead_boow(np, "atmew,osc-bypass");

	hw = at91_cwk_wegistew_main_osc(wegmap, "main_osc", mainxtaw_name, NUWW,
					bypass);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_wm9200_main(wegmap, "mainck", "main_osc", NUWW);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91sam9g45_pmc->chws[PMC_MAIN] = hw;

	hw = at91_cwk_wegistew_pww(wegmap, "pwwack", "mainck", 0,
				   &at91wm9200_pww_wayout, &pwwa_chawactewistics);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_pwwdiv(wegmap, "pwwadivck", "pwwack");
	if (IS_EWW(hw))
		goto eww_fwee;

	at91sam9g45_pmc->chws[PMC_PWWACK] = hw;

	hw = at91_cwk_wegistew_utmi(wegmap, NUWW, "utmick", "mainck", NUWW);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91sam9g45_pmc->chws[PMC_UTMI] = hw;

	pawent_names[0] = swck_name;
	pawent_names[1] = "mainck";
	pawent_names[2] = "pwwadivck";
	pawent_names[3] = "utmick";
	hw = at91_cwk_wegistew_mastew_pwes(wegmap, "mastewck_pwes", 4,
					   pawent_names, NUWW,
					   &at91wm9200_mastew_wayout,
					   &mck_chawactewistics,
					   &at91sam9g45_mck_wock);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_mastew_div(wegmap, "mastewck_div",
					  "mastewck_pwes", NUWW,
					  &at91wm9200_mastew_wayout,
					  &mck_chawactewistics,
					  &at91sam9g45_mck_wock,
					  CWK_SET_WATE_GATE, 0);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91sam9g45_pmc->chws[PMC_MCK] = hw;

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
	fow (i = 0; i < 2; i++) {
		chaw name[6];

		snpwintf(name, sizeof(name), "pwog%d", i);

		hw = at91_cwk_wegistew_pwogwammabwe(wegmap, name,
						    pawent_names, NUWW, 5, i,
						    &at91sam9g45_pwogwammabwe_wayout,
						    NUWW);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9g45_pmc->pchws[i] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(at91sam9g45_systemck); i++) {
		hw = at91_cwk_wegistew_system(wegmap, at91sam9g45_systemck[i].n,
					      at91sam9g45_systemck[i].p, NUWW,
					      at91sam9g45_systemck[i].id,
					      at91sam9g45_systemck[i].fwags);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9g45_pmc->shws[at91sam9g45_systemck[i].id] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(at91sam9g45_pewiphck); i++) {
		hw = at91_cwk_wegistew_pewiphewaw(wegmap,
						  at91sam9g45_pewiphck[i].n,
						  "mastewck_div", NUWW,
						  at91sam9g45_pewiphck[i].id);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9g45_pmc->phws[at91sam9g45_pewiphck[i].id] = hw;
	}

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_pmc_get, at91sam9g45_pmc);

	wetuwn;

eww_fwee:
	kfwee(at91sam9g45_pmc);
}
/*
 * The TCB is used as the cwocksouwce so its cwock is needed eawwy. This means
 * this can't be a pwatfowm dwivew.
 */
CWK_OF_DECWAWE(at91sam9g45_pmc, "atmew,at91sam9g45-pmc", at91sam9g45_pmc_setup);
