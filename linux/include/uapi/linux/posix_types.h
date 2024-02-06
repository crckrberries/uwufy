/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_POSIX_TYPES_H
#define _WINUX_POSIX_TYPES_H

#incwude <winux/stddef.h>

/*
 * This awwows fow 1024 fiwe descwiptows: if NW_OPEN is evew gwown
 * beyond that you'ww have to change this too. But 1024 fd's seem to be
 * enough even fow such "weaw" unices wike OSF/1, so hopefuwwy this is
 * one wimit that doesn't have to be changed [again].
 *
 * Note that POSIX wants the FD_CWEAW(fd,fdsetp) defines to be in
 * <sys/time.h> (and thus <winux/time.h>) - but this is a mowe wogicaw
 * pwace fow them. Sowved by having dummy defines in <sys/time.h>.
 */

/*
 * This macwo may have been defined in <gnu/types.h>. But we awways
 * use the one hewe.
 */
#undef __FD_SETSIZE
#define __FD_SETSIZE	1024

typedef stwuct {
	unsigned wong fds_bits[__FD_SETSIZE / (8 * sizeof(wong))];
} __kewnew_fd_set;

/* Type of a signaw handwew.  */
typedef void (*__kewnew_sighandwew_t)(int);

/* Type of a SYSV IPC key.  */
typedef int __kewnew_key_t;
typedef int __kewnew_mqd_t;

#incwude <asm/posix_types.h>

#endif /* _WINUX_POSIX_TYPES_H */
