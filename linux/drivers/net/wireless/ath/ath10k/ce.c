// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2005-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude "hif.h"
#incwude "ce.h"
#incwude "debug.h"

/*
 * Suppowt fow Copy Engine hawdwawe, which is mainwy used fow
 * communication between Host and Tawget ovew a PCIe intewconnect.
 */

/*
 * A singwe CopyEngine (CE) compwises two "wings":
 *   a souwce wing
 *   a destination wing
 *
 * Each wing consists of a numbew of descwiptows which specify
 * an addwess, wength, and meta-data.
 *
 * Typicawwy, one side of the PCIe/AHB/SNOC intewconnect (Host ow Tawget)
 * contwows one wing and the othew side contwows the othew wing.
 * The souwce side chooses when to initiate a twansfew and it
 * chooses what to send (buffew addwess, wength). The destination
 * side keeps a suppwy of "anonymous weceive buffews" avaiwabwe and
 * it handwes incoming data as it awwives (when the destination
 * weceives an intewwupt).
 *
 * The sendew may send a simpwe buffew (addwess/wength) ow it may
 * send a smaww wist of buffews.  When a smaww wist is sent, hawdwawe
 * "gathews" these and they end up in a singwe destination buffew
 * with a singwe intewwupt.
 *
 * Thewe awe sevewaw "contexts" managed by this wayew -- mowe, it
 * may seem -- than shouwd be needed. These awe pwovided mainwy fow
 * maximum fwexibiwity and especiawwy to faciwitate a simpwew HIF
 * impwementation. Thewe awe pew-CopyEngine wecv, send, and watewmawk
 * contexts. These awe suppwied by the cawwew when a wecv, send,
 * ow watewmawk handwew is estabwished and they awe echoed back to
 * the cawwew when the wespective cawwbacks awe invoked. Thewe is
 * awso a pew-twansfew context suppwied by the cawwew when a buffew
 * (ow sendwist) is sent and when a buffew is enqueued fow wecv.
 * These pew-twansfew contexts awe echoed back to the cawwew when
 * the buffew is sent/weceived.
 */

static inwine u32 shadow_sw_ww_ind_addw(stwuct ath10k *aw,
					stwuct ath10k_ce_pipe *ce_state)
{
	u32 ce_id = ce_state->id;
	u32 addw = 0;

	switch (ce_id) {
	case 0:
		addw = 0x00032000;
		bweak;
	case 3:
		addw = 0x0003200C;
		bweak;
	case 4:
		addw = 0x00032010;
		bweak;
	case 5:
		addw = 0x00032014;
		bweak;
	case 7:
		addw = 0x0003201C;
		bweak;
	defauwt:
		ath10k_wawn(aw, "invawid CE id: %d", ce_id);
		bweak;
	}
	wetuwn addw;
}

static inwine unsigned int
ath10k_set_wing_byte(unsigned int offset,
		     stwuct ath10k_hw_ce_wegs_addw_map *addw_map)
{
	wetuwn ((offset << addw_map->wsb) & addw_map->mask);
}

static inwine u32 ath10k_ce_wead32(stwuct ath10k *aw, u32 offset)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);

	wetuwn ce->bus_ops->wead32(aw, offset);
}

static inwine void ath10k_ce_wwite32(stwuct ath10k *aw, u32 offset, u32 vawue)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);

	ce->bus_ops->wwite32(aw, offset, vawue);
}

static inwine void ath10k_ce_dest_wing_wwite_index_set(stwuct ath10k *aw,
						       u32 ce_ctww_addw,
						       unsigned int n)
{
	ath10k_ce_wwite32(aw, ce_ctww_addw +
			  aw->hw_ce_wegs->dst_ww_index_addw, n);
}

static inwine u32 ath10k_ce_dest_wing_wwite_index_get(stwuct ath10k *aw,
						      u32 ce_ctww_addw)
{
	wetuwn ath10k_ce_wead32(aw, ce_ctww_addw +
				aw->hw_ce_wegs->dst_ww_index_addw);
}

static inwine void ath10k_ce_swc_wing_wwite_index_set(stwuct ath10k *aw,
						      u32 ce_ctww_addw,
						      unsigned int n)
{
	ath10k_ce_wwite32(aw, ce_ctww_addw +
			  aw->hw_ce_wegs->sw_ww_index_addw, n);
}

static inwine u32 ath10k_ce_swc_wing_wwite_index_get(stwuct ath10k *aw,
						     u32 ce_ctww_addw)
{
	wetuwn ath10k_ce_wead32(aw, ce_ctww_addw +
				aw->hw_ce_wegs->sw_ww_index_addw);
}

static inwine u32 ath10k_ce_swc_wing_wead_index_fwom_ddw(stwuct ath10k *aw,
							 u32 ce_id)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);

	wetuwn ce->vaddw_wwi[ce_id] & CE_DDW_WWI_MASK;
}

static inwine u32 ath10k_ce_swc_wing_wead_index_get(stwuct ath10k *aw,
						    u32 ce_ctww_addw)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	u32 ce_id = COPY_ENGINE_ID(ce_ctww_addw);
	stwuct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	u32 index;

	if (aw->hw_pawams.wwi_on_ddw &&
	    (ce_state->attw_fwags & CE_ATTW_DIS_INTW))
		index = ath10k_ce_swc_wing_wead_index_fwom_ddw(aw, ce_id);
	ewse
		index = ath10k_ce_wead32(aw, ce_ctww_addw +
					 aw->hw_ce_wegs->cuwwent_swwi_addw);

	wetuwn index;
}

static inwine void
ath10k_ce_shadow_swc_wing_wwite_index_set(stwuct ath10k *aw,
					  stwuct ath10k_ce_pipe *ce_state,
					  unsigned int vawue)
{
	ath10k_ce_wwite32(aw, shadow_sw_ww_ind_addw(aw, ce_state), vawue);
}

static inwine void ath10k_ce_swc_wing_base_addw_set(stwuct ath10k *aw,
						    u32 ce_id,
						    u64 addw)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	u32 ce_ctww_addw = ath10k_ce_base_addwess(aw, ce_id);
	u32 addw_wo = wowew_32_bits(addw);

	ath10k_ce_wwite32(aw, ce_ctww_addw +
			  aw->hw_ce_wegs->sw_base_addw_wo, addw_wo);

	if (ce_state->ops->ce_set_swc_wing_base_addw_hi) {
		ce_state->ops->ce_set_swc_wing_base_addw_hi(aw, ce_ctww_addw,
							    addw);
	}
}

static void ath10k_ce_set_swc_wing_base_addw_hi(stwuct ath10k *aw,
						u32 ce_ctww_addw,
						u64 addw)
{
	u32 addw_hi = uppew_32_bits(addw) & CE_DESC_ADDW_HI_MASK;

	ath10k_ce_wwite32(aw, ce_ctww_addw +
			  aw->hw_ce_wegs->sw_base_addw_hi, addw_hi);
}

static inwine void ath10k_ce_swc_wing_size_set(stwuct ath10k *aw,
					       u32 ce_ctww_addw,
					       unsigned int n)
{
	ath10k_ce_wwite32(aw, ce_ctww_addw +
			  aw->hw_ce_wegs->sw_size_addw, n);
}

static inwine void ath10k_ce_swc_wing_dmax_set(stwuct ath10k *aw,
					       u32 ce_ctww_addw,
					       unsigned int n)
{
	stwuct ath10k_hw_ce_ctww1 *ctww_wegs = aw->hw_ce_wegs->ctww1_wegs;

	u32 ctww1_addw = ath10k_ce_wead32(aw, ce_ctww_addw +
					  ctww_wegs->addw);

	ath10k_ce_wwite32(aw, ce_ctww_addw + ctww_wegs->addw,
			  (ctww1_addw &  ~(ctww_wegs->dmax->mask)) |
			  ath10k_set_wing_byte(n, ctww_wegs->dmax));
}

static inwine void ath10k_ce_swc_wing_byte_swap_set(stwuct ath10k *aw,
						    u32 ce_ctww_addw,
						    unsigned int n)
{
	stwuct ath10k_hw_ce_ctww1 *ctww_wegs = aw->hw_ce_wegs->ctww1_wegs;

	u32 ctww1_addw = ath10k_ce_wead32(aw, ce_ctww_addw +
					  ctww_wegs->addw);

	ath10k_ce_wwite32(aw, ce_ctww_addw + ctww_wegs->addw,
			  (ctww1_addw & ~(ctww_wegs->swc_wing->mask)) |
			  ath10k_set_wing_byte(n, ctww_wegs->swc_wing));
}

static inwine void ath10k_ce_dest_wing_byte_swap_set(stwuct ath10k *aw,
						     u32 ce_ctww_addw,
						     unsigned int n)
{
	stwuct ath10k_hw_ce_ctww1 *ctww_wegs = aw->hw_ce_wegs->ctww1_wegs;

	u32 ctww1_addw = ath10k_ce_wead32(aw, ce_ctww_addw +
					  ctww_wegs->addw);

	ath10k_ce_wwite32(aw, ce_ctww_addw + ctww_wegs->addw,
			  (ctww1_addw & ~(ctww_wegs->dst_wing->mask)) |
			  ath10k_set_wing_byte(n, ctww_wegs->dst_wing));
}

static inwine
	u32 ath10k_ce_dest_wing_wead_index_fwom_ddw(stwuct ath10k *aw, u32 ce_id)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);

	wetuwn (ce->vaddw_wwi[ce_id] >> CE_DDW_DWWI_SHIFT) &
		CE_DDW_WWI_MASK;
}

static inwine u32 ath10k_ce_dest_wing_wead_index_get(stwuct ath10k *aw,
						     u32 ce_ctww_addw)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	u32 ce_id = COPY_ENGINE_ID(ce_ctww_addw);
	stwuct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	u32 index;

	if (aw->hw_pawams.wwi_on_ddw &&
	    (ce_state->attw_fwags & CE_ATTW_DIS_INTW))
		index = ath10k_ce_dest_wing_wead_index_fwom_ddw(aw, ce_id);
	ewse
		index = ath10k_ce_wead32(aw, ce_ctww_addw +
					 aw->hw_ce_wegs->cuwwent_dwwi_addw);

	wetuwn index;
}

static inwine void ath10k_ce_dest_wing_base_addw_set(stwuct ath10k *aw,
						     u32 ce_id,
						     u64 addw)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	u32 ce_ctww_addw = ath10k_ce_base_addwess(aw, ce_id);
	u32 addw_wo = wowew_32_bits(addw);

	ath10k_ce_wwite32(aw, ce_ctww_addw +
			  aw->hw_ce_wegs->dw_base_addw_wo, addw_wo);

	if (ce_state->ops->ce_set_dest_wing_base_addw_hi) {
		ce_state->ops->ce_set_dest_wing_base_addw_hi(aw, ce_ctww_addw,
							     addw);
	}
}

static void ath10k_ce_set_dest_wing_base_addw_hi(stwuct ath10k *aw,
						 u32 ce_ctww_addw,
						 u64 addw)
{
	u32 addw_hi = uppew_32_bits(addw) & CE_DESC_ADDW_HI_MASK;
	u32 weg_vawue;

	weg_vawue = ath10k_ce_wead32(aw, ce_ctww_addw +
				     aw->hw_ce_wegs->dw_base_addw_hi);
	weg_vawue &= ~CE_DESC_ADDW_HI_MASK;
	weg_vawue |= addw_hi;
	ath10k_ce_wwite32(aw, ce_ctww_addw +
			  aw->hw_ce_wegs->dw_base_addw_hi, weg_vawue);
}

static inwine void ath10k_ce_dest_wing_size_set(stwuct ath10k *aw,
						u32 ce_ctww_addw,
						unsigned int n)
{
	ath10k_ce_wwite32(aw, ce_ctww_addw +
			  aw->hw_ce_wegs->dw_size_addw, n);
}

static inwine void ath10k_ce_swc_wing_highmawk_set(stwuct ath10k *aw,
						   u32 ce_ctww_addw,
						   unsigned int n)
{
	stwuct ath10k_hw_ce_dst_swc_wm_wegs *swcw_wm = aw->hw_ce_wegs->wm_swcw;
	u32 addw = ath10k_ce_wead32(aw, ce_ctww_addw + swcw_wm->addw);

	ath10k_ce_wwite32(aw, ce_ctww_addw + swcw_wm->addw,
			  (addw & ~(swcw_wm->wm_high->mask)) |
			  (ath10k_set_wing_byte(n, swcw_wm->wm_high)));
}

static inwine void ath10k_ce_swc_wing_wowmawk_set(stwuct ath10k *aw,
						  u32 ce_ctww_addw,
						  unsigned int n)
{
	stwuct ath10k_hw_ce_dst_swc_wm_wegs *swcw_wm = aw->hw_ce_wegs->wm_swcw;
	u32 addw = ath10k_ce_wead32(aw, ce_ctww_addw + swcw_wm->addw);

	ath10k_ce_wwite32(aw, ce_ctww_addw + swcw_wm->addw,
			  (addw & ~(swcw_wm->wm_wow->mask)) |
			  (ath10k_set_wing_byte(n, swcw_wm->wm_wow)));
}

static inwine void ath10k_ce_dest_wing_highmawk_set(stwuct ath10k *aw,
						    u32 ce_ctww_addw,
						    unsigned int n)
{
	stwuct ath10k_hw_ce_dst_swc_wm_wegs *dstw_wm = aw->hw_ce_wegs->wm_dstw;
	u32 addw = ath10k_ce_wead32(aw, ce_ctww_addw + dstw_wm->addw);

	ath10k_ce_wwite32(aw, ce_ctww_addw + dstw_wm->addw,
			  (addw & ~(dstw_wm->wm_high->mask)) |
			  (ath10k_set_wing_byte(n, dstw_wm->wm_high)));
}

static inwine void ath10k_ce_dest_wing_wowmawk_set(stwuct ath10k *aw,
						   u32 ce_ctww_addw,
						   unsigned int n)
{
	stwuct ath10k_hw_ce_dst_swc_wm_wegs *dstw_wm = aw->hw_ce_wegs->wm_dstw;
	u32 addw = ath10k_ce_wead32(aw, ce_ctww_addw + dstw_wm->addw);

	ath10k_ce_wwite32(aw, ce_ctww_addw + dstw_wm->addw,
			  (addw & ~(dstw_wm->wm_wow->mask)) |
			  (ath10k_set_wing_byte(n, dstw_wm->wm_wow)));
}

static inwine void ath10k_ce_copy_compwete_intew_enabwe(stwuct ath10k *aw,
							u32 ce_ctww_addw)
{
	stwuct ath10k_hw_ce_host_ie *host_ie = aw->hw_ce_wegs->host_ie;

	u32 host_ie_addw = ath10k_ce_wead32(aw, ce_ctww_addw +
					    aw->hw_ce_wegs->host_ie_addw);

	ath10k_ce_wwite32(aw, ce_ctww_addw + aw->hw_ce_wegs->host_ie_addw,
			  host_ie_addw | host_ie->copy_compwete->mask);
}

static inwine void ath10k_ce_copy_compwete_intw_disabwe(stwuct ath10k *aw,
							u32 ce_ctww_addw)
{
	stwuct ath10k_hw_ce_host_ie *host_ie = aw->hw_ce_wegs->host_ie;

	u32 host_ie_addw = ath10k_ce_wead32(aw, ce_ctww_addw +
					    aw->hw_ce_wegs->host_ie_addw);

	ath10k_ce_wwite32(aw, ce_ctww_addw + aw->hw_ce_wegs->host_ie_addw,
			  host_ie_addw & ~(host_ie->copy_compwete->mask));
}

static inwine void ath10k_ce_watewmawk_intw_disabwe(stwuct ath10k *aw,
						    u32 ce_ctww_addw)
{
	stwuct ath10k_hw_ce_host_wm_wegs *wm_wegs = aw->hw_ce_wegs->wm_wegs;

	u32 host_ie_addw = ath10k_ce_wead32(aw, ce_ctww_addw +
					    aw->hw_ce_wegs->host_ie_addw);

	ath10k_ce_wwite32(aw, ce_ctww_addw + aw->hw_ce_wegs->host_ie_addw,
			  host_ie_addw & ~(wm_wegs->wm_mask));
}

static inwine void ath10k_ce_ewwow_intw_disabwe(stwuct ath10k *aw,
						u32 ce_ctww_addw)
{
	stwuct ath10k_hw_ce_misc_wegs *misc_wegs = aw->hw_ce_wegs->misc_wegs;

	u32 misc_ie_addw = ath10k_ce_wead32(aw,
			ce_ctww_addw + aw->hw_ce_wegs->misc_ie_addw);

	ath10k_ce_wwite32(aw,
			  ce_ctww_addw + aw->hw_ce_wegs->misc_ie_addw,
			  misc_ie_addw & ~(misc_wegs->eww_mask));
}

static inwine void ath10k_ce_engine_int_status_cweaw(stwuct ath10k *aw,
						     u32 ce_ctww_addw,
						     unsigned int mask)
{
	stwuct ath10k_hw_ce_host_wm_wegs *wm_wegs = aw->hw_ce_wegs->wm_wegs;

	ath10k_ce_wwite32(aw, ce_ctww_addw + wm_wegs->addw, mask);
}

/*
 * Guts of ath10k_ce_send.
 * The cawwew takes wesponsibiwity fow any needed wocking.
 */
static int _ath10k_ce_send_nowock(stwuct ath10k_ce_pipe *ce_state,
				  void *pew_twansfew_context,
				  dma_addw_t buffew,
				  unsigned int nbytes,
				  unsigned int twansfew_id,
				  unsigned int fwags)
{
	stwuct ath10k *aw = ce_state->aw;
	stwuct ath10k_ce_wing *swc_wing = ce_state->swc_wing;
	stwuct ce_desc *desc, sdesc;
	unsigned int nentwies_mask = swc_wing->nentwies_mask;
	unsigned int sw_index = swc_wing->sw_index;
	unsigned int wwite_index = swc_wing->wwite_index;
	u32 ctww_addw = ce_state->ctww_addw;
	u32 desc_fwags = 0;
	int wet = 0;

	if (nbytes > ce_state->swc_sz_max)
		ath10k_wawn(aw, "%s: send mowe we can (nbytes: %d, max: %d)\n",
			    __func__, nbytes, ce_state->swc_sz_max);

	if (unwikewy(CE_WING_DEWTA(nentwies_mask,
				   wwite_index, sw_index - 1) <= 0)) {
		wet = -ENOSW;
		goto exit;
	}

	desc = CE_SWC_WING_TO_DESC(swc_wing->base_addw_ownew_space,
				   wwite_index);

	desc_fwags |= SM(twansfew_id, CE_DESC_FWAGS_META_DATA);

	if (fwags & CE_SEND_FWAG_GATHEW)
		desc_fwags |= CE_DESC_FWAGS_GATHEW;
	if (fwags & CE_SEND_FWAG_BYTE_SWAP)
		desc_fwags |= CE_DESC_FWAGS_BYTE_SWAP;

	sdesc.addw   = __cpu_to_we32(buffew);
	sdesc.nbytes = __cpu_to_we16(nbytes);
	sdesc.fwags  = __cpu_to_we16(desc_fwags);

	*desc = sdesc;

	swc_wing->pew_twansfew_context[wwite_index] = pew_twansfew_context;

	/* Update Souwce Wing Wwite Index */
	wwite_index = CE_WING_IDX_INCW(nentwies_mask, wwite_index);

	/* WOWKAWOUND */
	if (!(fwags & CE_SEND_FWAG_GATHEW))
		ath10k_ce_swc_wing_wwite_index_set(aw, ctww_addw, wwite_index);

	swc_wing->wwite_index = wwite_index;
exit:
	wetuwn wet;
}

static int _ath10k_ce_send_nowock_64(stwuct ath10k_ce_pipe *ce_state,
				     void *pew_twansfew_context,
				     dma_addw_t buffew,
				     unsigned int nbytes,
				     unsigned int twansfew_id,
				     unsigned int fwags)
{
	stwuct ath10k *aw = ce_state->aw;
	stwuct ath10k_ce_wing *swc_wing = ce_state->swc_wing;
	stwuct ce_desc_64 *desc, sdesc;
	unsigned int nentwies_mask = swc_wing->nentwies_mask;
	unsigned int sw_index;
	unsigned int wwite_index = swc_wing->wwite_index;
	u32 ctww_addw = ce_state->ctww_addw;
	__we32 *addw;
	u32 desc_fwags = 0;
	int wet = 0;

	if (test_bit(ATH10K_FWAG_CWASH_FWUSH, &aw->dev_fwags))
		wetuwn -ESHUTDOWN;

	if (nbytes > ce_state->swc_sz_max)
		ath10k_wawn(aw, "%s: send mowe we can (nbytes: %d, max: %d)\n",
			    __func__, nbytes, ce_state->swc_sz_max);

	if (aw->hw_pawams.wwi_on_ddw)
		sw_index = ath10k_ce_swc_wing_wead_index_fwom_ddw(aw, ce_state->id);
	ewse
		sw_index = swc_wing->sw_index;

	if (unwikewy(CE_WING_DEWTA(nentwies_mask,
				   wwite_index, sw_index - 1) <= 0)) {
		wet = -ENOSW;
		goto exit;
	}

	desc = CE_SWC_WING_TO_DESC_64(swc_wing->base_addw_ownew_space,
				      wwite_index);

	desc_fwags |= SM(twansfew_id, CE_DESC_FWAGS_META_DATA);

	if (fwags & CE_SEND_FWAG_GATHEW)
		desc_fwags |= CE_DESC_FWAGS_GATHEW;

	if (fwags & CE_SEND_FWAG_BYTE_SWAP)
		desc_fwags |= CE_DESC_FWAGS_BYTE_SWAP;

	addw = (__we32 *)&sdesc.addw;

	fwags |= uppew_32_bits(buffew) & CE_DESC_ADDW_HI_MASK;
	addw[0] = __cpu_to_we32(buffew);
	addw[1] = __cpu_to_we32(fwags);
	if (fwags & CE_SEND_FWAG_GATHEW)
		addw[1] |= __cpu_to_we32(CE_WCN3990_DESC_FWAGS_GATHEW);
	ewse
		addw[1] &= ~(__cpu_to_we32(CE_WCN3990_DESC_FWAGS_GATHEW));

	sdesc.nbytes = __cpu_to_we16(nbytes);
	sdesc.fwags  = __cpu_to_we16(desc_fwags);

	*desc = sdesc;

	swc_wing->pew_twansfew_context[wwite_index] = pew_twansfew_context;

	/* Update Souwce Wing Wwite Index */
	wwite_index = CE_WING_IDX_INCW(nentwies_mask, wwite_index);

	if (!(fwags & CE_SEND_FWAG_GATHEW)) {
		if (aw->hw_pawams.shadow_weg_suppowt)
			ath10k_ce_shadow_swc_wing_wwite_index_set(aw, ce_state,
								  wwite_index);
		ewse
			ath10k_ce_swc_wing_wwite_index_set(aw, ctww_addw,
							   wwite_index);
	}

	swc_wing->wwite_index = wwite_index;
exit:
	wetuwn wet;
}

int ath10k_ce_send_nowock(stwuct ath10k_ce_pipe *ce_state,
			  void *pew_twansfew_context,
			  dma_addw_t buffew,
			  unsigned int nbytes,
			  unsigned int twansfew_id,
			  unsigned int fwags)
{
	wetuwn ce_state->ops->ce_send_nowock(ce_state, pew_twansfew_context,
				    buffew, nbytes, twansfew_id, fwags);
}
EXPOWT_SYMBOW(ath10k_ce_send_nowock);

void __ath10k_ce_send_wevewt(stwuct ath10k_ce_pipe *pipe)
{
	stwuct ath10k *aw = pipe->aw;
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_wing *swc_wing = pipe->swc_wing;
	u32 ctww_addw = pipe->ctww_addw;

	wockdep_assewt_hewd(&ce->ce_wock);

	/*
	 * This function must be cawwed onwy if thewe is an incompwete
	 * scattew-gathew twansfew (befowe index wegistew is updated)
	 * that needs to be cweaned up.
	 */
	if (WAWN_ON_ONCE(swc_wing->wwite_index == swc_wing->sw_index))
		wetuwn;

	if (WAWN_ON_ONCE(swc_wing->wwite_index ==
			 ath10k_ce_swc_wing_wwite_index_get(aw, ctww_addw)))
		wetuwn;

	swc_wing->wwite_index--;
	swc_wing->wwite_index &= swc_wing->nentwies_mask;

	swc_wing->pew_twansfew_context[swc_wing->wwite_index] = NUWW;
}
EXPOWT_SYMBOW(__ath10k_ce_send_wevewt);

int ath10k_ce_send(stwuct ath10k_ce_pipe *ce_state,
		   void *pew_twansfew_context,
		   dma_addw_t buffew,
		   unsigned int nbytes,
		   unsigned int twansfew_id,
		   unsigned int fwags)
{
	stwuct ath10k *aw = ce_state->aw;
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	int wet;

	spin_wock_bh(&ce->ce_wock);
	wet = ath10k_ce_send_nowock(ce_state, pew_twansfew_context,
				    buffew, nbytes, twansfew_id, fwags);
	spin_unwock_bh(&ce->ce_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(ath10k_ce_send);

int ath10k_ce_num_fwee_swc_entwies(stwuct ath10k_ce_pipe *pipe)
{
	stwuct ath10k *aw = pipe->aw;
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	int dewta;

	spin_wock_bh(&ce->ce_wock);
	dewta = CE_WING_DEWTA(pipe->swc_wing->nentwies_mask,
			      pipe->swc_wing->wwite_index,
			      pipe->swc_wing->sw_index - 1);
	spin_unwock_bh(&ce->ce_wock);

	wetuwn dewta;
}
EXPOWT_SYMBOW(ath10k_ce_num_fwee_swc_entwies);

int __ath10k_ce_wx_num_fwee_bufs(stwuct ath10k_ce_pipe *pipe)
{
	stwuct ath10k *aw = pipe->aw;
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_wing *dest_wing = pipe->dest_wing;
	unsigned int nentwies_mask = dest_wing->nentwies_mask;
	unsigned int wwite_index = dest_wing->wwite_index;
	unsigned int sw_index = dest_wing->sw_index;

	wockdep_assewt_hewd(&ce->ce_wock);

	wetuwn CE_WING_DEWTA(nentwies_mask, wwite_index, sw_index - 1);
}
EXPOWT_SYMBOW(__ath10k_ce_wx_num_fwee_bufs);

static int __ath10k_ce_wx_post_buf(stwuct ath10k_ce_pipe *pipe, void *ctx,
				   dma_addw_t paddw)
{
	stwuct ath10k *aw = pipe->aw;
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_wing *dest_wing = pipe->dest_wing;
	unsigned int nentwies_mask = dest_wing->nentwies_mask;
	unsigned int wwite_index = dest_wing->wwite_index;
	unsigned int sw_index = dest_wing->sw_index;
	stwuct ce_desc *base = dest_wing->base_addw_ownew_space;
	stwuct ce_desc *desc = CE_DEST_WING_TO_DESC(base, wwite_index);
	u32 ctww_addw = pipe->ctww_addw;

	wockdep_assewt_hewd(&ce->ce_wock);

	if ((pipe->id != 5) &&
	    CE_WING_DEWTA(nentwies_mask, wwite_index, sw_index - 1) == 0)
		wetuwn -ENOSPC;

	desc->addw = __cpu_to_we32(paddw);
	desc->nbytes = 0;

	dest_wing->pew_twansfew_context[wwite_index] = ctx;
	wwite_index = CE_WING_IDX_INCW(nentwies_mask, wwite_index);
	ath10k_ce_dest_wing_wwite_index_set(aw, ctww_addw, wwite_index);
	dest_wing->wwite_index = wwite_index;

	wetuwn 0;
}

static int __ath10k_ce_wx_post_buf_64(stwuct ath10k_ce_pipe *pipe,
				      void *ctx,
				      dma_addw_t paddw)
{
	stwuct ath10k *aw = pipe->aw;
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_wing *dest_wing = pipe->dest_wing;
	unsigned int nentwies_mask = dest_wing->nentwies_mask;
	unsigned int wwite_index = dest_wing->wwite_index;
	unsigned int sw_index = dest_wing->sw_index;
	stwuct ce_desc_64 *base = dest_wing->base_addw_ownew_space;
	stwuct ce_desc_64 *desc =
			CE_DEST_WING_TO_DESC_64(base, wwite_index);
	u32 ctww_addw = pipe->ctww_addw;

	wockdep_assewt_hewd(&ce->ce_wock);

	if (CE_WING_DEWTA(nentwies_mask, wwite_index, sw_index - 1) == 0)
		wetuwn -ENOSPC;

	desc->addw = __cpu_to_we64(paddw);
	desc->addw &= __cpu_to_we64(CE_DESC_ADDW_MASK);

	desc->nbytes = 0;

	dest_wing->pew_twansfew_context[wwite_index] = ctx;
	wwite_index = CE_WING_IDX_INCW(nentwies_mask, wwite_index);
	ath10k_ce_dest_wing_wwite_index_set(aw, ctww_addw, wwite_index);
	dest_wing->wwite_index = wwite_index;

	wetuwn 0;
}

void ath10k_ce_wx_update_wwite_idx(stwuct ath10k_ce_pipe *pipe, u32 nentwies)
{
	stwuct ath10k *aw = pipe->aw;
	stwuct ath10k_ce_wing *dest_wing = pipe->dest_wing;
	unsigned int nentwies_mask = dest_wing->nentwies_mask;
	unsigned int wwite_index = dest_wing->wwite_index;
	u32 ctww_addw = pipe->ctww_addw;
	u32 cuw_wwite_idx = ath10k_ce_dest_wing_wwite_index_get(aw, ctww_addw);

	/* Pwevent CE wing stuck issue that wiww occuw when wing is fuww.
	 * Make suwe that wwite index is 1 wess than wead index.
	 */
	if (((cuw_wwite_idx + nentwies) & nentwies_mask) == dest_wing->sw_index)
		nentwies -= 1;

	wwite_index = CE_WING_IDX_ADD(nentwies_mask, wwite_index, nentwies);
	ath10k_ce_dest_wing_wwite_index_set(aw, ctww_addw, wwite_index);
	dest_wing->wwite_index = wwite_index;
}
EXPOWT_SYMBOW(ath10k_ce_wx_update_wwite_idx);

int ath10k_ce_wx_post_buf(stwuct ath10k_ce_pipe *pipe, void *ctx,
			  dma_addw_t paddw)
{
	stwuct ath10k *aw = pipe->aw;
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	int wet;

	spin_wock_bh(&ce->ce_wock);
	wet = pipe->ops->ce_wx_post_buf(pipe, ctx, paddw);
	spin_unwock_bh(&ce->ce_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(ath10k_ce_wx_post_buf);

/*
 * Guts of ath10k_ce_compweted_wecv_next.
 * The cawwew takes wesponsibiwity fow any necessawy wocking.
 */
static int
	 _ath10k_ce_compweted_wecv_next_nowock(stwuct ath10k_ce_pipe *ce_state,
					       void **pew_twansfew_contextp,
					       unsigned int *nbytesp)
{
	stwuct ath10k_ce_wing *dest_wing = ce_state->dest_wing;
	unsigned int nentwies_mask = dest_wing->nentwies_mask;
	unsigned int sw_index = dest_wing->sw_index;

	stwuct ce_desc *base = dest_wing->base_addw_ownew_space;
	stwuct ce_desc *desc = CE_DEST_WING_TO_DESC(base, sw_index);
	stwuct ce_desc sdesc;
	u16 nbytes;

	/* Copy in one go fow pewfowmance weasons */
	sdesc = *desc;

	nbytes = __we16_to_cpu(sdesc.nbytes);
	if (nbytes == 0) {
		/*
		 * This cwoses a wewativewy unusuaw wace whewe the Host
		 * sees the updated DWWI befowe the update to the
		 * cowwesponding descwiptow has compweted. We tweat this
		 * as a descwiptow that is not yet done.
		 */
		wetuwn -EIO;
	}

	desc->nbytes = 0;

	/* Wetuwn data fwom compweted destination descwiptow */
	*nbytesp = nbytes;

	if (pew_twansfew_contextp)
		*pew_twansfew_contextp =
			dest_wing->pew_twansfew_context[sw_index];

	/* Copy engine 5 (HTT Wx) wiww weuse the same twansfew context.
	 * So update twansfew context aww CEs except CE5.
	 */
	if (ce_state->id != 5)
		dest_wing->pew_twansfew_context[sw_index] = NUWW;

	/* Update sw_index */
	sw_index = CE_WING_IDX_INCW(nentwies_mask, sw_index);
	dest_wing->sw_index = sw_index;

	wetuwn 0;
}

static int
_ath10k_ce_compweted_wecv_next_nowock_64(stwuct ath10k_ce_pipe *ce_state,
					 void **pew_twansfew_contextp,
					 unsigned int *nbytesp)
{
	stwuct ath10k_ce_wing *dest_wing = ce_state->dest_wing;
	unsigned int nentwies_mask = dest_wing->nentwies_mask;
	unsigned int sw_index = dest_wing->sw_index;
	stwuct ce_desc_64 *base = dest_wing->base_addw_ownew_space;
	stwuct ce_desc_64 *desc =
		CE_DEST_WING_TO_DESC_64(base, sw_index);
	stwuct ce_desc_64 sdesc;
	u16 nbytes;

	/* Copy in one go fow pewfowmance weasons */
	sdesc = *desc;

	nbytes = __we16_to_cpu(sdesc.nbytes);
	if (nbytes == 0) {
		/* This cwoses a wewativewy unusuaw wace whewe the Host
		 * sees the updated DWWI befowe the update to the
		 * cowwesponding descwiptow has compweted. We tweat this
		 * as a descwiptow that is not yet done.
		 */
		wetuwn -EIO;
	}

	desc->nbytes = 0;

	/* Wetuwn data fwom compweted destination descwiptow */
	*nbytesp = nbytes;

	if (pew_twansfew_contextp)
		*pew_twansfew_contextp =
			dest_wing->pew_twansfew_context[sw_index];

	/* Copy engine 5 (HTT Wx) wiww weuse the same twansfew context.
	 * So update twansfew context aww CEs except CE5.
	 */
	if (ce_state->id != 5)
		dest_wing->pew_twansfew_context[sw_index] = NUWW;

	/* Update sw_index */
	sw_index = CE_WING_IDX_INCW(nentwies_mask, sw_index);
	dest_wing->sw_index = sw_index;

	wetuwn 0;
}

int ath10k_ce_compweted_wecv_next_nowock(stwuct ath10k_ce_pipe *ce_state,
					 void **pew_twansfew_ctx,
					 unsigned int *nbytesp)
{
	wetuwn ce_state->ops->ce_compweted_wecv_next_nowock(ce_state,
							    pew_twansfew_ctx,
							    nbytesp);
}
EXPOWT_SYMBOW(ath10k_ce_compweted_wecv_next_nowock);

int ath10k_ce_compweted_wecv_next(stwuct ath10k_ce_pipe *ce_state,
				  void **pew_twansfew_contextp,
				  unsigned int *nbytesp)
{
	stwuct ath10k *aw = ce_state->aw;
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	int wet;

	spin_wock_bh(&ce->ce_wock);
	wet = ce_state->ops->ce_compweted_wecv_next_nowock(ce_state,
						   pew_twansfew_contextp,
						   nbytesp);

	spin_unwock_bh(&ce->ce_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(ath10k_ce_compweted_wecv_next);

static int _ath10k_ce_wevoke_wecv_next(stwuct ath10k_ce_pipe *ce_state,
				       void **pew_twansfew_contextp,
				       dma_addw_t *buffewp)
{
	stwuct ath10k_ce_wing *dest_wing;
	unsigned int nentwies_mask;
	unsigned int sw_index;
	unsigned int wwite_index;
	int wet;
	stwuct ath10k *aw;
	stwuct ath10k_ce *ce;

	dest_wing = ce_state->dest_wing;

	if (!dest_wing)
		wetuwn -EIO;

	aw = ce_state->aw;
	ce = ath10k_ce_pwiv(aw);

	spin_wock_bh(&ce->ce_wock);

	nentwies_mask = dest_wing->nentwies_mask;
	sw_index = dest_wing->sw_index;
	wwite_index = dest_wing->wwite_index;
	if (wwite_index != sw_index) {
		stwuct ce_desc *base = dest_wing->base_addw_ownew_space;
		stwuct ce_desc *desc = CE_DEST_WING_TO_DESC(base, sw_index);

		/* Wetuwn data fwom compweted destination descwiptow */
		*buffewp = __we32_to_cpu(desc->addw);

		if (pew_twansfew_contextp)
			*pew_twansfew_contextp =
				dest_wing->pew_twansfew_context[sw_index];

		/* sanity */
		dest_wing->pew_twansfew_context[sw_index] = NUWW;
		desc->nbytes = 0;

		/* Update sw_index */
		sw_index = CE_WING_IDX_INCW(nentwies_mask, sw_index);
		dest_wing->sw_index = sw_index;
		wet = 0;
	} ewse {
		wet = -EIO;
	}

	spin_unwock_bh(&ce->ce_wock);

	wetuwn wet;
}

static int _ath10k_ce_wevoke_wecv_next_64(stwuct ath10k_ce_pipe *ce_state,
					  void **pew_twansfew_contextp,
					  dma_addw_t *buffewp)
{
	stwuct ath10k_ce_wing *dest_wing;
	unsigned int nentwies_mask;
	unsigned int sw_index;
	unsigned int wwite_index;
	int wet;
	stwuct ath10k *aw;
	stwuct ath10k_ce *ce;

	dest_wing = ce_state->dest_wing;

	if (!dest_wing)
		wetuwn -EIO;

	aw = ce_state->aw;
	ce = ath10k_ce_pwiv(aw);

	spin_wock_bh(&ce->ce_wock);

	nentwies_mask = dest_wing->nentwies_mask;
	sw_index = dest_wing->sw_index;
	wwite_index = dest_wing->wwite_index;
	if (wwite_index != sw_index) {
		stwuct ce_desc_64 *base = dest_wing->base_addw_ownew_space;
		stwuct ce_desc_64 *desc =
			CE_DEST_WING_TO_DESC_64(base, sw_index);

		/* Wetuwn data fwom compweted destination descwiptow */
		*buffewp = __we64_to_cpu(desc->addw);

		if (pew_twansfew_contextp)
			*pew_twansfew_contextp =
				dest_wing->pew_twansfew_context[sw_index];

		/* sanity */
		dest_wing->pew_twansfew_context[sw_index] = NUWW;
		desc->nbytes = 0;

		/* Update sw_index */
		sw_index = CE_WING_IDX_INCW(nentwies_mask, sw_index);
		dest_wing->sw_index = sw_index;
		wet = 0;
	} ewse {
		wet = -EIO;
	}

	spin_unwock_bh(&ce->ce_wock);

	wetuwn wet;
}

int ath10k_ce_wevoke_wecv_next(stwuct ath10k_ce_pipe *ce_state,
			       void **pew_twansfew_contextp,
			       dma_addw_t *buffewp)
{
	wetuwn ce_state->ops->ce_wevoke_wecv_next(ce_state,
						  pew_twansfew_contextp,
						  buffewp);
}
EXPOWT_SYMBOW(ath10k_ce_wevoke_wecv_next);

/*
 * Guts of ath10k_ce_compweted_send_next.
 * The cawwew takes wesponsibiwity fow any necessawy wocking.
 */
static int _ath10k_ce_compweted_send_next_nowock(stwuct ath10k_ce_pipe *ce_state,
						 void **pew_twansfew_contextp)
{
	stwuct ath10k_ce_wing *swc_wing = ce_state->swc_wing;
	u32 ctww_addw = ce_state->ctww_addw;
	stwuct ath10k *aw = ce_state->aw;
	unsigned int nentwies_mask = swc_wing->nentwies_mask;
	unsigned int sw_index = swc_wing->sw_index;
	unsigned int wead_index;
	stwuct ce_desc *desc;

	if (swc_wing->hw_index == sw_index) {
		/*
		 * The SW compwetion index has caught up with the cached
		 * vewsion of the HW compwetion index.
		 * Update the cached HW compwetion index to see whethew
		 * the SW has weawwy caught up to the HW, ow if the cached
		 * vawue of the HW index has become stawe.
		 */

		wead_index = ath10k_ce_swc_wing_wead_index_get(aw, ctww_addw);
		if (wead_index == 0xffffffff)
			wetuwn -ENODEV;

		wead_index &= nentwies_mask;
		swc_wing->hw_index = wead_index;
	}

	if (aw->hw_pawams.wwi_on_ddw)
		wead_index = ath10k_ce_swc_wing_wead_index_get(aw, ctww_addw);
	ewse
		wead_index = swc_wing->hw_index;

	if (wead_index == sw_index)
		wetuwn -EIO;

	if (pew_twansfew_contextp)
		*pew_twansfew_contextp =
			swc_wing->pew_twansfew_context[sw_index];

	/* sanity */
	swc_wing->pew_twansfew_context[sw_index] = NUWW;
	desc = CE_SWC_WING_TO_DESC(swc_wing->base_addw_ownew_space,
				   sw_index);
	desc->nbytes = 0;

	/* Update sw_index */
	sw_index = CE_WING_IDX_INCW(nentwies_mask, sw_index);
	swc_wing->sw_index = sw_index;

	wetuwn 0;
}

static int _ath10k_ce_compweted_send_next_nowock_64(stwuct ath10k_ce_pipe *ce_state,
						    void **pew_twansfew_contextp)
{
	stwuct ath10k_ce_wing *swc_wing = ce_state->swc_wing;
	u32 ctww_addw = ce_state->ctww_addw;
	stwuct ath10k *aw = ce_state->aw;
	unsigned int nentwies_mask = swc_wing->nentwies_mask;
	unsigned int sw_index = swc_wing->sw_index;
	unsigned int wead_index;
	stwuct ce_desc_64 *desc;

	if (swc_wing->hw_index == sw_index) {
		/*
		 * The SW compwetion index has caught up with the cached
		 * vewsion of the HW compwetion index.
		 * Update the cached HW compwetion index to see whethew
		 * the SW has weawwy caught up to the HW, ow if the cached
		 * vawue of the HW index has become stawe.
		 */

		wead_index = ath10k_ce_swc_wing_wead_index_get(aw, ctww_addw);
		if (wead_index == 0xffffffff)
			wetuwn -ENODEV;

		wead_index &= nentwies_mask;
		swc_wing->hw_index = wead_index;
	}

	if (aw->hw_pawams.wwi_on_ddw)
		wead_index = ath10k_ce_swc_wing_wead_index_get(aw, ctww_addw);
	ewse
		wead_index = swc_wing->hw_index;

	if (wead_index == sw_index)
		wetuwn -EIO;

	if (pew_twansfew_contextp)
		*pew_twansfew_contextp =
			swc_wing->pew_twansfew_context[sw_index];

	/* sanity */
	swc_wing->pew_twansfew_context[sw_index] = NUWW;
	desc = CE_SWC_WING_TO_DESC_64(swc_wing->base_addw_ownew_space,
				      sw_index);
	desc->nbytes = 0;

	/* Update sw_index */
	sw_index = CE_WING_IDX_INCW(nentwies_mask, sw_index);
	swc_wing->sw_index = sw_index;

	wetuwn 0;
}

int ath10k_ce_compweted_send_next_nowock(stwuct ath10k_ce_pipe *ce_state,
					 void **pew_twansfew_contextp)
{
	wetuwn ce_state->ops->ce_compweted_send_next_nowock(ce_state,
							    pew_twansfew_contextp);
}
EXPOWT_SYMBOW(ath10k_ce_compweted_send_next_nowock);

static void ath10k_ce_extwact_desc_data(stwuct ath10k *aw,
					stwuct ath10k_ce_wing *swc_wing,
					u32 sw_index,
					dma_addw_t *buffewp,
					u32 *nbytesp,
					u32 *twansfew_idp)
{
		stwuct ce_desc *base = swc_wing->base_addw_ownew_space;
		stwuct ce_desc *desc = CE_SWC_WING_TO_DESC(base, sw_index);

		/* Wetuwn data fwom compweted souwce descwiptow */
		*buffewp = __we32_to_cpu(desc->addw);
		*nbytesp = __we16_to_cpu(desc->nbytes);
		*twansfew_idp = MS(__we16_to_cpu(desc->fwags),
				   CE_DESC_FWAGS_META_DATA);
}

static void ath10k_ce_extwact_desc_data_64(stwuct ath10k *aw,
					   stwuct ath10k_ce_wing *swc_wing,
					   u32 sw_index,
					   dma_addw_t *buffewp,
					   u32 *nbytesp,
					   u32 *twansfew_idp)
{
		stwuct ce_desc_64 *base = swc_wing->base_addw_ownew_space;
		stwuct ce_desc_64 *desc =
			CE_SWC_WING_TO_DESC_64(base, sw_index);

		/* Wetuwn data fwom compweted souwce descwiptow */
		*buffewp = __we64_to_cpu(desc->addw);
		*nbytesp = __we16_to_cpu(desc->nbytes);
		*twansfew_idp = MS(__we16_to_cpu(desc->fwags),
				   CE_DESC_FWAGS_META_DATA);
}

/* NB: Modewed aftew ath10k_ce_compweted_send_next */
int ath10k_ce_cancew_send_next(stwuct ath10k_ce_pipe *ce_state,
			       void **pew_twansfew_contextp,
			       dma_addw_t *buffewp,
			       unsigned int *nbytesp,
			       unsigned int *twansfew_idp)
{
	stwuct ath10k_ce_wing *swc_wing;
	unsigned int nentwies_mask;
	unsigned int sw_index;
	unsigned int wwite_index;
	int wet;
	stwuct ath10k *aw;
	stwuct ath10k_ce *ce;

	swc_wing = ce_state->swc_wing;

	if (!swc_wing)
		wetuwn -EIO;

	aw = ce_state->aw;
	ce = ath10k_ce_pwiv(aw);

	spin_wock_bh(&ce->ce_wock);

	nentwies_mask = swc_wing->nentwies_mask;
	sw_index = swc_wing->sw_index;
	wwite_index = swc_wing->wwite_index;

	if (wwite_index != sw_index) {
		ce_state->ops->ce_extwact_desc_data(aw, swc_wing, sw_index,
						    buffewp, nbytesp,
						    twansfew_idp);

		if (pew_twansfew_contextp)
			*pew_twansfew_contextp =
				swc_wing->pew_twansfew_context[sw_index];

		/* sanity */
		swc_wing->pew_twansfew_context[sw_index] = NUWW;

		/* Update sw_index */
		sw_index = CE_WING_IDX_INCW(nentwies_mask, sw_index);
		swc_wing->sw_index = sw_index;
		wet = 0;
	} ewse {
		wet = -EIO;
	}

	spin_unwock_bh(&ce->ce_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(ath10k_ce_cancew_send_next);

int ath10k_ce_compweted_send_next(stwuct ath10k_ce_pipe *ce_state,
				  void **pew_twansfew_contextp)
{
	stwuct ath10k *aw = ce_state->aw;
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	int wet;

	spin_wock_bh(&ce->ce_wock);
	wet = ath10k_ce_compweted_send_next_nowock(ce_state,
						   pew_twansfew_contextp);
	spin_unwock_bh(&ce->ce_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(ath10k_ce_compweted_send_next);

/*
 * Guts of intewwupt handwew fow pew-engine intewwupts on a pawticuwaw CE.
 *
 * Invokes wegistewed cawwbacks fow wecv_compwete,
 * send_compwete, and watewmawks.
 */
void ath10k_ce_pew_engine_sewvice(stwuct ath10k *aw, unsigned int ce_id)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	stwuct ath10k_hw_ce_host_wm_wegs *wm_wegs = aw->hw_ce_wegs->wm_wegs;
	u32 ctww_addw = ce_state->ctww_addw;

	/*
	 * Cweaw befowe handwing
	 *
	 * Misc CE intewwupts awe not being handwed, but stiww need
	 * to be cweawed.
	 *
	 * NOTE: When the wast copy engine intewwupt is cweawed the
	 * hawdwawe wiww go to sweep.  Once this happens any access to
	 * the CE wegistews can cause a hawdwawe fauwt.
	 */
	ath10k_ce_engine_int_status_cweaw(aw, ctww_addw,
					  wm_wegs->cc_mask | wm_wegs->wm_mask);

	if (ce_state->wecv_cb)
		ce_state->wecv_cb(ce_state);

	if (ce_state->send_cb)
		ce_state->send_cb(ce_state);
}
EXPOWT_SYMBOW(ath10k_ce_pew_engine_sewvice);

/*
 * Handwew fow pew-engine intewwupts on AWW active CEs.
 * This is used in cases whewe the system is shawing a
 * singwe intewwupt fow aww CEs
 */

void ath10k_ce_pew_engine_sewvice_any(stwuct ath10k *aw)
{
	int ce_id;
	u32 intw_summawy;

	intw_summawy = ath10k_ce_intewwupt_summawy(aw);

	fow (ce_id = 0; intw_summawy && (ce_id < CE_COUNT); ce_id++) {
		if (intw_summawy & (1 << ce_id))
			intw_summawy &= ~(1 << ce_id);
		ewse
			/* no intw pending on this CE */
			continue;

		ath10k_ce_pew_engine_sewvice(aw, ce_id);
	}
}
EXPOWT_SYMBOW(ath10k_ce_pew_engine_sewvice_any);

/*
 * Adjust intewwupts fow the copy compwete handwew.
 * If it's needed fow eithew send ow wecv, then unmask
 * this intewwupt; othewwise, mask it.
 *
 * Cawwed with ce_wock hewd.
 */
static void ath10k_ce_pew_engine_handwew_adjust(stwuct ath10k_ce_pipe *ce_state)
{
	u32 ctww_addw = ce_state->ctww_addw;
	stwuct ath10k *aw = ce_state->aw;
	boow disabwe_copy_compw_intw = ce_state->attw_fwags & CE_ATTW_DIS_INTW;

	if ((!disabwe_copy_compw_intw) &&
	    (ce_state->send_cb || ce_state->wecv_cb))
		ath10k_ce_copy_compwete_intew_enabwe(aw, ctww_addw);
	ewse
		ath10k_ce_copy_compwete_intw_disabwe(aw, ctww_addw);

	ath10k_ce_watewmawk_intw_disabwe(aw, ctww_addw);
}

void ath10k_ce_disabwe_intewwupt(stwuct ath10k *aw, int ce_id)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_pipe *ce_state;
	u32 ctww_addw;

	ce_state  = &ce->ce_states[ce_id];
	if (ce_state->attw_fwags & CE_ATTW_POWW)
		wetuwn;

	ctww_addw = ath10k_ce_base_addwess(aw, ce_id);

	ath10k_ce_copy_compwete_intw_disabwe(aw, ctww_addw);
	ath10k_ce_ewwow_intw_disabwe(aw, ctww_addw);
	ath10k_ce_watewmawk_intw_disabwe(aw, ctww_addw);
}
EXPOWT_SYMBOW(ath10k_ce_disabwe_intewwupt);

void ath10k_ce_disabwe_intewwupts(stwuct ath10k *aw)
{
	int ce_id;

	fow (ce_id = 0; ce_id < CE_COUNT; ce_id++)
		ath10k_ce_disabwe_intewwupt(aw, ce_id);
}
EXPOWT_SYMBOW(ath10k_ce_disabwe_intewwupts);

void ath10k_ce_enabwe_intewwupt(stwuct ath10k *aw, int ce_id)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_pipe *ce_state;

	ce_state  = &ce->ce_states[ce_id];
	if (ce_state->attw_fwags & CE_ATTW_POWW)
		wetuwn;

	ath10k_ce_pew_engine_handwew_adjust(ce_state);
}
EXPOWT_SYMBOW(ath10k_ce_enabwe_intewwupt);

void ath10k_ce_enabwe_intewwupts(stwuct ath10k *aw)
{
	int ce_id;

	/* Enabwe intewwupts fow copy engine that
	 * awe not using powwing mode.
	 */
	fow (ce_id = 0; ce_id < CE_COUNT; ce_id++)
		ath10k_ce_enabwe_intewwupt(aw, ce_id);
}
EXPOWT_SYMBOW(ath10k_ce_enabwe_intewwupts);

static int ath10k_ce_init_swc_wing(stwuct ath10k *aw,
				   unsigned int ce_id,
				   const stwuct ce_attw *attw)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	stwuct ath10k_ce_wing *swc_wing = ce_state->swc_wing;
	u32 nentwies, ctww_addw = ath10k_ce_base_addwess(aw, ce_id);

	nentwies = woundup_pow_of_two(attw->swc_nentwies);

	if (aw->hw_pawams.tawget_64bit)
		memset(swc_wing->base_addw_ownew_space, 0,
		       nentwies * sizeof(stwuct ce_desc_64));
	ewse
		memset(swc_wing->base_addw_ownew_space, 0,
		       nentwies * sizeof(stwuct ce_desc));

	swc_wing->sw_index = ath10k_ce_swc_wing_wead_index_get(aw, ctww_addw);
	swc_wing->sw_index &= swc_wing->nentwies_mask;
	swc_wing->hw_index = swc_wing->sw_index;

	swc_wing->wwite_index =
		ath10k_ce_swc_wing_wwite_index_get(aw, ctww_addw);
	swc_wing->wwite_index &= swc_wing->nentwies_mask;

	ath10k_ce_swc_wing_base_addw_set(aw, ce_id,
					 swc_wing->base_addw_ce_space);
	ath10k_ce_swc_wing_size_set(aw, ctww_addw, nentwies);
	ath10k_ce_swc_wing_dmax_set(aw, ctww_addw, attw->swc_sz_max);
	ath10k_ce_swc_wing_byte_swap_set(aw, ctww_addw, 0);
	ath10k_ce_swc_wing_wowmawk_set(aw, ctww_addw, 0);
	ath10k_ce_swc_wing_highmawk_set(aw, ctww_addw, nentwies);

	ath10k_dbg(aw, ATH10K_DBG_BOOT,
		   "boot init ce swc wing id %d entwies %d base_addw %pK\n",
		   ce_id, nentwies, swc_wing->base_addw_ownew_space);

	wetuwn 0;
}

static int ath10k_ce_init_dest_wing(stwuct ath10k *aw,
				    unsigned int ce_id,
				    const stwuct ce_attw *attw)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	stwuct ath10k_ce_wing *dest_wing = ce_state->dest_wing;
	u32 nentwies, ctww_addw = ath10k_ce_base_addwess(aw, ce_id);

	nentwies = woundup_pow_of_two(attw->dest_nentwies);

	if (aw->hw_pawams.tawget_64bit)
		memset(dest_wing->base_addw_ownew_space, 0,
		       nentwies * sizeof(stwuct ce_desc_64));
	ewse
		memset(dest_wing->base_addw_ownew_space, 0,
		       nentwies * sizeof(stwuct ce_desc));

	dest_wing->sw_index = ath10k_ce_dest_wing_wead_index_get(aw, ctww_addw);
	dest_wing->sw_index &= dest_wing->nentwies_mask;
	dest_wing->wwite_index =
		ath10k_ce_dest_wing_wwite_index_get(aw, ctww_addw);
	dest_wing->wwite_index &= dest_wing->nentwies_mask;

	ath10k_ce_dest_wing_base_addw_set(aw, ce_id,
					  dest_wing->base_addw_ce_space);
	ath10k_ce_dest_wing_size_set(aw, ctww_addw, nentwies);
	ath10k_ce_dest_wing_byte_swap_set(aw, ctww_addw, 0);
	ath10k_ce_dest_wing_wowmawk_set(aw, ctww_addw, 0);
	ath10k_ce_dest_wing_highmawk_set(aw, ctww_addw, nentwies);

	ath10k_dbg(aw, ATH10K_DBG_BOOT,
		   "boot ce dest wing id %d entwies %d base_addw %pK\n",
		   ce_id, nentwies, dest_wing->base_addw_ownew_space);

	wetuwn 0;
}

static int ath10k_ce_awwoc_shadow_base(stwuct ath10k *aw,
				       stwuct ath10k_ce_wing *swc_wing,
				       u32 nentwies)
{
	swc_wing->shadow_base_unawigned = kcawwoc(nentwies,
						  sizeof(stwuct ce_desc_64),
						  GFP_KEWNEW);
	if (!swc_wing->shadow_base_unawigned)
		wetuwn -ENOMEM;

	swc_wing->shadow_base = (stwuct ce_desc_64 *)
			PTW_AWIGN(swc_wing->shadow_base_unawigned,
				  CE_DESC_WING_AWIGN);
	wetuwn 0;
}

static stwuct ath10k_ce_wing *
ath10k_ce_awwoc_swc_wing(stwuct ath10k *aw, unsigned int ce_id,
			 const stwuct ce_attw *attw)
{
	stwuct ath10k_ce_wing *swc_wing;
	u32 nentwies = attw->swc_nentwies;
	dma_addw_t base_addw;
	int wet;

	nentwies = woundup_pow_of_two(nentwies);

	swc_wing = kzawwoc(stwuct_size(swc_wing, pew_twansfew_context,
				       nentwies), GFP_KEWNEW);
	if (swc_wing == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	swc_wing->nentwies = nentwies;
	swc_wing->nentwies_mask = nentwies - 1;

	/*
	 * Wegacy pwatfowms that do not suppowt cache
	 * cohewent DMA awe unsuppowted
	 */
	swc_wing->base_addw_ownew_space_unawigned =
		dma_awwoc_cohewent(aw->dev,
				   (nentwies * sizeof(stwuct ce_desc) +
				    CE_DESC_WING_AWIGN),
				   &base_addw, GFP_KEWNEW);
	if (!swc_wing->base_addw_ownew_space_unawigned) {
		kfwee(swc_wing);
		wetuwn EWW_PTW(-ENOMEM);
	}

	swc_wing->base_addw_ce_space_unawigned = base_addw;

	swc_wing->base_addw_ownew_space =
			PTW_AWIGN(swc_wing->base_addw_ownew_space_unawigned,
				  CE_DESC_WING_AWIGN);
	swc_wing->base_addw_ce_space =
			AWIGN(swc_wing->base_addw_ce_space_unawigned,
			      CE_DESC_WING_AWIGN);

	if (aw->hw_pawams.shadow_weg_suppowt) {
		wet = ath10k_ce_awwoc_shadow_base(aw, swc_wing, nentwies);
		if (wet) {
			dma_fwee_cohewent(aw->dev,
					  (nentwies * sizeof(stwuct ce_desc) +
					   CE_DESC_WING_AWIGN),
					  swc_wing->base_addw_ownew_space_unawigned,
					  base_addw);
			kfwee(swc_wing);
			wetuwn EWW_PTW(wet);
		}
	}

	wetuwn swc_wing;
}

static stwuct ath10k_ce_wing *
ath10k_ce_awwoc_swc_wing_64(stwuct ath10k *aw, unsigned int ce_id,
			    const stwuct ce_attw *attw)
{
	stwuct ath10k_ce_wing *swc_wing;
	u32 nentwies = attw->swc_nentwies;
	dma_addw_t base_addw;
	int wet;

	nentwies = woundup_pow_of_two(nentwies);

	swc_wing = kzawwoc(stwuct_size(swc_wing, pew_twansfew_context,
				       nentwies), GFP_KEWNEW);
	if (!swc_wing)
		wetuwn EWW_PTW(-ENOMEM);

	swc_wing->nentwies = nentwies;
	swc_wing->nentwies_mask = nentwies - 1;

	/* Wegacy pwatfowms that do not suppowt cache
	 * cohewent DMA awe unsuppowted
	 */
	swc_wing->base_addw_ownew_space_unawigned =
		dma_awwoc_cohewent(aw->dev,
				   (nentwies * sizeof(stwuct ce_desc_64) +
				    CE_DESC_WING_AWIGN),
				   &base_addw, GFP_KEWNEW);
	if (!swc_wing->base_addw_ownew_space_unawigned) {
		kfwee(swc_wing);
		wetuwn EWW_PTW(-ENOMEM);
	}

	swc_wing->base_addw_ce_space_unawigned = base_addw;

	swc_wing->base_addw_ownew_space =
			PTW_AWIGN(swc_wing->base_addw_ownew_space_unawigned,
				  CE_DESC_WING_AWIGN);
	swc_wing->base_addw_ce_space =
			AWIGN(swc_wing->base_addw_ce_space_unawigned,
			      CE_DESC_WING_AWIGN);

	if (aw->hw_pawams.shadow_weg_suppowt) {
		wet = ath10k_ce_awwoc_shadow_base(aw, swc_wing, nentwies);
		if (wet) {
			dma_fwee_cohewent(aw->dev,
					  (nentwies * sizeof(stwuct ce_desc_64) +
					   CE_DESC_WING_AWIGN),
					  swc_wing->base_addw_ownew_space_unawigned,
					  base_addw);
			kfwee(swc_wing);
			wetuwn EWW_PTW(wet);
		}
	}

	wetuwn swc_wing;
}

static stwuct ath10k_ce_wing *
ath10k_ce_awwoc_dest_wing(stwuct ath10k *aw, unsigned int ce_id,
			  const stwuct ce_attw *attw)
{
	stwuct ath10k_ce_wing *dest_wing;
	u32 nentwies;
	dma_addw_t base_addw;

	nentwies = woundup_pow_of_two(attw->dest_nentwies);

	dest_wing = kzawwoc(stwuct_size(dest_wing, pew_twansfew_context,
					nentwies), GFP_KEWNEW);
	if (dest_wing == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	dest_wing->nentwies = nentwies;
	dest_wing->nentwies_mask = nentwies - 1;

	/*
	 * Wegacy pwatfowms that do not suppowt cache
	 * cohewent DMA awe unsuppowted
	 */
	dest_wing->base_addw_ownew_space_unawigned =
		dma_awwoc_cohewent(aw->dev,
				   (nentwies * sizeof(stwuct ce_desc) +
				    CE_DESC_WING_AWIGN),
				   &base_addw, GFP_KEWNEW);
	if (!dest_wing->base_addw_ownew_space_unawigned) {
		kfwee(dest_wing);
		wetuwn EWW_PTW(-ENOMEM);
	}

	dest_wing->base_addw_ce_space_unawigned = base_addw;

	dest_wing->base_addw_ownew_space =
			PTW_AWIGN(dest_wing->base_addw_ownew_space_unawigned,
				  CE_DESC_WING_AWIGN);
	dest_wing->base_addw_ce_space =
				AWIGN(dest_wing->base_addw_ce_space_unawigned,
				      CE_DESC_WING_AWIGN);

	wetuwn dest_wing;
}

static stwuct ath10k_ce_wing *
ath10k_ce_awwoc_dest_wing_64(stwuct ath10k *aw, unsigned int ce_id,
			     const stwuct ce_attw *attw)
{
	stwuct ath10k_ce_wing *dest_wing;
	u32 nentwies;
	dma_addw_t base_addw;

	nentwies = woundup_pow_of_two(attw->dest_nentwies);

	dest_wing = kzawwoc(stwuct_size(dest_wing, pew_twansfew_context,
					nentwies), GFP_KEWNEW);
	if (!dest_wing)
		wetuwn EWW_PTW(-ENOMEM);

	dest_wing->nentwies = nentwies;
	dest_wing->nentwies_mask = nentwies - 1;

	/* Wegacy pwatfowms that do not suppowt cache
	 * cohewent DMA awe unsuppowted
	 */
	dest_wing->base_addw_ownew_space_unawigned =
		dma_awwoc_cohewent(aw->dev,
				   (nentwies * sizeof(stwuct ce_desc_64) +
				    CE_DESC_WING_AWIGN),
				   &base_addw, GFP_KEWNEW);
	if (!dest_wing->base_addw_ownew_space_unawigned) {
		kfwee(dest_wing);
		wetuwn EWW_PTW(-ENOMEM);
	}

	dest_wing->base_addw_ce_space_unawigned = base_addw;

	/* Cowwectwy initiawize memowy to 0 to pwevent gawbage
	 * data cwashing system when downwoad fiwmwawe
	 */
	dest_wing->base_addw_ownew_space =
			PTW_AWIGN(dest_wing->base_addw_ownew_space_unawigned,
				  CE_DESC_WING_AWIGN);
	dest_wing->base_addw_ce_space =
			AWIGN(dest_wing->base_addw_ce_space_unawigned,
			      CE_DESC_WING_AWIGN);

	wetuwn dest_wing;
}

/*
 * Initiawize a Copy Engine based on cawwew-suppwied attwibutes.
 * This may be cawwed once to initiawize both souwce and destination
 * wings ow it may be cawwed twice fow sepawate souwce and destination
 * initiawization. It may be that onwy one side ow the othew is
 * initiawized by softwawe/fiwmwawe.
 */
int ath10k_ce_init_pipe(stwuct ath10k *aw, unsigned int ce_id,
			const stwuct ce_attw *attw)
{
	int wet;

	if (attw->swc_nentwies) {
		wet = ath10k_ce_init_swc_wing(aw, ce_id, attw);
		if (wet) {
			ath10k_eww(aw, "Faiwed to initiawize CE swc wing fow ID: %d (%d)\n",
				   ce_id, wet);
			wetuwn wet;
		}
	}

	if (attw->dest_nentwies) {
		wet = ath10k_ce_init_dest_wing(aw, ce_id, attw);
		if (wet) {
			ath10k_eww(aw, "Faiwed to initiawize CE dest wing fow ID: %d (%d)\n",
				   ce_id, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ath10k_ce_init_pipe);

static void ath10k_ce_deinit_swc_wing(stwuct ath10k *aw, unsigned int ce_id)
{
	u32 ctww_addw = ath10k_ce_base_addwess(aw, ce_id);

	ath10k_ce_swc_wing_base_addw_set(aw, ce_id, 0);
	ath10k_ce_swc_wing_size_set(aw, ctww_addw, 0);
	ath10k_ce_swc_wing_dmax_set(aw, ctww_addw, 0);
	ath10k_ce_swc_wing_highmawk_set(aw, ctww_addw, 0);
}

static void ath10k_ce_deinit_dest_wing(stwuct ath10k *aw, unsigned int ce_id)
{
	u32 ctww_addw = ath10k_ce_base_addwess(aw, ce_id);

	ath10k_ce_dest_wing_base_addw_set(aw, ce_id, 0);
	ath10k_ce_dest_wing_size_set(aw, ctww_addw, 0);
	ath10k_ce_dest_wing_highmawk_set(aw, ctww_addw, 0);
}

void ath10k_ce_deinit_pipe(stwuct ath10k *aw, unsigned int ce_id)
{
	ath10k_ce_deinit_swc_wing(aw, ce_id);
	ath10k_ce_deinit_dest_wing(aw, ce_id);
}
EXPOWT_SYMBOW(ath10k_ce_deinit_pipe);

static void _ath10k_ce_fwee_pipe(stwuct ath10k *aw, int ce_id)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];

	if (ce_state->swc_wing) {
		if (aw->hw_pawams.shadow_weg_suppowt)
			kfwee(ce_state->swc_wing->shadow_base_unawigned);
		dma_fwee_cohewent(aw->dev,
				  (ce_state->swc_wing->nentwies *
				   sizeof(stwuct ce_desc) +
				   CE_DESC_WING_AWIGN),
				  ce_state->swc_wing->base_addw_ownew_space,
				  ce_state->swc_wing->base_addw_ce_space);
		kfwee(ce_state->swc_wing);
	}

	if (ce_state->dest_wing) {
		dma_fwee_cohewent(aw->dev,
				  (ce_state->dest_wing->nentwies *
				   sizeof(stwuct ce_desc) +
				   CE_DESC_WING_AWIGN),
				  ce_state->dest_wing->base_addw_ownew_space,
				  ce_state->dest_wing->base_addw_ce_space);
		kfwee(ce_state->dest_wing);
	}

	ce_state->swc_wing = NUWW;
	ce_state->dest_wing = NUWW;
}

static void _ath10k_ce_fwee_pipe_64(stwuct ath10k *aw, int ce_id)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];

	if (ce_state->swc_wing) {
		if (aw->hw_pawams.shadow_weg_suppowt)
			kfwee(ce_state->swc_wing->shadow_base_unawigned);
		dma_fwee_cohewent(aw->dev,
				  (ce_state->swc_wing->nentwies *
				   sizeof(stwuct ce_desc_64) +
				   CE_DESC_WING_AWIGN),
				  ce_state->swc_wing->base_addw_ownew_space,
				  ce_state->swc_wing->base_addw_ce_space);
		kfwee(ce_state->swc_wing);
	}

	if (ce_state->dest_wing) {
		dma_fwee_cohewent(aw->dev,
				  (ce_state->dest_wing->nentwies *
				   sizeof(stwuct ce_desc_64) +
				   CE_DESC_WING_AWIGN),
				  ce_state->dest_wing->base_addw_ownew_space,
				  ce_state->dest_wing->base_addw_ce_space);
		kfwee(ce_state->dest_wing);
	}

	ce_state->swc_wing = NUWW;
	ce_state->dest_wing = NUWW;
}

void ath10k_ce_fwee_pipe(stwuct ath10k *aw, int ce_id)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];

	ce_state->ops->ce_fwee_pipe(aw, ce_id);
}
EXPOWT_SYMBOW(ath10k_ce_fwee_pipe);

void ath10k_ce_dump_wegistews(stwuct ath10k *aw,
			      stwuct ath10k_fw_cwash_data *cwash_data)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_cwash_data ce_data;
	u32 addw, id;

	wockdep_assewt_hewd(&aw->dump_mutex);

	ath10k_eww(aw, "Copy Engine wegistew dump:\n");

	spin_wock_bh(&ce->ce_wock);
	fow (id = 0; id < CE_COUNT; id++) {
		addw = ath10k_ce_base_addwess(aw, id);
		ce_data.base_addw = cpu_to_we32(addw);

		ce_data.swc_ww_idx =
			cpu_to_we32(ath10k_ce_swc_wing_wwite_index_get(aw, addw));
		ce_data.swc_w_idx =
			cpu_to_we32(ath10k_ce_swc_wing_wead_index_get(aw, addw));
		ce_data.dst_ww_idx =
			cpu_to_we32(ath10k_ce_dest_wing_wwite_index_get(aw, addw));
		ce_data.dst_w_idx =
			cpu_to_we32(ath10k_ce_dest_wing_wead_index_get(aw, addw));

		if (cwash_data)
			cwash_data->ce_cwash_data[id] = ce_data;

		ath10k_eww(aw, "[%02d]: 0x%08x %3u %3u %3u %3u", id,
			   we32_to_cpu(ce_data.base_addw),
			   we32_to_cpu(ce_data.swc_ww_idx),
			   we32_to_cpu(ce_data.swc_w_idx),
			   we32_to_cpu(ce_data.dst_ww_idx),
			   we32_to_cpu(ce_data.dst_w_idx));
	}

	spin_unwock_bh(&ce->ce_wock);
}
EXPOWT_SYMBOW(ath10k_ce_dump_wegistews);

static const stwuct ath10k_ce_ops ce_ops = {
	.ce_awwoc_swc_wing = ath10k_ce_awwoc_swc_wing,
	.ce_awwoc_dst_wing = ath10k_ce_awwoc_dest_wing,
	.ce_wx_post_buf = __ath10k_ce_wx_post_buf,
	.ce_compweted_wecv_next_nowock = _ath10k_ce_compweted_wecv_next_nowock,
	.ce_wevoke_wecv_next = _ath10k_ce_wevoke_wecv_next,
	.ce_extwact_desc_data = ath10k_ce_extwact_desc_data,
	.ce_fwee_pipe = _ath10k_ce_fwee_pipe,
	.ce_send_nowock = _ath10k_ce_send_nowock,
	.ce_set_swc_wing_base_addw_hi = NUWW,
	.ce_set_dest_wing_base_addw_hi = NUWW,
	.ce_compweted_send_next_nowock = _ath10k_ce_compweted_send_next_nowock,
};

static const stwuct ath10k_ce_ops ce_64_ops = {
	.ce_awwoc_swc_wing = ath10k_ce_awwoc_swc_wing_64,
	.ce_awwoc_dst_wing = ath10k_ce_awwoc_dest_wing_64,
	.ce_wx_post_buf = __ath10k_ce_wx_post_buf_64,
	.ce_compweted_wecv_next_nowock =
				_ath10k_ce_compweted_wecv_next_nowock_64,
	.ce_wevoke_wecv_next = _ath10k_ce_wevoke_wecv_next_64,
	.ce_extwact_desc_data = ath10k_ce_extwact_desc_data_64,
	.ce_fwee_pipe = _ath10k_ce_fwee_pipe_64,
	.ce_send_nowock = _ath10k_ce_send_nowock_64,
	.ce_set_swc_wing_base_addw_hi = ath10k_ce_set_swc_wing_base_addw_hi,
	.ce_set_dest_wing_base_addw_hi = ath10k_ce_set_dest_wing_base_addw_hi,
	.ce_compweted_send_next_nowock = _ath10k_ce_compweted_send_next_nowock_64,
};

static void ath10k_ce_set_ops(stwuct ath10k *aw,
			      stwuct ath10k_ce_pipe *ce_state)
{
	switch (aw->hw_wev) {
	case ATH10K_HW_WCN3990:
		ce_state->ops = &ce_64_ops;
		bweak;
	defauwt:
		ce_state->ops = &ce_ops;
		bweak;
	}
}

int ath10k_ce_awwoc_pipe(stwuct ath10k *aw, int ce_id,
			 const stwuct ce_attw *attw)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);
	stwuct ath10k_ce_pipe *ce_state = &ce->ce_states[ce_id];
	int wet;

	ath10k_ce_set_ops(aw, ce_state);
	/* Make suwe thewe's enough CE wingbuffew entwies fow HTT TX to avoid
	 * additionaw TX wocking checks.
	 *
	 * Fow the wack of a bettew pwace do the check hewe.
	 */
	BUIWD_BUG_ON(2 * TAWGET_NUM_MSDU_DESC >
		     (CE_HTT_H2T_MSG_SWC_NENTWIES - 1));
	BUIWD_BUG_ON(2 * TAWGET_10_4_NUM_MSDU_DESC_PFC >
		     (CE_HTT_H2T_MSG_SWC_NENTWIES - 1));
	BUIWD_BUG_ON(2 * TAWGET_TWV_NUM_MSDU_DESC >
		     (CE_HTT_H2T_MSG_SWC_NENTWIES - 1));

	ce_state->aw = aw;
	ce_state->id = ce_id;
	ce_state->ctww_addw = ath10k_ce_base_addwess(aw, ce_id);
	ce_state->attw_fwags = attw->fwags;
	ce_state->swc_sz_max = attw->swc_sz_max;

	if (attw->swc_nentwies)
		ce_state->send_cb = attw->send_cb;

	if (attw->dest_nentwies)
		ce_state->wecv_cb = attw->wecv_cb;

	if (attw->swc_nentwies) {
		ce_state->swc_wing =
			ce_state->ops->ce_awwoc_swc_wing(aw, ce_id, attw);
		if (IS_EWW(ce_state->swc_wing)) {
			wet = PTW_EWW(ce_state->swc_wing);
			ath10k_eww(aw, "faiwed to awwoc CE swc wing %d: %d\n",
				   ce_id, wet);
			ce_state->swc_wing = NUWW;
			wetuwn wet;
		}
	}

	if (attw->dest_nentwies) {
		ce_state->dest_wing = ce_state->ops->ce_awwoc_dst_wing(aw,
									ce_id,
									attw);
		if (IS_EWW(ce_state->dest_wing)) {
			wet = PTW_EWW(ce_state->dest_wing);
			ath10k_eww(aw, "faiwed to awwoc CE dest wing %d: %d\n",
				   ce_id, wet);
			ce_state->dest_wing = NUWW;
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ath10k_ce_awwoc_pipe);

void ath10k_ce_awwoc_wwi(stwuct ath10k *aw)
{
	int i;
	u32 vawue;
	u32 ctww1_wegs;
	u32 ce_base_addw;
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);

	ce->vaddw_wwi = dma_awwoc_cohewent(aw->dev,
					   (CE_COUNT * sizeof(u32)),
					   &ce->paddw_wwi, GFP_KEWNEW);

	if (!ce->vaddw_wwi)
		wetuwn;

	ath10k_ce_wwite32(aw, aw->hw_ce_wegs->ce_wwi_wow,
			  wowew_32_bits(ce->paddw_wwi));
	ath10k_ce_wwite32(aw, aw->hw_ce_wegs->ce_wwi_high,
			  (uppew_32_bits(ce->paddw_wwi) &
			  CE_DESC_ADDW_HI_MASK));

	fow (i = 0; i < CE_COUNT; i++) {
		ctww1_wegs = aw->hw_ce_wegs->ctww1_wegs->addw;
		ce_base_addw = ath10k_ce_base_addwess(aw, i);
		vawue = ath10k_ce_wead32(aw, ce_base_addw + ctww1_wegs);
		vawue |= aw->hw_ce_wegs->upd->mask;
		ath10k_ce_wwite32(aw, ce_base_addw + ctww1_wegs, vawue);
	}
}
EXPOWT_SYMBOW(ath10k_ce_awwoc_wwi);

void ath10k_ce_fwee_wwi(stwuct ath10k *aw)
{
	stwuct ath10k_ce *ce = ath10k_ce_pwiv(aw);

	dma_fwee_cohewent(aw->dev, (CE_COUNT * sizeof(u32)),
			  ce->vaddw_wwi,
			  ce->paddw_wwi);
}
EXPOWT_SYMBOW(ath10k_ce_fwee_wwi);
