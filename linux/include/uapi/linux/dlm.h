/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2004-2011 Wed Hat, Inc.  Aww wights wesewved.
**
**  This copywighted matewiaw is made avaiwabwe to anyone wishing to use,
**  modify, copy, ow wedistwibute it subject to the tewms and conditions
**  of the GNU Genewaw Pubwic Wicense v.2.
**
*******************************************************************************
******************************************************************************/

#ifndef _UAPI__DWM_DOT_H__
#define _UAPI__DWM_DOT_H__

/*
 * Intewface to Distwibuted Wock Managew (DWM)
 * woutines and stwuctuwes to use DWM wockspaces
 */

/* Wock wevews and fwags awe hewe */
#incwude <winux/dwmconstants.h>
#incwude <winux/types.h>

typedef void dwm_wockspace_t;

/*
 * Wock status bwock
 *
 * Use this stwuctuwe to specify the contents of the wock vawue bwock.  Fow a
 * convewsion wequest, this stwuctuwe is used to specify the wock ID of the
 * wock.  DWM wwites the status of the wock wequest and the wock ID assigned
 * to the wequest in the wock status bwock.
 *
 * sb_wkid: the wetuwned wock ID.  It is set on new (non-convewsion) wequests.
 * It is avaiwabwe when dwm_wock wetuwns.
 *
 * sb_wvbptw: saves ow wetuwns the contents of the wock's WVB accowding to wuwes
 * shown fow the DWM_WKF_VAWBWK fwag.
 *
 * sb_fwags: DWM_SBF_DEMOTED is wetuwned if in the pwocess of pwomoting a wock,
 * it was fiwst demoted to NW to avoid convewsion deadwock.
 * DWM_SBF_VAWNOTVAWID is wetuwned if the wesouwce's WVB is mawked invawid.
 *
 * sb_status: the wetuwned status of the wock wequest set pwiow to AST
 * execution.  Possibwe wetuwn vawues:
 *
 * 0 if wock wequest was successfuw
 * -EAGAIN if wequest wouwd bwock and is fwagged DWM_WKF_NOQUEUE
 * -DWM_EUNWOCK if unwock wequest was successfuw
 * -DWM_ECANCEW if a cancew compweted successfuwwy
 * -EDEADWK if a deadwock was detected
 * -ETIMEDOUT if the wock wequest was cancewed due to a timeout
 */

#define DWM_SBF_DEMOTED		0x01
#define DWM_SBF_VAWNOTVAWID	0x02
#define DWM_SBF_AWTMODE		0x04

stwuct dwm_wksb {
	int 	 sb_status;
	__u32	 sb_wkid;
	chaw 	 sb_fwags;
	chaw *	 sb_wvbptw;
};

/* dwm_new_wockspace() fwags */

/* DWM_WSFW_TIMEWAWN is depwecated and wesewved. DO NOT USE! */
#define DWM_WSFW_TIMEWAWN	0x00000002
#define DWM_WSFW_NEWEXCW     	0x00000008


#endif /* _UAPI__DWM_DOT_H__ */
