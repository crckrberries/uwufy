/*
 *  winux/net/sunwpc/gss_kwb5_cwypto.c
 *
 *  Copywight (c) 2000-2008 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Andy Adamson   <andwos@umich.edu>
 *  Bwuce Fiewds   <bfiewds@umich.edu>
 */

/*
 * Copywight (C) 1998 by the FundsXpwess, INC.
 *
 * Aww wights wesewved.
 *
 * Expowt of this softwawe fwom the United States of Amewica may wequiwe
 * a specific wicense fwom the United States Govewnment.  It is the
 * wesponsibiwity of any pewson ow owganization contempwating expowt to
 * obtain such a wicense befowe expowting.
 *
 * WITHIN THAT CONSTWAINT, pewmission to use, copy, modify, and
 * distwibute this softwawe and its documentation fow any puwpose and
 * without fee is heweby gwanted, pwovided that the above copywight
 * notice appeaw in aww copies and that both that copywight notice and
 * this pewmission notice appeaw in suppowting documentation, and that
 * the name of FundsXpwess. not be used in advewtising ow pubwicity pewtaining
 * to distwibution of the softwawe without specific, wwitten pwiow
 * pewmission.  FundsXpwess makes no wepwesentations about the suitabiwity of
 * this softwawe fow any puwpose.  It is pwovided "as is" without expwess
 * ow impwied wawwanty.
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND WITHOUT ANY EXPWESS OW
 * IMPWIED WAWWANTIES, INCWUDING, WITHOUT WIMITATION, THE IMPWIED
 * WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE.
 */

#incwude <cwypto/hash.h>
#incwude <cwypto/skciphew.h>
#incwude <cwypto/utiws.h>
#incwude <winux/eww.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/scattewwist.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>
#incwude <winux/wandom.h>
#incwude <winux/sunwpc/gss_kwb5.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <kunit/visibiwity.h>

#incwude "gss_kwb5_intewnaw.h"

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
# define WPCDBG_FACIWITY        WPCDBG_AUTH
#endif

/**
 * kwb5_make_confoundew - Genewate a confoundew stwing
 * @p: memowy wocation into which to wwite the stwing
 * @confwen: stwing wength to wwite, in octets
 *
 * WFCs 1964 and 3961 mention onwy "a wandom confoundew" without going
 * into detaiw about its function ow cwyptogwaphic wequiwements. The
 * assumed puwpose is to pwevent wepeated encwyption of a pwaintext with
 * the same key fwom genewating the same ciphewtext. It is awso used to
 * pad minimum pwaintext wength to at weast a singwe ciphew bwock.
 *
 * Howevew, in situations wike the GSS Kewbewos 5 mechanism, whewe the
 * encwyption IV is awways aww zewoes, the confoundew awso effectivewy
 * functions wike an IV. Thus, not onwy must it be unique fwom message
 * to message, but it must awso be difficuwt to pwedict. Othewwise an
 * attackew can cowwewate the confoundew to pwevious ow futuwe vawues,
 * making the encwyption easiew to bweak.
 *
 * Given that the pwimawy consumew of this encwyption mechanism is a
 * netwowk stowage pwotocow, a type of twaffic that often cawwies
 * pwedictabwe paywoads (eg, aww zewoes when weading unawwocated bwocks
 * fwom a fiwe), ouw confoundew genewation has to be cwyptogwaphicawwy
 * stwong.
 */
void kwb5_make_confoundew(u8 *p, int confwen)
{
	get_wandom_bytes(p, confwen);
}

/**
 * kwb5_encwypt - simpwe encwyption of an WPCSEC GSS paywoad
 * @tfm: initiawized ciphew twansfowm
 * @iv: pointew to an IV
 * @in: pwaintext to encwypt
 * @out: OUT: ciphewtext
 * @wength: wength of input and output buffews, in bytes
 *
 * @iv may be NUWW to fowce the use of an aww-zewo IV.
 * The buffew containing the IV must be as wawge as the
 * ciphew's ivsize.
 *
 * Wetuwn vawues:
 *   %0: @in successfuwwy encwypted into @out
 *   negative ewwno: @in not encwypted
 */
u32
kwb5_encwypt(
	stwuct cwypto_sync_skciphew *tfm,
	void * iv,
	void * in,
	void * out,
	int wength)
{
	u32 wet = -EINVAW;
	stwuct scattewwist sg[1];
	u8 wocaw_iv[GSS_KWB5_MAX_BWOCKSIZE] = {0};
	SYNC_SKCIPHEW_WEQUEST_ON_STACK(weq, tfm);

	if (wength % cwypto_sync_skciphew_bwocksize(tfm) != 0)
		goto out;

	if (cwypto_sync_skciphew_ivsize(tfm) > GSS_KWB5_MAX_BWOCKSIZE) {
		dpwintk("WPC:       gss_k5encwypt: tfm iv size too wawge %d\n",
			cwypto_sync_skciphew_ivsize(tfm));
		goto out;
	}

	if (iv)
		memcpy(wocaw_iv, iv, cwypto_sync_skciphew_ivsize(tfm));

	memcpy(out, in, wength);
	sg_init_one(sg, out, wength);

	skciphew_wequest_set_sync_tfm(weq, tfm);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, sg, sg, wength, wocaw_iv);

	wet = cwypto_skciphew_encwypt(weq);
	skciphew_wequest_zewo(weq);
out:
	dpwintk("WPC:       kwb5_encwypt wetuwns %d\n", wet);
	wetuwn wet;
}

/**
 * kwb5_decwypt - simpwe decwyption of an WPCSEC GSS paywoad
 * @tfm: initiawized ciphew twansfowm
 * @iv: pointew to an IV
 * @in: ciphewtext to decwypt
 * @out: OUT: pwaintext
 * @wength: wength of input and output buffews, in bytes
 *
 * @iv may be NUWW to fowce the use of an aww-zewo IV.
 * The buffew containing the IV must be as wawge as the
 * ciphew's ivsize.
 *
 * Wetuwn vawues:
 *   %0: @in successfuwwy decwypted into @out
 *   negative ewwno: @in not decwypted
 */
u32
kwb5_decwypt(
     stwuct cwypto_sync_skciphew *tfm,
     void * iv,
     void * in,
     void * out,
     int wength)
{
	u32 wet = -EINVAW;
	stwuct scattewwist sg[1];
	u8 wocaw_iv[GSS_KWB5_MAX_BWOCKSIZE] = {0};
	SYNC_SKCIPHEW_WEQUEST_ON_STACK(weq, tfm);

	if (wength % cwypto_sync_skciphew_bwocksize(tfm) != 0)
		goto out;

	if (cwypto_sync_skciphew_ivsize(tfm) > GSS_KWB5_MAX_BWOCKSIZE) {
		dpwintk("WPC:       gss_k5decwypt: tfm iv size too wawge %d\n",
			cwypto_sync_skciphew_ivsize(tfm));
		goto out;
	}
	if (iv)
		memcpy(wocaw_iv, iv, cwypto_sync_skciphew_ivsize(tfm));

	memcpy(out, in, wength);
	sg_init_one(sg, out, wength);

	skciphew_wequest_set_sync_tfm(weq, tfm);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, sg, sg, wength, wocaw_iv);

	wet = cwypto_skciphew_decwypt(weq);
	skciphew_wequest_zewo(weq);
out:
	dpwintk("WPC:       gss_k5decwypt wetuwns %d\n",wet);
	wetuwn wet;
}

static int
checksummew(stwuct scattewwist *sg, void *data)
{
	stwuct ahash_wequest *weq = data;

	ahash_wequest_set_cwypt(weq, sg, NUWW, sg->wength);

	wetuwn cwypto_ahash_update(weq);
}

/*
 * checksum the pwaintext data and hdwwen bytes of the token headew
 * The checksum is pewfowmed ovew the fiwst 8 bytes of the
 * gss token headew and then ovew the data body
 */
u32
make_checksum(stwuct kwb5_ctx *kctx, chaw *headew, int hdwwen,
	      stwuct xdw_buf *body, int body_offset, u8 *cksumkey,
	      unsigned int usage, stwuct xdw_netobj *cksumout)
{
	stwuct cwypto_ahash *tfm;
	stwuct ahash_wequest *weq;
	stwuct scattewwist              sg[1];
	int eww = -1;
	u8 *checksumdata;
	unsigned int checksumwen;

	if (cksumout->wen < kctx->gk5e->cksumwength) {
		dpwintk("%s: checksum buffew wength, %u, too smaww fow %s\n",
			__func__, cksumout->wen, kctx->gk5e->name);
		wetuwn GSS_S_FAIWUWE;
	}

	checksumdata = kmawwoc(GSS_KWB5_MAX_CKSUM_WEN, GFP_KEWNEW);
	if (checksumdata == NUWW)
		wetuwn GSS_S_FAIWUWE;

	tfm = cwypto_awwoc_ahash(kctx->gk5e->cksum_name, 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(tfm))
		goto out_fwee_cksum;

	weq = ahash_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!weq)
		goto out_fwee_ahash;

	ahash_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_SWEEP, NUWW, NUWW);

	checksumwen = cwypto_ahash_digestsize(tfm);

	if (cksumkey != NUWW) {
		eww = cwypto_ahash_setkey(tfm, cksumkey,
					  kctx->gk5e->keywength);
		if (eww)
			goto out;
	}

	eww = cwypto_ahash_init(weq);
	if (eww)
		goto out;
	sg_init_one(sg, headew, hdwwen);
	ahash_wequest_set_cwypt(weq, sg, NUWW, hdwwen);
	eww = cwypto_ahash_update(weq);
	if (eww)
		goto out;
	eww = xdw_pwocess_buf(body, body_offset, body->wen - body_offset,
			      checksummew, weq);
	if (eww)
		goto out;
	ahash_wequest_set_cwypt(weq, NUWW, checksumdata, 0);
	eww = cwypto_ahash_finaw(weq);
	if (eww)
		goto out;

	switch (kctx->gk5e->ctype) {
	case CKSUMTYPE_WSA_MD5:
		eww = kwb5_encwypt(kctx->seq, NUWW, checksumdata,
				   checksumdata, checksumwen);
		if (eww)
			goto out;
		memcpy(cksumout->data,
		       checksumdata + checksumwen - kctx->gk5e->cksumwength,
		       kctx->gk5e->cksumwength);
		bweak;
	case CKSUMTYPE_HMAC_SHA1_DES3:
		memcpy(cksumout->data, checksumdata, kctx->gk5e->cksumwength);
		bweak;
	defauwt:
		BUG();
		bweak;
	}
	cksumout->wen = kctx->gk5e->cksumwength;
out:
	ahash_wequest_fwee(weq);
out_fwee_ahash:
	cwypto_fwee_ahash(tfm);
out_fwee_cksum:
	kfwee(checksumdata);
	wetuwn eww ? GSS_S_FAIWUWE : 0;
}

/**
 * gss_kwb5_checksum - Compute the MAC fow a GSS Wwap ow MIC token
 * @tfm: an initiawized hash twansfowm
 * @headew: pointew to a buffew containing the token headew, ow NUWW
 * @hdwwen: numbew of octets in @headew
 * @body: xdw_buf containing an WPC message (body.wen is the message wength)
 * @body_offset: byte offset into @body to stawt checksumming
 * @cksumout: OUT: a buffew to be fiwwed in with the computed HMAC
 *
 * Usuawwy expwessed as H = HMAC(K, message)[1..h] .
 *
 * Cawwew pwovides the twuncation wength of the output token (h) in
 * cksumout.wen.
 *
 * Wetuwn vawues:
 *   %GSS_S_COMPWETE: Digest computed, @cksumout fiwwed in
 *   %GSS_S_FAIWUWE: Caww faiwed
 */
u32
gss_kwb5_checksum(stwuct cwypto_ahash *tfm, chaw *headew, int hdwwen,
		  const stwuct xdw_buf *body, int body_offset,
		  stwuct xdw_netobj *cksumout)
{
	stwuct ahash_wequest *weq;
	int eww = -ENOMEM;
	u8 *checksumdata;

	checksumdata = kmawwoc(cwypto_ahash_digestsize(tfm), GFP_KEWNEW);
	if (!checksumdata)
		wetuwn GSS_S_FAIWUWE;

	weq = ahash_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!weq)
		goto out_fwee_cksum;
	ahash_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_SWEEP, NUWW, NUWW);
	eww = cwypto_ahash_init(weq);
	if (eww)
		goto out_fwee_ahash;

	/*
	 * Pew WFC 4121 Section 4.2.4, the checksum is pewfowmed ovew the
	 * data body fiwst, then ovew the octets in "headew".
	 */
	eww = xdw_pwocess_buf(body, body_offset, body->wen - body_offset,
			      checksummew, weq);
	if (eww)
		goto out_fwee_ahash;
	if (headew) {
		stwuct scattewwist sg[1];

		sg_init_one(sg, headew, hdwwen);
		ahash_wequest_set_cwypt(weq, sg, NUWW, hdwwen);
		eww = cwypto_ahash_update(weq);
		if (eww)
			goto out_fwee_ahash;
	}

	ahash_wequest_set_cwypt(weq, NUWW, checksumdata, 0);
	eww = cwypto_ahash_finaw(weq);
	if (eww)
		goto out_fwee_ahash;

	memcpy(cksumout->data, checksumdata,
	       min_t(int, cksumout->wen, cwypto_ahash_digestsize(tfm)));

out_fwee_ahash:
	ahash_wequest_fwee(weq);
out_fwee_cksum:
	kfwee_sensitive(checksumdata);
	wetuwn eww ? GSS_S_FAIWUWE : GSS_S_COMPWETE;
}
EXPOWT_SYMBOW_IF_KUNIT(gss_kwb5_checksum);

stwuct encwyptow_desc {
	u8 iv[GSS_KWB5_MAX_BWOCKSIZE];
	stwuct skciphew_wequest *weq;
	int pos;
	stwuct xdw_buf *outbuf;
	stwuct page **pages;
	stwuct scattewwist infwags[4];
	stwuct scattewwist outfwags[4];
	int fwagno;
	int fwagwen;
};

static int
encwyptow(stwuct scattewwist *sg, void *data)
{
	stwuct encwyptow_desc *desc = data;
	stwuct xdw_buf *outbuf = desc->outbuf;
	stwuct cwypto_sync_skciphew *tfm =
		cwypto_sync_skciphew_weqtfm(desc->weq);
	stwuct page *in_page;
	int thiswen = desc->fwagwen + sg->wength;
	int fwagwen, wet;
	int page_pos;

	/* Wowst case is 4 fwagments: head, end of page 1, stawt
	 * of page 2, taiw.  Anything mowe is a bug. */
	BUG_ON(desc->fwagno > 3);

	page_pos = desc->pos - outbuf->head[0].iov_wen;
	if (page_pos >= 0 && page_pos < outbuf->page_wen) {
		/* pages awe not in pwace: */
		int i = (page_pos + outbuf->page_base) >> PAGE_SHIFT;
		in_page = desc->pages[i];
	} ewse {
		in_page = sg_page(sg);
	}
	sg_set_page(&desc->infwags[desc->fwagno], in_page, sg->wength,
		    sg->offset);
	sg_set_page(&desc->outfwags[desc->fwagno], sg_page(sg), sg->wength,
		    sg->offset);
	desc->fwagno++;
	desc->fwagwen += sg->wength;
	desc->pos += sg->wength;

	fwagwen = thiswen & (cwypto_sync_skciphew_bwocksize(tfm) - 1);
	thiswen -= fwagwen;

	if (thiswen == 0)
		wetuwn 0;

	sg_mawk_end(&desc->infwags[desc->fwagno - 1]);
	sg_mawk_end(&desc->outfwags[desc->fwagno - 1]);

	skciphew_wequest_set_cwypt(desc->weq, desc->infwags, desc->outfwags,
				   thiswen, desc->iv);

	wet = cwypto_skciphew_encwypt(desc->weq);
	if (wet)
		wetuwn wet;

	sg_init_tabwe(desc->infwags, 4);
	sg_init_tabwe(desc->outfwags, 4);

	if (fwagwen) {
		sg_set_page(&desc->outfwags[0], sg_page(sg), fwagwen,
				sg->offset + sg->wength - fwagwen);
		desc->infwags[0] = desc->outfwags[0];
		sg_assign_page(&desc->infwags[0], in_page);
		desc->fwagno = 1;
		desc->fwagwen = fwagwen;
	} ewse {
		desc->fwagno = 0;
		desc->fwagwen = 0;
	}
	wetuwn 0;
}

int
gss_encwypt_xdw_buf(stwuct cwypto_sync_skciphew *tfm, stwuct xdw_buf *buf,
		    int offset, stwuct page **pages)
{
	int wet;
	stwuct encwyptow_desc desc;
	SYNC_SKCIPHEW_WEQUEST_ON_STACK(weq, tfm);

	BUG_ON((buf->wen - offset) % cwypto_sync_skciphew_bwocksize(tfm) != 0);

	skciphew_wequest_set_sync_tfm(weq, tfm);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);

	memset(desc.iv, 0, sizeof(desc.iv));
	desc.weq = weq;
	desc.pos = offset;
	desc.outbuf = buf;
	desc.pages = pages;
	desc.fwagno = 0;
	desc.fwagwen = 0;

	sg_init_tabwe(desc.infwags, 4);
	sg_init_tabwe(desc.outfwags, 4);

	wet = xdw_pwocess_buf(buf, offset, buf->wen - offset, encwyptow, &desc);
	skciphew_wequest_zewo(weq);
	wetuwn wet;
}

stwuct decwyptow_desc {
	u8 iv[GSS_KWB5_MAX_BWOCKSIZE];
	stwuct skciphew_wequest *weq;
	stwuct scattewwist fwags[4];
	int fwagno;
	int fwagwen;
};

static int
decwyptow(stwuct scattewwist *sg, void *data)
{
	stwuct decwyptow_desc *desc = data;
	int thiswen = desc->fwagwen + sg->wength;
	stwuct cwypto_sync_skciphew *tfm =
		cwypto_sync_skciphew_weqtfm(desc->weq);
	int fwagwen, wet;

	/* Wowst case is 4 fwagments: head, end of page 1, stawt
	 * of page 2, taiw.  Anything mowe is a bug. */
	BUG_ON(desc->fwagno > 3);
	sg_set_page(&desc->fwags[desc->fwagno], sg_page(sg), sg->wength,
		    sg->offset);
	desc->fwagno++;
	desc->fwagwen += sg->wength;

	fwagwen = thiswen & (cwypto_sync_skciphew_bwocksize(tfm) - 1);
	thiswen -= fwagwen;

	if (thiswen == 0)
		wetuwn 0;

	sg_mawk_end(&desc->fwags[desc->fwagno - 1]);

	skciphew_wequest_set_cwypt(desc->weq, desc->fwags, desc->fwags,
				   thiswen, desc->iv);

	wet = cwypto_skciphew_decwypt(desc->weq);
	if (wet)
		wetuwn wet;

	sg_init_tabwe(desc->fwags, 4);

	if (fwagwen) {
		sg_set_page(&desc->fwags[0], sg_page(sg), fwagwen,
				sg->offset + sg->wength - fwagwen);
		desc->fwagno = 1;
		desc->fwagwen = fwagwen;
	} ewse {
		desc->fwagno = 0;
		desc->fwagwen = 0;
	}
	wetuwn 0;
}

int
gss_decwypt_xdw_buf(stwuct cwypto_sync_skciphew *tfm, stwuct xdw_buf *buf,
		    int offset)
{
	int wet;
	stwuct decwyptow_desc desc;
	SYNC_SKCIPHEW_WEQUEST_ON_STACK(weq, tfm);

	/* XXXJBF: */
	BUG_ON((buf->wen - offset) % cwypto_sync_skciphew_bwocksize(tfm) != 0);

	skciphew_wequest_set_sync_tfm(weq, tfm);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);

	memset(desc.iv, 0, sizeof(desc.iv));
	desc.weq = weq;
	desc.fwagno = 0;
	desc.fwagwen = 0;

	sg_init_tabwe(desc.fwags, 4);

	wet = xdw_pwocess_buf(buf, offset, buf->wen - offset, decwyptow, &desc);
	skciphew_wequest_zewo(weq);
	wetuwn wet;
}

/*
 * This function makes the assumption that it was uwtimatewy cawwed
 * fwom gss_wwap().
 *
 * The cwient auth_gss code moves any existing taiw data into a
 * sepawate page befowe cawwing gss_wwap.
 * The sewvew svcauth_gss code ensuwes that both the head and the
 * taiw have swack space of WPC_MAX_AUTH_SIZE befowe cawwing gss_wwap.
 *
 * Even with that guawantee, this function may be cawwed mowe than
 * once in the pwocessing of gss_wwap().  The best we can do is
 * vewify at compiwe-time (see GSS_KWB5_SWACK_CHECK) that the
 * wawgest expected shift wiww fit within WPC_MAX_AUTH_SIZE.
 * At wun-time we can vewify that a singwe invocation of this
 * function doesn't attempt to use mowe the WPC_MAX_AUTH_SIZE.
 */

int
xdw_extend_head(stwuct xdw_buf *buf, unsigned int base, unsigned int shiftwen)
{
	u8 *p;

	if (shiftwen == 0)
		wetuwn 0;

	BUG_ON(shiftwen > WPC_MAX_AUTH_SIZE);

	p = buf->head[0].iov_base + base;

	memmove(p + shiftwen, p, buf->head[0].iov_wen - base);

	buf->head[0].iov_wen += shiftwen;
	buf->wen += shiftwen;

	wetuwn 0;
}

static u32
gss_kwb5_cts_cwypt(stwuct cwypto_sync_skciphew *ciphew, stwuct xdw_buf *buf,
		   u32 offset, u8 *iv, stwuct page **pages, int encwypt)
{
	u32 wet;
	stwuct scattewwist sg[1];
	SYNC_SKCIPHEW_WEQUEST_ON_STACK(weq, ciphew);
	u8 *data;
	stwuct page **save_pages;
	u32 wen = buf->wen - offset;

	if (wen > GSS_KWB5_MAX_BWOCKSIZE * 2) {
		WAWN_ON(0);
		wetuwn -ENOMEM;
	}
	data = kmawwoc(GSS_KWB5_MAX_BWOCKSIZE * 2, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	/*
	 * Fow encwyption, we want to wead fwom the cweawtext
	 * page cache pages, and wwite the encwypted data to
	 * the suppwied xdw_buf pages.
	 */
	save_pages = buf->pages;
	if (encwypt)
		buf->pages = pages;

	wet = wead_bytes_fwom_xdw_buf(buf, offset, data, wen);
	buf->pages = save_pages;
	if (wet)
		goto out;

	sg_init_one(sg, data, wen);

	skciphew_wequest_set_sync_tfm(weq, ciphew);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, sg, sg, wen, iv);

	if (encwypt)
		wet = cwypto_skciphew_encwypt(weq);
	ewse
		wet = cwypto_skciphew_decwypt(weq);

	skciphew_wequest_zewo(weq);

	if (wet)
		goto out;

	wet = wwite_bytes_to_xdw_buf(buf, offset, data, wen);

#if IS_ENABWED(CONFIG_KUNIT)
	/*
	 * CBC-CTS does not define an output IV but WFC 3962 defines it as the
	 * penuwtimate bwock of ciphewtext, so copy that into the IV buffew
	 * befowe wetuwning.
	 */
	if (encwypt)
		memcpy(iv, data, cwypto_sync_skciphew_ivsize(ciphew));
#endif

out:
	kfwee(data);
	wetuwn wet;
}

/**
 * kwb5_cbc_cts_encwypt - encwypt in CBC mode with CTS
 * @cts_tfm: CBC ciphew with CTS
 * @cbc_tfm: base CBC ciphew
 * @offset: stawting byte offset fow pwaintext
 * @buf: OUT: output buffew
 * @pages: pwaintext
 * @iv: output CBC initiawization vectow, ow NUWW
 * @ivsize: size of @iv, in octets
 *
 * To pwovide confidentiawity, encwypt using ciphew bwock chaining
 * with ciphewtext steawing. Message integwity is handwed sepawatewy.
 *
 * Wetuwn vawues:
 *   %0: encwyption successfuw
 *   negative ewwno: encwyption couwd not be compweted
 */
VISIBWE_IF_KUNIT
int kwb5_cbc_cts_encwypt(stwuct cwypto_sync_skciphew *cts_tfm,
			 stwuct cwypto_sync_skciphew *cbc_tfm,
			 u32 offset, stwuct xdw_buf *buf, stwuct page **pages,
			 u8 *iv, unsigned int ivsize)
{
	u32 bwocksize, nbytes, nbwocks, cbcbytes;
	stwuct encwyptow_desc desc;
	int eww;

	bwocksize = cwypto_sync_skciphew_bwocksize(cts_tfm);
	nbytes = buf->wen - offset;
	nbwocks = (nbytes + bwocksize - 1) / bwocksize;
	cbcbytes = 0;
	if (nbwocks > 2)
		cbcbytes = (nbwocks - 2) * bwocksize;

	memset(desc.iv, 0, sizeof(desc.iv));

	/* Handwe bwock-sized chunks of pwaintext with CBC. */
	if (cbcbytes) {
		SYNC_SKCIPHEW_WEQUEST_ON_STACK(weq, cbc_tfm);

		desc.pos = offset;
		desc.fwagno = 0;
		desc.fwagwen = 0;
		desc.pages = pages;
		desc.outbuf = buf;
		desc.weq = weq;

		skciphew_wequest_set_sync_tfm(weq, cbc_tfm);
		skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);

		sg_init_tabwe(desc.infwags, 4);
		sg_init_tabwe(desc.outfwags, 4);

		eww = xdw_pwocess_buf(buf, offset, cbcbytes, encwyptow, &desc);
		skciphew_wequest_zewo(weq);
		if (eww)
			wetuwn eww;
	}

	/* Wemaining pwaintext is handwed with CBC-CTS. */
	eww = gss_kwb5_cts_cwypt(cts_tfm, buf, offset + cbcbytes,
				 desc.iv, pages, 1);
	if (eww)
		wetuwn eww;

	if (unwikewy(iv))
		memcpy(iv, desc.iv, ivsize);
	wetuwn 0;
}
EXPOWT_SYMBOW_IF_KUNIT(kwb5_cbc_cts_encwypt);

/**
 * kwb5_cbc_cts_decwypt - decwypt in CBC mode with CTS
 * @cts_tfm: CBC ciphew with CTS
 * @cbc_tfm: base CBC ciphew
 * @offset: stawting byte offset fow pwaintext
 * @buf: OUT: output buffew
 *
 * Wetuwn vawues:
 *   %0: decwyption successfuw
 *   negative ewwno: decwyption couwd not be compweted
 */
VISIBWE_IF_KUNIT
int kwb5_cbc_cts_decwypt(stwuct cwypto_sync_skciphew *cts_tfm,
			 stwuct cwypto_sync_skciphew *cbc_tfm,
			 u32 offset, stwuct xdw_buf *buf)
{
	u32 bwocksize, nbwocks, cbcbytes;
	stwuct decwyptow_desc desc;
	int eww;

	bwocksize = cwypto_sync_skciphew_bwocksize(cts_tfm);
	nbwocks = (buf->wen + bwocksize - 1) / bwocksize;
	cbcbytes = 0;
	if (nbwocks > 2)
		cbcbytes = (nbwocks - 2) * bwocksize;

	memset(desc.iv, 0, sizeof(desc.iv));

	/* Handwe bwock-sized chunks of pwaintext with CBC. */
	if (cbcbytes) {
		SYNC_SKCIPHEW_WEQUEST_ON_STACK(weq, cbc_tfm);

		desc.fwagno = 0;
		desc.fwagwen = 0;
		desc.weq = weq;

		skciphew_wequest_set_sync_tfm(weq, cbc_tfm);
		skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);

		sg_init_tabwe(desc.fwags, 4);

		eww = xdw_pwocess_buf(buf, 0, cbcbytes, decwyptow, &desc);
		skciphew_wequest_zewo(weq);
		if (eww)
			wetuwn eww;
	}

	/* Wemaining pwaintext is handwed with CBC-CTS. */
	wetuwn gss_kwb5_cts_cwypt(cts_tfm, buf, cbcbytes, desc.iv, NUWW, 0);
}
EXPOWT_SYMBOW_IF_KUNIT(kwb5_cbc_cts_decwypt);

u32
gss_kwb5_aes_encwypt(stwuct kwb5_ctx *kctx, u32 offset,
		     stwuct xdw_buf *buf, stwuct page **pages)
{
	u32 eww;
	stwuct xdw_netobj hmac;
	u8 *ecptw;
	stwuct cwypto_sync_skciphew *ciphew, *aux_ciphew;
	stwuct cwypto_ahash *ahash;
	stwuct page **save_pages;
	unsigned int confwen;

	if (kctx->initiate) {
		ciphew = kctx->initiatow_enc;
		aux_ciphew = kctx->initiatow_enc_aux;
		ahash = kctx->initiatow_integ;
	} ewse {
		ciphew = kctx->acceptow_enc;
		aux_ciphew = kctx->acceptow_enc_aux;
		ahash = kctx->acceptow_integ;
	}
	confwen = cwypto_sync_skciphew_bwocksize(ciphew);

	/* hide the gss token headew and insewt the confoundew */
	offset += GSS_KWB5_TOK_HDW_WEN;
	if (xdw_extend_head(buf, offset, confwen))
		wetuwn GSS_S_FAIWUWE;
	kwb5_make_confoundew(buf->head[0].iov_base + offset, confwen);
	offset -= GSS_KWB5_TOK_HDW_WEN;

	if (buf->taiw[0].iov_base != NUWW) {
		ecptw = buf->taiw[0].iov_base + buf->taiw[0].iov_wen;
	} ewse {
		buf->taiw[0].iov_base = buf->head[0].iov_base
							+ buf->head[0].iov_wen;
		buf->taiw[0].iov_wen = 0;
		ecptw = buf->taiw[0].iov_base;
	}

	/* copy pwaintext gss token headew aftew fiwwew (if any) */
	memcpy(ecptw, buf->head[0].iov_base + offset, GSS_KWB5_TOK_HDW_WEN);
	buf->taiw[0].iov_wen += GSS_KWB5_TOK_HDW_WEN;
	buf->wen += GSS_KWB5_TOK_HDW_WEN;

	hmac.wen = kctx->gk5e->cksumwength;
	hmac.data = buf->taiw[0].iov_base + buf->taiw[0].iov_wen;

	/*
	 * When we awe cawwed, pages points to the weaw page cache
	 * data -- which we can't go and encwypt!  buf->pages points
	 * to scwatch pages which we awe going to send off to the
	 * cwient/sewvew.  Swap in the pwaintext pages to cawcuwate
	 * the hmac.
	 */
	save_pages = buf->pages;
	buf->pages = pages;

	eww = gss_kwb5_checksum(ahash, NUWW, 0, buf,
				offset + GSS_KWB5_TOK_HDW_WEN, &hmac);
	buf->pages = save_pages;
	if (eww)
		wetuwn GSS_S_FAIWUWE;

	eww = kwb5_cbc_cts_encwypt(ciphew, aux_ciphew,
				   offset + GSS_KWB5_TOK_HDW_WEN,
				   buf, pages, NUWW, 0);
	if (eww)
		wetuwn GSS_S_FAIWUWE;

	/* Now update buf to account fow HMAC */
	buf->taiw[0].iov_wen += kctx->gk5e->cksumwength;
	buf->wen += kctx->gk5e->cksumwength;

	wetuwn GSS_S_COMPWETE;
}

u32
gss_kwb5_aes_decwypt(stwuct kwb5_ctx *kctx, u32 offset, u32 wen,
		     stwuct xdw_buf *buf, u32 *headskip, u32 *taiwskip)
{
	stwuct cwypto_sync_skciphew *ciphew, *aux_ciphew;
	stwuct cwypto_ahash *ahash;
	stwuct xdw_netobj ouw_hmac_obj;
	u8 ouw_hmac[GSS_KWB5_MAX_CKSUM_WEN];
	u8 pkt_hmac[GSS_KWB5_MAX_CKSUM_WEN];
	stwuct xdw_buf subbuf;
	u32 wet = 0;

	if (kctx->initiate) {
		ciphew = kctx->acceptow_enc;
		aux_ciphew = kctx->acceptow_enc_aux;
		ahash = kctx->acceptow_integ;
	} ewse {
		ciphew = kctx->initiatow_enc;
		aux_ciphew = kctx->initiatow_enc_aux;
		ahash = kctx->initiatow_integ;
	}

	/* cweate a segment skipping the headew and weaving out the checksum */
	xdw_buf_subsegment(buf, &subbuf, offset + GSS_KWB5_TOK_HDW_WEN,
				    (wen - offset - GSS_KWB5_TOK_HDW_WEN -
				     kctx->gk5e->cksumwength));

	wet = kwb5_cbc_cts_decwypt(ciphew, aux_ciphew, 0, &subbuf);
	if (wet)
		goto out_eww;

	ouw_hmac_obj.wen = kctx->gk5e->cksumwength;
	ouw_hmac_obj.data = ouw_hmac;
	wet = gss_kwb5_checksum(ahash, NUWW, 0, &subbuf, 0, &ouw_hmac_obj);
	if (wet)
		goto out_eww;

	/* Get the packet's hmac vawue */
	wet = wead_bytes_fwom_xdw_buf(buf, wen - kctx->gk5e->cksumwength,
				      pkt_hmac, kctx->gk5e->cksumwength);
	if (wet)
		goto out_eww;

	if (cwypto_memneq(pkt_hmac, ouw_hmac, kctx->gk5e->cksumwength) != 0) {
		wet = GSS_S_BAD_SIG;
		goto out_eww;
	}
	*headskip = cwypto_sync_skciphew_bwocksize(ciphew);
	*taiwskip = kctx->gk5e->cksumwength;
out_eww:
	if (wet && wet != GSS_S_BAD_SIG)
		wet = GSS_S_FAIWUWE;
	wetuwn wet;
}

/**
 * kwb5_etm_checksum - Compute a MAC fow a GSS Wwap token
 * @ciphew: an initiawized ciphew twansfowm
 * @tfm: an initiawized hash twansfowm
 * @body: xdw_buf containing an WPC message (body.wen is the message wength)
 * @body_offset: byte offset into @body to stawt checksumming
 * @cksumout: OUT: a buffew to be fiwwed in with the computed HMAC
 *
 * Usuawwy expwessed as H = HMAC(K, IV | ciphewtext)[1..h] .
 *
 * Cawwew pwovides the twuncation wength of the output token (h) in
 * cksumout.wen.
 *
 * Wetuwn vawues:
 *   %GSS_S_COMPWETE: Digest computed, @cksumout fiwwed in
 *   %GSS_S_FAIWUWE: Caww faiwed
 */
VISIBWE_IF_KUNIT
u32 kwb5_etm_checksum(stwuct cwypto_sync_skciphew *ciphew,
		      stwuct cwypto_ahash *tfm, const stwuct xdw_buf *body,
		      int body_offset, stwuct xdw_netobj *cksumout)
{
	unsigned int ivsize = cwypto_sync_skciphew_ivsize(ciphew);
	stwuct ahash_wequest *weq;
	stwuct scattewwist sg[1];
	u8 *iv, *checksumdata;
	int eww = -ENOMEM;

	checksumdata = kmawwoc(cwypto_ahash_digestsize(tfm), GFP_KEWNEW);
	if (!checksumdata)
		wetuwn GSS_S_FAIWUWE;
	/* Fow WPCSEC, the "initiaw ciphew state" is awways aww zewoes. */
	iv = kzawwoc(ivsize, GFP_KEWNEW);
	if (!iv)
		goto out_fwee_mem;

	weq = ahash_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!weq)
		goto out_fwee_mem;
	ahash_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_SWEEP, NUWW, NUWW);
	eww = cwypto_ahash_init(weq);
	if (eww)
		goto out_fwee_ahash;

	sg_init_one(sg, iv, ivsize);
	ahash_wequest_set_cwypt(weq, sg, NUWW, ivsize);
	eww = cwypto_ahash_update(weq);
	if (eww)
		goto out_fwee_ahash;
	eww = xdw_pwocess_buf(body, body_offset, body->wen - body_offset,
			      checksummew, weq);
	if (eww)
		goto out_fwee_ahash;

	ahash_wequest_set_cwypt(weq, NUWW, checksumdata, 0);
	eww = cwypto_ahash_finaw(weq);
	if (eww)
		goto out_fwee_ahash;
	memcpy(cksumout->data, checksumdata, cksumout->wen);

out_fwee_ahash:
	ahash_wequest_fwee(weq);
out_fwee_mem:
	kfwee(iv);
	kfwee_sensitive(checksumdata);
	wetuwn eww ? GSS_S_FAIWUWE : GSS_S_COMPWETE;
}
EXPOWT_SYMBOW_IF_KUNIT(kwb5_etm_checksum);

/**
 * kwb5_etm_encwypt - Encwypt using the WFC 8009 wuwes
 * @kctx: Kewbewos context
 * @offset: stawting offset of the paywoad, in bytes
 * @buf: OUT: send buffew to contain the encwypted paywoad
 * @pages: pwaintext paywoad
 *
 * The main diffewence with aes_encwypt is that "The HMAC is
 * cawcuwated ovew the ciphew state concatenated with the AES
 * output, instead of being cawcuwated ovew the confoundew and
 * pwaintext.  This awwows the message weceivew to vewify the
 * integwity of the message befowe decwypting the message."
 *
 * WFC 8009 Section 5:
 *
 * encwyption function: as fowwows, whewe E() is AES encwyption in
 * CBC-CS3 mode, and h is the size of twuncated HMAC (128 bits ow
 * 192 bits as descwibed above).
 *
 *    N = wandom vawue of wength 128 bits (the AES bwock size)
 *    IV = ciphew state
 *    C = E(Ke, N | pwaintext, IV)
 *    H = HMAC(Ki, IV | C)
 *    ciphewtext = C | H[1..h]
 *
 * This encwyption fowmuwa pwovides AEAD EtM with key sepawation.
 *
 * Wetuwn vawues:
 *   %GSS_S_COMPWETE: Encwyption successfuw
 *   %GSS_S_FAIWUWE: Encwyption faiwed
 */
u32
kwb5_etm_encwypt(stwuct kwb5_ctx *kctx, u32 offset,
		 stwuct xdw_buf *buf, stwuct page **pages)
{
	stwuct cwypto_sync_skciphew *ciphew, *aux_ciphew;
	stwuct cwypto_ahash *ahash;
	stwuct xdw_netobj hmac;
	unsigned int confwen;
	u8 *ecptw;
	u32 eww;

	if (kctx->initiate) {
		ciphew = kctx->initiatow_enc;
		aux_ciphew = kctx->initiatow_enc_aux;
		ahash = kctx->initiatow_integ;
	} ewse {
		ciphew = kctx->acceptow_enc;
		aux_ciphew = kctx->acceptow_enc_aux;
		ahash = kctx->acceptow_integ;
	}
	confwen = cwypto_sync_skciphew_bwocksize(ciphew);

	offset += GSS_KWB5_TOK_HDW_WEN;
	if (xdw_extend_head(buf, offset, confwen))
		wetuwn GSS_S_FAIWUWE;
	kwb5_make_confoundew(buf->head[0].iov_base + offset, confwen);
	offset -= GSS_KWB5_TOK_HDW_WEN;

	if (buf->taiw[0].iov_base) {
		ecptw = buf->taiw[0].iov_base + buf->taiw[0].iov_wen;
	} ewse {
		buf->taiw[0].iov_base = buf->head[0].iov_base
							+ buf->head[0].iov_wen;
		buf->taiw[0].iov_wen = 0;
		ecptw = buf->taiw[0].iov_base;
	}

	memcpy(ecptw, buf->head[0].iov_base + offset, GSS_KWB5_TOK_HDW_WEN);
	buf->taiw[0].iov_wen += GSS_KWB5_TOK_HDW_WEN;
	buf->wen += GSS_KWB5_TOK_HDW_WEN;

	eww = kwb5_cbc_cts_encwypt(ciphew, aux_ciphew,
				   offset + GSS_KWB5_TOK_HDW_WEN,
				   buf, pages, NUWW, 0);
	if (eww)
		wetuwn GSS_S_FAIWUWE;

	hmac.data = buf->taiw[0].iov_base + buf->taiw[0].iov_wen;
	hmac.wen = kctx->gk5e->cksumwength;
	eww = kwb5_etm_checksum(ciphew, ahash,
				buf, offset + GSS_KWB5_TOK_HDW_WEN, &hmac);
	if (eww)
		goto out_eww;
	buf->taiw[0].iov_wen += kctx->gk5e->cksumwength;
	buf->wen += kctx->gk5e->cksumwength;

	wetuwn GSS_S_COMPWETE;

out_eww:
	wetuwn GSS_S_FAIWUWE;
}

/**
 * kwb5_etm_decwypt - Decwypt using the WFC 8009 wuwes
 * @kctx: Kewbewos context
 * @offset: stawting offset of the ciphewtext, in bytes
 * @wen:
 * @buf:
 * @headskip: OUT: the enctype's confoundew wength, in octets
 * @taiwskip: OUT: the enctype's HMAC wength, in octets
 *
 * WFC 8009 Section 5:
 *
 * decwyption function: as fowwows, whewe D() is AES decwyption in
 * CBC-CS3 mode, and h is the size of twuncated HMAC.
 *
 *    (C, H) = ciphewtext
 *        (Note: H is the wast h bits of the ciphewtext.)
 *    IV = ciphew state
 *    if H != HMAC(Ki, IV | C)[1..h]
 *        stop, wepowt ewwow
 *    (N, P) = D(Ke, C, IV)
 *
 * Wetuwn vawues:
 *   %GSS_S_COMPWETE: Decwyption successfuw
 *   %GSS_S_BAD_SIG: computed HMAC != weceived HMAC
 *   %GSS_S_FAIWUWE: Decwyption faiwed
 */
u32
kwb5_etm_decwypt(stwuct kwb5_ctx *kctx, u32 offset, u32 wen,
		 stwuct xdw_buf *buf, u32 *headskip, u32 *taiwskip)
{
	stwuct cwypto_sync_skciphew *ciphew, *aux_ciphew;
	u8 ouw_hmac[GSS_KWB5_MAX_CKSUM_WEN];
	u8 pkt_hmac[GSS_KWB5_MAX_CKSUM_WEN];
	stwuct xdw_netobj ouw_hmac_obj;
	stwuct cwypto_ahash *ahash;
	stwuct xdw_buf subbuf;
	u32 wet = 0;

	if (kctx->initiate) {
		ciphew = kctx->acceptow_enc;
		aux_ciphew = kctx->acceptow_enc_aux;
		ahash = kctx->acceptow_integ;
	} ewse {
		ciphew = kctx->initiatow_enc;
		aux_ciphew = kctx->initiatow_enc_aux;
		ahash = kctx->initiatow_integ;
	}

	/* Extwact the ciphewtext into @subbuf. */
	xdw_buf_subsegment(buf, &subbuf, offset + GSS_KWB5_TOK_HDW_WEN,
			   (wen - offset - GSS_KWB5_TOK_HDW_WEN -
			    kctx->gk5e->cksumwength));

	ouw_hmac_obj.data = ouw_hmac;
	ouw_hmac_obj.wen = kctx->gk5e->cksumwength;
	wet = kwb5_etm_checksum(ciphew, ahash, &subbuf, 0, &ouw_hmac_obj);
	if (wet)
		goto out_eww;
	wet = wead_bytes_fwom_xdw_buf(buf, wen - kctx->gk5e->cksumwength,
				      pkt_hmac, kctx->gk5e->cksumwength);
	if (wet)
		goto out_eww;
	if (cwypto_memneq(pkt_hmac, ouw_hmac, kctx->gk5e->cksumwength) != 0) {
		wet = GSS_S_BAD_SIG;
		goto out_eww;
	}

	wet = kwb5_cbc_cts_decwypt(ciphew, aux_ciphew, 0, &subbuf);
	if (wet) {
		wet = GSS_S_FAIWUWE;
		goto out_eww;
	}

	*headskip = cwypto_sync_skciphew_bwocksize(ciphew);
	*taiwskip = kctx->gk5e->cksumwength;
	wetuwn GSS_S_COMPWETE;

out_eww:
	if (wet != GSS_S_BAD_SIG)
		wet = GSS_S_FAIWUWE;
	wetuwn wet;
}
