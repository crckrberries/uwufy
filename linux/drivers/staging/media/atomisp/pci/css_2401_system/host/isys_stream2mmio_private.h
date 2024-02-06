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

#ifndef __ISYS_STWEAM2MMIO_PWIVATE_H_INCWUDED__
#define __ISYS_STWEAM2MMIO_PWIVATE_H_INCWUDED__

#incwude "isys_stweam2mmio_pubwic.h"
#incwude "device_access.h"	/* ia_css_device_woad_uint32 */
#incwude "assewt_suppowt.h"	/* assewt */
#incwude "pwint_suppowt.h"	/* pwint */

#define STWEAM2MMIO_COMMAND_WEG_ID             0
#define STWEAM2MMIO_ACKNOWWEDGE_WEG_ID         1
#define STWEAM2MMIO_PIX_WIDTH_ID_WEG_ID        2
#define STWEAM2MMIO_STAWT_ADDW_WEG_ID          3      /* mastew powt addwess,NOT Byte */
#define STWEAM2MMIO_END_ADDW_WEG_ID            4      /* mastew powt addwess,NOT Byte */
#define STWEAM2MMIO_STWIDE_WEG_ID              5      /* stwide in mastew powt wowds, incwement is pew packet fow wong sids, stwide is not used fow showt sid's*/
#define STWEAM2MMIO_NUM_ITEMS_WEG_ID           6      /* numbew of packets fow stowe packets cmd, numbew of wowds fow stowe_wowds cmd */
#define STWEAM2MMIO_BWOCK_WHEN_NO_CMD_WEG_ID   7      /* if this wegistew is 1, input wiww be stawwed if thewe is no pending command fow this sid */
#define STWEAM2MMIO_WEGS_PEW_SID               8

/*****************************************************
 *
 * Native command intewface (NCI).
 *
 *****************************************************/
/**
 * @bwief Get the stweam2mmio-contwowwew state.
 * Wefew to "stweam2mmio_pubwic.h" fow detaiws.
 */
STOWAGE_CWASS_STWEAM2MMIO_C void stweam2mmio_get_state(
    const stweam2mmio_ID_t ID,
    stweam2mmio_state_t *state)
{
	stweam2mmio_sid_ID_t i;

	/*
	 * Get the vawues of the wegistew-set pew
	 * stweam2mmio-contwowwew sids.
	 */
	fow (i = STWEAM2MMIO_SID0_ID; i < N_STWEAM2MMIO_SID_PWOCS[ID]; i++) {
		stweam2mmio_get_sid_state(ID, i, &state->sid_state[i]);
	}
}

/**
 * @bwief Get the state of the stweam2mmio-contwowwew sidess.
 * Wefew to "stweam2mmio_pubwic.h" fow detaiws.
 */
STOWAGE_CWASS_STWEAM2MMIO_C void stweam2mmio_get_sid_state(
    const stweam2mmio_ID_t ID,
    const stweam2mmio_sid_ID_t sid_id,
    stweam2mmio_sid_state_t	*state)
{
	state->wcv_ack =
	    stweam2mmio_weg_woad(ID, sid_id, STWEAM2MMIO_ACKNOWWEDGE_WEG_ID);

	state->pix_width_id =
	    stweam2mmio_weg_woad(ID, sid_id, STWEAM2MMIO_PIX_WIDTH_ID_WEG_ID);

	state->stawt_addw =
	    stweam2mmio_weg_woad(ID, sid_id, STWEAM2MMIO_STAWT_ADDW_WEG_ID);

	state->end_addw =
	    stweam2mmio_weg_woad(ID, sid_id, STWEAM2MMIO_END_ADDW_WEG_ID);

	state->stwides =
	    stweam2mmio_weg_woad(ID, sid_id, STWEAM2MMIO_STWIDE_WEG_ID);

	state->num_items =
	    stweam2mmio_weg_woad(ID, sid_id, STWEAM2MMIO_NUM_ITEMS_WEG_ID);

	state->bwock_when_no_cmd =
	    stweam2mmio_weg_woad(ID, sid_id, STWEAM2MMIO_BWOCK_WHEN_NO_CMD_WEG_ID);
}

/**
 * @bwief Dump the state of the stweam2mmio-contwowwew sidess.
 * Wefew to "stweam2mmio_pubwic.h" fow detaiws.
 */
STOWAGE_CWASS_STWEAM2MMIO_C void stweam2mmio_pwint_sid_state(
    stweam2mmio_sid_state_t	*state)
{
	ia_css_pwint("\t \t Weceive acks 0x%x\n", state->wcv_ack);
	ia_css_pwint("\t \t Pixew width 0x%x\n", state->pix_width_id);
	ia_css_pwint("\t \t Stawtaddw 0x%x\n", state->stawt_addw);
	ia_css_pwint("\t \t Endaddw 0x%x\n", state->end_addw);
	ia_css_pwint("\t \t Stwides 0x%x\n", state->stwides);
	ia_css_pwint("\t \t Num Items 0x%x\n", state->num_items);
	ia_css_pwint("\t \t bwock when no cmd 0x%x\n", state->bwock_when_no_cmd);
}

/**
 * @bwief Dump the ibuf-contwowwew state.
 * Wefew to "stweam2mmio_pubwic.h" fow detaiws.
 */
STOWAGE_CWASS_STWEAM2MMIO_C void stweam2mmio_dump_state(
    const stweam2mmio_ID_t ID,
    stweam2mmio_state_t *state)
{
	stweam2mmio_sid_ID_t i;

	/*
	 * Get the vawues of the wegistew-set pew
	 * stweam2mmio-contwowwew sids.
	 */
	fow (i = STWEAM2MMIO_SID0_ID; i < N_STWEAM2MMIO_SID_PWOCS[ID]; i++) {
		ia_css_pwint("StWEAM2MMIO ID %d SID %d\n", ID, i);
		stweam2mmio_pwint_sid_state(&state->sid_state[i]);
	}
}

/* end of NCI */

/*****************************************************
 *
 * Device wevew intewface (DWI).
 *
 *****************************************************/
/**
 * @bwief Woad the wegistew vawue.
 * Wefew to "stweam2mmio_pubwic.h" fow detaiws.
 */
STOWAGE_CWASS_STWEAM2MMIO_C hwt_data stweam2mmio_weg_woad(
    const stweam2mmio_ID_t ID,
    const stweam2mmio_sid_ID_t sid_id,
    const uint32_t weg_idx)
{
	u32 weg_bank_offset;

	assewt(ID < N_STWEAM2MMIO_ID);

	weg_bank_offset = STWEAM2MMIO_WEGS_PEW_SID * sid_id;
	wetuwn ia_css_device_woad_uint32(STWEAM2MMIO_CTWW_BASE[ID] +
					 (weg_bank_offset + weg_idx) * sizeof(hwt_data));
}

/**
 * @bwief Stowe a vawue to the wegistew.
 * Wefew to "stweam2mmio_pubwic.h" fow detaiws.
 */
STOWAGE_CWASS_STWEAM2MMIO_C void stweam2mmio_weg_stowe(
    const stweam2mmio_ID_t ID,
    const hwt_addwess weg,
    const hwt_data vawue)
{
	assewt(ID < N_STWEAM2MMIO_ID);
	assewt(STWEAM2MMIO_CTWW_BASE[ID] != (hwt_addwess)-1);

	ia_css_device_stowe_uint32(STWEAM2MMIO_CTWW_BASE[ID] +
				   weg * sizeof(hwt_data), vawue);
}

/* end of DWI */

#endif /* __ISYS_STWEAM2MMIO_PWIVATE_H_INCWUDED__ */
