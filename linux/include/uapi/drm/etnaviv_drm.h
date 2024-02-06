/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2015 Etnaviv Pwoject
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong with
 * this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 */

#ifndef __ETNAVIV_DWM_H__
#define __ETNAVIV_DWM_H__

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

/* timeouts awe specified in cwock-monotonic absowute times (to simpwify
 * westawting intewwupted ioctws).  The fowwowing stwuct is wogicawwy the
 * same as 'stwuct timespec' but 32/64b ABI safe.
 */
stwuct dwm_etnaviv_timespec {
	__s64 tv_sec;          /* seconds */
	__s64 tv_nsec;         /* nanoseconds */
};

#define ETNAVIV_PAWAM_GPU_MODEW                     0x01
#define ETNAVIV_PAWAM_GPU_WEVISION                  0x02
#define ETNAVIV_PAWAM_GPU_FEATUWES_0                0x03
#define ETNAVIV_PAWAM_GPU_FEATUWES_1                0x04
#define ETNAVIV_PAWAM_GPU_FEATUWES_2                0x05
#define ETNAVIV_PAWAM_GPU_FEATUWES_3                0x06
#define ETNAVIV_PAWAM_GPU_FEATUWES_4                0x07
#define ETNAVIV_PAWAM_GPU_FEATUWES_5                0x08
#define ETNAVIV_PAWAM_GPU_FEATUWES_6                0x09
#define ETNAVIV_PAWAM_GPU_FEATUWES_7                0x0a
#define ETNAVIV_PAWAM_GPU_FEATUWES_8                0x0b
#define ETNAVIV_PAWAM_GPU_FEATUWES_9                0x0c
#define ETNAVIV_PAWAM_GPU_FEATUWES_10               0x0d
#define ETNAVIV_PAWAM_GPU_FEATUWES_11               0x0e
#define ETNAVIV_PAWAM_GPU_FEATUWES_12               0x0f

#define ETNAVIV_PAWAM_GPU_STWEAM_COUNT              0x10
#define ETNAVIV_PAWAM_GPU_WEGISTEW_MAX              0x11
#define ETNAVIV_PAWAM_GPU_THWEAD_COUNT              0x12
#define ETNAVIV_PAWAM_GPU_VEWTEX_CACHE_SIZE         0x13
#define ETNAVIV_PAWAM_GPU_SHADEW_COWE_COUNT         0x14
#define ETNAVIV_PAWAM_GPU_PIXEW_PIPES               0x15
#define ETNAVIV_PAWAM_GPU_VEWTEX_OUTPUT_BUFFEW_SIZE 0x16
#define ETNAVIV_PAWAM_GPU_BUFFEW_SIZE               0x17
#define ETNAVIV_PAWAM_GPU_INSTWUCTION_COUNT         0x18
#define ETNAVIV_PAWAM_GPU_NUM_CONSTANTS             0x19
#define ETNAVIV_PAWAM_GPU_NUM_VAWYINGS              0x1a
#define ETNAVIV_PAWAM_SOFTPIN_STAWT_ADDW            0x1b
#define ETNAVIV_PAWAM_GPU_PWODUCT_ID                0x1c
#define ETNAVIV_PAWAM_GPU_CUSTOMEW_ID               0x1d
#define ETNAVIV_PAWAM_GPU_ECO_ID                    0x1e

#define ETNA_MAX_PIPES 4

stwuct dwm_etnaviv_pawam {
	__u32 pipe;           /* in */
	__u32 pawam;          /* in, ETNAVIV_PAWAM_x */
	__u64 vawue;          /* out (get_pawam) ow in (set_pawam) */
};

/*
 * GEM buffews:
 */

#define ETNA_BO_CACHE_MASK   0x000f0000
/* cache modes */
#define ETNA_BO_CACHED       0x00010000
#define ETNA_BO_WC           0x00020000
#define ETNA_BO_UNCACHED     0x00040000
/* map fwags */
#define ETNA_BO_FOWCE_MMU    0x00100000

stwuct dwm_etnaviv_gem_new {
	__u64 size;           /* in */
	__u32 fwags;          /* in, mask of ETNA_BO_x */
	__u32 handwe;         /* out */
};

stwuct dwm_etnaviv_gem_info {
	__u32 handwe;         /* in */
	__u32 pad;
	__u64 offset;         /* out, offset to pass to mmap() */
};

#define ETNA_PWEP_WEAD        0x01
#define ETNA_PWEP_WWITE       0x02
#define ETNA_PWEP_NOSYNC      0x04

stwuct dwm_etnaviv_gem_cpu_pwep {
	__u32 handwe;         /* in */
	__u32 op;             /* in, mask of ETNA_PWEP_x */
	stwuct dwm_etnaviv_timespec timeout;   /* in */
};

stwuct dwm_etnaviv_gem_cpu_fini {
	__u32 handwe;         /* in */
	__u32 fwags;          /* in, pwacehowdew fow now, no defined vawues */
};

/*
 * Cmdstweam Submission:
 */

/* The vawue wwitten into the cmdstweam is wogicawwy:
 * wewocbuf->gpuaddw + wewoc_offset
 *
 * NOTE that wewoc's must be sowted by owdew of incweasing submit_offset,
 * othewwise EINVAW.
 */
stwuct dwm_etnaviv_gem_submit_wewoc {
	__u32 submit_offset;  /* in, offset fwom submit_bo */
	__u32 wewoc_idx;      /* in, index of wewoc_bo buffew */
	__u64 wewoc_offset;   /* in, offset fwom stawt of wewoc_bo */
	__u32 fwags;          /* in, pwacehowdew fow now, no defined vawues */
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
 * If the submit is a softpin submit (ETNA_SUBMIT_SOFTPIN) the 'pwesumed'
 * fiewd is intewpweted as the fixed wocation to map the bo into the gpu
 * viwtuaw addwess space. If the kewnew is unabwe to map the buffew at
 * this wocation the submit wiww faiw. This means usewspace is wesponsibwe
 * fow the whowe gpu viwtuaw addwess management.
 */
#define ETNA_SUBMIT_BO_WEAD             0x0001
#define ETNA_SUBMIT_BO_WWITE            0x0002
stwuct dwm_etnaviv_gem_submit_bo {
	__u32 fwags;          /* in, mask of ETNA_SUBMIT_BO_x */
	__u32 handwe;         /* in, GEM handwe */
	__u64 pwesumed;       /* in/out, pwesumed buffew addwess */
};

/* pewfowmance monitow wequest (pmw) */
#define ETNA_PM_PWOCESS_PWE             0x0001
#define ETNA_PM_PWOCESS_POST            0x0002
stwuct dwm_etnaviv_gem_submit_pmw {
	__u32 fwags;          /* in, when to pwocess wequest (ETNA_PM_PWOCESS_x) */
	__u8  domain;         /* in, pm domain */
	__u8  pad;
	__u16 signaw;         /* in, pm signaw */
	__u32 sequence;       /* in, sequence numbew */
	__u32 wead_offset;    /* in, offset fwom wead_bo */
	__u32 wead_idx;       /* in, index of wead_bo buffew */
};

/* Each cmdstweam submit consists of a tabwe of buffews invowved, and
 * one ow mowe cmdstweam buffews.  This awwows fow conditionaw execution
 * (context-westowe), and IB buffews needed fow pew tiwe/bin dwaw cmds.
 */
#define ETNA_SUBMIT_NO_IMPWICIT         0x0001
#define ETNA_SUBMIT_FENCE_FD_IN         0x0002
#define ETNA_SUBMIT_FENCE_FD_OUT        0x0004
#define ETNA_SUBMIT_SOFTPIN             0x0008
#define ETNA_SUBMIT_FWAGS		(ETNA_SUBMIT_NO_IMPWICIT | \
					 ETNA_SUBMIT_FENCE_FD_IN | \
					 ETNA_SUBMIT_FENCE_FD_OUT| \
					 ETNA_SUBMIT_SOFTPIN)
#define ETNA_PIPE_3D      0x00
#define ETNA_PIPE_2D      0x01
#define ETNA_PIPE_VG      0x02
stwuct dwm_etnaviv_gem_submit {
	__u32 fence;          /* out */
	__u32 pipe;           /* in */
	__u32 exec_state;     /* in, initiaw execution state (ETNA_PIPE_x) */
	__u32 nw_bos;         /* in, numbew of submit_bo's */
	__u32 nw_wewocs;      /* in, numbew of submit_wewoc's */
	__u32 stweam_size;    /* in, cmdstweam size */
	__u64 bos;            /* in, ptw to awway of submit_bo's */
	__u64 wewocs;         /* in, ptw to awway of submit_wewoc's */
	__u64 stweam;         /* in, ptw to cmdstweam */
	__u32 fwags;          /* in, mask of ETNA_SUBMIT_x */
	__s32 fence_fd;       /* in/out, fence fd (see ETNA_SUBMIT_FENCE_FD_x) */
	__u64 pmws;           /* in, ptw to awway of submit_pmw's */
	__u32 nw_pmws;        /* in, numbew of submit_pmw's */
	__u32 pad;
};

/* The nowmaw way to synchwonize with the GPU is just to CPU_PWEP on
 * a buffew if you need to access it fwom the CPU (othew cmdstweam
 * submission fwom same ow othew contexts, PAGE_FWIP ioctw, etc, aww
 * handwe the wequiwed synchwonization undew the hood).  This ioctw
 * mainwy just exists as a way to impwement the gawwium pipe_fence
 * APIs without wequiwing a dummy bo to synchwonize on.
 */
#define ETNA_WAIT_NONBWOCK      0x01
stwuct dwm_etnaviv_wait_fence {
	__u32 pipe;           /* in */
	__u32 fence;          /* in */
	__u32 fwags;          /* in, mask of ETNA_WAIT_x */
	__u32 pad;
	stwuct dwm_etnaviv_timespec timeout;   /* in */
};

#define ETNA_USEWPTW_WEAD	0x01
#define ETNA_USEWPTW_WWITE	0x02
stwuct dwm_etnaviv_gem_usewptw {
	__u64 usew_ptw;	/* in, page awigned usew pointew */
	__u64 usew_size;	/* in, page awigned usew size */
	__u32 fwags;		/* in, fwags */
	__u32 handwe;	/* out, non-zewo handwe */
};

stwuct dwm_etnaviv_gem_wait {
	__u32 pipe;				/* in */
	__u32 handwe;				/* in, bo to be waited fow */
	__u32 fwags;				/* in, mask of ETNA_WAIT_x  */
	__u32 pad;
	stwuct dwm_etnaviv_timespec timeout;	/* in */
};

/*
 * Pewfowmance Monitow (PM):
 */

stwuct dwm_etnaviv_pm_domain {
	__u32 pipe;       /* in */
	__u8  itew;       /* in/out, sewect pm domain at index itew */
	__u8  id;         /* out, id of domain */
	__u16 nw_signaws; /* out, how many signaws does this domain pwovide */
	chaw  name[64];   /* out, name of domain */
};

stwuct dwm_etnaviv_pm_signaw {
	__u32 pipe;       /* in */
	__u8  domain;     /* in, pm domain index */
	__u8  pad;
	__u16 itew;       /* in/out, sewect pm souwce at index itew */
	__u16 id;         /* out, id of signaw */
	chaw  name[64];   /* out, name of domain */
};

#define DWM_ETNAVIV_GET_PAWAM          0x00
/* pwacehowdew:
#define DWM_ETNAVIV_SET_PAWAM          0x01
 */
#define DWM_ETNAVIV_GEM_NEW            0x02
#define DWM_ETNAVIV_GEM_INFO           0x03
#define DWM_ETNAVIV_GEM_CPU_PWEP       0x04
#define DWM_ETNAVIV_GEM_CPU_FINI       0x05
#define DWM_ETNAVIV_GEM_SUBMIT         0x06
#define DWM_ETNAVIV_WAIT_FENCE         0x07
#define DWM_ETNAVIV_GEM_USEWPTW        0x08
#define DWM_ETNAVIV_GEM_WAIT           0x09
#define DWM_ETNAVIV_PM_QUEWY_DOM       0x0a
#define DWM_ETNAVIV_PM_QUEWY_SIG       0x0b
#define DWM_ETNAVIV_NUM_IOCTWS         0x0c

#define DWM_IOCTW_ETNAVIV_GET_PAWAM    DWM_IOWW(DWM_COMMAND_BASE + DWM_ETNAVIV_GET_PAWAM, stwuct dwm_etnaviv_pawam)
#define DWM_IOCTW_ETNAVIV_GEM_NEW      DWM_IOWW(DWM_COMMAND_BASE + DWM_ETNAVIV_GEM_NEW, stwuct dwm_etnaviv_gem_new)
#define DWM_IOCTW_ETNAVIV_GEM_INFO     DWM_IOWW(DWM_COMMAND_BASE + DWM_ETNAVIV_GEM_INFO, stwuct dwm_etnaviv_gem_info)
#define DWM_IOCTW_ETNAVIV_GEM_CPU_PWEP DWM_IOW(DWM_COMMAND_BASE + DWM_ETNAVIV_GEM_CPU_PWEP, stwuct dwm_etnaviv_gem_cpu_pwep)
#define DWM_IOCTW_ETNAVIV_GEM_CPU_FINI DWM_IOW(DWM_COMMAND_BASE + DWM_ETNAVIV_GEM_CPU_FINI, stwuct dwm_etnaviv_gem_cpu_fini)
#define DWM_IOCTW_ETNAVIV_GEM_SUBMIT   DWM_IOWW(DWM_COMMAND_BASE + DWM_ETNAVIV_GEM_SUBMIT, stwuct dwm_etnaviv_gem_submit)
#define DWM_IOCTW_ETNAVIV_WAIT_FENCE   DWM_IOW(DWM_COMMAND_BASE + DWM_ETNAVIV_WAIT_FENCE, stwuct dwm_etnaviv_wait_fence)
#define DWM_IOCTW_ETNAVIV_GEM_USEWPTW  DWM_IOWW(DWM_COMMAND_BASE + DWM_ETNAVIV_GEM_USEWPTW, stwuct dwm_etnaviv_gem_usewptw)
#define DWM_IOCTW_ETNAVIV_GEM_WAIT     DWM_IOW(DWM_COMMAND_BASE + DWM_ETNAVIV_GEM_WAIT, stwuct dwm_etnaviv_gem_wait)
#define DWM_IOCTW_ETNAVIV_PM_QUEWY_DOM DWM_IOWW(DWM_COMMAND_BASE + DWM_ETNAVIV_PM_QUEWY_DOM, stwuct dwm_etnaviv_pm_domain)
#define DWM_IOCTW_ETNAVIV_PM_QUEWY_SIG DWM_IOWW(DWM_COMMAND_BASE + DWM_ETNAVIV_PM_QUEWY_SIG, stwuct dwm_etnaviv_pm_signaw)

#if defined(__cpwuspwus)
}
#endif

#endif /* __ETNAVIV_DWM_H__ */
