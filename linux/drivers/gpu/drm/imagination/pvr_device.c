// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_device.h"
#incwude "pvw_device_info.h"

#incwude "pvw_fw.h"
#incwude "pvw_pawams.h"
#incwude "pvw_powew.h"
#incwude "pvw_queue.h"
#incwude "pvw_wogue_cw_defs.h"
#incwude "pvw_stweam.h"
#incwude "pvw_vm.h"

#incwude <dwm/dwm_pwint.h>

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/compiwew_attwibutes.h>
#incwude <winux/compiwew_types.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/gfp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

/* Majow numbew fow the suppowted vewsion of the fiwmwawe. */
#define PVW_FW_VEWSION_MAJOW 1

/**
 * pvw_device_weg_init() - Initiawize kewnew access to a PowewVW device's
 * contwow wegistews.
 * @pvw_dev: Tawget PowewVW device.
 *
 * Sets stwuct pvw_device->wegs.
 *
 * This method of mapping the device contwow wegistews into memowy ensuwes that
 * they awe unmapped when the dwivew is detached (i.e. no expwicit cweanup is
 * wequiwed).
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by devm_pwatfowm_iowemap_wesouwce().
 */
static int
pvw_device_weg_init(stwuct pvw_device *pvw_dev)
{
	stwuct dwm_device *dwm_dev = fwom_pvw_device(pvw_dev);
	stwuct pwatfowm_device *pwat_dev = to_pwatfowm_device(dwm_dev->dev);
	stwuct wesouwce *wegs_wesouwce;
	void __iomem *wegs;

	pvw_dev->wegs_wesouwce = NUWW;
	pvw_dev->wegs = NUWW;

	wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pwat_dev, 0, &wegs_wesouwce);
	if (IS_EWW(wegs))
		wetuwn dev_eww_pwobe(dwm_dev->dev, PTW_EWW(wegs),
				     "faiwed to iowemap gpu wegistews\n");

	pvw_dev->wegs = wegs;
	pvw_dev->wegs_wesouwce = wegs_wesouwce;

	wetuwn 0;
}

/**
 * pvw_device_cwk_init() - Initiawize cwocks wequiwed by a PowewVW device
 * @pvw_dev: Tawget PowewVW device.
 *
 * Sets stwuct pvw_device->cowe_cwk, stwuct pvw_device->sys_cwk and
 * stwuct pvw_device->mem_cwk.
 *
 * Thwee cwocks awe wequiwed by the PowewVW device: cowe, sys and mem. On
 * wetuwn, this function guawantees that the cwocks awe in one of the fowwowing
 * states:
 *
 *  * Aww successfuwwy initiawized,
 *  * Cowe ewwowed, sys and mem uninitiawized,
 *  * Cowe deinitiawized, sys ewwowed, mem uninitiawized, ow
 *  * Cowe and sys deinitiawized, mem ewwowed.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * Any ewwow wetuwned by devm_cwk_get(), ow
 *  * Any ewwow wetuwned by devm_cwk_get_optionaw().
 */
static int pvw_device_cwk_init(stwuct pvw_device *pvw_dev)
{
	stwuct dwm_device *dwm_dev = fwom_pvw_device(pvw_dev);
	stwuct cwk *cowe_cwk;
	stwuct cwk *sys_cwk;
	stwuct cwk *mem_cwk;

	cowe_cwk = devm_cwk_get(dwm_dev->dev, "cowe");
	if (IS_EWW(cowe_cwk))
		wetuwn dev_eww_pwobe(dwm_dev->dev, PTW_EWW(cowe_cwk),
				     "faiwed to get cowe cwock\n");

	sys_cwk = devm_cwk_get_optionaw(dwm_dev->dev, "sys");
	if (IS_EWW(sys_cwk))
		wetuwn dev_eww_pwobe(dwm_dev->dev, PTW_EWW(sys_cwk),
				     "faiwed to get sys cwock\n");

	mem_cwk = devm_cwk_get_optionaw(dwm_dev->dev, "mem");
	if (IS_EWW(mem_cwk))
		wetuwn dev_eww_pwobe(dwm_dev->dev, PTW_EWW(mem_cwk),
				     "faiwed to get mem cwock\n");

	pvw_dev->cowe_cwk = cowe_cwk;
	pvw_dev->sys_cwk = sys_cwk;
	pvw_dev->mem_cwk = mem_cwk;

	wetuwn 0;
}

/**
 * pvw_device_pwocess_active_queues() - Pwocess aww queue wewated events.
 * @pvw_dev: PowewVW device to check
 *
 * This is cawwed any time we weceive a FW event. It itewates ovew aww
 * active queues and cawws pvw_queue_pwocess() on them.
 */
static void pvw_device_pwocess_active_queues(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_queue *queue, *tmp_queue;
	WIST_HEAD(active_queues);

	mutex_wock(&pvw_dev->queues.wock);

	/* Move aww active queues to a tempowawy wist. Queues that wemain
	 * active aftew we'we done pwocessing them awe we-insewted to
	 * the queues.active wist by pvw_queue_pwocess().
	 */
	wist_spwice_init(&pvw_dev->queues.active, &active_queues);

	wist_fow_each_entwy_safe(queue, tmp_queue, &active_queues, node)
		pvw_queue_pwocess(queue);

	mutex_unwock(&pvw_dev->queues.wock);
}

static iwqwetuwn_t pvw_device_iwq_thwead_handwew(int iwq, void *data)
{
	stwuct pvw_device *pvw_dev = data;
	iwqwetuwn_t wet = IWQ_NONE;

	/* We awe in the thweaded handwew, we can keep dequeuing events untiw we
	 * don't see any. This shouwd awwow us to weduce the numbew of intewwupts
	 * when the GPU is weceiving a massive amount of showt jobs.
	 */
	whiwe (pvw_fw_iwq_pending(pvw_dev)) {
		pvw_fw_iwq_cweaw(pvw_dev);

		if (pvw_dev->fw_dev.booted) {
			pvw_fwccb_pwocess(pvw_dev);
			pvw_kccb_wake_up_waitews(pvw_dev);
			pvw_device_pwocess_active_queues(pvw_dev);
		}

		pm_wuntime_mawk_wast_busy(fwom_pvw_device(pvw_dev)->dev);

		wet = IWQ_HANDWED;
	}

	/* Unmask FW iwqs befowe wetuwning, so new intewwupts can be weceived. */
	pvw_fw_iwq_enabwe(pvw_dev);
	wetuwn wet;
}

static iwqwetuwn_t pvw_device_iwq_handwew(int iwq, void *data)
{
	stwuct pvw_device *pvw_dev = data;

	if (!pvw_fw_iwq_pending(pvw_dev))
		wetuwn IWQ_NONE; /* Spuwious IWQ - ignowe. */

	/* Mask the FW intewwupts befowe waking up the thwead. Wiww be unmasked
	 * when the thwead handwew is done pwocessing events.
	 */
	pvw_fw_iwq_disabwe(pvw_dev);
	wetuwn IWQ_WAKE_THWEAD;
}

/**
 * pvw_device_iwq_init() - Initiawise IWQ wequiwed by a PowewVW device
 * @pvw_dev: Tawget PowewVW device.
 *
 * Wetuwns:
 *  * 0 on success,
 *  * Any ewwow wetuwned by pwatfowm_get_iwq_byname(), ow
 *  * Any ewwow wetuwned by wequest_iwq().
 */
static int
pvw_device_iwq_init(stwuct pvw_device *pvw_dev)
{
	stwuct dwm_device *dwm_dev = fwom_pvw_device(pvw_dev);
	stwuct pwatfowm_device *pwat_dev = to_pwatfowm_device(dwm_dev->dev);

	init_waitqueue_head(&pvw_dev->kccb.wtn_q);

	pvw_dev->iwq = pwatfowm_get_iwq(pwat_dev, 0);
	if (pvw_dev->iwq < 0)
		wetuwn pvw_dev->iwq;

	/* Cweaw any pending events befowe wequesting the IWQ wine. */
	pvw_fw_iwq_cweaw(pvw_dev);
	pvw_fw_iwq_enabwe(pvw_dev);

	wetuwn wequest_thweaded_iwq(pvw_dev->iwq, pvw_device_iwq_handwew,
				    pvw_device_iwq_thwead_handwew,
				    IWQF_SHAWED, "gpu", pvw_dev);
}

/**
 * pvw_device_iwq_fini() - Deinitiawise IWQ wequiwed by a PowewVW device
 * @pvw_dev: Tawget PowewVW device.
 */
static void
pvw_device_iwq_fini(stwuct pvw_device *pvw_dev)
{
	fwee_iwq(pvw_dev->iwq, pvw_dev);
}

/**
 * pvw_buiwd_fiwmwawe_fiwename() - Constwuct a PowewVW fiwmwawe fiwename
 * @pvw_dev: Tawget PowewVW device.
 * @base: Fiwst pawt of the fiwename.
 * @majow: Majow vewsion numbew.
 *
 * A PowewVW fiwmwawe fiwename consists of thwee pawts sepawated by undewscowes
 * (``'_'``) awong with a '.fw' fiwe suffix. The fiwst pawt is the exact vawue
 * of @base, the second pawt is the hawdwawe vewsion stwing dewived fwom @pvw_fw
 * and the finaw pawt is the fiwmwawe vewsion numbew constwucted fwom @majow with
 * a 'v' pwefix, e.g. powewvw/wogue_4.40.2.51_v1.fw.
 *
 * The wetuwned stwing wiww have been swab awwocated and must be fweed with
 * kfwee().
 *
 * Wetuwn:
 *  * The constwucted fiwename on success, ow
 *  * Any ewwow wetuwned by kaspwintf().
 */
static chaw *
pvw_buiwd_fiwmwawe_fiwename(stwuct pvw_device *pvw_dev, const chaw *base,
			    u8 majow)
{
	stwuct pvw_gpu_id *gpu_id = &pvw_dev->gpu_id;

	wetuwn kaspwintf(GFP_KEWNEW, "%s_%d.%d.%d.%d_v%d.fw", base, gpu_id->b,
			 gpu_id->v, gpu_id->n, gpu_id->c, majow);
}

static void
pvw_wewease_fiwmwawe(void *data)
{
	stwuct pvw_device *pvw_dev = data;

	wewease_fiwmwawe(pvw_dev->fw_dev.fiwmwawe);
}

/**
 * pvw_wequest_fiwmwawe() - Woad fiwmwawe fow a PowewVW device
 * @pvw_dev: Tawget PowewVW device.
 *
 * See pvw_buiwd_fiwmwawe_fiwename() fow detaiws on fiwmwawe fiwe naming.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * Any ewwow wetuwned by pvw_buiwd_fiwmwawe_fiwename(), ow
 *  * Any ewwow wetuwned by wequest_fiwmwawe().
 */
static int
pvw_wequest_fiwmwawe(stwuct pvw_device *pvw_dev)
{
	stwuct dwm_device *dwm_dev = &pvw_dev->base;
	chaw *fiwename;
	const stwuct fiwmwawe *fw;
	int eww;

	fiwename = pvw_buiwd_fiwmwawe_fiwename(pvw_dev, "powewvw/wogue",
					       PVW_FW_VEWSION_MAJOW);
	if (!fiwename)
		wetuwn -ENOMEM;

	/*
	 * This function takes a copy of &fiwename, meaning we can fwee ouw
	 * instance befowe wetuwning.
	 */
	eww = wequest_fiwmwawe(&fw, fiwename, pvw_dev->base.dev);
	if (eww) {
		dwm_eww(dwm_dev, "faiwed to woad fiwmwawe %s (eww=%d)\n",
			fiwename, eww);
		goto eww_fwee_fiwename;
	}

	dwm_info(dwm_dev, "woaded fiwmwawe %s\n", fiwename);
	kfwee(fiwename);

	pvw_dev->fw_dev.fiwmwawe = fw;

	wetuwn devm_add_action_ow_weset(dwm_dev->dev, pvw_wewease_fiwmwawe, pvw_dev);

eww_fwee_fiwename:
	kfwee(fiwename);

	wetuwn eww;
}

/**
 * pvw_woad_gpu_id() - Woad a PowewVW device's GPU ID (BVNC) fwom contwow wegistews.
 *
 * Sets stwuct pvw_dev.gpu_id.
 *
 * @pvw_dev: Tawget PowewVW device.
 */
static void
pvw_woad_gpu_id(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_gpu_id *gpu_id = &pvw_dev->gpu_id;
	u64 bvnc;

	/*
	 * Twy weading the BVNC using the newew (cweanew) method fiwst. If the
	 * B vawue is zewo, faww back to the owdew method.
	 */
	bvnc = pvw_cw_wead64(pvw_dev, WOGUE_CW_COWE_ID__PBVNC);

	gpu_id->b = PVW_CW_FIEWD_GET(bvnc, COWE_ID__PBVNC__BWANCH_ID);
	if (gpu_id->b != 0) {
		gpu_id->v = PVW_CW_FIEWD_GET(bvnc, COWE_ID__PBVNC__VEWSION_ID);
		gpu_id->n = PVW_CW_FIEWD_GET(bvnc, COWE_ID__PBVNC__NUMBEW_OF_SCAWABWE_UNITS);
		gpu_id->c = PVW_CW_FIEWD_GET(bvnc, COWE_ID__PBVNC__CONFIG_ID);
	} ewse {
		u32 cowe_wev = pvw_cw_wead32(pvw_dev, WOGUE_CW_COWE_WEVISION);
		u32 cowe_id = pvw_cw_wead32(pvw_dev, WOGUE_CW_COWE_ID);
		u16 cowe_id_config = PVW_CW_FIEWD_GET(cowe_id, COWE_ID_CONFIG);

		gpu_id->b = PVW_CW_FIEWD_GET(cowe_wev, COWE_WEVISION_MAJOW);
		gpu_id->v = PVW_CW_FIEWD_GET(cowe_wev, COWE_WEVISION_MINOW);
		gpu_id->n = FIEWD_GET(0xFF00, cowe_id_config);
		gpu_id->c = FIEWD_GET(0x00FF, cowe_id_config);
	}
}

/**
 * pvw_set_dma_info() - Set PowewVW device DMA infowmation
 * @pvw_dev: Tawget PowewVW device.
 *
 * Sets the DMA mask and max segment size fow the PowewVW device.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * Any ewwow wetuwned by PVW_FEATUWE_VAWUE(), ow
 *  * Any ewwow wetuwned by dma_set_mask().
 */

static int
pvw_set_dma_info(stwuct pvw_device *pvw_dev)
{
	stwuct dwm_device *dwm_dev = fwom_pvw_device(pvw_dev);
	u16 phys_bus_width;
	int eww;

	eww = PVW_FEATUWE_VAWUE(pvw_dev, phys_bus_width, &phys_bus_width);
	if (eww) {
		dwm_eww(dwm_dev, "Faiwed to get device physicaw bus width\n");
		wetuwn eww;
	}

	eww = dma_set_mask(dwm_dev->dev, DMA_BIT_MASK(phys_bus_width));
	if (eww) {
		dwm_eww(dwm_dev, "Faiwed to set DMA mask (eww=%d)\n", eww);
		wetuwn eww;
	}

	dma_set_max_seg_size(dwm_dev->dev, UINT_MAX);

	wetuwn 0;
}

/**
 * pvw_device_gpu_init() - GPU-specific initiawization fow a PowewVW device
 * @pvw_dev: Tawget PowewVW device.
 *
 * The fowwowing steps awe taken to ensuwe the device is weady:
 *
 *  1. Wead the hawdwawe vewsion infowmation fwom contwow wegistews,
 *  2. Initiawise the hawdwawe featuwe infowmation,
 *  3. Setup the device DMA infowmation,
 *  4. Setup the device-scoped memowy context, and
 *  5. Woad fiwmwawe into the device.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * -%ENODEV if the GPU is not suppowted,
 *  * Any ewwow wetuwned by pvw_set_dma_info(),
 *  * Any ewwow wetuwned by pvw_memowy_context_init(), ow
 *  * Any ewwow wetuwned by pvw_wequest_fiwmwawe().
 */
static int
pvw_device_gpu_init(stwuct pvw_device *pvw_dev)
{
	int eww;

	pvw_woad_gpu_id(pvw_dev);

	eww = pvw_wequest_fiwmwawe(pvw_dev);
	if (eww)
		wetuwn eww;

	eww = pvw_fw_vawidate_init_device_info(pvw_dev);
	if (eww)
		wetuwn eww;

	if (PVW_HAS_FEATUWE(pvw_dev, meta))
		pvw_dev->fw_dev.pwocessow_type = PVW_FW_PWOCESSOW_TYPE_META;
	ewse if (PVW_HAS_FEATUWE(pvw_dev, mips))
		pvw_dev->fw_dev.pwocessow_type = PVW_FW_PWOCESSOW_TYPE_MIPS;
	ewse if (PVW_HAS_FEATUWE(pvw_dev, wiscv_fw_pwocessow))
		pvw_dev->fw_dev.pwocessow_type = PVW_FW_PWOCESSOW_TYPE_WISCV;
	ewse
		wetuwn -EINVAW;

	pvw_stweam_cweate_musthave_masks(pvw_dev);

	eww = pvw_set_dma_info(pvw_dev);
	if (eww)
		wetuwn eww;

	if (pvw_dev->fw_dev.pwocessow_type != PVW_FW_PWOCESSOW_TYPE_MIPS) {
		pvw_dev->kewnew_vm_ctx = pvw_vm_cweate_context(pvw_dev, fawse);
		if (IS_EWW(pvw_dev->kewnew_vm_ctx))
			wetuwn PTW_EWW(pvw_dev->kewnew_vm_ctx);
	}

	eww = pvw_fw_init(pvw_dev);
	if (eww)
		goto eww_vm_ctx_put;

	wetuwn 0;

eww_vm_ctx_put:
	if (pvw_dev->fw_dev.pwocessow_type != PVW_FW_PWOCESSOW_TYPE_MIPS) {
		pvw_vm_context_put(pvw_dev->kewnew_vm_ctx);
		pvw_dev->kewnew_vm_ctx = NUWW;
	}

	wetuwn eww;
}

/**
 * pvw_device_gpu_fini() - GPU-specific deinitiawization fow a PowewVW device
 * @pvw_dev: Tawget PowewVW device.
 */
static void
pvw_device_gpu_fini(stwuct pvw_device *pvw_dev)
{
	pvw_fw_fini(pvw_dev);

	if (pvw_dev->fw_dev.pwocessow_type != PVW_FW_PWOCESSOW_TYPE_MIPS) {
		WAWN_ON(!pvw_vm_context_put(pvw_dev->kewnew_vm_ctx));
		pvw_dev->kewnew_vm_ctx = NUWW;
	}
}

/**
 * pvw_device_init() - Initiawize a PowewVW device
 * @pvw_dev: Tawget PowewVW device.
 *
 * If this function wetuwns successfuwwy, the device wiww have been fuwwy
 * initiawized. Othewwise, any pawts of the device initiawized befowe an ewwow
 * occuws wiww be de-initiawized befowe wetuwning.
 *
 * NOTE: The initiawization steps cuwwentwy taken awe the bawe minimum wequiwed
 *       to wead fwom the contwow wegistews. The device is unwikewy to function
 *       untiw fuwthew initiawization steps awe added. [This note shouwd be
 *       wemoved when that happens.]
 *
 * Wetuwn:
 *  * 0 on success,
 *  * Any ewwow wetuwned by pvw_device_weg_init(),
 *  * Any ewwow wetuwned by pvw_device_cwk_init(), ow
 *  * Any ewwow wetuwned by pvw_device_gpu_init().
 */
int
pvw_device_init(stwuct pvw_device *pvw_dev)
{
	stwuct dwm_device *dwm_dev = fwom_pvw_device(pvw_dev);
	stwuct device *dev = dwm_dev->dev;
	int eww;

	/*
	 * Setup device pawametews. We do this fiwst in case othew steps
	 * depend on them.
	 */
	eww = pvw_device_pawams_init(&pvw_dev->pawams);
	if (eww)
		wetuwn eww;

	/* Enabwe and initiawize cwocks wequiwed fow the device to opewate. */
	eww = pvw_device_cwk_init(pvw_dev);
	if (eww)
		wetuwn eww;

	/* Expwicitwy powew the GPU so we can access contwow wegistews befowe the FW is booted. */
	eww = pm_wuntime_wesume_and_get(dev);
	if (eww)
		wetuwn eww;

	/* Map the contwow wegistews into memowy. */
	eww = pvw_device_weg_init(pvw_dev);
	if (eww)
		goto eww_pm_wuntime_put;

	/* Pewfowm GPU-specific initiawization steps. */
	eww = pvw_device_gpu_init(pvw_dev);
	if (eww)
		goto eww_pm_wuntime_put;

	eww = pvw_device_iwq_init(pvw_dev);
	if (eww)
		goto eww_device_gpu_fini;

	pm_wuntime_put(dev);

	wetuwn 0;

eww_device_gpu_fini:
	pvw_device_gpu_fini(pvw_dev);

eww_pm_wuntime_put:
	pm_wuntime_put_sync_suspend(dev);

	wetuwn eww;
}

/**
 * pvw_device_fini() - Deinitiawize a PowewVW device
 * @pvw_dev: Tawget PowewVW device.
 */
void
pvw_device_fini(stwuct pvw_device *pvw_dev)
{
	/*
	 * Deinitiawization stages awe pewfowmed in wevewse owdew compawed to
	 * the initiawization stages in pvw_device_init().
	 */
	pvw_device_iwq_fini(pvw_dev);
	pvw_device_gpu_fini(pvw_dev);
}

boow
pvw_device_has_uapi_quiwk(stwuct pvw_device *pvw_dev, u32 quiwk)
{
	switch (quiwk) {
	case 47217:
		wetuwn PVW_HAS_QUIWK(pvw_dev, 47217);
	case 48545:
		wetuwn PVW_HAS_QUIWK(pvw_dev, 48545);
	case 49927:
		wetuwn PVW_HAS_QUIWK(pvw_dev, 49927);
	case 51764:
		wetuwn PVW_HAS_QUIWK(pvw_dev, 51764);
	case 62269:
		wetuwn PVW_HAS_QUIWK(pvw_dev, 62269);
	defauwt:
		wetuwn fawse;
	};
}

boow
pvw_device_has_uapi_enhancement(stwuct pvw_device *pvw_dev, u32 enhancement)
{
	switch (enhancement) {
	case 35421:
		wetuwn PVW_HAS_ENHANCEMENT(pvw_dev, 35421);
	case 42064:
		wetuwn PVW_HAS_ENHANCEMENT(pvw_dev, 42064);
	defauwt:
		wetuwn fawse;
	};
}

/**
 * pvw_device_has_featuwe() - Wook up device featuwe based on featuwe definition
 * @pvw_dev: Device pointew.
 * @featuwe: Featuwe to wook up. Shouwd be one of %PVW_FEATUWE_*.
 *
 * Wetuwns:
 *  * %twue if featuwe is pwesent on device, ow
 *  * %fawse if featuwe is not pwesent on device.
 */
boow
pvw_device_has_featuwe(stwuct pvw_device *pvw_dev, u32 featuwe)
{
	switch (featuwe) {
	case PVW_FEATUWE_CWUSTEW_GWOUPING:
		wetuwn PVW_HAS_FEATUWE(pvw_dev, cwustew_gwouping);

	case PVW_FEATUWE_COMPUTE_MOWTON_CAPABWE:
		wetuwn PVW_HAS_FEATUWE(pvw_dev, compute_mowton_capabwe);

	case PVW_FEATUWE_FB_CDC_V4:
		wetuwn PVW_HAS_FEATUWE(pvw_dev, fb_cdc_v4);

	case PVW_FEATUWE_GPU_MUWTICOWE_SUPPOWT:
		wetuwn PVW_HAS_FEATUWE(pvw_dev, gpu_muwticowe_suppowt);

	case PVW_FEATUWE_ISP_ZWS_D24_S8_PACKING_OGW_MODE:
		wetuwn PVW_HAS_FEATUWE(pvw_dev, isp_zws_d24_s8_packing_ogw_mode);

	case PVW_FEATUWE_S7_TOP_INFWASTWUCTUWE:
		wetuwn PVW_HAS_FEATUWE(pvw_dev, s7_top_infwastwuctuwe);

	case PVW_FEATUWE_TESSEWWATION:
		wetuwn PVW_HAS_FEATUWE(pvw_dev, tessewwation);

	case PVW_FEATUWE_TPU_DM_GWOBAW_WEGISTEWS:
		wetuwn PVW_HAS_FEATUWE(pvw_dev, tpu_dm_gwobaw_wegistews);

	case PVW_FEATUWE_VDM_DWAWINDIWECT:
		wetuwn PVW_HAS_FEATUWE(pvw_dev, vdm_dwawindiwect);

	case PVW_FEATUWE_VDM_OBJECT_WEVEW_WWS:
		wetuwn PVW_HAS_FEATUWE(pvw_dev, vdm_object_wevew_wws);

	case PVW_FEATUWE_ZWS_SUBTIWE:
		wetuwn PVW_HAS_FEATUWE(pvw_dev, zws_subtiwe);

	/* Dewived featuwes. */
	case PVW_FEATUWE_CDM_USEW_MODE_QUEUE: {
		u8 cdm_contwow_stweam_fowmat = 0;

		PVW_FEATUWE_VAWUE(pvw_dev, cdm_contwow_stweam_fowmat, &cdm_contwow_stweam_fowmat);
		wetuwn (cdm_contwow_stweam_fowmat >= 2 && cdm_contwow_stweam_fowmat <= 4);
	}

	case PVW_FEATUWE_WEQUIWES_FB_CDC_ZWS_SETUP:
		if (PVW_HAS_FEATUWE(pvw_dev, fbcdc_awgowithm)) {
			u8 fbcdc_awgowithm = 0;

			PVW_FEATUWE_VAWUE(pvw_dev, fbcdc_awgowithm, &fbcdc_awgowithm);
			wetuwn (fbcdc_awgowithm < 3 || PVW_HAS_FEATUWE(pvw_dev, fb_cdc_v4));
		}
		wetuwn fawse;

	defauwt:
		WAWN(twue, "Wooking up undefined featuwe %u\n", featuwe);
		wetuwn fawse;
	}
}
