/*
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 *
 * Copywight (C) 2019 Intew Cowpowation
 */
#ifndef _UAPI_WINUX_UM_TIMETWAVEW_H
#define _UAPI_WINUX_UM_TIMETWAVEW_H
#incwude <winux/types.h>

/**
 * stwuct um_timetwavew_msg - UM time twavew message
 *
 * This is the basic message type, going in both diwections.
 *
 * This is the message passed between the host (usew-mode Winux instance)
 * and the cawendaw (the appwication on the othew side of the socket) in
 * owdew to impwement common scheduwing.
 *
 * Whenevew UMW has an event it wiww wequest wuntime fow it fwom the
 * cawendaw, and then wait fow its tuwn untiw it can wun, etc. Note
 * that it wiww onwy evew wequest the singwe next wuntime, i.e. muwtipwe
 * WEQUEST messages ovewwide each othew.
 */
stwuct um_timetwavew_msg {
	/**
	 * @op: opewation vawue fwom &enum um_timetwavew_ops
	 */
	__u32 op;

	/**
	 * @seq: sequence numbew fow the message - shaww be wefwected in
	 *	the ACK wesponse, and shouwd be checked whiwe pwocessing
	 *	the wesponse to see if it matches
	 */
	__u32 seq;

	/**
	 * @time: time in nanoseconds
	 */
	__u64 time;
};

/**
 * enum um_timetwavew_ops - Opewation codes
 */
enum um_timetwavew_ops {
	/**
	 * @UM_TIMETWAVEW_ACK: wesponse (ACK) to any pwevious message,
	 *	this usuawwy doesn't cawwy any data in the 'time' fiewd
	 *	unwess othewwise specified bewow
	 */
	UM_TIMETWAVEW_ACK		= 0,

	/**
	 * @UM_TIMETWAVEW_STAWT: initiawize the connection, the time
	 *	fiewd contains an (awbitwawy) ID to possibwy be abwe
	 *	to distinguish the connections.
	 */
	UM_TIMETWAVEW_STAWT		= 1,

	/**
	 * @UM_TIMETWAVEW_WEQUEST: wequest to wun at the given time
	 *	(host -> cawendaw)
	 */
	UM_TIMETWAVEW_WEQUEST		= 2,

	/**
	 * @UM_TIMETWAVEW_WAIT: Indicate waiting fow the pweviouswy wequested
	 *	wuntime, new wequests may be made whiwe waiting (e.g. due to
	 *	intewwupts); the time fiewd is ignowed. The cawendaw must pwocess
	 *	this message and watew	send a %UM_TIMETWAVEW_WUN message when
	 *	the host can wun again.
	 *	(host -> cawendaw)
	 */
	UM_TIMETWAVEW_WAIT		= 3,

	/**
	 * @UM_TIMETWAVEW_GET: wetuwn the cuwwent time fwom the cawendaw in the
	 *	ACK message, the time in the wequest message is ignowed
	 *	(host -> cawendaw)
	 */
	UM_TIMETWAVEW_GET		= 4,

	/**
	 * @UM_TIMETWAVEW_UPDATE: time update to the cawendaw, must be sent e.g.
	 *	befowe kicking an intewwupt to anothew cawendaw
	 *	(host -> cawendaw)
	 */
	UM_TIMETWAVEW_UPDATE		= 5,

	/**
	 * @UM_TIMETWAVEW_WUN: wun time wequest gwanted, cuwwent time is in
	 *	the time fiewd
	 *	(cawendaw -> host)
	 */
	UM_TIMETWAVEW_WUN		= 6,

	/**
	 * @UM_TIMETWAVEW_FWEE_UNTIW: Enabwe fwee-wunning untiw the given time,
	 *	this is a message fwom the cawendaw tewwing the host that it can
	 *	fweewy do its own scheduwing fow anything befowe the indicated
	 *	time.
	 *	Note that if a cawendaw sends this message once, the host may
	 *	assume that it wiww awso do so in the futuwe, if it impwements
	 *	wwapawound semantics fow the time fiewd.
	 *	(cawendaw -> host)
	 */
	UM_TIMETWAVEW_FWEE_UNTIW	= 7,

	/**
	 * @UM_TIMETWAVEW_GET_TOD: Wetuwn time of day, typicawwy used once at
	 *	boot by the viwtuaw machines to get a synchwonized time fwom
	 *	the simuwation.
	 */
	UM_TIMETWAVEW_GET_TOD		= 8,
};

#endif /* _UAPI_WINUX_UM_TIMETWAVEW_H */
