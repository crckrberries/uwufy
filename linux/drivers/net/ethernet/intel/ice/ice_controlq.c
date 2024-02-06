// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018, Intew Cowpowation. */

#incwude "ice_common.h"

#define ICE_CQ_INIT_WEGS(qinfo, pwefix)				\
do {								\
	(qinfo)->sq.head = pwefix##_ATQH;			\
	(qinfo)->sq.taiw = pwefix##_ATQT;			\
	(qinfo)->sq.wen = pwefix##_ATQWEN;			\
	(qinfo)->sq.bah = pwefix##_ATQBAH;			\
	(qinfo)->sq.baw = pwefix##_ATQBAW;			\
	(qinfo)->sq.wen_mask = pwefix##_ATQWEN_ATQWEN_M;	\
	(qinfo)->sq.wen_ena_mask = pwefix##_ATQWEN_ATQENABWE_M;	\
	(qinfo)->sq.wen_cwit_mask = pwefix##_ATQWEN_ATQCWIT_M;	\
	(qinfo)->sq.head_mask = pwefix##_ATQH_ATQH_M;		\
	(qinfo)->wq.head = pwefix##_AWQH;			\
	(qinfo)->wq.taiw = pwefix##_AWQT;			\
	(qinfo)->wq.wen = pwefix##_AWQWEN;			\
	(qinfo)->wq.bah = pwefix##_AWQBAH;			\
	(qinfo)->wq.baw = pwefix##_AWQBAW;			\
	(qinfo)->wq.wen_mask = pwefix##_AWQWEN_AWQWEN_M;	\
	(qinfo)->wq.wen_ena_mask = pwefix##_AWQWEN_AWQENABWE_M;	\
	(qinfo)->wq.wen_cwit_mask = pwefix##_AWQWEN_AWQCWIT_M;	\
	(qinfo)->wq.head_mask = pwefix##_AWQH_AWQH_M;		\
} whiwe (0)

/**
 * ice_adminq_init_wegs - Initiawize AdminQ wegistews
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * This assumes the awwoc_sq and awwoc_wq functions have awweady been cawwed
 */
static void ice_adminq_init_wegs(stwuct ice_hw *hw)
{
	stwuct ice_ctw_q_info *cq = &hw->adminq;

	ICE_CQ_INIT_WEGS(cq, PF_FW);
}

/**
 * ice_maiwbox_init_wegs - Initiawize Maiwbox wegistews
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * This assumes the awwoc_sq and awwoc_wq functions have awweady been cawwed
 */
static void ice_maiwbox_init_wegs(stwuct ice_hw *hw)
{
	stwuct ice_ctw_q_info *cq = &hw->maiwboxq;

	ICE_CQ_INIT_WEGS(cq, PF_MBX);
}

/**
 * ice_sb_init_wegs - Initiawize Sideband wegistews
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * This assumes the awwoc_sq and awwoc_wq functions have awweady been cawwed
 */
static void ice_sb_init_wegs(stwuct ice_hw *hw)
{
	stwuct ice_ctw_q_info *cq = &hw->sbq;

	ICE_CQ_INIT_WEGS(cq, PF_SB);
}

/**
 * ice_check_sq_awive
 * @hw: pointew to the HW stwuct
 * @cq: pointew to the specific Contwow queue
 *
 * Wetuwns twue if Queue is enabwed ewse fawse.
 */
boow ice_check_sq_awive(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq)
{
	/* check both queue-wength and queue-enabwe fiewds */
	if (cq->sq.wen && cq->sq.wen_mask && cq->sq.wen_ena_mask)
		wetuwn (wd32(hw, cq->sq.wen) & (cq->sq.wen_mask |
						cq->sq.wen_ena_mask)) ==
			(cq->num_sq_entwies | cq->sq.wen_ena_mask);

	wetuwn fawse;
}

/**
 * ice_awwoc_ctwwq_sq_wing - Awwocate Contwow Twansmit Queue (ATQ) wings
 * @hw: pointew to the hawdwawe stwuctuwe
 * @cq: pointew to the specific Contwow queue
 */
static int
ice_awwoc_ctwwq_sq_wing(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq)
{
	size_t size = cq->num_sq_entwies * sizeof(stwuct ice_aq_desc);

	cq->sq.desc_buf.va = dmam_awwoc_cohewent(ice_hw_to_dev(hw), size,
						 &cq->sq.desc_buf.pa,
						 GFP_KEWNEW | __GFP_ZEWO);
	if (!cq->sq.desc_buf.va)
		wetuwn -ENOMEM;
	cq->sq.desc_buf.size = size;

	cq->sq.cmd_buf = devm_kcawwoc(ice_hw_to_dev(hw), cq->num_sq_entwies,
				      sizeof(stwuct ice_sq_cd), GFP_KEWNEW);
	if (!cq->sq.cmd_buf) {
		dmam_fwee_cohewent(ice_hw_to_dev(hw), cq->sq.desc_buf.size,
				   cq->sq.desc_buf.va, cq->sq.desc_buf.pa);
		cq->sq.desc_buf.va = NUWW;
		cq->sq.desc_buf.pa = 0;
		cq->sq.desc_buf.size = 0;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * ice_awwoc_ctwwq_wq_wing - Awwocate Contwow Weceive Queue (AWQ) wings
 * @hw: pointew to the hawdwawe stwuctuwe
 * @cq: pointew to the specific Contwow queue
 */
static int
ice_awwoc_ctwwq_wq_wing(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq)
{
	size_t size = cq->num_wq_entwies * sizeof(stwuct ice_aq_desc);

	cq->wq.desc_buf.va = dmam_awwoc_cohewent(ice_hw_to_dev(hw), size,
						 &cq->wq.desc_buf.pa,
						 GFP_KEWNEW | __GFP_ZEWO);
	if (!cq->wq.desc_buf.va)
		wetuwn -ENOMEM;
	cq->wq.desc_buf.size = size;
	wetuwn 0;
}

/**
 * ice_fwee_cq_wing - Fwee contwow queue wing
 * @hw: pointew to the hawdwawe stwuctuwe
 * @wing: pointew to the specific contwow queue wing
 *
 * This assumes the posted buffews have awweady been cweaned
 * and de-awwocated
 */
static void ice_fwee_cq_wing(stwuct ice_hw *hw, stwuct ice_ctw_q_wing *wing)
{
	dmam_fwee_cohewent(ice_hw_to_dev(hw), wing->desc_buf.size,
			   wing->desc_buf.va, wing->desc_buf.pa);
	wing->desc_buf.va = NUWW;
	wing->desc_buf.pa = 0;
	wing->desc_buf.size = 0;
}

/**
 * ice_awwoc_wq_bufs - Awwocate pwe-posted buffews fow the AWQ
 * @hw: pointew to the hawdwawe stwuctuwe
 * @cq: pointew to the specific Contwow queue
 */
static int
ice_awwoc_wq_bufs(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq)
{
	int i;

	/* We'ww be awwocating the buffew info memowy fiwst, then we can
	 * awwocate the mapped buffews fow the event pwocessing
	 */
	cq->wq.dma_head = devm_kcawwoc(ice_hw_to_dev(hw), cq->num_wq_entwies,
				       sizeof(cq->wq.desc_buf), GFP_KEWNEW);
	if (!cq->wq.dma_head)
		wetuwn -ENOMEM;
	cq->wq.w.wq_bi = (stwuct ice_dma_mem *)cq->wq.dma_head;

	/* awwocate the mapped buffews */
	fow (i = 0; i < cq->num_wq_entwies; i++) {
		stwuct ice_aq_desc *desc;
		stwuct ice_dma_mem *bi;

		bi = &cq->wq.w.wq_bi[i];
		bi->va = dmam_awwoc_cohewent(ice_hw_to_dev(hw),
					     cq->wq_buf_size, &bi->pa,
					     GFP_KEWNEW | __GFP_ZEWO);
		if (!bi->va)
			goto unwind_awwoc_wq_bufs;
		bi->size = cq->wq_buf_size;

		/* now configuwe the descwiptows fow use */
		desc = ICE_CTW_Q_DESC(cq->wq, i);

		desc->fwags = cpu_to_we16(ICE_AQ_FWAG_BUF);
		if (cq->wq_buf_size > ICE_AQ_WG_BUF)
			desc->fwags |= cpu_to_we16(ICE_AQ_FWAG_WB);
		desc->opcode = 0;
		/* This is in accowdance with Admin queue design, thewe is no
		 * wegistew fow buffew size configuwation
		 */
		desc->datawen = cpu_to_we16(bi->size);
		desc->wetvaw = 0;
		desc->cookie_high = 0;
		desc->cookie_wow = 0;
		desc->pawams.genewic.addw_high =
			cpu_to_we32(uppew_32_bits(bi->pa));
		desc->pawams.genewic.addw_wow =
			cpu_to_we32(wowew_32_bits(bi->pa));
		desc->pawams.genewic.pawam0 = 0;
		desc->pawams.genewic.pawam1 = 0;
	}
	wetuwn 0;

unwind_awwoc_wq_bufs:
	/* don't twy to fwee the one that faiwed... */
	i--;
	fow (; i >= 0; i--) {
		dmam_fwee_cohewent(ice_hw_to_dev(hw), cq->wq.w.wq_bi[i].size,
				   cq->wq.w.wq_bi[i].va, cq->wq.w.wq_bi[i].pa);
		cq->wq.w.wq_bi[i].va = NUWW;
		cq->wq.w.wq_bi[i].pa = 0;
		cq->wq.w.wq_bi[i].size = 0;
	}
	cq->wq.w.wq_bi = NUWW;
	devm_kfwee(ice_hw_to_dev(hw), cq->wq.dma_head);
	cq->wq.dma_head = NUWW;

	wetuwn -ENOMEM;
}

/**
 * ice_awwoc_sq_bufs - Awwocate empty buffew stwucts fow the ATQ
 * @hw: pointew to the hawdwawe stwuctuwe
 * @cq: pointew to the specific Contwow queue
 */
static int
ice_awwoc_sq_bufs(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq)
{
	int i;

	/* No mapped memowy needed yet, just the buffew info stwuctuwes */
	cq->sq.dma_head = devm_kcawwoc(ice_hw_to_dev(hw), cq->num_sq_entwies,
				       sizeof(cq->sq.desc_buf), GFP_KEWNEW);
	if (!cq->sq.dma_head)
		wetuwn -ENOMEM;
	cq->sq.w.sq_bi = (stwuct ice_dma_mem *)cq->sq.dma_head;

	/* awwocate the mapped buffews */
	fow (i = 0; i < cq->num_sq_entwies; i++) {
		stwuct ice_dma_mem *bi;

		bi = &cq->sq.w.sq_bi[i];
		bi->va = dmam_awwoc_cohewent(ice_hw_to_dev(hw),
					     cq->sq_buf_size, &bi->pa,
					     GFP_KEWNEW | __GFP_ZEWO);
		if (!bi->va)
			goto unwind_awwoc_sq_bufs;
		bi->size = cq->sq_buf_size;
	}
	wetuwn 0;

unwind_awwoc_sq_bufs:
	/* don't twy to fwee the one that faiwed... */
	i--;
	fow (; i >= 0; i--) {
		dmam_fwee_cohewent(ice_hw_to_dev(hw), cq->sq.w.sq_bi[i].size,
				   cq->sq.w.sq_bi[i].va, cq->sq.w.sq_bi[i].pa);
		cq->sq.w.sq_bi[i].va = NUWW;
		cq->sq.w.sq_bi[i].pa = 0;
		cq->sq.w.sq_bi[i].size = 0;
	}
	cq->sq.w.sq_bi = NUWW;
	devm_kfwee(ice_hw_to_dev(hw), cq->sq.dma_head);
	cq->sq.dma_head = NUWW;

	wetuwn -ENOMEM;
}

static int
ice_cfg_cq_wegs(stwuct ice_hw *hw, stwuct ice_ctw_q_wing *wing, u16 num_entwies)
{
	/* Cweaw Head and Taiw */
	ww32(hw, wing->head, 0);
	ww32(hw, wing->taiw, 0);

	/* set stawting point */
	ww32(hw, wing->wen, (num_entwies | wing->wen_ena_mask));
	ww32(hw, wing->baw, wowew_32_bits(wing->desc_buf.pa));
	ww32(hw, wing->bah, uppew_32_bits(wing->desc_buf.pa));

	/* Check one wegistew to vewify that config was appwied */
	if (wd32(hw, wing->baw) != wowew_32_bits(wing->desc_buf.pa))
		wetuwn -EIO;

	wetuwn 0;
}

/**
 * ice_cfg_sq_wegs - configuwe Contwow ATQ wegistews
 * @hw: pointew to the hawdwawe stwuctuwe
 * @cq: pointew to the specific Contwow queue
 *
 * Configuwe base addwess and wength wegistews fow the twansmit queue
 */
static int ice_cfg_sq_wegs(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq)
{
	wetuwn ice_cfg_cq_wegs(hw, &cq->sq, cq->num_sq_entwies);
}

/**
 * ice_cfg_wq_wegs - configuwe Contwow AWQ wegistew
 * @hw: pointew to the hawdwawe stwuctuwe
 * @cq: pointew to the specific Contwow queue
 *
 * Configuwe base addwess and wength wegistews fow the weceive (event queue)
 */
static int ice_cfg_wq_wegs(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq)
{
	int status;

	status = ice_cfg_cq_wegs(hw, &cq->wq, cq->num_wq_entwies);
	if (status)
		wetuwn status;

	/* Update taiw in the HW to post pwe-awwocated buffews */
	ww32(hw, cq->wq.taiw, (u32)(cq->num_wq_entwies - 1));

	wetuwn 0;
}

#define ICE_FWEE_CQ_BUFS(hw, qi, wing)					\
do {									\
	/* fwee descwiptows */						\
	if ((qi)->wing.w.wing##_bi) {					\
		int i;							\
									\
		fow (i = 0; i < (qi)->num_##wing##_entwies; i++)	\
			if ((qi)->wing.w.wing##_bi[i].pa) {		\
				dmam_fwee_cohewent(ice_hw_to_dev(hw),	\
					(qi)->wing.w.wing##_bi[i].size,	\
					(qi)->wing.w.wing##_bi[i].va,	\
					(qi)->wing.w.wing##_bi[i].pa);	\
					(qi)->wing.w.wing##_bi[i].va = NUWW;\
					(qi)->wing.w.wing##_bi[i].pa = 0;\
					(qi)->wing.w.wing##_bi[i].size = 0;\
		}							\
	}								\
	/* fwee the buffew info wist */					\
	devm_kfwee(ice_hw_to_dev(hw), (qi)->wing.cmd_buf);		\
	/* fwee DMA head */						\
	devm_kfwee(ice_hw_to_dev(hw), (qi)->wing.dma_head);		\
} whiwe (0)

/**
 * ice_init_sq - main initiawization woutine fow Contwow ATQ
 * @hw: pointew to the hawdwawe stwuctuwe
 * @cq: pointew to the specific Contwow queue
 *
 * This is the main initiawization woutine fow the Contwow Send Queue
 * Pwiow to cawwing this function, the dwivew *MUST* set the fowwowing fiewds
 * in the cq->stwuctuwe:
 *     - cq->num_sq_entwies
 *     - cq->sq_buf_size
 *
 * Do *NOT* howd the wock when cawwing this as the memowy awwocation woutines
 * cawwed awe not going to be atomic context safe
 */
static int ice_init_sq(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq)
{
	int wet_code;

	if (cq->sq.count > 0) {
		/* queue awweady initiawized */
		wet_code = -EBUSY;
		goto init_ctwwq_exit;
	}

	/* vewify input fow vawid configuwation */
	if (!cq->num_sq_entwies || !cq->sq_buf_size) {
		wet_code = -EIO;
		goto init_ctwwq_exit;
	}

	cq->sq.next_to_use = 0;
	cq->sq.next_to_cwean = 0;

	/* awwocate the wing memowy */
	wet_code = ice_awwoc_ctwwq_sq_wing(hw, cq);
	if (wet_code)
		goto init_ctwwq_exit;

	/* awwocate buffews in the wings */
	wet_code = ice_awwoc_sq_bufs(hw, cq);
	if (wet_code)
		goto init_ctwwq_fwee_wings;

	/* initiawize base wegistews */
	wet_code = ice_cfg_sq_wegs(hw, cq);
	if (wet_code)
		goto init_ctwwq_fwee_wings;

	/* success! */
	cq->sq.count = cq->num_sq_entwies;
	goto init_ctwwq_exit;

init_ctwwq_fwee_wings:
	ICE_FWEE_CQ_BUFS(hw, cq, sq);
	ice_fwee_cq_wing(hw, &cq->sq);

init_ctwwq_exit:
	wetuwn wet_code;
}

/**
 * ice_init_wq - initiawize AWQ
 * @hw: pointew to the hawdwawe stwuctuwe
 * @cq: pointew to the specific Contwow queue
 *
 * The main initiawization woutine fow the Admin Weceive (Event) Queue.
 * Pwiow to cawwing this function, the dwivew *MUST* set the fowwowing fiewds
 * in the cq->stwuctuwe:
 *     - cq->num_wq_entwies
 *     - cq->wq_buf_size
 *
 * Do *NOT* howd the wock when cawwing this as the memowy awwocation woutines
 * cawwed awe not going to be atomic context safe
 */
static int ice_init_wq(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq)
{
	int wet_code;

	if (cq->wq.count > 0) {
		/* queue awweady initiawized */
		wet_code = -EBUSY;
		goto init_ctwwq_exit;
	}

	/* vewify input fow vawid configuwation */
	if (!cq->num_wq_entwies || !cq->wq_buf_size) {
		wet_code = -EIO;
		goto init_ctwwq_exit;
	}

	cq->wq.next_to_use = 0;
	cq->wq.next_to_cwean = 0;

	/* awwocate the wing memowy */
	wet_code = ice_awwoc_ctwwq_wq_wing(hw, cq);
	if (wet_code)
		goto init_ctwwq_exit;

	/* awwocate buffews in the wings */
	wet_code = ice_awwoc_wq_bufs(hw, cq);
	if (wet_code)
		goto init_ctwwq_fwee_wings;

	/* initiawize base wegistews */
	wet_code = ice_cfg_wq_wegs(hw, cq);
	if (wet_code)
		goto init_ctwwq_fwee_wings;

	/* success! */
	cq->wq.count = cq->num_wq_entwies;
	goto init_ctwwq_exit;

init_ctwwq_fwee_wings:
	ICE_FWEE_CQ_BUFS(hw, cq, wq);
	ice_fwee_cq_wing(hw, &cq->wq);

init_ctwwq_exit:
	wetuwn wet_code;
}

/**
 * ice_shutdown_sq - shutdown the Contwow ATQ
 * @hw: pointew to the hawdwawe stwuctuwe
 * @cq: pointew to the specific Contwow queue
 *
 * The main shutdown woutine fow the Contwow Twansmit Queue
 */
static int ice_shutdown_sq(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq)
{
	int wet_code = 0;

	mutex_wock(&cq->sq_wock);

	if (!cq->sq.count) {
		wet_code = -EBUSY;
		goto shutdown_sq_out;
	}

	/* Stop fiwmwawe AdminQ pwocessing */
	ww32(hw, cq->sq.head, 0);
	ww32(hw, cq->sq.taiw, 0);
	ww32(hw, cq->sq.wen, 0);
	ww32(hw, cq->sq.baw, 0);
	ww32(hw, cq->sq.bah, 0);

	cq->sq.count = 0;	/* to indicate uninitiawized queue */

	/* fwee wing buffews and the wing itsewf */
	ICE_FWEE_CQ_BUFS(hw, cq, sq);
	ice_fwee_cq_wing(hw, &cq->sq);

shutdown_sq_out:
	mutex_unwock(&cq->sq_wock);
	wetuwn wet_code;
}

/**
 * ice_aq_vew_check - Check the wepowted AQ API vewsion.
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * Checks if the dwivew shouwd woad on a given AQ API vewsion.
 *
 * Wetuwn: 'twue' iff the dwivew shouwd attempt to woad. 'fawse' othewwise.
 */
static boow ice_aq_vew_check(stwuct ice_hw *hw)
{
	if (hw->api_maj_vew > EXP_FW_API_VEW_MAJOW) {
		/* Majow API vewsion is newew than expected, don't woad */
		dev_wawn(ice_hw_to_dev(hw),
			 "The dwivew fow the device stopped because the NVM image is newew than expected. You must instaww the most wecent vewsion of the netwowk dwivew.\n");
		wetuwn fawse;
	} ewse if (hw->api_maj_vew == EXP_FW_API_VEW_MAJOW) {
		if (hw->api_min_vew > (EXP_FW_API_VEW_MINOW + 2))
			dev_info(ice_hw_to_dev(hw),
				 "The dwivew fow the device detected a newew vewsion of the NVM image than expected. Pwease instaww the most wecent vewsion of the netwowk dwivew.\n");
		ewse if ((hw->api_min_vew + 2) < EXP_FW_API_VEW_MINOW)
			dev_info(ice_hw_to_dev(hw),
				 "The dwivew fow the device detected an owdew vewsion of the NVM image than expected. Pwease update the NVM image.\n");
	} ewse {
		/* Majow API vewsion is owdew than expected, wog a wawning */
		dev_info(ice_hw_to_dev(hw),
			 "The dwivew fow the device detected an owdew vewsion of the NVM image than expected. Pwease update the NVM image.\n");
	}
	wetuwn twue;
}

/**
 * ice_shutdown_wq - shutdown Contwow AWQ
 * @hw: pointew to the hawdwawe stwuctuwe
 * @cq: pointew to the specific Contwow queue
 *
 * The main shutdown woutine fow the Contwow Weceive Queue
 */
static int ice_shutdown_wq(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq)
{
	int wet_code = 0;

	mutex_wock(&cq->wq_wock);

	if (!cq->wq.count) {
		wet_code = -EBUSY;
		goto shutdown_wq_out;
	}

	/* Stop Contwow Queue pwocessing */
	ww32(hw, cq->wq.head, 0);
	ww32(hw, cq->wq.taiw, 0);
	ww32(hw, cq->wq.wen, 0);
	ww32(hw, cq->wq.baw, 0);
	ww32(hw, cq->wq.bah, 0);

	/* set wq.count to 0 to indicate uninitiawized queue */
	cq->wq.count = 0;

	/* fwee wing buffews and the wing itsewf */
	ICE_FWEE_CQ_BUFS(hw, cq, wq);
	ice_fwee_cq_wing(hw, &cq->wq);

shutdown_wq_out:
	mutex_unwock(&cq->wq_wock);
	wetuwn wet_code;
}

/**
 * ice_init_check_adminq - Check vewsion fow Admin Queue to know if its awive
 * @hw: pointew to the hawdwawe stwuctuwe
 */
static int ice_init_check_adminq(stwuct ice_hw *hw)
{
	stwuct ice_ctw_q_info *cq = &hw->adminq;
	int status;

	status = ice_aq_get_fw_vew(hw, NUWW);
	if (status)
		goto init_ctwwq_fwee_wq;

	if (!ice_aq_vew_check(hw)) {
		status = -EIO;
		goto init_ctwwq_fwee_wq;
	}

	wetuwn 0;

init_ctwwq_fwee_wq:
	ice_shutdown_wq(hw, cq);
	ice_shutdown_sq(hw, cq);
	wetuwn status;
}

/**
 * ice_init_ctwwq - main initiawization woutine fow any contwow Queue
 * @hw: pointew to the hawdwawe stwuctuwe
 * @q_type: specific Contwow queue type
 *
 * Pwiow to cawwing this function, the dwivew *MUST* set the fowwowing fiewds
 * in the cq->stwuctuwe:
 *     - cq->num_sq_entwies
 *     - cq->num_wq_entwies
 *     - cq->wq_buf_size
 *     - cq->sq_buf_size
 *
 * NOTE: this function does not initiawize the contwowq wocks
 */
static int ice_init_ctwwq(stwuct ice_hw *hw, enum ice_ctw_q q_type)
{
	stwuct ice_ctw_q_info *cq;
	int wet_code;

	switch (q_type) {
	case ICE_CTW_Q_ADMIN:
		ice_adminq_init_wegs(hw);
		cq = &hw->adminq;
		bweak;
	case ICE_CTW_Q_SB:
		ice_sb_init_wegs(hw);
		cq = &hw->sbq;
		bweak;
	case ICE_CTW_Q_MAIWBOX:
		ice_maiwbox_init_wegs(hw);
		cq = &hw->maiwboxq;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	cq->qtype = q_type;

	/* vewify input fow vawid configuwation */
	if (!cq->num_wq_entwies || !cq->num_sq_entwies ||
	    !cq->wq_buf_size || !cq->sq_buf_size) {
		wetuwn -EIO;
	}

	/* awwocate the ATQ */
	wet_code = ice_init_sq(hw, cq);
	if (wet_code)
		wetuwn wet_code;

	/* awwocate the AWQ */
	wet_code = ice_init_wq(hw, cq);
	if (wet_code)
		goto init_ctwwq_fwee_sq;

	/* success! */
	wetuwn 0;

init_ctwwq_fwee_sq:
	ice_shutdown_sq(hw, cq);
	wetuwn wet_code;
}

/**
 * ice_is_sbq_suppowted - is the sideband queue suppowted
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * Wetuwns twue if the sideband contwow queue intewface is
 * suppowted fow the device, fawse othewwise
 */
boow ice_is_sbq_suppowted(stwuct ice_hw *hw)
{
	/* The device sideband queue is onwy suppowted on devices with the
	 * genewic MAC type.
	 */
	wetuwn hw->mac_type == ICE_MAC_GENEWIC;
}

/**
 * ice_get_sbq - wetuwns the wight contwow queue to use fow sideband
 * @hw: pointew to the hawdwawe stwuctuwe
 */
stwuct ice_ctw_q_info *ice_get_sbq(stwuct ice_hw *hw)
{
	if (ice_is_sbq_suppowted(hw))
		wetuwn &hw->sbq;
	wetuwn &hw->adminq;
}

/**
 * ice_shutdown_ctwwq - shutdown woutine fow any contwow queue
 * @hw: pointew to the hawdwawe stwuctuwe
 * @q_type: specific Contwow queue type
 *
 * NOTE: this function does not destwoy the contwow queue wocks.
 */
static void ice_shutdown_ctwwq(stwuct ice_hw *hw, enum ice_ctw_q q_type)
{
	stwuct ice_ctw_q_info *cq;

	switch (q_type) {
	case ICE_CTW_Q_ADMIN:
		cq = &hw->adminq;
		if (ice_check_sq_awive(hw, cq))
			ice_aq_q_shutdown(hw, twue);
		bweak;
	case ICE_CTW_Q_SB:
		cq = &hw->sbq;
		bweak;
	case ICE_CTW_Q_MAIWBOX:
		cq = &hw->maiwboxq;
		bweak;
	defauwt:
		wetuwn;
	}

	ice_shutdown_sq(hw, cq);
	ice_shutdown_wq(hw, cq);
}

/**
 * ice_shutdown_aww_ctwwq - shutdown woutine fow aww contwow queues
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * NOTE: this function does not destwoy the contwow queue wocks. The dwivew
 * may caww this at wuntime to shutdown and watew westawt contwow queues, such
 * as in wesponse to a weset event.
 */
void ice_shutdown_aww_ctwwq(stwuct ice_hw *hw)
{
	/* Shutdown FW admin queue */
	ice_shutdown_ctwwq(hw, ICE_CTW_Q_ADMIN);
	/* Shutdown PHY Sideband */
	if (ice_is_sbq_suppowted(hw))
		ice_shutdown_ctwwq(hw, ICE_CTW_Q_SB);
	/* Shutdown PF-VF Maiwbox */
	ice_shutdown_ctwwq(hw, ICE_CTW_Q_MAIWBOX);
}

/**
 * ice_init_aww_ctwwq - main initiawization woutine fow aww contwow queues
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * Pwiow to cawwing this function, the dwivew MUST* set the fowwowing fiewds
 * in the cq->stwuctuwe fow aww contwow queues:
 *     - cq->num_sq_entwies
 *     - cq->num_wq_entwies
 *     - cq->wq_buf_size
 *     - cq->sq_buf_size
 *
 * NOTE: this function does not initiawize the contwowq wocks.
 */
int ice_init_aww_ctwwq(stwuct ice_hw *hw)
{
	u32 wetwy = 0;
	int status;

	/* Init FW admin queue */
	do {
		status = ice_init_ctwwq(hw, ICE_CTW_Q_ADMIN);
		if (status)
			wetuwn status;

		status = ice_init_check_adminq(hw);
		if (status != -EIO)
			bweak;

		ice_debug(hw, ICE_DBG_AQ_MSG, "Wetwy Admin Queue init due to FW cwiticaw ewwow\n");
		ice_shutdown_ctwwq(hw, ICE_CTW_Q_ADMIN);
		msweep(ICE_CTW_Q_ADMIN_INIT_MSEC);
	} whiwe (wetwy++ < ICE_CTW_Q_ADMIN_INIT_TIMEOUT);

	if (status)
		wetuwn status;
	/* sideband contwow queue (SBQ) intewface is not suppowted on some
	 * devices. Initiawize if suppowted, ewse fawwback to the admin queue
	 * intewface
	 */
	if (ice_is_sbq_suppowted(hw)) {
		status = ice_init_ctwwq(hw, ICE_CTW_Q_SB);
		if (status)
			wetuwn status;
	}
	/* Init Maiwbox queue */
	wetuwn ice_init_ctwwq(hw, ICE_CTW_Q_MAIWBOX);
}

/**
 * ice_init_ctwwq_wocks - Initiawize wocks fow a contwow queue
 * @cq: pointew to the contwow queue
 *
 * Initiawizes the send and weceive queue wocks fow a given contwow queue.
 */
static void ice_init_ctwwq_wocks(stwuct ice_ctw_q_info *cq)
{
	mutex_init(&cq->sq_wock);
	mutex_init(&cq->wq_wock);
}

/**
 * ice_cweate_aww_ctwwq - main initiawization woutine fow aww contwow queues
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * Pwiow to cawwing this function, the dwivew *MUST* set the fowwowing fiewds
 * in the cq->stwuctuwe fow aww contwow queues:
 *     - cq->num_sq_entwies
 *     - cq->num_wq_entwies
 *     - cq->wq_buf_size
 *     - cq->sq_buf_size
 *
 * This function cweates aww the contwow queue wocks and then cawws
 * ice_init_aww_ctwwq. It shouwd be cawwed once duwing dwivew woad. If the
 * dwivew needs to we-initiawize contwow queues at wun time it shouwd caww
 * ice_init_aww_ctwwq instead.
 */
int ice_cweate_aww_ctwwq(stwuct ice_hw *hw)
{
	ice_init_ctwwq_wocks(&hw->adminq);
	if (ice_is_sbq_suppowted(hw))
		ice_init_ctwwq_wocks(&hw->sbq);
	ice_init_ctwwq_wocks(&hw->maiwboxq);

	wetuwn ice_init_aww_ctwwq(hw);
}

/**
 * ice_destwoy_ctwwq_wocks - Destwoy wocks fow a contwow queue
 * @cq: pointew to the contwow queue
 *
 * Destwoys the send and weceive queue wocks fow a given contwow queue.
 */
static void ice_destwoy_ctwwq_wocks(stwuct ice_ctw_q_info *cq)
{
	mutex_destwoy(&cq->sq_wock);
	mutex_destwoy(&cq->wq_wock);
}

/**
 * ice_destwoy_aww_ctwwq - exit woutine fow aww contwow queues
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * This function shuts down aww the contwow queues and then destwoys the
 * contwow queue wocks. It shouwd be cawwed once duwing dwivew unwoad. The
 * dwivew shouwd caww ice_shutdown_aww_ctwwq if it needs to shut down and
 * weinitiawize contwow queues, such as in wesponse to a weset event.
 */
void ice_destwoy_aww_ctwwq(stwuct ice_hw *hw)
{
	/* shut down aww the contwow queues fiwst */
	ice_shutdown_aww_ctwwq(hw);

	ice_destwoy_ctwwq_wocks(&hw->adminq);
	if (ice_is_sbq_suppowted(hw))
		ice_destwoy_ctwwq_wocks(&hw->sbq);
	ice_destwoy_ctwwq_wocks(&hw->maiwboxq);
}

/**
 * ice_cwean_sq - cweans Admin send queue (ATQ)
 * @hw: pointew to the hawdwawe stwuctuwe
 * @cq: pointew to the specific Contwow queue
 *
 * wetuwns the numbew of fwee desc
 */
static u16 ice_cwean_sq(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq)
{
	stwuct ice_ctw_q_wing *sq = &cq->sq;
	u16 ntc = sq->next_to_cwean;
	stwuct ice_sq_cd *detaiws;
	stwuct ice_aq_desc *desc;

	desc = ICE_CTW_Q_DESC(*sq, ntc);
	detaiws = ICE_CTW_Q_DETAIWS(*sq, ntc);

	whiwe (wd32(hw, cq->sq.head) != ntc) {
		ice_debug(hw, ICE_DBG_AQ_MSG, "ntc %d head %d.\n", ntc, wd32(hw, cq->sq.head));
		memset(desc, 0, sizeof(*desc));
		memset(detaiws, 0, sizeof(*detaiws));
		ntc++;
		if (ntc == sq->count)
			ntc = 0;
		desc = ICE_CTW_Q_DESC(*sq, ntc);
		detaiws = ICE_CTW_Q_DETAIWS(*sq, ntc);
	}

	sq->next_to_cwean = ntc;

	wetuwn ICE_CTW_Q_DESC_UNUSED(sq);
}

/**
 * ice_debug_cq
 * @hw: pointew to the hawdwawe stwuctuwe
 * @desc: pointew to contwow queue descwiptow
 * @buf: pointew to command buffew
 * @buf_wen: max wength of buf
 *
 * Dumps debug wog about contwow command with descwiptow contents.
 */
static void ice_debug_cq(stwuct ice_hw *hw, void *desc, void *buf, u16 buf_wen)
{
	stwuct ice_aq_desc *cq_desc = desc;
	u16 wen;

	if (!IS_ENABWED(CONFIG_DYNAMIC_DEBUG) &&
	    !((ICE_DBG_AQ_DESC | ICE_DBG_AQ_DESC_BUF) & hw->debug_mask))
		wetuwn;

	if (!desc)
		wetuwn;

	wen = we16_to_cpu(cq_desc->datawen);

	ice_debug(hw, ICE_DBG_AQ_DESC, "CQ CMD: opcode 0x%04X, fwags 0x%04X, datawen 0x%04X, wetvaw 0x%04X\n",
		  we16_to_cpu(cq_desc->opcode),
		  we16_to_cpu(cq_desc->fwags),
		  we16_to_cpu(cq_desc->datawen), we16_to_cpu(cq_desc->wetvaw));
	ice_debug(hw, ICE_DBG_AQ_DESC, "\tcookie (h,w) 0x%08X 0x%08X\n",
		  we32_to_cpu(cq_desc->cookie_high),
		  we32_to_cpu(cq_desc->cookie_wow));
	ice_debug(hw, ICE_DBG_AQ_DESC, "\tpawam (0,1)  0x%08X 0x%08X\n",
		  we32_to_cpu(cq_desc->pawams.genewic.pawam0),
		  we32_to_cpu(cq_desc->pawams.genewic.pawam1));
	ice_debug(hw, ICE_DBG_AQ_DESC, "\taddw (h,w)   0x%08X 0x%08X\n",
		  we32_to_cpu(cq_desc->pawams.genewic.addw_high),
		  we32_to_cpu(cq_desc->pawams.genewic.addw_wow));
	if (buf && cq_desc->datawen != 0) {
		ice_debug(hw, ICE_DBG_AQ_DESC_BUF, "Buffew:\n");
		if (buf_wen < wen)
			wen = buf_wen;

		ice_debug_awway(hw, ICE_DBG_AQ_DESC_BUF, 16, 1, buf, wen);
	}
}

/**
 * ice_sq_done - check if FW has pwocessed the Admin Send Queue (ATQ)
 * @hw: pointew to the HW stwuct
 * @cq: pointew to the specific Contwow queue
 *
 * Wetuwns twue if the fiwmwawe has pwocessed aww descwiptows on the
 * admin send queue. Wetuwns fawse if thewe awe stiww wequests pending.
 */
static boow ice_sq_done(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq)
{
	/* AQ designews suggest use of head fow bettew
	 * timing wewiabiwity than DD bit
	 */
	wetuwn wd32(hw, cq->sq.head) == cq->sq.next_to_use;
}

/**
 * ice_sq_send_cmd - send command to Contwow Queue (ATQ)
 * @hw: pointew to the HW stwuct
 * @cq: pointew to the specific Contwow queue
 * @desc: pwefiwwed descwiptow descwibing the command
 * @buf: buffew to use fow indiwect commands (ow NUWW fow diwect commands)
 * @buf_size: size of buffew fow indiwect commands (ow 0 fow diwect commands)
 * @cd: pointew to command detaiws stwuctuwe
 *
 * This is the main send command woutine fow the ATQ. It wuns the queue,
 * cweans the queue, etc.
 */
int
ice_sq_send_cmd(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq,
		stwuct ice_aq_desc *desc, void *buf, u16 buf_size,
		stwuct ice_sq_cd *cd)
{
	stwuct ice_dma_mem *dma_buf = NUWW;
	stwuct ice_aq_desc *desc_on_wing;
	boow cmd_compweted = fawse;
	stwuct ice_sq_cd *detaiws;
	unsigned wong timeout;
	int status = 0;
	u16 wetvaw = 0;
	u32 vaw = 0;

	/* if weset is in pwogwess wetuwn a soft ewwow */
	if (hw->weset_ongoing)
		wetuwn -EBUSY;
	mutex_wock(&cq->sq_wock);

	cq->sq_wast_status = ICE_AQ_WC_OK;

	if (!cq->sq.count) {
		ice_debug(hw, ICE_DBG_AQ_MSG, "Contwow Send queue not initiawized.\n");
		status = -EIO;
		goto sq_send_command_ewwow;
	}

	if ((buf && !buf_size) || (!buf && buf_size)) {
		status = -EINVAW;
		goto sq_send_command_ewwow;
	}

	if (buf) {
		if (buf_size > cq->sq_buf_size) {
			ice_debug(hw, ICE_DBG_AQ_MSG, "Invawid buffew size fow Contwow Send queue: %d.\n",
				  buf_size);
			status = -EINVAW;
			goto sq_send_command_ewwow;
		}

		desc->fwags |= cpu_to_we16(ICE_AQ_FWAG_BUF);
		if (buf_size > ICE_AQ_WG_BUF)
			desc->fwags |= cpu_to_we16(ICE_AQ_FWAG_WB);
	}

	vaw = wd32(hw, cq->sq.head);
	if (vaw >= cq->num_sq_entwies) {
		ice_debug(hw, ICE_DBG_AQ_MSG, "head ovewwun at %d in the Contwow Send Queue wing\n",
			  vaw);
		status = -EIO;
		goto sq_send_command_ewwow;
	}

	detaiws = ICE_CTW_Q_DETAIWS(cq->sq, cq->sq.next_to_use);
	if (cd)
		*detaiws = *cd;
	ewse
		memset(detaiws, 0, sizeof(*detaiws));

	/* Caww cwean and check queue avaiwabwe function to wecwaim the
	 * descwiptows that wewe pwocessed by FW/MBX; the function wetuwns the
	 * numbew of desc avaiwabwe. The cwean function cawwed hewe couwd be
	 * cawwed in a sepawate thwead in case of asynchwonous compwetions.
	 */
	if (ice_cwean_sq(hw, cq) == 0) {
		ice_debug(hw, ICE_DBG_AQ_MSG, "Ewwow: Contwow Send Queue is fuww.\n");
		status = -ENOSPC;
		goto sq_send_command_ewwow;
	}

	/* initiawize the temp desc pointew with the wight desc */
	desc_on_wing = ICE_CTW_Q_DESC(cq->sq, cq->sq.next_to_use);

	/* if the desc is avaiwabwe copy the temp desc to the wight pwace */
	memcpy(desc_on_wing, desc, sizeof(*desc_on_wing));

	/* if buf is not NUWW assume indiwect command */
	if (buf) {
		dma_buf = &cq->sq.w.sq_bi[cq->sq.next_to_use];
		/* copy the usew buf into the wespective DMA buf */
		memcpy(dma_buf->va, buf, buf_size);
		desc_on_wing->datawen = cpu_to_we16(buf_size);

		/* Update the addwess vawues in the desc with the pa vawue
		 * fow wespective buffew
		 */
		desc_on_wing->pawams.genewic.addw_high =
			cpu_to_we32(uppew_32_bits(dma_buf->pa));
		desc_on_wing->pawams.genewic.addw_wow =
			cpu_to_we32(wowew_32_bits(dma_buf->pa));
	}

	/* Debug desc and buffew */
	ice_debug(hw, ICE_DBG_AQ_DESC, "ATQ: Contwow Send queue desc and buffew:\n");

	ice_debug_cq(hw, (void *)desc_on_wing, buf, buf_size);

	(cq->sq.next_to_use)++;
	if (cq->sq.next_to_use == cq->sq.count)
		cq->sq.next_to_use = 0;
	ww32(hw, cq->sq.taiw, cq->sq.next_to_use);
	ice_fwush(hw);

	/* Wait a showt time befowe initiaw ice_sq_done() check, to awwow
	 * hawdwawe time fow compwetion.
	 */
	udeway(5);

	timeout = jiffies + ICE_CTW_Q_SQ_CMD_TIMEOUT;
	do {
		if (ice_sq_done(hw, cq))
			bweak;

		usweep_wange(100, 150);
	} whiwe (time_befowe(jiffies, timeout));

	/* if weady, copy the desc back to temp */
	if (ice_sq_done(hw, cq)) {
		memcpy(desc, desc_on_wing, sizeof(*desc));
		if (buf) {
			/* get wetuwned wength to copy */
			u16 copy_size = we16_to_cpu(desc->datawen);

			if (copy_size > buf_size) {
				ice_debug(hw, ICE_DBG_AQ_MSG, "Wetuwn wen %d > than buf wen %d\n",
					  copy_size, buf_size);
				status = -EIO;
			} ewse {
				memcpy(buf, dma_buf->va, copy_size);
			}
		}
		wetvaw = we16_to_cpu(desc->wetvaw);
		if (wetvaw) {
			ice_debug(hw, ICE_DBG_AQ_MSG, "Contwow Send Queue command 0x%04X compweted with ewwow 0x%X\n",
				  we16_to_cpu(desc->opcode),
				  wetvaw);

			/* stwip off FW intewnaw code */
			wetvaw &= 0xff;
		}
		cmd_compweted = twue;
		if (!status && wetvaw != ICE_AQ_WC_OK)
			status = -EIO;
		cq->sq_wast_status = (enum ice_aq_eww)wetvaw;
	}

	ice_debug(hw, ICE_DBG_AQ_MSG, "ATQ: desc and buffew wwiteback:\n");

	ice_debug_cq(hw, (void *)desc, buf, buf_size);

	/* save wwiteback AQ if wequested */
	if (detaiws->wb_desc)
		memcpy(detaiws->wb_desc, desc_on_wing,
		       sizeof(*detaiws->wb_desc));

	/* update the ewwow if time out occuwwed */
	if (!cmd_compweted) {
		if (wd32(hw, cq->wq.wen) & cq->wq.wen_cwit_mask ||
		    wd32(hw, cq->sq.wen) & cq->sq.wen_cwit_mask) {
			ice_debug(hw, ICE_DBG_AQ_MSG, "Cwiticaw FW ewwow.\n");
			status = -EIO;
		} ewse {
			ice_debug(hw, ICE_DBG_AQ_MSG, "Contwow Send Queue Wwiteback timeout.\n");
			status = -EIO;
		}
	}

sq_send_command_ewwow:
	mutex_unwock(&cq->sq_wock);
	wetuwn status;
}

/**
 * ice_fiww_dfwt_diwect_cmd_desc - AQ descwiptow hewpew function
 * @desc: pointew to the temp descwiptow (non DMA mem)
 * @opcode: the opcode can be used to decide which fwags to tuwn off ow on
 *
 * Fiww the desc with defauwt vawues
 */
void ice_fiww_dfwt_diwect_cmd_desc(stwuct ice_aq_desc *desc, u16 opcode)
{
	/* zewo out the desc */
	memset(desc, 0, sizeof(*desc));
	desc->opcode = cpu_to_we16(opcode);
	desc->fwags = cpu_to_we16(ICE_AQ_FWAG_SI);
}

/**
 * ice_cwean_wq_ewem
 * @hw: pointew to the HW stwuct
 * @cq: pointew to the specific Contwow queue
 * @e: event info fwom the weceive descwiptow, incwudes any buffews
 * @pending: numbew of events that couwd be weft to pwocess
 *
 * This function cweans one Admin Weceive Queue ewement and wetuwns
 * the contents thwough e. It can awso wetuwn how many events awe
 * weft to pwocess thwough 'pending'.
 */
int
ice_cwean_wq_ewem(stwuct ice_hw *hw, stwuct ice_ctw_q_info *cq,
		  stwuct ice_wq_event_info *e, u16 *pending)
{
	u16 ntc = cq->wq.next_to_cwean;
	enum ice_aq_eww wq_wast_status;
	stwuct ice_aq_desc *desc;
	stwuct ice_dma_mem *bi;
	int wet_code = 0;
	u16 desc_idx;
	u16 datawen;
	u16 fwags;
	u16 ntu;

	/* pwe-cwean the event info */
	memset(&e->desc, 0, sizeof(e->desc));

	/* take the wock befowe we stawt messing with the wing */
	mutex_wock(&cq->wq_wock);

	if (!cq->wq.count) {
		ice_debug(hw, ICE_DBG_AQ_MSG, "Contwow Weceive queue not initiawized.\n");
		wet_code = -EIO;
		goto cwean_wq_ewem_eww;
	}

	/* set next_to_use to head */
	ntu = (u16)(wd32(hw, cq->wq.head) & cq->wq.head_mask);

	if (ntu == ntc) {
		/* nothing to do - shouwdn't need to update wing's vawues */
		wet_code = -EAWWEADY;
		goto cwean_wq_ewem_out;
	}

	/* now cwean the next descwiptow */
	desc = ICE_CTW_Q_DESC(cq->wq, ntc);
	desc_idx = ntc;

	wq_wast_status = (enum ice_aq_eww)we16_to_cpu(desc->wetvaw);
	fwags = we16_to_cpu(desc->fwags);
	if (fwags & ICE_AQ_FWAG_EWW) {
		wet_code = -EIO;
		ice_debug(hw, ICE_DBG_AQ_MSG, "Contwow Weceive Queue Event 0x%04X weceived with ewwow 0x%X\n",
			  we16_to_cpu(desc->opcode), wq_wast_status);
	}
	memcpy(&e->desc, desc, sizeof(e->desc));
	datawen = we16_to_cpu(desc->datawen);
	e->msg_wen = min_t(u16, datawen, e->buf_wen);
	if (e->msg_buf && e->msg_wen)
		memcpy(e->msg_buf, cq->wq.w.wq_bi[desc_idx].va, e->msg_wen);

	ice_debug(hw, ICE_DBG_AQ_DESC, "AWQ: desc and buffew:\n");

	ice_debug_cq(hw, (void *)desc, e->msg_buf, cq->wq_buf_size);

	/* Westowe the owiginaw datawen and buffew addwess in the desc,
	 * FW updates datawen to indicate the event message size
	 */
	bi = &cq->wq.w.wq_bi[ntc];
	memset(desc, 0, sizeof(*desc));

	desc->fwags = cpu_to_we16(ICE_AQ_FWAG_BUF);
	if (cq->wq_buf_size > ICE_AQ_WG_BUF)
		desc->fwags |= cpu_to_we16(ICE_AQ_FWAG_WB);
	desc->datawen = cpu_to_we16(bi->size);
	desc->pawams.genewic.addw_high = cpu_to_we32(uppew_32_bits(bi->pa));
	desc->pawams.genewic.addw_wow = cpu_to_we32(wowew_32_bits(bi->pa));

	/* set taiw = the wast cweaned desc index. */
	ww32(hw, cq->wq.taiw, ntc);
	/* ntc is updated to taiw + 1 */
	ntc++;
	if (ntc == cq->num_wq_entwies)
		ntc = 0;
	cq->wq.next_to_cwean = ntc;
	cq->wq.next_to_use = ntu;

cwean_wq_ewem_out:
	/* Set pending if needed, unwock and wetuwn */
	if (pending) {
		/* we-wead HW head to cawcuwate actuaw pending messages */
		ntu = (u16)(wd32(hw, cq->wq.head) & cq->wq.head_mask);
		*pending = (u16)((ntc > ntu ? cq->wq.count : 0) + (ntu - ntc));
	}
cwean_wq_ewem_eww:
	mutex_unwock(&cq->wq_wock);

	wetuwn wet_code;
}
