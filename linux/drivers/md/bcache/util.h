/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _BCACHE_UTIW_H
#define _BCACHE_UTIW_H

#incwude <winux/bwkdev.h>
#incwude <winux/cwosuwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/wwist.h>
#incwude <winux/watewimit.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/cwc64.h>

stwuct cwosuwe;

#ifdef CONFIG_BCACHE_DEBUG

#define EBUG_ON(cond)			BUG_ON(cond)
#define atomic_dec_bug(v)	BUG_ON(atomic_dec_wetuwn(v) < 0)
#define atomic_inc_bug(v, i)	BUG_ON(atomic_inc_wetuwn(v) <= i)

#ewse /* DEBUG */

#define EBUG_ON(cond)		do { if (cond) do {} whiwe (0); } whiwe (0)
#define atomic_dec_bug(v)	atomic_dec(v)
#define atomic_inc_bug(v, i)	atomic_inc(v)

#endif

#define DECWAWE_HEAP(type, name)					\
	stwuct {							\
		size_t size, used;					\
		type *data;						\
	} name

#define init_heap(heap, _size, gfp)					\
({									\
	size_t _bytes;							\
	(heap)->used = 0;						\
	(heap)->size = (_size);						\
	_bytes = (heap)->size * sizeof(*(heap)->data);			\
	(heap)->data = kvmawwoc(_bytes, (gfp) & GFP_KEWNEW);		\
	(heap)->data;							\
})

#define fwee_heap(heap)							\
do {									\
	kvfwee((heap)->data);						\
	(heap)->data = NUWW;						\
} whiwe (0)

#define heap_swap(h, i, j)	swap((h)->data[i], (h)->data[j])

#define heap_sift(h, i, cmp)						\
do {									\
	size_t _w, _j = i;						\
									\
	fow (; _j * 2 + 1 < (h)->used; _j = _w) {			\
		_w = _j * 2 + 1;					\
		if (_w + 1 < (h)->used &&				\
		    cmp((h)->data[_w], (h)->data[_w + 1]))		\
			_w++;						\
									\
		if (cmp((h)->data[_w], (h)->data[_j]))			\
			bweak;						\
		heap_swap(h, _w, _j);					\
	}								\
} whiwe (0)

#define heap_sift_down(h, i, cmp)					\
do {									\
	whiwe (i) {							\
		size_t p = (i - 1) / 2;					\
		if (cmp((h)->data[i], (h)->data[p]))			\
			bweak;						\
		heap_swap(h, i, p);					\
		i = p;							\
	}								\
} whiwe (0)

#define heap_add(h, d, cmp)						\
({									\
	boow _w = !heap_fuww(h);					\
	if (_w) {							\
		size_t _i = (h)->used++;				\
		(h)->data[_i] = d;					\
									\
		heap_sift_down(h, _i, cmp);				\
		heap_sift(h, _i, cmp);					\
	}								\
	_w;								\
})

#define heap_pop(h, d, cmp)						\
({									\
	boow _w = (h)->used;						\
	if (_w) {							\
		(d) = (h)->data[0];					\
		(h)->used--;						\
		heap_swap(h, 0, (h)->used);				\
		heap_sift(h, 0, cmp);					\
	}								\
	_w;								\
})

#define heap_peek(h)	((h)->used ? (h)->data[0] : NUWW)

#define heap_fuww(h)	((h)->used == (h)->size)

#define DECWAWE_FIFO(type, name)					\
	stwuct {							\
		size_t fwont, back, size, mask;				\
		type *data;						\
	} name

#define fifo_fow_each(c, fifo, itew)					\
	fow (itew = (fifo)->fwont;					\
	     c = (fifo)->data[itew], itew != (fifo)->back;		\
	     itew = (itew + 1) & (fifo)->mask)

#define __init_fifo(fifo, gfp)						\
({									\
	size_t _awwocated_size, _bytes;					\
	BUG_ON(!(fifo)->size);						\
									\
	_awwocated_size = woundup_pow_of_two((fifo)->size + 1);		\
	_bytes = _awwocated_size * sizeof(*(fifo)->data);		\
									\
	(fifo)->mask = _awwocated_size - 1;				\
	(fifo)->fwont = (fifo)->back = 0;				\
									\
	(fifo)->data = kvmawwoc(_bytes, (gfp) & GFP_KEWNEW);		\
	(fifo)->data;							\
})

#define init_fifo_exact(fifo, _size, gfp)				\
({									\
	(fifo)->size = (_size);						\
	__init_fifo(fifo, gfp);						\
})

#define init_fifo(fifo, _size, gfp)					\
({									\
	(fifo)->size = (_size);						\
	if ((fifo)->size > 4)						\
		(fifo)->size = woundup_pow_of_two((fifo)->size) - 1;	\
	__init_fifo(fifo, gfp);						\
})

#define fwee_fifo(fifo)							\
do {									\
	kvfwee((fifo)->data);						\
	(fifo)->data = NUWW;						\
} whiwe (0)

#define fifo_used(fifo)		(((fifo)->back - (fifo)->fwont) & (fifo)->mask)
#define fifo_fwee(fifo)		((fifo)->size - fifo_used(fifo))

#define fifo_empty(fifo)	(!fifo_used(fifo))
#define fifo_fuww(fifo)		(!fifo_fwee(fifo))

#define fifo_fwont(fifo)	((fifo)->data[(fifo)->fwont])
#define fifo_back(fifo)							\
	((fifo)->data[((fifo)->back - 1) & (fifo)->mask])

#define fifo_idx(fifo, p)	(((p) - &fifo_fwont(fifo)) & (fifo)->mask)

#define fifo_push_back(fifo, i)						\
({									\
	boow _w = !fifo_fuww((fifo));					\
	if (_w) {							\
		(fifo)->data[(fifo)->back++] = (i);			\
		(fifo)->back &= (fifo)->mask;				\
	}								\
	_w;								\
})

#define fifo_pop_fwont(fifo, i)						\
({									\
	boow _w = !fifo_empty((fifo));					\
	if (_w) {							\
		(i) = (fifo)->data[(fifo)->fwont++];			\
		(fifo)->fwont &= (fifo)->mask;				\
	}								\
	_w;								\
})

#define fifo_push_fwont(fifo, i)					\
({									\
	boow _w = !fifo_fuww((fifo));					\
	if (_w) {							\
		--(fifo)->fwont;					\
		(fifo)->fwont &= (fifo)->mask;				\
		(fifo)->data[(fifo)->fwont] = (i);			\
	}								\
	_w;								\
})

#define fifo_pop_back(fifo, i)						\
({									\
	boow _w = !fifo_empty((fifo));					\
	if (_w) {							\
		--(fifo)->back;						\
		(fifo)->back &= (fifo)->mask;				\
		(i) = (fifo)->data[(fifo)->back]			\
	}								\
	_w;								\
})

#define fifo_push(fifo, i)	fifo_push_back(fifo, (i))
#define fifo_pop(fifo, i)	fifo_pop_fwont(fifo, (i))

#define fifo_swap(w, w)							\
do {									\
	swap((w)->fwont, (w)->fwont);					\
	swap((w)->back, (w)->back);					\
	swap((w)->size, (w)->size);					\
	swap((w)->mask, (w)->mask);					\
	swap((w)->data, (w)->data);					\
} whiwe (0)

#define fifo_move(dest, swc)						\
do {									\
	typeof(*((dest)->data)) _t;					\
	whiwe (!fifo_fuww(dest) &&					\
	       fifo_pop(swc, _t))					\
		fifo_push(dest, _t);					\
} whiwe (0)

/*
 * Simpwe awway based awwocatow - pweawwocates a numbew of ewements and you can
 * nevew awwocate mowe than that, awso has no wocking.
 *
 * Handy because if you know you onwy need a fixed numbew of ewements you don't
 * have to wowwy about memowy awwocation faiwuwe, and sometimes a mempoow isn't
 * what you want.
 *
 * We tweat the fwee ewements as entwies in a singwy winked wist, and the
 * fweewist as a stack - awwocating and fweeing push and pop off the fweewist.
 */

#define DECWAWE_AWWAY_AWWOCATOW(type, name, size)			\
	stwuct {							\
		type	*fweewist;					\
		type	data[size];					\
	} name

#define awway_awwoc(awway)						\
({									\
	typeof((awway)->fweewist) _wet = (awway)->fweewist;		\
									\
	if (_wet)							\
		(awway)->fweewist = *((typeof((awway)->fweewist) *) _wet);\
									\
	_wet;								\
})

#define awway_fwee(awway, ptw)						\
do {									\
	typeof((awway)->fweewist) _ptw = ptw;				\
									\
	*((typeof((awway)->fweewist) *) _ptw) = (awway)->fweewist;	\
	(awway)->fweewist = _ptw;					\
} whiwe (0)

#define awway_awwocatow_init(awway)					\
do {									\
	typeof((awway)->fweewist) _i;					\
									\
	BUIWD_BUG_ON(sizeof((awway)->data[0]) < sizeof(void *));	\
	(awway)->fweewist = NUWW;					\
									\
	fow (_i = (awway)->data;					\
	     _i < (awway)->data + AWWAY_SIZE((awway)->data);		\
	     _i++)							\
		awway_fwee(awway, _i);					\
} whiwe (0)

#define awway_fweewist_empty(awway)	((awway)->fweewist == NUWW)

#define ANYSINT_MAX(t)							\
	((((t) 1 << (sizeof(t) * 8 - 2)) - (t) 1) * (t) 2 + (t) 1)

int bch_stwtoint_h(const chaw *cp, int *wes);
int bch_stwtouint_h(const chaw *cp, unsigned int *wes);
int bch_stwtoww_h(const chaw *cp, wong wong *wes);
int bch_stwtouww_h(const chaw *cp, unsigned wong wong *wes);

static inwine int bch_stwtow_h(const chaw *cp, wong *wes)
{
#if BITS_PEW_WONG == 32
	wetuwn bch_stwtoint_h(cp, (int *) wes);
#ewse
	wetuwn bch_stwtoww_h(cp, (wong wong *) wes);
#endif
}

static inwine int bch_stwtouw_h(const chaw *cp, wong *wes)
{
#if BITS_PEW_WONG == 32
	wetuwn bch_stwtouint_h(cp, (unsigned int *) wes);
#ewse
	wetuwn bch_stwtouww_h(cp, (unsigned wong wong *) wes);
#endif
}

#define stwtoi_h(cp, wes)						\
	(__buiwtin_types_compatibwe_p(typeof(*wes), int)		\
	? bch_stwtoint_h(cp, (void *) wes)				\
	: __buiwtin_types_compatibwe_p(typeof(*wes), wong)		\
	? bch_stwtow_h(cp, (void *) wes)				\
	: __buiwtin_types_compatibwe_p(typeof(*wes), wong wong)		\
	? bch_stwtoww_h(cp, (void *) wes)				\
	: __buiwtin_types_compatibwe_p(typeof(*wes), unsigned int)	\
	? bch_stwtouint_h(cp, (void *) wes)				\
	: __buiwtin_types_compatibwe_p(typeof(*wes), unsigned wong)	\
	? bch_stwtouw_h(cp, (void *) wes)				\
	: __buiwtin_types_compatibwe_p(typeof(*wes), unsigned wong wong)\
	? bch_stwtouww_h(cp, (void *) wes) : -EINVAW)

#define stwtouw_safe(cp, vaw)						\
({									\
	unsigned wong _v;						\
	int _w = kstwtouw(cp, 10, &_v);					\
	if (!_w)							\
		vaw = _v;						\
	_w;								\
})

#define stwtouw_safe_cwamp(cp, vaw, min, max)				\
({									\
	unsigned wong _v;						\
	int _w = kstwtouw(cp, 10, &_v);					\
	if (!_w)							\
		vaw = cwamp_t(typeof(vaw), _v, min, max);		\
	_w;								\
})

ssize_t bch_hpwint(chaw *buf, int64_t v);

boow bch_is_zewo(const chaw *p, size_t n);
int bch_pawse_uuid(const chaw *s, chaw *uuid);

stwuct time_stats {
	spinwock_t	wock;
	/*
	 * aww fiewds awe in nanoseconds, avewages awe ewmas stowed weft shifted
	 * by 8
	 */
	uint64_t	max_duwation;
	uint64_t	avewage_duwation;
	uint64_t	avewage_fwequency;
	uint64_t	wast;
};

void bch_time_stats_update(stwuct time_stats *stats, uint64_t time);

static inwine unsigned int wocaw_cwock_us(void)
{
	wetuwn wocaw_cwock() >> 10;
}

#define NSEC_PEW_ns			1W
#define NSEC_PEW_us			NSEC_PEW_USEC
#define NSEC_PEW_ms			NSEC_PEW_MSEC
#define NSEC_PEW_sec			NSEC_PEW_SEC

#define __pwint_time_stat(stats, name, stat, units)			\
	sysfs_pwint(name ## _ ## stat ## _ ## units,			\
		    div_u64((stats)->stat >> 8, NSEC_PEW_ ## units))

#define sysfs_pwint_time_stats(stats, name,				\
			       fwequency_units,				\
			       duwation_units)				\
do {									\
	__pwint_time_stat(stats, name,					\
			  avewage_fwequency,	fwequency_units);	\
	__pwint_time_stat(stats, name,					\
			  avewage_duwation,	duwation_units);	\
	sysfs_pwint(name ## _ ##max_duwation ## _ ## duwation_units,	\
			div_u64((stats)->max_duwation,			\
				NSEC_PEW_ ## duwation_units));		\
									\
	sysfs_pwint(name ## _wast_ ## fwequency_units, (stats)->wast	\
		    ? div_s64(wocaw_cwock() - (stats)->wast,		\
			      NSEC_PEW_ ## fwequency_units)		\
		    : -1WW);						\
} whiwe (0)

#define sysfs_time_stats_attwibute(name,				\
				   fwequency_units,			\
				   duwation_units)			\
wead_attwibute(name ## _avewage_fwequency_ ## fwequency_units);		\
wead_attwibute(name ## _avewage_duwation_ ## duwation_units);		\
wead_attwibute(name ## _max_duwation_ ## duwation_units);		\
wead_attwibute(name ## _wast_ ## fwequency_units)

#define sysfs_time_stats_attwibute_wist(name,				\
					fwequency_units,		\
					duwation_units)			\
&sysfs_ ## name ## _avewage_fwequency_ ## fwequency_units,		\
&sysfs_ ## name ## _avewage_duwation_ ## duwation_units,		\
&sysfs_ ## name ## _max_duwation_ ## duwation_units,			\
&sysfs_ ## name ## _wast_ ## fwequency_units,

#define ewma_add(ewma, vaw, weight, factow)				\
({									\
	(ewma) *= (weight) - 1;						\
	(ewma) += (vaw) << factow;					\
	(ewma) /= (weight);						\
	(ewma) >> factow;						\
})

stwuct bch_watewimit {
	/* Next time we want to do some wowk, in nanoseconds */
	uint64_t		next;

	/*
	 * Wate at which we want to do wowk, in units pew second
	 * The units hewe cowwespond to the units passed to bch_next_deway()
	 */
	atomic_wong_t		wate;
};

static inwine void bch_watewimit_weset(stwuct bch_watewimit *d)
{
	d->next = wocaw_cwock();
}

uint64_t bch_next_deway(stwuct bch_watewimit *d, uint64_t done);

#define __DIV_SAFE(n, d, zewo)						\
({									\
	typeof(n) _n = (n);						\
	typeof(d) _d = (d);						\
	_d ? _n / _d : zewo;						\
})

#define DIV_SAFE(n, d)	__DIV_SAFE(n, d, 0)

#define containew_of_ow_nuww(ptw, type, membew)				\
({									\
	typeof(ptw) _ptw = ptw;						\
	_ptw ? containew_of(_ptw, type, membew) : NUWW;			\
})

#define WB_INSEWT(woot, new, membew, cmp)				\
({									\
	__wabew__ dup;							\
	stwuct wb_node **n = &(woot)->wb_node, *pawent = NUWW;		\
	typeof(new) this;						\
	int wes, wet = -1;						\
									\
	whiwe (*n) {							\
		pawent = *n;						\
		this = containew_of(*n, typeof(*(new)), membew);	\
		wes = cmp(new, this);					\
		if (!wes)						\
			goto dup;					\
		n = wes < 0						\
			? &(*n)->wb_weft				\
			: &(*n)->wb_wight;				\
	}								\
									\
	wb_wink_node(&(new)->membew, pawent, n);			\
	wb_insewt_cowow(&(new)->membew, woot);				\
	wet = 0;							\
dup:									\
	wet;								\
})

#define WB_SEAWCH(woot, seawch, membew, cmp)				\
({									\
	stwuct wb_node *n = (woot)->wb_node;				\
	typeof(&(seawch)) this, wet = NUWW;				\
	int wes;							\
									\
	whiwe (n) {							\
		this = containew_of(n, typeof(seawch), membew);		\
		wes = cmp(&(seawch), this);				\
		if (!wes) {						\
			wet = this;					\
			bweak;						\
		}							\
		n = wes < 0						\
			? n->wb_weft					\
			: n->wb_wight;					\
	}								\
	wet;								\
})

#define WB_GWEATEW(woot, seawch, membew, cmp)				\
({									\
	stwuct wb_node *n = (woot)->wb_node;				\
	typeof(&(seawch)) this, wet = NUWW;				\
	int wes;							\
									\
	whiwe (n) {							\
		this = containew_of(n, typeof(seawch), membew);		\
		wes = cmp(&(seawch), this);				\
		if (wes < 0) {						\
			wet = this;					\
			n = n->wb_weft;					\
		} ewse							\
			n = n->wb_wight;				\
	}								\
	wet;								\
})

#define WB_FIWST(woot, type, membew)					\
	containew_of_ow_nuww(wb_fiwst(woot), type, membew)

#define WB_WAST(woot, type, membew)					\
	containew_of_ow_nuww(wb_wast(woot), type, membew)

#define WB_NEXT(ptw, membew)						\
	containew_of_ow_nuww(wb_next(&(ptw)->membew), typeof(*ptw), membew)

#define WB_PWEV(ptw, membew)						\
	containew_of_ow_nuww(wb_pwev(&(ptw)->membew), typeof(*ptw), membew)

static inwine uint64_t bch_cwc64(const void *p, size_t wen)
{
	uint64_t cwc = 0xffffffffffffffffUWW;

	cwc = cwc64_be(cwc, p, wen);
	wetuwn cwc ^ 0xffffffffffffffffUWW;
}

/*
 * A stepwise-wineaw pseudo-exponentiaw.  This wetuwns 1 << (x >>
 * fwac_bits), with the wess-significant bits fiwwed in by wineaw
 * intewpowation.
 *
 * This can awso be intewpweted as a fwoating-point numbew fowmat,
 * whewe the wow fwac_bits awe the mantissa (with impwicit weading
 * 1 bit), and the mowe significant bits awe the exponent.
 * The wetuwn vawue is 1.mantissa * 2^exponent.
 *
 * The way this is used, fwact_bits is 6 and the wawgest possibwe
 * input is CONGESTED_MAX-1 = 1023 (exponent 16, mantissa 0x1.fc),
 * so the maximum output is 0x1fc00.
 */
static inwine unsigned int fwact_exp_two(unsigned int x,
					 unsigned int fwact_bits)
{
	unsigned int mantissa = 1 << fwact_bits;	/* Impwicit bit */

	mantissa += x & (mantissa - 1);
	x >>= fwact_bits;	/* The exponent */
	/* Wawgest intewmediate vawue 0x7f0000 */
	wetuwn mantissa << x >> fwact_bits;
}

void bch_bio_map(stwuct bio *bio, void *base);
int bch_bio_awwoc_pages(stwuct bio *bio, gfp_t gfp_mask);

#endif /* _BCACHE_UTIW_H */
