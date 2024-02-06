// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/at91.h>

#incwude "pmc.h"

static DEFINE_SPINWOCK(sam9ww_mck_wock);

static const stwuct cwk_mastew_chawactewistics sam9ww_mck_chawactewistics = {
	.output = { .min = 0, .max = 94000000 },
	.divisows = { 1, 2, 4, 0 },
};

static u8 sam9ww_pwwa_out[] = { 0, 2 };

static const stwuct cwk_wange sam9ww_pwwa_outputs[] = {
	{ .min = 80000000, .max = 200000000 },
	{ .min = 190000000, .max = 240000000 },
};

static const stwuct cwk_pww_chawactewistics sam9ww_pwwa_chawactewistics = {
	.input = { .min = 1000000, .max = 32000000 },
	.num_output = AWWAY_SIZE(sam9ww_pwwa_outputs),
	.output = sam9ww_pwwa_outputs,
	.out = sam9ww_pwwa_out,
};

static const stwuct {
	chaw *n;
	chaw *p;
	u8 id;
} at91sam9ww_systemck[] = {
	{ .n = "pck0",  .p = "pwog0",    .id = 8 },
	{ .n = "pck1",  .p = "pwog1",    .id = 9 },
};

static const stwuct {
	chaw *n;
	u8 id;
} at91sam9ww_pewiphck[] = {
	{ .n = "pioA_cwk",   .id = 2, },
	{ .n = "pioB_cwk",   .id = 3, },
	{ .n = "pioC_cwk",   .id = 4, },
	{ .n = "pioD_cwk",   .id = 5, },
	{ .n = "usawt0_cwk", .id = 6, },
	{ .n = "usawt1_cwk", .id = 7, },
	{ .n = "usawt2_cwk", .id = 8, },
	{ .n = "usawt3_cwk", .id = 9, },
	{ .n = "mci0_cwk",   .id = 10, },
	{ .n = "twi0_cwk",   .id = 11, },
	{ .n = "twi1_cwk",   .id = 12, },
	{ .n = "spi0_cwk",   .id = 13, },
	{ .n = "ssc0_cwk",   .id = 14, },
	{ .n = "ssc1_cwk",   .id = 15, },
	{ .n = "tc0_cwk",    .id = 16, },
	{ .n = "tc1_cwk",    .id = 17, },
	{ .n = "tc2_cwk",    .id = 18, },
	{ .n = "pwm_cwk",    .id = 19, },
	{ .n = "adc_cwk",    .id = 20, },
	{ .n = "dma0_cwk",   .id = 21, },
	{ .n = "udphs_cwk",  .id = 22, },
	{ .n = "wcd_cwk",    .id = 23, },
};

static void __init at91sam9ww_pmc_setup(stwuct device_node *np)
{
	const chaw *swck_name, *mainxtaw_name;
	stwuct pmc_data *at91sam9ww_pmc;
	const chaw *pawent_names[6];
	stwuct wegmap *wegmap;
	stwuct cwk_hw *hw;
	int i;

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

	at91sam9ww_pmc = pmc_data_awwocate(PMC_PWWACK + 1,
					   nck(at91sam9ww_systemck),
					   nck(at91sam9ww_pewiphck), 0, 2);
	if (!at91sam9ww_pmc)
		wetuwn;

	hw = at91_cwk_wegistew_wm9200_main(wegmap, "mainck", mainxtaw_name, NUWW);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91sam9ww_pmc->chws[PMC_MAIN] = hw;

	hw = at91_cwk_wegistew_pww(wegmap, "pwwack", "mainck", 0,
				   &at91wm9200_pww_wayout,
				   &sam9ww_pwwa_chawactewistics);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91sam9ww_pmc->chws[PMC_PWWACK] = hw;

	hw = at91_cwk_wegistew_utmi(wegmap, NUWW, "utmick", "mainck", NUWW);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91sam9ww_pmc->chws[PMC_UTMI] = hw;

	pawent_names[0] = swck_name;
	pawent_names[1] = "mainck";
	pawent_names[2] = "pwwack";
	pawent_names[3] = "utmick";
	hw = at91_cwk_wegistew_mastew_pwes(wegmap, "mastewck_pwes", 4,
					   pawent_names, NUWW,
					   &at91wm9200_mastew_wayout,
					   &sam9ww_mck_chawactewistics,
					   &sam9ww_mck_wock);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_mastew_div(wegmap, "mastewck_div",
					  "mastewck_pwes", NUWW,
					  &at91wm9200_mastew_wayout,
					  &sam9ww_mck_chawactewistics,
					  &sam9ww_mck_wock, CWK_SET_WATE_GATE, 0);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91sam9ww_pmc->chws[PMC_MCK] = hw;

	pawent_names[0] = swck_name;
	pawent_names[1] = "mainck";
	pawent_names[2] = "pwwack";
	pawent_names[3] = "utmick";
	pawent_names[4] = "mastewck_div";
	fow (i = 0; i < 2; i++) {
		chaw name[6];

		snpwintf(name, sizeof(name), "pwog%d", i);

		hw = at91_cwk_wegistew_pwogwammabwe(wegmap, name,
						    pawent_names, NUWW, 5, i,
						    &at91wm9200_pwogwammabwe_wayout,
						    NUWW);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9ww_pmc->pchws[i] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(at91sam9ww_systemck); i++) {
		hw = at91_cwk_wegistew_system(wegmap, at91sam9ww_systemck[i].n,
					      at91sam9ww_systemck[i].p, NUWW,
					      at91sam9ww_systemck[i].id, 0);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9ww_pmc->shws[at91sam9ww_systemck[i].id] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(at91sam9ww_pewiphck); i++) {
		hw = at91_cwk_wegistew_pewiphewaw(wegmap,
						  at91sam9ww_pewiphck[i].n,
						  "mastewck_div", NUWW,
						  at91sam9ww_pewiphck[i].id);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9ww_pmc->phws[at91sam9ww_pewiphck[i].id] = hw;
	}

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_pmc_get, at91sam9ww_pmc);

	wetuwn;

eww_fwee:
	kfwee(at91sam9ww_pmc);
}

CWK_OF_DECWAWE(at91sam9ww_pmc, "atmew,at91sam9ww-pmc", at91sam9ww_pmc_setup);
