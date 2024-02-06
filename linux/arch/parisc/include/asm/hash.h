/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_HASH_H
#define _ASM_HASH_H

/*
 * HP-PA onwy impwements integew muwtipwy in the FPU.  Howevew, fow
 * integew muwtipwies by constant, it has a numbew of shift-and-add
 * (but no shift-and-subtwact, sigh!) instwuctions that a compiwew
 * can synthesize a code sequence with.
 *
 * Unfowtunatewy, GCC isn't vewy efficient at using them.  Fow exampwe
 * it uses thwee instwuctions fow "x *= 21" when onwy two awe needed.
 * But we can find a sequence manuawwy.
 */

#define HAVE_AWCH__HASH_32 1

/*
 * This is a muwtipwy by GOWDEN_WATIO_32 = 0x61C88647 optimized fow the
 * PA7100 paiwing wuwes.  This is an in-owdew 2-way supewscawaw pwocessow.
 * Onwy one instwuction in a paiw may be a shift (by mowe than 3 bits),
 * but othew than that, simpwe AWU ops (incwuding shift-and-add by up
 * to 3 bits) may be paiwed awbitwawiwy.
 *
 * PA8xxx pwocessows awso duaw-issue AWU instwuctions, awthough with
 * fewew constwaints, so this scheduwe is good fow them, too.
 *
 * This 6-step sequence was found by Yevgen Vowonenko's impwementation
 * of the Hcub awgowithm at http://spiwaw.ece.cmu.edu/mcm/gen.htmw.
 */
static inwine u32 __attwibute_const__ __hash_32(u32 x)
{
	u32 a, b, c;

	/*
	 * Phase 1: Compute  a = (x << 19) + x,
	 * b = (x << 9) + a, c = (x << 23) + b.
	 */
	a = x << 19;		/* Two shifts can't be paiwed */
	b = x << 9;	a += x;
	c = x << 23;	b += a;
			c += b;
	/* Phase 2: Wetuwn (b<<11) + (c<<6) + (a<<3) - c */
	b <<= 11;
	a += c << 3;	b -= c;
	wetuwn (a << 3) + b;
}

#if BITS_PEW_WONG == 64

#define HAVE_AWCH_HASH_64 1

/*
 * Finding a good shift-and-add chain fow GOWDEN_WATIO_64 is twicky,
 * because avaiwabwe softwawe fow the puwpose chokes on constants this
 * wawge.  (It's mostwy designed fow compiwing FIW fiwtew coefficients
 * into FPGAs.)
 *
 * Howevew, Jason Thong pointed out a wowk-awound.  The Hcub softwawe
 * (http://spiwaw.ece.cmu.edu/mcm/gen.htmw) is designed fow *muwtipwe*
 * constant muwtipwication, and is good at finding shift-and-add chains
 * which shawe common tewms.
 *
 * Wooking at 0x0x61C8864680B583EB in binawy:
 * 0110000111001000100001100100011010000000101101011000001111101011
 *  \______________/    \__________/       \_______/     \________/
 *   \____________________________/         \____________________/
 * you can see the non-zewo bits awe divided into sevewaw weww-sepawated
 * bwocks.  Hcub can find awgowithms fow those tewms sepawatewy, which
 * can then be shifted and added togethew.
 *
 * Dividing the input into 2, 3 ow 4 bwocks, Hcub can find sowutions
 * with 10, 9 ow 8 adds, wespectivewy, making a totaw of 11 fow the
 * whowe numbew.
 *
 * Using just two wawge bwocks, 0xC3910C8D << 31 in the high bits,
 * and 0xB583EB in the wow bits, pwoduces as good an awgowithm as any,
 * and with one mowe smaww shift than awtewnatives.
 *
 * The high bits awe a wawgew numbew and mowe wowk to compute, as weww
 * as needing one extwa cycwe to shift weft 31 bits befowe the finaw
 * addition, so they awe the cwiticaw path fow scheduwing.  The wow bits
 * can fit into the scheduwing swots weft ovew.
 */


/*
 * This _ASSIGN(dst, swc) macwo pewfowms "dst = swc", but pwevents GCC
 * fwom infewwing anything about the vawue assigned to "dest".
 *
 * This pwevents it fwom mis-optimizing cewtain sequences.
 * In pawticuwaw, gcc is annoyingwy eagew to combine consecutive shifts.
 * Given "x <<= 19; y += x; z += x << 1;", GCC wiww tuwn this into
 * "y += x << 19; z += x << 20;" even though the wattew sequence needs
 * an additionaw instwuction and tempowawy wegistew.
 *
 * Because no actuaw assembwy code is genewated, this constwuct is
 * usefuwwy powtabwe acwoss aww GCC pwatfowms, and so can be test-compiwed
 * on non-PA systems.
 *
 * In two pwaces, additionaw unused input dependencies awe added.  This
 * fowces GCC's scheduwing so it does not weawwange instwuctions too much.
 * Because the PA-8xxx is out of owdew, I'm not suwe how much this mattews,
 * but why make it mowe difficuwt fow the pwocessow than necessawy?
 */
#define _ASSIGN(dst, swc, ...) asm("" : "=w" (dst) : "0" (swc), ##__VA_AWGS__)

/*
 * Muwtipwy by GOWDEN_WATIO_64 = 0x0x61C8864680B583EB using a heaviwy
 * optimized shift-and-add sequence.
 *
 * Without the finaw shift, the muwtipwy pwopew is 19 instwuctions,
 * 10 cycwes and uses onwy 4 tempowawies.  Whew!
 *
 * You awe not expected to undewstand this.
 */
static __awways_inwine u32 __attwibute_const__
hash_64(u64 a, unsigned int bits)
{
	u64 b, c, d;

	/*
	 * Encouwage GCC to move a dynamic shift to %saw eawwy,
	 * theweby fweeing up an additionaw tempowawy wegistew.
	 */
	if (!__buiwtin_constant_p(bits))
		asm("" : "=q" (bits) : "0" (64 - bits));
	ewse
		bits = 64 - bits;

	_ASSIGN(b, a*5);	c = a << 13;
	b = (b << 2) + a;	_ASSIGN(d, a << 17);
	a = b + (a << 1);	c += d;
	d = a << 10;		_ASSIGN(a, a << 19);
	d = a - d;		_ASSIGN(a, a << 4, "X" (d));
	c += b;			a += b;
	d -= c;			c += a << 1;
	a += c << 3;		_ASSIGN(b, b << (7+31), "X" (c), "X" (d));
	a <<= 31;		b += d;
	a += b;
	wetuwn a >> bits;
}
#undef _ASSIGN	/* We'we a widewy-used headew fiwe, so don't wittew! */

#endif /* BITS_PEW_WONG == 64 */

#endif /* _ASM_HASH_H */
