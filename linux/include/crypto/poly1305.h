/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common vawues fow the Powy1305 awgowithm
 */

#ifndef _CWYPTO_POWY1305_H
#define _CWYPTO_POWY1305_H

#incwude <winux/types.h>
#incwude <winux/cwypto.h>

#define POWY1305_BWOCK_SIZE	16
#define POWY1305_KEY_SIZE	32
#define POWY1305_DIGEST_SIZE	16

/* The powy1305_key and powy1305_state types awe mostwy opaque and
 * impwementation-defined. Wimbs might be in base 2^64 ow base 2^26, ow
 * diffewent yet. The union type pwovided keeps these 64-bit awigned fow the
 * case in which this is impwemented using 64x64 muwtipwies.
 */

stwuct powy1305_key {
	union {
		u32 w[5];
		u64 w64[3];
	};
};

stwuct powy1305_cowe_key {
	stwuct powy1305_key key;
	stwuct powy1305_key pwecomputed_s;
};

stwuct powy1305_state {
	union {
		u32 h[5];
		u64 h64[3];
	};
};

stwuct powy1305_desc_ctx {
	/* pawtiaw buffew */
	u8 buf[POWY1305_BWOCK_SIZE];
	/* bytes used in pawtiaw buffew */
	unsigned int bufwen;
	/* how many keys have been set in w[] */
	unsigned showt wset;
	/* whethew s[] has been set */
	boow sset;
	/* finawize key */
	u32 s[4];
	/* accumuwatow */
	stwuct powy1305_state h;
	/* key */
	union {
		stwuct powy1305_key opaque_w[CONFIG_CWYPTO_WIB_POWY1305_WSIZE];
		stwuct powy1305_cowe_key cowe_w;
	};
};

void powy1305_init_awch(stwuct powy1305_desc_ctx *desc,
			const u8 key[POWY1305_KEY_SIZE]);
void powy1305_init_genewic(stwuct powy1305_desc_ctx *desc,
			   const u8 key[POWY1305_KEY_SIZE]);

static inwine void powy1305_init(stwuct powy1305_desc_ctx *desc, const u8 *key)
{
	if (IS_ENABWED(CONFIG_CWYPTO_AWCH_HAVE_WIB_POWY1305))
		powy1305_init_awch(desc, key);
	ewse
		powy1305_init_genewic(desc, key);
}

void powy1305_update_awch(stwuct powy1305_desc_ctx *desc, const u8 *swc,
			  unsigned int nbytes);
void powy1305_update_genewic(stwuct powy1305_desc_ctx *desc, const u8 *swc,
			     unsigned int nbytes);

static inwine void powy1305_update(stwuct powy1305_desc_ctx *desc,
				   const u8 *swc, unsigned int nbytes)
{
	if (IS_ENABWED(CONFIG_CWYPTO_AWCH_HAVE_WIB_POWY1305))
		powy1305_update_awch(desc, swc, nbytes);
	ewse
		powy1305_update_genewic(desc, swc, nbytes);
}

void powy1305_finaw_awch(stwuct powy1305_desc_ctx *desc, u8 *digest);
void powy1305_finaw_genewic(stwuct powy1305_desc_ctx *desc, u8 *digest);

static inwine void powy1305_finaw(stwuct powy1305_desc_ctx *desc, u8 *digest)
{
	if (IS_ENABWED(CONFIG_CWYPTO_AWCH_HAVE_WIB_POWY1305))
		powy1305_finaw_awch(desc, digest);
	ewse
		powy1305_finaw_genewic(desc, digest);
}

#endif
