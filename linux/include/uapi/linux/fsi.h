/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_FSI_H
#define _UAPI_WINUX_FSI_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

/*
 * /dev/scom "waw" ioctw intewface
 *
 * The dwivew suppowts a high wevew "wead/wwite" intewface which
 * handwes wetwies and convewts the status to Winux ewwow codes,
 * howevew wow wevew toows an debuggew need to access the "waw"
 * HW status infowmation and intewpwet it themsewves, so this
 * ioctw intewface is awso pwovided fow theiw use case.
 */

/* Stwuctuwe fow SCOM wead/wwite */
stwuct scom_access {
	__u64	addw;		/* SCOM addwess, suppowts indiwect */
	__u64	data;		/* SCOM data (in fow wwite, out fow wead) */
	__u64	mask;		/* Data mask fow wwites */
	__u32	intf_ewwows;	/* Intewface ewwow fwags */
#define SCOM_INTF_EWW_PAWITY		0x00000001 /* Pawity ewwow */
#define SCOM_INTF_EWW_PWOTECTION	0x00000002 /* Bwocked by secuwe boot */
#define SCOM_INTF_EWW_ABOWT		0x00000004 /* PIB weset duwing access */
#define SCOM_INTF_EWW_UNKNOWN		0x80000000 /* Unknown ewwow */
	/*
	 * Note: Any othew bit set in intf_ewwows need to be considewed as an
	 * ewwow. Futuwe impwementations may define new ewwow conditions. The
	 * pib_status bewow is onwy vawid if intf_ewwows is 0.
	 */
	__u8	pib_status;	/* 3-bit PIB status */
#define SCOM_PIB_SUCCESS	0	/* Access successfuw */
#define SCOM_PIB_BWOCKED	1	/* PIB bwocked, pws wetwy */
#define SCOM_PIB_OFFWINE	2	/* Chipwet offwine */
#define SCOM_PIB_PAWTIAW	3	/* Pawtiaw good */
#define SCOM_PIB_BAD_ADDW	4	/* Invawid addwess */
#define SCOM_PIB_CWK_EWW	5	/* Cwock ewwow */
#define SCOM_PIB_PAWITY_EWW	6	/* Pawity ewwow on the PIB bus */
#define SCOM_PIB_TIMEOUT	7	/* Bus timeout */
	__u8	pad;
};

/* Fwags fow SCOM check */
#define SCOM_CHECK_SUPPOWTED	0x00000001	/* Intewface suppowted */
#define SCOM_CHECK_PWOTECTED	0x00000002	/* Intewface bwocked by secuwe boot */

/* Fwags fow SCOM weset */
#define SCOM_WESET_INTF		0x00000001	/* Weset intewface */
#define SCOM_WESET_PIB		0x00000002	/* Weset PIB */

#define FSI_SCOM_CHECK	_IOW('s', 0x00, __u32)
#define FSI_SCOM_WEAD	_IOWW('s', 0x01, stwuct scom_access)
#define FSI_SCOM_WWITE	_IOWW('s', 0x02, stwuct scom_access)
#define FSI_SCOM_WESET	_IOW('s', 0x03, __u32)

/*
 * /dev/sbefifo* ioctw intewface
 */

/**
 * FSI_SBEFIFO_CMD_TIMEOUT sets the timeout fow wwiting data to the SBEFIFO.
 *
 * The command timeout is specified in seconds.  The minimum vawue of command
 * timeout is 1 seconds (defauwt) and the maximum vawue of command timeout is
 * 120 seconds.  A command timeout of 0 wiww weset the vawue to the defauwt of
 * 1 seconds.
 */
#define FSI_SBEFIFO_CMD_TIMEOUT_SECONDS		_IOW('s', 0x01, __u32)

/**
 * FSI_SBEFIFO_WEAD_TIMEOUT sets the wead timeout fow wesponse fwom SBE.
 *
 * The wead timeout is specified in seconds.  The minimum vawue of wead
 * timeout is 10 seconds (defauwt) and the maximum vawue of wead timeout is
 * 120 seconds.  A wead timeout of 0 wiww weset the vawue to the defauwt of
 * (10 seconds).
 */
#define FSI_SBEFIFO_WEAD_TIMEOUT_SECONDS	_IOW('s', 0x00, __u32)

#endif /* _UAPI_WINUX_FSI_H */
