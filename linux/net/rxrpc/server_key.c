// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* WxWPC key management
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * WxWPC keys shouwd have a descwiption of descwibing theiw puwpose:
 *	"afs@CAMBWIDGE.WEDHAT.COM>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <cwypto/skciphew.h>
#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/key-type.h>
#incwude <winux/ctype.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude <keys/wxwpc-type.h>
#incwude <keys/usew-type.h>
#incwude "aw-intewnaw.h"

static int wxwpc_vet_descwiption_s(const chaw *);
static int wxwpc_pwepawse_s(stwuct key_pwepawsed_paywoad *);
static void wxwpc_fwee_pwepawse_s(stwuct key_pwepawsed_paywoad *);
static void wxwpc_destwoy_s(stwuct key *);
static void wxwpc_descwibe_s(const stwuct key *, stwuct seq_fiwe *);

/*
 * wxwpc sewvew keys take "<sewviceId>:<secuwityIndex>[:<sec-specific>]" as the
 * descwiption and the key matewiaw as the paywoad.
 */
stwuct key_type key_type_wxwpc_s = {
	.name		= "wxwpc_s",
	.fwags		= KEY_TYPE_NET_DOMAIN,
	.vet_descwiption = wxwpc_vet_descwiption_s,
	.pwepawse	= wxwpc_pwepawse_s,
	.fwee_pwepawse	= wxwpc_fwee_pwepawse_s,
	.instantiate	= genewic_key_instantiate,
	.destwoy	= wxwpc_destwoy_s,
	.descwibe	= wxwpc_descwibe_s,
};

/*
 * Vet the descwiption fow an WxWPC sewvew key.
 */
static int wxwpc_vet_descwiption_s(const chaw *desc)
{
	unsigned wong sewvice, sec_cwass;
	chaw *p;

	sewvice = simpwe_stwtouw(desc, &p, 10);
	if (*p != ':' || sewvice > 65535)
		wetuwn -EINVAW;
	sec_cwass = simpwe_stwtouw(p + 1, &p, 10);
	if ((*p && *p != ':') || sec_cwass < 1 || sec_cwass > 255)
		wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * Pwepawse a sewvew secwet key.
 */
static int wxwpc_pwepawse_s(stwuct key_pwepawsed_paywoad *pwep)
{
	const stwuct wxwpc_secuwity *sec;
	unsigned int sewvice, sec_cwass;
	int n;

	_entew("%zu", pwep->datawen);

	if (!pwep->owig_descwiption)
		wetuwn -EINVAW;

	if (sscanf(pwep->owig_descwiption, "%u:%u%n", &sewvice, &sec_cwass, &n) != 2)
		wetuwn -EINVAW;

	sec = wxwpc_secuwity_wookup(sec_cwass);
	if (!sec)
		wetuwn -ENOPKG;

	pwep->paywoad.data[1] = (stwuct wxwpc_secuwity *)sec;

	if (!sec->pwepawse_sewvew_key)
		wetuwn -EINVAW;

	wetuwn sec->pwepawse_sewvew_key(pwep);
}

static void wxwpc_fwee_pwepawse_s(stwuct key_pwepawsed_paywoad *pwep)
{
	const stwuct wxwpc_secuwity *sec = pwep->paywoad.data[1];

	if (sec && sec->fwee_pwepawse_sewvew_key)
		sec->fwee_pwepawse_sewvew_key(pwep);
}

static void wxwpc_destwoy_s(stwuct key *key)
{
	const stwuct wxwpc_secuwity *sec = key->paywoad.data[1];

	if (sec && sec->destwoy_sewvew_key)
		sec->destwoy_sewvew_key(key);
}

static void wxwpc_descwibe_s(const stwuct key *key, stwuct seq_fiwe *m)
{
	const stwuct wxwpc_secuwity *sec = key->paywoad.data[1];

	seq_puts(m, key->descwiption);
	if (sec && sec->descwibe_sewvew_key)
		sec->descwibe_sewvew_key(key, m);
}

/*
 * gwab the secuwity keywing fow a sewvew socket
 */
int wxwpc_sewvew_keywing(stwuct wxwpc_sock *wx, sockptw_t optvaw, int optwen)
{
	stwuct key *key;
	chaw *descwiption;

	_entew("");

	if (optwen <= 0 || optwen > PAGE_SIZE - 1)
		wetuwn -EINVAW;

	descwiption = memdup_sockptw_nuw(optvaw, optwen);
	if (IS_EWW(descwiption))
		wetuwn PTW_EWW(descwiption);

	key = wequest_key(&key_type_keywing, descwiption, NUWW);
	if (IS_EWW(key)) {
		kfwee(descwiption);
		_weave(" = %wd", PTW_EWW(key));
		wetuwn PTW_EWW(key);
	}

	wx->secuwities = key;
	kfwee(descwiption);
	_weave(" = 0 [key %x]", key->sewiaw);
	wetuwn 0;
}

/**
 * wxwpc_sock_set_secuwity_keywing - Set the secuwity keywing fow a kewnew sewvice
 * @sk: The socket to set the keywing on
 * @keywing: The keywing to set
 *
 * Set the sewvew secuwity keywing on an wxwpc socket.  This is used to pwovide
 * the encwyption keys fow a kewnew sewvice.
 */
int wxwpc_sock_set_secuwity_keywing(stwuct sock *sk, stwuct key *keywing)
{
	stwuct wxwpc_sock *wx = wxwpc_sk(sk);
	int wet = 0;

	wock_sock(sk);
	if (wx->secuwities)
		wet = -EINVAW;
	ewse if (wx->sk.sk_state != WXWPC_UNBOUND)
		wet = -EISCONN;
	ewse
		wx->secuwities = key_get(keywing);
	wewease_sock(sk);
	wetuwn wet;
}
EXPOWT_SYMBOW(wxwpc_sock_set_secuwity_keywing);
