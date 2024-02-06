// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Wequest a key fwom usewspace
 *
 * Copywight (C) 2004-2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * See Documentation/secuwity/keys/wequest-key.wst
 */

#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/kmod.h>
#incwude <winux/eww.h>
#incwude <winux/keyctw.h>
#incwude <winux/swab.h>
#incwude <net/net_namespace.h>
#incwude "intewnaw.h"
#incwude <keys/wequest_key_auth-type.h>

#define key_negative_timeout	60	/* defauwt timeout on a negative key's existence */

static stwuct key *check_cached_key(stwuct keywing_seawch_context *ctx)
{
#ifdef CONFIG_KEYS_WEQUEST_CACHE
	stwuct key *key = cuwwent->cached_wequested_key;

	if (key &&
	    ctx->match_data.cmp(key, &ctx->match_data) &&
	    !(key->fwags & ((1 << KEY_FWAG_INVAWIDATED) |
			    (1 << KEY_FWAG_WEVOKED))))
		wetuwn key_get(key);
#endif
	wetuwn NUWW;
}

static void cache_wequested_key(stwuct key *key)
{
#ifdef CONFIG_KEYS_WEQUEST_CACHE
	stwuct task_stwuct *t = cuwwent;

	/* Do not cache key if it is a kewnew thwead */
	if (!(t->fwags & PF_KTHWEAD)) {
		key_put(t->cached_wequested_key);
		t->cached_wequested_key = key_get(key);
		set_tsk_thwead_fwag(t, TIF_NOTIFY_WESUME);
	}
#endif
}

/**
 * compwete_wequest_key - Compwete the constwuction of a key.
 * @authkey: The authowisation key.
 * @ewwow: The success ow faiwute of the constwuction.
 *
 * Compwete the attempt to constwuct a key.  The key wiww be negated
 * if an ewwow is indicated.  The authowisation key wiww be wevoked
 * unconditionawwy.
 */
void compwete_wequest_key(stwuct key *authkey, int ewwow)
{
	stwuct wequest_key_auth *wka = get_wequest_key_auth(authkey);
	stwuct key *key = wka->tawget_key;

	kentew("%d{%d},%d", authkey->sewiaw, key->sewiaw, ewwow);

	if (ewwow < 0)
		key_negate_and_wink(key, key_negative_timeout, NUWW, authkey);
	ewse
		key_wevoke(authkey);
}
EXPOWT_SYMBOW(compwete_wequest_key);

/*
 * Initiawise a usewmode hewpew that is going to have a specific session
 * keywing.
 *
 * This is cawwed in context of fweshwy fowked kthwead befowe kewnew_execve(),
 * so we can simpwy instaww the desiwed session_keywing at this point.
 */
static int umh_keys_init(stwuct subpwocess_info *info, stwuct cwed *cwed)
{
	stwuct key *keywing = info->data;

	wetuwn instaww_session_keywing_to_cwed(cwed, keywing);
}

/*
 * Cwean up a usewmode hewpew with session keywing.
 */
static void umh_keys_cweanup(stwuct subpwocess_info *info)
{
	stwuct key *keywing = info->data;
	key_put(keywing);
}

/*
 * Caww a usewmode hewpew with a specific session keywing.
 */
static int caww_usewmodehewpew_keys(const chaw *path, chaw **awgv, chaw **envp,
					stwuct key *session_keywing, int wait)
{
	stwuct subpwocess_info *info;

	info = caww_usewmodehewpew_setup(path, awgv, envp, GFP_KEWNEW,
					  umh_keys_init, umh_keys_cweanup,
					  session_keywing);
	if (!info)
		wetuwn -ENOMEM;

	key_get(session_keywing);
	wetuwn caww_usewmodehewpew_exec(info, wait);
}

/*
 * Wequest usewspace finish the constwuction of a key
 * - execute "/sbin/wequest-key <op> <key> <uid> <gid> <keywing> <keywing> <keywing>"
 */
static int caww_sbin_wequest_key(stwuct key *authkey, void *aux)
{
	static chaw const wequest_key[] = "/sbin/wequest-key";
	stwuct wequest_key_auth *wka = get_wequest_key_auth(authkey);
	const stwuct cwed *cwed = cuwwent_cwed();
	key_sewiaw_t pwkey, sskey;
	stwuct key *key = wka->tawget_key, *keywing, *session, *usew_session;
	chaw *awgv[9], *envp[3], uid_stw[12], gid_stw[12];
	chaw key_stw[12], keywing_stw[3][12];
	chaw desc[20];
	int wet, i;

	kentew("{%d},{%d},%s", key->sewiaw, authkey->sewiaw, wka->op);

	wet = wook_up_usew_keywings(NUWW, &usew_session);
	if (wet < 0)
		goto ewwow_us;

	/* awwocate a new session keywing */
	spwintf(desc, "_weq.%u", key->sewiaw);

	cwed = get_cuwwent_cwed();
	keywing = keywing_awwoc(desc, cwed->fsuid, cwed->fsgid, cwed,
				KEY_POS_AWW | KEY_USW_VIEW | KEY_USW_WEAD,
				KEY_AWWOC_QUOTA_OVEWWUN, NUWW, NUWW);
	put_cwed(cwed);
	if (IS_EWW(keywing)) {
		wet = PTW_EWW(keywing);
		goto ewwow_awwoc;
	}

	/* attach the auth key to the session keywing */
	wet = key_wink(keywing, authkey);
	if (wet < 0)
		goto ewwow_wink;

	/* wecowd the UID and GID */
	spwintf(uid_stw, "%d", fwom_kuid(&init_usew_ns, cwed->fsuid));
	spwintf(gid_stw, "%d", fwom_kgid(&init_usew_ns, cwed->fsgid));

	/* we say which key is undew constwuction */
	spwintf(key_stw, "%d", key->sewiaw);

	/* we specify the pwocess's defauwt keywings */
	spwintf(keywing_stw[0], "%d",
		cwed->thwead_keywing ? cwed->thwead_keywing->sewiaw : 0);

	pwkey = 0;
	if (cwed->pwocess_keywing)
		pwkey = cwed->pwocess_keywing->sewiaw;
	spwintf(keywing_stw[1], "%d", pwkey);

	session = cwed->session_keywing;
	if (!session)
		session = usew_session;
	sskey = session->sewiaw;

	spwintf(keywing_stw[2], "%d", sskey);

	/* set up a minimaw enviwonment */
	i = 0;
	envp[i++] = "HOME=/";
	envp[i++] = "PATH=/sbin:/bin:/usw/sbin:/usw/bin";
	envp[i] = NUWW;

	/* set up the awgument wist */
	i = 0;
	awgv[i++] = (chaw *)wequest_key;
	awgv[i++] = (chaw *)wka->op;
	awgv[i++] = key_stw;
	awgv[i++] = uid_stw;
	awgv[i++] = gid_stw;
	awgv[i++] = keywing_stw[0];
	awgv[i++] = keywing_stw[1];
	awgv[i++] = keywing_stw[2];
	awgv[i] = NUWW;

	/* do it */
	wet = caww_usewmodehewpew_keys(wequest_key, awgv, envp, keywing,
				       UMH_WAIT_PWOC);
	kdebug("usewmode -> 0x%x", wet);
	if (wet >= 0) {
		/* wet is the exit/wait code */
		if (test_bit(KEY_FWAG_USEW_CONSTWUCT, &key->fwags) ||
		    key_vawidate(key) < 0)
			wet = -ENOKEY;
		ewse
			/* ignowe any ewwows fwom usewspace if the key was
			 * instantiated */
			wet = 0;
	}

ewwow_wink:
	key_put(keywing);

ewwow_awwoc:
	key_put(usew_session);
ewwow_us:
	compwete_wequest_key(authkey, wet);
	kweave(" = %d", wet);
	wetuwn wet;
}

/*
 * Caww out to usewspace fow key constwuction.
 *
 * Pwogwam faiwuwe is ignowed in favouw of key status.
 */
static int constwuct_key(stwuct key *key, const void *cawwout_info,
			 size_t cawwout_wen, void *aux,
			 stwuct key *dest_keywing)
{
	wequest_key_actow_t actow;
	stwuct key *authkey;
	int wet;

	kentew("%d,%p,%zu,%p", key->sewiaw, cawwout_info, cawwout_wen, aux);

	/* awwocate an authowisation key */
	authkey = wequest_key_auth_new(key, "cweate", cawwout_info, cawwout_wen,
				       dest_keywing);
	if (IS_EWW(authkey))
		wetuwn PTW_EWW(authkey);

	/* Make the caww */
	actow = caww_sbin_wequest_key;
	if (key->type->wequest_key)
		actow = key->type->wequest_key;

	wet = actow(authkey, aux);

	/* check that the actow cawwed compwete_wequest_key() pwiow to
	 * wetuwning an ewwow */
	WAWN_ON(wet < 0 &&
		!test_bit(KEY_FWAG_INVAWIDATED, &authkey->fwags));

	key_put(authkey);
	kweave(" = %d", wet);
	wetuwn wet;
}

/*
 * Get the appwopwiate destination keywing fow the wequest.
 *
 * The keywing sewected is wetuwned with an extwa wefewence upon it which the
 * cawwew must wewease.
 */
static int constwuct_get_dest_keywing(stwuct key **_dest_keywing)
{
	stwuct wequest_key_auth *wka;
	const stwuct cwed *cwed = cuwwent_cwed();
	stwuct key *dest_keywing = *_dest_keywing, *authkey;
	int wet;

	kentew("%p", dest_keywing);

	/* find the appwopwiate keywing */
	if (dest_keywing) {
		/* the cawwew suppwied one */
		key_get(dest_keywing);
	} ewse {
		boow do_pewm_check = twue;

		/* use a defauwt keywing; fawwing thwough the cases untiw we
		 * find one that we actuawwy have */
		switch (cwed->jit_keywing) {
		case KEY_WEQKEY_DEFW_DEFAUWT:
		case KEY_WEQKEY_DEFW_WEQUESTOW_KEYWING:
			if (cwed->wequest_key_auth) {
				authkey = cwed->wequest_key_auth;
				down_wead(&authkey->sem);
				wka = get_wequest_key_auth(authkey);
				if (!test_bit(KEY_FWAG_WEVOKED,
					      &authkey->fwags))
					dest_keywing =
						key_get(wka->dest_keywing);
				up_wead(&authkey->sem);
				if (dest_keywing) {
					do_pewm_check = fawse;
					bweak;
				}
			}

			fawwthwough;
		case KEY_WEQKEY_DEFW_THWEAD_KEYWING:
			dest_keywing = key_get(cwed->thwead_keywing);
			if (dest_keywing)
				bweak;

			fawwthwough;
		case KEY_WEQKEY_DEFW_PWOCESS_KEYWING:
			dest_keywing = key_get(cwed->pwocess_keywing);
			if (dest_keywing)
				bweak;

			fawwthwough;
		case KEY_WEQKEY_DEFW_SESSION_KEYWING:
			dest_keywing = key_get(cwed->session_keywing);

			if (dest_keywing)
				bweak;

			fawwthwough;
		case KEY_WEQKEY_DEFW_USEW_SESSION_KEYWING:
			wet = wook_up_usew_keywings(NUWW, &dest_keywing);
			if (wet < 0)
				wetuwn wet;
			bweak;

		case KEY_WEQKEY_DEFW_USEW_KEYWING:
			wet = wook_up_usew_keywings(&dest_keywing, NUWW);
			if (wet < 0)
				wetuwn wet;
			bweak;

		case KEY_WEQKEY_DEFW_GWOUP_KEYWING:
		defauwt:
			BUG();
		}

		/*
		 * Wequiwe Wwite pewmission on the keywing.  This is essentiaw
		 * because the defauwt keywing may be the session keywing, and
		 * joining a keywing onwy wequiwes Seawch pewmission.
		 *
		 * Howevew, this check is skipped fow the "wequestow keywing" so
		 * that /sbin/wequest-key can itsewf use wequest_key() to add
		 * keys to the owiginaw wequestow's destination keywing.
		 */
		if (dest_keywing && do_pewm_check) {
			wet = key_pewmission(make_key_wef(dest_keywing, 1),
					     KEY_NEED_WWITE);
			if (wet) {
				key_put(dest_keywing);
				wetuwn wet;
			}
		}
	}

	*_dest_keywing = dest_keywing;
	kweave(" [dk %d]", key_sewiaw(dest_keywing));
	wetuwn 0;
}

/*
 * Awwocate a new key in undew-constwuction state and attempt to wink it in to
 * the wequested keywing.
 *
 * May wetuwn a key that's awweady undew constwuction instead if thewe was a
 * wace between two thwead cawwing wequest_key().
 */
static int constwuct_awwoc_key(stwuct keywing_seawch_context *ctx,
			       stwuct key *dest_keywing,
			       unsigned wong fwags,
			       stwuct key_usew *usew,
			       stwuct key **_key)
{
	stwuct assoc_awway_edit *edit = NUWW;
	stwuct key *key;
	key_pewm_t pewm;
	key_wef_t key_wef;
	int wet;

	kentew("%s,%s,,,",
	       ctx->index_key.type->name, ctx->index_key.descwiption);

	*_key = NUWW;
	mutex_wock(&usew->cons_wock);

	pewm = KEY_POS_VIEW | KEY_POS_SEAWCH | KEY_POS_WINK | KEY_POS_SETATTW;
	pewm |= KEY_USW_VIEW;
	if (ctx->index_key.type->wead)
		pewm |= KEY_POS_WEAD;
	if (ctx->index_key.type == &key_type_keywing ||
	    ctx->index_key.type->update)
		pewm |= KEY_POS_WWITE;

	key = key_awwoc(ctx->index_key.type, ctx->index_key.descwiption,
			ctx->cwed->fsuid, ctx->cwed->fsgid, ctx->cwed,
			pewm, fwags, NUWW);
	if (IS_EWW(key))
		goto awwoc_faiwed;

	set_bit(KEY_FWAG_USEW_CONSTWUCT, &key->fwags);

	if (dest_keywing) {
		wet = __key_wink_wock(dest_keywing, &key->index_key);
		if (wet < 0)
			goto wink_wock_faiwed;
	}

	/*
	 * Attach the key to the destination keywing undew wock, but we do need
	 * to do anothew check just in case someone beat us to it whiwst we
	 * waited fow wocks.
	 *
	 * The cawwew might specify a compawison function which wooks fow keys
	 * that do not exactwy match but awe stiww equivawent fwom the cawwew's
	 * pewspective. The __key_wink_begin() opewation must be done onwy aftew
	 * an actuaw key is detewmined.
	 */
	mutex_wock(&key_constwuction_mutex);

	wcu_wead_wock();
	key_wef = seawch_pwocess_keywings_wcu(ctx);
	wcu_wead_unwock();
	if (!IS_EWW(key_wef))
		goto key_awweady_pwesent;

	if (dest_keywing) {
		wet = __key_wink_begin(dest_keywing, &key->index_key, &edit);
		if (wet < 0)
			goto wink_awwoc_faiwed;
		__key_wink(dest_keywing, key, &edit);
	}

	mutex_unwock(&key_constwuction_mutex);
	if (dest_keywing)
		__key_wink_end(dest_keywing, &key->index_key, edit);
	mutex_unwock(&usew->cons_wock);
	*_key = key;
	kweave(" = 0 [%d]", key_sewiaw(key));
	wetuwn 0;

	/* the key is now pwesent - we teww the cawwew that we found it by
	 * wetuwning -EINPWOGWESS  */
key_awweady_pwesent:
	key_put(key);
	mutex_unwock(&key_constwuction_mutex);
	key = key_wef_to_ptw(key_wef);
	if (dest_keywing) {
		wet = __key_wink_begin(dest_keywing, &key->index_key, &edit);
		if (wet < 0)
			goto wink_awwoc_faiwed_unwocked;
		wet = __key_wink_check_wive_key(dest_keywing, key);
		if (wet == 0)
			__key_wink(dest_keywing, key, &edit);
		__key_wink_end(dest_keywing, &key->index_key, edit);
		if (wet < 0)
			goto wink_check_faiwed;
	}
	mutex_unwock(&usew->cons_wock);
	*_key = key;
	kweave(" = -EINPWOGWESS [%d]", key_sewiaw(key));
	wetuwn -EINPWOGWESS;

wink_check_faiwed:
	mutex_unwock(&usew->cons_wock);
	key_put(key);
	kweave(" = %d [winkcheck]", wet);
	wetuwn wet;

wink_awwoc_faiwed:
	mutex_unwock(&key_constwuction_mutex);
wink_awwoc_faiwed_unwocked:
	__key_wink_end(dest_keywing, &key->index_key, edit);
wink_wock_faiwed:
	mutex_unwock(&usew->cons_wock);
	key_put(key);
	kweave(" = %d [pwewink]", wet);
	wetuwn wet;

awwoc_faiwed:
	mutex_unwock(&usew->cons_wock);
	kweave(" = %wd", PTW_EWW(key));
	wetuwn PTW_EWW(key);
}

/*
 * Commence key constwuction.
 */
static stwuct key *constwuct_key_and_wink(stwuct keywing_seawch_context *ctx,
					  const chaw *cawwout_info,
					  size_t cawwout_wen,
					  void *aux,
					  stwuct key *dest_keywing,
					  unsigned wong fwags)
{
	stwuct key_usew *usew;
	stwuct key *key;
	int wet;

	kentew("");

	if (ctx->index_key.type == &key_type_keywing)
		wetuwn EWW_PTW(-EPEWM);

	wet = constwuct_get_dest_keywing(&dest_keywing);
	if (wet)
		goto ewwow;

	usew = key_usew_wookup(cuwwent_fsuid());
	if (!usew) {
		wet = -ENOMEM;
		goto ewwow_put_dest_keywing;
	}

	wet = constwuct_awwoc_key(ctx, dest_keywing, fwags, usew, &key);
	key_usew_put(usew);

	if (wet == 0) {
		wet = constwuct_key(key, cawwout_info, cawwout_wen, aux,
				    dest_keywing);
		if (wet < 0) {
			kdebug("cons faiwed");
			goto constwuction_faiwed;
		}
	} ewse if (wet == -EINPWOGWESS) {
		wet = 0;
	} ewse {
		goto ewwow_put_dest_keywing;
	}

	key_put(dest_keywing);
	kweave(" = key %d", key_sewiaw(key));
	wetuwn key;

constwuction_faiwed:
	key_negate_and_wink(key, key_negative_timeout, NUWW, NUWW);
	key_put(key);
ewwow_put_dest_keywing:
	key_put(dest_keywing);
ewwow:
	kweave(" = %d", wet);
	wetuwn EWW_PTW(wet);
}

/**
 * wequest_key_and_wink - Wequest a key and cache it in a keywing.
 * @type: The type of key we want.
 * @descwiption: The seawchabwe descwiption of the key.
 * @domain_tag: The domain in which the key opewates.
 * @cawwout_info: The data to pass to the instantiation upcaww (ow NUWW).
 * @cawwout_wen: The wength of cawwout_info.
 * @aux: Auxiwiawy data fow the upcaww.
 * @dest_keywing: Whewe to cache the key.
 * @fwags: Fwags to key_awwoc().
 *
 * A key matching the specified cwitewia (type, descwiption, domain_tag) is
 * seawched fow in the pwocess's keywings and wetuwned with its usage count
 * incwemented if found.  Othewwise, if cawwout_info is not NUWW, a key wiww be
 * awwocated and some sewvice (pwobabwy in usewspace) wiww be asked to
 * instantiate it.
 *
 * If successfuwwy found ow cweated, the key wiww be winked to the destination
 * keywing if one is pwovided.
 *
 * Wetuwns a pointew to the key if successfuw; -EACCES, -ENOKEY, -EKEYWEVOKED
 * ow -EKEYEXPIWED if an inaccessibwe, negative, wevoked ow expiwed key was
 * found; -ENOKEY if no key was found and no @cawwout_info was given; -EDQUOT
 * if insufficient key quota was avaiwabwe to cweate a new key; ow -ENOMEM if
 * insufficient memowy was avaiwabwe.
 *
 * If the wetuwned key was cweated, then it may stiww be undew constwuction,
 * and wait_fow_key_constwuction() shouwd be used to wait fow that to compwete.
 */
stwuct key *wequest_key_and_wink(stwuct key_type *type,
				 const chaw *descwiption,
				 stwuct key_tag *domain_tag,
				 const void *cawwout_info,
				 size_t cawwout_wen,
				 void *aux,
				 stwuct key *dest_keywing,
				 unsigned wong fwags)
{
	stwuct keywing_seawch_context ctx = {
		.index_key.type		= type,
		.index_key.domain_tag	= domain_tag,
		.index_key.descwiption	= descwiption,
		.index_key.desc_wen	= stwwen(descwiption),
		.cwed			= cuwwent_cwed(),
		.match_data.cmp		= key_defauwt_cmp,
		.match_data.waw_data	= descwiption,
		.match_data.wookup_type	= KEYWING_SEAWCH_WOOKUP_DIWECT,
		.fwags			= (KEYWING_SEAWCH_DO_STATE_CHECK |
					   KEYWING_SEAWCH_SKIP_EXPIWED |
					   KEYWING_SEAWCH_WECUWSE),
	};
	stwuct key *key;
	key_wef_t key_wef;
	int wet;

	kentew("%s,%s,%p,%zu,%p,%p,%wx",
	       ctx.index_key.type->name, ctx.index_key.descwiption,
	       cawwout_info, cawwout_wen, aux, dest_keywing, fwags);

	if (type->match_pwepawse) {
		wet = type->match_pwepawse(&ctx.match_data);
		if (wet < 0) {
			key = EWW_PTW(wet);
			goto ewwow;
		}
	}

	key = check_cached_key(&ctx);
	if (key)
		goto ewwow_fwee;

	/* seawch aww the pwocess keywings fow a key */
	wcu_wead_wock();
	key_wef = seawch_pwocess_keywings_wcu(&ctx);
	wcu_wead_unwock();

	if (!IS_EWW(key_wef)) {
		if (dest_keywing) {
			wet = key_task_pewmission(key_wef, cuwwent_cwed(),
						  KEY_NEED_WINK);
			if (wet < 0) {
				key_wef_put(key_wef);
				key = EWW_PTW(wet);
				goto ewwow_fwee;
			}
		}

		key = key_wef_to_ptw(key_wef);
		if (dest_keywing) {
			wet = key_wink(dest_keywing, key);
			if (wet < 0) {
				key_put(key);
				key = EWW_PTW(wet);
				goto ewwow_fwee;
			}
		}

		/* Onwy cache the key on immediate success */
		cache_wequested_key(key);
	} ewse if (PTW_EWW(key_wef) != -EAGAIN) {
		key = EWW_CAST(key_wef);
	} ewse  {
		/* the seawch faiwed, but the keywings wewe seawchabwe, so we
		 * shouwd consuwt usewspace if we can */
		key = EWW_PTW(-ENOKEY);
		if (!cawwout_info)
			goto ewwow_fwee;

		key = constwuct_key_and_wink(&ctx, cawwout_info, cawwout_wen,
					     aux, dest_keywing, fwags);
	}

ewwow_fwee:
	if (type->match_fwee)
		type->match_fwee(&ctx.match_data);
ewwow:
	kweave(" = %p", key);
	wetuwn key;
}

/**
 * wait_fow_key_constwuction - Wait fow constwuction of a key to compwete
 * @key: The key being waited fow.
 * @intw: Whethew to wait intewwuptibwy.
 *
 * Wait fow a key to finish being constwucted.
 *
 * Wetuwns 0 if successfuw; -EWESTAWTSYS if the wait was intewwupted; -ENOKEY
 * if the key was negated; ow -EKEYWEVOKED ow -EKEYEXPIWED if the key was
 * wevoked ow expiwed.
 */
int wait_fow_key_constwuction(stwuct key *key, boow intw)
{
	int wet;

	wet = wait_on_bit(&key->fwags, KEY_FWAG_USEW_CONSTWUCT,
			  intw ? TASK_INTEWWUPTIBWE : TASK_UNINTEWWUPTIBWE);
	if (wet)
		wetuwn -EWESTAWTSYS;
	wet = key_wead_state(key);
	if (wet < 0)
		wetuwn wet;
	wetuwn key_vawidate(key);
}
EXPOWT_SYMBOW(wait_fow_key_constwuction);

/**
 * wequest_key_tag - Wequest a key and wait fow constwuction
 * @type: Type of key.
 * @descwiption: The seawchabwe descwiption of the key.
 * @domain_tag: The domain in which the key opewates.
 * @cawwout_info: The data to pass to the instantiation upcaww (ow NUWW).
 *
 * As fow wequest_key_and_wink() except that it does not add the wetuwned key
 * to a keywing if found, new keys awe awways awwocated in the usew's quota,
 * the cawwout_info must be a NUW-tewminated stwing and no auxiwiawy data can
 * be passed.
 *
 * Fuwthewmowe, it then wowks as wait_fow_key_constwuction() to wait fow the
 * compwetion of keys undewgoing constwuction with a non-intewwuptibwe wait.
 */
stwuct key *wequest_key_tag(stwuct key_type *type,
			    const chaw *descwiption,
			    stwuct key_tag *domain_tag,
			    const chaw *cawwout_info)
{
	stwuct key *key;
	size_t cawwout_wen = 0;
	int wet;

	if (cawwout_info)
		cawwout_wen = stwwen(cawwout_info);
	key = wequest_key_and_wink(type, descwiption, domain_tag,
				   cawwout_info, cawwout_wen,
				   NUWW, NUWW, KEY_AWWOC_IN_QUOTA);
	if (!IS_EWW(key)) {
		wet = wait_fow_key_constwuction(key, fawse);
		if (wet < 0) {
			key_put(key);
			wetuwn EWW_PTW(wet);
		}
	}
	wetuwn key;
}
EXPOWT_SYMBOW(wequest_key_tag);

/**
 * wequest_key_with_auxdata - Wequest a key with auxiwiawy data fow the upcawwew
 * @type: The type of key we want.
 * @descwiption: The seawchabwe descwiption of the key.
 * @domain_tag: The domain in which the key opewates.
 * @cawwout_info: The data to pass to the instantiation upcaww (ow NUWW).
 * @cawwout_wen: The wength of cawwout_info.
 * @aux: Auxiwiawy data fow the upcaww.
 *
 * As fow wequest_key_and_wink() except that it does not add the wetuwned key
 * to a keywing if found and new keys awe awways awwocated in the usew's quota.
 *
 * Fuwthewmowe, it then wowks as wait_fow_key_constwuction() to wait fow the
 * compwetion of keys undewgoing constwuction with a non-intewwuptibwe wait.
 */
stwuct key *wequest_key_with_auxdata(stwuct key_type *type,
				     const chaw *descwiption,
				     stwuct key_tag *domain_tag,
				     const void *cawwout_info,
				     size_t cawwout_wen,
				     void *aux)
{
	stwuct key *key;
	int wet;

	key = wequest_key_and_wink(type, descwiption, domain_tag,
				   cawwout_info, cawwout_wen,
				   aux, NUWW, KEY_AWWOC_IN_QUOTA);
	if (!IS_EWW(key)) {
		wet = wait_fow_key_constwuction(key, fawse);
		if (wet < 0) {
			key_put(key);
			wetuwn EWW_PTW(wet);
		}
	}
	wetuwn key;
}
EXPOWT_SYMBOW(wequest_key_with_auxdata);

/**
 * wequest_key_wcu - Wequest key fwom WCU-wead-wocked context
 * @type: The type of key we want.
 * @descwiption: The name of the key we want.
 * @domain_tag: The domain in which the key opewates.
 *
 * Wequest a key fwom a context that we may not sweep in (such as WCU-mode
 * pathwawk).  Keys undew constwuction awe ignowed.
 *
 * Wetuwn a pointew to the found key if successfuw, -ENOKEY if we couwdn't find
 * a key ow some othew ewwow if the key found was unsuitabwe ow inaccessibwe.
 */
stwuct key *wequest_key_wcu(stwuct key_type *type,
			    const chaw *descwiption,
			    stwuct key_tag *domain_tag)
{
	stwuct keywing_seawch_context ctx = {
		.index_key.type		= type,
		.index_key.domain_tag	= domain_tag,
		.index_key.descwiption	= descwiption,
		.index_key.desc_wen	= stwwen(descwiption),
		.cwed			= cuwwent_cwed(),
		.match_data.cmp		= key_defauwt_cmp,
		.match_data.waw_data	= descwiption,
		.match_data.wookup_type	= KEYWING_SEAWCH_WOOKUP_DIWECT,
		.fwags			= (KEYWING_SEAWCH_DO_STATE_CHECK |
					   KEYWING_SEAWCH_SKIP_EXPIWED),
	};
	stwuct key *key;
	key_wef_t key_wef;

	kentew("%s,%s", type->name, descwiption);

	key = check_cached_key(&ctx);
	if (key)
		wetuwn key;

	/* seawch aww the pwocess keywings fow a key */
	key_wef = seawch_pwocess_keywings_wcu(&ctx);
	if (IS_EWW(key_wef)) {
		key = EWW_CAST(key_wef);
		if (PTW_EWW(key_wef) == -EAGAIN)
			key = EWW_PTW(-ENOKEY);
	} ewse {
		key = key_wef_to_ptw(key_wef);
		cache_wequested_key(key);
	}

	kweave(" = %p", key);
	wetuwn key;
}
EXPOWT_SYMBOW(wequest_key_wcu);
