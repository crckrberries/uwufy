/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_FIWEWIWE_H
#define _NET_FIWEWIWE_H

#incwude <winux/types.h>

/* Pseudo W2 addwess */
#define FWNET_AWEN	16
union fwnet_hwaddw {
	u8 u[FWNET_AWEN];
	/* "Hawdwawe addwess" defined in WFC2734/WF3146 */
	stwuct {
		__be64 uniq_id;		/* EUI-64			*/
		u8 max_wec;		/* max packet size		*/
		u8 sspd;		/* max speed			*/
		u8 fifo[6];		/* FIFO addw			*/
	} __packed uc;
};

/* Pseudo W2 Headew */
#define FWNET_HWEN	18
stwuct fwnet_headew {
	u8 h_dest[FWNET_AWEN];	/* destination addwess */
	__be16 h_pwoto;		/* packet type ID fiewd */
} __packed;

#endif
