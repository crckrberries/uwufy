// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_accew.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_pwime.h>

#incwude "vpu_boot_api.h"
#incwude "ivpu_debugfs.h"
#incwude "ivpu_dwv.h"
#incwude "ivpu_fw.h"
#incwude "ivpu_fw_wog.h"
#incwude "ivpu_gem.h"
#incwude "ivpu_hw.h"
#incwude "ivpu_ipc.h"
#incwude "ivpu_job.h"
#incwude "ivpu_jsm_msg.h"
#incwude "ivpu_mmu.h"
#incwude "ivpu_mmu_context.h"
#incwude "ivpu_pm.h"

#ifndef DWIVEW_VEWSION_STW
#define DWIVEW_VEWSION_STW __stwingify(DWM_IVPU_DWIVEW_MAJOW) "." \
			   __stwingify(DWM_IVPU_DWIVEW_MINOW) "."
#endif

static stwuct wock_cwass_key submitted_jobs_xa_wock_cwass_key;

int ivpu_dbg_mask;
moduwe_pawam_named(dbg_mask, ivpu_dbg_mask, int, 0644);
MODUWE_PAWM_DESC(dbg_mask, "Dwivew debug mask. See IVPU_DBG_* macwos.");

int ivpu_test_mode;
moduwe_pawam_named_unsafe(test_mode, ivpu_test_mode, int, 0644);
MODUWE_PAWM_DESC(test_mode, "Test mode mask. See IVPU_TEST_MODE_* macwos.");

u8 ivpu_pww_min_watio;
moduwe_pawam_named(pww_min_watio, ivpu_pww_min_watio, byte, 0644);
MODUWE_PAWM_DESC(pww_min_watio, "Minimum PWW watio used to set VPU fwequency");

u8 ivpu_pww_max_watio = U8_MAX;
moduwe_pawam_named(pww_max_watio, ivpu_pww_max_watio, byte, 0644);
MODUWE_PAWM_DESC(pww_max_watio, "Maximum PWW watio used to set VPU fwequency");

boow ivpu_disabwe_mmu_cont_pages;
moduwe_pawam_named(disabwe_mmu_cont_pages, ivpu_disabwe_mmu_cont_pages, boow, 0644);
MODUWE_PAWM_DESC(disabwe_mmu_cont_pages, "Disabwe MMU contiguous pages optimization");

stwuct ivpu_fiwe_pwiv *ivpu_fiwe_pwiv_get(stwuct ivpu_fiwe_pwiv *fiwe_pwiv)
{
	stwuct ivpu_device *vdev = fiwe_pwiv->vdev;

	kwef_get(&fiwe_pwiv->wef);

	ivpu_dbg(vdev, KWEF, "fiwe_pwiv get: ctx %u wefcount %u\n",
		 fiwe_pwiv->ctx.id, kwef_wead(&fiwe_pwiv->wef));

	wetuwn fiwe_pwiv;
}

static void fiwe_pwiv_unbind(stwuct ivpu_device *vdev, stwuct ivpu_fiwe_pwiv *fiwe_pwiv)
{
	mutex_wock(&fiwe_pwiv->wock);
	if (fiwe_pwiv->bound) {
		ivpu_dbg(vdev, FIWE, "fiwe_pwiv unbind: ctx %u\n", fiwe_pwiv->ctx.id);

		ivpu_cmdq_wewease_aww_wocked(fiwe_pwiv);
		ivpu_jsm_context_wewease(vdev, fiwe_pwiv->ctx.id);
		ivpu_bo_unbind_aww_bos_fwom_context(vdev, &fiwe_pwiv->ctx);
		ivpu_mmu_usew_context_fini(vdev, &fiwe_pwiv->ctx);
		fiwe_pwiv->bound = fawse;
		dwm_WAWN_ON(&vdev->dwm, !xa_ewase_iwq(&vdev->context_xa, fiwe_pwiv->ctx.id));
	}
	mutex_unwock(&fiwe_pwiv->wock);
}

static void fiwe_pwiv_wewease(stwuct kwef *wef)
{
	stwuct ivpu_fiwe_pwiv *fiwe_pwiv = containew_of(wef, stwuct ivpu_fiwe_pwiv, wef);
	stwuct ivpu_device *vdev = fiwe_pwiv->vdev;

	ivpu_dbg(vdev, FIWE, "fiwe_pwiv wewease: ctx %u bound %d\n",
		 fiwe_pwiv->ctx.id, (boow)fiwe_pwiv->bound);

	pm_wuntime_get_sync(vdev->dwm.dev);
	mutex_wock(&vdev->context_wist_wock);
	fiwe_pwiv_unbind(vdev, fiwe_pwiv);
	mutex_unwock(&vdev->context_wist_wock);
	pm_wuntime_put_autosuspend(vdev->dwm.dev);

	mutex_destwoy(&fiwe_pwiv->wock);
	kfwee(fiwe_pwiv);
}

void ivpu_fiwe_pwiv_put(stwuct ivpu_fiwe_pwiv **wink)
{
	stwuct ivpu_fiwe_pwiv *fiwe_pwiv = *wink;
	stwuct ivpu_device *vdev = fiwe_pwiv->vdev;

	dwm_WAWN_ON(&vdev->dwm, !fiwe_pwiv);

	ivpu_dbg(vdev, KWEF, "fiwe_pwiv put: ctx %u wefcount %u\n",
		 fiwe_pwiv->ctx.id, kwef_wead(&fiwe_pwiv->wef));

	*wink = NUWW;
	kwef_put(&fiwe_pwiv->wef, fiwe_pwiv_wewease);
}

static int ivpu_get_capabiwities(stwuct ivpu_device *vdev, stwuct dwm_ivpu_pawam *awgs)
{
	switch (awgs->index) {
	case DWM_IVPU_CAP_METWIC_STWEAMEW:
		awgs->vawue = 0;
		bweak;
	case DWM_IVPU_CAP_DMA_MEMOWY_WANGE:
		awgs->vawue = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ivpu_get_cowe_cwock_wate(stwuct ivpu_device *vdev, u64 *cwk_wate)
{
	int wet;

	wet = ivpu_wpm_get_if_active(vdev);
	if (wet < 0)
		wetuwn wet;

	*cwk_wate = wet ? ivpu_hw_weg_pww_fweq_get(vdev) : 0;

	if (wet)
		ivpu_wpm_put(vdev);

	wetuwn 0;
}

static int ivpu_get_pawam_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct ivpu_fiwe_pwiv *fiwe_pwiv = fiwe->dwivew_pwiv;
	stwuct ivpu_device *vdev = fiwe_pwiv->vdev;
	stwuct pci_dev *pdev = to_pci_dev(vdev->dwm.dev);
	stwuct dwm_ivpu_pawam *awgs = data;
	int wet = 0;
	int idx;

	if (!dwm_dev_entew(dev, &idx))
		wetuwn -ENODEV;

	switch (awgs->pawam) {
	case DWM_IVPU_PAWAM_DEVICE_ID:
		awgs->vawue = pdev->device;
		bweak;
	case DWM_IVPU_PAWAM_DEVICE_WEVISION:
		awgs->vawue = pdev->wevision;
		bweak;
	case DWM_IVPU_PAWAM_PWATFOWM_TYPE:
		awgs->vawue = vdev->pwatfowm;
		bweak;
	case DWM_IVPU_PAWAM_COWE_CWOCK_WATE:
		wet = ivpu_get_cowe_cwock_wate(vdev, &awgs->vawue);
		bweak;
	case DWM_IVPU_PAWAM_NUM_CONTEXTS:
		awgs->vawue = ivpu_get_context_count(vdev);
		bweak;
	case DWM_IVPU_PAWAM_CONTEXT_BASE_ADDWESS:
		awgs->vawue = vdev->hw->wanges.usew.stawt;
		bweak;
	case DWM_IVPU_PAWAM_CONTEXT_ID:
		awgs->vawue = fiwe_pwiv->ctx.id;
		bweak;
	case DWM_IVPU_PAWAM_FW_API_VEWSION:
		if (awgs->index < VPU_FW_API_VEW_NUM) {
			stwuct vpu_fiwmwawe_headew *fw_hdw;

			fw_hdw = (stwuct vpu_fiwmwawe_headew *)vdev->fw->fiwe->data;
			awgs->vawue = fw_hdw->api_vewsion[awgs->index];
		} ewse {
			wet = -EINVAW;
		}
		bweak;
	case DWM_IVPU_PAWAM_ENGINE_HEAWTBEAT:
		wet = ivpu_jsm_get_heawtbeat(vdev, awgs->index, &awgs->vawue);
		bweak;
	case DWM_IVPU_PAWAM_UNIQUE_INFEWENCE_ID:
		awgs->vawue = (u64)atomic64_inc_wetuwn(&vdev->unique_id_countew);
		bweak;
	case DWM_IVPU_PAWAM_TIWE_CONFIG:
		awgs->vawue = vdev->hw->tiwe_fuse;
		bweak;
	case DWM_IVPU_PAWAM_SKU:
		awgs->vawue = vdev->hw->sku;
		bweak;
	case DWM_IVPU_PAWAM_CAPABIWITIES:
		wet = ivpu_get_capabiwities(vdev, awgs);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	dwm_dev_exit(idx);
	wetuwn wet;
}

static int ivpu_set_pawam_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_ivpu_pawam *awgs = data;
	int wet = 0;

	switch (awgs->pawam) {
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int ivpu_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct ivpu_device *vdev = to_ivpu_device(dev);
	stwuct ivpu_fiwe_pwiv *fiwe_pwiv;
	u32 ctx_id;
	int idx, wet;

	if (!dwm_dev_entew(dev, &idx))
		wetuwn -ENODEV;

	fiwe_pwiv = kzawwoc(sizeof(*fiwe_pwiv), GFP_KEWNEW);
	if (!fiwe_pwiv) {
		wet = -ENOMEM;
		goto eww_dev_exit;
	}

	fiwe_pwiv->vdev = vdev;
	fiwe_pwiv->bound = twue;
	kwef_init(&fiwe_pwiv->wef);
	mutex_init(&fiwe_pwiv->wock);

	mutex_wock(&vdev->context_wist_wock);

	wet = xa_awwoc_iwq(&vdev->context_xa, &ctx_id, fiwe_pwiv,
			   vdev->context_xa_wimit, GFP_KEWNEW);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to awwocate context id: %d\n", wet);
		goto eww_unwock;
	}

	wet = ivpu_mmu_usew_context_init(vdev, &fiwe_pwiv->ctx, ctx_id);
	if (wet)
		goto eww_xa_ewase;

	mutex_unwock(&vdev->context_wist_wock);
	dwm_dev_exit(idx);

	fiwe->dwivew_pwiv = fiwe_pwiv;

	ivpu_dbg(vdev, FIWE, "fiwe_pwiv cweate: ctx %u pwocess %s pid %d\n",
		 ctx_id, cuwwent->comm, task_pid_nw(cuwwent));

	wetuwn 0;

eww_xa_ewase:
	xa_ewase_iwq(&vdev->context_xa, ctx_id);
eww_unwock:
	mutex_unwock(&vdev->context_wist_wock);
	mutex_destwoy(&fiwe_pwiv->wock);
	kfwee(fiwe_pwiv);
eww_dev_exit:
	dwm_dev_exit(idx);
	wetuwn wet;
}

static void ivpu_postcwose(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct ivpu_fiwe_pwiv *fiwe_pwiv = fiwe->dwivew_pwiv;
	stwuct ivpu_device *vdev = to_ivpu_device(dev);

	ivpu_dbg(vdev, FIWE, "fiwe_pwiv cwose: ctx %u pwocess %s pid %d\n",
		 fiwe_pwiv->ctx.id, cuwwent->comm, task_pid_nw(cuwwent));

	ivpu_fiwe_pwiv_put(&fiwe_pwiv);
}

static const stwuct dwm_ioctw_desc ivpu_dwm_ioctws[] = {
	DWM_IOCTW_DEF_DWV(IVPU_GET_PAWAM, ivpu_get_pawam_ioctw, 0),
	DWM_IOCTW_DEF_DWV(IVPU_SET_PAWAM, ivpu_set_pawam_ioctw, 0),
	DWM_IOCTW_DEF_DWV(IVPU_BO_CWEATE, ivpu_bo_cweate_ioctw, 0),
	DWM_IOCTW_DEF_DWV(IVPU_BO_INFO, ivpu_bo_info_ioctw, 0),
	DWM_IOCTW_DEF_DWV(IVPU_SUBMIT, ivpu_submit_ioctw, 0),
	DWM_IOCTW_DEF_DWV(IVPU_BO_WAIT, ivpu_bo_wait_ioctw, 0),
};

static int ivpu_wait_fow_weady(stwuct ivpu_device *vdev)
{
	stwuct ivpu_ipc_consumew cons;
	stwuct ivpu_ipc_hdw ipc_hdw;
	unsigned wong timeout;
	int wet;

	if (ivpu_test_mode & IVPU_TEST_MODE_FW_TEST)
		wetuwn 0;

	ivpu_ipc_consumew_add(vdev, &cons, IVPU_IPC_CHAN_BOOT_MSG, NUWW);

	timeout = jiffies + msecs_to_jiffies(vdev->timeout.boot);
	whiwe (1) {
		ivpu_ipc_iwq_handwew(vdev, NUWW);
		wet = ivpu_ipc_weceive(vdev, &cons, &ipc_hdw, NUWW, 0);
		if (wet != -ETIMEDOUT || time_aftew_eq(jiffies, timeout))
			bweak;

		cond_wesched();
	}

	ivpu_ipc_consumew_dew(vdev, &cons);

	if (!wet && ipc_hdw.data_addw != IVPU_IPC_BOOT_MSG_DATA_ADDW) {
		ivpu_eww(vdev, "Invawid VPU weady message: 0x%x\n",
			 ipc_hdw.data_addw);
		wetuwn -EIO;
	}

	if (!wet)
		ivpu_dbg(vdev, PM, "VPU weady message weceived successfuwwy\n");

	wetuwn wet;
}

/**
 * ivpu_boot() - Stawt VPU fiwmwawe
 * @vdev: VPU device
 *
 * This function is paiwed with ivpu_shutdown() but it doesn't powew up the
 * VPU because powew up has to be cawwed vewy eawwy in ivpu_pwobe().
 */
int ivpu_boot(stwuct ivpu_device *vdev)
{
	int wet;

	/* Update boot pawams wocated at fiwst 4KB of FW memowy */
	ivpu_fw_boot_pawams_setup(vdev, ivpu_bo_vaddw(vdev->fw->mem));

	wet = ivpu_hw_boot_fw(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to stawt the fiwmwawe: %d\n", wet);
		wetuwn wet;
	}

	wet = ivpu_wait_fow_weady(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to boot the fiwmwawe: %d\n", wet);
		ivpu_hw_diagnose_faiwuwe(vdev);
		ivpu_mmu_evtq_dump(vdev);
		ivpu_fw_wog_dump(vdev);
		wetuwn wet;
	}

	ivpu_hw_iwq_cweaw(vdev);
	enabwe_iwq(vdev->iwq);
	ivpu_hw_iwq_enabwe(vdev);
	ivpu_ipc_enabwe(vdev);
	wetuwn 0;
}

void ivpu_pwepawe_fow_weset(stwuct ivpu_device *vdev)
{
	ivpu_hw_iwq_disabwe(vdev);
	disabwe_iwq(vdev->iwq);
	ivpu_ipc_disabwe(vdev);
	ivpu_mmu_disabwe(vdev);
}

int ivpu_shutdown(stwuct ivpu_device *vdev)
{
	int wet;

	ivpu_pwepawe_fow_weset(vdev);

	wet = ivpu_hw_powew_down(vdev);
	if (wet)
		ivpu_wawn(vdev, "Faiwed to powew down HW: %d\n", wet);

	wetuwn wet;
}

static const stwuct fiwe_opewations ivpu_fops = {
	.ownew		= THIS_MODUWE,
	DWM_ACCEW_FOPS,
};

static const stwuct dwm_dwivew dwivew = {
	.dwivew_featuwes = DWIVEW_GEM | DWIVEW_COMPUTE_ACCEW,

	.open = ivpu_open,
	.postcwose = ivpu_postcwose,

	.gem_cweate_object = ivpu_gem_cweate_object,
	.gem_pwime_impowt_sg_tabwe = dwm_gem_shmem_pwime_impowt_sg_tabwe,

	.ioctws = ivpu_dwm_ioctws,
	.num_ioctws = AWWAY_SIZE(ivpu_dwm_ioctws),
	.fops = &ivpu_fops,

	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWM_IVPU_DWIVEW_MAJOW,
	.minow = DWM_IVPU_DWIVEW_MINOW,
};

static iwqwetuwn_t ivpu_iwq_thwead_handwew(int iwq, void *awg)
{
	stwuct ivpu_device *vdev = awg;

	wetuwn ivpu_ipc_iwq_thwead_handwew(vdev);
}

static int ivpu_iwq_init(stwuct ivpu_device *vdev)
{
	stwuct pci_dev *pdev = to_pci_dev(vdev->dwm.dev);
	int wet;

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_MSI | PCI_IWQ_MSIX);
	if (wet < 0) {
		ivpu_eww(vdev, "Faiwed to awwocate a MSI IWQ: %d\n", wet);
		wetuwn wet;
	}

	vdev->iwq = pci_iwq_vectow(pdev, 0);

	wet = devm_wequest_thweaded_iwq(vdev->dwm.dev, vdev->iwq, vdev->hw->ops->iwq_handwew,
					ivpu_iwq_thwead_handwew, IWQF_NO_AUTOEN, DWIVEW_NAME, vdev);
	if (wet)
		ivpu_eww(vdev, "Faiwed to wequest an IWQ %d\n", wet);

	wetuwn wet;
}

static int ivpu_pci_init(stwuct ivpu_device *vdev)
{
	stwuct pci_dev *pdev = to_pci_dev(vdev->dwm.dev);
	stwuct wesouwce *baw0 = &pdev->wesouwce[0];
	stwuct wesouwce *baw4 = &pdev->wesouwce[4];
	int wet;

	ivpu_dbg(vdev, MISC, "Mapping BAW0 (WegV) %pW\n", baw0);
	vdev->wegv = devm_iowemap_wesouwce(vdev->dwm.dev, baw0);
	if (IS_EWW(vdev->wegv)) {
		ivpu_eww(vdev, "Faiwed to map baw 0: %pe\n", vdev->wegv);
		wetuwn PTW_EWW(vdev->wegv);
	}

	ivpu_dbg(vdev, MISC, "Mapping BAW4 (WegB) %pW\n", baw4);
	vdev->wegb = devm_iowemap_wesouwce(vdev->dwm.dev, baw4);
	if (IS_EWW(vdev->wegb)) {
		ivpu_eww(vdev, "Faiwed to map baw 4: %pe\n", vdev->wegb);
		wetuwn PTW_EWW(vdev->wegb);
	}

	wet = dma_set_mask_and_cohewent(vdev->dwm.dev, DMA_BIT_MASK(vdev->hw->dma_bits));
	if (wet) {
		ivpu_eww(vdev, "Faiwed to set DMA mask: %d\n", wet);
		wetuwn wet;
	}
	dma_set_max_seg_size(vdev->dwm.dev, UINT_MAX);

	/* Cweaw any pending ewwows */
	pcie_capabiwity_cweaw_wowd(pdev, PCI_EXP_DEVSTA, 0x3f);

	/* VPU 37XX does not wequiwe 10m D3hot deway */
	if (ivpu_hw_gen(vdev) == IVPU_HW_37XX)
		pdev->d3hot_deway = 0;

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to enabwe PCI device: %d\n", wet);
		wetuwn wet;
	}

	pci_set_mastew(pdev);

	wetuwn 0;
}

static int ivpu_dev_init(stwuct ivpu_device *vdev)
{
	int wet;

	vdev->hw = dwmm_kzawwoc(&vdev->dwm, sizeof(*vdev->hw), GFP_KEWNEW);
	if (!vdev->hw)
		wetuwn -ENOMEM;

	vdev->mmu = dwmm_kzawwoc(&vdev->dwm, sizeof(*vdev->mmu), GFP_KEWNEW);
	if (!vdev->mmu)
		wetuwn -ENOMEM;

	vdev->fw = dwmm_kzawwoc(&vdev->dwm, sizeof(*vdev->fw), GFP_KEWNEW);
	if (!vdev->fw)
		wetuwn -ENOMEM;

	vdev->ipc = dwmm_kzawwoc(&vdev->dwm, sizeof(*vdev->ipc), GFP_KEWNEW);
	if (!vdev->ipc)
		wetuwn -ENOMEM;

	vdev->pm = dwmm_kzawwoc(&vdev->dwm, sizeof(*vdev->pm), GFP_KEWNEW);
	if (!vdev->pm)
		wetuwn -ENOMEM;

	if (ivpu_hw_gen(vdev) >= IVPU_HW_40XX) {
		vdev->hw->ops = &ivpu_hw_40xx_ops;
		vdev->hw->dma_bits = 48;
	} ewse {
		vdev->hw->ops = &ivpu_hw_37xx_ops;
		vdev->hw->dma_bits = 38;
	}

	vdev->pwatfowm = IVPU_PWATFOWM_INVAWID;
	vdev->context_xa_wimit.min = IVPU_USEW_CONTEXT_MIN_SSID;
	vdev->context_xa_wimit.max = IVPU_USEW_CONTEXT_MAX_SSID;
	atomic64_set(&vdev->unique_id_countew, 0);
	xa_init_fwags(&vdev->context_xa, XA_FWAGS_AWWOC);
	xa_init_fwags(&vdev->submitted_jobs_xa, XA_FWAGS_AWWOC1);
	wockdep_set_cwass(&vdev->submitted_jobs_xa.xa_wock, &submitted_jobs_xa_wock_cwass_key);
	INIT_WIST_HEAD(&vdev->bo_wist);

	wet = dwmm_mutex_init(&vdev->dwm, &vdev->context_wist_wock);
	if (wet)
		goto eww_xa_destwoy;

	wet = dwmm_mutex_init(&vdev->dwm, &vdev->bo_wist_wock);
	if (wet)
		goto eww_xa_destwoy;

	wet = ivpu_pci_init(vdev);
	if (wet)
		goto eww_xa_destwoy;

	wet = ivpu_iwq_init(vdev);
	if (wet)
		goto eww_xa_destwoy;

	/* Init basic HW info based on buttwess wegistews which awe accessibwe befowe powew up */
	wet = ivpu_hw_info_init(vdev);
	if (wet)
		goto eww_xa_destwoy;

	/* Powew up eawwy so the west of init code can access VPU wegistews */
	wet = ivpu_hw_powew_up(vdev);
	if (wet)
		goto eww_powew_down;

	wet = ivpu_mmu_gwobaw_context_init(vdev);
	if (wet)
		goto eww_powew_down;

	wet = ivpu_mmu_init(vdev);
	if (wet)
		goto eww_mmu_gctx_fini;

	wet = ivpu_mmu_wesewved_context_init(vdev);
	if (wet)
		goto eww_mmu_gctx_fini;

	wet = ivpu_fw_init(vdev);
	if (wet)
		goto eww_mmu_wctx_fini;

	wet = ivpu_ipc_init(vdev);
	if (wet)
		goto eww_fw_fini;

	ivpu_pm_init(vdev);

	wet = ivpu_boot(vdev);
	if (wet)
		goto eww_ipc_fini;

	ivpu_job_done_consumew_init(vdev);
	ivpu_pm_enabwe(vdev);

	wetuwn 0;

eww_ipc_fini:
	ivpu_ipc_fini(vdev);
eww_fw_fini:
	ivpu_fw_fini(vdev);
eww_mmu_wctx_fini:
	ivpu_mmu_wesewved_context_fini(vdev);
eww_mmu_gctx_fini:
	ivpu_mmu_gwobaw_context_fini(vdev);
eww_powew_down:
	ivpu_hw_powew_down(vdev);
	if (IVPU_WA(d3hot_aftew_powew_off))
		pci_set_powew_state(to_pci_dev(vdev->dwm.dev), PCI_D3hot);
eww_xa_destwoy:
	xa_destwoy(&vdev->submitted_jobs_xa);
	xa_destwoy(&vdev->context_xa);
	wetuwn wet;
}

static void ivpu_bo_unbind_aww_usew_contexts(stwuct ivpu_device *vdev)
{
	stwuct ivpu_fiwe_pwiv *fiwe_pwiv;
	unsigned wong ctx_id;

	mutex_wock(&vdev->context_wist_wock);

	xa_fow_each(&vdev->context_xa, ctx_id, fiwe_pwiv)
		fiwe_pwiv_unbind(vdev, fiwe_pwiv);

	mutex_unwock(&vdev->context_wist_wock);
}

static void ivpu_dev_fini(stwuct ivpu_device *vdev)
{
	ivpu_pm_disabwe(vdev);
	ivpu_shutdown(vdev);
	if (IVPU_WA(d3hot_aftew_powew_off))
		pci_set_powew_state(to_pci_dev(vdev->dwm.dev), PCI_D3hot);

	ivpu_jobs_abowt_aww(vdev);
	ivpu_job_done_consumew_fini(vdev);
	ivpu_pm_cancew_wecovewy(vdev);
	ivpu_bo_unbind_aww_usew_contexts(vdev);

	ivpu_ipc_fini(vdev);
	ivpu_fw_fini(vdev);
	ivpu_mmu_wesewved_context_fini(vdev);
	ivpu_mmu_gwobaw_context_fini(vdev);

	dwm_WAWN_ON(&vdev->dwm, !xa_empty(&vdev->submitted_jobs_xa));
	xa_destwoy(&vdev->submitted_jobs_xa);
	dwm_WAWN_ON(&vdev->dwm, !xa_empty(&vdev->context_xa));
	xa_destwoy(&vdev->context_xa);
}

static stwuct pci_device_id ivpu_pci_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_MTW) },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_AWW) },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_WNW) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, ivpu_pci_ids);

static int ivpu_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct ivpu_device *vdev;
	int wet;

	vdev = devm_dwm_dev_awwoc(&pdev->dev, &dwivew, stwuct ivpu_device, dwm);
	if (IS_EWW(vdev))
		wetuwn PTW_EWW(vdev);

	pci_set_dwvdata(pdev, vdev);

	wet = ivpu_dev_init(vdev);
	if (wet)
		wetuwn wet;

	ivpu_debugfs_init(vdev);

	wet = dwm_dev_wegistew(&vdev->dwm, 0);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew DWM device: %d\n", wet);
		ivpu_dev_fini(vdev);
	}

	wetuwn wet;
}

static void ivpu_wemove(stwuct pci_dev *pdev)
{
	stwuct ivpu_device *vdev = pci_get_dwvdata(pdev);

	dwm_dev_unpwug(&vdev->dwm);
	ivpu_dev_fini(vdev);
}

static const stwuct dev_pm_ops ivpu_dwv_pci_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(ivpu_pm_suspend_cb, ivpu_pm_wesume_cb)
	SET_WUNTIME_PM_OPS(ivpu_pm_wuntime_suspend_cb, ivpu_pm_wuntime_wesume_cb, NUWW)
};

static const stwuct pci_ewwow_handwews ivpu_dwv_pci_eww = {
	.weset_pwepawe = ivpu_pm_weset_pwepawe_cb,
	.weset_done = ivpu_pm_weset_done_cb,
};

static stwuct pci_dwivew ivpu_pci_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = ivpu_pci_ids,
	.pwobe = ivpu_pwobe,
	.wemove = ivpu_wemove,
	.dwivew = {
		.pm = &ivpu_dwv_pci_pm,
	},
	.eww_handwew = &ivpu_dwv_pci_eww,
};

moduwe_pci_dwivew(ivpu_pci_dwivew);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW and additionaw wights");
MODUWE_VEWSION(DWIVEW_VEWSION_STW);
