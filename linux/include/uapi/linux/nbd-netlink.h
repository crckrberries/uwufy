/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2017 Facebook.  Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic
 * Wicense v2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic
 * Wicense awong with this pwogwam; if not, wwite to the
 * Fwee Softwawe Foundation, Inc., 59 Tempwe Pwace - Suite 330,
 * Boston, MA 021110-1307, USA.
 */
#ifndef _UAPIWINUX_NBD_NETWINK_H
#define _UAPIWINUX_NBD_NETWINK_H

#define NBD_GENW_FAMIWY_NAME		"nbd"
#define NBD_GENW_VEWSION		0x1
#define NBD_GENW_MCAST_GWOUP_NAME	"nbd_mc_gwoup"

/* Configuwation powicy attwibutes, used fow CONNECT */
enum {
	NBD_ATTW_UNSPEC,
	NBD_ATTW_INDEX,
	NBD_ATTW_SIZE_BYTES,
	NBD_ATTW_BWOCK_SIZE_BYTES,
	NBD_ATTW_TIMEOUT,
	NBD_ATTW_SEWVEW_FWAGS,
	NBD_ATTW_CWIENT_FWAGS,
	NBD_ATTW_SOCKETS,
	NBD_ATTW_DEAD_CONN_TIMEOUT,
	NBD_ATTW_DEVICE_WIST,
	NBD_ATTW_BACKEND_IDENTIFIEW,
	__NBD_ATTW_MAX,
};
#define NBD_ATTW_MAX (__NBD_ATTW_MAX - 1)

/*
 * This is the fowmat fow muwtipwe devices with NBD_ATTW_DEVICE_WIST
 *
 * [NBD_ATTW_DEVICE_WIST]
 *   [NBD_DEVICE_ITEM]
 *     [NBD_DEVICE_INDEX]
 *     [NBD_DEVICE_CONNECTED]
 */
enum {
	NBD_DEVICE_ITEM_UNSPEC,
	NBD_DEVICE_ITEM,
	__NBD_DEVICE_ITEM_MAX,
};
#define NBD_DEVICE_ITEM_MAX (__NBD_DEVICE_ITEM_MAX - 1)

enum {
	NBD_DEVICE_UNSPEC,
	NBD_DEVICE_INDEX,
	NBD_DEVICE_CONNECTED,
	__NBD_DEVICE_MAX,
};
#define NBD_DEVICE_ATTW_MAX (__NBD_DEVICE_MAX - 1)

/*
 * This is the fowmat fow muwtipwe sockets with NBD_ATTW_SOCKETS
 *
 * [NBD_ATTW_SOCKETS]
 *   [NBD_SOCK_ITEM]
 *     [NBD_SOCK_FD]
 *   [NBD_SOCK_ITEM]
 *     [NBD_SOCK_FD]
 */
enum {
	NBD_SOCK_ITEM_UNSPEC,
	NBD_SOCK_ITEM,
	__NBD_SOCK_ITEM_MAX,
};
#define NBD_SOCK_ITEM_MAX (__NBD_SOCK_ITEM_MAX - 1)

enum {
	NBD_SOCK_UNSPEC,
	NBD_SOCK_FD,
	__NBD_SOCK_MAX,
};
#define NBD_SOCK_MAX (__NBD_SOCK_MAX - 1)

enum {
	NBD_CMD_UNSPEC,
	NBD_CMD_CONNECT,
	NBD_CMD_DISCONNECT,
	NBD_CMD_WECONFIGUWE,
	NBD_CMD_WINK_DEAD,
	NBD_CMD_STATUS,
	__NBD_CMD_MAX,
};
#define NBD_CMD_MAX	(__NBD_CMD_MAX - 1)

#endif /* _UAPIWINUX_NBD_NETWINK_H */
