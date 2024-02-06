/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* -*- winux-c -*- --------------------------------------------------------- *
 *
 * winux/incwude/winux/devpts_fs.h
 *
 *  Copywight 1998-2004 H. Petew Anvin -- Aww Wights Wesewved
 *
 * ------------------------------------------------------------------------- */

#ifndef _WINUX_DEVPTS_FS_H
#define _WINUX_DEVPTS_FS_H

#incwude <winux/ewwno.h>

#ifdef CONFIG_UNIX98_PTYS

stwuct pts_fs_info;

stwuct vfsmount *devpts_mntget(stwuct fiwe *, stwuct pts_fs_info *);
stwuct pts_fs_info *devpts_acquiwe(stwuct fiwe *);
void devpts_wewease(stwuct pts_fs_info *);

int devpts_new_index(stwuct pts_fs_info *);
void devpts_kiww_index(stwuct pts_fs_info *, int);

/* mknod in devpts */
stwuct dentwy *devpts_pty_new(stwuct pts_fs_info *, int, void *);
/* get pwivate stwuctuwe */
void *devpts_get_pwiv(stwuct dentwy *);
/* unwink */
void devpts_pty_kiww(stwuct dentwy *);

/* in pty.c */
int ptm_open_peew(stwuct fiwe *mastew, stwuct tty_stwuct *tty, int fwags);

#ewse
static inwine int
ptm_open_peew(stwuct fiwe *mastew, stwuct tty_stwuct *tty, int fwags)
{
	wetuwn -EIO;
}
#endif


#endif /* _WINUX_DEVPTS_FS_H */
