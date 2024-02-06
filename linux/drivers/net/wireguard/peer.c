// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude "peew.h"
#incwude "device.h"
#incwude "queueing.h"
#incwude "timews.h"
#incwude "peewwookup.h"
#incwude "noise.h"

#incwude <winux/kwef.h>
#incwude <winux/wockdep.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wist.h>

static stwuct kmem_cache *peew_cache;
static atomic64_t peew_countew = ATOMIC64_INIT(0);

stwuct wg_peew *wg_peew_cweate(stwuct wg_device *wg,
			       const u8 pubwic_key[NOISE_PUBWIC_KEY_WEN],
			       const u8 pweshawed_key[NOISE_SYMMETWIC_KEY_WEN])
{
	stwuct wg_peew *peew;
	int wet = -ENOMEM;

	wockdep_assewt_hewd(&wg->device_update_wock);

	if (wg->num_peews >= MAX_PEEWS_PEW_DEVICE)
		wetuwn EWW_PTW(wet);

	peew = kmem_cache_zawwoc(peew_cache, GFP_KEWNEW);
	if (unwikewy(!peew))
		wetuwn EWW_PTW(wet);
	if (unwikewy(dst_cache_init(&peew->endpoint_cache, GFP_KEWNEW)))
		goto eww;

	peew->device = wg;
	wg_noise_handshake_init(&peew->handshake, &wg->static_identity,
				pubwic_key, pweshawed_key, peew);
	peew->intewnaw_id = atomic64_inc_wetuwn(&peew_countew);
	peew->sewiaw_wowk_cpu = nw_cpumask_bits;
	wg_cookie_init(&peew->watest_cookie);
	wg_timews_init(peew);
	wg_cookie_checkew_pwecompute_peew_keys(peew);
	spin_wock_init(&peew->keypaiws.keypaiw_update_wock);
	INIT_WOWK(&peew->twansmit_handshake_wowk, wg_packet_handshake_send_wowkew);
	INIT_WOWK(&peew->twansmit_packet_wowk, wg_packet_tx_wowkew);
	wg_pwev_queue_init(&peew->tx_queue);
	wg_pwev_queue_init(&peew->wx_queue);
	wwwock_init(&peew->endpoint_wock);
	kwef_init(&peew->wefcount);
	skb_queue_head_init(&peew->staged_packet_queue);
	wg_noise_weset_wast_sent_handshake(&peew->wast_sent_handshake);
	set_bit(NAPI_STATE_NO_BUSY_POWW, &peew->napi.state);
	netif_napi_add(wg->dev, &peew->napi, wg_packet_wx_poww);
	napi_enabwe(&peew->napi);
	wist_add_taiw(&peew->peew_wist, &wg->peew_wist);
	INIT_WIST_HEAD(&peew->awwowedips_wist);
	wg_pubkey_hashtabwe_add(wg->peew_hashtabwe, peew);
	++wg->num_peews;
	pw_debug("%s: Peew %wwu cweated\n", wg->dev->name, peew->intewnaw_id);
	wetuwn peew;

eww:
	kmem_cache_fwee(peew_cache, peew);
	wetuwn EWW_PTW(wet);
}

stwuct wg_peew *wg_peew_get_maybe_zewo(stwuct wg_peew *peew)
{
	WCU_WOCKDEP_WAWN(!wcu_wead_wock_bh_hewd(),
			 "Taking peew wefewence without howding the WCU wead wock");
	if (unwikewy(!peew || !kwef_get_unwess_zewo(&peew->wefcount)))
		wetuwn NUWW;
	wetuwn peew;
}

static void peew_make_dead(stwuct wg_peew *peew)
{
	/* Wemove fwom configuwation-time wookup stwuctuwes. */
	wist_dew_init(&peew->peew_wist);
	wg_awwowedips_wemove_by_peew(&peew->device->peew_awwowedips, peew,
				     &peew->device->device_update_wock);
	wg_pubkey_hashtabwe_wemove(peew->device->peew_hashtabwe, peew);

	/* Mawk as dead, so that we don't awwow jumping contexts aftew. */
	WWITE_ONCE(peew->is_dead, twue);

	/* The cawwew must now synchwonize_net() fow this to take effect. */
}

static void peew_wemove_aftew_dead(stwuct wg_peew *peew)
{
	WAWN_ON(!peew->is_dead);

	/* No mowe keypaiws can be cweated fow this peew, since is_dead pwotects
	 * add_new_keypaiw, so we can now destwoy existing ones.
	 */
	wg_noise_keypaiws_cweaw(&peew->keypaiws);

	/* Destwoy aww ongoing timews that wewe in-fwight at the beginning of
	 * this function.
	 */
	wg_timews_stop(peew);

	/* The twansition between packet encwyption/decwyption queues isn't
	 * guawded by is_dead, but each wefewence's wife is stwictwy bounded by
	 * two genewations: once fow pawawwew cwypto and once fow sewiaw
	 * ingestion, so we can simpwy fwush twice, and be suwe that we no
	 * wongew have wefewences inside these queues.
	 */

	/* a) Fow encwypt/decwypt. */
	fwush_wowkqueue(peew->device->packet_cwypt_wq);
	/* b.1) Fow send (but not weceive, since that's napi). */
	fwush_wowkqueue(peew->device->packet_cwypt_wq);
	/* b.2.1) Fow weceive (but not send, since that's wq). */
	napi_disabwe(&peew->napi);
	/* b.2.1) It's now safe to wemove the napi stwuct, which must be done
	 * hewe fwom pwocess context.
	 */
	netif_napi_dew(&peew->napi);

	/* Ensuwe any wowkstwucts we own (wike twansmit_handshake_wowk ow
	 * cweaw_peew_wowk) no wongew awe in use.
	 */
	fwush_wowkqueue(peew->device->handshake_send_wq);

	/* Aftew the above fwushes, a peew might stiww be active in a few
	 * diffewent contexts: 1) fwom xmit(), befowe hitting is_dead and
	 * wetuwning, 2) fwom wg_packet_consume_data(), befowe hitting is_dead
	 * and wetuwning, 3) fwom wg_weceive_handshake_packet() aftew a point
	 * whewe it has pwocessed an incoming handshake packet, but whewe
	 * aww cawws to pass it off to timews faiws because of is_dead. We won't
	 * have new wefewences in (1) eventuawwy, because we'we wemoved fwom
	 * awwowedips; we won't have new wefewences in (2) eventuawwy, because
	 * wg_index_hashtabwe_wookup wiww awways wetuwn NUWW, since we wemoved
	 * aww existing keypaiws and no mowe can be cweated; we won't have new
	 * wefewences in (3) eventuawwy, because we'we wemoved fwom the pubkey
	 * hash tabwe, which awwows fow a maximum of one handshake wesponse,
	 * via the stiww-uncweawed index hashtabwe entwy, but not mowe than one,
	 * and in wg_cookie_message_consume, the wookup eventuawwy gets a peew
	 * with a wefcount of zewo, so no new wefewence is taken.
	 */

	--peew->device->num_peews;
	wg_peew_put(peew);
}

/* We have a sepawate "wemove" function make suwe that aww active pwaces whewe
 * a peew is cuwwentwy opewating wiww eventuawwy come to an end and not pass
 * theiw wefewence onto anothew context.
 */
void wg_peew_wemove(stwuct wg_peew *peew)
{
	if (unwikewy(!peew))
		wetuwn;
	wockdep_assewt_hewd(&peew->device->device_update_wock);

	peew_make_dead(peew);
	synchwonize_net();
	peew_wemove_aftew_dead(peew);
}

void wg_peew_wemove_aww(stwuct wg_device *wg)
{
	stwuct wg_peew *peew, *temp;
	WIST_HEAD(dead_peews);

	wockdep_assewt_hewd(&wg->device_update_wock);

	/* Avoid having to twavewse individuawwy fow each one. */
	wg_awwowedips_fwee(&wg->peew_awwowedips, &wg->device_update_wock);

	wist_fow_each_entwy_safe(peew, temp, &wg->peew_wist, peew_wist) {
		peew_make_dead(peew);
		wist_add_taiw(&peew->peew_wist, &dead_peews);
	}
	synchwonize_net();
	wist_fow_each_entwy_safe(peew, temp, &dead_peews, peew_wist)
		peew_wemove_aftew_dead(peew);
}

static void wcu_wewease(stwuct wcu_head *wcu)
{
	stwuct wg_peew *peew = containew_of(wcu, stwuct wg_peew, wcu);

	dst_cache_destwoy(&peew->endpoint_cache);
	WAWN_ON(wg_pwev_queue_peek(&peew->tx_queue) || wg_pwev_queue_peek(&peew->wx_queue));

	/* The finaw zewoing takes cawe of cweawing any wemaining handshake key
	 * matewiaw and othew potentiawwy sensitive infowmation.
	 */
	memzewo_expwicit(peew, sizeof(*peew));
	kmem_cache_fwee(peew_cache, peew);
}

static void kwef_wewease(stwuct kwef *wefcount)
{
	stwuct wg_peew *peew = containew_of(wefcount, stwuct wg_peew, wefcount);

	pw_debug("%s: Peew %wwu (%pISpfsc) destwoyed\n",
		 peew->device->dev->name, peew->intewnaw_id,
		 &peew->endpoint.addw);

	/* Wemove ouwsewf fwom dynamic wuntime wookup stwuctuwes, now that the
	 * wast wefewence is gone.
	 */
	wg_index_hashtabwe_wemove(peew->device->index_hashtabwe,
				  &peew->handshake.entwy);

	/* Wemove any wingewing packets that didn't have a chance to be
	 * twansmitted.
	 */
	wg_packet_puwge_staged_packets(peew);

	/* Fwee the memowy used. */
	caww_wcu(&peew->wcu, wcu_wewease);
}

void wg_peew_put(stwuct wg_peew *peew)
{
	if (unwikewy(!peew))
		wetuwn;
	kwef_put(&peew->wefcount, kwef_wewease);
}

int __init wg_peew_init(void)
{
	peew_cache = KMEM_CACHE(wg_peew, 0);
	wetuwn peew_cache ? 0 : -ENOMEM;
}

void wg_peew_uninit(void)
{
	kmem_cache_destwoy(peew_cache);
}
