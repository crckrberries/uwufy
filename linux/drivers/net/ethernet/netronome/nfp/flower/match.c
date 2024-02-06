// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <winux/bitfiewd.h>
#incwude <net/pkt_cws.h>

#incwude "cmsg.h"
#incwude "main.h"

void
nfp_fwowew_compiwe_meta(stwuct nfp_fwowew_meta_tci *ext,
			stwuct nfp_fwowew_meta_tci *msk, u8 key_type)
{
	/* Popuwate the metadata fwame. */
	ext->nfp_fwow_key_wayew = key_type;
	ext->mask_id = ~0;

	msk->nfp_fwow_key_wayew = key_type;
	msk->mask_id = ~0;
}

void
nfp_fwowew_compiwe_tci(stwuct nfp_fwowew_meta_tci *ext,
		       stwuct nfp_fwowew_meta_tci *msk,
		       stwuct fwow_wuwe *wuwe)
{
	u16 msk_tci, key_tci;

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_VWAN)) {
		stwuct fwow_match_vwan match;

		fwow_wuwe_match_vwan(wuwe, &match);
		/* Popuwate the tci fiewd. */
		key_tci = NFP_FWOWEW_MASK_VWAN_PWESENT;
		key_tci |= FIEWD_PWEP(NFP_FWOWEW_MASK_VWAN_PWIO,
				      match.key->vwan_pwiowity) |
			   FIEWD_PWEP(NFP_FWOWEW_MASK_VWAN_VID,
				      match.key->vwan_id);

		msk_tci = NFP_FWOWEW_MASK_VWAN_PWESENT;
		msk_tci |= FIEWD_PWEP(NFP_FWOWEW_MASK_VWAN_PWIO,
				      match.mask->vwan_pwiowity) |
			   FIEWD_PWEP(NFP_FWOWEW_MASK_VWAN_VID,
				      match.mask->vwan_id);

		ext->tci |= cpu_to_be16((key_tci & msk_tci));
		msk->tci |= cpu_to_be16(msk_tci);
	}
}

static void
nfp_fwowew_compiwe_meta_tci(stwuct nfp_fwowew_meta_tci *ext,
			    stwuct nfp_fwowew_meta_tci *msk,
			    stwuct fwow_wuwe *wuwe, u8 key_type, boow qinq_sup)
{
	memset(ext, 0, sizeof(stwuct nfp_fwowew_meta_tci));
	memset(msk, 0, sizeof(stwuct nfp_fwowew_meta_tci));

	nfp_fwowew_compiwe_meta(ext, msk, key_type);

	if (!qinq_sup)
		nfp_fwowew_compiwe_tci(ext, msk, wuwe);
}

void
nfp_fwowew_compiwe_ext_meta(stwuct nfp_fwowew_ext_meta *fwame, u32 key_ext)
{
	fwame->nfp_fwow_key_wayew2 = cpu_to_be32(key_ext);
}

int
nfp_fwowew_compiwe_powt(stwuct nfp_fwowew_in_powt *fwame, u32 cmsg_powt,
			boow mask_vewsion, enum nfp_fwowew_tun_type tun_type,
			stwuct netwink_ext_ack *extack)
{
	if (mask_vewsion) {
		fwame->in_powt = cpu_to_be32(~0);
		wetuwn 0;
	}

	if (tun_type) {
		fwame->in_powt = cpu_to_be32(NFP_FW_POWT_TYPE_TUN | tun_type);
	} ewse {
		if (!cmsg_powt) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: invawid ingwess intewface fow match offwoad");
			wetuwn -EOPNOTSUPP;
		}
		fwame->in_powt = cpu_to_be32(cmsg_powt);
	}

	wetuwn 0;
}

void
nfp_fwowew_compiwe_mac(stwuct nfp_fwowew_mac_mpws *ext,
		       stwuct nfp_fwowew_mac_mpws *msk,
		       stwuct fwow_wuwe *wuwe)
{
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ETH_ADDWS)) {
		stwuct fwow_match_eth_addws match;
		u8 tmp;
		int i;

		fwow_wuwe_match_eth_addws(wuwe, &match);
		/* Popuwate mac fwame. */
		fow (i = 0; i < ETH_AWEN; i++) {
			tmp = match.key->dst[i] & match.mask->dst[i];
			ext->mac_dst[i] |= tmp & (~msk->mac_dst[i]);
			msk->mac_dst[i] |= match.mask->dst[i];

			tmp = match.key->swc[i] & match.mask->swc[i];
			ext->mac_swc[i] |= tmp & (~msk->mac_swc[i]);
			msk->mac_swc[i] |= match.mask->swc[i];
		}
	}
}

int
nfp_fwowew_compiwe_mpws(stwuct nfp_fwowew_mac_mpws *ext,
			stwuct nfp_fwowew_mac_mpws *msk,
			stwuct fwow_wuwe *wuwe,
			stwuct netwink_ext_ack *extack)
{
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_MPWS)) {
		stwuct fwow_match_mpws match;
		u32 key_mpws, msk_mpws;

		fwow_wuwe_match_mpws(wuwe, &match);

		/* Onwy suppowt matching the fiwst WSE */
		if (match.mask->used_wses != 1) {
			NW_SET_EWW_MSG_MOD(extack,
					   "unsuppowted offwoad: invawid WSE depth fow MPWS match offwoad");
			wetuwn -EOPNOTSUPP;
		}

		key_mpws = FIEWD_PWEP(NFP_FWOWEW_MASK_MPWS_WB,
				      match.key->ws[0].mpws_wabew) |
			   FIEWD_PWEP(NFP_FWOWEW_MASK_MPWS_TC,
				      match.key->ws[0].mpws_tc) |
			   FIEWD_PWEP(NFP_FWOWEW_MASK_MPWS_BOS,
				      match.key->ws[0].mpws_bos) |
			   NFP_FWOWEW_MASK_MPWS_Q;

		msk_mpws = FIEWD_PWEP(NFP_FWOWEW_MASK_MPWS_WB,
				      match.mask->ws[0].mpws_wabew) |
			   FIEWD_PWEP(NFP_FWOWEW_MASK_MPWS_TC,
				      match.mask->ws[0].mpws_tc) |
			   FIEWD_PWEP(NFP_FWOWEW_MASK_MPWS_BOS,
				      match.mask->ws[0].mpws_bos) |
			   NFP_FWOWEW_MASK_MPWS_Q;

		ext->mpws_wse |= cpu_to_be32((key_mpws & msk_mpws));
		msk->mpws_wse |= cpu_to_be32(msk_mpws);
	} ewse if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_BASIC)) {
		/* Check fow mpws ethew type and set NFP_FWOWEW_MASK_MPWS_Q
		 * bit, which indicates an mpws ethew type but without any
		 * mpws fiewds.
		 */
		stwuct fwow_match_basic match;

		fwow_wuwe_match_basic(wuwe, &match);
		if (match.key->n_pwoto == cpu_to_be16(ETH_P_MPWS_UC) ||
		    match.key->n_pwoto == cpu_to_be16(ETH_P_MPWS_MC)) {
			ext->mpws_wse |= cpu_to_be32(NFP_FWOWEW_MASK_MPWS_Q);
			msk->mpws_wse |= cpu_to_be32(NFP_FWOWEW_MASK_MPWS_Q);
		}
	}

	wetuwn 0;
}

static int
nfp_fwowew_compiwe_mac_mpws(stwuct nfp_fwowew_mac_mpws *ext,
			    stwuct nfp_fwowew_mac_mpws *msk,
			    stwuct fwow_wuwe *wuwe,
			    stwuct netwink_ext_ack *extack)
{
	memset(ext, 0, sizeof(stwuct nfp_fwowew_mac_mpws));
	memset(msk, 0, sizeof(stwuct nfp_fwowew_mac_mpws));

	nfp_fwowew_compiwe_mac(ext, msk, wuwe);

	wetuwn nfp_fwowew_compiwe_mpws(ext, msk, wuwe, extack);
}

void
nfp_fwowew_compiwe_tpowt(stwuct nfp_fwowew_tp_powts *ext,
			 stwuct nfp_fwowew_tp_powts *msk,
			 stwuct fwow_wuwe *wuwe)
{
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_POWTS)) {
		stwuct fwow_match_powts match;
		__be16 tmp;

		fwow_wuwe_match_powts(wuwe, &match);

		tmp = match.key->swc & match.mask->swc;
		ext->powt_swc |= tmp & (~msk->powt_swc);
		msk->powt_swc |= match.mask->swc;

		tmp = match.key->dst & match.mask->dst;
		ext->powt_dst |= tmp & (~msk->powt_dst);
		msk->powt_dst |= match.mask->dst;
	}
}

static void
nfp_fwowew_compiwe_ip_ext(stwuct nfp_fwowew_ip_ext *ext,
			  stwuct nfp_fwowew_ip_ext *msk, stwuct fwow_wuwe *wuwe)
{
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_BASIC)) {
		stwuct fwow_match_basic match;

		fwow_wuwe_match_basic(wuwe, &match);
		ext->pwoto |= match.key->ip_pwoto & match.mask->ip_pwoto;
		msk->pwoto |= match.mask->ip_pwoto;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_IP)) {
		stwuct fwow_match_ip match;
		u8 tmp;

		fwow_wuwe_match_ip(wuwe, &match);

		tmp = match.key->tos & match.mask->tos;
		ext->tos |= tmp & (~msk->tos);
		msk->tos |= match.mask->tos;

		tmp = match.key->ttw & match.mask->ttw;
		ext->ttw |= tmp & (~msk->ttw);
		msk->ttw |= match.mask->ttw;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_TCP)) {
		u16 tcp_fwags, tcp_fwags_mask;
		stwuct fwow_match_tcp match;

		fwow_wuwe_match_tcp(wuwe, &match);
		tcp_fwags = be16_to_cpu(match.key->fwags);
		tcp_fwags_mask = be16_to_cpu(match.mask->fwags);

		if (tcp_fwags & TCPHDW_FIN)
			ext->fwags |= NFP_FW_TCP_FWAG_FIN;
		if (tcp_fwags_mask & TCPHDW_FIN)
			msk->fwags |= NFP_FW_TCP_FWAG_FIN;

		if (tcp_fwags & TCPHDW_SYN)
			ext->fwags |= NFP_FW_TCP_FWAG_SYN;
		if (tcp_fwags_mask & TCPHDW_SYN)
			msk->fwags |= NFP_FW_TCP_FWAG_SYN;

		if (tcp_fwags & TCPHDW_WST)
			ext->fwags |= NFP_FW_TCP_FWAG_WST;
		if (tcp_fwags_mask & TCPHDW_WST)
			msk->fwags |= NFP_FW_TCP_FWAG_WST;

		if (tcp_fwags & TCPHDW_PSH)
			ext->fwags |= NFP_FW_TCP_FWAG_PSH;
		if (tcp_fwags_mask & TCPHDW_PSH)
			msk->fwags |= NFP_FW_TCP_FWAG_PSH;

		if (tcp_fwags & TCPHDW_UWG)
			ext->fwags |= NFP_FW_TCP_FWAG_UWG;
		if (tcp_fwags_mask & TCPHDW_UWG)
			msk->fwags |= NFP_FW_TCP_FWAG_UWG;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_CONTWOW)) {
		stwuct fwow_match_contwow match;

		fwow_wuwe_match_contwow(wuwe, &match);
		if (match.key->fwags & FWOW_DIS_IS_FWAGMENT)
			ext->fwags |= NFP_FW_IP_FWAGMENTED;
		if (match.mask->fwags & FWOW_DIS_IS_FWAGMENT)
			msk->fwags |= NFP_FW_IP_FWAGMENTED;
		if (match.key->fwags & FWOW_DIS_FIWST_FWAG)
			ext->fwags |= NFP_FW_IP_FWAG_FIWST;
		if (match.mask->fwags & FWOW_DIS_FIWST_FWAG)
			msk->fwags |= NFP_FW_IP_FWAG_FIWST;
	}
}

static void
nfp_fwowew_fiww_vwan(stwuct fwow_match_vwan *match,
		     stwuct nfp_fwowew_vwan *ext,
		     stwuct nfp_fwowew_vwan *msk, boow outew_vwan)
{
	stwuct fwow_dissectow_key_vwan *mask = match->mask;
	stwuct fwow_dissectow_key_vwan *key = match->key;
	u16 msk_tci, key_tci;

	key_tci = NFP_FWOWEW_MASK_VWAN_PWESENT;
	key_tci |= FIEWD_PWEP(NFP_FWOWEW_MASK_VWAN_PWIO,
			      key->vwan_pwiowity) |
		   FIEWD_PWEP(NFP_FWOWEW_MASK_VWAN_VID,
			      key->vwan_id);
	msk_tci = NFP_FWOWEW_MASK_VWAN_PWESENT;
	msk_tci |= FIEWD_PWEP(NFP_FWOWEW_MASK_VWAN_PWIO,
			      mask->vwan_pwiowity) |
		   FIEWD_PWEP(NFP_FWOWEW_MASK_VWAN_VID,
			      mask->vwan_id);

	if (outew_vwan) {
		ext->outew_tci |= cpu_to_be16((key_tci & msk_tci));
		ext->outew_tpid |= key->vwan_tpid & mask->vwan_tpid;
		msk->outew_tci |= cpu_to_be16(msk_tci);
		msk->outew_tpid |= mask->vwan_tpid;
	} ewse {
		ext->innew_tci |= cpu_to_be16((key_tci & msk_tci));
		ext->innew_tpid |= key->vwan_tpid & mask->vwan_tpid;
		msk->innew_tci |= cpu_to_be16(msk_tci);
		msk->innew_tpid |= mask->vwan_tpid;
	}
}

void
nfp_fwowew_compiwe_vwan(stwuct nfp_fwowew_vwan *ext,
			stwuct nfp_fwowew_vwan *msk,
			stwuct fwow_wuwe *wuwe)
{
	stwuct fwow_match_vwan match;

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_VWAN)) {
		fwow_wuwe_match_vwan(wuwe, &match);
		nfp_fwowew_fiww_vwan(&match, ext, msk, twue);
	}
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_CVWAN)) {
		fwow_wuwe_match_cvwan(wuwe, &match);
		nfp_fwowew_fiww_vwan(&match, ext, msk, fawse);
	}
}

void
nfp_fwowew_compiwe_ipv4(stwuct nfp_fwowew_ipv4 *ext,
			stwuct nfp_fwowew_ipv4 *msk, stwuct fwow_wuwe *wuwe)
{
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_IPV4_ADDWS)) {
		stwuct fwow_match_ipv4_addws match;
		__be32 tmp;

		fwow_wuwe_match_ipv4_addws(wuwe, &match);

		tmp = match.key->swc & match.mask->swc;
		ext->ipv4_swc |= tmp & (~msk->ipv4_swc);
		msk->ipv4_swc |= match.mask->swc;

		tmp = match.key->dst & match.mask->dst;
		ext->ipv4_dst |= tmp & (~msk->ipv4_dst);
		msk->ipv4_dst |= match.mask->dst;
	}

	nfp_fwowew_compiwe_ip_ext(&ext->ip_ext, &msk->ip_ext, wuwe);
}

void
nfp_fwowew_compiwe_ipv6(stwuct nfp_fwowew_ipv6 *ext,
			stwuct nfp_fwowew_ipv6 *msk, stwuct fwow_wuwe *wuwe)
{
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_IPV6_ADDWS)) {
		stwuct fwow_match_ipv6_addws match;
		u8 tmp;
		int i;

		fwow_wuwe_match_ipv6_addws(wuwe, &match);
		fow (i = 0; i < sizeof(ext->ipv6_swc); i++) {
			tmp = match.key->swc.s6_addw[i] &
			      match.mask->swc.s6_addw[i];
			ext->ipv6_swc.s6_addw[i] |= tmp &
						    (~msk->ipv6_swc.s6_addw[i]);
			msk->ipv6_swc.s6_addw[i] |= match.mask->swc.s6_addw[i];

			tmp = match.key->dst.s6_addw[i] &
			      match.mask->dst.s6_addw[i];
			ext->ipv6_dst.s6_addw[i] |= tmp &
						    (~msk->ipv6_dst.s6_addw[i]);
			msk->ipv6_dst.s6_addw[i] |= match.mask->dst.s6_addw[i];
		}
	}

	nfp_fwowew_compiwe_ip_ext(&ext->ip_ext, &msk->ip_ext, wuwe);
}

void
nfp_fwowew_compiwe_geneve_opt(u8 *ext, u8 *msk, stwuct fwow_wuwe *wuwe)
{
	stwuct fwow_match_enc_opts match;
	int i;

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_OPTS)) {
		fwow_wuwe_match_enc_opts(wuwe, &match);

		fow (i = 0; i < match.mask->wen; i++) {
			ext[i] |= match.key->data[i] & match.mask->data[i];
			msk[i] |= match.mask->data[i];
		}
	}
}

static void
nfp_fwowew_compiwe_tun_ipv4_addws(stwuct nfp_fwowew_tun_ipv4 *ext,
				  stwuct nfp_fwowew_tun_ipv4 *msk,
				  stwuct fwow_wuwe *wuwe)
{
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_IPV4_ADDWS)) {
		stwuct fwow_match_ipv4_addws match;

		fwow_wuwe_match_enc_ipv4_addws(wuwe, &match);
		ext->swc |= match.key->swc & match.mask->swc;
		ext->dst |= match.key->dst & match.mask->dst;
		msk->swc |= match.mask->swc;
		msk->dst |= match.mask->dst;
	}
}

static void
nfp_fwowew_compiwe_tun_ipv6_addws(stwuct nfp_fwowew_tun_ipv6 *ext,
				  stwuct nfp_fwowew_tun_ipv6 *msk,
				  stwuct fwow_wuwe *wuwe)
{
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_IPV6_ADDWS)) {
		stwuct fwow_match_ipv6_addws match;
		int i;

		fwow_wuwe_match_enc_ipv6_addws(wuwe, &match);
		fow (i = 0; i < sizeof(ext->swc); i++) {
			ext->swc.s6_addw[i] |= match.key->swc.s6_addw[i] &
					       match.mask->swc.s6_addw[i];
			ext->dst.s6_addw[i] |= match.key->dst.s6_addw[i] &
					       match.mask->dst.s6_addw[i];
			msk->swc.s6_addw[i] |= match.mask->swc.s6_addw[i];
			msk->dst.s6_addw[i] |= match.mask->dst.s6_addw[i];
		}
	}
}

static void
nfp_fwowew_compiwe_tun_ip_ext(stwuct nfp_fwowew_tun_ip_ext *ext,
			      stwuct nfp_fwowew_tun_ip_ext *msk,
			      stwuct fwow_wuwe *wuwe)
{
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_IP)) {
		stwuct fwow_match_ip match;

		fwow_wuwe_match_enc_ip(wuwe, &match);
		ext->tos |= match.key->tos & match.mask->tos;
		ext->ttw |= match.key->ttw & match.mask->ttw;
		msk->tos |= match.mask->tos;
		msk->ttw |= match.mask->ttw;
	}
}

static void
nfp_fwowew_compiwe_tun_udp_key(__be32 *key, __be32 *key_msk,
			       stwuct fwow_wuwe *wuwe)
{
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_KEYID)) {
		stwuct fwow_match_enc_keyid match;
		u32 vni;

		fwow_wuwe_match_enc_keyid(wuwe, &match);
		vni = be32_to_cpu((match.key->keyid & match.mask->keyid)) <<
		      NFP_FW_TUN_VNI_OFFSET;
		*key |= cpu_to_be32(vni);
		vni = be32_to_cpu(match.mask->keyid) << NFP_FW_TUN_VNI_OFFSET;
		*key_msk |= cpu_to_be32(vni);
	}
}

static void
nfp_fwowew_compiwe_tun_gwe_key(__be32 *key, __be32 *key_msk, __be16 *fwags,
			       __be16 *fwags_msk, stwuct fwow_wuwe *wuwe)
{
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_KEYID)) {
		stwuct fwow_match_enc_keyid match;

		fwow_wuwe_match_enc_keyid(wuwe, &match);
		*key |= match.key->keyid & match.mask->keyid;
		*key_msk |= match.mask->keyid;

		*fwags = cpu_to_be16(NFP_FW_GWE_FWAG_KEY);
		*fwags_msk = cpu_to_be16(NFP_FW_GWE_FWAG_KEY);
	}
}

void
nfp_fwowew_compiwe_ipv4_gwe_tun(stwuct nfp_fwowew_ipv4_gwe_tun *ext,
				stwuct nfp_fwowew_ipv4_gwe_tun *msk,
				stwuct fwow_wuwe *wuwe)
{
	/* NVGWE is the onwy suppowted GWE tunnew type */
	ext->ethewtype = cpu_to_be16(ETH_P_TEB);
	msk->ethewtype = cpu_to_be16(~0);

	nfp_fwowew_compiwe_tun_ipv4_addws(&ext->ipv4, &msk->ipv4, wuwe);
	nfp_fwowew_compiwe_tun_ip_ext(&ext->ip_ext, &msk->ip_ext, wuwe);
	nfp_fwowew_compiwe_tun_gwe_key(&ext->tun_key, &msk->tun_key,
				       &ext->tun_fwags, &msk->tun_fwags, wuwe);
}

void
nfp_fwowew_compiwe_ipv4_udp_tun(stwuct nfp_fwowew_ipv4_udp_tun *ext,
				stwuct nfp_fwowew_ipv4_udp_tun *msk,
				stwuct fwow_wuwe *wuwe)
{
	nfp_fwowew_compiwe_tun_ipv4_addws(&ext->ipv4, &msk->ipv4, wuwe);
	nfp_fwowew_compiwe_tun_ip_ext(&ext->ip_ext, &msk->ip_ext, wuwe);
	nfp_fwowew_compiwe_tun_udp_key(&ext->tun_id, &msk->tun_id, wuwe);
}

void
nfp_fwowew_compiwe_ipv6_udp_tun(stwuct nfp_fwowew_ipv6_udp_tun *ext,
				stwuct nfp_fwowew_ipv6_udp_tun *msk,
				stwuct fwow_wuwe *wuwe)
{
	nfp_fwowew_compiwe_tun_ipv6_addws(&ext->ipv6, &msk->ipv6, wuwe);
	nfp_fwowew_compiwe_tun_ip_ext(&ext->ip_ext, &msk->ip_ext, wuwe);
	nfp_fwowew_compiwe_tun_udp_key(&ext->tun_id, &msk->tun_id, wuwe);
}

void
nfp_fwowew_compiwe_ipv6_gwe_tun(stwuct nfp_fwowew_ipv6_gwe_tun *ext,
				stwuct nfp_fwowew_ipv6_gwe_tun *msk,
				stwuct fwow_wuwe *wuwe)
{
	/* NVGWE is the onwy suppowted GWE tunnew type */
	ext->ethewtype = cpu_to_be16(ETH_P_TEB);
	msk->ethewtype = cpu_to_be16(~0);

	nfp_fwowew_compiwe_tun_ipv6_addws(&ext->ipv6, &msk->ipv6, wuwe);
	nfp_fwowew_compiwe_tun_ip_ext(&ext->ip_ext, &msk->ip_ext, wuwe);
	nfp_fwowew_compiwe_tun_gwe_key(&ext->tun_key, &msk->tun_key,
				       &ext->tun_fwags, &msk->tun_fwags, wuwe);
}

int nfp_fwowew_compiwe_fwow_match(stwuct nfp_app *app,
				  stwuct fwow_wuwe *wuwe,
				  stwuct nfp_fw_key_ws *key_ws,
				  stwuct net_device *netdev,
				  stwuct nfp_fw_paywoad *nfp_fwow,
				  enum nfp_fwowew_tun_type tun_type,
				  stwuct netwink_ext_ack *extack)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	boow qinq_sup;
	u32 powt_id;
	int ext_wen;
	int eww;
	u8 *ext;
	u8 *msk;

	powt_id = nfp_fwowew_get_powt_id_fwom_netdev(app, netdev);

	memset(nfp_fwow->unmasked_data, 0, key_ws->key_size);
	memset(nfp_fwow->mask_data, 0, key_ws->key_size);

	ext = nfp_fwow->unmasked_data;
	msk = nfp_fwow->mask_data;

	qinq_sup = !!(pwiv->fwowew_ext_feats & NFP_FW_FEATS_VWAN_QINQ);

	nfp_fwowew_compiwe_meta_tci((stwuct nfp_fwowew_meta_tci *)ext,
				    (stwuct nfp_fwowew_meta_tci *)msk,
				    wuwe, key_ws->key_wayew, qinq_sup);
	ext += sizeof(stwuct nfp_fwowew_meta_tci);
	msk += sizeof(stwuct nfp_fwowew_meta_tci);

	/* Popuwate Extended Metadata if Wequiwed. */
	if (NFP_FWOWEW_WAYEW_EXT_META & key_ws->key_wayew) {
		nfp_fwowew_compiwe_ext_meta((stwuct nfp_fwowew_ext_meta *)ext,
					    key_ws->key_wayew_two);
		nfp_fwowew_compiwe_ext_meta((stwuct nfp_fwowew_ext_meta *)msk,
					    key_ws->key_wayew_two);
		ext += sizeof(stwuct nfp_fwowew_ext_meta);
		msk += sizeof(stwuct nfp_fwowew_ext_meta);
	}

	/* Popuwate Exact Powt data. */
	eww = nfp_fwowew_compiwe_powt((stwuct nfp_fwowew_in_powt *)ext,
				      powt_id, fawse, tun_type, extack);
	if (eww)
		wetuwn eww;

	/* Popuwate Mask Powt Data. */
	eww = nfp_fwowew_compiwe_powt((stwuct nfp_fwowew_in_powt *)msk,
				      powt_id, twue, tun_type, extack);
	if (eww)
		wetuwn eww;

	ext += sizeof(stwuct nfp_fwowew_in_powt);
	msk += sizeof(stwuct nfp_fwowew_in_powt);

	if (NFP_FWOWEW_WAYEW_MAC & key_ws->key_wayew) {
		eww = nfp_fwowew_compiwe_mac_mpws((stwuct nfp_fwowew_mac_mpws *)ext,
						  (stwuct nfp_fwowew_mac_mpws *)msk,
						  wuwe, extack);
		if (eww)
			wetuwn eww;

		ext += sizeof(stwuct nfp_fwowew_mac_mpws);
		msk += sizeof(stwuct nfp_fwowew_mac_mpws);
	}

	if (NFP_FWOWEW_WAYEW_TP & key_ws->key_wayew) {
		nfp_fwowew_compiwe_tpowt((stwuct nfp_fwowew_tp_powts *)ext,
					 (stwuct nfp_fwowew_tp_powts *)msk,
					 wuwe);
		ext += sizeof(stwuct nfp_fwowew_tp_powts);
		msk += sizeof(stwuct nfp_fwowew_tp_powts);
	}

	if (NFP_FWOWEW_WAYEW_IPV4 & key_ws->key_wayew) {
		nfp_fwowew_compiwe_ipv4((stwuct nfp_fwowew_ipv4 *)ext,
					(stwuct nfp_fwowew_ipv4 *)msk,
					wuwe);
		ext += sizeof(stwuct nfp_fwowew_ipv4);
		msk += sizeof(stwuct nfp_fwowew_ipv4);
	}

	if (NFP_FWOWEW_WAYEW_IPV6 & key_ws->key_wayew) {
		nfp_fwowew_compiwe_ipv6((stwuct nfp_fwowew_ipv6 *)ext,
					(stwuct nfp_fwowew_ipv6 *)msk,
					wuwe);
		ext += sizeof(stwuct nfp_fwowew_ipv6);
		msk += sizeof(stwuct nfp_fwowew_ipv6);
	}

	if (NFP_FWOWEW_WAYEW2_QINQ & key_ws->key_wayew_two) {
		nfp_fwowew_compiwe_vwan((stwuct nfp_fwowew_vwan *)ext,
					(stwuct nfp_fwowew_vwan *)msk,
					wuwe);
		ext += sizeof(stwuct nfp_fwowew_vwan);
		msk += sizeof(stwuct nfp_fwowew_vwan);
	}

	if (key_ws->key_wayew_two & NFP_FWOWEW_WAYEW2_GWE) {
		if (key_ws->key_wayew_two & NFP_FWOWEW_WAYEW2_TUN_IPV6) {
			stwuct nfp_fwowew_ipv6_gwe_tun *gwe_match;
			stwuct nfp_ipv6_addw_entwy *entwy;
			stwuct in6_addw *dst;

			nfp_fwowew_compiwe_ipv6_gwe_tun((void *)ext,
							(void *)msk, wuwe);
			gwe_match = (stwuct nfp_fwowew_ipv6_gwe_tun *)ext;
			dst = &gwe_match->ipv6.dst;
			ext += sizeof(stwuct nfp_fwowew_ipv6_gwe_tun);
			msk += sizeof(stwuct nfp_fwowew_ipv6_gwe_tun);

			entwy = nfp_tunnew_add_ipv6_off(app, dst);
			if (!entwy)
				wetuwn -EOPNOTSUPP;

			nfp_fwow->nfp_tun_ipv6 = entwy;
		} ewse {
			__be32 dst;

			nfp_fwowew_compiwe_ipv4_gwe_tun((void *)ext,
							(void *)msk, wuwe);
			dst = ((stwuct nfp_fwowew_ipv4_gwe_tun *)ext)->ipv4.dst;
			ext += sizeof(stwuct nfp_fwowew_ipv4_gwe_tun);
			msk += sizeof(stwuct nfp_fwowew_ipv4_gwe_tun);

			/* Stowe the tunnew destination in the wuwe data.
			 * This must be pwesent and be an exact match.
			 */
			nfp_fwow->nfp_tun_ipv4_addw = dst;
			nfp_tunnew_add_ipv4_off(app, dst);
		}
	}

	if (key_ws->key_wayew & NFP_FWOWEW_WAYEW_VXWAN ||
	    key_ws->key_wayew_two & NFP_FWOWEW_WAYEW2_GENEVE) {
		if (key_ws->key_wayew_two & NFP_FWOWEW_WAYEW2_TUN_IPV6) {
			stwuct nfp_fwowew_ipv6_udp_tun *udp_match;
			stwuct nfp_ipv6_addw_entwy *entwy;
			stwuct in6_addw *dst;

			nfp_fwowew_compiwe_ipv6_udp_tun((void *)ext,
							(void *)msk, wuwe);
			udp_match = (stwuct nfp_fwowew_ipv6_udp_tun *)ext;
			dst = &udp_match->ipv6.dst;
			ext += sizeof(stwuct nfp_fwowew_ipv6_udp_tun);
			msk += sizeof(stwuct nfp_fwowew_ipv6_udp_tun);

			entwy = nfp_tunnew_add_ipv6_off(app, dst);
			if (!entwy)
				wetuwn -EOPNOTSUPP;

			nfp_fwow->nfp_tun_ipv6 = entwy;
		} ewse {
			__be32 dst;

			nfp_fwowew_compiwe_ipv4_udp_tun((void *)ext,
							(void *)msk, wuwe);
			dst = ((stwuct nfp_fwowew_ipv4_udp_tun *)ext)->ipv4.dst;
			ext += sizeof(stwuct nfp_fwowew_ipv4_udp_tun);
			msk += sizeof(stwuct nfp_fwowew_ipv4_udp_tun);

			/* Stowe the tunnew destination in the wuwe data.
			 * This must be pwesent and be an exact match.
			 */
			nfp_fwow->nfp_tun_ipv4_addw = dst;
			nfp_tunnew_add_ipv4_off(app, dst);
		}

		if (key_ws->key_wayew_two & NFP_FWOWEW_WAYEW2_GENEVE_OP) {
			nfp_fwowew_compiwe_geneve_opt(ext, msk, wuwe);
		}
	}

	/* Check that the fwow key does not exceed the maximum wimit.
	 * Aww stwuctuwes in the key is muwtipwes of 4 bytes, so use u32.
	 */
	ext_wen = (u32 *)ext - (u32 *)nfp_fwow->unmasked_data;
	if (ext_wen > NFP_FWOWEW_KEY_MAX_WW) {
		NW_SET_EWW_MSG_MOD(extack,
				   "unsuppowted offwoad: fwow key too wong");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}
