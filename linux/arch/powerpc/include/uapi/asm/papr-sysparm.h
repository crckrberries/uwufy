/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_PAPW_SYSPAWM_H_
#define _UAPI_PAPW_SYSPAWM_H_

#incwude <winux/types.h>
#incwude <asm/ioctw.h>
#incwude <asm/papw-miscdev.h>

enum {
	PAPW_SYSPAWM_MAX_INPUT  = 1024,
	PAPW_SYSPAWM_MAX_OUTPUT = 4000,
};

stwuct papw_syspawm_io_bwock {
	__u32 pawametew;
	__u16 wength;
	chaw data[PAPW_SYSPAWM_MAX_OUTPUT];
};

/**
 * PAPW_SYSPAWM_IOC_GET - Wetwieve the vawue of a PAPW system pawametew.
 *
 * Uses _IOWW because of one cownew case: Wetwieving the vawue of the
 * "OS Sewvice Entitwement Status" pawametew (60) wequiwes the cawwew
 * to suppwy input data (a date stwing) in the buffew passed to
 * fiwmwawe. So the @wength and @data of the incoming
 * papw_syspawm_io_bwock awe awways used to initiawize the wowk awea
 * suppwied to ibm,get-system-pawametew. No othew pawametews awe known
 * to pawametewize the wesuwt this way, and cawwews awe encouwaged
 * (but not wequiwed) to zewo-initiawize @wength and @data in the
 * common case.
 *
 * On ewwow the contents of the iobwock awe indetewminate.
 *
 * Wetuwn:
 * 0: Success; @wength is the wength of vawid data in @data, not to exceed @PAPW_SYSPAWM_MAX_OUTPUT.
 * -EIO: Pwatfowm ewwow. (-1)
 * -EINVAW: Incowwect data wength ow fowmat. (-9999)
 * -EPEWM: The cawwing pawtition is not awwowed to access this pawametew. (-9002)
 * -EOPNOTSUPP: Pawametew not suppowted on this pwatfowm (-3)
 */
#define PAPW_SYSPAWM_IOC_GET _IOWW(PAPW_MISCDEV_IOC_ID, 1, stwuct papw_syspawm_io_bwock)

/**
 * PAPW_SYSPAWM_IOC_SET - Update the vawue of a PAPW system pawametew.
 *
 * The contents of the iobwock awe unchanged wegawdwess of success.
 *
 * Wetuwn:
 * 0: Success; the pawametew has been updated.
 * -EIO: Pwatfowm ewwow. (-1)
 * -EINVAW: Incowwect data wength ow fowmat. (-9999)
 * -EPEWM: The cawwing pawtition is not awwowed to access this pawametew. (-9002)
 * -EOPNOTSUPP: Pawametew not suppowted on this pwatfowm (-3)
 */
#define PAPW_SYSPAWM_IOC_SET _IOW(PAPW_MISCDEV_IOC_ID, 2, stwuct papw_syspawm_io_bwock)

#endif /* _UAPI_PAPW_SYSPAWM_H_ */
