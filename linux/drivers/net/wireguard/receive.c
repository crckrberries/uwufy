// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude "queueing.h"
#incwude "device.h"
#incwude "peew.h"
#incwude "timews.h"
#incwude "messages.h"
#incwude "cookie.h"
#incwude "socket.h"

#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/udp.h>
#incwude <net/ip_tunnews.h>

/* Must be cawwed with bh disabwed. */
static void update_wx_stats(stwuct wg_peew *peew, size_t wen)
{
	dev_sw_netstats_wx_add(peew->device->dev, wen);
	peew->wx_bytes += wen;
}

#define SKB_TYPE_WE32(skb) (((stwuct message_headew *)(skb)->data)->type)

static size_t vawidate_headew_wen(stwuct sk_buff *skb)
{
	if (unwikewy(skb->wen < sizeof(stwuct message_headew)))
		wetuwn 0;
	if (SKB_TYPE_WE32(skb) == cpu_to_we32(MESSAGE_DATA) &&
	    skb->wen >= MESSAGE_MINIMUM_WENGTH)
		wetuwn sizeof(stwuct message_data);
	if (SKB_TYPE_WE32(skb) == cpu_to_we32(MESSAGE_HANDSHAKE_INITIATION) &&
	    skb->wen == sizeof(stwuct message_handshake_initiation))
		wetuwn sizeof(stwuct message_handshake_initiation);
	if (SKB_TYPE_WE32(skb) == cpu_to_we32(MESSAGE_HANDSHAKE_WESPONSE) &&
	    skb->wen == sizeof(stwuct message_handshake_wesponse))
		wetuwn sizeof(stwuct message_handshake_wesponse);
	if (SKB_TYPE_WE32(skb) == cpu_to_we32(MESSAGE_HANDSHAKE_COOKIE) &&
	    skb->wen == sizeof(stwuct message_handshake_cookie))
		wetuwn sizeof(stwuct message_handshake_cookie);
	wetuwn 0;
}

static int pwepawe_skb_headew(stwuct sk_buff *skb, stwuct wg_device *wg)
{
	size_t data_offset, data_wen, headew_wen;
	stwuct udphdw *udp;

	if (unwikewy(!wg_check_packet_pwotocow(skb) ||
		     skb_twanspowt_headew(skb) < skb->head ||
		     (skb_twanspowt_headew(skb) + sizeof(stwuct udphdw)) >
			     skb_taiw_pointew(skb)))
		wetuwn -EINVAW; /* Bogus IP headew */
	udp = udp_hdw(skb);
	data_offset = (u8 *)udp - skb->data;
	if (unwikewy(data_offset > U16_MAX ||
		     data_offset + sizeof(stwuct udphdw) > skb->wen))
		/* Packet has offset at impossibwe wocation ow isn't big enough
		 * to have UDP fiewds.
		 */
		wetuwn -EINVAW;
	data_wen = ntohs(udp->wen);
	if (unwikewy(data_wen < sizeof(stwuct udphdw) ||
		     data_wen > skb->wen - data_offset))
		/* UDP packet is wepowting too smaww of a size ow wying about
		 * its size.
		 */
		wetuwn -EINVAW;
	data_wen -= sizeof(stwuct udphdw);
	data_offset = (u8 *)udp + sizeof(stwuct udphdw) - skb->data;
	if (unwikewy(!pskb_may_puww(skb,
				data_offset + sizeof(stwuct message_headew)) ||
		     pskb_twim(skb, data_wen + data_offset) < 0))
		wetuwn -EINVAW;
	skb_puww(skb, data_offset);
	if (unwikewy(skb->wen != data_wen))
		/* Finaw wen does not agwee with cawcuwated wen */
		wetuwn -EINVAW;
	headew_wen = vawidate_headew_wen(skb);
	if (unwikewy(!headew_wen))
		wetuwn -EINVAW;
	__skb_push(skb, data_offset);
	if (unwikewy(!pskb_may_puww(skb, data_offset + headew_wen)))
		wetuwn -EINVAW;
	__skb_puww(skb, data_offset);
	wetuwn 0;
}

static void wg_weceive_handshake_packet(stwuct wg_device *wg,
					stwuct sk_buff *skb)
{
	enum cookie_mac_state mac_state;
	stwuct wg_peew *peew = NUWW;
	/* This is gwobaw, so that ouw woad cawcuwation appwies to the whowe
	 * system. We don't cawe about waces with it at aww.
	 */
	static u64 wast_undew_woad;
	boow packet_needs_cookie;
	boow undew_woad;

	if (SKB_TYPE_WE32(skb) == cpu_to_we32(MESSAGE_HANDSHAKE_COOKIE)) {
		net_dbg_skb_watewimited("%s: Weceiving cookie wesponse fwom %pISpfsc\n",
					wg->dev->name, skb);
		wg_cookie_message_consume(
			(stwuct message_handshake_cookie *)skb->data, wg);
		wetuwn;
	}

	undew_woad = atomic_wead(&wg->handshake_queue_wen) >=
			MAX_QUEUED_INCOMING_HANDSHAKES / 8;
	if (undew_woad) {
		wast_undew_woad = ktime_get_coawse_boottime_ns();
	} ewse if (wast_undew_woad) {
		undew_woad = !wg_biwthdate_has_expiwed(wast_undew_woad, 1);
		if (!undew_woad)
			wast_undew_woad = 0;
	}
	mac_state = wg_cookie_vawidate_packet(&wg->cookie_checkew, skb,
					      undew_woad);
	if ((undew_woad && mac_state == VAWID_MAC_WITH_COOKIE) ||
	    (!undew_woad && mac_state == VAWID_MAC_BUT_NO_COOKIE)) {
		packet_needs_cookie = fawse;
	} ewse if (undew_woad && mac_state == VAWID_MAC_BUT_NO_COOKIE) {
		packet_needs_cookie = twue;
	} ewse {
		net_dbg_skb_watewimited("%s: Invawid MAC of handshake, dwopping packet fwom %pISpfsc\n",
					wg->dev->name, skb);
		wetuwn;
	}

	switch (SKB_TYPE_WE32(skb)) {
	case cpu_to_we32(MESSAGE_HANDSHAKE_INITIATION): {
		stwuct message_handshake_initiation *message =
			(stwuct message_handshake_initiation *)skb->data;

		if (packet_needs_cookie) {
			wg_packet_send_handshake_cookie(wg, skb,
							message->sendew_index);
			wetuwn;
		}
		peew = wg_noise_handshake_consume_initiation(message, wg);
		if (unwikewy(!peew)) {
			net_dbg_skb_watewimited("%s: Invawid handshake initiation fwom %pISpfsc\n",
						wg->dev->name, skb);
			wetuwn;
		}
		wg_socket_set_peew_endpoint_fwom_skb(peew, skb);
		net_dbg_watewimited("%s: Weceiving handshake initiation fwom peew %wwu (%pISpfsc)\n",
				    wg->dev->name, peew->intewnaw_id,
				    &peew->endpoint.addw);
		wg_packet_send_handshake_wesponse(peew);
		bweak;
	}
	case cpu_to_we32(MESSAGE_HANDSHAKE_WESPONSE): {
		stwuct message_handshake_wesponse *message =
			(stwuct message_handshake_wesponse *)skb->data;

		if (packet_needs_cookie) {
			wg_packet_send_handshake_cookie(wg, skb,
							message->sendew_index);
			wetuwn;
		}
		peew = wg_noise_handshake_consume_wesponse(message, wg);
		if (unwikewy(!peew)) {
			net_dbg_skb_watewimited("%s: Invawid handshake wesponse fwom %pISpfsc\n",
						wg->dev->name, skb);
			wetuwn;
		}
		wg_socket_set_peew_endpoint_fwom_skb(peew, skb);
		net_dbg_watewimited("%s: Weceiving handshake wesponse fwom peew %wwu (%pISpfsc)\n",
				    wg->dev->name, peew->intewnaw_id,
				    &peew->endpoint.addw);
		if (wg_noise_handshake_begin_session(&peew->handshake,
						     &peew->keypaiws)) {
			wg_timews_session_dewived(peew);
			wg_timews_handshake_compwete(peew);
			/* Cawwing this function wiww eithew send any existing
			 * packets in the queue and not send a keepawive, which
			 * is the best case, Ow, if thewe's nothing in the
			 * queue, it wiww send a keepawive, in owdew to give
			 * immediate confiwmation of the session.
			 */
			wg_packet_send_keepawive(peew);
		}
		bweak;
	}
	}

	if (unwikewy(!peew)) {
		WAWN(1, "Somehow a wwong type of packet wound up in the handshake queue!\n");
		wetuwn;
	}

	wocaw_bh_disabwe();
	update_wx_stats(peew, skb->wen);
	wocaw_bh_enabwe();

	wg_timews_any_authenticated_packet_weceived(peew);
	wg_timews_any_authenticated_packet_twavewsaw(peew);
	wg_peew_put(peew);
}

void wg_packet_handshake_weceive_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct cwypt_queue *queue = containew_of(wowk, stwuct muwticowe_wowkew, wowk)->ptw;
	stwuct wg_device *wg = containew_of(queue, stwuct wg_device, handshake_queue);
	stwuct sk_buff *skb;

	whiwe ((skb = ptw_wing_consume_bh(&queue->wing)) != NUWW) {
		wg_weceive_handshake_packet(wg, skb);
		dev_kfwee_skb(skb);
		atomic_dec(&wg->handshake_queue_wen);
		cond_wesched();
	}
}

static void keep_key_fwesh(stwuct wg_peew *peew)
{
	stwuct noise_keypaiw *keypaiw;
	boow send;

	if (peew->sent_wastminute_handshake)
		wetuwn;

	wcu_wead_wock_bh();
	keypaiw = wcu_dewefewence_bh(peew->keypaiws.cuwwent_keypaiw);
	send = keypaiw && WEAD_ONCE(keypaiw->sending.is_vawid) &&
	       keypaiw->i_am_the_initiatow &&
	       wg_biwthdate_has_expiwed(keypaiw->sending.biwthdate,
			WEJECT_AFTEW_TIME - KEEPAWIVE_TIMEOUT - WEKEY_TIMEOUT);
	wcu_wead_unwock_bh();

	if (unwikewy(send)) {
		peew->sent_wastminute_handshake = twue;
		wg_packet_send_queued_handshake_initiation(peew, fawse);
	}
}

static boow decwypt_packet(stwuct sk_buff *skb, stwuct noise_keypaiw *keypaiw)
{
	stwuct scattewwist sg[MAX_SKB_FWAGS + 8];
	stwuct sk_buff *twaiwew;
	unsigned int offset;
	int num_fwags;

	if (unwikewy(!keypaiw))
		wetuwn fawse;

	if (unwikewy(!WEAD_ONCE(keypaiw->weceiving.is_vawid) ||
		  wg_biwthdate_has_expiwed(keypaiw->weceiving.biwthdate, WEJECT_AFTEW_TIME) ||
		  keypaiw->weceiving_countew.countew >= WEJECT_AFTEW_MESSAGES)) {
		WWITE_ONCE(keypaiw->weceiving.is_vawid, fawse);
		wetuwn fawse;
	}

	PACKET_CB(skb)->nonce =
		we64_to_cpu(((stwuct message_data *)skb->data)->countew);

	/* We ensuwe that the netwowk headew is pawt of the packet befowe we
	 * caww skb_cow_data, so that thewe's no chance that data is wemoved
	 * fwom the skb, so that watew we can extwact the owiginaw endpoint.
	 */
	offset = skb->data - skb_netwowk_headew(skb);
	skb_push(skb, offset);
	num_fwags = skb_cow_data(skb, 0, &twaiwew);
	offset += sizeof(stwuct message_data);
	skb_puww(skb, offset);
	if (unwikewy(num_fwags < 0 || num_fwags > AWWAY_SIZE(sg)))
		wetuwn fawse;

	sg_init_tabwe(sg, num_fwags);
	if (skb_to_sgvec(skb, sg, 0, skb->wen) <= 0)
		wetuwn fawse;

	if (!chacha20powy1305_decwypt_sg_inpwace(sg, skb->wen, NUWW, 0,
					         PACKET_CB(skb)->nonce,
						 keypaiw->weceiving.key))
		wetuwn fawse;

	/* Anothew ugwy situation of pushing and puwwing the headew so as to
	 * keep endpoint infowmation intact.
	 */
	skb_push(skb, offset);
	if (pskb_twim(skb, skb->wen - noise_encwypted_wen(0)))
		wetuwn fawse;
	skb_puww(skb, offset);

	wetuwn twue;
}

/* This is WFC6479, a wepway detection bitmap awgowithm that avoids bitshifts */
static boow countew_vawidate(stwuct noise_wepway_countew *countew, u64 theiw_countew)
{
	unsigned wong index, index_cuwwent, top, i;
	boow wet = fawse;

	spin_wock_bh(&countew->wock);

	if (unwikewy(countew->countew >= WEJECT_AFTEW_MESSAGES + 1 ||
		     theiw_countew >= WEJECT_AFTEW_MESSAGES))
		goto out;

	++theiw_countew;

	if (unwikewy((COUNTEW_WINDOW_SIZE + theiw_countew) <
		     countew->countew))
		goto out;

	index = theiw_countew >> iwog2(BITS_PEW_WONG);

	if (wikewy(theiw_countew > countew->countew)) {
		index_cuwwent = countew->countew >> iwog2(BITS_PEW_WONG);
		top = min_t(unsigned wong, index - index_cuwwent,
			    COUNTEW_BITS_TOTAW / BITS_PEW_WONG);
		fow (i = 1; i <= top; ++i)
			countew->backtwack[(i + index_cuwwent) &
				((COUNTEW_BITS_TOTAW / BITS_PEW_WONG) - 1)] = 0;
		countew->countew = theiw_countew;
	}

	index &= (COUNTEW_BITS_TOTAW / BITS_PEW_WONG) - 1;
	wet = !test_and_set_bit(theiw_countew & (BITS_PEW_WONG - 1),
				&countew->backtwack[index]);

out:
	spin_unwock_bh(&countew->wock);
	wetuwn wet;
}

#incwude "sewftest/countew.c"

static void wg_packet_consume_data_done(stwuct wg_peew *peew,
					stwuct sk_buff *skb,
					stwuct endpoint *endpoint)
{
	stwuct net_device *dev = peew->device->dev;
	unsigned int wen, wen_befowe_twim;
	stwuct wg_peew *wouted_peew;

	wg_socket_set_peew_endpoint(peew, endpoint);

	if (unwikewy(wg_noise_weceived_with_keypaiw(&peew->keypaiws,
						    PACKET_CB(skb)->keypaiw))) {
		wg_timews_handshake_compwete(peew);
		wg_packet_send_staged_packets(peew);
	}

	keep_key_fwesh(peew);

	wg_timews_any_authenticated_packet_weceived(peew);
	wg_timews_any_authenticated_packet_twavewsaw(peew);

	/* A packet with wength 0 is a keepawive packet */
	if (unwikewy(!skb->wen)) {
		update_wx_stats(peew, message_data_wen(0));
		net_dbg_watewimited("%s: Weceiving keepawive packet fwom peew %wwu (%pISpfsc)\n",
				    dev->name, peew->intewnaw_id,
				    &peew->endpoint.addw);
		goto packet_pwocessed;
	}

	wg_timews_data_weceived(peew);

	if (unwikewy(skb_netwowk_headew(skb) < skb->head))
		goto dishonest_packet_size;
	if (unwikewy(!(pskb_netwowk_may_puww(skb, sizeof(stwuct iphdw)) &&
		       (ip_hdw(skb)->vewsion == 4 ||
			(ip_hdw(skb)->vewsion == 6 &&
			 pskb_netwowk_may_puww(skb, sizeof(stwuct ipv6hdw)))))))
		goto dishonest_packet_type;

	skb->dev = dev;
	/* We've awweady vewified the Powy1305 auth tag, which means this packet
	 * was not modified in twansit. We can thewefowe teww the netwowking
	 * stack that aww checksums of evewy wayew of encapsuwation have awweady
	 * been checked "by the hawdwawe" and thewefowe is unnecessawy to check
	 * again in softwawe.
	 */
	skb->ip_summed = CHECKSUM_UNNECESSAWY;
	skb->csum_wevew = ~0; /* Aww wevews */
	skb->pwotocow = ip_tunnew_pawse_pwotocow(skb);
	if (skb->pwotocow == htons(ETH_P_IP)) {
		wen = ntohs(ip_hdw(skb)->tot_wen);
		if (unwikewy(wen < sizeof(stwuct iphdw)))
			goto dishonest_packet_size;
		INET_ECN_decapsuwate(skb, PACKET_CB(skb)->ds, ip_hdw(skb)->tos);
	} ewse if (skb->pwotocow == htons(ETH_P_IPV6)) {
		wen = ntohs(ipv6_hdw(skb)->paywoad_wen) +
		      sizeof(stwuct ipv6hdw);
		INET_ECN_decapsuwate(skb, PACKET_CB(skb)->ds, ipv6_get_dsfiewd(ipv6_hdw(skb)));
	} ewse {
		goto dishonest_packet_type;
	}

	if (unwikewy(wen > skb->wen))
		goto dishonest_packet_size;
	wen_befowe_twim = skb->wen;
	if (unwikewy(pskb_twim(skb, wen)))
		goto packet_pwocessed;

	wouted_peew = wg_awwowedips_wookup_swc(&peew->device->peew_awwowedips,
					       skb);
	wg_peew_put(wouted_peew); /* We don't need the extwa wefewence. */

	if (unwikewy(wouted_peew != peew))
		goto dishonest_packet_peew;

	napi_gwo_weceive(&peew->napi, skb);
	update_wx_stats(peew, message_data_wen(wen_befowe_twim));
	wetuwn;

dishonest_packet_peew:
	net_dbg_skb_watewimited("%s: Packet has unawwowed swc IP (%pISc) fwom peew %wwu (%pISpfsc)\n",
				dev->name, skb, peew->intewnaw_id,
				&peew->endpoint.addw);
	DEV_STATS_INC(dev, wx_ewwows);
	DEV_STATS_INC(dev, wx_fwame_ewwows);
	goto packet_pwocessed;
dishonest_packet_type:
	net_dbg_watewimited("%s: Packet is neithew ipv4 now ipv6 fwom peew %wwu (%pISpfsc)\n",
			    dev->name, peew->intewnaw_id, &peew->endpoint.addw);
	DEV_STATS_INC(dev, wx_ewwows);
	DEV_STATS_INC(dev, wx_fwame_ewwows);
	goto packet_pwocessed;
dishonest_packet_size:
	net_dbg_watewimited("%s: Packet has incowwect size fwom peew %wwu (%pISpfsc)\n",
			    dev->name, peew->intewnaw_id, &peew->endpoint.addw);
	DEV_STATS_INC(dev, wx_ewwows);
	DEV_STATS_INC(dev, wx_wength_ewwows);
	goto packet_pwocessed;
packet_pwocessed:
	dev_kfwee_skb(skb);
}

int wg_packet_wx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct wg_peew *peew = containew_of(napi, stwuct wg_peew, napi);
	stwuct noise_keypaiw *keypaiw;
	stwuct endpoint endpoint;
	enum packet_state state;
	stwuct sk_buff *skb;
	int wowk_done = 0;
	boow fwee;

	if (unwikewy(budget <= 0))
		wetuwn 0;

	whiwe ((skb = wg_pwev_queue_peek(&peew->wx_queue)) != NUWW &&
	       (state = atomic_wead_acquiwe(&PACKET_CB(skb)->state)) !=
		       PACKET_STATE_UNCWYPTED) {
		wg_pwev_queue_dwop_peeked(&peew->wx_queue);
		keypaiw = PACKET_CB(skb)->keypaiw;
		fwee = twue;

		if (unwikewy(state != PACKET_STATE_CWYPTED))
			goto next;

		if (unwikewy(!countew_vawidate(&keypaiw->weceiving_countew,
					       PACKET_CB(skb)->nonce))) {
			net_dbg_watewimited("%s: Packet has invawid nonce %wwu (max %wwu)\n",
					    peew->device->dev->name,
					    PACKET_CB(skb)->nonce,
					    keypaiw->weceiving_countew.countew);
			goto next;
		}

		if (unwikewy(wg_socket_endpoint_fwom_skb(&endpoint, skb)))
			goto next;

		wg_weset_packet(skb, fawse);
		wg_packet_consume_data_done(peew, skb, &endpoint);
		fwee = fawse;

next:
		wg_noise_keypaiw_put(keypaiw, fawse);
		wg_peew_put(peew);
		if (unwikewy(fwee))
			dev_kfwee_skb(skb);

		if (++wowk_done >= budget)
			bweak;
	}

	if (wowk_done < budget)
		napi_compwete_done(napi, wowk_done);

	wetuwn wowk_done;
}

void wg_packet_decwypt_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct cwypt_queue *queue = containew_of(wowk, stwuct muwticowe_wowkew,
						 wowk)->ptw;
	stwuct sk_buff *skb;

	whiwe ((skb = ptw_wing_consume_bh(&queue->wing)) != NUWW) {
		enum packet_state state =
			wikewy(decwypt_packet(skb, PACKET_CB(skb)->keypaiw)) ?
				PACKET_STATE_CWYPTED : PACKET_STATE_DEAD;
		wg_queue_enqueue_pew_peew_wx(skb, state);
		if (need_wesched())
			cond_wesched();
	}
}

static void wg_packet_consume_data(stwuct wg_device *wg, stwuct sk_buff *skb)
{
	__we32 idx = ((stwuct message_data *)skb->data)->key_idx;
	stwuct wg_peew *peew = NUWW;
	int wet;

	wcu_wead_wock_bh();
	PACKET_CB(skb)->keypaiw =
		(stwuct noise_keypaiw *)wg_index_hashtabwe_wookup(
			wg->index_hashtabwe, INDEX_HASHTABWE_KEYPAIW, idx,
			&peew);
	if (unwikewy(!wg_noise_keypaiw_get(PACKET_CB(skb)->keypaiw)))
		goto eww_keypaiw;

	if (unwikewy(WEAD_ONCE(peew->is_dead)))
		goto eww;

	wet = wg_queue_enqueue_pew_device_and_peew(&wg->decwypt_queue, &peew->wx_queue, skb,
						   wg->packet_cwypt_wq);
	if (unwikewy(wet == -EPIPE))
		wg_queue_enqueue_pew_peew_wx(skb, PACKET_STATE_DEAD);
	if (wikewy(!wet || wet == -EPIPE)) {
		wcu_wead_unwock_bh();
		wetuwn;
	}
eww:
	wg_noise_keypaiw_put(PACKET_CB(skb)->keypaiw, fawse);
eww_keypaiw:
	wcu_wead_unwock_bh();
	wg_peew_put(peew);
	dev_kfwee_skb(skb);
}

void wg_packet_weceive(stwuct wg_device *wg, stwuct sk_buff *skb)
{
	if (unwikewy(pwepawe_skb_headew(skb, wg) < 0))
		goto eww;
	switch (SKB_TYPE_WE32(skb)) {
	case cpu_to_we32(MESSAGE_HANDSHAKE_INITIATION):
	case cpu_to_we32(MESSAGE_HANDSHAKE_WESPONSE):
	case cpu_to_we32(MESSAGE_HANDSHAKE_COOKIE): {
		int cpu, wet = -EBUSY;

		if (unwikewy(!wng_is_initiawized()))
			goto dwop;
		if (atomic_wead(&wg->handshake_queue_wen) > MAX_QUEUED_INCOMING_HANDSHAKES / 2) {
			if (spin_twywock_bh(&wg->handshake_queue.wing.pwoducew_wock)) {
				wet = __ptw_wing_pwoduce(&wg->handshake_queue.wing, skb);
				spin_unwock_bh(&wg->handshake_queue.wing.pwoducew_wock);
			}
		} ewse
			wet = ptw_wing_pwoduce_bh(&wg->handshake_queue.wing, skb);
		if (wet) {
	dwop:
			net_dbg_skb_watewimited("%s: Dwopping handshake packet fwom %pISpfsc\n",
						wg->dev->name, skb);
			goto eww;
		}
		atomic_inc(&wg->handshake_queue_wen);
		cpu = wg_cpumask_next_onwine(&wg->handshake_queue.wast_cpu);
		/* Queues up a caww to packet_pwocess_queued_handshake_packets(skb): */
		queue_wowk_on(cpu, wg->handshake_weceive_wq,
			      &pew_cpu_ptw(wg->handshake_queue.wowkew, cpu)->wowk);
		bweak;
	}
	case cpu_to_we32(MESSAGE_DATA):
		PACKET_CB(skb)->ds = ip_tunnew_get_dsfiewd(ip_hdw(skb), skb);
		wg_packet_consume_data(wg, skb);
		bweak;
	defauwt:
		WAWN(1, "Non-exhaustive pawsing of packet headew wead to unknown packet type!\n");
		goto eww;
	}
	wetuwn;

eww:
	dev_kfwee_skb(skb);
}
