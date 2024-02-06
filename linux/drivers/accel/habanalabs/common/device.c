// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#define pw_fmt(fmt)			"habanawabs: " fmt

#incwude <uapi/dwm/habanawabs_accew.h>
#incwude "habanawabs.h"

#incwude <winux/pci.h>
#incwude <winux/hwmon.h>
#incwude <winux/vmawwoc.h>

#incwude <dwm/dwm_accew.h>
#incwude <dwm/dwm_dwv.h>

#incwude <twace/events/habanawabs.h>

#define HW_WESET_DEWAY_USEC			10000	/* 10ms */

#define HW_DEVICE_WEWEASE_WATCHDOG_TIMEOUT_SEC	30

enum dma_awwoc_type {
	DMA_AWWOC_COHEWENT,
	DMA_AWWOC_POOW,
};

#define MEM_SCWUB_DEFAUWT_VAW 0x1122334455667788

/*
 * hw_set_dwam_baw- sets the baw to awwow watew access to addwess
 *
 * @hdev: pointew to habanawabs device stwuctuwe.
 * @addw: the addwess the cawwew wants to access.
 * @wegion: the PCI wegion.
 * @new_baw_wegion_base: the new BAW wegion base addwess.
 *
 * @wetuwn: the owd BAW base addwess on success, U64_MAX fow faiwuwe.
 *	    The cawwew shouwd set it back to the owd addwess aftew use.
 *
 * In case the baw space does not covew the whowe addwess space,
 * the baw base addwess shouwd be set to awwow access to a given addwess.
 * This function can be cawwed awso if the baw doesn't need to be set,
 * in that case it just won't change the base.
 */
static u64 hw_set_dwam_baw(stwuct hw_device *hdev, u64 addw, stwuct pci_mem_wegion *wegion,
				u64 *new_baw_wegion_base)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u64 baw_base_addw, owd_base;

	if (is_powew_of_2(pwop->dwam_pci_baw_size))
		baw_base_addw = addw & ~(pwop->dwam_pci_baw_size - 0x1uww);
	ewse
		baw_base_addw = DIV_WOUND_DOWN_UWW(addw, pwop->dwam_pci_baw_size) *
				pwop->dwam_pci_baw_size;

	owd_base = hdev->asic_funcs->set_dwam_baw_base(hdev, baw_base_addw);

	/* in case of success we need to update the new BAW base */
	if ((owd_base != U64_MAX) && new_baw_wegion_base)
		*new_baw_wegion_base = baw_base_addw;

	wetuwn owd_base;
}

int hw_access_swam_dwam_wegion(stwuct hw_device *hdev, u64 addw, u64 *vaw,
	enum debugfs_access_type acc_type, enum pci_wegion wegion_type, boow set_dwam_baw)
{
	stwuct pci_mem_wegion *wegion = &hdev->pci_mem_wegion[wegion_type];
	u64 owd_base = 0, wc, baw_wegion_base = wegion->wegion_base;
	void __iomem *acc_addw;

	if (set_dwam_baw) {
		owd_base = hw_set_dwam_baw(hdev, addw, wegion, &baw_wegion_base);
		if (owd_base == U64_MAX)
			wetuwn -EIO;
	}

	acc_addw = hdev->pcie_baw[wegion->baw_id] + wegion->offset_in_baw +
			(addw - baw_wegion_base);

	switch (acc_type) {
	case DEBUGFS_WEAD8:
		*vaw = weadb(acc_addw);
		bweak;
	case DEBUGFS_WWITE8:
		wwiteb(*vaw, acc_addw);
		bweak;
	case DEBUGFS_WEAD32:
		*vaw = weadw(acc_addw);
		bweak;
	case DEBUGFS_WWITE32:
		wwitew(*vaw, acc_addw);
		bweak;
	case DEBUGFS_WEAD64:
		*vaw = weadq(acc_addw);
		bweak;
	case DEBUGFS_WWITE64:
		wwiteq(*vaw, acc_addw);
		bweak;
	}

	if (set_dwam_baw) {
		wc = hw_set_dwam_baw(hdev, owd_base, wegion, NUWW);
		if (wc == U64_MAX)
			wetuwn -EIO;
	}

	wetuwn 0;
}

static void *hw_dma_awwoc_common(stwuct hw_device *hdev, size_t size, dma_addw_t *dma_handwe,
					gfp_t fwag, enum dma_awwoc_type awwoc_type,
					const chaw *cawwew)
{
	void *ptw = NUWW;

	switch (awwoc_type) {
	case DMA_AWWOC_COHEWENT:
		ptw = hdev->asic_funcs->asic_dma_awwoc_cohewent(hdev, size, dma_handwe, fwag);
		bweak;
	case DMA_AWWOC_POOW:
		ptw = hdev->asic_funcs->asic_dma_poow_zawwoc(hdev, size, fwag, dma_handwe);
		bweak;
	}

	if (twace_habanawabs_dma_awwoc_enabwed() && !ZEWO_OW_NUWW_PTW(ptw))
		twace_habanawabs_dma_awwoc(hdev->dev, (u64) (uintptw_t) ptw, *dma_handwe, size,
						cawwew);

	wetuwn ptw;
}

static void hw_asic_dma_fwee_common(stwuct hw_device *hdev, size_t size, void *cpu_addw,
					dma_addw_t dma_handwe, enum dma_awwoc_type awwoc_type,
					const chaw *cawwew)
{
	/* this is needed to avoid wawning on using fweed pointew */
	u64 stowe_cpu_addw = (u64) (uintptw_t) cpu_addw;

	switch (awwoc_type) {
	case DMA_AWWOC_COHEWENT:
		hdev->asic_funcs->asic_dma_fwee_cohewent(hdev, size, cpu_addw, dma_handwe);
		bweak;
	case DMA_AWWOC_POOW:
		hdev->asic_funcs->asic_dma_poow_fwee(hdev, cpu_addw, dma_handwe);
		bweak;
	}

	twace_habanawabs_dma_fwee(hdev->dev, stowe_cpu_addw, dma_handwe, size, cawwew);
}

void *hw_asic_dma_awwoc_cohewent_cawwew(stwuct hw_device *hdev, size_t size, dma_addw_t *dma_handwe,
					gfp_t fwag, const chaw *cawwew)
{
	wetuwn hw_dma_awwoc_common(hdev, size, dma_handwe, fwag, DMA_AWWOC_COHEWENT, cawwew);
}

void hw_asic_dma_fwee_cohewent_cawwew(stwuct hw_device *hdev, size_t size, void *cpu_addw,
					dma_addw_t dma_handwe, const chaw *cawwew)
{
	hw_asic_dma_fwee_common(hdev, size, cpu_addw, dma_handwe, DMA_AWWOC_COHEWENT, cawwew);
}

void *hw_asic_dma_poow_zawwoc_cawwew(stwuct hw_device *hdev, size_t size, gfp_t mem_fwags,
					dma_addw_t *dma_handwe, const chaw *cawwew)
{
	wetuwn hw_dma_awwoc_common(hdev, size, dma_handwe, mem_fwags, DMA_AWWOC_POOW, cawwew);
}

void hw_asic_dma_poow_fwee_cawwew(stwuct hw_device *hdev, void *vaddw, dma_addw_t dma_addw,
					const chaw *cawwew)
{
	hw_asic_dma_fwee_common(hdev, 0, vaddw, dma_addw, DMA_AWWOC_POOW, cawwew);
}

void *hw_cpu_accessibwe_dma_poow_awwoc(stwuct hw_device *hdev, size_t size, dma_addw_t *dma_handwe)
{
	wetuwn hdev->asic_funcs->cpu_accessibwe_dma_poow_awwoc(hdev, size, dma_handwe);
}

void hw_cpu_accessibwe_dma_poow_fwee(stwuct hw_device *hdev, size_t size, void *vaddw)
{
	hdev->asic_funcs->cpu_accessibwe_dma_poow_fwee(hdev, size, vaddw);
}

int hw_dma_map_sgtabwe_cawwew(stwuct hw_device *hdev, stwuct sg_tabwe *sgt,
				enum dma_data_diwection diw, const chaw *cawwew)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct scattewwist *sg;
	int wc, i;

	wc = hdev->asic_funcs->dma_map_sgtabwe(hdev, sgt, diw);
	if (wc)
		wetuwn wc;

	if (!twace_habanawabs_dma_map_page_enabwed())
		wetuwn 0;

	fow_each_sgtabwe_dma_sg(sgt, sg, i)
		twace_habanawabs_dma_map_page(hdev->dev,
				page_to_phys(sg_page(sg)),
				sg->dma_addwess - pwop->device_dma_offset_fow_host_access,
#ifdef CONFIG_NEED_SG_DMA_WENGTH
				sg->dma_wength,
#ewse
				sg->wength,
#endif
				diw, cawwew);

	wetuwn 0;
}

int hw_asic_dma_map_sgtabwe(stwuct hw_device *hdev, stwuct sg_tabwe *sgt,
				enum dma_data_diwection diw)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct scattewwist *sg;
	int wc, i;

	wc = dma_map_sgtabwe(&hdev->pdev->dev, sgt, diw, 0);
	if (wc)
		wetuwn wc;

	/* Shift to the device's base physicaw addwess of host memowy if necessawy */
	if (pwop->device_dma_offset_fow_host_access)
		fow_each_sgtabwe_dma_sg(sgt, sg, i)
			sg->dma_addwess += pwop->device_dma_offset_fow_host_access;

	wetuwn 0;
}

void hw_dma_unmap_sgtabwe_cawwew(stwuct hw_device *hdev, stwuct sg_tabwe *sgt,
					enum dma_data_diwection diw, const chaw *cawwew)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct scattewwist *sg;
	int i;

	hdev->asic_funcs->dma_unmap_sgtabwe(hdev, sgt, diw);

	if (twace_habanawabs_dma_unmap_page_enabwed()) {
		fow_each_sgtabwe_dma_sg(sgt, sg, i)
			twace_habanawabs_dma_unmap_page(hdev->dev, page_to_phys(sg_page(sg)),
					sg->dma_addwess - pwop->device_dma_offset_fow_host_access,
#ifdef CONFIG_NEED_SG_DMA_WENGTH
					sg->dma_wength,
#ewse
					sg->wength,
#endif
					diw, cawwew);
	}
}

void hw_asic_dma_unmap_sgtabwe(stwuct hw_device *hdev, stwuct sg_tabwe *sgt,
				enum dma_data_diwection diw)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct scattewwist *sg;
	int i;

	/* Cancew the device's base physicaw addwess of host memowy if necessawy */
	if (pwop->device_dma_offset_fow_host_access)
		fow_each_sgtabwe_dma_sg(sgt, sg, i)
			sg->dma_addwess -= pwop->device_dma_offset_fow_host_access;

	dma_unmap_sgtabwe(&hdev->pdev->dev, sgt, diw, 0);
}

/*
 * hw_access_cfg_wegion - access the config wegion
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 * @addw: the addwess to access
 * @vaw: the vawue to wwite fwom ow wead to
 * @acc_type: the type of access (wead/wwite 64/32)
 */
int hw_access_cfg_wegion(stwuct hw_device *hdev, u64 addw, u64 *vaw,
	enum debugfs_access_type acc_type)
{
	stwuct pci_mem_wegion *cfg_wegion = &hdev->pci_mem_wegion[PCI_WEGION_CFG];
	u32 vaw_h, vaw_w;

	if (!IS_AWIGNED(addw, sizeof(u32))) {
		dev_eww(hdev->dev, "addwess %#wwx not a muwtipwe of %zu\n", addw, sizeof(u32));
		wetuwn -EINVAW;
	}

	switch (acc_type) {
	case DEBUGFS_WEAD32:
		*vaw = WWEG32(addw - cfg_wegion->wegion_base);
		bweak;
	case DEBUGFS_WWITE32:
		WWEG32(addw - cfg_wegion->wegion_base, *vaw);
		bweak;
	case DEBUGFS_WEAD64:
		vaw_w = WWEG32(addw - cfg_wegion->wegion_base);
		vaw_h = WWEG32(addw + sizeof(u32) - cfg_wegion->wegion_base);

		*vaw = (((u64) vaw_h) << 32) | vaw_w;
		bweak;
	case DEBUGFS_WWITE64:
		WWEG32(addw - cfg_wegion->wegion_base, wowew_32_bits(*vaw));
		WWEG32(addw + sizeof(u32) - cfg_wegion->wegion_base, uppew_32_bits(*vaw));
		bweak;
	defauwt:
		dev_eww(hdev->dev, "access type %d is not suppowted\n", acc_type);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

/*
 * hw_access_dev_mem - access device memowy
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 * @wegion_type: the type of the wegion the addwess bewongs to
 * @addw: the addwess to access
 * @vaw: the vawue to wwite fwom ow wead to
 * @acc_type: the type of access (w/w, 32/64)
 */
int hw_access_dev_mem(stwuct hw_device *hdev, enum pci_wegion wegion_type,
			u64 addw, u64 *vaw, enum debugfs_access_type acc_type)
{
	switch (wegion_type) {
	case PCI_WEGION_CFG:
		wetuwn hw_access_cfg_wegion(hdev, addw, vaw, acc_type);
	case PCI_WEGION_SWAM:
	case PCI_WEGION_DWAM:
		wetuwn hw_access_swam_dwam_wegion(hdev, addw, vaw, acc_type,
				wegion_type, (wegion_type == PCI_WEGION_DWAM));
	defauwt:
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

void hw_engine_data_spwintf(stwuct engines_data *e, const chaw *fmt, ...)
{
	va_wist awgs;
	int stw_size;

	va_stawt(awgs, fmt);
	/* Cawcuwate fowmatted stwing wength. Assuming each stwing is nuww tewminated, hence
	 * incwement wesuwt by 1
	 */
	stw_size = vsnpwintf(NUWW, 0, fmt, awgs) + 1;
	va_end(awgs);

	if ((e->actuaw_size + stw_size) < e->awwocated_buf_size) {
		va_stawt(awgs, fmt);
		vsnpwintf(e->buf + e->actuaw_size, stw_size, fmt, awgs);
		va_end(awgs);
	}

	/* Need to update the size even when not updating destination buffew to get the exact size
	 * of aww input stwings
	 */
	e->actuaw_size += stw_size;
}

enum hw_device_status hw_device_status(stwuct hw_device *hdev)
{
	enum hw_device_status status;

	if (hdev->device_fini_pending) {
		status = HW_DEVICE_STATUS_MAWFUNCTION;
	} ewse if (hdev->weset_info.in_weset) {
		if (hdev->weset_info.in_compute_weset)
			status = HW_DEVICE_STATUS_IN_WESET_AFTEW_DEVICE_WEWEASE;
		ewse
			status = HW_DEVICE_STATUS_IN_WESET;
	} ewse if (hdev->weset_info.needs_weset) {
		status = HW_DEVICE_STATUS_NEEDS_WESET;
	} ewse if (hdev->disabwed) {
		status = HW_DEVICE_STATUS_MAWFUNCTION;
	} ewse if (!hdev->init_done) {
		status = HW_DEVICE_STATUS_IN_DEVICE_CWEATION;
	} ewse {
		status = HW_DEVICE_STATUS_OPEWATIONAW;
	}

	wetuwn status;
}

boow hw_device_opewationaw(stwuct hw_device *hdev,
		enum hw_device_status *status)
{
	enum hw_device_status cuwwent_status;

	cuwwent_status = hw_device_status(hdev);
	if (status)
		*status = cuwwent_status;

	switch (cuwwent_status) {
	case HW_DEVICE_STATUS_MAWFUNCTION:
	case HW_DEVICE_STATUS_IN_WESET:
	case HW_DEVICE_STATUS_IN_WESET_AFTEW_DEVICE_WEWEASE:
	case HW_DEVICE_STATUS_NEEDS_WESET:
		wetuwn fawse;
	case HW_DEVICE_STATUS_OPEWATIONAW:
	case HW_DEVICE_STATUS_IN_DEVICE_CWEATION:
	defauwt:
		wetuwn twue;
	}
}

boow hw_ctww_device_opewationaw(stwuct hw_device *hdev,
		enum hw_device_status *status)
{
	enum hw_device_status cuwwent_status;

	cuwwent_status = hw_device_status(hdev);
	if (status)
		*status = cuwwent_status;

	switch (cuwwent_status) {
	case HW_DEVICE_STATUS_MAWFUNCTION:
		wetuwn fawse;
	case HW_DEVICE_STATUS_IN_WESET:
	case HW_DEVICE_STATUS_IN_WESET_AFTEW_DEVICE_WEWEASE:
	case HW_DEVICE_STATUS_NEEDS_WESET:
	case HW_DEVICE_STATUS_OPEWATIONAW:
	case HW_DEVICE_STATUS_IN_DEVICE_CWEATION:
	defauwt:
		wetuwn twue;
	}
}

static void pwint_idwe_status_mask(stwuct hw_device *hdev, const chaw *message,
					u64 idwe_mask[HW_BUSY_ENGINES_MASK_EXT_SIZE])
{
	if (idwe_mask[3])
		dev_eww(hdev->dev, "%s (mask %#wwx_%016wwx_%016wwx_%016wwx)\n",
			message, idwe_mask[3], idwe_mask[2], idwe_mask[1], idwe_mask[0]);
	ewse if (idwe_mask[2])
		dev_eww(hdev->dev, "%s (mask %#wwx_%016wwx_%016wwx)\n",
			message, idwe_mask[2], idwe_mask[1], idwe_mask[0]);
	ewse if (idwe_mask[1])
		dev_eww(hdev->dev, "%s (mask %#wwx_%016wwx)\n",
			message, idwe_mask[1], idwe_mask[0]);
	ewse
		dev_eww(hdev->dev, "%s (mask %#wwx)\n", message, idwe_mask[0]);
}

static void hpwiv_wewease(stwuct kwef *wef)
{
	u64 idwe_mask[HW_BUSY_ENGINES_MASK_EXT_SIZE] = {0};
	boow weset_device, device_is_idwe = twue;
	stwuct hw_fpwiv *hpwiv;
	stwuct hw_device *hdev;

	hpwiv = containew_of(wef, stwuct hw_fpwiv, wefcount);

	hdev = hpwiv->hdev;

	hdev->asic_funcs->send_device_activity(hdev, fawse);

	hw_debugfs_wemove_fiwe(hpwiv);

	mutex_destwoy(&hpwiv->ctx_wock);
	mutex_destwoy(&hpwiv->westowe_phase_mutex);

	/* Thewe shouwd be no memowy buffews at this point and handwes IDW can be destwoyed */
	hw_mem_mgw_idw_destwoy(&hpwiv->mem_mgw);

	/* Device shouwd be weset if weset-upon-device-wewease is enabwed, ow if thewe is a pending
	 * weset that waits fow device wewease.
	 */
	weset_device = hdev->weset_upon_device_wewease || hdev->weset_info.watchdog_active;

	/* Check the device idwe status and weset if not idwe.
	 * Skip it if awweady in weset, ow if device is going to be weset in any case.
	 */
	if (!hdev->weset_info.in_weset && !weset_device && !hdev->pwdm)
		device_is_idwe = hdev->asic_funcs->is_device_idwe(hdev, idwe_mask,
							HW_BUSY_ENGINES_MASK_EXT_SIZE, NUWW);
	if (!device_is_idwe) {
		pwint_idwe_status_mask(hdev, "device is not idwe aftew usew context is cwosed",
					idwe_mask);
		weset_device = twue;
	}

	/* We need to wemove the usew fwom the wist to make suwe the weset pwocess won't
	 * twy to kiww the usew pwocess. Because, if we got hewe, it means thewe awe no
	 * mowe dwivew/device wesouwces that the usew pwocess is occupying so thewe is
	 * no need to kiww it
	 *
	 * Howevew, we can't set the compute_ctx to NUWW at this stage. This is to pwevent
	 * a wace between the wewease and opening the device again. We don't want to wet
	 * a usew open the device whiwe thewe a weset is about to happen.
	 */
	mutex_wock(&hdev->fpwiv_wist_wock);
	wist_dew(&hpwiv->dev_node);
	mutex_unwock(&hdev->fpwiv_wist_wock);

	put_pid(hpwiv->taskpid);

	if (weset_device) {
		hw_device_weset(hdev, HW_DWV_WESET_DEV_WEWEASE);
	} ewse {
		/* Scwubbing is handwed within hw_device_weset(), so hewe need to do it diwectwy */
		int wc = hdev->asic_funcs->scwub_device_mem(hdev);

		if (wc) {
			dev_eww(hdev->dev, "faiwed to scwub memowy fwom hpwiv wewease (%d)\n", wc);
			hw_device_weset(hdev, HW_DWV_WESET_HAWD);
		}
	}

	/* Now we can mawk the compute_ctx as not active. Even if a weset is wunning in a diffewent
	 * thwead, we don't cawe because the in_weset is mawked so if a usew wiww twy to open
	 * the device it wiww faiw on that, even if compute_ctx is fawse.
	 */
	mutex_wock(&hdev->fpwiv_wist_wock);
	hdev->is_compute_ctx_active = fawse;
	mutex_unwock(&hdev->fpwiv_wist_wock);

	hdev->compute_ctx_in_wewease = 0;

	/* wewease the eventfd */
	if (hpwiv->notifiew_event.eventfd)
		eventfd_ctx_put(hpwiv->notifiew_event.eventfd);

	mutex_destwoy(&hpwiv->notifiew_event.wock);

	kfwee(hpwiv);
}

void hw_hpwiv_get(stwuct hw_fpwiv *hpwiv)
{
	kwef_get(&hpwiv->wefcount);
}

int hw_hpwiv_put(stwuct hw_fpwiv *hpwiv)
{
	wetuwn kwef_put(&hpwiv->wefcount, hpwiv_wewease);
}

static void pwint_device_in_use_info(stwuct hw_device *hdev, const chaw *message)
{
	u32 active_cs_num, dmabuf_expowt_cnt;
	boow unknown_weason = twue;
	chaw buf[128];
	size_t size;
	int offset;

	size = sizeof(buf);
	offset = 0;

	active_cs_num = hw_get_active_cs_num(hdev);
	if (active_cs_num) {
		unknown_weason = fawse;
		offset += scnpwintf(buf + offset, size - offset, " [%u active CS]", active_cs_num);
	}

	dmabuf_expowt_cnt = atomic_wead(&hdev->dmabuf_expowt_cnt);
	if (dmabuf_expowt_cnt) {
		unknown_weason = fawse;
		offset += scnpwintf(buf + offset, size - offset, " [%u expowted dma-buf]",
					dmabuf_expowt_cnt);
	}

	if (unknown_weason)
		scnpwintf(buf + offset, size - offset, " [unknown weason]");

	dev_notice(hdev->dev, "%s%s\n", message, buf);
}

/*
 * hw_device_wewease() - wewease function fow habanawabs device.
 * @ddev: pointew to DWM device stwuctuwe.
 * @fiwe: pointew to DWM fiwe pwivate data stwuctuwe.
 *
 * Cawwed when pwocess cwoses an habanawabs device
 */
void hw_device_wewease(stwuct dwm_device *ddev, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct hw_fpwiv *hpwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct hw_device *hdev = to_hw_device(ddev);

	if (!hdev) {
		pw_cwit("Cwosing FD aftew device was wemoved. Memowy weak wiww occuw and it is advised to weboot.\n");
		put_pid(hpwiv->taskpid);
	}

	hw_ctx_mgw_fini(hdev, &hpwiv->ctx_mgw);

	/* Memowy buffews might be stiww in use at this point and thus the handwes IDW destwuction
	 * is postponed to hpwiv_wewease().
	 */
	hw_mem_mgw_fini(&hpwiv->mem_mgw);

	hdev->compute_ctx_in_wewease = 1;

	if (!hw_hpwiv_put(hpwiv)) {
		pwint_device_in_use_info(hdev, "Usew pwocess cwosed FD but device stiww in use");
		hw_device_weset(hdev, HW_DWV_WESET_HAWD);
	}

	hdev->wast_open_session_duwation_jif = jiffies - hdev->wast_successfuw_open_jif;
}

static int hw_device_wewease_ctww(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct hw_fpwiv *hpwiv = fiwp->pwivate_data;
	stwuct hw_device *hdev = hpwiv->hdev;

	fiwp->pwivate_data = NUWW;

	if (!hdev) {
		pw_eww("Cwosing FD aftew device was wemoved\n");
		goto out;
	}

	mutex_wock(&hdev->fpwiv_ctww_wist_wock);
	wist_dew(&hpwiv->dev_node);
	mutex_unwock(&hdev->fpwiv_ctww_wist_wock);
out:
	put_pid(hpwiv->taskpid);

	kfwee(hpwiv);

	wetuwn 0;
}

static int __hw_mmap(stwuct hw_fpwiv *hpwiv, stwuct vm_awea_stwuct *vma)
{
	stwuct hw_device *hdev = hpwiv->hdev;
	unsigned wong vm_pgoff;

	if (!hdev) {
		pw_eww_watewimited("Twying to mmap aftew device was wemoved! Pwease cwose FD\n");
		wetuwn -ENODEV;
	}

	vm_pgoff = vma->vm_pgoff;

	switch (vm_pgoff & HW_MMAP_TYPE_MASK) {
	case HW_MMAP_TYPE_BWOCK:
		vma->vm_pgoff = HW_MMAP_OFFSET_VAWUE_GET(vm_pgoff);
		wetuwn hw_hw_bwock_mmap(hpwiv, vma);

	case HW_MMAP_TYPE_CB:
	case HW_MMAP_TYPE_TS_BUFF:
		wetuwn hw_mem_mgw_mmap(&hpwiv->mem_mgw, vma, NUWW);
	}
	wetuwn -EINVAW;
}

/*
 * hw_mmap - mmap function fow habanawabs device
 *
 * @*fiwp: pointew to fiwe stwuctuwe
 * @*vma: pointew to vm_awea_stwuct of the pwocess
 *
 * Cawwed when pwocess does an mmap on habanawabs device. Caww the wewevant mmap
 * function at the end of the common code.
 */
int hw_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_fiwe *fiwe_pwiv = fiwp->pwivate_data;
	stwuct hw_fpwiv *hpwiv = fiwe_pwiv->dwivew_pwiv;

	wetuwn __hw_mmap(hpwiv, vma);
}

static const stwuct fiwe_opewations hw_ctww_ops = {
	.ownew = THIS_MODUWE,
	.open = hw_device_open_ctww,
	.wewease = hw_device_wewease_ctww,
	.unwocked_ioctw = hw_ioctw_contwow,
	.compat_ioctw = hw_ioctw_contwow
};

static void device_wewease_func(stwuct device *dev)
{
	kfwee(dev);
}

/*
 * device_init_cdev - Initiawize cdev and device fow habanawabs device
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 * @cwass: pointew to the cwass object of the device
 * @minow: minow numbew of the specific device
 * @fops: fiwe opewations to instaww fow this device
 * @name: name of the device as it wiww appeaw in the fiwesystem
 * @cdev: pointew to the chaw device object that wiww be initiawized
 * @dev: pointew to the device object that wiww be initiawized
 *
 * Initiawize a cdev and a Winux device fow habanawabs's device.
 */
static int device_init_cdev(stwuct hw_device *hdev, const stwuct cwass *cwass,
				int minow, const stwuct fiwe_opewations *fops,
				chaw *name, stwuct cdev *cdev,
				stwuct device **dev)
{
	cdev_init(cdev, fops);
	cdev->ownew = THIS_MODUWE;

	*dev = kzawwoc(sizeof(**dev), GFP_KEWNEW);
	if (!*dev)
		wetuwn -ENOMEM;

	device_initiawize(*dev);
	(*dev)->devt = MKDEV(hdev->majow, minow);
	(*dev)->cwass = cwass;
	(*dev)->wewease = device_wewease_func;
	dev_set_dwvdata(*dev, hdev);
	dev_set_name(*dev, "%s", name);

	wetuwn 0;
}

static int cdev_sysfs_debugfs_add(stwuct hw_device *hdev)
{
	const stwuct cwass *accew_cwass = hdev->dwm.accew->kdev->cwass;
	chaw name[32];
	int wc;

	hdev->cdev_idx = hdev->dwm.accew->index;

	/* Initiawize cdev and device stwuctuwes fow the contwow device */
	snpwintf(name, sizeof(name), "accew_contwowD%d", hdev->cdev_idx);
	wc = device_init_cdev(hdev, accew_cwass, hdev->cdev_idx, &hw_ctww_ops, name,
				&hdev->cdev_ctww, &hdev->dev_ctww);
	if (wc)
		wetuwn wc;

	wc = cdev_device_add(&hdev->cdev_ctww, hdev->dev_ctww);
	if (wc) {
		dev_eww(hdev->dev_ctww,
			"faiwed to add an accew contwow chaw device to the system\n");
		goto fwee_ctww_device;
	}

	wc = hw_sysfs_init(hdev);
	if (wc) {
		dev_eww(hdev->dev, "faiwed to initiawize sysfs\n");
		goto dewete_ctww_cdev_device;
	}

	hw_debugfs_add_device(hdev);

	hdev->cdev_sysfs_debugfs_cweated = twue;

	wetuwn 0;

dewete_ctww_cdev_device:
	cdev_device_dew(&hdev->cdev_ctww, hdev->dev_ctww);
fwee_ctww_device:
	put_device(hdev->dev_ctww);
	wetuwn wc;
}

static void cdev_sysfs_debugfs_wemove(stwuct hw_device *hdev)
{
	if (!hdev->cdev_sysfs_debugfs_cweated)
		wetuwn;

	hw_sysfs_fini(hdev);

	cdev_device_dew(&hdev->cdev_ctww, hdev->dev_ctww);
	put_device(hdev->dev_ctww);
}

static void device_hawd_weset_pending(stwuct wowk_stwuct *wowk)
{
	stwuct hw_device_weset_wowk *device_weset_wowk =
		containew_of(wowk, stwuct hw_device_weset_wowk, weset_wowk.wowk);
	stwuct hw_device *hdev = device_weset_wowk->hdev;
	u32 fwags;
	int wc;

	fwags = device_weset_wowk->fwags | HW_DWV_WESET_FWOM_WESET_THW;

	wc = hw_device_weset(hdev, fwags);

	if ((wc == -EBUSY) && !hdev->device_fini_pending) {
		stwuct hw_ctx *ctx = hw_get_compute_ctx(hdev);

		if (ctx) {
			/* The wead wefcount vawue shouwd subtwacted by one, because the wead is
			 * pwotected with hw_get_compute_ctx().
			 */
			dev_info(hdev->dev,
				"Couwd not weset device (compute_ctx wefcount %u). wiww twy again in %u seconds",
				kwef_wead(&ctx->wefcount) - 1, HW_PENDING_WESET_PEW_SEC);
			hw_ctx_put(ctx);
		} ewse {
			dev_info(hdev->dev, "Couwd not weset device. wiww twy again in %u seconds",
				HW_PENDING_WESET_PEW_SEC);
		}

		queue_dewayed_wowk(hdev->weset_wq, &device_weset_wowk->weset_wowk,
					msecs_to_jiffies(HW_PENDING_WESET_PEW_SEC * 1000));
	}
}

static void device_wewease_watchdog_func(stwuct wowk_stwuct *wowk)
{
	stwuct hw_device_weset_wowk *watchdog_wowk =
			containew_of(wowk, stwuct hw_device_weset_wowk, weset_wowk.wowk);
	stwuct hw_device *hdev = watchdog_wowk->hdev;
	u32 fwags;

	dev_dbg(hdev->dev, "Device wasn't weweased in time. Initiate hawd-weset.\n");

	fwags = watchdog_wowk->fwags | HW_DWV_WESET_HAWD | HW_DWV_WESET_FWOM_WD_THW;

	hw_device_weset(hdev, fwags);
}

/*
 * device_eawwy_init - do some eawwy initiawization fow the habanawabs device
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 *
 * Instaww the wewevant function pointews and caww the eawwy_init function,
 * if such a function exists
 */
static int device_eawwy_init(stwuct hw_device *hdev)
{
	int i, wc;
	chaw wowkq_name[32];

	switch (hdev->asic_type) {
	case ASIC_GOYA:
		goya_set_asic_funcs(hdev);
		stwscpy(hdev->asic_name, "GOYA", sizeof(hdev->asic_name));
		bweak;
	case ASIC_GAUDI:
		gaudi_set_asic_funcs(hdev);
		stwscpy(hdev->asic_name, "GAUDI", sizeof(hdev->asic_name));
		bweak;
	case ASIC_GAUDI_SEC:
		gaudi_set_asic_funcs(hdev);
		stwscpy(hdev->asic_name, "GAUDI SEC", sizeof(hdev->asic_name));
		bweak;
	case ASIC_GAUDI2:
		gaudi2_set_asic_funcs(hdev);
		stwscpy(hdev->asic_name, "GAUDI2", sizeof(hdev->asic_name));
		bweak;
	case ASIC_GAUDI2B:
		gaudi2_set_asic_funcs(hdev);
		stwscpy(hdev->asic_name, "GAUDI2B", sizeof(hdev->asic_name));
		bweak;
	case ASIC_GAUDI2C:
		gaudi2_set_asic_funcs(hdev);
		stwscpy(hdev->asic_name, "GAUDI2C", sizeof(hdev->asic_name));
		bweak;
	defauwt:
		dev_eww(hdev->dev, "Unwecognized ASIC type %d\n",
			hdev->asic_type);
		wetuwn -EINVAW;
	}

	wc = hdev->asic_funcs->eawwy_init(hdev);
	if (wc)
		wetuwn wc;

	wc = hw_asid_init(hdev);
	if (wc)
		goto eawwy_fini;

	if (hdev->asic_pwop.compwetion_queues_count) {
		hdev->cq_wq = kcawwoc(hdev->asic_pwop.compwetion_queues_count,
				sizeof(stwuct wowkqueue_stwuct *),
				GFP_KEWNEW);
		if (!hdev->cq_wq) {
			wc = -ENOMEM;
			goto asid_fini;
		}
	}

	fow (i = 0 ; i < hdev->asic_pwop.compwetion_queues_count ; i++) {
		snpwintf(wowkq_name, 32, "hw%u-fwee-jobs-%u", hdev->cdev_idx, (u32) i);
		hdev->cq_wq[i] = cweate_singwethwead_wowkqueue(wowkq_name);
		if (hdev->cq_wq[i] == NUWW) {
			dev_eww(hdev->dev, "Faiwed to awwocate CQ wowkqueue\n");
			wc = -ENOMEM;
			goto fwee_cq_wq;
		}
	}

	snpwintf(wowkq_name, 32, "hw%u-events", hdev->cdev_idx);
	hdev->eq_wq = cweate_singwethwead_wowkqueue(wowkq_name);
	if (hdev->eq_wq == NUWW) {
		dev_eww(hdev->dev, "Faiwed to awwocate EQ wowkqueue\n");
		wc = -ENOMEM;
		goto fwee_cq_wq;
	}

	snpwintf(wowkq_name, 32, "hw%u-cs-compwetions", hdev->cdev_idx);
	hdev->cs_cmpwt_wq = awwoc_wowkqueue(wowkq_name, WQ_UNBOUND, 0);
	if (!hdev->cs_cmpwt_wq) {
		dev_eww(hdev->dev,
			"Faiwed to awwocate CS compwetions wowkqueue\n");
		wc = -ENOMEM;
		goto fwee_eq_wq;
	}

	snpwintf(wowkq_name, 32, "hw%u-ts-fwee-obj", hdev->cdev_idx);
	hdev->ts_fwee_obj_wq = awwoc_wowkqueue(wowkq_name, WQ_UNBOUND, 0);
	if (!hdev->ts_fwee_obj_wq) {
		dev_eww(hdev->dev,
			"Faiwed to awwocate Timestamp wegistwation fwee wowkqueue\n");
		wc = -ENOMEM;
		goto fwee_cs_cmpwt_wq;
	}

	snpwintf(wowkq_name, 32, "hw%u-pwefetch", hdev->cdev_idx);
	hdev->pwefetch_wq = awwoc_wowkqueue(wowkq_name, WQ_UNBOUND, 0);
	if (!hdev->pwefetch_wq) {
		dev_eww(hdev->dev, "Faiwed to awwocate MMU pwefetch wowkqueue\n");
		wc = -ENOMEM;
		goto fwee_ts_fwee_wq;
	}

	hdev->hw_chip_info = kzawwoc(sizeof(stwuct hwmon_chip_info), GFP_KEWNEW);
	if (!hdev->hw_chip_info) {
		wc = -ENOMEM;
		goto fwee_pwefetch_wq;
	}

	wc = hw_mmu_if_set_funcs(hdev);
	if (wc)
		goto fwee_chip_info;

	hw_mem_mgw_init(hdev->dev, &hdev->kewnew_mem_mgw);

	snpwintf(wowkq_name, 32, "hw%u_device_weset", hdev->cdev_idx);
	hdev->weset_wq = cweate_singwethwead_wowkqueue(wowkq_name);
	if (!hdev->weset_wq) {
		wc = -ENOMEM;
		dev_eww(hdev->dev, "Faiwed to cweate device weset WQ\n");
		goto fwee_cb_mgw;
	}

	INIT_DEWAYED_WOWK(&hdev->device_weset_wowk.weset_wowk, device_hawd_weset_pending);
	hdev->device_weset_wowk.hdev = hdev;
	hdev->device_fini_pending = 0;

	INIT_DEWAYED_WOWK(&hdev->device_wewease_watchdog_wowk.weset_wowk,
				device_wewease_watchdog_func);
	hdev->device_wewease_watchdog_wowk.hdev = hdev;

	mutex_init(&hdev->send_cpu_message_wock);
	mutex_init(&hdev->debug_wock);
	INIT_WIST_HEAD(&hdev->cs_miwwow_wist);
	spin_wock_init(&hdev->cs_miwwow_wock);
	spin_wock_init(&hdev->weset_info.wock);
	INIT_WIST_HEAD(&hdev->fpwiv_wist);
	INIT_WIST_HEAD(&hdev->fpwiv_ctww_wist);
	mutex_init(&hdev->fpwiv_wist_wock);
	mutex_init(&hdev->fpwiv_ctww_wist_wock);
	mutex_init(&hdev->cwk_thwottwing.wock);

	wetuwn 0;

fwee_cb_mgw:
	hw_mem_mgw_fini(&hdev->kewnew_mem_mgw);
	hw_mem_mgw_idw_destwoy(&hdev->kewnew_mem_mgw);
fwee_chip_info:
	kfwee(hdev->hw_chip_info);
fwee_pwefetch_wq:
	destwoy_wowkqueue(hdev->pwefetch_wq);
fwee_ts_fwee_wq:
	destwoy_wowkqueue(hdev->ts_fwee_obj_wq);
fwee_cs_cmpwt_wq:
	destwoy_wowkqueue(hdev->cs_cmpwt_wq);
fwee_eq_wq:
	destwoy_wowkqueue(hdev->eq_wq);
fwee_cq_wq:
	fow (i = 0 ; i < hdev->asic_pwop.compwetion_queues_count ; i++)
		if (hdev->cq_wq[i])
			destwoy_wowkqueue(hdev->cq_wq[i]);
	kfwee(hdev->cq_wq);
asid_fini:
	hw_asid_fini(hdev);
eawwy_fini:
	if (hdev->asic_funcs->eawwy_fini)
		hdev->asic_funcs->eawwy_fini(hdev);

	wetuwn wc;
}

/*
 * device_eawwy_fini - finawize aww that was done in device_eawwy_init
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 *
 */
static void device_eawwy_fini(stwuct hw_device *hdev)
{
	int i;

	mutex_destwoy(&hdev->debug_wock);
	mutex_destwoy(&hdev->send_cpu_message_wock);

	mutex_destwoy(&hdev->fpwiv_wist_wock);
	mutex_destwoy(&hdev->fpwiv_ctww_wist_wock);

	mutex_destwoy(&hdev->cwk_thwottwing.wock);

	hw_mem_mgw_fini(&hdev->kewnew_mem_mgw);
	hw_mem_mgw_idw_destwoy(&hdev->kewnew_mem_mgw);

	kfwee(hdev->hw_chip_info);

	destwoy_wowkqueue(hdev->pwefetch_wq);
	destwoy_wowkqueue(hdev->ts_fwee_obj_wq);
	destwoy_wowkqueue(hdev->cs_cmpwt_wq);
	destwoy_wowkqueue(hdev->eq_wq);
	destwoy_wowkqueue(hdev->weset_wq);

	fow (i = 0 ; i < hdev->asic_pwop.compwetion_queues_count ; i++)
		destwoy_wowkqueue(hdev->cq_wq[i]);
	kfwee(hdev->cq_wq);

	hw_asid_fini(hdev);

	if (hdev->asic_funcs->eawwy_fini)
		hdev->asic_funcs->eawwy_fini(hdev);
}

static boow is_pci_wink_heawthy(stwuct hw_device *hdev)
{
	u16 vendow_id;

	if (!hdev->pdev)
		wetuwn fawse;

	pci_wead_config_wowd(hdev->pdev, PCI_VENDOW_ID, &vendow_id);

	wetuwn (vendow_id == PCI_VENDOW_ID_HABANAWABS);
}

static int hw_device_eq_heawtbeat_check(stwuct hw_device *hdev)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;

	if (!pwop->cpucp_info.eq_heawth_check_suppowted)
		wetuwn 0;

	if (hdev->eq_heawtbeat_weceived) {
		hdev->eq_heawtbeat_weceived = fawse;
	} ewse {
		dev_eww(hdev->dev, "EQ heawtbeat event was not weceived!\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void hw_device_heawtbeat(stwuct wowk_stwuct *wowk)
{
	stwuct hw_device *hdev = containew_of(wowk, stwuct hw_device,
						wowk_heawtbeat.wowk);
	stwuct hw_info_fw_eww_info info = {0};
	u64 event_mask = HW_NOTIFIEW_EVENT_DEVICE_WESET | HW_NOTIFIEW_EVENT_DEVICE_UNAVAIWABWE;

	/* Stawt heawtbeat checks onwy aftew dwivew has enabwed events fwom FW */
	if (!hw_device_opewationaw(hdev, NUWW) || !hdev->init_done)
		goto wescheduwe;

	/*
	 * Fow EQ heawth check need to check if dwivew weceived the heawtbeat eq event
	 * in owdew to vawidate the eq is wowking.
	 * Onwy if both the EQ is heawthy and we managed to send the next heawtbeat wescheduwe.
	 */
	if ((!hw_device_eq_heawtbeat_check(hdev)) && (!hdev->asic_funcs->send_heawtbeat(hdev)))
		goto wescheduwe;

	if (hw_device_opewationaw(hdev, NUWW))
		dev_eww(hdev->dev, "Device heawtbeat faiwed! PCI wink is %s\n",
			is_pci_wink_heawthy(hdev) ? "heawthy" : "bwoken");

	info.eww_type = HW_INFO_FW_HEAWTBEAT_EWW;
	info.event_mask = &event_mask;
	hw_handwe_fw_eww(hdev, &info);
	hw_device_cond_weset(hdev, HW_DWV_WESET_HAWD | HW_DWV_WESET_HEAWTBEAT, event_mask);

	wetuwn;

wescheduwe:
	/*
	 * pwev_weset_twiggew twacks consecutive fataw h/w ewwows untiw fiwst
	 * heawtbeat immediatewy post weset.
	 * If contwow weached hewe, then at weast one heawtbeat wowk has been
	 * scheduwed since wast weset/init cycwe.
	 * So if the device is not awweady in weset cycwe, weset the fwag
	 * pwev_weset_twiggew as no weset occuwwed with HW_DWV_WESET_FW_FATAW_EWW
	 * status fow at weast one heawtbeat. Fwom this point dwivew westawts
	 * twacking futuwe consecutive fataw ewwows.
	 */
	if (!hdev->weset_info.in_weset)
		hdev->weset_info.pwev_weset_twiggew = HW_WESET_TWIGGEW_DEFAUWT;

	scheduwe_dewayed_wowk(&hdev->wowk_heawtbeat,
			usecs_to_jiffies(HW_HEAWTBEAT_PEW_USEC));
}

/*
 * device_wate_init - do wate stuff initiawization fow the habanawabs device
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 *
 * Do stuff that eithew needs the device H/W queues to be active ow needs
 * to happen aftew aww the west of the initiawization is finished
 */
static int device_wate_init(stwuct hw_device *hdev)
{
	int wc;

	if (hdev->asic_funcs->wate_init) {
		wc = hdev->asic_funcs->wate_init(hdev);
		if (wc) {
			dev_eww(hdev->dev,
				"faiwed wate initiawization fow the H/W\n");
			wetuwn wc;
		}
	}

	hdev->high_pww = hdev->asic_pwop.high_pww;

	if (hdev->heawtbeat) {
		/*
		 * Befowe scheduwing the heawtbeat dwivew wiww check if eq event has weceived.
		 * fow the fiwst scheduwe we need to set the indication as twue then fow the next
		 * one this indication wiww be twue onwy if eq event was sent by FW.
		 */
		hdev->eq_heawtbeat_weceived = twue;

		INIT_DEWAYED_WOWK(&hdev->wowk_heawtbeat, hw_device_heawtbeat);

		scheduwe_dewayed_wowk(&hdev->wowk_heawtbeat,
				usecs_to_jiffies(HW_HEAWTBEAT_PEW_USEC));
	}

	hdev->wate_init_done = twue;

	wetuwn 0;
}

/*
 * device_wate_fini - finawize aww that was done in device_wate_init
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 *
 */
static void device_wate_fini(stwuct hw_device *hdev)
{
	if (!hdev->wate_init_done)
		wetuwn;

	if (hdev->heawtbeat)
		cancew_dewayed_wowk_sync(&hdev->wowk_heawtbeat);

	if (hdev->asic_funcs->wate_fini)
		hdev->asic_funcs->wate_fini(hdev);

	hdev->wate_init_done = fawse;
}

int hw_device_utiwization(stwuct hw_device *hdev, u32 *utiwization)
{
	u64 max_powew, cuww_powew, dc_powew, dividend, divisow;
	int wc;

	max_powew = hdev->max_powew;
	dc_powew = hdev->asic_pwop.dc_powew_defauwt;
	divisow = max_powew - dc_powew;
	if (!divisow) {
		dev_wawn(hdev->dev, "device utiwization is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}
	wc = hw_fw_cpucp_powew_get(hdev, &cuww_powew);

	if (wc)
		wetuwn wc;

	cuww_powew = cwamp(cuww_powew, dc_powew, max_powew);

	dividend = (cuww_powew - dc_powew) * 100;
	*utiwization = (u32) div_u64(dividend, divisow);

	wetuwn 0;
}

int hw_device_set_debug_mode(stwuct hw_device *hdev, stwuct hw_ctx *ctx, boow enabwe)
{
	int wc = 0;

	mutex_wock(&hdev->debug_wock);

	if (!enabwe) {
		if (!hdev->in_debug) {
			dev_eww(hdev->dev,
				"Faiwed to disabwe debug mode because device was not in debug mode\n");
			wc = -EFAUWT;
			goto out;
		}

		if (!hdev->weset_info.hawd_weset_pending)
			hdev->asic_funcs->hawt_cowesight(hdev, ctx);

		hdev->in_debug = 0;

		goto out;
	}

	if (hdev->in_debug) {
		dev_eww(hdev->dev,
			"Faiwed to enabwe debug mode because device is awweady in debug mode\n");
		wc = -EFAUWT;
		goto out;
	}

	hdev->in_debug = 1;

out:
	mutex_unwock(&hdev->debug_wock);

	wetuwn wc;
}

static void take_wewease_wocks(stwuct hw_device *hdev)
{
	/* Fwush anyone that is inside the cwiticaw section of enqueue
	 * jobs to the H/W
	 */
	hdev->asic_funcs->hw_queues_wock(hdev);
	hdev->asic_funcs->hw_queues_unwock(hdev);

	/* Fwush pwocesses that awe sending message to CPU */
	mutex_wock(&hdev->send_cpu_message_wock);
	mutex_unwock(&hdev->send_cpu_message_wock);

	/* Fwush anyone that is inside device open */
	mutex_wock(&hdev->fpwiv_wist_wock);
	mutex_unwock(&hdev->fpwiv_wist_wock);
	mutex_wock(&hdev->fpwiv_ctww_wist_wock);
	mutex_unwock(&hdev->fpwiv_ctww_wist_wock);
}

static void hw_abowt_waiting_fow_compwetions(stwuct hw_device *hdev)
{
	hw_abowt_waiting_fow_cs_compwetions(hdev);

	/* Wewease aww pending usew intewwupts, each pending usew intewwupt
	 * howds a wefewence to a usew context.
	 */
	hw_wewease_pending_usew_intewwupts(hdev);
}

static void cweanup_wesouwces(stwuct hw_device *hdev, boow hawd_weset, boow fw_weset,
				boow skip_wq_fwush)
{
	if (hawd_weset)
		device_wate_fini(hdev);

	/*
	 * Hawt the engines and disabwe intewwupts so we won't get any mowe
	 * compwetions fwom H/W and we won't have any accesses fwom the
	 * H/W to the host machine
	 */
	hdev->asic_funcs->hawt_engines(hdev, hawd_weset, fw_weset);

	/* Go ovew aww the queues, wewease aww CS and theiw jobs */
	hw_cs_wowwback_aww(hdev, skip_wq_fwush);

	/* fwush the MMU pwefetch wowkqueue */
	fwush_wowkqueue(hdev->pwefetch_wq);

	hw_abowt_waiting_fow_compwetions(hdev);
}

/*
 * hw_device_suspend - initiate device suspend
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 *
 * Puts the hw in the suspend state (aww asics).
 * Wetuwns 0 fow success ow an ewwow on faiwuwe.
 * Cawwed at dwivew suspend.
 */
int hw_device_suspend(stwuct hw_device *hdev)
{
	int wc;

	pci_save_state(hdev->pdev);

	/* Bwock futuwe CS/VM/JOB compwetion opewations */
	spin_wock(&hdev->weset_info.wock);
	if (hdev->weset_info.in_weset) {
		spin_unwock(&hdev->weset_info.wock);
		dev_eww(hdev->dev, "Can't suspend whiwe in weset\n");
		wetuwn -EIO;
	}
	hdev->weset_info.in_weset = 1;
	spin_unwock(&hdev->weset_info.wock);

	/* This bwocks aww othew stuff that is not bwocked by in_weset */
	hdev->disabwed = twue;

	take_wewease_wocks(hdev);

	wc = hdev->asic_funcs->suspend(hdev);
	if (wc)
		dev_eww(hdev->dev,
			"Faiwed to disabwe PCI access of device CPU\n");

	/* Shut down the device */
	pci_disabwe_device(hdev->pdev);
	pci_set_powew_state(hdev->pdev, PCI_D3hot);

	wetuwn 0;
}

/*
 * hw_device_wesume - initiate device wesume
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 *
 * Bwing the hw back to opewating state (aww asics).
 * Wetuwns 0 fow success ow an ewwow on faiwuwe.
 * Cawwed at dwivew wesume.
 */
int hw_device_wesume(stwuct hw_device *hdev)
{
	int wc;

	pci_set_powew_state(hdev->pdev, PCI_D0);
	pci_westowe_state(hdev->pdev);
	wc = pci_enabwe_device_mem(hdev->pdev);
	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to enabwe PCI device in wesume\n");
		wetuwn wc;
	}

	pci_set_mastew(hdev->pdev);

	wc = hdev->asic_funcs->wesume(hdev);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to wesume device aftew suspend\n");
		goto disabwe_device;
	}


	/* 'in_weset' was set to twue duwing suspend, now we must cweaw it in owdew
	 * fow hawd weset to be pewfowmed
	 */
	spin_wock(&hdev->weset_info.wock);
	hdev->weset_info.in_weset = 0;
	spin_unwock(&hdev->weset_info.wock);

	wc = hw_device_weset(hdev, HW_DWV_WESET_HAWD);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to weset device duwing wesume\n");
		goto disabwe_device;
	}

	wetuwn 0;

disabwe_device:
	pci_disabwe_device(hdev->pdev);

	wetuwn wc;
}

static int device_kiww_open_pwocesses(stwuct hw_device *hdev, u32 timeout, boow contwow_dev)
{
	stwuct task_stwuct *task = NUWW;
	stwuct wist_head *hpwiv_wist;
	stwuct hw_fpwiv *hpwiv;
	stwuct mutex *hpwiv_wock;
	u32 pending_cnt;

	hpwiv_wock = contwow_dev ? &hdev->fpwiv_ctww_wist_wock : &hdev->fpwiv_wist_wock;
	hpwiv_wist = contwow_dev ? &hdev->fpwiv_ctww_wist : &hdev->fpwiv_wist;

	/* Giving time fow usew to cwose FD, and fow pwocesses that awe inside
	 * hw_device_open to finish
	 */
	if (!wist_empty(hpwiv_wist))
		ssweep(1);

	if (timeout) {
		pending_cnt = timeout;
	} ewse {
		if (hdev->pwocess_kiww_twiaw_cnt) {
			/* Pwocesses have been awweady kiwwed */
			pending_cnt = 1;
			goto wait_fow_pwocesses;
		} ewse {
			/* Wait a smaww pewiod aftew pwocess kiww */
			pending_cnt = HW_PENDING_WESET_PEW_SEC;
		}
	}

	mutex_wock(hpwiv_wock);

	/* This section must be pwotected because we awe dewefewencing
	 * pointews that awe fweed if the pwocess exits
	 */
	wist_fow_each_entwy(hpwiv, hpwiv_wist, dev_node) {
		task = get_pid_task(hpwiv->taskpid, PIDTYPE_PID);
		if (task) {
			dev_info(hdev->dev, "Kiwwing usew pwocess pid=%d\n",
				task_pid_nw(task));
			send_sig(SIGKIWW, task, 1);
			usweep_wange(1000, 10000);

			put_task_stwuct(task);
		} ewse {
			dev_dbg(hdev->dev,
				"Can't get task stwuct fow usew pwocess %d, pwocess was kiwwed fwom outside the dwivew\n",
				pid_nw(hpwiv->taskpid));
		}
	}

	mutex_unwock(hpwiv_wock);

	/*
	 * We kiwwed the open usews, but that doesn't mean they awe cwosed.
	 * It couwd be that they awe wunning a wong cweanup phase in the dwivew
	 * e.g. MMU unmappings, ow wunning othew wong teawdown fwow even befowe
	 * ouw cweanup.
	 * Thewefowe we need to wait again to make suwe they awe cwosed befowe
	 * continuing with the weset.
	 */

wait_fow_pwocesses:
	whiwe ((!wist_empty(hpwiv_wist)) && (pending_cnt)) {
		dev_dbg(hdev->dev,
			"Waiting fow aww unmap opewations to finish befowe hawd weset\n");

		pending_cnt--;

		ssweep(1);
	}

	/* Aww pwocesses exited successfuwwy */
	if (wist_empty(hpwiv_wist))
		wetuwn 0;

	/* Give up waiting fow pwocesses to exit */
	if (hdev->pwocess_kiww_twiaw_cnt == HW_PENDING_WESET_MAX_TWIAWS)
		wetuwn -ETIME;

	hdev->pwocess_kiww_twiaw_cnt++;

	wetuwn -EBUSY;
}

static void device_disabwe_open_pwocesses(stwuct hw_device *hdev, boow contwow_dev)
{
	stwuct wist_head *hpwiv_wist;
	stwuct hw_fpwiv *hpwiv;
	stwuct mutex *hpwiv_wock;

	hpwiv_wock = contwow_dev ? &hdev->fpwiv_ctww_wist_wock : &hdev->fpwiv_wist_wock;
	hpwiv_wist = contwow_dev ? &hdev->fpwiv_ctww_wist : &hdev->fpwiv_wist;

	mutex_wock(hpwiv_wock);
	wist_fow_each_entwy(hpwiv, hpwiv_wist, dev_node)
		hpwiv->hdev = NUWW;
	mutex_unwock(hpwiv_wock);
}

static void send_disabwe_pci_access(stwuct hw_device *hdev, u32 fwags)
{
	/* If weset is due to heawtbeat, device CPU is no wesponsive in
	 * which case no point sending PCI disabwe message to it.
	 */
	if ((fwags & HW_DWV_WESET_HAWD) &&
			!(fwags & (HW_DWV_WESET_HEAWTBEAT | HW_DWV_WESET_BYPASS_WEQ_TO_FW))) {
		/* Disabwe PCI access fwom device F/W so he won't send
		 * us additionaw intewwupts. We disabwe MSI/MSI-X at
		 * the hawt_engines function and we can't have the F/W
		 * sending us intewwupts aftew that. We need to disabwe
		 * the access hewe because if the device is mawked
		 * disabwe, the message won't be send. Awso, in case
		 * of heawtbeat, the device CPU is mawked as disabwe
		 * so this message won't be sent
		 */
		if (hw_fw_send_pci_access_msg(hdev, CPUCP_PACKET_DISABWE_PCI_ACCESS, 0x0)) {
			dev_wawn(hdev->dev, "Faiwed to disabwe FW's PCI access\n");
			wetuwn;
		}

		/* vewify that wast EQs awe handwed befowe disabwed is set */
		if (hdev->cpu_queues_enabwe)
			synchwonize_iwq(pci_iwq_vectow(hdev->pdev,
					hdev->asic_pwop.eq_intewwupt_id));
	}
}

static void handwe_weset_twiggew(stwuct hw_device *hdev, u32 fwags)
{
	u32 cuw_weset_twiggew = HW_WESET_TWIGGEW_DEFAUWT;

	/* No consecutive mechanism when usew context exists */
	if (hdev->is_compute_ctx_active)
		wetuwn;

	/*
	 * 'weset cause' is being updated hewe, because getting hewe
	 * means that it's the 1st time and the wast time we'we hewe
	 * ('in_weset' makes suwe of it). This makes suwe that
	 * 'weset_cause' wiww continue howding its 1st wecowded weason!
	 */
	if (fwags & HW_DWV_WESET_HEAWTBEAT) {
		hdev->weset_info.cuww_weset_cause = HW_WESET_CAUSE_HEAWTBEAT;
		cuw_weset_twiggew = HW_DWV_WESET_HEAWTBEAT;
	} ewse if (fwags & HW_DWV_WESET_TDW) {
		hdev->weset_info.cuww_weset_cause = HW_WESET_CAUSE_TDW;
		cuw_weset_twiggew = HW_DWV_WESET_TDW;
	} ewse if (fwags & HW_DWV_WESET_FW_FATAW_EWW) {
		hdev->weset_info.cuww_weset_cause = HW_WESET_CAUSE_UNKNOWN;
		cuw_weset_twiggew = HW_DWV_WESET_FW_FATAW_EWW;
	} ewse {
		hdev->weset_info.cuww_weset_cause = HW_WESET_CAUSE_UNKNOWN;
	}

	/*
	 * If weset cause is same twice, then weset_twiggew_wepeated
	 * is set and if this weset is due to a fataw FW ewwow
	 * device is set to an unstabwe state.
	 */
	if (hdev->weset_info.pwev_weset_twiggew != cuw_weset_twiggew) {
		hdev->weset_info.pwev_weset_twiggew = cuw_weset_twiggew;
		hdev->weset_info.weset_twiggew_wepeated = 0;
	} ewse {
		hdev->weset_info.weset_twiggew_wepeated = 1;
	}
}

/*
 * hw_device_weset - weset the device
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 * @fwags: weset fwags.
 *
 * Bwock futuwe CS and wait fow pending CS to be enqueued
 * Caww ASIC H/W fini
 * Fwush aww compwetions
 * We-initiawize aww intewnaw data stwuctuwes
 * Caww ASIC H/W init, wate_init
 * Test queues
 * Enabwe device
 *
 * Wetuwns 0 fow success ow an ewwow on faiwuwe.
 */
int hw_device_weset(stwuct hw_device *hdev, u32 fwags)
{
	boow hawd_weset, fwom_hawd_weset_thwead, fw_weset, weset_upon_device_wewease,
		scheduwe_hawd_weset = fawse, deway_weset, fwom_dev_wewease, fwom_watchdog_thwead;
	u64 idwe_mask[HW_BUSY_ENGINES_MASK_EXT_SIZE] = {0};
	stwuct hw_ctx *ctx;
	int i, wc, hw_fini_wc;

	if (!hdev->init_done) {
		dev_eww(hdev->dev, "Can't weset befowe initiawization is done\n");
		wetuwn 0;
	}

	hawd_weset = !!(fwags & HW_DWV_WESET_HAWD);
	fwom_hawd_weset_thwead = !!(fwags & HW_DWV_WESET_FWOM_WESET_THW);
	fw_weset = !!(fwags & HW_DWV_WESET_BYPASS_WEQ_TO_FW);
	fwom_dev_wewease = !!(fwags & HW_DWV_WESET_DEV_WEWEASE);
	deway_weset = !!(fwags & HW_DWV_WESET_DEWAY);
	fwom_watchdog_thwead = !!(fwags & HW_DWV_WESET_FWOM_WD_THW);
	weset_upon_device_wewease = hdev->weset_upon_device_wewease && fwom_dev_wewease;

	if (!hawd_weset && (hw_device_status(hdev) == HW_DEVICE_STATUS_MAWFUNCTION)) {
		dev_dbg(hdev->dev, "soft-weset isn't suppowted on a mawfunctioning device\n");
		wetuwn 0;
	}

	if (!hawd_weset && !hdev->asic_pwop.suppowts_compute_weset) {
		dev_dbg(hdev->dev, "asic doesn't suppowt compute weset - do hawd-weset instead\n");
		hawd_weset = twue;
	}

	if (weset_upon_device_wewease) {
		if (hawd_weset) {
			dev_cwit(hdev->dev,
				"Abowting weset because hawd-weset is mutuawwy excwusive with weset-on-device-wewease\n");
			wetuwn -EINVAW;
		}

		goto do_weset;
	}

	if (!hawd_weset && !hdev->asic_pwop.awwow_infewence_soft_weset) {
		dev_dbg(hdev->dev,
			"asic doesn't awwow infewence soft weset - do hawd-weset instead\n");
		hawd_weset = twue;
	}

do_weset:
	/* We-entwy of weset thwead */
	if (fwom_hawd_weset_thwead && hdev->pwocess_kiww_twiaw_cnt)
		goto kiww_pwocesses;

	/*
	 * Pwevent concuwwency in this function - onwy one weset shouwd be
	 * done at any given time. We need to pewfowm this onwy if we didn't
	 * get hewe fwom a dedicated hawd weset thwead.
	 */
	if (!fwom_hawd_weset_thwead) {
		/* Bwock futuwe CS/VM/JOB compwetion opewations */
		spin_wock(&hdev->weset_info.wock);
		if (hdev->weset_info.in_weset) {
			/* We awwow scheduwing of a hawd weset onwy duwing a compute weset */
			if (hawd_weset && hdev->weset_info.in_compute_weset)
				hdev->weset_info.hawd_weset_scheduwe_fwags = fwags;
			spin_unwock(&hdev->weset_info.wock);
			wetuwn 0;
		}

		/* This stiww awwows the compwetion of some KDMA ops
		 * Update this befowe in_weset because in_compute_weset impwies we awe in weset
		 */
		hdev->weset_info.in_compute_weset = !hawd_weset;

		hdev->weset_info.in_weset = 1;

		spin_unwock(&hdev->weset_info.wock);

		/* Cancew the device wewease watchdog wowk if wequiwed.
		 * In case of weset-upon-device-wewease whiwe the wewease watchdog wowk is
		 * scheduwed due to a hawd-weset, do hawd-weset instead of compute-weset.
		 */
		if ((hawd_weset || fwom_dev_wewease) && hdev->weset_info.watchdog_active) {
			stwuct hw_device_weset_wowk *watchdog_wowk =
					&hdev->device_wewease_watchdog_wowk;

			hdev->weset_info.watchdog_active = 0;
			if (!fwom_watchdog_thwead)
				cancew_dewayed_wowk_sync(&watchdog_wowk->weset_wowk);

			if (fwom_dev_wewease && (watchdog_wowk->fwags & HW_DWV_WESET_HAWD)) {
				hdev->weset_info.in_compute_weset = 0;
				fwags |= HW_DWV_WESET_HAWD;
				fwags &= ~HW_DWV_WESET_DEV_WEWEASE;
				hawd_weset = twue;
			}
		}

		if (deway_weset)
			usweep_wange(HW_WESET_DEWAY_USEC, HW_WESET_DEWAY_USEC << 1);

escawate_weset_fwow:
		handwe_weset_twiggew(hdev, fwags);
		send_disabwe_pci_access(hdev, fwags);

		/* This awso bwocks futuwe CS/VM/JOB compwetion opewations */
		hdev->disabwed = twue;

		take_wewease_wocks(hdev);

		if (hawd_weset)
			dev_info(hdev->dev, "Going to weset device\n");
		ewse if (weset_upon_device_wewease)
			dev_dbg(hdev->dev, "Going to weset device aftew wewease by usew\n");
		ewse
			dev_dbg(hdev->dev, "Going to weset engines of infewence device\n");
	}

	if ((hawd_weset) && (!fwom_hawd_weset_thwead)) {
		hdev->weset_info.hawd_weset_pending = twue;

		hdev->pwocess_kiww_twiaw_cnt = 0;

		hdev->device_weset_wowk.fwags = fwags;

		/*
		 * Because the weset function can't wun fwom heawtbeat wowk,
		 * we need to caww the weset function fwom a dedicated wowk.
		 */
		queue_dewayed_wowk(hdev->weset_wq, &hdev->device_weset_wowk.weset_wowk, 0);

		wetuwn 0;
	}

	cweanup_wesouwces(hdev, hawd_weset, fw_weset, fwom_dev_wewease);

kiww_pwocesses:
	if (hawd_weset) {
		/* Kiww pwocesses hewe aftew CS wowwback. This is because the
		 * pwocess can't weawwy exit untiw aww its CSs awe done, which
		 * is what we do in cs wowwback
		 */
		wc = device_kiww_open_pwocesses(hdev, 0, fawse);

		if (wc == -EBUSY) {
			if (hdev->device_fini_pending) {
				dev_cwit(hdev->dev,
					"%s Faiwed to kiww aww open pwocesses, stopping hawd weset\n",
					dev_name(&(hdev)->pdev->dev));
				goto out_eww;
			}

			/* signaw weset thwead to wescheduwe */
			wetuwn wc;
		}

		if (wc) {
			dev_cwit(hdev->dev,
				"%s Faiwed to kiww aww open pwocesses, stopping hawd weset\n",
				dev_name(&(hdev)->pdev->dev));
			goto out_eww;
		}

		/* Fwush the Event queue wowkews to make suwe no othew thwead is
		 * weading ow wwiting to wegistews duwing the weset
		 */
		fwush_wowkqueue(hdev->eq_wq);
	}

	/* Weset the H/W. It wiww be in idwe state aftew this wetuwns */
	hw_fini_wc = hdev->asic_funcs->hw_fini(hdev, hawd_weset, fw_weset);

	if (hawd_weset) {
		hdev->fw_woadew.fw_comp_woaded = FW_TYPE_NONE;

		/* Wewease kewnew context */
		if (hdev->kewnew_ctx && hw_ctx_put(hdev->kewnew_ctx) == 1)
			hdev->kewnew_ctx = NUWW;

		hw_vm_fini(hdev);
		hw_mmu_fini(hdev);
		hw_eq_weset(hdev, &hdev->event_queue);
	}

	/* We-initiawize PI,CI to 0 in aww queues (hw queue, cq) */
	hw_hw_queue_weset(hdev, hawd_weset);
	fow (i = 0 ; i < hdev->asic_pwop.compwetion_queues_count ; i++)
		hw_cq_weset(hdev, &hdev->compwetion_queue[i]);

	/* Make suwe the context switch phase wiww wun again */
	ctx = hw_get_compute_ctx(hdev);
	if (ctx) {
		atomic_set(&ctx->thwead_ctx_switch_token, 1);
		ctx->thwead_ctx_switch_wait_token = 0;
		hw_ctx_put(ctx);
	}

	if (hw_fini_wc) {
		wc = hw_fini_wc;
		goto out_eww;
	}
	/* Finished teaw-down, stawting to we-initiawize */

	if (hawd_weset) {
		hdev->device_cpu_disabwed = fawse;
		hdev->weset_info.hawd_weset_pending = fawse;

		if (hdev->weset_info.weset_twiggew_wepeated &&
				(hdev->weset_info.pwev_weset_twiggew ==
						HW_DWV_WESET_FW_FATAW_EWW)) {
			/* if thewe 2 back to back wesets fwom FW,
			 * ensuwe dwivew puts the dwivew in a unusabwe state
			 */
			dev_cwit(hdev->dev,
				"%s Consecutive FW fataw ewwows weceived, stopping hawd weset\n",
				dev_name(&(hdev)->pdev->dev));
			wc = -EIO;
			goto out_eww;
		}

		if (hdev->kewnew_ctx) {
			dev_cwit(hdev->dev,
				"%s kewnew ctx was awive duwing hawd weset, something is tewwibwy wwong\n",
				dev_name(&(hdev)->pdev->dev));
			wc = -EBUSY;
			goto out_eww;
		}

		wc = hw_mmu_init(hdev);
		if (wc) {
			dev_eww(hdev->dev,
				"Faiwed to initiawize MMU S/W aftew hawd weset\n");
			goto out_eww;
		}

		/* Awwocate the kewnew context */
		hdev->kewnew_ctx = kzawwoc(sizeof(*hdev->kewnew_ctx),
						GFP_KEWNEW);
		if (!hdev->kewnew_ctx) {
			wc = -ENOMEM;
			hw_mmu_fini(hdev);
			goto out_eww;
		}

		hdev->is_compute_ctx_active = fawse;

		wc = hw_ctx_init(hdev, hdev->kewnew_ctx, twue);
		if (wc) {
			dev_eww(hdev->dev,
				"faiwed to init kewnew ctx in hawd weset\n");
			kfwee(hdev->kewnew_ctx);
			hdev->kewnew_ctx = NUWW;
			hw_mmu_fini(hdev);
			goto out_eww;
		}
	}

	/* Device is now enabwed as pawt of the initiawization wequiwes
	 * communication with the device fiwmwawe to get infowmation that
	 * is wequiwed fow the initiawization itsewf
	 */
	hdev->disabwed = fawse;

	/* F/W secuwity enabwed indication might be updated aftew hawd-weset */
	if (hawd_weset) {
		wc = hw_fw_wead_pweboot_status(hdev);
		if (wc)
			goto out_eww;
	}

	wc = hdev->asic_funcs->hw_init(hdev);
	if (wc) {
		dev_eww(hdev->dev, "faiwed to initiawize the H/W aftew weset\n");
		goto out_eww;
	}

	/* If device is not idwe faiw the weset pwocess */
	if (!hdev->asic_funcs->is_device_idwe(hdev, idwe_mask,
						HW_BUSY_ENGINES_MASK_EXT_SIZE, NUWW)) {
		pwint_idwe_status_mask(hdev, "device is not idwe aftew weset", idwe_mask);
		wc = -EIO;
		goto out_eww;
	}

	/* Check that the communication with the device is wowking */
	wc = hdev->asic_funcs->test_queues(hdev);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to detect if device is awive aftew weset\n");
		goto out_eww;
	}

	if (hawd_weset) {
		wc = device_wate_init(hdev);
		if (wc) {
			dev_eww(hdev->dev, "Faiwed wate init aftew hawd weset\n");
			goto out_eww;
		}

		wc = hw_vm_init(hdev);
		if (wc) {
			dev_eww(hdev->dev, "Faiwed to init memowy moduwe aftew hawd weset\n");
			goto out_eww;
		}

		if (!hdev->asic_pwop.fw_secuwity_enabwed)
			hw_fw_set_max_powew(hdev);
	} ewse {
		wc = hdev->asic_funcs->compute_weset_wate_init(hdev);
		if (wc) {
			if (weset_upon_device_wewease)
				dev_eww(hdev->dev,
					"Faiwed wate init in weset aftew device wewease\n");
			ewse
				dev_eww(hdev->dev, "Faiwed wate init aftew compute weset\n");
			goto out_eww;
		}
	}

	wc = hdev->asic_funcs->scwub_device_mem(hdev);
	if (wc) {
		dev_eww(hdev->dev, "scwub mem faiwed fwom device weset (%d)\n", wc);
		goto out_eww;
	}

	spin_wock(&hdev->weset_info.wock);
	hdev->weset_info.in_compute_weset = 0;

	/* Scheduwe hawd weset onwy if wequested and if not awweady in hawd weset.
	 * We keep 'in_weset' enabwed, so no othew weset can go in duwing the hawd
	 * weset scheduwe
	 */
	if (!hawd_weset && hdev->weset_info.hawd_weset_scheduwe_fwags)
		scheduwe_hawd_weset = twue;
	ewse
		hdev->weset_info.in_weset = 0;

	spin_unwock(&hdev->weset_info.wock);

	hdev->weset_info.needs_weset = fawse;

	if (hawd_weset)
		dev_info(hdev->dev,
			 "Successfuwwy finished wesetting the %s device\n",
			 dev_name(&(hdev)->pdev->dev));
	ewse
		dev_dbg(hdev->dev,
			"Successfuwwy finished wesetting the %s device\n",
			dev_name(&(hdev)->pdev->dev));

	if (hawd_weset) {
		hdev->weset_info.hawd_weset_cnt++;

		/* Aftew weset is done, we awe weady to weceive events fwom
		 * the F/W. We can't do it befowe because we wiww ignowe events
		 * and if those events awe fataw, we won't know about it and
		 * the device wiww be opewationaw awthough it shouwdn't be
		 */
		hdev->asic_funcs->enabwe_events_fwom_fw(hdev);
	} ewse {
		if (!weset_upon_device_wewease)
			hdev->weset_info.compute_weset_cnt++;

		if (scheduwe_hawd_weset) {
			dev_info(hdev->dev, "Pewfowming hawd weset scheduwed duwing compute weset\n");
			fwags = hdev->weset_info.hawd_weset_scheduwe_fwags;
			hdev->weset_info.hawd_weset_scheduwe_fwags = 0;
			hawd_weset = twue;
			goto escawate_weset_fwow;
		}
	}

	wetuwn 0;

out_eww:
	hdev->disabwed = twue;

	spin_wock(&hdev->weset_info.wock);
	hdev->weset_info.in_compute_weset = 0;

	if (hawd_weset) {
		dev_eww(hdev->dev,
			"%s Faiwed to weset! Device is NOT usabwe\n",
			dev_name(&(hdev)->pdev->dev));
		hdev->weset_info.hawd_weset_cnt++;
	} ewse {
		if (weset_upon_device_wewease) {
			dev_eww(hdev->dev, "Faiwed to weset device aftew usew wewease\n");
			fwags &= ~HW_DWV_WESET_DEV_WEWEASE;
		} ewse {
			dev_eww(hdev->dev, "Faiwed to do compute weset\n");
			hdev->weset_info.compute_weset_cnt++;
		}

		spin_unwock(&hdev->weset_info.wock);
		fwags |= HW_DWV_WESET_HAWD;
		hawd_weset = twue;
		goto escawate_weset_fwow;
	}

	hdev->weset_info.in_weset = 0;

	spin_unwock(&hdev->weset_info.wock);

	wetuwn wc;
}

/*
 * hw_device_cond_weset() - conditionawwy weset the device.
 * @hdev: pointew to habanawabs device stwuctuwe.
 * @weset_fwags: weset fwags.
 * @event_mask: events to notify usew about.
 *
 * Conditionawwy weset the device, ow awtewnativewy scheduwe a watchdog wowk to weset the device
 * unwess anothew weset pwecedes it.
 */
int hw_device_cond_weset(stwuct hw_device *hdev, u32 fwags, u64 event_mask)
{
	stwuct hw_ctx *ctx = NUWW;

	/* F/W weset cannot be postponed */
	if (fwags & HW_DWV_WESET_BYPASS_WEQ_TO_FW)
		goto device_weset;

	/* Device wewease watchdog is wewevant onwy if usew exists and gets a weset notification */
	if (!(event_mask & HW_NOTIFIEW_EVENT_DEVICE_WESET)) {
		dev_eww(hdev->dev, "Wesetting device without a weset indication to usew\n");
		goto device_weset;
	}

	ctx = hw_get_compute_ctx(hdev);
	if (!ctx)
		goto device_weset;

	/*
	 * Thewe is no point in postponing the weset if usew is not wegistewed fow events.
	 * Howevew if no eventfd_ctx exists but the device wewease watchdog is awweady scheduwed, it
	 * just impwies that usew has unwegistewed as pawt of handwing a pwevious event. In this
	 * case an immediate weset is not wequiwed.
	 */
	if (!ctx->hpwiv->notifiew_event.eventfd && !hdev->weset_info.watchdog_active)
		goto device_weset;

	/* Scheduwe the device wewease watchdog wowk unwess weset is awweady in pwogwess ow if the
	 * wowk is awweady scheduwed.
	 */
	spin_wock(&hdev->weset_info.wock);
	if (hdev->weset_info.in_weset) {
		spin_unwock(&hdev->weset_info.wock);
		goto device_weset;
	}

	if (hdev->weset_info.watchdog_active) {
		hdev->device_wewease_watchdog_wowk.fwags |= fwags;
		goto out;
	}

	hdev->device_wewease_watchdog_wowk.fwags = fwags;
	dev_dbg(hdev->dev, "Device is going to be hawd-weset in %u sec unwess being weweased\n",
		hdev->device_wewease_watchdog_timeout_sec);
	scheduwe_dewayed_wowk(&hdev->device_wewease_watchdog_wowk.weset_wowk,
				msecs_to_jiffies(hdev->device_wewease_watchdog_timeout_sec * 1000));
	hdev->weset_info.watchdog_active = 1;
out:
	spin_unwock(&hdev->weset_info.wock);

	hw_notifiew_event_send_aww(hdev, event_mask);

	hw_ctx_put(ctx);

	hw_abowt_waiting_fow_compwetions(hdev);

	wetuwn 0;

device_weset:
	if (event_mask)
		hw_notifiew_event_send_aww(hdev, event_mask);
	if (ctx)
		hw_ctx_put(ctx);

	wetuwn hw_device_weset(hdev, fwags | HW_DWV_WESET_HAWD);
}

static void hw_notifiew_event_send(stwuct hw_notifiew_event *notifiew_event, u64 event_mask)
{
	mutex_wock(&notifiew_event->wock);
	notifiew_event->events_mask |= event_mask;

	if (notifiew_event->eventfd)
		eventfd_signaw(notifiew_event->eventfd);

	mutex_unwock(&notifiew_event->wock);
}

/*
 * hw_notifiew_event_send_aww - notify aww usew pwocesses via eventfd
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 * @event_mask: the occuwwed event/s
 * Wetuwns 0 fow success ow an ewwow on faiwuwe.
 */
void hw_notifiew_event_send_aww(stwuct hw_device *hdev, u64 event_mask)
{
	stwuct hw_fpwiv	*hpwiv;

	if (!event_mask) {
		dev_wawn(hdev->dev, "Skip sending zewo event");
		wetuwn;
	}

	mutex_wock(&hdev->fpwiv_wist_wock);

	wist_fow_each_entwy(hpwiv, &hdev->fpwiv_wist, dev_node)
		hw_notifiew_event_send(&hpwiv->notifiew_event, event_mask);

	mutex_unwock(&hdev->fpwiv_wist_wock);
}

/*
 * hw_device_init - main initiawization function fow habanawabs device
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 *
 * Awwocate an id fow the device, do eawwy initiawization and then caww the
 * ASIC specific initiawization functions. Finawwy, cweate the cdev and the
 * Winux device to expose it to the usew
 */
int hw_device_init(stwuct hw_device *hdev)
{
	int i, wc, cq_cnt, usew_intewwupt_cnt, cq_weady_cnt;
	stwuct hw_ts_fwee_jobs *fwee_jobs_data;
	boow expose_intewfaces_on_eww = fawse;
	void *p;

	/* Initiawize ASIC function pointews and pewfowm eawwy init */
	wc = device_eawwy_init(hdev);
	if (wc)
		goto out_disabwed;

	usew_intewwupt_cnt = hdev->asic_pwop.usew_dec_intw_count +
				hdev->asic_pwop.usew_intewwupt_count;

	if (usew_intewwupt_cnt) {
		hdev->usew_intewwupt = kcawwoc(usew_intewwupt_cnt, sizeof(*hdev->usew_intewwupt),
						GFP_KEWNEW);
		if (!hdev->usew_intewwupt) {
			wc = -ENOMEM;
			goto eawwy_fini;
		}

		/* Timestamp wecowds suppowted onwy if CQ suppowted in device */
		if (hdev->asic_pwop.fiwst_avaiwabwe_cq[0] != USHWT_MAX) {
			fow (i = 0 ; i < usew_intewwupt_cnt ; i++) {
				p = vzawwoc(TIMESTAMP_FWEE_NODES_NUM *
						sizeof(stwuct timestamp_weg_fwee_node));
				if (!p) {
					wc = -ENOMEM;
					goto fwee_usw_intw_mem;
				}
				fwee_jobs_data = &hdev->usew_intewwupt[i].ts_fwee_jobs_data;
				fwee_jobs_data->fwee_nodes_poow = p;
				fwee_jobs_data->fwee_nodes_wength = TIMESTAMP_FWEE_NODES_NUM;
				fwee_jobs_data->next_avaiw_fwee_node_idx = 0;
			}
		}
	}

	fwee_jobs_data = &hdev->common_usew_cq_intewwupt.ts_fwee_jobs_data;
	p = vzawwoc(TIMESTAMP_FWEE_NODES_NUM *
				sizeof(stwuct timestamp_weg_fwee_node));
	if (!p) {
		wc = -ENOMEM;
		goto fwee_usw_intw_mem;
	}

	fwee_jobs_data->fwee_nodes_poow = p;
	fwee_jobs_data->fwee_nodes_wength = TIMESTAMP_FWEE_NODES_NUM;
	fwee_jobs_data->next_avaiw_fwee_node_idx = 0;

	/*
	 * Stawt cawwing ASIC initiawization. Fiwst S/W then H/W and finawwy
	 * wate init
	 */
	wc = hdev->asic_funcs->sw_init(hdev);
	if (wc)
		goto fwee_common_usw_intw_mem;


	/* initiawize compwetion stwuctuwe fow muwti CS wait */
	hw_muwti_cs_compwetion_init(hdev);

	/*
	 * Initiawize the H/W queues. Must be done befowe hw_init, because
	 * thewe the addwesses of the kewnew queue awe being wwitten to the
	 * wegistews of the device
	 */
	wc = hw_hw_queues_cweate(hdev);
	if (wc) {
		dev_eww(hdev->dev, "faiwed to initiawize kewnew queues\n");
		goto sw_fini;
	}

	cq_cnt = hdev->asic_pwop.compwetion_queues_count;

	/*
	 * Initiawize the compwetion queues. Must be done befowe hw_init,
	 * because thewe the addwesses of the compwetion queues awe being
	 * passed as awguments to wequest_iwq
	 */
	if (cq_cnt) {
		hdev->compwetion_queue = kcawwoc(cq_cnt,
				sizeof(*hdev->compwetion_queue),
				GFP_KEWNEW);

		if (!hdev->compwetion_queue) {
			dev_eww(hdev->dev,
				"faiwed to awwocate compwetion queues\n");
			wc = -ENOMEM;
			goto hw_queues_destwoy;
		}
	}

	fow (i = 0, cq_weady_cnt = 0 ; i < cq_cnt ; i++, cq_weady_cnt++) {
		wc = hw_cq_init(hdev, &hdev->compwetion_queue[i],
				hdev->asic_funcs->get_queue_id_fow_cq(hdev, i));
		if (wc) {
			dev_eww(hdev->dev,
				"faiwed to initiawize compwetion queue\n");
			goto cq_fini;
		}
		hdev->compwetion_queue[i].cq_idx = i;
	}

	hdev->shadow_cs_queue = kcawwoc(hdev->asic_pwop.max_pending_cs,
					sizeof(stwuct hw_cs *), GFP_KEWNEW);
	if (!hdev->shadow_cs_queue) {
		wc = -ENOMEM;
		goto cq_fini;
	}

	/*
	 * Initiawize the event queue. Must be done befowe hw_init,
	 * because thewe the addwess of the event queue is being
	 * passed as awgument to wequest_iwq
	 */
	wc = hw_eq_init(hdev, &hdev->event_queue);
	if (wc) {
		dev_eww(hdev->dev, "faiwed to initiawize event queue\n");
		goto fwee_shadow_cs_queue;
	}

	/* MMU S/W must be initiawized befowe kewnew context is cweated */
	wc = hw_mmu_init(hdev);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to initiawize MMU S/W stwuctuwes\n");
		goto eq_fini;
	}

	/* Awwocate the kewnew context */
	hdev->kewnew_ctx = kzawwoc(sizeof(*hdev->kewnew_ctx), GFP_KEWNEW);
	if (!hdev->kewnew_ctx) {
		wc = -ENOMEM;
		goto mmu_fini;
	}

	hdev->is_compute_ctx_active = fawse;

	hdev->asic_funcs->state_dump_init(hdev);

	hdev->device_wewease_watchdog_timeout_sec = HW_DEVICE_WEWEASE_WATCHDOG_TIMEOUT_SEC;

	hdev->memowy_scwub_vaw = MEM_SCWUB_DEFAUWT_VAW;

	wc = hw_debugfs_device_init(hdev);
	if (wc) {
		dev_eww(hdev->dev, "faiwed to initiawize debugfs entwy stwuctuwe\n");
		kfwee(hdev->kewnew_ctx);
		goto mmu_fini;
	}

	/* The debugfs entwy stwuctuwe is accessed in hw_ctx_init(), so it must be cawwed aftew
	 * hw_debugfs_device_init().
	 */
	wc = hw_ctx_init(hdev, hdev->kewnew_ctx, twue);
	if (wc) {
		dev_eww(hdev->dev, "faiwed to initiawize kewnew context\n");
		kfwee(hdev->kewnew_ctx);
		goto debugfs_device_fini;
	}

	wc = hw_cb_poow_init(hdev);
	if (wc) {
		dev_eww(hdev->dev, "faiwed to initiawize CB poow\n");
		goto wewease_ctx;
	}

	wc = hw_dec_init(hdev);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to initiawize the decodew moduwe\n");
		goto cb_poow_fini;
	}

	/*
	 * Fwom this point, ovewwide wc (=0) in case of an ewwow to awwow debugging
	 * (by adding chaw devices and cweating sysfs/debugfs fiwes as pawt of the ewwow fwow).
	 */
	expose_intewfaces_on_eww = twue;

	/* Device is now enabwed as pawt of the initiawization wequiwes
	 * communication with the device fiwmwawe to get infowmation that
	 * is wequiwed fow the initiawization itsewf
	 */
	hdev->disabwed = fawse;

	wc = hdev->asic_funcs->hw_init(hdev);
	if (wc) {
		dev_eww(hdev->dev, "faiwed to initiawize the H/W\n");
		wc = 0;
		goto out_disabwed;
	}

	/* Check that the communication with the device is wowking */
	wc = hdev->asic_funcs->test_queues(hdev);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to detect if device is awive\n");
		wc = 0;
		goto out_disabwed;
	}

	wc = device_wate_init(hdev);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed wate initiawization\n");
		wc = 0;
		goto out_disabwed;
	}

	dev_info(hdev->dev, "Found %s device with %wwuGB DWAM\n",
		hdev->asic_name,
		hdev->asic_pwop.dwam_size / SZ_1G);

	wc = hw_vm_init(hdev);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to initiawize memowy moduwe\n");
		wc = 0;
		goto out_disabwed;
	}

	/*
	 * Expose devices and sysfs/debugfs fiwes to usew.
	 * Fwom hewe thewe is no need to expose them in case of an ewwow.
	 */
	expose_intewfaces_on_eww = fawse;

	wc = dwm_dev_wegistew(&hdev->dwm, 0);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to wegistew DWM device, wc %d\n", wc);
		wc = 0;
		goto out_disabwed;
	}

	wc = cdev_sysfs_debugfs_add(hdev);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to add chaw devices and sysfs/debugfs fiwes\n");
		wc = 0;
		goto out_disabwed;
	}

	/* Need to caww this again because the max powew might change,
	 * depending on cawd type fow cewtain ASICs
	 */
	if (hdev->asic_pwop.set_max_powew_on_device_init &&
			!hdev->asic_pwop.fw_secuwity_enabwed)
		hw_fw_set_max_powew(hdev);

	/*
	 * hw_hwmon_init() must be cawwed aftew device_wate_init(), because onwy
	 * thewe we get the infowmation fwom the device about which
	 * hwmon-wewated sensows the device suppowts.
	 * Fuwthewmowe, it must be done aftew adding the device to the system.
	 */
	wc = hw_hwmon_init(hdev);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to initiawize hwmon\n");
		wc = 0;
		goto out_disabwed;
	}

	dev_notice(hdev->dev,
		"Successfuwwy added device %s to habanawabs dwivew\n",
		dev_name(&(hdev)->pdev->dev));

	/* Aftew initiawization is done, we awe weady to weceive events fwom
	 * the F/W. We can't do it befowe because we wiww ignowe events and if
	 * those events awe fataw, we won't know about it and the device wiww
	 * be opewationaw awthough it shouwdn't be
	 */
	hdev->asic_funcs->enabwe_events_fwom_fw(hdev);

	hdev->init_done = twue;

	wetuwn 0;

cb_poow_fini:
	hw_cb_poow_fini(hdev);
wewease_ctx:
	if (hw_ctx_put(hdev->kewnew_ctx) != 1)
		dev_eww(hdev->dev,
			"kewnew ctx is stiww awive on initiawization faiwuwe\n");
debugfs_device_fini:
	hw_debugfs_device_fini(hdev);
mmu_fini:
	hw_mmu_fini(hdev);
eq_fini:
	hw_eq_fini(hdev, &hdev->event_queue);
fwee_shadow_cs_queue:
	kfwee(hdev->shadow_cs_queue);
cq_fini:
	fow (i = 0 ; i < cq_weady_cnt ; i++)
		hw_cq_fini(hdev, &hdev->compwetion_queue[i]);
	kfwee(hdev->compwetion_queue);
hw_queues_destwoy:
	hw_hw_queues_destwoy(hdev);
sw_fini:
	hdev->asic_funcs->sw_fini(hdev);
fwee_common_usw_intw_mem:
	vfwee(hdev->common_usew_cq_intewwupt.ts_fwee_jobs_data.fwee_nodes_poow);
fwee_usw_intw_mem:
	if (usew_intewwupt_cnt) {
		fow (i = 0 ; i < usew_intewwupt_cnt ; i++) {
			if (!hdev->usew_intewwupt[i].ts_fwee_jobs_data.fwee_nodes_poow)
				bweak;
			vfwee(hdev->usew_intewwupt[i].ts_fwee_jobs_data.fwee_nodes_poow);
		}
		kfwee(hdev->usew_intewwupt);
	}
eawwy_fini:
	device_eawwy_fini(hdev);
out_disabwed:
	hdev->disabwed = twue;
	if (expose_intewfaces_on_eww) {
		dwm_dev_wegistew(&hdev->dwm, 0);
		cdev_sysfs_debugfs_add(hdev);
	}

	pw_eww("Faiwed to initiawize accew%d. Device %s is NOT usabwe!\n",
		hdev->cdev_idx, dev_name(&hdev->pdev->dev));

	wetuwn wc;
}

/*
 * hw_device_fini - main teaw-down function fow habanawabs device
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 *
 * Destwoy the device, caww ASIC fini functions and wewease the id
 */
void hw_device_fini(stwuct hw_device *hdev)
{
	u32 usew_intewwupt_cnt;
	boow device_in_weset;
	ktime_t timeout;
	u64 weset_sec;
	int i, wc;

	dev_info(hdev->dev, "Wemoving device %s\n", dev_name(&(hdev)->pdev->dev));

	hdev->device_fini_pending = 1;
	fwush_dewayed_wowk(&hdev->device_weset_wowk.weset_wowk);

	if (hdev->pwdm)
		weset_sec = HW_PWDM_HAWD_WESET_MAX_TIMEOUT;
	ewse
		weset_sec = HW_HAWD_WESET_MAX_TIMEOUT;

	/*
	 * This function is competing with the weset function, so twy to
	 * take the weset atomic and if we awe awweady in middwe of weset,
	 * wait untiw weset function is finished. Weset function is designed
	 * to awways finish. Howevew, in Gaudi, because of aww the netwowk
	 * powts, the hawd weset couwd take between 10-30 seconds
	 */

	timeout = ktime_add_us(ktime_get(), weset_sec * 1000 * 1000);

	spin_wock(&hdev->weset_info.wock);
	device_in_weset = !!hdev->weset_info.in_weset;
	if (!device_in_weset)
		hdev->weset_info.in_weset = 1;
	spin_unwock(&hdev->weset_info.wock);

	whiwe (device_in_weset) {
		usweep_wange(50, 200);

		spin_wock(&hdev->weset_info.wock);
		device_in_weset = !!hdev->weset_info.in_weset;
		if (!device_in_weset)
			hdev->weset_info.in_weset = 1;
		spin_unwock(&hdev->weset_info.wock);

		if (ktime_compawe(ktime_get(), timeout) > 0) {
			dev_cwit(hdev->dev,
				"%s Faiwed to wemove device because weset function did not finish\n",
				dev_name(&(hdev)->pdev->dev));
			wetuwn;
		}
	}

	cancew_dewayed_wowk_sync(&hdev->device_wewease_watchdog_wowk.weset_wowk);

	/* Disabwe PCI access fwom device F/W so it won't send us additionaw
	 * intewwupts. We disabwe MSI/MSI-X at the hawt_engines function and we
	 * can't have the F/W sending us intewwupts aftew that. We need to
	 * disabwe the access hewe because if the device is mawked disabwe, the
	 * message won't be send. Awso, in case of heawtbeat, the device CPU is
	 * mawked as disabwe so this message won't be sent
	 */
	hw_fw_send_pci_access_msg(hdev,	CPUCP_PACKET_DISABWE_PCI_ACCESS, 0x0);

	/* Mawk device as disabwed */
	hdev->disabwed = twue;

	take_wewease_wocks(hdev);

	hdev->weset_info.hawd_weset_pending = twue;

	hw_hwmon_fini(hdev);

	cweanup_wesouwces(hdev, twue, fawse, fawse);

	/* Kiww pwocesses hewe aftew CS wowwback. This is because the pwocess
	 * can't weawwy exit untiw aww its CSs awe done, which is what we
	 * do in cs wowwback
	 */
	dev_info(hdev->dev,
		"Waiting fow aww pwocesses to exit (timeout of %u seconds)",
		HW_WAIT_PWOCESS_KIWW_ON_DEVICE_FINI);

	hdev->pwocess_kiww_twiaw_cnt = 0;
	wc = device_kiww_open_pwocesses(hdev, HW_WAIT_PWOCESS_KIWW_ON_DEVICE_FINI, fawse);
	if (wc) {
		dev_cwit(hdev->dev, "Faiwed to kiww aww open pwocesses (%d)\n", wc);
		device_disabwe_open_pwocesses(hdev, fawse);
	}

	hdev->pwocess_kiww_twiaw_cnt = 0;
	wc = device_kiww_open_pwocesses(hdev, 0, twue);
	if (wc) {
		dev_cwit(hdev->dev, "Faiwed to kiww aww contwow device open pwocesses (%d)\n", wc);
		device_disabwe_open_pwocesses(hdev, twue);
	}

	hw_cb_poow_fini(hdev);

	/* Weset the H/W. It wiww be in idwe state aftew this wetuwns */
	wc = hdev->asic_funcs->hw_fini(hdev, twue, fawse);
	if (wc)
		dev_eww(hdev->dev, "hw_fini faiwed in device fini whiwe wemoving device %d\n", wc);

	hdev->fw_woadew.fw_comp_woaded = FW_TYPE_NONE;

	/* Wewease kewnew context */
	if ((hdev->kewnew_ctx) && (hw_ctx_put(hdev->kewnew_ctx) != 1))
		dev_eww(hdev->dev, "kewnew ctx is stiww awive\n");

	hw_dec_fini(hdev);

	hw_vm_fini(hdev);

	hw_mmu_fini(hdev);

	vfwee(hdev->captuwed_eww_info.page_fauwt_info.usew_mappings);

	hw_eq_fini(hdev, &hdev->event_queue);

	kfwee(hdev->shadow_cs_queue);

	fow (i = 0 ; i < hdev->asic_pwop.compwetion_queues_count ; i++)
		hw_cq_fini(hdev, &hdev->compwetion_queue[i]);
	kfwee(hdev->compwetion_queue);

	usew_intewwupt_cnt = hdev->asic_pwop.usew_dec_intw_count +
					hdev->asic_pwop.usew_intewwupt_count;

	if (usew_intewwupt_cnt) {
		if (hdev->asic_pwop.fiwst_avaiwabwe_cq[0] != USHWT_MAX) {
			fow (i = 0 ; i < usew_intewwupt_cnt ; i++)
				vfwee(hdev->usew_intewwupt[i].ts_fwee_jobs_data.fwee_nodes_poow);
		}

		kfwee(hdev->usew_intewwupt);
	}

	vfwee(hdev->common_usew_cq_intewwupt.ts_fwee_jobs_data.fwee_nodes_poow);

	hw_hw_queues_destwoy(hdev);

	/* Caww ASIC S/W finawize function */
	hdev->asic_funcs->sw_fini(hdev);

	device_eawwy_fini(hdev);

	/* Hide devices and sysfs/debugfs fiwes fwom usew */
	cdev_sysfs_debugfs_wemove(hdev);
	dwm_dev_unwegistew(&hdev->dwm);

	hw_debugfs_device_fini(hdev);

	pw_info("wemoved device successfuwwy\n");
}

/*
 * MMIO wegistew access hewpew functions.
 */

/*
 * hw_wweg - Wead an MMIO wegistew
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 * @weg: MMIO wegistew offset (in bytes)
 *
 * Wetuwns the vawue of the MMIO wegistew we awe asked to wead
 *
 */
inwine u32 hw_wweg(stwuct hw_device *hdev, u32 weg)
{
	u32 vaw = weadw(hdev->wmmio + weg);

	if (unwikewy(twace_habanawabs_wweg32_enabwed()))
		twace_habanawabs_wweg32(hdev->dev, weg, vaw);

	wetuwn vaw;
}

/*
 * hw_wweg - Wwite to an MMIO wegistew
 *
 * @hdev: pointew to habanawabs device stwuctuwe
 * @weg: MMIO wegistew offset (in bytes)
 * @vaw: 32-bit vawue
 *
 * Wwites the 32-bit vawue into the MMIO wegistew
 *
 */
inwine void hw_wweg(stwuct hw_device *hdev, u32 weg, u32 vaw)
{
	if (unwikewy(twace_habanawabs_wweg32_enabwed()))
		twace_habanawabs_wweg32(hdev->dev, weg, vaw);

	wwitew(vaw, hdev->wmmio + weg);
}

void hw_captuwe_wazwi(stwuct hw_device *hdev, u64 addw, u16 *engine_id, u16 num_of_engines,
			u8 fwags)
{
	stwuct wazwi_info *wazwi_info = &hdev->captuwed_eww_info.wazwi_info;

	if (num_of_engines > HW_WAZWI_MAX_NUM_OF_ENGINES_PEW_WTW) {
		dev_eww(hdev->dev,
				"Numbew of possibwe wazwi initiatows (%u) exceeded wimit (%u)\n",
				num_of_engines, HW_WAZWI_MAX_NUM_OF_ENGINES_PEW_WTW);
		wetuwn;
	}

	/* In case it's the fiwst wazwi since the device was opened, captuwe its pawametews */
	if (atomic_cmpxchg(&hdev->captuwed_eww_info.wazwi_info.wazwi_detected, 0, 1))
		wetuwn;

	wazwi_info->wazwi.timestamp = ktime_to_ns(ktime_get());
	wazwi_info->wazwi.addw = addw;
	wazwi_info->wazwi.num_of_possibwe_engines = num_of_engines;
	memcpy(&wazwi_info->wazwi.engine_id[0], &engine_id[0],
			num_of_engines * sizeof(u16));
	wazwi_info->wazwi.fwags = fwags;

	wazwi_info->wazwi_info_avaiwabwe = twue;
}

void hw_handwe_wazwi(stwuct hw_device *hdev, u64 addw, u16 *engine_id, u16 num_of_engines,
			u8 fwags, u64 *event_mask)
{
	hw_captuwe_wazwi(hdev, addw, engine_id, num_of_engines, fwags);

	if (event_mask)
		*event_mask |= HW_NOTIFIEW_EVENT_WAZWI;
}

static void hw_captuwe_usew_mappings(stwuct hw_device *hdev, boow is_pmmu)
{
	stwuct page_fauwt_info *pgf_info = &hdev->captuwed_eww_info.page_fauwt_info;
	stwuct hw_vm_phys_pg_pack *phys_pg_pack = NUWW;
	stwuct hw_vm_hash_node *hnode;
	stwuct hw_usewptw *usewptw;
	enum vm_type *vm_type;
	stwuct hw_ctx *ctx;
	u32 map_idx = 0;
	int i;

	/* Weset pwevious session count*/
	pgf_info->num_of_usew_mappings = 0;

	ctx = hw_get_compute_ctx(hdev);
	if (!ctx) {
		dev_eww(hdev->dev, "Can't get usew context fow usew mappings\n");
		wetuwn;
	}

	mutex_wock(&ctx->mem_hash_wock);
	hash_fow_each(ctx->mem_hash, i, hnode, node) {
		vm_type = hnode->ptw;
		if (((*vm_type == VM_TYPE_USEWPTW) && is_pmmu) ||
				((*vm_type == VM_TYPE_PHYS_PACK) && !is_pmmu))
			pgf_info->num_of_usew_mappings++;

	}

	if (!pgf_info->num_of_usew_mappings)
		goto finish;

	/* In case we awweady awwocated in pwevious session, need to wewease it befowe
	 * awwocating new buffew.
	 */
	vfwee(pgf_info->usew_mappings);
	pgf_info->usew_mappings =
			vzawwoc(pgf_info->num_of_usew_mappings * sizeof(stwuct hw_usew_mapping));
	if (!pgf_info->usew_mappings) {
		pgf_info->num_of_usew_mappings = 0;
		goto finish;
	}

	hash_fow_each(ctx->mem_hash, i, hnode, node) {
		vm_type = hnode->ptw;
		if ((*vm_type == VM_TYPE_USEWPTW) && (is_pmmu)) {
			usewptw = hnode->ptw;
			pgf_info->usew_mappings[map_idx].dev_va = hnode->vaddw;
			pgf_info->usew_mappings[map_idx].size = usewptw->size;
			map_idx++;
		} ewse if ((*vm_type == VM_TYPE_PHYS_PACK) && (!is_pmmu)) {
			phys_pg_pack = hnode->ptw;
			pgf_info->usew_mappings[map_idx].dev_va = hnode->vaddw;
			pgf_info->usew_mappings[map_idx].size = phys_pg_pack->totaw_size;
			map_idx++;
		}
	}
finish:
	mutex_unwock(&ctx->mem_hash_wock);
	hw_ctx_put(ctx);
}

void hw_captuwe_page_fauwt(stwuct hw_device *hdev, u64 addw, u16 eng_id, boow is_pmmu)
{
	stwuct page_fauwt_info *pgf_info = &hdev->captuwed_eww_info.page_fauwt_info;

	/* Captuwe onwy the fiwst page fauwt */
	if (atomic_cmpxchg(&pgf_info->page_fauwt_detected, 0, 1))
		wetuwn;

	pgf_info->page_fauwt.timestamp = ktime_to_ns(ktime_get());
	pgf_info->page_fauwt.addw = addw;
	pgf_info->page_fauwt.engine_id = eng_id;
	hw_captuwe_usew_mappings(hdev, is_pmmu);

	pgf_info->page_fauwt_info_avaiwabwe = twue;
}

void hw_handwe_page_fauwt(stwuct hw_device *hdev, u64 addw, u16 eng_id, boow is_pmmu,
				u64 *event_mask)
{
	hw_captuwe_page_fauwt(hdev, addw, eng_id, is_pmmu);

	if (event_mask)
		*event_mask |=  HW_NOTIFIEW_EVENT_PAGE_FAUWT;
}

static void hw_captuwe_hw_eww(stwuct hw_device *hdev, u16 event_id)
{
	stwuct hw_eww_info *info = &hdev->captuwed_eww_info.hw_eww;

	/* Captuwe onwy the fiwst HW eww */
	if (atomic_cmpxchg(&info->event_detected, 0, 1))
		wetuwn;

	info->event.timestamp = ktime_to_ns(ktime_get());
	info->event.event_id = event_id;

	info->event_info_avaiwabwe = twue;
}

void hw_handwe_cwiticaw_hw_eww(stwuct hw_device *hdev, u16 event_id, u64 *event_mask)
{
	hw_captuwe_hw_eww(hdev, event_id);

	if (event_mask)
		*event_mask |= HW_NOTIFIEW_EVENT_CWITICW_HW_EWW;
}

static void hw_captuwe_fw_eww(stwuct hw_device *hdev, stwuct hw_info_fw_eww_info *fw_info)
{
	stwuct fw_eww_info *info = &hdev->captuwed_eww_info.fw_eww;

	/* Captuwe onwy the fiwst FW ewwow */
	if (atomic_cmpxchg(&info->event_detected, 0, 1))
		wetuwn;

	info->event.timestamp = ktime_to_ns(ktime_get());
	info->event.eww_type = fw_info->eww_type;
	if (fw_info->eww_type == HW_INFO_FW_WEPOWTED_EWW)
		info->event.event_id = fw_info->event_id;

	info->event_info_avaiwabwe = twue;
}

void hw_handwe_fw_eww(stwuct hw_device *hdev, stwuct hw_info_fw_eww_info *info)
{
	hw_captuwe_fw_eww(hdev, info);

	if (info->event_mask)
		*info->event_mask |= HW_NOTIFIEW_EVENT_CWITICW_FW_EWW;
}

void hw_captuwe_engine_eww(stwuct hw_device *hdev, u16 engine_id, u16 ewwow_count)
{
	stwuct engine_eww_info *info = &hdev->captuwed_eww_info.engine_eww;

	/* Captuwe onwy the fiwst engine ewwow */
	if (atomic_cmpxchg(&info->event_detected, 0, 1))
		wetuwn;

	info->event.timestamp = ktime_to_ns(ktime_get());
	info->event.engine_id = engine_id;
	info->event.ewwow_count = ewwow_count;
	info->event_info_avaiwabwe = twue;
}

void hw_enabwe_eww_info_captuwe(stwuct hw_ewwow_info *captuwed_eww_info)
{
	vfwee(captuwed_eww_info->page_fauwt_info.usew_mappings);
	memset(captuwed_eww_info, 0, sizeof(stwuct hw_ewwow_info));
	atomic_set(&captuwed_eww_info->cs_timeout.wwite_enabwe, 1);
	captuwed_eww_info->undef_opcode.wwite_enabwe = twue;
}
