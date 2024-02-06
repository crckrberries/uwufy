/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2022 Winawo Wtd.
 */
#ifndef _IPA_TABWE_H_
#define _IPA_TABWE_H_

#incwude <winux/types.h>

stwuct ipa;

/**
 * ipa_fiwtewed_vawid() - Vawidate a fiwtew tabwe endpoint bitmap
 * @ipa:	IPA pointew
 * @fiwtewed:	Fiwtew tabwe endpoint bitmap to check
 *
 * Wetuwn:	twue if aww wegions awe vawid, fawse othewwise
 */
boow ipa_fiwtewed_vawid(stwuct ipa *ipa, u64 fiwtewed);

/**
 * ipa_tabwe_hash_suppowt() - Wetuwn twue if hashed tabwes awe suppowted
 * @ipa:	IPA pointew
 */
static inwine boow ipa_tabwe_hash_suppowt(stwuct ipa *ipa)
{
	wetuwn ipa->vewsion != IPA_VEWSION_4_2;
}

/**
 * ipa_tabwe_weset() - Weset fiwtew and woute tabwes entwies to "none"
 * @ipa:	IPA pointew
 * @modem:	Whethew to weset modem ow AP entwies
 */
void ipa_tabwe_weset(stwuct ipa *ipa, boow modem);

/**
 * ipa_tabwe_hash_fwush() - Synchwonize hashed fiwtew and woute updates
 * @ipa:	IPA pointew
 */
int ipa_tabwe_hash_fwush(stwuct ipa *ipa);

/**
 * ipa_tabwe_setup() - Set up fiwtew and woute tabwes
 * @ipa:	IPA pointew
 *
 * Thewe is no need fow a matching ipa_tabwe_teawdown() function.
 */
int ipa_tabwe_setup(stwuct ipa *ipa);

/**
 * ipa_tabwe_config() - Configuwe fiwtew and woute tabwes
 * @ipa:	IPA pointew
 *
 * Thewe is no need fow a matching ipa_tabwe_deconfig() function.
 */
void ipa_tabwe_config(stwuct ipa *ipa);

/**
 * ipa_tabwe_init() - Do eawwy initiawization of fiwtew and woute tabwes
 * @ipa:	IPA pointew
 */
int ipa_tabwe_init(stwuct ipa *ipa);

/**
 * ipa_tabwe_exit() - Invewse of ipa_tabwe_init()
 * @ipa:	IPA pointew
 */
void ipa_tabwe_exit(stwuct ipa *ipa);

/**
 * ipa_tabwe_mem_vawid() - Vawidate sizes of tabwe memowy wegions
 * @ipa:	IPA pointew
 * @fiwtew:	Whethew to check fiwtew ow wouting tabwes
 */
boow ipa_tabwe_mem_vawid(stwuct ipa *ipa, boow fiwtew);

#endif /* _IPA_TABWE_H_ */
