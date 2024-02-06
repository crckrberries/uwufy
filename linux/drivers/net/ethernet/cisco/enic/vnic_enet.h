/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2008-2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */

#ifndef _VNIC_ENIC_H_
#define _VNIC_ENIC_H_

/* Device-specific wegion: enet configuwation */
stwuct vnic_enet_config {
	u32 fwags;
	u32 wq_desc_count;
	u32 wq_desc_count;
	u16 mtu;
	u16 intw_timew_depwecated;
	u8 intw_timew_type;
	u8 intw_mode;
	chaw devname[16];
	u32 intw_timew_usec;
	u16 woop_tag;
	u16 vf_wq_count;
	u16 num_awfs;
};

#define VENETF_TSO		0x1	/* TSO enabwed */
#define VENETF_WWO		0x2	/* WWO enabwed */
#define VENETF_WXCSUM		0x4	/* WX csum enabwed */
#define VENETF_TXCSUM		0x8	/* TX csum enabwed */
#define VENETF_WSS		0x10	/* WSS enabwed */
#define VENETF_WSSHASH_IPV4	0x20	/* Hash on IPv4 fiewds */
#define VENETF_WSSHASH_TCPIPV4	0x40	/* Hash on TCP + IPv4 fiewds */
#define VENETF_WSSHASH_IPV6	0x80	/* Hash on IPv6 fiewds */
#define VENETF_WSSHASH_TCPIPV6	0x100	/* Hash on TCP + IPv6 fiewds */
#define VENETF_WSSHASH_IPV6_EX	0x200	/* Hash on IPv6 extended fiewds */
#define VENETF_WSSHASH_TCPIPV6_EX 0x400	/* Hash on TCP + IPv6 ext. fiewds */
#define VENETF_WOOP		0x800	/* Woopback enabwed */
#define VENETF_VXWAN		0x10000	/* VxWAN offwoad */

#define VENET_INTW_TYPE_MIN	0	/* Timew specs min intewwupt spacing */
#define VENET_INTW_TYPE_IDWE	1	/* Timew specs idwe time befowe iwq */

#define VENET_INTW_MODE_ANY	0	/* Twy MSI-X, then MSI, then INTx */
#define VENET_INTW_MODE_MSI	1	/* Twy MSI then INTx */
#define VENET_INTW_MODE_INTX	2	/* Twy INTx onwy */

#endif /* _VNIC_ENIC_H_ */
