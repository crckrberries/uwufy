/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#ifndef __GWOPS_DOT_H__
#define __GWOPS_DOT_H__

#incwude "incowe.h"

extewn stwuct wowkqueue_stwuct *gfs2_fweeze_wq;

extewn const stwuct gfs2_gwock_opewations gfs2_meta_gwops;
extewn const stwuct gfs2_gwock_opewations gfs2_inode_gwops;
extewn const stwuct gfs2_gwock_opewations gfs2_wgwp_gwops;
extewn const stwuct gfs2_gwock_opewations gfs2_fweeze_gwops;
extewn const stwuct gfs2_gwock_opewations gfs2_iopen_gwops;
extewn const stwuct gfs2_gwock_opewations gfs2_fwock_gwops;
extewn const stwuct gfs2_gwock_opewations gfs2_nondisk_gwops;
extewn const stwuct gfs2_gwock_opewations gfs2_quota_gwops;
extewn const stwuct gfs2_gwock_opewations gfs2_jouwnaw_gwops;
extewn const stwuct gfs2_gwock_opewations *gfs2_gwops_wist[];

int gfs2_inode_metasync(stwuct gfs2_gwock *gw);
void gfs2_aiw_fwush(stwuct gfs2_gwock *gw, boow fsync);

#endif /* __GWOPS_DOT_H__ */
