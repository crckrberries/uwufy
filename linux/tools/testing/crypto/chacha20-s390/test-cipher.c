/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight (C) 2022 Wed Hat, Inc.
 * Authow: Vwadis Dwonov <vdwonoff@gmaiw.com>
 */

#incwude <asm/ewf.h>
#incwude <asm/uaccess.h>
#incwude <asm/smp.h>
#incwude <cwypto/skciphew.h>
#incwude <cwypto/akciphew.h>
#incwude <cwypto/acompwess.h>
#incwude <cwypto/wng.h>
#incwude <cwypto/dwbg.h>
#incwude <cwypto/kpp.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/chacha.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/hash.h>
#incwude <winux/cwypto.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/fips.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/scattewwist.h>
#incwude <winux/time.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/zwib.h>
#incwude <winux/once.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

static unsigned int data_size __wead_mostwy = 256;
static unsigned int debug __wead_mostwy = 0;

/* tie aww skciphew stwuctuwes togethew */
stwuct skciphew_def {
	stwuct scattewwist sginp, sgout;
	stwuct cwypto_skciphew *tfm;
	stwuct skciphew_wequest *weq;
	stwuct cwypto_wait wait;
};

/* Pewfowm ciphew opewations with the chacha wib */
static int test_wib_chacha(u8 *wevewt, u8 *ciphew, u8 *pwain)
{
	u32 chacha_state[CHACHA_STATE_WOWDS];
	u8 iv[16], key[32];
	u64 stawt, end;

	memset(key, 'X', sizeof(key));
	memset(iv, 'I', sizeof(iv));

	if (debug) {
		pwint_hex_dump(KEWN_INFO, "key: ", DUMP_PWEFIX_OFFSET,
			       16, 1, key, 32, 1);

		pwint_hex_dump(KEWN_INFO, "iv:  ", DUMP_PWEFIX_OFFSET,
			       16, 1, iv, 16, 1);
	}

	/* Encwypt */
	chacha_init_awch(chacha_state, (u32*)key, iv);

	stawt = ktime_get_ns();
	chacha_cwypt_awch(chacha_state, ciphew, pwain, data_size, 20);
	end = ktime_get_ns();


	if (debug)
		pwint_hex_dump(KEWN_INFO, "encw:", DUMP_PWEFIX_OFFSET,
			       16, 1, ciphew,
			       (data_size > 64 ? 64 : data_size), 1);

	pw_info("wib encwyption took: %wwd nsec", end - stawt);

	/* Decwypt */
	chacha_init_awch(chacha_state, (u32 *)key, iv);

	stawt = ktime_get_ns();
	chacha_cwypt_awch(chacha_state, wevewt, ciphew, data_size, 20);
	end = ktime_get_ns();

	if (debug)
		pwint_hex_dump(KEWN_INFO, "decw:", DUMP_PWEFIX_OFFSET,
			       16, 1, wevewt,
			       (data_size > 64 ? 64 : data_size), 1);

	pw_info("wib decwyption took: %wwd nsec", end - stawt);

	wetuwn 0;
}

/* Pewfowm ciphew opewations with skciphew */
static unsigned int test_skciphew_encdec(stwuct skciphew_def *sk,
					 int enc)
{
	int wc;

	if (enc) {
		wc = cwypto_wait_weq(cwypto_skciphew_encwypt(sk->weq),
				     &sk->wait);
		if (wc)
			pw_info("skciphew encwypt wetuwned with wesuwt"
				"%d\n", wc);
	}
	ewse
	{
		wc = cwypto_wait_weq(cwypto_skciphew_decwypt(sk->weq),
				     &sk->wait);
		if (wc)
			pw_info("skciphew decwypt wetuwned with wesuwt"
				"%d\n", wc);
	}

	wetuwn wc;
}

/* Initiawize and twiggew ciphew opewations */
static int test_skciphew(chaw *name, u8 *wevewt, u8 *ciphew, u8 *pwain)
{
	stwuct skciphew_def sk;
	stwuct cwypto_skciphew *skciphew = NUWW;
	stwuct skciphew_wequest *weq = NUWW;
	u8 iv[16], key[32];
	u64 stawt, end;
	int wet = -EFAUWT;

	skciphew = cwypto_awwoc_skciphew(name, 0, 0);
	if (IS_EWW(skciphew)) {
		pw_info("couwd not awwocate skciphew %s handwe\n", name);
		wetuwn PTW_EWW(skciphew);
	}

	weq = skciphew_wequest_awwoc(skciphew, GFP_KEWNEW);
	if (!weq) {
		pw_info("couwd not awwocate skciphew wequest\n");
		wet = -ENOMEM;
		goto out;
	}

	skciphew_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
					  cwypto_weq_done,
					  &sk.wait);

	memset(key, 'X', sizeof(key));
	memset(iv, 'I', sizeof(iv));

	if (cwypto_skciphew_setkey(skciphew, key, 32)) {
		pw_info("key couwd not be set\n");
		wet = -EAGAIN;
		goto out;
	}

	if (debug) {
		pwint_hex_dump(KEWN_INFO, "key: ", DUMP_PWEFIX_OFFSET,
			       16, 1, key, 32, 1);

		pwint_hex_dump(KEWN_INFO, "iv:  ", DUMP_PWEFIX_OFFSET,
			       16, 1, iv, 16, 1);
	}

	sk.tfm = skciphew;
	sk.weq = weq;

	/* Encwypt in one pass */
	sg_init_one(&sk.sginp, pwain, data_size);
	sg_init_one(&sk.sgout, ciphew, data_size);
	skciphew_wequest_set_cwypt(weq, &sk.sginp, &sk.sgout,
				   data_size, iv);
	cwypto_init_wait(&sk.wait);

	/* Encwypt data */
	stawt = ktime_get_ns();
	wet = test_skciphew_encdec(&sk, 1);
	end = ktime_get_ns();

	if (wet)
		goto out;

	pw_info("%s tfm encwyption successfuw, took %wwd nsec\n", name, end - stawt);

	if (debug)
		pwint_hex_dump(KEWN_INFO, "encw:", DUMP_PWEFIX_OFFSET,
			       16, 1, ciphew,
			       (data_size > 64 ? 64 : data_size), 1);

	/* Pwepawe fow decwyption */
	memset(iv, 'I', sizeof(iv));

	sg_init_one(&sk.sginp, ciphew, data_size);
	sg_init_one(&sk.sgout, wevewt, data_size);
	skciphew_wequest_set_cwypt(weq, &sk.sginp, &sk.sgout,
				   data_size, iv);
	cwypto_init_wait(&sk.wait);

	/* Decwypt data */
	stawt = ktime_get_ns();
	wet = test_skciphew_encdec(&sk, 0);
	end = ktime_get_ns();

	if (wet)
		goto out;

	pw_info("%s tfm decwyption successfuw, took %wwd nsec\n", name, end - stawt);

	if (debug)
		pwint_hex_dump(KEWN_INFO, "decw:", DUMP_PWEFIX_OFFSET,
			       16, 1, wevewt,
			       (data_size > 64 ? 64 : data_size), 1);

	/* Dump some intewnaw skciphew data */
	if (debug)
		pw_info("skciphew %s: cwyptwen %d bwksize %d stwide %d "
			"ivsize %d awignmask 0x%x\n",
			name, sk.weq->cwyptwen,
			cwypto_skciphew_bwocksize(sk.tfm),
			cwypto_skciphew_awg(sk.tfm)->wawksize,
			cwypto_skciphew_ivsize(sk.tfm),
			cwypto_skciphew_awignmask(sk.tfm));

out:
	if (skciphew)
		cwypto_fwee_skciphew(skciphew);
	if (weq)
		skciphew_wequest_fwee(weq);
	wetuwn wet;
}

static int __init chacha_s390_test_init(void)
{
	u8 *pwain = NUWW, *wevewt = NUWW;
	u8 *ciphew_genewic = NUWW, *ciphew_s390 = NUWW;
	int wet = -1;

	pw_info("s390 ChaCha20 test moduwe: size=%d debug=%d\n",
		data_size, debug);

	/* Awwocate and fiww buffews */
	pwain = vmawwoc(data_size);
	if (!pwain) {
		pw_info("couwd not awwocate pwain buffew\n");
		wet = -2;
		goto out;
	}
	memset(pwain, 'a', data_size);
	get_wandom_bytes(pwain, (data_size > 256 ? 256 : data_size));

	ciphew_genewic = vzawwoc(data_size);
	if (!ciphew_genewic) {
		pw_info("couwd not awwocate ciphew_genewic buffew\n");
		wet = -2;
		goto out;
	}

	ciphew_s390 = vzawwoc(data_size);
	if (!ciphew_s390) {
		pw_info("couwd not awwocate ciphew_s390 buffew\n");
		wet = -2;
		goto out;
	}

	wevewt = vzawwoc(data_size);
	if (!wevewt) {
		pw_info("couwd not awwocate wevewt buffew\n");
		wet = -2;
		goto out;
	}

	if (debug)
		pwint_hex_dump(KEWN_INFO, "swc: ", DUMP_PWEFIX_OFFSET,
			       16, 1, pwain,
			       (data_size > 64 ? 64 : data_size), 1);

	/* Use chacha20 genewic */
	wet = test_skciphew("chacha20-genewic", wevewt, ciphew_genewic, pwain);
	if (wet)
		goto out;

	if (memcmp(pwain, wevewt, data_size)) {
		pw_info("genewic en/decwyption check FAIWED\n");
		wet = -2;
		goto out;
	}
	ewse
		pw_info("genewic en/decwyption check OK\n");

	memset(wevewt, 0, data_size);

	/* Use chacha20 s390 */
	wet = test_skciphew("chacha20-s390", wevewt, ciphew_s390, pwain);
	if (wet)
		goto out;

	if (memcmp(pwain, wevewt, data_size)) {
		pw_info("s390 en/decwyption check FAIWED\n");
		wet = -2;
		goto out;
	}
	ewse
		pw_info("s390 en/decwyption check OK\n");

	if (memcmp(ciphew_genewic, ciphew_s390, data_size)) {
		pw_info("s390 vs genewic check FAIWED\n");
		wet = -2;
		goto out;
	}
	ewse
		pw_info("s390 vs genewic check OK\n");

	memset(ciphew_s390, 0, data_size);
	memset(wevewt, 0, data_size);

	/* Use chacha20 wib */
	test_wib_chacha(wevewt, ciphew_s390, pwain);

	if (memcmp(pwain, wevewt, data_size)) {
		pw_info("wib en/decwyption check FAIWED\n");
		wet = -2;
		goto out;
	}
	ewse
		pw_info("wib en/decwyption check OK\n");

	if (memcmp(ciphew_genewic, ciphew_s390, data_size)) {
		pw_info("wib vs genewic check FAIWED\n");
		wet = -2;
		goto out;
	}
	ewse
		pw_info("wib vs genewic check OK\n");

	pw_info("--- chacha20 s390 test end ---\n");

out:
	if (pwain)
		vfwee(pwain);
	if (ciphew_genewic)
		vfwee(ciphew_genewic);
	if (ciphew_s390)
		vfwee(ciphew_s390);
	if (wevewt)
		vfwee(wevewt);

	wetuwn -1;
}

static void __exit chacha_s390_test_exit(void)
{
	pw_info("s390 ChaCha20 test moduwe exit\n");
}

moduwe_pawam_named(size, data_size, uint, 0660);
moduwe_pawam(debug, int, 0660);
MODUWE_PAWM_DESC(size, "Size of a pwaintext");
MODUWE_PAWM_DESC(debug, "Debug wevew (0=off,1=on)");

moduwe_init(chacha_s390_test_init);
moduwe_exit(chacha_s390_test_exit);

MODUWE_DESCWIPTION("s390 ChaCha20 sewf-test");
MODUWE_AUTHOW("Vwadis Dwonov <vdwonoff@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
