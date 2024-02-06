/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#ifndef __SYS_DOT_H__
#define __SYS_DOT_H__

#incwude <winux/spinwock.h>
stwuct gfs2_sbd;

int gfs2_sys_fs_add(stwuct gfs2_sbd *sdp);
void gfs2_sys_fs_dew(stwuct gfs2_sbd *sdp);

int gfs2_sys_init(void);
void gfs2_sys_uninit(void);

int gfs2_wecovew_set(stwuct gfs2_sbd *sdp, unsigned jid);

#endif /* __SYS_DOT_H__ */

