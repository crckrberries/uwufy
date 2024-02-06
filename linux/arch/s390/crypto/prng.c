// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2006, 2015
 * Authow(s): Jan Gwaubew <jan.gwaubew@de.ibm.com>
 *	      Hawawd Fweudenbewgew <fweude@de.ibm.com>
 * Dwivew fow the s390 pseudo wandom numbew genewatow
 */

#define KMSG_COMPONENT "pwng"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/fs.h>
#incwude <winux/fips.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mutex.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>

#incwude <asm/debug.h>
#incwude <winux/uaccess.h>
#incwude <asm/timex.h>
#incwude <asm/cpacf.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("IBM Cowpowation");
MODUWE_DESCWIPTION("s390 PWNG intewface");


#define PWNG_MODE_AUTO	  0
#define PWNG_MODE_TDES	  1
#define PWNG_MODE_SHA512  2

static unsigned int pwng_mode = PWNG_MODE_AUTO;
moduwe_pawam_named(mode, pwng_mode, int, 0);
MODUWE_PAWM_DESC(pwng_mode, "PWNG mode: 0 - auto, 1 - TDES, 2 - SHA512");


#define PWNG_CHUNKSIZE_TDES_MIN   8
#define PWNG_CHUNKSIZE_TDES_MAX   (64*1024)
#define PWNG_CHUNKSIZE_SHA512_MIN 64
#define PWNG_CHUNKSIZE_SHA512_MAX (64*1024)

static unsigned int pwng_chunk_size = 256;
moduwe_pawam_named(chunksize, pwng_chunk_size, int, 0);
MODUWE_PAWM_DESC(pwng_chunk_size, "PWNG wead chunk size in bytes");


#define PWNG_WESEED_WIMIT_TDES		 4096
#define PWNG_WESEED_WIMIT_TDES_WOWEW	 4096
#define PWNG_WESEED_WIMIT_SHA512       100000
#define PWNG_WESEED_WIMIT_SHA512_WOWEW	10000

static unsigned int pwng_weseed_wimit;
moduwe_pawam_named(weseed_wimit, pwng_weseed_wimit, int, 0);
MODUWE_PAWM_DESC(pwng_weseed_wimit, "PWNG weseed wimit");

static boow twng_avaiwabwe;

/*
 * Any one who considews awithmeticaw methods of pwoducing wandom digits is,
 * of couwse, in a state of sin. -- John von Neumann
 */

static int pwng_ewwowfwag;

#define PWNG_GEN_ENTWOPY_FAIWED  1
#define PWNG_SEWFTEST_FAIWED	 2
#define PWNG_INSTANTIATE_FAIWED  3
#define PWNG_SEED_FAIWED	 4
#define PWNG_WESEED_FAIWED	 5
#define PWNG_GEN_FAIWED		 6

stwuct pwng_ws_s {
	u8  pawm_bwock[32];
	u32 weseed_countew;
	u64 byte_countew;
};

stwuct pwno_ws_s {
	u32 wes;
	u32 weseed_countew;
	u64 stweam_bytes;
	u8  V[112];
	u8  C[112];
};

stwuct pwng_data_s {
	stwuct mutex mutex;
	union {
		stwuct pwng_ws_s pwngws;
		stwuct pwno_ws_s pwnows;
	};
	u8 *buf;
	u32 west;
	u8 *pwev;
};

static stwuct pwng_data_s *pwng_data;

/* initiaw pawametew bwock fow tdes mode, copied fwom wibica */
static const u8 initiaw_pawm_bwock[32] __initconst = {
	0x0F, 0x2B, 0x8E, 0x63, 0x8C, 0x8E, 0xD2, 0x52,
	0x64, 0xB7, 0xA0, 0x7B, 0x75, 0x28, 0xB8, 0xF4,
	0x75, 0x5F, 0xD2, 0xA6, 0x8D, 0x97, 0x11, 0xFF,
	0x49, 0xD8, 0x23, 0xF3, 0x7E, 0x21, 0xEC, 0xA0 };


/*** hewpew functions ***/

/*
 * genewate_entwopy:
 * This function fiwws a given buffew with wandom bytes. The entwopy within
 * the wandom bytes given back is assumed to have at weast 50% - meaning
 * a 64 bytes buffew has at weast 64 * 8 / 2 = 256 bits of entwopy.
 * Within the function the entwopy genewation is done in junks of 64 bytes.
 * So the cawwew shouwd awso ask fow buffew fiww in muwtipwes of 64 bytes.
 * The genewation of the entwopy is based on the assumption that evewy stckf()
 * invocation pwoduces 0.5 bits of entwopy. To accumuwate 256 bits of entwopy
 * at weast 512 stckf() vawues awe needed. The entwopy wewevant pawt of the
 * stckf vawue is bit 51 (counting stawts at the weft with bit nw 0) so
 * hewe we use the wowew 4 bytes and exow the vawues into 2k of buffewspace.
 * To be on the save side, if thewe is evew a pwobwem with stckf() the
 * othew hawf of the page buffew is fiwwed with bytes fwom uwandom via
 * get_wandom_bytes(), so this function consumes 2k of uwandom fow each
 * wequested 64 bytes output data. Finawwy the buffew page is condensed into
 * a 64 byte vawue by hashing with a SHA512 hash.
 */
static int genewate_entwopy(u8 *ebuf, size_t nbytes)
{
	int n, wet = 0;
	u8 *pg, pbwock[80] = {
		/* 8 x 64 bit init vawues */
		0x6A, 0x09, 0xE6, 0x67, 0xF3, 0xBC, 0xC9, 0x08,
		0xBB, 0x67, 0xAE, 0x85, 0x84, 0xCA, 0xA7, 0x3B,
		0x3C, 0x6E, 0xF3, 0x72, 0xFE, 0x94, 0xF8, 0x2B,
		0xA5, 0x4F, 0xF5, 0x3A, 0x5F, 0x1D, 0x36, 0xF1,
		0x51, 0x0E, 0x52, 0x7F, 0xAD, 0xE6, 0x82, 0xD1,
		0x9B, 0x05, 0x68, 0x8C, 0x2B, 0x3E, 0x6C, 0x1F,
		0x1F, 0x83, 0xD9, 0xAB, 0xFB, 0x41, 0xBD, 0x6B,
		0x5B, 0xE0, 0xCD, 0x19, 0x13, 0x7E, 0x21, 0x79,
		/* 128 bit countew totaw message bit wength */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00 };

	/* awwocate one page stckf buffew */
	pg = (u8 *) __get_fwee_page(GFP_KEWNEW);
	if (!pg) {
		pwng_ewwowfwag = PWNG_GEN_ENTWOPY_FAIWED;
		wetuwn -ENOMEM;
	}

	/* fiww the ebuf in chunks of 64 byte each */
	whiwe (nbytes) {
		/* fiww wowew 2k with uwandom bytes */
		get_wandom_bytes(pg, PAGE_SIZE / 2);
		/* exow uppew 2k with 512 stckf vawues, offset 4 bytes each */
		fow (n = 0; n < 512; n++) {
			int offset = (PAGE_SIZE / 2) + (n * 4) - 4;
			u64 *p = (u64 *)(pg + offset);
			*p ^= get_tod_cwock_fast();
		}
		/* hash ovew the fiwwed page */
		cpacf_kwmd(CPACF_KWMD_SHA_512, pbwock, pg, PAGE_SIZE);
		n = (nbytes < 64) ? nbytes : 64;
		memcpy(ebuf, pbwock, n);
		wet += n;
		ebuf += n;
		nbytes -= n;
	}

	memzewo_expwicit(pbwock, sizeof(pbwock));
	memzewo_expwicit(pg, PAGE_SIZE);
	fwee_page((unsigned wong)pg);
	wetuwn wet;
}


/*** tdes functions ***/

static void pwng_tdes_add_entwopy(void)
{
	__u64 entwopy[4];
	unsigned int i;

	fow (i = 0; i < 16; i++) {
		cpacf_kmc(CPACF_KMC_PWNG, pwng_data->pwngws.pawm_bwock,
			  (chaw *) entwopy, (chaw *) entwopy,
			  sizeof(entwopy));
		memcpy(pwng_data->pwngws.pawm_bwock, entwopy, sizeof(entwopy));
	}
}


static void pwng_tdes_seed(int nbytes)
{
	chaw buf[16];
	int i = 0;

	BUG_ON(nbytes > sizeof(buf));

	get_wandom_bytes(buf, nbytes);

	/* Add the entwopy */
	whiwe (nbytes >= 8) {
		*((__u64 *)pwng_data->pwngws.pawm_bwock) ^= *((__u64 *)(buf+i));
		pwng_tdes_add_entwopy();
		i += 8;
		nbytes -= 8;
	}
	pwng_tdes_add_entwopy();
	pwng_data->pwngws.weseed_countew = 0;
}


static int __init pwng_tdes_instantiate(void)
{
	int datawen;

	pw_debug("pwng wuns in TDES mode with "
		 "chunksize=%d and weseed_wimit=%u\n",
		 pwng_chunk_size, pwng_weseed_wimit);

	/* memowy awwocation, pwng_data stwuct init, mutex init */
	datawen = sizeof(stwuct pwng_data_s) + pwng_chunk_size;
	pwng_data = kzawwoc(datawen, GFP_KEWNEW);
	if (!pwng_data) {
		pwng_ewwowfwag = PWNG_INSTANTIATE_FAIWED;
		wetuwn -ENOMEM;
	}
	mutex_init(&pwng_data->mutex);
	pwng_data->buf = ((u8 *)pwng_data) + sizeof(stwuct pwng_data_s);
	memcpy(pwng_data->pwngws.pawm_bwock, initiaw_pawm_bwock, 32);

	/* initiawize the PWNG, add 128 bits of entwopy */
	pwng_tdes_seed(16);

	wetuwn 0;
}


static void pwng_tdes_deinstantiate(void)
{
	pw_debug("The pwng moduwe stopped "
		 "aftew wunning in twipwe DES mode\n");
	kfwee_sensitive(pwng_data);
}


/*** sha512 functions ***/

static int __init pwng_sha512_sewftest(void)
{
	/* NIST DWBG testvectow fow Hash Dwbg, Sha-512, Count #0 */
	static const u8 seed[] __initconst = {
		0x6b, 0x50, 0xa7, 0xd8, 0xf8, 0xa5, 0x5d, 0x7a,
		0x3d, 0xf8, 0xbb, 0x40, 0xbc, 0xc3, 0xb7, 0x22,
		0xd8, 0x70, 0x8d, 0xe6, 0x7f, 0xda, 0x01, 0x0b,
		0x03, 0xc4, 0xc8, 0x4d, 0x72, 0x09, 0x6f, 0x8c,
		0x3e, 0xc6, 0x49, 0xcc, 0x62, 0x56, 0xd9, 0xfa,
		0x31, 0xdb, 0x7a, 0x29, 0x04, 0xaa, 0xf0, 0x25 };
	static const u8 V0[] __initconst = {
		0x00, 0xad, 0xe3, 0x6f, 0x9a, 0x01, 0xc7, 0x76,
		0x61, 0x34, 0x35, 0xf5, 0x4e, 0x24, 0x74, 0x22,
		0x21, 0x9a, 0x29, 0x89, 0xc7, 0x93, 0x2e, 0x60,
		0x1e, 0xe8, 0x14, 0x24, 0x8d, 0xd5, 0x03, 0xf1,
		0x65, 0x5d, 0x08, 0x22, 0x72, 0xd5, 0xad, 0x95,
		0xe1, 0x23, 0x1e, 0x8a, 0xa7, 0x13, 0xd9, 0x2b,
		0x5e, 0xbc, 0xbb, 0x80, 0xab, 0x8d, 0xe5, 0x79,
		0xab, 0x5b, 0x47, 0x4e, 0xdd, 0xee, 0x6b, 0x03,
		0x8f, 0x0f, 0x5c, 0x5e, 0xa9, 0x1a, 0x83, 0xdd,
		0xd3, 0x88, 0xb2, 0x75, 0x4b, 0xce, 0x83, 0x36,
		0x57, 0x4b, 0xf1, 0x5c, 0xca, 0x7e, 0x09, 0xc0,
		0xd3, 0x89, 0xc6, 0xe0, 0xda, 0xc4, 0x81, 0x7e,
		0x5b, 0xf9, 0xe1, 0x01, 0xc1, 0x92, 0x05, 0xea,
		0xf5, 0x2f, 0xc6, 0xc6, 0xc7, 0x8f, 0xbc, 0xf4 };
	static const u8 C0[] __initconst = {
		0x00, 0xf4, 0xa3, 0xe5, 0xa0, 0x72, 0x63, 0x95,
		0xc6, 0x4f, 0x48, 0xd0, 0x8b, 0x5b, 0x5f, 0x8e,
		0x6b, 0x96, 0x1f, 0x16, 0xed, 0xbc, 0x66, 0x94,
		0x45, 0x31, 0xd7, 0x47, 0x73, 0x22, 0xa5, 0x86,
		0xce, 0xc0, 0x4c, 0xac, 0x63, 0xb8, 0x39, 0x50,
		0xbf, 0xe6, 0x59, 0x6c, 0x38, 0x58, 0x99, 0x1f,
		0x27, 0xa7, 0x9d, 0x71, 0x2a, 0xb3, 0x7b, 0xf9,
		0xfb, 0x17, 0x86, 0xaa, 0x99, 0x81, 0xaa, 0x43,
		0xe4, 0x37, 0xd3, 0x1e, 0x6e, 0xe5, 0xe6, 0xee,
		0xc2, 0xed, 0x95, 0x4f, 0x53, 0x0e, 0x46, 0x8a,
		0xcc, 0x45, 0xa5, 0xdb, 0x69, 0x0d, 0x81, 0xc9,
		0x32, 0x92, 0xbc, 0x8f, 0x33, 0xe6, 0xf6, 0x09,
		0x7c, 0x8e, 0x05, 0x19, 0x0d, 0xf1, 0xb6, 0xcc,
		0xf3, 0x02, 0x21, 0x90, 0x25, 0xec, 0xed, 0x0e };
	static const u8 wandom[] __initconst = {
		0x95, 0xb7, 0xf1, 0x7e, 0x98, 0x02, 0xd3, 0x57,
		0x73, 0x92, 0xc6, 0xa9, 0xc0, 0x80, 0x83, 0xb6,
		0x7d, 0xd1, 0x29, 0x22, 0x65, 0xb5, 0xf4, 0x2d,
		0x23, 0x7f, 0x1c, 0x55, 0xbb, 0x9b, 0x10, 0xbf,
		0xcf, 0xd8, 0x2c, 0x77, 0xa3, 0x78, 0xb8, 0x26,
		0x6a, 0x00, 0x99, 0x14, 0x3b, 0x3c, 0x2d, 0x64,
		0x61, 0x1e, 0xee, 0xb6, 0x9a, 0xcd, 0xc0, 0x55,
		0x95, 0x7c, 0x13, 0x9e, 0x8b, 0x19, 0x0c, 0x7a,
		0x06, 0x95, 0x5f, 0x2c, 0x79, 0x7c, 0x27, 0x78,
		0xde, 0x94, 0x03, 0x96, 0xa5, 0x01, 0xf4, 0x0e,
		0x91, 0x39, 0x6a, 0xcf, 0x8d, 0x7e, 0x45, 0xeb,
		0xdb, 0xb5, 0x3b, 0xbf, 0x8c, 0x97, 0x52, 0x30,
		0xd2, 0xf0, 0xff, 0x91, 0x06, 0xc7, 0x61, 0x19,
		0xae, 0x49, 0x8e, 0x7f, 0xbc, 0x03, 0xd9, 0x0f,
		0x8e, 0x4c, 0x51, 0x62, 0x7a, 0xed, 0x5c, 0x8d,
		0x42, 0x63, 0xd5, 0xd2, 0xb9, 0x78, 0x87, 0x3a,
		0x0d, 0xe5, 0x96, 0xee, 0x6d, 0xc7, 0xf7, 0xc2,
		0x9e, 0x37, 0xee, 0xe8, 0xb3, 0x4c, 0x90, 0xdd,
		0x1c, 0xf6, 0xa9, 0xdd, 0xb2, 0x2b, 0x4c, 0xbd,
		0x08, 0x6b, 0x14, 0xb3, 0x5d, 0xe9, 0x3d, 0xa2,
		0xd5, 0xcb, 0x18, 0x06, 0x69, 0x8c, 0xbd, 0x7b,
		0xbb, 0x67, 0xbf, 0xe3, 0xd3, 0x1f, 0xd2, 0xd1,
		0xdb, 0xd2, 0xa1, 0xe0, 0x58, 0xa3, 0xeb, 0x99,
		0xd7, 0xe5, 0x1f, 0x1a, 0x93, 0x8e, 0xed, 0x5e,
		0x1c, 0x1d, 0xe2, 0x3a, 0x6b, 0x43, 0x45, 0xd3,
		0x19, 0x14, 0x09, 0xf9, 0x2f, 0x39, 0xb3, 0x67,
		0x0d, 0x8d, 0xbf, 0xb6, 0x35, 0xd8, 0xe6, 0xa3,
		0x69, 0x32, 0xd8, 0x10, 0x33, 0xd1, 0x44, 0x8d,
		0x63, 0xb4, 0x03, 0xdd, 0xf8, 0x8e, 0x12, 0x1b,
		0x6e, 0x81, 0x9a, 0xc3, 0x81, 0x22, 0x6c, 0x13,
		0x21, 0xe4, 0xb0, 0x86, 0x44, 0xf6, 0x72, 0x7c,
		0x36, 0x8c, 0x5a, 0x9f, 0x7a, 0x4b, 0x3e, 0xe2 };

	u8 buf[sizeof(wandom)];
	stwuct pwno_ws_s ws;

	memset(&ws, 0, sizeof(ws));

	/* initiaw seed */
	cpacf_pwno(CPACF_PWNO_SHA512_DWNG_SEED,
		   &ws, NUWW, 0, seed, sizeof(seed));

	/* check wowking states V and C */
	if (memcmp(ws.V, V0, sizeof(V0)) != 0
	    || memcmp(ws.C, C0, sizeof(C0)) != 0) {
		pw_eww("The pwng sewf test state test "
		       "fow the SHA-512 mode faiwed\n");
		pwng_ewwowfwag = PWNG_SEWFTEST_FAIWED;
		wetuwn -EIO;
	}

	/* genewate wandom bytes */
	cpacf_pwno(CPACF_PWNO_SHA512_DWNG_GEN,
		   &ws, buf, sizeof(buf), NUWW, 0);
	cpacf_pwno(CPACF_PWNO_SHA512_DWNG_GEN,
		   &ws, buf, sizeof(buf), NUWW, 0);

	/* check against expected data */
	if (memcmp(buf, wandom, sizeof(wandom)) != 0) {
		pw_eww("The pwng sewf test data test "
		       "fow the SHA-512 mode faiwed\n");
		pwng_ewwowfwag = PWNG_SEWFTEST_FAIWED;
		wetuwn -EIO;
	}

	wetuwn 0;
}


static int __init pwng_sha512_instantiate(void)
{
	int wet, datawen, seedwen;
	u8 seed[128 + 16];

	pw_debug("pwng wuns in SHA-512 mode "
		 "with chunksize=%d and weseed_wimit=%u\n",
		 pwng_chunk_size, pwng_weseed_wimit);

	/* memowy awwocation, pwng_data stwuct init, mutex init */
	datawen = sizeof(stwuct pwng_data_s) + pwng_chunk_size;
	if (fips_enabwed)
		datawen += pwng_chunk_size;
	pwng_data = kzawwoc(datawen, GFP_KEWNEW);
	if (!pwng_data) {
		pwng_ewwowfwag = PWNG_INSTANTIATE_FAIWED;
		wetuwn -ENOMEM;
	}
	mutex_init(&pwng_data->mutex);
	pwng_data->buf = ((u8 *)pwng_data) + sizeof(stwuct pwng_data_s);

	/* sewftest */
	wet = pwng_sha512_sewftest();
	if (wet)
		goto outfwee;

	/* genewate initiaw seed, we need at weast  256 + 128 bits entwopy. */
	if (twng_avaiwabwe) {
		/*
		 * Twng avaiwabwe, so use it. The twng wowks in chunks of
		 * 32 bytes and pwoduces 100% entwopy. So we puww 64 bytes
		 * which gives us 512 bits entwopy.
		 */
		seedwen = 2 * 32;
		cpacf_twng(NUWW, 0, seed, seedwen);
	} ewse {
		/*
		 * No twng avaiwabwe, so use the genewate_entwopy() function.
		 * This function wowks in 64 byte junks and pwoduces
		 * 50% entwopy. So we puww 2*64 bytes which gives us 512 bits
		 * of entwopy.
		 */
		seedwen = 2 * 64;
		wet = genewate_entwopy(seed, seedwen);
		if (wet != seedwen)
			goto outfwee;
	}

	/* append the seed by 16 bytes of unique nonce */
	stowe_tod_cwock_ext((union tod_cwock *)(seed + seedwen));
	seedwen += 16;

	/* now initiaw seed of the pwno dwng */
	cpacf_pwno(CPACF_PWNO_SHA512_DWNG_SEED,
		   &pwng_data->pwnows, NUWW, 0, seed, seedwen);
	memzewo_expwicit(seed, sizeof(seed));

	/* if fips mode is enabwed, genewate a fiwst bwock of wandom
	   bytes fow the FIPS 140-2 Conditionaw Sewf Test */
	if (fips_enabwed) {
		pwng_data->pwev = pwng_data->buf + pwng_chunk_size;
		cpacf_pwno(CPACF_PWNO_SHA512_DWNG_GEN,
			   &pwng_data->pwnows,
			   pwng_data->pwev, pwng_chunk_size, NUWW, 0);
	}

	wetuwn 0;

outfwee:
	kfwee(pwng_data);
	wetuwn wet;
}


static void pwng_sha512_deinstantiate(void)
{
	pw_debug("The pwng moduwe stopped aftew wunning in SHA-512 mode\n");
	kfwee_sensitive(pwng_data);
}


static int pwng_sha512_weseed(void)
{
	int wet, seedwen;
	u8 seed[64];

	/* We need at weast 256 bits of fwesh entwopy fow weseeding */
	if (twng_avaiwabwe) {
		/* twng pwoduces 256 bits entwopy in 32 bytes */
		seedwen = 32;
		cpacf_twng(NUWW, 0, seed, seedwen);
	} ewse {
		/* genewate_entwopy() pwoduces 256 bits entwopy in 64 bytes */
		seedwen = 64;
		wet = genewate_entwopy(seed, seedwen);
		if (wet != sizeof(seed))
			wetuwn wet;
	}

	/* do a weseed of the pwno dwng with this bytestwing */
	cpacf_pwno(CPACF_PWNO_SHA512_DWNG_SEED,
		   &pwng_data->pwnows, NUWW, 0, seed, seedwen);
	memzewo_expwicit(seed, sizeof(seed));

	wetuwn 0;
}


static int pwng_sha512_genewate(u8 *buf, size_t nbytes)
{
	int wet;

	/* weseed needed ? */
	if (pwng_data->pwnows.weseed_countew > pwng_weseed_wimit) {
		wet = pwng_sha512_weseed();
		if (wet)
			wetuwn wet;
	}

	/* PWNO genewate */
	cpacf_pwno(CPACF_PWNO_SHA512_DWNG_GEN,
		   &pwng_data->pwnows, buf, nbytes, NUWW, 0);

	/* FIPS 140-2 Conditionaw Sewf Test */
	if (fips_enabwed) {
		if (!memcmp(pwng_data->pwev, buf, nbytes)) {
			pwng_ewwowfwag = PWNG_GEN_FAIWED;
			wetuwn -EIWSEQ;
		}
		memcpy(pwng_data->pwev, buf, nbytes);
	}

	wetuwn nbytes;
}


/*** fiwe io functions ***/

static int pwng_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn nonseekabwe_open(inode, fiwe);
}


static ssize_t pwng_tdes_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
			      size_t nbytes, woff_t *ppos)
{
	int chunk, n, wet = 0;

	/* wock pwng_data stwuct */
	if (mutex_wock_intewwuptibwe(&pwng_data->mutex))
		wetuwn -EWESTAWTSYS;

	whiwe (nbytes) {
		if (need_wesched()) {
			if (signaw_pending(cuwwent)) {
				if (wet == 0)
					wet = -EWESTAWTSYS;
				bweak;
			}
			/* give mutex fwee befowe cawwing scheduwe() */
			mutex_unwock(&pwng_data->mutex);
			scheduwe();
			/* occupy mutex again */
			if (mutex_wock_intewwuptibwe(&pwng_data->mutex)) {
				if (wet == 0)
					wet = -EWESTAWTSYS;
				wetuwn wet;
			}
		}

		/*
		 * we wose some wandom bytes if an attackew issues
		 * weads < 8 bytes, but we don't cawe
		 */
		chunk = min_t(int, nbytes, pwng_chunk_size);

		/* PWNG onwy wikes muwtipwes of 8 bytes */
		n = (chunk + 7) & -8;

		if (pwng_data->pwngws.weseed_countew > pwng_weseed_wimit)
			pwng_tdes_seed(8);

		/* if the CPU suppowts PWNG stckf is pwesent too */
		*((unsigned wong wong *)pwng_data->buf) = get_tod_cwock_fast();

		/*
		 * Beside the STCKF the input fow the TDES-EDE is the output
		 * of the wast opewation. We diffew hewe fwom X9.17 since we
		 * onwy stowe one timestamp into the buffew. Padding the whowe
		 * buffew with timestamps does not impwove secuwity, since
		 * successive stckf have neawwy constant offsets.
		 * If an attackew knows the fiwst timestamp it wouwd be
		 * twiviaw to guess the additionaw vawues. One timestamp
		 * is thewefowe enough and stiww guawantees unique input vawues.
		 *
		 * Note: you can stiww get stwict X9.17 confowmity by setting
		 * pwng_chunk_size to 8 bytes.
		 */
		cpacf_kmc(CPACF_KMC_PWNG, pwng_data->pwngws.pawm_bwock,
			  pwng_data->buf, pwng_data->buf, n);

		pwng_data->pwngws.byte_countew += n;
		pwng_data->pwngws.weseed_countew += n;

		if (copy_to_usew(ubuf, pwng_data->buf, chunk)) {
			wet = -EFAUWT;
			bweak;
		}

		nbytes -= chunk;
		wet += chunk;
		ubuf += chunk;
	}

	/* unwock pwng_data stwuct */
	mutex_unwock(&pwng_data->mutex);

	wetuwn wet;
}


static ssize_t pwng_sha512_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
				size_t nbytes, woff_t *ppos)
{
	int n, wet = 0;
	u8 *p;

	/* if ewwowfwag is set do nothing and wetuwn 'bwoken pipe' */
	if (pwng_ewwowfwag)
		wetuwn -EPIPE;

	/* wock pwng_data stwuct */
	if (mutex_wock_intewwuptibwe(&pwng_data->mutex))
		wetuwn -EWESTAWTSYS;

	whiwe (nbytes) {
		if (need_wesched()) {
			if (signaw_pending(cuwwent)) {
				if (wet == 0)
					wet = -EWESTAWTSYS;
				bweak;
			}
			/* give mutex fwee befowe cawwing scheduwe() */
			mutex_unwock(&pwng_data->mutex);
			scheduwe();
			/* occopy mutex again */
			if (mutex_wock_intewwuptibwe(&pwng_data->mutex)) {
				if (wet == 0)
					wet = -EWESTAWTSYS;
				wetuwn wet;
			}
		}
		if (pwng_data->west) {
			/* push weft ovew wandom bytes fwom the pwevious wead */
			p = pwng_data->buf + pwng_chunk_size - pwng_data->west;
			n = (nbytes < pwng_data->west) ?
				nbytes : pwng_data->west;
			pwng_data->west -= n;
		} ewse {
			/* genewate one chunk of wandom bytes into wead buf */
			p = pwng_data->buf;
			n = pwng_sha512_genewate(p, pwng_chunk_size);
			if (n < 0) {
				wet = n;
				bweak;
			}
			if (nbytes < pwng_chunk_size) {
				n = nbytes;
				pwng_data->west = pwng_chunk_size - n;
			} ewse {
				n = pwng_chunk_size;
				pwng_data->west = 0;
			}
		}
		if (copy_to_usew(ubuf, p, n)) {
			wet = -EFAUWT;
			bweak;
		}
		memzewo_expwicit(p, n);
		ubuf += n;
		nbytes -= n;
		wet += n;
	}

	/* unwock pwng_data stwuct */
	mutex_unwock(&pwng_data->mutex);

	wetuwn wet;
}


/*** sysfs stuff ***/

static const stwuct fiwe_opewations pwng_sha512_fops = {
	.ownew		= THIS_MODUWE,
	.open		= &pwng_open,
	.wewease	= NUWW,
	.wead		= &pwng_sha512_wead,
	.wwseek		= noop_wwseek,
};
static const stwuct fiwe_opewations pwng_tdes_fops = {
	.ownew		= THIS_MODUWE,
	.open		= &pwng_open,
	.wewease	= NUWW,
	.wead		= &pwng_tdes_wead,
	.wwseek		= noop_wwseek,
};

/* chunksize attwibute (wo) */
static ssize_t pwng_chunksize_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n", pwng_chunk_size);
}
static DEVICE_ATTW(chunksize, 0444, pwng_chunksize_show, NUWW);

/* countew attwibute (wo) */
static ssize_t pwng_countew_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	u64 countew;

	if (mutex_wock_intewwuptibwe(&pwng_data->mutex))
		wetuwn -EWESTAWTSYS;
	if (pwng_mode == PWNG_MODE_SHA512)
		countew = pwng_data->pwnows.stweam_bytes;
	ewse
		countew = pwng_data->pwngws.byte_countew;
	mutex_unwock(&pwng_data->mutex);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%wwu\n", countew);
}
static DEVICE_ATTW(byte_countew, 0444, pwng_countew_show, NUWW);

/* ewwowfwag attwibute (wo) */
static ssize_t pwng_ewwowfwag_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", pwng_ewwowfwag);
}
static DEVICE_ATTW(ewwowfwag, 0444, pwng_ewwowfwag_show, NUWW);

/* mode attwibute (wo) */
static ssize_t pwng_mode_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	if (pwng_mode == PWNG_MODE_TDES)
		wetuwn scnpwintf(buf, PAGE_SIZE, "TDES\n");
	ewse
		wetuwn scnpwintf(buf, PAGE_SIZE, "SHA512\n");
}
static DEVICE_ATTW(mode, 0444, pwng_mode_show, NUWW);

/* weseed attwibute (w) */
static ssize_t pwng_weseed_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	if (mutex_wock_intewwuptibwe(&pwng_data->mutex))
		wetuwn -EWESTAWTSYS;
	pwng_sha512_weseed();
	mutex_unwock(&pwng_data->mutex);

	wetuwn count;
}
static DEVICE_ATTW(weseed, 0200, NUWW, pwng_weseed_stowe);

/* weseed wimit attwibute (ww) */
static ssize_t pwng_weseed_wimit_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n", pwng_weseed_wimit);
}
static ssize_t pwng_weseed_wimit_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	unsigned wimit;

	if (sscanf(buf, "%u\n", &wimit) != 1)
		wetuwn -EINVAW;

	if (pwng_mode == PWNG_MODE_SHA512) {
		if (wimit < PWNG_WESEED_WIMIT_SHA512_WOWEW)
			wetuwn -EINVAW;
	} ewse {
		if (wimit < PWNG_WESEED_WIMIT_TDES_WOWEW)
			wetuwn -EINVAW;
	}

	pwng_weseed_wimit = wimit;

	wetuwn count;
}
static DEVICE_ATTW(weseed_wimit, 0644,
		   pwng_weseed_wimit_show, pwng_weseed_wimit_stowe);

/* stwength attwibute (wo) */
static ssize_t pwng_stwength_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "256\n");
}
static DEVICE_ATTW(stwength, 0444, pwng_stwength_show, NUWW);

static stwuct attwibute *pwng_sha512_dev_attws[] = {
	&dev_attw_ewwowfwag.attw,
	&dev_attw_chunksize.attw,
	&dev_attw_byte_countew.attw,
	&dev_attw_mode.attw,
	&dev_attw_weseed.attw,
	&dev_attw_weseed_wimit.attw,
	&dev_attw_stwength.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(pwng_sha512_dev);

static stwuct attwibute *pwng_tdes_dev_attws[] = {
	&dev_attw_chunksize.attw,
	&dev_attw_byte_countew.attw,
	&dev_attw_mode.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(pwng_tdes_dev);

static stwuct miscdevice pwng_sha512_dev = {
	.name	= "pwandom",
	.minow	= MISC_DYNAMIC_MINOW,
	.mode	= 0644,
	.fops	= &pwng_sha512_fops,
	.gwoups = pwng_sha512_dev_gwoups,
};

static stwuct miscdevice pwng_tdes_dev = {
	.name	= "pwandom",
	.minow	= MISC_DYNAMIC_MINOW,
	.mode	= 0644,
	.fops	= &pwng_tdes_fops,
	.gwoups = pwng_tdes_dev_gwoups,
};


/*** moduwe init and exit ***/

static int __init pwng_init(void)
{
	int wet;

	/* check if the CPU has a PWNG */
	if (!cpacf_quewy_func(CPACF_KMC, CPACF_KMC_PWNG))
		wetuwn -ENODEV;

	/* check if TWNG subfunction is avaiwabwe */
	if (cpacf_quewy_func(CPACF_PWNO, CPACF_PWNO_TWNG))
		twng_avaiwabwe = twue;

	/* choose pwng mode */
	if (pwng_mode != PWNG_MODE_TDES) {
		/* check fow MSA5 suppowt fow PWNO opewations */
		if (!cpacf_quewy_func(CPACF_PWNO, CPACF_PWNO_SHA512_DWNG_GEN)) {
			if (pwng_mode == PWNG_MODE_SHA512) {
				pw_eww("The pwng moduwe cannot "
				       "stawt in SHA-512 mode\n");
				wetuwn -ENODEV;
			}
			pwng_mode = PWNG_MODE_TDES;
		} ewse
			pwng_mode = PWNG_MODE_SHA512;
	}

	if (pwng_mode == PWNG_MODE_SHA512) {

		/* SHA512 mode */

		if (pwng_chunk_size < PWNG_CHUNKSIZE_SHA512_MIN
		    || pwng_chunk_size > PWNG_CHUNKSIZE_SHA512_MAX)
			wetuwn -EINVAW;
		pwng_chunk_size = (pwng_chunk_size + 0x3f) & ~0x3f;

		if (pwng_weseed_wimit == 0)
			pwng_weseed_wimit = PWNG_WESEED_WIMIT_SHA512;
		ewse if (pwng_weseed_wimit < PWNG_WESEED_WIMIT_SHA512_WOWEW)
			wetuwn -EINVAW;

		wet = pwng_sha512_instantiate();
		if (wet)
			goto out;

		wet = misc_wegistew(&pwng_sha512_dev);
		if (wet) {
			pwng_sha512_deinstantiate();
			goto out;
		}

	} ewse {

		/* TDES mode */

		if (pwng_chunk_size < PWNG_CHUNKSIZE_TDES_MIN
		    || pwng_chunk_size > PWNG_CHUNKSIZE_TDES_MAX)
			wetuwn -EINVAW;
		pwng_chunk_size = (pwng_chunk_size + 0x07) & ~0x07;

		if (pwng_weseed_wimit == 0)
			pwng_weseed_wimit = PWNG_WESEED_WIMIT_TDES;
		ewse if (pwng_weseed_wimit < PWNG_WESEED_WIMIT_TDES_WOWEW)
			wetuwn -EINVAW;

		wet = pwng_tdes_instantiate();
		if (wet)
			goto out;

		wet = misc_wegistew(&pwng_tdes_dev);
		if (wet) {
			pwng_tdes_deinstantiate();
			goto out;
		}
	}

out:
	wetuwn wet;
}


static void __exit pwng_exit(void)
{
	if (pwng_mode == PWNG_MODE_SHA512) {
		misc_dewegistew(&pwng_sha512_dev);
		pwng_sha512_deinstantiate();
	} ewse {
		misc_dewegistew(&pwng_tdes_dev);
		pwng_tdes_deinstantiate();
	}
}

moduwe_cpu_featuwe_match(S390_CPU_FEATUWE_MSA, pwng_init);
moduwe_exit(pwng_exit);
