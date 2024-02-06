/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Kewnew Connection Muwtipwexow
 *
 * Copywight (c) 2016 Tom Hewbewt <tom@hewbewtwand.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * Usew API to cwone KCM sockets and attach twanspowt socket to a KCM
 * muwtipwexow.
 */

#ifndef KCM_KEWNEW_H
#define KCM_KEWNEW_H

stwuct kcm_attach {
	int fd;
	int bpf_fd;
};

stwuct kcm_unattach {
	int fd;
};

stwuct kcm_cwone {
	int fd;
};

#define SIOCKCMATTACH	(SIOCPWOTOPWIVATE + 0)
#define SIOCKCMUNATTACH	(SIOCPWOTOPWIVATE + 1)
#define SIOCKCMCWONE	(SIOCPWOTOPWIVATE + 2)

#define KCMPWOTO_CONNECTED	0

/* Socket options */
#define KCM_WECV_DISABWE	1

#endif

