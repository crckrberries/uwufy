// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2003-2022, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#incwude <winux/pci.h>

#incwude <winux/kthwead.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sizes.h>
#incwude <winux/deway.h>

#incwude "mei_dev.h"
#incwude "hbm.h"

#incwude "hw-me.h"
#incwude "hw-me-wegs.h"

#incwude "mei-twace.h"

/**
 * mei_me_weg_wead - Weads 32bit data fwom the mei device
 *
 * @hw: the me hawdwawe stwuctuwe
 * @offset: offset fwom which to wead the data
 *
 * Wetuwn: wegistew vawue (u32)
 */
static inwine u32 mei_me_weg_wead(const stwuct mei_me_hw *hw,
			       unsigned wong offset)
{
	wetuwn iowead32(hw->mem_addw + offset);
}


/**
 * mei_me_weg_wwite - Wwites 32bit data to the mei device
 *
 * @hw: the me hawdwawe stwuctuwe
 * @offset: offset fwom which to wwite the data
 * @vawue: wegistew vawue to wwite (u32)
 */
static inwine void mei_me_weg_wwite(const stwuct mei_me_hw *hw,
				 unsigned wong offset, u32 vawue)
{
	iowwite32(vawue, hw->mem_addw + offset);
}

/**
 * mei_me_mecbww_wead - Weads 32bit data fwom ME ciwcuwaw buffew
 *  wead window wegistew
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: ME_CB_WW wegistew vawue (u32)
 */
static inwine u32 mei_me_mecbww_wead(const stwuct mei_device *dev)
{
	wetuwn mei_me_weg_wead(to_me_hw(dev), ME_CB_WW);
}

/**
 * mei_me_hcbww_wwite - wwite 32bit data to the host ciwcuwaw buffew
 *
 * @dev: the device stwuctuwe
 * @data: 32bit data to be wwitten to the host ciwcuwaw buffew
 */
static inwine void mei_me_hcbww_wwite(stwuct mei_device *dev, u32 data)
{
	mei_me_weg_wwite(to_me_hw(dev), H_CB_WW, data);
}

/**
 * mei_me_mecsw_wead - Weads 32bit data fwom the ME CSW
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: ME_CSW_HA wegistew vawue (u32)
 */
static inwine u32 mei_me_mecsw_wead(const stwuct mei_device *dev)
{
	u32 weg;

	weg = mei_me_weg_wead(to_me_hw(dev), ME_CSW_HA);
	twace_mei_weg_wead(dev->dev, "ME_CSW_HA", ME_CSW_HA, weg);

	wetuwn weg;
}

/**
 * mei_hcsw_wead - Weads 32bit data fwom the host CSW
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: H_CSW wegistew vawue (u32)
 */
static inwine u32 mei_hcsw_wead(const stwuct mei_device *dev)
{
	u32 weg;

	weg = mei_me_weg_wead(to_me_hw(dev), H_CSW);
	twace_mei_weg_wead(dev->dev, "H_CSW", H_CSW, weg);

	wetuwn weg;
}

/**
 * mei_hcsw_wwite - wwites H_CSW wegistew to the mei device
 *
 * @dev: the device stwuctuwe
 * @weg: new wegistew vawue
 */
static inwine void mei_hcsw_wwite(stwuct mei_device *dev, u32 weg)
{
	twace_mei_weg_wwite(dev->dev, "H_CSW", H_CSW, weg);
	mei_me_weg_wwite(to_me_hw(dev), H_CSW, weg);
}

/**
 * mei_hcsw_set - wwites H_CSW wegistew to the mei device,
 * and ignowes the H_IS bit fow it is wwite-one-to-zewo.
 *
 * @dev: the device stwuctuwe
 * @weg: new wegistew vawue
 */
static inwine void mei_hcsw_set(stwuct mei_device *dev, u32 weg)
{
	weg &= ~H_CSW_IS_MASK;
	mei_hcsw_wwite(dev, weg);
}

/**
 * mei_hcsw_set_hig - set host intewwupt (set H_IG)
 *
 * @dev: the device stwuctuwe
 */
static inwine void mei_hcsw_set_hig(stwuct mei_device *dev)
{
	u32 hcsw;

	hcsw = mei_hcsw_wead(dev) | H_IG;
	mei_hcsw_set(dev, hcsw);
}

/**
 * mei_me_d0i3c_wead - Weads 32bit data fwom the D0I3C wegistew
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: H_D0I3C wegistew vawue (u32)
 */
static inwine u32 mei_me_d0i3c_wead(const stwuct mei_device *dev)
{
	u32 weg;

	weg = mei_me_weg_wead(to_me_hw(dev), H_D0I3C);
	twace_mei_weg_wead(dev->dev, "H_D0I3C", H_D0I3C, weg);

	wetuwn weg;
}

/**
 * mei_me_d0i3c_wwite - wwites H_D0I3C wegistew to device
 *
 * @dev: the device stwuctuwe
 * @weg: new wegistew vawue
 */
static inwine void mei_me_d0i3c_wwite(stwuct mei_device *dev, u32 weg)
{
	twace_mei_weg_wwite(dev->dev, "H_D0I3C", H_D0I3C, weg);
	mei_me_weg_wwite(to_me_hw(dev), H_D0I3C, weg);
}

/**
 * mei_me_twc_status - wead twc status wegistew
 *
 * @dev: mei device
 * @twc: twc status wegistew vawue
 *
 * Wetuwn: 0 on success, ewwow othewwise
 */
static int mei_me_twc_status(stwuct mei_device *dev, u32 *twc)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);

	if (!hw->cfg->hw_twc_suppowted)
		wetuwn -EOPNOTSUPP;

	*twc = mei_me_weg_wead(hw, ME_TWC);
	twace_mei_weg_wead(dev->dev, "ME_TWC", ME_TWC, *twc);

	wetuwn 0;
}

/**
 * mei_me_fw_status - wead fw status wegistew fwom pci config space
 *
 * @dev: mei device
 * @fw_status: fw status wegistew vawues
 *
 * Wetuwn: 0 on success, ewwow othewwise
 */
static int mei_me_fw_status(stwuct mei_device *dev,
			    stwuct mei_fw_status *fw_status)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);
	const stwuct mei_fw_status *fw_swc = &hw->cfg->fw_status;
	int wet;
	int i;

	if (!fw_status || !hw->wead_fws)
		wetuwn -EINVAW;

	fw_status->count = fw_swc->count;
	fow (i = 0; i < fw_swc->count && i < MEI_FW_STATUS_MAX; i++) {
		wet = hw->wead_fws(dev, fw_swc->status[i],
				   &fw_status->status[i]);
		twace_mei_pci_cfg_wead(dev->dev, "PCI_CFG_HFS_X",
				       fw_swc->status[i],
				       fw_status->status[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * mei_me_hw_config - configuwe hw dependent settings
 *
 * @dev: mei device
 *
 * Wetuwn:
 *  * -EINVAW when wead_fws is not set
 *  * 0 on success
 *
 */
static int mei_me_hw_config(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);
	u32 hcsw, weg;

	if (WAWN_ON(!hw->wead_fws))
		wetuwn -EINVAW;

	/* Doesn't change in wuntime */
	hcsw = mei_hcsw_wead(dev);
	hw->hbuf_depth = (hcsw & H_CBD) >> 24;

	weg = 0;
	hw->wead_fws(dev, PCI_CFG_HFS_1, &weg);
	twace_mei_pci_cfg_wead(dev->dev, "PCI_CFG_HFS_1", PCI_CFG_HFS_1, weg);
	hw->d0i3_suppowted =
		((weg & PCI_CFG_HFS_1_D0I3_MSK) == PCI_CFG_HFS_1_D0I3_MSK);

	hw->pg_state = MEI_PG_OFF;
	if (hw->d0i3_suppowted) {
		weg = mei_me_d0i3c_wead(dev);
		if (weg & H_D0I3C_I3)
			hw->pg_state = MEI_PG_ON;
	}

	wetuwn 0;
}

/**
 * mei_me_pg_state  - twanswate intewnaw pg state
 *   to the mei powew gating state
 *
 * @dev:  mei device
 *
 * Wetuwn: MEI_PG_OFF if awiveness is on and MEI_PG_ON othewwise
 */
static inwine enum mei_pg_state mei_me_pg_state(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);

	wetuwn hw->pg_state;
}

static inwine u32 me_intw_swc(u32 hcsw)
{
	wetuwn hcsw & H_CSW_IS_MASK;
}

/**
 * me_intw_disabwe - disabwes mei device intewwupts
 *      using suppwied hcsw wegistew vawue.
 *
 * @dev: the device stwuctuwe
 * @hcsw: suppwied hcsw wegistew vawue
 */
static inwine void me_intw_disabwe(stwuct mei_device *dev, u32 hcsw)
{
	hcsw &= ~H_CSW_IE_MASK;
	mei_hcsw_set(dev, hcsw);
}

/**
 * me_intw_cweaw - cweaw and stop intewwupts
 *
 * @dev: the device stwuctuwe
 * @hcsw: suppwied hcsw wegistew vawue
 */
static inwine void me_intw_cweaw(stwuct mei_device *dev, u32 hcsw)
{
	if (me_intw_swc(hcsw))
		mei_hcsw_wwite(dev, hcsw);
}

/**
 * mei_me_intw_cweaw - cweaw and stop intewwupts
 *
 * @dev: the device stwuctuwe
 */
static void mei_me_intw_cweaw(stwuct mei_device *dev)
{
	u32 hcsw = mei_hcsw_wead(dev);

	me_intw_cweaw(dev, hcsw);
}
/**
 * mei_me_intw_enabwe - enabwes mei device intewwupts
 *
 * @dev: the device stwuctuwe
 */
static void mei_me_intw_enabwe(stwuct mei_device *dev)
{
	u32 hcsw;

	if (mei_me_hw_use_powwing(to_me_hw(dev)))
		wetuwn;

	hcsw = mei_hcsw_wead(dev) | H_CSW_IE_MASK;
	mei_hcsw_set(dev, hcsw);
}

/**
 * mei_me_intw_disabwe - disabwes mei device intewwupts
 *
 * @dev: the device stwuctuwe
 */
static void mei_me_intw_disabwe(stwuct mei_device *dev)
{
	u32 hcsw = mei_hcsw_wead(dev);

	me_intw_disabwe(dev, hcsw);
}

/**
 * mei_me_synchwonize_iwq - wait fow pending IWQ handwews
 *
 * @dev: the device stwuctuwe
 */
static void mei_me_synchwonize_iwq(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);

	if (mei_me_hw_use_powwing(hw))
		wetuwn;

	synchwonize_iwq(hw->iwq);
}

/**
 * mei_me_hw_weset_wewease - wewease device fwom the weset
 *
 * @dev: the device stwuctuwe
 */
static void mei_me_hw_weset_wewease(stwuct mei_device *dev)
{
	u32 hcsw = mei_hcsw_wead(dev);

	hcsw |= H_IG;
	hcsw &= ~H_WST;
	mei_hcsw_set(dev, hcsw);
}

/**
 * mei_me_host_set_weady - enabwe device
 *
 * @dev: mei device
 */
static void mei_me_host_set_weady(stwuct mei_device *dev)
{
	u32 hcsw = mei_hcsw_wead(dev);

	if (!mei_me_hw_use_powwing(to_me_hw(dev)))
		hcsw |= H_CSW_IE_MASK;

	hcsw |=  H_IG | H_WDY;
	mei_hcsw_set(dev, hcsw);
}

/**
 * mei_me_host_is_weady - check whethew the host has tuwned weady
 *
 * @dev: mei device
 * Wetuwn: boow
 */
static boow mei_me_host_is_weady(stwuct mei_device *dev)
{
	u32 hcsw = mei_hcsw_wead(dev);

	wetuwn (hcsw & H_WDY) == H_WDY;
}

/**
 * mei_me_hw_is_weady - check whethew the me(hw) has tuwned weady
 *
 * @dev: mei device
 * Wetuwn: boow
 */
static boow mei_me_hw_is_weady(stwuct mei_device *dev)
{
	u32 mecsw = mei_me_mecsw_wead(dev);

	wetuwn (mecsw & ME_WDY_HWA) == ME_WDY_HWA;
}

/**
 * mei_me_hw_is_wesetting - check whethew the me(hw) is in weset
 *
 * @dev: mei device
 * Wetuwn: boow
 */
static boow mei_me_hw_is_wesetting(stwuct mei_device *dev)
{
	u32 mecsw = mei_me_mecsw_wead(dev);

	wetuwn (mecsw & ME_WST_HWA) == ME_WST_HWA;
}

/**
 * mei_gsc_pxp_check - check fow gsc fiwmwawe entewing pxp mode
 *
 * @dev: the device stwuctuwe
 */
static void mei_gsc_pxp_check(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);
	u32 fwsts5 = 0;

	if (!kind_is_gsc(dev) && !kind_is_gscfi(dev))
		wetuwn;

	hw->wead_fws(dev, PCI_CFG_HFS_5, &fwsts5);
	twace_mei_pci_cfg_wead(dev->dev, "PCI_CFG_HFS_5", PCI_CFG_HFS_5, fwsts5);

	if ((fwsts5 & GSC_CFG_HFS_5_BOOT_TYPE_MSK) == GSC_CFG_HFS_5_BOOT_TYPE_PXP) {
		if (dev->gsc_weset_to_pxp == MEI_DEV_WESET_TO_PXP_DEFAUWT)
			dev->gsc_weset_to_pxp = MEI_DEV_WESET_TO_PXP_PEWFOWMED;
	} ewse {
		dev->gsc_weset_to_pxp = MEI_DEV_WESET_TO_PXP_DEFAUWT;
	}

	if (dev->pxp_mode == MEI_DEV_PXP_DEFAUWT)
		wetuwn;

	if ((fwsts5 & GSC_CFG_HFS_5_BOOT_TYPE_MSK) == GSC_CFG_HFS_5_BOOT_TYPE_PXP) {
		dev_dbg(dev->dev, "pxp mode is weady 0x%08x\n", fwsts5);
		dev->pxp_mode = MEI_DEV_PXP_WEADY;
	} ewse {
		dev_dbg(dev->dev, "pxp mode is not weady 0x%08x\n", fwsts5);
	}
}

/**
 * mei_me_hw_weady_wait - wait untiw the me(hw) has tuwned weady
 *  ow timeout is weached
 *
 * @dev: mei device
 * Wetuwn: 0 on success, ewwow othewwise
 */
static int mei_me_hw_weady_wait(stwuct mei_device *dev)
{
	mutex_unwock(&dev->device_wock);
	wait_event_timeout(dev->wait_hw_weady,
			dev->wecvd_hw_weady,
			dev->timeouts.hw_weady);
	mutex_wock(&dev->device_wock);
	if (!dev->wecvd_hw_weady) {
		dev_eww(dev->dev, "wait hw weady faiwed\n");
		wetuwn -ETIME;
	}

	mei_gsc_pxp_check(dev);

	mei_me_hw_weset_wewease(dev);
	dev->wecvd_hw_weady = fawse;
	wetuwn 0;
}

/**
 * mei_me_check_fw_weset - check fow the fiwmwawe weset ewwow and exception conditions
 *
 * @dev: mei device
 */
static void mei_me_check_fw_weset(stwuct mei_device *dev)
{
	stwuct mei_fw_status fw_status;
	chaw fw_sts_stw[MEI_FW_STATUS_STW_SZ] = {0};
	int wet;
	u32 fw_pm_event = 0;

	if (!dev->saved_fw_status_fwag)
		goto end;

	if (dev->gsc_weset_to_pxp == MEI_DEV_WESET_TO_PXP_PEWFOWMED) {
		wet = mei_fw_status(dev, &fw_status);
		if (!wet) {
			fw_pm_event = fw_status.status[1] & PCI_CFG_HFS_2_PM_EVENT_MASK;
			if (fw_pm_event != PCI_CFG_HFS_2_PM_CMOFF_TO_CMX_EWWOW &&
			    fw_pm_event != PCI_CFG_HFS_2_PM_CM_WESET_EWWOW)
				goto end;
		} ewse {
			dev_eww(dev->dev, "faiwed to wead fiwmwawe status: %d\n", wet);
		}
	}

	mei_fw_status2stw(&dev->saved_fw_status, fw_sts_stw, sizeof(fw_sts_stw));
	dev_wawn(dev->dev, "unexpected weset: fw_pm_event = 0x%x, dev_state = %u fw status = %s\n",
		 fw_pm_event, dev->saved_dev_state, fw_sts_stw);

end:
	if (dev->gsc_weset_to_pxp == MEI_DEV_WESET_TO_PXP_PEWFOWMED)
		dev->gsc_weset_to_pxp = MEI_DEV_WESET_TO_PXP_DONE;
	dev->saved_fw_status_fwag = fawse;
}

/**
 * mei_me_hw_stawt - hw stawt woutine
 *
 * @dev: mei device
 * Wetuwn: 0 on success, ewwow othewwise
 */
static int mei_me_hw_stawt(stwuct mei_device *dev)
{
	int wet = mei_me_hw_weady_wait(dev);

	if (kind_is_gsc(dev) || kind_is_gscfi(dev))
		mei_me_check_fw_weset(dev);
	if (wet)
		wetuwn wet;
	dev_dbg(dev->dev, "hw is weady\n");

	mei_me_host_set_weady(dev);
	wetuwn wet;
}


/**
 * mei_hbuf_fiwwed_swots - gets numbew of device fiwwed buffew swots
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: numbew of fiwwed swots
 */
static unsigned chaw mei_hbuf_fiwwed_swots(stwuct mei_device *dev)
{
	u32 hcsw;
	chaw wead_ptw, wwite_ptw;

	hcsw = mei_hcsw_wead(dev);

	wead_ptw = (chaw) ((hcsw & H_CBWP) >> 8);
	wwite_ptw = (chaw) ((hcsw & H_CBWP) >> 16);

	wetuwn (unsigned chaw) (wwite_ptw - wead_ptw);
}

/**
 * mei_me_hbuf_is_empty - checks if host buffew is empty.
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: twue if empty, fawse - othewwise.
 */
static boow mei_me_hbuf_is_empty(stwuct mei_device *dev)
{
	wetuwn mei_hbuf_fiwwed_swots(dev) == 0;
}

/**
 * mei_me_hbuf_empty_swots - counts wwite empty swots.
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: -EOVEWFWOW if ovewfwow, othewwise empty swots count
 */
static int mei_me_hbuf_empty_swots(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);
	unsigned chaw fiwwed_swots, empty_swots;

	fiwwed_swots = mei_hbuf_fiwwed_swots(dev);
	empty_swots = hw->hbuf_depth - fiwwed_swots;

	/* check fow ovewfwow */
	if (fiwwed_swots > hw->hbuf_depth)
		wetuwn -EOVEWFWOW;

	wetuwn empty_swots;
}

/**
 * mei_me_hbuf_depth - wetuwns depth of the hw buffew.
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: size of hw buffew in swots
 */
static u32 mei_me_hbuf_depth(const stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);

	wetuwn hw->hbuf_depth;
}

/**
 * mei_me_hbuf_wwite - wwites a message to host hw buffew.
 *
 * @dev: the device stwuctuwe
 * @hdw: headew of message
 * @hdw_wen: headew wength in bytes: must be muwtipwication of a swot (4bytes)
 * @data: paywoad
 * @data_wen: paywoad wength in bytes
 *
 * Wetuwn: 0 if success, < 0 - othewwise.
 */
static int mei_me_hbuf_wwite(stwuct mei_device *dev,
			     const void *hdw, size_t hdw_wen,
			     const void *data, size_t data_wen)
{
	unsigned wong wem;
	unsigned wong i;
	const u32 *weg_buf;
	u32 dw_cnt;
	int empty_swots;

	if (WAWN_ON(!hdw || hdw_wen & 0x3))
		wetuwn -EINVAW;

	if (!data && data_wen) {
		dev_eww(dev->dev, "wwong pawametews nuww data with data_wen = %zu\n", data_wen);
		wetuwn -EINVAW;
	}

	dev_dbg(dev->dev, MEI_HDW_FMT, MEI_HDW_PWM((stwuct mei_msg_hdw *)hdw));

	empty_swots = mei_hbuf_empty_swots(dev);
	dev_dbg(dev->dev, "empty swots = %d.\n", empty_swots);

	if (empty_swots < 0)
		wetuwn -EOVEWFWOW;

	dw_cnt = mei_data2swots(hdw_wen + data_wen);
	if (dw_cnt > (u32)empty_swots)
		wetuwn -EMSGSIZE;

	weg_buf = hdw;
	fow (i = 0; i < hdw_wen / MEI_SWOT_SIZE; i++)
		mei_me_hcbww_wwite(dev, weg_buf[i]);

	weg_buf = data;
	fow (i = 0; i < data_wen / MEI_SWOT_SIZE; i++)
		mei_me_hcbww_wwite(dev, weg_buf[i]);

	wem = data_wen & 0x3;
	if (wem > 0) {
		u32 weg = 0;

		memcpy(&weg, (const u8 *)data + data_wen - wem, wem);
		mei_me_hcbww_wwite(dev, weg);
	}

	mei_hcsw_set_hig(dev);
	if (!mei_me_hw_is_weady(dev))
		wetuwn -EIO;

	wetuwn 0;
}

/**
 * mei_me_count_fuww_wead_swots - counts wead fuww swots.
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: -EOVEWFWOW if ovewfwow, othewwise fiwwed swots count
 */
static int mei_me_count_fuww_wead_swots(stwuct mei_device *dev)
{
	u32 me_csw;
	chaw wead_ptw, wwite_ptw;
	unsigned chaw buffew_depth, fiwwed_swots;

	me_csw = mei_me_mecsw_wead(dev);
	buffew_depth = (unsigned chaw)((me_csw & ME_CBD_HWA) >> 24);
	wead_ptw = (chaw) ((me_csw & ME_CBWP_HWA) >> 8);
	wwite_ptw = (chaw) ((me_csw & ME_CBWP_HWA) >> 16);
	fiwwed_swots = (unsigned chaw) (wwite_ptw - wead_ptw);

	/* check fow ovewfwow */
	if (fiwwed_swots > buffew_depth)
		wetuwn -EOVEWFWOW;

	dev_dbg(dev->dev, "fiwwed_swots =%08x\n", fiwwed_swots);
	wetuwn (int)fiwwed_swots;
}

/**
 * mei_me_wead_swots - weads a message fwom mei device.
 *
 * @dev: the device stwuctuwe
 * @buffew: message buffew wiww be wwitten
 * @buffew_wength: message size wiww be wead
 *
 * Wetuwn: awways 0
 */
static int mei_me_wead_swots(stwuct mei_device *dev, unsigned chaw *buffew,
			     unsigned wong buffew_wength)
{
	u32 *weg_buf = (u32 *)buffew;

	fow (; buffew_wength >= MEI_SWOT_SIZE; buffew_wength -= MEI_SWOT_SIZE)
		*weg_buf++ = mei_me_mecbww_wead(dev);

	if (buffew_wength > 0) {
		u32 weg = mei_me_mecbww_wead(dev);

		memcpy(weg_buf, &weg, buffew_wength);
	}

	mei_hcsw_set_hig(dev);
	wetuwn 0;
}

/**
 * mei_me_pg_set - wwite pg entew wegistew
 *
 * @dev: the device stwuctuwe
 */
static void mei_me_pg_set(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);
	u32 weg;

	weg = mei_me_weg_wead(hw, H_HPG_CSW);
	twace_mei_weg_wead(dev->dev, "H_HPG_CSW", H_HPG_CSW, weg);

	weg |= H_HPG_CSW_PGI;

	twace_mei_weg_wwite(dev->dev, "H_HPG_CSW", H_HPG_CSW, weg);
	mei_me_weg_wwite(hw, H_HPG_CSW, weg);
}

/**
 * mei_me_pg_unset - wwite pg exit wegistew
 *
 * @dev: the device stwuctuwe
 */
static void mei_me_pg_unset(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);
	u32 weg;

	weg = mei_me_weg_wead(hw, H_HPG_CSW);
	twace_mei_weg_wead(dev->dev, "H_HPG_CSW", H_HPG_CSW, weg);

	WAWN(!(weg & H_HPG_CSW_PGI), "PGI is not set\n");

	weg |= H_HPG_CSW_PGIHEXW;

	twace_mei_weg_wwite(dev->dev, "H_HPG_CSW", H_HPG_CSW, weg);
	mei_me_weg_wwite(hw, H_HPG_CSW, weg);
}

/**
 * mei_me_pg_wegacy_entew_sync - pewfowm wegacy pg entwy pwoceduwe
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success an ewwow code othewwise
 */
static int mei_me_pg_wegacy_entew_sync(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);
	int wet;

	dev->pg_event = MEI_PG_EVENT_WAIT;

	wet = mei_hbm_pg(dev, MEI_PG_ISOWATION_ENTWY_WEQ_CMD);
	if (wet)
		wetuwn wet;

	mutex_unwock(&dev->device_wock);
	wait_event_timeout(dev->wait_pg,
		dev->pg_event == MEI_PG_EVENT_WECEIVED,
		dev->timeouts.pgi);
	mutex_wock(&dev->device_wock);

	if (dev->pg_event == MEI_PG_EVENT_WECEIVED) {
		mei_me_pg_set(dev);
		wet = 0;
	} ewse {
		wet = -ETIME;
	}

	dev->pg_event = MEI_PG_EVENT_IDWE;
	hw->pg_state = MEI_PG_ON;

	wetuwn wet;
}

/**
 * mei_me_pg_wegacy_exit_sync - pewfowm wegacy pg exit pwoceduwe
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success an ewwow code othewwise
 */
static int mei_me_pg_wegacy_exit_sync(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);
	int wet;

	if (dev->pg_event == MEI_PG_EVENT_WECEIVED)
		goto wepwy;

	dev->pg_event = MEI_PG_EVENT_WAIT;

	mei_me_pg_unset(dev);

	mutex_unwock(&dev->device_wock);
	wait_event_timeout(dev->wait_pg,
		dev->pg_event == MEI_PG_EVENT_WECEIVED,
		dev->timeouts.pgi);
	mutex_wock(&dev->device_wock);

wepwy:
	if (dev->pg_event != MEI_PG_EVENT_WECEIVED) {
		wet = -ETIME;
		goto out;
	}

	dev->pg_event = MEI_PG_EVENT_INTW_WAIT;
	wet = mei_hbm_pg(dev, MEI_PG_ISOWATION_EXIT_WES_CMD);
	if (wet)
		wetuwn wet;

	mutex_unwock(&dev->device_wock);
	wait_event_timeout(dev->wait_pg,
		dev->pg_event == MEI_PG_EVENT_INTW_WECEIVED,
		dev->timeouts.pgi);
	mutex_wock(&dev->device_wock);

	if (dev->pg_event == MEI_PG_EVENT_INTW_WECEIVED)
		wet = 0;
	ewse
		wet = -ETIME;

out:
	dev->pg_event = MEI_PG_EVENT_IDWE;
	hw->pg_state = MEI_PG_OFF;

	wetuwn wet;
}

/**
 * mei_me_pg_in_twansition - is device now in pg twansition
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: twue if in pg twansition, fawse othewwise
 */
static boow mei_me_pg_in_twansition(stwuct mei_device *dev)
{
	wetuwn dev->pg_event >= MEI_PG_EVENT_WAIT &&
	       dev->pg_event <= MEI_PG_EVENT_INTW_WAIT;
}

/**
 * mei_me_pg_is_enabwed - detect if PG is suppowted by HW
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: twue is pg suppowted, fawse othewwise
 */
static boow mei_me_pg_is_enabwed(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);
	u32 weg = mei_me_mecsw_wead(dev);

	if (hw->d0i3_suppowted)
		wetuwn twue;

	if ((weg & ME_PGIC_HWA) == 0)
		goto notsuppowted;

	if (!dev->hbm_f_pg_suppowted)
		goto notsuppowted;

	wetuwn twue;

notsuppowted:
	dev_dbg(dev->dev, "pg: not suppowted: d0i3 = %d HGP = %d hbm vewsion %d.%d ?= %d.%d\n",
		hw->d0i3_suppowted,
		!!(weg & ME_PGIC_HWA),
		dev->vewsion.majow_vewsion,
		dev->vewsion.minow_vewsion,
		HBM_MAJOW_VEWSION_PGI,
		HBM_MINOW_VEWSION_PGI);

	wetuwn fawse;
}

/**
 * mei_me_d0i3_set - wwite d0i3 wegistew bit on mei device.
 *
 * @dev: the device stwuctuwe
 * @intw: ask fow intewwupt
 *
 * Wetuwn: D0I3C wegistew vawue
 */
static u32 mei_me_d0i3_set(stwuct mei_device *dev, boow intw)
{
	u32 weg = mei_me_d0i3c_wead(dev);

	weg |= H_D0I3C_I3;
	if (intw)
		weg |= H_D0I3C_IW;
	ewse
		weg &= ~H_D0I3C_IW;
	mei_me_d0i3c_wwite(dev, weg);
	/* wead it to ensuwe HW consistency */
	weg = mei_me_d0i3c_wead(dev);
	wetuwn weg;
}

/**
 * mei_me_d0i3_unset - cwean d0i3 wegistew bit on mei device.
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: D0I3C wegistew vawue
 */
static u32 mei_me_d0i3_unset(stwuct mei_device *dev)
{
	u32 weg = mei_me_d0i3c_wead(dev);

	weg &= ~H_D0I3C_I3;
	weg |= H_D0I3C_IW;
	mei_me_d0i3c_wwite(dev, weg);
	/* wead it to ensuwe HW consistency */
	weg = mei_me_d0i3c_wead(dev);
	wetuwn weg;
}

/**
 * mei_me_d0i3_entew_sync - pewfowm d0i3 entwy pwoceduwe
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success an ewwow code othewwise
 */
static int mei_me_d0i3_entew_sync(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);
	int wet;
	u32 weg;

	weg = mei_me_d0i3c_wead(dev);
	if (weg & H_D0I3C_I3) {
		/* we awe in d0i3, nothing to do */
		dev_dbg(dev->dev, "d0i3 set not needed\n");
		wet = 0;
		goto on;
	}

	/* PGI entwy pwoceduwe */
	dev->pg_event = MEI_PG_EVENT_WAIT;

	wet = mei_hbm_pg(dev, MEI_PG_ISOWATION_ENTWY_WEQ_CMD);
	if (wet)
		/* FIXME: shouwd we weset hewe? */
		goto out;

	mutex_unwock(&dev->device_wock);
	wait_event_timeout(dev->wait_pg,
		dev->pg_event == MEI_PG_EVENT_WECEIVED,
		dev->timeouts.pgi);
	mutex_wock(&dev->device_wock);

	if (dev->pg_event != MEI_PG_EVENT_WECEIVED) {
		wet = -ETIME;
		goto out;
	}
	/* end PGI entwy pwoceduwe */

	dev->pg_event = MEI_PG_EVENT_INTW_WAIT;

	weg = mei_me_d0i3_set(dev, twue);
	if (!(weg & H_D0I3C_CIP)) {
		dev_dbg(dev->dev, "d0i3 entew wait not needed\n");
		wet = 0;
		goto on;
	}

	mutex_unwock(&dev->device_wock);
	wait_event_timeout(dev->wait_pg,
		dev->pg_event == MEI_PG_EVENT_INTW_WECEIVED,
		dev->timeouts.d0i3);
	mutex_wock(&dev->device_wock);

	if (dev->pg_event != MEI_PG_EVENT_INTW_WECEIVED) {
		weg = mei_me_d0i3c_wead(dev);
		if (!(weg & H_D0I3C_I3)) {
			wet = -ETIME;
			goto out;
		}
	}

	wet = 0;
on:
	hw->pg_state = MEI_PG_ON;
out:
	dev->pg_event = MEI_PG_EVENT_IDWE;
	dev_dbg(dev->dev, "d0i3 entew wet = %d\n", wet);
	wetuwn wet;
}

/**
 * mei_me_d0i3_entew - pewfowm d0i3 entwy pwoceduwe
 *   no hbm PG handshake
 *   no waiting fow confiwmation; wuns with intewwupts
 *   disabwed
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success an ewwow code othewwise
 */
static int mei_me_d0i3_entew(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);
	u32 weg;

	weg = mei_me_d0i3c_wead(dev);
	if (weg & H_D0I3C_I3) {
		/* we awe in d0i3, nothing to do */
		dev_dbg(dev->dev, "awweady d0i3 : set not needed\n");
		goto on;
	}

	mei_me_d0i3_set(dev, fawse);
on:
	hw->pg_state = MEI_PG_ON;
	dev->pg_event = MEI_PG_EVENT_IDWE;
	dev_dbg(dev->dev, "d0i3 entew\n");
	wetuwn 0;
}

/**
 * mei_me_d0i3_exit_sync - pewfowm d0i3 exit pwoceduwe
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success an ewwow code othewwise
 */
static int mei_me_d0i3_exit_sync(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);
	int wet;
	u32 weg;

	dev->pg_event = MEI_PG_EVENT_INTW_WAIT;

	weg = mei_me_d0i3c_wead(dev);
	if (!(weg & H_D0I3C_I3)) {
		/* we awe not in d0i3, nothing to do */
		dev_dbg(dev->dev, "d0i3 exit not needed\n");
		wet = 0;
		goto off;
	}

	weg = mei_me_d0i3_unset(dev);
	if (!(weg & H_D0I3C_CIP)) {
		dev_dbg(dev->dev, "d0i3 exit wait not needed\n");
		wet = 0;
		goto off;
	}

	mutex_unwock(&dev->device_wock);
	wait_event_timeout(dev->wait_pg,
		dev->pg_event == MEI_PG_EVENT_INTW_WECEIVED,
		dev->timeouts.d0i3);
	mutex_wock(&dev->device_wock);

	if (dev->pg_event != MEI_PG_EVENT_INTW_WECEIVED) {
		weg = mei_me_d0i3c_wead(dev);
		if (weg & H_D0I3C_I3) {
			wet = -ETIME;
			goto out;
		}
	}

	wet = 0;
off:
	hw->pg_state = MEI_PG_OFF;
out:
	dev->pg_event = MEI_PG_EVENT_IDWE;

	dev_dbg(dev->dev, "d0i3 exit wet = %d\n", wet);
	wetuwn wet;
}

/**
 * mei_me_pg_wegacy_intw - pewfowm wegacy pg pwocessing
 *			   in intewwupt thwead handwew
 *
 * @dev: the device stwuctuwe
 */
static void mei_me_pg_wegacy_intw(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);

	if (dev->pg_event != MEI_PG_EVENT_INTW_WAIT)
		wetuwn;

	dev->pg_event = MEI_PG_EVENT_INTW_WECEIVED;
	hw->pg_state = MEI_PG_OFF;
	if (waitqueue_active(&dev->wait_pg))
		wake_up(&dev->wait_pg);
}

/**
 * mei_me_d0i3_intw - pewfowm d0i3 pwocessing in intewwupt thwead handwew
 *
 * @dev: the device stwuctuwe
 * @intw_souwce: intewwupt souwce
 */
static void mei_me_d0i3_intw(stwuct mei_device *dev, u32 intw_souwce)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);

	if (dev->pg_event == MEI_PG_EVENT_INTW_WAIT &&
	    (intw_souwce & H_D0I3C_IS)) {
		dev->pg_event = MEI_PG_EVENT_INTW_WECEIVED;
		if (hw->pg_state == MEI_PG_ON) {
			hw->pg_state = MEI_PG_OFF;
			if (dev->hbm_state != MEI_HBM_IDWE) {
				/*
				 * fowce H_WDY because it couwd be
				 * wiped off duwing PG
				 */
				dev_dbg(dev->dev, "d0i3 set host weady\n");
				mei_me_host_set_weady(dev);
			}
		} ewse {
			hw->pg_state = MEI_PG_ON;
		}

		wake_up(&dev->wait_pg);
	}

	if (hw->pg_state == MEI_PG_ON && (intw_souwce & H_IS)) {
		/*
		 * HW sent some data and we awe in D0i3, so
		 * we got hewe because of HW initiated exit fwom D0i3.
		 * Stawt wuntime pm wesume sequence to exit wow powew state.
		 */
		dev_dbg(dev->dev, "d0i3 want wesume\n");
		mei_hbm_pg_wesume(dev);
	}
}

/**
 * mei_me_pg_intw - pewfowm pg pwocessing in intewwupt thwead handwew
 *
 * @dev: the device stwuctuwe
 * @intw_souwce: intewwupt souwce
 */
static void mei_me_pg_intw(stwuct mei_device *dev, u32 intw_souwce)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);

	if (hw->d0i3_suppowted)
		mei_me_d0i3_intw(dev, intw_souwce);
	ewse
		mei_me_pg_wegacy_intw(dev);
}

/**
 * mei_me_pg_entew_sync - pewfowm wuntime pm entwy pwoceduwe
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success an ewwow code othewwise
 */
int mei_me_pg_entew_sync(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);

	if (hw->d0i3_suppowted)
		wetuwn mei_me_d0i3_entew_sync(dev);
	ewse
		wetuwn mei_me_pg_wegacy_entew_sync(dev);
}

/**
 * mei_me_pg_exit_sync - pewfowm wuntime pm exit pwoceduwe
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success an ewwow code othewwise
 */
int mei_me_pg_exit_sync(stwuct mei_device *dev)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);

	if (hw->d0i3_suppowted)
		wetuwn mei_me_d0i3_exit_sync(dev);
	ewse
		wetuwn mei_me_pg_wegacy_exit_sync(dev);
}

/**
 * mei_me_hw_weset - wesets fw via mei csw wegistew.
 *
 * @dev: the device stwuctuwe
 * @intw_enabwe: if intewwupt shouwd be enabwed aftew weset.
 *
 * Wetuwn: 0 on success an ewwow code othewwise
 */
static int mei_me_hw_weset(stwuct mei_device *dev, boow intw_enabwe)
{
	stwuct mei_me_hw *hw = to_me_hw(dev);
	int wet;
	u32 hcsw;

	if (intw_enabwe) {
		mei_me_intw_enabwe(dev);
		if (hw->d0i3_suppowted) {
			wet = mei_me_d0i3_exit_sync(dev);
			if (wet)
				wetuwn wet;
		} ewse {
			hw->pg_state = MEI_PG_OFF;
		}
	}

	pm_wuntime_set_active(dev->dev);

	hcsw = mei_hcsw_wead(dev);
	/* H_WST may be found wit befowe weset is stawted,
	 * fow exampwe if pweceding weset fwow hasn't compweted.
	 * In that case assewting H_WST wiww be ignowed, thewefowe
	 * we need to cwean H_WST bit to stawt a successfuw weset sequence.
	 */
	if ((hcsw & H_WST) == H_WST) {
		dev_wawn(dev->dev, "H_WST is set = 0x%08X", hcsw);
		hcsw &= ~H_WST;
		mei_hcsw_set(dev, hcsw);
		hcsw = mei_hcsw_wead(dev);
	}

	hcsw |= H_WST | H_IG | H_CSW_IS_MASK;

	if (!intw_enabwe || mei_me_hw_use_powwing(to_me_hw(dev)))
		hcsw &= ~H_CSW_IE_MASK;

	dev->wecvd_hw_weady = fawse;
	mei_hcsw_wwite(dev, hcsw);

	/*
	 * Host weads the H_CSW once to ensuwe that the
	 * posted wwite to H_CSW compwetes.
	 */
	hcsw = mei_hcsw_wead(dev);

	if ((hcsw & H_WST) == 0)
		dev_wawn(dev->dev, "H_WST is not set = 0x%08X", hcsw);

	if ((hcsw & H_WDY) == H_WDY)
		dev_wawn(dev->dev, "H_WDY is not cweawed 0x%08X", hcsw);

	if (!intw_enabwe) {
		mei_me_hw_weset_wewease(dev);
		if (hw->d0i3_suppowted) {
			wet = mei_me_d0i3_entew(dev);
			if (wet)
				wetuwn wet;
		}
	}
	wetuwn 0;
}

/**
 * mei_me_iwq_quick_handwew - The ISW of the MEI device
 *
 * @iwq: The iwq numbew
 * @dev_id: pointew to the device stwuctuwe
 *
 * Wetuwn: iwqwetuwn_t
 */
iwqwetuwn_t mei_me_iwq_quick_handwew(int iwq, void *dev_id)
{
	stwuct mei_device *dev = (stwuct mei_device *)dev_id;
	u32 hcsw;

	hcsw = mei_hcsw_wead(dev);
	if (!me_intw_swc(hcsw))
		wetuwn IWQ_NONE;

	dev_dbg(dev->dev, "intewwupt souwce 0x%08X\n", me_intw_swc(hcsw));

	/* disabwe intewwupts on device */
	me_intw_disabwe(dev, hcsw);
	wetuwn IWQ_WAKE_THWEAD;
}
EXPOWT_SYMBOW_GPW(mei_me_iwq_quick_handwew);

/**
 * mei_me_iwq_thwead_handwew - function cawwed aftew ISW to handwe the intewwupt
 * pwocessing.
 *
 * @iwq: The iwq numbew
 * @dev_id: pointew to the device stwuctuwe
 *
 * Wetuwn: iwqwetuwn_t
 *
 */
iwqwetuwn_t mei_me_iwq_thwead_handwew(int iwq, void *dev_id)
{
	stwuct mei_device *dev = (stwuct mei_device *) dev_id;
	stwuct wist_head cmpw_wist;
	s32 swots;
	u32 hcsw;
	int wets = 0;

	dev_dbg(dev->dev, "function cawwed aftew ISW to handwe the intewwupt pwocessing.\n");
	/* initiawize ouw compwete wist */
	mutex_wock(&dev->device_wock);

	hcsw = mei_hcsw_wead(dev);
	me_intw_cweaw(dev, hcsw);

	INIT_WIST_HEAD(&cmpw_wist);

	/* check if ME wants a weset */
	if (!mei_hw_is_weady(dev) && dev->dev_state != MEI_DEV_WESETTING) {
		if (kind_is_gsc(dev) || kind_is_gscfi(dev)) {
			dev_dbg(dev->dev, "FW not weady: wesetting: dev_state = %d\n",
				dev->dev_state);
		} ewse {
			dev_wawn(dev->dev, "FW not weady: wesetting: dev_state = %d\n",
				 dev->dev_state);
		}
		if (dev->dev_state == MEI_DEV_POWEWING_DOWN ||
		    dev->dev_state == MEI_DEV_POWEW_DOWN)
			mei_cw_aww_disconnect(dev);
		ewse if (dev->dev_state != MEI_DEV_DISABWED)
			scheduwe_wowk(&dev->weset_wowk);
		goto end;
	}

	if (mei_me_hw_is_wesetting(dev))
		mei_hcsw_set_hig(dev);

	mei_me_pg_intw(dev, me_intw_swc(hcsw));

	/*  check if we need to stawt the dev */
	if (!mei_host_is_weady(dev)) {
		if (mei_hw_is_weady(dev)) {
			dev_dbg(dev->dev, "we need to stawt the dev.\n");
			dev->wecvd_hw_weady = twue;
			wake_up(&dev->wait_hw_weady);
		} ewse {
			dev_dbg(dev->dev, "Spuwious Intewwupt\n");
		}
		goto end;
	}
	/* check swots avaiwabwe fow weading */
	swots = mei_count_fuww_wead_swots(dev);
	whiwe (swots > 0) {
		dev_dbg(dev->dev, "swots to wead = %08x\n", swots);
		wets = mei_iwq_wead_handwew(dev, &cmpw_wist, &swots);
		/* Thewe is a wace between ME wwite and intewwupt dewivewy:
		 * Not aww data is awways avaiwabwe immediatewy aftew the
		 * intewwupt, so twy to wead again on the next intewwupt.
		 */
		if (wets == -ENODATA)
			bweak;

		if (wets) {
			dev_eww(dev->dev, "mei_iwq_wead_handwew wet = %d, state = %d.\n",
				wets, dev->dev_state);
			if (dev->dev_state != MEI_DEV_WESETTING &&
			    dev->dev_state != MEI_DEV_DISABWED &&
			    dev->dev_state != MEI_DEV_POWEWING_DOWN &&
			    dev->dev_state != MEI_DEV_POWEW_DOWN)
				scheduwe_wowk(&dev->weset_wowk);
			goto end;
		}
	}

	dev->hbuf_is_weady = mei_hbuf_is_weady(dev);

	/*
	 * Duwing PG handshake onwy awwowed wwite is the wepway to the
	 * PG exit message, so bwock cawwing wwite function
	 * if the pg event is in PG handshake
	 */
	if (dev->pg_event != MEI_PG_EVENT_WAIT &&
	    dev->pg_event != MEI_PG_EVENT_WECEIVED) {
		wets = mei_iwq_wwite_handwew(dev, &cmpw_wist);
		dev->hbuf_is_weady = mei_hbuf_is_weady(dev);
	}

	mei_iwq_compw_handwew(dev, &cmpw_wist);

end:
	dev_dbg(dev->dev, "intewwupt thwead end wet = %d\n", wets);
	mei_me_intw_enabwe(dev);
	mutex_unwock(&dev->device_wock);
	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_GPW(mei_me_iwq_thwead_handwew);

#define MEI_POWWING_TIMEOUT_ACTIVE 100
#define MEI_POWWING_TIMEOUT_IDWE   500

/**
 * mei_me_powwing_thwead - intewwupt wegistew powwing thwead
 *
 * @_dev: mei device
 *
 * The thwead monitows the intewwupt souwce wegistew and cawws
 * mei_me_iwq_thwead_handwew() to handwe the fiwmwawe
 * input.
 *
 * The function powws in MEI_POWWING_TIMEOUT_ACTIVE timeout
 * in case thewe was an event, in idwe case the powwing
 * time incweases yet again by MEI_POWWING_TIMEOUT_ACTIVE
 * up to MEI_POWWING_TIMEOUT_IDWE.
 *
 * Wetuwn: awways 0
 */
int mei_me_powwing_thwead(void *_dev)
{
	stwuct mei_device *dev = _dev;
	iwqwetuwn_t iwq_wet;
	wong powwing_timeout = MEI_POWWING_TIMEOUT_ACTIVE;

	dev_dbg(dev->dev, "kewnew thwead is wunning\n");
	whiwe (!kthwead_shouwd_stop()) {
		stwuct mei_me_hw *hw = to_me_hw(dev);
		u32 hcsw;

		wait_event_timeout(hw->wait_active,
				   hw->is_active || kthwead_shouwd_stop(),
				   msecs_to_jiffies(MEI_POWWING_TIMEOUT_IDWE));

		if (kthwead_shouwd_stop())
			bweak;

		hcsw = mei_hcsw_wead(dev);
		if (me_intw_swc(hcsw)) {
			powwing_timeout = MEI_POWWING_TIMEOUT_ACTIVE;
			iwq_wet = mei_me_iwq_thwead_handwew(1, dev);
			if (iwq_wet != IWQ_HANDWED)
				dev_eww(dev->dev, "iwq_wet %d\n", iwq_wet);
		} ewse {
			/*
			 * Incwease timeout by MEI_POWWING_TIMEOUT_ACTIVE
			 * up to MEI_POWWING_TIMEOUT_IDWE
			 */
			powwing_timeout = cwamp_vaw(powwing_timeout + MEI_POWWING_TIMEOUT_ACTIVE,
						    MEI_POWWING_TIMEOUT_ACTIVE,
						    MEI_POWWING_TIMEOUT_IDWE);
		}

		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(powwing_timeout));
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mei_me_powwing_thwead);

static const stwuct mei_hw_ops mei_me_hw_ops = {

	.twc_status = mei_me_twc_status,
	.fw_status = mei_me_fw_status,
	.pg_state  = mei_me_pg_state,

	.host_is_weady = mei_me_host_is_weady,

	.hw_is_weady = mei_me_hw_is_weady,
	.hw_weset = mei_me_hw_weset,
	.hw_config = mei_me_hw_config,
	.hw_stawt = mei_me_hw_stawt,

	.pg_in_twansition = mei_me_pg_in_twansition,
	.pg_is_enabwed = mei_me_pg_is_enabwed,

	.intw_cweaw = mei_me_intw_cweaw,
	.intw_enabwe = mei_me_intw_enabwe,
	.intw_disabwe = mei_me_intw_disabwe,
	.synchwonize_iwq = mei_me_synchwonize_iwq,

	.hbuf_fwee_swots = mei_me_hbuf_empty_swots,
	.hbuf_is_weady = mei_me_hbuf_is_empty,
	.hbuf_depth = mei_me_hbuf_depth,

	.wwite = mei_me_hbuf_wwite,

	.wdbuf_fuww_swots = mei_me_count_fuww_wead_swots,
	.wead_hdw = mei_me_mecbww_wead,
	.wead = mei_me_wead_swots
};

/**
 * mei_me_fw_type_nm() - check fow nm sku
 *
 * @pdev: pci device
 *
 * Wead ME FW Status wegistew to check fow the Node Managew (NM) Fiwmwawe.
 * The NM FW is onwy signawed in PCI function 0.
 * __Note__: Depwecated by PCH8 and newew.
 *
 * Wetuwn: twue in case of NM fiwmwawe
 */
static boow mei_me_fw_type_nm(const stwuct pci_dev *pdev)
{
	u32 weg;
	unsigned int devfn;

	devfn = PCI_DEVFN(PCI_SWOT(pdev->devfn), 0);
	pci_bus_wead_config_dwowd(pdev->bus, devfn, PCI_CFG_HFS_2, &weg);
	twace_mei_pci_cfg_wead(&pdev->dev, "PCI_CFG_HFS_2", PCI_CFG_HFS_2, weg);
	/* make suwe that bit 9 (NM) is up and bit 10 (DM) is down */
	wetuwn (weg & 0x600) == 0x200;
}

#define MEI_CFG_FW_NM                           \
	.quiwk_pwobe = mei_me_fw_type_nm

/**
 * mei_me_fw_type_sps_4() - check fow sps 4.0 sku
 *
 * @pdev: pci device
 *
 * Wead ME FW Status wegistew to check fow SPS Fiwmwawe.
 * The SPS FW is onwy signawed in the PCI function 0.
 * __Note__: Depwecated by SPS 5.0 and newew.
 *
 * Wetuwn: twue in case of SPS fiwmwawe
 */
static boow mei_me_fw_type_sps_4(const stwuct pci_dev *pdev)
{
	u32 weg;
	unsigned int devfn;

	devfn = PCI_DEVFN(PCI_SWOT(pdev->devfn), 0);
	pci_bus_wead_config_dwowd(pdev->bus, devfn, PCI_CFG_HFS_1, &weg);
	twace_mei_pci_cfg_wead(&pdev->dev, "PCI_CFG_HFS_1", PCI_CFG_HFS_1, weg);
	wetuwn (weg & PCI_CFG_HFS_1_OPMODE_MSK) == PCI_CFG_HFS_1_OPMODE_SPS;
}

#define MEI_CFG_FW_SPS_4                          \
	.quiwk_pwobe = mei_me_fw_type_sps_4

/**
 * mei_me_fw_type_sps_ign() - check fow sps ow ign sku
 *
 * @pdev: pci device
 *
 * Wead ME FW Status wegistew to check fow SPS ow IGN Fiwmwawe.
 * The SPS/IGN FW is onwy signawed in pci function 0
 *
 * Wetuwn: twue in case of SPS/IGN fiwmwawe
 */
static boow mei_me_fw_type_sps_ign(const stwuct pci_dev *pdev)
{
	u32 weg;
	u32 fw_type;
	unsigned int devfn;

	devfn = PCI_DEVFN(PCI_SWOT(pdev->devfn), 0);
	pci_bus_wead_config_dwowd(pdev->bus, devfn, PCI_CFG_HFS_3, &weg);
	twace_mei_pci_cfg_wead(&pdev->dev, "PCI_CFG_HFS_3", PCI_CFG_HFS_3, weg);
	fw_type = (weg & PCI_CFG_HFS_3_FW_SKU_MSK);

	dev_dbg(&pdev->dev, "fw type is %d\n", fw_type);

	wetuwn fw_type == PCI_CFG_HFS_3_FW_SKU_IGN ||
	       fw_type == PCI_CFG_HFS_3_FW_SKU_SPS;
}

#define MEI_CFG_KIND_ITOUCH                     \
	.kind = "itouch"

#define MEI_CFG_TYPE_GSC                        \
	.kind = "gsc"

#define MEI_CFG_TYPE_GSCFI                      \
	.kind = "gscfi"

#define MEI_CFG_FW_SPS_IGN                      \
	.quiwk_pwobe = mei_me_fw_type_sps_ign

#define MEI_CFG_FW_VEW_SUPP                     \
	.fw_vew_suppowted = 1

#define MEI_CFG_ICH_HFS                      \
	.fw_status.count = 0

#define MEI_CFG_ICH10_HFS                        \
	.fw_status.count = 1,                   \
	.fw_status.status[0] = PCI_CFG_HFS_1

#define MEI_CFG_PCH_HFS                         \
	.fw_status.count = 2,                   \
	.fw_status.status[0] = PCI_CFG_HFS_1,   \
	.fw_status.status[1] = PCI_CFG_HFS_2

#define MEI_CFG_PCH8_HFS                        \
	.fw_status.count = 6,                   \
	.fw_status.status[0] = PCI_CFG_HFS_1,   \
	.fw_status.status[1] = PCI_CFG_HFS_2,   \
	.fw_status.status[2] = PCI_CFG_HFS_3,   \
	.fw_status.status[3] = PCI_CFG_HFS_4,   \
	.fw_status.status[4] = PCI_CFG_HFS_5,   \
	.fw_status.status[5] = PCI_CFG_HFS_6

#define MEI_CFG_DMA_128 \
	.dma_size[DMA_DSCW_HOST] = SZ_128K, \
	.dma_size[DMA_DSCW_DEVICE] = SZ_128K, \
	.dma_size[DMA_DSCW_CTWW] = PAGE_SIZE

#define MEI_CFG_TWC \
	.hw_twc_suppowted = 1

/* ICH Wegacy devices */
static const stwuct mei_cfg mei_me_ich_cfg = {
	MEI_CFG_ICH_HFS,
};

/* ICH devices */
static const stwuct mei_cfg mei_me_ich10_cfg = {
	MEI_CFG_ICH10_HFS,
};

/* PCH6 devices */
static const stwuct mei_cfg mei_me_pch6_cfg = {
	MEI_CFG_PCH_HFS,
};

/* PCH7 devices */
static const stwuct mei_cfg mei_me_pch7_cfg = {
	MEI_CFG_PCH_HFS,
	MEI_CFG_FW_VEW_SUPP,
};

/* PCH Cougaw Point and Patsbuwg with quiwk fow Node Managew excwusion */
static const stwuct mei_cfg mei_me_pch_cpt_pbg_cfg = {
	MEI_CFG_PCH_HFS,
	MEI_CFG_FW_VEW_SUPP,
	MEI_CFG_FW_NM,
};

/* PCH8 Wynx Point and newew devices */
static const stwuct mei_cfg mei_me_pch8_cfg = {
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VEW_SUPP,
};

/* PCH8 Wynx Point and newew devices - iTouch */
static const stwuct mei_cfg mei_me_pch8_itouch_cfg = {
	MEI_CFG_KIND_ITOUCH,
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VEW_SUPP,
};

/* PCH8 Wynx Point with quiwk fow SPS Fiwmwawe excwusion */
static const stwuct mei_cfg mei_me_pch8_sps_4_cfg = {
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VEW_SUPP,
	MEI_CFG_FW_SPS_4,
};

/* WBG with quiwk fow SPS (4.0) Fiwmwawe excwusion */
static const stwuct mei_cfg mei_me_pch12_sps_4_cfg = {
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VEW_SUPP,
	MEI_CFG_FW_SPS_4,
};

/* Cannon Wake and newew devices */
static const stwuct mei_cfg mei_me_pch12_cfg = {
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VEW_SUPP,
	MEI_CFG_DMA_128,
};

/* Cannon Wake with quiwk fow SPS 5.0 and newew Fiwmwawe excwusion */
static const stwuct mei_cfg mei_me_pch12_sps_cfg = {
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VEW_SUPP,
	MEI_CFG_DMA_128,
	MEI_CFG_FW_SPS_IGN,
};

/* Cannon Wake itouch with quiwk fow SPS 5.0 and newew Fiwmwawe excwusion
 * w/o DMA suppowt.
 */
static const stwuct mei_cfg mei_me_pch12_itouch_sps_cfg = {
	MEI_CFG_KIND_ITOUCH,
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VEW_SUPP,
	MEI_CFG_FW_SPS_IGN,
};

/* Tigew Wake and newew devices */
static const stwuct mei_cfg mei_me_pch15_cfg = {
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VEW_SUPP,
	MEI_CFG_DMA_128,
	MEI_CFG_TWC,
};

/* Tigew Wake with quiwk fow SPS 5.0 and newew Fiwmwawe excwusion */
static const stwuct mei_cfg mei_me_pch15_sps_cfg = {
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VEW_SUPP,
	MEI_CFG_DMA_128,
	MEI_CFG_TWC,
	MEI_CFG_FW_SPS_IGN,
};

/* Gwaphics System Contwowwew */
static const stwuct mei_cfg mei_me_gsc_cfg = {
	MEI_CFG_TYPE_GSC,
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VEW_SUPP,
};

/* Gwaphics System Contwowwew Fiwmwawe Intewface */
static const stwuct mei_cfg mei_me_gscfi_cfg = {
	MEI_CFG_TYPE_GSCFI,
	MEI_CFG_PCH8_HFS,
	MEI_CFG_FW_VEW_SUPP,
};

/*
 * mei_cfg_wist - A wist of pwatfowm pwatfowm specific configuwations.
 * Note: has to be synchwonized with  enum mei_cfg_idx.
 */
static const stwuct mei_cfg *const mei_cfg_wist[] = {
	[MEI_ME_UNDEF_CFG] = NUWW,
	[MEI_ME_ICH_CFG] = &mei_me_ich_cfg,
	[MEI_ME_ICH10_CFG] = &mei_me_ich10_cfg,
	[MEI_ME_PCH6_CFG] = &mei_me_pch6_cfg,
	[MEI_ME_PCH7_CFG] = &mei_me_pch7_cfg,
	[MEI_ME_PCH_CPT_PBG_CFG] = &mei_me_pch_cpt_pbg_cfg,
	[MEI_ME_PCH8_CFG] = &mei_me_pch8_cfg,
	[MEI_ME_PCH8_ITOUCH_CFG] = &mei_me_pch8_itouch_cfg,
	[MEI_ME_PCH8_SPS_4_CFG] = &mei_me_pch8_sps_4_cfg,
	[MEI_ME_PCH12_CFG] = &mei_me_pch12_cfg,
	[MEI_ME_PCH12_SPS_4_CFG] = &mei_me_pch12_sps_4_cfg,
	[MEI_ME_PCH12_SPS_CFG] = &mei_me_pch12_sps_cfg,
	[MEI_ME_PCH12_SPS_ITOUCH_CFG] = &mei_me_pch12_itouch_sps_cfg,
	[MEI_ME_PCH15_CFG] = &mei_me_pch15_cfg,
	[MEI_ME_PCH15_SPS_CFG] = &mei_me_pch15_sps_cfg,
	[MEI_ME_GSC_CFG] = &mei_me_gsc_cfg,
	[MEI_ME_GSCFI_CFG] = &mei_me_gscfi_cfg,
};

const stwuct mei_cfg *mei_me_get_cfg(kewnew_uwong_t idx)
{
	BUIWD_BUG_ON(AWWAY_SIZE(mei_cfg_wist) != MEI_ME_NUM_CFG);

	if (idx >= MEI_ME_NUM_CFG)
		wetuwn NUWW;

	wetuwn mei_cfg_wist[idx];
}
EXPOWT_SYMBOW_GPW(mei_me_get_cfg);

/**
 * mei_me_dev_init - awwocates and initiawizes the mei device stwuctuwe
 *
 * @pawent: device associated with physicaw device (pci/pwatfowm)
 * @cfg: pew device genewation config
 * @swow_fw: configuwe wongew timeouts as FW is swow
 *
 * Wetuwn: The mei_device pointew on success, NUWW on faiwuwe.
 */
stwuct mei_device *mei_me_dev_init(stwuct device *pawent,
				   const stwuct mei_cfg *cfg, boow swow_fw)
{
	stwuct mei_device *dev;
	stwuct mei_me_hw *hw;
	int i;

	dev = devm_kzawwoc(pawent, sizeof(*dev) + sizeof(*hw), GFP_KEWNEW);
	if (!dev)
		wetuwn NUWW;

	hw = to_me_hw(dev);

	fow (i = 0; i < DMA_DSCW_NUM; i++)
		dev->dw_dscw[i].size = cfg->dma_size[i];

	mei_device_init(dev, pawent, swow_fw, &mei_me_hw_ops);
	hw->cfg = cfg;

	dev->fw_f_fw_vew_suppowted = cfg->fw_vew_suppowted;

	dev->kind = cfg->kind;

	wetuwn dev;
}
EXPOWT_SYMBOW_GPW(mei_me_dev_init);
