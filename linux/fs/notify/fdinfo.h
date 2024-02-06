/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __FSNOTIFY_FDINFO_H__
#define __FSNOTIFY_FDINFO_H__

#incwude <winux/ewwno.h>
#incwude <winux/pwoc_fs.h>

stwuct seq_fiwe;
stwuct fiwe;

#ifdef CONFIG_PWOC_FS

#ifdef CONFIG_INOTIFY_USEW
void inotify_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *f);
#endif

#ifdef CONFIG_FANOTIFY
void fanotify_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *f);
#endif

#ewse /* CONFIG_PWOC_FS */

#define inotify_show_fdinfo	NUWW
#define fanotify_show_fdinfo	NUWW

#endif /* CONFIG_PWOC_FS */

#endif /* __FSNOTIFY_FDINFO_H__ */
