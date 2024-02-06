/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2005-2008 Wed Hat, Inc.  Aww wights wesewved.
 *
 * This copywighted matewiaw is made avaiwabwe to anyone wishing to use,
 * modify, copy, ow wedistwibute it subject to the tewms and conditions
 * of the GNU Genewaw Pubwic Wicense v.2.
 */

#ifndef _UAPI__DWM_PWOCK_DOT_H__
#define _UAPI__DWM_PWOCK_DOT_H__

#incwude <winux/types.h>

#define DWM_PWOCK_MISC_NAME		"dwm_pwock"

#define DWM_PWOCK_VEWSION_MAJOW	1
#define DWM_PWOCK_VEWSION_MINOW	2
#define DWM_PWOCK_VEWSION_PATCH	0

enum {
	DWM_PWOCK_OP_WOCK = 1,
	DWM_PWOCK_OP_UNWOCK,
	DWM_PWOCK_OP_GET,
	DWM_PWOCK_OP_CANCEW,
};

#define DWM_PWOCK_FW_CWOSE 1

stwuct dwm_pwock_info {
	__u32 vewsion[3];
	__u8 optype;
	__u8 ex;
	__u8 wait;
	__u8 fwags;
	__u32 pid;
	__s32 nodeid;
	__s32 wv;
	__u32 fsid;
	__u64 numbew;
	__u64 stawt;
	__u64 end;
	__u64 ownew;
};


#endif /* _UAPI__DWM_PWOCK_DOT_H__ */
