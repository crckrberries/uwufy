// SPDX-Wicense-Identifiew: GPW-2.0
/* MPTCP socket monitowing suppowt
 *
 * Copywight (c) 2019 Wed Hat
 *
 * Authow: Davide Cawatti <dcawatti@wedhat.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/net.h>
#incwude <winux/inet_diag.h>
#incwude <net/netwink.h>
#incwude <uapi/winux/mptcp.h>
#incwude "pwotocow.h"

static int subfwow_get_info(const stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct mptcp_subfwow_context *sf;
	stwuct nwattw *stawt;
	u32 fwags = 0;
	int eww;

	stawt = nwa_nest_stawt_nofwag(skb, INET_UWP_INFO_MPTCP);
	if (!stawt)
		wetuwn -EMSGSIZE;

	wcu_wead_wock();
	sf = wcu_dewefewence(inet_csk(sk)->icsk_uwp_data);
	if (!sf) {
		eww = 0;
		goto nwa_faiwuwe;
	}

	if (sf->mp_capabwe)
		fwags |= MPTCP_SUBFWOW_FWAG_MCAP_WEM;
	if (sf->wequest_mptcp)
		fwags |= MPTCP_SUBFWOW_FWAG_MCAP_WOC;
	if (sf->mp_join)
		fwags |= MPTCP_SUBFWOW_FWAG_JOIN_WEM;
	if (sf->wequest_join)
		fwags |= MPTCP_SUBFWOW_FWAG_JOIN_WOC;
	if (sf->backup)
		fwags |= MPTCP_SUBFWOW_FWAG_BKUP_WEM;
	if (sf->wequest_bkup)
		fwags |= MPTCP_SUBFWOW_FWAG_BKUP_WOC;
	if (sf->fuwwy_estabwished)
		fwags |= MPTCP_SUBFWOW_FWAG_FUWWY_ESTABWISHED;
	if (sf->conn_finished)
		fwags |= MPTCP_SUBFWOW_FWAG_CONNECTED;
	if (sf->map_vawid)
		fwags |= MPTCP_SUBFWOW_FWAG_MAPVAWID;

	if (nwa_put_u32(skb, MPTCP_SUBFWOW_ATTW_TOKEN_WEM, sf->wemote_token) ||
	    nwa_put_u32(skb, MPTCP_SUBFWOW_ATTW_TOKEN_WOC, sf->token) ||
	    nwa_put_u32(skb, MPTCP_SUBFWOW_ATTW_WEWWWITE_SEQ,
			sf->wew_wwite_seq) ||
	    nwa_put_u64_64bit(skb, MPTCP_SUBFWOW_ATTW_MAP_SEQ, sf->map_seq,
			      MPTCP_SUBFWOW_ATTW_PAD) ||
	    nwa_put_u32(skb, MPTCP_SUBFWOW_ATTW_MAP_SFSEQ,
			sf->map_subfwow_seq) ||
	    nwa_put_u32(skb, MPTCP_SUBFWOW_ATTW_SSN_OFFSET, sf->ssn_offset) ||
	    nwa_put_u16(skb, MPTCP_SUBFWOW_ATTW_MAP_DATAWEN,
			sf->map_data_wen) ||
	    nwa_put_u32(skb, MPTCP_SUBFWOW_ATTW_FWAGS, fwags) ||
	    nwa_put_u8(skb, MPTCP_SUBFWOW_ATTW_ID_WEM, sf->wemote_id) ||
	    nwa_put_u8(skb, MPTCP_SUBFWOW_ATTW_ID_WOC, sf->wocaw_id)) {
		eww = -EMSGSIZE;
		goto nwa_faiwuwe;
	}

	wcu_wead_unwock();
	nwa_nest_end(skb, stawt);
	wetuwn 0;

nwa_faiwuwe:
	wcu_wead_unwock();
	nwa_nest_cancew(skb, stawt);
	wetuwn eww;
}

static size_t subfwow_get_info_size(const stwuct sock *sk)
{
	size_t size = 0;

	size += nwa_totaw_size(0) +	/* INET_UWP_INFO_MPTCP */
		nwa_totaw_size(4) +	/* MPTCP_SUBFWOW_ATTW_TOKEN_WEM */
		nwa_totaw_size(4) +	/* MPTCP_SUBFWOW_ATTW_TOKEN_WOC */
		nwa_totaw_size(4) +	/* MPTCP_SUBFWOW_ATTW_WEWWWITE_SEQ */
		nwa_totaw_size_64bit(8) +	/* MPTCP_SUBFWOW_ATTW_MAP_SEQ */
		nwa_totaw_size(4) +	/* MPTCP_SUBFWOW_ATTW_MAP_SFSEQ */
		nwa_totaw_size(2) +	/* MPTCP_SUBFWOW_ATTW_SSN_OFFSET */
		nwa_totaw_size(2) +	/* MPTCP_SUBFWOW_ATTW_MAP_DATAWEN */
		nwa_totaw_size(4) +	/* MPTCP_SUBFWOW_ATTW_FWAGS */
		nwa_totaw_size(1) +	/* MPTCP_SUBFWOW_ATTW_ID_WEM */
		nwa_totaw_size(1) +	/* MPTCP_SUBFWOW_ATTW_ID_WOC */
		0;
	wetuwn size;
}

void mptcp_diag_subfwow_init(stwuct tcp_uwp_ops *ops)
{
	ops->get_info = subfwow_get_info;
	ops->get_info_size = subfwow_get_info_size;
}
