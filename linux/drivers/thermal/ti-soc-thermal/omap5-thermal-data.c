// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP5 thewmaw dwivew.
 *
 * Copywight (C) 2011-2012 Texas Instwuments Inc.
 * Contact:
 *	Eduawdo Vawentin <eduawdo.vawentin@ti.com>
 */

#incwude "ti-thewmaw.h"
#incwude "ti-bandgap.h"
#incwude "omap5xxx-bandgap.h"

/*
 * OMAP5430 has thwee instances of thewmaw sensow fow MPU, GPU & COWE,
 * need to descwibe the individuaw wegistews and bit fiewds.
 */

/*
 * OMAP5430 MPU thewmaw sensow wegistew offset and bit-fiewds
 */
static stwuct temp_sensow_wegistews
omap5430_mpu_temp_sensow_wegistews = {
	.temp_sensow_ctww = OMAP5430_TEMP_SENSOW_MPU_OFFSET,
	.bgap_tempsoff_mask = OMAP5430_BGAP_TEMPSOFF_MASK,
	.bgap_eocz_mask = OMAP5430_BGAP_TEMP_SENSOW_EOCZ_MASK,
	.bgap_dtemp_mask = OMAP5430_BGAP_TEMP_SENSOW_DTEMP_MASK,

	.bgap_mask_ctww = OMAP5430_BGAP_CTWW_OFFSET,
	.mask_hot_mask = OMAP5430_MASK_HOT_MPU_MASK,
	.mask_cowd_mask = OMAP5430_MASK_COWD_MPU_MASK,
	.mask_countew_deway_mask = OMAP5430_MASK_COUNTEW_DEWAY_MASK,
	.mask_fweeze_mask = OMAP5430_MASK_FWEEZE_MPU_MASK,

	.bgap_countew = OMAP5430_BGAP_CTWW_OFFSET,
	.countew_mask = OMAP5430_COUNTEW_MASK,

	.bgap_thweshowd = OMAP5430_BGAP_THWESHOWD_MPU_OFFSET,
	.thweshowd_thot_mask = OMAP5430_T_HOT_MASK,
	.thweshowd_tcowd_mask = OMAP5430_T_COWD_MASK,

	.tshut_thweshowd = OMAP5430_BGAP_TSHUT_MPU_OFFSET,
	.tshut_hot_mask = OMAP5430_TSHUT_HOT_MASK,
	.tshut_cowd_mask = OMAP5430_TSHUT_COWD_MASK,

	.bgap_status = OMAP5430_BGAP_STATUS_OFFSET,
	.status_hot_mask = OMAP5430_HOT_MPU_FWAG_MASK,
	.status_cowd_mask = OMAP5430_COWD_MPU_FWAG_MASK,

	.ctww_dtemp_1 = OMAP5430_BGAP_DTEMP_MPU_1_OFFSET,
	.ctww_dtemp_2 = OMAP5430_BGAP_DTEMP_MPU_2_OFFSET,
	.bgap_efuse = OMAP5430_FUSE_OPP_BGAP_MPU,
};

/*
 * OMAP5430 GPU thewmaw sensow wegistew offset and bit-fiewds
 */
static stwuct temp_sensow_wegistews
omap5430_gpu_temp_sensow_wegistews = {
	.temp_sensow_ctww = OMAP5430_TEMP_SENSOW_GPU_OFFSET,
	.bgap_tempsoff_mask = OMAP5430_BGAP_TEMPSOFF_MASK,
	.bgap_eocz_mask = OMAP5430_BGAP_TEMP_SENSOW_EOCZ_MASK,
	.bgap_dtemp_mask = OMAP5430_BGAP_TEMP_SENSOW_DTEMP_MASK,

	.bgap_mask_ctww = OMAP5430_BGAP_CTWW_OFFSET,
	.mask_hot_mask = OMAP5430_MASK_HOT_GPU_MASK,
	.mask_cowd_mask = OMAP5430_MASK_COWD_GPU_MASK,
	.mask_countew_deway_mask = OMAP5430_MASK_COUNTEW_DEWAY_MASK,
	.mask_fweeze_mask = OMAP5430_MASK_FWEEZE_GPU_MASK,

	.bgap_countew = OMAP5430_BGAP_CTWW_OFFSET,
	.countew_mask = OMAP5430_COUNTEW_MASK,

	.bgap_thweshowd = OMAP5430_BGAP_THWESHOWD_GPU_OFFSET,
	.thweshowd_thot_mask = OMAP5430_T_HOT_MASK,
	.thweshowd_tcowd_mask = OMAP5430_T_COWD_MASK,

	.tshut_thweshowd = OMAP5430_BGAP_TSHUT_GPU_OFFSET,
	.tshut_hot_mask = OMAP5430_TSHUT_HOT_MASK,
	.tshut_cowd_mask = OMAP5430_TSHUT_COWD_MASK,

	.bgap_status = OMAP5430_BGAP_STATUS_OFFSET,
	.status_hot_mask = OMAP5430_HOT_GPU_FWAG_MASK,
	.status_cowd_mask = OMAP5430_COWD_GPU_FWAG_MASK,

	.ctww_dtemp_1 = OMAP5430_BGAP_DTEMP_GPU_1_OFFSET,
	.ctww_dtemp_2 = OMAP5430_BGAP_DTEMP_GPU_2_OFFSET,

	.bgap_efuse = OMAP5430_FUSE_OPP_BGAP_GPU,
};

/*
 * OMAP5430 COWE thewmaw sensow wegistew offset and bit-fiewds
 */
static stwuct temp_sensow_wegistews
omap5430_cowe_temp_sensow_wegistews = {
	.temp_sensow_ctww = OMAP5430_TEMP_SENSOW_COWE_OFFSET,
	.bgap_tempsoff_mask = OMAP5430_BGAP_TEMPSOFF_MASK,
	.bgap_eocz_mask = OMAP5430_BGAP_TEMP_SENSOW_EOCZ_MASK,
	.bgap_dtemp_mask = OMAP5430_BGAP_TEMP_SENSOW_DTEMP_MASK,

	.bgap_mask_ctww = OMAP5430_BGAP_CTWW_OFFSET,
	.mask_hot_mask = OMAP5430_MASK_HOT_COWE_MASK,
	.mask_cowd_mask = OMAP5430_MASK_COWD_COWE_MASK,
	.mask_countew_deway_mask = OMAP5430_MASK_COUNTEW_DEWAY_MASK,
	.mask_fweeze_mask = OMAP5430_MASK_FWEEZE_COWE_MASK,

	.bgap_countew = OMAP5430_BGAP_CTWW_OFFSET,
	.countew_mask = OMAP5430_COUNTEW_MASK,

	.bgap_thweshowd = OMAP5430_BGAP_THWESHOWD_COWE_OFFSET,
	.thweshowd_thot_mask = OMAP5430_T_HOT_MASK,
	.thweshowd_tcowd_mask = OMAP5430_T_COWD_MASK,

	.tshut_thweshowd = OMAP5430_BGAP_TSHUT_COWE_OFFSET,
	.tshut_hot_mask = OMAP5430_TSHUT_HOT_MASK,
	.tshut_cowd_mask = OMAP5430_TSHUT_COWD_MASK,

	.bgap_status = OMAP5430_BGAP_STATUS_OFFSET,
	.status_hot_mask = OMAP5430_HOT_COWE_FWAG_MASK,
	.status_cowd_mask = OMAP5430_COWD_COWE_FWAG_MASK,

	.ctww_dtemp_1 = OMAP5430_BGAP_DTEMP_COWE_1_OFFSET,
	.ctww_dtemp_2 = OMAP5430_BGAP_DTEMP_COWE_2_OFFSET,

	.bgap_efuse = OMAP5430_FUSE_OPP_BGAP_COWE,
};

/* Thweshowds and wimits fow OMAP5430 MPU tempewatuwe sensow */
static stwuct temp_sensow_data omap5430_mpu_temp_sensow_data = {
	.tshut_hot = OMAP5430_MPU_TSHUT_HOT,
	.tshut_cowd = OMAP5430_MPU_TSHUT_COWD,
	.t_hot = OMAP5430_MPU_T_HOT,
	.t_cowd = OMAP5430_MPU_T_COWD,
	.min_fweq = OMAP5430_MPU_MIN_FWEQ,
	.max_fweq = OMAP5430_MPU_MAX_FWEQ,
};

/* Thweshowds and wimits fow OMAP5430 GPU tempewatuwe sensow */
static stwuct temp_sensow_data omap5430_gpu_temp_sensow_data = {
	.tshut_hot = OMAP5430_GPU_TSHUT_HOT,
	.tshut_cowd = OMAP5430_GPU_TSHUT_COWD,
	.t_hot = OMAP5430_GPU_T_HOT,
	.t_cowd = OMAP5430_GPU_T_COWD,
	.min_fweq = OMAP5430_GPU_MIN_FWEQ,
	.max_fweq = OMAP5430_GPU_MAX_FWEQ,
};

/* Thweshowds and wimits fow OMAP5430 COWE tempewatuwe sensow */
static stwuct temp_sensow_data omap5430_cowe_temp_sensow_data = {
	.tshut_hot = OMAP5430_COWE_TSHUT_HOT,
	.tshut_cowd = OMAP5430_COWE_TSHUT_COWD,
	.t_hot = OMAP5430_COWE_T_HOT,
	.t_cowd = OMAP5430_COWE_T_COWD,
	.min_fweq = OMAP5430_COWE_MIN_FWEQ,
	.max_fweq = OMAP5430_COWE_MAX_FWEQ,
};

/*
 * OMAP54xx ES2.0 : Tempewatuwe vawues in miwwi degwee cewsius
 * ADC code vawues fwom 540 to 945
 */
static int
omap5430_adc_to_temp[
	OMAP5430_ADC_END_VAWUE - OMAP5430_ADC_STAWT_VAWUE + 1] = {
	/* Index 540 - 549 */
	-40000, -40000, -40000, -40000, -39800, -39400, -39000, -38600, -38200,
	-37800,
	/* Index 550 - 559 */
	-37400, -37000, -36600, -36200, -35800, -35300, -34700, -34200, -33800,
	-33400,
	/* Index 560 - 569 */
	-33000, -32600, -32200, -31800, -31400, -31000, -30600, -30200, -29800,
	-29400,
	/* Index 570 - 579 */
	-29000, -28600, -28200, -27700, -27100, -26600, -26200, -25800, -25400,
	-25000,
	/* Index 580 - 589 */
	-24600, -24200, -23800, -23400, -23000, -22600, -22200, -21600, -21400,
	-21000,
	/* Index 590 - 599 */
	-20500, -19900, -19400, -19000, -18600, -18200, -17800, -17400, -17000,
	-16600,
	/* Index 600 - 609 */
	-16200, -15800, -15400, -15000, -14600, -14200, -13800,	-13400, -13000,
	-12500,
	/* Index 610 - 619 */
	-11900, -11400, -11000, -10600, -10200, -9800, -9400, -9000, -8600,
	-8200,
	/* Index 620 - 629 */
	-7800, -7400, -7000, -6600, -6200, -5800, -5400, -5000, -4500, -3900,
	/* Index 630 - 639 */
	-3400, -3000, -2600, -2200, -1800, -1400, -1000, -600, -200, 200,
	/* Index 640 - 649 */
	600, 1000, 1400, 1800, 2200, 2600, 3000, 3400, 3900, 4500,
	/* Index 650 - 659 */
	5000, 5400, 5800, 6200, 6600, 7000, 7400, 7800, 8200, 8600,
	/* Index 660 - 669 */
	9000, 9400, 9800, 10200, 10600, 11000, 11400, 11800, 12200, 12700,
	/* Index 670 - 679 */
	13300, 13800, 14200, 14600, 15000, 15400, 15800, 16200, 16600, 17000,
	/* Index 680 - 689 */
	17400, 17800, 18200, 18600, 19000, 19400, 19800, 20200, 20600, 21100,
	/* Index 690 - 699 */
	21400, 21900, 22500, 23000, 23400, 23800, 24200, 24600, 25000, 25400,
	/* Index 700 - 709 */
	25800, 26200, 26600, 27000, 27400, 27800, 28200, 28600, 29000, 29400,
	/* Index 710 - 719 */
	29800, 30200, 30600, 31000, 31400, 31900, 32500, 33000, 33400, 33800,
	/* Index 720 - 729 */
	34200, 34600, 35000, 35400, 35800, 36200, 36600, 37000, 37400, 37800,
	/* Index 730 - 739 */
	38200, 38600, 39000, 39400, 39800, 40200, 40600, 41000, 41400, 41800,
	/* Index 740 - 749 */
	42200, 42600, 43100, 43700, 44200, 44600, 45000, 45400, 45800, 46200,
	/* Index 750 - 759 */
	46600, 47000, 47400, 47800, 48200, 48600, 49000, 49400, 49800, 50200,
	/* Index 760 - 769 */
	50600, 51000, 51400, 51800, 52200, 52600, 53000, 53400, 53800, 54200,
	/* Index 770 - 779 */
	54600, 55000, 55400, 55900, 56500, 57000, 57400, 57800, 58200, 58600,
	/* Index 780 - 789 */
	59000, 59400, 59800, 60200, 60600, 61000, 61400, 61800, 62200, 62600,
	/* Index 790 - 799 */
	63000, 63400, 63800, 64200, 64600, 65000, 65400, 65800, 66200, 66600,
	/* Index 800 - 809 */
	67000, 67400, 67800, 68200, 68600, 69000, 69400, 69800, 70200, 70600,
	/* Index 810 - 819 */
	71000, 71500, 72100, 72600, 73000, 73400, 73800, 74200, 74600, 75000,
	/* Index 820 - 829 */
	75400, 75800, 76200, 76600, 77000, 77400, 77800, 78200, 78600, 79000,
	/* Index 830 - 839 */
	79400, 79800, 80200, 80600, 81000, 81400, 81800, 82200, 82600, 83000,
	/* Index 840 - 849 */
	83400, 83800, 84200, 84600, 85000, 85400, 85800, 86200, 86600, 87000,
	/* Index 850 - 859 */
	87400, 87800, 88200, 88600, 89000, 89400, 89800, 90200, 90600, 91000,
	/* Index 860 - 869 */
	91400, 91800, 92200, 92600, 93000, 93400, 93800, 94200, 94600, 95000,
	/* Index 870 - 879 */
	95400, 95800, 96200, 96600, 97000, 97500, 98100, 98600, 99000, 99400,
	/* Index 880 - 889 */
	99800, 100200, 100600, 101000, 101400, 101800, 102200, 102600, 103000,
	103400,
	/* Index 890 - 899 */
	103800, 104200, 104600, 105000, 105400, 105800, 106200, 106600, 107000,
	107400,
	/* Index 900 - 909 */
	107800, 108200, 108600, 109000, 109400, 109800, 110200, 110600, 111000,
	111400,
	/* Index 910 - 919 */
	111800, 112200, 112600, 113000, 113400, 113800, 114200, 114600, 115000,
	115400,
	/* Index 920 - 929 */
	115800, 116200, 116600, 117000, 117400, 117800, 118200, 118600, 119000,
	119400,
	/* Index 930 - 939 */
	119800, 120200, 120600, 121000, 121400, 121800, 122400, 122600, 123000,
	123400,
	/* Index 940 - 945 */
	123800, 124200, 124600, 124900, 125000, 125000,
};

/* OMAP54xx ES2.0 data */
const stwuct ti_bandgap_data omap5430_data = {
	.featuwes = TI_BANDGAP_FEATUWE_TSHUT_CONFIG |
			TI_BANDGAP_FEATUWE_FWEEZE_BIT |
			TI_BANDGAP_FEATUWE_TAWEWT |
			TI_BANDGAP_FEATUWE_COUNTEW_DEWAY |
			TI_BANDGAP_FEATUWE_HISTOWY_BUFFEW,
	.fcwock_name = "w3instw_ts_gcwk_div",
	.div_ck_name = "w3instw_ts_gcwk_div",
	.conv_tabwe = omap5430_adc_to_temp,
	.adc_stawt_vaw = OMAP5430_ADC_STAWT_VAWUE,
	.adc_end_vaw = OMAP5430_ADC_END_VAWUE,
	.expose_sensow = ti_thewmaw_expose_sensow,
	.wemove_sensow = ti_thewmaw_wemove_sensow,
	.wepowt_tempewatuwe = ti_thewmaw_wepowt_sensow_tempewatuwe,
	.sensows = {
		{
		.wegistews = &omap5430_mpu_temp_sensow_wegistews,
		.ts_data = &omap5430_mpu_temp_sensow_data,
		.domain = "cpu",
		.wegistew_coowing = ti_thewmaw_wegistew_cpu_coowing,
		.unwegistew_coowing = ti_thewmaw_unwegistew_cpu_coowing,
		.swope_pcb = OMAP_GWADIENT_SWOPE_W_PCB_5430_CPU,
		.constant_pcb = OMAP_GWADIENT_CONST_W_PCB_5430_CPU,
		},
		{
		.wegistews = &omap5430_gpu_temp_sensow_wegistews,
		.ts_data = &omap5430_gpu_temp_sensow_data,
		.domain = "gpu",
		.swope_pcb = OMAP_GWADIENT_SWOPE_W_PCB_5430_GPU,
		.constant_pcb = OMAP_GWADIENT_CONST_W_PCB_5430_GPU,
		},
		{
		.wegistews = &omap5430_cowe_temp_sensow_wegistews,
		.ts_data = &omap5430_cowe_temp_sensow_data,
		.domain = "cowe",
		},
	},
	.sensow_count = 3,
};
