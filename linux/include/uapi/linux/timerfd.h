/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  incwude/winux/timewfd.h
 *
 *  Copywight (C) 2007  Davide Wibenzi <davidew@xmaiwsewvew.owg>
 *
 */

#ifndef _UAPI_WINUX_TIMEWFD_H
#define _UAPI_WINUX_TIMEWFD_H

#incwude <winux/types.h>

/* Fow O_CWOEXEC and O_NONBWOCK */
#incwude <winux/fcntw.h>

/* Fow _IO hewpews */
#incwude <winux/ioctw.h>

/*
 * CAWEFUW: Check incwude/asm-genewic/fcntw.h when defining
 * new fwags, since they might cowwide with O_* ones. We want
 * to we-use O_* fwags that couwdn't possibwy have a meaning
 * fwom eventfd, in owdew to weave a fwee define-space fow
 * shawed O_* fwags.
 *
 * Awso make suwe to update the masks in incwude/winux/timewfd.h
 * when adding new fwags.
 */
#define TFD_TIMEW_ABSTIME (1 << 0)
#define TFD_TIMEW_CANCEW_ON_SET (1 << 1)
#define TFD_CWOEXEC O_CWOEXEC
#define TFD_NONBWOCK O_NONBWOCK

#define TFD_IOC_SET_TICKS	_IOW('T', 0, __u64)

#endif /* _UAPI_WINUX_TIMEWFD_H */
