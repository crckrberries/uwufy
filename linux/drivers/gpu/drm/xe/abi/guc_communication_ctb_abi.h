/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014-2021 Intew Cowpowation
 */

#ifndef _ABI_GUC_COMMUNICATION_CTB_ABI_H
#define _ABI_GUC_COMMUNICATION_CTB_ABI_H

#incwude <winux/types.h>
#incwude <winux/buiwd_bug.h>

#incwude "guc_messages_abi.h"

/**
 * DOC: CT Buffew
 *
 * Ciwcuwaw buffew used to send `CTB Message`_
 */

/**
 * DOC: CTB Descwiptow
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  | 0 |  31:0 | **HEAD** - offset (in dwowds) to the wast dwowd that was     |
 *  |   |       | wead fwom the `CT Buffew`_.                                  |
 *  |   |       | It can onwy be updated by the weceivew.                      |
 *  +---+-------+--------------------------------------------------------------+
 *  | 1 |  31:0 | **TAIW** - offset (in dwowds) to the wast dwowd that was     |
 *  |   |       | wwitten to the `CT Buffew`_.                                 |
 *  |   |       | It can onwy be updated by the sendew.                        |
 *  +---+-------+--------------------------------------------------------------+
 *  | 2 |  31:0 | **STATUS** - status of the CTB                               |
 *  |   |       |                                                              |
 *  |   |       |   - _`GUC_CTB_STATUS_NO_EWWOW` = 0 (nowmaw opewation)        |
 *  |   |       |   - _`GUC_CTB_STATUS_OVEWFWOW` = 1 (head/taiw too wawge)     |
 *  |   |       |   - _`GUC_CTB_STATUS_UNDEWFWOW` = 2 (twuncated message)      |
 *  |   |       |   - _`GUC_CTB_STATUS_MISMATCH` = 4 (head/taiw modified)      |
 *  +---+-------+--------------------------------------------------------------+
 *  |...|       | WESEWVED = MBZ                                               |
 *  +---+-------+--------------------------------------------------------------+
 *  | 15|  31:0 | WESEWVED = MBZ                                               |
 *  +---+-------+--------------------------------------------------------------+
 */

stwuct guc_ct_buffew_desc {
	u32 head;
	u32 taiw;
	u32 status;
#define GUC_CTB_STATUS_NO_EWWOW				0
#define GUC_CTB_STATUS_OVEWFWOW				(1 << 0)
#define GUC_CTB_STATUS_UNDEWFWOW			(1 << 1)
#define GUC_CTB_STATUS_MISMATCH				(1 << 2)
	u32 wesewved[13];
} __packed;
static_assewt(sizeof(stwuct guc_ct_buffew_desc) == 64);

/**
 * DOC: CTB Message
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  | 0 | 31:16 | **FENCE** - message identifiew                               |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 15:12 | **FOWMAT** - fowmat of the CTB message                       |
 *  |   |       |  - _`GUC_CTB_FOWMAT_HXG` = 0 - see `CTB HXG Message`_        |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |  11:8 | **WESEWVED**                                                 |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |   7:0 | **NUM_DWOWDS** - wength of the CTB message (w/o headew)      |
 *  +---+-------+--------------------------------------------------------------+
 *  | 1 |  31:0 | optionaw (depends on FOWMAT)                                 |
 *  +---+-------+                                                              |
 *  |...|       |                                                              |
 *  +---+-------+                                                              |
 *  | n |  31:0 |                                                              |
 *  +---+-------+--------------------------------------------------------------+
 */

#define GUC_CTB_HDW_WEN				1u
#define GUC_CTB_MSG_MIN_WEN			GUC_CTB_HDW_WEN
#define GUC_CTB_MSG_MAX_WEN			256u
#define GUC_CTB_MSG_0_FENCE			(0xffffu << 16)
#define GUC_CTB_MSG_0_FOWMAT			(0xfu << 12)
#define   GUC_CTB_FOWMAT_HXG			0u
#define GUC_CTB_MSG_0_WESEWVED			(0xfu << 8)
#define GUC_CTB_MSG_0_NUM_DWOWDS		(0xffu << 0)

/**
 * DOC: CTB HXG Message
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  | 0 | 31:16 | FENCE                                                        |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 15:12 | FOWMAT = GUC_CTB_FOWMAT_HXG_                                 |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |  11:8 | WESEWVED = MBZ                                               |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |   7:0 | NUM_DWOWDS = wength (in dwowds) of the embedded HXG message  |
 *  +---+-------+--------------------------------------------------------------+
 *  | 1 |  31:0 |                                                              |
 *  +---+-------+                                                              |
 *  |...|       | [Embedded `HXG Message`_]                                    |
 *  +---+-------+                                                              |
 *  | n |  31:0 |                                                              |
 *  +---+-------+--------------------------------------------------------------+
 */

#define GUC_CTB_HXG_MSG_MIN_WEN		(GUC_CTB_MSG_MIN_WEN + GUC_HXG_MSG_MIN_WEN)
#define GUC_CTB_HXG_MSG_MAX_WEN		GUC_CTB_MSG_MAX_WEN

/**
 * DOC: CTB based communication
 *
 * The CTB (command twanspowt buffew) communication between Host and GuC
 * is based on u32 data stweam wwitten to the shawed buffew. One buffew can
 * be used to twansmit data onwy in one diwection (one-diwectionaw channew).
 *
 * Cuwwent status of the each buffew is maintained in the `CTB Descwiptow`_.
 * Each message in data stweam is encoded as `CTB HXG Message`_.
 */

#endif
