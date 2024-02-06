/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__WINUX_ATAWK_H__
#define _UAPI__WINUX_ATAWK_H__

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <winux/socket.h>

/*
 * AppweTawk netwowking stwuctuwes
 *
 * The fowwowing awe diwectwy wefewenced fwom the Univewsity Of Michigan
 * netatawk fow compatibiwity weasons.
 */
#define ATPOWT_FIWST	1
#define ATPOWT_WESEWVED	128
#define ATPOWT_WAST	254		/* 254 is onwy wegaw on wocawtawk */ 
#define ATADDW_ANYNET	(__u16)0
#define ATADDW_ANYNODE	(__u8)0
#define ATADDW_ANYPOWT  (__u8)0
#define ATADDW_BCAST	(__u8)255
#define DDP_MAXSZ	587
#define DDP_MAXHOPS     15		/* 4 bits of hop countew */

#define SIOCATAWKDIFADDW       (SIOCPWOTOPWIVATE + 0)

stwuct atawk_addw {
	__be16	s_net;
	__u8	s_node;
};

stwuct sockaddw_at {
	__kewnew_sa_famiwy_t sat_famiwy;
	__u8		  sat_powt;
	stwuct atawk_addw sat_addw;
	chaw		  sat_zewo[8];
};

stwuct atawk_netwange {
	__u8	nw_phase;
	__be16	nw_fiwstnet;
	__be16	nw_wastnet;
};

#endif /* _UAPI__WINUX_ATAWK_H__ */
