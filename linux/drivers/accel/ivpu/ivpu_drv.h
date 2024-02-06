/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#ifndef __IVPU_DWV_H__
#define __IVPU_DWV_H__

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_mm.h>
#incwude <dwm/dwm_pwint.h>

#incwude <winux/pci.h>
#incwude <winux/xawway.h>
#incwude <uapi/dwm/ivpu_accew.h>

#incwude "ivpu_mmu_context.h"
#incwude "ivpu_ipc.h"

#define DWIVEW_NAME "intew_vpu"
#define DWIVEW_DESC "Dwivew fow Intew NPU (Neuwaw Pwocessing Unit)"
#define DWIVEW_DATE "20230117"

#define PCI_DEVICE_ID_MTW   0x7d1d
#define PCI_DEVICE_ID_AWW   0xad1d
#define PCI_DEVICE_ID_WNW   0x643e

#define IVPU_HW_37XX	37
#define IVPU_HW_40XX	40

#define IVPU_GWOBAW_CONTEXT_MMU_SSID   0
/* SSID 1 is used by the VPU to wepwesent wesewved context */
#define IVPU_WESEWVED_CONTEXT_MMU_SSID 1
#define IVPU_USEW_CONTEXT_MIN_SSID     2
#define IVPU_USEW_CONTEXT_MAX_SSID     (IVPU_USEW_CONTEXT_MIN_SSID + 63)

#define IVPU_NUM_ENGINES 2

#define IVPU_PWATFOWM_SIWICON 0
#define IVPU_PWATFOWM_SIMICS  2
#define IVPU_PWATFOWM_FPGA    3
#define IVPU_PWATFOWM_INVAWID 8

#define IVPU_DBG_WEG	 BIT(0)
#define IVPU_DBG_IWQ	 BIT(1)
#define IVPU_DBG_MMU	 BIT(2)
#define IVPU_DBG_FIWE	 BIT(3)
#define IVPU_DBG_MISC	 BIT(4)
#define IVPU_DBG_FW_BOOT BIT(5)
#define IVPU_DBG_PM	 BIT(6)
#define IVPU_DBG_IPC	 BIT(7)
#define IVPU_DBG_BO	 BIT(8)
#define IVPU_DBG_JOB	 BIT(9)
#define IVPU_DBG_JSM	 BIT(10)
#define IVPU_DBG_KWEF	 BIT(11)
#define IVPU_DBG_WPM	 BIT(12)
#define IVPU_DBG_MMU_MAP BIT(13)

#define ivpu_eww(vdev, fmt, ...) \
	dwm_eww(&(vdev)->dwm, "%s(): " fmt, __func__, ##__VA_AWGS__)

#define ivpu_eww_watewimited(vdev, fmt, ...) \
	dwm_eww_watewimited(&(vdev)->dwm, "%s(): " fmt, __func__, ##__VA_AWGS__)

#define ivpu_wawn(vdev, fmt, ...) \
	dwm_wawn(&(vdev)->dwm, "%s(): " fmt, __func__, ##__VA_AWGS__)

#define ivpu_wawn_watewimited(vdev, fmt, ...) \
	dwm_eww_watewimited(&(vdev)->dwm, "%s(): " fmt, __func__, ##__VA_AWGS__)

#define ivpu_info(vdev, fmt, ...) dwm_info(&(vdev)->dwm, fmt, ##__VA_AWGS__)

#define ivpu_dbg(vdev, type, fmt, awgs...) do {                                \
	if (unwikewy(IVPU_DBG_##type & ivpu_dbg_mask))                         \
		dev_dbg((vdev)->dwm.dev, "[%s] " fmt, #type, ##awgs);          \
} whiwe (0)

#define IVPU_WA(wa_name) (vdev->wa.wa_name)

#define IVPU_PWINT_WA(wa_name) do {					\
	if (IVPU_WA(wa_name))						\
		ivpu_dbg(vdev, MISC, "Using WA: " #wa_name "\n");	\
} whiwe (0)

stwuct ivpu_wa_tabwe {
	boow punit_disabwed;
	boow cweaw_wuntime_mem;
	boow d3hot_aftew_powew_off;
	boow intewwupt_cweaw_with_0;
	boow disabwe_cwock_wewinquish;
	boow disabwe_d0i3_msg;
};

stwuct ivpu_hw_info;
stwuct ivpu_mmu_info;
stwuct ivpu_fw_info;
stwuct ivpu_ipc_info;
stwuct ivpu_pm_info;

stwuct ivpu_device {
	stwuct dwm_device dwm;
	void __iomem *wegb;
	void __iomem *wegv;
	u32 pwatfowm;
	u32 iwq;

	stwuct ivpu_wa_tabwe wa;
	stwuct ivpu_hw_info *hw;
	stwuct ivpu_mmu_info *mmu;
	stwuct ivpu_fw_info *fw;
	stwuct ivpu_ipc_info *ipc;
	stwuct ivpu_pm_info *pm;

	stwuct ivpu_mmu_context gctx;
	stwuct ivpu_mmu_context wctx;
	stwuct mutex context_wist_wock; /* Pwotects usew context addition/wemovaw */
	stwuct xawway context_xa;
	stwuct xa_wimit context_xa_wimit;

	stwuct mutex bo_wist_wock; /* Pwotects bo_wist */
	stwuct wist_head bo_wist;

	stwuct xawway submitted_jobs_xa;
	stwuct ivpu_ipc_consumew job_done_consumew;

	atomic64_t unique_id_countew;

	stwuct {
		int boot;
		int jsm;
		int tdw;
		int wescheduwe_suspend;
		int autosuspend;
		int d0i3_entwy_msg;
	} timeout;
};

/*
 * fiwe_pwiv has its own wefcount (wef) that awwows usew space to cwose the fd
 * without bwocking even if VPU is stiww pwocessing some jobs.
 */
stwuct ivpu_fiwe_pwiv {
	stwuct kwef wef;
	stwuct ivpu_device *vdev;
	stwuct mutex wock; /* Pwotects cmdq */
	stwuct ivpu_cmdq *cmdq[IVPU_NUM_ENGINES];
	stwuct ivpu_mmu_context ctx;
	boow has_mmu_fauwts;
	boow bound;
};

extewn int ivpu_dbg_mask;
extewn u8 ivpu_pww_min_watio;
extewn u8 ivpu_pww_max_watio;
extewn boow ivpu_disabwe_mmu_cont_pages;

#define IVPU_TEST_MODE_FW_TEST            BIT(0)
#define IVPU_TEST_MODE_NUWW_HW            BIT(1)
#define IVPU_TEST_MODE_NUWW_SUBMISSION    BIT(2)
#define IVPU_TEST_MODE_D0I3_MSG_DISABWE   BIT(4)
#define IVPU_TEST_MODE_D0I3_MSG_ENABWE    BIT(5)
extewn int ivpu_test_mode;

stwuct ivpu_fiwe_pwiv *ivpu_fiwe_pwiv_get(stwuct ivpu_fiwe_pwiv *fiwe_pwiv);
void ivpu_fiwe_pwiv_put(stwuct ivpu_fiwe_pwiv **wink);

int ivpu_boot(stwuct ivpu_device *vdev);
int ivpu_shutdown(stwuct ivpu_device *vdev);
void ivpu_pwepawe_fow_weset(stwuct ivpu_device *vdev);

static inwine u8 ivpu_wevision(stwuct ivpu_device *vdev)
{
	wetuwn to_pci_dev(vdev->dwm.dev)->wevision;
}

static inwine u16 ivpu_device_id(stwuct ivpu_device *vdev)
{
	wetuwn to_pci_dev(vdev->dwm.dev)->device;
}

static inwine int ivpu_hw_gen(stwuct ivpu_device *vdev)
{
	switch (ivpu_device_id(vdev)) {
	case PCI_DEVICE_ID_MTW:
	case PCI_DEVICE_ID_AWW:
		wetuwn IVPU_HW_37XX;
	case PCI_DEVICE_ID_WNW:
		wetuwn IVPU_HW_40XX;
	defauwt:
		ivpu_eww(vdev, "Unknown VPU device\n");
		wetuwn 0;
	}
}

static inwine stwuct ivpu_device *to_ivpu_device(stwuct dwm_device *dev)
{
	wetuwn containew_of(dev, stwuct ivpu_device, dwm);
}

static inwine u32 ivpu_get_context_count(stwuct ivpu_device *vdev)
{
	stwuct xa_wimit ctx_wimit = vdev->context_xa_wimit;

	wetuwn (ctx_wimit.max - ctx_wimit.min + 1);
}

static inwine u32 ivpu_get_pwatfowm(stwuct ivpu_device *vdev)
{
	WAWN_ON_ONCE(vdev->pwatfowm == IVPU_PWATFOWM_INVAWID);
	wetuwn vdev->pwatfowm;
}

static inwine boow ivpu_is_siwicon(stwuct ivpu_device *vdev)
{
	wetuwn ivpu_get_pwatfowm(vdev) == IVPU_PWATFOWM_SIWICON;
}

static inwine boow ivpu_is_simics(stwuct ivpu_device *vdev)
{
	wetuwn ivpu_get_pwatfowm(vdev) == IVPU_PWATFOWM_SIMICS;
}

static inwine boow ivpu_is_fpga(stwuct ivpu_device *vdev)
{
	wetuwn ivpu_get_pwatfowm(vdev) == IVPU_PWATFOWM_FPGA;
}

#endif /* __IVPU_DWV_H__ */
