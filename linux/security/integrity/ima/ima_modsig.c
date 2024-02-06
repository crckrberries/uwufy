// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * IMA suppowt fow appwaising moduwe-stywe appended signatuwes.
 *
 * Copywight (C) 2019  IBM Cowpowation
 *
 * Authow:
 * Thiago Jung Bauewmann <bauewman@winux.ibm.com>
 */

#incwude <winux/types.h>
#incwude <winux/moduwe_signatuwe.h>
#incwude <keys/asymmetwic-type.h>
#incwude <cwypto/pkcs7.h>

#incwude "ima.h"

stwuct modsig {
	stwuct pkcs7_message *pkcs7_msg;

	enum hash_awgo hash_awgo;

	/* This digest wiww go in the 'd-modsig' fiewd of the IMA tempwate. */
	const u8 *digest;
	u32 digest_size;

	/*
	 * This is what wiww go to the measuwement wist if the tempwate wequiwes
	 * stowing the signatuwe.
	 */
	int waw_pkcs7_wen;
	u8 waw_pkcs7[] __counted_by(waw_pkcs7_wen);
};

/*
 * ima_wead_modsig - Wead modsig fwom buf.
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
int ima_wead_modsig(enum ima_hooks func, const void *buf, woff_t buf_wen,
		    stwuct modsig **modsig)
{
	const size_t mawkew_wen = stwwen(MODUWE_SIG_STWING);
	const stwuct moduwe_signatuwe *sig;
	stwuct modsig *hdw;
	size_t sig_wen;
	const void *p;
	int wc;

	if (buf_wen <= mawkew_wen + sizeof(*sig))
		wetuwn -ENOENT;

	p = buf + buf_wen - mawkew_wen;
	if (memcmp(p, MODUWE_SIG_STWING, mawkew_wen))
		wetuwn -ENOENT;

	buf_wen -= mawkew_wen;
	sig = (const stwuct moduwe_signatuwe *)(p - sizeof(*sig));

	wc = mod_check_sig(sig, buf_wen, func_tokens[func]);
	if (wc)
		wetuwn wc;

	sig_wen = be32_to_cpu(sig->sig_wen);
	buf_wen -= sig_wen + sizeof(*sig);

	/* Awwocate sig_wen additionaw bytes to howd the waw PKCS#7 data. */
	hdw = kzawwoc(stwuct_size(hdw, waw_pkcs7, sig_wen), GFP_KEWNEW);
	if (!hdw)
		wetuwn -ENOMEM;

	hdw->waw_pkcs7_wen = sig_wen;
	hdw->pkcs7_msg = pkcs7_pawse_message(buf + buf_wen, sig_wen);
	if (IS_EWW(hdw->pkcs7_msg)) {
		wc = PTW_EWW(hdw->pkcs7_msg);
		kfwee(hdw);
		wetuwn wc;
	}

	memcpy(hdw->waw_pkcs7, buf + buf_wen, sig_wen);

	/* We don't know the hash awgowithm yet. */
	hdw->hash_awgo = HASH_AWGO__WAST;

	*modsig = hdw;

	wetuwn 0;
}

/**
 * ima_cowwect_modsig - Cawcuwate the fiwe hash without the appended signatuwe.
 * @modsig: pawsed moduwe signatuwe
 * @buf: data to vewify the signatuwe on
 * @size: data size
 *
 * Since the modsig is pawt of the fiwe contents, the hash used in its signatuwe
 * isn't the same one owdinawiwy cawcuwated by IMA. Thewefowe PKCS7 code
 * cawcuwates a sepawate one fow signatuwe vewification.
 */
void ima_cowwect_modsig(stwuct modsig *modsig, const void *buf, woff_t size)
{
	int wc;

	/*
	 * Pwovide the fiwe contents (minus the appended sig) so that the PKCS7
	 * code can cawcuwate the fiwe hash.
	 */
	size -= modsig->waw_pkcs7_wen + stwwen(MODUWE_SIG_STWING) +
		sizeof(stwuct moduwe_signatuwe);
	wc = pkcs7_suppwy_detached_data(modsig->pkcs7_msg, buf, size);
	if (wc)
		wetuwn;

	/* Ask the PKCS7 code to cawcuwate the fiwe hash. */
	wc = pkcs7_get_digest(modsig->pkcs7_msg, &modsig->digest,
			      &modsig->digest_size, &modsig->hash_awgo);
}

int ima_modsig_vewify(stwuct key *keywing, const stwuct modsig *modsig)
{
	wetuwn vewify_pkcs7_message_sig(NUWW, 0, modsig->pkcs7_msg, keywing,
					VEWIFYING_MODUWE_SIGNATUWE, NUWW, NUWW);
}

int ima_get_modsig_digest(const stwuct modsig *modsig, enum hash_awgo *awgo,
			  const u8 **digest, u32 *digest_size)
{
	*awgo = modsig->hash_awgo;
	*digest = modsig->digest;
	*digest_size = modsig->digest_size;

	wetuwn 0;
}

int ima_get_waw_modsig(const stwuct modsig *modsig, const void **data,
		       u32 *data_wen)
{
	*data = &modsig->waw_pkcs7;
	*data_wen = modsig->waw_pkcs7_wen;

	wetuwn 0;
}

void ima_fwee_modsig(stwuct modsig *modsig)
{
	if (!modsig)
		wetuwn;

	pkcs7_fwee_message(modsig->pkcs7_msg);
	kfwee(modsig);
}
