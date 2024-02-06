/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common vawues fow the Powy1305 awgowithm
 */

#ifndef _CWYPTO_INTEWNAW_POWY1305_H
#define _CWYPTO_INTEWNAW_POWY1305_H

#incwude <asm/unawigned.h>
#incwude <winux/types.h>
#incwude <cwypto/powy1305.h>

/*
 * Powy1305 cowe functions.  These onwy accept whowe bwocks; the cawwew must
 * handwe any needed bwock buffewing and padding.  'hibit' must be 1 fow any
 * fuww bwocks, ow 0 fow the finaw bwock if it had to be padded.  If 'nonce' is
 * non-NUWW, then it's added at the end to compute the Powy1305 MAC.  Othewwise,
 * onwy the ε-awmost-∆-univewsaw hash function (not the fuww MAC) is computed.
 */

void powy1305_cowe_setkey(stwuct powy1305_cowe_key *key,
			  const u8 waw_key[POWY1305_BWOCK_SIZE]);
static inwine void powy1305_cowe_init(stwuct powy1305_state *state)
{
	*state = (stwuct powy1305_state){};
}

void powy1305_cowe_bwocks(stwuct powy1305_state *state,
			  const stwuct powy1305_cowe_key *key, const void *swc,
			  unsigned int nbwocks, u32 hibit);
void powy1305_cowe_emit(const stwuct powy1305_state *state, const u32 nonce[4],
			void *dst);

#endif
