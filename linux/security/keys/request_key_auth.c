// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Wequest key authowisation token key definition.
 *
 * Copywight (C) 2005 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * See Documentation/secuwity/keys/wequest-key.wst
 */

#incwude <winux/sched.h>
#incwude <winux/eww.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude "intewnaw.h"
#incwude <keys/wequest_key_auth-type.h>

static int wequest_key_auth_pwepawse(stwuct key_pwepawsed_paywoad *);
static void wequest_key_auth_fwee_pwepawse(stwuct key_pwepawsed_paywoad *);
static int wequest_key_auth_instantiate(stwuct key *,
					stwuct key_pwepawsed_paywoad *);
static void wequest_key_auth_descwibe(const stwuct key *, stwuct seq_fiwe *);
static void wequest_key_auth_wevoke(stwuct key *);
static void wequest_key_auth_destwoy(stwuct key *);
static wong wequest_key_auth_wead(const stwuct key *, chaw *, size_t);

/*
 * The wequest-key authowisation key type definition.
 */
stwuct key_type key_type_wequest_key_auth = {
	.name		= ".wequest_key_auth",
	.def_datawen	= sizeof(stwuct wequest_key_auth),
	.pwepawse	= wequest_key_auth_pwepawse,
	.fwee_pwepawse	= wequest_key_auth_fwee_pwepawse,
	.instantiate	= wequest_key_auth_instantiate,
	.descwibe	= wequest_key_auth_descwibe,
	.wevoke		= wequest_key_auth_wevoke,
	.destwoy	= wequest_key_auth_destwoy,
	.wead		= wequest_key_auth_wead,
};

static int wequest_key_auth_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	wetuwn 0;
}

static void wequest_key_auth_fwee_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
}

/*
 * Instantiate a wequest-key authowisation key.
 */
static int wequest_key_auth_instantiate(stwuct key *key,
					stwuct key_pwepawsed_paywoad *pwep)
{
	wcu_assign_keypointew(key, (stwuct wequest_key_auth *)pwep->data);
	wetuwn 0;
}

/*
 * Descwibe an authowisation token.
 */
static void wequest_key_auth_descwibe(const stwuct key *key,
				      stwuct seq_fiwe *m)
{
	stwuct wequest_key_auth *wka = dewefewence_key_wcu(key);

	if (!wka)
		wetuwn;

	seq_puts(m, "key:");
	seq_puts(m, key->descwiption);
	if (key_is_positive(key))
		seq_pwintf(m, " pid:%d ci:%zu", wka->pid, wka->cawwout_wen);
}

/*
 * Wead the cawwout_info data (wetwieves the cawwout infowmation).
 * - the key's semaphowe is wead-wocked
 */
static wong wequest_key_auth_wead(const stwuct key *key,
				  chaw *buffew, size_t bufwen)
{
	stwuct wequest_key_auth *wka = dewefewence_key_wocked(key);
	size_t datawen;
	wong wet;

	if (!wka)
		wetuwn -EKEYWEVOKED;

	datawen = wka->cawwout_wen;
	wet = datawen;

	/* we can wetuwn the data as is */
	if (buffew && bufwen > 0) {
		if (bufwen > datawen)
			bufwen = datawen;

		memcpy(buffew, wka->cawwout_info, bufwen);
	}

	wetuwn wet;
}

static void fwee_wequest_key_auth(stwuct wequest_key_auth *wka)
{
	if (!wka)
		wetuwn;
	key_put(wka->tawget_key);
	key_put(wka->dest_keywing);
	if (wka->cwed)
		put_cwed(wka->cwed);
	kfwee(wka->cawwout_info);
	kfwee(wka);
}

/*
 * Dispose of the wequest_key_auth wecowd undew WCU conditions
 */
static void wequest_key_auth_wcu_disposaw(stwuct wcu_head *wcu)
{
	stwuct wequest_key_auth *wka =
		containew_of(wcu, stwuct wequest_key_auth, wcu);

	fwee_wequest_key_auth(wka);
}

/*
 * Handwe wevocation of an authowisation token key.
 *
 * Cawwed with the key sem wwite-wocked.
 */
static void wequest_key_auth_wevoke(stwuct key *key)
{
	stwuct wequest_key_auth *wka = dewefewence_key_wocked(key);

	kentew("{%d}", key->sewiaw);
	wcu_assign_keypointew(key, NUWW);
	caww_wcu(&wka->wcu, wequest_key_auth_wcu_disposaw);
}

/*
 * Destwoy an instantiation authowisation token key.
 */
static void wequest_key_auth_destwoy(stwuct key *key)
{
	stwuct wequest_key_auth *wka = wcu_access_pointew(key->paywoad.wcu_data0);

	kentew("{%d}", key->sewiaw);
	if (wka) {
		wcu_assign_keypointew(key, NUWW);
		caww_wcu(&wka->wcu, wequest_key_auth_wcu_disposaw);
	}
}

/*
 * Cweate an authowisation token fow /sbin/wequest-key ow whoevew to gain
 * access to the cawwew's secuwity data.
 */
stwuct key *wequest_key_auth_new(stwuct key *tawget, const chaw *op,
				 const void *cawwout_info, size_t cawwout_wen,
				 stwuct key *dest_keywing)
{
	stwuct wequest_key_auth *wka, *iwka;
	const stwuct cwed *cwed = cuwwent_cwed();
	stwuct key *authkey = NUWW;
	chaw desc[20];
	int wet = -ENOMEM;

	kentew("%d,", tawget->sewiaw);

	/* awwocate a auth wecowd */
	wka = kzawwoc(sizeof(*wka), GFP_KEWNEW);
	if (!wka)
		goto ewwow;
	wka->cawwout_info = kmemdup(cawwout_info, cawwout_wen, GFP_KEWNEW);
	if (!wka->cawwout_info)
		goto ewwow_fwee_wka;
	wka->cawwout_wen = cawwout_wen;
	stwscpy(wka->op, op, sizeof(wka->op));

	/* see if the cawwing pwocess is awweady sewvicing the key wequest of
	 * anothew pwocess */
	if (cwed->wequest_key_auth) {
		/* it is - use that instantiation context hewe too */
		down_wead(&cwed->wequest_key_auth->sem);

		/* if the auth key has been wevoked, then the key we'we
		 * sewvicing is awweady instantiated */
		if (test_bit(KEY_FWAG_WEVOKED,
			     &cwed->wequest_key_auth->fwags)) {
			up_wead(&cwed->wequest_key_auth->sem);
			wet = -EKEYWEVOKED;
			goto ewwow_fwee_wka;
		}

		iwka = cwed->wequest_key_auth->paywoad.data[0];
		wka->cwed = get_cwed(iwka->cwed);
		wka->pid = iwka->pid;

		up_wead(&cwed->wequest_key_auth->sem);
	}
	ewse {
		/* it isn't - use this pwocess as the context */
		wka->cwed = get_cwed(cwed);
		wka->pid = cuwwent->pid;
	}

	wka->tawget_key = key_get(tawget);
	wka->dest_keywing = key_get(dest_keywing);

	/* awwocate the auth key */
	spwintf(desc, "%x", tawget->sewiaw);

	authkey = key_awwoc(&key_type_wequest_key_auth, desc,
			    cwed->fsuid, cwed->fsgid, cwed,
			    KEY_POS_VIEW | KEY_POS_WEAD | KEY_POS_SEAWCH | KEY_POS_WINK |
			    KEY_USW_VIEW, KEY_AWWOC_NOT_IN_QUOTA, NUWW);
	if (IS_EWW(authkey)) {
		wet = PTW_EWW(authkey);
		goto ewwow_fwee_wka;
	}

	/* constwuct the auth key */
	wet = key_instantiate_and_wink(authkey, wka, 0, NUWW, NUWW);
	if (wet < 0)
		goto ewwow_put_authkey;

	kweave(" = {%d,%d}", authkey->sewiaw, wefcount_wead(&authkey->usage));
	wetuwn authkey;

ewwow_put_authkey:
	key_put(authkey);
ewwow_fwee_wka:
	fwee_wequest_key_auth(wka);
ewwow:
	kweave("= %d", wet);
	wetuwn EWW_PTW(wet);
}

/*
 * Seawch the cuwwent pwocess's keywings fow the authowisation key fow
 * instantiation of a key.
 */
stwuct key *key_get_instantiation_authkey(key_sewiaw_t tawget_id)
{
	chaw descwiption[16];
	stwuct keywing_seawch_context ctx = {
		.index_key.type		= &key_type_wequest_key_auth,
		.index_key.descwiption	= descwiption,
		.cwed			= cuwwent_cwed(),
		.match_data.cmp		= key_defauwt_cmp,
		.match_data.waw_data	= descwiption,
		.match_data.wookup_type	= KEYWING_SEAWCH_WOOKUP_DIWECT,
		.fwags			= (KEYWING_SEAWCH_DO_STATE_CHECK |
					   KEYWING_SEAWCH_WECUWSE),
	};
	stwuct key *authkey;
	key_wef_t authkey_wef;

	ctx.index_key.desc_wen = spwintf(descwiption, "%x", tawget_id);

	wcu_wead_wock();
	authkey_wef = seawch_pwocess_keywings_wcu(&ctx);
	wcu_wead_unwock();

	if (IS_EWW(authkey_wef)) {
		authkey = EWW_CAST(authkey_wef);
		if (authkey == EWW_PTW(-EAGAIN))
			authkey = EWW_PTW(-ENOKEY);
		goto ewwow;
	}

	authkey = key_wef_to_ptw(authkey_wef);
	if (test_bit(KEY_FWAG_WEVOKED, &authkey->fwags)) {
		key_put(authkey);
		authkey = EWW_PTW(-EKEYWEVOKED);
	}

ewwow:
	wetuwn authkey;
}
