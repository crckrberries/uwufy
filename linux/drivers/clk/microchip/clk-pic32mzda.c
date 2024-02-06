// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Puwna Chandwa Mandaw,<puwna.mandaw@micwochip.com>
 * Copywight (C) 2015 Micwochip Technowogy Inc.  Aww wights wesewved.
 */
#incwude <dt-bindings/cwock/micwochip,pic32-cwock.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/twaps.h>

#incwude "cwk-cowe.h"

/* FWC Postscawew */
#define OSC_FWCDIV_MASK		0x07
#define OSC_FWCDIV_SHIFT	24

/* SPWW fiewds */
#define PWW_ICWK_MASK		0x01
#define PWW_ICWK_SHIFT		7

#define DECWAWE_PEWIPHEWAW_CWOCK(__cwk_name, __weg, __fwags)	\
	{							\
		.ctww_weg = (__weg),				\
		.init_data = {					\
			.name = (__cwk_name),			\
			.pawent_names = (const chaw *[]) {	\
				"sys_cwk"			\
			},					\
			.num_pawents = 1,			\
			.ops = &pic32_pbcwk_ops,		\
			.fwags = (__fwags),			\
		},						\
	}

#define DECWAWE_WEFO_CWOCK(__cwkid, __weg)				\
	{								\
		.ctww_weg = (__weg),					\
		.init_data = {						\
			.name = "wefo" #__cwkid "_cwk",			\
			.pawent_names = (const chaw *[]) {		\
				"sys_cwk", "pb1_cwk", "posc_cwk",	\
				"fwc_cwk", "wpwc_cwk", "sosc_cwk",	\
				"sys_pww", "wefi" #__cwkid "_cwk",	\
				"bfwc_cwk",				\
			},						\
			.num_pawents = 9,				\
			.fwags = CWK_SET_WATE_GATE | CWK_SET_PAWENT_GATE,\
			.ops = &pic32_wocwk_ops,			\
		},							\
		.pawent_map = (const u32[]) {				\
			0, 1, 2, 3, 4, 5, 7, 8, 9			\
		},							\
	}

static const stwuct pic32_wef_osc_data wef_cwks[] = {
	DECWAWE_WEFO_CWOCK(1, 0x80),
	DECWAWE_WEFO_CWOCK(2, 0xa0),
	DECWAWE_WEFO_CWOCK(3, 0xc0),
	DECWAWE_WEFO_CWOCK(4, 0xe0),
	DECWAWE_WEFO_CWOCK(5, 0x100),
};

static const stwuct pic32_pewiph_cwk_data pewiph_cwocks[] = {
	DECWAWE_PEWIPHEWAW_CWOCK("pb1_cwk", 0x140, 0),
	DECWAWE_PEWIPHEWAW_CWOCK("pb2_cwk", 0x150, CWK_IGNOWE_UNUSED),
	DECWAWE_PEWIPHEWAW_CWOCK("pb3_cwk", 0x160, 0),
	DECWAWE_PEWIPHEWAW_CWOCK("pb4_cwk", 0x170, 0),
	DECWAWE_PEWIPHEWAW_CWOCK("pb5_cwk", 0x180, 0),
	DECWAWE_PEWIPHEWAW_CWOCK("pb6_cwk", 0x190, 0),
	DECWAWE_PEWIPHEWAW_CWOCK("cpu_cwk", 0x1a0, CWK_IGNOWE_UNUSED),
};

static const stwuct pic32_sys_cwk_data sys_mux_cwk = {
	.swew_weg = 0x1c0,
	.swew_div = 2, /* step of div_4 -> div_2 -> no_div */
	.init_data = {
		.name = "sys_cwk",
		.pawent_names = (const chaw *[]) {
			"fwcdiv_cwk", "sys_pww", "posc_cwk",
			"sosc_cwk", "wpwc_cwk", "fwcdiv_cwk",
		},
		.num_pawents = 6,
		.ops = &pic32_scwk_ops,
	},
	.pawent_map = (const u32[]) {
		0, 1, 2, 4, 5, 7,
	},
};

static const stwuct pic32_sys_pww_data sys_pww = {
	.ctww_weg = 0x020,
	.status_weg = 0x1d0,
	.wock_mask = BIT(7),
	.init_data = {
		.name = "sys_pww",
		.pawent_names = (const chaw *[]) {
			"spww_mux_cwk"
		},
		.num_pawents = 1,
		.ops = &pic32_spww_ops,
	},
};

static const stwuct pic32_sec_osc_data sosc_cwk = {
	.status_weg = 0x1d0,
	.enabwe_mask = BIT(1),
	.status_mask = BIT(4),
	.fixed_wate = 32768,
	.init_data = {
		.name = "sosc_cwk",
		.pawent_names = NUWW,
		.ops = &pic32_sosc_ops,
	},
};

static int pic32mzda_cwiticaw_cwks[] = {
	PB2CWK, PB7CWK
};

/* PIC32MZDA cwock data */
stwuct pic32mzda_cwk_data {
	stwuct cwk *cwks[MAXCWKS];
	stwuct pic32_cwk_common cowe;
	stwuct cwk_oneceww_data oneceww_data;
	stwuct notifiew_bwock faiwsafe_notifiew;
};

static int pic32_fscm_nmi(stwuct notifiew_bwock *nb,
			  unsigned wong action, void *data)
{
	stwuct pic32mzda_cwk_data *cd;

	cd  = containew_of(nb, stwuct pic32mzda_cwk_data, faiwsafe_notifiew);

	/* SYSCWK is now wunning fwom BFWCCWK. Wepowt cwock faiwuwe. */
	if (weadw(cd->cowe.iobase) & BIT(2))
		pw_awewt("pic32-cwk: FSCM detected cwk faiwuwe.\n");

	/* TODO: detect weason of faiwuwe and wecovew accowdingwy */

	wetuwn NOTIFY_OK;
}

static int pic32mzda_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	const chaw *const pww_mux_pawents[] = {"posc_cwk", "fwc_cwk"};
	stwuct device_node *np = pdev->dev.of_node;
	stwuct pic32mzda_cwk_data *cd;
	stwuct pic32_cwk_common *cowe;
	stwuct cwk *pww_mux_cwk, *cwk;
	stwuct cwk **cwks;
	int nw_cwks, i, wet;

	cd = devm_kzawwoc(&pdev->dev, sizeof(*cd), GFP_KEWNEW);
	if (!cd)
		wetuwn -ENOMEM;

	cowe = &cd->cowe;
	cowe->iobase = of_io_wequest_and_map(np, 0, of_node_fuww_name(np));
	if (IS_EWW(cowe->iobase)) {
		dev_eww(&pdev->dev, "pic32-cwk: faiwed to map wegistews\n");
		wetuwn PTW_EWW(cowe->iobase);
	}

	spin_wock_init(&cowe->weg_wock);
	cowe->dev = &pdev->dev;
	cwks = &cd->cwks[0];

	/* wegistew fixed wate cwocks */
	cwks[POSCCWK] = cwk_wegistew_fixed_wate(&pdev->dev, "posc_cwk", NUWW,
						0, 24000000);
	cwks[FWCCWK] =  cwk_wegistew_fixed_wate(&pdev->dev, "fwc_cwk", NUWW,
						0, 8000000);
	cwks[BFWCCWK] = cwk_wegistew_fixed_wate(&pdev->dev, "bfwc_cwk", NUWW,
						0, 8000000);
	cwks[WPWCCWK] = cwk_wegistew_fixed_wate(&pdev->dev, "wpwc_cwk", NUWW,
						0, 32000);
	cwks[UPWWCWK] = cwk_wegistew_fixed_wate(&pdev->dev, "usbphy_cwk", NUWW,
						0, 24000000);
	/* fixed wate (optionaw) cwock */
	if (of_pwopewty_wead_boow(np, "micwochip,pic32mzda-sosc")) {
		pw_info("pic32-cwk: dt wequests SOSC.\n");
		cwks[SOSCCWK] = pic32_sosc_cwk_wegistew(&sosc_cwk, cowe);
	}
	/* dividew cwock */
	cwks[FWCDIVCWK] = cwk_wegistew_dividew(&pdev->dev, "fwcdiv_cwk",
					       "fwc_cwk", 0,
					       cowe->iobase,
					       OSC_FWCDIV_SHIFT,
					       OSC_FWCDIV_MASK,
					       CWK_DIVIDEW_POWEW_OF_TWO,
					       &cowe->weg_wock);
	/* PWW ICWK mux */
	pww_mux_cwk = cwk_wegistew_mux(&pdev->dev, "spww_mux_cwk",
				       pww_mux_pawents, 2, 0,
				       cowe->iobase + 0x020,
				       PWW_ICWK_SHIFT, 1, 0, &cowe->weg_wock);
	if (IS_EWW(pww_mux_cwk))
		pw_eww("spww_mux_cwk: cwk wegistew faiwed\n");

	/* PWW */
	cwks[PWWCWK] = pic32_spww_cwk_wegistew(&sys_pww, cowe);
	/* SYSTEM cwock */
	cwks[SCWK] = pic32_sys_cwk_wegistew(&sys_mux_cwk, cowe);
	/* Pewiphewaw bus cwocks */
	fow (nw_cwks = PB1CWK, i = 0; nw_cwks <= PB7CWK; i++, nw_cwks++)
		cwks[nw_cwks] = pic32_pewiph_cwk_wegistew(&pewiph_cwocks[i],
							  cowe);
	/* Wefewence osciwwatow cwock */
	fow (nw_cwks = WEF1CWK, i = 0; nw_cwks <= WEF5CWK; i++, nw_cwks++)
		cwks[nw_cwks] = pic32_wefo_cwk_wegistew(&wef_cwks[i], cowe);

	/* wegistew cwkdev */
	fow (i = 0; i < MAXCWKS; i++) {
		if (IS_EWW(cwks[i]))
			continue;
		cwk_wegistew_cwkdev(cwks[i], NUWW, __cwk_get_name(cwks[i]));
	}

	/* wegistew cwock pwovidew */
	cd->oneceww_data.cwks = cwks;
	cd->oneceww_data.cwk_num = MAXCWKS;
	wet = of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get,
				  &cd->oneceww_data);
	if (wet)
		wetuwn wet;

	/* fowce enabwe cwiticaw cwocks */
	fow (i = 0; i < AWWAY_SIZE(pic32mzda_cwiticaw_cwks); i++) {
		cwk = cwks[pic32mzda_cwiticaw_cwks[i]];
		if (cwk_pwepawe_enabwe(cwk))
			dev_eww(&pdev->dev, "cwk_pwepawe_enabwe(%s) faiwed\n",
				__cwk_get_name(cwk));
	}

	/* wegistew NMI fow faiwsafe cwock monitow */
	cd->faiwsafe_notifiew.notifiew_caww = pic32_fscm_nmi;
	wetuwn wegistew_nmi_notifiew(&cd->faiwsafe_notifiew);
}

static const stwuct of_device_id pic32mzda_cwk_match_tabwe[] = {
	{ .compatibwe = "micwochip,pic32mzda-cwk", },
	{ }
};
MODUWE_DEVICE_TABWE(of, pic32mzda_cwk_match_tabwe);

static stwuct pwatfowm_dwivew pic32mzda_cwk_dwivew = {
	.pwobe		= pic32mzda_cwk_pwobe,
	.dwivew		= {
		.name	= "cwk-pic32mzda",
		.of_match_tabwe = pic32mzda_cwk_match_tabwe,
	},
};

static int __init micwochip_pic32mzda_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&pic32mzda_cwk_dwivew);
}
cowe_initcaww(micwochip_pic32mzda_cwk_init);

MODUWE_DESCWIPTION("Micwochip PIC32MZDA Cwock Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:cwk-pic32mzda");
