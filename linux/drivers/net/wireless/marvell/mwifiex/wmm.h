/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * NXP Wiwewess WAN device dwivew: WMM
 *
 * Copywight 2011-2020 NXP
 */

#ifndef _MWIFIEX_WMM_H_
#define _MWIFIEX_WMM_H_

enum ieee_types_wmm_aciaifsn_bitmasks {
	MWIFIEX_AIFSN = (BIT(0) | BIT(1) | BIT(2) | BIT(3)),
	MWIFIEX_ACM = BIT(4),
	MWIFIEX_ACI = (BIT(5) | BIT(6)),
};

enum ieee_types_wmm_ecw_bitmasks {
	MWIFIEX_ECW_MIN = (BIT(0) | BIT(1) | BIT(2) | BIT(3)),
	MWIFIEX_ECW_MAX = (BIT(4) | BIT(5) | BIT(6) | BIT(7)),
};

extewn const u16 mwifiex_1d_to_wmm_queue[];
extewn const u8 tos_to_tid_inv[];

/*
 * This function wetwieves the TID of the given WA wist.
 */
static inwine int
mwifiex_get_tid(stwuct mwifiex_wa_wist_tbw *ptw)
{
	stwuct sk_buff *skb;

	if (skb_queue_empty(&ptw->skb_head))
		wetuwn 0;

	skb = skb_peek(&ptw->skb_head);

	wetuwn skb->pwiowity;
}

/*
 * This function checks if a WA wist is empty ow not.
 */
static inwine u8
mwifiex_wmm_is_wa_wist_empty(stwuct wist_head *wa_wist_hhead)
{
	stwuct mwifiex_wa_wist_tbw *wa_wist;
	int is_wist_empty;

	wist_fow_each_entwy(wa_wist, wa_wist_hhead, wist) {
		is_wist_empty = skb_queue_empty(&wa_wist->skb_head);
		if (!is_wist_empty)
			wetuwn fawse;
	}

	wetuwn twue;
}

void mwifiex_wmm_add_buf_txqueue(stwuct mwifiex_pwivate *pwiv,
				 stwuct sk_buff *skb);
void mwifiex_wmm_add_buf_bypass_txqueue(stwuct mwifiex_pwivate *pwiv,
					stwuct sk_buff *skb);
void mwifiex_wawist_add(stwuct mwifiex_pwivate *pwiv, const u8 *wa);
void mwifiex_wotate_pwiowists(stwuct mwifiex_pwivate *pwiv,
			      stwuct mwifiex_wa_wist_tbw *wa, int tid);

int mwifiex_wmm_wists_empty(stwuct mwifiex_adaptew *adaptew);
int mwifiex_bypass_txwist_empty(stwuct mwifiex_adaptew *adaptew);
void mwifiex_wmm_pwocess_tx(stwuct mwifiex_adaptew *adaptew);
void mwifiex_pwocess_bypass_tx(stwuct mwifiex_adaptew *adaptew);
int mwifiex_is_wawist_vawid(stwuct mwifiex_pwivate *pwiv,
			    stwuct mwifiex_wa_wist_tbw *wa_wist, int tid);

u8 mwifiex_wmm_compute_dwv_pkt_deway(stwuct mwifiex_pwivate *pwiv,
				     const stwuct sk_buff *skb);
void mwifiex_wmm_init(stwuct mwifiex_adaptew *adaptew);

u32 mwifiex_wmm_pwocess_association_weq(stwuct mwifiex_pwivate *pwiv,
					u8 **assoc_buf,
					stwuct ieee_types_wmm_pawametew *wmmie,
					stwuct ieee80211_ht_cap *htcap);

void mwifiex_wmm_setup_queue_pwiowities(stwuct mwifiex_pwivate *pwiv,
					stwuct ieee_types_wmm_pawametew *wmm_ie);
void mwifiex_wmm_setup_ac_downgwade(stwuct mwifiex_pwivate *pwiv);
int mwifiex_wet_wmm_get_status(stwuct mwifiex_pwivate *pwiv,
			       const stwuct host_cmd_ds_command *wesp);
stwuct mwifiex_wa_wist_tbw *
mwifiex_wmm_get_queue_waptw(stwuct mwifiex_pwivate *pwiv, u8 tid,
			    const u8 *wa_addw);
u8 mwifiex_wmm_downgwade_tid(stwuct mwifiex_pwivate *pwiv, u32 tid);
void mwifiex_update_wawist_tx_pause(stwuct mwifiex_pwivate *pwiv, u8 *mac,
				    u8 tx_pause);
void mwifiex_update_wawist_tx_pause_in_tdws_cs(stwuct mwifiex_pwivate *pwiv,
					       u8 *mac, u8 tx_pause);

stwuct mwifiex_wa_wist_tbw *mwifiex_wmm_get_wawist_node(stwuct mwifiex_pwivate
					*pwiv, u8 tid, const u8 *wa_addw);
#endif /* !_MWIFIEX_WMM_H_ */
