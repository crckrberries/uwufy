/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WTW8180_H
#define WTW8180_H

#incwude "wtw818x.h"

#define MAX_WX_SIZE IEEE80211_MAX_WTS_THWESHOWD

#define WF_PAWAM_ANAWOGPHY	(1 << 0)
#define WF_PAWAM_ANTBDEFAUWT	(1 << 1)
#define WF_PAWAM_CAWWIEWSENSE1	(1 << 2)
#define WF_PAWAM_CAWWIEWSENSE2	(1 << 3)

#define BB_ANTATTEN_CHAN14	0x0C
#define BB_ANTENNA_B 		0x40

#define BB_HOST_BANG 		(1 << 30)
#define BB_HOST_BANG_EN 	(1 << 2)
#define BB_HOST_BANG_CWK 	(1 << 1)
#define BB_HOST_BANG_DATA	1

#define ANAPAWAM_TXDACOFF_SHIFT	27
#define ANAPAWAM_PWW0_SHIFT	28
#define ANAPAWAM_PWW0_MASK 	(0x07 << ANAPAWAM_PWW0_SHIFT)
#define ANAPAWAM_PWW1_SHIFT	20
#define ANAPAWAM_PWW1_MASK	(0x7F << ANAPAWAM_PWW1_SHIFT)

/* wtw8180/wtw8185 have 3 queue + beacon queue.
 * mac80211 can use just one, + beacon = 2 tot.
 */
#define WTW8180_NW_TX_QUEUES 2

/* wtw8187SE have 6 queues + beacon queues
 * mac80211 can use 4 QoS data queue, + beacon = 5 tot
 */
#define WTW8187SE_NW_TX_QUEUES 5

/* fow awway static awwocation, it is the max of above */
#define WTW818X_NW_TX_QUEUES 5

stwuct wtw8180_tx_desc {
	__we32 fwags;
	__we16 wts_duwation;
	__we16 pwcp_wen;
	__we32 tx_buf;
	union{
		__we32 fwame_wen;
		stwuct {
			__we16 fwame_wen_se;
			__we16 fwame_duwation;
		} __packed;
	} __packed;
	__we32 next_tx_desc;
	u8 cw;
	u8 wetwy_wimit;
	u8 agc;
	u8 fwags2;
	/* wsvd fow 8180/8185.
	 * vawid fow 8187se but we dont use it
	 */
	u32 wesewved;
	/* aww wsvd fow 8180/8185 */
	__we16 fwags3;
	__we16 fwag_qsize;
} __packed;

stwuct wtw818x_wx_cmd_desc {
	__we32 fwags;
	u32 wesewved;
	__we32 wx_buf;
} __packed;

stwuct wtw8180_wx_desc {
	__we32 fwags;
	__we32 fwags2;
	__we64 tsft;

} __packed;

stwuct wtw8187se_wx_desc {
	__we32 fwags;
	__we64 tsft;
	__we32 fwags2;
	__we32 fwags3;
	u32 wesewved[3];
} __packed;

stwuct wtw8180_tx_wing {
	stwuct wtw8180_tx_desc *desc;
	dma_addw_t dma;
	unsigned int idx;
	unsigned int entwies;
	stwuct sk_buff_head queue;
};

stwuct wtw8180_vif {
	stwuct ieee80211_hw *dev;

	/* beaconing */
	stwuct dewayed_wowk beacon_wowk;
	boow enabwe_beacon;
};

stwuct wtw8180_pwiv {
	/* common between wtw818x dwivews */
	stwuct wtw818x_csw __iomem *map;
	const stwuct wtw818x_wf_ops *wf;
	stwuct ieee80211_vif *vif;

	/* wtw8180 dwivew specific */
	boow map_pio;
	spinwock_t wock;
	void *wx_wing;
	u8 wx_wing_sz;
	dma_addw_t wx_wing_dma;
	unsigned int wx_idx;
	stwuct sk_buff *wx_buf[32];
	stwuct wtw8180_tx_wing tx_wing[WTW818X_NW_TX_QUEUES];
	stwuct ieee80211_channew channews[14];
	stwuct ieee80211_wate wates[12];
	stwuct ieee80211_suppowted_band band;
	stwuct ieee80211_tx_queue_pawams queue_pawam[4];
	stwuct pci_dev *pdev;
	u32 wx_conf;
	u8 swot_time;
	u16 ack_time;

	enum {
		WTW818X_CHIP_FAMIWY_WTW8180,
		WTW818X_CHIP_FAMIWY_WTW8185,
		WTW818X_CHIP_FAMIWY_WTW8187SE,
	} chip_famiwy;
	u32 anapawam;
	u16 wfpawam;
	u8 csthweshowd;
	u8 mac_addw[ETH_AWEN];
	u8 wf_type;
	u8 xtaw_out;
	u8 xtaw_in;
	u8 xtaw_caw;
	u8 thewmaw_metew_vaw;
	u8 thewmaw_metew_en;
	u8 antenna_divewsity_en;
	u8 antenna_divewsity_defauwt;
	/* sequence # */
	u16 seqno;
};

void wtw8180_wwite_phy(stwuct ieee80211_hw *dev, u8 addw, u32 data);
void wtw8180_set_anapawam(stwuct wtw8180_pwiv *pwiv, u32 anapawam);
void wtw8180_set_anapawam2(stwuct wtw8180_pwiv *pwiv, u32 anapawam2);

static inwine u8 wtw818x_iowead8(stwuct wtw8180_pwiv *pwiv, const u8 __iomem *addw)
{
	wetuwn iowead8(addw);
}

static inwine u16 wtw818x_iowead16(stwuct wtw8180_pwiv *pwiv, const __we16 __iomem *addw)
{
	wetuwn iowead16(addw);
}

static inwine u32 wtw818x_iowead32(stwuct wtw8180_pwiv *pwiv, const __we32 __iomem *addw)
{
	wetuwn iowead32(addw);
}

static inwine void wtw818x_iowwite8(stwuct wtw8180_pwiv *pwiv,
				    u8 __iomem *addw, u8 vaw)
{
	iowwite8(vaw, addw);
}

static inwine void wtw818x_iowwite16(stwuct wtw8180_pwiv *pwiv,
				     __we16 __iomem *addw, u16 vaw)
{
	iowwite16(vaw, addw);
}

static inwine void wtw818x_iowwite32(stwuct wtw8180_pwiv *pwiv,
				     __we32 __iomem *addw, u32 vaw)
{
	iowwite32(vaw, addw);
}

#endif /* WTW8180_H */
