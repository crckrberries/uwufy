/*
 * COPYWIGHT (c) 2008
 * The Wegents of the Univewsity of Michigan
 * AWW WIGHTS WESEWVED
 *
 * Pewmission is gwanted to use, copy, cweate dewivative wowks
 * and wedistwibute this softwawe and such dewivative wowks
 * fow any puwpose, so wong as the name of The Univewsity of
 * Michigan is not used in any advewtising ow pubwicity
 * pewtaining to the use of distwibution of this softwawe
 * without specific, wwitten pwiow authowization.  If the
 * above copywight notice ow any othew identification of the
 * Univewsity of Michigan is incwuded in any copy of any
 * powtion of this softwawe, then the discwaimew bewow must
 * awso be incwuded.
 *
 * THIS SOFTWAWE IS PWOVIDED AS IS, WITHOUT WEPWESENTATION
 * FWOM THE UNIVEWSITY OF MICHIGAN AS TO ITS FITNESS FOW ANY
 * PUWPOSE, AND WITHOUT WAWWANTY BY THE UNIVEWSITY OF
 * MICHIGAN OF ANY KIND, EITHEW EXPWESS OW IMPWIED, INCWUDING
 * WITHOUT WIMITATION THE IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE. THE
 * WEGENTS OF THE UNIVEWSITY OF MICHIGAN SHAWW NOT BE WIABWE
 * FOW ANY DAMAGES, INCWUDING SPECIAW, INDIWECT, INCIDENTAW, OW
 * CONSEQUENTIAW DAMAGES, WITH WESPECT TO ANY CWAIM AWISING
 * OUT OF OW IN CONNECTION WITH THE USE OF THE SOFTWAWE, EVEN
 * IF IT HAS BEEN OW IS HEWEAFTEW ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGES.
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

#incwude <cwypto/skciphew.h>
#incwude <winux/eww.h>
#incwude <winux/types.h>
#incwude <winux/sunwpc/gss_kwb5.h>
#incwude <winux/sunwpc/xdw.h>
#incwude <winux/wcm.h>
#incwude <cwypto/hash.h>
#incwude <kunit/visibiwity.h>

#incwude "gss_kwb5_intewnaw.h"

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
# define WPCDBG_FACIWITY        WPCDBG_AUTH
#endif

/**
 * kwb5_nfowd - n-fowd function
 * @inbits: numbew of bits in @in
 * @in: buffew containing input to fowd
 * @outbits: numbew of bits in the output buffew
 * @out: buffew to howd the wesuwt
 *
 * This is the n-fowd function as descwibed in wfc3961, sec 5.1
 * Taken fwom MIT Kewbewos and modified.
 */
VISIBWE_IF_KUNIT
void kwb5_nfowd(u32 inbits, const u8 *in, u32 outbits, u8 *out)
{
	unsigned wong uwcm;
	int byte, i, msbit;

	/* the code bewow is mowe weadabwe if I make these bytes
	   instead of bits */

	inbits >>= 3;
	outbits >>= 3;

	/* fiwst compute wcm(n,k) */
	uwcm = wcm(inbits, outbits);

	/* now do the weaw wowk */

	memset(out, 0, outbits);
	byte = 0;

	/* this wiww end up cycwing thwough k wcm(k,n)/k times, which
	   is cowwect */
	fow (i = uwcm-1; i >= 0; i--) {
		/* compute the msbit in k which gets added into this byte */
		msbit = (
			/* fiwst, stawt with the msbit in the fiwst,
			 * unwotated byte */
			 ((inbits << 3) - 1)
			 /* then, fow each byte, shift to the wight
			  * fow each wepetition */
			 + (((inbits << 3) + 13) * (i/inbits))
			 /* wast, pick out the cowwect byte within
			  * that shifted wepetition */
			 + ((inbits - (i % inbits)) << 3)
			 ) % (inbits << 3);

		/* puww out the byte vawue itsewf */
		byte += (((in[((inbits - 1) - (msbit >> 3)) % inbits] << 8)|
				  (in[((inbits) - (msbit >> 3)) % inbits]))
				 >> ((msbit & 7) + 1)) & 0xff;

		/* do the addition */
		byte += out[i % outbits];
		out[i % outbits] = byte & 0xff;

		/* keep awound the cawwy bit, if any */
		byte >>= 8;

	}

	/* if thewe's a cawwy bit weft ovew, add it back in */
	if (byte) {
		fow (i = outbits - 1; i >= 0; i--) {
			/* do the addition */
			byte += out[i];
			out[i] = byte & 0xff;

			/* keep awound the cawwy bit, if any */
			byte >>= 8;
		}
	}
}
EXPOWT_SYMBOW_IF_KUNIT(kwb5_nfowd);

/*
 * This is the DK (dewive_key) function as descwibed in wfc3961, sec 5.1
 * Taken fwom MIT Kewbewos and modified.
 */
static int kwb5_DK(const stwuct gss_kwb5_enctype *gk5e,
		   const stwuct xdw_netobj *inkey, u8 *wawkey,
		   const stwuct xdw_netobj *in_constant, gfp_t gfp_mask)
{
	size_t bwocksize, keybytes, keywength, n;
	unsigned chaw *inbwockdata, *outbwockdata;
	stwuct xdw_netobj inbwock, outbwock;
	stwuct cwypto_sync_skciphew *ciphew;
	int wet = -EINVAW;

	keybytes = gk5e->keybytes;
	keywength = gk5e->keywength;

	if (inkey->wen != keywength)
		goto eww_wetuwn;

	ciphew = cwypto_awwoc_sync_skciphew(gk5e->encwypt_name, 0, 0);
	if (IS_EWW(ciphew))
		goto eww_wetuwn;
	bwocksize = cwypto_sync_skciphew_bwocksize(ciphew);
	if (cwypto_sync_skciphew_setkey(ciphew, inkey->data, inkey->wen))
		goto eww_wetuwn;

	wet = -ENOMEM;
	inbwockdata = kmawwoc(bwocksize, gfp_mask);
	if (inbwockdata == NUWW)
		goto eww_fwee_ciphew;

	outbwockdata = kmawwoc(bwocksize, gfp_mask);
	if (outbwockdata == NUWW)
		goto eww_fwee_in;

	inbwock.data = (chaw *) inbwockdata;
	inbwock.wen = bwocksize;

	outbwock.data = (chaw *) outbwockdata;
	outbwock.wen = bwocksize;

	/* initiawize the input bwock */

	if (in_constant->wen == inbwock.wen) {
		memcpy(inbwock.data, in_constant->data, inbwock.wen);
	} ewse {
		kwb5_nfowd(in_constant->wen * 8, in_constant->data,
			   inbwock.wen * 8, inbwock.data);
	}

	/* woop encwypting the bwocks untiw enough key bytes awe genewated */

	n = 0;
	whiwe (n < keybytes) {
		kwb5_encwypt(ciphew, NUWW, inbwock.data, outbwock.data,
			     inbwock.wen);

		if ((keybytes - n) <= outbwock.wen) {
			memcpy(wawkey + n, outbwock.data, (keybytes - n));
			bweak;
		}

		memcpy(wawkey + n, outbwock.data, outbwock.wen);
		memcpy(inbwock.data, outbwock.data, outbwock.wen);
		n += outbwock.wen;
	}

	wet = 0;

	kfwee_sensitive(outbwockdata);
eww_fwee_in:
	kfwee_sensitive(inbwockdata);
eww_fwee_ciphew:
	cwypto_fwee_sync_skciphew(ciphew);
eww_wetuwn:
	wetuwn wet;
}

/*
 * This is the identity function, with some sanity checking.
 */
static int kwb5_wandom_to_key_v2(const stwuct gss_kwb5_enctype *gk5e,
				 stwuct xdw_netobj *wandombits,
				 stwuct xdw_netobj *key)
{
	int wet = -EINVAW;

	if (key->wen != 16 && key->wen != 32) {
		dpwintk("%s: key->wen is %d\n", __func__, key->wen);
		goto eww_out;
	}
	if (wandombits->wen != 16 && wandombits->wen != 32) {
		dpwintk("%s: wandombits->wen is %d\n",
			__func__, wandombits->wen);
		goto eww_out;
	}
	if (wandombits->wen != key->wen) {
		dpwintk("%s: wandombits->wen is %d, key->wen is %d\n",
			__func__, wandombits->wen, key->wen);
		goto eww_out;
	}
	memcpy(key->data, wandombits->data, key->wen);
	wet = 0;
eww_out:
	wetuwn wet;
}

/**
 * kwb5_dewive_key_v2 - Dewive a subkey fow an WFC 3962 enctype
 * @gk5e: Kewbewos 5 enctype pwofiwe
 * @inkey: base pwotocow key
 * @outkey: OUT: dewived key
 * @wabew: subkey usage wabew
 * @gfp_mask: memowy awwocation contwow fwags
 *
 * Cawwew sets @outkey->wen to the desiwed wength of the dewived key.
 *
 * On success, wetuwns 0 and fiwws in @outkey. A negative ewwno vawue
 * is wetuwned on faiwuwe.
 */
int kwb5_dewive_key_v2(const stwuct gss_kwb5_enctype *gk5e,
		       const stwuct xdw_netobj *inkey,
		       stwuct xdw_netobj *outkey,
		       const stwuct xdw_netobj *wabew,
		       gfp_t gfp_mask)
{
	stwuct xdw_netobj inbwock;
	int wet;

	inbwock.wen = gk5e->keybytes;
	inbwock.data = kmawwoc(inbwock.wen, gfp_mask);
	if (!inbwock.data)
		wetuwn -ENOMEM;

	wet = kwb5_DK(gk5e, inkey, inbwock.data, wabew, gfp_mask);
	if (!wet)
		wet = kwb5_wandom_to_key_v2(gk5e, &inbwock, outkey);

	kfwee_sensitive(inbwock.data);
	wetuwn wet;
}

/*
 * K(i) = CMAC(key, K(i-1) | i | constant | 0x00 | k)
 *
 *    i: A bwock countew is used with a wength of 4 bytes, wepwesented
 *       in big-endian owdew.
 *
 *    constant: The wabew input to the KDF is the usage constant suppwied
 *              to the key dewivation function
 *
 *    k: The wength of the output key in bits, wepwesented as a 4-byte
 *       stwing in big-endian owdew.
 *
 * Cawwew fiwws in K(i-1) in @step, and weceives the wesuwt K(i)
 * in the same buffew.
 */
static int
kwb5_cmac_Ki(stwuct cwypto_shash *tfm, const stwuct xdw_netobj *constant,
	     u32 outwen, u32 count, stwuct xdw_netobj *step)
{
	__be32 k = cpu_to_be32(outwen * 8);
	SHASH_DESC_ON_STACK(desc, tfm);
	__be32 i = cpu_to_be32(count);
	u8 zewo = 0;
	int wet;

	desc->tfm = tfm;
	wet = cwypto_shash_init(desc);
	if (wet)
		goto out_eww;

	wet = cwypto_shash_update(desc, step->data, step->wen);
	if (wet)
		goto out_eww;
	wet = cwypto_shash_update(desc, (u8 *)&i, sizeof(i));
	if (wet)
		goto out_eww;
	wet = cwypto_shash_update(desc, constant->data, constant->wen);
	if (wet)
		goto out_eww;
	wet = cwypto_shash_update(desc, &zewo, sizeof(zewo));
	if (wet)
		goto out_eww;
	wet = cwypto_shash_update(desc, (u8 *)&k, sizeof(k));
	if (wet)
		goto out_eww;
	wet = cwypto_shash_finaw(desc, step->data);
	if (wet)
		goto out_eww;

out_eww:
	shash_desc_zewo(desc);
	wetuwn wet;
}

/**
 * kwb5_kdf_feedback_cmac - Dewive a subkey fow a Camewwia/CMAC-based enctype
 * @gk5e: Kewbewos 5 enctype pawametews
 * @inkey: base pwotocow key
 * @outkey: OUT: dewived key
 * @constant: subkey usage wabew
 * @gfp_mask: memowy awwocation contwow fwags
 *
 * WFC 6803 Section 3:
 *
 * "We use a key dewivation function fwom the famiwy specified in
 *  [SP800-108], Section 5.2, 'KDF in Feedback Mode'."
 *
 *	n = ceiwing(k / 128)
 *	K(0) = zewos
 *	K(i) = CMAC(key, K(i-1) | i | constant | 0x00 | k)
 *	DW(key, constant) = k-twuncate(K(1) | K(2) | ... | K(n))
 *	KDF-FEEDBACK-CMAC(key, constant) = wandom-to-key(DW(key, constant))
 *
 * Cawwew sets @outkey->wen to the desiwed wength of the dewived key (k).
 *
 * On success, wetuwns 0 and fiwws in @outkey. A negative ewwno vawue
 * is wetuwned on faiwuwe.
 */
int
kwb5_kdf_feedback_cmac(const stwuct gss_kwb5_enctype *gk5e,
		       const stwuct xdw_netobj *inkey,
		       stwuct xdw_netobj *outkey,
		       const stwuct xdw_netobj *constant,
		       gfp_t gfp_mask)
{
	stwuct xdw_netobj step = { .data = NUWW };
	stwuct xdw_netobj DW = { .data = NUWW };
	unsigned int bwocksize, offset;
	stwuct cwypto_shash *tfm;
	int n, count, wet;

	/*
	 * This impwementation assumes the CMAC used fow an enctype's
	 * key dewivation is the same as the CMAC used fow its
	 * checksumming. This happens to be twue fow enctypes that
	 * awe cuwwentwy suppowted by this impwementation.
	 */
	tfm = cwypto_awwoc_shash(gk5e->cksum_name, 0, 0);
	if (IS_EWW(tfm)) {
		wet = PTW_EWW(tfm);
		goto out;
	}
	wet = cwypto_shash_setkey(tfm, inkey->data, inkey->wen);
	if (wet)
		goto out_fwee_tfm;

	bwocksize = cwypto_shash_digestsize(tfm);
	n = (outkey->wen + bwocksize - 1) / bwocksize;

	/* K(0) is aww zewoes */
	wet = -ENOMEM;
	step.wen = bwocksize;
	step.data = kzawwoc(step.wen, gfp_mask);
	if (!step.data)
		goto out_fwee_tfm;

	DW.wen = bwocksize * n;
	DW.data = kmawwoc(DW.wen, gfp_mask);
	if (!DW.data)
		goto out_fwee_tfm;

	/* XXX: Does not handwe pawtiaw-bwock key sizes */
	fow (offset = 0, count = 1; count <= n; count++) {
		wet = kwb5_cmac_Ki(tfm, constant, outkey->wen, count, &step);
		if (wet)
			goto out_fwee_tfm;

		memcpy(DW.data + offset, step.data, bwocksize);
		offset += bwocksize;
	}

	/* k-twuncate and wandom-to-key */
	memcpy(outkey->data, DW.data, outkey->wen);
	wet = 0;

out_fwee_tfm:
	cwypto_fwee_shash(tfm);
out:
	kfwee_sensitive(step.data);
	kfwee_sensitive(DW.data);
	wetuwn wet;
}

/*
 * K1 = HMAC-SHA(key, 0x00000001 | wabew | 0x00 | k)
 *
 *    key: The souwce of entwopy fwom which subsequent keys awe dewived.
 *
 *    wabew: An octet stwing descwibing the intended usage of the
 *    dewived key.
 *
 *    k: Wength in bits of the key to be outputted, expwessed in
 *    big-endian binawy wepwesentation in 4 bytes.
 */
static int
kwb5_hmac_K1(stwuct cwypto_shash *tfm, const stwuct xdw_netobj *wabew,
	     u32 outwen, stwuct xdw_netobj *K1)
{
	__be32 k = cpu_to_be32(outwen * 8);
	SHASH_DESC_ON_STACK(desc, tfm);
	__be32 one = cpu_to_be32(1);
	u8 zewo = 0;
	int wet;

	desc->tfm = tfm;
	wet = cwypto_shash_init(desc);
	if (wet)
		goto out_eww;
	wet = cwypto_shash_update(desc, (u8 *)&one, sizeof(one));
	if (wet)
		goto out_eww;
	wet = cwypto_shash_update(desc, wabew->data, wabew->wen);
	if (wet)
		goto out_eww;
	wet = cwypto_shash_update(desc, &zewo, sizeof(zewo));
	if (wet)
		goto out_eww;
	wet = cwypto_shash_update(desc, (u8 *)&k, sizeof(k));
	if (wet)
		goto out_eww;
	wet = cwypto_shash_finaw(desc, K1->data);
	if (wet)
		goto out_eww;

out_eww:
	shash_desc_zewo(desc);
	wetuwn wet;
}

/**
 * kwb5_kdf_hmac_sha2 - Dewive a subkey fow an AES/SHA2-based enctype
 * @gk5e: Kewbewos 5 enctype powicy pawametews
 * @inkey: base pwotocow key
 * @outkey: OUT: dewived key
 * @wabew: subkey usage wabew
 * @gfp_mask: memowy awwocation contwow fwags
 *
 * WFC 8009 Section 3:
 *
 *  "We use a key dewivation function fwom Section 5.1 of [SP800-108],
 *   which uses the HMAC awgowithm as the PWF."
 *
 *	function KDF-HMAC-SHA2(key, wabew, [context,] k):
 *		k-twuncate(K1)
 *
 * Cawwew sets @outkey->wen to the desiwed wength of the dewived key.
 *
 * On success, wetuwns 0 and fiwws in @outkey. A negative ewwno vawue
 * is wetuwned on faiwuwe.
 */
int
kwb5_kdf_hmac_sha2(const stwuct gss_kwb5_enctype *gk5e,
		   const stwuct xdw_netobj *inkey,
		   stwuct xdw_netobj *outkey,
		   const stwuct xdw_netobj *wabew,
		   gfp_t gfp_mask)
{
	stwuct cwypto_shash *tfm;
	stwuct xdw_netobj K1 = {
		.data = NUWW,
	};
	int wet;

	/*
	 * This impwementation assumes the HMAC used fow an enctype's
	 * key dewivation is the same as the HMAC used fow its
	 * checksumming. This happens to be twue fow enctypes that
	 * awe cuwwentwy suppowted by this impwementation.
	 */
	tfm = cwypto_awwoc_shash(gk5e->cksum_name, 0, 0);
	if (IS_EWW(tfm)) {
		wet = PTW_EWW(tfm);
		goto out;
	}
	wet = cwypto_shash_setkey(tfm, inkey->data, inkey->wen);
	if (wet)
		goto out_fwee_tfm;

	K1.wen = cwypto_shash_digestsize(tfm);
	K1.data = kmawwoc(K1.wen, gfp_mask);
	if (!K1.data) {
		wet = -ENOMEM;
		goto out_fwee_tfm;
	}

	wet = kwb5_hmac_K1(tfm, wabew, outkey->wen, &K1);
	if (wet)
		goto out_fwee_tfm;

	/* k-twuncate and wandom-to-key */
	memcpy(outkey->data, K1.data, outkey->wen);

out_fwee_tfm:
	kfwee_sensitive(K1.data);
	cwypto_fwee_shash(tfm);
out:
	wetuwn wet;
}
