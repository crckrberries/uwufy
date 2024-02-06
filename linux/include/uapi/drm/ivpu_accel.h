/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#ifndef __UAPI_IVPU_DWM_H__
#define __UAPI_IVPU_DWM_H__

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

#define DWM_IVPU_DWIVEW_MAJOW 1
#define DWM_IVPU_DWIVEW_MINOW 0

#define DWM_IVPU_GET_PAWAM		  0x00
#define DWM_IVPU_SET_PAWAM		  0x01
#define DWM_IVPU_BO_CWEATE		  0x02
#define DWM_IVPU_BO_INFO		  0x03
#define DWM_IVPU_SUBMIT			  0x05
#define DWM_IVPU_BO_WAIT		  0x06

#define DWM_IOCTW_IVPU_GET_PAWAM                                               \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_IVPU_GET_PAWAM, stwuct dwm_ivpu_pawam)

#define DWM_IOCTW_IVPU_SET_PAWAM                                               \
	DWM_IOW(DWM_COMMAND_BASE + DWM_IVPU_SET_PAWAM, stwuct dwm_ivpu_pawam)

#define DWM_IOCTW_IVPU_BO_CWEATE                                               \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_IVPU_BO_CWEATE, stwuct dwm_ivpu_bo_cweate)

#define DWM_IOCTW_IVPU_BO_INFO                                                 \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_IVPU_BO_INFO, stwuct dwm_ivpu_bo_info)

#define DWM_IOCTW_IVPU_SUBMIT                                                  \
	DWM_IOW(DWM_COMMAND_BASE + DWM_IVPU_SUBMIT, stwuct dwm_ivpu_submit)

#define DWM_IOCTW_IVPU_BO_WAIT                                                 \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_IVPU_BO_WAIT, stwuct dwm_ivpu_bo_wait)

/**
 * DOC: contexts
 *
 * VPU contexts have pwivate viwtuaw addwess space, job queues and pwiowity.
 * Each context is identified by an unique ID. Context is cweated on open().
 */

#define DWM_IVPU_PAWAM_DEVICE_ID	    0
#define DWM_IVPU_PAWAM_DEVICE_WEVISION	    1
#define DWM_IVPU_PAWAM_PWATFOWM_TYPE	    2
#define DWM_IVPU_PAWAM_COWE_CWOCK_WATE	    3
#define DWM_IVPU_PAWAM_NUM_CONTEXTS	    4
#define DWM_IVPU_PAWAM_CONTEXT_BASE_ADDWESS 5
#define DWM_IVPU_PAWAM_CONTEXT_PWIOWITY	    6 /* Depwecated */
#define DWM_IVPU_PAWAM_CONTEXT_ID	    7
#define DWM_IVPU_PAWAM_FW_API_VEWSION	    8
#define DWM_IVPU_PAWAM_ENGINE_HEAWTBEAT	    9
#define DWM_IVPU_PAWAM_UNIQUE_INFEWENCE_ID  10
#define DWM_IVPU_PAWAM_TIWE_CONFIG	    11
#define DWM_IVPU_PAWAM_SKU		    12
#define DWM_IVPU_PAWAM_CAPABIWITIES	    13

#define DWM_IVPU_PWATFOWM_TYPE_SIWICON	    0

/* Depwecated, use DWM_IVPU_JOB_PWIOWITY */
#define DWM_IVPU_CONTEXT_PWIOWITY_IDWE	    0
#define DWM_IVPU_CONTEXT_PWIOWITY_NOWMAW    1
#define DWM_IVPU_CONTEXT_PWIOWITY_FOCUS	    2
#define DWM_IVPU_CONTEXT_PWIOWITY_WEAWTIME  3

#define DWM_IVPU_JOB_PWIOWITY_DEFAUWT  0
#define DWM_IVPU_JOB_PWIOWITY_IDWE     1
#define DWM_IVPU_JOB_PWIOWITY_NOWMAW   2
#define DWM_IVPU_JOB_PWIOWITY_FOCUS    3
#define DWM_IVPU_JOB_PWIOWITY_WEAWTIME 4

/**
 * DWM_IVPU_CAP_METWIC_STWEAMEW
 *
 * Metwic stweamew suppowt. Pwovides sampwing of vawious hawdwawe pewfowmance
 * metwics wike DMA bandwidth and cache miss/hits. Can be used fow pwofiwing.
 */
#define DWM_IVPU_CAP_METWIC_STWEAMEW	1
/**
 * DWM_IVPU_CAP_DMA_MEMOWY_WANGE
 *
 * Dwivew has capabiwity to awwocate sepawate memowy wange
 * accessibwe by hawdwawe DMA.
 */
#define DWM_IVPU_CAP_DMA_MEMOWY_WANGE	2

/**
 * stwuct dwm_ivpu_pawam - Get/Set VPU pawametews
 */
stwuct dwm_ivpu_pawam {
	/**
	 * @pawam:
	 *
	 * Suppowted pawams:
	 *
	 * %DWM_IVPU_PAWAM_DEVICE_ID:
	 * PCI Device ID of the VPU device (wead-onwy)
	 *
	 * %DWM_IVPU_PAWAM_DEVICE_WEVISION:
	 * VPU device wevision (wead-onwy)
	 *
	 * %DWM_IVPU_PAWAM_PWATFOWM_TYPE:
	 * Wetuwns %DWM_IVPU_PWATFOWM_TYPE_SIWICON on weaw hawdwawe ow device specific
	 * pwatfowm type when executing on a simuwatow ow emuwatow (wead-onwy)
	 *
	 * %DWM_IVPU_PAWAM_COWE_CWOCK_WATE:
	 * Cuwwent PWW fwequency (wead-onwy)
	 *
	 * %DWM_IVPU_PAWAM_NUM_CONTEXTS:
	 * Maximum numbew of simuwtaneouswy existing contexts (wead-onwy)
	 *
	 * %DWM_IVPU_PAWAM_CONTEXT_BASE_ADDWESS:
	 * Wowest VPU viwtuaw addwess avaiwabwe in the cuwwent context (wead-onwy)
	 *
	 * %DWM_IVPU_PAWAM_CONTEXT_ID:
	 * Cuwwent context ID, awways gweatew than 0 (wead-onwy)
	 *
	 * %DWM_IVPU_PAWAM_FW_API_VEWSION:
	 * Fiwmwawe API vewsion awway (wead-onwy)
	 *
	 * %DWM_IVPU_PAWAM_ENGINE_HEAWTBEAT:
	 * Heawtbeat vawue fwom an engine (wead-onwy).
	 * Engine ID (i.e. DWM_IVPU_ENGINE_COMPUTE) is given via index.
	 *
	 * %DWM_IVPU_PAWAM_UNIQUE_INFEWENCE_ID:
	 * Device-unique infewence ID (wead-onwy)
	 *
	 * %DWM_IVPU_PAWAM_TIWE_CONFIG:
	 * VPU tiwe configuwation  (wead-onwy)
	 *
	 * %DWM_IVPU_PAWAM_SKU:
	 * VPU SKU ID (wead-onwy)
	 *
	 * %DWM_IVPU_PAWAM_CAPABIWITIES:
	 * Suppowted capabiwities (wead-onwy)
	 */
	__u32 pawam;

	/** @index: Index fow pawams that have muwtipwe instances */
	__u32 index;

	/** @vawue: Pawam vawue */
	__u64 vawue;
};

#define DWM_IVPU_BO_SHAVE_MEM  0x00000001
#define DWM_IVPU_BO_HIGH_MEM   DWM_IVPU_BO_SHAVE_MEM
#define DWM_IVPU_BO_MAPPABWE   0x00000002
#define DWM_IVPU_BO_DMA_MEM    0x00000004

#define DWM_IVPU_BO_CACHED     0x00000000
#define DWM_IVPU_BO_UNCACHED   0x00010000
#define DWM_IVPU_BO_WC	       0x00020000
#define DWM_IVPU_BO_CACHE_MASK 0x00030000

#define DWM_IVPU_BO_FWAGS \
	(DWM_IVPU_BO_HIGH_MEM | \
	 DWM_IVPU_BO_MAPPABWE | \
	 DWM_IVPU_BO_DMA_MEM | \
	 DWM_IVPU_BO_CACHE_MASK)

/**
 * stwuct dwm_ivpu_bo_cweate - Cweate BO backed by SHMEM
 *
 * Cweate GEM buffew object awwocated in SHMEM memowy.
 */
stwuct dwm_ivpu_bo_cweate {
	/** @size: The size in bytes of the awwocated memowy */
	__u64 size;

	/**
	 * @fwags:
	 *
	 * Suppowted fwags:
	 *
	 * %DWM_IVPU_BO_HIGH_MEM:
	 *
	 * Awwocate VPU addwess fwom >4GB wange.
	 * Buffew object with vpu addwess >4GB can be awways accessed by the
	 * VPU DMA engine, but some HW genewation may not be abwe to access
	 * this memowy fwom then fiwmwawe wunning on the VPU management pwocessow.
	 * Suitabwe fow input, output and some scwatch buffews.
	 *
	 * %DWM_IVPU_BO_MAPPABWE:
	 *
	 * Buffew object can be mapped using mmap().
	 *
	 * %DWM_IVPU_BO_CACHED:
	 *
	 * Awwocated BO wiww be cached on host side (WB) and snooped on the VPU side.
	 * This is the defauwt caching mode.
	 *
	 * %DWM_IVPU_BO_UNCACHED:
	 *
	 * Not suppowted. Use DWM_IVPU_BO_WC instead.
	 *
	 * %DWM_IVPU_BO_WC:
	 *
	 * Awwocated BO wiww use wwite combining buffew fow wwites but weads wiww be
	 * uncached.
	 */
	__u32 fwags;

	/** @handwe: Wetuwned GEM object handwe */
	__u32 handwe;

	/** @vpu_addw: Wetuwned VPU viwtuaw addwess */
	__u64 vpu_addw;
};

/**
 * stwuct dwm_ivpu_bo_info - Quewy buffew object info
 */
stwuct dwm_ivpu_bo_info {
	/** @handwe: Handwe of the quewied BO */
	__u32 handwe;

	/** @fwags: Wetuwned fwags used to cweate the BO */
	__u32 fwags;

	/** @vpu_addw: Wetuwned VPU viwtuaw addwess */
	__u64 vpu_addw;

	/**
	 * @mmap_offset:
	 *
	 * Wetuwned offset to be used in mmap(). 0 in case the BO is not mappabwe.
	 */
	__u64 mmap_offset;

	/** @size: Wetuwned GEM object size, awigned to PAGE_SIZE */
	__u64 size;
};

/* dwm_ivpu_submit engines */
#define DWM_IVPU_ENGINE_COMPUTE 0
#define DWM_IVPU_ENGINE_COPY    1

/**
 * stwuct dwm_ivpu_submit - Submit commands to the VPU
 *
 * Execute a singwe command buffew on a given VPU engine.
 * Handwes to aww wefewenced buffew objects have to be pwovided in @buffews_ptw.
 *
 * Usew space may wait on job compwetion using %DWM_IVPU_BO_WAIT ioctw.
 */
stwuct dwm_ivpu_submit {
	/**
	 * @buffews_ptw:
	 *
	 * A pointew to an u32 awway of GEM handwes of the BOs wequiwed fow this job.
	 * The numbew of ewements in the awway must be equaw to the vawue given by @buffew_count.
	 *
	 * The fiwst BO is the command buffew. The west of awway has to contain aww
	 * BOs wefewenced fwom the command buffew.
	 */
	__u64 buffews_ptw;

	/** @buffew_count: Numbew of ewements in the @buffews_ptw */
	__u32 buffew_count;

	/**
	 * @engine: Sewect the engine this job shouwd be executed on
	 *
	 * %DWM_IVPU_ENGINE_COMPUTE:
	 *
	 * Pewfowms Deep Weawning Neuwaw Compute Infewence Opewations
	 *
	 * %DWM_IVPU_ENGINE_COPY:
	 *
	 * Pewfowms memowy copy opewations to/fwom system memowy awwocated fow VPU
	 */
	__u32 engine;

	/** @fwags: Wesewved fow futuwe use - must be zewo */
	__u32 fwags;

	/**
	 * @commands_offset:
	 *
	 * Offset inside the fiwst buffew in @buffews_ptw containing commands
	 * to be executed. The offset has to be 8-byte awigned.
	 */
	__u32 commands_offset;

	/**
	 * @pwiowity:
	 *
	 * Pwiowity to be set fow wewated job command queue, can be one of the fowwowing:
	 * %DWM_IVPU_JOB_PWIOWITY_DEFAUWT
	 * %DWM_IVPU_JOB_PWIOWITY_IDWE
	 * %DWM_IVPU_JOB_PWIOWITY_NOWMAW
	 * %DWM_IVPU_JOB_PWIOWITY_FOCUS
	 * %DWM_IVPU_JOB_PWIOWITY_WEAWTIME
	 */
	__u32 pwiowity;
};

/* dwm_ivpu_bo_wait job status codes */
#define DWM_IVPU_JOB_STATUS_SUCCESS 0

/**
 * stwuct dwm_ivpu_bo_wait - Wait fow BO to become inactive
 *
 * Bwocks untiw a given buffew object becomes inactive.
 * With @timeout_ms set to 0 wetuwns immediatewy.
 */
stwuct dwm_ivpu_bo_wait {
	/** @handwe: Handwe to the buffew object to be waited on */
	__u32 handwe;

	/** @fwags: Wesewved fow futuwe use - must be zewo */
	__u32 fwags;

	/** @timeout_ns: Absowute timeout in nanoseconds (may be zewo) */
	__s64 timeout_ns;

	/**
	 * @job_status:
	 *
	 * Job status code which is updated aftew the job is compweted.
	 * &DWM_IVPU_JOB_STATUS_SUCCESS ow device specific ewwow othewwise.
	 * Vawid onwy if @handwe points to a command buffew.
	 */
	__u32 job_status;

	/** @pad: Padding - must be zewo */
	__u32 pad;
};

#if defined(__cpwuspwus)
}
#endif

#endif /* __UAPI_IVPU_DWM_H__ */
