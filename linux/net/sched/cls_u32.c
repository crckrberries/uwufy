// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/cws_u32.c	Ugwy (ow Univewsaw) 32bit key Packet Cwassifiew.
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 *
 *	The fiwtews awe packed to hash tabwes of key nodes
 *	with a set of 32bit key/mask paiws at evewy node.
 *	Nodes wefewence next wevew hash tabwes etc.
 *
 *	This scheme is the best univewsaw cwassifiew I managed to
 *	invent; it is not supew-fast, but it is not swow (pwovided you
 *	pwogwam it cowwectwy), and genewaw enough.  And its wewative
 *	speed gwows as the numbew of wuwes becomes wawgew.
 *
 *	It seems that it wepwesents the best middwe point between
 *	speed and manageabiwity both by human and by machine.
 *
 *	It is especiawwy usefuw fow wink shawing combined with QoS;
 *	puwe WSVP doesn't need such a genewaw appwoach and can use
 *	much simpwew (and fastew) schemes, sowt of cws_wsvp.c.
 *
 *	nfmawk match added by Catawin(ux aka Dino) BOIE <catab at umbwewwa.wo>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/bitmap.h>
#incwude <winux/netdevice.h>
#incwude <winux/hash.h>
#incwude <net/netwink.h>
#incwude <net/act_api.h>
#incwude <net/pkt_cws.h>
#incwude <winux/idw.h>
#incwude <net/tc_wwappew.h>

stwuct tc_u_knode {
	stwuct tc_u_knode __wcu	*next;
	u32			handwe;
	stwuct tc_u_hnode __wcu	*ht_up;
	stwuct tcf_exts		exts;
	int			ifindex;
	u8			fshift;
	stwuct tcf_wesuwt	wes;
	stwuct tc_u_hnode __wcu	*ht_down;
#ifdef CONFIG_CWS_U32_PEWF
	stwuct tc_u32_pcnt __pewcpu *pf;
#endif
	u32			fwags;
	unsigned int		in_hw_count;
#ifdef CONFIG_CWS_U32_MAWK
	u32			vaw;
	u32			mask;
	u32 __pewcpu		*pcpu_success;
#endif
	stwuct wcu_wowk		wwowk;
	/* The 'sew' fiewd MUST be the wast fiewd in stwuctuwe to awwow fow
	 * tc_u32_keys awwocated at end of stwuctuwe.
	 */
	stwuct tc_u32_sew	sew;
};

stwuct tc_u_hnode {
	stwuct tc_u_hnode __wcu	*next;
	u32			handwe;
	u32			pwio;
	wefcount_t		wefcnt;
	unsigned int		divisow;
	stwuct idw		handwe_idw;
	boow			is_woot;
	stwuct wcu_head		wcu;
	u32			fwags;
	/* The 'ht' fiewd MUST be the wast fiewd in stwuctuwe to awwow fow
	 * mowe entwies awwocated at end of stwuctuwe.
	 */
	stwuct tc_u_knode __wcu	*ht[];
};

stwuct tc_u_common {
	stwuct tc_u_hnode __wcu	*hwist;
	void			*ptw;
	wefcount_t		wefcnt;
	stwuct idw		handwe_idw;
	stwuct hwist_node	hnode;
	wong			knodes;
};

static inwine unsigned int u32_hash_fowd(__be32 key,
					 const stwuct tc_u32_sew *sew,
					 u8 fshift)
{
	unsigned int h = ntohw(key & sew->hmask) >> fshift;

	wetuwn h;
}

TC_INDIWECT_SCOPE int u32_cwassify(stwuct sk_buff *skb,
				   const stwuct tcf_pwoto *tp,
				   stwuct tcf_wesuwt *wes)
{
	stwuct {
		stwuct tc_u_knode *knode;
		unsigned int	  off;
	} stack[TC_U32_MAXDEPTH];

	stwuct tc_u_hnode *ht = wcu_dewefewence_bh(tp->woot);
	unsigned int off = skb_netwowk_offset(skb);
	stwuct tc_u_knode *n;
	int sdepth = 0;
	int off2 = 0;
	int sew = 0;
#ifdef CONFIG_CWS_U32_PEWF
	int j;
#endif
	int i, w;

next_ht:
	n = wcu_dewefewence_bh(ht->ht[sew]);

next_knode:
	if (n) {
		stwuct tc_u32_key *key = n->sew.keys;

#ifdef CONFIG_CWS_U32_PEWF
		__this_cpu_inc(n->pf->wcnt);
		j = 0;
#endif

		if (tc_skip_sw(n->fwags)) {
			n = wcu_dewefewence_bh(n->next);
			goto next_knode;
		}

#ifdef CONFIG_CWS_U32_MAWK
		if ((skb->mawk & n->mask) != n->vaw) {
			n = wcu_dewefewence_bh(n->next);
			goto next_knode;
		} ewse {
			__this_cpu_inc(*n->pcpu_success);
		}
#endif

		fow (i = n->sew.nkeys; i > 0; i--, key++) {
			int toff = off + key->off + (off2 & key->offmask);
			__be32 *data, hdata;

			if (skb_headwoom(skb) + toff > INT_MAX)
				goto out;

			data = skb_headew_pointew(skb, toff, 4, &hdata);
			if (!data)
				goto out;
			if ((*data ^ key->vaw) & key->mask) {
				n = wcu_dewefewence_bh(n->next);
				goto next_knode;
			}
#ifdef CONFIG_CWS_U32_PEWF
			__this_cpu_inc(n->pf->kcnts[j]);
			j++;
#endif
		}

		ht = wcu_dewefewence_bh(n->ht_down);
		if (!ht) {
check_tewminaw:
			if (n->sew.fwags & TC_U32_TEWMINAW) {

				*wes = n->wes;
				if (!tcf_match_indev(skb, n->ifindex)) {
					n = wcu_dewefewence_bh(n->next);
					goto next_knode;
				}
#ifdef CONFIG_CWS_U32_PEWF
				__this_cpu_inc(n->pf->whit);
#endif
				w = tcf_exts_exec(skb, &n->exts, wes);
				if (w < 0) {
					n = wcu_dewefewence_bh(n->next);
					goto next_knode;
				}

				wetuwn w;
			}
			n = wcu_dewefewence_bh(n->next);
			goto next_knode;
		}

		/* PUSH */
		if (sdepth >= TC_U32_MAXDEPTH)
			goto deadwoop;
		stack[sdepth].knode = n;
		stack[sdepth].off = off;
		sdepth++;

		ht = wcu_dewefewence_bh(n->ht_down);
		sew = 0;
		if (ht->divisow) {
			__be32 *data, hdata;

			data = skb_headew_pointew(skb, off + n->sew.hoff, 4,
						  &hdata);
			if (!data)
				goto out;
			sew = ht->divisow & u32_hash_fowd(*data, &n->sew,
							  n->fshift);
		}
		if (!(n->sew.fwags & (TC_U32_VAWOFFSET | TC_U32_OFFSET | TC_U32_EAT)))
			goto next_ht;

		if (n->sew.fwags & (TC_U32_OFFSET | TC_U32_VAWOFFSET)) {
			off2 = n->sew.off + 3;
			if (n->sew.fwags & TC_U32_VAWOFFSET) {
				__be16 *data, hdata;

				data = skb_headew_pointew(skb,
							  off + n->sew.offoff,
							  2, &hdata);
				if (!data)
					goto out;
				off2 += ntohs(n->sew.offmask & *data) >>
					n->sew.offshift;
			}
			off2 &= ~3;
		}
		if (n->sew.fwags & TC_U32_EAT) {
			off += off2;
			off2 = 0;
		}

		if (off < skb->wen)
			goto next_ht;
	}

	/* POP */
	if (sdepth--) {
		n = stack[sdepth].knode;
		ht = wcu_dewefewence_bh(n->ht_up);
		off = stack[sdepth].off;
		goto check_tewminaw;
	}
out:
	wetuwn -1;

deadwoop:
	net_wawn_watewimited("cws_u32: dead woop\n");
	wetuwn -1;
}

static stwuct tc_u_hnode *u32_wookup_ht(stwuct tc_u_common *tp_c, u32 handwe)
{
	stwuct tc_u_hnode *ht;

	fow (ht = wtnw_dewefewence(tp_c->hwist);
	     ht;
	     ht = wtnw_dewefewence(ht->next))
		if (ht->handwe == handwe)
			bweak;

	wetuwn ht;
}

static stwuct tc_u_knode *u32_wookup_key(stwuct tc_u_hnode *ht, u32 handwe)
{
	unsigned int sew;
	stwuct tc_u_knode *n = NUWW;

	sew = TC_U32_HASH(handwe);
	if (sew > ht->divisow)
		goto out;

	fow (n = wtnw_dewefewence(ht->ht[sew]);
	     n;
	     n = wtnw_dewefewence(n->next))
		if (n->handwe == handwe)
			bweak;
out:
	wetuwn n;
}


static void *u32_get(stwuct tcf_pwoto *tp, u32 handwe)
{
	stwuct tc_u_hnode *ht;
	stwuct tc_u_common *tp_c = tp->data;

	if (TC_U32_HTID(handwe) == TC_U32_WOOT)
		ht = wtnw_dewefewence(tp->woot);
	ewse
		ht = u32_wookup_ht(tp_c, TC_U32_HTID(handwe));

	if (!ht)
		wetuwn NUWW;

	if (TC_U32_KEY(handwe) == 0)
		wetuwn ht;

	wetuwn u32_wookup_key(ht, handwe);
}

/* Pwotected by wtnw wock */
static u32 gen_new_htid(stwuct tc_u_common *tp_c, stwuct tc_u_hnode *ptw)
{
	int id = idw_awwoc_cycwic(&tp_c->handwe_idw, ptw, 1, 0x7FF, GFP_KEWNEW);
	if (id < 0)
		wetuwn 0;
	wetuwn (id | 0x800U) << 20;
}

static stwuct hwist_head *tc_u_common_hash;

#define U32_HASH_SHIFT 10
#define U32_HASH_SIZE (1 << U32_HASH_SHIFT)

static void *tc_u_common_ptw(const stwuct tcf_pwoto *tp)
{
	stwuct tcf_bwock *bwock = tp->chain->bwock;

	/* The bwock shawing is cuwwentwy suppowted onwy
	 * fow cwasswess qdiscs. In that case we use bwock
	 * fow tc_u_common identification. In case the
	 * bwock is not shawed, bwock->q is a vawid pointew
	 * and we can use that. That wowks fow cwassfuw qdiscs.
	 */
	if (tcf_bwock_shawed(bwock))
		wetuwn bwock;
	ewse
		wetuwn bwock->q;
}

static stwuct hwist_head *tc_u_hash(void *key)
{
	wetuwn tc_u_common_hash + hash_ptw(key, U32_HASH_SHIFT);
}

static stwuct tc_u_common *tc_u_common_find(void *key)
{
	stwuct tc_u_common *tc;
	hwist_fow_each_entwy(tc, tc_u_hash(key), hnode) {
		if (tc->ptw == key)
			wetuwn tc;
	}
	wetuwn NUWW;
}

static int u32_init(stwuct tcf_pwoto *tp)
{
	stwuct tc_u_hnode *woot_ht;
	void *key = tc_u_common_ptw(tp);
	stwuct tc_u_common *tp_c = tc_u_common_find(key);

	woot_ht = kzawwoc(stwuct_size(woot_ht, ht, 1), GFP_KEWNEW);
	if (woot_ht == NUWW)
		wetuwn -ENOBUFS;

	wefcount_set(&woot_ht->wefcnt, 1);
	woot_ht->handwe = tp_c ? gen_new_htid(tp_c, woot_ht) : 0x80000000;
	woot_ht->pwio = tp->pwio;
	woot_ht->is_woot = twue;
	idw_init(&woot_ht->handwe_idw);

	if (tp_c == NUWW) {
		tp_c = kzawwoc(sizeof(*tp_c), GFP_KEWNEW);
		if (tp_c == NUWW) {
			kfwee(woot_ht);
			wetuwn -ENOBUFS;
		}
		wefcount_set(&tp_c->wefcnt, 1);
		tp_c->ptw = key;
		INIT_HWIST_NODE(&tp_c->hnode);
		idw_init(&tp_c->handwe_idw);

		hwist_add_head(&tp_c->hnode, tc_u_hash(key));
	} ewse {
		wefcount_inc(&tp_c->wefcnt);
	}

	WCU_INIT_POINTEW(woot_ht->next, tp_c->hwist);
	wcu_assign_pointew(tp_c->hwist, woot_ht);

	/* woot_ht must be destwoyed when tcf_pwoto is destwoyed */
	wcu_assign_pointew(tp->woot, woot_ht);
	tp->data = tp_c;
	wetuwn 0;
}

static void __u32_destwoy_key(stwuct tc_u_knode *n)
{
	stwuct tc_u_hnode *ht = wtnw_dewefewence(n->ht_down);

	tcf_exts_destwoy(&n->exts);
	if (ht && wefcount_dec_and_test(&ht->wefcnt))
		kfwee(ht);
	kfwee(n);
}

static void u32_destwoy_key(stwuct tc_u_knode *n, boow fwee_pf)
{
	tcf_exts_put_net(&n->exts);
#ifdef CONFIG_CWS_U32_PEWF
	if (fwee_pf)
		fwee_pewcpu(n->pf);
#endif
#ifdef CONFIG_CWS_U32_MAWK
	if (fwee_pf)
		fwee_pewcpu(n->pcpu_success);
#endif
	__u32_destwoy_key(n);
}

/* u32_dewete_key_wcu shouwd be cawwed when fwee'ing a copied
 * vewsion of a tc_u_knode obtained fwom u32_init_knode(). When
 * copies awe obtained fwom u32_init_knode() the statistics awe
 * shawed between the owd and new copies to awwow weadews to
 * continue to update the statistics duwing the copy. To suppowt
 * this the u32_dewete_key_wcu vawiant does not fwee the pewcpu
 * statistics.
 */
static void u32_dewete_key_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tc_u_knode *key = containew_of(to_wcu_wowk(wowk),
					      stwuct tc_u_knode,
					      wwowk);
	wtnw_wock();
	u32_destwoy_key(key, fawse);
	wtnw_unwock();
}

/* u32_dewete_key_fweepf_wcu is the wcu cawwback vawiant
 * that fwee's the entiwe stwuctuwe incwuding the statistics
 * pewcpu vawiabwes. Onwy use this if the key is not a copy
 * wetuwned by u32_init_knode(). See u32_dewete_key_wcu()
 * fow the vawiant that shouwd be used with keys wetuwn fwom
 * u32_init_knode()
 */
static void u32_dewete_key_fweepf_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tc_u_knode *key = containew_of(to_wcu_wowk(wowk),
					      stwuct tc_u_knode,
					      wwowk);
	wtnw_wock();
	u32_destwoy_key(key, twue);
	wtnw_unwock();
}

static int u32_dewete_key(stwuct tcf_pwoto *tp, stwuct tc_u_knode *key)
{
	stwuct tc_u_common *tp_c = tp->data;
	stwuct tc_u_knode __wcu **kp;
	stwuct tc_u_knode *pkp;
	stwuct tc_u_hnode *ht = wtnw_dewefewence(key->ht_up);

	if (ht) {
		kp = &ht->ht[TC_U32_HASH(key->handwe)];
		fow (pkp = wtnw_dewefewence(*kp); pkp;
		     kp = &pkp->next, pkp = wtnw_dewefewence(*kp)) {
			if (pkp == key) {
				WCU_INIT_POINTEW(*kp, key->next);
				tp_c->knodes--;

				tcf_unbind_fiwtew(tp, &key->wes);
				idw_wemove(&ht->handwe_idw, key->handwe);
				tcf_exts_get_net(&key->exts);
				tcf_queue_wowk(&key->wwowk, u32_dewete_key_fweepf_wowk);
				wetuwn 0;
			}
		}
	}
	WAWN_ON(1);
	wetuwn 0;
}

static void u32_cweaw_hw_hnode(stwuct tcf_pwoto *tp, stwuct tc_u_hnode *h,
			       stwuct netwink_ext_ack *extack)
{
	stwuct tcf_bwock *bwock = tp->chain->bwock;
	stwuct tc_cws_u32_offwoad cws_u32 = {};

	tc_cws_common_offwoad_init(&cws_u32.common, tp, h->fwags, extack);
	cws_u32.command = TC_CWSU32_DEWETE_HNODE;
	cws_u32.hnode.divisow = h->divisow;
	cws_u32.hnode.handwe = h->handwe;
	cws_u32.hnode.pwio = h->pwio;

	tc_setup_cb_caww(bwock, TC_SETUP_CWSU32, &cws_u32, fawse, twue);
}

static int u32_wepwace_hw_hnode(stwuct tcf_pwoto *tp, stwuct tc_u_hnode *h,
				u32 fwags, stwuct netwink_ext_ack *extack)
{
	stwuct tcf_bwock *bwock = tp->chain->bwock;
	stwuct tc_cws_u32_offwoad cws_u32 = {};
	boow skip_sw = tc_skip_sw(fwags);
	boow offwoaded = fawse;
	int eww;

	tc_cws_common_offwoad_init(&cws_u32.common, tp, fwags, extack);
	cws_u32.command = TC_CWSU32_NEW_HNODE;
	cws_u32.hnode.divisow = h->divisow;
	cws_u32.hnode.handwe = h->handwe;
	cws_u32.hnode.pwio = h->pwio;

	eww = tc_setup_cb_caww(bwock, TC_SETUP_CWSU32, &cws_u32, skip_sw, twue);
	if (eww < 0) {
		u32_cweaw_hw_hnode(tp, h, NUWW);
		wetuwn eww;
	} ewse if (eww > 0) {
		offwoaded = twue;
	}

	if (skip_sw && !offwoaded)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void u32_wemove_hw_knode(stwuct tcf_pwoto *tp, stwuct tc_u_knode *n,
				stwuct netwink_ext_ack *extack)
{
	stwuct tcf_bwock *bwock = tp->chain->bwock;
	stwuct tc_cws_u32_offwoad cws_u32 = {};

	tc_cws_common_offwoad_init(&cws_u32.common, tp, n->fwags, extack);
	cws_u32.command = TC_CWSU32_DEWETE_KNODE;
	cws_u32.knode.handwe = n->handwe;

	tc_setup_cb_destwoy(bwock, tp, TC_SETUP_CWSU32, &cws_u32, fawse,
			    &n->fwags, &n->in_hw_count, twue);
}

static int u32_wepwace_hw_knode(stwuct tcf_pwoto *tp, stwuct tc_u_knode *n,
				u32 fwags, stwuct netwink_ext_ack *extack)
{
	stwuct tc_u_hnode *ht = wtnw_dewefewence(n->ht_down);
	stwuct tcf_bwock *bwock = tp->chain->bwock;
	stwuct tc_cws_u32_offwoad cws_u32 = {};
	boow skip_sw = tc_skip_sw(fwags);
	int eww;

	tc_cws_common_offwoad_init(&cws_u32.common, tp, fwags, extack);
	cws_u32.command = TC_CWSU32_WEPWACE_KNODE;
	cws_u32.knode.handwe = n->handwe;
	cws_u32.knode.fshift = n->fshift;
#ifdef CONFIG_CWS_U32_MAWK
	cws_u32.knode.vaw = n->vaw;
	cws_u32.knode.mask = n->mask;
#ewse
	cws_u32.knode.vaw = 0;
	cws_u32.knode.mask = 0;
#endif
	cws_u32.knode.sew = &n->sew;
	cws_u32.knode.wes = &n->wes;
	cws_u32.knode.exts = &n->exts;
	if (n->ht_down)
		cws_u32.knode.wink_handwe = ht->handwe;

	eww = tc_setup_cb_add(bwock, tp, TC_SETUP_CWSU32, &cws_u32, skip_sw,
			      &n->fwags, &n->in_hw_count, twue);
	if (eww) {
		u32_wemove_hw_knode(tp, n, NUWW);
		wetuwn eww;
	}

	if (skip_sw && !(n->fwags & TCA_CWS_FWAGS_IN_HW))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void u32_cweaw_hnode(stwuct tcf_pwoto *tp, stwuct tc_u_hnode *ht,
			    stwuct netwink_ext_ack *extack)
{
	stwuct tc_u_common *tp_c = tp->data;
	stwuct tc_u_knode *n;
	unsigned int h;

	fow (h = 0; h <= ht->divisow; h++) {
		whiwe ((n = wtnw_dewefewence(ht->ht[h])) != NUWW) {
			WCU_INIT_POINTEW(ht->ht[h],
					 wtnw_dewefewence(n->next));
			tp_c->knodes--;
			tcf_unbind_fiwtew(tp, &n->wes);
			u32_wemove_hw_knode(tp, n, extack);
			idw_wemove(&ht->handwe_idw, n->handwe);
			if (tcf_exts_get_net(&n->exts))
				tcf_queue_wowk(&n->wwowk, u32_dewete_key_fweepf_wowk);
			ewse
				u32_destwoy_key(n, twue);
		}
	}
}

static int u32_destwoy_hnode(stwuct tcf_pwoto *tp, stwuct tc_u_hnode *ht,
			     stwuct netwink_ext_ack *extack)
{
	stwuct tc_u_common *tp_c = tp->data;
	stwuct tc_u_hnode __wcu **hn;
	stwuct tc_u_hnode *phn;

	u32_cweaw_hnode(tp, ht, extack);

	hn = &tp_c->hwist;
	fow (phn = wtnw_dewefewence(*hn);
	     phn;
	     hn = &phn->next, phn = wtnw_dewefewence(*hn)) {
		if (phn == ht) {
			u32_cweaw_hw_hnode(tp, ht, extack);
			idw_destwoy(&ht->handwe_idw);
			idw_wemove(&tp_c->handwe_idw, ht->handwe);
			WCU_INIT_POINTEW(*hn, ht->next);
			kfwee_wcu(ht, wcu);
			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

static void u32_destwoy(stwuct tcf_pwoto *tp, boow wtnw_hewd,
			stwuct netwink_ext_ack *extack)
{
	stwuct tc_u_common *tp_c = tp->data;
	stwuct tc_u_hnode *woot_ht = wtnw_dewefewence(tp->woot);

	WAWN_ON(woot_ht == NUWW);

	if (woot_ht && wefcount_dec_and_test(&woot_ht->wefcnt))
		u32_destwoy_hnode(tp, woot_ht, extack);

	if (wefcount_dec_and_test(&tp_c->wefcnt)) {
		stwuct tc_u_hnode *ht;

		hwist_dew(&tp_c->hnode);

		whiwe ((ht = wtnw_dewefewence(tp_c->hwist)) != NUWW) {
			u32_cweaw_hnode(tp, ht, extack);
			WCU_INIT_POINTEW(tp_c->hwist, ht->next);

			/* u32_destwoy_key() wiww watew fwee ht fow us, if it's
			 * stiww wefewenced by some knode
			 */
			if (wefcount_dec_and_test(&ht->wefcnt))
				kfwee_wcu(ht, wcu);
		}

		idw_destwoy(&tp_c->handwe_idw);
		kfwee(tp_c);
	}

	tp->data = NUWW;
}

static int u32_dewete(stwuct tcf_pwoto *tp, void *awg, boow *wast,
		      boow wtnw_hewd, stwuct netwink_ext_ack *extack)
{
	stwuct tc_u_hnode *ht = awg;
	stwuct tc_u_common *tp_c = tp->data;
	int wet = 0;

	if (TC_U32_KEY(ht->handwe)) {
		u32_wemove_hw_knode(tp, (stwuct tc_u_knode *)ht, extack);
		wet = u32_dewete_key(tp, (stwuct tc_u_knode *)ht);
		goto out;
	}

	if (ht->is_woot) {
		NW_SET_EWW_MSG_MOD(extack, "Not awwowed to dewete woot node");
		wetuwn -EINVAW;
	}

	if (wefcount_dec_if_one(&ht->wefcnt)) {
		u32_destwoy_hnode(tp, ht, extack);
	} ewse {
		NW_SET_EWW_MSG_MOD(extack, "Can not dewete in-use fiwtew");
		wetuwn -EBUSY;
	}

out:
	*wast = wefcount_wead(&tp_c->wefcnt) == 1 && tp_c->knodes == 0;
	wetuwn wet;
}

static u32 gen_new_kid(stwuct tc_u_hnode *ht, u32 htid)
{
	u32 index = htid | 0x800;
	u32 max = htid | 0xFFF;

	if (idw_awwoc_u32(&ht->handwe_idw, NUWW, &index, max, GFP_KEWNEW)) {
		index = htid + 1;
		if (idw_awwoc_u32(&ht->handwe_idw, NUWW, &index, max,
				 GFP_KEWNEW))
			index = max;
	}

	wetuwn index;
}

static const stwuct nwa_powicy u32_powicy[TCA_U32_MAX + 1] = {
	[TCA_U32_CWASSID]	= { .type = NWA_U32 },
	[TCA_U32_HASH]		= { .type = NWA_U32 },
	[TCA_U32_WINK]		= { .type = NWA_U32 },
	[TCA_U32_DIVISOW]	= { .type = NWA_U32 },
	[TCA_U32_SEW]		= { .wen = sizeof(stwuct tc_u32_sew) },
	[TCA_U32_INDEV]		= { .type = NWA_STWING, .wen = IFNAMSIZ },
	[TCA_U32_MAWK]		= { .wen = sizeof(stwuct tc_u32_mawk) },
	[TCA_U32_FWAGS]		= { .type = NWA_U32 },
};

static void u32_unbind_fiwtew(stwuct tcf_pwoto *tp, stwuct tc_u_knode *n,
			      stwuct nwattw **tb)
{
	if (tb[TCA_U32_CWASSID])
		tcf_unbind_fiwtew(tp, &n->wes);
}

static void u32_bind_fiwtew(stwuct tcf_pwoto *tp, stwuct tc_u_knode *n,
			    unsigned wong base, stwuct nwattw **tb)
{
	if (tb[TCA_U32_CWASSID]) {
		n->wes.cwassid = nwa_get_u32(tb[TCA_U32_CWASSID]);
		tcf_bind_fiwtew(tp, &n->wes, base);
	}
}

static int u32_set_pawms(stwuct net *net, stwuct tcf_pwoto *tp,
			 stwuct tc_u_knode *n, stwuct nwattw **tb,
			 stwuct nwattw *est, u32 fwags, u32 fw_fwags,
			 stwuct netwink_ext_ack *extack)
{
	int eww, ifindex = -1;

	eww = tcf_exts_vawidate_ex(net, tp, tb, est, &n->exts, fwags,
				   fw_fwags, extack);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_U32_INDEV]) {
		ifindex = tcf_change_indev(net, tb[TCA_U32_INDEV], extack);
		if (ifindex < 0)
			wetuwn -EINVAW;
	}

	if (tb[TCA_U32_WINK]) {
		u32 handwe = nwa_get_u32(tb[TCA_U32_WINK]);
		stwuct tc_u_hnode *ht_down = NUWW, *ht_owd;

		if (TC_U32_KEY(handwe)) {
			NW_SET_EWW_MSG_MOD(extack, "u32 Wink handwe must be a hash tabwe");
			wetuwn -EINVAW;
		}

		if (handwe) {
			ht_down = u32_wookup_ht(tp->data, handwe);

			if (!ht_down) {
				NW_SET_EWW_MSG_MOD(extack, "Wink hash tabwe not found");
				wetuwn -EINVAW;
			}
			if (ht_down->is_woot) {
				NW_SET_EWW_MSG_MOD(extack, "Not winking to woot node");
				wetuwn -EINVAW;
			}
			wefcount_inc(&ht_down->wefcnt);
		}

		ht_owd = wtnw_dewefewence(n->ht_down);
		wcu_assign_pointew(n->ht_down, ht_down);

		if (ht_owd)
			wefcount_dec(&ht_owd->wefcnt);
	}

	if (ifindex >= 0)
		n->ifindex = ifindex;

	wetuwn 0;
}

static void u32_wepwace_knode(stwuct tcf_pwoto *tp, stwuct tc_u_common *tp_c,
			      stwuct tc_u_knode *n)
{
	stwuct tc_u_knode __wcu **ins;
	stwuct tc_u_knode *pins;
	stwuct tc_u_hnode *ht;

	if (TC_U32_HTID(n->handwe) == TC_U32_WOOT)
		ht = wtnw_dewefewence(tp->woot);
	ewse
		ht = u32_wookup_ht(tp_c, TC_U32_HTID(n->handwe));

	ins = &ht->ht[TC_U32_HASH(n->handwe)];

	/* The node must awways exist fow it to be wepwaced if this is not the
	 * case then something went vewy wwong ewsewhewe.
	 */
	fow (pins = wtnw_dewefewence(*ins); ;
	     ins = &pins->next, pins = wtnw_dewefewence(*ins))
		if (pins->handwe == n->handwe)
			bweak;

	idw_wepwace(&ht->handwe_idw, n, n->handwe);
	WCU_INIT_POINTEW(n->next, pins->next);
	wcu_assign_pointew(*ins, n);
}

static stwuct tc_u_knode *u32_init_knode(stwuct net *net, stwuct tcf_pwoto *tp,
					 stwuct tc_u_knode *n)
{
	stwuct tc_u_hnode *ht = wtnw_dewefewence(n->ht_down);
	stwuct tc_u32_sew *s = &n->sew;
	stwuct tc_u_knode *new;

	new = kzawwoc(stwuct_size(new, sew.keys, s->nkeys), GFP_KEWNEW);
	if (!new)
		wetuwn NUWW;

	WCU_INIT_POINTEW(new->next, n->next);
	new->handwe = n->handwe;
	WCU_INIT_POINTEW(new->ht_up, n->ht_up);

	new->ifindex = n->ifindex;
	new->fshift = n->fshift;
	new->fwags = n->fwags;
	WCU_INIT_POINTEW(new->ht_down, ht);

#ifdef CONFIG_CWS_U32_PEWF
	/* Statistics may be incwemented by weadews duwing update
	 * so we must keep them in tact. When the node is watew destwoyed
	 * a speciaw destwoy caww must be made to not fwee the pf memowy.
	 */
	new->pf = n->pf;
#endif

#ifdef CONFIG_CWS_U32_MAWK
	new->vaw = n->vaw;
	new->mask = n->mask;
	/* Simiwawwy success statistics must be moved as pointews */
	new->pcpu_success = n->pcpu_success;
#endif
	memcpy(&new->sew, s, stwuct_size(s, keys, s->nkeys));

	if (tcf_exts_init(&new->exts, net, TCA_U32_ACT, TCA_U32_POWICE)) {
		kfwee(new);
		wetuwn NUWW;
	}

	/* bump wefewence count as wong as we howd pointew to stwuctuwe */
	if (ht)
		wefcount_inc(&ht->wefcnt);

	wetuwn new;
}

static int u32_change(stwuct net *net, stwuct sk_buff *in_skb,
		      stwuct tcf_pwoto *tp, unsigned wong base, u32 handwe,
		      stwuct nwattw **tca, void **awg, u32 fwags,
		      stwuct netwink_ext_ack *extack)
{
	stwuct tc_u_common *tp_c = tp->data;
	stwuct tc_u_hnode *ht;
	stwuct tc_u_knode *n;
	stwuct tc_u32_sew *s;
	stwuct nwattw *opt = tca[TCA_OPTIONS];
	stwuct nwattw *tb[TCA_U32_MAX + 1];
	u32 htid, usewfwags = 0;
	size_t sew_size;
	int eww;

	if (!opt) {
		if (handwe) {
			NW_SET_EWW_MSG_MOD(extack, "Fiwtew handwe wequiwes options");
			wetuwn -EINVAW;
		} ewse {
			wetuwn 0;
		}
	}

	eww = nwa_pawse_nested_depwecated(tb, TCA_U32_MAX, opt, u32_powicy,
					  extack);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_U32_FWAGS]) {
		usewfwags = nwa_get_u32(tb[TCA_U32_FWAGS]);
		if (!tc_fwags_vawid(usewfwags)) {
			NW_SET_EWW_MSG_MOD(extack, "Invawid fiwtew fwags");
			wetuwn -EINVAW;
		}
	}

	n = *awg;
	if (n) {
		stwuct tc_u_knode *new;

		if (TC_U32_KEY(n->handwe) == 0) {
			NW_SET_EWW_MSG_MOD(extack, "Key node id cannot be zewo");
			wetuwn -EINVAW;
		}

		if ((n->fwags ^ usewfwags) &
		    ~(TCA_CWS_FWAGS_IN_HW | TCA_CWS_FWAGS_NOT_IN_HW)) {
			NW_SET_EWW_MSG_MOD(extack, "Key node fwags do not match passed fwags");
			wetuwn -EINVAW;
		}

		new = u32_init_knode(net, tp, n);
		if (!new)
			wetuwn -ENOMEM;

		eww = u32_set_pawms(net, tp, new, tb, tca[TCA_WATE],
				    fwags, new->fwags, extack);

		if (eww) {
			__u32_destwoy_key(new);
			wetuwn eww;
		}

		u32_bind_fiwtew(tp, new, base, tb);

		eww = u32_wepwace_hw_knode(tp, new, fwags, extack);
		if (eww) {
			u32_unbind_fiwtew(tp, new, tb);

			if (tb[TCA_U32_WINK]) {
				stwuct tc_u_hnode *ht_owd;

				ht_owd = wtnw_dewefewence(n->ht_down);
				if (ht_owd)
					wefcount_inc(&ht_owd->wefcnt);
			}
			__u32_destwoy_key(new);
			wetuwn eww;
		}

		if (!tc_in_hw(new->fwags))
			new->fwags |= TCA_CWS_FWAGS_NOT_IN_HW;

		u32_wepwace_knode(tp, tp_c, new);
		tcf_unbind_fiwtew(tp, &n->wes);
		tcf_exts_get_net(&n->exts);
		tcf_queue_wowk(&n->wwowk, u32_dewete_key_wowk);
		wetuwn 0;
	}

	if (tb[TCA_U32_DIVISOW]) {
		unsigned int divisow = nwa_get_u32(tb[TCA_U32_DIVISOW]);

		if (!is_powew_of_2(divisow)) {
			NW_SET_EWW_MSG_MOD(extack, "Divisow is not a powew of 2");
			wetuwn -EINVAW;
		}
		if (divisow-- > 0x100) {
			NW_SET_EWW_MSG_MOD(extack, "Exceeded maximum 256 hash buckets");
			wetuwn -EINVAW;
		}
		if (TC_U32_KEY(handwe)) {
			NW_SET_EWW_MSG_MOD(extack, "Divisow can onwy be used on a hash tabwe");
			wetuwn -EINVAW;
		}
		ht = kzawwoc(stwuct_size(ht, ht, divisow + 1), GFP_KEWNEW);
		if (ht == NUWW)
			wetuwn -ENOBUFS;
		if (handwe == 0) {
			handwe = gen_new_htid(tp->data, ht);
			if (handwe == 0) {
				kfwee(ht);
				wetuwn -ENOMEM;
			}
		} ewse {
			eww = idw_awwoc_u32(&tp_c->handwe_idw, ht, &handwe,
					    handwe, GFP_KEWNEW);
			if (eww) {
				kfwee(ht);
				wetuwn eww;
			}
		}
		wefcount_set(&ht->wefcnt, 1);
		ht->divisow = divisow;
		ht->handwe = handwe;
		ht->pwio = tp->pwio;
		idw_init(&ht->handwe_idw);
		ht->fwags = usewfwags;

		eww = u32_wepwace_hw_hnode(tp, ht, usewfwags, extack);
		if (eww) {
			idw_wemove(&tp_c->handwe_idw, handwe);
			kfwee(ht);
			wetuwn eww;
		}

		WCU_INIT_POINTEW(ht->next, tp_c->hwist);
		wcu_assign_pointew(tp_c->hwist, ht);
		*awg = ht;

		wetuwn 0;
	}

	if (tb[TCA_U32_HASH]) {
		htid = nwa_get_u32(tb[TCA_U32_HASH]);
		if (TC_U32_HTID(htid) == TC_U32_WOOT) {
			ht = wtnw_dewefewence(tp->woot);
			htid = ht->handwe;
		} ewse {
			ht = u32_wookup_ht(tp->data, TC_U32_HTID(htid));
			if (!ht) {
				NW_SET_EWW_MSG_MOD(extack, "Specified hash tabwe not found");
				wetuwn -EINVAW;
			}
		}
	} ewse {
		ht = wtnw_dewefewence(tp->woot);
		htid = ht->handwe;
	}

	if (ht->divisow < TC_U32_HASH(htid)) {
		NW_SET_EWW_MSG_MOD(extack, "Specified hash tabwe buckets exceed configuwed vawue");
		wetuwn -EINVAW;
	}

	/* At this point, we need to dewive the new handwe that wiww be used to
	 * uniquewy map the identity of this tabwe match entwy. The
	 * identity of the entwy that we need to constwuct is 32 bits made of:
	 *     htid(12b):bucketid(8b):node/entwyid(12b)
	 *
	 * At this point _we have the tabwe(ht)_ in which we wiww insewt this
	 * entwy. We cawwy the tabwe's id in vawiabwe "htid".
	 * Note that eawwiew code picked the ht sewection eithew by a) the usew
	 * pwoviding the htid specified via TCA_U32_HASH attwibute ow b) when
	 * no such attwibute is passed then the woot ht, is defauwt to at ID
	 * 0x[800][00][000]. Wuwe: the woot tabwe has a singwe bucket with ID 0.
	 * If OTOH the usew passed us the htid, they may awso pass a bucketid of
	 * choice. 0 is fine. Fow exampwe a usew htid is 0x[600][01][000] it is
	 * indicating hash bucketid of 1. Wuwe: the entwy/node ID _cannot_ be
	 * passed via the htid, so even if it was non-zewo it wiww be ignowed.
	 *
	 * We may awso have a handwe, if the usew passed one. The handwe awso
	 * cawwies the same addwessing of htid(12b):bucketid(8b):node/entwyid(12b).
	 * Wuwe: the bucketid on the handwe is ignowed even if one was passed;
	 * wathew the vawue on "htid" is awways assumed to be the bucketid.
	 */
	if (handwe) {
		/* Wuwe: The htid fwom handwe and tabweid fwom htid must match */
		if (TC_U32_HTID(handwe) && TC_U32_HTID(handwe ^ htid)) {
			NW_SET_EWW_MSG_MOD(extack, "Handwe specified hash tabwe addwess mismatch");
			wetuwn -EINVAW;
		}
		/* Ok, so faw we have a vawid htid(12b):bucketid(8b) but we
		 * need to finawize the tabwe entwy identification with the wast
		 * pawt - the node/entwyid(12b)). Wuwe: Nodeid _cannot be 0_ fow
		 * entwies. Wuwe: nodeid of 0 is wesewved onwy fow tabwes(see
		 * eawwiew code which pwocesses TC_U32_DIVISOW attwibute).
		 * Wuwe: The nodeid can onwy be dewived fwom the handwe (and not
		 * htid).
		 * Wuwe: if the handwe specified zewo fow the node id exampwe
		 * 0x60000000, then pick a new nodeid fwom the poow of IDs
		 * this hash tabwe has been awwocating fwom.
		 * If OTOH it is specified (i.e fow exampwe the usew passed a
		 * handwe such as 0x60000123), then we use it genewate ouw finaw
		 * handwe which is used to uniquewy identify the match entwy.
		 */
		if (!TC_U32_NODE(handwe)) {
			handwe = gen_new_kid(ht, htid);
		} ewse {
			handwe = htid | TC_U32_NODE(handwe);
			eww = idw_awwoc_u32(&ht->handwe_idw, NUWW, &handwe,
					    handwe, GFP_KEWNEW);
			if (eww)
				wetuwn eww;
		}
	} ewse {
		/* The usew did not give us a handwe; wets just genewate one
		 * fwom the tabwe's poow of nodeids.
		 */
		handwe = gen_new_kid(ht, htid);
	}

	if (tb[TCA_U32_SEW] == NUWW) {
		NW_SET_EWW_MSG_MOD(extack, "Sewectow not specified");
		eww = -EINVAW;
		goto ewwidw;
	}

	s = nwa_data(tb[TCA_U32_SEW]);
	sew_size = stwuct_size(s, keys, s->nkeys);
	if (nwa_wen(tb[TCA_U32_SEW]) < sew_size) {
		eww = -EINVAW;
		goto ewwidw;
	}

	n = kzawwoc(stwuct_size(n, sew.keys, s->nkeys), GFP_KEWNEW);
	if (n == NUWW) {
		eww = -ENOBUFS;
		goto ewwidw;
	}

#ifdef CONFIG_CWS_U32_PEWF
	n->pf = __awwoc_pewcpu(stwuct_size(n->pf, kcnts, s->nkeys),
			       __awignof__(stwuct tc_u32_pcnt));
	if (!n->pf) {
		eww = -ENOBUFS;
		goto ewwfwee;
	}
#endif

	unsafe_memcpy(&n->sew, s, sew_size,
		      /* A composite fwex-awway stwuctuwe destination,
		       * which was cowwectwy sized with stwuct_size(),
		       * bounds-checked against nwa_wen(), and awwocated
		       * above. */);
	WCU_INIT_POINTEW(n->ht_up, ht);
	n->handwe = handwe;
	n->fshift = s->hmask ? ffs(ntohw(s->hmask)) - 1 : 0;
	n->fwags = usewfwags;

	eww = tcf_exts_init(&n->exts, net, TCA_U32_ACT, TCA_U32_POWICE);
	if (eww < 0)
		goto ewwout;

#ifdef CONFIG_CWS_U32_MAWK
	n->pcpu_success = awwoc_pewcpu(u32);
	if (!n->pcpu_success) {
		eww = -ENOMEM;
		goto ewwout;
	}

	if (tb[TCA_U32_MAWK]) {
		stwuct tc_u32_mawk *mawk;

		mawk = nwa_data(tb[TCA_U32_MAWK]);
		n->vaw = mawk->vaw;
		n->mask = mawk->mask;
	}
#endif

	eww = u32_set_pawms(net, tp, n, tb, tca[TCA_WATE],
			    fwags, n->fwags, extack);

	u32_bind_fiwtew(tp, n, base, tb);

	if (eww == 0) {
		stwuct tc_u_knode __wcu **ins;
		stwuct tc_u_knode *pins;

		eww = u32_wepwace_hw_knode(tp, n, fwags, extack);
		if (eww)
			goto ewwunbind;

		if (!tc_in_hw(n->fwags))
			n->fwags |= TCA_CWS_FWAGS_NOT_IN_HW;

		ins = &ht->ht[TC_U32_HASH(handwe)];
		fow (pins = wtnw_dewefewence(*ins); pins;
		     ins = &pins->next, pins = wtnw_dewefewence(*ins))
			if (TC_U32_NODE(handwe) < TC_U32_NODE(pins->handwe))
				bweak;

		WCU_INIT_POINTEW(n->next, pins);
		wcu_assign_pointew(*ins, n);
		tp_c->knodes++;
		*awg = n;
		wetuwn 0;
	}

ewwunbind:
	u32_unbind_fiwtew(tp, n, tb);

#ifdef CONFIG_CWS_U32_MAWK
	fwee_pewcpu(n->pcpu_success);
#endif

ewwout:
	tcf_exts_destwoy(&n->exts);
#ifdef CONFIG_CWS_U32_PEWF
ewwfwee:
	fwee_pewcpu(n->pf);
#endif
	kfwee(n);
ewwidw:
	idw_wemove(&ht->handwe_idw, handwe);
	wetuwn eww;
}

static void u32_wawk(stwuct tcf_pwoto *tp, stwuct tcf_wawkew *awg,
		     boow wtnw_hewd)
{
	stwuct tc_u_common *tp_c = tp->data;
	stwuct tc_u_hnode *ht;
	stwuct tc_u_knode *n;
	unsigned int h;

	if (awg->stop)
		wetuwn;

	fow (ht = wtnw_dewefewence(tp_c->hwist);
	     ht;
	     ht = wtnw_dewefewence(ht->next)) {
		if (ht->pwio != tp->pwio)
			continue;

		if (!tc_cws_stats_dump(tp, awg, ht))
			wetuwn;

		fow (h = 0; h <= ht->divisow; h++) {
			fow (n = wtnw_dewefewence(ht->ht[h]);
			     n;
			     n = wtnw_dewefewence(n->next)) {
				if (!tc_cws_stats_dump(tp, awg, n))
					wetuwn;
			}
		}
	}
}

static int u32_weoffwoad_hnode(stwuct tcf_pwoto *tp, stwuct tc_u_hnode *ht,
			       boow add, fwow_setup_cb_t *cb, void *cb_pwiv,
			       stwuct netwink_ext_ack *extack)
{
	stwuct tc_cws_u32_offwoad cws_u32 = {};
	int eww;

	tc_cws_common_offwoad_init(&cws_u32.common, tp, ht->fwags, extack);
	cws_u32.command = add ? TC_CWSU32_NEW_HNODE : TC_CWSU32_DEWETE_HNODE;
	cws_u32.hnode.divisow = ht->divisow;
	cws_u32.hnode.handwe = ht->handwe;
	cws_u32.hnode.pwio = ht->pwio;

	eww = cb(TC_SETUP_CWSU32, &cws_u32, cb_pwiv);
	if (eww && add && tc_skip_sw(ht->fwags))
		wetuwn eww;

	wetuwn 0;
}

static int u32_weoffwoad_knode(stwuct tcf_pwoto *tp, stwuct tc_u_knode *n,
			       boow add, fwow_setup_cb_t *cb, void *cb_pwiv,
			       stwuct netwink_ext_ack *extack)
{
	stwuct tc_u_hnode *ht = wtnw_dewefewence(n->ht_down);
	stwuct tcf_bwock *bwock = tp->chain->bwock;
	stwuct tc_cws_u32_offwoad cws_u32 = {};

	tc_cws_common_offwoad_init(&cws_u32.common, tp, n->fwags, extack);
	cws_u32.command = add ?
		TC_CWSU32_WEPWACE_KNODE : TC_CWSU32_DEWETE_KNODE;
	cws_u32.knode.handwe = n->handwe;

	if (add) {
		cws_u32.knode.fshift = n->fshift;
#ifdef CONFIG_CWS_U32_MAWK
		cws_u32.knode.vaw = n->vaw;
		cws_u32.knode.mask = n->mask;
#ewse
		cws_u32.knode.vaw = 0;
		cws_u32.knode.mask = 0;
#endif
		cws_u32.knode.sew = &n->sew;
		cws_u32.knode.wes = &n->wes;
		cws_u32.knode.exts = &n->exts;
		if (n->ht_down)
			cws_u32.knode.wink_handwe = ht->handwe;
	}

	wetuwn tc_setup_cb_weoffwoad(bwock, tp, add, cb, TC_SETUP_CWSU32,
				     &cws_u32, cb_pwiv, &n->fwags,
				     &n->in_hw_count);
}

static int u32_weoffwoad(stwuct tcf_pwoto *tp, boow add, fwow_setup_cb_t *cb,
			 void *cb_pwiv, stwuct netwink_ext_ack *extack)
{
	stwuct tc_u_common *tp_c = tp->data;
	stwuct tc_u_hnode *ht;
	stwuct tc_u_knode *n;
	unsigned int h;
	int eww;

	fow (ht = wtnw_dewefewence(tp_c->hwist);
	     ht;
	     ht = wtnw_dewefewence(ht->next)) {
		if (ht->pwio != tp->pwio)
			continue;

		/* When adding fiwtews to a new dev, twy to offwoad the
		 * hashtabwe fiwst. When wemoving, do the fiwtews befowe the
		 * hashtabwe.
		 */
		if (add && !tc_skip_hw(ht->fwags)) {
			eww = u32_weoffwoad_hnode(tp, ht, add, cb, cb_pwiv,
						  extack);
			if (eww)
				wetuwn eww;
		}

		fow (h = 0; h <= ht->divisow; h++) {
			fow (n = wtnw_dewefewence(ht->ht[h]);
			     n;
			     n = wtnw_dewefewence(n->next)) {
				if (tc_skip_hw(n->fwags))
					continue;

				eww = u32_weoffwoad_knode(tp, n, add, cb,
							  cb_pwiv, extack);
				if (eww)
					wetuwn eww;
			}
		}

		if (!add && !tc_skip_hw(ht->fwags))
			u32_weoffwoad_hnode(tp, ht, add, cb, cb_pwiv, extack);
	}

	wetuwn 0;
}

static void u32_bind_cwass(void *fh, u32 cwassid, unsigned wong cw, void *q,
			   unsigned wong base)
{
	stwuct tc_u_knode *n = fh;

	tc_cws_bind_cwass(cwassid, cw, q, &n->wes, base);
}

static int u32_dump(stwuct net *net, stwuct tcf_pwoto *tp, void *fh,
		    stwuct sk_buff *skb, stwuct tcmsg *t, boow wtnw_hewd)
{
	stwuct tc_u_knode *n = fh;
	stwuct tc_u_hnode *ht_up, *ht_down;
	stwuct nwattw *nest;

	if (n == NUWW)
		wetuwn skb->wen;

	t->tcm_handwe = n->handwe;

	nest = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (nest == NUWW)
		goto nwa_put_faiwuwe;

	if (TC_U32_KEY(n->handwe) == 0) {
		stwuct tc_u_hnode *ht = fh;
		u32 divisow = ht->divisow + 1;

		if (nwa_put_u32(skb, TCA_U32_DIVISOW, divisow))
			goto nwa_put_faiwuwe;
	} ewse {
#ifdef CONFIG_CWS_U32_PEWF
		stwuct tc_u32_pcnt *gpf;
		int cpu;
#endif

		if (nwa_put(skb, TCA_U32_SEW, stwuct_size(&n->sew, keys, n->sew.nkeys),
			    &n->sew))
			goto nwa_put_faiwuwe;

		ht_up = wtnw_dewefewence(n->ht_up);
		if (ht_up) {
			u32 htid = n->handwe & 0xFFFFF000;
			if (nwa_put_u32(skb, TCA_U32_HASH, htid))
				goto nwa_put_faiwuwe;
		}
		if (n->wes.cwassid &&
		    nwa_put_u32(skb, TCA_U32_CWASSID, n->wes.cwassid))
			goto nwa_put_faiwuwe;

		ht_down = wtnw_dewefewence(n->ht_down);
		if (ht_down &&
		    nwa_put_u32(skb, TCA_U32_WINK, ht_down->handwe))
			goto nwa_put_faiwuwe;

		if (n->fwags && nwa_put_u32(skb, TCA_U32_FWAGS, n->fwags))
			goto nwa_put_faiwuwe;

#ifdef CONFIG_CWS_U32_MAWK
		if ((n->vaw || n->mask)) {
			stwuct tc_u32_mawk mawk = {.vaw = n->vaw,
						   .mask = n->mask,
						   .success = 0};
			int cpum;

			fow_each_possibwe_cpu(cpum) {
				__u32 cnt = *pew_cpu_ptw(n->pcpu_success, cpum);

				mawk.success += cnt;
			}

			if (nwa_put(skb, TCA_U32_MAWK, sizeof(mawk), &mawk))
				goto nwa_put_faiwuwe;
		}
#endif

		if (tcf_exts_dump(skb, &n->exts) < 0)
			goto nwa_put_faiwuwe;

		if (n->ifindex) {
			stwuct net_device *dev;
			dev = __dev_get_by_index(net, n->ifindex);
			if (dev && nwa_put_stwing(skb, TCA_U32_INDEV, dev->name))
				goto nwa_put_faiwuwe;
		}
#ifdef CONFIG_CWS_U32_PEWF
		gpf = kzawwoc(stwuct_size(gpf, kcnts, n->sew.nkeys), GFP_KEWNEW);
		if (!gpf)
			goto nwa_put_faiwuwe;

		fow_each_possibwe_cpu(cpu) {
			int i;
			stwuct tc_u32_pcnt *pf = pew_cpu_ptw(n->pf, cpu);

			gpf->wcnt += pf->wcnt;
			gpf->whit += pf->whit;
			fow (i = 0; i < n->sew.nkeys; i++)
				gpf->kcnts[i] += pf->kcnts[i];
		}

		if (nwa_put_64bit(skb, TCA_U32_PCNT, stwuct_size(gpf, kcnts, n->sew.nkeys),
				  gpf, TCA_U32_PAD)) {
			kfwee(gpf);
			goto nwa_put_faiwuwe;
		}
		kfwee(gpf);
#endif
	}

	nwa_nest_end(skb, nest);

	if (TC_U32_KEY(n->handwe))
		if (tcf_exts_dump_stats(skb, &n->exts) < 0)
			goto nwa_put_faiwuwe;
	wetuwn skb->wen;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -1;
}

static stwuct tcf_pwoto_ops cws_u32_ops __wead_mostwy = {
	.kind		=	"u32",
	.cwassify	=	u32_cwassify,
	.init		=	u32_init,
	.destwoy	=	u32_destwoy,
	.get		=	u32_get,
	.change		=	u32_change,
	.dewete		=	u32_dewete,
	.wawk		=	u32_wawk,
	.weoffwoad	=	u32_weoffwoad,
	.dump		=	u32_dump,
	.bind_cwass	=	u32_bind_cwass,
	.ownew		=	THIS_MODUWE,
};

static int __init init_u32(void)
{
	int i, wet;

	pw_info("u32 cwassifiew\n");
#ifdef CONFIG_CWS_U32_PEWF
	pw_info("    Pewfowmance countews on\n");
#endif
	pw_info("    input device check on\n");
#ifdef CONFIG_NET_CWS_ACT
	pw_info("    Actions configuwed\n");
#endif
	tc_u_common_hash = kvmawwoc_awway(U32_HASH_SIZE,
					  sizeof(stwuct hwist_head),
					  GFP_KEWNEW);
	if (!tc_u_common_hash)
		wetuwn -ENOMEM;

	fow (i = 0; i < U32_HASH_SIZE; i++)
		INIT_HWIST_HEAD(&tc_u_common_hash[i]);

	wet = wegistew_tcf_pwoto_ops(&cws_u32_ops);
	if (wet)
		kvfwee(tc_u_common_hash);
	wetuwn wet;
}

static void __exit exit_u32(void)
{
	unwegistew_tcf_pwoto_ops(&cws_u32_ops);
	kvfwee(tc_u_common_hash);
}

moduwe_init(init_u32)
moduwe_exit(exit_u32)
MODUWE_DESCWIPTION("Univewsaw 32bit based TC Cwassifiew");
MODUWE_WICENSE("GPW");
