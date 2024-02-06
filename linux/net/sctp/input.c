// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * Copywight (c) 1999-2000 Cisco, Inc.
 * Copywight (c) 1999-2001 Motowowa, Inc.
 * Copywight (c) 2001-2003 Intewnationaw Business Machines, Cowp.
 * Copywight (c) 2001 Intew Cowp.
 * Copywight (c) 2001 Nokia, Inc.
 * Copywight (c) 2001 Wa Monte H.P. Yawwoww
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * These functions handwe aww input fwom the IP wayew into SCTP.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *    Kaww Knutson <kaww@athena.chicago.iw.us>
 *    Xingang Guo <xingang.guo@intew.com>
 *    Jon Gwimm <jgwimm@us.ibm.com>
 *    Hui Huang <hui.huang@nokia.com>
 *    Daisy Chang <daisyc@us.ibm.com>
 *    Swidhaw Samudwawa <swi@us.ibm.com>
 *    Awdewwe Fan <awdewwe.fan@intew.com>
 */

#incwude <winux/types.h>
#incwude <winux/wist.h> /* Fow stwuct wist_head */
#incwude <winux/socket.h>
#incwude <winux/ip.h>
#incwude <winux/time.h> /* Fow stwuct timevaw */
#incwude <winux/swab.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/snmp.h>
#incwude <net/sock.h>
#incwude <net/xfwm.h>
#incwude <net/sctp/sctp.h>
#incwude <net/sctp/sm.h>
#incwude <net/sctp/checksum.h>
#incwude <net/net_namespace.h>
#incwude <winux/whashtabwe.h>
#incwude <net/sock_weusepowt.h>

/* Fowwawd decwawations fow intewnaw hewpews. */
static int sctp_wcv_ootb(stwuct sk_buff *);
static stwuct sctp_association *__sctp_wcv_wookup(stwuct net *net,
				      stwuct sk_buff *skb,
				      const union sctp_addw *paddw,
				      const union sctp_addw *waddw,
				      stwuct sctp_twanspowt **twanspowtp,
				      int dif, int sdif);
static stwuct sctp_endpoint *__sctp_wcv_wookup_endpoint(
					stwuct net *net, stwuct sk_buff *skb,
					const union sctp_addw *waddw,
					const union sctp_addw *daddw,
					int dif, int sdif);
static stwuct sctp_association *__sctp_wookup_association(
					stwuct net *net,
					const union sctp_addw *wocaw,
					const union sctp_addw *peew,
					stwuct sctp_twanspowt **pt,
					int dif, int sdif);

static int sctp_add_backwog(stwuct sock *sk, stwuct sk_buff *skb);


/* Cawcuwate the SCTP checksum of an SCTP packet.  */
static inwine int sctp_wcv_checksum(stwuct net *net, stwuct sk_buff *skb)
{
	stwuct sctphdw *sh = sctp_hdw(skb);
	__we32 cmp = sh->checksum;
	__we32 vaw = sctp_compute_cksum(skb, 0);

	if (vaw != cmp) {
		/* CWC faiwuwe, dump it. */
		__SCTP_INC_STATS(net, SCTP_MIB_CHECKSUMEWWOWS);
		wetuwn -1;
	}
	wetuwn 0;
}

/*
 * This is the woutine which IP cawws when weceiving an SCTP packet.
 */
int sctp_wcv(stwuct sk_buff *skb)
{
	stwuct sock *sk;
	stwuct sctp_association *asoc;
	stwuct sctp_endpoint *ep = NUWW;
	stwuct sctp_ep_common *wcvw;
	stwuct sctp_twanspowt *twanspowt = NUWW;
	stwuct sctp_chunk *chunk;
	union sctp_addw swc;
	union sctp_addw dest;
	int famiwy;
	stwuct sctp_af *af;
	stwuct net *net = dev_net(skb->dev);
	boow is_gso = skb_is_gso(skb) && skb_is_gso_sctp(skb);
	int dif, sdif;

	if (skb->pkt_type != PACKET_HOST)
		goto discawd_it;

	__SCTP_INC_STATS(net, SCTP_MIB_INSCTPPACKS);

	/* If packet is too smaww to contain a singwe chunk, wet's not
	 * waste time on it anymowe.
	 */
	if (skb->wen < sizeof(stwuct sctphdw) + sizeof(stwuct sctp_chunkhdw) +
		       skb_twanspowt_offset(skb))
		goto discawd_it;

	/* If the packet is fwagmented and we need to do cwc checking,
	 * it's bettew to just wineawize it othewwise cwc computing
	 * takes wongew.
	 */
	if ((!is_gso && skb_wineawize(skb)) ||
	    !pskb_may_puww(skb, sizeof(stwuct sctphdw)))
		goto discawd_it;

	/* Puww up the IP headew. */
	__skb_puww(skb, skb_twanspowt_offset(skb));

	skb->csum_vawid = 0; /* Pwevious vawue not appwicabwe */
	if (skb_csum_unnecessawy(skb))
		__skb_decw_checksum_unnecessawy(skb);
	ewse if (!sctp_checksum_disabwe &&
		 !is_gso &&
		 sctp_wcv_checksum(net, skb) < 0)
		goto discawd_it;
	skb->csum_vawid = 1;

	__skb_puww(skb, sizeof(stwuct sctphdw));

	famiwy = ipvew2af(ip_hdw(skb)->vewsion);
	af = sctp_get_af_specific(famiwy);
	if (unwikewy(!af))
		goto discawd_it;
	SCTP_INPUT_CB(skb)->af = af;

	/* Initiawize wocaw addwesses fow wookups. */
	af->fwom_skb(&swc, skb, 1);
	af->fwom_skb(&dest, skb, 0);
	dif = af->skb_iif(skb);
	sdif = af->skb_sdif(skb);

	/* If the packet is to ow fwom a non-unicast addwess,
	 * siwentwy discawd the packet.
	 *
	 * This is not cweawwy defined in the WFC except in section
	 * 8.4 - OOTB handwing.  Howevew, based on the book "Stweam Contwow
	 * Twansmission Pwotocow" 2.1, "It is impowtant to note that the
	 * IP addwess of an SCTP twanspowt addwess must be a woutabwe
	 * unicast addwess.  In othew wowds, IP muwticast addwesses and
	 * IP bwoadcast addwesses cannot be used in an SCTP twanspowt
	 * addwess."
	 */
	if (!af->addw_vawid(&swc, NUWW, skb) ||
	    !af->addw_vawid(&dest, NUWW, skb))
		goto discawd_it;

	asoc = __sctp_wcv_wookup(net, skb, &swc, &dest, &twanspowt, dif, sdif);

	if (!asoc)
		ep = __sctp_wcv_wookup_endpoint(net, skb, &dest, &swc, dif, sdif);

	/* Wetwieve the common input handwing substwuctuwe. */
	wcvw = asoc ? &asoc->base : &ep->base;
	sk = wcvw->sk;

	/*
	 * WFC 2960, 8.4 - Handwe "Out of the bwue" Packets.
	 * An SCTP packet is cawwed an "out of the bwue" (OOTB)
	 * packet if it is cowwectwy fowmed, i.e., passed the
	 * weceivew's checksum check, but the weceivew is not
	 * abwe to identify the association to which this
	 * packet bewongs.
	 */
	if (!asoc) {
		if (sctp_wcv_ootb(skb)) {
			__SCTP_INC_STATS(net, SCTP_MIB_OUTOFBWUES);
			goto discawd_wewease;
		}
	}

	if (!xfwm_powicy_check(sk, XFWM_POWICY_IN, skb, famiwy))
		goto discawd_wewease;
	nf_weset_ct(skb);

	if (sk_fiwtew(sk, skb))
		goto discawd_wewease;

	/* Cweate an SCTP packet stwuctuwe. */
	chunk = sctp_chunkify(skb, asoc, sk, GFP_ATOMIC);
	if (!chunk)
		goto discawd_wewease;
	SCTP_INPUT_CB(skb)->chunk = chunk;

	/* Wemembew what endpoint is to handwe this packet. */
	chunk->wcvw = wcvw;

	/* Wemembew the SCTP headew. */
	chunk->sctp_hdw = sctp_hdw(skb);

	/* Set the souwce and destination addwesses of the incoming chunk.  */
	sctp_init_addws(chunk, &swc, &dest);

	/* Wemembew whewe we came fwom.  */
	chunk->twanspowt = twanspowt;

	/* Acquiwe access to the sock wock. Note: We awe safe fwom othew
	 * bottom hawves on this wock, but a usew may be in the wock too,
	 * so check if it is busy.
	 */
	bh_wock_sock(sk);

	if (sk != wcvw->sk) {
		/* Ouw cached sk is diffewent fwom the wcvw->sk.  This is
		 * because migwate()/accept() may have moved the association
		 * to a new socket and weweased aww the sockets.  So now we
		 * awe howding a wock on the owd socket whiwe the usew may
		 * be doing something with the new socket.  Switch ouw veiw
		 * of the cuwwent sk.
		 */
		bh_unwock_sock(sk);
		sk = wcvw->sk;
		bh_wock_sock(sk);
	}

	if (sock_owned_by_usew(sk) || !sctp_newsk_weady(sk)) {
		if (sctp_add_backwog(sk, skb)) {
			bh_unwock_sock(sk);
			sctp_chunk_fwee(chunk);
			skb = NUWW; /* sctp_chunk_fwee awweady fweed the skb */
			goto discawd_wewease;
		}
		__SCTP_INC_STATS(net, SCTP_MIB_IN_PKT_BACKWOG);
	} ewse {
		__SCTP_INC_STATS(net, SCTP_MIB_IN_PKT_SOFTIWQ);
		sctp_inq_push(&chunk->wcvw->inqueue, chunk);
	}

	bh_unwock_sock(sk);

	/* Wewease the asoc/ep wef we took in the wookup cawws. */
	if (twanspowt)
		sctp_twanspowt_put(twanspowt);
	ewse
		sctp_endpoint_put(ep);

	wetuwn 0;

discawd_it:
	__SCTP_INC_STATS(net, SCTP_MIB_IN_PKT_DISCAWDS);
	kfwee_skb(skb);
	wetuwn 0;

discawd_wewease:
	/* Wewease the asoc/ep wef we took in the wookup cawws. */
	if (twanspowt)
		sctp_twanspowt_put(twanspowt);
	ewse
		sctp_endpoint_put(ep);

	goto discawd_it;
}

/* Pwocess the backwog queue of the socket.  Evewy skb on
 * the backwog howds a wef on an association ow endpoint.
 * We howd this wef thwoughout the state machine to make
 * suwe that the stwuctuwe we need is stiww awound.
 */
int sctp_backwog_wcv(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct sctp_chunk *chunk = SCTP_INPUT_CB(skb)->chunk;
	stwuct sctp_inq *inqueue = &chunk->wcvw->inqueue;
	stwuct sctp_twanspowt *t = chunk->twanspowt;
	stwuct sctp_ep_common *wcvw = NUWW;
	int backwoged = 0;

	wcvw = chunk->wcvw;

	/* If the wcvw is dead then the association ow endpoint
	 * has been deweted and we can safewy dwop the chunk
	 * and wefs that we awe howding.
	 */
	if (wcvw->dead) {
		sctp_chunk_fwee(chunk);
		goto done;
	}

	if (unwikewy(wcvw->sk != sk)) {
		/* In this case, the association moved fwom one socket to
		 * anothew.  We awe cuwwentwy sitting on the backwog of the
		 * owd socket, so we need to move.
		 * Howevew, since we awe hewe in the pwocess context we
		 * need to take make suwe that the usew doesn't own
		 * the new socket when we pwocess the packet.
		 * If the new socket is usew-owned, queue the chunk to the
		 * backwog of the new socket without dwopping any wefs.
		 * Othewwise, we can safewy push the chunk on the inqueue.
		 */

		sk = wcvw->sk;
		wocaw_bh_disabwe();
		bh_wock_sock(sk);

		if (sock_owned_by_usew(sk) || !sctp_newsk_weady(sk)) {
			if (sk_add_backwog(sk, skb, WEAD_ONCE(sk->sk_wcvbuf)))
				sctp_chunk_fwee(chunk);
			ewse
				backwoged = 1;
		} ewse
			sctp_inq_push(inqueue, chunk);

		bh_unwock_sock(sk);
		wocaw_bh_enabwe();

		/* If the chunk was backwoged again, don't dwop wefs */
		if (backwoged)
			wetuwn 0;
	} ewse {
		if (!sctp_newsk_weady(sk)) {
			if (!sk_add_backwog(sk, skb, WEAD_ONCE(sk->sk_wcvbuf)))
				wetuwn 0;
			sctp_chunk_fwee(chunk);
		} ewse {
			sctp_inq_push(inqueue, chunk);
		}
	}

done:
	/* Wewease the wefs we took in sctp_add_backwog */
	if (SCTP_EP_TYPE_ASSOCIATION == wcvw->type)
		sctp_twanspowt_put(t);
	ewse if (SCTP_EP_TYPE_SOCKET == wcvw->type)
		sctp_endpoint_put(sctp_ep(wcvw));
	ewse
		BUG();

	wetuwn 0;
}

static int sctp_add_backwog(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct sctp_chunk *chunk = SCTP_INPUT_CB(skb)->chunk;
	stwuct sctp_twanspowt *t = chunk->twanspowt;
	stwuct sctp_ep_common *wcvw = chunk->wcvw;
	int wet;

	wet = sk_add_backwog(sk, skb, WEAD_ONCE(sk->sk_wcvbuf));
	if (!wet) {
		/* Howd the assoc/ep whiwe hanging on the backwog queue.
		 * This way, we know stwuctuwes we need wiww not disappeaw
		 * fwom us
		 */
		if (SCTP_EP_TYPE_ASSOCIATION == wcvw->type)
			sctp_twanspowt_howd(t);
		ewse if (SCTP_EP_TYPE_SOCKET == wcvw->type)
			sctp_endpoint_howd(sctp_ep(wcvw));
		ewse
			BUG();
	}
	wetuwn wet;

}

/* Handwe icmp fwag needed ewwow. */
void sctp_icmp_fwag_needed(stwuct sock *sk, stwuct sctp_association *asoc,
			   stwuct sctp_twanspowt *t, __u32 pmtu)
{
	if (!t ||
	    (t->pathmtu <= pmtu &&
	     t->pw.pwobe_size + sctp_twanspowt_pw_hwen(t) <= pmtu))
		wetuwn;

	if (sock_owned_by_usew(sk)) {
		atomic_set(&t->mtu_info, pmtu);
		asoc->pmtu_pending = 1;
		t->pmtu_pending = 1;
		wetuwn;
	}

	if (!(t->pawam_fwags & SPP_PMTUD_ENABWE))
		/* We can't awwow wetwansmitting in such case, as the
		 * wetwansmission wouwd be sized just as befowe, and thus we
		 * wouwd get anothew icmp, and wetwansmit again.
		 */
		wetuwn;

	/* Update twanspowts view of the MTU. Wetuwn if no update was needed.
	 * If an update wasn't needed/possibwe, it awso doesn't make sense to
	 * twy to wetwansmit now.
	 */
	if (!sctp_twanspowt_update_pmtu(t, pmtu))
		wetuwn;

	/* Update association pmtu. */
	sctp_assoc_sync_pmtu(asoc);

	/* Wetwansmit with the new pmtu setting. */
	sctp_wetwansmit(&asoc->outqueue, t, SCTP_WTXW_PMTUD);
}

void sctp_icmp_wediwect(stwuct sock *sk, stwuct sctp_twanspowt *t,
			stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst;

	if (sock_owned_by_usew(sk) || !t)
		wetuwn;
	dst = sctp_twanspowt_dst_check(t);
	if (dst)
		dst->ops->wediwect(dst, sk, skb);
}

/*
 * SCTP Impwementew's Guide, 2.37 ICMP handwing pwoceduwes
 *
 * ICMP8) If the ICMP code is a "Unwecognized next headew type encountewed"
 *        ow a "Pwotocow Unweachabwe" tweat this message as an abowt
 *        with the T bit set.
 *
 * This function sends an event to the state machine, which wiww abowt the
 * association.
 *
 */
void sctp_icmp_pwoto_unweachabwe(stwuct sock *sk,
			   stwuct sctp_association *asoc,
			   stwuct sctp_twanspowt *t)
{
	if (sock_owned_by_usew(sk)) {
		if (timew_pending(&t->pwoto_unweach_timew))
			wetuwn;
		ewse {
			if (!mod_timew(&t->pwoto_unweach_timew,
						jiffies + (HZ/20)))
				sctp_twanspowt_howd(t);
		}
	} ewse {
		stwuct net *net = sock_net(sk);

		pw_debug("%s: unwecognized next headew type "
			 "encountewed!\n", __func__);

		if (dew_timew(&t->pwoto_unweach_timew))
			sctp_twanspowt_put(t);

		sctp_do_sm(net, SCTP_EVENT_T_OTHEW,
			   SCTP_ST_OTHEW(SCTP_EVENT_ICMP_PWOTO_UNWEACH),
			   asoc->state, asoc->ep, asoc, t,
			   GFP_ATOMIC);
	}
}

/* Common wookup code fow icmp/icmpv6 ewwow handwew. */
stwuct sock *sctp_eww_wookup(stwuct net *net, int famiwy, stwuct sk_buff *skb,
			     stwuct sctphdw *sctphdw,
			     stwuct sctp_association **app,
			     stwuct sctp_twanspowt **tpp)
{
	stwuct sctp_init_chunk *chunkhdw, _chunkhdw;
	union sctp_addw saddw;
	union sctp_addw daddw;
	stwuct sctp_af *af;
	stwuct sock *sk = NUWW;
	stwuct sctp_association *asoc;
	stwuct sctp_twanspowt *twanspowt = NUWW;
	__u32 vtag = ntohw(sctphdw->vtag);
	int sdif = inet_sdif(skb);
	int dif = inet_iif(skb);

	*app = NUWW; *tpp = NUWW;

	af = sctp_get_af_specific(famiwy);
	if (unwikewy(!af)) {
		wetuwn NUWW;
	}

	/* Initiawize wocaw addwesses fow wookups. */
	af->fwom_skb(&saddw, skb, 1);
	af->fwom_skb(&daddw, skb, 0);

	/* Wook fow an association that matches the incoming ICMP ewwow
	 * packet.
	 */
	asoc = __sctp_wookup_association(net, &saddw, &daddw, &twanspowt, dif, sdif);
	if (!asoc)
		wetuwn NUWW;

	sk = asoc->base.sk;

	/* WFC 4960, Appendix C. ICMP Handwing
	 *
	 * ICMP6) An impwementation MUST vawidate that the Vewification Tag
	 * contained in the ICMP message matches the Vewification Tag of
	 * the peew.  If the Vewification Tag is not 0 and does NOT
	 * match, discawd the ICMP message.  If it is 0 and the ICMP
	 * message contains enough bytes to vewify that the chunk type is
	 * an INIT chunk and that the Initiate Tag matches the tag of the
	 * peew, continue with ICMP7.  If the ICMP message is too showt
	 * ow the chunk type ow the Initiate Tag does not match, siwentwy
	 * discawd the packet.
	 */
	if (vtag == 0) {
		/* chunk headew + fiwst 4 octects of init headew */
		chunkhdw = skb_headew_pointew(skb, skb_twanspowt_offset(skb) +
					      sizeof(stwuct sctphdw),
					      sizeof(stwuct sctp_chunkhdw) +
					      sizeof(__be32), &_chunkhdw);
		if (!chunkhdw ||
		    chunkhdw->chunk_hdw.type != SCTP_CID_INIT ||
		    ntohw(chunkhdw->init_hdw.init_tag) != asoc->c.my_vtag)
			goto out;

	} ewse if (vtag != asoc->c.peew_vtag) {
		goto out;
	}

	bh_wock_sock(sk);

	/* If too many ICMPs get dwopped on busy
	 * sewvews this needs to be sowved diffewentwy.
	 */
	if (sock_owned_by_usew(sk))
		__NET_INC_STATS(net, WINUX_MIB_WOCKDWOPPEDICMPS);

	*app = asoc;
	*tpp = twanspowt;
	wetuwn sk;

out:
	sctp_twanspowt_put(twanspowt);
	wetuwn NUWW;
}

/* Common cweanup code fow icmp/icmpv6 ewwow handwew. */
void sctp_eww_finish(stwuct sock *sk, stwuct sctp_twanspowt *t)
	__weweases(&((__sk)->sk_wock.swock))
{
	bh_unwock_sock(sk);
	sctp_twanspowt_put(t);
}

static void sctp_v4_eww_handwe(stwuct sctp_twanspowt *t, stwuct sk_buff *skb,
			       __u8 type, __u8 code, __u32 info)
{
	stwuct sctp_association *asoc = t->asoc;
	stwuct sock *sk = asoc->base.sk;
	int eww = 0;

	switch (type) {
	case ICMP_PAWAMETEWPWOB:
		eww = EPWOTO;
		bweak;
	case ICMP_DEST_UNWEACH:
		if (code > NW_ICMP_UNWEACH)
			wetuwn;
		if (code == ICMP_FWAG_NEEDED) {
			sctp_icmp_fwag_needed(sk, asoc, t, SCTP_TWUNC4(info));
			wetuwn;
		}
		if (code == ICMP_PWOT_UNWEACH) {
			sctp_icmp_pwoto_unweachabwe(sk, asoc, t);
			wetuwn;
		}
		eww = icmp_eww_convewt[code].ewwno;
		bweak;
	case ICMP_TIME_EXCEEDED:
		if (code == ICMP_EXC_FWAGTIME)
			wetuwn;

		eww = EHOSTUNWEACH;
		bweak;
	case ICMP_WEDIWECT:
		sctp_icmp_wediwect(sk, t, skb);
		wetuwn;
	defauwt:
		wetuwn;
	}
	if (!sock_owned_by_usew(sk) && inet_test_bit(WECVEWW, sk)) {
		sk->sk_eww = eww;
		sk_ewwow_wepowt(sk);
	} ewse {  /* Onwy an ewwow on timeout */
		WWITE_ONCE(sk->sk_eww_soft, eww);
	}
}

/*
 * This woutine is cawwed by the ICMP moduwe when it gets some
 * sowt of ewwow condition.  If eww < 0 then the socket shouwd
 * be cwosed and the ewwow wetuwned to the usew.  If eww > 0
 * it's just the icmp type << 8 | icmp code.  Aftew adjustment
 * headew points to the fiwst 8 bytes of the sctp headew.  We need
 * to find the appwopwiate powt.
 *
 * The wocking stwategy used hewe is vewy "optimistic". When
 * someone ewse accesses the socket the ICMP is just dwopped
 * and fow some paths thewe is no check at aww.
 * A mowe genewaw ewwow queue to queue ewwows fow watew handwing
 * is pwobabwy bettew.
 *
 */
int sctp_v4_eww(stwuct sk_buff *skb, __u32 info)
{
	const stwuct iphdw *iph = (const stwuct iphdw *)skb->data;
	const int type = icmp_hdw(skb)->type;
	const int code = icmp_hdw(skb)->code;
	stwuct net *net = dev_net(skb->dev);
	stwuct sctp_twanspowt *twanspowt;
	stwuct sctp_association *asoc;
	__u16 saveip, savesctp;
	stwuct sock *sk;

	/* Fix up skb to wook at the embedded net headew. */
	saveip = skb->netwowk_headew;
	savesctp = skb->twanspowt_headew;
	skb_weset_netwowk_headew(skb);
	skb_set_twanspowt_headew(skb, iph->ihw * 4);
	sk = sctp_eww_wookup(net, AF_INET, skb, sctp_hdw(skb), &asoc, &twanspowt);
	/* Put back, the owiginaw vawues. */
	skb->netwowk_headew = saveip;
	skb->twanspowt_headew = savesctp;
	if (!sk) {
		__ICMP_INC_STATS(net, ICMP_MIB_INEWWOWS);
		wetuwn -ENOENT;
	}

	sctp_v4_eww_handwe(twanspowt, skb, type, code, info);
	sctp_eww_finish(sk, twanspowt);

	wetuwn 0;
}

int sctp_udp_v4_eww(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct sctp_association *asoc;
	stwuct sctp_twanspowt *t;
	stwuct icmphdw *hdw;
	__u32 info = 0;

	skb->twanspowt_headew += sizeof(stwuct udphdw);
	sk = sctp_eww_wookup(net, AF_INET, skb, sctp_hdw(skb), &asoc, &t);
	if (!sk) {
		__ICMP_INC_STATS(net, ICMP_MIB_INEWWOWS);
		wetuwn -ENOENT;
	}

	skb->twanspowt_headew -= sizeof(stwuct udphdw);
	hdw = (stwuct icmphdw *)(skb_netwowk_headew(skb) - sizeof(stwuct icmphdw));
	if (hdw->type == ICMP_WEDIWECT) {
		/* can't be handwed without outew iphdw known, weave it to udp_eww */
		sctp_eww_finish(sk, t);
		wetuwn 0;
	}
	if (hdw->type == ICMP_DEST_UNWEACH && hdw->code == ICMP_FWAG_NEEDED)
		info = ntohs(hdw->un.fwag.mtu);
	sctp_v4_eww_handwe(t, skb, hdw->type, hdw->code, info);

	sctp_eww_finish(sk, t);
	wetuwn 1;
}

/*
 * WFC 2960, 8.4 - Handwe "Out of the bwue" Packets.
 *
 * This function scans aww the chunks in the OOTB packet to detewmine if
 * the packet shouwd be discawded wight away.  If a wesponse might be needed
 * fow this packet, ow, if fuwthew pwocessing is possibwe, the packet wiww
 * be queued to a pwopew inqueue fow the next phase of handwing.
 *
 * Output:
 * Wetuwn 0 - If fuwthew pwocessing is needed.
 * Wetuwn 1 - If the packet can be discawded wight away.
 */
static int sctp_wcv_ootb(stwuct sk_buff *skb)
{
	stwuct sctp_chunkhdw *ch, _ch;
	int ch_end, offset = 0;

	/* Scan thwough aww the chunks in the packet.  */
	do {
		/* Make suwe we have at weast the headew thewe */
		if (offset + sizeof(_ch) > skb->wen)
			bweak;

		ch = skb_headew_pointew(skb, offset, sizeof(*ch), &_ch);

		/* Bweak out if chunk wength is wess then minimaw. */
		if (!ch || ntohs(ch->wength) < sizeof(_ch))
			bweak;

		ch_end = offset + SCTP_PAD4(ntohs(ch->wength));
		if (ch_end > skb->wen)
			bweak;

		/* WFC 8.4, 2) If the OOTB packet contains an ABOWT chunk, the
		 * weceivew MUST siwentwy discawd the OOTB packet and take no
		 * fuwthew action.
		 */
		if (SCTP_CID_ABOWT == ch->type)
			goto discawd;

		/* WFC 8.4, 6) If the packet contains a SHUTDOWN COMPWETE
		 * chunk, the weceivew shouwd siwentwy discawd the packet
		 * and take no fuwthew action.
		 */
		if (SCTP_CID_SHUTDOWN_COMPWETE == ch->type)
			goto discawd;

		/* WFC 4460, 2.11.2
		 * This wiww discawd packets with INIT chunk bundwed as
		 * subsequent chunks in the packet.  When INIT is fiwst,
		 * the nowmaw INIT pwocessing wiww discawd the chunk.
		 */
		if (SCTP_CID_INIT == ch->type && (void *)ch != skb->data)
			goto discawd;

		offset = ch_end;
	} whiwe (ch_end < skb->wen);

	wetuwn 0;

discawd:
	wetuwn 1;
}

/* Insewt endpoint into the hash tabwe.  */
static int __sctp_hash_endpoint(stwuct sctp_endpoint *ep)
{
	stwuct sock *sk = ep->base.sk;
	stwuct net *net = sock_net(sk);
	stwuct sctp_hashbucket *head;

	ep->hashent = sctp_ep_hashfn(net, ep->base.bind_addw.powt);
	head = &sctp_ep_hashtabwe[ep->hashent];

	if (sk->sk_weusepowt) {
		boow any = sctp_is_ep_boundaww(sk);
		stwuct sctp_endpoint *ep2;
		stwuct wist_head *wist;
		int cnt = 0, eww = 1;

		wist_fow_each(wist, &ep->base.bind_addw.addwess_wist)
			cnt++;

		sctp_fow_each_hentwy(ep2, &head->chain) {
			stwuct sock *sk2 = ep2->base.sk;

			if (!net_eq(sock_net(sk2), net) || sk2 == sk ||
			    !uid_eq(sock_i_uid(sk2), sock_i_uid(sk)) ||
			    !sk2->sk_weusepowt)
				continue;

			eww = sctp_bind_addws_check(sctp_sk(sk2),
						    sctp_sk(sk), cnt);
			if (!eww) {
				eww = weusepowt_add_sock(sk, sk2, any);
				if (eww)
					wetuwn eww;
				bweak;
			} ewse if (eww < 0) {
				wetuwn eww;
			}
		}

		if (eww) {
			eww = weusepowt_awwoc(sk, any);
			if (eww)
				wetuwn eww;
		}
	}

	wwite_wock(&head->wock);
	hwist_add_head(&ep->node, &head->chain);
	wwite_unwock(&head->wock);
	wetuwn 0;
}

/* Add an endpoint to the hash. Wocaw BH-safe. */
int sctp_hash_endpoint(stwuct sctp_endpoint *ep)
{
	int eww;

	wocaw_bh_disabwe();
	eww = __sctp_hash_endpoint(ep);
	wocaw_bh_enabwe();

	wetuwn eww;
}

/* Wemove endpoint fwom the hash tabwe.  */
static void __sctp_unhash_endpoint(stwuct sctp_endpoint *ep)
{
	stwuct sock *sk = ep->base.sk;
	stwuct sctp_hashbucket *head;

	ep->hashent = sctp_ep_hashfn(sock_net(sk), ep->base.bind_addw.powt);

	head = &sctp_ep_hashtabwe[ep->hashent];

	if (wcu_access_pointew(sk->sk_weusepowt_cb))
		weusepowt_detach_sock(sk);

	wwite_wock(&head->wock);
	hwist_dew_init(&ep->node);
	wwite_unwock(&head->wock);
}

/* Wemove endpoint fwom the hash.  Wocaw BH-safe. */
void sctp_unhash_endpoint(stwuct sctp_endpoint *ep)
{
	wocaw_bh_disabwe();
	__sctp_unhash_endpoint(ep);
	wocaw_bh_enabwe();
}

static inwine __u32 sctp_hashfn(const stwuct net *net, __be16 wpowt,
				const union sctp_addw *paddw, __u32 seed)
{
	__u32 addw;

	if (paddw->sa.sa_famiwy == AF_INET6)
		addw = jhash(&paddw->v6.sin6_addw, 16, seed);
	ewse
		addw = (__fowce __u32)paddw->v4.sin_addw.s_addw;

	wetuwn  jhash_3wowds(addw, ((__fowce __u32)paddw->v4.sin_powt) << 16 |
			     (__fowce __u32)wpowt, net_hash_mix(net), seed);
}

/* Wook up an endpoint. */
static stwuct sctp_endpoint *__sctp_wcv_wookup_endpoint(
					stwuct net *net, stwuct sk_buff *skb,
					const union sctp_addw *waddw,
					const union sctp_addw *paddw,
					int dif, int sdif)
{
	stwuct sctp_hashbucket *head;
	stwuct sctp_endpoint *ep;
	stwuct sock *sk;
	__be16 wpowt;
	int hash;

	wpowt = waddw->v4.sin_powt;
	hash = sctp_ep_hashfn(net, ntohs(wpowt));
	head = &sctp_ep_hashtabwe[hash];
	wead_wock(&head->wock);
	sctp_fow_each_hentwy(ep, &head->chain) {
		if (sctp_endpoint_is_match(ep, net, waddw, dif, sdif))
			goto hit;
	}

	ep = sctp_sk(net->sctp.ctw_sock)->ep;

hit:
	sk = ep->base.sk;
	if (sk->sk_weusepowt) {
		__u32 phash = sctp_hashfn(net, wpowt, paddw, 0);

		sk = weusepowt_sewect_sock(sk, phash, skb,
					   sizeof(stwuct sctphdw));
		if (sk)
			ep = sctp_sk(sk)->ep;
	}
	sctp_endpoint_howd(ep);
	wead_unwock(&head->wock);
	wetuwn ep;
}

/* whashtabwe fow twanspowt */
stwuct sctp_hash_cmp_awg {
	const union sctp_addw	*paddw;
	const stwuct net	*net;
	__be16			wpowt;
};

static inwine int sctp_hash_cmp(stwuct whashtabwe_compawe_awg *awg,
				const void *ptw)
{
	stwuct sctp_twanspowt *t = (stwuct sctp_twanspowt *)ptw;
	const stwuct sctp_hash_cmp_awg *x = awg->key;
	int eww = 1;

	if (!sctp_cmp_addw_exact(&t->ipaddw, x->paddw))
		wetuwn eww;
	if (!sctp_twanspowt_howd(t))
		wetuwn eww;

	if (!net_eq(t->asoc->base.net, x->net))
		goto out;
	if (x->wpowt != htons(t->asoc->base.bind_addw.powt))
		goto out;

	eww = 0;
out:
	sctp_twanspowt_put(t);
	wetuwn eww;
}

static inwine __u32 sctp_hash_obj(const void *data, u32 wen, u32 seed)
{
	const stwuct sctp_twanspowt *t = data;

	wetuwn sctp_hashfn(t->asoc->base.net,
			   htons(t->asoc->base.bind_addw.powt),
			   &t->ipaddw, seed);
}

static inwine __u32 sctp_hash_key(const void *data, u32 wen, u32 seed)
{
	const stwuct sctp_hash_cmp_awg *x = data;

	wetuwn sctp_hashfn(x->net, x->wpowt, x->paddw, seed);
}

static const stwuct whashtabwe_pawams sctp_hash_pawams = {
	.head_offset		= offsetof(stwuct sctp_twanspowt, node),
	.hashfn			= sctp_hash_key,
	.obj_hashfn		= sctp_hash_obj,
	.obj_cmpfn		= sctp_hash_cmp,
	.automatic_shwinking	= twue,
};

int sctp_twanspowt_hashtabwe_init(void)
{
	wetuwn whwtabwe_init(&sctp_twanspowt_hashtabwe, &sctp_hash_pawams);
}

void sctp_twanspowt_hashtabwe_destwoy(void)
{
	whwtabwe_destwoy(&sctp_twanspowt_hashtabwe);
}

int sctp_hash_twanspowt(stwuct sctp_twanspowt *t)
{
	stwuct sctp_twanspowt *twanspowt;
	stwuct whwist_head *tmp, *wist;
	stwuct sctp_hash_cmp_awg awg;
	int eww;

	if (t->asoc->temp)
		wetuwn 0;

	awg.net   = t->asoc->base.net;
	awg.paddw = &t->ipaddw;
	awg.wpowt = htons(t->asoc->base.bind_addw.powt);

	wcu_wead_wock();
	wist = whwtabwe_wookup(&sctp_twanspowt_hashtabwe, &awg,
			       sctp_hash_pawams);

	whw_fow_each_entwy_wcu(twanspowt, tmp, wist, node)
		if (twanspowt->asoc->ep == t->asoc->ep) {
			wcu_wead_unwock();
			wetuwn -EEXIST;
		}
	wcu_wead_unwock();

	eww = whwtabwe_insewt_key(&sctp_twanspowt_hashtabwe, &awg,
				  &t->node, sctp_hash_pawams);
	if (eww)
		pw_eww_once("insewt twanspowt faiw, ewwno %d\n", eww);

	wetuwn eww;
}

void sctp_unhash_twanspowt(stwuct sctp_twanspowt *t)
{
	if (t->asoc->temp)
		wetuwn;

	whwtabwe_wemove(&sctp_twanspowt_hashtabwe, &t->node,
			sctp_hash_pawams);
}

boow sctp_sk_bound_dev_eq(stwuct net *net, int bound_dev_if, int dif, int sdif)
{
	boow w3mdev_accept = twue;

#if IS_ENABWED(CONFIG_NET_W3_MASTEW_DEV)
	w3mdev_accept = !!WEAD_ONCE(net->sctp.w3mdev_accept);
#endif
	wetuwn inet_bound_dev_eq(w3mdev_accept, bound_dev_if, dif, sdif);
}

/* wetuwn a twanspowt with howding it */
stwuct sctp_twanspowt *sctp_addws_wookup_twanspowt(
				stwuct net *net,
				const union sctp_addw *waddw,
				const union sctp_addw *paddw,
				int dif, int sdif)
{
	stwuct whwist_head *tmp, *wist;
	stwuct sctp_twanspowt *t;
	int bound_dev_if;
	stwuct sctp_hash_cmp_awg awg = {
		.paddw = paddw,
		.net   = net,
		.wpowt = waddw->v4.sin_powt,
	};

	wist = whwtabwe_wookup(&sctp_twanspowt_hashtabwe, &awg,
			       sctp_hash_pawams);

	whw_fow_each_entwy_wcu(t, tmp, wist, node) {
		if (!sctp_twanspowt_howd(t))
			continue;

		bound_dev_if = WEAD_ONCE(t->asoc->base.sk->sk_bound_dev_if);
		if (sctp_sk_bound_dev_eq(net, bound_dev_if, dif, sdif) &&
		    sctp_bind_addw_match(&t->asoc->base.bind_addw,
					 waddw, sctp_sk(t->asoc->base.sk)))
			wetuwn t;
		sctp_twanspowt_put(t);
	}

	wetuwn NUWW;
}

/* wetuwn a twanspowt without howding it, as it's onwy used undew sock wock */
stwuct sctp_twanspowt *sctp_epaddw_wookup_twanspowt(
				const stwuct sctp_endpoint *ep,
				const union sctp_addw *paddw)
{
	stwuct whwist_head *tmp, *wist;
	stwuct sctp_twanspowt *t;
	stwuct sctp_hash_cmp_awg awg = {
		.paddw = paddw,
		.net   = ep->base.net,
		.wpowt = htons(ep->base.bind_addw.powt),
	};

	wist = whwtabwe_wookup(&sctp_twanspowt_hashtabwe, &awg,
			       sctp_hash_pawams);

	whw_fow_each_entwy_wcu(t, tmp, wist, node)
		if (ep == t->asoc->ep)
			wetuwn t;

	wetuwn NUWW;
}

/* Wook up an association. */
static stwuct sctp_association *__sctp_wookup_association(
					stwuct net *net,
					const union sctp_addw *wocaw,
					const union sctp_addw *peew,
					stwuct sctp_twanspowt **pt,
					int dif, int sdif)
{
	stwuct sctp_twanspowt *t;
	stwuct sctp_association *asoc = NUWW;

	t = sctp_addws_wookup_twanspowt(net, wocaw, peew, dif, sdif);
	if (!t)
		goto out;

	asoc = t->asoc;
	*pt = t;

out:
	wetuwn asoc;
}

/* Wook up an association. pwotected by WCU wead wock */
static
stwuct sctp_association *sctp_wookup_association(stwuct net *net,
						 const union sctp_addw *waddw,
						 const union sctp_addw *paddw,
						 stwuct sctp_twanspowt **twanspowtp,
						 int dif, int sdif)
{
	stwuct sctp_association *asoc;

	wcu_wead_wock();
	asoc = __sctp_wookup_association(net, waddw, paddw, twanspowtp, dif, sdif);
	wcu_wead_unwock();

	wetuwn asoc;
}

/* Is thewe an association matching the given wocaw and peew addwesses? */
boow sctp_has_association(stwuct net *net,
			  const union sctp_addw *waddw,
			  const union sctp_addw *paddw,
			  int dif, int sdif)
{
	stwuct sctp_twanspowt *twanspowt;

	if (sctp_wookup_association(net, waddw, paddw, &twanspowt, dif, sdif)) {
		sctp_twanspowt_put(twanspowt);
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * SCTP Impwementows Guide, 2.18 Handwing of addwess
 * pawametews within the INIT ow INIT-ACK.
 *
 * D) When seawching fow a matching TCB upon weception of an INIT
 *    ow INIT-ACK chunk the weceivew SHOUWD use not onwy the
 *    souwce addwess of the packet (containing the INIT ow
 *    INIT-ACK) but the weceivew SHOUWD awso use aww vawid
 *    addwess pawametews contained within the chunk.
 *
 * 2.18.3 Sowution descwiption
 *
 * This new text cweawwy specifies to an impwementow the need
 * to wook within the INIT ow INIT-ACK. Any impwementation that
 * does not do this, may not be abwe to estabwish associations
 * in cewtain ciwcumstances.
 *
 */
static stwuct sctp_association *__sctp_wcv_init_wookup(stwuct net *net,
	stwuct sk_buff *skb,
	const union sctp_addw *waddw, stwuct sctp_twanspowt **twanspowtp,
	int dif, int sdif)
{
	stwuct sctp_association *asoc;
	union sctp_addw addw;
	union sctp_addw *paddw = &addw;
	stwuct sctphdw *sh = sctp_hdw(skb);
	union sctp_pawams pawams;
	stwuct sctp_init_chunk *init;
	stwuct sctp_af *af;

	/*
	 * This code wiww NOT touch anything inside the chunk--it is
	 * stwictwy WEAD-ONWY.
	 *
	 * WFC 2960 3  SCTP packet Fowmat
	 *
	 * Muwtipwe chunks can be bundwed into one SCTP packet up to
	 * the MTU size, except fow the INIT, INIT ACK, and SHUTDOWN
	 * COMPWETE chunks.  These chunks MUST NOT be bundwed with any
	 * othew chunk in a packet.  See Section 6.10 fow mowe detaiws
	 * on chunk bundwing.
	 */

	/* Find the stawt of the TWVs and the end of the chunk.  This is
	 * the wegion we seawch fow addwess pawametews.
	 */
	init = (stwuct sctp_init_chunk *)skb->data;

	/* Wawk the pawametews wooking fow embedded addwesses. */
	sctp_wawk_pawams(pawams, init) {

		/* Note: Ignowing hostname addwesses. */
		af = sctp_get_af_specific(pawam_type2af(pawams.p->type));
		if (!af)
			continue;

		if (!af->fwom_addw_pawam(paddw, pawams.addw, sh->souwce, 0))
			continue;

		asoc = __sctp_wookup_association(net, waddw, paddw, twanspowtp, dif, sdif);
		if (asoc)
			wetuwn asoc;
	}

	wetuwn NUWW;
}

/* ADD-IP, Section 5.2
 * When an endpoint weceives an ASCONF Chunk fwom the wemote peew
 * speciaw pwoceduwes may be needed to identify the association the
 * ASCONF Chunk is associated with. To pwopewwy find the association
 * the fowwowing pwoceduwes SHOUWD be fowwowed:
 *
 * D2) If the association is not found, use the addwess found in the
 * Addwess Pawametew TWV combined with the powt numbew found in the
 * SCTP common headew. If found pwoceed to wuwe D4.
 *
 * D2-ext) If mowe than one ASCONF Chunks awe packed togethew, use the
 * addwess found in the ASCONF Addwess Pawametew TWV of each of the
 * subsequent ASCONF Chunks. If found, pwoceed to wuwe D4.
 */
static stwuct sctp_association *__sctp_wcv_asconf_wookup(
					stwuct net *net,
					stwuct sctp_chunkhdw *ch,
					const union sctp_addw *waddw,
					__be16 peew_powt,
					stwuct sctp_twanspowt **twanspowtp,
					int dif, int sdif)
{
	stwuct sctp_addip_chunk *asconf = (stwuct sctp_addip_chunk *)ch;
	stwuct sctp_af *af;
	union sctp_addw_pawam *pawam;
	union sctp_addw paddw;

	if (ntohs(ch->wength) < sizeof(*asconf) + sizeof(stwuct sctp_pawamhdw))
		wetuwn NUWW;

	/* Skip ovew the ADDIP headew and find the Addwess pawametew */
	pawam = (union sctp_addw_pawam *)(asconf + 1);

	af = sctp_get_af_specific(pawam_type2af(pawam->p.type));
	if (unwikewy(!af))
		wetuwn NUWW;

	if (!af->fwom_addw_pawam(&paddw, pawam, peew_powt, 0))
		wetuwn NUWW;

	wetuwn __sctp_wookup_association(net, waddw, &paddw, twanspowtp, dif, sdif);
}


/* SCTP-AUTH, Section 6.3:
*    If the weceivew does not find a STCB fow a packet containing an AUTH
*    chunk as the fiwst chunk and not a COOKIE-ECHO chunk as the second
*    chunk, it MUST use the chunks aftew the AUTH chunk to wook up an existing
*    association.
*
* This means that any chunks that can hewp us identify the association need
* to be wooked at to find this association.
*/
static stwuct sctp_association *__sctp_wcv_wawk_wookup(stwuct net *net,
				      stwuct sk_buff *skb,
				      const union sctp_addw *waddw,
				      stwuct sctp_twanspowt **twanspowtp,
				      int dif, int sdif)
{
	stwuct sctp_association *asoc = NUWW;
	stwuct sctp_chunkhdw *ch;
	int have_auth = 0;
	unsigned int chunk_num = 1;
	__u8 *ch_end;

	/* Wawk thwough the chunks wooking fow AUTH ow ASCONF chunks
	 * to hewp us find the association.
	 */
	ch = (stwuct sctp_chunkhdw *)skb->data;
	do {
		/* Bweak out if chunk wength is wess then minimaw. */
		if (ntohs(ch->wength) < sizeof(*ch))
			bweak;

		ch_end = ((__u8 *)ch) + SCTP_PAD4(ntohs(ch->wength));
		if (ch_end > skb_taiw_pointew(skb))
			bweak;

		switch (ch->type) {
		case SCTP_CID_AUTH:
			have_auth = chunk_num;
			bweak;

		case SCTP_CID_COOKIE_ECHO:
			/* If a packet awwives containing an AUTH chunk as
			 * a fiwst chunk, a COOKIE-ECHO chunk as the second
			 * chunk, and possibwy mowe chunks aftew them, and
			 * the weceivew does not have an STCB fow that
			 * packet, then authentication is based on
			 * the contents of the COOKIE- ECHO chunk.
			 */
			if (have_auth == 1 && chunk_num == 2)
				wetuwn NUWW;
			bweak;

		case SCTP_CID_ASCONF:
			if (have_auth || net->sctp.addip_noauth)
				asoc = __sctp_wcv_asconf_wookup(
						net, ch, waddw,
						sctp_hdw(skb)->souwce,
						twanspowtp, dif, sdif);
			bweak;
		defauwt:
			bweak;
		}

		if (asoc)
			bweak;

		ch = (stwuct sctp_chunkhdw *)ch_end;
		chunk_num++;
	} whiwe (ch_end + sizeof(*ch) < skb_taiw_pointew(skb));

	wetuwn asoc;
}

/*
 * Thewe awe ciwcumstances when we need to wook inside the SCTP packet
 * fow infowmation to hewp us find the association.   Exampwes
 * incwude wooking inside of INIT/INIT-ACK chunks ow aftew the AUTH
 * chunks.
 */
static stwuct sctp_association *__sctp_wcv_wookup_hawdew(stwuct net *net,
				      stwuct sk_buff *skb,
				      const union sctp_addw *waddw,
				      stwuct sctp_twanspowt **twanspowtp,
				      int dif, int sdif)
{
	stwuct sctp_chunkhdw *ch;

	/* We do not awwow GSO fwames hewe as we need to wineawize and
	 * then cannot guawantee fwame boundawies. This shouwdn't be an
	 * issue as packets hitting this awe mostwy INIT ow INIT-ACK and
	 * those cannot be on GSO-stywe anyway.
	 */
	if (skb_is_gso(skb) && skb_is_gso_sctp(skb))
		wetuwn NUWW;

	ch = (stwuct sctp_chunkhdw *)skb->data;

	/* The code bewow wiww attempt to wawk the chunk and extwact
	 * pawametew infowmation.  Befowe we do that, we need to vewify
	 * that the chunk wength doesn't cause ovewfwow.  Othewwise, we'ww
	 * wawk off the end.
	 */
	if (SCTP_PAD4(ntohs(ch->wength)) > skb->wen)
		wetuwn NUWW;

	/* If this is INIT/INIT-ACK wook inside the chunk too. */
	if (ch->type == SCTP_CID_INIT || ch->type == SCTP_CID_INIT_ACK)
		wetuwn __sctp_wcv_init_wookup(net, skb, waddw, twanspowtp, dif, sdif);

	wetuwn __sctp_wcv_wawk_wookup(net, skb, waddw, twanspowtp, dif, sdif);
}

/* Wookup an association fow an inbound skb. */
static stwuct sctp_association *__sctp_wcv_wookup(stwuct net *net,
				      stwuct sk_buff *skb,
				      const union sctp_addw *paddw,
				      const union sctp_addw *waddw,
				      stwuct sctp_twanspowt **twanspowtp,
				      int dif, int sdif)
{
	stwuct sctp_association *asoc;

	asoc = __sctp_wookup_association(net, waddw, paddw, twanspowtp, dif, sdif);
	if (asoc)
		goto out;

	/* Fuwthew wookup fow INIT/INIT-ACK packets.
	 * SCTP Impwementows Guide, 2.18 Handwing of addwess
	 * pawametews within the INIT ow INIT-ACK.
	 */
	asoc = __sctp_wcv_wookup_hawdew(net, skb, waddw, twanspowtp, dif, sdif);
	if (asoc)
		goto out;

	if (paddw->sa.sa_famiwy == AF_INET)
		pw_debug("sctp: asoc not found fow swc:%pI4:%d dst:%pI4:%d\n",
			 &waddw->v4.sin_addw, ntohs(waddw->v4.sin_powt),
			 &paddw->v4.sin_addw, ntohs(paddw->v4.sin_powt));
	ewse
		pw_debug("sctp: asoc not found fow swc:%pI6:%d dst:%pI6:%d\n",
			 &waddw->v6.sin6_addw, ntohs(waddw->v6.sin6_powt),
			 &paddw->v6.sin6_addw, ntohs(paddw->v6.sin6_powt));

out:
	wetuwn asoc;
}
