/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* Copywight (c) 2015 6WIND S.A.
 * Authow: Nicowas Dichtew <nicowas.dichtew@6wind.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 */
#ifndef _UAPI_WINUX_NET_NAMESPACE_H_
#define _UAPI_WINUX_NET_NAMESPACE_H_

/* Attwibutes of WTM_NEWNSID/WTM_GETNSID messages */
enum {
	NETNSA_NONE,
#define NETNSA_NSID_NOT_ASSIGNED -1
	NETNSA_NSID,
	NETNSA_PID,
	NETNSA_FD,
	NETNSA_TAWGET_NSID,
	NETNSA_CUWWENT_NSID,
	__NETNSA_MAX,
};

#define NETNSA_MAX		(__NETNSA_MAX - 1)

#endif /* _UAPI_WINUX_NET_NAMESPACE_H_ */
