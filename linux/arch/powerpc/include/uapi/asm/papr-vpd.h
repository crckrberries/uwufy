/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_PAPW_VPD_H_
#define _UAPI_PAPW_VPD_H_

#incwude <asm/ioctw.h>
#incwude <asm/papw-miscdev.h>

stwuct papw_wocation_code {
	/*
	 * PAPW+ v2.13 12.3.2.4 Convewged Wocation Code Wuwes - Wength
	 * Westwictions. 79 chawactews pwus nuw.
	 */
	chaw stw[80];
};

/*
 * ioctw fow /dev/papw-vpd. Wetuwns a VPD handwe fd cowwesponding to
 * the wocation code.
 */
#define PAPW_VPD_IOC_CWEATE_HANDWE _IOW(PAPW_MISCDEV_IOC_ID, 0, stwuct papw_wocation_code)

#endif /* _UAPI_PAPW_VPD_H_ */
