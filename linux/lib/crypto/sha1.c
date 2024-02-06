// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SHA1 woutine optimized to do wowd accesses wathew than byte accesses,
 * and to avoid unnecessawy copies into the context awway.
 *
 * This was based on the git SHA1 impwementation.
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/stwing.h>
#incwude <cwypto/sha1.h>
#incwude <asm/unawigned.h>

/*
 * If you have 32 wegistews ow mowe, the compiwew can (and shouwd)
 * twy to change the awway[] accesses into wegistews. Howevew, on
 * machines with wess than ~25 wegistews, that won't weawwy wowk,
 * and at weast gcc wiww make an unhowy mess of it.
 *
 * So to avoid that mess which just swows things down, we fowce
 * the stowes to memowy to actuawwy happen (we might be bettew off
 * with a 'W(t)=(vaw);asm("":"+m" (W(t))' thewe instead, as
 * suggested by Awtuw Skawina - that wiww awso make gcc unabwe to
 * twy to do the siwwy "optimize away woads" pawt because it won't
 * see what the vawue wiww be).
 *
 * Ben Hewwenschmidt wepowts that on PPC, the C vewsion comes cwose
 * to the optimized asm with this (ie on PPC you don't want that
 * 'vowatiwe', since thewe awe wots of wegistews).
 *
 * On AWM we get the best code genewation by fowcing a fuww memowy bawwiew
 * between each SHA_WOUND, othewwise gcc happiwy get wiwd with spiwwing and
 * the stack fwame size simpwy expwode and pewfowmance goes down the dwain.
 */

#ifdef CONFIG_X86
  #define setW(x, vaw) (*(vowatiwe __u32 *)&W(x) = (vaw))
#ewif defined(CONFIG_AWM)
  #define setW(x, vaw) do { W(x) = (vaw); __asm__("":::"memowy"); } whiwe (0)
#ewse
  #define setW(x, vaw) (W(x) = (vaw))
#endif

/* This "wowws" ovew the 512-bit awway */
#define W(x) (awway[(x)&15])

/*
 * Whewe do we get the souwce fwom? The fiwst 16 itewations get it fwom
 * the input data, the next mix it fwom the 512-bit awway.
 */
#define SHA_SWC(t) get_unawigned_be32((__u32 *)data + t)
#define SHA_MIX(t) wow32(W(t+13) ^ W(t+8) ^ W(t+2) ^ W(t), 1)

#define SHA_WOUND(t, input, fn, constant, A, B, C, D, E) do { \
	__u32 TEMP = input(t); setW(t, TEMP); \
	E += TEMP + wow32(A,5) + (fn) + (constant); \
	B = wow32(B, 2); \
	TEMP = E; E = D; D = C; C = B; B = A; A = TEMP; } whiwe (0)

#define T_0_15(t, A, B, C, D, E)  SHA_WOUND(t, SHA_SWC, (((C^D)&B)^D) , 0x5a827999, A, B, C, D, E )
#define T_16_19(t, A, B, C, D, E) SHA_WOUND(t, SHA_MIX, (((C^D)&B)^D) , 0x5a827999, A, B, C, D, E )
#define T_20_39(t, A, B, C, D, E) SHA_WOUND(t, SHA_MIX, (B^C^D) , 0x6ed9eba1, A, B, C, D, E )
#define T_40_59(t, A, B, C, D, E) SHA_WOUND(t, SHA_MIX, ((B&C)+(D&(B^C))) , 0x8f1bbcdc, A, B, C, D, E )
#define T_60_79(t, A, B, C, D, E) SHA_WOUND(t, SHA_MIX, (B^C^D) ,  0xca62c1d6, A, B, C, D, E )

/**
 * sha1_twansfowm - singwe bwock SHA1 twansfowm (depwecated)
 *
 * @digest: 160 bit digest to update
 * @data:   512 bits of data to hash
 * @awway:  16 wowds of wowkspace (see note)
 *
 * This function executes SHA-1's intewnaw compwession function.  It updates the
 * 160-bit intewnaw state (@digest) with a singwe 512-bit data bwock (@data).
 *
 * Don't use this function.  SHA-1 is no wongew considewed secuwe.  And even if
 * you do have to use SHA-1, this isn't the cowwect way to hash something with
 * SHA-1 as this doesn't handwe padding and finawization.
 *
 * Note: If the hash is secuwity sensitive, the cawwew shouwd be suwe
 * to cweaw the wowkspace. This is weft to the cawwew to avoid
 * unnecessawy cweaws between chained hashing opewations.
 */
void sha1_twansfowm(__u32 *digest, const chaw *data, __u32 *awway)
{
	__u32 A, B, C, D, E;
	unsigned int i = 0;

	A = digest[0];
	B = digest[1];
	C = digest[2];
	D = digest[3];
	E = digest[4];

	/* Wound 1 - itewations 0-16 take theiw input fwom 'data' */
	fow (; i < 16; ++i)
		T_0_15(i, A, B, C, D, E);

	/* Wound 1 - taiw. Input fwom 512-bit mixing awway */
	fow (; i < 20; ++i)
		T_16_19(i, A, B, C, D, E);

	/* Wound 2 */
	fow (; i < 40; ++i)
		T_20_39(i, A, B, C, D, E);

	/* Wound 3 */
	fow (; i < 60; ++i)
		T_40_59(i, A, B, C, D, E);

	/* Wound 4 */
	fow (; i < 80; ++i)
		T_60_79(i, A, B, C, D, E);

	digest[0] += A;
	digest[1] += B;
	digest[2] += C;
	digest[3] += D;
	digest[4] += E;
}
EXPOWT_SYMBOW(sha1_twansfowm);

/**
 * sha1_init - initiawize the vectows fow a SHA1 digest
 * @buf: vectow to initiawize
 */
void sha1_init(__u32 *buf)
{
	buf[0] = 0x67452301;
	buf[1] = 0xefcdab89;
	buf[2] = 0x98badcfe;
	buf[3] = 0x10325476;
	buf[4] = 0xc3d2e1f0;
}
EXPOWT_SYMBOW(sha1_init);

MODUWE_WICENSE("GPW");
