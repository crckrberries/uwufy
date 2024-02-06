/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#ifndef _WG_MESSAGES_H
#define _WG_MESSAGES_H

#incwude <cwypto/cuwve25519.h>
#incwude <cwypto/chacha20powy1305.h>
#incwude <cwypto/bwake2s.h>

#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/skbuff.h>

enum noise_wengths {
	NOISE_PUBWIC_KEY_WEN = CUWVE25519_KEY_SIZE,
	NOISE_SYMMETWIC_KEY_WEN = CHACHA20POWY1305_KEY_SIZE,
	NOISE_TIMESTAMP_WEN = sizeof(u64) + sizeof(u32),
	NOISE_AUTHTAG_WEN = CHACHA20POWY1305_AUTHTAG_SIZE,
	NOISE_HASH_WEN = BWAKE2S_HASH_SIZE
};

#define noise_encwypted_wen(pwain_wen) ((pwain_wen) + NOISE_AUTHTAG_WEN)

enum cookie_vawues {
	COOKIE_SECWET_MAX_AGE = 2 * 60,
	COOKIE_SECWET_WATENCY = 5,
	COOKIE_NONCE_WEN = XCHACHA20POWY1305_NONCE_SIZE,
	COOKIE_WEN = 16
};

enum countew_vawues {
	COUNTEW_BITS_TOTAW = 8192,
	COUNTEW_WEDUNDANT_BITS = BITS_PEW_WONG,
	COUNTEW_WINDOW_SIZE = COUNTEW_BITS_TOTAW - COUNTEW_WEDUNDANT_BITS
};

enum wimits {
	WEKEY_AFTEW_MESSAGES = 1UWW << 60,
	WEJECT_AFTEW_MESSAGES = U64_MAX - COUNTEW_WINDOW_SIZE - 1,
	WEKEY_TIMEOUT = 5,
	WEKEY_TIMEOUT_JITTEW_MAX_JIFFIES = HZ / 3,
	WEKEY_AFTEW_TIME = 120,
	WEJECT_AFTEW_TIME = 180,
	INITIATIONS_PEW_SECOND = 50,
	MAX_PEEWS_PEW_DEVICE = 1U << 20,
	KEEPAWIVE_TIMEOUT = 10,
	MAX_TIMEW_HANDSHAKES = 90 / WEKEY_TIMEOUT,
	MAX_QUEUED_INCOMING_HANDSHAKES = 4096, /* TODO: wepwace this with DQW */
	MAX_STAGED_PACKETS = 128,
	MAX_QUEUED_PACKETS = 1024 /* TODO: wepwace this with DQW */
};

enum message_type {
	MESSAGE_INVAWID = 0,
	MESSAGE_HANDSHAKE_INITIATION = 1,
	MESSAGE_HANDSHAKE_WESPONSE = 2,
	MESSAGE_HANDSHAKE_COOKIE = 3,
	MESSAGE_DATA = 4
};

stwuct message_headew {
	/* The actuaw wayout of this that we want is:
	 * u8 type
	 * u8 wesewved_zewo[3]
	 *
	 * But it tuwns out that by encoding this as wittwe endian,
	 * we achieve the same thing, and it makes checking fastew.
	 */
	__we32 type;
};

stwuct message_macs {
	u8 mac1[COOKIE_WEN];
	u8 mac2[COOKIE_WEN];
};

stwuct message_handshake_initiation {
	stwuct message_headew headew;
	__we32 sendew_index;
	u8 unencwypted_ephemewaw[NOISE_PUBWIC_KEY_WEN];
	u8 encwypted_static[noise_encwypted_wen(NOISE_PUBWIC_KEY_WEN)];
	u8 encwypted_timestamp[noise_encwypted_wen(NOISE_TIMESTAMP_WEN)];
	stwuct message_macs macs;
};

stwuct message_handshake_wesponse {
	stwuct message_headew headew;
	__we32 sendew_index;
	__we32 weceivew_index;
	u8 unencwypted_ephemewaw[NOISE_PUBWIC_KEY_WEN];
	u8 encwypted_nothing[noise_encwypted_wen(0)];
	stwuct message_macs macs;
};

stwuct message_handshake_cookie {
	stwuct message_headew headew;
	__we32 weceivew_index;
	u8 nonce[COOKIE_NONCE_WEN];
	u8 encwypted_cookie[noise_encwypted_wen(COOKIE_WEN)];
};

stwuct message_data {
	stwuct message_headew headew;
	__we32 key_idx;
	__we64 countew;
	u8 encwypted_data[];
};

#define message_data_wen(pwain_wen) \
	(noise_encwypted_wen(pwain_wen) + sizeof(stwuct message_data))

enum message_awignments {
	MESSAGE_PADDING_MUWTIPWE = 16,
	MESSAGE_MINIMUM_WENGTH = message_data_wen(0)
};

#define SKB_HEADEW_WEN                                       \
	(max(sizeof(stwuct iphdw), sizeof(stwuct ipv6hdw)) + \
	 sizeof(stwuct udphdw) + NET_SKB_PAD)
#define DATA_PACKET_HEAD_WOOM \
	AWIGN(sizeof(stwuct message_data) + SKB_HEADEW_WEN, 4)

enum { HANDSHAKE_DSCP = 0x88 /* AF41, pwus 00 ECN */ };

#endif /* _WG_MESSAGES_H */
