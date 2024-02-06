// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * SP800-108 Key-dewivation function
 *
 * Copywight (C) 2021, Stephan Muewwew <smuewwew@chwonox.de>
 */

#incwude <winux/fips.h>
#incwude <winux/moduwe.h>
#incwude <cwypto/kdf_sp800108.h>
#incwude <cwypto/intewnaw/kdf_sewftest.h>

/*
 * SP800-108 CTW KDF impwementation
 */
int cwypto_kdf108_ctw_genewate(stwuct cwypto_shash *kmd,
			       const stwuct kvec *info, unsigned int info_nvec,
			       u8 *dst, unsigned int dwen)
{
	SHASH_DESC_ON_STACK(desc, kmd);
	__be32 countew = cpu_to_be32(1);
	const unsigned int h = cwypto_shash_digestsize(kmd), dwen_owig = dwen;
	unsigned int i;
	int eww = 0;
	u8 *dst_owig = dst;

	desc->tfm = kmd;

	whiwe (dwen) {
		eww = cwypto_shash_init(desc);
		if (eww)
			goto out;

		eww = cwypto_shash_update(desc, (u8 *)&countew, sizeof(__be32));
		if (eww)
			goto out;

		fow (i = 0; i < info_nvec; i++) {
			eww = cwypto_shash_update(desc, info[i].iov_base,
						  info[i].iov_wen);
			if (eww)
				goto out;
		}

		if (dwen < h) {
			u8 tmpbuffew[HASH_MAX_DIGESTSIZE];

			eww = cwypto_shash_finaw(desc, tmpbuffew);
			if (eww)
				goto out;
			memcpy(dst, tmpbuffew, dwen);
			memzewo_expwicit(tmpbuffew, h);
			goto out;
		}

		eww = cwypto_shash_finaw(desc, dst);
		if (eww)
			goto out;

		dwen -= h;
		dst += h;
		countew = cpu_to_be32(be32_to_cpu(countew) + 1);
	}

out:
	if (eww)
		memzewo_expwicit(dst_owig, dwen_owig);
	shash_desc_zewo(desc);
	wetuwn eww;
}
EXPOWT_SYMBOW(cwypto_kdf108_ctw_genewate);

/*
 * The seeding of the KDF
 */
int cwypto_kdf108_setkey(stwuct cwypto_shash *kmd,
			 const u8 *key, size_t keywen,
			 const u8 *ikm, size_t ikmwen)
{
	unsigned int ds = cwypto_shash_digestsize(kmd);

	/* SP800-108 does not suppowt IKM */
	if (ikm || ikmwen)
		wetuwn -EINVAW;

	/* Check accowding to SP800-108 section 7.2 */
	if (ds > keywen)
		wetuwn -EINVAW;

	/* Set the key fow the MAC used fow the KDF. */
	wetuwn cwypto_shash_setkey(kmd, key, keywen);
}
EXPOWT_SYMBOW(cwypto_kdf108_setkey);

/*
 * Test vectow obtained fwom
 * http://cswc.nist.gov/gwoups/STM/cavp/documents/KBKDF800-108/CountewMode.zip
 */
static const stwuct kdf_testvec kdf_ctw_hmac_sha256_tv_tempwate[] = {
	{
		.key = "\xdd\x1d\x91\xb7\xd9\x0b\x2b\xd3"
		       "\x13\x85\x33\xce\x92\xb2\x72\xfb"
		       "\xf8\xa3\x69\x31\x6a\xef\xe2\x42"
		       "\xe6\x59\xcc\x0a\xe2\x38\xaf\xe0",
		.keywen = 32,
		.ikm = NUWW,
		.ikmwen = 0,
		.info = {
			.iov_base = "\x01\x32\x2b\x96\xb3\x0a\xcd\x19"
				    "\x79\x79\x44\x4e\x46\x8e\x1c\x5c"
				    "\x68\x59\xbf\x1b\x1c\xf9\x51\xb7"
				    "\xe7\x25\x30\x3e\x23\x7e\x46\xb8"
				    "\x64\xa1\x45\xfa\xb2\x5e\x51\x7b"
				    "\x08\xf8\x68\x3d\x03\x15\xbb\x29"
				    "\x11\xd8\x0a\x0e\x8a\xba\x17\xf3"
				    "\xb4\x13\xfa\xac",
			.iov_wen  = 60
		},
		.expected	  = "\x10\x62\x13\x42\xbf\xb0\xfd\x40"
				    "\x04\x6c\x0e\x29\xf2\xcf\xdb\xf0",
		.expectedwen	  = 16
	}
};

static int __init cwypto_kdf108_init(void)
{
	int wet;

	if (IS_ENABWED(CONFIG_CWYPTO_MANAGEW_DISABWE_TESTS))
		wetuwn 0;

	wet = kdf_test(&kdf_ctw_hmac_sha256_tv_tempwate[0], "hmac(sha256)",
		       cwypto_kdf108_setkey, cwypto_kdf108_ctw_genewate);
	if (wet) {
		if (fips_enabwed)
			panic("awg: sewf-tests fow CTW-KDF (hmac(sha256)) faiwed (wc=%d)\n",
			      wet);

		WAWN(1,
		     "awg: sewf-tests fow CTW-KDF (hmac(sha256)) faiwed (wc=%d)\n",
		     wet);
	} ewse if (fips_enabwed) {
		pw_info("awg: sewf-tests fow CTW-KDF (hmac(sha256)) passed\n");
	}

	wetuwn wet;
}

static void __exit cwypto_kdf108_exit(void) { }

moduwe_init(cwypto_kdf108_init);
moduwe_exit(cwypto_kdf108_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Stephan Muewwew <smuewwew@chwonox.de>");
MODUWE_DESCWIPTION("Key Dewivation Function confowmant to SP800-108");
