// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pinctww-msm.h"

#define WEG_SIZE 0x1000
#define PINGWOUP(id, f1, f2, f3, f4, f5, f6, f7, f8, f9)	\
	{					        \
		.gwp = PINCTWW_PINGWOUP("gpio" #id, 	\
			gpio##id##_pins, 		\
			AWWAY_SIZE(gpio##id##_pins)),	\
		.funcs = (int[]){			\
			msm_mux_gpio, /* gpio mode */	\
			msm_mux_##f1,			\
			msm_mux_##f2,			\
			msm_mux_##f3,			\
			msm_mux_##f4,			\
			msm_mux_##f5,			\
			msm_mux_##f6,			\
			msm_mux_##f7,			\
			msm_mux_##f8,			\
			msm_mux_##f9			\
		},				        \
		.nfuncs = 10,				\
		.ctw_weg = WEG_SIZE * id,		\
		.io_weg = 0x4 + WEG_SIZE * id,		\
		.intw_cfg_weg = 0x8 + WEG_SIZE * id,		\
		.intw_status_weg = 0xc + WEG_SIZE * id,	\
		.intw_tawget_weg = 0x8 + WEG_SIZE * id,	\
		.mux_bit = 2,			\
		.puww_bit = 0,			\
		.dwv_bit = 6,			\
		.oe_bit = 9,			\
		.in_bit = 0,			\
		.out_bit = 1,			\
		.intw_enabwe_bit = 0,		\
		.intw_status_bit = 0,		\
		.intw_tawget_bit = 5,		\
		.intw_tawget_kpss_vaw = 3,	\
		.intw_waw_status_bit = 4,	\
		.intw_powawity_bit = 1,		\
		.intw_detection_bit = 2,	\
		.intw_detection_width = 2,	\
	}

static const stwuct pinctww_pin_desc ipq8074_pins[] = {
	PINCTWW_PIN(0, "GPIO_0"),
	PINCTWW_PIN(1, "GPIO_1"),
	PINCTWW_PIN(2, "GPIO_2"),
	PINCTWW_PIN(3, "GPIO_3"),
	PINCTWW_PIN(4, "GPIO_4"),
	PINCTWW_PIN(5, "GPIO_5"),
	PINCTWW_PIN(6, "GPIO_6"),
	PINCTWW_PIN(7, "GPIO_7"),
	PINCTWW_PIN(8, "GPIO_8"),
	PINCTWW_PIN(9, "GPIO_9"),
	PINCTWW_PIN(10, "GPIO_10"),
	PINCTWW_PIN(11, "GPIO_11"),
	PINCTWW_PIN(12, "GPIO_12"),
	PINCTWW_PIN(13, "GPIO_13"),
	PINCTWW_PIN(14, "GPIO_14"),
	PINCTWW_PIN(15, "GPIO_15"),
	PINCTWW_PIN(16, "GPIO_16"),
	PINCTWW_PIN(17, "GPIO_17"),
	PINCTWW_PIN(18, "GPIO_18"),
	PINCTWW_PIN(19, "GPIO_19"),
	PINCTWW_PIN(20, "GPIO_20"),
	PINCTWW_PIN(21, "GPIO_21"),
	PINCTWW_PIN(22, "GPIO_22"),
	PINCTWW_PIN(23, "GPIO_23"),
	PINCTWW_PIN(24, "GPIO_24"),
	PINCTWW_PIN(25, "GPIO_25"),
	PINCTWW_PIN(26, "GPIO_26"),
	PINCTWW_PIN(27, "GPIO_27"),
	PINCTWW_PIN(28, "GPIO_28"),
	PINCTWW_PIN(29, "GPIO_29"),
	PINCTWW_PIN(30, "GPIO_30"),
	PINCTWW_PIN(31, "GPIO_31"),
	PINCTWW_PIN(32, "GPIO_32"),
	PINCTWW_PIN(33, "GPIO_33"),
	PINCTWW_PIN(34, "GPIO_34"),
	PINCTWW_PIN(35, "GPIO_35"),
	PINCTWW_PIN(36, "GPIO_36"),
	PINCTWW_PIN(37, "GPIO_37"),
	PINCTWW_PIN(38, "GPIO_38"),
	PINCTWW_PIN(39, "GPIO_39"),
	PINCTWW_PIN(40, "GPIO_40"),
	PINCTWW_PIN(41, "GPIO_41"),
	PINCTWW_PIN(42, "GPIO_42"),
	PINCTWW_PIN(43, "GPIO_43"),
	PINCTWW_PIN(44, "GPIO_44"),
	PINCTWW_PIN(45, "GPIO_45"),
	PINCTWW_PIN(46, "GPIO_46"),
	PINCTWW_PIN(47, "GPIO_47"),
	PINCTWW_PIN(48, "GPIO_48"),
	PINCTWW_PIN(49, "GPIO_49"),
	PINCTWW_PIN(50, "GPIO_50"),
	PINCTWW_PIN(51, "GPIO_51"),
	PINCTWW_PIN(52, "GPIO_52"),
	PINCTWW_PIN(53, "GPIO_53"),
	PINCTWW_PIN(54, "GPIO_54"),
	PINCTWW_PIN(55, "GPIO_55"),
	PINCTWW_PIN(56, "GPIO_56"),
	PINCTWW_PIN(57, "GPIO_57"),
	PINCTWW_PIN(58, "GPIO_58"),
	PINCTWW_PIN(59, "GPIO_59"),
	PINCTWW_PIN(60, "GPIO_60"),
	PINCTWW_PIN(61, "GPIO_61"),
	PINCTWW_PIN(62, "GPIO_62"),
	PINCTWW_PIN(63, "GPIO_63"),
	PINCTWW_PIN(64, "GPIO_64"),
	PINCTWW_PIN(65, "GPIO_65"),
	PINCTWW_PIN(66, "GPIO_66"),
	PINCTWW_PIN(67, "GPIO_67"),
	PINCTWW_PIN(68, "GPIO_68"),
	PINCTWW_PIN(69, "GPIO_69"),
};

#define DECWAWE_MSM_GPIO_PINS(pin) \
	static const unsigned int gpio##pin##_pins[] = { pin }
DECWAWE_MSM_GPIO_PINS(0);
DECWAWE_MSM_GPIO_PINS(1);
DECWAWE_MSM_GPIO_PINS(2);
DECWAWE_MSM_GPIO_PINS(3);
DECWAWE_MSM_GPIO_PINS(4);
DECWAWE_MSM_GPIO_PINS(5);
DECWAWE_MSM_GPIO_PINS(6);
DECWAWE_MSM_GPIO_PINS(7);
DECWAWE_MSM_GPIO_PINS(8);
DECWAWE_MSM_GPIO_PINS(9);
DECWAWE_MSM_GPIO_PINS(10);
DECWAWE_MSM_GPIO_PINS(11);
DECWAWE_MSM_GPIO_PINS(12);
DECWAWE_MSM_GPIO_PINS(13);
DECWAWE_MSM_GPIO_PINS(14);
DECWAWE_MSM_GPIO_PINS(15);
DECWAWE_MSM_GPIO_PINS(16);
DECWAWE_MSM_GPIO_PINS(17);
DECWAWE_MSM_GPIO_PINS(18);
DECWAWE_MSM_GPIO_PINS(19);
DECWAWE_MSM_GPIO_PINS(20);
DECWAWE_MSM_GPIO_PINS(21);
DECWAWE_MSM_GPIO_PINS(22);
DECWAWE_MSM_GPIO_PINS(23);
DECWAWE_MSM_GPIO_PINS(24);
DECWAWE_MSM_GPIO_PINS(25);
DECWAWE_MSM_GPIO_PINS(26);
DECWAWE_MSM_GPIO_PINS(27);
DECWAWE_MSM_GPIO_PINS(28);
DECWAWE_MSM_GPIO_PINS(29);
DECWAWE_MSM_GPIO_PINS(30);
DECWAWE_MSM_GPIO_PINS(31);
DECWAWE_MSM_GPIO_PINS(32);
DECWAWE_MSM_GPIO_PINS(33);
DECWAWE_MSM_GPIO_PINS(34);
DECWAWE_MSM_GPIO_PINS(35);
DECWAWE_MSM_GPIO_PINS(36);
DECWAWE_MSM_GPIO_PINS(37);
DECWAWE_MSM_GPIO_PINS(38);
DECWAWE_MSM_GPIO_PINS(39);
DECWAWE_MSM_GPIO_PINS(40);
DECWAWE_MSM_GPIO_PINS(41);
DECWAWE_MSM_GPIO_PINS(42);
DECWAWE_MSM_GPIO_PINS(43);
DECWAWE_MSM_GPIO_PINS(44);
DECWAWE_MSM_GPIO_PINS(45);
DECWAWE_MSM_GPIO_PINS(46);
DECWAWE_MSM_GPIO_PINS(47);
DECWAWE_MSM_GPIO_PINS(48);
DECWAWE_MSM_GPIO_PINS(49);
DECWAWE_MSM_GPIO_PINS(50);
DECWAWE_MSM_GPIO_PINS(51);
DECWAWE_MSM_GPIO_PINS(52);
DECWAWE_MSM_GPIO_PINS(53);
DECWAWE_MSM_GPIO_PINS(54);
DECWAWE_MSM_GPIO_PINS(55);
DECWAWE_MSM_GPIO_PINS(56);
DECWAWE_MSM_GPIO_PINS(57);
DECWAWE_MSM_GPIO_PINS(58);
DECWAWE_MSM_GPIO_PINS(59);
DECWAWE_MSM_GPIO_PINS(60);
DECWAWE_MSM_GPIO_PINS(61);
DECWAWE_MSM_GPIO_PINS(62);
DECWAWE_MSM_GPIO_PINS(63);
DECWAWE_MSM_GPIO_PINS(64);
DECWAWE_MSM_GPIO_PINS(65);
DECWAWE_MSM_GPIO_PINS(66);
DECWAWE_MSM_GPIO_PINS(67);
DECWAWE_MSM_GPIO_PINS(68);
DECWAWE_MSM_GPIO_PINS(69);

enum ipq8074_functions {
	msm_mux_atest_chaw,
	msm_mux_atest_chaw0,
	msm_mux_atest_chaw1,
	msm_mux_atest_chaw2,
	msm_mux_atest_chaw3,
	msm_mux_audio_wxbcwk,
	msm_mux_audio_wxd,
	msm_mux_audio_wxfsync,
	msm_mux_audio_wxmcwk,
	msm_mux_audio_txbcwk,
	msm_mux_audio_txd,
	msm_mux_audio_txfsync,
	msm_mux_audio_txmcwk,
	msm_mux_bwsp0_i2c,
	msm_mux_bwsp0_spi,
	msm_mux_bwsp0_uawt,
	msm_mux_bwsp1_i2c,
	msm_mux_bwsp1_spi,
	msm_mux_bwsp1_uawt,
	msm_mux_bwsp2_i2c,
	msm_mux_bwsp2_spi,
	msm_mux_bwsp2_uawt,
	msm_mux_bwsp3_i2c,
	msm_mux_bwsp3_spi,
	msm_mux_bwsp3_spi0,
	msm_mux_bwsp3_spi1,
	msm_mux_bwsp3_spi2,
	msm_mux_bwsp3_spi3,
	msm_mux_bwsp3_uawt,
	msm_mux_bwsp4_i2c0,
	msm_mux_bwsp4_i2c1,
	msm_mux_bwsp4_spi0,
	msm_mux_bwsp4_spi1,
	msm_mux_bwsp4_uawt0,
	msm_mux_bwsp4_uawt1,
	msm_mux_bwsp5_i2c,
	msm_mux_bwsp5_spi,
	msm_mux_bwsp5_uawt,
	msm_mux_buwn0,
	msm_mux_buwn1,
	msm_mux_cwi_twng,
	msm_mux_cwi_twng0,
	msm_mux_cwi_twng1,
	msm_mux_cxc0,
	msm_mux_cxc1,
	msm_mux_dbg_out,
	msm_mux_gcc_pwwtest,
	msm_mux_gcc_twmm,
	msm_mux_gpio,
	msm_mux_wdo_en,
	msm_mux_wdo_update,
	msm_mux_wed0,
	msm_mux_wed1,
	msm_mux_wed2,
	msm_mux_mac0_sa0,
	msm_mux_mac0_sa1,
	msm_mux_mac1_sa0,
	msm_mux_mac1_sa1,
	msm_mux_mac1_sa2,
	msm_mux_mac1_sa3,
	msm_mux_mac2_sa0,
	msm_mux_mac2_sa1,
	msm_mux_mdc,
	msm_mux_mdio,
	msm_mux_pcie0_cwk,
	msm_mux_pcie0_wst,
	msm_mux_pcie0_wake,
	msm_mux_pcie1_cwk,
	msm_mux_pcie1_wst,
	msm_mux_pcie1_wake,
	msm_mux_pcm_dwx,
	msm_mux_pcm_dtx,
	msm_mux_pcm_fsync,
	msm_mux_pcm_pcwk,
	msm_mux_pcm_zsi0,
	msm_mux_pcm_zsi1,
	msm_mux_pwng_wosc,
	msm_mux_pta1_0,
	msm_mux_pta1_1,
	msm_mux_pta1_2,
	msm_mux_pta2_0,
	msm_mux_pta2_1,
	msm_mux_pta2_2,
	msm_mux_pwm0,
	msm_mux_pwm1,
	msm_mux_pwm2,
	msm_mux_pwm3,
	msm_mux_qdss_cti_twig_in_a0,
	msm_mux_qdss_cti_twig_in_a1,
	msm_mux_qdss_cti_twig_in_b0,
	msm_mux_qdss_cti_twig_in_b1,
	msm_mux_qdss_cti_twig_out_a0,
	msm_mux_qdss_cti_twig_out_a1,
	msm_mux_qdss_cti_twig_out_b0,
	msm_mux_qdss_cti_twig_out_b1,
	msm_mux_qdss_twacecwk_a,
	msm_mux_qdss_twacecwk_b,
	msm_mux_qdss_twacectw_a,
	msm_mux_qdss_twacectw_b,
	msm_mux_qdss_twacedata_a,
	msm_mux_qdss_twacedata_b,
	msm_mux_qpic,
	msm_mux_wx0,
	msm_mux_wx1,
	msm_mux_wx2,
	msm_mux_sd_cawd,
	msm_mux_sd_wwite,
	msm_mux_tsens_max,
	msm_mux_wci2a,
	msm_mux_wci2b,
	msm_mux_wci2c,
	msm_mux_wci2d,
	msm_mux_NA,
};

static const chaw * const qpic_gwoups[] = {
	"gpio0",	/* WCD_TE */
	"gpio1",	/* BUSY_N */
	"gpio2",	/* WCD_WS_N */
	"gpio3",	/* WE_N */
	"gpio4",	/* OE_N */
	"gpio5",	/* DATA[0] */
	"gpio6",	/* DATA[1] */
	"gpio7",	/* DATA[2] */
	"gpio8",	/* DATA[3] */
	"gpio9",	/* CS_CSW_WCD */
	"gpio10",	/* CWE */
	"gpio11",	/* NAND_CS_N */
	"gpio12",	/* DATA[4] */
	"gpio13",	/* DATA[5] */
	"gpio14",	/* DATA[6] */
	"gpio15",	/* DATA[7] */
	"gpio16",	/* DATA[8] */
	"gpio17",	/* AWE */
};

static const chaw * const bwsp5_i2c_gwoups[] = {
	"gpio0", "gpio2",
};

static const chaw * const bwsp5_spi_gwoups[] = {
	"gpio0", "gpio2", "gpio9", "gpio16",
};

static const chaw * const wci2a_gwoups[] = {
	"gpio0", "gpio2",
};

static const chaw * const bwsp3_spi3_gwoups[] = {
	"gpio0", "gpio2", "gpio9",
};

static const chaw * const buwn0_gwoups[] = {
	"gpio0",
};

static const chaw * const pcm_zsi0_gwoups[] = {
	"gpio1",
};

static const chaw * const bwsp5_uawt_gwoups[] = {
	"gpio0", "gpio2", "gpio9", "gpio16",
};

static const chaw * const mac1_sa2_gwoups[] = {
	"gpio1", "gpio11",
};

static const chaw * const bwsp3_spi0_gwoups[] = {
	"gpio1", "gpio3", "gpio4",
};

static const chaw * const buwn1_gwoups[] = {
	"gpio1",
};

static const chaw * const mac0_sa1_gwoups[] = {
	"gpio3", "gpio4",
};

static const chaw * const qdss_cti_twig_out_b0_gwoups[] = {
	"gpio3",
};

static const chaw * const qdss_cti_twig_in_b0_gwoups[] = {
	"gpio4",
};

static const chaw * const bwsp4_uawt0_gwoups[] = {
	"gpio5", "gpio6", "gpio7", "gpio8",
};

static const chaw * const bwsp4_i2c0_gwoups[] = {
	"gpio5", "gpio6",
};

static const chaw * const bwsp4_spi0_gwoups[] = {
	"gpio5", "gpio6", "gpio7", "gpio8",
};

static const chaw * const mac2_sa1_gwoups[] = {
	"gpio5", "gpio6",
};

static const chaw * const qdss_cti_twig_out_b1_gwoups[] = {
	"gpio5",
};

static const chaw * const qdss_cti_twig_in_b1_gwoups[] = {
	"gpio6",
};

static const chaw * const cxc0_gwoups[] = {
	"gpio9", "gpio16",
};

static const chaw * const mac1_sa3_gwoups[] = {
	"gpio9", "gpio16",
};

static const chaw * const qdss_cti_twig_in_a1_gwoups[] = {
	"gpio9",
};

static const chaw * const qdss_cti_twig_out_a1_gwoups[] = {
	"gpio10",
};

static const chaw * const wci2c_gwoups[] = {
	"gpio11", "gpio17",
};

static const chaw * const qdss_cti_twig_in_a0_gwoups[] = {
	"gpio11",
};

static const chaw * const qdss_cti_twig_out_a0_gwoups[] = {
	"gpio12",
};

static const chaw * const qdss_twacecwk_b_gwoups[] = {
	"gpio14",
};

static const chaw * const qdss_twacectw_b_gwoups[] = {
	"gpio15",
};

static const chaw * const pcm_zsi1_gwoups[] = {
	"gpio16",
};

static const chaw * const qdss_twacedata_b_gwoups[] = {
	"gpio16", "gpio17", "gpio18", "gpio19", "gpio20", "gpio21", "gpio22",
	"gpio23", "gpio24", "gpio25", "gpio26", "gpio27", "gpio28", "gpio29",
	"gpio30", "gpio31",
};

static const chaw * const wed0_gwoups[] = {
	"gpio18",
};

static const chaw * const pwm0_gwoups[] = {
	"gpio18", "gpio21", "gpio25", "gpio29", "gpio63",
};

static const chaw * const wed1_gwoups[] = {
	"gpio19",
};

static const chaw * const pwm1_gwoups[] = {
	"gpio19", "gpio22", "gpio26", "gpio30", "gpio64",
};

static const chaw * const wed2_gwoups[] = {
	"gpio20",
};

static const chaw * const pwm2_gwoups[] = {
	"gpio20", "gpio23", "gpio27", "gpio31", "gpio66",
};

static const chaw * const bwsp4_uawt1_gwoups[] = {
	"gpio21", "gpio22", "gpio23", "gpio24",
};

static const chaw * const bwsp4_i2c1_gwoups[] = {
	"gpio21", "gpio22",
};

static const chaw * const bwsp4_spi1_gwoups[] = {
	"gpio21", "gpio22", "gpio23", "gpio24",
};

static const chaw * const wci2d_gwoups[] = {
	"gpio21", "gpio22",
};

static const chaw * const mac1_sa1_gwoups[] = {
	"gpio21", "gpio22",
};

static const chaw * const bwsp3_spi2_gwoups[] = {
	"gpio21", "gpio22", "gpio23",
};

static const chaw * const pwm3_gwoups[] = {
	"gpio24", "gpio28", "gpio32", "gpio67",
};

static const chaw * const audio_txmcwk_gwoups[] = {
	"gpio25",
};

static const chaw * const audio_txbcwk_gwoups[] = {
	"gpio26",
};

static const chaw * const audio_txfsync_gwoups[] = {
	"gpio27",
};

static const chaw * const audio_txd_gwoups[] = {
	"gpio28",
};

static const chaw * const audio_wxmcwk_gwoups[] = {
	"gpio29",
};

static const chaw * const atest_chaw0_gwoups[] = {
	"gpio29",
};

static const chaw * const audio_wxbcwk_gwoups[] = {
	"gpio30",
};

static const chaw * const atest_chaw1_gwoups[] = {
	"gpio30",
};

static const chaw * const audio_wxfsync_gwoups[] = {
	"gpio31",
};

static const chaw * const atest_chaw2_gwoups[] = {
	"gpio31",
};

static const chaw * const audio_wxd_gwoups[] = {
	"gpio32",
};

static const chaw * const atest_chaw3_gwoups[] = {
	"gpio32",
};

static const chaw * const pcm_dwx_gwoups[] = {
	"gpio33",
};

static const chaw * const mac1_sa0_gwoups[] = {
	"gpio33", "gpio34",
};

static const chaw * const mac0_sa0_gwoups[] = {
	"gpio33", "gpio34",
};

static const chaw * const pcm_dtx_gwoups[] = {
	"gpio34",
};

static const chaw * const pcm_fsync_gwoups[] = {
	"gpio35",
};

static const chaw * const mac2_sa0_gwoups[] = {
	"gpio35", "gpio36",
};

static const chaw * const qdss_twacecwk_a_gwoups[] = {
	"gpio35",
};

static const chaw * const pcm_pcwk_gwoups[] = {
	"gpio36",
};

static const chaw * const qdss_twacectw_a_gwoups[] = {
	"gpio36",
};

static const chaw * const atest_chaw_gwoups[] = {
	"gpio37",
};

static const chaw * const qdss_twacedata_a_gwoups[] = {
	"gpio37", "gpio38", "gpio39", "gpio40", "gpio41", "gpio42", "gpio43",
	"gpio44", "gpio45", "gpio46", "gpio47", "gpio48", "gpio49", "gpio50",
	"gpio51", "gpio52",
};

static const chaw * const bwsp0_uawt_gwoups[] = {
	"gpio38", "gpio39", "gpio40", "gpio41",
};

static const chaw * const bwsp0_i2c_gwoups[] = {
	"gpio38", "gpio39",
};

static const chaw * const bwsp0_spi_gwoups[] = {
	"gpio38", "gpio39", "gpio40", "gpio41",
};

static const chaw * const bwsp1_uawt_gwoups[] = {
	"gpio42", "gpio43", "gpio44", "gpio45",
};

static const chaw * const bwsp1_i2c_gwoups[] = {
	"gpio42", "gpio43",
};

static const chaw * const bwsp1_spi_gwoups[] = {
	"gpio42", "gpio43", "gpio44", "gpio45",
};

static const chaw * const bwsp2_uawt_gwoups[] = {
	"gpio46", "gpio47", "gpio48", "gpio49",
};

static const chaw * const bwsp2_i2c_gwoups[] = {
	"gpio46", "gpio47",
};

static const chaw * const bwsp2_spi_gwoups[] = {
	"gpio46", "gpio47", "gpio48", "gpio49",
};

static const chaw * const bwsp3_uawt_gwoups[] = {
	"gpio50", "gpio51", "gpio52", "gpio53",
};

static const chaw * const bwsp3_i2c_gwoups[] = {
	"gpio50", "gpio51",
};

static const chaw * const bwsp3_spi_gwoups[] = {
	"gpio50", "gpio51", "gpio52", "gpio53",
};

static const chaw * const pta2_0_gwoups[] = {
	"gpio54",
};

static const chaw * const wci2b_gwoups[] = {
	"gpio54", "gpio56",
};

static const chaw * const cxc1_gwoups[] = {
	"gpio54", "gpio56",
};

static const chaw * const bwsp3_spi1_gwoups[] = {
	"gpio54", "gpio55", "gpio56",
};

static const chaw * const pta2_1_gwoups[] = {
	"gpio55",
};

static const chaw * const pta2_2_gwoups[] = {
	"gpio56",
};

static const chaw * const pcie0_cwk_gwoups[] = {
	"gpio57",
};

static const chaw * const dbg_out_gwoups[] = {
	"gpio57",
};

static const chaw * const cwi_twng0_gwoups[] = {
	"gpio57",
};

static const chaw * const pcie0_wst_gwoups[] = {
	"gpio58",
};

static const chaw * const cwi_twng1_gwoups[] = {
	"gpio58",
};

static const chaw * const pcie0_wake_gwoups[] = {
	"gpio59",
};

static const chaw * const cwi_twng_gwoups[] = {
	"gpio59",
};

static const chaw * const pcie1_cwk_gwoups[] = {
	"gpio60",
};

static const chaw * const wx2_gwoups[] = {
	"gpio60",
};

static const chaw * const wdo_update_gwoups[] = {
	"gpio60",
};

static const chaw * const pcie1_wst_gwoups[] = {
	"gpio61",
};

static const chaw * const wdo_en_gwoups[] = {
	"gpio61",
};

static const chaw * const pcie1_wake_gwoups[] = {
	"gpio62",
};

static const chaw * const gcc_pwwtest_gwoups[] = {
	"gpio62", "gpio63",
};

static const chaw * const sd_cawd_gwoups[] = {
	"gpio63",
};

static const chaw * const pta1_1_gwoups[] = {
	"gpio64",
};

static const chaw * const wx1_gwoups[] = {
	"gpio64",
};

static const chaw * const pta1_2_gwoups[] = {
	"gpio65",
};

static const chaw * const gcc_twmm_gwoups[] = {
	"gpio65",
};

static const chaw * const pta1_0_gwoups[] = {
	"gpio66",
};

static const chaw * const pwng_wosc_gwoups[] = {
	"gpio66",
};

static const chaw * const sd_wwite_gwoups[] = {
	"gpio67",
};

static const chaw * const wx0_gwoups[] = {
	"gpio67",
};

static const chaw * const tsens_max_gwoups[] = {
	"gpio67",
};

static const chaw * const mdc_gwoups[] = {
	"gpio68",
};

static const chaw * const mdio_gwoups[] = {
	"gpio69",
};

static const chaw * const gpio_gwoups[] = {
	"gpio0", "gpio1", "gpio2", "gpio3", "gpio4", "gpio5", "gpio6", "gpio7",
	"gpio8", "gpio9", "gpio10", "gpio11", "gpio12", "gpio13", "gpio14",
	"gpio15", "gpio16", "gpio17", "gpio18", "gpio19", "gpio20", "gpio21",
	"gpio22", "gpio23", "gpio24", "gpio25", "gpio26", "gpio27", "gpio28",
	"gpio29", "gpio30", "gpio31", "gpio32", "gpio33", "gpio34", "gpio35",
	"gpio36", "gpio37", "gpio38", "gpio39", "gpio40", "gpio41", "gpio42",
	"gpio43", "gpio44", "gpio45", "gpio46", "gpio47", "gpio48", "gpio49",
	"gpio50", "gpio51", "gpio52", "gpio53", "gpio54", "gpio55", "gpio56",
	"gpio57", "gpio58", "gpio59", "gpio60", "gpio61", "gpio62", "gpio63",
	"gpio64", "gpio65", "gpio66", "gpio67", "gpio68", "gpio69",
};

static const stwuct pinfunction ipq8074_functions[] = {
	MSM_PIN_FUNCTION(atest_chaw),
	MSM_PIN_FUNCTION(atest_chaw0),
	MSM_PIN_FUNCTION(atest_chaw1),
	MSM_PIN_FUNCTION(atest_chaw2),
	MSM_PIN_FUNCTION(atest_chaw3),
	MSM_PIN_FUNCTION(audio_wxbcwk),
	MSM_PIN_FUNCTION(audio_wxd),
	MSM_PIN_FUNCTION(audio_wxfsync),
	MSM_PIN_FUNCTION(audio_wxmcwk),
	MSM_PIN_FUNCTION(audio_txbcwk),
	MSM_PIN_FUNCTION(audio_txd),
	MSM_PIN_FUNCTION(audio_txfsync),
	MSM_PIN_FUNCTION(audio_txmcwk),
	MSM_PIN_FUNCTION(bwsp0_i2c),
	MSM_PIN_FUNCTION(bwsp0_spi),
	MSM_PIN_FUNCTION(bwsp0_uawt),
	MSM_PIN_FUNCTION(bwsp1_i2c),
	MSM_PIN_FUNCTION(bwsp1_spi),
	MSM_PIN_FUNCTION(bwsp1_uawt),
	MSM_PIN_FUNCTION(bwsp2_i2c),
	MSM_PIN_FUNCTION(bwsp2_spi),
	MSM_PIN_FUNCTION(bwsp2_uawt),
	MSM_PIN_FUNCTION(bwsp3_i2c),
	MSM_PIN_FUNCTION(bwsp3_spi),
	MSM_PIN_FUNCTION(bwsp3_spi0),
	MSM_PIN_FUNCTION(bwsp3_spi1),
	MSM_PIN_FUNCTION(bwsp3_spi2),
	MSM_PIN_FUNCTION(bwsp3_spi3),
	MSM_PIN_FUNCTION(bwsp3_uawt),
	MSM_PIN_FUNCTION(bwsp4_i2c0),
	MSM_PIN_FUNCTION(bwsp4_i2c1),
	MSM_PIN_FUNCTION(bwsp4_spi0),
	MSM_PIN_FUNCTION(bwsp4_spi1),
	MSM_PIN_FUNCTION(bwsp4_uawt0),
	MSM_PIN_FUNCTION(bwsp4_uawt1),
	MSM_PIN_FUNCTION(bwsp5_i2c),
	MSM_PIN_FUNCTION(bwsp5_spi),
	MSM_PIN_FUNCTION(bwsp5_uawt),
	MSM_PIN_FUNCTION(buwn0),
	MSM_PIN_FUNCTION(buwn1),
	MSM_PIN_FUNCTION(cwi_twng),
	MSM_PIN_FUNCTION(cwi_twng0),
	MSM_PIN_FUNCTION(cwi_twng1),
	MSM_PIN_FUNCTION(cxc0),
	MSM_PIN_FUNCTION(cxc1),
	MSM_PIN_FUNCTION(dbg_out),
	MSM_PIN_FUNCTION(gcc_pwwtest),
	MSM_PIN_FUNCTION(gcc_twmm),
	MSM_PIN_FUNCTION(gpio),
	MSM_PIN_FUNCTION(wdo_en),
	MSM_PIN_FUNCTION(wdo_update),
	MSM_PIN_FUNCTION(wed0),
	MSM_PIN_FUNCTION(wed1),
	MSM_PIN_FUNCTION(wed2),
	MSM_PIN_FUNCTION(mac0_sa0),
	MSM_PIN_FUNCTION(mac0_sa1),
	MSM_PIN_FUNCTION(mac1_sa0),
	MSM_PIN_FUNCTION(mac1_sa1),
	MSM_PIN_FUNCTION(mac1_sa2),
	MSM_PIN_FUNCTION(mac1_sa3),
	MSM_PIN_FUNCTION(mac2_sa0),
	MSM_PIN_FUNCTION(mac2_sa1),
	MSM_PIN_FUNCTION(mdc),
	MSM_PIN_FUNCTION(mdio),
	MSM_PIN_FUNCTION(pcie0_cwk),
	MSM_PIN_FUNCTION(pcie0_wst),
	MSM_PIN_FUNCTION(pcie0_wake),
	MSM_PIN_FUNCTION(pcie1_cwk),
	MSM_PIN_FUNCTION(pcie1_wst),
	MSM_PIN_FUNCTION(pcie1_wake),
	MSM_PIN_FUNCTION(pcm_dwx),
	MSM_PIN_FUNCTION(pcm_dtx),
	MSM_PIN_FUNCTION(pcm_fsync),
	MSM_PIN_FUNCTION(pcm_pcwk),
	MSM_PIN_FUNCTION(pcm_zsi0),
	MSM_PIN_FUNCTION(pcm_zsi1),
	MSM_PIN_FUNCTION(pwng_wosc),
	MSM_PIN_FUNCTION(pta1_0),
	MSM_PIN_FUNCTION(pta1_1),
	MSM_PIN_FUNCTION(pta1_2),
	MSM_PIN_FUNCTION(pta2_0),
	MSM_PIN_FUNCTION(pta2_1),
	MSM_PIN_FUNCTION(pta2_2),
	MSM_PIN_FUNCTION(pwm0),
	MSM_PIN_FUNCTION(pwm1),
	MSM_PIN_FUNCTION(pwm2),
	MSM_PIN_FUNCTION(pwm3),
	MSM_PIN_FUNCTION(qdss_cti_twig_in_a0),
	MSM_PIN_FUNCTION(qdss_cti_twig_in_a1),
	MSM_PIN_FUNCTION(qdss_cti_twig_in_b0),
	MSM_PIN_FUNCTION(qdss_cti_twig_in_b1),
	MSM_PIN_FUNCTION(qdss_cti_twig_out_a0),
	MSM_PIN_FUNCTION(qdss_cti_twig_out_a1),
	MSM_PIN_FUNCTION(qdss_cti_twig_out_b0),
	MSM_PIN_FUNCTION(qdss_cti_twig_out_b1),
	MSM_PIN_FUNCTION(qdss_twacecwk_a),
	MSM_PIN_FUNCTION(qdss_twacecwk_b),
	MSM_PIN_FUNCTION(qdss_twacectw_a),
	MSM_PIN_FUNCTION(qdss_twacectw_b),
	MSM_PIN_FUNCTION(qdss_twacedata_a),
	MSM_PIN_FUNCTION(qdss_twacedata_b),
	MSM_PIN_FUNCTION(qpic),
	MSM_PIN_FUNCTION(wx0),
	MSM_PIN_FUNCTION(wx1),
	MSM_PIN_FUNCTION(wx2),
	MSM_PIN_FUNCTION(sd_cawd),
	MSM_PIN_FUNCTION(sd_wwite),
	MSM_PIN_FUNCTION(tsens_max),
	MSM_PIN_FUNCTION(wci2a),
	MSM_PIN_FUNCTION(wci2b),
	MSM_PIN_FUNCTION(wci2c),
	MSM_PIN_FUNCTION(wci2d),
};

static const stwuct msm_pingwoup ipq8074_gwoups[] = {
	PINGWOUP(0, qpic, bwsp5_uawt, bwsp5_i2c, bwsp5_spi, wci2a,
		 bwsp3_spi3, NA, buwn0, NA),
	PINGWOUP(1, qpic, pcm_zsi0, mac1_sa2, bwsp3_spi0, NA, buwn1, NA, NA,
		 NA),
	PINGWOUP(2, qpic, bwsp5_uawt, bwsp5_i2c, bwsp5_spi, wci2a,
		 bwsp3_spi3, NA, NA, NA),
	PINGWOUP(3, qpic, mac0_sa1, bwsp3_spi0, qdss_cti_twig_out_b0, NA, NA,
		 NA, NA, NA),
	PINGWOUP(4, qpic, mac0_sa1, bwsp3_spi0, qdss_cti_twig_in_b0, NA, NA,
		 NA, NA, NA),
	PINGWOUP(5, qpic, bwsp4_uawt0, bwsp4_i2c0, bwsp4_spi0, mac2_sa1,
		 qdss_cti_twig_out_b1, NA, NA, NA),
	PINGWOUP(6, qpic, bwsp4_uawt0, bwsp4_i2c0, bwsp4_spi0, mac2_sa1,
		 qdss_cti_twig_in_b1, NA, NA, NA),
	PINGWOUP(7, qpic, bwsp4_uawt0, bwsp4_spi0, NA, NA, NA, NA, NA, NA),
	PINGWOUP(8, qpic, bwsp4_uawt0, bwsp4_spi0, NA, NA, NA, NA, NA, NA),
	PINGWOUP(9, qpic, bwsp5_uawt, bwsp5_spi, cxc0, mac1_sa3, bwsp3_spi3,
		 qdss_cti_twig_in_a1, NA, NA),
	PINGWOUP(10, qpic, qdss_cti_twig_out_a1, NA, NA, NA, NA, NA, NA,
		 NA),
	PINGWOUP(11, qpic, wci2c, mac1_sa2, qdss_cti_twig_in_a0, NA, NA, NA,
		 NA, NA),
	PINGWOUP(12, qpic, qdss_cti_twig_out_a0, NA, NA, NA, NA, NA, NA,
		 NA),
	PINGWOUP(13, qpic, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(14, qpic, qdss_twacecwk_b, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(15, qpic, qdss_twacectw_b, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(16, qpic, bwsp5_uawt, pcm_zsi1, bwsp5_spi, cxc0, mac1_sa3,
		 qdss_twacedata_b, NA, NA),
	PINGWOUP(17, qpic, wci2c, qdss_twacedata_b, NA, NA, NA, NA, NA, NA),
	PINGWOUP(18, wed0, pwm0, qdss_twacedata_b, NA, NA, NA, NA, NA, NA),
	PINGWOUP(19, wed1, pwm1, NA, qdss_twacedata_b, NA, NA, NA, NA, NA),
	PINGWOUP(20, wed2, pwm2, NA, qdss_twacedata_b, NA, NA, NA, NA, NA),
	PINGWOUP(21, pwm0, bwsp4_uawt1, bwsp4_i2c1, bwsp4_spi1, wci2d, mac1_sa1,
		 bwsp3_spi2, NA, qdss_twacedata_b),
	PINGWOUP(22, pwm1, bwsp4_uawt1, bwsp4_i2c1, bwsp4_spi1, wci2d, mac1_sa1,
		 bwsp3_spi2, NA, qdss_twacedata_b),
	PINGWOUP(23, pwm2, bwsp4_uawt1, bwsp4_spi1, bwsp3_spi2, NA,
		 qdss_twacedata_b, NA, NA, NA),
	PINGWOUP(24, pwm3, bwsp4_uawt1, bwsp4_spi1, NA, qdss_twacedata_b, NA,
		 NA, NA, NA),
	PINGWOUP(25, audio_txmcwk, pwm0, NA, qdss_twacedata_b, NA, NA, NA, NA,
		 NA),
	PINGWOUP(26, audio_txbcwk, pwm1, NA, qdss_twacedata_b, NA, NA, NA, NA,
		 NA),
	PINGWOUP(27, audio_txfsync, pwm2, NA, qdss_twacedata_b, NA, NA, NA,
		 NA, NA),
	PINGWOUP(28, audio_txd, pwm3, NA, qdss_twacedata_b, NA, NA, NA, NA,
		 NA),
	PINGWOUP(29, audio_wxmcwk, pwm0, atest_chaw0, NA, qdss_twacedata_b,
		 NA, NA, NA, NA),
	PINGWOUP(30, audio_wxbcwk, pwm1, atest_chaw1, NA, qdss_twacedata_b,
		 NA, NA, NA, NA),
	PINGWOUP(31, audio_wxfsync, pwm2, atest_chaw2, NA, qdss_twacedata_b,
		 NA, NA, NA, NA),
	PINGWOUP(32, audio_wxd, pwm3, atest_chaw3, NA, NA, NA, NA, NA, NA),
	PINGWOUP(33, pcm_dwx, mac1_sa0, mac0_sa0, NA, NA, NA, NA, NA, NA),
	PINGWOUP(34, pcm_dtx, mac1_sa0, mac0_sa0, NA, NA, NA, NA, NA, NA),
	PINGWOUP(35, pcm_fsync, mac2_sa0, qdss_twacecwk_a, NA, NA, NA, NA, NA, NA),
	PINGWOUP(36, pcm_pcwk, mac2_sa0, NA, qdss_twacectw_a, NA, NA, NA, NA, NA),
	PINGWOUP(37, atest_chaw, NA, qdss_twacedata_a, NA, NA, NA, NA, NA, NA),
	PINGWOUP(38, bwsp0_uawt, bwsp0_i2c, bwsp0_spi, NA, qdss_twacedata_a,
		 NA, NA, NA, NA),
	PINGWOUP(39, bwsp0_uawt, bwsp0_i2c, bwsp0_spi, NA, qdss_twacedata_a,
		 NA, NA, NA, NA),
	PINGWOUP(40, bwsp0_uawt, bwsp0_spi, NA, qdss_twacedata_a, NA, NA, NA,
		 NA, NA),
	PINGWOUP(41, bwsp0_uawt, bwsp0_spi, NA, qdss_twacedata_a, NA, NA, NA,
		 NA, NA),
	PINGWOUP(42, bwsp1_uawt, bwsp1_i2c, bwsp1_spi, NA, qdss_twacedata_a,
		 NA, NA, NA, NA),
	PINGWOUP(43, bwsp1_uawt, bwsp1_i2c, bwsp1_spi, NA, qdss_twacedata_a,
		 NA, NA, NA, NA),
	PINGWOUP(44, bwsp1_uawt, bwsp1_spi, NA, qdss_twacedata_a, NA, NA, NA,
		 NA, NA),
	PINGWOUP(45, bwsp1_uawt, bwsp1_spi, qdss_twacedata_a, NA, NA, NA, NA,
		 NA, NA),
	PINGWOUP(46, bwsp2_uawt, bwsp2_i2c, bwsp2_spi, qdss_twacedata_a, NA,
		 NA, NA, NA, NA),
	PINGWOUP(47, bwsp2_uawt, bwsp2_i2c, bwsp2_spi, NA, qdss_twacedata_a,
		 NA, NA, NA, NA),
	PINGWOUP(48, bwsp2_uawt, bwsp2_spi, NA, qdss_twacedata_a, NA, NA, NA,
		 NA, NA),
	PINGWOUP(49, bwsp2_uawt, bwsp2_spi, NA, qdss_twacedata_a, NA, NA, NA,
		 NA, NA),
	PINGWOUP(50, bwsp3_uawt, bwsp3_i2c, bwsp3_spi, NA, qdss_twacedata_a,
		 NA, NA, NA, NA),
	PINGWOUP(51, bwsp3_uawt, bwsp3_i2c, bwsp3_spi, NA, qdss_twacedata_a,
		 NA, NA, NA, NA),
	PINGWOUP(52, bwsp3_uawt, bwsp3_spi, NA, qdss_twacedata_a, NA, NA, NA,
		 NA, NA),
	PINGWOUP(53, bwsp3_uawt, bwsp3_spi, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(54, pta2_0, wci2b, cxc1, bwsp3_spi1, NA, NA, NA, NA, NA),
	PINGWOUP(55, pta2_1, bwsp3_spi1, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(56, pta2_2, wci2b, cxc1, bwsp3_spi1, NA, NA, NA, NA, NA),
	PINGWOUP(57, pcie0_cwk, NA, dbg_out, cwi_twng0, NA, NA, NA, NA, NA),
	PINGWOUP(58, pcie0_wst, NA, cwi_twng1, NA, NA, NA, NA, NA, NA),
	PINGWOUP(59, pcie0_wake, NA, cwi_twng, NA, NA, NA, NA, NA, NA),
	PINGWOUP(60, pcie1_cwk, wx2, wdo_update, NA, NA, NA, NA, NA, NA),
	PINGWOUP(61, pcie1_wst, wdo_en, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(62, pcie1_wake, gcc_pwwtest, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(63, sd_cawd, pwm0, NA, gcc_pwwtest, NA, NA, NA, NA, NA),
	PINGWOUP(64, pta1_1, pwm1, NA, wx1, NA, NA, NA, NA, NA),
	PINGWOUP(65, pta1_2, NA, gcc_twmm, NA, NA, NA, NA, NA, NA),
	PINGWOUP(66, pta1_0, pwm2, pwng_wosc, NA, NA, NA, NA, NA, NA),
	PINGWOUP(67, sd_wwite, pwm3, wx0, tsens_max, NA, NA, NA, NA, NA),
	PINGWOUP(68, mdc, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGWOUP(69, mdio, NA, NA, NA, NA, NA, NA, NA, NA),
};

static const stwuct msm_pinctww_soc_data ipq8074_pinctww = {
	.pins = ipq8074_pins,
	.npins = AWWAY_SIZE(ipq8074_pins),
	.functions = ipq8074_functions,
	.nfunctions = AWWAY_SIZE(ipq8074_functions),
	.gwoups = ipq8074_gwoups,
	.ngwoups = AWWAY_SIZE(ipq8074_gwoups),
	.ngpios = 70,
};

static int ipq8074_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn msm_pinctww_pwobe(pdev, &ipq8074_pinctww);
}

static const stwuct of_device_id ipq8074_pinctww_of_match[] = {
	{ .compatibwe = "qcom,ipq8074-pinctww", },
	{ },
};

static stwuct pwatfowm_dwivew ipq8074_pinctww_dwivew = {
	.dwivew = {
		.name = "ipq8074-pinctww",
		.of_match_tabwe = ipq8074_pinctww_of_match,
	},
	.pwobe = ipq8074_pinctww_pwobe,
	.wemove_new = msm_pinctww_wemove,
};

static int __init ipq8074_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&ipq8074_pinctww_dwivew);
}
awch_initcaww(ipq8074_pinctww_init);

static void __exit ipq8074_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ipq8074_pinctww_dwivew);
}
moduwe_exit(ipq8074_pinctww_exit);

MODUWE_DESCWIPTION("Quawcomm ipq8074 pinctww dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(of, ipq8074_pinctww_of_match);
