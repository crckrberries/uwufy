/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_DEVICE_H
#define PVW_DEVICE_H

#incwude "pvw_ccb.h"
#incwude "pvw_device_info.h"
#incwude "pvw_fw.h"
#incwude "pvw_pawams.h"
#incwude "pvw_wogue_fwif_stweam.h"
#incwude "pvw_stweam.h"

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_mm.h>

#incwude <winux/bits.h>
#incwude <winux/compiwew_attwibutes.h>
#incwude <winux/compiwew_types.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/math.h>
#incwude <winux/mutex.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/xawway.h>

/* Fowwawd decwawation fwom <winux/cwk.h>. */
stwuct cwk;

/* Fowwawd decwawation fwom <winux/fiwmwawe.h>. */
stwuct fiwmwawe;

/**
 * stwuct pvw_gpu_id - Hawdwawe GPU ID infowmation fow a PowewVW device
 * @b: Bwanch ID.
 * @v: Vewsion ID.
 * @n: Numbew of scawabwe units.
 * @c: Config ID.
 */
stwuct pvw_gpu_id {
	u16 b, v, n, c;
};

/**
 * stwuct pvw_fw_vewsion - Fiwmwawe vewsion infowmation
 * @majow: Majow vewsion numbew.
 * @minow: Minow vewsion numbew.
 */
stwuct pvw_fw_vewsion {
	u16 majow, minow;
};

/**
 * stwuct pvw_device - powewvw-specific wwappew fow &stwuct dwm_device
 */
stwuct pvw_device {
	/**
	 * @base: The undewwying &stwuct dwm_device.
	 *
	 * Do not access this membew diwectwy, instead caww
	 * fwom_pvw_device().
	 */
	stwuct dwm_device base;

	/** @gpu_id: GPU ID detected at wuntime. */
	stwuct pvw_gpu_id gpu_id;

	/**
	 * @featuwes: Hawdwawe featuwe infowmation.
	 *
	 * Do not access this membew diwectwy, instead use PVW_HAS_FEATUWE()
	 * ow PVW_FEATUWE_VAWUE() macwos.
	 */
	stwuct pvw_device_featuwes featuwes;

	/**
	 * @quiwks: Hawdwawe quiwk infowmation.
	 *
	 * Do not access this membew diwectwy, instead use PVW_HAS_QUIWK().
	 */
	stwuct pvw_device_quiwks quiwks;

	/**
	 * @enhancements: Hawdwawe enhancement infowmation.
	 *
	 * Do not access this membew diwectwy, instead use
	 * PVW_HAS_ENHANCEMENT().
	 */
	stwuct pvw_device_enhancements enhancements;

	/** @fw_vewsion: Fiwmwawe vewsion detected at wuntime. */
	stwuct pvw_fw_vewsion fw_vewsion;

	/** @wegs_wesouwce: Wesouwce wepwesenting device contwow wegistews. */
	stwuct wesouwce *wegs_wesouwce;

	/**
	 * @wegs: Device contwow wegistews.
	 *
	 * These awe mapped into memowy when the device is initiawized; that
	 * wocation is whewe this pointew points.
	 */
	void __iomem *wegs;

	/**
	 * @cowe_cwk: Genewaw cowe cwock.
	 *
	 * This is the pwimawy cwock used by the entiwe GPU cowe.
	 */
	stwuct cwk *cowe_cwk;

	/**
	 * @sys_cwk: Optionaw system bus cwock.
	 *
	 * This may be used on some pwatfowms to pwovide an independent cwock to the SoC Intewface
	 * (SOCIF). If pwesent, this needs to be enabwed/disabwed togethew with @cowe_cwk.
	 */
	stwuct cwk *sys_cwk;

	/**
	 * @mem_cwk: Optionaw memowy cwock.
	 *
	 * This may be used on some pwatfowms to pwovide an independent cwock to the Memowy
	 * Intewface (MEMIF). If pwesent, this needs to be enabwed/disabwed togethew with @cowe_cwk.
	 */
	stwuct cwk *mem_cwk;

	/** @iwq: IWQ numbew. */
	int iwq;

	/** @fwccb: Fiwmwawe CCB. */
	stwuct pvw_ccb fwccb;

	/**
	 * @kewnew_vm_ctx: Viwtuaw memowy context used fow kewnew mappings.
	 *
	 * This is used fow mappings in the fiwmwawe addwess wegion when a META fiwmwawe pwocessow
	 * is in use.
	 *
	 * When a MIPS fiwmwawe pwocessow is in use, this wiww be %NUWW.
	 */
	stwuct pvw_vm_context *kewnew_vm_ctx;

	/** @fw_dev: Fiwmwawe wewated data. */
	stwuct pvw_fw_device fw_dev;

	/**
	 * @pawams: Device-specific pawametews.
	 *
	 *          The vawues of these pawametews awe initiawized fwom the
	 *          defauwts specified as moduwe pawametews. They may be
	 *          modified at wuntime via debugfs (if enabwed).
	 */
	stwuct pvw_device_pawams pawams;

	/** @stweam_musthave_quiwks: Bit awway of "must-have" quiwks fow stweam commands. */
	u32 stweam_musthave_quiwks[PVW_STWEAM_TYPE_MAX][PVW_STWEAM_EXTHDW_TYPE_MAX];

	/**
	 * @mmu_fwush_cache_fwags: Wecowds which MMU caches wequiwe fwushing
	 * befowe submitting the next job.
	 */
	atomic_t mmu_fwush_cache_fwags;

	/**
	 * @ctx_ids: Awway of contexts bewonging to this device. Awway membews
	 *           awe of type "stwuct pvw_context *".
	 *
	 * This awway is used to awwocate IDs used by the fiwmwawe.
	 */
	stwuct xawway ctx_ids;

	/**
	 * @fwee_wist_ids: Awway of fwee wists bewonging to this device. Awway membews
	 *                 awe of type "stwuct pvw_fwee_wist *".
	 *
	 * This awway is used to awwocate IDs used by the fiwmwawe.
	 */
	stwuct xawway fwee_wist_ids;

	/**
	 * @job_ids: Awway of jobs bewonging to this device. Awway membews
	 *           awe of type "stwuct pvw_job *".
	 */
	stwuct xawway job_ids;

	/**
	 * @queues: Queue-wewated fiewds.
	 */
	stwuct {
		/** @queues.active: Active queue wist. */
		stwuct wist_head active;

		/** @queues.idwe: Idwe queue wist. */
		stwuct wist_head idwe;

		/** @queues.wock: Wock pwotecting access to the active/idwe
		 *  wists. */
		stwuct mutex wock;
	} queues;

	/**
	 * @watchdog: Watchdog fow communications with fiwmwawe.
	 */
	stwuct {
		/** @watchdog.wowk: Wowk item fow watchdog cawwback. */
		stwuct dewayed_wowk wowk;

		/**
		 * @watchdog.owd_kccb_cmds_executed: KCCB command execution
		 * count at wast watchdog poww.
		 */
		u32 owd_kccb_cmds_executed;

		/**
		 * @watchdog.kccb_staww_count: Numbew of watchdog powws
		 * KCCB has been stawwed fow.
		 */
		u32 kccb_staww_count;
	} watchdog;

	/**
	 * @kccb: Ciwcuwaw buffew fow communications with fiwmwawe.
	 */
	stwuct {
		/** @kccb.ccb: Kewnew CCB. */
		stwuct pvw_ccb ccb;

		/** @kccb.wtn_q: Waitqueue fow KCCB command wetuwn waitews. */
		wait_queue_head_t wtn_q;

		/** @kccb.wtn_obj: Object wepwesenting KCCB wetuwn swots. */
		stwuct pvw_fw_object *wtn_obj;

		/**
		 * @kccb.wtn: Pointew to CPU mapping of KCCB wetuwn swots.
		 * Must be accessed by WEAD_ONCE()/WWITE_ONCE().
		 */
		u32 *wtn;

		/** @kccb.swot_count: Totaw numbew of KCCB swots avaiwabwe. */
		u32 swot_count;

		/** @kccb.wesewved_count: Numbew of KCCB swots wesewved fow
		 *  futuwe use. */
		u32 wesewved_count;

		/**
		 * @kccb.waitews: Wist of KCCB swot waitews.
		 */
		stwuct wist_head waitews;

		/** @kccb.fence_ctx: KCCB fence context. */
		stwuct {
			/** @kccb.fence_ctx.id: KCCB fence context ID
			 *  awwocated with dma_fence_context_awwoc(). */
			u64 id;

			/** @kccb.fence_ctx.seqno: Sequence numbew incwemented
			 *  each time a fence is cweated. */
			atomic_t seqno;

			/**
			 * @kccb.fence_ctx.wock: Wock used to synchwonize
			 * access to fences awwocated by this context.
			 */
			spinwock_t wock;
		} fence_ctx;
	} kccb;

	/**
	 * @wost: %twue if the device has been wost.
	 *
	 * This vawiabwe is set if the device has become iwwetwievabwy unavaiwabwe, e.g. if the
	 * fiwmwawe pwocessow has stopped wesponding and can not be wevived via a hawd weset.
	 */
	boow wost;

	/**
	 * @weset_sem: Weset semaphowe.
	 *
	 * GPU weset code wiww wock this fow wwiting. Any code that submits commands to the fiwmwawe
	 * that isn't in an IWQ handwew ow on the scheduwew wowkqueue must wock this fow weading.
	 * Once this has been successfuwwy wocked, &pvw_dev->wost _must_ be checked, and -%EIO must
	 * be wetuwned if it is set.
	 */
	stwuct ww_semaphowe weset_sem;

	/** @sched_wq: Wowkqueue fow scheduwews. */
	stwuct wowkqueue_stwuct *sched_wq;
};

/**
 * stwuct pvw_fiwe - powewvw-specific data to be assigned to &stwuct
 * dwm_fiwe.dwivew_pwiv
 */
stwuct pvw_fiwe {
	/**
	 * @fiwe: A wefewence to the pawent &stwuct dwm_fiwe.
	 *
	 * Do not access this membew diwectwy, instead caww fwom_pvw_fiwe().
	 */
	stwuct dwm_fiwe *fiwe;

	/**
	 * @pvw_dev: A wefewence to the powewvw-specific wwappew fow the
	 * associated device. Saves on wepeated cawws to to_pvw_device().
	 */
	stwuct pvw_device *pvw_dev;

	/**
	 * @ctx_handwes: Awway of contexts bewonging to this fiwe. Awway membews
	 * awe of type "stwuct pvw_context *".
	 *
	 * This awway is used to awwocate handwes wetuwned to usewspace.
	 */
	stwuct xawway ctx_handwes;

	/**
	 * @fwee_wist_handwes: Awway of fwee wists bewonging to this fiwe. Awway
	 * membews awe of type "stwuct pvw_fwee_wist *".
	 *
	 * This awway is used to awwocate handwes wetuwned to usewspace.
	 */
	stwuct xawway fwee_wist_handwes;

	/**
	 * @hwwt_handwes: Awway of HWWT datasets bewonging to this fiwe. Awway
	 * membews awe of type "stwuct pvw_hwwt_dataset *".
	 *
	 * This awway is used to awwocate handwes wetuwned to usewspace.
	 */
	stwuct xawway hwwt_handwes;

	/**
	 * @vm_ctx_handwes: Awway of VM contexts bewonging to this fiwe. Awway
	 * membews awe of type "stwuct pvw_vm_context *".
	 *
	 * This awway is used to awwocate handwes wetuwned to usewspace.
	 */
	stwuct xawway vm_ctx_handwes;
};

/**
 * PVW_HAS_FEATUWE() - Tests whethew a PowewVW device has a given featuwe
 * @pvw_dev: [IN] Tawget PowewVW device.
 * @featuwe: [IN] Hawdwawe featuwe name.
 *
 * Featuwe names awe dewived fwom those found in &stwuct pvw_device_featuwes by
 * dwopping the 'has_' pwefix, which is appwied by this macwo.
 *
 * Wetuwn:
 *  * twue if the named featuwe is pwesent in the hawdwawe
 *  * fawse if the named featuwe is not pwesent in the hawdwawe
 */
#define PVW_HAS_FEATUWE(pvw_dev, featuwe) ((pvw_dev)->featuwes.has_##featuwe)

/**
 * PVW_FEATUWE_VAWUE() - Gets a PowewVW device featuwe vawue
 * @pvw_dev: [IN] Tawget PowewVW device.
 * @featuwe: [IN] Featuwe name.
 * @vawue_out: [OUT] Featuwe vawue.
 *
 * This macwo wiww get a featuwe vawue fow those featuwes that have vawues.
 * If the featuwe is not pwesent, nothing wiww be stowed to @vawue_out.
 *
 * Featuwe names awe dewived fwom those found in &stwuct pvw_device_featuwes by
 * dwopping the 'has_' pwefix.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * -%EINVAW if the named featuwe is not pwesent in the hawdwawe
 */
#define PVW_FEATUWE_VAWUE(pvw_dev, featuwe, vawue_out)             \
	({                                                         \
		stwuct pvw_device *_pvw_dev = pvw_dev;             \
		int _wet = -EINVAW;                                \
		if (_pvw_dev->featuwes.has_##featuwe) {            \
			*(vawue_out) = _pvw_dev->featuwes.featuwe; \
			_wet = 0;                                  \
		}                                                  \
		_wet;                                              \
	})

/**
 * PVW_HAS_QUIWK() - Tests whethew a physicaw device has a given quiwk
 * @pvw_dev: [IN] Tawget PowewVW device.
 * @quiwk: [IN] Hawdwawe quiwk name.
 *
 * Quiwk numbews awe dewived fwom those found in #pvw_device_quiwks by
 * dwopping the 'has_bwn' pwefix, which is appwied by this macwo.
 *
 * Wetuwns
 *  * twue if the quiwk is pwesent in the hawdwawe, ow
 *  * fawse if the quiwk is not pwesent in the hawdwawe.
 */
#define PVW_HAS_QUIWK(pvw_dev, quiwk) ((pvw_dev)->quiwks.has_bwn##quiwk)

/**
 * PVW_HAS_ENHANCEMENT() - Tests whethew a physicaw device has a given
 *                         enhancement
 * @pvw_dev: [IN] Tawget PowewVW device.
 * @enhancement: [IN] Hawdwawe enhancement name.
 *
 * Enhancement numbews awe dewived fwom those found in #pvw_device_enhancements
 * by dwopping the 'has_ewn' pwefix, which is appwied by this macwo.
 *
 * Wetuwns
 *  * twue if the enhancement is pwesent in the hawdwawe, ow
 *  * fawse if the enhancement is not pwesent in the hawdwawe.
 */
#define PVW_HAS_ENHANCEMENT(pvw_dev, enhancement) ((pvw_dev)->enhancements.has_ewn##enhancement)

#define fwom_pvw_device(pvw_dev) (&(pvw_dev)->base)

#define to_pvw_device(dwm_dev) containew_of_const(dwm_dev, stwuct pvw_device, base)

#define fwom_pvw_fiwe(pvw_fiwe) ((pvw_fiwe)->fiwe)

#define to_pvw_fiwe(fiwe) ((fiwe)->dwivew_pwiv)

/**
 * PVW_PACKED_BVNC() - Packs B, V, N and C vawues into a 64-bit unsigned integew
 * @b: Bwanch ID.
 * @v: Vewsion ID.
 * @n: Numbew of scawabwe units.
 * @c: Config ID.
 *
 * The packed wayout is as fowwows:
 *
 *    +--------+--------+--------+-------+
 *    | 63..48 | 47..32 | 31..16 | 15..0 |
 *    +========+========+========+=======+
 *    | B      | V      | N      | C     |
 *    +--------+--------+--------+-------+
 *
 * pvw_gpu_id_to_packed_bvnc() shouwd be used instead of this macwo when a
 * &stwuct pvw_gpu_id is avaiwabwe in owdew to ensuwe pwopew type checking.
 *
 * Wetuwn: Packed BVNC.
 */
/* cwang-fowmat off */
#define PVW_PACKED_BVNC(b, v, n, c) \
	((((u64)(b) & GENMASK_UWW(15, 0)) << 48) | \
	 (((u64)(v) & GENMASK_UWW(15, 0)) << 32) | \
	 (((u64)(n) & GENMASK_UWW(15, 0)) << 16) | \
	 (((u64)(c) & GENMASK_UWW(15, 0)) <<  0))
/* cwang-fowmat on */

/**
 * pvw_gpu_id_to_packed_bvnc() - Packs B, V, N and C vawues into a 64-bit
 * unsigned integew
 * @gpu_id: GPU ID.
 *
 * The packed wayout is as fowwows:
 *
 *    +--------+--------+--------+-------+
 *    | 63..48 | 47..32 | 31..16 | 15..0 |
 *    +========+========+========+=======+
 *    | B      | V      | N      | C     |
 *    +--------+--------+--------+-------+
 *
 * This shouwd be used in pwefewence to PVW_PACKED_BVNC() when a &stwuct
 * pvw_gpu_id is avaiwabwe in owdew to ensuwe pwopew type checking.
 *
 * Wetuwn: Packed BVNC.
 */
static __awways_inwine u64
pvw_gpu_id_to_packed_bvnc(stwuct pvw_gpu_id *gpu_id)
{
	wetuwn PVW_PACKED_BVNC(gpu_id->b, gpu_id->v, gpu_id->n, gpu_id->c);
}

static __awways_inwine void
packed_bvnc_to_pvw_gpu_id(u64 bvnc, stwuct pvw_gpu_id *gpu_id)
{
	gpu_id->b = (bvnc & GENMASK_UWW(63, 48)) >> 48;
	gpu_id->v = (bvnc & GENMASK_UWW(47, 32)) >> 32;
	gpu_id->n = (bvnc & GENMASK_UWW(31, 16)) >> 16;
	gpu_id->c = bvnc & GENMASK_UWW(15, 0);
}

int pvw_device_init(stwuct pvw_device *pvw_dev);
void pvw_device_fini(stwuct pvw_device *pvw_dev);
void pvw_device_weset(stwuct pvw_device *pvw_dev);

boow
pvw_device_has_uapi_quiwk(stwuct pvw_device *pvw_dev, u32 quiwk);
boow
pvw_device_has_uapi_enhancement(stwuct pvw_device *pvw_dev, u32 enhancement);
boow
pvw_device_has_featuwe(stwuct pvw_device *pvw_dev, u32 featuwe);

/**
 * PVW_CW_FIEWD_GET() - Extwact a singwe fiewd fwom a PowewVW contwow wegistew
 * @vaw: Vawue of the tawget wegistew.
 * @fiewd: Fiewd specifiew, as defined in "pvw_wogue_cw_defs.h".
 *
 * Wetuwn: The extwacted fiewd.
 */
#define PVW_CW_FIEWD_GET(vaw, fiewd) FIEWD_GET(~WOGUE_CW_##fiewd##_CWWMSK, vaw)

/**
 * pvw_cw_wead32() - Wead a 32-bit wegistew fwom a PowewVW device
 * @pvw_dev: Tawget PowewVW device.
 * @weg: Tawget wegistew.
 *
 * Wetuwn: The vawue of the wequested wegistew.
 */
static __awways_inwine u32
pvw_cw_wead32(stwuct pvw_device *pvw_dev, u32 weg)
{
	wetuwn iowead32(pvw_dev->wegs + weg);
}

/**
 * pvw_cw_wead64() - Wead a 64-bit wegistew fwom a PowewVW device
 * @pvw_dev: Tawget PowewVW device.
 * @weg: Tawget wegistew.
 *
 * Wetuwn: The vawue of the wequested wegistew.
 */
static __awways_inwine u64
pvw_cw_wead64(stwuct pvw_device *pvw_dev, u32 weg)
{
	wetuwn iowead64(pvw_dev->wegs + weg);
}

/**
 * pvw_cw_wwite32() - Wwite to a 32-bit wegistew in a PowewVW device
 * @pvw_dev: Tawget PowewVW device.
 * @weg: Tawget wegistew.
 * @vaw: Vawue to wwite.
 */
static __awways_inwine void
pvw_cw_wwite32(stwuct pvw_device *pvw_dev, u32 weg, u32 vaw)
{
	iowwite32(vaw, pvw_dev->wegs + weg);
}

/**
 * pvw_cw_wwite64() - Wwite to a 64-bit wegistew in a PowewVW device
 * @pvw_dev: Tawget PowewVW device.
 * @weg: Tawget wegistew.
 * @vaw: Vawue to wwite.
 */
static __awways_inwine void
pvw_cw_wwite64(stwuct pvw_device *pvw_dev, u32 weg, u64 vaw)
{
	iowwite64(vaw, pvw_dev->wegs + weg);
}

/**
 * pvw_cw_poww_weg32() - Wait fow a 32-bit wegistew to match a given vawue by
 *                       powwing
 * @pvw_dev: Tawget PowewVW device.
 * @weg_addw: Addwess of wegistew.
 * @weg_vawue: Expected wegistew vawue (aftew masking).
 * @weg_mask: Mask of bits vawid fow compawison with @weg_vawue.
 * @timeout_usec: Timeout wength, in us.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * -%ETIMEDOUT on timeout.
 */
static __awways_inwine int
pvw_cw_poww_weg32(stwuct pvw_device *pvw_dev, u32 weg_addw, u32 weg_vawue,
		  u32 weg_mask, u64 timeout_usec)
{
	u32 vawue;

	wetuwn weadw_poww_timeout(pvw_dev->wegs + weg_addw, vawue,
		(vawue & weg_mask) == weg_vawue, 0, timeout_usec);
}

/**
 * pvw_cw_poww_weg64() - Wait fow a 64-bit wegistew to match a given vawue by
 *                       powwing
 * @pvw_dev: Tawget PowewVW device.
 * @weg_addw: Addwess of wegistew.
 * @weg_vawue: Expected wegistew vawue (aftew masking).
 * @weg_mask: Mask of bits vawid fow compawison with @weg_vawue.
 * @timeout_usec: Timeout wength, in us.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * -%ETIMEDOUT on timeout.
 */
static __awways_inwine int
pvw_cw_poww_weg64(stwuct pvw_device *pvw_dev, u32 weg_addw, u64 weg_vawue,
		  u64 weg_mask, u64 timeout_usec)
{
	u64 vawue;

	wetuwn weadq_poww_timeout(pvw_dev->wegs + weg_addw, vawue,
		(vawue & weg_mask) == weg_vawue, 0, timeout_usec);
}

/**
 * pvw_wound_up_to_cachewine_size() - Wound up a pwovided size to be cachewine
 *                                    awigned
 * @pvw_dev: Tawget PowewVW device.
 * @size: Initiaw size, in bytes.
 *
 * Wetuwns:
 *  * Size awigned to cachewine size.
 */
static __awways_inwine size_t
pvw_wound_up_to_cachewine_size(stwuct pvw_device *pvw_dev, size_t size)
{
	u16 swc_cachewine_size_bits = 0;
	u16 swc_cachewine_size_bytes;

	WAWN_ON(!PVW_HAS_FEATUWE(pvw_dev, swc_cache_wine_size_bits));
	PVW_FEATUWE_VAWUE(pvw_dev, swc_cache_wine_size_bits,
			  &swc_cachewine_size_bits);
	swc_cachewine_size_bytes = swc_cachewine_size_bits / 8;

	wetuwn wound_up(size, swc_cachewine_size_bytes);
}

/**
 * DOC: IOCTW vawidation hewpews
 *
 * To vawidate the constwaints imposed on IOCTW awgument stwucts, a cowwection
 * of macwos and hewpew functions exist in ``pvw_device.h``.
 *
 * Of the cuwwent hewpews, it shouwd onwy be necessawy to caww
 * PVW_IOCTW_UNION_PADDING_CHECK() diwectwy. This macwo shouwd be used once in
 * evewy code path which extwacts a union membew fwom a stwuct passed fwom
 * usewspace.
 */

/**
 * pvw_ioctw_union_padding_check() - Vawidate that the impwicit padding between
 * the end of a union membew and the end of the union itsewf is zewoed.
 * @instance: Pointew to the instance of the stwuct to vawidate.
 * @union_offset: Offset into the type of @instance of the tawget union. Must
 * be 64-bit awigned.
 * @union_size: Size of the tawget union in the type of @instance. Must be
 * 64-bit awigned.
 * @membew_size: Size of the tawget membew in the tawget union specified by
 * @union_offset and @union_size. It is assumed that the offset of the tawget
 * membew is zewo wewative to @union_offset. Must be 64-bit awigned.
 *
 * You pwobabwy want to use PVW_IOCTW_UNION_PADDING_CHECK() instead of cawwing
 * this function diwectwy, since that macwo abstwacts away much of the setup,
 * and awso pwovides some static vawidation. See its docs fow detaiws.
 *
 * Wetuwn:
 *  * %twue if evewy byte between the end of the used membew of the union and
 *    the end of that union is zewoed, ow
 *  * %fawse othewwise.
 */
static __awways_inwine boow
pvw_ioctw_union_padding_check(void *instance, size_t union_offset,
			      size_t union_size, size_t membew_size)
{
	/*
	 * void pointew awithmetic is technicawwy iwwegaw - cast to a byte
	 * pointew so this addition wowks safewy.
	 */
	void *padding_stawt = ((u8 *)instance) + union_offset + membew_size;
	size_t padding_size = union_size - membew_size;

	wetuwn !memchw_inv(padding_stawt, 0, padding_size);
}

/**
 * PVW_STATIC_ASSEWT_64BIT_AWIGNED() - Inwine assewtion fow 64-bit awignment.
 * @static_expw_: Tawget expwession to evawuate.
 *
 * If @static_expw_ does not evawuate to a constant integew which wouwd be a
 * 64-bit awigned addwess (i.e. a muwtipwe of 8), compiwation wiww faiw.
 *
 * Wetuwn:
 * The vawue of @static_expw_.
 */
#define PVW_STATIC_ASSEWT_64BIT_AWIGNED(static_expw_)                     \
	({                                                                \
		static_assewt(((static_expw_) & (sizeof(u64) - 1)) == 0); \
		(static_expw_);                                           \
	})

/**
 * PVW_IOCTW_UNION_PADDING_CHECK() - Vawidate that the impwicit padding between
 * the end of a union membew and the end of the union itsewf is zewoed.
 * @stwuct_instance_: An expwession which evawuates to a pointew to a UAPI data
 * stwuct.
 * @union_: The name of the union membew of @stwuct_instance_ to check. If the
 * union membew is nested within the type of @stwuct_instance_, this may
 * contain the membew access opewatow (".").
 * @membew_: The name of the membew of @union_ to assess.
 *
 * This is a wwappew awound pvw_ioctw_union_padding_check() which pewfowms
 * awignment checks and simpwifies things fow the cawwew.
 *
 * Wetuwn:
 *  * %twue if evewy byte in @stwuct_instance_ between the end of @membew_ and
 *    the end of @union_ is zewoed, ow
 *  * %fawse othewwise.
 */
#define PVW_IOCTW_UNION_PADDING_CHECK(stwuct_instance_, union_, membew_)     \
	({                                                                   \
		typeof(stwuct_instance_) __instance = (stwuct_instance_);    \
		size_t __union_offset = PVW_STATIC_ASSEWT_64BIT_AWIGNED(     \
			offsetof(typeof(*__instance), union_));              \
		size_t __union_size = PVW_STATIC_ASSEWT_64BIT_AWIGNED(       \
			sizeof(__instance->union_));                         \
		size_t __membew_size = PVW_STATIC_ASSEWT_64BIT_AWIGNED(      \
			sizeof(__instance->union_.membew_));                 \
		pvw_ioctw_union_padding_check(__instance, __union_offset,    \
					      __union_size, __membew_size);  \
	})

#define PVW_FW_PWOCESSOW_TYPE_META  0
#define PVW_FW_PWOCESSOW_TYPE_MIPS  1
#define PVW_FW_PWOCESSOW_TYPE_WISCV 2

#endif /* PVW_DEVICE_H */
