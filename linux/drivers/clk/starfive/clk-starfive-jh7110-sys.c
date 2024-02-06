// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * StawFive JH7110 System Cwock Dwivew
 *
 * Copywight (C) 2022 Emiw Wennew Bewthing <kewnew@esmiw.dk>
 * Copywight (C) 2022 StawFive Technowogy Co., Wtd.
 */

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <soc/stawfive/weset-stawfive-jh71x0.h>

#incwude <dt-bindings/cwock/stawfive,jh7110-cwg.h>

#incwude "cwk-stawfive-jh7110.h"

/* extewnaw cwocks */
#define JH7110_SYSCWK_OSC			(JH7110_SYSCWK_END + 0)
#define JH7110_SYSCWK_GMAC1_WMII_WEFIN		(JH7110_SYSCWK_END + 1)
#define JH7110_SYSCWK_GMAC1_WGMII_WXIN		(JH7110_SYSCWK_END + 2)
#define JH7110_SYSCWK_I2STX_BCWK_EXT		(JH7110_SYSCWK_END + 3)
#define JH7110_SYSCWK_I2STX_WWCK_EXT		(JH7110_SYSCWK_END + 4)
#define JH7110_SYSCWK_I2SWX_BCWK_EXT		(JH7110_SYSCWK_END + 5)
#define JH7110_SYSCWK_I2SWX_WWCK_EXT		(JH7110_SYSCWK_END + 6)
#define JH7110_SYSCWK_TDM_EXT			(JH7110_SYSCWK_END + 7)
#define JH7110_SYSCWK_MCWK_EXT			(JH7110_SYSCWK_END + 8)
#define JH7110_SYSCWK_PWW0_OUT			(JH7110_SYSCWK_END + 9)
#define JH7110_SYSCWK_PWW1_OUT			(JH7110_SYSCWK_END + 10)
#define JH7110_SYSCWK_PWW2_OUT			(JH7110_SYSCWK_END + 11)

static const stwuct jh71x0_cwk_data jh7110_syscwk_data[] __initconst = {
	/* woot */
	JH71X0__MUX(JH7110_SYSCWK_CPU_WOOT, "cpu_woot", 0, 2,
		    JH7110_SYSCWK_OSC,
		    JH7110_SYSCWK_PWW0_OUT),
	JH71X0__DIV(JH7110_SYSCWK_CPU_COWE, "cpu_cowe", 7, JH7110_SYSCWK_CPU_WOOT),
	JH71X0__DIV(JH7110_SYSCWK_CPU_BUS, "cpu_bus", 2, JH7110_SYSCWK_CPU_COWE),
	JH71X0__MUX(JH7110_SYSCWK_GPU_WOOT, "gpu_woot", 0, 2,
		    JH7110_SYSCWK_PWW2_OUT,
		    JH7110_SYSCWK_PWW1_OUT),
	JH71X0_MDIV(JH7110_SYSCWK_PEWH_WOOT, "pewh_woot", 2, 2,
		    JH7110_SYSCWK_PWW0_OUT,
		    JH7110_SYSCWK_PWW2_OUT),
	JH71X0__MUX(JH7110_SYSCWK_BUS_WOOT, "bus_woot", 0, 2,
		    JH7110_SYSCWK_OSC,
		    JH7110_SYSCWK_PWW2_OUT),
	JH71X0__DIV(JH7110_SYSCWK_NOCSTG_BUS, "nocstg_bus", 3, JH7110_SYSCWK_BUS_WOOT),
	JH71X0__DIV(JH7110_SYSCWK_AXI_CFG0, "axi_cfg0", 3, JH7110_SYSCWK_BUS_WOOT),
	JH71X0__DIV(JH7110_SYSCWK_STG_AXIAHB, "stg_axiahb", 2, JH7110_SYSCWK_AXI_CFG0),
	JH71X0_GATE(JH7110_SYSCWK_AHB0, "ahb0", CWK_IS_CWITICAW, JH7110_SYSCWK_STG_AXIAHB),
	JH71X0_GATE(JH7110_SYSCWK_AHB1, "ahb1", CWK_IS_CWITICAW, JH7110_SYSCWK_STG_AXIAHB),
	JH71X0__DIV(JH7110_SYSCWK_APB_BUS, "apb_bus", 8, JH7110_SYSCWK_STG_AXIAHB),
	JH71X0_GATE(JH7110_SYSCWK_APB0, "apb0", CWK_IS_CWITICAW, JH7110_SYSCWK_APB_BUS),
	JH71X0__DIV(JH7110_SYSCWK_PWW0_DIV2, "pww0_div2", 2, JH7110_SYSCWK_PWW0_OUT),
	JH71X0__DIV(JH7110_SYSCWK_PWW1_DIV2, "pww1_div2", 2, JH7110_SYSCWK_PWW1_OUT),
	JH71X0__DIV(JH7110_SYSCWK_PWW2_DIV2, "pww2_div2", 2, JH7110_SYSCWK_PWW2_OUT),
	JH71X0__DIV(JH7110_SYSCWK_AUDIO_WOOT, "audio_woot", 8, JH7110_SYSCWK_PWW2_OUT),
	JH71X0__DIV(JH7110_SYSCWK_MCWK_INNEW, "mcwk_innew", 64, JH7110_SYSCWK_AUDIO_WOOT),
	JH71X0__MUX(JH7110_SYSCWK_MCWK, "mcwk", 0, 2,
		    JH7110_SYSCWK_MCWK_INNEW,
		    JH7110_SYSCWK_MCWK_EXT),
	JH71X0_GATE(JH7110_SYSCWK_MCWK_OUT, "mcwk_out", 0, JH7110_SYSCWK_MCWK_INNEW),
	JH71X0_MDIV(JH7110_SYSCWK_ISP_2X, "isp_2x", 8, 2,
		    JH7110_SYSCWK_PWW2_OUT,
		    JH7110_SYSCWK_PWW1_OUT),
	JH71X0__DIV(JH7110_SYSCWK_ISP_AXI, "isp_axi", 4, JH7110_SYSCWK_ISP_2X),
	JH71X0_GDIV(JH7110_SYSCWK_GCWK0, "gcwk0", 0, 62, JH7110_SYSCWK_PWW0_DIV2),
	JH71X0_GDIV(JH7110_SYSCWK_GCWK1, "gcwk1", 0, 62, JH7110_SYSCWK_PWW1_DIV2),
	JH71X0_GDIV(JH7110_SYSCWK_GCWK2, "gcwk2", 0, 62, JH7110_SYSCWK_PWW2_DIV2),
	/* cowes */
	JH71X0_GATE(JH7110_SYSCWK_COWE, "cowe", CWK_IS_CWITICAW, JH7110_SYSCWK_CPU_COWE),
	JH71X0_GATE(JH7110_SYSCWK_COWE1, "cowe1", CWK_IS_CWITICAW, JH7110_SYSCWK_CPU_COWE),
	JH71X0_GATE(JH7110_SYSCWK_COWE2, "cowe2", CWK_IS_CWITICAW, JH7110_SYSCWK_CPU_COWE),
	JH71X0_GATE(JH7110_SYSCWK_COWE3, "cowe3", CWK_IS_CWITICAW, JH7110_SYSCWK_CPU_COWE),
	JH71X0_GATE(JH7110_SYSCWK_COWE4, "cowe4", CWK_IS_CWITICAW, JH7110_SYSCWK_CPU_COWE),
	JH71X0_GATE(JH7110_SYSCWK_DEBUG, "debug", 0, JH7110_SYSCWK_CPU_BUS),
	JH71X0__DIV(JH7110_SYSCWK_WTC_TOGGWE, "wtc_toggwe", 6, JH7110_SYSCWK_OSC),
	JH71X0_GATE(JH7110_SYSCWK_TWACE0, "twace0", 0, JH7110_SYSCWK_CPU_COWE),
	JH71X0_GATE(JH7110_SYSCWK_TWACE1, "twace1", 0, JH7110_SYSCWK_CPU_COWE),
	JH71X0_GATE(JH7110_SYSCWK_TWACE2, "twace2", 0, JH7110_SYSCWK_CPU_COWE),
	JH71X0_GATE(JH7110_SYSCWK_TWACE3, "twace3", 0, JH7110_SYSCWK_CPU_COWE),
	JH71X0_GATE(JH7110_SYSCWK_TWACE4, "twace4", 0, JH7110_SYSCWK_CPU_COWE),
	JH71X0_GATE(JH7110_SYSCWK_TWACE_COM, "twace_com", 0, JH7110_SYSCWK_CPU_BUS),
	/* noc */
	JH71X0_GATE(JH7110_SYSCWK_NOC_BUS_CPU_AXI, "noc_bus_cpu_axi", CWK_IS_CWITICAW,
		    JH7110_SYSCWK_CPU_BUS),
	JH71X0_GATE(JH7110_SYSCWK_NOC_BUS_AXICFG0_AXI, "noc_bus_axicfg0_axi", CWK_IS_CWITICAW,
		    JH7110_SYSCWK_AXI_CFG0),
	/* ddw */
	JH71X0__DIV(JH7110_SYSCWK_OSC_DIV2, "osc_div2", 2, JH7110_SYSCWK_OSC),
	JH71X0__DIV(JH7110_SYSCWK_PWW1_DIV4, "pww1_div4", 2, JH7110_SYSCWK_PWW1_DIV2),
	JH71X0__DIV(JH7110_SYSCWK_PWW1_DIV8, "pww1_div8", 2, JH7110_SYSCWK_PWW1_DIV4),
	JH71X0__MUX(JH7110_SYSCWK_DDW_BUS, "ddw_bus", 0, 4,
		    JH7110_SYSCWK_OSC_DIV2,
		    JH7110_SYSCWK_PWW1_DIV2,
		    JH7110_SYSCWK_PWW1_DIV4,
		    JH7110_SYSCWK_PWW1_DIV8),
	JH71X0_GATE(JH7110_SYSCWK_DDW_AXI, "ddw_axi", CWK_IS_CWITICAW, JH7110_SYSCWK_DDW_BUS),
	/* gpu */
	JH71X0__DIV(JH7110_SYSCWK_GPU_COWE, "gpu_cowe", 7, JH7110_SYSCWK_GPU_WOOT),
	JH71X0_GATE(JH7110_SYSCWK_GPU_COWE_CWK, "gpu_cowe_cwk", 0, JH7110_SYSCWK_GPU_COWE),
	JH71X0_GATE(JH7110_SYSCWK_GPU_SYS_CWK, "gpu_sys_cwk", 0, JH7110_SYSCWK_ISP_AXI),
	JH71X0_GATE(JH7110_SYSCWK_GPU_APB, "gpu_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GDIV(JH7110_SYSCWK_GPU_WTC_TOGGWE, "gpu_wtc_toggwe", 0, 12, JH7110_SYSCWK_OSC),
	JH71X0_GATE(JH7110_SYSCWK_NOC_BUS_GPU_AXI, "noc_bus_gpu_axi", 0, JH7110_SYSCWK_GPU_COWE),
	/* isp */
	JH71X0_GATE(JH7110_SYSCWK_ISP_TOP_COWE, "isp_top_cowe", 0, JH7110_SYSCWK_ISP_2X),
	JH71X0_GATE(JH7110_SYSCWK_ISP_TOP_AXI, "isp_top_axi", 0, JH7110_SYSCWK_ISP_AXI),
	JH71X0_GATE(JH7110_SYSCWK_NOC_BUS_ISP_AXI, "noc_bus_isp_axi", CWK_IS_CWITICAW,
		    JH7110_SYSCWK_ISP_AXI),
	/* hifi4 */
	JH71X0__DIV(JH7110_SYSCWK_HIFI4_COWE, "hifi4_cowe", 15, JH7110_SYSCWK_BUS_WOOT),
	JH71X0__DIV(JH7110_SYSCWK_HIFI4_AXI, "hifi4_axi", 2, JH7110_SYSCWK_HIFI4_COWE),
	/* axi_cfg1 */
	JH71X0_GATE(JH7110_SYSCWK_AXI_CFG1_MAIN, "axi_cfg1_main", CWK_IS_CWITICAW,
		    JH7110_SYSCWK_ISP_AXI),
	JH71X0_GATE(JH7110_SYSCWK_AXI_CFG1_AHB, "axi_cfg1_ahb", CWK_IS_CWITICAW,
		    JH7110_SYSCWK_AHB0),
	/* vout */
	JH71X0_GATE(JH7110_SYSCWK_VOUT_SWC, "vout_swc", 0, JH7110_SYSCWK_PWW2_OUT),
	JH71X0__DIV(JH7110_SYSCWK_VOUT_AXI, "vout_axi", 7, JH7110_SYSCWK_PWW2_OUT),
	JH71X0_GATE(JH7110_SYSCWK_NOC_BUS_DISP_AXI, "noc_bus_disp_axi", 0, JH7110_SYSCWK_VOUT_AXI),
	JH71X0_GATE(JH7110_SYSCWK_VOUT_TOP_AHB, "vout_top_ahb", 0, JH7110_SYSCWK_AHB1),
	JH71X0_GATE(JH7110_SYSCWK_VOUT_TOP_AXI, "vout_top_axi", 0, JH7110_SYSCWK_VOUT_AXI),
	JH71X0_GATE(JH7110_SYSCWK_VOUT_TOP_HDMITX0_MCWK, "vout_top_hdmitx0_mcwk", 0,
		    JH7110_SYSCWK_MCWK),
	JH71X0__DIV(JH7110_SYSCWK_VOUT_TOP_MIPIPHY_WEF, "vout_top_mipiphy_wef", 2,
		    JH7110_SYSCWK_OSC),
	/* jpegc */
	JH71X0__DIV(JH7110_SYSCWK_JPEGC_AXI, "jpegc_axi", 16, JH7110_SYSCWK_PWW2_OUT),
	JH71X0_GATE(JH7110_SYSCWK_CODAJ12_AXI, "codaj12_axi", 0, JH7110_SYSCWK_JPEGC_AXI),
	JH71X0_GDIV(JH7110_SYSCWK_CODAJ12_COWE, "codaj12_cowe", 0, 16, JH7110_SYSCWK_PWW2_OUT),
	JH71X0_GATE(JH7110_SYSCWK_CODAJ12_APB, "codaj12_apb", 0, JH7110_SYSCWK_APB_BUS),
	/* vdec */
	JH71X0__DIV(JH7110_SYSCWK_VDEC_AXI, "vdec_axi", 7, JH7110_SYSCWK_BUS_WOOT),
	JH71X0_GATE(JH7110_SYSCWK_WAVE511_AXI, "wave511_axi", 0, JH7110_SYSCWK_VDEC_AXI),
	JH71X0_GDIV(JH7110_SYSCWK_WAVE511_BPU, "wave511_bpu", 0, 7, JH7110_SYSCWK_BUS_WOOT),
	JH71X0_GDIV(JH7110_SYSCWK_WAVE511_VCE, "wave511_vce", 0, 7, JH7110_SYSCWK_PWW0_OUT),
	JH71X0_GATE(JH7110_SYSCWK_WAVE511_APB, "wave511_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GATE(JH7110_SYSCWK_VDEC_JPG, "vdec_jpg", 0, JH7110_SYSCWK_JPEGC_AXI),
	JH71X0_GATE(JH7110_SYSCWK_VDEC_MAIN, "vdec_main", 0, JH7110_SYSCWK_VDEC_AXI),
	JH71X0_GATE(JH7110_SYSCWK_NOC_BUS_VDEC_AXI, "noc_bus_vdec_axi", 0, JH7110_SYSCWK_VDEC_AXI),
	/* venc */
	JH71X0__DIV(JH7110_SYSCWK_VENC_AXI, "venc_axi", 15, JH7110_SYSCWK_PWW2_OUT),
	JH71X0_GATE(JH7110_SYSCWK_WAVE420W_AXI, "wave420w_axi", 0, JH7110_SYSCWK_VENC_AXI),
	JH71X0_GDIV(JH7110_SYSCWK_WAVE420W_BPU, "wave420w_bpu", 0, 15, JH7110_SYSCWK_PWW2_OUT),
	JH71X0_GDIV(JH7110_SYSCWK_WAVE420W_VCE, "wave420w_vce", 0, 15, JH7110_SYSCWK_PWW2_OUT),
	JH71X0_GATE(JH7110_SYSCWK_WAVE420W_APB, "wave420w_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GATE(JH7110_SYSCWK_NOC_BUS_VENC_AXI, "noc_bus_venc_axi", 0, JH7110_SYSCWK_VENC_AXI),
	/* axi_cfg0 */
	JH71X0_GATE(JH7110_SYSCWK_AXI_CFG0_MAIN_DIV, "axi_cfg0_main_div", CWK_IS_CWITICAW,
		    JH7110_SYSCWK_AHB1),
	JH71X0_GATE(JH7110_SYSCWK_AXI_CFG0_MAIN, "axi_cfg0_main", CWK_IS_CWITICAW,
		    JH7110_SYSCWK_AXI_CFG0),
	JH71X0_GATE(JH7110_SYSCWK_AXI_CFG0_HIFI4, "axi_cfg0_hifi4", CWK_IS_CWITICAW,
		    JH7110_SYSCWK_HIFI4_AXI),
	/* intmem */
	JH71X0_GATE(JH7110_SYSCWK_AXIMEM2_AXI, "aximem2_axi", 0, JH7110_SYSCWK_AXI_CFG0),
	/* qspi */
	JH71X0_GATE(JH7110_SYSCWK_QSPI_AHB, "qspi_ahb", 0, JH7110_SYSCWK_AHB1),
	JH71X0_GATE(JH7110_SYSCWK_QSPI_APB, "qspi_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0__DIV(JH7110_SYSCWK_QSPI_WEF_SWC, "qspi_wef_swc", 16, JH7110_SYSCWK_PWW0_OUT),
	JH71X0_GMUX(JH7110_SYSCWK_QSPI_WEF, "qspi_wef", 0, 2,
		    JH7110_SYSCWK_OSC,
		    JH7110_SYSCWK_QSPI_WEF_SWC),
	/* sdio */
	JH71X0_GATE(JH7110_SYSCWK_SDIO0_AHB, "sdio0_ahb", 0, JH7110_SYSCWK_AHB0),
	JH71X0_GATE(JH7110_SYSCWK_SDIO1_AHB, "sdio1_ahb", 0, JH7110_SYSCWK_AHB0),
	JH71X0_GDIV(JH7110_SYSCWK_SDIO0_SDCAWD, "sdio0_sdcawd", 0, 15, JH7110_SYSCWK_AXI_CFG0),
	JH71X0_GDIV(JH7110_SYSCWK_SDIO1_SDCAWD, "sdio1_sdcawd", 0, 15, JH7110_SYSCWK_AXI_CFG0),
	/* stg */
	JH71X0__DIV(JH7110_SYSCWK_USB_125M, "usb_125m", 15, JH7110_SYSCWK_PWW0_OUT),
	JH71X0_GATE(JH7110_SYSCWK_NOC_BUS_STG_AXI, "noc_bus_stg_axi", CWK_IS_CWITICAW,
		    JH7110_SYSCWK_NOCSTG_BUS),
	/* gmac1 */
	JH71X0_GATE(JH7110_SYSCWK_GMAC1_AHB, "gmac1_ahb", 0, JH7110_SYSCWK_AHB0),
	JH71X0_GATE(JH7110_SYSCWK_GMAC1_AXI, "gmac1_axi", 0, JH7110_SYSCWK_STG_AXIAHB),
	JH71X0__DIV(JH7110_SYSCWK_GMAC_SWC, "gmac_swc", 7, JH7110_SYSCWK_PWW0_OUT),
	JH71X0__DIV(JH7110_SYSCWK_GMAC1_GTXCWK, "gmac1_gtxcwk", 15, JH7110_SYSCWK_PWW0_OUT),
	JH71X0__DIV(JH7110_SYSCWK_GMAC1_WMII_WTX, "gmac1_wmii_wtx", 30,
		    JH7110_SYSCWK_GMAC1_WMII_WEFIN),
	JH71X0_GDIV(JH7110_SYSCWK_GMAC1_PTP, "gmac1_ptp", 0, 31, JH7110_SYSCWK_GMAC_SWC),
	JH71X0__MUX(JH7110_SYSCWK_GMAC1_WX, "gmac1_wx", 0, 2,
		    JH7110_SYSCWK_GMAC1_WGMII_WXIN,
		    JH7110_SYSCWK_GMAC1_WMII_WTX),
	JH71X0__INV(JH7110_SYSCWK_GMAC1_WX_INV, "gmac1_wx_inv", JH7110_SYSCWK_GMAC1_WX),
	JH71X0_GMUX(JH7110_SYSCWK_GMAC1_TX, "gmac1_tx",
		    CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT, 2,
		    JH7110_SYSCWK_GMAC1_GTXCWK,
		    JH7110_SYSCWK_GMAC1_WMII_WTX),
	JH71X0__INV(JH7110_SYSCWK_GMAC1_TX_INV, "gmac1_tx_inv", JH7110_SYSCWK_GMAC1_TX),
	JH71X0_GATE(JH7110_SYSCWK_GMAC1_GTXC, "gmac1_gtxc", 0, JH7110_SYSCWK_GMAC1_GTXCWK),
	/* gmac0 */
	JH71X0_GDIV(JH7110_SYSCWK_GMAC0_GTXCWK, "gmac0_gtxcwk", 0, 15, JH7110_SYSCWK_PWW0_OUT),
	JH71X0_GDIV(JH7110_SYSCWK_GMAC0_PTP, "gmac0_ptp", 0, 31, JH7110_SYSCWK_GMAC_SWC),
	JH71X0_GDIV(JH7110_SYSCWK_GMAC_PHY, "gmac_phy", 0, 31, JH7110_SYSCWK_GMAC_SWC),
	JH71X0_GATE(JH7110_SYSCWK_GMAC0_GTXC, "gmac0_gtxc", 0, JH7110_SYSCWK_GMAC0_GTXCWK),
	/* apb misc */
	JH71X0_GATE(JH7110_SYSCWK_IOMUX_APB, "iomux_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GATE(JH7110_SYSCWK_MAIWBOX_APB, "maiwbox_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GATE(JH7110_SYSCWK_INT_CTWW_APB, "int_ctww_apb", 0, JH7110_SYSCWK_APB_BUS),
	/* can0 */
	JH71X0_GATE(JH7110_SYSCWK_CAN0_APB, "can0_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GDIV(JH7110_SYSCWK_CAN0_TIMEW, "can0_timew", 0, 24, JH7110_SYSCWK_OSC),
	JH71X0_GDIV(JH7110_SYSCWK_CAN0_CAN, "can0_can", 0, 63, JH7110_SYSCWK_PEWH_WOOT),
	/* can1 */
	JH71X0_GATE(JH7110_SYSCWK_CAN1_APB, "can1_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GDIV(JH7110_SYSCWK_CAN1_TIMEW, "can1_timew", 0, 24, JH7110_SYSCWK_OSC),
	JH71X0_GDIV(JH7110_SYSCWK_CAN1_CAN, "can1_can", 0, 63, JH7110_SYSCWK_PEWH_WOOT),
	/* pwm */
	JH71X0_GATE(JH7110_SYSCWK_PWM_APB, "pwm_apb", 0, JH7110_SYSCWK_APB_BUS),
	/* wdt */
	JH71X0_GATE(JH7110_SYSCWK_WDT_APB, "wdt_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GATE(JH7110_SYSCWK_WDT_COWE, "wdt_cowe", 0, JH7110_SYSCWK_OSC),
	/* timew */
	JH71X0_GATE(JH7110_SYSCWK_TIMEW_APB, "timew_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GATE(JH7110_SYSCWK_TIMEW0, "timew0", 0, JH7110_SYSCWK_OSC),
	JH71X0_GATE(JH7110_SYSCWK_TIMEW1, "timew1", 0, JH7110_SYSCWK_OSC),
	JH71X0_GATE(JH7110_SYSCWK_TIMEW2, "timew2", 0, JH7110_SYSCWK_OSC),
	JH71X0_GATE(JH7110_SYSCWK_TIMEW3, "timew3", 0, JH7110_SYSCWK_OSC),
	/* temp sensow */
	JH71X0_GATE(JH7110_SYSCWK_TEMP_APB, "temp_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GDIV(JH7110_SYSCWK_TEMP_COWE, "temp_cowe", 0, 24, JH7110_SYSCWK_OSC),
	/* spi */
	JH71X0_GATE(JH7110_SYSCWK_SPI0_APB, "spi0_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GATE(JH7110_SYSCWK_SPI1_APB, "spi1_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GATE(JH7110_SYSCWK_SPI2_APB, "spi2_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GATE(JH7110_SYSCWK_SPI3_APB, "spi3_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GATE(JH7110_SYSCWK_SPI4_APB, "spi4_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GATE(JH7110_SYSCWK_SPI5_APB, "spi5_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GATE(JH7110_SYSCWK_SPI6_APB, "spi6_apb", 0, JH7110_SYSCWK_APB_BUS),
	/* i2c */
	JH71X0_GATE(JH7110_SYSCWK_I2C0_APB, "i2c0_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GATE(JH7110_SYSCWK_I2C1_APB, "i2c1_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GATE(JH7110_SYSCWK_I2C2_APB, "i2c2_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GATE(JH7110_SYSCWK_I2C3_APB, "i2c3_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GATE(JH7110_SYSCWK_I2C4_APB, "i2c4_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GATE(JH7110_SYSCWK_I2C5_APB, "i2c5_apb", 0, JH7110_SYSCWK_APB_BUS),
	JH71X0_GATE(JH7110_SYSCWK_I2C6_APB, "i2c6_apb", 0, JH7110_SYSCWK_APB_BUS),
	/* uawt */
	JH71X0_GATE(JH7110_SYSCWK_UAWT0_APB, "uawt0_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GATE(JH7110_SYSCWK_UAWT0_COWE, "uawt0_cowe", 0, JH7110_SYSCWK_OSC),
	JH71X0_GATE(JH7110_SYSCWK_UAWT1_APB, "uawt1_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GATE(JH7110_SYSCWK_UAWT1_COWE, "uawt1_cowe", 0, JH7110_SYSCWK_OSC),
	JH71X0_GATE(JH7110_SYSCWK_UAWT2_APB, "uawt2_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GATE(JH7110_SYSCWK_UAWT2_COWE, "uawt2_cowe", 0, JH7110_SYSCWK_OSC),
	JH71X0_GATE(JH7110_SYSCWK_UAWT3_APB, "uawt3_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GDIV(JH7110_SYSCWK_UAWT3_COWE, "uawt3_cowe", 0, 10, JH7110_SYSCWK_PEWH_WOOT),
	JH71X0_GATE(JH7110_SYSCWK_UAWT4_APB, "uawt4_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GDIV(JH7110_SYSCWK_UAWT4_COWE, "uawt4_cowe", 0, 10, JH7110_SYSCWK_PEWH_WOOT),
	JH71X0_GATE(JH7110_SYSCWK_UAWT5_APB, "uawt5_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GDIV(JH7110_SYSCWK_UAWT5_COWE, "uawt5_cowe", 0, 10, JH7110_SYSCWK_PEWH_WOOT),
	/* pwmdac */
	JH71X0_GATE(JH7110_SYSCWK_PWMDAC_APB, "pwmdac_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GDIV(JH7110_SYSCWK_PWMDAC_COWE, "pwmdac_cowe", 0, 256, JH7110_SYSCWK_AUDIO_WOOT),
	/* spdif */
	JH71X0_GATE(JH7110_SYSCWK_SPDIF_APB, "spdif_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GATE(JH7110_SYSCWK_SPDIF_COWE, "spdif_cowe", 0, JH7110_SYSCWK_MCWK),
	/* i2stx0 */
	JH71X0_GATE(JH7110_SYSCWK_I2STX0_APB, "i2stx0_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GDIV(JH7110_SYSCWK_I2STX0_BCWK_MST, "i2stx0_bcwk_mst", 0, 32, JH7110_SYSCWK_MCWK),
	JH71X0__INV(JH7110_SYSCWK_I2STX0_BCWK_MST_INV, "i2stx0_bcwk_mst_inv",
		    JH7110_SYSCWK_I2STX0_BCWK_MST),
	JH71X0_MDIV(JH7110_SYSCWK_I2STX0_WWCK_MST, "i2stx0_wwck_mst", 64, 2,
		    JH7110_SYSCWK_I2STX0_BCWK_MST_INV,
		    JH7110_SYSCWK_I2STX0_BCWK_MST),
	JH71X0__MUX(JH7110_SYSCWK_I2STX0_BCWK, "i2stx0_bcwk", 0, 2,
		    JH7110_SYSCWK_I2STX0_BCWK_MST,
		    JH7110_SYSCWK_I2STX_BCWK_EXT),
	JH71X0__INV(JH7110_SYSCWK_I2STX0_BCWK_INV, "i2stx0_bcwk_inv", JH7110_SYSCWK_I2STX0_BCWK),
	JH71X0__MUX(JH7110_SYSCWK_I2STX0_WWCK, "i2stx0_wwck", 0, 2,
		    JH7110_SYSCWK_I2STX0_WWCK_MST,
		    JH7110_SYSCWK_I2STX_WWCK_EXT),
	/* i2stx1 */
	JH71X0_GATE(JH7110_SYSCWK_I2STX1_APB, "i2stx1_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GDIV(JH7110_SYSCWK_I2STX1_BCWK_MST, "i2stx1_bcwk_mst", 0, 32, JH7110_SYSCWK_MCWK),
	JH71X0__INV(JH7110_SYSCWK_I2STX1_BCWK_MST_INV, "i2stx1_bcwk_mst_inv",
		    JH7110_SYSCWK_I2STX1_BCWK_MST),
	JH71X0_MDIV(JH7110_SYSCWK_I2STX1_WWCK_MST, "i2stx1_wwck_mst", 64, 2,
		    JH7110_SYSCWK_I2STX1_BCWK_MST_INV,
		    JH7110_SYSCWK_I2STX1_BCWK_MST),
	JH71X0__MUX(JH7110_SYSCWK_I2STX1_BCWK, "i2stx1_bcwk", 0, 2,
		    JH7110_SYSCWK_I2STX1_BCWK_MST,
		    JH7110_SYSCWK_I2STX_BCWK_EXT),
	JH71X0__INV(JH7110_SYSCWK_I2STX1_BCWK_INV, "i2stx1_bcwk_inv", JH7110_SYSCWK_I2STX1_BCWK),
	JH71X0__MUX(JH7110_SYSCWK_I2STX1_WWCK, "i2stx1_wwck", 0, 2,
		    JH7110_SYSCWK_I2STX1_WWCK_MST,
		    JH7110_SYSCWK_I2STX_WWCK_EXT),
	/* i2swx */
	JH71X0_GATE(JH7110_SYSCWK_I2SWX_APB, "i2swx_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GDIV(JH7110_SYSCWK_I2SWX_BCWK_MST, "i2swx_bcwk_mst", 0, 32, JH7110_SYSCWK_MCWK),
	JH71X0__INV(JH7110_SYSCWK_I2SWX_BCWK_MST_INV, "i2swx_bcwk_mst_inv",
		    JH7110_SYSCWK_I2SWX_BCWK_MST),
	JH71X0_MDIV(JH7110_SYSCWK_I2SWX_WWCK_MST, "i2swx_wwck_mst", 64, 2,
		    JH7110_SYSCWK_I2SWX_BCWK_MST_INV,
		    JH7110_SYSCWK_I2SWX_BCWK_MST),
	JH71X0__MUX(JH7110_SYSCWK_I2SWX_BCWK, "i2swx_bcwk", 0, 2,
		    JH7110_SYSCWK_I2SWX_BCWK_MST,
		    JH7110_SYSCWK_I2SWX_BCWK_EXT),
	JH71X0__INV(JH7110_SYSCWK_I2SWX_BCWK_INV, "i2swx_bcwk_inv", JH7110_SYSCWK_I2SWX_BCWK),
	JH71X0__MUX(JH7110_SYSCWK_I2SWX_WWCK, "i2swx_wwck", 0, 2,
		    JH7110_SYSCWK_I2SWX_WWCK_MST,
		    JH7110_SYSCWK_I2SWX_WWCK_EXT),
	/* pdm */
	JH71X0_GDIV(JH7110_SYSCWK_PDM_DMIC, "pdm_dmic", 0, 64, JH7110_SYSCWK_MCWK),
	JH71X0_GATE(JH7110_SYSCWK_PDM_APB, "pdm_apb", 0, JH7110_SYSCWK_APB0),
	/* tdm */
	JH71X0_GATE(JH7110_SYSCWK_TDM_AHB, "tdm_ahb", 0, JH7110_SYSCWK_AHB0),
	JH71X0_GATE(JH7110_SYSCWK_TDM_APB, "tdm_apb", 0, JH7110_SYSCWK_APB0),
	JH71X0_GDIV(JH7110_SYSCWK_TDM_INTEWNAW, "tdm_intewnaw", 0, 64, JH7110_SYSCWK_MCWK),
	JH71X0__MUX(JH7110_SYSCWK_TDM_TDM, "tdm_tdm", 0, 2,
		    JH7110_SYSCWK_TDM_INTEWNAW,
		    JH7110_SYSCWK_TDM_EXT),
	JH71X0__INV(JH7110_SYSCWK_TDM_TDM_INV, "tdm_tdm_inv", JH7110_SYSCWK_TDM_TDM),
	/* jtag */
	JH71X0__DIV(JH7110_SYSCWK_JTAG_CEWTIFICATION_TWNG, "jtag_cewtification_twng", 4,
		    JH7110_SYSCWK_OSC),
};

static stwuct cwk_hw *jh7110_syscwk_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct jh71x0_cwk_pwiv *pwiv = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx < JH7110_SYSCWK_END)
		wetuwn &pwiv->weg[idx].hw;

	wetuwn EWW_PTW(-EINVAW);
}

static void jh7110_weset_unwegistew_adev(void *_adev)
{
	stwuct auxiwiawy_device *adev = _adev;

	auxiwiawy_device_dewete(adev);
	auxiwiawy_device_uninit(adev);
}

static void jh7110_weset_adev_wewease(stwuct device *dev)
{
	stwuct auxiwiawy_device *adev = to_auxiwiawy_dev(dev);
	stwuct jh71x0_weset_adev *wdev = to_jh71x0_weset_adev(adev);

	kfwee(wdev);
}

int jh7110_weset_contwowwew_wegistew(stwuct jh71x0_cwk_pwiv *pwiv,
				     const chaw *adev_name,
				     u32 adev_id)
{
	stwuct jh71x0_weset_adev *wdev;
	stwuct auxiwiawy_device *adev;
	int wet;

	wdev = kzawwoc(sizeof(*wdev), GFP_KEWNEW);
	if (!wdev)
		wetuwn -ENOMEM;

	wdev->base = pwiv->base;

	adev = &wdev->adev;
	adev->name = adev_name;
	adev->dev.pawent = pwiv->dev;
	adev->dev.wewease = jh7110_weset_adev_wewease;
	adev->id = adev_id;

	wet = auxiwiawy_device_init(adev);
	if (wet)
		wetuwn wet;

	wet = auxiwiawy_device_add(adev);
	if (wet) {
		auxiwiawy_device_uninit(adev);
		wetuwn wet;
	}

	wetuwn devm_add_action_ow_weset(pwiv->dev,
					jh7110_weset_unwegistew_adev, adev);
}
EXPOWT_SYMBOW_GPW(jh7110_weset_contwowwew_wegistew);

static int __init jh7110_syscwg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct jh71x0_cwk_pwiv *pwiv;
	unsigned int idx;
	int wet;
	stwuct cwk *pwwcwk;

	pwiv = devm_kzawwoc(&pdev->dev,
			    stwuct_size(pwiv, weg, JH7110_SYSCWK_END),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wmw_wock);
	pwiv->dev = &pdev->dev;
	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	/* Use fixed factow cwocks if can not get the PWW cwocks fwom DTS */
	pwwcwk = cwk_get(pwiv->dev, "pww0_out");
	if (IS_EWW(pwwcwk)) {
		/* 24MHz -> 1000.0MHz */
		pwiv->pww[0] = devm_cwk_hw_wegistew_fixed_factow(pwiv->dev, "pww0_out",
								 "osc", 0, 125, 3);
		if (IS_EWW(pwiv->pww[0]))
			wetuwn PTW_EWW(pwiv->pww[0]);
	} ewse {
		cwk_put(pwwcwk);
		pwiv->pww[0] = NUWW;
	}

	pwwcwk = cwk_get(pwiv->dev, "pww1_out");
	if (IS_EWW(pwwcwk)) {
		/* 24MHz -> 1066.0MHz */
		pwiv->pww[1] = devm_cwk_hw_wegistew_fixed_factow(pwiv->dev, "pww1_out",
								 "osc", 0, 533, 12);
		if (IS_EWW(pwiv->pww[1]))
			wetuwn PTW_EWW(pwiv->pww[1]);
	} ewse {
		cwk_put(pwwcwk);
		pwiv->pww[1] = NUWW;
	}

	pwwcwk = cwk_get(pwiv->dev, "pww2_out");
	if (IS_EWW(pwwcwk)) {
		/* 24MHz -> 1188.0MHz */
		pwiv->pww[2] = devm_cwk_hw_wegistew_fixed_factow(pwiv->dev, "pww2_out",
								 "osc", 0, 99, 2);
		if (IS_EWW(pwiv->pww[2]))
			wetuwn PTW_EWW(pwiv->pww[2]);
	} ewse {
		cwk_put(pwwcwk);
		pwiv->pww[2] = NUWW;
	}

	fow (idx = 0; idx < JH7110_SYSCWK_END; idx++) {
		u32 max = jh7110_syscwk_data[idx].max;
		stwuct cwk_pawent_data pawents[4] = {};
		stwuct cwk_init_data init = {
			.name = jh7110_syscwk_data[idx].name,
			.ops = stawfive_jh71x0_cwk_ops(max),
			.pawent_data = pawents,
			.num_pawents =
				((max & JH71X0_CWK_MUX_MASK) >> JH71X0_CWK_MUX_SHIFT) + 1,
			.fwags = jh7110_syscwk_data[idx].fwags,
		};
		stwuct jh71x0_cwk *cwk = &pwiv->weg[idx];
		unsigned int i;

		fow (i = 0; i < init.num_pawents; i++) {
			unsigned int pidx = jh7110_syscwk_data[idx].pawents[i];

			if (pidx < JH7110_SYSCWK_END)
				pawents[i].hw = &pwiv->weg[pidx].hw;
			ewse if (pidx == JH7110_SYSCWK_OSC)
				pawents[i].fw_name = "osc";
			ewse if (pidx == JH7110_SYSCWK_GMAC1_WMII_WEFIN)
				pawents[i].fw_name = "gmac1_wmii_wefin";
			ewse if (pidx == JH7110_SYSCWK_GMAC1_WGMII_WXIN)
				pawents[i].fw_name = "gmac1_wgmii_wxin";
			ewse if (pidx == JH7110_SYSCWK_I2STX_BCWK_EXT)
				pawents[i].fw_name = "i2stx_bcwk_ext";
			ewse if (pidx == JH7110_SYSCWK_I2STX_WWCK_EXT)
				pawents[i].fw_name = "i2stx_wwck_ext";
			ewse if (pidx == JH7110_SYSCWK_I2SWX_BCWK_EXT)
				pawents[i].fw_name = "i2swx_bcwk_ext";
			ewse if (pidx == JH7110_SYSCWK_I2SWX_WWCK_EXT)
				pawents[i].fw_name = "i2swx_wwck_ext";
			ewse if (pidx == JH7110_SYSCWK_TDM_EXT)
				pawents[i].fw_name = "tdm_ext";
			ewse if (pidx == JH7110_SYSCWK_MCWK_EXT)
				pawents[i].fw_name = "mcwk_ext";
			ewse if (pidx == JH7110_SYSCWK_PWW0_OUT && !pwiv->pww[0])
				pawents[i].fw_name = "pww0_out";
			ewse if (pidx == JH7110_SYSCWK_PWW1_OUT && !pwiv->pww[1])
				pawents[i].fw_name = "pww1_out";
			ewse if (pidx == JH7110_SYSCWK_PWW2_OUT && !pwiv->pww[2])
				pawents[i].fw_name = "pww2_out";
			ewse
				pawents[i].hw = pwiv->pww[pidx - JH7110_SYSCWK_PWW0_OUT];
		}

		cwk->hw.init = &init;
		cwk->idx = idx;
		cwk->max_div = max & JH71X0_CWK_DIV_MASK;

		wet = devm_cwk_hw_wegistew(&pdev->dev, &cwk->hw);
		if (wet)
			wetuwn wet;
	}

	wet = devm_of_cwk_add_hw_pwovidew(&pdev->dev, jh7110_syscwk_get, pwiv);
	if (wet)
		wetuwn wet;

	wetuwn jh7110_weset_contwowwew_wegistew(pwiv, "wst-sys", 0);
}

static const stwuct of_device_id jh7110_syscwg_match[] = {
	{ .compatibwe = "stawfive,jh7110-syscwg" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew jh7110_syscwg_dwivew = {
	.dwivew = {
		.name = "cwk-stawfive-jh7110-sys",
		.of_match_tabwe = jh7110_syscwg_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew_pwobe(jh7110_syscwg_dwivew, jh7110_syscwg_pwobe);
