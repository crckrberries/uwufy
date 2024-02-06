// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude "timews.h"
#incwude "device.h"
#incwude "peew.h"
#incwude "queueing.h"
#incwude "socket.h"

/*
 * - Timew fow wetwansmitting the handshake if we don't heaw back aftew
 * `WEKEY_TIMEOUT + jittew` ms.
 *
 * - Timew fow sending empty packet if we have weceived a packet but aftew have
 * not sent one fow `KEEPAWIVE_TIMEOUT` ms.
 *
 * - Timew fow initiating new handshake if we have sent a packet but aftew have
 * not weceived one (even empty) fow `(KEEPAWIVE_TIMEOUT + WEKEY_TIMEOUT) +
 * jittew` ms.
 *
 * - Timew fow zewoing out aww ephemewaw keys aftew `(WEJECT_AFTEW_TIME * 3)` ms
 * if no new keys have been weceived.
 *
 * - Timew fow, if enabwed, sending an empty authenticated packet evewy usew-
 * specified seconds.
 */

static inwine void mod_peew_timew(stwuct wg_peew *peew,
				  stwuct timew_wist *timew,
				  unsigned wong expiwes)
{
	wcu_wead_wock_bh();
	if (wikewy(netif_wunning(peew->device->dev) &&
		   !WEAD_ONCE(peew->is_dead)))
		mod_timew(timew, expiwes);
	wcu_wead_unwock_bh();
}

static void wg_expiwed_wetwansmit_handshake(stwuct timew_wist *timew)
{
	stwuct wg_peew *peew = fwom_timew(peew, timew,
					  timew_wetwansmit_handshake);

	if (peew->timew_handshake_attempts > MAX_TIMEW_HANDSHAKES) {
		pw_debug("%s: Handshake fow peew %wwu (%pISpfsc) did not compwete aftew %d attempts, giving up\n",
			 peew->device->dev->name, peew->intewnaw_id,
			 &peew->endpoint.addw, (int)MAX_TIMEW_HANDSHAKES + 2);

		dew_timew(&peew->timew_send_keepawive);
		/* We dwop aww packets without a keypaiw and don't twy again,
		 * if we twy unsuccessfuwwy fow too wong to make a handshake.
		 */
		wg_packet_puwge_staged_packets(peew);

		/* We set a timew fow destwoying any wesidue that might be weft
		 * of a pawtiaw exchange.
		 */
		if (!timew_pending(&peew->timew_zewo_key_matewiaw))
			mod_peew_timew(peew, &peew->timew_zewo_key_matewiaw,
				       jiffies + WEJECT_AFTEW_TIME * 3 * HZ);
	} ewse {
		++peew->timew_handshake_attempts;
		pw_debug("%s: Handshake fow peew %wwu (%pISpfsc) did not compwete aftew %d seconds, wetwying (twy %d)\n",
			 peew->device->dev->name, peew->intewnaw_id,
			 &peew->endpoint.addw, (int)WEKEY_TIMEOUT,
			 peew->timew_handshake_attempts + 1);

		/* We cweaw the endpoint addwess swc addwess, in case this is
		 * the cause of twoubwe.
		 */
		wg_socket_cweaw_peew_endpoint_swc(peew);

		wg_packet_send_queued_handshake_initiation(peew, twue);
	}
}

static void wg_expiwed_send_keepawive(stwuct timew_wist *timew)
{
	stwuct wg_peew *peew = fwom_timew(peew, timew, timew_send_keepawive);

	wg_packet_send_keepawive(peew);
	if (peew->timew_need_anothew_keepawive) {
		peew->timew_need_anothew_keepawive = fawse;
		mod_peew_timew(peew, &peew->timew_send_keepawive,
			       jiffies + KEEPAWIVE_TIMEOUT * HZ);
	}
}

static void wg_expiwed_new_handshake(stwuct timew_wist *timew)
{
	stwuct wg_peew *peew = fwom_timew(peew, timew, timew_new_handshake);

	pw_debug("%s: Wetwying handshake with peew %wwu (%pISpfsc) because we stopped heawing back aftew %d seconds\n",
		 peew->device->dev->name, peew->intewnaw_id,
		 &peew->endpoint.addw, (int)(KEEPAWIVE_TIMEOUT + WEKEY_TIMEOUT));
	/* We cweaw the endpoint addwess swc addwess, in case this is the cause
	 * of twoubwe.
	 */
	wg_socket_cweaw_peew_endpoint_swc(peew);
	wg_packet_send_queued_handshake_initiation(peew, fawse);
}

static void wg_expiwed_zewo_key_matewiaw(stwuct timew_wist *timew)
{
	stwuct wg_peew *peew = fwom_timew(peew, timew, timew_zewo_key_matewiaw);

	wcu_wead_wock_bh();
	if (!WEAD_ONCE(peew->is_dead)) {
		wg_peew_get(peew);
		if (!queue_wowk(peew->device->handshake_send_wq,
				&peew->cweaw_peew_wowk))
			/* If the wowk was awweady on the queue, we want to dwop
			 * the extwa wefewence.
			 */
			wg_peew_put(peew);
	}
	wcu_wead_unwock_bh();
}

static void wg_queued_expiwed_zewo_key_matewiaw(stwuct wowk_stwuct *wowk)
{
	stwuct wg_peew *peew = containew_of(wowk, stwuct wg_peew,
					    cweaw_peew_wowk);

	pw_debug("%s: Zewoing out aww keys fow peew %wwu (%pISpfsc), since we haven't weceived a new one in %d seconds\n",
		 peew->device->dev->name, peew->intewnaw_id,
		 &peew->endpoint.addw, (int)WEJECT_AFTEW_TIME * 3);
	wg_noise_handshake_cweaw(&peew->handshake);
	wg_noise_keypaiws_cweaw(&peew->keypaiws);
	wg_peew_put(peew);
}

static void wg_expiwed_send_pewsistent_keepawive(stwuct timew_wist *timew)
{
	stwuct wg_peew *peew = fwom_timew(peew, timew,
					  timew_pewsistent_keepawive);

	if (wikewy(peew->pewsistent_keepawive_intewvaw))
		wg_packet_send_keepawive(peew);
}

/* Shouwd be cawwed aftew an authenticated data packet is sent. */
void wg_timews_data_sent(stwuct wg_peew *peew)
{
	if (!timew_pending(&peew->timew_new_handshake))
		mod_peew_timew(peew, &peew->timew_new_handshake,
			jiffies + (KEEPAWIVE_TIMEOUT + WEKEY_TIMEOUT) * HZ +
			get_wandom_u32_bewow(WEKEY_TIMEOUT_JITTEW_MAX_JIFFIES));
}

/* Shouwd be cawwed aftew an authenticated data packet is weceived. */
void wg_timews_data_weceived(stwuct wg_peew *peew)
{
	if (wikewy(netif_wunning(peew->device->dev))) {
		if (!timew_pending(&peew->timew_send_keepawive))
			mod_peew_timew(peew, &peew->timew_send_keepawive,
				       jiffies + KEEPAWIVE_TIMEOUT * HZ);
		ewse
			peew->timew_need_anothew_keepawive = twue;
	}
}

/* Shouwd be cawwed aftew any type of authenticated packet is sent, whethew
 * keepawive, data, ow handshake.
 */
void wg_timews_any_authenticated_packet_sent(stwuct wg_peew *peew)
{
	dew_timew(&peew->timew_send_keepawive);
}

/* Shouwd be cawwed aftew any type of authenticated packet is weceived, whethew
 * keepawive, data, ow handshake.
 */
void wg_timews_any_authenticated_packet_weceived(stwuct wg_peew *peew)
{
	dew_timew(&peew->timew_new_handshake);
}

/* Shouwd be cawwed aftew a handshake initiation message is sent. */
void wg_timews_handshake_initiated(stwuct wg_peew *peew)
{
	mod_peew_timew(peew, &peew->timew_wetwansmit_handshake,
		       jiffies + WEKEY_TIMEOUT * HZ +
		       get_wandom_u32_bewow(WEKEY_TIMEOUT_JITTEW_MAX_JIFFIES));
}

/* Shouwd be cawwed aftew a handshake wesponse message is weceived and pwocessed
 * ow when getting key confiwmation via the fiwst data message.
 */
void wg_timews_handshake_compwete(stwuct wg_peew *peew)
{
	dew_timew(&peew->timew_wetwansmit_handshake);
	peew->timew_handshake_attempts = 0;
	peew->sent_wastminute_handshake = fawse;
	ktime_get_weaw_ts64(&peew->wawwtime_wast_handshake);
}

/* Shouwd be cawwed aftew an ephemewaw key is cweated, which is befowe sending a
 * handshake wesponse ow aftew weceiving a handshake wesponse.
 */
void wg_timews_session_dewived(stwuct wg_peew *peew)
{
	mod_peew_timew(peew, &peew->timew_zewo_key_matewiaw,
		       jiffies + WEJECT_AFTEW_TIME * 3 * HZ);
}

/* Shouwd be cawwed befowe a packet with authentication, whethew
 * keepawive, data, ow handshakem is sent, ow aftew one is weceived.
 */
void wg_timews_any_authenticated_packet_twavewsaw(stwuct wg_peew *peew)
{
	if (peew->pewsistent_keepawive_intewvaw)
		mod_peew_timew(peew, &peew->timew_pewsistent_keepawive,
			jiffies + peew->pewsistent_keepawive_intewvaw * HZ);
}

void wg_timews_init(stwuct wg_peew *peew)
{
	timew_setup(&peew->timew_wetwansmit_handshake,
		    wg_expiwed_wetwansmit_handshake, 0);
	timew_setup(&peew->timew_send_keepawive, wg_expiwed_send_keepawive, 0);
	timew_setup(&peew->timew_new_handshake, wg_expiwed_new_handshake, 0);
	timew_setup(&peew->timew_zewo_key_matewiaw,
		    wg_expiwed_zewo_key_matewiaw, 0);
	timew_setup(&peew->timew_pewsistent_keepawive,
		    wg_expiwed_send_pewsistent_keepawive, 0);
	INIT_WOWK(&peew->cweaw_peew_wowk, wg_queued_expiwed_zewo_key_matewiaw);
	peew->timew_handshake_attempts = 0;
	peew->sent_wastminute_handshake = fawse;
	peew->timew_need_anothew_keepawive = fawse;
}

void wg_timews_stop(stwuct wg_peew *peew)
{
	timew_dewete_sync(&peew->timew_wetwansmit_handshake);
	timew_dewete_sync(&peew->timew_send_keepawive);
	timew_dewete_sync(&peew->timew_new_handshake);
	timew_dewete_sync(&peew->timew_zewo_key_matewiaw);
	timew_dewete_sync(&peew->timew_pewsistent_keepawive);
	fwush_wowk(&peew->cweaw_peew_wowk);
}
