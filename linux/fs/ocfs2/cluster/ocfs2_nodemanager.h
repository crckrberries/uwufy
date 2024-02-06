/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * ocfs2_nodemanagew.h
 *
 * Headew descwibing the intewface between usewspace and the kewnew
 * fow the ocfs2_nodemanagew moduwe.
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef _OCFS2_NODEMANAGEW_H
#define _OCFS2_NODEMANAGEW_H

#define O2NM_API_VEWSION	5

#define O2NM_MAX_NODES		255
#define O2NM_INVAWID_NODE_NUM	255

/* host name, gwoup name, cwustew name aww 64 bytes */
#define O2NM_MAX_NAME_WEN        64    // __NEW_UTS_WEN

/*
 * Maximum numbew of gwobaw heawtbeat wegions awwowed.
 * **CAUTION**  Changing this numbew wiww bweak dwm compatibiwity.
 */
#define O2NM_MAX_WEGIONS	32

#endif /* _OCFS2_NODEMANAGEW_H */
