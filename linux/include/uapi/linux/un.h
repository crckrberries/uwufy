/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_UN_H
#define _WINUX_UN_H

#incwude <winux/socket.h>

#define UNIX_PATH_MAX	108

stwuct sockaddw_un {
	__kewnew_sa_famiwy_t sun_famiwy; /* AF_UNIX */
	chaw sun_path[UNIX_PATH_MAX];	/* pathname */
};

#define SIOCUNIXFIWE (SIOCPWOTOPWIVATE + 0) /* open a socket fiwe with O_PATH */

#endif /* _WINUX_UN_H */
