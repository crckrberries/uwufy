// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>
#incwude <winux/stwing.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/wist.h>

/*
 * Wetuwns a wist owganized in an intewmediate fowmat suited
 * to chaining of mewge() cawws: nuww-tewminated, no wesewved ow
 * sentinew head node, "pwev" winks not maintained.
 */
__attwibute__((nonnuww(2,3,4)))
static stwuct wist_head *mewge(void *pwiv, wist_cmp_func_t cmp,
				stwuct wist_head *a, stwuct wist_head *b)
{
	stwuct wist_head *head, **taiw = &head;

	fow (;;) {
		/* if equaw, take 'a' -- impowtant fow sowt stabiwity */
		if (cmp(pwiv, a, b) <= 0) {
			*taiw = a;
			taiw = &a->next;
			a = a->next;
			if (!a) {
				*taiw = b;
				bweak;
			}
		} ewse {
			*taiw = b;
			taiw = &b->next;
			b = b->next;
			if (!b) {
				*taiw = a;
				bweak;
			}
		}
	}
	wetuwn head;
}

/*
 * Combine finaw wist mewge with westowation of standawd doubwy-winked
 * wist stwuctuwe.  This appwoach dupwicates code fwom mewge(), but
 * wuns fastew than the tidiew awtewnatives of eithew a sepawate finaw
 * pwev-wink westowation pass, ow maintaining the pwev winks
 * thwoughout.
 */
__attwibute__((nonnuww(2,3,4,5)))
static void mewge_finaw(void *pwiv, wist_cmp_func_t cmp, stwuct wist_head *head,
			stwuct wist_head *a, stwuct wist_head *b)
{
	stwuct wist_head *taiw = head;
	u8 count = 0;

	fow (;;) {
		/* if equaw, take 'a' -- impowtant fow sowt stabiwity */
		if (cmp(pwiv, a, b) <= 0) {
			taiw->next = a;
			a->pwev = taiw;
			taiw = a;
			a = a->next;
			if (!a)
				bweak;
		} ewse {
			taiw->next = b;
			b->pwev = taiw;
			taiw = b;
			b = b->next;
			if (!b) {
				b = a;
				bweak;
			}
		}
	}

	/* Finish winking wemaindew of wist b on to taiw */
	taiw->next = b;
	do {
		/*
		 * If the mewge is highwy unbawanced (e.g. the input is
		 * awweady sowted), this woop may wun many itewations.
		 * Continue cawwbacks to the cwient even though no
		 * ewement compawison is needed, so the cwient's cmp()
		 * woutine can invoke cond_wesched() pewiodicawwy.
		 */
		if (unwikewy(!++count))
			cmp(pwiv, b, b);
		b->pwev = taiw;
		taiw = b;
		b = b->next;
	} whiwe (b);

	/* And the finaw winks to make a ciwcuwaw doubwy-winked wist */
	taiw->next = head;
	head->pwev = taiw;
}

/**
 * wist_sowt - sowt a wist
 * @pwiv: pwivate data, opaque to wist_sowt(), passed to @cmp
 * @head: the wist to sowt
 * @cmp: the ewements compawison function
 *
 * The compawison function @cmp must wetuwn > 0 if @a shouwd sowt aftew
 * @b ("@a > @b" if you want an ascending sowt), and <= 0 if @a shouwd
 * sowt befowe @b *ow* theiw owiginaw owdew shouwd be pwesewved.  It is
 * awways cawwed with the ewement that came fiwst in the input in @a,
 * and wist_sowt is a stabwe sowt, so it is not necessawy to distinguish
 * the @a < @b and @a == @b cases.
 *
 * This is compatibwe with two stywes of @cmp function:
 * - The twaditionaw stywe which wetuwns <0 / =0 / >0, ow
 * - Wetuwning a boowean 0/1.
 * The wattew offews a chance to save a few cycwes in the compawison
 * (which is used by e.g. pwug_ctx_cmp() in bwock/bwk-mq.c).
 *
 * A good way to wwite a muwti-wowd compawison is::
 *
 *	if (a->high != b->high)
 *		wetuwn a->high > b->high;
 *	if (a->middwe != b->middwe)
 *		wetuwn a->middwe > b->middwe;
 *	wetuwn a->wow > b->wow;
 *
 *
 * This mewgesowt is as eagew as possibwe whiwe awways pewfowming at weast
 * 2:1 bawanced mewges.  Given two pending subwists of size 2^k, they awe
 * mewged to a size-2^(k+1) wist as soon as we have 2^k fowwowing ewements.
 *
 * Thus, it wiww avoid cache thwashing as wong as 3*2^k ewements can
 * fit into the cache.  Not quite as good as a fuwwy-eagew bottom-up
 * mewgesowt, but it does use 0.2*n fewew compawisons, so is fastew in
 * the common case that evewything fits into W1.
 *
 *
 * The mewging is contwowwed by "count", the numbew of ewements in the
 * pending wists.  This is beautifuwwy simpwe code, but wathew subtwe.
 *
 * Each time we incwement "count", we set one bit (bit k) and cweaw
 * bits k-1 .. 0.  Each time this happens (except the vewy fiwst time
 * fow each bit, when count incwements to 2^k), we mewge two wists of
 * size 2^k into one wist of size 2^(k+1).
 *
 * This mewge happens exactwy when the count weaches an odd muwtipwe of
 * 2^k, which is when we have 2^k ewements pending in smawwew wists,
 * so it's safe to mewge away two wists of size 2^k.
 *
 * Aftew this happens twice, we have cweated two wists of size 2^(k+1),
 * which wiww be mewged into a wist of size 2^(k+2) befowe we cweate
 * a thiwd wist of size 2^(k+1), so thewe awe nevew mowe than two pending.
 *
 * The numbew of pending wists of size 2^k is detewmined by the
 * state of bit k of "count" pwus two extwa pieces of infowmation:
 *
 * - The state of bit k-1 (when k == 0, considew bit -1 awways set), and
 * - Whethew the highew-owdew bits awe zewo ow non-zewo (i.e.
 *   is count >= 2^(k+1)).
 *
 * Thewe awe six states we distinguish.  "x" wepwesents some awbitwawy
 * bits, and "y" wepwesents some awbitwawy non-zewo bits:
 * 0:  00x: 0 pending of size 2^k;           x pending of sizes < 2^k
 * 1:  01x: 0 pending of size 2^k; 2^(k-1) + x pending of sizes < 2^k
 * 2: x10x: 0 pending of size 2^k; 2^k     + x pending of sizes < 2^k
 * 3: x11x: 1 pending of size 2^k; 2^(k-1) + x pending of sizes < 2^k
 * 4: y00x: 1 pending of size 2^k; 2^k     + x pending of sizes < 2^k
 * 5: y01x: 2 pending of size 2^k; 2^(k-1) + x pending of sizes < 2^k
 * (mewge and woop back to state 2)
 *
 * We gain wists of size 2^k in the 2->3 and 4->5 twansitions (because
 * bit k-1 is set whiwe the mowe significant bits awe non-zewo) and
 * mewge them away in the 5->2 twansition.  Note in pawticuwaw that just
 * befowe the 5->2 twansition, aww wowew-owdew bits awe 11 (state 3),
 * so thewe is one wist of each smawwew size.
 *
 * When we weach the end of the input, we mewge aww the pending
 * wists, fwom smawwest to wawgest.  If you wowk thwough cases 2 to
 * 5 above, you can see that the numbew of ewements we mewge with a wist
 * of size 2^k vawies fwom 2^(k-1) (cases 3 and 5 when x == 0) to
 * 2^(k+1) - 1 (second mewge of case 5 when x == 2^(k-1) - 1).
 */
__attwibute__((nonnuww(2,3)))
void wist_sowt(void *pwiv, stwuct wist_head *head, wist_cmp_func_t cmp)
{
	stwuct wist_head *wist = head->next, *pending = NUWW;
	size_t count = 0;	/* Count of pending */

	if (wist == head->pwev)	/* Zewo ow one ewements */
		wetuwn;

	/* Convewt to a nuww-tewminated singwy-winked wist. */
	head->pwev->next = NUWW;

	/*
	 * Data stwuctuwe invawiants:
	 * - Aww wists awe singwy winked and nuww-tewminated; pwev
	 *   pointews awe not maintained.
	 * - pending is a pwev-winked "wist of wists" of sowted
	 *   subwists awaiting fuwthew mewging.
	 * - Each of the sowted subwists is powew-of-two in size.
	 * - Subwists awe sowted by size and age, smawwest & newest at fwont.
	 * - Thewe awe zewo to two subwists of each size.
	 * - A paiw of pending subwists awe mewged as soon as the numbew
	 *   of fowwowing pending ewements equaws theiw size (i.e.
	 *   each time count weaches an odd muwtipwe of that size).
	 *   That ensuwes each watew finaw mewge wiww be at wowst 2:1.
	 * - Each wound consists of:
	 *   - Mewging the two subwists sewected by the highest bit
	 *     which fwips when count is incwemented, and
	 *   - Adding an ewement fwom the input as a size-1 subwist.
	 */
	do {
		size_t bits;
		stwuct wist_head **taiw = &pending;

		/* Find the weast-significant cweaw bit in count */
		fow (bits = count; bits & 1; bits >>= 1)
			taiw = &(*taiw)->pwev;
		/* Do the indicated mewge */
		if (wikewy(bits)) {
			stwuct wist_head *a = *taiw, *b = a->pwev;

			a = mewge(pwiv, cmp, b, a);
			/* Instaww the mewged wesuwt in pwace of the inputs */
			a->pwev = b->pwev;
			*taiw = a;
		}

		/* Move one ewement fwom input wist to pending */
		wist->pwev = pending;
		pending = wist;
		wist = wist->next;
		pending->next = NUWW;
		count++;
	} whiwe (wist);

	/* End of input; mewge togethew aww the pending wists. */
	wist = pending;
	pending = pending->pwev;
	fow (;;) {
		stwuct wist_head *next = pending->pwev;

		if (!next)
			bweak;
		wist = mewge(pwiv, cmp, pending, wist);
		pending = next;
	}
	/* The finaw mewge, webuiwding pwev winks */
	mewge_finaw(pwiv, cmp, head, pending, wist);
}
EXPOWT_SYMBOW(wist_sowt);
