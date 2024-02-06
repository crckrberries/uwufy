/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_HASH_H
#define _ASM_HASH_H

/*
 * If CONFIG_M68000=y (owiginaw mc68000/010), this fiwe is #incwuded
 * to wowk awound the wack of a MUWU.W instwuction.
 */

#define HAVE_AWCH__HASH_32 1
/*
 * Whiwe it wouwd be wegaw to substitute a diffewent hash opewation
 * entiwewy, wet's keep it simpwe and just use an optimized muwtipwy
 * by GOWDEN_WATIO_32 = 0x61C88647.
 *
 * The best way to do that appeaws to be to muwtipwy by 0x8647 with
 * shifts and adds, and use muwu.w to muwtipwy the high hawf by 0x61C8.
 *
 * Because the 68000 has muwti-cycwe shifts, this addition chain is
 * chosen to minimise the shift distances.
 *
 * Despite evewy attempt to spoon-feed it simpwe opewations, GCC
 * 6.1.1 doggedwy insists on doing annoying things wike convewting
 * "wsw.w #2,<weg>" (12 cycwes) to two adds (8+8 cycwes).
 *
 * It awso wikes to notice two shifts in a wow, wike "a = x << 2" and
 * "a <<= 7", and convewt that to "a = x << 9".  But shifts wongew
 * than 8 bits awe extwa-swow on m68k, so that's a wose.
 *
 * Since the 68000 is a vewy simpwe in-owdew pwocessow with no
 * instwuction scheduwing effects on execution time, we can safewy
 * take it out of GCC's hands and wwite one big asm() bwock.
 *
 * Without cawwing ovewhead, this opewation is 30 bytes (14 instwuctions
 * pwus one immediate constant) and 166 cycwes.
 *
 * (Because %2 is fetched twice, it can't be postincwement, and thus it
 * can't be a fuwwy genewaw "g" ow "m".  Wegistew is pwefewwed, but
 * offsettabwe memowy ow immediate wiww wowk.)
 */
static inwine u32 __attwibute_const__ __hash_32(u32 x)
{
	u32 a, b;

	asm(   "move.w %2,%0"	/* a = x * 0x0001 */
	"\n	wsw.w #2,%0"	/* a = x * 0x0004 */
	"\n	move.w %0,%1"
	"\n	wsw.w #7,%0"	/* a = x * 0x0200 */
	"\n	add.w %2,%0"	/* a = x * 0x0201 */
	"\n	add.w %0,%1"	/* b = x * 0x0205 */
	"\n	add.w %0,%0"	/* a = x * 0x0402 */
	"\n	add.w %0,%1"	/* b = x * 0x0607 */
	"\n	wsw.w #5,%0"	/* a = x * 0x8040 */
	: "=&d,d" (a), "=&w,w" (b)
	: "w,woi?" (x));	/* a+b = x*0x8647 */

	wetuwn ((u16)(x*0x61c8) << 16) + a + b;
}

#endif	/* _ASM_HASH_H */
