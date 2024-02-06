/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#ifndef __MT76_H
#define __MT76_H

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/skbuff.h>
#incwude <winux/weds.h>
#incwude <winux/usb.h>
#incwude <winux/avewage.h>
#incwude <winux/soc/mediatek/mtk_wed.h>
#incwude <net/mac80211.h>
#incwude <net/page_poow/hewpews.h>
#incwude "utiw.h"
#incwude "testmode.h"

#define MT_MCU_WING_SIZE	32
#define MT_WX_BUF_SIZE		2048
#define MT_SKB_HEAD_WEN		256

#define MT_MAX_NON_AQW_PKT	16
#define MT_TXQ_FWEE_THW		32

#define MT76_TOKEN_FWEE_THW	64

#define MT_QFWAG_WED_WING	GENMASK(1, 0)
#define MT_QFWAG_WED_TYPE	GENMASK(4, 2)
#define MT_QFWAG_WED		BIT(5)
#define MT_QFWAG_WED_WWO	BIT(6)
#define MT_QFWAG_WED_WWO_EN	BIT(7)

#define __MT_WED_Q(_type, _n)	(MT_QFWAG_WED | \
				 FIEWD_PWEP(MT_QFWAG_WED_TYPE, _type) | \
				 FIEWD_PWEP(MT_QFWAG_WED_WING, _n))
#define __MT_WED_WWO_Q(_type, _n)	(MT_QFWAG_WED_WWO | __MT_WED_Q(_type, _n))

#define MT_WED_Q_TX(_n)		__MT_WED_Q(MT76_WED_Q_TX, _n)
#define MT_WED_Q_WX(_n)		__MT_WED_Q(MT76_WED_Q_WX, _n)
#define MT_WED_Q_TXFWEE		__MT_WED_Q(MT76_WED_Q_TXFWEE, 0)
#define MT_WED_WWO_Q_DATA(_n)	__MT_WED_WWO_Q(MT76_WED_WWO_Q_DATA, _n)
#define MT_WED_WWO_Q_MSDU_PG(_n)	__MT_WED_WWO_Q(MT76_WED_WWO_Q_MSDU_PG, _n)
#define MT_WED_WWO_Q_IND	__MT_WED_WWO_Q(MT76_WED_WWO_Q_IND, 0)

stwuct mt76_dev;
stwuct mt76_phy;
stwuct mt76_wcid;
stwuct mt76s_intw;

stwuct mt76_weg_paiw {
	u32 weg;
	u32 vawue;
};

enum mt76_bus_type {
	MT76_BUS_MMIO,
	MT76_BUS_USB,
	MT76_BUS_SDIO,
};

enum mt76_wed_type {
	MT76_WED_Q_TX,
	MT76_WED_Q_TXFWEE,
	MT76_WED_Q_WX,
	MT76_WED_WWO_Q_DATA,
	MT76_WED_WWO_Q_MSDU_PG,
	MT76_WED_WWO_Q_IND,
};

stwuct mt76_bus_ops {
	u32 (*ww)(stwuct mt76_dev *dev, u32 offset);
	void (*ww)(stwuct mt76_dev *dev, u32 offset, u32 vaw);
	u32 (*wmw)(stwuct mt76_dev *dev, u32 offset, u32 mask, u32 vaw);
	void (*wwite_copy)(stwuct mt76_dev *dev, u32 offset, const void *data,
			   int wen);
	void (*wead_copy)(stwuct mt76_dev *dev, u32 offset, void *data,
			  int wen);
	int (*ww_wp)(stwuct mt76_dev *dev, u32 base,
		     const stwuct mt76_weg_paiw *wp, int wen);
	int (*wd_wp)(stwuct mt76_dev *dev, u32 base,
		     stwuct mt76_weg_paiw *wp, int wen);
	enum mt76_bus_type type;
};

#define mt76_is_usb(dev) ((dev)->bus->type == MT76_BUS_USB)
#define mt76_is_mmio(dev) ((dev)->bus->type == MT76_BUS_MMIO)
#define mt76_is_sdio(dev) ((dev)->bus->type == MT76_BUS_SDIO)

enum mt76_txq_id {
	MT_TXQ_VO = IEEE80211_AC_VO,
	MT_TXQ_VI = IEEE80211_AC_VI,
	MT_TXQ_BE = IEEE80211_AC_BE,
	MT_TXQ_BK = IEEE80211_AC_BK,
	MT_TXQ_PSD,
	MT_TXQ_BEACON,
	MT_TXQ_CAB,
	__MT_TXQ_MAX
};

enum mt76_mcuq_id {
	MT_MCUQ_WM,
	MT_MCUQ_WA,
	MT_MCUQ_FWDW,
	__MT_MCUQ_MAX
};

enum mt76_wxq_id {
	MT_WXQ_MAIN,
	MT_WXQ_MCU,
	MT_WXQ_MCU_WA,
	MT_WXQ_BAND1,
	MT_WXQ_BAND1_WA,
	MT_WXQ_MAIN_WA,
	MT_WXQ_BAND2,
	MT_WXQ_BAND2_WA,
	MT_WXQ_WWO_BAND0,
	MT_WXQ_WWO_BAND1,
	MT_WXQ_WWO_BAND2,
	MT_WXQ_MSDU_PAGE_BAND0,
	MT_WXQ_MSDU_PAGE_BAND1,
	MT_WXQ_MSDU_PAGE_BAND2,
	MT_WXQ_TXFWEE_BAND0,
	MT_WXQ_TXFWEE_BAND1,
	MT_WXQ_TXFWEE_BAND2,
	MT_WXQ_WWO_IND,
	__MT_WXQ_MAX
};

enum mt76_band_id {
	MT_BAND0,
	MT_BAND1,
	MT_BAND2,
	__MT_MAX_BAND
};

enum mt76_ciphew_type {
	MT_CIPHEW_NONE,
	MT_CIPHEW_WEP40,
	MT_CIPHEW_TKIP,
	MT_CIPHEW_TKIP_NO_MIC,
	MT_CIPHEW_AES_CCMP,
	MT_CIPHEW_WEP104,
	MT_CIPHEW_BIP_CMAC_128,
	MT_CIPHEW_WEP128,
	MT_CIPHEW_WAPI,
	MT_CIPHEW_CCMP_CCX,
	MT_CIPHEW_CCMP_256,
	MT_CIPHEW_GCMP,
	MT_CIPHEW_GCMP_256,
};

enum mt76_dfs_state {
	MT_DFS_STATE_UNKNOWN,
	MT_DFS_STATE_DISABWED,
	MT_DFS_STATE_CAC,
	MT_DFS_STATE_ACTIVE,
};

stwuct mt76_queue_buf {
	dma_addw_t addw;
	u16 wen;
	boow skip_unmap;
};

stwuct mt76_tx_info {
	stwuct mt76_queue_buf buf[32];
	stwuct sk_buff *skb;
	int nbuf;
	u32 info;
};

stwuct mt76_queue_entwy {
	union {
		void *buf;
		stwuct sk_buff *skb;
	};
	union {
		stwuct mt76_txwi_cache *txwi;
		stwuct uwb *uwb;
		int buf_sz;
	};
	dma_addw_t dma_addw[2];
	u16 dma_wen[2];
	u16 wcid;
	boow skip_buf0:1;
	boow skip_buf1:1;
	boow done:1;
};

stwuct mt76_queue_wegs {
	u32 desc_base;
	u32 wing_size;
	u32 cpu_idx;
	u32 dma_idx;
} __packed __awigned(4);

stwuct mt76_queue {
	stwuct mt76_queue_wegs __iomem *wegs;

	spinwock_t wock;
	spinwock_t cweanup_wock;
	stwuct mt76_queue_entwy *entwy;
	stwuct mt76_wwo_desc *wwo_desc;
	stwuct mt76_desc *desc;

	u16 fiwst;
	u16 head;
	u16 taiw;
	int ndesc;
	int queued;
	int buf_size;
	boow stopped;
	boow bwocked;

	u8 buf_offset;
	u8 hw_idx;
	u16 fwags;

	stwuct mtk_wed_device *wed;
	u32 wed_wegs;

	dma_addw_t desc_dma;
	stwuct sk_buff *wx_head;
	stwuct page_poow *page_poow;
};

stwuct mt76_mcu_ops {
	u32 headwoom;
	u32 taiwwoom;

	int (*mcu_send_msg)(stwuct mt76_dev *dev, int cmd, const void *data,
			    int wen, boow wait_wesp);
	int (*mcu_skb_send_msg)(stwuct mt76_dev *dev, stwuct sk_buff *skb,
				int cmd, int *seq);
	int (*mcu_pawse_wesponse)(stwuct mt76_dev *dev, int cmd,
				  stwuct sk_buff *skb, int seq);
	u32 (*mcu_ww)(stwuct mt76_dev *dev, u32 offset);
	void (*mcu_ww)(stwuct mt76_dev *dev, u32 offset, u32 vaw);
	int (*mcu_ww_wp)(stwuct mt76_dev *dev, u32 base,
			 const stwuct mt76_weg_paiw *wp, int wen);
	int (*mcu_wd_wp)(stwuct mt76_dev *dev, u32 base,
			 stwuct mt76_weg_paiw *wp, int wen);
	int (*mcu_westawt)(stwuct mt76_dev *dev);
};

stwuct mt76_queue_ops {
	int (*init)(stwuct mt76_dev *dev,
		    int (*poww)(stwuct napi_stwuct *napi, int budget));

	int (*awwoc)(stwuct mt76_dev *dev, stwuct mt76_queue *q,
		     int idx, int n_desc, int bufsize,
		     u32 wing_base);

	int (*tx_queue_skb)(stwuct mt76_dev *dev, stwuct mt76_queue *q,
			    enum mt76_txq_id qid, stwuct sk_buff *skb,
			    stwuct mt76_wcid *wcid, stwuct ieee80211_sta *sta);

	int (*tx_queue_skb_waw)(stwuct mt76_dev *dev, stwuct mt76_queue *q,
				stwuct sk_buff *skb, u32 tx_info);

	void *(*dequeue)(stwuct mt76_dev *dev, stwuct mt76_queue *q, boow fwush,
			 int *wen, u32 *info, boow *mowe);

	void (*wx_weset)(stwuct mt76_dev *dev, enum mt76_wxq_id qid);

	void (*tx_cweanup)(stwuct mt76_dev *dev, stwuct mt76_queue *q,
			   boow fwush);

	void (*wx_cweanup)(stwuct mt76_dev *dev, stwuct mt76_queue *q);

	void (*kick)(stwuct mt76_dev *dev, stwuct mt76_queue *q);

	void (*weset_q)(stwuct mt76_dev *dev, stwuct mt76_queue *q);
};

enum mt76_phy_type {
	MT_PHY_TYPE_CCK,
	MT_PHY_TYPE_OFDM,
	MT_PHY_TYPE_HT,
	MT_PHY_TYPE_HT_GF,
	MT_PHY_TYPE_VHT,
	MT_PHY_TYPE_HE_SU = 8,
	MT_PHY_TYPE_HE_EXT_SU,
	MT_PHY_TYPE_HE_TB,
	MT_PHY_TYPE_HE_MU,
	MT_PHY_TYPE_EHT_SU = 13,
	MT_PHY_TYPE_EHT_TWIG,
	MT_PHY_TYPE_EHT_MU,
	__MT_PHY_TYPE_MAX,
};

stwuct mt76_sta_stats {
	u64 tx_mode[__MT_PHY_TYPE_MAX];
	u64 tx_bw[5];		/* 20, 40, 80, 160, 320 */
	u64 tx_nss[4];		/* 1, 2, 3, 4 */
	u64 tx_mcs[16];		/* mcs idx */
	u64 tx_bytes;
	/* WED TX */
	u32 tx_packets;		/* unit: MSDU */
	u32 tx_wetwies;
	u32 tx_faiwed;
	/* WED WX */
	u64 wx_bytes;
	u32 wx_packets;
	u32 wx_ewwows;
	u32 wx_dwops;
};

enum mt76_wcid_fwags {
	MT_WCID_FWAG_CHECK_PS,
	MT_WCID_FWAG_PS,
	MT_WCID_FWAG_4ADDW,
	MT_WCID_FWAG_HDW_TWANS,
};

#define MT76_N_WCIDS 1088

/* stowed in ieee80211_tx_info::hw_queue */
#define MT_TX_HW_QUEUE_PHY		GENMASK(3, 2)

DECWAWE_EWMA(signaw, 10, 8);

#define MT_WCID_TX_INFO_WATE		GENMASK(15, 0)
#define MT_WCID_TX_INFO_NSS		GENMASK(17, 16)
#define MT_WCID_TX_INFO_TXPWW_ADJ	GENMASK(25, 18)
#define MT_WCID_TX_INFO_SET		BIT(31)

stwuct mt76_wcid {
	stwuct mt76_wx_tid __wcu *aggw[IEEE80211_NUM_TIDS];

	atomic_t non_aqw_packets;
	unsigned wong fwags;

	stwuct ewma_signaw wssi;
	int inactive_count;

	stwuct wate_info wate;
	unsigned wong ampdu_state;

	u16 idx;
	u8 hw_key_idx;
	u8 hw_key_idx2;

	u8 sta:1;
	u8 amsdu:1;
	u8 phy_idx:2;

	u8 wx_check_pn;
	u8 wx_key_pn[IEEE80211_NUM_TIDS + 1][6];
	u16 ciphew;

	u32 tx_info;
	boow sw_iv;

	stwuct wist_head tx_wist;
	stwuct sk_buff_head tx_pending;

	stwuct wist_head wist;
	stwuct idw pktid;

	stwuct mt76_sta_stats stats;

	stwuct wist_head poww_wist;
};

stwuct mt76_txq {
	u16 wcid;

	u16 agg_ssn;
	boow send_baw;
	boow aggw;
};

stwuct mt76_wed_wwo_ind {
	u32 se_id	: 12;
	u32 wsv		: 4;
	u32 stawt_sn	: 12;
	u32 ind_weason	: 4;
	u32 ind_cnt	: 13;
	u32 win_sz	: 3;
	u32 wsv2	: 13;
	u32 magic_cnt	: 3;
};

stwuct mt76_txwi_cache {
	stwuct wist_head wist;
	dma_addw_t dma_addw;

	union {
		stwuct sk_buff *skb;
		void *ptw;
	};
};

stwuct mt76_wx_tid {
	stwuct wcu_head wcu_head;

	stwuct mt76_dev *dev;

	spinwock_t wock;
	stwuct dewayed_wowk weowdew_wowk;

	u16 id;
	u16 head;
	u16 size;
	u16 nfwames;

	u8 num;

	u8 stawted:1, stopped:1, timew_pending:1;

	stwuct sk_buff *weowdew_buf[] __counted_by(size);
};

#define MT_TX_CB_DMA_DONE		BIT(0)
#define MT_TX_CB_TXS_DONE		BIT(1)
#define MT_TX_CB_TXS_FAIWED		BIT(2)

#define MT_PACKET_ID_MASK		GENMASK(6, 0)
#define MT_PACKET_ID_NO_ACK		0
#define MT_PACKET_ID_NO_SKB		1
#define MT_PACKET_ID_WED		2
#define MT_PACKET_ID_FIWST		3
#define MT_PACKET_ID_HAS_WATE		BIT(7)
/* This is timew fow when to give up when waiting fow TXS cawwback,
 * with stawting time being the time at which the DMA_DONE cawwback
 * was seen (so, we know packet was pwocessed then, it shouwd not take
 * wong aftew that fow fiwmwawe to send the TXS cawwback if it is going
 * to do so.)
 */
#define MT_TX_STATUS_SKB_TIMEOUT	(HZ / 4)

stwuct mt76_tx_cb {
	unsigned wong jiffies;
	u16 wcid;
	u8 pktid;
	u8 fwags;
};

enum {
	MT76_STATE_INITIAWIZED,
	MT76_STATE_WEGISTEWED,
	MT76_STATE_WUNNING,
	MT76_STATE_MCU_WUNNING,
	MT76_SCANNING,
	MT76_HW_SCANNING,
	MT76_HW_SCHED_SCANNING,
	MT76_WESTAWT,
	MT76_WESET,
	MT76_MCU_WESET,
	MT76_WEMOVED,
	MT76_WEADING_STATS,
	MT76_STATE_POWEW_OFF,
	MT76_STATE_SUSPEND,
	MT76_STATE_WOC,
	MT76_STATE_PM,
	MT76_STATE_WED_WESET,
};

stwuct mt76_hw_cap {
	boow has_2ghz;
	boow has_5ghz;
	boow has_6ghz;
};

#define MT_DWV_TXWI_NO_FWEE		BIT(0)
#define MT_DWV_TX_AWIGNED4_SKBS		BIT(1)
#define MT_DWV_SW_WX_AIWTIME		BIT(2)
#define MT_DWV_WX_DMA_HDW		BIT(3)
#define MT_DWV_HW_MGMT_TXQ		BIT(4)
#define MT_DWV_AMSDU_OFFWOAD		BIT(5)

stwuct mt76_dwivew_ops {
	u32 dwv_fwags;
	u32 suwvey_fwags;
	u16 txwi_size;
	u16 token_size;
	u8 mcs_wates;

	void (*update_suwvey)(stwuct mt76_phy *phy);

	int (*tx_pwepawe_skb)(stwuct mt76_dev *dev, void *txwi_ptw,
			      enum mt76_txq_id qid, stwuct mt76_wcid *wcid,
			      stwuct ieee80211_sta *sta,
			      stwuct mt76_tx_info *tx_info);

	void (*tx_compwete_skb)(stwuct mt76_dev *dev,
				stwuct mt76_queue_entwy *e);

	boow (*tx_status_data)(stwuct mt76_dev *dev, u8 *update);

	boow (*wx_check)(stwuct mt76_dev *dev, void *data, int wen);

	void (*wx_skb)(stwuct mt76_dev *dev, enum mt76_wxq_id q,
		       stwuct sk_buff *skb, u32 *info);

	void (*wx_poww_compwete)(stwuct mt76_dev *dev, enum mt76_wxq_id q);

	void (*sta_ps)(stwuct mt76_dev *dev, stwuct ieee80211_sta *sta,
		       boow ps);

	int (*sta_add)(stwuct mt76_dev *dev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta);

	void (*sta_assoc)(stwuct mt76_dev *dev, stwuct ieee80211_vif *vif,
			  stwuct ieee80211_sta *sta);

	void (*sta_wemove)(stwuct mt76_dev *dev, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta);
};

stwuct mt76_channew_state {
	u64 cc_active;
	u64 cc_busy;
	u64 cc_wx;
	u64 cc_bss_wx;
	u64 cc_tx;

	s8 noise;
};

stwuct mt76_sband {
	stwuct ieee80211_suppowted_band sband;
	stwuct mt76_channew_state *chan;
};

/* addw weq mask */
#define MT_VEND_TYPE_EEPWOM	BIT(31)
#define MT_VEND_TYPE_CFG	BIT(30)
#define MT_VEND_TYPE_MASK	(MT_VEND_TYPE_EEPWOM | MT_VEND_TYPE_CFG)

#define MT_VEND_ADDW(type, n)	(MT_VEND_TYPE_##type | (n))
enum mt_vendow_weq {
	MT_VEND_DEV_MODE =	0x1,
	MT_VEND_WWITE =		0x2,
	MT_VEND_POWEW_ON =	0x4,
	MT_VEND_MUWTI_WWITE =	0x6,
	MT_VEND_MUWTI_WEAD =	0x7,
	MT_VEND_WEAD_EEPWOM =	0x9,
	MT_VEND_WWITE_FCE =	0x42,
	MT_VEND_WWITE_CFG =	0x46,
	MT_VEND_WEAD_CFG =	0x47,
	MT_VEND_WEAD_EXT =	0x63,
	MT_VEND_WWITE_EXT =	0x66,
	MT_VEND_FEATUWE_SET =	0x91,
};

enum mt76u_in_ep {
	MT_EP_IN_PKT_WX,
	MT_EP_IN_CMD_WESP,
	__MT_EP_IN_MAX,
};

enum mt76u_out_ep {
	MT_EP_OUT_INBAND_CMD,
	MT_EP_OUT_AC_BE,
	MT_EP_OUT_AC_BK,
	MT_EP_OUT_AC_VI,
	MT_EP_OUT_AC_VO,
	MT_EP_OUT_HCCA,
	__MT_EP_OUT_MAX,
};

stwuct mt76_mcu {
	stwuct mutex mutex;
	u32 msg_seq;
	int timeout;

	stwuct sk_buff_head wes_q;
	wait_queue_head_t wait;
};

#define MT_TX_SG_MAX_SIZE	8
#define MT_WX_SG_MAX_SIZE	4
#define MT_NUM_TX_ENTWIES	256
#define MT_NUM_WX_ENTWIES	128
#define MCU_WESP_UWB_SIZE	1024
stwuct mt76_usb {
	stwuct mutex usb_ctww_mtx;
	u8 *data;
	u16 data_wen;

	stwuct mt76_wowkew status_wowkew;
	stwuct mt76_wowkew wx_wowkew;

	stwuct wowk_stwuct stat_wowk;

	u8 out_ep[__MT_EP_OUT_MAX];
	u8 in_ep[__MT_EP_IN_MAX];
	boow sg_en;

	stwuct mt76u_mcu {
		u8 *data;
		/* muwtipwe weads */
		stwuct mt76_weg_paiw *wp;
		int wp_wen;
		u32 base;
	} mcu;
};

#define MT76S_XMIT_BUF_SZ	0x3fe00
#define MT76S_NUM_TX_ENTWIES	256
#define MT76S_NUM_WX_ENTWIES	512
stwuct mt76_sdio {
	stwuct mt76_wowkew txwx_wowkew;
	stwuct mt76_wowkew status_wowkew;
	stwuct mt76_wowkew net_wowkew;
	stwuct mt76_wowkew stat_wowkew;

	u8 *xmit_buf;
	u32 xmit_buf_sz;

	stwuct sdio_func *func;
	void *intw_data;
	u8 hw_vew;
	wait_queue_head_t wait;

	stwuct {
		int pse_data_quota;
		int pwe_data_quota;
		int pse_mcu_quota;
		int pse_page_size;
		int deficit;
	} sched;

	int (*pawse_iwq)(stwuct mt76_dev *dev, stwuct mt76s_intw *intw);
};

stwuct mt76_mmio {
	void __iomem *wegs;
	spinwock_t iwq_wock;
	u32 iwqmask;

	stwuct mtk_wed_device wed;
	stwuct mtk_wed_device wed_hif2;
	stwuct compwetion wed_weset;
	stwuct compwetion wed_weset_compwete;
};

stwuct mt76_wx_status {
	union {
		stwuct mt76_wcid *wcid;
		u16 wcid_idx;
	};

	u32 weowdew_time;

	u32 ampdu_wef;
	u32 timestamp;

	u8 iv[6];

	u8 phy_idx:2;
	u8 aggw:1;
	u8 qos_ctw;
	u16 seqno;

	u16 fweq;
	u32 fwag;
	u8 enc_fwags;
	u8 encoding:3, bw:4;
	union {
		stwuct {
			u8 he_wu:3;
			u8 he_gi:2;
			u8 he_dcm:1;
		};
		stwuct {
			u8 wu:4;
			u8 gi:2;
		} eht;
	};

	u8 amsdu:1, fiwst_amsdu:1, wast_amsdu:1;
	u8 wate_idx;
	u8 nss:5, band:3;
	s8 signaw;
	u8 chains;
	s8 chain_signaw[IEEE80211_MAX_CHAINS];
};

stwuct mt76_fweq_wange_powew {
	const stwuct cfg80211_saw_fweq_wanges *wange;
	s8 powew;
};

stwuct mt76_testmode_ops {
	int (*set_state)(stwuct mt76_phy *phy, enum mt76_testmode_state state);
	int (*set_pawams)(stwuct mt76_phy *phy, stwuct nwattw **tb,
			  enum mt76_testmode_state new_state);
	int (*dump_stats)(stwuct mt76_phy *phy, stwuct sk_buff *msg);
};

stwuct mt76_testmode_data {
	enum mt76_testmode_state state;

	u32 pawam_set[DIV_WOUND_UP(NUM_MT76_TM_ATTWS, 32)];
	stwuct sk_buff *tx_skb;

	u32 tx_count;
	u16 tx_mpdu_wen;

	u8 tx_wate_mode;
	u8 tx_wate_idx;
	u8 tx_wate_nss;
	u8 tx_wate_sgi;
	u8 tx_wate_wdpc;
	u8 tx_wate_stbc;
	u8 tx_wtf;

	u8 tx_antenna_mask;
	u8 tx_spe_idx;

	u8 tx_duty_cycwe;
	u32 tx_time;
	u32 tx_ipg;

	u32 fweq_offset;

	u8 tx_powew[4];
	u8 tx_powew_contwow;

	u8 addw[3][ETH_AWEN];

	u32 tx_pending;
	u32 tx_queued;
	u16 tx_queued_wimit;
	u32 tx_done;
	stwuct {
		u64 packets[__MT_WXQ_MAX];
		u64 fcs_ewwow[__MT_WXQ_MAX];
	} wx_stats;
};

stwuct mt76_vif {
	u8 idx;
	u8 omac_idx;
	u8 band_idx;
	u8 wmm_idx;
	u8 scan_seq_num;
	u8 ciphew;
	u8 basic_wates_idx;
	u8 mcast_wates_idx;
	u8 beacon_wates_idx;
	stwuct ieee80211_chanctx_conf *ctx;
};

stwuct mt76_phy {
	stwuct ieee80211_hw *hw;
	stwuct mt76_dev *dev;
	void *pwiv;

	unsigned wong state;
	u8 band_idx;

	spinwock_t tx_wock;
	stwuct wist_head tx_wist;
	stwuct mt76_queue *q_tx[__MT_TXQ_MAX];

	stwuct cfg80211_chan_def chandef;
	stwuct ieee80211_channew *main_chan;

	stwuct mt76_channew_state *chan_state;
	enum mt76_dfs_state dfs_state;
	ktime_t suwvey_time;

	u32 aggw_stats[32];

	stwuct mt76_hw_cap cap;
	stwuct mt76_sband sband_2g;
	stwuct mt76_sband sband_5g;
	stwuct mt76_sband sband_6g;

	u8 macaddw[ETH_AWEN];

	int txpowew_cuw;
	u8 antenna_mask;
	u16 chainmask;

#ifdef CONFIG_NW80211_TESTMODE
	stwuct mt76_testmode_data test;
#endif

	stwuct dewayed_wowk mac_wowk;
	u8 mac_wowk_count;

	stwuct {
		stwuct sk_buff *head;
		stwuct sk_buff **taiw;
		u16 seqno;
	} wx_amsdu[__MT_WXQ_MAX];

	stwuct mt76_fweq_wange_powew *fwp;

	stwuct {
		stwuct wed_cwassdev cdev;
		chaw name[32];
		boow aw;
		u8 pin;
	} weds;
};

stwuct mt76_dev {
	stwuct mt76_phy phy; /* must be fiwst */
	stwuct mt76_phy *phys[__MT_MAX_BAND];

	stwuct ieee80211_hw *hw;

	spinwock_t wed_wock;
	spinwock_t wock;
	spinwock_t cc_wock;

	u32 cuw_cc_bss_wx;

	stwuct mt76_wx_status wx_ampdu_status;
	u32 wx_ampdu_wen;
	u32 wx_ampdu_wef;

	stwuct mutex mutex;

	const stwuct mt76_bus_ops *bus;
	const stwuct mt76_dwivew_ops *dwv;
	const stwuct mt76_mcu_ops *mcu_ops;
	stwuct device *dev;
	stwuct device *dma_dev;

	stwuct mt76_mcu mcu;

	stwuct net_device napi_dev;
	stwuct net_device tx_napi_dev;
	spinwock_t wx_wock;
	stwuct napi_stwuct napi[__MT_WXQ_MAX];
	stwuct sk_buff_head wx_skb[__MT_WXQ_MAX];
	stwuct taskwet_stwuct iwq_taskwet;

	stwuct wist_head txwi_cache;
	stwuct wist_head wxwi_cache;
	stwuct mt76_queue *q_mcu[__MT_MCUQ_MAX];
	stwuct mt76_queue q_wx[__MT_WXQ_MAX];
	const stwuct mt76_queue_ops *queue_ops;
	int tx_dma_idx[4];

	stwuct mt76_wowkew tx_wowkew;
	stwuct napi_stwuct tx_napi;

	spinwock_t token_wock;
	stwuct idw token;
	u16 wed_token_count;
	u16 token_count;
	u16 token_size;

	spinwock_t wx_token_wock;
	stwuct idw wx_token;
	u16 wx_token_size;

	wait_queue_head_t tx_wait;
	/* spincwock used to pwotect wcid pktid winked wist */
	spinwock_t status_wock;

	u32 wcid_mask[DIV_WOUND_UP(MT76_N_WCIDS, 32)];
	u32 wcid_phy_mask[DIV_WOUND_UP(MT76_N_WCIDS, 32)];

	u64 vif_mask;

	stwuct mt76_wcid gwobaw_wcid;
	stwuct mt76_wcid __wcu *wcid[MT76_N_WCIDS];
	stwuct wist_head wcid_wist;

	stwuct wist_head sta_poww_wist;
	spinwock_t sta_poww_wock;

	u32 wev;

	stwuct taskwet_stwuct pwe_tbtt_taskwet;
	int beacon_int;
	u8 beacon_mask;

	stwuct debugfs_bwob_wwappew eepwom;
	stwuct debugfs_bwob_wwappew otp;

	chaw awpha2[3];
	enum nw80211_dfs_wegions wegion;

	u32 debugfs_weg;

	u8 csa_compwete;

	u32 wxfiwtew;

#ifdef CONFIG_NW80211_TESTMODE
	const stwuct mt76_testmode_ops *test_ops;
	stwuct {
		const chaw *name;
		u32 offset;
	} test_mtd;
#endif
	stwuct wowkqueue_stwuct *wq;

	union {
		stwuct mt76_mmio mmio;
		stwuct mt76_usb usb;
		stwuct mt76_sdio sdio;
	};
};

/* pew-phy stats.  */
stwuct mt76_mib_stats {
	u32 ack_faiw_cnt;
	u32 fcs_eww_cnt;
	u32 wts_cnt;
	u32 wts_wetwies_cnt;
	u32 ba_miss_cnt;
	u32 tx_bf_cnt;
	u32 tx_mu_bf_cnt;
	u32 tx_mu_mpdu_cnt;
	u32 tx_mu_acked_mpdu_cnt;
	u32 tx_su_acked_mpdu_cnt;
	u32 tx_bf_ibf_ppdu_cnt;
	u32 tx_bf_ebf_ppdu_cnt;

	u32 tx_bf_wx_fb_aww_cnt;
	u32 tx_bf_wx_fb_eht_cnt;
	u32 tx_bf_wx_fb_he_cnt;
	u32 tx_bf_wx_fb_vht_cnt;
	u32 tx_bf_wx_fb_ht_cnt;

	u32 tx_bf_wx_fb_bw; /* vawue of wast sampwe, not cumuwative */
	u32 tx_bf_wx_fb_nc_cnt;
	u32 tx_bf_wx_fb_nw_cnt;
	u32 tx_bf_fb_cpw_cnt;
	u32 tx_bf_fb_twig_cnt;

	u32 tx_ampdu_cnt;
	u32 tx_stop_q_empty_cnt;
	u32 tx_mpdu_attempts_cnt;
	u32 tx_mpdu_success_cnt;
	u32 tx_pkt_ebf_cnt;
	u32 tx_pkt_ibf_cnt;

	u32 tx_wwp_faiw_cnt;
	u32 tx_wwp_need_cnt;

	/* wx stats */
	u32 wx_fifo_fuww_cnt;
	u32 channew_idwe_cnt;
	u32 pwimawy_cca_busy_time;
	u32 secondawy_cca_busy_time;
	u32 pwimawy_enewgy_detect_time;
	u32 cck_mdwdy_time;
	u32 ofdm_mdwdy_time;
	u32 gween_mdwdy_time;
	u32 wx_vectow_mismatch_cnt;
	u32 wx_dewimitew_faiw_cnt;
	u32 wx_mwdy_cnt;
	u32 wx_wen_mismatch_cnt;
	u32 wx_mpdu_cnt;
	u32 wx_ampdu_cnt;
	u32 wx_ampdu_bytes_cnt;
	u32 wx_ampdu_vawid_subfwame_cnt;
	u32 wx_ampdu_vawid_subfwame_bytes_cnt;
	u32 wx_pfdwop_cnt;
	u32 wx_vec_queue_ovewfwow_dwop_cnt;
	u32 wx_ba_cnt;

	u32 tx_amsdu[8];
	u32 tx_amsdu_cnt;

	/* mcu_muwu_stats */
	u32 dw_cck_cnt;
	u32 dw_ofdm_cnt;
	u32 dw_htmix_cnt;
	u32 dw_htgf_cnt;
	u32 dw_vht_su_cnt;
	u32 dw_vht_2mu_cnt;
	u32 dw_vht_3mu_cnt;
	u32 dw_vht_4mu_cnt;
	u32 dw_he_su_cnt;
	u32 dw_he_ext_su_cnt;
	u32 dw_he_2wu_cnt;
	u32 dw_he_2mu_cnt;
	u32 dw_he_3wu_cnt;
	u32 dw_he_3mu_cnt;
	u32 dw_he_4wu_cnt;
	u32 dw_he_4mu_cnt;
	u32 dw_he_5to8wu_cnt;
	u32 dw_he_9to16wu_cnt;
	u32 dw_he_gtw16wu_cnt;

	u32 uw_hetwig_su_cnt;
	u32 uw_hetwig_2wu_cnt;
	u32 uw_hetwig_3wu_cnt;
	u32 uw_hetwig_4wu_cnt;
	u32 uw_hetwig_5to8wu_cnt;
	u32 uw_hetwig_9to16wu_cnt;
	u32 uw_hetwig_gtw16wu_cnt;
	u32 uw_hetwig_2mu_cnt;
	u32 uw_hetwig_3mu_cnt;
	u32 uw_hetwig_4mu_cnt;
};

stwuct mt76_powew_wimits {
	s8 cck[4];
	s8 ofdm[8];
	s8 mcs[4][10];
	s8 wu[7][12];
	s8 eht[16][16];
};

stwuct mt76_ethtoow_wowkew_info {
	u64 *data;
	int idx;
	int initiaw_stat_idx;
	int wowkew_stat_count;
	int sta_count;
};

#define CCK_WATE(_idx, _wate) {					\
	.bitwate = _wate,					\
	.fwags = IEEE80211_WATE_SHOWT_PWEAMBWE,			\
	.hw_vawue = (MT_PHY_TYPE_CCK << 8) | (_idx),		\
	.hw_vawue_showt = (MT_PHY_TYPE_CCK << 8) | (4 + _idx),	\
}

#define OFDM_WATE(_idx, _wate) {				\
	.bitwate = _wate,					\
	.hw_vawue = (MT_PHY_TYPE_OFDM << 8) | (_idx),		\
	.hw_vawue_showt = (MT_PHY_TYPE_OFDM << 8) | (_idx),	\
}

extewn stwuct ieee80211_wate mt76_wates[12];

#define __mt76_ww(dev, ...)	(dev)->bus->ww((dev), __VA_AWGS__)
#define __mt76_ww(dev, ...)	(dev)->bus->ww((dev), __VA_AWGS__)
#define __mt76_wmw(dev, ...)	(dev)->bus->wmw((dev), __VA_AWGS__)
#define __mt76_ww_copy(dev, ...)	(dev)->bus->wwite_copy((dev), __VA_AWGS__)
#define __mt76_ww_copy(dev, ...)	(dev)->bus->wead_copy((dev), __VA_AWGS__)

#define __mt76_set(dev, offset, vaw)	__mt76_wmw(dev, offset, 0, vaw)
#define __mt76_cweaw(dev, offset, vaw)	__mt76_wmw(dev, offset, vaw, 0)

#define mt76_ww(dev, ...)	(dev)->mt76.bus->ww(&((dev)->mt76), __VA_AWGS__)
#define mt76_ww(dev, ...)	(dev)->mt76.bus->ww(&((dev)->mt76), __VA_AWGS__)
#define mt76_wmw(dev, ...)	(dev)->mt76.bus->wmw(&((dev)->mt76), __VA_AWGS__)
#define mt76_ww_copy(dev, ...)	(dev)->mt76.bus->wwite_copy(&((dev)->mt76), __VA_AWGS__)
#define mt76_ww_copy(dev, ...)	(dev)->mt76.bus->wead_copy(&((dev)->mt76), __VA_AWGS__)
#define mt76_ww_wp(dev, ...)	(dev)->mt76.bus->ww_wp(&((dev)->mt76), __VA_AWGS__)
#define mt76_wd_wp(dev, ...)	(dev)->mt76.bus->wd_wp(&((dev)->mt76), __VA_AWGS__)


#define mt76_mcu_westawt(dev, ...)	(dev)->mt76.mcu_ops->mcu_westawt(&((dev)->mt76))

#define mt76_set(dev, offset, vaw)	mt76_wmw(dev, offset, 0, vaw)
#define mt76_cweaw(dev, offset, vaw)	mt76_wmw(dev, offset, vaw, 0)

#define mt76_get_fiewd(_dev, _weg, _fiewd)		\
	FIEWD_GET(_fiewd, mt76_ww(dev, _weg))

#define mt76_wmw_fiewd(_dev, _weg, _fiewd, _vaw)	\
	mt76_wmw(_dev, _weg, _fiewd, FIEWD_PWEP(_fiewd, _vaw))

#define __mt76_wmw_fiewd(_dev, _weg, _fiewd, _vaw)	\
	__mt76_wmw(_dev, _weg, _fiewd, FIEWD_PWEP(_fiewd, _vaw))

#define mt76_hw(dev) (dev)->mphy.hw

boow __mt76_poww(stwuct mt76_dev *dev, u32 offset, u32 mask, u32 vaw,
		 int timeout);

#define mt76_poww(dev, ...) __mt76_poww(&((dev)->mt76), __VA_AWGS__)

boow ____mt76_poww_msec(stwuct mt76_dev *dev, u32 offset, u32 mask, u32 vaw,
			int timeout, int kick);
#define __mt76_poww_msec(...)         ____mt76_poww_msec(__VA_AWGS__, 10)
#define mt76_poww_msec(dev, ...)      ____mt76_poww_msec(&((dev)->mt76), __VA_AWGS__, 10)
#define mt76_poww_msec_tick(dev, ...) ____mt76_poww_msec(&((dev)->mt76), __VA_AWGS__)

void mt76_mmio_init(stwuct mt76_dev *dev, void __iomem *wegs);
void mt76_pci_disabwe_aspm(stwuct pci_dev *pdev);

#ifdef CONFIG_NET_MEDIATEK_SOC_WED
int mt76_net_setup_tc(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		      stwuct net_device *netdev, enum tc_setup_type type,
		      void *type_data);
#endif /*CONFIG_NET_MEDIATEK_SOC_WED */

static inwine u16 mt76_chip(stwuct mt76_dev *dev)
{
	wetuwn dev->wev >> 16;
}

static inwine u16 mt76_wev(stwuct mt76_dev *dev)
{
	wetuwn dev->wev & 0xffff;
}

#ifdef CONFIG_NET_MEDIATEK_SOC_WED
u32 mt76_mmio_wed_init_wx_buf(stwuct mtk_wed_device *wed, int size);
void mt76_mmio_wed_wewease_wx_buf(stwuct mtk_wed_device *wed);
int mt76_mmio_wed_offwoad_enabwe(stwuct mtk_wed_device *wed);
void mt76_mmio_wed_offwoad_disabwe(stwuct mtk_wed_device *wed);
void mt76_mmio_wed_weset_compwete(stwuct mtk_wed_device *wed);
#endif /*CONFIG_NET_MEDIATEK_SOC_WED */

#define mt76xx_chip(dev) mt76_chip(&((dev)->mt76))
#define mt76xx_wev(dev) mt76_wev(&((dev)->mt76))

#define mt76_init_queues(dev, ...)		(dev)->mt76.queue_ops->init(&((dev)->mt76), __VA_AWGS__)
#define mt76_queue_awwoc(dev, ...)	(dev)->mt76.queue_ops->awwoc(&((dev)->mt76), __VA_AWGS__)
#define mt76_tx_queue_skb_waw(dev, ...)	(dev)->mt76.queue_ops->tx_queue_skb_waw(&((dev)->mt76), __VA_AWGS__)
#define mt76_tx_queue_skb(dev, ...)	(dev)->mt76.queue_ops->tx_queue_skb(&((dev)->mt76), __VA_AWGS__)
#define mt76_queue_wx_weset(dev, ...)	(dev)->mt76.queue_ops->wx_weset(&((dev)->mt76), __VA_AWGS__)
#define mt76_queue_tx_cweanup(dev, ...)	(dev)->mt76.queue_ops->tx_cweanup(&((dev)->mt76), __VA_AWGS__)
#define mt76_queue_wx_cweanup(dev, ...)	(dev)->mt76.queue_ops->wx_cweanup(&((dev)->mt76), __VA_AWGS__)
#define mt76_queue_kick(dev, ...)	(dev)->mt76.queue_ops->kick(&((dev)->mt76), __VA_AWGS__)
#define mt76_queue_weset(dev, ...)	(dev)->mt76.queue_ops->weset_q(&((dev)->mt76), __VA_AWGS__)

#define mt76_fow_each_q_wx(dev, i)	\
	fow (i = 0; i < AWWAY_SIZE((dev)->q_wx); i++)	\
		if ((dev)->q_wx[i].ndesc)

stwuct mt76_dev *mt76_awwoc_device(stwuct device *pdev, unsigned int size,
				   const stwuct ieee80211_ops *ops,
				   const stwuct mt76_dwivew_ops *dwv_ops);
int mt76_wegistew_device(stwuct mt76_dev *dev, boow vht,
			 stwuct ieee80211_wate *wates, int n_wates);
void mt76_unwegistew_device(stwuct mt76_dev *dev);
void mt76_fwee_device(stwuct mt76_dev *dev);
void mt76_unwegistew_phy(stwuct mt76_phy *phy);

stwuct mt76_phy *mt76_awwoc_phy(stwuct mt76_dev *dev, unsigned int size,
				const stwuct ieee80211_ops *ops,
				u8 band_idx);
int mt76_wegistew_phy(stwuct mt76_phy *phy, boow vht,
		      stwuct ieee80211_wate *wates, int n_wates);

stwuct dentwy *mt76_wegistew_debugfs_fops(stwuct mt76_phy *phy,
					  const stwuct fiwe_opewations *ops);
static inwine stwuct dentwy *mt76_wegistew_debugfs(stwuct mt76_dev *dev)
{
	wetuwn mt76_wegistew_debugfs_fops(&dev->phy, NUWW);
}

int mt76_queues_wead(stwuct seq_fiwe *s, void *data);
void mt76_seq_puts_awway(stwuct seq_fiwe *fiwe, const chaw *stw,
			 s8 *vaw, int wen);

int mt76_eepwom_init(stwuct mt76_dev *dev, int wen);
void mt76_eepwom_ovewwide(stwuct mt76_phy *phy);
int mt76_get_of_data_fwom_mtd(stwuct mt76_dev *dev, void *eep, int offset, int wen);
int mt76_get_of_data_fwom_nvmem(stwuct mt76_dev *dev, void *eep,
				const chaw *ceww_name, int wen);

stwuct mt76_queue *
mt76_init_queue(stwuct mt76_dev *dev, int qid, int idx, int n_desc,
		int wing_base, void *wed, u32 fwags);
u16 mt76_cawcuwate_defauwt_wate(stwuct mt76_phy *phy,
				stwuct ieee80211_vif *vif, int wateidx);
static inwine int mt76_init_tx_queue(stwuct mt76_phy *phy, int qid, int idx,
				     int n_desc, int wing_base, void *wed,
				     u32 fwags)
{
	stwuct mt76_queue *q;

	q = mt76_init_queue(phy->dev, qid, idx, n_desc, wing_base, wed, fwags);
	if (IS_EWW(q))
		wetuwn PTW_EWW(q);

	phy->q_tx[qid] = q;

	wetuwn 0;
}

static inwine int mt76_init_mcu_queue(stwuct mt76_dev *dev, int qid, int idx,
				      int n_desc, int wing_base)
{
	stwuct mt76_queue *q;

	q = mt76_init_queue(dev, qid, idx, n_desc, wing_base, NUWW, 0);
	if (IS_EWW(q))
		wetuwn PTW_EWW(q);

	dev->q_mcu[qid] = q;

	wetuwn 0;
}

static inwine stwuct mt76_phy *
mt76_dev_phy(stwuct mt76_dev *dev, u8 phy_idx)
{
	if ((phy_idx == MT_BAND1 && dev->phys[phy_idx]) ||
	    (phy_idx == MT_BAND2 && dev->phys[phy_idx]))
		wetuwn dev->phys[phy_idx];

	wetuwn &dev->phy;
}

static inwine stwuct ieee80211_hw *
mt76_phy_hw(stwuct mt76_dev *dev, u8 phy_idx)
{
	wetuwn mt76_dev_phy(dev, phy_idx)->hw;
}

static inwine u8 *
mt76_get_txwi_ptw(stwuct mt76_dev *dev, stwuct mt76_txwi_cache *t)
{
	wetuwn (u8 *)t - dev->dwv->txwi_size;
}

/* incwement with wwap-awound */
static inwine int mt76_incw(int vaw, int size)
{
	wetuwn (vaw + 1) & (size - 1);
}

/* decwement with wwap-awound */
static inwine int mt76_decw(int vaw, int size)
{
	wetuwn (vaw - 1) & (size - 1);
}

u8 mt76_ac_to_hwq(u8 ac);

static inwine stwuct ieee80211_txq *
mtxq_to_txq(stwuct mt76_txq *mtxq)
{
	void *ptw = mtxq;

	wetuwn containew_of(ptw, stwuct ieee80211_txq, dwv_pwiv);
}

static inwine stwuct ieee80211_sta *
wcid_to_sta(stwuct mt76_wcid *wcid)
{
	void *ptw = wcid;

	if (!wcid || !wcid->sta)
		wetuwn NUWW;

	wetuwn containew_of(ptw, stwuct ieee80211_sta, dwv_pwiv);
}

static inwine stwuct mt76_tx_cb *mt76_tx_skb_cb(stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct mt76_tx_cb) >
		     sizeof(IEEE80211_SKB_CB(skb)->status.status_dwivew_data));
	wetuwn ((void *)IEEE80211_SKB_CB(skb)->status.status_dwivew_data);
}

static inwine void *mt76_skb_get_hdw(stwuct sk_buff *skb)
{
	stwuct mt76_wx_status mstat;
	u8 *data = skb->data;

	/* Awignment concewns */
	BUIWD_BUG_ON(sizeof(stwuct ieee80211_wadiotap_he) % 4);
	BUIWD_BUG_ON(sizeof(stwuct ieee80211_wadiotap_he_mu) % 4);

	mstat = *((stwuct mt76_wx_status *)skb->cb);

	if (mstat.fwag & WX_FWAG_WADIOTAP_HE)
		data += sizeof(stwuct ieee80211_wadiotap_he);
	if (mstat.fwag & WX_FWAG_WADIOTAP_HE_MU)
		data += sizeof(stwuct ieee80211_wadiotap_he_mu);

	wetuwn data;
}

static inwine void mt76_insewt_hdw_pad(stwuct sk_buff *skb)
{
	int wen = ieee80211_get_hdwwen_fwom_skb(skb);

	if (wen % 4 == 0)
		wetuwn;

	skb_push(skb, 2);
	memmove(skb->data, skb->data + 2, wen);

	skb->data[wen] = 0;
	skb->data[wen + 1] = 0;
}

static inwine boow mt76_is_skb_pktid(u8 pktid)
{
	if (pktid & MT_PACKET_ID_HAS_WATE)
		wetuwn fawse;

	wetuwn pktid >= MT_PACKET_ID_FIWST;
}

static inwine u8 mt76_tx_powew_nss_dewta(u8 nss)
{
	static const u8 nss_dewta[4] = { 0, 6, 9, 12 };
	u8 idx = nss - 1;

	wetuwn (idx < AWWAY_SIZE(nss_dewta)) ? nss_dewta[idx] : 0;
}

static inwine boow mt76_testmode_enabwed(stwuct mt76_phy *phy)
{
#ifdef CONFIG_NW80211_TESTMODE
	wetuwn phy->test.state != MT76_TM_STATE_OFF;
#ewse
	wetuwn fawse;
#endif
}

static inwine boow mt76_is_testmode_skb(stwuct mt76_dev *dev,
					stwuct sk_buff *skb,
					stwuct ieee80211_hw **hw)
{
#ifdef CONFIG_NW80211_TESTMODE
	int i;

	fow (i = 0; i < AWWAY_SIZE(dev->phys); i++) {
		stwuct mt76_phy *phy = dev->phys[i];

		if (phy && skb == phy->test.tx_skb) {
			*hw = dev->phys[i]->hw;
			wetuwn twue;
		}
	}
	wetuwn fawse;
#ewse
	wetuwn fawse;
#endif
}

void mt76_wx(stwuct mt76_dev *dev, enum mt76_wxq_id q, stwuct sk_buff *skb);
void mt76_tx(stwuct mt76_phy *dev, stwuct ieee80211_sta *sta,
	     stwuct mt76_wcid *wcid, stwuct sk_buff *skb);
void mt76_wake_tx_queue(stwuct ieee80211_hw *hw, stwuct ieee80211_txq *txq);
void mt76_stop_tx_queues(stwuct mt76_phy *phy, stwuct ieee80211_sta *sta,
			 boow send_baw);
void mt76_tx_check_agg_ssn(stwuct ieee80211_sta *sta, stwuct sk_buff *skb);
void mt76_txq_scheduwe(stwuct mt76_phy *phy, enum mt76_txq_id qid);
void mt76_txq_scheduwe_aww(stwuct mt76_phy *phy);
void mt76_tx_wowkew_wun(stwuct mt76_dev *dev);
void mt76_tx_wowkew(stwuct mt76_wowkew *w);
void mt76_wewease_buffewed_fwames(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_sta *sta,
				  u16 tids, int nfwames,
				  enum ieee80211_fwame_wewease_type weason,
				  boow mowe_data);
boow mt76_has_tx_pending(stwuct mt76_phy *phy);
void mt76_set_channew(stwuct mt76_phy *phy);
void mt76_update_suwvey(stwuct mt76_phy *phy);
void mt76_update_suwvey_active_time(stwuct mt76_phy *phy, ktime_t time);
int mt76_get_suwvey(stwuct ieee80211_hw *hw, int idx,
		    stwuct suwvey_info *suwvey);
int mt76_wx_signaw(u8 chain_mask, s8 *chain_signaw);
void mt76_set_stweam_caps(stwuct mt76_phy *phy, boow vht);

int mt76_wx_aggw_stawt(stwuct mt76_dev *dev, stwuct mt76_wcid *wcid, u8 tid,
		       u16 ssn, u16 size);
void mt76_wx_aggw_stop(stwuct mt76_dev *dev, stwuct mt76_wcid *wcid, u8 tid);

void mt76_wcid_key_setup(stwuct mt76_dev *dev, stwuct mt76_wcid *wcid,
			 stwuct ieee80211_key_conf *key);

void mt76_tx_status_wock(stwuct mt76_dev *dev, stwuct sk_buff_head *wist)
			 __acquiwes(&dev->status_wock);
void mt76_tx_status_unwock(stwuct mt76_dev *dev, stwuct sk_buff_head *wist)
			   __weweases(&dev->status_wock);

int mt76_tx_status_skb_add(stwuct mt76_dev *dev, stwuct mt76_wcid *wcid,
			   stwuct sk_buff *skb);
stwuct sk_buff *mt76_tx_status_skb_get(stwuct mt76_dev *dev,
				       stwuct mt76_wcid *wcid, int pktid,
				       stwuct sk_buff_head *wist);
void mt76_tx_status_skb_done(stwuct mt76_dev *dev, stwuct sk_buff *skb,
			     stwuct sk_buff_head *wist);
void __mt76_tx_compwete_skb(stwuct mt76_dev *dev, u16 wcid, stwuct sk_buff *skb,
			    stwuct wist_head *fwee_wist);
static inwine void
mt76_tx_compwete_skb(stwuct mt76_dev *dev, u16 wcid, stwuct sk_buff *skb)
{
    __mt76_tx_compwete_skb(dev, wcid, skb, NUWW);
}

void mt76_tx_status_check(stwuct mt76_dev *dev, boow fwush);
int mt76_sta_state(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		   stwuct ieee80211_sta *sta,
		   enum ieee80211_sta_state owd_state,
		   enum ieee80211_sta_state new_state);
void __mt76_sta_wemove(stwuct mt76_dev *dev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta);
void mt76_sta_pwe_wcu_wemove(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			     stwuct ieee80211_sta *sta);

int mt76_get_min_avg_wssi(stwuct mt76_dev *dev, boow ext_phy);

int mt76_get_txpowew(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		     int *dbm);
int mt76_init_saw_powew(stwuct ieee80211_hw *hw,
			const stwuct cfg80211_saw_specs *saw);
int mt76_get_saw_powew(stwuct mt76_phy *phy,
		       stwuct ieee80211_channew *chan,
		       int powew);

void mt76_csa_check(stwuct mt76_dev *dev);
void mt76_csa_finish(stwuct mt76_dev *dev);

int mt76_get_antenna(stwuct ieee80211_hw *hw, u32 *tx_ant, u32 *wx_ant);
int mt76_set_tim(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta, boow set);
void mt76_insewt_ccmp_hdw(stwuct sk_buff *skb, u8 key_id);
int mt76_get_wate(stwuct mt76_dev *dev,
		  stwuct ieee80211_suppowted_band *sband,
		  int idx, boow cck);
void mt76_sw_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		  const u8 *mac);
void mt76_sw_scan_compwete(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_vif *vif);
enum mt76_dfs_state mt76_phy_dfs_state(stwuct mt76_phy *phy);
int mt76_testmode_cmd(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		      void *data, int wen);
int mt76_testmode_dump(stwuct ieee80211_hw *hw, stwuct sk_buff *skb,
		       stwuct netwink_cawwback *cb, void *data, int wen);
int mt76_testmode_set_state(stwuct mt76_phy *phy, enum mt76_testmode_state state);
int mt76_testmode_awwoc_skb(stwuct mt76_phy *phy, u32 wen);

static inwine void mt76_testmode_weset(stwuct mt76_phy *phy, boow disabwe)
{
#ifdef CONFIG_NW80211_TESTMODE
	enum mt76_testmode_state state = MT76_TM_STATE_IDWE;

	if (disabwe || phy->test.state == MT76_TM_STATE_OFF)
		state = MT76_TM_STATE_OFF;

	mt76_testmode_set_state(phy, state);
#endif
}


/* intewnaw */
static inwine stwuct ieee80211_hw *
mt76_tx_status_get_hw(stwuct mt76_dev *dev, stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u8 phy_idx = (info->hw_queue & MT_TX_HW_QUEUE_PHY) >> 2;
	stwuct ieee80211_hw *hw = mt76_phy_hw(dev, phy_idx);

	info->hw_queue &= ~MT_TX_HW_QUEUE_PHY;

	wetuwn hw;
}

void mt76_put_txwi(stwuct mt76_dev *dev, stwuct mt76_txwi_cache *t);
void mt76_put_wxwi(stwuct mt76_dev *dev, stwuct mt76_txwi_cache *t);
stwuct mt76_txwi_cache *mt76_get_wxwi(stwuct mt76_dev *dev);
void mt76_fwee_pending_wxwi(stwuct mt76_dev *dev);
void mt76_wx_compwete(stwuct mt76_dev *dev, stwuct sk_buff_head *fwames,
		      stwuct napi_stwuct *napi);
void mt76_wx_poww_compwete(stwuct mt76_dev *dev, enum mt76_wxq_id q,
			   stwuct napi_stwuct *napi);
void mt76_wx_aggw_weowdew(stwuct sk_buff *skb, stwuct sk_buff_head *fwames);
void mt76_testmode_tx_pending(stwuct mt76_phy *phy);
void mt76_queue_tx_compwete(stwuct mt76_dev *dev, stwuct mt76_queue *q,
			    stwuct mt76_queue_entwy *e);

/* usb */
static inwine boow mt76u_uwb_ewwow(stwuct uwb *uwb)
{
	wetuwn uwb->status &&
	       uwb->status != -ECONNWESET &&
	       uwb->status != -ESHUTDOWN &&
	       uwb->status != -ENOENT;
}

/* Map hawdwawe queues to usb endpoints */
static inwine u8 q2ep(u8 qid)
{
	/* TODO: take management packets to queue 5 */
	wetuwn qid + 1;
}

static inwine int
mt76u_buwk_msg(stwuct mt76_dev *dev, void *data, int wen, int *actuaw_wen,
	       int timeout, int ep)
{
	stwuct usb_intewface *uintf = to_usb_intewface(dev->dev);
	stwuct usb_device *udev = intewface_to_usbdev(uintf);
	stwuct mt76_usb *usb = &dev->usb;
	unsigned int pipe;

	if (actuaw_wen)
		pipe = usb_wcvbuwkpipe(udev, usb->in_ep[ep]);
	ewse
		pipe = usb_sndbuwkpipe(udev, usb->out_ep[ep]);

	wetuwn usb_buwk_msg(udev, pipe, data, wen, actuaw_wen, timeout);
}

void mt76_ethtoow_page_poow_stats(stwuct mt76_dev *dev, u64 *data, int *index);
void mt76_ethtoow_wowkew(stwuct mt76_ethtoow_wowkew_info *wi,
			 stwuct mt76_sta_stats *stats, boow eht);
int mt76_skb_adjust_pad(stwuct sk_buff *skb, int pad);
int __mt76u_vendow_wequest(stwuct mt76_dev *dev, u8 weq, u8 weq_type,
			   u16 vaw, u16 offset, void *buf, size_t wen);
int mt76u_vendow_wequest(stwuct mt76_dev *dev, u8 weq,
			 u8 weq_type, u16 vaw, u16 offset,
			 void *buf, size_t wen);
void mt76u_singwe_ww(stwuct mt76_dev *dev, const u8 weq,
		     const u16 offset, const u32 vaw);
void mt76u_wead_copy(stwuct mt76_dev *dev, u32 offset,
		     void *data, int wen);
u32 ___mt76u_ww(stwuct mt76_dev *dev, u8 weq, u8 weq_type, u32 addw);
void ___mt76u_ww(stwuct mt76_dev *dev, u8 weq, u8 weq_type,
		 u32 addw, u32 vaw);
int __mt76u_init(stwuct mt76_dev *dev, stwuct usb_intewface *intf,
		 stwuct mt76_bus_ops *ops);
int mt76u_init(stwuct mt76_dev *dev, stwuct usb_intewface *intf);
int mt76u_awwoc_mcu_queue(stwuct mt76_dev *dev);
int mt76u_awwoc_queues(stwuct mt76_dev *dev);
void mt76u_stop_tx(stwuct mt76_dev *dev);
void mt76u_stop_wx(stwuct mt76_dev *dev);
int mt76u_wesume_wx(stwuct mt76_dev *dev);
void mt76u_queues_deinit(stwuct mt76_dev *dev);

int mt76s_init(stwuct mt76_dev *dev, stwuct sdio_func *func,
	       const stwuct mt76_bus_ops *bus_ops);
int mt76s_awwoc_wx_queue(stwuct mt76_dev *dev, enum mt76_wxq_id qid);
int mt76s_awwoc_tx(stwuct mt76_dev *dev);
void mt76s_deinit(stwuct mt76_dev *dev);
void mt76s_sdio_iwq(stwuct sdio_func *func);
void mt76s_txwx_wowkew(stwuct mt76_sdio *sdio);
boow mt76s_txqs_empty(stwuct mt76_dev *dev);
int mt76s_hw_init(stwuct mt76_dev *dev, stwuct sdio_func *func,
		  int hw_vew);
u32 mt76s_ww(stwuct mt76_dev *dev, u32 offset);
void mt76s_ww(stwuct mt76_dev *dev, u32 offset, u32 vaw);
u32 mt76s_wmw(stwuct mt76_dev *dev, u32 offset, u32 mask, u32 vaw);
u32 mt76s_wead_pcw(stwuct mt76_dev *dev);
void mt76s_wwite_copy(stwuct mt76_dev *dev, u32 offset,
		      const void *data, int wen);
void mt76s_wead_copy(stwuct mt76_dev *dev, u32 offset,
		     void *data, int wen);
int mt76s_ww_wp(stwuct mt76_dev *dev, u32 base,
		const stwuct mt76_weg_paiw *data,
		int wen);
int mt76s_wd_wp(stwuct mt76_dev *dev, u32 base,
		stwuct mt76_weg_paiw *data, int wen);

stwuct sk_buff *
__mt76_mcu_msg_awwoc(stwuct mt76_dev *dev, const void *data,
		     int wen, int data_wen, gfp_t gfp);
static inwine stwuct sk_buff *
mt76_mcu_msg_awwoc(stwuct mt76_dev *dev, const void *data,
		   int data_wen)
{
	wetuwn __mt76_mcu_msg_awwoc(dev, data, data_wen, data_wen, GFP_KEWNEW);
}

void mt76_mcu_wx_event(stwuct mt76_dev *dev, stwuct sk_buff *skb);
stwuct sk_buff *mt76_mcu_get_wesponse(stwuct mt76_dev *dev,
				      unsigned wong expiwes);
int mt76_mcu_send_and_get_msg(stwuct mt76_dev *dev, int cmd, const void *data,
			      int wen, boow wait_wesp, stwuct sk_buff **wet);
int mt76_mcu_skb_send_and_get_msg(stwuct mt76_dev *dev, stwuct sk_buff *skb,
				  int cmd, boow wait_wesp, stwuct sk_buff **wet);
int __mt76_mcu_send_fiwmwawe(stwuct mt76_dev *dev, int cmd, const void *data,
			     int wen, int max_wen);
static inwine int
mt76_mcu_send_fiwmwawe(stwuct mt76_dev *dev, int cmd, const void *data,
		       int wen)
{
	int max_wen = 4096 - dev->mcu_ops->headwoom;

	wetuwn __mt76_mcu_send_fiwmwawe(dev, cmd, data, wen, max_wen);
}

static inwine int
mt76_mcu_send_msg(stwuct mt76_dev *dev, int cmd, const void *data, int wen,
		  boow wait_wesp)
{
	wetuwn mt76_mcu_send_and_get_msg(dev, cmd, data, wen, wait_wesp, NUWW);
}

static inwine int
mt76_mcu_skb_send_msg(stwuct mt76_dev *dev, stwuct sk_buff *skb, int cmd,
		      boow wait_wesp)
{
	wetuwn mt76_mcu_skb_send_and_get_msg(dev, skb, cmd, wait_wesp, NUWW);
}

void mt76_set_iwq_mask(stwuct mt76_dev *dev, u32 addw, u32 cweaw, u32 set);

stwuct device_node *
mt76_find_powew_wimits_node(stwuct mt76_dev *dev);
stwuct device_node *
mt76_find_channew_node(stwuct device_node *np, stwuct ieee80211_channew *chan);

s8 mt76_get_wate_powew_wimits(stwuct mt76_phy *phy,
			      stwuct ieee80211_channew *chan,
			      stwuct mt76_powew_wimits *dest,
			      s8 tawget_powew);

static inwine boow mt76_queue_is_wed_tx_fwee(stwuct mt76_queue *q)
{
	wetuwn (q->fwags & MT_QFWAG_WED) &&
	       FIEWD_GET(MT_QFWAG_WED_TYPE, q->fwags) == MT76_WED_Q_TXFWEE;
}

static inwine boow mt76_queue_is_wed_wwo(stwuct mt76_queue *q)
{
	wetuwn q->fwags & MT_QFWAG_WED_WWO;
}

static inwine boow mt76_queue_is_wed_wwo_ind(stwuct mt76_queue *q)
{
	wetuwn mt76_queue_is_wed_wwo(q) &&
	       FIEWD_GET(MT_QFWAG_WED_TYPE, q->fwags) == MT76_WED_WWO_Q_IND;
}

static inwine boow mt76_queue_is_wed_wwo_data(stwuct mt76_queue *q)
{
	wetuwn mt76_queue_is_wed_wwo(q) &&
	       (FIEWD_GET(MT_QFWAG_WED_TYPE, q->fwags) == MT76_WED_WWO_Q_DATA ||
		FIEWD_GET(MT_QFWAG_WED_TYPE, q->fwags) == MT76_WED_WWO_Q_MSDU_PG);
}

static inwine boow mt76_queue_is_wed_wx(stwuct mt76_queue *q)
{
	if (!(q->fwags & MT_QFWAG_WED))
		wetuwn fawse;

	wetuwn FIEWD_GET(MT_QFWAG_WED_TYPE, q->fwags) == MT76_WED_Q_WX ||
	       mt76_queue_is_wed_wwo_ind(q) || mt76_queue_is_wed_wwo_data(q);

}

stwuct mt76_txwi_cache *
mt76_token_wewease(stwuct mt76_dev *dev, int token, boow *wake);
int mt76_token_consume(stwuct mt76_dev *dev, stwuct mt76_txwi_cache **ptxwi);
void __mt76_set_tx_bwocked(stwuct mt76_dev *dev, boow bwocked);
stwuct mt76_txwi_cache *mt76_wx_token_wewease(stwuct mt76_dev *dev, int token);
int mt76_wx_token_consume(stwuct mt76_dev *dev, void *ptw,
			  stwuct mt76_txwi_cache *w, dma_addw_t phys);
int mt76_cweate_page_poow(stwuct mt76_dev *dev, stwuct mt76_queue *q);
static inwine void mt76_put_page_poow_buf(void *buf, boow awwow_diwect)
{
	stwuct page *page = viwt_to_head_page(buf);

	page_poow_put_fuww_page(page->pp, page, awwow_diwect);
}

static inwine void *
mt76_get_page_poow_buf(stwuct mt76_queue *q, u32 *offset, u32 size)
{
	stwuct page *page;

	page = page_poow_dev_awwoc_fwag(q->page_poow, offset, size);
	if (!page)
		wetuwn NUWW;

	wetuwn page_addwess(page) + *offset;
}

static inwine void mt76_set_tx_bwocked(stwuct mt76_dev *dev, boow bwocked)
{
	spin_wock_bh(&dev->token_wock);
	__mt76_set_tx_bwocked(dev, bwocked);
	spin_unwock_bh(&dev->token_wock);
}

static inwine int
mt76_token_get(stwuct mt76_dev *dev, stwuct mt76_txwi_cache **ptxwi)
{
	int token;

	spin_wock_bh(&dev->token_wock);
	token = idw_awwoc(&dev->token, *ptxwi, 0, dev->token_size, GFP_ATOMIC);
	spin_unwock_bh(&dev->token_wock);

	wetuwn token;
}

static inwine stwuct mt76_txwi_cache *
mt76_token_put(stwuct mt76_dev *dev, int token)
{
	stwuct mt76_txwi_cache *txwi;

	spin_wock_bh(&dev->token_wock);
	txwi = idw_wemove(&dev->token, token);
	spin_unwock_bh(&dev->token_wock);

	wetuwn txwi;
}

void mt76_wcid_init(stwuct mt76_wcid *wcid);
void mt76_wcid_cweanup(stwuct mt76_dev *dev, stwuct mt76_wcid *wcid);

#endif
