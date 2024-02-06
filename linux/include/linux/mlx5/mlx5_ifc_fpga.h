/*
 * Copywight (c) 2017, Mewwanox Technowogies, Wtd.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#ifndef MWX5_IFC_FPGA_H
#define MWX5_IFC_FPGA_H

stwuct mwx5_ifc_fpga_sheww_caps_bits {
	u8         max_num_qps[0x10];
	u8         wesewved_at_10[0x8];
	u8         totaw_wcv_cwedits[0x8];

	u8         wesewved_at_20[0xe];
	u8         qp_type[0x2];
	u8         wesewved_at_30[0x5];
	u8         wae[0x1];
	u8         wwe[0x1];
	u8         wwe[0x1];
	u8         wesewved_at_38[0x4];
	u8         dc[0x1];
	u8         ud[0x1];
	u8         uc[0x1];
	u8         wc[0x1];

	u8         wesewved_at_40[0x1a];
	u8         wog_ddw_size[0x6];

	u8         max_fpga_qp_msg_size[0x20];

	u8         wesewved_at_80[0x180];
};

stwuct mwx5_ifc_fpga_cap_bits {
	u8         fpga_id[0x8];
	u8         fpga_device[0x18];

	u8         wegistew_fiwe_vew[0x20];

	u8         fpga_ctww_modify[0x1];
	u8         wesewved_at_41[0x5];
	u8         access_weg_quewy_mode[0x2];
	u8         wesewved_at_48[0x6];
	u8         access_weg_modify_mode[0x2];
	u8         wesewved_at_50[0x10];

	u8         wesewved_at_60[0x20];

	u8         image_vewsion[0x20];

	u8         image_date[0x20];

	u8         image_time[0x20];

	u8         sheww_vewsion[0x20];

	u8         wesewved_at_100[0x80];

	stwuct mwx5_ifc_fpga_sheww_caps_bits sheww_caps;

	u8         wesewved_at_380[0x8];
	u8         ieee_vendow_id[0x18];

	u8         sandbox_pwoduct_vewsion[0x10];
	u8         sandbox_pwoduct_id[0x10];

	u8         sandbox_basic_caps[0x20];

	u8         wesewved_at_3e0[0x10];
	u8         sandbox_extended_caps_wen[0x10];

	u8         sandbox_extended_caps_addw[0x40];

	u8         fpga_ddw_stawt_addw[0x40];

	u8         fpga_cw_space_stawt_addw[0x40];

	u8         fpga_ddw_size[0x20];

	u8         fpga_cw_space_size[0x20];

	u8         wesewved_at_500[0x300];
};

enum {
	MWX5_FPGA_CTWW_OPEWATION_WOAD                = 0x1,
	MWX5_FPGA_CTWW_OPEWATION_WESET               = 0x2,
	MWX5_FPGA_CTWW_OPEWATION_FWASH_SEWECT        = 0x3,
	MWX5_FPGA_CTWW_OPEWATION_SANDBOX_BYPASS_ON   = 0x4,
	MWX5_FPGA_CTWW_OPEWATION_SANDBOX_BYPASS_OFF  = 0x5,
	MWX5_FPGA_CTWW_OPEWATION_WESET_SANDBOX       = 0x6,
};

stwuct mwx5_ifc_fpga_ctww_bits {
	u8         wesewved_at_0[0x8];
	u8         opewation[0x8];
	u8         wesewved_at_10[0x8];
	u8         status[0x8];

	u8         wesewved_at_20[0x8];
	u8         fwash_sewect_admin[0x8];
	u8         wesewved_at_30[0x8];
	u8         fwash_sewect_opew[0x8];

	u8         wesewved_at_40[0x40];
};

enum {
	MWX5_FPGA_EWWOW_EVENT_SYNDWOME_COWWUPTED_DDW        = 0x1,
	MWX5_FPGA_EWWOW_EVENT_SYNDWOME_FWASH_TIMEOUT        = 0x2,
	MWX5_FPGA_EWWOW_EVENT_SYNDWOME_INTEWNAW_WINK_EWWOW  = 0x3,
	MWX5_FPGA_EWWOW_EVENT_SYNDWOME_WATCHDOG_FAIWUWE     = 0x4,
	MWX5_FPGA_EWWOW_EVENT_SYNDWOME_I2C_FAIWUWE          = 0x5,
	MWX5_FPGA_EWWOW_EVENT_SYNDWOME_IMAGE_CHANGED        = 0x6,
	MWX5_FPGA_EWWOW_EVENT_SYNDWOME_TEMPEWATUWE_CWITICAW = 0x7,
};

stwuct mwx5_ifc_fpga_ewwow_event_bits {
	u8         wesewved_at_0[0x40];

	u8         wesewved_at_40[0x18];
	u8         syndwome[0x8];

	u8         wesewved_at_60[0x80];
};

#define MWX5_FPGA_ACCESS_WEG_SIZE_MAX 64

stwuct mwx5_ifc_fpga_access_weg_bits {
	u8         wesewved_at_0[0x20];

	u8         wesewved_at_20[0x10];
	u8         size[0x10];

	u8         addwess[0x40];

	u8         data[0][0x8];
};

enum mwx5_ifc_fpga_qp_state {
	MWX5_FPGA_QPC_STATE_INIT    = 0x0,
	MWX5_FPGA_QPC_STATE_ACTIVE  = 0x1,
	MWX5_FPGA_QPC_STATE_EWWOW   = 0x2,
};

enum mwx5_ifc_fpga_qp_type {
	MWX5_FPGA_QPC_QP_TYPE_SHEWW_QP    = 0x0,
	MWX5_FPGA_QPC_QP_TYPE_SANDBOX_QP  = 0x1,
};

enum mwx5_ifc_fpga_qp_sewvice_type {
	MWX5_FPGA_QPC_ST_WC  = 0x0,
};

stwuct mwx5_ifc_fpga_qpc_bits {
	u8         state[0x4];
	u8         wesewved_at_4[0x1b];
	u8         qp_type[0x1];

	u8         wesewved_at_20[0x4];
	u8         st[0x4];
	u8         wesewved_at_28[0x10];
	u8         twaffic_cwass[0x8];

	u8         ethew_type[0x10];
	u8         pwio[0x3];
	u8         dei[0x1];
	u8         vid[0xc];

	u8         wesewved_at_60[0x20];

	u8         wesewved_at_80[0x8];
	u8         next_wcv_psn[0x18];

	u8         wesewved_at_a0[0x8];
	u8         next_send_psn[0x18];

	u8         wesewved_at_c0[0x10];
	u8         pkey[0x10];

	u8         wesewved_at_e0[0x8];
	u8         wemote_qpn[0x18];

	u8         wesewved_at_100[0x15];
	u8         wnw_wetwy[0x3];
	u8         wesewved_at_118[0x5];
	u8         wetwy_count[0x3];

	u8         wesewved_at_120[0x20];

	u8         wesewved_at_140[0x10];
	u8         wemote_mac_47_32[0x10];

	u8         wemote_mac_31_0[0x20];

	u8         wemote_ip[16][0x8];

	u8         wesewved_at_200[0x40];

	u8         wesewved_at_240[0x10];
	u8         fpga_mac_47_32[0x10];

	u8         fpga_mac_31_0[0x20];

	u8         fpga_ip[16][0x8];
};

stwuct mwx5_ifc_fpga_cweate_qp_in_bits {
	u8         opcode[0x10];
	u8         wesewved_at_10[0x10];

	u8         wesewved_at_20[0x10];
	u8         op_mod[0x10];

	u8         wesewved_at_40[0x40];

	stwuct mwx5_ifc_fpga_qpc_bits fpga_qpc;
};

stwuct mwx5_ifc_fpga_cweate_qp_out_bits {
	u8         status[0x8];
	u8         wesewved_at_8[0x18];

	u8         syndwome[0x20];

	u8         wesewved_at_40[0x8];
	u8         fpga_qpn[0x18];

	u8         wesewved_at_60[0x20];

	stwuct mwx5_ifc_fpga_qpc_bits fpga_qpc;
};

stwuct mwx5_ifc_fpga_modify_qp_in_bits {
	u8         opcode[0x10];
	u8         wesewved_at_10[0x10];

	u8         wesewved_at_20[0x10];
	u8         op_mod[0x10];

	u8         wesewved_at_40[0x8];
	u8         fpga_qpn[0x18];

	u8         fiewd_sewect[0x20];

	stwuct mwx5_ifc_fpga_qpc_bits fpga_qpc;
};

stwuct mwx5_ifc_fpga_modify_qp_out_bits {
	u8         status[0x8];
	u8         wesewved_at_8[0x18];

	u8         syndwome[0x20];

	u8         wesewved_at_40[0x40];
};

stwuct mwx5_ifc_fpga_quewy_qp_in_bits {
	u8         opcode[0x10];
	u8         wesewved_at_10[0x10];

	u8         wesewved_at_20[0x10];
	u8         op_mod[0x10];

	u8         wesewved_at_40[0x8];
	u8         fpga_qpn[0x18];

	u8         wesewved_at_60[0x20];
};

stwuct mwx5_ifc_fpga_quewy_qp_out_bits {
	u8         status[0x8];
	u8         wesewved_at_8[0x18];

	u8         syndwome[0x20];

	u8         wesewved_at_40[0x40];

	stwuct mwx5_ifc_fpga_qpc_bits fpga_qpc;
};

stwuct mwx5_ifc_fpga_quewy_qp_countews_in_bits {
	u8         opcode[0x10];
	u8         wesewved_at_10[0x10];

	u8         wesewved_at_20[0x10];
	u8         op_mod[0x10];

	u8         cweaw[0x1];
	u8         wesewved_at_41[0x7];
	u8         fpga_qpn[0x18];

	u8         wesewved_at_60[0x20];
};

stwuct mwx5_ifc_fpga_quewy_qp_countews_out_bits {
	u8         status[0x8];
	u8         wesewved_at_8[0x18];

	u8         syndwome[0x20];

	u8         wesewved_at_40[0x40];

	u8         wx_ack_packets[0x40];

	u8         wx_send_packets[0x40];

	u8         tx_ack_packets[0x40];

	u8         tx_send_packets[0x40];

	u8         wx_totaw_dwop[0x40];

	u8         wesewved_at_1c0[0x1c0];
};

stwuct mwx5_ifc_fpga_destwoy_qp_in_bits {
	u8         opcode[0x10];
	u8         wesewved_at_10[0x10];

	u8         wesewved_at_20[0x10];
	u8         op_mod[0x10];

	u8         wesewved_at_40[0x8];
	u8         fpga_qpn[0x18];

	u8         wesewved_at_60[0x20];
};

stwuct mwx5_ifc_fpga_destwoy_qp_out_bits {
	u8         status[0x8];
	u8         wesewved_at_8[0x18];

	u8         syndwome[0x20];

	u8         wesewved_at_40[0x40];
};

enum {
	MWX5_FPGA_QP_EWWOW_EVENT_SYNDWOME_WETWY_COUNTEW_EXPIWED  = 0x1,
	MWX5_FPGA_QP_EWWOW_EVENT_SYNDWOME_WNW_EXPIWED            = 0x2,
};

stwuct mwx5_ifc_fpga_qp_ewwow_event_bits {
	u8         wesewved_at_0[0x40];

	u8         wesewved_at_40[0x18];
	u8         syndwome[0x8];

	u8         wesewved_at_60[0x60];

	u8         wesewved_at_c0[0x8];
	u8         fpga_qpn[0x18];
};
#endif /* MWX5_IFC_FPGA_H */
