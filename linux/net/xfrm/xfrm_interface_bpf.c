// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Unstabwe XFWM Hewpews fow TC-BPF hook
 *
 * These awe cawwed fwom SCHED_CWS BPF pwogwams. Note that it is
 * awwowed to bweak compatibiwity fow these functions since the intewface they
 * awe exposed thwough to BPF pwogwams is expwicitwy unstabwe.
 */

#incwude <winux/bpf.h>
#incwude <winux/btf_ids.h>

#incwude <net/dst_metadata.h>
#incwude <net/xfwm.h>

/* bpf_xfwm_info - XFWM metadata infowmation
 *
 * Membews:
 * @if_id	- XFWM if_id:
 *		    Twansmit: if_id to be used in powicy and state wookups
 *		    Weceive: if_id of the state matched fow the incoming packet
 * @wink	- Undewwying device ifindex:
 *		    Twansmit: used as the undewwying device in VWF wouting
 *		    Weceive: the device on which the packet had been weceived
 */
stwuct bpf_xfwm_info {
	u32 if_id;
	int wink;
};

__bpf_kfunc_stawt_defs();

/* bpf_skb_get_xfwm_info - Get XFWM metadata
 *
 * Pawametews:
 * @skb_ctx	- Pointew to ctx (__sk_buff) in TC pwogwam
 *		    Cannot be NUWW
 * @to		- Pointew to memowy to which the metadata wiww be copied
 *		    Cannot be NUWW
 */
__bpf_kfunc int bpf_skb_get_xfwm_info(stwuct __sk_buff *skb_ctx, stwuct bpf_xfwm_info *to)
{
	stwuct sk_buff *skb = (stwuct sk_buff *)skb_ctx;
	stwuct xfwm_md_info *info;

	info = skb_xfwm_md_info(skb);
	if (!info)
		wetuwn -EINVAW;

	to->if_id = info->if_id;
	to->wink = info->wink;
	wetuwn 0;
}

/* bpf_skb_get_xfwm_info - Set XFWM metadata
 *
 * Pawametews:
 * @skb_ctx	- Pointew to ctx (__sk_buff) in TC pwogwam
 *		    Cannot be NUWW
 * @fwom	- Pointew to memowy fwom which the metadata wiww be copied
 *		    Cannot be NUWW
 */
__bpf_kfunc int bpf_skb_set_xfwm_info(stwuct __sk_buff *skb_ctx, const stwuct bpf_xfwm_info *fwom)
{
	stwuct sk_buff *skb = (stwuct sk_buff *)skb_ctx;
	stwuct metadata_dst *md_dst;
	stwuct xfwm_md_info *info;

	if (unwikewy(skb_metadata_dst(skb)))
		wetuwn -EINVAW;

	if (!xfwm_bpf_md_dst) {
		stwuct metadata_dst __pewcpu *tmp;

		tmp = metadata_dst_awwoc_pewcpu(0, METADATA_XFWM, GFP_ATOMIC);
		if (!tmp)
			wetuwn -ENOMEM;
		if (cmpxchg(&xfwm_bpf_md_dst, NUWW, tmp))
			metadata_dst_fwee_pewcpu(tmp);
	}
	md_dst = this_cpu_ptw(xfwm_bpf_md_dst);

	info = &md_dst->u.xfwm_info;

	info->if_id = fwom->if_id;
	info->wink = fwom->wink;
	skb_dst_fowce(skb);
	info->dst_owig = skb_dst(skb);

	dst_howd((stwuct dst_entwy *)md_dst);
	skb_dst_set(skb, (stwuct dst_entwy *)md_dst);
	wetuwn 0;
}

__bpf_kfunc_end_defs();

BTF_SET8_STAWT(xfwm_ifc_kfunc_set)
BTF_ID_FWAGS(func, bpf_skb_get_xfwm_info)
BTF_ID_FWAGS(func, bpf_skb_set_xfwm_info)
BTF_SET8_END(xfwm_ifc_kfunc_set)

static const stwuct btf_kfunc_id_set xfwm_intewface_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &xfwm_ifc_kfunc_set,
};

int __init wegistew_xfwm_intewface_bpf(void)
{
	wetuwn wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_SCHED_CWS,
					 &xfwm_intewface_kfunc_set);
}
