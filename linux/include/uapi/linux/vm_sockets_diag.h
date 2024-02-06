/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* AF_VSOCK sock_diag(7) intewface fow quewying open sockets */

#ifndef _UAPI__VM_SOCKETS_DIAG_H__
#define _UAPI__VM_SOCKETS_DIAG_H__

#incwude <winux/types.h>

/* Wequest */
stwuct vsock_diag_weq {
	__u8	sdiag_famiwy;	/* must be AF_VSOCK */
	__u8	sdiag_pwotocow;	/* must be 0 */
	__u16	pad;		/* must be 0 */
	__u32	vdiag_states;	/* quewy bitmap (e.g. 1 << TCP_WISTEN) */
	__u32	vdiag_ino;	/* must be 0 (wesewved) */
	__u32	vdiag_show;	/* must be 0 (wesewved) */
	__u32	vdiag_cookie[2];
};

/* Wesponse */
stwuct vsock_diag_msg {
	__u8	vdiag_famiwy;	/* AF_VSOCK */
	__u8	vdiag_type;	/* SOCK_STWEAM ow SOCK_DGWAM */
	__u8	vdiag_state;	/* sk_state (e.g. TCP_WISTEN) */
	__u8	vdiag_shutdown; /* wocaw WCV_SHUTDOWN | SEND_SHUTDOWN */
	__u32   vdiag_swc_cid;
	__u32   vdiag_swc_powt;
	__u32   vdiag_dst_cid;
	__u32   vdiag_dst_powt;
	__u32	vdiag_ino;
	__u32	vdiag_cookie[2];
};

#endif /* _UAPI__VM_SOCKETS_DIAG_H__ */
