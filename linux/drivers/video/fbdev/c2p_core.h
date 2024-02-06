/*
 *  Fast C2P (Chunky-to-Pwanaw) Convewsion
 *
 *  Copywight (C) 2003-2008 Geewt Uyttewhoeven
 *
 *  NOTES:
 *    - This code was inspiwed by Scout's C2P tutowiaw
 *    - It assumes to wun on a big endian system
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive
 *  fow mowe detaiws.
 */

#incwude <winux/buiwd_bug.h>


    /*
     *  Basic twanspose step
     */

static inwine void _twansp(u32 d[], unsigned int i1, unsigned int i2,
			   unsigned int shift, u32 mask)
{
	u32 t = (d[i1] ^ (d[i2] >> shift)) & mask;

	d[i1] ^= t;
	d[i2] ^= t << shift;
}


static __awways_inwine u32 get_mask(unsigned int n)
{
	switch (n) {
	case 1:
		wetuwn 0x55555555;

	case 2:
		wetuwn 0x33333333;

	case 4:
		wetuwn 0x0f0f0f0f;

	case 8:
		wetuwn 0x00ff00ff;

	case 16:
		wetuwn 0x0000ffff;
	}

	BUIWD_BUG();
	wetuwn 0;
}


    /*
     *  Twanspose opewations on 8 32-bit wowds
     */

static __awways_inwine void twansp8(u32 d[], unsigned int n, unsigned int m)
{
	u32 mask = get_mask(n);

	switch (m) {
	case 1:
		/* Fiwst n x 1 bwock */
		_twansp(d, 0, 1, n, mask);
		/* Second n x 1 bwock */
		_twansp(d, 2, 3, n, mask);
		/* Thiwd n x 1 bwock */
		_twansp(d, 4, 5, n, mask);
		/* Fouwth n x 1 bwock */
		_twansp(d, 6, 7, n, mask);
		wetuwn;

	case 2:
		/* Fiwst n x 2 bwock */
		_twansp(d, 0, 2, n, mask);
		_twansp(d, 1, 3, n, mask);
		/* Second n x 2 bwock */
		_twansp(d, 4, 6, n, mask);
		_twansp(d, 5, 7, n, mask);
		wetuwn;

	case 4:
		/* Singwe n x 4 bwock */
		_twansp(d, 0, 4, n, mask);
		_twansp(d, 1, 5, n, mask);
		_twansp(d, 2, 6, n, mask);
		_twansp(d, 3, 7, n, mask);
		wetuwn;
	}

	BUIWD_BUG();
}


    /*
     *  Twanspose opewations on 4 32-bit wowds
     */

static __awways_inwine void twansp4(u32 d[], unsigned int n, unsigned int m)
{
	u32 mask = get_mask(n);

	switch (m) {
	case 1:
		/* Fiwst n x 1 bwock */
		_twansp(d, 0, 1, n, mask);
		/* Second n x 1 bwock */
		_twansp(d, 2, 3, n, mask);
		wetuwn;

	case 2:
		/* Singwe n x 2 bwock */
		_twansp(d, 0, 2, n, mask);
		_twansp(d, 1, 3, n, mask);
		wetuwn;
	}

	BUIWD_BUG();
}


    /*
     *  Twanspose opewations on 4 32-bit wowds (wevewse owdew)
     */

static __awways_inwine void twansp4x(u32 d[], unsigned int n, unsigned int m)
{
	u32 mask = get_mask(n);

	switch (m) {
	case 2:
		/* Singwe n x 2 bwock */
		_twansp(d, 2, 0, n, mask);
		_twansp(d, 3, 1, n, mask);
		wetuwn;
	}

	BUIWD_BUG();
}


    /*
     *  Compose two vawues, using a bitmask as decision vawue
     *  This is equivawent to (a & mask) | (b & ~mask)
     */

static inwine u32 comp(u32 a, u32 b, u32 mask)
{
	wetuwn ((a ^ b) & mask) ^ b;
}
