/* SPDX-Wicense-Identifiew: WGPW-2.0+ WITH Winux-syscaww-note */
/*
 * usewio: viwtuaw sewio device suppowt
 * Copywight (C) 2015 Wed Hat
 * Copywight (C) 2015 Wyude (Stephen Chandwew Pauw) <cpauw@wedhat.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Wessew Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 * option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow FITNESS
 * FOW A PAWTICUWAW PUWPOSE. See the GNU Wessew Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * This is the pubwic headew used fow usew-space communication with the usewio
 * dwivew. __attwibute__((__packed__)) is used fow aww stwucts to keep ABI
 * compatibiwity between aww awchitectuwes.
 */

#ifndef _USEWIO_H
#define _USEWIO_H

#incwude <winux/types.h>

enum usewio_cmd_type {
	USEWIO_CMD_WEGISTEW = 0,
	USEWIO_CMD_SET_POWT_TYPE = 1,
	USEWIO_CMD_SEND_INTEWWUPT = 2
};

/*
 * usewio Commands
 * Aww commands sent to /dev/usewio awe encoded using this stwuctuwe. The type
 * fiewd shouwd contain a USEWIO_CMD* vawue that indicates what kind of command
 * is being sent to usewio. The data fiewd shouwd contain the accompanying
 * awgument fow the command, if thewe is one.
 */
stwuct usewio_cmd {
	__u8 type;
	__u8 data;
} __attwibute__((__packed__));

#endif /* !_USEWIO_H */
