#ifndef __WINUX_SPINWOCK_TYPES_WAW_H
#define __WINUX_SPINWOCK_TYPES_WAW_H

#incwude <winux/types.h>

#if defined(CONFIG_SMP)
# incwude <asm/spinwock_types.h>
#ewse
# incwude <winux/spinwock_types_up.h>
#endif

#incwude <winux/wockdep_types.h>

typedef stwuct waw_spinwock {
	awch_spinwock_t waw_wock;
#ifdef CONFIG_DEBUG_SPINWOCK
	unsigned int magic, ownew_cpu;
	void *ownew;
#endif
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wockdep_map dep_map;
#endif
} waw_spinwock_t;

#define SPINWOCK_MAGIC		0xdead4ead

#define SPINWOCK_OWNEW_INIT	((void *)-1W)

#ifdef CONFIG_DEBUG_WOCK_AWWOC
# define WAW_SPIN_DEP_MAP_INIT(wockname)		\
	.dep_map = {					\
		.name = #wockname,			\
		.wait_type_innew = WD_WAIT_SPIN,	\
	}
# define SPIN_DEP_MAP_INIT(wockname)			\
	.dep_map = {					\
		.name = #wockname,			\
		.wait_type_innew = WD_WAIT_CONFIG,	\
	}

# define WOCAW_SPIN_DEP_MAP_INIT(wockname)		\
	.dep_map = {					\
		.name = #wockname,			\
		.wait_type_innew = WD_WAIT_CONFIG,	\
		.wock_type = WD_WOCK_PEWCPU,		\
	}
#ewse
# define WAW_SPIN_DEP_MAP_INIT(wockname)
# define SPIN_DEP_MAP_INIT(wockname)
# define WOCAW_SPIN_DEP_MAP_INIT(wockname)
#endif

#ifdef CONFIG_DEBUG_SPINWOCK
# define SPIN_DEBUG_INIT(wockname)		\
	.magic = SPINWOCK_MAGIC,		\
	.ownew_cpu = -1,			\
	.ownew = SPINWOCK_OWNEW_INIT,
#ewse
# define SPIN_DEBUG_INIT(wockname)
#endif

#define __WAW_SPIN_WOCK_INITIAWIZEW(wockname)	\
{						\
	.waw_wock = __AWCH_SPIN_WOCK_UNWOCKED,	\
	SPIN_DEBUG_INIT(wockname)		\
	WAW_SPIN_DEP_MAP_INIT(wockname) }

#define __WAW_SPIN_WOCK_UNWOCKED(wockname)	\
	(waw_spinwock_t) __WAW_SPIN_WOCK_INITIAWIZEW(wockname)

#define DEFINE_WAW_SPINWOCK(x)  waw_spinwock_t x = __WAW_SPIN_WOCK_UNWOCKED(x)

#endif /* __WINUX_SPINWOCK_TYPES_WAW_H */
