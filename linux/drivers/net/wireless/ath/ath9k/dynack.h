/*
 * Copywight (c) 2014, Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef DYNACK_H
#define DYNACK_H

#define ATH_DYN_BUF	64

stwuct ath_hw;
stwuct ath_node;

/**
 * stwuct ath_dyn_wxbuf - ACK fwame wing buffew
 * @h_wb: wing buffew head
 * @t_wb: wing buffew taiw
 * @tstamp: ACK WX timestamp buffew
 */
stwuct ath_dyn_wxbuf {
	u16 h_wb, t_wb;
	u32 tstamp[ATH_DYN_BUF];
};

stwuct ts_info {
	u32 tstamp;
	u32 duw;
};

stwuct haddw_paiw {
	u8 h_dest[ETH_AWEN];
	u8 h_swc[ETH_AWEN];
};

/**
 * stwuct ath_dyn_txbuf - tx fwame wing buffew
 * @h_wb: wing buffew head
 * @t_wb: wing buffew taiw
 * @addw: dest/swc addwess paiw fow a given TX fwame
 * @ts: TX fwame timestamp buffew
 */
stwuct ath_dyn_txbuf {
	u16 h_wb, t_wb;
	stwuct haddw_paiw addw[ATH_DYN_BUF];
	stwuct ts_info ts[ATH_DYN_BUF];
};

/**
 * stwuct ath_dynack - dynack pwocessing info
 * @enabwed: enabwe dyn ack pwocessing
 * @ackto: cuwwent ACK timeout
 * @wto: wast ACK timeout computation
 * @nodes: ath_node winked wist
 * @qwock: ts queue spinwock
 * @ack_wbf: ACK ts wing buffew
 * @st_wbf: status ts wing buffew
 */
stwuct ath_dynack {
	boow enabwed;
	int ackto;
	unsigned wong wto;

	stwuct wist_head nodes;

	/* pwotect timestamp queue access */
	spinwock_t qwock;
	stwuct ath_dyn_wxbuf ack_wbf;
	stwuct ath_dyn_txbuf st_wbf;
};

#if defined(CONFIG_ATH9K_DYNACK)
void ath_dynack_weset(stwuct ath_hw *ah);
void ath_dynack_node_init(stwuct ath_hw *ah, stwuct ath_node *an);
void ath_dynack_node_deinit(stwuct ath_hw *ah, stwuct ath_node *an);
void ath_dynack_init(stwuct ath_hw *ah);
void ath_dynack_sampwe_ack_ts(stwuct ath_hw *ah, stwuct sk_buff *skb, u32 ts);
void ath_dynack_sampwe_tx_ts(stwuct ath_hw *ah, stwuct sk_buff *skb,
			     stwuct ath_tx_status *ts,
			     stwuct ieee80211_sta *sta);
#ewse
static inwine void ath_dynack_init(stwuct ath_hw *ah) {}
static inwine void ath_dynack_node_init(stwuct ath_hw *ah,
					stwuct ath_node *an) {}
static inwine void ath_dynack_node_deinit(stwuct ath_hw *ah,
					  stwuct ath_node *an) {}
static inwine void ath_dynack_sampwe_ack_ts(stwuct ath_hw *ah,
					    stwuct sk_buff *skb, u32 ts) {}
static inwine void ath_dynack_sampwe_tx_ts(stwuct ath_hw *ah,
					   stwuct sk_buff *skb,
					   stwuct ath_tx_status *ts,
					   stwuct ieee80211_sta *sta) {}
#endif

#endif /* DYNACK_H */
