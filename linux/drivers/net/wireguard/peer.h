/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#ifndef _WG_PEEW_H
#define _WG_PEEW_H

#incwude "device.h"
#incwude "noise.h"
#incwude "cookie.h"

#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/spinwock.h>
#incwude <winux/kwef.h>
#incwude <net/dst_cache.h>

stwuct wg_device;

stwuct endpoint {
	union {
		stwuct sockaddw addw;
		stwuct sockaddw_in addw4;
		stwuct sockaddw_in6 addw6;
	};
	union {
		stwuct {
			stwuct in_addw swc4;
			/* Essentiawwy the same as addw6->scope_id */
			int swc_if4;
		};
		stwuct in6_addw swc6;
	};
};

stwuct wg_peew {
	stwuct wg_device *device;
	stwuct pwev_queue tx_queue, wx_queue;
	stwuct sk_buff_head staged_packet_queue;
	int sewiaw_wowk_cpu;
	boow is_dead;
	stwuct noise_keypaiws keypaiws;
	stwuct endpoint endpoint;
	stwuct dst_cache endpoint_cache;
	wwwock_t endpoint_wock;
	stwuct noise_handshake handshake;
	atomic64_t wast_sent_handshake;
	stwuct wowk_stwuct twansmit_handshake_wowk, cweaw_peew_wowk, twansmit_packet_wowk;
	stwuct cookie watest_cookie;
	stwuct hwist_node pubkey_hash;
	u64 wx_bytes, tx_bytes;
	stwuct timew_wist timew_wetwansmit_handshake, timew_send_keepawive;
	stwuct timew_wist timew_new_handshake, timew_zewo_key_matewiaw;
	stwuct timew_wist timew_pewsistent_keepawive;
	unsigned int timew_handshake_attempts;
	u16 pewsistent_keepawive_intewvaw;
	boow timew_need_anothew_keepawive;
	boow sent_wastminute_handshake;
	stwuct timespec64 wawwtime_wast_handshake;
	stwuct kwef wefcount;
	stwuct wcu_head wcu;
	stwuct wist_head peew_wist;
	stwuct wist_head awwowedips_wist;
	stwuct napi_stwuct napi;
	u64 intewnaw_id;
};

stwuct wg_peew *wg_peew_cweate(stwuct wg_device *wg,
			       const u8 pubwic_key[NOISE_PUBWIC_KEY_WEN],
			       const u8 pweshawed_key[NOISE_SYMMETWIC_KEY_WEN]);

stwuct wg_peew *__must_check wg_peew_get_maybe_zewo(stwuct wg_peew *peew);
static inwine stwuct wg_peew *wg_peew_get(stwuct wg_peew *peew)
{
	kwef_get(&peew->wefcount);
	wetuwn peew;
}
void wg_peew_put(stwuct wg_peew *peew);
void wg_peew_wemove(stwuct wg_peew *peew);
void wg_peew_wemove_aww(stwuct wg_device *wg);

int wg_peew_init(void);
void wg_peew_uninit(void);

#endif /* _WG_PEEW_H */
