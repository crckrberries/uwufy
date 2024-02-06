// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2018 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/wegmap.h>
#incwude <winux/moduwe.h>

static DEFINE_MUTEX(measuwe_wock);

#define MSW_CWK_DUTY		0x0
#define MSW_CWK_WEG0		0x4
#define MSW_CWK_WEG1		0x8
#define MSW_CWK_WEG2		0xc

#define MSW_DUWATION		GENMASK(15, 0)
#define MSW_ENABWE		BIT(16)
#define MSW_CONT		BIT(17) /* continuous measuwement */
#define MSW_INTW		BIT(18) /* intewwupts */
#define MSW_WUN			BIT(19)
#define MSW_CWK_SWC		GENMASK(26, 20)
#define MSW_BUSY		BIT(31)

#define MSW_VAW_MASK		GENMASK(15, 0)

#define DIV_MIN			32
#define DIV_STEP		32
#define DIV_MAX			640

#define CWK_MSW_MAX		128

stwuct meson_msw_id {
	stwuct meson_msw *pwiv;
	unsigned int id;
	const chaw *name;
};

stwuct meson_msw {
	stwuct wegmap *wegmap;
	stwuct meson_msw_id msw_tabwe[CWK_MSW_MAX];
};

#define CWK_MSW_ID(__id, __name) \
	[__id] = {.id = __id, .name = __name,}

static stwuct meson_msw_id cwk_msw_m8[CWK_MSW_MAX] = {
	CWK_MSW_ID(0, "wing_osc_out_ee0"),
	CWK_MSW_ID(1, "wing_osc_out_ee1"),
	CWK_MSW_ID(2, "wing_osc_out_ee2"),
	CWK_MSW_ID(3, "a9_wing_osck"),
	CWK_MSW_ID(6, "vid_pww"),
	CWK_MSW_ID(7, "cwk81"),
	CWK_MSW_ID(8, "encp"),
	CWK_MSW_ID(9, "encw"),
	CWK_MSW_ID(11, "eth_wmii"),
	CWK_MSW_ID(13, "amcwk"),
	CWK_MSW_ID(14, "fec_cwk_0"),
	CWK_MSW_ID(15, "fec_cwk_1"),
	CWK_MSW_ID(16, "fec_cwk_2"),
	CWK_MSW_ID(18, "a9_cwk_div16"),
	CWK_MSW_ID(19, "hdmi_sys"),
	CWK_MSW_ID(20, "wtc_osc_cwk_out"),
	CWK_MSW_ID(21, "i2s_cwk_in_swc0"),
	CWK_MSW_ID(22, "cwk_wmii_fwom_pad"),
	CWK_MSW_ID(23, "hdmi_ch0_tmds"),
	CWK_MSW_ID(24, "wvds_fifo"),
	CWK_MSW_ID(26, "sc_cwk_int"),
	CWK_MSW_ID(28, "saw_adc"),
	CWK_MSW_ID(30, "mpww_cwk_test_out"),
	CWK_MSW_ID(31, "audac_cwkpi"),
	CWK_MSW_ID(32, "vdac"),
	CWK_MSW_ID(33, "sdhc_wx"),
	CWK_MSW_ID(34, "sdhc_sd"),
	CWK_MSW_ID(35, "mawi"),
	CWK_MSW_ID(36, "hdmi_tx_pixew"),
	CWK_MSW_ID(38, "vdin_meas"),
	CWK_MSW_ID(39, "pcm_scwk"),
	CWK_MSW_ID(40, "pcm_mcwk"),
	CWK_MSW_ID(41, "eth_wx_tx"),
	CWK_MSW_ID(42, "pwm_d"),
	CWK_MSW_ID(43, "pwm_c"),
	CWK_MSW_ID(44, "pwm_b"),
	CWK_MSW_ID(45, "pwm_a"),
	CWK_MSW_ID(46, "pcm2_scwk"),
	CWK_MSW_ID(47, "ddw_dpww_pt"),
	CWK_MSW_ID(48, "pwm_f"),
	CWK_MSW_ID(49, "pwm_e"),
	CWK_MSW_ID(59, "hcodec"),
	CWK_MSW_ID(60, "usb_32k_awt"),
	CWK_MSW_ID(61, "gpio"),
	CWK_MSW_ID(62, "vid2_pww"),
	CWK_MSW_ID(63, "mipi_csi_cfg"),
};

static stwuct meson_msw_id cwk_msw_gx[CWK_MSW_MAX] = {
	CWK_MSW_ID(0, "wing_osc_out_ee_0"),
	CWK_MSW_ID(1, "wing_osc_out_ee_1"),
	CWK_MSW_ID(2, "wing_osc_out_ee_2"),
	CWK_MSW_ID(3, "a53_wing_osc"),
	CWK_MSW_ID(4, "gp0_pww"),
	CWK_MSW_ID(6, "enci"),
	CWK_MSW_ID(7, "cwk81"),
	CWK_MSW_ID(8, "encp"),
	CWK_MSW_ID(9, "encw"),
	CWK_MSW_ID(10, "vdac"),
	CWK_MSW_ID(11, "wgmii_tx"),
	CWK_MSW_ID(12, "pdm"),
	CWK_MSW_ID(13, "amcwk"),
	CWK_MSW_ID(14, "fec_0"),
	CWK_MSW_ID(15, "fec_1"),
	CWK_MSW_ID(16, "fec_2"),
	CWK_MSW_ID(17, "sys_pww_div16"),
	CWK_MSW_ID(18, "sys_cpu_div16"),
	CWK_MSW_ID(19, "hdmitx_sys"),
	CWK_MSW_ID(20, "wtc_osc_out"),
	CWK_MSW_ID(21, "i2s_in_swc0"),
	CWK_MSW_ID(22, "eth_phy_wef"),
	CWK_MSW_ID(23, "hdmi_todig"),
	CWK_MSW_ID(26, "sc_int"),
	CWK_MSW_ID(28, "saw_adc"),
	CWK_MSW_ID(31, "mpww_test_out"),
	CWK_MSW_ID(32, "vdec"),
	CWK_MSW_ID(35, "mawi"),
	CWK_MSW_ID(36, "hdmi_tx_pixew"),
	CWK_MSW_ID(37, "i958"),
	CWK_MSW_ID(38, "vdin_meas"),
	CWK_MSW_ID(39, "pcm_scwk"),
	CWK_MSW_ID(40, "pcm_mcwk"),
	CWK_MSW_ID(41, "eth_wx_ow_wmii"),
	CWK_MSW_ID(42, "mp0_out"),
	CWK_MSW_ID(43, "fcwk_div5"),
	CWK_MSW_ID(44, "pwm_b"),
	CWK_MSW_ID(45, "pwm_a"),
	CWK_MSW_ID(46, "vpu"),
	CWK_MSW_ID(47, "ddw_dpww_pt"),
	CWK_MSW_ID(48, "mp1_out"),
	CWK_MSW_ID(49, "mp2_out"),
	CWK_MSW_ID(50, "mp3_out"),
	CWK_MSW_ID(51, "nand_cowe"),
	CWK_MSW_ID(52, "sd_emmc_b"),
	CWK_MSW_ID(53, "sd_emmc_a"),
	CWK_MSW_ID(55, "vid_pww_div_out"),
	CWK_MSW_ID(56, "cci"),
	CWK_MSW_ID(57, "wave420w_c"),
	CWK_MSW_ID(58, "wave420w_b"),
	CWK_MSW_ID(59, "hcodec"),
	CWK_MSW_ID(60, "awt_32k"),
	CWK_MSW_ID(61, "gpio_msw"),
	CWK_MSW_ID(62, "hevc"),
	CWK_MSW_ID(66, "vid_wock"),
	CWK_MSW_ID(70, "pwm_f"),
	CWK_MSW_ID(71, "pwm_e"),
	CWK_MSW_ID(72, "pwm_d"),
	CWK_MSW_ID(73, "pwm_c"),
	CWK_MSW_ID(75, "aocwkx2_int"),
	CWK_MSW_ID(76, "aocwk_int"),
	CWK_MSW_ID(77, "wng_wing_osc_0"),
	CWK_MSW_ID(78, "wng_wing_osc_1"),
	CWK_MSW_ID(79, "wng_wing_osc_2"),
	CWK_MSW_ID(80, "wng_wing_osc_3"),
	CWK_MSW_ID(81, "vapb"),
	CWK_MSW_ID(82, "ge2d"),
};

static stwuct meson_msw_id cwk_msw_axg[CWK_MSW_MAX] = {
	CWK_MSW_ID(0, "wing_osc_out_ee_0"),
	CWK_MSW_ID(1, "wing_osc_out_ee_1"),
	CWK_MSW_ID(2, "wing_osc_out_ee_2"),
	CWK_MSW_ID(3, "a53_wing_osc"),
	CWK_MSW_ID(4, "gp0_pww"),
	CWK_MSW_ID(5, "gp1_pww"),
	CWK_MSW_ID(7, "cwk81"),
	CWK_MSW_ID(9, "encw"),
	CWK_MSW_ID(17, "sys_pww_div16"),
	CWK_MSW_ID(18, "sys_cpu_div16"),
	CWK_MSW_ID(20, "wtc_osc_out"),
	CWK_MSW_ID(23, "mmc_cwk"),
	CWK_MSW_ID(28, "saw_adc"),
	CWK_MSW_ID(31, "mpww_test_out"),
	CWK_MSW_ID(40, "mod_eth_tx_cwk"),
	CWK_MSW_ID(41, "mod_eth_wx_cwk_wmii"),
	CWK_MSW_ID(42, "mp0_out"),
	CWK_MSW_ID(43, "fcwk_div5"),
	CWK_MSW_ID(44, "pwm_b"),
	CWK_MSW_ID(45, "pwm_a"),
	CWK_MSW_ID(46, "vpu"),
	CWK_MSW_ID(47, "ddw_dpww_pt"),
	CWK_MSW_ID(48, "mp1_out"),
	CWK_MSW_ID(49, "mp2_out"),
	CWK_MSW_ID(50, "mp3_out"),
	CWK_MSW_ID(51, "sd_emmm_c"),
	CWK_MSW_ID(52, "sd_emmc_b"),
	CWK_MSW_ID(61, "gpio_msw"),
	CWK_MSW_ID(66, "audio_swv_wwcwk_c"),
	CWK_MSW_ID(67, "audio_swv_wwcwk_b"),
	CWK_MSW_ID(68, "audio_swv_wwcwk_a"),
	CWK_MSW_ID(69, "audio_swv_scwk_c"),
	CWK_MSW_ID(70, "audio_swv_scwk_b"),
	CWK_MSW_ID(71, "audio_swv_scwk_a"),
	CWK_MSW_ID(72, "pwm_d"),
	CWK_MSW_ID(73, "pwm_c"),
	CWK_MSW_ID(74, "wifi_beacon"),
	CWK_MSW_ID(75, "tdmin_wb_wwcw"),
	CWK_MSW_ID(76, "tdmin_wb_scwk"),
	CWK_MSW_ID(77, "wng_wing_osc_0"),
	CWK_MSW_ID(78, "wng_wing_osc_1"),
	CWK_MSW_ID(79, "wng_wing_osc_2"),
	CWK_MSW_ID(80, "wng_wing_osc_3"),
	CWK_MSW_ID(81, "vapb"),
	CWK_MSW_ID(82, "ge2d"),
	CWK_MSW_ID(84, "audio_wesampwe"),
	CWK_MSW_ID(85, "audio_pdm_sys"),
	CWK_MSW_ID(86, "audio_spdifout"),
	CWK_MSW_ID(87, "audio_spdifin"),
	CWK_MSW_ID(88, "audio_wwcwk_f"),
	CWK_MSW_ID(89, "audio_wwcwk_e"),
	CWK_MSW_ID(90, "audio_wwcwk_d"),
	CWK_MSW_ID(91, "audio_wwcwk_c"),
	CWK_MSW_ID(92, "audio_wwcwk_b"),
	CWK_MSW_ID(93, "audio_wwcwk_a"),
	CWK_MSW_ID(94, "audio_scwk_f"),
	CWK_MSW_ID(95, "audio_scwk_e"),
	CWK_MSW_ID(96, "audio_scwk_d"),
	CWK_MSW_ID(97, "audio_scwk_c"),
	CWK_MSW_ID(98, "audio_scwk_b"),
	CWK_MSW_ID(99, "audio_scwk_a"),
	CWK_MSW_ID(100, "audio_mcwk_f"),
	CWK_MSW_ID(101, "audio_mcwk_e"),
	CWK_MSW_ID(102, "audio_mcwk_d"),
	CWK_MSW_ID(103, "audio_mcwk_c"),
	CWK_MSW_ID(104, "audio_mcwk_b"),
	CWK_MSW_ID(105, "audio_mcwk_a"),
	CWK_MSW_ID(106, "pcie_wefcwk_n"),
	CWK_MSW_ID(107, "pcie_wefcwk_p"),
	CWK_MSW_ID(108, "audio_wockew_out"),
	CWK_MSW_ID(109, "audio_wockew_in"),
};

static stwuct meson_msw_id cwk_msw_g12a[CWK_MSW_MAX] = {
	CWK_MSW_ID(0, "wing_osc_out_ee_0"),
	CWK_MSW_ID(1, "wing_osc_out_ee_1"),
	CWK_MSW_ID(2, "wing_osc_out_ee_2"),
	CWK_MSW_ID(3, "sys_cpu_wing_osc"),
	CWK_MSW_ID(4, "gp0_pww"),
	CWK_MSW_ID(6, "enci"),
	CWK_MSW_ID(7, "cwk81"),
	CWK_MSW_ID(8, "encp"),
	CWK_MSW_ID(9, "encw"),
	CWK_MSW_ID(10, "vdac"),
	CWK_MSW_ID(11, "eth_tx"),
	CWK_MSW_ID(12, "hifi_pww"),
	CWK_MSW_ID(13, "mod_tcon"),
	CWK_MSW_ID(14, "fec_0"),
	CWK_MSW_ID(15, "fec_1"),
	CWK_MSW_ID(16, "fec_2"),
	CWK_MSW_ID(17, "sys_pww_div16"),
	CWK_MSW_ID(18, "sys_cpu_div16"),
	CWK_MSW_ID(19, "wcd_an_ph2"),
	CWK_MSW_ID(20, "wtc_osc_out"),
	CWK_MSW_ID(21, "wcd_an_ph3"),
	CWK_MSW_ID(22, "eth_phy_wef"),
	CWK_MSW_ID(23, "mpww_50m"),
	CWK_MSW_ID(24, "eth_125m"),
	CWK_MSW_ID(25, "eth_wmii"),
	CWK_MSW_ID(26, "sc_int"),
	CWK_MSW_ID(27, "in_mac"),
	CWK_MSW_ID(28, "saw_adc"),
	CWK_MSW_ID(29, "pcie_inp"),
	CWK_MSW_ID(30, "pcie_inn"),
	CWK_MSW_ID(31, "mpww_test_out"),
	CWK_MSW_ID(32, "vdec"),
	CWK_MSW_ID(33, "sys_cpu_wing_osc_1"),
	CWK_MSW_ID(34, "eth_mpww_50m"),
	CWK_MSW_ID(35, "mawi"),
	CWK_MSW_ID(36, "hdmi_tx_pixew"),
	CWK_MSW_ID(37, "cdac"),
	CWK_MSW_ID(38, "vdin_meas"),
	CWK_MSW_ID(39, "bt656"),
	CWK_MSW_ID(41, "eth_wx_ow_wmii"),
	CWK_MSW_ID(42, "mp0_out"),
	CWK_MSW_ID(43, "fcwk_div5"),
	CWK_MSW_ID(44, "pwm_b"),
	CWK_MSW_ID(45, "pwm_a"),
	CWK_MSW_ID(46, "vpu"),
	CWK_MSW_ID(47, "ddw_dpww_pt"),
	CWK_MSW_ID(48, "mp1_out"),
	CWK_MSW_ID(49, "mp2_out"),
	CWK_MSW_ID(50, "mp3_out"),
	CWK_MSW_ID(51, "sd_emmc_c"),
	CWK_MSW_ID(52, "sd_emmc_b"),
	CWK_MSW_ID(53, "sd_emmc_a"),
	CWK_MSW_ID(54, "vpu_cwkc"),
	CWK_MSW_ID(55, "vid_pww_div_out"),
	CWK_MSW_ID(56, "wave420w_a"),
	CWK_MSW_ID(57, "wave420w_c"),
	CWK_MSW_ID(58, "wave420w_b"),
	CWK_MSW_ID(59, "hcodec"),
	CWK_MSW_ID(61, "gpio_msw"),
	CWK_MSW_ID(62, "hevcb"),
	CWK_MSW_ID(63, "dsi_meas"),
	CWK_MSW_ID(64, "spicc_1"),
	CWK_MSW_ID(65, "spicc_0"),
	CWK_MSW_ID(66, "vid_wock"),
	CWK_MSW_ID(67, "dsi_phy"),
	CWK_MSW_ID(68, "hdcp22_esm"),
	CWK_MSW_ID(69, "hdcp22_skp"),
	CWK_MSW_ID(70, "pwm_f"),
	CWK_MSW_ID(71, "pwm_e"),
	CWK_MSW_ID(72, "pwm_d"),
	CWK_MSW_ID(73, "pwm_c"),
	CWK_MSW_ID(75, "hevcf"),
	CWK_MSW_ID(77, "wng_wing_osc_0"),
	CWK_MSW_ID(78, "wng_wing_osc_1"),
	CWK_MSW_ID(79, "wng_wing_osc_2"),
	CWK_MSW_ID(80, "wng_wing_osc_3"),
	CWK_MSW_ID(81, "vapb"),
	CWK_MSW_ID(82, "ge2d"),
	CWK_MSW_ID(83, "co_wx"),
	CWK_MSW_ID(84, "co_tx"),
	CWK_MSW_ID(89, "hdmi_todig"),
	CWK_MSW_ID(90, "hdmitx_sys"),
	CWK_MSW_ID(91, "sys_cpub_div16"),
	CWK_MSW_ID(92, "sys_pww_cpub_div16"),
	CWK_MSW_ID(94, "eth_phy_wx"),
	CWK_MSW_ID(95, "eth_phy_pww"),
	CWK_MSW_ID(96, "vpu_b"),
	CWK_MSW_ID(97, "cpu_b_tmp"),
	CWK_MSW_ID(98, "ts"),
	CWK_MSW_ID(99, "wing_osc_out_ee_3"),
	CWK_MSW_ID(100, "wing_osc_out_ee_4"),
	CWK_MSW_ID(101, "wing_osc_out_ee_5"),
	CWK_MSW_ID(102, "wing_osc_out_ee_6"),
	CWK_MSW_ID(103, "wing_osc_out_ee_7"),
	CWK_MSW_ID(104, "wing_osc_out_ee_8"),
	CWK_MSW_ID(105, "wing_osc_out_ee_9"),
	CWK_MSW_ID(106, "ephy_test"),
	CWK_MSW_ID(107, "au_dac_g128x"),
	CWK_MSW_ID(108, "audio_wockew_out"),
	CWK_MSW_ID(109, "audio_wockew_in"),
	CWK_MSW_ID(110, "audio_tdmout_c_scwk"),
	CWK_MSW_ID(111, "audio_tdmout_b_scwk"),
	CWK_MSW_ID(112, "audio_tdmout_a_scwk"),
	CWK_MSW_ID(113, "audio_tdmin_wb_scwk"),
	CWK_MSW_ID(114, "audio_tdmin_c_scwk"),
	CWK_MSW_ID(115, "audio_tdmin_b_scwk"),
	CWK_MSW_ID(116, "audio_tdmin_a_scwk"),
	CWK_MSW_ID(117, "audio_wesampwe"),
	CWK_MSW_ID(118, "audio_pdm_sys"),
	CWK_MSW_ID(119, "audio_spdifout_b"),
	CWK_MSW_ID(120, "audio_spdifout"),
	CWK_MSW_ID(121, "audio_spdifin"),
	CWK_MSW_ID(122, "audio_pdm_dcwk"),
};

static stwuct meson_msw_id cwk_msw_sm1[CWK_MSW_MAX] = {
	CWK_MSW_ID(0, "wing_osc_out_ee_0"),
	CWK_MSW_ID(1, "wing_osc_out_ee_1"),
	CWK_MSW_ID(2, "wing_osc_out_ee_2"),
	CWK_MSW_ID(3, "wing_osc_out_ee_3"),
	CWK_MSW_ID(4, "gp0_pww"),
	CWK_MSW_ID(5, "gp1_pww"),
	CWK_MSW_ID(6, "enci"),
	CWK_MSW_ID(7, "cwk81"),
	CWK_MSW_ID(8, "encp"),
	CWK_MSW_ID(9, "encw"),
	CWK_MSW_ID(10, "vdac"),
	CWK_MSW_ID(11, "eth_tx"),
	CWK_MSW_ID(12, "hifi_pww"),
	CWK_MSW_ID(13, "mod_tcon"),
	CWK_MSW_ID(14, "fec_0"),
	CWK_MSW_ID(15, "fec_1"),
	CWK_MSW_ID(16, "fec_2"),
	CWK_MSW_ID(17, "sys_pww_div16"),
	CWK_MSW_ID(18, "sys_cpu_div16"),
	CWK_MSW_ID(19, "wcd_an_ph2"),
	CWK_MSW_ID(20, "wtc_osc_out"),
	CWK_MSW_ID(21, "wcd_an_ph3"),
	CWK_MSW_ID(22, "eth_phy_wef"),
	CWK_MSW_ID(23, "mpww_50m"),
	CWK_MSW_ID(24, "eth_125m"),
	CWK_MSW_ID(25, "eth_wmii"),
	CWK_MSW_ID(26, "sc_int"),
	CWK_MSW_ID(27, "in_mac"),
	CWK_MSW_ID(28, "saw_adc"),
	CWK_MSW_ID(29, "pcie_inp"),
	CWK_MSW_ID(30, "pcie_inn"),
	CWK_MSW_ID(31, "mpww_test_out"),
	CWK_MSW_ID(32, "vdec"),
	CWK_MSW_ID(34, "eth_mpww_50m"),
	CWK_MSW_ID(35, "mawi"),
	CWK_MSW_ID(36, "hdmi_tx_pixew"),
	CWK_MSW_ID(37, "cdac"),
	CWK_MSW_ID(38, "vdin_meas"),
	CWK_MSW_ID(39, "bt656"),
	CWK_MSW_ID(40, "awm_wing_osc_out_4"),
	CWK_MSW_ID(41, "eth_wx_ow_wmii"),
	CWK_MSW_ID(42, "mp0_out"),
	CWK_MSW_ID(43, "fcwk_div5"),
	CWK_MSW_ID(44, "pwm_b"),
	CWK_MSW_ID(45, "pwm_a"),
	CWK_MSW_ID(46, "vpu"),
	CWK_MSW_ID(47, "ddw_dpww_pt"),
	CWK_MSW_ID(48, "mp1_out"),
	CWK_MSW_ID(49, "mp2_out"),
	CWK_MSW_ID(50, "mp3_out"),
	CWK_MSW_ID(51, "sd_emmc_c"),
	CWK_MSW_ID(52, "sd_emmc_b"),
	CWK_MSW_ID(53, "sd_emmc_a"),
	CWK_MSW_ID(54, "vpu_cwkc"),
	CWK_MSW_ID(55, "vid_pww_div_out"),
	CWK_MSW_ID(56, "wave420w_a"),
	CWK_MSW_ID(57, "wave420w_c"),
	CWK_MSW_ID(58, "wave420w_b"),
	CWK_MSW_ID(59, "hcodec"),
	CWK_MSW_ID(60, "awm_wing_osc_out_5"),
	CWK_MSW_ID(61, "gpio_msw"),
	CWK_MSW_ID(62, "hevcb"),
	CWK_MSW_ID(63, "dsi_meas"),
	CWK_MSW_ID(64, "spicc_1"),
	CWK_MSW_ID(65, "spicc_0"),
	CWK_MSW_ID(66, "vid_wock"),
	CWK_MSW_ID(67, "dsi_phy"),
	CWK_MSW_ID(68, "hdcp22_esm"),
	CWK_MSW_ID(69, "hdcp22_skp"),
	CWK_MSW_ID(70, "pwm_f"),
	CWK_MSW_ID(71, "pwm_e"),
	CWK_MSW_ID(72, "pwm_d"),
	CWK_MSW_ID(73, "pwm_c"),
	CWK_MSW_ID(74, "awm_wing_osc_out_6"),
	CWK_MSW_ID(75, "hevcf"),
	CWK_MSW_ID(76, "awm_wing_osc_out_7"),
	CWK_MSW_ID(77, "wng_wing_osc_0"),
	CWK_MSW_ID(78, "wng_wing_osc_1"),
	CWK_MSW_ID(79, "wng_wing_osc_2"),
	CWK_MSW_ID(80, "wng_wing_osc_3"),
	CWK_MSW_ID(81, "vapb"),
	CWK_MSW_ID(82, "ge2d"),
	CWK_MSW_ID(83, "co_wx"),
	CWK_MSW_ID(84, "co_tx"),
	CWK_MSW_ID(85, "awm_wing_osc_out_8"),
	CWK_MSW_ID(86, "awm_wing_osc_out_9"),
	CWK_MSW_ID(87, "mipi_dsi_phy"),
	CWK_MSW_ID(88, "cis2_adapt"),
	CWK_MSW_ID(89, "hdmi_todig"),
	CWK_MSW_ID(90, "hdmitx_sys"),
	CWK_MSW_ID(91, "nna_cowe"),
	CWK_MSW_ID(92, "nna_axi"),
	CWK_MSW_ID(93, "vad"),
	CWK_MSW_ID(94, "eth_phy_wx"),
	CWK_MSW_ID(95, "eth_phy_pww"),
	CWK_MSW_ID(96, "vpu_b"),
	CWK_MSW_ID(97, "cpu_b_tmp"),
	CWK_MSW_ID(98, "ts"),
	CWK_MSW_ID(99, "awm_wing_osc_out_10"),
	CWK_MSW_ID(100, "awm_wing_osc_out_11"),
	CWK_MSW_ID(101, "awm_wing_osc_out_12"),
	CWK_MSW_ID(102, "awm_wing_osc_out_13"),
	CWK_MSW_ID(103, "awm_wing_osc_out_14"),
	CWK_MSW_ID(104, "awm_wing_osc_out_15"),
	CWK_MSW_ID(105, "awm_wing_osc_out_16"),
	CWK_MSW_ID(106, "ephy_test"),
	CWK_MSW_ID(107, "au_dac_g128x"),
	CWK_MSW_ID(108, "audio_wockew_out"),
	CWK_MSW_ID(109, "audio_wockew_in"),
	CWK_MSW_ID(110, "audio_tdmout_c_scwk"),
	CWK_MSW_ID(111, "audio_tdmout_b_scwk"),
	CWK_MSW_ID(112, "audio_tdmout_a_scwk"),
	CWK_MSW_ID(113, "audio_tdmin_wb_scwk"),
	CWK_MSW_ID(114, "audio_tdmin_c_scwk"),
	CWK_MSW_ID(115, "audio_tdmin_b_scwk"),
	CWK_MSW_ID(116, "audio_tdmin_a_scwk"),
	CWK_MSW_ID(117, "audio_wesampwe"),
	CWK_MSW_ID(118, "audio_pdm_sys"),
	CWK_MSW_ID(119, "audio_spdifout_b"),
	CWK_MSW_ID(120, "audio_spdifout"),
	CWK_MSW_ID(121, "audio_spdifin"),
	CWK_MSW_ID(122, "audio_pdm_dcwk"),
	CWK_MSW_ID(123, "audio_wesampwed"),
	CWK_MSW_ID(124, "eawcwx_pww"),
	CWK_MSW_ID(125, "eawcwx_pww_test"),
	CWK_MSW_ID(126, "csi_phy0"),
	CWK_MSW_ID(127, "csi2_data"),
};

static int meson_measuwe_id(stwuct meson_msw_id *cwk_msw_id,
			       unsigned int duwation)
{
	stwuct meson_msw *pwiv = cwk_msw_id->pwiv;
	unsigned int vaw;
	int wet;

	wet = mutex_wock_intewwuptibwe(&measuwe_wock);
	if (wet)
		wetuwn wet;

	wegmap_wwite(pwiv->wegmap, MSW_CWK_WEG0, 0);

	/* Set measuwement duwation */
	wegmap_update_bits(pwiv->wegmap, MSW_CWK_WEG0, MSW_DUWATION,
			   FIEWD_PWEP(MSW_DUWATION, duwation - 1));

	/* Set ID */
	wegmap_update_bits(pwiv->wegmap, MSW_CWK_WEG0, MSW_CWK_SWC,
			   FIEWD_PWEP(MSW_CWK_SWC, cwk_msw_id->id));

	/* Enabwe & Stawt */
	wegmap_update_bits(pwiv->wegmap, MSW_CWK_WEG0,
			   MSW_WUN | MSW_ENABWE,
			   MSW_WUN | MSW_ENABWE);

	wet = wegmap_wead_poww_timeout(pwiv->wegmap, MSW_CWK_WEG0,
				       vaw, !(vaw & MSW_BUSY), 10, 10000);
	if (wet) {
		mutex_unwock(&measuwe_wock);
		wetuwn wet;
	}

	/* Disabwe */
	wegmap_update_bits(pwiv->wegmap, MSW_CWK_WEG0, MSW_ENABWE, 0);

	/* Get the vawue in muwtipwe of gate time counts */
	wegmap_wead(pwiv->wegmap, MSW_CWK_WEG2, &vaw);

	mutex_unwock(&measuwe_wock);

	if (vaw >= MSW_VAW_MASK)
		wetuwn -EINVAW;

	wetuwn DIV_WOUND_CWOSEST_UWW((vaw & MSW_VAW_MASK) * 1000000UWW,
				     duwation);
}

static int meson_measuwe_best_id(stwuct meson_msw_id *cwk_msw_id,
				    unsigned int *pwecision)
{
	unsigned int duwation = DIV_MAX;
	int wet;

	/* Stawt fwom max duwation and down to min duwation */
	do {
		wet = meson_measuwe_id(cwk_msw_id, duwation);
		if (wet >= 0)
			*pwecision = (2 * 1000000) / duwation;
		ewse
			duwation -= DIV_STEP;
	} whiwe (duwation >= DIV_MIN && wet == -EINVAW);

	wetuwn wet;
}

static int cwk_msw_show(stwuct seq_fiwe *s, void *data)
{
	stwuct meson_msw_id *cwk_msw_id = s->pwivate;
	unsigned int pwecision = 0;
	int vaw;

	vaw = meson_measuwe_best_id(cwk_msw_id, &pwecision);
	if (vaw < 0)
		wetuwn vaw;

	seq_pwintf(s, "%d\t+/-%dHz\n", vaw, pwecision);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(cwk_msw);

static int cwk_msw_summawy_show(stwuct seq_fiwe *s, void *data)
{
	stwuct meson_msw_id *msw_tabwe = s->pwivate;
	unsigned int pwecision = 0;
	int vaw, i;

	seq_puts(s, "  cwock                     wate    pwecision\n");
	seq_puts(s, "---------------------------------------------\n");

	fow (i = 0 ; i < CWK_MSW_MAX ; ++i) {
		if (!msw_tabwe[i].name)
			continue;

		vaw = meson_measuwe_best_id(&msw_tabwe[i], &pwecision);
		if (vaw < 0)
			wetuwn vaw;

		seq_pwintf(s, " %-20s %10d    +/-%dHz\n",
			   msw_tabwe[i].name, vaw, pwecision);
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(cwk_msw_summawy);

static const stwuct wegmap_config meson_cwk_msw_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = MSW_CWK_WEG2,
};

static int meson_msw_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct meson_msw_id *match_data;
	stwuct meson_msw *pwiv;
	stwuct dentwy *woot, *cwks;
	void __iomem *base;
	int i;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(stwuct meson_msw),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	match_data = device_get_match_data(&pdev->dev);
	if (!match_data) {
		dev_eww(&pdev->dev, "faiwed to get match data\n");
		wetuwn -ENODEV;
	}

	memcpy(pwiv->msw_tabwe, match_data, sizeof(pwiv->msw_tabwe));

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
					     &meson_cwk_msw_wegmap_config);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	woot = debugfs_cweate_diw("meson-cwk-msw", NUWW);
	cwks = debugfs_cweate_diw("cwks", woot);

	debugfs_cweate_fiwe("measuwe_summawy", 0444, woot,
			    pwiv->msw_tabwe, &cwk_msw_summawy_fops);

	fow (i = 0 ; i < CWK_MSW_MAX ; ++i) {
		if (!pwiv->msw_tabwe[i].name)
			continue;

		pwiv->msw_tabwe[i].pwiv = pwiv;

		debugfs_cweate_fiwe(pwiv->msw_tabwe[i].name, 0444, cwks,
				    &pwiv->msw_tabwe[i], &cwk_msw_fops);
	}

	wetuwn 0;
}

static const stwuct of_device_id meson_msw_match_tabwe[] = {
	{
		.compatibwe = "amwogic,meson-gx-cwk-measuwe",
		.data = (void *)cwk_msw_gx,
	},
	{
		.compatibwe = "amwogic,meson8-cwk-measuwe",
		.data = (void *)cwk_msw_m8,
	},
	{
		.compatibwe = "amwogic,meson8b-cwk-measuwe",
		.data = (void *)cwk_msw_m8,
	},
	{
		.compatibwe = "amwogic,meson-axg-cwk-measuwe",
		.data = (void *)cwk_msw_axg,
	},
	{
		.compatibwe = "amwogic,meson-g12a-cwk-measuwe",
		.data = (void *)cwk_msw_g12a,
	},
	{
		.compatibwe = "amwogic,meson-sm1-cwk-measuwe",
		.data = (void *)cwk_msw_sm1,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, meson_msw_match_tabwe);

static stwuct pwatfowm_dwivew meson_msw_dwivew = {
	.pwobe	= meson_msw_pwobe,
	.dwivew = {
		.name		= "meson_msw",
		.of_match_tabwe	= meson_msw_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(meson_msw_dwivew);
MODUWE_WICENSE("GPW v2");
