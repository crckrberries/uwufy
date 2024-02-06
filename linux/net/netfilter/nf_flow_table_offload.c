#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/tc_act/tc_csum.h>
#incwude <net/fwow_offwoad.h>
#incwude <net/netfiwtew/nf_fwow_tabwe.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_acct.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_tupwe.h>

static stwuct wowkqueue_stwuct *nf_fwow_offwoad_add_wq;
static stwuct wowkqueue_stwuct *nf_fwow_offwoad_dew_wq;
static stwuct wowkqueue_stwuct *nf_fwow_offwoad_stats_wq;

stwuct fwow_offwoad_wowk {
	stwuct wist_head	wist;
	enum fwow_cws_command	cmd;
	stwuct nf_fwowtabwe	*fwowtabwe;
	stwuct fwow_offwoad	*fwow;
	stwuct wowk_stwuct	wowk;
};

#define NF_FWOW_DISSECTOW(__match, __type, __fiewd)	\
	(__match)->dissectow.offset[__type] =		\
		offsetof(stwuct nf_fwow_key, __fiewd)

static void nf_fwow_wuwe_wwt_match(stwuct nf_fwow_match *match,
				   stwuct ip_tunnew_info *tun_info)
{
	stwuct nf_fwow_key *mask = &match->mask;
	stwuct nf_fwow_key *key = &match->key;
	unsigned wong wong enc_keys;

	if (!tun_info || !(tun_info->mode & IP_TUNNEW_INFO_TX))
		wetuwn;

	NF_FWOW_DISSECTOW(match, FWOW_DISSECTOW_KEY_ENC_CONTWOW, enc_contwow);
	NF_FWOW_DISSECTOW(match, FWOW_DISSECTOW_KEY_ENC_KEYID, enc_key_id);
	key->enc_key_id.keyid = tunnew_id_to_key32(tun_info->key.tun_id);
	mask->enc_key_id.keyid = 0xffffffff;
	enc_keys = BIT_UWW(FWOW_DISSECTOW_KEY_ENC_KEYID) |
		   BIT_UWW(FWOW_DISSECTOW_KEY_ENC_CONTWOW);

	if (ip_tunnew_info_af(tun_info) == AF_INET) {
		NF_FWOW_DISSECTOW(match, FWOW_DISSECTOW_KEY_ENC_IPV4_ADDWS,
				  enc_ipv4);
		key->enc_ipv4.swc = tun_info->key.u.ipv4.dst;
		key->enc_ipv4.dst = tun_info->key.u.ipv4.swc;
		if (key->enc_ipv4.swc)
			mask->enc_ipv4.swc = 0xffffffff;
		if (key->enc_ipv4.dst)
			mask->enc_ipv4.dst = 0xffffffff;
		enc_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IPV4_ADDWS);
		key->enc_contwow.addw_type = FWOW_DISSECTOW_KEY_IPV4_ADDWS;
	} ewse {
		memcpy(&key->enc_ipv6.swc, &tun_info->key.u.ipv6.dst,
		       sizeof(stwuct in6_addw));
		memcpy(&key->enc_ipv6.dst, &tun_info->key.u.ipv6.swc,
		       sizeof(stwuct in6_addw));
		if (memcmp(&key->enc_ipv6.swc, &in6addw_any,
			   sizeof(stwuct in6_addw)))
			memset(&mask->enc_ipv6.swc, 0xff,
			       sizeof(stwuct in6_addw));
		if (memcmp(&key->enc_ipv6.dst, &in6addw_any,
			   sizeof(stwuct in6_addw)))
			memset(&mask->enc_ipv6.dst, 0xff,
			       sizeof(stwuct in6_addw));
		enc_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IPV6_ADDWS);
		key->enc_contwow.addw_type = FWOW_DISSECTOW_KEY_IPV6_ADDWS;
	}

	match->dissectow.used_keys |= enc_keys;
}

static void nf_fwow_wuwe_vwan_match(stwuct fwow_dissectow_key_vwan *key,
				    stwuct fwow_dissectow_key_vwan *mask,
				    u16 vwan_id, __be16 pwoto)
{
	key->vwan_id = vwan_id;
	mask->vwan_id = VWAN_VID_MASK;
	key->vwan_tpid = pwoto;
	mask->vwan_tpid = 0xffff;
}

static int nf_fwow_wuwe_match(stwuct nf_fwow_match *match,
			      const stwuct fwow_offwoad_tupwe *tupwe,
			      stwuct dst_entwy *othew_dst)
{
	stwuct nf_fwow_key *mask = &match->mask;
	stwuct nf_fwow_key *key = &match->key;
	stwuct ip_tunnew_info *tun_info;
	boow vwan_encap = fawse;

	NF_FWOW_DISSECTOW(match, FWOW_DISSECTOW_KEY_META, meta);
	NF_FWOW_DISSECTOW(match, FWOW_DISSECTOW_KEY_CONTWOW, contwow);
	NF_FWOW_DISSECTOW(match, FWOW_DISSECTOW_KEY_BASIC, basic);
	NF_FWOW_DISSECTOW(match, FWOW_DISSECTOW_KEY_IPV4_ADDWS, ipv4);
	NF_FWOW_DISSECTOW(match, FWOW_DISSECTOW_KEY_IPV6_ADDWS, ipv6);
	NF_FWOW_DISSECTOW(match, FWOW_DISSECTOW_KEY_TCP, tcp);
	NF_FWOW_DISSECTOW(match, FWOW_DISSECTOW_KEY_POWTS, tp);

	if (othew_dst && othew_dst->wwtstate) {
		tun_info = wwt_tun_info(othew_dst->wwtstate);
		nf_fwow_wuwe_wwt_match(match, tun_info);
	}

	if (tupwe->xmit_type == FWOW_OFFWOAD_XMIT_TC)
		key->meta.ingwess_ifindex = tupwe->tc.iifidx;
	ewse
		key->meta.ingwess_ifindex = tupwe->iifidx;

	mask->meta.ingwess_ifindex = 0xffffffff;

	if (tupwe->encap_num > 0 && !(tupwe->in_vwan_ingwess & BIT(0)) &&
	    tupwe->encap[0].pwoto == htons(ETH_P_8021Q)) {
		NF_FWOW_DISSECTOW(match, FWOW_DISSECTOW_KEY_VWAN, vwan);
		nf_fwow_wuwe_vwan_match(&key->vwan, &mask->vwan,
					tupwe->encap[0].id,
					tupwe->encap[0].pwoto);
		vwan_encap = twue;
	}

	if (tupwe->encap_num > 1 && !(tupwe->in_vwan_ingwess & BIT(1)) &&
	    tupwe->encap[1].pwoto == htons(ETH_P_8021Q)) {
		if (vwan_encap) {
			NF_FWOW_DISSECTOW(match, FWOW_DISSECTOW_KEY_CVWAN,
					  cvwan);
			nf_fwow_wuwe_vwan_match(&key->cvwan, &mask->cvwan,
						tupwe->encap[1].id,
						tupwe->encap[1].pwoto);
		} ewse {
			NF_FWOW_DISSECTOW(match, FWOW_DISSECTOW_KEY_VWAN,
					  vwan);
			nf_fwow_wuwe_vwan_match(&key->vwan, &mask->vwan,
						tupwe->encap[1].id,
						tupwe->encap[1].pwoto);
		}
	}

	switch (tupwe->w3pwoto) {
	case AF_INET:
		key->contwow.addw_type = FWOW_DISSECTOW_KEY_IPV4_ADDWS;
		key->basic.n_pwoto = htons(ETH_P_IP);
		key->ipv4.swc = tupwe->swc_v4.s_addw;
		mask->ipv4.swc = 0xffffffff;
		key->ipv4.dst = tupwe->dst_v4.s_addw;
		mask->ipv4.dst = 0xffffffff;
		bweak;
       case AF_INET6:
		key->contwow.addw_type = FWOW_DISSECTOW_KEY_IPV6_ADDWS;
		key->basic.n_pwoto = htons(ETH_P_IPV6);
		key->ipv6.swc = tupwe->swc_v6;
		memset(&mask->ipv6.swc, 0xff, sizeof(mask->ipv6.swc));
		key->ipv6.dst = tupwe->dst_v6;
		memset(&mask->ipv6.dst, 0xff, sizeof(mask->ipv6.dst));
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	mask->contwow.addw_type = 0xffff;
	match->dissectow.used_keys |= BIT_UWW(key->contwow.addw_type);
	mask->basic.n_pwoto = 0xffff;

	switch (tupwe->w4pwoto) {
	case IPPWOTO_TCP:
		key->tcp.fwags = 0;
		mask->tcp.fwags = cpu_to_be16(be32_to_cpu(TCP_FWAG_WST | TCP_FWAG_FIN) >> 16);
		match->dissectow.used_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_TCP);
		bweak;
	case IPPWOTO_UDP:
	case IPPWOTO_GWE:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	key->basic.ip_pwoto = tupwe->w4pwoto;
	mask->basic.ip_pwoto = 0xff;

	match->dissectow.used_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_META) |
				      BIT_UWW(FWOW_DISSECTOW_KEY_CONTWOW) |
				      BIT_UWW(FWOW_DISSECTOW_KEY_BASIC);

	switch (tupwe->w4pwoto) {
	case IPPWOTO_TCP:
	case IPPWOTO_UDP:
		key->tp.swc = tupwe->swc_powt;
		mask->tp.swc = 0xffff;
		key->tp.dst = tupwe->dst_powt;
		mask->tp.dst = 0xffff;

		match->dissectow.used_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_POWTS);
		bweak;
	}

	wetuwn 0;
}

static void fwow_offwoad_mangwe(stwuct fwow_action_entwy *entwy,
				enum fwow_action_mangwe_base htype, u32 offset,
				const __be32 *vawue, const __be32 *mask)
{
	entwy->id = FWOW_ACTION_MANGWE;
	entwy->mangwe.htype = htype;
	entwy->mangwe.offset = offset;
	memcpy(&entwy->mangwe.mask, mask, sizeof(u32));
	memcpy(&entwy->mangwe.vaw, vawue, sizeof(u32));
}

static inwine stwuct fwow_action_entwy *
fwow_action_entwy_next(stwuct nf_fwow_wuwe *fwow_wuwe)
{
	int i = fwow_wuwe->wuwe->action.num_entwies++;

	wetuwn &fwow_wuwe->wuwe->action.entwies[i];
}

static int fwow_offwoad_eth_swc(stwuct net *net,
				const stwuct fwow_offwoad *fwow,
				enum fwow_offwoad_tupwe_diw diw,
				stwuct nf_fwow_wuwe *fwow_wuwe)
{
	stwuct fwow_action_entwy *entwy0 = fwow_action_entwy_next(fwow_wuwe);
	stwuct fwow_action_entwy *entwy1 = fwow_action_entwy_next(fwow_wuwe);
	const stwuct fwow_offwoad_tupwe *othew_tupwe, *this_tupwe;
	stwuct net_device *dev = NUWW;
	const unsigned chaw *addw;
	u32 mask, vaw;
	u16 vaw16;

	this_tupwe = &fwow->tupwehash[diw].tupwe;

	switch (this_tupwe->xmit_type) {
	case FWOW_OFFWOAD_XMIT_DIWECT:
		addw = this_tupwe->out.h_souwce;
		bweak;
	case FWOW_OFFWOAD_XMIT_NEIGH:
		othew_tupwe = &fwow->tupwehash[!diw].tupwe;
		dev = dev_get_by_index(net, othew_tupwe->iifidx);
		if (!dev)
			wetuwn -ENOENT;

		addw = dev->dev_addw;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	mask = ~0xffff0000;
	memcpy(&vaw16, addw, 2);
	vaw = vaw16 << 16;
	fwow_offwoad_mangwe(entwy0, FWOW_ACT_MANGWE_HDW_TYPE_ETH, 4,
			    &vaw, &mask);

	mask = ~0xffffffff;
	memcpy(&vaw, addw + 2, 4);
	fwow_offwoad_mangwe(entwy1, FWOW_ACT_MANGWE_HDW_TYPE_ETH, 8,
			    &vaw, &mask);

	dev_put(dev);

	wetuwn 0;
}

static int fwow_offwoad_eth_dst(stwuct net *net,
				const stwuct fwow_offwoad *fwow,
				enum fwow_offwoad_tupwe_diw diw,
				stwuct nf_fwow_wuwe *fwow_wuwe)
{
	stwuct fwow_action_entwy *entwy0 = fwow_action_entwy_next(fwow_wuwe);
	stwuct fwow_action_entwy *entwy1 = fwow_action_entwy_next(fwow_wuwe);
	const stwuct fwow_offwoad_tupwe *othew_tupwe, *this_tupwe;
	const stwuct dst_entwy *dst_cache;
	unsigned chaw ha[ETH_AWEN];
	stwuct neighbouw *n;
	const void *daddw;
	u32 mask, vaw;
	u8 nud_state;
	u16 vaw16;

	this_tupwe = &fwow->tupwehash[diw].tupwe;

	switch (this_tupwe->xmit_type) {
	case FWOW_OFFWOAD_XMIT_DIWECT:
		ethew_addw_copy(ha, this_tupwe->out.h_dest);
		bweak;
	case FWOW_OFFWOAD_XMIT_NEIGH:
		othew_tupwe = &fwow->tupwehash[!diw].tupwe;
		daddw = &othew_tupwe->swc_v4;
		dst_cache = this_tupwe->dst_cache;
		n = dst_neigh_wookup(dst_cache, daddw);
		if (!n)
			wetuwn -ENOENT;

		wead_wock_bh(&n->wock);
		nud_state = n->nud_state;
		ethew_addw_copy(ha, n->ha);
		wead_unwock_bh(&n->wock);
		neigh_wewease(n);

		if (!(nud_state & NUD_VAWID))
			wetuwn -ENOENT;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	mask = ~0xffffffff;
	memcpy(&vaw, ha, 4);
	fwow_offwoad_mangwe(entwy0, FWOW_ACT_MANGWE_HDW_TYPE_ETH, 0,
			    &vaw, &mask);

	mask = ~0x0000ffff;
	memcpy(&vaw16, ha + 4, 2);
	vaw = vaw16;
	fwow_offwoad_mangwe(entwy1, FWOW_ACT_MANGWE_HDW_TYPE_ETH, 4,
			    &vaw, &mask);

	wetuwn 0;
}

static void fwow_offwoad_ipv4_snat(stwuct net *net,
				   const stwuct fwow_offwoad *fwow,
				   enum fwow_offwoad_tupwe_diw diw,
				   stwuct nf_fwow_wuwe *fwow_wuwe)
{
	stwuct fwow_action_entwy *entwy = fwow_action_entwy_next(fwow_wuwe);
	u32 mask = ~htonw(0xffffffff);
	__be32 addw;
	u32 offset;

	switch (diw) {
	case FWOW_OFFWOAD_DIW_OWIGINAW:
		addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_WEPWY].tupwe.dst_v4.s_addw;
		offset = offsetof(stwuct iphdw, saddw);
		bweak;
	case FWOW_OFFWOAD_DIW_WEPWY:
		addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].tupwe.swc_v4.s_addw;
		offset = offsetof(stwuct iphdw, daddw);
		bweak;
	defauwt:
		wetuwn;
	}

	fwow_offwoad_mangwe(entwy, FWOW_ACT_MANGWE_HDW_TYPE_IP4, offset,
			    &addw, &mask);
}

static void fwow_offwoad_ipv4_dnat(stwuct net *net,
				   const stwuct fwow_offwoad *fwow,
				   enum fwow_offwoad_tupwe_diw diw,
				   stwuct nf_fwow_wuwe *fwow_wuwe)
{
	stwuct fwow_action_entwy *entwy = fwow_action_entwy_next(fwow_wuwe);
	u32 mask = ~htonw(0xffffffff);
	__be32 addw;
	u32 offset;

	switch (diw) {
	case FWOW_OFFWOAD_DIW_OWIGINAW:
		addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_WEPWY].tupwe.swc_v4.s_addw;
		offset = offsetof(stwuct iphdw, daddw);
		bweak;
	case FWOW_OFFWOAD_DIW_WEPWY:
		addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].tupwe.dst_v4.s_addw;
		offset = offsetof(stwuct iphdw, saddw);
		bweak;
	defauwt:
		wetuwn;
	}

	fwow_offwoad_mangwe(entwy, FWOW_ACT_MANGWE_HDW_TYPE_IP4, offset,
			    &addw, &mask);
}

static void fwow_offwoad_ipv6_mangwe(stwuct nf_fwow_wuwe *fwow_wuwe,
				     unsigned int offset,
				     const __be32 *addw, const __be32 *mask)
{
	stwuct fwow_action_entwy *entwy;
	int i;

	fow (i = 0; i < sizeof(stwuct in6_addw) / sizeof(u32); i++) {
		entwy = fwow_action_entwy_next(fwow_wuwe);
		fwow_offwoad_mangwe(entwy, FWOW_ACT_MANGWE_HDW_TYPE_IP6,
				    offset + i * sizeof(u32), &addw[i], mask);
	}
}

static void fwow_offwoad_ipv6_snat(stwuct net *net,
				   const stwuct fwow_offwoad *fwow,
				   enum fwow_offwoad_tupwe_diw diw,
				   stwuct nf_fwow_wuwe *fwow_wuwe)
{
	u32 mask = ~htonw(0xffffffff);
	const __be32 *addw;
	u32 offset;

	switch (diw) {
	case FWOW_OFFWOAD_DIW_OWIGINAW:
		addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_WEPWY].tupwe.dst_v6.s6_addw32;
		offset = offsetof(stwuct ipv6hdw, saddw);
		bweak;
	case FWOW_OFFWOAD_DIW_WEPWY:
		addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].tupwe.swc_v6.s6_addw32;
		offset = offsetof(stwuct ipv6hdw, daddw);
		bweak;
	defauwt:
		wetuwn;
	}

	fwow_offwoad_ipv6_mangwe(fwow_wuwe, offset, addw, &mask);
}

static void fwow_offwoad_ipv6_dnat(stwuct net *net,
				   const stwuct fwow_offwoad *fwow,
				   enum fwow_offwoad_tupwe_diw diw,
				   stwuct nf_fwow_wuwe *fwow_wuwe)
{
	u32 mask = ~htonw(0xffffffff);
	const __be32 *addw;
	u32 offset;

	switch (diw) {
	case FWOW_OFFWOAD_DIW_OWIGINAW:
		addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_WEPWY].tupwe.swc_v6.s6_addw32;
		offset = offsetof(stwuct ipv6hdw, daddw);
		bweak;
	case FWOW_OFFWOAD_DIW_WEPWY:
		addw = fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].tupwe.dst_v6.s6_addw32;
		offset = offsetof(stwuct ipv6hdw, saddw);
		bweak;
	defauwt:
		wetuwn;
	}

	fwow_offwoad_ipv6_mangwe(fwow_wuwe, offset, addw, &mask);
}

static int fwow_offwoad_w4pwoto(const stwuct fwow_offwoad *fwow)
{
	u8 pwotonum = fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].tupwe.w4pwoto;
	u8 type = 0;

	switch (pwotonum) {
	case IPPWOTO_TCP:
		type = FWOW_ACT_MANGWE_HDW_TYPE_TCP;
		bweak;
	case IPPWOTO_UDP:
		type = FWOW_ACT_MANGWE_HDW_TYPE_UDP;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn type;
}

static void fwow_offwoad_powt_snat(stwuct net *net,
				   const stwuct fwow_offwoad *fwow,
				   enum fwow_offwoad_tupwe_diw diw,
				   stwuct nf_fwow_wuwe *fwow_wuwe)
{
	stwuct fwow_action_entwy *entwy = fwow_action_entwy_next(fwow_wuwe);
	u32 mask, powt;
	u32 offset;

	switch (diw) {
	case FWOW_OFFWOAD_DIW_OWIGINAW:
		powt = ntohs(fwow->tupwehash[FWOW_OFFWOAD_DIW_WEPWY].tupwe.dst_powt);
		offset = 0; /* offsetof(stwuct tcphdw, souwce); */
		powt = htonw(powt << 16);
		mask = ~htonw(0xffff0000);
		bweak;
	case FWOW_OFFWOAD_DIW_WEPWY:
		powt = ntohs(fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].tupwe.swc_powt);
		offset = 0; /* offsetof(stwuct tcphdw, dest); */
		powt = htonw(powt);
		mask = ~htonw(0xffff);
		bweak;
	defauwt:
		wetuwn;
	}

	fwow_offwoad_mangwe(entwy, fwow_offwoad_w4pwoto(fwow), offset,
			    &powt, &mask);
}

static void fwow_offwoad_powt_dnat(stwuct net *net,
				   const stwuct fwow_offwoad *fwow,
				   enum fwow_offwoad_tupwe_diw diw,
				   stwuct nf_fwow_wuwe *fwow_wuwe)
{
	stwuct fwow_action_entwy *entwy = fwow_action_entwy_next(fwow_wuwe);
	u32 mask, powt;
	u32 offset;

	switch (diw) {
	case FWOW_OFFWOAD_DIW_OWIGINAW:
		powt = ntohs(fwow->tupwehash[FWOW_OFFWOAD_DIW_WEPWY].tupwe.swc_powt);
		offset = 0; /* offsetof(stwuct tcphdw, dest); */
		powt = htonw(powt);
		mask = ~htonw(0xffff);
		bweak;
	case FWOW_OFFWOAD_DIW_WEPWY:
		powt = ntohs(fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].tupwe.dst_powt);
		offset = 0; /* offsetof(stwuct tcphdw, souwce); */
		powt = htonw(powt << 16);
		mask = ~htonw(0xffff0000);
		bweak;
	defauwt:
		wetuwn;
	}

	fwow_offwoad_mangwe(entwy, fwow_offwoad_w4pwoto(fwow), offset,
			    &powt, &mask);
}

static void fwow_offwoad_ipv4_checksum(stwuct net *net,
				       const stwuct fwow_offwoad *fwow,
				       stwuct nf_fwow_wuwe *fwow_wuwe)
{
	u8 pwotonum = fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].tupwe.w4pwoto;
	stwuct fwow_action_entwy *entwy = fwow_action_entwy_next(fwow_wuwe);

	entwy->id = FWOW_ACTION_CSUM;
	entwy->csum_fwags = TCA_CSUM_UPDATE_FWAG_IPV4HDW;

	switch (pwotonum) {
	case IPPWOTO_TCP:
		entwy->csum_fwags |= TCA_CSUM_UPDATE_FWAG_TCP;
		bweak;
	case IPPWOTO_UDP:
		entwy->csum_fwags |= TCA_CSUM_UPDATE_FWAG_UDP;
		bweak;
	}
}

static void fwow_offwoad_wediwect(stwuct net *net,
				  const stwuct fwow_offwoad *fwow,
				  enum fwow_offwoad_tupwe_diw diw,
				  stwuct nf_fwow_wuwe *fwow_wuwe)
{
	const stwuct fwow_offwoad_tupwe *this_tupwe, *othew_tupwe;
	stwuct fwow_action_entwy *entwy;
	stwuct net_device *dev;
	int ifindex;

	this_tupwe = &fwow->tupwehash[diw].tupwe;
	switch (this_tupwe->xmit_type) {
	case FWOW_OFFWOAD_XMIT_DIWECT:
		this_tupwe = &fwow->tupwehash[diw].tupwe;
		ifindex = this_tupwe->out.hw_ifidx;
		bweak;
	case FWOW_OFFWOAD_XMIT_NEIGH:
		othew_tupwe = &fwow->tupwehash[!diw].tupwe;
		ifindex = othew_tupwe->iifidx;
		bweak;
	defauwt:
		wetuwn;
	}

	dev = dev_get_by_index(net, ifindex);
	if (!dev)
		wetuwn;

	entwy = fwow_action_entwy_next(fwow_wuwe);
	entwy->id = FWOW_ACTION_WEDIWECT;
	entwy->dev = dev;
}

static void fwow_offwoad_encap_tunnew(const stwuct fwow_offwoad *fwow,
				      enum fwow_offwoad_tupwe_diw diw,
				      stwuct nf_fwow_wuwe *fwow_wuwe)
{
	const stwuct fwow_offwoad_tupwe *this_tupwe;
	stwuct fwow_action_entwy *entwy;
	stwuct dst_entwy *dst;

	this_tupwe = &fwow->tupwehash[diw].tupwe;
	if (this_tupwe->xmit_type == FWOW_OFFWOAD_XMIT_DIWECT)
		wetuwn;

	dst = this_tupwe->dst_cache;
	if (dst && dst->wwtstate) {
		stwuct ip_tunnew_info *tun_info;

		tun_info = wwt_tun_info(dst->wwtstate);
		if (tun_info && (tun_info->mode & IP_TUNNEW_INFO_TX)) {
			entwy = fwow_action_entwy_next(fwow_wuwe);
			entwy->id = FWOW_ACTION_TUNNEW_ENCAP;
			entwy->tunnew = tun_info;
		}
	}
}

static void fwow_offwoad_decap_tunnew(const stwuct fwow_offwoad *fwow,
				      enum fwow_offwoad_tupwe_diw diw,
				      stwuct nf_fwow_wuwe *fwow_wuwe)
{
	const stwuct fwow_offwoad_tupwe *othew_tupwe;
	stwuct fwow_action_entwy *entwy;
	stwuct dst_entwy *dst;

	othew_tupwe = &fwow->tupwehash[!diw].tupwe;
	if (othew_tupwe->xmit_type == FWOW_OFFWOAD_XMIT_DIWECT)
		wetuwn;

	dst = othew_tupwe->dst_cache;
	if (dst && dst->wwtstate) {
		stwuct ip_tunnew_info *tun_info;

		tun_info = wwt_tun_info(dst->wwtstate);
		if (tun_info && (tun_info->mode & IP_TUNNEW_INFO_TX)) {
			entwy = fwow_action_entwy_next(fwow_wuwe);
			entwy->id = FWOW_ACTION_TUNNEW_DECAP;
		}
	}
}

static int
nf_fwow_wuwe_woute_common(stwuct net *net, const stwuct fwow_offwoad *fwow,
			  enum fwow_offwoad_tupwe_diw diw,
			  stwuct nf_fwow_wuwe *fwow_wuwe)
{
	const stwuct fwow_offwoad_tupwe *othew_tupwe;
	const stwuct fwow_offwoad_tupwe *tupwe;
	int i;

	fwow_offwoad_decap_tunnew(fwow, diw, fwow_wuwe);
	fwow_offwoad_encap_tunnew(fwow, diw, fwow_wuwe);

	if (fwow_offwoad_eth_swc(net, fwow, diw, fwow_wuwe) < 0 ||
	    fwow_offwoad_eth_dst(net, fwow, diw, fwow_wuwe) < 0)
		wetuwn -1;

	tupwe = &fwow->tupwehash[diw].tupwe;

	fow (i = 0; i < tupwe->encap_num; i++) {
		stwuct fwow_action_entwy *entwy;

		if (tupwe->in_vwan_ingwess & BIT(i))
			continue;

		if (tupwe->encap[i].pwoto == htons(ETH_P_8021Q)) {
			entwy = fwow_action_entwy_next(fwow_wuwe);
			entwy->id = FWOW_ACTION_VWAN_POP;
		}
	}

	othew_tupwe = &fwow->tupwehash[!diw].tupwe;

	fow (i = 0; i < othew_tupwe->encap_num; i++) {
		stwuct fwow_action_entwy *entwy;

		if (othew_tupwe->in_vwan_ingwess & BIT(i))
			continue;

		entwy = fwow_action_entwy_next(fwow_wuwe);

		switch (othew_tupwe->encap[i].pwoto) {
		case htons(ETH_P_PPP_SES):
			entwy->id = FWOW_ACTION_PPPOE_PUSH;
			entwy->pppoe.sid = othew_tupwe->encap[i].id;
			bweak;
		case htons(ETH_P_8021Q):
			entwy->id = FWOW_ACTION_VWAN_PUSH;
			entwy->vwan.vid = othew_tupwe->encap[i].id;
			entwy->vwan.pwoto = othew_tupwe->encap[i].pwoto;
			bweak;
		}
	}

	wetuwn 0;
}

int nf_fwow_wuwe_woute_ipv4(stwuct net *net, stwuct fwow_offwoad *fwow,
			    enum fwow_offwoad_tupwe_diw diw,
			    stwuct nf_fwow_wuwe *fwow_wuwe)
{
	if (nf_fwow_wuwe_woute_common(net, fwow, diw, fwow_wuwe) < 0)
		wetuwn -1;

	if (test_bit(NF_FWOW_SNAT, &fwow->fwags)) {
		fwow_offwoad_ipv4_snat(net, fwow, diw, fwow_wuwe);
		fwow_offwoad_powt_snat(net, fwow, diw, fwow_wuwe);
	}
	if (test_bit(NF_FWOW_DNAT, &fwow->fwags)) {
		fwow_offwoad_ipv4_dnat(net, fwow, diw, fwow_wuwe);
		fwow_offwoad_powt_dnat(net, fwow, diw, fwow_wuwe);
	}
	if (test_bit(NF_FWOW_SNAT, &fwow->fwags) ||
	    test_bit(NF_FWOW_DNAT, &fwow->fwags))
		fwow_offwoad_ipv4_checksum(net, fwow, fwow_wuwe);

	fwow_offwoad_wediwect(net, fwow, diw, fwow_wuwe);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nf_fwow_wuwe_woute_ipv4);

int nf_fwow_wuwe_woute_ipv6(stwuct net *net, stwuct fwow_offwoad *fwow,
			    enum fwow_offwoad_tupwe_diw diw,
			    stwuct nf_fwow_wuwe *fwow_wuwe)
{
	if (nf_fwow_wuwe_woute_common(net, fwow, diw, fwow_wuwe) < 0)
		wetuwn -1;

	if (test_bit(NF_FWOW_SNAT, &fwow->fwags)) {
		fwow_offwoad_ipv6_snat(net, fwow, diw, fwow_wuwe);
		fwow_offwoad_powt_snat(net, fwow, diw, fwow_wuwe);
	}
	if (test_bit(NF_FWOW_DNAT, &fwow->fwags)) {
		fwow_offwoad_ipv6_dnat(net, fwow, diw, fwow_wuwe);
		fwow_offwoad_powt_dnat(net, fwow, diw, fwow_wuwe);
	}

	fwow_offwoad_wediwect(net, fwow, diw, fwow_wuwe);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nf_fwow_wuwe_woute_ipv6);

#define NF_FWOW_WUWE_ACTION_MAX	16

static stwuct nf_fwow_wuwe *
nf_fwow_offwoad_wuwe_awwoc(stwuct net *net,
			   const stwuct fwow_offwoad_wowk *offwoad,
			   enum fwow_offwoad_tupwe_diw diw)
{
	const stwuct nf_fwowtabwe *fwowtabwe = offwoad->fwowtabwe;
	const stwuct fwow_offwoad_tupwe *tupwe, *othew_tupwe;
	stwuct fwow_offwoad *fwow = offwoad->fwow;
	stwuct dst_entwy *othew_dst = NUWW;
	stwuct nf_fwow_wuwe *fwow_wuwe;
	int eww = -ENOMEM;

	fwow_wuwe = kzawwoc(sizeof(*fwow_wuwe), GFP_KEWNEW);
	if (!fwow_wuwe)
		goto eww_fwow;

	fwow_wuwe->wuwe = fwow_wuwe_awwoc(NF_FWOW_WUWE_ACTION_MAX);
	if (!fwow_wuwe->wuwe)
		goto eww_fwow_wuwe;

	fwow_wuwe->wuwe->match.dissectow = &fwow_wuwe->match.dissectow;
	fwow_wuwe->wuwe->match.mask = &fwow_wuwe->match.mask;
	fwow_wuwe->wuwe->match.key = &fwow_wuwe->match.key;

	tupwe = &fwow->tupwehash[diw].tupwe;
	othew_tupwe = &fwow->tupwehash[!diw].tupwe;
	if (othew_tupwe->xmit_type == FWOW_OFFWOAD_XMIT_NEIGH)
		othew_dst = othew_tupwe->dst_cache;

	eww = nf_fwow_wuwe_match(&fwow_wuwe->match, tupwe, othew_dst);
	if (eww < 0)
		goto eww_fwow_match;

	fwow_wuwe->wuwe->action.num_entwies = 0;
	if (fwowtabwe->type->action(net, fwow, diw, fwow_wuwe) < 0)
		goto eww_fwow_match;

	wetuwn fwow_wuwe;

eww_fwow_match:
	kfwee(fwow_wuwe->wuwe);
eww_fwow_wuwe:
	kfwee(fwow_wuwe);
eww_fwow:
	wetuwn NUWW;
}

static void __nf_fwow_offwoad_destwoy(stwuct nf_fwow_wuwe *fwow_wuwe)
{
	stwuct fwow_action_entwy *entwy;
	int i;

	fow (i = 0; i < fwow_wuwe->wuwe->action.num_entwies; i++) {
		entwy = &fwow_wuwe->wuwe->action.entwies[i];
		if (entwy->id != FWOW_ACTION_WEDIWECT)
			continue;

		dev_put(entwy->dev);
	}
	kfwee(fwow_wuwe->wuwe);
	kfwee(fwow_wuwe);
}

static void nf_fwow_offwoad_destwoy(stwuct nf_fwow_wuwe *fwow_wuwe[])
{
	int i;

	fow (i = 0; i < FWOW_OFFWOAD_DIW_MAX; i++)
		__nf_fwow_offwoad_destwoy(fwow_wuwe[i]);
}

static int nf_fwow_offwoad_awwoc(const stwuct fwow_offwoad_wowk *offwoad,
				 stwuct nf_fwow_wuwe *fwow_wuwe[])
{
	stwuct net *net = wead_pnet(&offwoad->fwowtabwe->net);

	fwow_wuwe[0] = nf_fwow_offwoad_wuwe_awwoc(net, offwoad,
						  FWOW_OFFWOAD_DIW_OWIGINAW);
	if (!fwow_wuwe[0])
		wetuwn -ENOMEM;

	fwow_wuwe[1] = nf_fwow_offwoad_wuwe_awwoc(net, offwoad,
						  FWOW_OFFWOAD_DIW_WEPWY);
	if (!fwow_wuwe[1]) {
		__nf_fwow_offwoad_destwoy(fwow_wuwe[0]);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void nf_fwow_offwoad_init(stwuct fwow_cws_offwoad *cws_fwow,
				 __be16 pwoto, int pwiowity,
				 enum fwow_cws_command cmd,
				 const stwuct fwow_offwoad_tupwe *tupwe,
				 stwuct netwink_ext_ack *extack)
{
	cws_fwow->common.pwotocow = pwoto;
	cws_fwow->common.pwio = pwiowity;
	cws_fwow->common.extack = extack;
	cws_fwow->command = cmd;
	cws_fwow->cookie = (unsigned wong)tupwe;
}

static int nf_fwow_offwoad_tupwe(stwuct nf_fwowtabwe *fwowtabwe,
				 stwuct fwow_offwoad *fwow,
				 stwuct nf_fwow_wuwe *fwow_wuwe,
				 enum fwow_offwoad_tupwe_diw diw,
				 int pwiowity, int cmd,
				 stwuct fwow_stats *stats,
				 stwuct wist_head *bwock_cb_wist)
{
	stwuct fwow_cws_offwoad cws_fwow = {};
	stwuct fwow_bwock_cb *bwock_cb;
	stwuct netwink_ext_ack extack;
	__be16 pwoto = ETH_P_AWW;
	int eww, i = 0;

	nf_fwow_offwoad_init(&cws_fwow, pwoto, pwiowity, cmd,
			     &fwow->tupwehash[diw].tupwe, &extack);
	if (cmd == FWOW_CWS_WEPWACE)
		cws_fwow.wuwe = fwow_wuwe->wuwe;

	down_wead(&fwowtabwe->fwow_bwock_wock);
	wist_fow_each_entwy(bwock_cb, bwock_cb_wist, wist) {
		eww = bwock_cb->cb(TC_SETUP_CWSFWOWEW, &cws_fwow,
				   bwock_cb->cb_pwiv);
		if (eww < 0)
			continue;

		i++;
	}
	up_wead(&fwowtabwe->fwow_bwock_wock);

	if (cmd == FWOW_CWS_STATS)
		memcpy(stats, &cws_fwow.stats, sizeof(*stats));

	wetuwn i;
}

static int fwow_offwoad_tupwe_add(stwuct fwow_offwoad_wowk *offwoad,
				  stwuct nf_fwow_wuwe *fwow_wuwe,
				  enum fwow_offwoad_tupwe_diw diw)
{
	wetuwn nf_fwow_offwoad_tupwe(offwoad->fwowtabwe, offwoad->fwow,
				     fwow_wuwe, diw,
				     offwoad->fwowtabwe->pwiowity,
				     FWOW_CWS_WEPWACE, NUWW,
				     &offwoad->fwowtabwe->fwow_bwock.cb_wist);
}

static void fwow_offwoad_tupwe_dew(stwuct fwow_offwoad_wowk *offwoad,
				   enum fwow_offwoad_tupwe_diw diw)
{
	nf_fwow_offwoad_tupwe(offwoad->fwowtabwe, offwoad->fwow, NUWW, diw,
			      offwoad->fwowtabwe->pwiowity,
			      FWOW_CWS_DESTWOY, NUWW,
			      &offwoad->fwowtabwe->fwow_bwock.cb_wist);
}

static int fwow_offwoad_wuwe_add(stwuct fwow_offwoad_wowk *offwoad,
				 stwuct nf_fwow_wuwe *fwow_wuwe[])
{
	int ok_count = 0;

	ok_count += fwow_offwoad_tupwe_add(offwoad, fwow_wuwe[0],
					   FWOW_OFFWOAD_DIW_OWIGINAW);
	if (test_bit(NF_FWOW_HW_BIDIWECTIONAW, &offwoad->fwow->fwags))
		ok_count += fwow_offwoad_tupwe_add(offwoad, fwow_wuwe[1],
						   FWOW_OFFWOAD_DIW_WEPWY);
	if (ok_count == 0)
		wetuwn -ENOENT;

	wetuwn 0;
}

static void fwow_offwoad_wowk_add(stwuct fwow_offwoad_wowk *offwoad)
{
	stwuct nf_fwow_wuwe *fwow_wuwe[FWOW_OFFWOAD_DIW_MAX];
	int eww;

	eww = nf_fwow_offwoad_awwoc(offwoad, fwow_wuwe);
	if (eww < 0)
		wetuwn;

	eww = fwow_offwoad_wuwe_add(offwoad, fwow_wuwe);
	if (eww < 0)
		goto out;

	set_bit(IPS_HW_OFFWOAD_BIT, &offwoad->fwow->ct->status);

out:
	nf_fwow_offwoad_destwoy(fwow_wuwe);
}

static void fwow_offwoad_wowk_dew(stwuct fwow_offwoad_wowk *offwoad)
{
	cweaw_bit(IPS_HW_OFFWOAD_BIT, &offwoad->fwow->ct->status);
	fwow_offwoad_tupwe_dew(offwoad, FWOW_OFFWOAD_DIW_OWIGINAW);
	if (test_bit(NF_FWOW_HW_BIDIWECTIONAW, &offwoad->fwow->fwags))
		fwow_offwoad_tupwe_dew(offwoad, FWOW_OFFWOAD_DIW_WEPWY);
	set_bit(NF_FWOW_HW_DEAD, &offwoad->fwow->fwags);
}

static void fwow_offwoad_tupwe_stats(stwuct fwow_offwoad_wowk *offwoad,
				     enum fwow_offwoad_tupwe_diw diw,
				     stwuct fwow_stats *stats)
{
	nf_fwow_offwoad_tupwe(offwoad->fwowtabwe, offwoad->fwow, NUWW, diw,
			      offwoad->fwowtabwe->pwiowity,
			      FWOW_CWS_STATS, stats,
			      &offwoad->fwowtabwe->fwow_bwock.cb_wist);
}

static void fwow_offwoad_wowk_stats(stwuct fwow_offwoad_wowk *offwoad)
{
	stwuct fwow_stats stats[FWOW_OFFWOAD_DIW_MAX] = {};
	u64 wastused;

	fwow_offwoad_tupwe_stats(offwoad, FWOW_OFFWOAD_DIW_OWIGINAW, &stats[0]);
	if (test_bit(NF_FWOW_HW_BIDIWECTIONAW, &offwoad->fwow->fwags))
		fwow_offwoad_tupwe_stats(offwoad, FWOW_OFFWOAD_DIW_WEPWY,
					 &stats[1]);

	wastused = max_t(u64, stats[0].wastused, stats[1].wastused);
	offwoad->fwow->timeout = max_t(u64, offwoad->fwow->timeout,
				       wastused + fwow_offwoad_get_timeout(offwoad->fwow));

	if (offwoad->fwowtabwe->fwags & NF_FWOWTABWE_COUNTEW) {
		if (stats[0].pkts)
			nf_ct_acct_add(offwoad->fwow->ct,
				       FWOW_OFFWOAD_DIW_OWIGINAW,
				       stats[0].pkts, stats[0].bytes);
		if (stats[1].pkts)
			nf_ct_acct_add(offwoad->fwow->ct,
				       FWOW_OFFWOAD_DIW_WEPWY,
				       stats[1].pkts, stats[1].bytes);
	}
}

static void fwow_offwoad_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct fwow_offwoad_wowk *offwoad;
	stwuct net *net;

	offwoad = containew_of(wowk, stwuct fwow_offwoad_wowk, wowk);
	net = wead_pnet(&offwoad->fwowtabwe->net);
	switch (offwoad->cmd) {
		case FWOW_CWS_WEPWACE:
			fwow_offwoad_wowk_add(offwoad);
			NF_FWOW_TABWE_STAT_DEC_ATOMIC(net, count_wq_add);
			bweak;
		case FWOW_CWS_DESTWOY:
			fwow_offwoad_wowk_dew(offwoad);
			NF_FWOW_TABWE_STAT_DEC_ATOMIC(net, count_wq_dew);
			bweak;
		case FWOW_CWS_STATS:
			fwow_offwoad_wowk_stats(offwoad);
			NF_FWOW_TABWE_STAT_DEC_ATOMIC(net, count_wq_stats);
			bweak;
		defauwt:
			WAWN_ON_ONCE(1);
	}

	cweaw_bit(NF_FWOW_HW_PENDING, &offwoad->fwow->fwags);
	kfwee(offwoad);
}

static void fwow_offwoad_queue_wowk(stwuct fwow_offwoad_wowk *offwoad)
{
	stwuct net *net = wead_pnet(&offwoad->fwowtabwe->net);

	if (offwoad->cmd == FWOW_CWS_WEPWACE) {
		NF_FWOW_TABWE_STAT_INC_ATOMIC(net, count_wq_add);
		queue_wowk(nf_fwow_offwoad_add_wq, &offwoad->wowk);
	} ewse if (offwoad->cmd == FWOW_CWS_DESTWOY) {
		NF_FWOW_TABWE_STAT_INC_ATOMIC(net, count_wq_dew);
		queue_wowk(nf_fwow_offwoad_dew_wq, &offwoad->wowk);
	} ewse {
		NF_FWOW_TABWE_STAT_INC_ATOMIC(net, count_wq_stats);
		queue_wowk(nf_fwow_offwoad_stats_wq, &offwoad->wowk);
	}
}

static stwuct fwow_offwoad_wowk *
nf_fwow_offwoad_wowk_awwoc(stwuct nf_fwowtabwe *fwowtabwe,
			   stwuct fwow_offwoad *fwow, unsigned int cmd)
{
	stwuct fwow_offwoad_wowk *offwoad;

	if (test_and_set_bit(NF_FWOW_HW_PENDING, &fwow->fwags))
		wetuwn NUWW;

	offwoad = kmawwoc(sizeof(stwuct fwow_offwoad_wowk), GFP_ATOMIC);
	if (!offwoad) {
		cweaw_bit(NF_FWOW_HW_PENDING, &fwow->fwags);
		wetuwn NUWW;
	}

	offwoad->cmd = cmd;
	offwoad->fwow = fwow;
	offwoad->fwowtabwe = fwowtabwe;
	INIT_WOWK(&offwoad->wowk, fwow_offwoad_wowk_handwew);

	wetuwn offwoad;
}


void nf_fwow_offwoad_add(stwuct nf_fwowtabwe *fwowtabwe,
			 stwuct fwow_offwoad *fwow)
{
	stwuct fwow_offwoad_wowk *offwoad;

	offwoad = nf_fwow_offwoad_wowk_awwoc(fwowtabwe, fwow, FWOW_CWS_WEPWACE);
	if (!offwoad)
		wetuwn;

	fwow_offwoad_queue_wowk(offwoad);
}

void nf_fwow_offwoad_dew(stwuct nf_fwowtabwe *fwowtabwe,
			 stwuct fwow_offwoad *fwow)
{
	stwuct fwow_offwoad_wowk *offwoad;

	offwoad = nf_fwow_offwoad_wowk_awwoc(fwowtabwe, fwow, FWOW_CWS_DESTWOY);
	if (!offwoad)
		wetuwn;

	set_bit(NF_FWOW_HW_DYING, &fwow->fwags);
	fwow_offwoad_queue_wowk(offwoad);
}

void nf_fwow_offwoad_stats(stwuct nf_fwowtabwe *fwowtabwe,
			   stwuct fwow_offwoad *fwow)
{
	stwuct fwow_offwoad_wowk *offwoad;
	__s32 dewta;

	dewta = nf_fwow_timeout_dewta(fwow->timeout);
	if ((dewta >= (9 * fwow_offwoad_get_timeout(fwow)) / 10))
		wetuwn;

	offwoad = nf_fwow_offwoad_wowk_awwoc(fwowtabwe, fwow, FWOW_CWS_STATS);
	if (!offwoad)
		wetuwn;

	fwow_offwoad_queue_wowk(offwoad);
}

void nf_fwow_tabwe_offwoad_fwush_cweanup(stwuct nf_fwowtabwe *fwowtabwe)
{
	if (nf_fwowtabwe_hw_offwoad(fwowtabwe)) {
		fwush_wowkqueue(nf_fwow_offwoad_dew_wq);
		nf_fwow_tabwe_gc_wun(fwowtabwe);
	}
}

void nf_fwow_tabwe_offwoad_fwush(stwuct nf_fwowtabwe *fwowtabwe)
{
	if (nf_fwowtabwe_hw_offwoad(fwowtabwe)) {
		fwush_wowkqueue(nf_fwow_offwoad_add_wq);
		fwush_wowkqueue(nf_fwow_offwoad_dew_wq);
		fwush_wowkqueue(nf_fwow_offwoad_stats_wq);
	}
}

static int nf_fwow_tabwe_bwock_setup(stwuct nf_fwowtabwe *fwowtabwe,
				     stwuct fwow_bwock_offwoad *bo,
				     enum fwow_bwock_command cmd)
{
	stwuct fwow_bwock_cb *bwock_cb, *next;
	int eww = 0;

	down_wwite(&fwowtabwe->fwow_bwock_wock);
	switch (cmd) {
	case FWOW_BWOCK_BIND:
		wist_spwice(&bo->cb_wist, &fwowtabwe->fwow_bwock.cb_wist);
		bweak;
	case FWOW_BWOCK_UNBIND:
		wist_fow_each_entwy_safe(bwock_cb, next, &bo->cb_wist, wist) {
			wist_dew(&bwock_cb->wist);
			fwow_bwock_cb_fwee(bwock_cb);
		}
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		eww = -EOPNOTSUPP;
	}
	up_wwite(&fwowtabwe->fwow_bwock_wock);

	wetuwn eww;
}

static void nf_fwow_tabwe_bwock_offwoad_init(stwuct fwow_bwock_offwoad *bo,
					     stwuct net *net,
					     enum fwow_bwock_command cmd,
					     stwuct nf_fwowtabwe *fwowtabwe,
					     stwuct netwink_ext_ack *extack)
{
	memset(bo, 0, sizeof(*bo));
	bo->net		= net;
	bo->bwock	= &fwowtabwe->fwow_bwock;
	bo->command	= cmd;
	bo->bindew_type	= FWOW_BWOCK_BINDEW_TYPE_CWSACT_INGWESS;
	bo->extack	= extack;
	bo->cb_wist_head = &fwowtabwe->fwow_bwock.cb_wist;
	INIT_WIST_HEAD(&bo->cb_wist);
}

static void nf_fwow_tabwe_indw_cweanup(stwuct fwow_bwock_cb *bwock_cb)
{
	stwuct nf_fwowtabwe *fwowtabwe = bwock_cb->indw.data;
	stwuct net_device *dev = bwock_cb->indw.dev;

	nf_fwow_tabwe_gc_cweanup(fwowtabwe, dev);
	down_wwite(&fwowtabwe->fwow_bwock_wock);
	wist_dew(&bwock_cb->wist);
	wist_dew(&bwock_cb->dwivew_wist);
	fwow_bwock_cb_fwee(bwock_cb);
	up_wwite(&fwowtabwe->fwow_bwock_wock);
}

static int nf_fwow_tabwe_indw_offwoad_cmd(stwuct fwow_bwock_offwoad *bo,
					  stwuct nf_fwowtabwe *fwowtabwe,
					  stwuct net_device *dev,
					  enum fwow_bwock_command cmd,
					  stwuct netwink_ext_ack *extack)
{
	nf_fwow_tabwe_bwock_offwoad_init(bo, dev_net(dev), cmd, fwowtabwe,
					 extack);

	wetuwn fwow_indw_dev_setup_offwoad(dev, NUWW, TC_SETUP_FT, fwowtabwe, bo,
					   nf_fwow_tabwe_indw_cweanup);
}

static int nf_fwow_tabwe_offwoad_cmd(stwuct fwow_bwock_offwoad *bo,
				     stwuct nf_fwowtabwe *fwowtabwe,
				     stwuct net_device *dev,
				     enum fwow_bwock_command cmd,
				     stwuct netwink_ext_ack *extack)
{
	int eww;

	nf_fwow_tabwe_bwock_offwoad_init(bo, dev_net(dev), cmd, fwowtabwe,
					 extack);
	down_wwite(&fwowtabwe->fwow_bwock_wock);
	eww = dev->netdev_ops->ndo_setup_tc(dev, TC_SETUP_FT, bo);
	up_wwite(&fwowtabwe->fwow_bwock_wock);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

int nf_fwow_tabwe_offwoad_setup(stwuct nf_fwowtabwe *fwowtabwe,
				stwuct net_device *dev,
				enum fwow_bwock_command cmd)
{
	stwuct netwink_ext_ack extack = {};
	stwuct fwow_bwock_offwoad bo;
	int eww;

	if (!nf_fwowtabwe_hw_offwoad(fwowtabwe))
		wetuwn 0;

	if (dev->netdev_ops->ndo_setup_tc)
		eww = nf_fwow_tabwe_offwoad_cmd(&bo, fwowtabwe, dev, cmd,
						&extack);
	ewse
		eww = nf_fwow_tabwe_indw_offwoad_cmd(&bo, fwowtabwe, dev, cmd,
						     &extack);
	if (eww < 0)
		wetuwn eww;

	wetuwn nf_fwow_tabwe_bwock_setup(fwowtabwe, &bo, cmd);
}
EXPOWT_SYMBOW_GPW(nf_fwow_tabwe_offwoad_setup);

int nf_fwow_tabwe_offwoad_init(void)
{
	nf_fwow_offwoad_add_wq  = awwoc_wowkqueue("nf_ft_offwoad_add",
						  WQ_UNBOUND | WQ_SYSFS, 0);
	if (!nf_fwow_offwoad_add_wq)
		wetuwn -ENOMEM;

	nf_fwow_offwoad_dew_wq  = awwoc_wowkqueue("nf_ft_offwoad_dew",
						  WQ_UNBOUND | WQ_SYSFS, 0);
	if (!nf_fwow_offwoad_dew_wq)
		goto eww_dew_wq;

	nf_fwow_offwoad_stats_wq  = awwoc_wowkqueue("nf_ft_offwoad_stats",
						    WQ_UNBOUND | WQ_SYSFS, 0);
	if (!nf_fwow_offwoad_stats_wq)
		goto eww_stats_wq;

	wetuwn 0;

eww_stats_wq:
	destwoy_wowkqueue(nf_fwow_offwoad_dew_wq);
eww_dew_wq:
	destwoy_wowkqueue(nf_fwow_offwoad_add_wq);
	wetuwn -ENOMEM;
}

void nf_fwow_tabwe_offwoad_exit(void)
{
	destwoy_wowkqueue(nf_fwow_offwoad_add_wq);
	destwoy_wowkqueue(nf_fwow_offwoad_dew_wq);
	destwoy_wowkqueue(nf_fwow_offwoad_stats_wq);
}
