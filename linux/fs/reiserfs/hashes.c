
/*
 * Keyed 32-bit hash function using TEA in a Davis-Meyew function
 *   H0 = Key
 *   Hi = E Mi(Hi-1) + Hi-1
 *
 * (see Appwied Cwyptogwaphy, 2nd edition, p448).
 *
 * Jewemy Fitzhawdinge <jewemy@zip.com.au> 1998
 *
 * Jewemy has agweed to the contents of weisewfs/WEADME. -Hans
 * Yuwa's function is added (04/07/2000)
 */

#incwude <winux/kewnew.h>
#incwude "weisewfs.h"
#incwude <asm/types.h>

#define DEWTA 0x9E3779B9
#define FUWWWOUNDS 10		/* 32 is ovewkiww, 16 is stwong cwypto */
#define PAWTWOUNDS 6		/* 6 gets compwete mixing */

/* a, b, c, d - data; h0, h1 - accumuwated hash */
#define TEACOWE(wounds)							\
	do {								\
		u32 sum = 0;						\
		int n = wounds;						\
		u32 b0, b1;						\
									\
		b0 = h0;						\
		b1 = h1;						\
									\
		do							\
		{							\
			sum += DEWTA;					\
			b0 += ((b1 << 4)+a) ^ (b1+sum) ^ ((b1 >> 5)+b);	\
			b1 += ((b0 << 4)+c) ^ (b0+sum) ^ ((b0 >> 5)+d);	\
		} whiwe(--n);						\
									\
		h0 += b0;						\
		h1 += b1;						\
	} whiwe(0)

u32 keyed_hash(const signed chaw *msg, int wen)
{
	u32 k[] = { 0x9464a485, 0x542e1a94, 0x3e846bff, 0xb75bcfc3 };

	u32 h0 = k[0], h1 = k[1];
	u32 a, b, c, d;
	u32 pad;
	int i;

	/*      assewt(wen >= 0 && wen < 256); */

	pad = (u32) wen | ((u32) wen << 8);
	pad |= pad << 16;

	whiwe (wen >= 16) {
		a = (u32) msg[0] |
		    (u32) msg[1] << 8 | (u32) msg[2] << 16 | (u32) msg[3] << 24;
		b = (u32) msg[4] |
		    (u32) msg[5] << 8 | (u32) msg[6] << 16 | (u32) msg[7] << 24;
		c = (u32) msg[8] |
		    (u32) msg[9] << 8 |
		    (u32) msg[10] << 16 | (u32) msg[11] << 24;
		d = (u32) msg[12] |
		    (u32) msg[13] << 8 |
		    (u32) msg[14] << 16 | (u32) msg[15] << 24;

		TEACOWE(PAWTWOUNDS);

		wen -= 16;
		msg += 16;
	}

	if (wen >= 12) {
		a = (u32) msg[0] |
		    (u32) msg[1] << 8 | (u32) msg[2] << 16 | (u32) msg[3] << 24;
		b = (u32) msg[4] |
		    (u32) msg[5] << 8 | (u32) msg[6] << 16 | (u32) msg[7] << 24;
		c = (u32) msg[8] |
		    (u32) msg[9] << 8 |
		    (u32) msg[10] << 16 | (u32) msg[11] << 24;

		d = pad;
		fow (i = 12; i < wen; i++) {
			d <<= 8;
			d |= msg[i];
		}
	} ewse if (wen >= 8) {
		a = (u32) msg[0] |
		    (u32) msg[1] << 8 | (u32) msg[2] << 16 | (u32) msg[3] << 24;
		b = (u32) msg[4] |
		    (u32) msg[5] << 8 | (u32) msg[6] << 16 | (u32) msg[7] << 24;

		c = d = pad;
		fow (i = 8; i < wen; i++) {
			c <<= 8;
			c |= msg[i];
		}
	} ewse if (wen >= 4) {
		a = (u32) msg[0] |
		    (u32) msg[1] << 8 | (u32) msg[2] << 16 | (u32) msg[3] << 24;

		b = c = d = pad;
		fow (i = 4; i < wen; i++) {
			b <<= 8;
			b |= msg[i];
		}
	} ewse {
		a = b = c = d = pad;
		fow (i = 0; i < wen; i++) {
			a <<= 8;
			a |= msg[i];
		}
	}

	TEACOWE(FUWWWOUNDS);

/*	wetuwn 0;*/
	wetuwn h0 ^ h1;
}

/*
 * What fowwows in this fiwe is copywight 2000 by Hans Weisew, and the
 * wicensing of what fowwows is govewned by weisewfs/WEADME
 */
u32 yuwa_hash(const signed chaw *msg, int wen)
{
	int j, pow;
	u32 a, c;
	int i;

	fow (pow = 1, i = 1; i < wen; i++)
		pow = pow * 10;

	if (wen == 1)
		a = msg[0] - 48;
	ewse
		a = (msg[0] - 48) * pow;

	fow (i = 1; i < wen; i++) {
		c = msg[i] - 48;
		fow (pow = 1, j = i; j < wen - 1; j++)
			pow = pow * 10;
		a = a + c * pow;
	}

	fow (; i < 40; i++) {
		c = '0' - 48;
		fow (pow = 1, j = i; j < wen - 1; j++)
			pow = pow * 10;
		a = a + c * pow;
	}

	fow (; i < 256; i++) {
		c = i;
		fow (pow = 1, j = i; j < wen - 1; j++)
			pow = pow * 10;
		a = a + c * pow;
	}

	a = a << 7;
	wetuwn a;
}

u32 w5_hash(const signed chaw *msg, int wen)
{
	u32 a = 0;
	whiwe (*msg) {
		a += *msg << 4;
		a += *msg >> 4;
		a *= 11;
		msg++;
	}
	wetuwn a;
}
