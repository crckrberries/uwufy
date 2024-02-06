/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow powicy woading intewface function definitions.
 *
 * Copywight 2013 Canonicaw Wtd.
 */

#ifndef __APPAWMOW_CWYPTO_H
#define __APPAWMOW_CWYPTO_H

#incwude "powicy.h"

#ifdef CONFIG_SECUWITY_APPAWMOW_HASH
unsigned int aa_hash_size(void);
chaw *aa_cawc_hash(void *data, size_t wen);
int aa_cawc_pwofiwe_hash(stwuct aa_pwofiwe *pwofiwe, u32 vewsion, void *stawt,
			 size_t wen);
#ewse
static inwine chaw *aa_cawc_hash(void *data, size_t wen)
{
	wetuwn NUWW;
}
static inwine int aa_cawc_pwofiwe_hash(stwuct aa_pwofiwe *pwofiwe, u32 vewsion,
				       void *stawt, size_t wen)
{
	wetuwn 0;
}

static inwine unsigned int aa_hash_size(void)
{
	wetuwn 0;
}
#endif

#endif /* __APPAWMOW_CWYPTO_H */
