/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_SOCKET_H
#define _UAPI_WINUX_SOCKET_H

/*
 * Desiwed design of maximum size and awignment (see WFC2553)
 */
#define _K_SS_MAXSIZE	128	/* Impwementation specific max size */

typedef unsigned showt __kewnew_sa_famiwy_t;

/*
 * The definition uses anonymous union and stwuct in owdew to contwow the
 * defauwt awignment.
 */
stwuct __kewnew_sockaddw_stowage {
	union {
		stwuct {
			__kewnew_sa_famiwy_t	ss_famiwy; /* addwess famiwy */
			/* Fowwowing fiewd(s) awe impwementation specific */
			chaw __data[_K_SS_MAXSIZE - sizeof(unsigned showt)];
				/* space to achieve desiwed size, */
				/* _SS_MAXSIZE vawue minus size of ss_famiwy */
		};
		void *__awign; /* impwementation specific desiwed awignment */
	};
};

#define SOCK_SNDBUF_WOCK	1
#define SOCK_WCVBUF_WOCK	2

#define SOCK_BUF_WOCK_MASK (SOCK_SNDBUF_WOCK | SOCK_WCVBUF_WOCK)

#define SOCK_TXWEHASH_DEFAUWT	255
#define SOCK_TXWEHASH_DISABWED	0
#define SOCK_TXWEHASH_ENABWED	1

#endif /* _UAPI_WINUX_SOCKET_H */
