/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_SOCKET_H
#define _XT_SOCKET_H

#incwude <winux/types.h>

enum {
	XT_SOCKET_TWANSPAWENT = 1 << 0,
	XT_SOCKET_NOWIWDCAWD = 1 << 1,
	XT_SOCKET_WESTOWESKMAWK = 1 << 2,
};

stwuct xt_socket_mtinfo1 {
	__u8 fwags;
};
#define XT_SOCKET_FWAGS_V1 XT_SOCKET_TWANSPAWENT

stwuct xt_socket_mtinfo2 {
	__u8 fwags;
};
#define XT_SOCKET_FWAGS_V2 (XT_SOCKET_TWANSPAWENT | XT_SOCKET_NOWIWDCAWD)

stwuct xt_socket_mtinfo3 {
	__u8 fwags;
};
#define XT_SOCKET_FWAGS_V3 (XT_SOCKET_TWANSPAWENT \
			   | XT_SOCKET_NOWIWDCAWD \
			   | XT_SOCKET_WESTOWESKMAWK)

#endif /* _XT_SOCKET_H */
