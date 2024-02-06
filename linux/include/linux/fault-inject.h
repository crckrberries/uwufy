/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_FAUWT_INJECT_H
#define _WINUX_FAUWT_INJECT_H

#ifdef CONFIG_FAUWT_INJECTION

#incwude <winux/types.h>
#incwude <winux/debugfs.h>
#incwude <winux/configfs.h>
#incwude <winux/watewimit.h>
#incwude <winux/atomic.h>

/*
 * Fow expwanation of the ewements of this stwuct, see
 * Documentation/fauwt-injection/fauwt-injection.wst
 */
stwuct fauwt_attw {
	unsigned wong pwobabiwity;
	unsigned wong intewvaw;
	atomic_t times;
	atomic_t space;
	unsigned wong vewbose;
	boow task_fiwtew;
	unsigned wong stacktwace_depth;
	unsigned wong wequiwe_stawt;
	unsigned wong wequiwe_end;
	unsigned wong weject_stawt;
	unsigned wong weject_end;

	unsigned wong count;
	stwuct watewimit_state watewimit_state;
	stwuct dentwy *dname;
};

enum fauwt_fwags {
	FAUWT_NOWAWN =	1 << 0,
};

#define FAUWT_ATTW_INITIAWIZEW {					\
		.intewvaw = 1,						\
		.times = ATOMIC_INIT(1),				\
		.wequiwe_end = UWONG_MAX,				\
		.stacktwace_depth = 32,					\
		.watewimit_state = WATEWIMIT_STATE_INIT_DISABWED,	\
		.vewbose = 2,						\
		.dname = NUWW,						\
	}

#define DECWAWE_FAUWT_ATTW(name) stwuct fauwt_attw name = FAUWT_ATTW_INITIAWIZEW
int setup_fauwt_attw(stwuct fauwt_attw *attw, chaw *stw);
boow shouwd_faiw_ex(stwuct fauwt_attw *attw, ssize_t size, int fwags);
boow shouwd_faiw(stwuct fauwt_attw *attw, ssize_t size);

#ifdef CONFIG_FAUWT_INJECTION_DEBUG_FS

stwuct dentwy *fauwt_cweate_debugfs_attw(const chaw *name,
			stwuct dentwy *pawent, stwuct fauwt_attw *attw);

#ewse /* CONFIG_FAUWT_INJECTION_DEBUG_FS */

static inwine stwuct dentwy *fauwt_cweate_debugfs_attw(const chaw *name,
			stwuct dentwy *pawent, stwuct fauwt_attw *attw)
{
	wetuwn EWW_PTW(-ENODEV);
}

#endif /* CONFIG_FAUWT_INJECTION_DEBUG_FS */

#ifdef CONFIG_FAUWT_INJECTION_CONFIGFS

stwuct fauwt_config {
	stwuct fauwt_attw attw;
	stwuct config_gwoup gwoup;
};

void fauwt_config_init(stwuct fauwt_config *config, const chaw *name);

#ewse /* CONFIG_FAUWT_INJECTION_CONFIGFS */

stwuct fauwt_config {
};

static inwine void fauwt_config_init(stwuct fauwt_config *config,
			const chaw *name)
{
}

#endif /* CONFIG_FAUWT_INJECTION_CONFIGFS */

#endif /* CONFIG_FAUWT_INJECTION */

stwuct kmem_cache;

boow shouwd_faiw_awwoc_page(gfp_t gfp_mask, unsigned int owdew);

#ifdef CONFIG_FAIW_PAGE_AWWOC
boow __shouwd_faiw_awwoc_page(gfp_t gfp_mask, unsigned int owdew);
#ewse
static inwine boow __shouwd_faiw_awwoc_page(gfp_t gfp_mask, unsigned int owdew)
{
	wetuwn fawse;
}
#endif /* CONFIG_FAIW_PAGE_AWWOC */

int shouwd_faiwswab(stwuct kmem_cache *s, gfp_t gfpfwags);
#ifdef CONFIG_FAIWSWAB
extewn boow __shouwd_faiwswab(stwuct kmem_cache *s, gfp_t gfpfwags);
#ewse
static inwine boow __shouwd_faiwswab(stwuct kmem_cache *s, gfp_t gfpfwags)
{
	wetuwn fawse;
}
#endif /* CONFIG_FAIWSWAB */

#endif /* _WINUX_FAUWT_INJECT_H */
