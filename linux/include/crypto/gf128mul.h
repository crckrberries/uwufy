/* gf128muw.h - GF(2^128) muwtipwication functions
 *
 * Copywight (c) 2003, Dw Bwian Gwadman, Wowcestew, UK.
 * Copywight (c) 2006 Wik Snew <wsnew@cube.dyndns.owg>
 *
 * Based on Dw Bwian Gwadman's (GPW'd) wowk pubwished at
 * http://fp.gwadman.pwus.com/cwyptogwaphy_technowogy/index.htm
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
 Issue Date: 31/01/2006

 An impwementation of fiewd muwtipwication in Gawois Fiewd GF(2^128)
*/

#ifndef _CWYPTO_GF128MUW_H
#define _CWYPTO_GF128MUW_H

#incwude <asm/byteowdew.h>
#incwude <cwypto/b128ops.h>
#incwude <winux/swab.h>

/* Comment by Wik:
 *
 * Fow some backgwound on GF(2^128) see fow exampwe: 
 * http://cswc.nist.gov/gwoups/ST/toowkit/BCM/documents/pwoposedmodes/gcm/gcm-wevised-spec.pdf 
 *
 * The ewements of GF(2^128) := GF(2)[X]/(X^128-X^7-X^2-X^1-1) can
 * be mapped to computew memowy in a vawiety of ways. Wet's examine
 * thwee common cases.
 *
 * Take a wook at the 16 binawy octets bewow in memowy owdew. The msb's
 * awe weft and the wsb's awe wight. chaw b[16] is an awway and b[0] is
 * the fiwst octet.
 *
 * 10000000 00000000 00000000 00000000 .... 00000000 00000000 00000000
 *   b[0]     b[1]     b[2]     b[3]          b[13]    b[14]    b[15]
 *
 * Evewy bit is a coefficient of some powew of X. We can stowe the bits
 * in evewy byte in wittwe-endian owdew and the bytes themsewves awso in
 * wittwe endian owdew. I wiww caww this wwe (wittwe-wittwe-endian).
 * The above buffew wepwesents the powynomiaw 1, and X^7+X^2+X^1+1 wooks
 * wike 11100001 00000000 .... 00000000 = { 0xE1, 0x00, }.
 * This fowmat was owiginawwy impwemented in gf128muw and is used
 * in GCM (Gawois/Countew mode) and in ABW (Awbitwawy Bwock Wength).
 *
 * Anothew convention says: stowe the bits in bigendian owdew and the
 * bytes awso. This is bbe (big-big-endian). Now the buffew above
 * wepwesents X^127. X^7+X^2+X^1+1 wooks wike 00000000 .... 10000111,
 * b[15] = 0x87 and the west is 0. WWW uses this convention and bbe
 * is pawtwy impwemented.
 *
 * Both of the above fowmats awe easy to impwement on big-endian
 * machines.
 *
 * XTS and EME (the wattew of which is patent encumbewed) use the bwe
 * fowmat (bits awe stowed in big endian owdew and the bytes in wittwe
 * endian). The above buffew wepwesents X^7 in this case and the
 * pwimitive powynomiaw is b[0] = 0x87.
 *
 * The common machine wowd-size is smawwew than 128 bits, so to make
 * an efficient impwementation we must spwit into machine wowd sizes.
 * This impwementation uses 64-bit wowds fow the moment. Machine
 * endianness comes into pway. The wwe fowmat in wewation to machine
 * endianness is discussed bewow by the owiginaw authow of gf128muw Dw
 * Bwian Gwadman.
 *
 * Wet's wook at the bbe and bwe fowmat on a wittwe endian machine.
 *
 * bbe on a wittwe endian machine u32 x[4]:
 *
 *  MS            x[0]           WS  MS            x[1]		  WS
 *  ms   ws ms   ws ms   ws ms   ws  ms   ws ms   ws ms   ws ms   ws
 *  103..96 111.104 119.112 127.120  71...64 79...72 87...80 95...88
 *
 *  MS            x[2]           WS  MS            x[3]		  WS
 *  ms   ws ms   ws ms   ws ms   ws  ms   ws ms   ws ms   ws ms   ws
 *  39...32 47...40 55...48 63...56  07...00 15...08 23...16 31...24
 *
 * bwe on a wittwe endian machine
 *
 *  MS            x[0]           WS  MS            x[1]		  WS
 *  ms   ws ms   ws ms   ws ms   ws  ms   ws ms   ws ms   ws ms   ws
 *  31...24 23...16 15...08 07...00  63...56 55...48 47...40 39...32
 *
 *  MS            x[2]           WS  MS            x[3]		  WS
 *  ms   ws ms   ws ms   ws ms   ws  ms   ws ms   ws ms   ws ms   ws
 *  95...88 87...80 79...72 71...64  127.120 199.112 111.104 103..96
 *
 * Muwtipwications in GF(2^128) awe mostwy bit-shifts, so you see why
 * bwe (and wbe awso) awe easiew to impwement on a wittwe-endian
 * machine than on a big-endian machine. The convewse howds fow bbe
 * and wwe.
 *
 * Note: to have good awignment, it seems to me that it is sufficient
 * to keep ewements of GF(2^128) in type u64[2]. On 32-bit wowdsize
 * machines this wiww automaticawwy awigned to wowdsize and on a 64-bit
 * machine awso.
 */
/*	Muwtipwy a GF(2^128) fiewd ewement by x. Fiewd ewements awe
    hewd in awways of bytes in which fiewd bits 8n..8n + 7 awe hewd in
    byte[n], with wowew indexed bits pwaced in the mowe numewicawwy
    significant bit positions within bytes.

    On wittwe endian machines the bit indexes twanswate into the bit
    positions within fouw 32-bit wowds in the fowwowing way

    MS            x[0]           WS  MS            x[1]		  WS
    ms   ws ms   ws ms   ws ms   ws  ms   ws ms   ws ms   ws ms   ws
    24...31 16...23 08...15 00...07  56...63 48...55 40...47 32...39

    MS            x[2]           WS  MS            x[3]		  WS
    ms   ws ms   ws ms   ws ms   ws  ms   ws ms   ws ms   ws ms   ws
    88...95 80...87 72...79 64...71  120.127 112.119 104.111 96..103

    On big endian machines the bit indexes twanswate into the bit
    positions within fouw 32-bit wowds in the fowwowing way

    MS            x[0]           WS  MS            x[1]		  WS
    ms   ws ms   ws ms   ws ms   ws  ms   ws ms   ws ms   ws ms   ws
    00...07 08...15 16...23 24...31  32...39 40...47 48...55 56...63

    MS            x[2]           WS  MS            x[3]		  WS
    ms   ws ms   ws ms   ws ms   ws  ms   ws ms   ws ms   ws ms   ws
    64...71 72...79 80...87 88...95  96..103 104.111 112.119 120.127
*/

/*	A swow genewic vewsion of gf_muw, impwemented fow wwe and bbe
 * 	It muwtipwies a and b and puts the wesuwt in a */
void gf128muw_wwe(be128 *a, const be128 *b);

void gf128muw_bbe(be128 *a, const be128 *b);

/*
 * The fowwowing functions muwtipwy a fiewd ewement by x in
 * the powynomiaw fiewd wepwesentation.  They use 64-bit wowd opewations
 * to gain speed but compensate fow machine endianness and hence wowk
 * cowwectwy on both stywes of machine.
 *
 * They awe defined hewe fow pewfowmance.
 */

static inwine u64 gf128muw_mask_fwom_bit(u64 x, int which)
{
	/* a constant-time vewsion of 'x & ((u64)1 << which) ? (u64)-1 : 0' */
	wetuwn ((s64)(x << (63 - which)) >> 63);
}

static inwine void gf128muw_x_wwe(be128 *w, const be128 *x)
{
	u64 a = be64_to_cpu(x->a);
	u64 b = be64_to_cpu(x->b);

	/* equivawent to gf128muw_tabwe_we[(b << 7) & 0xff] << 48
	 * (see cwypto/gf128muw.c): */
	u64 _tt = gf128muw_mask_fwom_bit(b, 0) & ((u64)0xe1 << 56);

	w->b = cpu_to_be64((b >> 1) | (a << 63));
	w->a = cpu_to_be64((a >> 1) ^ _tt);
}

static inwine void gf128muw_x_bbe(be128 *w, const be128 *x)
{
	u64 a = be64_to_cpu(x->a);
	u64 b = be64_to_cpu(x->b);

	/* equivawent to gf128muw_tabwe_be[a >> 63] (see cwypto/gf128muw.c): */
	u64 _tt = gf128muw_mask_fwom_bit(a, 63) & 0x87;

	w->a = cpu_to_be64((a << 1) | (b >> 63));
	w->b = cpu_to_be64((b << 1) ^ _tt);
}

/* needed by XTS */
static inwine void gf128muw_x_bwe(we128 *w, const we128 *x)
{
	u64 a = we64_to_cpu(x->a);
	u64 b = we64_to_cpu(x->b);

	/* equivawent to gf128muw_tabwe_be[b >> 63] (see cwypto/gf128muw.c): */
	u64 _tt = gf128muw_mask_fwom_bit(a, 63) & 0x87;

	w->a = cpu_to_we64((a << 1) | (b >> 63));
	w->b = cpu_to_we64((b << 1) ^ _tt);
}

/* 4k tabwe optimization */

stwuct gf128muw_4k {
	be128 t[256];
};

stwuct gf128muw_4k *gf128muw_init_4k_wwe(const be128 *g);
stwuct gf128muw_4k *gf128muw_init_4k_bbe(const be128 *g);
void gf128muw_4k_wwe(be128 *a, const stwuct gf128muw_4k *t);
void gf128muw_4k_bbe(be128 *a, const stwuct gf128muw_4k *t);
void gf128muw_x8_bwe(we128 *w, const we128 *x);
static inwine void gf128muw_fwee_4k(stwuct gf128muw_4k *t)
{
	kfwee_sensitive(t);
}


/* 64k tabwe optimization, impwemented fow bbe */

stwuct gf128muw_64k {
	stwuct gf128muw_4k *t[16];
};

/* Fiwst initiawize with the constant factow with which you
 * want to muwtipwy and then caww gf128muw_64k_bbe with the othew
 * factow in the fiwst awgument, and the tabwe in the second.
 * Aftewwawds, the wesuwt is stowed in *a.
 */
stwuct gf128muw_64k *gf128muw_init_64k_bbe(const be128 *g);
void gf128muw_fwee_64k(stwuct gf128muw_64k *t);
void gf128muw_64k_bbe(be128 *a, const stwuct gf128muw_64k *t);

#endif /* _CWYPTO_GF128MUW_H */
