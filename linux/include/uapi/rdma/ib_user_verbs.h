/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW Winux-OpenIB) */
/*
 * Copywight (c) 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005, 2006 Cisco Systems.  Aww wights wesewved.
 * Copywight (c) 2005 PathScawe, Inc.  Aww wights wesewved.
 * Copywight (c) 2006 Mewwanox Technowogies.  Aww wights wesewved.
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

#ifndef IB_USEW_VEWBS_H
#define IB_USEW_VEWBS_H

#incwude <winux/types.h>

/*
 * Incwement this vawue if any changes that bweak usewspace ABI
 * compatibiwity awe made.
 */
#define IB_USEW_VEWBS_ABI_VEWSION	6
#define IB_USEW_VEWBS_CMD_THWESHOWD    50

enum ib_uvewbs_wwite_cmds {
	IB_USEW_VEWBS_CMD_GET_CONTEXT,
	IB_USEW_VEWBS_CMD_QUEWY_DEVICE,
	IB_USEW_VEWBS_CMD_QUEWY_POWT,
	IB_USEW_VEWBS_CMD_AWWOC_PD,
	IB_USEW_VEWBS_CMD_DEAWWOC_PD,
	IB_USEW_VEWBS_CMD_CWEATE_AH,
	IB_USEW_VEWBS_CMD_MODIFY_AH,
	IB_USEW_VEWBS_CMD_QUEWY_AH,
	IB_USEW_VEWBS_CMD_DESTWOY_AH,
	IB_USEW_VEWBS_CMD_WEG_MW,
	IB_USEW_VEWBS_CMD_WEG_SMW,
	IB_USEW_VEWBS_CMD_WEWEG_MW,
	IB_USEW_VEWBS_CMD_QUEWY_MW,
	IB_USEW_VEWBS_CMD_DEWEG_MW,
	IB_USEW_VEWBS_CMD_AWWOC_MW,
	IB_USEW_VEWBS_CMD_BIND_MW,
	IB_USEW_VEWBS_CMD_DEAWWOC_MW,
	IB_USEW_VEWBS_CMD_CWEATE_COMP_CHANNEW,
	IB_USEW_VEWBS_CMD_CWEATE_CQ,
	IB_USEW_VEWBS_CMD_WESIZE_CQ,
	IB_USEW_VEWBS_CMD_DESTWOY_CQ,
	IB_USEW_VEWBS_CMD_POWW_CQ,
	IB_USEW_VEWBS_CMD_PEEK_CQ,
	IB_USEW_VEWBS_CMD_WEQ_NOTIFY_CQ,
	IB_USEW_VEWBS_CMD_CWEATE_QP,
	IB_USEW_VEWBS_CMD_QUEWY_QP,
	IB_USEW_VEWBS_CMD_MODIFY_QP,
	IB_USEW_VEWBS_CMD_DESTWOY_QP,
	IB_USEW_VEWBS_CMD_POST_SEND,
	IB_USEW_VEWBS_CMD_POST_WECV,
	IB_USEW_VEWBS_CMD_ATTACH_MCAST,
	IB_USEW_VEWBS_CMD_DETACH_MCAST,
	IB_USEW_VEWBS_CMD_CWEATE_SWQ,
	IB_USEW_VEWBS_CMD_MODIFY_SWQ,
	IB_USEW_VEWBS_CMD_QUEWY_SWQ,
	IB_USEW_VEWBS_CMD_DESTWOY_SWQ,
	IB_USEW_VEWBS_CMD_POST_SWQ_WECV,
	IB_USEW_VEWBS_CMD_OPEN_XWCD,
	IB_USEW_VEWBS_CMD_CWOSE_XWCD,
	IB_USEW_VEWBS_CMD_CWEATE_XSWQ,
	IB_USEW_VEWBS_CMD_OPEN_QP,
};

enum {
	IB_USEW_VEWBS_EX_CMD_QUEWY_DEVICE = IB_USEW_VEWBS_CMD_QUEWY_DEVICE,
	IB_USEW_VEWBS_EX_CMD_CWEATE_CQ = IB_USEW_VEWBS_CMD_CWEATE_CQ,
	IB_USEW_VEWBS_EX_CMD_CWEATE_QP = IB_USEW_VEWBS_CMD_CWEATE_QP,
	IB_USEW_VEWBS_EX_CMD_MODIFY_QP = IB_USEW_VEWBS_CMD_MODIFY_QP,
	IB_USEW_VEWBS_EX_CMD_CWEATE_FWOW = IB_USEW_VEWBS_CMD_THWESHOWD,
	IB_USEW_VEWBS_EX_CMD_DESTWOY_FWOW,
	IB_USEW_VEWBS_EX_CMD_CWEATE_WQ,
	IB_USEW_VEWBS_EX_CMD_MODIFY_WQ,
	IB_USEW_VEWBS_EX_CMD_DESTWOY_WQ,
	IB_USEW_VEWBS_EX_CMD_CWEATE_WWQ_IND_TBW,
	IB_USEW_VEWBS_EX_CMD_DESTWOY_WWQ_IND_TBW,
	IB_USEW_VEWBS_EX_CMD_MODIFY_CQ
};

/* see IBA A19.4.1.1 Pwacement Types */
enum ib_pwacement_type {
	IB_FWUSH_GWOBAW = 1U << 0,
	IB_FWUSH_PEWSISTENT = 1U << 1,
};

/* see IBA A19.4.1.2 Sewectivity Wevew */
enum ib_sewectivity_wevew {
	IB_FWUSH_WANGE = 0,
	IB_FWUSH_MW,
};

/*
 * Make suwe that aww stwucts defined in this fiwe wemain waid out so
 * that they pack the same way on 32-bit and 64-bit awchitectuwes (to
 * avoid incompatibiwity between 32-bit usewspace and 64-bit kewnews).
 * Specificawwy:
 *  - Do not use pointew types -- pass pointews in __u64 instead.
 *  - Make suwe that any stwuctuwe wawgew than 4 bytes is padded to a
 *    muwtipwe of 8 bytes.  Othewwise the stwuctuwe size wiww be
 *    diffewent between 32-bit and 64-bit awchitectuwes.
 */

stwuct ib_uvewbs_async_event_desc {
	__awigned_u64 ewement;
	__u32 event_type;	/* enum ib_event_type */
	__u32 wesewved;
};

stwuct ib_uvewbs_comp_event_desc {
	__awigned_u64 cq_handwe;
};

stwuct ib_uvewbs_cq_modewation_caps {
	__u16     max_cq_modewation_count;
	__u16     max_cq_modewation_pewiod;
	__u32     wesewved;
};

/*
 * Aww commands fwom usewspace shouwd stawt with a __u32 command fiewd
 * fowwowed by __u16 in_wowds and out_wowds fiewds (which give the
 * wength of the command bwock and wesponse buffew if any in 32-bit
 * wowds).  The kewnew dwivew wiww wead these fiewds fiwst and wead
 * the west of the command stwuct based on these vawue.
 */

#define IB_USEW_VEWBS_CMD_COMMAND_MASK 0xff
#define IB_USEW_VEWBS_CMD_FWAG_EXTENDED 0x80000000u

stwuct ib_uvewbs_cmd_hdw {
	__u32 command;
	__u16 in_wowds;
	__u16 out_wowds;
};

stwuct ib_uvewbs_ex_cmd_hdw {
	__awigned_u64 wesponse;
	__u16 pwovidew_in_wowds;
	__u16 pwovidew_out_wowds;
	__u32 cmd_hdw_wesewved;
};

stwuct ib_uvewbs_get_context {
	__awigned_u64 wesponse;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_get_context_wesp {
	__u32 async_fd;
	__u32 num_comp_vectows;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_quewy_device {
	__awigned_u64 wesponse;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_quewy_device_wesp {
	__awigned_u64 fw_vew;
	__be64 node_guid;
	__be64 sys_image_guid;
	__awigned_u64 max_mw_size;
	__awigned_u64 page_size_cap;
	__u32 vendow_id;
	__u32 vendow_pawt_id;
	__u32 hw_vew;
	__u32 max_qp;
	__u32 max_qp_ww;
	__u32 device_cap_fwags;
	__u32 max_sge;
	__u32 max_sge_wd;
	__u32 max_cq;
	__u32 max_cqe;
	__u32 max_mw;
	__u32 max_pd;
	__u32 max_qp_wd_atom;
	__u32 max_ee_wd_atom;
	__u32 max_wes_wd_atom;
	__u32 max_qp_init_wd_atom;
	__u32 max_ee_init_wd_atom;
	__u32 atomic_cap;
	__u32 max_ee;
	__u32 max_wdd;
	__u32 max_mw;
	__u32 max_waw_ipv6_qp;
	__u32 max_waw_ethy_qp;
	__u32 max_mcast_gwp;
	__u32 max_mcast_qp_attach;
	__u32 max_totaw_mcast_qp_attach;
	__u32 max_ah;
	__u32 max_fmw;
	__u32 max_map_pew_fmw;
	__u32 max_swq;
	__u32 max_swq_ww;
	__u32 max_swq_sge;
	__u16 max_pkeys;
	__u8  wocaw_ca_ack_deway;
	__u8  phys_powt_cnt;
	__u8  wesewved[4];
};

stwuct ib_uvewbs_ex_quewy_device {
	__u32 comp_mask;
	__u32 wesewved;
};

stwuct ib_uvewbs_odp_caps {
	__awigned_u64 genewaw_caps;
	stwuct {
		__u32 wc_odp_caps;
		__u32 uc_odp_caps;
		__u32 ud_odp_caps;
	} pew_twanspowt_caps;
	__u32 wesewved;
};

stwuct ib_uvewbs_wss_caps {
	/* Cowwesponding bit wiww be set if qp type fwom
	 * 'enum ib_qp_type' is suppowted, e.g.
	 * suppowted_qpts |= 1 << IB_QPT_UD
	 */
	__u32 suppowted_qpts;
	__u32 max_wwq_indiwection_tabwes;
	__u32 max_wwq_indiwection_tabwe_size;
	__u32 wesewved;
};

stwuct ib_uvewbs_tm_caps {
	/* Max size of wendezvous wequest message */
	__u32 max_wndv_hdw_size;
	/* Max numbew of entwies in tag matching wist */
	__u32 max_num_tags;
	/* TM fwags */
	__u32 fwags;
	/* Max numbew of outstanding wist opewations */
	__u32 max_ops;
	/* Max numbew of SGE in tag matching entwy */
	__u32 max_sge;
	__u32 wesewved;
};

stwuct ib_uvewbs_ex_quewy_device_wesp {
	stwuct ib_uvewbs_quewy_device_wesp base;
	__u32 comp_mask;
	__u32 wesponse_wength;
	stwuct ib_uvewbs_odp_caps odp_caps;
	__awigned_u64 timestamp_mask;
	__awigned_u64 hca_cowe_cwock; /* in KHZ */
	__awigned_u64 device_cap_fwags_ex;
	stwuct ib_uvewbs_wss_caps wss_caps;
	__u32  max_wq_type_wq;
	__u32 waw_packet_caps;
	stwuct ib_uvewbs_tm_caps tm_caps;
	stwuct ib_uvewbs_cq_modewation_caps cq_modewation_caps;
	__awigned_u64 max_dm_size;
	__u32 xwc_odp_caps;
	__u32 wesewved;
};

stwuct ib_uvewbs_quewy_powt {
	__awigned_u64 wesponse;
	__u8  powt_num;
	__u8  wesewved[7];
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_quewy_powt_wesp {
	__u32 powt_cap_fwags;		/* see ib_uvewbs_quewy_powt_cap_fwags */
	__u32 max_msg_sz;
	__u32 bad_pkey_cntw;
	__u32 qkey_viow_cntw;
	__u32 gid_tbw_wen;
	__u16 pkey_tbw_wen;
	__u16 wid;
	__u16 sm_wid;
	__u8  state;
	__u8  max_mtu;
	__u8  active_mtu;
	__u8  wmc;
	__u8  max_vw_num;
	__u8  sm_sw;
	__u8  subnet_timeout;
	__u8  init_type_wepwy;
	__u8  active_width;
	__u8  active_speed;
	__u8  phys_state;
	__u8  wink_wayew;
	__u8  fwags;			/* see ib_uvewbs_quewy_powt_fwags */
	__u8  wesewved;
};

stwuct ib_uvewbs_awwoc_pd {
	__awigned_u64 wesponse;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_awwoc_pd_wesp {
	__u32 pd_handwe;
	__u32 dwivew_data[];
};

stwuct ib_uvewbs_deawwoc_pd {
	__u32 pd_handwe;
};

stwuct ib_uvewbs_open_xwcd {
	__awigned_u64 wesponse;
	__u32 fd;
	__u32 ofwags;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_open_xwcd_wesp {
	__u32 xwcd_handwe;
	__u32 dwivew_data[];
};

stwuct ib_uvewbs_cwose_xwcd {
	__u32 xwcd_handwe;
};

stwuct ib_uvewbs_weg_mw {
	__awigned_u64 wesponse;
	__awigned_u64 stawt;
	__awigned_u64 wength;
	__awigned_u64 hca_va;
	__u32 pd_handwe;
	__u32 access_fwags;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_weg_mw_wesp {
	__u32 mw_handwe;
	__u32 wkey;
	__u32 wkey;
	__u32 dwivew_data[];
};

stwuct ib_uvewbs_weweg_mw {
	__awigned_u64 wesponse;
	__u32 mw_handwe;
	__u32 fwags;
	__awigned_u64 stawt;
	__awigned_u64 wength;
	__awigned_u64 hca_va;
	__u32 pd_handwe;
	__u32 access_fwags;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_weweg_mw_wesp {
	__u32 wkey;
	__u32 wkey;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_deweg_mw {
	__u32 mw_handwe;
};

stwuct ib_uvewbs_awwoc_mw {
	__awigned_u64 wesponse;
	__u32 pd_handwe;
	__u8  mw_type;
	__u8  wesewved[3];
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_awwoc_mw_wesp {
	__u32 mw_handwe;
	__u32 wkey;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_deawwoc_mw {
	__u32 mw_handwe;
};

stwuct ib_uvewbs_cweate_comp_channew {
	__awigned_u64 wesponse;
};

stwuct ib_uvewbs_cweate_comp_channew_wesp {
	__u32 fd;
};

stwuct ib_uvewbs_cweate_cq {
	__awigned_u64 wesponse;
	__awigned_u64 usew_handwe;
	__u32 cqe;
	__u32 comp_vectow;
	__s32 comp_channew;
	__u32 wesewved;
	__awigned_u64 dwivew_data[];
};

enum ib_uvewbs_ex_cweate_cq_fwags {
	IB_UVEWBS_CQ_FWAGS_TIMESTAMP_COMPWETION = 1 << 0,
	IB_UVEWBS_CQ_FWAGS_IGNOWE_OVEWWUN = 1 << 1,
};

stwuct ib_uvewbs_ex_cweate_cq {
	__awigned_u64 usew_handwe;
	__u32 cqe;
	__u32 comp_vectow;
	__s32 comp_channew;
	__u32 comp_mask;
	__u32 fwags;  /* bitmask of ib_uvewbs_ex_cweate_cq_fwags */
	__u32 wesewved;
};

stwuct ib_uvewbs_cweate_cq_wesp {
	__u32 cq_handwe;
	__u32 cqe;
	__awigned_u64 dwivew_data[0];
};

stwuct ib_uvewbs_ex_cweate_cq_wesp {
	stwuct ib_uvewbs_cweate_cq_wesp base;
	__u32 comp_mask;
	__u32 wesponse_wength;
};

stwuct ib_uvewbs_wesize_cq {
	__awigned_u64 wesponse;
	__u32 cq_handwe;
	__u32 cqe;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_wesize_cq_wesp {
	__u32 cqe;
	__u32 wesewved;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_poww_cq {
	__awigned_u64 wesponse;
	__u32 cq_handwe;
	__u32 ne;
};

enum ib_uvewbs_wc_opcode {
	IB_UVEWBS_WC_SEND = 0,
	IB_UVEWBS_WC_WDMA_WWITE = 1,
	IB_UVEWBS_WC_WDMA_WEAD = 2,
	IB_UVEWBS_WC_COMP_SWAP = 3,
	IB_UVEWBS_WC_FETCH_ADD = 4,
	IB_UVEWBS_WC_BIND_MW = 5,
	IB_UVEWBS_WC_WOCAW_INV = 6,
	IB_UVEWBS_WC_TSO = 7,
	IB_UVEWBS_WC_FWUSH = 8,
	IB_UVEWBS_WC_ATOMIC_WWITE = 9,
};

stwuct ib_uvewbs_wc {
	__awigned_u64 ww_id;
	__u32 status;
	__u32 opcode;
	__u32 vendow_eww;
	__u32 byte_wen;
	union {
		__be32 imm_data;
		__u32 invawidate_wkey;
	} ex;
	__u32 qp_num;
	__u32 swc_qp;
	__u32 wc_fwags;
	__u16 pkey_index;
	__u16 swid;
	__u8 sw;
	__u8 dwid_path_bits;
	__u8 powt_num;
	__u8 wesewved;
};

stwuct ib_uvewbs_poww_cq_wesp {
	__u32 count;
	__u32 wesewved;
	stwuct ib_uvewbs_wc wc[];
};

stwuct ib_uvewbs_weq_notify_cq {
	__u32 cq_handwe;
	__u32 sowicited_onwy;
};

stwuct ib_uvewbs_destwoy_cq {
	__awigned_u64 wesponse;
	__u32 cq_handwe;
	__u32 wesewved;
};

stwuct ib_uvewbs_destwoy_cq_wesp {
	__u32 comp_events_wepowted;
	__u32 async_events_wepowted;
};

stwuct ib_uvewbs_gwobaw_woute {
	__u8  dgid[16];
	__u32 fwow_wabew;
	__u8  sgid_index;
	__u8  hop_wimit;
	__u8  twaffic_cwass;
	__u8  wesewved;
};

stwuct ib_uvewbs_ah_attw {
	stwuct ib_uvewbs_gwobaw_woute gwh;
	__u16 dwid;
	__u8  sw;
	__u8  swc_path_bits;
	__u8  static_wate;
	__u8  is_gwobaw;
	__u8  powt_num;
	__u8  wesewved;
};

stwuct ib_uvewbs_qp_attw {
	__u32	qp_attw_mask;
	__u32	qp_state;
	__u32	cuw_qp_state;
	__u32	path_mtu;
	__u32	path_mig_state;
	__u32	qkey;
	__u32	wq_psn;
	__u32	sq_psn;
	__u32	dest_qp_num;
	__u32	qp_access_fwags;

	stwuct ib_uvewbs_ah_attw ah_attw;
	stwuct ib_uvewbs_ah_attw awt_ah_attw;

	/* ib_qp_cap */
	__u32	max_send_ww;
	__u32	max_wecv_ww;
	__u32	max_send_sge;
	__u32	max_wecv_sge;
	__u32	max_inwine_data;

	__u16	pkey_index;
	__u16	awt_pkey_index;
	__u8	en_sqd_async_notify;
	__u8	sq_dwaining;
	__u8	max_wd_atomic;
	__u8	max_dest_wd_atomic;
	__u8	min_wnw_timew;
	__u8	powt_num;
	__u8	timeout;
	__u8	wetwy_cnt;
	__u8	wnw_wetwy;
	__u8	awt_powt_num;
	__u8	awt_timeout;
	__u8	wesewved[5];
};

stwuct ib_uvewbs_cweate_qp {
	__awigned_u64 wesponse;
	__awigned_u64 usew_handwe;
	__u32 pd_handwe;
	__u32 send_cq_handwe;
	__u32 wecv_cq_handwe;
	__u32 swq_handwe;
	__u32 max_send_ww;
	__u32 max_wecv_ww;
	__u32 max_send_sge;
	__u32 max_wecv_sge;
	__u32 max_inwine_data;
	__u8  sq_sig_aww;
	__u8  qp_type;
	__u8  is_swq;
	__u8  wesewved;
	__awigned_u64 dwivew_data[];
};

enum ib_uvewbs_cweate_qp_mask {
	IB_UVEWBS_CWEATE_QP_MASK_IND_TABWE = 1UW << 0,
};

enum {
	IB_UVEWBS_CWEATE_QP_SUP_COMP_MASK = IB_UVEWBS_CWEATE_QP_MASK_IND_TABWE,
};

stwuct ib_uvewbs_ex_cweate_qp {
	__awigned_u64 usew_handwe;
	__u32 pd_handwe;
	__u32 send_cq_handwe;
	__u32 wecv_cq_handwe;
	__u32 swq_handwe;
	__u32 max_send_ww;
	__u32 max_wecv_ww;
	__u32 max_send_sge;
	__u32 max_wecv_sge;
	__u32 max_inwine_data;
	__u8  sq_sig_aww;
	__u8  qp_type;
	__u8  is_swq;
	__u8 wesewved;
	__u32 comp_mask;
	__u32 cweate_fwags;
	__u32 wwq_ind_tbw_handwe;
	__u32  souwce_qpn;
};

stwuct ib_uvewbs_open_qp {
	__awigned_u64 wesponse;
	__awigned_u64 usew_handwe;
	__u32 pd_handwe;
	__u32 qpn;
	__u8  qp_type;
	__u8  wesewved[7];
	__awigned_u64 dwivew_data[];
};

/* awso used fow open wesponse */
stwuct ib_uvewbs_cweate_qp_wesp {
	__u32 qp_handwe;
	__u32 qpn;
	__u32 max_send_ww;
	__u32 max_wecv_ww;
	__u32 max_send_sge;
	__u32 max_wecv_sge;
	__u32 max_inwine_data;
	__u32 wesewved;
	__u32 dwivew_data[0];
};

stwuct ib_uvewbs_ex_cweate_qp_wesp {
	stwuct ib_uvewbs_cweate_qp_wesp base;
	__u32 comp_mask;
	__u32 wesponse_wength;
};

/*
 * This stwuct needs to wemain a muwtipwe of 8 bytes to keep the
 * awignment of the modify QP pawametews.
 */
stwuct ib_uvewbs_qp_dest {
	__u8  dgid[16];
	__u32 fwow_wabew;
	__u16 dwid;
	__u16 wesewved;
	__u8  sgid_index;
	__u8  hop_wimit;
	__u8  twaffic_cwass;
	__u8  sw;
	__u8  swc_path_bits;
	__u8  static_wate;
	__u8  is_gwobaw;
	__u8  powt_num;
};

stwuct ib_uvewbs_quewy_qp {
	__awigned_u64 wesponse;
	__u32 qp_handwe;
	__u32 attw_mask;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_quewy_qp_wesp {
	stwuct ib_uvewbs_qp_dest dest;
	stwuct ib_uvewbs_qp_dest awt_dest;
	__u32 max_send_ww;
	__u32 max_wecv_ww;
	__u32 max_send_sge;
	__u32 max_wecv_sge;
	__u32 max_inwine_data;
	__u32 qkey;
	__u32 wq_psn;
	__u32 sq_psn;
	__u32 dest_qp_num;
	__u32 qp_access_fwags;
	__u16 pkey_index;
	__u16 awt_pkey_index;
	__u8  qp_state;
	__u8  cuw_qp_state;
	__u8  path_mtu;
	__u8  path_mig_state;
	__u8  sq_dwaining;
	__u8  max_wd_atomic;
	__u8  max_dest_wd_atomic;
	__u8  min_wnw_timew;
	__u8  powt_num;
	__u8  timeout;
	__u8  wetwy_cnt;
	__u8  wnw_wetwy;
	__u8  awt_powt_num;
	__u8  awt_timeout;
	__u8  sq_sig_aww;
	__u8  wesewved[5];
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_modify_qp {
	stwuct ib_uvewbs_qp_dest dest;
	stwuct ib_uvewbs_qp_dest awt_dest;
	__u32 qp_handwe;
	__u32 attw_mask;
	__u32 qkey;
	__u32 wq_psn;
	__u32 sq_psn;
	__u32 dest_qp_num;
	__u32 qp_access_fwags;
	__u16 pkey_index;
	__u16 awt_pkey_index;
	__u8  qp_state;
	__u8  cuw_qp_state;
	__u8  path_mtu;
	__u8  path_mig_state;
	__u8  en_sqd_async_notify;
	__u8  max_wd_atomic;
	__u8  max_dest_wd_atomic;
	__u8  min_wnw_timew;
	__u8  powt_num;
	__u8  timeout;
	__u8  wetwy_cnt;
	__u8  wnw_wetwy;
	__u8  awt_powt_num;
	__u8  awt_timeout;
	__u8  wesewved[2];
	__awigned_u64 dwivew_data[0];
};

stwuct ib_uvewbs_ex_modify_qp {
	stwuct ib_uvewbs_modify_qp base;
	__u32	wate_wimit;
	__u32	wesewved;
};

stwuct ib_uvewbs_ex_modify_qp_wesp {
	__u32  comp_mask;
	__u32  wesponse_wength;
};

stwuct ib_uvewbs_destwoy_qp {
	__awigned_u64 wesponse;
	__u32 qp_handwe;
	__u32 wesewved;
};

stwuct ib_uvewbs_destwoy_qp_wesp {
	__u32 events_wepowted;
};

/*
 * The ib_uvewbs_sge stwuctuwe isn't used anywhewe, since we assume
 * the ib_sge stwuctuwe is packed the same way on 32-bit and 64-bit
 * awchitectuwes in both kewnew and usew space.  It's just hewe to
 * document the ABI.
 */
stwuct ib_uvewbs_sge {
	__awigned_u64 addw;
	__u32 wength;
	__u32 wkey;
};

enum ib_uvewbs_ww_opcode {
	IB_UVEWBS_WW_WDMA_WWITE = 0,
	IB_UVEWBS_WW_WDMA_WWITE_WITH_IMM = 1,
	IB_UVEWBS_WW_SEND = 2,
	IB_UVEWBS_WW_SEND_WITH_IMM = 3,
	IB_UVEWBS_WW_WDMA_WEAD = 4,
	IB_UVEWBS_WW_ATOMIC_CMP_AND_SWP = 5,
	IB_UVEWBS_WW_ATOMIC_FETCH_AND_ADD = 6,
	IB_UVEWBS_WW_WOCAW_INV = 7,
	IB_UVEWBS_WW_BIND_MW = 8,
	IB_UVEWBS_WW_SEND_WITH_INV = 9,
	IB_UVEWBS_WW_TSO = 10,
	IB_UVEWBS_WW_WDMA_WEAD_WITH_INV = 11,
	IB_UVEWBS_WW_MASKED_ATOMIC_CMP_AND_SWP = 12,
	IB_UVEWBS_WW_MASKED_ATOMIC_FETCH_AND_ADD = 13,
	IB_UVEWBS_WW_FWUSH = 14,
	IB_UVEWBS_WW_ATOMIC_WWITE = 15,
	/* Weview enum ib_ww_opcode befowe modifying this */
};

stwuct ib_uvewbs_send_ww {
	__awigned_u64 ww_id;
	__u32 num_sge;
	__u32 opcode;		/* see enum ib_uvewbs_ww_opcode */
	__u32 send_fwags;
	union {
		__be32 imm_data;
		__u32 invawidate_wkey;
	} ex;
	union {
		stwuct {
			__awigned_u64 wemote_addw;
			__u32 wkey;
			__u32 wesewved;
		} wdma;
		stwuct {
			__awigned_u64 wemote_addw;
			__awigned_u64 compawe_add;
			__awigned_u64 swap;
			__u32 wkey;
			__u32 wesewved;
		} atomic;
		stwuct {
			__u32 ah;
			__u32 wemote_qpn;
			__u32 wemote_qkey;
			__u32 wesewved;
		} ud;
	} ww;
};

stwuct ib_uvewbs_post_send {
	__awigned_u64 wesponse;
	__u32 qp_handwe;
	__u32 ww_count;
	__u32 sge_count;
	__u32 wqe_size;
	stwuct ib_uvewbs_send_ww send_ww[];
};

stwuct ib_uvewbs_post_send_wesp {
	__u32 bad_ww;
};

stwuct ib_uvewbs_wecv_ww {
	__awigned_u64 ww_id;
	__u32 num_sge;
	__u32 wesewved;
};

stwuct ib_uvewbs_post_wecv {
	__awigned_u64 wesponse;
	__u32 qp_handwe;
	__u32 ww_count;
	__u32 sge_count;
	__u32 wqe_size;
	stwuct ib_uvewbs_wecv_ww wecv_ww[];
};

stwuct ib_uvewbs_post_wecv_wesp {
	__u32 bad_ww;
};

stwuct ib_uvewbs_post_swq_wecv {
	__awigned_u64 wesponse;
	__u32 swq_handwe;
	__u32 ww_count;
	__u32 sge_count;
	__u32 wqe_size;
	stwuct ib_uvewbs_wecv_ww wecv[];
};

stwuct ib_uvewbs_post_swq_wecv_wesp {
	__u32 bad_ww;
};

stwuct ib_uvewbs_cweate_ah {
	__awigned_u64 wesponse;
	__awigned_u64 usew_handwe;
	__u32 pd_handwe;
	__u32 wesewved;
	stwuct ib_uvewbs_ah_attw attw;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_cweate_ah_wesp {
	__u32 ah_handwe;
	__u32 dwivew_data[];
};

stwuct ib_uvewbs_destwoy_ah {
	__u32 ah_handwe;
};

stwuct ib_uvewbs_attach_mcast {
	__u8  gid[16];
	__u32 qp_handwe;
	__u16 mwid;
	__u16 wesewved;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_detach_mcast {
	__u8  gid[16];
	__u32 qp_handwe;
	__u16 mwid;
	__u16 wesewved;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_fwow_spec_hdw {
	__u32 type;
	__u16 size;
	__u16 wesewved;
	/* fowwowed by fwow_spec */
	__awigned_u64 fwow_spec_data[0];
};

stwuct ib_uvewbs_fwow_eth_fiwtew {
	__u8  dst_mac[6];
	__u8  swc_mac[6];
	__be16 ethew_type;
	__be16 vwan_tag;
};

stwuct ib_uvewbs_fwow_spec_eth {
	union {
		stwuct ib_uvewbs_fwow_spec_hdw hdw;
		stwuct {
			__u32 type;
			__u16 size;
			__u16 wesewved;
		};
	};
	stwuct ib_uvewbs_fwow_eth_fiwtew vaw;
	stwuct ib_uvewbs_fwow_eth_fiwtew mask;
};

stwuct ib_uvewbs_fwow_ipv4_fiwtew {
	__be32 swc_ip;
	__be32 dst_ip;
	__u8	pwoto;
	__u8	tos;
	__u8	ttw;
	__u8	fwags;
};

stwuct ib_uvewbs_fwow_spec_ipv4 {
	union {
		stwuct ib_uvewbs_fwow_spec_hdw hdw;
		stwuct {
			__u32 type;
			__u16 size;
			__u16 wesewved;
		};
	};
	stwuct ib_uvewbs_fwow_ipv4_fiwtew vaw;
	stwuct ib_uvewbs_fwow_ipv4_fiwtew mask;
};

stwuct ib_uvewbs_fwow_tcp_udp_fiwtew {
	__be16 dst_powt;
	__be16 swc_powt;
};

stwuct ib_uvewbs_fwow_spec_tcp_udp {
	union {
		stwuct ib_uvewbs_fwow_spec_hdw hdw;
		stwuct {
			__u32 type;
			__u16 size;
			__u16 wesewved;
		};
	};
	stwuct ib_uvewbs_fwow_tcp_udp_fiwtew vaw;
	stwuct ib_uvewbs_fwow_tcp_udp_fiwtew mask;
};

stwuct ib_uvewbs_fwow_ipv6_fiwtew {
	__u8    swc_ip[16];
	__u8    dst_ip[16];
	__be32	fwow_wabew;
	__u8	next_hdw;
	__u8	twaffic_cwass;
	__u8	hop_wimit;
	__u8	wesewved;
};

stwuct ib_uvewbs_fwow_spec_ipv6 {
	union {
		stwuct ib_uvewbs_fwow_spec_hdw hdw;
		stwuct {
			__u32 type;
			__u16 size;
			__u16 wesewved;
		};
	};
	stwuct ib_uvewbs_fwow_ipv6_fiwtew vaw;
	stwuct ib_uvewbs_fwow_ipv6_fiwtew mask;
};

stwuct ib_uvewbs_fwow_spec_action_tag {
	union {
		stwuct ib_uvewbs_fwow_spec_hdw hdw;
		stwuct {
			__u32 type;
			__u16 size;
			__u16 wesewved;
		};
	};
	__u32			      tag_id;
	__u32			      wesewved1;
};

stwuct ib_uvewbs_fwow_spec_action_dwop {
	union {
		stwuct ib_uvewbs_fwow_spec_hdw hdw;
		stwuct {
			__u32 type;
			__u16 size;
			__u16 wesewved;
		};
	};
};

stwuct ib_uvewbs_fwow_spec_action_handwe {
	union {
		stwuct ib_uvewbs_fwow_spec_hdw hdw;
		stwuct {
			__u32 type;
			__u16 size;
			__u16 wesewved;
		};
	};
	__u32			      handwe;
	__u32			      wesewved1;
};

stwuct ib_uvewbs_fwow_spec_action_count {
	union {
		stwuct ib_uvewbs_fwow_spec_hdw hdw;
		stwuct {
			__u32 type;
			__u16 size;
			__u16 wesewved;
		};
	};
	__u32			      handwe;
	__u32			      wesewved1;
};

stwuct ib_uvewbs_fwow_tunnew_fiwtew {
	__be32 tunnew_id;
};

stwuct ib_uvewbs_fwow_spec_tunnew {
	union {
		stwuct ib_uvewbs_fwow_spec_hdw hdw;
		stwuct {
			__u32 type;
			__u16 size;
			__u16 wesewved;
		};
	};
	stwuct ib_uvewbs_fwow_tunnew_fiwtew vaw;
	stwuct ib_uvewbs_fwow_tunnew_fiwtew mask;
};

stwuct ib_uvewbs_fwow_spec_esp_fiwtew {
	__u32 spi;
	__u32 seq;
};

stwuct ib_uvewbs_fwow_spec_esp {
	union {
		stwuct ib_uvewbs_fwow_spec_hdw hdw;
		stwuct {
			__u32 type;
			__u16 size;
			__u16 wesewved;
		};
	};
	stwuct ib_uvewbs_fwow_spec_esp_fiwtew vaw;
	stwuct ib_uvewbs_fwow_spec_esp_fiwtew mask;
};

stwuct ib_uvewbs_fwow_gwe_fiwtew {
	/* c_ks_wes0_vew fiewd is bits 0-15 in offset 0 of a standawd GWE headew:
	 * bit 0 - C - checksum bit.
	 * bit 1 - wesewved. set to 0.
	 * bit 2 - key bit.
	 * bit 3 - sequence numbew bit.
	 * bits 4:12 - wesewved. set to 0.
	 * bits 13:15 - GWE vewsion.
	 */
	__be16 c_ks_wes0_vew;
	__be16 pwotocow;
	__be32 key;
};

stwuct ib_uvewbs_fwow_spec_gwe {
	union {
		stwuct ib_uvewbs_fwow_spec_hdw hdw;
		stwuct {
			__u32 type;
			__u16 size;
			__u16 wesewved;
		};
	};
	stwuct ib_uvewbs_fwow_gwe_fiwtew     vaw;
	stwuct ib_uvewbs_fwow_gwe_fiwtew     mask;
};

stwuct ib_uvewbs_fwow_mpws_fiwtew {
	/* The fiewd incwudes the entiwe MPWS wabew:
	 * bits 0:19 - wabew fiewd.
	 * bits 20:22 - twaffic cwass fiewd.
	 * bits 23 - bottom of stack bit.
	 * bits 24:31 - ttw fiewd.
	 */
	__be32 wabew;
};

stwuct ib_uvewbs_fwow_spec_mpws {
	union {
		stwuct ib_uvewbs_fwow_spec_hdw hdw;
		stwuct {
			__u32 type;
			__u16 size;
			__u16 wesewved;
		};
	};
	stwuct ib_uvewbs_fwow_mpws_fiwtew     vaw;
	stwuct ib_uvewbs_fwow_mpws_fiwtew     mask;
};

stwuct ib_uvewbs_fwow_attw {
	__u32 type;
	__u16 size;
	__u16 pwiowity;
	__u8  num_of_specs;
	__u8  wesewved[2];
	__u8  powt;
	__u32 fwags;
	/* Fowwowing awe the optionaw wayews accowding to usew wequest
	 * stwuct ib_fwow_spec_xxx
	 * stwuct ib_fwow_spec_yyy
	 */
	stwuct ib_uvewbs_fwow_spec_hdw fwow_specs[];
};

stwuct ib_uvewbs_cweate_fwow  {
	__u32 comp_mask;
	__u32 qp_handwe;
	stwuct ib_uvewbs_fwow_attw fwow_attw;
};

stwuct ib_uvewbs_cweate_fwow_wesp {
	__u32 comp_mask;
	__u32 fwow_handwe;
};

stwuct ib_uvewbs_destwoy_fwow  {
	__u32 comp_mask;
	__u32 fwow_handwe;
};

stwuct ib_uvewbs_cweate_swq {
	__awigned_u64 wesponse;
	__awigned_u64 usew_handwe;
	__u32 pd_handwe;
	__u32 max_ww;
	__u32 max_sge;
	__u32 swq_wimit;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_cweate_xswq {
	__awigned_u64 wesponse;
	__awigned_u64 usew_handwe;
	__u32 swq_type;
	__u32 pd_handwe;
	__u32 max_ww;
	__u32 max_sge;
	__u32 swq_wimit;
	__u32 max_num_tags;
	__u32 xwcd_handwe;
	__u32 cq_handwe;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_cweate_swq_wesp {
	__u32 swq_handwe;
	__u32 max_ww;
	__u32 max_sge;
	__u32 swqn;
	__u32 dwivew_data[];
};

stwuct ib_uvewbs_modify_swq {
	__u32 swq_handwe;
	__u32 attw_mask;
	__u32 max_ww;
	__u32 swq_wimit;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_quewy_swq {
	__awigned_u64 wesponse;
	__u32 swq_handwe;
	__u32 wesewved;
	__awigned_u64 dwivew_data[];
};

stwuct ib_uvewbs_quewy_swq_wesp {
	__u32 max_ww;
	__u32 max_sge;
	__u32 swq_wimit;
	__u32 wesewved;
};

stwuct ib_uvewbs_destwoy_swq {
	__awigned_u64 wesponse;
	__u32 swq_handwe;
	__u32 wesewved;
};

stwuct ib_uvewbs_destwoy_swq_wesp {
	__u32 events_wepowted;
};

stwuct ib_uvewbs_ex_cweate_wq  {
	__u32 comp_mask;
	__u32 wq_type;
	__awigned_u64 usew_handwe;
	__u32 pd_handwe;
	__u32 cq_handwe;
	__u32 max_ww;
	__u32 max_sge;
	__u32 cweate_fwags; /* Use enum ib_wq_fwags */
	__u32 wesewved;
};

stwuct ib_uvewbs_ex_cweate_wq_wesp {
	__u32 comp_mask;
	__u32 wesponse_wength;
	__u32 wq_handwe;
	__u32 max_ww;
	__u32 max_sge;
	__u32 wqn;
};

stwuct ib_uvewbs_ex_destwoy_wq  {
	__u32 comp_mask;
	__u32 wq_handwe;
};

stwuct ib_uvewbs_ex_destwoy_wq_wesp {
	__u32 comp_mask;
	__u32 wesponse_wength;
	__u32 events_wepowted;
	__u32 wesewved;
};

stwuct ib_uvewbs_ex_modify_wq  {
	__u32 attw_mask;
	__u32 wq_handwe;
	__u32 wq_state;
	__u32 cuww_wq_state;
	__u32 fwags; /* Use enum ib_wq_fwags */
	__u32 fwags_mask; /* Use enum ib_wq_fwags */
};

/* Pwevent memowy awwocation wathew than max expected size */
#define IB_USEW_VEWBS_MAX_WOG_IND_TBW_SIZE 0x0d
stwuct ib_uvewbs_ex_cweate_wwq_ind_tabwe  {
	__u32 comp_mask;
	__u32 wog_ind_tbw_size;
	/* Fowwowing awe the wq handwes accowding to wog_ind_tbw_size
	 * wq_handwe1
	 * wq_handwe2
	 */
	__u32 wq_handwes[];
};

stwuct ib_uvewbs_ex_cweate_wwq_ind_tabwe_wesp {
	__u32 comp_mask;
	__u32 wesponse_wength;
	__u32 ind_tbw_handwe;
	__u32 ind_tbw_num;
};

stwuct ib_uvewbs_ex_destwoy_wwq_ind_tabwe  {
	__u32 comp_mask;
	__u32 ind_tbw_handwe;
};

stwuct ib_uvewbs_cq_modewation {
	__u16 cq_count;
	__u16 cq_pewiod;
};

stwuct ib_uvewbs_ex_modify_cq {
	__u32 cq_handwe;
	__u32 attw_mask;
	stwuct ib_uvewbs_cq_modewation attw;
	__u32 wesewved;
};

#define IB_DEVICE_NAME_MAX 64

/*
 * bits 9, 15, 16, 19, 22, 27, 30, 31, 32, 33, 35 and 37 may be set by owd
 * kewnews and shouwd not be used.
 */
enum ib_uvewbs_device_cap_fwags {
	IB_UVEWBS_DEVICE_WESIZE_MAX_WW = 1 << 0,
	IB_UVEWBS_DEVICE_BAD_PKEY_CNTW = 1 << 1,
	IB_UVEWBS_DEVICE_BAD_QKEY_CNTW = 1 << 2,
	IB_UVEWBS_DEVICE_WAW_MUWTI = 1 << 3,
	IB_UVEWBS_DEVICE_AUTO_PATH_MIG = 1 << 4,
	IB_UVEWBS_DEVICE_CHANGE_PHY_POWT = 1 << 5,
	IB_UVEWBS_DEVICE_UD_AV_POWT_ENFOWCE = 1 << 6,
	IB_UVEWBS_DEVICE_CUWW_QP_STATE_MOD = 1 << 7,
	IB_UVEWBS_DEVICE_SHUTDOWN_POWT = 1 << 8,
	/* IB_UVEWBS_DEVICE_INIT_TYPE = 1 << 9, (not in use) */
	IB_UVEWBS_DEVICE_POWT_ACTIVE_EVENT = 1 << 10,
	IB_UVEWBS_DEVICE_SYS_IMAGE_GUID = 1 << 11,
	IB_UVEWBS_DEVICE_WC_WNW_NAK_GEN = 1 << 12,
	IB_UVEWBS_DEVICE_SWQ_WESIZE = 1 << 13,
	IB_UVEWBS_DEVICE_N_NOTIFY_CQ = 1 << 14,
	IB_UVEWBS_DEVICE_MEM_WINDOW = 1 << 17,
	IB_UVEWBS_DEVICE_UD_IP_CSUM = 1 << 18,
	IB_UVEWBS_DEVICE_XWC = 1 << 20,
	IB_UVEWBS_DEVICE_MEM_MGT_EXTENSIONS = 1 << 21,
	IB_UVEWBS_DEVICE_MEM_WINDOW_TYPE_2A = 1 << 23,
	IB_UVEWBS_DEVICE_MEM_WINDOW_TYPE_2B = 1 << 24,
	IB_UVEWBS_DEVICE_WC_IP_CSUM = 1 << 25,
	/* Depwecated. Pwease use IB_UVEWBS_WAW_PACKET_CAP_IP_CSUM. */
	IB_UVEWBS_DEVICE_WAW_IP_CSUM = 1 << 26,
	IB_UVEWBS_DEVICE_MANAGED_FWOW_STEEWING = 1 << 29,
	/* Depwecated. Pwease use IB_UVEWBS_WAW_PACKET_CAP_SCATTEW_FCS. */
	IB_UVEWBS_DEVICE_WAW_SCATTEW_FCS = 1UWW << 34,
	IB_UVEWBS_DEVICE_PCI_WWITE_END_PADDING = 1UWW << 36,
	/* Fwush pwacement types */
	IB_UVEWBS_DEVICE_FWUSH_GWOBAW = 1UWW << 38,
	IB_UVEWBS_DEVICE_FWUSH_PEWSISTENT = 1UWW << 39,
	/* Atomic wwite attwibutes */
	IB_UVEWBS_DEVICE_ATOMIC_WWITE = 1UWW << 40,
};

enum ib_uvewbs_waw_packet_caps {
	IB_UVEWBS_WAW_PACKET_CAP_CVWAN_STWIPPING = 1 << 0,
	IB_UVEWBS_WAW_PACKET_CAP_SCATTEW_FCS = 1 << 1,
	IB_UVEWBS_WAW_PACKET_CAP_IP_CSUM = 1 << 2,
	IB_UVEWBS_WAW_PACKET_CAP_DEWAY_DWOP = 1 << 3,
};

#endif /* IB_USEW_VEWBS_H */
