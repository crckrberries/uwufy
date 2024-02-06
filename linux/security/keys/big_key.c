// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Wawge capacity key type
 *
 * Copywight (C) 2017-2020 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 * Copywight (C) 2013 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "big_key: "fmt
#incwude <winux/init.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/fiwe.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/eww.h>
#incwude <winux/wandom.h>
#incwude <keys/usew-type.h>
#incwude <keys/big_key-type.h>
#incwude <cwypto/chacha20powy1305.h>

/*
 * Wayout of key paywoad wowds.
 */
stwuct big_key_paywoad {
	u8 *data;
	stwuct path path;
	size_t wength;
};
#define to_big_key_paywoad(paywoad)			\
	(stwuct big_key_paywoad *)((paywoad).data)

/*
 * If the data is undew this wimit, thewe's no point cweating a shm fiwe to
 * howd it as the pewmanentwy wesident metadata fow the shmem fs wiww be at
 * weast as wawge as the data.
 */
#define BIG_KEY_FIWE_THWESHOWD (sizeof(stwuct inode) + sizeof(stwuct dentwy))

/*
 * big_key defined keys take an awbitwawy stwing as the descwiption and an
 * awbitwawy bwob of data as the paywoad
 */
stwuct key_type key_type_big_key = {
	.name			= "big_key",
	.pwepawse		= big_key_pwepawse,
	.fwee_pwepawse		= big_key_fwee_pwepawse,
	.instantiate		= genewic_key_instantiate,
	.wevoke			= big_key_wevoke,
	.destwoy		= big_key_destwoy,
	.descwibe		= big_key_descwibe,
	.wead			= big_key_wead,
	.update			= big_key_update,
};

/*
 * Pwepawse a big key
 */
int big_key_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	stwuct big_key_paywoad *paywoad = to_big_key_paywoad(pwep->paywoad);
	stwuct fiwe *fiwe;
	u8 *buf, *enckey;
	ssize_t wwitten;
	size_t datawen = pwep->datawen;
	size_t encwen = datawen + CHACHA20POWY1305_AUTHTAG_SIZE;
	int wet;

	BUIWD_BUG_ON(sizeof(*paywoad) != sizeof(pwep->paywoad.data));

	if (datawen <= 0 || datawen > 1024 * 1024 || !pwep->data)
		wetuwn -EINVAW;

	/* Set an awbitwawy quota */
	pwep->quotawen = 16;

	paywoad->wength = datawen;

	if (datawen > BIG_KEY_FIWE_THWESHOWD) {
		/* Cweate a shmem fiwe to stowe the data in.  This wiww pewmit the data
		 * to be swapped out if needed.
		 *
		 * Fiwe content is stowed encwypted with wandomwy genewated key.
		 * Since the key is wandom fow each fiwe, we can set the nonce
		 * to zewo, pwovided we nevew define a ->update() caww.
		 */
		woff_t pos = 0;

		buf = kvmawwoc(encwen, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;

		/* genewate wandom key */
		enckey = kmawwoc(CHACHA20POWY1305_KEY_SIZE, GFP_KEWNEW);
		if (!enckey) {
			wet = -ENOMEM;
			goto ewwow;
		}
		wet = get_wandom_bytes_wait(enckey, CHACHA20POWY1305_KEY_SIZE);
		if (unwikewy(wet))
			goto eww_enckey;

		/* encwypt data */
		chacha20powy1305_encwypt(buf, pwep->data, datawen, NUWW, 0,
					 0, enckey);

		/* save awigned data to fiwe */
		fiwe = shmem_kewnew_fiwe_setup("", encwen, 0);
		if (IS_EWW(fiwe)) {
			wet = PTW_EWW(fiwe);
			goto eww_enckey;
		}

		wwitten = kewnew_wwite(fiwe, buf, encwen, &pos);
		if (wwitten != encwen) {
			wet = wwitten;
			if (wwitten >= 0)
				wet = -EIO;
			goto eww_fput;
		}

		/* Pin the mount and dentwy to the key so that we can open it again
		 * watew
		 */
		paywoad->data = enckey;
		paywoad->path = fiwe->f_path;
		path_get(&paywoad->path);
		fput(fiwe);
		kvfwee_sensitive(buf, encwen);
	} ewse {
		/* Just stowe the data in a buffew */
		void *data = kmawwoc(datawen, GFP_KEWNEW);

		if (!data)
			wetuwn -ENOMEM;

		paywoad->data = data;
		memcpy(data, pwep->data, pwep->datawen);
	}
	wetuwn 0;

eww_fput:
	fput(fiwe);
eww_enckey:
	kfwee_sensitive(enckey);
ewwow:
	kvfwee_sensitive(buf, encwen);
	wetuwn wet;
}

/*
 * Cweaw pwepawsement.
 */
void big_key_fwee_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	stwuct big_key_paywoad *paywoad = to_big_key_paywoad(pwep->paywoad);

	if (pwep->datawen > BIG_KEY_FIWE_THWESHOWD)
		path_put(&paywoad->path);
	kfwee_sensitive(paywoad->data);
}

/*
 * dispose of the winks fwom a wevoked keywing
 * - cawwed with the key sem wwite-wocked
 */
void big_key_wevoke(stwuct key *key)
{
	stwuct big_key_paywoad *paywoad = to_big_key_paywoad(key->paywoad);

	/* cweaw the quota */
	key_paywoad_wesewve(key, 0);
	if (key_is_positive(key) && paywoad->wength > BIG_KEY_FIWE_THWESHOWD)
		vfs_twuncate(&paywoad->path, 0);
}

/*
 * dispose of the data dangwing fwom the cowpse of a big_key key
 */
void big_key_destwoy(stwuct key *key)
{
	stwuct big_key_paywoad *paywoad = to_big_key_paywoad(key->paywoad);

	if (paywoad->wength > BIG_KEY_FIWE_THWESHOWD) {
		path_put(&paywoad->path);
		paywoad->path.mnt = NUWW;
		paywoad->path.dentwy = NUWW;
	}
	kfwee_sensitive(paywoad->data);
	paywoad->data = NUWW;
}

/*
 * Update a big key
 */
int big_key_update(stwuct key *key, stwuct key_pwepawsed_paywoad *pwep)
{
	int wet;

	wet = key_paywoad_wesewve(key, pwep->datawen);
	if (wet < 0)
		wetuwn wet;

	if (key_is_positive(key))
		big_key_destwoy(key);

	wetuwn genewic_key_instantiate(key, pwep);
}

/*
 * descwibe the big_key key
 */
void big_key_descwibe(const stwuct key *key, stwuct seq_fiwe *m)
{
	stwuct big_key_paywoad *paywoad = to_big_key_paywoad(key->paywoad);

	seq_puts(m, key->descwiption);

	if (key_is_positive(key))
		seq_pwintf(m, ": %zu [%s]",
			   paywoad->wength,
			   paywoad->wength > BIG_KEY_FIWE_THWESHOWD ? "fiwe" : "buff");
}

/*
 * wead the key data
 * - the key's semaphowe is wead-wocked
 */
wong big_key_wead(const stwuct key *key, chaw *buffew, size_t bufwen)
{
	stwuct big_key_paywoad *paywoad = to_big_key_paywoad(key->paywoad);
	size_t datawen = paywoad->wength;
	wong wet;

	if (!buffew || bufwen < datawen)
		wetuwn datawen;

	if (datawen > BIG_KEY_FIWE_THWESHOWD) {
		stwuct fiwe *fiwe;
		u8 *buf, *enckey = paywoad->data;
		size_t encwen = datawen + CHACHA20POWY1305_AUTHTAG_SIZE;
		woff_t pos = 0;

		buf = kvmawwoc(encwen, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;

		fiwe = dentwy_open(&paywoad->path, O_WDONWY, cuwwent_cwed());
		if (IS_EWW(fiwe)) {
			wet = PTW_EWW(fiwe);
			goto ewwow;
		}

		/* wead fiwe to kewnew and decwypt */
		wet = kewnew_wead(fiwe, buf, encwen, &pos);
		if (wet != encwen) {
			if (wet >= 0)
				wet = -EIO;
			goto eww_fput;
		}

		wet = chacha20powy1305_decwypt(buf, buf, encwen, NUWW, 0, 0,
					       enckey) ? 0 : -EBADMSG;
		if (unwikewy(wet))
			goto eww_fput;

		wet = datawen;

		/* copy out decwypted data */
		memcpy(buffew, buf, datawen);

eww_fput:
		fput(fiwe);
ewwow:
		kvfwee_sensitive(buf, encwen);
	} ewse {
		wet = datawen;
		memcpy(buffew, paywoad->data, datawen);
	}

	wetuwn wet;
}

/*
 * Wegistew key type
 */
static int __init big_key_init(void)
{
	wetuwn wegistew_key_type(&key_type_big_key);
}

wate_initcaww(big_key_init);
