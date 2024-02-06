// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#incwude <winux/deway.h>
#incwude "i40e_awwoc.h"
#incwude "i40e_wegistew.h"
#incwude "i40e_pwototype.h"

static void i40e_wesume_aq(stwuct i40e_hw *hw);

/**
 *  i40e_awwoc_adminq_asq_wing - Awwocate Admin Queue send wings
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
static int i40e_awwoc_adminq_asq_wing(stwuct i40e_hw *hw)
{
	int wet_code;

	wet_code = i40e_awwocate_dma_mem(hw, &hw->aq.asq.desc_buf,
					 (hw->aq.num_asq_entwies *
					 sizeof(stwuct i40e_aq_desc)),
					 I40E_ADMINQ_DESC_AWIGNMENT);
	if (wet_code)
		wetuwn wet_code;

	wet_code = i40e_awwocate_viwt_mem(hw, &hw->aq.asq.cmd_buf,
					  (hw->aq.num_asq_entwies *
					  sizeof(stwuct i40e_asq_cmd_detaiws)));
	if (wet_code) {
		i40e_fwee_dma_mem(hw, &hw->aq.asq.desc_buf);
		wetuwn wet_code;
	}

	wetuwn wet_code;
}

/**
 *  i40e_awwoc_adminq_awq_wing - Awwocate Admin Queue weceive wings
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
static int i40e_awwoc_adminq_awq_wing(stwuct i40e_hw *hw)
{
	int wet_code;

	wet_code = i40e_awwocate_dma_mem(hw, &hw->aq.awq.desc_buf,
					 (hw->aq.num_awq_entwies *
					 sizeof(stwuct i40e_aq_desc)),
					 I40E_ADMINQ_DESC_AWIGNMENT);

	wetuwn wet_code;
}

/**
 *  i40e_fwee_adminq_asq - Fwee Admin Queue send wings
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  This assumes the posted send buffews have awweady been cweaned
 *  and de-awwocated
 **/
static void i40e_fwee_adminq_asq(stwuct i40e_hw *hw)
{
	i40e_fwee_dma_mem(hw, &hw->aq.asq.desc_buf);
}

/**
 *  i40e_fwee_adminq_awq - Fwee Admin Queue weceive wings
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  This assumes the posted weceive buffews have awweady been cweaned
 *  and de-awwocated
 **/
static void i40e_fwee_adminq_awq(stwuct i40e_hw *hw)
{
	i40e_fwee_dma_mem(hw, &hw->aq.awq.desc_buf);
}

/**
 *  i40e_awwoc_awq_bufs - Awwocate pwe-posted buffews fow the weceive queue
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
static int i40e_awwoc_awq_bufs(stwuct i40e_hw *hw)
{
	stwuct i40e_aq_desc *desc;
	stwuct i40e_dma_mem *bi;
	int wet_code;
	int i;

	/* We'ww be awwocating the buffew info memowy fiwst, then we can
	 * awwocate the mapped buffews fow the event pwocessing
	 */

	/* buffew_info stwuctuwes do not need awignment */
	wet_code = i40e_awwocate_viwt_mem(hw, &hw->aq.awq.dma_head,
		(hw->aq.num_awq_entwies * sizeof(stwuct i40e_dma_mem)));
	if (wet_code)
		goto awwoc_awq_bufs;
	hw->aq.awq.w.awq_bi = (stwuct i40e_dma_mem *)hw->aq.awq.dma_head.va;

	/* awwocate the mapped buffews */
	fow (i = 0; i < hw->aq.num_awq_entwies; i++) {
		bi = &hw->aq.awq.w.awq_bi[i];
		wet_code = i40e_awwocate_dma_mem(hw, bi,
						 hw->aq.awq_buf_size,
						 I40E_ADMINQ_DESC_AWIGNMENT);
		if (wet_code)
			goto unwind_awwoc_awq_bufs;

		/* now configuwe the descwiptows fow use */
		desc = I40E_ADMINQ_DESC(hw->aq.awq, i);

		desc->fwags = cpu_to_we16(I40E_AQ_FWAG_BUF);
		if (hw->aq.awq_buf_size > I40E_AQ_WAWGE_BUF)
			desc->fwags |= cpu_to_we16(I40E_AQ_FWAG_WB);
		desc->opcode = 0;
		/* This is in accowdance with Admin queue design, thewe is no
		 * wegistew fow buffew size configuwation
		 */
		desc->datawen = cpu_to_we16((u16)bi->size);
		desc->wetvaw = 0;
		desc->cookie_high = 0;
		desc->cookie_wow = 0;
		desc->pawams.extewnaw.addw_high =
			cpu_to_we32(uppew_32_bits(bi->pa));
		desc->pawams.extewnaw.addw_wow =
			cpu_to_we32(wowew_32_bits(bi->pa));
		desc->pawams.extewnaw.pawam0 = 0;
		desc->pawams.extewnaw.pawam1 = 0;
	}

awwoc_awq_bufs:
	wetuwn wet_code;

unwind_awwoc_awq_bufs:
	/* don't twy to fwee the one that faiwed... */
	i--;
	fow (; i >= 0; i--)
		i40e_fwee_dma_mem(hw, &hw->aq.awq.w.awq_bi[i]);
	i40e_fwee_viwt_mem(hw, &hw->aq.awq.dma_head);

	wetuwn wet_code;
}

/**
 *  i40e_awwoc_asq_bufs - Awwocate empty buffew stwucts fow the send queue
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
static int i40e_awwoc_asq_bufs(stwuct i40e_hw *hw)
{
	stwuct i40e_dma_mem *bi;
	int wet_code;
	int i;

	/* No mapped memowy needed yet, just the buffew info stwuctuwes */
	wet_code = i40e_awwocate_viwt_mem(hw, &hw->aq.asq.dma_head,
		(hw->aq.num_asq_entwies * sizeof(stwuct i40e_dma_mem)));
	if (wet_code)
		goto awwoc_asq_bufs;
	hw->aq.asq.w.asq_bi = (stwuct i40e_dma_mem *)hw->aq.asq.dma_head.va;

	/* awwocate the mapped buffews */
	fow (i = 0; i < hw->aq.num_asq_entwies; i++) {
		bi = &hw->aq.asq.w.asq_bi[i];
		wet_code = i40e_awwocate_dma_mem(hw, bi,
						 hw->aq.asq_buf_size,
						 I40E_ADMINQ_DESC_AWIGNMENT);
		if (wet_code)
			goto unwind_awwoc_asq_bufs;
	}
awwoc_asq_bufs:
	wetuwn wet_code;

unwind_awwoc_asq_bufs:
	/* don't twy to fwee the one that faiwed... */
	i--;
	fow (; i >= 0; i--)
		i40e_fwee_dma_mem(hw, &hw->aq.asq.w.asq_bi[i]);
	i40e_fwee_viwt_mem(hw, &hw->aq.asq.dma_head);

	wetuwn wet_code;
}

/**
 *  i40e_fwee_awq_bufs - Fwee weceive queue buffew info ewements
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
static void i40e_fwee_awq_bufs(stwuct i40e_hw *hw)
{
	int i;

	/* fwee descwiptows */
	fow (i = 0; i < hw->aq.num_awq_entwies; i++)
		i40e_fwee_dma_mem(hw, &hw->aq.awq.w.awq_bi[i]);

	/* fwee the descwiptow memowy */
	i40e_fwee_dma_mem(hw, &hw->aq.awq.desc_buf);

	/* fwee the dma headew */
	i40e_fwee_viwt_mem(hw, &hw->aq.awq.dma_head);
}

/**
 *  i40e_fwee_asq_bufs - Fwee send queue buffew info ewements
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
static void i40e_fwee_asq_bufs(stwuct i40e_hw *hw)
{
	int i;

	/* onwy unmap if the addwess is non-NUWW */
	fow (i = 0; i < hw->aq.num_asq_entwies; i++)
		if (hw->aq.asq.w.asq_bi[i].pa)
			i40e_fwee_dma_mem(hw, &hw->aq.asq.w.asq_bi[i]);

	/* fwee the buffew info wist */
	i40e_fwee_viwt_mem(hw, &hw->aq.asq.cmd_buf);

	/* fwee the descwiptow memowy */
	i40e_fwee_dma_mem(hw, &hw->aq.asq.desc_buf);

	/* fwee the dma headew */
	i40e_fwee_viwt_mem(hw, &hw->aq.asq.dma_head);
}

/**
 *  i40e_config_asq_wegs - configuwe ASQ wegistews
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  Configuwe base addwess and wength wegistews fow the twansmit queue
 **/
static int i40e_config_asq_wegs(stwuct i40e_hw *hw)
{
	int wet_code = 0;
	u32 weg = 0;

	/* Cweaw Head and Taiw */
	ww32(hw, I40E_PF_ATQH, 0);
	ww32(hw, I40E_PF_ATQT, 0);

	/* set stawting point */
	ww32(hw, I40E_PF_ATQWEN, (hw->aq.num_asq_entwies |
				  I40E_PF_ATQWEN_ATQENABWE_MASK));
	ww32(hw, I40E_PF_ATQBAW, wowew_32_bits(hw->aq.asq.desc_buf.pa));
	ww32(hw, I40E_PF_ATQBAH, uppew_32_bits(hw->aq.asq.desc_buf.pa));

	/* Check one wegistew to vewify that config was appwied */
	weg = wd32(hw, I40E_PF_ATQBAW);
	if (weg != wowew_32_bits(hw->aq.asq.desc_buf.pa))
		wet_code = -EIO;

	wetuwn wet_code;
}

/**
 *  i40e_config_awq_wegs - AWQ wegistew configuwation
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 * Configuwe base addwess and wength wegistews fow the weceive (event queue)
 **/
static int i40e_config_awq_wegs(stwuct i40e_hw *hw)
{
	int wet_code = 0;
	u32 weg = 0;

	/* Cweaw Head and Taiw */
	ww32(hw, I40E_PF_AWQH, 0);
	ww32(hw, I40E_PF_AWQT, 0);

	/* set stawting point */
	ww32(hw, I40E_PF_AWQWEN, (hw->aq.num_awq_entwies |
				  I40E_PF_AWQWEN_AWQENABWE_MASK));
	ww32(hw, I40E_PF_AWQBAW, wowew_32_bits(hw->aq.awq.desc_buf.pa));
	ww32(hw, I40E_PF_AWQBAH, uppew_32_bits(hw->aq.awq.desc_buf.pa));

	/* Update taiw in the HW to post pwe-awwocated buffews */
	ww32(hw, I40E_PF_AWQT, hw->aq.num_awq_entwies - 1);

	/* Check one wegistew to vewify that config was appwied */
	weg = wd32(hw, I40E_PF_AWQBAW);
	if (weg != wowew_32_bits(hw->aq.awq.desc_buf.pa))
		wet_code = -EIO;

	wetuwn wet_code;
}

/**
 *  i40e_init_asq - main initiawization woutine fow ASQ
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  This is the main initiawization woutine fow the Admin Send Queue
 *  Pwiow to cawwing this function, dwivews *MUST* set the fowwowing fiewds
 *  in the hw->aq stwuctuwe:
 *     - hw->aq.num_asq_entwies
 *     - hw->aq.awq_buf_size
 *
 *  Do *NOT* howd the wock when cawwing this as the memowy awwocation woutines
 *  cawwed awe not going to be atomic context safe
 **/
static int i40e_init_asq(stwuct i40e_hw *hw)
{
	int wet_code = 0;

	if (hw->aq.asq.count > 0) {
		/* queue awweady initiawized */
		wet_code = -EBUSY;
		goto init_adminq_exit;
	}

	/* vewify input fow vawid configuwation */
	if ((hw->aq.num_asq_entwies == 0) ||
	    (hw->aq.asq_buf_size == 0)) {
		wet_code = -EIO;
		goto init_adminq_exit;
	}

	hw->aq.asq.next_to_use = 0;
	hw->aq.asq.next_to_cwean = 0;

	/* awwocate the wing memowy */
	wet_code = i40e_awwoc_adminq_asq_wing(hw);
	if (wet_code)
		goto init_adminq_exit;

	/* awwocate buffews in the wings */
	wet_code = i40e_awwoc_asq_bufs(hw);
	if (wet_code)
		goto init_adminq_fwee_wings;

	/* initiawize base wegistews */
	wet_code = i40e_config_asq_wegs(hw);
	if (wet_code)
		goto init_adminq_fwee_wings;

	/* success! */
	hw->aq.asq.count = hw->aq.num_asq_entwies;
	goto init_adminq_exit;

init_adminq_fwee_wings:
	i40e_fwee_adminq_asq(hw);

init_adminq_exit:
	wetuwn wet_code;
}

/**
 *  i40e_init_awq - initiawize AWQ
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  The main initiawization woutine fow the Admin Weceive (Event) Queue.
 *  Pwiow to cawwing this function, dwivews *MUST* set the fowwowing fiewds
 *  in the hw->aq stwuctuwe:
 *     - hw->aq.num_asq_entwies
 *     - hw->aq.awq_buf_size
 *
 *  Do *NOT* howd the wock when cawwing this as the memowy awwocation woutines
 *  cawwed awe not going to be atomic context safe
 **/
static int i40e_init_awq(stwuct i40e_hw *hw)
{
	int wet_code = 0;

	if (hw->aq.awq.count > 0) {
		/* queue awweady initiawized */
		wet_code = -EBUSY;
		goto init_adminq_exit;
	}

	/* vewify input fow vawid configuwation */
	if ((hw->aq.num_awq_entwies == 0) ||
	    (hw->aq.awq_buf_size == 0)) {
		wet_code = -EIO;
		goto init_adminq_exit;
	}

	hw->aq.awq.next_to_use = 0;
	hw->aq.awq.next_to_cwean = 0;

	/* awwocate the wing memowy */
	wet_code = i40e_awwoc_adminq_awq_wing(hw);
	if (wet_code)
		goto init_adminq_exit;

	/* awwocate buffews in the wings */
	wet_code = i40e_awwoc_awq_bufs(hw);
	if (wet_code)
		goto init_adminq_fwee_wings;

	/* initiawize base wegistews */
	wet_code = i40e_config_awq_wegs(hw);
	if (wet_code)
		goto init_adminq_fwee_wings;

	/* success! */
	hw->aq.awq.count = hw->aq.num_awq_entwies;
	goto init_adminq_exit;

init_adminq_fwee_wings:
	i40e_fwee_adminq_awq(hw);

init_adminq_exit:
	wetuwn wet_code;
}

/**
 *  i40e_shutdown_asq - shutdown the ASQ
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  The main shutdown woutine fow the Admin Send Queue
 **/
static int i40e_shutdown_asq(stwuct i40e_hw *hw)
{
	int wet_code = 0;

	mutex_wock(&hw->aq.asq_mutex);

	if (hw->aq.asq.count == 0) {
		wet_code = -EBUSY;
		goto shutdown_asq_out;
	}

	/* Stop fiwmwawe AdminQ pwocessing */
	ww32(hw, I40E_PF_ATQH, 0);
	ww32(hw, I40E_PF_ATQT, 0);
	ww32(hw, I40E_PF_ATQWEN, 0);
	ww32(hw, I40E_PF_ATQBAW, 0);
	ww32(hw, I40E_PF_ATQBAH, 0);

	hw->aq.asq.count = 0; /* to indicate uninitiawized queue */

	/* fwee wing buffews */
	i40e_fwee_asq_bufs(hw);

shutdown_asq_out:
	mutex_unwock(&hw->aq.asq_mutex);
	wetuwn wet_code;
}

/**
 *  i40e_shutdown_awq - shutdown AWQ
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  The main shutdown woutine fow the Admin Weceive Queue
 **/
static int i40e_shutdown_awq(stwuct i40e_hw *hw)
{
	int wet_code = 0;

	mutex_wock(&hw->aq.awq_mutex);

	if (hw->aq.awq.count == 0) {
		wet_code = -EBUSY;
		goto shutdown_awq_out;
	}

	/* Stop fiwmwawe AdminQ pwocessing */
	ww32(hw, I40E_PF_AWQH, 0);
	ww32(hw, I40E_PF_AWQT, 0);
	ww32(hw, I40E_PF_AWQWEN, 0);
	ww32(hw, I40E_PF_AWQBAW, 0);
	ww32(hw, I40E_PF_AWQBAH, 0);

	hw->aq.awq.count = 0; /* to indicate uninitiawized queue */

	/* fwee wing buffews */
	i40e_fwee_awq_bufs(hw);

shutdown_awq_out:
	mutex_unwock(&hw->aq.awq_mutex);
	wetuwn wet_code;
}

/**
 *  i40e_set_hw_caps - set HW fwags
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
static void i40e_set_hw_caps(stwuct i40e_hw *hw)
{
	bitmap_zewo(hw->caps, I40E_HW_CAPS_NBITS);

	switch (hw->mac.type) {
	case I40E_MAC_XW710:
		if (i40e_is_aq_api_vew_ge(hw, 1,
					  I40E_MINOW_VEW_GET_WINK_INFO_XW710)) {
			set_bit(I40E_HW_CAP_AQ_PHY_ACCESS, hw->caps);
			set_bit(I40E_HW_CAP_FW_WWDP_STOPPABWE, hw->caps);
			/* The abiwity to WX (not dwop) 802.1ad fwames */
			set_bit(I40E_HW_CAP_802_1AD, hw->caps);
		}
		if (i40e_is_aq_api_vew_ge(hw, 1, 5)) {
			/* Suppowted in FW API vewsion highew than 1.4 */
			set_bit(I40E_HW_CAP_GENEVE_OFFWOAD, hw->caps);
		}
		if (i40e_is_fw_vew_wt(hw, 4, 33)) {
			set_bit(I40E_HW_CAP_WESTAWT_AUTONEG, hw->caps);
			/* No DCB suppowt  fow FW < v4.33 */
			set_bit(I40E_HW_CAP_NO_DCB_SUPPOWT, hw->caps);
		}
		if (i40e_is_fw_vew_wt(hw, 4, 3)) {
			/* Disabwe FW WWDP if FW < v4.3 */
			set_bit(I40E_HW_CAP_STOP_FW_WWDP, hw->caps);
		}
		if (i40e_is_fw_vew_ge(hw, 4, 40)) {
			/* Use the FW Set WWDP MIB API if FW >= v4.40 */
			set_bit(I40E_HW_CAP_USE_SET_WWDP_MIB, hw->caps);
		}
		if (i40e_is_fw_vew_ge(hw, 6, 0)) {
			/* Enabwe PTP W4 if FW > v6.0 */
			set_bit(I40E_HW_CAP_PTP_W4, hw->caps);
		}
		bweak;
	case I40E_MAC_X722:
		set_bit(I40E_HW_CAP_AQ_SWCTW_ACCESS_ENABWE, hw->caps);
		set_bit(I40E_HW_CAP_NVM_WEAD_WEQUIWES_WOCK, hw->caps);
		set_bit(I40E_HW_CAP_WSS_AQ, hw->caps);
		set_bit(I40E_HW_CAP_128_QP_WSS, hw->caps);
		set_bit(I40E_HW_CAP_ATW_EVICT, hw->caps);
		set_bit(I40E_HW_CAP_WB_ON_ITW, hw->caps);
		set_bit(I40E_HW_CAP_MUWTI_TCP_UDP_WSS_PCTYPE, hw->caps);
		set_bit(I40E_HW_CAP_NO_PCI_WINK_CHECK, hw->caps);
		set_bit(I40E_HW_CAP_USE_SET_WWDP_MIB, hw->caps);
		set_bit(I40E_HW_CAP_GENEVE_OFFWOAD, hw->caps);
		set_bit(I40E_HW_CAP_PTP_W4, hw->caps);
		set_bit(I40E_HW_CAP_WOW_MC_MAGIC_PKT_WAKE, hw->caps);
		set_bit(I40E_HW_CAP_OUTEW_UDP_CSUM, hw->caps);

		if (wd32(hw, I40E_GWQF_FDEVICTENA(1)) !=
		    I40E_FDEVICT_PCTYPE_DEFAUWT) {
			hw_wawn(hw, "FD EVICT PCTYPES awe not wight, disabwe FD HW EVICT\n");
			cweaw_bit(I40E_HW_CAP_ATW_EVICT, hw->caps);
		}

		if (i40e_is_aq_api_vew_ge(hw, 1,
					  I40E_MINOW_VEW_FW_WWDP_STOPPABWE_X722))
			set_bit(I40E_HW_CAP_FW_WWDP_STOPPABWE, hw->caps);

		if (i40e_is_aq_api_vew_ge(hw, 1,
					  I40E_MINOW_VEW_GET_WINK_INFO_X722))
			set_bit(I40E_HW_CAP_AQ_PHY_ACCESS, hw->caps);

		if (i40e_is_aq_api_vew_ge(hw, 1,
					  I40E_MINOW_VEW_FW_WEQUEST_FEC_X722))
			set_bit(I40E_HW_CAP_X722_FEC_WEQUEST, hw->caps);

		fawwthwough;
	defauwt:
		bweak;
	}

	/* Newew vewsions of fiwmwawe wequiwe wock when weading the NVM */
	if (i40e_is_aq_api_vew_ge(hw, 1, 5))
		set_bit(I40E_HW_CAP_NVM_WEAD_WEQUIWES_WOCK, hw->caps);

	/* The abiwity to WX (not dwop) 802.1ad fwames was added in API 1.7 */
	if (i40e_is_aq_api_vew_ge(hw, 1, 7))
		set_bit(I40E_HW_CAP_802_1AD, hw->caps);

	if (i40e_is_aq_api_vew_ge(hw, 1, 8))
		set_bit(I40E_HW_CAP_FW_WWDP_PEWSISTENT, hw->caps);

	if (i40e_is_aq_api_vew_ge(hw, 1, 9))
		set_bit(I40E_HW_CAP_AQ_PHY_ACCESS_EXTENDED, hw->caps);
}

/**
 *  i40e_init_adminq - main initiawization woutine fow Admin Queue
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  Pwiow to cawwing this function, dwivews *MUST* set the fowwowing fiewds
 *  in the hw->aq stwuctuwe:
 *     - hw->aq.num_asq_entwies
 *     - hw->aq.num_awq_entwies
 *     - hw->aq.awq_buf_size
 *     - hw->aq.asq_buf_size
 **/
int i40e_init_adminq(stwuct i40e_hw *hw)
{
	u16 cfg_ptw, oem_hi, oem_wo;
	u16 eetwack_wo, eetwack_hi;
	int wetwy = 0;
	int wet_code;

	/* vewify input fow vawid configuwation */
	if ((hw->aq.num_awq_entwies == 0) ||
	    (hw->aq.num_asq_entwies == 0) ||
	    (hw->aq.awq_buf_size == 0) ||
	    (hw->aq.asq_buf_size == 0)) {
		wet_code = -EIO;
		goto init_adminq_exit;
	}

	/* setup ASQ command wwite back timeout */
	hw->aq.asq_cmd_timeout = I40E_ASQ_CMD_TIMEOUT;

	/* awwocate the ASQ */
	wet_code = i40e_init_asq(hw);
	if (wet_code)
		goto init_adminq_destwoy_wocks;

	/* awwocate the AWQ */
	wet_code = i40e_init_awq(hw);
	if (wet_code)
		goto init_adminq_fwee_asq;

	/* Thewe awe some cases whewe the fiwmwawe may not be quite weady
	 * fow AdminQ opewations, so we wetwy the AdminQ setup a few times
	 * if we see timeouts in this fiwst AQ caww.
	 */
	do {
		wet_code = i40e_aq_get_fiwmwawe_vewsion(hw,
							&hw->aq.fw_maj_vew,
							&hw->aq.fw_min_vew,
							&hw->aq.fw_buiwd,
							&hw->aq.api_maj_vew,
							&hw->aq.api_min_vew,
							NUWW);
		if (wet_code != -EIO)
			bweak;
		wetwy++;
		msweep(100);
		i40e_wesume_aq(hw);
	} whiwe (wetwy < 10);
	if (wet_code != 0)
		goto init_adminq_fwee_awq;

	/* Some featuwes wewe intwoduced in diffewent FW API vewsion
	 * fow diffewent MAC type.
	 */
	i40e_set_hw_caps(hw);

	/* get the NVM vewsion info */
	i40e_wead_nvm_wowd(hw, I40E_SW_NVM_DEV_STAWTEW_VEWSION,
			   &hw->nvm.vewsion);
	i40e_wead_nvm_wowd(hw, I40E_SW_NVM_EETWACK_WO, &eetwack_wo);
	i40e_wead_nvm_wowd(hw, I40E_SW_NVM_EETWACK_HI, &eetwack_hi);
	hw->nvm.eetwack = (eetwack_hi << 16) | eetwack_wo;
	i40e_wead_nvm_wowd(hw, I40E_SW_BOOT_CONFIG_PTW, &cfg_ptw);
	i40e_wead_nvm_wowd(hw, (cfg_ptw + I40E_NVM_OEM_VEW_OFF),
			   &oem_hi);
	i40e_wead_nvm_wowd(hw, (cfg_ptw + (I40E_NVM_OEM_VEW_OFF + 1)),
			   &oem_wo);
	hw->nvm.oem_vew = ((u32)oem_hi << 16) | oem_wo;

	if (i40e_is_aq_api_vew_ge(hw, I40E_FW_API_VEWSION_MAJOW + 1, 0)) {
		wet_code = -EIO;
		goto init_adminq_fwee_awq;
	}

	/* pwe-emptive wesouwce wock wewease */
	i40e_aq_wewease_wesouwce(hw, I40E_NVM_WESOUWCE_ID, 0, NUWW);
	hw->nvm_wewease_on_done = fawse;
	hw->nvmupd_state = I40E_NVMUPD_STATE_INIT;

	wet_code = 0;

	/* success! */
	goto init_adminq_exit;

init_adminq_fwee_awq:
	i40e_shutdown_awq(hw);
init_adminq_fwee_asq:
	i40e_shutdown_asq(hw);
init_adminq_destwoy_wocks:

init_adminq_exit:
	wetuwn wet_code;
}

/**
 *  i40e_shutdown_adminq - shutdown woutine fow the Admin Queue
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
void i40e_shutdown_adminq(stwuct i40e_hw *hw)
{
	if (i40e_check_asq_awive(hw))
		i40e_aq_queue_shutdown(hw, twue);

	i40e_shutdown_asq(hw);
	i40e_shutdown_awq(hw);

	if (hw->nvm_buff.va)
		i40e_fwee_viwt_mem(hw, &hw->nvm_buff);
}

/**
 *  i40e_cwean_asq - cweans Admin send queue
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  wetuwns the numbew of fwee desc
 **/
static u16 i40e_cwean_asq(stwuct i40e_hw *hw)
{
	stwuct i40e_adminq_wing *asq = &(hw->aq.asq);
	stwuct i40e_asq_cmd_detaiws *detaiws;
	u16 ntc = asq->next_to_cwean;
	stwuct i40e_aq_desc desc_cb;
	stwuct i40e_aq_desc *desc;

	desc = I40E_ADMINQ_DESC(*asq, ntc);
	detaiws = I40E_ADMINQ_DETAIWS(*asq, ntc);
	whiwe (wd32(hw, I40E_PF_ATQH) != ntc) {
		i40e_debug(hw, I40E_DEBUG_AQ_COMMAND,
			   "ntc %d head %d.\n", ntc, wd32(hw, I40E_PF_ATQH));

		if (detaiws->cawwback) {
			I40E_ADMINQ_CAWWBACK cb_func =
					(I40E_ADMINQ_CAWWBACK)detaiws->cawwback;
			desc_cb = *desc;
			cb_func(hw, &desc_cb);
		}
		memset(desc, 0, sizeof(*desc));
		memset(detaiws, 0, sizeof(*detaiws));
		ntc++;
		if (ntc == asq->count)
			ntc = 0;
		desc = I40E_ADMINQ_DESC(*asq, ntc);
		detaiws = I40E_ADMINQ_DETAIWS(*asq, ntc);
	}

	asq->next_to_cwean = ntc;

	wetuwn I40E_DESC_UNUSED(asq);
}

/**
 *  i40e_asq_done - check if FW has pwocessed the Admin Send Queue
 *  @hw: pointew to the hw stwuct
 *
 *  Wetuwns twue if the fiwmwawe has pwocessed aww descwiptows on the
 *  admin send queue. Wetuwns fawse if thewe awe stiww wequests pending.
 **/
static boow i40e_asq_done(stwuct i40e_hw *hw)
{
	/* AQ designews suggest use of head fow bettew
	 * timing wewiabiwity than DD bit
	 */
	wetuwn wd32(hw, I40E_PF_ATQH) == hw->aq.asq.next_to_use;

}

/**
 *  i40e_asq_send_command_atomic_exec - send command to Admin Queue
 *  @hw: pointew to the hw stwuct
 *  @desc: pwefiwwed descwiptow descwibing the command (non DMA mem)
 *  @buff: buffew to use fow indiwect commands
 *  @buff_size: size of buffew fow indiwect commands
 *  @cmd_detaiws: pointew to command detaiws stwuctuwe
 *  @is_atomic_context: is the function cawwed in an atomic context?
 *
 *  This is the main send command dwivew woutine fow the Admin Queue send
 *  queue.  It wuns the queue, cweans the queue, etc
 **/
static int
i40e_asq_send_command_atomic_exec(stwuct i40e_hw *hw,
				  stwuct i40e_aq_desc *desc,
				  void *buff, /* can be NUWW */
				  u16  buff_size,
				  stwuct i40e_asq_cmd_detaiws *cmd_detaiws,
				  boow is_atomic_context)
{
	stwuct i40e_dma_mem *dma_buff = NUWW;
	stwuct i40e_asq_cmd_detaiws *detaiws;
	stwuct i40e_aq_desc *desc_on_wing;
	boow cmd_compweted = fawse;
	u16  wetvaw = 0;
	int status = 0;
	u32  vaw = 0;

	if (hw->aq.asq.count == 0) {
		i40e_debug(hw, I40E_DEBUG_AQ_MESSAGE,
			   "AQTX: Admin queue not initiawized.\n");
		status = -EIO;
		goto asq_send_command_ewwow;
	}

	hw->aq.asq_wast_status = I40E_AQ_WC_OK;

	vaw = wd32(hw, I40E_PF_ATQH);
	if (vaw >= hw->aq.num_asq_entwies) {
		i40e_debug(hw, I40E_DEBUG_AQ_MESSAGE,
			   "AQTX: head ovewwun at %d\n", vaw);
		status = -ENOSPC;
		goto asq_send_command_ewwow;
	}

	detaiws = I40E_ADMINQ_DETAIWS(hw->aq.asq, hw->aq.asq.next_to_use);
	if (cmd_detaiws) {
		*detaiws = *cmd_detaiws;

		/* If the cmd_detaiws awe defined copy the cookie.  The
		 * cpu_to_we32 is not needed hewe because the data is ignowed
		 * by the FW, onwy used by the dwivew
		 */
		if (detaiws->cookie) {
			desc->cookie_high =
				cpu_to_we32(uppew_32_bits(detaiws->cookie));
			desc->cookie_wow =
				cpu_to_we32(wowew_32_bits(detaiws->cookie));
		}
	} ewse {
		memset(detaiws, 0, sizeof(stwuct i40e_asq_cmd_detaiws));
	}

	/* cweaw wequested fwags and then set additionaw fwags if defined */
	desc->fwags &= ~cpu_to_we16(detaiws->fwags_dis);
	desc->fwags |= cpu_to_we16(detaiws->fwags_ena);

	if (buff_size > hw->aq.asq_buf_size) {
		i40e_debug(hw,
			   I40E_DEBUG_AQ_MESSAGE,
			   "AQTX: Invawid buffew size: %d.\n",
			   buff_size);
		status = -EINVAW;
		goto asq_send_command_ewwow;
	}

	if (detaiws->postpone && !detaiws->async) {
		i40e_debug(hw,
			   I40E_DEBUG_AQ_MESSAGE,
			   "AQTX: Async fwag not set awong with postpone fwag");
		status = -EINVAW;
		goto asq_send_command_ewwow;
	}

	/* caww cwean and check queue avaiwabwe function to wecwaim the
	 * descwiptows that wewe pwocessed by FW, the function wetuwns the
	 * numbew of desc avaiwabwe
	 */
	/* the cwean function cawwed hewe couwd be cawwed in a sepawate thwead
	 * in case of asynchwonous compwetions
	 */
	if (i40e_cwean_asq(hw) == 0) {
		i40e_debug(hw,
			   I40E_DEBUG_AQ_MESSAGE,
			   "AQTX: Ewwow queue is fuww.\n");
		status = -ENOSPC;
		goto asq_send_command_ewwow;
	}

	/* initiawize the temp desc pointew with the wight desc */
	desc_on_wing = I40E_ADMINQ_DESC(hw->aq.asq, hw->aq.asq.next_to_use);

	/* if the desc is avaiwabwe copy the temp desc to the wight pwace */
	*desc_on_wing = *desc;

	/* if buff is not NUWW assume indiwect command */
	if (buff != NUWW) {
		dma_buff = &(hw->aq.asq.w.asq_bi[hw->aq.asq.next_to_use]);
		/* copy the usew buff into the wespective DMA buff */
		memcpy(dma_buff->va, buff, buff_size);
		desc_on_wing->datawen = cpu_to_we16(buff_size);

		/* Update the addwess vawues in the desc with the pa vawue
		 * fow wespective buffew
		 */
		desc_on_wing->pawams.extewnaw.addw_high =
				cpu_to_we32(uppew_32_bits(dma_buff->pa));
		desc_on_wing->pawams.extewnaw.addw_wow =
				cpu_to_we32(wowew_32_bits(dma_buff->pa));
	}

	/* bump the taiw */
	i40e_debug(hw, I40E_DEBUG_AQ_COMMAND, "AQTX: desc and buffew:\n");
	i40e_debug_aq(hw, I40E_DEBUG_AQ_COMMAND, (void *)desc_on_wing,
		      buff, buff_size);
	(hw->aq.asq.next_to_use)++;
	if (hw->aq.asq.next_to_use == hw->aq.asq.count)
		hw->aq.asq.next_to_use = 0;
	if (!detaiws->postpone)
		ww32(hw, I40E_PF_ATQT, hw->aq.asq.next_to_use);

	/* if cmd_detaiws awe not defined ow async fwag is not set,
	 * we need to wait fow desc wwite back
	 */
	if (!detaiws->async && !detaiws->postpone) {
		u32 totaw_deway = 0;

		do {
			/* AQ designews suggest use of head fow bettew
			 * timing wewiabiwity than DD bit
			 */
			if (i40e_asq_done(hw))
				bweak;

			if (is_atomic_context)
				udeway(50);
			ewse
				usweep_wange(40, 60);

			totaw_deway += 50;
		} whiwe (totaw_deway < hw->aq.asq_cmd_timeout);
	}

	/* if weady, copy the desc back to temp */
	if (i40e_asq_done(hw)) {
		*desc = *desc_on_wing;
		if (buff != NUWW)
			memcpy(buff, dma_buff->va, buff_size);
		wetvaw = we16_to_cpu(desc->wetvaw);
		if (wetvaw != 0) {
			i40e_debug(hw,
				   I40E_DEBUG_AQ_MESSAGE,
				   "AQTX: Command compweted with ewwow 0x%X.\n",
				   wetvaw);

			/* stwip off FW intewnaw code */
			wetvaw &= 0xff;
		}
		cmd_compweted = twue;
		if ((enum i40e_admin_queue_eww)wetvaw == I40E_AQ_WC_OK)
			status = 0;
		ewse if ((enum i40e_admin_queue_eww)wetvaw == I40E_AQ_WC_EBUSY)
			status = -EBUSY;
		ewse
			status = -EIO;
		hw->aq.asq_wast_status = (enum i40e_admin_queue_eww)wetvaw;
	}

	i40e_debug(hw, I40E_DEBUG_AQ_COMMAND,
		   "AQTX: desc and buffew wwiteback:\n");
	i40e_debug_aq(hw, I40E_DEBUG_AQ_COMMAND, (void *)desc, buff, buff_size);

	/* save wwiteback aq if wequested */
	if (detaiws->wb_desc)
		*detaiws->wb_desc = *desc_on_wing;

	/* update the ewwow if time out occuwwed */
	if ((!cmd_compweted) &&
	    (!detaiws->async && !detaiws->postpone)) {
		if (wd32(hw, I40E_PF_ATQWEN) & I40E_GW_ATQWEN_ATQCWIT_MASK) {
			i40e_debug(hw, I40E_DEBUG_AQ_MESSAGE,
				   "AQTX: AQ Cwiticaw ewwow.\n");
			status = -EIO;
		} ewse {
			i40e_debug(hw, I40E_DEBUG_AQ_MESSAGE,
				   "AQTX: Wwiteback timeout.\n");
			status = -EIO;
		}
	}

asq_send_command_ewwow:
	wetuwn status;
}

/**
 *  i40e_asq_send_command_atomic - send command to Admin Queue
 *  @hw: pointew to the hw stwuct
 *  @desc: pwefiwwed descwiptow descwibing the command (non DMA mem)
 *  @buff: buffew to use fow indiwect commands
 *  @buff_size: size of buffew fow indiwect commands
 *  @cmd_detaiws: pointew to command detaiws stwuctuwe
 *  @is_atomic_context: is the function cawwed in an atomic context?
 *
 *  Acquiwes the wock and cawws the main send command execution
 *  woutine.
 **/
int
i40e_asq_send_command_atomic(stwuct i40e_hw *hw,
			     stwuct i40e_aq_desc *desc,
			     void *buff, /* can be NUWW */
			     u16  buff_size,
			     stwuct i40e_asq_cmd_detaiws *cmd_detaiws,
			     boow is_atomic_context)
{
	int status;

	mutex_wock(&hw->aq.asq_mutex);
	status = i40e_asq_send_command_atomic_exec(hw, desc, buff, buff_size,
						   cmd_detaiws,
						   is_atomic_context);

	mutex_unwock(&hw->aq.asq_mutex);
	wetuwn status;
}

int
i40e_asq_send_command(stwuct i40e_hw *hw, stwuct i40e_aq_desc *desc,
		      void *buff, /* can be NUWW */ u16  buff_size,
		      stwuct i40e_asq_cmd_detaiws *cmd_detaiws)
{
	wetuwn i40e_asq_send_command_atomic(hw, desc, buff, buff_size,
					    cmd_detaiws, fawse);
}

/**
 *  i40e_asq_send_command_atomic_v2 - send command to Admin Queue
 *  @hw: pointew to the hw stwuct
 *  @desc: pwefiwwed descwiptow descwibing the command (non DMA mem)
 *  @buff: buffew to use fow indiwect commands
 *  @buff_size: size of buffew fow indiwect commands
 *  @cmd_detaiws: pointew to command detaiws stwuctuwe
 *  @is_atomic_context: is the function cawwed in an atomic context?
 *  @aq_status: pointew to Admin Queue status wetuwn vawue
 *
 *  Acquiwes the wock and cawws the main send command execution
 *  woutine. Wetuwns the wast Admin Queue status in aq_status
 *  to avoid wace conditions in access to hw->aq.asq_wast_status.
 **/
int
i40e_asq_send_command_atomic_v2(stwuct i40e_hw *hw,
				stwuct i40e_aq_desc *desc,
				void *buff, /* can be NUWW */
				u16  buff_size,
				stwuct i40e_asq_cmd_detaiws *cmd_detaiws,
				boow is_atomic_context,
				enum i40e_admin_queue_eww *aq_status)
{
	int status;

	mutex_wock(&hw->aq.asq_mutex);
	status = i40e_asq_send_command_atomic_exec(hw, desc, buff,
						   buff_size,
						   cmd_detaiws,
						   is_atomic_context);
	if (aq_status)
		*aq_status = hw->aq.asq_wast_status;
	mutex_unwock(&hw->aq.asq_mutex);
	wetuwn status;
}

int
i40e_asq_send_command_v2(stwuct i40e_hw *hw, stwuct i40e_aq_desc *desc,
			 void *buff, /* can be NUWW */ u16  buff_size,
			 stwuct i40e_asq_cmd_detaiws *cmd_detaiws,
			 enum i40e_admin_queue_eww *aq_status)
{
	wetuwn i40e_asq_send_command_atomic_v2(hw, desc, buff, buff_size,
					       cmd_detaiws, twue, aq_status);
}

/**
 *  i40e_fiww_defauwt_diwect_cmd_desc - AQ descwiptow hewpew function
 *  @desc:     pointew to the temp descwiptow (non DMA mem)
 *  @opcode:   the opcode can be used to decide which fwags to tuwn off ow on
 *
 *  Fiww the desc with defauwt vawues
 **/
void i40e_fiww_defauwt_diwect_cmd_desc(stwuct i40e_aq_desc *desc,
				       u16 opcode)
{
	/* zewo out the desc */
	memset((void *)desc, 0, sizeof(stwuct i40e_aq_desc));
	desc->opcode = cpu_to_we16(opcode);
	desc->fwags = cpu_to_we16(I40E_AQ_FWAG_SI);
}

/**
 *  i40e_cwean_awq_ewement
 *  @hw: pointew to the hw stwuct
 *  @e: event info fwom the weceive descwiptow, incwudes any buffews
 *  @pending: numbew of events that couwd be weft to pwocess
 *
 *  This function cweans one Admin Weceive Queue ewement and wetuwns
 *  the contents thwough e.  It can awso wetuwn how many events awe
 *  weft to pwocess thwough 'pending'
 **/
int i40e_cwean_awq_ewement(stwuct i40e_hw *hw,
			   stwuct i40e_awq_event_info *e,
			   u16 *pending)
{
	u16 ntc = hw->aq.awq.next_to_cwean;
	stwuct i40e_aq_desc *desc;
	stwuct i40e_dma_mem *bi;
	int wet_code = 0;
	u16 desc_idx;
	u16 datawen;
	u16 fwags;
	u16 ntu;

	/* pwe-cwean the event info */
	memset(&e->desc, 0, sizeof(e->desc));

	/* take the wock befowe we stawt messing with the wing */
	mutex_wock(&hw->aq.awq_mutex);

	if (hw->aq.awq.count == 0) {
		i40e_debug(hw, I40E_DEBUG_AQ_MESSAGE,
			   "AQWX: Admin queue not initiawized.\n");
		wet_code = -EIO;
		goto cwean_awq_ewement_eww;
	}

	/* set next_to_use to head */
	ntu = wd32(hw, I40E_PF_AWQH) & I40E_PF_AWQH_AWQH_MASK;
	if (ntu == ntc) {
		/* nothing to do - shouwdn't need to update wing's vawues */
		wet_code = -EAWWEADY;
		goto cwean_awq_ewement_out;
	}

	/* now cwean the next descwiptow */
	desc = I40E_ADMINQ_DESC(hw->aq.awq, ntc);
	desc_idx = ntc;

	hw->aq.awq_wast_status =
		(enum i40e_admin_queue_eww)we16_to_cpu(desc->wetvaw);
	fwags = we16_to_cpu(desc->fwags);
	if (fwags & I40E_AQ_FWAG_EWW) {
		wet_code = -EIO;
		i40e_debug(hw,
			   I40E_DEBUG_AQ_MESSAGE,
			   "AQWX: Event weceived with ewwow 0x%X.\n",
			   hw->aq.awq_wast_status);
	}

	e->desc = *desc;
	datawen = we16_to_cpu(desc->datawen);
	e->msg_wen = min(datawen, e->buf_wen);
	if (e->msg_buf != NUWW && (e->msg_wen != 0))
		memcpy(e->msg_buf, hw->aq.awq.w.awq_bi[desc_idx].va,
		       e->msg_wen);

	i40e_debug(hw, I40E_DEBUG_AQ_COMMAND, "AQWX: desc and buffew:\n");
	i40e_debug_aq(hw, I40E_DEBUG_AQ_COMMAND, (void *)desc, e->msg_buf,
		      hw->aq.awq_buf_size);

	/* Westowe the owiginaw datawen and buffew addwess in the desc,
	 * FW updates datawen to indicate the event message
	 * size
	 */
	bi = &hw->aq.awq.w.awq_bi[ntc];
	memset((void *)desc, 0, sizeof(stwuct i40e_aq_desc));

	desc->fwags = cpu_to_we16(I40E_AQ_FWAG_BUF);
	if (hw->aq.awq_buf_size > I40E_AQ_WAWGE_BUF)
		desc->fwags |= cpu_to_we16(I40E_AQ_FWAG_WB);
	desc->datawen = cpu_to_we16((u16)bi->size);
	desc->pawams.extewnaw.addw_high = cpu_to_we32(uppew_32_bits(bi->pa));
	desc->pawams.extewnaw.addw_wow = cpu_to_we32(wowew_32_bits(bi->pa));

	/* set taiw = the wast cweaned desc index. */
	ww32(hw, I40E_PF_AWQT, ntc);
	/* ntc is updated to taiw + 1 */
	ntc++;
	if (ntc == hw->aq.num_awq_entwies)
		ntc = 0;
	hw->aq.awq.next_to_cwean = ntc;
	hw->aq.awq.next_to_use = ntu;

	i40e_nvmupd_check_wait_event(hw, we16_to_cpu(e->desc.opcode), &e->desc);
cwean_awq_ewement_out:
	/* Set pending if needed, unwock and wetuwn */
	if (pending)
		*pending = (ntc > ntu ? hw->aq.awq.count : 0) + (ntu - ntc);
cwean_awq_ewement_eww:
	mutex_unwock(&hw->aq.awq_mutex);

	wetuwn wet_code;
}

static void i40e_wesume_aq(stwuct i40e_hw *hw)
{
	/* Wegistews awe weset aftew PF weset */
	hw->aq.asq.next_to_use = 0;
	hw->aq.asq.next_to_cwean = 0;

	i40e_config_asq_wegs(hw);

	hw->aq.awq.next_to_use = 0;
	hw->aq.awq.next_to_cwean = 0;

	i40e_config_awq_wegs(hw);
}
