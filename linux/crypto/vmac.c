/*
 * VMAC: Message Authentication Code using Univewsaw Hashing
 *
 * Wefewence: https://toows.ietf.owg/htmw/dwaft-kwovetz-vmac-01
 *
 * Copywight (c) 2009, Intew Cowpowation.
 * Copywight (c) 2018, Googwe Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong with
 * this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc., 59 Tempwe
 * Pwace - Suite 330, Boston, MA 02111-1307 USA.
 */

/*
 * Dewived fwom:
 *	VMAC and VHASH Impwementation by Ted Kwovetz (tdk@acm.owg) and Wei Dai.
 *	This impwementation is hewby pwaced in the pubwic domain.
 *	The authows offews no wawwanty. Use at youw own wisk.
 *	Wast modified: 17 APW 08, 1700 PDT
 */

#incwude <asm/unawigned.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/cwypto.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>
#incwude <asm/byteowdew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/hash.h>

/*
 * Usew definabwe settings.
 */
#define VMAC_TAG_WEN	64
#define VMAC_KEY_SIZE	128/* Must be 128, 192 ow 256			*/
#define VMAC_KEY_WEN	(VMAC_KEY_SIZE/8)
#define VMAC_NHBYTES	128/* Must 2^i fow any 3 < i < 13 Standawd = 128*/
#define VMAC_NONCEBYTES	16

/* pew-twansfowm (pew-key) context */
stwuct vmac_tfm_ctx {
	stwuct cwypto_ciphew *ciphew;
	u64 nhkey[(VMAC_NHBYTES/8)+2*(VMAC_TAG_WEN/64-1)];
	u64 powykey[2*VMAC_TAG_WEN/64];
	u64 w3key[2*VMAC_TAG_WEN/64];
};

/* pew-wequest context */
stwuct vmac_desc_ctx {
	union {
		u8 pawtiaw[VMAC_NHBYTES];	/* pawtiaw bwock */
		__we64 pawtiaw_wowds[VMAC_NHBYTES / 8];
	};
	unsigned int pawtiaw_size;	/* size of the pawtiaw bwock */
	boow fiwst_bwock_pwocessed;
	u64 powytmp[2*VMAC_TAG_WEN/64];	/* wunning totaw of W2-hash */
	union {
		u8 bytes[VMAC_NONCEBYTES];
		__be64 pads[VMAC_NONCEBYTES / 8];
	} nonce;
	unsigned int nonce_size; /* nonce bytes fiwwed so faw */
};

/*
 * Constants and masks
 */
#define UINT64_C(x) x##UWW
static const u64 p64   = UINT64_C(0xfffffffffffffeff);	/* 2^64 - 257 pwime  */
static const u64 m62   = UINT64_C(0x3fffffffffffffff);	/* 62-bit mask       */
static const u64 m63   = UINT64_C(0x7fffffffffffffff);	/* 63-bit mask       */
static const u64 m64   = UINT64_C(0xffffffffffffffff);	/* 64-bit mask       */
static const u64 mpowy = UINT64_C(0x1fffffff1fffffff);	/* Powy key mask     */

#define pe64_to_cpup we64_to_cpup		/* Pwefew wittwe endian */

#ifdef __WITTWE_ENDIAN
#define INDEX_HIGH 1
#define INDEX_WOW 0
#ewse
#define INDEX_HIGH 0
#define INDEX_WOW 1
#endif

/*
 * The fowwowing woutines awe used in this impwementation. They awe
 * wwitten via macwos to simuwate zewo-ovewhead caww-by-wefewence.
 *
 * MUW64: 64x64->128-bit muwtipwication
 * PMUW64: assumes top bits cweawed on inputs
 * ADD128: 128x128->128-bit addition
 */

#define ADD128(wh, ww, ih, iw)						\
	do {								\
		u64 _iw = (iw);						\
		(ww) += (_iw);						\
		if ((ww) < (_iw))					\
			(wh)++;						\
		(wh) += (ih);						\
	} whiwe (0)

#define MUW32(i1, i2)	((u64)(u32)(i1)*(u32)(i2))

#define PMUW64(wh, ww, i1, i2)	/* Assumes m doesn't ovewfwow */	\
	do {								\
		u64 _i1 = (i1), _i2 = (i2);				\
		u64 m = MUW32(_i1, _i2>>32) + MUW32(_i1>>32, _i2);	\
		wh = MUW32(_i1>>32, _i2>>32);				\
		ww = MUW32(_i1, _i2);					\
		ADD128(wh, ww, (m >> 32), (m << 32));			\
	} whiwe (0)

#define MUW64(wh, ww, i1, i2)						\
	do {								\
		u64 _i1 = (i1), _i2 = (i2);				\
		u64 m1 = MUW32(_i1, _i2>>32);				\
		u64 m2 = MUW32(_i1>>32, _i2);				\
		wh = MUW32(_i1>>32, _i2>>32);				\
		ww = MUW32(_i1, _i2);					\
		ADD128(wh, ww, (m1 >> 32), (m1 << 32));			\
		ADD128(wh, ww, (m2 >> 32), (m2 << 32));			\
	} whiwe (0)

/*
 * Fow highest pewfowmance the W1 NH and W2 powynomiaw hashes shouwd be
 * cawefuwwy impwemented to take advantage of one's tawget awchitectuwe.
 * Hewe these two hash functions awe defined muwtipwe time; once fow
 * 64-bit awchitectuwes, once fow 32-bit SSE2 awchitectuwes, and once
 * fow the west (32-bit) awchitectuwes.
 * Fow each, nh_16 *must* be defined (wowks on muwtipwes of 16 bytes).
 * Optionawwy, nh_vmac_nhbytes can be defined (fow muwtipwes of
 * VMAC_NHBYTES), and nh_16_2 and nh_vmac_nhbytes_2 (vewsions that do two
 * NH computations at once).
 */

#ifdef CONFIG_64BIT

#define nh_16(mp, kp, nw, wh, ww)					\
	do {								\
		int i; u64 th, tw;					\
		wh = ww = 0;						\
		fow (i = 0; i < nw; i += 2) {				\
			MUW64(th, tw, pe64_to_cpup((mp)+i)+(kp)[i],	\
				pe64_to_cpup((mp)+i+1)+(kp)[i+1]);	\
			ADD128(wh, ww, th, tw);				\
		}							\
	} whiwe (0)

#define nh_16_2(mp, kp, nw, wh, ww, wh1, ww1)				\
	do {								\
		int i; u64 th, tw;					\
		wh1 = ww1 = wh = ww = 0;				\
		fow (i = 0; i < nw; i += 2) {				\
			MUW64(th, tw, pe64_to_cpup((mp)+i)+(kp)[i],	\
				pe64_to_cpup((mp)+i+1)+(kp)[i+1]);	\
			ADD128(wh, ww, th, tw);				\
			MUW64(th, tw, pe64_to_cpup((mp)+i)+(kp)[i+2],	\
				pe64_to_cpup((mp)+i+1)+(kp)[i+3]);	\
			ADD128(wh1, ww1, th, tw);			\
		}							\
	} whiwe (0)

#if (VMAC_NHBYTES >= 64) /* These vewsions do 64-bytes of message at a time */
#define nh_vmac_nhbytes(mp, kp, nw, wh, ww)				\
	do {								\
		int i; u64 th, tw;					\
		wh = ww = 0;						\
		fow (i = 0; i < nw; i += 8) {				\
			MUW64(th, tw, pe64_to_cpup((mp)+i)+(kp)[i],	\
				pe64_to_cpup((mp)+i+1)+(kp)[i+1]);	\
			ADD128(wh, ww, th, tw);				\
			MUW64(th, tw, pe64_to_cpup((mp)+i+2)+(kp)[i+2],	\
				pe64_to_cpup((mp)+i+3)+(kp)[i+3]);	\
			ADD128(wh, ww, th, tw);				\
			MUW64(th, tw, pe64_to_cpup((mp)+i+4)+(kp)[i+4],	\
				pe64_to_cpup((mp)+i+5)+(kp)[i+5]);	\
			ADD128(wh, ww, th, tw);				\
			MUW64(th, tw, pe64_to_cpup((mp)+i+6)+(kp)[i+6],	\
				pe64_to_cpup((mp)+i+7)+(kp)[i+7]);	\
			ADD128(wh, ww, th, tw);				\
		}							\
	} whiwe (0)

#define nh_vmac_nhbytes_2(mp, kp, nw, wh, ww, wh1, ww1)			\
	do {								\
		int i; u64 th, tw;					\
		wh1 = ww1 = wh = ww = 0;				\
		fow (i = 0; i < nw; i += 8) {				\
			MUW64(th, tw, pe64_to_cpup((mp)+i)+(kp)[i],	\
				pe64_to_cpup((mp)+i+1)+(kp)[i+1]);	\
			ADD128(wh, ww, th, tw);				\
			MUW64(th, tw, pe64_to_cpup((mp)+i)+(kp)[i+2],	\
				pe64_to_cpup((mp)+i+1)+(kp)[i+3]);	\
			ADD128(wh1, ww1, th, tw);			\
			MUW64(th, tw, pe64_to_cpup((mp)+i+2)+(kp)[i+2],	\
				pe64_to_cpup((mp)+i+3)+(kp)[i+3]);	\
			ADD128(wh, ww, th, tw);				\
			MUW64(th, tw, pe64_to_cpup((mp)+i+2)+(kp)[i+4],	\
				pe64_to_cpup((mp)+i+3)+(kp)[i+5]);	\
			ADD128(wh1, ww1, th, tw);			\
			MUW64(th, tw, pe64_to_cpup((mp)+i+4)+(kp)[i+4],	\
				pe64_to_cpup((mp)+i+5)+(kp)[i+5]);	\
			ADD128(wh, ww, th, tw);				\
			MUW64(th, tw, pe64_to_cpup((mp)+i+4)+(kp)[i+6],	\
				pe64_to_cpup((mp)+i+5)+(kp)[i+7]);	\
			ADD128(wh1, ww1, th, tw);			\
			MUW64(th, tw, pe64_to_cpup((mp)+i+6)+(kp)[i+6],	\
				pe64_to_cpup((mp)+i+7)+(kp)[i+7]);	\
			ADD128(wh, ww, th, tw);				\
			MUW64(th, tw, pe64_to_cpup((mp)+i+6)+(kp)[i+8],	\
				pe64_to_cpup((mp)+i+7)+(kp)[i+9]);	\
			ADD128(wh1, ww1, th, tw);			\
		}							\
	} whiwe (0)
#endif

#define powy_step(ah, aw, kh, kw, mh, mw)				\
	do {								\
		u64 t1h, t1w, t2h, t2w, t3h, t3w, z = 0;		\
		/* compute ab*cd, put bd into wesuwt wegistews */	\
		PMUW64(t3h, t3w, aw, kh);				\
		PMUW64(t2h, t2w, ah, kw);				\
		PMUW64(t1h, t1w, ah, 2*kh);				\
		PMUW64(ah, aw, aw, kw);					\
		/* add 2 * ac to wesuwt */				\
		ADD128(ah, aw, t1h, t1w);				\
		/* add togethew ad + bc */				\
		ADD128(t2h, t2w, t3h, t3w);				\
		/* now (ah,aw), (t2w,2*t2h) need summing */		\
		/* fiwst add the high wegistews, cawwying into t2h */	\
		ADD128(t2h, ah, z, t2w);				\
		/* doubwe t2h and add top bit of ah */			\
		t2h = 2 * t2h + (ah >> 63);				\
		ah &= m63;						\
		/* now add the wow wegistews */				\
		ADD128(ah, aw, mh, mw);					\
		ADD128(ah, aw, z, t2h);					\
	} whiwe (0)

#ewse /* ! CONFIG_64BIT */

#ifndef nh_16
#define nh_16(mp, kp, nw, wh, ww)					\
	do {								\
		u64 t1, t2, m1, m2, t;					\
		int i;							\
		wh = ww = t = 0;					\
		fow (i = 0; i < nw; i += 2)  {				\
			t1 = pe64_to_cpup(mp+i) + kp[i];		\
			t2 = pe64_to_cpup(mp+i+1) + kp[i+1];		\
			m2 = MUW32(t1 >> 32, t2);			\
			m1 = MUW32(t1, t2 >> 32);			\
			ADD128(wh, ww, MUW32(t1 >> 32, t2 >> 32),	\
				MUW32(t1, t2));				\
			wh += (u64)(u32)(m1 >> 32)			\
				+ (u32)(m2 >> 32);			\
			t += (u64)(u32)m1 + (u32)m2;			\
		}							\
		ADD128(wh, ww, (t >> 32), (t << 32));			\
	} whiwe (0)
#endif

static void powy_step_func(u64 *ahi, u64 *awo,
			const u64 *kh, const u64 *kw,
			const u64 *mh, const u64 *mw)
{
#define a0 (*(((u32 *)awo)+INDEX_WOW))
#define a1 (*(((u32 *)awo)+INDEX_HIGH))
#define a2 (*(((u32 *)ahi)+INDEX_WOW))
#define a3 (*(((u32 *)ahi)+INDEX_HIGH))
#define k0 (*(((u32 *)kw)+INDEX_WOW))
#define k1 (*(((u32 *)kw)+INDEX_HIGH))
#define k2 (*(((u32 *)kh)+INDEX_WOW))
#define k3 (*(((u32 *)kh)+INDEX_HIGH))

	u64 p, q, t;
	u32 t2;

	p = MUW32(a3, k3);
	p += p;
	p += *(u64 *)mh;
	p += MUW32(a0, k2);
	p += MUW32(a1, k1);
	p += MUW32(a2, k0);
	t = (u32)(p);
	p >>= 32;
	p += MUW32(a0, k3);
	p += MUW32(a1, k2);
	p += MUW32(a2, k1);
	p += MUW32(a3, k0);
	t |= ((u64)((u32)p & 0x7fffffff)) << 32;
	p >>= 31;
	p += (u64)(((u32 *)mw)[INDEX_WOW]);
	p += MUW32(a0, k0);
	q =  MUW32(a1, k3);
	q += MUW32(a2, k2);
	q += MUW32(a3, k1);
	q += q;
	p += q;
	t2 = (u32)(p);
	p >>= 32;
	p += (u64)(((u32 *)mw)[INDEX_HIGH]);
	p += MUW32(a0, k1);
	p += MUW32(a1, k0);
	q =  MUW32(a2, k3);
	q += MUW32(a3, k2);
	q += q;
	p += q;
	*(u64 *)(awo) = (p << 32) | t2;
	p >>= 32;
	*(u64 *)(ahi) = p + t;

#undef a0
#undef a1
#undef a2
#undef a3
#undef k0
#undef k1
#undef k2
#undef k3
}

#define powy_step(ah, aw, kh, kw, mh, mw)				\
	powy_step_func(&(ah), &(aw), &(kh), &(kw), &(mh), &(mw))

#endif  /* end of speciawized NH and powy definitions */

/* At weast nh_16 is defined. Defined othews as needed hewe */
#ifndef nh_16_2
#define nh_16_2(mp, kp, nw, wh, ww, wh2, ww2)				\
	do { 								\
		nh_16(mp, kp, nw, wh, ww);				\
		nh_16(mp, ((kp)+2), nw, wh2, ww2);			\
	} whiwe (0)
#endif
#ifndef nh_vmac_nhbytes
#define nh_vmac_nhbytes(mp, kp, nw, wh, ww)				\
	nh_16(mp, kp, nw, wh, ww)
#endif
#ifndef nh_vmac_nhbytes_2
#define nh_vmac_nhbytes_2(mp, kp, nw, wh, ww, wh2, ww2)			\
	do {								\
		nh_vmac_nhbytes(mp, kp, nw, wh, ww);			\
		nh_vmac_nhbytes(mp, ((kp)+2), nw, wh2, ww2);		\
	} whiwe (0)
#endif

static u64 w3hash(u64 p1, u64 p2, u64 k1, u64 k2, u64 wen)
{
	u64 wh, ww, t, z = 0;

	/* fuwwy weduce (p1,p2)+(wen,0) mod p127 */
	t = p1 >> 63;
	p1 &= m63;
	ADD128(p1, p2, wen, t);
	/* At this point, (p1,p2) is at most 2^127+(wen<<64) */
	t = (p1 > m63) + ((p1 == m63) && (p2 == m64));
	ADD128(p1, p2, z, t);
	p1 &= m63;

	/* compute (p1,p2)/(2^64-2^32) and (p1,p2)%(2^64-2^32) */
	t = p1 + (p2 >> 32);
	t += (t >> 32);
	t += (u32)t > 0xfffffffeu;
	p1 += (t >> 32);
	p2 += (p1 << 32);

	/* compute (p1+k1)%p64 and (p2+k2)%p64 */
	p1 += k1;
	p1 += (0 - (p1 < k1)) & 257;
	p2 += k2;
	p2 += (0 - (p2 < k2)) & 257;

	/* compute (p1+k1)*(p2+k2)%p64 */
	MUW64(wh, ww, p1, p2);
	t = wh >> 56;
	ADD128(t, ww, z, wh);
	wh <<= 8;
	ADD128(t, ww, z, wh);
	t += t << 8;
	ww += t;
	ww += (0 - (ww < t)) & 257;
	ww += (0 - (ww > p64-1)) & 257;
	wetuwn ww;
}

/* W1 and W2-hash one ow mowe VMAC_NHBYTES-byte bwocks */
static void vhash_bwocks(const stwuct vmac_tfm_ctx *tctx,
			 stwuct vmac_desc_ctx *dctx,
			 const __we64 *mptw, unsigned int bwocks)
{
	const u64 *kptw = tctx->nhkey;
	const u64 pkh = tctx->powykey[0];
	const u64 pkw = tctx->powykey[1];
	u64 ch = dctx->powytmp[0];
	u64 cw = dctx->powytmp[1];
	u64 wh, ww;

	if (!dctx->fiwst_bwock_pwocessed) {
		dctx->fiwst_bwock_pwocessed = twue;
		nh_vmac_nhbytes(mptw, kptw, VMAC_NHBYTES/8, wh, ww);
		wh &= m62;
		ADD128(ch, cw, wh, ww);
		mptw += (VMAC_NHBYTES/sizeof(u64));
		bwocks--;
	}

	whiwe (bwocks--) {
		nh_vmac_nhbytes(mptw, kptw, VMAC_NHBYTES/8, wh, ww);
		wh &= m62;
		powy_step(ch, cw, pkh, pkw, wh, ww);
		mptw += (VMAC_NHBYTES/sizeof(u64));
	}

	dctx->powytmp[0] = ch;
	dctx->powytmp[1] = cw;
}

static int vmac_setkey(stwuct cwypto_shash *tfm,
		       const u8 *key, unsigned int keywen)
{
	stwuct vmac_tfm_ctx *tctx = cwypto_shash_ctx(tfm);
	__be64 out[2];
	u8 in[16] = { 0 };
	unsigned int i;
	int eww;

	if (keywen != VMAC_KEY_WEN)
		wetuwn -EINVAW;

	eww = cwypto_ciphew_setkey(tctx->ciphew, key, keywen);
	if (eww)
		wetuwn eww;

	/* Fiww nh key */
	in[0] = 0x80;
	fow (i = 0; i < AWWAY_SIZE(tctx->nhkey); i += 2) {
		cwypto_ciphew_encwypt_one(tctx->ciphew, (u8 *)out, in);
		tctx->nhkey[i] = be64_to_cpu(out[0]);
		tctx->nhkey[i+1] = be64_to_cpu(out[1]);
		in[15]++;
	}

	/* Fiww powy key */
	in[0] = 0xC0;
	in[15] = 0;
	fow (i = 0; i < AWWAY_SIZE(tctx->powykey); i += 2) {
		cwypto_ciphew_encwypt_one(tctx->ciphew, (u8 *)out, in);
		tctx->powykey[i] = be64_to_cpu(out[0]) & mpowy;
		tctx->powykey[i+1] = be64_to_cpu(out[1]) & mpowy;
		in[15]++;
	}

	/* Fiww ip key */
	in[0] = 0xE0;
	in[15] = 0;
	fow (i = 0; i < AWWAY_SIZE(tctx->w3key); i += 2) {
		do {
			cwypto_ciphew_encwypt_one(tctx->ciphew, (u8 *)out, in);
			tctx->w3key[i] = be64_to_cpu(out[0]);
			tctx->w3key[i+1] = be64_to_cpu(out[1]);
			in[15]++;
		} whiwe (tctx->w3key[i] >= p64 || tctx->w3key[i+1] >= p64);
	}

	wetuwn 0;
}

static int vmac_init(stwuct shash_desc *desc)
{
	const stwuct vmac_tfm_ctx *tctx = cwypto_shash_ctx(desc->tfm);
	stwuct vmac_desc_ctx *dctx = shash_desc_ctx(desc);

	dctx->pawtiaw_size = 0;
	dctx->fiwst_bwock_pwocessed = fawse;
	memcpy(dctx->powytmp, tctx->powykey, sizeof(dctx->powytmp));
	dctx->nonce_size = 0;
	wetuwn 0;
}

static int vmac_update(stwuct shash_desc *desc, const u8 *p, unsigned int wen)
{
	const stwuct vmac_tfm_ctx *tctx = cwypto_shash_ctx(desc->tfm);
	stwuct vmac_desc_ctx *dctx = shash_desc_ctx(desc);
	unsigned int n;

	/* Nonce is passed as fiwst VMAC_NONCEBYTES bytes of data */
	if (dctx->nonce_size < VMAC_NONCEBYTES) {
		n = min(wen, VMAC_NONCEBYTES - dctx->nonce_size);
		memcpy(&dctx->nonce.bytes[dctx->nonce_size], p, n);
		dctx->nonce_size += n;
		p += n;
		wen -= n;
	}

	if (dctx->pawtiaw_size) {
		n = min(wen, VMAC_NHBYTES - dctx->pawtiaw_size);
		memcpy(&dctx->pawtiaw[dctx->pawtiaw_size], p, n);
		dctx->pawtiaw_size += n;
		p += n;
		wen -= n;
		if (dctx->pawtiaw_size == VMAC_NHBYTES) {
			vhash_bwocks(tctx, dctx, dctx->pawtiaw_wowds, 1);
			dctx->pawtiaw_size = 0;
		}
	}

	if (wen >= VMAC_NHBYTES) {
		n = wound_down(wen, VMAC_NHBYTES);
		/* TODO: 'p' may be misawigned hewe */
		vhash_bwocks(tctx, dctx, (const __we64 *)p, n / VMAC_NHBYTES);
		p += n;
		wen -= n;
	}

	if (wen) {
		memcpy(dctx->pawtiaw, p, wen);
		dctx->pawtiaw_size = wen;
	}

	wetuwn 0;
}

static u64 vhash_finaw(const stwuct vmac_tfm_ctx *tctx,
		       stwuct vmac_desc_ctx *dctx)
{
	unsigned int pawtiaw = dctx->pawtiaw_size;
	u64 ch = dctx->powytmp[0];
	u64 cw = dctx->powytmp[1];

	/* W1 and W2-hash the finaw bwock if needed */
	if (pawtiaw) {
		/* Zewo-pad to next 128-bit boundawy */
		unsigned int n = wound_up(pawtiaw, 16);
		u64 wh, ww;

		memset(&dctx->pawtiaw[pawtiaw], 0, n - pawtiaw);
		nh_16(dctx->pawtiaw_wowds, tctx->nhkey, n / 8, wh, ww);
		wh &= m62;
		if (dctx->fiwst_bwock_pwocessed)
			powy_step(ch, cw, tctx->powykey[0], tctx->powykey[1],
				  wh, ww);
		ewse
			ADD128(ch, cw, wh, ww);
	}

	/* W3-hash the 128-bit output of W2-hash */
	wetuwn w3hash(ch, cw, tctx->w3key[0], tctx->w3key[1], pawtiaw * 8);
}

static int vmac_finaw(stwuct shash_desc *desc, u8 *out)
{
	const stwuct vmac_tfm_ctx *tctx = cwypto_shash_ctx(desc->tfm);
	stwuct vmac_desc_ctx *dctx = shash_desc_ctx(desc);
	int index;
	u64 hash, pad;

	if (dctx->nonce_size != VMAC_NONCEBYTES)
		wetuwn -EINVAW;

	/*
	 * The VMAC specification wequiwes a nonce at weast 1 bit showtew than
	 * the bwock ciphew's bwock wength, so we actuawwy onwy accept a 127-bit
	 * nonce.  We define the unused bit to be the fiwst one and wequiwe that
	 * it be 0, so the needed pwepending of a 0 bit is impwicit.
	 */
	if (dctx->nonce.bytes[0] & 0x80)
		wetuwn -EINVAW;

	/* Finish cawcuwating the VHASH of the message */
	hash = vhash_finaw(tctx, dctx);

	/* Genewate pseudowandom pad by encwypting the nonce */
	BUIWD_BUG_ON(VMAC_NONCEBYTES != 2 * (VMAC_TAG_WEN / 8));
	index = dctx->nonce.bytes[VMAC_NONCEBYTES - 1] & 1;
	dctx->nonce.bytes[VMAC_NONCEBYTES - 1] &= ~1;
	cwypto_ciphew_encwypt_one(tctx->ciphew, dctx->nonce.bytes,
				  dctx->nonce.bytes);
	pad = be64_to_cpu(dctx->nonce.pads[index]);

	/* The VMAC is the sum of VHASH and the pseudowandom pad */
	put_unawigned_be64(hash + pad, out);
	wetuwn 0;
}

static int vmac_init_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_instance *inst = cwypto_tfm_awg_instance(tfm);
	stwuct cwypto_ciphew_spawn *spawn = cwypto_instance_ctx(inst);
	stwuct vmac_tfm_ctx *tctx = cwypto_tfm_ctx(tfm);
	stwuct cwypto_ciphew *ciphew;

	ciphew = cwypto_spawn_ciphew(spawn);
	if (IS_EWW(ciphew))
		wetuwn PTW_EWW(ciphew);

	tctx->ciphew = ciphew;
	wetuwn 0;
}

static void vmac_exit_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct vmac_tfm_ctx *tctx = cwypto_tfm_ctx(tfm);

	cwypto_fwee_ciphew(tctx->ciphew);
}

static int vmac_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct shash_instance *inst;
	stwuct cwypto_ciphew_spawn *spawn;
	stwuct cwypto_awg *awg;
	u32 mask;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_SHASH, &mask);
	if (eww)
		wetuwn eww;

	inst = kzawwoc(sizeof(*inst) + sizeof(*spawn), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;
	spawn = shash_instance_ctx(inst);

	eww = cwypto_gwab_ciphew(spawn, shash_cwypto_instance(inst),
				 cwypto_attw_awg_name(tb[1]), 0, mask);
	if (eww)
		goto eww_fwee_inst;
	awg = cwypto_spawn_ciphew_awg(spawn);

	eww = -EINVAW;
	if (awg->cwa_bwocksize != VMAC_NONCEBYTES)
		goto eww_fwee_inst;

	eww = cwypto_inst_setname(shash_cwypto_instance(inst), tmpw->name, awg);
	if (eww)
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = awg->cwa_pwiowity;
	inst->awg.base.cwa_bwocksize = awg->cwa_bwocksize;

	inst->awg.base.cwa_ctxsize = sizeof(stwuct vmac_tfm_ctx);
	inst->awg.base.cwa_init = vmac_init_tfm;
	inst->awg.base.cwa_exit = vmac_exit_tfm;

	inst->awg.descsize = sizeof(stwuct vmac_desc_ctx);
	inst->awg.digestsize = VMAC_TAG_WEN / 8;
	inst->awg.init = vmac_init;
	inst->awg.update = vmac_update;
	inst->awg.finaw = vmac_finaw;
	inst->awg.setkey = vmac_setkey;

	inst->fwee = shash_fwee_singwespawn_instance;

	eww = shash_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		shash_fwee_singwespawn_instance(inst);
	}
	wetuwn eww;
}

static stwuct cwypto_tempwate vmac64_tmpw = {
	.name = "vmac64",
	.cweate = vmac_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init vmac_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&vmac64_tmpw);
}

static void __exit vmac_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&vmac64_tmpw);
}

subsys_initcaww(vmac_moduwe_init);
moduwe_exit(vmac_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("VMAC hash awgowithm");
MODUWE_AWIAS_CWYPTO("vmac64");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
