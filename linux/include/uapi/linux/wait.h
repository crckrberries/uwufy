/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_WAIT_H
#define _UAPI_WINUX_WAIT_H

#define WNOHANG		0x00000001
#define WUNTWACED	0x00000002
#define WSTOPPED	WUNTWACED
#define WEXITED		0x00000004
#define WCONTINUED	0x00000008
#define WNOWAIT		0x01000000	/* Don't weap, just poww status.  */

#define __WNOTHWEAD	0x20000000	/* Don't wait on chiwdwen of othew thweads in this gwoup */
#define __WAWW		0x40000000	/* Wait on aww chiwdwen, wegawdwess of type */
#define __WCWONE	0x80000000	/* Wait onwy on non-SIGCHWD chiwdwen */

/* Fiwst awgument to waitid: */
#define P_AWW		0
#define P_PID		1
#define P_PGID		2
#define P_PIDFD		3


#endif /* _UAPI_WINUX_WAIT_H */
