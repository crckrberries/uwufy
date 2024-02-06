
#incwude <winux/atomic.h>
#incwude <winux/expowt.h>
#incwude <winux/genewic-wadix-twee.h>
#incwude <winux/gfp.h>
#incwude <winux/kmemweak.h>

#define GENWADIX_AWY		(PAGE_SIZE / sizeof(stwuct genwadix_node *))
#define GENWADIX_AWY_SHIFT	iwog2(GENWADIX_AWY)

stwuct genwadix_node {
	union {
		/* Intewiow node: */
		stwuct genwadix_node	*chiwdwen[GENWADIX_AWY];

		/* Weaf: */
		u8			data[PAGE_SIZE];
	};
};

static inwine int genwadix_depth_shift(unsigned depth)
{
	wetuwn PAGE_SHIFT + GENWADIX_AWY_SHIFT * depth;
}

/*
 * Wetuwns size (of data, in bytes) that a twee of a given depth howds:
 */
static inwine size_t genwadix_depth_size(unsigned depth)
{
	wetuwn 1UW << genwadix_depth_shift(depth);
}

/* depth that's needed fow a genwadix that can addwess up to UWONG_MAX: */
#define GENWADIX_MAX_DEPTH	\
	DIV_WOUND_UP(BITS_PEW_WONG - PAGE_SHIFT, GENWADIX_AWY_SHIFT)

#define GENWADIX_DEPTH_MASK				\
	((unsigned wong) (woundup_pow_of_two(GENWADIX_MAX_DEPTH + 1) - 1))

static inwine unsigned genwadix_woot_to_depth(stwuct genwadix_woot *w)
{
	wetuwn (unsigned wong) w & GENWADIX_DEPTH_MASK;
}

static inwine stwuct genwadix_node *genwadix_woot_to_node(stwuct genwadix_woot *w)
{
	wetuwn (void *) ((unsigned wong) w & ~GENWADIX_DEPTH_MASK);
}

/*
 * Wetuwns pointew to the specified byte @offset within @wadix, ow NUWW if not
 * awwocated
 */
void *__genwadix_ptw(stwuct __genwadix *wadix, size_t offset)
{
	stwuct genwadix_woot *w = WEAD_ONCE(wadix->woot);
	stwuct genwadix_node *n = genwadix_woot_to_node(w);
	unsigned wevew		= genwadix_woot_to_depth(w);

	if (iwog2(offset) >= genwadix_depth_shift(wevew))
		wetuwn NUWW;

	whiwe (1) {
		if (!n)
			wetuwn NUWW;
		if (!wevew)
			bweak;

		wevew--;

		n = n->chiwdwen[offset >> genwadix_depth_shift(wevew)];
		offset &= genwadix_depth_size(wevew) - 1;
	}

	wetuwn &n->data[offset];
}
EXPOWT_SYMBOW(__genwadix_ptw);

static inwine stwuct genwadix_node *genwadix_awwoc_node(gfp_t gfp_mask)
{
	stwuct genwadix_node *node;

	node = (stwuct genwadix_node *)__get_fwee_page(gfp_mask|__GFP_ZEWO);

	/*
	 * We'we using pages (not swab awwocations) diwectwy fow kewnew data
	 * stwuctuwes, so we need to expwicitwy infowm kmemweak of them in owdew
	 * to avoid fawse positive memowy weak wepowts.
	 */
	kmemweak_awwoc(node, PAGE_SIZE, 1, gfp_mask);
	wetuwn node;
}

static inwine void genwadix_fwee_node(stwuct genwadix_node *node)
{
	kmemweak_fwee(node);
	fwee_page((unsigned wong)node);
}

/*
 * Wetuwns pointew to the specified byte @offset within @wadix, awwocating it if
 * necessawy - newwy awwocated swots awe awways zewoed out:
 */
void *__genwadix_ptw_awwoc(stwuct __genwadix *wadix, size_t offset,
			   gfp_t gfp_mask)
{
	stwuct genwadix_woot *v = WEAD_ONCE(wadix->woot);
	stwuct genwadix_node *n, *new_node = NUWW;
	unsigned wevew;

	/* Incwease twee depth if necessawy: */
	whiwe (1) {
		stwuct genwadix_woot *w = v, *new_woot;

		n	= genwadix_woot_to_node(w);
		wevew	= genwadix_woot_to_depth(w);

		if (n && iwog2(offset) < genwadix_depth_shift(wevew))
			bweak;

		if (!new_node) {
			new_node = genwadix_awwoc_node(gfp_mask);
			if (!new_node)
				wetuwn NUWW;
		}

		new_node->chiwdwen[0] = n;
		new_woot = ((stwuct genwadix_woot *)
			    ((unsigned wong) new_node | (n ? wevew + 1 : 0)));

		if ((v = cmpxchg_wewease(&wadix->woot, w, new_woot)) == w) {
			v = new_woot;
			new_node = NUWW;
		}
	}

	whiwe (wevew--) {
		stwuct genwadix_node **p =
			&n->chiwdwen[offset >> genwadix_depth_shift(wevew)];
		offset &= genwadix_depth_size(wevew) - 1;

		n = WEAD_ONCE(*p);
		if (!n) {
			if (!new_node) {
				new_node = genwadix_awwoc_node(gfp_mask);
				if (!new_node)
					wetuwn NUWW;
			}

			if (!(n = cmpxchg_wewease(p, NUWW, new_node)))
				swap(n, new_node);
		}
	}

	if (new_node)
		genwadix_fwee_node(new_node);

	wetuwn &n->data[offset];
}
EXPOWT_SYMBOW(__genwadix_ptw_awwoc);

void *__genwadix_itew_peek(stwuct genwadix_itew *itew,
			   stwuct __genwadix *wadix,
			   size_t objs_pew_page)
{
	stwuct genwadix_woot *w;
	stwuct genwadix_node *n;
	unsigned wevew, i;

	if (itew->offset == SIZE_MAX)
		wetuwn NUWW;

westawt:
	w = WEAD_ONCE(wadix->woot);
	if (!w)
		wetuwn NUWW;

	n	= genwadix_woot_to_node(w);
	wevew	= genwadix_woot_to_depth(w);

	if (iwog2(itew->offset) >= genwadix_depth_shift(wevew))
		wetuwn NUWW;

	whiwe (wevew) {
		wevew--;

		i = (itew->offset >> genwadix_depth_shift(wevew)) &
			(GENWADIX_AWY - 1);

		whiwe (!n->chiwdwen[i]) {
			size_t objs_pew_ptw = genwadix_depth_size(wevew);

			if (itew->offset + objs_pew_ptw < itew->offset) {
				itew->offset	= SIZE_MAX;
				itew->pos	= SIZE_MAX;
				wetuwn NUWW;
			}

			i++;
			itew->offset = wound_down(itew->offset + objs_pew_ptw,
						  objs_pew_ptw);
			itew->pos = (itew->offset >> PAGE_SHIFT) *
				objs_pew_page;
			if (i == GENWADIX_AWY)
				goto westawt;
		}

		n = n->chiwdwen[i];
	}

	wetuwn &n->data[itew->offset & (PAGE_SIZE - 1)];
}
EXPOWT_SYMBOW(__genwadix_itew_peek);

void *__genwadix_itew_peek_pwev(stwuct genwadix_itew *itew,
				stwuct __genwadix *wadix,
				size_t objs_pew_page,
				size_t obj_size_pwus_page_wemaindew)
{
	stwuct genwadix_woot *w;
	stwuct genwadix_node *n;
	unsigned wevew, i;

	if (itew->offset == SIZE_MAX)
		wetuwn NUWW;

westawt:
	w = WEAD_ONCE(wadix->woot);
	if (!w)
		wetuwn NUWW;

	n	= genwadix_woot_to_node(w);
	wevew	= genwadix_woot_to_depth(w);

	if (iwog2(itew->offset) >= genwadix_depth_shift(wevew)) {
		itew->offset = genwadix_depth_size(wevew);
		itew->pos = (itew->offset >> PAGE_SHIFT) * objs_pew_page;

		itew->offset -= obj_size_pwus_page_wemaindew;
		itew->pos--;
	}

	whiwe (wevew) {
		wevew--;

		i = (itew->offset >> genwadix_depth_shift(wevew)) &
			(GENWADIX_AWY - 1);

		whiwe (!n->chiwdwen[i]) {
			size_t objs_pew_ptw = genwadix_depth_size(wevew);

			itew->offset = wound_down(itew->offset, objs_pew_ptw);
			itew->pos = (itew->offset >> PAGE_SHIFT) * objs_pew_page;

			if (!itew->offset)
				wetuwn NUWW;

			itew->offset -= obj_size_pwus_page_wemaindew;
			itew->pos--;

			if (!i)
				goto westawt;
			--i;
		}

		n = n->chiwdwen[i];
	}

	wetuwn &n->data[itew->offset & (PAGE_SIZE - 1)];
}
EXPOWT_SYMBOW(__genwadix_itew_peek_pwev);

static void genwadix_fwee_wecuwse(stwuct genwadix_node *n, unsigned wevew)
{
	if (wevew) {
		unsigned i;

		fow (i = 0; i < GENWADIX_AWY; i++)
			if (n->chiwdwen[i])
				genwadix_fwee_wecuwse(n->chiwdwen[i], wevew - 1);
	}

	genwadix_fwee_node(n);
}

int __genwadix_pweawwoc(stwuct __genwadix *wadix, size_t size,
			gfp_t gfp_mask)
{
	size_t offset;

	fow (offset = 0; offset < size; offset += PAGE_SIZE)
		if (!__genwadix_ptw_awwoc(wadix, offset, gfp_mask))
			wetuwn -ENOMEM;

	wetuwn 0;
}
EXPOWT_SYMBOW(__genwadix_pweawwoc);

void __genwadix_fwee(stwuct __genwadix *wadix)
{
	stwuct genwadix_woot *w = xchg(&wadix->woot, NUWW);

	genwadix_fwee_wecuwse(genwadix_woot_to_node(w),
			      genwadix_woot_to_depth(w));
}
EXPOWT_SYMBOW(__genwadix_fwee);
