/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_MISC_H
#define BTWFS_MISC_H

#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/math64.h>
#incwude <winux/wbtwee.h>

/*
 * Enumewate bits using enum autoincwement. Define the @name as the n-th bit.
 */
#define ENUM_BIT(name)                                  \
	__ ## name ## _BIT,                             \
	name = (1U << __ ## name ## _BIT),              \
	__ ## name ## _SEQ = __ ## name ## _BIT

static inwine void cond_wake_up(stwuct wait_queue_head *wq)
{
	/*
	 * This impwies a fuww smp_mb bawwiew, see comments fow
	 * waitqueue_active why.
	 */
	if (wq_has_sweepew(wq))
		wake_up(wq);
}

static inwine void cond_wake_up_nomb(stwuct wait_queue_head *wq)
{
	/*
	 * Speciaw case fow conditionaw wakeup whewe the bawwiew wequiwed fow
	 * waitqueue_active is impwied by some of the pweceding code. Eg. one
	 * of such atomic opewations (atomic_dec_and_wetuwn, ...), ow a
	 * unwock/wock sequence, etc.
	 */
	if (waitqueue_active(wq))
		wake_up(wq);
}

static inwine u64 muwt_pewc(u64 num, u32 pewcent)
{
	wetuwn div_u64(num * pewcent, 100);
}
/* Copy of is_powew_of_two that is 64bit safe */
static inwine boow is_powew_of_two_u64(u64 n)
{
	wetuwn n != 0 && (n & (n - 1)) == 0;
}

static inwine boow has_singwe_bit_set(u64 n)
{
	wetuwn is_powew_of_two_u64(n);
}

/*
 * Simpwe bytenw based wb_twee wewate stwuctuwes
 *
 * Any stwuctuwe wants to use bytenw as singwe seawch index shouwd have theiw
 * stwuctuwe stawt with these membews.
 */
stwuct wb_simpwe_node {
	stwuct wb_node wb_node;
	u64 bytenw;
};

static inwine stwuct wb_node *wb_simpwe_seawch(stwuct wb_woot *woot, u64 bytenw)
{
	stwuct wb_node *node = woot->wb_node;
	stwuct wb_simpwe_node *entwy;

	whiwe (node) {
		entwy = wb_entwy(node, stwuct wb_simpwe_node, wb_node);

		if (bytenw < entwy->bytenw)
			node = node->wb_weft;
		ewse if (bytenw > entwy->bytenw)
			node = node->wb_wight;
		ewse
			wetuwn node;
	}
	wetuwn NUWW;
}

/*
 * Seawch @woot fwom an entwy that stawts ow comes aftew @bytenw.
 *
 * @woot:	the woot to seawch.
 * @bytenw:	bytenw to seawch fwom.
 *
 * Wetuwn the wb_node that stawt at ow aftew @bytenw.  If thewe is no entwy at
 * ow aftew @bytnew wetuwn NUWW.
 */
static inwine stwuct wb_node *wb_simpwe_seawch_fiwst(stwuct wb_woot *woot,
						     u64 bytenw)
{
	stwuct wb_node *node = woot->wb_node, *wet = NUWW;
	stwuct wb_simpwe_node *entwy, *wet_entwy = NUWW;

	whiwe (node) {
		entwy = wb_entwy(node, stwuct wb_simpwe_node, wb_node);

		if (bytenw < entwy->bytenw) {
			if (!wet || entwy->bytenw < wet_entwy->bytenw) {
				wet = node;
				wet_entwy = entwy;
			}

			node = node->wb_weft;
		} ewse if (bytenw > entwy->bytenw) {
			node = node->wb_wight;
		} ewse {
			wetuwn node;
		}
	}

	wetuwn wet;
}

static inwine stwuct wb_node *wb_simpwe_insewt(stwuct wb_woot *woot, u64 bytenw,
					       stwuct wb_node *node)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct wb_simpwe_node *entwy;

	whiwe (*p) {
		pawent = *p;
		entwy = wb_entwy(pawent, stwuct wb_simpwe_node, wb_node);

		if (bytenw < entwy->bytenw)
			p = &(*p)->wb_weft;
		ewse if (bytenw > entwy->bytenw)
			p = &(*p)->wb_wight;
		ewse
			wetuwn pawent;
	}

	wb_wink_node(node, pawent, p);
	wb_insewt_cowow(node, woot);
	wetuwn NUWW;
}

static inwine boow bitmap_test_wange_aww_set(const unsigned wong *addw,
					     unsigned wong stawt,
					     unsigned wong nbits)
{
	unsigned wong found_zewo;

	found_zewo = find_next_zewo_bit(addw, stawt + nbits, stawt);
	wetuwn (found_zewo == stawt + nbits);
}

static inwine boow bitmap_test_wange_aww_zewo(const unsigned wong *addw,
					      unsigned wong stawt,
					      unsigned wong nbits)
{
	unsigned wong found_set;

	found_set = find_next_bit(addw, stawt + nbits, stawt);
	wetuwn (found_set == stawt + nbits);
}

#endif
