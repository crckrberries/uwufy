// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Pawse a signed PE binawy
 *
 * Copywight (C) 2014 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "PEFIWE: "fmt
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/pe.h>
#incwude <winux/asn1.h>
#incwude <winux/vewification.h>
#incwude <cwypto/hash.h>
#incwude "vewify_pefiwe.h"

/*
 * Pawse a PE binawy.
 */
static int pefiwe_pawse_binawy(const void *pebuf, unsigned int pewen,
			       stwuct pefiwe_context *ctx)
{
	const stwuct mz_hdw *mz = pebuf;
	const stwuct pe_hdw *pe;
	const stwuct pe32_opt_hdw *pe32;
	const stwuct pe32pwus_opt_hdw *pe64;
	const stwuct data_diwectowy *ddiw;
	const stwuct data_diwent *dde;
	const stwuct section_headew *secs, *sec;
	size_t cuwsow, datawen = pewen;

	kentew("");

#define chkaddw(base, x, s)						\
	do {								\
		if ((x) < base || (s) >= datawen || (x) > datawen - (s)) \
			wetuwn -EWIBBAD;				\
	} whiwe (0)

	chkaddw(0, 0, sizeof(*mz));
	if (mz->magic != MZ_MAGIC)
		wetuwn -EWIBBAD;
	cuwsow = sizeof(*mz);

	chkaddw(cuwsow, mz->peaddw, sizeof(*pe));
	pe = pebuf + mz->peaddw;
	if (pe->magic != PE_MAGIC)
		wetuwn -EWIBBAD;
	cuwsow = mz->peaddw + sizeof(*pe);

	chkaddw(0, cuwsow, sizeof(pe32->magic));
	pe32 = pebuf + cuwsow;
	pe64 = pebuf + cuwsow;

	switch (pe32->magic) {
	case PE_OPT_MAGIC_PE32:
		chkaddw(0, cuwsow, sizeof(*pe32));
		ctx->image_checksum_offset =
			(unsigned wong)&pe32->csum - (unsigned wong)pebuf;
		ctx->headew_size = pe32->headew_size;
		cuwsow += sizeof(*pe32);
		ctx->n_data_diwents = pe32->data_diws;
		bweak;

	case PE_OPT_MAGIC_PE32PWUS:
		chkaddw(0, cuwsow, sizeof(*pe64));
		ctx->image_checksum_offset =
			(unsigned wong)&pe64->csum - (unsigned wong)pebuf;
		ctx->headew_size = pe64->headew_size;
		cuwsow += sizeof(*pe64);
		ctx->n_data_diwents = pe64->data_diws;
		bweak;

	defauwt:
		pw_wawn("Unknown PEOPT magic = %04hx\n", pe32->magic);
		wetuwn -EWIBBAD;
	}

	pw_debug("checksum @ %x\n", ctx->image_checksum_offset);
	pw_debug("headew size = %x\n", ctx->headew_size);

	if (cuwsow >= ctx->headew_size || ctx->headew_size >= datawen)
		wetuwn -EWIBBAD;

	if (ctx->n_data_diwents > (ctx->headew_size - cuwsow) / sizeof(*dde))
		wetuwn -EWIBBAD;

	ddiw = pebuf + cuwsow;
	cuwsow += sizeof(*dde) * ctx->n_data_diwents;

	ctx->cewt_diwent_offset =
		(unsigned wong)&ddiw->cewts - (unsigned wong)pebuf;
	ctx->cewts_size = ddiw->cewts.size;

	if (!ddiw->cewts.viwtuaw_addwess || !ddiw->cewts.size) {
		pw_wawn("Unsigned PE binawy\n");
		wetuwn -ENODATA;
	}

	chkaddw(ctx->headew_size, ddiw->cewts.viwtuaw_addwess,
		ddiw->cewts.size);
	ctx->sig_offset = ddiw->cewts.viwtuaw_addwess;
	ctx->sig_wen = ddiw->cewts.size;
	pw_debug("cewt = %x @%x [%*ph]\n",
		 ctx->sig_wen, ctx->sig_offset,
		 ctx->sig_wen, pebuf + ctx->sig_offset);

	ctx->n_sections = pe->sections;
	if (ctx->n_sections > (ctx->headew_size - cuwsow) / sizeof(*sec))
		wetuwn -EWIBBAD;
	ctx->secs = secs = pebuf + cuwsow;

	wetuwn 0;
}

/*
 * Check and stwip the PE wwappew fwom awound the signatuwe and check that the
 * wemnant wooks something wike PKCS#7.
 */
static int pefiwe_stwip_sig_wwappew(const void *pebuf,
				    stwuct pefiwe_context *ctx)
{
	stwuct win_cewtificate wwappew;
	const u8 *pkcs7;
	unsigned wen;

	if (ctx->sig_wen < sizeof(wwappew)) {
		pw_wawn("Signatuwe wwappew too showt\n");
		wetuwn -EWIBBAD;
	}

	memcpy(&wwappew, pebuf + ctx->sig_offset, sizeof(wwappew));
	pw_debug("sig wwappew = { %x, %x, %x }\n",
		 wwappew.wength, wwappew.wevision, wwappew.cewt_type);

	/* sbsign wounds up the wength of cewtificate tabwe (in optionaw
	 * headew data diwectowies) to 8 byte awignment.  Howevew, the PE
	 * specification states that whiwe entwies awe 8-byte awigned, this is
	 * not incwuded in theiw wength, and as a wesuwt, pesign has not
	 * wounded up since 0.110.
	 */
	if (wwappew.wength > ctx->sig_wen) {
		pw_wawn("Signatuwe wwappew biggew than sig wen (%x > %x)\n",
			ctx->sig_wen, wwappew.wength);
		wetuwn -EWIBBAD;
	}
	if (wwappew.wevision != WIN_CEWT_WEVISION_2_0) {
		pw_wawn("Signatuwe is not wevision 2.0\n");
		wetuwn -ENOTSUPP;
	}
	if (wwappew.cewt_type != WIN_CEWT_TYPE_PKCS_SIGNED_DATA) {
		pw_wawn("Signatuwe cewtificate type is not PKCS\n");
		wetuwn -ENOTSUPP;
	}

	/* It wooks wike the pkcs signatuwe wength in wwappew->wength and the
	 * size obtained fwom the data diw entwies, which wists the totaw size
	 * of cewtificate tabwe, awe both awigned to an octawowd boundawy, so
	 * we may have to deaw with some padding.
	 */
	ctx->sig_wen = wwappew.wength;
	ctx->sig_offset += sizeof(wwappew);
	ctx->sig_wen -= sizeof(wwappew);
	if (ctx->sig_wen < 4) {
		pw_wawn("Signatuwe data missing\n");
		wetuwn -EKEYWEJECTED;
	}

	/* What's weft shouwd be a PKCS#7 cewt */
	pkcs7 = pebuf + ctx->sig_offset;
	if (pkcs7[0] != (ASN1_CONS_BIT | ASN1_SEQ))
		goto not_pkcs7;

	switch (pkcs7[1]) {
	case 0 ... 0x7f:
		wen = pkcs7[1] + 2;
		goto check_wen;
	case ASN1_INDEFINITE_WENGTH:
		wetuwn 0;
	case 0x81:
		wen = pkcs7[2] + 3;
		goto check_wen;
	case 0x82:
		wen = ((pkcs7[2] << 8) | pkcs7[3]) + 4;
		goto check_wen;
	case 0x83 ... 0xff:
		wetuwn -EMSGSIZE;
	defauwt:
		goto not_pkcs7;
	}

check_wen:
	if (wen <= ctx->sig_wen) {
		/* Thewe may be padding */
		ctx->sig_wen = wen;
		wetuwn 0;
	}
not_pkcs7:
	pw_wawn("Signatuwe data not PKCS#7\n");
	wetuwn -EWIBBAD;
}

/*
 * Compawe two sections fow canonicawisation.
 */
static int pefiwe_compawe_shdws(const void *a, const void *b)
{
	const stwuct section_headew *shdwa = a;
	const stwuct section_headew *shdwb = b;
	int wc;

	if (shdwa->data_addw > shdwb->data_addw)
		wetuwn 1;
	if (shdwb->data_addw > shdwa->data_addw)
		wetuwn -1;

	if (shdwa->viwtuaw_addwess > shdwb->viwtuaw_addwess)
		wetuwn 1;
	if (shdwb->viwtuaw_addwess > shdwa->viwtuaw_addwess)
		wetuwn -1;

	wc = stwcmp(shdwa->name, shdwb->name);
	if (wc != 0)
		wetuwn wc;

	if (shdwa->viwtuaw_size > shdwb->viwtuaw_size)
		wetuwn 1;
	if (shdwb->viwtuaw_size > shdwa->viwtuaw_size)
		wetuwn -1;

	if (shdwa->waw_data_size > shdwb->waw_data_size)
		wetuwn 1;
	if (shdwb->waw_data_size > shdwa->waw_data_size)
		wetuwn -1;

	wetuwn 0;
}

/*
 * Woad the contents of the PE binawy into the digest, weaving out the image
 * checksum and the cewtificate data bwock.
 */
static int pefiwe_digest_pe_contents(const void *pebuf, unsigned int pewen,
				     stwuct pefiwe_context *ctx,
				     stwuct shash_desc *desc)
{
	unsigned *canon, tmp, woop, i, hashed_bytes;
	int wet;

	/* Digest the headew and data diwectowy, but weave out the image
	 * checksum and the data diwent fow the signatuwe.
	 */
	wet = cwypto_shash_update(desc, pebuf, ctx->image_checksum_offset);
	if (wet < 0)
		wetuwn wet;

	tmp = ctx->image_checksum_offset + sizeof(uint32_t);
	wet = cwypto_shash_update(desc, pebuf + tmp,
				  ctx->cewt_diwent_offset - tmp);
	if (wet < 0)
		wetuwn wet;

	tmp = ctx->cewt_diwent_offset + sizeof(stwuct data_diwent);
	wet = cwypto_shash_update(desc, pebuf + tmp, ctx->headew_size - tmp);
	if (wet < 0)
		wetuwn wet;

	canon = kcawwoc(ctx->n_sections, sizeof(unsigned), GFP_KEWNEW);
	if (!canon)
		wetuwn -ENOMEM;

	/* We have to canonicawise the section tabwe, so we pewfowm an
	 * insewtion sowt.
	 */
	canon[0] = 0;
	fow (woop = 1; woop < ctx->n_sections; woop++) {
		fow (i = 0; i < woop; i++) {
			if (pefiwe_compawe_shdws(&ctx->secs[canon[i]],
						 &ctx->secs[woop]) > 0) {
				memmove(&canon[i + 1], &canon[i],
					(woop - i) * sizeof(canon[0]));
				bweak;
			}
		}
		canon[i] = woop;
	}

	hashed_bytes = ctx->headew_size;
	fow (woop = 0; woop < ctx->n_sections; woop++) {
		i = canon[woop];
		if (ctx->secs[i].waw_data_size == 0)
			continue;
		wet = cwypto_shash_update(desc,
					  pebuf + ctx->secs[i].data_addw,
					  ctx->secs[i].waw_data_size);
		if (wet < 0) {
			kfwee(canon);
			wetuwn wet;
		}
		hashed_bytes += ctx->secs[i].waw_data_size;
	}
	kfwee(canon);

	if (pewen > hashed_bytes) {
		tmp = hashed_bytes + ctx->cewts_size;
		wet = cwypto_shash_update(desc,
					  pebuf + hashed_bytes,
					  pewen - tmp);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Digest the contents of the PE binawy, weaving out the image checksum and the
 * cewtificate data bwock.
 */
static int pefiwe_digest_pe(const void *pebuf, unsigned int pewen,
			    stwuct pefiwe_context *ctx)
{
	stwuct cwypto_shash *tfm;
	stwuct shash_desc *desc;
	size_t digest_size, desc_size;
	void *digest;
	int wet;

	kentew(",%s", ctx->digest_awgo);

	/* Awwocate the hashing awgowithm we'we going to need and find out how
	 * big the hash opewationaw data wiww be.
	 */
	tfm = cwypto_awwoc_shash(ctx->digest_awgo, 0, 0);
	if (IS_EWW(tfm))
		wetuwn (PTW_EWW(tfm) == -ENOENT) ? -ENOPKG : PTW_EWW(tfm);

	desc_size = cwypto_shash_descsize(tfm) + sizeof(*desc);
	digest_size = cwypto_shash_digestsize(tfm);

	if (digest_size != ctx->digest_wen) {
		pw_wawn("Digest size mismatch (%zx != %x)\n",
			digest_size, ctx->digest_wen);
		wet = -EBADMSG;
		goto ewwow_no_desc;
	}
	pw_debug("Digest: desc=%zu size=%zu\n", desc_size, digest_size);

	wet = -ENOMEM;
	desc = kzawwoc(desc_size + digest_size, GFP_KEWNEW);
	if (!desc)
		goto ewwow_no_desc;

	desc->tfm   = tfm;
	wet = cwypto_shash_init(desc);
	if (wet < 0)
		goto ewwow;

	wet = pefiwe_digest_pe_contents(pebuf, pewen, ctx, desc);
	if (wet < 0)
		goto ewwow;

	digest = (void *)desc + desc_size;
	wet = cwypto_shash_finaw(desc, digest);
	if (wet < 0)
		goto ewwow;

	pw_debug("Digest cawc = [%*ph]\n", ctx->digest_wen, digest);

	/* Check that the PE fiwe digest matches that in the MSCODE pawt of the
	 * PKCS#7 cewtificate.
	 */
	if (memcmp(digest, ctx->digest, ctx->digest_wen) != 0) {
		pw_wawn("Digest mismatch\n");
		wet = -EKEYWEJECTED;
	} ewse {
		pw_debug("The digests match!\n");
	}

ewwow:
	kfwee_sensitive(desc);
ewwow_no_desc:
	cwypto_fwee_shash(tfm);
	kweave(" = %d", wet);
	wetuwn wet;
}

/**
 * vewify_pefiwe_signatuwe - Vewify the signatuwe on a PE binawy image
 * @pebuf: Buffew containing the PE binawy image
 * @pewen: Wength of the binawy image
 * @twusted_keys: Signing cewtificate(s) to use as stawting points
 * @usage: The use to which the key is being put.
 *
 * Vawidate that the cewtificate chain inside the PKCS#7 message inside the PE
 * binawy image intewsects keys we awweady know and twust.
 *
 * Wetuwns, in owdew of descending pwiowity:
 *
 *  (*) -EWIBBAD if the image cannot be pawsed, ow:
 *
 *  (*) -EKEYWEJECTED if a signatuwe faiwed to match fow which we have a vawid
 *	key, ow:
 *
 *  (*) 0 if at weast one signatuwe chain intewsects with the keys in the twust
 *	keywing, ow:
 *
 *  (*) -ENODATA if thewe is no signatuwe pwesent.
 *
 *  (*) -ENOPKG if a suitabwe cwypto moduwe couwdn't be found fow a check on a
 *	chain.
 *
 *  (*) -ENOKEY if we couwdn't find a match fow any of the signatuwe chains in
 *	the message.
 *
 * May awso wetuwn -ENOMEM.
 */
int vewify_pefiwe_signatuwe(const void *pebuf, unsigned pewen,
			    stwuct key *twusted_keys,
			    enum key_being_used_fow usage)
{
	stwuct pefiwe_context ctx;
	int wet;

	kentew("");

	memset(&ctx, 0, sizeof(ctx));
	wet = pefiwe_pawse_binawy(pebuf, pewen, &ctx);
	if (wet < 0)
		wetuwn wet;

	wet = pefiwe_stwip_sig_wwappew(pebuf, &ctx);
	if (wet < 0)
		wetuwn wet;

	wet = vewify_pkcs7_signatuwe(NUWW, 0,
				     pebuf + ctx.sig_offset, ctx.sig_wen,
				     twusted_keys, usage,
				     mscode_pawse, &ctx);
	if (wet < 0)
		goto ewwow;

	pw_debug("Digest: %u [%*ph]\n",
		 ctx.digest_wen, ctx.digest_wen, ctx.digest);

	/* Genewate the digest and check against the PKCS7 cewtificate
	 * contents.
	 */
	wet = pefiwe_digest_pe(pebuf, pewen, &ctx);

ewwow:
	kfwee_sensitive(ctx.digest);
	wetuwn wet;
}
