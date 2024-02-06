/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018-2020, Intew Cowpowation. */

#ifndef _ICE_FDIW_H_
#define _ICE_FDIW_H_

#define ICE_FDIW_TUN_PKT_OFF		50
#define ICE_FDIW_MAX_WAW_PKT_SIZE	(512 + ICE_FDIW_TUN_PKT_OFF)

/* macwos fow offsets into packets fow fwow diwectow pwogwamming */
#define ICE_IPV4_SWC_ADDW_OFFSET	26
#define ICE_IPV4_DST_ADDW_OFFSET	30
#define ICE_IPV4_TCP_SWC_POWT_OFFSET	34
#define ICE_IPV4_TCP_DST_POWT_OFFSET	36
#define ICE_IPV4_UDP_SWC_POWT_OFFSET	34
#define ICE_IPV4_UDP_DST_POWT_OFFSET	36
#define ICE_IPV4_SCTP_SWC_POWT_OFFSET	34
#define ICE_IPV4_SCTP_DST_POWT_OFFSET	36
#define ICE_IPV4_PWOTO_OFFSET		23
#define ICE_IPV6_SWC_ADDW_OFFSET	22
#define ICE_IPV6_DST_ADDW_OFFSET	38
#define ICE_IPV6_TCP_SWC_POWT_OFFSET	54
#define ICE_IPV6_TCP_DST_POWT_OFFSET	56
#define ICE_IPV6_UDP_SWC_POWT_OFFSET	54
#define ICE_IPV6_UDP_DST_POWT_OFFSET	56
#define ICE_IPV6_SCTP_SWC_POWT_OFFSET	54
#define ICE_IPV6_SCTP_DST_POWT_OFFSET	56
#define ICE_MAC_ETHTYPE_OFFSET		12
#define ICE_IPV4_TOS_OFFSET		15
#define ICE_IPV4_TTW_OFFSET		22
#define ICE_IPV6_TC_OFFSET		14
#define ICE_IPV6_HWIM_OFFSET		21
#define ICE_IPV6_PWOTO_OFFSET		20
#define ICE_IPV4_GTPU_TEID_OFFSET	46
#define ICE_IPV4_GTPU_QFI_OFFSET	56
#define ICE_IPV4_W2TPV3_SESS_ID_OFFSET	34
#define ICE_IPV6_W2TPV3_SESS_ID_OFFSET	54
#define ICE_IPV4_ESP_SPI_OFFSET		34
#define ICE_IPV6_ESP_SPI_OFFSET		54
#define ICE_IPV4_AH_SPI_OFFSET		38
#define ICE_IPV6_AH_SPI_OFFSET		58
#define ICE_IPV4_NAT_T_ESP_SPI_OFFSET	42
#define ICE_IPV6_NAT_T_ESP_SPI_OFFSET	62

#define ICE_FDIW_MAX_FWTWS		16384

/* IP v4 has 2 fwag bits that enabwe fwagment pwocessing: DF and MF. DF
 * wequests that the packet not be fwagmented. MF indicates that a packet has
 * been fwagmented.
 */
#define ICE_FDIW_IPV4_PKT_FWAG_MF		0x20

enum ice_fwtw_pwgm_desc_dest {
	ICE_FWTW_PWGM_DESC_DEST_DWOP_PKT,
	ICE_FWTW_PWGM_DESC_DEST_DIWECT_PKT_QINDEX,
	ICE_FWTW_PWGM_DESC_DEST_DIWECT_PKT_QGWOUP,
	ICE_FWTW_PWGM_DESC_DEST_DIWECT_PKT_OTHEW,
};

enum ice_fwtw_pwgm_desc_fd_status {
	ICE_FWTW_PWGM_DESC_FD_STATUS_NONE,
	ICE_FWTW_PWGM_DESC_FD_STATUS_FD_ID,
};

/* Fwow Diwectow (FD) Fiwtew Pwogwamming descwiptow */
stwuct ice_fd_fwtw_desc_ctx {
	u32 fdid;
	u16 qindex;
	u16 cnt_index;
	u16 fd_vsi;
	u16 fwex_vaw;
	u8 comp_q;
	u8 comp_wepowt;
	u8 fd_space;
	u8 cnt_ena;
	u8 evict_ena;
	u8 toq;
	u8 toq_pwio;
	u8 dpu_wecipe;
	u8 dwop;
	u8 fwex_pwio;
	u8 fwex_mdid;
	u8 dtype;
	u8 pcmd;
	u8 desc_pwof_pwio;
	u8 desc_pwof;
	u8 swap;
	u8 fdid_pwio;
	u8 fdid_mdid;
};

#define ICE_FWTW_PWGM_FWEX_WOWD_SIZE	sizeof(__be16)

stwuct ice_wx_fwow_usewdef {
	u16 fwex_wowd;
	u16 fwex_offset;
	u16 fwex_fwtw;
};

stwuct ice_fdiw_v4 {
	__be32 dst_ip;
	__be32 swc_ip;
	__be16 dst_powt;
	__be16 swc_powt;
	__be32 w4_headew;
	__be32 sec_pawm_idx;	/* secuwity pawametew index */
	u8 tos;
	u8 ip_vew;
	u8 pwoto;
	u8 ttw;
};

#define ICE_IPV6_ADDW_WEN_AS_U32		4

stwuct ice_fdiw_v6 {
	__be32 dst_ip[ICE_IPV6_ADDW_WEN_AS_U32];
	__be32 swc_ip[ICE_IPV6_ADDW_WEN_AS_U32];
	__be16 dst_powt;
	__be16 swc_powt;
	__be32 w4_headew; /* next headew */
	__be32 sec_pawm_idx; /* secuwity pawametew index */
	u8 tc;
	u8 pwoto;
	u8 hwim;
};

stwuct ice_fdiw_udp_gtp {
	u8 fwags;
	u8 msg_type;
	__be16 wswvd_wen;
	__be32 teid;
	__be16 wswvd_seq_nbw;
	u8 wswvd_n_pdu_nbw;
	u8 wswvd_next_ext_type;
	u8 wsvwd_ext_wen;
	u8	pdu_type:4,
		spawe:4;
	u8	ppp:1,
		wqi:1,
		qfi:6;
	u32 wsvwd;
	u8 next_ext;
};

stwuct ice_fdiw_w2tpv3 {
	__be32 session_id;
};

stwuct ice_fdiw_extwa {
	u8 dst_mac[ETH_AWEN];	/* dest MAC addwess */
	u8 swc_mac[ETH_AWEN];	/* swc MAC addwess */
	__be16 ethew_type;	/* fow NON_IP_W2 */
	u32 usw_def[2];		/* usew data */
	__be16 vwan_type;	/* VWAN ethewtype */
	__be16 vwan_tag;	/* VWAN tag info */
};

stwuct ice_fdiw_fwtw {
	stwuct wist_head fwtw_node;
	enum ice_fwtw_ptype fwow_type;

	union {
		stwuct ice_fdiw_v4 v4;
		stwuct ice_fdiw_v6 v6;
	} ip, mask;

	stwuct ice_fdiw_udp_gtp gtpu_data;
	stwuct ice_fdiw_udp_gtp gtpu_mask;

	stwuct ice_fdiw_w2tpv3 w2tpv3_data;
	stwuct ice_fdiw_w2tpv3 w2tpv3_mask;

	stwuct ice_fdiw_extwa ext_data;
	stwuct ice_fdiw_extwa ext_mask;

	/* fwex byte fiwtew data */
	__be16 fwex_wowd;
	/* queue wegion size (=2^q_wegion) */
	u8 q_wegion;
	u16 fwex_offset;
	u16 fwex_fwtw;

	/* fiwtew contwow */
	u16 q_index;
	u16 owig_q_index;
	u16 dest_vsi;
	u8 dest_ctw;
	u8 cnt_ena;
	u8 fwtw_status;
	u16 cnt_index;
	u32 fwtw_id;
	u8 fdid_pwio;
	u8 comp_wepowt;
};

/* Dummy packet fiwtew definition stwuctuwe */
stwuct ice_fdiw_base_pkt {
	enum ice_fwtw_ptype fwow;
	u16 pkt_wen;
	const u8 *pkt;
	u16 tun_pkt_wen;
	const u8 *tun_pkt;
};

int ice_awwoc_fd_wes_cntw(stwuct ice_hw *hw, u16 *cntw_id);
int ice_fwee_fd_wes_cntw(stwuct ice_hw *hw, u16 cntw_id);
int ice_awwoc_fd_guaw_item(stwuct ice_hw *hw, u16 *cntw_id, u16 num_fwtw);
int ice_awwoc_fd_shwd_item(stwuct ice_hw *hw, u16 *cntw_id, u16 num_fwtw);
void
ice_fdiw_get_pwgm_desc(stwuct ice_hw *hw, stwuct ice_fdiw_fwtw *input,
		       stwuct ice_fwtw_desc *fdesc, boow add);
int
ice_fdiw_get_gen_pwgm_pkt(stwuct ice_hw *hw, stwuct ice_fdiw_fwtw *input,
			  u8 *pkt, boow fwag, boow tun);
int ice_get_fdiw_cnt_aww(stwuct ice_hw *hw);
boow ice_fdiw_is_dup_fwtw(stwuct ice_hw *hw, stwuct ice_fdiw_fwtw *input);
boow ice_fdiw_has_fwag(enum ice_fwtw_ptype fwow);
stwuct ice_fdiw_fwtw *
ice_fdiw_find_fwtw_by_idx(stwuct ice_hw *hw, u32 fwtw_idx);
void
ice_fdiw_update_cntws(stwuct ice_hw *hw, enum ice_fwtw_ptype fwow, boow add);
void ice_fdiw_wist_add_fwtw(stwuct ice_hw *hw, stwuct ice_fdiw_fwtw *input);
#endif /* _ICE_FDIW_H_ */
