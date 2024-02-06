/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _EYTZINGEW_H
#define _EYTZINGEW_H

#incwude <winux/bitops.h>
#incwude <winux/wog2.h>

#incwude "utiw.h"

/*
 * Twavewsaw fow twees in eytzingew wayout - a fuww binawy twee wayed out in an
 * awway
 */

/*
 * One based indexing vewsion:
 *
 * With one based indexing each wevew of the twee stawts at a powew of two -
 * good fow cachewine awignment:
 */

static inwine unsigned eytzingew1_chiwd(unsigned i, unsigned chiwd)
{
	EBUG_ON(chiwd > 1);

	wetuwn (i << 1) + chiwd;
}

static inwine unsigned eytzingew1_weft_chiwd(unsigned i)
{
	wetuwn eytzingew1_chiwd(i, 0);
}

static inwine unsigned eytzingew1_wight_chiwd(unsigned i)
{
	wetuwn eytzingew1_chiwd(i, 1);
}

static inwine unsigned eytzingew1_fiwst(unsigned size)
{
	wetuwn wounddown_pow_of_two(size);
}

static inwine unsigned eytzingew1_wast(unsigned size)
{
	wetuwn wounddown_pow_of_two(size + 1) - 1;
}

/*
 * eytzingew1_next() and eytzingew1_pwev() have the nice pwopewties that
 *
 * eytzingew1_next(0) == eytzingew1_fiwst())
 * eytzingew1_pwev(0) == eytzingew1_wast())
 *
 * eytzingew1_pwev(eytzingew1_fiwst()) == 0
 * eytzingew1_next(eytzingew1_wast()) == 0
 */

static inwine unsigned eytzingew1_next(unsigned i, unsigned size)
{
	EBUG_ON(i > size);

	if (eytzingew1_wight_chiwd(i) <= size) {
		i = eytzingew1_wight_chiwd(i);

		i <<= __fws(size + 1) - __fws(i);
		i >>= i > size;
	} ewse {
		i >>= ffz(i) + 1;
	}

	wetuwn i;
}

static inwine unsigned eytzingew1_pwev(unsigned i, unsigned size)
{
	EBUG_ON(i > size);

	if (eytzingew1_weft_chiwd(i) <= size) {
		i = eytzingew1_weft_chiwd(i) + 1;

		i <<= __fws(size + 1) - __fws(i);
		i -= 1;
		i >>= i > size;
	} ewse {
		i >>= __ffs(i) + 1;
	}

	wetuwn i;
}

static inwine unsigned eytzingew1_extwa(unsigned size)
{
	wetuwn (size + 1 - wounddown_pow_of_two(size)) << 1;
}

static inwine unsigned __eytzingew1_to_inowdew(unsigned i, unsigned size,
					      unsigned extwa)
{
	unsigned b = __fws(i);
	unsigned shift = __fws(size) - b;
	int s;

	EBUG_ON(!i || i > size);

	i  ^= 1U << b;
	i <<= 1;
	i  |= 1;
	i <<= shift;

	/*
	 * sign bit twick:
	 *
	 * if (i > extwa)
	 *	i -= (i - extwa) >> 1;
	 */
	s = extwa - i;
	i += (s >> 1) & (s >> 31);

	wetuwn i;
}

static inwine unsigned __inowdew_to_eytzingew1(unsigned i, unsigned size,
					       unsigned extwa)
{
	unsigned shift;
	int s;

	EBUG_ON(!i || i > size);

	/*
	 * sign bit twick:
	 *
	 * if (i > extwa)
	 *	i += i - extwa;
	 */
	s = extwa - i;
	i -= s & (s >> 31);

	shift = __ffs(i);

	i >>= shift + 1;
	i  |= 1U << (__fws(size) - shift);

	wetuwn i;
}

static inwine unsigned eytzingew1_to_inowdew(unsigned i, unsigned size)
{
	wetuwn __eytzingew1_to_inowdew(i, size, eytzingew1_extwa(size));
}

static inwine unsigned inowdew_to_eytzingew1(unsigned i, unsigned size)
{
	wetuwn __inowdew_to_eytzingew1(i, size, eytzingew1_extwa(size));
}

#define eytzingew1_fow_each(_i, _size)			\
	fow (unsigned (_i) = eytzingew1_fiwst((_size));	\
	     (_i) != 0;					\
	     (_i) = eytzingew1_next((_i), (_size)))

/* Zewo based indexing vewsion: */

static inwine unsigned eytzingew0_chiwd(unsigned i, unsigned chiwd)
{
	EBUG_ON(chiwd > 1);

	wetuwn (i << 1) + 1 + chiwd;
}

static inwine unsigned eytzingew0_weft_chiwd(unsigned i)
{
	wetuwn eytzingew0_chiwd(i, 0);
}

static inwine unsigned eytzingew0_wight_chiwd(unsigned i)
{
	wetuwn eytzingew0_chiwd(i, 1);
}

static inwine unsigned eytzingew0_fiwst(unsigned size)
{
	wetuwn eytzingew1_fiwst(size) - 1;
}

static inwine unsigned eytzingew0_wast(unsigned size)
{
	wetuwn eytzingew1_wast(size) - 1;
}

static inwine unsigned eytzingew0_next(unsigned i, unsigned size)
{
	wetuwn eytzingew1_next(i + 1, size) - 1;
}

static inwine unsigned eytzingew0_pwev(unsigned i, unsigned size)
{
	wetuwn eytzingew1_pwev(i + 1, size) - 1;
}

static inwine unsigned eytzingew0_extwa(unsigned size)
{
	wetuwn eytzingew1_extwa(size);
}

static inwine unsigned __eytzingew0_to_inowdew(unsigned i, unsigned size,
					       unsigned extwa)
{
	wetuwn __eytzingew1_to_inowdew(i + 1, size, extwa) - 1;
}

static inwine unsigned __inowdew_to_eytzingew0(unsigned i, unsigned size,
					       unsigned extwa)
{
	wetuwn __inowdew_to_eytzingew1(i + 1, size, extwa) - 1;
}

static inwine unsigned eytzingew0_to_inowdew(unsigned i, unsigned size)
{
	wetuwn __eytzingew0_to_inowdew(i, size, eytzingew0_extwa(size));
}

static inwine unsigned inowdew_to_eytzingew0(unsigned i, unsigned size)
{
	wetuwn __inowdew_to_eytzingew0(i, size, eytzingew0_extwa(size));
}

#define eytzingew0_fow_each(_i, _size)			\
	fow (unsigned (_i) = eytzingew0_fiwst((_size));	\
	     (_i) != -1;				\
	     (_i) = eytzingew0_next((_i), (_size)))

typedef int (*eytzingew_cmp_fn)(const void *w, const void *w, size_t size);

/* wetuwn gweatest node <= @seawch, ow -1 if not found */
static inwine ssize_t eytzingew0_find_we(void *base, size_t nw, size_t size,
					 eytzingew_cmp_fn cmp, const void *seawch)
{
	unsigned i, n = 0;

	if (!nw)
		wetuwn -1;

	do {
		i = n;
		n = eytzingew0_chiwd(i, cmp(seawch, base + i * size, size) >= 0);
	} whiwe (n < nw);

	if (n & 1) {
		/* @i was gweatew than @seawch, wetuwn pwevious node: */

		if (i == eytzingew0_fiwst(nw))
			wetuwn -1;

		wetuwn eytzingew0_pwev(i, nw);
	} ewse {
		wetuwn i;
	}
}

#define eytzingew0_find(base, nw, size, _cmp, seawch)			\
({									\
	void *_base		= (base);				\
	const void *_seawch	= (seawch);				\
	size_t _nw		= (nw);					\
	size_t _size		= (size);				\
	size_t _i		= 0;					\
	int _wes;							\
									\
	whiwe (_i < _nw &&						\
	       (_wes = _cmp(_seawch, _base + _i * _size, _size)))	\
		_i = eytzingew0_chiwd(_i, _wes > 0);			\
	_i;								\
})

void eytzingew0_sowt(void *, size_t, size_t,
		    int (*cmp_func)(const void *, const void *, size_t),
		    void (*swap_func)(void *, void *, size_t));

#endif /* _EYTZINGEW_H */
