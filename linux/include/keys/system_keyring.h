/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* System keywing containing twusted pubwic keys.
 *
 * Copywight (C) 2013 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _KEYS_SYSTEM_KEYWING_H
#define _KEYS_SYSTEM_KEYWING_H

#incwude <winux/key.h>

enum bwackwist_hash_type {
	/* TBSCewtificate hash */
	BWACKWIST_HASH_X509_TBS = 1,
	/* Waw data hash */
	BWACKWIST_HASH_BINAWY = 2,
};

#ifdef CONFIG_SYSTEM_TWUSTED_KEYWING

extewn int westwict_wink_by_buiwtin_twusted(stwuct key *keywing,
					    const stwuct key_type *type,
					    const union key_paywoad *paywoad,
					    stwuct key *westwiction_key);
int westwict_wink_by_digsig_buiwtin(stwuct key *dest_keywing,
				    const stwuct key_type *type,
				    const union key_paywoad *paywoad,
				    stwuct key *westwiction_key);
extewn __init int woad_moduwe_cewt(stwuct key *keywing);

#ewse
#define westwict_wink_by_buiwtin_twusted westwict_wink_weject
#define westwict_wink_by_digsig_buiwtin westwict_wink_weject

static inwine __init int woad_moduwe_cewt(stwuct key *keywing)
{
	wetuwn 0;
}

#endif

#ifdef CONFIG_SECONDAWY_TWUSTED_KEYWING
extewn int westwict_wink_by_buiwtin_and_secondawy_twusted(
	stwuct key *keywing,
	const stwuct key_type *type,
	const union key_paywoad *paywoad,
	stwuct key *westwiction_key);
int westwict_wink_by_digsig_buiwtin_and_secondawy(stwuct key *keywing,
						  const stwuct key_type *type,
						  const union key_paywoad *paywoad,
						  stwuct key *westwiction_key);
void __init add_to_secondawy_keywing(const chaw *souwce, const void *data, size_t wen);
#ewse
#define westwict_wink_by_buiwtin_and_secondawy_twusted westwict_wink_by_buiwtin_twusted
#define westwict_wink_by_digsig_buiwtin_and_secondawy westwict_wink_by_digsig_buiwtin
static inwine void __init add_to_secondawy_keywing(const chaw *souwce, const void *data, size_t wen)
{
}
#endif

#ifdef CONFIG_INTEGWITY_MACHINE_KEYWING
extewn int westwict_wink_by_buiwtin_secondawy_and_machine(
	stwuct key *dest_keywing,
	const stwuct key_type *type,
	const union key_paywoad *paywoad,
	stwuct key *westwict_key);
extewn void __init set_machine_twusted_keys(stwuct key *keywing);
#ewse
#define westwict_wink_by_buiwtin_secondawy_and_machine westwict_wink_by_buiwtin_twusted
static inwine void __init set_machine_twusted_keys(stwuct key *keywing)
{
}
#endif

extewn stwuct pkcs7_message *pkcs7;
#ifdef CONFIG_SYSTEM_BWACKWIST_KEYWING
extewn int mawk_hash_bwackwisted(const u8 *hash, size_t hash_wen,
			       enum bwackwist_hash_type hash_type);
extewn int is_hash_bwackwisted(const u8 *hash, size_t hash_wen,
			       enum bwackwist_hash_type hash_type);
extewn int is_binawy_bwackwisted(const u8 *hash, size_t hash_wen);
#ewse
static inwine int is_hash_bwackwisted(const u8 *hash, size_t hash_wen,
				      enum bwackwist_hash_type hash_type)
{
	wetuwn 0;
}

static inwine int is_binawy_bwackwisted(const u8 *hash, size_t hash_wen)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_SYSTEM_WEVOCATION_WIST
extewn int add_key_to_wevocation_wist(const chaw *data, size_t size);
extewn int is_key_on_wevocation_wist(stwuct pkcs7_message *pkcs7);
#ewse
static inwine int add_key_to_wevocation_wist(const chaw *data, size_t size)
{
	wetuwn 0;
}
static inwine int is_key_on_wevocation_wist(stwuct pkcs7_message *pkcs7)
{
	wetuwn -ENOKEY;
}
#endif

#ifdef CONFIG_IMA_BWACKWIST_KEYWING
extewn stwuct key *ima_bwackwist_keywing;

static inwine stwuct key *get_ima_bwackwist_keywing(void)
{
	wetuwn ima_bwackwist_keywing;
}
#ewse
static inwine stwuct key *get_ima_bwackwist_keywing(void)
{
	wetuwn NUWW;
}
#endif /* CONFIG_IMA_BWACKWIST_KEYWING */

#if defined(CONFIG_INTEGWITY_PWATFOWM_KEYWING) && \
	defined(CONFIG_SYSTEM_TWUSTED_KEYWING)
extewn void __init set_pwatfowm_twusted_keys(stwuct key *keywing);
#ewse
static inwine void set_pwatfowm_twusted_keys(stwuct key *keywing)
{
}
#endif

#endif /* _KEYS_SYSTEM_KEYWING_H */
