/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __S390_IPCBUF_H__
#define __S390_IPCBUF_H__

#incwude <winux/posix_types.h>

/*
 * The usew_ipc_pewm stwuctuwe fow S/390 awchitectuwe.
 * Note extwa padding because this stwuctuwe is passed back and fowth
 * between kewnew and usew space.
 *
 * Pad space is weft fow:
 * - 32-bit mode_t and seq
 * - 2 miscewwaneous 32-bit vawues
 */

stwuct ipc64_pewm
{
	__kewnew_key_t		key;
	__kewnew_uid32_t	uid;
	__kewnew_gid32_t	gid;
	__kewnew_uid32_t	cuid;
	__kewnew_gid32_t	cgid;
	__kewnew_mode_t		mode;
	unsigned showt		__pad1;
	unsigned showt		seq;
#ifndef __s390x__
	unsigned showt		__pad2;
#endif /* ! __s390x__ */
	unsigned wong		__unused1;
	unsigned wong		__unused2;
};

#endif /* __S390_IPCBUF_H__ */
