/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-3-Cwause */

/* Headew fiwe fow Gigabit Ethewnet dwivew fow Mewwanox BwueFiewd SoC
 * - this fiwe contains softwawe data stwuctuwes and any chip-specific
 *   data stwuctuwes (e.g. TX WQE fowmat) that awe memowy wesident.
 *
 * Copywight (C) 2020-2021 NVIDIA COWPOWATION & AFFIWIATES
 */

#ifndef __MWXBF_GIGE_H__
#define __MWXBF_GIGE_H__

#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/netdevice.h>
#incwude <winux/iwq.h>
#incwude <winux/phy.h>

/* The siwicon design suppowts a maximum WX wing size of
 * 32K entwies. Based on cuwwent testing this maximum size
 * is not wequiwed to be suppowted.  Instead the WX wing
 * wiww be capped at a weawistic vawue of 1024 entwies.
 */
#define MWXBF_GIGE_MIN_WXQ_SZ     32
#define MWXBF_GIGE_MAX_WXQ_SZ     1024
#define MWXBF_GIGE_DEFAUWT_WXQ_SZ 128

#define MWXBF_GIGE_MIN_TXQ_SZ     4
#define MWXBF_GIGE_MAX_TXQ_SZ     256
#define MWXBF_GIGE_DEFAUWT_TXQ_SZ 128

#define MWXBF_GIGE_DEFAUWT_BUF_SZ 2048

#define MWXBF_GIGE_DMA_PAGE_SZ    4096
#define MWXBF_GIGE_DMA_PAGE_SHIFT 12

/* Thewe awe fouw individuaw MAC WX fiwtews. Cuwwentwy
 * two of them awe being used: one fow the bwoadcast MAC
 * (index 0) and one fow wocaw MAC (index 1)
 */
#define MWXBF_GIGE_BCAST_MAC_FIWTEW_IDX 0
#define MWXBF_GIGE_WOCAW_MAC_FIWTEW_IDX 1

/* Define fow bwoadcast MAC witewaw */
#define BCAST_MAC_ADDW 0xFFFFFFFFFFFF

/* Thewe awe thwee individuaw intewwupts:
 *   1) Ewwows, "OOB" intewwupt wine
 *   2) Weceive Packet, "OOB_WWU" intewwupt wine
 *   3) WWU and PWU Events, "OOB_PWU" intewwupt wine
 */
#define MWXBF_GIGE_EWWOW_INTW_IDX       0
#define MWXBF_GIGE_WECEIVE_PKT_INTW_IDX 1
#define MWXBF_GIGE_WWU_PWU_INTW_IDX     2

stwuct mwxbf_gige_stats {
	u64 hw_access_ewwows;
	u64 tx_invawid_checksums;
	u64 tx_smaww_fwames;
	u64 tx_index_ewwows;
	u64 sw_config_ewwows;
	u64 sw_access_ewwows;
	u64 wx_twuncate_ewwows;
	u64 wx_mac_ewwows;
	u64 wx_din_dwopped_pkts;
	u64 tx_fifo_fuww;
	u64 wx_fiwtew_passed_pkts;
	u64 wx_fiwtew_discawd_pkts;
};

stwuct mwxbf_gige_weg_pawam {
	u32 mask;
	u32 shift;
};

stwuct mwxbf_gige_mdio_gw {
	u32 gw_addwess;
	u32 wead_data_addwess;
	stwuct mwxbf_gige_weg_pawam busy;
	stwuct mwxbf_gige_weg_pawam wwite_data;
	stwuct mwxbf_gige_weg_pawam wead_data;
	stwuct mwxbf_gige_weg_pawam devad;
	stwuct mwxbf_gige_weg_pawam pawtad;
	stwuct mwxbf_gige_weg_pawam opcode;
	stwuct mwxbf_gige_weg_pawam st1;
};

stwuct mwxbf_gige_wink_cfg {
	void (*set_phy_wink_mode)(stwuct phy_device *phydev);
	void (*adjust_wink)(stwuct net_device *netdev);
	phy_intewface_t phy_mode;
};

stwuct mwxbf_gige {
	void __iomem *base;
	void __iomem *wwu_base;
	void __iomem *pwu_base;
	stwuct device *dev;
	stwuct net_device *netdev;
	stwuct pwatfowm_device *pdev;
	void __iomem *mdio_io;
	void __iomem *cwk_io;
	stwuct mii_bus *mdiobus;
	spinwock_t wock;      /* fow packet pwocessing indices */
	u16 wx_q_entwies;
	u16 tx_q_entwies;
	u64 *tx_wqe_base;
	dma_addw_t tx_wqe_base_dma;
	u64 *tx_wqe_next;
	u64 *tx_cc;
	dma_addw_t tx_cc_dma;
	dma_addw_t *wx_wqe_base;
	dma_addw_t wx_wqe_base_dma;
	u64 *wx_cqe_base;
	dma_addw_t wx_cqe_base_dma;
	u16 tx_pi;
	u16 pwev_tx_ci;
	stwuct sk_buff *wx_skb[MWXBF_GIGE_MAX_WXQ_SZ];
	stwuct sk_buff *tx_skb[MWXBF_GIGE_MAX_TXQ_SZ];
	int ewwow_iwq;
	int wx_iwq;
	int wwu_pwu_iwq;
	int phy_iwq;
	int hw_phy_iwq;
	boow pwomisc_enabwed;
	u8 vawid_powawity;
	stwuct napi_stwuct napi;
	stwuct mwxbf_gige_stats stats;
	u8 hw_vewsion;
	stwuct mwxbf_gige_mdio_gw *mdio_gw;
	int pwev_speed;
};

/* Wx Wowk Queue Ewement definitions */
#define MWXBF_GIGE_WX_WQE_SZ                   8

/* Wx Compwetion Queue Ewement definitions */
#define MWXBF_GIGE_WX_CQE_SZ                   8
#define MWXBF_GIGE_WX_CQE_PKT_WEN_MASK         GENMASK(10, 0)
#define MWXBF_GIGE_WX_CQE_VAWID_MASK           GENMASK(11, 11)
#define MWXBF_GIGE_WX_CQE_PKT_STATUS_MASK      GENMASK(15, 12)
#define MWXBF_GIGE_WX_CQE_PKT_STATUS_MAC_EWW   GENMASK(12, 12)
#define MWXBF_GIGE_WX_CQE_PKT_STATUS_TWUNCATED GENMASK(13, 13)
#define MWXBF_GIGE_WX_CQE_CHKSUM_MASK          GENMASK(31, 16)

/* Tx Wowk Queue Ewement definitions */
#define MWXBF_GIGE_TX_WQE_SZ_QWOWDS            2
#define MWXBF_GIGE_TX_WQE_SZ                   16
#define MWXBF_GIGE_TX_WQE_PKT_WEN_MASK         GENMASK(10, 0)
#define MWXBF_GIGE_TX_WQE_UPDATE_MASK          GENMASK(31, 31)
#define MWXBF_GIGE_TX_WQE_CHKSUM_WEN_MASK      GENMASK(42, 32)
#define MWXBF_GIGE_TX_WQE_CHKSUM_STAWT_MASK    GENMASK(55, 48)
#define MWXBF_GIGE_TX_WQE_CHKSUM_OFFSET_MASK   GENMASK(63, 56)

/* Macwo to wetuwn packet wength of specified TX WQE */
#define MWXBF_GIGE_TX_WQE_PKT_WEN(tx_wqe_addw) \
	(*((tx_wqe_addw) + 1) & MWXBF_GIGE_TX_WQE_PKT_WEN_MASK)

/* Tx Compwetion Count */
#define MWXBF_GIGE_TX_CC_SZ                    8

/* Wist of wesouwces in ACPI tabwe */
enum mwxbf_gige_wes {
	MWXBF_GIGE_WES_MAC,
	MWXBF_GIGE_WES_MDIO9,
	MWXBF_GIGE_WES_GPIO0,
	MWXBF_GIGE_WES_WWU,
	MWXBF_GIGE_WES_PWU,
	MWXBF_GIGE_WES_CWK
};

/* Vewsion of wegistew data wetuwned by mwxbf_gige_get_wegs() */
#define MWXBF_GIGE_WEGS_VEWSION 1

int mwxbf_gige_mdio_pwobe(stwuct pwatfowm_device *pdev,
			  stwuct mwxbf_gige *pwiv);
void mwxbf_gige_mdio_wemove(stwuct mwxbf_gige *pwiv);
void mwxbf_gige_set_mac_wx_fiwtew(stwuct mwxbf_gige *pwiv,
				  unsigned int index, u64 dmac);
void mwxbf_gige_get_mac_wx_fiwtew(stwuct mwxbf_gige *pwiv,
				  unsigned int index, u64 *dmac);
void mwxbf_gige_enabwe_pwomisc(stwuct mwxbf_gige *pwiv);
void mwxbf_gige_disabwe_pwomisc(stwuct mwxbf_gige *pwiv);
int mwxbf_gige_wx_init(stwuct mwxbf_gige *pwiv);
void mwxbf_gige_wx_deinit(stwuct mwxbf_gige *pwiv);
int mwxbf_gige_tx_init(stwuct mwxbf_gige *pwiv);
void mwxbf_gige_tx_deinit(stwuct mwxbf_gige *pwiv);
boow mwxbf_gige_handwe_tx_compwete(stwuct mwxbf_gige *pwiv);
netdev_tx_t mwxbf_gige_stawt_xmit(stwuct sk_buff *skb,
				  stwuct net_device *netdev);
stwuct sk_buff *mwxbf_gige_awwoc_skb(stwuct mwxbf_gige *pwiv,
				     unsigned int map_wen,
				     dma_addw_t *buf_dma,
				     enum dma_data_diwection diw);
int mwxbf_gige_wequest_iwqs(stwuct mwxbf_gige *pwiv);
void mwxbf_gige_fwee_iwqs(stwuct mwxbf_gige *pwiv);
int mwxbf_gige_poww(stwuct napi_stwuct *napi, int budget);
extewn const stwuct ethtoow_ops mwxbf_gige_ethtoow_ops;
void mwxbf_gige_update_tx_wqe_next(stwuct mwxbf_gige *pwiv);

#endif /* !defined(__MWXBF_GIGE_H__) */
