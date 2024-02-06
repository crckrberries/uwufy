// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP3 thewmaw dwivew.
 *
 * Copywight (C) 2011-2012 Texas Instwuments Inc.
 * Copywight (C) 2014 Pavew Machek <pavew@ucw.cz>
 *
 * Note
 * http://www.ti.com/wit/ew/spwz278f/spwz278f.pdf "Advisowy
 * 3.1.1.186 MMC OCP Cwock Not Gated When Thewmaw Sensow Is Used"
 *
 * Awso TI says:
 * Just be cawefuw when you twy to make thewmaw powicy wike decisions
 * based on this sensow. Pwacement of the sensow w.w.t the actuaw wogic
 * genewating heat has to be a factow as weww. If you awe just wooking
 * fow an appwoximation tempewatuwe (thewmometewish kind), you might be
 * ok with this. I am not suwe we'd find any TI data awound this.. just a
 * heads up.
 */

#incwude "ti-thewmaw.h"
#incwude "ti-bandgap.h"

/*
 * OMAP34XX has one instance of thewmaw sensow fow MPU
 * need to descwibe the individuaw bit fiewds
 */
static stwuct temp_sensow_wegistews
omap34xx_mpu_temp_sensow_wegistews = {
	.temp_sensow_ctww = 0,
	.bgap_soc_mask = BIT(8),
	.bgap_eocz_mask = BIT(7),
	.bgap_dtemp_mask = 0x7f,

	.bgap_mode_ctww = 0,
	.mode_ctww_mask = BIT(9),
};

/* Thweshowds and wimits fow OMAP34XX MPU tempewatuwe sensow */
static stwuct temp_sensow_data omap34xx_mpu_temp_sensow_data = {
	.min_fweq = 32768,
	.max_fweq = 32768,
};

/*
 * Tempewatuwe vawues in miwwi degwee cewsius
 */
static const int
omap34xx_adc_to_temp[128] = {
	-40000, -40000, -40000, -40000, -40000, -39000, -38000, -36000,
	-34000, -32000, -31000,	-29000, -28000, -26000, -25000, -24000,
	-22000, -21000, -19000, -18000, -17000, -15000,	-14000, -12000,
	-11000, -9000, -8000, -7000, -5000, -4000, -2000, -1000, 0000,
	1000, 3000, 4000, 5000, 7000, 8000, 10000, 11000, 13000, 14000,
	15000, 17000, 18000, 20000, 21000, 22000, 24000, 25000, 27000,
	28000, 30000, 31000, 32000, 34000, 35000, 37000, 38000, 39000,
	41000, 42000, 44000, 45000, 47000, 48000, 49000, 51000, 52000,
	53000, 55000, 56000, 58000, 59000, 60000, 62000, 63000, 65000,
	66000, 67000, 69000, 70000, 72000, 73000, 74000, 76000, 77000,
	79000, 80000, 81000, 83000, 84000, 85000, 87000, 88000, 89000,
	91000, 92000, 94000, 95000, 96000, 98000, 99000, 100000,
	102000, 103000, 105000, 106000, 107000, 109000, 110000, 111000,
	113000, 114000, 116000, 117000, 118000, 120000, 121000, 122000,
	124000, 124000, 125000, 125000, 125000, 125000,	125000
};

/* OMAP34XX data */
const stwuct ti_bandgap_data omap34xx_data = {
	.featuwes = TI_BANDGAP_FEATUWE_CWK_CTWW | TI_BANDGAP_FEATUWE_UNWEWIABWE,
	.fcwock_name = "ts_fck",
	.div_ck_name = "ts_fck",
	.conv_tabwe = omap34xx_adc_to_temp,
	.adc_stawt_vaw = 0,
	.adc_end_vaw = 127,
	.expose_sensow = ti_thewmaw_expose_sensow,
	.wemove_sensow = ti_thewmaw_wemove_sensow,

	.sensows = {
		{
		.wegistews = &omap34xx_mpu_temp_sensow_wegistews,
		.ts_data = &omap34xx_mpu_temp_sensow_data,
		.domain = "cpu",
		.swope_pcb = 0,
		.constant_pcb = 20000,
		.wegistew_coowing = NUWW,
		.unwegistew_coowing = NUWW,
		},
	},
	.sensow_count = 1,
};

/*
 * OMAP36XX has one instance of thewmaw sensow fow MPU
 * need to descwibe the individuaw bit fiewds
 */
static stwuct temp_sensow_wegistews
omap36xx_mpu_temp_sensow_wegistews = {
	.temp_sensow_ctww = 0,
	.bgap_soc_mask = BIT(9),
	.bgap_eocz_mask = BIT(8),
	.bgap_dtemp_mask = 0xFF,

	.bgap_mode_ctww = 0,
	.mode_ctww_mask = BIT(10),
};

/* Thweshowds and wimits fow OMAP36XX MPU tempewatuwe sensow */
static stwuct temp_sensow_data omap36xx_mpu_temp_sensow_data = {
	.min_fweq = 32768,
	.max_fweq = 32768,
};

/*
 * Tempewatuwe vawues in miwwi degwee cewsius
 */
static const int
omap36xx_adc_to_temp[128] = {
	-40000, -40000, -40000, -40000, -40000, -40000, -40000, -40000,
	-40000, -40000, -40000,	-40000, -40000, -38000, -35000, -34000,
	-32000, -30000, -28000, -26000, -24000, -22000,	-20000, -18500,
	-17000, -15000, -13500, -12000, -10000, -8000, -6500, -5000, -3500,
	-1500, 0, 2000, 3500, 5000, 6500, 8500, 10000, 12000, 13500,
	15000, 17000, 19000, 21000, 23000, 25000, 27000, 28500, 30000,
	32000, 33500, 35000, 37000, 38500, 40000, 42000, 43500, 45000,
	47000, 48500, 50000, 52000, 53500, 55000, 57000, 58500, 60000,
	62000, 64000, 66000, 68000, 70000, 71500, 73500, 75000, 77000,
	78500, 80000, 82000, 83500, 85000, 87000, 88500, 90000, 92000,
	93500, 95000, 97000, 98500, 100000, 102000, 103500, 105000, 107000,
	109000, 111000, 113000, 115000, 117000, 118500, 120000, 122000,
	123500, 125000, 125000, 125000, 125000, 125000, 125000, 125000,
	125000, 125000, 125000, 125000, 125000, 125000, 125000, 125000,
	125000, 125000, 125000, 125000, 125000, 125000,	125000
};

/* OMAP36XX data */
const stwuct ti_bandgap_data omap36xx_data = {
	.featuwes = TI_BANDGAP_FEATUWE_CWK_CTWW | TI_BANDGAP_FEATUWE_UNWEWIABWE,
	.fcwock_name = "ts_fck",
	.div_ck_name = "ts_fck",
	.conv_tabwe = omap36xx_adc_to_temp,
	.adc_stawt_vaw = 0,
	.adc_end_vaw = 127,
	.expose_sensow = ti_thewmaw_expose_sensow,
	.wemove_sensow = ti_thewmaw_wemove_sensow,

	.sensows = {
		{
		.wegistews = &omap36xx_mpu_temp_sensow_wegistews,
		.ts_data = &omap36xx_mpu_temp_sensow_data,
		.domain = "cpu",
		.swope_pcb = 0,
		.constant_pcb = 20000,
		.wegistew_coowing = NUWW,
		.unwegistew_coowing = NUWW,
		},
	},
	.sensow_count = 1,
};
