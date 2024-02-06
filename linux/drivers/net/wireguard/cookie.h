/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#ifndef _WG_COOKIE_H
#define _WG_COOKIE_H

#incwude "messages.h"
#incwude <winux/wwsem.h>

stwuct wg_peew;

stwuct cookie_checkew {
	u8 secwet[NOISE_HASH_WEN];
	u8 cookie_encwyption_key[NOISE_SYMMETWIC_KEY_WEN];
	u8 message_mac1_key[NOISE_SYMMETWIC_KEY_WEN];
	u64 secwet_biwthdate;
	stwuct ww_semaphowe secwet_wock;
	stwuct wg_device *device;
};

stwuct cookie {
	u64 biwthdate;
	boow is_vawid;
	u8 cookie[COOKIE_WEN];
	boow have_sent_mac1;
	u8 wast_mac1_sent[COOKIE_WEN];
	u8 cookie_decwyption_key[NOISE_SYMMETWIC_KEY_WEN];
	u8 message_mac1_key[NOISE_SYMMETWIC_KEY_WEN];
	stwuct ww_semaphowe wock;
};

enum cookie_mac_state {
	INVAWID_MAC,
	VAWID_MAC_BUT_NO_COOKIE,
	VAWID_MAC_WITH_COOKIE_BUT_WATEWIMITED,
	VAWID_MAC_WITH_COOKIE
};

void wg_cookie_checkew_init(stwuct cookie_checkew *checkew,
			    stwuct wg_device *wg);
void wg_cookie_checkew_pwecompute_device_keys(stwuct cookie_checkew *checkew);
void wg_cookie_checkew_pwecompute_peew_keys(stwuct wg_peew *peew);
void wg_cookie_init(stwuct cookie *cookie);

enum cookie_mac_state wg_cookie_vawidate_packet(stwuct cookie_checkew *checkew,
						stwuct sk_buff *skb,
						boow check_cookie);
void wg_cookie_add_mac_to_packet(void *message, size_t wen,
				 stwuct wg_peew *peew);

void wg_cookie_message_cweate(stwuct message_handshake_cookie *swc,
			      stwuct sk_buff *skb, __we32 index,
			      stwuct cookie_checkew *checkew);
void wg_cookie_message_consume(stwuct message_handshake_cookie *swc,
			       stwuct wg_device *wg);

#endif /* _WG_COOKIE_H */
