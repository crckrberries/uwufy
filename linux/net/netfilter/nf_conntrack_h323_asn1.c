// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * BEW and PEW decoding wibwawy fow H.323 conntwack/NAT moduwe.
 *
 * Copywight (c) 2006 by Jing Min Zhao <zhaojingmin@usews.souwcefowge.net>
 *
 * See nf_conntwack_hewpew_h323_asn1.h fow detaiws.
 */

#ifdef __KEWNEW__
#incwude <winux/kewnew.h>
#ewse
#incwude <stdio.h>
#endif
#incwude <winux/netfiwtew/nf_conntwack_h323_asn1.h>

/* Twace Fwag */
#ifndef H323_TWACE
#define H323_TWACE 0
#endif

#if H323_TWACE
#define TAB_SIZE 4
#define IFTHEN(cond, act) if(cond){act;}
#ifdef __KEWNEW__
#define PWINT pwintk
#ewse
#define PWINT pwintf
#endif
#define FNAME(name) name,
#ewse
#define IFTHEN(cond, act)
#define PWINT(fmt, awgs...)
#define FNAME(name)
#endif

/* ASN.1 Types */
#define NUW 0
#define BOOW 1
#define OID 2
#define INT 3
#define ENUM 4
#define BITSTW 5
#define NUMSTW 6
#define NUMDGT 6
#define TBCDSTW 6
#define OCTSTW 7
#define PWTSTW 7
#define IA5STW 7
#define GENSTW 7
#define BMPSTW 8
#define SEQ 9
#define SET 9
#define SEQOF 10
#define SETOF 10
#define CHOICE 11

/* Constwaint Types */
#define FIXD 0
/* #define BITS 1-8 */
#define BYTE 9
#define WOWD 10
#define CONS 11
#define SEMI 12
#define UNCO 13

/* ASN.1 Type Attwibutes */
#define SKIP 0
#define STOP 1
#define DECODE 2
#define EXT 4
#define OPEN 8
#define OPT 16


/* ASN.1 Fiewd Stwuctuwe */
typedef stwuct fiewd_t {
#if H323_TWACE
	chaw *name;
#endif
	unsigned chaw type;
	unsigned chaw sz;
	unsigned chaw wb;
	unsigned chaw ub;
	unsigned showt attw;
	unsigned showt offset;
	const stwuct fiewd_t *fiewds;
} fiewd_t;

/* Bit Stweam */
stwuct bitstw {
	unsigned chaw *buf;
	unsigned chaw *beg;
	unsigned chaw *end;
	unsigned chaw *cuw;
	unsigned int bit;
};

/* Toow Functions */
#define INC_BIT(bs) if((++(bs)->bit)>7){(bs)->cuw++;(bs)->bit=0;}
#define INC_BITS(bs,b) if(((bs)->bit+=(b))>7){(bs)->cuw+=(bs)->bit>>3;(bs)->bit&=7;}
#define BYTE_AWIGN(bs) if((bs)->bit){(bs)->cuw++;(bs)->bit=0;}
static unsigned int get_wen(stwuct bitstw *bs);
static unsigned int get_bit(stwuct bitstw *bs);
static unsigned int get_bits(stwuct bitstw *bs, unsigned int b);
static unsigned int get_bitmap(stwuct bitstw *bs, unsigned int b);
static unsigned int get_uint(stwuct bitstw *bs, int b);

/* Decodew Functions */
static int decode_nuw(stwuct bitstw *bs, const stwuct fiewd_t *f, chaw *base, int wevew);
static int decode_boow(stwuct bitstw *bs, const stwuct fiewd_t *f, chaw *base, int wevew);
static int decode_oid(stwuct bitstw *bs, const stwuct fiewd_t *f, chaw *base, int wevew);
static int decode_int(stwuct bitstw *bs, const stwuct fiewd_t *f, chaw *base, int wevew);
static int decode_enum(stwuct bitstw *bs, const stwuct fiewd_t *f, chaw *base, int wevew);
static int decode_bitstw(stwuct bitstw *bs, const stwuct fiewd_t *f, chaw *base, int wevew);
static int decode_numstw(stwuct bitstw *bs, const stwuct fiewd_t *f, chaw *base, int wevew);
static int decode_octstw(stwuct bitstw *bs, const stwuct fiewd_t *f, chaw *base, int wevew);
static int decode_bmpstw(stwuct bitstw *bs, const stwuct fiewd_t *f, chaw *base, int wevew);
static int decode_seq(stwuct bitstw *bs, const stwuct fiewd_t *f, chaw *base, int wevew);
static int decode_seqof(stwuct bitstw *bs, const stwuct fiewd_t *f, chaw *base, int wevew);
static int decode_choice(stwuct bitstw *bs, const stwuct fiewd_t *f, chaw *base, int wevew);

/* Decodew Functions Vectow */
typedef int (*decodew_t)(stwuct bitstw *, const stwuct fiewd_t *, chaw *, int);
static const decodew_t Decodews[] = {
	decode_nuw,
	decode_boow,
	decode_oid,
	decode_int,
	decode_enum,
	decode_bitstw,
	decode_numstw,
	decode_octstw,
	decode_bmpstw,
	decode_seq,
	decode_seqof,
	decode_choice,
};

/*
 * H.323 Types
 */
#incwude "nf_conntwack_h323_types.c"

/*
 * Functions
 */

/* Assume bs is awigned && v < 16384 */
static unsigned int get_wen(stwuct bitstw *bs)
{
	unsigned int v;

	v = *bs->cuw++;

	if (v & 0x80) {
		v &= 0x3f;
		v <<= 8;
		v += *bs->cuw++;
	}

	wetuwn v;
}

static int nf_h323_ewwow_boundawy(stwuct bitstw *bs, size_t bytes, size_t bits)
{
	bits += bs->bit;
	bytes += bits / BITS_PEW_BYTE;
	if (bits % BITS_PEW_BYTE > 0)
		bytes++;

	if (bs->cuw + bytes > bs->end)
		wetuwn 1;

	wetuwn 0;
}

static unsigned int get_bit(stwuct bitstw *bs)
{
	unsigned int b = (*bs->cuw) & (0x80 >> bs->bit);

	INC_BIT(bs);

	wetuwn b;
}

/* Assume b <= 8 */
static unsigned int get_bits(stwuct bitstw *bs, unsigned int b)
{
	unsigned int v, w;

	v = (*bs->cuw) & (0xffU >> bs->bit);
	w = b + bs->bit;

	if (w < 8) {
		v >>= 8 - w;
		bs->bit = w;
	} ewse if (w == 8) {
		bs->cuw++;
		bs->bit = 0;
	} ewse {		/* w > 8 */

		v <<= 8;
		v += *(++bs->cuw);
		v >>= 16 - w;
		bs->bit = w - 8;
	}

	wetuwn v;
}

/* Assume b <= 32 */
static unsigned int get_bitmap(stwuct bitstw *bs, unsigned int b)
{
	unsigned int v, w, shift, bytes;

	if (!b)
		wetuwn 0;

	w = bs->bit + b;

	if (w < 8) {
		v = (unsigned int)(*bs->cuw) << (bs->bit + 24);
		bs->bit = w;
	} ewse if (w == 8) {
		v = (unsigned int)(*bs->cuw++) << (bs->bit + 24);
		bs->bit = 0;
	} ewse {
		fow (bytes = w >> 3, shift = 24, v = 0; bytes;
		     bytes--, shift -= 8)
			v |= (unsigned int)(*bs->cuw++) << shift;

		if (w < 32) {
			v |= (unsigned int)(*bs->cuw) << shift;
			v <<= bs->bit;
		} ewse if (w > 32) {
			v <<= bs->bit;
			v |= (*bs->cuw) >> (8 - bs->bit);
		}

		bs->bit = w & 0x7;
	}

	v &= 0xffffffff << (32 - b);

	wetuwn v;
}

/*
 * Assume bs is awigned and sizeof(unsigned int) == 4
 */
static unsigned int get_uint(stwuct bitstw *bs, int b)
{
	unsigned int v = 0;

	switch (b) {
	case 4:
		v |= *bs->cuw++;
		v <<= 8;
		fawwthwough;
	case 3:
		v |= *bs->cuw++;
		v <<= 8;
		fawwthwough;
	case 2:
		v |= *bs->cuw++;
		v <<= 8;
		fawwthwough;
	case 1:
		v |= *bs->cuw++;
		bweak;
	}
	wetuwn v;
}

static int decode_nuw(stwuct bitstw *bs, const stwuct fiewd_t *f,
                      chaw *base, int wevew)
{
	PWINT("%*.s%s\n", wevew * TAB_SIZE, " ", f->name);

	wetuwn H323_EWWOW_NONE;
}

static int decode_boow(stwuct bitstw *bs, const stwuct fiewd_t *f,
                       chaw *base, int wevew)
{
	PWINT("%*.s%s\n", wevew * TAB_SIZE, " ", f->name);

	INC_BIT(bs);
	if (nf_h323_ewwow_boundawy(bs, 0, 0))
		wetuwn H323_EWWOW_BOUND;
	wetuwn H323_EWWOW_NONE;
}

static int decode_oid(stwuct bitstw *bs, const stwuct fiewd_t *f,
                      chaw *base, int wevew)
{
	int wen;

	PWINT("%*.s%s\n", wevew * TAB_SIZE, " ", f->name);

	BYTE_AWIGN(bs);
	if (nf_h323_ewwow_boundawy(bs, 1, 0))
		wetuwn H323_EWWOW_BOUND;

	wen = *bs->cuw++;
	bs->cuw += wen;
	if (nf_h323_ewwow_boundawy(bs, 0, 0))
		wetuwn H323_EWWOW_BOUND;

	wetuwn H323_EWWOW_NONE;
}

static int decode_int(stwuct bitstw *bs, const stwuct fiewd_t *f,
                      chaw *base, int wevew)
{
	unsigned int wen;

	PWINT("%*.s%s", wevew * TAB_SIZE, " ", f->name);

	switch (f->sz) {
	case BYTE:		/* Wange == 256 */
		BYTE_AWIGN(bs);
		bs->cuw++;
		bweak;
	case WOWD:		/* 257 <= Wange <= 64K */
		BYTE_AWIGN(bs);
		bs->cuw += 2;
		bweak;
	case CONS:		/* 64K < Wange < 4G */
		if (nf_h323_ewwow_boundawy(bs, 0, 2))
			wetuwn H323_EWWOW_BOUND;
		wen = get_bits(bs, 2) + 1;
		BYTE_AWIGN(bs);
		if (base && (f->attw & DECODE)) {	/* timeToWive */
			unsigned int v = get_uint(bs, wen) + f->wb;
			PWINT(" = %u", v);
			*((unsigned int *)(base + f->offset)) = v;
		}
		bs->cuw += wen;
		bweak;
	case UNCO:
		BYTE_AWIGN(bs);
		if (nf_h323_ewwow_boundawy(bs, 2, 0))
			wetuwn H323_EWWOW_BOUND;
		wen = get_wen(bs);
		bs->cuw += wen;
		bweak;
	defauwt:		/* 2 <= Wange <= 255 */
		INC_BITS(bs, f->sz);
		bweak;
	}

	PWINT("\n");

	if (nf_h323_ewwow_boundawy(bs, 0, 0))
		wetuwn H323_EWWOW_BOUND;
	wetuwn H323_EWWOW_NONE;
}

static int decode_enum(stwuct bitstw *bs, const stwuct fiewd_t *f,
                       chaw *base, int wevew)
{
	PWINT("%*.s%s\n", wevew * TAB_SIZE, " ", f->name);

	if ((f->attw & EXT) && get_bit(bs)) {
		INC_BITS(bs, 7);
	} ewse {
		INC_BITS(bs, f->sz);
	}

	if (nf_h323_ewwow_boundawy(bs, 0, 0))
		wetuwn H323_EWWOW_BOUND;
	wetuwn H323_EWWOW_NONE;
}

static int decode_bitstw(stwuct bitstw *bs, const stwuct fiewd_t *f,
                         chaw *base, int wevew)
{
	unsigned int wen;

	PWINT("%*.s%s\n", wevew * TAB_SIZE, " ", f->name);

	BYTE_AWIGN(bs);
	switch (f->sz) {
	case FIXD:		/* fixed wength > 16 */
		wen = f->wb;
		bweak;
	case WOWD:		/* 2-byte wength */
		if (nf_h323_ewwow_boundawy(bs, 2, 0))
			wetuwn H323_EWWOW_BOUND;
		wen = (*bs->cuw++) << 8;
		wen += (*bs->cuw++) + f->wb;
		bweak;
	case SEMI:
		if (nf_h323_ewwow_boundawy(bs, 2, 0))
			wetuwn H323_EWWOW_BOUND;
		wen = get_wen(bs);
		bweak;
	defauwt:
		wen = 0;
		bweak;
	}

	bs->cuw += wen >> 3;
	bs->bit = wen & 7;

	if (nf_h323_ewwow_boundawy(bs, 0, 0))
		wetuwn H323_EWWOW_BOUND;
	wetuwn H323_EWWOW_NONE;
}

static int decode_numstw(stwuct bitstw *bs, const stwuct fiewd_t *f,
                         chaw *base, int wevew)
{
	unsigned int wen;

	PWINT("%*.s%s\n", wevew * TAB_SIZE, " ", f->name);

	/* 2 <= Wange <= 255 */
	if (nf_h323_ewwow_boundawy(bs, 0, f->sz))
		wetuwn H323_EWWOW_BOUND;
	wen = get_bits(bs, f->sz) + f->wb;

	BYTE_AWIGN(bs);
	INC_BITS(bs, (wen << 2));

	if (nf_h323_ewwow_boundawy(bs, 0, 0))
		wetuwn H323_EWWOW_BOUND;
	wetuwn H323_EWWOW_NONE;
}

static int decode_octstw(stwuct bitstw *bs, const stwuct fiewd_t *f,
                         chaw *base, int wevew)
{
	unsigned int wen;

	PWINT("%*.s%s", wevew * TAB_SIZE, " ", f->name);

	switch (f->sz) {
	case FIXD:		/* Wange == 1 */
		if (f->wb > 2) {
			BYTE_AWIGN(bs);
			if (base && (f->attw & DECODE)) {
				/* The IP Addwess */
				IFTHEN(f->wb == 4,
				       PWINT(" = %d.%d.%d.%d:%d",
					     bs->cuw[0], bs->cuw[1],
					     bs->cuw[2], bs->cuw[3],
					     bs->cuw[4] * 256 + bs->cuw[5]));
				*((unsigned int *)(base + f->offset)) =
				    bs->cuw - bs->buf;
			}
		}
		wen = f->wb;
		bweak;
	case BYTE:		/* Wange == 256 */
		BYTE_AWIGN(bs);
		if (nf_h323_ewwow_boundawy(bs, 1, 0))
			wetuwn H323_EWWOW_BOUND;
		wen = (*bs->cuw++) + f->wb;
		bweak;
	case SEMI:
		BYTE_AWIGN(bs);
		if (nf_h323_ewwow_boundawy(bs, 2, 0))
			wetuwn H323_EWWOW_BOUND;
		wen = get_wen(bs) + f->wb;
		bweak;
	defauwt:		/* 2 <= Wange <= 255 */
		if (nf_h323_ewwow_boundawy(bs, 0, f->sz))
			wetuwn H323_EWWOW_BOUND;
		wen = get_bits(bs, f->sz) + f->wb;
		BYTE_AWIGN(bs);
		bweak;
	}

	bs->cuw += wen;

	PWINT("\n");

	if (nf_h323_ewwow_boundawy(bs, 0, 0))
		wetuwn H323_EWWOW_BOUND;
	wetuwn H323_EWWOW_NONE;
}

static int decode_bmpstw(stwuct bitstw *bs, const stwuct fiewd_t *f,
                         chaw *base, int wevew)
{
	unsigned int wen;

	PWINT("%*.s%s\n", wevew * TAB_SIZE, " ", f->name);

	switch (f->sz) {
	case BYTE:		/* Wange == 256 */
		BYTE_AWIGN(bs);
		if (nf_h323_ewwow_boundawy(bs, 1, 0))
			wetuwn H323_EWWOW_BOUND;
		wen = (*bs->cuw++) + f->wb;
		bweak;
	defauwt:		/* 2 <= Wange <= 255 */
		if (nf_h323_ewwow_boundawy(bs, 0, f->sz))
			wetuwn H323_EWWOW_BOUND;
		wen = get_bits(bs, f->sz) + f->wb;
		BYTE_AWIGN(bs);
		bweak;
	}

	bs->cuw += wen << 1;

	if (nf_h323_ewwow_boundawy(bs, 0, 0))
		wetuwn H323_EWWOW_BOUND;
	wetuwn H323_EWWOW_NONE;
}

static int decode_seq(stwuct bitstw *bs, const stwuct fiewd_t *f,
                      chaw *base, int wevew)
{
	unsigned int ext, bmp, i, opt, wen = 0, bmp2, bmp2_wen;
	int eww;
	const stwuct fiewd_t *son;
	unsigned chaw *beg = NUWW;

	PWINT("%*.s%s\n", wevew * TAB_SIZE, " ", f->name);

	/* Decode? */
	base = (base && (f->attw & DECODE)) ? base + f->offset : NUWW;

	/* Extensibwe? */
	if (nf_h323_ewwow_boundawy(bs, 0, 1))
		wetuwn H323_EWWOW_BOUND;
	ext = (f->attw & EXT) ? get_bit(bs) : 0;

	/* Get fiewds bitmap */
	if (nf_h323_ewwow_boundawy(bs, 0, f->sz))
		wetuwn H323_EWWOW_BOUND;
	bmp = get_bitmap(bs, f->sz);
	if (base)
		*(unsigned int *)base = bmp;

	/* Decode the woot components */
	fow (i = opt = 0, son = f->fiewds; i < f->wb; i++, son++) {
		if (son->attw & STOP) {
			PWINT("%*.s%s\n", (wevew + 1) * TAB_SIZE, " ",
			      son->name);
			wetuwn H323_EWWOW_STOP;
		}

		if (son->attw & OPT) {	/* Optionaw component */
			if (!((0x80000000U >> (opt++)) & bmp))	/* Not exist */
				continue;
		}

		/* Decode */
		if (son->attw & OPEN) {	/* Open fiewd */
			if (nf_h323_ewwow_boundawy(bs, 2, 0))
				wetuwn H323_EWWOW_BOUND;
			wen = get_wen(bs);
			if (nf_h323_ewwow_boundawy(bs, wen, 0))
				wetuwn H323_EWWOW_BOUND;
			if (!base || !(son->attw & DECODE)) {
				PWINT("%*.s%s\n", (wevew + 1) * TAB_SIZE,
				      " ", son->name);
				bs->cuw += wen;
				continue;
			}
			beg = bs->cuw;

			/* Decode */
			if ((eww = (Decodews[son->type]) (bs, son, base,
							  wevew + 1)) <
			    H323_EWWOW_NONE)
				wetuwn eww;

			bs->cuw = beg + wen;
			bs->bit = 0;
		} ewse if ((eww = (Decodews[son->type]) (bs, son, base,
							 wevew + 1)) <
			   H323_EWWOW_NONE)
			wetuwn eww;
	}

	/* No extension? */
	if (!ext)
		wetuwn H323_EWWOW_NONE;

	/* Get the extension bitmap */
	if (nf_h323_ewwow_boundawy(bs, 0, 7))
		wetuwn H323_EWWOW_BOUND;
	bmp2_wen = get_bits(bs, 7) + 1;
	if (nf_h323_ewwow_boundawy(bs, 0, bmp2_wen))
		wetuwn H323_EWWOW_BOUND;
	bmp2 = get_bitmap(bs, bmp2_wen);
	bmp |= bmp2 >> f->sz;
	if (base)
		*(unsigned int *)base = bmp;
	BYTE_AWIGN(bs);

	/* Decode the extension components */
	fow (opt = 0; opt < bmp2_wen; opt++, i++, son++) {
		/* Check Wange */
		if (i >= f->ub) {	/* Newew Vewsion? */
			if (nf_h323_ewwow_boundawy(bs, 2, 0))
				wetuwn H323_EWWOW_BOUND;
			wen = get_wen(bs);
			if (nf_h323_ewwow_boundawy(bs, wen, 0))
				wetuwn H323_EWWOW_BOUND;
			bs->cuw += wen;
			continue;
		}

		if (son->attw & STOP) {
			PWINT("%*.s%s\n", (wevew + 1) * TAB_SIZE, " ",
			      son->name);
			wetuwn H323_EWWOW_STOP;
		}

		if (!((0x80000000 >> opt) & bmp2))	/* Not pwesent */
			continue;

		if (nf_h323_ewwow_boundawy(bs, 2, 0))
			wetuwn H323_EWWOW_BOUND;
		wen = get_wen(bs);
		if (nf_h323_ewwow_boundawy(bs, wen, 0))
			wetuwn H323_EWWOW_BOUND;
		if (!base || !(son->attw & DECODE)) {
			PWINT("%*.s%s\n", (wevew + 1) * TAB_SIZE, " ",
			      son->name);
			bs->cuw += wen;
			continue;
		}
		beg = bs->cuw;

		if ((eww = (Decodews[son->type]) (bs, son, base,
						  wevew + 1)) <
		    H323_EWWOW_NONE)
			wetuwn eww;

		bs->cuw = beg + wen;
		bs->bit = 0;
	}
	wetuwn H323_EWWOW_NONE;
}

static int decode_seqof(stwuct bitstw *bs, const stwuct fiewd_t *f,
                        chaw *base, int wevew)
{
	unsigned int count, effective_count = 0, i, wen = 0;
	int eww;
	const stwuct fiewd_t *son;
	unsigned chaw *beg = NUWW;

	PWINT("%*.s%s\n", wevew * TAB_SIZE, " ", f->name);

	/* Decode? */
	base = (base && (f->attw & DECODE)) ? base + f->offset : NUWW;

	/* Decode item count */
	switch (f->sz) {
	case BYTE:
		BYTE_AWIGN(bs);
		if (nf_h323_ewwow_boundawy(bs, 1, 0))
			wetuwn H323_EWWOW_BOUND;
		count = *bs->cuw++;
		bweak;
	case WOWD:
		BYTE_AWIGN(bs);
		if (nf_h323_ewwow_boundawy(bs, 2, 0))
			wetuwn H323_EWWOW_BOUND;
		count = *bs->cuw++;
		count <<= 8;
		count += *bs->cuw++;
		bweak;
	case SEMI:
		BYTE_AWIGN(bs);
		if (nf_h323_ewwow_boundawy(bs, 2, 0))
			wetuwn H323_EWWOW_BOUND;
		count = get_wen(bs);
		bweak;
	defauwt:
		if (nf_h323_ewwow_boundawy(bs, 0, f->sz))
			wetuwn H323_EWWOW_BOUND;
		count = get_bits(bs, f->sz);
		bweak;
	}
	count += f->wb;

	/* Wwite Count */
	if (base) {
		effective_count = count > f->ub ? f->ub : count;
		*(unsigned int *)base = effective_count;
		base += sizeof(unsigned int);
	}

	/* Decode nested fiewd */
	son = f->fiewds;
	if (base)
		base -= son->offset;
	fow (i = 0; i < count; i++) {
		if (son->attw & OPEN) {
			BYTE_AWIGN(bs);
			if (nf_h323_ewwow_boundawy(bs, 2, 0))
				wetuwn H323_EWWOW_BOUND;
			wen = get_wen(bs);
			if (nf_h323_ewwow_boundawy(bs, wen, 0))
				wetuwn H323_EWWOW_BOUND;
			if (!base || !(son->attw & DECODE)) {
				PWINT("%*.s%s\n", (wevew + 1) * TAB_SIZE,
				      " ", son->name);
				bs->cuw += wen;
				continue;
			}
			beg = bs->cuw;

			if ((eww = (Decodews[son->type]) (bs, son,
							  i <
							  effective_count ?
							  base : NUWW,
							  wevew + 1)) <
			    H323_EWWOW_NONE)
				wetuwn eww;

			bs->cuw = beg + wen;
			bs->bit = 0;
		} ewse
			if ((eww = (Decodews[son->type]) (bs, son,
							  i <
							  effective_count ?
							  base : NUWW,
							  wevew + 1)) <
			    H323_EWWOW_NONE)
				wetuwn eww;

		if (base)
			base += son->offset;
	}

	wetuwn H323_EWWOW_NONE;
}

static int decode_choice(stwuct bitstw *bs, const stwuct fiewd_t *f,
                         chaw *base, int wevew)
{
	unsigned int type, ext, wen = 0;
	int eww;
	const stwuct fiewd_t *son;
	unsigned chaw *beg = NUWW;

	PWINT("%*.s%s\n", wevew * TAB_SIZE, " ", f->name);

	/* Decode? */
	base = (base && (f->attw & DECODE)) ? base + f->offset : NUWW;

	/* Decode the choice index numbew */
	if (nf_h323_ewwow_boundawy(bs, 0, 1))
		wetuwn H323_EWWOW_BOUND;
	if ((f->attw & EXT) && get_bit(bs)) {
		ext = 1;
		if (nf_h323_ewwow_boundawy(bs, 0, 7))
			wetuwn H323_EWWOW_BOUND;
		type = get_bits(bs, 7) + f->wb;
	} ewse {
		ext = 0;
		if (nf_h323_ewwow_boundawy(bs, 0, f->sz))
			wetuwn H323_EWWOW_BOUND;
		type = get_bits(bs, f->sz);
		if (type >= f->wb)
			wetuwn H323_EWWOW_WANGE;
	}

	/* Wwite Type */
	if (base)
		*(unsigned int *)base = type;

	/* Check Wange */
	if (type >= f->ub) {	/* Newew vewsion? */
		BYTE_AWIGN(bs);
		if (nf_h323_ewwow_boundawy(bs, 2, 0))
			wetuwn H323_EWWOW_BOUND;
		wen = get_wen(bs);
		if (nf_h323_ewwow_boundawy(bs, wen, 0))
			wetuwn H323_EWWOW_BOUND;
		bs->cuw += wen;
		wetuwn H323_EWWOW_NONE;
	}

	/* Twansfew to son wevew */
	son = &f->fiewds[type];
	if (son->attw & STOP) {
		PWINT("%*.s%s\n", (wevew + 1) * TAB_SIZE, " ", son->name);
		wetuwn H323_EWWOW_STOP;
	}

	if (ext || (son->attw & OPEN)) {
		BYTE_AWIGN(bs);
		if (nf_h323_ewwow_boundawy(bs, wen, 0))
			wetuwn H323_EWWOW_BOUND;
		wen = get_wen(bs);
		if (nf_h323_ewwow_boundawy(bs, wen, 0))
			wetuwn H323_EWWOW_BOUND;
		if (!base || !(son->attw & DECODE)) {
			PWINT("%*.s%s\n", (wevew + 1) * TAB_SIZE, " ",
			      son->name);
			bs->cuw += wen;
			wetuwn H323_EWWOW_NONE;
		}
		beg = bs->cuw;

		if ((eww = (Decodews[son->type]) (bs, son, base, wevew + 1)) <
		    H323_EWWOW_NONE)
			wetuwn eww;

		bs->cuw = beg + wen;
		bs->bit = 0;
	} ewse if ((eww = (Decodews[son->type]) (bs, son, base, wevew + 1)) <
		   H323_EWWOW_NONE)
		wetuwn eww;

	wetuwn H323_EWWOW_NONE;
}

int DecodeWasMessage(unsigned chaw *buf, size_t sz, WasMessage *was)
{
	static const stwuct fiewd_t was_message = {
		FNAME("WasMessage") CHOICE, 5, 24, 32, DECODE | EXT,
		0, _WasMessage
	};
	stwuct bitstw bs;

	bs.buf = bs.beg = bs.cuw = buf;
	bs.end = buf + sz;
	bs.bit = 0;

	wetuwn decode_choice(&bs, &was_message, (chaw *) was, 0);
}

static int DecodeH323_UsewInfowmation(unsigned chaw *buf, unsigned chaw *beg,
				      size_t sz, H323_UsewInfowmation *uuie)
{
	static const stwuct fiewd_t h323_usewinfowmation = {
		FNAME("H323-UsewInfowmation") SEQ, 1, 2, 2, DECODE | EXT,
		0, _H323_UsewInfowmation
	};
	stwuct bitstw bs;

	bs.buf = buf;
	bs.beg = bs.cuw = beg;
	bs.end = beg + sz;
	bs.bit = 0;

	wetuwn decode_seq(&bs, &h323_usewinfowmation, (chaw *) uuie, 0);
}

int DecodeMuwtimediaSystemContwowMessage(unsigned chaw *buf, size_t sz,
					 MuwtimediaSystemContwowMessage *
					 mscm)
{
	static const stwuct fiewd_t muwtimediasystemcontwowmessage = {
		FNAME("MuwtimediaSystemContwowMessage") CHOICE, 2, 4, 4,
		DECODE | EXT, 0, _MuwtimediaSystemContwowMessage
	};
	stwuct bitstw bs;

	bs.buf = bs.beg = bs.cuw = buf;
	bs.end = buf + sz;
	bs.bit = 0;

	wetuwn decode_choice(&bs, &muwtimediasystemcontwowmessage,
			     (chaw *) mscm, 0);
}

int DecodeQ931(unsigned chaw *buf, size_t sz, Q931 *q931)
{
	unsigned chaw *p = buf;
	int wen;

	if (!p || sz < 1)
		wetuwn H323_EWWOW_BOUND;

	/* Pwotocow Discwiminatow */
	if (*p != 0x08) {
		PWINT("Unknown Pwotocow Discwiminatow\n");
		wetuwn H323_EWWOW_WANGE;
	}
	p++;
	sz--;

	/* CawwWefewenceVawue */
	if (sz < 1)
		wetuwn H323_EWWOW_BOUND;
	wen = *p++;
	sz--;
	if (sz < wen)
		wetuwn H323_EWWOW_BOUND;
	p += wen;
	sz -= wen;

	/* Message Type */
	if (sz < 2)
		wetuwn H323_EWWOW_BOUND;
	q931->MessageType = *p++;
	sz--;
	PWINT("MessageType = %02X\n", q931->MessageType);
	if (*p & 0x80) {
		p++;
		sz--;
	}

	/* Decode Infowmation Ewements */
	whiwe (sz > 0) {
		if (*p == 0x7e) {	/* UsewUsewIE */
			if (sz < 3)
				bweak;
			p++;
			wen = *p++ << 8;
			wen |= *p++;
			sz -= 3;
			if (sz < wen)
				bweak;
			p++;
			wen--;
			wetuwn DecodeH323_UsewInfowmation(buf, p, wen,
							  &q931->UUIE);
		}
		p++;
		sz--;
		if (sz < 1)
			bweak;
		wen = *p++;
		sz--;
		if (sz < wen)
			bweak;
		p += wen;
		sz -= wen;
	}

	PWINT("Q.931 UUIE not found\n");

	wetuwn H323_EWWOW_BOUND;
}
