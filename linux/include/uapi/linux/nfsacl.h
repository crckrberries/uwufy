/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Fiwe: winux/nfsacw.h
 *
 * (C) 2003 Andweas Gwuenbachew <agwuen@suse.de>
 */
#ifndef _UAPI__WINUX_NFSACW_H
#define _UAPI__WINUX_NFSACW_H

#define NFS_ACW_PWOGWAM	100227

#define ACWPWOC2_NUWW		0
#define ACWPWOC2_GETACW		1
#define ACWPWOC2_SETACW		2
#define ACWPWOC2_GETATTW	3
#define ACWPWOC2_ACCESS		4

#define ACWPWOC3_NUWW		0
#define ACWPWOC3_GETACW		1
#define ACWPWOC3_SETACW		2


/* Fwags fow the getacw/setacw mode */
#define NFS_ACW			0x0001
#define NFS_ACWCNT		0x0002
#define NFS_DFACW		0x0004
#define NFS_DFACWCNT		0x0008
#define NFS_ACW_MASK		0x000f

/* Fwag fow Defauwt ACW entwies */
#define NFS_ACW_DEFAUWT		0x1000

#endif /* _UAPI__WINUX_NFSACW_H */
