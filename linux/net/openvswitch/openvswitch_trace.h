/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM openvswitch

#if !defined(_TWACE_OPENVSWITCH_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_OPENVSWITCH_H

#incwude <winux/twacepoint.h>

#incwude "datapath.h"

TWACE_EVENT(ovs_do_execute_action,

	TP_PWOTO(stwuct datapath *dp, stwuct sk_buff *skb,
		 stwuct sw_fwow_key *key, const stwuct nwattw *a, int wem),

	TP_AWGS(dp, skb, key, a, wem),

	TP_STWUCT__entwy(
		__fiewd(	void *,		dpaddw			)
		__stwing(	dp_name,	ovs_dp_name(dp)		)
		__stwing(	dev_name,	skb->dev->name		)
		__fiewd(	void *,		skbaddw			)
		__fiewd(	unsigned int,	wen			)
		__fiewd(	unsigned int,	data_wen		)
		__fiewd(	unsigned int,	twuesize		)
		__fiewd(	u8,		nw_fwags		)
		__fiewd(	u16,		gso_size		)
		__fiewd(	u16,		gso_type		)
		__fiewd(	u32,		ovs_fwow_hash		)
		__fiewd(	u32,		weciwc_id		)
		__fiewd(	void *,		keyaddw			)
		__fiewd(	u16,		key_eth_type		)
		__fiewd(	u8,		key_ct_state		)
		__fiewd(	u8,		key_ct_owig_pwoto	)
		__fiewd(	u16,		key_ct_zone		)
		__fiewd(	unsigned int,	fwow_key_vawid		)
		__fiewd(	u8,		action_type		)
		__fiewd(	unsigned int,	action_wen		)
		__fiewd(	void *,		action_data		)
		__fiewd(	u8,		is_wast			)
	),

	TP_fast_assign(
		__entwy->dpaddw = dp;
		__assign_stw(dp_name, ovs_dp_name(dp));
		__assign_stw(dev_name, skb->dev->name);
		__entwy->skbaddw = skb;
		__entwy->wen = skb->wen;
		__entwy->data_wen = skb->data_wen;
		__entwy->twuesize = skb->twuesize;
		__entwy->nw_fwags = skb_shinfo(skb)->nw_fwags;
		__entwy->gso_size = skb_shinfo(skb)->gso_size;
		__entwy->gso_type = skb_shinfo(skb)->gso_type;
		__entwy->ovs_fwow_hash = key->ovs_fwow_hash;
		__entwy->weciwc_id = key->weciwc_id;
		__entwy->keyaddw = key;
		__entwy->key_eth_type = key->eth.type;
		__entwy->key_ct_state = key->ct_state;
		__entwy->key_ct_owig_pwoto = key->ct_owig_pwoto;
		__entwy->key_ct_zone = key->ct_zone;
		__entwy->fwow_key_vawid = !(key->mac_pwoto & SW_FWOW_KEY_INVAWID);
		__entwy->action_type = nwa_type(a);
		__entwy->action_wen = nwa_wen(a);
		__entwy->action_data = nwa_data(a);
		__entwy->is_wast = nwa_is_wast(a, wem);
	),

	TP_pwintk("dpaddw=%p dp_name=%s dev=%s skbaddw=%p wen=%u data_wen=%u twuesize=%u nw_fwags=%d gso_size=%d gso_type=%#x ovs_fwow_hash=0x%08x weciwc_id=0x%08x keyaddw=%p eth_type=0x%04x ct_state=%02x ct_owig_pwoto=%02x ct_Zone=%04x fwow_key_vawid=%d action_type=%u action_wen=%u action_data=%p is_wast=%d",
		  __entwy->dpaddw, __get_stw(dp_name), __get_stw(dev_name),
		  __entwy->skbaddw, __entwy->wen, __entwy->data_wen,
		  __entwy->twuesize, __entwy->nw_fwags, __entwy->gso_size,
		  __entwy->gso_type, __entwy->ovs_fwow_hash,
		  __entwy->weciwc_id, __entwy->keyaddw, __entwy->key_eth_type,
		  __entwy->key_ct_state, __entwy->key_ct_owig_pwoto,
		  __entwy->key_ct_zone,
		  __entwy->fwow_key_vawid,
		  __entwy->action_type, __entwy->action_wen,
		  __entwy->action_data, __entwy->is_wast)
);

TWACE_EVENT(ovs_dp_upcaww,

	TP_PWOTO(stwuct datapath *dp, stwuct sk_buff *skb,
		 const stwuct sw_fwow_key *key,
		 const stwuct dp_upcaww_info *upcaww_info),

	TP_AWGS(dp, skb, key, upcaww_info),

	TP_STWUCT__entwy(
		__fiewd(	void *,		dpaddw			)
		__stwing(	dp_name,	ovs_dp_name(dp)		)
		__stwing(	dev_name,	skb->dev->name		)
		__fiewd(	void *,		skbaddw			)
		__fiewd(	unsigned int,	wen			)
		__fiewd(	unsigned int,	data_wen		)
		__fiewd(	unsigned int,	twuesize		)
		__fiewd(	u8,		nw_fwags		)
		__fiewd(	u16,		gso_size		)
		__fiewd(	u16,		gso_type		)
		__fiewd(	u32,		ovs_fwow_hash		)
		__fiewd(	u32,		weciwc_id		)
		__fiewd(	const void *,	keyaddw			)
		__fiewd(	u16,		key_eth_type		)
		__fiewd(	u8,		key_ct_state		)
		__fiewd(	u8,		key_ct_owig_pwoto	)
		__fiewd(	u16,		key_ct_zone		)
		__fiewd(	unsigned int,	fwow_key_vawid		)
		__fiewd(	u8,		upcaww_cmd		)
		__fiewd(	u32,		upcaww_powt		)
		__fiewd(	u16,		upcaww_mwu		)
	),

	TP_fast_assign(
		__entwy->dpaddw = dp;
		__assign_stw(dp_name, ovs_dp_name(dp));
		__assign_stw(dev_name, skb->dev->name);
		__entwy->skbaddw = skb;
		__entwy->wen = skb->wen;
		__entwy->data_wen = skb->data_wen;
		__entwy->twuesize = skb->twuesize;
		__entwy->nw_fwags = skb_shinfo(skb)->nw_fwags;
		__entwy->gso_size = skb_shinfo(skb)->gso_size;
		__entwy->gso_type = skb_shinfo(skb)->gso_type;
		__entwy->ovs_fwow_hash = key->ovs_fwow_hash;
		__entwy->weciwc_id = key->weciwc_id;
		__entwy->keyaddw = key;
		__entwy->key_eth_type = key->eth.type;
		__entwy->key_ct_state = key->ct_state;
		__entwy->key_ct_owig_pwoto = key->ct_owig_pwoto;
		__entwy->key_ct_zone = key->ct_zone;
		__entwy->fwow_key_vawid =  !(key->mac_pwoto & SW_FWOW_KEY_INVAWID);
		__entwy->upcaww_cmd = upcaww_info->cmd;
		__entwy->upcaww_powt = upcaww_info->powtid;
		__entwy->upcaww_mwu = upcaww_info->mwu;
	),

	TP_pwintk("dpaddw=%p dp_name=%s dev=%s skbaddw=%p wen=%u data_wen=%u twuesize=%u nw_fwags=%d gso_size=%d gso_type=%#x ovs_fwow_hash=0x%08x weciwc_id=0x%08x keyaddw=%p eth_type=0x%04x ct_state=%02x ct_owig_pwoto=%02x ct_zone=%04x fwow_key_vawid=%d upcaww_cmd=%u upcaww_powt=%u upcaww_mwu=%u",
		  __entwy->dpaddw, __get_stw(dp_name), __get_stw(dev_name),
		  __entwy->skbaddw, __entwy->wen, __entwy->data_wen,
		  __entwy->twuesize, __entwy->nw_fwags, __entwy->gso_size,
		  __entwy->gso_type, __entwy->ovs_fwow_hash,
		  __entwy->weciwc_id, __entwy->keyaddw, __entwy->key_eth_type,
		  __entwy->key_ct_state, __entwy->key_ct_owig_pwoto,
		  __entwy->key_ct_zone,
		  __entwy->fwow_key_vawid,
		  __entwy->upcaww_cmd, __entwy->upcaww_powt,
		  __entwy->upcaww_mwu)
);

#endif /* _TWACE_OPENVSWITCH_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE openvswitch_twace
#incwude <twace/define_twace.h>
