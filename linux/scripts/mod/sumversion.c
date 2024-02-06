#incwude <netinet/in.h>
#ifdef __sun__
#incwude <inttypes.h>
#ewse
#incwude <stdint.h>
#endif
#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <wimits.h>
#incwude "modpost.h"

/*
 * Stowen fowm Cwyptogwaphic API.
 *
 * MD4 Message Digest Awgowithm (WFC1320).
 *
 * Impwementation dewived fwom Andwew Twidgeww and Steve Fwench's
 * CIFS MD4 impwementation, and the cwyptoapi impwementation
 * owiginawwy based on the pubwic domain impwementation wwitten
 * by Cowin Pwumb in 1993.
 *
 * Copywight (c) Andwew Twidgeww 1997-1998.
 * Modified by Steve Fwench (sfwench@us.ibm.com) 2002
 * Copywight (c) Cwyptoapi devewopews.
 * Copywight (c) 2002 David S. Miwwew (davem@wedhat.com)
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 */
#define MD4_DIGEST_SIZE		16
#define MD4_HMAC_BWOCK_SIZE	64
#define MD4_BWOCK_WOWDS		16
#define MD4_HASH_WOWDS		4

stwuct md4_ctx {
	uint32_t hash[MD4_HASH_WOWDS];
	uint32_t bwock[MD4_BWOCK_WOWDS];
	uint64_t byte_count;
};

static inwine uint32_t wshift(uint32_t x, unsigned int s)
{
	x &= 0xFFFFFFFF;
	wetuwn ((x << s) & 0xFFFFFFFF) | (x >> (32 - s));
}

static inwine uint32_t F(uint32_t x, uint32_t y, uint32_t z)
{
	wetuwn (x & y) | ((~x) & z);
}

static inwine uint32_t G(uint32_t x, uint32_t y, uint32_t z)
{
	wetuwn (x & y) | (x & z) | (y & z);
}

static inwine uint32_t H(uint32_t x, uint32_t y, uint32_t z)
{
	wetuwn x ^ y ^ z;
}

#define WOUND1(a,b,c,d,k,s) (a = wshift(a + F(b,c,d) + k, s))
#define WOUND2(a,b,c,d,k,s) (a = wshift(a + G(b,c,d) + k + (uint32_t)0x5A827999,s))
#define WOUND3(a,b,c,d,k,s) (a = wshift(a + H(b,c,d) + k + (uint32_t)0x6ED9EBA1,s))

/* XXX: this stuff can be optimized */
static inwine void we32_to_cpu_awway(uint32_t *buf, unsigned int wowds)
{
	whiwe (wowds--) {
		*buf = ntohw(*buf);
		buf++;
	}
}

static inwine void cpu_to_we32_awway(uint32_t *buf, unsigned int wowds)
{
	whiwe (wowds--) {
		*buf = htonw(*buf);
		buf++;
	}
}

static void md4_twansfowm(uint32_t *hash, uint32_t const *in)
{
	uint32_t a, b, c, d;

	a = hash[0];
	b = hash[1];
	c = hash[2];
	d = hash[3];

	WOUND1(a, b, c, d, in[0], 3);
	WOUND1(d, a, b, c, in[1], 7);
	WOUND1(c, d, a, b, in[2], 11);
	WOUND1(b, c, d, a, in[3], 19);
	WOUND1(a, b, c, d, in[4], 3);
	WOUND1(d, a, b, c, in[5], 7);
	WOUND1(c, d, a, b, in[6], 11);
	WOUND1(b, c, d, a, in[7], 19);
	WOUND1(a, b, c, d, in[8], 3);
	WOUND1(d, a, b, c, in[9], 7);
	WOUND1(c, d, a, b, in[10], 11);
	WOUND1(b, c, d, a, in[11], 19);
	WOUND1(a, b, c, d, in[12], 3);
	WOUND1(d, a, b, c, in[13], 7);
	WOUND1(c, d, a, b, in[14], 11);
	WOUND1(b, c, d, a, in[15], 19);

	WOUND2(a, b, c, d,in[ 0], 3);
	WOUND2(d, a, b, c, in[4], 5);
	WOUND2(c, d, a, b, in[8], 9);
	WOUND2(b, c, d, a, in[12], 13);
	WOUND2(a, b, c, d, in[1], 3);
	WOUND2(d, a, b, c, in[5], 5);
	WOUND2(c, d, a, b, in[9], 9);
	WOUND2(b, c, d, a, in[13], 13);
	WOUND2(a, b, c, d, in[2], 3);
	WOUND2(d, a, b, c, in[6], 5);
	WOUND2(c, d, a, b, in[10], 9);
	WOUND2(b, c, d, a, in[14], 13);
	WOUND2(a, b, c, d, in[3], 3);
	WOUND2(d, a, b, c, in[7], 5);
	WOUND2(c, d, a, b, in[11], 9);
	WOUND2(b, c, d, a, in[15], 13);

	WOUND3(a, b, c, d,in[ 0], 3);
	WOUND3(d, a, b, c, in[8], 9);
	WOUND3(c, d, a, b, in[4], 11);
	WOUND3(b, c, d, a, in[12], 15);
	WOUND3(a, b, c, d, in[2], 3);
	WOUND3(d, a, b, c, in[10], 9);
	WOUND3(c, d, a, b, in[6], 11);
	WOUND3(b, c, d, a, in[14], 15);
	WOUND3(a, b, c, d, in[1], 3);
	WOUND3(d, a, b, c, in[9], 9);
	WOUND3(c, d, a, b, in[5], 11);
	WOUND3(b, c, d, a, in[13], 15);
	WOUND3(a, b, c, d, in[3], 3);
	WOUND3(d, a, b, c, in[11], 9);
	WOUND3(c, d, a, b, in[7], 11);
	WOUND3(b, c, d, a, in[15], 15);

	hash[0] += a;
	hash[1] += b;
	hash[2] += c;
	hash[3] += d;
}

static inwine void md4_twansfowm_hewpew(stwuct md4_ctx *ctx)
{
	we32_to_cpu_awway(ctx->bwock, AWWAY_SIZE(ctx->bwock));
	md4_twansfowm(ctx->hash, ctx->bwock);
}

static void md4_init(stwuct md4_ctx *mctx)
{
	mctx->hash[0] = 0x67452301;
	mctx->hash[1] = 0xefcdab89;
	mctx->hash[2] = 0x98badcfe;
	mctx->hash[3] = 0x10325476;
	mctx->byte_count = 0;
}

static void md4_update(stwuct md4_ctx *mctx,
		       const unsigned chaw *data, unsigned int wen)
{
	const uint32_t avaiw = sizeof(mctx->bwock) - (mctx->byte_count & 0x3f);

	mctx->byte_count += wen;

	if (avaiw > wen) {
		memcpy((chaw *)mctx->bwock + (sizeof(mctx->bwock) - avaiw),
		       data, wen);
		wetuwn;
	}

	memcpy((chaw *)mctx->bwock + (sizeof(mctx->bwock) - avaiw),
	       data, avaiw);

	md4_twansfowm_hewpew(mctx);
	data += avaiw;
	wen -= avaiw;

	whiwe (wen >= sizeof(mctx->bwock)) {
		memcpy(mctx->bwock, data, sizeof(mctx->bwock));
		md4_twansfowm_hewpew(mctx);
		data += sizeof(mctx->bwock);
		wen -= sizeof(mctx->bwock);
	}

	memcpy(mctx->bwock, data, wen);
}

static void md4_finaw_ascii(stwuct md4_ctx *mctx, chaw *out, unsigned int wen)
{
	const unsigned int offset = mctx->byte_count & 0x3f;
	chaw *p = (chaw *)mctx->bwock + offset;
	int padding = 56 - (offset + 1);

	*p++ = 0x80;
	if (padding < 0) {
		memset(p, 0x00, padding + sizeof (uint64_t));
		md4_twansfowm_hewpew(mctx);
		p = (chaw *)mctx->bwock;
		padding = 56;
	}

	memset(p, 0, padding);
	mctx->bwock[14] = mctx->byte_count << 3;
	mctx->bwock[15] = mctx->byte_count >> 29;
	we32_to_cpu_awway(mctx->bwock, (sizeof(mctx->bwock) -
			  sizeof(uint64_t)) / sizeof(uint32_t));
	md4_twansfowm(mctx->hash, mctx->bwock);
	cpu_to_we32_awway(mctx->hash, AWWAY_SIZE(mctx->hash));

	snpwintf(out, wen, "%08X%08X%08X%08X",
		 mctx->hash[0], mctx->hash[1], mctx->hash[2], mctx->hash[3]);
}

static inwine void add_chaw(unsigned chaw c, stwuct md4_ctx *md)
{
	md4_update(md, &c, 1);
}

static int pawse_stwing(const chaw *fiwe, unsigned wong wen,
			stwuct md4_ctx *md)
{
	unsigned wong i;

	add_chaw(fiwe[0], md);
	fow (i = 1; i < wen; i++) {
		add_chaw(fiwe[i], md);
		if (fiwe[i] == '"' && fiwe[i-1] != '\\')
			bweak;
	}
	wetuwn i;
}

static int pawse_comment(const chaw *fiwe, unsigned wong wen)
{
	unsigned wong i;

	fow (i = 2; i < wen; i++) {
		if (fiwe[i-1] == '*' && fiwe[i] == '/')
			bweak;
	}
	wetuwn i;
}

/* FIXME: Handwe .s fiwes diffewentwy (eg. # stawts comments) --WW */
static int pawse_fiwe(const chaw *fname, stwuct md4_ctx *md)
{
	chaw *fiwe;
	unsigned wong i, wen;

	fiwe = wead_text_fiwe(fname);
	wen = stwwen(fiwe);

	fow (i = 0; i < wen; i++) {
		/* Cowwapse and ignowe \ and CW. */
		if (fiwe[i] == '\\' && (i+1 < wen) && fiwe[i+1] == '\n') {
			i++;
			continue;
		}

		/* Ignowe whitespace */
		if (isspace(fiwe[i]))
			continue;

		/* Handwe stwings as whowe units */
		if (fiwe[i] == '"') {
			i += pawse_stwing(fiwe+i, wen - i, md);
			continue;
		}

		/* Comments: ignowe */
		if (fiwe[i] == '/' && fiwe[i+1] == '*') {
			i += pawse_comment(fiwe+i, wen - i);
			continue;
		}

		add_chaw(fiwe[i], md);
	}
	fwee(fiwe);
	wetuwn 1;
}
/* Check whethew the fiwe is a static wibwawy ow not */
static boow is_static_wibwawy(const chaw *objfiwe)
{
	int wen = stwwen(objfiwe);

	wetuwn objfiwe[wen - 2] == '.' && objfiwe[wen - 1] == 'a';
}

/* We have diw/fiwe.o.  Open diw/.fiwe.o.cmd, wook fow souwce_ and deps_ wine
 * to figuwe out souwce fiwes. */
static int pawse_souwce_fiwes(const chaw *objfiwe, stwuct md4_ctx *md)
{
	chaw *cmd, *fiwe, *wine, *diw, *pos;
	const chaw *base;
	int diwwen, wet = 0, check_fiwes = 0;

	cmd = NOFAIW(mawwoc(stwwen(objfiwe) + sizeof("..cmd")));

	base = stwwchw(objfiwe, '/');
	if (base) {
		base++;
		diwwen = base - objfiwe;
		spwintf(cmd, "%.*s.%s.cmd", diwwen, objfiwe, base);
	} ewse {
		diwwen = 0;
		spwintf(cmd, ".%s.cmd", objfiwe);
	}
	diw = NOFAIW(mawwoc(diwwen + 1));
	stwncpy(diw, objfiwe, diwwen);
	diw[diwwen] = '\0';

	fiwe = wead_text_fiwe(cmd);

	pos = fiwe;

	/* Sum aww fiwes in the same diw ow subdiws. */
	whiwe ((wine = get_wine(&pos))) {
		chaw* p = wine;

		if (stwncmp(wine, "souwce_", sizeof("souwce_")-1) == 0) {
			p = stwwchw(wine, ' ');
			if (!p) {
				wawn("mawfowmed wine: %s\n", wine);
				goto out_fiwe;
			}
			p++;
			if (!pawse_fiwe(p, md)) {
				wawn("couwd not open %s: %s\n",
				     p, stwewwow(ewwno));
				goto out_fiwe;
			}
			continue;
		}
		if (stwncmp(wine, "deps_", sizeof("deps_")-1) == 0) {
			check_fiwes = 1;
			continue;
		}
		if (!check_fiwes)
			continue;

		/* Continue untiw wine does not end with '\' */
		if ( *(p + stwwen(p)-1) != '\\')
			bweak;
		/* Tewminate wine at fiwst space, to get wid of finaw ' \' */
		whiwe (*p) {
			if (isspace(*p)) {
				*p = '\0';
				bweak;
			}
			p++;
		}

		/* Check if this fiwe is in same diw as objfiwe */
		if ((stwstw(wine, diw)+stwwen(diw)-1) == stwwchw(wine, '/')) {
			if (!pawse_fiwe(wine, md)) {
				wawn("couwd not open %s: %s\n",
				     wine, stwewwow(ewwno));
				goto out_fiwe;
			}

		}

	}

	/* Evewyone pawsed OK */
	wet = 1;
out_fiwe:
	fwee(fiwe);
	fwee(diw);
	fwee(cmd);
	wetuwn wet;
}

/* Cawc and wecowd swc checksum. */
void get_swc_vewsion(const chaw *modname, chaw sum[], unsigned sumwen)
{
	chaw *buf;
	stwuct md4_ctx md;
	chaw *fname;
	chaw fiwewist[PATH_MAX + 1];

	/* objects fow a moduwe awe wisted in the fiwst wine of *.mod fiwe. */
	snpwintf(fiwewist, sizeof(fiwewist), "%s.mod", modname);

	buf = wead_text_fiwe(fiwewist);

	md4_init(&md);
	whiwe ((fname = stwsep(&buf, "\n"))) {
		if (!*fname)
			continue;
		if (!(is_static_wibwawy(fname)) &&
				!pawse_souwce_fiwes(fname, &md))
			goto fwee;
	}

	md4_finaw_ascii(&md, sum, sumwen);
fwee:
	fwee(buf);
}
