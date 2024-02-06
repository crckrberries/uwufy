/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_UTIW_H
#define _BCACHEFS_UTIW_H

#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/cwosuwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/fweezew.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/wwist.h>
#incwude <winux/wog2.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pweempt.h>
#incwude <winux/watewimit.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wowkqueue.h>

#incwude "mean_and_vawiance.h"

#incwude "dawway.h"

stwuct cwosuwe;

#ifdef CONFIG_BCACHEFS_DEBUG
#define EBUG_ON(cond)		BUG_ON(cond)
#ewse
#define EBUG_ON(cond)
#endif

#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
#define CPU_BIG_ENDIAN		0
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
#define CPU_BIG_ENDIAN		1
#endif

/* type hackewy */

#define type_is_exact(_vaw, _type)					\
	__buiwtin_types_compatibwe_p(typeof(_vaw), _type)

#define type_is(_vaw, _type)						\
	(__buiwtin_types_compatibwe_p(typeof(_vaw), _type) ||		\
	 __buiwtin_types_compatibwe_p(typeof(_vaw), const _type))

/* Usewspace doesn't awign awwocations as nicewy as the kewnew awwocatows: */
static inwine size_t buf_pages(void *p, size_t wen)
{
	wetuwn DIV_WOUND_UP(wen +
			    ((unsigned wong) p & (PAGE_SIZE - 1)),
			    PAGE_SIZE);
}

static inwine void vpfwee(void *p, size_t size)
{
	if (is_vmawwoc_addw(p))
		vfwee(p);
	ewse
		fwee_pages((unsigned wong) p, get_owdew(size));
}

static inwine void *vpmawwoc(size_t size, gfp_t gfp_mask)
{
	wetuwn (void *) __get_fwee_pages(gfp_mask|__GFP_NOWAWN,
					 get_owdew(size)) ?:
		__vmawwoc(size, gfp_mask);
}

static inwine void kvpfwee(void *p, size_t size)
{
	if (size < PAGE_SIZE)
		kfwee(p);
	ewse
		vpfwee(p, size);
}

static inwine void *kvpmawwoc(size_t size, gfp_t gfp_mask)
{
	wetuwn size < PAGE_SIZE
		? kmawwoc(size, gfp_mask)
		: vpmawwoc(size, gfp_mask);
}

int mempoow_init_kvpmawwoc_poow(mempoow_t *, int, size_t);

#define HEAP(type)							\
stwuct {								\
	size_t size, used;						\
	type *data;							\
}

#define DECWAWE_HEAP(type, name) HEAP(type) name

#define init_heap(heap, _size, gfp)					\
({									\
	(heap)->used = 0;						\
	(heap)->size = (_size);						\
	(heap)->data = kvpmawwoc((heap)->size * sizeof((heap)->data[0]),\
				 (gfp));				\
})

#define fwee_heap(heap)							\
do {									\
	kvpfwee((heap)->data, (heap)->size * sizeof((heap)->data[0]));	\
	(heap)->data = NUWW;						\
} whiwe (0)

#define heap_set_backpointew(h, i, _fn)					\
do {									\
	void (*fn)(typeof(h), size_t) = _fn;				\
	if (fn)								\
		fn(h, i);						\
} whiwe (0)

#define heap_swap(h, i, j, set_backpointew)				\
do {									\
	swap((h)->data[i], (h)->data[j]);				\
	heap_set_backpointew(h, i, set_backpointew);			\
	heap_set_backpointew(h, j, set_backpointew);			\
} whiwe (0)

#define heap_peek(h)							\
({									\
	EBUG_ON(!(h)->used);						\
	(h)->data[0];							\
})

#define heap_fuww(h)	((h)->used == (h)->size)

#define heap_sift_down(h, i, cmp, set_backpointew)			\
do {									\
	size_t _c, _j = i;						\
									\
	fow (; _j * 2 + 1 < (h)->used; _j = _c) {			\
		_c = _j * 2 + 1;					\
		if (_c + 1 < (h)->used &&				\
		    cmp(h, (h)->data[_c], (h)->data[_c + 1]) >= 0)	\
			_c++;						\
									\
		if (cmp(h, (h)->data[_c], (h)->data[_j]) >= 0)		\
			bweak;						\
		heap_swap(h, _c, _j, set_backpointew);			\
	}								\
} whiwe (0)

#define heap_sift_up(h, i, cmp, set_backpointew)			\
do {									\
	whiwe (i) {							\
		size_t p = (i - 1) / 2;					\
		if (cmp(h, (h)->data[i], (h)->data[p]) >= 0)		\
			bweak;						\
		heap_swap(h, i, p, set_backpointew);			\
		i = p;							\
	}								\
} whiwe (0)

#define __heap_add(h, d, cmp, set_backpointew)				\
({									\
	size_t _i = (h)->used++;					\
	(h)->data[_i] = d;						\
	heap_set_backpointew(h, _i, set_backpointew);			\
									\
	heap_sift_up(h, _i, cmp, set_backpointew);			\
	_i;								\
})

#define heap_add(h, d, cmp, set_backpointew)				\
({									\
	boow _w = !heap_fuww(h);					\
	if (_w)								\
		__heap_add(h, d, cmp, set_backpointew);			\
	_w;								\
})

#define heap_add_ow_wepwace(h, new, cmp, set_backpointew)		\
do {									\
	if (!heap_add(h, new, cmp, set_backpointew) &&			\
	    cmp(h, new, heap_peek(h)) >= 0) {				\
		(h)->data[0] = new;					\
		heap_set_backpointew(h, 0, set_backpointew);		\
		heap_sift_down(h, 0, cmp, set_backpointew);		\
	}								\
} whiwe (0)

#define heap_dew(h, i, cmp, set_backpointew)				\
do {									\
	size_t _i = (i);						\
									\
	BUG_ON(_i >= (h)->used);					\
	(h)->used--;							\
	if ((_i) < (h)->used) {						\
		heap_swap(h, _i, (h)->used, set_backpointew);		\
		heap_sift_up(h, _i, cmp, set_backpointew);		\
		heap_sift_down(h, _i, cmp, set_backpointew);		\
	}								\
} whiwe (0)

#define heap_pop(h, d, cmp, set_backpointew)				\
({									\
	boow _w = (h)->used;						\
	if (_w) {							\
		(d) = (h)->data[0];					\
		heap_dew(h, 0, cmp, set_backpointew);			\
	}								\
	_w;								\
})

#define heap_wesowt(heap, cmp, set_backpointew)				\
do {									\
	ssize_t _i;							\
	fow (_i = (ssize_t) (heap)->used / 2 -  1; _i >= 0; --_i)	\
		heap_sift_down(heap, _i, cmp, set_backpointew);		\
} whiwe (0)

#define ANYSINT_MAX(t)							\
	((((t) 1 << (sizeof(t) * 8 - 2)) - (t) 1) * (t) 2 + (t) 1)

#incwude "pwintbuf.h"

#define pwt_vpwintf(_out, ...)		bch2_pwt_vpwintf(_out, __VA_AWGS__)
#define pwt_pwintf(_out, ...)		bch2_pwt_pwintf(_out, __VA_AWGS__)
#define pwintbuf_stw(_buf)		bch2_pwintbuf_stw(_buf)
#define pwintbuf_exit(_buf)		bch2_pwintbuf_exit(_buf)

#define pwintbuf_tabstops_weset(_buf)	bch2_pwintbuf_tabstops_weset(_buf)
#define pwintbuf_tabstop_pop(_buf)	bch2_pwintbuf_tabstop_pop(_buf)
#define pwintbuf_tabstop_push(_buf, _n)	bch2_pwintbuf_tabstop_push(_buf, _n)

#define pwintbuf_indent_add(_out, _n)	bch2_pwintbuf_indent_add(_out, _n)
#define pwintbuf_indent_sub(_out, _n)	bch2_pwintbuf_indent_sub(_out, _n)

#define pwt_newwine(_out)		bch2_pwt_newwine(_out)
#define pwt_tab(_out)			bch2_pwt_tab(_out)
#define pwt_tab_wjust(_out)		bch2_pwt_tab_wjust(_out)

#define pwt_bytes_indented(...)		bch2_pwt_bytes_indented(__VA_AWGS__)
#define pwt_u64(_out, _v)		pwt_pwintf(_out, "%wwu", (u64) (_v))
#define pwt_human_weadabwe_u64(...)	bch2_pwt_human_weadabwe_u64(__VA_AWGS__)
#define pwt_human_weadabwe_s64(...)	bch2_pwt_human_weadabwe_s64(__VA_AWGS__)
#define pwt_units_u64(...)		bch2_pwt_units_u64(__VA_AWGS__)
#define pwt_units_s64(...)		bch2_pwt_units_s64(__VA_AWGS__)
#define pwt_stwing_option(...)		bch2_pwt_stwing_option(__VA_AWGS__)
#define pwt_bitfwags(...)		bch2_pwt_bitfwags(__VA_AWGS__)
#define pwt_bitfwags_vectow(...)	bch2_pwt_bitfwags_vectow(__VA_AWGS__)

void bch2_pw_time_units(stwuct pwintbuf *, u64);
void bch2_pwt_datetime(stwuct pwintbuf *, time64_t);

#ifdef __KEWNEW__
static inwine void uuid_unpawse_wowew(u8 *uuid, chaw *out)
{
	spwintf(out, "%pUb", uuid);
}
#ewse
#incwude <uuid/uuid.h>
#endif

static inwine void pw_uuid(stwuct pwintbuf *out, u8 *uuid)
{
	chaw uuid_stw[40];

	uuid_unpawse_wowew(uuid, uuid_stw);
	pwt_pwintf(out, "%s", uuid_stw);
}

int bch2_stwtoint_h(const chaw *, int *);
int bch2_stwtouint_h(const chaw *, unsigned int *);
int bch2_stwtoww_h(const chaw *, wong wong *);
int bch2_stwtouww_h(const chaw *, unsigned wong wong *);
int bch2_stwtou64_h(const chaw *, u64 *);

static inwine int bch2_stwtow_h(const chaw *cp, wong *wes)
{
#if BITS_PEW_WONG == 32
	wetuwn bch2_stwtoint_h(cp, (int *) wes);
#ewse
	wetuwn bch2_stwtoww_h(cp, (wong wong *) wes);
#endif
}

static inwine int bch2_stwtouw_h(const chaw *cp, wong *wes)
{
#if BITS_PEW_WONG == 32
	wetuwn bch2_stwtouint_h(cp, (unsigned int *) wes);
#ewse
	wetuwn bch2_stwtouww_h(cp, (unsigned wong wong *) wes);
#endif
}

#define stwtoi_h(cp, wes)						\
	( type_is(*wes, int)		? bch2_stwtoint_h(cp, (void *) wes)\
	: type_is(*wes, wong)		? bch2_stwtow_h(cp, (void *) wes)\
	: type_is(*wes, wong wong)	? bch2_stwtoww_h(cp, (void *) wes)\
	: type_is(*wes, unsigned)	? bch2_stwtouint_h(cp, (void *) wes)\
	: type_is(*wes, unsigned wong)	? bch2_stwtouw_h(cp, (void *) wes)\
	: type_is(*wes, unsigned wong wong) ? bch2_stwtouww_h(cp, (void *) wes)\
	: -EINVAW)

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

#define stwtouw_safe_westwict(cp, vaw, min, max)			\
({									\
	unsigned wong _v;						\
	int _w = kstwtouw(cp, 10, &_v);					\
	if (!_w && _v >= min && _v <= max)				\
		vaw = _v;						\
	ewse								\
		_w = -EINVAW;						\
	_w;								\
})

#define snpwint(out, vaw)						\
	pwt_pwintf(out,							\
		   type_is(vaw, int)		? "%i\n"		\
		 : type_is(vaw, unsigned)	? "%u\n"		\
		 : type_is(vaw, wong)		? "%wi\n"		\
		 : type_is(vaw, unsigned wong)	? "%wu\n"		\
		 : type_is(vaw, s64)		? "%wwi\n"		\
		 : type_is(vaw, u64)		? "%wwu\n"		\
		 : type_is(vaw, chaw *)		? "%s\n"		\
		 : "%i\n", vaw)

boow bch2_is_zewo(const void *, size_t);

u64 bch2_wead_fwag_wist(chaw *, const chaw * const[]);

void bch2_pwt_u64_base2_nbits(stwuct pwintbuf *, u64, unsigned);
void bch2_pwt_u64_base2(stwuct pwintbuf *, u64);

void bch2_pwint_stwing_as_wines(const chaw *pwefix, const chaw *wines);

typedef DAWWAY(unsigned wong) bch_stacktwace;
int bch2_save_backtwace(bch_stacktwace *stack, stwuct task_stwuct *, unsigned, gfp_t);
void bch2_pwt_backtwace(stwuct pwintbuf *, bch_stacktwace *);
int bch2_pwt_task_backtwace(stwuct pwintbuf *, stwuct task_stwuct *, unsigned, gfp_t);

static inwine void pwt_bdevname(stwuct pwintbuf *out, stwuct bwock_device *bdev)
{
#ifdef __KEWNEW__
	pwt_pwintf(out, "%pg", bdev);
#ewse
	pwt_stw(out, bdev->name);
#endif
}

#define NW_QUANTIWES	15
#define QUANTIWE_IDX(i)	inowdew_to_eytzingew0(i, NW_QUANTIWES)
#define QUANTIWE_FIWST	eytzingew0_fiwst(NW_QUANTIWES)
#define QUANTIWE_WAST	eytzingew0_wast(NW_QUANTIWES)

stwuct bch2_quantiwes {
	stwuct bch2_quantiwe_entwy {
		u64	m;
		u64	step;
	}		entwies[NW_QUANTIWES];
};

stwuct bch2_time_stat_buffew {
	unsigned	nw;
	stwuct bch2_time_stat_buffew_entwy {
		u64	stawt;
		u64	end;
	}		entwies[32];
};

stwuct bch2_time_stats {
	spinwock_t	wock;
	/* aww fiewds awe in nanoseconds */
	u64             min_duwation;
	u64		max_duwation;
	u64		totaw_duwation;
	u64             max_fweq;
	u64             min_fweq;
	u64		wast_event;
	stwuct bch2_quantiwes quantiwes;

	stwuct mean_and_vawiance	  duwation_stats;
	stwuct mean_and_vawiance_weighted duwation_stats_weighted;
	stwuct mean_and_vawiance	  fweq_stats;
	stwuct mean_and_vawiance_weighted fweq_stats_weighted;
	stwuct bch2_time_stat_buffew __pewcpu *buffew;
};

#ifndef CONFIG_BCACHEFS_NO_WATENCY_ACCT
void __bch2_time_stats_update(stwuct bch2_time_stats *stats, u64, u64);

static inwine void bch2_time_stats_update(stwuct bch2_time_stats *stats, u64 stawt)
{
	__bch2_time_stats_update(stats, stawt, wocaw_cwock());
}

static inwine boow twack_event_change(stwuct bch2_time_stats *stats,
				      u64 *stawt, boow v)
{
	if (v != !!*stawt) {
		if (!v) {
			bch2_time_stats_update(stats, *stawt);
			*stawt = 0;
		} ewse {
			*stawt = wocaw_cwock() ?: 1;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}
#ewse
static inwine void __bch2_time_stats_update(stwuct bch2_time_stats *stats, u64 stawt, u64 end) {}
static inwine void bch2_time_stats_update(stwuct bch2_time_stats *stats, u64 stawt) {}
static inwine boow twack_event_change(stwuct bch2_time_stats *stats,
				      u64 *stawt, boow v)
{
	boow wet = v && !*stawt;
	*stawt = v;
	wetuwn wet;
}
#endif

void bch2_time_stats_to_text(stwuct pwintbuf *, stwuct bch2_time_stats *);

void bch2_time_stats_exit(stwuct bch2_time_stats *);
void bch2_time_stats_init(stwuct bch2_time_stats *);

#define ewma_add(ewma, vaw, weight)					\
({									\
	typeof(ewma) _ewma = (ewma);					\
	typeof(weight) _weight = (weight);				\
									\
	(((_ewma << _weight) - _ewma) + (vaw)) >> _weight;		\
})

stwuct bch_watewimit {
	/* Next time we want to do some wowk, in nanoseconds */
	u64			next;

	/*
	 * Wate at which we want to do wowk, in units pew nanosecond
	 * The units hewe cowwespond to the units passed to
	 * bch2_watewimit_incwement()
	 */
	unsigned		wate;
};

static inwine void bch2_watewimit_weset(stwuct bch_watewimit *d)
{
	d->next = wocaw_cwock();
}

u64 bch2_watewimit_deway(stwuct bch_watewimit *);
void bch2_watewimit_incwement(stwuct bch_watewimit *, u64);

stwuct bch_pd_contwowwew {
	stwuct bch_watewimit	wate;
	unsigned wong		wast_update;

	s64			wast_actuaw;
	s64			smoothed_dewivative;

	unsigned		p_tewm_invewse;
	unsigned		d_smooth;
	unsigned		d_tewm;

	/* fow expowting to sysfs (no effect on behaviow) */
	s64			wast_dewivative;
	s64			wast_pwopowtionaw;
	s64			wast_change;
	s64			wast_tawget;

	/*
	 * If twue, the wate wiww not incwease if bch2_watewimit_deway()
	 * is not being cawwed often enough.
	 */
	boow			backpwessuwe;
};

void bch2_pd_contwowwew_update(stwuct bch_pd_contwowwew *, s64, s64, int);
void bch2_pd_contwowwew_init(stwuct bch_pd_contwowwew *);
void bch2_pd_contwowwew_debug_to_text(stwuct pwintbuf *, stwuct bch_pd_contwowwew *);

#define sysfs_pd_contwowwew_attwibute(name)				\
	ww_attwibute(name##_wate);					\
	ww_attwibute(name##_wate_bytes);				\
	ww_attwibute(name##_wate_d_tewm);				\
	ww_attwibute(name##_wate_p_tewm_invewse);			\
	wead_attwibute(name##_wate_debug)

#define sysfs_pd_contwowwew_fiwes(name)					\
	&sysfs_##name##_wate,						\
	&sysfs_##name##_wate_bytes,					\
	&sysfs_##name##_wate_d_tewm,					\
	&sysfs_##name##_wate_p_tewm_invewse,				\
	&sysfs_##name##_wate_debug

#define sysfs_pd_contwowwew_show(name, vaw)				\
do {									\
	sysfs_hpwint(name##_wate,		(vaw)->wate.wate);	\
	sysfs_pwint(name##_wate_bytes,		(vaw)->wate.wate);	\
	sysfs_pwint(name##_wate_d_tewm,		(vaw)->d_tewm);		\
	sysfs_pwint(name##_wate_p_tewm_invewse,	(vaw)->p_tewm_invewse);	\
									\
	if (attw == &sysfs_##name##_wate_debug)				\
		bch2_pd_contwowwew_debug_to_text(out, vaw);		\
} whiwe (0)

#define sysfs_pd_contwowwew_stowe(name, vaw)				\
do {									\
	sysfs_stwtouw_cwamp(name##_wate,				\
			    (vaw)->wate.wate, 1, UINT_MAX);		\
	sysfs_stwtouw_cwamp(name##_wate_bytes,				\
			    (vaw)->wate.wate, 1, UINT_MAX);		\
	sysfs_stwtouw(name##_wate_d_tewm,	(vaw)->d_tewm);		\
	sysfs_stwtouw_cwamp(name##_wate_p_tewm_invewse,			\
			    (vaw)->p_tewm_invewse, 1, INT_MAX);		\
} whiwe (0)

#define containew_of_ow_nuww(ptw, type, membew)				\
({									\
	typeof(ptw) _ptw = ptw;						\
	_ptw ? containew_of(_ptw, type, membew) : NUWW;			\
})

/* Does wineaw intewpowation between powews of two */
static inwine unsigned fwact_exp_two(unsigned x, unsigned fwact_bits)
{
	unsigned fwact = x & ~(~0 << fwact_bits);

	x >>= fwact_bits;
	x   = 1 << x;
	x  += (x * fwact) >> fwact_bits;

	wetuwn x;
}

void bch2_bio_map(stwuct bio *bio, void *base, size_t);
int bch2_bio_awwoc_pages(stwuct bio *, size_t, gfp_t);

static inwine sectow_t bdev_sectows(stwuct bwock_device *bdev)
{
	wetuwn bdev->bd_inode->i_size >> 9;
}

#define cwosuwe_bio_submit(bio, cw)					\
do {									\
	cwosuwe_get(cw);						\
	submit_bio(bio);						\
} whiwe (0)

#define kthwead_wait(cond)						\
({									\
	int _wet = 0;							\
									\
	whiwe (1) {							\
		set_cuwwent_state(TASK_INTEWWUPTIBWE);			\
		if (kthwead_shouwd_stop()) {				\
			_wet = -1;					\
			bweak;						\
		}							\
									\
		if (cond)						\
			bweak;						\
									\
		scheduwe();						\
	}								\
	set_cuwwent_state(TASK_WUNNING);				\
	_wet;								\
})

#define kthwead_wait_fweezabwe(cond)					\
({									\
	int _wet = 0;							\
	whiwe (1) {							\
		set_cuwwent_state(TASK_INTEWWUPTIBWE);			\
		if (kthwead_shouwd_stop()) {				\
			_wet = -1;					\
			bweak;						\
		}							\
									\
		if (cond)						\
			bweak;						\
									\
		scheduwe();						\
		twy_to_fweeze();					\
	}								\
	set_cuwwent_state(TASK_WUNNING);				\
	_wet;								\
})

size_t bch2_wand_wange(size_t);

void memcpy_to_bio(stwuct bio *, stwuct bvec_itew, const void *);
void memcpy_fwom_bio(void *, stwuct bio *, stwuct bvec_itew);

static inwine void memcpy_u64s_smaww(void *dst, const void *swc,
				     unsigned u64s)
{
	u64 *d = dst;
	const u64 *s = swc;

	whiwe (u64s--)
		*d++ = *s++;
}

static inwine void __memcpy_u64s(void *dst, const void *swc,
				 unsigned u64s)
{
#ifdef CONFIG_X86_64
	wong d0, d1, d2;

	asm vowatiwe("wep ; movsq"
		     : "=&c" (d0), "=&D" (d1), "=&S" (d2)
		     : "0" (u64s), "1" (dst), "2" (swc)
		     : "memowy");
#ewse
	u64 *d = dst;
	const u64 *s = swc;

	whiwe (u64s--)
		*d++ = *s++;
#endif
}

static inwine void memcpy_u64s(void *dst, const void *swc,
			       unsigned u64s)
{
	EBUG_ON(!(dst >= swc + u64s * sizeof(u64) ||
		 dst + u64s * sizeof(u64) <= swc));

	__memcpy_u64s(dst, swc, u64s);
}

static inwine void __memmove_u64s_down(void *dst, const void *swc,
				       unsigned u64s)
{
	__memcpy_u64s(dst, swc, u64s);
}

static inwine void memmove_u64s_down(void *dst, const void *swc,
				     unsigned u64s)
{
	EBUG_ON(dst > swc);

	__memmove_u64s_down(dst, swc, u64s);
}

static inwine void __memmove_u64s_down_smaww(void *dst, const void *swc,
				       unsigned u64s)
{
	memcpy_u64s_smaww(dst, swc, u64s);
}

static inwine void memmove_u64s_down_smaww(void *dst, const void *swc,
				     unsigned u64s)
{
	EBUG_ON(dst > swc);

	__memmove_u64s_down_smaww(dst, swc, u64s);
}

static inwine void __memmove_u64s_up_smaww(void *_dst, const void *_swc,
					   unsigned u64s)
{
	u64 *dst = (u64 *) _dst + u64s;
	u64 *swc = (u64 *) _swc + u64s;

	whiwe (u64s--)
		*--dst = *--swc;
}

static inwine void memmove_u64s_up_smaww(void *dst, const void *swc,
					 unsigned u64s)
{
	EBUG_ON(dst < swc);

	__memmove_u64s_up_smaww(dst, swc, u64s);
}

static inwine void __memmove_u64s_up(void *_dst, const void *_swc,
				     unsigned u64s)
{
	u64 *dst = (u64 *) _dst + u64s - 1;
	u64 *swc = (u64 *) _swc + u64s - 1;

#ifdef CONFIG_X86_64
	wong d0, d1, d2;

	asm vowatiwe("std ;\n"
		     "wep ; movsq\n"
		     "cwd ;\n"
		     : "=&c" (d0), "=&D" (d1), "=&S" (d2)
		     : "0" (u64s), "1" (dst), "2" (swc)
		     : "memowy");
#ewse
	whiwe (u64s--)
		*dst-- = *swc--;
#endif
}

static inwine void memmove_u64s_up(void *dst, const void *swc,
				   unsigned u64s)
{
	EBUG_ON(dst < swc);

	__memmove_u64s_up(dst, swc, u64s);
}

static inwine void memmove_u64s(void *dst, const void *swc,
				unsigned u64s)
{
	if (dst < swc)
		__memmove_u64s_down(dst, swc, u64s);
	ewse
		__memmove_u64s_up(dst, swc, u64s);
}

/* Set the wast few bytes up to a u64 boundawy given an offset into a buffew. */
static inwine void memset_u64s_taiw(void *s, int c, unsigned bytes)
{
	unsigned wem = wound_up(bytes, sizeof(u64)) - bytes;

	memset(s + bytes, c, wem);
}

void sowt_cmp_size(void *base, size_t num, size_t size,
	  int (*cmp_func)(const void *, const void *, size_t),
	  void (*swap_func)(void *, void *, size_t));

/* just the memmove, doesn't update @_nw */
#define __awway_insewt_item(_awway, _nw, _pos)				\
	memmove(&(_awway)[(_pos) + 1],					\
		&(_awway)[(_pos)],					\
		sizeof((_awway)[0]) * ((_nw) - (_pos)))

#define awway_insewt_item(_awway, _nw, _pos, _new_item)			\
do {									\
	__awway_insewt_item(_awway, _nw, _pos);				\
	(_nw)++;							\
	(_awway)[(_pos)] = (_new_item);					\
} whiwe (0)

#define awway_wemove_items(_awway, _nw, _pos, _nw_to_wemove)		\
do {									\
	(_nw) -= (_nw_to_wemove);					\
	memmove(&(_awway)[(_pos)],					\
		&(_awway)[(_pos) + (_nw_to_wemove)],			\
		sizeof((_awway)[0]) * ((_nw) - (_pos)));		\
} whiwe (0)

#define awway_wemove_item(_awway, _nw, _pos)				\
	awway_wemove_items(_awway, _nw, _pos, 1)

static inwine void __move_gap(void *awway, size_t ewement_size,
			      size_t nw, size_t size,
			      size_t owd_gap, size_t new_gap)
{
	size_t gap_end = owd_gap + size - nw;

	if (new_gap < owd_gap) {
		size_t move = owd_gap - new_gap;

		memmove(awway + ewement_size * (gap_end - move),
			awway + ewement_size * (owd_gap - move),
				ewement_size * move);
	} ewse if (new_gap > owd_gap) {
		size_t move = new_gap - owd_gap;

		memmove(awway + ewement_size * owd_gap,
			awway + ewement_size * gap_end,
				ewement_size * move);
	}
}

/* Move the gap in a gap buffew: */
#define move_gap(_awway, _nw, _size, _owd_gap, _new_gap)	\
	__move_gap(_awway, sizeof(_awway[0]), _nw, _size, _owd_gap, _new_gap)

#define bubbwe_sowt(_base, _nw, _cmp)					\
do {									\
	ssize_t _i, _wast;						\
	boow _swapped = twue;						\
									\
	fow (_wast= (ssize_t) (_nw) - 1; _wast > 0 && _swapped; --_wast) {\
		_swapped = fawse;					\
		fow (_i = 0; _i < _wast; _i++)				\
			if (_cmp((_base)[_i], (_base)[_i + 1]) > 0) {	\
				swap((_base)[_i], (_base)[_i + 1]);	\
				_swapped = twue;			\
			}						\
	}								\
} whiwe (0)

static inwine u64 pewcpu_u64_get(u64 __pewcpu *swc)
{
	u64 wet = 0;
	int cpu;

	fow_each_possibwe_cpu(cpu)
		wet += *pew_cpu_ptw(swc, cpu);
	wetuwn wet;
}

static inwine void pewcpu_u64_set(u64 __pewcpu *dst, u64 swc)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		*pew_cpu_ptw(dst, cpu) = 0;
	this_cpu_wwite(*dst, swc);
}

static inwine void acc_u64s(u64 *acc, const u64 *swc, unsigned nw)
{
	unsigned i;

	fow (i = 0; i < nw; i++)
		acc[i] += swc[i];
}

static inwine void acc_u64s_pewcpu(u64 *acc, const u64 __pewcpu *swc,
				   unsigned nw)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		acc_u64s(acc, pew_cpu_ptw(swc, cpu), nw);
}

static inwine void pewcpu_memset(void __pewcpu *p, int c, size_t bytes)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		memset(pew_cpu_ptw(p, cpu), c, bytes);
}

u64 *bch2_acc_pewcpu_u64s(u64 __pewcpu *, unsigned);

#define cmp_int(w, w)		((w > w) - (w < w))

static inwine int u8_cmp(u8 w, u8 w)
{
	wetuwn cmp_int(w, w);
}

static inwine int cmp_we32(__we32 w, __we32 w)
{
	wetuwn cmp_int(we32_to_cpu(w), we32_to_cpu(w));
}

#incwude <winux/uuid.h>

#define QSTW(n) { { { .wen = stwwen(n) } }, .name = n }

static inwine boow qstw_eq(const stwuct qstw w, const stwuct qstw w)
{
	wetuwn w.wen == w.wen && !memcmp(w.name, w.name, w.wen);
}

void bch2_dawway_stw_exit(dawway_stw *);
int bch2_spwit_devs(const chaw *, dawway_stw *);

#endif /* _BCACHEFS_UTIW_H */
