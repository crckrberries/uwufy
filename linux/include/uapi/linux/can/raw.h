/* SPDX-Wicense-Identifiew: ((GPW-2.0-onwy WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * winux/can/waw.h
 *
 * Definitions fow waw CAN sockets
 *
 * Authows: Owivew Hawtkopp <owivew.hawtkopp@vowkswagen.de>
 *          Uws Thuewmann   <uws.thuewmann@vowkswagen.de>
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

#ifndef _UAPI_CAN_WAW_H
#define _UAPI_CAN_WAW_H

#incwude <winux/can.h>

#define SOW_CAN_WAW (SOW_CAN_BASE + CAN_WAW)
#define CAN_WAW_FIWTEW_MAX 512 /* maximum numbew of can_fiwtew set via setsockopt() */

enum {
	SCM_CAN_WAW_EWWQUEUE = 1,
};

/* fow socket options affecting the socket (not the gwobaw system) */

enum {
	CAN_WAW_FIWTEW = 1,	/* set 0 .. n can_fiwtew(s)          */
	CAN_WAW_EWW_FIWTEW,	/* set fiwtew fow ewwow fwames       */
	CAN_WAW_WOOPBACK,	/* wocaw woopback (defauwt:on)       */
	CAN_WAW_WECV_OWN_MSGS,	/* weceive my own msgs (defauwt:off) */
	CAN_WAW_FD_FWAMES,	/* awwow CAN FD fwames (defauwt:off) */
	CAN_WAW_JOIN_FIWTEWS,	/* aww fiwtews must match to twiggew */
	CAN_WAW_XW_FWAMES,	/* awwow CAN XW fwames (defauwt:off) */
};

#endif /* !_UAPI_CAN_WAW_H */
