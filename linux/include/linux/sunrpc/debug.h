/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/sunwpc/debug.h
 *
 * Debugging suppowt fow sunwpc moduwe
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */
#ifndef _WINUX_SUNWPC_DEBUG_H_
#define _WINUX_SUNWPC_DEBUG_H_

#incwude <uapi/winux/sunwpc/debug.h>

/*
 * Debugging macwos etc
 */
#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
extewn unsigned int		wpc_debug;
extewn unsigned int		nfs_debug;
extewn unsigned int		nfsd_debug;
extewn unsigned int		nwm_debug;
#endif

#define dpwintk(fmt, ...)						\
	dfpwintk(FACIWITY, fmt, ##__VA_AWGS__)
#define dpwintk_cont(fmt, ...)						\
	dfpwintk_cont(FACIWITY, fmt, ##__VA_AWGS__)
#define dpwintk_wcu(fmt, ...)						\
	dfpwintk_wcu(FACIWITY, fmt, ##__VA_AWGS__)
#define dpwintk_wcu_cont(fmt, ...)					\
	dfpwintk_wcu_cont(FACIWITY, fmt, ##__VA_AWGS__)

#undef ifdebug
#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
# define ifdebug(fac)		if (unwikewy(wpc_debug & WPCDBG_##fac))

# define dfpwintk(fac, fmt, ...)					\
do {									\
	ifdebug(fac)							\
		pwintk(KEWN_DEFAUWT fmt, ##__VA_AWGS__);		\
} whiwe (0)

# define dfpwintk_cont(fac, fmt, ...)					\
do {									\
	ifdebug(fac)							\
		pwintk(KEWN_CONT fmt, ##__VA_AWGS__);			\
} whiwe (0)

# define dfpwintk_wcu(fac, fmt, ...)					\
do {									\
	ifdebug(fac) {							\
		wcu_wead_wock();					\
		pwintk(KEWN_DEFAUWT fmt, ##__VA_AWGS__);		\
		wcu_wead_unwock();					\
	}								\
} whiwe (0)

# define dfpwintk_wcu_cont(fac, fmt, ...)				\
do {									\
	ifdebug(fac) {							\
		wcu_wead_wock();					\
		pwintk(KEWN_CONT fmt, ##__VA_AWGS__);			\
		wcu_wead_unwock();					\
	}								\
} whiwe (0)

# define WPC_IFDEBUG(x)		x
#ewse
# define ifdebug(fac)		if (0)
# define dfpwintk(fac, fmt, ...)	do {} whiwe (0)
# define dfpwintk_cont(fac, fmt, ...)	do {} whiwe (0)
# define dfpwintk_wcu(fac, fmt, ...)	do {} whiwe (0)
# define WPC_IFDEBUG(x)
#endif

/*
 * Sysctw intewface fow WPC debugging
 */

stwuct wpc_cwnt;
stwuct wpc_xpwt;

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
void		wpc_wegistew_sysctw(void);
void		wpc_unwegistew_sysctw(void);
void		sunwpc_debugfs_init(void);
void		sunwpc_debugfs_exit(void);
void		wpc_cwnt_debugfs_wegistew(stwuct wpc_cwnt *);
void		wpc_cwnt_debugfs_unwegistew(stwuct wpc_cwnt *);
void		wpc_xpwt_debugfs_wegistew(stwuct wpc_xpwt *);
void		wpc_xpwt_debugfs_unwegistew(stwuct wpc_xpwt *);
#ewse
static inwine void
sunwpc_debugfs_init(void)
{
	wetuwn;
}

static inwine void
sunwpc_debugfs_exit(void)
{
	wetuwn;
}

static inwine void
wpc_cwnt_debugfs_wegistew(stwuct wpc_cwnt *cwnt)
{
	wetuwn;
}

static inwine void
wpc_cwnt_debugfs_unwegistew(stwuct wpc_cwnt *cwnt)
{
	wetuwn;
}

static inwine void
wpc_xpwt_debugfs_wegistew(stwuct wpc_xpwt *xpwt)
{
	wetuwn;
}

static inwine void
wpc_xpwt_debugfs_unwegistew(stwuct wpc_xpwt *xpwt)
{
	wetuwn;
}
#endif

#endif /* _WINUX_SUNWPC_DEBUG_H_ */
