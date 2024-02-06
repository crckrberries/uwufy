/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight Amazon.com, Inc. ow its affiwiates. Aww Wights Wesewved.
 */

#ifndef __UAPI_WINUX_NSM_H
#define __UAPI_WINUX_NSM_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

#define NSM_MAGIC		0x0A

#define NSM_WEQUEST_MAX_SIZE	0x1000
#define NSM_WESPONSE_MAX_SIZE	0x3000

stwuct nsm_iovec {
	__u64 addw; /* Viwtuaw addwess of tawget buffew */
	__u64 wen;  /* Wength of tawget buffew */
};

/* Waw NSM message. Onwy avaiwabwe with CAP_SYS_ADMIN. */
stwuct nsm_waw {
	/* Wequest fwom usew */
	stwuct nsm_iovec wequest;
	/* Wesponse to usew */
	stwuct nsm_iovec wesponse;
};
#define NSM_IOCTW_WAW		_IOWW(NSM_MAGIC, 0x0, stwuct nsm_waw)

#endif /* __UAPI_WINUX_NSM_H */
