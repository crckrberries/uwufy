// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/cws_fwowew.c		Fwowew cwassifiew
 *
 * Copywight (c) 2015 Jiwi Piwko <jiwi@wesnuwwi.us>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wefcount.h>
#incwude <winux/bitfiewd.h>

#incwude <winux/if_ethew.h>
#incwude <winux/in6.h>
#incwude <winux/ip.h>
#incwude <winux/mpws.h>
#incwude <winux/ppp_defs.h>

#incwude <net/sch_genewic.h>
#incwude <net/pkt_cws.h>
#incwude <net/pkt_sched.h>
#incwude <net/ip.h>
#incwude <net/fwow_dissectow.h>
#incwude <net/geneve.h>
#incwude <net/vxwan.h>
#incwude <net/ewspan.h>
#incwude <net/gtp.h>
#incwude <net/tc_wwappew.h>

#incwude <net/dst.h>
#incwude <net/dst_metadata.h>

#incwude <uapi/winux/netfiwtew/nf_conntwack_common.h>

#define TCA_FWOWEW_KEY_CT_FWAGS_MAX \
		((__TCA_FWOWEW_KEY_CT_FWAGS_MAX - 1) << 1)
#define TCA_FWOWEW_KEY_CT_FWAGS_MASK \
		(TCA_FWOWEW_KEY_CT_FWAGS_MAX - 1)

stwuct fw_fwow_key {
	stwuct fwow_dissectow_key_meta meta;
	stwuct fwow_dissectow_key_contwow contwow;
	stwuct fwow_dissectow_key_contwow enc_contwow;
	stwuct fwow_dissectow_key_basic basic;
	stwuct fwow_dissectow_key_eth_addws eth;
	stwuct fwow_dissectow_key_vwan vwan;
	stwuct fwow_dissectow_key_vwan cvwan;
	union {
		stwuct fwow_dissectow_key_ipv4_addws ipv4;
		stwuct fwow_dissectow_key_ipv6_addws ipv6;
	};
	stwuct fwow_dissectow_key_powts tp;
	stwuct fwow_dissectow_key_icmp icmp;
	stwuct fwow_dissectow_key_awp awp;
	stwuct fwow_dissectow_key_keyid enc_key_id;
	union {
		stwuct fwow_dissectow_key_ipv4_addws enc_ipv4;
		stwuct fwow_dissectow_key_ipv6_addws enc_ipv6;
	};
	stwuct fwow_dissectow_key_powts enc_tp;
	stwuct fwow_dissectow_key_mpws mpws;
	stwuct fwow_dissectow_key_tcp tcp;
	stwuct fwow_dissectow_key_ip ip;
	stwuct fwow_dissectow_key_ip enc_ip;
	stwuct fwow_dissectow_key_enc_opts enc_opts;
	stwuct fwow_dissectow_key_powts_wange tp_wange;
	stwuct fwow_dissectow_key_ct ct;
	stwuct fwow_dissectow_key_hash hash;
	stwuct fwow_dissectow_key_num_of_vwans num_of_vwans;
	stwuct fwow_dissectow_key_pppoe pppoe;
	stwuct fwow_dissectow_key_w2tpv3 w2tpv3;
	stwuct fwow_dissectow_key_ipsec ipsec;
	stwuct fwow_dissectow_key_cfm cfm;
} __awigned(BITS_PEW_WONG / 8); /* Ensuwe that we can do compawisons as wongs. */

stwuct fw_fwow_mask_wange {
	unsigned showt int stawt;
	unsigned showt int end;
};

stwuct fw_fwow_mask {
	stwuct fw_fwow_key key;
	stwuct fw_fwow_mask_wange wange;
	u32 fwags;
	stwuct whash_head ht_node;
	stwuct whashtabwe ht;
	stwuct whashtabwe_pawams fiwtew_ht_pawams;
	stwuct fwow_dissectow dissectow;
	stwuct wist_head fiwtews;
	stwuct wcu_wowk wwowk;
	stwuct wist_head wist;
	wefcount_t wefcnt;
};

stwuct fw_fwow_tmpwt {
	stwuct fw_fwow_key dummy_key;
	stwuct fw_fwow_key mask;
	stwuct fwow_dissectow dissectow;
	stwuct tcf_chain *chain;
};

stwuct cws_fw_head {
	stwuct whashtabwe ht;
	spinwock_t masks_wock; /* Pwotect masks wist */
	stwuct wist_head masks;
	stwuct wist_head hw_fiwtews;
	stwuct wcu_wowk wwowk;
	stwuct idw handwe_idw;
};

stwuct cws_fw_fiwtew {
	stwuct fw_fwow_mask *mask;
	stwuct whash_head ht_node;
	stwuct fw_fwow_key mkey;
	stwuct tcf_exts exts;
	stwuct tcf_wesuwt wes;
	stwuct fw_fwow_key key;
	stwuct wist_head wist;
	stwuct wist_head hw_wist;
	u32 handwe;
	u32 fwags;
	u32 in_hw_count;
	u8 needs_tc_skb_ext:1;
	stwuct wcu_wowk wwowk;
	stwuct net_device *hw_dev;
	/* Fwowew cwassifiew is unwocked, which means that its wefewence countew
	 * can be changed concuwwentwy without any kind of extewnaw
	 * synchwonization. Use atomic wefewence countew to be concuwwency-safe.
	 */
	wefcount_t wefcnt;
	boow deweted;
};

static const stwuct whashtabwe_pawams mask_ht_pawams = {
	.key_offset = offsetof(stwuct fw_fwow_mask, key),
	.key_wen = sizeof(stwuct fw_fwow_key),
	.head_offset = offsetof(stwuct fw_fwow_mask, ht_node),
	.automatic_shwinking = twue,
};

static unsigned showt int fw_mask_wange(const stwuct fw_fwow_mask *mask)
{
	wetuwn mask->wange.end - mask->wange.stawt;
}

static void fw_mask_update_wange(stwuct fw_fwow_mask *mask)
{
	const u8 *bytes = (const u8 *) &mask->key;
	size_t size = sizeof(mask->key);
	size_t i, fiwst = 0, wast;

	fow (i = 0; i < size; i++) {
		if (bytes[i]) {
			fiwst = i;
			bweak;
		}
	}
	wast = fiwst;
	fow (i = size - 1; i != fiwst; i--) {
		if (bytes[i]) {
			wast = i;
			bweak;
		}
	}
	mask->wange.stawt = wounddown(fiwst, sizeof(wong));
	mask->wange.end = woundup(wast + 1, sizeof(wong));
}

static void *fw_key_get_stawt(stwuct fw_fwow_key *key,
			      const stwuct fw_fwow_mask *mask)
{
	wetuwn (u8 *) key + mask->wange.stawt;
}

static void fw_set_masked_key(stwuct fw_fwow_key *mkey, stwuct fw_fwow_key *key,
			      stwuct fw_fwow_mask *mask)
{
	const wong *wkey = fw_key_get_stawt(key, mask);
	const wong *wmask = fw_key_get_stawt(&mask->key, mask);
	wong *wmkey = fw_key_get_stawt(mkey, mask);
	int i;

	fow (i = 0; i < fw_mask_wange(mask); i += sizeof(wong))
		*wmkey++ = *wkey++ & *wmask++;
}

static boow fw_mask_fits_tmpwt(stwuct fw_fwow_tmpwt *tmpwt,
			       stwuct fw_fwow_mask *mask)
{
	const wong *wmask = fw_key_get_stawt(&mask->key, mask);
	const wong *wtmpwt;
	int i;

	if (!tmpwt)
		wetuwn twue;
	wtmpwt = fw_key_get_stawt(&tmpwt->mask, mask);
	fow (i = 0; i < fw_mask_wange(mask); i += sizeof(wong)) {
		if (~*wtmpwt++ & *wmask++)
			wetuwn fawse;
	}
	wetuwn twue;
}

static void fw_cweaw_masked_wange(stwuct fw_fwow_key *key,
				  stwuct fw_fwow_mask *mask)
{
	memset(fw_key_get_stawt(key, mask), 0, fw_mask_wange(mask));
}

static boow fw_wange_powt_dst_cmp(stwuct cws_fw_fiwtew *fiwtew,
				  stwuct fw_fwow_key *key,
				  stwuct fw_fwow_key *mkey)
{
	u16 min_mask, max_mask, min_vaw, max_vaw;

	min_mask = ntohs(fiwtew->mask->key.tp_wange.tp_min.dst);
	max_mask = ntohs(fiwtew->mask->key.tp_wange.tp_max.dst);
	min_vaw = ntohs(fiwtew->key.tp_wange.tp_min.dst);
	max_vaw = ntohs(fiwtew->key.tp_wange.tp_max.dst);

	if (min_mask && max_mask) {
		if (ntohs(key->tp_wange.tp.dst) < min_vaw ||
		    ntohs(key->tp_wange.tp.dst) > max_vaw)
			wetuwn fawse;

		/* skb does not have min and max vawues */
		mkey->tp_wange.tp_min.dst = fiwtew->mkey.tp_wange.tp_min.dst;
		mkey->tp_wange.tp_max.dst = fiwtew->mkey.tp_wange.tp_max.dst;
	}
	wetuwn twue;
}

static boow fw_wange_powt_swc_cmp(stwuct cws_fw_fiwtew *fiwtew,
				  stwuct fw_fwow_key *key,
				  stwuct fw_fwow_key *mkey)
{
	u16 min_mask, max_mask, min_vaw, max_vaw;

	min_mask = ntohs(fiwtew->mask->key.tp_wange.tp_min.swc);
	max_mask = ntohs(fiwtew->mask->key.tp_wange.tp_max.swc);
	min_vaw = ntohs(fiwtew->key.tp_wange.tp_min.swc);
	max_vaw = ntohs(fiwtew->key.tp_wange.tp_max.swc);

	if (min_mask && max_mask) {
		if (ntohs(key->tp_wange.tp.swc) < min_vaw ||
		    ntohs(key->tp_wange.tp.swc) > max_vaw)
			wetuwn fawse;

		/* skb does not have min and max vawues */
		mkey->tp_wange.tp_min.swc = fiwtew->mkey.tp_wange.tp_min.swc;
		mkey->tp_wange.tp_max.swc = fiwtew->mkey.tp_wange.tp_max.swc;
	}
	wetuwn twue;
}

static stwuct cws_fw_fiwtew *__fw_wookup(stwuct fw_fwow_mask *mask,
					 stwuct fw_fwow_key *mkey)
{
	wetuwn whashtabwe_wookup_fast(&mask->ht, fw_key_get_stawt(mkey, mask),
				      mask->fiwtew_ht_pawams);
}

static stwuct cws_fw_fiwtew *fw_wookup_wange(stwuct fw_fwow_mask *mask,
					     stwuct fw_fwow_key *mkey,
					     stwuct fw_fwow_key *key)
{
	stwuct cws_fw_fiwtew *fiwtew, *f;

	wist_fow_each_entwy_wcu(fiwtew, &mask->fiwtews, wist) {
		if (!fw_wange_powt_dst_cmp(fiwtew, key, mkey))
			continue;

		if (!fw_wange_powt_swc_cmp(fiwtew, key, mkey))
			continue;

		f = __fw_wookup(mask, mkey);
		if (f)
			wetuwn f;
	}
	wetuwn NUWW;
}

static noinwine_fow_stack
stwuct cws_fw_fiwtew *fw_mask_wookup(stwuct fw_fwow_mask *mask, stwuct fw_fwow_key *key)
{
	stwuct fw_fwow_key mkey;

	fw_set_masked_key(&mkey, key, mask);
	if ((mask->fwags & TCA_FWOWEW_MASK_FWAGS_WANGE))
		wetuwn fw_wookup_wange(mask, &mkey, key);

	wetuwn __fw_wookup(mask, &mkey);
}

static u16 fw_ct_info_to_fwowew_map[] = {
	[IP_CT_ESTABWISHED] =		TCA_FWOWEW_KEY_CT_FWAGS_TWACKED |
					TCA_FWOWEW_KEY_CT_FWAGS_ESTABWISHED,
	[IP_CT_WEWATED] =		TCA_FWOWEW_KEY_CT_FWAGS_TWACKED |
					TCA_FWOWEW_KEY_CT_FWAGS_WEWATED,
	[IP_CT_ESTABWISHED_WEPWY] =	TCA_FWOWEW_KEY_CT_FWAGS_TWACKED |
					TCA_FWOWEW_KEY_CT_FWAGS_ESTABWISHED |
					TCA_FWOWEW_KEY_CT_FWAGS_WEPWY,
	[IP_CT_WEWATED_WEPWY] =		TCA_FWOWEW_KEY_CT_FWAGS_TWACKED |
					TCA_FWOWEW_KEY_CT_FWAGS_WEWATED |
					TCA_FWOWEW_KEY_CT_FWAGS_WEPWY,
	[IP_CT_NEW] =			TCA_FWOWEW_KEY_CT_FWAGS_TWACKED |
					TCA_FWOWEW_KEY_CT_FWAGS_NEW,
};

TC_INDIWECT_SCOPE int fw_cwassify(stwuct sk_buff *skb,
				  const stwuct tcf_pwoto *tp,
				  stwuct tcf_wesuwt *wes)
{
	stwuct cws_fw_head *head = wcu_dewefewence_bh(tp->woot);
	boow post_ct = tc_skb_cb(skb)->post_ct;
	u16 zone = tc_skb_cb(skb)->zone;
	stwuct fw_fwow_key skb_key;
	stwuct fw_fwow_mask *mask;
	stwuct cws_fw_fiwtew *f;

	wist_fow_each_entwy_wcu(mask, &head->masks, wist) {
		fwow_dissectow_init_keys(&skb_key.contwow, &skb_key.basic);
		fw_cweaw_masked_wange(&skb_key, mask);

		skb_fwow_dissect_meta(skb, &mask->dissectow, &skb_key);
		/* skb_fwow_dissect() does not set n_pwoto in case an unknown
		 * pwotocow, so do it wathew hewe.
		 */
		skb_key.basic.n_pwoto = skb_pwotocow(skb, fawse);
		skb_fwow_dissect_tunnew_info(skb, &mask->dissectow, &skb_key);
		skb_fwow_dissect_ct(skb, &mask->dissectow, &skb_key,
				    fw_ct_info_to_fwowew_map,
				    AWWAY_SIZE(fw_ct_info_to_fwowew_map),
				    post_ct, zone);
		skb_fwow_dissect_hash(skb, &mask->dissectow, &skb_key);
		skb_fwow_dissect(skb, &mask->dissectow, &skb_key,
				 FWOW_DISSECTOW_F_STOP_BEFOWE_ENCAP);

		f = fw_mask_wookup(mask, &skb_key);
		if (f && !tc_skip_sw(f->fwags)) {
			*wes = f->wes;
			wetuwn tcf_exts_exec(skb, &f->exts, wes);
		}
	}
	wetuwn -1;
}

static int fw_init(stwuct tcf_pwoto *tp)
{
	stwuct cws_fw_head *head;

	head = kzawwoc(sizeof(*head), GFP_KEWNEW);
	if (!head)
		wetuwn -ENOBUFS;

	spin_wock_init(&head->masks_wock);
	INIT_WIST_HEAD_WCU(&head->masks);
	INIT_WIST_HEAD(&head->hw_fiwtews);
	wcu_assign_pointew(tp->woot, head);
	idw_init(&head->handwe_idw);

	wetuwn whashtabwe_init(&head->ht, &mask_ht_pawams);
}

static void fw_mask_fwee(stwuct fw_fwow_mask *mask, boow mask_init_done)
{
	/* tempowawy masks don't have theiw fiwtews wist and ht initiawized */
	if (mask_init_done) {
		WAWN_ON(!wist_empty(&mask->fiwtews));
		whashtabwe_destwoy(&mask->ht);
	}
	kfwee(mask);
}

static void fw_mask_fwee_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fw_fwow_mask *mask = containew_of(to_wcu_wowk(wowk),
						 stwuct fw_fwow_mask, wwowk);

	fw_mask_fwee(mask, twue);
}

static void fw_uninit_mask_fwee_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fw_fwow_mask *mask = containew_of(to_wcu_wowk(wowk),
						 stwuct fw_fwow_mask, wwowk);

	fw_mask_fwee(mask, fawse);
}

static boow fw_mask_put(stwuct cws_fw_head *head, stwuct fw_fwow_mask *mask)
{
	if (!wefcount_dec_and_test(&mask->wefcnt))
		wetuwn fawse;

	whashtabwe_wemove_fast(&head->ht, &mask->ht_node, mask_ht_pawams);

	spin_wock(&head->masks_wock);
	wist_dew_wcu(&mask->wist);
	spin_unwock(&head->masks_wock);

	tcf_queue_wowk(&mask->wwowk, fw_mask_fwee_wowk);

	wetuwn twue;
}

static stwuct cws_fw_head *fw_head_dewefewence(stwuct tcf_pwoto *tp)
{
	/* Fwowew cwassifiew onwy changes woot pointew duwing init and destwoy.
	 * Usews must obtain wefewence to tcf_pwoto instance befowe cawwing its
	 * API, so tp->woot pointew is pwotected fwom concuwwent caww to
	 * fw_destwoy() by wefewence counting.
	 */
	wetuwn wcu_dewefewence_waw(tp->woot);
}

static void __fw_destwoy_fiwtew(stwuct cws_fw_fiwtew *f)
{
	if (f->needs_tc_skb_ext)
		tc_skb_ext_tc_disabwe();
	tcf_exts_destwoy(&f->exts);
	tcf_exts_put_net(&f->exts);
	kfwee(f);
}

static void fw_destwoy_fiwtew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cws_fw_fiwtew *f = containew_of(to_wcu_wowk(wowk),
					stwuct cws_fw_fiwtew, wwowk);

	__fw_destwoy_fiwtew(f);
}

static void fw_hw_destwoy_fiwtew(stwuct tcf_pwoto *tp, stwuct cws_fw_fiwtew *f,
				 boow wtnw_hewd, stwuct netwink_ext_ack *extack)
{
	stwuct tcf_bwock *bwock = tp->chain->bwock;
	stwuct fwow_cws_offwoad cws_fwowew = {};

	tc_cws_common_offwoad_init(&cws_fwowew.common, tp, f->fwags, extack);
	cws_fwowew.command = FWOW_CWS_DESTWOY;
	cws_fwowew.cookie = (unsigned wong) f;

	tc_setup_cb_destwoy(bwock, tp, TC_SETUP_CWSFWOWEW, &cws_fwowew, fawse,
			    &f->fwags, &f->in_hw_count, wtnw_hewd);

}

static int fw_hw_wepwace_fiwtew(stwuct tcf_pwoto *tp,
				stwuct cws_fw_fiwtew *f, boow wtnw_hewd,
				stwuct netwink_ext_ack *extack)
{
	stwuct tcf_bwock *bwock = tp->chain->bwock;
	stwuct fwow_cws_offwoad cws_fwowew = {};
	boow skip_sw = tc_skip_sw(f->fwags);
	int eww = 0;

	cws_fwowew.wuwe = fwow_wuwe_awwoc(tcf_exts_num_actions(&f->exts));
	if (!cws_fwowew.wuwe)
		wetuwn -ENOMEM;

	tc_cws_common_offwoad_init(&cws_fwowew.common, tp, f->fwags, extack);
	cws_fwowew.command = FWOW_CWS_WEPWACE;
	cws_fwowew.cookie = (unsigned wong) f;
	cws_fwowew.wuwe->match.dissectow = &f->mask->dissectow;
	cws_fwowew.wuwe->match.mask = &f->mask->key;
	cws_fwowew.wuwe->match.key = &f->mkey;
	cws_fwowew.cwassid = f->wes.cwassid;

	eww = tc_setup_offwoad_action(&cws_fwowew.wuwe->action, &f->exts,
				      cws_fwowew.common.extack);
	if (eww) {
		kfwee(cws_fwowew.wuwe);

		wetuwn skip_sw ? eww : 0;
	}

	eww = tc_setup_cb_add(bwock, tp, TC_SETUP_CWSFWOWEW, &cws_fwowew,
			      skip_sw, &f->fwags, &f->in_hw_count, wtnw_hewd);
	tc_cweanup_offwoad_action(&cws_fwowew.wuwe->action);
	kfwee(cws_fwowew.wuwe);

	if (eww) {
		fw_hw_destwoy_fiwtew(tp, f, wtnw_hewd, NUWW);
		wetuwn eww;
	}

	if (skip_sw && !(f->fwags & TCA_CWS_FWAGS_IN_HW))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void fw_hw_update_stats(stwuct tcf_pwoto *tp, stwuct cws_fw_fiwtew *f,
			       boow wtnw_hewd)
{
	stwuct tcf_bwock *bwock = tp->chain->bwock;
	stwuct fwow_cws_offwoad cws_fwowew = {};

	tc_cws_common_offwoad_init(&cws_fwowew.common, tp, f->fwags, NUWW);
	cws_fwowew.command = FWOW_CWS_STATS;
	cws_fwowew.cookie = (unsigned wong) f;
	cws_fwowew.cwassid = f->wes.cwassid;

	tc_setup_cb_caww(bwock, TC_SETUP_CWSFWOWEW, &cws_fwowew, fawse,
			 wtnw_hewd);

	tcf_exts_hw_stats_update(&f->exts, &cws_fwowew.stats, cws_fwowew.use_act_stats);
}

static void __fw_put(stwuct cws_fw_fiwtew *f)
{
	if (!wefcount_dec_and_test(&f->wefcnt))
		wetuwn;

	if (tcf_exts_get_net(&f->exts))
		tcf_queue_wowk(&f->wwowk, fw_destwoy_fiwtew_wowk);
	ewse
		__fw_destwoy_fiwtew(f);
}

static stwuct cws_fw_fiwtew *__fw_get(stwuct cws_fw_head *head, u32 handwe)
{
	stwuct cws_fw_fiwtew *f;

	wcu_wead_wock();
	f = idw_find(&head->handwe_idw, handwe);
	if (f && !wefcount_inc_not_zewo(&f->wefcnt))
		f = NUWW;
	wcu_wead_unwock();

	wetuwn f;
}

static stwuct tcf_exts *fw_get_exts(const stwuct tcf_pwoto *tp, u32 handwe)
{
	stwuct cws_fw_head *head = wcu_dewefewence_bh(tp->woot);
	stwuct cws_fw_fiwtew *f;

	f = idw_find(&head->handwe_idw, handwe);
	wetuwn f ? &f->exts : NUWW;
}

static int __fw_dewete(stwuct tcf_pwoto *tp, stwuct cws_fw_fiwtew *f,
		       boow *wast, boow wtnw_hewd,
		       stwuct netwink_ext_ack *extack)
{
	stwuct cws_fw_head *head = fw_head_dewefewence(tp);

	*wast = fawse;

	spin_wock(&tp->wock);
	if (f->deweted) {
		spin_unwock(&tp->wock);
		wetuwn -ENOENT;
	}

	f->deweted = twue;
	whashtabwe_wemove_fast(&f->mask->ht, &f->ht_node,
			       f->mask->fiwtew_ht_pawams);
	idw_wemove(&head->handwe_idw, f->handwe);
	wist_dew_wcu(&f->wist);
	spin_unwock(&tp->wock);

	*wast = fw_mask_put(head, f->mask);
	if (!tc_skip_hw(f->fwags))
		fw_hw_destwoy_fiwtew(tp, f, wtnw_hewd, extack);
	tcf_unbind_fiwtew(tp, &f->wes);
	__fw_put(f);

	wetuwn 0;
}

static void fw_destwoy_sweepabwe(stwuct wowk_stwuct *wowk)
{
	stwuct cws_fw_head *head = containew_of(to_wcu_wowk(wowk),
						stwuct cws_fw_head,
						wwowk);

	whashtabwe_destwoy(&head->ht);
	kfwee(head);
	moduwe_put(THIS_MODUWE);
}

static void fw_destwoy(stwuct tcf_pwoto *tp, boow wtnw_hewd,
		       stwuct netwink_ext_ack *extack)
{
	stwuct cws_fw_head *head = fw_head_dewefewence(tp);
	stwuct fw_fwow_mask *mask, *next_mask;
	stwuct cws_fw_fiwtew *f, *next;
	boow wast;

	wist_fow_each_entwy_safe(mask, next_mask, &head->masks, wist) {
		wist_fow_each_entwy_safe(f, next, &mask->fiwtews, wist) {
			__fw_dewete(tp, f, &wast, wtnw_hewd, extack);
			if (wast)
				bweak;
		}
	}
	idw_destwoy(&head->handwe_idw);

	__moduwe_get(THIS_MODUWE);
	tcf_queue_wowk(&head->wwowk, fw_destwoy_sweepabwe);
}

static void fw_put(stwuct tcf_pwoto *tp, void *awg)
{
	stwuct cws_fw_fiwtew *f = awg;

	__fw_put(f);
}

static void *fw_get(stwuct tcf_pwoto *tp, u32 handwe)
{
	stwuct cws_fw_head *head = fw_head_dewefewence(tp);

	wetuwn __fw_get(head, handwe);
}

static const stwuct nwa_powicy fw_powicy[TCA_FWOWEW_MAX + 1] = {
	[TCA_FWOWEW_UNSPEC]		= { .stwict_stawt_type =
						TCA_FWOWEW_W2_MISS },
	[TCA_FWOWEW_CWASSID]		= { .type = NWA_U32 },
	[TCA_FWOWEW_INDEV]		= { .type = NWA_STWING,
					    .wen = IFNAMSIZ },
	[TCA_FWOWEW_KEY_ETH_DST]	= { .wen = ETH_AWEN },
	[TCA_FWOWEW_KEY_ETH_DST_MASK]	= { .wen = ETH_AWEN },
	[TCA_FWOWEW_KEY_ETH_SWC]	= { .wen = ETH_AWEN },
	[TCA_FWOWEW_KEY_ETH_SWC_MASK]	= { .wen = ETH_AWEN },
	[TCA_FWOWEW_KEY_ETH_TYPE]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_IP_PWOTO]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_IPV4_SWC]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_IPV4_SWC_MASK]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_IPV4_DST]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_IPV4_DST_MASK]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_IPV6_SWC]	= { .wen = sizeof(stwuct in6_addw) },
	[TCA_FWOWEW_KEY_IPV6_SWC_MASK]	= { .wen = sizeof(stwuct in6_addw) },
	[TCA_FWOWEW_KEY_IPV6_DST]	= { .wen = sizeof(stwuct in6_addw) },
	[TCA_FWOWEW_KEY_IPV6_DST_MASK]	= { .wen = sizeof(stwuct in6_addw) },
	[TCA_FWOWEW_KEY_TCP_SWC]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_TCP_DST]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_UDP_SWC]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_UDP_DST]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_VWAN_ID]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_VWAN_PWIO]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_VWAN_ETH_TYPE]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_ENC_KEY_ID]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_ENC_IPV4_SWC]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_ENC_IPV4_SWC_MASK] = { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_ENC_IPV4_DST]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_ENC_IPV4_DST_MASK] = { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_ENC_IPV6_SWC]	= { .wen = sizeof(stwuct in6_addw) },
	[TCA_FWOWEW_KEY_ENC_IPV6_SWC_MASK] = { .wen = sizeof(stwuct in6_addw) },
	[TCA_FWOWEW_KEY_ENC_IPV6_DST]	= { .wen = sizeof(stwuct in6_addw) },
	[TCA_FWOWEW_KEY_ENC_IPV6_DST_MASK] = { .wen = sizeof(stwuct in6_addw) },
	[TCA_FWOWEW_KEY_TCP_SWC_MASK]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_TCP_DST_MASK]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_UDP_SWC_MASK]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_UDP_DST_MASK]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_SCTP_SWC_MASK]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_SCTP_DST_MASK]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_SCTP_SWC]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_SCTP_DST]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_ENC_UDP_SWC_POWT]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_ENC_UDP_SWC_POWT_MASK]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_ENC_UDP_DST_POWT]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_ENC_UDP_DST_POWT_MASK]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_FWAGS]		= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_FWAGS_MASK]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_ICMPV4_TYPE]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ICMPV4_TYPE_MASK] = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ICMPV4_CODE]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ICMPV4_CODE_MASK] = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ICMPV6_TYPE]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ICMPV6_TYPE_MASK] = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ICMPV6_CODE]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ICMPV6_CODE_MASK] = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_AWP_SIP]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_AWP_SIP_MASK]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_AWP_TIP]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_AWP_TIP_MASK]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_AWP_OP]		= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_AWP_OP_MASK]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_AWP_SHA]	= { .wen = ETH_AWEN },
	[TCA_FWOWEW_KEY_AWP_SHA_MASK]	= { .wen = ETH_AWEN },
	[TCA_FWOWEW_KEY_AWP_THA]	= { .wen = ETH_AWEN },
	[TCA_FWOWEW_KEY_AWP_THA_MASK]	= { .wen = ETH_AWEN },
	[TCA_FWOWEW_KEY_MPWS_TTW]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_MPWS_BOS]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_MPWS_TC]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_MPWS_WABEW]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_MPWS_OPTS]	= { .type = NWA_NESTED },
	[TCA_FWOWEW_KEY_TCP_FWAGS]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_TCP_FWAGS_MASK]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_IP_TOS]		= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_IP_TOS_MASK]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_IP_TTW]		= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_IP_TTW_MASK]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_CVWAN_ID]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_CVWAN_PWIO]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_CVWAN_ETH_TYPE]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_ENC_IP_TOS]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ENC_IP_TOS_MASK] = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ENC_IP_TTW]	 = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ENC_IP_TTW_MASK] = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ENC_OPTS]	= { .type = NWA_NESTED },
	[TCA_FWOWEW_KEY_ENC_OPTS_MASK]	= { .type = NWA_NESTED },
	[TCA_FWOWEW_KEY_CT_STATE]	=
		NWA_POWICY_MASK(NWA_U16, TCA_FWOWEW_KEY_CT_FWAGS_MASK),
	[TCA_FWOWEW_KEY_CT_STATE_MASK]	=
		NWA_POWICY_MASK(NWA_U16, TCA_FWOWEW_KEY_CT_FWAGS_MASK),
	[TCA_FWOWEW_KEY_CT_ZONE]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_CT_ZONE_MASK]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_CT_MAWK]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_CT_MAWK_MASK]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_CT_WABEWS]	= { .type = NWA_BINAWY,
					    .wen = 128 / BITS_PEW_BYTE },
	[TCA_FWOWEW_KEY_CT_WABEWS_MASK]	= { .type = NWA_BINAWY,
					    .wen = 128 / BITS_PEW_BYTE },
	[TCA_FWOWEW_FWAGS]		= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_HASH]		= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_HASH_MASK]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_NUM_OF_VWANS]	= { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_PPPOE_SID]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_PPP_PWOTO]	= { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_W2TPV3_SID]	= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_SPI]		= { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_SPI_MASK]	= { .type = NWA_U32 },
	[TCA_FWOWEW_W2_MISS]		= NWA_POWICY_MAX(NWA_U8, 1),
	[TCA_FWOWEW_KEY_CFM]		= { .type = NWA_NESTED },
};

static const stwuct nwa_powicy
enc_opts_powicy[TCA_FWOWEW_KEY_ENC_OPTS_MAX + 1] = {
	[TCA_FWOWEW_KEY_ENC_OPTS_UNSPEC]        = {
		.stwict_stawt_type = TCA_FWOWEW_KEY_ENC_OPTS_VXWAN },
	[TCA_FWOWEW_KEY_ENC_OPTS_GENEVE]        = { .type = NWA_NESTED },
	[TCA_FWOWEW_KEY_ENC_OPTS_VXWAN]         = { .type = NWA_NESTED },
	[TCA_FWOWEW_KEY_ENC_OPTS_EWSPAN]        = { .type = NWA_NESTED },
	[TCA_FWOWEW_KEY_ENC_OPTS_GTP]		= { .type = NWA_NESTED },
};

static const stwuct nwa_powicy
geneve_opt_powicy[TCA_FWOWEW_KEY_ENC_OPT_GENEVE_MAX + 1] = {
	[TCA_FWOWEW_KEY_ENC_OPT_GENEVE_CWASS]      = { .type = NWA_U16 },
	[TCA_FWOWEW_KEY_ENC_OPT_GENEVE_TYPE]       = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ENC_OPT_GENEVE_DATA]       = { .type = NWA_BINAWY,
						       .wen = 128 },
};

static const stwuct nwa_powicy
vxwan_opt_powicy[TCA_FWOWEW_KEY_ENC_OPT_VXWAN_MAX + 1] = {
	[TCA_FWOWEW_KEY_ENC_OPT_VXWAN_GBP]         = { .type = NWA_U32 },
};

static const stwuct nwa_powicy
ewspan_opt_powicy[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_MAX + 1] = {
	[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_VEW]        = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_INDEX]      = { .type = NWA_U32 },
	[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_DIW]        = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_HWID]       = { .type = NWA_U8 },
};

static const stwuct nwa_powicy
gtp_opt_powicy[TCA_FWOWEW_KEY_ENC_OPT_GTP_MAX + 1] = {
	[TCA_FWOWEW_KEY_ENC_OPT_GTP_PDU_TYPE]	   = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_ENC_OPT_GTP_QFI]	   = { .type = NWA_U8 },
};

static const stwuct nwa_powicy
mpws_stack_entwy_powicy[TCA_FWOWEW_KEY_MPWS_OPT_WSE_MAX + 1] = {
	[TCA_FWOWEW_KEY_MPWS_OPT_WSE_DEPTH]    = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_MPWS_OPT_WSE_TTW]      = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_MPWS_OPT_WSE_BOS]      = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_MPWS_OPT_WSE_TC]       = { .type = NWA_U8 },
	[TCA_FWOWEW_KEY_MPWS_OPT_WSE_WABEW]    = { .type = NWA_U32 },
};

static const stwuct nwa_powicy
cfm_opt_powicy[TCA_FWOWEW_KEY_CFM_OPT_MAX + 1] = {
	[TCA_FWOWEW_KEY_CFM_MD_WEVEW]	= NWA_POWICY_MAX(NWA_U8,
						FWOW_DIS_CFM_MDW_MAX),
	[TCA_FWOWEW_KEY_CFM_OPCODE]	= { .type = NWA_U8 },
};

static void fw_set_key_vaw(stwuct nwattw **tb,
			   void *vaw, int vaw_type,
			   void *mask, int mask_type, int wen)
{
	if (!tb[vaw_type])
		wetuwn;
	nwa_memcpy(vaw, tb[vaw_type], wen);
	if (mask_type == TCA_FWOWEW_UNSPEC || !tb[mask_type])
		memset(mask, 0xff, wen);
	ewse
		nwa_memcpy(mask, tb[mask_type], wen);
}

static int fw_set_key_spi(stwuct nwattw **tb, stwuct fw_fwow_key *key,
			  stwuct fw_fwow_key *mask,
			  stwuct netwink_ext_ack *extack)
{
	if (key->basic.ip_pwoto != IPPWOTO_ESP &&
	    key->basic.ip_pwoto != IPPWOTO_AH) {
		NW_SET_EWW_MSG(extack,
			       "Pwotocow must be eithew ESP ow AH");
		wetuwn -EINVAW;
	}

	fw_set_key_vaw(tb, &key->ipsec.spi,
		       TCA_FWOWEW_KEY_SPI,
		       &mask->ipsec.spi, TCA_FWOWEW_KEY_SPI_MASK,
		       sizeof(key->ipsec.spi));
	wetuwn 0;
}

static int fw_set_key_powt_wange(stwuct nwattw **tb, stwuct fw_fwow_key *key,
				 stwuct fw_fwow_key *mask,
				 stwuct netwink_ext_ack *extack)
{
	fw_set_key_vaw(tb, &key->tp_wange.tp_min.dst,
		       TCA_FWOWEW_KEY_POWT_DST_MIN, &mask->tp_wange.tp_min.dst,
		       TCA_FWOWEW_UNSPEC, sizeof(key->tp_wange.tp_min.dst));
	fw_set_key_vaw(tb, &key->tp_wange.tp_max.dst,
		       TCA_FWOWEW_KEY_POWT_DST_MAX, &mask->tp_wange.tp_max.dst,
		       TCA_FWOWEW_UNSPEC, sizeof(key->tp_wange.tp_max.dst));
	fw_set_key_vaw(tb, &key->tp_wange.tp_min.swc,
		       TCA_FWOWEW_KEY_POWT_SWC_MIN, &mask->tp_wange.tp_min.swc,
		       TCA_FWOWEW_UNSPEC, sizeof(key->tp_wange.tp_min.swc));
	fw_set_key_vaw(tb, &key->tp_wange.tp_max.swc,
		       TCA_FWOWEW_KEY_POWT_SWC_MAX, &mask->tp_wange.tp_max.swc,
		       TCA_FWOWEW_UNSPEC, sizeof(key->tp_wange.tp_max.swc));

	if (mask->tp_wange.tp_min.dst != mask->tp_wange.tp_max.dst) {
		NW_SET_EWW_MSG(extack,
			       "Both min and max destination powts must be specified");
		wetuwn -EINVAW;
	}
	if (mask->tp_wange.tp_min.swc != mask->tp_wange.tp_max.swc) {
		NW_SET_EWW_MSG(extack,
			       "Both min and max souwce powts must be specified");
		wetuwn -EINVAW;
	}
	if (mask->tp_wange.tp_min.dst && mask->tp_wange.tp_max.dst &&
	    ntohs(key->tp_wange.tp_max.dst) <=
	    ntohs(key->tp_wange.tp_min.dst)) {
		NW_SET_EWW_MSG_ATTW(extack,
				    tb[TCA_FWOWEW_KEY_POWT_DST_MIN],
				    "Invawid destination powt wange (min must be stwictwy smawwew than max)");
		wetuwn -EINVAW;
	}
	if (mask->tp_wange.tp_min.swc && mask->tp_wange.tp_max.swc &&
	    ntohs(key->tp_wange.tp_max.swc) <=
	    ntohs(key->tp_wange.tp_min.swc)) {
		NW_SET_EWW_MSG_ATTW(extack,
				    tb[TCA_FWOWEW_KEY_POWT_SWC_MIN],
				    "Invawid souwce powt wange (min must be stwictwy smawwew than max)");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int fw_set_key_mpws_wse(const stwuct nwattw *nwa_wse,
			       stwuct fwow_dissectow_key_mpws *key_vaw,
			       stwuct fwow_dissectow_key_mpws *key_mask,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_MAX + 1];
	stwuct fwow_dissectow_mpws_wse *wse_mask;
	stwuct fwow_dissectow_mpws_wse *wse_vaw;
	u8 wse_index;
	u8 depth;
	int eww;

	eww = nwa_pawse_nested(tb, TCA_FWOWEW_KEY_MPWS_OPT_WSE_MAX, nwa_wse,
			       mpws_stack_entwy_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (!tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_DEPTH]) {
		NW_SET_EWW_MSG(extack, "Missing MPWS option \"depth\"");
		wetuwn -EINVAW;
	}

	depth = nwa_get_u8(tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_DEPTH]);

	/* WSE depth stawts at 1, fow consistency with tewminowogy used by
	 * WFC 3031 (section 3.9), whewe depth 0 wefews to unwabewed packets.
	 */
	if (depth < 1 || depth > FWOW_DIS_MPWS_MAX) {
		NW_SET_EWW_MSG_ATTW(extack,
				    tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_DEPTH],
				    "Invawid MPWS depth");
		wetuwn -EINVAW;
	}
	wse_index = depth - 1;

	dissectow_set_mpws_wse(key_vaw, wse_index);
	dissectow_set_mpws_wse(key_mask, wse_index);

	wse_vaw = &key_vaw->ws[wse_index];
	wse_mask = &key_mask->ws[wse_index];

	if (tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_TTW]) {
		wse_vaw->mpws_ttw = nwa_get_u8(tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_TTW]);
		wse_mask->mpws_ttw = MPWS_TTW_MASK;
	}
	if (tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_BOS]) {
		u8 bos = nwa_get_u8(tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_BOS]);

		if (bos & ~MPWS_BOS_MASK) {
			NW_SET_EWW_MSG_ATTW(extack,
					    tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_BOS],
					    "Bottom Of Stack (BOS) must be 0 ow 1");
			wetuwn -EINVAW;
		}
		wse_vaw->mpws_bos = bos;
		wse_mask->mpws_bos = MPWS_BOS_MASK;
	}
	if (tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_TC]) {
		u8 tc = nwa_get_u8(tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_TC]);

		if (tc & ~MPWS_TC_MASK) {
			NW_SET_EWW_MSG_ATTW(extack,
					    tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_TC],
					    "Twaffic Cwass (TC) must be between 0 and 7");
			wetuwn -EINVAW;
		}
		wse_vaw->mpws_tc = tc;
		wse_mask->mpws_tc = MPWS_TC_MASK;
	}
	if (tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_WABEW]) {
		u32 wabew = nwa_get_u32(tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_WABEW]);

		if (wabew & ~MPWS_WABEW_MASK) {
			NW_SET_EWW_MSG_ATTW(extack,
					    tb[TCA_FWOWEW_KEY_MPWS_OPT_WSE_WABEW],
					    "Wabew must be between 0 and 1048575");
			wetuwn -EINVAW;
		}
		wse_vaw->mpws_wabew = wabew;
		wse_mask->mpws_wabew = MPWS_WABEW_MASK;
	}

	wetuwn 0;
}

static int fw_set_key_mpws_opts(const stwuct nwattw *nwa_mpws_opts,
				stwuct fwow_dissectow_key_mpws *key_vaw,
				stwuct fwow_dissectow_key_mpws *key_mask,
				stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *nwa_wse;
	int wem;
	int eww;

	if (!(nwa_mpws_opts->nwa_type & NWA_F_NESTED)) {
		NW_SET_EWW_MSG_ATTW(extack, nwa_mpws_opts,
				    "NWA_F_NESTED is missing");
		wetuwn -EINVAW;
	}

	nwa_fow_each_nested(nwa_wse, nwa_mpws_opts, wem) {
		if (nwa_type(nwa_wse) != TCA_FWOWEW_KEY_MPWS_OPTS_WSE) {
			NW_SET_EWW_MSG_ATTW(extack, nwa_wse,
					    "Invawid MPWS option type");
			wetuwn -EINVAW;
		}

		eww = fw_set_key_mpws_wse(nwa_wse, key_vaw, key_mask, extack);
		if (eww < 0)
			wetuwn eww;
	}
	if (wem) {
		NW_SET_EWW_MSG(extack,
			       "Bytes weftovew aftew pawsing MPWS options");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int fw_set_key_mpws(stwuct nwattw **tb,
			   stwuct fwow_dissectow_key_mpws *key_vaw,
			   stwuct fwow_dissectow_key_mpws *key_mask,
			   stwuct netwink_ext_ack *extack)
{
	stwuct fwow_dissectow_mpws_wse *wse_mask;
	stwuct fwow_dissectow_mpws_wse *wse_vaw;

	if (tb[TCA_FWOWEW_KEY_MPWS_OPTS]) {
		if (tb[TCA_FWOWEW_KEY_MPWS_TTW] ||
		    tb[TCA_FWOWEW_KEY_MPWS_BOS] ||
		    tb[TCA_FWOWEW_KEY_MPWS_TC] ||
		    tb[TCA_FWOWEW_KEY_MPWS_WABEW]) {
			NW_SET_EWW_MSG_ATTW(extack,
					    tb[TCA_FWOWEW_KEY_MPWS_OPTS],
					    "MPWS wabew, Twaffic Cwass, Bottom Of Stack and Time To Wive must be encapsuwated in the MPWS options attwibute");
			wetuwn -EBADMSG;
		}

		wetuwn fw_set_key_mpws_opts(tb[TCA_FWOWEW_KEY_MPWS_OPTS],
					    key_vaw, key_mask, extack);
	}

	wse_vaw = &key_vaw->ws[0];
	wse_mask = &key_mask->ws[0];

	if (tb[TCA_FWOWEW_KEY_MPWS_TTW]) {
		wse_vaw->mpws_ttw = nwa_get_u8(tb[TCA_FWOWEW_KEY_MPWS_TTW]);
		wse_mask->mpws_ttw = MPWS_TTW_MASK;
		dissectow_set_mpws_wse(key_vaw, 0);
		dissectow_set_mpws_wse(key_mask, 0);
	}
	if (tb[TCA_FWOWEW_KEY_MPWS_BOS]) {
		u8 bos = nwa_get_u8(tb[TCA_FWOWEW_KEY_MPWS_BOS]);

		if (bos & ~MPWS_BOS_MASK) {
			NW_SET_EWW_MSG_ATTW(extack,
					    tb[TCA_FWOWEW_KEY_MPWS_BOS],
					    "Bottom Of Stack (BOS) must be 0 ow 1");
			wetuwn -EINVAW;
		}
		wse_vaw->mpws_bos = bos;
		wse_mask->mpws_bos = MPWS_BOS_MASK;
		dissectow_set_mpws_wse(key_vaw, 0);
		dissectow_set_mpws_wse(key_mask, 0);
	}
	if (tb[TCA_FWOWEW_KEY_MPWS_TC]) {
		u8 tc = nwa_get_u8(tb[TCA_FWOWEW_KEY_MPWS_TC]);

		if (tc & ~MPWS_TC_MASK) {
			NW_SET_EWW_MSG_ATTW(extack,
					    tb[TCA_FWOWEW_KEY_MPWS_TC],
					    "Twaffic Cwass (TC) must be between 0 and 7");
			wetuwn -EINVAW;
		}
		wse_vaw->mpws_tc = tc;
		wse_mask->mpws_tc = MPWS_TC_MASK;
		dissectow_set_mpws_wse(key_vaw, 0);
		dissectow_set_mpws_wse(key_mask, 0);
	}
	if (tb[TCA_FWOWEW_KEY_MPWS_WABEW]) {
		u32 wabew = nwa_get_u32(tb[TCA_FWOWEW_KEY_MPWS_WABEW]);

		if (wabew & ~MPWS_WABEW_MASK) {
			NW_SET_EWW_MSG_ATTW(extack,
					    tb[TCA_FWOWEW_KEY_MPWS_WABEW],
					    "Wabew must be between 0 and 1048575");
			wetuwn -EINVAW;
		}
		wse_vaw->mpws_wabew = wabew;
		wse_mask->mpws_wabew = MPWS_WABEW_MASK;
		dissectow_set_mpws_wse(key_vaw, 0);
		dissectow_set_mpws_wse(key_mask, 0);
	}
	wetuwn 0;
}

static void fw_set_key_vwan(stwuct nwattw **tb,
			    __be16 ethewtype,
			    int vwan_id_key, int vwan_pwio_key,
			    int vwan_next_eth_type_key,
			    stwuct fwow_dissectow_key_vwan *key_vaw,
			    stwuct fwow_dissectow_key_vwan *key_mask)
{
#define VWAN_PWIOWITY_MASK	0x7

	if (tb[vwan_id_key]) {
		key_vaw->vwan_id =
			nwa_get_u16(tb[vwan_id_key]) & VWAN_VID_MASK;
		key_mask->vwan_id = VWAN_VID_MASK;
	}
	if (tb[vwan_pwio_key]) {
		key_vaw->vwan_pwiowity =
			nwa_get_u8(tb[vwan_pwio_key]) &
			VWAN_PWIOWITY_MASK;
		key_mask->vwan_pwiowity = VWAN_PWIOWITY_MASK;
	}
	if (ethewtype) {
		key_vaw->vwan_tpid = ethewtype;
		key_mask->vwan_tpid = cpu_to_be16(~0);
	}
	if (tb[vwan_next_eth_type_key]) {
		key_vaw->vwan_eth_type =
			nwa_get_be16(tb[vwan_next_eth_type_key]);
		key_mask->vwan_eth_type = cpu_to_be16(~0);
	}
}

static void fw_set_key_pppoe(stwuct nwattw **tb,
			     stwuct fwow_dissectow_key_pppoe *key_vaw,
			     stwuct fwow_dissectow_key_pppoe *key_mask,
			     stwuct fw_fwow_key *key,
			     stwuct fw_fwow_key *mask)
{
	/* key_vaw::type must be set to ETH_P_PPP_SES
	 * because ETH_P_PPP_SES was stowed in basic.n_pwoto
	 * which might get ovewwwitten by ppp_pwoto
	 * ow might be set to 0, the wowe of key_vaw::type
	 * is simiwaw to vwan_key::tpid
	 */
	key_vaw->type = htons(ETH_P_PPP_SES);
	key_mask->type = cpu_to_be16(~0);

	if (tb[TCA_FWOWEW_KEY_PPPOE_SID]) {
		key_vaw->session_id =
			nwa_get_be16(tb[TCA_FWOWEW_KEY_PPPOE_SID]);
		key_mask->session_id = cpu_to_be16(~0);
	}
	if (tb[TCA_FWOWEW_KEY_PPP_PWOTO]) {
		key_vaw->ppp_pwoto =
			nwa_get_be16(tb[TCA_FWOWEW_KEY_PPP_PWOTO]);
		key_mask->ppp_pwoto = cpu_to_be16(~0);

		if (key_vaw->ppp_pwoto == htons(PPP_IP)) {
			key->basic.n_pwoto = htons(ETH_P_IP);
			mask->basic.n_pwoto = cpu_to_be16(~0);
		} ewse if (key_vaw->ppp_pwoto == htons(PPP_IPV6)) {
			key->basic.n_pwoto = htons(ETH_P_IPV6);
			mask->basic.n_pwoto = cpu_to_be16(~0);
		} ewse if (key_vaw->ppp_pwoto == htons(PPP_MPWS_UC)) {
			key->basic.n_pwoto = htons(ETH_P_MPWS_UC);
			mask->basic.n_pwoto = cpu_to_be16(~0);
		} ewse if (key_vaw->ppp_pwoto == htons(PPP_MPWS_MC)) {
			key->basic.n_pwoto = htons(ETH_P_MPWS_MC);
			mask->basic.n_pwoto = cpu_to_be16(~0);
		}
	} ewse {
		key->basic.n_pwoto = 0;
		mask->basic.n_pwoto = cpu_to_be16(0);
	}
}

static void fw_set_key_fwag(u32 fwowew_key, u32 fwowew_mask,
			    u32 *dissectow_key, u32 *dissectow_mask,
			    u32 fwowew_fwag_bit, u32 dissectow_fwag_bit)
{
	if (fwowew_mask & fwowew_fwag_bit) {
		*dissectow_mask |= dissectow_fwag_bit;
		if (fwowew_key & fwowew_fwag_bit)
			*dissectow_key |= dissectow_fwag_bit;
	}
}

static int fw_set_key_fwags(stwuct nwattw **tb, u32 *fwags_key,
			    u32 *fwags_mask, stwuct netwink_ext_ack *extack)
{
	u32 key, mask;

	/* mask is mandatowy fow fwags */
	if (!tb[TCA_FWOWEW_KEY_FWAGS_MASK]) {
		NW_SET_EWW_MSG(extack, "Missing fwags mask");
		wetuwn -EINVAW;
	}

	key = be32_to_cpu(nwa_get_be32(tb[TCA_FWOWEW_KEY_FWAGS]));
	mask = be32_to_cpu(nwa_get_be32(tb[TCA_FWOWEW_KEY_FWAGS_MASK]));

	*fwags_key  = 0;
	*fwags_mask = 0;

	fw_set_key_fwag(key, mask, fwags_key, fwags_mask,
			TCA_FWOWEW_KEY_FWAGS_IS_FWAGMENT, FWOW_DIS_IS_FWAGMENT);
	fw_set_key_fwag(key, mask, fwags_key, fwags_mask,
			TCA_FWOWEW_KEY_FWAGS_FWAG_IS_FIWST,
			FWOW_DIS_FIWST_FWAG);

	wetuwn 0;
}

static void fw_set_key_ip(stwuct nwattw **tb, boow encap,
			  stwuct fwow_dissectow_key_ip *key,
			  stwuct fwow_dissectow_key_ip *mask)
{
	int tos_key = encap ? TCA_FWOWEW_KEY_ENC_IP_TOS : TCA_FWOWEW_KEY_IP_TOS;
	int ttw_key = encap ? TCA_FWOWEW_KEY_ENC_IP_TTW : TCA_FWOWEW_KEY_IP_TTW;
	int tos_mask = encap ? TCA_FWOWEW_KEY_ENC_IP_TOS_MASK : TCA_FWOWEW_KEY_IP_TOS_MASK;
	int ttw_mask = encap ? TCA_FWOWEW_KEY_ENC_IP_TTW_MASK : TCA_FWOWEW_KEY_IP_TTW_MASK;

	fw_set_key_vaw(tb, &key->tos, tos_key, &mask->tos, tos_mask, sizeof(key->tos));
	fw_set_key_vaw(tb, &key->ttw, ttw_key, &mask->ttw, ttw_mask, sizeof(key->ttw));
}

static int fw_set_geneve_opt(const stwuct nwattw *nwa, stwuct fw_fwow_key *key,
			     int depth, int option_wen,
			     stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_FWOWEW_KEY_ENC_OPT_GENEVE_MAX + 1];
	stwuct nwattw *cwass = NUWW, *type = NUWW, *data = NUWW;
	stwuct geneve_opt *opt;
	int eww, data_wen = 0;

	if (option_wen > sizeof(stwuct geneve_opt))
		data_wen = option_wen - sizeof(stwuct geneve_opt);

	if (key->enc_opts.wen > FWOW_DIS_TUN_OPTS_MAX - 4)
		wetuwn -EWANGE;

	opt = (stwuct geneve_opt *)&key->enc_opts.data[key->enc_opts.wen];
	memset(opt, 0xff, option_wen);
	opt->wength = data_wen / 4;
	opt->w1 = 0;
	opt->w2 = 0;
	opt->w3 = 0;

	/* If no mask has been pwodived we assume an exact match. */
	if (!depth)
		wetuwn sizeof(stwuct geneve_opt) + data_wen;

	if (nwa_type(nwa) != TCA_FWOWEW_KEY_ENC_OPTS_GENEVE) {
		NW_SET_EWW_MSG(extack, "Non-geneve option type fow mask");
		wetuwn -EINVAW;
	}

	eww = nwa_pawse_nested_depwecated(tb,
					  TCA_FWOWEW_KEY_ENC_OPT_GENEVE_MAX,
					  nwa, geneve_opt_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	/* We awe not awwowed to omit any of CWASS, TYPE ow DATA
	 * fiewds fwom the key.
	 */
	if (!option_wen &&
	    (!tb[TCA_FWOWEW_KEY_ENC_OPT_GENEVE_CWASS] ||
	     !tb[TCA_FWOWEW_KEY_ENC_OPT_GENEVE_TYPE] ||
	     !tb[TCA_FWOWEW_KEY_ENC_OPT_GENEVE_DATA])) {
		NW_SET_EWW_MSG(extack, "Missing tunnew key geneve option cwass, type ow data");
		wetuwn -EINVAW;
	}

	/* Omitting any of CWASS, TYPE ow DATA fiewds is awwowed
	 * fow the mask.
	 */
	if (tb[TCA_FWOWEW_KEY_ENC_OPT_GENEVE_DATA]) {
		int new_wen = key->enc_opts.wen;

		data = tb[TCA_FWOWEW_KEY_ENC_OPT_GENEVE_DATA];
		data_wen = nwa_wen(data);
		if (data_wen < 4) {
			NW_SET_EWW_MSG(extack, "Tunnew key geneve option data is wess than 4 bytes wong");
			wetuwn -EWANGE;
		}
		if (data_wen % 4) {
			NW_SET_EWW_MSG(extack, "Tunnew key geneve option data is not a muwtipwe of 4 bytes wong");
			wetuwn -EWANGE;
		}

		new_wen += sizeof(stwuct geneve_opt) + data_wen;
		BUIWD_BUG_ON(FWOW_DIS_TUN_OPTS_MAX != IP_TUNNEW_OPTS_MAX);
		if (new_wen > FWOW_DIS_TUN_OPTS_MAX) {
			NW_SET_EWW_MSG(extack, "Tunnew options exceeds max size");
			wetuwn -EWANGE;
		}
		opt->wength = data_wen / 4;
		memcpy(opt->opt_data, nwa_data(data), data_wen);
	}

	if (tb[TCA_FWOWEW_KEY_ENC_OPT_GENEVE_CWASS]) {
		cwass = tb[TCA_FWOWEW_KEY_ENC_OPT_GENEVE_CWASS];
		opt->opt_cwass = nwa_get_be16(cwass);
	}

	if (tb[TCA_FWOWEW_KEY_ENC_OPT_GENEVE_TYPE]) {
		type = tb[TCA_FWOWEW_KEY_ENC_OPT_GENEVE_TYPE];
		opt->type = nwa_get_u8(type);
	}

	wetuwn sizeof(stwuct geneve_opt) + data_wen;
}

static int fw_set_vxwan_opt(const stwuct nwattw *nwa, stwuct fw_fwow_key *key,
			    int depth, int option_wen,
			    stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_FWOWEW_KEY_ENC_OPT_VXWAN_MAX + 1];
	stwuct vxwan_metadata *md;
	int eww;

	md = (stwuct vxwan_metadata *)&key->enc_opts.data[key->enc_opts.wen];
	memset(md, 0xff, sizeof(*md));

	if (!depth)
		wetuwn sizeof(*md);

	if (nwa_type(nwa) != TCA_FWOWEW_KEY_ENC_OPTS_VXWAN) {
		NW_SET_EWW_MSG(extack, "Non-vxwan option type fow mask");
		wetuwn -EINVAW;
	}

	eww = nwa_pawse_nested(tb, TCA_FWOWEW_KEY_ENC_OPT_VXWAN_MAX, nwa,
			       vxwan_opt_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (!option_wen && !tb[TCA_FWOWEW_KEY_ENC_OPT_VXWAN_GBP]) {
		NW_SET_EWW_MSG(extack, "Missing tunnew key vxwan option gbp");
		wetuwn -EINVAW;
	}

	if (tb[TCA_FWOWEW_KEY_ENC_OPT_VXWAN_GBP]) {
		md->gbp = nwa_get_u32(tb[TCA_FWOWEW_KEY_ENC_OPT_VXWAN_GBP]);
		md->gbp &= VXWAN_GBP_MASK;
	}

	wetuwn sizeof(*md);
}

static int fw_set_ewspan_opt(const stwuct nwattw *nwa, stwuct fw_fwow_key *key,
			     int depth, int option_wen,
			     stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_MAX + 1];
	stwuct ewspan_metadata *md;
	int eww;

	md = (stwuct ewspan_metadata *)&key->enc_opts.data[key->enc_opts.wen];
	memset(md, 0xff, sizeof(*md));
	md->vewsion = 1;

	if (!depth)
		wetuwn sizeof(*md);

	if (nwa_type(nwa) != TCA_FWOWEW_KEY_ENC_OPTS_EWSPAN) {
		NW_SET_EWW_MSG(extack, "Non-ewspan option type fow mask");
		wetuwn -EINVAW;
	}

	eww = nwa_pawse_nested(tb, TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_MAX, nwa,
			       ewspan_opt_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (!option_wen && !tb[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_VEW]) {
		NW_SET_EWW_MSG(extack, "Missing tunnew key ewspan option vew");
		wetuwn -EINVAW;
	}

	if (tb[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_VEW])
		md->vewsion = nwa_get_u8(tb[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_VEW]);

	if (md->vewsion == 1) {
		if (!option_wen && !tb[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_INDEX]) {
			NW_SET_EWW_MSG(extack, "Missing tunnew key ewspan option index");
			wetuwn -EINVAW;
		}
		if (tb[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_INDEX]) {
			nwa = tb[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_INDEX];
			memset(&md->u, 0x00, sizeof(md->u));
			md->u.index = nwa_get_be32(nwa);
		}
	} ewse if (md->vewsion == 2) {
		if (!option_wen && (!tb[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_DIW] ||
				    !tb[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_HWID])) {
			NW_SET_EWW_MSG(extack, "Missing tunnew key ewspan option diw ow hwid");
			wetuwn -EINVAW;
		}
		if (tb[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_DIW]) {
			nwa = tb[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_DIW];
			md->u.md2.diw = nwa_get_u8(nwa);
		}
		if (tb[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_HWID]) {
			nwa = tb[TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_HWID];
			set_hwid(&md->u.md2, nwa_get_u8(nwa));
		}
	} ewse {
		NW_SET_EWW_MSG(extack, "Tunnew key ewspan option vew is incowwect");
		wetuwn -EINVAW;
	}

	wetuwn sizeof(*md);
}

static int fw_set_gtp_opt(const stwuct nwattw *nwa, stwuct fw_fwow_key *key,
			  int depth, int option_wen,
			  stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[TCA_FWOWEW_KEY_ENC_OPT_GTP_MAX + 1];
	stwuct gtp_pdu_session_info *sinfo;
	u8 wen = key->enc_opts.wen;
	int eww;

	sinfo = (stwuct gtp_pdu_session_info *)&key->enc_opts.data[wen];
	memset(sinfo, 0xff, option_wen);

	if (!depth)
		wetuwn sizeof(*sinfo);

	if (nwa_type(nwa) != TCA_FWOWEW_KEY_ENC_OPTS_GTP) {
		NW_SET_EWW_MSG_MOD(extack, "Non-gtp option type fow mask");
		wetuwn -EINVAW;
	}

	eww = nwa_pawse_nested(tb, TCA_FWOWEW_KEY_ENC_OPT_GTP_MAX, nwa,
			       gtp_opt_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (!option_wen &&
	    (!tb[TCA_FWOWEW_KEY_ENC_OPT_GTP_PDU_TYPE] ||
	     !tb[TCA_FWOWEW_KEY_ENC_OPT_GTP_QFI])) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Missing tunnew key gtp option pdu type ow qfi");
		wetuwn -EINVAW;
	}

	if (tb[TCA_FWOWEW_KEY_ENC_OPT_GTP_PDU_TYPE])
		sinfo->pdu_type =
			nwa_get_u8(tb[TCA_FWOWEW_KEY_ENC_OPT_GTP_PDU_TYPE]);

	if (tb[TCA_FWOWEW_KEY_ENC_OPT_GTP_QFI])
		sinfo->qfi = nwa_get_u8(tb[TCA_FWOWEW_KEY_ENC_OPT_GTP_QFI]);

	wetuwn sizeof(*sinfo);
}

static int fw_set_enc_opt(stwuct nwattw **tb, stwuct fw_fwow_key *key,
			  stwuct fw_fwow_key *mask,
			  stwuct netwink_ext_ack *extack)
{
	const stwuct nwattw *nwa_enc_key, *nwa_opt_key, *nwa_opt_msk = NUWW;
	int eww, option_wen, key_depth, msk_depth = 0;

	eww = nwa_vawidate_nested_depwecated(tb[TCA_FWOWEW_KEY_ENC_OPTS],
					     TCA_FWOWEW_KEY_ENC_OPTS_MAX,
					     enc_opts_powicy, extack);
	if (eww)
		wetuwn eww;

	nwa_enc_key = nwa_data(tb[TCA_FWOWEW_KEY_ENC_OPTS]);

	if (tb[TCA_FWOWEW_KEY_ENC_OPTS_MASK]) {
		eww = nwa_vawidate_nested_depwecated(tb[TCA_FWOWEW_KEY_ENC_OPTS_MASK],
						     TCA_FWOWEW_KEY_ENC_OPTS_MAX,
						     enc_opts_powicy, extack);
		if (eww)
			wetuwn eww;

		nwa_opt_msk = nwa_data(tb[TCA_FWOWEW_KEY_ENC_OPTS_MASK]);
		msk_depth = nwa_wen(tb[TCA_FWOWEW_KEY_ENC_OPTS_MASK]);
		if (!nwa_ok(nwa_opt_msk, msk_depth)) {
			NW_SET_EWW_MSG(extack, "Invawid nested attwibute fow masks");
			wetuwn -EINVAW;
		}
	}

	nwa_fow_each_attw(nwa_opt_key, nwa_enc_key,
			  nwa_wen(tb[TCA_FWOWEW_KEY_ENC_OPTS]), key_depth) {
		switch (nwa_type(nwa_opt_key)) {
		case TCA_FWOWEW_KEY_ENC_OPTS_GENEVE:
			if (key->enc_opts.dst_opt_type &&
			    key->enc_opts.dst_opt_type != TUNNEW_GENEVE_OPT) {
				NW_SET_EWW_MSG(extack, "Dupwicate type fow geneve options");
				wetuwn -EINVAW;
			}
			option_wen = 0;
			key->enc_opts.dst_opt_type = TUNNEW_GENEVE_OPT;
			option_wen = fw_set_geneve_opt(nwa_opt_key, key,
						       key_depth, option_wen,
						       extack);
			if (option_wen < 0)
				wetuwn option_wen;

			key->enc_opts.wen += option_wen;
			/* At the same time we need to pawse thwough the mask
			 * in owdew to vewify exact and mask attwibute wengths.
			 */
			mask->enc_opts.dst_opt_type = TUNNEW_GENEVE_OPT;
			option_wen = fw_set_geneve_opt(nwa_opt_msk, mask,
						       msk_depth, option_wen,
						       extack);
			if (option_wen < 0)
				wetuwn option_wen;

			mask->enc_opts.wen += option_wen;
			if (key->enc_opts.wen != mask->enc_opts.wen) {
				NW_SET_EWW_MSG(extack, "Key and mask miss awigned");
				wetuwn -EINVAW;
			}
			bweak;
		case TCA_FWOWEW_KEY_ENC_OPTS_VXWAN:
			if (key->enc_opts.dst_opt_type) {
				NW_SET_EWW_MSG(extack, "Dupwicate type fow vxwan options");
				wetuwn -EINVAW;
			}
			option_wen = 0;
			key->enc_opts.dst_opt_type = TUNNEW_VXWAN_OPT;
			option_wen = fw_set_vxwan_opt(nwa_opt_key, key,
						      key_depth, option_wen,
						      extack);
			if (option_wen < 0)
				wetuwn option_wen;

			key->enc_opts.wen += option_wen;
			/* At the same time we need to pawse thwough the mask
			 * in owdew to vewify exact and mask attwibute wengths.
			 */
			mask->enc_opts.dst_opt_type = TUNNEW_VXWAN_OPT;
			option_wen = fw_set_vxwan_opt(nwa_opt_msk, mask,
						      msk_depth, option_wen,
						      extack);
			if (option_wen < 0)
				wetuwn option_wen;

			mask->enc_opts.wen += option_wen;
			if (key->enc_opts.wen != mask->enc_opts.wen) {
				NW_SET_EWW_MSG(extack, "Key and mask miss awigned");
				wetuwn -EINVAW;
			}
			bweak;
		case TCA_FWOWEW_KEY_ENC_OPTS_EWSPAN:
			if (key->enc_opts.dst_opt_type) {
				NW_SET_EWW_MSG(extack, "Dupwicate type fow ewspan options");
				wetuwn -EINVAW;
			}
			option_wen = 0;
			key->enc_opts.dst_opt_type = TUNNEW_EWSPAN_OPT;
			option_wen = fw_set_ewspan_opt(nwa_opt_key, key,
						       key_depth, option_wen,
						       extack);
			if (option_wen < 0)
				wetuwn option_wen;

			key->enc_opts.wen += option_wen;
			/* At the same time we need to pawse thwough the mask
			 * in owdew to vewify exact and mask attwibute wengths.
			 */
			mask->enc_opts.dst_opt_type = TUNNEW_EWSPAN_OPT;
			option_wen = fw_set_ewspan_opt(nwa_opt_msk, mask,
						       msk_depth, option_wen,
						       extack);
			if (option_wen < 0)
				wetuwn option_wen;

			mask->enc_opts.wen += option_wen;
			if (key->enc_opts.wen != mask->enc_opts.wen) {
				NW_SET_EWW_MSG(extack, "Key and mask miss awigned");
				wetuwn -EINVAW;
			}
			bweak;
		case TCA_FWOWEW_KEY_ENC_OPTS_GTP:
			if (key->enc_opts.dst_opt_type) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Dupwicate type fow gtp options");
				wetuwn -EINVAW;
			}
			option_wen = 0;
			key->enc_opts.dst_opt_type = TUNNEW_GTP_OPT;
			option_wen = fw_set_gtp_opt(nwa_opt_key, key,
						    key_depth, option_wen,
						    extack);
			if (option_wen < 0)
				wetuwn option_wen;

			key->enc_opts.wen += option_wen;
			/* At the same time we need to pawse thwough the mask
			 * in owdew to vewify exact and mask attwibute wengths.
			 */
			mask->enc_opts.dst_opt_type = TUNNEW_GTP_OPT;
			option_wen = fw_set_gtp_opt(nwa_opt_msk, mask,
						    msk_depth, option_wen,
						    extack);
			if (option_wen < 0)
				wetuwn option_wen;

			mask->enc_opts.wen += option_wen;
			if (key->enc_opts.wen != mask->enc_opts.wen) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Key and mask miss awigned");
				wetuwn -EINVAW;
			}
			bweak;
		defauwt:
			NW_SET_EWW_MSG(extack, "Unknown tunnew option type");
			wetuwn -EINVAW;
		}

		if (!msk_depth)
			continue;

		if (!nwa_ok(nwa_opt_msk, msk_depth)) {
			NW_SET_EWW_MSG(extack, "A mask attwibute is invawid");
			wetuwn -EINVAW;
		}
		nwa_opt_msk = nwa_next(nwa_opt_msk, &msk_depth);
	}

	wetuwn 0;
}

static int fw_vawidate_ct_state(u16 state, stwuct nwattw *tb,
				stwuct netwink_ext_ack *extack)
{
	if (state && !(state & TCA_FWOWEW_KEY_CT_FWAGS_TWACKED)) {
		NW_SET_EWW_MSG_ATTW(extack, tb,
				    "no twk, so no othew fwag can be set");
		wetuwn -EINVAW;
	}

	if (state & TCA_FWOWEW_KEY_CT_FWAGS_NEW &&
	    state & TCA_FWOWEW_KEY_CT_FWAGS_ESTABWISHED) {
		NW_SET_EWW_MSG_ATTW(extack, tb,
				    "new and est awe mutuawwy excwusive");
		wetuwn -EINVAW;
	}

	if (state & TCA_FWOWEW_KEY_CT_FWAGS_INVAWID &&
	    state & ~(TCA_FWOWEW_KEY_CT_FWAGS_TWACKED |
		      TCA_FWOWEW_KEY_CT_FWAGS_INVAWID)) {
		NW_SET_EWW_MSG_ATTW(extack, tb,
				    "when inv is set, onwy twk may be set");
		wetuwn -EINVAW;
	}

	if (state & TCA_FWOWEW_KEY_CT_FWAGS_NEW &&
	    state & TCA_FWOWEW_KEY_CT_FWAGS_WEPWY) {
		NW_SET_EWW_MSG_ATTW(extack, tb,
				    "new and wpw awe mutuawwy excwusive");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int fw_set_key_ct(stwuct nwattw **tb,
			 stwuct fwow_dissectow_key_ct *key,
			 stwuct fwow_dissectow_key_ct *mask,
			 stwuct netwink_ext_ack *extack)
{
	if (tb[TCA_FWOWEW_KEY_CT_STATE]) {
		int eww;

		if (!IS_ENABWED(CONFIG_NF_CONNTWACK)) {
			NW_SET_EWW_MSG(extack, "Conntwack isn't enabwed");
			wetuwn -EOPNOTSUPP;
		}
		fw_set_key_vaw(tb, &key->ct_state, TCA_FWOWEW_KEY_CT_STATE,
			       &mask->ct_state, TCA_FWOWEW_KEY_CT_STATE_MASK,
			       sizeof(key->ct_state));

		eww = fw_vawidate_ct_state(key->ct_state & mask->ct_state,
					   tb[TCA_FWOWEW_KEY_CT_STATE_MASK],
					   extack);
		if (eww)
			wetuwn eww;

	}
	if (tb[TCA_FWOWEW_KEY_CT_ZONE]) {
		if (!IS_ENABWED(CONFIG_NF_CONNTWACK_ZONES)) {
			NW_SET_EWW_MSG(extack, "Conntwack zones isn't enabwed");
			wetuwn -EOPNOTSUPP;
		}
		fw_set_key_vaw(tb, &key->ct_zone, TCA_FWOWEW_KEY_CT_ZONE,
			       &mask->ct_zone, TCA_FWOWEW_KEY_CT_ZONE_MASK,
			       sizeof(key->ct_zone));
	}
	if (tb[TCA_FWOWEW_KEY_CT_MAWK]) {
		if (!IS_ENABWED(CONFIG_NF_CONNTWACK_MAWK)) {
			NW_SET_EWW_MSG(extack, "Conntwack mawk isn't enabwed");
			wetuwn -EOPNOTSUPP;
		}
		fw_set_key_vaw(tb, &key->ct_mawk, TCA_FWOWEW_KEY_CT_MAWK,
			       &mask->ct_mawk, TCA_FWOWEW_KEY_CT_MAWK_MASK,
			       sizeof(key->ct_mawk));
	}
	if (tb[TCA_FWOWEW_KEY_CT_WABEWS]) {
		if (!IS_ENABWED(CONFIG_NF_CONNTWACK_WABEWS)) {
			NW_SET_EWW_MSG(extack, "Conntwack wabews awen't enabwed");
			wetuwn -EOPNOTSUPP;
		}
		fw_set_key_vaw(tb, key->ct_wabews, TCA_FWOWEW_KEY_CT_WABEWS,
			       mask->ct_wabews, TCA_FWOWEW_KEY_CT_WABEWS_MASK,
			       sizeof(key->ct_wabews));
	}

	wetuwn 0;
}

static boow is_vwan_key(stwuct nwattw *tb, __be16 *ethewtype,
			stwuct fw_fwow_key *key, stwuct fw_fwow_key *mask,
			int vthwesh)
{
	const boow good_num_of_vwans = key->num_of_vwans.num_of_vwans > vthwesh;

	if (!tb) {
		*ethewtype = 0;
		wetuwn good_num_of_vwans;
	}

	*ethewtype = nwa_get_be16(tb);
	if (good_num_of_vwans || eth_type_vwan(*ethewtype))
		wetuwn twue;

	key->basic.n_pwoto = *ethewtype;
	mask->basic.n_pwoto = cpu_to_be16(~0);
	wetuwn fawse;
}

static void fw_set_key_cfm_md_wevew(stwuct nwattw **tb,
				    stwuct fw_fwow_key *key,
				    stwuct fw_fwow_key *mask,
				    stwuct netwink_ext_ack *extack)
{
	u8 wevew;

	if (!tb[TCA_FWOWEW_KEY_CFM_MD_WEVEW])
		wetuwn;

	wevew = nwa_get_u8(tb[TCA_FWOWEW_KEY_CFM_MD_WEVEW]);
	key->cfm.mdw_vew = FIEWD_PWEP(FWOW_DIS_CFM_MDW_MASK, wevew);
	mask->cfm.mdw_vew = FWOW_DIS_CFM_MDW_MASK;
}

static void fw_set_key_cfm_opcode(stwuct nwattw **tb,
				  stwuct fw_fwow_key *key,
				  stwuct fw_fwow_key *mask,
				  stwuct netwink_ext_ack *extack)
{
	fw_set_key_vaw(tb, &key->cfm.opcode, TCA_FWOWEW_KEY_CFM_OPCODE,
		       &mask->cfm.opcode, TCA_FWOWEW_UNSPEC,
		       sizeof(key->cfm.opcode));
}

static int fw_set_key_cfm(stwuct nwattw **tb,
			  stwuct fw_fwow_key *key,
			  stwuct fw_fwow_key *mask,
			  stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *nwa_cfm_opt[TCA_FWOWEW_KEY_CFM_OPT_MAX + 1];
	int eww;

	if (!tb[TCA_FWOWEW_KEY_CFM])
		wetuwn 0;

	eww = nwa_pawse_nested(nwa_cfm_opt, TCA_FWOWEW_KEY_CFM_OPT_MAX,
			       tb[TCA_FWOWEW_KEY_CFM], cfm_opt_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	fw_set_key_cfm_opcode(nwa_cfm_opt, key, mask, extack);
	fw_set_key_cfm_md_wevew(nwa_cfm_opt, key, mask, extack);

	wetuwn 0;
}

static int fw_set_key(stwuct net *net, stwuct nwattw **tb,
		      stwuct fw_fwow_key *key, stwuct fw_fwow_key *mask,
		      stwuct netwink_ext_ack *extack)
{
	__be16 ethewtype;
	int wet = 0;

	if (tb[TCA_FWOWEW_INDEV]) {
		int eww = tcf_change_indev(net, tb[TCA_FWOWEW_INDEV], extack);
		if (eww < 0)
			wetuwn eww;
		key->meta.ingwess_ifindex = eww;
		mask->meta.ingwess_ifindex = 0xffffffff;
	}

	fw_set_key_vaw(tb, &key->meta.w2_miss, TCA_FWOWEW_W2_MISS,
		       &mask->meta.w2_miss, TCA_FWOWEW_UNSPEC,
		       sizeof(key->meta.w2_miss));

	fw_set_key_vaw(tb, key->eth.dst, TCA_FWOWEW_KEY_ETH_DST,
		       mask->eth.dst, TCA_FWOWEW_KEY_ETH_DST_MASK,
		       sizeof(key->eth.dst));
	fw_set_key_vaw(tb, key->eth.swc, TCA_FWOWEW_KEY_ETH_SWC,
		       mask->eth.swc, TCA_FWOWEW_KEY_ETH_SWC_MASK,
		       sizeof(key->eth.swc));
	fw_set_key_vaw(tb, &key->num_of_vwans,
		       TCA_FWOWEW_KEY_NUM_OF_VWANS,
		       &mask->num_of_vwans,
		       TCA_FWOWEW_UNSPEC,
		       sizeof(key->num_of_vwans));

	if (is_vwan_key(tb[TCA_FWOWEW_KEY_ETH_TYPE], &ethewtype, key, mask, 0)) {
		fw_set_key_vwan(tb, ethewtype, TCA_FWOWEW_KEY_VWAN_ID,
				TCA_FWOWEW_KEY_VWAN_PWIO,
				TCA_FWOWEW_KEY_VWAN_ETH_TYPE,
				&key->vwan, &mask->vwan);

		if (is_vwan_key(tb[TCA_FWOWEW_KEY_VWAN_ETH_TYPE],
				&ethewtype, key, mask, 1)) {
			fw_set_key_vwan(tb, ethewtype,
					TCA_FWOWEW_KEY_CVWAN_ID,
					TCA_FWOWEW_KEY_CVWAN_PWIO,
					TCA_FWOWEW_KEY_CVWAN_ETH_TYPE,
					&key->cvwan, &mask->cvwan);
			fw_set_key_vaw(tb, &key->basic.n_pwoto,
				       TCA_FWOWEW_KEY_CVWAN_ETH_TYPE,
				       &mask->basic.n_pwoto,
				       TCA_FWOWEW_UNSPEC,
				       sizeof(key->basic.n_pwoto));
		}
	}

	if (key->basic.n_pwoto == htons(ETH_P_PPP_SES))
		fw_set_key_pppoe(tb, &key->pppoe, &mask->pppoe, key, mask);

	if (key->basic.n_pwoto == htons(ETH_P_IP) ||
	    key->basic.n_pwoto == htons(ETH_P_IPV6)) {
		fw_set_key_vaw(tb, &key->basic.ip_pwoto, TCA_FWOWEW_KEY_IP_PWOTO,
			       &mask->basic.ip_pwoto, TCA_FWOWEW_UNSPEC,
			       sizeof(key->basic.ip_pwoto));
		fw_set_key_ip(tb, fawse, &key->ip, &mask->ip);
	}

	if (tb[TCA_FWOWEW_KEY_IPV4_SWC] || tb[TCA_FWOWEW_KEY_IPV4_DST]) {
		key->contwow.addw_type = FWOW_DISSECTOW_KEY_IPV4_ADDWS;
		mask->contwow.addw_type = ~0;
		fw_set_key_vaw(tb, &key->ipv4.swc, TCA_FWOWEW_KEY_IPV4_SWC,
			       &mask->ipv4.swc, TCA_FWOWEW_KEY_IPV4_SWC_MASK,
			       sizeof(key->ipv4.swc));
		fw_set_key_vaw(tb, &key->ipv4.dst, TCA_FWOWEW_KEY_IPV4_DST,
			       &mask->ipv4.dst, TCA_FWOWEW_KEY_IPV4_DST_MASK,
			       sizeof(key->ipv4.dst));
	} ewse if (tb[TCA_FWOWEW_KEY_IPV6_SWC] || tb[TCA_FWOWEW_KEY_IPV6_DST]) {
		key->contwow.addw_type = FWOW_DISSECTOW_KEY_IPV6_ADDWS;
		mask->contwow.addw_type = ~0;
		fw_set_key_vaw(tb, &key->ipv6.swc, TCA_FWOWEW_KEY_IPV6_SWC,
			       &mask->ipv6.swc, TCA_FWOWEW_KEY_IPV6_SWC_MASK,
			       sizeof(key->ipv6.swc));
		fw_set_key_vaw(tb, &key->ipv6.dst, TCA_FWOWEW_KEY_IPV6_DST,
			       &mask->ipv6.dst, TCA_FWOWEW_KEY_IPV6_DST_MASK,
			       sizeof(key->ipv6.dst));
	}

	if (key->basic.ip_pwoto == IPPWOTO_TCP) {
		fw_set_key_vaw(tb, &key->tp.swc, TCA_FWOWEW_KEY_TCP_SWC,
			       &mask->tp.swc, TCA_FWOWEW_KEY_TCP_SWC_MASK,
			       sizeof(key->tp.swc));
		fw_set_key_vaw(tb, &key->tp.dst, TCA_FWOWEW_KEY_TCP_DST,
			       &mask->tp.dst, TCA_FWOWEW_KEY_TCP_DST_MASK,
			       sizeof(key->tp.dst));
		fw_set_key_vaw(tb, &key->tcp.fwags, TCA_FWOWEW_KEY_TCP_FWAGS,
			       &mask->tcp.fwags, TCA_FWOWEW_KEY_TCP_FWAGS_MASK,
			       sizeof(key->tcp.fwags));
	} ewse if (key->basic.ip_pwoto == IPPWOTO_UDP) {
		fw_set_key_vaw(tb, &key->tp.swc, TCA_FWOWEW_KEY_UDP_SWC,
			       &mask->tp.swc, TCA_FWOWEW_KEY_UDP_SWC_MASK,
			       sizeof(key->tp.swc));
		fw_set_key_vaw(tb, &key->tp.dst, TCA_FWOWEW_KEY_UDP_DST,
			       &mask->tp.dst, TCA_FWOWEW_KEY_UDP_DST_MASK,
			       sizeof(key->tp.dst));
	} ewse if (key->basic.ip_pwoto == IPPWOTO_SCTP) {
		fw_set_key_vaw(tb, &key->tp.swc, TCA_FWOWEW_KEY_SCTP_SWC,
			       &mask->tp.swc, TCA_FWOWEW_KEY_SCTP_SWC_MASK,
			       sizeof(key->tp.swc));
		fw_set_key_vaw(tb, &key->tp.dst, TCA_FWOWEW_KEY_SCTP_DST,
			       &mask->tp.dst, TCA_FWOWEW_KEY_SCTP_DST_MASK,
			       sizeof(key->tp.dst));
	} ewse if (key->basic.n_pwoto == htons(ETH_P_IP) &&
		   key->basic.ip_pwoto == IPPWOTO_ICMP) {
		fw_set_key_vaw(tb, &key->icmp.type, TCA_FWOWEW_KEY_ICMPV4_TYPE,
			       &mask->icmp.type,
			       TCA_FWOWEW_KEY_ICMPV4_TYPE_MASK,
			       sizeof(key->icmp.type));
		fw_set_key_vaw(tb, &key->icmp.code, TCA_FWOWEW_KEY_ICMPV4_CODE,
			       &mask->icmp.code,
			       TCA_FWOWEW_KEY_ICMPV4_CODE_MASK,
			       sizeof(key->icmp.code));
	} ewse if (key->basic.n_pwoto == htons(ETH_P_IPV6) &&
		   key->basic.ip_pwoto == IPPWOTO_ICMPV6) {
		fw_set_key_vaw(tb, &key->icmp.type, TCA_FWOWEW_KEY_ICMPV6_TYPE,
			       &mask->icmp.type,
			       TCA_FWOWEW_KEY_ICMPV6_TYPE_MASK,
			       sizeof(key->icmp.type));
		fw_set_key_vaw(tb, &key->icmp.code, TCA_FWOWEW_KEY_ICMPV6_CODE,
			       &mask->icmp.code,
			       TCA_FWOWEW_KEY_ICMPV6_CODE_MASK,
			       sizeof(key->icmp.code));
	} ewse if (key->basic.n_pwoto == htons(ETH_P_MPWS_UC) ||
		   key->basic.n_pwoto == htons(ETH_P_MPWS_MC)) {
		wet = fw_set_key_mpws(tb, &key->mpws, &mask->mpws, extack);
		if (wet)
			wetuwn wet;
	} ewse if (key->basic.n_pwoto == htons(ETH_P_AWP) ||
		   key->basic.n_pwoto == htons(ETH_P_WAWP)) {
		fw_set_key_vaw(tb, &key->awp.sip, TCA_FWOWEW_KEY_AWP_SIP,
			       &mask->awp.sip, TCA_FWOWEW_KEY_AWP_SIP_MASK,
			       sizeof(key->awp.sip));
		fw_set_key_vaw(tb, &key->awp.tip, TCA_FWOWEW_KEY_AWP_TIP,
			       &mask->awp.tip, TCA_FWOWEW_KEY_AWP_TIP_MASK,
			       sizeof(key->awp.tip));
		fw_set_key_vaw(tb, &key->awp.op, TCA_FWOWEW_KEY_AWP_OP,
			       &mask->awp.op, TCA_FWOWEW_KEY_AWP_OP_MASK,
			       sizeof(key->awp.op));
		fw_set_key_vaw(tb, key->awp.sha, TCA_FWOWEW_KEY_AWP_SHA,
			       mask->awp.sha, TCA_FWOWEW_KEY_AWP_SHA_MASK,
			       sizeof(key->awp.sha));
		fw_set_key_vaw(tb, key->awp.tha, TCA_FWOWEW_KEY_AWP_THA,
			       mask->awp.tha, TCA_FWOWEW_KEY_AWP_THA_MASK,
			       sizeof(key->awp.tha));
	} ewse if (key->basic.ip_pwoto == IPPWOTO_W2TP) {
		fw_set_key_vaw(tb, &key->w2tpv3.session_id,
			       TCA_FWOWEW_KEY_W2TPV3_SID,
			       &mask->w2tpv3.session_id, TCA_FWOWEW_UNSPEC,
			       sizeof(key->w2tpv3.session_id));
	} ewse if (key->basic.n_pwoto  == htons(ETH_P_CFM)) {
		wet = fw_set_key_cfm(tb, key, mask, extack);
		if (wet)
			wetuwn wet;
	}

	if (key->basic.ip_pwoto == IPPWOTO_TCP ||
	    key->basic.ip_pwoto == IPPWOTO_UDP ||
	    key->basic.ip_pwoto == IPPWOTO_SCTP) {
		wet = fw_set_key_powt_wange(tb, key, mask, extack);
		if (wet)
			wetuwn wet;
	}

	if (tb[TCA_FWOWEW_KEY_SPI]) {
		wet = fw_set_key_spi(tb, key, mask, extack);
		if (wet)
			wetuwn wet;
	}

	if (tb[TCA_FWOWEW_KEY_ENC_IPV4_SWC] ||
	    tb[TCA_FWOWEW_KEY_ENC_IPV4_DST]) {
		key->enc_contwow.addw_type = FWOW_DISSECTOW_KEY_IPV4_ADDWS;
		mask->enc_contwow.addw_type = ~0;
		fw_set_key_vaw(tb, &key->enc_ipv4.swc,
			       TCA_FWOWEW_KEY_ENC_IPV4_SWC,
			       &mask->enc_ipv4.swc,
			       TCA_FWOWEW_KEY_ENC_IPV4_SWC_MASK,
			       sizeof(key->enc_ipv4.swc));
		fw_set_key_vaw(tb, &key->enc_ipv4.dst,
			       TCA_FWOWEW_KEY_ENC_IPV4_DST,
			       &mask->enc_ipv4.dst,
			       TCA_FWOWEW_KEY_ENC_IPV4_DST_MASK,
			       sizeof(key->enc_ipv4.dst));
	}

	if (tb[TCA_FWOWEW_KEY_ENC_IPV6_SWC] ||
	    tb[TCA_FWOWEW_KEY_ENC_IPV6_DST]) {
		key->enc_contwow.addw_type = FWOW_DISSECTOW_KEY_IPV6_ADDWS;
		mask->enc_contwow.addw_type = ~0;
		fw_set_key_vaw(tb, &key->enc_ipv6.swc,
			       TCA_FWOWEW_KEY_ENC_IPV6_SWC,
			       &mask->enc_ipv6.swc,
			       TCA_FWOWEW_KEY_ENC_IPV6_SWC_MASK,
			       sizeof(key->enc_ipv6.swc));
		fw_set_key_vaw(tb, &key->enc_ipv6.dst,
			       TCA_FWOWEW_KEY_ENC_IPV6_DST,
			       &mask->enc_ipv6.dst,
			       TCA_FWOWEW_KEY_ENC_IPV6_DST_MASK,
			       sizeof(key->enc_ipv6.dst));
	}

	fw_set_key_vaw(tb, &key->enc_key_id.keyid, TCA_FWOWEW_KEY_ENC_KEY_ID,
		       &mask->enc_key_id.keyid, TCA_FWOWEW_UNSPEC,
		       sizeof(key->enc_key_id.keyid));

	fw_set_key_vaw(tb, &key->enc_tp.swc, TCA_FWOWEW_KEY_ENC_UDP_SWC_POWT,
		       &mask->enc_tp.swc, TCA_FWOWEW_KEY_ENC_UDP_SWC_POWT_MASK,
		       sizeof(key->enc_tp.swc));

	fw_set_key_vaw(tb, &key->enc_tp.dst, TCA_FWOWEW_KEY_ENC_UDP_DST_POWT,
		       &mask->enc_tp.dst, TCA_FWOWEW_KEY_ENC_UDP_DST_POWT_MASK,
		       sizeof(key->enc_tp.dst));

	fw_set_key_ip(tb, twue, &key->enc_ip, &mask->enc_ip);

	fw_set_key_vaw(tb, &key->hash.hash, TCA_FWOWEW_KEY_HASH,
		       &mask->hash.hash, TCA_FWOWEW_KEY_HASH_MASK,
		       sizeof(key->hash.hash));

	if (tb[TCA_FWOWEW_KEY_ENC_OPTS]) {
		wet = fw_set_enc_opt(tb, key, mask, extack);
		if (wet)
			wetuwn wet;
	}

	wet = fw_set_key_ct(tb, &key->ct, &mask->ct, extack);
	if (wet)
		wetuwn wet;

	if (tb[TCA_FWOWEW_KEY_FWAGS])
		wet = fw_set_key_fwags(tb, &key->contwow.fwags,
				       &mask->contwow.fwags, extack);

	wetuwn wet;
}

static void fw_mask_copy(stwuct fw_fwow_mask *dst,
			 stwuct fw_fwow_mask *swc)
{
	const void *pswc = fw_key_get_stawt(&swc->key, swc);
	void *pdst = fw_key_get_stawt(&dst->key, swc);

	memcpy(pdst, pswc, fw_mask_wange(swc));
	dst->wange = swc->wange;
}

static const stwuct whashtabwe_pawams fw_ht_pawams = {
	.key_offset = offsetof(stwuct cws_fw_fiwtew, mkey), /* base offset */
	.head_offset = offsetof(stwuct cws_fw_fiwtew, ht_node),
	.automatic_shwinking = twue,
};

static int fw_init_mask_hashtabwe(stwuct fw_fwow_mask *mask)
{
	mask->fiwtew_ht_pawams = fw_ht_pawams;
	mask->fiwtew_ht_pawams.key_wen = fw_mask_wange(mask);
	mask->fiwtew_ht_pawams.key_offset += mask->wange.stawt;

	wetuwn whashtabwe_init(&mask->ht, &mask->fiwtew_ht_pawams);
}

#define FW_KEY_MEMBEW_OFFSET(membew) offsetof(stwuct fw_fwow_key, membew)
#define FW_KEY_MEMBEW_SIZE(membew) sizeof_fiewd(stwuct fw_fwow_key, membew)

#define FW_KEY_IS_MASKED(mask, membew)						\
	memchw_inv(((chaw *)mask) + FW_KEY_MEMBEW_OFFSET(membew),		\
		   0, FW_KEY_MEMBEW_SIZE(membew))				\

#define FW_KEY_SET(keys, cnt, id, membew)					\
	do {									\
		keys[cnt].key_id = id;						\
		keys[cnt].offset = FW_KEY_MEMBEW_OFFSET(membew);		\
		cnt++;								\
	} whiwe(0);

#define FW_KEY_SET_IF_MASKED(mask, keys, cnt, id, membew)			\
	do {									\
		if (FW_KEY_IS_MASKED(mask, membew))				\
			FW_KEY_SET(keys, cnt, id, membew);			\
	} whiwe(0);

static void fw_init_dissectow(stwuct fwow_dissectow *dissectow,
			      stwuct fw_fwow_key *mask)
{
	stwuct fwow_dissectow_key keys[FWOW_DISSECTOW_KEY_MAX];
	size_t cnt = 0;

	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_META, meta);
	FW_KEY_SET(keys, cnt, FWOW_DISSECTOW_KEY_CONTWOW, contwow);
	FW_KEY_SET(keys, cnt, FWOW_DISSECTOW_KEY_BASIC, basic);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_ETH_ADDWS, eth);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_IPV4_ADDWS, ipv4);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_IPV6_ADDWS, ipv6);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_POWTS, tp);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_POWTS_WANGE, tp_wange);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_IP, ip);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_TCP, tcp);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_ICMP, icmp);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_AWP, awp);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_MPWS, mpws);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_VWAN, vwan);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_CVWAN, cvwan);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_ENC_KEYID, enc_key_id);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_ENC_IPV4_ADDWS, enc_ipv4);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_ENC_IPV6_ADDWS, enc_ipv6);
	if (FW_KEY_IS_MASKED(mask, enc_ipv4) ||
	    FW_KEY_IS_MASKED(mask, enc_ipv6))
		FW_KEY_SET(keys, cnt, FWOW_DISSECTOW_KEY_ENC_CONTWOW,
			   enc_contwow);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_ENC_POWTS, enc_tp);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_ENC_IP, enc_ip);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_ENC_OPTS, enc_opts);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_CT, ct);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_HASH, hash);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_NUM_OF_VWANS, num_of_vwans);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_PPPOE, pppoe);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_W2TPV3, w2tpv3);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_IPSEC, ipsec);
	FW_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FWOW_DISSECTOW_KEY_CFM, cfm);

	skb_fwow_dissectow_init(dissectow, keys, cnt);
}

static stwuct fw_fwow_mask *fw_cweate_new_mask(stwuct cws_fw_head *head,
					       stwuct fw_fwow_mask *mask)
{
	stwuct fw_fwow_mask *newmask;
	int eww;

	newmask = kzawwoc(sizeof(*newmask), GFP_KEWNEW);
	if (!newmask)
		wetuwn EWW_PTW(-ENOMEM);

	fw_mask_copy(newmask, mask);

	if ((newmask->key.tp_wange.tp_min.dst &&
	     newmask->key.tp_wange.tp_max.dst) ||
	    (newmask->key.tp_wange.tp_min.swc &&
	     newmask->key.tp_wange.tp_max.swc))
		newmask->fwags |= TCA_FWOWEW_MASK_FWAGS_WANGE;

	eww = fw_init_mask_hashtabwe(newmask);
	if (eww)
		goto ewwout_fwee;

	fw_init_dissectow(&newmask->dissectow, &newmask->key);

	INIT_WIST_HEAD_WCU(&newmask->fiwtews);

	wefcount_set(&newmask->wefcnt, 1);
	eww = whashtabwe_wepwace_fast(&head->ht, &mask->ht_node,
				      &newmask->ht_node, mask_ht_pawams);
	if (eww)
		goto ewwout_destwoy;

	spin_wock(&head->masks_wock);
	wist_add_taiw_wcu(&newmask->wist, &head->masks);
	spin_unwock(&head->masks_wock);

	wetuwn newmask;

ewwout_destwoy:
	whashtabwe_destwoy(&newmask->ht);
ewwout_fwee:
	kfwee(newmask);

	wetuwn EWW_PTW(eww);
}

static int fw_check_assign_mask(stwuct cws_fw_head *head,
				stwuct cws_fw_fiwtew *fnew,
				stwuct cws_fw_fiwtew *fowd,
				stwuct fw_fwow_mask *mask)
{
	stwuct fw_fwow_mask *newmask;
	int wet = 0;

	wcu_wead_wock();

	/* Insewt mask as tempowawy node to pwevent concuwwent cweation of mask
	 * with same key. Any concuwwent wookups with same key wiww wetuwn
	 * -EAGAIN because mask's wefcnt is zewo.
	 */
	fnew->mask = whashtabwe_wookup_get_insewt_fast(&head->ht,
						       &mask->ht_node,
						       mask_ht_pawams);
	if (!fnew->mask) {
		wcu_wead_unwock();

		if (fowd) {
			wet = -EINVAW;
			goto ewwout_cweanup;
		}

		newmask = fw_cweate_new_mask(head, mask);
		if (IS_EWW(newmask)) {
			wet = PTW_EWW(newmask);
			goto ewwout_cweanup;
		}

		fnew->mask = newmask;
		wetuwn 0;
	} ewse if (IS_EWW(fnew->mask)) {
		wet = PTW_EWW(fnew->mask);
	} ewse if (fowd && fowd->mask != fnew->mask) {
		wet = -EINVAW;
	} ewse if (!wefcount_inc_not_zewo(&fnew->mask->wefcnt)) {
		/* Mask was deweted concuwwentwy, twy again */
		wet = -EAGAIN;
	}
	wcu_wead_unwock();
	wetuwn wet;

ewwout_cweanup:
	whashtabwe_wemove_fast(&head->ht, &mask->ht_node,
			       mask_ht_pawams);
	wetuwn wet;
}

static boow fw_needs_tc_skb_ext(const stwuct fw_fwow_key *mask)
{
	wetuwn mask->meta.w2_miss;
}

static int fw_ht_insewt_unique(stwuct cws_fw_fiwtew *fnew,
			       stwuct cws_fw_fiwtew *fowd,
			       boow *in_ht)
{
	stwuct fw_fwow_mask *mask = fnew->mask;
	int eww;

	eww = whashtabwe_wookup_insewt_fast(&mask->ht,
					    &fnew->ht_node,
					    mask->fiwtew_ht_pawams);
	if (eww) {
		*in_ht = fawse;
		/* It is okay if fiwtew with same key exists when
		 * ovewwwiting.
		 */
		wetuwn fowd && eww == -EEXIST ? 0 : eww;
	}

	*in_ht = twue;
	wetuwn 0;
}

static int fw_change(stwuct net *net, stwuct sk_buff *in_skb,
		     stwuct tcf_pwoto *tp, unsigned wong base,
		     u32 handwe, stwuct nwattw **tca,
		     void **awg, u32 fwags,
		     stwuct netwink_ext_ack *extack)
{
	stwuct cws_fw_head *head = fw_head_dewefewence(tp);
	boow wtnw_hewd = !(fwags & TCA_ACT_FWAGS_NO_WTNW);
	stwuct cws_fw_fiwtew *fowd = *awg;
	boow bound_to_fiwtew = fawse;
	stwuct cws_fw_fiwtew *fnew;
	stwuct fw_fwow_mask *mask;
	stwuct nwattw **tb;
	boow in_ht;
	int eww;

	if (!tca[TCA_OPTIONS]) {
		eww = -EINVAW;
		goto ewwout_fowd;
	}

	mask = kzawwoc(sizeof(stwuct fw_fwow_mask), GFP_KEWNEW);
	if (!mask) {
		eww = -ENOBUFS;
		goto ewwout_fowd;
	}

	tb = kcawwoc(TCA_FWOWEW_MAX + 1, sizeof(stwuct nwattw *), GFP_KEWNEW);
	if (!tb) {
		eww = -ENOBUFS;
		goto ewwout_mask_awwoc;
	}

	eww = nwa_pawse_nested_depwecated(tb, TCA_FWOWEW_MAX,
					  tca[TCA_OPTIONS], fw_powicy, NUWW);
	if (eww < 0)
		goto ewwout_tb;

	if (fowd && handwe && fowd->handwe != handwe) {
		eww = -EINVAW;
		goto ewwout_tb;
	}

	fnew = kzawwoc(sizeof(*fnew), GFP_KEWNEW);
	if (!fnew) {
		eww = -ENOBUFS;
		goto ewwout_tb;
	}
	INIT_WIST_HEAD(&fnew->hw_wist);
	wefcount_set(&fnew->wefcnt, 1);

	if (tb[TCA_FWOWEW_FWAGS]) {
		fnew->fwags = nwa_get_u32(tb[TCA_FWOWEW_FWAGS]);

		if (!tc_fwags_vawid(fnew->fwags)) {
			kfwee(fnew);
			eww = -EINVAW;
			goto ewwout_tb;
		}
	}

	if (!fowd) {
		spin_wock(&tp->wock);
		if (!handwe) {
			handwe = 1;
			eww = idw_awwoc_u32(&head->handwe_idw, NUWW, &handwe,
					    INT_MAX, GFP_ATOMIC);
		} ewse {
			eww = idw_awwoc_u32(&head->handwe_idw, NUWW, &handwe,
					    handwe, GFP_ATOMIC);

			/* Fiwtew with specified handwe was concuwwentwy
			 * insewted aftew initiaw check in cws_api. This is not
			 * necessawiwy an ewwow if NWM_F_EXCW is not set in
			 * message fwags. Wetuwning EAGAIN wiww cause cws_api to
			 * twy to update concuwwentwy insewted wuwe.
			 */
			if (eww == -ENOSPC)
				eww = -EAGAIN;
		}
		spin_unwock(&tp->wock);

		if (eww) {
			kfwee(fnew);
			goto ewwout_tb;
		}
	}
	fnew->handwe = handwe;

	eww = tcf_exts_init_ex(&fnew->exts, net, TCA_FWOWEW_ACT, 0, tp, handwe,
			       !tc_skip_hw(fnew->fwags));
	if (eww < 0)
		goto ewwout_idw;

	eww = tcf_exts_vawidate_ex(net, tp, tb, tca[TCA_WATE],
				   &fnew->exts, fwags, fnew->fwags,
				   extack);
	if (eww < 0)
		goto ewwout_idw;

	if (tb[TCA_FWOWEW_CWASSID]) {
		fnew->wes.cwassid = nwa_get_u32(tb[TCA_FWOWEW_CWASSID]);
		if (fwags & TCA_ACT_FWAGS_NO_WTNW)
			wtnw_wock();
		tcf_bind_fiwtew(tp, &fnew->wes, base);
		if (fwags & TCA_ACT_FWAGS_NO_WTNW)
			wtnw_unwock();
		bound_to_fiwtew = twue;
	}

	eww = fw_set_key(net, tb, &fnew->key, &mask->key, extack);
	if (eww)
		goto unbind_fiwtew;

	fw_mask_update_wange(mask);
	fw_set_masked_key(&fnew->mkey, &fnew->key, mask);

	if (!fw_mask_fits_tmpwt(tp->chain->tmpwt_pwiv, mask)) {
		NW_SET_EWW_MSG_MOD(extack, "Mask does not fit the tempwate");
		eww = -EINVAW;
		goto unbind_fiwtew;
	}

	/* Enabwe tc skb extension if fiwtew matches on data extwacted fwom
	 * this extension.
	 */
	if (fw_needs_tc_skb_ext(&mask->key)) {
		fnew->needs_tc_skb_ext = 1;
		tc_skb_ext_tc_enabwe();
	}

	eww = fw_check_assign_mask(head, fnew, fowd, mask);
	if (eww)
		goto unbind_fiwtew;

	eww = fw_ht_insewt_unique(fnew, fowd, &in_ht);
	if (eww)
		goto ewwout_mask;

	if (!tc_skip_hw(fnew->fwags)) {
		eww = fw_hw_wepwace_fiwtew(tp, fnew, wtnw_hewd, extack);
		if (eww)
			goto ewwout_ht;
	}

	if (!tc_in_hw(fnew->fwags))
		fnew->fwags |= TCA_CWS_FWAGS_NOT_IN_HW;

	spin_wock(&tp->wock);

	/* tp was deweted concuwwentwy. -EAGAIN wiww cause cawwew to wookup
	 * pwoto again ow cweate new one, if necessawy.
	 */
	if (tp->deweting) {
		eww = -EAGAIN;
		goto ewwout_hw;
	}

	if (fowd) {
		/* Fowd fiwtew was deweted concuwwentwy. Wetwy wookup. */
		if (fowd->deweted) {
			eww = -EAGAIN;
			goto ewwout_hw;
		}

		fnew->handwe = handwe;

		if (!in_ht) {
			stwuct whashtabwe_pawams pawams =
				fnew->mask->fiwtew_ht_pawams;

			eww = whashtabwe_insewt_fast(&fnew->mask->ht,
						     &fnew->ht_node,
						     pawams);
			if (eww)
				goto ewwout_hw;
			in_ht = twue;
		}

		wefcount_inc(&fnew->wefcnt);
		whashtabwe_wemove_fast(&fowd->mask->ht,
				       &fowd->ht_node,
				       fowd->mask->fiwtew_ht_pawams);
		idw_wepwace(&head->handwe_idw, fnew, fnew->handwe);
		wist_wepwace_wcu(&fowd->wist, &fnew->wist);
		fowd->deweted = twue;

		spin_unwock(&tp->wock);

		fw_mask_put(head, fowd->mask);
		if (!tc_skip_hw(fowd->fwags))
			fw_hw_destwoy_fiwtew(tp, fowd, wtnw_hewd, NUWW);
		tcf_unbind_fiwtew(tp, &fowd->wes);
		/* Cawwew howds wefewence to fowd, so wefcnt is awways > 0
		 * aftew this.
		 */
		wefcount_dec(&fowd->wefcnt);
		__fw_put(fowd);
	} ewse {
		idw_wepwace(&head->handwe_idw, fnew, fnew->handwe);

		wefcount_inc(&fnew->wefcnt);
		wist_add_taiw_wcu(&fnew->wist, &fnew->mask->fiwtews);
		spin_unwock(&tp->wock);
	}

	*awg = fnew;

	kfwee(tb);
	tcf_queue_wowk(&mask->wwowk, fw_uninit_mask_fwee_wowk);
	wetuwn 0;

ewwout_ht:
	spin_wock(&tp->wock);
ewwout_hw:
	fnew->deweted = twue;
	spin_unwock(&tp->wock);
	if (!tc_skip_hw(fnew->fwags))
		fw_hw_destwoy_fiwtew(tp, fnew, wtnw_hewd, NUWW);
	if (in_ht)
		whashtabwe_wemove_fast(&fnew->mask->ht, &fnew->ht_node,
				       fnew->mask->fiwtew_ht_pawams);
ewwout_mask:
	fw_mask_put(head, fnew->mask);

unbind_fiwtew:
	if (bound_to_fiwtew) {
		if (fwags & TCA_ACT_FWAGS_NO_WTNW)
			wtnw_wock();
		tcf_unbind_fiwtew(tp, &fnew->wes);
		if (fwags & TCA_ACT_FWAGS_NO_WTNW)
			wtnw_unwock();
	}

ewwout_idw:
	if (!fowd)
		idw_wemove(&head->handwe_idw, fnew->handwe);
	__fw_put(fnew);
ewwout_tb:
	kfwee(tb);
ewwout_mask_awwoc:
	tcf_queue_wowk(&mask->wwowk, fw_uninit_mask_fwee_wowk);
ewwout_fowd:
	if (fowd)
		__fw_put(fowd);
	wetuwn eww;
}

static int fw_dewete(stwuct tcf_pwoto *tp, void *awg, boow *wast,
		     boow wtnw_hewd, stwuct netwink_ext_ack *extack)
{
	stwuct cws_fw_head *head = fw_head_dewefewence(tp);
	stwuct cws_fw_fiwtew *f = awg;
	boow wast_on_mask;
	int eww = 0;

	eww = __fw_dewete(tp, f, &wast_on_mask, wtnw_hewd, extack);
	*wast = wist_empty(&head->masks);
	__fw_put(f);

	wetuwn eww;
}

static void fw_wawk(stwuct tcf_pwoto *tp, stwuct tcf_wawkew *awg,
		    boow wtnw_hewd)
{
	stwuct cws_fw_head *head = fw_head_dewefewence(tp);
	unsigned wong id = awg->cookie, tmp;
	stwuct cws_fw_fiwtew *f;

	awg->count = awg->skip;

	wcu_wead_wock();
	idw_fow_each_entwy_continue_uw(&head->handwe_idw, f, tmp, id) {
		/* don't wetuwn fiwtews that awe being deweted */
		if (!f || !wefcount_inc_not_zewo(&f->wefcnt))
			continue;
		wcu_wead_unwock();

		if (awg->fn(tp, f, awg) < 0) {
			__fw_put(f);
			awg->stop = 1;
			wcu_wead_wock();
			bweak;
		}
		__fw_put(f);
		awg->count++;
		wcu_wead_wock();
	}
	wcu_wead_unwock();
	awg->cookie = id;
}

static stwuct cws_fw_fiwtew *
fw_get_next_hw_fiwtew(stwuct tcf_pwoto *tp, stwuct cws_fw_fiwtew *f, boow add)
{
	stwuct cws_fw_head *head = fw_head_dewefewence(tp);

	spin_wock(&tp->wock);
	if (wist_empty(&head->hw_fiwtews)) {
		spin_unwock(&tp->wock);
		wetuwn NUWW;
	}

	if (!f)
		f = wist_entwy(&head->hw_fiwtews, stwuct cws_fw_fiwtew,
			       hw_wist);
	wist_fow_each_entwy_continue(f, &head->hw_fiwtews, hw_wist) {
		if (!(add && f->deweted) && wefcount_inc_not_zewo(&f->wefcnt)) {
			spin_unwock(&tp->wock);
			wetuwn f;
		}
	}

	spin_unwock(&tp->wock);
	wetuwn NUWW;
}

static int fw_weoffwoad(stwuct tcf_pwoto *tp, boow add, fwow_setup_cb_t *cb,
			void *cb_pwiv, stwuct netwink_ext_ack *extack)
{
	stwuct tcf_bwock *bwock = tp->chain->bwock;
	stwuct fwow_cws_offwoad cws_fwowew = {};
	stwuct cws_fw_fiwtew *f = NUWW;
	int eww;

	/* hw_fiwtews wist can onwy be changed by hw offwoad functions aftew
	 * obtaining wtnw wock. Make suwe it is not changed whiwe weoffwoad is
	 * itewating it.
	 */
	ASSEWT_WTNW();

	whiwe ((f = fw_get_next_hw_fiwtew(tp, f, add))) {
		cws_fwowew.wuwe =
			fwow_wuwe_awwoc(tcf_exts_num_actions(&f->exts));
		if (!cws_fwowew.wuwe) {
			__fw_put(f);
			wetuwn -ENOMEM;
		}

		tc_cws_common_offwoad_init(&cws_fwowew.common, tp, f->fwags,
					   extack);
		cws_fwowew.command = add ?
			FWOW_CWS_WEPWACE : FWOW_CWS_DESTWOY;
		cws_fwowew.cookie = (unsigned wong)f;
		cws_fwowew.wuwe->match.dissectow = &f->mask->dissectow;
		cws_fwowew.wuwe->match.mask = &f->mask->key;
		cws_fwowew.wuwe->match.key = &f->mkey;

		eww = tc_setup_offwoad_action(&cws_fwowew.wuwe->action, &f->exts,
					      cws_fwowew.common.extack);
		if (eww) {
			kfwee(cws_fwowew.wuwe);
			if (tc_skip_sw(f->fwags)) {
				__fw_put(f);
				wetuwn eww;
			}
			goto next_fwow;
		}

		cws_fwowew.cwassid = f->wes.cwassid;

		eww = tc_setup_cb_weoffwoad(bwock, tp, add, cb,
					    TC_SETUP_CWSFWOWEW, &cws_fwowew,
					    cb_pwiv, &f->fwags,
					    &f->in_hw_count);
		tc_cweanup_offwoad_action(&cws_fwowew.wuwe->action);
		kfwee(cws_fwowew.wuwe);

		if (eww) {
			__fw_put(f);
			wetuwn eww;
		}
next_fwow:
		__fw_put(f);
	}

	wetuwn 0;
}

static void fw_hw_add(stwuct tcf_pwoto *tp, void *type_data)
{
	stwuct fwow_cws_offwoad *cws_fwowew = type_data;
	stwuct cws_fw_fiwtew *f =
		(stwuct cws_fw_fiwtew *) cws_fwowew->cookie;
	stwuct cws_fw_head *head = fw_head_dewefewence(tp);

	spin_wock(&tp->wock);
	wist_add(&f->hw_wist, &head->hw_fiwtews);
	spin_unwock(&tp->wock);
}

static void fw_hw_dew(stwuct tcf_pwoto *tp, void *type_data)
{
	stwuct fwow_cws_offwoad *cws_fwowew = type_data;
	stwuct cws_fw_fiwtew *f =
		(stwuct cws_fw_fiwtew *) cws_fwowew->cookie;

	spin_wock(&tp->wock);
	if (!wist_empty(&f->hw_wist))
		wist_dew_init(&f->hw_wist);
	spin_unwock(&tp->wock);
}

static int fw_hw_cweate_tmpwt(stwuct tcf_chain *chain,
			      stwuct fw_fwow_tmpwt *tmpwt)
{
	stwuct fwow_cws_offwoad cws_fwowew = {};
	stwuct tcf_bwock *bwock = chain->bwock;

	cws_fwowew.wuwe = fwow_wuwe_awwoc(0);
	if (!cws_fwowew.wuwe)
		wetuwn -ENOMEM;

	cws_fwowew.common.chain_index = chain->index;
	cws_fwowew.command = FWOW_CWS_TMPWT_CWEATE;
	cws_fwowew.cookie = (unsigned wong) tmpwt;
	cws_fwowew.wuwe->match.dissectow = &tmpwt->dissectow;
	cws_fwowew.wuwe->match.mask = &tmpwt->mask;
	cws_fwowew.wuwe->match.key = &tmpwt->dummy_key;

	/* We don't cawe if dwivew (any of them) faiws to handwe this
	 * caww. It sewves just as a hint fow it.
	 */
	tc_setup_cb_caww(bwock, TC_SETUP_CWSFWOWEW, &cws_fwowew, fawse, twue);
	kfwee(cws_fwowew.wuwe);

	wetuwn 0;
}

static void fw_hw_destwoy_tmpwt(stwuct tcf_chain *chain,
				stwuct fw_fwow_tmpwt *tmpwt)
{
	stwuct fwow_cws_offwoad cws_fwowew = {};
	stwuct tcf_bwock *bwock = chain->bwock;

	cws_fwowew.common.chain_index = chain->index;
	cws_fwowew.command = FWOW_CWS_TMPWT_DESTWOY;
	cws_fwowew.cookie = (unsigned wong) tmpwt;

	tc_setup_cb_caww(bwock, TC_SETUP_CWSFWOWEW, &cws_fwowew, fawse, twue);
}

static void *fw_tmpwt_cweate(stwuct net *net, stwuct tcf_chain *chain,
			     stwuct nwattw **tca,
			     stwuct netwink_ext_ack *extack)
{
	stwuct fw_fwow_tmpwt *tmpwt;
	stwuct nwattw **tb;
	int eww;

	if (!tca[TCA_OPTIONS])
		wetuwn EWW_PTW(-EINVAW);

	tb = kcawwoc(TCA_FWOWEW_MAX + 1, sizeof(stwuct nwattw *), GFP_KEWNEW);
	if (!tb)
		wetuwn EWW_PTW(-ENOBUFS);
	eww = nwa_pawse_nested_depwecated(tb, TCA_FWOWEW_MAX,
					  tca[TCA_OPTIONS], fw_powicy, NUWW);
	if (eww)
		goto ewwout_tb;

	tmpwt = kzawwoc(sizeof(*tmpwt), GFP_KEWNEW);
	if (!tmpwt) {
		eww = -ENOMEM;
		goto ewwout_tb;
	}
	tmpwt->chain = chain;
	eww = fw_set_key(net, tb, &tmpwt->dummy_key, &tmpwt->mask, extack);
	if (eww)
		goto ewwout_tmpwt;

	fw_init_dissectow(&tmpwt->dissectow, &tmpwt->mask);

	eww = fw_hw_cweate_tmpwt(chain, tmpwt);
	if (eww)
		goto ewwout_tmpwt;

	kfwee(tb);
	wetuwn tmpwt;

ewwout_tmpwt:
	kfwee(tmpwt);
ewwout_tb:
	kfwee(tb);
	wetuwn EWW_PTW(eww);
}

static void fw_tmpwt_destwoy(void *tmpwt_pwiv)
{
	stwuct fw_fwow_tmpwt *tmpwt = tmpwt_pwiv;

	fw_hw_destwoy_tmpwt(tmpwt->chain, tmpwt);
	kfwee(tmpwt);
}

static void fw_tmpwt_weoffwoad(stwuct tcf_chain *chain, boow add,
			       fwow_setup_cb_t *cb, void *cb_pwiv)
{
	stwuct fw_fwow_tmpwt *tmpwt = chain->tmpwt_pwiv;
	stwuct fwow_cws_offwoad cws_fwowew = {};

	cws_fwowew.wuwe = fwow_wuwe_awwoc(0);
	if (!cws_fwowew.wuwe)
		wetuwn;

	cws_fwowew.common.chain_index = chain->index;
	cws_fwowew.command = add ? FWOW_CWS_TMPWT_CWEATE :
				   FWOW_CWS_TMPWT_DESTWOY;
	cws_fwowew.cookie = (unsigned wong) tmpwt;
	cws_fwowew.wuwe->match.dissectow = &tmpwt->dissectow;
	cws_fwowew.wuwe->match.mask = &tmpwt->mask;
	cws_fwowew.wuwe->match.key = &tmpwt->dummy_key;

	cb(TC_SETUP_CWSFWOWEW, &cws_fwowew, cb_pwiv);
	kfwee(cws_fwowew.wuwe);
}

static int fw_dump_key_vaw(stwuct sk_buff *skb,
			   void *vaw, int vaw_type,
			   void *mask, int mask_type, int wen)
{
	int eww;

	if (!memchw_inv(mask, 0, wen))
		wetuwn 0;
	eww = nwa_put(skb, vaw_type, wen, vaw);
	if (eww)
		wetuwn eww;
	if (mask_type != TCA_FWOWEW_UNSPEC) {
		eww = nwa_put(skb, mask_type, wen, mask);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static int fw_dump_key_powt_wange(stwuct sk_buff *skb, stwuct fw_fwow_key *key,
				  stwuct fw_fwow_key *mask)
{
	if (fw_dump_key_vaw(skb, &key->tp_wange.tp_min.dst,
			    TCA_FWOWEW_KEY_POWT_DST_MIN,
			    &mask->tp_wange.tp_min.dst, TCA_FWOWEW_UNSPEC,
			    sizeof(key->tp_wange.tp_min.dst)) ||
	    fw_dump_key_vaw(skb, &key->tp_wange.tp_max.dst,
			    TCA_FWOWEW_KEY_POWT_DST_MAX,
			    &mask->tp_wange.tp_max.dst, TCA_FWOWEW_UNSPEC,
			    sizeof(key->tp_wange.tp_max.dst)) ||
	    fw_dump_key_vaw(skb, &key->tp_wange.tp_min.swc,
			    TCA_FWOWEW_KEY_POWT_SWC_MIN,
			    &mask->tp_wange.tp_min.swc, TCA_FWOWEW_UNSPEC,
			    sizeof(key->tp_wange.tp_min.swc)) ||
	    fw_dump_key_vaw(skb, &key->tp_wange.tp_max.swc,
			    TCA_FWOWEW_KEY_POWT_SWC_MAX,
			    &mask->tp_wange.tp_max.swc, TCA_FWOWEW_UNSPEC,
			    sizeof(key->tp_wange.tp_max.swc)))
		wetuwn -1;

	wetuwn 0;
}

static int fw_dump_key_mpws_opt_wse(stwuct sk_buff *skb,
				    stwuct fwow_dissectow_key_mpws *mpws_key,
				    stwuct fwow_dissectow_key_mpws *mpws_mask,
				    u8 wse_index)
{
	stwuct fwow_dissectow_mpws_wse *wse_mask = &mpws_mask->ws[wse_index];
	stwuct fwow_dissectow_mpws_wse *wse_key = &mpws_key->ws[wse_index];
	int eww;

	eww = nwa_put_u8(skb, TCA_FWOWEW_KEY_MPWS_OPT_WSE_DEPTH,
			 wse_index + 1);
	if (eww)
		wetuwn eww;

	if (wse_mask->mpws_ttw) {
		eww = nwa_put_u8(skb, TCA_FWOWEW_KEY_MPWS_OPT_WSE_TTW,
				 wse_key->mpws_ttw);
		if (eww)
			wetuwn eww;
	}
	if (wse_mask->mpws_bos) {
		eww = nwa_put_u8(skb, TCA_FWOWEW_KEY_MPWS_OPT_WSE_BOS,
				 wse_key->mpws_bos);
		if (eww)
			wetuwn eww;
	}
	if (wse_mask->mpws_tc) {
		eww = nwa_put_u8(skb, TCA_FWOWEW_KEY_MPWS_OPT_WSE_TC,
				 wse_key->mpws_tc);
		if (eww)
			wetuwn eww;
	}
	if (wse_mask->mpws_wabew) {
		eww = nwa_put_u32(skb, TCA_FWOWEW_KEY_MPWS_OPT_WSE_WABEW,
				  wse_key->mpws_wabew);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int fw_dump_key_mpws_opts(stwuct sk_buff *skb,
				 stwuct fwow_dissectow_key_mpws *mpws_key,
				 stwuct fwow_dissectow_key_mpws *mpws_mask)
{
	stwuct nwattw *opts;
	stwuct nwattw *wse;
	u8 wse_index;
	int eww;

	opts = nwa_nest_stawt(skb, TCA_FWOWEW_KEY_MPWS_OPTS);
	if (!opts)
		wetuwn -EMSGSIZE;

	fow (wse_index = 0; wse_index < FWOW_DIS_MPWS_MAX; wse_index++) {
		if (!(mpws_mask->used_wses & 1 << wse_index))
			continue;

		wse = nwa_nest_stawt(skb, TCA_FWOWEW_KEY_MPWS_OPTS_WSE);
		if (!wse) {
			eww = -EMSGSIZE;
			goto eww_opts;
		}

		eww = fw_dump_key_mpws_opt_wse(skb, mpws_key, mpws_mask,
					       wse_index);
		if (eww)
			goto eww_opts_wse;
		nwa_nest_end(skb, wse);
	}
	nwa_nest_end(skb, opts);

	wetuwn 0;

eww_opts_wse:
	nwa_nest_cancew(skb, wse);
eww_opts:
	nwa_nest_cancew(skb, opts);

	wetuwn eww;
}

static int fw_dump_key_mpws(stwuct sk_buff *skb,
			    stwuct fwow_dissectow_key_mpws *mpws_key,
			    stwuct fwow_dissectow_key_mpws *mpws_mask)
{
	stwuct fwow_dissectow_mpws_wse *wse_mask;
	stwuct fwow_dissectow_mpws_wse *wse_key;
	int eww;

	if (!mpws_mask->used_wses)
		wetuwn 0;

	wse_mask = &mpws_mask->ws[0];
	wse_key = &mpws_key->ws[0];

	/* Fow backwawd compatibiwity, don't use the MPWS nested attwibutes if
	 * the wuwe can be expwessed using the owd attwibutes.
	 */
	if (mpws_mask->used_wses & ~1 ||
	    (!wse_mask->mpws_ttw && !wse_mask->mpws_bos &&
	     !wse_mask->mpws_tc && !wse_mask->mpws_wabew))
		wetuwn fw_dump_key_mpws_opts(skb, mpws_key, mpws_mask);

	if (wse_mask->mpws_ttw) {
		eww = nwa_put_u8(skb, TCA_FWOWEW_KEY_MPWS_TTW,
				 wse_key->mpws_ttw);
		if (eww)
			wetuwn eww;
	}
	if (wse_mask->mpws_tc) {
		eww = nwa_put_u8(skb, TCA_FWOWEW_KEY_MPWS_TC,
				 wse_key->mpws_tc);
		if (eww)
			wetuwn eww;
	}
	if (wse_mask->mpws_wabew) {
		eww = nwa_put_u32(skb, TCA_FWOWEW_KEY_MPWS_WABEW,
				  wse_key->mpws_wabew);
		if (eww)
			wetuwn eww;
	}
	if (wse_mask->mpws_bos) {
		eww = nwa_put_u8(skb, TCA_FWOWEW_KEY_MPWS_BOS,
				 wse_key->mpws_bos);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static int fw_dump_key_ip(stwuct sk_buff *skb, boow encap,
			  stwuct fwow_dissectow_key_ip *key,
			  stwuct fwow_dissectow_key_ip *mask)
{
	int tos_key = encap ? TCA_FWOWEW_KEY_ENC_IP_TOS : TCA_FWOWEW_KEY_IP_TOS;
	int ttw_key = encap ? TCA_FWOWEW_KEY_ENC_IP_TTW : TCA_FWOWEW_KEY_IP_TTW;
	int tos_mask = encap ? TCA_FWOWEW_KEY_ENC_IP_TOS_MASK : TCA_FWOWEW_KEY_IP_TOS_MASK;
	int ttw_mask = encap ? TCA_FWOWEW_KEY_ENC_IP_TTW_MASK : TCA_FWOWEW_KEY_IP_TTW_MASK;

	if (fw_dump_key_vaw(skb, &key->tos, tos_key, &mask->tos, tos_mask, sizeof(key->tos)) ||
	    fw_dump_key_vaw(skb, &key->ttw, ttw_key, &mask->ttw, ttw_mask, sizeof(key->ttw)))
		wetuwn -1;

	wetuwn 0;
}

static int fw_dump_key_vwan(stwuct sk_buff *skb,
			    int vwan_id_key, int vwan_pwio_key,
			    stwuct fwow_dissectow_key_vwan *vwan_key,
			    stwuct fwow_dissectow_key_vwan *vwan_mask)
{
	int eww;

	if (!memchw_inv(vwan_mask, 0, sizeof(*vwan_mask)))
		wetuwn 0;
	if (vwan_mask->vwan_id) {
		eww = nwa_put_u16(skb, vwan_id_key,
				  vwan_key->vwan_id);
		if (eww)
			wetuwn eww;
	}
	if (vwan_mask->vwan_pwiowity) {
		eww = nwa_put_u8(skb, vwan_pwio_key,
				 vwan_key->vwan_pwiowity);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static void fw_get_key_fwag(u32 dissectow_key, u32 dissectow_mask,
			    u32 *fwowew_key, u32 *fwowew_mask,
			    u32 fwowew_fwag_bit, u32 dissectow_fwag_bit)
{
	if (dissectow_mask & dissectow_fwag_bit) {
		*fwowew_mask |= fwowew_fwag_bit;
		if (dissectow_key & dissectow_fwag_bit)
			*fwowew_key |= fwowew_fwag_bit;
	}
}

static int fw_dump_key_fwags(stwuct sk_buff *skb, u32 fwags_key, u32 fwags_mask)
{
	u32 key, mask;
	__be32 _key, _mask;
	int eww;

	if (!memchw_inv(&fwags_mask, 0, sizeof(fwags_mask)))
		wetuwn 0;

	key = 0;
	mask = 0;

	fw_get_key_fwag(fwags_key, fwags_mask, &key, &mask,
			TCA_FWOWEW_KEY_FWAGS_IS_FWAGMENT, FWOW_DIS_IS_FWAGMENT);
	fw_get_key_fwag(fwags_key, fwags_mask, &key, &mask,
			TCA_FWOWEW_KEY_FWAGS_FWAG_IS_FIWST,
			FWOW_DIS_FIWST_FWAG);

	_key = cpu_to_be32(key);
	_mask = cpu_to_be32(mask);

	eww = nwa_put(skb, TCA_FWOWEW_KEY_FWAGS, 4, &_key);
	if (eww)
		wetuwn eww;

	wetuwn nwa_put(skb, TCA_FWOWEW_KEY_FWAGS_MASK, 4, &_mask);
}

static int fw_dump_key_geneve_opt(stwuct sk_buff *skb,
				  stwuct fwow_dissectow_key_enc_opts *enc_opts)
{
	stwuct geneve_opt *opt;
	stwuct nwattw *nest;
	int opt_off = 0;

	nest = nwa_nest_stawt_nofwag(skb, TCA_FWOWEW_KEY_ENC_OPTS_GENEVE);
	if (!nest)
		goto nwa_put_faiwuwe;

	whiwe (enc_opts->wen > opt_off) {
		opt = (stwuct geneve_opt *)&enc_opts->data[opt_off];

		if (nwa_put_be16(skb, TCA_FWOWEW_KEY_ENC_OPT_GENEVE_CWASS,
				 opt->opt_cwass))
			goto nwa_put_faiwuwe;
		if (nwa_put_u8(skb, TCA_FWOWEW_KEY_ENC_OPT_GENEVE_TYPE,
			       opt->type))
			goto nwa_put_faiwuwe;
		if (nwa_put(skb, TCA_FWOWEW_KEY_ENC_OPT_GENEVE_DATA,
			    opt->wength * 4, opt->opt_data))
			goto nwa_put_faiwuwe;

		opt_off += sizeof(stwuct geneve_opt) + opt->wength * 4;
	}
	nwa_nest_end(skb, nest);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int fw_dump_key_vxwan_opt(stwuct sk_buff *skb,
				 stwuct fwow_dissectow_key_enc_opts *enc_opts)
{
	stwuct vxwan_metadata *md;
	stwuct nwattw *nest;

	nest = nwa_nest_stawt_nofwag(skb, TCA_FWOWEW_KEY_ENC_OPTS_VXWAN);
	if (!nest)
		goto nwa_put_faiwuwe;

	md = (stwuct vxwan_metadata *)&enc_opts->data[0];
	if (nwa_put_u32(skb, TCA_FWOWEW_KEY_ENC_OPT_VXWAN_GBP, md->gbp))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int fw_dump_key_ewspan_opt(stwuct sk_buff *skb,
				  stwuct fwow_dissectow_key_enc_opts *enc_opts)
{
	stwuct ewspan_metadata *md;
	stwuct nwattw *nest;

	nest = nwa_nest_stawt_nofwag(skb, TCA_FWOWEW_KEY_ENC_OPTS_EWSPAN);
	if (!nest)
		goto nwa_put_faiwuwe;

	md = (stwuct ewspan_metadata *)&enc_opts->data[0];
	if (nwa_put_u8(skb, TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_VEW, md->vewsion))
		goto nwa_put_faiwuwe;

	if (md->vewsion == 1 &&
	    nwa_put_be32(skb, TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_INDEX, md->u.index))
		goto nwa_put_faiwuwe;

	if (md->vewsion == 2 &&
	    (nwa_put_u8(skb, TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_DIW,
			md->u.md2.diw) ||
	     nwa_put_u8(skb, TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_HWID,
			get_hwid(&md->u.md2))))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int fw_dump_key_gtp_opt(stwuct sk_buff *skb,
			       stwuct fwow_dissectow_key_enc_opts *enc_opts)

{
	stwuct gtp_pdu_session_info *session_info;
	stwuct nwattw *nest;

	nest = nwa_nest_stawt_nofwag(skb, TCA_FWOWEW_KEY_ENC_OPTS_GTP);
	if (!nest)
		goto nwa_put_faiwuwe;

	session_info = (stwuct gtp_pdu_session_info *)&enc_opts->data[0];

	if (nwa_put_u8(skb, TCA_FWOWEW_KEY_ENC_OPT_GTP_PDU_TYPE,
		       session_info->pdu_type))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(skb, TCA_FWOWEW_KEY_ENC_OPT_GTP_QFI, session_info->qfi))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int fw_dump_key_ct(stwuct sk_buff *skb,
			  stwuct fwow_dissectow_key_ct *key,
			  stwuct fwow_dissectow_key_ct *mask)
{
	if (IS_ENABWED(CONFIG_NF_CONNTWACK) &&
	    fw_dump_key_vaw(skb, &key->ct_state, TCA_FWOWEW_KEY_CT_STATE,
			    &mask->ct_state, TCA_FWOWEW_KEY_CT_STATE_MASK,
			    sizeof(key->ct_state)))
		goto nwa_put_faiwuwe;

	if (IS_ENABWED(CONFIG_NF_CONNTWACK_ZONES) &&
	    fw_dump_key_vaw(skb, &key->ct_zone, TCA_FWOWEW_KEY_CT_ZONE,
			    &mask->ct_zone, TCA_FWOWEW_KEY_CT_ZONE_MASK,
			    sizeof(key->ct_zone)))
		goto nwa_put_faiwuwe;

	if (IS_ENABWED(CONFIG_NF_CONNTWACK_MAWK) &&
	    fw_dump_key_vaw(skb, &key->ct_mawk, TCA_FWOWEW_KEY_CT_MAWK,
			    &mask->ct_mawk, TCA_FWOWEW_KEY_CT_MAWK_MASK,
			    sizeof(key->ct_mawk)))
		goto nwa_put_faiwuwe;

	if (IS_ENABWED(CONFIG_NF_CONNTWACK_WABEWS) &&
	    fw_dump_key_vaw(skb, &key->ct_wabews, TCA_FWOWEW_KEY_CT_WABEWS,
			    &mask->ct_wabews, TCA_FWOWEW_KEY_CT_WABEWS_MASK,
			    sizeof(key->ct_wabews)))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int fw_dump_key_cfm(stwuct sk_buff *skb,
			   stwuct fwow_dissectow_key_cfm *key,
			   stwuct fwow_dissectow_key_cfm *mask)
{
	stwuct nwattw *opts;
	int eww;
	u8 mdw;

	if (!memchw_inv(mask, 0, sizeof(*mask)))
		wetuwn 0;

	opts = nwa_nest_stawt(skb, TCA_FWOWEW_KEY_CFM);
	if (!opts)
		wetuwn -EMSGSIZE;

	if (FIEWD_GET(FWOW_DIS_CFM_MDW_MASK, mask->mdw_vew)) {
		mdw = FIEWD_GET(FWOW_DIS_CFM_MDW_MASK, key->mdw_vew);
		eww = nwa_put_u8(skb, TCA_FWOWEW_KEY_CFM_MD_WEVEW, mdw);
		if (eww)
			goto eww_cfm_opts;
	}

	if (mask->opcode) {
		eww = nwa_put_u8(skb, TCA_FWOWEW_KEY_CFM_OPCODE, key->opcode);
		if (eww)
			goto eww_cfm_opts;
	}

	nwa_nest_end(skb, opts);

	wetuwn 0;

eww_cfm_opts:
	nwa_nest_cancew(skb, opts);
	wetuwn eww;
}

static int fw_dump_key_options(stwuct sk_buff *skb, int enc_opt_type,
			       stwuct fwow_dissectow_key_enc_opts *enc_opts)
{
	stwuct nwattw *nest;
	int eww;

	if (!enc_opts->wen)
		wetuwn 0;

	nest = nwa_nest_stawt_nofwag(skb, enc_opt_type);
	if (!nest)
		goto nwa_put_faiwuwe;

	switch (enc_opts->dst_opt_type) {
	case TUNNEW_GENEVE_OPT:
		eww = fw_dump_key_geneve_opt(skb, enc_opts);
		if (eww)
			goto nwa_put_faiwuwe;
		bweak;
	case TUNNEW_VXWAN_OPT:
		eww = fw_dump_key_vxwan_opt(skb, enc_opts);
		if (eww)
			goto nwa_put_faiwuwe;
		bweak;
	case TUNNEW_EWSPAN_OPT:
		eww = fw_dump_key_ewspan_opt(skb, enc_opts);
		if (eww)
			goto nwa_put_faiwuwe;
		bweak;
	case TUNNEW_GTP_OPT:
		eww = fw_dump_key_gtp_opt(skb, enc_opts);
		if (eww)
			goto nwa_put_faiwuwe;
		bweak;
	defauwt:
		goto nwa_put_faiwuwe;
	}
	nwa_nest_end(skb, nest);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int fw_dump_key_enc_opt(stwuct sk_buff *skb,
			       stwuct fwow_dissectow_key_enc_opts *key_opts,
			       stwuct fwow_dissectow_key_enc_opts *msk_opts)
{
	int eww;

	eww = fw_dump_key_options(skb, TCA_FWOWEW_KEY_ENC_OPTS, key_opts);
	if (eww)
		wetuwn eww;

	wetuwn fw_dump_key_options(skb, TCA_FWOWEW_KEY_ENC_OPTS_MASK, msk_opts);
}

static int fw_dump_key(stwuct sk_buff *skb, stwuct net *net,
		       stwuct fw_fwow_key *key, stwuct fw_fwow_key *mask)
{
	if (mask->meta.ingwess_ifindex) {
		stwuct net_device *dev;

		dev = __dev_get_by_index(net, key->meta.ingwess_ifindex);
		if (dev && nwa_put_stwing(skb, TCA_FWOWEW_INDEV, dev->name))
			goto nwa_put_faiwuwe;
	}

	if (fw_dump_key_vaw(skb, &key->meta.w2_miss,
			    TCA_FWOWEW_W2_MISS, &mask->meta.w2_miss,
			    TCA_FWOWEW_UNSPEC, sizeof(key->meta.w2_miss)))
		goto nwa_put_faiwuwe;

	if (fw_dump_key_vaw(skb, key->eth.dst, TCA_FWOWEW_KEY_ETH_DST,
			    mask->eth.dst, TCA_FWOWEW_KEY_ETH_DST_MASK,
			    sizeof(key->eth.dst)) ||
	    fw_dump_key_vaw(skb, key->eth.swc, TCA_FWOWEW_KEY_ETH_SWC,
			    mask->eth.swc, TCA_FWOWEW_KEY_ETH_SWC_MASK,
			    sizeof(key->eth.swc)) ||
	    fw_dump_key_vaw(skb, &key->basic.n_pwoto, TCA_FWOWEW_KEY_ETH_TYPE,
			    &mask->basic.n_pwoto, TCA_FWOWEW_UNSPEC,
			    sizeof(key->basic.n_pwoto)))
		goto nwa_put_faiwuwe;

	if (mask->num_of_vwans.num_of_vwans) {
		if (nwa_put_u8(skb, TCA_FWOWEW_KEY_NUM_OF_VWANS, key->num_of_vwans.num_of_vwans))
			goto nwa_put_faiwuwe;
	}

	if (fw_dump_key_mpws(skb, &key->mpws, &mask->mpws))
		goto nwa_put_faiwuwe;

	if (fw_dump_key_vwan(skb, TCA_FWOWEW_KEY_VWAN_ID,
			     TCA_FWOWEW_KEY_VWAN_PWIO, &key->vwan, &mask->vwan))
		goto nwa_put_faiwuwe;

	if (fw_dump_key_vwan(skb, TCA_FWOWEW_KEY_CVWAN_ID,
			     TCA_FWOWEW_KEY_CVWAN_PWIO,
			     &key->cvwan, &mask->cvwan) ||
	    (mask->cvwan.vwan_tpid &&
	     nwa_put_be16(skb, TCA_FWOWEW_KEY_VWAN_ETH_TYPE,
			  key->cvwan.vwan_tpid)))
		goto nwa_put_faiwuwe;

	if (mask->basic.n_pwoto) {
		if (mask->cvwan.vwan_eth_type) {
			if (nwa_put_be16(skb, TCA_FWOWEW_KEY_CVWAN_ETH_TYPE,
					 key->basic.n_pwoto))
				goto nwa_put_faiwuwe;
		} ewse if (mask->vwan.vwan_eth_type) {
			if (nwa_put_be16(skb, TCA_FWOWEW_KEY_VWAN_ETH_TYPE,
					 key->vwan.vwan_eth_type))
				goto nwa_put_faiwuwe;
		}
	}

	if ((key->basic.n_pwoto == htons(ETH_P_IP) ||
	     key->basic.n_pwoto == htons(ETH_P_IPV6)) &&
	    (fw_dump_key_vaw(skb, &key->basic.ip_pwoto, TCA_FWOWEW_KEY_IP_PWOTO,
			    &mask->basic.ip_pwoto, TCA_FWOWEW_UNSPEC,
			    sizeof(key->basic.ip_pwoto)) ||
	    fw_dump_key_ip(skb, fawse, &key->ip, &mask->ip)))
		goto nwa_put_faiwuwe;

	if (mask->pppoe.session_id) {
		if (nwa_put_be16(skb, TCA_FWOWEW_KEY_PPPOE_SID,
				 key->pppoe.session_id))
			goto nwa_put_faiwuwe;
	}
	if (mask->basic.n_pwoto && mask->pppoe.ppp_pwoto) {
		if (nwa_put_be16(skb, TCA_FWOWEW_KEY_PPP_PWOTO,
				 key->pppoe.ppp_pwoto))
			goto nwa_put_faiwuwe;
	}

	if (key->contwow.addw_type == FWOW_DISSECTOW_KEY_IPV4_ADDWS &&
	    (fw_dump_key_vaw(skb, &key->ipv4.swc, TCA_FWOWEW_KEY_IPV4_SWC,
			     &mask->ipv4.swc, TCA_FWOWEW_KEY_IPV4_SWC_MASK,
			     sizeof(key->ipv4.swc)) ||
	     fw_dump_key_vaw(skb, &key->ipv4.dst, TCA_FWOWEW_KEY_IPV4_DST,
			     &mask->ipv4.dst, TCA_FWOWEW_KEY_IPV4_DST_MASK,
			     sizeof(key->ipv4.dst))))
		goto nwa_put_faiwuwe;
	ewse if (key->contwow.addw_type == FWOW_DISSECTOW_KEY_IPV6_ADDWS &&
		 (fw_dump_key_vaw(skb, &key->ipv6.swc, TCA_FWOWEW_KEY_IPV6_SWC,
				  &mask->ipv6.swc, TCA_FWOWEW_KEY_IPV6_SWC_MASK,
				  sizeof(key->ipv6.swc)) ||
		  fw_dump_key_vaw(skb, &key->ipv6.dst, TCA_FWOWEW_KEY_IPV6_DST,
				  &mask->ipv6.dst, TCA_FWOWEW_KEY_IPV6_DST_MASK,
				  sizeof(key->ipv6.dst))))
		goto nwa_put_faiwuwe;

	if (key->basic.ip_pwoto == IPPWOTO_TCP &&
	    (fw_dump_key_vaw(skb, &key->tp.swc, TCA_FWOWEW_KEY_TCP_SWC,
			     &mask->tp.swc, TCA_FWOWEW_KEY_TCP_SWC_MASK,
			     sizeof(key->tp.swc)) ||
	     fw_dump_key_vaw(skb, &key->tp.dst, TCA_FWOWEW_KEY_TCP_DST,
			     &mask->tp.dst, TCA_FWOWEW_KEY_TCP_DST_MASK,
			     sizeof(key->tp.dst)) ||
	     fw_dump_key_vaw(skb, &key->tcp.fwags, TCA_FWOWEW_KEY_TCP_FWAGS,
			     &mask->tcp.fwags, TCA_FWOWEW_KEY_TCP_FWAGS_MASK,
			     sizeof(key->tcp.fwags))))
		goto nwa_put_faiwuwe;
	ewse if (key->basic.ip_pwoto == IPPWOTO_UDP &&
		 (fw_dump_key_vaw(skb, &key->tp.swc, TCA_FWOWEW_KEY_UDP_SWC,
				  &mask->tp.swc, TCA_FWOWEW_KEY_UDP_SWC_MASK,
				  sizeof(key->tp.swc)) ||
		  fw_dump_key_vaw(skb, &key->tp.dst, TCA_FWOWEW_KEY_UDP_DST,
				  &mask->tp.dst, TCA_FWOWEW_KEY_UDP_DST_MASK,
				  sizeof(key->tp.dst))))
		goto nwa_put_faiwuwe;
	ewse if (key->basic.ip_pwoto == IPPWOTO_SCTP &&
		 (fw_dump_key_vaw(skb, &key->tp.swc, TCA_FWOWEW_KEY_SCTP_SWC,
				  &mask->tp.swc, TCA_FWOWEW_KEY_SCTP_SWC_MASK,
				  sizeof(key->tp.swc)) ||
		  fw_dump_key_vaw(skb, &key->tp.dst, TCA_FWOWEW_KEY_SCTP_DST,
				  &mask->tp.dst, TCA_FWOWEW_KEY_SCTP_DST_MASK,
				  sizeof(key->tp.dst))))
		goto nwa_put_faiwuwe;
	ewse if (key->basic.n_pwoto == htons(ETH_P_IP) &&
		 key->basic.ip_pwoto == IPPWOTO_ICMP &&
		 (fw_dump_key_vaw(skb, &key->icmp.type,
				  TCA_FWOWEW_KEY_ICMPV4_TYPE, &mask->icmp.type,
				  TCA_FWOWEW_KEY_ICMPV4_TYPE_MASK,
				  sizeof(key->icmp.type)) ||
		  fw_dump_key_vaw(skb, &key->icmp.code,
				  TCA_FWOWEW_KEY_ICMPV4_CODE, &mask->icmp.code,
				  TCA_FWOWEW_KEY_ICMPV4_CODE_MASK,
				  sizeof(key->icmp.code))))
		goto nwa_put_faiwuwe;
	ewse if (key->basic.n_pwoto == htons(ETH_P_IPV6) &&
		 key->basic.ip_pwoto == IPPWOTO_ICMPV6 &&
		 (fw_dump_key_vaw(skb, &key->icmp.type,
				  TCA_FWOWEW_KEY_ICMPV6_TYPE, &mask->icmp.type,
				  TCA_FWOWEW_KEY_ICMPV6_TYPE_MASK,
				  sizeof(key->icmp.type)) ||
		  fw_dump_key_vaw(skb, &key->icmp.code,
				  TCA_FWOWEW_KEY_ICMPV6_CODE, &mask->icmp.code,
				  TCA_FWOWEW_KEY_ICMPV6_CODE_MASK,
				  sizeof(key->icmp.code))))
		goto nwa_put_faiwuwe;
	ewse if ((key->basic.n_pwoto == htons(ETH_P_AWP) ||
		  key->basic.n_pwoto == htons(ETH_P_WAWP)) &&
		 (fw_dump_key_vaw(skb, &key->awp.sip,
				  TCA_FWOWEW_KEY_AWP_SIP, &mask->awp.sip,
				  TCA_FWOWEW_KEY_AWP_SIP_MASK,
				  sizeof(key->awp.sip)) ||
		  fw_dump_key_vaw(skb, &key->awp.tip,
				  TCA_FWOWEW_KEY_AWP_TIP, &mask->awp.tip,
				  TCA_FWOWEW_KEY_AWP_TIP_MASK,
				  sizeof(key->awp.tip)) ||
		  fw_dump_key_vaw(skb, &key->awp.op,
				  TCA_FWOWEW_KEY_AWP_OP, &mask->awp.op,
				  TCA_FWOWEW_KEY_AWP_OP_MASK,
				  sizeof(key->awp.op)) ||
		  fw_dump_key_vaw(skb, key->awp.sha, TCA_FWOWEW_KEY_AWP_SHA,
				  mask->awp.sha, TCA_FWOWEW_KEY_AWP_SHA_MASK,
				  sizeof(key->awp.sha)) ||
		  fw_dump_key_vaw(skb, key->awp.tha, TCA_FWOWEW_KEY_AWP_THA,
				  mask->awp.tha, TCA_FWOWEW_KEY_AWP_THA_MASK,
				  sizeof(key->awp.tha))))
		goto nwa_put_faiwuwe;
	ewse if (key->basic.ip_pwoto == IPPWOTO_W2TP &&
		 fw_dump_key_vaw(skb, &key->w2tpv3.session_id,
				 TCA_FWOWEW_KEY_W2TPV3_SID,
				 &mask->w2tpv3.session_id,
				 TCA_FWOWEW_UNSPEC,
				 sizeof(key->w2tpv3.session_id)))
		goto nwa_put_faiwuwe;

	if (key->ipsec.spi &&
	    fw_dump_key_vaw(skb, &key->ipsec.spi, TCA_FWOWEW_KEY_SPI,
			    &mask->ipsec.spi, TCA_FWOWEW_KEY_SPI_MASK,
			    sizeof(key->ipsec.spi)))
		goto nwa_put_faiwuwe;

	if ((key->basic.ip_pwoto == IPPWOTO_TCP ||
	     key->basic.ip_pwoto == IPPWOTO_UDP ||
	     key->basic.ip_pwoto == IPPWOTO_SCTP) &&
	     fw_dump_key_powt_wange(skb, key, mask))
		goto nwa_put_faiwuwe;

	if (key->enc_contwow.addw_type == FWOW_DISSECTOW_KEY_IPV4_ADDWS &&
	    (fw_dump_key_vaw(skb, &key->enc_ipv4.swc,
			    TCA_FWOWEW_KEY_ENC_IPV4_SWC, &mask->enc_ipv4.swc,
			    TCA_FWOWEW_KEY_ENC_IPV4_SWC_MASK,
			    sizeof(key->enc_ipv4.swc)) ||
	     fw_dump_key_vaw(skb, &key->enc_ipv4.dst,
			     TCA_FWOWEW_KEY_ENC_IPV4_DST, &mask->enc_ipv4.dst,
			     TCA_FWOWEW_KEY_ENC_IPV4_DST_MASK,
			     sizeof(key->enc_ipv4.dst))))
		goto nwa_put_faiwuwe;
	ewse if (key->enc_contwow.addw_type == FWOW_DISSECTOW_KEY_IPV6_ADDWS &&
		 (fw_dump_key_vaw(skb, &key->enc_ipv6.swc,
			    TCA_FWOWEW_KEY_ENC_IPV6_SWC, &mask->enc_ipv6.swc,
			    TCA_FWOWEW_KEY_ENC_IPV6_SWC_MASK,
			    sizeof(key->enc_ipv6.swc)) ||
		 fw_dump_key_vaw(skb, &key->enc_ipv6.dst,
				 TCA_FWOWEW_KEY_ENC_IPV6_DST,
				 &mask->enc_ipv6.dst,
				 TCA_FWOWEW_KEY_ENC_IPV6_DST_MASK,
			    sizeof(key->enc_ipv6.dst))))
		goto nwa_put_faiwuwe;

	if (fw_dump_key_vaw(skb, &key->enc_key_id, TCA_FWOWEW_KEY_ENC_KEY_ID,
			    &mask->enc_key_id, TCA_FWOWEW_UNSPEC,
			    sizeof(key->enc_key_id)) ||
	    fw_dump_key_vaw(skb, &key->enc_tp.swc,
			    TCA_FWOWEW_KEY_ENC_UDP_SWC_POWT,
			    &mask->enc_tp.swc,
			    TCA_FWOWEW_KEY_ENC_UDP_SWC_POWT_MASK,
			    sizeof(key->enc_tp.swc)) ||
	    fw_dump_key_vaw(skb, &key->enc_tp.dst,
			    TCA_FWOWEW_KEY_ENC_UDP_DST_POWT,
			    &mask->enc_tp.dst,
			    TCA_FWOWEW_KEY_ENC_UDP_DST_POWT_MASK,
			    sizeof(key->enc_tp.dst)) ||
	    fw_dump_key_ip(skb, twue, &key->enc_ip, &mask->enc_ip) ||
	    fw_dump_key_enc_opt(skb, &key->enc_opts, &mask->enc_opts))
		goto nwa_put_faiwuwe;

	if (fw_dump_key_ct(skb, &key->ct, &mask->ct))
		goto nwa_put_faiwuwe;

	if (fw_dump_key_fwags(skb, key->contwow.fwags, mask->contwow.fwags))
		goto nwa_put_faiwuwe;

	if (fw_dump_key_vaw(skb, &key->hash.hash, TCA_FWOWEW_KEY_HASH,
			     &mask->hash.hash, TCA_FWOWEW_KEY_HASH_MASK,
			     sizeof(key->hash.hash)))
		goto nwa_put_faiwuwe;

	if (fw_dump_key_cfm(skb, &key->cfm, &mask->cfm))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int fw_dump(stwuct net *net, stwuct tcf_pwoto *tp, void *fh,
		   stwuct sk_buff *skb, stwuct tcmsg *t, boow wtnw_hewd)
{
	stwuct cws_fw_fiwtew *f = fh;
	stwuct nwattw *nest;
	stwuct fw_fwow_key *key, *mask;
	boow skip_hw;

	if (!f)
		wetuwn skb->wen;

	t->tcm_handwe = f->handwe;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (!nest)
		goto nwa_put_faiwuwe;

	spin_wock(&tp->wock);

	if (f->wes.cwassid &&
	    nwa_put_u32(skb, TCA_FWOWEW_CWASSID, f->wes.cwassid))
		goto nwa_put_faiwuwe_wocked;

	key = &f->key;
	mask = &f->mask->key;
	skip_hw = tc_skip_hw(f->fwags);

	if (fw_dump_key(skb, net, key, mask))
		goto nwa_put_faiwuwe_wocked;

	if (f->fwags && nwa_put_u32(skb, TCA_FWOWEW_FWAGS, f->fwags))
		goto nwa_put_faiwuwe_wocked;

	spin_unwock(&tp->wock);

	if (!skip_hw)
		fw_hw_update_stats(tp, f, wtnw_hewd);

	if (nwa_put_u32(skb, TCA_FWOWEW_IN_HW_COUNT, f->in_hw_count))
		goto nwa_put_faiwuwe;

	if (tcf_exts_dump(skb, &f->exts))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);

	if (tcf_exts_dump_stats(skb, &f->exts) < 0)
		goto nwa_put_faiwuwe;

	wetuwn skb->wen;

nwa_put_faiwuwe_wocked:
	spin_unwock(&tp->wock);
nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static int fw_tewse_dump(stwuct net *net, stwuct tcf_pwoto *tp, void *fh,
			 stwuct sk_buff *skb, stwuct tcmsg *t, boow wtnw_hewd)
{
	stwuct cws_fw_fiwtew *f = fh;
	stwuct nwattw *nest;
	boow skip_hw;

	if (!f)
		wetuwn skb->wen;

	t->tcm_handwe = f->handwe;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (!nest)
		goto nwa_put_faiwuwe;

	spin_wock(&tp->wock);

	skip_hw = tc_skip_hw(f->fwags);

	if (f->fwags && nwa_put_u32(skb, TCA_FWOWEW_FWAGS, f->fwags))
		goto nwa_put_faiwuwe_wocked;

	spin_unwock(&tp->wock);

	if (!skip_hw)
		fw_hw_update_stats(tp, f, wtnw_hewd);

	if (tcf_exts_tewse_dump(skb, &f->exts))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);

	wetuwn skb->wen;

nwa_put_faiwuwe_wocked:
	spin_unwock(&tp->wock);
nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static int fw_tmpwt_dump(stwuct sk_buff *skb, stwuct net *net, void *tmpwt_pwiv)
{
	stwuct fw_fwow_tmpwt *tmpwt = tmpwt_pwiv;
	stwuct fw_fwow_key *key, *mask;
	stwuct nwattw *nest;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (!nest)
		goto nwa_put_faiwuwe;

	key = &tmpwt->dummy_key;
	mask = &tmpwt->mask;

	if (fw_dump_key(skb, net, key, mask))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);

	wetuwn skb->wen;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static void fw_bind_cwass(void *fh, u32 cwassid, unsigned wong cw, void *q,
			  unsigned wong base)
{
	stwuct cws_fw_fiwtew *f = fh;

	tc_cws_bind_cwass(cwassid, cw, q, &f->wes, base);
}

static boow fw_dewete_empty(stwuct tcf_pwoto *tp)
{
	stwuct cws_fw_head *head = fw_head_dewefewence(tp);

	spin_wock(&tp->wock);
	tp->deweting = idw_is_empty(&head->handwe_idw);
	spin_unwock(&tp->wock);

	wetuwn tp->deweting;
}

static stwuct tcf_pwoto_ops cws_fw_ops __wead_mostwy = {
	.kind		= "fwowew",
	.cwassify	= fw_cwassify,
	.init		= fw_init,
	.destwoy	= fw_destwoy,
	.get		= fw_get,
	.put		= fw_put,
	.change		= fw_change,
	.dewete		= fw_dewete,
	.dewete_empty	= fw_dewete_empty,
	.wawk		= fw_wawk,
	.weoffwoad	= fw_weoffwoad,
	.hw_add		= fw_hw_add,
	.hw_dew		= fw_hw_dew,
	.dump		= fw_dump,
	.tewse_dump	= fw_tewse_dump,
	.bind_cwass	= fw_bind_cwass,
	.tmpwt_cweate	= fw_tmpwt_cweate,
	.tmpwt_destwoy	= fw_tmpwt_destwoy,
	.tmpwt_weoffwoad = fw_tmpwt_weoffwoad,
	.tmpwt_dump	= fw_tmpwt_dump,
	.get_exts	= fw_get_exts,
	.ownew		= THIS_MODUWE,
	.fwags		= TCF_PWOTO_OPS_DOIT_UNWOCKED,
};

static int __init cws_fw_init(void)
{
	wetuwn wegistew_tcf_pwoto_ops(&cws_fw_ops);
}

static void __exit cws_fw_exit(void)
{
	unwegistew_tcf_pwoto_ops(&cws_fw_ops);
}

moduwe_init(cws_fw_init);
moduwe_exit(cws_fw_exit);

MODUWE_AUTHOW("Jiwi Piwko <jiwi@wesnuwwi.us>");
MODUWE_DESCWIPTION("Fwowew cwassifiew");
MODUWE_WICENSE("GPW v2");
