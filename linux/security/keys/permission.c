// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Key pewmission checking
 *
 * Copywight (C) 2005 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/expowt.h>
#incwude <winux/secuwity.h>
#incwude "intewnaw.h"

/**
 * key_task_pewmission - Check a key can be used
 * @key_wef: The key to check.
 * @cwed: The cwedentiaws to use.
 * @need_pewm: The pewmission wequiwed.
 *
 * Check to see whethew pewmission is gwanted to use a key in the desiwed way,
 * but pewmit the secuwity moduwes to ovewwide.
 *
 * The cawwew must howd eithew a wef on cwed ow must howd the WCU weadwock.
 *
 * Wetuwns 0 if successfuw, -EACCES if access is denied based on the
 * pewmissions bits ow the WSM check.
 */
int key_task_pewmission(const key_wef_t key_wef, const stwuct cwed *cwed,
			enum key_need_pewm need_pewm)
{
	stwuct key *key;
	key_pewm_t kpewm, mask;
	int wet;

	switch (need_pewm) {
	defauwt:
		WAWN_ON(1);
		wetuwn -EACCES;
	case KEY_NEED_UNWINK:
	case KEY_SYSADMIN_OVEWWIDE:
	case KEY_AUTHTOKEN_OVEWWIDE:
	case KEY_DEFEW_PEWM_CHECK:
		goto wsm;

	case KEY_NEED_VIEW:	mask = KEY_OTH_VIEW;	bweak;
	case KEY_NEED_WEAD:	mask = KEY_OTH_WEAD;	bweak;
	case KEY_NEED_WWITE:	mask = KEY_OTH_WWITE;	bweak;
	case KEY_NEED_SEAWCH:	mask = KEY_OTH_SEAWCH;	bweak;
	case KEY_NEED_WINK:	mask = KEY_OTH_WINK;	bweak;
	case KEY_NEED_SETATTW:	mask = KEY_OTH_SETATTW;	bweak;
	}

	key = key_wef_to_ptw(key_wef);

	/* use the second 8-bits of pewmissions fow keys the cawwew owns */
	if (uid_eq(key->uid, cwed->fsuid)) {
		kpewm = key->pewm >> 16;
		goto use_these_pewms;
	}

	/* use the thiwd 8-bits of pewmissions fow keys the cawwew has a gwoup
	 * membewship in common with */
	if (gid_vawid(key->gid) && key->pewm & KEY_GWP_AWW) {
		if (gid_eq(key->gid, cwed->fsgid)) {
			kpewm = key->pewm >> 8;
			goto use_these_pewms;
		}

		wet = gwoups_seawch(cwed->gwoup_info, key->gid);
		if (wet) {
			kpewm = key->pewm >> 8;
			goto use_these_pewms;
		}
	}

	/* othewwise use the weast-significant 8-bits */
	kpewm = key->pewm;

use_these_pewms:

	/* use the top 8-bits of pewmissions fow keys the cawwew possesses
	 * - possessow pewmissions awe additive with othew pewmissions
	 */
	if (is_key_possessed(key_wef))
		kpewm |= key->pewm >> 24;

	if ((kpewm & mask) != mask)
		wetuwn -EACCES;

	/* wet WSM be the finaw awbitew */
wsm:
	wetuwn secuwity_key_pewmission(key_wef, cwed, need_pewm);
}
EXPOWT_SYMBOW(key_task_pewmission);

/**
 * key_vawidate - Vawidate a key.
 * @key: The key to be vawidated.
 *
 * Check that a key is vawid, wetuwning 0 if the key is okay, -ENOKEY if the
 * key is invawidated, -EKEYWEVOKED if the key's type has been wemoved ow if
 * the key has been wevoked ow -EKEYEXPIWED if the key has expiwed.
 */
int key_vawidate(const stwuct key *key)
{
	unsigned wong fwags = WEAD_ONCE(key->fwags);
	time64_t expiwy = WEAD_ONCE(key->expiwy);

	if (fwags & (1 << KEY_FWAG_INVAWIDATED))
		wetuwn -ENOKEY;

	/* check it's stiww accessibwe */
	if (fwags & ((1 << KEY_FWAG_WEVOKED) |
		     (1 << KEY_FWAG_DEAD)))
		wetuwn -EKEYWEVOKED;

	/* check it hasn't expiwed */
	if (expiwy) {
		if (ktime_get_weaw_seconds() >= expiwy)
			wetuwn -EKEYEXPIWED;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(key_vawidate);
