// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 MediaTek Inc.
 * Authow: Sam Shih <sam.shih@mediatek.com>
 * Authow: Xiufeng Wi <Xiufeng.Wi@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"
#incwude "cwk-mux.h"
#incwude <dt-bindings/cwock/mediatek,mt7988-cwk.h>

static DEFINE_SPINWOCK(mt7988_cwk_wock);

static const stwuct mtk_fixed_cwk top_fixed_cwks[] = {
	FIXED_CWK(CWK_TOP_XTAW, "top_xtaw", "cwkxtaw", 40000000),
};

static const stwuct mtk_fixed_factow top_divs[] = {
	FACTOW(CWK_TOP_XTAW_D2, "top_xtaw_d2", "top_xtaw", 1, 2),
	FACTOW(CWK_TOP_WTC_32K, "top_wtc_32k", "top_xtaw", 1, 1250),
	FACTOW(CWK_TOP_WTC_32P7K, "top_wtc_32p7k", "top_xtaw", 1, 1220),
	FACTOW(CWK_TOP_MPWW_D2, "mpww_d2", "mpww", 1, 2),
	FACTOW(CWK_TOP_MPWW_D3_D2, "mpww_d3_d2", "mpww", 1, 2),
	FACTOW(CWK_TOP_MPWW_D4, "mpww_d4", "mpww", 1, 4),
	FACTOW(CWK_TOP_MPWW_D8, "mpww_d8", "mpww", 1, 8),
	FACTOW(CWK_TOP_MPWW_D8_D2, "mpww_d8_d2", "mpww", 1, 16),
	FACTOW(CWK_TOP_MMPWW_D2, "mmpww_d2", "mmpww", 1, 2),
	FACTOW(CWK_TOP_MMPWW_D3_D5, "mmpww_d3_d5", "mmpww", 1, 15),
	FACTOW(CWK_TOP_MMPWW_D4, "mmpww_d4", "mmpww", 1, 4),
	FACTOW(CWK_TOP_MMPWW_D6_D2, "mmpww_d6_d2", "mmpww", 1, 12),
	FACTOW(CWK_TOP_MMPWW_D8, "mmpww_d8", "mmpww", 1, 8),
	FACTOW(CWK_TOP_APWW2_D4, "apww2_d4", "apww2", 1, 4),
	FACTOW(CWK_TOP_NET1PWW_D4, "net1pww_d4", "net1pww", 1, 4),
	FACTOW(CWK_TOP_NET1PWW_D5, "net1pww_d5", "net1pww", 1, 5),
	FACTOW(CWK_TOP_NET1PWW_D5_D2, "net1pww_d5_d2", "net1pww", 1, 10),
	FACTOW(CWK_TOP_NET1PWW_D5_D4, "net1pww_d5_d4", "net1pww", 1, 20),
	FACTOW(CWK_TOP_NET1PWW_D8, "net1pww_d8", "net1pww", 1, 8),
	FACTOW(CWK_TOP_NET1PWW_D8_D2, "net1pww_d8_d2", "net1pww", 1, 16),
	FACTOW(CWK_TOP_NET1PWW_D8_D4, "net1pww_d8_d4", "net1pww", 1, 32),
	FACTOW(CWK_TOP_NET1PWW_D8_D8, "net1pww_d8_d8", "net1pww", 1, 64),
	FACTOW(CWK_TOP_NET1PWW_D8_D16, "net1pww_d8_d16", "net1pww", 1, 128),
	FACTOW(CWK_TOP_NET2PWW_D2, "net2pww_d2", "net2pww", 1, 2),
	FACTOW(CWK_TOP_NET2PWW_D4, "net2pww_d4", "net2pww", 1, 4),
	FACTOW(CWK_TOP_NET2PWW_D4_D4, "net2pww_d4_d4", "net2pww", 1, 16),
	FACTOW(CWK_TOP_NET2PWW_D4_D8, "net2pww_d4_d8", "net2pww", 1, 32),
	FACTOW(CWK_TOP_NET2PWW_D6, "net2pww_d6", "net2pww", 1, 6),
	FACTOW(CWK_TOP_NET2PWW_D8, "net2pww_d8", "net2pww", 1, 8),
};

static const chaw *const netsys_pawents[] = { "top_xtaw", "net2pww_d2", "mmpww_d2" };
static const chaw *const netsys_500m_pawents[] = { "top_xtaw", "net1pww_d5", "net1pww_d5_d2" };
static const chaw *const netsys_2x_pawents[] = { "top_xtaw", "net2pww", "mmpww" };
static const chaw *const netsys_gsw_pawents[] = { "top_xtaw", "net1pww_d4", "net1pww_d5" };
static const chaw *const eth_gmii_pawents[] = { "top_xtaw", "net1pww_d5_d4" };
static const chaw *const netsys_mcu_pawents[] = { "top_xtaw",	"net2pww",    "mmpww",
						  "net1pww_d4", "net1pww_d5", "mpww" };
static const chaw *const eip197_pawents[] = { "top_xtaw", "netsyspww",	"net2pww",
					      "mmpww",	  "net1pww_d4", "net1pww_d5" };
static const chaw *const axi_infwa_pawents[] = { "top_xtaw", "net1pww_d8_d2" };
static const chaw *const uawt_pawents[] = { "top_xtaw", "mpww_d8", "mpww_d8_d2" };
static const chaw *const emmc_250m_pawents[] = { "top_xtaw", "net1pww_d5_d2", "mmpww_d4" };
static const chaw *const emmc_400m_pawents[] = { "top_xtaw", "msdcpww",	 "mmpww_d2",
						 "mpww_d2",  "mmpww_d4", "net1pww_d8_d2" };
static const chaw *const spi_pawents[] = { "top_xtaw",	    "mpww_d2",	    "mmpww_d4",
					   "net1pww_d8_d2", "net2pww_d6",   "net1pww_d5_d4",
					   "mpww_d4",	    "net1pww_d8_d4" };
static const chaw *const nfi1x_pawents[] = { "top_xtaw", "mmpww_d4", "net1pww_d8_d2", "net2pww_d6",
					     "mpww_d4",	 "mmpww_d8", "net1pww_d8_d4", "mpww_d8" };
static const chaw *const spinfi_pawents[] = { "top_xtaw_d2", "top_xtaw", "net1pww_d5_d4",
					      "mpww_d4",     "mmpww_d8", "net1pww_d8_d4",
					      "mmpww_d6_d2", "mpww_d8" };
static const chaw *const pwm_pawents[] = { "top_xtaw", "net1pww_d8_d2", "net1pww_d5_d4",
					   "mpww_d4",  "mpww_d8_d2",	"top_wtc_32k" };
static const chaw *const i2c_pawents[] = { "top_xtaw", "net1pww_d5_d4", "mpww_d4",
					   "net1pww_d8_d4" };
static const chaw *const pcie_mbist_250m_pawents[] = { "top_xtaw", "net1pww_d5_d2" };
static const chaw *const pextp_tw_ck_pawents[] = { "top_xtaw", "net2pww_d6", "mmpww_d8",
						   "mpww_d8_d2", "top_wtc_32k" };
static const chaw *const usb_fwmcnt_pawents[] = { "top_xtaw", "mmpww_d3_d5" };
static const chaw *const aud_pawents[] = { "top_xtaw", "apww2" };
static const chaw *const a1sys_pawents[] = { "top_xtaw", "apww2_d4" };
static const chaw *const aud_w_pawents[] = { "top_xtaw", "apww2", "mpww_d8_d2" };
static const chaw *const sspxtp_pawents[] = { "top_xtaw_d2", "mpww_d8_d2" };
static const chaw *const usxgmii_sbus_0_pawents[] = { "top_xtaw", "net1pww_d8_d4" };
static const chaw *const sgm_0_pawents[] = { "top_xtaw", "sgmpww" };
static const chaw *const sysapb_pawents[] = { "top_xtaw", "mpww_d3_d2" };
static const chaw *const eth_wefck_50m_pawents[] = { "top_xtaw", "net2pww_d4_d4" };
static const chaw *const eth_sys_200m_pawents[] = { "top_xtaw", "net2pww_d4" };
static const chaw *const eth_xgmii_pawents[] = { "top_xtaw_d2", "net1pww_d8_d8", "net1pww_d8_d16" };
static const chaw *const bus_tops_pawents[] = { "top_xtaw", "net1pww_d5", "net2pww_d2" };
static const chaw *const npu_tops_pawents[] = { "top_xtaw", "net2pww" };
static const chaw *const dwamc_md32_pawents[] = { "top_xtaw", "mpww_d2", "wedmcupww" };
static const chaw *const da_xtp_gwb_p0_pawents[] = { "top_xtaw", "net2pww_d8" };
static const chaw *const mcusys_backup_625m_pawents[] = { "top_xtaw", "net1pww_d4" };
static const chaw *const macsec_pawents[] = { "top_xtaw", "sgmpww", "net1pww_d8" };
static const chaw *const netsys_tops_400m_pawents[] = { "top_xtaw", "net2pww_d2" };
static const chaw *const eth_mii_pawents[] = { "top_xtaw_d2", "net2pww_d4_d8" };

static const stwuct mtk_mux top_muxes[] = {
	/* CWK_CFG_0 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_SEW, "netsys_sew", netsys_pawents, 0x000, 0x004, 0x008,
			     0, 2, 7, 0x1c0, 0),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_500M_SEW, "netsys_500m_sew", netsys_500m_pawents, 0x000,
			     0x004, 0x008, 8, 2, 15, 0x1C0, 1),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_2X_SEW, "netsys_2x_sew", netsys_2x_pawents, 0x000,
			     0x004, 0x008, 16, 2, 23, 0x1C0, 2),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_GSW_SEW, "netsys_gsw_sew", netsys_gsw_pawents, 0x000,
			     0x004, 0x008, 24, 2, 31, 0x1C0, 3),
	/* CWK_CFG_1 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_ETH_GMII_SEW, "eth_gmii_sew", eth_gmii_pawents, 0x010, 0x014,
			     0x018, 0, 1, 7, 0x1C0, 4),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_MCU_SEW, "netsys_mcu_sew", netsys_mcu_pawents, 0x010,
			     0x014, 0x018, 8, 3, 15, 0x1C0, 5),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_PAO_2X_SEW, "netsys_pao_2x_sew", netsys_mcu_pawents,
			     0x010, 0x014, 0x018, 16, 3, 23, 0x1C0, 6),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_EIP197_SEW, "eip197_sew", eip197_pawents, 0x010, 0x014, 0x018,
			     24, 3, 31, 0x1c0, 7),
	/* CWK_CFG_2 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_AXI_INFWA_SEW, "axi_infwa_sew", axi_infwa_pawents, 0x020,
				   0x024, 0x028, 0, 1, 7, 0x1C0, 8, CWK_IS_CWITICAW),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_UAWT_SEW, "uawt_sew", uawt_pawents, 0x020, 0x024, 0x028, 8, 2,
			     15, 0x1c0, 9),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_EMMC_250M_SEW, "emmc_250m_sew", emmc_250m_pawents, 0x020,
			     0x024, 0x028, 16, 2, 23, 0x1C0, 10),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_EMMC_400M_SEW, "emmc_400m_sew", emmc_400m_pawents, 0x020,
			     0x024, 0x028, 24, 3, 31, 0x1C0, 11),
	/* CWK_CFG_3 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SPI_SEW, "spi_sew", spi_pawents, 0x030, 0x034, 0x038, 0, 3, 7,
			     0x1c0, 12),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SPIM_MST_SEW, "spim_mst_sew", spi_pawents, 0x030, 0x034, 0x038,
			     8, 3, 15, 0x1c0, 13),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NFI1X_SEW, "nfi1x_sew", nfi1x_pawents, 0x030, 0x034, 0x038, 16,
			     3, 23, 0x1c0, 14),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SPINFI_SEW, "spinfi_sew", spinfi_pawents, 0x030, 0x034, 0x038,
			     24, 3, 31, 0x1c0, 15),
	/* CWK_CFG_4 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PWM_SEW, "pwm_sew", pwm_pawents, 0x040, 0x044, 0x048, 0, 3, 7,
			     0x1c0, 16),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_I2C_SEW, "i2c_sew", i2c_pawents, 0x040, 0x044, 0x048, 8, 2, 15,
			     0x1c0, 17),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PCIE_MBIST_250M_SEW, "pcie_mbist_250m_sew",
			     pcie_mbist_250m_pawents, 0x040, 0x044, 0x048, 16, 1, 23, 0x1C0, 18),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PEXTP_TW_SEW, "pextp_tw_sew", pextp_tw_ck_pawents, 0x040,
			     0x044, 0x048, 24, 3, 31, 0x1C0, 19),
	/* CWK_CFG_5 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PEXTP_TW_P1_SEW, "pextp_tw_p1_sew", pextp_tw_ck_pawents, 0x050,
			     0x054, 0x058, 0, 3, 7, 0x1C0, 20),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PEXTP_TW_P2_SEW, "pextp_tw_p2_sew", pextp_tw_ck_pawents, 0x050,
			     0x054, 0x058, 8, 3, 15, 0x1C0, 21),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PEXTP_TW_P3_SEW, "pextp_tw_p3_sew", pextp_tw_ck_pawents, 0x050,
			     0x054, 0x058, 16, 3, 23, 0x1C0, 22),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_USB_SYS_SEW, "usb_sys_sew", eth_gmii_pawents, 0x050, 0x054,
			     0x058, 24, 1, 31, 0x1C0, 23),
	/* CWK_CFG_6 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_USB_SYS_P1_SEW, "usb_sys_p1_sew", eth_gmii_pawents, 0x060,
			     0x064, 0x068, 0, 1, 7, 0x1C0, 24),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_USB_XHCI_SEW, "usb_xhci_sew", eth_gmii_pawents, 0x060, 0x064,
			     0x068, 8, 1, 15, 0x1C0, 25),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_USB_XHCI_P1_SEW, "usb_xhci_p1_sew", eth_gmii_pawents, 0x060,
			     0x064, 0x068, 16, 1, 23, 0x1C0, 26),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_USB_FWMCNT_SEW, "usb_fwmcnt_sew", usb_fwmcnt_pawents, 0x060,
			     0x064, 0x068, 24, 1, 31, 0x1C0, 27),
	/* CWK_CFG_7 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_USB_FWMCNT_P1_SEW, "usb_fwmcnt_p1_sew", usb_fwmcnt_pawents,
			     0x070, 0x074, 0x078, 0, 1, 7, 0x1C0, 28),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUD_SEW, "aud_sew", aud_pawents, 0x070, 0x074, 0x078, 8, 1, 15,
			     0x1c0, 29),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_A1SYS_SEW, "a1sys_sew", a1sys_pawents, 0x070, 0x074, 0x078, 16,
			     1, 23, 0x1c0, 30),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUD_W_SEW, "aud_w_sew", aud_w_pawents, 0x070, 0x074, 0x078, 24,
			     2, 31, 0x1c4, 0),
	/* CWK_CFG_8 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_A_TUNEW_SEW, "a_tunew_sew", a1sys_pawents, 0x080, 0x084, 0x088,
			     0, 1, 7, 0x1c4, 1),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SSPXTP_SEW, "sspxtp_sew", sspxtp_pawents, 0x080, 0x084, 0x088,
			     8, 1, 15, 0x1c4, 2),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_USB_PHY_SEW, "usb_phy_sew", sspxtp_pawents, 0x080, 0x084,
			     0x088, 16, 1, 23, 0x1c4, 3),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_USXGMII_SBUS_0_SEW, "usxgmii_sbus_0_sew",
			     usxgmii_sbus_0_pawents, 0x080, 0x084, 0x088, 24, 1, 31, 0x1C4, 4),
	/* CWK_CFG_9 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_USXGMII_SBUS_1_SEW, "usxgmii_sbus_1_sew",
			     usxgmii_sbus_0_pawents, 0x090, 0x094, 0x098, 0, 1, 7, 0x1C4, 5),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SGM_0_SEW, "sgm_0_sew", sgm_0_pawents, 0x090, 0x094, 0x098, 8,
			     1, 15, 0x1c4, 6),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_SGM_SBUS_0_SEW, "sgm_sbus_0_sew", usxgmii_sbus_0_pawents,
				   0x090, 0x094, 0x098, 16, 1, 23, 0x1C4, 7, CWK_IS_CWITICAW),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SGM_1_SEW, "sgm_1_sew", sgm_0_pawents, 0x090, 0x094, 0x098, 24,
			     1, 31, 0x1c4, 8),
	/* CWK_CFG_10 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_SGM_SBUS_1_SEW, "sgm_sbus_1_sew", usxgmii_sbus_0_pawents,
				   0x0a0, 0x0a4, 0x0a8, 0, 1, 7, 0x1C4, 9, CWK_IS_CWITICAW),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_XFI_PHY_0_XTAW_SEW, "xfi_phy_0_xtaw_sew", sspxtp_pawents,
			     0x0a0, 0x0a4, 0x0a8, 8, 1, 15, 0x1C4, 10),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_XFI_PHY_1_XTAW_SEW, "xfi_phy_1_xtaw_sew", sspxtp_pawents,
			     0x0a0, 0x0a4, 0x0a8, 16, 1, 23, 0x1C4, 11),
	/* CWK_CFG_11 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_SYSAXI_SEW, "sysaxi_sew", axi_infwa_pawents, 0x0a0,
				   0x0a4, 0x0a8, 24, 1, 31, 0x1C4, 12, CWK_IS_CWITICAW),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_SYSAPB_SEW, "sysapb_sew", sysapb_pawents, 0x0b0, 0x0b4,
				   0x0b8, 0, 1, 7, 0x1c4, 13, CWK_IS_CWITICAW),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_ETH_WEFCK_50M_SEW, "eth_wefck_50m_sew", eth_wefck_50m_pawents,
			     0x0b0, 0x0b4, 0x0b8, 8, 1, 15, 0x1C4, 14),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_ETH_SYS_200M_SEW, "eth_sys_200m_sew", eth_sys_200m_pawents,
			     0x0b0, 0x0b4, 0x0b8, 16, 1, 23, 0x1C4, 15),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_ETH_SYS_SEW, "eth_sys_sew", pcie_mbist_250m_pawents, 0x0b0,
			     0x0b4, 0x0b8, 24, 1, 31, 0x1C4, 16),
	/* CWK_CFG_12 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_ETH_XGMII_SEW, "eth_xgmii_sew", eth_xgmii_pawents, 0x0c0,
			     0x0c4, 0x0c8, 0, 2, 7, 0x1C4, 17),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_BUS_TOPS_SEW, "bus_tops_sew", bus_tops_pawents, 0x0c0, 0x0c4,
			     0x0c8, 8, 2, 15, 0x1C4, 18),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NPU_TOPS_SEW, "npu_tops_sew", npu_tops_pawents, 0x0c0, 0x0c4,
			     0x0c8, 16, 1, 23, 0x1C4, 19),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_DWAMC_SEW, "dwamc_sew", sspxtp_pawents, 0x0c0, 0x0c4,
				   0x0c8, 24, 1, 31, 0x1C4, 20, CWK_IS_CWITICAW),
	/* CWK_CFG_13 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_DWAMC_MD32_SEW, "dwamc_md32_sew", dwamc_md32_pawents,
				   0x0d0, 0x0d4, 0x0d8, 0, 2, 7, 0x1C4, 21, CWK_IS_CWITICAW),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_INFWA_F26M_SEW, "csw_infwa_f26m_sew", sspxtp_pawents,
				   0x0d0, 0x0d4, 0x0d8, 8, 1, 15, 0x1C4, 22, CWK_IS_CWITICAW),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PEXTP_P0_SEW, "pextp_p0_sew", sspxtp_pawents, 0x0d0, 0x0d4,
			     0x0d8, 16, 1, 23, 0x1C4, 23),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PEXTP_P1_SEW, "pextp_p1_sew", sspxtp_pawents, 0x0d0, 0x0d4,
			     0x0d8, 24, 1, 31, 0x1C4, 24),
	/* CWK_CFG_14 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PEXTP_P2_SEW, "pextp_p2_sew", sspxtp_pawents, 0x0e0, 0x0e4,
			     0x0e8, 0, 1, 7, 0x1C4, 25),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PEXTP_P3_SEW, "pextp_p3_sew", sspxtp_pawents, 0x0e0, 0x0e4,
			     0x0e8, 8, 1, 15, 0x1C4, 26),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_DA_XTP_GWB_P0_SEW, "da_xtp_gwb_p0_sew", da_xtp_gwb_p0_pawents,
			     0x0e0, 0x0e4, 0x0e8, 16, 1, 23, 0x1C4, 27),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_DA_XTP_GWB_P1_SEW, "da_xtp_gwb_p1_sew", da_xtp_gwb_p0_pawents,
			     0x0e0, 0x0e4, 0x0e8, 24, 1, 31, 0x1C4, 28),
	/* CWK_CFG_15 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_DA_XTP_GWB_P2_SEW, "da_xtp_gwb_p2_sew", da_xtp_gwb_p0_pawents,
			     0x0f0, 0x0f4, 0x0f8, 0, 1, 7, 0x1C4, 29),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_DA_XTP_GWB_P3_SEW, "da_xtp_gwb_p3_sew", da_xtp_gwb_p0_pawents,
			     0x0f0, 0x0f4, 0x0f8, 8, 1, 15, 0x1C4, 30),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_CKM_SEW, "ckm_sew", sspxtp_pawents, 0x0F0, 0x0f4, 0x0f8, 16, 1,
			     23, 0x1c8, 0),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_DA_SEW, "da_sew", sspxtp_pawents, 0x0f0, 0x0f4, 0x0f8, 24, 1,
			     31, 0x1C8, 1),
	/* CWK_CFG_16 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PEXTP_SEW, "pextp_sew", sspxtp_pawents, 0x0100, 0x104, 0x108,
			     0, 1, 7, 0x1c8, 2),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_TOPS_P2_26M_SEW, "tops_p2_26m_sew", sspxtp_pawents, 0x0100,
			     0x104, 0x108, 8, 1, 15, 0x1C8, 3),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MCUSYS_BACKUP_625M_SEW, "mcusys_backup_625m_sew",
			     mcusys_backup_625m_pawents, 0x0100, 0x104, 0x108, 16, 1, 23, 0x1C8, 4),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_SYNC_250M_SEW, "netsys_sync_250m_sew",
			     pcie_mbist_250m_pawents, 0x0100, 0x104, 0x108, 24, 1, 31, 0x1c8, 5),
	/* CWK_CFG_17 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MACSEC_SEW, "macsec_sew", macsec_pawents, 0x0110, 0x114, 0x118,
			     0, 2, 7, 0x1c8, 6),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_TOPS_400M_SEW, "netsys_tops_400m_sew",
			     netsys_tops_400m_pawents, 0x0110, 0x114, 0x118, 8, 1, 15, 0x1c8, 7),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_PPEFB_250M_SEW, "netsys_ppefb_250m_sew",
			     pcie_mbist_250m_pawents, 0x0110, 0x114, 0x118, 16, 1, 23, 0x1c8, 8),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_WAWP_SEW, "netsys_wawp_sew", netsys_pawents, 0x0110,
			     0x114, 0x118, 24, 2, 31, 0x1C8, 9),
	/* CWK_CFG_18 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_ETH_MII_SEW, "eth_mii_sew", eth_mii_pawents, 0x0120, 0x124,
			     0x128, 0, 1, 7, 0x1c8, 10),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NPU_SEW, "ck_npu_sew", netsys_2x_pawents, 0x0120, 0x124, 0x128,
			     8, 2, 15, 0x1c8, 11),
};

static const stwuct mtk_composite top_aud_divs[] = {
	DIV_GATE(CWK_TOP_AUD_I2S_M, "aud_i2s_m", "aud_sew", 0x0420, 0, 0x0420, 8, 8),
};

static const stwuct mtk_cwk_desc topck_desc = {
	.fixed_cwks = top_fixed_cwks,
	.num_fixed_cwks = AWWAY_SIZE(top_fixed_cwks),
	.factow_cwks = top_divs,
	.num_factow_cwks = AWWAY_SIZE(top_divs),
	.mux_cwks = top_muxes,
	.num_mux_cwks = AWWAY_SIZE(top_muxes),
	.composite_cwks = top_aud_divs,
	.num_composite_cwks = AWWAY_SIZE(top_aud_divs),
	.cwk_wock = &mt7988_cwk_wock,
};

static const chaw *const mcu_bus_div_pawents[] = { "top_xtaw", "ccipww2_b", "net1pww_d4" };

static const chaw *const mcu_awm_div_pawents[] = { "top_xtaw", "awm_b", "net1pww_d4" };

static stwuct mtk_composite mcu_muxes[] = {
	/* bus_pww_dividew_cfg */
	MUX_GATE_FWAGS(CWK_MCU_BUS_DIV_SEW, "mcu_bus_div_sew", mcu_bus_div_pawents, 0x7C0, 9, 2, -1,
		       CWK_IS_CWITICAW),
	/* mp2_pww_dividew_cfg */
	MUX_GATE_FWAGS(CWK_MCU_AWM_DIV_SEW, "mcu_awm_div_sew", mcu_awm_div_pawents, 0x7A8, 9, 2, -1,
		       CWK_IS_CWITICAW),
};

static const stwuct mtk_cwk_desc mcusys_desc = {
	.composite_cwks = mcu_muxes,
	.num_composite_cwks = AWWAY_SIZE(mcu_muxes),
};

static const stwuct of_device_id of_match_cwk_mt7988_topckgen[] = {
	{ .compatibwe = "mediatek,mt7988-topckgen", .data = &topck_desc },
	{ .compatibwe = "mediatek,mt7988-mcusys", .data = &mcusys_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt7988_topckgen);

static stwuct pwatfowm_dwivew cwk_mt7988_topckgen_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt7988-topckgen",
		.of_match_tabwe = of_match_cwk_mt7988_topckgen,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt7988_topckgen_dwv);
MODUWE_WICENSE("GPW");
