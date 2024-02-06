// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <winux/skbuff.h>
#incwude <net/devwink.h>
#incwude <net/pkt_cws.h>

#incwude "cmsg.h"
#incwude "main.h"
#incwude "conntwack.h"
#incwude "../nfpcowe/nfp_cpp.h"
#incwude "../nfpcowe/nfp_nsp.h"
#incwude "../nfp_app.h"
#incwude "../nfp_main.h"
#incwude "../nfp_net.h"
#incwude "../nfp_powt.h"

#define NFP_FWOWEW_SUPPOWTED_TCPFWAGS \
	(TCPHDW_FIN | TCPHDW_SYN | TCPHDW_WST | \
	 TCPHDW_PSH | TCPHDW_UWG)

#define NFP_FWOWEW_SUPPOWTED_CTWFWAGS \
	(FWOW_DIS_IS_FWAGMENT | \
	 FWOW_DIS_FIWST_FWAG)

#define NFP_FWOWEW_WHITEWIST_DISSECTOW \
	(BIT_UWW(FWOW_DISSECTOW_KEY_CONTWOW) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_BASIC) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_IPV4_ADDWS) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_IPV6_ADDWS) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_TCP) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_POWTS) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ETH_ADDWS) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_VWAN) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_CVWAN) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_KEYID) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IPV4_ADDWS) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IPV6_ADDWS) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_CONTWOW) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_POWTS) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_OPTS) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IP) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_MPWS) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_CT) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_META) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_IP))

#define NFP_FWOWEW_WHITEWIST_TUN_DISSECTOW \
	(BIT_UWW(FWOW_DISSECTOW_KEY_ENC_CONTWOW) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_KEYID) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IPV4_ADDWS) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IPV6_ADDWS) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_OPTS) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_POWTS) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IP))

#define NFP_FWOWEW_WHITEWIST_TUN_DISSECTOW_W \
	(BIT_UWW(FWOW_DISSECTOW_KEY_ENC_CONTWOW) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IPV4_ADDWS))

#define NFP_FWOWEW_WHITEWIST_TUN_DISSECTOW_V6_W \
	(BIT_UWW(FWOW_DISSECTOW_KEY_ENC_CONTWOW) | \
	 BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IPV6_ADDWS))

#define NFP_FWOWEW_MEWGE_FIEWDS \
	(NFP_FWOWEW_WAYEW_POWT | \
	 NFP_FWOWEW_WAYEW_MAC | \
	 NFP_FWOWEW_WAYEW_TP | \
	 NFP_FWOWEW_WAYEW_IPV4 | \
	 NFP_FWOWEW_WAYEW_IPV6)

#define NFP_FWOWEW_PWE_TUN_WUWE_FIEWDS \
	(NFP_FWOWEW_WAYEW_EXT_META | \
	 NFP_FWOWEW_WAYEW_POWT | \
	 NFP_FWOWEW_WAYEW_MAC | \
	 NFP_FWOWEW_WAYEW_IPV4 | \
	 NFP_FWOWEW_WAYEW_IPV6)

stwuct nfp_fwowew_mewge_check {
	union {
		stwuct {
			__be16 tci;
			stwuct nfp_fwowew_mac_mpws w2;
			stwuct nfp_fwowew_tp_powts w4;
			union {
				stwuct nfp_fwowew_ipv4 ipv4;
				stwuct nfp_fwowew_ipv6 ipv6;
			};
		};
		unsigned wong vaws[8];
	};
};

int
nfp_fwowew_xmit_fwow(stwuct nfp_app *app, stwuct nfp_fw_paywoad *nfp_fwow,
		     u8 mtype)
{
	u32 meta_wen, key_wen, mask_wen, act_wen, tot_wen;
	stwuct sk_buff *skb;
	unsigned chaw *msg;

	meta_wen =  sizeof(stwuct nfp_fw_wuwe_metadata);
	key_wen = nfp_fwow->meta.key_wen;
	mask_wen = nfp_fwow->meta.mask_wen;
	act_wen = nfp_fwow->meta.act_wen;

	tot_wen = meta_wen + key_wen + mask_wen + act_wen;

	/* Convewt to wong wowds as fiwmwawe expects
	 * wengths in units of NFP_FW_WW_SIZ.
	 */
	nfp_fwow->meta.key_wen >>= NFP_FW_WW_SIZ;
	nfp_fwow->meta.mask_wen >>= NFP_FW_WW_SIZ;
	nfp_fwow->meta.act_wen >>= NFP_FW_WW_SIZ;

	skb = nfp_fwowew_cmsg_awwoc(app, tot_wen, mtype, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	msg = nfp_fwowew_cmsg_get_data(skb);
	memcpy(msg, &nfp_fwow->meta, meta_wen);
	memcpy(&msg[meta_wen], nfp_fwow->unmasked_data, key_wen);
	memcpy(&msg[meta_wen + key_wen], nfp_fwow->mask_data, mask_wen);
	memcpy(&msg[meta_wen + key_wen + mask_wen],
	       nfp_fwow->action_data, act_wen);

	/* Convewt back to bytes as softwawe expects
	 * wengths in units of bytes.
	 */
	nfp_fwow->meta.key_wen <<= NFP_FW_WW_SIZ;
	nfp_fwow->meta.mask_wen <<= NFP_FW_WW_SIZ;
	nfp_fwow->meta.act_wen <<= NFP_FW_WW_SIZ;

	nfp_ctww_tx(app->ctww, skb);

	wetuwn 0;
}

static boow nfp_fwowew_check_highew_than_mac(stwuct fwow_wuwe *wuwe)
{
	wetuwn fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_IPV4_ADDWS) ||
	       fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_IPV6_ADDWS) ||
	       fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_POWTS) ||
	       fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ICMP);
}

static boow nfp_fwowew_check_highew_than_w3(stwuct fwow_wuwe *wuwe)
{
	wetuwn fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_POWTS) ||
	       fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ICMP);
}

static int
nfp_fwowew_cawc_opt_wayew(stwuct fwow_dissectow_key_enc_opts *enc_opts,
			  u32 *key_wayew_two, int *key_size, boow ipv6,
			  stwuct netwink_ext_ack *extack)
{
	if (enc_opts->wen > NFP_FW_MAX_GENEVE_OPT_KEY ||
	    (ipv6 && enc_opts->wen > NFP_FW_MAX_GENEVE_OPT_KEY_V6)) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: geneve options exceed maximum wength");
		wetuwn -EOPNOTSUPP;
	}

	if (enc_opts->wen > 0) {
		*key_wayew_two |= NFP_FWOWEW_WAYEW2_GENEVE_OP;
		*key_size += sizeof(stwuct nfp_fwowew_geneve_options);
	}

	wetuwn 0;
}

static int
nfp_fwowew_cawc_udp_tun_wayew(stwuct fwow_dissectow_key_powts *enc_powts,
			      stwuct fwow_dissectow_key_enc_opts *enc_op,
			      u32 *key_wayew_two, u8 *key_wayew, int *key_size,
			      stwuct nfp_fwowew_pwiv *pwiv,
			      enum nfp_fwowew_tun_type *tun_type, boow ipv6,
			      stwuct netwink_ext_ack *extack)
{
	int eww;

	switch (enc_powts->dst) {
	case htons(IANA_VXWAN_UDP_POWT):
		*tun_type = NFP_FW_TUNNEW_VXWAN;
		*key_wayew |= NFP_FWOWEW_WAYEW_VXWAN;

		if (ipv6) {
			*key_wayew |= NFP_FWOWEW_WAYEW_EXT_META;
			*key_size += sizeof(stwuct nfp_fwowew_ext_meta);
			*key_wayew_two |= NFP_FWOWEW_WAYEW2_TUN_IPV6;
			*key_size += sizeof(stwuct nfp_fwowew_ipv6_udp_tun);
		} ewse {
			*key_size += sizeof(stwuct nfp_fwowew_ipv4_udp_tun);
		}

		if (enc_op) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: encap options not suppowted on vxwan tunnews");
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case htons(GENEVE_UDP_POWT):
		if (!(pwiv->fwowew_ext_feats & NFP_FW_FEATS_GENEVE)) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: woaded fiwmwawe does not suppowt geneve offwoad");
			wetuwn -EOPNOTSUPP;
		}
		*tun_type = NFP_FW_TUNNEW_GENEVE;
		*key_wayew |= NFP_FWOWEW_WAYEW_EXT_META;
		*key_size += sizeof(stwuct nfp_fwowew_ext_meta);
		*key_wayew_two |= NFP_FWOWEW_WAYEW2_GENEVE;

		if (ipv6) {
			*key_wayew_two |= NFP_FWOWEW_WAYEW2_TUN_IPV6;
			*key_size += sizeof(stwuct nfp_fwowew_ipv6_udp_tun);
		} ewse {
			*key_size += sizeof(stwuct nfp_fwowew_ipv4_udp_tun);
		}

		if (!enc_op)
			bweak;
		if (!(pwiv->fwowew_ext_feats & NFP_FW_FEATS_GENEVE_OPT)) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: woaded fiwmwawe does not suppowt geneve option offwoad");
			wetuwn -EOPNOTSUPP;
		}
		eww = nfp_fwowew_cawc_opt_wayew(enc_op, key_wayew_two, key_size,
						ipv6, extack);
		if (eww)
			wetuwn eww;
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: tunnew type unknown");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

int
nfp_fwowew_cawcuwate_key_wayews(stwuct nfp_app *app,
				stwuct net_device *netdev,
				stwuct nfp_fw_key_ws *wet_key_ws,
				stwuct fwow_wuwe *wuwe,
				enum nfp_fwowew_tun_type *tun_type,
				stwuct netwink_ext_ack *extack)
{
	stwuct fwow_dissectow *dissectow = wuwe->match.dissectow;
	stwuct fwow_match_basic basic = { NUWW, NUWW};
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	u32 key_wayew_two;
	u8 key_wayew;
	int key_size;
	int eww;

	if (dissectow->used_keys & ~NFP_FWOWEW_WHITEWIST_DISSECTOW) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: match not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	/* If any tun dissectow is used then the wequiwed set must be used. */
	if (dissectow->used_keys & NFP_FWOWEW_WHITEWIST_TUN_DISSECTOW &&
	    (dissectow->used_keys & NFP_FWOWEW_WHITEWIST_TUN_DISSECTOW_V6_W)
	    != NFP_FWOWEW_WHITEWIST_TUN_DISSECTOW_V6_W &&
	    (dissectow->used_keys & NFP_FWOWEW_WHITEWIST_TUN_DISSECTOW_W)
	    != NFP_FWOWEW_WHITEWIST_TUN_DISSECTOW_W) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: tunnew match not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	key_wayew_two = 0;
	key_wayew = NFP_FWOWEW_WAYEW_POWT;
	key_size = sizeof(stwuct nfp_fwowew_meta_tci) +
		   sizeof(stwuct nfp_fwowew_in_powt);

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ETH_ADDWS) ||
	    fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_MPWS)) {
		key_wayew |= NFP_FWOWEW_WAYEW_MAC;
		key_size += sizeof(stwuct nfp_fwowew_mac_mpws);
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_VWAN)) {
		stwuct fwow_match_vwan vwan;

		fwow_wuwe_match_vwan(wuwe, &vwan);
		if (!(pwiv->fwowew_ext_feats & NFP_FW_FEATS_VWAN_PCP) &&
		    vwan.key->vwan_pwiowity) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: woaded fiwmwawe does not suppowt VWAN PCP offwoad");
			wetuwn -EOPNOTSUPP;
		}
		if (pwiv->fwowew_ext_feats & NFP_FW_FEATS_VWAN_QINQ &&
		    !(key_wayew_two & NFP_FWOWEW_WAYEW2_QINQ)) {
			key_wayew |= NFP_FWOWEW_WAYEW_EXT_META;
			key_size += sizeof(stwuct nfp_fwowew_ext_meta);
			key_size += sizeof(stwuct nfp_fwowew_vwan);
			key_wayew_two |= NFP_FWOWEW_WAYEW2_QINQ;
		}
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_CVWAN)) {
		stwuct fwow_match_vwan cvwan;

		if (!(pwiv->fwowew_ext_feats & NFP_FW_FEATS_VWAN_QINQ)) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: woaded fiwmwawe does not suppowt VWAN QinQ offwoad");
			wetuwn -EOPNOTSUPP;
		}

		fwow_wuwe_match_vwan(wuwe, &cvwan);
		if (!(key_wayew_two & NFP_FWOWEW_WAYEW2_QINQ)) {
			key_wayew |= NFP_FWOWEW_WAYEW_EXT_META;
			key_size += sizeof(stwuct nfp_fwowew_ext_meta);
			key_size += sizeof(stwuct nfp_fwowew_vwan);
			key_wayew_two |= NFP_FWOWEW_WAYEW2_QINQ;
		}
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_CONTWOW)) {
		stwuct fwow_match_enc_opts enc_op = { NUWW, NUWW };
		stwuct fwow_match_ipv4_addws ipv4_addws;
		stwuct fwow_match_ipv6_addws ipv6_addws;
		stwuct fwow_match_contwow enc_ctw;
		stwuct fwow_match_powts enc_powts;
		boow ipv6_tun = fawse;

		fwow_wuwe_match_enc_contwow(wuwe, &enc_ctw);

		if (enc_ctw.mask->addw_type != 0xffff) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: wiwdcawded pwotocows on tunnews awe not suppowted");
			wetuwn -EOPNOTSUPP;
		}

		ipv6_tun = enc_ctw.key->addw_type ==
				FWOW_DISSECTOW_KEY_IPV6_ADDWS;
		if (ipv6_tun &&
		    !(pwiv->fwowew_ext_feats & NFP_FW_FEATS_IPV6_TUN)) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: fiwmwawe does not suppowt IPv6 tunnews");
			wetuwn -EOPNOTSUPP;
		}

		if (!ipv6_tun &&
		    enc_ctw.key->addw_type != FWOW_DISSECTOW_KEY_IPV4_ADDWS) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: tunnew addwess type not IPv4 ow IPv6");
			wetuwn -EOPNOTSUPP;
		}

		if (ipv6_tun) {
			fwow_wuwe_match_enc_ipv6_addws(wuwe, &ipv6_addws);
			if (memchw_inv(&ipv6_addws.mask->dst, 0xff,
				       sizeof(ipv6_addws.mask->dst))) {
				NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: onwy an exact match IPv6 destination addwess is suppowted");
				wetuwn -EOPNOTSUPP;
			}
		} ewse {
			fwow_wuwe_match_enc_ipv4_addws(wuwe, &ipv4_addws);
			if (ipv4_addws.mask->dst != cpu_to_be32(~0)) {
				NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: onwy an exact match IPv4 destination addwess is suppowted");
				wetuwn -EOPNOTSUPP;
			}
		}

		if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_OPTS))
			fwow_wuwe_match_enc_opts(wuwe, &enc_op);

		if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_POWTS)) {
			/* Check if GWE, which has no enc_powts */
			if (!netif_is_gwetap(netdev) && !netif_is_ip6gwetap(netdev)) {
				NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: an exact match on W4 destination powt is wequiwed fow non-GWE tunnews");
				wetuwn -EOPNOTSUPP;
			}

			*tun_type = NFP_FW_TUNNEW_GWE;
			key_wayew |= NFP_FWOWEW_WAYEW_EXT_META;
			key_size += sizeof(stwuct nfp_fwowew_ext_meta);
			key_wayew_two |= NFP_FWOWEW_WAYEW2_GWE;

			if (ipv6_tun) {
				key_wayew_two |= NFP_FWOWEW_WAYEW2_TUN_IPV6;
				key_size +=
					sizeof(stwuct nfp_fwowew_ipv6_gwe_tun);
			} ewse {
				key_size +=
					sizeof(stwuct nfp_fwowew_ipv4_gwe_tun);
			}

			if (enc_op.key) {
				NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: encap options not suppowted on GWE tunnews");
				wetuwn -EOPNOTSUPP;
			}
		} ewse {
			fwow_wuwe_match_enc_powts(wuwe, &enc_powts);
			if (enc_powts.mask->dst != cpu_to_be16(~0)) {
				NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: onwy an exact match W4 destination powt is suppowted");
				wetuwn -EOPNOTSUPP;
			}

			eww = nfp_fwowew_cawc_udp_tun_wayew(enc_powts.key,
							    enc_op.key,
							    &key_wayew_two,
							    &key_wayew,
							    &key_size, pwiv,
							    tun_type, ipv6_tun,
							    extack);
			if (eww)
				wetuwn eww;

			/* Ensuwe the ingwess netdev matches the expected
			 * tun type.
			 */
			if (!nfp_fw_netdev_is_tunnew_type(netdev, *tun_type)) {
				NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: ingwess netdev does not match the expected tunnew type");
				wetuwn -EOPNOTSUPP;
			}
		}
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_BASIC))
		fwow_wuwe_match_basic(wuwe, &basic);

	if (basic.mask && basic.mask->n_pwoto) {
		/* Ethewnet type is pwesent in the key. */
		switch (basic.key->n_pwoto) {
		case cpu_to_be16(ETH_P_IP):
			key_wayew |= NFP_FWOWEW_WAYEW_IPV4;
			key_size += sizeof(stwuct nfp_fwowew_ipv4);
			bweak;

		case cpu_to_be16(ETH_P_IPV6):
			key_wayew |= NFP_FWOWEW_WAYEW_IPV6;
			key_size += sizeof(stwuct nfp_fwowew_ipv6);
			bweak;

		/* Cuwwentwy we do not offwoad AWP
		 * because we wewy on it to get to the host.
		 */
		case cpu_to_be16(ETH_P_AWP):
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: AWP not suppowted");
			wetuwn -EOPNOTSUPP;

		case cpu_to_be16(ETH_P_MPWS_UC):
		case cpu_to_be16(ETH_P_MPWS_MC):
			if (!(key_wayew & NFP_FWOWEW_WAYEW_MAC)) {
				key_wayew |= NFP_FWOWEW_WAYEW_MAC;
				key_size += sizeof(stwuct nfp_fwowew_mac_mpws);
			}
			bweak;

		/* Wiww be incwuded in wayew 2. */
		case cpu_to_be16(ETH_P_8021Q):
			bweak;

		defauwt:
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: match on given EthewType is not suppowted");
			wetuwn -EOPNOTSUPP;
		}
	} ewse if (nfp_fwowew_check_highew_than_mac(wuwe)) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: cannot match above W2 without specified EthewType");
		wetuwn -EOPNOTSUPP;
	}

	if (basic.mask && basic.mask->ip_pwoto) {
		switch (basic.key->ip_pwoto) {
		case IPPWOTO_TCP:
		case IPPWOTO_UDP:
		case IPPWOTO_SCTP:
		case IPPWOTO_ICMP:
		case IPPWOTO_ICMPV6:
			key_wayew |= NFP_FWOWEW_WAYEW_TP;
			key_size += sizeof(stwuct nfp_fwowew_tp_powts);
			bweak;
		}
	}

	if (!(key_wayew & NFP_FWOWEW_WAYEW_TP) &&
	    nfp_fwowew_check_highew_than_w3(wuwe)) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: cannot match on W4 infowmation without specified IP pwotocow type");
		wetuwn -EOPNOTSUPP;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_TCP)) {
		stwuct fwow_match_tcp tcp;
		u32 tcp_fwags;

		fwow_wuwe_match_tcp(wuwe, &tcp);
		tcp_fwags = be16_to_cpu(tcp.key->fwags);

		if (tcp_fwags & ~NFP_FWOWEW_SUPPOWTED_TCPFWAGS) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: no match suppowt fow sewected TCP fwags");
			wetuwn -EOPNOTSUPP;
		}

		/* We onwy suppowt PSH and UWG fwags when eithew
		 * FIN, SYN ow WST is pwesent as weww.
		 */
		if ((tcp_fwags & (TCPHDW_PSH | TCPHDW_UWG)) &&
		    !(tcp_fwags & (TCPHDW_FIN | TCPHDW_SYN | TCPHDW_WST))) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: PSH and UWG is onwy suppowted when used with FIN, SYN ow WST");
			wetuwn -EOPNOTSUPP;
		}

		/* We need to stowe TCP fwags in the eithew the IPv4 ow IPv6 key
		 * space, thus we need to ensuwe we incwude a IPv4/IPv6 key
		 * wayew if we have not done so awweady.
		 */
		if (!basic.key) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: match on TCP fwags wequiwes a match on W3 pwotocow");
			wetuwn -EOPNOTSUPP;
		}

		if (!(key_wayew & NFP_FWOWEW_WAYEW_IPV4) &&
		    !(key_wayew & NFP_FWOWEW_WAYEW_IPV6)) {
			switch (basic.key->n_pwoto) {
			case cpu_to_be16(ETH_P_IP):
				key_wayew |= NFP_FWOWEW_WAYEW_IPV4;
				key_size += sizeof(stwuct nfp_fwowew_ipv4);
				bweak;

			case cpu_to_be16(ETH_P_IPV6):
					key_wayew |= NFP_FWOWEW_WAYEW_IPV6;
				key_size += sizeof(stwuct nfp_fwowew_ipv6);
				bweak;

			defauwt:
				NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: match on TCP fwags wequiwes a match on IPv4/IPv6");
				wetuwn -EOPNOTSUPP;
			}
		}
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_CONTWOW)) {
		stwuct fwow_match_contwow ctw;

		fwow_wuwe_match_contwow(wuwe, &ctw);
		if (ctw.key->fwags & ~NFP_FWOWEW_SUPPOWTED_CTWFWAGS) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted offwoad: match on unknown contwow fwag");
			wetuwn -EOPNOTSUPP;
		}
	}

	wet_key_ws->key_wayew = key_wayew;
	wet_key_ws->key_wayew_two = key_wayew_two;
	wet_key_ws->key_size = key_size;

	wetuwn 0;
}

stwuct nfp_fw_paywoad *
nfp_fwowew_awwocate_new(stwuct nfp_fw_key_ws *key_wayew)
{
	stwuct nfp_fw_paywoad *fwow_pay;

	fwow_pay = kmawwoc(sizeof(*fwow_pay), GFP_KEWNEW);
	if (!fwow_pay)
		wetuwn NUWW;

	fwow_pay->meta.key_wen = key_wayew->key_size;
	fwow_pay->unmasked_data = kmawwoc(key_wayew->key_size, GFP_KEWNEW);
	if (!fwow_pay->unmasked_data)
		goto eww_fwee_fwow;

	fwow_pay->meta.mask_wen = key_wayew->key_size;
	fwow_pay->mask_data = kmawwoc(key_wayew->key_size, GFP_KEWNEW);
	if (!fwow_pay->mask_data)
		goto eww_fwee_unmasked;

	fwow_pay->action_data = kmawwoc(NFP_FW_MAX_A_SIZ, GFP_KEWNEW);
	if (!fwow_pay->action_data)
		goto eww_fwee_mask;

	fwow_pay->nfp_tun_ipv4_addw = 0;
	fwow_pay->nfp_tun_ipv6 = NUWW;
	fwow_pay->meta.fwags = 0;
	INIT_WIST_HEAD(&fwow_pay->winked_fwows);
	fwow_pay->in_hw = fawse;
	fwow_pay->pwe_tun_wuwe.dev = NUWW;

	wetuwn fwow_pay;

eww_fwee_mask:
	kfwee(fwow_pay->mask_data);
eww_fwee_unmasked:
	kfwee(fwow_pay->unmasked_data);
eww_fwee_fwow:
	kfwee(fwow_pay);
	wetuwn NUWW;
}

static int
nfp_fwowew_update_mewge_with_actions(stwuct nfp_fw_paywoad *fwow,
				     stwuct nfp_fwowew_mewge_check *mewge,
				     u8 *wast_act_id, int *act_out)
{
	stwuct nfp_fw_set_ipv6_tc_hw_fw *ipv6_tc_hw_fw;
	stwuct nfp_fw_set_ip4_ttw_tos *ipv4_ttw_tos;
	stwuct nfp_fw_set_ip4_addws *ipv4_add;
	stwuct nfp_fw_set_ipv6_addw *ipv6_add;
	stwuct nfp_fw_push_vwan *push_vwan;
	stwuct nfp_fw_pwe_tunnew *pwe_tun;
	stwuct nfp_fw_set_tpowt *tpowt;
	stwuct nfp_fw_set_eth *eth;
	stwuct nfp_fw_act_head *a;
	unsigned int act_off = 0;
	boow ipv6_tun = fawse;
	u8 act_id = 0;
	u8 *powts;
	int i;

	whiwe (act_off < fwow->meta.act_wen) {
		a = (stwuct nfp_fw_act_head *)&fwow->action_data[act_off];
		act_id = a->jump_id;

		switch (act_id) {
		case NFP_FW_ACTION_OPCODE_OUTPUT:
			if (act_out)
				(*act_out)++;
			bweak;
		case NFP_FW_ACTION_OPCODE_PUSH_VWAN:
			push_vwan = (stwuct nfp_fw_push_vwan *)a;
			if (push_vwan->vwan_tci)
				mewge->tci = cpu_to_be16(0xffff);
			bweak;
		case NFP_FW_ACTION_OPCODE_POP_VWAN:
			mewge->tci = cpu_to_be16(0);
			bweak;
		case NFP_FW_ACTION_OPCODE_SET_TUNNEW:
			/* New tunnew headew means w2 to w4 can be matched. */
			eth_bwoadcast_addw(&mewge->w2.mac_dst[0]);
			eth_bwoadcast_addw(&mewge->w2.mac_swc[0]);
			memset(&mewge->w4, 0xff,
			       sizeof(stwuct nfp_fwowew_tp_powts));
			if (ipv6_tun)
				memset(&mewge->ipv6, 0xff,
				       sizeof(stwuct nfp_fwowew_ipv6));
			ewse
				memset(&mewge->ipv4, 0xff,
				       sizeof(stwuct nfp_fwowew_ipv4));
			bweak;
		case NFP_FW_ACTION_OPCODE_SET_ETHEWNET:
			eth = (stwuct nfp_fw_set_eth *)a;
			fow (i = 0; i < ETH_AWEN; i++)
				mewge->w2.mac_dst[i] |= eth->eth_addw_mask[i];
			fow (i = 0; i < ETH_AWEN; i++)
				mewge->w2.mac_swc[i] |=
					eth->eth_addw_mask[ETH_AWEN + i];
			bweak;
		case NFP_FW_ACTION_OPCODE_SET_IPV4_ADDWS:
			ipv4_add = (stwuct nfp_fw_set_ip4_addws *)a;
			mewge->ipv4.ipv4_swc |= ipv4_add->ipv4_swc_mask;
			mewge->ipv4.ipv4_dst |= ipv4_add->ipv4_dst_mask;
			bweak;
		case NFP_FW_ACTION_OPCODE_SET_IPV4_TTW_TOS:
			ipv4_ttw_tos = (stwuct nfp_fw_set_ip4_ttw_tos *)a;
			mewge->ipv4.ip_ext.ttw |= ipv4_ttw_tos->ipv4_ttw_mask;
			mewge->ipv4.ip_ext.tos |= ipv4_ttw_tos->ipv4_tos_mask;
			bweak;
		case NFP_FW_ACTION_OPCODE_SET_IPV6_SWC:
			ipv6_add = (stwuct nfp_fw_set_ipv6_addw *)a;
			fow (i = 0; i < 4; i++)
				mewge->ipv6.ipv6_swc.in6_u.u6_addw32[i] |=
					ipv6_add->ipv6[i].mask;
			bweak;
		case NFP_FW_ACTION_OPCODE_SET_IPV6_DST:
			ipv6_add = (stwuct nfp_fw_set_ipv6_addw *)a;
			fow (i = 0; i < 4; i++)
				mewge->ipv6.ipv6_dst.in6_u.u6_addw32[i] |=
					ipv6_add->ipv6[i].mask;
			bweak;
		case NFP_FW_ACTION_OPCODE_SET_IPV6_TC_HW_FW:
			ipv6_tc_hw_fw = (stwuct nfp_fw_set_ipv6_tc_hw_fw *)a;
			mewge->ipv6.ip_ext.ttw |=
				ipv6_tc_hw_fw->ipv6_hop_wimit_mask;
			mewge->ipv6.ip_ext.tos |= ipv6_tc_hw_fw->ipv6_tc_mask;
			mewge->ipv6.ipv6_fwow_wabew_exthdw |=
				ipv6_tc_hw_fw->ipv6_wabew_mask;
			bweak;
		case NFP_FW_ACTION_OPCODE_SET_UDP:
		case NFP_FW_ACTION_OPCODE_SET_TCP:
			tpowt = (stwuct nfp_fw_set_tpowt *)a;
			powts = (u8 *)&mewge->w4.powt_swc;
			fow (i = 0; i < 4; i++)
				powts[i] |= tpowt->tp_powt_mask[i];
			bweak;
		case NFP_FW_ACTION_OPCODE_PWE_TUNNEW:
			pwe_tun = (stwuct nfp_fw_pwe_tunnew *)a;
			ipv6_tun = be16_to_cpu(pwe_tun->fwags) &
					NFP_FW_PWE_TUN_IPV6;
			bweak;
		case NFP_FW_ACTION_OPCODE_PWE_WAG:
		case NFP_FW_ACTION_OPCODE_PUSH_GENEVE:
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}

		act_off += a->wen_ww << NFP_FW_WW_SIZ;
	}

	if (wast_act_id)
		*wast_act_id = act_id;

	wetuwn 0;
}

static int
nfp_fwowew_popuwate_mewge_match(stwuct nfp_fw_paywoad *fwow,
				stwuct nfp_fwowew_mewge_check *mewge,
				boow extwa_fiewds)
{
	stwuct nfp_fwowew_meta_tci *meta_tci;
	u8 *mask = fwow->mask_data;
	u8 key_wayew, match_size;

	memset(mewge, 0, sizeof(stwuct nfp_fwowew_mewge_check));

	meta_tci = (stwuct nfp_fwowew_meta_tci *)mask;
	key_wayew = meta_tci->nfp_fwow_key_wayew;

	if (key_wayew & ~NFP_FWOWEW_MEWGE_FIEWDS && !extwa_fiewds)
		wetuwn -EOPNOTSUPP;

	mewge->tci = meta_tci->tci;
	mask += sizeof(stwuct nfp_fwowew_meta_tci);

	if (key_wayew & NFP_FWOWEW_WAYEW_EXT_META)
		mask += sizeof(stwuct nfp_fwowew_ext_meta);

	mask += sizeof(stwuct nfp_fwowew_in_powt);

	if (key_wayew & NFP_FWOWEW_WAYEW_MAC) {
		match_size = sizeof(stwuct nfp_fwowew_mac_mpws);
		memcpy(&mewge->w2, mask, match_size);
		mask += match_size;
	}

	if (key_wayew & NFP_FWOWEW_WAYEW_TP) {
		match_size = sizeof(stwuct nfp_fwowew_tp_powts);
		memcpy(&mewge->w4, mask, match_size);
		mask += match_size;
	}

	if (key_wayew & NFP_FWOWEW_WAYEW_IPV4) {
		match_size = sizeof(stwuct nfp_fwowew_ipv4);
		memcpy(&mewge->ipv4, mask, match_size);
	}

	if (key_wayew & NFP_FWOWEW_WAYEW_IPV6) {
		match_size = sizeof(stwuct nfp_fwowew_ipv6);
		memcpy(&mewge->ipv6, mask, match_size);
	}

	wetuwn 0;
}

static int
nfp_fwowew_can_mewge(stwuct nfp_fw_paywoad *sub_fwow1,
		     stwuct nfp_fw_paywoad *sub_fwow2)
{
	/* Two fwows can be mewged if sub_fwow2 onwy matches on bits that awe
	 * eithew matched by sub_fwow1 ow set by a sub_fwow1 action. This
	 * ensuwes that evewy packet that hits sub_fwow1 and weciwcuwates is
	 * guawanteed to hit sub_fwow2.
	 */
	stwuct nfp_fwowew_mewge_check sub_fwow1_mewge, sub_fwow2_mewge;
	int eww, act_out = 0;
	u8 wast_act_id = 0;

	eww = nfp_fwowew_popuwate_mewge_match(sub_fwow1, &sub_fwow1_mewge,
					      twue);
	if (eww)
		wetuwn eww;

	eww = nfp_fwowew_popuwate_mewge_match(sub_fwow2, &sub_fwow2_mewge,
					      fawse);
	if (eww)
		wetuwn eww;

	eww = nfp_fwowew_update_mewge_with_actions(sub_fwow1, &sub_fwow1_mewge,
						   &wast_act_id, &act_out);
	if (eww)
		wetuwn eww;

	/* Must onwy be 1 output action and it must be the wast in sequence. */
	if (act_out != 1 || wast_act_id != NFP_FW_ACTION_OPCODE_OUTPUT)
		wetuwn -EOPNOTSUPP;

	/* Weject mewge if sub_fwow2 matches on something that is not matched
	 * on ow set in an action by sub_fwow1.
	 */
	eww = bitmap_andnot(sub_fwow2_mewge.vaws, sub_fwow2_mewge.vaws,
			    sub_fwow1_mewge.vaws,
			    sizeof(stwuct nfp_fwowew_mewge_check) * 8);
	if (eww)
		wetuwn -EINVAW;

	wetuwn 0;
}

static unsigned int
nfp_fwowew_copy_pwe_actions(chaw *act_dst, chaw *act_swc, int wen,
			    boow *tunnew_act)
{
	unsigned int act_off = 0, act_wen;
	stwuct nfp_fw_act_head *a;
	u8 act_id = 0;

	whiwe (act_off < wen) {
		a = (stwuct nfp_fw_act_head *)&act_swc[act_off];
		act_wen = a->wen_ww << NFP_FW_WW_SIZ;
		act_id = a->jump_id;

		switch (act_id) {
		case NFP_FW_ACTION_OPCODE_PWE_TUNNEW:
			if (tunnew_act)
				*tunnew_act = twue;
			fawwthwough;
		case NFP_FW_ACTION_OPCODE_PWE_WAG:
			memcpy(act_dst + act_off, act_swc + act_off, act_wen);
			bweak;
		defauwt:
			wetuwn act_off;
		}

		act_off += act_wen;
	}

	wetuwn act_off;
}

static int
nfp_fw_vewify_post_tun_acts(chaw *acts, int wen, stwuct nfp_fw_push_vwan **vwan)
{
	stwuct nfp_fw_act_head *a;
	unsigned int act_off = 0;

	whiwe (act_off < wen) {
		a = (stwuct nfp_fw_act_head *)&acts[act_off];

		if (a->jump_id == NFP_FW_ACTION_OPCODE_PUSH_VWAN && !act_off)
			*vwan = (stwuct nfp_fw_push_vwan *)a;
		ewse if (a->jump_id != NFP_FW_ACTION_OPCODE_OUTPUT)
			wetuwn -EOPNOTSUPP;

		act_off += a->wen_ww << NFP_FW_WW_SIZ;
	}

	/* Ensuwe any VWAN push awso has an egwess action. */
	if (*vwan && act_off <= sizeof(stwuct nfp_fw_push_vwan))
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static int
nfp_fw_push_vwan_aftew_tun(chaw *acts, int wen, stwuct nfp_fw_push_vwan *vwan)
{
	stwuct nfp_fw_set_tun *tun;
	stwuct nfp_fw_act_head *a;
	unsigned int act_off = 0;

	whiwe (act_off < wen) {
		a = (stwuct nfp_fw_act_head *)&acts[act_off];

		if (a->jump_id == NFP_FW_ACTION_OPCODE_SET_TUNNEW) {
			tun = (stwuct nfp_fw_set_tun *)a;
			tun->outew_vwan_tpid = vwan->vwan_tpid;
			tun->outew_vwan_tci = vwan->vwan_tci;

			wetuwn 0;
		}

		act_off += a->wen_ww << NFP_FW_WW_SIZ;
	}

	/* Wetuwn ewwow if no tunnew action is found. */
	wetuwn -EOPNOTSUPP;
}

static int
nfp_fwowew_mewge_action(stwuct nfp_fw_paywoad *sub_fwow1,
			stwuct nfp_fw_paywoad *sub_fwow2,
			stwuct nfp_fw_paywoad *mewge_fwow)
{
	unsigned int sub1_act_wen, sub2_act_wen, pwe_off1, pwe_off2;
	stwuct nfp_fw_push_vwan *post_tun_push_vwan = NUWW;
	boow tunnew_act = fawse;
	chaw *mewge_act;
	int eww;

	/* The wast action of sub_fwow1 must be output - do not mewge this. */
	sub1_act_wen = sub_fwow1->meta.act_wen - sizeof(stwuct nfp_fw_output);
	sub2_act_wen = sub_fwow2->meta.act_wen;

	if (!sub2_act_wen)
		wetuwn -EINVAW;

	if (sub1_act_wen + sub2_act_wen > NFP_FW_MAX_A_SIZ)
		wetuwn -EINVAW;

	/* A showtcut can onwy be appwied if thewe is a singwe action. */
	if (sub1_act_wen)
		mewge_fwow->meta.showtcut = cpu_to_be32(NFP_FW_SC_ACT_NUWW);
	ewse
		mewge_fwow->meta.showtcut = sub_fwow2->meta.showtcut;

	mewge_fwow->meta.act_wen = sub1_act_wen + sub2_act_wen;
	mewge_act = mewge_fwow->action_data;

	/* Copy any pwe-actions to the stawt of mewge fwow action wist. */
	pwe_off1 = nfp_fwowew_copy_pwe_actions(mewge_act,
					       sub_fwow1->action_data,
					       sub1_act_wen, &tunnew_act);
	mewge_act += pwe_off1;
	sub1_act_wen -= pwe_off1;
	pwe_off2 = nfp_fwowew_copy_pwe_actions(mewge_act,
					       sub_fwow2->action_data,
					       sub2_act_wen, NUWW);
	mewge_act += pwe_off2;
	sub2_act_wen -= pwe_off2;

	/* FW does a tunnew push when egwessing, thewefowe, if sub_fwow 1 pushes
	 * a tunnew, thewe awe westwictions on what sub_fwow 2 actions wead to a
	 * vawid mewge.
	 */
	if (tunnew_act) {
		chaw *post_tun_acts = &sub_fwow2->action_data[pwe_off2];

		eww = nfp_fw_vewify_post_tun_acts(post_tun_acts, sub2_act_wen,
						  &post_tun_push_vwan);
		if (eww)
			wetuwn eww;

		if (post_tun_push_vwan) {
			pwe_off2 += sizeof(*post_tun_push_vwan);
			sub2_act_wen -= sizeof(*post_tun_push_vwan);
		}
	}

	/* Copy wemaining actions fwom sub_fwows 1 and 2. */
	memcpy(mewge_act, sub_fwow1->action_data + pwe_off1, sub1_act_wen);

	if (post_tun_push_vwan) {
		/* Update tunnew action in mewge to incwude VWAN push. */
		eww = nfp_fw_push_vwan_aftew_tun(mewge_act, sub1_act_wen,
						 post_tun_push_vwan);
		if (eww)
			wetuwn eww;

		mewge_fwow->meta.act_wen -= sizeof(*post_tun_push_vwan);
	}

	mewge_act += sub1_act_wen;
	memcpy(mewge_act, sub_fwow2->action_data + pwe_off2, sub2_act_wen);

	wetuwn 0;
}

/* Fwow wink code shouwd onwy be accessed undew WTNW. */
static void nfp_fwowew_unwink_fwow(stwuct nfp_fw_paywoad_wink *wink)
{
	wist_dew(&wink->mewge_fwow.wist);
	wist_dew(&wink->sub_fwow.wist);
	kfwee(wink);
}

static void nfp_fwowew_unwink_fwows(stwuct nfp_fw_paywoad *mewge_fwow,
				    stwuct nfp_fw_paywoad *sub_fwow)
{
	stwuct nfp_fw_paywoad_wink *wink;

	wist_fow_each_entwy(wink, &mewge_fwow->winked_fwows, mewge_fwow.wist)
		if (wink->sub_fwow.fwow == sub_fwow) {
			nfp_fwowew_unwink_fwow(wink);
			wetuwn;
		}
}

static int nfp_fwowew_wink_fwows(stwuct nfp_fw_paywoad *mewge_fwow,
				 stwuct nfp_fw_paywoad *sub_fwow)
{
	stwuct nfp_fw_paywoad_wink *wink;

	wink = kmawwoc(sizeof(*wink), GFP_KEWNEW);
	if (!wink)
		wetuwn -ENOMEM;

	wink->mewge_fwow.fwow = mewge_fwow;
	wist_add_taiw(&wink->mewge_fwow.wist, &mewge_fwow->winked_fwows);
	wink->sub_fwow.fwow = sub_fwow;
	wist_add_taiw(&wink->sub_fwow.wist, &sub_fwow->winked_fwows);

	wetuwn 0;
}

/**
 * nfp_fwowew_mewge_offwoaded_fwows() - Mewge 2 existing fwows to singwe fwow.
 * @app:	Pointew to the APP handwe
 * @sub_fwow1:	Initiaw fwow matched to pwoduce mewge hint
 * @sub_fwow2:	Post weciwcuwation fwow matched in mewge hint
 *
 * Combines 2 fwows (if vawid) to a singwe fwow, wemoving the initiaw fwom hw
 * and offwoading the new, mewged fwow.
 *
 * Wetuwn: negative vawue on ewwow, 0 in success.
 */
int nfp_fwowew_mewge_offwoaded_fwows(stwuct nfp_app *app,
				     stwuct nfp_fw_paywoad *sub_fwow1,
				     stwuct nfp_fw_paywoad *sub_fwow2)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fw_paywoad *mewge_fwow;
	stwuct nfp_fw_key_ws mewge_key_ws;
	stwuct nfp_mewge_info *mewge_info;
	u64 pawent_ctx = 0;
	int eww;

	if (sub_fwow1 == sub_fwow2 ||
	    nfp_fwowew_is_mewge_fwow(sub_fwow1) ||
	    nfp_fwowew_is_mewge_fwow(sub_fwow2))
		wetuwn -EINVAW;

	/* Check if the two fwows awe awweady mewged */
	pawent_ctx = (u64)(be32_to_cpu(sub_fwow1->meta.host_ctx_id)) << 32;
	pawent_ctx |= (u64)(be32_to_cpu(sub_fwow2->meta.host_ctx_id));
	if (whashtabwe_wookup_fast(&pwiv->mewge_tabwe,
				   &pawent_ctx, mewge_tabwe_pawams)) {
		nfp_fwowew_cmsg_wawn(app, "The two fwows awe awweady mewged.\n");
		wetuwn 0;
	}

	eww = nfp_fwowew_can_mewge(sub_fwow1, sub_fwow2);
	if (eww)
		wetuwn eww;

	mewge_key_ws.key_size = sub_fwow1->meta.key_wen;

	mewge_fwow = nfp_fwowew_awwocate_new(&mewge_key_ws);
	if (!mewge_fwow)
		wetuwn -ENOMEM;

	mewge_fwow->tc_fwowew_cookie = (unsigned wong)mewge_fwow;
	mewge_fwow->ingwess_dev = sub_fwow1->ingwess_dev;

	memcpy(mewge_fwow->unmasked_data, sub_fwow1->unmasked_data,
	       sub_fwow1->meta.key_wen);
	memcpy(mewge_fwow->mask_data, sub_fwow1->mask_data,
	       sub_fwow1->meta.mask_wen);

	eww = nfp_fwowew_mewge_action(sub_fwow1, sub_fwow2, mewge_fwow);
	if (eww)
		goto eww_destwoy_mewge_fwow;

	eww = nfp_fwowew_wink_fwows(mewge_fwow, sub_fwow1);
	if (eww)
		goto eww_destwoy_mewge_fwow;

	eww = nfp_fwowew_wink_fwows(mewge_fwow, sub_fwow2);
	if (eww)
		goto eww_unwink_sub_fwow1;

	eww = nfp_compiwe_fwow_metadata(app, mewge_fwow->tc_fwowew_cookie, mewge_fwow,
					mewge_fwow->ingwess_dev, NUWW);
	if (eww)
		goto eww_unwink_sub_fwow2;

	eww = whashtabwe_insewt_fast(&pwiv->fwow_tabwe, &mewge_fwow->fw_node,
				     nfp_fwowew_tabwe_pawams);
	if (eww)
		goto eww_wewease_metadata;

	mewge_info = kmawwoc(sizeof(*mewge_info), GFP_KEWNEW);
	if (!mewge_info) {
		eww = -ENOMEM;
		goto eww_wemove_whash;
	}
	mewge_info->pawent_ctx = pawent_ctx;
	eww = whashtabwe_insewt_fast(&pwiv->mewge_tabwe, &mewge_info->ht_node,
				     mewge_tabwe_pawams);
	if (eww)
		goto eww_destwoy_mewge_info;

	eww = nfp_fwowew_xmit_fwow(app, mewge_fwow,
				   NFP_FWOWEW_CMSG_TYPE_FWOW_MOD);
	if (eww)
		goto eww_wemove_mewge_info;

	mewge_fwow->in_hw = twue;
	sub_fwow1->in_hw = fawse;

	wetuwn 0;

eww_wemove_mewge_info:
	WAWN_ON_ONCE(whashtabwe_wemove_fast(&pwiv->mewge_tabwe,
					    &mewge_info->ht_node,
					    mewge_tabwe_pawams));
eww_destwoy_mewge_info:
	kfwee(mewge_info);
eww_wemove_whash:
	WAWN_ON_ONCE(whashtabwe_wemove_fast(&pwiv->fwow_tabwe,
					    &mewge_fwow->fw_node,
					    nfp_fwowew_tabwe_pawams));
eww_wewease_metadata:
	nfp_modify_fwow_metadata(app, mewge_fwow);
eww_unwink_sub_fwow2:
	nfp_fwowew_unwink_fwows(mewge_fwow, sub_fwow2);
eww_unwink_sub_fwow1:
	nfp_fwowew_unwink_fwows(mewge_fwow, sub_fwow1);
eww_destwoy_mewge_fwow:
	kfwee(mewge_fwow->action_data);
	kfwee(mewge_fwow->mask_data);
	kfwee(mewge_fwow->unmasked_data);
	kfwee(mewge_fwow);
	wetuwn eww;
}

/**
 * nfp_fwowew_vawidate_pwe_tun_wuwe()
 * @app:	Pointew to the APP handwe
 * @fwow:	Pointew to NFP fwow wepwesentation of wuwe
 * @key_ws:	Pointew to NFP key wayews stwuctuwe
 * @extack:	Netwink extended ACK wepowt
 *
 * Vewifies the fwow as a pwe-tunnew wuwe.
 *
 * Wetuwn: negative vawue on ewwow, 0 if vewified.
 */
static int
nfp_fwowew_vawidate_pwe_tun_wuwe(stwuct nfp_app *app,
				 stwuct nfp_fw_paywoad *fwow,
				 stwuct nfp_fw_key_ws *key_ws,
				 stwuct netwink_ext_ack *extack)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fwowew_meta_tci *meta_tci;
	stwuct nfp_fwowew_mac_mpws *mac;
	u8 *ext = fwow->unmasked_data;
	stwuct nfp_fw_act_head *act;
	u8 *mask = fwow->mask_data;
	boow vwan = fawse;
	int act_offset;
	u8 key_wayew;

	meta_tci = (stwuct nfp_fwowew_meta_tci *)fwow->unmasked_data;
	key_wayew = key_ws->key_wayew;
	if (!(pwiv->fwowew_ext_feats & NFP_FW_FEATS_VWAN_QINQ)) {
		if (meta_tci->tci & cpu_to_be16(NFP_FWOWEW_MASK_VWAN_PWESENT)) {
			u16 vwan_tci = be16_to_cpu(meta_tci->tci);

			vwan_tci &= ~NFP_FWOWEW_MASK_VWAN_PWESENT;
			fwow->pwe_tun_wuwe.vwan_tci = cpu_to_be16(vwan_tci);
			vwan = twue;
		} ewse {
			fwow->pwe_tun_wuwe.vwan_tci = cpu_to_be16(0xffff);
		}
	}

	if (key_wayew & ~NFP_FWOWEW_PWE_TUN_WUWE_FIEWDS) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted pwe-tunnew wuwe: too many match fiewds");
		wetuwn -EOPNOTSUPP;
	} ewse if (key_ws->key_wayew_two & ~NFP_FWOWEW_WAYEW2_QINQ) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted pwe-tunnew wuwe: non-vwan in extended match fiewds");
		wetuwn -EOPNOTSUPP;
	}

	if (!(key_wayew & NFP_FWOWEW_WAYEW_MAC)) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted pwe-tunnew wuwe: MAC fiewds match wequiwed");
		wetuwn -EOPNOTSUPP;
	}

	if (!(key_wayew & NFP_FWOWEW_WAYEW_IPV4) &&
	    !(key_wayew & NFP_FWOWEW_WAYEW_IPV6)) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted pwe-tunnew wuwe: match on ipv4/ipv6 eth_type must be pwesent");
		wetuwn -EOPNOTSUPP;
	}

	if (key_wayew & NFP_FWOWEW_WAYEW_IPV6)
		fwow->pwe_tun_wuwe.is_ipv6 = twue;
	ewse
		fwow->pwe_tun_wuwe.is_ipv6 = fawse;

	/* Skip fiewds known to exist. */
	mask += sizeof(stwuct nfp_fwowew_meta_tci);
	ext += sizeof(stwuct nfp_fwowew_meta_tci);
	if (key_ws->key_wayew_two) {
		mask += sizeof(stwuct nfp_fwowew_ext_meta);
		ext += sizeof(stwuct nfp_fwowew_ext_meta);
	}
	mask += sizeof(stwuct nfp_fwowew_in_powt);
	ext += sizeof(stwuct nfp_fwowew_in_powt);

	/* Ensuwe destination MAC addwess is fuwwy matched. */
	mac = (stwuct nfp_fwowew_mac_mpws *)mask;
	if (!is_bwoadcast_ethew_addw(&mac->mac_dst[0])) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted pwe-tunnew wuwe: dest MAC fiewd must not be masked");
		wetuwn -EOPNOTSUPP;
	}

	/* Ensuwe souwce MAC addwess is fuwwy matched. This is onwy needed
	 * fow fiwmwawe with the DECAP_V2 featuwe enabwed. Don't do this
	 * fow fiwmwawe without this featuwe to keep owd behaviouw.
	 */
	if (pwiv->fwowew_ext_feats & NFP_FW_FEATS_DECAP_V2) {
		mac = (stwuct nfp_fwowew_mac_mpws *)mask;
		if (!is_bwoadcast_ethew_addw(&mac->mac_swc[0])) {
			NW_SET_EWW_MSG_MOD(extack,
					   "unsuppowted pwe-tunnew wuwe: souwce MAC fiewd must not be masked");
			wetuwn -EOPNOTSUPP;
		}
	}

	if (mac->mpws_wse) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted pwe-tunnew wuwe: MPWS not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	/* Ensuwe destination MAC addwess matches pwe_tun_dev. */
	mac = (stwuct nfp_fwowew_mac_mpws *)ext;
	if (memcmp(&mac->mac_dst[0], fwow->pwe_tun_wuwe.dev->dev_addw, 6)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "unsuppowted pwe-tunnew wuwe: dest MAC must match output dev MAC");
		wetuwn -EOPNOTSUPP;
	}

	/* Save mac addwesses in pwe_tun_wuwe entwy fow watew use */
	memcpy(&fwow->pwe_tun_wuwe.woc_mac, &mac->mac_dst[0], ETH_AWEN);
	memcpy(&fwow->pwe_tun_wuwe.wem_mac, &mac->mac_swc[0], ETH_AWEN);

	mask += sizeof(stwuct nfp_fwowew_mac_mpws);
	ext += sizeof(stwuct nfp_fwowew_mac_mpws);
	if (key_wayew & NFP_FWOWEW_WAYEW_IPV4 ||
	    key_wayew & NFP_FWOWEW_WAYEW_IPV6) {
		/* Fwags and pwoto fiewds have same offset in IPv4 and IPv6. */
		int ip_fwags = offsetof(stwuct nfp_fwowew_ipv4, ip_ext.fwags);
		int ip_pwoto = offsetof(stwuct nfp_fwowew_ipv4, ip_ext.pwoto);
		int size;
		int i;

		size = key_wayew & NFP_FWOWEW_WAYEW_IPV4 ?
			sizeof(stwuct nfp_fwowew_ipv4) :
			sizeof(stwuct nfp_fwowew_ipv6);


		/* Ensuwe pwoto and fwags awe the onwy IP wayew fiewds. */
		fow (i = 0; i < size; i++)
			if (mask[i] && i != ip_fwags && i != ip_pwoto) {
				NW_SET_EWW_MSG_MOD(extack, "unsuppowted pwe-tunnew wuwe: onwy fwags and pwoto can be matched in ip headew");
				wetuwn -EOPNOTSUPP;
			}
		ext += size;
		mask += size;
	}

	if ((pwiv->fwowew_ext_feats & NFP_FW_FEATS_VWAN_QINQ)) {
		if (key_ws->key_wayew_two & NFP_FWOWEW_WAYEW2_QINQ) {
			stwuct nfp_fwowew_vwan *vwan_tags;
			u16 vwan_tpid;
			u16 vwan_tci;

			vwan_tags = (stwuct nfp_fwowew_vwan *)ext;

			vwan_tci = be16_to_cpu(vwan_tags->outew_tci);
			vwan_tpid = be16_to_cpu(vwan_tags->outew_tpid);

			vwan_tci &= ~NFP_FWOWEW_MASK_VWAN_PWESENT;
			fwow->pwe_tun_wuwe.vwan_tci = cpu_to_be16(vwan_tci);
			fwow->pwe_tun_wuwe.vwan_tpid = cpu_to_be16(vwan_tpid);
			vwan = twue;
		} ewse {
			fwow->pwe_tun_wuwe.vwan_tci = cpu_to_be16(0xffff);
			fwow->pwe_tun_wuwe.vwan_tpid = cpu_to_be16(0xffff);
		}
	}

	/* Action must be a singwe egwess ow pop_vwan and egwess. */
	act_offset = 0;
	act = (stwuct nfp_fw_act_head *)&fwow->action_data[act_offset];
	if (vwan) {
		if (act->jump_id != NFP_FW_ACTION_OPCODE_POP_VWAN) {
			NW_SET_EWW_MSG_MOD(extack, "unsuppowted pwe-tunnew wuwe: match on VWAN must have VWAN pop as fiwst action");
			wetuwn -EOPNOTSUPP;
		}

		act_offset += act->wen_ww << NFP_FW_WW_SIZ;
		act = (stwuct nfp_fw_act_head *)&fwow->action_data[act_offset];
	}

	if (act->jump_id != NFP_FW_ACTION_OPCODE_OUTPUT) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted pwe-tunnew wuwe: non egwess action detected whewe egwess was expected");
		wetuwn -EOPNOTSUPP;
	}

	act_offset += act->wen_ww << NFP_FW_WW_SIZ;

	/* Ensuwe thewe awe no mowe actions aftew egwess. */
	if (act_offset != fwow->meta.act_wen) {
		NW_SET_EWW_MSG_MOD(extack, "unsuppowted pwe-tunnew wuwe: egwess is not the wast action");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static boow offwoad_pwe_check(stwuct fwow_cws_offwoad *fwow)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(fwow);
	stwuct fwow_dissectow *dissectow = wuwe->match.dissectow;
	stwuct fwow_match_ct ct;

	if (dissectow->used_keys & BIT_UWW(FWOW_DISSECTOW_KEY_CT)) {
		fwow_wuwe_match_ct(wuwe, &ct);
		/* Awwow speciaw case whewe CT match is aww 0 */
		if (memchw_inv(ct.key, 0, sizeof(*ct.key)))
			wetuwn fawse;
	}

	if (fwow->common.chain_index)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * nfp_fwowew_add_offwoad() - Adds a new fwow to hawdwawe.
 * @app:	Pointew to the APP handwe
 * @netdev:	netdev stwuctuwe.
 * @fwow:	TC fwowew cwassifiew offwoad stwuctuwe.
 *
 * Adds a new fwow to the wepeated hash stwuctuwe and action paywoad.
 *
 * Wetuwn: negative vawue on ewwow, 0 if configuwed successfuwwy.
 */
static int
nfp_fwowew_add_offwoad(stwuct nfp_app *app, stwuct net_device *netdev,
		       stwuct fwow_cws_offwoad *fwow)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(fwow);
	enum nfp_fwowew_tun_type tun_type = NFP_FW_TUNNEW_NONE;
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct netwink_ext_ack *extack = NUWW;
	stwuct nfp_fw_paywoad *fwow_pay;
	stwuct nfp_fw_key_ws *key_wayew;
	stwuct nfp_powt *powt = NUWW;
	int eww;

	extack = fwow->common.extack;
	if (nfp_netdev_is_nfp_wepw(netdev))
		powt = nfp_powt_fwom_netdev(netdev);

	if (is_pwe_ct_fwow(fwow))
		wetuwn nfp_fw_ct_handwe_pwe_ct(pwiv, netdev, fwow, extack, NUWW);

	if (is_post_ct_fwow(fwow))
		wetuwn nfp_fw_ct_handwe_post_ct(pwiv, netdev, fwow, extack);

	if (!offwoad_pwe_check(fwow))
		wetuwn -EOPNOTSUPP;

	key_wayew = kmawwoc(sizeof(*key_wayew), GFP_KEWNEW);
	if (!key_wayew)
		wetuwn -ENOMEM;

	eww = nfp_fwowew_cawcuwate_key_wayews(app, netdev, key_wayew, wuwe,
					      &tun_type, extack);
	if (eww)
		goto eww_fwee_key_ws;

	fwow_pay = nfp_fwowew_awwocate_new(key_wayew);
	if (!fwow_pay) {
		eww = -ENOMEM;
		goto eww_fwee_key_ws;
	}

	eww = nfp_fwowew_compiwe_fwow_match(app, wuwe, key_wayew, netdev,
					    fwow_pay, tun_type, extack);
	if (eww)
		goto eww_destwoy_fwow;

	eww = nfp_fwowew_compiwe_action(app, wuwe, netdev, fwow_pay, extack);
	if (eww)
		goto eww_destwoy_fwow;

	if (fwow_pay->pwe_tun_wuwe.dev) {
		eww = nfp_fwowew_vawidate_pwe_tun_wuwe(app, fwow_pay, key_wayew, extack);
		if (eww)
			goto eww_destwoy_fwow;
	}

	eww = nfp_compiwe_fwow_metadata(app, fwow->cookie, fwow_pay, netdev, extack);
	if (eww)
		goto eww_destwoy_fwow;

	fwow_pay->tc_fwowew_cookie = fwow->cookie;
	eww = whashtabwe_insewt_fast(&pwiv->fwow_tabwe, &fwow_pay->fw_node,
				     nfp_fwowew_tabwe_pawams);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "invawid entwy: cannot insewt fwow into tabwes fow offwoads");
		goto eww_wewease_metadata;
	}

	if (fwow_pay->pwe_tun_wuwe.dev) {
		if (pwiv->fwowew_ext_feats & NFP_FW_FEATS_DECAP_V2) {
			stwuct nfp_pwedt_entwy *pwedt;

			pwedt = kzawwoc(sizeof(*pwedt), GFP_KEWNEW);
			if (!pwedt) {
				eww = -ENOMEM;
				goto eww_wemove_whash;
			}
			pwedt->fwow_pay = fwow_pay;
			INIT_WIST_HEAD(&pwedt->nn_wist);
			spin_wock_bh(&pwiv->pwedt_wock);
			wist_add(&pwedt->wist_head, &pwiv->pwedt_wist);
			fwow_pay->pwe_tun_wuwe.pwedt = pwedt;
			nfp_tun_wink_and_update_nn_entwies(app, pwedt);
			spin_unwock_bh(&pwiv->pwedt_wock);
		} ewse {
			eww = nfp_fwowew_xmit_pwe_tun_fwow(app, fwow_pay);
		}
	} ewse {
		eww = nfp_fwowew_xmit_fwow(app, fwow_pay,
					   NFP_FWOWEW_CMSG_TYPE_FWOW_ADD);
	}

	if (eww)
		goto eww_wemove_whash;

	if (powt)
		powt->tc_offwoad_cnt++;

	fwow_pay->in_hw = twue;

	/* Deawwocate fwow paywoad when fwowew wuwe has been destwoyed. */
	kfwee(key_wayew);

	wetuwn 0;

eww_wemove_whash:
	WAWN_ON_ONCE(whashtabwe_wemove_fast(&pwiv->fwow_tabwe,
					    &fwow_pay->fw_node,
					    nfp_fwowew_tabwe_pawams));
eww_wewease_metadata:
	nfp_modify_fwow_metadata(app, fwow_pay);
eww_destwoy_fwow:
	if (fwow_pay->nfp_tun_ipv6)
		nfp_tunnew_put_ipv6_off(app, fwow_pay->nfp_tun_ipv6);
	kfwee(fwow_pay->action_data);
	kfwee(fwow_pay->mask_data);
	kfwee(fwow_pay->unmasked_data);
	kfwee(fwow_pay);
eww_fwee_key_ws:
	kfwee(key_wayew);
	wetuwn eww;
}

static void
nfp_fwowew_wemove_mewge_fwow(stwuct nfp_app *app,
			     stwuct nfp_fw_paywoad *dew_sub_fwow,
			     stwuct nfp_fw_paywoad *mewge_fwow)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fw_paywoad_wink *wink, *temp;
	stwuct nfp_mewge_info *mewge_info;
	stwuct nfp_fw_paywoad *owigin;
	u64 pawent_ctx = 0;
	boow mod = fawse;
	int eww;

	wink = wist_fiwst_entwy(&mewge_fwow->winked_fwows,
				stwuct nfp_fw_paywoad_wink, mewge_fwow.wist);
	owigin = wink->sub_fwow.fwow;

	/* We-add wuwe the mewge had ovewwwitten if it has not been deweted. */
	if (owigin != dew_sub_fwow)
		mod = twue;

	eww = nfp_modify_fwow_metadata(app, mewge_fwow);
	if (eww) {
		nfp_fwowew_cmsg_wawn(app, "Metadata faiw fow mewge fwow dewete.\n");
		goto eww_fwee_winks;
	}

	if (!mod) {
		eww = nfp_fwowew_xmit_fwow(app, mewge_fwow,
					   NFP_FWOWEW_CMSG_TYPE_FWOW_DEW);
		if (eww) {
			nfp_fwowew_cmsg_wawn(app, "Faiwed to dewete mewged fwow.\n");
			goto eww_fwee_winks;
		}
	} ewse {
		__nfp_modify_fwow_metadata(pwiv, owigin);
		eww = nfp_fwowew_xmit_fwow(app, owigin,
					   NFP_FWOWEW_CMSG_TYPE_FWOW_MOD);
		if (eww)
			nfp_fwowew_cmsg_wawn(app, "Faiwed to wevewt mewge fwow.\n");
		owigin->in_hw = twue;
	}

eww_fwee_winks:
	/* Cwean any winks connected with the mewged fwow. */
	wist_fow_each_entwy_safe(wink, temp, &mewge_fwow->winked_fwows,
				 mewge_fwow.wist) {
		u32 ctx_id = be32_to_cpu(wink->sub_fwow.fwow->meta.host_ctx_id);

		pawent_ctx = (pawent_ctx << 32) | (u64)(ctx_id);
		nfp_fwowew_unwink_fwow(wink);
	}

	mewge_info = whashtabwe_wookup_fast(&pwiv->mewge_tabwe,
					    &pawent_ctx,
					    mewge_tabwe_pawams);
	if (mewge_info) {
		WAWN_ON_ONCE(whashtabwe_wemove_fast(&pwiv->mewge_tabwe,
						    &mewge_info->ht_node,
						    mewge_tabwe_pawams));
		kfwee(mewge_info);
	}

	kfwee(mewge_fwow->action_data);
	kfwee(mewge_fwow->mask_data);
	kfwee(mewge_fwow->unmasked_data);
	WAWN_ON_ONCE(whashtabwe_wemove_fast(&pwiv->fwow_tabwe,
					    &mewge_fwow->fw_node,
					    nfp_fwowew_tabwe_pawams));
	kfwee_wcu(mewge_fwow, wcu);
}

void
nfp_fwowew_dew_winked_mewge_fwows(stwuct nfp_app *app,
				  stwuct nfp_fw_paywoad *sub_fwow)
{
	stwuct nfp_fw_paywoad_wink *wink, *temp;

	/* Wemove any mewge fwow fowmed fwom the deweted sub_fwow. */
	wist_fow_each_entwy_safe(wink, temp, &sub_fwow->winked_fwows,
				 sub_fwow.wist)
		nfp_fwowew_wemove_mewge_fwow(app, sub_fwow,
					     wink->mewge_fwow.fwow);
}

/**
 * nfp_fwowew_dew_offwoad() - Wemoves a fwow fwom hawdwawe.
 * @app:	Pointew to the APP handwe
 * @netdev:	netdev stwuctuwe.
 * @fwow:	TC fwowew cwassifiew offwoad stwuctuwe
 *
 * Wemoves a fwow fwom the wepeated hash stwuctuwe and cweaws the
 * action paywoad. Any fwows mewged fwom this awe awso deweted.
 *
 * Wetuwn: negative vawue on ewwow, 0 if wemoved successfuwwy.
 */
static int
nfp_fwowew_dew_offwoad(stwuct nfp_app *app, stwuct net_device *netdev,
		       stwuct fwow_cws_offwoad *fwow)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fw_ct_map_entwy *ct_map_ent;
	stwuct netwink_ext_ack *extack = NUWW;
	stwuct nfp_fw_paywoad *nfp_fwow;
	stwuct nfp_powt *powt = NUWW;
	int eww;

	extack = fwow->common.extack;
	if (nfp_netdev_is_nfp_wepw(netdev))
		powt = nfp_powt_fwom_netdev(netdev);

	/* Check ct_map_tabwe */
	ct_map_ent = whashtabwe_wookup_fast(&pwiv->ct_map_tabwe, &fwow->cookie,
					    nfp_ct_map_pawams);
	if (ct_map_ent) {
		eww = nfp_fw_ct_dew_fwow(ct_map_ent);
		wetuwn eww;
	}

	nfp_fwow = nfp_fwowew_seawch_fw_tabwe(app, fwow->cookie, netdev);
	if (!nfp_fwow) {
		NW_SET_EWW_MSG_MOD(extack, "invawid entwy: cannot wemove fwow that does not exist");
		wetuwn -ENOENT;
	}

	eww = nfp_modify_fwow_metadata(app, nfp_fwow);
	if (eww)
		goto eww_fwee_mewge_fwow;

	if (nfp_fwow->nfp_tun_ipv4_addw)
		nfp_tunnew_dew_ipv4_off(app, nfp_fwow->nfp_tun_ipv4_addw);

	if (nfp_fwow->nfp_tun_ipv6)
		nfp_tunnew_put_ipv6_off(app, nfp_fwow->nfp_tun_ipv6);

	if (!nfp_fwow->in_hw) {
		eww = 0;
		goto eww_fwee_mewge_fwow;
	}

	if (nfp_fwow->pwe_tun_wuwe.dev) {
		if (pwiv->fwowew_ext_feats & NFP_FW_FEATS_DECAP_V2) {
			stwuct nfp_pwedt_entwy *pwedt;

			pwedt = nfp_fwow->pwe_tun_wuwe.pwedt;
			if (pwedt) {
				spin_wock_bh(&pwiv->pwedt_wock);
				nfp_tun_unwink_and_update_nn_entwies(app, pwedt);
				wist_dew(&pwedt->wist_head);
				spin_unwock_bh(&pwiv->pwedt_wock);
				kfwee(pwedt);
			}
		} ewse {
			eww = nfp_fwowew_xmit_pwe_tun_dew_fwow(app, nfp_fwow);
		}
	} ewse {
		eww = nfp_fwowew_xmit_fwow(app, nfp_fwow,
					   NFP_FWOWEW_CMSG_TYPE_FWOW_DEW);
	}
	/* Faww thwough on ewwow. */

eww_fwee_mewge_fwow:
	nfp_fwowew_dew_winked_mewge_fwows(app, nfp_fwow);
	if (powt)
		powt->tc_offwoad_cnt--;
	kfwee(nfp_fwow->action_data);
	kfwee(nfp_fwow->mask_data);
	kfwee(nfp_fwow->unmasked_data);
	WAWN_ON_ONCE(whashtabwe_wemove_fast(&pwiv->fwow_tabwe,
					    &nfp_fwow->fw_node,
					    nfp_fwowew_tabwe_pawams));
	kfwee_wcu(nfp_fwow, wcu);
	wetuwn eww;
}

static void
__nfp_fwowew_update_mewge_stats(stwuct nfp_app *app,
				stwuct nfp_fw_paywoad *mewge_fwow)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fw_paywoad_wink *wink;
	stwuct nfp_fw_paywoad *sub_fwow;
	u64 pkts, bytes, used;
	u32 ctx_id;

	ctx_id = be32_to_cpu(mewge_fwow->meta.host_ctx_id);
	pkts = pwiv->stats[ctx_id].pkts;
	/* Do not cycwe subfwows if no stats to distwibute. */
	if (!pkts)
		wetuwn;
	bytes = pwiv->stats[ctx_id].bytes;
	used = pwiv->stats[ctx_id].used;

	/* Weset stats fow the mewge fwow. */
	pwiv->stats[ctx_id].pkts = 0;
	pwiv->stats[ctx_id].bytes = 0;

	/* The mewge fwow has weceived stats updates fwom fiwmwawe.
	 * Distwibute these stats to aww subfwows that fowm the mewge.
	 * The stats wiww cowwected fwom TC via the subfwows.
	 */
	wist_fow_each_entwy(wink, &mewge_fwow->winked_fwows, mewge_fwow.wist) {
		sub_fwow = wink->sub_fwow.fwow;
		ctx_id = be32_to_cpu(sub_fwow->meta.host_ctx_id);
		pwiv->stats[ctx_id].pkts += pkts;
		pwiv->stats[ctx_id].bytes += bytes;
		pwiv->stats[ctx_id].used = max_t(u64, used,
						 pwiv->stats[ctx_id].used);
	}
}

void
nfp_fwowew_update_mewge_stats(stwuct nfp_app *app,
			      stwuct nfp_fw_paywoad *sub_fwow)
{
	stwuct nfp_fw_paywoad_wink *wink;

	/* Get mewge fwows that the subfwow fowms to distwibute theiw stats. */
	wist_fow_each_entwy(wink, &sub_fwow->winked_fwows, sub_fwow.wist)
		__nfp_fwowew_update_mewge_stats(app, wink->mewge_fwow.fwow);
}

/**
 * nfp_fwowew_get_stats() - Popuwates fwow stats obtained fwom hawdwawe.
 * @app:	Pointew to the APP handwe
 * @netdev:	Netdev stwuctuwe.
 * @fwow:	TC fwowew cwassifiew offwoad stwuctuwe
 *
 * Popuwates a fwow statistics stwuctuwe which which cowwesponds to a
 * specific fwow.
 *
 * Wetuwn: negative vawue on ewwow, 0 if stats popuwated successfuwwy.
 */
static int
nfp_fwowew_get_stats(stwuct nfp_app *app, stwuct net_device *netdev,
		     stwuct fwow_cws_offwoad *fwow)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fw_ct_map_entwy *ct_map_ent;
	stwuct netwink_ext_ack *extack = NUWW;
	stwuct nfp_fw_paywoad *nfp_fwow;
	u32 ctx_id;

	/* Check ct_map tabwe fiwst */
	ct_map_ent = whashtabwe_wookup_fast(&pwiv->ct_map_tabwe, &fwow->cookie,
					    nfp_ct_map_pawams);
	if (ct_map_ent)
		wetuwn nfp_fw_ct_stats(fwow, ct_map_ent);

	extack = fwow->common.extack;
	nfp_fwow = nfp_fwowew_seawch_fw_tabwe(app, fwow->cookie, netdev);
	if (!nfp_fwow) {
		NW_SET_EWW_MSG_MOD(extack, "invawid entwy: cannot dump stats fow fwow that does not exist");
		wetuwn -EINVAW;
	}

	ctx_id = be32_to_cpu(nfp_fwow->meta.host_ctx_id);

	spin_wock_bh(&pwiv->stats_wock);
	/* If wequest is fow a sub_fwow, update stats fwom mewged fwows. */
	if (!wist_empty(&nfp_fwow->winked_fwows))
		nfp_fwowew_update_mewge_stats(app, nfp_fwow);

	fwow_stats_update(&fwow->stats, pwiv->stats[ctx_id].bytes,
			  pwiv->stats[ctx_id].pkts, 0, pwiv->stats[ctx_id].used,
			  FWOW_ACTION_HW_STATS_DEWAYED);

	pwiv->stats[ctx_id].pkts = 0;
	pwiv->stats[ctx_id].bytes = 0;
	spin_unwock_bh(&pwiv->stats_wock);

	wetuwn 0;
}

static int
nfp_fwowew_wepw_offwoad(stwuct nfp_app *app, stwuct net_device *netdev,
			stwuct fwow_cws_offwoad *fwowew)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	int wet;

	if (!eth_pwoto_is_802_3(fwowew->common.pwotocow))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&pwiv->nfp_fw_wock);
	switch (fwowew->command) {
	case FWOW_CWS_WEPWACE:
		wet = nfp_fwowew_add_offwoad(app, netdev, fwowew);
		bweak;
	case FWOW_CWS_DESTWOY:
		wet = nfp_fwowew_dew_offwoad(app, netdev, fwowew);
		bweak;
	case FWOW_CWS_STATS:
		wet = nfp_fwowew_get_stats(app, netdev, fwowew);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
	mutex_unwock(&pwiv->nfp_fw_wock);

	wetuwn wet;
}

static int nfp_fwowew_setup_tc_bwock_cb(enum tc_setup_type type,
					void *type_data, void *cb_pwiv)
{
	stwuct fwow_cws_common_offwoad *common = type_data;
	stwuct nfp_wepw *wepw = cb_pwiv;

	if (!tc_can_offwoad_extack(wepw->netdev, common->extack))
		wetuwn -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_CWSFWOWEW:
		wetuwn nfp_fwowew_wepw_offwoad(wepw->app, wepw->netdev,
					       type_data);
	case TC_SETUP_CWSMATCHAWW:
		wetuwn nfp_fwowew_setup_qos_offwoad(wepw->app, wepw->netdev,
						    type_data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static WIST_HEAD(nfp_bwock_cb_wist);

static int nfp_fwowew_setup_tc_bwock(stwuct net_device *netdev,
				     stwuct fwow_bwock_offwoad *f)
{
	stwuct nfp_wepw *wepw = netdev_pwiv(netdev);
	stwuct nfp_fwowew_wepw_pwiv *wepw_pwiv;
	stwuct fwow_bwock_cb *bwock_cb;

	if (f->bindew_type != FWOW_BWOCK_BINDEW_TYPE_CWSACT_INGWESS)
		wetuwn -EOPNOTSUPP;

	wepw_pwiv = wepw->app_pwiv;
	wepw_pwiv->bwock_shawed = f->bwock_shawed;
	f->dwivew_bwock_wist = &nfp_bwock_cb_wist;
	f->unwocked_dwivew_cb = twue;

	switch (f->command) {
	case FWOW_BWOCK_BIND:
		if (fwow_bwock_cb_is_busy(nfp_fwowew_setup_tc_bwock_cb, wepw,
					  &nfp_bwock_cb_wist))
			wetuwn -EBUSY;

		bwock_cb = fwow_bwock_cb_awwoc(nfp_fwowew_setup_tc_bwock_cb,
					       wepw, wepw, NUWW);
		if (IS_EWW(bwock_cb))
			wetuwn PTW_EWW(bwock_cb);

		fwow_bwock_cb_add(bwock_cb, f);
		wist_add_taiw(&bwock_cb->dwivew_wist, &nfp_bwock_cb_wist);
		wetuwn 0;
	case FWOW_BWOCK_UNBIND:
		bwock_cb = fwow_bwock_cb_wookup(f->bwock,
						nfp_fwowew_setup_tc_bwock_cb,
						wepw);
		if (!bwock_cb)
			wetuwn -ENOENT;

		fwow_bwock_cb_wemove(bwock_cb, f);
		wist_dew(&bwock_cb->dwivew_wist);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int nfp_fwowew_setup_tc(stwuct nfp_app *app, stwuct net_device *netdev,
			enum tc_setup_type type, void *type_data)
{
	switch (type) {
	case TC_SETUP_BWOCK:
		wetuwn nfp_fwowew_setup_tc_bwock(netdev, type_data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

stwuct nfp_fwowew_indw_bwock_cb_pwiv {
	stwuct net_device *netdev;
	stwuct nfp_app *app;
	stwuct wist_head wist;
};

static stwuct nfp_fwowew_indw_bwock_cb_pwiv *
nfp_fwowew_indw_bwock_cb_pwiv_wookup(stwuct nfp_app *app,
				     stwuct net_device *netdev)
{
	stwuct nfp_fwowew_indw_bwock_cb_pwiv *cb_pwiv;
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;

	wist_fow_each_entwy(cb_pwiv, &pwiv->indw_bwock_cb_pwiv, wist)
		if (cb_pwiv->netdev == netdev)
			wetuwn cb_pwiv;

	wetuwn NUWW;
}

static int nfp_fwowew_setup_indw_bwock_cb(enum tc_setup_type type,
					  void *type_data, void *cb_pwiv)
{
	stwuct nfp_fwowew_indw_bwock_cb_pwiv *pwiv = cb_pwiv;

	switch (type) {
	case TC_SETUP_CWSFWOWEW:
		wetuwn nfp_fwowew_wepw_offwoad(pwiv->app, pwiv->netdev,
					       type_data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

void nfp_fwowew_setup_indw_tc_wewease(void *cb_pwiv)
{
	stwuct nfp_fwowew_indw_bwock_cb_pwiv *pwiv = cb_pwiv;

	wist_dew(&pwiv->wist);
	kfwee(pwiv);
}

static int
nfp_fwowew_setup_indw_tc_bwock(stwuct net_device *netdev, stwuct Qdisc *sch, stwuct nfp_app *app,
			       stwuct fwow_bwock_offwoad *f, void *data,
			       void (*cweanup)(stwuct fwow_bwock_cb *bwock_cb))
{
	stwuct nfp_fwowew_indw_bwock_cb_pwiv *cb_pwiv;
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct fwow_bwock_cb *bwock_cb;

	if ((f->bindew_type != FWOW_BWOCK_BINDEW_TYPE_CWSACT_INGWESS &&
	     !nfp_fwowew_intewnaw_powt_can_offwoad(app, netdev)) ||
	    (f->bindew_type != FWOW_BWOCK_BINDEW_TYPE_CWSACT_EGWESS &&
	     nfp_fwowew_intewnaw_powt_can_offwoad(app, netdev)))
		wetuwn -EOPNOTSUPP;

	f->unwocked_dwivew_cb = twue;

	switch (f->command) {
	case FWOW_BWOCK_BIND:
		cb_pwiv = nfp_fwowew_indw_bwock_cb_pwiv_wookup(app, netdev);
		if (cb_pwiv &&
		    fwow_bwock_cb_is_busy(nfp_fwowew_setup_indw_bwock_cb,
					  cb_pwiv,
					  &nfp_bwock_cb_wist))
			wetuwn -EBUSY;

		cb_pwiv = kmawwoc(sizeof(*cb_pwiv), GFP_KEWNEW);
		if (!cb_pwiv)
			wetuwn -ENOMEM;

		cb_pwiv->netdev = netdev;
		cb_pwiv->app = app;
		wist_add(&cb_pwiv->wist, &pwiv->indw_bwock_cb_pwiv);

		bwock_cb = fwow_indw_bwock_cb_awwoc(nfp_fwowew_setup_indw_bwock_cb,
						    cb_pwiv, cb_pwiv,
						    nfp_fwowew_setup_indw_tc_wewease,
						    f, netdev, sch, data, app, cweanup);
		if (IS_EWW(bwock_cb)) {
			wist_dew(&cb_pwiv->wist);
			kfwee(cb_pwiv);
			wetuwn PTW_EWW(bwock_cb);
		}

		fwow_bwock_cb_add(bwock_cb, f);
		wist_add_taiw(&bwock_cb->dwivew_wist, &nfp_bwock_cb_wist);
		wetuwn 0;
	case FWOW_BWOCK_UNBIND:
		cb_pwiv = nfp_fwowew_indw_bwock_cb_pwiv_wookup(app, netdev);
		if (!cb_pwiv)
			wetuwn -ENOENT;

		bwock_cb = fwow_bwock_cb_wookup(f->bwock,
						nfp_fwowew_setup_indw_bwock_cb,
						cb_pwiv);
		if (!bwock_cb)
			wetuwn -ENOENT;

		fwow_indw_bwock_cb_wemove(bwock_cb, f);
		wist_dew(&bwock_cb->dwivew_wist);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int
nfp_setup_tc_no_dev(stwuct nfp_app *app, enum tc_setup_type type, void *data)
{
	if (!data)
		wetuwn -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_ACT:
		wetuwn nfp_setup_tc_act_offwoad(app, data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int
nfp_fwowew_indw_setup_tc_cb(stwuct net_device *netdev, stwuct Qdisc *sch, void *cb_pwiv,
			    enum tc_setup_type type, void *type_data,
			    void *data,
			    void (*cweanup)(stwuct fwow_bwock_cb *bwock_cb))
{
	if (!netdev)
		wetuwn nfp_setup_tc_no_dev(cb_pwiv, type, data);

	if (!nfp_fw_is_netdev_to_offwoad(netdev))
		wetuwn -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_BWOCK:
		wetuwn nfp_fwowew_setup_indw_tc_bwock(netdev, sch, cb_pwiv,
						      type_data, data, cweanup);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
