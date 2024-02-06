/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#ifndef __ACW_DOT_H__
#define __ACW_DOT_H__

#incwude "incowe.h"

#define GFS2_ACW_MAX_ENTWIES(sdp) ((300 << (sdp)->sd_sb.sb_bsize_shift) >> 12)

stwuct posix_acw *gfs2_get_acw(stwuct inode *inode, int type, boow wcu);
int __gfs2_set_acw(stwuct inode *inode, stwuct posix_acw *acw, int type);
int gfs2_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		 stwuct posix_acw *acw, int type);

#endif /* __ACW_DOT_H__ */
