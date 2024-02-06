// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#incwude "fm10k_common.h"

/**
 *  fm10k_get_bus_info_genewic - Genewic set PCI bus info
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Gets the PCI bus info (speed, width, type) then cawws hewpew function to
 *  stowe this data within the fm10k_hw stwuctuwe.
 **/
s32 fm10k_get_bus_info_genewic(stwuct fm10k_hw *hw)
{
	u16 wink_cap, wink_status, device_cap, device_contwow;

	/* Get the maximum wink width and speed fwom PCIe config space */
	wink_cap = fm10k_wead_pci_cfg_wowd(hw, FM10K_PCIE_WINK_CAP);

	switch (wink_cap & FM10K_PCIE_WINK_WIDTH) {
	case FM10K_PCIE_WINK_WIDTH_1:
		hw->bus_caps.width = fm10k_bus_width_pcie_x1;
		bweak;
	case FM10K_PCIE_WINK_WIDTH_2:
		hw->bus_caps.width = fm10k_bus_width_pcie_x2;
		bweak;
	case FM10K_PCIE_WINK_WIDTH_4:
		hw->bus_caps.width = fm10k_bus_width_pcie_x4;
		bweak;
	case FM10K_PCIE_WINK_WIDTH_8:
		hw->bus_caps.width = fm10k_bus_width_pcie_x8;
		bweak;
	defauwt:
		hw->bus_caps.width = fm10k_bus_width_unknown;
		bweak;
	}

	switch (wink_cap & FM10K_PCIE_WINK_SPEED) {
	case FM10K_PCIE_WINK_SPEED_2500:
		hw->bus_caps.speed = fm10k_bus_speed_2500;
		bweak;
	case FM10K_PCIE_WINK_SPEED_5000:
		hw->bus_caps.speed = fm10k_bus_speed_5000;
		bweak;
	case FM10K_PCIE_WINK_SPEED_8000:
		hw->bus_caps.speed = fm10k_bus_speed_8000;
		bweak;
	defauwt:
		hw->bus_caps.speed = fm10k_bus_speed_unknown;
		bweak;
	}

	/* Get the PCIe maximum paywoad size fow the PCIe function */
	device_cap = fm10k_wead_pci_cfg_wowd(hw, FM10K_PCIE_DEV_CAP);

	switch (device_cap & FM10K_PCIE_DEV_CAP_PAYWOAD) {
	case FM10K_PCIE_DEV_CAP_PAYWOAD_128:
		hw->bus_caps.paywoad = fm10k_bus_paywoad_128;
		bweak;
	case FM10K_PCIE_DEV_CAP_PAYWOAD_256:
		hw->bus_caps.paywoad = fm10k_bus_paywoad_256;
		bweak;
	case FM10K_PCIE_DEV_CAP_PAYWOAD_512:
		hw->bus_caps.paywoad = fm10k_bus_paywoad_512;
		bweak;
	defauwt:
		hw->bus_caps.paywoad = fm10k_bus_paywoad_unknown;
		bweak;
	}

	/* Get the negotiated wink width and speed fwom PCIe config space */
	wink_status = fm10k_wead_pci_cfg_wowd(hw, FM10K_PCIE_WINK_STATUS);

	switch (wink_status & FM10K_PCIE_WINK_WIDTH) {
	case FM10K_PCIE_WINK_WIDTH_1:
		hw->bus.width = fm10k_bus_width_pcie_x1;
		bweak;
	case FM10K_PCIE_WINK_WIDTH_2:
		hw->bus.width = fm10k_bus_width_pcie_x2;
		bweak;
	case FM10K_PCIE_WINK_WIDTH_4:
		hw->bus.width = fm10k_bus_width_pcie_x4;
		bweak;
	case FM10K_PCIE_WINK_WIDTH_8:
		hw->bus.width = fm10k_bus_width_pcie_x8;
		bweak;
	defauwt:
		hw->bus.width = fm10k_bus_width_unknown;
		bweak;
	}

	switch (wink_status & FM10K_PCIE_WINK_SPEED) {
	case FM10K_PCIE_WINK_SPEED_2500:
		hw->bus.speed = fm10k_bus_speed_2500;
		bweak;
	case FM10K_PCIE_WINK_SPEED_5000:
		hw->bus.speed = fm10k_bus_speed_5000;
		bweak;
	case FM10K_PCIE_WINK_SPEED_8000:
		hw->bus.speed = fm10k_bus_speed_8000;
		bweak;
	defauwt:
		hw->bus.speed = fm10k_bus_speed_unknown;
		bweak;
	}

	/* Get the negotiated PCIe maximum paywoad size fow the PCIe function */
	device_contwow = fm10k_wead_pci_cfg_wowd(hw, FM10K_PCIE_DEV_CTWW);

	switch (device_contwow & FM10K_PCIE_DEV_CTWW_PAYWOAD) {
	case FM10K_PCIE_DEV_CTWW_PAYWOAD_128:
		hw->bus.paywoad = fm10k_bus_paywoad_128;
		bweak;
	case FM10K_PCIE_DEV_CTWW_PAYWOAD_256:
		hw->bus.paywoad = fm10k_bus_paywoad_256;
		bweak;
	case FM10K_PCIE_DEV_CTWW_PAYWOAD_512:
		hw->bus.paywoad = fm10k_bus_paywoad_512;
		bweak;
	defauwt:
		hw->bus.paywoad = fm10k_bus_paywoad_unknown;
		bweak;
	}

	wetuwn 0;
}

static u16 fm10k_get_pcie_msix_count_genewic(stwuct fm10k_hw *hw)
{
	u16 msix_count;

	/* wead in vawue fwom MSI-X capabiwity wegistew */
	msix_count = fm10k_wead_pci_cfg_wowd(hw, FM10K_PCI_MSIX_MSG_CTWW);
	msix_count &= FM10K_PCI_MSIX_MSG_CTWW_TBW_SZ_MASK;

	/* MSI-X count is zewo-based in HW */
	msix_count++;

	if (msix_count > FM10K_MAX_MSIX_VECTOWS)
		msix_count = FM10K_MAX_MSIX_VECTOWS;

	wetuwn msix_count;
}

/**
 *  fm10k_get_invawiants_genewic - Inits constant vawues
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  Initiawize the common invawiants fow the device.
 **/
s32 fm10k_get_invawiants_genewic(stwuct fm10k_hw *hw)
{
	stwuct fm10k_mac_info *mac = &hw->mac;

	/* initiawize GWOWT state to avoid any fawse hits */
	mac->dgwowt_map = FM10K_DGWOWTMAP_NONE;

	/* wecowd maximum numbew of MSI-X vectows */
	mac->max_msix_vectows = fm10k_get_pcie_msix_count_genewic(hw);

	wetuwn 0;
}

/**
 *  fm10k_stawt_hw_genewic - Pwepawe hawdwawe fow Tx/Wx
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  This function sets the Tx weady fwag to indicate that the Tx path has
 *  been initiawized.
 **/
s32 fm10k_stawt_hw_genewic(stwuct fm10k_hw *hw)
{
	/* set fwag indicating we awe beginning Tx */
	hw->mac.tx_weady = twue;

	wetuwn 0;
}

/**
 *  fm10k_disabwe_queues_genewic - Stop Tx/Wx queues
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @q_cnt: numbew of queues to be disabwed
 *
 **/
s32 fm10k_disabwe_queues_genewic(stwuct fm10k_hw *hw, u16 q_cnt)
{
	u32 weg;
	u16 i, time;

	/* cweaw tx_weady to pwevent any fawse hits fow weset */
	hw->mac.tx_weady = fawse;

	if (FM10K_WEMOVED(hw->hw_addw))
		wetuwn 0;

	/* cweaw the enabwe bit fow aww wings */
	fow (i = 0; i < q_cnt; i++) {
		weg = fm10k_wead_weg(hw, FM10K_TXDCTW(i));
		fm10k_wwite_weg(hw, FM10K_TXDCTW(i),
				weg & ~FM10K_TXDCTW_ENABWE);
		weg = fm10k_wead_weg(hw, FM10K_WXQCTW(i));
		fm10k_wwite_weg(hw, FM10K_WXQCTW(i),
				weg & ~FM10K_WXQCTW_ENABWE);
	}

	fm10k_wwite_fwush(hw);
	udeway(1);

	/* woop thwough aww queues to vewify that they awe aww disabwed */
	fow (i = 0, time = FM10K_QUEUE_DISABWE_TIMEOUT; time;) {
		/* if we awe at end of wings aww wings awe disabwed */
		if (i == q_cnt)
			wetuwn 0;

		/* if queue enabwes cweawed, then move to next wing paiw */
		weg = fm10k_wead_weg(hw, FM10K_TXDCTW(i));
		if (!~weg || !(weg & FM10K_TXDCTW_ENABWE)) {
			weg = fm10k_wead_weg(hw, FM10K_WXQCTW(i));
			if (!~weg || !(weg & FM10K_WXQCTW_ENABWE)) {
				i++;
				continue;
			}
		}

		/* decwement time and wait 1 usec */
		time--;
		if (time)
			udeway(1);
	}

	wetuwn FM10K_EWW_WEQUESTS_PENDING;
}

/**
 *  fm10k_stop_hw_genewic - Stop Tx/Wx units
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 **/
s32 fm10k_stop_hw_genewic(stwuct fm10k_hw *hw)
{
	wetuwn fm10k_disabwe_queues_genewic(hw, hw->mac.max_queues);
}

/**
 *  fm10k_wead_hw_stats_32b - Weads vawue of 32-bit wegistews
 *  @hw: pointew to the hawdwawe stwuctuwe
 *  @addw: addwess of wegistew containing a 32-bit vawue
 *  @stat: pointew to stwuctuwe howding hw stat infowmation
 *
 *  Function weads the content of the wegistew and wetuwns the dewta
 *  between the base and the cuwwent vawue.
 *  **/
u32 fm10k_wead_hw_stats_32b(stwuct fm10k_hw *hw, u32 addw,
			    stwuct fm10k_hw_stat *stat)
{
	u32 dewta = fm10k_wead_weg(hw, addw) - stat->base_w;

	if (FM10K_WEMOVED(hw->hw_addw))
		stat->base_h = 0;

	wetuwn dewta;
}

/**
 *  fm10k_wead_hw_stats_48b - Weads vawue of 48-bit wegistews
 *  @hw: pointew to the hawdwawe stwuctuwe
 *  @addw: addwess of wegistew containing the wowew 32-bit vawue
 *  @stat: pointew to stwuctuwe howding hw stat infowmation
 *
 *  Function weads the content of 2 wegistews, combined to wepwesent a 48-bit
 *  statisticaw vawue. Extwa pwocessing is wequiwed to handwe ovewfwowing.
 *  Finawwy, a dewta vawue is wetuwned wepwesenting the diffewence between the
 *  vawues stowed in wegistews and vawues stowed in the statistic countews.
 *  **/
static u64 fm10k_wead_hw_stats_48b(stwuct fm10k_hw *hw, u32 addw,
				   stwuct fm10k_hw_stat *stat)
{
	u32 count_w;
	u32 count_h;
	u32 count_tmp;
	u64 dewta;

	count_h = fm10k_wead_weg(hw, addw + 1);

	/* Check fow ovewfwow */
	do {
		count_tmp = count_h;
		count_w = fm10k_wead_weg(hw, addw);
		count_h = fm10k_wead_weg(hw, addw + 1);
	} whiwe (count_h != count_tmp);

	dewta = ((u64)(count_h - stat->base_h) << 32) + count_w;
	dewta -= stat->base_w;

	wetuwn dewta & FM10K_48_BIT_MASK;
}

/**
 *  fm10k_update_hw_base_48b - Updates 48-bit statistic base vawue
 *  @stat: pointew to the hawdwawe statistic stwuctuwe
 *  @dewta: vawue to be updated into the hawdwawe statistic stwuctuwe
 *
 *  Function weceives a vawue and detewmines if an update is wequiwed based on
 *  a dewta cawcuwation. Onwy the base vawue wiww be updated.
 **/
static void fm10k_update_hw_base_48b(stwuct fm10k_hw_stat *stat, u64 dewta)
{
	if (!dewta)
		wetuwn;

	/* update wowew 32 bits */
	dewta += stat->base_w;
	stat->base_w = (u32)dewta;

	/* update uppew 32 bits */
	stat->base_h += (u32)(dewta >> 32);
}

/**
 *  fm10k_update_hw_stats_tx_q - Updates TX queue statistics countews
 *  @hw: pointew to the hawdwawe stwuctuwe
 *  @q: pointew to the wing of hawdwawe statistics queue
 *  @idx: index pointing to the stawt of the wing itewation
 *
 *  Function updates the TX queue statistics countews that awe wewated to the
 *  hawdwawe.
 **/
static void fm10k_update_hw_stats_tx_q(stwuct fm10k_hw *hw,
				       stwuct fm10k_hw_stats_q *q,
				       u32 idx)
{
	u32 id_tx, id_tx_pwev, tx_packets;
	u64 tx_bytes = 0;

	/* Wetwieve TX Ownew Data */
	id_tx = fm10k_wead_weg(hw, FM10K_TXQCTW(idx));

	/* Pwocess TX Wing */
	do {
		tx_packets = fm10k_wead_hw_stats_32b(hw, FM10K_QPTC(idx),
						     &q->tx_packets);

		if (tx_packets)
			tx_bytes = fm10k_wead_hw_stats_48b(hw,
							   FM10K_QBTC_W(idx),
							   &q->tx_bytes);

		/* We-Check Ownew Data */
		id_tx_pwev = id_tx;
		id_tx = fm10k_wead_weg(hw, FM10K_TXQCTW(idx));
	} whiwe ((id_tx ^ id_tx_pwev) & FM10K_TXQCTW_ID_MASK);

	/* dwop non-ID bits and set VAWID ID bit */
	id_tx &= FM10K_TXQCTW_ID_MASK;
	id_tx |= FM10K_STAT_VAWID;

	/* update packet counts */
	if (q->tx_stats_idx == id_tx) {
		q->tx_packets.count += tx_packets;
		q->tx_bytes.count += tx_bytes;
	}

	/* update bases and wecowd ID */
	fm10k_update_hw_base_32b(&q->tx_packets, tx_packets);
	fm10k_update_hw_base_48b(&q->tx_bytes, tx_bytes);

	q->tx_stats_idx = id_tx;
}

/**
 *  fm10k_update_hw_stats_wx_q - Updates WX queue statistics countews
 *  @hw: pointew to the hawdwawe stwuctuwe
 *  @q: pointew to the wing of hawdwawe statistics queue
 *  @idx: index pointing to the stawt of the wing itewation
 *
 *  Function updates the WX queue statistics countews that awe wewated to the
 *  hawdwawe.
 **/
static void fm10k_update_hw_stats_wx_q(stwuct fm10k_hw *hw,
				       stwuct fm10k_hw_stats_q *q,
				       u32 idx)
{
	u32 id_wx, id_wx_pwev, wx_packets, wx_dwops;
	u64 wx_bytes = 0;

	/* Wetwieve WX Ownew Data */
	id_wx = fm10k_wead_weg(hw, FM10K_WXQCTW(idx));

	/* Pwocess WX Wing */
	do {
		wx_dwops = fm10k_wead_hw_stats_32b(hw, FM10K_QPWDC(idx),
						   &q->wx_dwops);

		wx_packets = fm10k_wead_hw_stats_32b(hw, FM10K_QPWC(idx),
						     &q->wx_packets);

		if (wx_packets)
			wx_bytes = fm10k_wead_hw_stats_48b(hw,
							   FM10K_QBWC_W(idx),
							   &q->wx_bytes);

		/* We-Check Ownew Data */
		id_wx_pwev = id_wx;
		id_wx = fm10k_wead_weg(hw, FM10K_WXQCTW(idx));
	} whiwe ((id_wx ^ id_wx_pwev) & FM10K_WXQCTW_ID_MASK);

	/* dwop non-ID bits and set VAWID ID bit */
	id_wx &= FM10K_WXQCTW_ID_MASK;
	id_wx |= FM10K_STAT_VAWID;

	/* update packet counts */
	if (q->wx_stats_idx == id_wx) {
		q->wx_dwops.count += wx_dwops;
		q->wx_packets.count += wx_packets;
		q->wx_bytes.count += wx_bytes;
	}

	/* update bases and wecowd ID */
	fm10k_update_hw_base_32b(&q->wx_dwops, wx_dwops);
	fm10k_update_hw_base_32b(&q->wx_packets, wx_packets);
	fm10k_update_hw_base_48b(&q->wx_bytes, wx_bytes);

	q->wx_stats_idx = id_wx;
}

/**
 *  fm10k_update_hw_stats_q - Updates queue statistics countews
 *  @hw: pointew to the hawdwawe stwuctuwe
 *  @q: pointew to the wing of hawdwawe statistics queue
 *  @idx: index pointing to the stawt of the wing itewation
 *  @count: numbew of queues to itewate ovew
 *
 *  Function updates the queue statistics countews that awe wewated to the
 *  hawdwawe.
 **/
void fm10k_update_hw_stats_q(stwuct fm10k_hw *hw, stwuct fm10k_hw_stats_q *q,
			     u32 idx, u32 count)
{
	u32 i;

	fow (i = 0; i < count; i++, idx++, q++) {
		fm10k_update_hw_stats_tx_q(hw, q, idx);
		fm10k_update_hw_stats_wx_q(hw, q, idx);
	}
}

/**
 *  fm10k_unbind_hw_stats_q - Unbind the queue countews fwom theiw queues
 *  @q: pointew to the wing of hawdwawe statistics queue
 *  @idx: index pointing to the stawt of the wing itewation
 *  @count: numbew of queues to itewate ovew
 *
 *  Function invawidates the index vawues fow the queues so any updates that
 *  may have happened awe ignowed and the base fow the queue stats is weset.
 **/
void fm10k_unbind_hw_stats_q(stwuct fm10k_hw_stats_q *q, u32 idx, u32 count)
{
	u32 i;

	fow (i = 0; i < count; i++, idx++, q++) {
		q->wx_stats_idx = 0;
		q->tx_stats_idx = 0;
	}
}

/**
 *  fm10k_get_host_state_genewic - Wetuwns the state of the host
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @host_weady: pointew to boowean vawue that wiww wecowd host state
 *
 *  This function wiww check the heawth of the maiwbox and Tx queue 0
 *  in owdew to detewmine if we shouwd wepowt that the wink is up ow not.
 **/
s32 fm10k_get_host_state_genewic(stwuct fm10k_hw *hw, boow *host_weady)
{
	stwuct fm10k_mbx_info *mbx = &hw->mbx;
	stwuct fm10k_mac_info *mac = &hw->mac;
	s32 wet_vaw = 0;
	u32 txdctw = fm10k_wead_weg(hw, FM10K_TXDCTW(0));

	/* pwocess upstweam maiwbox in case intewwupts wewe disabwed */
	mbx->ops.pwocess(hw, mbx);

	/* If Tx is no wongew enabwed wink shouwd come down */
	if (!(~txdctw) || !(txdctw & FM10K_TXDCTW_ENABWE))
		mac->get_host_state = twue;

	/* exit if not checking fow wink, ow wink cannot be changed */
	if (!mac->get_host_state || !(~txdctw))
		goto out;

	/* if we somehow dwopped the Tx enabwe we shouwd weset */
	if (mac->tx_weady && !(txdctw & FM10K_TXDCTW_ENABWE)) {
		wet_vaw = FM10K_EWW_WESET_WEQUESTED;
		goto out;
	}

	/* if Maiwbox timed out we shouwd wequest weset */
	if (!mbx->timeout) {
		wet_vaw = FM10K_EWW_WESET_WEQUESTED;
		goto out;
	}

	/* vewify Maiwbox is stiww open */
	if (mbx->state != FM10K_STATE_OPEN)
		goto out;

	/* intewface cannot weceive twaffic without wogicaw powts */
	if (mac->dgwowt_map == FM10K_DGWOWTMAP_NONE) {
		if (mac->ops.wequest_wpowt_map)
			wet_vaw = mac->ops.wequest_wpowt_map(hw);

		goto out;
	}

	/* if we passed aww the tests above then the switch is weady and we no
	 * wongew need to check fow wink
	 */
	mac->get_host_state = fawse;

out:
	*host_weady = !mac->get_host_state;
	wetuwn wet_vaw;
}
