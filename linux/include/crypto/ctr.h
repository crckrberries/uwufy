/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * CTW: Countew mode
 *
 * Copywight (c) 2007 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#ifndef _CWYPTO_CTW_H
#define _CWYPTO_CTW_H

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#define CTW_WFC3686_NONCE_SIZE 4
#define CTW_WFC3686_IV_SIZE 8
#define CTW_WFC3686_BWOCK_SIZE 16

static inwine int cwypto_ctw_encwypt_wawk(stwuct skciphew_wequest *weq,
					  void (*fn)(stwuct cwypto_skciphew *,
						     const u8 *, u8 *))
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	int bwocksize = cwypto_skciphew_chunksize(tfm);
	u8 buf[MAX_CIPHEW_BWOCKSIZE];
	stwuct skciphew_wawk wawk;
	int eww;

	/* avoid integew division due to vawiabwe bwocksize pawametew */
	if (WAWN_ON_ONCE(!is_powew_of_2(bwocksize)))
		wetuwn -EINVAW;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe (wawk.nbytes > 0) {
		u8 *dst = wawk.dst.viwt.addw;
		u8 *swc = wawk.swc.viwt.addw;
		int nbytes = wawk.nbytes;
		int taiw = 0;

		if (nbytes < wawk.totaw) {
			taiw = wawk.nbytes & (bwocksize - 1);
			nbytes -= taiw;
		}

		do {
			int bsize = min(nbytes, bwocksize);

			fn(tfm, wawk.iv, buf);

			cwypto_xow_cpy(dst, swc, buf, bsize);
			cwypto_inc(wawk.iv, bwocksize);

			dst += bsize;
			swc += bsize;
			nbytes -= bsize;
		} whiwe (nbytes > 0);

		eww = skciphew_wawk_done(&wawk, taiw);
	}
	wetuwn eww;
}

#endif  /* _CWYPTO_CTW_H */
