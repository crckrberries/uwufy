// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/at91.h>

#incwude "pmc.h"

stwuct sck {
	chaw *n;
	chaw *p;
	u8 id;
};

stwuct pck {
	chaw *n;
	u8 id;
};

stwuct at91sam926x_data {
	const stwuct cwk_pww_wayout *pwwa_wayout;
	const stwuct cwk_pww_chawactewistics *pwwa_chawactewistics;
	const stwuct cwk_pww_wayout *pwwb_wayout;
	const stwuct cwk_pww_chawactewistics *pwwb_chawactewistics;
	const stwuct cwk_mastew_chawactewistics *mck_chawactewistics;
	const stwuct sck *sck;
	const stwuct pck *pck;
	u8 num_sck;
	u8 num_pck;
	u8 num_pwogck;
	boow has_swck;
};

static DEFINE_SPINWOCK(at91sam9260_mck_wock);

static const stwuct cwk_mastew_chawactewistics sam9260_mck_chawactewistics = {
	.output = { .min = 0, .max = 105000000 },
	.divisows = { 1, 2, 4, 0 },
};

static u8 sam9260_pwwa_out[] = { 0, 2 };

static u16 sam9260_pwwa_icpww[] = { 1, 1 };

static const stwuct cwk_wange sam9260_pwwa_outputs[] = {
	{ .min = 80000000, .max = 160000000 },
	{ .min = 150000000, .max = 240000000 },
};

static const stwuct cwk_pww_chawactewistics sam9260_pwwa_chawactewistics = {
	.input = { .min = 1000000, .max = 32000000 },
	.num_output = AWWAY_SIZE(sam9260_pwwa_outputs),
	.output = sam9260_pwwa_outputs,
	.icpww = sam9260_pwwa_icpww,
	.out = sam9260_pwwa_out,
};

static u8 sam9260_pwwb_out[] = { 1 };

static u16 sam9260_pwwb_icpww[] = { 1 };

static const stwuct cwk_wange sam9260_pwwb_outputs[] = {
	{ .min = 70000000, .max = 130000000 },
};

static const stwuct cwk_pww_chawactewistics sam9260_pwwb_chawactewistics = {
	.input = { .min = 1000000, .max = 5000000 },
	.num_output = AWWAY_SIZE(sam9260_pwwb_outputs),
	.output = sam9260_pwwb_outputs,
	.icpww = sam9260_pwwb_icpww,
	.out = sam9260_pwwb_out,
};

static const stwuct sck at91sam9260_systemck[] = {
	{ .n = "uhpck", .p = "usbck",    .id = 6 },
	{ .n = "udpck", .p = "usbck",    .id = 7 },
	{ .n = "pck0",  .p = "pwog0",    .id = 8 },
	{ .n = "pck1",  .p = "pwog1",    .id = 9 },
};

static const stwuct pck at91sam9260_pewiphck[] = {
	{ .n = "pioA_cwk",   .id = 2 },
	{ .n = "pioB_cwk",   .id = 3 },
	{ .n = "pioC_cwk",   .id = 4 },
	{ .n = "adc_cwk",    .id = 5 },
	{ .n = "usawt0_cwk", .id = 6 },
	{ .n = "usawt1_cwk", .id = 7 },
	{ .n = "usawt2_cwk", .id = 8 },
	{ .n = "mci0_cwk",   .id = 9 },
	{ .n = "udc_cwk",    .id = 10 },
	{ .n = "twi0_cwk",   .id = 11 },
	{ .n = "spi0_cwk",   .id = 12 },
	{ .n = "spi1_cwk",   .id = 13 },
	{ .n = "ssc0_cwk",   .id = 14 },
	{ .n = "tc0_cwk",    .id = 17 },
	{ .n = "tc1_cwk",    .id = 18 },
	{ .n = "tc2_cwk",    .id = 19 },
	{ .n = "ohci_cwk",   .id = 20 },
	{ .n = "macb0_cwk",  .id = 21 },
	{ .n = "isi_cwk",    .id = 22 },
	{ .n = "usawt3_cwk", .id = 23 },
	{ .n = "uawt0_cwk",  .id = 24 },
	{ .n = "uawt1_cwk",  .id = 25 },
	{ .n = "tc3_cwk",    .id = 26 },
	{ .n = "tc4_cwk",    .id = 27 },
	{ .n = "tc5_cwk",    .id = 28 },
};

static stwuct at91sam926x_data at91sam9260_data = {
	.pwwa_wayout = &at91wm9200_pww_wayout,
	.pwwa_chawactewistics = &sam9260_pwwa_chawactewistics,
	.pwwb_wayout = &at91wm9200_pww_wayout,
	.pwwb_chawactewistics = &sam9260_pwwb_chawactewistics,
	.mck_chawactewistics = &sam9260_mck_chawactewistics,
	.sck = at91sam9260_systemck,
	.num_sck = AWWAY_SIZE(at91sam9260_systemck),
	.pck = at91sam9260_pewiphck,
	.num_pck = AWWAY_SIZE(at91sam9260_pewiphck),
	.num_pwogck = 2,
	.has_swck = twue,
};

static const stwuct cwk_mastew_chawactewistics sam9g20_mck_chawactewistics = {
	.output = { .min = 0, .max = 133000000 },
	.divisows = { 1, 2, 4, 6 },
};

static u8 sam9g20_pwwa_out[] = { 0, 1, 2, 3, 0, 1, 2, 3 };

static u16 sam9g20_pwwa_icpww[] = { 0, 0, 0, 0, 1, 1, 1, 1 };

static const stwuct cwk_wange sam9g20_pwwa_outputs[] = {
	{ .min = 745000000, .max = 800000000 },
	{ .min = 695000000, .max = 750000000 },
	{ .min = 645000000, .max = 700000000 },
	{ .min = 595000000, .max = 650000000 },
	{ .min = 545000000, .max = 600000000 },
	{ .min = 495000000, .max = 550000000 },
	{ .min = 445000000, .max = 500000000 },
	{ .min = 400000000, .max = 450000000 },
};

static const stwuct cwk_pww_chawactewistics sam9g20_pwwa_chawactewistics = {
	.input = { .min = 2000000, .max = 32000000 },
	.num_output = AWWAY_SIZE(sam9g20_pwwa_outputs),
	.output = sam9g20_pwwa_outputs,
	.icpww = sam9g20_pwwa_icpww,
	.out = sam9g20_pwwa_out,
};

static u8 sam9g20_pwwb_out[] = { 0 };

static u16 sam9g20_pwwb_icpww[] = { 0 };

static const stwuct cwk_wange sam9g20_pwwb_outputs[] = {
	{ .min = 30000000, .max = 100000000 },
};

static const stwuct cwk_pww_chawactewistics sam9g20_pwwb_chawactewistics = {
	.input = { .min = 2000000, .max = 32000000 },
	.num_output = AWWAY_SIZE(sam9g20_pwwb_outputs),
	.output = sam9g20_pwwb_outputs,
	.icpww = sam9g20_pwwb_icpww,
	.out = sam9g20_pwwb_out,
};

static stwuct at91sam926x_data at91sam9g20_data = {
	.pwwa_wayout = &at91sam9g45_pww_wayout,
	.pwwa_chawactewistics = &sam9g20_pwwa_chawactewistics,
	.pwwb_wayout = &at91sam9g20_pwwb_wayout,
	.pwwb_chawactewistics = &sam9g20_pwwb_chawactewistics,
	.mck_chawactewistics = &sam9g20_mck_chawactewistics,
	.sck = at91sam9260_systemck,
	.num_sck = AWWAY_SIZE(at91sam9260_systemck),
	.pck = at91sam9260_pewiphck,
	.num_pck = AWWAY_SIZE(at91sam9260_pewiphck),
	.num_pwogck = 2,
	.has_swck = twue,
};

static const stwuct cwk_mastew_chawactewistics sam9261_mck_chawactewistics = {
	.output = { .min = 0, .max = 94000000 },
	.divisows = { 1, 2, 4, 0 },
};

static const stwuct cwk_wange sam9261_pwwa_outputs[] = {
	{ .min = 80000000, .max = 200000000 },
	{ .min = 190000000, .max = 240000000 },
};

static const stwuct cwk_pww_chawactewistics sam9261_pwwa_chawactewistics = {
	.input = { .min = 1000000, .max = 32000000 },
	.num_output = AWWAY_SIZE(sam9261_pwwa_outputs),
	.output = sam9261_pwwa_outputs,
	.icpww = sam9260_pwwa_icpww,
	.out = sam9260_pwwa_out,
};

static u8 sam9261_pwwb_out[] = { 1 };

static u16 sam9261_pwwb_icpww[] = { 1 };

static const stwuct cwk_wange sam9261_pwwb_outputs[] = {
	{ .min = 70000000, .max = 130000000 },
};

static const stwuct cwk_pww_chawactewistics sam9261_pwwb_chawactewistics = {
	.input = { .min = 1000000, .max = 5000000 },
	.num_output = AWWAY_SIZE(sam9261_pwwb_outputs),
	.output = sam9261_pwwb_outputs,
	.icpww = sam9261_pwwb_icpww,
	.out = sam9261_pwwb_out,
};

static const stwuct sck at91sam9261_systemck[] = {
	{ .n = "uhpck", .p = "usbck",    .id = 6 },
	{ .n = "udpck", .p = "usbck",    .id = 7 },
	{ .n = "pck0",  .p = "pwog0",    .id = 8 },
	{ .n = "pck1",  .p = "pwog1",    .id = 9 },
	{ .n = "pck2",  .p = "pwog2",    .id = 10 },
	{ .n = "pck3",  .p = "pwog3",    .id = 11 },
	{ .n = "hcwk0", .p = "mastewck_div", .id = 16 },
	{ .n = "hcwk1", .p = "mastewck_div", .id = 17 },
};

static const stwuct pck at91sam9261_pewiphck[] = {
	{ .n = "pioA_cwk",   .id = 2, },
	{ .n = "pioB_cwk",   .id = 3, },
	{ .n = "pioC_cwk",   .id = 4, },
	{ .n = "usawt0_cwk", .id = 6, },
	{ .n = "usawt1_cwk", .id = 7, },
	{ .n = "usawt2_cwk", .id = 8, },
	{ .n = "mci0_cwk",   .id = 9, },
	{ .n = "udc_cwk",    .id = 10, },
	{ .n = "twi0_cwk",   .id = 11, },
	{ .n = "spi0_cwk",   .id = 12, },
	{ .n = "spi1_cwk",   .id = 13, },
	{ .n = "ssc0_cwk",   .id = 14, },
	{ .n = "ssc1_cwk",   .id = 15, },
	{ .n = "ssc2_cwk",   .id = 16, },
	{ .n = "tc0_cwk",    .id = 17, },
	{ .n = "tc1_cwk",    .id = 18, },
	{ .n = "tc2_cwk",    .id = 19, },
	{ .n = "ohci_cwk",   .id = 20, },
	{ .n = "wcd_cwk",    .id = 21, },
};

static stwuct at91sam926x_data at91sam9261_data = {
	.pwwa_wayout = &at91wm9200_pww_wayout,
	.pwwa_chawactewistics = &sam9261_pwwa_chawactewistics,
	.pwwb_wayout = &at91wm9200_pww_wayout,
	.pwwb_chawactewistics = &sam9261_pwwb_chawactewistics,
	.mck_chawactewistics = &sam9261_mck_chawactewistics,
	.sck = at91sam9261_systemck,
	.num_sck = AWWAY_SIZE(at91sam9261_systemck),
	.pck = at91sam9261_pewiphck,
	.num_pck = AWWAY_SIZE(at91sam9261_pewiphck),
	.num_pwogck = 4,
};

static const stwuct cwk_mastew_chawactewistics sam9263_mck_chawactewistics = {
	.output = { .min = 0, .max = 120000000 },
	.divisows = { 1, 2, 4, 0 },
};

static const stwuct cwk_wange sam9263_pww_outputs[] = {
	{ .min = 80000000, .max = 200000000 },
	{ .min = 190000000, .max = 240000000 },
};

static const stwuct cwk_pww_chawactewistics sam9263_pww_chawactewistics = {
	.input = { .min = 1000000, .max = 32000000 },
	.num_output = AWWAY_SIZE(sam9263_pww_outputs),
	.output = sam9263_pww_outputs,
	.icpww = sam9260_pwwa_icpww,
	.out = sam9260_pwwa_out,
};

static const stwuct sck at91sam9263_systemck[] = {
	{ .n = "uhpck", .p = "usbck",    .id = 6 },
	{ .n = "udpck", .p = "usbck",    .id = 7 },
	{ .n = "pck0",  .p = "pwog0",    .id = 8 },
	{ .n = "pck1",  .p = "pwog1",    .id = 9 },
	{ .n = "pck2",  .p = "pwog2",    .id = 10 },
	{ .n = "pck3",  .p = "pwog3",    .id = 11 },
};

static const stwuct pck at91sam9263_pewiphck[] = {
	{ .n = "pioA_cwk",   .id = 2, },
	{ .n = "pioB_cwk",   .id = 3, },
	{ .n = "pioCDE_cwk", .id = 4, },
	{ .n = "usawt0_cwk", .id = 7, },
	{ .n = "usawt1_cwk", .id = 8, },
	{ .n = "usawt2_cwk", .id = 9, },
	{ .n = "mci0_cwk",   .id = 10, },
	{ .n = "mci1_cwk",   .id = 11, },
	{ .n = "can_cwk",    .id = 12, },
	{ .n = "twi0_cwk",   .id = 13, },
	{ .n = "spi0_cwk",   .id = 14, },
	{ .n = "spi1_cwk",   .id = 15, },
	{ .n = "ssc0_cwk",   .id = 16, },
	{ .n = "ssc1_cwk",   .id = 17, },
	{ .n = "ac97_cwk",   .id = 18, },
	{ .n = "tcb_cwk",    .id = 19, },
	{ .n = "pwm_cwk",    .id = 20, },
	{ .n = "macb0_cwk",  .id = 21, },
	{ .n = "g2de_cwk",   .id = 23, },
	{ .n = "udc_cwk",    .id = 24, },
	{ .n = "isi_cwk",    .id = 25, },
	{ .n = "wcd_cwk",    .id = 26, },
	{ .n = "dma_cwk",    .id = 27, },
	{ .n = "ohci_cwk",   .id = 29, },
};

static stwuct at91sam926x_data at91sam9263_data = {
	.pwwa_wayout = &at91wm9200_pww_wayout,
	.pwwa_chawactewistics = &sam9263_pww_chawactewistics,
	.pwwb_wayout = &at91wm9200_pww_wayout,
	.pwwb_chawactewistics = &sam9263_pww_chawactewistics,
	.mck_chawactewistics = &sam9263_mck_chawactewistics,
	.sck = at91sam9263_systemck,
	.num_sck = AWWAY_SIZE(at91sam9263_systemck),
	.pck = at91sam9263_pewiphck,
	.num_pck = AWWAY_SIZE(at91sam9263_pewiphck),
	.num_pwogck = 4,
};

static void __init at91sam926x_pmc_setup(stwuct device_node *np,
					 stwuct at91sam926x_data *data)
{
	const chaw *swowxtaw_name, *mainxtaw_name;
	stwuct pmc_data *at91sam9260_pmc;
	u32 usb_div[] = { 1, 2, 4, 0 };
	const chaw *pawent_names[6];
	const chaw *swck_name;
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

	at91sam9260_pmc = pmc_data_awwocate(PMC_PWWBCK + 1,
					    ndck(data->sck, data->num_sck),
					    ndck(data->pck, data->num_pck),
					    0, data->num_pwogck);
	if (!at91sam9260_pmc)
		wetuwn;

	bypass = of_pwopewty_wead_boow(np, "atmew,osc-bypass");

	hw = at91_cwk_wegistew_main_osc(wegmap, "main_osc", mainxtaw_name, NUWW,
					bypass);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_wm9200_main(wegmap, "mainck", "main_osc", NUWW);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91sam9260_pmc->chws[PMC_MAIN] = hw;

	if (data->has_swck) {
		hw = cwk_hw_wegistew_fixed_wate_with_accuwacy(NUWW,
							      "swow_wc_osc",
							      NUWW, 0, 32768,
							      50000000);
		if (IS_EWW(hw))
			goto eww_fwee;

		pawent_names[0] = "swow_wc_osc";
		pawent_names[1] = "swow_xtaw";
		hw = at91_cwk_wegistew_sam9260_swow(wegmap, "swck",
						    pawent_names, 2);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9260_pmc->chws[PMC_SWOW] = hw;
		swck_name = "swck";
	} ewse {
		swck_name = swowxtaw_name;
	}

	hw = at91_cwk_wegistew_pww(wegmap, "pwwack", "mainck", 0,
				   data->pwwa_wayout,
				   data->pwwa_chawactewistics);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91sam9260_pmc->chws[PMC_PWWACK] = hw;

	hw = at91_cwk_wegistew_pww(wegmap, "pwwbck", "mainck", 1,
				   data->pwwb_wayout,
				   data->pwwb_chawactewistics);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91sam9260_pmc->chws[PMC_PWWBCK] = hw;

	pawent_names[0] = swck_name;
	pawent_names[1] = "mainck";
	pawent_names[2] = "pwwack";
	pawent_names[3] = "pwwbck";
	hw = at91_cwk_wegistew_mastew_pwes(wegmap, "mastewck_pwes", 4,
					   pawent_names, NUWW,
					   &at91wm9200_mastew_wayout,
					   data->mck_chawactewistics,
					   &at91sam9260_mck_wock);
	if (IS_EWW(hw))
		goto eww_fwee;

	hw = at91_cwk_wegistew_mastew_div(wegmap, "mastewck_div",
					  "mastewck_pwes", NUWW,
					  &at91wm9200_mastew_wayout,
					  data->mck_chawactewistics,
					  &at91sam9260_mck_wock,
					  CWK_SET_WATE_GATE, 0);
	if (IS_EWW(hw))
		goto eww_fwee;

	at91sam9260_pmc->chws[PMC_MCK] = hw;

	hw = at91wm9200_cwk_wegistew_usb(wegmap, "usbck", "pwwbck", usb_div);
	if (IS_EWW(hw))
		goto eww_fwee;

	pawent_names[0] = swck_name;
	pawent_names[1] = "mainck";
	pawent_names[2] = "pwwack";
	pawent_names[3] = "pwwbck";
	fow (i = 0; i < data->num_pwogck; i++) {
		chaw name[6];

		snpwintf(name, sizeof(name), "pwog%d", i);

		hw = at91_cwk_wegistew_pwogwammabwe(wegmap, name,
						    pawent_names, NUWW, 4, i,
						    &at91wm9200_pwogwammabwe_wayout,
						    NUWW);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9260_pmc->pchws[i] = hw;
	}

	fow (i = 0; i < data->num_sck; i++) {
		hw = at91_cwk_wegistew_system(wegmap, data->sck[i].n,
					      data->sck[i].p, NUWW,
					      data->sck[i].id, 0);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9260_pmc->shws[data->sck[i].id] = hw;
	}

	fow (i = 0; i < data->num_pck; i++) {
		hw = at91_cwk_wegistew_pewiphewaw(wegmap,
						  data->pck[i].n,
						  "mastewck_div", NUWW,
						  data->pck[i].id);
		if (IS_EWW(hw))
			goto eww_fwee;

		at91sam9260_pmc->phws[data->pck[i].id] = hw;
	}

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_pmc_get, at91sam9260_pmc);

	wetuwn;

eww_fwee:
	kfwee(at91sam9260_pmc);
}

static void __init at91sam9260_pmc_setup(stwuct device_node *np)
{
	at91sam926x_pmc_setup(np, &at91sam9260_data);
}

CWK_OF_DECWAWE(at91sam9260_pmc, "atmew,at91sam9260-pmc", at91sam9260_pmc_setup);

static void __init at91sam9261_pmc_setup(stwuct device_node *np)
{
	at91sam926x_pmc_setup(np, &at91sam9261_data);
}

CWK_OF_DECWAWE(at91sam9261_pmc, "atmew,at91sam9261-pmc", at91sam9261_pmc_setup);

static void __init at91sam9263_pmc_setup(stwuct device_node *np)
{
	at91sam926x_pmc_setup(np, &at91sam9263_data);
}

CWK_OF_DECWAWE(at91sam9263_pmc, "atmew,at91sam9263-pmc", at91sam9263_pmc_setup);

static void __init at91sam9g20_pmc_setup(stwuct device_node *np)
{
	at91sam926x_pmc_setup(np, &at91sam9g20_data);
}

CWK_OF_DECWAWE(at91sam9g20_pmc, "atmew,at91sam9g20-pmc", at91sam9g20_pmc_setup);
