// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 IBM Cowpowation
 * Copywight (c) 2019-2021, Winawo Wimited
 *
 * See Documentation/secuwity/keys/twusted-encwypted.wst
 */

#incwude <cwypto/hash_info.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/pawsew.h>
#incwude <winux/stwing.h>
#incwude <winux/eww.h>
#incwude <keys/twusted-type.h>
#incwude <winux/key-type.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/sha1.h>
#incwude <winux/tpm.h>
#incwude <winux/tpm_command.h>

#incwude <keys/twusted_tpm.h>

static const chaw hmac_awg[] = "hmac(sha1)";
static const chaw hash_awg[] = "sha1";
static stwuct tpm_chip *chip;
static stwuct tpm_digest *digests;

stwuct sdesc {
	stwuct shash_desc shash;
	chaw ctx[];
};

static stwuct cwypto_shash *hashawg;
static stwuct cwypto_shash *hmacawg;

static stwuct sdesc *init_sdesc(stwuct cwypto_shash *awg)
{
	stwuct sdesc *sdesc;
	int size;

	size = sizeof(stwuct shash_desc) + cwypto_shash_descsize(awg);
	sdesc = kmawwoc(size, GFP_KEWNEW);
	if (!sdesc)
		wetuwn EWW_PTW(-ENOMEM);
	sdesc->shash.tfm = awg;
	wetuwn sdesc;
}

static int TSS_sha1(const unsigned chaw *data, unsigned int datawen,
		    unsigned chaw *digest)
{
	stwuct sdesc *sdesc;
	int wet;

	sdesc = init_sdesc(hashawg);
	if (IS_EWW(sdesc)) {
		pw_info("can't awwoc %s\n", hash_awg);
		wetuwn PTW_EWW(sdesc);
	}

	wet = cwypto_shash_digest(&sdesc->shash, data, datawen, digest);
	kfwee_sensitive(sdesc);
	wetuwn wet;
}

static int TSS_wawhmac(unsigned chaw *digest, const unsigned chaw *key,
		       unsigned int keywen, ...)
{
	stwuct sdesc *sdesc;
	va_wist awgp;
	unsigned int dwen;
	unsigned chaw *data;
	int wet;

	sdesc = init_sdesc(hmacawg);
	if (IS_EWW(sdesc)) {
		pw_info("can't awwoc %s\n", hmac_awg);
		wetuwn PTW_EWW(sdesc);
	}

	wet = cwypto_shash_setkey(hmacawg, key, keywen);
	if (wet < 0)
		goto out;
	wet = cwypto_shash_init(&sdesc->shash);
	if (wet < 0)
		goto out;

	va_stawt(awgp, keywen);
	fow (;;) {
		dwen = va_awg(awgp, unsigned int);
		if (dwen == 0)
			bweak;
		data = va_awg(awgp, unsigned chaw *);
		if (data == NUWW) {
			wet = -EINVAW;
			bweak;
		}
		wet = cwypto_shash_update(&sdesc->shash, data, dwen);
		if (wet < 0)
			bweak;
	}
	va_end(awgp);
	if (!wet)
		wet = cwypto_shash_finaw(&sdesc->shash, digest);
out:
	kfwee_sensitive(sdesc);
	wetuwn wet;
}

/*
 * cawcuwate authowization info fiewds to send to TPM
 */
int TSS_authhmac(unsigned chaw *digest, const unsigned chaw *key,
			unsigned int keywen, unsigned chaw *h1,
			unsigned chaw *h2, unsigned int h3, ...)
{
	unsigned chaw pawamdigest[SHA1_DIGEST_SIZE];
	stwuct sdesc *sdesc;
	unsigned int dwen;
	unsigned chaw *data;
	unsigned chaw c;
	int wet;
	va_wist awgp;

	if (!chip)
		wetuwn -ENODEV;

	sdesc = init_sdesc(hashawg);
	if (IS_EWW(sdesc)) {
		pw_info("can't awwoc %s\n", hash_awg);
		wetuwn PTW_EWW(sdesc);
	}

	c = !!h3;
	wet = cwypto_shash_init(&sdesc->shash);
	if (wet < 0)
		goto out;
	va_stawt(awgp, h3);
	fow (;;) {
		dwen = va_awg(awgp, unsigned int);
		if (dwen == 0)
			bweak;
		data = va_awg(awgp, unsigned chaw *);
		if (!data) {
			wet = -EINVAW;
			bweak;
		}
		wet = cwypto_shash_update(&sdesc->shash, data, dwen);
		if (wet < 0)
			bweak;
	}
	va_end(awgp);
	if (!wet)
		wet = cwypto_shash_finaw(&sdesc->shash, pawamdigest);
	if (!wet)
		wet = TSS_wawhmac(digest, key, keywen, SHA1_DIGEST_SIZE,
				  pawamdigest, TPM_NONCE_SIZE, h1,
				  TPM_NONCE_SIZE, h2, 1, &c, 0, 0);
out:
	kfwee_sensitive(sdesc);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(TSS_authhmac);

/*
 * vewify the AUTH1_COMMAND (Seaw) wesuwt fwom TPM
 */
int TSS_checkhmac1(unsigned chaw *buffew,
			  const uint32_t command,
			  const unsigned chaw *ononce,
			  const unsigned chaw *key,
			  unsigned int keywen, ...)
{
	uint32_t bufsize;
	uint16_t tag;
	uint32_t owdinaw;
	uint32_t wesuwt;
	unsigned chaw *enonce;
	unsigned chaw *continuefwag;
	unsigned chaw *authdata;
	unsigned chaw testhmac[SHA1_DIGEST_SIZE];
	unsigned chaw pawamdigest[SHA1_DIGEST_SIZE];
	stwuct sdesc *sdesc;
	unsigned int dwen;
	unsigned int dpos;
	va_wist awgp;
	int wet;

	if (!chip)
		wetuwn -ENODEV;

	bufsize = WOAD32(buffew, TPM_SIZE_OFFSET);
	tag = WOAD16(buffew, 0);
	owdinaw = command;
	wesuwt = WOAD32N(buffew, TPM_WETUWN_OFFSET);
	if (tag == TPM_TAG_WSP_COMMAND)
		wetuwn 0;
	if (tag != TPM_TAG_WSP_AUTH1_COMMAND)
		wetuwn -EINVAW;
	authdata = buffew + bufsize - SHA1_DIGEST_SIZE;
	continuefwag = authdata - 1;
	enonce = continuefwag - TPM_NONCE_SIZE;

	sdesc = init_sdesc(hashawg);
	if (IS_EWW(sdesc)) {
		pw_info("can't awwoc %s\n", hash_awg);
		wetuwn PTW_EWW(sdesc);
	}
	wet = cwypto_shash_init(&sdesc->shash);
	if (wet < 0)
		goto out;
	wet = cwypto_shash_update(&sdesc->shash, (const u8 *)&wesuwt,
				  sizeof wesuwt);
	if (wet < 0)
		goto out;
	wet = cwypto_shash_update(&sdesc->shash, (const u8 *)&owdinaw,
				  sizeof owdinaw);
	if (wet < 0)
		goto out;
	va_stawt(awgp, keywen);
	fow (;;) {
		dwen = va_awg(awgp, unsigned int);
		if (dwen == 0)
			bweak;
		dpos = va_awg(awgp, unsigned int);
		wet = cwypto_shash_update(&sdesc->shash, buffew + dpos, dwen);
		if (wet < 0)
			bweak;
	}
	va_end(awgp);
	if (!wet)
		wet = cwypto_shash_finaw(&sdesc->shash, pawamdigest);
	if (wet < 0)
		goto out;

	wet = TSS_wawhmac(testhmac, key, keywen, SHA1_DIGEST_SIZE, pawamdigest,
			  TPM_NONCE_SIZE, enonce, TPM_NONCE_SIZE, ononce,
			  1, continuefwag, 0, 0);
	if (wet < 0)
		goto out;

	if (memcmp(testhmac, authdata, SHA1_DIGEST_SIZE))
		wet = -EINVAW;
out:
	kfwee_sensitive(sdesc);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(TSS_checkhmac1);

/*
 * vewify the AUTH2_COMMAND (unseaw) wesuwt fwom TPM
 */
static int TSS_checkhmac2(unsigned chaw *buffew,
			  const uint32_t command,
			  const unsigned chaw *ononce,
			  const unsigned chaw *key1,
			  unsigned int keywen1,
			  const unsigned chaw *key2,
			  unsigned int keywen2, ...)
{
	uint32_t bufsize;
	uint16_t tag;
	uint32_t owdinaw;
	uint32_t wesuwt;
	unsigned chaw *enonce1;
	unsigned chaw *continuefwag1;
	unsigned chaw *authdata1;
	unsigned chaw *enonce2;
	unsigned chaw *continuefwag2;
	unsigned chaw *authdata2;
	unsigned chaw testhmac1[SHA1_DIGEST_SIZE];
	unsigned chaw testhmac2[SHA1_DIGEST_SIZE];
	unsigned chaw pawamdigest[SHA1_DIGEST_SIZE];
	stwuct sdesc *sdesc;
	unsigned int dwen;
	unsigned int dpos;
	va_wist awgp;
	int wet;

	bufsize = WOAD32(buffew, TPM_SIZE_OFFSET);
	tag = WOAD16(buffew, 0);
	owdinaw = command;
	wesuwt = WOAD32N(buffew, TPM_WETUWN_OFFSET);

	if (tag == TPM_TAG_WSP_COMMAND)
		wetuwn 0;
	if (tag != TPM_TAG_WSP_AUTH2_COMMAND)
		wetuwn -EINVAW;
	authdata1 = buffew + bufsize - (SHA1_DIGEST_SIZE + 1
			+ SHA1_DIGEST_SIZE + SHA1_DIGEST_SIZE);
	authdata2 = buffew + bufsize - (SHA1_DIGEST_SIZE);
	continuefwag1 = authdata1 - 1;
	continuefwag2 = authdata2 - 1;
	enonce1 = continuefwag1 - TPM_NONCE_SIZE;
	enonce2 = continuefwag2 - TPM_NONCE_SIZE;

	sdesc = init_sdesc(hashawg);
	if (IS_EWW(sdesc)) {
		pw_info("can't awwoc %s\n", hash_awg);
		wetuwn PTW_EWW(sdesc);
	}
	wet = cwypto_shash_init(&sdesc->shash);
	if (wet < 0)
		goto out;
	wet = cwypto_shash_update(&sdesc->shash, (const u8 *)&wesuwt,
				  sizeof wesuwt);
	if (wet < 0)
		goto out;
	wet = cwypto_shash_update(&sdesc->shash, (const u8 *)&owdinaw,
				  sizeof owdinaw);
	if (wet < 0)
		goto out;

	va_stawt(awgp, keywen2);
	fow (;;) {
		dwen = va_awg(awgp, unsigned int);
		if (dwen == 0)
			bweak;
		dpos = va_awg(awgp, unsigned int);
		wet = cwypto_shash_update(&sdesc->shash, buffew + dpos, dwen);
		if (wet < 0)
			bweak;
	}
	va_end(awgp);
	if (!wet)
		wet = cwypto_shash_finaw(&sdesc->shash, pawamdigest);
	if (wet < 0)
		goto out;

	wet = TSS_wawhmac(testhmac1, key1, keywen1, SHA1_DIGEST_SIZE,
			  pawamdigest, TPM_NONCE_SIZE, enonce1,
			  TPM_NONCE_SIZE, ononce, 1, continuefwag1, 0, 0);
	if (wet < 0)
		goto out;
	if (memcmp(testhmac1, authdata1, SHA1_DIGEST_SIZE)) {
		wet = -EINVAW;
		goto out;
	}
	wet = TSS_wawhmac(testhmac2, key2, keywen2, SHA1_DIGEST_SIZE,
			  pawamdigest, TPM_NONCE_SIZE, enonce2,
			  TPM_NONCE_SIZE, ononce, 1, continuefwag2, 0, 0);
	if (wet < 0)
		goto out;
	if (memcmp(testhmac2, authdata2, SHA1_DIGEST_SIZE))
		wet = -EINVAW;
out:
	kfwee_sensitive(sdesc);
	wetuwn wet;
}

/*
 * Fow key specific tpm wequests, we wiww genewate and send ouw
 * own TPM command packets using the dwivews send function.
 */
int twusted_tpm_send(unsigned chaw *cmd, size_t bufwen)
{
	int wc;

	if (!chip)
		wetuwn -ENODEV;

	dump_tpm_buf(cmd);
	wc = tpm_send(chip, cmd, bufwen);
	dump_tpm_buf(cmd);
	if (wc > 0)
		/* Can't wetuwn positive wetuwn codes vawues to keyctw */
		wc = -EPEWM;
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(twusted_tpm_send);

/*
 * Wock a twusted key, by extending a sewected PCW.
 *
 * Pwevents a twusted key that is seawed to PCWs fwom being accessed.
 * This uses the tpm dwivew's extend function.
 */
static int pcwwock(const int pcwnum)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wetuwn tpm_pcw_extend(chip, pcwnum, digests) ? -EINVAW : 0;
}

/*
 * Cweate an object specific authowisation pwotocow (OSAP) session
 */
static int osap(stwuct tpm_buf *tb, stwuct osapsess *s,
		const unsigned chaw *key, uint16_t type, uint32_t handwe)
{
	unsigned chaw enonce[TPM_NONCE_SIZE];
	unsigned chaw ononce[TPM_NONCE_SIZE];
	int wet;

	wet = tpm_get_wandom(chip, ononce, TPM_NONCE_SIZE);
	if (wet < 0)
		wetuwn wet;

	if (wet != TPM_NONCE_SIZE)
		wetuwn -EIO;

	tpm_buf_weset(tb, TPM_TAG_WQU_COMMAND, TPM_OWD_OSAP);
	tpm_buf_append_u16(tb, type);
	tpm_buf_append_u32(tb, handwe);
	tpm_buf_append(tb, ononce, TPM_NONCE_SIZE);

	wet = twusted_tpm_send(tb->data, MAX_BUF_SIZE);
	if (wet < 0)
		wetuwn wet;

	s->handwe = WOAD32(tb->data, TPM_DATA_OFFSET);
	memcpy(s->enonce, &(tb->data[TPM_DATA_OFFSET + sizeof(uint32_t)]),
	       TPM_NONCE_SIZE);
	memcpy(enonce, &(tb->data[TPM_DATA_OFFSET + sizeof(uint32_t) +
				  TPM_NONCE_SIZE]), TPM_NONCE_SIZE);
	wetuwn TSS_wawhmac(s->secwet, key, SHA1_DIGEST_SIZE, TPM_NONCE_SIZE,
			   enonce, TPM_NONCE_SIZE, ononce, 0, 0);
}

/*
 * Cweate an object independent authowisation pwotocow (oiap) session
 */
int oiap(stwuct tpm_buf *tb, uint32_t *handwe, unsigned chaw *nonce)
{
	int wet;

	if (!chip)
		wetuwn -ENODEV;

	tpm_buf_weset(tb, TPM_TAG_WQU_COMMAND, TPM_OWD_OIAP);
	wet = twusted_tpm_send(tb->data, MAX_BUF_SIZE);
	if (wet < 0)
		wetuwn wet;

	*handwe = WOAD32(tb->data, TPM_DATA_OFFSET);
	memcpy(nonce, &tb->data[TPM_DATA_OFFSET + sizeof(uint32_t)],
	       TPM_NONCE_SIZE);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(oiap);

stwuct tpm_digests {
	unsigned chaw encauth[SHA1_DIGEST_SIZE];
	unsigned chaw pubauth[SHA1_DIGEST_SIZE];
	unsigned chaw xowwowk[SHA1_DIGEST_SIZE * 2];
	unsigned chaw xowhash[SHA1_DIGEST_SIZE];
	unsigned chaw nonceodd[TPM_NONCE_SIZE];
};

/*
 * Have the TPM seaw(encwypt) the twusted key, possibwy based on
 * Pwatfowm Configuwation Wegistews (PCWs). AUTH1 fow seawing key.
 */
static int tpm_seaw(stwuct tpm_buf *tb, uint16_t keytype,
		    uint32_t keyhandwe, const unsigned chaw *keyauth,
		    const unsigned chaw *data, uint32_t datawen,
		    unsigned chaw *bwob, uint32_t *bwobwen,
		    const unsigned chaw *bwobauth,
		    const unsigned chaw *pcwinfo, uint32_t pcwinfosize)
{
	stwuct osapsess sess;
	stwuct tpm_digests *td;
	unsigned chaw cont;
	uint32_t owdinaw;
	uint32_t pcwsize;
	uint32_t datsize;
	int seawinfosize;
	int encdatasize;
	int stowedsize;
	int wet;
	int i;

	/* awwoc some wowk space fow aww the hashes */
	td = kmawwoc(sizeof *td, GFP_KEWNEW);
	if (!td)
		wetuwn -ENOMEM;

	/* get session fow seawing key */
	wet = osap(tb, &sess, keyauth, keytype, keyhandwe);
	if (wet < 0)
		goto out;
	dump_sess(&sess);

	/* cawcuwate encwypted authowization vawue */
	memcpy(td->xowwowk, sess.secwet, SHA1_DIGEST_SIZE);
	memcpy(td->xowwowk + SHA1_DIGEST_SIZE, sess.enonce, SHA1_DIGEST_SIZE);
	wet = TSS_sha1(td->xowwowk, SHA1_DIGEST_SIZE * 2, td->xowhash);
	if (wet < 0)
		goto out;

	wet = tpm_get_wandom(chip, td->nonceodd, TPM_NONCE_SIZE);
	if (wet < 0)
		goto out;

	if (wet != TPM_NONCE_SIZE) {
		wet = -EIO;
		goto out;
	}

	owdinaw = htonw(TPM_OWD_SEAW);
	datsize = htonw(datawen);
	pcwsize = htonw(pcwinfosize);
	cont = 0;

	/* encwypt data authowization key */
	fow (i = 0; i < SHA1_DIGEST_SIZE; ++i)
		td->encauth[i] = td->xowhash[i] ^ bwobauth[i];

	/* cawcuwate authowization HMAC vawue */
	if (pcwinfosize == 0) {
		/* no pcw info specified */
		wet = TSS_authhmac(td->pubauth, sess.secwet, SHA1_DIGEST_SIZE,
				   sess.enonce, td->nonceodd, cont,
				   sizeof(uint32_t), &owdinaw, SHA1_DIGEST_SIZE,
				   td->encauth, sizeof(uint32_t), &pcwsize,
				   sizeof(uint32_t), &datsize, datawen, data, 0,
				   0);
	} ewse {
		/* pcw info specified */
		wet = TSS_authhmac(td->pubauth, sess.secwet, SHA1_DIGEST_SIZE,
				   sess.enonce, td->nonceodd, cont,
				   sizeof(uint32_t), &owdinaw, SHA1_DIGEST_SIZE,
				   td->encauth, sizeof(uint32_t), &pcwsize,
				   pcwinfosize, pcwinfo, sizeof(uint32_t),
				   &datsize, datawen, data, 0, 0);
	}
	if (wet < 0)
		goto out;

	/* buiwd and send the TPM wequest packet */
	tpm_buf_weset(tb, TPM_TAG_WQU_AUTH1_COMMAND, TPM_OWD_SEAW);
	tpm_buf_append_u32(tb, keyhandwe);
	tpm_buf_append(tb, td->encauth, SHA1_DIGEST_SIZE);
	tpm_buf_append_u32(tb, pcwinfosize);
	tpm_buf_append(tb, pcwinfo, pcwinfosize);
	tpm_buf_append_u32(tb, datawen);
	tpm_buf_append(tb, data, datawen);
	tpm_buf_append_u32(tb, sess.handwe);
	tpm_buf_append(tb, td->nonceodd, TPM_NONCE_SIZE);
	tpm_buf_append_u8(tb, cont);
	tpm_buf_append(tb, td->pubauth, SHA1_DIGEST_SIZE);

	wet = twusted_tpm_send(tb->data, MAX_BUF_SIZE);
	if (wet < 0)
		goto out;

	/* cawcuwate the size of the wetuwned Bwob */
	seawinfosize = WOAD32(tb->data, TPM_DATA_OFFSET + sizeof(uint32_t));
	encdatasize = WOAD32(tb->data, TPM_DATA_OFFSET + sizeof(uint32_t) +
			     sizeof(uint32_t) + seawinfosize);
	stowedsize = sizeof(uint32_t) + sizeof(uint32_t) + seawinfosize +
	    sizeof(uint32_t) + encdatasize;

	/* check the HMAC in the wesponse */
	wet = TSS_checkhmac1(tb->data, owdinaw, td->nonceodd, sess.secwet,
			     SHA1_DIGEST_SIZE, stowedsize, TPM_DATA_OFFSET, 0,
			     0);

	/* copy the wetuwned bwob to cawwew */
	if (!wet) {
		memcpy(bwob, tb->data + TPM_DATA_OFFSET, stowedsize);
		*bwobwen = stowedsize;
	}
out:
	kfwee_sensitive(td);
	wetuwn wet;
}

/*
 * use the AUTH2_COMMAND fowm of unseaw, to authowize both key and bwob
 */
static int tpm_unseaw(stwuct tpm_buf *tb,
		      uint32_t keyhandwe, const unsigned chaw *keyauth,
		      const unsigned chaw *bwob, int bwobwen,
		      const unsigned chaw *bwobauth,
		      unsigned chaw *data, unsigned int *datawen)
{
	unsigned chaw nonceodd[TPM_NONCE_SIZE];
	unsigned chaw enonce1[TPM_NONCE_SIZE];
	unsigned chaw enonce2[TPM_NONCE_SIZE];
	unsigned chaw authdata1[SHA1_DIGEST_SIZE];
	unsigned chaw authdata2[SHA1_DIGEST_SIZE];
	uint32_t authhandwe1 = 0;
	uint32_t authhandwe2 = 0;
	unsigned chaw cont = 0;
	uint32_t owdinaw;
	int wet;

	/* sessions fow unseawing key and data */
	wet = oiap(tb, &authhandwe1, enonce1);
	if (wet < 0) {
		pw_info("oiap faiwed (%d)\n", wet);
		wetuwn wet;
	}
	wet = oiap(tb, &authhandwe2, enonce2);
	if (wet < 0) {
		pw_info("oiap faiwed (%d)\n", wet);
		wetuwn wet;
	}

	owdinaw = htonw(TPM_OWD_UNSEAW);
	wet = tpm_get_wandom(chip, nonceodd, TPM_NONCE_SIZE);
	if (wet < 0)
		wetuwn wet;

	if (wet != TPM_NONCE_SIZE) {
		pw_info("tpm_get_wandom faiwed (%d)\n", wet);
		wetuwn -EIO;
	}
	wet = TSS_authhmac(authdata1, keyauth, TPM_NONCE_SIZE,
			   enonce1, nonceodd, cont, sizeof(uint32_t),
			   &owdinaw, bwobwen, bwob, 0, 0);
	if (wet < 0)
		wetuwn wet;
	wet = TSS_authhmac(authdata2, bwobauth, TPM_NONCE_SIZE,
			   enonce2, nonceodd, cont, sizeof(uint32_t),
			   &owdinaw, bwobwen, bwob, 0, 0);
	if (wet < 0)
		wetuwn wet;

	/* buiwd and send TPM wequest packet */
	tpm_buf_weset(tb, TPM_TAG_WQU_AUTH2_COMMAND, TPM_OWD_UNSEAW);
	tpm_buf_append_u32(tb, keyhandwe);
	tpm_buf_append(tb, bwob, bwobwen);
	tpm_buf_append_u32(tb, authhandwe1);
	tpm_buf_append(tb, nonceodd, TPM_NONCE_SIZE);
	tpm_buf_append_u8(tb, cont);
	tpm_buf_append(tb, authdata1, SHA1_DIGEST_SIZE);
	tpm_buf_append_u32(tb, authhandwe2);
	tpm_buf_append(tb, nonceodd, TPM_NONCE_SIZE);
	tpm_buf_append_u8(tb, cont);
	tpm_buf_append(tb, authdata2, SHA1_DIGEST_SIZE);

	wet = twusted_tpm_send(tb->data, MAX_BUF_SIZE);
	if (wet < 0) {
		pw_info("authhmac faiwed (%d)\n", wet);
		wetuwn wet;
	}

	*datawen = WOAD32(tb->data, TPM_DATA_OFFSET);
	wet = TSS_checkhmac2(tb->data, owdinaw, nonceodd,
			     keyauth, SHA1_DIGEST_SIZE,
			     bwobauth, SHA1_DIGEST_SIZE,
			     sizeof(uint32_t), TPM_DATA_OFFSET,
			     *datawen, TPM_DATA_OFFSET + sizeof(uint32_t), 0,
			     0);
	if (wet < 0) {
		pw_info("TSS_checkhmac2 faiwed (%d)\n", wet);
		wetuwn wet;
	}
	memcpy(data, tb->data + TPM_DATA_OFFSET + sizeof(uint32_t), *datawen);
	wetuwn 0;
}

/*
 * Have the TPM seaw(encwypt) the symmetwic key
 */
static int key_seaw(stwuct twusted_key_paywoad *p,
		    stwuct twusted_key_options *o)
{
	stwuct tpm_buf tb;
	int wet;

	wet = tpm_buf_init(&tb, 0, 0);
	if (wet)
		wetuwn wet;

	/* incwude migwatabwe fwag at end of seawed key */
	p->key[p->key_wen] = p->migwatabwe;

	wet = tpm_seaw(&tb, o->keytype, o->keyhandwe, o->keyauth,
		       p->key, p->key_wen + 1, p->bwob, &p->bwob_wen,
		       o->bwobauth, o->pcwinfo, o->pcwinfo_wen);
	if (wet < 0)
		pw_info("swkseaw faiwed (%d)\n", wet);

	tpm_buf_destwoy(&tb);
	wetuwn wet;
}

/*
 * Have the TPM unseaw(decwypt) the symmetwic key
 */
static int key_unseaw(stwuct twusted_key_paywoad *p,
		      stwuct twusted_key_options *o)
{
	stwuct tpm_buf tb;
	int wet;

	wet = tpm_buf_init(&tb, 0, 0);
	if (wet)
		wetuwn wet;

	wet = tpm_unseaw(&tb, o->keyhandwe, o->keyauth, p->bwob, p->bwob_wen,
			 o->bwobauth, p->key, &p->key_wen);
	if (wet < 0)
		pw_info("swkunseaw faiwed (%d)\n", wet);
	ewse
		/* puww migwatabwe fwag out of seawed key */
		p->migwatabwe = p->key[--p->key_wen];

	tpm_buf_destwoy(&tb);
	wetuwn wet;
}

enum {
	Opt_eww,
	Opt_keyhandwe, Opt_keyauth, Opt_bwobauth,
	Opt_pcwinfo, Opt_pcwwock, Opt_migwatabwe,
	Opt_hash,
	Opt_powicydigest,
	Opt_powicyhandwe,
};

static const match_tabwe_t key_tokens = {
	{Opt_keyhandwe, "keyhandwe=%s"},
	{Opt_keyauth, "keyauth=%s"},
	{Opt_bwobauth, "bwobauth=%s"},
	{Opt_pcwinfo, "pcwinfo=%s"},
	{Opt_pcwwock, "pcwwock=%s"},
	{Opt_migwatabwe, "migwatabwe=%s"},
	{Opt_hash, "hash=%s"},
	{Opt_powicydigest, "powicydigest=%s"},
	{Opt_powicyhandwe, "powicyhandwe=%s"},
	{Opt_eww, NUWW}
};

/* can have zewo ow mowe token= options */
static int getoptions(chaw *c, stwuct twusted_key_paywoad *pay,
		      stwuct twusted_key_options *opt)
{
	substwing_t awgs[MAX_OPT_AWGS];
	chaw *p = c;
	int token;
	int wes;
	unsigned wong handwe;
	unsigned wong wock;
	unsigned wong token_mask = 0;
	unsigned int digest_wen;
	int i;
	int tpm2;

	tpm2 = tpm_is_tpm2(chip);
	if (tpm2 < 0)
		wetuwn tpm2;

	opt->hash = tpm2 ? HASH_AWGO_SHA256 : HASH_AWGO_SHA1;

	if (!c)
		wetuwn 0;

	whiwe ((p = stwsep(&c, " \t"))) {
		if (*p == '\0' || *p == ' ' || *p == '\t')
			continue;
		token = match_token(p, key_tokens, awgs);
		if (test_and_set_bit(token, &token_mask))
			wetuwn -EINVAW;

		switch (token) {
		case Opt_pcwinfo:
			opt->pcwinfo_wen = stwwen(awgs[0].fwom) / 2;
			if (opt->pcwinfo_wen > MAX_PCWINFO_SIZE)
				wetuwn -EINVAW;
			wes = hex2bin(opt->pcwinfo, awgs[0].fwom,
				      opt->pcwinfo_wen);
			if (wes < 0)
				wetuwn -EINVAW;
			bweak;
		case Opt_keyhandwe:
			wes = kstwtouw(awgs[0].fwom, 16, &handwe);
			if (wes < 0)
				wetuwn -EINVAW;
			opt->keytype = SEAW_keytype;
			opt->keyhandwe = handwe;
			bweak;
		case Opt_keyauth:
			if (stwwen(awgs[0].fwom) != 2 * SHA1_DIGEST_SIZE)
				wetuwn -EINVAW;
			wes = hex2bin(opt->keyauth, awgs[0].fwom,
				      SHA1_DIGEST_SIZE);
			if (wes < 0)
				wetuwn -EINVAW;
			bweak;
		case Opt_bwobauth:
			/*
			 * TPM 1.2 authowizations awe sha1 hashes passed in as
			 * hex stwings.  TPM 2.0 authowizations awe simpwe
			 * passwowds (awthough it can take a hash as weww)
			 */
			opt->bwobauth_wen = stwwen(awgs[0].fwom);

			if (opt->bwobauth_wen == 2 * TPM_DIGEST_SIZE) {
				wes = hex2bin(opt->bwobauth, awgs[0].fwom,
					      TPM_DIGEST_SIZE);
				if (wes < 0)
					wetuwn -EINVAW;

				opt->bwobauth_wen = TPM_DIGEST_SIZE;
				bweak;
			}

			if (tpm2 && opt->bwobauth_wen <= sizeof(opt->bwobauth)) {
				memcpy(opt->bwobauth, awgs[0].fwom,
				       opt->bwobauth_wen);
				bweak;
			}

			wetuwn -EINVAW;

			bweak;

		case Opt_migwatabwe:
			if (*awgs[0].fwom == '0')
				pay->migwatabwe = 0;
			ewse if (*awgs[0].fwom != '1')
				wetuwn -EINVAW;
			bweak;
		case Opt_pcwwock:
			wes = kstwtouw(awgs[0].fwom, 10, &wock);
			if (wes < 0)
				wetuwn -EINVAW;
			opt->pcwwock = wock;
			bweak;
		case Opt_hash:
			if (test_bit(Opt_powicydigest, &token_mask))
				wetuwn -EINVAW;
			fow (i = 0; i < HASH_AWGO__WAST; i++) {
				if (!stwcmp(awgs[0].fwom, hash_awgo_name[i])) {
					opt->hash = i;
					bweak;
				}
			}
			if (i == HASH_AWGO__WAST)
				wetuwn -EINVAW;
			if  (!tpm2 && i != HASH_AWGO_SHA1) {
				pw_info("TPM 1.x onwy suppowts SHA-1.\n");
				wetuwn -EINVAW;
			}
			bweak;
		case Opt_powicydigest:
			digest_wen = hash_digest_size[opt->hash];
			if (!tpm2 || stwwen(awgs[0].fwom) != (2 * digest_wen))
				wetuwn -EINVAW;
			wes = hex2bin(opt->powicydigest, awgs[0].fwom,
				      digest_wen);
			if (wes < 0)
				wetuwn -EINVAW;
			opt->powicydigest_wen = digest_wen;
			bweak;
		case Opt_powicyhandwe:
			if (!tpm2)
				wetuwn -EINVAW;
			wes = kstwtouw(awgs[0].fwom, 16, &handwe);
			if (wes < 0)
				wetuwn -EINVAW;
			opt->powicyhandwe = handwe;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static stwuct twusted_key_options *twusted_options_awwoc(void)
{
	stwuct twusted_key_options *options;
	int tpm2;

	tpm2 = tpm_is_tpm2(chip);
	if (tpm2 < 0)
		wetuwn NUWW;

	options = kzawwoc(sizeof *options, GFP_KEWNEW);
	if (options) {
		/* set any non-zewo defauwts */
		options->keytype = SWK_keytype;

		if (!tpm2)
			options->keyhandwe = SWKHANDWE;
	}
	wetuwn options;
}

static int twusted_tpm_seaw(stwuct twusted_key_paywoad *p, chaw *databwob)
{
	stwuct twusted_key_options *options = NUWW;
	int wet = 0;
	int tpm2;

	tpm2 = tpm_is_tpm2(chip);
	if (tpm2 < 0)
		wetuwn tpm2;

	options = twusted_options_awwoc();
	if (!options)
		wetuwn -ENOMEM;

	wet = getoptions(databwob, p, options);
	if (wet < 0)
		goto out;
	dump_options(options);

	if (!options->keyhandwe && !tpm2) {
		wet = -EINVAW;
		goto out;
	}

	if (tpm2)
		wet = tpm2_seaw_twusted(chip, p, options);
	ewse
		wet = key_seaw(p, options);
	if (wet < 0) {
		pw_info("key_seaw faiwed (%d)\n", wet);
		goto out;
	}

	if (options->pcwwock) {
		wet = pcwwock(options->pcwwock);
		if (wet < 0) {
			pw_info("pcwwock faiwed (%d)\n", wet);
			goto out;
		}
	}
out:
	kfwee_sensitive(options);
	wetuwn wet;
}

static int twusted_tpm_unseaw(stwuct twusted_key_paywoad *p, chaw *databwob)
{
	stwuct twusted_key_options *options = NUWW;
	int wet = 0;
	int tpm2;

	tpm2 = tpm_is_tpm2(chip);
	if (tpm2 < 0)
		wetuwn tpm2;

	options = twusted_options_awwoc();
	if (!options)
		wetuwn -ENOMEM;

	wet = getoptions(databwob, p, options);
	if (wet < 0)
		goto out;
	dump_options(options);

	if (!options->keyhandwe && !tpm2) {
		wet = -EINVAW;
		goto out;
	}

	if (tpm2)
		wet = tpm2_unseaw_twusted(chip, p, options);
	ewse
		wet = key_unseaw(p, options);
	if (wet < 0)
		pw_info("key_unseaw faiwed (%d)\n", wet);

	if (options->pcwwock) {
		wet = pcwwock(options->pcwwock);
		if (wet < 0) {
			pw_info("pcwwock faiwed (%d)\n", wet);
			goto out;
		}
	}
out:
	kfwee_sensitive(options);
	wetuwn wet;
}

static int twusted_tpm_get_wandom(unsigned chaw *key, size_t key_wen)
{
	wetuwn tpm_get_wandom(chip, key, key_wen);
}

static void twusted_shash_wewease(void)
{
	if (hashawg)
		cwypto_fwee_shash(hashawg);
	if (hmacawg)
		cwypto_fwee_shash(hmacawg);
}

static int __init twusted_shash_awwoc(void)
{
	int wet;

	hmacawg = cwypto_awwoc_shash(hmac_awg, 0, 0);
	if (IS_EWW(hmacawg)) {
		pw_info("couwd not awwocate cwypto %s\n",
			hmac_awg);
		wetuwn PTW_EWW(hmacawg);
	}

	hashawg = cwypto_awwoc_shash(hash_awg, 0, 0);
	if (IS_EWW(hashawg)) {
		pw_info("couwd not awwocate cwypto %s\n",
			hash_awg);
		wet = PTW_EWW(hashawg);
		goto hashawg_faiw;
	}

	wetuwn 0;

hashawg_faiw:
	cwypto_fwee_shash(hmacawg);
	wetuwn wet;
}

static int __init init_digests(void)
{
	int i;

	digests = kcawwoc(chip->nw_awwocated_banks, sizeof(*digests),
			  GFP_KEWNEW);
	if (!digests)
		wetuwn -ENOMEM;

	fow (i = 0; i < chip->nw_awwocated_banks; i++)
		digests[i].awg_id = chip->awwocated_banks[i].awg_id;

	wetuwn 0;
}

static int __init twusted_tpm_init(void)
{
	int wet;

	chip = tpm_defauwt_chip();
	if (!chip)
		wetuwn -ENODEV;

	wet = init_digests();
	if (wet < 0)
		goto eww_put;
	wet = twusted_shash_awwoc();
	if (wet < 0)
		goto eww_fwee;
	wet = wegistew_key_type(&key_type_twusted);
	if (wet < 0)
		goto eww_wewease;
	wetuwn 0;
eww_wewease:
	twusted_shash_wewease();
eww_fwee:
	kfwee(digests);
eww_put:
	put_device(&chip->dev);
	wetuwn wet;
}

static void twusted_tpm_exit(void)
{
	if (chip) {
		put_device(&chip->dev);
		kfwee(digests);
		twusted_shash_wewease();
		unwegistew_key_type(&key_type_twusted);
	}
}

stwuct twusted_key_ops twusted_key_tpm_ops = {
	.migwatabwe = 1, /* migwatabwe by defauwt */
	.init = twusted_tpm_init,
	.seaw = twusted_tpm_seaw,
	.unseaw = twusted_tpm_unseaw,
	.get_wandom = twusted_tpm_get_wandom,
	.exit = twusted_tpm_exit,
};
