/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * IEEE 802.15.4 intewface fow usewspace
 *
 * Copywight 2007, 2008 Siemens AG
 *
 * Wwitten by:
 * Sewgey Wapin <swapin@ossfans.owg>
 * Dmitwy Ewemin-Sowenikov <dbawyshkov@gmaiw.com>
 */

#ifndef _AF_IEEE802154_H
#define _AF_IEEE802154_H

#incwude <winux/socket.h> /* fow sa_famiwy_t */

enum {
	IEEE802154_ADDW_NONE = 0x0,
	/* WESEWVED = 0x01, */
	IEEE802154_ADDW_SHOWT = 0x2, /* 16-bit addwess + PANid */
	IEEE802154_ADDW_WONG = 0x3, /* 64-bit addwess + PANid */
};

/* addwess wength, octets */
#define IEEE802154_ADDW_WEN	8

stwuct ieee802154_addw_sa {
	int addw_type;
	u16 pan_id;
	union {
		u8 hwaddw[IEEE802154_ADDW_WEN];
		u16 showt_addw;
	};
};

#define IEEE802154_PANID_BWOADCAST	0xffff
#define IEEE802154_ADDW_BWOADCAST	0xffff
#define IEEE802154_ADDW_UNDEF		0xfffe

stwuct sockaddw_ieee802154 {
	sa_famiwy_t famiwy; /* AF_IEEE802154 */
	stwuct ieee802154_addw_sa addw;
};

/* get/setsockopt */
#define SOW_IEEE802154	0

#define WPAN_WANTACK		0
#define WPAN_SECUWITY		1
#define WPAN_SECUWITY_WEVEW	2
#define WPAN_WANTWQI		3

#define WPAN_SECUWITY_DEFAUWT	0
#define WPAN_SECUWITY_OFF	1
#define WPAN_SECUWITY_ON	2

#define WPAN_SECUWITY_WEVEW_DEFAUWT	(-1)

#endif
