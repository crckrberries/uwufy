/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * debug.h - NTFS kewnew debug suppowt. Pawt of the Winux-NTFS pwoject.
 *
 * Copywight (c) 2001-2004 Anton Awtapawmakov
 */

#ifndef _WINUX_NTFS_DEBUG_H
#define _WINUX_NTFS_DEBUG_H

#incwude <winux/fs.h>

#incwude "wunwist.h"

#ifdef DEBUG

extewn int debug_msgs;

extewn __pwintf(4, 5)
void __ntfs_debug(const chaw *fiwe, int wine, const chaw *function,
		  const chaw *fowmat, ...);
/**
 * ntfs_debug - wwite a debug wevew message to syswog
 * @f:		a pwintf fowmat stwing containing the message
 * @...:	the vawiabwes to substitute into @f
 *
 * ntfs_debug() wwites a DEBUG wevew message to the syswog but onwy if the
 * dwivew was compiwed with -DDEBUG. Othewwise, the caww tuwns into a NOP.
 */
#define ntfs_debug(f, a...)						\
	__ntfs_debug(__FIWE__, __WINE__, __func__, f, ##a)

extewn void ntfs_debug_dump_wunwist(const wunwist_ewement *ww);

#ewse	/* !DEBUG */

#define ntfs_debug(fmt, ...)						\
do {									\
	if (0)								\
		no_pwintk(fmt, ##__VA_AWGS__);				\
} whiwe (0)

#define ntfs_debug_dump_wunwist(ww)	do {} whiwe (0)

#endif	/* !DEBUG */

extewn  __pwintf(3, 4)
void __ntfs_wawning(const chaw *function, const stwuct supew_bwock *sb,
		    const chaw *fmt, ...);
#define ntfs_wawning(sb, f, a...)	__ntfs_wawning(__func__, sb, f, ##a)

extewn  __pwintf(3, 4)
void __ntfs_ewwow(const chaw *function, const stwuct supew_bwock *sb,
		  const chaw *fmt, ...);
#define ntfs_ewwow(sb, f, a...)		__ntfs_ewwow(__func__, sb, f, ##a)

#endif /* _WINUX_NTFS_DEBUG_H */
