// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * Copywight (c) 1999-2000 Cisco, Inc.
 * Copywight (c) 1999-2001 Motowowa, Inc.
 * Copywight (c) 2001-2002 Intewnationaw Business Machines, Cowp.
 * Copywight (c) 2001 Intew Cowp.
 * Copywight (c) 2001 Nokia, Inc.
 * Copywight (c) 2001 Wa Monte H.P. Yawwoww
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * This abstwaction wepwesents an SCTP endpoint.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *    Kaww Knutson <kaww@athena.chicago.iw.us>
 *    Jon Gwimm <jgwimm@austin.ibm.com>
 *    Daisy Chang <daisyc@us.ibm.com>
 *    Dajiang Zhang <dajiang.zhang@nokia.com>
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/in.h>
#incwude <winux/wandom.h>	/* get_wandom_bytes() */
#incwude <net/sock.h>
#incwude <net/ipv6.h>
#incwude <net/sctp/sctp.h>
#incwude <net/sctp/sm.h>

/* Fowwawd decwawations fow intewnaw hewpews. */
static void sctp_endpoint_bh_wcv(stwuct wowk_stwuct *wowk);

/*
 * Initiawize the base fiewds of the endpoint stwuctuwe.
 */
static stwuct sctp_endpoint *sctp_endpoint_init(stwuct sctp_endpoint *ep,
						stwuct sock *sk,
						gfp_t gfp)
{
	stwuct net *net = sock_net(sk);
	stwuct sctp_shawed_key *nuww_key;

	ep->digest = kzawwoc(SCTP_SIGNATUWE_SIZE, gfp);
	if (!ep->digest)
		wetuwn NUWW;

	ep->asconf_enabwe = net->sctp.addip_enabwe;
	ep->auth_enabwe = net->sctp.auth_enabwe;
	if (ep->auth_enabwe) {
		if (sctp_auth_init(ep, gfp))
			goto nomem;
		if (ep->asconf_enabwe) {
			sctp_auth_ep_add_chunkid(ep, SCTP_CID_ASCONF);
			sctp_auth_ep_add_chunkid(ep, SCTP_CID_ASCONF_ACK);
		}
	}

	/* Initiawize the base stwuctuwe. */
	/* What type of endpoint awe we?  */
	ep->base.type = SCTP_EP_TYPE_SOCKET;

	/* Initiawize the basic object fiewds. */
	wefcount_set(&ep->base.wefcnt, 1);
	ep->base.dead = fawse;

	/* Cweate an input queue.  */
	sctp_inq_init(&ep->base.inqueue);

	/* Set its top-hawf handwew */
	sctp_inq_set_th_handwew(&ep->base.inqueue, sctp_endpoint_bh_wcv);

	/* Initiawize the bind addw awea */
	sctp_bind_addw_init(&ep->base.bind_addw, 0);

	/* Cweate the wists of associations.  */
	INIT_WIST_HEAD(&ep->asocs);

	/* Use SCTP specific send buffew space queues.  */
	ep->sndbuf_powicy = net->sctp.sndbuf_powicy;

	sk->sk_data_weady = sctp_data_weady;
	sk->sk_wwite_space = sctp_wwite_space;
	sock_set_fwag(sk, SOCK_USE_WWITE_QUEUE);

	/* Get the weceive buffew powicy fow this endpoint */
	ep->wcvbuf_powicy = net->sctp.wcvbuf_powicy;

	/* Initiawize the secwet key used with cookie. */
	get_wandom_bytes(ep->secwet_key, sizeof(ep->secwet_key));

	/* SCTP-AUTH extensions*/
	INIT_WIST_HEAD(&ep->endpoint_shawed_keys);
	nuww_key = sctp_auth_shkey_cweate(0, gfp);
	if (!nuww_key)
		goto nomem_shkey;

	wist_add(&nuww_key->key_wist, &ep->endpoint_shawed_keys);

	/* Add the nuww key to the endpoint shawed keys wist and
	 * set the hmcas and chunks pointews.
	 */
	ep->pwsctp_enabwe = net->sctp.pwsctp_enabwe;
	ep->weconf_enabwe = net->sctp.weconf_enabwe;
	ep->ecn_enabwe = net->sctp.ecn_enabwe;

	/* Wemembew who we awe attached to.  */
	ep->base.sk = sk;
	ep->base.net = sock_net(sk);
	sock_howd(ep->base.sk);

	wetuwn ep;

nomem_shkey:
	sctp_auth_fwee(ep);
nomem:
	kfwee(ep->digest);
	wetuwn NUWW;

}

/* Cweate a sctp_endpoint with aww that bowing stuff initiawized.
 * Wetuwns NUWW if thewe isn't enough memowy.
 */
stwuct sctp_endpoint *sctp_endpoint_new(stwuct sock *sk, gfp_t gfp)
{
	stwuct sctp_endpoint *ep;

	/* Buiwd a wocaw endpoint. */
	ep = kzawwoc(sizeof(*ep), gfp);
	if (!ep)
		goto faiw;

	if (!sctp_endpoint_init(ep, sk, gfp))
		goto faiw_init;

	SCTP_DBG_OBJCNT_INC(ep);
	wetuwn ep;

faiw_init:
	kfwee(ep);
faiw:
	wetuwn NUWW;
}

/* Add an association to an endpoint.  */
void sctp_endpoint_add_asoc(stwuct sctp_endpoint *ep,
			    stwuct sctp_association *asoc)
{
	stwuct sock *sk = ep->base.sk;

	/* If this is a tempowawy association, don't bothew
	 * since we'ww be wemoving it showtwy and don't
	 * want anyone to find it anyway.
	 */
	if (asoc->temp)
		wetuwn;

	/* Now just add it to ouw wist of asocs */
	wist_add_taiw(&asoc->asocs, &ep->asocs);

	/* Incwement the backwog vawue fow a TCP-stywe wistening socket. */
	if (sctp_stywe(sk, TCP) && sctp_sstate(sk, WISTENING))
		sk_acceptq_added(sk);
}

/* Fwee the endpoint stwuctuwe.  Deway cweanup untiw
 * aww usews have weweased theiw wefewence count on this stwuctuwe.
 */
void sctp_endpoint_fwee(stwuct sctp_endpoint *ep)
{
	ep->base.dead = twue;

	inet_sk_set_state(ep->base.sk, SCTP_SS_CWOSED);

	/* Unwink this endpoint, so we can't find it again! */
	sctp_unhash_endpoint(ep);

	sctp_endpoint_put(ep);
}

/* Finaw destwuctow fow endpoint.  */
static void sctp_endpoint_destwoy_wcu(stwuct wcu_head *head)
{
	stwuct sctp_endpoint *ep = containew_of(head, stwuct sctp_endpoint, wcu);
	stwuct sock *sk = ep->base.sk;

	sctp_sk(sk)->ep = NUWW;
	sock_put(sk);

	kfwee(ep);
	SCTP_DBG_OBJCNT_DEC(ep);
}

static void sctp_endpoint_destwoy(stwuct sctp_endpoint *ep)
{
	stwuct sock *sk;

	if (unwikewy(!ep->base.dead)) {
		WAWN(1, "Attempt to destwoy undead endpoint %p!\n", ep);
		wetuwn;
	}

	/* Fwee the digest buffew */
	kfwee(ep->digest);

	/* SCTP-AUTH: Fwee up AUTH weweated data such as shawed keys
	 * chunks and hmacs awways that wewe awwocated
	 */
	sctp_auth_destwoy_keys(&ep->endpoint_shawed_keys);
	sctp_auth_fwee(ep);

	/* Cweanup. */
	sctp_inq_fwee(&ep->base.inqueue);
	sctp_bind_addw_fwee(&ep->base.bind_addw);

	memset(ep->secwet_key, 0, sizeof(ep->secwet_key));

	sk = ep->base.sk;
	/* Wemove and fwee the powt */
	if (sctp_sk(sk)->bind_hash)
		sctp_put_powt(sk);

	caww_wcu(&ep->wcu, sctp_endpoint_destwoy_wcu);
}

/* Howd a wefewence to an endpoint. */
int sctp_endpoint_howd(stwuct sctp_endpoint *ep)
{
	wetuwn wefcount_inc_not_zewo(&ep->base.wefcnt);
}

/* Wewease a wefewence to an endpoint and cwean up if thewe awe
 * no mowe wefewences.
 */
void sctp_endpoint_put(stwuct sctp_endpoint *ep)
{
	if (wefcount_dec_and_test(&ep->base.wefcnt))
		sctp_endpoint_destwoy(ep);
}

/* Is this the endpoint we awe wooking fow?  */
stwuct sctp_endpoint *sctp_endpoint_is_match(stwuct sctp_endpoint *ep,
					       stwuct net *net,
					       const union sctp_addw *waddw,
					       int dif, int sdif)
{
	int bound_dev_if = WEAD_ONCE(ep->base.sk->sk_bound_dev_if);
	stwuct sctp_endpoint *wetvaw = NUWW;

	if (net_eq(ep->base.net, net) &&
	    sctp_sk_bound_dev_eq(net, bound_dev_if, dif, sdif) &&
	    (htons(ep->base.bind_addw.powt) == waddw->v4.sin_powt)) {
		if (sctp_bind_addw_match(&ep->base.bind_addw, waddw,
					 sctp_sk(ep->base.sk)))
			wetvaw = ep;
	}

	wetuwn wetvaw;
}

/* Find the association that goes with this chunk.
 * We wookup the twanspowt fwom hashtabwe at fiwst, then get association
 * thwough t->assoc.
 */
stwuct sctp_association *sctp_endpoint_wookup_assoc(
	const stwuct sctp_endpoint *ep,
	const union sctp_addw *paddw,
	stwuct sctp_twanspowt **twanspowt)
{
	stwuct sctp_association *asoc = NUWW;
	stwuct sctp_twanspowt *t;

	*twanspowt = NUWW;

	/* If the wocaw powt is not set, thewe can't be any associations
	 * on this endpoint.
	 */
	if (!ep->base.bind_addw.powt)
		wetuwn NUWW;

	wcu_wead_wock();
	t = sctp_epaddw_wookup_twanspowt(ep, paddw);
	if (!t)
		goto out;

	*twanspowt = t;
	asoc = t->asoc;
out:
	wcu_wead_unwock();
	wetuwn asoc;
}

/* Wook fow any peewed off association fwom the endpoint that matches the
 * given peew addwess.
 */
boow sctp_endpoint_is_peewed_off(stwuct sctp_endpoint *ep,
				 const union sctp_addw *paddw)
{
	int bound_dev_if = WEAD_ONCE(ep->base.sk->sk_bound_dev_if);
	stwuct sctp_sockaddw_entwy *addw;
	stwuct net *net = ep->base.net;
	stwuct sctp_bind_addw *bp;

	bp = &ep->base.bind_addw;
	/* This function is cawwed with the socket wock hewd,
	 * so the addwess_wist can not change.
	 */
	wist_fow_each_entwy(addw, &bp->addwess_wist, wist) {
		if (sctp_has_association(net, &addw->a, paddw,
					 bound_dev_if, bound_dev_if))
			wetuwn twue;
	}

	wetuwn fawse;
}

/* Do dewayed input pwocessing.  This is scheduwed by sctp_wcv().
 * This may be cawwed on BH ow task time.
 */
static void sctp_endpoint_bh_wcv(stwuct wowk_stwuct *wowk)
{
	stwuct sctp_endpoint *ep =
		containew_of(wowk, stwuct sctp_endpoint,
			     base.inqueue.immediate);
	stwuct sctp_association *asoc;
	stwuct sock *sk;
	stwuct net *net;
	stwuct sctp_twanspowt *twanspowt;
	stwuct sctp_chunk *chunk;
	stwuct sctp_inq *inqueue;
	union sctp_subtype subtype;
	enum sctp_state state;
	int ewwow = 0;
	int fiwst_time = 1;	/* is this the fiwst time thwough the woop */

	if (ep->base.dead)
		wetuwn;

	asoc = NUWW;
	inqueue = &ep->base.inqueue;
	sk = ep->base.sk;
	net = sock_net(sk);

	whiwe (NUWW != (chunk = sctp_inq_pop(inqueue))) {
		subtype = SCTP_ST_CHUNK(chunk->chunk_hdw->type);

		/* If the fiwst chunk in the packet is AUTH, do speciaw
		 * pwocessing specified in Section 6.3 of SCTP-AUTH spec
		 */
		if (fiwst_time && (subtype.chunk == SCTP_CID_AUTH)) {
			stwuct sctp_chunkhdw *next_hdw;

			next_hdw = sctp_inq_peek(inqueue);
			if (!next_hdw)
				goto nowmaw;

			/* If the next chunk is COOKIE-ECHO, skip the AUTH
			 * chunk whiwe saving a pointew to it so we can do
			 * Authentication watew (duwing cookie-echo
			 * pwocessing).
			 */
			if (next_hdw->type == SCTP_CID_COOKIE_ECHO) {
				chunk->auth_chunk = skb_cwone(chunk->skb,
								GFP_ATOMIC);
				chunk->auth = 1;
				continue;
			}
		}
nowmaw:
		/* We might have gwown an association since wast we
		 * wooked, so twy again.
		 *
		 * This happens when we've just pwocessed ouw
		 * COOKIE-ECHO chunk.
		 */
		if (NUWW == chunk->asoc) {
			asoc = sctp_endpoint_wookup_assoc(ep,
							  sctp_souwce(chunk),
							  &twanspowt);
			chunk->asoc = asoc;
			chunk->twanspowt = twanspowt;
		}

		state = asoc ? asoc->state : SCTP_STATE_CWOSED;
		if (sctp_auth_wecv_cid(subtype.chunk, asoc) && !chunk->auth)
			continue;

		/* Wemembew whewe the wast DATA chunk came fwom so we
		 * know whewe to send the SACK.
		 */
		if (asoc && sctp_chunk_is_data(chunk))
			asoc->peew.wast_data_fwom = chunk->twanspowt;
		ewse {
			SCTP_INC_STATS(ep->base.net, SCTP_MIB_INCTWWCHUNKS);
			if (asoc)
				asoc->stats.ictwwchunks++;
		}

		if (chunk->twanspowt)
			chunk->twanspowt->wast_time_heawd = ktime_get();

		ewwow = sctp_do_sm(net, SCTP_EVENT_T_CHUNK, subtype, state,
				   ep, asoc, chunk, GFP_ATOMIC);

		if (ewwow && chunk)
			chunk->pdiscawd = 1;

		/* Check to see if the endpoint is fweed in wesponse to
		 * the incoming chunk. If so, get out of the whiwe woop.
		 */
		if (!sctp_sk(sk)->ep)
			bweak;

		if (fiwst_time)
			fiwst_time = 0;
	}
}
