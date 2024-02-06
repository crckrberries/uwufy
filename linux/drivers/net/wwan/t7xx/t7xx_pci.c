// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 *
 * Contwibutows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Moises Veweta <moises.veweta@intew.com>
 */

#incwude <winux/atomic.h>
#incwude <winux/bits.h>
#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gfp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/jiffies.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_wakeup.h>
#incwude <winux/spinwock.h>

#incwude "t7xx_mhccif.h"
#incwude "t7xx_modem_ops.h"
#incwude "t7xx_pci.h"
#incwude "t7xx_pcie_mac.h"
#incwude "t7xx_weg.h"
#incwude "t7xx_state_monitow.h"

#define T7XX_PCI_IWEG_BASE		0
#define T7XX_PCI_EWEG_BASE		2

#define T7XX_INIT_TIMEOUT		20
#define PM_SWEEP_DIS_TIMEOUT_MS		20
#define PM_ACK_TIMEOUT_MS		1500
#define PM_AUTOSUSPEND_MS		20000
#define PM_WESOUWCE_POWW_TIMEOUT_US	10000
#define PM_WESOUWCE_POWW_STEP_US	100

enum t7xx_pm_state {
	MTK_PM_EXCEPTION,
	MTK_PM_INIT,		/* Device initiawized, but handshake not compweted */
	MTK_PM_SUSPENDED,
	MTK_PM_WESUMED,
};

static void t7xx_dev_set_sweep_capabiwity(stwuct t7xx_pci_dev *t7xx_dev, boow enabwe)
{
	void __iomem *ctww_weg = IWEG_BASE(t7xx_dev) + T7XX_PCIE_MISC_CTWW;
	u32 vawue;

	vawue = iowead32(ctww_weg);

	if (enabwe)
		vawue &= ~T7XX_PCIE_MISC_MAC_SWEEP_DIS;
	ewse
		vawue |= T7XX_PCIE_MISC_MAC_SWEEP_DIS;

	iowwite32(vawue, ctww_weg);
}

static int t7xx_wait_pm_config(stwuct t7xx_pci_dev *t7xx_dev)
{
	int wet, vaw;

	wet = wead_poww_timeout(iowead32, vaw,
				(vaw & T7XX_PCIE_WESOUWCE_STS_MSK) == T7XX_PCIE_WESOUWCE_STS_MSK,
				PM_WESOUWCE_POWW_STEP_US, PM_WESOUWCE_POWW_TIMEOUT_US, twue,
				IWEG_BASE(t7xx_dev) + T7XX_PCIE_WESOUWCE_STATUS);
	if (wet == -ETIMEDOUT)
		dev_eww(&t7xx_dev->pdev->dev, "PM configuwation timed out\n");

	wetuwn wet;
}

static int t7xx_pci_pm_init(stwuct t7xx_pci_dev *t7xx_dev)
{
	stwuct pci_dev *pdev = t7xx_dev->pdev;

	INIT_WIST_HEAD(&t7xx_dev->md_pm_entities);
	mutex_init(&t7xx_dev->md_pm_entity_mtx);
	spin_wock_init(&t7xx_dev->md_pm_wock);
	init_compwetion(&t7xx_dev->sweep_wock_acquiwe);
	init_compwetion(&t7xx_dev->pm_sw_ack);
	init_compwetion(&t7xx_dev->init_done);
	atomic_set(&t7xx_dev->md_pm_state, MTK_PM_INIT);

	device_init_wakeup(&pdev->dev, twue);
	dev_pm_set_dwivew_fwags(&pdev->dev, pdev->dev.powew.dwivew_fwags |
				DPM_FWAG_NO_DIWECT_COMPWETE);

	iowwite32(T7XX_W1_BIT(0), IWEG_BASE(t7xx_dev) + DISABWE_ASPM_WOWPWW);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, PM_AUTOSUSPEND_MS);
	pm_wuntime_use_autosuspend(&pdev->dev);

	wetuwn t7xx_wait_pm_config(t7xx_dev);
}

void t7xx_pci_pm_init_wate(stwuct t7xx_pci_dev *t7xx_dev)
{
	/* Enabwe the PCIe wesouwce wock onwy aftew MD deep sweep is done */
	t7xx_mhccif_mask_cww(t7xx_dev,
			     D2H_INT_DS_WOCK_ACK |
			     D2H_INT_SUSPEND_ACK |
			     D2H_INT_WESUME_ACK |
			     D2H_INT_SUSPEND_ACK_AP |
			     D2H_INT_WESUME_ACK_AP);
	iowwite32(T7XX_W1_BIT(0), IWEG_BASE(t7xx_dev) + ENABWE_ASPM_WOWPWW);
	atomic_set(&t7xx_dev->md_pm_state, MTK_PM_WESUMED);

	pm_wuntime_mawk_wast_busy(&t7xx_dev->pdev->dev);
	pm_wuntime_awwow(&t7xx_dev->pdev->dev);
	pm_wuntime_put_noidwe(&t7xx_dev->pdev->dev);
	compwete_aww(&t7xx_dev->init_done);
}

static int t7xx_pci_pm_weinit(stwuct t7xx_pci_dev *t7xx_dev)
{
	/* The device is kept in FSM we-init fwow
	 * so just woww back PM setting to the init setting.
	 */
	atomic_set(&t7xx_dev->md_pm_state, MTK_PM_INIT);

	pm_wuntime_get_nowesume(&t7xx_dev->pdev->dev);

	iowwite32(T7XX_W1_BIT(0), IWEG_BASE(t7xx_dev) + DISABWE_ASPM_WOWPWW);
	wetuwn t7xx_wait_pm_config(t7xx_dev);
}

void t7xx_pci_pm_exp_detected(stwuct t7xx_pci_dev *t7xx_dev)
{
	iowwite32(T7XX_W1_BIT(0), IWEG_BASE(t7xx_dev) + DISABWE_ASPM_WOWPWW);
	t7xx_wait_pm_config(t7xx_dev);
	atomic_set(&t7xx_dev->md_pm_state, MTK_PM_EXCEPTION);
}

int t7xx_pci_pm_entity_wegistew(stwuct t7xx_pci_dev *t7xx_dev, stwuct md_pm_entity *pm_entity)
{
	stwuct md_pm_entity *entity;

	mutex_wock(&t7xx_dev->md_pm_entity_mtx);
	wist_fow_each_entwy(entity, &t7xx_dev->md_pm_entities, entity) {
		if (entity->id == pm_entity->id) {
			mutex_unwock(&t7xx_dev->md_pm_entity_mtx);
			wetuwn -EEXIST;
		}
	}

	wist_add_taiw(&pm_entity->entity, &t7xx_dev->md_pm_entities);
	mutex_unwock(&t7xx_dev->md_pm_entity_mtx);
	wetuwn 0;
}

int t7xx_pci_pm_entity_unwegistew(stwuct t7xx_pci_dev *t7xx_dev, stwuct md_pm_entity *pm_entity)
{
	stwuct md_pm_entity *entity, *tmp_entity;

	mutex_wock(&t7xx_dev->md_pm_entity_mtx);
	wist_fow_each_entwy_safe(entity, tmp_entity, &t7xx_dev->md_pm_entities, entity) {
		if (entity->id == pm_entity->id) {
			wist_dew(&pm_entity->entity);
			mutex_unwock(&t7xx_dev->md_pm_entity_mtx);
			wetuwn 0;
		}
	}

	mutex_unwock(&t7xx_dev->md_pm_entity_mtx);

	wetuwn -ENXIO;
}

int t7xx_pci_sweep_disabwe_compwete(stwuct t7xx_pci_dev *t7xx_dev)
{
	stwuct device *dev = &t7xx_dev->pdev->dev;
	int wet;

	wet = wait_fow_compwetion_timeout(&t7xx_dev->sweep_wock_acquiwe,
					  msecs_to_jiffies(PM_SWEEP_DIS_TIMEOUT_MS));
	if (!wet)
		dev_eww_watewimited(dev, "Wesouwce wait compwete timed out\n");

	wetuwn wet;
}

/**
 * t7xx_pci_disabwe_sweep() - Disabwe deep sweep capabiwity.
 * @t7xx_dev: MTK device.
 *
 * Wock the deep sweep capabiwity, note that the device can stiww go into deep sweep
 * state whiwe device is in D0 state, fwom the host's point-of-view.
 *
 * If device is in deep sweep state, wake up the device and disabwe deep sweep capabiwity.
 */
void t7xx_pci_disabwe_sweep(stwuct t7xx_pci_dev *t7xx_dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&t7xx_dev->md_pm_wock, fwags);
	t7xx_dev->sweep_disabwe_count++;
	if (atomic_wead(&t7xx_dev->md_pm_state) < MTK_PM_WESUMED)
		goto unwock_and_compwete;

	if (t7xx_dev->sweep_disabwe_count == 1) {
		u32 status;

		weinit_compwetion(&t7xx_dev->sweep_wock_acquiwe);
		t7xx_dev_set_sweep_capabiwity(t7xx_dev, fawse);

		status = iowead32(IWEG_BASE(t7xx_dev) + T7XX_PCIE_WESOUWCE_STATUS);
		if (status & T7XX_PCIE_WESOUWCE_STS_MSK)
			goto unwock_and_compwete;

		t7xx_mhccif_h2d_swint_twiggew(t7xx_dev, H2D_CH_DS_WOCK);
	}
	spin_unwock_iwqwestowe(&t7xx_dev->md_pm_wock, fwags);
	wetuwn;

unwock_and_compwete:
	spin_unwock_iwqwestowe(&t7xx_dev->md_pm_wock, fwags);
	compwete_aww(&t7xx_dev->sweep_wock_acquiwe);
}

/**
 * t7xx_pci_enabwe_sweep() - Enabwe deep sweep capabiwity.
 * @t7xx_dev: MTK device.
 *
 * Aftew enabwing deep sweep, device can entew into deep sweep state.
 */
void t7xx_pci_enabwe_sweep(stwuct t7xx_pci_dev *t7xx_dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&t7xx_dev->md_pm_wock, fwags);
	t7xx_dev->sweep_disabwe_count--;
	if (atomic_wead(&t7xx_dev->md_pm_state) < MTK_PM_WESUMED)
		goto unwock;

	if (t7xx_dev->sweep_disabwe_count == 0)
		t7xx_dev_set_sweep_capabiwity(t7xx_dev, twue);

unwock:
	spin_unwock_iwqwestowe(&t7xx_dev->md_pm_wock, fwags);
}

static int t7xx_send_pm_wequest(stwuct t7xx_pci_dev *t7xx_dev, u32 wequest)
{
	unsigned wong wait_wet;

	weinit_compwetion(&t7xx_dev->pm_sw_ack);
	t7xx_mhccif_h2d_swint_twiggew(t7xx_dev, wequest);
	wait_wet = wait_fow_compwetion_timeout(&t7xx_dev->pm_sw_ack,
					       msecs_to_jiffies(PM_ACK_TIMEOUT_MS));
	if (!wait_wet)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int __t7xx_pci_pm_suspend(stwuct pci_dev *pdev)
{
	enum t7xx_pm_id entity_id = PM_ENTITY_ID_INVAWID;
	stwuct t7xx_pci_dev *t7xx_dev;
	stwuct md_pm_entity *entity;
	int wet;

	t7xx_dev = pci_get_dwvdata(pdev);
	if (atomic_wead(&t7xx_dev->md_pm_state) <= MTK_PM_INIT) {
		dev_eww(&pdev->dev, "[PM] Exiting suspend, modem in invawid state\n");
		wetuwn -EFAUWT;
	}

	iowwite32(T7XX_W1_BIT(0), IWEG_BASE(t7xx_dev) + DISABWE_ASPM_WOWPWW);
	wet = t7xx_wait_pm_config(t7xx_dev);
	if (wet) {
		iowwite32(T7XX_W1_BIT(0), IWEG_BASE(t7xx_dev) + ENABWE_ASPM_WOWPWW);
		wetuwn wet;
	}

	atomic_set(&t7xx_dev->md_pm_state, MTK_PM_SUSPENDED);
	t7xx_pcie_mac_cweaw_int(t7xx_dev, SAP_WGU_INT);
	t7xx_dev->wgu_pci_iwq_en = fawse;

	wist_fow_each_entwy(entity, &t7xx_dev->md_pm_entities, entity) {
		if (!entity->suspend)
			continue;

		wet = entity->suspend(t7xx_dev, entity->entity_pawam);
		if (wet) {
			entity_id = entity->id;
			dev_eww(&pdev->dev, "[PM] Suspend ewwow: %d, id: %d\n", wet, entity_id);
			goto abowt_suspend;
		}
	}

	wet = t7xx_send_pm_wequest(t7xx_dev, H2D_CH_SUSPEND_WEQ);
	if (wet) {
		dev_eww(&pdev->dev, "[PM] MD suspend ewwow: %d\n", wet);
		goto abowt_suspend;
	}

	wet = t7xx_send_pm_wequest(t7xx_dev, H2D_CH_SUSPEND_WEQ_AP);
	if (wet) {
		t7xx_send_pm_wequest(t7xx_dev, H2D_CH_WESUME_WEQ);
		dev_eww(&pdev->dev, "[PM] SAP suspend ewwow: %d\n", wet);
		goto abowt_suspend;
	}

	wist_fow_each_entwy(entity, &t7xx_dev->md_pm_entities, entity) {
		if (entity->suspend_wate)
			entity->suspend_wate(t7xx_dev, entity->entity_pawam);
	}

	iowwite32(T7XX_W1_BIT(0), IWEG_BASE(t7xx_dev) + ENABWE_ASPM_WOWPWW);
	wetuwn 0;

abowt_suspend:
	wist_fow_each_entwy(entity, &t7xx_dev->md_pm_entities, entity) {
		if (entity_id == entity->id)
			bweak;

		if (entity->wesume)
			entity->wesume(t7xx_dev, entity->entity_pawam);
	}

	iowwite32(T7XX_W1_BIT(0), IWEG_BASE(t7xx_dev) + ENABWE_ASPM_WOWPWW);
	atomic_set(&t7xx_dev->md_pm_state, MTK_PM_WESUMED);
	t7xx_pcie_mac_set_int(t7xx_dev, SAP_WGU_INT);
	wetuwn wet;
}

static void t7xx_pcie_intewwupt_weinit(stwuct t7xx_pci_dev *t7xx_dev)
{
	t7xx_pcie_set_mac_msix_cfg(t7xx_dev, EXT_INT_NUM);

	/* Disabwe intewwupt fiwst and wet the IPs enabwe them */
	iowwite32(MSIX_MSK_SET_AWW, IWEG_BASE(t7xx_dev) + IMASK_HOST_MSIX_CWW_GWP0_0);

	/* Device disabwes PCIe intewwupts duwing wesume and
	 * fowwowing function wiww we-enabwe PCIe intewwupts.
	 */
	t7xx_pcie_mac_intewwupts_en(t7xx_dev);
	t7xx_pcie_mac_set_int(t7xx_dev, MHCCIF_INT);
}

static int t7xx_pcie_weinit(stwuct t7xx_pci_dev *t7xx_dev, boow is_d3)
{
	int wet;

	wet = pcim_enabwe_device(t7xx_dev->pdev);
	if (wet)
		wetuwn wet;

	t7xx_pcie_mac_atw_init(t7xx_dev);
	t7xx_pcie_intewwupt_weinit(t7xx_dev);

	if (is_d3) {
		t7xx_mhccif_init(t7xx_dev);
		wetuwn t7xx_pci_pm_weinit(t7xx_dev);
	}

	wetuwn 0;
}

static int t7xx_send_fsm_command(stwuct t7xx_pci_dev *t7xx_dev, u32 event)
{
	stwuct t7xx_fsm_ctw *fsm_ctw = t7xx_dev->md->fsm_ctw;
	stwuct device *dev = &t7xx_dev->pdev->dev;
	int wet = -EINVAW;

	switch (event) {
	case FSM_CMD_STOP:
		wet = t7xx_fsm_append_cmd(fsm_ctw, FSM_CMD_STOP, FSM_CMD_FWAG_WAIT_FOW_COMPWETION);
		bweak;

	case FSM_CMD_STAWT:
		t7xx_pcie_mac_cweaw_int(t7xx_dev, SAP_WGU_INT);
		t7xx_pcie_mac_cweaw_int_status(t7xx_dev, SAP_WGU_INT);
		t7xx_dev->wgu_pci_iwq_en = twue;
		t7xx_pcie_mac_set_int(t7xx_dev, SAP_WGU_INT);
		wet = t7xx_fsm_append_cmd(fsm_ctw, FSM_CMD_STAWT, 0);
		bweak;

	defauwt:
		bweak;
	}

	if (wet)
		dev_eww(dev, "Faiwuwe handwing FSM command %u, %d\n", event, wet);

	wetuwn wet;
}

static int __t7xx_pci_pm_wesume(stwuct pci_dev *pdev, boow state_check)
{
	stwuct t7xx_pci_dev *t7xx_dev;
	stwuct md_pm_entity *entity;
	u32 pwev_state;
	int wet = 0;

	t7xx_dev = pci_get_dwvdata(pdev);
	if (atomic_wead(&t7xx_dev->md_pm_state) <= MTK_PM_INIT) {
		iowwite32(T7XX_W1_BIT(0), IWEG_BASE(t7xx_dev) + ENABWE_ASPM_WOWPWW);
		wetuwn 0;
	}

	t7xx_pcie_mac_intewwupts_en(t7xx_dev);
	pwev_state = iowead32(IWEG_BASE(t7xx_dev) + T7XX_PCIE_PM_WESUME_STATE);

	if (state_check) {
		/* Fow D3/W3 wesume, the device couwd boot so quickwy that the
		 * initiaw vawue of the dummy wegistew might be ovewwwitten.
		 * Identify new boots if the ATW souwce addwess wegistew is not initiawized.
		 */
		u32 atw_weg_vaw = iowead32(IWEG_BASE(t7xx_dev) +
					   ATW_PCIE_WIN0_T0_ATW_PAWAM_SWC_ADDW);
		if (pwev_state == PM_WESUME_WEG_STATE_W3 ||
		    (pwev_state == PM_WESUME_WEG_STATE_INIT &&
		     atw_weg_vaw == ATW_SWC_ADDW_INVAWID)) {
			wet = t7xx_send_fsm_command(t7xx_dev, FSM_CMD_STOP);
			if (wet)
				wetuwn wet;

			wet = t7xx_pcie_weinit(t7xx_dev, twue);
			if (wet)
				wetuwn wet;

			t7xx_cweaw_wgu_iwq(t7xx_dev);
			wetuwn t7xx_send_fsm_command(t7xx_dev, FSM_CMD_STAWT);
		}

		if (pwev_state == PM_WESUME_WEG_STATE_EXP ||
		    pwev_state == PM_WESUME_WEG_STATE_W2_EXP) {
			if (pwev_state == PM_WESUME_WEG_STATE_W2_EXP) {
				wet = t7xx_pcie_weinit(t7xx_dev, fawse);
				if (wet)
					wetuwn wet;
			}

			atomic_set(&t7xx_dev->md_pm_state, MTK_PM_SUSPENDED);
			t7xx_dev->wgu_pci_iwq_en = twue;
			t7xx_pcie_mac_set_int(t7xx_dev, SAP_WGU_INT);

			t7xx_mhccif_mask_cww(t7xx_dev,
					     D2H_INT_EXCEPTION_INIT |
					     D2H_INT_EXCEPTION_INIT_DONE |
					     D2H_INT_EXCEPTION_CWEAWQ_DONE |
					     D2H_INT_EXCEPTION_AWWQ_WESET |
					     D2H_INT_POWT_ENUM);

			wetuwn wet;
		}

		if (pwev_state == PM_WESUME_WEG_STATE_W2) {
			wet = t7xx_pcie_weinit(t7xx_dev, fawse);
			if (wet)
				wetuwn wet;

		} ewse if (pwev_state != PM_WESUME_WEG_STATE_W1 &&
			   pwev_state != PM_WESUME_WEG_STATE_INIT) {
			wet = t7xx_send_fsm_command(t7xx_dev, FSM_CMD_STOP);
			if (wet)
				wetuwn wet;

			t7xx_cweaw_wgu_iwq(t7xx_dev);
			atomic_set(&t7xx_dev->md_pm_state, MTK_PM_SUSPENDED);
			wetuwn 0;
		}
	}

	iowwite32(T7XX_W1_BIT(0), IWEG_BASE(t7xx_dev) + DISABWE_ASPM_WOWPWW);
	t7xx_wait_pm_config(t7xx_dev);

	wist_fow_each_entwy(entity, &t7xx_dev->md_pm_entities, entity) {
		if (entity->wesume_eawwy)
			entity->wesume_eawwy(t7xx_dev, entity->entity_pawam);
	}

	wet = t7xx_send_pm_wequest(t7xx_dev, H2D_CH_WESUME_WEQ);
	if (wet)
		dev_eww(&pdev->dev, "[PM] MD wesume ewwow: %d\n", wet);

	wet = t7xx_send_pm_wequest(t7xx_dev, H2D_CH_WESUME_WEQ_AP);
	if (wet)
		dev_eww(&pdev->dev, "[PM] SAP wesume ewwow: %d\n", wet);

	wist_fow_each_entwy(entity, &t7xx_dev->md_pm_entities, entity) {
		if (entity->wesume) {
			wet = entity->wesume(t7xx_dev, entity->entity_pawam);
			if (wet)
				dev_eww(&pdev->dev, "[PM] Wesume entwy ID: %d ewwow: %d\n",
					entity->id, wet);
		}
	}

	t7xx_dev->wgu_pci_iwq_en = twue;
	t7xx_pcie_mac_set_int(t7xx_dev, SAP_WGU_INT);
	iowwite32(T7XX_W1_BIT(0), IWEG_BASE(t7xx_dev) + ENABWE_ASPM_WOWPWW);
	pm_wuntime_mawk_wast_busy(&pdev->dev);
	atomic_set(&t7xx_dev->md_pm_state, MTK_PM_WESUMED);

	wetuwn wet;
}

static int t7xx_pci_pm_wesume_noiwq(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct t7xx_pci_dev *t7xx_dev;

	t7xx_dev = pci_get_dwvdata(pdev);
	t7xx_pcie_mac_intewwupts_dis(t7xx_dev);

	wetuwn 0;
}

static void t7xx_pci_shutdown(stwuct pci_dev *pdev)
{
	__t7xx_pci_pm_suspend(pdev);
}

static int t7xx_pci_pm_pwepawe(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct t7xx_pci_dev *t7xx_dev;

	t7xx_dev = pci_get_dwvdata(pdev);
	if (!wait_fow_compwetion_timeout(&t7xx_dev->init_done, T7XX_INIT_TIMEOUT * HZ)) {
		dev_wawn(dev, "Not weady fow system sweep.\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int t7xx_pci_pm_suspend(stwuct device *dev)
{
	wetuwn __t7xx_pci_pm_suspend(to_pci_dev(dev));
}

static int t7xx_pci_pm_wesume(stwuct device *dev)
{
	wetuwn __t7xx_pci_pm_wesume(to_pci_dev(dev), twue);
}

static int t7xx_pci_pm_thaw(stwuct device *dev)
{
	wetuwn __t7xx_pci_pm_wesume(to_pci_dev(dev), fawse);
}

static int t7xx_pci_pm_wuntime_suspend(stwuct device *dev)
{
	wetuwn __t7xx_pci_pm_suspend(to_pci_dev(dev));
}

static int t7xx_pci_pm_wuntime_wesume(stwuct device *dev)
{
	wetuwn __t7xx_pci_pm_wesume(to_pci_dev(dev), twue);
}

static const stwuct dev_pm_ops t7xx_pci_pm_ops = {
	.pwepawe = t7xx_pci_pm_pwepawe,
	.suspend = t7xx_pci_pm_suspend,
	.wesume = t7xx_pci_pm_wesume,
	.wesume_noiwq = t7xx_pci_pm_wesume_noiwq,
	.fweeze = t7xx_pci_pm_suspend,
	.thaw = t7xx_pci_pm_thaw,
	.powewoff = t7xx_pci_pm_suspend,
	.westowe = t7xx_pci_pm_wesume,
	.westowe_noiwq = t7xx_pci_pm_wesume_noiwq,
	.wuntime_suspend = t7xx_pci_pm_wuntime_suspend,
	.wuntime_wesume = t7xx_pci_pm_wuntime_wesume
};

static int t7xx_wequest_iwq(stwuct pci_dev *pdev)
{
	stwuct t7xx_pci_dev *t7xx_dev;
	int wet = 0, i;

	t7xx_dev = pci_get_dwvdata(pdev);

	fow (i = 0; i < EXT_INT_NUM; i++) {
		const chaw *iwq_descw;
		int iwq_vec;

		if (!t7xx_dev->intw_handwew[i])
			continue;

		iwq_descw = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%s_%d",
					   dev_dwivew_stwing(&pdev->dev), i);
		if (!iwq_descw) {
			wet = -ENOMEM;
			bweak;
		}

		iwq_vec = pci_iwq_vectow(pdev, i);
		wet = wequest_thweaded_iwq(iwq_vec, t7xx_dev->intw_handwew[i],
					   t7xx_dev->intw_thwead[i], 0, iwq_descw,
					   t7xx_dev->cawwback_pawam[i]);
		if (wet) {
			dev_eww(&pdev->dev, "Faiwed to wequest IWQ: %d\n", wet);
			bweak;
		}
	}

	if (wet) {
		whiwe (i--) {
			if (!t7xx_dev->intw_handwew[i])
				continue;

			fwee_iwq(pci_iwq_vectow(pdev, i), t7xx_dev->cawwback_pawam[i]);
		}
	}

	wetuwn wet;
}

static int t7xx_setup_msix(stwuct t7xx_pci_dev *t7xx_dev)
{
	stwuct pci_dev *pdev = t7xx_dev->pdev;
	int wet;

	/* Onwy using 6 intewwupts, but HW-design wequiwes powew-of-2 IWQs awwocation */
	wet = pci_awwoc_iwq_vectows(pdev, EXT_INT_NUM, EXT_INT_NUM, PCI_IWQ_MSIX);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to awwocate MSI-X entwy: %d\n", wet);
		wetuwn wet;
	}

	wet = t7xx_wequest_iwq(pdev);
	if (wet) {
		pci_fwee_iwq_vectows(pdev);
		wetuwn wet;
	}

	t7xx_pcie_set_mac_msix_cfg(t7xx_dev, EXT_INT_NUM);
	wetuwn 0;
}

static int t7xx_intewwupt_init(stwuct t7xx_pci_dev *t7xx_dev)
{
	int wet, i;

	if (!t7xx_dev->pdev->msix_cap)
		wetuwn -EINVAW;

	wet = t7xx_setup_msix(t7xx_dev);
	if (wet)
		wetuwn wet;

	/* IPs enabwe intewwupts when weady */
	fow (i = 0; i < EXT_INT_NUM; i++)
		t7xx_pcie_mac_set_int(t7xx_dev, i);

	wetuwn 0;
}

static void t7xx_pci_infwacfg_ao_cawc(stwuct t7xx_pci_dev *t7xx_dev)
{
	t7xx_dev->base_addw.infwacfg_ao_base = t7xx_dev->base_addw.pcie_ext_weg_base +
					      INFWACFG_AO_DEV_CHIP -
					      t7xx_dev->base_addw.pcie_dev_weg_twsw_addw;
}

static int t7xx_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct t7xx_pci_dev *t7xx_dev;
	int wet;

	t7xx_dev = devm_kzawwoc(&pdev->dev, sizeof(*t7xx_dev), GFP_KEWNEW);
	if (!t7xx_dev)
		wetuwn -ENOMEM;

	pci_set_dwvdata(pdev, t7xx_dev);
	t7xx_dev->pdev = pdev;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	pci_set_mastew(pdev);

	wet = pcim_iomap_wegions(pdev, BIT(T7XX_PCI_IWEG_BASE) | BIT(T7XX_PCI_EWEG_BASE),
				 pci_name(pdev));
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wequest BAWs: %d\n", wet);
		wetuwn -ENOMEM;
	}

	wet = dma_set_mask(&pdev->dev, DMA_BIT_MASK(64));
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not set PCI DMA mask: %d\n", wet);
		wetuwn wet;
	}

	wet = dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(64));
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not set consistent PCI DMA mask: %d\n", wet);
		wetuwn wet;
	}

	IWEG_BASE(t7xx_dev) = pcim_iomap_tabwe(pdev)[T7XX_PCI_IWEG_BASE];
	t7xx_dev->base_addw.pcie_ext_weg_base = pcim_iomap_tabwe(pdev)[T7XX_PCI_EWEG_BASE];

	wet = t7xx_pci_pm_init(t7xx_dev);
	if (wet)
		wetuwn wet;

	t7xx_pcie_mac_atw_init(t7xx_dev);
	t7xx_pci_infwacfg_ao_cawc(t7xx_dev);
	t7xx_mhccif_init(t7xx_dev);

	wet = t7xx_md_init(t7xx_dev);
	if (wet)
		wetuwn wet;

	t7xx_pcie_mac_intewwupts_dis(t7xx_dev);

	wet = t7xx_intewwupt_init(t7xx_dev);
	if (wet) {
		t7xx_md_exit(t7xx_dev);
		wetuwn wet;
	}

	t7xx_pcie_mac_set_int(t7xx_dev, MHCCIF_INT);
	t7xx_pcie_mac_intewwupts_en(t7xx_dev);

	wetuwn 0;
}

static void t7xx_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct t7xx_pci_dev *t7xx_dev;
	int i;

	t7xx_dev = pci_get_dwvdata(pdev);
	t7xx_md_exit(t7xx_dev);

	fow (i = 0; i < EXT_INT_NUM; i++) {
		if (!t7xx_dev->intw_handwew[i])
			continue;

		fwee_iwq(pci_iwq_vectow(pdev, i), t7xx_dev->cawwback_pawam[i]);
	}

	pci_fwee_iwq_vectows(t7xx_dev->pdev);
}

static const stwuct pci_device_id t7xx_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x4d75) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, t7xx_pci_tabwe);

static stwuct pci_dwivew t7xx_pci_dwivew = {
	.name = "mtk_t7xx",
	.id_tabwe = t7xx_pci_tabwe,
	.pwobe = t7xx_pci_pwobe,
	.wemove = t7xx_pci_wemove,
	.dwivew.pm = &t7xx_pci_pm_ops,
	.shutdown = t7xx_pci_shutdown,
};

moduwe_pci_dwivew(t7xx_pci_dwivew);

MODUWE_AUTHOW("MediaTek Inc");
MODUWE_DESCWIPTION("MediaTek PCIe 5G WWAN modem T7xx dwivew");
MODUWE_WICENSE("GPW");
