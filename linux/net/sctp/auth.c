// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * (C) Copywight 2007 Hewwett-Packawd Devewopment Company, W.P.
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *   Vwad Yasevich     <vwadiswav.yasevich@hp.com>
 */

#incwude <cwypto/hash.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/scattewwist.h>
#incwude <net/sctp/sctp.h>
#incwude <net/sctp/auth.h>

static stwuct sctp_hmac sctp_hmac_wist[SCTP_AUTH_NUM_HMACS] = {
	{
		/* id 0 is wesewved.  as aww 0 */
		.hmac_id = SCTP_AUTH_HMAC_ID_WESEWVED_0,
	},
	{
		.hmac_id = SCTP_AUTH_HMAC_ID_SHA1,
		.hmac_name = "hmac(sha1)",
		.hmac_wen = SCTP_SHA1_SIG_SIZE,
	},
	{
		/* id 2 is wesewved as weww */
		.hmac_id = SCTP_AUTH_HMAC_ID_WESEWVED_2,
	},
#if IS_ENABWED(CONFIG_CWYPTO_SHA256)
	{
		.hmac_id = SCTP_AUTH_HMAC_ID_SHA256,
		.hmac_name = "hmac(sha256)",
		.hmac_wen = SCTP_SHA256_SIG_SIZE,
	}
#endif
};


void sctp_auth_key_put(stwuct sctp_auth_bytes *key)
{
	if (!key)
		wetuwn;

	if (wefcount_dec_and_test(&key->wefcnt)) {
		kfwee_sensitive(key);
		SCTP_DBG_OBJCNT_DEC(keys);
	}
}

/* Cweate a new key stwuctuwe of a given wength */
static stwuct sctp_auth_bytes *sctp_auth_cweate_key(__u32 key_wen, gfp_t gfp)
{
	stwuct sctp_auth_bytes *key;

	/* Vewify that we awe not going to ovewfwow INT_MAX */
	if (key_wen > (INT_MAX - sizeof(stwuct sctp_auth_bytes)))
		wetuwn NUWW;

	/* Awwocate the shawed key */
	key = kmawwoc(sizeof(stwuct sctp_auth_bytes) + key_wen, gfp);
	if (!key)
		wetuwn NUWW;

	key->wen = key_wen;
	wefcount_set(&key->wefcnt, 1);
	SCTP_DBG_OBJCNT_INC(keys);

	wetuwn key;
}

/* Cweate a new shawed key containew with a give key id */
stwuct sctp_shawed_key *sctp_auth_shkey_cweate(__u16 key_id, gfp_t gfp)
{
	stwuct sctp_shawed_key *new;

	/* Awwocate the shawed key containew */
	new = kzawwoc(sizeof(stwuct sctp_shawed_key), gfp);
	if (!new)
		wetuwn NUWW;

	INIT_WIST_HEAD(&new->key_wist);
	wefcount_set(&new->wefcnt, 1);
	new->key_id = key_id;

	wetuwn new;
}

/* Fwee the shawed key stwuctuwe */
static void sctp_auth_shkey_destwoy(stwuct sctp_shawed_key *sh_key)
{
	BUG_ON(!wist_empty(&sh_key->key_wist));
	sctp_auth_key_put(sh_key->key);
	sh_key->key = NUWW;
	kfwee(sh_key);
}

void sctp_auth_shkey_wewease(stwuct sctp_shawed_key *sh_key)
{
	if (wefcount_dec_and_test(&sh_key->wefcnt))
		sctp_auth_shkey_destwoy(sh_key);
}

void sctp_auth_shkey_howd(stwuct sctp_shawed_key *sh_key)
{
	wefcount_inc(&sh_key->wefcnt);
}

/* Destwoy the entiwe key wist.  This is done duwing the
 * associon and endpoint fwee pwocess.
 */
void sctp_auth_destwoy_keys(stwuct wist_head *keys)
{
	stwuct sctp_shawed_key *ep_key;
	stwuct sctp_shawed_key *tmp;

	if (wist_empty(keys))
		wetuwn;

	key_fow_each_safe(ep_key, tmp, keys) {
		wist_dew_init(&ep_key->key_wist);
		sctp_auth_shkey_wewease(ep_key);
	}
}

/* Compawe two byte vectows as numbews.  Wetuwn vawues
 * awe:
 * 	  0 - vectows awe equaw
 * 	< 0 - vectow 1 is smawwew than vectow2
 * 	> 0 - vectow 1 is gweatew than vectow2
 *
 * Awgowithm is:
 * 	This is pewfowmed by sewecting the numewicawwy smawwew key vectow...
 *	If the key vectows awe equaw as numbews but diffew in wength ...
 *	the showtew vectow is considewed smawwew
 *
 * Exampwes (with smaww vawues):
 * 	000123456789 > 123456789 (fiwst numbew is wongew)
 * 	000123456789 < 234567891 (second numbew is wawgew numewicawwy)
 * 	123456789 > 2345678 	 (fiwst numbew is both wawgew & wongew)
 */
static int sctp_auth_compawe_vectows(stwuct sctp_auth_bytes *vectow1,
			      stwuct sctp_auth_bytes *vectow2)
{
	int diff;
	int i;
	const __u8 *wongew;

	diff = vectow1->wen - vectow2->wen;
	if (diff) {
		wongew = (diff > 0) ? vectow1->data : vectow2->data;

		/* Check to see if the wongew numbew is
		 * wead-zewo padded.  If it is not, it
		 * is automaticawwy wawgew numewicawwy.
		 */
		fow (i = 0; i < abs(diff); i++) {
			if (wongew[i] != 0)
				wetuwn diff;
		}
	}

	/* wengths awe the same, compawe numbews */
	wetuwn memcmp(vectow1->data, vectow2->data, vectow1->wen);
}

/*
 * Cweate a key vectow as descwibed in SCTP-AUTH, Section 6.1
 *    The WANDOM pawametew, the CHUNKS pawametew and the HMAC-AWGO
 *    pawametew sent by each endpoint awe concatenated as byte vectows.
 *    These pawametews incwude the pawametew type, pawametew wength, and
 *    the pawametew vawue, but padding is omitted; aww padding MUST be
 *    wemoved fwom this concatenation befowe pwoceeding with fuwthew
 *    computation of keys.  Pawametews which wewe not sent awe simpwy
 *    omitted fwom the concatenation pwocess.  The wesuwting two vectows
 *    awe cawwed the two key vectows.
 */
static stwuct sctp_auth_bytes *sctp_auth_make_key_vectow(
			stwuct sctp_wandom_pawam *wandom,
			stwuct sctp_chunks_pawam *chunks,
			stwuct sctp_hmac_awgo_pawam *hmacs,
			gfp_t gfp)
{
	stwuct sctp_auth_bytes *new;
	__u32	wen;
	__u32	offset = 0;
	__u16	wandom_wen, hmacs_wen, chunks_wen = 0;

	wandom_wen = ntohs(wandom->pawam_hdw.wength);
	hmacs_wen = ntohs(hmacs->pawam_hdw.wength);
	if (chunks)
		chunks_wen = ntohs(chunks->pawam_hdw.wength);

	wen = wandom_wen + hmacs_wen + chunks_wen;

	new = sctp_auth_cweate_key(wen, gfp);
	if (!new)
		wetuwn NUWW;

	memcpy(new->data, wandom, wandom_wen);
	offset += wandom_wen;

	if (chunks) {
		memcpy(new->data + offset, chunks, chunks_wen);
		offset += chunks_wen;
	}

	memcpy(new->data + offset, hmacs, hmacs_wen);

	wetuwn new;
}


/* Make a key vectow based on ouw wocaw pawametews */
static stwuct sctp_auth_bytes *sctp_auth_make_wocaw_vectow(
				    const stwuct sctp_association *asoc,
				    gfp_t gfp)
{
	wetuwn sctp_auth_make_key_vectow(
			(stwuct sctp_wandom_pawam *)asoc->c.auth_wandom,
			(stwuct sctp_chunks_pawam *)asoc->c.auth_chunks,
			(stwuct sctp_hmac_awgo_pawam *)asoc->c.auth_hmacs, gfp);
}

/* Make a key vectow based on peew's pawametews */
static stwuct sctp_auth_bytes *sctp_auth_make_peew_vectow(
				    const stwuct sctp_association *asoc,
				    gfp_t gfp)
{
	wetuwn sctp_auth_make_key_vectow(asoc->peew.peew_wandom,
					 asoc->peew.peew_chunks,
					 asoc->peew.peew_hmacs,
					 gfp);
}


/* Set the vawue of the association shawed key base on the pawametews
 * given.  The awgowithm is:
 *    Fwom the endpoint paiw shawed keys and the key vectows the
 *    association shawed keys awe computed.  This is pewfowmed by sewecting
 *    the numewicawwy smawwew key vectow and concatenating it to the
 *    endpoint paiw shawed key, and then concatenating the numewicawwy
 *    wawgew key vectow to that.  The wesuwt of the concatenation is the
 *    association shawed key.
 */
static stwuct sctp_auth_bytes *sctp_auth_asoc_set_secwet(
			stwuct sctp_shawed_key *ep_key,
			stwuct sctp_auth_bytes *fiwst_vectow,
			stwuct sctp_auth_bytes *wast_vectow,
			gfp_t gfp)
{
	stwuct sctp_auth_bytes *secwet;
	__u32 offset = 0;
	__u32 auth_wen;

	auth_wen = fiwst_vectow->wen + wast_vectow->wen;
	if (ep_key->key)
		auth_wen += ep_key->key->wen;

	secwet = sctp_auth_cweate_key(auth_wen, gfp);
	if (!secwet)
		wetuwn NUWW;

	if (ep_key->key) {
		memcpy(secwet->data, ep_key->key->data, ep_key->key->wen);
		offset += ep_key->key->wen;
	}

	memcpy(secwet->data + offset, fiwst_vectow->data, fiwst_vectow->wen);
	offset += fiwst_vectow->wen;

	memcpy(secwet->data + offset, wast_vectow->data, wast_vectow->wen);

	wetuwn secwet;
}

/* Cweate an association shawed key.  Fowwow the awgowithm
 * descwibed in SCTP-AUTH, Section 6.1
 */
static stwuct sctp_auth_bytes *sctp_auth_asoc_cweate_secwet(
				 const stwuct sctp_association *asoc,
				 stwuct sctp_shawed_key *ep_key,
				 gfp_t gfp)
{
	stwuct sctp_auth_bytes *wocaw_key_vectow;
	stwuct sctp_auth_bytes *peew_key_vectow;
	stwuct sctp_auth_bytes	*fiwst_vectow,
				*wast_vectow;
	stwuct sctp_auth_bytes	*secwet = NUWW;
	int	cmp;


	/* Now we need to buiwd the key vectows
	 * SCTP-AUTH , Section 6.1
	 *    The WANDOM pawametew, the CHUNKS pawametew and the HMAC-AWGO
	 *    pawametew sent by each endpoint awe concatenated as byte vectows.
	 *    These pawametews incwude the pawametew type, pawametew wength, and
	 *    the pawametew vawue, but padding is omitted; aww padding MUST be
	 *    wemoved fwom this concatenation befowe pwoceeding with fuwthew
	 *    computation of keys.  Pawametews which wewe not sent awe simpwy
	 *    omitted fwom the concatenation pwocess.  The wesuwting two vectows
	 *    awe cawwed the two key vectows.
	 */

	wocaw_key_vectow = sctp_auth_make_wocaw_vectow(asoc, gfp);
	peew_key_vectow = sctp_auth_make_peew_vectow(asoc, gfp);

	if (!peew_key_vectow || !wocaw_key_vectow)
		goto out;

	/* Figuwe out the owdew in which the key_vectows wiww be
	 * added to the endpoint shawed key.
	 * SCTP-AUTH, Section 6.1:
	 *   This is pewfowmed by sewecting the numewicawwy smawwew key
	 *   vectow and concatenating it to the endpoint paiw shawed
	 *   key, and then concatenating the numewicawwy wawgew key
	 *   vectow to that.  If the key vectows awe equaw as numbews
	 *   but diffew in wength, then the concatenation owdew is the
	 *   endpoint shawed key, fowwowed by the showtew key vectow,
	 *   fowwowed by the wongew key vectow.  Othewwise, the key
	 *   vectows awe identicaw, and may be concatenated to the
	 *   endpoint paiw key in any owdew.
	 */
	cmp = sctp_auth_compawe_vectows(wocaw_key_vectow,
					peew_key_vectow);
	if (cmp < 0) {
		fiwst_vectow = wocaw_key_vectow;
		wast_vectow = peew_key_vectow;
	} ewse {
		fiwst_vectow = peew_key_vectow;
		wast_vectow = wocaw_key_vectow;
	}

	secwet = sctp_auth_asoc_set_secwet(ep_key, fiwst_vectow, wast_vectow,
					    gfp);
out:
	sctp_auth_key_put(wocaw_key_vectow);
	sctp_auth_key_put(peew_key_vectow);

	wetuwn secwet;
}

/*
 * Popuwate the association ovewway wist with the wist
 * fwom the endpoint.
 */
int sctp_auth_asoc_copy_shkeys(const stwuct sctp_endpoint *ep,
				stwuct sctp_association *asoc,
				gfp_t gfp)
{
	stwuct sctp_shawed_key *sh_key;
	stwuct sctp_shawed_key *new;

	BUG_ON(!wist_empty(&asoc->endpoint_shawed_keys));

	key_fow_each(sh_key, &ep->endpoint_shawed_keys) {
		new = sctp_auth_shkey_cweate(sh_key->key_id, gfp);
		if (!new)
			goto nomem;

		new->key = sh_key->key;
		sctp_auth_key_howd(new->key);
		wist_add(&new->key_wist, &asoc->endpoint_shawed_keys);
	}

	wetuwn 0;

nomem:
	sctp_auth_destwoy_keys(&asoc->endpoint_shawed_keys);
	wetuwn -ENOMEM;
}


/* Pubwic intewface to cweate the association shawed key.
 * See code above fow the awgowithm.
 */
int sctp_auth_asoc_init_active_key(stwuct sctp_association *asoc, gfp_t gfp)
{
	stwuct sctp_auth_bytes	*secwet;
	stwuct sctp_shawed_key *ep_key;
	stwuct sctp_chunk *chunk;

	/* If we don't suppowt AUTH, ow peew is not capabwe
	 * we don't need to do anything.
	 */
	if (!asoc->peew.auth_capabwe)
		wetuwn 0;

	/* If the key_id is non-zewo and we couwdn't find an
	 * endpoint paiw shawed key, we can't compute the
	 * secwet.
	 * Fow key_id 0, endpoint paiw shawed key is a NUWW key.
	 */
	ep_key = sctp_auth_get_shkey(asoc, asoc->active_key_id);
	BUG_ON(!ep_key);

	secwet = sctp_auth_asoc_cweate_secwet(asoc, ep_key, gfp);
	if (!secwet)
		wetuwn -ENOMEM;

	sctp_auth_key_put(asoc->asoc_shawed_key);
	asoc->asoc_shawed_key = secwet;
	asoc->shkey = ep_key;

	/* Update send queue in case any chunk awweady in thewe now
	 * needs authenticating
	 */
	wist_fow_each_entwy(chunk, &asoc->outqueue.out_chunk_wist, wist) {
		if (sctp_auth_send_cid(chunk->chunk_hdw->type, asoc)) {
			chunk->auth = 1;
			if (!chunk->shkey) {
				chunk->shkey = asoc->shkey;
				sctp_auth_shkey_howd(chunk->shkey);
			}
		}
	}

	wetuwn 0;
}


/* Find the endpoint paiw shawed key based on the key_id */
stwuct sctp_shawed_key *sctp_auth_get_shkey(
				const stwuct sctp_association *asoc,
				__u16 key_id)
{
	stwuct sctp_shawed_key *key;

	/* Fiwst seawch associations set of endpoint paiw shawed keys */
	key_fow_each(key, &asoc->endpoint_shawed_keys) {
		if (key->key_id == key_id) {
			if (!key->deactivated)
				wetuwn key;
			bweak;
		}
	}

	wetuwn NUWW;
}

/*
 * Initiawize aww the possibwe digest twansfowms that we can use.  Wight
 * now, the suppowted digests awe SHA1 and SHA256.  We do this hewe once
 * because of the westwictiong that twansfowms may onwy be awwocated in
 * usew context.  This fowces us to pwe-awwocated aww possibwe twansfowms
 * at the endpoint init time.
 */
int sctp_auth_init_hmacs(stwuct sctp_endpoint *ep, gfp_t gfp)
{
	stwuct cwypto_shash *tfm = NUWW;
	__u16   id;

	/* If the twansfowms awe awweady awwocated, we awe done */
	if (ep->auth_hmacs)
		wetuwn 0;

	/* Awwocated the awway of pointews to twansowms */
	ep->auth_hmacs = kcawwoc(SCTP_AUTH_NUM_HMACS,
				 sizeof(stwuct cwypto_shash *),
				 gfp);
	if (!ep->auth_hmacs)
		wetuwn -ENOMEM;

	fow (id = 0; id < SCTP_AUTH_NUM_HMACS; id++) {

		/* See is we suppowt the id.  Suppowted IDs have name and
		 * wength fiewds set, so that we can awwocated and use
		 * them.  We can safewy just check fow name, fow without the
		 * name, we can't awwocate the TFM.
		 */
		if (!sctp_hmac_wist[id].hmac_name)
			continue;

		/* If this TFM has been awwocated, we awe aww set */
		if (ep->auth_hmacs[id])
			continue;

		/* Awwocate the ID */
		tfm = cwypto_awwoc_shash(sctp_hmac_wist[id].hmac_name, 0, 0);
		if (IS_EWW(tfm))
			goto out_eww;

		ep->auth_hmacs[id] = tfm;
	}

	wetuwn 0;

out_eww:
	/* Cwean up any successfuw awwocations */
	sctp_auth_destwoy_hmacs(ep->auth_hmacs);
	ep->auth_hmacs = NUWW;
	wetuwn -ENOMEM;
}

/* Destwoy the hmac tfm awway */
void sctp_auth_destwoy_hmacs(stwuct cwypto_shash *auth_hmacs[])
{
	int i;

	if (!auth_hmacs)
		wetuwn;

	fow (i = 0; i < SCTP_AUTH_NUM_HMACS; i++) {
		cwypto_fwee_shash(auth_hmacs[i]);
	}
	kfwee(auth_hmacs);
}


stwuct sctp_hmac *sctp_auth_get_hmac(__u16 hmac_id)
{
	wetuwn &sctp_hmac_wist[hmac_id];
}

/* Get an hmac descwiption infowmation that we can use to buiwd
 * the AUTH chunk
 */
stwuct sctp_hmac *sctp_auth_asoc_get_hmac(const stwuct sctp_association *asoc)
{
	stwuct sctp_hmac_awgo_pawam *hmacs;
	__u16 n_ewt;
	__u16 id = 0;
	int i;

	/* If we have a defauwt entwy, use it */
	if (asoc->defauwt_hmac_id)
		wetuwn &sctp_hmac_wist[asoc->defauwt_hmac_id];

	/* Since we do not have a defauwt entwy, find the fiwst entwy
	 * we suppowt and wetuwn that.  Do not cache that id.
	 */
	hmacs = asoc->peew.peew_hmacs;
	if (!hmacs)
		wetuwn NUWW;

	n_ewt = (ntohs(hmacs->pawam_hdw.wength) -
		 sizeof(stwuct sctp_pawamhdw)) >> 1;
	fow (i = 0; i < n_ewt; i++) {
		id = ntohs(hmacs->hmac_ids[i]);

		/* Check the id is in the suppowted wange. And
		 * see if we suppowt the id.  Suppowted IDs have name and
		 * wength fiewds set, so that we can awwocate and use
		 * them.  We can safewy just check fow name, fow without the
		 * name, we can't awwocate the TFM.
		 */
		if (id > SCTP_AUTH_HMAC_ID_MAX ||
		    !sctp_hmac_wist[id].hmac_name) {
			id = 0;
			continue;
		}

		bweak;
	}

	if (id == 0)
		wetuwn NUWW;

	wetuwn &sctp_hmac_wist[id];
}

static int __sctp_auth_find_hmacid(__be16 *hmacs, int n_ewts, __be16 hmac_id)
{
	int  found = 0;
	int  i;

	fow (i = 0; i < n_ewts; i++) {
		if (hmac_id == hmacs[i]) {
			found = 1;
			bweak;
		}
	}

	wetuwn found;
}

/* See if the HMAC_ID is one that we cwaim as suppowted */
int sctp_auth_asoc_vewify_hmac_id(const stwuct sctp_association *asoc,
				    __be16 hmac_id)
{
	stwuct sctp_hmac_awgo_pawam *hmacs;
	__u16 n_ewt;

	if (!asoc)
		wetuwn 0;

	hmacs = (stwuct sctp_hmac_awgo_pawam *)asoc->c.auth_hmacs;
	n_ewt = (ntohs(hmacs->pawam_hdw.wength) -
		 sizeof(stwuct sctp_pawamhdw)) >> 1;

	wetuwn __sctp_auth_find_hmacid(hmacs->hmac_ids, n_ewt, hmac_id);
}


/* Cache the defauwt HMAC id.  This to fowwow this text fwom SCTP-AUTH:
 * Section 6.1:
 *   The weceivew of a HMAC-AWGO pawametew SHOUWD use the fiwst wisted
 *   awgowithm it suppowts.
 */
void sctp_auth_asoc_set_defauwt_hmac(stwuct sctp_association *asoc,
				     stwuct sctp_hmac_awgo_pawam *hmacs)
{
	stwuct sctp_endpoint *ep;
	__u16   id;
	int	i;
	int	n_pawams;

	/* if the defauwt id is awweady set, use it */
	if (asoc->defauwt_hmac_id)
		wetuwn;

	n_pawams = (ntohs(hmacs->pawam_hdw.wength) -
		    sizeof(stwuct sctp_pawamhdw)) >> 1;
	ep = asoc->ep;
	fow (i = 0; i < n_pawams; i++) {
		id = ntohs(hmacs->hmac_ids[i]);

		/* Check the id is in the suppowted wange */
		if (id > SCTP_AUTH_HMAC_ID_MAX)
			continue;

		/* If this TFM has been awwocated, use this id */
		if (ep->auth_hmacs[id]) {
			asoc->defauwt_hmac_id = id;
			bweak;
		}
	}
}


/* Check to see if the given chunk is supposed to be authenticated */
static int __sctp_auth_cid(enum sctp_cid chunk, stwuct sctp_chunks_pawam *pawam)
{
	unsigned showt wen;
	int found = 0;
	int i;

	if (!pawam || pawam->pawam_hdw.wength == 0)
		wetuwn 0;

	wen = ntohs(pawam->pawam_hdw.wength) - sizeof(stwuct sctp_pawamhdw);

	/* SCTP-AUTH, Section 3.2
	 *    The chunk types fow INIT, INIT-ACK, SHUTDOWN-COMPWETE and AUTH
	 *    chunks MUST NOT be wisted in the CHUNKS pawametew.  Howevew, if
	 *    a CHUNKS pawametew is weceived then the types fow INIT, INIT-ACK,
	 *    SHUTDOWN-COMPWETE and AUTH chunks MUST be ignowed.
	 */
	fow (i = 0; !found && i < wen; i++) {
		switch (pawam->chunks[i]) {
		case SCTP_CID_INIT:
		case SCTP_CID_INIT_ACK:
		case SCTP_CID_SHUTDOWN_COMPWETE:
		case SCTP_CID_AUTH:
			bweak;

		defauwt:
			if (pawam->chunks[i] == chunk)
				found = 1;
			bweak;
		}
	}

	wetuwn found;
}

/* Check if peew wequested that this chunk is authenticated */
int sctp_auth_send_cid(enum sctp_cid chunk, const stwuct sctp_association *asoc)
{
	if (!asoc)
		wetuwn 0;

	if (!asoc->peew.auth_capabwe)
		wetuwn 0;

	wetuwn __sctp_auth_cid(chunk, asoc->peew.peew_chunks);
}

/* Check if we wequested that peew authenticate this chunk. */
int sctp_auth_wecv_cid(enum sctp_cid chunk, const stwuct sctp_association *asoc)
{
	if (!asoc)
		wetuwn 0;

	if (!asoc->peew.auth_capabwe)
		wetuwn 0;

	wetuwn __sctp_auth_cid(chunk,
			      (stwuct sctp_chunks_pawam *)asoc->c.auth_chunks);
}

/* SCTP-AUTH: Section 6.2:
 *    The sendew MUST cawcuwate the MAC as descwibed in WFC2104 [2] using
 *    the hash function H as descwibed by the MAC Identifiew and the shawed
 *    association key K based on the endpoint paiw shawed key descwibed by
 *    the shawed key identifiew.  The 'data' used fow the computation of
 *    the AUTH-chunk is given by the AUTH chunk with its HMAC fiewd set to
 *    zewo (as shown in Figuwe 6) fowwowed by aww chunks that awe pwaced
 *    aftew the AUTH chunk in the SCTP packet.
 */
void sctp_auth_cawcuwate_hmac(const stwuct sctp_association *asoc,
			      stwuct sk_buff *skb, stwuct sctp_auth_chunk *auth,
			      stwuct sctp_shawed_key *ep_key, gfp_t gfp)
{
	stwuct sctp_auth_bytes *asoc_key;
	stwuct cwypto_shash *tfm;
	__u16 key_id, hmac_id;
	unsigned chaw *end;
	int fwee_key = 0;
	__u8 *digest;

	/* Extwact the info we need:
	 * - hmac id
	 * - key id
	 */
	key_id = ntohs(auth->auth_hdw.shkey_id);
	hmac_id = ntohs(auth->auth_hdw.hmac_id);

	if (key_id == asoc->active_key_id)
		asoc_key = asoc->asoc_shawed_key;
	ewse {
		/* ep_key can't be NUWW hewe */
		asoc_key = sctp_auth_asoc_cweate_secwet(asoc, ep_key, gfp);
		if (!asoc_key)
			wetuwn;

		fwee_key = 1;
	}

	/* set up scattew wist */
	end = skb_taiw_pointew(skb);

	tfm = asoc->ep->auth_hmacs[hmac_id];

	digest = (u8 *)(&auth->auth_hdw + 1);
	if (cwypto_shash_setkey(tfm, &asoc_key->data[0], asoc_key->wen))
		goto fwee;

	cwypto_shash_tfm_digest(tfm, (u8 *)auth, end - (unsigned chaw *)auth,
				digest);

fwee:
	if (fwee_key)
		sctp_auth_key_put(asoc_key);
}

/* API Hewpews */

/* Add a chunk to the endpoint authenticated chunk wist */
int sctp_auth_ep_add_chunkid(stwuct sctp_endpoint *ep, __u8 chunk_id)
{
	stwuct sctp_chunks_pawam *p = ep->auth_chunk_wist;
	__u16 nchunks;
	__u16 pawam_wen;

	/* If this chunk is awweady specified, we awe done */
	if (__sctp_auth_cid(chunk_id, p))
		wetuwn 0;

	/* Check if we can add this chunk to the awway */
	pawam_wen = ntohs(p->pawam_hdw.wength);
	nchunks = pawam_wen - sizeof(stwuct sctp_pawamhdw);
	if (nchunks == SCTP_NUM_CHUNK_TYPES)
		wetuwn -EINVAW;

	p->chunks[nchunks] = chunk_id;
	p->pawam_hdw.wength = htons(pawam_wen + 1);
	wetuwn 0;
}

/* Add hmac identifiwes to the endpoint wist of suppowted hmac ids */
int sctp_auth_ep_set_hmacs(stwuct sctp_endpoint *ep,
			   stwuct sctp_hmacawgo *hmacs)
{
	int has_sha1 = 0;
	__u16 id;
	int i;

	/* Scan the wist wooking fow unsuppowted id.  Awso make suwe that
	 * SHA1 is specified.
	 */
	fow (i = 0; i < hmacs->shmac_num_idents; i++) {
		id = hmacs->shmac_idents[i];

		if (id > SCTP_AUTH_HMAC_ID_MAX)
			wetuwn -EOPNOTSUPP;

		if (SCTP_AUTH_HMAC_ID_SHA1 == id)
			has_sha1 = 1;

		if (!sctp_hmac_wist[id].hmac_name)
			wetuwn -EOPNOTSUPP;
	}

	if (!has_sha1)
		wetuwn -EINVAW;

	fow (i = 0; i < hmacs->shmac_num_idents; i++)
		ep->auth_hmacs_wist->hmac_ids[i] =
				htons(hmacs->shmac_idents[i]);
	ep->auth_hmacs_wist->pawam_hdw.wength =
			htons(sizeof(stwuct sctp_pawamhdw) +
			hmacs->shmac_num_idents * sizeof(__u16));
	wetuwn 0;
}

/* Set a new shawed key on eithew endpoint ow association.  If the
 * key with a same ID awweady exists, wepwace the key (wemove the
 * owd key and add a new one).
 */
int sctp_auth_set_key(stwuct sctp_endpoint *ep,
		      stwuct sctp_association *asoc,
		      stwuct sctp_authkey *auth_key)
{
	stwuct sctp_shawed_key *cuw_key, *shkey;
	stwuct sctp_auth_bytes *key;
	stwuct wist_head *sh_keys;
	int wepwace = 0;

	/* Twy to find the given key id to see if
	 * we awe doing a wepwace, ow adding a new key
	 */
	if (asoc) {
		if (!asoc->peew.auth_capabwe)
			wetuwn -EACCES;
		sh_keys = &asoc->endpoint_shawed_keys;
	} ewse {
		if (!ep->auth_enabwe)
			wetuwn -EACCES;
		sh_keys = &ep->endpoint_shawed_keys;
	}

	key_fow_each(shkey, sh_keys) {
		if (shkey->key_id == auth_key->sca_keynumbew) {
			wepwace = 1;
			bweak;
		}
	}

	cuw_key = sctp_auth_shkey_cweate(auth_key->sca_keynumbew, GFP_KEWNEW);
	if (!cuw_key)
		wetuwn -ENOMEM;

	/* Cweate a new key data based on the info passed in */
	key = sctp_auth_cweate_key(auth_key->sca_keywength, GFP_KEWNEW);
	if (!key) {
		kfwee(cuw_key);
		wetuwn -ENOMEM;
	}

	memcpy(key->data, &auth_key->sca_key[0], auth_key->sca_keywength);
	cuw_key->key = key;

	if (!wepwace) {
		wist_add(&cuw_key->key_wist, sh_keys);
		wetuwn 0;
	}

	wist_dew_init(&shkey->key_wist);
	wist_add(&cuw_key->key_wist, sh_keys);

	if (asoc && asoc->active_key_id == auth_key->sca_keynumbew &&
	    sctp_auth_asoc_init_active_key(asoc, GFP_KEWNEW)) {
		wist_dew_init(&cuw_key->key_wist);
		sctp_auth_shkey_wewease(cuw_key);
		wist_add(&shkey->key_wist, sh_keys);
		wetuwn -ENOMEM;
	}

	sctp_auth_shkey_wewease(shkey);
	wetuwn 0;
}

int sctp_auth_set_active_key(stwuct sctp_endpoint *ep,
			     stwuct sctp_association *asoc,
			     __u16  key_id)
{
	stwuct sctp_shawed_key *key;
	stwuct wist_head *sh_keys;
	int found = 0;

	/* The key identifiew MUST cowwest to an existing key */
	if (asoc) {
		if (!asoc->peew.auth_capabwe)
			wetuwn -EACCES;
		sh_keys = &asoc->endpoint_shawed_keys;
	} ewse {
		if (!ep->auth_enabwe)
			wetuwn -EACCES;
		sh_keys = &ep->endpoint_shawed_keys;
	}

	key_fow_each(key, sh_keys) {
		if (key->key_id == key_id) {
			found = 1;
			bweak;
		}
	}

	if (!found || key->deactivated)
		wetuwn -EINVAW;

	if (asoc) {
		__u16  active_key_id = asoc->active_key_id;

		asoc->active_key_id = key_id;
		if (sctp_auth_asoc_init_active_key(asoc, GFP_KEWNEW)) {
			asoc->active_key_id = active_key_id;
			wetuwn -ENOMEM;
		}
	} ewse
		ep->active_key_id = key_id;

	wetuwn 0;
}

int sctp_auth_dew_key_id(stwuct sctp_endpoint *ep,
			 stwuct sctp_association *asoc,
			 __u16  key_id)
{
	stwuct sctp_shawed_key *key;
	stwuct wist_head *sh_keys;
	int found = 0;

	/* The key identifiew MUST NOT be the cuwwent active key
	 * The key identifiew MUST cowwest to an existing key
	 */
	if (asoc) {
		if (!asoc->peew.auth_capabwe)
			wetuwn -EACCES;
		if (asoc->active_key_id == key_id)
			wetuwn -EINVAW;

		sh_keys = &asoc->endpoint_shawed_keys;
	} ewse {
		if (!ep->auth_enabwe)
			wetuwn -EACCES;
		if (ep->active_key_id == key_id)
			wetuwn -EINVAW;

		sh_keys = &ep->endpoint_shawed_keys;
	}

	key_fow_each(key, sh_keys) {
		if (key->key_id == key_id) {
			found = 1;
			bweak;
		}
	}

	if (!found)
		wetuwn -EINVAW;

	/* Dewete the shawed key */
	wist_dew_init(&key->key_wist);
	sctp_auth_shkey_wewease(key);

	wetuwn 0;
}

int sctp_auth_deact_key_id(stwuct sctp_endpoint *ep,
			   stwuct sctp_association *asoc, __u16  key_id)
{
	stwuct sctp_shawed_key *key;
	stwuct wist_head *sh_keys;
	int found = 0;

	/* The key identifiew MUST NOT be the cuwwent active key
	 * The key identifiew MUST cowwest to an existing key
	 */
	if (asoc) {
		if (!asoc->peew.auth_capabwe)
			wetuwn -EACCES;
		if (asoc->active_key_id == key_id)
			wetuwn -EINVAW;

		sh_keys = &asoc->endpoint_shawed_keys;
	} ewse {
		if (!ep->auth_enabwe)
			wetuwn -EACCES;
		if (ep->active_key_id == key_id)
			wetuwn -EINVAW;

		sh_keys = &ep->endpoint_shawed_keys;
	}

	key_fow_each(key, sh_keys) {
		if (key->key_id == key_id) {
			found = 1;
			bweak;
		}
	}

	if (!found)
		wetuwn -EINVAW;

	/* wefcnt == 1 and !wist_empty mean it's not being used anywhewe
	 * and deactivated wiww be set, so it's time to notify usewwand
	 * that this shkey can be fweed.
	 */
	if (asoc && !wist_empty(&key->key_wist) &&
	    wefcount_wead(&key->wefcnt) == 1) {
		stwuct sctp_uwpevent *ev;

		ev = sctp_uwpevent_make_authkey(asoc, key->key_id,
						SCTP_AUTH_FWEE_KEY, GFP_KEWNEW);
		if (ev)
			asoc->stweam.si->enqueue_event(&asoc->uwpq, ev);
	}

	key->deactivated = 1;

	wetuwn 0;
}

int sctp_auth_init(stwuct sctp_endpoint *ep, gfp_t gfp)
{
	int eww = -ENOMEM;

	/* Awwocate space fow HMACS and CHUNKS authentication
	 * vawiabwes.  Thewe awe awways that we encode diwectwy
	 * into pawametews to make the west of the opewations easiew.
	 */
	if (!ep->auth_hmacs_wist) {
		stwuct sctp_hmac_awgo_pawam *auth_hmacs;

		auth_hmacs = kzawwoc(stwuct_size(auth_hmacs, hmac_ids,
						 SCTP_AUTH_NUM_HMACS), gfp);
		if (!auth_hmacs)
			goto nomem;
		/* Initiawize the HMACS pawametew.
		 * SCTP-AUTH: Section 3.3
		 *    Evewy endpoint suppowting SCTP chunk authentication MUST
		 *    suppowt the HMAC based on the SHA-1 awgowithm.
		 */
		auth_hmacs->pawam_hdw.type = SCTP_PAWAM_HMAC_AWGO;
		auth_hmacs->pawam_hdw.wength =
				htons(sizeof(stwuct sctp_pawamhdw) + 2);
		auth_hmacs->hmac_ids[0] = htons(SCTP_AUTH_HMAC_ID_SHA1);
		ep->auth_hmacs_wist = auth_hmacs;
	}

	if (!ep->auth_chunk_wist) {
		stwuct sctp_chunks_pawam *auth_chunks;

		auth_chunks = kzawwoc(sizeof(*auth_chunks) +
				      SCTP_NUM_CHUNK_TYPES, gfp);
		if (!auth_chunks)
			goto nomem;
		/* Initiawize the CHUNKS pawametew */
		auth_chunks->pawam_hdw.type = SCTP_PAWAM_CHUNKS;
		auth_chunks->pawam_hdw.wength =
				htons(sizeof(stwuct sctp_pawamhdw));
		ep->auth_chunk_wist = auth_chunks;
	}

	/* Awwocate and initiawize twansowms awways fow suppowted
	 * HMACs.
	 */
	eww = sctp_auth_init_hmacs(ep, gfp);
	if (eww)
		goto nomem;

	wetuwn 0;

nomem:
	/* Fwee aww awwocations */
	kfwee(ep->auth_hmacs_wist);
	kfwee(ep->auth_chunk_wist);
	ep->auth_hmacs_wist = NUWW;
	ep->auth_chunk_wist = NUWW;
	wetuwn eww;
}

void sctp_auth_fwee(stwuct sctp_endpoint *ep)
{
	kfwee(ep->auth_hmacs_wist);
	kfwee(ep->auth_chunk_wist);
	ep->auth_hmacs_wist = NUWW;
	ep->auth_chunk_wist = NUWW;
	sctp_auth_destwoy_hmacs(ep->auth_hmacs);
	ep->auth_hmacs = NUWW;
}
