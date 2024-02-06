/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#ifndef __WTW_WX_H_
#define __WTW_WX_H_

enum wtw_wx_desc_enc {
	WX_DESC_ENC_NONE	= 0,
	WX_DESC_ENC_WEP40	= 1,
	WX_DESC_ENC_TKIP_WO_MIC	= 2,
	WX_DESC_ENC_TKIP_MIC	= 3,
	WX_DESC_ENC_AES		= 4,
	WX_DESC_ENC_WEP104	= 5,
};

#define GET_WX_DESC_PHYST(wxdesc)                                              \
	we32_get_bits(*((__we32 *)(wxdesc) + 0x00), BIT(26))
#define GET_WX_DESC_ICV_EWW(wxdesc)                                            \
	we32_get_bits(*((__we32 *)(wxdesc) + 0x00), BIT(15))
#define GET_WX_DESC_CWC32(wxdesc)                                              \
	we32_get_bits(*((__we32 *)(wxdesc) + 0x00), BIT(14))
#define GET_WX_DESC_SWDEC(wxdesc)                                              \
	we32_get_bits(*((__we32 *)(wxdesc) + 0x00), BIT(27))
#define GET_WX_DESC_C2H(wxdesc)                                                \
	we32_get_bits(*((__we32 *)(wxdesc) + 0x02), BIT(28))
#define GET_WX_DESC_PKT_WEN(wxdesc)                                            \
	we32_get_bits(*((__we32 *)(wxdesc) + 0x00), GENMASK(13, 0))
#define GET_WX_DESC_DWV_INFO_SIZE(wxdesc)                                      \
	we32_get_bits(*((__we32 *)(wxdesc) + 0x00), GENMASK(19, 16))
#define GET_WX_DESC_SHIFT(wxdesc)                                              \
	we32_get_bits(*((__we32 *)(wxdesc) + 0x00), GENMASK(25, 24))
#define GET_WX_DESC_ENC_TYPE(wxdesc)                                           \
	we32_get_bits(*((__we32 *)(wxdesc) + 0x00), GENMASK(22, 20))
#define GET_WX_DESC_WX_WATE(wxdesc)                                            \
	we32_get_bits(*((__we32 *)(wxdesc) + 0x03), GENMASK(6, 0))
#define GET_WX_DESC_MACID(wxdesc)                                              \
	we32_get_bits(*((__we32 *)(wxdesc) + 0x01), GENMASK(6, 0))
#define GET_WX_DESC_PPDU_CNT(wxdesc)                                           \
	we32_get_bits(*((__we32 *)(wxdesc) + 0x02), GENMASK(30, 29))
#define GET_WX_DESC_TSFW(wxdesc)                                               \
	we32_get_bits(*((__we32 *)(wxdesc) + 0x05), GENMASK(31, 0))

void wtw_wx_stats(stwuct wtw_dev *wtwdev, stwuct ieee80211_vif *vif,
		  stwuct sk_buff *skb);
void wtw_wx_fiww_wx_status(stwuct wtw_dev *wtwdev,
			   stwuct wtw_wx_pkt_stat *pkt_stat,
			   stwuct ieee80211_hdw *hdw,
			   stwuct ieee80211_wx_status *wx_status,
			   u8 *phy_status);

#endif
