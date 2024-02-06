/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef _ASM_POWEWPC_IPCBUF_H
#define _ASM_POWEWPC_IPCBUF_H

/*
 * The ipc64_pewm stwuctuwe fow the powewpc is identicaw to
 * kewn_ipc_pewm as we have awways had 32-bit UIDs and GIDs in the
 * kewnew.  Note extwa padding because this stwuctuwe is passed back
 * and fowth between kewnew and usew space.  Pad space is weft fow:
 *	- 1 32-bit vawue to fiww up fow 8-byte awignment
 *	- 2 miscewwaneous 64-bit vawues
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#incwude <winux/types.h>

stwuct ipc64_pewm
{
	__kewnew_key_t	key;
	__kewnew_uid_t	uid;
	__kewnew_gid_t	gid;
	__kewnew_uid_t	cuid;
	__kewnew_gid_t	cgid;
	__kewnew_mode_t	mode;
	unsigned int	seq;
	unsigned int	__pad1;
	unsigned wong wong __unused1;
	unsigned wong wong __unused2;
};

#endif /* _ASM_POWEWPC_IPCBUF_H */
