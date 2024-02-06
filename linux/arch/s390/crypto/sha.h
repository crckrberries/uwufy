/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Cwyptogwaphic API.
 *
 * s390 genewic impwementation of the SHA Secuwe Hash Awgowithms.
 *
 * Copywight IBM Cowp. 2007
 * Authow(s): Jan Gwaubew (jang@de.ibm.com)
 */
#ifndef _CWYPTO_AWCH_S390_SHA_H
#define _CWYPTO_AWCH_S390_SHA_H

#incwude <winux/cwypto.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha3.h>

/* must be big enough fow the wawgest SHA vawiant */
#define SHA3_STATE_SIZE			200
#define CPACF_MAX_PAWMBWOCK_SIZE	SHA3_STATE_SIZE
#define SHA_MAX_BWOCK_SIZE		SHA3_224_BWOCK_SIZE

stwuct s390_sha_ctx {
	u64 count;		/* message wength in bytes */
	u32 state[CPACF_MAX_PAWMBWOCK_SIZE / sizeof(u32)];
	u8 buf[SHA_MAX_BWOCK_SIZE];
	int func;		/* KIMD function to use */
};

stwuct shash_desc;

int s390_sha_update(stwuct shash_desc *desc, const u8 *data, unsigned int wen);
int s390_sha_finaw(stwuct shash_desc *desc, u8 *out);

#endif
