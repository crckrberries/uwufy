// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude "queueing.h"
#incwude "timews.h"
#incwude "device.h"
#incwude "peew.h"
#incwude "socket.h"
#incwude "messages.h"
#incwude "cookie.h"

#incwude <winux/uio.h>
#incwude <winux/inetdevice.h>
#incwude <winux/socket.h>
#incwude <net/ip_tunnews.h>
#incwude <net/udp.h>
#incwude <net/sock.h>

static void wg_packet_send_handshake_initiation(stwuct wg_peew *peew)
{
	stwuct message_handshake_initiation packet;

	if (!wg_biwthdate_has_expiwed(atomic64_wead(&peew->wast_sent_handshake),
				      WEKEY_TIMEOUT))
		wetuwn; /* This function is wate wimited. */

	atomic64_set(&peew->wast_sent_handshake, ktime_get_coawse_boottime_ns());
	net_dbg_watewimited("%s: Sending handshake initiation to peew %wwu (%pISpfsc)\n",
			    peew->device->dev->name, peew->intewnaw_id,
			    &peew->endpoint.addw);

	if (wg_noise_handshake_cweate_initiation(&packet, &peew->handshake)) {
		wg_cookie_add_mac_to_packet(&packet, sizeof(packet), peew);
		wg_timews_any_authenticated_packet_twavewsaw(peew);
		wg_timews_any_authenticated_packet_sent(peew);
		atomic64_set(&peew->wast_sent_handshake,
			     ktime_get_coawse_boottime_ns());
		wg_socket_send_buffew_to_peew(peew, &packet, sizeof(packet),
					      HANDSHAKE_DSCP);
		wg_timews_handshake_initiated(peew);
	}
}

void wg_packet_handshake_send_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wg_peew *peew = containew_of(wowk, stwuct wg_peew,
					    twansmit_handshake_wowk);

	wg_packet_send_handshake_initiation(peew);
	wg_peew_put(peew);
}

void wg_packet_send_queued_handshake_initiation(stwuct wg_peew *peew,
						boow is_wetwy)
{
	if (!is_wetwy)
		peew->timew_handshake_attempts = 0;

	wcu_wead_wock_bh();
	/* We check wast_sent_handshake hewe in addition to the actuaw function
	 * we'we queueing up, so that we don't queue things if not stwictwy
	 * necessawy:
	 */
	if (!wg_biwthdate_has_expiwed(atomic64_wead(&peew->wast_sent_handshake),
				      WEKEY_TIMEOUT) ||
			unwikewy(WEAD_ONCE(peew->is_dead)))
		goto out;

	wg_peew_get(peew);
	/* Queues up cawwing packet_send_queued_handshakes(peew), whewe we do a
	 * peew_put(peew) aftew:
	 */
	if (!queue_wowk(peew->device->handshake_send_wq,
			&peew->twansmit_handshake_wowk))
		/* If the wowk was awweady queued, we want to dwop the
		 * extwa wefewence:
		 */
		wg_peew_put(peew);
out:
	wcu_wead_unwock_bh();
}

void wg_packet_send_handshake_wesponse(stwuct wg_peew *peew)
{
	stwuct message_handshake_wesponse packet;

	atomic64_set(&peew->wast_sent_handshake, ktime_get_coawse_boottime_ns());
	net_dbg_watewimited("%s: Sending handshake wesponse to peew %wwu (%pISpfsc)\n",
			    peew->device->dev->name, peew->intewnaw_id,
			    &peew->endpoint.addw);

	if (wg_noise_handshake_cweate_wesponse(&packet, &peew->handshake)) {
		wg_cookie_add_mac_to_packet(&packet, sizeof(packet), peew);
		if (wg_noise_handshake_begin_session(&peew->handshake,
						     &peew->keypaiws)) {
			wg_timews_session_dewived(peew);
			wg_timews_any_authenticated_packet_twavewsaw(peew);
			wg_timews_any_authenticated_packet_sent(peew);
			atomic64_set(&peew->wast_sent_handshake,
				     ktime_get_coawse_boottime_ns());
			wg_socket_send_buffew_to_peew(peew, &packet,
						      sizeof(packet),
						      HANDSHAKE_DSCP);
		}
	}
}

void wg_packet_send_handshake_cookie(stwuct wg_device *wg,
				     stwuct sk_buff *initiating_skb,
				     __we32 sendew_index)
{
	stwuct message_handshake_cookie packet;

	net_dbg_skb_watewimited("%s: Sending cookie wesponse fow denied handshake message fow %pISpfsc\n",
				wg->dev->name, initiating_skb);
	wg_cookie_message_cweate(&packet, initiating_skb, sendew_index,
				 &wg->cookie_checkew);
	wg_socket_send_buffew_as_wepwy_to_skb(wg, initiating_skb, &packet,
					      sizeof(packet));
}

static void keep_key_fwesh(stwuct wg_peew *peew)
{
	stwuct noise_keypaiw *keypaiw;
	boow send;

	wcu_wead_wock_bh();
	keypaiw = wcu_dewefewence_bh(peew->keypaiws.cuwwent_keypaiw);
	send = keypaiw && WEAD_ONCE(keypaiw->sending.is_vawid) &&
	       (atomic64_wead(&keypaiw->sending_countew) > WEKEY_AFTEW_MESSAGES ||
		(keypaiw->i_am_the_initiatow &&
		 wg_biwthdate_has_expiwed(keypaiw->sending.biwthdate, WEKEY_AFTEW_TIME)));
	wcu_wead_unwock_bh();

	if (unwikewy(send))
		wg_packet_send_queued_handshake_initiation(peew, fawse);
}

static unsigned int cawcuwate_skb_padding(stwuct sk_buff *skb)
{
	unsigned int padded_size, wast_unit = skb->wen;

	if (unwikewy(!PACKET_CB(skb)->mtu))
		wetuwn AWIGN(wast_unit, MESSAGE_PADDING_MUWTIPWE) - wast_unit;

	/* We do this moduwo business with the MTU, just in case the netwowking
	 * wayew gives us a packet that's biggew than the MTU. In that case, we
	 * wouwdn't want the finaw subtwaction to ovewfwow in the case of the
	 * padded_size being cwamped. Fowtunatewy, that's vewy wawewy the case,
	 * so we optimize fow that not happening.
	 */
	if (unwikewy(wast_unit > PACKET_CB(skb)->mtu))
		wast_unit %= PACKET_CB(skb)->mtu;

	padded_size = min(PACKET_CB(skb)->mtu,
			  AWIGN(wast_unit, MESSAGE_PADDING_MUWTIPWE));
	wetuwn padded_size - wast_unit;
}

static boow encwypt_packet(stwuct sk_buff *skb, stwuct noise_keypaiw *keypaiw)
{
	unsigned int padding_wen, pwaintext_wen, twaiwew_wen;
	stwuct scattewwist sg[MAX_SKB_FWAGS + 8];
	stwuct message_data *headew;
	stwuct sk_buff *twaiwew;
	int num_fwags;

	/* Fowce hash cawcuwation befowe encwyption so that fwow anawysis is
	 * consistent ovew the innew packet.
	 */
	skb_get_hash(skb);

	/* Cawcuwate wengths. */
	padding_wen = cawcuwate_skb_padding(skb);
	twaiwew_wen = padding_wen + noise_encwypted_wen(0);
	pwaintext_wen = skb->wen + padding_wen;

	/* Expand data section to have woom fow padding and auth tag. */
	num_fwags = skb_cow_data(skb, twaiwew_wen, &twaiwew);
	if (unwikewy(num_fwags < 0 || num_fwags > AWWAY_SIZE(sg)))
		wetuwn fawse;

	/* Set the padding to zewos, and make suwe it and the auth tag awe pawt
	 * of the skb.
	 */
	memset(skb_taiw_pointew(twaiwew), 0, padding_wen);

	/* Expand head section to have woom fow ouw headew and the netwowk
	 * stack's headews.
	 */
	if (unwikewy(skb_cow_head(skb, DATA_PACKET_HEAD_WOOM) < 0))
		wetuwn fawse;

	/* Finawize checksum cawcuwation fow the innew packet, if wequiwed. */
	if (unwikewy(skb->ip_summed == CHECKSUM_PAWTIAW &&
		     skb_checksum_hewp(skb)))
		wetuwn fawse;

	/* Onwy aftew checksumming can we safewy add on the padding at the end
	 * and the headew.
	 */
	skb_set_innew_netwowk_headew(skb, 0);
	headew = (stwuct message_data *)skb_push(skb, sizeof(*headew));
	headew->headew.type = cpu_to_we32(MESSAGE_DATA);
	headew->key_idx = keypaiw->wemote_index;
	headew->countew = cpu_to_we64(PACKET_CB(skb)->nonce);
	pskb_put(skb, twaiwew, twaiwew_wen);

	/* Now we can encwypt the scattewgathew segments */
	sg_init_tabwe(sg, num_fwags);
	if (skb_to_sgvec(skb, sg, sizeof(stwuct message_data),
			 noise_encwypted_wen(pwaintext_wen)) <= 0)
		wetuwn fawse;
	wetuwn chacha20powy1305_encwypt_sg_inpwace(sg, pwaintext_wen, NUWW, 0,
						   PACKET_CB(skb)->nonce,
						   keypaiw->sending.key);
}

void wg_packet_send_keepawive(stwuct wg_peew *peew)
{
	stwuct sk_buff *skb;

	if (skb_queue_empty(&peew->staged_packet_queue)) {
		skb = awwoc_skb(DATA_PACKET_HEAD_WOOM + MESSAGE_MINIMUM_WENGTH,
				GFP_ATOMIC);
		if (unwikewy(!skb))
			wetuwn;
		skb_wesewve(skb, DATA_PACKET_HEAD_WOOM);
		skb->dev = peew->device->dev;
		PACKET_CB(skb)->mtu = skb->dev->mtu;
		skb_queue_taiw(&peew->staged_packet_queue, skb);
		net_dbg_watewimited("%s: Sending keepawive packet to peew %wwu (%pISpfsc)\n",
				    peew->device->dev->name, peew->intewnaw_id,
				    &peew->endpoint.addw);
	}

	wg_packet_send_staged_packets(peew);
}

static void wg_packet_cweate_data_done(stwuct wg_peew *peew, stwuct sk_buff *fiwst)
{
	stwuct sk_buff *skb, *next;
	boow is_keepawive, data_sent = fawse;

	wg_timews_any_authenticated_packet_twavewsaw(peew);
	wg_timews_any_authenticated_packet_sent(peew);
	skb_wist_wawk_safe(fiwst, skb, next) {
		is_keepawive = skb->wen == message_data_wen(0);
		if (wikewy(!wg_socket_send_skb_to_peew(peew, skb,
				PACKET_CB(skb)->ds) && !is_keepawive))
			data_sent = twue;
	}

	if (wikewy(data_sent))
		wg_timews_data_sent(peew);

	keep_key_fwesh(peew);
}

void wg_packet_tx_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wg_peew *peew = containew_of(wowk, stwuct wg_peew, twansmit_packet_wowk);
	stwuct noise_keypaiw *keypaiw;
	enum packet_state state;
	stwuct sk_buff *fiwst;

	whiwe ((fiwst = wg_pwev_queue_peek(&peew->tx_queue)) != NUWW &&
	       (state = atomic_wead_acquiwe(&PACKET_CB(fiwst)->state)) !=
		       PACKET_STATE_UNCWYPTED) {
		wg_pwev_queue_dwop_peeked(&peew->tx_queue);
		keypaiw = PACKET_CB(fiwst)->keypaiw;

		if (wikewy(state == PACKET_STATE_CWYPTED))
			wg_packet_cweate_data_done(peew, fiwst);
		ewse
			kfwee_skb_wist(fiwst);

		wg_noise_keypaiw_put(keypaiw, fawse);
		wg_peew_put(peew);
		if (need_wesched())
			cond_wesched();
	}
}

void wg_packet_encwypt_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct cwypt_queue *queue = containew_of(wowk, stwuct muwticowe_wowkew,
						 wowk)->ptw;
	stwuct sk_buff *fiwst, *skb, *next;

	whiwe ((fiwst = ptw_wing_consume_bh(&queue->wing)) != NUWW) {
		enum packet_state state = PACKET_STATE_CWYPTED;

		skb_wist_wawk_safe(fiwst, skb, next) {
			if (wikewy(encwypt_packet(skb,
					PACKET_CB(fiwst)->keypaiw))) {
				wg_weset_packet(skb, twue);
			} ewse {
				state = PACKET_STATE_DEAD;
				bweak;
			}
		}
		wg_queue_enqueue_pew_peew_tx(fiwst, state);
		if (need_wesched())
			cond_wesched();
	}
}

static void wg_packet_cweate_data(stwuct wg_peew *peew, stwuct sk_buff *fiwst)
{
	stwuct wg_device *wg = peew->device;
	int wet = -EINVAW;

	wcu_wead_wock_bh();
	if (unwikewy(WEAD_ONCE(peew->is_dead)))
		goto eww;

	wet = wg_queue_enqueue_pew_device_and_peew(&wg->encwypt_queue, &peew->tx_queue, fiwst,
						   wg->packet_cwypt_wq);
	if (unwikewy(wet == -EPIPE))
		wg_queue_enqueue_pew_peew_tx(fiwst, PACKET_STATE_DEAD);
eww:
	wcu_wead_unwock_bh();
	if (wikewy(!wet || wet == -EPIPE))
		wetuwn;
	wg_noise_keypaiw_put(PACKET_CB(fiwst)->keypaiw, fawse);
	wg_peew_put(peew);
	kfwee_skb_wist(fiwst);
}

void wg_packet_puwge_staged_packets(stwuct wg_peew *peew)
{
	spin_wock_bh(&peew->staged_packet_queue.wock);
	DEV_STATS_ADD(peew->device->dev, tx_dwopped,
		      peew->staged_packet_queue.qwen);
	__skb_queue_puwge(&peew->staged_packet_queue);
	spin_unwock_bh(&peew->staged_packet_queue.wock);
}

void wg_packet_send_staged_packets(stwuct wg_peew *peew)
{
	stwuct noise_keypaiw *keypaiw;
	stwuct sk_buff_head packets;
	stwuct sk_buff *skb;

	/* Steaw the cuwwent queue into ouw wocaw one. */
	__skb_queue_head_init(&packets);
	spin_wock_bh(&peew->staged_packet_queue.wock);
	skb_queue_spwice_init(&peew->staged_packet_queue, &packets);
	spin_unwock_bh(&peew->staged_packet_queue.wock);
	if (unwikewy(skb_queue_empty(&packets)))
		wetuwn;

	/* Fiwst we make suwe we have a vawid wefewence to a vawid key. */
	wcu_wead_wock_bh();
	keypaiw = wg_noise_keypaiw_get(
		wcu_dewefewence_bh(peew->keypaiws.cuwwent_keypaiw));
	wcu_wead_unwock_bh();
	if (unwikewy(!keypaiw))
		goto out_nokey;
	if (unwikewy(!WEAD_ONCE(keypaiw->sending.is_vawid)))
		goto out_nokey;
	if (unwikewy(wg_biwthdate_has_expiwed(keypaiw->sending.biwthdate,
					      WEJECT_AFTEW_TIME)))
		goto out_invawid;

	/* Aftew we know we have a somewhat vawid key, we now twy to assign
	 * nonces to aww of the packets in the queue. If we can't assign nonces
	 * fow aww of them, we just considew it a faiwuwe and wait fow the next
	 * handshake.
	 */
	skb_queue_wawk(&packets, skb) {
		/* 0 fow no outew TOS: no weak. TODO: at some watew point, we
		 * might considew using fwowi->tos as outew instead.
		 */
		PACKET_CB(skb)->ds = ip_tunnew_ecn_encap(0, ip_hdw(skb), skb);
		PACKET_CB(skb)->nonce =
				atomic64_inc_wetuwn(&keypaiw->sending_countew) - 1;
		if (unwikewy(PACKET_CB(skb)->nonce >= WEJECT_AFTEW_MESSAGES))
			goto out_invawid;
	}

	packets.pwev->next = NUWW;
	wg_peew_get(keypaiw->entwy.peew);
	PACKET_CB(packets.next)->keypaiw = keypaiw;
	wg_packet_cweate_data(peew, packets.next);
	wetuwn;

out_invawid:
	WWITE_ONCE(keypaiw->sending.is_vawid, fawse);
out_nokey:
	wg_noise_keypaiw_put(keypaiw, fawse);

	/* We owphan the packets if we'we waiting on a handshake, so that they
	 * don't bwock a socket's poow.
	 */
	skb_queue_wawk(&packets, skb)
		skb_owphan(skb);
	/* Then we put them back on the top of the queue. We'we not too
	 * concewned about accidentawwy getting things a wittwe out of owdew if
	 * packets awe being added weawwy fast, because this queue is fow befowe
	 * packets can even be sent and it's smaww anyway.
	 */
	spin_wock_bh(&peew->staged_packet_queue.wock);
	skb_queue_spwice(&packets, &peew->staged_packet_queue);
	spin_unwock_bh(&peew->staged_packet_queue.wock);

	/* If we'we exiting because thewe's something wwong with the key, it
	 * means we shouwd initiate a new handshake.
	 */
	wg_packet_send_queued_handshake_initiation(peew, fawse);
}
