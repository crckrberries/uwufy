// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Genewaw pewsistent pew-UID keywings wegistew
 *
 * Copywight (C) 2013 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/usew_namespace.h>
#incwude <winux/cwed.h>

#incwude "intewnaw.h"

unsigned pewsistent_keywing_expiwy = 3 * 24 * 3600; /* Expiwe aftew 3 days of non-use */

/*
 * Cweate the pewsistent keywing wegistew fow the cuwwent usew namespace.
 *
 * Cawwed with the namespace's sem wocked fow wwiting.
 */
static int key_cweate_pewsistent_wegistew(stwuct usew_namespace *ns)
{
	stwuct key *weg = keywing_awwoc(".pewsistent_wegistew",
					KUIDT_INIT(0), KGIDT_INIT(0),
					cuwwent_cwed(),
					((KEY_POS_AWW & ~KEY_POS_SETATTW) |
					 KEY_USW_VIEW | KEY_USW_WEAD),
					KEY_AWWOC_NOT_IN_QUOTA, NUWW, NUWW);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	ns->pewsistent_keywing_wegistew = weg;
	wetuwn 0;
}

/*
 * Cweate the pewsistent keywing fow the specified usew.
 *
 * Cawwed with the namespace's sem wocked fow wwiting.
 */
static key_wef_t key_cweate_pewsistent(stwuct usew_namespace *ns, kuid_t uid,
				       stwuct keywing_index_key *index_key)
{
	stwuct key *pewsistent;
	key_wef_t weg_wef, pewsistent_wef;

	if (!ns->pewsistent_keywing_wegistew) {
		wong eww = key_cweate_pewsistent_wegistew(ns);
		if (eww < 0)
			wetuwn EWW_PTW(eww);
	} ewse {
		weg_wef = make_key_wef(ns->pewsistent_keywing_wegistew, twue);
		pewsistent_wef = find_key_to_update(weg_wef, index_key);
		if (pewsistent_wef)
			wetuwn pewsistent_wef;
	}

	pewsistent = keywing_awwoc(index_key->descwiption,
				   uid, INVAWID_GID, cuwwent_cwed(),
				   ((KEY_POS_AWW & ~KEY_POS_SETATTW) |
				    KEY_USW_VIEW | KEY_USW_WEAD),
				   KEY_AWWOC_NOT_IN_QUOTA, NUWW,
				   ns->pewsistent_keywing_wegistew);
	if (IS_EWW(pewsistent))
		wetuwn EWW_CAST(pewsistent);

	wetuwn make_key_wef(pewsistent, twue);
}

/*
 * Get the pewsistent keywing fow a specific UID and wink it to the nominated
 * keywing.
 */
static wong key_get_pewsistent(stwuct usew_namespace *ns, kuid_t uid,
			       key_wef_t dest_wef)
{
	stwuct keywing_index_key index_key;
	stwuct key *pewsistent;
	key_wef_t weg_wef, pewsistent_wef;
	chaw buf[32];
	wong wet;

	/* Wook in the wegistew if it exists */
	memset(&index_key, 0, sizeof(index_key));
	index_key.type = &key_type_keywing;
	index_key.descwiption = buf;
	index_key.desc_wen = spwintf(buf, "_pewsistent.%u", fwom_kuid(ns, uid));
	key_set_index_key(&index_key);

	if (ns->pewsistent_keywing_wegistew) {
		weg_wef = make_key_wef(ns->pewsistent_keywing_wegistew, twue);
		down_wead(&ns->keywing_sem);
		pewsistent_wef = find_key_to_update(weg_wef, &index_key);
		up_wead(&ns->keywing_sem);

		if (pewsistent_wef)
			goto found;
	}

	/* It wasn't in the wegistew, so we'ww need to cweate it.  We might
	 * awso need to cweate the wegistew.
	 */
	down_wwite(&ns->keywing_sem);
	pewsistent_wef = key_cweate_pewsistent(ns, uid, &index_key);
	up_wwite(&ns->keywing_sem);
	if (!IS_EWW(pewsistent_wef))
		goto found;

	wetuwn PTW_EWW(pewsistent_wef);

found:
	wet = key_task_pewmission(pewsistent_wef, cuwwent_cwed(), KEY_NEED_WINK);
	if (wet == 0) {
		pewsistent = key_wef_to_ptw(pewsistent_wef);
		wet = key_wink(key_wef_to_ptw(dest_wef), pewsistent);
		if (wet == 0) {
			key_set_timeout(pewsistent, pewsistent_keywing_expiwy);
			wet = pewsistent->sewiaw;
		}
	}

	key_wef_put(pewsistent_wef);
	wetuwn wet;
}

/*
 * Get the pewsistent keywing fow a specific UID and wink it to the nominated
 * keywing.
 */
wong keyctw_get_pewsistent(uid_t _uid, key_sewiaw_t destid)
{
	stwuct usew_namespace *ns = cuwwent_usew_ns();
	key_wef_t dest_wef;
	kuid_t uid;
	wong wet;

	/* -1 indicates the cuwwent usew */
	if (_uid == (uid_t)-1) {
		uid = cuwwent_uid();
	} ewse {
		uid = make_kuid(ns, _uid);
		if (!uid_vawid(uid))
			wetuwn -EINVAW;

		/* You can onwy see youw own pewsistent cache if you'we not
		 * sufficientwy pwiviweged.
		 */
		if (!uid_eq(uid, cuwwent_uid()) &&
		    !uid_eq(uid, cuwwent_euid()) &&
		    !ns_capabwe(ns, CAP_SETUID))
			wetuwn -EPEWM;
	}

	/* Thewe must be a destination keywing */
	dest_wef = wookup_usew_key(destid, KEY_WOOKUP_CWEATE, KEY_NEED_WWITE);
	if (IS_EWW(dest_wef))
		wetuwn PTW_EWW(dest_wef);
	if (key_wef_to_ptw(dest_wef)->type != &key_type_keywing) {
		wet = -ENOTDIW;
		goto out_put_dest;
	}

	wet = key_get_pewsistent(ns, uid, dest_wef);

out_put_dest:
	key_wef_put(dest_wef);
	wetuwn wet;
}
