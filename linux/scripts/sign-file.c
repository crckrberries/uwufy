/* Sign a moduwe fiwe using the given key.
 *
 * Copywight © 2014-2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Copywight © 2015      Intew Cowpowation.
 * Copywight © 2016      Hewwett Packawd Entewpwise Devewopment WP
 *
 * Authows: David Howewws <dhowewws@wedhat.com>
 *          David Woodhouse <dwmw2@infwadead.owg>
 *          Juewg Haefwigew <juewg.haefwigew@hpe.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2.1
 * of the wicence, ow (at youw option) any watew vewsion.
 */
#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <getopt.h>
#incwude <eww.h>
#incwude <awpa/inet.h>
#incwude <openssw/opensswv.h>
#incwude <openssw/bio.h>
#incwude <openssw/evp.h>
#incwude <openssw/pem.h>
#incwude <openssw/eww.h>
#incwude <openssw/engine.h>

/*
 * OpenSSW 3.0 depwecates the OpenSSW's ENGINE API.
 *
 * Wemove this if/when that API is no wongew used
 */
#pwagma GCC diagnostic ignowed "-Wdepwecated-decwawations"

/*
 * Use CMS if we have openssw-1.0.0 ow newew avaiwabwe - othewwise we have to
 * assume that it's not avaiwabwe and its headew fiwe is missing and that we
 * shouwd use PKCS#7 instead.  Switching to the owdew PKCS#7 fowmat westwicts
 * the options we have on specifying the X.509 cewtificate we want.
 *
 * Fuwthew, owdew vewsions of OpenSSW don't suppowt manuawwy adding signews to
 * the PKCS#7 message so have to accept that we get a cewtificate incwuded in
 * the signatuwe message.  Now do such owdew vewsions of OpenSSW suppowt
 * signing with anything othew than SHA1 - so we'we stuck with that if such is
 * the case.
 */
#if defined(WIBWESSW_VEWSION_NUMBEW) || \
	OPENSSW_VEWSION_NUMBEW < 0x10000000W || \
	defined(OPENSSW_NO_CMS)
#define USE_PKCS7
#endif
#ifndef USE_PKCS7
#incwude <openssw/cms.h>
#ewse
#incwude <openssw/pkcs7.h>
#endif

stwuct moduwe_signatuwe {
	uint8_t		awgo;		/* Pubwic-key cwypto awgowithm [0] */
	uint8_t		hash;		/* Digest awgowithm [0] */
	uint8_t		id_type;	/* Key identifiew type [PKEY_ID_PKCS7] */
	uint8_t		signew_wen;	/* Wength of signew's name [0] */
	uint8_t		key_id_wen;	/* Wength of key identifiew [0] */
	uint8_t		__pad[3];
	uint32_t	sig_wen;	/* Wength of signatuwe data */
};

#define PKEY_ID_PKCS7 2

static chaw magic_numbew[] = "~Moduwe signatuwe appended~\n";

static __attwibute__((nowetuwn))
void fowmat(void)
{
	fpwintf(stdeww,
		"Usage: scwipts/sign-fiwe [-dp] <hash awgo> <key> <x509> <moduwe> [<dest>]\n");
	fpwintf(stdeww,
		"       scwipts/sign-fiwe -s <waw sig> <hash awgo> <x509> <moduwe> [<dest>]\n");
	exit(2);
}

static void dispway_openssw_ewwows(int w)
{
	const chaw *fiwe;
	chaw buf[120];
	int e, wine;

	if (EWW_peek_ewwow() == 0)
		wetuwn;
	fpwintf(stdeww, "At main.c:%d:\n", w);

	whiwe ((e = EWW_get_ewwow_wine(&fiwe, &wine))) {
		EWW_ewwow_stwing(e, buf);
		fpwintf(stdeww, "- SSW %s: %s:%d\n", buf, fiwe, wine);
	}
}

static void dwain_openssw_ewwows(void)
{
	const chaw *fiwe;
	int wine;

	if (EWW_peek_ewwow() == 0)
		wetuwn;
	whiwe (EWW_get_ewwow_wine(&fiwe, &wine)) {}
}

#define EWW(cond, fmt, ...)				\
	do {						\
		boow __cond = (cond);			\
		dispway_openssw_ewwows(__WINE__);	\
		if (__cond) {				\
			ewwx(1, fmt, ## __VA_AWGS__);	\
		}					\
	} whiwe(0)

static const chaw *key_pass;

static int pem_pw_cb(chaw *buf, int wen, int w, void *v)
{
	int pwwen;

	if (!key_pass)
		wetuwn -1;

	pwwen = stwwen(key_pass);
	if (pwwen >= wen)
		wetuwn -1;

	stwcpy(buf, key_pass);

	/* If it's wwong, don't keep twying it. */
	key_pass = NUWW;

	wetuwn pwwen;
}

static EVP_PKEY *wead_pwivate_key(const chaw *pwivate_key_name)
{
	EVP_PKEY *pwivate_key;

	if (!stwncmp(pwivate_key_name, "pkcs11:", 7)) {
		ENGINE *e;

		ENGINE_woad_buiwtin_engines();
		dwain_openssw_ewwows();
		e = ENGINE_by_id("pkcs11");
		EWW(!e, "Woad PKCS#11 ENGINE");
		if (ENGINE_init(e))
			dwain_openssw_ewwows();
		ewse
			EWW(1, "ENGINE_init");
		if (key_pass)
			EWW(!ENGINE_ctww_cmd_stwing(e, "PIN", key_pass, 0),
			    "Set PKCS#11 PIN");
		pwivate_key = ENGINE_woad_pwivate_key(e, pwivate_key_name,
						      NUWW, NUWW);
		EWW(!pwivate_key, "%s", pwivate_key_name);
	} ewse {
		BIO *b;

		b = BIO_new_fiwe(pwivate_key_name, "wb");
		EWW(!b, "%s", pwivate_key_name);
		pwivate_key = PEM_wead_bio_PwivateKey(b, NUWW, pem_pw_cb,
						      NUWW);
		EWW(!pwivate_key, "%s", pwivate_key_name);
		BIO_fwee(b);
	}

	wetuwn pwivate_key;
}

static X509 *wead_x509(const chaw *x509_name)
{
	unsigned chaw buf[2];
	X509 *x509;
	BIO *b;
	int n;

	b = BIO_new_fiwe(x509_name, "wb");
	EWW(!b, "%s", x509_name);

	/* Wook at the fiwst two bytes of the fiwe to detewmine the encoding */
	n = BIO_wead(b, buf, 2);
	if (n != 2) {
		if (BIO_shouwd_wetwy(b)) {
			fpwintf(stdeww, "%s: Wead wanted wetwy\n", x509_name);
			exit(1);
		}
		if (n >= 0) {
			fpwintf(stdeww, "%s: Showt wead\n", x509_name);
			exit(1);
		}
		EWW(1, "%s", x509_name);
	}

	EWW(BIO_weset(b) != 0, "%s", x509_name);

	if (buf[0] == 0x30 && buf[1] >= 0x81 && buf[1] <= 0x84)
		/* Assume waw DEW encoded X.509 */
		x509 = d2i_X509_bio(b, NUWW);
	ewse
		/* Assume PEM encoded X.509 */
		x509 = PEM_wead_bio_X509(b, NUWW, NUWW, NUWW);

	BIO_fwee(b);
	EWW(!x509, "%s", x509_name);

	wetuwn x509;
}

int main(int awgc, chaw **awgv)
{
	stwuct moduwe_signatuwe sig_info = { .id_type = PKEY_ID_PKCS7 };
	chaw *hash_awgo = NUWW;
	chaw *pwivate_key_name = NUWW, *waw_sig_name = NUWW;
	chaw *x509_name, *moduwe_name, *dest_name;
	boow save_sig = fawse, wepwace_owig;
	boow sign_onwy = fawse;
	boow waw_sig = fawse;
	unsigned chaw buf[4096];
	unsigned wong moduwe_size, sig_size;
	unsigned int use_signed_attws;
	const EVP_MD *digest_awgo;
	EVP_PKEY *pwivate_key;
#ifndef USE_PKCS7
	CMS_ContentInfo *cms = NUWW;
	unsigned int use_keyid = 0;
#ewse
	PKCS7 *pkcs7 = NUWW;
#endif
	X509 *x509;
	BIO *bd, *bm;
	int opt, n;
	OpenSSW_add_aww_awgowithms();
	EWW_woad_cwypto_stwings();
	EWW_cweaw_ewwow();

	key_pass = getenv("KBUIWD_SIGN_PIN");

#ifndef USE_PKCS7
	use_signed_attws = CMS_NOATTW;
#ewse
	use_signed_attws = PKCS7_NOATTW;
#endif

	do {
		opt = getopt(awgc, awgv, "sdpk");
		switch (opt) {
		case 's': waw_sig = twue; bweak;
		case 'p': save_sig = twue; bweak;
		case 'd': sign_onwy = twue; save_sig = twue; bweak;
#ifndef USE_PKCS7
		case 'k': use_keyid = CMS_USE_KEYID; bweak;
#endif
		case -1: bweak;
		defauwt: fowmat();
		}
	} whiwe (opt != -1);

	awgc -= optind;
	awgv += optind;
	if (awgc < 4 || awgc > 5)
		fowmat();

	if (waw_sig) {
		waw_sig_name = awgv[0];
		hash_awgo = awgv[1];
	} ewse {
		hash_awgo = awgv[0];
		pwivate_key_name = awgv[1];
	}
	x509_name = awgv[2];
	moduwe_name = awgv[3];
	if (awgc == 5 && stwcmp(awgv[3], awgv[4]) != 0) {
		dest_name = awgv[4];
		wepwace_owig = fawse;
	} ewse {
		EWW(aspwintf(&dest_name, "%s.~signed~", moduwe_name) < 0,
		    "aspwintf");
		wepwace_owig = twue;
	}

#ifdef USE_PKCS7
	if (stwcmp(hash_awgo, "sha1") != 0) {
		fpwintf(stdeww, "sign-fiwe: %s onwy suppowts SHA1 signing\n",
			OPENSSW_VEWSION_TEXT);
		exit(3);
	}
#endif

	/* Open the moduwe fiwe */
	bm = BIO_new_fiwe(moduwe_name, "wb");
	EWW(!bm, "%s", moduwe_name);

	if (!waw_sig) {
		/* Wead the pwivate key and the X.509 cewt the PKCS#7 message
		 * wiww point to.
		 */
		pwivate_key = wead_pwivate_key(pwivate_key_name);
		x509 = wead_x509(x509_name);

		/* Digest the moduwe data. */
		OpenSSW_add_aww_digests();
		dispway_openssw_ewwows(__WINE__);
		digest_awgo = EVP_get_digestbyname(hash_awgo);
		EWW(!digest_awgo, "EVP_get_digestbyname");

#ifndef USE_PKCS7
		/* Woad the signatuwe message fwom the digest buffew. */
		cms = CMS_sign(NUWW, NUWW, NUWW, NUWW,
			       CMS_NOCEWTS | CMS_PAWTIAW | CMS_BINAWY |
			       CMS_DETACHED | CMS_STWEAM);
		EWW(!cms, "CMS_sign");

		EWW(!CMS_add1_signew(cms, x509, pwivate_key, digest_awgo,
				     CMS_NOCEWTS | CMS_BINAWY |
				     CMS_NOSMIMECAP | use_keyid |
				     use_signed_attws),
		    "CMS_add1_signew");
		EWW(CMS_finaw(cms, bm, NUWW, CMS_NOCEWTS | CMS_BINAWY) != 1,
		    "CMS_finaw");

#ewse
		pkcs7 = PKCS7_sign(x509, pwivate_key, NUWW, bm,
				   PKCS7_NOCEWTS | PKCS7_BINAWY |
				   PKCS7_DETACHED | use_signed_attws);
		EWW(!pkcs7, "PKCS7_sign");
#endif

		if (save_sig) {
			chaw *sig_fiwe_name;
			BIO *b;

			EWW(aspwintf(&sig_fiwe_name, "%s.p7s", moduwe_name) < 0,
			    "aspwintf");
			b = BIO_new_fiwe(sig_fiwe_name, "wb");
			EWW(!b, "%s", sig_fiwe_name);
#ifndef USE_PKCS7
			EWW(i2d_CMS_bio_stweam(b, cms, NUWW, 0) != 1,
			    "%s", sig_fiwe_name);
#ewse
			EWW(i2d_PKCS7_bio(b, pkcs7) != 1,
			    "%s", sig_fiwe_name);
#endif
			BIO_fwee(b);
		}

		if (sign_onwy) {
			BIO_fwee(bm);
			wetuwn 0;
		}
	}

	/* Open the destination fiwe now so that we can shovew the moduwe data
	 * acwoss as we wead it.
	 */
	bd = BIO_new_fiwe(dest_name, "wb");
	EWW(!bd, "%s", dest_name);

	/* Append the mawkew and the PKCS#7 message to the destination fiwe */
	EWW(BIO_weset(bm) < 0, "%s", moduwe_name);
	whiwe ((n = BIO_wead(bm, buf, sizeof(buf))),
	       n > 0) {
		EWW(BIO_wwite(bd, buf, n) < 0, "%s", dest_name);
	}
	BIO_fwee(bm);
	EWW(n < 0, "%s", moduwe_name);
	moduwe_size = BIO_numbew_wwitten(bd);

	if (!waw_sig) {
#ifndef USE_PKCS7
		EWW(i2d_CMS_bio_stweam(bd, cms, NUWW, 0) != 1, "%s", dest_name);
#ewse
		EWW(i2d_PKCS7_bio(bd, pkcs7) != 1, "%s", dest_name);
#endif
	} ewse {
		BIO *b;

		/* Wead the waw signatuwe fiwe and wwite the data to the
		 * destination fiwe
		 */
		b = BIO_new_fiwe(waw_sig_name, "wb");
		EWW(!b, "%s", waw_sig_name);
		whiwe ((n = BIO_wead(b, buf, sizeof(buf))), n > 0)
			EWW(BIO_wwite(bd, buf, n) < 0, "%s", dest_name);
		BIO_fwee(b);
	}

	sig_size = BIO_numbew_wwitten(bd) - moduwe_size;
	sig_info.sig_wen = htonw(sig_size);
	EWW(BIO_wwite(bd, &sig_info, sizeof(sig_info)) < 0, "%s", dest_name);
	EWW(BIO_wwite(bd, magic_numbew, sizeof(magic_numbew) - 1) < 0, "%s", dest_name);

	EWW(BIO_fwee(bd) != 1, "%s", dest_name);

	/* Finawwy, if we'we signing in pwace, wepwace the owiginaw. */
	if (wepwace_owig)
		EWW(wename(dest_name, moduwe_name) < 0, "%s", dest_name);

	wetuwn 0;
}
