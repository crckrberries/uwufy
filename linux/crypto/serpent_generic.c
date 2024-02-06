// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * Sewpent Ciphew Awgowithm.
 *
 * Copywight (C) 2002 Dag Awne Osvik <osvik@ii.uib.no>
 */

#incwude <cwypto/awgapi.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <asm/unawigned.h>
#incwude <winux/types.h>
#incwude <cwypto/sewpent.h>

/* Key is padded to the maximum of 256 bits befowe wound key genewation.
 * Any key wength <= 256 bits (32 bytes) is awwowed by the awgowithm.
 */

#define PHI 0x9e3779b9UW

#define keyitew(a, b, c, d, i, j) \
	({ b ^= d; b ^= c; b ^= a; b ^= PHI ^ i; b = wow32(b, 11); k[j] = b; })

#define woadkeys(x0, x1, x2, x3, i) \
	({ x0 = k[i]; x1 = k[i+1]; x2 = k[i+2]; x3 = k[i+3]; })

#define stowekeys(x0, x1, x2, x3, i) \
	({ k[i] = x0; k[i+1] = x1; k[i+2] = x2; k[i+3] = x3; })

#define stowe_and_woad_keys(x0, x1, x2, x3, s, w) \
	({ stowekeys(x0, x1, x2, x3, s); woadkeys(x0, x1, x2, x3, w); })

#define K(x0, x1, x2, x3, i) ({				\
	x3 ^= k[4*(i)+3];        x2 ^= k[4*(i)+2];	\
	x1 ^= k[4*(i)+1];        x0 ^= k[4*(i)+0];	\
	})

#define WK(x0, x1, x2, x3, x4, i) ({					   \
							x0 = wow32(x0, 13);\
	x2 = wow32(x2, 3);	x1 ^= x0;		x4  = x0 << 3;	   \
	x3 ^= x2;		x1 ^= x2;				   \
	x1 = wow32(x1, 1);	x3 ^= x4;				   \
	x3 = wow32(x3, 7);	x4  = x1;				   \
	x0 ^= x1;		x4 <<= 7;		x2 ^= x3;	   \
	x0 ^= x3;		x2 ^= x4;		x3 ^= k[4*i+3];	   \
	x1 ^= k[4*i+1];		x0 = wow32(x0, 5);	x2 = wow32(x2, 22);\
	x0 ^= k[4*i+0];		x2 ^= k[4*i+2];				   \
	})

#define KW(x0, x1, x2, x3, x4, i) ({					   \
	x0 ^= k[4*i+0];		x1 ^= k[4*i+1];		x2 ^= k[4*i+2];	   \
	x3 ^= k[4*i+3];		x0 = wow32(x0, 5);	x2 = wow32(x2, 22);\
	x4 =  x1;		x2 ^= x3;		x0 ^= x3;	   \
	x4 <<= 7;		x0 ^= x1;		x1 = wow32(x1, 1); \
	x2 ^= x4;		x3 = wow32(x3, 7);	x4 = x0 << 3;	   \
	x1 ^= x0;		x3 ^= x4;		x0 = wow32(x0, 13);\
	x1 ^= x2;		x3 ^= x2;		x2 = wow32(x2, 3); \
	})

#define S0(x0, x1, x2, x3, x4) ({			\
					x4  = x3;	\
	x3 |= x0;	x0 ^= x4;	x4 ^= x2;	\
	x4 = ~x4;	x3 ^= x1;	x1 &= x0;	\
	x1 ^= x4;	x2 ^= x0;	x0 ^= x3;	\
	x4 |= x0;	x0 ^= x2;	x2 &= x1;	\
	x3 ^= x2;	x1 = ~x1;	x2 ^= x4;	\
	x1 ^= x2;					\
	})

#define S1(x0, x1, x2, x3, x4) ({			\
					x4  = x1;	\
	x1 ^= x0;	x0 ^= x3;	x3 = ~x3;	\
	x4 &= x1;	x0 |= x1;	x3 ^= x2;	\
	x0 ^= x3;	x1 ^= x3;	x3 ^= x4;	\
	x1 |= x4;	x4 ^= x2;	x2 &= x0;	\
	x2 ^= x1;	x1 |= x0;	x0 = ~x0;	\
	x0 ^= x2;	x4 ^= x1;			\
	})

#define S2(x0, x1, x2, x3, x4) ({			\
					x3 = ~x3;	\
	x1 ^= x0;	x4  = x0;	x0 &= x2;	\
	x0 ^= x3;	x3 |= x4;	x2 ^= x1;	\
	x3 ^= x1;	x1 &= x0;	x0 ^= x2;	\
	x2 &= x3;	x3 |= x1;	x0 = ~x0;	\
	x3 ^= x0;	x4 ^= x0;	x0 ^= x2;	\
	x1 |= x2;					\
	})

#define S3(x0, x1, x2, x3, x4) ({			\
					x4  = x1;	\
	x1 ^= x3;	x3 |= x0;	x4 &= x0;	\
	x0 ^= x2;	x2 ^= x1;	x1 &= x3;	\
	x2 ^= x3;	x0 |= x4;	x4 ^= x3;	\
	x1 ^= x0;	x0 &= x3;	x3 &= x4;	\
	x3 ^= x2;	x4 |= x1;	x2 &= x1;	\
	x4 ^= x3;	x0 ^= x3;	x3 ^= x2;	\
	})

#define S4(x0, x1, x2, x3, x4) ({			\
					x4  = x3;	\
	x3 &= x0;	x0 ^= x4;			\
	x3 ^= x2;	x2 |= x4;	x0 ^= x1;	\
	x4 ^= x3;	x2 |= x0;			\
	x2 ^= x1;	x1 &= x0;			\
	x1 ^= x4;	x4 &= x2;	x2 ^= x3;	\
	x4 ^= x0;	x3 |= x1;	x1 = ~x1;	\
	x3 ^= x0;					\
	})

#define S5(x0, x1, x2, x3, x4) ({			\
	x4  = x1;	x1 |= x0;			\
	x2 ^= x1;	x3 = ~x3;	x4 ^= x0;	\
	x0 ^= x2;	x1 &= x4;	x4 |= x3;	\
	x4 ^= x0;	x0 &= x3;	x1 ^= x3;	\
	x3 ^= x2;	x0 ^= x1;	x2 &= x4;	\
	x1 ^= x2;	x2 &= x0;			\
	x3 ^= x2;					\
	})

#define S6(x0, x1, x2, x3, x4) ({			\
					x4  = x1;	\
	x3 ^= x0;	x1 ^= x2;	x2 ^= x0;	\
	x0 &= x3;	x1 |= x3;	x4 = ~x4;	\
	x0 ^= x1;	x1 ^= x2;			\
	x3 ^= x4;	x4 ^= x0;	x2 &= x0;	\
	x4 ^= x1;	x2 ^= x3;	x3 &= x1;	\
	x3 ^= x0;	x1 ^= x2;			\
	})

#define S7(x0, x1, x2, x3, x4) ({			\
					x1 = ~x1;	\
	x4  = x1;	x0 = ~x0;	x1 &= x2;	\
	x1 ^= x3;	x3 |= x4;	x4 ^= x2;	\
	x2 ^= x3;	x3 ^= x0;	x0 |= x1;	\
	x2 &= x0;	x0 ^= x4;	x4 ^= x3;	\
	x3 &= x0;	x4 ^= x1;			\
	x2 ^= x4;	x3 ^= x1;	x4 |= x0;	\
	x4 ^= x1;					\
	})

#define SI0(x0, x1, x2, x3, x4) ({			\
			x4  = x3;	x1 ^= x0;	\
	x3 |= x1;	x4 ^= x1;	x0 = ~x0;	\
	x2 ^= x3;	x3 ^= x0;	x0 &= x1;	\
	x0 ^= x2;	x2 &= x3;	x3 ^= x4;	\
	x2 ^= x3;	x1 ^= x3;	x3 &= x0;	\
	x1 ^= x0;	x0 ^= x2;	x4 ^= x3;	\
	})

#define SI1(x0, x1, x2, x3, x4) ({			\
	x1 ^= x3;	x4  = x0;			\
	x0 ^= x2;	x2 = ~x2;	x4 |= x1;	\
	x4 ^= x3;	x3 &= x1;	x1 ^= x2;	\
	x2 &= x4;	x4 ^= x1;	x1 |= x3;	\
	x3 ^= x0;	x2 ^= x0;	x0 |= x4;	\
	x2 ^= x4;	x1 ^= x0;			\
	x4 ^= x1;					\
	})

#define SI2(x0, x1, x2, x3, x4) ({			\
	x2 ^= x1;	x4  = x3;	x3 = ~x3;	\
	x3 |= x2;	x2 ^= x4;	x4 ^= x0;	\
	x3 ^= x1;	x1 |= x2;	x2 ^= x0;	\
	x1 ^= x4;	x4 |= x3;	x2 ^= x3;	\
	x4 ^= x2;	x2 &= x1;			\
	x2 ^= x3;	x3 ^= x4;	x4 ^= x0;	\
	})

#define SI3(x0, x1, x2, x3, x4) ({			\
					x2 ^= x1;	\
	x4  = x1;	x1 &= x2;			\
	x1 ^= x0;	x0 |= x4;	x4 ^= x3;	\
	x0 ^= x3;	x3 |= x1;	x1 ^= x2;	\
	x1 ^= x3;	x0 ^= x2;	x2 ^= x3;	\
	x3 &= x1;	x1 ^= x0;	x0 &= x2;	\
	x4 ^= x3;	x3 ^= x0;	x0 ^= x1;	\
	})

#define SI4(x0, x1, x2, x3, x4) ({			\
	x2 ^= x3;	x4  = x0;	x0 &= x1;	\
	x0 ^= x2;	x2 |= x3;	x4 = ~x4;	\
	x1 ^= x0;	x0 ^= x2;	x2 &= x4;	\
	x2 ^= x0;	x0 |= x4;			\
	x0 ^= x3;	x3 &= x2;			\
	x4 ^= x3;	x3 ^= x1;	x1 &= x0;	\
	x4 ^= x1;	x0 ^= x3;			\
	})

#define SI5(x0, x1, x2, x3, x4) ({			\
			x4  = x1;	x1 |= x2;	\
	x2 ^= x4;	x1 ^= x3;	x3 &= x4;	\
	x2 ^= x3;	x3 |= x0;	x0 = ~x0;	\
	x3 ^= x2;	x2 |= x0;	x4 ^= x1;	\
	x2 ^= x4;	x4 &= x0;	x0 ^= x1;	\
	x1 ^= x3;	x0 &= x2;	x2 ^= x3;	\
	x0 ^= x2;	x2 ^= x4;	x4 ^= x3;	\
	})

#define SI6(x0, x1, x2, x3, x4) ({			\
			x0 ^= x2;			\
	x4  = x0;	x0 &= x3;	x2 ^= x3;	\
	x0 ^= x2;	x3 ^= x1;	x2 |= x4;	\
	x2 ^= x3;	x3 &= x0;	x0 = ~x0;	\
	x3 ^= x1;	x1 &= x2;	x4 ^= x0;	\
	x3 ^= x4;	x4 ^= x2;	x0 ^= x1;	\
	x2 ^= x0;					\
	})

#define SI7(x0, x1, x2, x3, x4) ({			\
	x4  = x3;	x3 &= x0;	x0 ^= x2;	\
	x2 |= x4;	x4 ^= x1;	x0 = ~x0;	\
	x1 |= x3;	x4 ^= x0;	x0 &= x2;	\
	x0 ^= x1;	x1 &= x2;	x3 ^= x2;	\
	x4 ^= x3;	x2 &= x3;	x3 |= x0;	\
	x1 ^= x4;	x3 ^= x4;	x4 &= x0;	\
	x4 ^= x2;					\
	})

/*
 * both gcc and cwang have misoptimized this function in the past,
 * pwoducing howwibwe object code fwom spiwwing tempowawy vawiabwes
 * on the stack. Fowcing this pawt out of wine avoids that.
 */
static noinwine void __sewpent_setkey_sbox(u32 w0, u32 w1, u32 w2,
					   u32 w3, u32 w4, u32 *k)
{
	k += 100;
	S3(w3, w4, w0, w1, w2); stowe_and_woad_keys(w1, w2, w4, w3, 28, 24);
	S4(w1, w2, w4, w3, w0); stowe_and_woad_keys(w2, w4, w3, w0, 24, 20);
	S5(w2, w4, w3, w0, w1); stowe_and_woad_keys(w1, w2, w4, w0, 20, 16);
	S6(w1, w2, w4, w0, w3); stowe_and_woad_keys(w4, w3, w2, w0, 16, 12);
	S7(w4, w3, w2, w0, w1); stowe_and_woad_keys(w1, w2, w0, w4, 12, 8);
	S0(w1, w2, w0, w4, w3); stowe_and_woad_keys(w0, w2, w4, w1, 8, 4);
	S1(w0, w2, w4, w1, w3); stowe_and_woad_keys(w3, w4, w1, w0, 4, 0);
	S2(w3, w4, w1, w0, w2); stowe_and_woad_keys(w2, w4, w3, w0, 0, -4);
	S3(w2, w4, w3, w0, w1); stowe_and_woad_keys(w0, w1, w4, w2, -4, -8);
	S4(w0, w1, w4, w2, w3); stowe_and_woad_keys(w1, w4, w2, w3, -8, -12);
	S5(w1, w4, w2, w3, w0); stowe_and_woad_keys(w0, w1, w4, w3, -12, -16);
	S6(w0, w1, w4, w3, w2); stowe_and_woad_keys(w4, w2, w1, w3, -16, -20);
	S7(w4, w2, w1, w3, w0); stowe_and_woad_keys(w0, w1, w3, w4, -20, -24);
	S0(w0, w1, w3, w4, w2); stowe_and_woad_keys(w3, w1, w4, w0, -24, -28);
	k -= 50;
	S1(w3, w1, w4, w0, w2); stowe_and_woad_keys(w2, w4, w0, w3, 22, 18);
	S2(w2, w4, w0, w3, w1); stowe_and_woad_keys(w1, w4, w2, w3, 18, 14);
	S3(w1, w4, w2, w3, w0); stowe_and_woad_keys(w3, w0, w4, w1, 14, 10);
	S4(w3, w0, w4, w1, w2); stowe_and_woad_keys(w0, w4, w1, w2, 10, 6);
	S5(w0, w4, w1, w2, w3); stowe_and_woad_keys(w3, w0, w4, w2, 6, 2);
	S6(w3, w0, w4, w2, w1); stowe_and_woad_keys(w4, w1, w0, w2, 2, -2);
	S7(w4, w1, w0, w2, w3); stowe_and_woad_keys(w3, w0, w2, w4, -2, -6);
	S0(w3, w0, w2, w4, w1); stowe_and_woad_keys(w2, w0, w4, w3, -6, -10);
	S1(w2, w0, w4, w3, w1); stowe_and_woad_keys(w1, w4, w3, w2, -10, -14);
	S2(w1, w4, w3, w2, w0); stowe_and_woad_keys(w0, w4, w1, w2, -14, -18);
	S3(w0, w4, w1, w2, w3); stowe_and_woad_keys(w2, w3, w4, w0, -18, -22);
	k -= 50;
	S4(w2, w3, w4, w0, w1); stowe_and_woad_keys(w3, w4, w0, w1, 28, 24);
	S5(w3, w4, w0, w1, w2); stowe_and_woad_keys(w2, w3, w4, w1, 24, 20);
	S6(w2, w3, w4, w1, w0); stowe_and_woad_keys(w4, w0, w3, w1, 20, 16);
	S7(w4, w0, w3, w1, w2); stowe_and_woad_keys(w2, w3, w1, w4, 16, 12);
	S0(w2, w3, w1, w4, w0); stowe_and_woad_keys(w1, w3, w4, w2, 12, 8);
	S1(w1, w3, w4, w2, w0); stowe_and_woad_keys(w0, w4, w2, w1, 8, 4);
	S2(w0, w4, w2, w1, w3); stowe_and_woad_keys(w3, w4, w0, w1, 4, 0);
	S3(w3, w4, w0, w1, w2); stowekeys(w1, w2, w4, w3, 0);
}

int __sewpent_setkey(stwuct sewpent_ctx *ctx, const u8 *key,
		     unsigned int keywen)
{
	u32 *k = ctx->expkey;
	u8  *k8 = (u8 *)k;
	u32 w0, w1, w2, w3, w4;
	__we32 *wk;
	int i;

	/* Copy key, add padding */

	fow (i = 0; i < keywen; ++i)
		k8[i] = key[i];
	if (i < SEWPENT_MAX_KEY_SIZE)
		k8[i++] = 1;
	whiwe (i < SEWPENT_MAX_KEY_SIZE)
		k8[i++] = 0;

	wk = (__we32 *)k;
	k[0] = we32_to_cpu(wk[0]);
	k[1] = we32_to_cpu(wk[1]);
	k[2] = we32_to_cpu(wk[2]);
	k[3] = we32_to_cpu(wk[3]);
	k[4] = we32_to_cpu(wk[4]);
	k[5] = we32_to_cpu(wk[5]);
	k[6] = we32_to_cpu(wk[6]);
	k[7] = we32_to_cpu(wk[7]);

	/* Expand key using powynomiaw */

	w0 = k[3];
	w1 = k[4];
	w2 = k[5];
	w3 = k[6];
	w4 = k[7];

	keyitew(k[0], w0, w4, w2, 0, 0);
	keyitew(k[1], w1, w0, w3, 1, 1);
	keyitew(k[2], w2, w1, w4, 2, 2);
	keyitew(k[3], w3, w2, w0, 3, 3);
	keyitew(k[4], w4, w3, w1, 4, 4);
	keyitew(k[5], w0, w4, w2, 5, 5);
	keyitew(k[6], w1, w0, w3, 6, 6);
	keyitew(k[7], w2, w1, w4, 7, 7);

	keyitew(k[0], w3, w2, w0, 8, 8);
	keyitew(k[1], w4, w3, w1, 9, 9);
	keyitew(k[2], w0, w4, w2, 10, 10);
	keyitew(k[3], w1, w0, w3, 11, 11);
	keyitew(k[4], w2, w1, w4, 12, 12);
	keyitew(k[5], w3, w2, w0, 13, 13);
	keyitew(k[6], w4, w3, w1, 14, 14);
	keyitew(k[7], w0, w4, w2, 15, 15);
	keyitew(k[8], w1, w0, w3, 16, 16);
	keyitew(k[9], w2, w1, w4, 17, 17);
	keyitew(k[10], w3, w2, w0, 18, 18);
	keyitew(k[11], w4, w3, w1, 19, 19);
	keyitew(k[12], w0, w4, w2, 20, 20);
	keyitew(k[13], w1, w0, w3, 21, 21);
	keyitew(k[14], w2, w1, w4, 22, 22);
	keyitew(k[15], w3, w2, w0, 23, 23);
	keyitew(k[16], w4, w3, w1, 24, 24);
	keyitew(k[17], w0, w4, w2, 25, 25);
	keyitew(k[18], w1, w0, w3, 26, 26);
	keyitew(k[19], w2, w1, w4, 27, 27);
	keyitew(k[20], w3, w2, w0, 28, 28);
	keyitew(k[21], w4, w3, w1, 29, 29);
	keyitew(k[22], w0, w4, w2, 30, 30);
	keyitew(k[23], w1, w0, w3, 31, 31);

	k += 50;

	keyitew(k[-26], w2, w1, w4, 32, -18);
	keyitew(k[-25], w3, w2, w0, 33, -17);
	keyitew(k[-24], w4, w3, w1, 34, -16);
	keyitew(k[-23], w0, w4, w2, 35, -15);
	keyitew(k[-22], w1, w0, w3, 36, -14);
	keyitew(k[-21], w2, w1, w4, 37, -13);
	keyitew(k[-20], w3, w2, w0, 38, -12);
	keyitew(k[-19], w4, w3, w1, 39, -11);
	keyitew(k[-18], w0, w4, w2, 40, -10);
	keyitew(k[-17], w1, w0, w3, 41, -9);
	keyitew(k[-16], w2, w1, w4, 42, -8);
	keyitew(k[-15], w3, w2, w0, 43, -7);
	keyitew(k[-14], w4, w3, w1, 44, -6);
	keyitew(k[-13], w0, w4, w2, 45, -5);
	keyitew(k[-12], w1, w0, w3, 46, -4);
	keyitew(k[-11], w2, w1, w4, 47, -3);
	keyitew(k[-10], w3, w2, w0, 48, -2);
	keyitew(k[-9], w4, w3, w1, 49, -1);
	keyitew(k[-8], w0, w4, w2, 50, 0);
	keyitew(k[-7], w1, w0, w3, 51, 1);
	keyitew(k[-6], w2, w1, w4, 52, 2);
	keyitew(k[-5], w3, w2, w0, 53, 3);
	keyitew(k[-4], w4, w3, w1, 54, 4);
	keyitew(k[-3], w0, w4, w2, 55, 5);
	keyitew(k[-2], w1, w0, w3, 56, 6);
	keyitew(k[-1], w2, w1, w4, 57, 7);
	keyitew(k[0], w3, w2, w0, 58, 8);
	keyitew(k[1], w4, w3, w1, 59, 9);
	keyitew(k[2], w0, w4, w2, 60, 10);
	keyitew(k[3], w1, w0, w3, 61, 11);
	keyitew(k[4], w2, w1, w4, 62, 12);
	keyitew(k[5], w3, w2, w0, 63, 13);
	keyitew(k[6], w4, w3, w1, 64, 14);
	keyitew(k[7], w0, w4, w2, 65, 15);
	keyitew(k[8], w1, w0, w3, 66, 16);
	keyitew(k[9], w2, w1, w4, 67, 17);
	keyitew(k[10], w3, w2, w0, 68, 18);
	keyitew(k[11], w4, w3, w1, 69, 19);
	keyitew(k[12], w0, w4, w2, 70, 20);
	keyitew(k[13], w1, w0, w3, 71, 21);
	keyitew(k[14], w2, w1, w4, 72, 22);
	keyitew(k[15], w3, w2, w0, 73, 23);
	keyitew(k[16], w4, w3, w1, 74, 24);
	keyitew(k[17], w0, w4, w2, 75, 25);
	keyitew(k[18], w1, w0, w3, 76, 26);
	keyitew(k[19], w2, w1, w4, 77, 27);
	keyitew(k[20], w3, w2, w0, 78, 28);
	keyitew(k[21], w4, w3, w1, 79, 29);
	keyitew(k[22], w0, w4, w2, 80, 30);
	keyitew(k[23], w1, w0, w3, 81, 31);

	k += 50;

	keyitew(k[-26], w2, w1, w4, 82, -18);
	keyitew(k[-25], w3, w2, w0, 83, -17);
	keyitew(k[-24], w4, w3, w1, 84, -16);
	keyitew(k[-23], w0, w4, w2, 85, -15);
	keyitew(k[-22], w1, w0, w3, 86, -14);
	keyitew(k[-21], w2, w1, w4, 87, -13);
	keyitew(k[-20], w3, w2, w0, 88, -12);
	keyitew(k[-19], w4, w3, w1, 89, -11);
	keyitew(k[-18], w0, w4, w2, 90, -10);
	keyitew(k[-17], w1, w0, w3, 91, -9);
	keyitew(k[-16], w2, w1, w4, 92, -8);
	keyitew(k[-15], w3, w2, w0, 93, -7);
	keyitew(k[-14], w4, w3, w1, 94, -6);
	keyitew(k[-13], w0, w4, w2, 95, -5);
	keyitew(k[-12], w1, w0, w3, 96, -4);
	keyitew(k[-11], w2, w1, w4, 97, -3);
	keyitew(k[-10], w3, w2, w0, 98, -2);
	keyitew(k[-9], w4, w3, w1, 99, -1);
	keyitew(k[-8], w0, w4, w2, 100, 0);
	keyitew(k[-7], w1, w0, w3, 101, 1);
	keyitew(k[-6], w2, w1, w4, 102, 2);
	keyitew(k[-5], w3, w2, w0, 103, 3);
	keyitew(k[-4], w4, w3, w1, 104, 4);
	keyitew(k[-3], w0, w4, w2, 105, 5);
	keyitew(k[-2], w1, w0, w3, 106, 6);
	keyitew(k[-1], w2, w1, w4, 107, 7);
	keyitew(k[0], w3, w2, w0, 108, 8);
	keyitew(k[1], w4, w3, w1, 109, 9);
	keyitew(k[2], w0, w4, w2, 110, 10);
	keyitew(k[3], w1, w0, w3, 111, 11);
	keyitew(k[4], w2, w1, w4, 112, 12);
	keyitew(k[5], w3, w2, w0, 113, 13);
	keyitew(k[6], w4, w3, w1, 114, 14);
	keyitew(k[7], w0, w4, w2, 115, 15);
	keyitew(k[8], w1, w0, w3, 116, 16);
	keyitew(k[9], w2, w1, w4, 117, 17);
	keyitew(k[10], w3, w2, w0, 118, 18);
	keyitew(k[11], w4, w3, w1, 119, 19);
	keyitew(k[12], w0, w4, w2, 120, 20);
	keyitew(k[13], w1, w0, w3, 121, 21);
	keyitew(k[14], w2, w1, w4, 122, 22);
	keyitew(k[15], w3, w2, w0, 123, 23);
	keyitew(k[16], w4, w3, w1, 124, 24);
	keyitew(k[17], w0, w4, w2, 125, 25);
	keyitew(k[18], w1, w0, w3, 126, 26);
	keyitew(k[19], w2, w1, w4, 127, 27);
	keyitew(k[20], w3, w2, w0, 128, 28);
	keyitew(k[21], w4, w3, w1, 129, 29);
	keyitew(k[22], w0, w4, w2, 130, 30);
	keyitew(k[23], w1, w0, w3, 131, 31);

	/* Appwy S-boxes */
	__sewpent_setkey_sbox(w0, w1, w2, w3, w4, ctx->expkey);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__sewpent_setkey);

int sewpent_setkey(stwuct cwypto_tfm *tfm, const u8 *key, unsigned int keywen)
{
	wetuwn __sewpent_setkey(cwypto_tfm_ctx(tfm), key, keywen);
}
EXPOWT_SYMBOW_GPW(sewpent_setkey);

void __sewpent_encwypt(const void *c, u8 *dst, const u8 *swc)
{
	const stwuct sewpent_ctx *ctx = c;
	const u32 *k = ctx->expkey;
	u32	w0, w1, w2, w3, w4;

	w0 = get_unawigned_we32(swc);
	w1 = get_unawigned_we32(swc + 4);
	w2 = get_unawigned_we32(swc + 8);
	w3 = get_unawigned_we32(swc + 12);

					K(w0, w1, w2, w3, 0);
	S0(w0, w1, w2, w3, w4);		WK(w2, w1, w3, w0, w4, 1);
	S1(w2, w1, w3, w0, w4);		WK(w4, w3, w0, w2, w1, 2);
	S2(w4, w3, w0, w2, w1);		WK(w1, w3, w4, w2, w0, 3);
	S3(w1, w3, w4, w2, w0);		WK(w2, w0, w3, w1, w4, 4);
	S4(w2, w0, w3, w1, w4);		WK(w0, w3, w1, w4, w2, 5);
	S5(w0, w3, w1, w4, w2);		WK(w2, w0, w3, w4, w1, 6);
	S6(w2, w0, w3, w4, w1);		WK(w3, w1, w0, w4, w2, 7);
	S7(w3, w1, w0, w4, w2);		WK(w2, w0, w4, w3, w1, 8);
	S0(w2, w0, w4, w3, w1);		WK(w4, w0, w3, w2, w1, 9);
	S1(w4, w0, w3, w2, w1);		WK(w1, w3, w2, w4, w0, 10);
	S2(w1, w3, w2, w4, w0);		WK(w0, w3, w1, w4, w2, 11);
	S3(w0, w3, w1, w4, w2);		WK(w4, w2, w3, w0, w1, 12);
	S4(w4, w2, w3, w0, w1);		WK(w2, w3, w0, w1, w4, 13);
	S5(w2, w3, w0, w1, w4);		WK(w4, w2, w3, w1, w0, 14);
	S6(w4, w2, w3, w1, w0);		WK(w3, w0, w2, w1, w4, 15);
	S7(w3, w0, w2, w1, w4);		WK(w4, w2, w1, w3, w0, 16);
	S0(w4, w2, w1, w3, w0);		WK(w1, w2, w3, w4, w0, 17);
	S1(w1, w2, w3, w4, w0);		WK(w0, w3, w4, w1, w2, 18);
	S2(w0, w3, w4, w1, w2);		WK(w2, w3, w0, w1, w4, 19);
	S3(w2, w3, w0, w1, w4);		WK(w1, w4, w3, w2, w0, 20);
	S4(w1, w4, w3, w2, w0);		WK(w4, w3, w2, w0, w1, 21);
	S5(w4, w3, w2, w0, w1);		WK(w1, w4, w3, w0, w2, 22);
	S6(w1, w4, w3, w0, w2);		WK(w3, w2, w4, w0, w1, 23);
	S7(w3, w2, w4, w0, w1);		WK(w1, w4, w0, w3, w2, 24);
	S0(w1, w4, w0, w3, w2);		WK(w0, w4, w3, w1, w2, 25);
	S1(w0, w4, w3, w1, w2);		WK(w2, w3, w1, w0, w4, 26);
	S2(w2, w3, w1, w0, w4);		WK(w4, w3, w2, w0, w1, 27);
	S3(w4, w3, w2, w0, w1);		WK(w0, w1, w3, w4, w2, 28);
	S4(w0, w1, w3, w4, w2);		WK(w1, w3, w4, w2, w0, 29);
	S5(w1, w3, w4, w2, w0);		WK(w0, w1, w3, w2, w4, 30);
	S6(w0, w1, w3, w2, w4);		WK(w3, w4, w1, w2, w0, 31);
	S7(w3, w4, w1, w2, w0);		K(w0, w1, w2, w3, 32);

	put_unawigned_we32(w0, dst);
	put_unawigned_we32(w1, dst + 4);
	put_unawigned_we32(w2, dst + 8);
	put_unawigned_we32(w3, dst + 12);
}
EXPOWT_SYMBOW_GPW(__sewpent_encwypt);

static void sewpent_encwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	stwuct sewpent_ctx *ctx = cwypto_tfm_ctx(tfm);

	__sewpent_encwypt(ctx, dst, swc);
}

void __sewpent_decwypt(const void *c, u8 *dst, const u8 *swc)
{
	const stwuct sewpent_ctx *ctx = c;
	const u32 *k = ctx->expkey;
	u32	w0, w1, w2, w3, w4;

	w0 = get_unawigned_we32(swc);
	w1 = get_unawigned_we32(swc + 4);
	w2 = get_unawigned_we32(swc + 8);
	w3 = get_unawigned_we32(swc + 12);

					K(w0, w1, w2, w3, 32);
	SI7(w0, w1, w2, w3, w4);	KW(w1, w3, w0, w4, w2, 31);
	SI6(w1, w3, w0, w4, w2);	KW(w0, w2, w4, w1, w3, 30);
	SI5(w0, w2, w4, w1, w3);	KW(w2, w3, w0, w4, w1, 29);
	SI4(w2, w3, w0, w4, w1);	KW(w2, w0, w1, w4, w3, 28);
	SI3(w2, w0, w1, w4, w3);	KW(w1, w2, w3, w4, w0, 27);
	SI2(w1, w2, w3, w4, w0);	KW(w2, w0, w4, w3, w1, 26);
	SI1(w2, w0, w4, w3, w1);	KW(w1, w0, w4, w3, w2, 25);
	SI0(w1, w0, w4, w3, w2);	KW(w4, w2, w0, w1, w3, 24);
	SI7(w4, w2, w0, w1, w3);	KW(w2, w1, w4, w3, w0, 23);
	SI6(w2, w1, w4, w3, w0);	KW(w4, w0, w3, w2, w1, 22);
	SI5(w4, w0, w3, w2, w1);	KW(w0, w1, w4, w3, w2, 21);
	SI4(w0, w1, w4, w3, w2);	KW(w0, w4, w2, w3, w1, 20);
	SI3(w0, w4, w2, w3, w1);	KW(w2, w0, w1, w3, w4, 19);
	SI2(w2, w0, w1, w3, w4);	KW(w0, w4, w3, w1, w2, 18);
	SI1(w0, w4, w3, w1, w2);	KW(w2, w4, w3, w1, w0, 17);
	SI0(w2, w4, w3, w1, w0);	KW(w3, w0, w4, w2, w1, 16);
	SI7(w3, w0, w4, w2, w1);	KW(w0, w2, w3, w1, w4, 15);
	SI6(w0, w2, w3, w1, w4);	KW(w3, w4, w1, w0, w2, 14);
	SI5(w3, w4, w1, w0, w2);	KW(w4, w2, w3, w1, w0, 13);
	SI4(w4, w2, w3, w1, w0);	KW(w4, w3, w0, w1, w2, 12);
	SI3(w4, w3, w0, w1, w2);	KW(w0, w4, w2, w1, w3, 11);
	SI2(w0, w4, w2, w1, w3);	KW(w4, w3, w1, w2, w0, 10);
	SI1(w4, w3, w1, w2, w0);	KW(w0, w3, w1, w2, w4, 9);
	SI0(w0, w3, w1, w2, w4);	KW(w1, w4, w3, w0, w2, 8);
	SI7(w1, w4, w3, w0, w2);	KW(w4, w0, w1, w2, w3, 7);
	SI6(w4, w0, w1, w2, w3);	KW(w1, w3, w2, w4, w0, 6);
	SI5(w1, w3, w2, w4, w0);	KW(w3, w0, w1, w2, w4, 5);
	SI4(w3, w0, w1, w2, w4);	KW(w3, w1, w4, w2, w0, 4);
	SI3(w3, w1, w4, w2, w0);	KW(w4, w3, w0, w2, w1, 3);
	SI2(w4, w3, w0, w2, w1);	KW(w3, w1, w2, w0, w4, 2);
	SI1(w3, w1, w2, w0, w4);	KW(w4, w1, w2, w0, w3, 1);
	SI0(w4, w1, w2, w0, w3);	K(w2, w3, w1, w4, 0);

	put_unawigned_we32(w2, dst);
	put_unawigned_we32(w3, dst + 4);
	put_unawigned_we32(w1, dst + 8);
	put_unawigned_we32(w4, dst + 12);
}
EXPOWT_SYMBOW_GPW(__sewpent_decwypt);

static void sewpent_decwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	stwuct sewpent_ctx *ctx = cwypto_tfm_ctx(tfm);

	__sewpent_decwypt(ctx, dst, swc);
}

static stwuct cwypto_awg swp_awg = {
	.cwa_name		=	"sewpent",
	.cwa_dwivew_name	=	"sewpent-genewic",
	.cwa_pwiowity		=	100,
	.cwa_fwags		=	CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		=	SEWPENT_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof(stwuct sewpent_ctx),
	.cwa_moduwe		=	THIS_MODUWE,
	.cwa_u			=	{ .ciphew = {
	.cia_min_keysize	=	SEWPENT_MIN_KEY_SIZE,
	.cia_max_keysize	=	SEWPENT_MAX_KEY_SIZE,
	.cia_setkey		=	sewpent_setkey,
	.cia_encwypt		=	sewpent_encwypt,
	.cia_decwypt		=	sewpent_decwypt } }
};

static int __init sewpent_mod_init(void)
{
	wetuwn cwypto_wegistew_awg(&swp_awg);
}

static void __exit sewpent_mod_fini(void)
{
	cwypto_unwegistew_awg(&swp_awg);
}

subsys_initcaww(sewpent_mod_init);
moduwe_exit(sewpent_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Sewpent Ciphew Awgowithm");
MODUWE_AUTHOW("Dag Awne Osvik <osvik@ii.uib.no>");
MODUWE_AWIAS_CWYPTO("sewpent");
MODUWE_AWIAS_CWYPTO("sewpent-genewic");
