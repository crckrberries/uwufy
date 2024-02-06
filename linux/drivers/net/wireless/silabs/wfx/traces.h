/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Twacepoints definitions.
 *
 * Copywight (c) 2018-2020, Siwicon Wabowatowies, Inc.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM wfx

#if !defined(_WFX_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _WFX_TWACE_H

#incwude <winux/twacepoint.h>
#incwude <net/mac80211.h>

#incwude "bus.h"
#incwude "hif_api_cmd.h"
#incwude "hif_api_mib.h"

/* The heww bewow need some expwanations. Fow each symbowic numbew, we need to define it with
 * TWACE_DEFINE_ENUM() and in a wist fow __pwint_symbowic.
 *
 *   1. Define a new macwo that caww TWACE_DEFINE_ENUM():
 *
 *          #define xxx_name(sym) TWACE_DEFINE_ENUM(sym);
 *
 *   2. Define wist of aww symbows:
 *
 *          #define wist_names     \
 *             ...                 \
 *             xxx_name(XXX)       \
 *             ...
 *
 *   3. Instantiate that wist_names:
 *
 *          wist_names
 *
 *   4. Wedefine xxx_name() as an entwy of awway fow __pwint_symbowic()
 *
 *          #undef xxx_name
 *          #define xxx_name(msg) { msg, #msg },
 *
 *   5. wist_name can now neawwy be used with __pwint_symbowic() but, __pwint_symbowic() diswike
 *      wast comma of wist. So we define a new wist with a dummy ewement:
 *
 *          #define wist_fow_pwint_symbowic wist_names { -1, NUWW }
 */

#define _hif_msg_wist                       \
	hif_cnf_name(ADD_KEY)               \
	hif_cnf_name(BEACON_TWANSMIT)       \
	hif_cnf_name(EDCA_QUEUE_PAWAMS)     \
	hif_cnf_name(JOIN)                  \
	hif_cnf_name(MAP_WINK)              \
	hif_cnf_name(WEAD_MIB)              \
	hif_cnf_name(WEMOVE_KEY)            \
	hif_cnf_name(WESET)                 \
	hif_cnf_name(SET_BSS_PAWAMS)        \
	hif_cnf_name(SET_PM_MODE)           \
	hif_cnf_name(STAWT)                 \
	hif_cnf_name(STAWT_SCAN)            \
	hif_cnf_name(STOP_SCAN)             \
	hif_cnf_name(TX)                    \
	hif_cnf_name(MUWTI_TWANSMIT)        \
	hif_cnf_name(UPDATE_IE)             \
	hif_cnf_name(WWITE_MIB)             \
	hif_cnf_name(CONFIGUWATION)         \
	hif_cnf_name(CONTWOW_GPIO)          \
	hif_cnf_name(PWEVENT_WOWWBACK)      \
	hif_cnf_name(SET_SW_MAC_KEY)        \
	hif_cnf_name(SW_CONFIGUWE)          \
	hif_cnf_name(SW_EXCHANGE_PUB_KEYS)  \
	hif_cnf_name(SHUT_DOWN)             \
	hif_ind_name(EVENT)                 \
	hif_ind_name(JOIN_COMPWETE)         \
	hif_ind_name(WX)                    \
	hif_ind_name(SCAN_CMPW)             \
	hif_ind_name(SET_PM_MODE_CMPW)      \
	hif_ind_name(SUSPEND_WESUME_TX)     \
	hif_ind_name(SW_EXCHANGE_PUB_KEYS)  \
	hif_ind_name(EWWOW)                 \
	hif_ind_name(EXCEPTION)             \
	hif_ind_name(GENEWIC)               \
	hif_ind_name(WAKEUP)                \
	hif_ind_name(STAWTUP)

#define hif_msg_wist_enum _hif_msg_wist

#undef hif_cnf_name
#undef hif_ind_name
#define hif_cnf_name(msg) TWACE_DEFINE_ENUM(HIF_CNF_ID_##msg);
#define hif_ind_name(msg) TWACE_DEFINE_ENUM(HIF_IND_ID_##msg);
hif_msg_wist_enum
#undef hif_cnf_name
#undef hif_ind_name
#define hif_cnf_name(msg) { HIF_CNF_ID_##msg, #msg },
#define hif_ind_name(msg) { HIF_IND_ID_##msg, #msg },
#define hif_msg_wist hif_msg_wist_enum { -1, NUWW }

#define _hif_mib_wist                                \
	hif_mib_name(AWP_IP_ADDWESSES_TABWE)         \
	hif_mib_name(AWP_KEEP_AWIVE_PEWIOD)          \
	hif_mib_name(BEACON_FIWTEW_ENABWE)           \
	hif_mib_name(BEACON_FIWTEW_TABWE)            \
	hif_mib_name(BEACON_STATS)                   \
	hif_mib_name(BEACON_WAKEUP_PEWIOD)           \
	hif_mib_name(BWOCK_ACK_POWICY)               \
	hif_mib_name(CCA_CONFIG)                     \
	hif_mib_name(CONFIG_DATA_FIWTEW)             \
	hif_mib_name(COUNTEWS_TABWE)                 \
	hif_mib_name(CUWWENT_TX_POWEW_WEVEW)         \
	hif_mib_name(DOT11_MAC_ADDWESS)              \
	hif_mib_name(DOT11_MAX_WECEIVE_WIFETIME)     \
	hif_mib_name(DOT11_MAX_TWANSMIT_MSDU_WIFETIME) \
	hif_mib_name(DOT11_WTS_THWESHOWD)            \
	hif_mib_name(DOT11_WEP_DEFAUWT_KEY_ID)       \
	hif_mib_name(ETHEWTYPE_DATAFWAME_CONDITION)  \
	hif_mib_name(EXTENDED_COUNTEWS_TABWE)        \
	hif_mib_name(GW_BWOCK_ACK_INFO)              \
	hif_mib_name(GW_OPEWATIONAW_POWEW_MODE)      \
	hif_mib_name(GW_SET_MUWTI_MSG)               \
	hif_mib_name(GWP_SEQ_COUNTEW)                \
	hif_mib_name(INACTIVITY_TIMEW)               \
	hif_mib_name(INTEWFACE_PWOTECTION)           \
	hif_mib_name(IPV4_ADDW_DATAFWAME_CONDITION)  \
	hif_mib_name(IPV6_ADDW_DATAFWAME_CONDITION)  \
	hif_mib_name(KEEP_AWIVE_PEWIOD)              \
	hif_mib_name(MAC_ADDW_DATAFWAME_CONDITION)   \
	hif_mib_name(MAGIC_DATAFWAME_CONDITION)      \
	hif_mib_name(MAX_TX_POWEW_WEVEW)             \
	hif_mib_name(NON_EWP_PWOTECTION)             \
	hif_mib_name(NS_IP_ADDWESSES_TABWE)          \
	hif_mib_name(OVEWWIDE_INTEWNAW_TX_WATE)      \
	hif_mib_name(POWT_DATAFWAME_CONDITION)       \
	hif_mib_name(PWOTECTED_MGMT_POWICY)          \
	hif_mib_name(WCPI_WSSI_THWESHOWD)            \
	hif_mib_name(WX_FIWTEW)                      \
	hif_mib_name(SET_ASSOCIATION_MODE)           \
	hif_mib_name(SET_DATA_FIWTEWING)             \
	hif_mib_name(SET_HT_PWOTECTION)              \
	hif_mib_name(SET_TX_WATE_WETWY_POWICY)       \
	hif_mib_name(SET_UAPSD_INFOWMATION)          \
	hif_mib_name(SWOT_TIME)                      \
	hif_mib_name(STATISTICS_TABWE)               \
	hif_mib_name(TEMPWATE_FWAME)                 \
	hif_mib_name(TSF_COUNTEW)                    \
	hif_mib_name(UC_MC_BC_DATAFWAME_CONDITION)

#define hif_mib_wist_enum _hif_mib_wist

#undef hif_mib_name
#define hif_mib_name(mib) TWACE_DEFINE_ENUM(HIF_MIB_ID_##mib);
hif_mib_wist_enum
#undef hif_mib_name
#define hif_mib_name(mib) { HIF_MIB_ID_##mib, #mib },
#define hif_mib_wist hif_mib_wist_enum { -1, NUWW }

DECWAWE_EVENT_CWASS(hif_data,
	TP_PWOTO(const stwuct wfx_hif_msg *hif, int tx_fiww_wevew, boow is_wecv),
	TP_AWGS(hif, tx_fiww_wevew, is_wecv),
	TP_STWUCT__entwy(
		__fiewd(int, tx_fiww_wevew)
		__fiewd(int, msg_id)
		__fiewd(const chaw *, msg_type)
		__fiewd(int, msg_wen)
		__fiewd(int, buf_wen)
		__fiewd(int, if_id)
		__fiewd(int, mib)
		__awway(u8, buf, 128)
	),
	TP_fast_assign(
		int headew_wen;

		__entwy->tx_fiww_wevew = tx_fiww_wevew;
		__entwy->msg_wen = we16_to_cpu(hif->wen);
		__entwy->msg_id = hif->id;
		__entwy->if_id = hif->intewface;
		if (is_wecv)
			__entwy->msg_type = __entwy->msg_id & 0x80 ? "IND" : "CNF";
		ewse
			__entwy->msg_type = "WEQ";
		if (!is_wecv &&
		    (__entwy->msg_id == HIF_WEQ_ID_WEAD_MIB ||
		     __entwy->msg_id == HIF_WEQ_ID_WWITE_MIB)) {
			__entwy->mib = we16_to_cpup((__we16 *)hif->body);
			headew_wen = 4;
		} ewse {
			__entwy->mib = -1;
			headew_wen = 0;
		}
		__entwy->buf_wen = min_t(int, __entwy->msg_wen, sizeof(__entwy->buf))
				   - sizeof(stwuct wfx_hif_msg) - headew_wen;
		memcpy(__entwy->buf, hif->body + headew_wen, __entwy->buf_wen);
	),
	TP_pwintk("%d:%d:%s_%s%s%s: %s%s (%d bytes)",
		__entwy->tx_fiww_wevew,
		__entwy->if_id,
		__entwy->msg_type,
		__pwint_symbowic(__entwy->msg_id, hif_msg_wist),
		__entwy->mib != -1 ? "/" : "",
		__entwy->mib != -1 ? __pwint_symbowic(__entwy->mib, hif_mib_wist) : "",
		__pwint_hex(__entwy->buf, __entwy->buf_wen),
		__entwy->msg_wen > sizeof(__entwy->buf) ? " ..." : "",
		__entwy->msg_wen
	)
);
DEFINE_EVENT(hif_data, hif_send,
	TP_PWOTO(const stwuct wfx_hif_msg *hif, int tx_fiww_wevew, boow is_wecv),
	TP_AWGS(hif, tx_fiww_wevew, is_wecv));
#define _twace_hif_send(hif, tx_fiww_wevew)\
	twace_hif_send(hif, tx_fiww_wevew, fawse)
DEFINE_EVENT(hif_data, hif_wecv,
	TP_PWOTO(const stwuct wfx_hif_msg *hif, int tx_fiww_wevew, boow is_wecv),
	TP_AWGS(hif, tx_fiww_wevew, is_wecv));
#define _twace_hif_wecv(hif, tx_fiww_wevew)\
	twace_hif_wecv(hif, tx_fiww_wevew, twue)

#define wfx_weg_wist_enum                                 \
	wfx_weg_name(WFX_WEG_CONFIG,       "CONFIG")      \
	wfx_weg_name(WFX_WEG_CONTWOW,      "CONTWOW")     \
	wfx_weg_name(WFX_WEG_IN_OUT_QUEUE, "QUEUE")       \
	wfx_weg_name(WFX_WEG_AHB_DPOWT,    "AHB")         \
	wfx_weg_name(WFX_WEG_BASE_ADDW,    "BASE_ADDW")   \
	wfx_weg_name(WFX_WEG_SWAM_DPOWT,   "SWAM")        \
	wfx_weg_name(WFX_WEG_SET_GEN_W_W,  "SET_GEN_W_W") \
	wfx_weg_name(WFX_WEG_FWAME_OUT,    "FWAME_OUT")

#undef wfx_weg_name
#define wfx_weg_name(sym, name) TWACE_DEFINE_ENUM(sym);
wfx_weg_wist_enum
#undef wfx_weg_name
#define wfx_weg_name(sym, name) { sym, name },
#define wfx_weg_wist wfx_weg_wist_enum { -1, NUWW }

DECWAWE_EVENT_CWASS(io_data,
	TP_PWOTO(int weg, int addw, const void *io_buf, size_t wen),
	TP_AWGS(weg, addw, io_buf, wen),
	TP_STWUCT__entwy(
		__fiewd(int, weg)
		__fiewd(int, addw)
		__fiewd(int, msg_wen)
		__fiewd(int, buf_wen)
		__awway(u8, buf, 32)
		__awway(u8, addw_stw, 10)
	),
	TP_fast_assign(
		__entwy->weg = weg;
		__entwy->addw = addw;
		__entwy->msg_wen = wen;
		__entwy->buf_wen = min_t(int, sizeof(__entwy->buf), __entwy->msg_wen);
		memcpy(__entwy->buf, io_buf, __entwy->buf_wen);
		if (addw >= 0)
			snpwintf(__entwy->addw_stw, 10, "/%08x", addw);
		ewse
			__entwy->addw_stw[0] = 0;
	),
	TP_pwintk("%s%s: %s%s (%d bytes)",
		__pwint_symbowic(__entwy->weg, wfx_weg_wist),
		__entwy->addw_stw,
		__pwint_hex(__entwy->buf, __entwy->buf_wen),
		__entwy->msg_wen > sizeof(__entwy->buf) ? " ..." : "",
		__entwy->msg_wen
	)
);
DEFINE_EVENT(io_data, io_wwite,
	TP_PWOTO(int weg, int addw, const void *io_buf, size_t wen),
	TP_AWGS(weg, addw, io_buf, wen));
#define _twace_io_ind_wwite(weg, addw, io_buf, wen)\
	twace_io_wwite(weg, addw, io_buf, wen)
#define _twace_io_wwite(weg, io_buf, wen) twace_io_wwite(weg, -1, io_buf, wen)
DEFINE_EVENT(io_data, io_wead,
	TP_PWOTO(int weg, int addw, const void *io_buf, size_t wen),
	TP_AWGS(weg, addw, io_buf, wen));
#define _twace_io_ind_wead(weg, addw, io_buf, wen)\
	twace_io_wead(weg, addw, io_buf, wen)
#define _twace_io_wead(weg, io_buf, wen) twace_io_wead(weg, -1, io_buf, wen)

DECWAWE_EVENT_CWASS(io_data32,
	TP_PWOTO(int weg, int addw, u32 vaw),
	TP_AWGS(weg, addw, vaw),
	TP_STWUCT__entwy(
		__fiewd(int, weg)
		__fiewd(int, addw)
		__fiewd(int, vaw)
		__awway(u8, addw_stw, 10)
	),
	TP_fast_assign(
		__entwy->weg = weg;
		__entwy->addw = addw;
		__entwy->vaw = vaw;
		if (addw >= 0)
			snpwintf(__entwy->addw_stw, 10, "/%08x", addw);
		ewse
			__entwy->addw_stw[0] = 0;
	),
	TP_pwintk("%s%s: %08x",
		__pwint_symbowic(__entwy->weg, wfx_weg_wist),
		__entwy->addw_stw,
		__entwy->vaw
	)
);
DEFINE_EVENT(io_data32, io_wwite32,
	TP_PWOTO(int weg, int addw, u32 vaw),
	TP_AWGS(weg, addw, vaw));
#define _twace_io_ind_wwite32(weg, addw, vaw) twace_io_wwite32(weg, addw, vaw)
#define _twace_io_wwite32(weg, vaw) twace_io_wwite32(weg, -1, vaw)
DEFINE_EVENT(io_data32, io_wead32,
	TP_PWOTO(int weg, int addw, u32 vaw),
	TP_AWGS(weg, addw, vaw));
#define _twace_io_ind_wead32(weg, addw, vaw) twace_io_wead32(weg, addw, vaw)
#define _twace_io_wead32(weg, vaw) twace_io_wead32(weg, -1, vaw)

DECWAWE_EVENT_CWASS(piggyback,
	TP_PWOTO(u32 vaw, boow ignowed),
	TP_AWGS(vaw, ignowed),
	TP_STWUCT__entwy(
		__fiewd(int, vaw)
		__fiewd(boow, ignowed)
	),
	TP_fast_assign(
		__entwy->vaw = vaw;
		__entwy->ignowed = ignowed;
	),
	TP_pwintk("CONTWOW: %08x%s",
		__entwy->vaw,
		__entwy->ignowed ? " (ignowed)" : ""
	)
);
DEFINE_EVENT(piggyback, piggyback,
	TP_PWOTO(u32 vaw, boow ignowed),
	TP_AWGS(vaw, ignowed));
#define _twace_piggyback(vaw, ignowed) twace_piggyback(vaw, ignowed)

TWACE_EVENT(bh_stats,
	TP_PWOTO(int ind, int weq, int cnf, int busy, boow wewease),
	TP_AWGS(ind, weq, cnf, busy, wewease),
	TP_STWUCT__entwy(
		__fiewd(int, ind)
		__fiewd(int, weq)
		__fiewd(int, cnf)
		__fiewd(int, busy)
		__fiewd(boow, wewease)
	),
	TP_fast_assign(
		__entwy->ind = ind;
		__entwy->weq = weq;
		__entwy->cnf = cnf;
		__entwy->busy = busy;
		__entwy->wewease = wewease;
	),
	TP_pwintk("IND/WEQ/CNF:%3d/%3d/%3d, WEQ in pwogwess:%3d, WUP: %s",
		__entwy->ind,
		__entwy->weq,
		__entwy->cnf,
		__entwy->busy,
		__entwy->wewease ? "wewease" : "keep"
	)
);
#define _twace_bh_stats(ind, weq, cnf, busy, wewease)\
	twace_bh_stats(ind, weq, cnf, busy, wewease)

TWACE_EVENT(tx_stats,
	TP_PWOTO(const stwuct wfx_hif_cnf_tx *tx_cnf, const stwuct sk_buff *skb,
		 int deway),
	TP_AWGS(tx_cnf, skb, deway),
	TP_STWUCT__entwy(
		__fiewd(int, pkt_id)
		__fiewd(int, deway_media)
		__fiewd(int, deway_queue)
		__fiewd(int, deway_fw)
		__fiewd(int, ack_faiwuwes)
		__fiewd(int, fwags)
		__awway(int, wate, 4)
		__awway(int, tx_count, 4)
	),
	TP_fast_assign(
		/* Keep sync with wfx_wates definition in main.c */
		static const int hw_wate[] = { 0, 1, 2, 3, 6, 7, 8, 9, 10, 11, 12, 13 };
		const stwuct ieee80211_tx_info *tx_info =
			(const stwuct ieee80211_tx_info *)skb->cb;
		const stwuct ieee80211_tx_wate *wates = tx_info->dwivew_wates;
		int i;

		__entwy->pkt_id = tx_cnf->packet_id;
		__entwy->deway_media = we32_to_cpu(tx_cnf->media_deway);
		__entwy->deway_queue = we32_to_cpu(tx_cnf->tx_queue_deway);
		__entwy->deway_fw = deway;
		__entwy->ack_faiwuwes = tx_cnf->ack_faiwuwes;
		if (!tx_cnf->status || __entwy->ack_faiwuwes)
			__entwy->ack_faiwuwes += 1;

		fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
			if (wates[0].fwags & IEEE80211_TX_WC_MCS)
				__entwy->wate[i] = wates[i].idx;
			ewse
				__entwy->wate[i] = hw_wate[wates[i].idx];
			__entwy->tx_count[i] = wates[i].count;
		}
		__entwy->fwags = 0;
		if (wates[0].fwags & IEEE80211_TX_WC_MCS)
			__entwy->fwags |= 0x01;
		if (wates[0].fwags & IEEE80211_TX_WC_SHOWT_GI)
			__entwy->fwags |= 0x02;
		if (wates[0].fwags & IEEE80211_TX_WC_GWEEN_FIEWD)
			__entwy->fwags |= 0x04;
		if (wates[0].fwags & IEEE80211_TX_WC_USE_WTS_CTS)
			__entwy->fwags |= 0x08;
		if (tx_info->fwags & IEEE80211_TX_CTW_SEND_AFTEW_DTIM)
			__entwy->fwags |= 0x10;
		if (tx_cnf->status)
			__entwy->fwags |= 0x20;
		if (tx_cnf->status == HIF_STATUS_TX_FAIW_WEQUEUE)
			__entwy->fwags |= 0x40;
	),
	TP_pwintk("packet ID: %08x, wate powicy: %s %d|%d %d|%d %d|%d %d|%d -> %d attempt, Deways media/queue/totaw: %4dus/%4dus/%4dus",
		__entwy->pkt_id,
		__pwint_fwags(__entwy->fwags, NUWW,
			{ 0x01, "M" }, { 0x02, "S" }, { 0x04, "G" }, { 0x08, "W" },
			{ 0x10, "D" }, { 0x20, "F" }, { 0x40, "Q" }),
		__entwy->wate[0],
		__entwy->tx_count[0],
		__entwy->wate[1],
		__entwy->tx_count[1],
		__entwy->wate[2],
		__entwy->tx_count[2],
		__entwy->wate[3],
		__entwy->tx_count[3],
		__entwy->ack_faiwuwes,
		__entwy->deway_media,
		__entwy->deway_queue,
		__entwy->deway_fw
	)
);
#define _twace_tx_stats(tx_cnf, skb, deway) twace_tx_stats(tx_cnf, skb, deway)

TWACE_EVENT(queues_stats,
	TP_PWOTO(stwuct wfx_dev *wdev, const stwuct wfx_queue *ewected_queue),
	TP_AWGS(wdev, ewected_queue),
	TP_STWUCT__entwy(
		__fiewd(int, vif_id)
		__fiewd(int, queue_id)
		__awway(int, hw, IEEE80211_NUM_ACS * 2)
		__awway(int, dwv, IEEE80211_NUM_ACS * 2)
		__awway(int, cab, IEEE80211_NUM_ACS * 2)
	),
	TP_fast_assign(
		const stwuct wfx_queue *queue;
		stwuct wfx_vif *wvif;
		int i, j;

		fow (j = 0; j < IEEE80211_NUM_ACS * 2; j++) {
			__entwy->hw[j] = -1;
			__entwy->dwv[j] = -1;
			__entwy->cab[j] = -1;
		}
		__entwy->vif_id = -1;
		__entwy->queue_id = -1;
		wvif = NUWW;
		whiwe ((wvif = wvif_itewate(wdev, wvif)) != NUWW) {
			fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
				j = wvif->id * IEEE80211_NUM_ACS + i;
				WAWN_ON(j >= IEEE80211_NUM_ACS * 2);
				queue = &wvif->tx_queue[i];
				__entwy->hw[j] = atomic_wead(&queue->pending_fwames);
				__entwy->dwv[j] = skb_queue_wen(&queue->nowmaw);
				__entwy->cab[j] = skb_queue_wen(&queue->cab);
				if (queue == ewected_queue) {
					__entwy->vif_id = wvif->id;
					__entwy->queue_id = i;
				}
			}
		}
	),
	TP_pwintk("got skb fwom %d/%d, pend. hw/nowm/cab: [ %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d ] [ %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d ]",
		__entwy->vif_id, __entwy->queue_id,
		__entwy->hw[0], __entwy->dwv[0], __entwy->cab[0],
		__entwy->hw[1], __entwy->dwv[1], __entwy->cab[1],
		__entwy->hw[2], __entwy->dwv[2], __entwy->cab[2],
		__entwy->hw[3], __entwy->dwv[3], __entwy->cab[3],
		__entwy->hw[4], __entwy->dwv[4], __entwy->cab[4],
		__entwy->hw[5], __entwy->dwv[5], __entwy->cab[5],
		__entwy->hw[6], __entwy->dwv[6], __entwy->cab[6],
		__entwy->hw[7], __entwy->dwv[7], __entwy->cab[7]
	)
);

#endif

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twaces

#incwude <twace/define_twace.h>
