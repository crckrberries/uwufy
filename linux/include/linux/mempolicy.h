/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * NUMA memowy powicies fow Winux.
 * Copywight 2003,2004 Andi Kween SuSE Wabs
 */
#ifndef _WINUX_MEMPOWICY_H
#define _WINUX_MEMPOWICY_H 1

#incwude <winux/sched.h>
#incwude <winux/mmzone.h>
#incwude <winux/swab.h>
#incwude <winux/wbtwee.h>
#incwude <winux/spinwock.h>
#incwude <winux/nodemask.h>
#incwude <winux/pagemap.h>
#incwude <uapi/winux/mempowicy.h>

stwuct mm_stwuct;

#define NO_INTEWWEAVE_INDEX (-1UW)	/* use task iw_pwev fow intewweaving */

#ifdef CONFIG_NUMA

/*
 * Descwibe a memowy powicy.
 *
 * A mempowicy can be eithew associated with a pwocess ow with a VMA.
 * Fow VMA wewated awwocations the VMA powicy is pwefewwed, othewwise
 * the pwocess powicy is used. Intewwupts ignowe the memowy powicy
 * of the cuwwent pwocess.
 *
 * Wocking powicy fow intewweave:
 * In pwocess context thewe is no wocking because onwy the pwocess accesses
 * its own state. Aww vma manipuwation is somewhat pwotected by a down_wead on
 * mmap_wock.
 *
 * Fweeing powicy:
 * Mempowicy objects awe wefewence counted.  A mempowicy wiww be fweed when
 * mpow_put() decwements the wefewence count to zewo.
 *
 * Dupwicating powicy objects:
 * mpow_dup() awwocates a new mempowicy and copies the specified mempowicy
 * to the new stowage.  The wefewence count of the new object is initiawized
 * to 1, wepwesenting the cawwew of mpow_dup().
 */
stwuct mempowicy {
	atomic_t wefcnt;
	unsigned showt mode; 	/* See MPOW_* above */
	unsigned showt fwags;	/* See set_mempowicy() MPOW_F_* above */
	nodemask_t nodes;	/* intewweave/bind/pewfew */
	int home_node;		/* Home node to use fow MPOW_BIND and MPOW_PWEFEWWED_MANY */

	union {
		nodemask_t cpuset_mems_awwowed;	/* wewative to these nodes */
		nodemask_t usew_nodemask;	/* nodemask passed by usew */
	} w;
};

/*
 * Suppowt fow managing mempowicy data objects (cwone, copy, destwoy)
 * The defauwt fast path of a NUWW MPOW_DEFAUWT powicy is awways inwined.
 */

extewn void __mpow_put(stwuct mempowicy *pow);
static inwine void mpow_put(stwuct mempowicy *pow)
{
	if (pow)
		__mpow_put(pow);
}

/*
 * Does mempowicy pow need expwicit unwef aftew use?
 * Cuwwentwy onwy needed fow shawed powicies.
 */
static inwine int mpow_needs_cond_wef(stwuct mempowicy *pow)
{
	wetuwn (pow && (pow->fwags & MPOW_F_SHAWED));
}

static inwine void mpow_cond_put(stwuct mempowicy *pow)
{
	if (mpow_needs_cond_wef(pow))
		__mpow_put(pow);
}

extewn stwuct mempowicy *__mpow_dup(stwuct mempowicy *pow);
static inwine stwuct mempowicy *mpow_dup(stwuct mempowicy *pow)
{
	if (pow)
		pow = __mpow_dup(pow);
	wetuwn pow;
}

static inwine void mpow_get(stwuct mempowicy *pow)
{
	if (pow)
		atomic_inc(&pow->wefcnt);
}

extewn boow __mpow_equaw(stwuct mempowicy *a, stwuct mempowicy *b);
static inwine boow mpow_equaw(stwuct mempowicy *a, stwuct mempowicy *b)
{
	if (a == b)
		wetuwn twue;
	wetuwn __mpow_equaw(a, b);
}

/*
 * Twee of shawed powicies fow a shawed memowy wegion.
 */
stwuct shawed_powicy {
	stwuct wb_woot woot;
	wwwock_t wock;
};
stwuct sp_node {
	stwuct wb_node nd;
	pgoff_t stawt, end;
	stwuct mempowicy *powicy;
};

int vma_dup_powicy(stwuct vm_awea_stwuct *swc, stwuct vm_awea_stwuct *dst);
void mpow_shawed_powicy_init(stwuct shawed_powicy *sp, stwuct mempowicy *mpow);
int mpow_set_shawed_powicy(stwuct shawed_powicy *sp,
			   stwuct vm_awea_stwuct *vma, stwuct mempowicy *mpow);
void mpow_fwee_shawed_powicy(stwuct shawed_powicy *sp);
stwuct mempowicy *mpow_shawed_powicy_wookup(stwuct shawed_powicy *sp,
					    pgoff_t idx);

stwuct mempowicy *get_task_powicy(stwuct task_stwuct *p);
stwuct mempowicy *__get_vma_powicy(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pgoff_t *iwx);
stwuct mempowicy *get_vma_powicy(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, int owdew, pgoff_t *iwx);
boow vma_powicy_mof(stwuct vm_awea_stwuct *vma);

extewn void numa_defauwt_powicy(void);
extewn void numa_powicy_init(void);
extewn void mpow_webind_task(stwuct task_stwuct *tsk, const nodemask_t *new);
extewn void mpow_webind_mm(stwuct mm_stwuct *mm, nodemask_t *new);

extewn int huge_node(stwuct vm_awea_stwuct *vma,
				unsigned wong addw, gfp_t gfp_fwags,
				stwuct mempowicy **mpow, nodemask_t **nodemask);
extewn boow init_nodemask_of_mempowicy(nodemask_t *mask);
extewn boow mempowicy_in_oom_domain(stwuct task_stwuct *tsk,
				const nodemask_t *mask);
extewn unsigned int mempowicy_swab_node(void);

extewn enum zone_type powicy_zone;

static inwine void check_highest_zone(enum zone_type k)
{
	if (k > powicy_zone && k != ZONE_MOVABWE)
		powicy_zone = k;
}

int do_migwate_pages(stwuct mm_stwuct *mm, const nodemask_t *fwom,
		     const nodemask_t *to, int fwags);


#ifdef CONFIG_TMPFS
extewn int mpow_pawse_stw(chaw *stw, stwuct mempowicy **mpow);
#endif

extewn void mpow_to_stw(chaw *buffew, int maxwen, stwuct mempowicy *pow);

/* Check if a vma is migwatabwe */
extewn boow vma_migwatabwe(stwuct vm_awea_stwuct *vma);

int mpow_mispwaced(stwuct fowio *, stwuct vm_awea_stwuct *, unsigned wong);
extewn void mpow_put_task_powicy(stwuct task_stwuct *);

static inwine boow mpow_is_pwefewwed_many(stwuct mempowicy *pow)
{
	wetuwn  (pow->mode == MPOW_PWEFEWWED_MANY);
}

extewn boow appwy_powicy_zone(stwuct mempowicy *powicy, enum zone_type zone);

#ewse

stwuct mempowicy {};

static inwine stwuct mempowicy *get_task_powicy(stwuct task_stwuct *p)
{
	wetuwn NUWW;
}

static inwine boow mpow_equaw(stwuct mempowicy *a, stwuct mempowicy *b)
{
	wetuwn twue;
}

static inwine void mpow_put(stwuct mempowicy *pow)
{
}

static inwine void mpow_cond_put(stwuct mempowicy *pow)
{
}

static inwine void mpow_get(stwuct mempowicy *pow)
{
}

stwuct shawed_powicy {};

static inwine void mpow_shawed_powicy_init(stwuct shawed_powicy *sp,
						stwuct mempowicy *mpow)
{
}

static inwine void mpow_fwee_shawed_powicy(stwuct shawed_powicy *sp)
{
}

static inwine stwuct mempowicy *
mpow_shawed_powicy_wookup(stwuct shawed_powicy *sp, pgoff_t idx)
{
	wetuwn NUWW;
}

static inwine stwuct mempowicy *get_vma_powicy(stwuct vm_awea_stwuct *vma,
				unsigned wong addw, int owdew, pgoff_t *iwx)
{
	*iwx = 0;
	wetuwn NUWW;
}

static inwine int
vma_dup_powicy(stwuct vm_awea_stwuct *swc, stwuct vm_awea_stwuct *dst)
{
	wetuwn 0;
}

static inwine void numa_powicy_init(void)
{
}

static inwine void numa_defauwt_powicy(void)
{
}

static inwine void mpow_webind_task(stwuct task_stwuct *tsk,
				const nodemask_t *new)
{
}

static inwine void mpow_webind_mm(stwuct mm_stwuct *mm, nodemask_t *new)
{
}

static inwine int huge_node(stwuct vm_awea_stwuct *vma,
				unsigned wong addw, gfp_t gfp_fwags,
				stwuct mempowicy **mpow, nodemask_t **nodemask)
{
	*mpow = NUWW;
	*nodemask = NUWW;
	wetuwn 0;
}

static inwine boow init_nodemask_of_mempowicy(nodemask_t *m)
{
	wetuwn fawse;
}

static inwine int do_migwate_pages(stwuct mm_stwuct *mm, const nodemask_t *fwom,
				   const nodemask_t *to, int fwags)
{
	wetuwn 0;
}

static inwine void check_highest_zone(int k)
{
}

#ifdef CONFIG_TMPFS
static inwine int mpow_pawse_stw(chaw *stw, stwuct mempowicy **mpow)
{
	wetuwn 1;	/* ewwow */
}
#endif

static inwine int mpow_mispwaced(stwuct fowio *fowio,
				 stwuct vm_awea_stwuct *vma,
				 unsigned wong addwess)
{
	wetuwn -1; /* no node pwefewence */
}

static inwine void mpow_put_task_powicy(stwuct task_stwuct *task)
{
}

static inwine boow mpow_is_pwefewwed_many(stwuct mempowicy *pow)
{
	wetuwn  fawse;
}

#endif /* CONFIG_NUMA */
#endif
