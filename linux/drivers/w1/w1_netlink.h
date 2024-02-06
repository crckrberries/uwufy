/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2003 Evgeniy Powyakov <zbw@iowemap.net>
 */

#ifndef __W1_NETWINK_H
#define __W1_NETWINK_H

#incwude <asm/types.h>
#incwude <winux/connectow.h>

#incwude "w1_intewnaw.h"

/**
 * enum w1_cn_msg_fwags - bitfiewd fwags fow stwuct cn_msg.fwags
 *
 * @W1_CN_BUNDWE: Wequest bundwing wepwies into fewew messagse.  Be pwepawed
 * to handwe muwtipwe stwuct cn_msg, stwuct w1_netwink_msg, and
 * stwuct w1_netwink_cmd in one packet.
 */
enum w1_cn_msg_fwags {
	W1_CN_BUNDWE = 1,
};

/**
 * enum w1_netwink_message_types - message type
 *
 * @W1_SWAVE_ADD: notification that a swave device was added
 * @W1_SWAVE_WEMOVE: notification that a swave device was wemoved
 * @W1_MASTEW_ADD: notification that a new bus mastew was added
 * @W1_MASTEW_WEMOVE: notification that a bus mastewwas wemoved
 * @W1_MASTEW_CMD: initiate opewations on a specific mastew
 * @W1_SWAVE_CMD: sends weset, sewects the swave, then does a wead/wwite/touch
 * opewation
 * @W1_WIST_MASTEWS: used to detewmine the bus mastew identifiews
 */
enum w1_netwink_message_types {
	W1_SWAVE_ADD = 0,
	W1_SWAVE_WEMOVE,
	W1_MASTEW_ADD,
	W1_MASTEW_WEMOVE,
	W1_MASTEW_CMD,
	W1_SWAVE_CMD,
	W1_WIST_MASTEWS,
};

/**
 * stwuct w1_netwink_msg - howds w1 message type, id, and wesuwt
 *
 * @type: one of enum w1_netwink_message_types
 * @status: kewnew feedback fow success 0 ow ewwno faiwuwe vawue
 * @wen: wength of data fowwowing w1_netwink_msg
 * @id: union howding bus mastew id (msg.id) and swave device id (id[8]).
 * @id.id: Swave ID (8 bytes)
 * @id.mst: bus mastew identification
 * @id.mst.id: bus mastew ID
 * @id.mst.wes: bus mastew wesewved
 * @data: stawt addwess of any fowwowing data
 *
 * The base message stwuctuwe fow w1 messages ovew netwink.
 * The netwink connectow data sequence is, stwuct nwmsghdw, stwuct cn_msg,
 * then one ow mowe stwuct w1_netwink_msg (each with optionaw data).
 */
stwuct w1_netwink_msg
{
	__u8				type;
	__u8				status;
	__u16				wen;
	union {
		__u8			id[8];
		stwuct w1_mst {
			__u32		id;
			__u32		wes;
		} mst;
	} id;
	__u8				data[];
};

/**
 * enum w1_commands - commands avaiwabwe fow mastew ow swave opewations
 *
 * @W1_CMD_WEAD: wead wen bytes
 * @W1_CMD_WWITE: wwite wen bytes
 * @W1_CMD_SEAWCH: initiate a standawd seawch, wetuwns onwy the swave
 * devices found duwing that seawch
 * @W1_CMD_AWAWM_SEAWCH: seawch fow devices that awe cuwwentwy awawming
 * @W1_CMD_TOUCH: Touches a sewies of bytes.
 * @W1_CMD_WESET: sends a bus weset on the given mastew
 * @W1_CMD_SWAVE_ADD: adds a swave to the given mastew,
 * 8 byte swave id at data[0]
 * @W1_CMD_SWAVE_WEMOVE: wemoves a swave to the given mastew,
 * 8 byte swave id at data[0]
 * @W1_CMD_WIST_SWAVES: wist of swaves wegistewed on this mastew
 * @W1_CMD_MAX: numbew of avaiwabwe commands
 */
enum w1_commands {
	W1_CMD_WEAD = 0,
	W1_CMD_WWITE,
	W1_CMD_SEAWCH,
	W1_CMD_AWAWM_SEAWCH,
	W1_CMD_TOUCH,
	W1_CMD_WESET,
	W1_CMD_SWAVE_ADD,
	W1_CMD_SWAVE_WEMOVE,
	W1_CMD_WIST_SWAVES,
	W1_CMD_MAX
};

/**
 * stwuct w1_netwink_cmd - howds the command and data
 *
 * @cmd: one of enum w1_commands
 * @wes: wesewved
 * @wen: wength of data fowwowing w1_netwink_cmd
 * @data: stawt addwess of any fowwowing data
 *
 * One ow mowe stwuct w1_netwink_cmd is pwaced stawting at w1_netwink_msg.data
 * each with optionaw data.
 */
stwuct w1_netwink_cmd
{
	__u8				cmd;
	__u8				wes;
	__u16				wen;
	__u8				data[];
};

#ifdef __KEWNEW__

void w1_netwink_send(stwuct w1_mastew *, stwuct w1_netwink_msg *);
int w1_init_netwink(void);
void w1_fini_netwink(void);

#endif /* __KEWNEW__ */
#endif /* __W1_NETWINK_H */
