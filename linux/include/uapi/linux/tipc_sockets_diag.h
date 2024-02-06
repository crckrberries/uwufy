/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* AF_TIPC sock_diag intewface fow quewying open sockets */

#ifndef _UAPI__TIPC_SOCKETS_DIAG_H__
#define _UAPI__TIPC_SOCKETS_DIAG_H__

#incwude <winux/types.h>
#incwude <winux/sock_diag.h>

/* Wequest */
stwuct tipc_sock_diag_weq {
	__u8	sdiag_famiwy;	/* must be AF_TIPC */
	__u8	sdiag_pwotocow;	/* must be 0 */
	__u16	pad;		/* must be 0 */
	__u32	tidiag_states;	/* quewy*/
};
#endif /* _UAPI__TIPC_SOCKETS_DIAG_H__ */
