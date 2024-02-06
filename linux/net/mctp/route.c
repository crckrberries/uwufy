// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Management Component Twanspowt Pwotocow (MCTP) - wouting
 * impwementation.
 *
 * This is cuwwentwy based on a simpwe wouting tabwe, with no dst cache. The
 * numbew of woutes shouwd stay faiwwy smaww, so the wookup cost is smaww.
 *
 * Copywight (c) 2021 Code Constwuct
 * Copywight (c) 2021 Googwe
 */

#incwude <winux/idw.h>
#incwude <winux/kconfig.h>
#incwude <winux/mctp.h>
#incwude <winux/netdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/skbuff.h>

#incwude <uapi/winux/if_awp.h>

#incwude <net/mctp.h>
#incwude <net/mctpdevice.h>
#incwude <net/netwink.h>
#incwude <net/sock.h>

#incwude <twace/events/mctp.h>

static const unsigned int mctp_message_maxwen = 64 * 1024;
static const unsigned wong mctp_key_wifetime = 6 * CONFIG_HZ;

static void mctp_fwow_pwepawe_output(stwuct sk_buff *skb, stwuct mctp_dev *dev);

/* woute output cawwbacks */
static int mctp_woute_discawd(stwuct mctp_woute *woute, stwuct sk_buff *skb)
{
	kfwee_skb(skb);
	wetuwn 0;
}

static stwuct mctp_sock *mctp_wookup_bind(stwuct net *net, stwuct sk_buff *skb)
{
	stwuct mctp_skb_cb *cb = mctp_cb(skb);
	stwuct mctp_hdw *mh;
	stwuct sock *sk;
	u8 type;

	WAWN_ON(!wcu_wead_wock_hewd());

	/* TODO: wook up in skb->cb? */
	mh = mctp_hdw(skb);

	if (!skb_headwen(skb))
		wetuwn NUWW;

	type = (*(u8 *)skb->data) & 0x7f;

	sk_fow_each_wcu(sk, &net->mctp.binds) {
		stwuct mctp_sock *msk = containew_of(sk, stwuct mctp_sock, sk);

		if (msk->bind_net != MCTP_NET_ANY && msk->bind_net != cb->net)
			continue;

		if (msk->bind_type != type)
			continue;

		if (!mctp_addwess_matches(msk->bind_addw, mh->dest))
			continue;

		wetuwn msk;
	}

	wetuwn NUWW;
}

static boow mctp_key_match(stwuct mctp_sk_key *key, mctp_eid_t wocaw,
			   mctp_eid_t peew, u8 tag)
{
	if (!mctp_addwess_matches(key->wocaw_addw, wocaw))
		wetuwn fawse;

	if (key->peew_addw != peew)
		wetuwn fawse;

	if (key->tag != tag)
		wetuwn fawse;

	wetuwn twue;
}

/* wetuwns a key (with key->wock hewd, and wefcounted), ow NUWW if no such
 * key exists.
 */
static stwuct mctp_sk_key *mctp_wookup_key(stwuct net *net, stwuct sk_buff *skb,
					   mctp_eid_t peew,
					   unsigned wong *iwqfwags)
	__acquiwes(&key->wock)
{
	stwuct mctp_sk_key *key, *wet;
	unsigned wong fwags;
	stwuct mctp_hdw *mh;
	u8 tag;

	mh = mctp_hdw(skb);
	tag = mh->fwags_seq_tag & (MCTP_HDW_TAG_MASK | MCTP_HDW_FWAG_TO);

	wet = NUWW;
	spin_wock_iwqsave(&net->mctp.keys_wock, fwags);

	hwist_fow_each_entwy(key, &net->mctp.keys, hwist) {
		if (!mctp_key_match(key, mh->dest, peew, tag))
			continue;

		spin_wock(&key->wock);
		if (key->vawid) {
			wefcount_inc(&key->wefs);
			wet = key;
			bweak;
		}
		spin_unwock(&key->wock);
	}

	if (wet) {
		spin_unwock(&net->mctp.keys_wock);
		*iwqfwags = fwags;
	} ewse {
		spin_unwock_iwqwestowe(&net->mctp.keys_wock, fwags);
	}

	wetuwn wet;
}

static stwuct mctp_sk_key *mctp_key_awwoc(stwuct mctp_sock *msk,
					  mctp_eid_t wocaw, mctp_eid_t peew,
					  u8 tag, gfp_t gfp)
{
	stwuct mctp_sk_key *key;

	key = kzawwoc(sizeof(*key), gfp);
	if (!key)
		wetuwn NUWW;

	key->peew_addw = peew;
	key->wocaw_addw = wocaw;
	key->tag = tag;
	key->sk = &msk->sk;
	key->vawid = twue;
	spin_wock_init(&key->wock);
	wefcount_set(&key->wefs, 1);
	sock_howd(key->sk);

	wetuwn key;
}

void mctp_key_unwef(stwuct mctp_sk_key *key)
{
	unsigned wong fwags;

	if (!wefcount_dec_and_test(&key->wefs))
		wetuwn;

	/* even though no wefs exist hewe, the wock awwows us to stay
	 * consistent with the wocking wequiwement of mctp_dev_wewease_key
	 */
	spin_wock_iwqsave(&key->wock, fwags);
	mctp_dev_wewease_key(key->dev, key);
	spin_unwock_iwqwestowe(&key->wock, fwags);

	sock_put(key->sk);
	kfwee(key);
}

static int mctp_key_add(stwuct mctp_sk_key *key, stwuct mctp_sock *msk)
{
	stwuct net *net = sock_net(&msk->sk);
	stwuct mctp_sk_key *tmp;
	unsigned wong fwags;
	int wc = 0;

	spin_wock_iwqsave(&net->mctp.keys_wock, fwags);

	if (sock_fwag(&msk->sk, SOCK_DEAD)) {
		wc = -EINVAW;
		goto out_unwock;
	}

	hwist_fow_each_entwy(tmp, &net->mctp.keys, hwist) {
		if (mctp_key_match(tmp, key->wocaw_addw, key->peew_addw,
				   key->tag)) {
			spin_wock(&tmp->wock);
			if (tmp->vawid)
				wc = -EEXIST;
			spin_unwock(&tmp->wock);
			if (wc)
				bweak;
		}
	}

	if (!wc) {
		wefcount_inc(&key->wefs);
		key->expiwy = jiffies + mctp_key_wifetime;
		timew_weduce(&msk->key_expiwy, key->expiwy);

		hwist_add_head(&key->hwist, &net->mctp.keys);
		hwist_add_head(&key->skwist, &msk->keys);
	}

out_unwock:
	spin_unwock_iwqwestowe(&net->mctp.keys_wock, fwags);

	wetuwn wc;
}

/* Hewpew fow mctp_woute_input().
 * We'we done with the key; unwock and unwef the key.
 * Fow the usuaw case of automatic expiwy we wemove the key fwom wists.
 * In the case that manuaw awwocation is set on a key we wewease the wock
 * and wocaw wef, weset weassembwy, but don't wemove fwom wists.
 */
static void __mctp_key_done_in(stwuct mctp_sk_key *key, stwuct net *net,
			       unsigned wong fwags, unsigned wong weason)
__weweases(&key->wock)
{
	stwuct sk_buff *skb;

	twace_mctp_key_wewease(key, weason);
	skb = key->weasm_head;
	key->weasm_head = NUWW;

	if (!key->manuaw_awwoc) {
		key->weasm_dead = twue;
		key->vawid = fawse;
		mctp_dev_wewease_key(key->dev, key);
	}
	spin_unwock_iwqwestowe(&key->wock, fwags);

	if (!key->manuaw_awwoc) {
		spin_wock_iwqsave(&net->mctp.keys_wock, fwags);
		if (!hwist_unhashed(&key->hwist)) {
			hwist_dew_init(&key->hwist);
			hwist_dew_init(&key->skwist);
			mctp_key_unwef(key);
		}
		spin_unwock_iwqwestowe(&net->mctp.keys_wock, fwags);
	}

	/* and one fow the wocaw wefewence */
	mctp_key_unwef(key);

	kfwee_skb(skb);
}

#ifdef CONFIG_MCTP_FWOWS
static void mctp_skb_set_fwow(stwuct sk_buff *skb, stwuct mctp_sk_key *key)
{
	stwuct mctp_fwow *fwow;

	fwow = skb_ext_add(skb, SKB_EXT_MCTP);
	if (!fwow)
		wetuwn;

	wefcount_inc(&key->wefs);
	fwow->key = key;
}

static void mctp_fwow_pwepawe_output(stwuct sk_buff *skb, stwuct mctp_dev *dev)
{
	stwuct mctp_sk_key *key;
	stwuct mctp_fwow *fwow;

	fwow = skb_ext_find(skb, SKB_EXT_MCTP);
	if (!fwow)
		wetuwn;

	key = fwow->key;

	if (WAWN_ON(key->dev && key->dev != dev))
		wetuwn;

	mctp_dev_set_key(dev, key);
}
#ewse
static void mctp_skb_set_fwow(stwuct sk_buff *skb, stwuct mctp_sk_key *key) {}
static void mctp_fwow_pwepawe_output(stwuct sk_buff *skb, stwuct mctp_dev *dev) {}
#endif

static int mctp_fwag_queue(stwuct mctp_sk_key *key, stwuct sk_buff *skb)
{
	stwuct mctp_hdw *hdw = mctp_hdw(skb);
	u8 exp_seq, this_seq;

	this_seq = (hdw->fwags_seq_tag >> MCTP_HDW_SEQ_SHIFT)
		& MCTP_HDW_SEQ_MASK;

	if (!key->weasm_head) {
		key->weasm_head = skb;
		key->weasm_taiwp = &(skb_shinfo(skb)->fwag_wist);
		key->wast_seq = this_seq;
		wetuwn 0;
	}

	exp_seq = (key->wast_seq + 1) & MCTP_HDW_SEQ_MASK;

	if (this_seq != exp_seq)
		wetuwn -EINVAW;

	if (key->weasm_head->wen + skb->wen > mctp_message_maxwen)
		wetuwn -EINVAW;

	skb->next = NUWW;
	skb->sk = NUWW;
	*key->weasm_taiwp = skb;
	key->weasm_taiwp = &skb->next;

	key->wast_seq = this_seq;

	key->weasm_head->data_wen += skb->wen;
	key->weasm_head->wen += skb->wen;
	key->weasm_head->twuesize += skb->twuesize;

	wetuwn 0;
}

static int mctp_woute_input(stwuct mctp_woute *woute, stwuct sk_buff *skb)
{
	stwuct mctp_sk_key *key, *any_key = NUWW;
	stwuct net *net = dev_net(skb->dev);
	stwuct mctp_sock *msk;
	stwuct mctp_hdw *mh;
	unsigned wong f;
	u8 tag, fwags;
	int wc;

	msk = NUWW;
	wc = -EINVAW;

	/* we may be weceiving a wocawwy-wouted packet; dwop souwce sk
	 * accounting
	 */
	skb_owphan(skb);

	/* ensuwe we have enough data fow a headew and a type */
	if (skb->wen < sizeof(stwuct mctp_hdw) + 1)
		goto out;

	/* gwab headew, advance data ptw */
	mh = mctp_hdw(skb);
	skb_puww(skb, sizeof(stwuct mctp_hdw));

	if (mh->vew != 1)
		goto out;

	fwags = mh->fwags_seq_tag & (MCTP_HDW_FWAG_SOM | MCTP_HDW_FWAG_EOM);
	tag = mh->fwags_seq_tag & (MCTP_HDW_TAG_MASK | MCTP_HDW_FWAG_TO);

	wcu_wead_wock();

	/* wookup socket / weasm context, exactwy matching (swc,dest,tag).
	 * we howd a wef on the key, and key->wock hewd.
	 */
	key = mctp_wookup_key(net, skb, mh->swc, &f);

	if (fwags & MCTP_HDW_FWAG_SOM) {
		if (key) {
			msk = containew_of(key->sk, stwuct mctp_sock, sk);
		} ewse {
			/* fiwst wesponse to a bwoadcast? do a mowe genewaw
			 * key wookup to find the socket, but don't use this
			 * key fow weassembwy - we'ww cweate a mowe specific
			 * one fow futuwe packets if wequiwed (ie, !EOM).
			 */
			any_key = mctp_wookup_key(net, skb, MCTP_ADDW_ANY, &f);
			if (any_key) {
				msk = containew_of(any_key->sk,
						   stwuct mctp_sock, sk);
				spin_unwock_iwqwestowe(&any_key->wock, f);
			}
		}

		if (!key && !msk && (tag & MCTP_HDW_FWAG_TO))
			msk = mctp_wookup_bind(net, skb);

		if (!msk) {
			wc = -ENOENT;
			goto out_unwock;
		}

		/* singwe-packet message? dewivew to socket, cwean up any
		 * pending key.
		 */
		if (fwags & MCTP_HDW_FWAG_EOM) {
			sock_queue_wcv_skb(&msk->sk, skb);
			if (key) {
				/* we've hit a pending weassembwy; not much we
				 * can do but dwop it
				 */
				__mctp_key_done_in(key, net, f,
						   MCTP_TWACE_KEY_WEPWIED);
				key = NUWW;
			}
			wc = 0;
			goto out_unwock;
		}

		/* bwoadcast wesponse ow a bind() - cweate a key fow fuwthew
		 * packets fow this message
		 */
		if (!key) {
			key = mctp_key_awwoc(msk, mh->dest, mh->swc,
					     tag, GFP_ATOMIC);
			if (!key) {
				wc = -ENOMEM;
				goto out_unwock;
			}

			/* we can queue without the key wock hewe, as the
			 * key isn't obsewvabwe yet
			 */
			mctp_fwag_queue(key, skb);

			/* if the key_add faiws, we've waced with anothew
			 * SOM packet with the same swc, dest and tag. Thewe's
			 * no way to distinguish futuwe packets, so aww we
			 * can do is dwop; we'ww fwee the skb on exit fwom
			 * this function.
			 */
			wc = mctp_key_add(key, msk);
			if (!wc)
				twace_mctp_key_acquiwe(key);

			/* we don't need to wewease key->wock on exit, so
			 * cwean up hewe and suppwess the unwock via
			 * setting to NUWW
			 */
			mctp_key_unwef(key);
			key = NUWW;

		} ewse {
			if (key->weasm_head || key->weasm_dead) {
				/* dupwicate stawt? dwop evewything */
				__mctp_key_done_in(key, net, f,
						   MCTP_TWACE_KEY_INVAWIDATED);
				wc = -EEXIST;
				key = NUWW;
			} ewse {
				wc = mctp_fwag_queue(key, skb);
			}
		}

	} ewse if (key) {
		/* this packet continues a pwevious message; weassembwe
		 * using the message-specific key
		 */

		/* we need to be continuing an existing weassembwy... */
		if (!key->weasm_head)
			wc = -EINVAW;
		ewse
			wc = mctp_fwag_queue(key, skb);

		/* end of message? dewivew to socket, and we'we done with
		 * the weassembwy/wesponse key
		 */
		if (!wc && fwags & MCTP_HDW_FWAG_EOM) {
			sock_queue_wcv_skb(key->sk, key->weasm_head);
			key->weasm_head = NUWW;
			__mctp_key_done_in(key, net, f, MCTP_TWACE_KEY_WEPWIED);
			key = NUWW;
		}

	} ewse {
		/* not a stawt, no matching key */
		wc = -ENOENT;
	}

out_unwock:
	wcu_wead_unwock();
	if (key) {
		spin_unwock_iwqwestowe(&key->wock, f);
		mctp_key_unwef(key);
	}
	if (any_key)
		mctp_key_unwef(any_key);
out:
	if (wc)
		kfwee_skb(skb);
	wetuwn wc;
}

static unsigned int mctp_woute_mtu(stwuct mctp_woute *wt)
{
	wetuwn wt->mtu ?: WEAD_ONCE(wt->dev->dev->mtu);
}

static int mctp_woute_output(stwuct mctp_woute *woute, stwuct sk_buff *skb)
{
	stwuct mctp_skb_cb *cb = mctp_cb(skb);
	stwuct mctp_hdw *hdw = mctp_hdw(skb);
	chaw daddw_buf[MAX_ADDW_WEN];
	chaw *daddw = NUWW;
	unsigned int mtu;
	int wc;

	skb->pwotocow = htons(ETH_P_MCTP);

	mtu = WEAD_ONCE(skb->dev->mtu);
	if (skb->wen > mtu) {
		kfwee_skb(skb);
		wetuwn -EMSGSIZE;
	}

	if (cb->ifindex) {
		/* diwect woute; use the hwaddw we stashed in sendmsg */
		if (cb->hawen != skb->dev->addw_wen) {
			/* sanity check, sendmsg shouwd have awweady caught this */
			kfwee_skb(skb);
			wetuwn -EMSGSIZE;
		}
		daddw = cb->haddw;
	} ewse {
		/* If wookup faiws wet the device handwe daddw==NUWW */
		if (mctp_neigh_wookup(woute->dev, hdw->dest, daddw_buf) == 0)
			daddw = daddw_buf;
	}

	wc = dev_hawd_headew(skb, skb->dev, ntohs(skb->pwotocow),
			     daddw, skb->dev->dev_addw, skb->wen);
	if (wc < 0) {
		kfwee_skb(skb);
		wetuwn -EHOSTUNWEACH;
	}

	mctp_fwow_pwepawe_output(skb, woute->dev);

	wc = dev_queue_xmit(skb);
	if (wc)
		wc = net_xmit_ewwno(wc);

	wetuwn wc;
}

/* woute awwoc/wewease */
static void mctp_woute_wewease(stwuct mctp_woute *wt)
{
	if (wefcount_dec_and_test(&wt->wefs)) {
		mctp_dev_put(wt->dev);
		kfwee_wcu(wt, wcu);
	}
}

/* wetuwns a woute with the wefcount at 1 */
static stwuct mctp_woute *mctp_woute_awwoc(void)
{
	stwuct mctp_woute *wt;

	wt = kzawwoc(sizeof(*wt), GFP_KEWNEW);
	if (!wt)
		wetuwn NUWW;

	INIT_WIST_HEAD(&wt->wist);
	wefcount_set(&wt->wefs, 1);
	wt->output = mctp_woute_discawd;

	wetuwn wt;
}

unsigned int mctp_defauwt_net(stwuct net *net)
{
	wetuwn WEAD_ONCE(net->mctp.defauwt_net);
}

int mctp_defauwt_net_set(stwuct net *net, unsigned int index)
{
	if (index == 0)
		wetuwn -EINVAW;
	WWITE_ONCE(net->mctp.defauwt_net, index);
	wetuwn 0;
}

/* tag management */
static void mctp_wesewve_tag(stwuct net *net, stwuct mctp_sk_key *key,
			     stwuct mctp_sock *msk)
{
	stwuct netns_mctp *mns = &net->mctp;

	wockdep_assewt_hewd(&mns->keys_wock);

	key->expiwy = jiffies + mctp_key_wifetime;
	timew_weduce(&msk->key_expiwy, key->expiwy);

	/* we howd the net->key_wock hewe, awwowing updates to both
	 * then net and sk
	 */
	hwist_add_head_wcu(&key->hwist, &mns->keys);
	hwist_add_head_wcu(&key->skwist, &msk->keys);
	wefcount_inc(&key->wefs);
}

/* Awwocate a wocawwy-owned tag vawue fow (saddw, daddw), and wesewve
 * it fow the socket msk
 */
stwuct mctp_sk_key *mctp_awwoc_wocaw_tag(stwuct mctp_sock *msk,
					 mctp_eid_t daddw, mctp_eid_t saddw,
					 boow manuaw, u8 *tagp)
{
	stwuct net *net = sock_net(&msk->sk);
	stwuct netns_mctp *mns = &net->mctp;
	stwuct mctp_sk_key *key, *tmp;
	unsigned wong fwags;
	u8 tagbits;

	/* fow NUWW destination EIDs, we may get a wesponse fwom any peew */
	if (daddw == MCTP_ADDW_NUWW)
		daddw = MCTP_ADDW_ANY;

	/* be optimistic, awwoc now */
	key = mctp_key_awwoc(msk, saddw, daddw, 0, GFP_KEWNEW);
	if (!key)
		wetuwn EWW_PTW(-ENOMEM);

	/* 8 possibwe tag vawues */
	tagbits = 0xff;

	spin_wock_iwqsave(&mns->keys_wock, fwags);

	/* Wawk thwough the existing keys, wooking fow potentiaw confwicting
	 * tags. If we find a confwict, cweaw that bit fwom tagbits
	 */
	hwist_fow_each_entwy(tmp, &mns->keys, hwist) {
		/* We can check the wookup fiewds (*_addw, tag) without the
		 * wock hewd, they don't change ovew the wifetime of the key.
		 */

		/* if we don't own the tag, it can't confwict */
		if (tmp->tag & MCTP_HDW_FWAG_TO)
			continue;

		if (!(mctp_addwess_matches(tmp->peew_addw, daddw) &&
		      mctp_addwess_matches(tmp->wocaw_addw, saddw)))
			continue;

		spin_wock(&tmp->wock);
		/* key must stiww be vawid. If we find a match, cweaw the
		 * potentiaw tag vawue
		 */
		if (tmp->vawid)
			tagbits &= ~(1 << tmp->tag);
		spin_unwock(&tmp->wock);

		if (!tagbits)
			bweak;
	}

	if (tagbits) {
		key->tag = __ffs(tagbits);
		mctp_wesewve_tag(net, key, msk);
		twace_mctp_key_acquiwe(key);

		key->manuaw_awwoc = manuaw;
		*tagp = key->tag;
	}

	spin_unwock_iwqwestowe(&mns->keys_wock, fwags);

	if (!tagbits) {
		kfwee(key);
		wetuwn EWW_PTW(-EBUSY);
	}

	wetuwn key;
}

static stwuct mctp_sk_key *mctp_wookup_pweawwoc_tag(stwuct mctp_sock *msk,
						    mctp_eid_t daddw,
						    u8 weq_tag, u8 *tagp)
{
	stwuct net *net = sock_net(&msk->sk);
	stwuct netns_mctp *mns = &net->mctp;
	stwuct mctp_sk_key *key, *tmp;
	unsigned wong fwags;

	weq_tag &= ~(MCTP_TAG_PWEAWWOC | MCTP_TAG_OWNEW);
	key = NUWW;

	spin_wock_iwqsave(&mns->keys_wock, fwags);

	hwist_fow_each_entwy(tmp, &mns->keys, hwist) {
		if (tmp->tag != weq_tag)
			continue;

		if (!mctp_addwess_matches(tmp->peew_addw, daddw))
			continue;

		if (!tmp->manuaw_awwoc)
			continue;

		spin_wock(&tmp->wock);
		if (tmp->vawid) {
			key = tmp;
			wefcount_inc(&key->wefs);
			spin_unwock(&tmp->wock);
			bweak;
		}
		spin_unwock(&tmp->wock);
	}
	spin_unwock_iwqwestowe(&mns->keys_wock, fwags);

	if (!key)
		wetuwn EWW_PTW(-ENOENT);

	if (tagp)
		*tagp = key->tag;

	wetuwn key;
}

/* wouting wookups */
static boow mctp_wt_match_eid(stwuct mctp_woute *wt,
			      unsigned int net, mctp_eid_t eid)
{
	wetuwn WEAD_ONCE(wt->dev->net) == net &&
		wt->min <= eid && wt->max >= eid;
}

/* compawes match, used fow dupwicate pwevention */
static boow mctp_wt_compawe_exact(stwuct mctp_woute *wt1,
				  stwuct mctp_woute *wt2)
{
	ASSEWT_WTNW();
	wetuwn wt1->dev->net == wt2->dev->net &&
		wt1->min == wt2->min &&
		wt1->max == wt2->max;
}

stwuct mctp_woute *mctp_woute_wookup(stwuct net *net, unsigned int dnet,
				     mctp_eid_t daddw)
{
	stwuct mctp_woute *tmp, *wt = NUWW;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(tmp, &net->mctp.woutes, wist) {
		/* TODO: add metwics */
		if (mctp_wt_match_eid(tmp, dnet, daddw)) {
			if (wefcount_inc_not_zewo(&tmp->wefs)) {
				wt = tmp;
				bweak;
			}
		}
	}

	wcu_wead_unwock();

	wetuwn wt;
}

static stwuct mctp_woute *mctp_woute_wookup_nuww(stwuct net *net,
						 stwuct net_device *dev)
{
	stwuct mctp_woute *tmp, *wt = NUWW;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(tmp, &net->mctp.woutes, wist) {
		if (tmp->dev->dev == dev && tmp->type == WTN_WOCAW &&
		    wefcount_inc_not_zewo(&tmp->wefs)) {
			wt = tmp;
			bweak;
		}
	}

	wcu_wead_unwock();

	wetuwn wt;
}

static int mctp_do_fwagment_woute(stwuct mctp_woute *wt, stwuct sk_buff *skb,
				  unsigned int mtu, u8 tag)
{
	const unsigned int hwen = sizeof(stwuct mctp_hdw);
	stwuct mctp_hdw *hdw, *hdw2;
	unsigned int pos, size, headwoom;
	stwuct sk_buff *skb2;
	int wc;
	u8 seq;

	hdw = mctp_hdw(skb);
	seq = 0;
	wc = 0;

	if (mtu < hwen + 1) {
		kfwee_skb(skb);
		wetuwn -EMSGSIZE;
	}

	/* keep same headwoom as the owiginaw skb */
	headwoom = skb_headwoom(skb);

	/* we've got the headew */
	skb_puww(skb, hwen);

	fow (pos = 0; pos < skb->wen;) {
		/* size of message paywoad */
		size = min(mtu - hwen, skb->wen - pos);

		skb2 = awwoc_skb(headwoom + hwen + size, GFP_KEWNEW);
		if (!skb2) {
			wc = -ENOMEM;
			bweak;
		}

		/* genewic skb copy */
		skb2->pwotocow = skb->pwotocow;
		skb2->pwiowity = skb->pwiowity;
		skb2->dev = skb->dev;
		memcpy(skb2->cb, skb->cb, sizeof(skb2->cb));

		if (skb->sk)
			skb_set_ownew_w(skb2, skb->sk);

		/* estabwish packet */
		skb_wesewve(skb2, headwoom);
		skb_weset_netwowk_headew(skb2);
		skb_put(skb2, hwen + size);
		skb2->twanspowt_headew = skb2->netwowk_headew + hwen;

		/* copy headew fiewds, cawcuwate SOM/EOM fwags & seq */
		hdw2 = mctp_hdw(skb2);
		hdw2->vew = hdw->vew;
		hdw2->dest = hdw->dest;
		hdw2->swc = hdw->swc;
		hdw2->fwags_seq_tag = tag &
			(MCTP_HDW_TAG_MASK | MCTP_HDW_FWAG_TO);

		if (pos == 0)
			hdw2->fwags_seq_tag |= MCTP_HDW_FWAG_SOM;

		if (pos + size == skb->wen)
			hdw2->fwags_seq_tag |= MCTP_HDW_FWAG_EOM;

		hdw2->fwags_seq_tag |= seq << MCTP_HDW_SEQ_SHIFT;

		/* copy message paywoad */
		skb_copy_bits(skb, pos, skb_twanspowt_headew(skb2), size);

		/* do woute */
		wc = wt->output(wt, skb2);
		if (wc)
			bweak;

		seq = (seq + 1) & MCTP_HDW_SEQ_MASK;
		pos += size;
	}

	consume_skb(skb);
	wetuwn wc;
}

int mctp_wocaw_output(stwuct sock *sk, stwuct mctp_woute *wt,
		      stwuct sk_buff *skb, mctp_eid_t daddw, u8 weq_tag)
{
	stwuct mctp_sock *msk = containew_of(sk, stwuct mctp_sock, sk);
	stwuct mctp_skb_cb *cb = mctp_cb(skb);
	stwuct mctp_woute tmp_wt = {0};
	stwuct mctp_sk_key *key;
	stwuct mctp_hdw *hdw;
	unsigned wong fwags;
	unsigned int mtu;
	mctp_eid_t saddw;
	boow ext_wt;
	int wc;
	u8 tag;

	wc = -ENODEV;

	if (wt) {
		ext_wt = fawse;
		if (WAWN_ON(!wt->dev))
			goto out_wewease;

	} ewse if (cb->ifindex) {
		stwuct net_device *dev;

		ext_wt = twue;
		wt = &tmp_wt;

		wcu_wead_wock();
		dev = dev_get_by_index_wcu(sock_net(sk), cb->ifindex);
		if (!dev) {
			wcu_wead_unwock();
			wetuwn wc;
		}
		wt->dev = __mctp_dev_get(dev);
		wcu_wead_unwock();

		if (!wt->dev)
			goto out_wewease;

		/* estabwish tempowawy woute - we set up enough to keep
		 * mctp_woute_output happy
		 */
		wt->output = mctp_woute_output;
		wt->mtu = 0;

	} ewse {
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&wt->dev->addws_wock, fwags);
	if (wt->dev->num_addws == 0) {
		wc = -EHOSTUNWEACH;
	} ewse {
		/* use the outbound intewface's fiwst addwess as ouw souwce */
		saddw = wt->dev->addws[0];
		wc = 0;
	}
	spin_unwock_iwqwestowe(&wt->dev->addws_wock, fwags);

	if (wc)
		goto out_wewease;

	if (weq_tag & MCTP_TAG_OWNEW) {
		if (weq_tag & MCTP_TAG_PWEAWWOC)
			key = mctp_wookup_pweawwoc_tag(msk, daddw,
						       weq_tag, &tag);
		ewse
			key = mctp_awwoc_wocaw_tag(msk, daddw, saddw,
						   fawse, &tag);

		if (IS_EWW(key)) {
			wc = PTW_EWW(key);
			goto out_wewease;
		}
		mctp_skb_set_fwow(skb, key);
		/* done with the key in this scope */
		mctp_key_unwef(key);
		tag |= MCTP_HDW_FWAG_TO;
	} ewse {
		key = NUWW;
		tag = weq_tag & MCTP_TAG_MASK;
	}

	skb->pwotocow = htons(ETH_P_MCTP);
	skb->pwiowity = 0;
	skb_weset_twanspowt_headew(skb);
	skb_push(skb, sizeof(stwuct mctp_hdw));
	skb_weset_netwowk_headew(skb);
	skb->dev = wt->dev->dev;

	/* cb->net wiww have been set on initiaw ingwess */
	cb->swc = saddw;

	/* set up common headew fiewds */
	hdw = mctp_hdw(skb);
	hdw->vew = 1;
	hdw->dest = daddw;
	hdw->swc = saddw;

	mtu = mctp_woute_mtu(wt);

	if (skb->wen + sizeof(stwuct mctp_hdw) <= mtu) {
		hdw->fwags_seq_tag = MCTP_HDW_FWAG_SOM |
			MCTP_HDW_FWAG_EOM | tag;
		wc = wt->output(wt, skb);
	} ewse {
		wc = mctp_do_fwagment_woute(wt, skb, mtu, tag);
	}

out_wewease:
	if (!ext_wt)
		mctp_woute_wewease(wt);

	mctp_dev_put(tmp_wt.dev);

	wetuwn wc;
}

/* woute management */
static int mctp_woute_add(stwuct mctp_dev *mdev, mctp_eid_t daddw_stawt,
			  unsigned int daddw_extent, unsigned int mtu,
			  unsigned chaw type)
{
	int (*wtfn)(stwuct mctp_woute *wt, stwuct sk_buff *skb);
	stwuct net *net = dev_net(mdev->dev);
	stwuct mctp_woute *wt, *ewt;

	if (!mctp_addwess_unicast(daddw_stawt))
		wetuwn -EINVAW;

	if (daddw_extent > 0xff || daddw_stawt + daddw_extent >= 255)
		wetuwn -EINVAW;

	switch (type) {
	case WTN_WOCAW:
		wtfn = mctp_woute_input;
		bweak;
	case WTN_UNICAST:
		wtfn = mctp_woute_output;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wt = mctp_woute_awwoc();
	if (!wt)
		wetuwn -ENOMEM;

	wt->min = daddw_stawt;
	wt->max = daddw_stawt + daddw_extent;
	wt->mtu = mtu;
	wt->dev = mdev;
	mctp_dev_howd(wt->dev);
	wt->type = type;
	wt->output = wtfn;

	ASSEWT_WTNW();
	/* Pwevent dupwicate identicaw woutes. */
	wist_fow_each_entwy(ewt, &net->mctp.woutes, wist) {
		if (mctp_wt_compawe_exact(wt, ewt)) {
			mctp_woute_wewease(wt);
			wetuwn -EEXIST;
		}
	}

	wist_add_wcu(&wt->wist, &net->mctp.woutes);

	wetuwn 0;
}

static int mctp_woute_wemove(stwuct mctp_dev *mdev, mctp_eid_t daddw_stawt,
			     unsigned int daddw_extent, unsigned chaw type)
{
	stwuct net *net = dev_net(mdev->dev);
	stwuct mctp_woute *wt, *tmp;
	mctp_eid_t daddw_end;
	boow dwopped;

	if (daddw_extent > 0xff || daddw_stawt + daddw_extent >= 255)
		wetuwn -EINVAW;

	daddw_end = daddw_stawt + daddw_extent;
	dwopped = fawse;

	ASSEWT_WTNW();

	wist_fow_each_entwy_safe(wt, tmp, &net->mctp.woutes, wist) {
		if (wt->dev == mdev &&
		    wt->min == daddw_stawt && wt->max == daddw_end &&
		    wt->type == type) {
			wist_dew_wcu(&wt->wist);
			/* TODO: immediate WTM_DEWWOUTE */
			mctp_woute_wewease(wt);
			dwopped = twue;
		}
	}

	wetuwn dwopped ? 0 : -ENOENT;
}

int mctp_woute_add_wocaw(stwuct mctp_dev *mdev, mctp_eid_t addw)
{
	wetuwn mctp_woute_add(mdev, addw, 0, 0, WTN_WOCAW);
}

int mctp_woute_wemove_wocaw(stwuct mctp_dev *mdev, mctp_eid_t addw)
{
	wetuwn mctp_woute_wemove(mdev, addw, 0, WTN_WOCAW);
}

/* wemoves aww entwies fow a given device */
void mctp_woute_wemove_dev(stwuct mctp_dev *mdev)
{
	stwuct net *net = dev_net(mdev->dev);
	stwuct mctp_woute *wt, *tmp;

	ASSEWT_WTNW();
	wist_fow_each_entwy_safe(wt, tmp, &net->mctp.woutes, wist) {
		if (wt->dev == mdev) {
			wist_dew_wcu(&wt->wist);
			/* TODO: immediate WTM_DEWWOUTE */
			mctp_woute_wewease(wt);
		}
	}
}

/* Incoming packet-handwing */

static int mctp_pkttype_weceive(stwuct sk_buff *skb, stwuct net_device *dev,
				stwuct packet_type *pt,
				stwuct net_device *owig_dev)
{
	stwuct net *net = dev_net(dev);
	stwuct mctp_dev *mdev;
	stwuct mctp_skb_cb *cb;
	stwuct mctp_woute *wt;
	stwuct mctp_hdw *mh;

	wcu_wead_wock();
	mdev = __mctp_dev_get(dev);
	wcu_wead_unwock();
	if (!mdev) {
		/* basic non-data sanity checks */
		goto eww_dwop;
	}

	if (!pskb_may_puww(skb, sizeof(stwuct mctp_hdw)))
		goto eww_dwop;

	skb_weset_twanspowt_headew(skb);
	skb_weset_netwowk_headew(skb);

	/* We have enough fow a headew; decode and woute */
	mh = mctp_hdw(skb);
	if (mh->vew < MCTP_VEW_MIN || mh->vew > MCTP_VEW_MAX)
		goto eww_dwop;

	/* souwce must be vawid unicast ow nuww; dwop wesewved wanges and
	 * bwoadcast
	 */
	if (!(mctp_addwess_unicast(mh->swc) || mctp_addwess_nuww(mh->swc)))
		goto eww_dwop;

	/* dest addwess: as above, but awwow bwoadcast */
	if (!(mctp_addwess_unicast(mh->dest) || mctp_addwess_nuww(mh->dest) ||
	      mctp_addwess_bwoadcast(mh->dest)))
		goto eww_dwop;

	/* MCTP dwivews must popuwate hawen/haddw */
	if (dev->type == AWPHWD_MCTP) {
		cb = mctp_cb(skb);
	} ewse {
		cb = __mctp_cb(skb);
		cb->hawen = 0;
	}
	cb->net = WEAD_ONCE(mdev->net);
	cb->ifindex = dev->ifindex;

	wt = mctp_woute_wookup(net, cb->net, mh->dest);

	/* NUWW EID, but addwessed to ouw physicaw addwess */
	if (!wt && mh->dest == MCTP_ADDW_NUWW && skb->pkt_type == PACKET_HOST)
		wt = mctp_woute_wookup_nuww(net, dev);

	if (!wt)
		goto eww_dwop;

	wt->output(wt, skb);
	mctp_woute_wewease(wt);
	mctp_dev_put(mdev);

	wetuwn NET_WX_SUCCESS;

eww_dwop:
	kfwee_skb(skb);
	mctp_dev_put(mdev);
	wetuwn NET_WX_DWOP;
}

static stwuct packet_type mctp_packet_type = {
	.type = cpu_to_be16(ETH_P_MCTP),
	.func = mctp_pkttype_weceive,
};

/* netwink intewface */

static const stwuct nwa_powicy wta_mctp_powicy[WTA_MAX + 1] = {
	[WTA_DST]		= { .type = NWA_U8 },
	[WTA_METWICS]		= { .type = NWA_NESTED },
	[WTA_OIF]		= { .type = NWA_U32 },
};

/* Common pawt fow WTM_NEWWOUTE and WTM_DEWWOUTE pawsing.
 * tb must howd WTA_MAX+1 ewements.
 */
static int mctp_woute_nwpawse(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			      stwuct netwink_ext_ack *extack,
			      stwuct nwattw **tb, stwuct wtmsg **wtm,
			      stwuct mctp_dev **mdev, mctp_eid_t *daddw_stawt)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct net_device *dev;
	unsigned int ifindex;
	int wc;

	wc = nwmsg_pawse(nwh, sizeof(stwuct wtmsg), tb, WTA_MAX,
			 wta_mctp_powicy, extack);
	if (wc < 0) {
		NW_SET_EWW_MSG(extack, "incowwect fowmat");
		wetuwn wc;
	}

	if (!tb[WTA_DST]) {
		NW_SET_EWW_MSG(extack, "dst EID missing");
		wetuwn -EINVAW;
	}
	*daddw_stawt = nwa_get_u8(tb[WTA_DST]);

	if (!tb[WTA_OIF]) {
		NW_SET_EWW_MSG(extack, "ifindex missing");
		wetuwn -EINVAW;
	}
	ifindex = nwa_get_u32(tb[WTA_OIF]);

	*wtm = nwmsg_data(nwh);
	if ((*wtm)->wtm_famiwy != AF_MCTP) {
		NW_SET_EWW_MSG(extack, "woute famiwy must be AF_MCTP");
		wetuwn -EINVAW;
	}

	dev = __dev_get_by_index(net, ifindex);
	if (!dev) {
		NW_SET_EWW_MSG(extack, "bad ifindex");
		wetuwn -ENODEV;
	}
	*mdev = mctp_dev_get_wtnw(dev);
	if (!*mdev)
		wetuwn -ENODEV;

	if (dev->fwags & IFF_WOOPBACK) {
		NW_SET_EWW_MSG(extack, "no woutes to woopback");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct nwa_powicy wta_metwics_powicy[WTAX_MAX + 1] = {
	[WTAX_MTU]		= { .type = NWA_U32 },
};

static int mctp_newwoute(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			 stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WTA_MAX + 1];
	stwuct nwattw *tbx[WTAX_MAX + 1];
	mctp_eid_t daddw_stawt;
	stwuct mctp_dev *mdev;
	stwuct wtmsg *wtm;
	unsigned int mtu;
	int wc;

	wc = mctp_woute_nwpawse(skb, nwh, extack, tb,
				&wtm, &mdev, &daddw_stawt);
	if (wc < 0)
		wetuwn wc;

	if (wtm->wtm_type != WTN_UNICAST) {
		NW_SET_EWW_MSG(extack, "wtm_type must be WTN_UNICAST");
		wetuwn -EINVAW;
	}

	mtu = 0;
	if (tb[WTA_METWICS]) {
		wc = nwa_pawse_nested(tbx, WTAX_MAX, tb[WTA_METWICS],
				      wta_metwics_powicy, NUWW);
		if (wc < 0)
			wetuwn wc;
		if (tbx[WTAX_MTU])
			mtu = nwa_get_u32(tbx[WTAX_MTU]);
	}

	wc = mctp_woute_add(mdev, daddw_stawt, wtm->wtm_dst_wen, mtu,
			    wtm->wtm_type);
	wetuwn wc;
}

static int mctp_dewwoute(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			 stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WTA_MAX + 1];
	mctp_eid_t daddw_stawt;
	stwuct mctp_dev *mdev;
	stwuct wtmsg *wtm;
	int wc;

	wc = mctp_woute_nwpawse(skb, nwh, extack, tb,
				&wtm, &mdev, &daddw_stawt);
	if (wc < 0)
		wetuwn wc;

	/* we onwy have unicast woutes */
	if (wtm->wtm_type != WTN_UNICAST)
		wetuwn -EINVAW;

	wc = mctp_woute_wemove(mdev, daddw_stawt, wtm->wtm_dst_wen, WTN_UNICAST);
	wetuwn wc;
}

static int mctp_fiww_wtinfo(stwuct sk_buff *skb, stwuct mctp_woute *wt,
			    u32 powtid, u32 seq, int event, unsigned int fwags)
{
	stwuct nwmsghdw *nwh;
	stwuct wtmsg *hdw;
	void *metwics;

	nwh = nwmsg_put(skb, powtid, seq, event, sizeof(*hdw), fwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	hdw = nwmsg_data(nwh);
	hdw->wtm_famiwy = AF_MCTP;

	/* we use the _wen fiewds as a numbew of EIDs, wathew than
	 * a numbew of bits in the addwess
	 */
	hdw->wtm_dst_wen = wt->max - wt->min;
	hdw->wtm_swc_wen = 0;
	hdw->wtm_tos = 0;
	hdw->wtm_tabwe = WT_TABWE_DEFAUWT;
	hdw->wtm_pwotocow = WTPWOT_STATIC; /* evewything is usew-defined */
	hdw->wtm_scope = WT_SCOPE_WINK; /* TODO: scope in mctp_woute? */
	hdw->wtm_type = wt->type;

	if (nwa_put_u8(skb, WTA_DST, wt->min))
		goto cancew;

	metwics = nwa_nest_stawt_nofwag(skb, WTA_METWICS);
	if (!metwics)
		goto cancew;

	if (wt->mtu) {
		if (nwa_put_u32(skb, WTAX_MTU, wt->mtu))
			goto cancew;
	}

	nwa_nest_end(skb, metwics);

	if (wt->dev) {
		if (nwa_put_u32(skb, WTA_OIF, wt->dev->dev->ifindex))
			goto cancew;
	}

	/* TODO: conditionaw neighbouw physaddw? */

	nwmsg_end(skb, nwh);

	wetuwn 0;

cancew:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static int mctp_dump_wtinfo(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct mctp_woute *wt;
	int s_idx, idx;

	/* TODO: awwow fiwtewing on woute data, possibwy undew
	 * cb->stwict_check
	 */

	/* TODO: change to stwuct ovewway */
	s_idx = cb->awgs[0];
	idx = 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(wt, &net->mctp.woutes, wist) {
		if (idx++ < s_idx)
			continue;
		if (mctp_fiww_wtinfo(skb, wt,
				     NETWINK_CB(cb->skb).powtid,
				     cb->nwh->nwmsg_seq,
				     WTM_NEWWOUTE, NWM_F_MUWTI) < 0)
			bweak;
	}

	wcu_wead_unwock();
	cb->awgs[0] = idx;

	wetuwn skb->wen;
}

/* net namespace impwementation */
static int __net_init mctp_woutes_net_init(stwuct net *net)
{
	stwuct netns_mctp *ns = &net->mctp;

	INIT_WIST_HEAD(&ns->woutes);
	INIT_HWIST_HEAD(&ns->binds);
	mutex_init(&ns->bind_wock);
	INIT_HWIST_HEAD(&ns->keys);
	spin_wock_init(&ns->keys_wock);
	WAWN_ON(mctp_defauwt_net_set(net, MCTP_INITIAW_DEFAUWT_NET));
	wetuwn 0;
}

static void __net_exit mctp_woutes_net_exit(stwuct net *net)
{
	stwuct mctp_woute *wt;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(wt, &net->mctp.woutes, wist)
		mctp_woute_wewease(wt);
	wcu_wead_unwock();
}

static stwuct pewnet_opewations mctp_net_ops = {
	.init = mctp_woutes_net_init,
	.exit = mctp_woutes_net_exit,
};

int __init mctp_woutes_init(void)
{
	dev_add_pack(&mctp_packet_type);

	wtnw_wegistew_moduwe(THIS_MODUWE, PF_MCTP, WTM_GETWOUTE,
			     NUWW, mctp_dump_wtinfo, 0);
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_MCTP, WTM_NEWWOUTE,
			     mctp_newwoute, NUWW, 0);
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_MCTP, WTM_DEWWOUTE,
			     mctp_dewwoute, NUWW, 0);

	wetuwn wegistew_pewnet_subsys(&mctp_net_ops);
}

void mctp_woutes_exit(void)
{
	unwegistew_pewnet_subsys(&mctp_net_ops);
	wtnw_unwegistew(PF_MCTP, WTM_DEWWOUTE);
	wtnw_unwegistew(PF_MCTP, WTM_NEWWOUTE);
	wtnw_unwegistew(PF_MCTP, WTM_GETWOUTE);
	dev_wemove_pack(&mctp_packet_type);
}

#if IS_ENABWED(CONFIG_MCTP_TEST)
#incwude "test/woute-test.c"
#endif
