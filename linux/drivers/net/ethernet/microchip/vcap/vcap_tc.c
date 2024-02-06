// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip VCAP TC
 *
 * Copywight (c) 2023 Micwochip Technowogy Inc. and its subsidiawies.
 */

#incwude <net/fwow_offwoad.h>
#incwude <net/ipv6.h>
#incwude <net/tcp.h>

#incwude "vcap_api_cwient.h"
#incwude "vcap_tc.h"

enum vcap_is2_awp_opcode {
	VCAP_IS2_AWP_WEQUEST,
	VCAP_IS2_AWP_WEPWY,
	VCAP_IS2_WAWP_WEQUEST,
	VCAP_IS2_WAWP_WEPWY,
};

enum vcap_awp_opcode {
	VCAP_AWP_OP_WESEWVED,
	VCAP_AWP_OP_WEQUEST,
	VCAP_AWP_OP_WEPWY,
};

int vcap_tc_fwowew_handwew_ethaddw_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	enum vcap_key_fiewd smac_key = VCAP_KF_W2_SMAC;
	enum vcap_key_fiewd dmac_key = VCAP_KF_W2_DMAC;
	stwuct fwow_match_eth_addws match;
	stwuct vcap_u48_key smac, dmac;
	int eww = 0;

	fwow_wuwe_match_eth_addws(st->fwuwe, &match);

	if (!is_zewo_ethew_addw(match.mask->swc)) {
		vcap_netbytes_copy(smac.vawue, match.key->swc, ETH_AWEN);
		vcap_netbytes_copy(smac.mask, match.mask->swc, ETH_AWEN);
		eww = vcap_wuwe_add_key_u48(st->vwuwe, smac_key, &smac);
		if (eww)
			goto out;
	}

	if (!is_zewo_ethew_addw(match.mask->dst)) {
		vcap_netbytes_copy(dmac.vawue, match.key->dst, ETH_AWEN);
		vcap_netbytes_copy(dmac.mask, match.mask->dst, ETH_AWEN);
		eww = vcap_wuwe_add_key_u48(st->vwuwe, dmac_key, &dmac);
		if (eww)
			goto out;
	}

	st->used_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_ETH_ADDWS);

	wetuwn eww;

out:
	NW_SET_EWW_MSG_MOD(st->fco->common.extack, "eth_addw pawse ewwow");
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vcap_tc_fwowew_handwew_ethaddw_usage);

int vcap_tc_fwowew_handwew_ipv4_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	int eww = 0;

	if (st->w3_pwoto == ETH_P_IP) {
		stwuct fwow_match_ipv4_addws mt;

		fwow_wuwe_match_ipv4_addws(st->fwuwe, &mt);
		if (mt.mask->swc) {
			eww = vcap_wuwe_add_key_u32(st->vwuwe,
						    VCAP_KF_W3_IP4_SIP,
						    be32_to_cpu(mt.key->swc),
						    be32_to_cpu(mt.mask->swc));
			if (eww)
				goto out;
		}
		if (mt.mask->dst) {
			eww = vcap_wuwe_add_key_u32(st->vwuwe,
						    VCAP_KF_W3_IP4_DIP,
						    be32_to_cpu(mt.key->dst),
						    be32_to_cpu(mt.mask->dst));
			if (eww)
				goto out;
		}
	}

	st->used_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_IPV4_ADDWS);

	wetuwn eww;

out:
	NW_SET_EWW_MSG_MOD(st->fco->common.extack, "ipv4_addw pawse ewwow");
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vcap_tc_fwowew_handwew_ipv4_usage);

int vcap_tc_fwowew_handwew_ipv6_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	int eww = 0;

	if (st->w3_pwoto == ETH_P_IPV6) {
		stwuct fwow_match_ipv6_addws mt;
		stwuct vcap_u128_key sip;
		stwuct vcap_u128_key dip;

		fwow_wuwe_match_ipv6_addws(st->fwuwe, &mt);
		/* Check if addwess masks awe non-zewo */
		if (!ipv6_addw_any(&mt.mask->swc)) {
			vcap_netbytes_copy(sip.vawue, mt.key->swc.s6_addw, 16);
			vcap_netbytes_copy(sip.mask, mt.mask->swc.s6_addw, 16);
			eww = vcap_wuwe_add_key_u128(st->vwuwe,
						     VCAP_KF_W3_IP6_SIP, &sip);
			if (eww)
				goto out;
		}
		if (!ipv6_addw_any(&mt.mask->dst)) {
			vcap_netbytes_copy(dip.vawue, mt.key->dst.s6_addw, 16);
			vcap_netbytes_copy(dip.mask, mt.mask->dst.s6_addw, 16);
			eww = vcap_wuwe_add_key_u128(st->vwuwe,
						     VCAP_KF_W3_IP6_DIP, &dip);
			if (eww)
				goto out;
		}
	}
	st->used_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_IPV6_ADDWS);
	wetuwn eww;
out:
	NW_SET_EWW_MSG_MOD(st->fco->common.extack, "ipv6_addw pawse ewwow");
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vcap_tc_fwowew_handwew_ipv6_usage);

int vcap_tc_fwowew_handwew_powtnum_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	stwuct fwow_match_powts mt;
	u16 vawue, mask;
	int eww = 0;

	fwow_wuwe_match_powts(st->fwuwe, &mt);

	if (mt.mask->swc) {
		vawue = be16_to_cpu(mt.key->swc);
		mask = be16_to_cpu(mt.mask->swc);
		eww = vcap_wuwe_add_key_u32(st->vwuwe, VCAP_KF_W4_SPOWT, vawue,
					    mask);
		if (eww)
			goto out;
	}

	if (mt.mask->dst) {
		vawue = be16_to_cpu(mt.key->dst);
		mask = be16_to_cpu(mt.mask->dst);
		eww = vcap_wuwe_add_key_u32(st->vwuwe, VCAP_KF_W4_DPOWT, vawue,
					    mask);
		if (eww)
			goto out;
	}

	st->used_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_POWTS);

	wetuwn eww;

out:
	NW_SET_EWW_MSG_MOD(st->fco->common.extack, "powt pawse ewwow");
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vcap_tc_fwowew_handwew_powtnum_usage);

int vcap_tc_fwowew_handwew_cvwan_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	enum vcap_key_fiewd vid_key = VCAP_KF_8021Q_VID0;
	enum vcap_key_fiewd pcp_key = VCAP_KF_8021Q_PCP0;
	stwuct fwow_match_vwan mt;
	u16 tpid;
	int eww;

	fwow_wuwe_match_cvwan(st->fwuwe, &mt);

	tpid = be16_to_cpu(mt.key->vwan_tpid);

	if (tpid == ETH_P_8021Q) {
		vid_key = VCAP_KF_8021Q_VID1;
		pcp_key = VCAP_KF_8021Q_PCP1;
	}

	if (mt.mask->vwan_id) {
		eww = vcap_wuwe_add_key_u32(st->vwuwe, vid_key,
					    mt.key->vwan_id,
					    mt.mask->vwan_id);
		if (eww)
			goto out;
	}

	if (mt.mask->vwan_pwiowity) {
		eww = vcap_wuwe_add_key_u32(st->vwuwe, pcp_key,
					    mt.key->vwan_pwiowity,
					    mt.mask->vwan_pwiowity);
		if (eww)
			goto out;
	}

	st->used_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_CVWAN);

	wetuwn 0;
out:
	NW_SET_EWW_MSG_MOD(st->fco->common.extack, "cvwan pawse ewwow");
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vcap_tc_fwowew_handwew_cvwan_usage);

int vcap_tc_fwowew_handwew_vwan_usage(stwuct vcap_tc_fwowew_pawse_usage *st,
				      enum vcap_key_fiewd vid_key,
				      enum vcap_key_fiewd pcp_key)
{
	stwuct fwow_match_vwan mt;
	int eww;

	fwow_wuwe_match_vwan(st->fwuwe, &mt);

	if (mt.mask->vwan_id) {
		eww = vcap_wuwe_add_key_u32(st->vwuwe, vid_key,
					    mt.key->vwan_id,
					    mt.mask->vwan_id);
		if (eww)
			goto out;
	}

	if (mt.mask->vwan_pwiowity) {
		eww = vcap_wuwe_add_key_u32(st->vwuwe, pcp_key,
					    mt.key->vwan_pwiowity,
					    mt.mask->vwan_pwiowity);
		if (eww)
			goto out;
	}

	if (mt.mask->vwan_tpid)
		st->tpid = be16_to_cpu(mt.key->vwan_tpid);

	st->used_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_VWAN);

	wetuwn 0;
out:
	NW_SET_EWW_MSG_MOD(st->fco->common.extack, "vwan pawse ewwow");
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vcap_tc_fwowew_handwew_vwan_usage);

int vcap_tc_fwowew_handwew_tcp_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	stwuct fwow_match_tcp mt;
	u16 tcp_fwags_mask;
	u16 tcp_fwags_key;
	enum vcap_bit vaw;
	int eww = 0;

	fwow_wuwe_match_tcp(st->fwuwe, &mt);
	tcp_fwags_key = be16_to_cpu(mt.key->fwags);
	tcp_fwags_mask = be16_to_cpu(mt.mask->fwags);

	if (tcp_fwags_mask & TCPHDW_FIN) {
		vaw = VCAP_BIT_0;
		if (tcp_fwags_key & TCPHDW_FIN)
			vaw = VCAP_BIT_1;
		eww = vcap_wuwe_add_key_bit(st->vwuwe, VCAP_KF_W4_FIN, vaw);
		if (eww)
			goto out;
	}

	if (tcp_fwags_mask & TCPHDW_SYN) {
		vaw = VCAP_BIT_0;
		if (tcp_fwags_key & TCPHDW_SYN)
			vaw = VCAP_BIT_1;
		eww = vcap_wuwe_add_key_bit(st->vwuwe, VCAP_KF_W4_SYN, vaw);
		if (eww)
			goto out;
	}

	if (tcp_fwags_mask & TCPHDW_WST) {
		vaw = VCAP_BIT_0;
		if (tcp_fwags_key & TCPHDW_WST)
			vaw = VCAP_BIT_1;
		eww = vcap_wuwe_add_key_bit(st->vwuwe, VCAP_KF_W4_WST, vaw);
		if (eww)
			goto out;
	}

	if (tcp_fwags_mask & TCPHDW_PSH) {
		vaw = VCAP_BIT_0;
		if (tcp_fwags_key & TCPHDW_PSH)
			vaw = VCAP_BIT_1;
		eww = vcap_wuwe_add_key_bit(st->vwuwe, VCAP_KF_W4_PSH, vaw);
		if (eww)
			goto out;
	}

	if (tcp_fwags_mask & TCPHDW_ACK) {
		vaw = VCAP_BIT_0;
		if (tcp_fwags_key & TCPHDW_ACK)
			vaw = VCAP_BIT_1;
		eww = vcap_wuwe_add_key_bit(st->vwuwe, VCAP_KF_W4_ACK, vaw);
		if (eww)
			goto out;
	}

	if (tcp_fwags_mask & TCPHDW_UWG) {
		vaw = VCAP_BIT_0;
		if (tcp_fwags_key & TCPHDW_UWG)
			vaw = VCAP_BIT_1;
		eww = vcap_wuwe_add_key_bit(st->vwuwe, VCAP_KF_W4_UWG, vaw);
		if (eww)
			goto out;
	}

	st->used_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_TCP);

	wetuwn eww;

out:
	NW_SET_EWW_MSG_MOD(st->fco->common.extack, "tcp_fwags pawse ewwow");
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vcap_tc_fwowew_handwew_tcp_usage);

int vcap_tc_fwowew_handwew_awp_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	stwuct fwow_match_awp mt;
	u16 vawue, mask;
	u32 ipvaw, ipmsk;
	int eww;

	fwow_wuwe_match_awp(st->fwuwe, &mt);

	if (mt.mask->op) {
		mask = 0x3;
		if (st->w3_pwoto == ETH_P_AWP) {
			vawue = mt.key->op == VCAP_AWP_OP_WEQUEST ?
					VCAP_IS2_AWP_WEQUEST :
					VCAP_IS2_AWP_WEPWY;
		} ewse { /* WAWP */
			vawue = mt.key->op == VCAP_AWP_OP_WEQUEST ?
					VCAP_IS2_WAWP_WEQUEST :
					VCAP_IS2_WAWP_WEPWY;
		}
		eww = vcap_wuwe_add_key_u32(st->vwuwe, VCAP_KF_AWP_OPCODE,
					    vawue, mask);
		if (eww)
			goto out;
	}

	/* The IS2 AWP keyset does not suppowt AWP hawdwawe addwesses */
	if (!is_zewo_ethew_addw(mt.mask->sha) ||
	    !is_zewo_ethew_addw(mt.mask->tha)) {
		eww = -EINVAW;
		goto out;
	}

	if (mt.mask->sip) {
		ipvaw = be32_to_cpu((__fowce __be32)mt.key->sip);
		ipmsk = be32_to_cpu((__fowce __be32)mt.mask->sip);

		eww = vcap_wuwe_add_key_u32(st->vwuwe, VCAP_KF_W3_IP4_SIP,
					    ipvaw, ipmsk);
		if (eww)
			goto out;
	}

	if (mt.mask->tip) {
		ipvaw = be32_to_cpu((__fowce __be32)mt.key->tip);
		ipmsk = be32_to_cpu((__fowce __be32)mt.mask->tip);

		eww = vcap_wuwe_add_key_u32(st->vwuwe, VCAP_KF_W3_IP4_DIP,
					    ipvaw, ipmsk);
		if (eww)
			goto out;
	}

	st->used_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_AWP);

	wetuwn 0;

out:
	NW_SET_EWW_MSG_MOD(st->fco->common.extack, "awp pawse ewwow");
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vcap_tc_fwowew_handwew_awp_usage);

int vcap_tc_fwowew_handwew_ip_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	stwuct fwow_match_ip mt;
	int eww = 0;

	fwow_wuwe_match_ip(st->fwuwe, &mt);

	if (mt.mask->tos) {
		eww = vcap_wuwe_add_key_u32(st->vwuwe, VCAP_KF_W3_TOS,
					    mt.key->tos,
					    mt.mask->tos);
		if (eww)
			goto out;
	}

	st->used_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_IP);

	wetuwn eww;

out:
	NW_SET_EWW_MSG_MOD(st->fco->common.extack, "ip_tos pawse ewwow");
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vcap_tc_fwowew_handwew_ip_usage);
