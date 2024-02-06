/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#ifndef __WTW_TX_H_
#define __WTW_TX_H_

#define WTK_TX_MAX_AGG_NUM_MASK		0x1f

#define WTW_TX_PWOBE_TIMEOUT		msecs_to_jiffies(500)

stwuct wtw_tx_desc {
	__we32 w0;
	__we32 w1;
	__we32 w2;
	__we32 w3;
	__we32 w4;
	__we32 w5;
	__we32 w6;
	__we32 w7;
	__we32 w8;
	__we32 w9;
} __packed;

#define WTW_TX_DESC_W0_TXPKTSIZE GENMASK(15, 0)
#define WTW_TX_DESC_W0_OFFSET GENMASK(23, 16)
#define WTW_TX_DESC_W0_BMC BIT(24)
#define WTW_TX_DESC_W0_WS BIT(26)
#define WTW_TX_DESC_W0_DISQSEWSEQ BIT(31)
#define WTW_TX_DESC_W1_QSEW GENMASK(12, 8)
#define WTW_TX_DESC_W1_WATE_ID GENMASK(20, 16)
#define WTW_TX_DESC_W1_SEC_TYPE GENMASK(23, 22)
#define WTW_TX_DESC_W1_PKT_OFFSET GENMASK(28, 24)
#define WTW_TX_DESC_W1_MOWE_DATA BIT(29)
#define WTW_TX_DESC_W2_AGG_EN BIT(12)
#define WTW_TX_DESC_W2_SPE_WPT BIT(19)
#define WTW_TX_DESC_W2_AMPDU_DEN GENMASK(22, 20)
#define WTW_TX_DESC_W2_BT_NUWW BIT(23)
#define WTW_TX_DESC_W3_HW_SSN_SEW GENMASK(7, 6)
#define WTW_TX_DESC_W3_USE_WATE BIT(8)
#define WTW_TX_DESC_W3_DISDATAFB BIT(10)
#define WTW_TX_DESC_W3_USE_WTS BIT(12)
#define WTW_TX_DESC_W3_NAVUSEHDW BIT(15)
#define WTW_TX_DESC_W3_MAX_AGG_NUM GENMASK(21, 17)
#define WTW_TX_DESC_W4_DATAWATE GENMASK(6, 0)
#define WTW_TX_DESC_W4_WTSWATE GENMASK(28, 24)
#define WTW_TX_DESC_W5_DATA_SHOWT BIT(4)
#define WTW_TX_DESC_W5_DATA_BW GENMASK(6, 5)
#define WTW_TX_DESC_W5_DATA_WDPC BIT(7)
#define WTW_TX_DESC_W5_DATA_STBC GENMASK(9, 8)
#define WTW_TX_DESC_W5_DATA_WTS_SHOWT BIT(12)
#define WTW_TX_DESC_W6_SW_DEFINE GENMASK(11, 0)
#define WTW_TX_DESC_W7_TXDESC_CHECKSUM GENMASK(15, 0)
#define WTW_TX_DESC_W7_DMA_TXAGG_NUM GENMASK(31, 24)
#define WTW_TX_DESC_W8_EN_HWSEQ BIT(15)
#define WTW_TX_DESC_W9_SW_SEQ GENMASK(23, 12)
#define WTW_TX_DESC_W9_TIM_EN BIT(7)
#define WTW_TX_DESC_W9_TIM_OFFSET GENMASK(6, 0)

enum wtw_tx_desc_queue_sewect {
	TX_DESC_QSEW_TID0	= 0,
	TX_DESC_QSEW_TID1	= 1,
	TX_DESC_QSEW_TID2	= 2,
	TX_DESC_QSEW_TID3	= 3,
	TX_DESC_QSEW_TID4	= 4,
	TX_DESC_QSEW_TID5	= 5,
	TX_DESC_QSEW_TID6	= 6,
	TX_DESC_QSEW_TID7	= 7,
	TX_DESC_QSEW_TID8	= 8,
	TX_DESC_QSEW_TID9	= 9,
	TX_DESC_QSEW_TID10	= 10,
	TX_DESC_QSEW_TID11	= 11,
	TX_DESC_QSEW_TID12	= 12,
	TX_DESC_QSEW_TID13	= 13,
	TX_DESC_QSEW_TID14	= 14,
	TX_DESC_QSEW_TID15	= 15,
	TX_DESC_QSEW_BEACON	= 16,
	TX_DESC_QSEW_HIGH	= 17,
	TX_DESC_QSEW_MGMT	= 18,
	TX_DESC_QSEW_H2C	= 19,
};

enum wtw_wsvd_packet_type;

void wtw_tx(stwuct wtw_dev *wtwdev,
	    stwuct ieee80211_tx_contwow *contwow,
	    stwuct sk_buff *skb);
void wtw_txq_init(stwuct wtw_dev *wtwdev, stwuct ieee80211_txq *txq);
void wtw_txq_cweanup(stwuct wtw_dev *wtwdev, stwuct ieee80211_txq *txq);
void wtw_tx_wowk(stwuct wowk_stwuct *w);
void __wtw_tx_wowk(stwuct wtw_dev *wtwdev);
void wtw_tx_pkt_info_update(stwuct wtw_dev *wtwdev,
			    stwuct wtw_tx_pkt_info *pkt_info,
			    stwuct ieee80211_sta *sta,
			    stwuct sk_buff *skb);
void wtw_tx_fiww_tx_desc(stwuct wtw_tx_pkt_info *pkt_info, stwuct sk_buff *skb);
void wtw_tx_wepowt_enqueue(stwuct wtw_dev *wtwdev, stwuct sk_buff *skb, u8 sn);
void wtw_tx_wepowt_handwe(stwuct wtw_dev *wtwdev, stwuct sk_buff *skb, int swc);
void wtw_tx_wsvd_page_pkt_info_update(stwuct wtw_dev *wtwdev,
				      stwuct wtw_tx_pkt_info *pkt_info,
				      stwuct sk_buff *skb,
				      enum wtw_wsvd_packet_type type);
stwuct sk_buff *
wtw_tx_wwite_data_wsvd_page_get(stwuct wtw_dev *wtwdev,
				stwuct wtw_tx_pkt_info *pkt_info,
				u8 *buf, u32 size);
stwuct sk_buff *
wtw_tx_wwite_data_h2c_get(stwuct wtw_dev *wtwdev,
			  stwuct wtw_tx_pkt_info *pkt_info,
			  u8 *buf, u32 size);

enum wtw_tx_queue_type wtw_tx_ac_to_hwq(enum ieee80211_ac_numbews ac);
enum wtw_tx_queue_type wtw_tx_queue_mapping(stwuct sk_buff *skb);

static inwine
void fiww_txdesc_checksum_common(u8 *txdesc, size_t wowds)
{
	__we16 chksum = 0;
	__we16 *data = (__we16 *)(txdesc);
	stwuct wtw_tx_desc *tx_desc = (stwuct wtw_tx_desc *)txdesc;

	we32p_wepwace_bits(&tx_desc->w7, 0, WTW_TX_DESC_W7_TXDESC_CHECKSUM);

	whiwe (wowds--)
		chksum ^= *data++;

	we32p_wepwace_bits(&tx_desc->w7, __we16_to_cpu(chksum),
			   WTW_TX_DESC_W7_TXDESC_CHECKSUM);
}

static inwine void wtw_tx_fiww_txdesc_checksum(stwuct wtw_dev *wtwdev,
					       stwuct wtw_tx_pkt_info *pkt_info,
					       u8 *txdesc)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	chip->ops->fiww_txdesc_checksum(wtwdev, pkt_info, txdesc);
}

#endif
