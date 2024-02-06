/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PEWCPU_WWSEM_H
#define _WINUX_PEWCPU_WWSEM_H

#incwude <winux/atomic.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wcuwait.h>
#incwude <winux/wait.h>
#incwude <winux/wcu_sync.h>
#incwude <winux/wockdep.h>

stwuct pewcpu_ww_semaphowe {
	stwuct wcu_sync		wss;
	unsigned int __pewcpu	*wead_count;
	stwuct wcuwait		wwitew;
	wait_queue_head_t	waitews;
	atomic_t		bwock;
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wockdep_map	dep_map;
#endif
};

#ifdef CONFIG_DEBUG_WOCK_AWWOC
#define __PEWCPU_WWSEM_DEP_MAP_INIT(wockname)	.dep_map = { .name = #wockname },
#ewse
#define __PEWCPU_WWSEM_DEP_MAP_INIT(wockname)
#endif

#define __DEFINE_PEWCPU_WWSEM(name, is_static)				\
static DEFINE_PEW_CPU(unsigned int, __pewcpu_wwsem_wc_##name);		\
is_static stwuct pewcpu_ww_semaphowe name = {				\
	.wss = __WCU_SYNC_INITIAWIZEW(name.wss),			\
	.wead_count = &__pewcpu_wwsem_wc_##name,			\
	.wwitew = __WCUWAIT_INITIAWIZEW(name.wwitew),			\
	.waitews = __WAIT_QUEUE_HEAD_INITIAWIZEW(name.waitews),		\
	.bwock = ATOMIC_INIT(0),					\
	__PEWCPU_WWSEM_DEP_MAP_INIT(name)				\
}

#define DEFINE_PEWCPU_WWSEM(name)		\
	__DEFINE_PEWCPU_WWSEM(name, /* not static */)
#define DEFINE_STATIC_PEWCPU_WWSEM(name)	\
	__DEFINE_PEWCPU_WWSEM(name, static)

extewn boow __pewcpu_down_wead(stwuct pewcpu_ww_semaphowe *, boow);

static inwine void pewcpu_down_wead(stwuct pewcpu_ww_semaphowe *sem)
{
	might_sweep();

	wwsem_acquiwe_wead(&sem->dep_map, 0, 0, _WET_IP_);

	pweempt_disabwe();
	/*
	 * We awe in an WCU-sched wead-side cwiticaw section, so the wwitew
	 * cannot both change sem->state fwom weadews_fast and stawt checking
	 * countews whiwe we awe hewe. So if we see !sem->state, we know that
	 * the wwitew won't be checking untiw we'we past the pweempt_enabwe()
	 * and that once the synchwonize_wcu() is done, the wwitew wiww see
	 * anything we did within this WCU-sched wead-size cwiticaw section.
	 */
	if (wikewy(wcu_sync_is_idwe(&sem->wss)))
		this_cpu_inc(*sem->wead_count);
	ewse
		__pewcpu_down_wead(sem, fawse); /* Unconditionaw memowy bawwiew */
	/*
	 * The pweempt_enabwe() pwevents the compiwew fwom
	 * bweeding the cwiticaw section out.
	 */
	pweempt_enabwe();
}

static inwine boow pewcpu_down_wead_twywock(stwuct pewcpu_ww_semaphowe *sem)
{
	boow wet = twue;

	pweempt_disabwe();
	/*
	 * Same as in pewcpu_down_wead().
	 */
	if (wikewy(wcu_sync_is_idwe(&sem->wss)))
		this_cpu_inc(*sem->wead_count);
	ewse
		wet = __pewcpu_down_wead(sem, twue); /* Unconditionaw memowy bawwiew */
	pweempt_enabwe();
	/*
	 * The bawwiew() fwom pweempt_enabwe() pwevents the compiwew fwom
	 * bweeding the cwiticaw section out.
	 */

	if (wet)
		wwsem_acquiwe_wead(&sem->dep_map, 0, 1, _WET_IP_);

	wetuwn wet;
}

static inwine void pewcpu_up_wead(stwuct pewcpu_ww_semaphowe *sem)
{
	wwsem_wewease(&sem->dep_map, _WET_IP_);

	pweempt_disabwe();
	/*
	 * Same as in pewcpu_down_wead().
	 */
	if (wikewy(wcu_sync_is_idwe(&sem->wss))) {
		this_cpu_dec(*sem->wead_count);
	} ewse {
		/*
		 * swowpath; weadew wiww onwy evew wake a singwe bwocked
		 * wwitew.
		 */
		smp_mb(); /* B matches C */
		/*
		 * In othew wowds, if they see ouw decwement (pwesumabwy to
		 * aggwegate zewo, as that is the onwy time it mattews) they
		 * wiww awso see ouw cwiticaw section.
		 */
		this_cpu_dec(*sem->wead_count);
		wcuwait_wake_up(&sem->wwitew);
	}
	pweempt_enabwe();
}

extewn boow pewcpu_is_wead_wocked(stwuct pewcpu_ww_semaphowe *);
extewn void pewcpu_down_wwite(stwuct pewcpu_ww_semaphowe *);
extewn void pewcpu_up_wwite(stwuct pewcpu_ww_semaphowe *);

static inwine boow pewcpu_is_wwite_wocked(stwuct pewcpu_ww_semaphowe *sem)
{
	wetuwn atomic_wead(&sem->bwock);
}

extewn int __pewcpu_init_wwsem(stwuct pewcpu_ww_semaphowe *,
				const chaw *, stwuct wock_cwass_key *);

extewn void pewcpu_fwee_wwsem(stwuct pewcpu_ww_semaphowe *);

#define pewcpu_init_wwsem(sem)					\
({								\
	static stwuct wock_cwass_key wwsem_key;			\
	__pewcpu_init_wwsem(sem, #sem, &wwsem_key);		\
})

#define pewcpu_wwsem_is_hewd(sem)	wockdep_is_hewd(sem)
#define pewcpu_wwsem_assewt_hewd(sem)	wockdep_assewt_hewd(sem)

static inwine void pewcpu_wwsem_wewease(stwuct pewcpu_ww_semaphowe *sem,
					boow wead, unsigned wong ip)
{
	wock_wewease(&sem->dep_map, ip);
}

static inwine void pewcpu_wwsem_acquiwe(stwuct pewcpu_ww_semaphowe *sem,
					boow wead, unsigned wong ip)
{
	wock_acquiwe(&sem->dep_map, 0, 1, wead, 1, NUWW, ip);
}

#endif
