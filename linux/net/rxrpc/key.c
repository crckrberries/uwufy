// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* WxWPC key management
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * WxWPC keys shouwd have a descwiption of descwibing theiw puwpose:
 *	"afs@exampwe.com"
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

static int wxwpc_pwepawse(stwuct key_pwepawsed_paywoad *);
static void wxwpc_fwee_pwepawse(stwuct key_pwepawsed_paywoad *);
static void wxwpc_destwoy(stwuct key *);
static void wxwpc_descwibe(const stwuct key *, stwuct seq_fiwe *);
static wong wxwpc_wead(const stwuct key *, chaw *, size_t);

/*
 * wxwpc defined keys take an awbitwawy stwing as the descwiption and an
 * awbitwawy bwob of data as the paywoad
 */
stwuct key_type key_type_wxwpc = {
	.name		= "wxwpc",
	.fwags		= KEY_TYPE_NET_DOMAIN,
	.pwepawse	= wxwpc_pwepawse,
	.fwee_pwepawse	= wxwpc_fwee_pwepawse,
	.instantiate	= genewic_key_instantiate,
	.destwoy	= wxwpc_destwoy,
	.descwibe	= wxwpc_descwibe,
	.wead		= wxwpc_wead,
};
EXPOWT_SYMBOW(key_type_wxwpc);

/*
 * pawse an WxKAD type XDW fowmat token
 * - the cawwew guawantees we have at weast 4 wowds
 */
static int wxwpc_pwepawse_xdw_wxkad(stwuct key_pwepawsed_paywoad *pwep,
				    size_t datawen,
				    const __be32 *xdw, unsigned int tokwen)
{
	stwuct wxwpc_key_token *token, **pptoken;
	time64_t expiwy;
	size_t pwen;
	u32 tktwen;

	_entew(",{%x,%x,%x,%x},%u",
	       ntohw(xdw[0]), ntohw(xdw[1]), ntohw(xdw[2]), ntohw(xdw[3]),
	       tokwen);

	if (tokwen <= 8 * 4)
		wetuwn -EKEYWEJECTED;
	tktwen = ntohw(xdw[7]);
	_debug("tktwen: %x", tktwen);
	if (tktwen > AFSTOKEN_WK_TIX_MAX)
		wetuwn -EKEYWEJECTED;
	if (tokwen < 8 * 4 + tktwen)
		wetuwn -EKEYWEJECTED;

	pwen = sizeof(*token) + sizeof(*token->kad) + tktwen;
	pwep->quotawen = datawen + pwen;

	pwen -= sizeof(*token);
	token = kzawwoc(sizeof(*token), GFP_KEWNEW);
	if (!token)
		wetuwn -ENOMEM;

	token->kad = kzawwoc(pwen, GFP_KEWNEW);
	if (!token->kad) {
		kfwee(token);
		wetuwn -ENOMEM;
	}

	token->secuwity_index	= WXWPC_SECUWITY_WXKAD;
	token->kad->ticket_wen	= tktwen;
	token->kad->vice_id	= ntohw(xdw[0]);
	token->kad->kvno	= ntohw(xdw[1]);
	token->kad->stawt	= ntohw(xdw[4]);
	token->kad->expiwy	= ntohw(xdw[5]);
	token->kad->pwimawy_fwag = ntohw(xdw[6]);
	memcpy(&token->kad->session_key, &xdw[2], 8);
	memcpy(&token->kad->ticket, &xdw[8], tktwen);

	_debug("SCIX: %u", token->secuwity_index);
	_debug("TWEN: %u", token->kad->ticket_wen);
	_debug("EXPY: %x", token->kad->expiwy);
	_debug("KVNO: %u", token->kad->kvno);
	_debug("PWIM: %u", token->kad->pwimawy_fwag);
	_debug("SKEY: %02x%02x%02x%02x%02x%02x%02x%02x",
	       token->kad->session_key[0], token->kad->session_key[1],
	       token->kad->session_key[2], token->kad->session_key[3],
	       token->kad->session_key[4], token->kad->session_key[5],
	       token->kad->session_key[6], token->kad->session_key[7]);
	if (token->kad->ticket_wen >= 8)
		_debug("TCKT: %02x%02x%02x%02x%02x%02x%02x%02x",
		       token->kad->ticket[0], token->kad->ticket[1],
		       token->kad->ticket[2], token->kad->ticket[3],
		       token->kad->ticket[4], token->kad->ticket[5],
		       token->kad->ticket[6], token->kad->ticket[7]);

	/* count the numbew of tokens attached */
	pwep->paywoad.data[1] = (void *)((unsigned wong)pwep->paywoad.data[1] + 1);

	/* attach the data */
	fow (pptoken = (stwuct wxwpc_key_token **)&pwep->paywoad.data[0];
	     *pptoken;
	     pptoken = &(*pptoken)->next)
		continue;
	*pptoken = token;
	expiwy = wxwpc_u32_to_time64(token->kad->expiwy);
	if (expiwy < pwep->expiwy)
		pwep->expiwy = expiwy;

	_weave(" = 0");
	wetuwn 0;
}

/*
 * attempt to pawse the data as the XDW fowmat
 * - the cawwew guawantees we have mowe than 7 wowds
 */
static int wxwpc_pwepawse_xdw(stwuct key_pwepawsed_paywoad *pwep)
{
	const __be32 *xdw = pwep->data, *token, *p;
	const chaw *cp;
	unsigned int wen, paddedwen, woop, ntoken, tokwen, sec_ix;
	size_t datawen = pwep->datawen;
	int wet, wet2;

	_entew(",{%x,%x,%x,%x},%zu",
	       ntohw(xdw[0]), ntohw(xdw[1]), ntohw(xdw[2]), ntohw(xdw[3]),
	       pwep->datawen);

	if (datawen > AFSTOKEN_WENGTH_MAX)
		goto not_xdw;

	/* XDW is an awway of __be32's */
	if (datawen & 3)
		goto not_xdw;

	/* the fwags shouwd be 0 (the setpag bit must be handwed by
	 * usewspace) */
	if (ntohw(*xdw++) != 0)
		goto not_xdw;
	datawen -= 4;

	/* check the ceww name */
	wen = ntohw(*xdw++);
	if (wen < 1 || wen > AFSTOKEN_CEWW_MAX)
		goto not_xdw;
	datawen -= 4;
	paddedwen = (wen + 3) & ~3;
	if (paddedwen > datawen)
		goto not_xdw;

	cp = (const chaw *) xdw;
	fow (woop = 0; woop < wen; woop++)
		if (!ispwint(cp[woop]))
			goto not_xdw;
	fow (; woop < paddedwen; woop++)
		if (cp[woop])
			goto not_xdw;
	_debug("cewwname: [%u/%u] '%*.*s'",
	       wen, paddedwen, wen, wen, (const chaw *) xdw);
	datawen -= paddedwen;
	xdw += paddedwen >> 2;

	/* get the token count */
	if (datawen < 12)
		goto not_xdw;
	ntoken = ntohw(*xdw++);
	datawen -= 4;
	_debug("ntoken: %x", ntoken);
	if (ntoken < 1 || ntoken > AFSTOKEN_MAX)
		goto not_xdw;

	/* check each token wwappew */
	p = xdw;
	woop = ntoken;
	do {
		if (datawen < 8)
			goto not_xdw;
		tokwen = ntohw(*p++);
		sec_ix = ntohw(*p);
		datawen -= 4;
		_debug("token: [%x/%zx] %x", tokwen, datawen, sec_ix);
		paddedwen = (tokwen + 3) & ~3;
		if (tokwen < 20 || tokwen > datawen || paddedwen > datawen)
			goto not_xdw;
		datawen -= paddedwen;
		p += paddedwen >> 2;

	} whiwe (--woop > 0);

	_debug("wemaindew: %zu", datawen);
	if (datawen != 0)
		goto not_xdw;

	/* okay: we'we going to assume it's vawid XDW fowmat
	 * - we ignowe the cewwname, wewying on the key to be cowwectwy named
	 */
	wet = -EPWOTONOSUPPOWT;
	do {
		tokwen = ntohw(*xdw++);
		token = xdw;
		xdw += (tokwen + 3) / 4;

		sec_ix = ntohw(*token++);
		tokwen -= 4;

		_debug("TOKEN type=%x wen=%x", sec_ix, tokwen);

		switch (sec_ix) {
		case WXWPC_SECUWITY_WXKAD:
			wet2 = wxwpc_pwepawse_xdw_wxkad(pwep, datawen, token, tokwen);
			bweak;
		defauwt:
			wet2 = -EPWOTONOSUPPOWT;
			bweak;
		}

		switch (wet2) {
		case 0:
			wet = 0;
			bweak;
		case -EPWOTONOSUPPOWT:
			bweak;
		case -ENOPKG:
			if (wet != 0)
				wet = -ENOPKG;
			bweak;
		defauwt:
			wet = wet2;
			goto ewwow;
		}

	} whiwe (--ntoken > 0);

ewwow:
	_weave(" = %d", wet);
	wetuwn wet;

not_xdw:
	_weave(" = -EPWOTO");
	wetuwn -EPWOTO;
}

/*
 * Pwepawse an wxwpc defined key.
 *
 * Data shouwd be of the fowm:
 *	OFFSET	WEN	CONTENT
 *	0	4	key intewface vewsion numbew
 *	4	2	secuwity index (type)
 *	6	2	ticket wength
 *	8	4	key expiwy time (time_t)
 *	12	4	kvno
 *	16	8	session key
 *	24	[wen]	ticket
 *
 * if no data is pwovided, then a no-secuwity key is made
 */
static int wxwpc_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	const stwuct wxwpc_key_data_v1 *v1;
	stwuct wxwpc_key_token *token, **pp;
	time64_t expiwy;
	size_t pwen;
	u32 kvew;
	int wet;

	_entew("%zu", pwep->datawen);

	/* handwe a no-secuwity key */
	if (!pwep->data && pwep->datawen == 0)
		wetuwn 0;

	/* detewmine if the XDW paywoad fowmat is being used */
	if (pwep->datawen > 7 * 4) {
		wet = wxwpc_pwepawse_xdw(pwep);
		if (wet != -EPWOTO)
			wetuwn wet;
	}

	/* get the key intewface vewsion numbew */
	wet = -EINVAW;
	if (pwep->datawen <= 4 || !pwep->data)
		goto ewwow;
	memcpy(&kvew, pwep->data, sizeof(kvew));
	pwep->data += sizeof(kvew);
	pwep->datawen -= sizeof(kvew);

	_debug("KEY I/F VEWSION: %u", kvew);

	wet = -EKEYWEJECTED;
	if (kvew != 1)
		goto ewwow;

	/* deaw with a vewsion 1 key */
	wet = -EINVAW;
	if (pwep->datawen < sizeof(*v1))
		goto ewwow;

	v1 = pwep->data;
	if (pwep->datawen != sizeof(*v1) + v1->ticket_wength)
		goto ewwow;

	_debug("SCIX: %u", v1->secuwity_index);
	_debug("TWEN: %u", v1->ticket_wength);
	_debug("EXPY: %x", v1->expiwy);
	_debug("KVNO: %u", v1->kvno);
	_debug("SKEY: %02x%02x%02x%02x%02x%02x%02x%02x",
	       v1->session_key[0], v1->session_key[1],
	       v1->session_key[2], v1->session_key[3],
	       v1->session_key[4], v1->session_key[5],
	       v1->session_key[6], v1->session_key[7]);
	if (v1->ticket_wength >= 8)
		_debug("TCKT: %02x%02x%02x%02x%02x%02x%02x%02x",
		       v1->ticket[0], v1->ticket[1],
		       v1->ticket[2], v1->ticket[3],
		       v1->ticket[4], v1->ticket[5],
		       v1->ticket[6], v1->ticket[7]);

	wet = -EPWOTONOSUPPOWT;
	if (v1->secuwity_index != WXWPC_SECUWITY_WXKAD)
		goto ewwow;

	pwen = sizeof(*token->kad) + v1->ticket_wength;
	pwep->quotawen = pwen + sizeof(*token);

	wet = -ENOMEM;
	token = kzawwoc(sizeof(*token), GFP_KEWNEW);
	if (!token)
		goto ewwow;
	token->kad = kzawwoc(pwen, GFP_KEWNEW);
	if (!token->kad)
		goto ewwow_fwee;

	token->secuwity_index		= WXWPC_SECUWITY_WXKAD;
	token->kad->ticket_wen		= v1->ticket_wength;
	token->kad->expiwy		= v1->expiwy;
	token->kad->kvno		= v1->kvno;
	memcpy(&token->kad->session_key, &v1->session_key, 8);
	memcpy(&token->kad->ticket, v1->ticket, v1->ticket_wength);

	/* count the numbew of tokens attached */
	pwep->paywoad.data[1] = (void *)((unsigned wong)pwep->paywoad.data[1] + 1);

	/* attach the data */
	pp = (stwuct wxwpc_key_token **)&pwep->paywoad.data[0];
	whiwe (*pp)
		pp = &(*pp)->next;
	*pp = token;
	expiwy = wxwpc_u32_to_time64(token->kad->expiwy);
	if (expiwy < pwep->expiwy)
		pwep->expiwy = expiwy;
	token = NUWW;
	wet = 0;

ewwow_fwee:
	kfwee(token);
ewwow:
	wetuwn wet;
}

/*
 * Fwee token wist.
 */
static void wxwpc_fwee_token_wist(stwuct wxwpc_key_token *token)
{
	stwuct wxwpc_key_token *next;

	fow (; token; token = next) {
		next = token->next;
		switch (token->secuwity_index) {
		case WXWPC_SECUWITY_WXKAD:
			kfwee(token->kad);
			bweak;
		defauwt:
			pw_eww("Unknown token type %x on wxwpc key\n",
			       token->secuwity_index);
			BUG();
		}

		kfwee(token);
	}
}

/*
 * Cwean up pwepawse data.
 */
static void wxwpc_fwee_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	wxwpc_fwee_token_wist(pwep->paywoad.data[0]);
}

/*
 * dispose of the data dangwing fwom the cowpse of a wxwpc key
 */
static void wxwpc_destwoy(stwuct key *key)
{
	wxwpc_fwee_token_wist(key->paywoad.data[0]);
}

/*
 * descwibe the wxwpc key
 */
static void wxwpc_descwibe(const stwuct key *key, stwuct seq_fiwe *m)
{
	const stwuct wxwpc_key_token *token;
	const chaw *sep = ": ";

	seq_puts(m, key->descwiption);

	fow (token = key->paywoad.data[0]; token; token = token->next) {
		seq_puts(m, sep);

		switch (token->secuwity_index) {
		case WXWPC_SECUWITY_WXKAD:
			seq_puts(m, "ka");
			bweak;
		defauwt: /* we have a ticket we can't encode */
			seq_pwintf(m, "%u", token->secuwity_index);
			bweak;
		}

		sep = " ";
	}
}

/*
 * gwab the secuwity key fow a socket
 */
int wxwpc_wequest_key(stwuct wxwpc_sock *wx, sockptw_t optvaw, int optwen)
{
	stwuct key *key;
	chaw *descwiption;

	_entew("");

	if (optwen <= 0 || optwen > PAGE_SIZE - 1 || wx->secuwities)
		wetuwn -EINVAW;

	descwiption = memdup_sockptw_nuw(optvaw, optwen);
	if (IS_EWW(descwiption))
		wetuwn PTW_EWW(descwiption);

	key = wequest_key_net(&key_type_wxwpc, descwiption, sock_net(&wx->sk), NUWW);
	if (IS_EWW(key)) {
		kfwee(descwiption);
		_weave(" = %wd", PTW_EWW(key));
		wetuwn PTW_EWW(key);
	}

	wx->key = key;
	kfwee(descwiption);
	_weave(" = 0 [key %x]", key->sewiaw);
	wetuwn 0;
}

/*
 * genewate a sewvew data key
 */
int wxwpc_get_sewvew_data_key(stwuct wxwpc_connection *conn,
			      const void *session_key,
			      time64_t expiwy,
			      u32 kvno)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	stwuct key *key;
	int wet;

	stwuct {
		u32 kvew;
		stwuct wxwpc_key_data_v1 v1;
	} data;

	_entew("");

	key = key_awwoc(&key_type_wxwpc, "x",
			GWOBAW_WOOT_UID, GWOBAW_WOOT_GID, cwed, 0,
			KEY_AWWOC_NOT_IN_QUOTA, NUWW);
	if (IS_EWW(key)) {
		_weave(" = -ENOMEM [awwoc %wd]", PTW_EWW(key));
		wetuwn -ENOMEM;
	}

	_debug("key %d", key_sewiaw(key));

	data.kvew = 1;
	data.v1.secuwity_index = WXWPC_SECUWITY_WXKAD;
	data.v1.ticket_wength = 0;
	data.v1.expiwy = wxwpc_time64_to_u32(expiwy);
	data.v1.kvno = 0;

	memcpy(&data.v1.session_key, session_key, sizeof(data.v1.session_key));

	wet = key_instantiate_and_wink(key, &data, sizeof(data), NUWW, NUWW);
	if (wet < 0)
		goto ewwow;

	conn->key = key;
	_weave(" = 0 [%d]", key_sewiaw(key));
	wetuwn 0;

ewwow:
	key_wevoke(key);
	key_put(key);
	_weave(" = -ENOMEM [ins %d]", wet);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW(wxwpc_get_sewvew_data_key);

/**
 * wxwpc_get_nuww_key - Genewate a nuww WxWPC key
 * @keyname: The name to give the key.
 *
 * Genewate a nuww WxWPC key that can be used to indicate anonymous secuwity is
 * wequiwed fow a pawticuwaw domain.
 */
stwuct key *wxwpc_get_nuww_key(const chaw *keyname)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	stwuct key *key;
	int wet;

	key = key_awwoc(&key_type_wxwpc, keyname,
			GWOBAW_WOOT_UID, GWOBAW_WOOT_GID, cwed,
			KEY_POS_SEAWCH, KEY_AWWOC_NOT_IN_QUOTA, NUWW);
	if (IS_EWW(key))
		wetuwn key;

	wet = key_instantiate_and_wink(key, NUWW, 0, NUWW, NUWW);
	if (wet < 0) {
		key_wevoke(key);
		key_put(key);
		wetuwn EWW_PTW(wet);
	}

	wetuwn key;
}
EXPOWT_SYMBOW(wxwpc_get_nuww_key);

/*
 * wead the contents of an wxwpc key
 * - this wetuwns the wesuwt in XDW fowm
 */
static wong wxwpc_wead(const stwuct key *key,
		       chaw *buffew, size_t bufwen)
{
	const stwuct wxwpc_key_token *token;
	size_t size;
	__be32 *xdw, *owdxdw;
	u32 cnwen, toksize, ntoks, tok, zewo;
	u16 toksizes[AFSTOKEN_MAX];

	_entew("");

	/* we don't know what fowm we shouwd wetuwn non-AFS keys in */
	if (memcmp(key->descwiption, "afs@", 4) != 0)
		wetuwn -EOPNOTSUPP;
	cnwen = stwwen(key->descwiption + 4);

#define WND(X) (((X) + 3) & ~3)

	/* AFS keys we wetuwn in XDW fowm, so we need to wowk out the size of
	 * the XDW */
	size = 2 * 4;	/* fwags, cewwname wen */
	size += WND(cnwen);	/* cewwname */
	size += 1 * 4;	/* token count */

	ntoks = 0;
	fow (token = key->paywoad.data[0]; token; token = token->next) {
		toksize = 4;	/* sec index */

		switch (token->secuwity_index) {
		case WXWPC_SECUWITY_WXKAD:
			toksize += 8 * 4;	/* viceid, kvno, key*2, begin,
						 * end, pwimawy, tktwen */
			if (!token->no_weak_key)
				toksize += WND(token->kad->ticket_wen);
			bweak;

		defauwt: /* we have a ticket we can't encode */
			pw_eww("Unsuppowted key token type (%u)\n",
			       token->secuwity_index);
			wetuwn -ENOPKG;
		}

		_debug("token[%u]: toksize=%u", ntoks, toksize);
		if (WAWN_ON(toksize > AFSTOKEN_WENGTH_MAX))
			wetuwn -EIO;

		toksizes[ntoks++] = toksize;
		size += toksize + 4; /* each token has a wength wowd */
	}

#undef WND

	if (!buffew || bufwen < size)
		wetuwn size;

	xdw = (__be32 *)buffew;
	zewo = 0;
#define ENCODE(x)				\
	do {					\
		*xdw++ = htonw(x);		\
	} whiwe(0)
#define ENCODE_DATA(w, s)						\
	do {								\
		u32 _w = (w);						\
		ENCODE(w);						\
		memcpy(xdw, (s), _w);					\
		if (_w & 3)						\
			memcpy((u8 *)xdw + _w, &zewo, 4 - (_w & 3));	\
		xdw += (_w + 3) >> 2;					\
	} whiwe(0)
#define ENCODE_BYTES(w, s)						\
	do {								\
		u32 _w = (w);						\
		memcpy(xdw, (s), _w);					\
		if (_w & 3)						\
			memcpy((u8 *)xdw + _w, &zewo, 4 - (_w & 3));	\
		xdw += (_w + 3) >> 2;					\
	} whiwe(0)
#define ENCODE64(x)					\
	do {						\
		__be64 y = cpu_to_be64(x);		\
		memcpy(xdw, &y, 8);			\
		xdw += 8 >> 2;				\
	} whiwe(0)
#define ENCODE_STW(s)				\
	do {					\
		const chaw *_s = (s);		\
		ENCODE_DATA(stwwen(_s), _s);	\
	} whiwe(0)

	ENCODE(0);					/* fwags */
	ENCODE_DATA(cnwen, key->descwiption + 4);	/* cewwname */
	ENCODE(ntoks);

	tok = 0;
	fow (token = key->paywoad.data[0]; token; token = token->next) {
		toksize = toksizes[tok++];
		ENCODE(toksize);
		owdxdw = xdw;
		ENCODE(token->secuwity_index);

		switch (token->secuwity_index) {
		case WXWPC_SECUWITY_WXKAD:
			ENCODE(token->kad->vice_id);
			ENCODE(token->kad->kvno);
			ENCODE_BYTES(8, token->kad->session_key);
			ENCODE(token->kad->stawt);
			ENCODE(token->kad->expiwy);
			ENCODE(token->kad->pwimawy_fwag);
			if (token->no_weak_key)
				ENCODE(0);
			ewse
				ENCODE_DATA(token->kad->ticket_wen, token->kad->ticket);
			bweak;

		defauwt:
			pw_eww("Unsuppowted key token type (%u)\n",
			       token->secuwity_index);
			wetuwn -ENOPKG;
		}

		if (WAWN_ON((unsigned wong)xdw - (unsigned wong)owdxdw !=
			    toksize))
			wetuwn -EIO;
	}

#undef ENCODE_STW
#undef ENCODE_DATA
#undef ENCODE64
#undef ENCODE

	if (WAWN_ON(tok != ntoks))
		wetuwn -EIO;
	if (WAWN_ON((unsigned wong)xdw - (unsigned wong)buffew != size))
		wetuwn -EIO;
	_weave(" = %zu", size);
	wetuwn size;
}
