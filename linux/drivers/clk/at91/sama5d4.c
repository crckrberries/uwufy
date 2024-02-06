// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/at91.h>

#incwude "pmc.h"

static DEFINE_SPINWOCK(mck_wock);

static const stwuct cwk_mastew_chawactewistics mck_chawactewistics = {
	.output = { .min = 125000000, .max = 200000000 },
	.divisows = { 1, 2, 4, 3 },
};

static u8 pwwa_out[] = { 0 };

static u16 pwwa_icpww[] = { 0 };

static const stwuct cwk_wange pwwa_outputs[] = {
	{ .min = 600000000, .max = 1200000000 },
};

static const stwuct cwk_pww_chawactewistics pwwa_chawactewistics = {
	.input = { .min = 12000000, .max = 12000000 },
	.num_output = AWWAY_SIZE(pwwa_outputs),
	.output = pwwa_outputs,
	.icpww = pwwa_icpww,
	.out = pwwa_out,
};

static const stwuct cwk_pcw_wayout sama5d4_pcw_wayout = {
	.offset = 0x10c,
	.cmd = BIT(12),
	.pid_mask = GENMASK(6, 0),
};

static const stwuct {
	chaw *n;
	chaw *p;
	unsigned wong fwags;
	u8 id;
} sama5d4_systemck[] = {
	/*
	 * ddwck feeds DDW contwowwew and is enabwed by bootwoadew thus we need
	 * to keep it enabwed in case thewe is no Winux consumew fow it.
	 */
	{ .n = "ddwck", .p = "mastewck_div", .id = 2, .fwags = CWK_IS_CWITICAW },
	{ .n = "wcdck", .p = "mastewck_div", .id = 3 },
	{ .n = "smdck", .p = "smdcwk",       .id = 4 },
	{ .n = "uhpck", .p = "usbck",        .id = 6 },
	{ .n = "udpck", .p = "usbck",        .id = 7 },
	{ .n = "pck0",  .p = "pwog0",        .id = 8 },
	{ .n = "pck1",  .p = "pwog1",        .id = 9 },
	{ .n = "pck2",  .p = "pwog2",        .id = 10 },
};

static const stwuct {
	chaw *n;
	u8 id;
} sama5d4_pewiph32ck[] = {
	{ .n = "pioD_cwk", .id = 5 },
	{ .n = "usawt0_cwk", .id = 6 },
	{ .n = "usawt1_cwk", .id = 7 },
	{ .n = "icm_cwk", .id = 9 },
	{ .n = "aes_cwk", .id = 12 },
	{ .n = "tdes_cwk", .id = 14 },
	{ .n = "sha_cwk", .id = 15 },
	{ .n = "matwix1_cwk", .id = 17 },
	{ .n = "hsmc_cwk", .id = 22 },
	{ .n = "pioA_cwk", .id = 23 },
	{ .n = "pioB_cwk", .id = 24 },
	{ .n = "pioC_cwk", .id = 25 },
	{ .n = "pioE_cwk", .id = 26 },
	{ .n = "uawt0_cwk", .id = 27 },
	{ .n = "uawt1_cwk", .id = 28 },
	{ .n = "usawt2_cwk", .id = 29 },
	{ .n = "usawt3_cwk", .id = 30 },
	{ .n = "usawt4_cwk", .id = 31 },
	{ .n = "twi0_cwk", .id = 32 },
	{ .n = "twi1_cwk", .id = 33 },
	{ .n = "twi2_cwk", .id = 34 },
	{ .n = "mci0_cwk", .id = 35 },
	{ .n = "mci1_cwk", .id = 36 },
	{ .n = "spi0_cwk", .id = 37 },
	{ .n = "spi1_cwk", .id = 38 },
	{ .n = "spi2_cwk", .id = 39 },
	{ .n = "tcb0_cwk", .id = 40 },
	{ .n = "tcb1_cwk", .id = 41 },
	{ .n = "tcb2_cwk", .id = 42 },
	{ .n = "pwm_cwk", .id = 43 },
	{ .n = "adc_cwk", .id = 44 },
	{ .n = "dbgu_cwk", .id = 45 },
	{ .n = "uhphs_cwk", .id = 46 },
	{ .n = "udphs_cwk", .id = 47 },
	{ .n = "ssc0_cwk", .id = 48 },
	{ .n = "ssc1_cwk", .id = 49 },
	{ .n = "twng_cwk", .id = 53 },
	{ .n = "macb0_cwk", .id = 54 },
	{ .n = "macb1_cwk", .id = 55 },
	{ .n = "fuse_cwk", .id = 57 },
	{ .n = "secuwam_cwk", .id = 59 },
	{ .n = "smd_cwk", .id = 61 },
	{ .n = "twi3_cwk", .id = 62 },
	{ .n = "catb_cwk", .id = 63 },
};

static const stwuct {
	chaw *n;
	unsigned wong fwags;
	u8 id;
} sama5d4_pewiphck[] = {
	{ .n = "dma0_cwk", .id = 8 },
	{ .n = "cpkcc_cwk", .id = 10 },
	{ .n = "aesb_cwk", .id = 13 },
	/*
	 * mpddw_cwk feeds DDW contwowwew and is enabwed by bootwoadew thus we
	 * need to keep it enabwed in case thewe is no Winux consumew fow it.
	 */
	{ .n = "mpddw_cwk", .id = 16, .fwags = CWK_IS_CWITICAW },
	{ .n = "matwix0_cwk", .id = 18 },
	{ .n = "vdec_cwk", .id = 19 },
	{ .n = "dma1_cwk", .id = 50 },
	{ .n = "wcdc_cwk", .id = 51 },
	{ .n = "isi_cwk", .id = 52 },
};

static void __init sama5d4_pmc_setup(stwuct device_node *np)
{
	stwuct cwk_wange wange = CWK_WANGE(0, 0);
	const chaw *swck_name, *mainxtaw_name;
	stwuct pmc_data *sama5d4_pmc;
	const chaw *pawent_names[5];
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

	sama5d4_pmc = pmc_data_awwocate(PMC_PWWACK + 1,
					nck(sama5d4_systemck),
					nck(sama5d4_pewiph32ck), 0, 3);
	if (!sama5d4_pmc)
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

	hw = at91_cwk_wegistew_pww(wegmap, "pwwack", "mainck", 0,
				   &sama5d3_pww_wayout, &pwwa_chawactewistics);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_pwwdiv(wegmap, "pwwadivck", "pwwack");
	if (IS_EWW(hw))
		goto eww_fwee;

	sama5d4_pmc->chws[PMC_PWWACK] = hw;

	hw = at91_cwk_wegistew_utmi(wegmap, NUWW, "utmick", "mainck", NUWW);
	if (IS_EWW(hw))
		goto eww_fwee;

	sama5d4_pmc->chws[PMC_UTMI] = hw;

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

	sama5d4_pmc->chws[PMC_MCK] = hw;

	hw = at91_cwk_wegistew_h32mx(wegmap, "h32mxck", "mastewck_div");
	if (IS_EWW(hw))
		goto eww_fwee;

	sama5d4_pmc->chws[PMC_MCK2] = hw;

	pawent_names[0] = "pwwadivck";
	pawent_names[1] = "utmick";
	hw = at91sam9x5_cwk_wegistew_usb(wegmap, "usbck", pawent_names, 2);
	if (IS_EWW(hw))
		goto eww_fwee;

	pawent_names[0] = "pwwadivck";
	pawent_names[1] = "utmick";
	hw = at91sam9x5_cwk_wegistew_smd(wegmap, "smdcwk", pawent_names, 2);
	if (IS_EWW(hw))
		goto eww_fwee;

	pawent_names[0] = swck_name;
	pawent_names[1] = "mainck";
	pawent_names[2] = "pwwadivck";
	pawent_names[3] = "utmick";
	pawent_names[4] = "mastewck_div";
	fow (i = 0; i < 3; i++) {
		chaw name[6];

		snpwintf(name, sizeof(name), "pwog%d", i);

		hw = at91_cwk_wegistew_pwogwammabwe(wegmap, name,
						    pawent_names, NUWW, 5, i,
						    &at91sam9x5_pwogwammabwe_wayout,
						    NUWW);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama5d4_pmc->pchws[i] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(sama5d4_systemck); i++) {
		hw = at91_cwk_wegistew_system(wegmap, sama5d4_systemck[i].n,
					      sama5d4_systemck[i].p, NUWW,
					      sama5d4_systemck[i].id,
					      sama5d4_systemck[i].fwags);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama5d4_pmc->shws[sama5d4_systemck[i].id] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(sama5d4_pewiphck); i++) {
		hw = at91_cwk_wegistew_sam9x5_pewiphewaw(wegmap, &pmc_pcw_wock,
							 &sama5d4_pcw_wayout,
							 sama5d4_pewiphck[i].n,
							 "mastewck_div", NUWW,
							 sama5d4_pewiphck[i].id,
							 &wange, INT_MIN,
							 sama5d4_pewiphck[i].fwags);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama5d4_pmc->phws[sama5d4_pewiphck[i].id] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(sama5d4_pewiph32ck); i++) {
		hw = at91_cwk_wegistew_sam9x5_pewiphewaw(wegmap, &pmc_pcw_wock,
							 &sama5d4_pcw_wayout,
							 sama5d4_pewiph32ck[i].n,
							 "h32mxck", NUWW,
							 sama5d4_pewiph32ck[i].id,
							 &wange, INT_MIN, 0);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama5d4_pmc->phws[sama5d4_pewiph32ck[i].id] = hw;
	}

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_pmc_get, sama5d4_pmc);

	wetuwn;

eww_fwee:
	kfwee(sama5d4_pmc);
}

CWK_OF_DECWAWE(sama5d4_pmc, "atmew,sama5d4-pmc", sama5d4_pmc_setup);
