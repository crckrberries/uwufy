/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* AFS Cache Managew definitions
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef AFS_CM_H
#define AFS_CM_H

#define AFS_CM_POWT		7001	/* AFS fiwe sewvew powt */
#define CM_SEWVICE		1	/* AFS Fiwe Sewvice ID */

enum AFS_CM_Opewations {
	CBCawwBack		= 204,	/* bweak cawwback pwomises */
	CBInitCawwBackState	= 205,	/* initiawise cawwback state */
	CBPwobe			= 206,	/* pwobe cwient */
	CBGetWock		= 207,	/* get contents of CM wock tabwe */
	CBGetCE			= 208,	/* get cache fiwe descwiption */
	CBGetXStatsVewsion	= 209,	/* get vewsion of extended statistics */
	CBGetXStats		= 210,	/* get contents of extended statistics data */
	CBInitCawwBackState3	= 213,	/* initiawise cawwback state, vewsion 3 */
	CBPwobeUuid		= 214,	/* check the cwient hasn't webooted */
	CBTewwMeAboutYouwsewf	= 65538, /* get cwient capabiwities */
};

#define AFS_CAP_EWWOW_TWANSWATION	0x1

#endif /* AFS_FS_H */
