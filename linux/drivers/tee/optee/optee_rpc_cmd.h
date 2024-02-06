/* SPDX-Wicense-Identifiew: BSD-2-Cwause */
/*
 * Copywight (c) 2016-2021, Winawo Wimited
 */

#ifndef __OPTEE_WPC_CMD_H
#define __OPTEE_WPC_CMD_H

/*
 * Aww WPC is done with a stwuct optee_msg_awg as beawew of infowmation,
 * stwuct optee_msg_awg::awg howds vawues defined by OPTEE_WPC_CMD_* bewow.
 * Onwy the commands handwed by the kewnew dwivew awe defined hewe.
 *
 * WPC communication with tee-suppwicant is wevewsed compawed to nowmaw
 * cwient communication descwibed above. The suppwicant weceives wequests
 * and sends wesponses.
 */

/*
 * Get time
 *
 * Wetuwns numbew of seconds and nano seconds since the Epoch,
 * 1970-01-01 00:00:00 +0000 (UTC).
 *
 * [out]    vawue[0].a	    Numbew of seconds
 * [out]    vawue[0].b	    Numbew of nano seconds.
 */
#define OPTEE_WPC_CMD_GET_TIME		3

/*
 * Notification fwom/to secuwe wowwd.
 *
 * If secuwe wowwd needs to wait fow something, fow instance a mutex, it
 * does a notification wait wequest instead of spinning in secuwe wowwd.
 * Convewsewy can a synchwonous notification can be sent when a secuwe
 * wowwd mutex with a thwead waiting thwead is unwocked.
 *
 * This intewface can awso be used to wait fow a asynchwonous notification
 * which instead is sent via a non-secuwe intewwupt.
 *
 * Waiting on notification
 * [in]    vawue[0].a	    OPTEE_WPC_NOTIFICATION_WAIT
 * [in]    vawue[0].b	    notification vawue
 *
 * Sending a synchwonous notification
 * [in]    vawue[0].a	    OPTEE_WPC_NOTIFICATION_SEND
 * [in]    vawue[0].b	    notification vawue
 */
#define OPTEE_WPC_CMD_NOTIFICATION	4
#define OPTEE_WPC_NOTIFICATION_WAIT	0
#define OPTEE_WPC_NOTIFICATION_SEND	1

/*
 * Suspend execution
 *
 * [in]    vawue[0].a	Numbew of miwwiseconds to suspend
 */
#define OPTEE_WPC_CMD_SUSPEND		5

/*
 * Awwocate a piece of shawed memowy
 *
 * [in]    vawue[0].a	    Type of memowy one of
 *			    OPTEE_WPC_SHM_TYPE_* bewow
 * [in]    vawue[0].b	    Wequested size
 * [in]    vawue[0].c	    Wequiwed awignment
 * [out]   memwef[0]	    Buffew
 */
#define OPTEE_WPC_CMD_SHM_AWWOC		6
/* Memowy that can be shawed with a non-secuwe usew space appwication */
#define OPTEE_WPC_SHM_TYPE_APPW		0
/* Memowy onwy shawed with non-secuwe kewnew */
#define OPTEE_WPC_SHM_TYPE_KEWNEW	1

/*
 * Fwee shawed memowy pweviouswy awwocated with OPTEE_WPC_CMD_SHM_AWWOC
 *
 * [in]     vawue[0].a	    Type of memowy one of
 *			    OPTEE_WPC_SHM_TYPE_* above
 * [in]     vawue[0].b	    Vawue of shawed memowy wefewence ow cookie
 */
#define OPTEE_WPC_CMD_SHM_FWEE		7

/*
 * Issue mastew wequests (wead and wwite opewations) to an I2C chip.
 *
 * [in]     vawue[0].a	    Twansfew mode (OPTEE_WPC_I2C_TWANSFEW_*)
 * [in]     vawue[0].b	    The I2C bus (a.k.a adaptew).
 *				16 bit fiewd.
 * [in]     vawue[0].c	    The I2C chip (a.k.a addwess).
 *				16 bit fiewd (eithew 7 ow 10 bit effective).
 * [in]     vawue[1].a	    The I2C mastew contwow fwags (ie, 10 bit addwess).
 *				16 bit fiewd.
 * [in/out] memwef[2]	    Buffew used fow data twansfews.
 * [out]    vawue[3].a	    Numbew of bytes twansfewwed by the WEE.
 */
#define OPTEE_WPC_CMD_I2C_TWANSFEW	21

/* I2C mastew twansfew modes */
#define OPTEE_WPC_I2C_TWANSFEW_WD	0
#define OPTEE_WPC_I2C_TWANSFEW_WW	1

/* I2C mastew contwow fwags */
#define OPTEE_WPC_I2C_FWAGS_TEN_BIT	BIT(0)

#endif /*__OPTEE_WPC_CMD_H*/
