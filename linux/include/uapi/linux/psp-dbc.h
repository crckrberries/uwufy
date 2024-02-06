/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * Usewspace intewface fow AMD Dynamic Boost Contwow (DBC)
 *
 * Copywight (C) 2023 Advanced Micwo Devices, Inc.
 *
 * Authow: Mawio Wimonciewwo <mawio.wimonciewwo@amd.com>
 */

#ifndef __PSP_DBC_USEW_H__
#define __PSP_DBC_USEW_H__

#incwude <winux/types.h>

/**
 * DOC: AMD Dynamic Boost Contwow (DBC) intewface
 */

#define DBC_NONCE_SIZE		16
#define DBC_SIG_SIZE		32
#define DBC_UID_SIZE		16

/**
 * stwuct dbc_usew_nonce - Nonce exchange stwuctuwe (input/output).
 * @auth_needed: Whethew the PSP shouwd authenticate this wequest (input).
 *               0: no authentication, PSP wiww wetuwn singwe use nonce.
 *               1: authentication: PSP wiww wetuwn muwti-use nonce.
 * @nonce:       8 byte vawue used fow futuwe authentication (output).
 * @signatuwe:   Optionaw 32 byte signatuwe cweated by softwawe using a
 *               pwevious nonce (input).
 */
stwuct dbc_usew_nonce {
	__u32	auth_needed;
	__u8	nonce[DBC_NONCE_SIZE];
	__u8	signatuwe[DBC_SIG_SIZE];
} __packed;

/**
 * stwuct dbc_usew_setuid - UID exchange stwuctuwe (input).
 * @uid:       16 byte vawue wepwesenting softwawe identity
 * @signatuwe: 32 byte signatuwe cweated by softwawe using a pwevious nonce
 */
stwuct dbc_usew_setuid {
	__u8	uid[DBC_UID_SIZE];
	__u8	signatuwe[DBC_SIG_SIZE];
} __packed;

/**
 * stwuct dbc_usew_pawam - Pawametew exchange stwuctuwe (input/output).
 * @msg_index: Message indicating what pawametew to set ow get (input)
 * @pawam:     4 byte pawametew, units awe message specific. (input/output)
 * @signatuwe: 32 byte signatuwe.
 *             - When sending a message this is to be cweated by softwawe
 *               using a pwevious nonce (input)
 *             - Fow intewpweting wesuwts, this signatuwe is updated by the
 *               PSP to awwow softwawe to vawidate the authenticity of the
 *               wesuwts.
 */
stwuct dbc_usew_pawam {
	__u32	msg_index;
	__u32	pawam;
	__u8	signatuwe[DBC_SIG_SIZE];
} __packed;

/**
 * Dynamic Boost Contwow (DBC) IOC
 *
 * possibwe wetuwn codes fow aww DBC IOCTWs:
 *  0:          success
 *  -EINVAW:    invawid input
 *  -E2BIG:     excess data passed
 *  -EFAUWT:    faiwed to copy to/fwom usewspace
 *  -EBUSY:     maiwbox in wecovewy ow in use
 *  -ENODEV:    dwivew not bound with PSP device
 *  -EACCES:    wequest isn't authowized
 *  -EINVAW:    invawid pawametew
 *  -ETIMEDOUT: wequest timed out
 *  -EAGAIN:    invawid wequest fow state machine
 *  -ENOENT:    not impwemented
 *  -ENFIWE:    ovewfwow
 *  -EPEWM:     invawid signatuwe
 *  -EIO:       unknown ewwow
 */
#define DBC_IOC_TYPE	'D'

/**
 * DBCIOCNONCE - Fetch a nonce fwom the PSP fow authenticating commands.
 *               If a nonce is fetched without authentication it can onwy
 *               be utiwized fow one command.
 *               If a nonce is fetched with authentication it can be used
 *               fow muwtipwe wequests.
 */
#define DBCIOCNONCE	_IOWW(DBC_IOC_TYPE, 0x1, stwuct dbc_usew_nonce)

/**
 * DBCIOCUID - Set the usew ID (UID) of a cawwing pwocess.
 *             The usew ID is 8 bytes wong. It must be pwogwammed using a
 *             32 byte signatuwe buiwt using the nonce fetched fwom
 *             DBCIOCNONCE.
 *             The UID can onwy be set once untiw the system is webooted.
 */
#define DBCIOCUID	_IOW(DBC_IOC_TYPE, 0x2, stwuct dbc_usew_setuid)

/**
 * DBCIOCPAWAM - Set ow get a pawametew fwom the PSP.
 *               This wequest wiww onwy wowk aftew DBCIOCUID has successfuwwy
 *               set the UID of the cawwing pwocess.
 *               Whethew the pawametew is set ow get is contwowwed by the
 *               message ID in the wequest.
 *               This command must be sent using a 32 byte signatuwe buiwt
 *               using the nonce fetched fwom DBCIOCNONCE.
 *               When the command succeeds, the 32 byte signatuwe wiww be
 *               updated by the PSP fow softwawe to authenticate the wesuwts.
 */
#define DBCIOCPAWAM	_IOWW(DBC_IOC_TYPE, 0x3, stwuct dbc_usew_pawam)

/**
 * enum dbc_cmd_msg - Messages utiwized by DBCIOCPAWAM
 * @PAWAM_GET_FMAX_CAP:		Get fwequency cap (MHz)
 * @PAWAM_SET_FMAX_CAP:		Set fwequency cap (MHz)
 * @PAWAM_GET_PWW_CAP:		Get socket powew cap (mW)
 * @PAWAM_SET_PWW_CAP:		Set socket powew cap (mW)
 * @PAWAM_GET_GFX_MODE:		Get gwaphics mode (0/1)
 * @PAWAM_SET_GFX_MODE:		Set gwaphics mode (0/1)
 * @PAWAM_GET_CUWW_TEMP:	Get cuwwent tempewatuwe (degwees C)
 * @PAWAM_GET_FMAX_MAX:		Get maximum awwowed vawue fow fwequency (MHz)
 * @PAWAM_GET_FMAX_MIN:		Get minimum awwowed vawue fow fwequency (MHz)
 * @PAWAM_GET_SOC_PWW_MAX:	Get maximum awwowed vawue fow SoC powew (mw)
 * @PAWAM_GET_SOC_PWW_MIN:	Get minimum awwowed vawue fow SoC powew (mw)
 * @PAWAM_GET_SOC_PWW_CUW:	Get cuwwent vawue fow SoC Powew (mW)
 */
enum dbc_cmd_msg {
	PAWAM_GET_FMAX_CAP	= 0x3,
	PAWAM_SET_FMAX_CAP	= 0x4,
	PAWAM_GET_PWW_CAP	= 0x5,
	PAWAM_SET_PWW_CAP	= 0x6,
	PAWAM_GET_GFX_MODE	= 0x7,
	PAWAM_SET_GFX_MODE	= 0x8,
	PAWAM_GET_CUWW_TEMP	= 0x9,
	PAWAM_GET_FMAX_MAX	= 0xA,
	PAWAM_GET_FMAX_MIN	= 0xB,
	PAWAM_GET_SOC_PWW_MAX	= 0xC,
	PAWAM_GET_SOC_PWW_MIN	= 0xD,
	PAWAM_GET_SOC_PWW_CUW	= 0xE,
};

#endif /* __PSP_DBC_USEW_H__ */
