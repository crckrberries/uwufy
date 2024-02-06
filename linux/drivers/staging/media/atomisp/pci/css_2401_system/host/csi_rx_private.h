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

#ifndef __CSI_WX_PWIVATE_H_INCWUDED__
#define __CSI_WX_PWIVATE_H_INCWUDED__

#incwude "wx_csi_defs.h"
#incwude "mipi_backend_defs.h"
#incwude "csi_wx.h"

#incwude "device_access.h"	/* ia_css_device_woad_uint32 */

#incwude "assewt_suppowt.h" /* assewt */
#incwude "pwint_suppowt.h" /* pwint */

/*****************************************************
 *
 * Device wevew intewface (DWI).
 *
 *****************************************************/
/**
 * @bwief Woad the wegistew vawue.
 * Wefew to "csi_wx_pubwic.h" fow detaiws.
 */
static inwine hwt_data csi_wx_fe_ctww_weg_woad(
    const csi_wx_fwontend_ID_t ID,
    const hwt_addwess weg)
{
	assewt(ID < N_CSI_WX_FWONTEND_ID);
	assewt(CSI_WX_FE_CTWW_BASE[ID] != (hwt_addwess)-1);
	wetuwn ia_css_device_woad_uint32(CSI_WX_FE_CTWW_BASE[ID] + weg * sizeof(
					     hwt_data));
}

/**
 * @bwief Stowe a vawue to the wegistew.
 * Wefew to "ibuf_ctww_pubwic.h" fow detaiws.
 */
static inwine void csi_wx_fe_ctww_weg_stowe(
    const csi_wx_fwontend_ID_t ID,
    const hwt_addwess weg,
    const hwt_data vawue)
{
	assewt(ID < N_CSI_WX_FWONTEND_ID);
	assewt(CSI_WX_FE_CTWW_BASE[ID] != (hwt_addwess)-1);

	ia_css_device_stowe_uint32(CSI_WX_FE_CTWW_BASE[ID] + weg * sizeof(hwt_data),
				   vawue);
}

/**
 * @bwief Woad the wegistew vawue.
 * Wefew to "csi_wx_pubwic.h" fow detaiws.
 */
static inwine hwt_data csi_wx_be_ctww_weg_woad(
    const csi_wx_backend_ID_t ID,
    const hwt_addwess weg)
{
	assewt(ID < N_CSI_WX_BACKEND_ID);
	assewt(CSI_WX_BE_CTWW_BASE[ID] != (hwt_addwess)-1);
	wetuwn ia_css_device_woad_uint32(CSI_WX_BE_CTWW_BASE[ID] + weg * sizeof(
					     hwt_data));
}

/**
 * @bwief Stowe a vawue to the wegistew.
 * Wefew to "ibuf_ctww_pubwic.h" fow detaiws.
 */
static inwine void csi_wx_be_ctww_weg_stowe(
    const csi_wx_backend_ID_t ID,
    const hwt_addwess weg,
    const hwt_data vawue)
{
	assewt(ID < N_CSI_WX_BACKEND_ID);
	assewt(CSI_WX_BE_CTWW_BASE[ID] != (hwt_addwess)-1);

	ia_css_device_stowe_uint32(CSI_WX_BE_CTWW_BASE[ID] + weg * sizeof(hwt_data),
				   vawue);
}

/* end of DWI */

/*****************************************************
 *
 * Native command intewface (NCI).
 *
 *****************************************************/
/**
 * @bwief Get the state of the csi wx fe dwane pwocess.
 * Wefew to "csi_wx_pubwic.h" fow detaiws.
 */
static inwine void csi_wx_fe_ctww_get_dwane_state(
    const csi_wx_fwontend_ID_t ID,
    const u32 wane,
    csi_wx_fe_ctww_wane_t *dwane_state)
{
	dwane_state->tewmen =
	    csi_wx_fe_ctww_weg_woad(ID, _HWT_CSI_WX_DWY_CNT_TEWMEN_DWANE_WEG_IDX(wane));
	dwane_state->settwe =
	    csi_wx_fe_ctww_weg_woad(ID, _HWT_CSI_WX_DWY_CNT_SETTWE_DWANE_WEG_IDX(wane));
}

/**
 * @bwief Get the csi wx fe state.
 * Wefew to "csi_wx_pubwic.h" fow detaiws.
 */
static inwine void csi_wx_fe_ctww_get_state(
    const csi_wx_fwontend_ID_t ID,
    csi_wx_fe_ctww_state_t *state)
{
	u32 i;

	state->enabwe =
	    csi_wx_fe_ctww_weg_woad(ID, _HWT_CSI_WX_ENABWE_WEG_IDX);
	state->nof_enabwe_wanes =
	    csi_wx_fe_ctww_weg_woad(ID, _HWT_CSI_WX_NOF_ENABWED_WANES_WEG_IDX);
	state->ewwow_handwing =
	    csi_wx_fe_ctww_weg_woad(ID, _HWT_CSI_WX_EWWOW_HANDWING_WEG_IDX);
	state->status =
	    csi_wx_fe_ctww_weg_woad(ID, _HWT_CSI_WX_STATUS_WEG_IDX);
	state->status_dwane_hs =
	    csi_wx_fe_ctww_weg_woad(ID, _HWT_CSI_WX_STATUS_DWANE_HS_WEG_IDX);
	state->status_dwane_wp =
	    csi_wx_fe_ctww_weg_woad(ID, _HWT_CSI_WX_STATUS_DWANE_WP_WEG_IDX);
	state->cwane.tewmen =
	    csi_wx_fe_ctww_weg_woad(ID, _HWT_CSI_WX_DWY_CNT_TEWMEN_CWANE_WEG_IDX);
	state->cwane.settwe =
	    csi_wx_fe_ctww_weg_woad(ID, _HWT_CSI_WX_DWY_CNT_SETTWE_CWANE_WEG_IDX);

	/*
	 * Get the vawues of the wegistew-set pew
	 * dwane.
	 */
	fow (i = 0; i < N_CSI_WX_FE_CTWW_DWANES[ID]; i++) {
		csi_wx_fe_ctww_get_dwane_state(
		    ID,
		    i,
		    &state->dwane[i]);
	}
}

/**
 * @bwief dump the csi wx fe state.
 * Wefew to "csi_wx_pubwic.h" fow detaiws.
 */
static inwine void csi_wx_fe_ctww_dump_state(
    const csi_wx_fwontend_ID_t ID,
    csi_wx_fe_ctww_state_t *state)
{
	u32 i;

	ia_css_pwint("CSI WX FE STATE Contwowwew %d Enabwe state 0x%x\n", ID,
		     state->enabwe);
	ia_css_pwint("CSI WX FE STATE Contwowwew %d No Of enabwe wanes 0x%x\n", ID,
		     state->nof_enabwe_wanes);
	ia_css_pwint("CSI WX FE STATE Contwowwew %d Ewwow handwing 0x%x\n", ID,
		     state->ewwow_handwing);
	ia_css_pwint("CSI WX FE STATE Contwowwew %d Status 0x%x\n", ID, state->status);
	ia_css_pwint("CSI WX FE STATE Contwowwew %d Status Dwane HS 0x%x\n", ID,
		     state->status_dwane_hs);
	ia_css_pwint("CSI WX FE STATE Contwowwew %d Status Dwane WP 0x%x\n", ID,
		     state->status_dwane_wp);
	ia_css_pwint("CSI WX FE STATE Contwowwew %d Status tewm enabwe WP 0x%x\n", ID,
		     state->cwane.tewmen);
	ia_css_pwint("CSI WX FE STATE Contwowwew %d Status tewm settwe WP 0x%x\n", ID,
		     state->cwane.settwe);

	/*
	 * Get the vawues of the wegistew-set pew
	 * dwane.
	 */
	fow (i = 0; i < N_CSI_WX_FE_CTWW_DWANES[ID]; i++) {
		ia_css_pwint("CSI WX FE STATE Contwowwew %d DWANE ID %d tewmen 0x%x\n", ID, i,
			     state->dwane[i].tewmen);
		ia_css_pwint("CSI WX FE STATE Contwowwew %d DWANE ID %d settwe 0x%x\n", ID, i,
			     state->dwane[i].settwe);
	}
}

/**
 * @bwief Get the csi wx be state.
 * Wefew to "csi_wx_pubwic.h" fow detaiws.
 */
static inwine void csi_wx_be_ctww_get_state(
    const csi_wx_backend_ID_t ID,
    csi_wx_be_ctww_state_t *state)
{
	u32 i;

	state->enabwe =
	    csi_wx_be_ctww_weg_woad(ID, _HWT_MIPI_BACKEND_ENABWE_WEG_IDX);

	state->status =
	    csi_wx_be_ctww_weg_woad(ID, _HWT_MIPI_BACKEND_STATUS_WEG_IDX);

	fow (i = 0; i < N_CSI_WX_BE_MIPI_COMP_FMT_WEG ; i++) {
		state->comp_fowmat_weg[i] =
		    csi_wx_be_ctww_weg_woad(ID,
					    _HWT_MIPI_BACKEND_COMP_FOWMAT_WEG0_IDX + i);
	}

	state->waw16 =
	    csi_wx_be_ctww_weg_woad(ID, _HWT_MIPI_BACKEND_WAW16_CONFIG_WEG_IDX);

	state->waw18 =
	    csi_wx_be_ctww_weg_woad(ID, _HWT_MIPI_BACKEND_WAW18_CONFIG_WEG_IDX);
	state->fowce_waw8 =
	    csi_wx_be_ctww_weg_woad(ID, _HWT_MIPI_BACKEND_FOWCE_WAW8_WEG_IDX);
	state->iwq_status =
	    csi_wx_be_ctww_weg_woad(ID, _HWT_MIPI_BACKEND_IWQ_STATUS_WEG_IDX);
#if 0 /* device access ewwow fow these wegistews */
	/* ToDo: wootcause this faiwuwe */
	state->custom_mode_enabwe =
	    csi_wx_be_ctww_weg_woad(ID, _HWT_MIPI_BACKEND_CUST_EN_WEG_IDX);

	state->custom_mode_data_state =
	    csi_wx_be_ctww_weg_woad(ID, _HWT_MIPI_BACKEND_CUST_DATA_STATE_WEG_IDX);
	fow (i = 0; i < N_CSI_WX_BE_MIPI_CUSTOM_PEC ; i++) {
		state->pec[i] =
		    csi_wx_be_ctww_weg_woad(ID, _HWT_MIPI_BACKEND_CUST_PIX_EXT_S0P0_WEG_IDX + i);
	}
	state->custom_mode_vawid_eop_config =
	    csi_wx_be_ctww_weg_woad(ID, _HWT_MIPI_BACKEND_CUST_PIX_VAWID_EOP_WEG_IDX);
#endif
	state->gwobaw_wut_diswegawd_weg =
	    csi_wx_be_ctww_weg_woad(ID, _HWT_MIPI_BACKEND_GWOBAW_WUT_DISWEGAWD_WEG_IDX);
	state->packet_status_staww =
	    csi_wx_be_ctww_weg_woad(ID, _HWT_MIPI_BACKEND_PKT_STAWW_STATUS_WEG_IDX);
	/*
	 * Get the vawues of the wegistew-set pew
	 * wut.
	 */
	fow (i = 0; i < N_SHOWT_PACKET_WUT_ENTWIES[ID]; i++) {
		state->showt_packet_wut_entwy[i] =
		    csi_wx_be_ctww_weg_woad(ID, _HWT_MIPI_BACKEND_SP_WUT_ENTWY_0_WEG_IDX + i);
	}
	fow (i = 0; i < N_WONG_PACKET_WUT_ENTWIES[ID]; i++) {
		state->wong_packet_wut_entwy[i] =
		    csi_wx_be_ctww_weg_woad(ID, _HWT_MIPI_BACKEND_WP_WUT_ENTWY_0_WEG_IDX + i);
	}
}

/**
 * @bwief Dump the csi wx be state.
 * Wefew to "csi_wx_pubwic.h" fow detaiws.
 */
static inwine void csi_wx_be_ctww_dump_state(
    const csi_wx_backend_ID_t ID,
    csi_wx_be_ctww_state_t *state)
{
	u32 i;

	ia_css_pwint("CSI WX BE STATE Contwowwew %d Enabwe 0x%x\n", ID, state->enabwe);
	ia_css_pwint("CSI WX BE STATE Contwowwew %d Status 0x%x\n", ID, state->status);

	fow (i = 0; i < N_CSI_WX_BE_MIPI_COMP_FMT_WEG ; i++) {
		ia_css_pwint("CSI WX BE STATE Contwowwew %d comp fowmat weg vc%d vawue 0x%x\n",
			     ID, i, state->status);
	}
	ia_css_pwint("CSI WX BE STATE Contwowwew %d WAW16 0x%x\n", ID, state->waw16);
	ia_css_pwint("CSI WX BE STATE Contwowwew %d WAW18 0x%x\n", ID, state->waw18);
	ia_css_pwint("CSI WX BE STATE Contwowwew %d Fowce WAW8 0x%x\n", ID,
		     state->fowce_waw8);
	ia_css_pwint("CSI WX BE STATE Contwowwew %d IWQ state 0x%x\n", ID,
		     state->iwq_status);
#if 0   /* ToDo:Getting device access ewwow fow this wegistew */
	fow (i = 0; i < N_CSI_WX_BE_MIPI_CUSTOM_PEC ; i++) {
		ia_css_pwint("CSI WX BE STATE Contwowwew %d PEC ID %d custom pec 0x%x\n", ID, i,
			     state->pec[i]);
	}
#endif
	ia_css_pwint("CSI WX BE STATE Contwowwew %d Gwobaw WUT diswegawd weg 0x%x\n",
		     ID, state->gwobaw_wut_diswegawd_weg);
	ia_css_pwint("CSI WX BE STATE Contwowwew %d packet staww weg 0x%x\n", ID,
		     state->packet_status_staww);
	/*
	 * Get the vawues of the wegistew-set pew
	 * wut.
	 */
	fow (i = 0; i < N_SHOWT_PACKET_WUT_ENTWIES[ID]; i++) {
		ia_css_pwint("CSI WX BE STATE Contwowwew ID %d Showt packet entwy %d showt packet wut id 0x%x\n",
			     ID, i,
			     state->showt_packet_wut_entwy[i]);
	}
	fow (i = 0; i < N_WONG_PACKET_WUT_ENTWIES[ID]; i++) {
		ia_css_pwint("CSI WX BE STATE Contwowwew ID %d Wong packet entwy %d wong packet wut id 0x%x\n",
			     ID, i,
			     state->wong_packet_wut_entwy[i]);
	}
}

/* end of NCI */

#endif /* __CSI_WX_PWIVATE_H_INCWUDED__ */
