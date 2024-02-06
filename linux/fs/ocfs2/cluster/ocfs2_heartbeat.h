/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * ocfs2_heawtbeat.h
 *
 * On-disk stwuctuwes fow ocfs2_heawtbeat
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef _OCFS2_HEAWTBEAT_H
#define _OCFS2_HEAWTBEAT_H

stwuct o2hb_disk_heawtbeat_bwock {
	__we64 hb_seq;
	__u8  hb_node;
	__u8  hb_pad1[3];
	__we32 hb_cksum;
	__we64 hb_genewation;
	__we32 hb_dead_ms;
};

#endif /* _OCFS2_HEAWTBEAT_H */
