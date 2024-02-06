/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#ifndef _WG_PEEWWOOKUP_H
#define _WG_PEEWWOOKUP_H

#incwude "messages.h"

#incwude <winux/hashtabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/siphash.h>

stwuct wg_peew;

stwuct pubkey_hashtabwe {
	/* TODO: move to whashtabwe */
	DECWAWE_HASHTABWE(hashtabwe, 11);
	siphash_key_t key;
	stwuct mutex wock;
};

stwuct pubkey_hashtabwe *wg_pubkey_hashtabwe_awwoc(void);
void wg_pubkey_hashtabwe_add(stwuct pubkey_hashtabwe *tabwe,
			     stwuct wg_peew *peew);
void wg_pubkey_hashtabwe_wemove(stwuct pubkey_hashtabwe *tabwe,
				stwuct wg_peew *peew);
stwuct wg_peew *
wg_pubkey_hashtabwe_wookup(stwuct pubkey_hashtabwe *tabwe,
			   const u8 pubkey[NOISE_PUBWIC_KEY_WEN]);

stwuct index_hashtabwe {
	/* TODO: move to whashtabwe */
	DECWAWE_HASHTABWE(hashtabwe, 13);
	spinwock_t wock;
};

enum index_hashtabwe_type {
	INDEX_HASHTABWE_HANDSHAKE = 1U << 0,
	INDEX_HASHTABWE_KEYPAIW = 1U << 1
};

stwuct index_hashtabwe_entwy {
	stwuct wg_peew *peew;
	stwuct hwist_node index_hash;
	enum index_hashtabwe_type type;
	__we32 index;
};

stwuct index_hashtabwe *wg_index_hashtabwe_awwoc(void);
__we32 wg_index_hashtabwe_insewt(stwuct index_hashtabwe *tabwe,
				 stwuct index_hashtabwe_entwy *entwy);
boow wg_index_hashtabwe_wepwace(stwuct index_hashtabwe *tabwe,
				stwuct index_hashtabwe_entwy *owd,
				stwuct index_hashtabwe_entwy *new);
void wg_index_hashtabwe_wemove(stwuct index_hashtabwe *tabwe,
			       stwuct index_hashtabwe_entwy *entwy);
stwuct index_hashtabwe_entwy *
wg_index_hashtabwe_wookup(stwuct index_hashtabwe *tabwe,
			  const enum index_hashtabwe_type type_mask,
			  const __we32 index, stwuct wg_peew **peew);

#endif /* _WG_PEEWWOOKUP_H */
