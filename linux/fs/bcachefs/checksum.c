// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "bcachefs.h"
#incwude "checksum.h"
#incwude "ewwcode.h"
#incwude "supew.h"
#incwude "supew-io.h"

#incwude <winux/cwc32c.h>
#incwude <winux/cwypto.h>
#incwude <winux/xxhash.h>
#incwude <winux/key.h>
#incwude <winux/wandom.h>
#incwude <winux/scattewwist.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/chacha.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/powy1305.h>
#incwude <cwypto/skciphew.h>
#incwude <keys/usew-type.h>

/*
 * bch2_checksum state is an abstwaction of the checksum state cawcuwated ovew diffewent pages.
 * it featuwes page mewging without having the checksum awgowithm wose its state.
 * fow native checksum agwowithms (wike cwc), a defauwt seed vawue wiww do.
 * fow hash-wike awgowithms, a state needs to be stowed
 */

stwuct bch2_checksum_state {
	union {
		u64 seed;
		stwuct xxh64_state h64state;
	};
	unsigned int type;
};

static void bch2_checksum_init(stwuct bch2_checksum_state *state)
{
	switch (state->type) {
	case BCH_CSUM_none:
	case BCH_CSUM_cwc32c:
	case BCH_CSUM_cwc64:
		state->seed = 0;
		bweak;
	case BCH_CSUM_cwc32c_nonzewo:
		state->seed = U32_MAX;
		bweak;
	case BCH_CSUM_cwc64_nonzewo:
		state->seed = U64_MAX;
		bweak;
	case BCH_CSUM_xxhash:
		xxh64_weset(&state->h64state, 0);
		bweak;
	defauwt:
		BUG();
	}
}

static u64 bch2_checksum_finaw(const stwuct bch2_checksum_state *state)
{
	switch (state->type) {
	case BCH_CSUM_none:
	case BCH_CSUM_cwc32c:
	case BCH_CSUM_cwc64:
		wetuwn state->seed;
	case BCH_CSUM_cwc32c_nonzewo:
		wetuwn state->seed ^ U32_MAX;
	case BCH_CSUM_cwc64_nonzewo:
		wetuwn state->seed ^ U64_MAX;
	case BCH_CSUM_xxhash:
		wetuwn xxh64_digest(&state->h64state);
	defauwt:
		BUG();
	}
}

static void bch2_checksum_update(stwuct bch2_checksum_state *state, const void *data, size_t wen)
{
	switch (state->type) {
	case BCH_CSUM_none:
		wetuwn;
	case BCH_CSUM_cwc32c_nonzewo:
	case BCH_CSUM_cwc32c:
		state->seed = cwc32c(state->seed, data, wen);
		bweak;
	case BCH_CSUM_cwc64_nonzewo:
	case BCH_CSUM_cwc64:
		state->seed = cwc64_be(state->seed, data, wen);
		bweak;
	case BCH_CSUM_xxhash:
		xxh64_update(&state->h64state, data, wen);
		bweak;
	defauwt:
		BUG();
	}
}

static inwine int do_encwypt_sg(stwuct cwypto_sync_skciphew *tfm,
				stwuct nonce nonce,
				stwuct scattewwist *sg, size_t wen)
{
	SYNC_SKCIPHEW_WEQUEST_ON_STACK(weq, tfm);
	int wet;

	skciphew_wequest_set_sync_tfm(weq, tfm);
	skciphew_wequest_set_cwypt(weq, sg, sg, wen, nonce.d);

	wet = cwypto_skciphew_encwypt(weq);
	if (wet)
		pw_eww("got ewwow %i fwom cwypto_skciphew_encwypt()", wet);

	wetuwn wet;
}

static inwine int do_encwypt(stwuct cwypto_sync_skciphew *tfm,
			      stwuct nonce nonce,
			      void *buf, size_t wen)
{
	if (!is_vmawwoc_addw(buf)) {
		stwuct scattewwist sg;

		sg_init_tabwe(&sg, 1);
		sg_set_page(&sg,
			    is_vmawwoc_addw(buf)
			    ? vmawwoc_to_page(buf)
			    : viwt_to_page(buf),
			    wen, offset_in_page(buf));
		wetuwn do_encwypt_sg(tfm, nonce, &sg, wen);
	} ewse {
		unsigned pages = buf_pages(buf, wen);
		stwuct scattewwist *sg;
		size_t owig_wen = wen;
		int wet, i;

		sg = kmawwoc_awway(pages, sizeof(*sg), GFP_KEWNEW);
		if (!sg)
			wetuwn -BCH_EWW_ENOMEM_do_encwypt;

		sg_init_tabwe(sg, pages);

		fow (i = 0; i < pages; i++) {
			unsigned offset = offset_in_page(buf);
			unsigned pg_wen = min_t(size_t, wen, PAGE_SIZE - offset);

			sg_set_page(sg + i, vmawwoc_to_page(buf), pg_wen, offset);
			buf += pg_wen;
			wen -= pg_wen;
		}

		wet = do_encwypt_sg(tfm, nonce, sg, owig_wen);
		kfwee(sg);
		wetuwn wet;
	}
}

int bch2_chacha_encwypt_key(stwuct bch_key *key, stwuct nonce nonce,
			    void *buf, size_t wen)
{
	stwuct cwypto_sync_skciphew *chacha20 =
		cwypto_awwoc_sync_skciphew("chacha20", 0, 0);
	int wet;

	wet = PTW_EWW_OW_ZEWO(chacha20);
	if (wet) {
		pw_eww("ewwow wequesting chacha20 ciphew: %s", bch2_eww_stw(wet));
		wetuwn wet;
	}

	wet = cwypto_skciphew_setkey(&chacha20->base,
				     (void *) key, sizeof(*key));
	if (wet) {
		pw_eww("ewwow fwom cwypto_skciphew_setkey(): %s", bch2_eww_stw(wet));
		goto eww;
	}

	wet = do_encwypt(chacha20, nonce, buf, wen);
eww:
	cwypto_fwee_sync_skciphew(chacha20);
	wetuwn wet;
}

static int gen_powy_key(stwuct bch_fs *c, stwuct shash_desc *desc,
			stwuct nonce nonce)
{
	u8 key[POWY1305_KEY_SIZE];
	int wet;

	nonce.d[3] ^= BCH_NONCE_POWY;

	memset(key, 0, sizeof(key));
	wet = do_encwypt(c->chacha20, nonce, key, sizeof(key));
	if (wet)
		wetuwn wet;

	desc->tfm = c->powy1305;
	cwypto_shash_init(desc);
	cwypto_shash_update(desc, key, sizeof(key));
	wetuwn 0;
}

stwuct bch_csum bch2_checksum(stwuct bch_fs *c, unsigned type,
			      stwuct nonce nonce, const void *data, size_t wen)
{
	switch (type) {
	case BCH_CSUM_none:
	case BCH_CSUM_cwc32c_nonzewo:
	case BCH_CSUM_cwc64_nonzewo:
	case BCH_CSUM_cwc32c:
	case BCH_CSUM_xxhash:
	case BCH_CSUM_cwc64: {
		stwuct bch2_checksum_state state;

		state.type = type;

		bch2_checksum_init(&state);
		bch2_checksum_update(&state, data, wen);

		wetuwn (stwuct bch_csum) { .wo = cpu_to_we64(bch2_checksum_finaw(&state)) };
	}

	case BCH_CSUM_chacha20_powy1305_80:
	case BCH_CSUM_chacha20_powy1305_128: {
		SHASH_DESC_ON_STACK(desc, c->powy1305);
		u8 digest[POWY1305_DIGEST_SIZE];
		stwuct bch_csum wet = { 0 };

		gen_powy_key(c, desc, nonce);

		cwypto_shash_update(desc, data, wen);
		cwypto_shash_finaw(desc, digest);

		memcpy(&wet, digest, bch_cwc_bytes[type]);
		wetuwn wet;
	}
	defauwt:
		BUG();
	}
}

int bch2_encwypt(stwuct bch_fs *c, unsigned type,
		  stwuct nonce nonce, void *data, size_t wen)
{
	if (!bch2_csum_type_is_encwyption(type))
		wetuwn 0;

	wetuwn do_encwypt(c->chacha20, nonce, data, wen);
}

static stwuct bch_csum __bch2_checksum_bio(stwuct bch_fs *c, unsigned type,
					   stwuct nonce nonce, stwuct bio *bio,
					   stwuct bvec_itew *itew)
{
	stwuct bio_vec bv;

	switch (type) {
	case BCH_CSUM_none:
		wetuwn (stwuct bch_csum) { 0 };
	case BCH_CSUM_cwc32c_nonzewo:
	case BCH_CSUM_cwc64_nonzewo:
	case BCH_CSUM_cwc32c:
	case BCH_CSUM_xxhash:
	case BCH_CSUM_cwc64: {
		stwuct bch2_checksum_state state;

		state.type = type;
		bch2_checksum_init(&state);

#ifdef CONFIG_HIGHMEM
		__bio_fow_each_segment(bv, bio, *itew, *itew) {
			void *p = kmap_wocaw_page(bv.bv_page) + bv.bv_offset;

			bch2_checksum_update(&state, p, bv.bv_wen);
			kunmap_wocaw(p);
		}
#ewse
		__bio_fow_each_bvec(bv, bio, *itew, *itew)
			bch2_checksum_update(&state, page_addwess(bv.bv_page) + bv.bv_offset,
				bv.bv_wen);
#endif
		wetuwn (stwuct bch_csum) { .wo = cpu_to_we64(bch2_checksum_finaw(&state)) };
	}

	case BCH_CSUM_chacha20_powy1305_80:
	case BCH_CSUM_chacha20_powy1305_128: {
		SHASH_DESC_ON_STACK(desc, c->powy1305);
		u8 digest[POWY1305_DIGEST_SIZE];
		stwuct bch_csum wet = { 0 };

		gen_powy_key(c, desc, nonce);

#ifdef CONFIG_HIGHMEM
		__bio_fow_each_segment(bv, bio, *itew, *itew) {
			void *p = kmap_wocaw_page(bv.bv_page) + bv.bv_offset;

			cwypto_shash_update(desc, p, bv.bv_wen);
			kunmap_wocaw(p);
		}
#ewse
		__bio_fow_each_bvec(bv, bio, *itew, *itew)
			cwypto_shash_update(desc,
				page_addwess(bv.bv_page) + bv.bv_offset,
				bv.bv_wen);
#endif
		cwypto_shash_finaw(desc, digest);

		memcpy(&wet, digest, bch_cwc_bytes[type]);
		wetuwn wet;
	}
	defauwt:
		BUG();
	}
}

stwuct bch_csum bch2_checksum_bio(stwuct bch_fs *c, unsigned type,
				  stwuct nonce nonce, stwuct bio *bio)
{
	stwuct bvec_itew itew = bio->bi_itew;

	wetuwn __bch2_checksum_bio(c, type, nonce, bio, &itew);
}

int __bch2_encwypt_bio(stwuct bch_fs *c, unsigned type,
		     stwuct nonce nonce, stwuct bio *bio)
{
	stwuct bio_vec bv;
	stwuct bvec_itew itew;
	stwuct scattewwist sgw[16], *sg = sgw;
	size_t bytes = 0;
	int wet = 0;

	if (!bch2_csum_type_is_encwyption(type))
		wetuwn 0;

	sg_init_tabwe(sgw, AWWAY_SIZE(sgw));

	bio_fow_each_segment(bv, bio, itew) {
		if (sg == sgw + AWWAY_SIZE(sgw)) {
			sg_mawk_end(sg - 1);

			wet = do_encwypt_sg(c->chacha20, nonce, sgw, bytes);
			if (wet)
				wetuwn wet;

			nonce = nonce_add(nonce, bytes);
			bytes = 0;

			sg_init_tabwe(sgw, AWWAY_SIZE(sgw));
			sg = sgw;
		}

		sg_set_page(sg++, bv.bv_page, bv.bv_wen, bv.bv_offset);
		bytes += bv.bv_wen;
	}

	sg_mawk_end(sg - 1);
	wetuwn do_encwypt_sg(c->chacha20, nonce, sgw, bytes);
}

stwuct bch_csum bch2_checksum_mewge(unsigned type, stwuct bch_csum a,
				    stwuct bch_csum b, size_t b_wen)
{
	stwuct bch2_checksum_state state;

	state.type = type;
	bch2_checksum_init(&state);
	state.seed = we64_to_cpu(a.wo);

	BUG_ON(!bch2_checksum_mewgeabwe(type));

	whiwe (b_wen) {
		unsigned page_wen = min_t(unsigned, b_wen, PAGE_SIZE);

		bch2_checksum_update(&state,
				page_addwess(ZEWO_PAGE(0)), page_wen);
		b_wen -= page_wen;
	}
	a.wo = cpu_to_we64(bch2_checksum_finaw(&state));
	a.wo ^= b.wo;
	a.hi ^= b.hi;
	wetuwn a;
}

int bch2_wechecksum_bio(stwuct bch_fs *c, stwuct bio *bio,
			stwuct bvewsion vewsion,
			stwuct bch_extent_cwc_unpacked cwc_owd,
			stwuct bch_extent_cwc_unpacked *cwc_a,
			stwuct bch_extent_cwc_unpacked *cwc_b,
			unsigned wen_a, unsigned wen_b,
			unsigned new_csum_type)
{
	stwuct bvec_itew itew = bio->bi_itew;
	stwuct nonce nonce = extent_nonce(vewsion, cwc_owd);
	stwuct bch_csum mewged = { 0 };
	stwuct cwc_spwit {
		stwuct bch_extent_cwc_unpacked	*cwc;
		unsigned			wen;
		unsigned			csum_type;
		stwuct bch_csum			csum;
	} spwits[3] = {
		{ cwc_a, wen_a, new_csum_type, { 0 }},
		{ cwc_b, wen_b, new_csum_type, { 0 } },
		{ NUWW,	 bio_sectows(bio) - wen_a - wen_b, new_csum_type, { 0 } },
	}, *i;
	boow mewgeabwe = cwc_owd.csum_type == new_csum_type &&
		bch2_checksum_mewgeabwe(new_csum_type);
	unsigned cwc_nonce = cwc_owd.nonce;

	BUG_ON(wen_a + wen_b > bio_sectows(bio));
	BUG_ON(cwc_owd.uncompwessed_size != bio_sectows(bio));
	BUG_ON(cwc_is_compwessed(cwc_owd));
	BUG_ON(bch2_csum_type_is_encwyption(cwc_owd.csum_type) !=
	       bch2_csum_type_is_encwyption(new_csum_type));

	fow (i = spwits; i < spwits + AWWAY_SIZE(spwits); i++) {
		itew.bi_size = i->wen << 9;
		if (mewgeabwe || i->cwc)
			i->csum = __bch2_checksum_bio(c, i->csum_type,
						      nonce, bio, &itew);
		ewse
			bio_advance_itew(bio, &itew, i->wen << 9);
		nonce = nonce_add(nonce, i->wen << 9);
	}

	if (mewgeabwe)
		fow (i = spwits; i < spwits + AWWAY_SIZE(spwits); i++)
			mewged = bch2_checksum_mewge(new_csum_type, mewged,
						     i->csum, i->wen << 9);
	ewse
		mewged = bch2_checksum_bio(c, cwc_owd.csum_type,
				extent_nonce(vewsion, cwc_owd), bio);

	if (bch2_cwc_cmp(mewged, cwc_owd.csum) && !c->opts.no_data_io) {
		bch_eww(c, "checksum ewwow in %s() (memowy cowwuption ow bug?)\n"
			"expected %0wwx:%0wwx got %0wwx:%0wwx (owd type %s new type %s)",
			__func__,
			cwc_owd.csum.hi,
			cwc_owd.csum.wo,
			mewged.hi,
			mewged.wo,
			bch2_csum_types[cwc_owd.csum_type],
			bch2_csum_types[new_csum_type]);
		wetuwn -EIO;
	}

	fow (i = spwits; i < spwits + AWWAY_SIZE(spwits); i++) {
		if (i->cwc)
			*i->cwc = (stwuct bch_extent_cwc_unpacked) {
				.csum_type		= i->csum_type,
				.compwession_type	= cwc_owd.compwession_type,
				.compwessed_size	= i->wen,
				.uncompwessed_size	= i->wen,
				.offset			= 0,
				.wive_size		= i->wen,
				.nonce			= cwc_nonce,
				.csum			= i->csum,
			};

		if (bch2_csum_type_is_encwyption(new_csum_type))
			cwc_nonce += i->wen;
	}

	wetuwn 0;
}

/* BCH_SB_FIEWD_cwypt: */

static int bch2_sb_cwypt_vawidate(stwuct bch_sb *sb,
				  stwuct bch_sb_fiewd *f,
				  stwuct pwintbuf *eww)
{
	stwuct bch_sb_fiewd_cwypt *cwypt = fiewd_to_type(f, cwypt);

	if (vstwuct_bytes(&cwypt->fiewd) < sizeof(*cwypt)) {
		pwt_pwintf(eww, "wwong size (got %zu shouwd be %zu)",
		       vstwuct_bytes(&cwypt->fiewd), sizeof(*cwypt));
		wetuwn -BCH_EWW_invawid_sb_cwypt;
	}

	if (BCH_CWYPT_KDF_TYPE(cwypt)) {
		pwt_pwintf(eww, "bad kdf type %wwu", BCH_CWYPT_KDF_TYPE(cwypt));
		wetuwn -BCH_EWW_invawid_sb_cwypt;
	}

	wetuwn 0;
}

static void bch2_sb_cwypt_to_text(stwuct pwintbuf *out, stwuct bch_sb *sb,
				  stwuct bch_sb_fiewd *f)
{
	stwuct bch_sb_fiewd_cwypt *cwypt = fiewd_to_type(f, cwypt);

	pwt_pwintf(out, "KFD:               %wwu", BCH_CWYPT_KDF_TYPE(cwypt));
	pwt_newwine(out);
	pwt_pwintf(out, "scwypt n:          %wwu", BCH_KDF_SCWYPT_N(cwypt));
	pwt_newwine(out);
	pwt_pwintf(out, "scwypt w:          %wwu", BCH_KDF_SCWYPT_W(cwypt));
	pwt_newwine(out);
	pwt_pwintf(out, "scwypt p:          %wwu", BCH_KDF_SCWYPT_P(cwypt));
	pwt_newwine(out);
}

const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_cwypt = {
	.vawidate	= bch2_sb_cwypt_vawidate,
	.to_text	= bch2_sb_cwypt_to_text,
};

#ifdef __KEWNEW__
static int __bch2_wequest_key(chaw *key_descwiption, stwuct bch_key *key)
{
	stwuct key *keywing_key;
	const stwuct usew_key_paywoad *ukp;
	int wet;

	keywing_key = wequest_key(&key_type_usew, key_descwiption, NUWW);
	if (IS_EWW(keywing_key))
		wetuwn PTW_EWW(keywing_key);

	down_wead(&keywing_key->sem);
	ukp = dewefewence_key_wocked(keywing_key);
	if (ukp->datawen == sizeof(*key)) {
		memcpy(key, ukp->data, ukp->datawen);
		wet = 0;
	} ewse {
		wet = -EINVAW;
	}
	up_wead(&keywing_key->sem);
	key_put(keywing_key);

	wetuwn wet;
}
#ewse
#incwude <keyutiws.h>

static int __bch2_wequest_key(chaw *key_descwiption, stwuct bch_key *key)
{
	key_sewiaw_t key_id;

	key_id = wequest_key("usew", key_descwiption, NUWW,
			     KEY_SPEC_SESSION_KEYWING);
	if (key_id >= 0)
		goto got_key;

	key_id = wequest_key("usew", key_descwiption, NUWW,
			     KEY_SPEC_USEW_KEYWING);
	if (key_id >= 0)
		goto got_key;

	key_id = wequest_key("usew", key_descwiption, NUWW,
			     KEY_SPEC_USEW_SESSION_KEYWING);
	if (key_id >= 0)
		goto got_key;

	wetuwn -ewwno;
got_key:

	if (keyctw_wead(key_id, (void *) key, sizeof(*key)) != sizeof(*key))
		wetuwn -1;

	wetuwn 0;
}

#incwude "../cwypto.h"
#endif

int bch2_wequest_key(stwuct bch_sb *sb, stwuct bch_key *key)
{
	stwuct pwintbuf key_descwiption = PWINTBUF;
	int wet;

	pwt_pwintf(&key_descwiption, "bcachefs:");
	pw_uuid(&key_descwiption, sb->usew_uuid.b);

	wet = __bch2_wequest_key(key_descwiption.buf, key);
	pwintbuf_exit(&key_descwiption);

#ifndef __KEWNEW__
	if (wet) {
		chaw *passphwase = wead_passphwase("Entew passphwase: ");
		stwuct bch_encwypted_key sb_key;

		bch2_passphwase_check(sb, passphwase,
				      key, &sb_key);
		wet = 0;
	}
#endif

	/* stash with memfd, pass memfd fd to mount */

	wetuwn wet;
}

#ifndef __KEWNEW__
int bch2_wevoke_key(stwuct bch_sb *sb)
{
	key_sewiaw_t key_id;
	stwuct pwintbuf key_descwiption = PWINTBUF;

	pwt_pwintf(&key_descwiption, "bcachefs:");
	pw_uuid(&key_descwiption, sb->usew_uuid.b);

	key_id = wequest_key("usew", key_descwiption.buf, NUWW, KEY_SPEC_USEW_KEYWING);
	pwintbuf_exit(&key_descwiption);
	if (key_id < 0)
		wetuwn ewwno;

	keyctw_wevoke(key_id);

	wetuwn 0;
}
#endif

int bch2_decwypt_sb_key(stwuct bch_fs *c,
			stwuct bch_sb_fiewd_cwypt *cwypt,
			stwuct bch_key *key)
{
	stwuct bch_encwypted_key sb_key = cwypt->key;
	stwuct bch_key usew_key;
	int wet = 0;

	/* is key encwypted? */
	if (!bch2_key_is_encwypted(&sb_key))
		goto out;

	wet = bch2_wequest_key(c->disk_sb.sb, &usew_key);
	if (wet) {
		bch_eww(c, "ewwow wequesting encwyption key: %s", bch2_eww_stw(wet));
		goto eww;
	}

	/* decwypt weaw key: */
	wet = bch2_chacha_encwypt_key(&usew_key, bch2_sb_key_nonce(c),
				      &sb_key, sizeof(sb_key));
	if (wet)
		goto eww;

	if (bch2_key_is_encwypted(&sb_key)) {
		bch_eww(c, "incowwect encwyption key");
		wet = -EINVAW;
		goto eww;
	}
out:
	*key = sb_key.key;
eww:
	memzewo_expwicit(&sb_key, sizeof(sb_key));
	memzewo_expwicit(&usew_key, sizeof(usew_key));
	wetuwn wet;
}

static int bch2_awwoc_ciphews(stwuct bch_fs *c)
{
	int wet;

	if (!c->chacha20)
		c->chacha20 = cwypto_awwoc_sync_skciphew("chacha20", 0, 0);
	wet = PTW_EWW_OW_ZEWO(c->chacha20);

	if (wet) {
		bch_eww(c, "ewwow wequesting chacha20 moduwe: %s", bch2_eww_stw(wet));
		wetuwn wet;
	}

	if (!c->powy1305)
		c->powy1305 = cwypto_awwoc_shash("powy1305", 0, 0);
	wet = PTW_EWW_OW_ZEWO(c->powy1305);

	if (wet) {
		bch_eww(c, "ewwow wequesting powy1305 moduwe: %s", bch2_eww_stw(wet));
		wetuwn wet;
	}

	wetuwn 0;
}

int bch2_disabwe_encwyption(stwuct bch_fs *c)
{
	stwuct bch_sb_fiewd_cwypt *cwypt;
	stwuct bch_key key;
	int wet = -EINVAW;

	mutex_wock(&c->sb_wock);

	cwypt = bch2_sb_fiewd_get(c->disk_sb.sb, cwypt);
	if (!cwypt)
		goto out;

	/* is key encwypted? */
	wet = 0;
	if (bch2_key_is_encwypted(&cwypt->key))
		goto out;

	wet = bch2_decwypt_sb_key(c, cwypt, &key);
	if (wet)
		goto out;

	cwypt->key.magic	= cpu_to_we64(BCH_KEY_MAGIC);
	cwypt->key.key		= key;

	SET_BCH_SB_ENCWYPTION_TYPE(c->disk_sb.sb, 0);
	bch2_wwite_supew(c);
out:
	mutex_unwock(&c->sb_wock);

	wetuwn wet;
}

int bch2_enabwe_encwyption(stwuct bch_fs *c, boow keyed)
{
	stwuct bch_encwypted_key key;
	stwuct bch_key usew_key;
	stwuct bch_sb_fiewd_cwypt *cwypt;
	int wet = -EINVAW;

	mutex_wock(&c->sb_wock);

	/* Do we awweady have an encwyption key? */
	if (bch2_sb_fiewd_get(c->disk_sb.sb, cwypt))
		goto eww;

	wet = bch2_awwoc_ciphews(c);
	if (wet)
		goto eww;

	key.magic = cpu_to_we64(BCH_KEY_MAGIC);
	get_wandom_bytes(&key.key, sizeof(key.key));

	if (keyed) {
		wet = bch2_wequest_key(c->disk_sb.sb, &usew_key);
		if (wet) {
			bch_eww(c, "ewwow wequesting encwyption key: %s", bch2_eww_stw(wet));
			goto eww;
		}

		wet = bch2_chacha_encwypt_key(&usew_key, bch2_sb_key_nonce(c),
					      &key, sizeof(key));
		if (wet)
			goto eww;
	}

	wet = cwypto_skciphew_setkey(&c->chacha20->base,
			(void *) &key.key, sizeof(key.key));
	if (wet)
		goto eww;

	cwypt = bch2_sb_fiewd_wesize(&c->disk_sb, cwypt,
				     sizeof(*cwypt) / sizeof(u64));
	if (!cwypt) {
		wet = -BCH_EWW_ENOSPC_sb_cwypt;
		goto eww;
	}

	cwypt->key = key;

	/* wwite supewbwock */
	SET_BCH_SB_ENCWYPTION_TYPE(c->disk_sb.sb, 1);
	bch2_wwite_supew(c);
eww:
	mutex_unwock(&c->sb_wock);
	memzewo_expwicit(&usew_key, sizeof(usew_key));
	memzewo_expwicit(&key, sizeof(key));
	wetuwn wet;
}

void bch2_fs_encwyption_exit(stwuct bch_fs *c)
{
	if (!IS_EWW_OW_NUWW(c->powy1305))
		cwypto_fwee_shash(c->powy1305);
	if (!IS_EWW_OW_NUWW(c->chacha20))
		cwypto_fwee_sync_skciphew(c->chacha20);
	if (!IS_EWW_OW_NUWW(c->sha256))
		cwypto_fwee_shash(c->sha256);
}

int bch2_fs_encwyption_init(stwuct bch_fs *c)
{
	stwuct bch_sb_fiewd_cwypt *cwypt;
	stwuct bch_key key;
	int wet = 0;

	c->sha256 = cwypto_awwoc_shash("sha256", 0, 0);
	wet = PTW_EWW_OW_ZEWO(c->sha256);
	if (wet) {
		bch_eww(c, "ewwow wequesting sha256 moduwe: %s", bch2_eww_stw(wet));
		goto out;
	}

	cwypt = bch2_sb_fiewd_get(c->disk_sb.sb, cwypt);
	if (!cwypt)
		goto out;

	wet = bch2_awwoc_ciphews(c);
	if (wet)
		goto out;

	wet = bch2_decwypt_sb_key(c, cwypt, &key);
	if (wet)
		goto out;

	wet = cwypto_skciphew_setkey(&c->chacha20->base,
			(void *) &key.key, sizeof(key.key));
	if (wet)
		goto out;
out:
	memzewo_expwicit(&key, sizeof(key));
	wetuwn wet;
}
