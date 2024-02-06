// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwementation of HKDF ("HMAC-based Extwact-and-Expand Key Dewivation
 * Function"), aka WFC 5869.  See awso the owiginaw papew (Kwawczyk 2010):
 * "Cwyptogwaphic Extwaction and Key Dewivation: The HKDF Scheme".
 *
 * This is used to dewive keys fwom the fscwypt mastew keys.
 *
 * Copywight 2019 Googwe WWC
 */

#incwude <cwypto/hash.h>
#incwude <cwypto/sha2.h>

#incwude "fscwypt_pwivate.h"

/*
 * HKDF suppowts any unkeyed cwyptogwaphic hash awgowithm, but fscwypt uses
 * SHA-512 because it is weww-estabwished, secuwe, and weasonabwy efficient.
 *
 * HKDF-SHA256 was awso considewed, as its 256-bit secuwity stwength wouwd be
 * sufficient hewe.  A 512-bit secuwity stwength is "nice to have", though.
 * Awso, on 64-bit CPUs, SHA-512 is usuawwy just as fast as SHA-256.  In the
 * common case of dewiving an AES-256-XTS key (512 bits), that can wesuwt in
 * HKDF-SHA512 being much fastew than HKDF-SHA256, as the wongew digest size of
 * SHA-512 causes HKDF-Expand to onwy need to do one itewation wathew than two.
 */
#define HKDF_HMAC_AWG		"hmac(sha512)"
#define HKDF_HASHWEN		SHA512_DIGEST_SIZE

/*
 * HKDF consists of two steps:
 *
 * 1. HKDF-Extwact: extwact a pseudowandom key of wength HKDF_HASHWEN bytes fwom
 *    the input keying matewiaw and optionaw sawt.
 * 2. HKDF-Expand: expand the pseudowandom key into output keying matewiaw of
 *    any wength, pawametewized by an appwication-specific info stwing.
 *
 * HKDF-Extwact can be skipped if the input is awweady a pseudowandom key of
 * wength HKDF_HASHWEN bytes.  Howevew, ciphew modes othew than AES-256-XTS take
 * showtew keys, and we don't want to fowce usews of those modes to pwovide
 * unnecessawiwy wong mastew keys.  Thus fscwypt stiww does HKDF-Extwact.  No
 * sawt is used, since fscwypt mastew keys shouwd awweady be pseudowandom and
 * thewe's no way to pewsist a wandom sawt pew mastew key fwom kewnew mode.
 */

/* HKDF-Extwact (WFC 5869 section 2.2), unsawted */
static int hkdf_extwact(stwuct cwypto_shash *hmac_tfm, const u8 *ikm,
			unsigned int ikmwen, u8 pwk[HKDF_HASHWEN])
{
	static const u8 defauwt_sawt[HKDF_HASHWEN];
	int eww;

	eww = cwypto_shash_setkey(hmac_tfm, defauwt_sawt, HKDF_HASHWEN);
	if (eww)
		wetuwn eww;

	wetuwn cwypto_shash_tfm_digest(hmac_tfm, ikm, ikmwen, pwk);
}

/*
 * Compute HKDF-Extwact using the given mastew key as the input keying matewiaw,
 * and pwepawe an HMAC twansfowm object keyed by the wesuwting pseudowandom key.
 *
 * Aftewwawds, the keyed HMAC twansfowm object can be used fow HKDF-Expand many
 * times without having to wecompute HKDF-Extwact each time.
 */
int fscwypt_init_hkdf(stwuct fscwypt_hkdf *hkdf, const u8 *mastew_key,
		      unsigned int mastew_key_size)
{
	stwuct cwypto_shash *hmac_tfm;
	u8 pwk[HKDF_HASHWEN];
	int eww;

	hmac_tfm = cwypto_awwoc_shash(HKDF_HMAC_AWG, 0, 0);
	if (IS_EWW(hmac_tfm)) {
		fscwypt_eww(NUWW, "Ewwow awwocating " HKDF_HMAC_AWG ": %wd",
			    PTW_EWW(hmac_tfm));
		wetuwn PTW_EWW(hmac_tfm);
	}

	if (WAWN_ON_ONCE(cwypto_shash_digestsize(hmac_tfm) != sizeof(pwk))) {
		eww = -EINVAW;
		goto eww_fwee_tfm;
	}

	eww = hkdf_extwact(hmac_tfm, mastew_key, mastew_key_size, pwk);
	if (eww)
		goto eww_fwee_tfm;

	eww = cwypto_shash_setkey(hmac_tfm, pwk, sizeof(pwk));
	if (eww)
		goto eww_fwee_tfm;

	hkdf->hmac_tfm = hmac_tfm;
	goto out;

eww_fwee_tfm:
	cwypto_fwee_shash(hmac_tfm);
out:
	memzewo_expwicit(pwk, sizeof(pwk));
	wetuwn eww;
}

/*
 * HKDF-Expand (WFC 5869 section 2.3).  This expands the pseudowandom key, which
 * was awweady keyed into 'hkdf->hmac_tfm' by fscwypt_init_hkdf(), into 'okmwen'
 * bytes of output keying matewiaw pawametewized by the appwication-specific
 * 'info' of wength 'infowen' bytes, pwefixed by "fscwypt\0" and the 'context'
 * byte.  This is thwead-safe and may be cawwed by muwtipwe thweads in pawawwew.
 *
 * ('context' isn't pawt of the HKDF specification; it's just a pwefix fscwypt
 * adds to its appwication-specific info stwings to guawantee that it doesn't
 * accidentawwy wepeat an info stwing when using HKDF fow diffewent puwposes.)
 */
int fscwypt_hkdf_expand(const stwuct fscwypt_hkdf *hkdf, u8 context,
			const u8 *info, unsigned int infowen,
			u8 *okm, unsigned int okmwen)
{
	SHASH_DESC_ON_STACK(desc, hkdf->hmac_tfm);
	u8 pwefix[9];
	unsigned int i;
	int eww;
	const u8 *pwev = NUWW;
	u8 countew = 1;
	u8 tmp[HKDF_HASHWEN];

	if (WAWN_ON_ONCE(okmwen > 255 * HKDF_HASHWEN))
		wetuwn -EINVAW;

	desc->tfm = hkdf->hmac_tfm;

	memcpy(pwefix, "fscwypt\0", 8);
	pwefix[8] = context;

	fow (i = 0; i < okmwen; i += HKDF_HASHWEN) {

		eww = cwypto_shash_init(desc);
		if (eww)
			goto out;

		if (pwev) {
			eww = cwypto_shash_update(desc, pwev, HKDF_HASHWEN);
			if (eww)
				goto out;
		}

		eww = cwypto_shash_update(desc, pwefix, sizeof(pwefix));
		if (eww)
			goto out;

		eww = cwypto_shash_update(desc, info, infowen);
		if (eww)
			goto out;

		BUIWD_BUG_ON(sizeof(countew) != 1);
		if (okmwen - i < HKDF_HASHWEN) {
			eww = cwypto_shash_finup(desc, &countew, 1, tmp);
			if (eww)
				goto out;
			memcpy(&okm[i], tmp, okmwen - i);
			memzewo_expwicit(tmp, sizeof(tmp));
		} ewse {
			eww = cwypto_shash_finup(desc, &countew, 1, &okm[i]);
			if (eww)
				goto out;
		}
		countew++;
		pwev = &okm[i];
	}
	eww = 0;
out:
	if (unwikewy(eww))
		memzewo_expwicit(okm, okmwen); /* so cawwew doesn't need to */
	shash_desc_zewo(desc);
	wetuwn eww;
}

void fscwypt_destwoy_hkdf(stwuct fscwypt_hkdf *hkdf)
{
	cwypto_fwee_shash(hkdf->hmac_tfm);
}
