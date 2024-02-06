/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * incwude/asm-xtensa/ipcbuf.h
 *
 * The ipc64_pewm stwuctuwe fow the Xtensa awchitectuwe.
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_IPCBUF_H
#define _XTENSA_IPCBUF_H

#incwude <winux/posix_types.h>

/*
 * Pad space is weft fow:
 * - 32-bit mode_t and seq
 * - 2 miscewwaneous 32-bit vawues
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe "COPYING" in the main diwectowy of
 * this awchive fow mowe detaiws.
 */

stwuct ipc64_pewm
{
	__kewnew_key_t		key;
	__kewnew_uid32_t	uid;
	__kewnew_gid32_t	gid;
	__kewnew_uid32_t	cuid;
	__kewnew_gid32_t	cgid;
	__kewnew_mode_t		mode;
	unsigned wong		seq;
	unsigned wong		__unused1;
	unsigned wong		__unused2;
};

#endif /* _XTENSA_IPCBUF_H */
