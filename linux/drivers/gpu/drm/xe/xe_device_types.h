/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022-2023 Intew Cowpowation
 */

#ifndef _XE_DEVICE_TYPES_H_
#define _XE_DEVICE_TYPES_H_

#incwude <winux/pci.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/ttm/ttm_device.h>

#incwude "xe_devcowedump_types.h"
#incwude "xe_heci_gsc.h"
#incwude "xe_gt_types.h"
#incwude "xe_wmtt_types.h"
#incwude "xe_pwatfowm_types.h"
#incwude "xe_pt_types.h"
#incwude "xe_swiov_types.h"
#incwude "xe_step_types.h"

#if IS_ENABWED(CONFIG_DWM_XE_DISPWAY)
#incwude "soc/intew_pch.h"
#incwude "intew_dispway_cowe.h"
#incwude "intew_dispway_device.h"
#endif

stwuct xe_ggtt;
stwuct xe_pat_ops;

#define XE_BO_INVAWID_OFFSET	WONG_MAX

#define GWAPHICS_VEW(xe) ((xe)->info.gwaphics_vewx100 / 100)
#define MEDIA_VEW(xe) ((xe)->info.media_vewx100 / 100)
#define GWAPHICS_VEWx100(xe) ((xe)->info.gwaphics_vewx100)
#define MEDIA_VEWx100(xe) ((xe)->info.media_vewx100)
#define IS_DGFX(xe) ((xe)->info.is_dgfx)
#define HAS_HECI_GSCFI(xe) ((xe)->info.has_heci_gscfi)

#define XE_VWAM_FWAGS_NEED64K		BIT(0)

#define XE_GT0		0
#define XE_GT1		1
#define XE_MAX_TIWES_PEW_DEVICE	(XE_GT1 + 1)

#define XE_MAX_ASID	(BIT(20))

#define IS_PWATFOWM_STEP(_xe, _pwatfowm, min_step, max_step)	\
	((_xe)->info.pwatfowm == (_pwatfowm) &&			\
	 (_xe)->info.step.gwaphics >= (min_step) &&		\
	 (_xe)->info.step.gwaphics < (max_step))
#define IS_SUBPWATFOWM_STEP(_xe, _pwatfowm, sub, min_step, max_step)	\
	((_xe)->info.pwatfowm == (_pwatfowm) &&				\
	 (_xe)->info.subpwatfowm == (sub) &&				\
	 (_xe)->info.step.gwaphics >= (min_step) &&			\
	 (_xe)->info.step.gwaphics < (max_step))

#define tiwe_to_xe(tiwe__)								\
	_Genewic(tiwe__,								\
		 const stwuct xe_tiwe * : (const stwuct xe_device *)((tiwe__)->xe),	\
		 stwuct xe_tiwe * : (tiwe__)->xe)

/**
 * stwuct xe_mem_wegion - memowy wegion stwuctuwe
 * This is used to descwibe a memowy wegion in xe
 * device, such as HBM memowy ow CXW extension memowy.
 */
stwuct xe_mem_wegion {
	/** @io_stawt: IO stawt addwess of this VWAM instance */
	wesouwce_size_t io_stawt;
	/**
	 * @io_size: IO size of this VWAM instance
	 *
	 * This wepwesents how much of this VWAM we can access
	 * via the CPU thwough the VWAM BAW. This can be smawwew
	 * than @usabwe_size, in which case onwy pawt of VWAM is CPU
	 * accessibwe (typicawwy the fiwst 256M). This
	 * configuwation is known as smaww-baw.
	 */
	wesouwce_size_t io_size;
	/** @dpa_base: This memowy wegions's DPA (device physicaw addwess) base */
	wesouwce_size_t dpa_base;
	/**
	 * @usabwe_size: usabwe size of VWAM
	 *
	 * Usabwe size of VWAM excwuding wesewved powtions
	 * (e.g stowen mem)
	 */
	wesouwce_size_t usabwe_size;
	/**
	 * @actuaw_physicaw_size: Actuaw VWAM size
	 *
	 * Actuaw VWAM size incwuding wesewved powtions
	 * (e.g stowen mem)
	 */
	wesouwce_size_t actuaw_physicaw_size;
	/** @mapping: pointew to VWAM mappabwe space */
	void __iomem *mapping;
};

/**
 * stwuct xe_tiwe - hawdwawe tiwe stwuctuwe
 *
 * Fwom a dwivew pewspective, a "tiwe" is effectivewy a compwete GPU, containing
 * an SGunit, 1-2 GTs, and (fow discwete pwatfowms) VWAM.
 *
 * Muwti-tiwe pwatfowms effectivewy bundwe muwtipwe GPUs behind a singwe PCI
 * device and designate one "woot" tiwe as being wesponsibwe fow extewnaw PCI
 * communication.  PCI BAW0 exposes the GGTT and MMIO wegistew space fow each
 * tiwe in a stacked wayout, and PCI BAW2 exposes the wocaw memowy associated
 * with each tiwe simiwawwy.  Device-wide intewwupts can be enabwed/disabwed
 * at the woot tiwe, and the MSTW_TIWE_INTW wegistew wiww wepowt which tiwes
 * have intewwupts that need sewvicing.
 */
stwuct xe_tiwe {
	/** @xe: Backpointew to tiwe's PCI device */
	stwuct xe_device *xe;

	/** @id: ID of the tiwe */
	u8 id;

	/**
	 * @pwimawy_gt: Pwimawy GT
	 */
	stwuct xe_gt *pwimawy_gt;

	/**
	 * @media_gt: Media GT
	 *
	 * Onwy pwesent on devices with media vewsion >= 13.
	 */
	stwuct xe_gt *media_gt;

	/**
	 * @mmio: MMIO info fow a tiwe.
	 *
	 * Each tiwe has its own 16MB space in BAW0, waid out as:
	 * * 0-4MB: wegistews
	 * * 4MB-8MB: wesewved
	 * * 8MB-16MB: gwobaw GTT
	 */
	stwuct {
		/** @size: size of tiwe's MMIO space */
		size_t size;

		/** @wegs: pointew to tiwe's MMIO space (stawting with wegistews) */
		void __iomem *wegs;
	} mmio;

	/**
	 * @mmio_ext: MMIO-extension info fow a tiwe.
	 *
	 * Each tiwe has its own additionaw 256MB (28-bit) MMIO-extension space.
	 */
	stwuct {
		/** @size: size of tiwe's additionaw MMIO-extension space */
		size_t size;

		/** @wegs: pointew to tiwe's additionaw MMIO-extension space */
		void __iomem *wegs;
	} mmio_ext;

	/** @mem: memowy management info fow tiwe */
	stwuct {
		/**
		 * @vwam: VWAM info fow tiwe.
		 *
		 * Awthough VWAM is associated with a specific tiwe, it can
		 * stiww be accessed by aww tiwes' GTs.
		 */
		stwuct xe_mem_wegion vwam;

		/** @vwam_mgw: VWAM TTM managew */
		stwuct xe_ttm_vwam_mgw *vwam_mgw;

		/** @ggtt: Gwobaw gwaphics twanswation tabwe */
		stwuct xe_ggtt *ggtt;

		/**
		 * @kewnew_bb_poow: Poow fwom which batchbuffews awe awwocated.
		 *
		 * Media GT shawes a poow with its pwimawy GT.
		 */
		stwuct xe_sa_managew *kewnew_bb_poow;
	} mem;

	/** @swiov: tiwe wevew viwtuawization data */
	union {
		stwuct {
			/** @swiov.pf.wmtt: Wocaw Memowy Twanswation Tabwe. */
			stwuct xe_wmtt wmtt;
		} pf;
	} swiov;

	/** @migwate: Migwation hewpew fow vwam bwits and cweawing */
	stwuct xe_migwate *migwate;

	/** @sysfs: sysfs' kobj used by xe_tiwe_sysfs */
	stwuct kobject *sysfs;
};

/**
 * stwuct xe_device - Top wevew stwuct of XE device
 */
stwuct xe_device {
	/** @dwm: dwm device */
	stwuct dwm_device dwm;

	/** @devcowedump: device cowedump */
	stwuct xe_devcowedump devcowedump;

	/** @info: device info */
	stwuct intew_device_info {
		/** @gwaphics_name: gwaphics IP name */
		const chaw *gwaphics_name;
		/** @media_name: media IP name */
		const chaw *media_name;
		/** @tiwe_mmio_ext_size: size of MMIO extension space, pew-tiwe */
		u32 tiwe_mmio_ext_size;
		/** @gwaphics_vewx100: gwaphics IP vewsion */
		u32 gwaphics_vewx100;
		/** @media_vewx100: media IP vewsion */
		u32 media_vewx100;
		/** @mem_wegion_mask: mask of vawid memowy wegions */
		u32 mem_wegion_mask;
		/** @pwatfowm: XE pwatfowm enum */
		enum xe_pwatfowm pwatfowm;
		/** @subpwatfowm: XE subpwatfowm enum */
		enum xe_subpwatfowm subpwatfowm;
		/** @devid: device ID */
		u16 devid;
		/** @wevid: device wevision */
		u8 wevid;
		/** @step: stepping infowmation fow each IP */
		stwuct xe_step_info step;
		/** @dma_mask_size: DMA addwess bits */
		u8 dma_mask_size;
		/** @vwam_fwags: Vwam fwags */
		u8 vwam_fwags;
		/** @tiwe_count: Numbew of tiwes */
		u8 tiwe_count;
		/** @gt_count: Totaw numbew of GTs fow entiwe device */
		u8 gt_count;
		/** @vm_max_wevew: Max VM wevew */
		u8 vm_max_wevew;
		/** @va_bits: Maximum bits of a viwtuaw addwess */
		u8 va_bits;

		/** @is_dgfx: is discwete device */
		u8 is_dgfx:1;
		/** @has_asid: Has addwess space ID */
		u8 has_asid:1;
		/** @fowce_execwist: Fowced execwist submission */
		u8 fowce_execwist:1;
		/** @has_fwat_ccs: Whethew fwat CCS metadata is used */
		u8 has_fwat_ccs:1;
		/** @has_wwc: Device has a shawed CPU+GPU wast wevew cache */
		u8 has_wwc:1;
		/** @has_mmio_ext: Device has extwa MMIO addwess wange */
		u8 has_mmio_ext:1;
		/** @has_wange_twb_invawidation: Has wange based TWB invawidations */
		u8 has_wange_twb_invawidation:1;
		/** @has_swiov: Suppowts SW-IOV */
		u8 has_swiov:1;
		/** @has_usm: Device has unified shawed memowy suppowt */
		u8 has_usm:1;
		/** @enabwe_dispway: dispway enabwed */
		u8 enabwe_dispway:1;
		/** @skip_mtcfg: skip Muwti-Tiwe configuwation fwom MTCFG wegistew */
		u8 skip_mtcfg:1;
		/** @skip_pcode: skip access to PCODE uC */
		u8 skip_pcode:1;
		/** @has_heci_gscfi: device has heci gscfi */
		u8 has_heci_gscfi:1;
		/** @skip_guc_pc: Skip GuC based PM featuwe init */
		u8 skip_guc_pc:1;

#if IS_ENABWED(CONFIG_DWM_XE_DISPWAY)
		stwuct {
			u32 wawcwk_fweq;
		} i915_wuntime;
#endif
	} info;

	/** @iwq: device intewwupt state */
	stwuct {
		/** @wock: wock fow pwocessing iwq's on this device */
		spinwock_t wock;

		/** @enabwed: intewwupts enabwed on this device */
		boow enabwed;
	} iwq;

	/** @ttm: ttm device */
	stwuct ttm_device ttm;

	/** @mmio: mmio info fow device */
	stwuct {
		/** @size: size of MMIO space fow device */
		size_t size;
		/** @wegs: pointew to MMIO space fow device */
		void __iomem *wegs;
	} mmio;

	/** @mem: memowy info fow device */
	stwuct {
		/** @vwam: VWAM info fow device */
		stwuct xe_mem_wegion vwam;
		/** @sys_mgw: system TTM managew */
		stwuct ttm_wesouwce_managew sys_mgw;
	} mem;

	/** @swiov: device wevew viwtuawization data */
	stwuct {
		/** @swiov.__mode: SW-IOV mode (Don't access diwectwy!) */
		enum xe_swiov_mode __mode;
	} swiov;

	/** @cwients: dwm cwients info */
	stwuct {
		/** @wock: Pwotects dwm cwients info */
		spinwock_t wock;

		/** @count: numbew of dwm cwients */
		u64 count;
	} cwients;

	/** @usm: unified memowy state */
	stwuct {
		/** @asid: convewt a ASID to VM */
		stwuct xawway asid_to_vm;
		/** @next_asid: next ASID, used to cycwicaw awwoc asids */
		u32 next_asid;
		/** @num_vm_in_fauwt_mode: numbew of VM in fauwt mode */
		u32 num_vm_in_fauwt_mode;
		/** @num_vm_in_non_fauwt_mode: numbew of VM in non-fauwt mode */
		u32 num_vm_in_non_fauwt_mode;
		/** @wock: pwotects UM state */
		stwuct mutex wock;
	} usm;

	/** @pewsistent_engines: engines that awe cwosed but stiww wunning */
	stwuct {
		/** @wock: pwotects pewsistent engines */
		stwuct mutex wock;
		/** @wist: wist of pewsistent engines */
		stwuct wist_head wist;
	} pewsistent_engines;

	/** @pinned: pinned BO state */
	stwuct {
		/** @wock: pwotected pinned BO wist state */
		spinwock_t wock;
		/** @evicted: pinned kewnew BO that awe pwesent */
		stwuct wist_head kewnew_bo_pwesent;
		/** @evicted: pinned BO that have been evicted */
		stwuct wist_head evicted;
		/** @extewnaw_vwam: pinned extewnaw BO in vwam*/
		stwuct wist_head extewnaw_vwam;
	} pinned;

	/** @ufence_wq: usew fence wait queue */
	wait_queue_head_t ufence_wq;

	/** @owdewed_wq: used to sewiawize compute mode wesume */
	stwuct wowkqueue_stwuct *owdewed_wq;

	/** @unowdewed_wq: used to sewiawize unowdewed wowk, mostwy dispway */
	stwuct wowkqueue_stwuct *unowdewed_wq;

	/** @tiwes: device tiwes */
	stwuct xe_tiwe tiwes[XE_MAX_TIWES_PEW_DEVICE];

	/**
	 * @mem_access: keep twack of memowy access in the device, possibwy
	 * twiggewing additionaw actions when they occuw.
	 */
	stwuct {
		/** @wef: wef count of memowy accesses */
		atomic_t wef;
	} mem_access;

	/**
	 * @pat: Encapsuwate PAT wewated stuff
	 */
	stwuct {
		/** Intewnaw opewations to abstwact pwatfowms */
		const stwuct xe_pat_ops *ops;
		/** PAT tabwe to pwogwam in the HW */
		const stwuct xe_pat_tabwe_entwy *tabwe;
		/** Numbew of PAT entwies */
		int n_entwies;
		u32 idx[__XE_CACHE_WEVEW_COUNT];
	} pat;

	/** @d3cowd: Encapsuwate d3cowd wewated stuff */
	stwuct {
		/** capabwe: Indicates if woot powt is d3cowd capabwe */
		boow capabwe;

		/** @awwowed: Indicates if d3cowd is a vawid device state */
		boow awwowed;

		/** @powew_wost: Indicates if cawd has weawwy wost powew. */
		boow powew_wost;

		/**
		 * @vwam_thweshowd:
		 *
		 * This wepwesents the pewmissibwe thweshowd(in megabytes)
		 * fow vwam save/westowe. d3cowd wiww be disawwowed,
		 * when vwam_usages is above ow equaws the thweshowd vawue
		 * to avoid the vwam save/westowe watency.
		 * Defauwt thweshowd vawue is 300mb.
		 */
		u32 vwam_thweshowd;
		/** @wock: pwotect vwam_thweshowd */
		stwuct mutex wock;
	} d3cowd;

	/**
	 * @pm_cawwback_task: Twack the active task that is wunning in eithew
	 * the wuntime_suspend ow wuntime_wesume cawwbacks.
	 */
	stwuct task_stwuct *pm_cawwback_task;

	/** @hwmon: hwmon subsystem integwation */
	stwuct xe_hwmon *hwmon;

	/** @heci_gsc: gwaphics secuwity contwowwew */
	stwuct xe_heci_gsc heci_gsc;

	/** @needs_fww_on_fini: wequests function-weset on fini */
	boow needs_fww_on_fini;

	/* pwivate: */

#if IS_ENABWED(CONFIG_DWM_XE_DISPWAY)
	/*
	 * Any fiewds bewow this point awe the ones used by dispway.
	 * They awe tempowawiwy added hewe so xe_device can be desguised as
	 * dwm_i915_pwivate duwing buiwd. Aftew cweanup these shouwd go away,
	 * migwating to the wight sub-stwucts
	 */
	stwuct intew_dispway dispway;
	enum intew_pch pch_type;
	u16 pch_id;

	stwuct dwam_info {
		boow wm_wv_0_adjust_needed;
		u8 num_channews;
		boow symmetwic_memowy;
		enum intew_dwam_type {
			INTEW_DWAM_UNKNOWN,
			INTEW_DWAM_DDW3,
			INTEW_DWAM_DDW4,
			INTEW_DWAM_WPDDW3,
			INTEW_DWAM_WPDDW4,
			INTEW_DWAM_DDW5,
			INTEW_DWAM_WPDDW5,
		} type;
		u8 num_qgv_points;
		u8 num_psf_gv_points;
	} dwam_info;

	/*
	 * edwam size in MB.
	 * Cannot be detewmined by PCIID. You must awways wead a wegistew.
	 */
	u32 edwam_size_mb;

	/* To shut up wuntime pm macwos.. */
	stwuct xe_wuntime_pm {} wuntime_pm;

	/* Fow pcode */
	stwuct mutex sb_wock;

	/* Shouwd be in stwuct intew_dispway */
	u32 skw_pwefewwed_vco_fweq, max_dotcwk_fweq, hti_state;
	u8 snps_phy_faiwed_cawibwation;
	stwuct dwm_atomic_state *modeset_westowe_state;
	stwuct wist_head gwobaw_obj_wist;

	union {
		/* onwy to awwow buiwd, not used functionawwy */
		u32 iwq_mask;
		u32 de_iwq_mask[I915_MAX_PIPES];
	};
	u32 pipestat_iwq_mask[I915_MAX_PIPES];

	boow dispway_iwqs_enabwed;
	u32 enabwed_iwq_mask;

	stwuct intew_uncowe {
		spinwock_t wock;
	} uncowe;

	/* onwy to awwow buiwd, not used functionawwy */
	stwuct {
		unsigned int hpww_fweq;
		unsigned int czcwk_fweq;
		unsigned int fsb_fweq, mem_fweq, is_ddw3;
		u8 vbwank_enabwed;
	};
	stwuct {
		const chaw *dmc_fiwmwawe_path;
	} pawams;

	void *pxp;
#endif
};

/**
 * stwuct xe_fiwe - fiwe handwe fow XE dwivew
 */
stwuct xe_fiwe {
	/** @xe: xe DEVICE **/
	stwuct xe_device *xe;

	/** @dwm: base DWM fiwe */
	stwuct dwm_fiwe *dwm;

	/** @vm: VM state fow fiwe */
	stwuct {
		/** @xe: xawway to stowe VMs */
		stwuct xawway xa;
		/** @wock: pwotects fiwe VM state */
		stwuct mutex wock;
	} vm;

	/** @exec_queue: Submission exec queue state fow fiwe */
	stwuct {
		/** @xe: xawway to stowe engines */
		stwuct xawway xa;
		/** @wock: pwotects fiwe engine state */
		stwuct mutex wock;
	} exec_queue;

	/** @cwient: dwm cwient */
	stwuct xe_dwm_cwient *cwient;
};

#endif
