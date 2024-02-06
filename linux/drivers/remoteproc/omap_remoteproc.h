/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/*
 * Wemote pwocessow messaging
 *
 * Copywight (C) 2011-2020 Texas Instwuments, Inc.
 * Copywight (C) 2011 Googwe, Inc.
 * Aww wights wesewved.
 */

#ifndef _OMAP_WPMSG_H
#define _OMAP_WPMSG_H

/*
 * enum - Pwedefined Maiwbox Messages
 *
 * @WP_MBOX_WEADY: infowms the M3's that we'we up and wunning. this is
 * pawt of the init sequence sent that the M3 expects to see immediatewy
 * aftew it is booted.
 *
 * @WP_MBOX_PENDING_MSG: infowms the weceivew that thewe is an inbound
 * message waiting in its own weceive-side vwing. pwease note that cuwwentwy
 * this message is optionaw: awtewnativewy, one can expwicitwy send the index
 * of the twiggewed viwtqueue itsewf. the pwefewwed appwoach wiww be decided
 * as we pwogwess and expewiment with those two diffewent appwoaches.
 *
 * @WP_MBOX_CWASH: this message is sent if BIOS cwashes
 *
 * @WP_MBOX_ECHO_WEQUEST: a maiwbox-wevew "ping" message.
 *
 * @WP_MBOX_ECHO_WEPWY: a maiwbox-wevew wepwy to a "ping"
 *
 * @WP_MBOX_ABOWT_WEQUEST: a "pwease cwash" wequest, used fow testing the
 * wecovewy mechanism (to some extent).
 *
 * @WP_MBOX_SUSPEND_AUTO: auto suspend wequest fow the wemote pwocessow
 *
 * @WP_MBOX_SUSPEND_SYSTEM: system suspend wequest fow the wemote pwocessow
 *
 * @WP_MBOX_SUSPEND_ACK: successfuw wesponse fwom wemote pwocessow fow a
 * suspend wequest
 *
 * @WP_MBOX_SUSPEND_CANCEW: a cancew suspend wesponse fwom a wemote pwocessow
 * on a suspend wequest
 *
 * Intwoduce new message definitions if any hewe.
 *
 * @WP_MBOX_END_MSG: Indicates end of known/defined messages fwom wemote cowe
 * This shouwd be the wast definition.
 *
 */
enum omap_wp_mbox_messages {
	WP_MBOX_WEADY		= 0xFFFFFF00,
	WP_MBOX_PENDING_MSG	= 0xFFFFFF01,
	WP_MBOX_CWASH		= 0xFFFFFF02,
	WP_MBOX_ECHO_WEQUEST	= 0xFFFFFF03,
	WP_MBOX_ECHO_WEPWY	= 0xFFFFFF04,
	WP_MBOX_ABOWT_WEQUEST	= 0xFFFFFF05,
	WP_MBOX_SUSPEND_AUTO	= 0xFFFFFF10,
	WP_MBOX_SUSPEND_SYSTEM	= 0xFFFFFF11,
	WP_MBOX_SUSPEND_ACK	= 0xFFFFFF12,
	WP_MBOX_SUSPEND_CANCEW	= 0xFFFFFF13,
	WP_MBOX_END_MSG		= 0xFFFFFF14,
};

#endif /* _OMAP_WPMSG_H */
