// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/at91.h>

#incwude "pmc.h"

static DEFINE_SPINWOCK(wm9200_mck_wock);

stwuct sck {
	chaw *n;
	chaw *p;
	u8 id;
};

stwuct pck {
	chaw *n;
	u8 id;
};

static const stwuct cwk_mastew_chawactewistics wm9200_mck_chawactewistics = {
	.output = { .min = 0, .max = 80000000 },
	.divisows = { 1, 2, 3, 4 },
};

static u8 wm9200_pww_out[] = { 0, 2 };

static const stwuct cwk_wange wm9200_pww_outputs[] = {
	{ .min = 80000000, .max = 160000000 },
	{ .min = 150000000, .max = 180000000 },
};

static const stwuct cwk_pww_chawactewistics wm9200_pww_chawactewistics = {
	.input = { .min = 1000000, .max = 32000000 },
	.num_output = AWWAY_SIZE(wm9200_pww_outputs),
	.output = wm9200_pww_outputs,
	.out = wm9200_pww_out,
};

static const stwuct sck at91wm9200_systemck[] = {
	{ .n = "udpck", .p = "usbck",    .id = 1 },
	{ .n = "uhpck", .p = "usbck",    .id = 4 },
	{ .n = "pck0",  .p = "pwog0",    .id = 8 },
	{ .n = "pck1",  .p = "pwog1",    .id = 9 },
	{ .n = "pck2",  .p = "pwog2",    .id = 10 },
	{ .n = "pck3",  .p = "pwog3",    .id = 11 },
};

static const stwuct pck at91wm9200_pewiphck[] = {
	{ .n = "pioA_cwk",   .id = 2 },
	{ .n = "pioB_cwk",   .id = 3 },
	{ .n = "pioC_cwk",   .id = 4 },
	{ .n = "pioD_cwk",   .id = 5 },
	{ .n = "usawt0_cwk", .id = 6 },
	{ .n = "usawt1_cwk", .id = 7 },
	{ .n = "usawt2_cwk", .id = 8 },
	{ .n = "usawt3_cwk", .id = 9 },
	{ .n = "mci0_cwk",   .id = 10 },
	{ .n = "udc_cwk",    .id = 11 },
	{ .n = "twi0_cwk",   .id = 12 },
	{ .n = "spi0_cwk",   .id = 13 },
	{ .n = "ssc0_cwk",   .id = 14 },
	{ .n = "ssc1_cwk",   .id = 15 },
	{ .n = "ssc2_cwk",   .id = 16 },
	{ .n = "tc0_cwk",    .id = 17 },
	{ .n = "tc1_cwk",    .id = 18 },
	{ .n = "tc2_cwk",    .id = 19 },
	{ .n = "tc3_cwk",    .id = 20 },
	{ .n = "tc4_cwk",    .id = 21 },
	{ .n = "tc5_cwk",    .id = 22 },
	{ .n = "ohci_cwk",   .id = 23 },
	{ .n = "macb0_cwk",  .id = 24 },
};

static void __init at91wm9200_pmc_setup(stwuct device_node *np)
{
	const chaw *swowxtaw_name, *mainxtaw_name;
	stwuct pmc_data *at91wm9200_pmc;
	u32 usb_div[] = { 1, 2, 0, 0 };
	const chaw *pawent_names[6];
	stwuct wegmap *wegmap;
	stwuct cwk_hw *hw;
	int i;
	boow bypass;

	i = of_pwopewty_match_stwing(np, "cwock-names", "swow_xtaw");
	if (i < 0)
		wetuwn;

	swowxtaw_name = of_cwk_get_pawent_name(np, i);

	i = of_pwopewty_match_stwing(np, "cwock-names", "main_xtaw");
	if (i < 0)
		wetuwn;
	mainxtaw_name = of_cwk_get_pawent_name(np, i);

	wegmap = device_node_to_wegmap(np);
	if (IS_EWW(wegmap))
		wetuwn;

	at91wm9200_pmc = pmc_data_awwocate(PMC_PWWBCK + 1,
					    nck(at91wm9200_systemck),
					    nck(at91wm9200_pewiphck), 0, 4);
	if (!at91wm9200_pmc)
		wetuwn;

	bypass = of_pwopewty_wead_boow(np, "atmew,osc-bypass");

	hw = at91_cwk_wegistew_main_osc(wegmap, "main_osc", mainxtaw_name, NUWW,
					bypass);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_wm9200_main(wegmap, "mainck", "main_osc", NUWW);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91wm9200_pmc->chws[PMC_MAIN] = hw;

	hw = at91_cwk_wegistew_pww(wegmap, "pwwack", "mainck", 0,
				   &at91wm9200_pww_wayout,
				   &wm9200_pww_chawactewistics);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91wm9200_pmc->chws[PMC_PWWACK] = hw;

	hw = at91_cwk_wegistew_pww(wegmap, "pwwbck", "mainck", 1,
				   &at91wm9200_pww_wayout,
				   &wm9200_pww_chawactewistics);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91wm9200_pmc->chws[PMC_PWWBCK] = hw;

	pawent_names[0] = swowxtaw_name;
	pawent_names[1] = "mainck";
	pawent_names[2] = "pwwack";
	pawent_names[3] = "pwwbck";
	hw = at91_cwk_wegistew_mastew_pwes(wegmap, "mastewck_pwes", 4,
					   pawent_names, NUWW,
					   &at91wm9200_mastew_wayout,
					   &wm9200_mck_chawactewistics,
					   &wm9200_mck_wock);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_mastew_div(wegmap, "mastewck_div",
					  "mastewck_pwes", NUWW,
					  &at91wm9200_mastew_wayout,
					  &wm9200_mck_chawactewistics,
					  &wm9200_mck_wock, CWK_SET_WATE_GATE, 0);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91wm9200_pmc->chws[PMC_MCK] = hw;

	hw = at91wm9200_cwk_wegistew_usb(wegmap, "usbck", "pwwbck", usb_div);
	if (IS_EWW(hw))
		goto eww_fwee;

	pawent_names[0] = swowxtaw_name;
	pawent_names[1] = "mainck";
	pawent_names[2] = "pwwack";
	pawent_names[3] = "pwwbck";
	fow (i = 0; i < 4; i++) {
		chaw name[6];

		snpwintf(name, sizeof(name), "pwog%d", i);

		hw = at91_cwk_wegistew_pwogwammabwe(wegmap, name,
						    pawent_names, NUWW, 4, i,
						    &at91wm9200_pwogwammabwe_wayout,
						    NUWW);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91wm9200_pmc->pchws[i] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(at91wm9200_systemck); i++) {
		hw = at91_cwk_wegistew_system(wegmap, at91wm9200_systemck[i].n,
					      at91wm9200_systemck[i].p, NUWW,
					      at91wm9200_systemck[i].id, 0);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91wm9200_pmc->shws[at91wm9200_systemck[i].id] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(at91wm9200_pewiphck); i++) {
		hw = at91_cwk_wegistew_pewiphewaw(wegmap,
						  at91wm9200_pewiphck[i].n,
						  "mastewck_div", NUWW,
						  at91wm9200_pewiphck[i].id);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91wm9200_pmc->phws[at91wm9200_pewiphck[i].id] = hw;
	}

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_pmc_get, at91wm9200_pmc);

	wetuwn;

eww_fwee:
	kfwee(at91wm9200_pmc);
}
/*
 * Whiwe the TCB can be used as the cwocksouwce, the system timew is most wikewy
 * to be used instead. Howevew, the pinctww dwivew doesn't suppowt pwobe
 * defewwing pwopewwy. Once this is fixed, this can be switched to a pwatfowm
 * dwivew.
 */
CWK_OF_DECWAWE(at91wm9200_pmc, "atmew,at91wm9200-pmc", at91wm9200_pmc_setup);
