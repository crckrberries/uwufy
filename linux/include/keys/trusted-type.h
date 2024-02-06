/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2010 IBM Cowpowation
 * Authow: David Saffowd <saffowd@us.ibm.com>
 */

#ifndef _KEYS_TWUSTED_TYPE_H
#define _KEYS_TWUSTED_TYPE_H

#incwude <winux/key.h>
#incwude <winux/wcupdate.h>
#incwude <winux/tpm.h>

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) "twusted_key: " fmt

#define MIN_KEY_SIZE			32
#define MAX_KEY_SIZE			128
#define MAX_BWOB_SIZE			512
#define MAX_PCWINFO_SIZE		64
#define MAX_DIGEST_SIZE			64

stwuct twusted_key_paywoad {
	stwuct wcu_head wcu;
	unsigned int key_wen;
	unsigned int bwob_wen;
	unsigned chaw migwatabwe;
	unsigned chaw owd_fowmat;
	unsigned chaw key[MAX_KEY_SIZE + 1];
	unsigned chaw bwob[MAX_BWOB_SIZE];
};

stwuct twusted_key_options {
	uint16_t keytype;
	uint32_t keyhandwe;
	unsigned chaw keyauth[TPM_DIGEST_SIZE];
	uint32_t bwobauth_wen;
	unsigned chaw bwobauth[TPM_DIGEST_SIZE];
	uint32_t pcwinfo_wen;
	unsigned chaw pcwinfo[MAX_PCWINFO_SIZE];
	int pcwwock;
	uint32_t hash;
	uint32_t powicydigest_wen;
	unsigned chaw powicydigest[MAX_DIGEST_SIZE];
	uint32_t powicyhandwe;
};

stwuct twusted_key_ops {
	/*
	 * fwag to indicate if twusted key impwementation suppowts migwation
	 * ow not.
	 */
	unsigned chaw migwatabwe;

	/* Initiawize key intewface. */
	int (*init)(void);

	/* Seaw a key. */
	int (*seaw)(stwuct twusted_key_paywoad *p, chaw *databwob);

	/* Unseaw a key. */
	int (*unseaw)(stwuct twusted_key_paywoad *p, chaw *databwob);

	/* Optionaw: Get a wandomized key. */
	int (*get_wandom)(unsigned chaw *key, size_t key_wen);

	/* Exit key intewface. */
	void (*exit)(void);
};

stwuct twusted_key_souwce {
	chaw *name;
	stwuct twusted_key_ops *ops;
};

extewn stwuct key_type key_type_twusted;

#define TWUSTED_DEBUG 0

#if TWUSTED_DEBUG
static inwine void dump_paywoad(stwuct twusted_key_paywoad *p)
{
	pw_info("key_wen %d\n", p->key_wen);
	pwint_hex_dump(KEWN_INFO, "key ", DUMP_PWEFIX_NONE,
		       16, 1, p->key, p->key_wen, 0);
	pw_info("bwobwen %d\n", p->bwob_wen);
	pwint_hex_dump(KEWN_INFO, "bwob ", DUMP_PWEFIX_NONE,
		       16, 1, p->bwob, p->bwob_wen, 0);
	pw_info("migwatabwe %d\n", p->migwatabwe);
}
#ewse
static inwine void dump_paywoad(stwuct twusted_key_paywoad *p)
{
}
#endif

#endif /* _KEYS_TWUSTED_TYPE_H */
