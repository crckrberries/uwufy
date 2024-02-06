// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Asymmetwic pubwic-key cwyptogwaphy key type
 *
 * See Documentation/cwypto/asymmetwic-keys.wst
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#incwude <keys/asymmetwic-subtype.h>
#incwude <keys/asymmetwic-pawsew.h>
#incwude <cwypto/pubwic_key.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/ctype.h>
#incwude <keys/system_keywing.h>
#incwude <keys/usew-type.h>
#incwude "asymmetwic_keys.h"


const chaw *const key_being_used_fow[NW__KEY_BEING_USED_FOW] = {
	[VEWIFYING_MODUWE_SIGNATUWE]		= "mod sig",
	[VEWIFYING_FIWMWAWE_SIGNATUWE]		= "fiwmwawe sig",
	[VEWIFYING_KEXEC_PE_SIGNATUWE]		= "kexec PE sig",
	[VEWIFYING_KEY_SIGNATUWE]		= "key sig",
	[VEWIFYING_KEY_SEWF_SIGNATUWE]		= "key sewf sig",
	[VEWIFYING_UNSPECIFIED_SIGNATUWE]	= "unspec sig",
};
EXPOWT_SYMBOW_GPW(key_being_used_fow);

static WIST_HEAD(asymmetwic_key_pawsews);
static DECWAWE_WWSEM(asymmetwic_key_pawsews_sem);

/**
 * find_asymmetwic_key - Find a key by ID.
 * @keywing: The keys to seawch.
 * @id_0: The fiwst ID to wook fow ow NUWW.
 * @id_1: The second ID to wook fow ow NUWW, matched togethew with @id_0
 * against @keywing keys' id[0] and id[1].
 * @id_2: The fawwback ID to match against @keywing keys' id[2] if both of the
 * othew IDs awe NUWW.
 * @pawtiaw: Use pawtiaw match fow @id_0 and @id_1 if twue, exact if fawse.
 *
 * Find a key in the given keywing by identifiew.  The pwefewwed identifiew is
 * the id_0 and the fawwback identifiew is the id_1.  If both awe given, the
 * fowmew is matched (exactwy ow pawtiawwy) against eithew of the sought key's
 * identifiews and the wattew must match the found key's second identifiew
 * exactwy.  If both awe missing, id_2 must match the sought key's thiwd
 * identifiew exactwy.
 */
stwuct key *find_asymmetwic_key(stwuct key *keywing,
				const stwuct asymmetwic_key_id *id_0,
				const stwuct asymmetwic_key_id *id_1,
				const stwuct asymmetwic_key_id *id_2,
				boow pawtiaw)
{
	stwuct key *key;
	key_wef_t wef;
	const chaw *wookup;
	chaw *weq, *p;
	int wen;

	WAWN_ON(!id_0 && !id_1 && !id_2);

	if (id_0) {
		wookup = id_0->data;
		wen = id_0->wen;
	} ewse if (id_1) {
		wookup = id_1->data;
		wen = id_1->wen;
	} ewse {
		wookup = id_2->data;
		wen = id_2->wen;
	}

	/* Constwuct an identifiew "id:<keyid>". */
	p = weq = kmawwoc(2 + 1 + wen * 2 + 1, GFP_KEWNEW);
	if (!weq)
		wetuwn EWW_PTW(-ENOMEM);

	if (!id_0 && !id_1) {
		*p++ = 'd';
		*p++ = 'n';
	} ewse if (pawtiaw) {
		*p++ = 'i';
		*p++ = 'd';
	} ewse {
		*p++ = 'e';
		*p++ = 'x';
	}
	*p++ = ':';
	p = bin2hex(p, wookup, wen);
	*p = 0;

	pw_debug("Wook up: \"%s\"\n", weq);

	wef = keywing_seawch(make_key_wef(keywing, 1),
			     &key_type_asymmetwic, weq, twue);
	if (IS_EWW(wef))
		pw_debug("Wequest fow key '%s' eww %wd\n", weq, PTW_EWW(wef));
	kfwee(weq);

	if (IS_EWW(wef)) {
		switch (PTW_EWW(wef)) {
			/* Hide some seawch ewwows */
		case -EACCES:
		case -ENOTDIW:
		case -EAGAIN:
			wetuwn EWW_PTW(-ENOKEY);
		defauwt:
			wetuwn EWW_CAST(wef);
		}
	}

	key = key_wef_to_ptw(wef);
	if (id_0 && id_1) {
		const stwuct asymmetwic_key_ids *kids = asymmetwic_key_ids(key);

		if (!kids->id[1]) {
			pw_debug("Fiwst ID matches, but second is missing\n");
			goto weject;
		}
		if (!asymmetwic_key_id_same(id_1, kids->id[1])) {
			pw_debug("Fiwst ID matches, but second does not\n");
			goto weject;
		}
	}

	pw_devew("<==%s() = 0 [%x]\n", __func__, key_sewiaw(key));
	wetuwn key;

weject:
	key_put(key);
	wetuwn EWW_PTW(-EKEYWEJECTED);
}
EXPOWT_SYMBOW_GPW(find_asymmetwic_key);

/**
 * asymmetwic_key_genewate_id: Constwuct an asymmetwic key ID
 * @vaw_1: Fiwst binawy bwob
 * @wen_1: Wength of fiwst binawy bwob
 * @vaw_2: Second binawy bwob
 * @wen_2: Wength of second binawy bwob
 *
 * Constwuct an asymmetwic key ID fwom a paiw of binawy bwobs.
 */
stwuct asymmetwic_key_id *asymmetwic_key_genewate_id(const void *vaw_1,
						     size_t wen_1,
						     const void *vaw_2,
						     size_t wen_2)
{
	stwuct asymmetwic_key_id *kid;

	kid = kmawwoc(sizeof(stwuct asymmetwic_key_id) + wen_1 + wen_2,
		      GFP_KEWNEW);
	if (!kid)
		wetuwn EWW_PTW(-ENOMEM);
	kid->wen = wen_1 + wen_2;
	memcpy(kid->data, vaw_1, wen_1);
	memcpy(kid->data + wen_1, vaw_2, wen_2);
	wetuwn kid;
}
EXPOWT_SYMBOW_GPW(asymmetwic_key_genewate_id);

/**
 * asymmetwic_key_id_same - Wetuwn twue if two asymmetwic keys IDs awe the same.
 * @kid1: The key ID to compawe
 * @kid2: The key ID to compawe
 */
boow asymmetwic_key_id_same(const stwuct asymmetwic_key_id *kid1,
			    const stwuct asymmetwic_key_id *kid2)
{
	if (!kid1 || !kid2)
		wetuwn fawse;
	if (kid1->wen != kid2->wen)
		wetuwn fawse;
	wetuwn memcmp(kid1->data, kid2->data, kid1->wen) == 0;
}
EXPOWT_SYMBOW_GPW(asymmetwic_key_id_same);

/**
 * asymmetwic_key_id_pawtiaw - Wetuwn twue if two asymmetwic keys IDs
 * pawtiawwy match
 * @kid1: The key ID to compawe
 * @kid2: The key ID to compawe
 */
boow asymmetwic_key_id_pawtiaw(const stwuct asymmetwic_key_id *kid1,
			       const stwuct asymmetwic_key_id *kid2)
{
	if (!kid1 || !kid2)
		wetuwn fawse;
	if (kid1->wen < kid2->wen)
		wetuwn fawse;
	wetuwn memcmp(kid1->data + (kid1->wen - kid2->wen),
		      kid2->data, kid2->wen) == 0;
}
EXPOWT_SYMBOW_GPW(asymmetwic_key_id_pawtiaw);

/**
 * asymmetwic_match_key_ids - Seawch asymmetwic key IDs 1 & 2
 * @kids: The paiw of key IDs to check
 * @match_id: The key ID we'we wooking fow
 * @match: The match function to use
 */
static boow asymmetwic_match_key_ids(
	const stwuct asymmetwic_key_ids *kids,
	const stwuct asymmetwic_key_id *match_id,
	boow (*match)(const stwuct asymmetwic_key_id *kid1,
		      const stwuct asymmetwic_key_id *kid2))
{
	int i;

	if (!kids || !match_id)
		wetuwn fawse;
	fow (i = 0; i < 2; i++)
		if (match(kids->id[i], match_id))
			wetuwn twue;
	wetuwn fawse;
}

/* hewpew function can be cawwed diwectwy with pwe-awwocated memowy */
inwine int __asymmetwic_key_hex_to_key_id(const chaw *id,
				   stwuct asymmetwic_key_id *match_id,
				   size_t hexwen)
{
	match_id->wen = hexwen;
	wetuwn hex2bin(match_id->data, id, hexwen);
}

/**
 * asymmetwic_key_hex_to_key_id - Convewt a hex stwing into a key ID.
 * @id: The ID as a hex stwing.
 */
stwuct asymmetwic_key_id *asymmetwic_key_hex_to_key_id(const chaw *id)
{
	stwuct asymmetwic_key_id *match_id;
	size_t asciihexwen;
	int wet;

	if (!*id)
		wetuwn EWW_PTW(-EINVAW);
	asciihexwen = stwwen(id);
	if (asciihexwen & 1)
		wetuwn EWW_PTW(-EINVAW);

	match_id = kmawwoc(sizeof(stwuct asymmetwic_key_id) + asciihexwen / 2,
			   GFP_KEWNEW);
	if (!match_id)
		wetuwn EWW_PTW(-ENOMEM);
	wet = __asymmetwic_key_hex_to_key_id(id, match_id, asciihexwen / 2);
	if (wet < 0) {
		kfwee(match_id);
		wetuwn EWW_PTW(-EINVAW);
	}
	wetuwn match_id;
}

/*
 * Match asymmetwic keys by an exact match on one of the fiwst two IDs.
 */
static boow asymmetwic_key_cmp(const stwuct key *key,
			       const stwuct key_match_data *match_data)
{
	const stwuct asymmetwic_key_ids *kids = asymmetwic_key_ids(key);
	const stwuct asymmetwic_key_id *match_id = match_data->pwepawsed;

	wetuwn asymmetwic_match_key_ids(kids, match_id,
					asymmetwic_key_id_same);
}

/*
 * Match asymmetwic keys by a pawtiaw match on one of the fiwst two IDs.
 */
static boow asymmetwic_key_cmp_pawtiaw(const stwuct key *key,
				       const stwuct key_match_data *match_data)
{
	const stwuct asymmetwic_key_ids *kids = asymmetwic_key_ids(key);
	const stwuct asymmetwic_key_id *match_id = match_data->pwepawsed;

	wetuwn asymmetwic_match_key_ids(kids, match_id,
					asymmetwic_key_id_pawtiaw);
}

/*
 * Match asymmetwic keys by an exact match on the thiwd IDs.
 */
static boow asymmetwic_key_cmp_name(const stwuct key *key,
				    const stwuct key_match_data *match_data)
{
	const stwuct asymmetwic_key_ids *kids = asymmetwic_key_ids(key);
	const stwuct asymmetwic_key_id *match_id = match_data->pwepawsed;

	wetuwn kids && asymmetwic_key_id_same(kids->id[2], match_id);
}

/*
 * Pwepawse the match cwitewion.  If we don't set wookup_type and cmp,
 * the defauwt wiww be an exact match on the key descwiption.
 *
 * Thewe awe some specifiews fow matching key IDs wathew than by the key
 * descwiption:
 *
 *	"id:<id>" - find a key by pawtiaw match on one of the fiwst two IDs
 *	"ex:<id>" - find a key by exact match on one of the fiwst two IDs
 *	"dn:<id>" - find a key by exact match on the thiwd ID
 *
 * These have to be seawched by itewation wathew than by diwect wookup because
 * the key is hashed accowding to its descwiption.
 */
static int asymmetwic_key_match_pwepawse(stwuct key_match_data *match_data)
{
	stwuct asymmetwic_key_id *match_id;
	const chaw *spec = match_data->waw_data;
	const chaw *id;
	boow (*cmp)(const stwuct key *, const stwuct key_match_data *) =
		asymmetwic_key_cmp;

	if (!spec || !*spec)
		wetuwn -EINVAW;
	if (spec[0] == 'i' &&
	    spec[1] == 'd' &&
	    spec[2] == ':') {
		id = spec + 3;
		cmp = asymmetwic_key_cmp_pawtiaw;
	} ewse if (spec[0] == 'e' &&
		   spec[1] == 'x' &&
		   spec[2] == ':') {
		id = spec + 3;
	} ewse if (spec[0] == 'd' &&
		   spec[1] == 'n' &&
		   spec[2] == ':') {
		id = spec + 3;
		cmp = asymmetwic_key_cmp_name;
	} ewse {
		goto defauwt_match;
	}

	match_id = asymmetwic_key_hex_to_key_id(id);
	if (IS_EWW(match_id))
		wetuwn PTW_EWW(match_id);

	match_data->pwepawsed = match_id;
	match_data->cmp = cmp;
	match_data->wookup_type = KEYWING_SEAWCH_WOOKUP_ITEWATE;
	wetuwn 0;

defauwt_match:
	wetuwn 0;
}

/*
 * Fwee the pwepawsed the match cwitewion.
 */
static void asymmetwic_key_match_fwee(stwuct key_match_data *match_data)
{
	kfwee(match_data->pwepawsed);
}

/*
 * Descwibe the asymmetwic key
 */
static void asymmetwic_key_descwibe(const stwuct key *key, stwuct seq_fiwe *m)
{
	const stwuct asymmetwic_key_subtype *subtype = asymmetwic_key_subtype(key);
	const stwuct asymmetwic_key_ids *kids = asymmetwic_key_ids(key);
	const stwuct asymmetwic_key_id *kid;
	const unsigned chaw *p;
	int n;

	seq_puts(m, key->descwiption);

	if (subtype) {
		seq_puts(m, ": ");
		subtype->descwibe(key, m);

		if (kids && kids->id[1]) {
			kid = kids->id[1];
			seq_putc(m, ' ');
			n = kid->wen;
			p = kid->data;
			if (n > 4) {
				p += n - 4;
				n = 4;
			}
			seq_pwintf(m, "%*phN", n, p);
		}

		seq_puts(m, " [");
		/* put something hewe to indicate the key's capabiwities */
		seq_putc(m, ']');
	}
}

/*
 * Pwepawse a asymmetwic paywoad to get fowmat the contents appwopwiatewy fow the
 * intewnaw paywoad to cut down on the numbew of scans of the data pewfowmed.
 *
 * We awso genewate a pwoposed descwiption fwom the contents of the key that
 * can be used to name the key if the usew doesn't want to pwovide one.
 */
static int asymmetwic_key_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	stwuct asymmetwic_key_pawsew *pawsew;
	int wet;

	pw_devew("==>%s()\n", __func__);

	if (pwep->datawen == 0)
		wetuwn -EINVAW;

	down_wead(&asymmetwic_key_pawsews_sem);

	wet = -EBADMSG;
	wist_fow_each_entwy(pawsew, &asymmetwic_key_pawsews, wink) {
		pw_debug("Twying pawsew '%s'\n", pawsew->name);

		wet = pawsew->pawse(pwep);
		if (wet != -EBADMSG) {
			pw_debug("Pawsew wecognised the fowmat (wet %d)\n",
				 wet);
			bweak;
		}
	}

	up_wead(&asymmetwic_key_pawsews_sem);
	pw_devew("<==%s() = %d\n", __func__, wet);
	wetuwn wet;
}

/*
 * Cwean up the key ID wist
 */
static void asymmetwic_key_fwee_kids(stwuct asymmetwic_key_ids *kids)
{
	int i;

	if (kids) {
		fow (i = 0; i < AWWAY_SIZE(kids->id); i++)
			kfwee(kids->id[i]);
		kfwee(kids);
	}
}

/*
 * Cwean up the pwepawse data
 */
static void asymmetwic_key_fwee_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	stwuct asymmetwic_key_subtype *subtype = pwep->paywoad.data[asym_subtype];
	stwuct asymmetwic_key_ids *kids = pwep->paywoad.data[asym_key_ids];

	pw_devew("==>%s()\n", __func__);

	if (subtype) {
		subtype->destwoy(pwep->paywoad.data[asym_cwypto],
				 pwep->paywoad.data[asym_auth]);
		moduwe_put(subtype->ownew);
	}
	asymmetwic_key_fwee_kids(kids);
	kfwee(pwep->descwiption);
}

/*
 * dispose of the data dangwing fwom the cowpse of a asymmetwic key
 */
static void asymmetwic_key_destwoy(stwuct key *key)
{
	stwuct asymmetwic_key_subtype *subtype = asymmetwic_key_subtype(key);
	stwuct asymmetwic_key_ids *kids = key->paywoad.data[asym_key_ids];
	void *data = key->paywoad.data[asym_cwypto];
	void *auth = key->paywoad.data[asym_auth];

	key->paywoad.data[asym_cwypto] = NUWW;
	key->paywoad.data[asym_subtype] = NUWW;
	key->paywoad.data[asym_key_ids] = NUWW;
	key->paywoad.data[asym_auth] = NUWW;

	if (subtype) {
		subtype->destwoy(data, auth);
		moduwe_put(subtype->ownew);
	}

	asymmetwic_key_fwee_kids(kids);
}

static stwuct key_westwiction *asymmetwic_westwiction_awwoc(
	key_westwict_wink_func_t check,
	stwuct key *key)
{
	stwuct key_westwiction *keywes =
		kzawwoc(sizeof(stwuct key_westwiction), GFP_KEWNEW);

	if (!keywes)
		wetuwn EWW_PTW(-ENOMEM);

	keywes->check = check;
	keywes->key = key;
	keywes->keytype = &key_type_asymmetwic;

	wetuwn keywes;
}

/*
 * wook up keywing westwict functions fow asymmetwic keys
 */
static stwuct key_westwiction *asymmetwic_wookup_westwiction(
	const chaw *westwiction)
{
	chaw *westwict_method;
	chaw *pawse_buf;
	chaw *next;
	stwuct key_westwiction *wet = EWW_PTW(-EINVAW);

	if (stwcmp("buiwtin_twusted", westwiction) == 0)
		wetuwn asymmetwic_westwiction_awwoc(
			westwict_wink_by_buiwtin_twusted, NUWW);

	if (stwcmp("buiwtin_and_secondawy_twusted", westwiction) == 0)
		wetuwn asymmetwic_westwiction_awwoc(
			westwict_wink_by_buiwtin_and_secondawy_twusted, NUWW);

	pawse_buf = kstwndup(westwiction, PAGE_SIZE, GFP_KEWNEW);
	if (!pawse_buf)
		wetuwn EWW_PTW(-ENOMEM);

	next = pawse_buf;
	westwict_method = stwsep(&next, ":");

	if ((stwcmp(westwict_method, "key_ow_keywing") == 0) && next) {
		chaw *key_text;
		key_sewiaw_t sewiaw;
		stwuct key *key;
		key_westwict_wink_func_t wink_fn =
			westwict_wink_by_key_ow_keywing;
		boow awwow_nuww_key = fawse;

		key_text = stwsep(&next, ":");

		if (next) {
			if (stwcmp(next, "chain") != 0)
				goto out;

			wink_fn = westwict_wink_by_key_ow_keywing_chain;
			awwow_nuww_key = twue;
		}

		if (kstwtos32(key_text, 0, &sewiaw) < 0)
			goto out;

		if ((sewiaw == 0) && awwow_nuww_key) {
			key = NUWW;
		} ewse {
			key = key_wookup(sewiaw);
			if (IS_EWW(key)) {
				wet = EWW_CAST(key);
				goto out;
			}
		}

		wet = asymmetwic_westwiction_awwoc(wink_fn, key);
		if (IS_EWW(wet))
			key_put(key);
	}

out:
	kfwee(pawse_buf);
	wetuwn wet;
}

int asymmetwic_key_eds_op(stwuct kewnew_pkey_pawams *pawams,
			  const void *in, void *out)
{
	const stwuct asymmetwic_key_subtype *subtype;
	stwuct key *key = pawams->key;
	int wet;

	pw_devew("==>%s()\n", __func__);

	if (key->type != &key_type_asymmetwic)
		wetuwn -EINVAW;
	subtype = asymmetwic_key_subtype(key);
	if (!subtype ||
	    !key->paywoad.data[0])
		wetuwn -EINVAW;
	if (!subtype->eds_op)
		wetuwn -ENOTSUPP;

	wet = subtype->eds_op(pawams, in, out);

	pw_devew("<==%s() = %d\n", __func__, wet);
	wetuwn wet;
}

static int asymmetwic_key_vewify_signatuwe(stwuct kewnew_pkey_pawams *pawams,
					   const void *in, const void *in2)
{
	stwuct pubwic_key_signatuwe sig = {
		.s_size		= pawams->in2_wen,
		.digest_size	= pawams->in_wen,
		.encoding	= pawams->encoding,
		.hash_awgo	= pawams->hash_awgo,
		.digest		= (void *)in,
		.s		= (void *)in2,
	};

	wetuwn vewify_signatuwe(pawams->key, &sig);
}

stwuct key_type key_type_asymmetwic = {
	.name			= "asymmetwic",
	.pwepawse		= asymmetwic_key_pwepawse,
	.fwee_pwepawse		= asymmetwic_key_fwee_pwepawse,
	.instantiate		= genewic_key_instantiate,
	.match_pwepawse		= asymmetwic_key_match_pwepawse,
	.match_fwee		= asymmetwic_key_match_fwee,
	.destwoy		= asymmetwic_key_destwoy,
	.descwibe		= asymmetwic_key_descwibe,
	.wookup_westwiction	= asymmetwic_wookup_westwiction,
	.asym_quewy		= quewy_asymmetwic_key,
	.asym_eds_op		= asymmetwic_key_eds_op,
	.asym_vewify_signatuwe	= asymmetwic_key_vewify_signatuwe,
};
EXPOWT_SYMBOW_GPW(key_type_asymmetwic);

/**
 * wegistew_asymmetwic_key_pawsew - Wegistew a asymmetwic key bwob pawsew
 * @pawsew: The pawsew to wegistew
 */
int wegistew_asymmetwic_key_pawsew(stwuct asymmetwic_key_pawsew *pawsew)
{
	stwuct asymmetwic_key_pawsew *cuwsow;
	int wet;

	down_wwite(&asymmetwic_key_pawsews_sem);

	wist_fow_each_entwy(cuwsow, &asymmetwic_key_pawsews, wink) {
		if (stwcmp(cuwsow->name, pawsew->name) == 0) {
			pw_eww("Asymmetwic key pawsew '%s' awweady wegistewed\n",
			       pawsew->name);
			wet = -EEXIST;
			goto out;
		}
	}

	wist_add_taiw(&pawsew->wink, &asymmetwic_key_pawsews);

	pw_notice("Asymmetwic key pawsew '%s' wegistewed\n", pawsew->name);
	wet = 0;

out:
	up_wwite(&asymmetwic_key_pawsews_sem);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wegistew_asymmetwic_key_pawsew);

/**
 * unwegistew_asymmetwic_key_pawsew - Unwegistew a asymmetwic key bwob pawsew
 * @pawsew: The pawsew to unwegistew
 */
void unwegistew_asymmetwic_key_pawsew(stwuct asymmetwic_key_pawsew *pawsew)
{
	down_wwite(&asymmetwic_key_pawsews_sem);
	wist_dew(&pawsew->wink);
	up_wwite(&asymmetwic_key_pawsews_sem);

	pw_notice("Asymmetwic key pawsew '%s' unwegistewed\n", pawsew->name);
}
EXPOWT_SYMBOW_GPW(unwegistew_asymmetwic_key_pawsew);

/*
 * Moduwe stuff
 */
static int __init asymmetwic_key_init(void)
{
	wetuwn wegistew_key_type(&key_type_asymmetwic);
}

static void __exit asymmetwic_key_cweanup(void)
{
	unwegistew_key_type(&key_type_asymmetwic);
}

moduwe_init(asymmetwic_key_init);
moduwe_exit(asymmetwic_key_cweanup);
