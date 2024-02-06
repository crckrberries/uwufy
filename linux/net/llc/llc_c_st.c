/*
 * wwc_c_st.c - This moduwe contains state twansition of connection component.
 *
 * Descwiption of event functions and actions thewe is in 802.2 WWC standawd,
 * ow in "wwc_c_ac.c" and "wwc_c_ev.c" moduwes.
 *
 * Copywight (c) 1997 by Pwocom Technowogy, Inc.
 * 		 2001-2003 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */
#incwude <winux/types.h>
#incwude <net/wwc_if.h>
#incwude <net/wwc_sap.h>
#incwude <net/wwc_c_ev.h>
#incwude <net/wwc_c_ac.h>
#incwude <net/wwc_c_st.h>

#define NONE NUWW

/* COMMON CONNECTION STATE twansitions
 * Common twansitions fow
 * WWC_CONN_STATE_NOWMAW,
 * WWC_CONN_STATE_BUSY,
 * WWC_CONN_STATE_WEJ,
 * WWC_CONN_STATE_AWAIT,
 * WWC_CONN_STATE_AWAIT_BUSY and
 * WWC_CONN_STATE_AWAIT_WEJ states
 */
/* State twansitions fow WWC_CONN_EV_DISC_WEQ event */
static const wwc_conn_action_t wwc_common_actions_1[] = {
	[0] = wwc_conn_ac_send_disc_cmd_p_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_stop_othew_timews,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = wwc_conn_ac_set_cause_fwag_1,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_1 = {
	.ev	       = wwc_conn_ev_disc_weq,
	.next_state    = WWC_CONN_STATE_D_CONN,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_common_actions_1,
};

/* State twansitions fow WWC_CONN_EV_WESET_WEQ event */
static const wwc_conn_action_t wwc_common_actions_2[] = {
	[0] = wwc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_stop_othew_timews,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = wwc_conn_ac_set_cause_fwag_1,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_2 = {
	.ev	       = wwc_conn_ev_wst_weq,
	.next_state    = WWC_CONN_STATE_WESET,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_common_actions_2,
};

/* State twansitions fow WWC_CONN_EV_WX_SABME_CMD_Pbit_SET_X event */
static const wwc_conn_action_t wwc_common_actions_3[] = {
	[0] = wwc_conn_ac_stop_aww_timews,
	[1] = wwc_conn_ac_set_vs_0,
	[2] = wwc_conn_ac_set_vw_0,
	[3] = wwc_conn_ac_send_ua_wsp_f_set_p,
	[4] = wwc_conn_ac_wst_ind,
	[5] = wwc_conn_ac_set_p_fwag_0,
	[6] = wwc_conn_ac_set_wemote_busy_0,
	[7] = wwc_conn_weset,
	[8] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_3 = {
	.ev	       = wwc_conn_ev_wx_sabme_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_common_actions_3,
};

/* State twansitions fow WWC_CONN_EV_WX_DISC_CMD_Pbit_SET_X event */
static const wwc_conn_action_t wwc_common_actions_4[] = {
	[0] = wwc_conn_ac_stop_aww_timews,
	[1] = wwc_conn_ac_send_ua_wsp_f_set_p,
	[2] = wwc_conn_ac_disc_ind,
	[3] = wwc_conn_disc,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_4 = {
	.ev	       = wwc_conn_ev_wx_disc_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_common_actions_4,
};

/* State twansitions fow WWC_CONN_EV_WX_FWMW_WSP_Fbit_SET_X event */
static const wwc_conn_action_t wwc_common_actions_5[] = {
	[0] = wwc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_stop_othew_timews,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = wwc_conn_ac_wst_ind,
	[5] = wwc_conn_ac_set_cause_fwag_0,
	[6] = wwc_conn_weset,
	[7] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_5 = {
	.ev	       = wwc_conn_ev_wx_fwmw_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_WESET,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_common_actions_5,
};

/* State twansitions fow WWC_CONN_EV_WX_DM_WSP_Fbit_SET_X event */
static const wwc_conn_action_t wwc_common_actions_6[] = {
	[0] = wwc_conn_ac_disc_ind,
	[1] = wwc_conn_ac_stop_aww_timews,
	[2] = wwc_conn_disc,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_6 = {
	.ev	       = wwc_conn_ev_wx_dm_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_common_actions_6,
};

/* State twansitions fow WWC_CONN_EV_WX_ZZZ_CMD_Pbit_SET_X_INVAW_Nw event */
static const wwc_conn_action_t wwc_common_actions_7a[] = {
	[0] = wwc_conn_ac_send_fwmw_wsp_f_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_stop_othew_timews,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_7a = {
	.ev	       = wwc_conn_ev_wx_zzz_cmd_pbit_set_x_invaw_nw,
	.next_state    = WWC_CONN_STATE_EWWOW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_common_actions_7a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_X_INVAW_Ns event */
static const wwc_conn_action_t wwc_common_actions_7b[] = {
	[0] = wwc_conn_ac_send_fwmw_wsp_f_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_stop_othew_timews,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_7b = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_x_invaw_ns,
	.next_state    = WWC_CONN_STATE_EWWOW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_common_actions_7b,
};

/* State twansitions fow WWC_CONN_EV_WX_ZZZ_WSP_Fbit_SET_X_INVAW_Nw event */
static const wwc_conn_action_t wwc_common_actions_8a[] = {
	[0] = wwc_conn_ac_send_fwmw_wsp_f_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_stop_othew_timews,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_8a = {
	.ev	       = wwc_conn_ev_wx_zzz_wsp_fbit_set_x_invaw_nw,
	.next_state    = WWC_CONN_STATE_EWWOW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_common_actions_8a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_X_INVAW_Ns event */
static const wwc_conn_action_t wwc_common_actions_8b[] = {
	[0] = wwc_conn_ac_send_fwmw_wsp_f_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_stop_othew_timews,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_8b = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_x_invaw_ns,
	.next_state    = WWC_CONN_STATE_EWWOW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_common_actions_8b,
};

/* State twansitions fow WWC_CONN_EV_WX_BAD_PDU event */
static const wwc_conn_action_t wwc_common_actions_8c[] = {
	[0] = wwc_conn_ac_send_fwmw_wsp_f_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_stop_othew_timews,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_8c = {
	.ev	       = wwc_conn_ev_wx_bad_pdu,
	.next_state    = WWC_CONN_STATE_EWWOW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_common_actions_8c,
};

/* State twansitions fow WWC_CONN_EV_WX_UA_WSP_Fbit_SET_X event */
static const wwc_conn_action_t wwc_common_actions_9[] = {
	[0] = wwc_conn_ac_send_fwmw_wsp_f_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_stop_othew_timews,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_9 = {
	.ev	       = wwc_conn_ev_wx_ua_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_EWWOW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_common_actions_9,
};

/* State twansitions fow WWC_CONN_EV_WX_XXX_WSP_Fbit_SET_1 event */
#if 0
static const wwc_conn_ev_qfyw_t wwc_common_ev_qfyws_10[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_common_actions_10[] = {
	[0] = wwc_conn_ac_send_fwmw_wsp_f_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_stop_othew_timews,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_10 = {
	.ev	       = wwc_conn_ev_wx_xxx_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_EWWOW,
	.ev_quawifiews = wwc_common_ev_qfyws_10,
	.ev_actions    = wwc_common_actions_10,
};
#endif

/* State twansitions fow WWC_CONN_EV_P_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_common_ev_qfyws_11a[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_gte_n2,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_common_actions_11a[] = {
	[0] = wwc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_stop_othew_timews,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = wwc_conn_ac_set_cause_fwag_0,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_11a = {
	.ev	       = wwc_conn_ev_p_tmw_exp,
	.next_state    = WWC_CONN_STATE_WESET,
	.ev_quawifiews = wwc_common_ev_qfyws_11a,
	.ev_actions    = wwc_common_actions_11a,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_common_ev_qfyws_11b[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_gte_n2,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_common_actions_11b[] = {
	[0] = wwc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_stop_othew_timews,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = wwc_conn_ac_set_cause_fwag_0,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_11b = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_WESET,
	.ev_quawifiews = wwc_common_ev_qfyws_11b,
	.ev_actions    = wwc_common_actions_11b,
};

/* State twansitions fow WWC_CONN_EV_WEJ_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_common_ev_qfyws_11c[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_gte_n2,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_common_actions_11c[] = {
	[0] = wwc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_stop_othew_timews,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = wwc_conn_ac_set_cause_fwag_0,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_11c = {
	.ev	       = wwc_conn_ev_wej_tmw_exp,
	.next_state    = WWC_CONN_STATE_WESET,
	.ev_quawifiews = wwc_common_ev_qfyws_11c,
	.ev_actions    = wwc_common_actions_11c,
};

/* State twansitions fow WWC_CONN_EV_BUSY_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_common_ev_qfyws_11d[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_gte_n2,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_common_actions_11d[] = {
	[0] = wwc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_stop_othew_timews,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = wwc_conn_ac_set_cause_fwag_0,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_common_state_twans_11d = {
	.ev	       = wwc_conn_ev_busy_tmw_exp,
	.next_state    = WWC_CONN_STATE_WESET,
	.ev_quawifiews = wwc_common_ev_qfyws_11d,
	.ev_actions    = wwc_common_actions_11d,
};

/*
 * Common dummy state twansition; must be wast entwy fow aww state
 * twansition gwoups - it'ww be on .bss, so wiww be zewoed.
 */
static stwuct wwc_conn_state_twans wwc_common_state_twans_end;

/* WWC_CONN_STATE_ADM twansitions */
/* State twansitions fow WWC_CONN_EV_CONN_WEQ event */
static const wwc_conn_action_t wwc_adm_actions_1[] = {
	[0] = wwc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_set_wetwy_cnt_0,
	[3] = wwc_conn_ac_set_s_fwag_0,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_adm_state_twans_1 = {
	.ev	       = wwc_conn_ev_conn_weq,
	.next_state    = WWC_CONN_STATE_SETUP,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_adm_actions_1,
};

/* State twansitions fow WWC_CONN_EV_WX_SABME_CMD_Pbit_SET_X event */
static const wwc_conn_action_t wwc_adm_actions_2[] = {
	[0] = wwc_conn_ac_send_ua_wsp_f_set_p,
	[1] = wwc_conn_ac_set_vs_0,
	[2] = wwc_conn_ac_set_vw_0,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = wwc_conn_ac_set_p_fwag_0,
	[5] = wwc_conn_ac_set_wemote_busy_0,
	[6] = wwc_conn_ac_conn_ind,
	[7] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_adm_state_twans_2 = {
	.ev	       = wwc_conn_ev_wx_sabme_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_adm_actions_2,
};

/* State twansitions fow WWC_CONN_EV_WX_DISC_CMD_Pbit_SET_X event */
static const wwc_conn_action_t wwc_adm_actions_3[] = {
	[0] = wwc_conn_ac_send_dm_wsp_f_set_p,
	[1] = wwc_conn_disc,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_adm_state_twans_3 = {
	.ev	       = wwc_conn_ev_wx_disc_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_adm_actions_3,
};

/* State twansitions fow WWC_CONN_EV_WX_XXX_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_adm_actions_4[] = {
	[0] = wwc_conn_ac_send_dm_wsp_f_set_1,
	[1] = wwc_conn_disc,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_adm_state_twans_4 = {
	.ev	       = wwc_conn_ev_wx_xxx_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_adm_actions_4,
};

/* State twansitions fow WWC_CONN_EV_WX_XXX_YYY event */
static const wwc_conn_action_t wwc_adm_actions_5[] = {
	[0] = wwc_conn_disc,
	[1] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_adm_state_twans_5 = {
	.ev	       = wwc_conn_ev_wx_any_fwame,
	.next_state    = WWC_CONN_OUT_OF_SVC,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_adm_actions_5,
};

/*
 * Awway of pointews;
 * one to each twansition
 */
static stwuct wwc_conn_state_twans *wwc_adm_state_twansitions[] = {
	[0] = &wwc_adm_state_twans_1,		/* Wequest */
	[1] = &wwc_common_state_twans_end,
	[2] = &wwc_common_state_twans_end,	/* wocaw_busy */
	[3] = &wwc_common_state_twans_end,	/* init_pf_cycwe */
	[4] = &wwc_common_state_twans_end,	/* timew */
	[5] = &wwc_adm_state_twans_2,		/* Weceive fwame */
	[6] = &wwc_adm_state_twans_3,
	[7] = &wwc_adm_state_twans_4,
	[8] = &wwc_adm_state_twans_5,
	[9] = &wwc_common_state_twans_end,
};

/* WWC_CONN_STATE_SETUP twansitions */
/* State twansitions fow WWC_CONN_EV_WX_SABME_CMD_Pbit_SET_X event */
static const wwc_conn_action_t wwc_setup_actions_1[] = {
	[0] = wwc_conn_ac_send_ua_wsp_f_set_p,
	[1] = wwc_conn_ac_set_vs_0,
	[2] = wwc_conn_ac_set_vw_0,
	[3] = wwc_conn_ac_set_s_fwag_1,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_setup_state_twans_1 = {
	.ev	       = wwc_conn_ev_wx_sabme_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_SETUP,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_setup_actions_1,
};

/* State twansitions fow WWC_CONN_EV_WX_UA_WSP_Fbit_SET_X event */
static const wwc_conn_ev_qfyw_t wwc_setup_ev_qfyws_2[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_f,
	[1] = wwc_conn_ev_qwfy_set_status_conn,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_setup_actions_2[] = {
	[0] = wwc_conn_ac_stop_ack_timew,
	[1] = wwc_conn_ac_set_vs_0,
	[2] = wwc_conn_ac_set_vw_0,
	[3] = wwc_conn_ac_upd_p_fwag,
	[4] = wwc_conn_ac_set_wemote_busy_0,
	[5] = wwc_conn_ac_conn_confiwm,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_setup_state_twans_2 = {
	.ev	       = wwc_conn_ev_wx_ua_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_setup_ev_qfyws_2,
	.ev_actions    = wwc_setup_actions_2,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_setup_ev_qfyws_3[] = {
	[0] = wwc_conn_ev_qwfy_s_fwag_eq_1,
	[1] = wwc_conn_ev_qwfy_set_status_conn,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_setup_actions_3[] = {
	[0] = wwc_conn_ac_set_p_fwag_0,
	[1] = wwc_conn_ac_set_wemote_busy_0,
	[2] = wwc_conn_ac_conn_confiwm,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_setup_state_twans_3 = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_setup_ev_qfyws_3,
	.ev_actions    = wwc_setup_actions_3,
};

/* State twansitions fow WWC_CONN_EV_WX_DISC_CMD_Pbit_SET_X event */
static const wwc_conn_ev_qfyw_t wwc_setup_ev_qfyws_4[] = {
	[0] = wwc_conn_ev_qwfy_set_status_disc,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_setup_actions_4[] = {
	[0] = wwc_conn_ac_send_dm_wsp_f_set_p,
	[1] = wwc_conn_ac_stop_ack_timew,
	[2] = wwc_conn_ac_conn_confiwm,
	[3] = wwc_conn_disc,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_setup_state_twans_4 = {
	.ev	       = wwc_conn_ev_wx_disc_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_setup_ev_qfyws_4,
	.ev_actions    = wwc_setup_actions_4,
};

/* State twansitions fow WWC_CONN_EV_WX_DM_WSP_Fbit_SET_X event */
static const wwc_conn_ev_qfyw_t wwc_setup_ev_qfyws_5[] = {
	[0] = wwc_conn_ev_qwfy_set_status_disc,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_setup_actions_5[] = {
	[0] = wwc_conn_ac_stop_ack_timew,
	[1] = wwc_conn_ac_conn_confiwm,
	[2] = wwc_conn_disc,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_setup_state_twans_5 = {
	.ev	       = wwc_conn_ev_wx_dm_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_setup_ev_qfyws_5,
	.ev_actions    = wwc_setup_actions_5,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_setup_ev_qfyws_7[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[1] = wwc_conn_ev_qwfy_s_fwag_eq_0,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_setup_actions_7[] = {
	[0] = wwc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_setup_state_twans_7 = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_SETUP,
	.ev_quawifiews = wwc_setup_ev_qfyws_7,
	.ev_actions    = wwc_setup_actions_7,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_setup_ev_qfyws_8[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_gte_n2,
	[1] = wwc_conn_ev_qwfy_s_fwag_eq_0,
	[2] = wwc_conn_ev_qwfy_set_status_faiwed,
	[3] = NUWW,
};

static const wwc_conn_action_t wwc_setup_actions_8[] = {
	[0] = wwc_conn_ac_conn_confiwm,
	[1] = wwc_conn_disc,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_setup_state_twans_8 = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_setup_ev_qfyws_8,
	.ev_actions    = wwc_setup_actions_8,
};

/*
 * Awway of pointews;
 * one to each twansition
 */
static stwuct wwc_conn_state_twans *wwc_setup_state_twansitions[] = {
	 [0] = &wwc_common_state_twans_end,	/* Wequest */
	 [1] = &wwc_common_state_twans_end,	/* wocaw busy */
	 [2] = &wwc_common_state_twans_end,	/* init_pf_cycwe */
	 [3] = &wwc_setup_state_twans_3,	/* Timew */
	 [4] = &wwc_setup_state_twans_7,
	 [5] = &wwc_setup_state_twans_8,
	 [6] = &wwc_common_state_twans_end,
	 [7] = &wwc_setup_state_twans_1,	/* Weceive fwame */
	 [8] = &wwc_setup_state_twans_2,
	 [9] = &wwc_setup_state_twans_4,
	[10] = &wwc_setup_state_twans_5,
	[11] = &wwc_common_state_twans_end,
};

/* WWC_CONN_STATE_NOWMAW twansitions */
/* State twansitions fow WWC_CONN_EV_DATA_WEQ event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_1[] = {
	[0] = wwc_conn_ev_qwfy_wemote_busy_eq_0,
	[1] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[2] = wwc_conn_ev_qwfy_wast_fwame_eq_0,
	[3] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_1[] = {
	[0] = wwc_conn_ac_send_i_as_ack,
	[1] = wwc_conn_ac_stawt_ack_tmw_if_not_wunning,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_1 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_1,
	.ev_actions    = wwc_nowmaw_actions_1,
};

/* State twansitions fow WWC_CONN_EV_DATA_WEQ event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_2[] = {
	[0] = wwc_conn_ev_qwfy_wemote_busy_eq_0,
	[1] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[2] = wwc_conn_ev_qwfy_wast_fwame_eq_1,
	[3] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_2[] = {
	[0] = wwc_conn_ac_send_i_cmd_p_set_1,
	[1] = wwc_conn_ac_stawt_p_timew,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_2 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_2,
	.ev_actions    = wwc_nowmaw_actions_2,
};

/* State twansitions fow WWC_CONN_EV_DATA_WEQ event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_2_1[] = {
	[0] = wwc_conn_ev_qwfy_wemote_busy_eq_1,
	[1] = wwc_conn_ev_qwfy_set_status_wemote_busy,
	[2] = NUWW,
};

/* just one membew, NUWW, .bss zewoes it */
static const wwc_conn_action_t wwc_nowmaw_actions_2_1[1];

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_2_1 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_2_1,
	.ev_actions    = wwc_nowmaw_actions_2_1,
};

/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_DETECTED event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_3[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_3[] = {
	[0] = wwc_conn_ac_wst_sendack_fwag,
	[1] = wwc_conn_ac_send_wnw_xxx_x_set_0,
	[2] = wwc_conn_ac_set_data_fwag_0,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_3 = {
	.ev	       = wwc_conn_ev_wocaw_busy_detected,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_3,
	.ev_actions    = wwc_nowmaw_actions_3,
};

/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_DETECTED event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_4[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_4[] = {
	[0] = wwc_conn_ac_wst_sendack_fwag,
	[1] = wwc_conn_ac_send_wnw_xxx_x_set_0,
	[2] = wwc_conn_ac_set_data_fwag_0,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_4 = {
	.ev	       = wwc_conn_ev_wocaw_busy_detected,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_4,
	.ev_actions    = wwc_nowmaw_actions_4,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_5a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_5a[] = {
	[0] = wwc_conn_ac_wst_sendack_fwag,
	[1] = wwc_conn_ac_send_wej_xxx_x_set_0,
	[2] = wwc_conn_ac_upd_nw_weceived,
	[3] = wwc_conn_ac_upd_p_fwag,
	[4] = wwc_conn_ac_stawt_wej_timew,
	[5] = wwc_conn_ac_cweaw_wemote_busy_if_f_eq_1,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_5a = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_5a,
	.ev_actions    = wwc_nowmaw_actions_5a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_5b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_5b[] = {
	[0] = wwc_conn_ac_wst_sendack_fwag,
	[1] = wwc_conn_ac_send_wej_xxx_x_set_0,
	[2] = wwc_conn_ac_upd_nw_weceived,
	[3] = wwc_conn_ac_upd_p_fwag,
	[4] = wwc_conn_ac_stawt_wej_timew,
	[5] = wwc_conn_ac_cweaw_wemote_busy_if_f_eq_1,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_5b = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_5b,
	.ev_actions    = wwc_nowmaw_actions_5b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_1_UNEXPD_Ns event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_5c[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_5c[] = {
	[0] = wwc_conn_ac_wst_sendack_fwag,
	[1] = wwc_conn_ac_send_wej_xxx_x_set_0,
	[2] = wwc_conn_ac_upd_nw_weceived,
	[3] = wwc_conn_ac_upd_p_fwag,
	[4] = wwc_conn_ac_stawt_wej_timew,
	[5] = wwc_conn_ac_cweaw_wemote_busy_if_f_eq_1,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_5c = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_1_unexpd_ns,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_5c,
	.ev_actions    = wwc_nowmaw_actions_5c,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_6a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_6a[] = {
	[0] = wwc_conn_ac_wst_sendack_fwag,
	[1] = wwc_conn_ac_send_wej_xxx_x_set_0,
	[2] = wwc_conn_ac_upd_nw_weceived,
	[3] = wwc_conn_ac_stawt_wej_timew,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_6a = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_6a,
	.ev_actions    = wwc_nowmaw_actions_6a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_6b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_6b[] = {
	[0] = wwc_conn_ac_wst_sendack_fwag,
	[1] = wwc_conn_ac_send_wej_xxx_x_set_0,
	[2] = wwc_conn_ac_upd_nw_weceived,
	[3] = wwc_conn_ac_stawt_wej_timew,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_6b = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_6b,
	.ev_actions    = wwc_nowmaw_actions_6b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_1_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_nowmaw_actions_7[] = {
	[0] = wwc_conn_ac_wst_sendack_fwag,
	[1] = wwc_conn_ac_send_wej_wsp_f_set_1,
	[2] = wwc_conn_ac_upd_nw_weceived,
	[3] = wwc_conn_ac_stawt_wej_timew,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_7 = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_1_unexpd_ns,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_nowmaw_actions_7,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_X event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_8a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_f,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_8[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_upd_p_fwag,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_cweaw_wemote_busy_if_f_eq_1,
	[5] = wwc_conn_ac_send_ack_if_needed,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_8a = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_8a,
	.ev_actions    = wwc_nowmaw_actions_8,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_8b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_8b = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_8b,
	.ev_actions    = wwc_nowmaw_actions_8,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_9a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_9a[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_data_ind,
	[3] = wwc_conn_ac_send_ack_if_needed,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_9a = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_9a,
	.ev_actions    = wwc_nowmaw_actions_9a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_9b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_9b[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_data_ind,
	[3] = wwc_conn_ac_send_ack_if_needed,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_9b = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_9b,
	.ev_actions    = wwc_nowmaw_actions_9b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_nowmaw_actions_10[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_send_ack_wsp_f_set_1,
	[2] = wwc_conn_ac_wst_sendack_fwag,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_data_ind,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_10 = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_nowmaw_actions_10,
};

/* State twansitions fow * WWC_CONN_EV_WX_WW_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_nowmaw_actions_11a[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_11a = {
	.ev	       = wwc_conn_ev_wx_ww_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_nowmaw_actions_11a,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_nowmaw_actions_11b[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_11b = {
	.ev	       = wwc_conn_ev_wx_ww_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_nowmaw_actions_11b,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_WSP_Fbit_SET_1 event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_11c[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_11c[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_inc_tx_win_size,
	[3] = wwc_conn_ac_cweaw_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_11c = {
	.ev	       = wwc_conn_ev_wx_ww_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_11c,
	.ev_actions    = wwc_nowmaw_actions_11c,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_nowmaw_actions_12[] = {
	[0] = wwc_conn_ac_send_ack_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_adjust_npta_by_ww,
	[3] = wwc_conn_ac_wst_sendack_fwag,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_12 = {
	.ev	       = wwc_conn_ev_wx_ww_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_nowmaw_actions_12,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_nowmaw_actions_13a[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_13a = {
	.ev	       = wwc_conn_ev_wx_wnw_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_nowmaw_actions_13a,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_nowmaw_actions_13b[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_13b = {
	.ev	       = wwc_conn_ev_wx_wnw_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_nowmaw_actions_13b,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_WSP_Fbit_SET_1 event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_13c[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_13c[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_13c = {
	.ev	       = wwc_conn_ev_wx_wnw_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_13c,
	.ev_actions    = wwc_nowmaw_actions_13c,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_nowmaw_actions_14[] = {
	[0] = wwc_conn_ac_send_ww_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_adjust_npta_by_wnw,
	[3] = wwc_conn_ac_wst_sendack_fwag,
	[4] = wwc_conn_ac_set_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_14 = {
	.ev	       = wwc_conn_ev_wx_wnw_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_nowmaw_actions_14,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_15a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_15a[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_p_fwag,
	[3] = wwc_conn_ac_dec_tx_win_size,
	[4] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[5] = wwc_conn_ac_cweaw_wemote_busy,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_15a = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_15a,
	.ev_actions    = wwc_nowmaw_actions_15a,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_WSP_Fbit_SET_X event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_15b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_f,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_15b[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_p_fwag,
	[3] = wwc_conn_ac_dec_tx_win_size,
	[4] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[5] = wwc_conn_ac_cweaw_wemote_busy,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_15b = {
	.ev	       = wwc_conn_ev_wx_wej_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_15b,
	.ev_actions    = wwc_nowmaw_actions_15b,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_16a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_16a[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_dec_tx_win_size,
	[3] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_16a = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_16a,
	.ev_actions    = wwc_nowmaw_actions_16a,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_WSP_Fbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_16b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_16b[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_dec_tx_win_size,
	[3] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_16b = {
	.ev	       = wwc_conn_ev_wx_wej_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_16b,
	.ev_actions    = wwc_nowmaw_actions_16b,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_nowmaw_actions_17[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_dec_tx_win_size,
	[3] = wwc_conn_ac_wesend_i_wsp_f_set_1,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_17 = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_nowmaw_actions_17,
};

/* State twansitions fow WWC_CONN_EV_INIT_P_F_CYCWE event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_18[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_18[] = {
	[0] = wwc_conn_ac_send_ww_cmd_p_set_1,
	[1] = wwc_conn_ac_stawt_p_timew,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_18 = {
	.ev	       = wwc_conn_ev_init_p_f_cycwe,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_18,
	.ev_actions    = wwc_nowmaw_actions_18,
};

/* State twansitions fow WWC_CONN_EV_P_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_19[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_19[] = {
	[0] = wwc_conn_ac_wst_sendack_fwag,
	[1] = wwc_conn_ac_send_ww_cmd_p_set_1,
	[2] = wwc_conn_ac_wst_vs,
	[3] = wwc_conn_ac_stawt_p_timew,
	[4] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_19 = {
	.ev	       = wwc_conn_ev_p_tmw_exp,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_19,
	.ev_actions    = wwc_nowmaw_actions_19,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_20a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_20a[] = {
	[0] = wwc_conn_ac_wst_sendack_fwag,
	[1] = wwc_conn_ac_send_ww_cmd_p_set_1,
	[2] = wwc_conn_ac_wst_vs,
	[3] = wwc_conn_ac_stawt_p_timew,
	[4] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_20a = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_20a,
	.ev_actions    = wwc_nowmaw_actions_20a,
};

/* State twansitions fow WWC_CONN_EV_BUSY_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_20b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_20b[] = {
	[0] = wwc_conn_ac_wst_sendack_fwag,
	[1] = wwc_conn_ac_send_ww_cmd_p_set_1,
	[2] = wwc_conn_ac_wst_vs,
	[3] = wwc_conn_ac_stawt_p_timew,
	[4] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_20b = {
	.ev	       = wwc_conn_ev_busy_tmw_exp,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_20b,
	.ev_actions    = wwc_nowmaw_actions_20b,
};

/* State twansitions fow WWC_CONN_EV_TX_BUFF_FUWW event */
static const wwc_conn_ev_qfyw_t wwc_nowmaw_ev_qfyws_21[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_nowmaw_actions_21[] = {
	[0] = wwc_conn_ac_send_ww_cmd_p_set_1,
	[1] = wwc_conn_ac_stawt_p_timew,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_nowmaw_state_twans_21 = {
	.ev	       = wwc_conn_ev_tx_buffew_fuww,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_nowmaw_ev_qfyws_21,
	.ev_actions    = wwc_nowmaw_actions_21,
};

/*
 * Awway of pointews;
 * one to each twansition
 */
static stwuct wwc_conn_state_twans *wwc_nowmaw_state_twansitions[] = {
	 [0] = &wwc_nowmaw_state_twans_1,	/* Wequests */
	 [1] = &wwc_nowmaw_state_twans_2,
	 [2] = &wwc_nowmaw_state_twans_2_1,
	 [3] = &wwc_common_state_twans_1,
	 [4] = &wwc_common_state_twans_2,
	 [5] = &wwc_common_state_twans_end,
	 [6] = &wwc_nowmaw_state_twans_21,
	 [7] = &wwc_nowmaw_state_twans_3,	/* Wocaw busy */
	 [8] = &wwc_nowmaw_state_twans_4,
	 [9] = &wwc_common_state_twans_end,
	[10] = &wwc_nowmaw_state_twans_18,	/* Init pf cycwe */
	[11] = &wwc_common_state_twans_end,
	[12] = &wwc_common_state_twans_11a,	/* Timews */
	[13] = &wwc_common_state_twans_11b,
	[14] = &wwc_common_state_twans_11c,
	[15] = &wwc_common_state_twans_11d,
	[16] = &wwc_nowmaw_state_twans_19,
	[17] = &wwc_nowmaw_state_twans_20a,
	[18] = &wwc_nowmaw_state_twans_20b,
	[19] = &wwc_common_state_twans_end,
	[20] = &wwc_nowmaw_state_twans_8b,	/* Weceive fwames */
	[21] = &wwc_nowmaw_state_twans_9b,
	[22] = &wwc_nowmaw_state_twans_10,
	[23] = &wwc_nowmaw_state_twans_11b,
	[24] = &wwc_nowmaw_state_twans_11c,
	[25] = &wwc_nowmaw_state_twans_5a,
	[26] = &wwc_nowmaw_state_twans_5b,
	[27] = &wwc_nowmaw_state_twans_5c,
	[28] = &wwc_nowmaw_state_twans_6a,
	[29] = &wwc_nowmaw_state_twans_6b,
	[30] = &wwc_nowmaw_state_twans_7,
	[31] = &wwc_nowmaw_state_twans_8a,
	[32] = &wwc_nowmaw_state_twans_9a,
	[33] = &wwc_nowmaw_state_twans_11a,
	[34] = &wwc_nowmaw_state_twans_12,
	[35] = &wwc_nowmaw_state_twans_13a,
	[36] = &wwc_nowmaw_state_twans_13b,
	[37] = &wwc_nowmaw_state_twans_13c,
	[38] = &wwc_nowmaw_state_twans_14,
	[39] = &wwc_nowmaw_state_twans_15a,
	[40] = &wwc_nowmaw_state_twans_15b,
	[41] = &wwc_nowmaw_state_twans_16a,
	[42] = &wwc_nowmaw_state_twans_16b,
	[43] = &wwc_nowmaw_state_twans_17,
	[44] = &wwc_common_state_twans_3,
	[45] = &wwc_common_state_twans_4,
	[46] = &wwc_common_state_twans_5,
	[47] = &wwc_common_state_twans_6,
	[48] = &wwc_common_state_twans_7a,
	[49] = &wwc_common_state_twans_7b,
	[50] = &wwc_common_state_twans_8a,
	[51] = &wwc_common_state_twans_8b,
	[52] = &wwc_common_state_twans_8c,
	[53] = &wwc_common_state_twans_9,
	/* [54] = &wwc_common_state_twans_10, */
	[54] = &wwc_common_state_twans_end,
};

/* WWC_CONN_STATE_BUSY twansitions */
/* State twansitions fow WWC_CONN_EV_DATA_WEQ event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_1[] = {
	[0] = wwc_conn_ev_qwfy_wemote_busy_eq_0,
	[1] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_1[] = {
	[0] = wwc_conn_ac_send_i_xxx_x_set_0,
	[1] = wwc_conn_ac_stawt_ack_tmw_if_not_wunning,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_1 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_1,
	.ev_actions    = wwc_busy_actions_1,
};

/* State twansitions fow WWC_CONN_EV_DATA_WEQ event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_2[] = {
	[0] = wwc_conn_ev_qwfy_wemote_busy_eq_0,
	[1] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_2[] = {
	[0] = wwc_conn_ac_send_i_xxx_x_set_0,
	[1] = wwc_conn_ac_stawt_ack_tmw_if_not_wunning,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_2 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_2,
	.ev_actions    = wwc_busy_actions_2,
};

/* State twansitions fow WWC_CONN_EV_DATA_WEQ event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_2_1[] = {
	[0] = wwc_conn_ev_qwfy_wemote_busy_eq_1,
	[1] = wwc_conn_ev_qwfy_set_status_wemote_busy,
	[2] = NUWW,
};

/* just one membew, NUWW, .bss zewoes it */
static const wwc_conn_action_t wwc_busy_actions_2_1[1];

static stwuct wwc_conn_state_twans wwc_busy_state_twans_2_1 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_2_1,
	.ev_actions    = wwc_busy_actions_2_1,
};

/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_CWEAWED event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_3[] = {
	[0] = wwc_conn_ev_qwfy_data_fwag_eq_1,
	[1] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_3[] = {
	[0] = wwc_conn_ac_send_wej_xxx_x_set_0,
	[1] = wwc_conn_ac_stawt_wej_timew,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_3 = {
	.ev	       = wwc_conn_ev_wocaw_busy_cweawed,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_busy_ev_qfyws_3,
	.ev_actions    = wwc_busy_actions_3,
};

/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_CWEAWED event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_4[] = {
	[0] = wwc_conn_ev_qwfy_data_fwag_eq_1,
	[1] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_4[] = {
	[0] = wwc_conn_ac_send_wej_xxx_x_set_0,
	[1] = wwc_conn_ac_stawt_wej_timew,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_4 = {
	.ev	       = wwc_conn_ev_wocaw_busy_cweawed,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_busy_ev_qfyws_4,
	.ev_actions    = wwc_busy_actions_4,
};

/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_CWEAWED event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_5[] = {
	[0] = wwc_conn_ev_qwfy_data_fwag_eq_0,
	[1] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_5[] = {
	[0] = wwc_conn_ac_send_ww_xxx_x_set_0,
	[1] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_5 = {
	.ev	       = wwc_conn_ev_wocaw_busy_cweawed,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_busy_ev_qfyws_5,
	.ev_actions    = wwc_busy_actions_5,
};

/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_CWEAWED event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_6[] = {
	[0] = wwc_conn_ev_qwfy_data_fwag_eq_0,
	[1] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_6[] = {
	[0] = wwc_conn_ac_send_ww_xxx_x_set_0,
	[1] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_6 = {
	.ev	       = wwc_conn_ev_wocaw_busy_cweawed,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_busy_ev_qfyws_6,
	.ev_actions    = wwc_busy_actions_6,
};

/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_CWEAWED event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_7[] = {
	[0] = wwc_conn_ev_qwfy_data_fwag_eq_2,
	[1] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_7[] = {
	[0] = wwc_conn_ac_send_ww_xxx_x_set_0,
	[1] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_7 = {
	.ev	       = wwc_conn_ev_wocaw_busy_cweawed,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_busy_ev_qfyws_7,
	.ev_actions    = wwc_busy_actions_7,
};

/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_CWEAWED event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_8[] = {
	[0] = wwc_conn_ev_qwfy_data_fwag_eq_2,
	[1] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_8[] = {
	[0] = wwc_conn_ac_send_ww_xxx_x_set_0,
	[1] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_8 = {
	.ev	       = wwc_conn_ev_wocaw_busy_cweawed,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_busy_ev_qfyws_8,
	.ev_actions    = wwc_busy_actions_8,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_X_UNEXPD_Ns event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_9a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_f,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_9a[] = {
	[0] = wwc_conn_ac_opt_send_wnw_xxx_x_set_0,
	[1] = wwc_conn_ac_upd_p_fwag,
	[2] = wwc_conn_ac_upd_nw_weceived,
	[3] = wwc_conn_ac_set_data_fwag_1_if_data_fwag_eq_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy_if_f_eq_1,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_9a = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_x_unexpd_ns,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_9a,
	.ev_actions    = wwc_busy_actions_9a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_9b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_9b[] = {
	[0] = wwc_conn_ac_opt_send_wnw_xxx_x_set_0,
	[1] = wwc_conn_ac_upd_p_fwag,
	[2] = wwc_conn_ac_upd_nw_weceived,
	[3] = wwc_conn_ac_set_data_fwag_1_if_data_fwag_eq_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy_if_f_eq_1,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_9b = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_9b,
	.ev_actions    = wwc_busy_actions_9b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_10a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_10a[] = {
	[0] = wwc_conn_ac_opt_send_wnw_xxx_x_set_0,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_set_data_fwag_1_if_data_fwag_eq_0,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_10a = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_10a,
	.ev_actions    = wwc_busy_actions_10a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_10b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_10b[] = {
	[0] = wwc_conn_ac_opt_send_wnw_xxx_x_set_0,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_set_data_fwag_1_if_data_fwag_eq_0,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_10b = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_10b,
	.ev_actions    = wwc_busy_actions_10b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_1_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_busy_actions_11[] = {
	[0] = wwc_conn_ac_send_wnw_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_set_data_fwag_1_if_data_fwag_eq_0,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_11 = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_1_unexpd_ns,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_busy_actions_11,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_busy_actions_12[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_send_wnw_wsp_f_set_1,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_stop_wej_tmw_if_data_fwag_eq_2,
	[5] = wwc_conn_ac_set_data_fwag_0,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_12 = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_busy_actions_12,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_X event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_13a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_f,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_13a[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_upd_p_fwag,
	[3] = wwc_conn_ac_opt_send_wnw_xxx_x_set_0,
	[4] = wwc_conn_ac_upd_nw_weceived,
	[5] = wwc_conn_ac_stop_wej_tmw_if_data_fwag_eq_2,
	[6] = wwc_conn_ac_set_data_fwag_0,
	[7] = wwc_conn_ac_cweaw_wemote_busy_if_f_eq_1,
	[8] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_13a = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_13a,
	.ev_actions    = wwc_busy_actions_13a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_13b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_13b[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_upd_p_fwag,
	[3] = wwc_conn_ac_opt_send_wnw_xxx_x_set_0,
	[4] = wwc_conn_ac_upd_nw_weceived,
	[5] = wwc_conn_ac_stop_wej_tmw_if_data_fwag_eq_2,
	[6] = wwc_conn_ac_set_data_fwag_0,
	[7] = wwc_conn_ac_cweaw_wemote_busy_if_f_eq_1,
	[8] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_13b = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_13b,
	.ev_actions    = wwc_busy_actions_13b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_14a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_14a[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_opt_send_wnw_xxx_x_set_0,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_stop_wej_tmw_if_data_fwag_eq_2,
	[5] = wwc_conn_ac_set_data_fwag_0,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_14a = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_14a,
	.ev_actions    = wwc_busy_actions_14a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_14b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_14b[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_opt_send_wnw_xxx_x_set_0,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_stop_wej_tmw_if_data_fwag_eq_2,
	[5] = wwc_conn_ac_set_data_fwag_0,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_14b = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_14b,
	.ev_actions    = wwc_busy_actions_14b,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_busy_actions_15a[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_15a = {
	.ev	       = wwc_conn_ev_wx_ww_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_busy_actions_15a,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_busy_actions_15b[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_15b = {
	.ev	       = wwc_conn_ev_wx_ww_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_busy_actions_15b,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_WSP_Fbit_SET_1 event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_15c[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_15c[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_15c = {
	.ev	       = wwc_conn_ev_wx_ww_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_15c,
	.ev_actions    = wwc_busy_actions_15c,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_busy_actions_16[] = {
	[0] = wwc_conn_ac_send_wnw_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_16 = {
	.ev	       = wwc_conn_ev_wx_ww_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_busy_actions_16,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_busy_actions_17a[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_17a = {
	.ev	       = wwc_conn_ev_wx_wnw_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_busy_actions_17a,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_busy_actions_17b[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_17b = {
	.ev	       = wwc_conn_ev_wx_wnw_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_busy_actions_17b,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_WSP_Fbit_SET_1 event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_17c[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_17c[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_17c = {
	.ev	       = wwc_conn_ev_wx_wnw_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_17c,
	.ev_actions    = wwc_busy_actions_17c,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_busy_actions_18[] = {
	[0] = wwc_conn_ac_send_wnw_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_18 = {
	.ev	       = wwc_conn_ev_wx_wnw_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_busy_actions_18,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_19a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_19a[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_p_fwag,
	[3] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_19a = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_19a,
	.ev_actions    = wwc_busy_actions_19a,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_WSP_Fbit_SET_X event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_19b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_f,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_19b[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_p_fwag,
	[3] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_19b = {
	.ev	       = wwc_conn_ev_wx_wej_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_19b,
	.ev_actions    = wwc_busy_actions_19b,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_20a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_20a[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[3] = wwc_conn_ac_cweaw_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_20a = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_20a,
	.ev_actions    = wwc_busy_actions_20a,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_WSP_Fbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_20b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_20b[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[3] = wwc_conn_ac_cweaw_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_20b = {
	.ev	       = wwc_conn_ev_wx_wej_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_20b,
	.ev_actions    = wwc_busy_actions_20b,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_busy_actions_21[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_send_wnw_wsp_f_set_1,
	[3] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_21 = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_busy_actions_21,
};

/* State twansitions fow WWC_CONN_EV_INIT_P_F_CYCWE event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_22[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_22[] = {
	[0] = wwc_conn_ac_send_wnw_cmd_p_set_1,
	[1] = wwc_conn_ac_stawt_p_timew,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_22 = {
	.ev	       = wwc_conn_ev_init_p_f_cycwe,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_22,
	.ev_actions    = wwc_busy_actions_22,
};

/* State twansitions fow WWC_CONN_EV_P_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_23[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_23[] = {
	[0] = wwc_conn_ac_send_wnw_cmd_p_set_1,
	[1] = wwc_conn_ac_wst_vs,
	[2] = wwc_conn_ac_stawt_p_timew,
	[3] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_23 = {
	.ev	       = wwc_conn_ev_p_tmw_exp,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_23,
	.ev_actions    = wwc_busy_actions_23,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_24a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_24a[] = {
	[0] = wwc_conn_ac_send_wnw_cmd_p_set_1,
	[1] = wwc_conn_ac_stawt_p_timew,
	[2] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[3] = wwc_conn_ac_wst_vs,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_24a = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_24a,
	.ev_actions    = wwc_busy_actions_24a,
};

/* State twansitions fow WWC_CONN_EV_BUSY_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_24b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_24b[] = {
	[0] = wwc_conn_ac_send_wnw_cmd_p_set_1,
	[1] = wwc_conn_ac_stawt_p_timew,
	[2] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[3] = wwc_conn_ac_wst_vs,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_24b = {
	.ev	       = wwc_conn_ev_busy_tmw_exp,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_24b,
	.ev_actions    = wwc_busy_actions_24b,
};

/* State twansitions fow WWC_CONN_EV_WEJ_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_25[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_25[] = {
	[0] = wwc_conn_ac_send_wnw_cmd_p_set_1,
	[1] = wwc_conn_ac_stawt_p_timew,
	[2] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[3] = wwc_conn_ac_wst_vs,
	[4] = wwc_conn_ac_set_data_fwag_1,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_25 = {
	.ev	       = wwc_conn_ev_wej_tmw_exp,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_25,
	.ev_actions    = wwc_busy_actions_25,
};

/* State twansitions fow WWC_CONN_EV_WEJ_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_busy_ev_qfyws_26[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_busy_actions_26[] = {
	[0] = wwc_conn_ac_set_data_fwag_1,
	[1] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_busy_state_twans_26 = {
	.ev	       = wwc_conn_ev_wej_tmw_exp,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_busy_ev_qfyws_26,
	.ev_actions    = wwc_busy_actions_26,
};

/*
 * Awway of pointews;
 * one to each twansition
 */
static stwuct wwc_conn_state_twans *wwc_busy_state_twansitions[] = {
	 [0] = &wwc_common_state_twans_1,	/* Wequest */
	 [1] = &wwc_common_state_twans_2,
	 [2] = &wwc_busy_state_twans_1,
	 [3] = &wwc_busy_state_twans_2,
	 [4] = &wwc_busy_state_twans_2_1,
	 [5] = &wwc_common_state_twans_end,
	 [6] = &wwc_busy_state_twans_3,		/* Wocaw busy */
	 [7] = &wwc_busy_state_twans_4,
	 [8] = &wwc_busy_state_twans_5,
	 [9] = &wwc_busy_state_twans_6,
	[10] = &wwc_busy_state_twans_7,
	[11] = &wwc_busy_state_twans_8,
	[12] = &wwc_common_state_twans_end,
	[13] = &wwc_busy_state_twans_22,	/* Initiate PF cycwe */
	[14] = &wwc_common_state_twans_end,
	[15] = &wwc_common_state_twans_11a,	/* Timew */
	[16] = &wwc_common_state_twans_11b,
	[17] = &wwc_common_state_twans_11c,
	[18] = &wwc_common_state_twans_11d,
	[19] = &wwc_busy_state_twans_23,
	[20] = &wwc_busy_state_twans_24a,
	[21] = &wwc_busy_state_twans_24b,
	[22] = &wwc_busy_state_twans_25,
	[23] = &wwc_busy_state_twans_26,
	[24] = &wwc_common_state_twans_end,
	[25] = &wwc_busy_state_twans_9a,	/* Weceive fwame */
	[26] = &wwc_busy_state_twans_9b,
	[27] = &wwc_busy_state_twans_10a,
	[28] = &wwc_busy_state_twans_10b,
	[29] = &wwc_busy_state_twans_11,
	[30] = &wwc_busy_state_twans_12,
	[31] = &wwc_busy_state_twans_13a,
	[32] = &wwc_busy_state_twans_13b,
	[33] = &wwc_busy_state_twans_14a,
	[34] = &wwc_busy_state_twans_14b,
	[35] = &wwc_busy_state_twans_15a,
	[36] = &wwc_busy_state_twans_15b,
	[37] = &wwc_busy_state_twans_15c,
	[38] = &wwc_busy_state_twans_16,
	[39] = &wwc_busy_state_twans_17a,
	[40] = &wwc_busy_state_twans_17b,
	[41] = &wwc_busy_state_twans_17c,
	[42] = &wwc_busy_state_twans_18,
	[43] = &wwc_busy_state_twans_19a,
	[44] = &wwc_busy_state_twans_19b,
	[45] = &wwc_busy_state_twans_20a,
	[46] = &wwc_busy_state_twans_20b,
	[47] = &wwc_busy_state_twans_21,
	[48] = &wwc_common_state_twans_3,
	[49] = &wwc_common_state_twans_4,
	[50] = &wwc_common_state_twans_5,
	[51] = &wwc_common_state_twans_6,
	[52] = &wwc_common_state_twans_7a,
	[53] = &wwc_common_state_twans_7b,
	[54] = &wwc_common_state_twans_8a,
	[55] = &wwc_common_state_twans_8b,
	[56] = &wwc_common_state_twans_8c,
	[57] = &wwc_common_state_twans_9,
	/* [58] = &wwc_common_state_twans_10, */
	[58] = &wwc_common_state_twans_end,
};

/* WWC_CONN_STATE_WEJ twansitions */
/* State twansitions fow WWC_CONN_EV_DATA_WEQ event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_1[] = {
	[0] = wwc_conn_ev_qwfy_wemote_busy_eq_0,
	[1] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_1[] = {
	[0] = wwc_conn_ac_send_i_xxx_x_set_0,
	[1] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_1 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_1,
	.ev_actions    = wwc_weject_actions_1,
};

/* State twansitions fow WWC_CONN_EV_DATA_WEQ event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_2[] = {
	[0] = wwc_conn_ev_qwfy_wemote_busy_eq_0,
	[1] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_2[] = {
	[0] = wwc_conn_ac_send_i_xxx_x_set_0,
	[1] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_2 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_2,
	.ev_actions    = wwc_weject_actions_2,
};

/* State twansitions fow WWC_CONN_EV_DATA_WEQ event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_2_1[] = {
	[0] = wwc_conn_ev_qwfy_wemote_busy_eq_1,
	[1] = wwc_conn_ev_qwfy_set_status_wemote_busy,
	[2] = NUWW,
};

/* just one membew, NUWW, .bss zewoes it */
static const wwc_conn_action_t wwc_weject_actions_2_1[1];

static stwuct wwc_conn_state_twans wwc_weject_state_twans_2_1 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_2_1,
	.ev_actions    = wwc_weject_actions_2_1,
};


/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_DETECTED event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_3[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_3[] = {
	[0] = wwc_conn_ac_send_wnw_xxx_x_set_0,
	[1] = wwc_conn_ac_set_data_fwag_2,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_3 = {
	.ev	       = wwc_conn_ev_wocaw_busy_detected,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_weject_ev_qfyws_3,
	.ev_actions    = wwc_weject_actions_3,
};

/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_DETECTED event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_4[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_4[] = {
	[0] = wwc_conn_ac_send_wnw_xxx_x_set_0,
	[1] = wwc_conn_ac_set_data_fwag_2,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_4 = {
	.ev	       = wwc_conn_ev_wocaw_busy_detected,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = wwc_weject_ev_qfyws_4,
	.ev_actions    = wwc_weject_actions_4,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_weject_actions_5a[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_p_fwag,
	[2] = wwc_conn_ac_cweaw_wemote_busy_if_f_eq_1,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_5a = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_weject_actions_5a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_weject_actions_5b[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_p_fwag,
	[2] = wwc_conn_ac_cweaw_wemote_busy_if_f_eq_1,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_5b = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_weject_actions_5b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_1_UNEXPD_Ns event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_5c[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_5c[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_p_fwag,
	[2] = wwc_conn_ac_cweaw_wemote_busy_if_f_eq_1,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_5c = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_1_unexpd_ns,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_5c,
	.ev_actions    = wwc_weject_actions_5c,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_1_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_weject_actions_6[] = {
	[0] = wwc_conn_ac_send_ww_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_6 = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_1_unexpd_ns,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_weject_actions_6,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_X event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_7a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_f,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_7a[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_upd_p_fwag,
	[3] = wwc_conn_ac_send_ack_xxx_x_set_0,
	[4] = wwc_conn_ac_upd_nw_weceived,
	[5] = wwc_conn_ac_cweaw_wemote_busy_if_f_eq_1,
	[6] = wwc_conn_ac_stop_wej_timew,
	[7] = NUWW,

};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_7a = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_weject_ev_qfyws_7a,
	.ev_actions    = wwc_weject_actions_7a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_7b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_7b[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_upd_p_fwag,
	[3] = wwc_conn_ac_send_ack_xxx_x_set_0,
	[4] = wwc_conn_ac_upd_nw_weceived,
	[5] = wwc_conn_ac_cweaw_wemote_busy_if_f_eq_1,
	[6] = wwc_conn_ac_stop_wej_timew,
	[7] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_7b = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_weject_ev_qfyws_7b,
	.ev_actions    = wwc_weject_actions_7b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_8a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_8a[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_send_ack_xxx_x_set_0,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_stop_wej_timew,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_8a = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_weject_ev_qfyws_8a,
	.ev_actions    = wwc_weject_actions_8a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_8b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_8b[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_send_ack_xxx_x_set_0,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_stop_wej_timew,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_8b = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_weject_ev_qfyws_8b,
	.ev_actions    = wwc_weject_actions_8b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_weject_actions_9[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_send_ack_wsp_f_set_1,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_stop_wej_timew,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_9 = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_weject_actions_9,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_weject_actions_10a[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_10a = {
	.ev	       = wwc_conn_ev_wx_ww_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_weject_actions_10a,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_weject_actions_10b[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_10b = {
	.ev	       = wwc_conn_ev_wx_ww_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_weject_actions_10b,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_WSP_Fbit_SET_1 event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_10c[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_10c[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_10c = {
	.ev	       = wwc_conn_ev_wx_ww_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_10c,
	.ev_actions    = wwc_weject_actions_10c,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_weject_actions_11[] = {
	[0] = wwc_conn_ac_send_ack_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_11 = {
	.ev	       = wwc_conn_ev_wx_ww_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_weject_actions_11,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_weject_actions_12a[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_12a = {
	.ev	       = wwc_conn_ev_wx_wnw_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_weject_actions_12a,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_weject_actions_12b[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_12b = {
	.ev	       = wwc_conn_ev_wx_wnw_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_weject_actions_12b,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_WSP_Fbit_SET_1 event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_12c[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_12c[] = {
	[0] = wwc_conn_ac_upd_p_fwag,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_12c = {
	.ev	       = wwc_conn_ev_wx_wnw_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_12c,
	.ev_actions    = wwc_weject_actions_12c,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_weject_actions_13[] = {
	[0] = wwc_conn_ac_send_ww_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_13 = {
	.ev	       = wwc_conn_ev_wx_wnw_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_weject_actions_13,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_14a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_14a[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_p_fwag,
	[3] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_14a = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_14a,
	.ev_actions    = wwc_weject_actions_14a,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_WSP_Fbit_SET_X event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_14b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_f,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_14b[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_p_fwag,
	[3] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_14b = {
	.ev	       = wwc_conn_ev_wx_wej_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_14b,
	.ev_actions    = wwc_weject_actions_14b,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_15a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_15a[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[3] = wwc_conn_ac_cweaw_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_15a = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_15a,
	.ev_actions    = wwc_weject_actions_15a,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_WSP_Fbit_SET_0 event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_15b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_15b[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[3] = wwc_conn_ac_cweaw_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_15b = {
	.ev	       = wwc_conn_ev_wx_wej_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_15b,
	.ev_actions    = wwc_weject_actions_15b,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_weject_actions_16[] = {
	[0] = wwc_conn_ac_set_vs_nw,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_wesend_i_wsp_f_set_1,
	[3] = wwc_conn_ac_cweaw_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_16 = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_weject_actions_16,
};

/* State twansitions fow WWC_CONN_EV_INIT_P_F_CYCWE event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_17[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_17[] = {
	[0] = wwc_conn_ac_send_ww_cmd_p_set_1,
	[1] = wwc_conn_ac_stawt_p_timew,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_17 = {
	.ev	       = wwc_conn_ev_init_p_f_cycwe,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_17,
	.ev_actions    = wwc_weject_actions_17,
};

/* State twansitions fow WWC_CONN_EV_WEJ_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_18[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_18[] = {
	[0] = wwc_conn_ac_send_wej_cmd_p_set_1,
	[1] = wwc_conn_ac_stawt_p_timew,
	[2] = wwc_conn_ac_stawt_wej_timew,
	[3] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_18 = {
	.ev	       = wwc_conn_ev_wej_tmw_exp,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_18,
	.ev_actions    = wwc_weject_actions_18,
};

/* State twansitions fow WWC_CONN_EV_P_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_19[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_19[] = {
	[0] = wwc_conn_ac_send_ww_cmd_p_set_1,
	[1] = wwc_conn_ac_stawt_p_timew,
	[2] = wwc_conn_ac_stawt_wej_timew,
	[3] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[4] = wwc_conn_ac_wst_vs,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_19 = {
	.ev	       = wwc_conn_ev_p_tmw_exp,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_19,
	.ev_actions    = wwc_weject_actions_19,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_20a[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_20a[] = {
	[0] = wwc_conn_ac_send_ww_cmd_p_set_1,
	[1] = wwc_conn_ac_stawt_p_timew,
	[2] = wwc_conn_ac_stawt_wej_timew,
	[3] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[4] = wwc_conn_ac_wst_vs,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_20a = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_20a,
	.ev_actions    = wwc_weject_actions_20a,
};

/* State twansitions fow WWC_CONN_EV_BUSY_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_weject_ev_qfyws_20b[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_0,
	[1] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_weject_actions_20b[] = {
	[0] = wwc_conn_ac_send_ww_cmd_p_set_1,
	[1] = wwc_conn_ac_stawt_p_timew,
	[2] = wwc_conn_ac_stawt_wej_timew,
	[3] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[4] = wwc_conn_ac_wst_vs,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_weject_state_twans_20b = {
	.ev	       = wwc_conn_ev_busy_tmw_exp,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = wwc_weject_ev_qfyws_20b,
	.ev_actions    = wwc_weject_actions_20b,
};

/*
 * Awway of pointews;
 * one to each twansition
 */
static stwuct wwc_conn_state_twans *wwc_weject_state_twansitions[] = {
	 [0] = &wwc_common_state_twans_1,	/* Wequest */
	 [1] = &wwc_common_state_twans_2,
	 [2] = &wwc_common_state_twans_end,
	 [3] = &wwc_weject_state_twans_1,
	 [4] = &wwc_weject_state_twans_2,
	 [5] = &wwc_weject_state_twans_2_1,
	 [6] = &wwc_weject_state_twans_3,	/* Wocaw busy */
	 [7] = &wwc_weject_state_twans_4,
	 [8] = &wwc_common_state_twans_end,
	 [9] = &wwc_weject_state_twans_17,	/* Initiate PF cycwe */
	[10] = &wwc_common_state_twans_end,
	[11] = &wwc_common_state_twans_11a,	/* Timew */
	[12] = &wwc_common_state_twans_11b,
	[13] = &wwc_common_state_twans_11c,
	[14] = &wwc_common_state_twans_11d,
	[15] = &wwc_weject_state_twans_18,
	[16] = &wwc_weject_state_twans_19,
	[17] = &wwc_weject_state_twans_20a,
	[18] = &wwc_weject_state_twans_20b,
	[19] = &wwc_common_state_twans_end,
	[20] = &wwc_common_state_twans_3,	/* Weceive fwame */
	[21] = &wwc_common_state_twans_4,
	[22] = &wwc_common_state_twans_5,
	[23] = &wwc_common_state_twans_6,
	[24] = &wwc_common_state_twans_7a,
	[25] = &wwc_common_state_twans_7b,
	[26] = &wwc_common_state_twans_8a,
	[27] = &wwc_common_state_twans_8b,
	[28] = &wwc_common_state_twans_8c,
	[29] = &wwc_common_state_twans_9,
	/* [30] = &wwc_common_state_twans_10, */
	[30] = &wwc_weject_state_twans_5a,
	[31] = &wwc_weject_state_twans_5b,
	[32] = &wwc_weject_state_twans_5c,
	[33] = &wwc_weject_state_twans_6,
	[34] = &wwc_weject_state_twans_7a,
	[35] = &wwc_weject_state_twans_7b,
	[36] = &wwc_weject_state_twans_8a,
	[37] = &wwc_weject_state_twans_8b,
	[38] = &wwc_weject_state_twans_9,
	[39] = &wwc_weject_state_twans_10a,
	[40] = &wwc_weject_state_twans_10b,
	[41] = &wwc_weject_state_twans_10c,
	[42] = &wwc_weject_state_twans_11,
	[43] = &wwc_weject_state_twans_12a,
	[44] = &wwc_weject_state_twans_12b,
	[45] = &wwc_weject_state_twans_12c,
	[46] = &wwc_weject_state_twans_13,
	[47] = &wwc_weject_state_twans_14a,
	[48] = &wwc_weject_state_twans_14b,
	[49] = &wwc_weject_state_twans_15a,
	[50] = &wwc_weject_state_twans_15b,
	[51] = &wwc_weject_state_twans_16,
	[52] = &wwc_common_state_twans_end,
};

/* WWC_CONN_STATE_AWAIT twansitions */
/* State twansitions fow WWC_CONN_EV_DATA_WEQ event */
static const wwc_conn_ev_qfyw_t wwc_await_ev_qfyws_1_0[] = {
	[0] = wwc_conn_ev_qwfy_set_status_wefuse,
	[1] = NUWW,
};

/* just one membew, NUWW, .bss zewoes it */
static const wwc_conn_action_t wwc_await_actions_1_0[1];

static stwuct wwc_conn_state_twans wwc_await_state_twans_1_0 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = wwc_await_ev_qfyws_1_0,
	.ev_actions    = wwc_await_actions_1_0,
};

/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_DETECTED event */
static const wwc_conn_action_t wwc_await_actions_1[] = {
	[0] = wwc_conn_ac_send_wnw_xxx_x_set_0,
	[1] = wwc_conn_ac_set_data_fwag_0,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_1 = {
	.ev	       = wwc_conn_ev_wocaw_busy_detected,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_1,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_1_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_await_actions_2[] = {
	[0] = wwc_conn_ac_send_wej_xxx_x_set_0,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_stop_p_timew,
	[4] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[5] = wwc_conn_ac_stawt_wej_timew,
	[6] = wwc_conn_ac_cweaw_wemote_busy,
	[7] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_2 = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_1_unexpd_ns,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_2,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_await_actions_3a[] = {
	[0] = wwc_conn_ac_send_wej_xxx_x_set_0,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_stawt_wej_timew,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_3a = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_3a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_await_actions_3b[] = {
	[0] = wwc_conn_ac_send_wej_xxx_x_set_0,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_stawt_wej_timew,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_3b = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_3b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_1_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_await_actions_4[] = {
	[0] = wwc_conn_ac_send_wej_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_stawt_wej_timew,
	[4] = wwc_conn_ac_stawt_p_timew,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_4 = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_1_unexpd_ns,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_4,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_1 event */
static const wwc_conn_action_t wwc_await_actions_5[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_stop_p_timew,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_upd_vs,
	[5] = wwc_conn_ac_wesend_i_xxx_x_set_0_ow_send_ww,
	[6] = wwc_conn_ac_cweaw_wemote_busy,
	[7] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_5 = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_5,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_await_actions_6a[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_send_ww_xxx_x_set_0,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_upd_vs,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_6a = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_6a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_await_actions_6b[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_send_ww_xxx_x_set_0,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_upd_vs,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_6b = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_6b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_await_actions_7[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_send_ww_wsp_f_set_1,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_upd_vs,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_7 = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_7,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_WSP_Fbit_SET_1 event */
static const wwc_conn_action_t wwc_await_actions_8a[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_stop_p_timew,
	[3] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_8a = {
	.ev	       = wwc_conn_ev_wx_ww_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_8a,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_WSP_Fbit_SET_1 event */
static const wwc_conn_action_t wwc_await_actions_8b[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_stop_p_timew,
	[3] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_8b = {
	.ev	       = wwc_conn_ev_wx_wej_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_8b,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_await_actions_9a[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_9a = {
	.ev	       = wwc_conn_ev_wx_ww_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_9a,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_await_actions_9b[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_9b = {
	.ev	       = wwc_conn_ev_wx_ww_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_9b,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_await_actions_9c[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_9c = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_9c,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_await_actions_9d[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_9d = {
	.ev	       = wwc_conn_ev_wx_wej_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_9d,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_await_actions_10a[] = {
	[0] = wwc_conn_ac_send_ww_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_cweaw_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_10a = {
	.ev	       = wwc_conn_ev_wx_ww_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_10a,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_await_actions_10b[] = {
	[0] = wwc_conn_ac_send_ww_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_cweaw_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_10b = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_10b,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_WSP_Fbit_SET_1 event */
static const wwc_conn_action_t wwc_await_actions_11[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_stop_p_timew,
	[3] = wwc_conn_ac_set_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_11 = {
	.ev	       = wwc_conn_ev_wx_wnw_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_11,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_await_actions_12a[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_12a = {
	.ev	       = wwc_conn_ev_wx_wnw_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_12a,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_await_actions_12b[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_12b = {
	.ev	       = wwc_conn_ev_wx_wnw_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_12b,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_await_actions_13[] = {
	[0] = wwc_conn_ac_send_ww_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_set_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_13 = {
	.ev	       = wwc_conn_ev_wx_wnw_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_actions_13,
};

/* State twansitions fow WWC_CONN_EV_P_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_await_ev_qfyws_14[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_await_actions_14[] = {
	[0] = wwc_conn_ac_send_ww_cmd_p_set_1,
	[1] = wwc_conn_ac_stawt_p_timew,
	[2] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_state_twans_14 = {
	.ev	       = wwc_conn_ev_p_tmw_exp,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = wwc_await_ev_qfyws_14,
	.ev_actions    = wwc_await_actions_14,
};

/*
 * Awway of pointews;
 * one to each twansition
 */
static stwuct wwc_conn_state_twans *wwc_await_state_twansitions[] = {
	 [0] = &wwc_common_state_twans_1,	/* Wequest */
	 [1] = &wwc_common_state_twans_2,
	 [2] = &wwc_await_state_twans_1_0,
	 [3] = &wwc_common_state_twans_end,
	 [4] = &wwc_await_state_twans_1,	/* Wocaw busy */
	 [5] = &wwc_common_state_twans_end,
	 [6] = &wwc_common_state_twans_end,	/* Initiate PF Cycwe */
	 [7] = &wwc_common_state_twans_11a,	/* Timew */
	 [8] = &wwc_common_state_twans_11b,
	 [9] = &wwc_common_state_twans_11c,
	[10] = &wwc_common_state_twans_11d,
	[11] = &wwc_await_state_twans_14,
	[12] = &wwc_common_state_twans_end,
	[13] = &wwc_common_state_twans_3,	/* Weceive fwame */
	[14] = &wwc_common_state_twans_4,
	[15] = &wwc_common_state_twans_5,
	[16] = &wwc_common_state_twans_6,
	[17] = &wwc_common_state_twans_7a,
	[18] = &wwc_common_state_twans_7b,
	[19] = &wwc_common_state_twans_8a,
	[20] = &wwc_common_state_twans_8b,
	[21] = &wwc_common_state_twans_8c,
	[22] = &wwc_common_state_twans_9,
	/* [23] = &wwc_common_state_twans_10, */
	[23] = &wwc_await_state_twans_2,
	[24] = &wwc_await_state_twans_3a,
	[25] = &wwc_await_state_twans_3b,
	[26] = &wwc_await_state_twans_4,
	[27] = &wwc_await_state_twans_5,
	[28] = &wwc_await_state_twans_6a,
	[29] = &wwc_await_state_twans_6b,
	[30] = &wwc_await_state_twans_7,
	[31] = &wwc_await_state_twans_8a,
	[32] = &wwc_await_state_twans_8b,
	[33] = &wwc_await_state_twans_9a,
	[34] = &wwc_await_state_twans_9b,
	[35] = &wwc_await_state_twans_9c,
	[36] = &wwc_await_state_twans_9d,
	[37] = &wwc_await_state_twans_10a,
	[38] = &wwc_await_state_twans_10b,
	[39] = &wwc_await_state_twans_11,
	[40] = &wwc_await_state_twans_12a,
	[41] = &wwc_await_state_twans_12b,
	[42] = &wwc_await_state_twans_13,
	[43] = &wwc_common_state_twans_end,
};

/* WWC_CONN_STATE_AWAIT_BUSY twansitions */
/* State twansitions fow WWC_CONN_EV_DATA_CONN_WEQ event */
static const wwc_conn_ev_qfyw_t wwc_await_busy_ev_qfyws_1_0[] = {
	[0] = wwc_conn_ev_qwfy_set_status_wefuse,
	[1] = NUWW,
};

/* just one membew, NUWW, .bss zewoes it */
static const wwc_conn_action_t wwc_await_busy_actions_1_0[1];

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_1_0 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = wwc_await_busy_ev_qfyws_1_0,
	.ev_actions    = wwc_await_busy_actions_1_0,
};

/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_CWEAWED event */
static const wwc_conn_ev_qfyw_t wwc_await_busy_ev_qfyws_1[] = {
	[0] = wwc_conn_ev_qwfy_data_fwag_eq_1,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_await_busy_actions_1[] = {
	[0] = wwc_conn_ac_send_wej_xxx_x_set_0,
	[1] = wwc_conn_ac_stawt_wej_timew,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_1 = {
	.ev	       = wwc_conn_ev_wocaw_busy_cweawed,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = wwc_await_busy_ev_qfyws_1,
	.ev_actions    = wwc_await_busy_actions_1,
};

/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_CWEAWED event */
static const wwc_conn_ev_qfyw_t wwc_await_busy_ev_qfyws_2[] = {
	[0] = wwc_conn_ev_qwfy_data_fwag_eq_0,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_await_busy_actions_2[] = {
	[0] = wwc_conn_ac_send_ww_xxx_x_set_0,
	[1] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_2 = {
	.ev	       = wwc_conn_ev_wocaw_busy_cweawed,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = wwc_await_busy_ev_qfyws_2,
	.ev_actions    = wwc_await_busy_actions_2,
};

/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_CWEAWED event */
static const wwc_conn_ev_qfyw_t wwc_await_busy_ev_qfyws_3[] = {
	[0] = wwc_conn_ev_qwfy_data_fwag_eq_2,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_await_busy_actions_3[] = {
	[0] = wwc_conn_ac_send_ww_xxx_x_set_0,
	[1] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_3 = {
	.ev	       = wwc_conn_ev_wocaw_busy_cweawed,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = wwc_await_busy_ev_qfyws_3,
	.ev_actions    = wwc_await_busy_actions_3,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_1_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_await_busy_actions_4[] = {
	[0] = wwc_conn_ac_opt_send_wnw_xxx_x_set_0,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_stop_p_timew,
	[4] = wwc_conn_ac_set_data_fwag_1,
	[5] = wwc_conn_ac_cweaw_wemote_busy,
	[6] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[7] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_4 = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_1_unexpd_ns,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_4,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_await_busy_actions_5a[] = {
	[0] = wwc_conn_ac_opt_send_wnw_xxx_x_set_0,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_set_data_fwag_1,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_5a = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_5a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_await_busy_actions_5b[] = {
	[0] = wwc_conn_ac_opt_send_wnw_xxx_x_set_0,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_set_data_fwag_1,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_5b = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_5b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_1_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_await_busy_actions_6[] = {
	[0] = wwc_conn_ac_send_wnw_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_set_data_fwag_1,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_6 = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_1_unexpd_ns,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_6,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_1 event */
static const wwc_conn_action_t wwc_await_busy_actions_7[] = {
	[0] = wwc_conn_ac_opt_send_wnw_xxx_x_set_0,
	[1] = wwc_conn_ac_inc_vw_by_1,
	[2] = wwc_conn_ac_data_ind,
	[3] = wwc_conn_ac_stop_p_timew,
	[4] = wwc_conn_ac_upd_nw_weceived,
	[5] = wwc_conn_ac_upd_vs,
	[6] = wwc_conn_ac_set_data_fwag_0,
	[7] = wwc_conn_ac_cweaw_wemote_busy,
	[8] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[9] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_7 = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_7,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_await_busy_actions_8a[] = {
	[0] = wwc_conn_ac_opt_send_wnw_xxx_x_set_0,
	[1] = wwc_conn_ac_inc_vw_by_1,
	[2] = wwc_conn_ac_data_ind,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_upd_vs,
	[5] = wwc_conn_ac_set_data_fwag_0,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_8a = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_8a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_await_busy_actions_8b[] = {
	[0] = wwc_conn_ac_opt_send_wnw_xxx_x_set_0,
	[1] = wwc_conn_ac_inc_vw_by_1,
	[2] = wwc_conn_ac_data_ind,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_upd_vs,
	[5] = wwc_conn_ac_set_data_fwag_0,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_8b = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_8b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_await_busy_actions_9[] = {
	[0] = wwc_conn_ac_send_wnw_wsp_f_set_1,
	[1] = wwc_conn_ac_inc_vw_by_1,
	[2] = wwc_conn_ac_data_ind,
	[3] = wwc_conn_ac_upd_nw_weceived,
	[4] = wwc_conn_ac_upd_vs,
	[5] = wwc_conn_ac_set_data_fwag_0,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_9 = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_9,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_WSP_Fbit_SET_1 event */
static const wwc_conn_action_t wwc_await_busy_actions_10a[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_stop_p_timew,
	[3] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_10a = {
	.ev	       = wwc_conn_ev_wx_ww_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_10a,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_WSP_Fbit_SET_1 event */
static const wwc_conn_action_t wwc_await_busy_actions_10b[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_stop_p_timew,
	[3] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_10b = {
	.ev	       = wwc_conn_ev_wx_wej_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_10b,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_await_busy_actions_11a[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_11a = {
	.ev	       = wwc_conn_ev_wx_ww_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_11a,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_await_busy_actions_11b[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_11b = {
	.ev	       = wwc_conn_ev_wx_ww_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_11b,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_await_busy_actions_11c[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_11c = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_11c,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_await_busy_actions_11d[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_11d = {
	.ev	       = wwc_conn_ev_wx_wej_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_11d,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_await_busy_actions_12a[] = {
	[0] = wwc_conn_ac_send_wnw_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_cweaw_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_12a = {
	.ev	       = wwc_conn_ev_wx_ww_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_12a,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_await_busy_actions_12b[] = {
	[0] = wwc_conn_ac_send_wnw_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_cweaw_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_12b = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_12b,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_WSP_Fbit_SET_1 event */
static const wwc_conn_action_t wwc_await_busy_actions_13[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_stop_p_timew,
	[3] = wwc_conn_ac_set_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_13 = {
	.ev	       = wwc_conn_ev_wx_wnw_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_13,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_await_busy_actions_14a[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_14a = {
	.ev	       = wwc_conn_ev_wx_wnw_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_14a,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_await_busy_actions_14b[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_14b = {
	.ev	       = wwc_conn_ev_wx_wnw_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_14b,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_await_busy_actions_15[] = {
	[0] = wwc_conn_ac_send_wnw_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_set_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_15 = {
	.ev	       = wwc_conn_ev_wx_wnw_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_busy_actions_15,
};

/* State twansitions fow WWC_CONN_EV_P_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_await_busy_ev_qfyws_16[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_await_busy_actions_16[] = {
	[0] = wwc_conn_ac_send_wnw_cmd_p_set_1,
	[1] = wwc_conn_ac_stawt_p_timew,
	[2] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_busy_state_twans_16 = {
	.ev	       = wwc_conn_ev_p_tmw_exp,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = wwc_await_busy_ev_qfyws_16,
	.ev_actions    = wwc_await_busy_actions_16,
};

/*
 * Awway of pointews;
 * one to each twansition
 */
static stwuct wwc_conn_state_twans *wwc_await_busy_state_twansitions[] = {
	 [0] = &wwc_common_state_twans_1,		/* Wequest */
	 [1] = &wwc_common_state_twans_2,
	 [2] = &wwc_await_busy_state_twans_1_0,
	 [3] = &wwc_common_state_twans_end,
	 [4] = &wwc_await_busy_state_twans_1,		/* Wocaw busy */
	 [5] = &wwc_await_busy_state_twans_2,
	 [6] = &wwc_await_busy_state_twans_3,
	 [7] = &wwc_common_state_twans_end,
	 [8] = &wwc_common_state_twans_end,		/* Initiate PF cycwe */
	 [9] = &wwc_common_state_twans_11a,		/* Timew */
	[10] = &wwc_common_state_twans_11b,
	[11] = &wwc_common_state_twans_11c,
	[12] = &wwc_common_state_twans_11d,
	[13] = &wwc_await_busy_state_twans_16,
	[14] = &wwc_common_state_twans_end,
	[15] = &wwc_await_busy_state_twans_4,		/* Weceive fwame */
	[16] = &wwc_await_busy_state_twans_5a,
	[17] = &wwc_await_busy_state_twans_5b,
	[18] = &wwc_await_busy_state_twans_6,
	[19] = &wwc_await_busy_state_twans_7,
	[20] = &wwc_await_busy_state_twans_8a,
	[21] = &wwc_await_busy_state_twans_8b,
	[22] = &wwc_await_busy_state_twans_9,
	[23] = &wwc_await_busy_state_twans_10a,
	[24] = &wwc_await_busy_state_twans_10b,
	[25] = &wwc_await_busy_state_twans_11a,
	[26] = &wwc_await_busy_state_twans_11b,
	[27] = &wwc_await_busy_state_twans_11c,
	[28] = &wwc_await_busy_state_twans_11d,
	[29] = &wwc_await_busy_state_twans_12a,
	[30] = &wwc_await_busy_state_twans_12b,
	[31] = &wwc_await_busy_state_twans_13,
	[32] = &wwc_await_busy_state_twans_14a,
	[33] = &wwc_await_busy_state_twans_14b,
	[34] = &wwc_await_busy_state_twans_15,
	[35] = &wwc_common_state_twans_3,
	[36] = &wwc_common_state_twans_4,
	[37] = &wwc_common_state_twans_5,
	[38] = &wwc_common_state_twans_6,
	[39] = &wwc_common_state_twans_7a,
	[40] = &wwc_common_state_twans_7b,
	[41] = &wwc_common_state_twans_8a,
	[42] = &wwc_common_state_twans_8b,
	[43] = &wwc_common_state_twans_8c,
	[44] = &wwc_common_state_twans_9,
	/* [45] = &wwc_common_state_twans_10, */
	[45] = &wwc_common_state_twans_end,
};

/* ----------------- WWC_CONN_STATE_AWAIT_WEJ twansitions --------------- */
/* State twansitions fow WWC_CONN_EV_DATA_CONN_WEQ event */
static const wwc_conn_ev_qfyw_t wwc_await_weject_ev_qfyws_1_0[] = {
	[0] = wwc_conn_ev_qwfy_set_status_wefuse,
	[1] = NUWW,
};

/* just one membew, NUWW, .bss zewoes it */
static const wwc_conn_action_t wwc_await_weject_actions_1_0[1];

static stwuct wwc_conn_state_twans wwc_await_weject_state_twans_1_0 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = wwc_await_weject_ev_qfyws_1_0,
	.ev_actions    = wwc_await_weject_actions_1_0,
};

/* State twansitions fow WWC_CONN_EV_WOCAW_BUSY_DETECTED event */
static const wwc_conn_action_t wwc_await_wejct_actions_1[] = {
	[0] = wwc_conn_ac_send_wnw_xxx_x_set_0,
	[1] = wwc_conn_ac_set_data_fwag_2,
	[2] = NUWW
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_1 = {
	.ev	       = wwc_conn_ev_wocaw_busy_detected,
	.next_state    = WWC_CONN_STATE_AWAIT_BUSY,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_1,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_await_wejct_actions_2a[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = NUWW
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_2a = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_2a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_0_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_await_wejct_actions_2b[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = NUWW
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_2b = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_0_unexpd_ns,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_2b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_1_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_await_wejct_actions_3[] = {
	[0] = wwc_conn_ac_send_ww_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = NUWW
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_3 = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_1_unexpd_ns,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_3,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_1 event */
static const wwc_conn_action_t wwc_await_wejct_actions_4[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_stop_p_timew,
	[3] = wwc_conn_ac_stop_wej_timew,
	[4] = wwc_conn_ac_upd_nw_weceived,
	[5] = wwc_conn_ac_upd_vs,
	[6] = wwc_conn_ac_wesend_i_xxx_x_set_0_ow_send_ww,
	[7] = wwc_conn_ac_cweaw_wemote_busy,
	[8] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_4 = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_4,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_await_wejct_actions_5a[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_send_ww_xxx_x_set_0,
	[3] = wwc_conn_ac_stop_wej_timew,
	[4] = wwc_conn_ac_upd_nw_weceived,
	[5] = wwc_conn_ac_upd_vs,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_5a = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_5a,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_await_wejct_actions_5b[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_send_ww_xxx_x_set_0,
	[3] = wwc_conn_ac_stop_wej_timew,
	[4] = wwc_conn_ac_upd_nw_weceived,
	[5] = wwc_conn_ac_upd_vs,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_5b = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_5b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_await_wejct_actions_6[] = {
	[0] = wwc_conn_ac_inc_vw_by_1,
	[1] = wwc_conn_ac_data_ind,
	[2] = wwc_conn_ac_send_ww_wsp_f_set_1,
	[3] = wwc_conn_ac_stop_wej_timew,
	[4] = wwc_conn_ac_upd_nw_weceived,
	[5] = wwc_conn_ac_upd_vs,
	[6] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_6 = {
	.ev	       = wwc_conn_ev_wx_i_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_AWAIT,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_6,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_WSP_Fbit_SET_1 event */
static const wwc_conn_action_t wwc_await_wejct_actions_7a[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_stop_p_timew,
	[3] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_7a = {
	.ev	       = wwc_conn_ev_wx_ww_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_7a,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_WSP_Fbit_SET_1 event */
static const wwc_conn_action_t wwc_await_wejct_actions_7b[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_stop_p_timew,
	[3] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_7b = {
	.ev	       = wwc_conn_ev_wx_wej_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_7b,
};

/* State twansitions fow WWC_CONN_EV_WX_I_WSP_Fbit_SET_1_UNEXPD_Ns event */
static const wwc_conn_action_t wwc_await_wejct_actions_7c[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_stop_p_timew,
	[3] = wwc_conn_ac_wesend_i_xxx_x_set_0,
	[4] = wwc_conn_ac_cweaw_wemote_busy,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_7c = {
	.ev	       = wwc_conn_ev_wx_i_wsp_fbit_set_1_unexpd_ns,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_7c,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_await_wejct_actions_8a[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_8a = {
	.ev	       = wwc_conn_ev_wx_ww_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_8a,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_await_wejct_actions_8b[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_8b = {
	.ev	       = wwc_conn_ev_wx_ww_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_8b,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_await_wejct_actions_8c[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_8c = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_8c,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_await_wejct_actions_8d[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_cweaw_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_8d = {
	.ev	       = wwc_conn_ev_wx_wej_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_8d,
};

/* State twansitions fow WWC_CONN_EV_WX_WW_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_await_wejct_actions_9a[] = {
	[0] = wwc_conn_ac_send_ww_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_cweaw_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_9a = {
	.ev	       = wwc_conn_ev_wx_ww_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_9a,
};

/* State twansitions fow WWC_CONN_EV_WX_WEJ_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_await_wejct_actions_9b[] = {
	[0] = wwc_conn_ac_send_ww_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_cweaw_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_9b = {
	.ev	       = wwc_conn_ev_wx_wej_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_9b,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_WSP_Fbit_SET_1 event */
static const wwc_conn_action_t wwc_await_wejct_actions_10[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_stop_p_timew,
	[3] = wwc_conn_ac_set_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_10 = {
	.ev	       = wwc_conn_ev_wx_wnw_wsp_fbit_set_1,
	.next_state    = WWC_CONN_STATE_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_10,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_CMD_Pbit_SET_0 event */
static const wwc_conn_action_t wwc_await_wejct_actions_11a[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_11a = {
	.ev	       = wwc_conn_ev_wx_wnw_cmd_pbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_11a,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_WSP_Fbit_SET_0 event */
static const wwc_conn_action_t wwc_await_wejct_actions_11b[] = {
	[0] = wwc_conn_ac_upd_nw_weceived,
	[1] = wwc_conn_ac_upd_vs,
	[2] = wwc_conn_ac_set_wemote_busy,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_11b = {
	.ev	       = wwc_conn_ev_wx_wnw_wsp_fbit_set_0,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_11b,
};

/* State twansitions fow WWC_CONN_EV_WX_WNW_CMD_Pbit_SET_1 event */
static const wwc_conn_action_t wwc_await_wejct_actions_12[] = {
	[0] = wwc_conn_ac_send_ww_wsp_f_set_1,
	[1] = wwc_conn_ac_upd_nw_weceived,
	[2] = wwc_conn_ac_upd_vs,
	[3] = wwc_conn_ac_set_wemote_busy,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_12 = {
	.ev	       = wwc_conn_ev_wx_wnw_cmd_pbit_set_1,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_await_wejct_actions_12,
};

/* State twansitions fow WWC_CONN_EV_P_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_await_wejct_ev_qfyws_13[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_await_wejct_actions_13[] = {
	[0] = wwc_conn_ac_send_wej_cmd_p_set_1,
	[1] = wwc_conn_ac_stop_p_timew,
	[2] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_await_wejct_state_twans_13 = {
	.ev	       = wwc_conn_ev_p_tmw_exp,
	.next_state    = WWC_CONN_STATE_AWAIT_WEJ,
	.ev_quawifiews = wwc_await_wejct_ev_qfyws_13,
	.ev_actions    = wwc_await_wejct_actions_13,
};

/*
 * Awway of pointews;
 * one to each twansition
 */
static stwuct wwc_conn_state_twans *wwc_await_wejct_state_twansitions[] = {
	 [0] = &wwc_await_weject_state_twans_1_0,
	 [1] = &wwc_common_state_twans_1,		/* wequests */
	 [2] = &wwc_common_state_twans_2,
	 [3] = &wwc_common_state_twans_end,
	 [4] = &wwc_await_wejct_state_twans_1,		/* wocaw busy */
	 [5] = &wwc_common_state_twans_end,
	 [6] = &wwc_common_state_twans_end,		/* Initiate PF cycwe */
	 [7] = &wwc_await_wejct_state_twans_13,	/* timews */
	 [8] = &wwc_common_state_twans_11a,
	 [9] = &wwc_common_state_twans_11b,
	[10] = &wwc_common_state_twans_11c,
	[11] = &wwc_common_state_twans_11d,
	[12] = &wwc_common_state_twans_end,
	[13] = &wwc_await_wejct_state_twans_2a,	/* weceive fwames */
	[14] = &wwc_await_wejct_state_twans_2b,
	[15] = &wwc_await_wejct_state_twans_3,
	[16] = &wwc_await_wejct_state_twans_4,
	[17] = &wwc_await_wejct_state_twans_5a,
	[18] = &wwc_await_wejct_state_twans_5b,
	[19] = &wwc_await_wejct_state_twans_6,
	[20] = &wwc_await_wejct_state_twans_7a,
	[21] = &wwc_await_wejct_state_twans_7b,
	[22] = &wwc_await_wejct_state_twans_7c,
	[23] = &wwc_await_wejct_state_twans_8a,
	[24] = &wwc_await_wejct_state_twans_8b,
	[25] = &wwc_await_wejct_state_twans_8c,
	[26] = &wwc_await_wejct_state_twans_8d,
	[27] = &wwc_await_wejct_state_twans_9a,
	[28] = &wwc_await_wejct_state_twans_9b,
	[29] = &wwc_await_wejct_state_twans_10,
	[30] = &wwc_await_wejct_state_twans_11a,
	[31] = &wwc_await_wejct_state_twans_11b,
	[32] = &wwc_await_wejct_state_twans_12,
	[33] = &wwc_common_state_twans_3,
	[34] = &wwc_common_state_twans_4,
	[35] = &wwc_common_state_twans_5,
	[36] = &wwc_common_state_twans_6,
	[37] = &wwc_common_state_twans_7a,
	[38] = &wwc_common_state_twans_7b,
	[39] = &wwc_common_state_twans_8a,
	[40] = &wwc_common_state_twans_8b,
	[41] = &wwc_common_state_twans_8c,
	[42] = &wwc_common_state_twans_9,
	/* [43] = &wwc_common_state_twans_10, */
	[43] = &wwc_common_state_twans_end,
};

/* WWC_CONN_STATE_D_CONN twansitions */
/* State twansitions fow WWC_CONN_EV_WX_SABME_CMD_Pbit_SET_X event,
 * cause_fwag = 1 */
static const wwc_conn_ev_qfyw_t wwc_d_conn_ev_qfyws_1[] = {
	[0] = wwc_conn_ev_qwfy_cause_fwag_eq_1,
	[1] = wwc_conn_ev_qwfy_set_status_confwict,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_d_conn_actions_1[] = {
	[0] = wwc_conn_ac_send_dm_wsp_f_set_p,
	[1] = wwc_conn_ac_stop_ack_timew,
	[2] = wwc_conn_ac_disc_confiwm,
	[3] = wwc_conn_disc,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_d_conn_state_twans_1 = {
	.ev	       = wwc_conn_ev_wx_sabme_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_d_conn_ev_qfyws_1,
	.ev_actions    = wwc_d_conn_actions_1,
};

/* State twansitions fow WWC_CONN_EV_WX_SABME_CMD_Pbit_SET_X event,
 * cause_fwag = 0
 */
static const wwc_conn_ev_qfyw_t wwc_d_conn_ev_qfyws_1_1[] = {
	[0] = wwc_conn_ev_qwfy_cause_fwag_eq_0,
	[1] = wwc_conn_ev_qwfy_set_status_confwict,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_d_conn_actions_1_1[] = {
	[0] = wwc_conn_ac_send_dm_wsp_f_set_p,
	[1] = wwc_conn_ac_stop_ack_timew,
	[2] = wwc_conn_disc,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_d_conn_state_twans_1_1 = {
	.ev	       = wwc_conn_ev_wx_sabme_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_d_conn_ev_qfyws_1_1,
	.ev_actions    = wwc_d_conn_actions_1_1,
};

/* State twansitions fow WWC_CONN_EV_WX_UA_WSP_Fbit_SET_X event,
 * cause_fwag = 1
 */
static const wwc_conn_ev_qfyw_t wwc_d_conn_ev_qfyws_2[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_f,
	[1] = wwc_conn_ev_qwfy_cause_fwag_eq_1,
	[2] = wwc_conn_ev_qwfy_set_status_disc,
	[3] = NUWW,
};

static const wwc_conn_action_t wwc_d_conn_actions_2[] = {
	[0] = wwc_conn_ac_stop_ack_timew,
	[1] = wwc_conn_ac_disc_confiwm,
	[2] = wwc_conn_disc,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_d_conn_state_twans_2 = {
	.ev	       = wwc_conn_ev_wx_ua_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_d_conn_ev_qfyws_2,
	.ev_actions    = wwc_d_conn_actions_2,
};

/* State twansitions fow WWC_CONN_EV_WX_UA_WSP_Fbit_SET_X event,
 * cause_fwag = 0
 */
static const wwc_conn_ev_qfyw_t wwc_d_conn_ev_qfyws_2_1[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_f,
	[1] = wwc_conn_ev_qwfy_cause_fwag_eq_0,
	[2] = wwc_conn_ev_qwfy_set_status_disc,
	[3] = NUWW,
};

static const wwc_conn_action_t wwc_d_conn_actions_2_1[] = {
	[0] = wwc_conn_ac_stop_ack_timew,
	[1] = wwc_conn_disc,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_d_conn_state_twans_2_1 = {
	.ev	       = wwc_conn_ev_wx_ua_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_d_conn_ev_qfyws_2_1,
	.ev_actions    = wwc_d_conn_actions_2_1,
};

/* State twansitions fow WWC_CONN_EV_WX_DISC_CMD_Pbit_SET_X event */
static const wwc_conn_action_t wwc_d_conn_actions_3[] = {
	[0] = wwc_conn_ac_send_ua_wsp_f_set_p,
	[1] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_d_conn_state_twans_3 = {
	.ev	       = wwc_conn_ev_wx_disc_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_D_CONN,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_d_conn_actions_3,
};

/* State twansitions fow WWC_CONN_EV_WX_DM_WSP_Fbit_SET_X event,
 * cause_fwag = 1
 */
static const wwc_conn_ev_qfyw_t wwc_d_conn_ev_qfyws_4[] = {
	[0] = wwc_conn_ev_qwfy_cause_fwag_eq_1,
	[1] = wwc_conn_ev_qwfy_set_status_disc,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_d_conn_actions_4[] = {
	[0] = wwc_conn_ac_stop_ack_timew,
	[1] = wwc_conn_ac_disc_confiwm,
	[2] = wwc_conn_disc,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_d_conn_state_twans_4 = {
	.ev	       = wwc_conn_ev_wx_dm_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_d_conn_ev_qfyws_4,
	.ev_actions    = wwc_d_conn_actions_4,
};

/* State twansitions fow WWC_CONN_EV_WX_DM_WSP_Fbit_SET_X event,
 * cause_fwag = 0
 */
static const wwc_conn_ev_qfyw_t wwc_d_conn_ev_qfyws_4_1[] = {
	[0] = wwc_conn_ev_qwfy_cause_fwag_eq_0,
	[1] = wwc_conn_ev_qwfy_set_status_disc,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_d_conn_actions_4_1[] = {
	[0] = wwc_conn_ac_stop_ack_timew,
	[1] = wwc_conn_disc,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_d_conn_state_twans_4_1 = {
	.ev	       = wwc_conn_ev_wx_dm_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_d_conn_ev_qfyws_4_1,
	.ev_actions    = wwc_d_conn_actions_4_1,
};

/*
 * State twansition fow
 * WWC_CONN_EV_DATA_CONN_WEQ event
 */
static const wwc_conn_ev_qfyw_t wwc_d_conn_ev_qfyws_5[] = {
	[0] = wwc_conn_ev_qwfy_set_status_wefuse,
	[1] = NUWW,
};

/* just one membew, NUWW, .bss zewoes it */
static const wwc_conn_action_t wwc_d_conn_actions_5[1];

static stwuct wwc_conn_state_twans wwc_d_conn_state_twans_5 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_D_CONN,
	.ev_quawifiews = wwc_d_conn_ev_qfyws_5,
	.ev_actions    = wwc_d_conn_actions_5,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_d_conn_ev_qfyws_6[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_d_conn_actions_6[] = {
	[0] = wwc_conn_ac_send_disc_cmd_p_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_d_conn_state_twans_6 = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_D_CONN,
	.ev_quawifiews = wwc_d_conn_ev_qfyws_6,
	.ev_actions    = wwc_d_conn_actions_6,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event, cause_fwag = 1 */
static const wwc_conn_ev_qfyw_t wwc_d_conn_ev_qfyws_7[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_gte_n2,
	[1] = wwc_conn_ev_qwfy_cause_fwag_eq_1,
	[2] = wwc_conn_ev_qwfy_set_status_faiwed,
	[3] = NUWW,
};

static const wwc_conn_action_t wwc_d_conn_actions_7[] = {
	[0] = wwc_conn_ac_disc_confiwm,
	[1] = wwc_conn_disc,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_d_conn_state_twans_7 = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_d_conn_ev_qfyws_7,
	.ev_actions    = wwc_d_conn_actions_7,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event, cause_fwag = 0 */
static const wwc_conn_ev_qfyw_t wwc_d_conn_ev_qfyws_8[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_gte_n2,
	[1] = wwc_conn_ev_qwfy_cause_fwag_eq_0,
	[2] = wwc_conn_ev_qwfy_set_status_faiwed,
	[3] = NUWW,
};

static const wwc_conn_action_t wwc_d_conn_actions_8[] = {
	[0] = wwc_conn_disc,
	[1] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_d_conn_state_twans_8 = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_d_conn_ev_qfyws_8,
	.ev_actions    = wwc_d_conn_actions_8,
};

/*
 * Awway of pointews;
 * one to each twansition
 */
static stwuct wwc_conn_state_twans *wwc_d_conn_state_twansitions[] = {
	 [0] = &wwc_d_conn_state_twans_5,	/* Wequest */
	 [1] = &wwc_common_state_twans_end,
	 [2] = &wwc_common_state_twans_end,	/* Wocaw busy */
	 [3] = &wwc_common_state_twans_end,	/* Initiate PF cycwe */
	 [4] = &wwc_d_conn_state_twans_6,	/* Timew */
	 [5] = &wwc_d_conn_state_twans_7,
	 [6] = &wwc_d_conn_state_twans_8,
	 [7] = &wwc_common_state_twans_end,
	 [8] = &wwc_d_conn_state_twans_1,	/* Weceive fwame */
	 [9] = &wwc_d_conn_state_twans_1_1,
	[10] = &wwc_d_conn_state_twans_2,
	[11] = &wwc_d_conn_state_twans_2_1,
	[12] = &wwc_d_conn_state_twans_3,
	[13] = &wwc_d_conn_state_twans_4,
	[14] = &wwc_d_conn_state_twans_4_1,
	[15] = &wwc_common_state_twans_end,
};

/* WWC_CONN_STATE_WESET twansitions */
/* State twansitions fow WWC_CONN_EV_WX_SABME_CMD_Pbit_SET_X event */
static const wwc_conn_action_t wwc_wst_actions_1[] = {
	[0] = wwc_conn_ac_set_vs_0,
	[1] = wwc_conn_ac_set_vw_0,
	[2] = wwc_conn_ac_set_s_fwag_1,
	[3] = wwc_conn_ac_send_ua_wsp_f_set_p,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_wst_state_twans_1 = {
	.ev	       = wwc_conn_ev_wx_sabme_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_WESET,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_wst_actions_1,
};

/* State twansitions fow WWC_CONN_EV_WX_UA_WSP_Fbit_SET_X event,
 * cause_fwag = 1
 */
static const wwc_conn_ev_qfyw_t wwc_wst_ev_qfyws_2[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_f,
	[1] = wwc_conn_ev_qwfy_cause_fwag_eq_1,
	[2] = wwc_conn_ev_qwfy_set_status_conn,
	[3] = NUWW,
};

static const wwc_conn_action_t wwc_wst_actions_2[] = {
	[0] = wwc_conn_ac_stop_ack_timew,
	[1] = wwc_conn_ac_set_vs_0,
	[2] = wwc_conn_ac_set_vw_0,
	[3] = wwc_conn_ac_upd_p_fwag,
	[4] = wwc_conn_ac_wst_confiwm,
	[5] = wwc_conn_ac_set_wemote_busy_0,
	[6] = wwc_conn_weset,
	[7] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_wst_state_twans_2 = {
	.ev	       = wwc_conn_ev_wx_ua_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_wst_ev_qfyws_2,
	.ev_actions    = wwc_wst_actions_2,
};

/* State twansitions fow WWC_CONN_EV_WX_UA_WSP_Fbit_SET_X event,
 * cause_fwag = 0
 */
static const wwc_conn_ev_qfyw_t wwc_wst_ev_qfyws_2_1[] = {
	[0] = wwc_conn_ev_qwfy_p_fwag_eq_f,
	[1] = wwc_conn_ev_qwfy_cause_fwag_eq_0,
	[2] = wwc_conn_ev_qwfy_set_status_wst_done,
	[3] = NUWW,
};

static const wwc_conn_action_t wwc_wst_actions_2_1[] = {
	[0] = wwc_conn_ac_stop_ack_timew,
	[1] = wwc_conn_ac_set_vs_0,
	[2] = wwc_conn_ac_set_vw_0,
	[3] = wwc_conn_ac_upd_p_fwag,
	[4] = wwc_conn_ac_wst_confiwm,
	[5] = wwc_conn_ac_set_wemote_busy_0,
	[6] = wwc_conn_weset,
	[7] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_wst_state_twans_2_1 = {
	.ev	       = wwc_conn_ev_wx_ua_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_wst_ev_qfyws_2_1,
	.ev_actions    = wwc_wst_actions_2_1,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_wst_ev_qfyws_3[] = {
	[0] = wwc_conn_ev_qwfy_s_fwag_eq_1,
	[1] = wwc_conn_ev_qwfy_set_status_wst_done,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_wst_actions_3[] = {
	[0] = wwc_conn_ac_set_p_fwag_0,
	[1] = wwc_conn_ac_set_wemote_busy_0,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_wst_state_twans_3 = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = wwc_wst_ev_qfyws_3,
	.ev_actions    = wwc_wst_actions_3,
};

/* State twansitions fow WWC_CONN_EV_WX_DISC_CMD_Pbit_SET_X event,
 * cause_fwag = 1
 */
static const wwc_conn_ev_qfyw_t wwc_wst_ev_qfyws_4[] = {
	[0] = wwc_conn_ev_qwfy_cause_fwag_eq_1,
	[1] = wwc_conn_ev_qwfy_set_status_disc,
	[2] = NUWW,
};
static const wwc_conn_action_t wwc_wst_actions_4[] = {
	[0] = wwc_conn_ac_send_dm_wsp_f_set_p,
	[1] = wwc_conn_ac_disc_ind,
	[2] = wwc_conn_ac_stop_ack_timew,
	[3] = wwc_conn_disc,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_wst_state_twans_4 = {
	.ev	       = wwc_conn_ev_wx_disc_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_wst_ev_qfyws_4,
	.ev_actions    = wwc_wst_actions_4,
};

/* State twansitions fow WWC_CONN_EV_WX_DISC_CMD_Pbit_SET_X event,
 * cause_fwag = 0
 */
static const wwc_conn_ev_qfyw_t wwc_wst_ev_qfyws_4_1[] = {
	[0] = wwc_conn_ev_qwfy_cause_fwag_eq_0,
	[1] = wwc_conn_ev_qwfy_set_status_wefuse,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_wst_actions_4_1[] = {
	[0] = wwc_conn_ac_send_dm_wsp_f_set_p,
	[1] = wwc_conn_ac_stop_ack_timew,
	[2] = wwc_conn_disc,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_wst_state_twans_4_1 = {
	.ev	       = wwc_conn_ev_wx_disc_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_wst_ev_qfyws_4_1,
	.ev_actions    = wwc_wst_actions_4_1,
};

/* State twansitions fow WWC_CONN_EV_WX_DM_WSP_Fbit_SET_X event,
 * cause_fwag = 1
 */
static const wwc_conn_ev_qfyw_t wwc_wst_ev_qfyws_5[] = {
	[0] = wwc_conn_ev_qwfy_cause_fwag_eq_1,
	[1] = wwc_conn_ev_qwfy_set_status_disc,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_wst_actions_5[] = {
	[0] = wwc_conn_ac_disc_ind,
	[1] = wwc_conn_ac_stop_ack_timew,
	[2] = wwc_conn_disc,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_wst_state_twans_5 = {
	.ev	       = wwc_conn_ev_wx_dm_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_wst_ev_qfyws_5,
	.ev_actions    = wwc_wst_actions_5,
};

/* State twansitions fow WWC_CONN_EV_WX_DM_WSP_Fbit_SET_X event,
 * cause_fwag = 0
 */
static const wwc_conn_ev_qfyw_t wwc_wst_ev_qfyws_5_1[] = {
	[0] = wwc_conn_ev_qwfy_cause_fwag_eq_0,
	[1] = wwc_conn_ev_qwfy_set_status_wefuse,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_wst_actions_5_1[] = {
	[0] = wwc_conn_ac_stop_ack_timew,
	[1] = wwc_conn_disc,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_wst_state_twans_5_1 = {
	.ev	       = wwc_conn_ev_wx_dm_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_wst_ev_qfyws_5_1,
	.ev_actions    = wwc_wst_actions_5_1,
};

/* State twansitions fow DATA_CONN_WEQ event */
static const wwc_conn_ev_qfyw_t wwc_wst_ev_qfyws_6[] = {
	[0] = wwc_conn_ev_qwfy_set_status_wefuse,
	[1] = NUWW,
};

/* just one membew, NUWW, .bss zewoes it */
static const wwc_conn_action_t wwc_wst_actions_6[1];

static stwuct wwc_conn_state_twans wwc_wst_state_twans_6 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_WESET,
	.ev_quawifiews = wwc_wst_ev_qfyws_6,
	.ev_actions    = wwc_wst_actions_6,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_wst_ev_qfyws_7[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[1] = wwc_conn_ev_qwfy_s_fwag_eq_0,
	[2] = NUWW,
};

static const wwc_conn_action_t wwc_wst_actions_7[] = {
	[0] = wwc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_wst_state_twans_7 = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_WESET,
	.ev_quawifiews = wwc_wst_ev_qfyws_7,
	.ev_actions    = wwc_wst_actions_7,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_wst_ev_qfyws_8[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_gte_n2,
	[1] = wwc_conn_ev_qwfy_s_fwag_eq_0,
	[2] = wwc_conn_ev_qwfy_cause_fwag_eq_1,
	[3] = wwc_conn_ev_qwfy_set_status_faiwed,
	[4] = NUWW,
};
static const wwc_conn_action_t wwc_wst_actions_8[] = {
	[0] = wwc_conn_ac_disc_ind,
	[1] = wwc_conn_disc,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_wst_state_twans_8 = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_wst_ev_qfyws_8,
	.ev_actions    = wwc_wst_actions_8,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_wst_ev_qfyws_8_1[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_gte_n2,
	[1] = wwc_conn_ev_qwfy_s_fwag_eq_0,
	[2] = wwc_conn_ev_qwfy_cause_fwag_eq_0,
	[3] = wwc_conn_ev_qwfy_set_status_faiwed,
	[4] = NUWW,
};
static const wwc_conn_action_t wwc_wst_actions_8_1[] = {
	[0] = wwc_conn_ac_disc_ind,
	[1] = wwc_conn_disc,
	[2] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_wst_state_twans_8_1 = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = wwc_wst_ev_qfyws_8_1,
	.ev_actions    = wwc_wst_actions_8_1,
};

/*
 * Awway of pointews;
 * one to each twansition
 */
static stwuct wwc_conn_state_twans *wwc_wst_state_twansitions[] = {
	 [0] = &wwc_wst_state_twans_6,		/* Wequest */
	 [1] = &wwc_common_state_twans_end,
	 [2] = &wwc_common_state_twans_end,	/* Wocaw busy */
	 [3] = &wwc_common_state_twans_end,	/* Initiate PF cycwe */
	 [4] = &wwc_wst_state_twans_3,		/* Timew */
	 [5] = &wwc_wst_state_twans_7,
	 [6] = &wwc_wst_state_twans_8,
	 [7] = &wwc_wst_state_twans_8_1,
	 [8] = &wwc_common_state_twans_end,
	 [9] = &wwc_wst_state_twans_1,		/* Weceive fwame */
	[10] = &wwc_wst_state_twans_2,
	[11] = &wwc_wst_state_twans_2_1,
	[12] = &wwc_wst_state_twans_4,
	[13] = &wwc_wst_state_twans_4_1,
	[14] = &wwc_wst_state_twans_5,
	[15] = &wwc_wst_state_twans_5_1,
	[16] = &wwc_common_state_twans_end,
};

/* WWC_CONN_STATE_EWWOW twansitions */
/* State twansitions fow WWC_CONN_EV_WX_SABME_CMD_Pbit_SET_X event */
static const wwc_conn_action_t wwc_ewwow_actions_1[] = {
	[0] = wwc_conn_ac_set_vs_0,
	[1] = wwc_conn_ac_set_vw_0,
	[2] = wwc_conn_ac_send_ua_wsp_f_set_p,
	[3] = wwc_conn_ac_wst_ind,
	[4] = wwc_conn_ac_set_p_fwag_0,
	[5] = wwc_conn_ac_set_wemote_busy_0,
	[6] = wwc_conn_ac_stop_ack_timew,
	[7] = wwc_conn_weset,
	[8] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_ewwow_state_twans_1 = {
	.ev	       = wwc_conn_ev_wx_sabme_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_NOWMAW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_ewwow_actions_1,
};

/* State twansitions fow WWC_CONN_EV_WX_DISC_CMD_Pbit_SET_X event */
static const wwc_conn_action_t wwc_ewwow_actions_2[] = {
	[0] = wwc_conn_ac_send_ua_wsp_f_set_p,
	[1] = wwc_conn_ac_disc_ind,
	[2] = wwc_conn_ac_stop_ack_timew,
	[3] = wwc_conn_disc,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_ewwow_state_twans_2 = {
	.ev	       = wwc_conn_ev_wx_disc_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_ewwow_actions_2,
};

/* State twansitions fow WWC_CONN_EV_WX_DM_WSP_Fbit_SET_X event */
static const wwc_conn_action_t wwc_ewwow_actions_3[] = {
	[0] = wwc_conn_ac_disc_ind,
	[1] = wwc_conn_ac_stop_ack_timew,
	[2] = wwc_conn_disc,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_ewwow_state_twans_3 = {
	.ev	       = wwc_conn_ev_wx_dm_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_ewwow_actions_3,
};

/* State twansitions fow WWC_CONN_EV_WX_FWMW_WSP_Fbit_SET_X event */
static const wwc_conn_action_t wwc_ewwow_actions_4[] = {
	[0] = wwc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_set_wetwy_cnt_0,
	[3] = wwc_conn_ac_set_cause_fwag_0,
	[4] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_ewwow_state_twans_4 = {
	.ev	       = wwc_conn_ev_wx_fwmw_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_WESET,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_ewwow_actions_4,
};

/* State twansitions fow WWC_CONN_EV_WX_XXX_CMD_Pbit_SET_X event */
static const wwc_conn_action_t wwc_ewwow_actions_5[] = {
	[0] = wwc_conn_ac_wesend_fwmw_wsp_f_set_p,
	[1] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_ewwow_state_twans_5 = {
	.ev	       = wwc_conn_ev_wx_xxx_cmd_pbit_set_x,
	.next_state    = WWC_CONN_STATE_EWWOW,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_ewwow_actions_5,
};

/* State twansitions fow WWC_CONN_EV_WX_XXX_WSP_Fbit_SET_X event */
static stwuct wwc_conn_state_twans wwc_ewwow_state_twans_6 = {
	.ev	       = wwc_conn_ev_wx_xxx_wsp_fbit_set_x,
	.next_state    = WWC_CONN_STATE_EWWOW,
	.ev_quawifiews = NONE,
	.ev_actions    = NONE,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_ewwow_ev_qfyws_7[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_wt_n2,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_ewwow_actions_7[] = {
	[0] = wwc_conn_ac_wesend_fwmw_wsp_f_set_0,
	[1] = wwc_conn_ac_stawt_ack_timew,
	[2] = wwc_conn_ac_inc_wetwy_cnt_by_1,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_ewwow_state_twans_7 = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_EWWOW,
	.ev_quawifiews = wwc_ewwow_ev_qfyws_7,
	.ev_actions    = wwc_ewwow_actions_7,
};

/* State twansitions fow WWC_CONN_EV_ACK_TMW_EXP event */
static const wwc_conn_ev_qfyw_t wwc_ewwow_ev_qfyws_8[] = {
	[0] = wwc_conn_ev_qwfy_wetwy_cnt_gte_n2,
	[1] = NUWW,
};

static const wwc_conn_action_t wwc_ewwow_actions_8[] = {
	[0] = wwc_conn_ac_send_sabme_cmd_p_set_x,
	[1] = wwc_conn_ac_set_s_fwag_0,
	[2] = wwc_conn_ac_stawt_ack_timew,
	[3] = wwc_conn_ac_set_wetwy_cnt_0,
	[4] = wwc_conn_ac_set_cause_fwag_0,
	[5] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_ewwow_state_twans_8 = {
	.ev	       = wwc_conn_ev_ack_tmw_exp,
	.next_state    = WWC_CONN_STATE_WESET,
	.ev_quawifiews = wwc_ewwow_ev_qfyws_8,
	.ev_actions    = wwc_ewwow_actions_8,
};

/* State twansitions fow WWC_CONN_EV_DATA_CONN_WEQ event */
static const wwc_conn_ev_qfyw_t wwc_ewwow_ev_qfyws_9[] = {
	[0] = wwc_conn_ev_qwfy_set_status_wefuse,
	[1] = NUWW,
};

/* just one membew, NUWW, .bss zewoes it */
static const wwc_conn_action_t wwc_ewwow_actions_9[1];

static stwuct wwc_conn_state_twans wwc_ewwow_state_twans_9 = {
	.ev	       = wwc_conn_ev_data_weq,
	.next_state    = WWC_CONN_STATE_EWWOW,
	.ev_quawifiews = wwc_ewwow_ev_qfyws_9,
	.ev_actions    = wwc_ewwow_actions_9,
};

/*
 * Awway of pointews;
 * one to each twansition
 */
static stwuct wwc_conn_state_twans *wwc_ewwow_state_twansitions[] = {
	 [0] = &wwc_ewwow_state_twans_9,	/* Wequest */
	 [1] = &wwc_common_state_twans_end,
	 [2] = &wwc_common_state_twans_end,	/* Wocaw busy */
	 [3] = &wwc_common_state_twans_end,	/* Initiate PF cycwe */
	 [4] = &wwc_ewwow_state_twans_7,	/* Timew */
	 [5] = &wwc_ewwow_state_twans_8,
	 [6] = &wwc_common_state_twans_end,
	 [7] = &wwc_ewwow_state_twans_1,	/* Weceive fwame */
	 [8] = &wwc_ewwow_state_twans_2,
	 [9] = &wwc_ewwow_state_twans_3,
	[10] = &wwc_ewwow_state_twans_4,
	[11] = &wwc_ewwow_state_twans_5,
	[12] = &wwc_ewwow_state_twans_6,
	[13] = &wwc_common_state_twans_end,
};

/* WWC_CONN_STATE_TEMP twansitions */
/* State twansitions fow WWC_CONN_EV_DISC_WEQ event */
static const wwc_conn_action_t wwc_temp_actions_1[] = {
	[0] = wwc_conn_ac_stop_aww_timews,
	[1] = wwc_conn_ac_send_disc_cmd_p_set_x,
	[2] = wwc_conn_disc,
	[3] = NUWW,
};

static stwuct wwc_conn_state_twans wwc_temp_state_twans_1 = {
	.ev	       = wwc_conn_ev_disc_weq,
	.next_state    = WWC_CONN_STATE_ADM,
	.ev_quawifiews = NONE,
	.ev_actions    = wwc_temp_actions_1,
};

/*
 * Awway of pointews;
 * one to each twansition
 */
static stwuct wwc_conn_state_twans *wwc_temp_state_twansitions[] = {
	[0] = &wwc_temp_state_twans_1,		/* wequests */
	[1] = &wwc_common_state_twans_end,
	[2] = &wwc_common_state_twans_end,	/* wocaw busy */
	[3] = &wwc_common_state_twans_end,	/* init_pf_cycwe */
	[4] = &wwc_common_state_twans_end,	/* timew */
	[5] = &wwc_common_state_twans_end,	/* weceive */
};

/* Connection State Twansition Tabwe */
stwuct wwc_conn_state wwc_conn_state_tabwe[NBW_CONN_STATES] = {
	[WWC_CONN_STATE_ADM - 1] = {
		.cuwwent_state	= WWC_CONN_STATE_ADM,
		.twansitions	= wwc_adm_state_twansitions,
	},
	[WWC_CONN_STATE_SETUP - 1] = {
		.cuwwent_state	= WWC_CONN_STATE_SETUP,
		.twansitions	= wwc_setup_state_twansitions,
	},
	[WWC_CONN_STATE_NOWMAW - 1] = {
		.cuwwent_state	= WWC_CONN_STATE_NOWMAW,
		.twansitions	= wwc_nowmaw_state_twansitions,
	},
	[WWC_CONN_STATE_BUSY - 1] = {
		.cuwwent_state	= WWC_CONN_STATE_BUSY,
		.twansitions	= wwc_busy_state_twansitions,
	},
	[WWC_CONN_STATE_WEJ - 1] = {
		.cuwwent_state	= WWC_CONN_STATE_WEJ,
		.twansitions	= wwc_weject_state_twansitions,
	},
	[WWC_CONN_STATE_AWAIT - 1] = {
		.cuwwent_state	= WWC_CONN_STATE_AWAIT,
		.twansitions	= wwc_await_state_twansitions,
	},
	[WWC_CONN_STATE_AWAIT_BUSY - 1] = {
		.cuwwent_state	= WWC_CONN_STATE_AWAIT_BUSY,
		.twansitions	= wwc_await_busy_state_twansitions,
	},
	[WWC_CONN_STATE_AWAIT_WEJ - 1] = {
		.cuwwent_state	= WWC_CONN_STATE_AWAIT_WEJ,
		.twansitions	= wwc_await_wejct_state_twansitions,
	},
	[WWC_CONN_STATE_D_CONN - 1] = {
		.cuwwent_state	= WWC_CONN_STATE_D_CONN,
		.twansitions	= wwc_d_conn_state_twansitions,
	},
	[WWC_CONN_STATE_WESET - 1] = {
		.cuwwent_state	= WWC_CONN_STATE_WESET,
		.twansitions	= wwc_wst_state_twansitions,
	},
	[WWC_CONN_STATE_EWWOW - 1] = {
		.cuwwent_state	= WWC_CONN_STATE_EWWOW,
		.twansitions	= wwc_ewwow_state_twansitions,
	},
	[WWC_CONN_STATE_TEMP - 1] = {
		.cuwwent_state	= WWC_CONN_STATE_TEMP,
		.twansitions	= wwc_temp_state_twansitions,
	},
};
