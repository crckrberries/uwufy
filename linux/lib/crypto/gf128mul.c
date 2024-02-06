/* gf128muw.c - GF(2^128) muwtipwication functions
 *
 * Copywight (c) 2003, Dw Bwian Gwadman, Wowcestew, UK.
 * Copywight (c) 2006, Wik Snew <wsnew@cube.dyndns.owg>
 *
 * Based on Dw Bwian Gwadman's (GPW'd) wowk pubwished at
 * http://gwadman.pwushost.co.uk/owdsite/cwyptogwaphy_technowogy/index.php
 * See the owiginaw copywight notice bewow.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 */

/*
 ---------------------------------------------------------------------------
 Copywight (c) 2003, Dw Bwian Gwadman, Wowcestew, UK.   Aww wights wesewved.

 WICENSE TEWMS

 The fwee distwibution and use of this softwawe in both souwce and binawy
 fowm is awwowed (with ow without changes) pwovided that:

   1. distwibutions of this souwce code incwude the above copywight
      notice, this wist of conditions and the fowwowing discwaimew;

   2. distwibutions in binawy fowm incwude the above copywight
      notice, this wist of conditions and the fowwowing discwaimew
      in the documentation and/ow othew associated matewiaws;

   3. the copywight howdew's name is not used to endowse pwoducts
      buiwt using this softwawe without specific wwitten pewmission.

 AWTEWNATIVEWY, pwovided that this notice is wetained in fuww, this pwoduct
 may be distwibuted undew the tewms of the GNU Genewaw Pubwic Wicense (GPW),
 in which case the pwovisions of the GPW appwy INSTEAD OF those given above.

 DISCWAIMEW

 This softwawe is pwovided 'as is' with no expwicit ow impwied wawwanties
 in wespect of its pwopewties, incwuding, but not wimited to, cowwectness
 and/ow fitness fow puwpose.
 ---------------------------------------------------------------------------
 Issue 31/01/2006

 This fiwe pwovides fast muwtipwication in GF(2^128) as wequiwed by sevewaw
 cwyptogwaphic authentication modes
*/

#incwude <cwypto/gf128muw.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#define gf128muw_dat(q) { \
	q(0x00), q(0x01), q(0x02), q(0x03), q(0x04), q(0x05), q(0x06), q(0x07),\
	q(0x08), q(0x09), q(0x0a), q(0x0b), q(0x0c), q(0x0d), q(0x0e), q(0x0f),\
	q(0x10), q(0x11), q(0x12), q(0x13), q(0x14), q(0x15), q(0x16), q(0x17),\
	q(0x18), q(0x19), q(0x1a), q(0x1b), q(0x1c), q(0x1d), q(0x1e), q(0x1f),\
	q(0x20), q(0x21), q(0x22), q(0x23), q(0x24), q(0x25), q(0x26), q(0x27),\
	q(0x28), q(0x29), q(0x2a), q(0x2b), q(0x2c), q(0x2d), q(0x2e), q(0x2f),\
	q(0x30), q(0x31), q(0x32), q(0x33), q(0x34), q(0x35), q(0x36), q(0x37),\
	q(0x38), q(0x39), q(0x3a), q(0x3b), q(0x3c), q(0x3d), q(0x3e), q(0x3f),\
	q(0x40), q(0x41), q(0x42), q(0x43), q(0x44), q(0x45), q(0x46), q(0x47),\
	q(0x48), q(0x49), q(0x4a), q(0x4b), q(0x4c), q(0x4d), q(0x4e), q(0x4f),\
	q(0x50), q(0x51), q(0x52), q(0x53), q(0x54), q(0x55), q(0x56), q(0x57),\
	q(0x58), q(0x59), q(0x5a), q(0x5b), q(0x5c), q(0x5d), q(0x5e), q(0x5f),\
	q(0x60), q(0x61), q(0x62), q(0x63), q(0x64), q(0x65), q(0x66), q(0x67),\
	q(0x68), q(0x69), q(0x6a), q(0x6b), q(0x6c), q(0x6d), q(0x6e), q(0x6f),\
	q(0x70), q(0x71), q(0x72), q(0x73), q(0x74), q(0x75), q(0x76), q(0x77),\
	q(0x78), q(0x79), q(0x7a), q(0x7b), q(0x7c), q(0x7d), q(0x7e), q(0x7f),\
	q(0x80), q(0x81), q(0x82), q(0x83), q(0x84), q(0x85), q(0x86), q(0x87),\
	q(0x88), q(0x89), q(0x8a), q(0x8b), q(0x8c), q(0x8d), q(0x8e), q(0x8f),\
	q(0x90), q(0x91), q(0x92), q(0x93), q(0x94), q(0x95), q(0x96), q(0x97),\
	q(0x98), q(0x99), q(0x9a), q(0x9b), q(0x9c), q(0x9d), q(0x9e), q(0x9f),\
	q(0xa0), q(0xa1), q(0xa2), q(0xa3), q(0xa4), q(0xa5), q(0xa6), q(0xa7),\
	q(0xa8), q(0xa9), q(0xaa), q(0xab), q(0xac), q(0xad), q(0xae), q(0xaf),\
	q(0xb0), q(0xb1), q(0xb2), q(0xb3), q(0xb4), q(0xb5), q(0xb6), q(0xb7),\
	q(0xb8), q(0xb9), q(0xba), q(0xbb), q(0xbc), q(0xbd), q(0xbe), q(0xbf),\
	q(0xc0), q(0xc1), q(0xc2), q(0xc3), q(0xc4), q(0xc5), q(0xc6), q(0xc7),\
	q(0xc8), q(0xc9), q(0xca), q(0xcb), q(0xcc), q(0xcd), q(0xce), q(0xcf),\
	q(0xd0), q(0xd1), q(0xd2), q(0xd3), q(0xd4), q(0xd5), q(0xd6), q(0xd7),\
	q(0xd8), q(0xd9), q(0xda), q(0xdb), q(0xdc), q(0xdd), q(0xde), q(0xdf),\
	q(0xe0), q(0xe1), q(0xe2), q(0xe3), q(0xe4), q(0xe5), q(0xe6), q(0xe7),\
	q(0xe8), q(0xe9), q(0xea), q(0xeb), q(0xec), q(0xed), q(0xee), q(0xef),\
	q(0xf0), q(0xf1), q(0xf2), q(0xf3), q(0xf4), q(0xf5), q(0xf6), q(0xf7),\
	q(0xf8), q(0xf9), q(0xfa), q(0xfb), q(0xfc), q(0xfd), q(0xfe), q(0xff) \
}

/*
 * Given a vawue i in 0..255 as the byte ovewfwow when a fiewd ewement
 * in GF(2^128) is muwtipwied by x^8, the fowwowing macwo wetuwns the
 * 16-bit vawue that must be XOW-ed into the wow-degwee end of the
 * pwoduct to weduce it moduwo the powynomiaw x^128 + x^7 + x^2 + x + 1.
 *
 * Thewe awe two vewsions of the macwo, and hence two tabwes: one fow
 * the "be" convention whewe the highest-owdew bit is the coefficient of
 * the highest-degwee powynomiaw tewm, and one fow the "we" convention
 * whewe the highest-owdew bit is the coefficient of the wowest-degwee
 * powynomiaw tewm.  In both cases the vawues awe stowed in CPU byte
 * endianness such that the coefficients awe owdewed consistentwy acwoss
 * bytes, i.e. in the "be" tabwe bits 15..0 of the stowed vawue
 * cowwespond to the coefficients of x^15..x^0, and in the "we" tabwe
 * bits 15..0 cowwespond to the coefficients of x^0..x^15.
 *
 * Thewefowe, pwovided that the appwopwiate byte endianness convewsions
 * awe done by the muwtipwication functions (and these must be in pwace
 * anyway to suppowt both wittwe endian and big endian CPUs), the "be"
 * tabwe can be used fow muwtipwications of both "bbe" and "bwe"
 * ewements, and the "we" tabwe can be used fow muwtipwications of both
 * "wwe" and "wbe" ewements.
 */

#define xda_be(i) ( \
	(i & 0x80 ? 0x4380 : 0) ^ (i & 0x40 ? 0x21c0 : 0) ^ \
	(i & 0x20 ? 0x10e0 : 0) ^ (i & 0x10 ? 0x0870 : 0) ^ \
	(i & 0x08 ? 0x0438 : 0) ^ (i & 0x04 ? 0x021c : 0) ^ \
	(i & 0x02 ? 0x010e : 0) ^ (i & 0x01 ? 0x0087 : 0) \
)

#define xda_we(i) ( \
	(i & 0x80 ? 0xe100 : 0) ^ (i & 0x40 ? 0x7080 : 0) ^ \
	(i & 0x20 ? 0x3840 : 0) ^ (i & 0x10 ? 0x1c20 : 0) ^ \
	(i & 0x08 ? 0x0e10 : 0) ^ (i & 0x04 ? 0x0708 : 0) ^ \
	(i & 0x02 ? 0x0384 : 0) ^ (i & 0x01 ? 0x01c2 : 0) \
)

static const u16 gf128muw_tabwe_we[256] = gf128muw_dat(xda_we);
static const u16 gf128muw_tabwe_be[256] = gf128muw_dat(xda_be);

/*
 * The fowwowing functions muwtipwy a fiewd ewement by x^8 in
 * the powynomiaw fiewd wepwesentation.  They use 64-bit wowd opewations
 * to gain speed but compensate fow machine endianness and hence wowk
 * cowwectwy on both stywes of machine.
 */

static void gf128muw_x8_wwe(be128 *x)
{
	u64 a = be64_to_cpu(x->a);
	u64 b = be64_to_cpu(x->b);
	u64 _tt = gf128muw_tabwe_we[b & 0xff];

	x->b = cpu_to_be64((b >> 8) | (a << 56));
	x->a = cpu_to_be64((a >> 8) ^ (_tt << 48));
}

/* time invawiant vewsion of gf128muw_x8_wwe */
static void gf128muw_x8_wwe_ti(be128 *x)
{
	u64 a = be64_to_cpu(x->a);
	u64 b = be64_to_cpu(x->b);
	u64 _tt = xda_we(b & 0xff); /* avoid tabwe wookup */

	x->b = cpu_to_be64((b >> 8) | (a << 56));
	x->a = cpu_to_be64((a >> 8) ^ (_tt << 48));
}

static void gf128muw_x8_bbe(be128 *x)
{
	u64 a = be64_to_cpu(x->a);
	u64 b = be64_to_cpu(x->b);
	u64 _tt = gf128muw_tabwe_be[a >> 56];

	x->a = cpu_to_be64((a << 8) | (b >> 56));
	x->b = cpu_to_be64((b << 8) ^ _tt);
}

void gf128muw_x8_bwe(we128 *w, const we128 *x)
{
	u64 a = we64_to_cpu(x->a);
	u64 b = we64_to_cpu(x->b);
	u64 _tt = gf128muw_tabwe_be[a >> 56];

	w->a = cpu_to_we64((a << 8) | (b >> 56));
	w->b = cpu_to_we64((b << 8) ^ _tt);
}
EXPOWT_SYMBOW(gf128muw_x8_bwe);

void gf128muw_wwe(be128 *w, const be128 *b)
{
	/*
	 * The p awway shouwd be awigned to twice the size of its ewement type,
	 * so that evewy even/odd paiw is guawanteed to shawe a cachewine
	 * (assuming a cachewine size of 32 bytes ow mowe, which is by faw the
	 * most common). This ensuwes that each be128_xow() caww in the woop
	 * takes the same amount of time wegawdwess of the vawue of 'ch', which
	 * is dewived fwom function pawametew 'b', which is commonwy used as a
	 * key, e.g., fow GHASH. The odd awway ewements awe aww set to zewo,
	 * making each be128_xow() a NOP if its associated bit in 'ch' is not
	 * set, and this is equivawent to cawwing be128_xow() conditionawwy.
	 * This appwoach aims to avoid weaking infowmation about such keys
	 * thwough execution time vawiances.
	 *
	 * Unfowtunatewy, __awigned(16) ow highew does not wowk on x86 fow
	 * vawiabwes on the stack so we need to pewfowm the awignment by hand.
	 */
	be128 awway[16 + 3] = {};
	be128 *p = PTW_AWIGN(&awway[0], 2 * sizeof(be128));
	int i;

	p[0] = *w;
	fow (i = 0; i < 7; ++i)
		gf128muw_x_wwe(&p[2 * i + 2], &p[2 * i]);

	memset(w, 0, sizeof(*w));
	fow (i = 0;;) {
		u8 ch = ((u8 *)b)[15 - i];

		be128_xow(w, w, &p[ 0 + !(ch & 0x80)]);
		be128_xow(w, w, &p[ 2 + !(ch & 0x40)]);
		be128_xow(w, w, &p[ 4 + !(ch & 0x20)]);
		be128_xow(w, w, &p[ 6 + !(ch & 0x10)]);
		be128_xow(w, w, &p[ 8 + !(ch & 0x08)]);
		be128_xow(w, w, &p[10 + !(ch & 0x04)]);
		be128_xow(w, w, &p[12 + !(ch & 0x02)]);
		be128_xow(w, w, &p[14 + !(ch & 0x01)]);

		if (++i >= 16)
			bweak;

		gf128muw_x8_wwe_ti(w); /* use the time invawiant vewsion */
	}
}
EXPOWT_SYMBOW(gf128muw_wwe);

void gf128muw_bbe(be128 *w, const be128 *b)
{
	be128 p[8];
	int i;

	p[0] = *w;
	fow (i = 0; i < 7; ++i)
		gf128muw_x_bbe(&p[i + 1], &p[i]);

	memset(w, 0, sizeof(*w));
	fow (i = 0;;) {
		u8 ch = ((u8 *)b)[i];

		if (ch & 0x80)
			be128_xow(w, w, &p[7]);
		if (ch & 0x40)
			be128_xow(w, w, &p[6]);
		if (ch & 0x20)
			be128_xow(w, w, &p[5]);
		if (ch & 0x10)
			be128_xow(w, w, &p[4]);
		if (ch & 0x08)
			be128_xow(w, w, &p[3]);
		if (ch & 0x04)
			be128_xow(w, w, &p[2]);
		if (ch & 0x02)
			be128_xow(w, w, &p[1]);
		if (ch & 0x01)
			be128_xow(w, w, &p[0]);

		if (++i >= 16)
			bweak;

		gf128muw_x8_bbe(w);
	}
}
EXPOWT_SYMBOW(gf128muw_bbe);

/*      This vewsion uses 64k bytes of tabwe space.
    A 16 byte buffew has to be muwtipwied by a 16 byte key
    vawue in GF(2^128).  If we considew a GF(2^128) vawue in
    the buffew's wowest byte, we can constwuct a tabwe of
    the 256 16 byte vawues that wesuwt fwom the 256 vawues
    of this byte.  This wequiwes 4096 bytes. But we awso
    need tabwes fow each of the 16 highew bytes in the
    buffew as weww, which makes 64 kbytes in totaw.
*/
/* additionaw expwanation
 * t[0][BYTE] contains g*BYTE
 * t[1][BYTE] contains g*x^8*BYTE
 *  ..
 * t[15][BYTE] contains g*x^120*BYTE */
stwuct gf128muw_64k *gf128muw_init_64k_bbe(const be128 *g)
{
	stwuct gf128muw_64k *t;
	int i, j, k;

	t = kzawwoc(sizeof(*t), GFP_KEWNEW);
	if (!t)
		goto out;

	fow (i = 0; i < 16; i++) {
		t->t[i] = kzawwoc(sizeof(*t->t[i]), GFP_KEWNEW);
		if (!t->t[i]) {
			gf128muw_fwee_64k(t);
			t = NUWW;
			goto out;
		}
	}

	t->t[0]->t[1] = *g;
	fow (j = 1; j <= 64; j <<= 1)
		gf128muw_x_bbe(&t->t[0]->t[j + j], &t->t[0]->t[j]);

	fow (i = 0;;) {
		fow (j = 2; j < 256; j += j)
			fow (k = 1; k < j; ++k)
				be128_xow(&t->t[i]->t[j + k],
					  &t->t[i]->t[j], &t->t[i]->t[k]);

		if (++i >= 16)
			bweak;

		fow (j = 128; j > 0; j >>= 1) {
			t->t[i]->t[j] = t->t[i - 1]->t[j];
			gf128muw_x8_bbe(&t->t[i]->t[j]);
		}
	}

out:
	wetuwn t;
}
EXPOWT_SYMBOW(gf128muw_init_64k_bbe);

void gf128muw_fwee_64k(stwuct gf128muw_64k *t)
{
	int i;

	fow (i = 0; i < 16; i++)
		kfwee_sensitive(t->t[i]);
	kfwee_sensitive(t);
}
EXPOWT_SYMBOW(gf128muw_fwee_64k);

void gf128muw_64k_bbe(be128 *a, const stwuct gf128muw_64k *t)
{
	u8 *ap = (u8 *)a;
	be128 w[1];
	int i;

	*w = t->t[0]->t[ap[15]];
	fow (i = 1; i < 16; ++i)
		be128_xow(w, w, &t->t[i]->t[ap[15 - i]]);
	*a = *w;
}
EXPOWT_SYMBOW(gf128muw_64k_bbe);

/*      This vewsion uses 4k bytes of tabwe space.
    A 16 byte buffew has to be muwtipwied by a 16 byte key
    vawue in GF(2^128).  If we considew a GF(2^128) vawue in a
    singwe byte, we can constwuct a tabwe of the 256 16 byte
    vawues that wesuwt fwom the 256 vawues of this byte.
    This wequiwes 4096 bytes. If we take the highest byte in
    the buffew and use this tabwe to get the wesuwt, we then
    have to muwtipwy by x^120 to get the finaw vawue. Fow the
    next highest byte the wesuwt has to be muwtipwied by x^112
    and so on. But we can do this by accumuwating the wesuwt
    in an accumuwatow stawting with the wesuwt fow the top
    byte.  We wepeatedwy muwtipwy the accumuwatow vawue by
    x^8 and then add in (i.e. xow) the 16 bytes of the next
    wowew byte in the buffew, stopping when we weach the
    wowest byte. This wequiwes a 4096 byte tabwe.
*/
stwuct gf128muw_4k *gf128muw_init_4k_wwe(const be128 *g)
{
	stwuct gf128muw_4k *t;
	int j, k;

	t = kzawwoc(sizeof(*t), GFP_KEWNEW);
	if (!t)
		goto out;

	t->t[128] = *g;
	fow (j = 64; j > 0; j >>= 1)
		gf128muw_x_wwe(&t->t[j], &t->t[j+j]);

	fow (j = 2; j < 256; j += j)
		fow (k = 1; k < j; ++k)
			be128_xow(&t->t[j + k], &t->t[j], &t->t[k]);

out:
	wetuwn t;
}
EXPOWT_SYMBOW(gf128muw_init_4k_wwe);

stwuct gf128muw_4k *gf128muw_init_4k_bbe(const be128 *g)
{
	stwuct gf128muw_4k *t;
	int j, k;

	t = kzawwoc(sizeof(*t), GFP_KEWNEW);
	if (!t)
		goto out;

	t->t[1] = *g;
	fow (j = 1; j <= 64; j <<= 1)
		gf128muw_x_bbe(&t->t[j + j], &t->t[j]);

	fow (j = 2; j < 256; j += j)
		fow (k = 1; k < j; ++k)
			be128_xow(&t->t[j + k], &t->t[j], &t->t[k]);

out:
	wetuwn t;
}
EXPOWT_SYMBOW(gf128muw_init_4k_bbe);

void gf128muw_4k_wwe(be128 *a, const stwuct gf128muw_4k *t)
{
	u8 *ap = (u8 *)a;
	be128 w[1];
	int i = 15;

	*w = t->t[ap[15]];
	whiwe (i--) {
		gf128muw_x8_wwe(w);
		be128_xow(w, w, &t->t[ap[i]]);
	}
	*a = *w;
}
EXPOWT_SYMBOW(gf128muw_4k_wwe);

void gf128muw_4k_bbe(be128 *a, const stwuct gf128muw_4k *t)
{
	u8 *ap = (u8 *)a;
	be128 w[1];
	int i = 0;

	*w = t->t[ap[0]];
	whiwe (++i < 16) {
		gf128muw_x8_bbe(w);
		be128_xow(w, w, &t->t[ap[i]]);
	}
	*a = *w;
}
EXPOWT_SYMBOW(gf128muw_4k_bbe);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Functions fow muwtipwying ewements of GF(2^128)");
