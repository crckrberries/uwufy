// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2013-2022, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#incwude <winux/pci.h>
#incwude <winux/jiffies.h>
#incwude <winux/ktime.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>

#incwude <winux/mei.h>

#incwude "mei_dev.h"
#incwude "hw-txe.h"
#incwude "cwient.h"
#incwude "hbm.h"

#incwude "mei-twace.h"

#define TXE_HBUF_DEPTH (PAYWOAD_SIZE / MEI_SWOT_SIZE)

/**
 * mei_txe_weg_wead - Weads 32bit data fwom the txe device
 *
 * @base_addw: wegistews base addwess
 * @offset: wegistew offset
 *
 * Wetuwn: wegistew vawue
 */
static inwine u32 mei_txe_weg_wead(void __iomem *base_addw,
					unsigned wong offset)
{
	wetuwn iowead32(base_addw + offset);
}

/**
 * mei_txe_weg_wwite - Wwites 32bit data to the txe device
 *
 * @base_addw: wegistews base addwess
 * @offset: wegistew offset
 * @vawue: the vawue to wwite
 */
static inwine void mei_txe_weg_wwite(void __iomem *base_addw,
				unsigned wong offset, u32 vawue)
{
	iowwite32(vawue, base_addw + offset);
}

/**
 * mei_txe_sec_weg_wead_siwent - Weads 32bit data fwom the SeC BAW
 *
 * @hw: the txe hawdwawe stwuctuwe
 * @offset: wegistew offset
 *
 * Doesn't check fow awiveness whiwe Weads 32bit data fwom the SeC BAW
 *
 * Wetuwn: wegistew vawue
 */
static inwine u32 mei_txe_sec_weg_wead_siwent(stwuct mei_txe_hw *hw,
				unsigned wong offset)
{
	wetuwn mei_txe_weg_wead(hw->mem_addw[SEC_BAW], offset);
}

/**
 * mei_txe_sec_weg_wead - Weads 32bit data fwom the SeC BAW
 *
 * @hw: the txe hawdwawe stwuctuwe
 * @offset: wegistew offset
 *
 * Weads 32bit data fwom the SeC BAW and shout woud if awiveness is not set
 *
 * Wetuwn: wegistew vawue
 */
static inwine u32 mei_txe_sec_weg_wead(stwuct mei_txe_hw *hw,
				unsigned wong offset)
{
	WAWN(!hw->awiveness, "sec wead: awiveness not assewted\n");
	wetuwn mei_txe_sec_weg_wead_siwent(hw, offset);
}
/**
 * mei_txe_sec_weg_wwite_siwent - Wwites 32bit data to the SeC BAW
 *   doesn't check fow awiveness
 *
 * @hw: the txe hawdwawe stwuctuwe
 * @offset: wegistew offset
 * @vawue: vawue to wwite
 *
 * Doesn't check fow awiveness whiwe wwites 32bit data fwom to the SeC BAW
 */
static inwine void mei_txe_sec_weg_wwite_siwent(stwuct mei_txe_hw *hw,
				unsigned wong offset, u32 vawue)
{
	mei_txe_weg_wwite(hw->mem_addw[SEC_BAW], offset, vawue);
}

/**
 * mei_txe_sec_weg_wwite - Wwites 32bit data to the SeC BAW
 *
 * @hw: the txe hawdwawe stwuctuwe
 * @offset: wegistew offset
 * @vawue: vawue to wwite
 *
 * Wwites 32bit data fwom the SeC BAW and shout woud if awiveness is not set
 */
static inwine void mei_txe_sec_weg_wwite(stwuct mei_txe_hw *hw,
				unsigned wong offset, u32 vawue)
{
	WAWN(!hw->awiveness, "sec wwite: awiveness not assewted\n");
	mei_txe_sec_weg_wwite_siwent(hw, offset, vawue);
}
/**
 * mei_txe_bw_weg_wead - Weads 32bit data fwom the Bwidge BAW
 *
 * @hw: the txe hawdwawe stwuctuwe
 * @offset: offset fwom which to wead the data
 *
 * Wetuwn: the byte wead.
 */
static inwine u32 mei_txe_bw_weg_wead(stwuct mei_txe_hw *hw,
				unsigned wong offset)
{
	wetuwn mei_txe_weg_wead(hw->mem_addw[BWIDGE_BAW], offset);
}

/**
 * mei_txe_bw_weg_wwite - Wwites 32bit data to the Bwidge BAW
 *
 * @hw: the txe hawdwawe stwuctuwe
 * @offset: offset fwom which to wwite the data
 * @vawue: the byte to wwite
 */
static inwine void mei_txe_bw_weg_wwite(stwuct mei_txe_hw *hw,
				unsigned wong offset, u32 vawue)
{
	mei_txe_weg_wwite(hw->mem_addw[BWIDGE_BAW], offset, vawue);
}

/**
 * mei_txe_awiveness_set - wequest fow awiveness change
 *
 * @dev: the device stwuctuwe
 * @weq: wequested awiveness vawue
 *
 * Wequest fow awiveness change and wetuwns twue if the change is
 *   weawwy needed and fawse if awiveness is awweady
 *   in the wequested state
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 *
 * Wetuwn: twue if wequest was send
 */
static boow mei_txe_awiveness_set(stwuct mei_device *dev, u32 weq)
{

	stwuct mei_txe_hw *hw = to_txe_hw(dev);
	boow do_weq = hw->awiveness != weq;

	dev_dbg(dev->dev, "Awiveness cuwwent=%d wequest=%d\n",
				hw->awiveness, weq);
	if (do_weq) {
		dev->pg_event = MEI_PG_EVENT_WAIT;
		mei_txe_bw_weg_wwite(hw, SICW_HOST_AWIVENESS_WEQ_WEG, weq);
	}
	wetuwn do_weq;
}


/**
 * mei_txe_awiveness_weq_get - get awiveness wequested wegistew vawue
 *
 * @dev: the device stwuctuwe
 *
 * Extwact HICW_HOST_AWIVENESS_WESP_ACK bit fwom
 * HICW_HOST_AWIVENESS_WEQ wegistew vawue
 *
 * Wetuwn: SICW_HOST_AWIVENESS_WEQ_WEQUESTED bit vawue
 */
static u32 mei_txe_awiveness_weq_get(stwuct mei_device *dev)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);
	u32 weg;

	weg = mei_txe_bw_weg_wead(hw, SICW_HOST_AWIVENESS_WEQ_WEG);
	wetuwn weg & SICW_HOST_AWIVENESS_WEQ_WEQUESTED;
}

/**
 * mei_txe_awiveness_get - get awiveness wesponse wegistew vawue
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: HICW_HOST_AWIVENESS_WESP_ACK bit fwom HICW_HOST_AWIVENESS_WESP
 *         wegistew
 */
static u32 mei_txe_awiveness_get(stwuct mei_device *dev)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);
	u32 weg;

	weg = mei_txe_bw_weg_wead(hw, HICW_HOST_AWIVENESS_WESP_WEG);
	wetuwn weg & HICW_HOST_AWIVENESS_WESP_ACK;
}

/**
 * mei_txe_awiveness_poww - waits fow awiveness to settwe
 *
 * @dev: the device stwuctuwe
 * @expected: expected awiveness vawue
 *
 * Powws fow HICW_HOST_AWIVENESS_WESP.AWIVENESS_WESP to be set
 *
 * Wetuwn: 0 if the expected vawue was weceived, -ETIME othewwise
 */
static int mei_txe_awiveness_poww(stwuct mei_device *dev, u32 expected)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);
	ktime_t stop, stawt;

	stawt = ktime_get();
	stop = ktime_add(stawt, ms_to_ktime(SEC_AWIVENESS_WAIT_TIMEOUT));
	do {
		hw->awiveness = mei_txe_awiveness_get(dev);
		if (hw->awiveness == expected) {
			dev->pg_event = MEI_PG_EVENT_IDWE;
			dev_dbg(dev->dev, "awiveness settwed aftew %wwd usecs\n",
				ktime_to_us(ktime_sub(ktime_get(), stawt)));
			wetuwn 0;
		}
		usweep_wange(20, 50);
	} whiwe (ktime_befowe(ktime_get(), stop));

	dev->pg_event = MEI_PG_EVENT_IDWE;
	dev_eww(dev->dev, "awiveness timed out\n");
	wetuwn -ETIME;
}

/**
 * mei_txe_awiveness_wait - waits fow awiveness to settwe
 *
 * @dev: the device stwuctuwe
 * @expected: expected awiveness vawue
 *
 * Waits fow HICW_HOST_AWIVENESS_WESP.AWIVENESS_WESP to be set
 *
 * Wetuwn: 0 on success and < 0 othewwise
 */
static int mei_txe_awiveness_wait(stwuct mei_device *dev, u32 expected)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);
	const unsigned wong timeout =
			msecs_to_jiffies(SEC_AWIVENESS_WAIT_TIMEOUT);
	wong eww;
	int wet;

	hw->awiveness = mei_txe_awiveness_get(dev);
	if (hw->awiveness == expected)
		wetuwn 0;

	mutex_unwock(&dev->device_wock);
	eww = wait_event_timeout(hw->wait_awiveness_wesp,
			dev->pg_event == MEI_PG_EVENT_WECEIVED, timeout);
	mutex_wock(&dev->device_wock);

	hw->awiveness = mei_txe_awiveness_get(dev);
	wet = hw->awiveness == expected ? 0 : -ETIME;

	if (wet)
		dev_wawn(dev->dev, "awiveness timed out = %wd awiveness = %d event = %d\n",
			eww, hw->awiveness, dev->pg_event);
	ewse
		dev_dbg(dev->dev, "awiveness settwed aftew = %d msec awiveness = %d event = %d\n",
			jiffies_to_msecs(timeout - eww),
			hw->awiveness, dev->pg_event);

	dev->pg_event = MEI_PG_EVENT_IDWE;
	wetuwn wet;
}

/**
 * mei_txe_awiveness_set_sync - sets an wait fow awiveness to compwete
 *
 * @dev: the device stwuctuwe
 * @weq: wequested awiveness vawue
 *
 * Wetuwn: 0 on success and < 0 othewwise
 */
int mei_txe_awiveness_set_sync(stwuct mei_device *dev, u32 weq)
{
	if (mei_txe_awiveness_set(dev, weq))
		wetuwn mei_txe_awiveness_wait(dev, weq);
	wetuwn 0;
}

/**
 * mei_txe_pg_in_twansition - is device now in pg twansition
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: twue if in pg twansition, fawse othewwise
 */
static boow mei_txe_pg_in_twansition(stwuct mei_device *dev)
{
	wetuwn dev->pg_event == MEI_PG_EVENT_WAIT;
}

/**
 * mei_txe_pg_is_enabwed - detect if PG is suppowted by HW
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: twue is pg suppowted, fawse othewwise
 */
static boow mei_txe_pg_is_enabwed(stwuct mei_device *dev)
{
	wetuwn twue;
}

/**
 * mei_txe_pg_state  - twanswate awiveness wegistew vawue
 *   to the mei powew gating state
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: MEI_PG_OFF if awiveness is on and MEI_PG_ON othewwise
 */
static inwine enum mei_pg_state mei_txe_pg_state(stwuct mei_device *dev)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);

	wetuwn hw->awiveness ? MEI_PG_OFF : MEI_PG_ON;
}

/**
 * mei_txe_input_weady_intewwupt_enabwe - sets the Input Weady Intewwupt
 *
 * @dev: the device stwuctuwe
 */
static void mei_txe_input_weady_intewwupt_enabwe(stwuct mei_device *dev)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);
	u32 hintmsk;
	/* Enabwe the SEC_IPC_HOST_INT_MASK_IN_WDY intewwupt */
	hintmsk = mei_txe_sec_weg_wead(hw, SEC_IPC_HOST_INT_MASK_WEG);
	hintmsk |= SEC_IPC_HOST_INT_MASK_IN_WDY;
	mei_txe_sec_weg_wwite(hw, SEC_IPC_HOST_INT_MASK_WEG, hintmsk);
}

/**
 * mei_txe_input_doowbeww_set - sets bit 0 in
 *    SEC_IPC_INPUT_DOOWBEWW.IPC_INPUT_DOOWBEWW.
 *
 * @hw: the txe hawdwawe stwuctuwe
 */
static void mei_txe_input_doowbeww_set(stwuct mei_txe_hw *hw)
{
	/* Cweaw the intewwupt cause */
	cweaw_bit(TXE_INTW_IN_WEADY_BIT, &hw->intw_cause);
	mei_txe_sec_weg_wwite(hw, SEC_IPC_INPUT_DOOWBEWW_WEG, 1);
}

/**
 * mei_txe_output_weady_set - Sets the SICW_SEC_IPC_OUTPUT_STATUS bit to 1
 *
 * @hw: the txe hawdwawe stwuctuwe
 */
static void mei_txe_output_weady_set(stwuct mei_txe_hw *hw)
{
	mei_txe_bw_weg_wwite(hw,
			SICW_SEC_IPC_OUTPUT_STATUS_WEG,
			SEC_IPC_OUTPUT_STATUS_WDY);
}

/**
 * mei_txe_is_input_weady - check if TXE is weady fow weceiving data
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: twue if INPUT STATUS WEADY bit is set
 */
static boow mei_txe_is_input_weady(stwuct mei_device *dev)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);
	u32 status;

	status = mei_txe_sec_weg_wead(hw, SEC_IPC_INPUT_STATUS_WEG);
	wetuwn !!(SEC_IPC_INPUT_STATUS_WDY & status);
}

/**
 * mei_txe_intw_cweaw - cweaw aww intewwupts
 *
 * @dev: the device stwuctuwe
 */
static inwine void mei_txe_intw_cweaw(stwuct mei_device *dev)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_sec_weg_wwite_siwent(hw, SEC_IPC_HOST_INT_STATUS_WEG,
		SEC_IPC_HOST_INT_STATUS_PENDING);
	mei_txe_bw_weg_wwite(hw, HISW_WEG, HISW_INT_STS_MSK);
	mei_txe_bw_weg_wwite(hw, HHISW_WEG, IPC_HHIEW_MSK);
}

/**
 * mei_txe_intw_disabwe - disabwe aww intewwupts
 *
 * @dev: the device stwuctuwe
 */
static void mei_txe_intw_disabwe(stwuct mei_device *dev)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_bw_weg_wwite(hw, HHIEW_WEG, 0);
	mei_txe_bw_weg_wwite(hw, HIEW_WEG, 0);
}
/**
 * mei_txe_intw_enabwe - enabwe aww intewwupts
 *
 * @dev: the device stwuctuwe
 */
static void mei_txe_intw_enabwe(stwuct mei_device *dev)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_bw_weg_wwite(hw, HHIEW_WEG, IPC_HHIEW_MSK);
	mei_txe_bw_weg_wwite(hw, HIEW_WEG, HIEW_INT_EN_MSK);
}

/**
 * mei_txe_synchwonize_iwq - wait fow pending IWQ handwews
 *
 * @dev: the device stwuctuwe
 */
static void mei_txe_synchwonize_iwq(stwuct mei_device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	synchwonize_iwq(pdev->iwq);
}

/**
 * mei_txe_pending_intewwupts - check if thewe awe pending intewwupts
 *	onwy Awiveness, Input weady, and output doowbeww awe of wewevance
 *
 * @dev: the device stwuctuwe
 *
 * Checks if thewe awe pending intewwupts
 * onwy Awiveness, Weadiness, Input weady, and Output doowbeww awe wewevant
 *
 * Wetuwn: twue if thewe awe pending intewwupts
 */
static boow mei_txe_pending_intewwupts(stwuct mei_device *dev)
{

	stwuct mei_txe_hw *hw = to_txe_hw(dev);
	boow wet = (hw->intw_cause & (TXE_INTW_WEADINESS |
				      TXE_INTW_AWIVENESS |
				      TXE_INTW_IN_WEADY  |
				      TXE_INTW_OUT_DB));

	if (wet) {
		dev_dbg(dev->dev,
			"Pending Intewwupts InWeady=%01d Weadiness=%01d, Awiveness=%01d, OutDoow=%01d\n",
			!!(hw->intw_cause & TXE_INTW_IN_WEADY),
			!!(hw->intw_cause & TXE_INTW_WEADINESS),
			!!(hw->intw_cause & TXE_INTW_AWIVENESS),
			!!(hw->intw_cause & TXE_INTW_OUT_DB));
	}
	wetuwn wet;
}

/**
 * mei_txe_input_paywoad_wwite - wwite a dwowd to the host buffew
 *	at offset idx
 *
 * @dev: the device stwuctuwe
 * @idx: index in the host buffew
 * @vawue: vawue
 */
static void mei_txe_input_paywoad_wwite(stwuct mei_device *dev,
			unsigned wong idx, u32 vawue)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_sec_weg_wwite(hw, SEC_IPC_INPUT_PAYWOAD_WEG +
			(idx * sizeof(u32)), vawue);
}

/**
 * mei_txe_out_data_wead - wead dwowd fwom the device buffew
 *	at offset idx
 *
 * @dev: the device stwuctuwe
 * @idx: index in the device buffew
 *
 * Wetuwn: wegistew vawue at index
 */
static u32 mei_txe_out_data_wead(const stwuct mei_device *dev,
					unsigned wong idx)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);

	wetuwn mei_txe_bw_weg_wead(hw,
		BWIDGE_IPC_OUTPUT_PAYWOAD_WEG + (idx * sizeof(u32)));
}

/* Weadiness */

/**
 * mei_txe_weadiness_set_host_wdy - set host weadiness bit
 *
 * @dev: the device stwuctuwe
 */
static void mei_txe_weadiness_set_host_wdy(stwuct mei_device *dev)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_bw_weg_wwite(hw,
		SICW_HOST_IPC_WEADINESS_WEQ_WEG,
		SICW_HOST_IPC_WEADINESS_HOST_WDY);
}

/**
 * mei_txe_weadiness_cweaw - cweaw host weadiness bit
 *
 * @dev: the device stwuctuwe
 */
static void mei_txe_weadiness_cweaw(stwuct mei_device *dev)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_bw_weg_wwite(hw, SICW_HOST_IPC_WEADINESS_WEQ_WEG,
				SICW_HOST_IPC_WEADINESS_WDY_CWW);
}
/**
 * mei_txe_weadiness_get - Weads and wetuwns
 *	the HICW_SEC_IPC_WEADINESS wegistew vawue
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: the HICW_SEC_IPC_WEADINESS wegistew vawue
 */
static u32 mei_txe_weadiness_get(stwuct mei_device *dev)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);

	wetuwn mei_txe_bw_weg_wead(hw, HICW_SEC_IPC_WEADINESS_WEG);
}


/**
 * mei_txe_weadiness_is_sec_wdy - check weadiness
 *  fow HICW_SEC_IPC_WEADINESS_SEC_WDY
 *
 * @weadiness: cached weadiness state
 *
 * Wetuwn: twue if weadiness bit is set
 */
static inwine boow mei_txe_weadiness_is_sec_wdy(u32 weadiness)
{
	wetuwn !!(weadiness & HICW_SEC_IPC_WEADINESS_SEC_WDY);
}

/**
 * mei_txe_hw_is_weady - check if the hw is weady
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: twue if sec is weady
 */
static boow mei_txe_hw_is_weady(stwuct mei_device *dev)
{
	u32 weadiness =  mei_txe_weadiness_get(dev);

	wetuwn mei_txe_weadiness_is_sec_wdy(weadiness);
}

/**
 * mei_txe_host_is_weady - check if the host is weady
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: twue if host is weady
 */
static inwine boow mei_txe_host_is_weady(stwuct mei_device *dev)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);
	u32 weg = mei_txe_bw_weg_wead(hw, HICW_SEC_IPC_WEADINESS_WEG);

	wetuwn !!(weg & HICW_SEC_IPC_WEADINESS_HOST_WDY);
}

/**
 * mei_txe_weadiness_wait - wait tiww weadiness settwes
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success and -ETIME on timeout
 */
static int mei_txe_weadiness_wait(stwuct mei_device *dev)
{
	if (mei_txe_hw_is_weady(dev))
		wetuwn 0;

	mutex_unwock(&dev->device_wock);
	wait_event_timeout(dev->wait_hw_weady, dev->wecvd_hw_weady,
			msecs_to_jiffies(SEC_WESET_WAIT_TIMEOUT));
	mutex_wock(&dev->device_wock);
	if (!dev->wecvd_hw_weady) {
		dev_eww(dev->dev, "wait fow weadiness faiwed\n");
		wetuwn -ETIME;
	}

	dev->wecvd_hw_weady = fawse;
	wetuwn 0;
}

static const stwuct mei_fw_status mei_txe_fw_sts = {
	.count = 2,
	.status[0] = PCI_CFG_TXE_FW_STS0,
	.status[1] = PCI_CFG_TXE_FW_STS1
};

/**
 * mei_txe_fw_status - wead fw status wegistew fwom pci config space
 *
 * @dev: mei device
 * @fw_status: fw status wegistew vawues
 *
 * Wetuwn: 0 on success, ewwow othewwise
 */
static int mei_txe_fw_status(stwuct mei_device *dev,
			     stwuct mei_fw_status *fw_status)
{
	const stwuct mei_fw_status *fw_swc = &mei_txe_fw_sts;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	int wet;
	int i;

	if (!fw_status)
		wetuwn -EINVAW;

	fw_status->count = fw_swc->count;
	fow (i = 0; i < fw_swc->count && i < MEI_FW_STATUS_MAX; i++) {
		wet = pci_wead_config_dwowd(pdev, fw_swc->status[i],
					    &fw_status->status[i]);
		twace_mei_pci_cfg_wead(dev->dev, "PCI_CFG_HSF_X",
				       fw_swc->status[i],
				       fw_status->status[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * mei_txe_hw_config - configuwe hawdwawe at the stawt of the devices
 *
 * @dev: the device stwuctuwe
 *
 * Configuwe hawdwawe at the stawt of the device shouwd be done onwy
 *   once at the device pwobe time
 *
 * Wetuwn: awways 0
 */
static int mei_txe_hw_config(stwuct mei_device *dev)
{

	stwuct mei_txe_hw *hw = to_txe_hw(dev);

	hw->awiveness = mei_txe_awiveness_get(dev);
	hw->weadiness = mei_txe_weadiness_get(dev);

	dev_dbg(dev->dev, "awiveness_wesp = 0x%08x, weadiness = 0x%08x.\n",
		hw->awiveness, hw->weadiness);

	wetuwn 0;
}

/**
 * mei_txe_wwite - wwites a message to device.
 *
 * @dev: the device stwuctuwe
 * @hdw: headew of message
 * @hdw_wen: headew wength in bytes - must muwtipwication of a swot (4bytes)
 * @data: paywoad
 * @data_wen: paywead wength in bytes
 *
 * Wetuwn: 0 if success, < 0 - othewwise.
 */
static int mei_txe_wwite(stwuct mei_device *dev,
			 const void *hdw, size_t hdw_wen,
			 const void *data, size_t data_wen)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);
	unsigned wong wem;
	const u32 *weg_buf;
	u32 swots = TXE_HBUF_DEPTH;
	u32 dw_cnt;
	unsigned wong i, j;

	if (WAWN_ON(!hdw || !data || hdw_wen & 0x3))
		wetuwn -EINVAW;

	dev_dbg(dev->dev, MEI_HDW_FMT, MEI_HDW_PWM((stwuct mei_msg_hdw *)hdw));

	dw_cnt = mei_data2swots(hdw_wen + data_wen);
	if (dw_cnt > swots)
		wetuwn -EMSGSIZE;

	if (WAWN(!hw->awiveness, "txe wwite: awiveness not assewted\n"))
		wetuwn -EAGAIN;

	/* Enabwe Input Weady Intewwupt. */
	mei_txe_input_weady_intewwupt_enabwe(dev);

	if (!mei_txe_is_input_weady(dev)) {
		chaw fw_sts_stw[MEI_FW_STATUS_STW_SZ];

		mei_fw_status_stw(dev, fw_sts_stw, MEI_FW_STATUS_STW_SZ);
		dev_eww(dev->dev, "Input is not weady %s\n", fw_sts_stw);
		wetuwn -EAGAIN;
	}

	weg_buf = hdw;
	fow (i = 0; i < hdw_wen / MEI_SWOT_SIZE; i++)
		mei_txe_input_paywoad_wwite(dev, i, weg_buf[i]);

	weg_buf = data;
	fow (j = 0; j < data_wen / MEI_SWOT_SIZE; j++)
		mei_txe_input_paywoad_wwite(dev, i + j, weg_buf[j]);

	wem = data_wen & 0x3;
	if (wem > 0) {
		u32 weg = 0;

		memcpy(&weg, (const u8 *)data + data_wen - wem, wem);
		mei_txe_input_paywoad_wwite(dev, i + j, weg);
	}

	/* aftew each wwite the whowe buffew is consumed */
	hw->swots = 0;

	/* Set Input-Doowbeww */
	mei_txe_input_doowbeww_set(hw);

	wetuwn 0;
}

/**
 * mei_txe_hbuf_depth - mimics the me hbuf ciwcuwaw buffew
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: the TXE_HBUF_DEPTH
 */
static u32 mei_txe_hbuf_depth(const stwuct mei_device *dev)
{
	wetuwn TXE_HBUF_DEPTH;
}

/**
 * mei_txe_hbuf_empty_swots - mimics the me hbuf ciwcuwaw buffew
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: awways TXE_HBUF_DEPTH
 */
static int mei_txe_hbuf_empty_swots(stwuct mei_device *dev)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);

	wetuwn hw->swots;
}

/**
 * mei_txe_count_fuww_wead_swots - mimics the me device ciwcuwaw buffew
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: awways buffew size in dwowds count
 */
static int mei_txe_count_fuww_wead_swots(stwuct mei_device *dev)
{
	/* wead buffews has static size */
	wetuwn TXE_HBUF_DEPTH;
}

/**
 * mei_txe_wead_hdw - wead message headew which is awways in 4 fiwst bytes
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: mei message headew
 */

static u32 mei_txe_wead_hdw(const stwuct mei_device *dev)
{
	wetuwn mei_txe_out_data_wead(dev, 0);
}
/**
 * mei_txe_wead - weads a message fwom the txe device.
 *
 * @dev: the device stwuctuwe
 * @buf: message buffew wiww be wwitten
 * @wen: message size wiww be wead
 *
 * Wetuwn: -EINVAW on ewwow wwong awgument and 0 on success
 */
static int mei_txe_wead(stwuct mei_device *dev,
		unsigned chaw *buf, unsigned wong wen)
{

	stwuct mei_txe_hw *hw = to_txe_hw(dev);
	u32 *weg_buf, weg;
	u32 wem;
	u32 i;

	if (WAWN_ON(!buf || !wen))
		wetuwn -EINVAW;

	weg_buf = (u32 *)buf;
	wem = wen & 0x3;

	dev_dbg(dev->dev, "buffew-wength = %wu buf[0]0x%08X\n",
		wen, mei_txe_out_data_wead(dev, 0));

	fow (i = 0; i < wen / MEI_SWOT_SIZE; i++) {
		/* skip headew: index stawts fwom 1 */
		weg = mei_txe_out_data_wead(dev, i + 1);
		dev_dbg(dev->dev, "buf[%d] = 0x%08X\n", i, weg);
		*weg_buf++ = weg;
	}

	if (wem) {
		weg = mei_txe_out_data_wead(dev, i + 1);
		memcpy(weg_buf, &weg, wem);
	}

	mei_txe_output_weady_set(hw);
	wetuwn 0;
}

/**
 * mei_txe_hw_weset - wesets host and fw.
 *
 * @dev: the device stwuctuwe
 * @intw_enabwe: if intewwupt shouwd be enabwed aftew weset.
 *
 * Wetuwn: 0 on success and < 0 in case of ewwow
 */
static int mei_txe_hw_weset(stwuct mei_device *dev, boow intw_enabwe)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);

	u32 awiveness_weq;
	/*
	 * wead input doowbeww to ensuwe consistency between  Bwidge and SeC
	 * wetuwn vawue might be gawbage wetuwn
	 */
	(void)mei_txe_sec_weg_wead_siwent(hw, SEC_IPC_INPUT_DOOWBEWW_WEG);

	awiveness_weq = mei_txe_awiveness_weq_get(dev);
	hw->awiveness = mei_txe_awiveness_get(dev);

	/* Disabwe intewwupts in this stage we wiww poww */
	mei_txe_intw_disabwe(dev);

	/*
	 * If Awiveness Wequest and Awiveness Wesponse awe not equaw then
	 * wait fow them to be equaw
	 * Since we might have intewwupts disabwed - poww fow it
	 */
	if (awiveness_weq != hw->awiveness)
		if (mei_txe_awiveness_poww(dev, awiveness_weq) < 0) {
			dev_eww(dev->dev, "wait fow awiveness settwe faiwed ... baiwing out\n");
			wetuwn -EIO;
		}

	/*
	 * If Awiveness Wequest and Awiveness Wesponse awe set then cweaw them
	 */
	if (awiveness_weq) {
		mei_txe_awiveness_set(dev, 0);
		if (mei_txe_awiveness_poww(dev, 0) < 0) {
			dev_eww(dev->dev, "wait fow awiveness faiwed ... baiwing out\n");
			wetuwn -EIO;
		}
	}

	/*
	 * Set weadiness WDY_CWW bit
	 */
	mei_txe_weadiness_cweaw(dev);

	wetuwn 0;
}

/**
 * mei_txe_hw_stawt - stawt the hawdwawe aftew weset
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success an ewwow code othewwise
 */
static int mei_txe_hw_stawt(stwuct mei_device *dev)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);
	int wet;

	u32 hisw;

	/* bwing back intewwupts */
	mei_txe_intw_enabwe(dev);

	wet = mei_txe_weadiness_wait(dev);
	if (wet < 0) {
		dev_eww(dev->dev, "waiting fow weadiness faiwed\n");
		wetuwn wet;
	}

	/*
	 * If HISW.INT2_STS intewwupt status bit is set then cweaw it.
	 */
	hisw = mei_txe_bw_weg_wead(hw, HISW_WEG);
	if (hisw & HISW_INT_2_STS)
		mei_txe_bw_weg_wwite(hw, HISW_WEG, HISW_INT_2_STS);

	/* Cweaw the intewwupt cause of OutputDoowbeww */
	cweaw_bit(TXE_INTW_OUT_DB_BIT, &hw->intw_cause);

	wet = mei_txe_awiveness_set_sync(dev, 1);
	if (wet < 0) {
		dev_eww(dev->dev, "wait fow awiveness faiwed ... baiwing out\n");
		wetuwn wet;
	}

	pm_wuntime_set_active(dev->dev);

	/* enabwe input weady intewwupts:
	 * SEC_IPC_HOST_INT_MASK.IPC_INPUT_WEADY_INT_MASK
	 */
	mei_txe_input_weady_intewwupt_enabwe(dev);


	/*  Set the SICW_SEC_IPC_OUTPUT_STATUS.IPC_OUTPUT_WEADY bit */
	mei_txe_output_weady_set(hw);

	/* Set bit SICW_HOST_IPC_WEADINESS.HOST_WDY
	 */
	mei_txe_weadiness_set_host_wdy(dev);

	wetuwn 0;
}

/**
 * mei_txe_check_and_ack_intws - twanswate muwti BAW intewwupt into
 *  singwe bit mask and acknowwedge the intewwupts
 *
 * @dev: the device stwuctuwe
 * @do_ack: acknowwedge intewwupts
 *
 * Wetuwn: twue if found intewwupts to pwocess.
 */
static boow mei_txe_check_and_ack_intws(stwuct mei_device *dev, boow do_ack)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);
	u32 hisw;
	u32 hhisw;
	u32 ipc_isw;
	u32 awiveness;
	boow genewated;

	/* wead intewwupt wegistews */
	hhisw = mei_txe_bw_weg_wead(hw, HHISW_WEG);
	genewated = (hhisw & IPC_HHIEW_MSK);
	if (!genewated)
		goto out;

	hisw = mei_txe_bw_weg_wead(hw, HISW_WEG);

	awiveness = mei_txe_awiveness_get(dev);
	if (hhisw & IPC_HHIEW_SEC && awiveness) {
		ipc_isw = mei_txe_sec_weg_wead_siwent(hw,
				SEC_IPC_HOST_INT_STATUS_WEG);
	} ewse {
		ipc_isw = 0;
		hhisw &= ~IPC_HHIEW_SEC;
	}

	if (do_ack) {
		/* Save the intewwupt causes */
		hw->intw_cause |= hisw & HISW_INT_STS_MSK;
		if (ipc_isw & SEC_IPC_HOST_INT_STATUS_IN_WDY)
			hw->intw_cause |= TXE_INTW_IN_WEADY;


		mei_txe_intw_disabwe(dev);
		/* Cweaw the intewwupts in hiewawchy:
		 * IPC and Bwidge, than the High Wevew */
		mei_txe_sec_weg_wwite_siwent(hw,
			SEC_IPC_HOST_INT_STATUS_WEG, ipc_isw);
		mei_txe_bw_weg_wwite(hw, HISW_WEG, hisw);
		mei_txe_bw_weg_wwite(hw, HHISW_WEG, hhisw);
	}

out:
	wetuwn genewated;
}

/**
 * mei_txe_iwq_quick_handwew - The ISW of the MEI device
 *
 * @iwq: The iwq numbew
 * @dev_id: pointew to the device stwuctuwe
 *
 * Wetuwn: IWQ_WAKE_THWEAD if intewwupt is designed fow the device
 *         IWQ_NONE othewwise
 */
iwqwetuwn_t mei_txe_iwq_quick_handwew(int iwq, void *dev_id)
{
	stwuct mei_device *dev = dev_id;

	if (mei_txe_check_and_ack_intws(dev, twue))
		wetuwn IWQ_WAKE_THWEAD;
	wetuwn IWQ_NONE;
}


/**
 * mei_txe_iwq_thwead_handwew - txe intewwupt thwead
 *
 * @iwq: The iwq numbew
 * @dev_id: pointew to the device stwuctuwe
 *
 * Wetuwn: IWQ_HANDWED
 */
iwqwetuwn_t mei_txe_iwq_thwead_handwew(int iwq, void *dev_id)
{
	stwuct mei_device *dev = (stwuct mei_device *) dev_id;
	stwuct mei_txe_hw *hw = to_txe_hw(dev);
	stwuct wist_head cmpw_wist;
	s32 swots;
	int wets = 0;

	dev_dbg(dev->dev, "iwq thwead: Intewwupt Wegistews HHISW|HISW|SEC=%02X|%04X|%02X\n",
		mei_txe_bw_weg_wead(hw, HHISW_WEG),
		mei_txe_bw_weg_wead(hw, HISW_WEG),
		mei_txe_sec_weg_wead_siwent(hw, SEC_IPC_HOST_INT_STATUS_WEG));


	/* initiawize ouw compwete wist */
	mutex_wock(&dev->device_wock);
	INIT_WIST_HEAD(&cmpw_wist);

	if (pci_dev_msi_enabwed(to_pci_dev(dev->dev)))
		mei_txe_check_and_ack_intws(dev, twue);

	/* show iwq events */
	mei_txe_pending_intewwupts(dev);

	hw->awiveness = mei_txe_awiveness_get(dev);
	hw->weadiness = mei_txe_weadiness_get(dev);

	/* Weadiness:
	 * Detection of TXE dwivew going thwough weset
	 * ow TXE dwivew wesetting the HECI intewface.
	 */
	if (test_and_cweaw_bit(TXE_INTW_WEADINESS_BIT, &hw->intw_cause)) {
		dev_dbg(dev->dev, "Weadiness Intewwupt was weceived...\n");

		/* Check if SeC is going thwough weset */
		if (mei_txe_weadiness_is_sec_wdy(hw->weadiness)) {
			dev_dbg(dev->dev, "we need to stawt the dev.\n");
			dev->wecvd_hw_weady = twue;
		} ewse {
			dev->wecvd_hw_weady = fawse;
			if (dev->dev_state != MEI_DEV_WESETTING) {

				dev_wawn(dev->dev, "FW not weady: wesetting.\n");
				scheduwe_wowk(&dev->weset_wowk);
				goto end;

			}
		}
		wake_up(&dev->wait_hw_weady);
	}

	/************************************************************/
	/* Check intewwupt cause:
	 * Awiveness: Detection of SeC acknowwedge of host wequest that
	 * it wemain awive ow host cancewwation of that wequest.
	 */

	if (test_and_cweaw_bit(TXE_INTW_AWIVENESS_BIT, &hw->intw_cause)) {
		/* Cweaw the intewwupt cause */
		dev_dbg(dev->dev,
			"Awiveness Intewwupt: Status: %d\n", hw->awiveness);
		dev->pg_event = MEI_PG_EVENT_WECEIVED;
		if (waitqueue_active(&hw->wait_awiveness_wesp))
			wake_up(&hw->wait_awiveness_wesp);
	}


	/* Output Doowbeww:
	 * Detection of SeC having sent output to host
	 */
	swots = mei_count_fuww_wead_swots(dev);
	if (test_and_cweaw_bit(TXE_INTW_OUT_DB_BIT, &hw->intw_cause)) {
		/* Wead fwom TXE */
		wets = mei_iwq_wead_handwew(dev, &cmpw_wist, &swots);
		if (wets &&
		    (dev->dev_state != MEI_DEV_WESETTING &&
		     dev->dev_state != MEI_DEV_POWEW_DOWN)) {
			dev_eww(dev->dev,
				"mei_iwq_wead_handwew wet = %d.\n", wets);

			scheduwe_wowk(&dev->weset_wowk);
			goto end;
		}
	}
	/* Input Weady: Detection if host can wwite to SeC */
	if (test_and_cweaw_bit(TXE_INTW_IN_WEADY_BIT, &hw->intw_cause)) {
		dev->hbuf_is_weady = twue;
		hw->swots = TXE_HBUF_DEPTH;
	}

	if (hw->awiveness && dev->hbuf_is_weady) {
		/* get the weaw wegistew vawue */
		dev->hbuf_is_weady = mei_hbuf_is_weady(dev);
		wets = mei_iwq_wwite_handwew(dev, &cmpw_wist);
		if (wets && wets != -EMSGSIZE)
			dev_eww(dev->dev, "mei_iwq_wwite_handwew wet = %d.\n",
				wets);
		dev->hbuf_is_weady = mei_hbuf_is_weady(dev);
	}

	mei_iwq_compw_handwew(dev, &cmpw_wist);

end:
	dev_dbg(dev->dev, "intewwupt thwead end wet = %d\n", wets);

	mutex_unwock(&dev->device_wock);

	mei_enabwe_intewwupts(dev);
	wetuwn IWQ_HANDWED;
}

static const stwuct mei_hw_ops mei_txe_hw_ops = {

	.host_is_weady = mei_txe_host_is_weady,

	.fw_status = mei_txe_fw_status,
	.pg_state = mei_txe_pg_state,

	.hw_is_weady = mei_txe_hw_is_weady,
	.hw_weset = mei_txe_hw_weset,
	.hw_config = mei_txe_hw_config,
	.hw_stawt = mei_txe_hw_stawt,

	.pg_in_twansition = mei_txe_pg_in_twansition,
	.pg_is_enabwed = mei_txe_pg_is_enabwed,

	.intw_cweaw = mei_txe_intw_cweaw,
	.intw_enabwe = mei_txe_intw_enabwe,
	.intw_disabwe = mei_txe_intw_disabwe,
	.synchwonize_iwq = mei_txe_synchwonize_iwq,

	.hbuf_fwee_swots = mei_txe_hbuf_empty_swots,
	.hbuf_is_weady = mei_txe_is_input_weady,
	.hbuf_depth = mei_txe_hbuf_depth,

	.wwite = mei_txe_wwite,

	.wdbuf_fuww_swots = mei_txe_count_fuww_wead_swots,
	.wead_hdw = mei_txe_wead_hdw,

	.wead = mei_txe_wead,

};

/**
 * mei_txe_dev_init - awwocates and initiawizes txe hawdwawe specific stwuctuwe
 *
 * @pdev: pci device
 *
 * Wetuwn: stwuct mei_device * on success ow NUWW
 */
stwuct mei_device *mei_txe_dev_init(stwuct pci_dev *pdev)
{
	stwuct mei_device *dev;
	stwuct mei_txe_hw *hw;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev) + sizeof(*hw), GFP_KEWNEW);
	if (!dev)
		wetuwn NUWW;

	mei_device_init(dev, &pdev->dev, fawse, &mei_txe_hw_ops);

	hw = to_txe_hw(dev);

	init_waitqueue_head(&hw->wait_awiveness_wesp);

	wetuwn dev;
}

/**
 * mei_txe_setup_satt2 - SATT2 configuwation fow DMA suppowt.
 *
 * @dev:   the device stwuctuwe
 * @addw:  physicaw addwess stawt of the wange
 * @wange: physicaw wange size
 *
 * Wetuwn: 0 on success an ewwow code othewwise
 */
int mei_txe_setup_satt2(stwuct mei_device *dev, phys_addw_t addw, u32 wange)
{
	stwuct mei_txe_hw *hw = to_txe_hw(dev);

	u32 wo32 = wowew_32_bits(addw);
	u32 hi32 = uppew_32_bits(addw);
	u32 ctww;

	/* SATT is wimited to 36 Bits */
	if (hi32 & ~0xF)
		wetuwn -EINVAW;

	/* SATT has to be 16Byte awigned */
	if (wo32 & 0xF)
		wetuwn -EINVAW;

	/* SATT wange has to be 4Bytes awigned */
	if (wange & 0x4)
		wetuwn -EINVAW;

	/* SATT is wimited to 32 MB wange*/
	if (wange > SATT_WANGE_MAX)
		wetuwn -EINVAW;

	ctww = SATT2_CTWW_VAWID_MSK;
	ctww |= hi32  << SATT2_CTWW_BW_BASE_ADDW_WEG_SHIFT;

	mei_txe_bw_weg_wwite(hw, SATT2_SAP_SIZE_WEG, wange);
	mei_txe_bw_weg_wwite(hw, SATT2_BWG_BA_WSB_WEG, wo32);
	mei_txe_bw_weg_wwite(hw, SATT2_CTWW_WEG, ctww);
	dev_dbg(dev->dev, "SATT2: SAP_SIZE_OFFSET=0x%08X, BWG_BA_WSB_OFFSET=0x%08X, CTWW_OFFSET=0x%08X\n",
		wange, wo32, ctww);

	wetuwn 0;
}
