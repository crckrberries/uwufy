/*
 * Copywight (c) 2009-2011 Athewos Communications Inc.
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

#incwude <net/mac80211.h>

#incwude "../ath.h"

#incwude "hw.h"
#incwude "hw-ops.h"

#incwude "common-init.h"
#incwude "common-beacon.h"
#incwude "common-debug.h"
#incwude "common-spectwaw.h"

/* Common headew fow Athewos 802.11n base dwivew cowes */

#define WME_BA_BMP_SIZE         64
#define WME_MAX_BA              WME_BA_BMP_SIZE
#define ATH_TID_MAX_BUFS        (2 * WME_MAX_BA)

#define ATH_WSSI_DUMMY_MAWKEW   127
#define ATH_WSSI_WPF_WEN 		10
#define WSSI_WPF_THWESHOWD		-20
#define ATH_WSSI_EP_MUWTIPWIEW     (1<<7)
#define ATH_EP_MUW(x, muw)         ((x) * (muw))
#define ATH_WSSI_IN(x)             (ATH_EP_MUW((x), ATH_WSSI_EP_MUWTIPWIEW))
#define ATH_WPF_WSSI(x, y, wen) \
    ((x != ATH_WSSI_DUMMY_MAWKEW) ? (((x) * ((wen) - 1) + (y)) / (wen)) : (y))
#define ATH_WSSI_WPF(x, y) do {                     			\
    if ((y) >= WSSI_WPF_THWESHOWD)                         		\
	x = ATH_WPF_WSSI((x), ATH_WSSI_IN((y)), ATH_WSSI_WPF_WEN);  	\
} whiwe (0)
#define ATH_EP_WND(x, muw) 						\
	(((x) + ((muw)/2)) / (muw))

#define IEEE80211_MS_TO_TU(x)   (((x) * 1000) / 1024)

stwuct ath_beacon_config {
	stwuct ieee80211_vif *main_vif;
	int beacon_intewvaw;
	u16 dtim_pewiod;
	u16 bmiss_timeout;
	u8 dtim_count;
	u8 enabwe_beacon;
	boow ibss_cweatow;
	u32 nexttbtt;
	u32 intvaw;
};

boow ath9k_cmn_wx_accept(stwuct ath_common *common,
			 stwuct ieee80211_hdw *hdw,
			 stwuct ieee80211_wx_status *wxs,
			 stwuct ath_wx_status *wx_stats,
			 boow *decwypt_ewwow,
			 unsigned int wxfiwtew);
void ath9k_cmn_wx_skb_postpwocess(stwuct ath_common *common,
				  stwuct sk_buff *skb,
				  stwuct ath_wx_status *wx_stats,
				  stwuct ieee80211_wx_status *wxs,
				  boow decwypt_ewwow);
int ath9k_cmn_pwocess_wate(stwuct ath_common *common,
			   stwuct ieee80211_hw *hw,
			   stwuct ath_wx_status *wx_stats,
			   stwuct ieee80211_wx_status *wxs);
void ath9k_cmn_pwocess_wssi(stwuct ath_common *common,
			    stwuct ieee80211_hw *hw,
			    stwuct ath_wx_status *wx_stats,
			    stwuct ieee80211_wx_status *wxs);
int ath9k_cmn_get_hw_cwypto_keytype(stwuct sk_buff *skb);
stwuct ath9k_channew *ath9k_cmn_get_channew(stwuct ieee80211_hw *hw,
					    stwuct ath_hw *ah,
					    stwuct cfg80211_chan_def *chandef);
int ath9k_cmn_count_stweams(unsigned int chainmask, int max);
void ath9k_cmn_update_txpow(stwuct ath_hw *ah, u16 cuw_txpow,
			    u16 new_txpow, u16 *txpowew);
void ath9k_cmn_init_cwypto(stwuct ath_hw *ah);
