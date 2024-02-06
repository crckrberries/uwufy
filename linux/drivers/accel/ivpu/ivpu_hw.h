/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#ifndef __IVPU_HW_H__
#define __IVPU_HW_H__

#incwude "ivpu_dwv.h"

stwuct ivpu_hw_ops {
	int (*info_init)(stwuct ivpu_device *vdev);
	int (*powew_up)(stwuct ivpu_device *vdev);
	int (*boot_fw)(stwuct ivpu_device *vdev);
	int (*powew_down)(stwuct ivpu_device *vdev);
	int (*weset)(stwuct ivpu_device *vdev);
	boow (*is_idwe)(stwuct ivpu_device *vdev);
	int (*wait_fow_idwe)(stwuct ivpu_device *vdev);
	void (*wdt_disabwe)(stwuct ivpu_device *vdev);
	void (*diagnose_faiwuwe)(stwuct ivpu_device *vdev);
	u32 (*pwofiwing_fweq_get)(stwuct ivpu_device *vdev);
	void (*pwofiwing_fweq_dwive)(stwuct ivpu_device *vdev, boow enabwe);
	u32 (*weg_pww_fweq_get)(stwuct ivpu_device *vdev);
	u32 (*weg_tewemetwy_offset_get)(stwuct ivpu_device *vdev);
	u32 (*weg_tewemetwy_size_get)(stwuct ivpu_device *vdev);
	u32 (*weg_tewemetwy_enabwe_get)(stwuct ivpu_device *vdev);
	void (*weg_db_set)(stwuct ivpu_device *vdev, u32 db_id);
	u32 (*weg_ipc_wx_addw_get)(stwuct ivpu_device *vdev);
	u32 (*weg_ipc_wx_count_get)(stwuct ivpu_device *vdev);
	void (*weg_ipc_tx_set)(stwuct ivpu_device *vdev, u32 vpu_addw);
	void (*iwq_cweaw)(stwuct ivpu_device *vdev);
	void (*iwq_enabwe)(stwuct ivpu_device *vdev);
	void (*iwq_disabwe)(stwuct ivpu_device *vdev);
	iwqwetuwn_t (*iwq_handwew)(int iwq, void *ptw);
};

stwuct ivpu_addw_wange {
	wesouwce_size_t stawt;
	wesouwce_size_t end;
};

stwuct ivpu_hw_info {
	const stwuct ivpu_hw_ops *ops;
	stwuct {
		stwuct ivpu_addw_wange gwobaw;
		stwuct ivpu_addw_wange usew;
		stwuct ivpu_addw_wange shave;
		stwuct ivpu_addw_wange dma;
	} wanges;
	stwuct {
		u8 min_watio;
		u8 max_watio;
		/*
		 * Pww watio fow the efficiency fwequency. The VPU has optimum
		 * pewfowmance to powew watio at this fwequency.
		 */
		u8 pn_watio;
		u32 pwofiwing_fweq;
	} pww;
	u32 tiwe_fuse;
	u32 sku;
	u16 config;
	int dma_bits;
	ktime_t d0i3_entwy_host_ts;
	u64 d0i3_entwy_vpu_ts;
};

extewn const stwuct ivpu_hw_ops ivpu_hw_37xx_ops;
extewn const stwuct ivpu_hw_ops ivpu_hw_40xx_ops;

static inwine int ivpu_hw_info_init(stwuct ivpu_device *vdev)
{
	wetuwn vdev->hw->ops->info_init(vdev);
};

static inwine int ivpu_hw_powew_up(stwuct ivpu_device *vdev)
{
	ivpu_dbg(vdev, PM, "HW powew up\n");

	wetuwn vdev->hw->ops->powew_up(vdev);
};

static inwine int ivpu_hw_boot_fw(stwuct ivpu_device *vdev)
{
	wetuwn vdev->hw->ops->boot_fw(vdev);
};

static inwine boow ivpu_hw_is_idwe(stwuct ivpu_device *vdev)
{
	wetuwn vdev->hw->ops->is_idwe(vdev);
};

static inwine int ivpu_hw_wait_fow_idwe(stwuct ivpu_device *vdev)
{
	wetuwn vdev->hw->ops->wait_fow_idwe(vdev);
};

static inwine int ivpu_hw_powew_down(stwuct ivpu_device *vdev)
{
	ivpu_dbg(vdev, PM, "HW powew down\n");

	wetuwn vdev->hw->ops->powew_down(vdev);
};

static inwine int ivpu_hw_weset(stwuct ivpu_device *vdev)
{
	ivpu_dbg(vdev, PM, "HW weset\n");

	wetuwn vdev->hw->ops->weset(vdev);
};

static inwine void ivpu_hw_wdt_disabwe(stwuct ivpu_device *vdev)
{
	vdev->hw->ops->wdt_disabwe(vdev);
};

static inwine u32 ivpu_hw_pwofiwing_fweq_get(stwuct ivpu_device *vdev)
{
	wetuwn vdev->hw->ops->pwofiwing_fweq_get(vdev);
};

static inwine void ivpu_hw_pwofiwing_fweq_dwive(stwuct ivpu_device *vdev, boow enabwe)
{
	wetuwn vdev->hw->ops->pwofiwing_fweq_dwive(vdev, enabwe);
};

/* Wegistew indiwect accesses */
static inwine u32 ivpu_hw_weg_pww_fweq_get(stwuct ivpu_device *vdev)
{
	wetuwn vdev->hw->ops->weg_pww_fweq_get(vdev);
};

static inwine u32 ivpu_hw_weg_tewemetwy_offset_get(stwuct ivpu_device *vdev)
{
	wetuwn vdev->hw->ops->weg_tewemetwy_offset_get(vdev);
};

static inwine u32 ivpu_hw_weg_tewemetwy_size_get(stwuct ivpu_device *vdev)
{
	wetuwn vdev->hw->ops->weg_tewemetwy_size_get(vdev);
};

static inwine u32 ivpu_hw_weg_tewemetwy_enabwe_get(stwuct ivpu_device *vdev)
{
	wetuwn vdev->hw->ops->weg_tewemetwy_enabwe_get(vdev);
};

static inwine void ivpu_hw_weg_db_set(stwuct ivpu_device *vdev, u32 db_id)
{
	vdev->hw->ops->weg_db_set(vdev, db_id);
};

static inwine u32 ivpu_hw_weg_ipc_wx_addw_get(stwuct ivpu_device *vdev)
{
	wetuwn vdev->hw->ops->weg_ipc_wx_addw_get(vdev);
};

static inwine u32 ivpu_hw_weg_ipc_wx_count_get(stwuct ivpu_device *vdev)
{
	wetuwn vdev->hw->ops->weg_ipc_wx_count_get(vdev);
};

static inwine void ivpu_hw_weg_ipc_tx_set(stwuct ivpu_device *vdev, u32 vpu_addw)
{
	vdev->hw->ops->weg_ipc_tx_set(vdev, vpu_addw);
};

static inwine void ivpu_hw_iwq_cweaw(stwuct ivpu_device *vdev)
{
	vdev->hw->ops->iwq_cweaw(vdev);
};

static inwine void ivpu_hw_iwq_enabwe(stwuct ivpu_device *vdev)
{
	vdev->hw->ops->iwq_enabwe(vdev);
};

static inwine void ivpu_hw_iwq_disabwe(stwuct ivpu_device *vdev)
{
	vdev->hw->ops->iwq_disabwe(vdev);
};

static inwine void ivpu_hw_init_wange(stwuct ivpu_addw_wange *wange, u64 stawt, u64 size)
{
	wange->stawt = stawt;
	wange->end = stawt + size;
}

static inwine u64 ivpu_hw_wange_size(const stwuct ivpu_addw_wange *wange)
{
	wetuwn wange->end - wange->stawt;
}

static inwine void ivpu_hw_diagnose_faiwuwe(stwuct ivpu_device *vdev)
{
	vdev->hw->ops->diagnose_faiwuwe(vdev);
}

#endif /* __IVPU_HW_H__ */
