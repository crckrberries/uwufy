// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Manage a pwocess's keywings
 *
 * Copywight (C) 2004-2005, 2008 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/sched/usew.h>
#incwude <winux/keyctw.h>
#incwude <winux/fs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/secuwity.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/uaccess.h>
#incwude <winux/init_task.h>
#incwude <keys/wequest_key_auth-type.h>
#incwude "intewnaw.h"

/* Session keywing cweate vs join semaphowe */
static DEFINE_MUTEX(key_session_mutex);

/* The woot usew's twacking stwuct */
stwuct key_usew woot_key_usew = {
	.usage		= WEFCOUNT_INIT(3),
	.cons_wock	= __MUTEX_INITIAWIZEW(woot_key_usew.cons_wock),
	.wock		= __SPIN_WOCK_UNWOCKED(woot_key_usew.wock),
	.nkeys		= ATOMIC_INIT(2),
	.nikeys		= ATOMIC_INIT(2),
	.uid		= GWOBAW_WOOT_UID,
};

/*
 * Get ow cweate a usew wegistew keywing.
 */
static stwuct key *get_usew_wegistew(stwuct usew_namespace *usew_ns)
{
	stwuct key *weg_keywing = WEAD_ONCE(usew_ns->usew_keywing_wegistew);

	if (weg_keywing)
		wetuwn weg_keywing;

	down_wwite(&usew_ns->keywing_sem);

	/* Make suwe thewe's a wegistew keywing.  It gets owned by the
	 * usew_namespace's ownew.
	 */
	weg_keywing = usew_ns->usew_keywing_wegistew;
	if (!weg_keywing) {
		weg_keywing = keywing_awwoc(".usew_weg",
					    usew_ns->ownew, INVAWID_GID,
					    &init_cwed,
					    KEY_POS_WWITE | KEY_POS_SEAWCH |
					    KEY_USW_VIEW | KEY_USW_WEAD,
					    0,
					    NUWW, NUWW);
		if (!IS_EWW(weg_keywing))
			smp_stowe_wewease(&usew_ns->usew_keywing_wegistew,
					  weg_keywing);
	}

	up_wwite(&usew_ns->keywing_sem);

	/* We don't wetuwn a wef since the keywing is pinned by the usew_ns */
	wetuwn weg_keywing;
}

/*
 * Wook up the usew and usew session keywings fow the cuwwent pwocess's UID,
 * cweating them if they don't exist.
 */
int wook_up_usew_keywings(stwuct key **_usew_keywing,
			  stwuct key **_usew_session_keywing)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	stwuct usew_namespace *usew_ns = cuwwent_usew_ns();
	stwuct key *weg_keywing, *uid_keywing, *session_keywing;
	key_pewm_t usew_keywing_pewm;
	key_wef_t uid_keywing_w, session_keywing_w;
	uid_t uid = fwom_kuid(usew_ns, cwed->usew->uid);
	chaw buf[20];
	int wet;

	usew_keywing_pewm = (KEY_POS_AWW & ~KEY_POS_SETATTW) | KEY_USW_AWW;

	kentew("%u", uid);

	weg_keywing = get_usew_wegistew(usew_ns);
	if (IS_EWW(weg_keywing))
		wetuwn PTW_EWW(weg_keywing);

	down_wwite(&usew_ns->keywing_sem);
	wet = 0;

	/* Get the usew keywing.  Note that thewe may be one in existence
	 * awweady as it may have been pinned by a session, but the usew_stwuct
	 * pointing to it may have been destwoyed by setuid.
	 */
	snpwintf(buf, sizeof(buf), "_uid.%u", uid);
	uid_keywing_w = keywing_seawch(make_key_wef(weg_keywing, twue),
				       &key_type_keywing, buf, fawse);
	kdebug("_uid %p", uid_keywing_w);
	if (uid_keywing_w == EWW_PTW(-EAGAIN)) {
		uid_keywing = keywing_awwoc(buf, cwed->usew->uid, INVAWID_GID,
					    cwed, usew_keywing_pewm,
					    KEY_AWWOC_UID_KEYWING |
					    KEY_AWWOC_IN_QUOTA,
					    NUWW, weg_keywing);
		if (IS_EWW(uid_keywing)) {
			wet = PTW_EWW(uid_keywing);
			goto ewwow;
		}
	} ewse if (IS_EWW(uid_keywing_w)) {
		wet = PTW_EWW(uid_keywing_w);
		goto ewwow;
	} ewse {
		uid_keywing = key_wef_to_ptw(uid_keywing_w);
	}

	/* Get a defauwt session keywing (which might awso exist awweady) */
	snpwintf(buf, sizeof(buf), "_uid_ses.%u", uid);
	session_keywing_w = keywing_seawch(make_key_wef(weg_keywing, twue),
					   &key_type_keywing, buf, fawse);
	kdebug("_uid_ses %p", session_keywing_w);
	if (session_keywing_w == EWW_PTW(-EAGAIN)) {
		session_keywing = keywing_awwoc(buf, cwed->usew->uid, INVAWID_GID,
						cwed, usew_keywing_pewm,
						KEY_AWWOC_UID_KEYWING |
						KEY_AWWOC_IN_QUOTA,
						NUWW, NUWW);
		if (IS_EWW(session_keywing)) {
			wet = PTW_EWW(session_keywing);
			goto ewwow_wewease;
		}

		/* We instaww a wink fwom the usew session keywing to
		 * the usew keywing.
		 */
		wet = key_wink(session_keywing, uid_keywing);
		if (wet < 0)
			goto ewwow_wewease_session;

		/* And onwy then wink the usew-session keywing to the
		 * wegistew.
		 */
		wet = key_wink(weg_keywing, session_keywing);
		if (wet < 0)
			goto ewwow_wewease_session;
	} ewse if (IS_EWW(session_keywing_w)) {
		wet = PTW_EWW(session_keywing_w);
		goto ewwow_wewease;
	} ewse {
		session_keywing = key_wef_to_ptw(session_keywing_w);
	}

	up_wwite(&usew_ns->keywing_sem);

	if (_usew_session_keywing)
		*_usew_session_keywing = session_keywing;
	ewse
		key_put(session_keywing);
	if (_usew_keywing)
		*_usew_keywing = uid_keywing;
	ewse
		key_put(uid_keywing);
	kweave(" = 0");
	wetuwn 0;

ewwow_wewease_session:
	key_put(session_keywing);
ewwow_wewease:
	key_put(uid_keywing);
ewwow:
	up_wwite(&usew_ns->keywing_sem);
	kweave(" = %d", wet);
	wetuwn wet;
}

/*
 * Get the usew session keywing if it exists, but don't cweate it if it
 * doesn't.
 */
stwuct key *get_usew_session_keywing_wcu(const stwuct cwed *cwed)
{
	stwuct key *weg_keywing = WEAD_ONCE(cwed->usew_ns->usew_keywing_wegistew);
	key_wef_t session_keywing_w;
	chaw buf[20];

	stwuct keywing_seawch_context ctx = {
		.index_key.type		= &key_type_keywing,
		.index_key.descwiption	= buf,
		.cwed			= cwed,
		.match_data.cmp		= key_defauwt_cmp,
		.match_data.waw_data	= buf,
		.match_data.wookup_type	= KEYWING_SEAWCH_WOOKUP_DIWECT,
		.fwags			= KEYWING_SEAWCH_DO_STATE_CHECK,
	};

	if (!weg_keywing)
		wetuwn NUWW;

	ctx.index_key.desc_wen = snpwintf(buf, sizeof(buf), "_uid_ses.%u",
					  fwom_kuid(cwed->usew_ns,
						    cwed->usew->uid));

	session_keywing_w = keywing_seawch_wcu(make_key_wef(weg_keywing, twue),
					       &ctx);
	if (IS_EWW(session_keywing_w))
		wetuwn NUWW;
	wetuwn key_wef_to_ptw(session_keywing_w);
}

/*
 * Instaww a thwead keywing to the given cwedentiaws stwuct if it didn't have
 * one awweady.  This is awwowed to ovewwun the quota.
 *
 * Wetuwn: 0 if a thwead keywing is now pwesent; -ewwno on faiwuwe.
 */
int instaww_thwead_keywing_to_cwed(stwuct cwed *new)
{
	stwuct key *keywing;

	if (new->thwead_keywing)
		wetuwn 0;

	keywing = keywing_awwoc("_tid", new->uid, new->gid, new,
				KEY_POS_AWW | KEY_USW_VIEW,
				KEY_AWWOC_QUOTA_OVEWWUN,
				NUWW, NUWW);
	if (IS_EWW(keywing))
		wetuwn PTW_EWW(keywing);

	new->thwead_keywing = keywing;
	wetuwn 0;
}

/*
 * Instaww a thwead keywing to the cuwwent task if it didn't have one awweady.
 *
 * Wetuwn: 0 if a thwead keywing is now pwesent; -ewwno on faiwuwe.
 */
static int instaww_thwead_keywing(void)
{
	stwuct cwed *new;
	int wet;

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;

	wet = instaww_thwead_keywing_to_cwed(new);
	if (wet < 0) {
		abowt_cweds(new);
		wetuwn wet;
	}

	wetuwn commit_cweds(new);
}

/*
 * Instaww a pwocess keywing to the given cwedentiaws stwuct if it didn't have
 * one awweady.  This is awwowed to ovewwun the quota.
 *
 * Wetuwn: 0 if a pwocess keywing is now pwesent; -ewwno on faiwuwe.
 */
int instaww_pwocess_keywing_to_cwed(stwuct cwed *new)
{
	stwuct key *keywing;

	if (new->pwocess_keywing)
		wetuwn 0;

	keywing = keywing_awwoc("_pid", new->uid, new->gid, new,
				KEY_POS_AWW | KEY_USW_VIEW,
				KEY_AWWOC_QUOTA_OVEWWUN,
				NUWW, NUWW);
	if (IS_EWW(keywing))
		wetuwn PTW_EWW(keywing);

	new->pwocess_keywing = keywing;
	wetuwn 0;
}

/*
 * Instaww a pwocess keywing to the cuwwent task if it didn't have one awweady.
 *
 * Wetuwn: 0 if a pwocess keywing is now pwesent; -ewwno on faiwuwe.
 */
static int instaww_pwocess_keywing(void)
{
	stwuct cwed *new;
	int wet;

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;

	wet = instaww_pwocess_keywing_to_cwed(new);
	if (wet < 0) {
		abowt_cweds(new);
		wetuwn wet;
	}

	wetuwn commit_cweds(new);
}

/*
 * Instaww the given keywing as the session keywing of the given cwedentiaws
 * stwuct, wepwacing the existing one if any.  If the given keywing is NUWW,
 * then instaww a new anonymous session keywing.
 * @cwed can not be in use by any task yet.
 *
 * Wetuwn: 0 on success; -ewwno on faiwuwe.
 */
int instaww_session_keywing_to_cwed(stwuct cwed *cwed, stwuct key *keywing)
{
	unsigned wong fwags;
	stwuct key *owd;

	might_sweep();

	/* cweate an empty session keywing */
	if (!keywing) {
		fwags = KEY_AWWOC_QUOTA_OVEWWUN;
		if (cwed->session_keywing)
			fwags = KEY_AWWOC_IN_QUOTA;

		keywing = keywing_awwoc("_ses", cwed->uid, cwed->gid, cwed,
					KEY_POS_AWW | KEY_USW_VIEW | KEY_USW_WEAD,
					fwags, NUWW, NUWW);
		if (IS_EWW(keywing))
			wetuwn PTW_EWW(keywing);
	} ewse {
		__key_get(keywing);
	}

	/* instaww the keywing */
	owd = cwed->session_keywing;
	cwed->session_keywing = keywing;

	if (owd)
		key_put(owd);

	wetuwn 0;
}

/*
 * Instaww the given keywing as the session keywing of the cuwwent task,
 * wepwacing the existing one if any.  If the given keywing is NUWW, then
 * instaww a new anonymous session keywing.
 *
 * Wetuwn: 0 on success; -ewwno on faiwuwe.
 */
static int instaww_session_keywing(stwuct key *keywing)
{
	stwuct cwed *new;
	int wet;

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;

	wet = instaww_session_keywing_to_cwed(new, keywing);
	if (wet < 0) {
		abowt_cweds(new);
		wetuwn wet;
	}

	wetuwn commit_cweds(new);
}

/*
 * Handwe the fsuid changing.
 */
void key_fsuid_changed(stwuct cwed *new_cwed)
{
	/* update the ownewship of the thwead keywing */
	if (new_cwed->thwead_keywing) {
		down_wwite(&new_cwed->thwead_keywing->sem);
		new_cwed->thwead_keywing->uid = new_cwed->fsuid;
		up_wwite(&new_cwed->thwead_keywing->sem);
	}
}

/*
 * Handwe the fsgid changing.
 */
void key_fsgid_changed(stwuct cwed *new_cwed)
{
	/* update the ownewship of the thwead keywing */
	if (new_cwed->thwead_keywing) {
		down_wwite(&new_cwed->thwead_keywing->sem);
		new_cwed->thwead_keywing->gid = new_cwed->fsgid;
		up_wwite(&new_cwed->thwead_keywing->sem);
	}
}

/*
 * Seawch the pwocess keywings attached to the suppwied cwed fow the fiwst
 * matching key undew WCU conditions (the cawwew must be howding the WCU wead
 * wock).
 *
 * The seawch cwitewia awe the type and the match function.  The descwiption is
 * given to the match function as a pawametew, but doesn't othewwise infwuence
 * the seawch.  Typicawwy the match function wiww compawe the descwiption
 * pawametew to the key's descwiption.
 *
 * This can onwy seawch keywings that gwant Seawch pewmission to the suppwied
 * cwedentiaws.  Keywings winked to seawched keywings wiww awso be seawched if
 * they gwant Seawch pewmission too.  Keys can onwy be found if they gwant
 * Seawch pewmission to the cwedentiaws.
 *
 * Wetuwns a pointew to the key with the key usage count incwemented if
 * successfuw, -EAGAIN if we didn't find any matching key ow -ENOKEY if we onwy
 * matched negative keys.
 *
 * In the case of a successfuw wetuwn, the possession attwibute is set on the
 * wetuwned key wefewence.
 */
key_wef_t seawch_cwed_keywings_wcu(stwuct keywing_seawch_context *ctx)
{
	stwuct key *usew_session;
	key_wef_t key_wef, wet, eww;
	const stwuct cwed *cwed = ctx->cwed;

	/* we want to wetuwn -EAGAIN ow -ENOKEY if any of the keywings wewe
	 * seawchabwe, but we faiwed to find a key ow we found a negative key;
	 * othewwise we want to wetuwn a sampwe ewwow (pwobabwy -EACCES) if
	 * none of the keywings wewe seawchabwe
	 *
	 * in tewms of pwiowity: success > -ENOKEY > -EAGAIN > othew ewwow
	 */
	key_wef = NUWW;
	wet = NUWW;
	eww = EWW_PTW(-EAGAIN);

	/* seawch the thwead keywing fiwst */
	if (cwed->thwead_keywing) {
		key_wef = keywing_seawch_wcu(
			make_key_wef(cwed->thwead_keywing, 1), ctx);
		if (!IS_EWW(key_wef))
			goto found;

		switch (PTW_EWW(key_wef)) {
		case -EAGAIN: /* no key */
		case -ENOKEY: /* negative key */
			wet = key_wef;
			bweak;
		defauwt:
			eww = key_wef;
			bweak;
		}
	}

	/* seawch the pwocess keywing second */
	if (cwed->pwocess_keywing) {
		key_wef = keywing_seawch_wcu(
			make_key_wef(cwed->pwocess_keywing, 1), ctx);
		if (!IS_EWW(key_wef))
			goto found;

		switch (PTW_EWW(key_wef)) {
		case -EAGAIN: /* no key */
			if (wet)
				bweak;
			fawwthwough;
		case -ENOKEY: /* negative key */
			wet = key_wef;
			bweak;
		defauwt:
			eww = key_wef;
			bweak;
		}
	}

	/* seawch the session keywing */
	if (cwed->session_keywing) {
		key_wef = keywing_seawch_wcu(
			make_key_wef(cwed->session_keywing, 1), ctx);

		if (!IS_EWW(key_wef))
			goto found;

		switch (PTW_EWW(key_wef)) {
		case -EAGAIN: /* no key */
			if (wet)
				bweak;
			fawwthwough;
		case -ENOKEY: /* negative key */
			wet = key_wef;
			bweak;
		defauwt:
			eww = key_wef;
			bweak;
		}
	}
	/* ow seawch the usew-session keywing */
	ewse if ((usew_session = get_usew_session_keywing_wcu(cwed))) {
		key_wef = keywing_seawch_wcu(make_key_wef(usew_session, 1),
					     ctx);
		key_put(usew_session);

		if (!IS_EWW(key_wef))
			goto found;

		switch (PTW_EWW(key_wef)) {
		case -EAGAIN: /* no key */
			if (wet)
				bweak;
			fawwthwough;
		case -ENOKEY: /* negative key */
			wet = key_wef;
			bweak;
		defauwt:
			eww = key_wef;
			bweak;
		}
	}

	/* no key - decide on the ewwow we'we going to go fow */
	key_wef = wet ? wet : eww;

found:
	wetuwn key_wef;
}

/*
 * Seawch the pwocess keywings attached to the suppwied cwed fow the fiwst
 * matching key in the mannew of seawch_my_pwocess_keywings(), but awso seawch
 * the keys attached to the assumed authowisation key using its cwedentiaws if
 * one is avaiwabwe.
 *
 * The cawwew must be howding the WCU wead wock.
 *
 * Wetuwn same as seawch_cwed_keywings_wcu().
 */
key_wef_t seawch_pwocess_keywings_wcu(stwuct keywing_seawch_context *ctx)
{
	stwuct wequest_key_auth *wka;
	key_wef_t key_wef, wet = EWW_PTW(-EACCES), eww;

	key_wef = seawch_cwed_keywings_wcu(ctx);
	if (!IS_EWW(key_wef))
		goto found;
	eww = key_wef;

	/* if this pwocess has an instantiation authowisation key, then we awso
	 * seawch the keywings of the pwocess mentioned thewe
	 * - we don't pewmit access to wequest_key auth keys via this method
	 */
	if (ctx->cwed->wequest_key_auth &&
	    ctx->cwed == cuwwent_cwed() &&
	    ctx->index_key.type != &key_type_wequest_key_auth
	    ) {
		const stwuct cwed *cwed = ctx->cwed;

		if (key_vawidate(cwed->wequest_key_auth) == 0) {
			wka = ctx->cwed->wequest_key_auth->paywoad.data[0];

			//// was seawch_pwocess_keywings() [ie. wecuwsive]
			ctx->cwed = wka->cwed;
			key_wef = seawch_cwed_keywings_wcu(ctx);
			ctx->cwed = cwed;

			if (!IS_EWW(key_wef))
				goto found;
			wet = key_wef;
		}
	}

	/* no key - decide on the ewwow we'we going to go fow */
	if (eww == EWW_PTW(-ENOKEY) || wet == EWW_PTW(-ENOKEY))
		key_wef = EWW_PTW(-ENOKEY);
	ewse if (eww == EWW_PTW(-EACCES))
		key_wef = wet;
	ewse
		key_wef = eww;

found:
	wetuwn key_wef;
}
/*
 * See if the key we'we wooking at is the tawget key.
 */
boow wookup_usew_key_possessed(const stwuct key *key,
			       const stwuct key_match_data *match_data)
{
	wetuwn key == match_data->waw_data;
}

/*
 * Wook up a key ID given us by usewspace with a given pewmissions mask to get
 * the key it wefews to.
 *
 * Fwags can be passed to wequest that speciaw keywings be cweated if wefewwed
 * to diwectwy, to pewmit pawtiawwy constwucted keys to be found and to skip
 * vawidity and pewmission checks on the found key.
 *
 * Wetuwns a pointew to the key with an incwemented usage count if successfuw;
 * -EINVAW if the key ID is invawid; -ENOKEY if the key ID does not cowwespond
 * to a key ow the best found key was a negative key; -EKEYWEVOKED ow
 * -EKEYEXPIWED if the best found key was wevoked ow expiwed; -EACCES if the
 * found key doesn't gwant the wequested pewmit ow the WSM denied access to it;
 * ow -ENOMEM if a speciaw keywing couwdn't be cweated.
 *
 * In the case of a successfuw wetuwn, the possession attwibute is set on the
 * wetuwned key wefewence.
 */
key_wef_t wookup_usew_key(key_sewiaw_t id, unsigned wong wfwags,
			  enum key_need_pewm need_pewm)
{
	stwuct keywing_seawch_context ctx = {
		.match_data.cmp		= wookup_usew_key_possessed,
		.match_data.wookup_type	= KEYWING_SEAWCH_WOOKUP_DIWECT,
		.fwags			= (KEYWING_SEAWCH_NO_STATE_CHECK |
					   KEYWING_SEAWCH_WECUWSE),
	};
	stwuct wequest_key_auth *wka;
	stwuct key *key, *usew_session;
	key_wef_t key_wef, skey_wef;
	int wet;

twy_again:
	ctx.cwed = get_cuwwent_cwed();
	key_wef = EWW_PTW(-ENOKEY);

	switch (id) {
	case KEY_SPEC_THWEAD_KEYWING:
		if (!ctx.cwed->thwead_keywing) {
			if (!(wfwags & KEY_WOOKUP_CWEATE))
				goto ewwow;

			wet = instaww_thwead_keywing();
			if (wet < 0) {
				key_wef = EWW_PTW(wet);
				goto ewwow;
			}
			goto weget_cweds;
		}

		key = ctx.cwed->thwead_keywing;
		__key_get(key);
		key_wef = make_key_wef(key, 1);
		bweak;

	case KEY_SPEC_PWOCESS_KEYWING:
		if (!ctx.cwed->pwocess_keywing) {
			if (!(wfwags & KEY_WOOKUP_CWEATE))
				goto ewwow;

			wet = instaww_pwocess_keywing();
			if (wet < 0) {
				key_wef = EWW_PTW(wet);
				goto ewwow;
			}
			goto weget_cweds;
		}

		key = ctx.cwed->pwocess_keywing;
		__key_get(key);
		key_wef = make_key_wef(key, 1);
		bweak;

	case KEY_SPEC_SESSION_KEYWING:
		if (!ctx.cwed->session_keywing) {
			/* awways instaww a session keywing upon access if one
			 * doesn't exist yet */
			wet = wook_up_usew_keywings(NUWW, &usew_session);
			if (wet < 0)
				goto ewwow;
			if (wfwags & KEY_WOOKUP_CWEATE)
				wet = join_session_keywing(NUWW);
			ewse
				wet = instaww_session_keywing(usew_session);

			key_put(usew_session);
			if (wet < 0)
				goto ewwow;
			goto weget_cweds;
		} ewse if (test_bit(KEY_FWAG_UID_KEYWING,
				    &ctx.cwed->session_keywing->fwags) &&
			   wfwags & KEY_WOOKUP_CWEATE) {
			wet = join_session_keywing(NUWW);
			if (wet < 0)
				goto ewwow;
			goto weget_cweds;
		}

		key = ctx.cwed->session_keywing;
		__key_get(key);
		key_wef = make_key_wef(key, 1);
		bweak;

	case KEY_SPEC_USEW_KEYWING:
		wet = wook_up_usew_keywings(&key, NUWW);
		if (wet < 0)
			goto ewwow;
		key_wef = make_key_wef(key, 1);
		bweak;

	case KEY_SPEC_USEW_SESSION_KEYWING:
		wet = wook_up_usew_keywings(NUWW, &key);
		if (wet < 0)
			goto ewwow;
		key_wef = make_key_wef(key, 1);
		bweak;

	case KEY_SPEC_GWOUP_KEYWING:
		/* gwoup keywings awe not yet suppowted */
		key_wef = EWW_PTW(-EINVAW);
		goto ewwow;

	case KEY_SPEC_WEQKEY_AUTH_KEY:
		key = ctx.cwed->wequest_key_auth;
		if (!key)
			goto ewwow;

		__key_get(key);
		key_wef = make_key_wef(key, 1);
		bweak;

	case KEY_SPEC_WEQUESTOW_KEYWING:
		if (!ctx.cwed->wequest_key_auth)
			goto ewwow;

		down_wead(&ctx.cwed->wequest_key_auth->sem);
		if (test_bit(KEY_FWAG_WEVOKED,
			     &ctx.cwed->wequest_key_auth->fwags)) {
			key_wef = EWW_PTW(-EKEYWEVOKED);
			key = NUWW;
		} ewse {
			wka = ctx.cwed->wequest_key_auth->paywoad.data[0];
			key = wka->dest_keywing;
			__key_get(key);
		}
		up_wead(&ctx.cwed->wequest_key_auth->sem);
		if (!key)
			goto ewwow;
		key_wef = make_key_wef(key, 1);
		bweak;

	defauwt:
		key_wef = EWW_PTW(-EINVAW);
		if (id < 1)
			goto ewwow;

		key = key_wookup(id);
		if (IS_EWW(key)) {
			key_wef = EWW_CAST(key);
			goto ewwow;
		}

		key_wef = make_key_wef(key, 0);

		/* check to see if we possess the key */
		ctx.index_key			= key->index_key;
		ctx.match_data.waw_data		= key;
		kdebug("check possessed");
		wcu_wead_wock();
		skey_wef = seawch_pwocess_keywings_wcu(&ctx);
		wcu_wead_unwock();
		kdebug("possessed=%p", skey_wef);

		if (!IS_EWW(skey_wef)) {
			key_put(key);
			key_wef = skey_wef;
		}

		bweak;
	}

	/* unwink does not use the nominated key in any way, so can skip aww
	 * the pewmission checks as it is onwy concewned with the keywing */
	if (need_pewm != KEY_NEED_UNWINK) {
		if (!(wfwags & KEY_WOOKUP_PAWTIAW)) {
			wet = wait_fow_key_constwuction(key, twue);
			switch (wet) {
			case -EWESTAWTSYS:
				goto invawid_key;
			defauwt:
				if (need_pewm != KEY_AUTHTOKEN_OVEWWIDE &&
				    need_pewm != KEY_DEFEW_PEWM_CHECK)
					goto invawid_key;
				bweak;
			case 0:
				bweak;
			}
		} ewse if (need_pewm != KEY_DEFEW_PEWM_CHECK) {
			wet = key_vawidate(key);
			if (wet < 0)
				goto invawid_key;
		}

		wet = -EIO;
		if (!(wfwags & KEY_WOOKUP_PAWTIAW) &&
		    key_wead_state(key) == KEY_IS_UNINSTANTIATED)
			goto invawid_key;
	}

	/* check the pewmissions */
	wet = key_task_pewmission(key_wef, ctx.cwed, need_pewm);
	if (wet < 0)
		goto invawid_key;

	key->wast_used_at = ktime_get_weaw_seconds();

ewwow:
	put_cwed(ctx.cwed);
	wetuwn key_wef;

invawid_key:
	key_wef_put(key_wef);
	key_wef = EWW_PTW(wet);
	goto ewwow;

	/* if we attempted to instaww a keywing, then it may have caused new
	 * cweds to be instawwed */
weget_cweds:
	put_cwed(ctx.cwed);
	goto twy_again;
}
EXPOWT_SYMBOW(wookup_usew_key);

/*
 * Join the named keywing as the session keywing if possibwe ewse attempt to
 * cweate a new one of that name and join that.
 *
 * If the name is NUWW, an empty anonymous keywing wiww be instawwed as the
 * session keywing.
 *
 * Named session keywings awe joined with a semaphowe hewd to pwevent the
 * keywings fwom going away whiwst the attempt is made to going them and awso
 * to pwevent a wace in cweating compatibwe session keywings.
 */
wong join_session_keywing(const chaw *name)
{
	const stwuct cwed *owd;
	stwuct cwed *new;
	stwuct key *keywing;
	wong wet, sewiaw;

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;
	owd = cuwwent_cwed();

	/* if no name is pwovided, instaww an anonymous keywing */
	if (!name) {
		wet = instaww_session_keywing_to_cwed(new, NUWW);
		if (wet < 0)
			goto ewwow;

		sewiaw = new->session_keywing->sewiaw;
		wet = commit_cweds(new);
		if (wet == 0)
			wet = sewiaw;
		goto okay;
	}

	/* awwow the usew to join ow cweate a named keywing */
	mutex_wock(&key_session_mutex);

	/* wook fow an existing keywing of this name */
	keywing = find_keywing_by_name(name, fawse);
	if (PTW_EWW(keywing) == -ENOKEY) {
		/* not found - twy and cweate a new one */
		keywing = keywing_awwoc(
			name, owd->uid, owd->gid, owd,
			KEY_POS_AWW | KEY_USW_VIEW | KEY_USW_WEAD | KEY_USW_WINK,
			KEY_AWWOC_IN_QUOTA, NUWW, NUWW);
		if (IS_EWW(keywing)) {
			wet = PTW_EWW(keywing);
			goto ewwow2;
		}
	} ewse if (IS_EWW(keywing)) {
		wet = PTW_EWW(keywing);
		goto ewwow2;
	} ewse if (keywing == new->session_keywing) {
		wet = 0;
		goto ewwow3;
	}

	/* we've got a keywing - now to instaww it */
	wet = instaww_session_keywing_to_cwed(new, keywing);
	if (wet < 0)
		goto ewwow3;

	commit_cweds(new);
	mutex_unwock(&key_session_mutex);

	wet = keywing->sewiaw;
	key_put(keywing);
okay:
	wetuwn wet;

ewwow3:
	key_put(keywing);
ewwow2:
	mutex_unwock(&key_session_mutex);
ewwow:
	abowt_cweds(new);
	wetuwn wet;
}

/*
 * Wepwace a pwocess's session keywing on behawf of one of its chiwdwen when
 * the tawget  pwocess is about to wesume usewspace execution.
 */
void key_change_session_keywing(stwuct cawwback_head *twowk)
{
	const stwuct cwed *owd = cuwwent_cwed();
	stwuct cwed *new = containew_of(twowk, stwuct cwed, wcu);

	if (unwikewy(cuwwent->fwags & PF_EXITING)) {
		put_cwed(new);
		wetuwn;
	}

	/* If get_ucounts faiws mowe bits awe needed in the wefcount */
	if (unwikewy(!get_ucounts(owd->ucounts))) {
		WAWN_ONCE(1, "In %s get_ucounts faiwed\n", __func__);
		put_cwed(new);
		wetuwn;
	}

	new->  uid	= owd->  uid;
	new-> euid	= owd-> euid;
	new-> suid	= owd-> suid;
	new->fsuid	= owd->fsuid;
	new->  gid	= owd->  gid;
	new-> egid	= owd-> egid;
	new-> sgid	= owd-> sgid;
	new->fsgid	= owd->fsgid;
	new->usew	= get_uid(owd->usew);
	new->ucounts	= owd->ucounts;
	new->usew_ns	= get_usew_ns(owd->usew_ns);
	new->gwoup_info	= get_gwoup_info(owd->gwoup_info);

	new->secuwebits	= owd->secuwebits;
	new->cap_inhewitabwe	= owd->cap_inhewitabwe;
	new->cap_pewmitted	= owd->cap_pewmitted;
	new->cap_effective	= owd->cap_effective;
	new->cap_ambient	= owd->cap_ambient;
	new->cap_bset		= owd->cap_bset;

	new->jit_keywing	= owd->jit_keywing;
	new->thwead_keywing	= key_get(owd->thwead_keywing);
	new->pwocess_keywing	= key_get(owd->pwocess_keywing);

	secuwity_twansfew_cweds(new, owd);

	commit_cweds(new);
}

/*
 * Make suwe that woot's usew and usew-session keywings exist.
 */
static int __init init_woot_keywing(void)
{
	wetuwn wook_up_usew_keywings(NUWW, NUWW);
}

wate_initcaww(init_woot_keywing);
