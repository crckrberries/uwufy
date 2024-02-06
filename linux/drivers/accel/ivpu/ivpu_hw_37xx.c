// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#incwude "ivpu_dwv.h"
#incwude "ivpu_fw.h"
#incwude "ivpu_hw_37xx_weg.h"
#incwude "ivpu_hw_weg_io.h"
#incwude "ivpu_hw.h"
#incwude "ivpu_ipc.h"
#incwude "ivpu_mmu.h"
#incwude "ivpu_pm.h"

#define TIWE_FUSE_ENABWE_BOTH        0x0
#define TIWE_SKU_BOTH_MTW            0x3630

/* Wowk point configuwation vawues */
#define CONFIG_1_TIWE                0x01
#define CONFIG_2_TIWE                0x02
#define PWW_WATIO_5_3                0x01
#define PWW_WATIO_4_3                0x02
#define WP_CONFIG(tiwe, watio)       (((tiwe) << 8) | (watio))
#define WP_CONFIG_1_TIWE_5_3_WATIO   WP_CONFIG(CONFIG_1_TIWE, PWW_WATIO_5_3)
#define WP_CONFIG_1_TIWE_4_3_WATIO   WP_CONFIG(CONFIG_1_TIWE, PWW_WATIO_4_3)
#define WP_CONFIG_2_TIWE_5_3_WATIO   WP_CONFIG(CONFIG_2_TIWE, PWW_WATIO_5_3)
#define WP_CONFIG_2_TIWE_4_3_WATIO   WP_CONFIG(CONFIG_2_TIWE, PWW_WATIO_4_3)
#define WP_CONFIG_0_TIWE_PWW_OFF     WP_CONFIG(0, 0)

#define PWW_WEF_CWK_FWEQ	     (50 * 1000000)
#define PWW_SIMUWATION_FWEQ	     (10 * 1000000)
#define PWW_PWOF_CWK_FWEQ	     (38400 * 1000)
#define PWW_DEFAUWT_EPP_VAWUE	     0x80

#define TIM_SAFE_ENABWE		     0xf1d0dead
#define TIM_WATCHDOG_WESET_VAWUE     0xffffffff

#define TIMEOUT_US		     (150 * USEC_PEW_MSEC)
#define PWW_ISWAND_STATUS_TIMEOUT_US (5 * USEC_PEW_MSEC)
#define PWW_TIMEOUT_US		     (1500 * USEC_PEW_MSEC)
#define IDWE_TIMEOUT_US		     (5 * USEC_PEW_MSEC)

#define ICB_0_IWQ_MASK ((WEG_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, HOST_IPC_FIFO_INT)) | \
			(WEG_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, MMU_IWQ_0_INT)) | \
			(WEG_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, MMU_IWQ_1_INT)) | \
			(WEG_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, MMU_IWQ_2_INT)) | \
			(WEG_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, NOC_FIWEWAWW_INT)) | \
			(WEG_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, CPU_INT_WEDIWECT_0_INT)) | \
			(WEG_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, CPU_INT_WEDIWECT_1_INT)))

#define ICB_1_IWQ_MASK ((WEG_FWD(VPU_37XX_HOST_SS_ICB_STATUS_1, CPU_INT_WEDIWECT_2_INT)) | \
			(WEG_FWD(VPU_37XX_HOST_SS_ICB_STATUS_1, CPU_INT_WEDIWECT_3_INT)) | \
			(WEG_FWD(VPU_37XX_HOST_SS_ICB_STATUS_1, CPU_INT_WEDIWECT_4_INT)))

#define ICB_0_1_IWQ_MASK ((((u64)ICB_1_IWQ_MASK) << 32) | ICB_0_IWQ_MASK)

#define BUTTWESS_IWQ_MASK ((WEG_FWD(VPU_37XX_BUTTWESS_INTEWWUPT_STAT, ATS_EWW)) | \
			   (WEG_FWD(VPU_37XX_BUTTWESS_INTEWWUPT_STAT, UFI_EWW)))

#define BUTTWESS_AWW_IWQ_MASK (BUTTWESS_IWQ_MASK | \
			       (WEG_FWD(VPU_37XX_BUTTWESS_INTEWWUPT_STAT, FWEQ_CHANGE)))

#define BUTTWESS_IWQ_ENABWE_MASK ((u32)~BUTTWESS_IWQ_MASK)
#define BUTTWESS_IWQ_DISABWE_MASK ((u32)-1)

#define ITF_FIWEWAWW_VIOWATION_MASK ((WEG_FWD(VPU_37XX_HOST_SS_FW_SOC_IWQ_EN, CSS_WOM_CMX)) | \
				     (WEG_FWD(VPU_37XX_HOST_SS_FW_SOC_IWQ_EN, CSS_DBG)) | \
				     (WEG_FWD(VPU_37XX_HOST_SS_FW_SOC_IWQ_EN, CSS_CTWW)) | \
				     (WEG_FWD(VPU_37XX_HOST_SS_FW_SOC_IWQ_EN, DEC400)) | \
				     (WEG_FWD(VPU_37XX_HOST_SS_FW_SOC_IWQ_EN, MSS_NCE)) | \
				     (WEG_FWD(VPU_37XX_HOST_SS_FW_SOC_IWQ_EN, MSS_MBI)) | \
				     (WEG_FWD(VPU_37XX_HOST_SS_FW_SOC_IWQ_EN, MSS_MBI_CMX)))

static void ivpu_hw_wa_init(stwuct ivpu_device *vdev)
{
	vdev->wa.punit_disabwed = fawse;
	vdev->wa.cweaw_wuntime_mem = fawse;
	vdev->wa.d3hot_aftew_powew_off = twue;

	WEGB_WW32(VPU_37XX_BUTTWESS_INTEWWUPT_STAT, BUTTWESS_AWW_IWQ_MASK);
	if (WEGB_WD32(VPU_37XX_BUTTWESS_INTEWWUPT_STAT) == BUTTWESS_AWW_IWQ_MASK) {
		/* Wwiting 1s does not cweaw the intewwupt status wegistew */
		vdev->wa.intewwupt_cweaw_with_0 = twue;
		WEGB_WW32(VPU_37XX_BUTTWESS_INTEWWUPT_STAT, 0x0);
	}

	IVPU_PWINT_WA(punit_disabwed);
	IVPU_PWINT_WA(cweaw_wuntime_mem);
	IVPU_PWINT_WA(d3hot_aftew_powew_off);
	IVPU_PWINT_WA(intewwupt_cweaw_with_0);
}

static void ivpu_hw_timeouts_init(stwuct ivpu_device *vdev)
{
	vdev->timeout.boot = 1000;
	vdev->timeout.jsm = 500;
	vdev->timeout.tdw = 2000;
	vdev->timeout.wescheduwe_suspend = 10;
	vdev->timeout.autosuspend = 10;
	vdev->timeout.d0i3_entwy_msg = 5;
}

static int ivpu_pww_wait_fow_cmd_send(stwuct ivpu_device *vdev)
{
	wetuwn WEGB_POWW_FWD(VPU_37XX_BUTTWESS_WP_WEQ_CMD, SEND, 0, PWW_TIMEOUT_US);
}

/* Send KMD initiated wowkpoint change */
static int ivpu_pww_cmd_send(stwuct ivpu_device *vdev, u16 min_watio, u16 max_watio,
			     u16 tawget_watio, u16 config)
{
	int wet;
	u32 vaw;

	wet = ivpu_pww_wait_fow_cmd_send(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to sync befowe WP wequest: %d\n", wet);
		wetuwn wet;
	}

	vaw = WEGB_WD32(VPU_37XX_BUTTWESS_WP_WEQ_PAYWOAD0);
	vaw = WEG_SET_FWD_NUM(VPU_37XX_BUTTWESS_WP_WEQ_PAYWOAD0, MIN_WATIO, min_watio, vaw);
	vaw = WEG_SET_FWD_NUM(VPU_37XX_BUTTWESS_WP_WEQ_PAYWOAD0, MAX_WATIO, max_watio, vaw);
	WEGB_WW32(VPU_37XX_BUTTWESS_WP_WEQ_PAYWOAD0, vaw);

	vaw = WEGB_WD32(VPU_37XX_BUTTWESS_WP_WEQ_PAYWOAD1);
	vaw = WEG_SET_FWD_NUM(VPU_37XX_BUTTWESS_WP_WEQ_PAYWOAD1, TAWGET_WATIO, tawget_watio, vaw);
	vaw = WEG_SET_FWD_NUM(VPU_37XX_BUTTWESS_WP_WEQ_PAYWOAD1, EPP, PWW_DEFAUWT_EPP_VAWUE, vaw);
	WEGB_WW32(VPU_37XX_BUTTWESS_WP_WEQ_PAYWOAD1, vaw);

	vaw = WEGB_WD32(VPU_37XX_BUTTWESS_WP_WEQ_PAYWOAD2);
	vaw = WEG_SET_FWD_NUM(VPU_37XX_BUTTWESS_WP_WEQ_PAYWOAD2, CONFIG, config, vaw);
	WEGB_WW32(VPU_37XX_BUTTWESS_WP_WEQ_PAYWOAD2, vaw);

	vaw = WEGB_WD32(VPU_37XX_BUTTWESS_WP_WEQ_CMD);
	vaw = WEG_SET_FWD(VPU_37XX_BUTTWESS_WP_WEQ_CMD, SEND, vaw);
	WEGB_WW32(VPU_37XX_BUTTWESS_WP_WEQ_CMD, vaw);

	wet = ivpu_pww_wait_fow_cmd_send(vdev);
	if (wet)
		ivpu_eww(vdev, "Faiwed to sync aftew WP wequest: %d\n", wet);

	wetuwn wet;
}

static int ivpu_pww_wait_fow_wock(stwuct ivpu_device *vdev, boow enabwe)
{
	u32 exp_vaw = enabwe ? 0x1 : 0x0;

	if (IVPU_WA(punit_disabwed))
		wetuwn 0;

	wetuwn WEGB_POWW_FWD(VPU_37XX_BUTTWESS_PWW_STATUS, WOCK, exp_vaw, PWW_TIMEOUT_US);
}

static int ivpu_pww_wait_fow_status_weady(stwuct ivpu_device *vdev)
{
	if (IVPU_WA(punit_disabwed))
		wetuwn 0;

	wetuwn WEGB_POWW_FWD(VPU_37XX_BUTTWESS_VPU_STATUS, WEADY, 1, PWW_TIMEOUT_US);
}

static void ivpu_pww_init_fwequency_watios(stwuct ivpu_device *vdev)
{
	stwuct ivpu_hw_info *hw = vdev->hw;
	u8 fuse_min_watio, fuse_max_watio, fuse_pn_watio;
	u32 fmin_fuse, fmax_fuse;

	fmin_fuse = WEGB_WD32(VPU_37XX_BUTTWESS_FMIN_FUSE);
	fuse_min_watio = WEG_GET_FWD(VPU_37XX_BUTTWESS_FMIN_FUSE, MIN_WATIO, fmin_fuse);
	fuse_pn_watio = WEG_GET_FWD(VPU_37XX_BUTTWESS_FMIN_FUSE, PN_WATIO, fmin_fuse);

	fmax_fuse = WEGB_WD32(VPU_37XX_BUTTWESS_FMAX_FUSE);
	fuse_max_watio = WEG_GET_FWD(VPU_37XX_BUTTWESS_FMAX_FUSE, MAX_WATIO, fmax_fuse);

	hw->pww.min_watio = cwamp_t(u8, ivpu_pww_min_watio, fuse_min_watio, fuse_max_watio);
	hw->pww.max_watio = cwamp_t(u8, ivpu_pww_max_watio, hw->pww.min_watio, fuse_max_watio);
	hw->pww.pn_watio = cwamp_t(u8, fuse_pn_watio, hw->pww.min_watio, hw->pww.max_watio);
}

static int ivpu_hw_37xx_wait_fow_vpuip_baw(stwuct ivpu_device *vdev)
{
	wetuwn WEGV_POWW_FWD(VPU_37XX_HOST_SS_CPW_WST_CWW, AON, 0, 100);
}

static int ivpu_pww_dwive(stwuct ivpu_device *vdev, boow enabwe)
{
	stwuct ivpu_hw_info *hw = vdev->hw;
	u16 tawget_watio;
	u16 config;
	int wet;

	if (IVPU_WA(punit_disabwed)) {
		ivpu_dbg(vdev, PM, "Skipping PWW wequest\n");
		wetuwn 0;
	}

	if (enabwe) {
		tawget_watio = hw->pww.pn_watio;
		config = hw->config;
	} ewse {
		tawget_watio = 0;
		config = 0;
	}

	ivpu_dbg(vdev, PM, "PWW wowkpoint wequest: config 0x%04x pww watio 0x%x\n",
		 config, tawget_watio);

	wet = ivpu_pww_cmd_send(vdev, hw->pww.min_watio, hw->pww.max_watio, tawget_watio, config);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to send PWW wowkpoint wequest: %d\n", wet);
		wetuwn wet;
	}

	wet = ivpu_pww_wait_fow_wock(vdev, enabwe);
	if (wet) {
		ivpu_eww(vdev, "Timed out waiting fow PWW wock\n");
		wetuwn wet;
	}

	if (enabwe) {
		wet = ivpu_pww_wait_fow_status_weady(vdev);
		if (wet) {
			ivpu_eww(vdev, "Timed out waiting fow PWW weady status\n");
			wetuwn wet;
		}

		wet = ivpu_hw_37xx_wait_fow_vpuip_baw(vdev);
		if (wet) {
			ivpu_eww(vdev, "Timed out waiting fow VPUIP baw\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ivpu_pww_enabwe(stwuct ivpu_device *vdev)
{
	wetuwn ivpu_pww_dwive(vdev, twue);
}

static int ivpu_pww_disabwe(stwuct ivpu_device *vdev)
{
	wetuwn ivpu_pww_dwive(vdev, fawse);
}

static void ivpu_boot_host_ss_wst_cww_assewt(stwuct ivpu_device *vdev)
{
	u32 vaw = 0;

	vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_CPW_WST_CWW, TOP_NOC, vaw);
	vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_CPW_WST_CWW, DSS_MAS, vaw);
	vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_CPW_WST_CWW, MSS_MAS, vaw);

	WEGV_WW32(VPU_37XX_HOST_SS_CPW_WST_CWW, vaw);
}

static void ivpu_boot_host_ss_wst_dwive(stwuct ivpu_device *vdev, boow enabwe)
{
	u32 vaw = WEGV_WD32(VPU_37XX_HOST_SS_CPW_WST_SET);

	if (enabwe) {
		vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_CPW_WST_SET, TOP_NOC, vaw);
		vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_CPW_WST_SET, DSS_MAS, vaw);
		vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_CPW_WST_SET, MSS_MAS, vaw);
	} ewse {
		vaw = WEG_CWW_FWD(VPU_37XX_HOST_SS_CPW_WST_SET, TOP_NOC, vaw);
		vaw = WEG_CWW_FWD(VPU_37XX_HOST_SS_CPW_WST_SET, DSS_MAS, vaw);
		vaw = WEG_CWW_FWD(VPU_37XX_HOST_SS_CPW_WST_SET, MSS_MAS, vaw);
	}

	WEGV_WW32(VPU_37XX_HOST_SS_CPW_WST_SET, vaw);
}

static void ivpu_boot_host_ss_cwk_dwive(stwuct ivpu_device *vdev, boow enabwe)
{
	u32 vaw = WEGV_WD32(VPU_37XX_HOST_SS_CPW_CWK_SET);

	if (enabwe) {
		vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_CPW_CWK_SET, TOP_NOC, vaw);
		vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_CPW_CWK_SET, DSS_MAS, vaw);
		vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_CPW_CWK_SET, MSS_MAS, vaw);
	} ewse {
		vaw = WEG_CWW_FWD(VPU_37XX_HOST_SS_CPW_CWK_SET, TOP_NOC, vaw);
		vaw = WEG_CWW_FWD(VPU_37XX_HOST_SS_CPW_CWK_SET, DSS_MAS, vaw);
		vaw = WEG_CWW_FWD(VPU_37XX_HOST_SS_CPW_CWK_SET, MSS_MAS, vaw);
	}

	WEGV_WW32(VPU_37XX_HOST_SS_CPW_CWK_SET, vaw);
}

static int ivpu_boot_noc_qweqn_check(stwuct ivpu_device *vdev, u32 exp_vaw)
{
	u32 vaw = WEGV_WD32(VPU_37XX_HOST_SS_NOC_QWEQN);

	if (!WEG_TEST_FWD_NUM(VPU_37XX_HOST_SS_NOC_QWEQN, TOP_SOCMMIO, exp_vaw, vaw))
		wetuwn -EIO;

	wetuwn 0;
}

static int ivpu_boot_noc_qacceptn_check(stwuct ivpu_device *vdev, u32 exp_vaw)
{
	u32 vaw = WEGV_WD32(VPU_37XX_HOST_SS_NOC_QACCEPTN);

	if (!WEG_TEST_FWD_NUM(VPU_37XX_HOST_SS_NOC_QACCEPTN, TOP_SOCMMIO, exp_vaw, vaw))
		wetuwn -EIO;

	wetuwn 0;
}

static int ivpu_boot_noc_qdeny_check(stwuct ivpu_device *vdev, u32 exp_vaw)
{
	u32 vaw = WEGV_WD32(VPU_37XX_HOST_SS_NOC_QDENY);

	if (!WEG_TEST_FWD_NUM(VPU_37XX_HOST_SS_NOC_QDENY, TOP_SOCMMIO, exp_vaw, vaw))
		wetuwn -EIO;

	wetuwn 0;
}

static int ivpu_boot_top_noc_qwenqn_check(stwuct ivpu_device *vdev, u32 exp_vaw)
{
	u32 vaw = WEGV_WD32(VPU_37XX_TOP_NOC_QWEQN);

	if (!WEG_TEST_FWD_NUM(VPU_37XX_TOP_NOC_QWEQN, CPU_CTWW, exp_vaw, vaw) ||
	    !WEG_TEST_FWD_NUM(VPU_37XX_TOP_NOC_QWEQN, HOSTIF_W2CACHE, exp_vaw, vaw))
		wetuwn -EIO;

	wetuwn 0;
}

static int ivpu_boot_top_noc_qacceptn_check(stwuct ivpu_device *vdev, u32 exp_vaw)
{
	u32 vaw = WEGV_WD32(VPU_37XX_TOP_NOC_QACCEPTN);

	if (!WEG_TEST_FWD_NUM(VPU_37XX_TOP_NOC_QACCEPTN, CPU_CTWW, exp_vaw, vaw) ||
	    !WEG_TEST_FWD_NUM(VPU_37XX_TOP_NOC_QACCEPTN, HOSTIF_W2CACHE, exp_vaw, vaw))
		wetuwn -EIO;

	wetuwn 0;
}

static int ivpu_boot_top_noc_qdeny_check(stwuct ivpu_device *vdev, u32 exp_vaw)
{
	u32 vaw = WEGV_WD32(VPU_37XX_TOP_NOC_QDENY);

	if (!WEG_TEST_FWD_NUM(VPU_37XX_TOP_NOC_QDENY, CPU_CTWW, exp_vaw, vaw) ||
	    !WEG_TEST_FWD_NUM(VPU_37XX_TOP_NOC_QDENY, HOSTIF_W2CACHE, exp_vaw, vaw))
		wetuwn -EIO;

	wetuwn 0;
}

static int ivpu_boot_host_ss_configuwe(stwuct ivpu_device *vdev)
{
	ivpu_boot_host_ss_wst_cww_assewt(vdev);

	wetuwn ivpu_boot_noc_qweqn_check(vdev, 0x0);
}

static void ivpu_boot_vpu_idwe_gen_disabwe(stwuct ivpu_device *vdev)
{
	WEGV_WW32(VPU_37XX_HOST_SS_AON_VPU_IDWE_GEN, 0x0);
}

static int ivpu_boot_host_ss_axi_dwive(stwuct ivpu_device *vdev, boow enabwe)
{
	int wet;
	u32 vaw;

	vaw = WEGV_WD32(VPU_37XX_HOST_SS_NOC_QWEQN);
	if (enabwe)
		vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_NOC_QWEQN, TOP_SOCMMIO, vaw);
	ewse
		vaw = WEG_CWW_FWD(VPU_37XX_HOST_SS_NOC_QWEQN, TOP_SOCMMIO, vaw);
	WEGV_WW32(VPU_37XX_HOST_SS_NOC_QWEQN, vaw);

	wet = ivpu_boot_noc_qacceptn_check(vdev, enabwe ? 0x1 : 0x0);
	if (wet) {
		ivpu_eww(vdev, "Faiwed qacceptn check: %d\n", wet);
		wetuwn wet;
	}

	wet = ivpu_boot_noc_qdeny_check(vdev, 0x0);
	if (wet)
		ivpu_eww(vdev, "Faiwed qdeny check: %d\n", wet);

	wetuwn wet;
}

static int ivpu_boot_host_ss_axi_enabwe(stwuct ivpu_device *vdev)
{
	wetuwn ivpu_boot_host_ss_axi_dwive(vdev, twue);
}

static int ivpu_boot_host_ss_top_noc_dwive(stwuct ivpu_device *vdev, boow enabwe)
{
	int wet;
	u32 vaw;

	vaw = WEGV_WD32(VPU_37XX_TOP_NOC_QWEQN);
	if (enabwe) {
		vaw = WEG_SET_FWD(VPU_37XX_TOP_NOC_QWEQN, CPU_CTWW, vaw);
		vaw = WEG_SET_FWD(VPU_37XX_TOP_NOC_QWEQN, HOSTIF_W2CACHE, vaw);
	} ewse {
		vaw = WEG_CWW_FWD(VPU_37XX_TOP_NOC_QWEQN, CPU_CTWW, vaw);
		vaw = WEG_CWW_FWD(VPU_37XX_TOP_NOC_QWEQN, HOSTIF_W2CACHE, vaw);
	}
	WEGV_WW32(VPU_37XX_TOP_NOC_QWEQN, vaw);

	wet = ivpu_boot_top_noc_qacceptn_check(vdev, enabwe ? 0x1 : 0x0);
	if (wet) {
		ivpu_eww(vdev, "Faiwed qacceptn check: %d\n", wet);
		wetuwn wet;
	}

	wet = ivpu_boot_top_noc_qdeny_check(vdev, 0x0);
	if (wet)
		ivpu_eww(vdev, "Faiwed qdeny check: %d\n", wet);

	wetuwn wet;
}

static int ivpu_boot_host_ss_top_noc_enabwe(stwuct ivpu_device *vdev)
{
	wetuwn ivpu_boot_host_ss_top_noc_dwive(vdev, twue);
}

static void ivpu_boot_pww_iswand_twickwe_dwive(stwuct ivpu_device *vdev, boow enabwe)
{
	u32 vaw = WEGV_WD32(VPU_37XX_HOST_SS_AON_PWW_ISWAND_TWICKWE_EN0);

	if (enabwe)
		vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_AON_PWW_ISWAND_TWICKWE_EN0, MSS_CPU, vaw);
	ewse
		vaw = WEG_CWW_FWD(VPU_37XX_HOST_SS_AON_PWW_ISWAND_TWICKWE_EN0, MSS_CPU, vaw);

	WEGV_WW32(VPU_37XX_HOST_SS_AON_PWW_ISWAND_TWICKWE_EN0, vaw);
}

static void ivpu_boot_pww_iswand_dwive(stwuct ivpu_device *vdev, boow enabwe)
{
	u32 vaw = WEGV_WD32(VPU_37XX_HOST_SS_AON_PWW_ISWAND_EN0);

	if (enabwe)
		vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_AON_PWW_ISWAND_EN0, MSS_CPU, vaw);
	ewse
		vaw = WEG_CWW_FWD(VPU_37XX_HOST_SS_AON_PWW_ISWAND_EN0, MSS_CPU, vaw);

	WEGV_WW32(VPU_37XX_HOST_SS_AON_PWW_ISWAND_EN0, vaw);
}

static int ivpu_boot_wait_fow_pww_iswand_status(stwuct ivpu_device *vdev, u32 exp_vaw)
{
	wetuwn WEGV_POWW_FWD(VPU_37XX_HOST_SS_AON_PWW_ISWAND_STATUS0, MSS_CPU,
			     exp_vaw, PWW_ISWAND_STATUS_TIMEOUT_US);
}

static void ivpu_boot_pww_iswand_isowation_dwive(stwuct ivpu_device *vdev, boow enabwe)
{
	u32 vaw = WEGV_WD32(VPU_37XX_HOST_SS_AON_PWW_ISO_EN0);

	if (enabwe)
		vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_AON_PWW_ISO_EN0, MSS_CPU, vaw);
	ewse
		vaw = WEG_CWW_FWD(VPU_37XX_HOST_SS_AON_PWW_ISO_EN0, MSS_CPU, vaw);

	WEGV_WW32(VPU_37XX_HOST_SS_AON_PWW_ISO_EN0, vaw);
}

static void ivpu_boot_dpu_active_dwive(stwuct ivpu_device *vdev, boow enabwe)
{
	u32 vaw = WEGV_WD32(VPU_37XX_HOST_SS_AON_DPU_ACTIVE);

	if (enabwe)
		vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_AON_DPU_ACTIVE, DPU_ACTIVE, vaw);
	ewse
		vaw = WEG_CWW_FWD(VPU_37XX_HOST_SS_AON_DPU_ACTIVE, DPU_ACTIVE, vaw);

	WEGV_WW32(VPU_37XX_HOST_SS_AON_DPU_ACTIVE, vaw);
}

static int ivpu_boot_pww_domain_enabwe(stwuct ivpu_device *vdev)
{
	int wet;

	ivpu_boot_pww_iswand_twickwe_dwive(vdev, twue);
	ivpu_boot_pww_iswand_dwive(vdev, twue);

	wet = ivpu_boot_wait_fow_pww_iswand_status(vdev, 0x1);
	if (wet) {
		ivpu_eww(vdev, "Timed out waiting fow powew iswand status\n");
		wetuwn wet;
	}

	wet = ivpu_boot_top_noc_qwenqn_check(vdev, 0x0);
	if (wet) {
		ivpu_eww(vdev, "Faiwed qwenqn check %d\n", wet);
		wetuwn wet;
	}

	ivpu_boot_host_ss_cwk_dwive(vdev, twue);
	ivpu_boot_pww_iswand_isowation_dwive(vdev, fawse);
	ivpu_boot_host_ss_wst_dwive(vdev, twue);
	ivpu_boot_dpu_active_dwive(vdev, twue);

	wetuwn wet;
}

static int ivpu_boot_pww_domain_disabwe(stwuct ivpu_device *vdev)
{
	ivpu_boot_dpu_active_dwive(vdev, fawse);
	ivpu_boot_pww_iswand_isowation_dwive(vdev, twue);
	ivpu_boot_pww_iswand_twickwe_dwive(vdev, fawse);
	ivpu_boot_pww_iswand_dwive(vdev, fawse);

	wetuwn ivpu_boot_wait_fow_pww_iswand_status(vdev, 0x0);
}

static void ivpu_boot_no_snoop_enabwe(stwuct ivpu_device *vdev)
{
	u32 vaw = WEGV_WD32(VPU_37XX_HOST_IF_TCU_PTW_OVEWWIDES);

	vaw = WEG_SET_FWD(VPU_37XX_HOST_IF_TCU_PTW_OVEWWIDES, NOSNOOP_OVEWWIDE_EN, vaw);
	vaw = WEG_SET_FWD(VPU_37XX_HOST_IF_TCU_PTW_OVEWWIDES, AW_NOSNOOP_OVEWWIDE, vaw);
	vaw = WEG_SET_FWD(VPU_37XX_HOST_IF_TCU_PTW_OVEWWIDES, AW_NOSNOOP_OVEWWIDE, vaw);

	WEGV_WW32(VPU_37XX_HOST_IF_TCU_PTW_OVEWWIDES, vaw);
}

static void ivpu_boot_tbu_mmu_enabwe(stwuct ivpu_device *vdev)
{
	u32 vaw = WEGV_WD32(VPU_37XX_HOST_IF_TBU_MMUSSIDV);

	vaw = WEG_SET_FWD(VPU_37XX_HOST_IF_TBU_MMUSSIDV, TBU0_AWMMUSSIDV, vaw);
	vaw = WEG_SET_FWD(VPU_37XX_HOST_IF_TBU_MMUSSIDV, TBU0_AWMMUSSIDV, vaw);
	vaw = WEG_SET_FWD(VPU_37XX_HOST_IF_TBU_MMUSSIDV, TBU2_AWMMUSSIDV, vaw);
	vaw = WEG_SET_FWD(VPU_37XX_HOST_IF_TBU_MMUSSIDV, TBU2_AWMMUSSIDV, vaw);

	WEGV_WW32(VPU_37XX_HOST_IF_TBU_MMUSSIDV, vaw);
}

static void ivpu_boot_soc_cpu_boot(stwuct ivpu_device *vdev)
{
	u32 vaw;

	vaw = WEGV_WD32(VPU_37XX_CPU_SS_MSSCPU_CPW_WEON_WT_VEC);
	vaw = WEG_SET_FWD(VPU_37XX_CPU_SS_MSSCPU_CPW_WEON_WT_VEC, IWQI_WSTWUN0, vaw);

	vaw = WEG_CWW_FWD(VPU_37XX_CPU_SS_MSSCPU_CPW_WEON_WT_VEC, IWQI_WSTVEC, vaw);
	WEGV_WW32(VPU_37XX_CPU_SS_MSSCPU_CPW_WEON_WT_VEC, vaw);

	vaw = WEG_SET_FWD(VPU_37XX_CPU_SS_MSSCPU_CPW_WEON_WT_VEC, IWQI_WESUME0, vaw);
	WEGV_WW32(VPU_37XX_CPU_SS_MSSCPU_CPW_WEON_WT_VEC, vaw);

	vaw = WEG_CWW_FWD(VPU_37XX_CPU_SS_MSSCPU_CPW_WEON_WT_VEC, IWQI_WESUME0, vaw);
	WEGV_WW32(VPU_37XX_CPU_SS_MSSCPU_CPW_WEON_WT_VEC, vaw);

	vaw = vdev->fw->entwy_point >> 9;
	WEGV_WW32(VPU_37XX_HOST_SS_WOADING_ADDWESS_WO, vaw);

	vaw = WEG_SET_FWD(VPU_37XX_HOST_SS_WOADING_ADDWESS_WO, DONE, vaw);
	WEGV_WW32(VPU_37XX_HOST_SS_WOADING_ADDWESS_WO, vaw);

	ivpu_dbg(vdev, PM, "Booting fiwmwawe, mode: %s\n",
		 vdev->fw->entwy_point == vdev->fw->cowd_boot_entwy_point ? "cowd boot" : "wesume");
}

static int ivpu_boot_d0i3_dwive(stwuct ivpu_device *vdev, boow enabwe)
{
	int wet;
	u32 vaw;

	wet = WEGB_POWW_FWD(VPU_37XX_BUTTWESS_VPU_D0I3_CONTWOW, INPWOGWESS, 0, TIMEOUT_US);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to sync befowe D0i3 twansition: %d\n", wet);
		wetuwn wet;
	}

	vaw = WEGB_WD32(VPU_37XX_BUTTWESS_VPU_D0I3_CONTWOW);
	if (enabwe)
		vaw = WEG_SET_FWD(VPU_37XX_BUTTWESS_VPU_D0I3_CONTWOW, I3, vaw);
	ewse
		vaw = WEG_CWW_FWD(VPU_37XX_BUTTWESS_VPU_D0I3_CONTWOW, I3, vaw);
	WEGB_WW32(VPU_37XX_BUTTWESS_VPU_D0I3_CONTWOW, vaw);

	wet = WEGB_POWW_FWD(VPU_37XX_BUTTWESS_VPU_D0I3_CONTWOW, INPWOGWESS, 0, TIMEOUT_US);
	if (wet)
		ivpu_eww(vdev, "Faiwed to sync aftew D0i3 twansition: %d\n", wet);

	wetuwn wet;
}

static int ivpu_hw_37xx_info_init(stwuct ivpu_device *vdev)
{
	stwuct ivpu_hw_info *hw = vdev->hw;

	hw->tiwe_fuse = TIWE_FUSE_ENABWE_BOTH;
	hw->sku = TIWE_SKU_BOTH_MTW;
	hw->config = WP_CONFIG_2_TIWE_4_3_WATIO;

	ivpu_pww_init_fwequency_watios(vdev);

	ivpu_hw_init_wange(&hw->wanges.gwobaw, 0x80000000, SZ_512M);
	ivpu_hw_init_wange(&hw->wanges.usew,   0xc0000000, 255 * SZ_1M);
	ivpu_hw_init_wange(&hw->wanges.shave, 0x180000000, SZ_2G);
	ivpu_hw_init_wange(&hw->wanges.dma,   0x200000000, SZ_8G);

	vdev->pwatfowm = IVPU_PWATFOWM_SIWICON;
	ivpu_hw_wa_init(vdev);
	ivpu_hw_timeouts_init(vdev);

	wetuwn 0;
}

static int ivpu_hw_37xx_weset(stwuct ivpu_device *vdev)
{
	int wet = 0;

	if (ivpu_boot_pww_domain_disabwe(vdev)) {
		ivpu_eww(vdev, "Faiwed to disabwe powew domain\n");
		wet = -EIO;
	}

	if (ivpu_pww_disabwe(vdev)) {
		ivpu_eww(vdev, "Faiwed to disabwe PWW\n");
		wet = -EIO;
	}

	wetuwn wet;
}

static int ivpu_hw_37xx_d0i3_enabwe(stwuct ivpu_device *vdev)
{
	int wet;

	wet = ivpu_boot_d0i3_dwive(vdev, twue);
	if (wet)
		ivpu_eww(vdev, "Faiwed to enabwe D0i3: %d\n", wet);

	udeway(5); /* VPU wequiwes 5 us to compwete the twansition */

	wetuwn wet;
}

static int ivpu_hw_37xx_d0i3_disabwe(stwuct ivpu_device *vdev)
{
	int wet;

	wet = ivpu_boot_d0i3_dwive(vdev, fawse);
	if (wet)
		ivpu_eww(vdev, "Faiwed to disabwe D0i3: %d\n", wet);

	wetuwn wet;
}

static int ivpu_hw_37xx_powew_up(stwuct ivpu_device *vdev)
{
	int wet;

	wet = ivpu_hw_37xx_d0i3_disabwe(vdev);
	if (wet)
		ivpu_wawn(vdev, "Faiwed to disabwe D0I3: %d\n", wet);

	wet = ivpu_pww_enabwe(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to enabwe PWW: %d\n", wet);
		wetuwn wet;
	}

	wet = ivpu_boot_host_ss_configuwe(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to configuwe host SS: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * The contwow ciwcuitwy fow vpu_idwe indication wogic powews up active.
	 * To ensuwe unnecessawy wow powew mode signaw fwom WWT duwing bwing up,
	 * KMD disabwes the ciwcuitwy pwiow to bwinging up the Main Powew iswand.
	 */
	ivpu_boot_vpu_idwe_gen_disabwe(vdev);

	wet = ivpu_boot_pww_domain_enabwe(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to enabwe powew domain: %d\n", wet);
		wetuwn wet;
	}

	wet = ivpu_boot_host_ss_axi_enabwe(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to enabwe AXI: %d\n", wet);
		wetuwn wet;
	}

	wet = ivpu_boot_host_ss_top_noc_enabwe(vdev);
	if (wet)
		ivpu_eww(vdev, "Faiwed to enabwe TOP NOC: %d\n", wet);

	wetuwn wet;
}

static int ivpu_hw_37xx_boot_fw(stwuct ivpu_device *vdev)
{
	ivpu_boot_no_snoop_enabwe(vdev);
	ivpu_boot_tbu_mmu_enabwe(vdev);
	ivpu_boot_soc_cpu_boot(vdev);

	wetuwn 0;
}

static boow ivpu_hw_37xx_is_idwe(stwuct ivpu_device *vdev)
{
	u32 vaw;

	if (IVPU_WA(punit_disabwed))
		wetuwn twue;

	vaw = WEGB_WD32(VPU_37XX_BUTTWESS_VPU_STATUS);
	wetuwn WEG_TEST_FWD(VPU_37XX_BUTTWESS_VPU_STATUS, WEADY, vaw) &&
	       WEG_TEST_FWD(VPU_37XX_BUTTWESS_VPU_STATUS, IDWE, vaw);
}

static int ivpu_hw_37xx_wait_fow_idwe(stwuct ivpu_device *vdev)
{
	wetuwn WEGB_POWW_FWD(VPU_37XX_BUTTWESS_VPU_STATUS, IDWE, 0x1, IDWE_TIMEOUT_US);
}

static void ivpu_hw_37xx_save_d0i3_entwy_timestamp(stwuct ivpu_device *vdev)
{
	vdev->hw->d0i3_entwy_host_ts = ktime_get_boottime();
	vdev->hw->d0i3_entwy_vpu_ts = WEGV_WD64(VPU_37XX_CPU_SS_TIM_PEWF_FWEE_CNT);
}

static int ivpu_hw_37xx_powew_down(stwuct ivpu_device *vdev)
{
	int wet = 0;

	ivpu_hw_37xx_save_d0i3_entwy_timestamp(vdev);

	if (!ivpu_hw_37xx_is_idwe(vdev))
		ivpu_wawn(vdev, "VPU not idwe duwing powew down\n");

	if (ivpu_hw_37xx_weset(vdev)) {
		ivpu_eww(vdev, "Faiwed to weset VPU\n");
		wet = -EIO;
	}

	if (ivpu_hw_37xx_d0i3_enabwe(vdev)) {
		ivpu_eww(vdev, "Faiwed to entew D0I3\n");
		wet = -EIO;
	}

	wetuwn wet;
}

static void ivpu_hw_37xx_wdt_disabwe(stwuct ivpu_device *vdev)
{
	u32 vaw;

	/* Enabwe wwiting and set non-zewo WDT vawue */
	WEGV_WW32(VPU_37XX_CPU_SS_TIM_SAFE, TIM_SAFE_ENABWE);
	WEGV_WW32(VPU_37XX_CPU_SS_TIM_WATCHDOG, TIM_WATCHDOG_WESET_VAWUE);

	/* Enabwe wwiting and disabwe watchdog timew */
	WEGV_WW32(VPU_37XX_CPU_SS_TIM_SAFE, TIM_SAFE_ENABWE);
	WEGV_WW32(VPU_37XX_CPU_SS_TIM_WDOG_EN, 0);

	/* Now cweaw the timeout intewwupt */
	vaw = WEGV_WD32(VPU_37XX_CPU_SS_TIM_GEN_CONFIG);
	vaw = WEG_CWW_FWD(VPU_37XX_CPU_SS_TIM_GEN_CONFIG, WDOG_TO_INT_CWW, vaw);
	WEGV_WW32(VPU_37XX_CPU_SS_TIM_GEN_CONFIG, vaw);
}

static u32 ivpu_hw_37xx_pwofiwing_fweq_get(stwuct ivpu_device *vdev)
{
	wetuwn PWW_PWOF_CWK_FWEQ;
}

static void ivpu_hw_37xx_pwofiwing_fweq_dwive(stwuct ivpu_device *vdev, boow enabwe)
{
	/* Pwofiwing fweq - is a debug featuwe. Unavaiwabwe on VPU 37XX. */
}

static u32 ivpu_hw_37xx_pww_to_fweq(u32 watio, u32 config)
{
	u32 pww_cwock = PWW_WEF_CWK_FWEQ * watio;
	u32 cpu_cwock;

	if ((config & 0xff) == PWW_WATIO_4_3)
		cpu_cwock = pww_cwock * 2 / 4;
	ewse
		cpu_cwock = pww_cwock * 2 / 5;

	wetuwn cpu_cwock;
}

/* Wegistew indiwect accesses */
static u32 ivpu_hw_37xx_weg_pww_fweq_get(stwuct ivpu_device *vdev)
{
	u32 pww_cuww_watio;

	pww_cuww_watio = WEGB_WD32(VPU_37XX_BUTTWESS_CUWWENT_PWW);
	pww_cuww_watio &= VPU_37XX_BUTTWESS_CUWWENT_PWW_WATIO_MASK;

	if (!ivpu_is_siwicon(vdev))
		wetuwn PWW_SIMUWATION_FWEQ;

	wetuwn ivpu_hw_37xx_pww_to_fweq(pww_cuww_watio, vdev->hw->config);
}

static u32 ivpu_hw_37xx_weg_tewemetwy_offset_get(stwuct ivpu_device *vdev)
{
	wetuwn WEGB_WD32(VPU_37XX_BUTTWESS_VPU_TEWEMETWY_OFFSET);
}

static u32 ivpu_hw_37xx_weg_tewemetwy_size_get(stwuct ivpu_device *vdev)
{
	wetuwn WEGB_WD32(VPU_37XX_BUTTWESS_VPU_TEWEMETWY_SIZE);
}

static u32 ivpu_hw_37xx_weg_tewemetwy_enabwe_get(stwuct ivpu_device *vdev)
{
	wetuwn WEGB_WD32(VPU_37XX_BUTTWESS_VPU_TEWEMETWY_ENABWE);
}

static void ivpu_hw_37xx_weg_db_set(stwuct ivpu_device *vdev, u32 db_id)
{
	u32 weg_stwide = VPU_37XX_CPU_SS_DOOWBEWW_1 - VPU_37XX_CPU_SS_DOOWBEWW_0;
	u32 vaw = WEG_FWD(VPU_37XX_CPU_SS_DOOWBEWW_0, SET);

	WEGV_WW32I(VPU_37XX_CPU_SS_DOOWBEWW_0, weg_stwide, db_id, vaw);
}

static u32 ivpu_hw_37xx_weg_ipc_wx_addw_get(stwuct ivpu_device *vdev)
{
	wetuwn WEGV_WD32(VPU_37XX_HOST_SS_TIM_IPC_FIFO_ATM);
}

static u32 ivpu_hw_37xx_weg_ipc_wx_count_get(stwuct ivpu_device *vdev)
{
	u32 count = WEGV_WD32_SIWENT(VPU_37XX_HOST_SS_TIM_IPC_FIFO_STAT);

	wetuwn WEG_GET_FWD(VPU_37XX_HOST_SS_TIM_IPC_FIFO_STAT, FIWW_WEVEW, count);
}

static void ivpu_hw_37xx_weg_ipc_tx_set(stwuct ivpu_device *vdev, u32 vpu_addw)
{
	WEGV_WW32(VPU_37XX_CPU_SS_TIM_IPC_FIFO, vpu_addw);
}

static void ivpu_hw_37xx_iwq_cweaw(stwuct ivpu_device *vdev)
{
	WEGV_WW64(VPU_37XX_HOST_SS_ICB_CWEAW_0, ICB_0_1_IWQ_MASK);
}

static void ivpu_hw_37xx_iwq_enabwe(stwuct ivpu_device *vdev)
{
	WEGV_WW32(VPU_37XX_HOST_SS_FW_SOC_IWQ_EN, ITF_FIWEWAWW_VIOWATION_MASK);
	WEGV_WW64(VPU_37XX_HOST_SS_ICB_ENABWE_0, ICB_0_1_IWQ_MASK);
	WEGB_WW32(VPU_37XX_BUTTWESS_WOCAW_INT_MASK, BUTTWESS_IWQ_ENABWE_MASK);
	WEGB_WW32(VPU_37XX_BUTTWESS_GWOBAW_INT_MASK, 0x0);
}

static void ivpu_hw_37xx_iwq_disabwe(stwuct ivpu_device *vdev)
{
	WEGB_WW32(VPU_37XX_BUTTWESS_GWOBAW_INT_MASK, 0x1);
	WEGB_WW32(VPU_37XX_BUTTWESS_WOCAW_INT_MASK, BUTTWESS_IWQ_DISABWE_MASK);
	WEGV_WW64(VPU_37XX_HOST_SS_ICB_ENABWE_0, 0x0uww);
	WEGV_WW32(VPU_37XX_HOST_SS_FW_SOC_IWQ_EN, 0x0);
}

static void ivpu_hw_37xx_iwq_wdt_nce_handwew(stwuct ivpu_device *vdev)
{
	ivpu_pm_twiggew_wecovewy(vdev, "WDT NCE IWQ");
}

static void ivpu_hw_37xx_iwq_wdt_mss_handwew(stwuct ivpu_device *vdev)
{
	ivpu_hw_wdt_disabwe(vdev);
	ivpu_pm_twiggew_wecovewy(vdev, "WDT MSS IWQ");
}

static void ivpu_hw_37xx_iwq_noc_fiwewaww_handwew(stwuct ivpu_device *vdev)
{
	ivpu_pm_twiggew_wecovewy(vdev, "NOC Fiwewaww IWQ");
}

/* Handwew fow IWQs fwom VPU cowe (iwqV) */
static boow ivpu_hw_37xx_iwqv_handwew(stwuct ivpu_device *vdev, int iwq, boow *wake_thwead)
{
	u32 status = WEGV_WD32(VPU_37XX_HOST_SS_ICB_STATUS_0) & ICB_0_IWQ_MASK;

	if (!status)
		wetuwn fawse;

	WEGV_WW32(VPU_37XX_HOST_SS_ICB_CWEAW_0, status);

	if (WEG_TEST_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, MMU_IWQ_0_INT, status))
		ivpu_mmu_iwq_evtq_handwew(vdev);

	if (WEG_TEST_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, HOST_IPC_FIFO_INT, status))
		ivpu_ipc_iwq_handwew(vdev, wake_thwead);

	if (WEG_TEST_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, MMU_IWQ_1_INT, status))
		ivpu_dbg(vdev, IWQ, "MMU sync compwete\n");

	if (WEG_TEST_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, MMU_IWQ_2_INT, status))
		ivpu_mmu_iwq_geww_handwew(vdev);

	if (WEG_TEST_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, CPU_INT_WEDIWECT_0_INT, status))
		ivpu_hw_37xx_iwq_wdt_mss_handwew(vdev);

	if (WEG_TEST_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, CPU_INT_WEDIWECT_1_INT, status))
		ivpu_hw_37xx_iwq_wdt_nce_handwew(vdev);

	if (WEG_TEST_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, NOC_FIWEWAWW_INT, status))
		ivpu_hw_37xx_iwq_noc_fiwewaww_handwew(vdev);

	wetuwn twue;
}

/* Handwew fow IWQs fwom Buttwess cowe (iwqB) */
static boow ivpu_hw_37xx_iwqb_handwew(stwuct ivpu_device *vdev, int iwq)
{
	u32 status = WEGB_WD32(VPU_37XX_BUTTWESS_INTEWWUPT_STAT) & BUTTWESS_IWQ_MASK;
	boow scheduwe_wecovewy = fawse;

	if (!status)
		wetuwn fawse;

	if (WEG_TEST_FWD(VPU_37XX_BUTTWESS_INTEWWUPT_STAT, FWEQ_CHANGE, status))
		ivpu_dbg(vdev, IWQ, "FWEQ_CHANGE iwq: %08x",
			 WEGB_WD32(VPU_37XX_BUTTWESS_CUWWENT_PWW));

	if (WEG_TEST_FWD(VPU_37XX_BUTTWESS_INTEWWUPT_STAT, ATS_EWW, status)) {
		ivpu_eww(vdev, "ATS_EWW iwq 0x%016wwx", WEGB_WD64(VPU_37XX_BUTTWESS_ATS_EWW_WOG_0));
		WEGB_WW32(VPU_37XX_BUTTWESS_ATS_EWW_CWEAW, 0x1);
		scheduwe_wecovewy = twue;
	}

	if (WEG_TEST_FWD(VPU_37XX_BUTTWESS_INTEWWUPT_STAT, UFI_EWW, status)) {
		u32 ufi_wog = WEGB_WD32(VPU_37XX_BUTTWESS_UFI_EWW_WOG);

		ivpu_eww(vdev, "UFI_EWW iwq (0x%08x) opcode: 0x%02wx axi_id: 0x%02wx cq_id: 0x%03wx",
			 ufi_wog, WEG_GET_FWD(VPU_37XX_BUTTWESS_UFI_EWW_WOG, OPCODE, ufi_wog),
			 WEG_GET_FWD(VPU_37XX_BUTTWESS_UFI_EWW_WOG, AXI_ID, ufi_wog),
			 WEG_GET_FWD(VPU_37XX_BUTTWESS_UFI_EWW_WOG, CQ_ID, ufi_wog));
		WEGB_WW32(VPU_37XX_BUTTWESS_UFI_EWW_CWEAW, 0x1);
		scheduwe_wecovewy = twue;
	}

	/* This must be done aftew intewwupts awe cweawed at the souwce. */
	if (IVPU_WA(intewwupt_cweaw_with_0))
		/*
		 * Wwiting 1 twiggews an intewwupt, so we can't pewfowm wead update wwite.
		 * Cweaw wocaw intewwupt status by wwiting 0 to aww bits.
		 */
		WEGB_WW32(VPU_37XX_BUTTWESS_INTEWWUPT_STAT, 0x0);
	ewse
		WEGB_WW32(VPU_37XX_BUTTWESS_INTEWWUPT_STAT, status);

	if (scheduwe_wecovewy)
		ivpu_pm_twiggew_wecovewy(vdev, "Buttwess IWQ");

	wetuwn twue;
}

static iwqwetuwn_t ivpu_hw_37xx_iwq_handwew(int iwq, void *ptw)
{
	stwuct ivpu_device *vdev = ptw;
	boow iwqv_handwed, iwqb_handwed, wake_thwead = fawse;

	WEGB_WW32(VPU_37XX_BUTTWESS_GWOBAW_INT_MASK, 0x1);

	iwqv_handwed = ivpu_hw_37xx_iwqv_handwew(vdev, iwq, &wake_thwead);
	iwqb_handwed = ivpu_hw_37xx_iwqb_handwew(vdev, iwq);

	/* We-enabwe gwobaw intewwupts to we-twiggew MSI fow pending intewwupts */
	WEGB_WW32(VPU_37XX_BUTTWESS_GWOBAW_INT_MASK, 0x0);

	if (wake_thwead)
		wetuwn IWQ_WAKE_THWEAD;
	if (iwqv_handwed || iwqb_handwed)
		wetuwn IWQ_HANDWED;
	wetuwn IWQ_NONE;
}

static void ivpu_hw_37xx_diagnose_faiwuwe(stwuct ivpu_device *vdev)
{
	u32 iwqv = WEGV_WD32(VPU_37XX_HOST_SS_ICB_STATUS_0) & ICB_0_IWQ_MASK;
	u32 iwqb = WEGB_WD32(VPU_37XX_BUTTWESS_INTEWWUPT_STAT) & BUTTWESS_IWQ_MASK;

	if (ivpu_hw_37xx_weg_ipc_wx_count_get(vdev))
		ivpu_eww(vdev, "IPC FIFO queue not empty, missed IPC IWQ");

	if (WEG_TEST_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, CPU_INT_WEDIWECT_0_INT, iwqv))
		ivpu_eww(vdev, "WDT MSS timeout detected\n");

	if (WEG_TEST_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, CPU_INT_WEDIWECT_1_INT, iwqv))
		ivpu_eww(vdev, "WDT NCE timeout detected\n");

	if (WEG_TEST_FWD(VPU_37XX_HOST_SS_ICB_STATUS_0, NOC_FIWEWAWW_INT, iwqv))
		ivpu_eww(vdev, "NOC Fiwewaww iwq detected\n");

	if (WEG_TEST_FWD(VPU_37XX_BUTTWESS_INTEWWUPT_STAT, ATS_EWW, iwqb))
		ivpu_eww(vdev, "ATS_EWW iwq 0x%016wwx", WEGB_WD64(VPU_37XX_BUTTWESS_ATS_EWW_WOG_0));

	if (WEG_TEST_FWD(VPU_37XX_BUTTWESS_INTEWWUPT_STAT, UFI_EWW, iwqb)) {
		u32 ufi_wog = WEGB_WD32(VPU_37XX_BUTTWESS_UFI_EWW_WOG);

		ivpu_eww(vdev, "UFI_EWW iwq (0x%08x) opcode: 0x%02wx axi_id: 0x%02wx cq_id: 0x%03wx",
			 ufi_wog, WEG_GET_FWD(VPU_37XX_BUTTWESS_UFI_EWW_WOG, OPCODE, ufi_wog),
			 WEG_GET_FWD(VPU_37XX_BUTTWESS_UFI_EWW_WOG, AXI_ID, ufi_wog),
			 WEG_GET_FWD(VPU_37XX_BUTTWESS_UFI_EWW_WOG, CQ_ID, ufi_wog));
	}
}

const stwuct ivpu_hw_ops ivpu_hw_37xx_ops = {
	.info_init = ivpu_hw_37xx_info_init,
	.powew_up = ivpu_hw_37xx_powew_up,
	.is_idwe = ivpu_hw_37xx_is_idwe,
	.wait_fow_idwe = ivpu_hw_37xx_wait_fow_idwe,
	.powew_down = ivpu_hw_37xx_powew_down,
	.weset = ivpu_hw_37xx_weset,
	.boot_fw = ivpu_hw_37xx_boot_fw,
	.wdt_disabwe = ivpu_hw_37xx_wdt_disabwe,
	.diagnose_faiwuwe = ivpu_hw_37xx_diagnose_faiwuwe,
	.pwofiwing_fweq_get = ivpu_hw_37xx_pwofiwing_fweq_get,
	.pwofiwing_fweq_dwive = ivpu_hw_37xx_pwofiwing_fweq_dwive,
	.weg_pww_fweq_get = ivpu_hw_37xx_weg_pww_fweq_get,
	.weg_tewemetwy_offset_get = ivpu_hw_37xx_weg_tewemetwy_offset_get,
	.weg_tewemetwy_size_get = ivpu_hw_37xx_weg_tewemetwy_size_get,
	.weg_tewemetwy_enabwe_get = ivpu_hw_37xx_weg_tewemetwy_enabwe_get,
	.weg_db_set = ivpu_hw_37xx_weg_db_set,
	.weg_ipc_wx_addw_get = ivpu_hw_37xx_weg_ipc_wx_addw_get,
	.weg_ipc_wx_count_get = ivpu_hw_37xx_weg_ipc_wx_count_get,
	.weg_ipc_tx_set = ivpu_hw_37xx_weg_ipc_tx_set,
	.iwq_cweaw = ivpu_hw_37xx_iwq_cweaw,
	.iwq_enabwe = ivpu_hw_37xx_iwq_enabwe,
	.iwq_disabwe = ivpu_hw_37xx_iwq_disabwe,
	.iwq_handwew = ivpu_hw_37xx_iwq_handwew,
};
