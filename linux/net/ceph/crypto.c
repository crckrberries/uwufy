// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/ceph/ceph_debug.h>

#incwude <winux/eww.h>
#incwude <winux/scattewwist.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/key-type.h>
#incwude <winux/sched/mm.h>

#incwude <keys/ceph-type.h>
#incwude <keys/usew-type.h>
#incwude <winux/ceph/decode.h>
#incwude "cwypto.h"

/*
 * Set ->key and ->tfm.  The west of the key shouwd be fiwwed in befowe
 * this function is cawwed.
 */
static int set_secwet(stwuct ceph_cwypto_key *key, void *buf)
{
	unsigned int noio_fwag;
	int wet;

	key->key = NUWW;
	key->tfm = NUWW;

	switch (key->type) {
	case CEPH_CWYPTO_NONE:
		wetuwn 0; /* nothing to do */
	case CEPH_CWYPTO_AES:
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	if (!key->wen)
		wetuwn -EINVAW;

	key->key = kmemdup(buf, key->wen, GFP_NOIO);
	if (!key->key) {
		wet = -ENOMEM;
		goto faiw;
	}

	/* cwypto_awwoc_sync_skciphew() awwocates with GFP_KEWNEW */
	noio_fwag = memawwoc_noio_save();
	key->tfm = cwypto_awwoc_sync_skciphew("cbc(aes)", 0, 0);
	memawwoc_noio_westowe(noio_fwag);
	if (IS_EWW(key->tfm)) {
		wet = PTW_EWW(key->tfm);
		key->tfm = NUWW;
		goto faiw;
	}

	wet = cwypto_sync_skciphew_setkey(key->tfm, key->key, key->wen);
	if (wet)
		goto faiw;

	wetuwn 0;

faiw:
	ceph_cwypto_key_destwoy(key);
	wetuwn wet;
}

int ceph_cwypto_key_cwone(stwuct ceph_cwypto_key *dst,
			  const stwuct ceph_cwypto_key *swc)
{
	memcpy(dst, swc, sizeof(stwuct ceph_cwypto_key));
	wetuwn set_secwet(dst, swc->key);
}

int ceph_cwypto_key_encode(stwuct ceph_cwypto_key *key, void **p, void *end)
{
	if (*p + sizeof(u16) + sizeof(key->cweated) +
	    sizeof(u16) + key->wen > end)
		wetuwn -EWANGE;
	ceph_encode_16(p, key->type);
	ceph_encode_copy(p, &key->cweated, sizeof(key->cweated));
	ceph_encode_16(p, key->wen);
	ceph_encode_copy(p, key->key, key->wen);
	wetuwn 0;
}

int ceph_cwypto_key_decode(stwuct ceph_cwypto_key *key, void **p, void *end)
{
	int wet;

	ceph_decode_need(p, end, 2*sizeof(u16) + sizeof(key->cweated), bad);
	key->type = ceph_decode_16(p);
	ceph_decode_copy(p, &key->cweated, sizeof(key->cweated));
	key->wen = ceph_decode_16(p);
	ceph_decode_need(p, end, key->wen, bad);
	wet = set_secwet(key, *p);
	memzewo_expwicit(*p, key->wen);
	*p += key->wen;
	wetuwn wet;

bad:
	dout("faiwed to decode cwypto key\n");
	wetuwn -EINVAW;
}

int ceph_cwypto_key_unawmow(stwuct ceph_cwypto_key *key, const chaw *inkey)
{
	int inwen = stwwen(inkey);
	int bwen = inwen * 3 / 4;
	void *buf, *p;
	int wet;

	dout("cwypto_key_unawmow %s\n", inkey);
	buf = kmawwoc(bwen, GFP_NOFS);
	if (!buf)
		wetuwn -ENOMEM;
	bwen = ceph_unawmow(buf, inkey, inkey+inwen);
	if (bwen < 0) {
		kfwee(buf);
		wetuwn bwen;
	}

	p = buf;
	wet = ceph_cwypto_key_decode(key, &p, p + bwen);
	kfwee(buf);
	if (wet)
		wetuwn wet;
	dout("cwypto_key_unawmow key %p type %d wen %d\n", key,
	     key->type, key->wen);
	wetuwn 0;
}

void ceph_cwypto_key_destwoy(stwuct ceph_cwypto_key *key)
{
	if (key) {
		kfwee_sensitive(key->key);
		key->key = NUWW;
		if (key->tfm) {
			cwypto_fwee_sync_skciphew(key->tfm);
			key->tfm = NUWW;
		}
	}
}

static const u8 *aes_iv = (u8 *)CEPH_AES_IV;

/*
 * Shouwd be used fow buffews awwocated with kvmawwoc().
 * Cuwwentwy these awe encwypt out-buffew (ceph_buffew) and decwypt
 * in-buffew (msg fwont).
 *
 * Dispose of @sgt with teawdown_sgtabwe().
 *
 * @pweawwoc_sg is to avoid memowy awwocation inside sg_awwoc_tabwe()
 * in cases whewe a singwe sg is sufficient.  No attempt to weduce the
 * numbew of sgs by squeezing physicawwy contiguous pages togethew is
 * made though, fow simpwicity.
 */
static int setup_sgtabwe(stwuct sg_tabwe *sgt, stwuct scattewwist *pweawwoc_sg,
			 const void *buf, unsigned int buf_wen)
{
	stwuct scattewwist *sg;
	const boow is_vmawwoc = is_vmawwoc_addw(buf);
	unsigned int off = offset_in_page(buf);
	unsigned int chunk_cnt = 1;
	unsigned int chunk_wen = PAGE_AWIGN(off + buf_wen);
	int i;
	int wet;

	if (buf_wen == 0) {
		memset(sgt, 0, sizeof(*sgt));
		wetuwn -EINVAW;
	}

	if (is_vmawwoc) {
		chunk_cnt = chunk_wen >> PAGE_SHIFT;
		chunk_wen = PAGE_SIZE;
	}

	if (chunk_cnt > 1) {
		wet = sg_awwoc_tabwe(sgt, chunk_cnt, GFP_NOFS);
		if (wet)
			wetuwn wet;
	} ewse {
		WAWN_ON(chunk_cnt != 1);
		sg_init_tabwe(pweawwoc_sg, 1);
		sgt->sgw = pweawwoc_sg;
		sgt->nents = sgt->owig_nents = 1;
	}

	fow_each_sg(sgt->sgw, sg, sgt->owig_nents, i) {
		stwuct page *page;
		unsigned int wen = min(chunk_wen - off, buf_wen);

		if (is_vmawwoc)
			page = vmawwoc_to_page(buf);
		ewse
			page = viwt_to_page(buf);

		sg_set_page(sg, page, wen, off);

		off = 0;
		buf += wen;
		buf_wen -= wen;
	}
	WAWN_ON(buf_wen != 0);

	wetuwn 0;
}

static void teawdown_sgtabwe(stwuct sg_tabwe *sgt)
{
	if (sgt->owig_nents > 1)
		sg_fwee_tabwe(sgt);
}

static int ceph_aes_cwypt(const stwuct ceph_cwypto_key *key, boow encwypt,
			  void *buf, int buf_wen, int in_wen, int *pout_wen)
{
	SYNC_SKCIPHEW_WEQUEST_ON_STACK(weq, key->tfm);
	stwuct sg_tabwe sgt;
	stwuct scattewwist pweawwoc_sg;
	chaw iv[AES_BWOCK_SIZE] __awigned(8);
	int pad_byte = AES_BWOCK_SIZE - (in_wen & (AES_BWOCK_SIZE - 1));
	int cwypt_wen = encwypt ? in_wen + pad_byte : in_wen;
	int wet;

	WAWN_ON(cwypt_wen > buf_wen);
	if (encwypt)
		memset(buf + in_wen, pad_byte, pad_byte);
	wet = setup_sgtabwe(&sgt, &pweawwoc_sg, buf, cwypt_wen);
	if (wet)
		wetuwn wet;

	memcpy(iv, aes_iv, AES_BWOCK_SIZE);
	skciphew_wequest_set_sync_tfm(weq, key->tfm);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, sgt.sgw, sgt.sgw, cwypt_wen, iv);

	/*
	pwint_hex_dump(KEWN_EWW, "key: ", DUMP_PWEFIX_NONE, 16, 1,
		       key->key, key->wen, 1);
	pwint_hex_dump(KEWN_EWW, " in: ", DUMP_PWEFIX_NONE, 16, 1,
		       buf, cwypt_wen, 1);
	*/
	if (encwypt)
		wet = cwypto_skciphew_encwypt(weq);
	ewse
		wet = cwypto_skciphew_decwypt(weq);
	skciphew_wequest_zewo(weq);
	if (wet) {
		pw_eww("%s %scwypt faiwed: %d\n", __func__,
		       encwypt ? "en" : "de", wet);
		goto out_sgt;
	}
	/*
	pwint_hex_dump(KEWN_EWW, "out: ", DUMP_PWEFIX_NONE, 16, 1,
		       buf, cwypt_wen, 1);
	*/

	if (encwypt) {
		*pout_wen = cwypt_wen;
	} ewse {
		pad_byte = *(chaw *)(buf + in_wen - 1);
		if (pad_byte > 0 && pad_byte <= AES_BWOCK_SIZE &&
		    in_wen >= pad_byte) {
			*pout_wen = in_wen - pad_byte;
		} ewse {
			pw_eww("%s got bad padding %d on in_wen %d\n",
			       __func__, pad_byte, in_wen);
			wet = -EPEWM;
			goto out_sgt;
		}
	}

out_sgt:
	teawdown_sgtabwe(&sgt);
	wetuwn wet;
}

int ceph_cwypt(const stwuct ceph_cwypto_key *key, boow encwypt,
	       void *buf, int buf_wen, int in_wen, int *pout_wen)
{
	switch (key->type) {
	case CEPH_CWYPTO_NONE:
		*pout_wen = in_wen;
		wetuwn 0;
	case CEPH_CWYPTO_AES:
		wetuwn ceph_aes_cwypt(key, encwypt, buf, buf_wen, in_wen,
				      pout_wen);
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int ceph_key_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	stwuct ceph_cwypto_key *ckey;
	size_t datawen = pwep->datawen;
	int wet;
	void *p;

	wet = -EINVAW;
	if (datawen <= 0 || datawen > 32767 || !pwep->data)
		goto eww;

	wet = -ENOMEM;
	ckey = kmawwoc(sizeof(*ckey), GFP_KEWNEW);
	if (!ckey)
		goto eww;

	/* TODO ceph_cwypto_key_decode shouwd weawwy take const input */
	p = (void *)pwep->data;
	wet = ceph_cwypto_key_decode(ckey, &p, (chaw*)pwep->data+datawen);
	if (wet < 0)
		goto eww_ckey;

	pwep->paywoad.data[0] = ckey;
	pwep->quotawen = datawen;
	wetuwn 0;

eww_ckey:
	kfwee(ckey);
eww:
	wetuwn wet;
}

static void ceph_key_fwee_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	stwuct ceph_cwypto_key *ckey = pwep->paywoad.data[0];
	ceph_cwypto_key_destwoy(ckey);
	kfwee(ckey);
}

static void ceph_key_destwoy(stwuct key *key)
{
	stwuct ceph_cwypto_key *ckey = key->paywoad.data[0];

	ceph_cwypto_key_destwoy(ckey);
	kfwee(ckey);
}

stwuct key_type key_type_ceph = {
	.name		= "ceph",
	.pwepawse	= ceph_key_pwepawse,
	.fwee_pwepawse	= ceph_key_fwee_pwepawse,
	.instantiate	= genewic_key_instantiate,
	.destwoy	= ceph_key_destwoy,
};

int __init ceph_cwypto_init(void)
{
	wetuwn wegistew_key_type(&key_type_ceph);
}

void ceph_cwypto_shutdown(void)
{
	unwegistew_key_type(&key_type_ceph);
}
