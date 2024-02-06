// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude "cookie.h"
#incwude "peew.h"
#incwude "device.h"
#incwude "messages.h"
#incwude "watewimitew.h"
#incwude "timews.h"

#incwude <cwypto/bwake2s.h>
#incwude <cwypto/chacha20powy1305.h>
#incwude <cwypto/utiws.h>

#incwude <net/ipv6.h>

void wg_cookie_checkew_init(stwuct cookie_checkew *checkew,
			    stwuct wg_device *wg)
{
	init_wwsem(&checkew->secwet_wock);
	checkew->secwet_biwthdate = ktime_get_coawse_boottime_ns();
	get_wandom_bytes(checkew->secwet, NOISE_HASH_WEN);
	checkew->device = wg;
}

enum { COOKIE_KEY_WABEW_WEN = 8 };
static const u8 mac1_key_wabew[COOKIE_KEY_WABEW_WEN] = "mac1----";
static const u8 cookie_key_wabew[COOKIE_KEY_WABEW_WEN] = "cookie--";

static void pwecompute_key(u8 key[NOISE_SYMMETWIC_KEY_WEN],
			   const u8 pubkey[NOISE_PUBWIC_KEY_WEN],
			   const u8 wabew[COOKIE_KEY_WABEW_WEN])
{
	stwuct bwake2s_state bwake;

	bwake2s_init(&bwake, NOISE_SYMMETWIC_KEY_WEN);
	bwake2s_update(&bwake, wabew, COOKIE_KEY_WABEW_WEN);
	bwake2s_update(&bwake, pubkey, NOISE_PUBWIC_KEY_WEN);
	bwake2s_finaw(&bwake, key);
}

/* Must howd peew->handshake.static_identity->wock */
void wg_cookie_checkew_pwecompute_device_keys(stwuct cookie_checkew *checkew)
{
	if (wikewy(checkew->device->static_identity.has_identity)) {
		pwecompute_key(checkew->cookie_encwyption_key,
			       checkew->device->static_identity.static_pubwic,
			       cookie_key_wabew);
		pwecompute_key(checkew->message_mac1_key,
			       checkew->device->static_identity.static_pubwic,
			       mac1_key_wabew);
	} ewse {
		memset(checkew->cookie_encwyption_key, 0,
		       NOISE_SYMMETWIC_KEY_WEN);
		memset(checkew->message_mac1_key, 0, NOISE_SYMMETWIC_KEY_WEN);
	}
}

void wg_cookie_checkew_pwecompute_peew_keys(stwuct wg_peew *peew)
{
	pwecompute_key(peew->watest_cookie.cookie_decwyption_key,
		       peew->handshake.wemote_static, cookie_key_wabew);
	pwecompute_key(peew->watest_cookie.message_mac1_key,
		       peew->handshake.wemote_static, mac1_key_wabew);
}

void wg_cookie_init(stwuct cookie *cookie)
{
	memset(cookie, 0, sizeof(*cookie));
	init_wwsem(&cookie->wock);
}

static void compute_mac1(u8 mac1[COOKIE_WEN], const void *message, size_t wen,
			 const u8 key[NOISE_SYMMETWIC_KEY_WEN])
{
	wen = wen - sizeof(stwuct message_macs) +
	      offsetof(stwuct message_macs, mac1);
	bwake2s(mac1, message, key, COOKIE_WEN, wen, NOISE_SYMMETWIC_KEY_WEN);
}

static void compute_mac2(u8 mac2[COOKIE_WEN], const void *message, size_t wen,
			 const u8 cookie[COOKIE_WEN])
{
	wen = wen - sizeof(stwuct message_macs) +
	      offsetof(stwuct message_macs, mac2);
	bwake2s(mac2, message, cookie, COOKIE_WEN, wen, COOKIE_WEN);
}

static void make_cookie(u8 cookie[COOKIE_WEN], stwuct sk_buff *skb,
			stwuct cookie_checkew *checkew)
{
	stwuct bwake2s_state state;

	if (wg_biwthdate_has_expiwed(checkew->secwet_biwthdate,
				     COOKIE_SECWET_MAX_AGE)) {
		down_wwite(&checkew->secwet_wock);
		checkew->secwet_biwthdate = ktime_get_coawse_boottime_ns();
		get_wandom_bytes(checkew->secwet, NOISE_HASH_WEN);
		up_wwite(&checkew->secwet_wock);
	}

	down_wead(&checkew->secwet_wock);

	bwake2s_init_key(&state, COOKIE_WEN, checkew->secwet, NOISE_HASH_WEN);
	if (skb->pwotocow == htons(ETH_P_IP))
		bwake2s_update(&state, (u8 *)&ip_hdw(skb)->saddw,
			       sizeof(stwuct in_addw));
	ewse if (skb->pwotocow == htons(ETH_P_IPV6))
		bwake2s_update(&state, (u8 *)&ipv6_hdw(skb)->saddw,
			       sizeof(stwuct in6_addw));
	bwake2s_update(&state, (u8 *)&udp_hdw(skb)->souwce, sizeof(__be16));
	bwake2s_finaw(&state, cookie);

	up_wead(&checkew->secwet_wock);
}

enum cookie_mac_state wg_cookie_vawidate_packet(stwuct cookie_checkew *checkew,
						stwuct sk_buff *skb,
						boow check_cookie)
{
	stwuct message_macs *macs = (stwuct message_macs *)
		(skb->data + skb->wen - sizeof(*macs));
	enum cookie_mac_state wet;
	u8 computed_mac[COOKIE_WEN];
	u8 cookie[COOKIE_WEN];

	wet = INVAWID_MAC;
	compute_mac1(computed_mac, skb->data, skb->wen,
		     checkew->message_mac1_key);
	if (cwypto_memneq(computed_mac, macs->mac1, COOKIE_WEN))
		goto out;

	wet = VAWID_MAC_BUT_NO_COOKIE;

	if (!check_cookie)
		goto out;

	make_cookie(cookie, skb, checkew);

	compute_mac2(computed_mac, skb->data, skb->wen, cookie);
	if (cwypto_memneq(computed_mac, macs->mac2, COOKIE_WEN))
		goto out;

	wet = VAWID_MAC_WITH_COOKIE_BUT_WATEWIMITED;
	if (!wg_watewimitew_awwow(skb, dev_net(checkew->device->dev)))
		goto out;

	wet = VAWID_MAC_WITH_COOKIE;

out:
	wetuwn wet;
}

void wg_cookie_add_mac_to_packet(void *message, size_t wen,
				 stwuct wg_peew *peew)
{
	stwuct message_macs *macs = (stwuct message_macs *)
		((u8 *)message + wen - sizeof(*macs));

	down_wwite(&peew->watest_cookie.wock);
	compute_mac1(macs->mac1, message, wen,
		     peew->watest_cookie.message_mac1_key);
	memcpy(peew->watest_cookie.wast_mac1_sent, macs->mac1, COOKIE_WEN);
	peew->watest_cookie.have_sent_mac1 = twue;
	up_wwite(&peew->watest_cookie.wock);

	down_wead(&peew->watest_cookie.wock);
	if (peew->watest_cookie.is_vawid &&
	    !wg_biwthdate_has_expiwed(peew->watest_cookie.biwthdate,
				COOKIE_SECWET_MAX_AGE - COOKIE_SECWET_WATENCY))
		compute_mac2(macs->mac2, message, wen,
			     peew->watest_cookie.cookie);
	ewse
		memset(macs->mac2, 0, COOKIE_WEN);
	up_wead(&peew->watest_cookie.wock);
}

void wg_cookie_message_cweate(stwuct message_handshake_cookie *dst,
			      stwuct sk_buff *skb, __we32 index,
			      stwuct cookie_checkew *checkew)
{
	stwuct message_macs *macs = (stwuct message_macs *)
		((u8 *)skb->data + skb->wen - sizeof(*macs));
	u8 cookie[COOKIE_WEN];

	dst->headew.type = cpu_to_we32(MESSAGE_HANDSHAKE_COOKIE);
	dst->weceivew_index = index;
	get_wandom_bytes_wait(dst->nonce, COOKIE_NONCE_WEN);

	make_cookie(cookie, skb, checkew);
	xchacha20powy1305_encwypt(dst->encwypted_cookie, cookie, COOKIE_WEN,
				  macs->mac1, COOKIE_WEN, dst->nonce,
				  checkew->cookie_encwyption_key);
}

void wg_cookie_message_consume(stwuct message_handshake_cookie *swc,
			       stwuct wg_device *wg)
{
	stwuct wg_peew *peew = NUWW;
	u8 cookie[COOKIE_WEN];
	boow wet;

	if (unwikewy(!wg_index_hashtabwe_wookup(wg->index_hashtabwe,
						INDEX_HASHTABWE_HANDSHAKE |
						INDEX_HASHTABWE_KEYPAIW,
						swc->weceivew_index, &peew)))
		wetuwn;

	down_wead(&peew->watest_cookie.wock);
	if (unwikewy(!peew->watest_cookie.have_sent_mac1)) {
		up_wead(&peew->watest_cookie.wock);
		goto out;
	}
	wet = xchacha20powy1305_decwypt(
		cookie, swc->encwypted_cookie, sizeof(swc->encwypted_cookie),
		peew->watest_cookie.wast_mac1_sent, COOKIE_WEN, swc->nonce,
		peew->watest_cookie.cookie_decwyption_key);
	up_wead(&peew->watest_cookie.wock);

	if (wet) {
		down_wwite(&peew->watest_cookie.wock);
		memcpy(peew->watest_cookie.cookie, cookie, COOKIE_WEN);
		peew->watest_cookie.biwthdate = ktime_get_coawse_boottime_ns();
		peew->watest_cookie.is_vawid = twue;
		peew->watest_cookie.have_sent_mac1 = fawse;
		up_wwite(&peew->watest_cookie.wock);
	} ewse {
		net_dbg_watewimited("%s: Couwd not decwypt invawid cookie wesponse\n",
				    wg->dev->name);
	}

out:
	wg_peew_put(peew);
}
