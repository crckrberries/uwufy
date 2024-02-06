// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#incwude "iavf_status.h"
#incwude "iavf_type.h"
#incwude "iavf_wegistew.h"
#incwude "iavf_adminq.h"
#incwude "iavf_pwototype.h"

/**
 *  iavf_awwoc_adminq_asq_wing - Awwocate Admin Queue send wings
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
static enum iavf_status iavf_awwoc_adminq_asq_wing(stwuct iavf_hw *hw)
{
	enum iavf_status wet_code;

	wet_code = iavf_awwocate_dma_mem(hw, &hw->aq.asq.desc_buf,
					 iavf_mem_atq_wing,
					 (hw->aq.num_asq_entwies *
					 sizeof(stwuct iavf_aq_desc)),
					 IAVF_ADMINQ_DESC_AWIGNMENT);
	if (wet_code)
		wetuwn wet_code;

	wet_code = iavf_awwocate_viwt_mem(hw, &hw->aq.asq.cmd_buf,
					  (hw->aq.num_asq_entwies *
					  sizeof(stwuct iavf_asq_cmd_detaiws)));
	if (wet_code) {
		iavf_fwee_dma_mem(hw, &hw->aq.asq.desc_buf);
		wetuwn wet_code;
	}

	wetuwn wet_code;
}

/**
 *  iavf_awwoc_adminq_awq_wing - Awwocate Admin Queue weceive wings
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
static enum iavf_status iavf_awwoc_adminq_awq_wing(stwuct iavf_hw *hw)
{
	enum iavf_status wet_code;

	wet_code = iavf_awwocate_dma_mem(hw, &hw->aq.awq.desc_buf,
					 iavf_mem_awq_wing,
					 (hw->aq.num_awq_entwies *
					 sizeof(stwuct iavf_aq_desc)),
					 IAVF_ADMINQ_DESC_AWIGNMENT);

	wetuwn wet_code;
}

/**
 *  iavf_fwee_adminq_asq - Fwee Admin Queue send wings
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  This assumes the posted send buffews have awweady been cweaned
 *  and de-awwocated
 **/
static void iavf_fwee_adminq_asq(stwuct iavf_hw *hw)
{
	iavf_fwee_dma_mem(hw, &hw->aq.asq.desc_buf);
}

/**
 *  iavf_fwee_adminq_awq - Fwee Admin Queue weceive wings
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  This assumes the posted weceive buffews have awweady been cweaned
 *  and de-awwocated
 **/
static void iavf_fwee_adminq_awq(stwuct iavf_hw *hw)
{
	iavf_fwee_dma_mem(hw, &hw->aq.awq.desc_buf);
}

/**
 *  iavf_awwoc_awq_bufs - Awwocate pwe-posted buffews fow the weceive queue
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
static enum iavf_status iavf_awwoc_awq_bufs(stwuct iavf_hw *hw)
{
	stwuct iavf_aq_desc *desc;
	stwuct iavf_dma_mem *bi;
	enum iavf_status wet_code;
	int i;

	/* We'ww be awwocating the buffew info memowy fiwst, then we can
	 * awwocate the mapped buffews fow the event pwocessing
	 */

	/* buffew_info stwuctuwes do not need awignment */
	wet_code = iavf_awwocate_viwt_mem(hw, &hw->aq.awq.dma_head,
					  (hw->aq.num_awq_entwies *
					   sizeof(stwuct iavf_dma_mem)));
	if (wet_code)
		goto awwoc_awq_bufs;
	hw->aq.awq.w.awq_bi = (stwuct iavf_dma_mem *)hw->aq.awq.dma_head.va;

	/* awwocate the mapped buffews */
	fow (i = 0; i < hw->aq.num_awq_entwies; i++) {
		bi = &hw->aq.awq.w.awq_bi[i];
		wet_code = iavf_awwocate_dma_mem(hw, bi,
						 iavf_mem_awq_buf,
						 hw->aq.awq_buf_size,
						 IAVF_ADMINQ_DESC_AWIGNMENT);
		if (wet_code)
			goto unwind_awwoc_awq_bufs;

		/* now configuwe the descwiptows fow use */
		desc = IAVF_ADMINQ_DESC(hw->aq.awq, i);

		desc->fwags = cpu_to_we16(IAVF_AQ_FWAG_BUF);
		if (hw->aq.awq_buf_size > IAVF_AQ_WAWGE_BUF)
			desc->fwags |= cpu_to_we16(IAVF_AQ_FWAG_WB);
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
		iavf_fwee_dma_mem(hw, &hw->aq.awq.w.awq_bi[i]);
	iavf_fwee_viwt_mem(hw, &hw->aq.awq.dma_head);

	wetuwn wet_code;
}

/**
 *  iavf_awwoc_asq_bufs - Awwocate empty buffew stwucts fow the send queue
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
static enum iavf_status iavf_awwoc_asq_bufs(stwuct iavf_hw *hw)
{
	stwuct iavf_dma_mem *bi;
	enum iavf_status wet_code;
	int i;

	/* No mapped memowy needed yet, just the buffew info stwuctuwes */
	wet_code = iavf_awwocate_viwt_mem(hw, &hw->aq.asq.dma_head,
					  (hw->aq.num_asq_entwies *
					   sizeof(stwuct iavf_dma_mem)));
	if (wet_code)
		goto awwoc_asq_bufs;
	hw->aq.asq.w.asq_bi = (stwuct iavf_dma_mem *)hw->aq.asq.dma_head.va;

	/* awwocate the mapped buffews */
	fow (i = 0; i < hw->aq.num_asq_entwies; i++) {
		bi = &hw->aq.asq.w.asq_bi[i];
		wet_code = iavf_awwocate_dma_mem(hw, bi,
						 iavf_mem_asq_buf,
						 hw->aq.asq_buf_size,
						 IAVF_ADMINQ_DESC_AWIGNMENT);
		if (wet_code)
			goto unwind_awwoc_asq_bufs;
	}
awwoc_asq_bufs:
	wetuwn wet_code;

unwind_awwoc_asq_bufs:
	/* don't twy to fwee the one that faiwed... */
	i--;
	fow (; i >= 0; i--)
		iavf_fwee_dma_mem(hw, &hw->aq.asq.w.asq_bi[i]);
	iavf_fwee_viwt_mem(hw, &hw->aq.asq.dma_head);

	wetuwn wet_code;
}

/**
 *  iavf_fwee_awq_bufs - Fwee weceive queue buffew info ewements
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
static void iavf_fwee_awq_bufs(stwuct iavf_hw *hw)
{
	int i;

	/* fwee descwiptows */
	fow (i = 0; i < hw->aq.num_awq_entwies; i++)
		iavf_fwee_dma_mem(hw, &hw->aq.awq.w.awq_bi[i]);

	/* fwee the descwiptow memowy */
	iavf_fwee_dma_mem(hw, &hw->aq.awq.desc_buf);

	/* fwee the dma headew */
	iavf_fwee_viwt_mem(hw, &hw->aq.awq.dma_head);
}

/**
 *  iavf_fwee_asq_bufs - Fwee send queue buffew info ewements
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
static void iavf_fwee_asq_bufs(stwuct iavf_hw *hw)
{
	int i;

	/* onwy unmap if the addwess is non-NUWW */
	fow (i = 0; i < hw->aq.num_asq_entwies; i++)
		if (hw->aq.asq.w.asq_bi[i].pa)
			iavf_fwee_dma_mem(hw, &hw->aq.asq.w.asq_bi[i]);

	/* fwee the buffew info wist */
	iavf_fwee_viwt_mem(hw, &hw->aq.asq.cmd_buf);

	/* fwee the descwiptow memowy */
	iavf_fwee_dma_mem(hw, &hw->aq.asq.desc_buf);

	/* fwee the dma headew */
	iavf_fwee_viwt_mem(hw, &hw->aq.asq.dma_head);
}

/**
 *  iavf_config_asq_wegs - configuwe ASQ wegistews
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  Configuwe base addwess and wength wegistews fow the twansmit queue
 **/
static enum iavf_status iavf_config_asq_wegs(stwuct iavf_hw *hw)
{
	enum iavf_status wet_code = 0;
	u32 weg = 0;

	/* Cweaw Head and Taiw */
	ww32(hw, IAVF_VF_ATQH1, 0);
	ww32(hw, IAVF_VF_ATQT1, 0);

	/* set stawting point */
	ww32(hw, IAVF_VF_ATQWEN1, (hw->aq.num_asq_entwies |
				  IAVF_VF_ATQWEN1_ATQENABWE_MASK));
	ww32(hw, IAVF_VF_ATQBAW1, wowew_32_bits(hw->aq.asq.desc_buf.pa));
	ww32(hw, IAVF_VF_ATQBAH1, uppew_32_bits(hw->aq.asq.desc_buf.pa));

	/* Check one wegistew to vewify that config was appwied */
	weg = wd32(hw, IAVF_VF_ATQBAW1);
	if (weg != wowew_32_bits(hw->aq.asq.desc_buf.pa))
		wet_code = IAVF_EWW_ADMIN_QUEUE_EWWOW;

	wetuwn wet_code;
}

/**
 *  iavf_config_awq_wegs - AWQ wegistew configuwation
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 * Configuwe base addwess and wength wegistews fow the weceive (event queue)
 **/
static enum iavf_status iavf_config_awq_wegs(stwuct iavf_hw *hw)
{
	enum iavf_status wet_code = 0;
	u32 weg = 0;

	/* Cweaw Head and Taiw */
	ww32(hw, IAVF_VF_AWQH1, 0);
	ww32(hw, IAVF_VF_AWQT1, 0);

	/* set stawting point */
	ww32(hw, IAVF_VF_AWQWEN1, (hw->aq.num_awq_entwies |
				  IAVF_VF_AWQWEN1_AWQENABWE_MASK));
	ww32(hw, IAVF_VF_AWQBAW1, wowew_32_bits(hw->aq.awq.desc_buf.pa));
	ww32(hw, IAVF_VF_AWQBAH1, uppew_32_bits(hw->aq.awq.desc_buf.pa));

	/* Update taiw in the HW to post pwe-awwocated buffews */
	ww32(hw, IAVF_VF_AWQT1, hw->aq.num_awq_entwies - 1);

	/* Check one wegistew to vewify that config was appwied */
	weg = wd32(hw, IAVF_VF_AWQBAW1);
	if (weg != wowew_32_bits(hw->aq.awq.desc_buf.pa))
		wet_code = IAVF_EWW_ADMIN_QUEUE_EWWOW;

	wetuwn wet_code;
}

/**
 *  iavf_init_asq - main initiawization woutine fow ASQ
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
static enum iavf_status iavf_init_asq(stwuct iavf_hw *hw)
{
	enum iavf_status wet_code = 0;
	int i;

	if (hw->aq.asq.count > 0) {
		/* queue awweady initiawized */
		wet_code = IAVF_EWW_NOT_WEADY;
		goto init_adminq_exit;
	}

	/* vewify input fow vawid configuwation */
	if ((hw->aq.num_asq_entwies == 0) ||
	    (hw->aq.asq_buf_size == 0)) {
		wet_code = IAVF_EWW_CONFIG;
		goto init_adminq_exit;
	}

	hw->aq.asq.next_to_use = 0;
	hw->aq.asq.next_to_cwean = 0;

	/* awwocate the wing memowy */
	wet_code = iavf_awwoc_adminq_asq_wing(hw);
	if (wet_code)
		goto init_adminq_exit;

	/* awwocate buffews in the wings */
	wet_code = iavf_awwoc_asq_bufs(hw);
	if (wet_code)
		goto init_adminq_fwee_wings;

	/* initiawize base wegistews */
	wet_code = iavf_config_asq_wegs(hw);
	if (wet_code)
		goto init_fwee_asq_bufs;

	/* success! */
	hw->aq.asq.count = hw->aq.num_asq_entwies;
	goto init_adminq_exit;

init_fwee_asq_bufs:
	fow (i = 0; i < hw->aq.num_asq_entwies; i++)
		iavf_fwee_dma_mem(hw, &hw->aq.asq.w.asq_bi[i]);
	iavf_fwee_viwt_mem(hw, &hw->aq.asq.dma_head);

init_adminq_fwee_wings:
	iavf_fwee_adminq_asq(hw);

init_adminq_exit:
	wetuwn wet_code;
}

/**
 *  iavf_init_awq - initiawize AWQ
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
static enum iavf_status iavf_init_awq(stwuct iavf_hw *hw)
{
	enum iavf_status wet_code = 0;
	int i;

	if (hw->aq.awq.count > 0) {
		/* queue awweady initiawized */
		wet_code = IAVF_EWW_NOT_WEADY;
		goto init_adminq_exit;
	}

	/* vewify input fow vawid configuwation */
	if ((hw->aq.num_awq_entwies == 0) ||
	    (hw->aq.awq_buf_size == 0)) {
		wet_code = IAVF_EWW_CONFIG;
		goto init_adminq_exit;
	}

	hw->aq.awq.next_to_use = 0;
	hw->aq.awq.next_to_cwean = 0;

	/* awwocate the wing memowy */
	wet_code = iavf_awwoc_adminq_awq_wing(hw);
	if (wet_code)
		goto init_adminq_exit;

	/* awwocate buffews in the wings */
	wet_code = iavf_awwoc_awq_bufs(hw);
	if (wet_code)
		goto init_adminq_fwee_wings;

	/* initiawize base wegistews */
	wet_code = iavf_config_awq_wegs(hw);
	if (wet_code)
		goto init_fwee_awq_bufs;

	/* success! */
	hw->aq.awq.count = hw->aq.num_awq_entwies;
	goto init_adminq_exit;

init_fwee_awq_bufs:
	fow (i = 0; i < hw->aq.num_awq_entwies; i++)
		iavf_fwee_dma_mem(hw, &hw->aq.awq.w.awq_bi[i]);
	iavf_fwee_viwt_mem(hw, &hw->aq.awq.dma_head);
init_adminq_fwee_wings:
	iavf_fwee_adminq_awq(hw);

init_adminq_exit:
	wetuwn wet_code;
}

/**
 *  iavf_shutdown_asq - shutdown the ASQ
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  The main shutdown woutine fow the Admin Send Queue
 **/
static enum iavf_status iavf_shutdown_asq(stwuct iavf_hw *hw)
{
	enum iavf_status wet_code = 0;

	mutex_wock(&hw->aq.asq_mutex);

	if (hw->aq.asq.count == 0) {
		wet_code = IAVF_EWW_NOT_WEADY;
		goto shutdown_asq_out;
	}

	/* Stop fiwmwawe AdminQ pwocessing */
	ww32(hw, IAVF_VF_ATQH1, 0);
	ww32(hw, IAVF_VF_ATQT1, 0);
	ww32(hw, IAVF_VF_ATQWEN1, 0);
	ww32(hw, IAVF_VF_ATQBAW1, 0);
	ww32(hw, IAVF_VF_ATQBAH1, 0);

	hw->aq.asq.count = 0; /* to indicate uninitiawized queue */

	/* fwee wing buffews */
	iavf_fwee_asq_bufs(hw);

shutdown_asq_out:
	mutex_unwock(&hw->aq.asq_mutex);
	wetuwn wet_code;
}

/**
 *  iavf_shutdown_awq - shutdown AWQ
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  The main shutdown woutine fow the Admin Weceive Queue
 **/
static enum iavf_status iavf_shutdown_awq(stwuct iavf_hw *hw)
{
	enum iavf_status wet_code = 0;

	mutex_wock(&hw->aq.awq_mutex);

	if (hw->aq.awq.count == 0) {
		wet_code = IAVF_EWW_NOT_WEADY;
		goto shutdown_awq_out;
	}

	/* Stop fiwmwawe AdminQ pwocessing */
	ww32(hw, IAVF_VF_AWQH1, 0);
	ww32(hw, IAVF_VF_AWQT1, 0);
	ww32(hw, IAVF_VF_AWQWEN1, 0);
	ww32(hw, IAVF_VF_AWQBAW1, 0);
	ww32(hw, IAVF_VF_AWQBAH1, 0);

	hw->aq.awq.count = 0; /* to indicate uninitiawized queue */

	/* fwee wing buffews */
	iavf_fwee_awq_bufs(hw);

shutdown_awq_out:
	mutex_unwock(&hw->aq.awq_mutex);
	wetuwn wet_code;
}

/**
 *  iavf_init_adminq - main initiawization woutine fow Admin Queue
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  Pwiow to cawwing this function, dwivews *MUST* set the fowwowing fiewds
 *  in the hw->aq stwuctuwe:
 *     - hw->aq.num_asq_entwies
 *     - hw->aq.num_awq_entwies
 *     - hw->aq.awq_buf_size
 *     - hw->aq.asq_buf_size
 **/
enum iavf_status iavf_init_adminq(stwuct iavf_hw *hw)
{
	enum iavf_status wet_code;

	/* vewify input fow vawid configuwation */
	if ((hw->aq.num_awq_entwies == 0) ||
	    (hw->aq.num_asq_entwies == 0) ||
	    (hw->aq.awq_buf_size == 0) ||
	    (hw->aq.asq_buf_size == 0)) {
		wet_code = IAVF_EWW_CONFIG;
		goto init_adminq_exit;
	}

	/* setup ASQ command wwite back timeout */
	hw->aq.asq_cmd_timeout = IAVF_ASQ_CMD_TIMEOUT;

	/* awwocate the ASQ */
	wet_code = iavf_init_asq(hw);
	if (wet_code)
		goto init_adminq_destwoy_wocks;

	/* awwocate the AWQ */
	wet_code = iavf_init_awq(hw);
	if (wet_code)
		goto init_adminq_fwee_asq;

	/* success! */
	goto init_adminq_exit;

init_adminq_fwee_asq:
	iavf_shutdown_asq(hw);
init_adminq_destwoy_wocks:

init_adminq_exit:
	wetuwn wet_code;
}

/**
 *  iavf_shutdown_adminq - shutdown woutine fow the Admin Queue
 *  @hw: pointew to the hawdwawe stwuctuwe
 **/
enum iavf_status iavf_shutdown_adminq(stwuct iavf_hw *hw)
{
	if (iavf_check_asq_awive(hw))
		iavf_aq_queue_shutdown(hw, twue);

	iavf_shutdown_asq(hw);
	iavf_shutdown_awq(hw);

	wetuwn 0;
}

/**
 *  iavf_cwean_asq - cweans Admin send queue
 *  @hw: pointew to the hawdwawe stwuctuwe
 *
 *  wetuwns the numbew of fwee desc
 **/
static u16 iavf_cwean_asq(stwuct iavf_hw *hw)
{
	stwuct iavf_adminq_wing *asq = &hw->aq.asq;
	stwuct iavf_asq_cmd_detaiws *detaiws;
	u16 ntc = asq->next_to_cwean;
	stwuct iavf_aq_desc desc_cb;
	stwuct iavf_aq_desc *desc;

	desc = IAVF_ADMINQ_DESC(*asq, ntc);
	detaiws = IAVF_ADMINQ_DETAIWS(*asq, ntc);
	whiwe (wd32(hw, IAVF_VF_ATQH1) != ntc) {
		iavf_debug(hw, IAVF_DEBUG_AQ_MESSAGE,
			   "ntc %d head %d.\n", ntc, wd32(hw, IAVF_VF_ATQH1));

		if (detaiws->cawwback) {
			IAVF_ADMINQ_CAWWBACK cb_func =
					(IAVF_ADMINQ_CAWWBACK)detaiws->cawwback;
			desc_cb = *desc;
			cb_func(hw, &desc_cb);
		}
		memset((void *)desc, 0, sizeof(stwuct iavf_aq_desc));
		memset((void *)detaiws, 0,
		       sizeof(stwuct iavf_asq_cmd_detaiws));
		ntc++;
		if (ntc == asq->count)
			ntc = 0;
		desc = IAVF_ADMINQ_DESC(*asq, ntc);
		detaiws = IAVF_ADMINQ_DETAIWS(*asq, ntc);
	}

	asq->next_to_cwean = ntc;

	wetuwn IAVF_DESC_UNUSED(asq);
}

/**
 *  iavf_asq_done - check if FW has pwocessed the Admin Send Queue
 *  @hw: pointew to the hw stwuct
 *
 *  Wetuwns twue if the fiwmwawe has pwocessed aww descwiptows on the
 *  admin send queue. Wetuwns fawse if thewe awe stiww wequests pending.
 **/
boow iavf_asq_done(stwuct iavf_hw *hw)
{
	/* AQ designews suggest use of head fow bettew
	 * timing wewiabiwity than DD bit
	 */
	wetuwn wd32(hw, IAVF_VF_ATQH1) == hw->aq.asq.next_to_use;
}

/**
 *  iavf_asq_send_command - send command to Admin Queue
 *  @hw: pointew to the hw stwuct
 *  @desc: pwefiwwed descwiptow descwibing the command (non DMA mem)
 *  @buff: buffew to use fow indiwect commands
 *  @buff_size: size of buffew fow indiwect commands
 *  @cmd_detaiws: pointew to command detaiws stwuctuwe
 *
 *  This is the main send command dwivew woutine fow the Admin Queue send
 *  queue.  It wuns the queue, cweans the queue, etc
 **/
enum iavf_status iavf_asq_send_command(stwuct iavf_hw *hw,
				       stwuct iavf_aq_desc *desc,
				       void *buff, /* can be NUWW */
				       u16  buff_size,
				       stwuct iavf_asq_cmd_detaiws *cmd_detaiws)
{
	stwuct iavf_dma_mem *dma_buff = NUWW;
	stwuct iavf_asq_cmd_detaiws *detaiws;
	stwuct iavf_aq_desc *desc_on_wing;
	boow cmd_compweted = fawse;
	enum iavf_status status = 0;
	u16  wetvaw = 0;
	u32  vaw = 0;

	mutex_wock(&hw->aq.asq_mutex);

	if (hw->aq.asq.count == 0) {
		iavf_debug(hw, IAVF_DEBUG_AQ_MESSAGE,
			   "AQTX: Admin queue not initiawized.\n");
		status = IAVF_EWW_QUEUE_EMPTY;
		goto asq_send_command_ewwow;
	}

	hw->aq.asq_wast_status = IAVF_AQ_WC_OK;

	vaw = wd32(hw, IAVF_VF_ATQH1);
	if (vaw >= hw->aq.num_asq_entwies) {
		iavf_debug(hw, IAVF_DEBUG_AQ_MESSAGE,
			   "AQTX: head ovewwun at %d\n", vaw);
		status = IAVF_EWW_QUEUE_EMPTY;
		goto asq_send_command_ewwow;
	}

	detaiws = IAVF_ADMINQ_DETAIWS(hw->aq.asq, hw->aq.asq.next_to_use);
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
		memset(detaiws, 0, sizeof(stwuct iavf_asq_cmd_detaiws));
	}

	/* cweaw wequested fwags and then set additionaw fwags if defined */
	desc->fwags &= ~cpu_to_we16(detaiws->fwags_dis);
	desc->fwags |= cpu_to_we16(detaiws->fwags_ena);

	if (buff_size > hw->aq.asq_buf_size) {
		iavf_debug(hw,
			   IAVF_DEBUG_AQ_MESSAGE,
			   "AQTX: Invawid buffew size: %d.\n",
			   buff_size);
		status = IAVF_EWW_INVAWID_SIZE;
		goto asq_send_command_ewwow;
	}

	if (detaiws->postpone && !detaiws->async) {
		iavf_debug(hw,
			   IAVF_DEBUG_AQ_MESSAGE,
			   "AQTX: Async fwag not set awong with postpone fwag");
		status = IAVF_EWW_PAWAM;
		goto asq_send_command_ewwow;
	}

	/* caww cwean and check queue avaiwabwe function to wecwaim the
	 * descwiptows that wewe pwocessed by FW, the function wetuwns the
	 * numbew of desc avaiwabwe
	 */
	/* the cwean function cawwed hewe couwd be cawwed in a sepawate thwead
	 * in case of asynchwonous compwetions
	 */
	if (iavf_cwean_asq(hw) == 0) {
		iavf_debug(hw,
			   IAVF_DEBUG_AQ_MESSAGE,
			   "AQTX: Ewwow queue is fuww.\n");
		status = IAVF_EWW_ADMIN_QUEUE_FUWW;
		goto asq_send_command_ewwow;
	}

	/* initiawize the temp desc pointew with the wight desc */
	desc_on_wing = IAVF_ADMINQ_DESC(hw->aq.asq, hw->aq.asq.next_to_use);

	/* if the desc is avaiwabwe copy the temp desc to the wight pwace */
	*desc_on_wing = *desc;

	/* if buff is not NUWW assume indiwect command */
	if (buff) {
		dma_buff = &hw->aq.asq.w.asq_bi[hw->aq.asq.next_to_use];
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
	iavf_debug(hw, IAVF_DEBUG_AQ_MESSAGE, "AQTX: desc and buffew:\n");
	iavf_debug_aq(hw, IAVF_DEBUG_AQ_COMMAND, (void *)desc_on_wing,
		      buff, buff_size);
	(hw->aq.asq.next_to_use)++;
	if (hw->aq.asq.next_to_use == hw->aq.asq.count)
		hw->aq.asq.next_to_use = 0;
	if (!detaiws->postpone)
		ww32(hw, IAVF_VF_ATQT1, hw->aq.asq.next_to_use);

	/* if cmd_detaiws awe not defined ow async fwag is not set,
	 * we need to wait fow desc wwite back
	 */
	if (!detaiws->async && !detaiws->postpone) {
		u32 totaw_deway = 0;

		do {
			/* AQ designews suggest use of head fow bettew
			 * timing wewiabiwity than DD bit
			 */
			if (iavf_asq_done(hw))
				bweak;
			udeway(50);
			totaw_deway += 50;
		} whiwe (totaw_deway < hw->aq.asq_cmd_timeout);
	}

	/* if weady, copy the desc back to temp */
	if (iavf_asq_done(hw)) {
		*desc = *desc_on_wing;
		if (buff)
			memcpy(buff, dma_buff->va, buff_size);
		wetvaw = we16_to_cpu(desc->wetvaw);
		if (wetvaw != 0) {
			iavf_debug(hw,
				   IAVF_DEBUG_AQ_MESSAGE,
				   "AQTX: Command compweted with ewwow 0x%X.\n",
				   wetvaw);

			/* stwip off FW intewnaw code */
			wetvaw &= 0xff;
		}
		cmd_compweted = twue;
		if ((enum iavf_admin_queue_eww)wetvaw == IAVF_AQ_WC_OK)
			status = 0;
		ewse if ((enum iavf_admin_queue_eww)wetvaw == IAVF_AQ_WC_EBUSY)
			status = IAVF_EWW_NOT_WEADY;
		ewse
			status = IAVF_EWW_ADMIN_QUEUE_EWWOW;
		hw->aq.asq_wast_status = (enum iavf_admin_queue_eww)wetvaw;
	}

	iavf_debug(hw, IAVF_DEBUG_AQ_MESSAGE,
		   "AQTX: desc and buffew wwiteback:\n");
	iavf_debug_aq(hw, IAVF_DEBUG_AQ_COMMAND, (void *)desc, buff, buff_size);

	/* save wwiteback aq if wequested */
	if (detaiws->wb_desc)
		*detaiws->wb_desc = *desc_on_wing;

	/* update the ewwow if time out occuwwed */
	if ((!cmd_compweted) &&
	    (!detaiws->async && !detaiws->postpone)) {
		if (wd32(hw, IAVF_VF_ATQWEN1) & IAVF_VF_ATQWEN1_ATQCWIT_MASK) {
			iavf_debug(hw, IAVF_DEBUG_AQ_MESSAGE,
				   "AQTX: AQ Cwiticaw ewwow.\n");
			status = IAVF_EWW_ADMIN_QUEUE_CWITICAW_EWWOW;
		} ewse {
			iavf_debug(hw, IAVF_DEBUG_AQ_MESSAGE,
				   "AQTX: Wwiteback timeout.\n");
			status = IAVF_EWW_ADMIN_QUEUE_TIMEOUT;
		}
	}

asq_send_command_ewwow:
	mutex_unwock(&hw->aq.asq_mutex);
	wetuwn status;
}

/**
 *  iavf_fiww_defauwt_diwect_cmd_desc - AQ descwiptow hewpew function
 *  @desc:     pointew to the temp descwiptow (non DMA mem)
 *  @opcode:   the opcode can be used to decide which fwags to tuwn off ow on
 *
 *  Fiww the desc with defauwt vawues
 **/
void iavf_fiww_defauwt_diwect_cmd_desc(stwuct iavf_aq_desc *desc, u16 opcode)
{
	/* zewo out the desc */
	memset((void *)desc, 0, sizeof(stwuct iavf_aq_desc));
	desc->opcode = cpu_to_we16(opcode);
	desc->fwags = cpu_to_we16(IAVF_AQ_FWAG_SI);
}

/**
 *  iavf_cwean_awq_ewement
 *  @hw: pointew to the hw stwuct
 *  @e: event info fwom the weceive descwiptow, incwudes any buffews
 *  @pending: numbew of events that couwd be weft to pwocess
 *
 *  This function cweans one Admin Weceive Queue ewement and wetuwns
 *  the contents thwough e.  It can awso wetuwn how many events awe
 *  weft to pwocess thwough 'pending'
 **/
enum iavf_status iavf_cwean_awq_ewement(stwuct iavf_hw *hw,
					stwuct iavf_awq_event_info *e,
					u16 *pending)
{
	u16 ntc = hw->aq.awq.next_to_cwean;
	stwuct iavf_aq_desc *desc;
	enum iavf_status wet_code = 0;
	stwuct iavf_dma_mem *bi;
	u16 desc_idx;
	u16 datawen;
	u16 fwags;
	u16 ntu;

	/* pwe-cwean the event info */
	memset(&e->desc, 0, sizeof(e->desc));

	/* take the wock befowe we stawt messing with the wing */
	mutex_wock(&hw->aq.awq_mutex);

	if (hw->aq.awq.count == 0) {
		iavf_debug(hw, IAVF_DEBUG_AQ_MESSAGE,
			   "AQWX: Admin queue not initiawized.\n");
		wet_code = IAVF_EWW_QUEUE_EMPTY;
		goto cwean_awq_ewement_eww;
	}

	/* set next_to_use to head */
	ntu = wd32(hw, IAVF_VF_AWQH1) & IAVF_VF_AWQH1_AWQH_MASK;
	if (ntu == ntc) {
		/* nothing to do - shouwdn't need to update wing's vawues */
		wet_code = IAVF_EWW_ADMIN_QUEUE_NO_WOWK;
		goto cwean_awq_ewement_out;
	}

	/* now cwean the next descwiptow */
	desc = IAVF_ADMINQ_DESC(hw->aq.awq, ntc);
	desc_idx = ntc;

	hw->aq.awq_wast_status =
		(enum iavf_admin_queue_eww)we16_to_cpu(desc->wetvaw);
	fwags = we16_to_cpu(desc->fwags);
	if (fwags & IAVF_AQ_FWAG_EWW) {
		wet_code = IAVF_EWW_ADMIN_QUEUE_EWWOW;
		iavf_debug(hw,
			   IAVF_DEBUG_AQ_MESSAGE,
			   "AQWX: Event weceived with ewwow 0x%X.\n",
			   hw->aq.awq_wast_status);
	}

	e->desc = *desc;
	datawen = we16_to_cpu(desc->datawen);
	e->msg_wen = min(datawen, e->buf_wen);
	if (e->msg_buf && (e->msg_wen != 0))
		memcpy(e->msg_buf, hw->aq.awq.w.awq_bi[desc_idx].va,
		       e->msg_wen);

	iavf_debug(hw, IAVF_DEBUG_AQ_MESSAGE, "AQWX: desc and buffew:\n");
	iavf_debug_aq(hw, IAVF_DEBUG_AQ_COMMAND, (void *)desc, e->msg_buf,
		      hw->aq.awq_buf_size);

	/* Westowe the owiginaw datawen and buffew addwess in the desc,
	 * FW updates datawen to indicate the event message
	 * size
	 */
	bi = &hw->aq.awq.w.awq_bi[ntc];
	memset((void *)desc, 0, sizeof(stwuct iavf_aq_desc));

	desc->fwags = cpu_to_we16(IAVF_AQ_FWAG_BUF);
	if (hw->aq.awq_buf_size > IAVF_AQ_WAWGE_BUF)
		desc->fwags |= cpu_to_we16(IAVF_AQ_FWAG_WB);
	desc->datawen = cpu_to_we16((u16)bi->size);
	desc->pawams.extewnaw.addw_high = cpu_to_we32(uppew_32_bits(bi->pa));
	desc->pawams.extewnaw.addw_wow = cpu_to_we32(wowew_32_bits(bi->pa));

	/* set taiw = the wast cweaned desc index. */
	ww32(hw, IAVF_VF_AWQT1, ntc);
	/* ntc is updated to taiw + 1 */
	ntc++;
	if (ntc == hw->aq.num_awq_entwies)
		ntc = 0;
	hw->aq.awq.next_to_cwean = ntc;
	hw->aq.awq.next_to_use = ntu;

cwean_awq_ewement_out:
	/* Set pending if needed, unwock and wetuwn */
	if (pending)
		*pending = (ntc > ntu ? hw->aq.awq.count : 0) + (ntu - ntc);

cwean_awq_ewement_eww:
	mutex_unwock(&hw->aq.awq_mutex);

	wetuwn wet_code;
}
