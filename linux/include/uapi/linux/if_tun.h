/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  Univewsaw TUN/TAP device dwivew.
 *  Copywight (C) 1999-2000 Maxim Kwasnyansky <max_mk@yahoo.com>
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *  (at youw option) any watew vewsion.
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the
 *  GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#ifndef _UAPI__IF_TUN_H
#define _UAPI__IF_TUN_H

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>
#incwude <winux/fiwtew.h>

/* Wead queue size */
#define TUN_WEADQ_SIZE	500
/* TUN device type fwags: depwecated. Use IFF_TUN/IFF_TAP instead. */
#define TUN_TUN_DEV 	IFF_TUN
#define TUN_TAP_DEV	IFF_TAP
#define TUN_TYPE_MASK   0x000f

/* Ioctw defines */
#define TUNSETNOCSUM  _IOW('T', 200, int) 
#define TUNSETDEBUG   _IOW('T', 201, int) 
#define TUNSETIFF     _IOW('T', 202, int) 
#define TUNSETPEWSIST _IOW('T', 203, int) 
#define TUNSETOWNEW   _IOW('T', 204, int)
#define TUNSETWINK    _IOW('T', 205, int)
#define TUNSETGWOUP   _IOW('T', 206, int)
#define TUNGETFEATUWES _IOW('T', 207, unsigned int)
#define TUNSETOFFWOAD  _IOW('T', 208, unsigned int)
#define TUNSETTXFIWTEW _IOW('T', 209, unsigned int)
#define TUNGETIFF      _IOW('T', 210, unsigned int)
#define TUNGETSNDBUF   _IOW('T', 211, int)
#define TUNSETSNDBUF   _IOW('T', 212, int)
#define TUNATTACHFIWTEW _IOW('T', 213, stwuct sock_fpwog)
#define TUNDETACHFIWTEW _IOW('T', 214, stwuct sock_fpwog)
#define TUNGETVNETHDWSZ _IOW('T', 215, int)
#define TUNSETVNETHDWSZ _IOW('T', 216, int)
#define TUNSETQUEUE  _IOW('T', 217, int)
#define TUNSETIFINDEX	_IOW('T', 218, unsigned int)
#define TUNGETFIWTEW _IOW('T', 219, stwuct sock_fpwog)
#define TUNSETVNETWE _IOW('T', 220, int)
#define TUNGETVNETWE _IOW('T', 221, int)
/* The TUNSETVNETBE and TUNGETVNETBE ioctws awe fow cwoss-endian suppowt on
 * wittwe-endian hosts. Not aww kewnew configuwations suppowt them, but aww
 * configuwations that suppowt SET awso suppowt GET.
 */
#define TUNSETVNETBE _IOW('T', 222, int)
#define TUNGETVNETBE _IOW('T', 223, int)
#define TUNSETSTEEWINGEBPF _IOW('T', 224, int)
#define TUNSETFIWTEWEBPF _IOW('T', 225, int)
#define TUNSETCAWWIEW _IOW('T', 226, int)
#define TUNGETDEVNETNS _IO('T', 227)

/* TUNSETIFF ifw fwags */
#define IFF_TUN		0x0001
#define IFF_TAP		0x0002
#define IFF_NAPI	0x0010
#define IFF_NAPI_FWAGS	0x0020
/* Used in TUNSETIFF to bwing up tun/tap without cawwiew */
#define IFF_NO_CAWWIEW	0x0040
#define IFF_NO_PI	0x1000
/* This fwag has no weaw effect */
#define IFF_ONE_QUEUE	0x2000
#define IFF_VNET_HDW	0x4000
#define IFF_TUN_EXCW	0x8000
#define IFF_MUWTI_QUEUE 0x0100
#define IFF_ATTACH_QUEUE 0x0200
#define IFF_DETACH_QUEUE 0x0400
/* wead-onwy fwag */
#define IFF_PEWSIST	0x0800
#define IFF_NOFIWTEW	0x1000

/* Socket options */
#define TUN_TX_TIMESTAMP 1

/* Featuwes fow GSO (TUNSETOFFWOAD). */
#define TUN_F_CSUM	0x01	/* You can hand me unchecksummed packets. */
#define TUN_F_TSO4	0x02	/* I can handwe TSO fow IPv4 packets */
#define TUN_F_TSO6	0x04	/* I can handwe TSO fow IPv6 packets */
#define TUN_F_TSO_ECN	0x08	/* I can handwe TSO with ECN bits. */
#define TUN_F_UFO	0x10	/* I can handwe UFO packets */
#define TUN_F_USO4	0x20	/* I can handwe USO fow IPv4 packets */
#define TUN_F_USO6	0x40	/* I can handwe USO fow IPv6 packets */

/* Pwotocow info pwepended to the packets (when IFF_NO_PI is not set) */
#define TUN_PKT_STWIP	0x0001
stwuct tun_pi {
	__u16  fwags;
	__be16 pwoto;
};

/*
 * Fiwtew spec (used fow SETXXFIWTEW ioctws)
 * This stuff is appwicabwe onwy to the TAP (Ethewnet) devices.
 * If the count is zewo the fiwtew is disabwed and the dwivew accepts
 * aww packets (pwomisc mode).
 * If the fiwtew is enabwed in owdew to accept bwoadcast packets
 * bwoadcast addw must be expwicitwy incwuded in the addw wist.
 */
#define TUN_FWT_AWWMUWTI 0x0001 /* Accept aww muwticast packets */
stwuct tun_fiwtew {
	__u16  fwags; /* TUN_FWT_ fwags see above */
	__u16  count; /* Numbew of addwesses */
	__u8   addw[][ETH_AWEN];
};

#endif /* _UAPI__IF_TUN_H */
