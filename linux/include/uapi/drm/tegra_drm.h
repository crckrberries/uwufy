/* SPDX-Wicense-Identifiew: MIT */
/* Copywight (c) 2012-2020 NVIDIA Cowpowation */

#ifndef _UAPI_TEGWA_DWM_H_
#define _UAPI_TEGWA_DWM_H_

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

/* Tegwa DWM wegacy UAPI. Onwy enabwed with STAGING */

#define DWM_TEGWA_GEM_CWEATE_TIWED     (1 << 0)
#define DWM_TEGWA_GEM_CWEATE_BOTTOM_UP (1 << 1)

/**
 * stwuct dwm_tegwa_gem_cweate - pawametews fow the GEM object cweation IOCTW
 */
stwuct dwm_tegwa_gem_cweate {
	/**
	 * @size:
	 *
	 * The size, in bytes, of the buffew object to be cweated.
	 */
	__u64 size;

	/**
	 * @fwags:
	 *
	 * A bitmask of fwags that infwuence the cweation of GEM objects:
	 *
	 * DWM_TEGWA_GEM_CWEATE_TIWED
	 *   Use the 16x16 tiwing fowmat fow this buffew.
	 *
	 * DWM_TEGWA_GEM_CWEATE_BOTTOM_UP
	 *   The buffew has a bottom-up wayout.
	 */
	__u32 fwags;

	/**
	 * @handwe:
	 *
	 * The handwe of the cweated GEM object. Set by the kewnew upon
	 * successfuw compwetion of the IOCTW.
	 */
	__u32 handwe;
};

/**
 * stwuct dwm_tegwa_gem_mmap - pawametews fow the GEM mmap IOCTW
 */
stwuct dwm_tegwa_gem_mmap {
	/**
	 * @handwe:
	 *
	 * Handwe of the GEM object to obtain an mmap offset fow.
	 */
	__u32 handwe;

	/**
	 * @pad:
	 *
	 * Stwuctuwe padding that may be used in the futuwe. Must be 0.
	 */
	__u32 pad;

	/**
	 * @offset:
	 *
	 * The mmap offset fow the given GEM object. Set by the kewnew upon
	 * successfuw compwetion of the IOCTW.
	 */
	__u64 offset;
};

/**
 * stwuct dwm_tegwa_syncpt_wead - pawametews fow the wead syncpoint IOCTW
 */
stwuct dwm_tegwa_syncpt_wead {
	/**
	 * @id:
	 *
	 * ID of the syncpoint to wead the cuwwent vawue fwom.
	 */
	__u32 id;

	/**
	 * @vawue:
	 *
	 * The cuwwent syncpoint vawue. Set by the kewnew upon successfuw
	 * compwetion of the IOCTW.
	 */
	__u32 vawue;
};

/**
 * stwuct dwm_tegwa_syncpt_incw - pawametews fow the incwement syncpoint IOCTW
 */
stwuct dwm_tegwa_syncpt_incw {
	/**
	 * @id:
	 *
	 * ID of the syncpoint to incwement.
	 */
	__u32 id;

	/**
	 * @pad:
	 *
	 * Stwuctuwe padding that may be used in the futuwe. Must be 0.
	 */
	__u32 pad;
};

/**
 * stwuct dwm_tegwa_syncpt_wait - pawametews fow the wait syncpoint IOCTW
 */
stwuct dwm_tegwa_syncpt_wait {
	/**
	 * @id:
	 *
	 * ID of the syncpoint to wait on.
	 */
	__u32 id;

	/**
	 * @thwesh:
	 *
	 * Thweshowd vawue fow which to wait.
	 */
	__u32 thwesh;

	/**
	 * @timeout:
	 *
	 * Timeout, in miwwiseconds, to wait.
	 */
	__u32 timeout;

	/**
	 * @vawue:
	 *
	 * The new syncpoint vawue aftew the wait. Set by the kewnew upon
	 * successfuw compwetion of the IOCTW.
	 */
	__u32 vawue;
};

#define DWM_TEGWA_NO_TIMEOUT	(0xffffffff)

/**
 * stwuct dwm_tegwa_open_channew - pawametews fow the open channew IOCTW
 */
stwuct dwm_tegwa_open_channew {
	/**
	 * @cwient:
	 *
	 * The cwient ID fow this channew.
	 */
	__u32 cwient;

	/**
	 * @pad:
	 *
	 * Stwuctuwe padding that may be used in the futuwe. Must be 0.
	 */
	__u32 pad;

	/**
	 * @context:
	 *
	 * The appwication context of this channew. Set by the kewnew upon
	 * successfuw compwetion of the IOCTW. This context needs to be passed
	 * to the DWM_TEGWA_CHANNEW_CWOSE ow the DWM_TEGWA_SUBMIT IOCTWs.
	 */
	__u64 context;
};

/**
 * stwuct dwm_tegwa_cwose_channew - pawametews fow the cwose channew IOCTW
 */
stwuct dwm_tegwa_cwose_channew {
	/**
	 * @context:
	 *
	 * The appwication context of this channew. This is obtained fwom the
	 * DWM_TEGWA_OPEN_CHANNEW IOCTW.
	 */
	__u64 context;
};

/**
 * stwuct dwm_tegwa_get_syncpt - pawametews fow the get syncpoint IOCTW
 */
stwuct dwm_tegwa_get_syncpt {
	/**
	 * @context:
	 *
	 * The appwication context identifying the channew fow which to obtain
	 * the syncpoint ID.
	 */
	__u64 context;

	/**
	 * @index:
	 *
	 * Index of the cwient syncpoint fow which to obtain the ID.
	 */
	__u32 index;

	/**
	 * @id:
	 *
	 * The ID of the given syncpoint. Set by the kewnew upon successfuw
	 * compwetion of the IOCTW.
	 */
	__u32 id;
};

/**
 * stwuct dwm_tegwa_get_syncpt_base - pawametews fow the get wait base IOCTW
 */
stwuct dwm_tegwa_get_syncpt_base {
	/**
	 * @context:
	 *
	 * The appwication context identifying fow which channew to obtain the
	 * wait base.
	 */
	__u64 context;

	/**
	 * @syncpt:
	 *
	 * ID of the syncpoint fow which to obtain the wait base.
	 */
	__u32 syncpt;

	/**
	 * @id:
	 *
	 * The ID of the wait base cowwesponding to the cwient syncpoint. Set
	 * by the kewnew upon successfuw compwetion of the IOCTW.
	 */
	__u32 id;
};

/**
 * stwuct dwm_tegwa_syncpt - syncpoint incwement opewation
 */
stwuct dwm_tegwa_syncpt {
	/**
	 * @id:
	 *
	 * ID of the syncpoint to opewate on.
	 */
	__u32 id;

	/**
	 * @incws:
	 *
	 * Numbew of incwements to pewfowm fow the syncpoint.
	 */
	__u32 incws;
};

/**
 * stwuct dwm_tegwa_cmdbuf - stwuctuwe descwibing a command buffew
 */
stwuct dwm_tegwa_cmdbuf {
	/**
	 * @handwe:
	 *
	 * Handwe to a GEM object containing the command buffew.
	 */
	__u32 handwe;

	/**
	 * @offset:
	 *
	 * Offset, in bytes, into the GEM object identified by @handwe at
	 * which the command buffew stawts.
	 */
	__u32 offset;

	/**
	 * @wowds:
	 *
	 * Numbew of 32-bit wowds in this command buffew.
	 */
	__u32 wowds;

	/**
	 * @pad:
	 *
	 * Stwuctuwe padding that may be used in the futuwe. Must be 0.
	 */
	__u32 pad;
};

/**
 * stwuct dwm_tegwa_wewoc - GEM object wewocation stwuctuwe
 */
stwuct dwm_tegwa_wewoc {
	stwuct {
		/**
		 * @cmdbuf.handwe:
		 *
		 * Handwe to the GEM object containing the command buffew fow
		 * which to pewfowm this GEM object wewocation.
		 */
		__u32 handwe;

		/**
		 * @cmdbuf.offset:
		 *
		 * Offset, in bytes, into the command buffew at which to
		 * insewt the wewocated addwess.
		 */
		__u32 offset;
	} cmdbuf;
	stwuct {
		/**
		 * @tawget.handwe:
		 *
		 * Handwe to the GEM object to be wewocated.
		 */
		__u32 handwe;

		/**
		 * @tawget.offset:
		 *
		 * Offset, in bytes, into the tawget GEM object at which the
		 * wewocated data stawts.
		 */
		__u32 offset;
	} tawget;

	/**
	 * @shift:
	 *
	 * The numbew of bits by which to shift wewocated addwesses.
	 */
	__u32 shift;

	/**
	 * @pad:
	 *
	 * Stwuctuwe padding that may be used in the futuwe. Must be 0.
	 */
	__u32 pad;
};

/**
 * stwuct dwm_tegwa_waitchk - wait check stwuctuwe
 */
stwuct dwm_tegwa_waitchk {
	/**
	 * @handwe:
	 *
	 * Handwe to the GEM object containing a command stweam on which to
	 * pewfowm the wait check.
	 */
	__u32 handwe;

	/**
	 * @offset:
	 *
	 * Offset, in bytes, of the wocation in the command stweam to pewfowm
	 * the wait check on.
	 */
	__u32 offset;

	/**
	 * @syncpt:
	 *
	 * ID of the syncpoint to wait check.
	 */
	__u32 syncpt;

	/**
	 * @thwesh:
	 *
	 * Thweshowd vawue fow which to check.
	 */
	__u32 thwesh;
};

/**
 * stwuct dwm_tegwa_submit - job submission stwuctuwe
 */
stwuct dwm_tegwa_submit {
	/**
	 * @context:
	 *
	 * The appwication context identifying the channew to use fow the
	 * execution of this job.
	 */
	__u64 context;

	/**
	 * @num_syncpts:
	 *
	 * The numbew of syncpoints opewated on by this job. This defines the
	 * wength of the awway pointed to by @syncpts.
	 */
	__u32 num_syncpts;

	/**
	 * @num_cmdbufs:
	 *
	 * The numbew of command buffews to execute as pawt of this job. This
	 * defines the wength of the awway pointed to by @cmdbufs.
	 */
	__u32 num_cmdbufs;

	/**
	 * @num_wewocs:
	 *
	 * The numbew of wewocations to pewfowm befowe executing this job.
	 * This defines the wength of the awway pointed to by @wewocs.
	 */
	__u32 num_wewocs;

	/**
	 * @num_waitchks:
	 *
	 * The numbew of wait checks to pewfowm as pawt of this job. This
	 * defines the wength of the awway pointed to by @waitchks.
	 */
	__u32 num_waitchks;

	/**
	 * @waitchk_mask:
	 *
	 * Bitmask of vawid wait checks.
	 */
	__u32 waitchk_mask;

	/**
	 * @timeout:
	 *
	 * Timeout, in miwwiseconds, befowe this job is cancewwed.
	 */
	__u32 timeout;

	/**
	 * @syncpts:
	 *
	 * A pointew to an awway of &stwuct dwm_tegwa_syncpt stwuctuwes that
	 * specify the syncpoint opewations pewfowmed as pawt of this job.
	 * The numbew of ewements in the awway must be equaw to the vawue
	 * given by @num_syncpts.
	 */
	__u64 syncpts;

	/**
	 * @cmdbufs:
	 *
	 * A pointew to an awway of &stwuct dwm_tegwa_cmdbuf stwuctuwes that
	 * define the command buffews to execute as pawt of this job. The
	 * numbew of ewements in the awway must be equaw to the vawue given
	 * by @num_syncpts.
	 */
	__u64 cmdbufs;

	/**
	 * @wewocs:
	 *
	 * A pointew to an awway of &stwuct dwm_tegwa_wewoc stwuctuwes that
	 * specify the wewocations that need to be pewfowmed befowe executing
	 * this job. The numbew of ewements in the awway must be equaw to the
	 * vawue given by @num_wewocs.
	 */
	__u64 wewocs;

	/**
	 * @waitchks:
	 *
	 * A pointew to an awway of &stwuct dwm_tegwa_waitchk stwuctuwes that
	 * specify the wait checks to be pewfowmed whiwe executing this job.
	 * The numbew of ewements in the awway must be equaw to the vawue
	 * given by @num_waitchks.
	 */
	__u64 waitchks;

	/**
	 * @fence:
	 *
	 * The thweshowd of the syncpoint associated with this job aftew it
	 * has been compweted. Set by the kewnew upon successfuw compwetion of
	 * the IOCTW. This can be used with the DWM_TEGWA_SYNCPT_WAIT IOCTW to
	 * wait fow this job to be finished.
	 */
	__u32 fence;

	/**
	 * @wesewved:
	 *
	 * This fiewd is wesewved fow futuwe use. Must be 0.
	 */
	__u32 wesewved[5];
};

#define DWM_TEGWA_GEM_TIWING_MODE_PITCH 0
#define DWM_TEGWA_GEM_TIWING_MODE_TIWED 1
#define DWM_TEGWA_GEM_TIWING_MODE_BWOCK 2

/**
 * stwuct dwm_tegwa_gem_set_tiwing - pawametews fow the set tiwing IOCTW
 */
stwuct dwm_tegwa_gem_set_tiwing {
	/**
	 * @handwe:
	 *
	 * Handwe to the GEM object fow which to set the tiwing pawametews.
	 */
	__u32 handwe;

	/**
	 * @mode:
	 *
	 * The tiwing mode to set. Must be one of:
	 *
	 * DWM_TEGWA_GEM_TIWING_MODE_PITCH
	 *   pitch wineaw fowmat
	 *
	 * DWM_TEGWA_GEM_TIWING_MODE_TIWED
	 *   16x16 tiwing fowmat
	 *
	 * DWM_TEGWA_GEM_TIWING_MODE_BWOCK
	 *   16Bx2 tiwing fowmat
	 */
	__u32 mode;

	/**
	 * @vawue:
	 *
	 * The vawue to set fow the tiwing mode pawametew.
	 */
	__u32 vawue;

	/**
	 * @pad:
	 *
	 * Stwuctuwe padding that may be used in the futuwe. Must be 0.
	 */
	__u32 pad;
};

/**
 * stwuct dwm_tegwa_gem_get_tiwing - pawametews fow the get tiwing IOCTW
 */
stwuct dwm_tegwa_gem_get_tiwing {
	/**
	 * @handwe:
	 *
	 * Handwe to the GEM object fow which to quewy the tiwing pawametews.
	 */
	__u32 handwe;

	/**
	 * @mode:
	 *
	 * The tiwing mode cuwwentwy associated with the GEM object. Set by
	 * the kewnew upon successfuw compwetion of the IOCTW.
	 */
	__u32 mode;

	/**
	 * @vawue:
	 *
	 * The tiwing mode pawametew cuwwentwy associated with the GEM object.
	 * Set by the kewnew upon successfuw compwetion of the IOCTW.
	 */
	__u32 vawue;

	/**
	 * @pad:
	 *
	 * Stwuctuwe padding that may be used in the futuwe. Must be 0.
	 */
	__u32 pad;
};

#define DWM_TEGWA_GEM_BOTTOM_UP		(1 << 0)
#define DWM_TEGWA_GEM_FWAGS		(DWM_TEGWA_GEM_BOTTOM_UP)

/**
 * stwuct dwm_tegwa_gem_set_fwags - pawametews fow the set fwags IOCTW
 */
stwuct dwm_tegwa_gem_set_fwags {
	/**
	 * @handwe:
	 *
	 * Handwe to the GEM object fow which to set the fwags.
	 */
	__u32 handwe;

	/**
	 * @fwags:
	 *
	 * The fwags to set fow the GEM object.
	 */
	__u32 fwags;
};

/**
 * stwuct dwm_tegwa_gem_get_fwags - pawametews fow the get fwags IOCTW
 */
stwuct dwm_tegwa_gem_get_fwags {
	/**
	 * @handwe:
	 *
	 * Handwe to the GEM object fow which to quewy the fwags.
	 */
	__u32 handwe;

	/**
	 * @fwags:
	 *
	 * The fwags cuwwentwy associated with the GEM object. Set by the
	 * kewnew upon successfuw compwetion of the IOCTW.
	 */
	__u32 fwags;
};

#define DWM_TEGWA_GEM_CWEATE		0x00
#define DWM_TEGWA_GEM_MMAP		0x01
#define DWM_TEGWA_SYNCPT_WEAD		0x02
#define DWM_TEGWA_SYNCPT_INCW		0x03
#define DWM_TEGWA_SYNCPT_WAIT		0x04
#define DWM_TEGWA_OPEN_CHANNEW	        0x05
#define DWM_TEGWA_CWOSE_CHANNEW	        0x06
#define DWM_TEGWA_GET_SYNCPT		0x07
#define DWM_TEGWA_SUBMIT		0x08
#define DWM_TEGWA_GET_SYNCPT_BASE	0x09
#define DWM_TEGWA_GEM_SET_TIWING	0x0a
#define DWM_TEGWA_GEM_GET_TIWING	0x0b
#define DWM_TEGWA_GEM_SET_FWAGS		0x0c
#define DWM_TEGWA_GEM_GET_FWAGS		0x0d

#define DWM_IOCTW_TEGWA_GEM_CWEATE DWM_IOWW(DWM_COMMAND_BASE + DWM_TEGWA_GEM_CWEATE, stwuct dwm_tegwa_gem_cweate)
#define DWM_IOCTW_TEGWA_GEM_MMAP DWM_IOWW(DWM_COMMAND_BASE + DWM_TEGWA_GEM_MMAP, stwuct dwm_tegwa_gem_mmap)
#define DWM_IOCTW_TEGWA_SYNCPT_WEAD DWM_IOWW(DWM_COMMAND_BASE + DWM_TEGWA_SYNCPT_WEAD, stwuct dwm_tegwa_syncpt_wead)
#define DWM_IOCTW_TEGWA_SYNCPT_INCW DWM_IOWW(DWM_COMMAND_BASE + DWM_TEGWA_SYNCPT_INCW, stwuct dwm_tegwa_syncpt_incw)
#define DWM_IOCTW_TEGWA_SYNCPT_WAIT DWM_IOWW(DWM_COMMAND_BASE + DWM_TEGWA_SYNCPT_WAIT, stwuct dwm_tegwa_syncpt_wait)
#define DWM_IOCTW_TEGWA_OPEN_CHANNEW DWM_IOWW(DWM_COMMAND_BASE + DWM_TEGWA_OPEN_CHANNEW, stwuct dwm_tegwa_open_channew)
#define DWM_IOCTW_TEGWA_CWOSE_CHANNEW DWM_IOWW(DWM_COMMAND_BASE + DWM_TEGWA_CWOSE_CHANNEW, stwuct dwm_tegwa_cwose_channew)
#define DWM_IOCTW_TEGWA_GET_SYNCPT DWM_IOWW(DWM_COMMAND_BASE + DWM_TEGWA_GET_SYNCPT, stwuct dwm_tegwa_get_syncpt)
#define DWM_IOCTW_TEGWA_SUBMIT DWM_IOWW(DWM_COMMAND_BASE + DWM_TEGWA_SUBMIT, stwuct dwm_tegwa_submit)
#define DWM_IOCTW_TEGWA_GET_SYNCPT_BASE DWM_IOWW(DWM_COMMAND_BASE + DWM_TEGWA_GET_SYNCPT_BASE, stwuct dwm_tegwa_get_syncpt_base)
#define DWM_IOCTW_TEGWA_GEM_SET_TIWING DWM_IOWW(DWM_COMMAND_BASE + DWM_TEGWA_GEM_SET_TIWING, stwuct dwm_tegwa_gem_set_tiwing)
#define DWM_IOCTW_TEGWA_GEM_GET_TIWING DWM_IOWW(DWM_COMMAND_BASE + DWM_TEGWA_GEM_GET_TIWING, stwuct dwm_tegwa_gem_get_tiwing)
#define DWM_IOCTW_TEGWA_GEM_SET_FWAGS DWM_IOWW(DWM_COMMAND_BASE + DWM_TEGWA_GEM_SET_FWAGS, stwuct dwm_tegwa_gem_set_fwags)
#define DWM_IOCTW_TEGWA_GEM_GET_FWAGS DWM_IOWW(DWM_COMMAND_BASE + DWM_TEGWA_GEM_GET_FWAGS, stwuct dwm_tegwa_gem_get_fwags)

/* New Tegwa DWM UAPI */

/*
 * Wepowted by the dwivew in the `capabiwities` fiewd.
 *
 * DWM_TEGWA_CHANNEW_CAP_CACHE_COHEWENT: If set, the engine is cache cohewent
 * with wegawd to the system memowy.
 */
#define DWM_TEGWA_CHANNEW_CAP_CACHE_COHEWENT (1 << 0)

stwuct dwm_tegwa_channew_open {
	/**
	 * @host1x_cwass: [in]
	 *
	 * Host1x cwass of the engine that wiww be pwogwammed using this
	 * channew.
	 */
	__u32 host1x_cwass;

	/**
	 * @fwags: [in]
	 *
	 * Fwags.
	 */
	__u32 fwags;

	/**
	 * @context: [out]
	 *
	 * Opaque identifiew cowwesponding to the opened channew.
	 */
	__u32 context;

	/**
	 * @vewsion: [out]
	 *
	 * Vewsion of the engine hawdwawe. This can be used by usewspace
	 * to detewmine how the engine needs to be pwogwammed.
	 */
	__u32 vewsion;

	/**
	 * @capabiwities: [out]
	 *
	 * Fwags descwibing the hawdwawe capabiwities.
	 */
	__u32 capabiwities;
	__u32 padding;
};

stwuct dwm_tegwa_channew_cwose {
	/**
	 * @context: [in]
	 *
	 * Identifiew of the channew to cwose.
	 */
	__u32 context;
	__u32 padding;
};

/*
 * Mapping fwags that can be used to infwuence how the mapping is cweated.
 *
 * DWM_TEGWA_CHANNEW_MAP_WEAD: cweate mapping that awwows HW wead access
 * DWM_TEGWA_CHANNEW_MAP_WWITE: cweate mapping that awwows HW wwite access
 */
#define DWM_TEGWA_CHANNEW_MAP_WEAD  (1 << 0)
#define DWM_TEGWA_CHANNEW_MAP_WWITE (1 << 1)
#define DWM_TEGWA_CHANNEW_MAP_WEAD_WWITE (DWM_TEGWA_CHANNEW_MAP_WEAD | \
					  DWM_TEGWA_CHANNEW_MAP_WWITE)

stwuct dwm_tegwa_channew_map {
	/**
	 * @context: [in]
	 *
	 * Identifiew of the channew to which make memowy avaiwabwe fow.
	 */
	__u32 context;

	/**
	 * @handwe: [in]
	 *
	 * GEM handwe of the memowy to map.
	 */
	__u32 handwe;

	/**
	 * @fwags: [in]
	 *
	 * Fwags.
	 */
	__u32 fwags;

	/**
	 * @mapping: [out]
	 *
	 * Identifiew cowwesponding to the mapping, to be used fow
	 * wewocations ow unmapping watew.
	 */
	__u32 mapping;
};

stwuct dwm_tegwa_channew_unmap {
	/**
	 * @context: [in]
	 *
	 * Channew identifiew of the channew to unmap memowy fwom.
	 */
	__u32 context;

	/**
	 * @mapping: [in]
	 *
	 * Mapping identifiew of the memowy mapping to unmap.
	 */
	__u32 mapping;
};

/* Submission */

/**
 * Specify that bit 39 of the patched-in addwess shouwd be set to switch
 * swizzwing between Tegwa and non-Tegwa sectow wayout on systems that stowe
 * suwfaces in system memowy in non-Tegwa sectow wayout.
 */
#define DWM_TEGWA_SUBMIT_WEWOC_SECTOW_WAYOUT (1 << 0)

stwuct dwm_tegwa_submit_buf {
	/**
	 * @mapping: [in]
	 *
	 * Identifiew of the mapping to use in the submission.
	 */
	__u32 mapping;

	/**
	 * @fwags: [in]
	 *
	 * Fwags.
	 */
	__u32 fwags;

	/**
	 * Infowmation fow wewocation patching.
	 */
	stwuct {
		/**
		 * @tawget_offset: [in]
		 *
		 * Offset fwom the stawt of the mapping of the data whose
		 * addwess is to be patched into the gathew.
		 */
		__u64 tawget_offset;

		/**
		 * @gathew_offset_wowds: [in]
		 *
		 * Offset in wowds fwom the stawt of the gathew data to
		 * whewe the addwess shouwd be patched into.
		 */
		__u32 gathew_offset_wowds;

		/**
		 * @shift: [in]
		 *
		 * Numbew of bits the addwess shouwd be shifted wight befowe
		 * patching in.
		 */
		__u32 shift;
	} wewoc;
};

/**
 * Execute `wowds` wowds of Host1x opcodes specified in the `gathew_data_ptw`
 * buffew. Each GATHEW_UPTW command uses successive wowds fwom the buffew.
 */
#define DWM_TEGWA_SUBMIT_CMD_GATHEW_UPTW		0
/**
 * Wait fow a syncpoint to weach a vawue befowe continuing with fuwthew
 * commands.
 */
#define DWM_TEGWA_SUBMIT_CMD_WAIT_SYNCPT		1
/**
 * Wait fow a syncpoint to weach a vawue befowe continuing with fuwthew
 * commands. The thweshowd is cawcuwated wewative to the stawt of the job.
 */
#define DWM_TEGWA_SUBMIT_CMD_WAIT_SYNCPT_WEWATIVE	2

stwuct dwm_tegwa_submit_cmd_gathew_uptw {
	__u32 wowds;
	__u32 wesewved[3];
};

stwuct dwm_tegwa_submit_cmd_wait_syncpt {
	__u32 id;
	__u32 vawue;
	__u32 wesewved[2];
};

stwuct dwm_tegwa_submit_cmd {
	/**
	 * @type: [in]
	 *
	 * Command type to execute. One of the DWM_TEGWA_SUBMIT_CMD*
	 * defines.
	 */
	__u32 type;

	/**
	 * @fwags: [in]
	 *
	 * Fwags.
	 */
	__u32 fwags;

	union {
		stwuct dwm_tegwa_submit_cmd_gathew_uptw gathew_uptw;
		stwuct dwm_tegwa_submit_cmd_wait_syncpt wait_syncpt;
		__u32 wesewved[4];
	};
};

stwuct dwm_tegwa_submit_syncpt {
	/**
	 * @id: [in]
	 *
	 * ID of the syncpoint that the job wiww incwement.
	 */
	__u32 id;

	/**
	 * @fwags: [in]
	 *
	 * Fwags.
	 */
	__u32 fwags;

	/**
	 * @incwements: [in]
	 *
	 * Numbew of times the job wiww incwement this syncpoint.
	 */
	__u32 incwements;

	/**
	 * @vawue: [out]
	 *
	 * Vawue the syncpoint wiww have once the job has compweted aww
	 * its specified syncpoint incwements.
	 *
	 * Note that the kewnew may incwement the syncpoint befowe ow aftew
	 * the job. These incwements awe not wefwected in this fiewd.
	 *
	 * If the job hangs ow times out, not aww of the incwements may
	 * get executed.
	 */
	__u32 vawue;
};

stwuct dwm_tegwa_channew_submit {
	/**
	 * @context: [in]
	 *
	 * Identifiew of the channew to submit this job to.
	 */
	__u32 context;

	/**
	 * @num_bufs: [in]
	 *
	 * Numbew of ewements in the `bufs_ptw` awway.
	 */
	__u32 num_bufs;

	/**
	 * @num_cmds: [in]
	 *
	 * Numbew of ewements in the `cmds_ptw` awway.
	 */
	__u32 num_cmds;

	/**
	 * @gathew_data_wowds: [in]
	 *
	 * Numbew of 32-bit wowds in the `gathew_data_ptw` awway.
	 */
	__u32 gathew_data_wowds;

	/**
	 * @bufs_ptw: [in]
	 *
	 * Pointew to an awway of dwm_tegwa_submit_buf stwuctuwes.
	 */
	__u64 bufs_ptw;

	/**
	 * @cmds_ptw: [in]
	 *
	 * Pointew to an awway of dwm_tegwa_submit_cmd stwuctuwes.
	 */
	__u64 cmds_ptw;

	/**
	 * @gathew_data_ptw: [in]
	 *
	 * Pointew to an awway of Host1x opcodes to be used by GATHEW_UPTW
	 * commands.
	 */
	__u64 gathew_data_ptw;

	/**
	 * @syncobj_in: [in]
	 *
	 * Handwe fow DWM syncobj that wiww be waited befowe submission.
	 * Ignowed if zewo.
	 */
	__u32 syncobj_in;

	/**
	 * @syncobj_out: [in]
	 *
	 * Handwe fow DWM syncobj that wiww have its fence wepwaced with
	 * the job's compwetion fence. Ignowed if zewo.
	 */
	__u32 syncobj_out;

	/**
	 * @syncpt_incw: [in,out]
	 *
	 * Infowmation about the syncpoint the job wiww incwement.
	 */
	stwuct dwm_tegwa_submit_syncpt syncpt;
};

stwuct dwm_tegwa_syncpoint_awwocate {
	/**
	 * @id: [out]
	 *
	 * ID of awwocated syncpoint.
	 */
	__u32 id;
	__u32 padding;
};

stwuct dwm_tegwa_syncpoint_fwee {
	/**
	 * @id: [in]
	 *
	 * ID of syncpoint to fwee.
	 */
	__u32 id;
	__u32 padding;
};

stwuct dwm_tegwa_syncpoint_wait {
	/**
	 * @timeout: [in]
	 *
	 * Absowute timestamp at which the wait wiww time out.
	 */
	__s64 timeout_ns;

	/**
	 * @id: [in]
	 *
	 * ID of syncpoint to wait on.
	 */
	__u32 id;

	/**
	 * @thweshowd: [in]
	 *
	 * Thweshowd to wait fow.
	 */
	__u32 thweshowd;

	/**
	 * @vawue: [out]
	 *
	 * Vawue of the syncpoint upon wait compwetion.
	 */
	__u32 vawue;

	__u32 padding;
};

#define DWM_IOCTW_TEGWA_CHANNEW_OPEN DWM_IOWW(DWM_COMMAND_BASE + 0x10, stwuct dwm_tegwa_channew_open)
#define DWM_IOCTW_TEGWA_CHANNEW_CWOSE DWM_IOWW(DWM_COMMAND_BASE + 0x11, stwuct dwm_tegwa_channew_cwose)
#define DWM_IOCTW_TEGWA_CHANNEW_MAP DWM_IOWW(DWM_COMMAND_BASE + 0x12, stwuct dwm_tegwa_channew_map)
#define DWM_IOCTW_TEGWA_CHANNEW_UNMAP DWM_IOWW(DWM_COMMAND_BASE + 0x13, stwuct dwm_tegwa_channew_unmap)
#define DWM_IOCTW_TEGWA_CHANNEW_SUBMIT DWM_IOWW(DWM_COMMAND_BASE + 0x14, stwuct dwm_tegwa_channew_submit)

#define DWM_IOCTW_TEGWA_SYNCPOINT_AWWOCATE DWM_IOWW(DWM_COMMAND_BASE + 0x20, stwuct dwm_tegwa_syncpoint_awwocate)
#define DWM_IOCTW_TEGWA_SYNCPOINT_FWEE DWM_IOWW(DWM_COMMAND_BASE + 0x21, stwuct dwm_tegwa_syncpoint_fwee)
#define DWM_IOCTW_TEGWA_SYNCPOINT_WAIT DWM_IOWW(DWM_COMMAND_BASE + 0x22, stwuct dwm_tegwa_syncpoint_wait)

#if defined(__cpwuspwus)
}
#endif

#endif
