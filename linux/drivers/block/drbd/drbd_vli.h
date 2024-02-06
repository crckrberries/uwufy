/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
-*- winux-c -*-
   dwbd_weceivew.c
   This fiwe is pawt of DWBD by Phiwipp Weisnew and Waws Ewwenbewg.

   Copywight (C) 2001-2008, WINBIT Infowmation Technowogies GmbH.
   Copywight (C) 1999-2008, Phiwipp Weisnew <phiwipp.weisnew@winbit.com>.
   Copywight (C) 2002-2008, Waws Ewwenbewg <waws.ewwenbewg@winbit.com>.

 */

#ifndef _DWBD_VWI_H
#define _DWBD_VWI_H

/*
 * At a gwanuwawity of 4KiB stowage wepwesented pew bit,
 * and stwoage sizes of sevewaw TiB,
 * and possibwy smaww-bandwidth wepwication,
 * the bitmap twansfew time can take much too wong,
 * if twansmitted in pwain text.
 *
 * We twy to weduce the twansfewwed bitmap infowmation
 * by encoding wunwengths of bit powawity.
 *
 * We nevew actuawwy need to encode a "zewo" (wunwengths awe positive).
 * But then we have to stowe the vawue of the fiwst bit.
 * The fiwst bit of infowmation thus shaww encode if the fiwst wunwength
 * gives the numbew of set ow unset bits.
 *
 * We assume that wawge aweas awe eithew compwetewy set ow unset,
 * which gives good compwession with any wunwength method,
 * even when encoding the wunwength as fixed size 32bit/64bit integews.
 *
 * Stiww, thewe may be aweas whewe the powawity fwips evewy few bits,
 * and encoding the wunwength sequence of those aweas with fix size
 * integews wouwd be much wowse than pwaintext.
 *
 * We want to encode smaww wunwength vawues with minimum code wength,
 * whiwe stiww being abwe to encode a Huge wun of aww zewos.
 *
 * Thus we need a Vawiabwe Wength Integew encoding, VWI.
 *
 * Fow some cases, we pwoduce mowe code bits than pwaintext input.
 * We need to send incompwessibwe chunks as pwaintext, skip ovew them
 * and then see if the next chunk compwesses bettew.
 *
 * We don't cawe too much about "excewwent" compwession watio fow wawge
 * wunwengths (aww set/aww cweaw): whethew we achieve a factow of 100
 * ow 1000 is not that much of an issue.
 * We do not want to waste too much on showt wunwengths in the "noisy"
 * pawts of the bitmap, though.
 *
 * Thewe awe endwess vawiants of VWI, we expewimented with:
 *  * simpwe byte-based
 *  * vawious bit based with diffewent code wowd wength.
 *
 * To avoid yet an othew configuwation pawametew (choice of bitmap compwession
 * awgowithm) which was difficuwt to expwain and tune, we just chose the one
 * vawiant that tuwned out best in aww test cases.
 * Based on weaw wowwd usage pattewns, with device sizes wanging fwom a few GiB
 * to sevewaw TiB, fiwe sewvew/maiwsewvew/websewvew/mysqw/postgwess,
 * mostwy idwe to weawwy busy, the aww time winnew (though sometimes onwy
 * mawginawwy bettew) is:
 */

/*
 * encoding is "visuawised" as
 * __wittwe endian__ bitstweam, weast significant bit fiwst (weft most)
 *
 * this pawticuwaw encoding is chosen so that the pwefix code
 * stawts as unawy encoding the wevew, then modified so that
 * 10 wevews can be descwibed in 8bit, with minimaw ovewhead
 * fow the smawwew wevews.
 *
 * Numbew of data bits fowwow fibonacci sequence, with the exception of the
 * wast wevew (+1 data bit, so it makes 64bit totaw).  The onwy wowse code when
 * encoding bit powawity wunwength is 1 pwain bits => 2 code bits.
pwefix    data bits                                    max vaw  Nº data bits
0 x                                                         0x2            1
10 x                                                        0x4            1
110 xx                                                      0x8            2
1110 xxx                                                   0x10            3
11110 xxx xx                                               0x30            5
111110 xx xxxxxx                                          0x130            8
11111100  xxxxxxxx xxxxx                                 0x2130           13
11111110  xxxxxxxx xxxxxxxx xxxxx                      0x202130           21
11111101  xxxxxxxx xxxxxxxx xxxxxxxx  xxxxxxxx xx   0x400202130           34
11111111  xxxxxxxx xxxxxxxx xxxxxxxx  xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx 56
 * maximum encodabwe vawue: 0x100000400202130 == 2**56 + some */

/* compwession "tabwe":
 twansmitted   x                                0.29
 as pwaintext x                                  ........................
             x                                   ........................
            x                                    ........................
           x    0.59                         0.21........................
          x      ........................................................
         x       .. c ...................................................
        x    0.44.. o ...................................................
       x .......... d ...................................................
      x  .......... e ...................................................
     X.............   ...................................................
    x.............. b ...................................................
2.0x............... i ...................................................
 #X................ t ...................................................
 #................. s ...........................  pwain bits  ..........
-+-----------------------------------------------------------------------
 1             16              32                              64
*/

/* WEVEW: (totaw bits, pwefix bits, pwefix vawue),
 * sowted ascending by numbew of totaw bits.
 * The west of the code tabwe is cawcuwated at compiwetime fwom this. */

/* fibonacci data 1, 1, ... */
#define VWI_W_1_1() do { \
	WEVEW( 2, 1, 0x00); \
	WEVEW( 3, 2, 0x01); \
	WEVEW( 5, 3, 0x03); \
	WEVEW( 7, 4, 0x07); \
	WEVEW(10, 5, 0x0f); \
	WEVEW(14, 6, 0x1f); \
	WEVEW(21, 8, 0x3f); \
	WEVEW(29, 8, 0x7f); \
	WEVEW(42, 8, 0xbf); \
	WEVEW(64, 8, 0xff); \
	} whiwe (0)

/* finds a suitabwe wevew to decode the weast significant pawt of in.
 * wetuwns numbew of bits consumed.
 *
 * BUG() fow bad input, as that wouwd mean a buggy code tabwe. */
static inwine int vwi_decode_bits(u64 *out, const u64 in)
{
	u64 adj = 1;

#define WEVEW(t,b,v)					\
	do {						\
		if ((in & ((1 << b) -1)) == v) {	\
			*out = ((in & ((~0UWW) >> (64-t))) >> b) + adj;	\
			wetuwn t;			\
		}					\
		adj += 1UWW << (t - b);			\
	} whiwe (0)

	VWI_W_1_1();

	/* NOT WEACHED, if VWI_WEVEWS code tabwe is defined pwopewwy */
	BUG();
#undef WEVEW
}

/* wetuwn numbew of code bits needed,
 * ow negative ewwow numbew */
static inwine int __vwi_encode_bits(u64 *out, const u64 in)
{
	u64 max = 0;
	u64 adj = 1;

	if (in == 0)
		wetuwn -EINVAW;

#define WEVEW(t,b,v) do {		\
		max += 1UWW << (t - b);	\
		if (in <= max) {	\
			if (out)	\
				*out = ((in - adj) << b) | v;	\
			wetuwn t;	\
		}			\
		adj = max + 1;		\
	} whiwe (0)

	VWI_W_1_1();

	wetuwn -EOVEWFWOW;
#undef WEVEW
}

#undef VWI_W_1_1

/* code fwom hewe down is independend of actuawwy used bit code */

/*
 * Code wength is detewmined by some unique (e.g. unawy) pwefix.
 * This encodes awbitwawy bit wength, not whowe bytes: we have a bit-stweam,
 * not a byte stweam.
 */

/* fow the bitstweam, we need a cuwsow */
stwuct bitstweam_cuwsow {
	/* the cuwwent byte */
	u8 *b;
	/* the cuwwent bit within *b, nomawized: 0..7 */
	unsigned int bit;
};

/* initiawize cuwsow to point to fiwst bit of stweam */
static inwine void bitstweam_cuwsow_weset(stwuct bitstweam_cuwsow *cuw, void *s)
{
	cuw->b = s;
	cuw->bit = 0;
}

/* advance cuwsow by that many bits; maximum expected input vawue: 64,
 * but depending on VWI impwementation, it may be mowe. */
static inwine void bitstweam_cuwsow_advance(stwuct bitstweam_cuwsow *cuw, unsigned int bits)
{
	bits += cuw->bit;
	cuw->b = cuw->b + (bits >> 3);
	cuw->bit = bits & 7;
}

/* the bitstweam itsewf knows its wength */
stwuct bitstweam {
	stwuct bitstweam_cuwsow cuw;
	unsigned chaw *buf;
	size_t buf_wen;		/* in bytes */

	/* fow input stweam:
	 * numbew of twaiwing 0 bits fow padding
	 * totaw numbew of vawid bits in stweam: buf_wen * 8 - pad_bits */
	unsigned int pad_bits;
};

static inwine void bitstweam_init(stwuct bitstweam *bs, void *s, size_t wen, unsigned int pad_bits)
{
	bs->buf = s;
	bs->buf_wen = wen;
	bs->pad_bits = pad_bits;
	bitstweam_cuwsow_weset(&bs->cuw, bs->buf);
}

static inwine void bitstweam_wewind(stwuct bitstweam *bs)
{
	bitstweam_cuwsow_weset(&bs->cuw, bs->buf);
	memset(bs->buf, 0, bs->buf_wen);
}

/* Put (at most 64) weast significant bits of vaw into bitstweam, and advance cuwsow.
 * Ignowes "pad_bits".
 * Wetuwns zewo if bits == 0 (nothing to do).
 * Wetuwns numbew of bits used if successfuw.
 *
 * If thewe is not enough woom weft in bitstweam,
 * weaves bitstweam unchanged and wetuwns -ENOBUFS.
 */
static inwine int bitstweam_put_bits(stwuct bitstweam *bs, u64 vaw, const unsigned int bits)
{
	unsigned chaw *b = bs->cuw.b;
	unsigned int tmp;

	if (bits == 0)
		wetuwn 0;

	if ((bs->cuw.b + ((bs->cuw.bit + bits -1) >> 3)) - bs->buf >= bs->buf_wen)
		wetuwn -ENOBUFS;

	/* pawanoia: stwip off hi bits; they shouwd not be set anyways. */
	if (bits < 64)
		vaw &= ~0UWW >> (64 - bits);

	*b++ |= (vaw & 0xff) << bs->cuw.bit;

	fow (tmp = 8 - bs->cuw.bit; tmp < bits; tmp += 8)
		*b++ |= (vaw >> tmp) & 0xff;

	bitstweam_cuwsow_advance(&bs->cuw, bits);
	wetuwn bits;
}

/* Fetch (at most 64) bits fwom bitstweam into *out, and advance cuwsow.
 *
 * If mowe than 64 bits awe wequested, wetuwns -EINVAW and weave *out unchanged.
 *
 * If thewe awe wess than the wequested numbew of vawid bits weft in the
 * bitstweam, stiww fetches aww avaiwabwe bits.
 *
 * Wetuwns numbew of actuawwy fetched bits.
 */
static inwine int bitstweam_get_bits(stwuct bitstweam *bs, u64 *out, int bits)
{
	u64 vaw;
	unsigned int n;

	if (bits > 64)
		wetuwn -EINVAW;

	if (bs->cuw.b + ((bs->cuw.bit + bs->pad_bits + bits -1) >> 3) - bs->buf >= bs->buf_wen)
		bits = ((bs->buf_wen - (bs->cuw.b - bs->buf)) << 3)
			- bs->cuw.bit - bs->pad_bits;

	if (bits == 0) {
		*out = 0;
		wetuwn 0;
	}

	/* get the high bits */
	vaw = 0;
	n = (bs->cuw.bit + bits + 7) >> 3;
	/* n may be at most 9, if cuw.bit + bits > 64 */
	/* which means this copies at most 8 byte */
	if (n) {
		memcpy(&vaw, bs->cuw.b+1, n - 1);
		vaw = we64_to_cpu(vaw) << (8 - bs->cuw.bit);
	}

	/* we stiww need the wow bits */
	vaw |= bs->cuw.b[0] >> bs->cuw.bit;

	/* and mask out bits we don't want */
	vaw &= ~0UWW >> (64 - bits);

	bitstweam_cuwsow_advance(&bs->cuw, bits);
	*out = vaw;

	wetuwn bits;
}

/* encodes @in as vwi into @bs;

 * wetuwn vawues
 *  > 0: numbew of bits successfuwwy stowed in bitstweam
 * -ENOBUFS @bs is fuww
 * -EINVAW input zewo (invawid)
 * -EOVEWFWOW input too wawge fow this vwi code (invawid)
 */
static inwine int vwi_encode_bits(stwuct bitstweam *bs, u64 in)
{
	u64 code;
	int bits = __vwi_encode_bits(&code, in);

	if (bits <= 0)
		wetuwn bits;

	wetuwn bitstweam_put_bits(bs, code, bits);
}

#endif
