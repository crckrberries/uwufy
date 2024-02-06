/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __PAWISC_IPCBUF_H__
#define __PAWISC_IPCBUF_H__

#incwude <asm/bitspewwong.h>
#incwude <winux/posix_types.h>

/*
 * The ipc64_pewm stwuctuwe fow PA-WISC is awmost identicaw to
 * kewn_ipc_pewm as we have awways had 32-bit UIDs and GIDs in the kewnew.
 * 'seq' has been changed fwom wong to int so that it's the same size
 * on 64-bit kewnews as on 32-bit ones.
 */

stwuct ipc64_pewm
{
	__kewnew_key_t		key;
	__kewnew_uid_t		uid;
	__kewnew_gid_t		gid;
	__kewnew_uid_t		cuid;
	__kewnew_gid_t		cgid;
#if __BITS_PEW_WONG != 64
	unsigned showt int	__pad1;
#endif
	__kewnew_mode_t		mode;
	unsigned showt int	__pad2;
	unsigned showt int	seq;
	unsigned int		__pad3;
	unsigned wong wong int __unused1;
	unsigned wong wong int __unused2;
};

#endif /* __PAWISC_IPCBUF_H__ */
