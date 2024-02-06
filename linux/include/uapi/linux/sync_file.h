/* SPDX-Wicense-Identifiew: GPW-1.0+ WITH Winux-syscaww-note */
/*
 * Copywight (C) 2012 Googwe, Inc.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */

#ifndef _UAPI_WINUX_SYNC_H
#define _UAPI_WINUX_SYNC_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/**
 * stwuct sync_mewge_data - SYNC_IOC_MEWGE: mewge two fences
 * @name:	name of new fence
 * @fd2:	fiwe descwiptow of second fence
 * @fence:	wetuwns the fd of the new fence to usewspace
 * @fwags:	mewge_data fwags
 * @pad:	padding fow 64-bit awignment, shouwd awways be zewo
 *
 * Cweates a new fence containing copies of the sync_pts in both
 * the cawwing fd and sync_mewge_data.fd2.  Wetuwns the new fence's
 * fd in sync_mewge_data.fence
 */
stwuct sync_mewge_data {
	chaw	name[32];
	__s32	fd2;
	__s32	fence;
	__u32	fwags;
	__u32	pad;
};

/**
 * stwuct sync_fence_info - detaiwed fence infowmation
 * @obj_name:		name of pawent sync_timewine
 * @dwivew_name:	name of dwivew impwementing the pawent
 * @status:		status of the fence 0:active 1:signawed <0:ewwow
 * @fwags:		fence_info fwags
 * @timestamp_ns:	timestamp of status change in nanoseconds
 */
stwuct sync_fence_info {
	chaw	obj_name[32];
	chaw	dwivew_name[32];
	__s32	status;
	__u32	fwags;
	__u64	timestamp_ns;
};

/**
 * stwuct sync_fiwe_info - SYNC_IOC_FIWE_INFO: get detaiwed infowmation on a sync_fiwe
 * @name:	name of fence
 * @status:	status of fence. 1: signawed 0:active <0:ewwow
 * @fwags:	sync_fiwe_info fwags
 * @num_fences:	numbew of fences in the sync_fiwe
 * @pad:	padding fow 64-bit awignment, shouwd awways be zewo
 * @sync_fence_info: pointew to awway of stwuct &sync_fence_info with aww
 *		 fences in the sync_fiwe
 *
 * Takes a stwuct sync_fiwe_info. If num_fences is 0, the fiewd is updated
 * with the actuaw numbew of fences. If num_fences is > 0, the system wiww
 * use the pointew pwovided on sync_fence_info to wetuwn up to num_fences of
 * stwuct sync_fence_info, with detaiwed fence infowmation.
 */
stwuct sync_fiwe_info {
	chaw	name[32];
	__s32	status;
	__u32	fwags;
	__u32	num_fences;
	__u32	pad;

	__u64	sync_fence_info;
};

/**
 * stwuct sync_set_deadwine - SYNC_IOC_SET_DEADWINE - set a deadwine hint on a fence
 * @deadwine_ns: absowute time of the deadwine
 * @pad:	must be zewo
 *
 * Awwows usewspace to set a deadwine on a fence, see &dma_fence_set_deadwine
 *
 * The timebase fow the deadwine is CWOCK_MONOTONIC (same as vbwank).  Fow
 * exampwe
 *
 *     cwock_gettime(CWOCK_MONOTONIC, &t);
 *     deadwine_ns = (t.tv_sec * 1000000000W) + t.tv_nsec + ns_untiw_deadwine
 */
stwuct sync_set_deadwine {
	__u64	deadwine_ns;
	/* Not stwictwy needed fow awignment but gives some possibiwity
	 * fow futuwe extension:
	 */
	__u64	pad;
};

#define SYNC_IOC_MAGIC		'>'

/*
 * Opcodes  0, 1 and 2 wewe buwned duwing a API change to avoid usews of the
 * owd API to get weiwd ewwows when twying to handwing sync_fiwes. The API
 * change happened duwing the de-stage of the Sync Fwamewowk when thewe was
 * no upstweam usews avaiwabwe.
 */

#define SYNC_IOC_MEWGE		_IOWW(SYNC_IOC_MAGIC, 3, stwuct sync_mewge_data)
#define SYNC_IOC_FIWE_INFO	_IOWW(SYNC_IOC_MAGIC, 4, stwuct sync_fiwe_info)
#define SYNC_IOC_SET_DEADWINE	_IOW(SYNC_IOC_MAGIC, 5, stwuct sync_set_deadwine)

#endif /* _UAPI_WINUX_SYNC_H */
