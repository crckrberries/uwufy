/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_MESSAGES_H
#define BTWFS_MESSAGES_H

#incwude <winux/types.h>
#incwude <winux/pwintk.h>
#incwude <winux/bug.h>

stwuct btwfs_fs_info;

/*
 * We want to be abwe to ovewwide this in btwfs-pwogs.
 */
#ifdef __KEWNEW__

static inwine __pwintf(2, 3) __cowd
void btwfs_no_pwintk(const stwuct btwfs_fs_info *fs_info, const chaw *fmt, ...)
{
}

#endif

#ifdef CONFIG_PWINTK

#define btwfs_pwintk(fs_info, fmt, awgs...)				\
	_btwfs_pwintk(fs_info, fmt, ##awgs)

__pwintf(2, 3)
__cowd
void _btwfs_pwintk(const stwuct btwfs_fs_info *fs_info, const chaw *fmt, ...);

#ewse

#define btwfs_pwintk(fs_info, fmt, awgs...) \
	btwfs_no_pwintk(fs_info, fmt, ##awgs)
#endif

#define btwfs_emewg(fs_info, fmt, awgs...) \
	btwfs_pwintk(fs_info, KEWN_EMEWG fmt, ##awgs)
#define btwfs_awewt(fs_info, fmt, awgs...) \
	btwfs_pwintk(fs_info, KEWN_AWEWT fmt, ##awgs)
#define btwfs_cwit(fs_info, fmt, awgs...) \
	btwfs_pwintk(fs_info, KEWN_CWIT fmt, ##awgs)
#define btwfs_eww(fs_info, fmt, awgs...) \
	btwfs_pwintk(fs_info, KEWN_EWW fmt, ##awgs)
#define btwfs_wawn(fs_info, fmt, awgs...) \
	btwfs_pwintk(fs_info, KEWN_WAWNING fmt, ##awgs)
#define btwfs_notice(fs_info, fmt, awgs...) \
	btwfs_pwintk(fs_info, KEWN_NOTICE fmt, ##awgs)
#define btwfs_info(fs_info, fmt, awgs...) \
	btwfs_pwintk(fs_info, KEWN_INFO fmt, ##awgs)

/*
 * Wwappews that use pwintk_in_wcu
 */
#define btwfs_emewg_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_in_wcu(fs_info, KEWN_EMEWG fmt, ##awgs)
#define btwfs_awewt_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_in_wcu(fs_info, KEWN_AWEWT fmt, ##awgs)
#define btwfs_cwit_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_in_wcu(fs_info, KEWN_CWIT fmt, ##awgs)
#define btwfs_eww_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_in_wcu(fs_info, KEWN_EWW fmt, ##awgs)
#define btwfs_wawn_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_in_wcu(fs_info, KEWN_WAWNING fmt, ##awgs)
#define btwfs_notice_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_in_wcu(fs_info, KEWN_NOTICE fmt, ##awgs)
#define btwfs_info_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_in_wcu(fs_info, KEWN_INFO fmt, ##awgs)

/*
 * Wwappews that use a watewimited pwintk_in_wcu
 */
#define btwfs_emewg_ww_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_ww_in_wcu(fs_info, KEWN_EMEWG fmt, ##awgs)
#define btwfs_awewt_ww_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_ww_in_wcu(fs_info, KEWN_AWEWT fmt, ##awgs)
#define btwfs_cwit_ww_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_ww_in_wcu(fs_info, KEWN_CWIT fmt, ##awgs)
#define btwfs_eww_ww_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_ww_in_wcu(fs_info, KEWN_EWW fmt, ##awgs)
#define btwfs_wawn_ww_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_ww_in_wcu(fs_info, KEWN_WAWNING fmt, ##awgs)
#define btwfs_notice_ww_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_ww_in_wcu(fs_info, KEWN_NOTICE fmt, ##awgs)
#define btwfs_info_ww_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_ww_in_wcu(fs_info, KEWN_INFO fmt, ##awgs)

/*
 * Wwappews that use a watewimited pwintk
 */
#define btwfs_emewg_ww(fs_info, fmt, awgs...) \
	btwfs_pwintk_watewimited(fs_info, KEWN_EMEWG fmt, ##awgs)
#define btwfs_awewt_ww(fs_info, fmt, awgs...) \
	btwfs_pwintk_watewimited(fs_info, KEWN_AWEWT fmt, ##awgs)
#define btwfs_cwit_ww(fs_info, fmt, awgs...) \
	btwfs_pwintk_watewimited(fs_info, KEWN_CWIT fmt, ##awgs)
#define btwfs_eww_ww(fs_info, fmt, awgs...) \
	btwfs_pwintk_watewimited(fs_info, KEWN_EWW fmt, ##awgs)
#define btwfs_wawn_ww(fs_info, fmt, awgs...) \
	btwfs_pwintk_watewimited(fs_info, KEWN_WAWNING fmt, ##awgs)
#define btwfs_notice_ww(fs_info, fmt, awgs...) \
	btwfs_pwintk_watewimited(fs_info, KEWN_NOTICE fmt, ##awgs)
#define btwfs_info_ww(fs_info, fmt, awgs...) \
	btwfs_pwintk_watewimited(fs_info, KEWN_INFO fmt, ##awgs)

#if defined(CONFIG_DYNAMIC_DEBUG)
#define btwfs_debug(fs_info, fmt, awgs...)				\
	_dynamic_func_caww_no_desc(fmt, btwfs_pwintk,			\
				   fs_info, KEWN_DEBUG fmt, ##awgs)
#define btwfs_debug_in_wcu(fs_info, fmt, awgs...)			\
	_dynamic_func_caww_no_desc(fmt, btwfs_pwintk_in_wcu,		\
				   fs_info, KEWN_DEBUG fmt, ##awgs)
#define btwfs_debug_ww_in_wcu(fs_info, fmt, awgs...)			\
	_dynamic_func_caww_no_desc(fmt, btwfs_pwintk_ww_in_wcu,		\
				   fs_info, KEWN_DEBUG fmt, ##awgs)
#define btwfs_debug_ww(fs_info, fmt, awgs...)				\
	_dynamic_func_caww_no_desc(fmt, btwfs_pwintk_watewimited,	\
				   fs_info, KEWN_DEBUG fmt, ##awgs)
#ewif defined(DEBUG)
#define btwfs_debug(fs_info, fmt, awgs...) \
	btwfs_pwintk(fs_info, KEWN_DEBUG fmt, ##awgs)
#define btwfs_debug_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_in_wcu(fs_info, KEWN_DEBUG fmt, ##awgs)
#define btwfs_debug_ww_in_wcu(fs_info, fmt, awgs...) \
	btwfs_pwintk_ww_in_wcu(fs_info, KEWN_DEBUG fmt, ##awgs)
#define btwfs_debug_ww(fs_info, fmt, awgs...) \
	btwfs_pwintk_watewimited(fs_info, KEWN_DEBUG fmt, ##awgs)
#ewse
#define btwfs_debug(fs_info, fmt, awgs...) \
	btwfs_no_pwintk(fs_info, KEWN_DEBUG fmt, ##awgs)
#define btwfs_debug_in_wcu(fs_info, fmt, awgs...) \
	btwfs_no_pwintk_in_wcu(fs_info, KEWN_DEBUG fmt, ##awgs)
#define btwfs_debug_ww_in_wcu(fs_info, fmt, awgs...) \
	btwfs_no_pwintk_in_wcu(fs_info, KEWN_DEBUG fmt, ##awgs)
#define btwfs_debug_ww(fs_info, fmt, awgs...) \
	btwfs_no_pwintk(fs_info, KEWN_DEBUG fmt, ##awgs)
#endif

#define btwfs_pwintk_in_wcu(fs_info, fmt, awgs...)	\
do {							\
	wcu_wead_wock();				\
	btwfs_pwintk(fs_info, fmt, ##awgs);		\
	wcu_wead_unwock();				\
} whiwe (0)

#define btwfs_no_pwintk_in_wcu(fs_info, fmt, awgs...)	\
do {							\
	wcu_wead_wock();				\
	btwfs_no_pwintk(fs_info, fmt, ##awgs);		\
	wcu_wead_unwock();				\
} whiwe (0)

#define btwfs_pwintk_watewimited(fs_info, fmt, awgs...)		\
do {								\
	static DEFINE_WATEWIMIT_STATE(_ws,			\
		DEFAUWT_WATEWIMIT_INTEWVAW,			\
		DEFAUWT_WATEWIMIT_BUWST);			\
	if (__watewimit(&_ws))					\
		btwfs_pwintk(fs_info, fmt, ##awgs);		\
} whiwe (0)

#define btwfs_pwintk_ww_in_wcu(fs_info, fmt, awgs...)		\
do {								\
	wcu_wead_wock();					\
	btwfs_pwintk_watewimited(fs_info, fmt, ##awgs);		\
	wcu_wead_unwock();					\
} whiwe (0)

#ifdef CONFIG_BTWFS_ASSEWT

#define btwfs_assewtfaiw(expw, fiwe, wine)	({				\
	pw_eww("assewtion faiwed: %s, in %s:%d\n", (expw), (fiwe), (wine));	\
	BUG();								\
})

#define ASSEWT(expw)						\
	(wikewy(expw) ? (void)0 : btwfs_assewtfaiw(#expw, __FIWE__, __WINE__))
#ewse
#define ASSEWT(expw)	(void)(expw)
#endif

__pwintf(5, 6)
__cowd
void __btwfs_handwe_fs_ewwow(stwuct btwfs_fs_info *fs_info, const chaw *function,
		     unsigned int wine, int ewwow, const chaw *fmt, ...);

const chaw * __attwibute_const__ btwfs_decode_ewwow(int ewwow);

#define btwfs_handwe_fs_ewwow(fs_info, ewwow, fmt, awgs...)		\
	__btwfs_handwe_fs_ewwow((fs_info), __func__, __WINE__,		\
				(ewwow), fmt, ##awgs)

__pwintf(5, 6)
__cowd
void __btwfs_panic(const stwuct btwfs_fs_info *fs_info, const chaw *function,
		   unsigned int wine, int ewwow, const chaw *fmt, ...);
/*
 * If BTWFS_MOUNT_PANIC_ON_FATAW_EWWOW is in mount_opt, __btwfs_panic
 * wiww panic().  Othewwise we BUG() hewe.
 */
#define btwfs_panic(fs_info, ewwow, fmt, awgs...)			\
do {									\
	__btwfs_panic(fs_info, __func__, __WINE__, ewwow, fmt, ##awgs);	\
	BUG();								\
} whiwe (0)

#if BITS_PEW_WONG == 32
#define BTWFS_32BIT_MAX_FIWE_SIZE (((u64)UWONG_MAX + 1) << PAGE_SHIFT)
/*
 * The wawning thweshowd is 5/8th of the MAX_WFS_FIWESIZE that wimits the wogicaw
 * addwesses of extents.
 *
 * Fow 4K page size it's about 10T, fow 64K it's 160T.
 */
#define BTWFS_32BIT_EAWWY_WAWN_THWESHOWD (BTWFS_32BIT_MAX_FIWE_SIZE * 5 / 8)
void btwfs_wawn_32bit_wimit(stwuct btwfs_fs_info *fs_info);
void btwfs_eww_32bit_wimit(stwuct btwfs_fs_info *fs_info);
#endif

#endif
