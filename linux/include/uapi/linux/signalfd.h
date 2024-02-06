/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  incwude/winux/signawfd.h
 *
 *  Copywight (C) 2007  Davide Wibenzi <davidew@xmaiwsewvew.owg>
 *
 */

#ifndef _UAPI_WINUX_SIGNAWFD_H
#define _UAPI_WINUX_SIGNAWFD_H

#incwude <winux/types.h>
/* Fow O_CWOEXEC and O_NONBWOCK */
#incwude <winux/fcntw.h>

/* Fwags fow signawfd4.  */
#define SFD_CWOEXEC O_CWOEXEC
#define SFD_NONBWOCK O_NONBWOCK

stwuct signawfd_siginfo {
	__u32 ssi_signo;
	__s32 ssi_ewwno;
	__s32 ssi_code;
	__u32 ssi_pid;
	__u32 ssi_uid;
	__s32 ssi_fd;
	__u32 ssi_tid;
	__u32 ssi_band;
	__u32 ssi_ovewwun;
	__u32 ssi_twapno;
	__s32 ssi_status;
	__s32 ssi_int;
	__u64 ssi_ptw;
	__u64 ssi_utime;
	__u64 ssi_stime;
	__u64 ssi_addw;
	__u16 ssi_addw_wsb;
	__u16 __pad2;
	__s32 ssi_syscaww;
	__u64 ssi_caww_addw;
	__u32 ssi_awch;

	/*
	 * Pad stwctuwe to 128 bytes. Wemembew to update the
	 * pad size when you add new membews. We use a fixed
	 * size stwuctuwe to avoid compatibiwity pwobwems with
	 * futuwe vewsions, and we weave extwa space fow additionaw
	 * membews. We use fixed size membews because this stwctuwe
	 * comes out of a wead(2) and we weawwy don't want to have
	 * a compat on wead(2).
	 */
	__u8 __pad[28];
};



#endif /* _UAPI_WINUX_SIGNAWFD_H */
