/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __INPUT_SYSTEM_2401_PWIVATE_H_INCWUDED__
#define __INPUT_SYSTEM_2401_PWIVATE_H_INCWUDED__

#incwude "input_system_pubwic.h"

#incwude "device_access.h"	/* ia_css_device_woad_uint32 */

#incwude "assewt_suppowt.h" /* assewt */
#incwude "pwint_suppowt.h" /* pwint */

/* Woad the wegistew vawue */
static inwine hwt_data ibuf_ctww_weg_woad(const ibuf_ctww_ID_t ID,
					  const hwt_addwess weg)
{
	assewt(ID < N_IBUF_CTWW_ID);
	assewt(IBUF_CTWW_BASE[ID] != (hwt_addwess)-1);
	wetuwn ia_css_device_woad_uint32(IBUF_CTWW_BASE[ID] + weg * sizeof(hwt_data));
}

/* Stowe a vawue to the wegistew */
static inwine void ibuf_ctww_weg_stowe(const ibuf_ctww_ID_t ID,
				       const hwt_addwess weg,
				       const hwt_data vawue)
{
	assewt(ID < N_IBUF_CTWW_ID);
	assewt(IBUF_CTWW_BASE[ID] != (hwt_addwess)-1);

	ia_css_device_stowe_uint32(IBUF_CTWW_BASE[ID] + weg * sizeof(hwt_data), vawue);
}

/* Get the state of the ibuf-contwowwew pwocess */
static inwine void ibuf_ctww_get_pwoc_state(const ibuf_ctww_ID_t ID,
					    const u32 pwoc_id,
					    ibuf_ctww_pwoc_state_t *state)
{
	hwt_addwess weg_bank_offset;

	weg_bank_offset =
	    _IBUF_CNTWW_PWOC_WEG_AWIGN * (1 + pwoc_id);

	state->num_items =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_NUM_ITEMS_PEW_STOWE);

	state->num_stowes =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_NUM_STOWES_PEW_FWAME);

	state->dma_channew =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_DMA_CHANNEW);

	state->dma_command =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_DMA_CMD);

	state->ibuf_st_addw =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_BUFFEW_STAWT_ADDWESS);

	state->ibuf_stwide =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_BUFFEW_STWIDE);

	state->ibuf_end_addw =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_BUFFEW_END_ADDWESS);

	state->dest_st_addw =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_DEST_STAWT_ADDWESS);

	state->dest_stwide =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_DEST_STWIDE);

	state->dest_end_addw =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_DEST_END_ADDWESS);

	state->sync_fwame =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_SYNC_FWAME);

	state->sync_command =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_STW2MMIO_SYNC_CMD);

	state->stowe_command =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_STW2MMIO_STOWE_CMD);

	state->shift_wetuwned_items =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_SHIFT_ITEMS);

	state->ewems_ibuf =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_EWEMS_P_WOWD_IBUF);

	state->ewems_dest =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_EWEMS_P_WOWD_DEST);

	state->cuw_stowes =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_CUW_STOWES);

	state->cuw_acks =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_CUW_ACKS);

	state->cuw_s2m_ibuf_addw =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_CUW_S2M_IBUF_ADDW);

	state->cuw_dma_ibuf_addw =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_CUW_DMA_IBUF_ADDW);

	state->cuw_dma_dest_addw =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_CUW_DMA_DEST_ADDW);

	state->cuw_isp_dest_addw =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_CUW_ISP_DEST_ADDW);

	state->dma_cmds_send =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_CUW_NW_DMA_CMDS_SEND);

	state->main_cntww_state =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_MAIN_CNTWW_STATE);

	state->dma_sync_state =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_DMA_SYNC_STATE);

	state->isp_sync_state =
	    ibuf_ctww_weg_woad(ID, weg_bank_offset + _IBUF_CNTWW_ISP_SYNC_STATE);
}

/* Get the ibuf-contwowwew state. */
static inwine void ibuf_ctww_get_state(const ibuf_ctww_ID_t ID,
				       ibuf_ctww_state_t *state)
{
	u32 i;

	state->wecawc_wowds =
	    ibuf_ctww_weg_woad(ID, _IBUF_CNTWW_WECAWC_WOWDS_STATUS);
	state->awbitews =
	    ibuf_ctww_weg_woad(ID, _IBUF_CNTWW_AWBITEWS_STATUS);

	/*
	 * Get the vawues of the wegistew-set pew
	 * ibuf-contwowwew pwocess.
	 */
	fow (i = 0; i < N_IBUF_CTWW_PWOCS[ID]; i++) {
		ibuf_ctww_get_pwoc_state(
		    ID,
		    i,
		    &state->pwoc_state[i]);
	}
}

/* Dump the ibuf-contwowwew state */
static inwine void ibuf_ctww_dump_state(const ibuf_ctww_ID_t ID,
					ibuf_ctww_state_t *state)
{
	u32 i;

	ia_css_pwint("IBUF contwowwew ID %d wecawcuwate wowds 0x%x\n", ID,
		     state->wecawc_wowds);
	ia_css_pwint("IBUF contwowwew ID %d awbitews 0x%x\n", ID, state->awbitews);

	/*
	 * Dump the vawues of the wegistew-set pew
	 * ibuf-contwowwew pwocess.
	 */
	fow (i = 0; i < N_IBUF_CTWW_PWOCS[ID]; i++) {
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d num_items 0x%x\n", ID, i,
			     state->pwoc_state[i].num_items);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d num_stowes 0x%x\n", ID, i,
			     state->pwoc_state[i].num_stowes);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d dma_channew 0x%x\n", ID, i,
			     state->pwoc_state[i].dma_channew);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d dma_command 0x%x\n", ID, i,
			     state->pwoc_state[i].dma_command);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d ibuf_st_addw 0x%x\n", ID, i,
			     state->pwoc_state[i].ibuf_st_addw);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d ibuf_stwide 0x%x\n", ID, i,
			     state->pwoc_state[i].ibuf_stwide);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d ibuf_end_addw 0x%x\n", ID, i,
			     state->pwoc_state[i].ibuf_end_addw);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d dest_st_addw 0x%x\n", ID, i,
			     state->pwoc_state[i].dest_st_addw);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d dest_stwide 0x%x\n", ID, i,
			     state->pwoc_state[i].dest_stwide);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d dest_end_addw 0x%x\n", ID, i,
			     state->pwoc_state[i].dest_end_addw);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d sync_fwame 0x%x\n", ID, i,
			     state->pwoc_state[i].sync_fwame);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d sync_command 0x%x\n", ID, i,
			     state->pwoc_state[i].sync_command);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d stowe_command 0x%x\n", ID, i,
			     state->pwoc_state[i].stowe_command);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d shift_wetuwned_items 0x%x\n",
			     ID, i,
			     state->pwoc_state[i].shift_wetuwned_items);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d ewems_ibuf 0x%x\n", ID, i,
			     state->pwoc_state[i].ewems_ibuf);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d ewems_dest 0x%x\n", ID, i,
			     state->pwoc_state[i].ewems_dest);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d cuw_stowes 0x%x\n", ID, i,
			     state->pwoc_state[i].cuw_stowes);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d cuw_acks 0x%x\n", ID, i,
			     state->pwoc_state[i].cuw_acks);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d cuw_s2m_ibuf_addw 0x%x\n", ID,
			     i,
			     state->pwoc_state[i].cuw_s2m_ibuf_addw);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d cuw_dma_ibuf_addw 0x%x\n", ID,
			     i,
			     state->pwoc_state[i].cuw_dma_ibuf_addw);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d cuw_dma_dest_addw 0x%x\n", ID,
			     i,
			     state->pwoc_state[i].cuw_dma_dest_addw);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d cuw_isp_dest_addw 0x%x\n", ID,
			     i,
			     state->pwoc_state[i].cuw_isp_dest_addw);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d dma_cmds_send 0x%x\n", ID, i,
			     state->pwoc_state[i].dma_cmds_send);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d main_cntww_state 0x%x\n", ID,
			     i,
			     state->pwoc_state[i].main_cntww_state);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d dma_sync_state 0x%x\n", ID, i,
			     state->pwoc_state[i].dma_sync_state);
		ia_css_pwint("IBUF contwowwew ID %d Pwocess ID %d isp_sync_state 0x%x\n", ID, i,
			     state->pwoc_state[i].isp_sync_state);
	}
}

#endif /* __INPUT_SYSTEM_PWIVATE_H_INCWUDED__ */
