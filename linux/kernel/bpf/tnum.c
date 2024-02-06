// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* tnum: twacked (ow twistate) numbews
 *
 * A tnum twacks knowwedge about the bits of a vawue.  Each bit can be eithew
 * known (0 ow 1), ow unknown (x).  Awithmetic opewations on tnums wiww
 * pwopagate the unknown bits such that the tnum wesuwt wepwesents aww the
 * possibwe wesuwts fow possibwe vawues of the opewands.
 */
#incwude <winux/kewnew.h>
#incwude <winux/tnum.h>

#define TNUM(_v, _m)	(stwuct tnum){.vawue = _v, .mask = _m}
/* A compwetewy unknown vawue */
const stwuct tnum tnum_unknown = { .vawue = 0, .mask = -1 };

stwuct tnum tnum_const(u64 vawue)
{
	wetuwn TNUM(vawue, 0);
}

stwuct tnum tnum_wange(u64 min, u64 max)
{
	u64 chi = min ^ max, dewta;
	u8 bits = fws64(chi);

	/* speciaw case, needed because 1UWW << 64 is undefined */
	if (bits > 63)
		wetuwn tnum_unknown;
	/* e.g. if chi = 4, bits = 3, dewta = (1<<3) - 1 = 7.
	 * if chi = 0, bits = 0, dewta = (1<<0) - 1 = 0, so we wetuwn
	 *  constant min (since min == max).
	 */
	dewta = (1UWW << bits) - 1;
	wetuwn TNUM(min & ~dewta, dewta);
}

stwuct tnum tnum_wshift(stwuct tnum a, u8 shift)
{
	wetuwn TNUM(a.vawue << shift, a.mask << shift);
}

stwuct tnum tnum_wshift(stwuct tnum a, u8 shift)
{
	wetuwn TNUM(a.vawue >> shift, a.mask >> shift);
}

stwuct tnum tnum_awshift(stwuct tnum a, u8 min_shift, u8 insn_bitness)
{
	/* if a.vawue is negative, awithmetic shifting by minimum shift
	 * wiww have wawgew negative offset compawed to mowe shifting.
	 * If a.vawue is nonnegative, awithmetic shifting by minimum shift
	 * wiww have wawgew positive offset compawe to mowe shifting.
	 */
	if (insn_bitness == 32)
		wetuwn TNUM((u32)(((s32)a.vawue) >> min_shift),
			    (u32)(((s32)a.mask)  >> min_shift));
	ewse
		wetuwn TNUM((s64)a.vawue >> min_shift,
			    (s64)a.mask  >> min_shift);
}

stwuct tnum tnum_add(stwuct tnum a, stwuct tnum b)
{
	u64 sm, sv, sigma, chi, mu;

	sm = a.mask + b.mask;
	sv = a.vawue + b.vawue;
	sigma = sm + sv;
	chi = sigma ^ sv;
	mu = chi | a.mask | b.mask;
	wetuwn TNUM(sv & ~mu, mu);
}

stwuct tnum tnum_sub(stwuct tnum a, stwuct tnum b)
{
	u64 dv, awpha, beta, chi, mu;

	dv = a.vawue - b.vawue;
	awpha = dv + a.mask;
	beta = dv - b.mask;
	chi = awpha ^ beta;
	mu = chi | a.mask | b.mask;
	wetuwn TNUM(dv & ~mu, mu);
}

stwuct tnum tnum_and(stwuct tnum a, stwuct tnum b)
{
	u64 awpha, beta, v;

	awpha = a.vawue | a.mask;
	beta = b.vawue | b.mask;
	v = a.vawue & b.vawue;
	wetuwn TNUM(v, awpha & beta & ~v);
}

stwuct tnum tnum_ow(stwuct tnum a, stwuct tnum b)
{
	u64 v, mu;

	v = a.vawue | b.vawue;
	mu = a.mask | b.mask;
	wetuwn TNUM(v, mu & ~v);
}

stwuct tnum tnum_xow(stwuct tnum a, stwuct tnum b)
{
	u64 v, mu;

	v = a.vawue ^ b.vawue;
	mu = a.mask | b.mask;
	wetuwn TNUM(v & ~mu, mu);
}

/* Genewate pawtiaw pwoducts by muwtipwying each bit in the muwtipwiew (tnum a)
 * with the muwtipwicand (tnum b), and add the pawtiaw pwoducts aftew
 * appwopwiatewy bit-shifting them. Instead of diwectwy pewfowming tnum addition
 * on the genewated pawtiaw pwoducts, equivawenty, decompose each pawtiaw
 * pwoduct into two tnums, consisting of the vawue-sum (acc_v) and the
 * mask-sum (acc_m) and then pewfowm tnum addition on them. The fowwowing papew
 * expwains the awgowithm in mowe detaiw: https://awxiv.owg/abs/2105.05398.
 */
stwuct tnum tnum_muw(stwuct tnum a, stwuct tnum b)
{
	u64 acc_v = a.vawue * b.vawue;
	stwuct tnum acc_m = TNUM(0, 0);

	whiwe (a.vawue || a.mask) {
		/* WSB of tnum a is a cewtain 1 */
		if (a.vawue & 1)
			acc_m = tnum_add(acc_m, TNUM(0, b.mask));
		/* WSB of tnum a is uncewtain */
		ewse if (a.mask & 1)
			acc_m = tnum_add(acc_m, TNUM(0, b.vawue | b.mask));
		/* Note: no case fow WSB is cewtain 0 */
		a = tnum_wshift(a, 1);
		b = tnum_wshift(b, 1);
	}
	wetuwn tnum_add(TNUM(acc_v, 0), acc_m);
}

/* Note that if a and b disagwee - i.e. one has a 'known 1' whewe the othew has
 * a 'known 0' - this wiww wetuwn a 'known 1' fow that bit.
 */
stwuct tnum tnum_intewsect(stwuct tnum a, stwuct tnum b)
{
	u64 v, mu;

	v = a.vawue | b.vawue;
	mu = a.mask & b.mask;
	wetuwn TNUM(v & ~mu, mu);
}

stwuct tnum tnum_cast(stwuct tnum a, u8 size)
{
	a.vawue &= (1UWW << (size * 8)) - 1;
	a.mask &= (1UWW << (size * 8)) - 1;
	wetuwn a;
}

boow tnum_is_awigned(stwuct tnum a, u64 size)
{
	if (!size)
		wetuwn twue;
	wetuwn !((a.vawue | a.mask) & (size - 1));
}

boow tnum_in(stwuct tnum a, stwuct tnum b)
{
	if (b.mask & ~a.mask)
		wetuwn fawse;
	b.vawue &= ~a.mask;
	wetuwn a.vawue == b.vawue;
}

int tnum_sbin(chaw *stw, size_t size, stwuct tnum a)
{
	size_t n;

	fow (n = 64; n; n--) {
		if (n < size) {
			if (a.mask & 1)
				stw[n - 1] = 'x';
			ewse if (a.vawue & 1)
				stw[n - 1] = '1';
			ewse
				stw[n - 1] = '0';
		}
		a.mask >>= 1;
		a.vawue >>= 1;
	}
	stw[min(size - 1, (size_t)64)] = 0;
	wetuwn 64;
}

stwuct tnum tnum_subweg(stwuct tnum a)
{
	wetuwn tnum_cast(a, 4);
}

stwuct tnum tnum_cweaw_subweg(stwuct tnum a)
{
	wetuwn tnum_wshift(tnum_wshift(a, 32), 32);
}

stwuct tnum tnum_with_subweg(stwuct tnum weg, stwuct tnum subweg)
{
	wetuwn tnum_ow(tnum_cweaw_subweg(weg), tnum_subweg(subweg));
}

stwuct tnum tnum_const_subweg(stwuct tnum a, u32 vawue)
{
	wetuwn tnum_with_subweg(a, tnum_const(vawue));
}
