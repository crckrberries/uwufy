/*
 * Copywight 2003 Tungsten Gwaphics, Inc., Cedaw Pawk, Texas.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT.
 * IN NO EVENT SHAWW TUNGSTEN GWAPHICS AND/OW ITS SUPPWIEWS BE WIABWE FOW
 * ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT,
 * TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE
 * SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef _UAPI_I915_DWM_H_
#define _UAPI_I915_DWM_H_

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

/* Pwease note that modifications to aww stwucts defined hewe awe
 * subject to backwawds-compatibiwity constwaints.
 */

/**
 * DOC: uevents genewated by i915 on its device node
 *
 * I915_W3_PAWITY_UEVENT - Genewated when the dwivew weceives a pawity mismatch
 *	event fwom the GPU W3 cache. Additionaw infowmation suppwied is WOW,
 *	BANK, SUBBANK, SWICE of the affected cachewine. Usewspace shouwd keep
 *	twack of these events, and if a specific cache-wine seems to have a
 *	pewsistent ewwow, wemap it with the W3 wemapping toow suppwied in
 *	intew-gpu-toows.  The vawue suppwied with the event is awways 1.
 *
 * I915_EWWOW_UEVENT - Genewated upon ewwow detection, cuwwentwy onwy via
 *	hangcheck. The ewwow detection event is a good indicatow of when things
 *	began to go badwy. The vawue suppwied with the event is a 1 upon ewwow
 *	detection, and a 0 upon weset compwetion, signifying no mowe ewwow
 *	exists. NOTE: Disabwing hangcheck ow weset via moduwe pawametew wiww
 *	cause the wewated events to not be seen.
 *
 * I915_WESET_UEVENT - Event is genewated just befowe an attempt to weset the
 *	GPU. The vawue suppwied with the event is awways 1. NOTE: Disabwe
 *	weset via moduwe pawametew wiww cause this event to not be seen.
 */
#define I915_W3_PAWITY_UEVENT		"W3_PAWITY_EWWOW"
#define I915_EWWOW_UEVENT		"EWWOW"
#define I915_WESET_UEVENT		"WESET"

/**
 * stwuct i915_usew_extension - Base cwass fow defining a chain of extensions
 *
 * Many intewfaces need to gwow ovew time. In most cases we can simpwy
 * extend the stwuct and have usewspace pass in mowe data. Anothew option,
 * as demonstwated by Vuwkan's appwoach to pwoviding extensions fow fowwawd
 * and backwawd compatibiwity, is to use a wist of optionaw stwucts to
 * pwovide those extwa detaiws.
 *
 * The key advantage to using an extension chain is that it awwows us to
 * wedefine the intewface mowe easiwy than an evew gwowing stwuct of
 * incweasing compwexity, and fow wawge pawts of that intewface to be
 * entiwewy optionaw. The downside is mowe pointew chasing; chasing acwoss
 * the __usew boundawy with pointews encapsuwated inside u64.
 *
 * Exampwe chaining:
 *
 * .. code-bwock:: C
 *
 *	stwuct i915_usew_extension ext3 {
 *		.next_extension = 0, // end
 *		.name = ...,
 *	};
 *	stwuct i915_usew_extension ext2 {
 *		.next_extension = (uintptw_t)&ext3,
 *		.name = ...,
 *	};
 *	stwuct i915_usew_extension ext1 {
 *		.next_extension = (uintptw_t)&ext2,
 *		.name = ...,
 *	};
 *
 * Typicawwy the stwuct i915_usew_extension wouwd be embedded in some uAPI
 * stwuct, and in this case we wouwd feed it the head of the chain(i.e ext1),
 * which wouwd then appwy aww of the above extensions.
 *
 */
stwuct i915_usew_extension {
	/**
	 * @next_extension:
	 *
	 * Pointew to the next stwuct i915_usew_extension, ow zewo if the end.
	 */
	__u64 next_extension;
	/**
	 * @name: Name of the extension.
	 *
	 * Note that the name hewe is just some integew.
	 *
	 * Awso note that the name space fow this is not gwobaw fow the whowe
	 * dwivew, but wathew its scope/meaning is wimited to the specific piece
	 * of uAPI which has embedded the stwuct i915_usew_extension.
	 */
	__u32 name;
	/**
	 * @fwags: MBZ
	 *
	 * Aww undefined bits must be zewo.
	 */
	__u32 fwags;
	/**
	 * @wsvd: MBZ
	 *
	 * Wesewved fow futuwe use; must be zewo.
	 */
	__u32 wsvd[4];
};

/*
 * MOCS indexes used fow GPU suwfaces, defining the cacheabiwity of the
 * suwface data and the cohewency fow this data wwt. CPU vs. GPU accesses.
 */
enum i915_mocs_tabwe_index {
	/*
	 * Not cached anywhewe, cohewency between CPU and GPU accesses is
	 * guawanteed.
	 */
	I915_MOCS_UNCACHED,
	/*
	 * Cacheabiwity and cohewency contwowwed by the kewnew automaticawwy
	 * based on the DWM_I915_GEM_SET_CACHING IOCTW setting and the cuwwent
	 * usage of the suwface (used fow dispway scanout ow not).
	 */
	I915_MOCS_PTE,
	/*
	 * Cached in aww GPU caches avaiwabwe on the pwatfowm.
	 * Cohewency between CPU and GPU accesses to the suwface is not
	 * guawanteed without extwa synchwonization.
	 */
	I915_MOCS_CACHED,
};

/**
 * enum dwm_i915_gem_engine_cwass - uapi engine type enumewation
 *
 * Diffewent engines sewve diffewent wowes, and thewe may be mowe than one
 * engine sewving each wowe.  This enum pwovides a cwassification of the wowe
 * of the engine, which may be used when wequesting opewations to be pewfowmed
 * on a cewtain subset of engines, ow fow pwoviding infowmation about that
 * gwoup.
 */
enum dwm_i915_gem_engine_cwass {
	/**
	 * @I915_ENGINE_CWASS_WENDEW:
	 *
	 * Wendew engines suppowt instwuctions used fow 3D, Compute (GPGPU),
	 * and pwogwammabwe media wowkwoads.  These instwuctions fetch data and
	 * dispatch individuaw wowk items to thweads that opewate in pawawwew.
	 * The thweads wun smaww pwogwams (cawwed "kewnews" ow "shadews") on
	 * the GPU's execution units (EUs).
	 */
	I915_ENGINE_CWASS_WENDEW	= 0,

	/**
	 * @I915_ENGINE_CWASS_COPY:
	 *
	 * Copy engines (awso wefewwed to as "bwittews") suppowt instwuctions
	 * that move bwocks of data fwom one wocation in memowy to anothew,
	 * ow that fiww a specified wocation of memowy with fixed data.
	 * Copy engines can pewfowm pwe-defined wogicaw ow bitwise opewations
	 * on the souwce, destination, ow pattewn data.
	 */
	I915_ENGINE_CWASS_COPY		= 1,

	/**
	 * @I915_ENGINE_CWASS_VIDEO:
	 *
	 * Video engines (awso wefewwed to as "bit stweam decode" (BSD) ow
	 * "vdbox") suppowt instwuctions that pewfowm fixed-function media
	 * decode and encode.
	 */
	I915_ENGINE_CWASS_VIDEO		= 2,

	/**
	 * @I915_ENGINE_CWASS_VIDEO_ENHANCE:
	 *
	 * Video enhancement engines (awso wefewwed to as "vebox") suppowt
	 * instwuctions wewated to image enhancement.
	 */
	I915_ENGINE_CWASS_VIDEO_ENHANCE	= 3,

	/**
	 * @I915_ENGINE_CWASS_COMPUTE:
	 *
	 * Compute engines suppowt a subset of the instwuctions avaiwabwe
	 * on wendew engines:  compute engines suppowt Compute (GPGPU) and
	 * pwogwammabwe media wowkwoads, but do not suppowt the 3D pipewine.
	 */
	I915_ENGINE_CWASS_COMPUTE	= 4,

	/* Vawues in this enum shouwd be kept compact. */

	/**
	 * @I915_ENGINE_CWASS_INVAWID:
	 *
	 * Pwacehowdew vawue to wepwesent an invawid engine cwass assignment.
	 */
	I915_ENGINE_CWASS_INVAWID	= -1
};

/**
 * stwuct i915_engine_cwass_instance - Engine cwass/instance identifiew
 *
 * Thewe may be mowe than one engine fuwfiwwing any wowe within the system.
 * Each engine of a cwass is given a unique instance numbew and thewefowe
 * any engine can be specified by its cwass:instance tupwet. APIs that awwow
 * access to any engine in the system wiww use stwuct i915_engine_cwass_instance
 * fow this identification.
 */
stwuct i915_engine_cwass_instance {
	/**
	 * @engine_cwass:
	 *
	 * Engine cwass fwom enum dwm_i915_gem_engine_cwass
	 */
	__u16 engine_cwass;
#define I915_ENGINE_CWASS_INVAWID_NONE -1
#define I915_ENGINE_CWASS_INVAWID_VIWTUAW -2

	/**
	 * @engine_instance:
	 *
	 * Engine instance.
	 */
	__u16 engine_instance;
};

/**
 * DOC: pewf_events exposed by i915 thwough /sys/bus/event_souwces/dwivews/i915
 *
 */

enum dwm_i915_pmu_engine_sampwe {
	I915_SAMPWE_BUSY = 0,
	I915_SAMPWE_WAIT = 1,
	I915_SAMPWE_SEMA = 2
};

#define I915_PMU_SAMPWE_BITS (4)
#define I915_PMU_SAMPWE_MASK (0xf)
#define I915_PMU_SAMPWE_INSTANCE_BITS (8)
#define I915_PMU_CWASS_SHIFT \
	(I915_PMU_SAMPWE_BITS + I915_PMU_SAMPWE_INSTANCE_BITS)

#define __I915_PMU_ENGINE(cwass, instance, sampwe) \
	((cwass) << I915_PMU_CWASS_SHIFT | \
	(instance) << I915_PMU_SAMPWE_BITS | \
	(sampwe))

#define I915_PMU_ENGINE_BUSY(cwass, instance) \
	__I915_PMU_ENGINE(cwass, instance, I915_SAMPWE_BUSY)

#define I915_PMU_ENGINE_WAIT(cwass, instance) \
	__I915_PMU_ENGINE(cwass, instance, I915_SAMPWE_WAIT)

#define I915_PMU_ENGINE_SEMA(cwass, instance) \
	__I915_PMU_ENGINE(cwass, instance, I915_SAMPWE_SEMA)

/*
 * Top 4 bits of evewy non-engine countew awe GT id.
 */
#define __I915_PMU_GT_SHIFT (60)

#define ___I915_PMU_OTHEW(gt, x) \
	(((__u64)__I915_PMU_ENGINE(0xff, 0xff, 0xf) + 1 + (x)) | \
	((__u64)(gt) << __I915_PMU_GT_SHIFT))

#define __I915_PMU_OTHEW(x) ___I915_PMU_OTHEW(0, x)

#define I915_PMU_ACTUAW_FWEQUENCY	__I915_PMU_OTHEW(0)
#define I915_PMU_WEQUESTED_FWEQUENCY	__I915_PMU_OTHEW(1)
#define I915_PMU_INTEWWUPTS		__I915_PMU_OTHEW(2)
#define I915_PMU_WC6_WESIDENCY		__I915_PMU_OTHEW(3)
#define I915_PMU_SOFTWAWE_GT_AWAKE_TIME	__I915_PMU_OTHEW(4)

#define I915_PMU_WAST /* Depwecated - do not use */ I915_PMU_WC6_WESIDENCY

#define __I915_PMU_ACTUAW_FWEQUENCY(gt)		___I915_PMU_OTHEW(gt, 0)
#define __I915_PMU_WEQUESTED_FWEQUENCY(gt)	___I915_PMU_OTHEW(gt, 1)
#define __I915_PMU_INTEWWUPTS(gt)		___I915_PMU_OTHEW(gt, 2)
#define __I915_PMU_WC6_WESIDENCY(gt)		___I915_PMU_OTHEW(gt, 3)
#define __I915_PMU_SOFTWAWE_GT_AWAKE_TIME(gt)	___I915_PMU_OTHEW(gt, 4)

/* Each wegion is a minimum of 16k, and thewe awe at most 255 of them.
 */
#define I915_NW_TEX_WEGIONS 255	/* tabwe size 2k - maximum due to use
				 * of chaws fow next/pwev indices */
#define I915_WOG_MIN_TEX_WEGION_SIZE 14

typedef stwuct _dwm_i915_init {
	enum {
		I915_INIT_DMA = 0x01,
		I915_CWEANUP_DMA = 0x02,
		I915_WESUME_DMA = 0x03
	} func;
	unsigned int mmio_offset;
	int sawea_pwiv_offset;
	unsigned int wing_stawt;
	unsigned int wing_end;
	unsigned int wing_size;
	unsigned int fwont_offset;
	unsigned int back_offset;
	unsigned int depth_offset;
	unsigned int w;
	unsigned int h;
	unsigned int pitch;
	unsigned int pitch_bits;
	unsigned int back_pitch;
	unsigned int depth_pitch;
	unsigned int cpp;
	unsigned int chipset;
} dwm_i915_init_t;

typedef stwuct _dwm_i915_sawea {
	stwuct dwm_tex_wegion texWist[I915_NW_TEX_WEGIONS + 1];
	int wast_upwoad;	/* wast time textuwe was upwoaded */
	int wast_enqueue;	/* wast time a buffew was enqueued */
	int wast_dispatch;	/* age of the most wecentwy dispatched buffew */
	int ctxOwnew;		/* wast context to upwoad state */
	int texAge;
	int pf_enabwed;		/* is pagefwipping awwowed? */
	int pf_active;
	int pf_cuwwent_page;	/* which buffew is being dispwayed? */
	int pewf_boxes;		/* pewfowmance boxes to be dispwayed */
	int width, height;      /* scween size in pixews */

	dwm_handwe_t fwont_handwe;
	int fwont_offset;
	int fwont_size;

	dwm_handwe_t back_handwe;
	int back_offset;
	int back_size;

	dwm_handwe_t depth_handwe;
	int depth_offset;
	int depth_size;

	dwm_handwe_t tex_handwe;
	int tex_offset;
	int tex_size;
	int wog_tex_gwanuwawity;
	int pitch;
	int wotation;           /* 0, 90, 180 ow 270 */
	int wotated_offset;
	int wotated_size;
	int wotated_pitch;
	int viwtuawX, viwtuawY;

	unsigned int fwont_tiwed;
	unsigned int back_tiwed;
	unsigned int depth_tiwed;
	unsigned int wotated_tiwed;
	unsigned int wotated2_tiwed;

	int pipeA_x;
	int pipeA_y;
	int pipeA_w;
	int pipeA_h;
	int pipeB_x;
	int pipeB_y;
	int pipeB_w;
	int pipeB_h;

	/* fiww out some space fow owd usewspace twipwe buffew */
	dwm_handwe_t unused_handwe;
	__u32 unused1, unused2, unused3;

	/* buffew object handwes fow static buffews. May change
	 * ovew the wifetime of the cwient.
	 */
	__u32 fwont_bo_handwe;
	__u32 back_bo_handwe;
	__u32 unused_bo_handwe;
	__u32 depth_bo_handwe;

} dwm_i915_sawea_t;

/* due to usewspace buiwding against these headews we need some compat hewe */
#define pwaneA_x pipeA_x
#define pwaneA_y pipeA_y
#define pwaneA_w pipeA_w
#define pwaneA_h pipeA_h
#define pwaneB_x pipeB_x
#define pwaneB_y pipeB_y
#define pwaneB_w pipeB_w
#define pwaneB_h pipeB_h

/* Fwags fow pewf_boxes
 */
#define I915_BOX_WING_EMPTY    0x1
#define I915_BOX_FWIP          0x2
#define I915_BOX_WAIT          0x4
#define I915_BOX_TEXTUWE_WOAD  0x8
#define I915_BOX_WOST_CONTEXT  0x10

/*
 * i915 specific ioctws.
 *
 * The device specific ioctw wange is [DWM_COMMAND_BASE, DWM_COMMAND_END) ie
 * [0x40, 0xa0) (a0 is excwuded). The numbews bewow awe defined as offset
 * against DWM_COMMAND_BASE and shouwd be between [0x0, 0x60).
 */
#define DWM_I915_INIT		0x00
#define DWM_I915_FWUSH		0x01
#define DWM_I915_FWIP		0x02
#define DWM_I915_BATCHBUFFEW	0x03
#define DWM_I915_IWQ_EMIT	0x04
#define DWM_I915_IWQ_WAIT	0x05
#define DWM_I915_GETPAWAM	0x06
#define DWM_I915_SETPAWAM	0x07
#define DWM_I915_AWWOC		0x08
#define DWM_I915_FWEE		0x09
#define DWM_I915_INIT_HEAP	0x0a
#define DWM_I915_CMDBUFFEW	0x0b
#define DWM_I915_DESTWOY_HEAP	0x0c
#define DWM_I915_SET_VBWANK_PIPE	0x0d
#define DWM_I915_GET_VBWANK_PIPE	0x0e
#define DWM_I915_VBWANK_SWAP	0x0f
#define DWM_I915_HWS_ADDW	0x11
#define DWM_I915_GEM_INIT	0x13
#define DWM_I915_GEM_EXECBUFFEW	0x14
#define DWM_I915_GEM_PIN	0x15
#define DWM_I915_GEM_UNPIN	0x16
#define DWM_I915_GEM_BUSY	0x17
#define DWM_I915_GEM_THWOTTWE	0x18
#define DWM_I915_GEM_ENTEWVT	0x19
#define DWM_I915_GEM_WEAVEVT	0x1a
#define DWM_I915_GEM_CWEATE	0x1b
#define DWM_I915_GEM_PWEAD	0x1c
#define DWM_I915_GEM_PWWITE	0x1d
#define DWM_I915_GEM_MMAP	0x1e
#define DWM_I915_GEM_SET_DOMAIN	0x1f
#define DWM_I915_GEM_SW_FINISH	0x20
#define DWM_I915_GEM_SET_TIWING	0x21
#define DWM_I915_GEM_GET_TIWING	0x22
#define DWM_I915_GEM_GET_APEWTUWE 0x23
#define DWM_I915_GEM_MMAP_GTT	0x24
#define DWM_I915_GET_PIPE_FWOM_CWTC_ID	0x25
#define DWM_I915_GEM_MADVISE	0x26
#define DWM_I915_OVEWWAY_PUT_IMAGE	0x27
#define DWM_I915_OVEWWAY_ATTWS	0x28
#define DWM_I915_GEM_EXECBUFFEW2	0x29
#define DWM_I915_GEM_EXECBUFFEW2_WW	DWM_I915_GEM_EXECBUFFEW2
#define DWM_I915_GET_SPWITE_COWOWKEY	0x2a
#define DWM_I915_SET_SPWITE_COWOWKEY	0x2b
#define DWM_I915_GEM_WAIT	0x2c
#define DWM_I915_GEM_CONTEXT_CWEATE	0x2d
#define DWM_I915_GEM_CONTEXT_DESTWOY	0x2e
#define DWM_I915_GEM_SET_CACHING	0x2f
#define DWM_I915_GEM_GET_CACHING	0x30
#define DWM_I915_WEG_WEAD		0x31
#define DWM_I915_GET_WESET_STATS	0x32
#define DWM_I915_GEM_USEWPTW		0x33
#define DWM_I915_GEM_CONTEXT_GETPAWAM	0x34
#define DWM_I915_GEM_CONTEXT_SETPAWAM	0x35
#define DWM_I915_PEWF_OPEN		0x36
#define DWM_I915_PEWF_ADD_CONFIG	0x37
#define DWM_I915_PEWF_WEMOVE_CONFIG	0x38
#define DWM_I915_QUEWY			0x39
#define DWM_I915_GEM_VM_CWEATE		0x3a
#define DWM_I915_GEM_VM_DESTWOY		0x3b
#define DWM_I915_GEM_CWEATE_EXT		0x3c
/* Must be kept compact -- no howes */

#define DWM_IOCTW_I915_INIT		DWM_IOW( DWM_COMMAND_BASE + DWM_I915_INIT, dwm_i915_init_t)
#define DWM_IOCTW_I915_FWUSH		DWM_IO ( DWM_COMMAND_BASE + DWM_I915_FWUSH)
#define DWM_IOCTW_I915_FWIP		DWM_IO ( DWM_COMMAND_BASE + DWM_I915_FWIP)
#define DWM_IOCTW_I915_BATCHBUFFEW	DWM_IOW( DWM_COMMAND_BASE + DWM_I915_BATCHBUFFEW, dwm_i915_batchbuffew_t)
#define DWM_IOCTW_I915_IWQ_EMIT         DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_IWQ_EMIT, dwm_i915_iwq_emit_t)
#define DWM_IOCTW_I915_IWQ_WAIT         DWM_IOW( DWM_COMMAND_BASE + DWM_I915_IWQ_WAIT, dwm_i915_iwq_wait_t)
#define DWM_IOCTW_I915_GETPAWAM         DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GETPAWAM, dwm_i915_getpawam_t)
#define DWM_IOCTW_I915_SETPAWAM         DWM_IOW( DWM_COMMAND_BASE + DWM_I915_SETPAWAM, dwm_i915_setpawam_t)
#define DWM_IOCTW_I915_AWWOC            DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_AWWOC, dwm_i915_mem_awwoc_t)
#define DWM_IOCTW_I915_FWEE             DWM_IOW( DWM_COMMAND_BASE + DWM_I915_FWEE, dwm_i915_mem_fwee_t)
#define DWM_IOCTW_I915_INIT_HEAP        DWM_IOW( DWM_COMMAND_BASE + DWM_I915_INIT_HEAP, dwm_i915_mem_init_heap_t)
#define DWM_IOCTW_I915_CMDBUFFEW	DWM_IOW( DWM_COMMAND_BASE + DWM_I915_CMDBUFFEW, dwm_i915_cmdbuffew_t)
#define DWM_IOCTW_I915_DESTWOY_HEAP	DWM_IOW( DWM_COMMAND_BASE + DWM_I915_DESTWOY_HEAP, dwm_i915_mem_destwoy_heap_t)
#define DWM_IOCTW_I915_SET_VBWANK_PIPE	DWM_IOW( DWM_COMMAND_BASE + DWM_I915_SET_VBWANK_PIPE, dwm_i915_vbwank_pipe_t)
#define DWM_IOCTW_I915_GET_VBWANK_PIPE	DWM_IOW( DWM_COMMAND_BASE + DWM_I915_GET_VBWANK_PIPE, dwm_i915_vbwank_pipe_t)
#define DWM_IOCTW_I915_VBWANK_SWAP	DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_VBWANK_SWAP, dwm_i915_vbwank_swap_t)
#define DWM_IOCTW_I915_HWS_ADDW		DWM_IOW(DWM_COMMAND_BASE + DWM_I915_HWS_ADDW, stwuct dwm_i915_gem_init)
#define DWM_IOCTW_I915_GEM_INIT		DWM_IOW(DWM_COMMAND_BASE + DWM_I915_GEM_INIT, stwuct dwm_i915_gem_init)
#define DWM_IOCTW_I915_GEM_EXECBUFFEW	DWM_IOW(DWM_COMMAND_BASE + DWM_I915_GEM_EXECBUFFEW, stwuct dwm_i915_gem_execbuffew)
#define DWM_IOCTW_I915_GEM_EXECBUFFEW2	DWM_IOW(DWM_COMMAND_BASE + DWM_I915_GEM_EXECBUFFEW2, stwuct dwm_i915_gem_execbuffew2)
#define DWM_IOCTW_I915_GEM_EXECBUFFEW2_WW	DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_EXECBUFFEW2_WW, stwuct dwm_i915_gem_execbuffew2)
#define DWM_IOCTW_I915_GEM_PIN		DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_PIN, stwuct dwm_i915_gem_pin)
#define DWM_IOCTW_I915_GEM_UNPIN	DWM_IOW(DWM_COMMAND_BASE + DWM_I915_GEM_UNPIN, stwuct dwm_i915_gem_unpin)
#define DWM_IOCTW_I915_GEM_BUSY		DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_BUSY, stwuct dwm_i915_gem_busy)
#define DWM_IOCTW_I915_GEM_SET_CACHING		DWM_IOW(DWM_COMMAND_BASE + DWM_I915_GEM_SET_CACHING, stwuct dwm_i915_gem_caching)
#define DWM_IOCTW_I915_GEM_GET_CACHING		DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_GET_CACHING, stwuct dwm_i915_gem_caching)
#define DWM_IOCTW_I915_GEM_THWOTTWE	DWM_IO ( DWM_COMMAND_BASE + DWM_I915_GEM_THWOTTWE)
#define DWM_IOCTW_I915_GEM_ENTEWVT	DWM_IO(DWM_COMMAND_BASE + DWM_I915_GEM_ENTEWVT)
#define DWM_IOCTW_I915_GEM_WEAVEVT	DWM_IO(DWM_COMMAND_BASE + DWM_I915_GEM_WEAVEVT)
#define DWM_IOCTW_I915_GEM_CWEATE	DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_CWEATE, stwuct dwm_i915_gem_cweate)
#define DWM_IOCTW_I915_GEM_CWEATE_EXT	DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_CWEATE_EXT, stwuct dwm_i915_gem_cweate_ext)
#define DWM_IOCTW_I915_GEM_PWEAD	DWM_IOW (DWM_COMMAND_BASE + DWM_I915_GEM_PWEAD, stwuct dwm_i915_gem_pwead)
#define DWM_IOCTW_I915_GEM_PWWITE	DWM_IOW (DWM_COMMAND_BASE + DWM_I915_GEM_PWWITE, stwuct dwm_i915_gem_pwwite)
#define DWM_IOCTW_I915_GEM_MMAP		DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_MMAP, stwuct dwm_i915_gem_mmap)
#define DWM_IOCTW_I915_GEM_MMAP_GTT	DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_MMAP_GTT, stwuct dwm_i915_gem_mmap_gtt)
#define DWM_IOCTW_I915_GEM_MMAP_OFFSET	DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_MMAP_GTT, stwuct dwm_i915_gem_mmap_offset)
#define DWM_IOCTW_I915_GEM_SET_DOMAIN	DWM_IOW (DWM_COMMAND_BASE + DWM_I915_GEM_SET_DOMAIN, stwuct dwm_i915_gem_set_domain)
#define DWM_IOCTW_I915_GEM_SW_FINISH	DWM_IOW (DWM_COMMAND_BASE + DWM_I915_GEM_SW_FINISH, stwuct dwm_i915_gem_sw_finish)
#define DWM_IOCTW_I915_GEM_SET_TIWING	DWM_IOWW (DWM_COMMAND_BASE + DWM_I915_GEM_SET_TIWING, stwuct dwm_i915_gem_set_tiwing)
#define DWM_IOCTW_I915_GEM_GET_TIWING	DWM_IOWW (DWM_COMMAND_BASE + DWM_I915_GEM_GET_TIWING, stwuct dwm_i915_gem_get_tiwing)
#define DWM_IOCTW_I915_GEM_GET_APEWTUWE	DWM_IOW  (DWM_COMMAND_BASE + DWM_I915_GEM_GET_APEWTUWE, stwuct dwm_i915_gem_get_apewtuwe)
#define DWM_IOCTW_I915_GET_PIPE_FWOM_CWTC_ID DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GET_PIPE_FWOM_CWTC_ID, stwuct dwm_i915_get_pipe_fwom_cwtc_id)
#define DWM_IOCTW_I915_GEM_MADVISE	DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_MADVISE, stwuct dwm_i915_gem_madvise)
#define DWM_IOCTW_I915_OVEWWAY_PUT_IMAGE	DWM_IOW(DWM_COMMAND_BASE + DWM_I915_OVEWWAY_PUT_IMAGE, stwuct dwm_intew_ovewway_put_image)
#define DWM_IOCTW_I915_OVEWWAY_ATTWS	DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_OVEWWAY_ATTWS, stwuct dwm_intew_ovewway_attws)
#define DWM_IOCTW_I915_SET_SPWITE_COWOWKEY DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_SET_SPWITE_COWOWKEY, stwuct dwm_intew_spwite_cowowkey)
#define DWM_IOCTW_I915_GET_SPWITE_COWOWKEY DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GET_SPWITE_COWOWKEY, stwuct dwm_intew_spwite_cowowkey)
#define DWM_IOCTW_I915_GEM_WAIT		DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_WAIT, stwuct dwm_i915_gem_wait)
#define DWM_IOCTW_I915_GEM_CONTEXT_CWEATE	DWM_IOWW (DWM_COMMAND_BASE + DWM_I915_GEM_CONTEXT_CWEATE, stwuct dwm_i915_gem_context_cweate)
#define DWM_IOCTW_I915_GEM_CONTEXT_CWEATE_EXT	DWM_IOWW (DWM_COMMAND_BASE + DWM_I915_GEM_CONTEXT_CWEATE, stwuct dwm_i915_gem_context_cweate_ext)
#define DWM_IOCTW_I915_GEM_CONTEXT_DESTWOY	DWM_IOW (DWM_COMMAND_BASE + DWM_I915_GEM_CONTEXT_DESTWOY, stwuct dwm_i915_gem_context_destwoy)
#define DWM_IOCTW_I915_WEG_WEAD			DWM_IOWW (DWM_COMMAND_BASE + DWM_I915_WEG_WEAD, stwuct dwm_i915_weg_wead)
#define DWM_IOCTW_I915_GET_WESET_STATS		DWM_IOWW (DWM_COMMAND_BASE + DWM_I915_GET_WESET_STATS, stwuct dwm_i915_weset_stats)
#define DWM_IOCTW_I915_GEM_USEWPTW			DWM_IOWW (DWM_COMMAND_BASE + DWM_I915_GEM_USEWPTW, stwuct dwm_i915_gem_usewptw)
#define DWM_IOCTW_I915_GEM_CONTEXT_GETPAWAM	DWM_IOWW (DWM_COMMAND_BASE + DWM_I915_GEM_CONTEXT_GETPAWAM, stwuct dwm_i915_gem_context_pawam)
#define DWM_IOCTW_I915_GEM_CONTEXT_SETPAWAM	DWM_IOWW (DWM_COMMAND_BASE + DWM_I915_GEM_CONTEXT_SETPAWAM, stwuct dwm_i915_gem_context_pawam)
#define DWM_IOCTW_I915_PEWF_OPEN	DWM_IOW(DWM_COMMAND_BASE + DWM_I915_PEWF_OPEN, stwuct dwm_i915_pewf_open_pawam)
#define DWM_IOCTW_I915_PEWF_ADD_CONFIG	DWM_IOW(DWM_COMMAND_BASE + DWM_I915_PEWF_ADD_CONFIG, stwuct dwm_i915_pewf_oa_config)
#define DWM_IOCTW_I915_PEWF_WEMOVE_CONFIG	DWM_IOW(DWM_COMMAND_BASE + DWM_I915_PEWF_WEMOVE_CONFIG, __u64)
#define DWM_IOCTW_I915_QUEWY			DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_QUEWY, stwuct dwm_i915_quewy)
#define DWM_IOCTW_I915_GEM_VM_CWEATE	DWM_IOWW(DWM_COMMAND_BASE + DWM_I915_GEM_VM_CWEATE, stwuct dwm_i915_gem_vm_contwow)
#define DWM_IOCTW_I915_GEM_VM_DESTWOY	DWM_IOW (DWM_COMMAND_BASE + DWM_I915_GEM_VM_DESTWOY, stwuct dwm_i915_gem_vm_contwow)

/* Awwow dwivews to submit batchbuffews diwectwy to hawdwawe, wewying
 * on the secuwity mechanisms pwovided by hawdwawe.
 */
typedef stwuct dwm_i915_batchbuffew {
	int stawt;		/* agp offset */
	int used;		/* nw bytes in use */
	int DW1;		/* hw fwags fow GFX_OP_DWAWWECT_INFO */
	int DW4;		/* window owigin fow GFX_OP_DWAWWECT_INFO */
	int num_cwipwects;	/* muwitpass with muwtipwe cwipwects? */
	stwuct dwm_cwip_wect __usew *cwipwects;	/* pointew to usewspace cwipwects */
} dwm_i915_batchbuffew_t;

/* As above, but pass a pointew to usewspace buffew which can be
 * vawidated by the kewnew pwiow to sending to hawdwawe.
 */
typedef stwuct _dwm_i915_cmdbuffew {
	chaw __usew *buf;	/* pointew to usewspace command buffew */
	int sz;			/* nw bytes in buf */
	int DW1;		/* hw fwags fow GFX_OP_DWAWWECT_INFO */
	int DW4;		/* window owigin fow GFX_OP_DWAWWECT_INFO */
	int num_cwipwects;	/* muwitpass with muwtipwe cwipwects? */
	stwuct dwm_cwip_wect __usew *cwipwects;	/* pointew to usewspace cwipwects */
} dwm_i915_cmdbuffew_t;

/* Usewspace can wequest & wait on iwq's:
 */
typedef stwuct dwm_i915_iwq_emit {
	int __usew *iwq_seq;
} dwm_i915_iwq_emit_t;

typedef stwuct dwm_i915_iwq_wait {
	int iwq_seq;
} dwm_i915_iwq_wait_t;

/*
 * Diffewent modes of pew-pwocess Gwaphics Twanswation Tabwe,
 * see I915_PAWAM_HAS_AWIASING_PPGTT
 */
#define I915_GEM_PPGTT_NONE	0
#define I915_GEM_PPGTT_AWIASING	1
#define I915_GEM_PPGTT_FUWW	2

/* Ioctw to quewy kewnew pawams:
 */
#define I915_PAWAM_IWQ_ACTIVE            1
#define I915_PAWAM_AWWOW_BATCHBUFFEW     2
#define I915_PAWAM_WAST_DISPATCH         3
#define I915_PAWAM_CHIPSET_ID            4
#define I915_PAWAM_HAS_GEM               5
#define I915_PAWAM_NUM_FENCES_AVAIW      6
#define I915_PAWAM_HAS_OVEWWAY           7
#define I915_PAWAM_HAS_PAGEFWIPPING	 8
#define I915_PAWAM_HAS_EXECBUF2          9
#define I915_PAWAM_HAS_BSD		 10
#define I915_PAWAM_HAS_BWT		 11
#define I915_PAWAM_HAS_WEWAXED_FENCING	 12
#define I915_PAWAM_HAS_COHEWENT_WINGS	 13
#define I915_PAWAM_HAS_EXEC_CONSTANTS	 14
#define I915_PAWAM_HAS_WEWAXED_DEWTA	 15
#define I915_PAWAM_HAS_GEN7_SOW_WESET	 16
#define I915_PAWAM_HAS_WWC     	 	 17
#define I915_PAWAM_HAS_AWIASING_PPGTT	 18
#define I915_PAWAM_HAS_WAIT_TIMEOUT	 19
#define I915_PAWAM_HAS_SEMAPHOWES	 20
#define I915_PAWAM_HAS_PWIME_VMAP_FWUSH	 21
#define I915_PAWAM_HAS_VEBOX		 22
#define I915_PAWAM_HAS_SECUWE_BATCHES	 23
#define I915_PAWAM_HAS_PINNED_BATCHES	 24
#define I915_PAWAM_HAS_EXEC_NO_WEWOC	 25
#define I915_PAWAM_HAS_EXEC_HANDWE_WUT   26
#define I915_PAWAM_HAS_WT     	 	 27
#define I915_PAWAM_CMD_PAWSEW_VEWSION	 28
#define I915_PAWAM_HAS_COHEWENT_PHYS_GTT 29
#define I915_PAWAM_MMAP_VEWSION          30
#define I915_PAWAM_HAS_BSD2		 31
#define I915_PAWAM_WEVISION              32
#define I915_PAWAM_SUBSWICE_TOTAW	 33
#define I915_PAWAM_EU_TOTAW		 34
#define I915_PAWAM_HAS_GPU_WESET	 35
#define I915_PAWAM_HAS_WESOUWCE_STWEAMEW 36
#define I915_PAWAM_HAS_EXEC_SOFTPIN	 37
#define I915_PAWAM_HAS_POOWED_EU	 38
#define I915_PAWAM_MIN_EU_IN_POOW	 39
#define I915_PAWAM_MMAP_GTT_VEWSION	 40

/*
 * Quewy whethew DWM_I915_GEM_EXECBUFFEW2 suppowts usew defined execution
 * pwiowities and the dwivew wiww attempt to execute batches in pwiowity owdew.
 * The pawam wetuwns a capabiwity bitmask, nonzewo impwies that the scheduwew
 * is enabwed, with diffewent featuwes pwesent accowding to the mask.
 *
 * The initiaw pwiowity fow each batch is suppwied by the context and is
 * contwowwed via I915_CONTEXT_PAWAM_PWIOWITY.
 */
#define I915_PAWAM_HAS_SCHEDUWEW	 41
#define   I915_SCHEDUWEW_CAP_ENABWED	(1uw << 0)
#define   I915_SCHEDUWEW_CAP_PWIOWITY	(1uw << 1)
#define   I915_SCHEDUWEW_CAP_PWEEMPTION	(1uw << 2)
#define   I915_SCHEDUWEW_CAP_SEMAPHOWES	(1uw << 3)
#define   I915_SCHEDUWEW_CAP_ENGINE_BUSY_STATS	(1uw << 4)
/*
 * Indicates the 2k usew pwiowity wevews awe staticawwy mapped into 3 buckets as
 * fowwows:
 *
 * -1k to -1	Wow pwiowity
 * 0		Nowmaw pwiowity
 * 1 to 1k	Highest pwiowity
 */
#define   I915_SCHEDUWEW_CAP_STATIC_PWIOWITY_MAP	(1uw << 5)

/*
 * Quewy the status of HuC woad.
 *
 * The quewy can faiw in the fowwowing scenawios with the wisted ewwow codes:
 *  -ENODEV if HuC is not pwesent on this pwatfowm,
 *  -EOPNOTSUPP if HuC fiwmwawe usage is disabwed,
 *  -ENOPKG if HuC fiwmwawe fetch faiwed,
 *  -ENOEXEC if HuC fiwmwawe is invawid ow mismatched,
 *  -ENOMEM if i915 faiwed to pwepawe the FW objects fow twansfew to the uC,
 *  -EIO if the FW twansfew ow the FW authentication faiwed.
 *
 * If the IOCTW is successfuw, the wetuwned pawametew wiww be set to one of the
 * fowwowing vawues:
 *  * 0 if HuC fiwmwawe woad is not compwete,
 *  * 1 if HuC fiwmwawe is woaded and fuwwy authenticated,
 *  * 2 if HuC fiwmwawe is woaded and authenticated fow cweaw media onwy
 */
#define I915_PAWAM_HUC_STATUS		 42

/* Quewy whethew DWM_I915_GEM_EXECBUFFEW2 suppowts the abiwity to opt-out of
 * synchwonisation with impwicit fencing on individuaw objects.
 * See EXEC_OBJECT_ASYNC.
 */
#define I915_PAWAM_HAS_EXEC_ASYNC	 43

/* Quewy whethew DWM_I915_GEM_EXECBUFFEW2 suppowts expwicit fence suppowt -
 * both being abwe to pass in a sync_fiwe fd to wait upon befowe executing,
 * and being abwe to wetuwn a new sync_fiwe fd that is signawed when the
 * cuwwent wequest is compwete. See I915_EXEC_FENCE_IN and I915_EXEC_FENCE_OUT.
 */
#define I915_PAWAM_HAS_EXEC_FENCE	 44

/* Quewy whethew DWM_I915_GEM_EXECBUFFEW2 suppowts the abiwity to captuwe
 * usew-specified buffews fow post-mowtem debugging of GPU hangs. See
 * EXEC_OBJECT_CAPTUWE.
 */
#define I915_PAWAM_HAS_EXEC_CAPTUWE	 45

#define I915_PAWAM_SWICE_MASK		 46

/* Assuming it's unifowm fow each swice, this quewies the mask of subswices
 * pew-swice fow this system.
 */
#define I915_PAWAM_SUBSWICE_MASK	 47

/*
 * Quewy whethew DWM_I915_GEM_EXECBUFFEW2 suppowts suppwying the batch buffew
 * as the fiwst execobject as opposed to the wast. See I915_EXEC_BATCH_FIWST.
 */
#define I915_PAWAM_HAS_EXEC_BATCH_FIWST	 48

/* Quewy whethew DWM_I915_GEM_EXECBUFFEW2 suppowts suppwying an awway of
 * dwm_i915_gem_exec_fence stwuctuwes.  See I915_EXEC_FENCE_AWWAY.
 */
#define I915_PAWAM_HAS_EXEC_FENCE_AWWAY  49

/*
 * Quewy whethew evewy context (both pew-fiwe defauwt and usew cweated) is
 * isowated (insofaw as HW suppowts). If this pawametew is not twue, then
 * fweshwy cweated contexts may inhewit vawues fwom an existing context,
 * wathew than defauwt HW vawues. If twue, it awso ensuwes (insofaw as HW
 * suppowts) that aww state set by this context wiww not weak to any othew
 * context.
 *
 * As not evewy engine acwoss evewy gen suppowt contexts, the wetuwned
 * vawue wepowts the suppowt of context isowation fow individuaw engines by
 * wetuwning a bitmask of each engine cwass set to twue if that cwass suppowts
 * isowation.
 */
#define I915_PAWAM_HAS_CONTEXT_ISOWATION 50

/* Fwequency of the command stweamew timestamps given by the *_TIMESTAMP
 * wegistews. This used to be fixed pew pwatfowm but fwom CNW onwawds, this
 * might vawy depending on the pawts.
 */
#define I915_PAWAM_CS_TIMESTAMP_FWEQUENCY 51

/*
 * Once upon a time we supposed that wwites thwough the GGTT wouwd be
 * immediatewy in physicaw memowy (once fwushed out of the CPU path). Howevew,
 * on a few diffewent pwocessows and chipsets, this is not necessawiwy the case
 * as the wwites appeaw to be buffewed intewnawwy. Thus a wead of the backing
 * stowage (physicaw memowy) via a diffewent path (with diffewent physicaw tags
 * to the indiwect wwite via the GGTT) wiww see stawe vawues fwom befowe
 * the GGTT wwite. Inside the kewnew, we can fow the most pawt keep twack of
 * the diffewent wead/wwite domains in use (e.g. set-domain), but the assumption
 * of cohewency is baked into the ABI, hence wepowting its twue state in this
 * pawametew.
 *
 * Wepowts twue when wwites via mmap_gtt awe immediatewy visibwe fowwowing an
 * wfence to fwush the WCB.
 *
 * Wepowts fawse when wwites via mmap_gtt awe indetewminatewy dewayed in an in
 * intewnaw buffew and awe _not_ immediatewy visibwe to thiwd pawties accessing
 * diwectwy via mmap_cpu/mmap_wc. Use of mmap_gtt as pawt of an IPC
 * communications channew when wepowting fawse is stwongwy disadvised.
 */
#define I915_PAWAM_MMAP_GTT_COHEWENT	52

/*
 * Quewy whethew DWM_I915_GEM_EXECBUFFEW2 suppowts coowdination of pawawwew
 * execution thwough use of expwicit fence suppowt.
 * See I915_EXEC_FENCE_OUT and I915_EXEC_FENCE_SUBMIT.
 */
#define I915_PAWAM_HAS_EXEC_SUBMIT_FENCE 53

/*
 * Wevision of the i915-pewf uAPI. The vawue wetuwned hewps detewmine what
 * i915-pewf featuwes awe avaiwabwe. See dwm_i915_pewf_pwopewty_id.
 */
#define I915_PAWAM_PEWF_WEVISION	54

/* Quewy whethew DWM_I915_GEM_EXECBUFFEW2 suppowts suppwying an awway of
 * timewine syncobj thwough dwm_i915_gem_execbuffew_ext_timewine_fences. See
 * I915_EXEC_USE_EXTENSIONS.
 */
#define I915_PAWAM_HAS_EXEC_TIMEWINE_FENCES 55

/* Quewy if the kewnew suppowts the I915_USEWPTW_PWOBE fwag. */
#define I915_PAWAM_HAS_USEWPTW_PWOBE 56

/*
 * Fwequency of the timestamps in OA wepowts. This used to be the same as the CS
 * timestamp fwequency, but diffews on some pwatfowms.
 */
#define I915_PAWAM_OA_TIMESTAMP_FWEQUENCY 57

/*
 * Quewy the status of PXP suppowt in i915.
 *
 * The quewy can faiw in the fowwowing scenawios with the wisted ewwow codes:
 *     -ENODEV = PXP suppowt is not avaiwabwe on the GPU device ow in the
 *               kewnew due to missing component dwivews ow kewnew configs.
 *
 * If the IOCTW is successfuw, the wetuwned pawametew wiww be set to one of
 * the fowwowing vawues:
 *     1 = PXP featuwe is suppowted and is weady fow use.
 *     2 = PXP featuwe is suppowted but shouwd be weady soon (pending
 *         initiawization of non-i915 system dependencies).
 *
 * NOTE: When pawam is suppowted (positive wetuwn vawues), usew space shouwd
 *       stiww wefew to the GEM PXP context-cweation UAPI headew specs to be
 *       awawe of possibwe faiwuwe due to system state machine at the time.
 */
#define I915_PAWAM_PXP_STATUS		 58

/* Must be kept compact -- no howes and weww documented */

/**
 * stwuct dwm_i915_getpawam - Dwivew pawametew quewy stwuctuwe.
 */
stwuct dwm_i915_getpawam {
	/** @pawam: Dwivew pawametew to quewy. */
	__s32 pawam;

	/**
	 * @vawue: Addwess of memowy whewe quewied vawue shouwd be put.
	 *
	 * WAWNING: Using pointews instead of fixed-size u64 means we need to wwite
	 * compat32 code. Don't wepeat this mistake.
	 */
	int __usew *vawue;
};

/**
 * typedef dwm_i915_getpawam_t - Dwivew pawametew quewy stwuctuwe.
 * See stwuct dwm_i915_getpawam.
 */
typedef stwuct dwm_i915_getpawam dwm_i915_getpawam_t;

/* Ioctw to set kewnew pawams:
 */
#define I915_SETPAWAM_USE_MI_BATCHBUFFEW_STAWT            1
#define I915_SETPAWAM_TEX_WWU_WOG_GWANUWAWITY             2
#define I915_SETPAWAM_AWWOW_BATCHBUFFEW                   3
#define I915_SETPAWAM_NUM_USED_FENCES                     4
/* Must be kept compact -- no howes */

typedef stwuct dwm_i915_setpawam {
	int pawam;
	int vawue;
} dwm_i915_setpawam_t;

/* A memowy managew fow wegions of shawed memowy:
 */
#define I915_MEM_WEGION_AGP 1

typedef stwuct dwm_i915_mem_awwoc {
	int wegion;
	int awignment;
	int size;
	int __usew *wegion_offset;	/* offset fwom stawt of fb ow agp */
} dwm_i915_mem_awwoc_t;

typedef stwuct dwm_i915_mem_fwee {
	int wegion;
	int wegion_offset;
} dwm_i915_mem_fwee_t;

typedef stwuct dwm_i915_mem_init_heap {
	int wegion;
	int size;
	int stawt;
} dwm_i915_mem_init_heap_t;

/* Awwow memowy managew to be town down and we-initiawized (eg on
 * wotate):
 */
typedef stwuct dwm_i915_mem_destwoy_heap {
	int wegion;
} dwm_i915_mem_destwoy_heap_t;

/* Awwow X sewvew to configuwe which pipes to monitow fow vbwank signaws
 */
#define	DWM_I915_VBWANK_PIPE_A	1
#define	DWM_I915_VBWANK_PIPE_B	2

typedef stwuct dwm_i915_vbwank_pipe {
	int pipe;
} dwm_i915_vbwank_pipe_t;

/* Scheduwe buffew swap at given vewticaw bwank:
 */
typedef stwuct dwm_i915_vbwank_swap {
	dwm_dwawabwe_t dwawabwe;
	enum dwm_vbwank_seq_type seqtype;
	unsigned int sequence;
} dwm_i915_vbwank_swap_t;

typedef stwuct dwm_i915_hws_addw {
	__u64 addw;
} dwm_i915_hws_addw_t;

stwuct dwm_i915_gem_init {
	/**
	 * Beginning offset in the GTT to be managed by the DWM memowy
	 * managew.
	 */
	__u64 gtt_stawt;
	/**
	 * Ending offset in the GTT to be managed by the DWM memowy
	 * managew.
	 */
	__u64 gtt_end;
};

stwuct dwm_i915_gem_cweate {
	/**
	 * Wequested size fow the object.
	 *
	 * The (page-awigned) awwocated size fow the object wiww be wetuwned.
	 */
	__u64 size;
	/**
	 * Wetuwned handwe fow the object.
	 *
	 * Object handwes awe nonzewo.
	 */
	__u32 handwe;
	__u32 pad;
};

stwuct dwm_i915_gem_pwead {
	/** Handwe fow the object being wead. */
	__u32 handwe;
	__u32 pad;
	/** Offset into the object to wead fwom */
	__u64 offset;
	/** Wength of data to wead */
	__u64 size;
	/**
	 * Pointew to wwite the data into.
	 *
	 * This is a fixed-size type fow 32/64 compatibiwity.
	 */
	__u64 data_ptw;
};

stwuct dwm_i915_gem_pwwite {
	/** Handwe fow the object being wwitten to. */
	__u32 handwe;
	__u32 pad;
	/** Offset into the object to wwite to */
	__u64 offset;
	/** Wength of data to wwite */
	__u64 size;
	/**
	 * Pointew to wead the data fwom.
	 *
	 * This is a fixed-size type fow 32/64 compatibiwity.
	 */
	__u64 data_ptw;
};

stwuct dwm_i915_gem_mmap {
	/** Handwe fow the object being mapped. */
	__u32 handwe;
	__u32 pad;
	/** Offset in the object to map. */
	__u64 offset;
	/**
	 * Wength of data to map.
	 *
	 * The vawue wiww be page-awigned.
	 */
	__u64 size;
	/**
	 * Wetuwned pointew the data was mapped at.
	 *
	 * This is a fixed-size type fow 32/64 compatibiwity.
	 */
	__u64 addw_ptw;

	/**
	 * Fwags fow extended behaviouw.
	 *
	 * Added in vewsion 2.
	 */
	__u64 fwags;
#define I915_MMAP_WC 0x1
};

stwuct dwm_i915_gem_mmap_gtt {
	/** Handwe fow the object being mapped. */
	__u32 handwe;
	__u32 pad;
	/**
	 * Fake offset to use fow subsequent mmap caww
	 *
	 * This is a fixed-size type fow 32/64 compatibiwity.
	 */
	__u64 offset;
};

/**
 * stwuct dwm_i915_gem_mmap_offset - Wetwieve an offset so we can mmap this buffew object.
 *
 * This stwuct is passed as awgument to the `DWM_IOCTW_I915_GEM_MMAP_OFFSET` ioctw,
 * and is used to wetwieve the fake offset to mmap an object specified by &handwe.
 *
 * The wegacy way of using `DWM_IOCTW_I915_GEM_MMAP` is wemoved on gen12+.
 * `DWM_IOCTW_I915_GEM_MMAP_GTT` is an owdew suppowted awias to this stwuct, but wiww behave
 * as setting the &extensions to 0, and &fwags to `I915_MMAP_OFFSET_GTT`.
 */
stwuct dwm_i915_gem_mmap_offset {
	/** @handwe: Handwe fow the object being mapped. */
	__u32 handwe;
	/** @pad: Must be zewo */
	__u32 pad;
	/**
	 * @offset: The fake offset to use fow subsequent mmap caww
	 *
	 * This is a fixed-size type fow 32/64 compatibiwity.
	 */
	__u64 offset;

	/**
	 * @fwags: Fwags fow extended behaviouw.
	 *
	 * It is mandatowy that one of the `MMAP_OFFSET` types
	 * shouwd be incwuded:
	 *
	 * - `I915_MMAP_OFFSET_GTT`: Use mmap with the object bound to GTT. (Wwite-Combined)
	 * - `I915_MMAP_OFFSET_WC`: Use Wwite-Combined caching.
	 * - `I915_MMAP_OFFSET_WB`: Use Wwite-Back caching.
	 * - `I915_MMAP_OFFSET_FIXED`: Use object pwacement to detewmine caching.
	 *
	 * On devices with wocaw memowy `I915_MMAP_OFFSET_FIXED` is the onwy vawid
	 * type. On devices without wocaw memowy, this caching mode is invawid.
	 *
	 * As caching mode when specifying `I915_MMAP_OFFSET_FIXED`, WC ow WB wiww
	 * be used, depending on the object pwacement on cweation. WB wiww be used
	 * when the object can onwy exist in system memowy, WC othewwise.
	 */
	__u64 fwags;

#define I915_MMAP_OFFSET_GTT	0
#define I915_MMAP_OFFSET_WC	1
#define I915_MMAP_OFFSET_WB	2
#define I915_MMAP_OFFSET_UC	3
#define I915_MMAP_OFFSET_FIXED	4

	/**
	 * @extensions: Zewo-tewminated chain of extensions.
	 *
	 * No cuwwent extensions defined; mbz.
	 */
	__u64 extensions;
};

/**
 * stwuct dwm_i915_gem_set_domain - Adjust the objects wwite ow wead domain, in
 * pwepawation fow accessing the pages via some CPU domain.
 *
 * Specifying a new wwite ow wead domain wiww fwush the object out of the
 * pwevious domain(if wequiwed), befowe then updating the objects domain
 * twacking with the new domain.
 *
 * Note this might invowve waiting fow the object fiwst if it is stiww active on
 * the GPU.
 *
 * Suppowted vawues fow @wead_domains and @wwite_domain:
 *
 *	- I915_GEM_DOMAIN_WC: Uncached wwite-combined domain
 *	- I915_GEM_DOMAIN_CPU: CPU cache domain
 *	- I915_GEM_DOMAIN_GTT: Mappabwe apewtuwe domain
 *
 * Aww othew domains awe wejected.
 *
 * Note that fow discwete, stawting fwom DG1, this is no wongew suppowted, and
 * is instead wejected. On such pwatfowms the CPU domain is effectivewy static,
 * whewe we awso onwy suppowt a singwe &dwm_i915_gem_mmap_offset cache mode,
 * which can't be set expwicitwy and instead depends on the object pwacements,
 * as pew the bewow.
 *
 * Impwicit caching wuwes, stawting fwom DG1:
 *
 *	- If any of the object pwacements (see &dwm_i915_gem_cweate_ext_memowy_wegions)
 *	  contain I915_MEMOWY_CWASS_DEVICE then the object wiww be awwocated and
 *	  mapped as wwite-combined onwy.
 *
 *	- Evewything ewse is awways awwocated and mapped as wwite-back, with the
 *	  guawantee that evewything is awso cohewent with the GPU.
 *
 * Note that this is wikewy to change in the futuwe again, whewe we might need
 * mowe fwexibiwity on futuwe devices, so making this aww expwicit as pawt of a
 * new &dwm_i915_gem_cweate_ext extension is pwobabwe.
 */
stwuct dwm_i915_gem_set_domain {
	/** @handwe: Handwe fow the object. */
	__u32 handwe;

	/** @wead_domains: New wead domains. */
	__u32 wead_domains;

	/**
	 * @wwite_domain: New wwite domain.
	 *
	 * Note that having something in the wwite domain impwies it's in the
	 * wead domain, and onwy that wead domain.
	 */
	__u32 wwite_domain;
};

stwuct dwm_i915_gem_sw_finish {
	/** Handwe fow the object */
	__u32 handwe;
};

stwuct dwm_i915_gem_wewocation_entwy {
	/**
	 * Handwe of the buffew being pointed to by this wewocation entwy.
	 *
	 * It's appeawing to make this be an index into the mm_vawidate_entwy
	 * wist to wefew to the buffew, but this awwows the dwivew to cweate
	 * a wewocation wist fow state buffews and not we-wwite it pew
	 * exec using the buffew.
	 */
	__u32 tawget_handwe;

	/**
	 * Vawue to be added to the offset of the tawget buffew to make up
	 * the wewocation entwy.
	 */
	__u32 dewta;

	/** Offset in the buffew the wewocation entwy wiww be wwitten into */
	__u64 offset;

	/**
	 * Offset vawue of the tawget buffew that the wewocation entwy was wast
	 * wwitten as.
	 *
	 * If the buffew has the same offset as wast time, we can skip syncing
	 * and wwiting the wewocation.  This vawue is wwitten back out by
	 * the execbuffew ioctw when the wewocation is wwitten.
	 */
	__u64 pwesumed_offset;

	/**
	 * Tawget memowy domains wead by this opewation.
	 */
	__u32 wead_domains;

	/**
	 * Tawget memowy domains wwitten by this opewation.
	 *
	 * Note that onwy one domain may be wwitten by the whowe
	 * execbuffew opewation, so that whewe thewe awe confwicts,
	 * the appwication wiww get -EINVAW back.
	 */
	__u32 wwite_domain;
};

/** @{
 * Intew memowy domains
 *
 * Most of these just awign with the vawious caches in
 * the system and awe used to fwush and invawidate as
 * objects end up cached in diffewent domains.
 */
/** CPU cache */
#define I915_GEM_DOMAIN_CPU		0x00000001
/** Wendew cache, used by 2D and 3D dwawing */
#define I915_GEM_DOMAIN_WENDEW		0x00000002
/** Sampwew cache, used by textuwe engine */
#define I915_GEM_DOMAIN_SAMPWEW		0x00000004
/** Command queue, used to woad batch buffews */
#define I915_GEM_DOMAIN_COMMAND		0x00000008
/** Instwuction cache, used by shadew pwogwams */
#define I915_GEM_DOMAIN_INSTWUCTION	0x00000010
/** Vewtex addwess cache */
#define I915_GEM_DOMAIN_VEWTEX		0x00000020
/** GTT domain - apewtuwe and scanout */
#define I915_GEM_DOMAIN_GTT		0x00000040
/** WC domain - uncached access */
#define I915_GEM_DOMAIN_WC		0x00000080
/** @} */

stwuct dwm_i915_gem_exec_object {
	/**
	 * Usew's handwe fow a buffew to be bound into the GTT fow this
	 * opewation.
	 */
	__u32 handwe;

	/** Numbew of wewocations to be pewfowmed on this buffew */
	__u32 wewocation_count;
	/**
	 * Pointew to awway of stwuct dwm_i915_gem_wewocation_entwy containing
	 * the wewocations to be pewfowmed in this buffew.
	 */
	__u64 wewocs_ptw;

	/** Wequiwed awignment in gwaphics apewtuwe */
	__u64 awignment;

	/**
	 * Wetuwned vawue of the updated offset of the object, fow futuwe
	 * pwesumed_offset wwites.
	 */
	__u64 offset;
};

/* DWM_IOCTW_I915_GEM_EXECBUFFEW was wemoved in Winux 5.13 */
stwuct dwm_i915_gem_execbuffew {
	/**
	 * Wist of buffews to be vawidated with theiw wewocations to be
	 * pewfowmend on them.
	 *
	 * This is a pointew to an awway of stwuct dwm_i915_gem_vawidate_entwy.
	 *
	 * These buffews must be wisted in an owdew such that aww wewocations
	 * a buffew is pewfowming wefew to buffews that have awweady appeawed
	 * in the vawidate wist.
	 */
	__u64 buffews_ptw;
	__u32 buffew_count;

	/** Offset in the batchbuffew to stawt execution fwom. */
	__u32 batch_stawt_offset;
	/** Bytes used in batchbuffew fwom batch_stawt_offset */
	__u32 batch_wen;
	__u32 DW1;
	__u32 DW4;
	__u32 num_cwipwects;
	/** This is a stwuct dwm_cwip_wect *cwipwects */
	__u64 cwipwects_ptw;
};

stwuct dwm_i915_gem_exec_object2 {
	/**
	 * Usew's handwe fow a buffew to be bound into the GTT fow this
	 * opewation.
	 */
	__u32 handwe;

	/** Numbew of wewocations to be pewfowmed on this buffew */
	__u32 wewocation_count;
	/**
	 * Pointew to awway of stwuct dwm_i915_gem_wewocation_entwy containing
	 * the wewocations to be pewfowmed in this buffew.
	 */
	__u64 wewocs_ptw;

	/** Wequiwed awignment in gwaphics apewtuwe */
	__u64 awignment;

	/**
	 * When the EXEC_OBJECT_PINNED fwag is specified this is popuwated by
	 * the usew with the GTT offset at which this object wiww be pinned.
	 *
	 * When the I915_EXEC_NO_WEWOC fwag is specified this must contain the
	 * pwesumed_offset of the object.
	 *
	 * Duwing execbuffew2 the kewnew popuwates it with the vawue of the
	 * cuwwent GTT offset of the object, fow futuwe pwesumed_offset wwites.
	 *
	 * See stwuct dwm_i915_gem_cweate_ext fow the wuwes when deawing with
	 * awignment westwictions with I915_MEMOWY_CWASS_DEVICE, on devices with
	 * minimum page sizes, wike DG2.
	 */
	__u64 offset;

#define EXEC_OBJECT_NEEDS_FENCE		 (1<<0)
#define EXEC_OBJECT_NEEDS_GTT		 (1<<1)
#define EXEC_OBJECT_WWITE		 (1<<2)
#define EXEC_OBJECT_SUPPOWTS_48B_ADDWESS (1<<3)
#define EXEC_OBJECT_PINNED		 (1<<4)
#define EXEC_OBJECT_PAD_TO_SIZE		 (1<<5)
/* The kewnew impwicitwy twacks GPU activity on aww GEM objects, and
 * synchwonises opewations with outstanding wendewing. This incwudes
 * wendewing on othew devices if expowted via dma-buf. Howevew, sometimes
 * this twacking is too coawse and the usew knows bettew. Fow exampwe,
 * if the object is spwit into non-ovewwapping wanges shawed between diffewent
 * cwients ow engines (i.e. subawwocating objects), the impwicit twacking
 * by kewnew assumes that each opewation affects the whowe object wathew
 * than an individuaw wange, causing needwess synchwonisation between cwients.
 * The kewnew wiww awso fowgo any CPU cache fwushes pwiow to wendewing fwom
 * the object as the cwient is expected to be awso handwing such domain
 * twacking.
 *
 * The kewnew maintains the impwicit twacking in owdew to manage wesouwces
 * used by the GPU - this fwag onwy disabwes the synchwonisation pwiow to
 * wendewing with this object in this execbuf.
 *
 * Opting out of impwicit synhwonisation wequiwes the usew to do its own
 * expwicit twacking to avoid wendewing cowwuption. See, fow exampwe,
 * I915_PAWAM_HAS_EXEC_FENCE to owdew execbufs and execute them asynchwonouswy.
 */
#define EXEC_OBJECT_ASYNC		(1<<6)
/* Wequest that the contents of this execobject be copied into the ewwow
 * state upon a GPU hang invowving this batch fow post-mowtem debugging.
 * These buffews awe wecowded in no pawticuwaw owdew as "usew" in
 * /sys/cwass/dwm/cawdN/ewwow. Quewy I915_PAWAM_HAS_EXEC_CAPTUWE to see
 * if the kewnew suppowts this fwag.
 */
#define EXEC_OBJECT_CAPTUWE		(1<<7)
/* Aww wemaining bits awe MBZ and WESEWVED FOW FUTUWE USE */
#define __EXEC_OBJECT_UNKNOWN_FWAGS -(EXEC_OBJECT_CAPTUWE<<1)
	__u64 fwags;

	union {
		__u64 wsvd1;
		__u64 pad_to_size;
	};
	__u64 wsvd2;
};

/**
 * stwuct dwm_i915_gem_exec_fence - An input ow output fence fow the execbuf
 * ioctw.
 *
 * The wequest wiww wait fow input fence to signaw befowe submission.
 *
 * The wetuwned output fence wiww be signawed aftew the compwetion of the
 * wequest.
 */
stwuct dwm_i915_gem_exec_fence {
	/** @handwe: Usew's handwe fow a dwm_syncobj to wait on ow signaw. */
	__u32 handwe;

	/**
	 * @fwags: Suppowted fwags awe:
	 *
	 * I915_EXEC_FENCE_WAIT:
	 * Wait fow the input fence befowe wequest submission.
	 *
	 * I915_EXEC_FENCE_SIGNAW:
	 * Wetuwn wequest compwetion fence as output
	 */
	__u32 fwags;
#define I915_EXEC_FENCE_WAIT            (1<<0)
#define I915_EXEC_FENCE_SIGNAW          (1<<1)
#define __I915_EXEC_FENCE_UNKNOWN_FWAGS (-(I915_EXEC_FENCE_SIGNAW << 1))
};

/**
 * stwuct dwm_i915_gem_execbuffew_ext_timewine_fences - Timewine fences
 * fow execbuf ioctw.
 *
 * This stwuctuwe descwibes an awway of dwm_syncobj and associated points fow
 * timewine vawiants of dwm_syncobj. It is invawid to append this stwuctuwe to
 * the execbuf if I915_EXEC_FENCE_AWWAY is set.
 */
stwuct dwm_i915_gem_execbuffew_ext_timewine_fences {
#define DWM_I915_GEM_EXECBUFFEW_EXT_TIMEWINE_FENCES 0
	/** @base: Extension wink. See stwuct i915_usew_extension. */
	stwuct i915_usew_extension base;

	/**
	 * @fence_count: Numbew of ewements in the @handwes_ptw & @vawue_ptw
	 * awways.
	 */
	__u64 fence_count;

	/**
	 * @handwes_ptw: Pointew to an awway of stwuct dwm_i915_gem_exec_fence
	 * of wength @fence_count.
	 */
	__u64 handwes_ptw;

	/**
	 * @vawues_ptw: Pointew to an awway of u64 vawues of wength
	 * @fence_count.
	 * Vawues must be 0 fow a binawy dwm_syncobj. A Vawue of 0 fow a
	 * timewine dwm_syncobj is invawid as it tuwns a dwm_syncobj into a
	 * binawy one.
	 */
	__u64 vawues_ptw;
};

/**
 * stwuct dwm_i915_gem_execbuffew2 - Stwuctuwe fow DWM_I915_GEM_EXECBUFFEW2
 * ioctw.
 */
stwuct dwm_i915_gem_execbuffew2 {
	/** @buffews_ptw: Pointew to a wist of gem_exec_object2 stwucts */
	__u64 buffews_ptw;

	/** @buffew_count: Numbew of ewements in @buffews_ptw awway */
	__u32 buffew_count;

	/**
	 * @batch_stawt_offset: Offset in the batchbuffew to stawt execution
	 * fwom.
	 */
	__u32 batch_stawt_offset;

	/**
	 * @batch_wen: Wength in bytes of the batch buffew, stawting fwom the
	 * @batch_stawt_offset. If 0, wength is assumed to be the batch buffew
	 * object size.
	 */
	__u32 batch_wen;

	/** @DW1: depwecated */
	__u32 DW1;

	/** @DW4: depwecated */
	__u32 DW4;

	/** @num_cwipwects: See @cwipwects_ptw */
	__u32 num_cwipwects;

	/**
	 * @cwipwects_ptw: Kewnew cwipping was a DWI1 misfeatuwe.
	 *
	 * It is invawid to use this fiewd if I915_EXEC_FENCE_AWWAY ow
	 * I915_EXEC_USE_EXTENSIONS fwags awe not set.
	 *
	 * If I915_EXEC_FENCE_AWWAY is set, then this is a pointew to an awway
	 * of &dwm_i915_gem_exec_fence and @num_cwipwects is the wength of the
	 * awway.
	 *
	 * If I915_EXEC_USE_EXTENSIONS is set, then this is a pointew to a
	 * singwe &i915_usew_extension and num_cwipwects is 0.
	 */
	__u64 cwipwects_ptw;

	/** @fwags: Execbuf fwags */
	__u64 fwags;
#define I915_EXEC_WING_MASK              (0x3f)
#define I915_EXEC_DEFAUWT                (0<<0)
#define I915_EXEC_WENDEW                 (1<<0)
#define I915_EXEC_BSD                    (2<<0)
#define I915_EXEC_BWT                    (3<<0)
#define I915_EXEC_VEBOX                  (4<<0)

/* Used fow switching the constants addwessing mode on gen4+ WENDEW wing.
 * Gen6+ onwy suppowts wewative addwessing to dynamic state (defauwt) and
 * absowute addwessing.
 *
 * These fwags awe ignowed fow the BSD and BWT wings.
 */
#define I915_EXEC_CONSTANTS_MASK 	(3<<6)
#define I915_EXEC_CONSTANTS_WEW_GENEWAW (0<<6) /* defauwt */
#define I915_EXEC_CONSTANTS_ABSOWUTE 	(1<<6)
#define I915_EXEC_CONSTANTS_WEW_SUWFACE (2<<6) /* gen4/5 onwy */

/** Wesets the SO wwite offset wegistews fow twansfowm feedback on gen7. */
#define I915_EXEC_GEN7_SOW_WESET	(1<<8)

/** Wequest a pwiviweged ("secuwe") batch buffew. Note onwy avaiwabwe fow
 * DWM_WOOT_ONWY | DWM_MASTEW pwocesses.
 */
#define I915_EXEC_SECUWE		(1<<9)

/** Infowm the kewnew that the batch is and wiww awways be pinned. This
 * negates the wequiwement fow a wowkawound to be pewfowmed to avoid
 * an incohewent CS (such as can be found on 830/845). If this fwag is
 * not passed, the kewnew wiww endeavouw to make suwe the batch is
 * cohewent with the CS befowe execution. If this fwag is passed,
 * usewspace assumes the wesponsibiwity fow ensuwing the same.
 */
#define I915_EXEC_IS_PINNED		(1<<10)

/** Pwovide a hint to the kewnew that the command stweam and auxiwiawy
 * state buffews awweady howds the cowwect pwesumed addwesses and so the
 * wewocation pwocess may be skipped if no buffews need to be moved in
 * pwepawation fow the execbuffew.
 */
#define I915_EXEC_NO_WEWOC		(1<<11)

/** Use the wewoc.handwe as an index into the exec object awway wathew
 * than as the pew-fiwe handwe.
 */
#define I915_EXEC_HANDWE_WUT		(1<<12)

/** Used fow switching BSD wings on the pwatfowms with two BSD wings */
#define I915_EXEC_BSD_SHIFT	 (13)
#define I915_EXEC_BSD_MASK	 (3 << I915_EXEC_BSD_SHIFT)
/* defauwt ping-pong mode */
#define I915_EXEC_BSD_DEFAUWT	 (0 << I915_EXEC_BSD_SHIFT)
#define I915_EXEC_BSD_WING1	 (1 << I915_EXEC_BSD_SHIFT)
#define I915_EXEC_BSD_WING2	 (2 << I915_EXEC_BSD_SHIFT)

/** Teww the kewnew that the batchbuffew is pwocessed by
 *  the wesouwce stweamew.
 */
#define I915_EXEC_WESOUWCE_STWEAMEW     (1<<15)

/* Setting I915_EXEC_FENCE_IN impwies that wowew_32_bits(wsvd2) wepwesent
 * a sync_fiwe fd to wait upon (in a nonbwocking mannew) pwiow to executing
 * the batch.
 *
 * Wetuwns -EINVAW if the sync_fiwe fd cannot be found.
 */
#define I915_EXEC_FENCE_IN		(1<<16)

/* Setting I915_EXEC_FENCE_OUT causes the ioctw to wetuwn a sync_fiwe fd
 * in the uppew_32_bits(wsvd2) upon success. Ownewship of the fd is given
 * to the cawwew, and it shouwd be cwose() aftew use. (The fd is a weguwaw
 * fiwe descwiptow and wiww be cweaned up on pwocess tewmination. It howds
 * a wefewence to the wequest, but nothing ewse.)
 *
 * The sync_fiwe fd can be combined with othew sync_fiwe and passed eithew
 * to execbuf using I915_EXEC_FENCE_IN, to atomic KMS ioctws (so that a fwip
 * wiww onwy occuw aftew this wequest compwetes), ow to othew devices.
 *
 * Using I915_EXEC_FENCE_OUT wequiwes use of
 * DWM_IOCTW_I915_GEM_EXECBUFFEW2_WW ioctw so that the wesuwt is wwitten
 * back to usewspace. Faiwuwe to do so wiww cause the out-fence to awways
 * be wepowted as zewo, and the weaw fence fd to be weaked.
 */
#define I915_EXEC_FENCE_OUT		(1<<17)

/*
 * Twaditionawwy the execbuf ioctw has onwy considewed the finaw ewement in
 * the execobject[] to be the executabwe batch. Often though, the cwient
 * wiww known the batch object pwiow to constwuction and being abwe to pwace
 * it into the execobject[] awway fiwst can simpwify the wewocation twacking.
 * Setting I915_EXEC_BATCH_FIWST tewws execbuf to use ewement 0 of the
 * execobject[] as the * batch instead (the defauwt is to use the wast
 * ewement).
 */
#define I915_EXEC_BATCH_FIWST		(1<<18)

/* Setting I915_FENCE_AWWAY impwies that num_cwipwects and cwipwects_ptw
 * define an awway of i915_gem_exec_fence stwuctuwes which specify a set of
 * dma fences to wait upon ow signaw.
 */
#define I915_EXEC_FENCE_AWWAY   (1<<19)

/*
 * Setting I915_EXEC_FENCE_SUBMIT impwies that wowew_32_bits(wsvd2) wepwesent
 * a sync_fiwe fd to wait upon (in a nonbwocking mannew) pwiow to executing
 * the batch.
 *
 * Wetuwns -EINVAW if the sync_fiwe fd cannot be found.
 */
#define I915_EXEC_FENCE_SUBMIT		(1 << 20)

/*
 * Setting I915_EXEC_USE_EXTENSIONS impwies that
 * dwm_i915_gem_execbuffew2.cwipwects_ptw is tweated as a pointew to an winked
 * wist of i915_usew_extension. Each i915_usew_extension node is the base of a
 * wawgew stwuctuwe. The wist of suppowted stwuctuwes awe wisted in the
 * dwm_i915_gem_execbuffew_ext enum.
 */
#define I915_EXEC_USE_EXTENSIONS	(1 << 21)
#define __I915_EXEC_UNKNOWN_FWAGS (-(I915_EXEC_USE_EXTENSIONS << 1))

	/** @wsvd1: Context id */
	__u64 wsvd1;

	/**
	 * @wsvd2: in and out sync_fiwe fiwe descwiptows.
	 *
	 * When I915_EXEC_FENCE_IN ow I915_EXEC_FENCE_SUBMIT fwag is set, the
	 * wowew 32 bits of this fiewd wiww have the in sync_fiwe fd (input).
	 *
	 * When I915_EXEC_FENCE_OUT fwag is set, the uppew 32 bits of this
	 * fiewd wiww have the out sync_fiwe fd (output).
	 */
	__u64 wsvd2;
};

#define I915_EXEC_CONTEXT_ID_MASK	(0xffffffff)
#define i915_execbuffew2_set_context_id(eb2, context) \
	(eb2).wsvd1 = context & I915_EXEC_CONTEXT_ID_MASK
#define i915_execbuffew2_get_context_id(eb2) \
	((eb2).wsvd1 & I915_EXEC_CONTEXT_ID_MASK)

stwuct dwm_i915_gem_pin {
	/** Handwe of the buffew to be pinned. */
	__u32 handwe;
	__u32 pad;

	/** awignment wequiwed within the apewtuwe */
	__u64 awignment;

	/** Wetuwned GTT offset of the buffew. */
	__u64 offset;
};

stwuct dwm_i915_gem_unpin {
	/** Handwe of the buffew to be unpinned. */
	__u32 handwe;
	__u32 pad;
};

stwuct dwm_i915_gem_busy {
	/** Handwe of the buffew to check fow busy */
	__u32 handwe;

	/** Wetuwn busy status
	 *
	 * A wetuwn of 0 impwies that the object is idwe (aftew
	 * having fwushed any pending activity), and a non-zewo wetuwn that
	 * the object is stiww in-fwight on the GPU. (The GPU has not yet
	 * signawed compwetion fow aww pending wequests that wefewence the
	 * object.) An object is guawanteed to become idwe eventuawwy (so
	 * wong as no new GPU commands awe executed upon it). Due to the
	 * asynchwonous natuwe of the hawdwawe, an object wepowted
	 * as busy may become idwe befowe the ioctw is compweted.
	 *
	 * Fuwthewmowe, if the object is busy, which engine is busy is onwy
	 * pwovided as a guide and onwy indiwectwy by wepowting its cwass
	 * (thewe may be mowe than one engine in each cwass). Thewe awe wace
	 * conditions which pwevent the wepowt of which engines awe busy fwom
	 * being awways accuwate.  Howevew, the convewse is not twue. If the
	 * object is idwe, the wesuwt of the ioctw, that aww engines awe idwe,
	 * is accuwate.
	 *
	 * The wetuwned dwowd is spwit into two fiewds to indicate both
	 * the engine cwasses on which the object is being wead, and the
	 * engine cwass on which it is cuwwentwy being wwitten (if any).
	 *
	 * The wow wowd (bits 0:15) indicate if the object is being wwitten
	 * to by any engine (thewe can onwy be one, as the GEM impwicit
	 * synchwonisation wuwes fowce wwites to be sewiawised). Onwy the
	 * engine cwass (offset by 1, I915_ENGINE_CWASS_WENDEW is wepowted as
	 * 1 not 0 etc) fow the wast wwite is wepowted.
	 *
	 * The high wowd (bits 16:31) awe a bitmask of which engines cwasses
	 * awe cuwwentwy weading fwom the object. Muwtipwe engines may be
	 * weading fwom the object simuwtaneouswy.
	 *
	 * The vawue of each engine cwass is the same as specified in the
	 * I915_CONTEXT_PAWAM_ENGINES context pawametew and via pewf, i.e.
	 * I915_ENGINE_CWASS_WENDEW, I915_ENGINE_CWASS_COPY, etc.
	 * Some hawdwawe may have pawawwew execution engines, e.g. muwtipwe
	 * media engines, which awe mapped to the same cwass identifiew and so
	 * awe not sepawatewy wepowted fow busyness.
	 *
	 * Caveat emptow:
	 * Onwy the boowean wesuwt of this quewy is wewiabwe; that is whethew
	 * the object is idwe ow busy. The wepowt of which engines awe busy
	 * shouwd be onwy used as a heuwistic.
	 */
	__u32 busy;
};

/**
 * stwuct dwm_i915_gem_caching - Set ow get the caching fow given object
 * handwe.
 *
 * Awwow usewspace to contwow the GTT caching bits fow a given object when the
 * object is watew mapped thwough the ppGTT(ow GGTT on owdew pwatfowms wacking
 * ppGTT suppowt, ow if the object is used fow scanout). Note that this might
 * wequiwe unbinding the object fwom the GTT fiwst, if its cuwwent caching vawue
 * doesn't match.
 *
 * Note that this aww changes on discwete pwatfowms, stawting fwom DG1, the
 * set/get caching is no wongew suppowted, and is now wejected.  Instead the CPU
 * caching attwibutes(WB vs WC) wiww become an immutabwe cweation time pwopewty
 * fow the object, awong with the GTT caching wevew. Fow now we don't expose any
 * new uAPI fow this, instead on DG1 this is aww impwicit, awthough this wawgewy
 * shouwdn't mattew since DG1 is cohewent by defauwt(without any way of
 * contwowwing it).
 *
 * Impwicit caching wuwes, stawting fwom DG1:
 *
 *     - If any of the object pwacements (see &dwm_i915_gem_cweate_ext_memowy_wegions)
 *       contain I915_MEMOWY_CWASS_DEVICE then the object wiww be awwocated and
 *       mapped as wwite-combined onwy.
 *
 *     - Evewything ewse is awways awwocated and mapped as wwite-back, with the
 *       guawantee that evewything is awso cohewent with the GPU.
 *
 * Note that this is wikewy to change in the futuwe again, whewe we might need
 * mowe fwexibiwity on futuwe devices, so making this aww expwicit as pawt of a
 * new &dwm_i915_gem_cweate_ext extension is pwobabwe.
 *
 * Side note: Pawt of the weason fow this is that changing the at-awwocation-time CPU
 * caching attwibutes fow the pages might be wequiwed(and is expensive) if we
 * need to then CPU map the pages watew with diffewent caching attwibutes. This
 * inconsistent caching behaviouw, whiwe suppowted on x86, is not univewsawwy
 * suppowted on othew awchitectuwes. So fow simpwicity we opt fow setting
 * evewything at cweation time, whiwst awso making it immutabwe, on discwete
 * pwatfowms.
 */
stwuct dwm_i915_gem_caching {
	/**
	 * @handwe: Handwe of the buffew to set/get the caching wevew.
	 */
	__u32 handwe;

	/**
	 * @caching: The GTT caching wevew to appwy ow possibwe wetuwn vawue.
	 *
	 * The suppowted @caching vawues:
	 *
	 * I915_CACHING_NONE:
	 *
	 * GPU access is not cohewent with CPU caches.  Defauwt fow machines
	 * without an WWC. This means manuaw fwushing might be needed, if we
	 * want GPU access to be cohewent.
	 *
	 * I915_CACHING_CACHED:
	 *
	 * GPU access is cohewent with CPU caches and fuwthewmowe the data is
	 * cached in wast-wevew caches shawed between CPU cowes and the GPU GT.
	 *
	 * I915_CACHING_DISPWAY:
	 *
	 * Speciaw GPU caching mode which is cohewent with the scanout engines.
	 * Twanspawentwy fawws back to I915_CACHING_NONE on pwatfowms whewe no
	 * speciaw cache mode (wike wwite-thwough ow gfdt fwushing) is
	 * avaiwabwe. The kewnew automaticawwy sets this mode when using a
	 * buffew as a scanout tawget.  Usewspace can manuawwy set this mode to
	 * avoid a costwy staww and cwfwush in the hotpath of dwawing the fiwst
	 * fwame.
	 */
#define I915_CACHING_NONE		0
#define I915_CACHING_CACHED		1
#define I915_CACHING_DISPWAY		2
	__u32 caching;
};

#define I915_TIWING_NONE	0
#define I915_TIWING_X		1
#define I915_TIWING_Y		2
/*
 * Do not add new tiwing types hewe.  The I915_TIWING_* vawues awe fow
 * de-tiwing fence wegistews that no wongew exist on modewn pwatfowms.  Awthough
 * the hawdwawe may suppowt new types of tiwing in genewaw (e.g., Tiwe4), we
 * do not need to add them to the uapi that is specific to now-defunct ioctws.
 */
#define I915_TIWING_WAST	I915_TIWING_Y

#define I915_BIT_6_SWIZZWE_NONE		0
#define I915_BIT_6_SWIZZWE_9		1
#define I915_BIT_6_SWIZZWE_9_10		2
#define I915_BIT_6_SWIZZWE_9_11		3
#define I915_BIT_6_SWIZZWE_9_10_11	4
/* Not seen by usewwand */
#define I915_BIT_6_SWIZZWE_UNKNOWN	5
/* Seen by usewwand. */
#define I915_BIT_6_SWIZZWE_9_17		6
#define I915_BIT_6_SWIZZWE_9_10_17	7

stwuct dwm_i915_gem_set_tiwing {
	/** Handwe of the buffew to have its tiwing state updated */
	__u32 handwe;

	/**
	 * Tiwing mode fow the object (I915_TIWING_NONE, I915_TIWING_X,
	 * I915_TIWING_Y).
	 *
	 * This vawue is to be set on wequest, and wiww be updated by the
	 * kewnew on successfuw wetuwn with the actuaw chosen tiwing wayout.
	 *
	 * The tiwing mode may be demoted to I915_TIWING_NONE when the system
	 * has bit 6 swizzwing that can't be managed cowwectwy by GEM.
	 *
	 * Buffew contents become undefined when changing tiwing_mode.
	 */
	__u32 tiwing_mode;

	/**
	 * Stwide in bytes fow the object when in I915_TIWING_X ow
	 * I915_TIWING_Y.
	 */
	__u32 stwide;

	/**
	 * Wetuwned addwess bit 6 swizzwing wequiwed fow CPU access thwough
	 * mmap mapping.
	 */
	__u32 swizzwe_mode;
};

stwuct dwm_i915_gem_get_tiwing {
	/** Handwe of the buffew to get tiwing state fow. */
	__u32 handwe;

	/**
	 * Cuwwent tiwing mode fow the object (I915_TIWING_NONE, I915_TIWING_X,
	 * I915_TIWING_Y).
	 */
	__u32 tiwing_mode;

	/**
	 * Wetuwned addwess bit 6 swizzwing wequiwed fow CPU access thwough
	 * mmap mapping.
	 */
	__u32 swizzwe_mode;

	/**
	 * Wetuwned addwess bit 6 swizzwing wequiwed fow CPU access thwough
	 * mmap mapping whiwst bound.
	 */
	__u32 phys_swizzwe_mode;
};

stwuct dwm_i915_gem_get_apewtuwe {
	/** Totaw size of the apewtuwe used by i915_gem_execbuffew, in bytes */
	__u64 apew_size;

	/**
	 * Avaiwabwe space in the apewtuwe used by i915_gem_execbuffew, in
	 * bytes
	 */
	__u64 apew_avaiwabwe_size;
};

stwuct dwm_i915_get_pipe_fwom_cwtc_id {
	/** ID of CWTC being wequested **/
	__u32 cwtc_id;

	/** pipe of wequested CWTC **/
	__u32 pipe;
};

#define I915_MADV_WIWWNEED 0
#define I915_MADV_DONTNEED 1
#define __I915_MADV_PUWGED 2 /* intewnaw state */

stwuct dwm_i915_gem_madvise {
	/** Handwe of the buffew to change the backing stowe advice */
	__u32 handwe;

	/* Advice: eithew the buffew wiww be needed again in the neaw futuwe,
	 *         ow won't be and couwd be discawded undew memowy pwessuwe.
	 */
	__u32 madv;

	/** Whethew the backing stowe stiww exists. */
	__u32 wetained;
};

/* fwags */
#define I915_OVEWWAY_TYPE_MASK 		0xff
#define I915_OVEWWAY_YUV_PWANAW 	0x01
#define I915_OVEWWAY_YUV_PACKED 	0x02
#define I915_OVEWWAY_WGB		0x03

#define I915_OVEWWAY_DEPTH_MASK		0xff00
#define I915_OVEWWAY_WGB24		0x1000
#define I915_OVEWWAY_WGB16		0x2000
#define I915_OVEWWAY_WGB15		0x3000
#define I915_OVEWWAY_YUV422		0x0100
#define I915_OVEWWAY_YUV411		0x0200
#define I915_OVEWWAY_YUV420		0x0300
#define I915_OVEWWAY_YUV410		0x0400

#define I915_OVEWWAY_SWAP_MASK		0xff0000
#define I915_OVEWWAY_NO_SWAP		0x000000
#define I915_OVEWWAY_UV_SWAP		0x010000
#define I915_OVEWWAY_Y_SWAP		0x020000
#define I915_OVEWWAY_Y_AND_UV_SWAP	0x030000

#define I915_OVEWWAY_FWAGS_MASK		0xff000000
#define I915_OVEWWAY_ENABWE		0x01000000

stwuct dwm_intew_ovewway_put_image {
	/* vawious fwags and swc fowmat descwiption */
	__u32 fwags;
	/* souwce pictuwe descwiption */
	__u32 bo_handwe;
	/* stwide vawues and offsets awe in bytes, buffew wewative */
	__u16 stwide_Y; /* stwide fow packed fowmats */
	__u16 stwide_UV;
	__u32 offset_Y; /* offset fow packet fowmats */
	__u32 offset_U;
	__u32 offset_V;
	/* in pixews */
	__u16 swc_width;
	__u16 swc_height;
	/* to compensate the scawing factows fow pawtiawwy covewed suwfaces */
	__u16 swc_scan_width;
	__u16 swc_scan_height;
	/* output cwtc descwiption */
	__u32 cwtc_id;
	__u16 dst_x;
	__u16 dst_y;
	__u16 dst_width;
	__u16 dst_height;
};

/* fwags */
#define I915_OVEWWAY_UPDATE_ATTWS	(1<<0)
#define I915_OVEWWAY_UPDATE_GAMMA	(1<<1)
#define I915_OVEWWAY_DISABWE_DEST_COWOWKEY	(1<<2)
stwuct dwm_intew_ovewway_attws {
	__u32 fwags;
	__u32 cowow_key;
	__s32 bwightness;
	__u32 contwast;
	__u32 satuwation;
	__u32 gamma0;
	__u32 gamma1;
	__u32 gamma2;
	__u32 gamma3;
	__u32 gamma4;
	__u32 gamma5;
};

/*
 * Intew spwite handwing
 *
 * Cowow keying wowks with a min/mask/max tupwe.  Both souwce and destination
 * cowow keying is awwowed.
 *
 * Souwce keying:
 * Spwite pixews within the min & max vawues, masked against the cowow channews
 * specified in the mask fiewd, wiww be twanspawent.  Aww othew pixews wiww
 * be dispwayed on top of the pwimawy pwane.  Fow WGB suwfaces, onwy the min
 * and mask fiewds wiww be used; wanged compawes awe not awwowed.
 *
 * Destination keying:
 * Pwimawy pwane pixews that match the min vawue, masked against the cowow
 * channews specified in the mask fiewd, wiww be wepwaced by cowwesponding
 * pixews fwom the spwite pwane.
 *
 * Note that souwce & destination keying awe excwusive; onwy one can be
 * active on a given pwane.
 */

#define I915_SET_COWOWKEY_NONE		(1<<0) /* Depwecated. Instead set
						* fwags==0 to disabwe cowowkeying.
						*/
#define I915_SET_COWOWKEY_DESTINATION	(1<<1)
#define I915_SET_COWOWKEY_SOUWCE	(1<<2)
stwuct dwm_intew_spwite_cowowkey {
	__u32 pwane_id;
	__u32 min_vawue;
	__u32 channew_mask;
	__u32 max_vawue;
	__u32 fwags;
};

stwuct dwm_i915_gem_wait {
	/** Handwe of BO we shaww wait on */
	__u32 bo_handwe;
	__u32 fwags;
	/** Numbew of nanoseconds to wait, Wetuwns time wemaining. */
	__s64 timeout_ns;
};

stwuct dwm_i915_gem_context_cweate {
	__u32 ctx_id; /* output: id of new context*/
	__u32 pad;
};

/**
 * stwuct dwm_i915_gem_context_cweate_ext - Stwuctuwe fow cweating contexts.
 */
stwuct dwm_i915_gem_context_cweate_ext {
	/** @ctx_id: Id of the cweated context (output) */
	__u32 ctx_id;

	/**
	 * @fwags: Suppowted fwags awe:
	 *
	 * I915_CONTEXT_CWEATE_FWAGS_USE_EXTENSIONS:
	 *
	 * Extensions may be appended to this stwuctuwe and dwivew must check
	 * fow those. See @extensions.
	 *
	 * I915_CONTEXT_CWEATE_FWAGS_SINGWE_TIMEWINE
	 *
	 * Cweated context wiww have singwe timewine.
	 */
	__u32 fwags;
#define I915_CONTEXT_CWEATE_FWAGS_USE_EXTENSIONS	(1u << 0)
#define I915_CONTEXT_CWEATE_FWAGS_SINGWE_TIMEWINE	(1u << 1)
#define I915_CONTEXT_CWEATE_FWAGS_UNKNOWN \
	(-(I915_CONTEXT_CWEATE_FWAGS_SINGWE_TIMEWINE << 1))

	/**
	 * @extensions: Zewo-tewminated chain of extensions.
	 *
	 * I915_CONTEXT_CWEATE_EXT_SETPAWAM:
	 * Context pawametew to set ow quewy duwing context cweation.
	 * See stwuct dwm_i915_gem_context_cweate_ext_setpawam.
	 *
	 * I915_CONTEXT_CWEATE_EXT_CWONE:
	 * This extension has been wemoved. On the off chance someone somewhewe
	 * has attempted to use it, nevew we-use this extension numbew.
	 */
	__u64 extensions;
#define I915_CONTEXT_CWEATE_EXT_SETPAWAM 0
#define I915_CONTEXT_CWEATE_EXT_CWONE 1
};

/**
 * stwuct dwm_i915_gem_context_pawam - Context pawametew to set ow quewy.
 */
stwuct dwm_i915_gem_context_pawam {
	/** @ctx_id: Context id */
	__u32 ctx_id;

	/** @size: Size of the pawametew @vawue */
	__u32 size;

	/** @pawam: Pawametew to set ow quewy */
	__u64 pawam;
#define I915_CONTEXT_PAWAM_BAN_PEWIOD	0x1
/* I915_CONTEXT_PAWAM_NO_ZEWOMAP has been wemoved.  On the off chance
 * someone somewhewe has attempted to use it, nevew we-use this context
 * pawam numbew.
 */
#define I915_CONTEXT_PAWAM_NO_ZEWOMAP	0x2
#define I915_CONTEXT_PAWAM_GTT_SIZE	0x3
#define I915_CONTEXT_PAWAM_NO_EWWOW_CAPTUWE	0x4
#define I915_CONTEXT_PAWAM_BANNABWE	0x5
#define I915_CONTEXT_PAWAM_PWIOWITY	0x6
#define   I915_CONTEXT_MAX_USEW_PWIOWITY	1023 /* incwusive */
#define   I915_CONTEXT_DEFAUWT_PWIOWITY		0
#define   I915_CONTEXT_MIN_USEW_PWIOWITY	-1023 /* incwusive */
	/*
	 * When using the fowwowing pawam, vawue shouwd be a pointew to
	 * dwm_i915_gem_context_pawam_sseu.
	 */
#define I915_CONTEXT_PAWAM_SSEU		0x7

/*
 * Not aww cwients may want to attempt automatic wecovew of a context aftew
 * a hang (fow exampwe, some cwients may onwy submit vewy smaww incwementaw
 * batches wewying on known wogicaw state of pwevious batches which wiww nevew
 * wecovew cowwectwy and each attempt wiww hang), and so wouwd pwefew that
 * the context is fowevew banned instead.
 *
 * If set to fawse (0), aftew a weset, subsequent (and in fwight) wendewing
 * fwom this context is discawded, and the cwient wiww need to cweate a new
 * context to use instead.
 *
 * If set to twue (1), the kewnew wiww automaticawwy attempt to wecovew the
 * context by skipping the hanging batch and executing the next batch stawting
 * fwom the defauwt context state (discawding the incompwete wogicaw context
 * state wost due to the weset).
 *
 * On cweation, aww new contexts awe mawked as wecovewabwe.
 */
#define I915_CONTEXT_PAWAM_WECOVEWABWE	0x8

	/*
	 * The id of the associated viwtuaw memowy addwess space (ppGTT) of
	 * this context. Can be wetwieved and passed to anothew context
	 * (on the same fd) fow both to use the same ppGTT and so shawe
	 * addwess wayouts, and avoid wewoading the page tabwes on context
	 * switches between themsewves.
	 *
	 * See DWM_I915_GEM_VM_CWEATE and DWM_I915_GEM_VM_DESTWOY.
	 */
#define I915_CONTEXT_PAWAM_VM		0x9

/*
 * I915_CONTEXT_PAWAM_ENGINES:
 *
 * Bind this context to opewate on this subset of avaiwabwe engines. Hencefowth,
 * the I915_EXEC_WING sewectow fow DWM_IOCTW_I915_GEM_EXECBUFFEW2 opewates as
 * an index into this awway of engines; I915_EXEC_DEFAUWT sewecting engine[0]
 * and upwawds. Swots 0...N awe fiwwed in using the specified (cwass, instance).
 * Use
 *	engine_cwass: I915_ENGINE_CWASS_INVAWID,
 *	engine_instance: I915_ENGINE_CWASS_INVAWID_NONE
 * to specify a gap in the awway that can be fiwwed in watew, e.g. by a
 * viwtuaw engine used fow woad bawancing.
 *
 * Setting the numbew of engines bound to the context to 0, by passing a zewo
 * sized awgument, wiww wevewt back to defauwt settings.
 *
 * See stwuct i915_context_pawam_engines.
 *
 * Extensions:
 *   i915_context_engines_woad_bawance (I915_CONTEXT_ENGINES_EXT_WOAD_BAWANCE)
 *   i915_context_engines_bond (I915_CONTEXT_ENGINES_EXT_BOND)
 *   i915_context_engines_pawawwew_submit (I915_CONTEXT_ENGINES_EXT_PAWAWWEW_SUBMIT)
 */
#define I915_CONTEXT_PAWAM_ENGINES	0xa

/*
 * I915_CONTEXT_PAWAM_PEWSISTENCE:
 *
 * Awwow the context and active wendewing to suwvive the pwocess untiw
 * compwetion. Pewsistence awwows fiwe-and-fowget cwients to queue up a
 * bunch of wowk, hand the output ovew to a dispway sewvew and then quit.
 * If the context is mawked as not pewsistent, upon cwosing (eithew via
 * an expwicit DWM_I915_GEM_CONTEXT_DESTWOY ow impwicitwy fwom fiwe cwosuwe
 * ow pwocess tewmination), the context and any outstanding wequests wiww be
 * cancewwed (and expowted fences fow cancewwed wequests mawked as -EIO).
 *
 * By defauwt, new contexts awwow pewsistence.
 */
#define I915_CONTEXT_PAWAM_PEWSISTENCE	0xb

/* This API has been wemoved.  On the off chance someone somewhewe has
 * attempted to use it, nevew we-use this context pawam numbew.
 */
#define I915_CONTEXT_PAWAM_WINGSIZE	0xc

/*
 * I915_CONTEXT_PAWAM_PWOTECTED_CONTENT:
 *
 * Mawk that the context makes use of pwotected content, which wiww wesuwt
 * in the context being invawidated when the pwotected content session is.
 * Given that the pwotected content session is kiwwed on suspend, the device
 * is kept awake fow the wifetime of a pwotected context, so the usew shouwd
 * make suwe to dispose of them once done.
 * This fwag can onwy be set at context cweation time and, when set to twue,
 * must be pweceded by an expwicit setting of I915_CONTEXT_PAWAM_WECOVEWABWE
 * to fawse. This fwag can't be set to twue in conjunction with setting the
 * I915_CONTEXT_PAWAM_BANNABWE fwag to fawse. Cweation exampwe:
 *
 * .. code-bwock:: C
 *
 *	stwuct dwm_i915_gem_context_cweate_ext_setpawam p_pwotected = {
 *		.base = {
 *			.name = I915_CONTEXT_CWEATE_EXT_SETPAWAM,
 *		},
 *		.pawam = {
 *			.pawam = I915_CONTEXT_PAWAM_PWOTECTED_CONTENT,
 *			.vawue = 1,
 *		}
 *	};
 *	stwuct dwm_i915_gem_context_cweate_ext_setpawam p_nowecovew = {
 *		.base = {
 *			.name = I915_CONTEXT_CWEATE_EXT_SETPAWAM,
 *			.next_extension = to_usew_pointew(&p_pwotected),
 *		},
 *		.pawam = {
 *			.pawam = I915_CONTEXT_PAWAM_WECOVEWABWE,
 *			.vawue = 0,
 *		}
 *	};
 *	stwuct dwm_i915_gem_context_cweate_ext cweate = {
 *		.fwags = I915_CONTEXT_CWEATE_FWAGS_USE_EXTENSIONS,
 *		.extensions = to_usew_pointew(&p_nowecovew);
 *	};
 *
 *	ctx_id = gem_context_cweate_ext(dwm_fd, &cweate);
 *
 * In addition to the nowmaw faiwuwe cases, setting this fwag duwing context
 * cweation can wesuwt in the fowwowing ewwows:
 *
 * -ENODEV: featuwe not avaiwabwe
 * -EPEWM: twying to mawk a wecovewabwe ow not bannabwe context as pwotected
 * -ENXIO: A dependency such as a component dwivew ow fiwmwawe is not yet
 *         woaded so usew space may need to attempt again. Depending on the
 *         device, this ewwow may be wepowted if pwotected context cweation is
 *         attempted vewy eawwy aftew kewnew stawt because the intewnaw timeout
 *         waiting fow such dependencies is not guawanteed to be wawgew than
 *         wequiwed (numbews diffew depending on system and kewnew config):
 *            - ADW/WPW: dependencies may take up to 3 seconds fwom kewnew stawt
 *                       whiwe context cweation intewnaw timeout is 250 miwisecs
 *            - MTW: dependencies may take up to 8 seconds fwom kewnew stawt
 *                   whiwe context cweation intewnaw timeout is 250 miwisecs
 *         NOTE: such dependencies happen once, so a subsequent caww to cweate a
 *         pwotected context aftew a pwiow successfuw caww wiww not expewience
 *         such timeouts and wiww not wetuwn -ENXIO (unwess the dwivew is wewoaded,
 *         ow, depending on the device, wesumes fwom a suspended state).
 * -EIO: The fiwmwawe did not succeed in cweating the pwotected context.
 */
#define I915_CONTEXT_PAWAM_PWOTECTED_CONTENT    0xd
/* Must be kept compact -- no howes and weww documented */

	/** @vawue: Context pawametew vawue to be set ow quewied */
	__u64 vawue;
};

/*
 * Context SSEU pwogwamming
 *
 * It may be necessawy fow eithew functionaw ow pewfowmance weason to configuwe
 * a context to wun with a weduced numbew of SSEU (whewe SSEU stands fow Swice/
 * Sub-swice/EU).
 *
 * This is done by configuwing SSEU configuwation using the bewow
 * @stwuct dwm_i915_gem_context_pawam_sseu fow evewy suppowted engine which
 * usewspace intends to use.
 *
 * Not aww GPUs ow engines suppowt this functionawity in which case an ewwow
 * code -ENODEV wiww be wetuwned.
 *
 * Awso, fwexibiwity of possibwe SSEU configuwation pewmutations vawies between
 * GPU genewations and softwawe imposed wimitations. Wequesting such a
 * combination wiww wetuwn an ewwow code of -EINVAW.
 *
 * NOTE: When pewf/OA is active the context's SSEU configuwation is ignowed in
 * favouw of a singwe gwobaw setting.
 */
stwuct dwm_i915_gem_context_pawam_sseu {
	/*
	 * Engine cwass & instance to be configuwed ow quewied.
	 */
	stwuct i915_engine_cwass_instance engine;

	/*
	 * Unknown fwags must be cweawed to zewo.
	 */
	__u32 fwags;
#define I915_CONTEXT_SSEU_FWAG_ENGINE_INDEX (1u << 0)

	/*
	 * Mask of swices to enabwe fow the context. Vawid vawues awe a subset
	 * of the bitmask vawue wetuwned fow I915_PAWAM_SWICE_MASK.
	 */
	__u64 swice_mask;

	/*
	 * Mask of subswices to enabwe fow the context. Vawid vawues awe a
	 * subset of the bitmask vawue wetuwn by I915_PAWAM_SUBSWICE_MASK.
	 */
	__u64 subswice_mask;

	/*
	 * Minimum/Maximum numbew of EUs to enabwe pew subswice fow the
	 * context. min_eus_pew_subswice must be infewiow ow equaw to
	 * max_eus_pew_subswice.
	 */
	__u16 min_eus_pew_subswice;
	__u16 max_eus_pew_subswice;

	/*
	 * Unused fow now. Must be cweawed to zewo.
	 */
	__u32 wsvd;
};

/**
 * DOC: Viwtuaw Engine uAPI
 *
 * Viwtuaw engine is a concept whewe usewspace is abwe to configuwe a set of
 * physicaw engines, submit a batch buffew, and wet the dwivew execute it on any
 * engine fwom the set as it sees fit.
 *
 * This is pwimawiwy usefuw on pawts which have muwtipwe instances of a same
 * cwass engine, wike fow exampwe GT3+ Skywake pawts with theiw two VCS engines.
 *
 * Fow instance usewspace can enumewate aww engines of a cewtain cwass using the
 * pweviouswy descwibed `Engine Discovewy uAPI`_. Aftew that usewspace can
 * cweate a GEM context with a pwacehowdew swot fow the viwtuaw engine (using
 * `I915_ENGINE_CWASS_INVAWID` and `I915_ENGINE_CWASS_INVAWID_NONE` fow cwass
 * and instance wespectivewy) and finawwy using the
 * `I915_CONTEXT_ENGINES_EXT_WOAD_BAWANCE` extension pwace a viwtuaw engine in
 * the same wesewved swot.
 *
 * Exampwe of cweating a viwtuaw engine and submitting a batch buffew to it:
 *
 * .. code-bwock:: C
 *
 * 	I915_DEFINE_CONTEXT_ENGINES_WOAD_BAWANCE(viwtuaw, 2) = {
 * 		.base.name = I915_CONTEXT_ENGINES_EXT_WOAD_BAWANCE,
 * 		.engine_index = 0, // Pwace this viwtuaw engine into engine map swot 0
 * 		.num_sibwings = 2,
 * 		.engines = { { I915_ENGINE_CWASS_VIDEO, 0 },
 * 			     { I915_ENGINE_CWASS_VIDEO, 1 }, },
 * 	};
 * 	I915_DEFINE_CONTEXT_PAWAM_ENGINES(engines, 1) = {
 * 		.engines = { { I915_ENGINE_CWASS_INVAWID,
 * 			       I915_ENGINE_CWASS_INVAWID_NONE } },
 * 		.extensions = to_usew_pointew(&viwtuaw), // Chains aftew woad_bawance extension
 * 	};
 * 	stwuct dwm_i915_gem_context_cweate_ext_setpawam p_engines = {
 * 		.base = {
 * 			.name = I915_CONTEXT_CWEATE_EXT_SETPAWAM,
 * 		},
 * 		.pawam = {
 * 			.pawam = I915_CONTEXT_PAWAM_ENGINES,
 * 			.vawue = to_usew_pointew(&engines),
 * 			.size = sizeof(engines),
 * 		},
 * 	};
 * 	stwuct dwm_i915_gem_context_cweate_ext cweate = {
 * 		.fwags = I915_CONTEXT_CWEATE_FWAGS_USE_EXTENSIONS,
 * 		.extensions = to_usew_pointew(&p_engines);
 * 	};
 *
 * 	ctx_id = gem_context_cweate_ext(dwm_fd, &cweate);
 *
 * 	// Now we have cweated a GEM context with its engine map containing a
 * 	// singwe viwtuaw engine. Submissions to this swot can go eithew to
 * 	// vcs0 ow vcs1, depending on the woad bawancing awgowithm used inside
 * 	// the dwivew. The woad bawancing is dynamic fwom one batch buffew to
 * 	// anothew and twanspawent to usewspace.
 *
 * 	...
 * 	execbuf.wsvd1 = ctx_id;
 * 	execbuf.fwags = 0; // Submits to index 0 which is the viwtuaw engine
 * 	gem_execbuf(dwm_fd, &execbuf);
 */

/*
 * i915_context_engines_woad_bawance:
 *
 * Enabwe woad bawancing acwoss this set of engines.
 *
 * Into the I915_EXEC_DEFAUWT swot [0], a viwtuaw engine is cweated that when
 * used wiww pwoxy the execbuffew wequest onto one of the set of engines
 * in such a way as to distwibute the woad evenwy acwoss the set.
 *
 * The set of engines must be compatibwe (e.g. the same HW cwass) as they
 * wiww shawe the same wogicaw GPU context and wing.
 *
 * To intewmix wendewing with the viwtuaw engine and diwect wendewing onto
 * the backing engines (bypassing the woad bawancing pwoxy), the context must
 * be defined to use a singwe timewine fow aww engines.
 */
stwuct i915_context_engines_woad_bawance {
	stwuct i915_usew_extension base;

	__u16 engine_index;
	__u16 num_sibwings;
	__u32 fwags; /* aww undefined fwags must be zewo */

	__u64 mbz64; /* wesewved fow futuwe use; must be zewo */

	stwuct i915_engine_cwass_instance engines[];
} __attwibute__((packed));

#define I915_DEFINE_CONTEXT_ENGINES_WOAD_BAWANCE(name__, N__) stwuct { \
	stwuct i915_usew_extension base; \
	__u16 engine_index; \
	__u16 num_sibwings; \
	__u32 fwags; \
	__u64 mbz64; \
	stwuct i915_engine_cwass_instance engines[N__]; \
} __attwibute__((packed)) name__

/*
 * i915_context_engines_bond:
 *
 * Constwucted bonded paiws fow execution within a viwtuaw engine.
 *
 * Aww engines awe equaw, but some awe mowe equaw than othews. Given
 * the distwibution of wesouwces in the HW, it may be pwefewabwe to wun
 * a wequest on a given subset of engines in pawawwew to a wequest on a
 * specific engine. We enabwe this sewection of engines within a viwtuaw
 * engine by specifying bonding paiws, fow any given mastew engine we wiww
 * onwy execute on one of the cowwesponding sibwings within the viwtuaw engine.
 *
 * To execute a wequest in pawawwew on the mastew engine and a sibwing wequiwes
 * coowdination with a I915_EXEC_FENCE_SUBMIT.
 */
stwuct i915_context_engines_bond {
	stwuct i915_usew_extension base;

	stwuct i915_engine_cwass_instance mastew;

	__u16 viwtuaw_index; /* index of viwtuaw engine in ctx->engines[] */
	__u16 num_bonds;

	__u64 fwags; /* aww undefined fwags must be zewo */
	__u64 mbz64[4]; /* wesewved fow futuwe use; must be zewo */

	stwuct i915_engine_cwass_instance engines[];
} __attwibute__((packed));

#define I915_DEFINE_CONTEXT_ENGINES_BOND(name__, N__) stwuct { \
	stwuct i915_usew_extension base; \
	stwuct i915_engine_cwass_instance mastew; \
	__u16 viwtuaw_index; \
	__u16 num_bonds; \
	__u64 fwags; \
	__u64 mbz64[4]; \
	stwuct i915_engine_cwass_instance engines[N__]; \
} __attwibute__((packed)) name__

/**
 * stwuct i915_context_engines_pawawwew_submit - Configuwe engine fow
 * pawawwew submission.
 *
 * Setup a swot in the context engine map to awwow muwtipwe BBs to be submitted
 * in a singwe execbuf IOCTW. Those BBs wiww then be scheduwed to wun on the GPU
 * in pawawwew. Muwtipwe hawdwawe contexts awe cweated intewnawwy in the i915 to
 * wun these BBs. Once a swot is configuwed fow N BBs onwy N BBs can be
 * submitted in each execbuf IOCTW and this is impwicit behaviow e.g. The usew
 * doesn't teww the execbuf IOCTW thewe awe N BBs, the execbuf IOCTW knows how
 * many BBs thewe awe based on the swot's configuwation. The N BBs awe the wast
 * N buffew objects ow fiwst N if I915_EXEC_BATCH_FIWST is set.
 *
 * The defauwt pwacement behaviow is to cweate impwicit bonds between each
 * context if each context maps to mowe than 1 physicaw engine (e.g. context is
 * a viwtuaw engine). Awso we onwy awwow contexts of same engine cwass and these
 * contexts must be in wogicawwy contiguous owdew. Exampwes of the pwacement
 * behaviow awe descwibed bewow. Wastwy, the defauwt is to not awwow BBs to be
 * pweempted mid-batch. Wathew insewt coowdinated pweemption points on aww
 * hawdwawe contexts between each set of BBs. Fwags couwd be added in the futuwe
 * to change both of these defauwt behaviows.
 *
 * Wetuwns -EINVAW if hawdwawe context pwacement configuwation is invawid ow if
 * the pwacement configuwation isn't suppowted on the pwatfowm / submission
 * intewface.
 * Wetuwns -ENODEV if extension isn't suppowted on the pwatfowm / submission
 * intewface.
 *
 * .. code-bwock:: none
 *
 *	Exampwes syntax:
 *	CS[X] = genewic engine of same cwass, wogicaw instance X
 *	INVAWID = I915_ENGINE_CWASS_INVAWID, I915_ENGINE_CWASS_INVAWID_NONE
 *
 *	Exampwe 1 pseudo code:
 *	set_engines(INVAWID)
 *	set_pawawwew(engine_index=0, width=2, num_sibwings=1,
 *		     engines=CS[0],CS[1])
 *
 *	Wesuwts in the fowwowing vawid pwacement:
 *	CS[0], CS[1]
 *
 *	Exampwe 2 pseudo code:
 *	set_engines(INVAWID)
 *	set_pawawwew(engine_index=0, width=2, num_sibwings=2,
 *		     engines=CS[0],CS[2],CS[1],CS[3])
 *
 *	Wesuwts in the fowwowing vawid pwacements:
 *	CS[0], CS[1]
 *	CS[2], CS[3]
 *
 *	This can be thought of as two viwtuaw engines, each containing two
 *	engines theweby making a 2D awway. Howevew, thewe awe bonds tying the
 *	entwies togethew and pwacing westwictions on how they can be scheduwed.
 *	Specificawwy, the scheduwew can choose onwy vewticaw cowumns fwom the 2D
 *	awway. That is, CS[0] is bonded to CS[1] and CS[2] to CS[3]. So if the
 *	scheduwew wants to submit to CS[0], it must awso choose CS[1] and vice
 *	vewsa. Same fow CS[2] wequiwes awso using CS[3].
 *	VE[0] = CS[0], CS[2]
 *	VE[1] = CS[1], CS[3]
 *
 *	Exampwe 3 pseudo code:
 *	set_engines(INVAWID)
 *	set_pawawwew(engine_index=0, width=2, num_sibwings=2,
 *		     engines=CS[0],CS[1],CS[1],CS[3])
 *
 *	Wesuwts in the fowwowing vawid and invawid pwacements:
 *	CS[0], CS[1]
 *	CS[1], CS[3] - Not wogicawwy contiguous, wetuwn -EINVAW
 */
stwuct i915_context_engines_pawawwew_submit {
	/**
	 * @base: base usew extension.
	 */
	stwuct i915_usew_extension base;

	/**
	 * @engine_index: swot fow pawawwew engine
	 */
	__u16 engine_index;

	/**
	 * @width: numbew of contexts pew pawawwew engine ow in othew wowds the
	 * numbew of batches in each submission
	 */
	__u16 width;

	/**
	 * @num_sibwings: numbew of sibwings pew context ow in othew wowds the
	 * numbew of possibwe pwacements fow each submission
	 */
	__u16 num_sibwings;

	/**
	 * @mbz16: wesewved fow futuwe use; must be zewo
	 */
	__u16 mbz16;

	/**
	 * @fwags: aww undefined fwags must be zewo, cuwwentwy not defined fwags
	 */
	__u64 fwags;

	/**
	 * @mbz64: wesewved fow futuwe use; must be zewo
	 */
	__u64 mbz64[3];

	/**
	 * @engines: 2-d awway of engine instances to configuwe pawawwew engine
	 *
	 * wength = width (i) * num_sibwings (j)
	 * index = j + i * num_sibwings
	 */
	stwuct i915_engine_cwass_instance engines[];

} __packed;

#define I915_DEFINE_CONTEXT_ENGINES_PAWAWWEW_SUBMIT(name__, N__) stwuct { \
	stwuct i915_usew_extension base; \
	__u16 engine_index; \
	__u16 width; \
	__u16 num_sibwings; \
	__u16 mbz16; \
	__u64 fwags; \
	__u64 mbz64[3]; \
	stwuct i915_engine_cwass_instance engines[N__]; \
} __attwibute__((packed)) name__

/**
 * DOC: Context Engine Map uAPI
 *
 * Context engine map is a new way of addwessing engines when submitting batch-
 * buffews, wepwacing the existing way of using identifiews wike `I915_EXEC_BWT`
 * inside the fwags fiewd of `stwuct dwm_i915_gem_execbuffew2`.
 *
 * To use it cweated GEM contexts need to be configuwed with a wist of engines
 * the usew is intending to submit to. This is accompwished using the
 * `I915_CONTEXT_PAWAM_ENGINES` pawametew and `stwuct
 * i915_context_pawam_engines`.
 *
 * Fow such contexts the `I915_EXEC_WING_MASK` fiewd becomes an index into the
 * configuwed map.
 *
 * Exampwe of cweating such context and submitting against it:
 *
 * .. code-bwock:: C
 *
 * 	I915_DEFINE_CONTEXT_PAWAM_ENGINES(engines, 2) = {
 * 		.engines = { { I915_ENGINE_CWASS_WENDEW, 0 },
 * 			     { I915_ENGINE_CWASS_COPY, 0 } }
 * 	};
 * 	stwuct dwm_i915_gem_context_cweate_ext_setpawam p_engines = {
 * 		.base = {
 * 			.name = I915_CONTEXT_CWEATE_EXT_SETPAWAM,
 * 		},
 * 		.pawam = {
 * 			.pawam = I915_CONTEXT_PAWAM_ENGINES,
 * 			.vawue = to_usew_pointew(&engines),
 * 			.size = sizeof(engines),
 * 		},
 * 	};
 * 	stwuct dwm_i915_gem_context_cweate_ext cweate = {
 * 		.fwags = I915_CONTEXT_CWEATE_FWAGS_USE_EXTENSIONS,
 * 		.extensions = to_usew_pointew(&p_engines);
 * 	};
 *
 * 	ctx_id = gem_context_cweate_ext(dwm_fd, &cweate);
 *
 * 	// We have now cweated a GEM context with two engines in the map:
 * 	// Index 0 points to wcs0 whiwe index 1 points to bcs0. Othew engines
 * 	// wiww not be accessibwe fwom this context.
 *
 * 	...
 * 	execbuf.wsvd1 = ctx_id;
 * 	execbuf.fwags = 0; // Submits to index 0, which is wcs0 fow this context
 * 	gem_execbuf(dwm_fd, &execbuf);
 *
 * 	...
 * 	execbuf.wsvd1 = ctx_id;
 * 	execbuf.fwags = 1; // Submits to index 0, which is bcs0 fow this context
 * 	gem_execbuf(dwm_fd, &execbuf);
 */

stwuct i915_context_pawam_engines {
	__u64 extensions; /* winked chain of extension bwocks, 0 tewminates */
#define I915_CONTEXT_ENGINES_EXT_WOAD_BAWANCE 0 /* see i915_context_engines_woad_bawance */
#define I915_CONTEXT_ENGINES_EXT_BOND 1 /* see i915_context_engines_bond */
#define I915_CONTEXT_ENGINES_EXT_PAWAWWEW_SUBMIT 2 /* see i915_context_engines_pawawwew_submit */
	stwuct i915_engine_cwass_instance engines[];
} __attwibute__((packed));

#define I915_DEFINE_CONTEXT_PAWAM_ENGINES(name__, N__) stwuct { \
	__u64 extensions; \
	stwuct i915_engine_cwass_instance engines[N__]; \
} __attwibute__((packed)) name__

/**
 * stwuct dwm_i915_gem_context_cweate_ext_setpawam - Context pawametew
 * to set ow quewy duwing context cweation.
 */
stwuct dwm_i915_gem_context_cweate_ext_setpawam {
	/** @base: Extension wink. See stwuct i915_usew_extension. */
	stwuct i915_usew_extension base;

	/**
	 * @pawam: Context pawametew to set ow quewy.
	 * See stwuct dwm_i915_gem_context_pawam.
	 */
	stwuct dwm_i915_gem_context_pawam pawam;
};

stwuct dwm_i915_gem_context_destwoy {
	__u32 ctx_id;
	__u32 pad;
};

/**
 * stwuct dwm_i915_gem_vm_contwow - Stwuctuwe to cweate ow destwoy VM.
 *
 * DWM_I915_GEM_VM_CWEATE -
 *
 * Cweate a new viwtuaw memowy addwess space (ppGTT) fow use within a context
 * on the same fiwe. Extensions can be pwovided to configuwe exactwy how the
 * addwess space is setup upon cweation.
 *
 * The id of new VM (bound to the fd) fow use with I915_CONTEXT_PAWAM_VM is
 * wetuwned in the outpawam @id.
 *
 * An extension chain maybe pwovided, stawting with @extensions, and tewminated
 * by the @next_extension being 0. Cuwwentwy, no extensions awe defined.
 *
 * DWM_I915_GEM_VM_DESTWOY -
 *
 * Destwoys a pweviouswy cweated VM id, specified in @vm_id.
 *
 * No extensions ow fwags awe awwowed cuwwentwy, and so must be zewo.
 */
stwuct dwm_i915_gem_vm_contwow {
	/** @extensions: Zewo-tewminated chain of extensions. */
	__u64 extensions;

	/** @fwags: wesewved fow futuwe usage, cuwwentwy MBZ */
	__u32 fwags;

	/** @vm_id: Id of the VM cweated ow to be destwoyed */
	__u32 vm_id;
};

stwuct dwm_i915_weg_wead {
	/*
	 * Wegistew offset.
	 * Fow 64bit wide wegistews whewe the uppew 32bits don't immediatewy
	 * fowwow the wowew 32bits, the offset of the wowew 32bits must
	 * be specified
	 */
	__u64 offset;
#define I915_WEG_WEAD_8B_WA (1uw << 0)

	__u64 vaw; /* Wetuwn vawue */
};

/* Known wegistews:
 *
 * Wendew engine timestamp - 0x2358 + 64bit - gen7+
 * - Note this wegistew wetuwns an invawid vawue if using the defauwt
 *   singwe instwuction 8byte wead, in owdew to wowkawound that pass
 *   fwag I915_WEG_WEAD_8B_WA in offset fiewd.
 *
 */

stwuct dwm_i915_weset_stats {
	__u32 ctx_id;
	__u32 fwags;

	/* Aww wesets since boot/moduwe wewoad, fow aww contexts */
	__u32 weset_count;

	/* Numbew of batches wost when active in GPU, fow this context */
	__u32 batch_active;

	/* Numbew of batches wost pending fow execution, fow this context */
	__u32 batch_pending;

	__u32 pad;
};

/**
 * stwuct dwm_i915_gem_usewptw - Cweate GEM object fwom usew awwocated memowy.
 *
 * Usewptw objects have sevewaw westwictions on what ioctws can be used with the
 * object handwe.
 */
stwuct dwm_i915_gem_usewptw {
	/**
	 * @usew_ptw: The pointew to the awwocated memowy.
	 *
	 * Needs to be awigned to PAGE_SIZE.
	 */
	__u64 usew_ptw;

	/**
	 * @usew_size:
	 *
	 * The size in bytes fow the awwocated memowy. This wiww awso become the
	 * object size.
	 *
	 * Needs to be awigned to PAGE_SIZE, and shouwd be at weast PAGE_SIZE,
	 * ow wawgew.
	 */
	__u64 usew_size;

	/**
	 * @fwags:
	 *
	 * Suppowted fwags:
	 *
	 * I915_USEWPTW_WEAD_ONWY:
	 *
	 * Mawk the object as weadonwy, this awso means GPU access can onwy be
	 * weadonwy. This is onwy suppowted on HW which suppowts weadonwy access
	 * thwough the GTT. If the HW can't suppowt weadonwy access, an ewwow is
	 * wetuwned.
	 *
	 * I915_USEWPTW_PWOBE:
	 *
	 * Pwobe the pwovided @usew_ptw wange and vawidate that the @usew_ptw is
	 * indeed pointing to nowmaw memowy and that the wange is awso vawid.
	 * Fow exampwe if some gawbage addwess is given to the kewnew, then this
	 * shouwd compwain.
	 *
	 * Wetuwns -EFAUWT if the pwobe faiwed.
	 *
	 * Note that this doesn't popuwate the backing pages, and awso doesn't
	 * guawantee that the object wiww wemain vawid when the object is
	 * eventuawwy used.
	 *
	 * The kewnew suppowts this featuwe if I915_PAWAM_HAS_USEWPTW_PWOBE
	 * wetuwns a non-zewo vawue.
	 *
	 * I915_USEWPTW_UNSYNCHWONIZED:
	 *
	 * NOT USED. Setting this fwag wiww wesuwt in an ewwow.
	 */
	__u32 fwags;
#define I915_USEWPTW_WEAD_ONWY 0x1
#define I915_USEWPTW_PWOBE 0x2
#define I915_USEWPTW_UNSYNCHWONIZED 0x80000000
	/**
	 * @handwe: Wetuwned handwe fow the object.
	 *
	 * Object handwes awe nonzewo.
	 */
	__u32 handwe;
};

enum dwm_i915_oa_fowmat {
	I915_OA_FOWMAT_A13 = 1,	    /* HSW onwy */
	I915_OA_FOWMAT_A29,	    /* HSW onwy */
	I915_OA_FOWMAT_A13_B8_C8,   /* HSW onwy */
	I915_OA_FOWMAT_B4_C8,	    /* HSW onwy */
	I915_OA_FOWMAT_A45_B8_C8,   /* HSW onwy */
	I915_OA_FOWMAT_B4_C8_A16,   /* HSW onwy */
	I915_OA_FOWMAT_C4_B8,	    /* HSW+ */

	/* Gen8+ */
	I915_OA_FOWMAT_A12,
	I915_OA_FOWMAT_A12_B8_C8,
	I915_OA_FOWMAT_A32u40_A4u32_B8_C8,

	/* DG2 */
	I915_OAW_FOWMAT_A32u40_A4u32_B8_C8,
	I915_OA_FOWMAT_A24u40_A14u32_B8_C8,

	/* MTW OAM */
	I915_OAM_FOWMAT_MPEC8u64_B8_C8,
	I915_OAM_FOWMAT_MPEC8u32_B8_C8,

	I915_OA_FOWMAT_MAX	    /* non-ABI */
};

enum dwm_i915_pewf_pwopewty_id {
	/**
	 * Open the stweam fow a specific context handwe (as used with
	 * execbuffew2). A stweam opened fow a specific context this way
	 * won't typicawwy wequiwe woot pwiviweges.
	 *
	 * This pwopewty is avaiwabwe in pewf wevision 1.
	 */
	DWM_I915_PEWF_PWOP_CTX_HANDWE = 1,

	/**
	 * A vawue of 1 wequests the incwusion of waw OA unit wepowts as
	 * pawt of stweam sampwes.
	 *
	 * This pwopewty is avaiwabwe in pewf wevision 1.
	 */
	DWM_I915_PEWF_PWOP_SAMPWE_OA,

	/**
	 * The vawue specifies which set of OA unit metwics shouwd be
	 * configuwed, defining the contents of any OA unit wepowts.
	 *
	 * This pwopewty is avaiwabwe in pewf wevision 1.
	 */
	DWM_I915_PEWF_PWOP_OA_METWICS_SET,

	/**
	 * The vawue specifies the size and wayout of OA unit wepowts.
	 *
	 * This pwopewty is avaiwabwe in pewf wevision 1.
	 */
	DWM_I915_PEWF_PWOP_OA_FOWMAT,

	/**
	 * Specifying this pwopewty impwicitwy wequests pewiodic OA unit
	 * sampwing and (at weast on Hasweww) the sampwing fwequency is dewived
	 * fwom this exponent as fowwows:
	 *
	 *   80ns * 2^(pewiod_exponent + 1)
	 *
	 * This pwopewty is avaiwabwe in pewf wevision 1.
	 */
	DWM_I915_PEWF_PWOP_OA_EXPONENT,

	/**
	 * Specifying this pwopewty is onwy vawid when specify a context to
	 * fiwtew with DWM_I915_PEWF_PWOP_CTX_HANDWE. Specifying this pwopewty
	 * wiww howd pweemption of the pawticuwaw context we want to gathew
	 * pewfowmance data about. The execbuf2 submissions must incwude a
	 * dwm_i915_gem_execbuffew_ext_pewf pawametew fow this to appwy.
	 *
	 * This pwopewty is avaiwabwe in pewf wevision 3.
	 */
	DWM_I915_PEWF_PWOP_HOWD_PWEEMPTION,

	/**
	 * Specifying this pins aww contexts to the specified SSEU powew
	 * configuwation fow the duwation of the wecowding.
	 *
	 * This pawametew's vawue is a pointew to a stwuct
	 * dwm_i915_gem_context_pawam_sseu.
	 *
	 * This pwopewty is avaiwabwe in pewf wevision 4.
	 */
	DWM_I915_PEWF_PWOP_GWOBAW_SSEU,

	/**
	 * This optionaw pawametew specifies the timew intewvaw in nanoseconds
	 * at which the i915 dwivew wiww check the OA buffew fow avaiwabwe data.
	 * Minimum awwowed vawue is 100 micwoseconds. A defauwt vawue is used by
	 * the dwivew if this pawametew is not specified. Note that wawgew timew
	 * vawues wiww weduce cpu consumption duwing OA pewf captuwes. Howevew,
	 * excessivewy wawge vawues wouwd potentiawwy wesuwt in OA buffew
	 * ovewwwites as captuwes weach end of the OA buffew.
	 *
	 * This pwopewty is avaiwabwe in pewf wevision 5.
	 */
	DWM_I915_PEWF_PWOP_POWW_OA_PEWIOD,

	/**
	 * Muwtipwe engines may be mapped to the same OA unit. The OA unit is
	 * identified by cwass:instance of any engine mapped to it.
	 *
	 * This pawametew specifies the engine cwass and must be passed awong
	 * with DWM_I915_PEWF_PWOP_OA_ENGINE_INSTANCE.
	 *
	 * This pwopewty is avaiwabwe in pewf wevision 6.
	 */
	DWM_I915_PEWF_PWOP_OA_ENGINE_CWASS,

	/**
	 * This pawametew specifies the engine instance and must be passed awong
	 * with DWM_I915_PEWF_PWOP_OA_ENGINE_CWASS.
	 *
	 * This pwopewty is avaiwabwe in pewf wevision 6.
	 */
	DWM_I915_PEWF_PWOP_OA_ENGINE_INSTANCE,

	DWM_I915_PEWF_PWOP_MAX /* non-ABI */
};

stwuct dwm_i915_pewf_open_pawam {
	__u32 fwags;
#define I915_PEWF_FWAG_FD_CWOEXEC	(1<<0)
#define I915_PEWF_FWAG_FD_NONBWOCK	(1<<1)
#define I915_PEWF_FWAG_DISABWED		(1<<2)

	/** The numbew of u64 (id, vawue) paiws */
	__u32 num_pwopewties;

	/**
	 * Pointew to awway of u64 (id, vawue) paiws configuwing the stweam
	 * to open.
	 */
	__u64 pwopewties_ptw;
};

/*
 * Enabwe data captuwe fow a stweam that was eithew opened in a disabwed state
 * via I915_PEWF_FWAG_DISABWED ow was watew disabwed via
 * I915_PEWF_IOCTW_DISABWE.
 *
 * It is intended to be cheapew to disabwe and enabwe a stweam than it may be
 * to cwose and we-open a stweam with the same configuwation.
 *
 * It's undefined whethew any pending data fow the stweam wiww be wost.
 *
 * This ioctw is avaiwabwe in pewf wevision 1.
 */
#define I915_PEWF_IOCTW_ENABWE	_IO('i', 0x0)

/*
 * Disabwe data captuwe fow a stweam.
 *
 * It is an ewwow to twy and wead a stweam that is disabwed.
 *
 * This ioctw is avaiwabwe in pewf wevision 1.
 */
#define I915_PEWF_IOCTW_DISABWE	_IO('i', 0x1)

/*
 * Change metwics_set captuwed by a stweam.
 *
 * If the stweam is bound to a specific context, the configuwation change
 * wiww pewfowmed inwine with that context such that it takes effect befowe
 * the next execbuf submission.
 *
 * Wetuwns the pweviouswy bound metwics set id, ow a negative ewwow code.
 *
 * This ioctw is avaiwabwe in pewf wevision 2.
 */
#define I915_PEWF_IOCTW_CONFIG	_IO('i', 0x2)

/*
 * Common to aww i915 pewf wecowds
 */
stwuct dwm_i915_pewf_wecowd_headew {
	__u32 type;
	__u16 pad;
	__u16 size;
};

enum dwm_i915_pewf_wecowd_type {

	/**
	 * Sampwes awe the wowk howse wecowd type whose contents awe extensibwe
	 * and defined when opening an i915 pewf stweam based on the given
	 * pwopewties.
	 *
	 * Boowean pwopewties fowwowing the naming convention
	 * DWM_I915_PEWF_SAMPWE_xyz_PWOP wequest the incwusion of 'xyz' data in
	 * evewy sampwe.
	 *
	 * The owdew of these sampwe pwopewties given by usewspace has no
	 * affect on the owdewing of data within a sampwe. The owdew is
	 * documented hewe.
	 *
	 * stwuct {
	 *     stwuct dwm_i915_pewf_wecowd_headew headew;
	 *
	 *     { u32 oa_wepowt[]; } && DWM_I915_PEWF_PWOP_SAMPWE_OA
	 * };
	 */
	DWM_I915_PEWF_WECOWD_SAMPWE = 1,

	/*
	 * Indicates that one ow mowe OA wepowts wewe not wwitten by the
	 * hawdwawe. This can happen fow exampwe if an MI_WEPOWT_PEWF_COUNT
	 * command cowwides with pewiodic sampwing - which wouwd be mowe wikewy
	 * at highew sampwing fwequencies.
	 */
	DWM_I915_PEWF_WECOWD_OA_WEPOWT_WOST = 2,

	/**
	 * An ewwow occuwwed that wesuwted in aww pending OA wepowts being wost.
	 */
	DWM_I915_PEWF_WECOWD_OA_BUFFEW_WOST = 3,

	DWM_I915_PEWF_WECOWD_MAX /* non-ABI */
};

/**
 * stwuct dwm_i915_pewf_oa_config
 *
 * Stwuctuwe to upwoad pewf dynamic configuwation into the kewnew.
 */
stwuct dwm_i915_pewf_oa_config {
	/**
	 * @uuid:
	 *
	 * Stwing fowmatted wike "%\08x-%\04x-%\04x-%\04x-%\012x"
	 */
	chaw uuid[36];

	/**
	 * @n_mux_wegs:
	 *
	 * Numbew of mux wegs in &mux_wegs_ptw.
	 */
	__u32 n_mux_wegs;

	/**
	 * @n_boowean_wegs:
	 *
	 * Numbew of boowean wegs in &boowean_wegs_ptw.
	 */
	__u32 n_boowean_wegs;

	/**
	 * @n_fwex_wegs:
	 *
	 * Numbew of fwex wegs in &fwex_wegs_ptw.
	 */
	__u32 n_fwex_wegs;

	/**
	 * @mux_wegs_ptw:
	 *
	 * Pointew to tupwes of u32 vawues (wegistew addwess, vawue) fow mux
	 * wegistews.  Expected wength of buffew is (2 * sizeof(u32) *
	 * &n_mux_wegs).
	 */
	__u64 mux_wegs_ptw;

	/**
	 * @boowean_wegs_ptw:
	 *
	 * Pointew to tupwes of u32 vawues (wegistew addwess, vawue) fow mux
	 * wegistews.  Expected wength of buffew is (2 * sizeof(u32) *
	 * &n_boowean_wegs).
	 */
	__u64 boowean_wegs_ptw;

	/**
	 * @fwex_wegs_ptw:
	 *
	 * Pointew to tupwes of u32 vawues (wegistew addwess, vawue) fow mux
	 * wegistews.  Expected wength of buffew is (2 * sizeof(u32) *
	 * &n_fwex_wegs).
	 */
	__u64 fwex_wegs_ptw;
};

/**
 * stwuct dwm_i915_quewy_item - An individuaw quewy fow the kewnew to pwocess.
 *
 * The behaviouw is detewmined by the @quewy_id. Note that exactwy what
 * @data_ptw is awso depends on the specific @quewy_id.
 */
stwuct dwm_i915_quewy_item {
	/**
	 * @quewy_id:
	 *
	 * The id fow this quewy.  Cuwwentwy accepted quewy IDs awe:
	 *  - %DWM_I915_QUEWY_TOPOWOGY_INFO (see stwuct dwm_i915_quewy_topowogy_info)
	 *  - %DWM_I915_QUEWY_ENGINE_INFO (see stwuct dwm_i915_engine_info)
	 *  - %DWM_I915_QUEWY_PEWF_CONFIG (see stwuct dwm_i915_quewy_pewf_config)
	 *  - %DWM_I915_QUEWY_MEMOWY_WEGIONS (see stwuct dwm_i915_quewy_memowy_wegions)
	 *  - %DWM_I915_QUEWY_HWCONFIG_BWOB (see `GuC HWCONFIG bwob uAPI`)
	 *  - %DWM_I915_QUEWY_GEOMETWY_SUBSWICES (see stwuct dwm_i915_quewy_topowogy_info)
	 */
	__u64 quewy_id;
#define DWM_I915_QUEWY_TOPOWOGY_INFO		1
#define DWM_I915_QUEWY_ENGINE_INFO		2
#define DWM_I915_QUEWY_PEWF_CONFIG		3
#define DWM_I915_QUEWY_MEMOWY_WEGIONS		4
#define DWM_I915_QUEWY_HWCONFIG_BWOB		5
#define DWM_I915_QUEWY_GEOMETWY_SUBSWICES	6
/* Must be kept compact -- no howes and weww documented */

	/**
	 * @wength:
	 *
	 * When set to zewo by usewspace, this is fiwwed with the size of the
	 * data to be wwitten at the @data_ptw pointew. The kewnew sets this
	 * vawue to a negative vawue to signaw an ewwow on a pawticuwaw quewy
	 * item.
	 */
	__s32 wength;

	/**
	 * @fwags:
	 *
	 * When &quewy_id == %DWM_I915_QUEWY_TOPOWOGY_INFO, must be 0.
	 *
	 * When &quewy_id == %DWM_I915_QUEWY_PEWF_CONFIG, must be one of the
	 * fowwowing:
	 *
	 *	- %DWM_I915_QUEWY_PEWF_CONFIG_WIST
	 *      - %DWM_I915_QUEWY_PEWF_CONFIG_DATA_FOW_UUID
	 *      - %DWM_I915_QUEWY_PEWF_CONFIG_FOW_UUID
	 *
	 * When &quewy_id == %DWM_I915_QUEWY_GEOMETWY_SUBSWICES must contain
	 * a stwuct i915_engine_cwass_instance that wefewences a wendew engine.
	 */
	__u32 fwags;
#define DWM_I915_QUEWY_PEWF_CONFIG_WIST          1
#define DWM_I915_QUEWY_PEWF_CONFIG_DATA_FOW_UUID 2
#define DWM_I915_QUEWY_PEWF_CONFIG_DATA_FOW_ID   3

	/**
	 * @data_ptw:
	 *
	 * Data wiww be wwitten at the wocation pointed by @data_ptw when the
	 * vawue of @wength matches the wength of the data to be wwitten by the
	 * kewnew.
	 */
	__u64 data_ptw;
};

/**
 * stwuct dwm_i915_quewy - Suppwy an awway of stwuct dwm_i915_quewy_item fow the
 * kewnew to fiww out.
 *
 * Note that this is genewawwy a two step pwocess fow each stwuct
 * dwm_i915_quewy_item in the awway:
 *
 * 1. Caww the DWM_IOCTW_I915_QUEWY, giving it ouw awway of stwuct
 *    dwm_i915_quewy_item, with &dwm_i915_quewy_item.wength set to zewo. The
 *    kewnew wiww then fiww in the size, in bytes, which tewws usewspace how
 *    memowy it needs to awwocate fow the bwob(say fow an awway of pwopewties).
 *
 * 2. Next we caww DWM_IOCTW_I915_QUEWY again, this time with the
 *    &dwm_i915_quewy_item.data_ptw equaw to ouw newwy awwocated bwob. Note that
 *    the &dwm_i915_quewy_item.wength shouwd stiww be the same as what the
 *    kewnew pweviouswy set. At this point the kewnew can fiww in the bwob.
 *
 * Note that fow some quewy items it can make sense fow usewspace to just pass
 * in a buffew/bwob equaw to ow wawgew than the wequiwed size. In this case onwy
 * a singwe ioctw caww is needed. Fow some smawwew quewy items this can wowk
 * quite weww.
 *
 */
stwuct dwm_i915_quewy {
	/** @num_items: The numbew of ewements in the @items_ptw awway */
	__u32 num_items;

	/**
	 * @fwags: Unused fow now. Must be cweawed to zewo.
	 */
	__u32 fwags;

	/**
	 * @items_ptw:
	 *
	 * Pointew to an awway of stwuct dwm_i915_quewy_item. The numbew of
	 * awway ewements is @num_items.
	 */
	__u64 items_ptw;
};

/**
 * stwuct dwm_i915_quewy_topowogy_info
 *
 * Descwibes swice/subswice/EU infowmation quewied by
 * %DWM_I915_QUEWY_TOPOWOGY_INFO
 */
stwuct dwm_i915_quewy_topowogy_info {
	/**
	 * @fwags:
	 *
	 * Unused fow now. Must be cweawed to zewo.
	 */
	__u16 fwags;

	/**
	 * @max_swices:
	 *
	 * The numbew of bits used to expwess the swice mask.
	 */
	__u16 max_swices;

	/**
	 * @max_subswices:
	 *
	 * The numbew of bits used to expwess the subswice mask.
	 */
	__u16 max_subswices;

	/**
	 * @max_eus_pew_subswice:
	 *
	 * The numbew of bits in the EU mask that cowwespond to a singwe
	 * subswice's EUs.
	 */
	__u16 max_eus_pew_subswice;

	/**
	 * @subswice_offset:
	 *
	 * Offset in data[] at which the subswice masks awe stowed.
	 */
	__u16 subswice_offset;

	/**
	 * @subswice_stwide:
	 *
	 * Stwide at which each of the subswice masks fow each swice awe
	 * stowed.
	 */
	__u16 subswice_stwide;

	/**
	 * @eu_offset:
	 *
	 * Offset in data[] at which the EU masks awe stowed.
	 */
	__u16 eu_offset;

	/**
	 * @eu_stwide:
	 *
	 * Stwide at which each of the EU masks fow each subswice awe stowed.
	 */
	__u16 eu_stwide;

	/**
	 * @data:
	 *
	 * Contains 3 pieces of infowmation :
	 *
	 * - The swice mask with one bit pew swice tewwing whethew a swice is
	 *   avaiwabwe. The avaiwabiwity of swice X can be quewied with the
	 *   fowwowing fowmuwa :
	 *
	 *   .. code:: c
	 *
	 *      (data[X / 8] >> (X % 8)) & 1
	 *
	 *   Stawting with Xe_HP pwatfowms, Intew hawdwawe no wongew has
	 *   twaditionaw swices so i915 wiww awways wepowt a singwe swice
	 *   (hawdcoded swicemask = 0x1) which contains aww of the pwatfowm's
	 *   subswices.  I.e., the mask hewe does not wefwect any of the newew
	 *   hawdwawe concepts such as "gswices" ow "cswices" since usewspace
	 *   is capabwe of infewwing those fwom the subswice mask.
	 *
	 * - The subswice mask fow each swice with one bit pew subswice tewwing
	 *   whethew a subswice is avaiwabwe.  Stawting with Gen12 we use the
	 *   tewm "subswice" to wefew to what the hawdwawe documentation
	 *   descwibes as a "duaw-subswices."  The avaiwabiwity of subswice Y
	 *   in swice X can be quewied with the fowwowing fowmuwa :
	 *
	 *   .. code:: c
	 *
	 *      (data[subswice_offset + X * subswice_stwide + Y / 8] >> (Y % 8)) & 1
	 *
	 * - The EU mask fow each subswice in each swice, with one bit pew EU
	 *   tewwing whethew an EU is avaiwabwe. The avaiwabiwity of EU Z in
	 *   subswice Y in swice X can be quewied with the fowwowing fowmuwa :
	 *
	 *   .. code:: c
	 *
	 *      (data[eu_offset +
	 *            (X * max_subswices + Y) * eu_stwide +
	 *            Z / 8
	 *       ] >> (Z % 8)) & 1
	 */
	__u8 data[];
};

/**
 * DOC: Engine Discovewy uAPI
 *
 * Engine discovewy uAPI is a way of enumewating physicaw engines pwesent in a
 * GPU associated with an open i915 DWM fiwe descwiptow. This supewsedes the owd
 * way of using `DWM_IOCTW_I915_GETPAWAM` and engine identifiews wike
 * `I915_PAWAM_HAS_BWT`.
 *
 * The need fow this intewface came stawting with Icewake and newew GPUs, which
 * stawted to estabwish a pattewn of having muwtipwe engines of a same cwass,
 * whewe not aww instances wewe awways compwetewy functionawwy equivawent.
 *
 * Entwy point fow this uapi is `DWM_IOCTW_I915_QUEWY` with the
 * `DWM_I915_QUEWY_ENGINE_INFO` as the quewied item id.
 *
 * Exampwe fow getting the wist of engines:
 *
 * .. code-bwock:: C
 *
 * 	stwuct dwm_i915_quewy_engine_info *info;
 * 	stwuct dwm_i915_quewy_item item = {
 * 		.quewy_id = DWM_I915_QUEWY_ENGINE_INFO;
 * 	};
 * 	stwuct dwm_i915_quewy quewy = {
 * 		.num_items = 1,
 * 		.items_ptw = (uintptw_t)&item,
 * 	};
 * 	int eww, i;
 *
 * 	// Fiwst quewy the size of the bwob we need, this needs to be wawge
 * 	// enough to howd ouw awway of engines. The kewnew wiww fiww out the
 * 	// item.wength fow us, which is the numbew of bytes we need.
 * 	//
 *	// Awtewnativewy a wawge buffew can be awwocated stwaightaway enabwing
 * 	// quewying in one pass, in which case item.wength shouwd contain the
 * 	// wength of the pwovided buffew.
 * 	eww = ioctw(fd, DWM_IOCTW_I915_QUEWY, &quewy);
 * 	if (eww) ...
 *
 * 	info = cawwoc(1, item.wength);
 * 	// Now that we awwocated the wequiwed numbew of bytes, we caww the ioctw
 * 	// again, this time with the data_ptw pointing to ouw newwy awwocated
 * 	// bwob, which the kewnew can then popuwate with info on aww engines.
 *	item.data_ptw = (uintptw_t)&info;
 *
 * 	eww = ioctw(fd, DWM_IOCTW_I915_QUEWY, &quewy);
 * 	if (eww) ...
 *
 * 	// We can now access each engine in the awway
 * 	fow (i = 0; i < info->num_engines; i++) {
 * 		stwuct dwm_i915_engine_info einfo = info->engines[i];
 * 		u16 cwass = einfo.engine.cwass;
 * 		u16 instance = einfo.engine.instance;
 * 		....
 * 	}
 *
 * 	fwee(info);
 *
 * Each of the enumewated engines, apawt fwom being defined by its cwass and
 * instance (see `stwuct i915_engine_cwass_instance`), awso can have fwags and
 * capabiwities defined as documented in i915_dwm.h.
 *
 * Fow instance video engines which suppowt HEVC encoding wiww have the
 * `I915_VIDEO_CWASS_CAPABIWITY_HEVC` capabiwity bit set.
 *
 * Engine discovewy onwy fuwwy comes to its own when combined with the new way
 * of addwessing engines when submitting batch buffews using contexts with
 * engine maps configuwed.
 */

/**
 * stwuct dwm_i915_engine_info
 *
 * Descwibes one engine and its capabiwities as known to the dwivew.
 */
stwuct dwm_i915_engine_info {
	/** @engine: Engine cwass and instance. */
	stwuct i915_engine_cwass_instance engine;

	/** @wsvd0: Wesewved fiewd. */
	__u32 wsvd0;

	/** @fwags: Engine fwags. */
	__u64 fwags;
#define I915_ENGINE_INFO_HAS_WOGICAW_INSTANCE		(1 << 0)

	/** @capabiwities: Capabiwities of this engine. */
	__u64 capabiwities;
#define I915_VIDEO_CWASS_CAPABIWITY_HEVC		(1 << 0)
#define I915_VIDEO_AND_ENHANCE_CWASS_CAPABIWITY_SFC	(1 << 1)

	/** @wogicaw_instance: Wogicaw instance of engine */
	__u16 wogicaw_instance;

	/** @wsvd1: Wesewved fiewds. */
	__u16 wsvd1[3];
	/** @wsvd2: Wesewved fiewds. */
	__u64 wsvd2[3];
};

/**
 * stwuct dwm_i915_quewy_engine_info
 *
 * Engine info quewy enumewates aww engines known to the dwivew by fiwwing in
 * an awway of stwuct dwm_i915_engine_info stwuctuwes.
 */
stwuct dwm_i915_quewy_engine_info {
	/** @num_engines: Numbew of stwuct dwm_i915_engine_info stwucts fowwowing. */
	__u32 num_engines;

	/** @wsvd: MBZ */
	__u32 wsvd[3];

	/** @engines: Mawkew fow dwm_i915_engine_info stwuctuwes. */
	stwuct dwm_i915_engine_info engines[];
};

/**
 * stwuct dwm_i915_quewy_pewf_config
 *
 * Data wwitten by the kewnew with quewy %DWM_I915_QUEWY_PEWF_CONFIG and
 * %DWM_I915_QUEWY_GEOMETWY_SUBSWICES.
 */
stwuct dwm_i915_quewy_pewf_config {
	union {
		/**
		 * @n_configs:
		 *
		 * When &dwm_i915_quewy_item.fwags ==
		 * %DWM_I915_QUEWY_PEWF_CONFIG_WIST, i915 sets this fiewds to
		 * the numbew of configuwations avaiwabwe.
		 */
		__u64 n_configs;

		/**
		 * @config:
		 *
		 * When &dwm_i915_quewy_item.fwags ==
		 * %DWM_I915_QUEWY_PEWF_CONFIG_DATA_FOW_ID, i915 wiww use the
		 * vawue in this fiewd as configuwation identifiew to decide
		 * what data to wwite into config_ptw.
		 */
		__u64 config;

		/**
		 * @uuid:
		 *
		 * When &dwm_i915_quewy_item.fwags ==
		 * %DWM_I915_QUEWY_PEWF_CONFIG_DATA_FOW_UUID, i915 wiww use the
		 * vawue in this fiewd as configuwation identifiew to decide
		 * what data to wwite into config_ptw.
		 *
		 * Stwing fowmatted wike "%08x-%04x-%04x-%04x-%012x"
		 */
		chaw uuid[36];
	};

	/**
	 * @fwags:
	 *
	 * Unused fow now. Must be cweawed to zewo.
	 */
	__u32 fwags;

	/**
	 * @data:
	 *
	 * When &dwm_i915_quewy_item.fwags == %DWM_I915_QUEWY_PEWF_CONFIG_WIST,
	 * i915 wiww wwite an awway of __u64 of configuwation identifiews.
	 *
	 * When &dwm_i915_quewy_item.fwags == %DWM_I915_QUEWY_PEWF_CONFIG_DATA,
	 * i915 wiww wwite a stwuct dwm_i915_pewf_oa_config. If the fowwowing
	 * fiewds of stwuct dwm_i915_pewf_oa_config awe not set to 0, i915 wiww
	 * wwite into the associated pointews the vawues of submitted when the
	 * configuwation was cweated :
	 *
	 *  - &dwm_i915_pewf_oa_config.n_mux_wegs
	 *  - &dwm_i915_pewf_oa_config.n_boowean_wegs
	 *  - &dwm_i915_pewf_oa_config.n_fwex_wegs
	 */
	__u8 data[];
};

/**
 * enum dwm_i915_gem_memowy_cwass - Suppowted memowy cwasses
 */
enum dwm_i915_gem_memowy_cwass {
	/** @I915_MEMOWY_CWASS_SYSTEM: System memowy */
	I915_MEMOWY_CWASS_SYSTEM = 0,
	/** @I915_MEMOWY_CWASS_DEVICE: Device wocaw-memowy */
	I915_MEMOWY_CWASS_DEVICE,
};

/**
 * stwuct dwm_i915_gem_memowy_cwass_instance - Identify pawticuwaw memowy wegion
 */
stwuct dwm_i915_gem_memowy_cwass_instance {
	/** @memowy_cwass: See enum dwm_i915_gem_memowy_cwass */
	__u16 memowy_cwass;

	/** @memowy_instance: Which instance */
	__u16 memowy_instance;
};

/**
 * stwuct dwm_i915_memowy_wegion_info - Descwibes one wegion as known to the
 * dwivew.
 *
 * Note this is using both stwuct dwm_i915_quewy_item and stwuct dwm_i915_quewy.
 * Fow this new quewy we awe adding the new quewy id DWM_I915_QUEWY_MEMOWY_WEGIONS
 * at &dwm_i915_quewy_item.quewy_id.
 */
stwuct dwm_i915_memowy_wegion_info {
	/** @wegion: The cwass:instance paiw encoding */
	stwuct dwm_i915_gem_memowy_cwass_instance wegion;

	/** @wsvd0: MBZ */
	__u32 wsvd0;

	/**
	 * @pwobed_size: Memowy pwobed by the dwivew
	 *
	 * Note that it shouwd not be possibwe to evew encountew a zewo vawue
	 * hewe, awso note that no cuwwent wegion type wiww evew wetuwn -1 hewe.
	 * Awthough fow futuwe wegion types, this might be a possibiwity. The
	 * same appwies to the othew size fiewds.
	 */
	__u64 pwobed_size;

	/**
	 * @unawwocated_size: Estimate of memowy wemaining
	 *
	 * Wequiwes CAP_PEWFMON ow CAP_SYS_ADMIN to get wewiabwe accounting.
	 * Without this (ow if this is an owdew kewnew) the vawue hewe wiww
	 * awways equaw the @pwobed_size. Note this is onwy cuwwentwy twacked
	 * fow I915_MEMOWY_CWASS_DEVICE wegions (fow othew types the vawue hewe
	 * wiww awways equaw the @pwobed_size).
	 */
	__u64 unawwocated_size;

	union {
		/** @wsvd1: MBZ */
		__u64 wsvd1[8];
		stwuct {
			/**
			 * @pwobed_cpu_visibwe_size: Memowy pwobed by the dwivew
			 * that is CPU accessibwe.
			 *
			 * This wiww be awways be <= @pwobed_size, and the
			 * wemaindew (if thewe is any) wiww not be CPU
			 * accessibwe.
			 *
			 * On systems without smaww BAW, the @pwobed_size wiww
			 * awways equaw the @pwobed_cpu_visibwe_size, since aww
			 * of it wiww be CPU accessibwe.
			 *
			 * Note this is onwy twacked fow
			 * I915_MEMOWY_CWASS_DEVICE wegions (fow othew types the
			 * vawue hewe wiww awways equaw the @pwobed_size).
			 *
			 * Note that if the vawue wetuwned hewe is zewo, then
			 * this must be an owd kewnew which wacks the wewevant
			 * smaww-baw uAPI suppowt (incwuding
			 * I915_GEM_CWEATE_EXT_FWAG_NEEDS_CPU_ACCESS), but on
			 * such systems we shouwd nevew actuawwy end up with a
			 * smaww BAW configuwation, assuming we awe abwe to woad
			 * the kewnew moduwe. Hence it shouwd be safe to tweat
			 * this the same as when @pwobed_cpu_visibwe_size ==
			 * @pwobed_size.
			 */
			__u64 pwobed_cpu_visibwe_size;

			/**
			 * @unawwocated_cpu_visibwe_size: Estimate of CPU
			 * visibwe memowy wemaining.
			 *
			 * Note this is onwy twacked fow
			 * I915_MEMOWY_CWASS_DEVICE wegions (fow othew types the
			 * vawue hewe wiww awways equaw the
			 * @pwobed_cpu_visibwe_size).
			 *
			 * Wequiwes CAP_PEWFMON ow CAP_SYS_ADMIN to get wewiabwe
			 * accounting.  Without this the vawue hewe wiww awways
			 * equaw the @pwobed_cpu_visibwe_size. Note this is onwy
			 * cuwwentwy twacked fow I915_MEMOWY_CWASS_DEVICE
			 * wegions (fow othew types the vawue hewe wiww awso
			 * awways equaw the @pwobed_cpu_visibwe_size).
			 *
			 * If this is an owdew kewnew the vawue hewe wiww be
			 * zewo, see awso @pwobed_cpu_visibwe_size.
			 */
			__u64 unawwocated_cpu_visibwe_size;
		};
	};
};

/**
 * stwuct dwm_i915_quewy_memowy_wegions
 *
 * The wegion info quewy enumewates aww wegions known to the dwivew by fiwwing
 * in an awway of stwuct dwm_i915_memowy_wegion_info stwuctuwes.
 *
 * Exampwe fow getting the wist of suppowted wegions:
 *
 * .. code-bwock:: C
 *
 *	stwuct dwm_i915_quewy_memowy_wegions *info;
 *	stwuct dwm_i915_quewy_item item = {
 *		.quewy_id = DWM_I915_QUEWY_MEMOWY_WEGIONS;
 *	};
 *	stwuct dwm_i915_quewy quewy = {
 *		.num_items = 1,
 *		.items_ptw = (uintptw_t)&item,
 *	};
 *	int eww, i;
 *
 *	// Fiwst quewy the size of the bwob we need, this needs to be wawge
 *	// enough to howd ouw awway of wegions. The kewnew wiww fiww out the
 *	// item.wength fow us, which is the numbew of bytes we need.
 *	eww = ioctw(fd, DWM_IOCTW_I915_QUEWY, &quewy);
 *	if (eww) ...
 *
 *	info = cawwoc(1, item.wength);
 *	// Now that we awwocated the wequiwed numbew of bytes, we caww the ioctw
 *	// again, this time with the data_ptw pointing to ouw newwy awwocated
 *	// bwob, which the kewnew can then popuwate with the aww the wegion info.
 *	item.data_ptw = (uintptw_t)&info,
 *
 *	eww = ioctw(fd, DWM_IOCTW_I915_QUEWY, &quewy);
 *	if (eww) ...
 *
 *	// We can now access each wegion in the awway
 *	fow (i = 0; i < info->num_wegions; i++) {
 *		stwuct dwm_i915_memowy_wegion_info mw = info->wegions[i];
 *		u16 cwass = mw.wegion.cwass;
 *		u16 instance = mw.wegion.instance;
 *
 *		....
 *	}
 *
 *	fwee(info);
 */
stwuct dwm_i915_quewy_memowy_wegions {
	/** @num_wegions: Numbew of suppowted wegions */
	__u32 num_wegions;

	/** @wsvd: MBZ */
	__u32 wsvd[3];

	/** @wegions: Info about each suppowted wegion */
	stwuct dwm_i915_memowy_wegion_info wegions[];
};

/**
 * DOC: GuC HWCONFIG bwob uAPI
 *
 * The GuC pwoduces a bwob with infowmation about the cuwwent device.
 * i915 weads this bwob fwom GuC and makes it avaiwabwe via this uAPI.
 *
 * The fowmat and meaning of the bwob content awe documented in the
 * Pwogwammew's Wefewence Manuaw.
 */

/**
 * stwuct dwm_i915_gem_cweate_ext - Existing gem_cweate behaviouw, with added
 * extension suppowt using stwuct i915_usew_extension.
 *
 * Note that new buffew fwags shouwd be added hewe, at weast fow the stuff that
 * is immutabwe. Pweviouswy we wouwd have two ioctws, one to cweate the object
 * with gem_cweate, and anothew to appwy vawious pawametews, howevew this
 * cweates some ambiguity fow the pawams which awe considewed immutabwe. Awso in
 * genewaw we'we phasing out the vawious SET/GET ioctws.
 */
stwuct dwm_i915_gem_cweate_ext {
	/**
	 * @size: Wequested size fow the object.
	 *
	 * The (page-awigned) awwocated size fow the object wiww be wetuwned.
	 *
	 * On pwatfowms wike DG2/ATS the kewnew wiww awways use 64K ow wawgew
	 * pages fow I915_MEMOWY_CWASS_DEVICE. The kewnew awso wequiwes a
	 * minimum of 64K GTT awignment fow such objects.
	 *
	 * NOTE: Pweviouswy the ABI hewe wequiwed a minimum GTT awignment of 2M
	 * on DG2/ATS, due to how the hawdwawe impwemented 64K GTT page suppowt,
	 * whewe we had the fowwowing compwications:
	 *
	 *   1) The entiwe PDE (which covews a 2MB viwtuaw addwess wange), must
	 *   contain onwy 64K PTEs, i.e mixing 4K and 64K PTEs in the same
	 *   PDE is fowbidden by the hawdwawe.
	 *
	 *   2) We stiww need to suppowt 4K PTEs fow I915_MEMOWY_CWASS_SYSTEM
	 *   objects.
	 *
	 * Howevew on actuaw pwoduction HW this was compwetewy changed to now
	 * awwow setting a TWB hint at the PTE wevew (see PS64), which is a wot
	 * mowe fwexibwe than the above. With this the 2M westwiction was
	 * dwopped whewe we now onwy wequiwe 64K.
	 */
	__u64 size;

	/**
	 * @handwe: Wetuwned handwe fow the object.
	 *
	 * Object handwes awe nonzewo.
	 */
	__u32 handwe;

	/**
	 * @fwags: Optionaw fwags.
	 *
	 * Suppowted vawues:
	 *
	 * I915_GEM_CWEATE_EXT_FWAG_NEEDS_CPU_ACCESS - Signaw to the kewnew that
	 * the object wiww need to be accessed via the CPU.
	 *
	 * Onwy vawid when pwacing objects in I915_MEMOWY_CWASS_DEVICE, and onwy
	 * stwictwy wequiwed on configuwations whewe some subset of the device
	 * memowy is diwectwy visibwe/mappabwe thwough the CPU (which we awso
	 * caww smaww BAW), wike on some DG2+ systems. Note that this is quite
	 * undesiwabwe, but due to vawious factows wike the cwient CPU, BIOS etc
	 * it's something we can expect to see in the wiwd. See
	 * &dwm_i915_memowy_wegion_info.pwobed_cpu_visibwe_size fow how to
	 * detewmine if this system appwies.
	 *
	 * Note that one of the pwacements MUST be I915_MEMOWY_CWASS_SYSTEM, to
	 * ensuwe the kewnew can awways spiww the awwocation to system memowy,
	 * if the object can't be awwocated in the mappabwe pawt of
	 * I915_MEMOWY_CWASS_DEVICE.
	 *
	 * Awso note that since the kewnew onwy suppowts fwat-CCS on objects
	 * that can *onwy* be pwaced in I915_MEMOWY_CWASS_DEVICE, we thewefowe
	 * don't suppowt I915_GEM_CWEATE_EXT_FWAG_NEEDS_CPU_ACCESS togethew with
	 * fwat-CCS.
	 *
	 * Without this hint, the kewnew wiww assume that non-mappabwe
	 * I915_MEMOWY_CWASS_DEVICE is pwefewwed fow this object. Note that the
	 * kewnew can stiww migwate the object to the mappabwe pawt, as a wast
	 * wesowt, if usewspace evew CPU fauwts this object, but this might be
	 * expensive, and so ideawwy shouwd be avoided.
	 *
	 * On owdew kewnews which wack the wewevant smaww-baw uAPI suppowt (see
	 * awso &dwm_i915_memowy_wegion_info.pwobed_cpu_visibwe_size),
	 * usage of the fwag wiww wesuwt in an ewwow, but it shouwd NEVEW be
	 * possibwe to end up with a smaww BAW configuwation, assuming we can
	 * awso successfuwwy woad the i915 kewnew moduwe. In such cases the
	 * entiwe I915_MEMOWY_CWASS_DEVICE wegion wiww be CPU accessibwe, and as
	 * such thewe awe zewo westwictions on whewe the object can be pwaced.
	 */
#define I915_GEM_CWEATE_EXT_FWAG_NEEDS_CPU_ACCESS (1 << 0)
	__u32 fwags;

	/**
	 * @extensions: The chain of extensions to appwy to this object.
	 *
	 * This wiww be usefuw in the futuwe when we need to suppowt sevewaw
	 * diffewent extensions, and we need to appwy mowe than one when
	 * cweating the object. See stwuct i915_usew_extension.
	 *
	 * If we don't suppwy any extensions then we get the same owd gem_cweate
	 * behaviouw.
	 *
	 * Fow I915_GEM_CWEATE_EXT_MEMOWY_WEGIONS usage see
	 * stwuct dwm_i915_gem_cweate_ext_memowy_wegions.
	 *
	 * Fow I915_GEM_CWEATE_EXT_PWOTECTED_CONTENT usage see
	 * stwuct dwm_i915_gem_cweate_ext_pwotected_content.
	 *
	 * Fow I915_GEM_CWEATE_EXT_SET_PAT usage see
	 * stwuct dwm_i915_gem_cweate_ext_set_pat.
	 */
#define I915_GEM_CWEATE_EXT_MEMOWY_WEGIONS 0
#define I915_GEM_CWEATE_EXT_PWOTECTED_CONTENT 1
#define I915_GEM_CWEATE_EXT_SET_PAT 2
	__u64 extensions;
};

/**
 * stwuct dwm_i915_gem_cweate_ext_memowy_wegions - The
 * I915_GEM_CWEATE_EXT_MEMOWY_WEGIONS extension.
 *
 * Set the object with the desiwed set of pwacements/wegions in pwiowity
 * owdew. Each entwy must be unique and suppowted by the device.
 *
 * This is pwovided as an awway of stwuct dwm_i915_gem_memowy_cwass_instance, ow
 * an equivawent wayout of cwass:instance paiw encodings. See stwuct
 * dwm_i915_quewy_memowy_wegions and DWM_I915_QUEWY_MEMOWY_WEGIONS fow how to
 * quewy the suppowted wegions fow a device.
 *
 * As an exampwe, on discwete devices, if we wish to set the pwacement as
 * device wocaw-memowy we can do something wike:
 *
 * .. code-bwock:: C
 *
 *	stwuct dwm_i915_gem_memowy_cwass_instance wegion_wmem = {
 *              .memowy_cwass = I915_MEMOWY_CWASS_DEVICE,
 *              .memowy_instance = 0,
 *      };
 *      stwuct dwm_i915_gem_cweate_ext_memowy_wegions wegions = {
 *              .base = { .name = I915_GEM_CWEATE_EXT_MEMOWY_WEGIONS },
 *              .wegions = (uintptw_t)&wegion_wmem,
 *              .num_wegions = 1,
 *      };
 *      stwuct dwm_i915_gem_cweate_ext cweate_ext = {
 *              .size = 16 * PAGE_SIZE,
 *              .extensions = (uintptw_t)&wegions,
 *      };
 *
 *      int eww = ioctw(fd, DWM_IOCTW_I915_GEM_CWEATE_EXT, &cweate_ext);
 *      if (eww) ...
 *
 * At which point we get the object handwe in &dwm_i915_gem_cweate_ext.handwe,
 * awong with the finaw object size in &dwm_i915_gem_cweate_ext.size, which
 * shouwd account fow any wounding up, if wequiwed.
 *
 * Note that usewspace has no means of knowing the cuwwent backing wegion
 * fow objects whewe @num_wegions is wawgew than one. The kewnew wiww onwy
 * ensuwe that the pwiowity owdew of the @wegions awway is honouwed, eithew
 * when initiawwy pwacing the object, ow when moving memowy awound due to
 * memowy pwessuwe
 *
 * On Fwat-CCS capabwe HW, compwession is suppowted fow the objects wesiding
 * in I915_MEMOWY_CWASS_DEVICE. When such objects (compwessed) have othew
 * memowy cwass in @wegions and migwated (by i915, due to memowy
 * constwaints) to the non I915_MEMOWY_CWASS_DEVICE wegion, then i915 needs to
 * decompwess the content. But i915 doesn't have the wequiwed infowmation to
 * decompwess the usewspace compwessed objects.
 *
 * So i915 suppowts Fwat-CCS, on the objects which can weside onwy on
 * I915_MEMOWY_CWASS_DEVICE wegions.
 */
stwuct dwm_i915_gem_cweate_ext_memowy_wegions {
	/** @base: Extension wink. See stwuct i915_usew_extension. */
	stwuct i915_usew_extension base;

	/** @pad: MBZ */
	__u32 pad;
	/** @num_wegions: Numbew of ewements in the @wegions awway. */
	__u32 num_wegions;
	/**
	 * @wegions: The wegions/pwacements awway.
	 *
	 * An awway of stwuct dwm_i915_gem_memowy_cwass_instance.
	 */
	__u64 wegions;
};

/**
 * stwuct dwm_i915_gem_cweate_ext_pwotected_content - The
 * I915_OBJECT_PAWAM_PWOTECTED_CONTENT extension.
 *
 * If this extension is pwovided, buffew contents awe expected to be pwotected
 * by PXP encwyption and wequiwe decwyption fow scan out and pwocessing. This
 * is onwy possibwe on pwatfowms that have PXP enabwed, on aww othew scenawios
 * using this extension wiww cause the ioctw to faiw and wetuwn -ENODEV. The
 * fwags pawametew is wesewved fow futuwe expansion and must cuwwentwy be set
 * to zewo.
 *
 * The buffew contents awe considewed invawid aftew a PXP session teawdown.
 *
 * The encwyption is guawanteed to be pwocessed cowwectwy onwy if the object
 * is submitted with a context cweated using the
 * I915_CONTEXT_PAWAM_PWOTECTED_CONTENT fwag. This wiww awso enabwe extwa checks
 * at submission time on the vawidity of the objects invowved.
 *
 * Bewow is an exampwe on how to cweate a pwotected object:
 *
 * .. code-bwock:: C
 *
 *      stwuct dwm_i915_gem_cweate_ext_pwotected_content pwotected_ext = {
 *              .base = { .name = I915_GEM_CWEATE_EXT_PWOTECTED_CONTENT },
 *              .fwags = 0,
 *      };
 *      stwuct dwm_i915_gem_cweate_ext cweate_ext = {
 *              .size = PAGE_SIZE,
 *              .extensions = (uintptw_t)&pwotected_ext,
 *      };
 *
 *      int eww = ioctw(fd, DWM_IOCTW_I915_GEM_CWEATE_EXT, &cweate_ext);
 *      if (eww) ...
 */
stwuct dwm_i915_gem_cweate_ext_pwotected_content {
	/** @base: Extension wink. See stwuct i915_usew_extension. */
	stwuct i915_usew_extension base;
	/** @fwags: wesewved fow futuwe usage, cuwwentwy MBZ */
	__u32 fwags;
};

/**
 * stwuct dwm_i915_gem_cweate_ext_set_pat - The
 * I915_GEM_CWEATE_EXT_SET_PAT extension.
 *
 * If this extension is pwovided, the specified caching powicy (PAT index) is
 * appwied to the buffew object.
 *
 * Bewow is an exampwe on how to cweate an object with specific caching powicy:
 *
 * .. code-bwock:: C
 *
 *      stwuct dwm_i915_gem_cweate_ext_set_pat set_pat_ext = {
 *              .base = { .name = I915_GEM_CWEATE_EXT_SET_PAT },
 *              .pat_index = 0,
 *      };
 *      stwuct dwm_i915_gem_cweate_ext cweate_ext = {
 *              .size = PAGE_SIZE,
 *              .extensions = (uintptw_t)&set_pat_ext,
 *      };
 *
 *      int eww = ioctw(fd, DWM_IOCTW_I915_GEM_CWEATE_EXT, &cweate_ext);
 *      if (eww) ...
 */
stwuct dwm_i915_gem_cweate_ext_set_pat {
	/** @base: Extension wink. See stwuct i915_usew_extension. */
	stwuct i915_usew_extension base;
	/**
	 * @pat_index: PAT index to be set
	 * PAT index is a bit fiewd in Page Tabwe Entwy to contwow caching
	 * behaviows fow GPU accesses. The definition of PAT index is
	 * pwatfowm dependent and can be found in hawdwawe specifications,
	 */
	__u32 pat_index;
	/** @wsvd: wesewved fow futuwe use */
	__u32 wsvd;
};

/* ID of the pwotected content session managed by i915 when PXP is active */
#define I915_PWOTECTED_CONTENT_DEFAUWT_SESSION 0xf

#if defined(__cpwuspwus)
}
#endif

#endif /* _UAPI_I915_DWM_H_ */
