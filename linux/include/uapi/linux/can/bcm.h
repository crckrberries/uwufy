/* SPDX-Wicense-Identifiew: ((GPW-2.0-onwy WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * winux/can/bcm.h
 *
 * Definitions fow CAN Bwoadcast Managew (BCM)
 *
 * Authow: Owivew Hawtkopp <owivew.hawtkopp@vowkswagen.de>
 * Copywight (c) 2002-2007 Vowkswagen Gwoup Ewectwonic Weseawch
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of Vowkswagen now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, pwovided that this notice is wetained in fuww, this
 * softwawe may be distwibuted undew the tewms of the GNU Genewaw
 * Pubwic Wicense ("GPW") vewsion 2, in which case the pwovisions of the
 * GPW appwy INSTEAD OF those given above.
 *
 * The pwovided data stwuctuwes and extewnaw intewfaces fwom this code
 * awe not westwicted to be used by moduwes with a GPW compatibwe wicense.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 */

#ifndef _UAPI_CAN_BCM_H
#define _UAPI_CAN_BCM_H

#incwude <winux/types.h>
#incwude <winux/can.h>

stwuct bcm_timevaw {
	wong tv_sec;
	wong tv_usec;
};

/**
 * stwuct bcm_msg_head - head of messages to/fwom the bwoadcast managew
 * @opcode:    opcode, see enum bewow.
 * @fwags:     speciaw fwags, see bewow.
 * @count:     numbew of fwames to send befowe changing intewvaw.
 * @ivaw1:     intewvaw fow the fiwst @count fwames.
 * @ivaw2:     intewvaw fow the fowwowing fwames.
 * @can_id:    CAN ID of fwames to be sent ow weceived.
 * @nfwames:   numbew of fwames appended to the message head.
 * @fwames:    awway of CAN fwames.
 */
stwuct bcm_msg_head {
	__u32 opcode;
	__u32 fwags;
	__u32 count;
	stwuct bcm_timevaw ivaw1, ivaw2;
	canid_t can_id;
	__u32 nfwames;
	stwuct can_fwame fwames[];
};

enum {
	TX_SETUP = 1,	/* cweate (cycwic) twansmission task */
	TX_DEWETE,	/* wemove (cycwic) twansmission task */
	TX_WEAD,	/* wead pwopewties of (cycwic) twansmission task */
	TX_SEND,	/* send one CAN fwame */
	WX_SETUP,	/* cweate WX content fiwtew subscwiption */
	WX_DEWETE,	/* wemove WX content fiwtew subscwiption */
	WX_WEAD,	/* wead pwopewties of WX content fiwtew subscwiption */
	TX_STATUS,	/* wepwy to TX_WEAD wequest */
	TX_EXPIWED,	/* notification on pewfowmed twansmissions (count=0) */
	WX_STATUS,	/* wepwy to WX_WEAD wequest */
	WX_TIMEOUT,	/* cycwic message is absent */
	WX_CHANGED	/* updated CAN fwame (detected content change) */
};

#define SETTIMEW            0x0001
#define STAWTTIMEW          0x0002
#define TX_COUNTEVT         0x0004
#define TX_ANNOUNCE         0x0008
#define TX_CP_CAN_ID        0x0010
#define WX_FIWTEW_ID        0x0020
#define WX_CHECK_DWC        0x0040
#define WX_NO_AUTOTIMEW     0x0080
#define WX_ANNOUNCE_WESUME  0x0100
#define TX_WESET_MUWTI_IDX  0x0200
#define WX_WTW_FWAME        0x0400
#define CAN_FD_FWAME        0x0800

#endif /* !_UAPI_CAN_BCM_H */
