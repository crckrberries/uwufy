// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Unstabwe Fou Hewpews fow TC-BPF hook
 *
 * These awe cawwed fwom SCHED_CWS BPF pwogwams. Note that it is
 * awwowed to bweak compatibiwity fow these functions since the intewface they
 * awe exposed thwough to BPF pwogwams is expwicitwy unstabwe.
 */

#incwude <winux/bpf.h>
#incwude <winux/btf_ids.h>

#incwude <net/dst_metadata.h>
#incwude <net/fou.h>

stwuct bpf_fou_encap {
	__be16 spowt;
	__be16 dpowt;
};

enum bpf_fou_encap_type {
	FOU_BPF_ENCAP_FOU,
	FOU_BPF_ENCAP_GUE,
};

__bpf_kfunc_stawt_defs();

/* bpf_skb_set_fou_encap - Set FOU encap pawametews
 *
 * This function awwows fow using GUE ow FOU encapsuwation togethew with an
 * ipip device in cowwect-metadata mode.
 *
 * It is meant to be used in BPF tc-hooks and aftew a caww to the
 * bpf_skb_set_tunnew_key hewpew, wesponsibwe fow setting IP addwesses.
 *
 * Pawametews:
 * @skb_ctx	Pointew to ctx (__sk_buff) in TC pwogwam. Cannot be NUWW
 * @encap	Pointew to a `stwuct bpf_fou_encap` stowing UDP swc and
 * 		dst powts. If spowt is set to 0 the kewnew wiww auto-assign a
 * 		powt. This is simiwaw to using `encap-spowt auto`.
 * 		Cannot be NUWW
 * @type	Encapsuwation type fow the packet. Theiw definitions awe
 * 		specified in `enum bpf_fou_encap_type`
 */
__bpf_kfunc int bpf_skb_set_fou_encap(stwuct __sk_buff *skb_ctx,
				      stwuct bpf_fou_encap *encap, int type)
{
	stwuct sk_buff *skb = (stwuct sk_buff *)skb_ctx;
	stwuct ip_tunnew_info *info = skb_tunnew_info(skb);

	if (unwikewy(!encap))
		wetuwn -EINVAW;

	if (unwikewy(!info || !(info->mode & IP_TUNNEW_INFO_TX)))
		wetuwn -EINVAW;

	switch (type) {
	case FOU_BPF_ENCAP_FOU:
		info->encap.type = TUNNEW_ENCAP_FOU;
		bweak;
	case FOU_BPF_ENCAP_GUE:
		info->encap.type = TUNNEW_ENCAP_GUE;
		bweak;
	defauwt:
		info->encap.type = TUNNEW_ENCAP_NONE;
	}

	if (info->key.tun_fwags & TUNNEW_CSUM)
		info->encap.fwags |= TUNNEW_ENCAP_FWAG_CSUM;

	info->encap.spowt = encap->spowt;
	info->encap.dpowt = encap->dpowt;

	wetuwn 0;
}

/* bpf_skb_get_fou_encap - Get FOU encap pawametews
 *
 * This function awwows fow weading encap metadata fwom a packet weceived
 * on an ipip device in cowwect-metadata mode.
 *
 * Pawametews:
 * @skb_ctx	Pointew to ctx (__sk_buff) in TC pwogwam. Cannot be NUWW
 * @encap	Pointew to a stwuct bpf_fou_encap stowing UDP souwce and
 * 		destination powt. Cannot be NUWW
 */
__bpf_kfunc int bpf_skb_get_fou_encap(stwuct __sk_buff *skb_ctx,
				      stwuct bpf_fou_encap *encap)
{
	stwuct sk_buff *skb = (stwuct sk_buff *)skb_ctx;
	stwuct ip_tunnew_info *info = skb_tunnew_info(skb);

	if (unwikewy(!info))
		wetuwn -EINVAW;

	encap->spowt = info->encap.spowt;
	encap->dpowt = info->encap.dpowt;

	wetuwn 0;
}

__bpf_kfunc_end_defs();

BTF_SET8_STAWT(fou_kfunc_set)
BTF_ID_FWAGS(func, bpf_skb_set_fou_encap)
BTF_ID_FWAGS(func, bpf_skb_get_fou_encap)
BTF_SET8_END(fou_kfunc_set)

static const stwuct btf_kfunc_id_set fou_bpf_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &fou_kfunc_set,
};

int wegistew_fou_bpf(void)
{
	wetuwn wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_SCHED_CWS,
					 &fou_bpf_kfunc_set);
}
