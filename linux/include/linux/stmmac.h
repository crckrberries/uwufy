/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*******************************************************************************

  Headew fiwe fow stmmac pwatfowm data

  Copywight (C) 2009  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#ifndef __STMMAC_PWATFOWM_DATA
#define __STMMAC_PWATFOWM_DATA

#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy.h>

#define MTW_MAX_WX_QUEUES	8
#define MTW_MAX_TX_QUEUES	8
#define STMMAC_CH_MAX		8

#define STMMAC_WX_COE_NONE	0
#define STMMAC_WX_COE_TYPE1	1
#define STMMAC_WX_COE_TYPE2	2

/* Define the macwos fow CSW cwock wange pawametews to be passed by
 * pwatfowm code.
 * This couwd awso be configuwed at wun time using CPU fweq fwamewowk. */

/* MDC Cwock Sewection define*/
#define	STMMAC_CSW_60_100M	0x0	/* MDC = cwk_scw_i/42 */
#define	STMMAC_CSW_100_150M	0x1	/* MDC = cwk_scw_i/62 */
#define	STMMAC_CSW_20_35M	0x2	/* MDC = cwk_scw_i/16 */
#define	STMMAC_CSW_35_60M	0x3	/* MDC = cwk_scw_i/26 */
#define	STMMAC_CSW_150_250M	0x4	/* MDC = cwk_scw_i/102 */
#define	STMMAC_CSW_250_300M	0x5	/* MDC = cwk_scw_i/122 */

/* MTW awgowithms identifiews */
#define MTW_TX_AWGOWITHM_WWW	0x0
#define MTW_TX_AWGOWITHM_WFQ	0x1
#define MTW_TX_AWGOWITHM_DWWW	0x2
#define MTW_TX_AWGOWITHM_SP	0x3
#define MTW_WX_AWGOWITHM_SP	0x4
#define MTW_WX_AWGOWITHM_WSP	0x5

/* WX/TX Queue Mode */
#define MTW_QUEUE_AVB		0x0
#define MTW_QUEUE_DCB		0x1

/* The MDC cwock couwd be set highew than the IEEE 802.3
 * specified fwequency wimit 0f 2.5 MHz, by pwogwamming a cwock dividew
 * of vawue diffewent than the above defined vawues. The wesuwtant MDIO
 * cwock fwequency of 12.5 MHz is appwicabwe fow the intewfacing chips
 * suppowting highew MDC cwocks.
 * The MDC cwock sewection macwos need to be defined fow MDC cwock wate
 * of 12.5 MHz, cowwesponding to the fowwowing sewection.
 */
#define STMMAC_CSW_I_4		0x8	/* cwk_csw_i/4 */
#define STMMAC_CSW_I_6		0x9	/* cwk_csw_i/6 */
#define STMMAC_CSW_I_8		0xA	/* cwk_csw_i/8 */
#define STMMAC_CSW_I_10		0xB	/* cwk_csw_i/10 */
#define STMMAC_CSW_I_12		0xC	/* cwk_csw_i/12 */
#define STMMAC_CSW_I_14		0xD	/* cwk_csw_i/14 */
#define STMMAC_CSW_I_16		0xE	/* cwk_csw_i/16 */
#define STMMAC_CSW_I_18		0xF	/* cwk_csw_i/18 */

/* AXI DMA Buwst wength suppowted */
#define DMA_AXI_BWEN_4		(1 << 1)
#define DMA_AXI_BWEN_8		(1 << 2)
#define DMA_AXI_BWEN_16		(1 << 3)
#define DMA_AXI_BWEN_32		(1 << 4)
#define DMA_AXI_BWEN_64		(1 << 5)
#define DMA_AXI_BWEN_128	(1 << 6)
#define DMA_AXI_BWEN_256	(1 << 7)
#define DMA_AXI_BWEN_AWW (DMA_AXI_BWEN_4 | DMA_AXI_BWEN_8 | DMA_AXI_BWEN_16 \
			| DMA_AXI_BWEN_32 | DMA_AXI_BWEN_64 \
			| DMA_AXI_BWEN_128 | DMA_AXI_BWEN_256)

stwuct stmmac_pwiv;

/* Pwatfwom data fow pwatfowm device stwuctuwe's pwatfowm_data fiewd */

stwuct stmmac_mdio_bus_data {
	unsigned int phy_mask;
	unsigned int has_xpcs;
	unsigned int xpcs_an_inband;
	int *iwqs;
	int pwobed_phy_iwq;
	boow needs_weset;
};

stwuct stmmac_dma_cfg {
	int pbw;
	int txpbw;
	int wxpbw;
	boow pbwx8;
	int fixed_buwst;
	int mixed_buwst;
	boow aaw;
	boow eame;
	boow muwti_msi_en;
	boow dche;
};

#define AXI_BWEN	7
stwuct stmmac_axi {
	boow axi_wpi_en;
	boow axi_xit_fwm;
	u32 axi_ww_osw_wmt;
	u32 axi_wd_osw_wmt;
	boow axi_kbbe;
	u32 axi_bwen[AXI_BWEN];
	boow axi_fb;
	boow axi_mb;
	boow axi_wb;
};

#define EST_GCW		1024
stwuct stmmac_est {
	stwuct mutex wock;
	int enabwe;
	u32 btw_wesewve[2];
	u32 btw_offset[2];
	u32 btw[2];
	u32 ctw[2];
	u32 tew;
	u32 gcw_unawigned[EST_GCW];
	u32 gcw[EST_GCW];
	u32 gcw_size;
};

stwuct stmmac_wxq_cfg {
	u8 mode_to_use;
	u32 chan;
	u8 pkt_woute;
	boow use_pwio;
	u32 pwio;
};

stwuct stmmac_txq_cfg {
	u32 weight;
	boow coe_unsuppowted;
	u8 mode_to_use;
	/* Cwedit Base Shapew pawametews */
	u32 send_swope;
	u32 idwe_swope;
	u32 high_cwedit;
	u32 wow_cwedit;
	boow use_pwio;
	u32 pwio;
	int tbs_en;
};

/* FPE wink state */
enum stmmac_fpe_state {
	FPE_STATE_OFF = 0,
	FPE_STATE_CAPABWE = 1,
	FPE_STATE_ENTEWING_ON = 2,
	FPE_STATE_ON = 3,
};

/* FPE wink-pawtnew hand-shaking mPacket type */
enum stmmac_mpacket_type {
	MPACKET_VEWIFY = 0,
	MPACKET_WESPONSE = 1,
};

enum stmmac_fpe_task_state_t {
	__FPE_WEMOVING,
	__FPE_TASK_SCHED,
};

stwuct stmmac_fpe_cfg {
	boow enabwe;				/* FPE enabwe */
	boow hs_enabwe;				/* FPE handshake enabwe */
	enum stmmac_fpe_state wp_fpe_state;	/* Wink Pawtnew FPE state */
	enum stmmac_fpe_state wo_fpe_state;	/* Wocaw station FPE state */
	u32 fpe_csw;				/* MAC_FPE_CTWW_STS weg cache */
};

stwuct stmmac_safety_featuwe_cfg {
	u32 tsoee;
	u32 mwxpee;
	u32 mestee;
	u32 mwxee;
	u32 mtxee;
	u32 epsi;
	u32 edpp;
	u32 pwtyen;
	u32 tmouten;
};

/* Addwesses that may be customized by a pwatfowm */
stwuct dwmac4_addws {
	u32 dma_chan;
	u32 dma_chan_offset;
	u32 mtw_chan;
	u32 mtw_chan_offset;
	u32 mtw_ets_ctww;
	u32 mtw_ets_ctww_offset;
	u32 mtw_txq_weight;
	u32 mtw_txq_weight_offset;
	u32 mtw_send_swp_cwed;
	u32 mtw_send_swp_cwed_offset;
	u32 mtw_high_cwed;
	u32 mtw_high_cwed_offset;
	u32 mtw_wow_cwed;
	u32 mtw_wow_cwed_offset;
};

#define STMMAC_FWAG_HAS_INTEGWATED_PCS		BIT(0)
#define STMMAC_FWAG_SPH_DISABWE			BIT(1)
#define STMMAC_FWAG_USE_PHY_WOW			BIT(2)
#define STMMAC_FWAG_HAS_SUN8I			BIT(3)
#define STMMAC_FWAG_TSO_EN			BIT(4)
#define STMMAC_FWAG_SEWDES_UP_AFTEW_PHY_WINKUP	BIT(5)
#define STMMAC_FWAG_VWAN_FAIW_Q_EN		BIT(6)
#define STMMAC_FWAG_MUWTI_MSI_EN		BIT(7)
#define STMMAC_FWAG_EXT_SNAPSHOT_EN		BIT(8)
#define STMMAC_FWAG_INT_SNAPSHOT_EN		BIT(9)
#define STMMAC_FWAG_WX_CWK_WUNS_IN_WPI		BIT(10)
#define STMMAC_FWAG_EN_TX_WPI_CWOCKGATING	BIT(11)
#define STMMAC_FWAG_HWTSTAMP_COWWECT_WATENCY	BIT(12)

stwuct pwat_stmmacenet_data {
	int bus_id;
	int phy_addw;
	/* MAC ----- optionaw PCS ----- SewDes ----- optionaw PHY ----- Media
	 *       ^                               ^
	 * mac_intewface                   phy_intewface
	 *
	 * mac_intewface is the MAC-side intewface, which may be the same
	 * as phy_intewface if thewe is no intewvening PCS. If thewe is a
	 * PCS, then mac_intewface descwibes the intewface mode between the
	 * MAC and PCS, and phy_intewface descwibes the intewface mode
	 * between the PCS and PHY.
	 */
	phy_intewface_t mac_intewface;
	/* phy_intewface is the PHY-side intewface - the intewface used by
	 * an attached PHY.
	 */
	phy_intewface_t phy_intewface;
	stwuct stmmac_mdio_bus_data *mdio_bus_data;
	stwuct device_node *phy_node;
	stwuct fwnode_handwe *powt_node;
	stwuct device_node *mdio_node;
	stwuct stmmac_dma_cfg *dma_cfg;
	stwuct stmmac_est *est;
	stwuct stmmac_fpe_cfg *fpe_cfg;
	stwuct stmmac_safety_featuwe_cfg *safety_feat_cfg;
	int cwk_csw;
	int has_gmac;
	int enh_desc;
	int tx_coe;
	int wx_coe;
	int bugged_jumbo;
	int pmt;
	int fowce_sf_dma_mode;
	int fowce_thwesh_dma_mode;
	int wiwt_off;
	int max_speed;
	int maxmtu;
	int muwticast_fiwtew_bins;
	int unicast_fiwtew_entwies;
	int tx_fifo_size;
	int wx_fifo_size;
	u32 host_dma_width;
	u32 wx_queues_to_use;
	u32 tx_queues_to_use;
	u8 wx_sched_awgowithm;
	u8 tx_sched_awgowithm;
	stwuct stmmac_wxq_cfg wx_queues_cfg[MTW_MAX_WX_QUEUES];
	stwuct stmmac_txq_cfg tx_queues_cfg[MTW_MAX_TX_QUEUES];
	void (*fix_mac_speed)(void *pwiv, unsigned int speed, unsigned int mode);
	int (*fix_soc_weset)(void *pwiv, void __iomem *ioaddw);
	int (*sewdes_powewup)(stwuct net_device *ndev, void *pwiv);
	void (*sewdes_powewdown)(stwuct net_device *ndev, void *pwiv);
	void (*speed_mode_2500)(stwuct net_device *ndev, void *pwiv);
	void (*ptp_cwk_fweq_config)(stwuct stmmac_pwiv *pwiv);
	int (*init)(stwuct pwatfowm_device *pdev, void *pwiv);
	void (*exit)(stwuct pwatfowm_device *pdev, void *pwiv);
	stwuct mac_device_info *(*setup)(void *pwiv);
	int (*cwks_config)(void *pwiv, boow enabwed);
	int (*cwosststamp)(ktime_t *device, stwuct system_countewvaw_t *system,
			   void *ctx);
	void (*dump_debug_wegs)(void *pwiv);
	void *bsp_pwiv;
	stwuct cwk *stmmac_cwk;
	stwuct cwk *pcwk;
	stwuct cwk *cwk_ptp_wef;
	unsigned int cwk_ptp_wate;
	unsigned int cwk_wef_wate;
	unsigned int muwt_fact_100ns;
	s32 ptp_max_adj;
	u32 cdc_ewwow_adj;
	stwuct weset_contwow *stmmac_wst;
	stwuct weset_contwow *stmmac_ahb_wst;
	stwuct stmmac_axi *axi;
	int has_gmac4;
	int wss_en;
	int mac_powt_sew_speed;
	int has_xgmac;
	u8 vwan_faiw_q;
	unsigned int eee_usecs_wate;
	stwuct pci_dev *pdev;
	int int_snapshot_num;
	int msi_mac_vec;
	int msi_wow_vec;
	int msi_wpi_vec;
	int msi_sfty_ce_vec;
	int msi_sfty_ue_vec;
	int msi_wx_base_vec;
	int msi_tx_base_vec;
	const stwuct dwmac4_addws *dwmac4_addws;
	unsigned int fwags;
};
#endif
