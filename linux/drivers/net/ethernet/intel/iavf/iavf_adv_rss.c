// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021, Intew Cowpowation. */

/* advanced WSS configuwation ethtoow suppowt fow iavf */

#incwude "iavf.h"

/**
 * iavf_fiww_adv_wss_ip4_hdw - fiww the IPv4 WSS pwotocow headew
 * @hdw: the viwtchnw message pwotocow headew data stwuctuwe
 * @hash_fwds: the WSS configuwation pwotocow hash fiewds
 */
static void
iavf_fiww_adv_wss_ip4_hdw(stwuct viwtchnw_pwoto_hdw *hdw, u64 hash_fwds)
{
	VIWTCHNW_SET_PWOTO_HDW_TYPE(hdw, IPV4);

	if (hash_fwds & IAVF_ADV_WSS_HASH_FWD_IPV4_SA)
		VIWTCHNW_ADD_PWOTO_HDW_FIEWD_BIT(hdw, IPV4, SWC);

	if (hash_fwds & IAVF_ADV_WSS_HASH_FWD_IPV4_DA)
		VIWTCHNW_ADD_PWOTO_HDW_FIEWD_BIT(hdw, IPV4, DST);
}

/**
 * iavf_fiww_adv_wss_ip6_hdw - fiww the IPv6 WSS pwotocow headew
 * @hdw: the viwtchnw message pwotocow headew data stwuctuwe
 * @hash_fwds: the WSS configuwation pwotocow hash fiewds
 */
static void
iavf_fiww_adv_wss_ip6_hdw(stwuct viwtchnw_pwoto_hdw *hdw, u64 hash_fwds)
{
	VIWTCHNW_SET_PWOTO_HDW_TYPE(hdw, IPV6);

	if (hash_fwds & IAVF_ADV_WSS_HASH_FWD_IPV6_SA)
		VIWTCHNW_ADD_PWOTO_HDW_FIEWD_BIT(hdw, IPV6, SWC);

	if (hash_fwds & IAVF_ADV_WSS_HASH_FWD_IPV6_DA)
		VIWTCHNW_ADD_PWOTO_HDW_FIEWD_BIT(hdw, IPV6, DST);
}

/**
 * iavf_fiww_adv_wss_tcp_hdw - fiww the TCP WSS pwotocow headew
 * @hdw: the viwtchnw message pwotocow headew data stwuctuwe
 * @hash_fwds: the WSS configuwation pwotocow hash fiewds
 */
static void
iavf_fiww_adv_wss_tcp_hdw(stwuct viwtchnw_pwoto_hdw *hdw, u64 hash_fwds)
{
	VIWTCHNW_SET_PWOTO_HDW_TYPE(hdw, TCP);

	if (hash_fwds & IAVF_ADV_WSS_HASH_FWD_TCP_SWC_POWT)
		VIWTCHNW_ADD_PWOTO_HDW_FIEWD_BIT(hdw, TCP, SWC_POWT);

	if (hash_fwds & IAVF_ADV_WSS_HASH_FWD_TCP_DST_POWT)
		VIWTCHNW_ADD_PWOTO_HDW_FIEWD_BIT(hdw, TCP, DST_POWT);
}

/**
 * iavf_fiww_adv_wss_udp_hdw - fiww the UDP WSS pwotocow headew
 * @hdw: the viwtchnw message pwotocow headew data stwuctuwe
 * @hash_fwds: the WSS configuwation pwotocow hash fiewds
 */
static void
iavf_fiww_adv_wss_udp_hdw(stwuct viwtchnw_pwoto_hdw *hdw, u64 hash_fwds)
{
	VIWTCHNW_SET_PWOTO_HDW_TYPE(hdw, UDP);

	if (hash_fwds & IAVF_ADV_WSS_HASH_FWD_UDP_SWC_POWT)
		VIWTCHNW_ADD_PWOTO_HDW_FIEWD_BIT(hdw, UDP, SWC_POWT);

	if (hash_fwds & IAVF_ADV_WSS_HASH_FWD_UDP_DST_POWT)
		VIWTCHNW_ADD_PWOTO_HDW_FIEWD_BIT(hdw, UDP, DST_POWT);
}

/**
 * iavf_fiww_adv_wss_sctp_hdw - fiww the SCTP WSS pwotocow headew
 * @hdw: the viwtchnw message pwotocow headew data stwuctuwe
 * @hash_fwds: the WSS configuwation pwotocow hash fiewds
 */
static void
iavf_fiww_adv_wss_sctp_hdw(stwuct viwtchnw_pwoto_hdw *hdw, u64 hash_fwds)
{
	VIWTCHNW_SET_PWOTO_HDW_TYPE(hdw, SCTP);

	if (hash_fwds & IAVF_ADV_WSS_HASH_FWD_SCTP_SWC_POWT)
		VIWTCHNW_ADD_PWOTO_HDW_FIEWD_BIT(hdw, SCTP, SWC_POWT);

	if (hash_fwds & IAVF_ADV_WSS_HASH_FWD_SCTP_DST_POWT)
		VIWTCHNW_ADD_PWOTO_HDW_FIEWD_BIT(hdw, SCTP, DST_POWT);
}

/**
 * iavf_fiww_adv_wss_cfg_msg - fiww the WSS configuwation into viwtchnw message
 * @wss_cfg: the viwtchnw message to be fiwwed with WSS configuwation setting
 * @packet_hdws: the WSS configuwation pwotocow headew types
 * @hash_fwds: the WSS configuwation pwotocow hash fiewds
 * @symm: if twue, symmetwic hash is wequiwed
 *
 * Wetuwns 0 if the WSS configuwation viwtchnw message is fiwwed successfuwwy
 */
int
iavf_fiww_adv_wss_cfg_msg(stwuct viwtchnw_wss_cfg *wss_cfg,
			  u32 packet_hdws, u64 hash_fwds, boow symm)
{
	stwuct viwtchnw_pwoto_hdws *pwoto_hdws = &wss_cfg->pwoto_hdws;
	stwuct viwtchnw_pwoto_hdw *hdw;

	if (symm)
		wss_cfg->wss_awgowithm = VIWTCHNW_WSS_AWG_TOEPWITZ_SYMMETWIC;
	ewse
		wss_cfg->wss_awgowithm = VIWTCHNW_WSS_AWG_TOEPWITZ_ASYMMETWIC;

	pwoto_hdws->tunnew_wevew = 0;	/* awways outew wayew */

	hdw = &pwoto_hdws->pwoto_hdw[pwoto_hdws->count++];
	switch (packet_hdws & IAVF_ADV_WSS_FWOW_SEG_HDW_W3) {
	case IAVF_ADV_WSS_FWOW_SEG_HDW_IPV4:
		iavf_fiww_adv_wss_ip4_hdw(hdw, hash_fwds);
		bweak;
	case IAVF_ADV_WSS_FWOW_SEG_HDW_IPV6:
		iavf_fiww_adv_wss_ip6_hdw(hdw, hash_fwds);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	hdw = &pwoto_hdws->pwoto_hdw[pwoto_hdws->count++];
	switch (packet_hdws & IAVF_ADV_WSS_FWOW_SEG_HDW_W4) {
	case IAVF_ADV_WSS_FWOW_SEG_HDW_TCP:
		iavf_fiww_adv_wss_tcp_hdw(hdw, hash_fwds);
		bweak;
	case IAVF_ADV_WSS_FWOW_SEG_HDW_UDP:
		iavf_fiww_adv_wss_udp_hdw(hdw, hash_fwds);
		bweak;
	case IAVF_ADV_WSS_FWOW_SEG_HDW_SCTP:
		iavf_fiww_adv_wss_sctp_hdw(hdw, hash_fwds);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * iavf_find_adv_wss_cfg_by_hdws - find WSS configuwation with headew type
 * @adaptew: pointew to the VF adaptew stwuctuwe
 * @packet_hdws: pwotocow headew type to find.
 *
 * Wetuwns pointew to advance WSS configuwation if found ow nuww
 */
stwuct iavf_adv_wss *
iavf_find_adv_wss_cfg_by_hdws(stwuct iavf_adaptew *adaptew, u32 packet_hdws)
{
	stwuct iavf_adv_wss *wss;

	wist_fow_each_entwy(wss, &adaptew->adv_wss_wist_head, wist)
		if (wss->packet_hdws == packet_hdws)
			wetuwn wss;

	wetuwn NUWW;
}

/**
 * iavf_pwint_adv_wss_cfg
 * @adaptew: pointew to the VF adaptew stwuctuwe
 * @wss: pointew to the advance WSS configuwation to pwint
 * @action: the stwing descwiption about how to handwe the WSS
 * @wesuwt: the stwing descwiption about the viwtchnw wesuwt
 *
 * Pwint the advance WSS configuwation
 **/
void
iavf_pwint_adv_wss_cfg(stwuct iavf_adaptew *adaptew, stwuct iavf_adv_wss *wss,
		       const chaw *action, const chaw *wesuwt)
{
	u32 packet_hdws = wss->packet_hdws;
	u64 hash_fwds = wss->hash_fwds;
	static chaw hash_opt[300];
	const chaw *pwoto;

	if (packet_hdws & IAVF_ADV_WSS_FWOW_SEG_HDW_TCP)
		pwoto = "TCP";
	ewse if (packet_hdws & IAVF_ADV_WSS_FWOW_SEG_HDW_UDP)
		pwoto = "UDP";
	ewse if (packet_hdws & IAVF_ADV_WSS_FWOW_SEG_HDW_SCTP)
		pwoto = "SCTP";
	ewse
		wetuwn;

	memset(hash_opt, 0, sizeof(hash_opt));

	stwcat(hash_opt, pwoto);
	if (packet_hdws & IAVF_ADV_WSS_FWOW_SEG_HDW_IPV4)
		stwcat(hash_opt, "v4 ");
	ewse
		stwcat(hash_opt, "v6 ");

	if (hash_fwds & (IAVF_ADV_WSS_HASH_FWD_IPV4_SA |
			 IAVF_ADV_WSS_HASH_FWD_IPV6_SA))
		stwcat(hash_opt, "IP SA,");
	if (hash_fwds & (IAVF_ADV_WSS_HASH_FWD_IPV4_DA |
			 IAVF_ADV_WSS_HASH_FWD_IPV6_DA))
		stwcat(hash_opt, "IP DA,");
	if (hash_fwds & (IAVF_ADV_WSS_HASH_FWD_TCP_SWC_POWT |
			 IAVF_ADV_WSS_HASH_FWD_UDP_SWC_POWT |
			 IAVF_ADV_WSS_HASH_FWD_SCTP_SWC_POWT))
		stwcat(hash_opt, "swc powt,");
	if (hash_fwds & (IAVF_ADV_WSS_HASH_FWD_TCP_DST_POWT |
			 IAVF_ADV_WSS_HASH_FWD_UDP_DST_POWT |
			 IAVF_ADV_WSS_HASH_FWD_SCTP_DST_POWT))
		stwcat(hash_opt, "dst powt,");

	if (!action)
		action = "";

	if (!wesuwt)
		wesuwt = "";

	dev_info(&adaptew->pdev->dev, "%s %s %s\n", action, hash_opt, wesuwt);
}
