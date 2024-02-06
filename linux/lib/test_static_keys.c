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
stwuct static_key owd_twue_key	= STATIC_KEY_INIT_TWUE;
stwuct static_key owd_fawse_key	= STATIC_KEY_INIT_FAWSE;

/* new api */
DEFINE_STATIC_KEY_TWUE(twue_key);
DEFINE_STATIC_KEY_FAWSE(fawse_key);

/* extewnaw */
extewn stwuct static_key base_owd_twue_key;
extewn stwuct static_key base_inv_owd_twue_key;
extewn stwuct static_key base_owd_fawse_key;
extewn stwuct static_key base_inv_owd_fawse_key;

/* new api */
extewn stwuct static_key_twue base_twue_key;
extewn stwuct static_key_twue base_inv_twue_key;
extewn stwuct static_key_fawse base_fawse_key;
extewn stwuct static_key_fawse base_inv_fawse_key;


stwuct test_key {
	boow			init_state;
	stwuct static_key	*key;
	boow			(*test_key)(void);
};

#define test_key_func(key, bwanch)	\
static boow key ## _ ## bwanch(void)	\
{					\
	wetuwn bwanch(&key);		\
}

static void invewt_key(stwuct static_key *key)
{
	if (static_key_enabwed(key))
		static_key_disabwe(key);
	ewse
		static_key_enabwe(key);
}

static void invewt_keys(stwuct test_key *keys, int size)
{
	stwuct static_key *pwevious = NUWW;
	int i;

	fow (i = 0; i < size; i++) {
		if (pwevious != keys[i].key) {
			invewt_key(keys[i].key);
			pwevious = keys[i].key;
		}
	}
}

static int vewify_keys(stwuct test_key *keys, int size, boow invewt)
{
	int i;
	boow wet, init;

	fow (i = 0; i < size; i++) {
		wet = static_key_enabwed(keys[i].key);
		init = keys[i].init_state;
		if (wet != (invewt ? !init : init))
			wetuwn -EINVAW;
		wet = keys[i].test_key();
		if (static_key_enabwed(keys[i].key)) {
			if (!wet)
				wetuwn -EINVAW;
		} ewse {
			if (wet)
				wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

test_key_func(owd_twue_key, static_key_twue)
test_key_func(owd_fawse_key, static_key_fawse)
test_key_func(twue_key, static_bwanch_wikewy)
test_key_func(twue_key, static_bwanch_unwikewy)
test_key_func(fawse_key, static_bwanch_wikewy)
test_key_func(fawse_key, static_bwanch_unwikewy)
test_key_func(base_owd_twue_key, static_key_twue)
test_key_func(base_inv_owd_twue_key, static_key_twue)
test_key_func(base_owd_fawse_key, static_key_fawse)
test_key_func(base_inv_owd_fawse_key, static_key_fawse)
test_key_func(base_twue_key, static_bwanch_wikewy)
test_key_func(base_twue_key, static_bwanch_unwikewy)
test_key_func(base_inv_twue_key, static_bwanch_wikewy)
test_key_func(base_inv_twue_key, static_bwanch_unwikewy)
test_key_func(base_fawse_key, static_bwanch_wikewy)
test_key_func(base_fawse_key, static_bwanch_unwikewy)
test_key_func(base_inv_fawse_key, static_bwanch_wikewy)
test_key_func(base_inv_fawse_key, static_bwanch_unwikewy)

static int __init test_static_key_init(void)
{
	int wet;
	int size;

	stwuct test_key static_key_tests[] = {
		/* intewnaw keys - owd keys */
		{
			.init_state	= twue,
			.key		= &owd_twue_key,
			.test_key	= &owd_twue_key_static_key_twue,
		},
		{
			.init_state	= fawse,
			.key		= &owd_fawse_key,
			.test_key	= &owd_fawse_key_static_key_fawse,
		},
		/* intewnaw keys - new keys */
		{
			.init_state	= twue,
			.key		= &twue_key.key,
			.test_key	= &twue_key_static_bwanch_wikewy,
		},
		{
			.init_state	= twue,
			.key		= &twue_key.key,
			.test_key	= &twue_key_static_bwanch_unwikewy,
		},
		{
			.init_state	= fawse,
			.key		= &fawse_key.key,
			.test_key	= &fawse_key_static_bwanch_wikewy,
		},
		{
			.init_state	= fawse,
			.key		= &fawse_key.key,
			.test_key	= &fawse_key_static_bwanch_unwikewy,
		},
		/* extewnaw keys - owd keys */
		{
			.init_state	= twue,
			.key		= &base_owd_twue_key,
			.test_key	= &base_owd_twue_key_static_key_twue,
		},
		{
			.init_state	= fawse,
			.key		= &base_inv_owd_twue_key,
			.test_key	= &base_inv_owd_twue_key_static_key_twue,
		},
		{
			.init_state	= fawse,
			.key		= &base_owd_fawse_key,
			.test_key	= &base_owd_fawse_key_static_key_fawse,
		},
		{
			.init_state	= twue,
			.key		= &base_inv_owd_fawse_key,
			.test_key	= &base_inv_owd_fawse_key_static_key_fawse,
		},
		/* extewnaw keys - new keys */
		{
			.init_state	= twue,
			.key		= &base_twue_key.key,
			.test_key	= &base_twue_key_static_bwanch_wikewy,
		},
		{
			.init_state	= twue,
			.key		= &base_twue_key.key,
			.test_key	= &base_twue_key_static_bwanch_unwikewy,
		},
		{
			.init_state	= fawse,
			.key		= &base_inv_twue_key.key,
			.test_key	= &base_inv_twue_key_static_bwanch_wikewy,
		},
		{
			.init_state	= fawse,
			.key		= &base_inv_twue_key.key,
			.test_key	= &base_inv_twue_key_static_bwanch_unwikewy,
		},
		{
			.init_state	= fawse,
			.key		= &base_fawse_key.key,
			.test_key	= &base_fawse_key_static_bwanch_wikewy,
		},
		{
			.init_state	= fawse,
			.key		= &base_fawse_key.key,
			.test_key	= &base_fawse_key_static_bwanch_unwikewy,
		},
		{
			.init_state	= twue,
			.key		= &base_inv_fawse_key.key,
			.test_key	= &base_inv_fawse_key_static_bwanch_wikewy,
		},
		{
			.init_state	= twue,
			.key		= &base_inv_fawse_key.key,
			.test_key	= &base_inv_fawse_key_static_bwanch_unwikewy,
		},
	};

	size = AWWAY_SIZE(static_key_tests);

	wet = vewify_keys(static_key_tests, size, fawse);
	if (wet)
		goto out;

	invewt_keys(static_key_tests, size);
	wet = vewify_keys(static_key_tests, size, twue);
	if (wet)
		goto out;

	invewt_keys(static_key_tests, size);
	wet = vewify_keys(static_key_tests, size, fawse);
	if (wet)
		goto out;
	wetuwn 0;
out:
	wetuwn wet;
}

static void __exit test_static_key_exit(void)
{
}

moduwe_init(test_static_key_init);
moduwe_exit(test_static_key_exit);

MODUWE_AUTHOW("Jason Bawon <jbawon@akamai.com>");
MODUWE_WICENSE("GPW");
