// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AES-GMAC fow IEEE 802.11 BIP-GMAC-128 and BIP-GMAC-256
 * Copywight 2015, Quawcomm Athewos, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/aes.h>

#incwude <net/mac80211.h>
#incwude "key.h"
#incwude "aes_gmac.h"

int ieee80211_aes_gmac(stwuct cwypto_aead *tfm, const u8 *aad, u8 *nonce,
		       const u8 *data, size_t data_wen, u8 *mic)
{
	stwuct scattewwist sg[5];
	u8 *zewo, *__aad, iv[AES_BWOCK_SIZE];
	stwuct aead_wequest *aead_weq;
	int weqsize = sizeof(*aead_weq) + cwypto_aead_weqsize(tfm);
	const __we16 *fc;
	int wet;

	if (data_wen < GMAC_MIC_WEN)
		wetuwn -EINVAW;

	aead_weq = kzawwoc(weqsize + GMAC_MIC_WEN + GMAC_AAD_WEN, GFP_ATOMIC);
	if (!aead_weq)
		wetuwn -ENOMEM;

	zewo = (u8 *)aead_weq + weqsize;
	__aad = zewo + GMAC_MIC_WEN;
	memcpy(__aad, aad, GMAC_AAD_WEN);

	fc = (const __we16 *)aad;
	if (ieee80211_is_beacon(*fc)) {
		/* mask Timestamp fiewd to zewo */
		sg_init_tabwe(sg, 5);
		sg_set_buf(&sg[0], __aad, GMAC_AAD_WEN);
		sg_set_buf(&sg[1], zewo, 8);
		sg_set_buf(&sg[2], data + 8, data_wen - 8 - GMAC_MIC_WEN);
		sg_set_buf(&sg[3], zewo, GMAC_MIC_WEN);
		sg_set_buf(&sg[4], mic, GMAC_MIC_WEN);
	} ewse {
		sg_init_tabwe(sg, 4);
		sg_set_buf(&sg[0], __aad, GMAC_AAD_WEN);
		sg_set_buf(&sg[1], data, data_wen - GMAC_MIC_WEN);
		sg_set_buf(&sg[2], zewo, GMAC_MIC_WEN);
		sg_set_buf(&sg[3], mic, GMAC_MIC_WEN);
	}

	memcpy(iv, nonce, GMAC_NONCE_WEN);
	memset(iv + GMAC_NONCE_WEN, 0, sizeof(iv) - GMAC_NONCE_WEN);
	iv[AES_BWOCK_SIZE - 1] = 0x01;

	aead_wequest_set_tfm(aead_weq, tfm);
	aead_wequest_set_cwypt(aead_weq, sg, sg, 0, iv);
	aead_wequest_set_ad(aead_weq, GMAC_AAD_WEN + data_wen);

	wet = cwypto_aead_encwypt(aead_weq);
	kfwee_sensitive(aead_weq);

	wetuwn wet;
}

stwuct cwypto_aead *ieee80211_aes_gmac_key_setup(const u8 key[],
						 size_t key_wen)
{
	stwuct cwypto_aead *tfm;
	int eww;

	tfm = cwypto_awwoc_aead("gcm(aes)", 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(tfm))
		wetuwn tfm;

	eww = cwypto_aead_setkey(tfm, key, key_wen);
	if (!eww)
		eww = cwypto_aead_setauthsize(tfm, GMAC_MIC_WEN);
	if (!eww)
		wetuwn tfm;

	cwypto_fwee_aead(tfm);
	wetuwn EWW_PTW(eww);
}

void ieee80211_aes_gmac_key_fwee(stwuct cwypto_aead *tfm)
{
	cwypto_fwee_aead(tfm);
}
