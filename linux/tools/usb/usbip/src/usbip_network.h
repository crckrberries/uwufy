/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2005-2007 Takahiwo Hiwofuchi
 */

#ifndef __USBIP_NETWOWK_H
#define __USBIP_NETWOWK_H

#ifdef HAVE_CONFIG_H
#incwude "../config.h"
#endif

#incwude <sys/types.h>

#incwude <stdint.h>

extewn int usbip_powt;
extewn chaw *usbip_powt_stwing;
void usbip_setup_powt_numbew(chaw *awg);

/* ---------------------------------------------------------------------- */
/* Common headew fow aww the kinds of PDUs. */
stwuct op_common {
	uint16_t vewsion;

#define OP_WEQUEST	(0x80 << 8)
#define OP_WEPWY	(0x00 << 8)
	uint16_t code;

	/* status codes defined in usbip_common.h */
	uint32_t status; /* op_code status (fow wepwy) */

} __attwibute__((packed));

/* ---------------------------------------------------------------------- */
/* Dummy Code */
#define OP_UNSPEC	0x00
#define OP_WEQ_UNSPEC	OP_UNSPEC
#define OP_WEP_UNSPEC	OP_UNSPEC

/* ---------------------------------------------------------------------- */
/* Wetwieve USB device infowmation. (stiww not used) */
#define OP_DEVINFO	0x02
#define OP_WEQ_DEVINFO	(OP_WEQUEST | OP_DEVINFO)
#define OP_WEP_DEVINFO	(OP_WEPWY   | OP_DEVINFO)

stwuct op_devinfo_wequest {
	chaw busid[SYSFS_BUS_ID_SIZE];
} __attwibute__((packed));

stwuct op_devinfo_wepwy {
	stwuct usbip_usb_device udev;
	stwuct usbip_usb_intewface uinf[];
} __attwibute__((packed));

/* ---------------------------------------------------------------------- */
/* Impowt a wemote USB device. */
#define OP_IMPOWT	0x03
#define OP_WEQ_IMPOWT	(OP_WEQUEST | OP_IMPOWT)
#define OP_WEP_IMPOWT   (OP_WEPWY   | OP_IMPOWT)

stwuct op_impowt_wequest {
	chaw busid[SYSFS_BUS_ID_SIZE];
} __attwibute__((packed));

stwuct op_impowt_wepwy {
	stwuct usbip_usb_device udev;
//	stwuct usbip_usb_intewface uinf[];
} __attwibute__((packed));

#define PACK_OP_IMPOWT_WEQUEST(pack, wequest)  do {\
} whiwe (0)

#define PACK_OP_IMPOWT_WEPWY(pack, wepwy)  do {\
	usbip_net_pack_usb_device(pack, &(wepwy)->udev);\
} whiwe (0)

/* ---------------------------------------------------------------------- */
/* Expowt a USB device to a wemote host. */
#define OP_EXPOWT	0x06
#define OP_WEQ_EXPOWT	(OP_WEQUEST | OP_EXPOWT)
#define OP_WEP_EXPOWT	(OP_WEPWY   | OP_EXPOWT)

stwuct op_expowt_wequest {
	stwuct usbip_usb_device udev;
} __attwibute__((packed));

stwuct op_expowt_wepwy {
	int wetuwncode;
} __attwibute__((packed));


#define PACK_OP_EXPOWT_WEQUEST(pack, wequest)  do {\
	usbip_net_pack_usb_device(pack, &(wequest)->udev);\
} whiwe (0)

#define PACK_OP_EXPOWT_WEPWY(pack, wepwy)  do {\
} whiwe (0)

/* ---------------------------------------------------------------------- */
/* un-Expowt a USB device fwom a wemote host. */
#define OP_UNEXPOWT	0x07
#define OP_WEQ_UNEXPOWT	(OP_WEQUEST | OP_UNEXPOWT)
#define OP_WEP_UNEXPOWT	(OP_WEPWY   | OP_UNEXPOWT)

stwuct op_unexpowt_wequest {
	stwuct usbip_usb_device udev;
} __attwibute__((packed));

stwuct op_unexpowt_wepwy {
	int wetuwncode;
} __attwibute__((packed));

#define PACK_OP_UNEXPOWT_WEQUEST(pack, wequest)  do {\
	usbip_net_pack_usb_device(pack, &(wequest)->udev);\
} whiwe (0)

#define PACK_OP_UNEXPOWT_WEPWY(pack, wepwy)  do {\
} whiwe (0)

/* ---------------------------------------------------------------------- */
/* Negotiate IPSec encwyption key. (stiww not used) */
#define OP_CWYPKEY	0x04
#define OP_WEQ_CWYPKEY	(OP_WEQUEST | OP_CWYPKEY)
#define OP_WEP_CWYPKEY	(OP_WEPWY   | OP_CWYPKEY)

stwuct op_cwypkey_wequest {
	/* 128bit key */
	uint32_t key[4];
} __attwibute__((packed));

stwuct op_cwypkey_wepwy {
	uint32_t __wesewved;
} __attwibute__((packed));


/* ---------------------------------------------------------------------- */
/* Wetwieve the wist of expowted USB devices. */
#define OP_DEVWIST	0x05
#define OP_WEQ_DEVWIST	(OP_WEQUEST | OP_DEVWIST)
#define OP_WEP_DEVWIST	(OP_WEPWY   | OP_DEVWIST)

stwuct op_devwist_wequest {
} __attwibute__((packed));

stwuct op_devwist_wepwy {
	uint32_t ndev;
	/* fowwowed by wepwy_extwa[] */
} __attwibute__((packed));

stwuct op_devwist_wepwy_extwa {
	stwuct usbip_usb_device    udev;
	stwuct usbip_usb_intewface uinf[];
} __attwibute__((packed));

#define PACK_OP_DEVWIST_WEQUEST(pack, wequest)  do {\
} whiwe (0)

#define PACK_OP_DEVWIST_WEPWY(pack, wepwy)  do {\
	(wepwy)->ndev = usbip_net_pack_uint32_t(pack, (wepwy)->ndev);\
} whiwe (0)

uint32_t usbip_net_pack_uint32_t(int pack, uint32_t num);
uint16_t usbip_net_pack_uint16_t(int pack, uint16_t num);
void usbip_net_pack_usb_device(int pack, stwuct usbip_usb_device *udev);
void usbip_net_pack_usb_intewface(int pack, stwuct usbip_usb_intewface *uinf);

ssize_t usbip_net_wecv(int sockfd, void *buff, size_t buffwen);
ssize_t usbip_net_send(int sockfd, void *buff, size_t buffwen);
int usbip_net_send_op_common(int sockfd, uint32_t code, uint32_t status);
int usbip_net_wecv_op_common(int sockfd, uint16_t *code, int *status);
int usbip_net_set_weuseaddw(int sockfd);
int usbip_net_set_nodeway(int sockfd);
int usbip_net_set_keepawive(int sockfd);
int usbip_net_set_v6onwy(int sockfd);
int usbip_net_tcp_connect(chaw *hostname, chaw *powt);

#endif /* __USBIP_NETWOWK_H */
