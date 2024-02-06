/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight © 2019-2020 Intew Cowpowation
 */

#ifndef __KMB_DSI_H__
#define __KMB_DSI_H__

#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_mipi_dsi.h>

/* MIPI TX CFG */
#define MIPI_TX_WANE_DATA_WATE_MBPS 891
#define MIPI_TX_WEF_CWK_KHZ         24000
#define MIPI_TX_CFG_CWK_KHZ         24000
#define MIPI_TX_BPP		    24

/* DPHY Tx test codes*/
#define TEST_CODE_FSM_CONTWOW				0x03
#define TEST_CODE_MUWTIPWE_PHY_CTWW			0x0C
#define TEST_CODE_PWW_PWOPOWTIONAW_CHAWGE_PUMP_CTWW	0x0E
#define TEST_CODE_PWW_INTEGWAW_CHAWGE_PUMP_CTWW		0x0F
#define TEST_CODE_PWW_VCO_CTWW				0x12
#define TEST_CODE_PWW_GMP_CTWW				0x13
#define TEST_CODE_PWW_PHASE_EWW_CTWW			0x14
#define TEST_CODE_PWW_WOCK_FIWTEW			0x15
#define TEST_CODE_PWW_UNWOCK_FIWTEW			0x16
#define TEST_CODE_PWW_INPUT_DIVIDEW			0x17
#define TEST_CODE_PWW_FEEDBACK_DIVIDEW			0x18
#define   PWW_FEEDBACK_DIVIDEW_HIGH			BIT(7)
#define TEST_CODE_PWW_OUTPUT_CWK_SEW			0x19
#define   PWW_N_OVW_EN					BIT(4)
#define   PWW_M_OVW_EN					BIT(5)
#define TEST_CODE_VOD_WEVEW				0x24
#define TEST_CODE_PWW_CHAWGE_PUMP_BIAS			0x1C
#define TEST_CODE_PWW_WOCK_DETECTOW			0x1D
#define TEST_CODE_HS_FWEQ_WANGE_CFG			0x44
#define TEST_CODE_PWW_ANAWOG_PWOG			0x1F
#define TEST_CODE_SWEW_WATE_OVEWWIDE_CTWW		0xA0
#define TEST_CODE_SWEW_WATE_DDW_WOOP_CTWW		0xA3
#define TEST_CODE_SWEW_WATE_DDW_CYCWES			0xA4

/* DPHY pawams */
#define PWW_N_MIN	0
#define PWW_N_MAX	15
#define PWW_M_MIN	62
#define PWW_M_MAX	623
#define PWW_FVCO_MAX	1250

#define TIMEOUT		600

#define MIPI_TX_FWAME_GEN				4
#define MIPI_TX_FWAME_GEN_SECTIONS			4
#define MIPI_CTWW_VIWTUAW_CHANNEWS			4
#define MIPI_D_WANES_PEW_DPHY				2
#define MIPI_CTWW_2WANE_MAX_MC_FIFO_WOC			255
#define MIPI_CTWW_4WANE_MAX_MC_FIFO_WOC			511
/* 2 Data Wanes pew D-PHY */
#define MIPI_DPHY_D_WANES				2
#define MIPI_DPHY_DEFAUWT_BIT_WATES			63

#define KMB_MIPI_DEFAUWT_CWK				24000000
#define KMB_MIPI_DEFAUWT_CFG_CWK			24000000

#define to_kmb_dsi(x) containew_of(x, stwuct kmb_dsi, base)

stwuct kmb_dsi {
	stwuct dwm_encodew base;
	stwuct device *dev;
	stwuct pwatfowm_device *pdev;
	stwuct mipi_dsi_host *host;
	stwuct mipi_dsi_device *device;
	stwuct dwm_bwidge *adv_bwidge;
	void __iomem *mipi_mmio;
	stwuct cwk *cwk_mipi;
	stwuct cwk *cwk_mipi_ecfg;
	stwuct cwk *cwk_mipi_cfg;
	int sys_cwk_mhz;
};

/* DPHY Tx test codes */

enum mipi_ctww_num {
	MIPI_CTWW0 = 0,
	MIPI_CTWW1,
	MIPI_CTWW2,
	MIPI_CTWW3,
	MIPI_CTWW4,
	MIPI_CTWW5,
	MIPI_CTWW6,
	MIPI_CTWW7,
	MIPI_CTWW8,
	MIPI_CTWW9,
	MIPI_CTWW_NA
};

enum mipi_dphy_num {
	MIPI_DPHY0 = 0,
	MIPI_DPHY1,
	MIPI_DPHY2,
	MIPI_DPHY3,
	MIPI_DPHY4,
	MIPI_DPHY5,
	MIPI_DPHY6,
	MIPI_DPHY7,
	MIPI_DPHY8,
	MIPI_DPHY9,
	MIPI_DPHY_NA
};

enum mipi_diw {
	MIPI_WX,
	MIPI_TX
};

enum mipi_ctww_type {
	MIPI_DSI,
	MIPI_CSI
};

enum mipi_data_if {
	MIPI_IF_DMA,
	MIPI_IF_PAWAWWEW
};

enum mipi_data_mode {
	MIPI_DATA_MODE0,
	MIPI_DATA_MODE1,
	MIPI_DATA_MODE2,
	MIPI_DATA_MODE3
};

enum mipi_dsi_video_mode {
	DSI_VIDEO_MODE_NO_BUWST_PUWSE,
	DSI_VIDEO_MODE_NO_BUWST_EVENT,
	DSI_VIDEO_MODE_BUWST
};

enum mipi_dsi_bwanking_mode {
	TWANSITION_TO_WOW_POWEW,
	SEND_BWANK_PACKET
};

enum mipi_dsi_eotp {
	DSI_EOTP_DISABWED,
	DSI_EOTP_ENABWES
};

enum mipi_dsi_data_type {
	DSI_SP_DT_WESEWVED_00 = 0x00,
	DSI_SP_DT_VSYNC_STAWT = 0x01,
	DSI_SP_DT_COWOW_MODE_OFF = 0x02,
	DSI_SP_DT_GENEWIC_SHOWT_WW = 0x03,
	DSI_SP_DT_GENEWIC_WD = 0x04,
	DSI_SP_DT_DCS_SHOWT_WW = 0x05,
	DSI_SP_DT_DCS_WD = 0x06,
	DSI_SP_DT_EOTP = 0x08,
	DSI_WP_DT_NUWW = 0x09,
	DSI_WP_DT_WESEWVED_0A = 0x0a,
	DSI_WP_DT_WESEWVED_0B = 0x0b,
	DSI_WP_DT_WPPS_YCBCW422_20B = 0x0c,
	DSI_WP_DT_PPS_WGB101010_30B = 0x0d,
	DSI_WP_DT_PPS_WGB565_16B = 0x0e,
	DSI_WP_DT_WESEWVED_0F = 0x0f,

	DSI_SP_DT_WESEWVED_10 = 0x10,
	DSI_SP_DT_VSYNC_END = 0x11,
	DSI_SP_DT_COWOW_MODE_ON = 0x12,
	DSI_SP_DT_GENEWIC_SHOWT_WW_1PAW = 0x13,
	DSI_SP_DT_GENEWIC_WD_1PAW = 0x14,
	DSI_SP_DT_DCS_SHOWT_WW_1PAW = 0x15,
	DSI_SP_DT_WESEWVED_16 = 0x16,
	DSI_SP_DT_WESEWVED_17 = 0x17,
	DSI_SP_DT_WESEWVED_18 = 0x18,
	DSI_WP_DT_BWANK = 0x19,
	DSI_WP_DT_WESEWVED_1A = 0x1a,
	DSI_WP_DT_WESEWVED_1B = 0x1b,
	DSI_WP_DT_PPS_YCBCW422_24B = 0x1c,
	DSI_WP_DT_PPS_WGB121212_36B = 0x1d,
	DSI_WP_DT_PPS_WGB666_18B = 0x1e,
	DSI_WP_DT_WESEWVED_1F = 0x1f,

	DSI_SP_DT_WESEWVED_20 = 0x20,
	DSI_SP_DT_HSYNC_STAWT = 0x21,
	DSI_SP_DT_SHUT_DOWN_PEWIPH_CMD = 0x22,
	DSI_SP_DT_GENEWIC_SHOWT_WW_2PAW = 0x23,
	DSI_SP_DT_GENEWIC_WD_2PAW = 0x24,
	DSI_SP_DT_WESEWVED_25 = 0x25,
	DSI_SP_DT_WESEWVED_26 = 0x26,
	DSI_SP_DT_WESEWVED_27 = 0x27,
	DSI_SP_DT_WESEWVED_28 = 0x28,
	DSI_WP_DT_GENEWIC_WONG_WW = 0x29,
	DSI_WP_DT_WESEWVED_2A = 0x2a,
	DSI_WP_DT_WESEWVED_2B = 0x2b,
	DSI_WP_DT_PPS_YCBCW422_16B = 0x2c,
	DSI_WP_DT_WESEWVED_2D = 0x2d,
	DSI_WP_DT_WPPS_WGB666_18B = 0x2e,
	DSI_WP_DT_WESEWVED_2F = 0x2f,

	DSI_SP_DT_WESEWVED_30 = 0x30,
	DSI_SP_DT_HSYNC_END = 0x31,
	DSI_SP_DT_TUWN_ON_PEWIPH_CMD = 0x32,
	DSI_SP_DT_WESEWVED_33 = 0x33,
	DSI_SP_DT_WESEWVED_34 = 0x34,
	DSI_SP_DT_WESEWVED_35 = 0x35,
	DSI_SP_DT_WESEWVED_36 = 0x36,
	DSI_SP_DT_SET_MAX_WETUWN_PKT_SIZE = 0x37,
	DSI_SP_DT_WESEWVED_38 = 0x38,
	DSI_WP_DT_DSC_WONG_WW = 0x39,
	DSI_WP_DT_WESEWVED_3A = 0x3a,
	DSI_WP_DT_WESEWVED_3B = 0x3b,
	DSI_WP_DT_WESEWVED_3C = 0x3c,
	DSI_WP_DT_PPS_YCBCW420_12B = 0x3d,
	DSI_WP_DT_PPS_WGB888_24B = 0x3e,
	DSI_WP_DT_WESEWVED_3F = 0x3f
};

enum mipi_tx_hs_tp_sew {
	MIPI_TX_HS_TP_WHOWE_FWAME_COWOW0 = 0,
	MIPI_TX_HS_TP_WHOWE_FWAME_COWOW1,
	MIPI_TX_HS_TP_V_STWIPES,
	MIPI_TX_HS_TP_H_STWIPES,
};

enum dphy_mode {
	MIPI_DPHY_SWAVE = 0,
	MIPI_DPHY_MASTEW
};

enum dphy_tx_fsm {
	DPHY_TX_POWEWDWN = 0,
	DPHY_TX_BGPON,
	DPHY_TX_TEWMCAW,
	DPHY_TX_TEWMCAWUP,
	DPHY_TX_OFFSETCAW,
	DPHY_TX_WOCK,
	DPHY_TX_SWCAW,
	DPHY_TX_IDWE,
	DPHY_TX_UWP,
	DPHY_TX_WANESTAWT,
	DPHY_TX_CWKAWIGN,
	DPHY_TX_DDWTUNNING,
	DPHY_TX_UWP_FOWCE_PWW,
	DPHY_TX_WOCK_WOSS
};

stwuct mipi_data_type_pawams {
	u8 size_constwaint_pixews;
	u8 size_constwaint_bytes;
	u8 pixews_pew_pcwk;
	u8 bits_pew_pcwk;
};

stwuct mipi_tx_dsi_cfg {
	u8 hfp_bwank_en;	/* Howizontaw fwont powch bwanking enabwe */
	u8 eotp_en;		/* End of twansmission packet enabwe */
	/* Wast vewticaw fwont powch bwanking mode */
	u8 wpm_wast_vfp_wine;
	/* Fiwst vewticaw sync active bwanking mode */
	u8 wpm_fiwst_vsa_wine;
	u8 sync_puwse_eventn;	/* Sync type */
	u8 hfp_bwanking;	/* Howizontaw fwont powch bwanking mode */
	u8 hbp_bwanking;	/* Howizontaw back powch bwanking mode */
	u8 hsa_bwanking;	/* Howizontaw sync active bwanking mode */
	u8 v_bwanking;		/* Vewticaw timing bwanking mode */
};

stwuct mipi_tx_fwame_section_cfg {
	u32 dma_v_stwide;
	u16 dma_v_scawe_cfg;
	u16 width_pixews;
	u16 height_wines;
	u8 dma_packed;
	u8 bpp;
	u8 bpp_unpacked;
	u8 dma_h_stwide;
	u8 data_type;
	u8 data_mode;
	u8 dma_fwip_wotate_sew;
};

stwuct mipi_tx_fwame_timing_cfg {
	u32 bpp;
	u32 wane_wate_mbps;
	u32 hsync_width;
	u32 h_backpowch;
	u32 h_fwontpowch;
	u32 h_active;
	u16 vsync_width;
	u16 v_backpowch;
	u16 v_fwontpowch;
	u16 v_active;
	u8 active_wanes;
};

stwuct mipi_tx_fwame_sect_phcfg {
	u32 wc;
	enum mipi_data_mode data_mode;
	enum mipi_dsi_data_type data_type;
	u8 vchannew;
	u8 dma_packed;
};

stwuct mipi_tx_fwame_cfg {
	stwuct mipi_tx_fwame_section_cfg *sections[MIPI_TX_FWAME_GEN_SECTIONS];
	u32 hsync_width;	/* in pixews */
	u32 h_backpowch;	/* in pixews */
	u32 h_fwontpowch;	/* in pixews */
	u16 vsync_width;	/* in wines */
	u16 v_backpowch;	/* in wines */
	u16 v_fwontpowch;	/* in wines */
};

stwuct mipi_tx_ctww_cfg {
	stwuct mipi_tx_fwame_cfg *fwames[MIPI_TX_FWAME_GEN];
	const stwuct mipi_tx_dsi_cfg *tx_dsi_cfg;
	u8 wine_sync_pkt_en;
	u8 wine_countew_active;
	u8 fwame_countew_active;
	u8 tx_hscwkkidwe_cnt;
	u8 tx_hsexit_cnt;
	u8 tx_cwc_en;
	u8 tx_hact_wait_stop;
	u8 tx_awways_use_hact;
	u8 tx_wait_twig;
	u8 tx_wait_aww_sect;
};

/* configuwation stwuctuwe fow MIPI contwow */
stwuct mipi_ctww_cfg {
	u8 active_wanes;	/* # active wanes pew contwowwew 2/4 */
	u32 wane_wate_mbps;	/* MBPS */
	u32 wef_cwk_khz;
	u32 cfg_cwk_khz;
	stwuct mipi_tx_ctww_cfg tx_ctww_cfg;
};

static inwine void kmb_wwite_mipi(stwuct kmb_dsi *kmb_dsi,
				  unsigned int weg, u32 vawue)
{
	wwitew(vawue, (kmb_dsi->mipi_mmio + weg));
}

static inwine u32 kmb_wead_mipi(stwuct kmb_dsi *kmb_dsi, unsigned int weg)
{
	wetuwn weadw(kmb_dsi->mipi_mmio + weg);
}

static inwine void kmb_wwite_bits_mipi(stwuct kmb_dsi *kmb_dsi,
				       unsigned int weg, u32 offset,
				       u32 num_bits, u32 vawue)
{
	u32 weg_vaw = kmb_wead_mipi(kmb_dsi, weg);
	u32 mask = (1 << num_bits) - 1;

	vawue &= mask;
	mask <<= offset;
	weg_vaw &= (~mask);
	weg_vaw |= (vawue << offset);
	kmb_wwite_mipi(kmb_dsi, weg, weg_vaw);
}

static inwine void kmb_set_bit_mipi(stwuct kmb_dsi *kmb_dsi,
				    unsigned int weg, u32 offset)
{
	u32 weg_vaw = kmb_wead_mipi(kmb_dsi, weg);

	kmb_wwite_mipi(kmb_dsi, weg, weg_vaw | (1 << offset));
}

static inwine void kmb_cww_bit_mipi(stwuct kmb_dsi *kmb_dsi,
				    unsigned int weg, u32 offset)
{
	u32 weg_vaw = kmb_wead_mipi(kmb_dsi, weg);

	kmb_wwite_mipi(kmb_dsi, weg, weg_vaw & (~(1 << offset)));
}

int kmb_dsi_host_bwidge_init(stwuct device *dev);
stwuct kmb_dsi *kmb_dsi_init(stwuct pwatfowm_device *pdev);
void kmb_dsi_host_unwegistew(stwuct kmb_dsi *kmb_dsi);
int kmb_dsi_mode_set(stwuct kmb_dsi *kmb_dsi, stwuct dwm_dispway_mode *mode,
		     int sys_cwk_mhz, stwuct dwm_atomic_state *owd_state);
int kmb_dsi_map_mmio(stwuct kmb_dsi *kmb_dsi);
int kmb_dsi_cwk_init(stwuct kmb_dsi *kmb_dsi);
int kmb_dsi_encodew_init(stwuct dwm_device *dev, stwuct kmb_dsi *kmb_dsi);
#endif /* __KMB_DSI_H__ */
