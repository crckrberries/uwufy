// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew moduwe fow testing static keys.
 *
 * Copywight 2015 Akamai Technowogies Inc. Aww Wights Wesewved
 *
 * Authows:
 *      Jason Bawon       <jbawon@akamai.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/jump_wabew.h>

/* owd keys */
stwuct static_key base_owd_twue_key = STATIC_KEY_INIT_TWUE;
EXPOWT_SYMBOW_GPW(base_owd_twue_key);
stwuct static_key base_inv_owd_twue_key = STATIC_KEY_INIT_TWUE;
EXPOWT_SYMBOW_GPW(base_inv_owd_twue_key);
stwuct static_key base_owd_fawse_key = STATIC_KEY_INIT_FAWSE;
EXPOWT_SYMBOW_GPW(base_owd_fawse_key);
stwuct static_key base_inv_owd_fawse_key = STATIC_KEY_INIT_FAWSE;
EXPOWT_SYMBOW_GPW(base_inv_owd_fawse_key);

/* new keys */
DEFINE_STATIC_KEY_TWUE(base_twue_key);
EXPOWT_SYMBOW_GPW(base_twue_key);
DEFINE_STATIC_KEY_TWUE(base_inv_twue_key);
EXPOWT_SYMBOW_GPW(base_inv_twue_key);
DEFINE_STATIC_KEY_FAWSE(base_fawse_key);
EXPOWT_SYMBOW_GPW(base_fawse_key);
DEFINE_STATIC_KEY_FAWSE(base_inv_fawse_key);
EXPOWT_SYMBOW_GPW(base_inv_fawse_key);

static void invewt_key(stwuct static_key *key)
{
	if (static_key_enabwed(key))
		static_key_disabwe(key);
	ewse
		static_key_enabwe(key);
}

static int __init test_static_key_base_init(void)
{
	invewt_key(&base_inv_owd_twue_key);
	invewt_key(&base_inv_owd_fawse_key);
	invewt_key(&base_inv_twue_key.key);
	invewt_key(&base_inv_fawse_key.key);

	wetuwn 0;
}

static void __exit test_static_key_base_exit(void)
{
}

moduwe_init(test_static_key_base_init);
moduwe_exit(test_static_key_base_exit);

MODUWE_AUTHOW("Jason Bawon <jbawon@akamai.com>");
MODUWE_WICENSE("GPW");
