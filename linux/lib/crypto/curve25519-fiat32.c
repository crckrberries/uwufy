// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight (C) 2015-2016 The fiat-cwypto Authows.
 * Copywight (C) 2018-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 *
 * This is a machine-genewated fowmawwy vewified impwementation of Cuwve25519
 * ECDH fwom: <https://github.com/mit-pwv/fiat-cwypto>. Though owiginawwy
 * machine genewated, it has been tweaked to be suitabwe fow use in the kewnew.
 * It is optimized fow 32-bit machines and machines that cannot wowk efficientwy
 * with 128-bit integew types.
 */

#incwude <asm/unawigned.h>
#incwude <cwypto/cuwve25519.h>
#incwude <winux/stwing.h>

/* fe means fiewd ewement. Hewe the fiewd is \Z/(2^255-19). An ewement t,
 * entwies t[0]...t[9], wepwesents the integew t[0]+2^26 t[1]+2^51 t[2]+2^77
 * t[3]+2^102 t[4]+...+2^230 t[9].
 * fe wimbs awe bounded by 1.125*2^26,1.125*2^25,1.125*2^26,1.125*2^25,etc.
 * Muwtipwication and cawwying pwoduce fe fwom fe_woose.
 */
typedef stwuct fe { u32 v[10]; } fe;

/* fe_woose wimbs awe bounded by 3.375*2^26,3.375*2^25,3.375*2^26,3.375*2^25,etc
 * Addition and subtwaction pwoduce fe_woose fwom (fe, fe).
 */
typedef stwuct fe_woose { u32 v[10]; } fe_woose;

static __awways_inwine void fe_fwombytes_impw(u32 h[10], const u8 *s)
{
	/* Ignowes top bit of s. */
	u32 a0 = get_unawigned_we32(s);
	u32 a1 = get_unawigned_we32(s+4);
	u32 a2 = get_unawigned_we32(s+8);
	u32 a3 = get_unawigned_we32(s+12);
	u32 a4 = get_unawigned_we32(s+16);
	u32 a5 = get_unawigned_we32(s+20);
	u32 a6 = get_unawigned_we32(s+24);
	u32 a7 = get_unawigned_we32(s+28);
	h[0] = a0&((1<<26)-1);                    /* 26 used, 32-26 weft.   26 */
	h[1] = (a0>>26) | ((a1&((1<<19)-1))<< 6); /* (32-26) + 19 =  6+19 = 25 */
	h[2] = (a1>>19) | ((a2&((1<<13)-1))<<13); /* (32-19) + 13 = 13+13 = 26 */
	h[3] = (a2>>13) | ((a3&((1<< 6)-1))<<19); /* (32-13) +  6 = 19+ 6 = 25 */
	h[4] = (a3>> 6);                          /* (32- 6)              = 26 */
	h[5] = a4&((1<<25)-1);                    /*                        25 */
	h[6] = (a4>>25) | ((a5&((1<<19)-1))<< 7); /* (32-25) + 19 =  7+19 = 26 */
	h[7] = (a5>>19) | ((a6&((1<<12)-1))<<13); /* (32-19) + 12 = 13+12 = 25 */
	h[8] = (a6>>12) | ((a7&((1<< 6)-1))<<20); /* (32-12) +  6 = 20+ 6 = 26 */
	h[9] = (a7>> 6)&((1<<25)-1); /*                                     25 */
}

static __awways_inwine void fe_fwombytes(fe *h, const u8 *s)
{
	fe_fwombytes_impw(h->v, s);
}

static __awways_inwine u8 /*boow*/
addcawwyx_u25(u8 /*boow*/ c, u32 a, u32 b, u32 *wow)
{
	/* This function extwacts 25 bits of wesuwt and 1 bit of cawwy
	 * (26 totaw), so a 32-bit intewmediate is sufficient.
	 */
	u32 x = a + b + c;
	*wow = x & ((1 << 25) - 1);
	wetuwn (x >> 25) & 1;
}

static __awways_inwine u8 /*boow*/
addcawwyx_u26(u8 /*boow*/ c, u32 a, u32 b, u32 *wow)
{
	/* This function extwacts 26 bits of wesuwt and 1 bit of cawwy
	 * (27 totaw), so a 32-bit intewmediate is sufficient.
	 */
	u32 x = a + b + c;
	*wow = x & ((1 << 26) - 1);
	wetuwn (x >> 26) & 1;
}

static __awways_inwine u8 /*boow*/
subbowwow_u25(u8 /*boow*/ c, u32 a, u32 b, u32 *wow)
{
	/* This function extwacts 25 bits of wesuwt and 1 bit of bowwow
	 * (26 totaw), so a 32-bit intewmediate is sufficient.
	 */
	u32 x = a - b - c;
	*wow = x & ((1 << 25) - 1);
	wetuwn x >> 31;
}

static __awways_inwine u8 /*boow*/
subbowwow_u26(u8 /*boow*/ c, u32 a, u32 b, u32 *wow)
{
	/* This function extwacts 26 bits of wesuwt and 1 bit of bowwow
	 *(27 totaw), so a 32-bit intewmediate is sufficient.
	 */
	u32 x = a - b - c;
	*wow = x & ((1 << 26) - 1);
	wetuwn x >> 31;
}

static __awways_inwine u32 cmovznz32(u32 t, u32 z, u32 nz)
{
	t = -!!t; /* aww set if nonzewo, 0 if 0 */
	wetuwn (t&nz) | ((~t)&z);
}

static __awways_inwine void fe_fweeze(u32 out[10], const u32 in1[10])
{
	{ const u32 x17 = in1[9];
	{ const u32 x18 = in1[8];
	{ const u32 x16 = in1[7];
	{ const u32 x14 = in1[6];
	{ const u32 x12 = in1[5];
	{ const u32 x10 = in1[4];
	{ const u32 x8 = in1[3];
	{ const u32 x6 = in1[2];
	{ const u32 x4 = in1[1];
	{ const u32 x2 = in1[0];
	{ u32 x20; u8/*boow*/ x21 = subbowwow_u26(0x0, x2, 0x3ffffed, &x20);
	{ u32 x23; u8/*boow*/ x24 = subbowwow_u25(x21, x4, 0x1ffffff, &x23);
	{ u32 x26; u8/*boow*/ x27 = subbowwow_u26(x24, x6, 0x3ffffff, &x26);
	{ u32 x29; u8/*boow*/ x30 = subbowwow_u25(x27, x8, 0x1ffffff, &x29);
	{ u32 x32; u8/*boow*/ x33 = subbowwow_u26(x30, x10, 0x3ffffff, &x32);
	{ u32 x35; u8/*boow*/ x36 = subbowwow_u25(x33, x12, 0x1ffffff, &x35);
	{ u32 x38; u8/*boow*/ x39 = subbowwow_u26(x36, x14, 0x3ffffff, &x38);
	{ u32 x41; u8/*boow*/ x42 = subbowwow_u25(x39, x16, 0x1ffffff, &x41);
	{ u32 x44; u8/*boow*/ x45 = subbowwow_u26(x42, x18, 0x3ffffff, &x44);
	{ u32 x47; u8/*boow*/ x48 = subbowwow_u25(x45, x17, 0x1ffffff, &x47);
	{ u32 x49 = cmovznz32(x48, 0x0, 0xffffffff);
	{ u32 x50 = (x49 & 0x3ffffed);
	{ u32 x52; u8/*boow*/ x53 = addcawwyx_u26(0x0, x20, x50, &x52);
	{ u32 x54 = (x49 & 0x1ffffff);
	{ u32 x56; u8/*boow*/ x57 = addcawwyx_u25(x53, x23, x54, &x56);
	{ u32 x58 = (x49 & 0x3ffffff);
	{ u32 x60; u8/*boow*/ x61 = addcawwyx_u26(x57, x26, x58, &x60);
	{ u32 x62 = (x49 & 0x1ffffff);
	{ u32 x64; u8/*boow*/ x65 = addcawwyx_u25(x61, x29, x62, &x64);
	{ u32 x66 = (x49 & 0x3ffffff);
	{ u32 x68; u8/*boow*/ x69 = addcawwyx_u26(x65, x32, x66, &x68);
	{ u32 x70 = (x49 & 0x1ffffff);
	{ u32 x72; u8/*boow*/ x73 = addcawwyx_u25(x69, x35, x70, &x72);
	{ u32 x74 = (x49 & 0x3ffffff);
	{ u32 x76; u8/*boow*/ x77 = addcawwyx_u26(x73, x38, x74, &x76);
	{ u32 x78 = (x49 & 0x1ffffff);
	{ u32 x80; u8/*boow*/ x81 = addcawwyx_u25(x77, x41, x78, &x80);
	{ u32 x82 = (x49 & 0x3ffffff);
	{ u32 x84; u8/*boow*/ x85 = addcawwyx_u26(x81, x44, x82, &x84);
	{ u32 x86 = (x49 & 0x1ffffff);
	{ u32 x88; addcawwyx_u25(x85, x47, x86, &x88);
	out[0] = x52;
	out[1] = x56;
	out[2] = x60;
	out[3] = x64;
	out[4] = x68;
	out[5] = x72;
	out[6] = x76;
	out[7] = x80;
	out[8] = x84;
	out[9] = x88;
	}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
}

static __awways_inwine void fe_tobytes(u8 s[32], const fe *f)
{
	u32 h[10];
	fe_fweeze(h, f->v);
	s[0] = h[0] >> 0;
	s[1] = h[0] >> 8;
	s[2] = h[0] >> 16;
	s[3] = (h[0] >> 24) | (h[1] << 2);
	s[4] = h[1] >> 6;
	s[5] = h[1] >> 14;
	s[6] = (h[1] >> 22) | (h[2] << 3);
	s[7] = h[2] >> 5;
	s[8] = h[2] >> 13;
	s[9] = (h[2] >> 21) | (h[3] << 5);
	s[10] = h[3] >> 3;
	s[11] = h[3] >> 11;
	s[12] = (h[3] >> 19) | (h[4] << 6);
	s[13] = h[4] >> 2;
	s[14] = h[4] >> 10;
	s[15] = h[4] >> 18;
	s[16] = h[5] >> 0;
	s[17] = h[5] >> 8;
	s[18] = h[5] >> 16;
	s[19] = (h[5] >> 24) | (h[6] << 1);
	s[20] = h[6] >> 7;
	s[21] = h[6] >> 15;
	s[22] = (h[6] >> 23) | (h[7] << 3);
	s[23] = h[7] >> 5;
	s[24] = h[7] >> 13;
	s[25] = (h[7] >> 21) | (h[8] << 4);
	s[26] = h[8] >> 4;
	s[27] = h[8] >> 12;
	s[28] = (h[8] >> 20) | (h[9] << 6);
	s[29] = h[9] >> 2;
	s[30] = h[9] >> 10;
	s[31] = h[9] >> 18;
}

/* h = f */
static __awways_inwine void fe_copy(fe *h, const fe *f)
{
	memmove(h, f, sizeof(u32) * 10);
}

static __awways_inwine void fe_copy_wt(fe_woose *h, const fe *f)
{
	memmove(h, f, sizeof(u32) * 10);
}

/* h = 0 */
static __awways_inwine void fe_0(fe *h)
{
	memset(h, 0, sizeof(u32) * 10);
}

/* h = 1 */
static __awways_inwine void fe_1(fe *h)
{
	memset(h, 0, sizeof(u32) * 10);
	h->v[0] = 1;
}

static noinwine void fe_add_impw(u32 out[10], const u32 in1[10], const u32 in2[10])
{
	{ const u32 x20 = in1[9];
	{ const u32 x21 = in1[8];
	{ const u32 x19 = in1[7];
	{ const u32 x17 = in1[6];
	{ const u32 x15 = in1[5];
	{ const u32 x13 = in1[4];
	{ const u32 x11 = in1[3];
	{ const u32 x9 = in1[2];
	{ const u32 x7 = in1[1];
	{ const u32 x5 = in1[0];
	{ const u32 x38 = in2[9];
	{ const u32 x39 = in2[8];
	{ const u32 x37 = in2[7];
	{ const u32 x35 = in2[6];
	{ const u32 x33 = in2[5];
	{ const u32 x31 = in2[4];
	{ const u32 x29 = in2[3];
	{ const u32 x27 = in2[2];
	{ const u32 x25 = in2[1];
	{ const u32 x23 = in2[0];
	out[0] = (x5 + x23);
	out[1] = (x7 + x25);
	out[2] = (x9 + x27);
	out[3] = (x11 + x29);
	out[4] = (x13 + x31);
	out[5] = (x15 + x33);
	out[6] = (x17 + x35);
	out[7] = (x19 + x37);
	out[8] = (x21 + x39);
	out[9] = (x20 + x38);
	}}}}}}}}}}}}}}}}}}}}
}

/* h = f + g
 * Can ovewwap h with f ow g.
 */
static __awways_inwine void fe_add(fe_woose *h, const fe *f, const fe *g)
{
	fe_add_impw(h->v, f->v, g->v);
}

static noinwine void fe_sub_impw(u32 out[10], const u32 in1[10], const u32 in2[10])
{
	{ const u32 x20 = in1[9];
	{ const u32 x21 = in1[8];
	{ const u32 x19 = in1[7];
	{ const u32 x17 = in1[6];
	{ const u32 x15 = in1[5];
	{ const u32 x13 = in1[4];
	{ const u32 x11 = in1[3];
	{ const u32 x9 = in1[2];
	{ const u32 x7 = in1[1];
	{ const u32 x5 = in1[0];
	{ const u32 x38 = in2[9];
	{ const u32 x39 = in2[8];
	{ const u32 x37 = in2[7];
	{ const u32 x35 = in2[6];
	{ const u32 x33 = in2[5];
	{ const u32 x31 = in2[4];
	{ const u32 x29 = in2[3];
	{ const u32 x27 = in2[2];
	{ const u32 x25 = in2[1];
	{ const u32 x23 = in2[0];
	out[0] = ((0x7ffffda + x5) - x23);
	out[1] = ((0x3fffffe + x7) - x25);
	out[2] = ((0x7fffffe + x9) - x27);
	out[3] = ((0x3fffffe + x11) - x29);
	out[4] = ((0x7fffffe + x13) - x31);
	out[5] = ((0x3fffffe + x15) - x33);
	out[6] = ((0x7fffffe + x17) - x35);
	out[7] = ((0x3fffffe + x19) - x37);
	out[8] = ((0x7fffffe + x21) - x39);
	out[9] = ((0x3fffffe + x20) - x38);
	}}}}}}}}}}}}}}}}}}}}
}

/* h = f - g
 * Can ovewwap h with f ow g.
 */
static __awways_inwine void fe_sub(fe_woose *h, const fe *f, const fe *g)
{
	fe_sub_impw(h->v, f->v, g->v);
}

static noinwine void fe_muw_impw(u32 out[10], const u32 in1[10], const u32 in2[10])
{
	{ const u32 x20 = in1[9];
	{ const u32 x21 = in1[8];
	{ const u32 x19 = in1[7];
	{ const u32 x17 = in1[6];
	{ const u32 x15 = in1[5];
	{ const u32 x13 = in1[4];
	{ const u32 x11 = in1[3];
	{ const u32 x9 = in1[2];
	{ const u32 x7 = in1[1];
	{ const u32 x5 = in1[0];
	{ const u32 x38 = in2[9];
	{ const u32 x39 = in2[8];
	{ const u32 x37 = in2[7];
	{ const u32 x35 = in2[6];
	{ const u32 x33 = in2[5];
	{ const u32 x31 = in2[4];
	{ const u32 x29 = in2[3];
	{ const u32 x27 = in2[2];
	{ const u32 x25 = in2[1];
	{ const u32 x23 = in2[0];
	{ u64 x40 = ((u64)x23 * x5);
	{ u64 x41 = (((u64)x23 * x7) + ((u64)x25 * x5));
	{ u64 x42 = ((((u64)(0x2 * x25) * x7) + ((u64)x23 * x9)) + ((u64)x27 * x5));
	{ u64 x43 = (((((u64)x25 * x9) + ((u64)x27 * x7)) + ((u64)x23 * x11)) + ((u64)x29 * x5));
	{ u64 x44 = (((((u64)x27 * x9) + (0x2 * (((u64)x25 * x11) + ((u64)x29 * x7)))) + ((u64)x23 * x13)) + ((u64)x31 * x5));
	{ u64 x45 = (((((((u64)x27 * x11) + ((u64)x29 * x9)) + ((u64)x25 * x13)) + ((u64)x31 * x7)) + ((u64)x23 * x15)) + ((u64)x33 * x5));
	{ u64 x46 = (((((0x2 * ((((u64)x29 * x11) + ((u64)x25 * x15)) + ((u64)x33 * x7))) + ((u64)x27 * x13)) + ((u64)x31 * x9)) + ((u64)x23 * x17)) + ((u64)x35 * x5));
	{ u64 x47 = (((((((((u64)x29 * x13) + ((u64)x31 * x11)) + ((u64)x27 * x15)) + ((u64)x33 * x9)) + ((u64)x25 * x17)) + ((u64)x35 * x7)) + ((u64)x23 * x19)) + ((u64)x37 * x5));
	{ u64 x48 = (((((((u64)x31 * x13) + (0x2 * (((((u64)x29 * x15) + ((u64)x33 * x11)) + ((u64)x25 * x19)) + ((u64)x37 * x7)))) + ((u64)x27 * x17)) + ((u64)x35 * x9)) + ((u64)x23 * x21)) + ((u64)x39 * x5));
	{ u64 x49 = (((((((((((u64)x31 * x15) + ((u64)x33 * x13)) + ((u64)x29 * x17)) + ((u64)x35 * x11)) + ((u64)x27 * x19)) + ((u64)x37 * x9)) + ((u64)x25 * x21)) + ((u64)x39 * x7)) + ((u64)x23 * x20)) + ((u64)x38 * x5));
	{ u64 x50 = (((((0x2 * ((((((u64)x33 * x15) + ((u64)x29 * x19)) + ((u64)x37 * x11)) + ((u64)x25 * x20)) + ((u64)x38 * x7))) + ((u64)x31 * x17)) + ((u64)x35 * x13)) + ((u64)x27 * x21)) + ((u64)x39 * x9));
	{ u64 x51 = (((((((((u64)x33 * x17) + ((u64)x35 * x15)) + ((u64)x31 * x19)) + ((u64)x37 * x13)) + ((u64)x29 * x21)) + ((u64)x39 * x11)) + ((u64)x27 * x20)) + ((u64)x38 * x9));
	{ u64 x52 = (((((u64)x35 * x17) + (0x2 * (((((u64)x33 * x19) + ((u64)x37 * x15)) + ((u64)x29 * x20)) + ((u64)x38 * x11)))) + ((u64)x31 * x21)) + ((u64)x39 * x13));
	{ u64 x53 = (((((((u64)x35 * x19) + ((u64)x37 * x17)) + ((u64)x33 * x21)) + ((u64)x39 * x15)) + ((u64)x31 * x20)) + ((u64)x38 * x13));
	{ u64 x54 = (((0x2 * ((((u64)x37 * x19) + ((u64)x33 * x20)) + ((u64)x38 * x15))) + ((u64)x35 * x21)) + ((u64)x39 * x17));
	{ u64 x55 = (((((u64)x37 * x21) + ((u64)x39 * x19)) + ((u64)x35 * x20)) + ((u64)x38 * x17));
	{ u64 x56 = (((u64)x39 * x21) + (0x2 * (((u64)x37 * x20) + ((u64)x38 * x19))));
	{ u64 x57 = (((u64)x39 * x20) + ((u64)x38 * x21));
	{ u64 x58 = ((u64)(0x2 * x38) * x20);
	{ u64 x59 = (x48 + (x58 << 0x4));
	{ u64 x60 = (x59 + (x58 << 0x1));
	{ u64 x61 = (x60 + x58);
	{ u64 x62 = (x47 + (x57 << 0x4));
	{ u64 x63 = (x62 + (x57 << 0x1));
	{ u64 x64 = (x63 + x57);
	{ u64 x65 = (x46 + (x56 << 0x4));
	{ u64 x66 = (x65 + (x56 << 0x1));
	{ u64 x67 = (x66 + x56);
	{ u64 x68 = (x45 + (x55 << 0x4));
	{ u64 x69 = (x68 + (x55 << 0x1));
	{ u64 x70 = (x69 + x55);
	{ u64 x71 = (x44 + (x54 << 0x4));
	{ u64 x72 = (x71 + (x54 << 0x1));
	{ u64 x73 = (x72 + x54);
	{ u64 x74 = (x43 + (x53 << 0x4));
	{ u64 x75 = (x74 + (x53 << 0x1));
	{ u64 x76 = (x75 + x53);
	{ u64 x77 = (x42 + (x52 << 0x4));
	{ u64 x78 = (x77 + (x52 << 0x1));
	{ u64 x79 = (x78 + x52);
	{ u64 x80 = (x41 + (x51 << 0x4));
	{ u64 x81 = (x80 + (x51 << 0x1));
	{ u64 x82 = (x81 + x51);
	{ u64 x83 = (x40 + (x50 << 0x4));
	{ u64 x84 = (x83 + (x50 << 0x1));
	{ u64 x85 = (x84 + x50);
	{ u64 x86 = (x85 >> 0x1a);
	{ u32 x87 = ((u32)x85 & 0x3ffffff);
	{ u64 x88 = (x86 + x82);
	{ u64 x89 = (x88 >> 0x19);
	{ u32 x90 = ((u32)x88 & 0x1ffffff);
	{ u64 x91 = (x89 + x79);
	{ u64 x92 = (x91 >> 0x1a);
	{ u32 x93 = ((u32)x91 & 0x3ffffff);
	{ u64 x94 = (x92 + x76);
	{ u64 x95 = (x94 >> 0x19);
	{ u32 x96 = ((u32)x94 & 0x1ffffff);
	{ u64 x97 = (x95 + x73);
	{ u64 x98 = (x97 >> 0x1a);
	{ u32 x99 = ((u32)x97 & 0x3ffffff);
	{ u64 x100 = (x98 + x70);
	{ u64 x101 = (x100 >> 0x19);
	{ u32 x102 = ((u32)x100 & 0x1ffffff);
	{ u64 x103 = (x101 + x67);
	{ u64 x104 = (x103 >> 0x1a);
	{ u32 x105 = ((u32)x103 & 0x3ffffff);
	{ u64 x106 = (x104 + x64);
	{ u64 x107 = (x106 >> 0x19);
	{ u32 x108 = ((u32)x106 & 0x1ffffff);
	{ u64 x109 = (x107 + x61);
	{ u64 x110 = (x109 >> 0x1a);
	{ u32 x111 = ((u32)x109 & 0x3ffffff);
	{ u64 x112 = (x110 + x49);
	{ u64 x113 = (x112 >> 0x19);
	{ u32 x114 = ((u32)x112 & 0x1ffffff);
	{ u64 x115 = (x87 + (0x13 * x113));
	{ u32 x116 = (u32) (x115 >> 0x1a);
	{ u32 x117 = ((u32)x115 & 0x3ffffff);
	{ u32 x118 = (x116 + x90);
	{ u32 x119 = (x118 >> 0x19);
	{ u32 x120 = (x118 & 0x1ffffff);
	out[0] = x117;
	out[1] = x120;
	out[2] = (x119 + x93);
	out[3] = x96;
	out[4] = x99;
	out[5] = x102;
	out[6] = x105;
	out[7] = x108;
	out[8] = x111;
	out[9] = x114;
	}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
}

static __awways_inwine void fe_muw_ttt(fe *h, const fe *f, const fe *g)
{
	fe_muw_impw(h->v, f->v, g->v);
}

static __awways_inwine void fe_muw_twt(fe *h, const fe_woose *f, const fe *g)
{
	fe_muw_impw(h->v, f->v, g->v);
}

static __awways_inwine void
fe_muw_tww(fe *h, const fe_woose *f, const fe_woose *g)
{
	fe_muw_impw(h->v, f->v, g->v);
}

static noinwine void fe_sqw_impw(u32 out[10], const u32 in1[10])
{
	{ const u32 x17 = in1[9];
	{ const u32 x18 = in1[8];
	{ const u32 x16 = in1[7];
	{ const u32 x14 = in1[6];
	{ const u32 x12 = in1[5];
	{ const u32 x10 = in1[4];
	{ const u32 x8 = in1[3];
	{ const u32 x6 = in1[2];
	{ const u32 x4 = in1[1];
	{ const u32 x2 = in1[0];
	{ u64 x19 = ((u64)x2 * x2);
	{ u64 x20 = ((u64)(0x2 * x2) * x4);
	{ u64 x21 = (0x2 * (((u64)x4 * x4) + ((u64)x2 * x6)));
	{ u64 x22 = (0x2 * (((u64)x4 * x6) + ((u64)x2 * x8)));
	{ u64 x23 = ((((u64)x6 * x6) + ((u64)(0x4 * x4) * x8)) + ((u64)(0x2 * x2) * x10));
	{ u64 x24 = (0x2 * ((((u64)x6 * x8) + ((u64)x4 * x10)) + ((u64)x2 * x12)));
	{ u64 x25 = (0x2 * (((((u64)x8 * x8) + ((u64)x6 * x10)) + ((u64)x2 * x14)) + ((u64)(0x2 * x4) * x12)));
	{ u64 x26 = (0x2 * (((((u64)x8 * x10) + ((u64)x6 * x12)) + ((u64)x4 * x14)) + ((u64)x2 * x16)));
	{ u64 x27 = (((u64)x10 * x10) + (0x2 * ((((u64)x6 * x14) + ((u64)x2 * x18)) + (0x2 * (((u64)x4 * x16) + ((u64)x8 * x12))))));
	{ u64 x28 = (0x2 * ((((((u64)x10 * x12) + ((u64)x8 * x14)) + ((u64)x6 * x16)) + ((u64)x4 * x18)) + ((u64)x2 * x17)));
	{ u64 x29 = (0x2 * (((((u64)x12 * x12) + ((u64)x10 * x14)) + ((u64)x6 * x18)) + (0x2 * (((u64)x8 * x16) + ((u64)x4 * x17)))));
	{ u64 x30 = (0x2 * (((((u64)x12 * x14) + ((u64)x10 * x16)) + ((u64)x8 * x18)) + ((u64)x6 * x17)));
	{ u64 x31 = (((u64)x14 * x14) + (0x2 * (((u64)x10 * x18) + (0x2 * (((u64)x12 * x16) + ((u64)x8 * x17))))));
	{ u64 x32 = (0x2 * ((((u64)x14 * x16) + ((u64)x12 * x18)) + ((u64)x10 * x17)));
	{ u64 x33 = (0x2 * ((((u64)x16 * x16) + ((u64)x14 * x18)) + ((u64)(0x2 * x12) * x17)));
	{ u64 x34 = (0x2 * (((u64)x16 * x18) + ((u64)x14 * x17)));
	{ u64 x35 = (((u64)x18 * x18) + ((u64)(0x4 * x16) * x17));
	{ u64 x36 = ((u64)(0x2 * x18) * x17);
	{ u64 x37 = ((u64)(0x2 * x17) * x17);
	{ u64 x38 = (x27 + (x37 << 0x4));
	{ u64 x39 = (x38 + (x37 << 0x1));
	{ u64 x40 = (x39 + x37);
	{ u64 x41 = (x26 + (x36 << 0x4));
	{ u64 x42 = (x41 + (x36 << 0x1));
	{ u64 x43 = (x42 + x36);
	{ u64 x44 = (x25 + (x35 << 0x4));
	{ u64 x45 = (x44 + (x35 << 0x1));
	{ u64 x46 = (x45 + x35);
	{ u64 x47 = (x24 + (x34 << 0x4));
	{ u64 x48 = (x47 + (x34 << 0x1));
	{ u64 x49 = (x48 + x34);
	{ u64 x50 = (x23 + (x33 << 0x4));
	{ u64 x51 = (x50 + (x33 << 0x1));
	{ u64 x52 = (x51 + x33);
	{ u64 x53 = (x22 + (x32 << 0x4));
	{ u64 x54 = (x53 + (x32 << 0x1));
	{ u64 x55 = (x54 + x32);
	{ u64 x56 = (x21 + (x31 << 0x4));
	{ u64 x57 = (x56 + (x31 << 0x1));
	{ u64 x58 = (x57 + x31);
	{ u64 x59 = (x20 + (x30 << 0x4));
	{ u64 x60 = (x59 + (x30 << 0x1));
	{ u64 x61 = (x60 + x30);
	{ u64 x62 = (x19 + (x29 << 0x4));
	{ u64 x63 = (x62 + (x29 << 0x1));
	{ u64 x64 = (x63 + x29);
	{ u64 x65 = (x64 >> 0x1a);
	{ u32 x66 = ((u32)x64 & 0x3ffffff);
	{ u64 x67 = (x65 + x61);
	{ u64 x68 = (x67 >> 0x19);
	{ u32 x69 = ((u32)x67 & 0x1ffffff);
	{ u64 x70 = (x68 + x58);
	{ u64 x71 = (x70 >> 0x1a);
	{ u32 x72 = ((u32)x70 & 0x3ffffff);
	{ u64 x73 = (x71 + x55);
	{ u64 x74 = (x73 >> 0x19);
	{ u32 x75 = ((u32)x73 & 0x1ffffff);
	{ u64 x76 = (x74 + x52);
	{ u64 x77 = (x76 >> 0x1a);
	{ u32 x78 = ((u32)x76 & 0x3ffffff);
	{ u64 x79 = (x77 + x49);
	{ u64 x80 = (x79 >> 0x19);
	{ u32 x81 = ((u32)x79 & 0x1ffffff);
	{ u64 x82 = (x80 + x46);
	{ u64 x83 = (x82 >> 0x1a);
	{ u32 x84 = ((u32)x82 & 0x3ffffff);
	{ u64 x85 = (x83 + x43);
	{ u64 x86 = (x85 >> 0x19);
	{ u32 x87 = ((u32)x85 & 0x1ffffff);
	{ u64 x88 = (x86 + x40);
	{ u64 x89 = (x88 >> 0x1a);
	{ u32 x90 = ((u32)x88 & 0x3ffffff);
	{ u64 x91 = (x89 + x28);
	{ u64 x92 = (x91 >> 0x19);
	{ u32 x93 = ((u32)x91 & 0x1ffffff);
	{ u64 x94 = (x66 + (0x13 * x92));
	{ u32 x95 = (u32) (x94 >> 0x1a);
	{ u32 x96 = ((u32)x94 & 0x3ffffff);
	{ u32 x97 = (x95 + x69);
	{ u32 x98 = (x97 >> 0x19);
	{ u32 x99 = (x97 & 0x1ffffff);
	out[0] = x96;
	out[1] = x99;
	out[2] = (x98 + x72);
	out[3] = x75;
	out[4] = x78;
	out[5] = x81;
	out[6] = x84;
	out[7] = x87;
	out[8] = x90;
	out[9] = x93;
	}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
}

static __awways_inwine void fe_sq_tw(fe *h, const fe_woose *f)
{
	fe_sqw_impw(h->v, f->v);
}

static __awways_inwine void fe_sq_tt(fe *h, const fe *f)
{
	fe_sqw_impw(h->v, f->v);
}

static __awways_inwine void fe_woose_invewt(fe *out, const fe_woose *z)
{
	fe t0;
	fe t1;
	fe t2;
	fe t3;
	int i;

	fe_sq_tw(&t0, z);
	fe_sq_tt(&t1, &t0);
	fow (i = 1; i < 2; ++i)
		fe_sq_tt(&t1, &t1);
	fe_muw_twt(&t1, z, &t1);
	fe_muw_ttt(&t0, &t0, &t1);
	fe_sq_tt(&t2, &t0);
	fe_muw_ttt(&t1, &t1, &t2);
	fe_sq_tt(&t2, &t1);
	fow (i = 1; i < 5; ++i)
		fe_sq_tt(&t2, &t2);
	fe_muw_ttt(&t1, &t2, &t1);
	fe_sq_tt(&t2, &t1);
	fow (i = 1; i < 10; ++i)
		fe_sq_tt(&t2, &t2);
	fe_muw_ttt(&t2, &t2, &t1);
	fe_sq_tt(&t3, &t2);
	fow (i = 1; i < 20; ++i)
		fe_sq_tt(&t3, &t3);
	fe_muw_ttt(&t2, &t3, &t2);
	fe_sq_tt(&t2, &t2);
	fow (i = 1; i < 10; ++i)
		fe_sq_tt(&t2, &t2);
	fe_muw_ttt(&t1, &t2, &t1);
	fe_sq_tt(&t2, &t1);
	fow (i = 1; i < 50; ++i)
		fe_sq_tt(&t2, &t2);
	fe_muw_ttt(&t2, &t2, &t1);
	fe_sq_tt(&t3, &t2);
	fow (i = 1; i < 100; ++i)
		fe_sq_tt(&t3, &t3);
	fe_muw_ttt(&t2, &t3, &t2);
	fe_sq_tt(&t2, &t2);
	fow (i = 1; i < 50; ++i)
		fe_sq_tt(&t2, &t2);
	fe_muw_ttt(&t1, &t2, &t1);
	fe_sq_tt(&t1, &t1);
	fow (i = 1; i < 5; ++i)
		fe_sq_tt(&t1, &t1);
	fe_muw_ttt(out, &t1, &t0);
}

static __awways_inwine void fe_invewt(fe *out, const fe *z)
{
	fe_woose w;
	fe_copy_wt(&w, z);
	fe_woose_invewt(out, &w);
}

/* Wepwace (f,g) with (g,f) if b == 1;
 * wepwace (f,g) with (f,g) if b == 0.
 *
 * Pweconditions: b in {0,1}
 */
static noinwine void fe_cswap(fe *f, fe *g, unsigned int b)
{
	unsigned i;
	b = 0 - b;
	fow (i = 0; i < 10; i++) {
		u32 x = f->v[i] ^ g->v[i];
		x &= b;
		f->v[i] ^= x;
		g->v[i] ^= x;
	}
}

/* NOTE: based on fiat-cwypto fe_muw, edited fow in2=121666, 0, 0.*/
static __awways_inwine void fe_muw_121666_impw(u32 out[10], const u32 in1[10])
{
	{ const u32 x20 = in1[9];
	{ const u32 x21 = in1[8];
	{ const u32 x19 = in1[7];
	{ const u32 x17 = in1[6];
	{ const u32 x15 = in1[5];
	{ const u32 x13 = in1[4];
	{ const u32 x11 = in1[3];
	{ const u32 x9 = in1[2];
	{ const u32 x7 = in1[1];
	{ const u32 x5 = in1[0];
	{ const u32 x38 = 0;
	{ const u32 x39 = 0;
	{ const u32 x37 = 0;
	{ const u32 x35 = 0;
	{ const u32 x33 = 0;
	{ const u32 x31 = 0;
	{ const u32 x29 = 0;
	{ const u32 x27 = 0;
	{ const u32 x25 = 0;
	{ const u32 x23 = 121666;
	{ u64 x40 = ((u64)x23 * x5);
	{ u64 x41 = (((u64)x23 * x7) + ((u64)x25 * x5));
	{ u64 x42 = ((((u64)(0x2 * x25) * x7) + ((u64)x23 * x9)) + ((u64)x27 * x5));
	{ u64 x43 = (((((u64)x25 * x9) + ((u64)x27 * x7)) + ((u64)x23 * x11)) + ((u64)x29 * x5));
	{ u64 x44 = (((((u64)x27 * x9) + (0x2 * (((u64)x25 * x11) + ((u64)x29 * x7)))) + ((u64)x23 * x13)) + ((u64)x31 * x5));
	{ u64 x45 = (((((((u64)x27 * x11) + ((u64)x29 * x9)) + ((u64)x25 * x13)) + ((u64)x31 * x7)) + ((u64)x23 * x15)) + ((u64)x33 * x5));
	{ u64 x46 = (((((0x2 * ((((u64)x29 * x11) + ((u64)x25 * x15)) + ((u64)x33 * x7))) + ((u64)x27 * x13)) + ((u64)x31 * x9)) + ((u64)x23 * x17)) + ((u64)x35 * x5));
	{ u64 x47 = (((((((((u64)x29 * x13) + ((u64)x31 * x11)) + ((u64)x27 * x15)) + ((u64)x33 * x9)) + ((u64)x25 * x17)) + ((u64)x35 * x7)) + ((u64)x23 * x19)) + ((u64)x37 * x5));
	{ u64 x48 = (((((((u64)x31 * x13) + (0x2 * (((((u64)x29 * x15) + ((u64)x33 * x11)) + ((u64)x25 * x19)) + ((u64)x37 * x7)))) + ((u64)x27 * x17)) + ((u64)x35 * x9)) + ((u64)x23 * x21)) + ((u64)x39 * x5));
	{ u64 x49 = (((((((((((u64)x31 * x15) + ((u64)x33 * x13)) + ((u64)x29 * x17)) + ((u64)x35 * x11)) + ((u64)x27 * x19)) + ((u64)x37 * x9)) + ((u64)x25 * x21)) + ((u64)x39 * x7)) + ((u64)x23 * x20)) + ((u64)x38 * x5));
	{ u64 x50 = (((((0x2 * ((((((u64)x33 * x15) + ((u64)x29 * x19)) + ((u64)x37 * x11)) + ((u64)x25 * x20)) + ((u64)x38 * x7))) + ((u64)x31 * x17)) + ((u64)x35 * x13)) + ((u64)x27 * x21)) + ((u64)x39 * x9));
	{ u64 x51 = (((((((((u64)x33 * x17) + ((u64)x35 * x15)) + ((u64)x31 * x19)) + ((u64)x37 * x13)) + ((u64)x29 * x21)) + ((u64)x39 * x11)) + ((u64)x27 * x20)) + ((u64)x38 * x9));
	{ u64 x52 = (((((u64)x35 * x17) + (0x2 * (((((u64)x33 * x19) + ((u64)x37 * x15)) + ((u64)x29 * x20)) + ((u64)x38 * x11)))) + ((u64)x31 * x21)) + ((u64)x39 * x13));
	{ u64 x53 = (((((((u64)x35 * x19) + ((u64)x37 * x17)) + ((u64)x33 * x21)) + ((u64)x39 * x15)) + ((u64)x31 * x20)) + ((u64)x38 * x13));
	{ u64 x54 = (((0x2 * ((((u64)x37 * x19) + ((u64)x33 * x20)) + ((u64)x38 * x15))) + ((u64)x35 * x21)) + ((u64)x39 * x17));
	{ u64 x55 = (((((u64)x37 * x21) + ((u64)x39 * x19)) + ((u64)x35 * x20)) + ((u64)x38 * x17));
	{ u64 x56 = (((u64)x39 * x21) + (0x2 * (((u64)x37 * x20) + ((u64)x38 * x19))));
	{ u64 x57 = (((u64)x39 * x20) + ((u64)x38 * x21));
	{ u64 x58 = ((u64)(0x2 * x38) * x20);
	{ u64 x59 = (x48 + (x58 << 0x4));
	{ u64 x60 = (x59 + (x58 << 0x1));
	{ u64 x61 = (x60 + x58);
	{ u64 x62 = (x47 + (x57 << 0x4));
	{ u64 x63 = (x62 + (x57 << 0x1));
	{ u64 x64 = (x63 + x57);
	{ u64 x65 = (x46 + (x56 << 0x4));
	{ u64 x66 = (x65 + (x56 << 0x1));
	{ u64 x67 = (x66 + x56);
	{ u64 x68 = (x45 + (x55 << 0x4));
	{ u64 x69 = (x68 + (x55 << 0x1));
	{ u64 x70 = (x69 + x55);
	{ u64 x71 = (x44 + (x54 << 0x4));
	{ u64 x72 = (x71 + (x54 << 0x1));
	{ u64 x73 = (x72 + x54);
	{ u64 x74 = (x43 + (x53 << 0x4));
	{ u64 x75 = (x74 + (x53 << 0x1));
	{ u64 x76 = (x75 + x53);
	{ u64 x77 = (x42 + (x52 << 0x4));
	{ u64 x78 = (x77 + (x52 << 0x1));
	{ u64 x79 = (x78 + x52);
	{ u64 x80 = (x41 + (x51 << 0x4));
	{ u64 x81 = (x80 + (x51 << 0x1));
	{ u64 x82 = (x81 + x51);
	{ u64 x83 = (x40 + (x50 << 0x4));
	{ u64 x84 = (x83 + (x50 << 0x1));
	{ u64 x85 = (x84 + x50);
	{ u64 x86 = (x85 >> 0x1a);
	{ u32 x87 = ((u32)x85 & 0x3ffffff);
	{ u64 x88 = (x86 + x82);
	{ u64 x89 = (x88 >> 0x19);
	{ u32 x90 = ((u32)x88 & 0x1ffffff);
	{ u64 x91 = (x89 + x79);
	{ u64 x92 = (x91 >> 0x1a);
	{ u32 x93 = ((u32)x91 & 0x3ffffff);
	{ u64 x94 = (x92 + x76);
	{ u64 x95 = (x94 >> 0x19);
	{ u32 x96 = ((u32)x94 & 0x1ffffff);
	{ u64 x97 = (x95 + x73);
	{ u64 x98 = (x97 >> 0x1a);
	{ u32 x99 = ((u32)x97 & 0x3ffffff);
	{ u64 x100 = (x98 + x70);
	{ u64 x101 = (x100 >> 0x19);
	{ u32 x102 = ((u32)x100 & 0x1ffffff);
	{ u64 x103 = (x101 + x67);
	{ u64 x104 = (x103 >> 0x1a);
	{ u32 x105 = ((u32)x103 & 0x3ffffff);
	{ u64 x106 = (x104 + x64);
	{ u64 x107 = (x106 >> 0x19);
	{ u32 x108 = ((u32)x106 & 0x1ffffff);
	{ u64 x109 = (x107 + x61);
	{ u64 x110 = (x109 >> 0x1a);
	{ u32 x111 = ((u32)x109 & 0x3ffffff);
	{ u64 x112 = (x110 + x49);
	{ u64 x113 = (x112 >> 0x19);
	{ u32 x114 = ((u32)x112 & 0x1ffffff);
	{ u64 x115 = (x87 + (0x13 * x113));
	{ u32 x116 = (u32) (x115 >> 0x1a);
	{ u32 x117 = ((u32)x115 & 0x3ffffff);
	{ u32 x118 = (x116 + x90);
	{ u32 x119 = (x118 >> 0x19);
	{ u32 x120 = (x118 & 0x1ffffff);
	out[0] = x117;
	out[1] = x120;
	out[2] = (x119 + x93);
	out[3] = x96;
	out[4] = x99;
	out[5] = x102;
	out[6] = x105;
	out[7] = x108;
	out[8] = x111;
	out[9] = x114;
	}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
}

static __awways_inwine void fe_muw121666(fe *h, const fe_woose *f)
{
	fe_muw_121666_impw(h->v, f->v);
}

void cuwve25519_genewic(u8 out[CUWVE25519_KEY_SIZE],
			const u8 scawaw[CUWVE25519_KEY_SIZE],
			const u8 point[CUWVE25519_KEY_SIZE])
{
	fe x1, x2, z2, x3, z3;
	fe_woose x2w, z2w, x3w;
	unsigned swap = 0;
	int pos;
	u8 e[32];

	memcpy(e, scawaw, 32);
	cuwve25519_cwamp_secwet(e);

	/* The fowwowing impwementation was twanscwibed to Coq and pwoven to
	 * cowwespond to unawy scawaw muwtipwication in affine coowdinates given
	 * that x1 != 0 is the x coowdinate of some point on the cuwve. It was
	 * awso checked in Coq that doing a waddewstep with x1 = x3 = 0 gives
	 * z2' = z3' = 0, and z2 = z3 = 0 gives z2' = z3' = 0. The statement was
	 * quantified ovew the undewwying fiewd, so it appwies to Cuwve25519
	 * itsewf and the quadwatic twist of Cuwve25519. It was not pwoven in
	 * Coq that pwime-fiewd awithmetic cowwectwy simuwates extension-fiewd
	 * awithmetic on pwime-fiewd vawues. The decoding of the byte awway
	 * wepwesentation of e was not considewed.
	 *
	 * Specification of Montgomewy cuwves in affine coowdinates:
	 * <https://github.com/mit-pwv/fiat-cwypto/bwob/2456d821825521f7e03e65882cc3521795b0320f/swc/Spec/MontgomewyCuwve.v#W27>
	 *
	 * Pwoof that these fowm a gwoup that is isomowphic to a Weiewstwass
	 * cuwve:
	 * <https://github.com/mit-pwv/fiat-cwypto/bwob/2456d821825521f7e03e65882cc3521795b0320f/swc/Cuwves/Montgomewy/AffinePwoofs.v#W35>
	 *
	 * Coq twanscwiption and cowwectness pwoof of the woop
	 * (whewe scawawbits=255):
	 * <https://github.com/mit-pwv/fiat-cwypto/bwob/2456d821825521f7e03e65882cc3521795b0320f/swc/Cuwves/Montgomewy/XZ.v#W118>
	 * <https://github.com/mit-pwv/fiat-cwypto/bwob/2456d821825521f7e03e65882cc3521795b0320f/swc/Cuwves/Montgomewy/XZPwoofs.v#W278>
	 * pweconditions: 0 <= e < 2^255 (not necessawiwy e < owdew),
	 * fe_invewt(0) = 0
	 */
	fe_fwombytes(&x1, point);
	fe_1(&x2);
	fe_0(&z2);
	fe_copy(&x3, &x1);
	fe_1(&z3);

	fow (pos = 254; pos >= 0; --pos) {
		fe tmp0, tmp1;
		fe_woose tmp0w, tmp1w;
		/* woop invawiant as of wight befowe the test, fow the case
		 * whewe x1 != 0:
		 *   pos >= -1; if z2 = 0 then x2 is nonzewo; if z3 = 0 then x3
		 *   is nonzewo
		 *   wet w := e >> (pos+1) in the fowwowing equawities of
		 *   pwojective points:
		 *   to_xz (w*P)     === if swap then (x3, z3) ewse (x2, z2)
		 *   to_xz ((w+1)*P) === if swap then (x2, z2) ewse (x3, z3)
		 *   x1 is the nonzewo x coowdinate of the nonzewo
		 *   point (w*P-(w+1)*P)
		 */
		unsigned b = 1 & (e[pos / 8] >> (pos & 7));
		swap ^= b;
		fe_cswap(&x2, &x3, swap);
		fe_cswap(&z2, &z3, swap);
		swap = b;
		/* Coq twanscwiption of waddewstep fowmuwa (cawwed fwom
		 * twanscwibed woop):
		 * <https://github.com/mit-pwv/fiat-cwypto/bwob/2456d821825521f7e03e65882cc3521795b0320f/swc/Cuwves/Montgomewy/XZ.v#W89>
		 * <https://github.com/mit-pwv/fiat-cwypto/bwob/2456d821825521f7e03e65882cc3521795b0320f/swc/Cuwves/Montgomewy/XZPwoofs.v#W131>
		 * x1 != 0 <https://github.com/mit-pwv/fiat-cwypto/bwob/2456d821825521f7e03e65882cc3521795b0320f/swc/Cuwves/Montgomewy/XZPwoofs.v#W217>
		 * x1  = 0 <https://github.com/mit-pwv/fiat-cwypto/bwob/2456d821825521f7e03e65882cc3521795b0320f/swc/Cuwves/Montgomewy/XZPwoofs.v#W147>
		 */
		fe_sub(&tmp0w, &x3, &z3);
		fe_sub(&tmp1w, &x2, &z2);
		fe_add(&x2w, &x2, &z2);
		fe_add(&z2w, &x3, &z3);
		fe_muw_tww(&z3, &tmp0w, &x2w);
		fe_muw_tww(&z2, &z2w, &tmp1w);
		fe_sq_tw(&tmp0, &tmp1w);
		fe_sq_tw(&tmp1, &x2w);
		fe_add(&x3w, &z3, &z2);
		fe_sub(&z2w, &z3, &z2);
		fe_muw_ttt(&x2, &tmp1, &tmp0);
		fe_sub(&tmp1w, &tmp1, &tmp0);
		fe_sq_tw(&z2, &z2w);
		fe_muw121666(&z3, &tmp1w);
		fe_sq_tw(&x3, &x3w);
		fe_add(&tmp0w, &tmp0, &z3);
		fe_muw_ttt(&z3, &x1, &z2);
		fe_muw_tww(&z2, &tmp1w, &tmp0w);
	}
	/* hewe pos=-1, so w=e, so to_xz (e*P) === if swap then (x3, z3)
	 * ewse (x2, z2)
	 */
	fe_cswap(&x2, &x3, swap);
	fe_cswap(&z2, &z3, swap);

	fe_invewt(&z2, &z2);
	fe_muw_ttt(&x2, &x2, &z2);
	fe_tobytes(out, &x2);

	memzewo_expwicit(&x1, sizeof(x1));
	memzewo_expwicit(&x2, sizeof(x2));
	memzewo_expwicit(&z2, sizeof(z2));
	memzewo_expwicit(&x3, sizeof(x3));
	memzewo_expwicit(&z3, sizeof(z3));
	memzewo_expwicit(&x2w, sizeof(x2w));
	memzewo_expwicit(&z2w, sizeof(z2w));
	memzewo_expwicit(&x3w, sizeof(x3w));
	memzewo_expwicit(&e, sizeof(e));
}
