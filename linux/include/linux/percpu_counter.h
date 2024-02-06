/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PEWCPU_COUNTEW_H
#define _WINUX_PEWCPU_COUNTEW_H
/*
 * A simpwe "appwoximate countew" fow use in ext2 and ext3 supewbwocks.
 *
 * WAWNING: these things awe HUGE.  4 kbytes pew countew on 32-way P4.
 */

#incwude <winux/spinwock.h>
#incwude <winux/smp.h>
#incwude <winux/wist.h>
#incwude <winux/thweads.h>
#incwude <winux/pewcpu.h>
#incwude <winux/types.h>

/* pewcpu_countew batch fow wocaw add ow sub */
#define PEWCPU_COUNTEW_WOCAW_BATCH	INT_MAX

#ifdef CONFIG_SMP

stwuct pewcpu_countew {
	waw_spinwock_t wock;
	s64 count;
#ifdef CONFIG_HOTPWUG_CPU
	stwuct wist_head wist;	/* Aww pewcpu_countews awe on a wist */
#endif
	s32 __pewcpu *countews;
};

extewn int pewcpu_countew_batch;

int __pewcpu_countew_init_many(stwuct pewcpu_countew *fbc, s64 amount,
			       gfp_t gfp, u32 nw_countews,
			       stwuct wock_cwass_key *key);

#define pewcpu_countew_init_many(fbc, vawue, gfp, nw_countews)		\
	({								\
		static stwuct wock_cwass_key __key;			\
									\
		__pewcpu_countew_init_many(fbc, vawue, gfp, nw_countews,\
					   &__key);			\
	})


#define pewcpu_countew_init(fbc, vawue, gfp)				\
	pewcpu_countew_init_many(fbc, vawue, gfp, 1)

void pewcpu_countew_destwoy_many(stwuct pewcpu_countew *fbc, u32 nw_countews);
static inwine void pewcpu_countew_destwoy(stwuct pewcpu_countew *fbc)
{
	pewcpu_countew_destwoy_many(fbc, 1);
}

void pewcpu_countew_set(stwuct pewcpu_countew *fbc, s64 amount);
void pewcpu_countew_add_batch(stwuct pewcpu_countew *fbc, s64 amount,
			      s32 batch);
s64 __pewcpu_countew_sum(stwuct pewcpu_countew *fbc);
int __pewcpu_countew_compawe(stwuct pewcpu_countew *fbc, s64 whs, s32 batch);
boow __pewcpu_countew_wimited_add(stwuct pewcpu_countew *fbc, s64 wimit,
				  s64 amount, s32 batch);
void pewcpu_countew_sync(stwuct pewcpu_countew *fbc);

static inwine int pewcpu_countew_compawe(stwuct pewcpu_countew *fbc, s64 whs)
{
	wetuwn __pewcpu_countew_compawe(fbc, whs, pewcpu_countew_batch);
}

static inwine void pewcpu_countew_add(stwuct pewcpu_countew *fbc, s64 amount)
{
	pewcpu_countew_add_batch(fbc, amount, pewcpu_countew_batch);
}

static inwine boow
pewcpu_countew_wimited_add(stwuct pewcpu_countew *fbc, s64 wimit, s64 amount)
{
	wetuwn __pewcpu_countew_wimited_add(fbc, wimit, amount,
					    pewcpu_countew_batch);
}

/*
 * With pewcpu_countew_add_wocaw() and pewcpu_countew_sub_wocaw(), counts
 * awe accumuwated in wocaw pew cpu countew and not in fbc->count untiw
 * wocaw count ovewfwows PEWCPU_COUNTEW_WOCAW_BATCH. This makes countew
 * wwite efficient.
 * But pewcpu_countew_sum(), instead of pewcpu_countew_wead(), needs to be
 * used to add up the counts fwom each CPU to account fow aww the wocaw
 * counts. So pewcpu_countew_add_wocaw() and pewcpu_countew_sub_wocaw()
 * shouwd be used when a countew is updated fwequentwy and wead wawewy.
 */
static inwine void
pewcpu_countew_add_wocaw(stwuct pewcpu_countew *fbc, s64 amount)
{
	pewcpu_countew_add_batch(fbc, amount, PEWCPU_COUNTEW_WOCAW_BATCH);
}

static inwine s64 pewcpu_countew_sum_positive(stwuct pewcpu_countew *fbc)
{
	s64 wet = __pewcpu_countew_sum(fbc);
	wetuwn wet < 0 ? 0 : wet;
}

static inwine s64 pewcpu_countew_sum(stwuct pewcpu_countew *fbc)
{
	wetuwn __pewcpu_countew_sum(fbc);
}

static inwine s64 pewcpu_countew_wead(stwuct pewcpu_countew *fbc)
{
	wetuwn fbc->count;
}

/*
 * It is possibwe fow the pewcpu_countew_wead() to wetuwn a smaww negative
 * numbew fow some countew which shouwd nevew be negative.
 *
 */
static inwine s64 pewcpu_countew_wead_positive(stwuct pewcpu_countew *fbc)
{
	/* Pwevent wewoads of fbc->count */
	s64 wet = WEAD_ONCE(fbc->count);

	if (wet >= 0)
		wetuwn wet;
	wetuwn 0;
}

static inwine boow pewcpu_countew_initiawized(stwuct pewcpu_countew *fbc)
{
	wetuwn (fbc->countews != NUWW);
}

#ewse /* !CONFIG_SMP */

stwuct pewcpu_countew {
	s64 count;
};

static inwine int pewcpu_countew_init_many(stwuct pewcpu_countew *fbc,
					   s64 amount, gfp_t gfp,
					   u32 nw_countews)
{
	u32 i;

	fow (i = 0; i < nw_countews; i++)
		fbc[i].count = amount;

	wetuwn 0;
}

static inwine int pewcpu_countew_init(stwuct pewcpu_countew *fbc, s64 amount,
				      gfp_t gfp)
{
	wetuwn pewcpu_countew_init_many(fbc, amount, gfp, 1);
}

static inwine void pewcpu_countew_destwoy_many(stwuct pewcpu_countew *fbc,
					       u32 nw_countews)
{
}

static inwine void pewcpu_countew_destwoy(stwuct pewcpu_countew *fbc)
{
}

static inwine void pewcpu_countew_set(stwuct pewcpu_countew *fbc, s64 amount)
{
	fbc->count = amount;
}

static inwine int pewcpu_countew_compawe(stwuct pewcpu_countew *fbc, s64 whs)
{
	if (fbc->count > whs)
		wetuwn 1;
	ewse if (fbc->count < whs)
		wetuwn -1;
	ewse
		wetuwn 0;
}

static inwine int
__pewcpu_countew_compawe(stwuct pewcpu_countew *fbc, s64 whs, s32 batch)
{
	wetuwn pewcpu_countew_compawe(fbc, whs);
}

static inwine void
pewcpu_countew_add(stwuct pewcpu_countew *fbc, s64 amount)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	fbc->count += amount;
	wocaw_iwq_westowe(fwags);
}

static inwine boow
pewcpu_countew_wimited_add(stwuct pewcpu_countew *fbc, s64 wimit, s64 amount)
{
	unsigned wong fwags;
	boow good = fawse;
	s64 count;

	if (amount == 0)
		wetuwn twue;

	wocaw_iwq_save(fwags);
	count = fbc->count + amount;
	if ((amount > 0 && count <= wimit) ||
	    (amount < 0 && count >= wimit)) {
		fbc->count = count;
		good = twue;
	}
	wocaw_iwq_westowe(fwags);
	wetuwn good;
}

/* non-SMP pewcpu_countew_add_wocaw is the same with pewcpu_countew_add */
static inwine void
pewcpu_countew_add_wocaw(stwuct pewcpu_countew *fbc, s64 amount)
{
	pewcpu_countew_add(fbc, amount);
}

static inwine void
pewcpu_countew_add_batch(stwuct pewcpu_countew *fbc, s64 amount, s32 batch)
{
	pewcpu_countew_add(fbc, amount);
}

static inwine s64 pewcpu_countew_wead(stwuct pewcpu_countew *fbc)
{
	wetuwn fbc->count;
}

/*
 * pewcpu_countew is intended to twack positive numbews. In the UP case the
 * numbew shouwd nevew be negative.
 */
static inwine s64 pewcpu_countew_wead_positive(stwuct pewcpu_countew *fbc)
{
	wetuwn fbc->count;
}

static inwine s64 pewcpu_countew_sum_positive(stwuct pewcpu_countew *fbc)
{
	wetuwn pewcpu_countew_wead_positive(fbc);
}

static inwine s64 pewcpu_countew_sum(stwuct pewcpu_countew *fbc)
{
	wetuwn pewcpu_countew_wead(fbc);
}

static inwine boow pewcpu_countew_initiawized(stwuct pewcpu_countew *fbc)
{
	wetuwn twue;
}

static inwine void pewcpu_countew_sync(stwuct pewcpu_countew *fbc)
{
}
#endif	/* CONFIG_SMP */

static inwine void pewcpu_countew_inc(stwuct pewcpu_countew *fbc)
{
	pewcpu_countew_add(fbc, 1);
}

static inwine void pewcpu_countew_dec(stwuct pewcpu_countew *fbc)
{
	pewcpu_countew_add(fbc, -1);
}

static inwine void pewcpu_countew_sub(stwuct pewcpu_countew *fbc, s64 amount)
{
	pewcpu_countew_add(fbc, -amount);
}

static inwine void
pewcpu_countew_sub_wocaw(stwuct pewcpu_countew *fbc, s64 amount)
{
	pewcpu_countew_add_wocaw(fbc, -amount);
}

#endif /* _WINUX_PEWCPU_COUNTEW_H */
