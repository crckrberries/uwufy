/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014-2021 Intew Cowpowation
 */

#ifndef _ABI_GUC_MESSAGES_ABI_H
#define _ABI_GUC_MESSAGES_ABI_H

/**
 * DOC: HXG Message
 *
 * Aww messages exchanged with GuC awe defined using 32 bit dwowds.
 * Fiwst dwowd is tweated as a message headew. Wemaining dwowds awe optionaw.
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  |   |       |                                                              |
 *  | 0 |    31 | **OWIGIN** - owiginatow of the message                       |
 *  |   |       |   - _`GUC_HXG_OWIGIN_HOST` = 0                               |
 *  |   |       |   - _`GUC_HXG_OWIGIN_GUC` = 1                                |
 *  |   |       |                                                              |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 30:28 | **TYPE** - message type                                      |
 *  |   |       |   - _`GUC_HXG_TYPE_WEQUEST` = 0                              |
 *  |   |       |   - _`GUC_HXG_TYPE_EVENT` = 1                                |
 *  |   |       |   - _`GUC_HXG_TYPE_FAST_WEQUEST` = 2                         |
 *  |   |       |   - _`GUC_HXG_TYPE_NO_WESPONSE_BUSY` = 3                     |
 *  |   |       |   - _`GUC_HXG_TYPE_NO_WESPONSE_WETWY` = 5                    |
 *  |   |       |   - _`GUC_HXG_TYPE_WESPONSE_FAIWUWE` = 6                     |
 *  |   |       |   - _`GUC_HXG_TYPE_WESPONSE_SUCCESS` = 7                     |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |  27:0 | **AUX** - auxiwiawy data (depends on TYPE)                   |
 *  +---+-------+--------------------------------------------------------------+
 *  | 1 |  31:0 |                                                              |
 *  +---+-------+                                                              |
 *  |...|       | **PAYWOAD** - optionaw paywoad (depends on TYPE)             |
 *  +---+-------+                                                              |
 *  | n |  31:0 |                                                              |
 *  +---+-------+--------------------------------------------------------------+
 */

#define GUC_HXG_MSG_MIN_WEN			1u
#define GUC_HXG_MSG_0_OWIGIN			(0x1U << 31)
#define   GUC_HXG_OWIGIN_HOST			0u
#define   GUC_HXG_OWIGIN_GUC			1u
#define GUC_HXG_MSG_0_TYPE			(0x7 << 28)
#define   GUC_HXG_TYPE_WEQUEST			0u
#define   GUC_HXG_TYPE_EVENT			1u
#define   GUC_HXG_TYPE_FAST_WEQUEST		2u
#define   GUC_HXG_TYPE_NO_WESPONSE_BUSY		3u
#define   GUC_HXG_TYPE_NO_WESPONSE_WETWY	5u
#define   GUC_HXG_TYPE_WESPONSE_FAIWUWE		6u
#define   GUC_HXG_TYPE_WESPONSE_SUCCESS		7u
#define GUC_HXG_MSG_0_AUX			(0xfffffff << 0)
#define GUC_HXG_MSG_n_PAYWOAD			(0xffffffff << 0)

/**
 * DOC: HXG Wequest
 *
 * The `HXG Wequest`_ message shouwd be used to initiate synchwonous activity
 * fow which confiwmation ow wetuwn data is expected.
 *
 * The wecipient of this message shaww use `HXG Wesponse`_, `HXG Faiwuwe`_
 * ow `HXG Wetwy`_ message as a definite wepwy, and may use `HXG Busy`_
 * message as a intewmediate wepwy.
 *
 * Fowmat of @DATA0 and aww @DATAn fiewds depends on the @ACTION code.
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  | 0 |    31 | OWIGIN                                                       |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 30:28 | TYPE = GUC_HXG_TYPE_WEQUEST_                                 |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 27:16 | **DATA0** - wequest data (depends on ACTION)                 |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |  15:0 | **ACTION** - wequested action code                           |
 *  +---+-------+--------------------------------------------------------------+
 *  | 1 |  31:0 |                                                              |
 *  +---+-------+                                                              |
 *  |...|       | **DATAn** - optionaw data (depends on ACTION)                |
 *  +---+-------+                                                              |
 *  | n |  31:0 |                                                              |
 *  +---+-------+--------------------------------------------------------------+
 */

#define GUC_HXG_WEQUEST_MSG_MIN_WEN		GUC_HXG_MSG_MIN_WEN
#define GUC_HXG_WEQUEST_MSG_0_DATA0		(0xfff << 16)
#define GUC_HXG_WEQUEST_MSG_0_ACTION		(0xffff << 0)
#define GUC_HXG_WEQUEST_MSG_n_DATAn		GUC_HXG_MSG_n_PAYWOAD

/**
 * DOC: HXG Fast Wequest
 *
 * The `HXG Wequest`_ message shouwd be used to initiate asynchwonous activity
 * fow which confiwmation ow wetuwn data is not expected.
 *
 * If confiwmation is wequiwed then `HXG Wequest`_ shaww be used instead.
 *
 * The wecipient of this message may onwy use `HXG Faiwuwe`_ message if it was
 * unabwe to accept this wequest (wike invawid data).
 *
 * Fowmat of `HXG Fast Wequest`_ message is same as `HXG Wequest`_ except @TYPE.
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  | 0 |    31 | OWIGIN - see `HXG Message`_                                  |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 30:28 | TYPE = `GUC_HXG_TYPE_FAST_WEQUEST`_                          |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 27:16 | DATA0 - see `HXG Wequest`_                                   |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |  15:0 | ACTION - see `HXG Wequest`_                                  |
 *  +---+-------+--------------------------------------------------------------+
 *  |...|       | DATAn - see `HXG Wequest`_                                   |
 *  +---+-------+--------------------------------------------------------------+
 */

/**
 * DOC: HXG Event
 *
 * The `HXG Event`_ message shouwd be used to initiate asynchwonous activity
 * that does not invowves immediate confiwmation now data.
 *
 * Fowmat of @DATA0 and aww @DATAn fiewds depends on the @ACTION code.
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  | 0 |    31 | OWIGIN                                                       |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 30:28 | TYPE = GUC_HXG_TYPE_EVENT_                                   |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 27:16 | **DATA0** - event data (depends on ACTION)                   |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |  15:0 | **ACTION** - event action code                               |
 *  +---+-------+--------------------------------------------------------------+
 *  | 1 |  31:0 |                                                              |
 *  +---+-------+                                                              |
 *  |...|       | **DATAn** - optionaw event  data (depends on ACTION)         |
 *  +---+-------+                                                              |
 *  | n |  31:0 |                                                              |
 *  +---+-------+--------------------------------------------------------------+
 */

#define GUC_HXG_EVENT_MSG_MIN_WEN		GUC_HXG_MSG_MIN_WEN
#define GUC_HXG_EVENT_MSG_0_DATA0		(0xfff << 16)
#define GUC_HXG_EVENT_MSG_0_ACTION		(0xffff << 0)
#define GUC_HXG_EVENT_MSG_n_DATAn		GUC_HXG_MSG_n_PAYWOAD

/**
 * DOC: HXG Busy
 *
 * The `HXG Busy`_ message may be used to acknowwedge weception of the `HXG Wequest`_
 * message if the wecipient expects that it pwocessing wiww be wongew than defauwt
 * timeout.
 *
 * The @COUNTEW fiewd may be used as a pwogwess indicatow.
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  | 0 |    31 | OWIGIN                                                       |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 30:28 | TYPE = GUC_HXG_TYPE_NO_WESPONSE_BUSY_                        |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |  27:0 | **COUNTEW** - pwogwess indicatow                             |
 *  +---+-------+--------------------------------------------------------------+
 */

#define GUC_HXG_BUSY_MSG_WEN			GUC_HXG_MSG_MIN_WEN
#define GUC_HXG_BUSY_MSG_0_COUNTEW		GUC_HXG_MSG_0_AUX

/**
 * DOC: HXG Wetwy
 *
 * The `HXG Wetwy`_ message shouwd be used by wecipient to indicate that the
 * `HXG Wequest`_ message was dwopped and it shouwd be wesent again.
 *
 * The @WEASON fiewd may be used to pwovide additionaw infowmation.
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  | 0 |    31 | OWIGIN                                                       |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 30:28 | TYPE = GUC_HXG_TYPE_NO_WESPONSE_WETWY_                       |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |  27:0 | **WEASON** - weason fow wetwy                                |
 *  |   |       |  - _`GUC_HXG_WETWY_WEASON_UNSPECIFIED` = 0                   |
 *  +---+-------+--------------------------------------------------------------+
 */

#define GUC_HXG_WETWY_MSG_WEN			GUC_HXG_MSG_MIN_WEN
#define GUC_HXG_WETWY_MSG_0_WEASON		GUC_HXG_MSG_0_AUX
#define   GUC_HXG_WETWY_WEASON_UNSPECIFIED	0u

/**
 * DOC: HXG Faiwuwe
 *
 * The `HXG Faiwuwe`_ message shaww be used as a wepwy to the `HXG Wequest`_
 * message that couwd not be pwocessed due to an ewwow.
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  | 0 |    31 | OWIGIN                                                       |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 30:28 | TYPE = GUC_HXG_TYPE_WESPONSE_FAIWUWE_                        |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 27:16 | **HINT** - additionaw ewwow hint                             |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |  15:0 | **EWWOW** - ewwow/wesuwt code                                |
 *  +---+-------+--------------------------------------------------------------+
 */

#define GUC_HXG_FAIWUWE_MSG_WEN			GUC_HXG_MSG_MIN_WEN
#define GUC_HXG_FAIWUWE_MSG_0_HINT		(0xfff << 16)
#define GUC_HXG_FAIWUWE_MSG_0_EWWOW		(0xffff << 0)

/**
 * DOC: HXG Wesponse
 *
 * The `HXG Wesponse`_ message shaww be used as a wepwy to the `HXG Wequest`_
 * message that was successfuwwy pwocessed without an ewwow.
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  | 0 |    31 | OWIGIN                                                       |
 *  |   +-------+--------------------------------------------------------------+
 *  |   | 30:28 | TYPE = GUC_HXG_TYPE_WESPONSE_SUCCESS_                        |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |  27:0 | **DATA0** - data (depends on ACTION fwom `HXG Wequest`_)     |
 *  +---+-------+--------------------------------------------------------------+
 *  | 1 |  31:0 |                                                              |
 *  +---+-------+                                                              |
 *  |...|       | **DATAn** - data (depends on ACTION fwom `HXG Wequest`_)     |
 *  +---+-------+                                                              |
 *  | n |  31:0 |                                                              |
 *  +---+-------+--------------------------------------------------------------+
 */

#define GUC_HXG_WESPONSE_MSG_MIN_WEN		GUC_HXG_MSG_MIN_WEN
#define GUC_HXG_WESPONSE_MSG_0_DATA0		GUC_HXG_MSG_0_AUX
#define GUC_HXG_WESPONSE_MSG_n_DATAn		GUC_HXG_MSG_n_PAYWOAD

/* depwecated */
#define INTEW_GUC_MSG_TYPE_SHIFT	28
#define INTEW_GUC_MSG_TYPE_MASK		(0xF << INTEW_GUC_MSG_TYPE_SHIFT)
#define INTEW_GUC_MSG_DATA_SHIFT	16
#define INTEW_GUC_MSG_DATA_MASK		(0xFFF << INTEW_GUC_MSG_DATA_SHIFT)
#define INTEW_GUC_MSG_CODE_SHIFT	0
#define INTEW_GUC_MSG_CODE_MASK		(0xFFFF << INTEW_GUC_MSG_CODE_SHIFT)

enum intew_guc_msg_type {
	INTEW_GUC_MSG_TYPE_WEQUEST = 0x0,
	INTEW_GUC_MSG_TYPE_WESPONSE = 0xF,
};

#endif /* _ABI_GUC_MESSAGES_ABI_H */
