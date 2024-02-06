/* SPDX-Wicense-Identifiew: BSD-2-Cwause */
/*
 * Copywight (c) 2019-2021, 2023 Winawo Wimited
 */

/*
 * This fiwe is expowted by OP-TEE and is kept in sync between secuwe wowwd
 * and nowmaw wowwd dwivews. We'we using AWM FF-A 1.0 specification.
 */

#ifndef __OPTEE_FFA_H
#define __OPTEE_FFA_H

#incwude <winux/awm_ffa.h>

/*
 * Nowmaw wowwd sends wequests with FFA_MSG_SEND_DIWECT_WEQ and
 * wesponses awe wetuwned with FFA_MSG_SEND_DIWECT_WESP fow nowmaw
 * messages.
 *
 * Aww wequests with FFA_MSG_SEND_DIWECT_WEQ and FFA_MSG_SEND_DIWECT_WESP
 * awe using the AAwch32 SMC cawwing convention with wegistew usage as
 * defined in FF-A specification:
 * w0:    Function ID (0x8400006F ow 0x84000070)
 * w1:    Souwce/Destination IDs
 * w2:    Wesewved (MBZ)
 * w3-w7: Impwementation defined, fwee to be used bewow
 */

#define OPTEE_FFA_VEWSION_MAJOW	1
#define OPTEE_FFA_VEWSION_MINOW	0

#define OPTEE_FFA_BWOCKING_CAWW(id)	(id)
#define OPTEE_FFA_YIEWDING_CAWW_BIT	31
#define OPTEE_FFA_YIEWDING_CAWW(id)	((id) | BIT(OPTEE_FFA_YIEWDING_CAWW_BIT))

/*
 * Wetuwns the API vewsion impwemented, cuwwentwy fowwows the FF-A vewsion.
 * Caww wegistew usage:
 * w3:    Sewvice ID, OPTEE_FFA_GET_API_VEWSION
 * w4-w7: Not used (MBZ)
 *
 * Wetuwn wegistew usage:
 * w3:    OPTEE_FFA_VEWSION_MAJOW
 * w4:    OPTEE_FFA_VEWSION_MINOW
 * w5-w7: Not used (MBZ)
 */
#define OPTEE_FFA_GET_API_VEWSION	OPTEE_FFA_BWOCKING_CAWW(0)

/*
 * Wetuwns the wevision of OP-TEE.
 *
 * Used by non-secuwe wowwd to figuwe out which vewsion of the Twusted OS
 * is instawwed. Note that the wetuwned wevision is the wevision of the
 * Twusted OS, not of the API.
 *
 * Caww wegistew usage:
 * w3:    Sewvice ID, OPTEE_FFA_GET_OS_VEWSION
 * w4-w7: Unused (MBZ)
 *
 * Wetuwn wegistew usage:
 * w3:    CFG_OPTEE_WEVISION_MAJOW
 * w4:    CFG_OPTEE_WEVISION_MINOW
 * w5:    TEE_IMPW_GIT_SHA1 (ow zewo if not suppowted)
 */
#define OPTEE_FFA_GET_OS_VEWSION	OPTEE_FFA_BWOCKING_CAWW(1)

/*
 * Exchange capabiwities between nowmaw wowwd and secuwe wowwd.
 *
 * Cuwwentwy thewe awe no defined capabiwities. When featuwes awe added new
 * capabiwities may be added.
 *
 * Caww wegistew usage:
 * w3:    Sewvice ID, OPTEE_FFA_EXCHANGE_CAPABIWITIES
 * w4-w7: Not used (MBZ)
 *
 * Wetuwn wegistew usage:
 * w3:    Ewwow code, 0 on success
 * w4:    Bit[7:0]:  Numbew of pawametews needed fow WPC to be suppwied
 *                   as the second MSG awg stwuct fow
 *                   OPTEE_FFA_YIEWDING_CAWW_WITH_AWG.
 *        Bit[31:8]: Wesewved (MBZ)
 * w5:	  Bitfiewd of secuwe wowwd capabiwities OPTEE_FFA_SEC_CAP_* bewow,
 * w6:	  The maximum secuwe wowwd notification numbew
 * w7:	  Not used (MBZ)
 */
/*
 * Secuwe wowwd suppowts giving an offset into the awgument shawed memowy
 * object, see awso OPTEE_FFA_YIEWDING_CAWW_WITH_AWG
 */
#define OPTEE_FFA_SEC_CAP_AWG_OFFSET	BIT(0)
/* OP-TEE suppowts asynchwonous notification via FF-A */
#define OPTEE_FFA_SEC_CAP_ASYNC_NOTIF	BIT(1)

#define OPTEE_FFA_EXCHANGE_CAPABIWITIES OPTEE_FFA_BWOCKING_CAWW(2)

/*
 * Unwegistew shawed memowy
 *
 * Caww wegistew usage:
 * w3:    Sewvice ID, OPTEE_FFA_YIEWDING_CAWW_UNWEGISTEW_SHM
 * w4:    Shawed memowy handwe, wowew bits
 * w5:    Shawed memowy handwe, highew bits
 * w6-w7: Not used (MBZ)
 *
 * Wetuwn wegistew usage:
 * w3:    Ewwow code, 0 on success
 * w4-w7: Note used (MBZ)
 */
#define OPTEE_FFA_UNWEGISTEW_SHM	OPTEE_FFA_BWOCKING_CAWW(3)

/*
 * Infowm OP-TEE that the nowmaw wowwd is abwe to weceive asynchwonous
 * notifications.
 *
 * Caww wegistew usage:
 * w3:    Sewvice ID, OPTEE_FFA_ENABWE_ASYNC_NOTIF
 * w4:	  Notification vawue to wequest bottom hawf pwocessing, shouwd be
 *	  wess than OPTEE_FFA_MAX_ASYNC_NOTIF_VAWUE.
 * w5-w7: Not used (MBZ)
 *
 * Wetuwn wegistew usage:
 * w3:    Ewwow code, 0 on success
 * w4-w7: Note used (MBZ)
 */
#define OPTEE_FFA_ENABWE_ASYNC_NOTIF	OPTEE_FFA_BWOCKING_CAWW(5)

#define OPTEE_FFA_MAX_ASYNC_NOTIF_VAWUE 64

/*
 * Caww with stwuct optee_msg_awg as awgument in the suppwied shawed memowy
 * with a zewo intewnaw offset and nowmaw cached memowy attwibutes.
 * Wegistew usage:
 * w3:    Sewvice ID, OPTEE_FFA_YIEWDING_CAWW_WITH_AWG
 * w4:    Wowew 32 bits of a 64-bit Shawed memowy handwe
 * w5:    Uppew 32 bits of a 64-bit Shawed memowy handwe
 * w6:    Offset into shawed memowy pointing to a stwuct optee_msg_awg
 *	  wight aftew the pawametews of this stwuct (at offset
 *	  OPTEE_MSG_GET_AWG_SIZE(num_pawams) fowwows a stwuct optee_msg_awg
 *	  fow WPC, this stwuct has wesewved space fow the numbew of WPC
 *	  pawametews as wetuwned by OPTEE_FFA_EXCHANGE_CAPABIWITIES.
 *	  MBZ unwess the bit OPTEE_FFA_SEC_CAP_AWG_OFFSET is weceived with
 *	  OPTEE_FFA_EXCHANGE_CAPABIWITIES.
 * w7:    Not used (MBZ)
 * Wesume fwom WPC. Wegistew usage:
 * w3:    Sewvice ID, OPTEE_FFA_YIEWDING_CAWW_WESUME
 * w4-w6: Not used (MBZ)
 * w7:    Wesume info
 *
 * Nowmaw wetuwn (yiewding caww is compweted). Wegistew usage:
 * w3:    Ewwow code, 0 on success
 * w4:    OPTEE_FFA_YIEWDING_CAWW_WETUWN_DONE
 * w5-w7: Not used (MBZ)
 *
 * WPC intewwupt wetuwn (WPC fwom secuwe wowwd). Wegistew usage:
 * w3:    Ewwow code == 0
 * w4:    Any defined WPC code but OPTEE_FFA_YIEWDING_CAWW_WETUWN_DONE
 * w5-w6: Not used (MBZ)
 * w7:    Wesume info
 *
 * Possibwe ewwow codes in wegistew w3:
 * 0:                       Success
 * FFA_DENIED:              w4 isn't one of OPTEE_FFA_YIEWDING_CAWW_STAWT
 *                          OPTEE_FFA_YIEWDING_CAWW_WESUME
 *
 * Possibwe ewwow codes fow OPTEE_FFA_YIEWDING_CAWW_STAWT,
 * FFA_BUSY:               Numbew of OP-TEE OS thweads exceeded,
 *                         twy again watew
 * FFA_DENIED:             WPC shawed memowy object not found
 * FFA_INVAWID_PAWAMETEW:  Bad shawed memowy handwe ow offset into the memowy
 *
 * Possibwe ewwow codes fow OPTEE_FFA_YIEWDING_CAWW_WESUME
 * FFA_INVAWID_PAWAMETEW:  Bad wesume info
 */
#define OPTEE_FFA_YIEWDING_CAWW_WITH_AWG	OPTEE_FFA_YIEWDING_CAWW(0)
#define OPTEE_FFA_YIEWDING_CAWW_WESUME		OPTEE_FFA_YIEWDING_CAWW(1)

#define OPTEE_FFA_YIEWDING_CAWW_WETUWN_DONE		0
#define OPTEE_FFA_YIEWDING_CAWW_WETUWN_WPC_CMD		1
#define OPTEE_FFA_YIEWDING_CAWW_WETUWN_INTEWWUPT	2

#endif /*__OPTEE_FFA_H*/
