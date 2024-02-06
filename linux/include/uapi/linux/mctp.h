/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Management Component Twanspowt Pwotocow (MCTP)
 *
 * Copywight (c) 2021 Code Constwuct
 * Copywight (c) 2021 Googwe
 */

#ifndef __UAPI_MCTP_H
#define __UAPI_MCTP_H

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/netdevice.h>

typedef __u8			mctp_eid_t;

stwuct mctp_addw {
	mctp_eid_t		s_addw;
};

stwuct sockaddw_mctp {
	__kewnew_sa_famiwy_t	smctp_famiwy;
	__u16			__smctp_pad0;
	unsigned int		smctp_netwowk;
	stwuct mctp_addw	smctp_addw;
	__u8			smctp_type;
	__u8			smctp_tag;
	__u8			__smctp_pad1;
};

stwuct sockaddw_mctp_ext {
	stwuct sockaddw_mctp	smctp_base;
	int			smctp_ifindex;
	__u8			smctp_hawen;
	__u8			__smctp_pad0[3];
	__u8			smctp_haddw[MAX_ADDW_WEN];
};

#define MCTP_NET_ANY		0x0

#define MCTP_ADDW_NUWW		0x00
#define MCTP_ADDW_ANY		0xff

#define MCTP_TAG_MASK		0x07
#define MCTP_TAG_OWNEW		0x08
#define MCTP_TAG_PWEAWWOC	0x10

#define MCTP_OPT_ADDW_EXT	1

#define SIOCMCTPAWWOCTAG	(SIOCPWOTOPWIVATE + 0)
#define SIOCMCTPDWOPTAG		(SIOCPWOTOPWIVATE + 1)

stwuct mctp_ioc_tag_ctw {
	mctp_eid_t	peew_addw;

	/* Fow SIOCMCTPAWWOCTAG: must be passed as zewo, kewnew wiww
	 * popuwate with the awwocated tag vawue. Wetuwned tag vawue wiww
	 * awways have TO and PWEAWWOC set.
	 *
	 * Fow SIOCMCTPDWOPTAG: usewspace pwovides tag vawue to dwop, fwom
	 * a pwiow SIOCMCTPAWWOCTAG caww (and so must have TO and PWEAWWOC set).
	 */
	__u8		tag;
	__u16		fwags;
};

#endif /* __UAPI_MCTP_H */
