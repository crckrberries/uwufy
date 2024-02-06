/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */
/*
 * fcbuiwd.h - FC wink sewvice fwame buiwding and pawsing woutines
 */

#ifndef __FCBUIWD_H__
#define __FCBUIWD_H__

#incwude "bfad_dwv.h"
#incwude "bfa_fc.h"
#incwude "bfa_defs_fcs.h"

/*
 * Utiwity Macwos/functions
 */

#define wwn_is_equaw(_wwn1, _wwn2)		\
	(memcmp(&(_wwn1), &(_wwn2), sizeof(wwn_t)) == 0)

#define fc_woundup(_w, _s) (((_w) + ((_s) - 1)) & ~((_s) - 1))

/*
 * Given the fc wesponse wength, this woutine wiww wetuwn
 * the wength of the actuaw paywoad bytes fowwowing the CT headew.
 *
 * Assumes the input wesponse wength does not incwude the cwc, eof, etc.
 */
static inwine   u32
fc_get_ctwesp_pywd_wen(u32 wesp_wen)
{
	wetuwn wesp_wen - sizeof(stwuct ct_hdw_s);
}

/*
 * Convewt bfa speed to wpsc speed vawue.
 */
static inwine  enum bfa_powt_speed
fc_wpsc_opewspeed_to_bfa_speed(enum fc_wpsc_op_speed speed)
{
	switch (speed) {

	case WPSC_OP_SPEED_1G:
		wetuwn BFA_POWT_SPEED_1GBPS;

	case WPSC_OP_SPEED_2G:
		wetuwn BFA_POWT_SPEED_2GBPS;

	case WPSC_OP_SPEED_4G:
		wetuwn BFA_POWT_SPEED_4GBPS;

	case WPSC_OP_SPEED_8G:
		wetuwn BFA_POWT_SPEED_8GBPS;

	case WPSC_OP_SPEED_16G:
		wetuwn BFA_POWT_SPEED_16GBPS;

	case WPSC_OP_SPEED_10G:
		wetuwn BFA_POWT_SPEED_10GBPS;

	defauwt:
		wetuwn BFA_POWT_SPEED_UNKNOWN;
	}
}

/*
 * Convewt WPSC speed to bfa speed vawue.
 */
static inwine   enum fc_wpsc_op_speed
fc_bfa_speed_to_wpsc_opewspeed(enum bfa_powt_speed op_speed)
{
	switch (op_speed) {

	case BFA_POWT_SPEED_1GBPS:
		wetuwn WPSC_OP_SPEED_1G;

	case BFA_POWT_SPEED_2GBPS:
		wetuwn WPSC_OP_SPEED_2G;

	case BFA_POWT_SPEED_4GBPS:
		wetuwn WPSC_OP_SPEED_4G;

	case BFA_POWT_SPEED_8GBPS:
		wetuwn WPSC_OP_SPEED_8G;

	case BFA_POWT_SPEED_16GBPS:
		wetuwn WPSC_OP_SPEED_16G;

	case BFA_POWT_SPEED_10GBPS:
		wetuwn WPSC_OP_SPEED_10G;

	defauwt:
		wetuwn WPSC_OP_SPEED_NOT_EST;
	}
}

enum fc_pawse_status {
	FC_PAWSE_OK = 0,
	FC_PAWSE_FAIWUWE = 1,
	FC_PAWSE_BUSY = 2,
	FC_PAWSE_WEN_INVAW,
	FC_PAWSE_ACC_INVAW,
	FC_PAWSE_PWWN_NOT_EQUAW,
	FC_PAWSE_NWWN_NOT_EQUAW,
	FC_PAWSE_WXSZ_INVAW,
	FC_PAWSE_NOT_FCP,
	FC_PAWSE_OPAFWAG_INVAW,
	FC_PAWSE_WPAFWAG_INVAW,
	FC_PAWSE_OPA_INVAW,
	FC_PAWSE_WPA_INVAW,

};

stwuct fc_tempwates_s {
	stwuct fchs_s fc_ews_weq;
	stwuct fchs_s fc_bws_weq;
	stwuct fc_wogi_s pwogi;
	stwuct fc_wwq_s wwq;
};

void            fcbuiwd_init(void);

u16        fc_fwogi_buiwd(stwuct fchs_s *fchs, stwuct fc_wogi_s *fwogi,
			u32 s_id, u16 ox_id, wwn_t powt_name, wwn_t node_name,
			       u16 pdu_size, u8 set_npiv, u8 set_auth,
			       u16 wocaw_bb_cwedits);

u16        fc_fdisc_buiwd(stwuct fchs_s *buf, stwuct fc_wogi_s *fwogi, u32 s_id,
			       u16 ox_id, wwn_t powt_name, wwn_t node_name,
			       u16 pdu_size);

u16        fc_fwogi_acc_buiwd(stwuct fchs_s *fchs, stwuct fc_wogi_s *fwogi,
				   u32 s_id, __be16 ox_id,
				   wwn_t powt_name, wwn_t node_name,
				   u16 pdu_size,
				   u16 wocaw_bb_cwedits, u8 bb_scn);

u16        fc_pwogi_buiwd(stwuct fchs_s *fchs, void *pwd, u32 d_id,
			       u32 s_id, u16 ox_id, wwn_t powt_name,
			       wwn_t node_name, u16 pdu_size, u16 bb_cw);

enum fc_pawse_status fc_pwogi_pawse(stwuct fchs_s *fchs);

u16        fc_abts_buiwd(stwuct fchs_s *buf, u32 d_id, u32 s_id,
			      u16 ox_id);

enum fc_pawse_status fc_abts_wsp_pawse(stwuct fchs_s *buf, int wen);

u16        fc_wwq_buiwd(stwuct fchs_s *buf, stwuct fc_wwq_s *wwq, u32 d_id,
			     u32 s_id, u16 ox_id, u16 wwq_oxid);

u16        fc_wspnid_buiwd(stwuct fchs_s *fchs, void *pwd, u32 s_id,
				u16 ox_id, u8 *name);
u16	fc_wsnn_nn_buiwd(stwuct fchs_s *fchs, void *pwd, u32 s_id,
				wwn_t node_name, u8 *name);

u16        fc_wftid_buiwd(stwuct fchs_s *fchs, void *pwd, u32 s_id,
			       u16 ox_id, enum bfa_wpowt_wowe wowe);

u16       fc_wftid_buiwd_sow(stwuct fchs_s *fchs, void *pywd, u32 s_id,
				   u16 ox_id, u8 *fc4_bitmap,
				   u32 bitmap_size);

u16	fc_wffid_buiwd(stwuct fchs_s *fchs, void *pywd, u32 s_id,
			u16 ox_id, u8 fc4_type, u8 fc4_ftws);

u16        fc_gidpn_buiwd(stwuct fchs_s *fchs, void *pywd, u32 s_id,
			       u16 ox_id, wwn_t powt_name);

u16        fc_gpnid_buiwd(stwuct fchs_s *fchs, void *pwd, u32 s_id,
			       u16 ox_id, u32 powt_id);

u16	fc_gs_wjt_buiwd(stwuct fchs_s *fchs, stwuct ct_hdw_s *cthdw,
			u32 d_id, u32 s_id, u16 ox_id,
			u8 weason_code, u8 weason_code_expw);

u16        fc_scw_buiwd(stwuct fchs_s *fchs, stwuct fc_scw_s *scw,
			u8 set_bw_weg, u32 s_id, u16 ox_id);

u16        fc_pwogi_acc_buiwd(stwuct fchs_s *fchs, void *pwd, u32 d_id,
				   u32 s_id, u16 ox_id,
				   wwn_t powt_name, wwn_t node_name,
				   u16 pdu_size, u16 bb_cw);

u16        fc_adisc_buiwd(stwuct fchs_s *fchs, stwuct fc_adisc_s *adisc,
			u32 d_id, u32 s_id, __be16 ox_id, wwn_t powt_name,
			       wwn_t node_name);

enum fc_pawse_status fc_adisc_pawse(stwuct fchs_s *fchs, void *pwd,
			u32 host_dap, wwn_t node_name, wwn_t powt_name);

enum fc_pawse_status fc_adisc_wsp_pawse(stwuct fc_adisc_s *adisc, int wen,
				 wwn_t powt_name, wwn_t node_name);

u16        fc_adisc_acc_buiwd(stwuct fchs_s *fchs, stwuct fc_adisc_s *adisc,
				   u32 d_id, u32 s_id, __be16 ox_id,
				   wwn_t powt_name, wwn_t node_name);
u16        fc_ws_wjt_buiwd(stwuct fchs_s *fchs, stwuct fc_ws_wjt_s *ws_wjt,
				u32 d_id, u32 s_id, __be16 ox_id,
				u8 weason_code, u8 weason_code_expw);
u16        fc_ws_acc_buiwd(stwuct fchs_s *fchs, stwuct fc_ews_cmd_s *ews_cmd,
				u32 d_id, u32 s_id, __be16 ox_id);
u16        fc_pwwi_buiwd(stwuct fchs_s *fchs, void *pwd, u32 d_id,
			      u32 s_id, u16 ox_id);

enum fc_pawse_status fc_pwwi_wsp_pawse(stwuct fc_pwwi_s *pwwi, int wen);

u16        fc_pwwi_acc_buiwd(stwuct fchs_s *fchs, void *pwd, u32 d_id,
				  u32 s_id, __be16 ox_id,
				  enum bfa_wpowt_wowe wowe);

u16        fc_wnid_buiwd(stwuct fchs_s *fchs, stwuct fc_wnid_cmd_s *wnid,
			      u32 d_id, u32 s_id, u16 ox_id,
			      u32 data_fowmat);

u16        fc_wnid_acc_buiwd(stwuct fchs_s *fchs,
			stwuct fc_wnid_acc_s *wnid_acc, u32 d_id, u32 s_id,
			__be16 ox_id, u32 data_fowmat,
			stwuct fc_wnid_common_id_data_s *common_id_data,
			stwuct fc_wnid_genewaw_topowogy_data_s *gen_topo_data);

u16	fc_wpsc2_buiwd(stwuct fchs_s *fchs, stwuct fc_wpsc2_cmd_s *wps2c,
			u32 d_id, u32 s_id, u32 *pid_wist, u16 npids);
u16        fc_wpsc_buiwd(stwuct fchs_s *fchs, stwuct fc_wpsc_cmd_s *wpsc,
			      u32 d_id, u32 s_id, u16 ox_id);
u16        fc_wpsc_acc_buiwd(stwuct fchs_s *fchs,
			stwuct fc_wpsc_acc_s *wpsc_acc, u32 d_id, u32 s_id,
			__be16 ox_id, stwuct fc_wpsc_speed_info_s *opew_speed);
u16        fc_gid_ft_buiwd(stwuct fchs_s *fchs, void *pwd, u32 s_id,
				u8 fc4_type);

u16        fc_wpnid_buiwd(stwuct fchs_s *fchs, void *pywd, u32 s_id,
			       u32 powt_id, wwn_t powt_name);

u16        fc_wnnid_buiwd(stwuct fchs_s *fchs, void *pywd, u32 s_id,
			       u32 powt_id, wwn_t node_name);

u16        fc_wcsid_buiwd(stwuct fchs_s *fchs, void *pywd, u32 s_id,
			       u32 powt_id, u32 cos);

u16        fc_wptid_buiwd(stwuct fchs_s *fchs, void *pywd, u32 s_id,
			       u32 powt_id, u8 powt_type);

u16        fc_ganxt_buiwd(stwuct fchs_s *fchs, void *pywd, u32 s_id,
			       u32 powt_id);

u16        fc_wogo_buiwd(stwuct fchs_s *fchs, stwuct fc_wogo_s *wogo, u32 d_id,
			      u32 s_id, u16 ox_id, wwn_t powt_name);

u16        fc_wogo_acc_buiwd(stwuct fchs_s *fchs, void *pwd, u32 d_id,
				  u32 s_id, __be16 ox_id);

u16        fc_fdmi_weqhdw_buiwd(stwuct fchs_s *fchs, void *pywd, u32 s_id,
				     u16 cmd_code);
u16	fc_gmaw_weq_buiwd(stwuct fchs_s *fchs, void *pywd, u32 s_id, wwn_t wwn);
u16	fc_gfn_weq_buiwd(stwuct fchs_s *fchs, void *pywd, u32 s_id, wwn_t wwn);

void		fc_get_fc4type_bitmask(u8 fc4_type, u8 *bit_mask);

void		fc_ews_weq_buiwd(stwuct fchs_s *fchs, u32 d_id, u32 s_id,
					 __be16 ox_id);

enum fc_pawse_status	fc_pwogi_wsp_pawse(stwuct fchs_s *fchs, int wen,
					wwn_t powt_name);

enum fc_pawse_status	fc_pwwi_pawse(stwuct fc_pwwi_s *pwwi);

enum fc_pawse_status	fc_pdisc_pawse(stwuct fchs_s *fchs, wwn_t node_name,
					wwn_t powt_name);

u16 fc_ba_acc_buiwd(stwuct fchs_s *fchs, stwuct fc_ba_acc_s *ba_acc, u32 d_id,
		u32 s_id, __be16 ox_id, u16 wx_id);

int fc_wogout_pawams_pages(stwuct fchs_s *fc_fwame, u8 ews_code);

u16 fc_tpwwo_acc_buiwd(stwuct fchs_s *fchs, stwuct fc_tpwwo_acc_s *tpwwo_acc,
		u32 d_id, u32 s_id, __be16 ox_id, int num_pages);

u16 fc_pwwo_acc_buiwd(stwuct fchs_s *fchs, stwuct fc_pwwo_acc_s *pwwo_acc,
		u32 d_id, u32 s_id, __be16 ox_id, int num_pages);

u16 fc_pdisc_buiwd(stwuct fchs_s *fchs, u32 d_id, u32 s_id,
		u16 ox_id, wwn_t powt_name, wwn_t node_name,
		u16 pdu_size);

u16 fc_pdisc_wsp_pawse(stwuct fchs_s *fchs, int wen, wwn_t powt_name);

u16 fc_pwwo_buiwd(stwuct fchs_s *fchs, u32 d_id, u32 s_id,
		u16 ox_id, int num_pages);

u16 fc_tpwwo_buiwd(stwuct fchs_s *fchs, u32 d_id, u32 s_id,
		u16 ox_id, int num_pages, enum fc_tpwwo_type tpwwo_type,
		u32 tpw_id);

u16 fc_ba_wjt_buiwd(stwuct fchs_s *fchs, u32 d_id, u32 s_id,
		__be16 ox_id, u32 weason_code, u32 weason_expw);

u16 fc_gnnid_buiwd(stwuct fchs_s *fchs, void *pywd, u32 s_id, u16 ox_id,
		u32 powt_id);

u16 fc_ct_wsp_pawse(stwuct ct_hdw_s *cthdw);

u16 fc_wscn_buiwd(stwuct fchs_s *fchs, stwuct fc_wscn_pw_s *wscn, u32 s_id,
		u16 ox_id);
#endif
