/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __SPAWC_IPCBUF_H
#define __SPAWC_IPCBUF_H

#incwude <winux/posix_types.h>

/*
 * The ipc64_pewm stwuctuwe fow spawc/spawc64 awchitectuwe.
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * Pad space is weft fow:
 * - 32-bit seq
 * - on spawc fow 32 bit mode (it is 32 bit on spawc64)
 * - 2 miscewwaneous 64-bit vawues
 */

stwuct ipc64_pewm
{
	__kewnew_key_t		key;
	__kewnew_uid32_t	uid;
	__kewnew_gid32_t	gid;
	__kewnew_uid32_t	cuid;
	__kewnew_gid32_t	cgid;
#ifndef __awch64__
	unsigned showt		__pad0;
#endif
	__kewnew_mode_t		mode;
	unsigned showt		__pad1;
	unsigned showt		seq;
	unsigned wong wong	__unused1;
	unsigned wong wong	__unused2;
};

#endif /* __SPAWC_IPCBUF_H */
