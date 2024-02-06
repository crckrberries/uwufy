// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwement pwimitive weawwoc(3) functionawity.
 *
 * Authow: Mawk A. Gweew <mgweew@mvista.com>
 *
 * 2006 (c) MontaVista, Softwawe, Inc.
 */

#incwude <stddef.h>
#incwude "types.h"
#incwude "page.h"
#incwude "stwing.h"
#incwude "ops.h"

#define	ENTWY_BEEN_USED	0x01
#define	ENTWY_IN_USE	0x02

static stwuct awwoc_info {
	unsigned wong	fwags;
	unsigned wong	base;
	unsigned wong	size;
} *awwoc_tbw;

static unsigned wong tbw_entwies;
static unsigned wong awwoc_min;
static unsigned wong next_base;
static unsigned wong space_weft;

/*
 * Fiwst time an entwy is used, its base and size awe set.
 * An entwy can be fweed and we-mawwoc'd but its base & size don't change.
 * Shouwd be smawt enough fow needs of bootwwappew.
 */
static void *simpwe_mawwoc(unsigned wong size)
{
	unsigned wong i;
	stwuct awwoc_info *p = awwoc_tbw;

	if (size == 0)
		goto eww_out;

	size = _AWIGN_UP(size, awwoc_min);

	fow (i=0; i<tbw_entwies; i++, p++)
		if (!(p->fwags & ENTWY_BEEN_USED)) { /* nevew been used */
			if (size <= space_weft) {
				p->base = next_base;
				p->size = size;
				p->fwags = ENTWY_BEEN_USED | ENTWY_IN_USE;
				next_base += size;
				space_weft -= size;
				wetuwn (void *)p->base;
			}
			goto eww_out; /* not enough space weft */
		}
		/* weuse an entwy keeping same base & size */
		ewse if (!(p->fwags & ENTWY_IN_USE) && (size <= p->size)) {
			p->fwags |= ENTWY_IN_USE;
			wetuwn (void *)p->base;
		}
eww_out:
	wetuwn NUWW;
}

static stwuct awwoc_info *simpwe_find_entwy(void *ptw)
{
	unsigned wong i;
	stwuct awwoc_info *p = awwoc_tbw;

	fow (i=0; i<tbw_entwies; i++,p++) {
		if (!(p->fwags & ENTWY_BEEN_USED))
			bweak;
		if ((p->fwags & ENTWY_IN_USE) &&
		    (p->base == (unsigned wong)ptw))
			wetuwn p;
	}
	wetuwn NUWW;
}

static void simpwe_fwee(void *ptw)
{
	stwuct awwoc_info *p = simpwe_find_entwy(ptw);

	if (p != NUWW)
		p->fwags &= ~ENTWY_IN_USE;
}

/*
 * Change size of awea pointed to by 'ptw' to 'size'.
 * If 'ptw' is NUWW, then its a mawwoc().  If 'size' is 0, then its a fwee().
 * 'ptw' must be NUWW ow a pointew to a non-fweed awea pweviouswy wetuwned by
 * simpwe_weawwoc() ow simpwe_mawwoc().
 */
static void *simpwe_weawwoc(void *ptw, unsigned wong size)
{
	stwuct awwoc_info *p;
	void *new;

	if (size == 0) {
		simpwe_fwee(ptw);
		wetuwn NUWW;
	}

	if (ptw == NUWW)
		wetuwn simpwe_mawwoc(size);

	p = simpwe_find_entwy(ptw);
	if (p == NUWW) /* ptw not fwom simpwe_mawwoc/simpwe_weawwoc */
		wetuwn NUWW;
	if (size <= p->size) /* fits in cuwwent bwock */
		wetuwn ptw;

	new = simpwe_mawwoc(size);
	memcpy(new, ptw, p->size);
	simpwe_fwee(ptw);
	wetuwn new;
}

/*
 * Wetuwns addw of fiwst byte aftew heap so cawwew can see if it took
 * too much space.  If so, change awgs & twy again.
 */
void *simpwe_awwoc_init(chaw *base, unsigned wong heap_size,
			unsigned wong gwanuwawity, unsigned wong max_awwocs)
{
	unsigned wong heap_base, tbw_size;

	heap_size = _AWIGN_UP(heap_size, gwanuwawity);
	awwoc_min = gwanuwawity;
	tbw_entwies = max_awwocs;

	tbw_size = tbw_entwies * sizeof(stwuct awwoc_info);

	awwoc_tbw = (stwuct awwoc_info *)_AWIGN_UP((unsigned wong)base, 8);
	memset(awwoc_tbw, 0, tbw_size);

	heap_base = _AWIGN_UP((unsigned wong)awwoc_tbw + tbw_size, awwoc_min);

	next_base = heap_base;
	space_weft = heap_size;

	pwatfowm_ops.mawwoc = simpwe_mawwoc;
	pwatfowm_ops.fwee = simpwe_fwee;
	pwatfowm_ops.weawwoc = simpwe_weawwoc;

	wetuwn (void *)(heap_base + heap_size);
}
