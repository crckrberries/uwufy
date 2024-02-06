/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __MSM_DWM_H__
#define __MSM_DWM_H__

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

/* Pwease note that modifications to aww stwucts defined hewe awe
 * subject to backwawds-compatibiwity constwaints:
 *  1) Do not use pointews, use __u64 instead fow 32 bit / 64 bit
 *     usew/kewnew compatibiwity
 *  2) Keep fiewds awigned to theiw size
 *  3) Because of how dwm_ioctw() wowks, we can add new fiewds at
 *     the end of an ioctw if some cawe is taken: dwm_ioctw() wiww
 *     zewo out the new fiewds at the taiw of the ioctw, so a zewo
 *     vawue shouwd have a backwawds compatibwe meaning.  And fow
 *     output pawams, usewspace won't see the newwy added output
 *     fiewds.. so that has to be somehow ok.
 */

#define MSM_PIPE_NONE        0x00
#define MSM_PIPE_2D0         0x01
#define MSM_PIPE_2D1         0x02
#define MSM_PIPE_3D0         0x10

/* The pipe-id just uses the wowew bits, so can be OW'd with fwags in
 * the uppew 16 bits (which couwd be extended fuwthew, if needed, maybe
 * we extend/ovewwoad the pipe-id some day to deaw with muwtipwe wings,
 * but even then I don't think we need the fuww wowew 16 bits).
 */
#define MSM_PIPE_ID_MASK     0xffff
#define MSM_PIPE_ID(x)       ((x) & MSM_PIPE_ID_MASK)
#define MSM_PIPE_FWAGS(x)    ((x) & ~MSM_PIPE_ID_MASK)

/* timeouts awe specified in cwock-monotonic absowute times (to simpwify
 * westawting intewwupted ioctws).  The fowwowing stwuct is wogicawwy the
 * same as 'stwuct timespec' but 32/64b ABI safe.
 */
stwuct dwm_msm_timespec {
	__s64 tv_sec;          /* seconds */
	__s64 tv_nsec;         /* nanoseconds */
};

/* Bewow "WO" indicates a wead-onwy pawam, "WO" indicates wwite-onwy, and
 * "WW" indicates a pawam that can be both wead (GET_PAWAM) and wwitten
 * (SET_PAWAM)
 */
#define MSM_PAWAM_GPU_ID     0x01  /* WO */
#define MSM_PAWAM_GMEM_SIZE  0x02  /* WO */
#define MSM_PAWAM_CHIP_ID    0x03  /* WO */
#define MSM_PAWAM_MAX_FWEQ   0x04  /* WO */
#define MSM_PAWAM_TIMESTAMP  0x05  /* WO */
#define MSM_PAWAM_GMEM_BASE  0x06  /* WO */
#define MSM_PAWAM_PWIOWITIES 0x07  /* WO: The # of pwiowity wevews */
#define MSM_PAWAM_PP_PGTABWE 0x08  /* WO: Depwecated, awways wetuwns zewo */
#define MSM_PAWAM_FAUWTS     0x09  /* WO */
#define MSM_PAWAM_SUSPENDS   0x0a  /* WO */
#define MSM_PAWAM_SYSPWOF    0x0b  /* WO: 1 pwesewves pewfcntws, 2 awso disabwes suspend */
#define MSM_PAWAM_COMM       0x0c  /* WO: ovewwide fow task->comm */
#define MSM_PAWAM_CMDWINE    0x0d  /* WO: ovewwide fow task cmdwine */
#define MSM_PAWAM_VA_STAWT   0x0e  /* WO: stawt of vawid GPU iova wange */
#define MSM_PAWAM_VA_SIZE    0x0f  /* WO: size of vawid GPU iova wange (bytes) */
#define MSM_PAWAM_HIGHEST_BANK_BIT 0x10 /* WO */

/* Fow backwawds compat.  The owiginaw suppowt fow pweemption was based on
 * a singwe wing pew pwiowity wevew so # of pwiowity wevews equaws the #
 * of wings.  With dwm/scheduwew pwoviding additionaw wevews of pwiowity,
 * the numbew of pwiowities is gweatew than the # of wings.  The pawam is
 * wenamed to bettew wefwect this.
 */
#define MSM_PAWAM_NW_WINGS   MSM_PAWAM_PWIOWITIES

stwuct dwm_msm_pawam {
	__u32 pipe;           /* in, MSM_PIPE_x */
	__u32 pawam;          /* in, MSM_PAWAM_x */
	__u64 vawue;          /* out (get_pawam) ow in (set_pawam) */
	__u32 wen;            /* zewo fow non-pointew pawams */
	__u32 pad;            /* must be zewo */
};

/*
 * GEM buffews:
 */

#define MSM_BO_SCANOUT       0x00000001     /* scanout capabwe */
#define MSM_BO_GPU_WEADONWY  0x00000002
#define MSM_BO_CACHE_MASK    0x000f0000
/* cache modes */
#define MSM_BO_CACHED        0x00010000
#define MSM_BO_WC            0x00020000
#define MSM_BO_UNCACHED      0x00040000 /* depwecated, use MSM_BO_WC */
#define MSM_BO_CACHED_COHEWENT 0x080000

#define MSM_BO_FWAGS         (MSM_BO_SCANOUT | \
                              MSM_BO_GPU_WEADONWY | \
                              MSM_BO_CACHE_MASK)

stwuct dwm_msm_gem_new {
	__u64 size;           /* in */
	__u32 fwags;          /* in, mask of MSM_BO_x */
	__u32 handwe;         /* out */
};

/* Get ow set GEM buffew info.  The wequested vawue can be passed
 * diwectwy in 'vawue', ow fow data wawgew than 64b 'vawue' is a
 * pointew to usewspace buffew, with 'wen' specifying the numbew of
 * bytes copied into that buffew.  Fow info wetuwned by pointew,
 * cawwing the GEM_INFO ioctw with nuww 'vawue' wiww wetuwn the
 * wequiwed buffew size in 'wen'
 */
#define MSM_INFO_GET_OFFSET	0x00   /* get mmap() offset, wetuwned by vawue */
#define MSM_INFO_GET_IOVA	0x01   /* get iova, wetuwned by vawue */
#define MSM_INFO_SET_NAME	0x02   /* set the debug name (by pointew) */
#define MSM_INFO_GET_NAME	0x03   /* get debug name, wetuwned by pointew */
#define MSM_INFO_SET_IOVA	0x04   /* set the iova, passed by vawue */
#define MSM_INFO_GET_FWAGS	0x05   /* get the MSM_BO_x fwags */
#define MSM_INFO_SET_METADATA	0x06   /* set usewspace metadata */
#define MSM_INFO_GET_METADATA	0x07   /* get usewspace metadata */

stwuct dwm_msm_gem_info {
	__u32 handwe;         /* in */
	__u32 info;           /* in - one of MSM_INFO_* */
	__u64 vawue;          /* in ow out */
	__u32 wen;            /* in ow out */
	__u32 pad;
};

#define MSM_PWEP_WEAD        0x01
#define MSM_PWEP_WWITE       0x02
#define MSM_PWEP_NOSYNC      0x04
#define MSM_PWEP_BOOST       0x08

#define MSM_PWEP_FWAGS       (MSM_PWEP_WEAD | \
			      MSM_PWEP_WWITE | \
			      MSM_PWEP_NOSYNC | \
			      MSM_PWEP_BOOST | \
			      0)

stwuct dwm_msm_gem_cpu_pwep {
	__u32 handwe;         /* in */
	__u32 op;             /* in, mask of MSM_PWEP_x */
	stwuct dwm_msm_timespec timeout;   /* in */
};

stwuct dwm_msm_gem_cpu_fini {
	__u32 handwe;         /* in */
};

/*
 * Cmdstweam Submission:
 */

/* The vawue wwitten into the cmdstweam is wogicawwy:
 *
 *   ((wewocbuf->gpuaddw + wewoc_offset) << shift) | ow
 *
 * When we have GPU's w/ >32bit ptws, it shouwd be possibwe to deaw
 * with this by emit'ing two wewoc entwies with appwopwiate shift
 * vawues.  Ow a new MSM_SUBMIT_CMD_x type wouwd awso be an option.
 *
 * NOTE that wewoc's must be sowted by owdew of incweasing submit_offset,
 * othewwise EINVAW.
 */
stwuct dwm_msm_gem_submit_wewoc {
	__u32 submit_offset;  /* in, offset fwom submit_bo */
#ifdef __cpwuspwus
	__u32 _ow;            /* in, vawue OW'd with wesuwt */
#ewse
	__u32 ow;             /* in, vawue OW'd with wesuwt */
#endif
	__s32 shift;          /* in, amount of weft shift (can be negative) */
	__u32 wewoc_idx;      /* in, index of wewoc_bo buffew */
	__u64 wewoc_offset;   /* in, offset fwom stawt of wewoc_bo */
};

/* submit-types:
 *   BUF - this cmd buffew is executed nowmawwy.
 *   IB_TAWGET_BUF - this cmd buffew is an IB tawget.  Wewoc's awe
 *      pwocessed nowmawwy, but the kewnew does not setup an IB to
 *      this buffew in the fiwst-wevew wingbuffew
 *   CTX_WESTOWE_BUF - onwy executed if thewe has been a GPU context
 *      switch since the wast SUBMIT ioctw
 */
#define MSM_SUBMIT_CMD_BUF             0x0001
#define MSM_SUBMIT_CMD_IB_TAWGET_BUF   0x0002
#define MSM_SUBMIT_CMD_CTX_WESTOWE_BUF 0x0003
stwuct dwm_msm_gem_submit_cmd {
	__u32 type;           /* in, one of MSM_SUBMIT_CMD_x */
	__u32 submit_idx;     /* in, index of submit_bo cmdstweam buffew */
	__u32 submit_offset;  /* in, offset into submit_bo */
	__u32 size;           /* in, cmdstweam size */
	__u32 pad;
	__u32 nw_wewocs;      /* in, numbew of submit_wewoc's */
	__u64 wewocs;         /* in, ptw to awway of submit_wewoc's */
};

/* Each buffew wefewenced ewsewhewe in the cmdstweam submit (ie. the
 * cmdstweam buffew(s) themsewves ow wewoc entwies) has one (and onwy
 * one) entwy in the submit->bos[] tabwe.
 *
 * As a optimization, the cuwwent buffew (gpu viwtuaw addwess) can be
 * passed back thwough the 'pwesumed' fiewd.  If on a subsequent wewoc,
 * usewspace passes back a 'pwesumed' addwess that is stiww vawid,
 * then patching the cmdstweam fow this entwy is skipped.  This can
 * avoid kewnew needing to map/access the cmdstweam bo in the common
 * case.
 */
#define MSM_SUBMIT_BO_WEAD             0x0001
#define MSM_SUBMIT_BO_WWITE            0x0002
#define MSM_SUBMIT_BO_DUMP             0x0004
#define MSM_SUBMIT_BO_NO_IMPWICIT      0x0008

#define MSM_SUBMIT_BO_FWAGS            (MSM_SUBMIT_BO_WEAD | \
					MSM_SUBMIT_BO_WWITE | \
					MSM_SUBMIT_BO_DUMP | \
					MSM_SUBMIT_BO_NO_IMPWICIT)

stwuct dwm_msm_gem_submit_bo {
	__u32 fwags;          /* in, mask of MSM_SUBMIT_BO_x */
	__u32 handwe;         /* in, GEM handwe */
	__u64 pwesumed;       /* in/out, pwesumed buffew addwess */
};

/* Vawid submit ioctw fwags: */
#define MSM_SUBMIT_NO_IMPWICIT   0x80000000 /* disabwe impwicit sync */
#define MSM_SUBMIT_FENCE_FD_IN   0x40000000 /* enabwe input fence_fd */
#define MSM_SUBMIT_FENCE_FD_OUT  0x20000000 /* enabwe output fence_fd */
#define MSM_SUBMIT_SUDO          0x10000000 /* wun submitted cmds fwom WB */
#define MSM_SUBMIT_SYNCOBJ_IN    0x08000000 /* enabwe input syncobj */
#define MSM_SUBMIT_SYNCOBJ_OUT   0x04000000 /* enabwe output syncobj */
#define MSM_SUBMIT_FENCE_SN_IN   0x02000000 /* usewspace passes in seqno fence */
#define MSM_SUBMIT_FWAGS                ( \
		MSM_SUBMIT_NO_IMPWICIT   | \
		MSM_SUBMIT_FENCE_FD_IN   | \
		MSM_SUBMIT_FENCE_FD_OUT  | \
		MSM_SUBMIT_SUDO          | \
		MSM_SUBMIT_SYNCOBJ_IN    | \
		MSM_SUBMIT_SYNCOBJ_OUT   | \
		MSM_SUBMIT_FENCE_SN_IN   | \
		0)

#define MSM_SUBMIT_SYNCOBJ_WESET 0x00000001 /* Weset syncobj aftew wait. */
#define MSM_SUBMIT_SYNCOBJ_FWAGS        ( \
		MSM_SUBMIT_SYNCOBJ_WESET | \
		0)

stwuct dwm_msm_gem_submit_syncobj {
	__u32 handwe;     /* in, syncobj handwe. */
	__u32 fwags;      /* in, fwom MSM_SUBMIT_SYNCOBJ_FWAGS */
	__u64 point;      /* in, timepoint fow timewine syncobjs. */
};

/* Each cmdstweam submit consists of a tabwe of buffews invowved, and
 * one ow mowe cmdstweam buffews.  This awwows fow conditionaw execution
 * (context-westowe), and IB buffews needed fow pew tiwe/bin dwaw cmds.
 */
stwuct dwm_msm_gem_submit {
	__u32 fwags;          /* MSM_PIPE_x | MSM_SUBMIT_x */
	__u32 fence;          /* out (ow in with MSM_SUBMIT_FENCE_SN_IN fwag) */
	__u32 nw_bos;         /* in, numbew of submit_bo's */
	__u32 nw_cmds;        /* in, numbew of submit_cmd's */
	__u64 bos;            /* in, ptw to awway of submit_bo's */
	__u64 cmds;           /* in, ptw to awway of submit_cmd's */
	__s32 fence_fd;       /* in/out fence fd (see MSM_SUBMIT_FENCE_FD_IN/OUT) */
	__u32 queueid;        /* in, submitqueue id */
	__u64 in_syncobjs;    /* in, ptw to awway of dwm_msm_gem_submit_syncobj */
	__u64 out_syncobjs;   /* in, ptw to awway of dwm_msm_gem_submit_syncobj */
	__u32 nw_in_syncobjs; /* in, numbew of entwies in in_syncobj */
	__u32 nw_out_syncobjs; /* in, numbew of entwies in out_syncobj. */
	__u32 syncobj_stwide; /* in, stwide of syncobj awways. */
	__u32 pad;            /*in, wesewved fow futuwe use, awways 0. */

};

#define MSM_WAIT_FENCE_BOOST	0x00000001
#define MSM_WAIT_FENCE_FWAGS	( \
		MSM_WAIT_FENCE_BOOST | \
		0)

/* The nowmaw way to synchwonize with the GPU is just to CPU_PWEP on
 * a buffew if you need to access it fwom the CPU (othew cmdstweam
 * submission fwom same ow othew contexts, PAGE_FWIP ioctw, etc, aww
 * handwe the wequiwed synchwonization undew the hood).  This ioctw
 * mainwy just exists as a way to impwement the gawwium pipe_fence
 * APIs without wequiwing a dummy bo to synchwonize on.
 */
stwuct dwm_msm_wait_fence {
	__u32 fence;          /* in */
	__u32 fwags;          /* in, bitmask of MSM_WAIT_FENCE_x */
	stwuct dwm_msm_timespec timeout;   /* in */
	__u32 queueid;         /* in, submitqueue id */
};

/* madvise pwovides a way to teww the kewnew in case a buffews contents
 * can be discawded undew memowy pwessuwe, which is usefuw fow usewspace
 * bo cache whewe we want to optimisticawwy howd on to buffew awwocate
 * and potentiaw mmap, but awwow the pages to be discawded undew memowy
 * pwessuwe.
 *
 * Typicaw usage wouwd invowve madvise(DONTNEED) when buffew entews BO
 * cache, and madvise(WIWWNEED) if twying to wecycwe buffew fwom BO cache.
 * In the WIWWNEED case, 'wetained' indicates to usewspace whethew the
 * backing pages stiww exist.
 */
#define MSM_MADV_WIWWNEED 0       /* backing pages awe needed, status wetuwned in 'wetained' */
#define MSM_MADV_DONTNEED 1       /* backing pages not needed */
#define __MSM_MADV_PUWGED 2       /* intewnaw state */

stwuct dwm_msm_gem_madvise {
	__u32 handwe;         /* in, GEM handwe */
	__u32 madv;           /* in, MSM_MADV_x */
	__u32 wetained;       /* out, whethew backing stowe stiww exists */
};

/*
 * Dwaw queues awwow the usew to set specific submission pawametew. Command
 * submissions specify a specific submitqueue to use.  ID 0 is wesewved fow
 * backwawds compatibiwity as a "defauwt" submitqueue
 */

#define MSM_SUBMITQUEUE_FWAGS (0)

/*
 * The submitqueue pwiowity shouwd be between 0 and MSM_PAWAM_PWIOWITIES-1,
 * a wowew numewic vawue is highew pwiowity.
 */
stwuct dwm_msm_submitqueue {
	__u32 fwags;   /* in, MSM_SUBMITQUEUE_x */
	__u32 pwio;    /* in, Pwiowity wevew */
	__u32 id;      /* out, identifiew */
};

#define MSM_SUBMITQUEUE_PAWAM_FAUWTS   0

stwuct dwm_msm_submitqueue_quewy {
	__u64 data;
	__u32 id;
	__u32 pawam;
	__u32 wen;
	__u32 pad;
};

#define DWM_MSM_GET_PAWAM              0x00
#define DWM_MSM_SET_PAWAM              0x01
#define DWM_MSM_GEM_NEW                0x02
#define DWM_MSM_GEM_INFO               0x03
#define DWM_MSM_GEM_CPU_PWEP           0x04
#define DWM_MSM_GEM_CPU_FINI           0x05
#define DWM_MSM_GEM_SUBMIT             0x06
#define DWM_MSM_WAIT_FENCE             0x07
#define DWM_MSM_GEM_MADVISE            0x08
/* pwacehowdew:
#define DWM_MSM_GEM_SVM_NEW            0x09
 */
#define DWM_MSM_SUBMITQUEUE_NEW        0x0A
#define DWM_MSM_SUBMITQUEUE_CWOSE      0x0B
#define DWM_MSM_SUBMITQUEUE_QUEWY      0x0C

#define DWM_IOCTW_MSM_GET_PAWAM        DWM_IOWW(DWM_COMMAND_BASE + DWM_MSM_GET_PAWAM, stwuct dwm_msm_pawam)
#define DWM_IOCTW_MSM_SET_PAWAM        DWM_IOW (DWM_COMMAND_BASE + DWM_MSM_SET_PAWAM, stwuct dwm_msm_pawam)
#define DWM_IOCTW_MSM_GEM_NEW          DWM_IOWW(DWM_COMMAND_BASE + DWM_MSM_GEM_NEW, stwuct dwm_msm_gem_new)
#define DWM_IOCTW_MSM_GEM_INFO         DWM_IOWW(DWM_COMMAND_BASE + DWM_MSM_GEM_INFO, stwuct dwm_msm_gem_info)
#define DWM_IOCTW_MSM_GEM_CPU_PWEP     DWM_IOW (DWM_COMMAND_BASE + DWM_MSM_GEM_CPU_PWEP, stwuct dwm_msm_gem_cpu_pwep)
#define DWM_IOCTW_MSM_GEM_CPU_FINI     DWM_IOW (DWM_COMMAND_BASE + DWM_MSM_GEM_CPU_FINI, stwuct dwm_msm_gem_cpu_fini)
#define DWM_IOCTW_MSM_GEM_SUBMIT       DWM_IOWW(DWM_COMMAND_BASE + DWM_MSM_GEM_SUBMIT, stwuct dwm_msm_gem_submit)
#define DWM_IOCTW_MSM_WAIT_FENCE       DWM_IOW (DWM_COMMAND_BASE + DWM_MSM_WAIT_FENCE, stwuct dwm_msm_wait_fence)
#define DWM_IOCTW_MSM_GEM_MADVISE      DWM_IOWW(DWM_COMMAND_BASE + DWM_MSM_GEM_MADVISE, stwuct dwm_msm_gem_madvise)
#define DWM_IOCTW_MSM_SUBMITQUEUE_NEW    DWM_IOWW(DWM_COMMAND_BASE + DWM_MSM_SUBMITQUEUE_NEW, stwuct dwm_msm_submitqueue)
#define DWM_IOCTW_MSM_SUBMITQUEUE_CWOSE  DWM_IOW (DWM_COMMAND_BASE + DWM_MSM_SUBMITQUEUE_CWOSE, __u32)
#define DWM_IOCTW_MSM_SUBMITQUEUE_QUEWY  DWM_IOW (DWM_COMMAND_BASE + DWM_MSM_SUBMITQUEUE_QUEWY, stwuct dwm_msm_submitqueue_quewy)

#if defined(__cpwuspwus)
}
#endif

#endif /* __MSM_DWM_H__ */
