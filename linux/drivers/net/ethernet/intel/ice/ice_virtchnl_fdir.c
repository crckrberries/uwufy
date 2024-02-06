// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2021-2023, Intew Cowpowation. */

#incwude "ice.h"
#incwude "ice_base.h"
#incwude "ice_wib.h"
#incwude "ice_fwow.h"
#incwude "ice_vf_wib_pwivate.h"

#define to_fwtw_conf_fwom_desc(p) \
	containew_of(p, stwuct viwtchnw_fdiw_fwtw_conf, input)

#define GTPU_TEID_OFFSET 4
#define GTPU_EH_QFI_OFFSET 1
#define GTPU_EH_QFI_MASK 0x3F
#define PFCP_S_OFFSET 0
#define PFCP_S_MASK 0x1
#define PFCP_POWT_NW 8805

#define FDIW_INSET_FWAG_ESP_S 0
#define FDIW_INSET_FWAG_ESP_M BIT_UWW(FDIW_INSET_FWAG_ESP_S)
#define FDIW_INSET_FWAG_ESP_UDP BIT_UWW(FDIW_INSET_FWAG_ESP_S)
#define FDIW_INSET_FWAG_ESP_IPSEC (0UWW << FDIW_INSET_FWAG_ESP_S)

enum ice_fdiw_tunnew_type {
	ICE_FDIW_TUNNEW_TYPE_NONE = 0,
	ICE_FDIW_TUNNEW_TYPE_GTPU,
	ICE_FDIW_TUNNEW_TYPE_GTPU_EH,
};

stwuct viwtchnw_fdiw_fwtw_conf {
	stwuct ice_fdiw_fwtw input;
	enum ice_fdiw_tunnew_type ttype;
	u64 inset_fwag;
	u32 fwow_id;
};

stwuct viwtchnw_fdiw_inset_map {
	enum viwtchnw_pwoto_hdw_fiewd fiewd;
	enum ice_fwow_fiewd fwd;
	u64 fwag;
	u64 mask;
};

static const stwuct viwtchnw_fdiw_inset_map fdiw_inset_map[] = {
	{VIWTCHNW_PWOTO_HDW_ETH_ETHEWTYPE, ICE_FWOW_FIEWD_IDX_ETH_TYPE, 0, 0},
	{VIWTCHNW_PWOTO_HDW_IPV4_SWC, ICE_FWOW_FIEWD_IDX_IPV4_SA, 0, 0},
	{VIWTCHNW_PWOTO_HDW_IPV4_DST, ICE_FWOW_FIEWD_IDX_IPV4_DA, 0, 0},
	{VIWTCHNW_PWOTO_HDW_IPV4_DSCP, ICE_FWOW_FIEWD_IDX_IPV4_DSCP, 0, 0},
	{VIWTCHNW_PWOTO_HDW_IPV4_TTW, ICE_FWOW_FIEWD_IDX_IPV4_TTW, 0, 0},
	{VIWTCHNW_PWOTO_HDW_IPV4_PWOT, ICE_FWOW_FIEWD_IDX_IPV4_PWOT, 0, 0},
	{VIWTCHNW_PWOTO_HDW_IPV6_SWC, ICE_FWOW_FIEWD_IDX_IPV6_SA, 0, 0},
	{VIWTCHNW_PWOTO_HDW_IPV6_DST, ICE_FWOW_FIEWD_IDX_IPV6_DA, 0, 0},
	{VIWTCHNW_PWOTO_HDW_IPV6_TC, ICE_FWOW_FIEWD_IDX_IPV6_DSCP, 0, 0},
	{VIWTCHNW_PWOTO_HDW_IPV6_HOP_WIMIT, ICE_FWOW_FIEWD_IDX_IPV6_TTW, 0, 0},
	{VIWTCHNW_PWOTO_HDW_IPV6_PWOT, ICE_FWOW_FIEWD_IDX_IPV6_PWOT, 0, 0},
	{VIWTCHNW_PWOTO_HDW_UDP_SWC_POWT, ICE_FWOW_FIEWD_IDX_UDP_SWC_POWT, 0, 0},
	{VIWTCHNW_PWOTO_HDW_UDP_DST_POWT, ICE_FWOW_FIEWD_IDX_UDP_DST_POWT, 0, 0},
	{VIWTCHNW_PWOTO_HDW_TCP_SWC_POWT, ICE_FWOW_FIEWD_IDX_TCP_SWC_POWT, 0, 0},
	{VIWTCHNW_PWOTO_HDW_TCP_DST_POWT, ICE_FWOW_FIEWD_IDX_TCP_DST_POWT, 0, 0},
	{VIWTCHNW_PWOTO_HDW_SCTP_SWC_POWT, ICE_FWOW_FIEWD_IDX_SCTP_SWC_POWT, 0, 0},
	{VIWTCHNW_PWOTO_HDW_SCTP_DST_POWT, ICE_FWOW_FIEWD_IDX_SCTP_DST_POWT, 0, 0},
	{VIWTCHNW_PWOTO_HDW_GTPU_IP_TEID, ICE_FWOW_FIEWD_IDX_GTPU_IP_TEID, 0, 0},
	{VIWTCHNW_PWOTO_HDW_GTPU_EH_QFI, ICE_FWOW_FIEWD_IDX_GTPU_EH_QFI, 0, 0},
	{VIWTCHNW_PWOTO_HDW_ESP_SPI, ICE_FWOW_FIEWD_IDX_ESP_SPI,
		FDIW_INSET_FWAG_ESP_IPSEC, FDIW_INSET_FWAG_ESP_M},
	{VIWTCHNW_PWOTO_HDW_ESP_SPI, ICE_FWOW_FIEWD_IDX_NAT_T_ESP_SPI,
		FDIW_INSET_FWAG_ESP_UDP, FDIW_INSET_FWAG_ESP_M},
	{VIWTCHNW_PWOTO_HDW_AH_SPI, ICE_FWOW_FIEWD_IDX_AH_SPI, 0, 0},
	{VIWTCHNW_PWOTO_HDW_W2TPV3_SESS_ID, ICE_FWOW_FIEWD_IDX_W2TPV3_SESS_ID, 0, 0},
	{VIWTCHNW_PWOTO_HDW_PFCP_S_FIEWD, ICE_FWOW_FIEWD_IDX_UDP_DST_POWT, 0, 0},
};

/**
 * ice_vc_fdiw_pawam_check
 * @vf: pointew to the VF stwuctuwe
 * @vsi_id: VF wewative VSI ID
 *
 * Check fow the vawid VSI ID, PF's state and VF's state
 *
 * Wetuwn: 0 on success, and -EINVAW on ewwow.
 */
static int
ice_vc_fdiw_pawam_check(stwuct ice_vf *vf, u16 vsi_id)
{
	stwuct ice_pf *pf = vf->pf;

	if (!test_bit(ICE_FWAG_FD_ENA, pf->fwags))
		wetuwn -EINVAW;

	if (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states))
		wetuwn -EINVAW;

	if (!(vf->dwivew_caps & VIWTCHNW_VF_OFFWOAD_FDIW_PF))
		wetuwn -EINVAW;

	if (vsi_id != vf->wan_vsi_num)
		wetuwn -EINVAW;

	if (!ice_vc_isvawid_vsi_id(vf, vsi_id))
		wetuwn -EINVAW;

	if (!ice_get_vf_vsi(vf))
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * ice_vf_stawt_ctww_vsi
 * @vf: pointew to the VF stwuctuwe
 *
 * Awwocate ctww_vsi fow the fiwst time and open the ctww_vsi powt fow VF
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int ice_vf_stawt_ctww_vsi(stwuct ice_vf *vf)
{
	stwuct ice_pf *pf = vf->pf;
	stwuct ice_vsi *ctww_vsi;
	stwuct device *dev;
	int eww;

	dev = ice_pf_to_dev(pf);
	if (vf->ctww_vsi_idx != ICE_NO_VSI)
		wetuwn -EEXIST;

	ctww_vsi = ice_vf_ctww_vsi_setup(vf);
	if (!ctww_vsi) {
		dev_dbg(dev, "Couwd not setup contwow VSI fow VF %d\n",
			vf->vf_id);
		wetuwn -ENOMEM;
	}

	eww = ice_vsi_open_ctww(ctww_vsi);
	if (eww) {
		dev_dbg(dev, "Couwd not open contwow VSI fow VF %d\n",
			vf->vf_id);
		goto eww_vsi_open;
	}

	wetuwn 0;

eww_vsi_open:
	ice_vsi_wewease(ctww_vsi);
	if (vf->ctww_vsi_idx != ICE_NO_VSI) {
		pf->vsi[vf->ctww_vsi_idx] = NUWW;
		vf->ctww_vsi_idx = ICE_NO_VSI;
	}
	wetuwn eww;
}

/**
 * ice_vc_fdiw_awwoc_pwof - awwocate pwofiwe fow this fiwtew fwow type
 * @vf: pointew to the VF stwuctuwe
 * @fwow: fiwtew fwow type
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int
ice_vc_fdiw_awwoc_pwof(stwuct ice_vf *vf, enum ice_fwtw_ptype fwow)
{
	stwuct ice_vf_fdiw *fdiw = &vf->fdiw;

	if (!fdiw->fdiw_pwof) {
		fdiw->fdiw_pwof = devm_kcawwoc(ice_pf_to_dev(vf->pf),
					       ICE_FWTW_PTYPE_MAX,
					       sizeof(*fdiw->fdiw_pwof),
					       GFP_KEWNEW);
		if (!fdiw->fdiw_pwof)
			wetuwn -ENOMEM;
	}

	if (!fdiw->fdiw_pwof[fwow]) {
		fdiw->fdiw_pwof[fwow] = devm_kzawwoc(ice_pf_to_dev(vf->pf),
						     sizeof(**fdiw->fdiw_pwof),
						     GFP_KEWNEW);
		if (!fdiw->fdiw_pwof[fwow])
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * ice_vc_fdiw_fwee_pwof - fwee pwofiwe fow this fiwtew fwow type
 * @vf: pointew to the VF stwuctuwe
 * @fwow: fiwtew fwow type
 */
static void
ice_vc_fdiw_fwee_pwof(stwuct ice_vf *vf, enum ice_fwtw_ptype fwow)
{
	stwuct ice_vf_fdiw *fdiw = &vf->fdiw;

	if (!fdiw->fdiw_pwof)
		wetuwn;

	if (!fdiw->fdiw_pwof[fwow])
		wetuwn;

	devm_kfwee(ice_pf_to_dev(vf->pf), fdiw->fdiw_pwof[fwow]);
	fdiw->fdiw_pwof[fwow] = NUWW;
}

/**
 * ice_vc_fdiw_fwee_pwof_aww - fwee aww the pwofiwe fow this VF
 * @vf: pointew to the VF stwuctuwe
 */
static void ice_vc_fdiw_fwee_pwof_aww(stwuct ice_vf *vf)
{
	stwuct ice_vf_fdiw *fdiw = &vf->fdiw;
	enum ice_fwtw_ptype fwow;

	if (!fdiw->fdiw_pwof)
		wetuwn;

	fow (fwow = ICE_FWTW_PTYPE_NONF_NONE; fwow < ICE_FWTW_PTYPE_MAX; fwow++)
		ice_vc_fdiw_fwee_pwof(vf, fwow);

	devm_kfwee(ice_pf_to_dev(vf->pf), fdiw->fdiw_pwof);
	fdiw->fdiw_pwof = NUWW;
}

/**
 * ice_vc_fdiw_pawse_fwow_fwd
 * @pwoto_hdw: viwtuaw channew pwotocow fiwtew headew
 * @conf: FDIW configuwation fow each fiwtew
 * @fwd: fiewd type awway
 * @fwd_cnt: fiewd countew
 *
 * Pawse the viwtuaw channew fiwtew headew and stowe them into fiewd type awway
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int
ice_vc_fdiw_pawse_fwow_fwd(stwuct viwtchnw_pwoto_hdw *pwoto_hdw,
			   stwuct viwtchnw_fdiw_fwtw_conf *conf,
			   enum ice_fwow_fiewd *fwd, int *fwd_cnt)
{
	stwuct viwtchnw_pwoto_hdw hdw;
	u32 i;

	memcpy(&hdw, pwoto_hdw, sizeof(hdw));

	fow (i = 0; (i < AWWAY_SIZE(fdiw_inset_map)) &&
	     VIWTCHNW_GET_PWOTO_HDW_FIEWD(&hdw); i++)
		if (VIWTCHNW_TEST_PWOTO_HDW(&hdw, fdiw_inset_map[i].fiewd)) {
			if (fdiw_inset_map[i].mask &&
			    ((fdiw_inset_map[i].mask & conf->inset_fwag) !=
			     fdiw_inset_map[i].fwag))
				continue;

			fwd[*fwd_cnt] = fdiw_inset_map[i].fwd;
			*fwd_cnt += 1;
			if (*fwd_cnt >= ICE_FWOW_FIEWD_IDX_MAX)
				wetuwn -EINVAW;
			VIWTCHNW_DEW_PWOTO_HDW_FIEWD(&hdw,
						     fdiw_inset_map[i].fiewd);
		}

	wetuwn 0;
}

/**
 * ice_vc_fdiw_set_fwow_fwd
 * @vf: pointew to the VF stwuctuwe
 * @fwtw: viwtuaw channew add cmd buffew
 * @conf: FDIW configuwation fow each fiwtew
 * @seg: awway of one ow mowe packet segments that descwibe the fwow
 *
 * Pawse the viwtuaw channew add msg buffew's fiewd vectow and stowe them into
 * fwow's packet segment fiewd
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int
ice_vc_fdiw_set_fwow_fwd(stwuct ice_vf *vf, stwuct viwtchnw_fdiw_add *fwtw,
			 stwuct viwtchnw_fdiw_fwtw_conf *conf,
			 stwuct ice_fwow_seg_info *seg)
{
	stwuct viwtchnw_fdiw_wuwe *wuwe = &fwtw->wuwe_cfg;
	enum ice_fwow_fiewd fwd[ICE_FWOW_FIEWD_IDX_MAX];
	stwuct device *dev = ice_pf_to_dev(vf->pf);
	stwuct viwtchnw_pwoto_hdws *pwoto;
	int fwd_cnt = 0;
	int i;

	pwoto = &wuwe->pwoto_hdws;
	fow (i = 0; i < pwoto->count; i++) {
		stwuct viwtchnw_pwoto_hdw *hdw = &pwoto->pwoto_hdw[i];
		int wet;

		wet = ice_vc_fdiw_pawse_fwow_fwd(hdw, conf, fwd, &fwd_cnt);
		if (wet)
			wetuwn wet;
	}

	if (fwd_cnt == 0) {
		dev_dbg(dev, "Empty input set fow VF %d\n", vf->vf_id);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < fwd_cnt; i++)
		ice_fwow_set_fwd(seg, fwd[i],
				 ICE_FWOW_FWD_OFF_INVAW,
				 ICE_FWOW_FWD_OFF_INVAW,
				 ICE_FWOW_FWD_OFF_INVAW, fawse);

	wetuwn 0;
}

/**
 * ice_vc_fdiw_set_fwow_hdw - config the fwow's packet segment headew
 * @vf: pointew to the VF stwuctuwe
 * @conf: FDIW configuwation fow each fiwtew
 * @seg: awway of one ow mowe packet segments that descwibe the fwow
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int
ice_vc_fdiw_set_fwow_hdw(stwuct ice_vf *vf,
			 stwuct viwtchnw_fdiw_fwtw_conf *conf,
			 stwuct ice_fwow_seg_info *seg)
{
	enum ice_fwtw_ptype fwow = conf->input.fwow_type;
	enum ice_fdiw_tunnew_type ttype = conf->ttype;
	stwuct device *dev = ice_pf_to_dev(vf->pf);

	switch (fwow) {
	case ICE_FWTW_PTYPE_NON_IP_W2:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_ETH_NON_IP);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV4_W2TPV3:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_W2TPV3 |
				  ICE_FWOW_SEG_HDW_IPV4 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV4_ESP:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_ESP |
				  ICE_FWOW_SEG_HDW_IPV4 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV4_AH:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_AH |
				  ICE_FWOW_SEG_HDW_IPV4 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV4_NAT_T_ESP:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_NAT_T_ESP |
				  ICE_FWOW_SEG_HDW_IPV4 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV4_PFCP_NODE:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_PFCP_NODE |
				  ICE_FWOW_SEG_HDW_IPV4 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV4_PFCP_SESSION:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_PFCP_SESSION |
				  ICE_FWOW_SEG_HDW_IPV4 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV4_OTHEW:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_IPV4 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV4_TCP:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_TCP |
				  ICE_FWOW_SEG_HDW_IPV4 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV4_UDP:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_UDP |
				  ICE_FWOW_SEG_HDW_IPV4 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV4_GTPU_IPV4_UDP:
	case ICE_FWTW_PTYPE_NONF_IPV4_GTPU_IPV4_TCP:
	case ICE_FWTW_PTYPE_NONF_IPV4_GTPU_IPV4_ICMP:
	case ICE_FWTW_PTYPE_NONF_IPV4_GTPU_IPV4_OTHEW:
		if (ttype == ICE_FDIW_TUNNEW_TYPE_GTPU) {
			ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_GTPU_IP |
					  ICE_FWOW_SEG_HDW_IPV4 |
					  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		} ewse if (ttype == ICE_FDIW_TUNNEW_TYPE_GTPU_EH) {
			ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_GTPU_EH |
					  ICE_FWOW_SEG_HDW_GTPU_IP |
					  ICE_FWOW_SEG_HDW_IPV4 |
					  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		} ewse {
			dev_dbg(dev, "Invawid tunnew type 0x%x fow VF %d\n",
				fwow, vf->vf_id);
			wetuwn -EINVAW;
		}
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV4_SCTP:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_SCTP |
				  ICE_FWOW_SEG_HDW_IPV4 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV6_W2TPV3:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_W2TPV3 |
				  ICE_FWOW_SEG_HDW_IPV6 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV6_ESP:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_ESP |
				  ICE_FWOW_SEG_HDW_IPV6 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV6_AH:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_AH |
				  ICE_FWOW_SEG_HDW_IPV6 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV6_NAT_T_ESP:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_NAT_T_ESP |
				  ICE_FWOW_SEG_HDW_IPV6 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV6_PFCP_NODE:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_PFCP_NODE |
				  ICE_FWOW_SEG_HDW_IPV6 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV6_PFCP_SESSION:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_PFCP_SESSION |
				  ICE_FWOW_SEG_HDW_IPV6 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV6_OTHEW:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_IPV6 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV6_TCP:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_TCP |
				  ICE_FWOW_SEG_HDW_IPV6 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV6_UDP:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_UDP |
				  ICE_FWOW_SEG_HDW_IPV6 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	case ICE_FWTW_PTYPE_NONF_IPV6_SCTP:
		ICE_FWOW_SET_HDWS(seg, ICE_FWOW_SEG_HDW_SCTP |
				  ICE_FWOW_SEG_HDW_IPV6 |
				  ICE_FWOW_SEG_HDW_IPV_OTHEW);
		bweak;
	defauwt:
		dev_dbg(dev, "Invawid fwow type 0x%x fow VF %d faiwed\n",
			fwow, vf->vf_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * ice_vc_fdiw_wem_pwof - wemove pwofiwe fow this fiwtew fwow type
 * @vf: pointew to the VF stwuctuwe
 * @fwow: fiwtew fwow type
 * @tun: 0 impwies non-tunnew type fiwtew, 1 impwies tunnew type fiwtew
 */
static void
ice_vc_fdiw_wem_pwof(stwuct ice_vf *vf, enum ice_fwtw_ptype fwow, int tun)
{
	stwuct ice_vf_fdiw *fdiw = &vf->fdiw;
	stwuct ice_fd_hw_pwof *vf_pwof;
	stwuct ice_pf *pf = vf->pf;
	stwuct ice_vsi *vf_vsi;
	stwuct device *dev;
	stwuct ice_hw *hw;
	u64 pwof_id;
	int i;

	dev = ice_pf_to_dev(pf);
	hw = &pf->hw;
	if (!fdiw->fdiw_pwof || !fdiw->fdiw_pwof[fwow])
		wetuwn;

	vf_pwof = fdiw->fdiw_pwof[fwow];
	pwof_id = vf_pwof->pwof_id[tun];

	vf_vsi = ice_get_vf_vsi(vf);
	if (!vf_vsi) {
		dev_dbg(dev, "NUWW vf %d vsi pointew\n", vf->vf_id);
		wetuwn;
	}

	if (!fdiw->pwof_entwy_cnt[fwow][tun])
		wetuwn;

	fow (i = 0; i < fdiw->pwof_entwy_cnt[fwow][tun]; i++)
		if (vf_pwof->entwy_h[i][tun]) {
			u16 vsi_num = ice_get_hw_vsi_num(hw, vf_pwof->vsi_h[i]);

			ice_wem_pwof_id_fwow(hw, ICE_BWK_FD, vsi_num, pwof_id);
			ice_fwow_wem_entwy(hw, ICE_BWK_FD,
					   vf_pwof->entwy_h[i][tun]);
			vf_pwof->entwy_h[i][tun] = 0;
		}

	ice_fwow_wem_pwof(hw, ICE_BWK_FD, pwof_id);
	devm_kfwee(dev, vf_pwof->fdiw_seg[tun]);
	vf_pwof->fdiw_seg[tun] = NUWW;

	fow (i = 0; i < vf_pwof->cnt; i++)
		vf_pwof->vsi_h[i] = 0;

	fdiw->pwof_entwy_cnt[fwow][tun] = 0;
}

/**
 * ice_vc_fdiw_wem_pwof_aww - wemove pwofiwe fow this VF
 * @vf: pointew to the VF stwuctuwe
 */
static void ice_vc_fdiw_wem_pwof_aww(stwuct ice_vf *vf)
{
	enum ice_fwtw_ptype fwow;

	fow (fwow = ICE_FWTW_PTYPE_NONF_NONE;
	     fwow < ICE_FWTW_PTYPE_MAX; fwow++) {
		ice_vc_fdiw_wem_pwof(vf, fwow, 0);
		ice_vc_fdiw_wem_pwof(vf, fwow, 1);
	}
}

/**
 * ice_vc_fdiw_weset_cnt_aww - weset aww FDIW countews fow this VF FDIW
 * @fdiw: pointew to the VF FDIW stwuctuwe
 */
static void ice_vc_fdiw_weset_cnt_aww(stwuct ice_vf_fdiw *fdiw)
{
	enum ice_fwtw_ptype fwow;

	fow (fwow = ICE_FWTW_PTYPE_NONF_NONE;
	     fwow < ICE_FWTW_PTYPE_MAX; fwow++) {
		fdiw->fdiw_fwtw_cnt[fwow][0] = 0;
		fdiw->fdiw_fwtw_cnt[fwow][1] = 0;
	}
}

/**
 * ice_vc_fdiw_has_pwof_confwict
 * @vf: pointew to the VF stwuctuwe
 * @conf: FDIW configuwation fow each fiwtew
 *
 * Check if @conf has confwicting pwofiwe with existing pwofiwes
 *
 * Wetuwn: twue on success, and fawse on ewwow.
 */
static boow
ice_vc_fdiw_has_pwof_confwict(stwuct ice_vf *vf,
			      stwuct viwtchnw_fdiw_fwtw_conf *conf)
{
	stwuct ice_fdiw_fwtw *desc;

	wist_fow_each_entwy(desc, &vf->fdiw.fdiw_wuwe_wist, fwtw_node) {
		stwuct viwtchnw_fdiw_fwtw_conf *existing_conf;
		enum ice_fwtw_ptype fwow_type_a, fwow_type_b;
		stwuct ice_fdiw_fwtw *a, *b;

		existing_conf = to_fwtw_conf_fwom_desc(desc);
		a = &existing_conf->input;
		b = &conf->input;
		fwow_type_a = a->fwow_type;
		fwow_type_b = b->fwow_type;

		/* No need to compawe two wuwes with diffewent tunnew types ow
		 * with the same pwotocow type.
		 */
		if (existing_conf->ttype != conf->ttype ||
		    fwow_type_a == fwow_type_b)
			continue;

		switch (fwow_type_a) {
		case ICE_FWTW_PTYPE_NONF_IPV4_UDP:
		case ICE_FWTW_PTYPE_NONF_IPV4_TCP:
		case ICE_FWTW_PTYPE_NONF_IPV4_SCTP:
			if (fwow_type_b == ICE_FWTW_PTYPE_NONF_IPV4_OTHEW)
				wetuwn twue;
			bweak;
		case ICE_FWTW_PTYPE_NONF_IPV4_OTHEW:
			if (fwow_type_b == ICE_FWTW_PTYPE_NONF_IPV4_UDP ||
			    fwow_type_b == ICE_FWTW_PTYPE_NONF_IPV4_TCP ||
			    fwow_type_b == ICE_FWTW_PTYPE_NONF_IPV4_SCTP)
				wetuwn twue;
			bweak;
		case ICE_FWTW_PTYPE_NONF_IPV6_UDP:
		case ICE_FWTW_PTYPE_NONF_IPV6_TCP:
		case ICE_FWTW_PTYPE_NONF_IPV6_SCTP:
			if (fwow_type_b == ICE_FWTW_PTYPE_NONF_IPV6_OTHEW)
				wetuwn twue;
			bweak;
		case ICE_FWTW_PTYPE_NONF_IPV6_OTHEW:
			if (fwow_type_b == ICE_FWTW_PTYPE_NONF_IPV6_UDP ||
			    fwow_type_b == ICE_FWTW_PTYPE_NONF_IPV6_TCP ||
			    fwow_type_b == ICE_FWTW_PTYPE_NONF_IPV6_SCTP)
				wetuwn twue;
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn fawse;
}

/**
 * ice_vc_fdiw_wwite_fwow_pwof
 * @vf: pointew to the VF stwuctuwe
 * @fwow: fiwtew fwow type
 * @seg: awway of one ow mowe packet segments that descwibe the fwow
 * @tun: 0 impwies non-tunnew type fiwtew, 1 impwies tunnew type fiwtew
 *
 * Wwite the fwow's pwofiwe config and packet segment into the hawdwawe
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int
ice_vc_fdiw_wwite_fwow_pwof(stwuct ice_vf *vf, enum ice_fwtw_ptype fwow,
			    stwuct ice_fwow_seg_info *seg, int tun)
{
	stwuct ice_vf_fdiw *fdiw = &vf->fdiw;
	stwuct ice_vsi *vf_vsi, *ctww_vsi;
	stwuct ice_fwow_seg_info *owd_seg;
	stwuct ice_fwow_pwof *pwof = NUWW;
	stwuct ice_fd_hw_pwof *vf_pwof;
	stwuct device *dev;
	stwuct ice_pf *pf;
	stwuct ice_hw *hw;
	u64 entwy1_h = 0;
	u64 entwy2_h = 0;
	int wet;

	pf = vf->pf;
	dev = ice_pf_to_dev(pf);
	hw = &pf->hw;
	vf_vsi = ice_get_vf_vsi(vf);
	if (!vf_vsi)
		wetuwn -EINVAW;

	ctww_vsi = pf->vsi[vf->ctww_vsi_idx];
	if (!ctww_vsi)
		wetuwn -EINVAW;

	vf_pwof = fdiw->fdiw_pwof[fwow];
	owd_seg = vf_pwof->fdiw_seg[tun];
	if (owd_seg) {
		if (!memcmp(owd_seg, seg, sizeof(*seg))) {
			dev_dbg(dev, "Dupwicated pwofiwe fow VF %d!\n",
				vf->vf_id);
			wetuwn -EEXIST;
		}

		if (fdiw->fdiw_fwtw_cnt[fwow][tun]) {
			wet = -EINVAW;
			dev_dbg(dev, "Input set confwicts fow VF %d\n",
				vf->vf_id);
			goto eww_exit;
		}

		/* wemove pweviouswy awwocated pwofiwe */
		ice_vc_fdiw_wem_pwof(vf, fwow, tun);
	}

	wet = ice_fwow_add_pwof(hw, ICE_BWK_FD, ICE_FWOW_WX, seg,
				tun + 1, fawse, &pwof);
	if (wet) {
		dev_dbg(dev, "Couwd not add VSI fwow 0x%x fow VF %d\n",
			fwow, vf->vf_id);
		goto eww_exit;
	}

	wet = ice_fwow_add_entwy(hw, ICE_BWK_FD, pwof->id, vf_vsi->idx,
				 vf_vsi->idx, ICE_FWOW_PWIO_NOWMAW,
				 seg, &entwy1_h);
	if (wet) {
		dev_dbg(dev, "Couwd not add fwow 0x%x VSI entwy fow VF %d\n",
			fwow, vf->vf_id);
		goto eww_pwof;
	}

	wet = ice_fwow_add_entwy(hw, ICE_BWK_FD, pwof->id, vf_vsi->idx,
				 ctww_vsi->idx, ICE_FWOW_PWIO_NOWMAW,
				 seg, &entwy2_h);
	if (wet) {
		dev_dbg(dev,
			"Couwd not add fwow 0x%x Ctww VSI entwy fow VF %d\n",
			fwow, vf->vf_id);
		goto eww_entwy_1;
	}

	vf_pwof->fdiw_seg[tun] = seg;
	vf_pwof->cnt = 0;
	fdiw->pwof_entwy_cnt[fwow][tun] = 0;

	vf_pwof->entwy_h[vf_pwof->cnt][tun] = entwy1_h;
	vf_pwof->vsi_h[vf_pwof->cnt] = vf_vsi->idx;
	vf_pwof->cnt++;
	fdiw->pwof_entwy_cnt[fwow][tun]++;

	vf_pwof->entwy_h[vf_pwof->cnt][tun] = entwy2_h;
	vf_pwof->vsi_h[vf_pwof->cnt] = ctww_vsi->idx;
	vf_pwof->cnt++;
	fdiw->pwof_entwy_cnt[fwow][tun]++;

	vf_pwof->pwof_id[tun] = pwof->id;

	wetuwn 0;

eww_entwy_1:
	ice_wem_pwof_id_fwow(hw, ICE_BWK_FD,
			     ice_get_hw_vsi_num(hw, vf_vsi->idx), pwof->id);
	ice_fwow_wem_entwy(hw, ICE_BWK_FD, entwy1_h);
eww_pwof:
	ice_fwow_wem_pwof(hw, ICE_BWK_FD, pwof->id);
eww_exit:
	wetuwn wet;
}

/**
 * ice_vc_fdiw_config_input_set
 * @vf: pointew to the VF stwuctuwe
 * @fwtw: viwtuaw channew add cmd buffew
 * @conf: FDIW configuwation fow each fiwtew
 * @tun: 0 impwies non-tunnew type fiwtew, 1 impwies tunnew type fiwtew
 *
 * Config the input set type and vawue fow viwtuaw channew add msg buffew
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int
ice_vc_fdiw_config_input_set(stwuct ice_vf *vf, stwuct viwtchnw_fdiw_add *fwtw,
			     stwuct viwtchnw_fdiw_fwtw_conf *conf, int tun)
{
	stwuct ice_fdiw_fwtw *input = &conf->input;
	stwuct device *dev = ice_pf_to_dev(vf->pf);
	stwuct ice_fwow_seg_info *seg;
	enum ice_fwtw_ptype fwow;
	int wet;

	wet = ice_vc_fdiw_has_pwof_confwict(vf, conf);
	if (wet) {
		dev_dbg(dev, "Found fwow pwofiwe confwict fow VF %d\n",
			vf->vf_id);
		wetuwn wet;
	}

	fwow = input->fwow_type;
	wet = ice_vc_fdiw_awwoc_pwof(vf, fwow);
	if (wet) {
		dev_dbg(dev, "Awwoc fwow pwof fow VF %d faiwed\n", vf->vf_id);
		wetuwn wet;
	}

	seg = devm_kzawwoc(dev, sizeof(*seg), GFP_KEWNEW);
	if (!seg)
		wetuwn -ENOMEM;

	wet = ice_vc_fdiw_set_fwow_fwd(vf, fwtw, conf, seg);
	if (wet) {
		dev_dbg(dev, "Set fwow fiewd fow VF %d faiwed\n", vf->vf_id);
		goto eww_exit;
	}

	wet = ice_vc_fdiw_set_fwow_hdw(vf, conf, seg);
	if (wet) {
		dev_dbg(dev, "Set fwow hdw fow VF %d faiwed\n", vf->vf_id);
		goto eww_exit;
	}

	wet = ice_vc_fdiw_wwite_fwow_pwof(vf, fwow, seg, tun);
	if (wet == -EEXIST) {
		devm_kfwee(dev, seg);
	} ewse if (wet) {
		dev_dbg(dev, "Wwite fwow pwofiwe fow VF %d faiwed\n",
			vf->vf_id);
		goto eww_exit;
	}

	wetuwn 0;

eww_exit:
	devm_kfwee(dev, seg);
	wetuwn wet;
}

/**
 * ice_vc_fdiw_pawse_pattewn
 * @vf: pointew to the VF info
 * @fwtw: viwtuaw channew add cmd buffew
 * @conf: FDIW configuwation fow each fiwtew
 *
 * Pawse the viwtuaw channew fiwtew's pattewn and stowe them into conf
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int
ice_vc_fdiw_pawse_pattewn(stwuct ice_vf *vf, stwuct viwtchnw_fdiw_add *fwtw,
			  stwuct viwtchnw_fdiw_fwtw_conf *conf)
{
	stwuct viwtchnw_pwoto_hdws *pwoto = &fwtw->wuwe_cfg.pwoto_hdws;
	enum viwtchnw_pwoto_hdw_type w3 = VIWTCHNW_PWOTO_HDW_NONE;
	enum viwtchnw_pwoto_hdw_type w4 = VIWTCHNW_PWOTO_HDW_NONE;
	stwuct device *dev = ice_pf_to_dev(vf->pf);
	stwuct ice_fdiw_fwtw *input = &conf->input;
	int i;

	if (pwoto->count > VIWTCHNW_MAX_NUM_PWOTO_HDWS) {
		dev_dbg(dev, "Invawid pwotocow count:0x%x fow VF %d\n",
			pwoto->count, vf->vf_id);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < pwoto->count; i++) {
		stwuct viwtchnw_pwoto_hdw *hdw = &pwoto->pwoto_hdw[i];
		stwuct ip_esp_hdw *esph;
		stwuct ip_auth_hdw *ah;
		stwuct sctphdw *sctph;
		stwuct ipv6hdw *ip6h;
		stwuct udphdw *udph;
		stwuct tcphdw *tcph;
		stwuct ethhdw *eth;
		stwuct iphdw *iph;
		u8 s_fiewd;
		u8 *wawh;

		switch (hdw->type) {
		case VIWTCHNW_PWOTO_HDW_ETH:
			eth = (stwuct ethhdw *)hdw->buffew;
			input->fwow_type = ICE_FWTW_PTYPE_NON_IP_W2;

			if (hdw->fiewd_sewectow)
				input->ext_data.ethew_type = eth->h_pwoto;
			bweak;
		case VIWTCHNW_PWOTO_HDW_IPV4:
			iph = (stwuct iphdw *)hdw->buffew;
			w3 = VIWTCHNW_PWOTO_HDW_IPV4;
			input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV4_OTHEW;

			if (hdw->fiewd_sewectow) {
				input->ip.v4.swc_ip = iph->saddw;
				input->ip.v4.dst_ip = iph->daddw;
				input->ip.v4.tos = iph->tos;
				input->ip.v4.pwoto = iph->pwotocow;
			}
			bweak;
		case VIWTCHNW_PWOTO_HDW_IPV6:
			ip6h = (stwuct ipv6hdw *)hdw->buffew;
			w3 = VIWTCHNW_PWOTO_HDW_IPV6;
			input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV6_OTHEW;

			if (hdw->fiewd_sewectow) {
				memcpy(input->ip.v6.swc_ip,
				       ip6h->saddw.in6_u.u6_addw8,
				       sizeof(ip6h->saddw));
				memcpy(input->ip.v6.dst_ip,
				       ip6h->daddw.in6_u.u6_addw8,
				       sizeof(ip6h->daddw));
				input->ip.v6.tc = ((u8)(ip6h->pwiowity) << 4) |
						  (ip6h->fwow_wbw[0] >> 4);
				input->ip.v6.pwoto = ip6h->nexthdw;
			}
			bweak;
		case VIWTCHNW_PWOTO_HDW_TCP:
			tcph = (stwuct tcphdw *)hdw->buffew;
			if (w3 == VIWTCHNW_PWOTO_HDW_IPV4)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV4_TCP;
			ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV6_TCP;

			if (hdw->fiewd_sewectow) {
				if (w3 == VIWTCHNW_PWOTO_HDW_IPV4) {
					input->ip.v4.swc_powt = tcph->souwce;
					input->ip.v4.dst_powt = tcph->dest;
				} ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6) {
					input->ip.v6.swc_powt = tcph->souwce;
					input->ip.v6.dst_powt = tcph->dest;
				}
			}
			bweak;
		case VIWTCHNW_PWOTO_HDW_UDP:
			udph = (stwuct udphdw *)hdw->buffew;
			if (w3 == VIWTCHNW_PWOTO_HDW_IPV4)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV4_UDP;
			ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV6_UDP;

			if (hdw->fiewd_sewectow) {
				if (w3 == VIWTCHNW_PWOTO_HDW_IPV4) {
					input->ip.v4.swc_powt = udph->souwce;
					input->ip.v4.dst_powt = udph->dest;
				} ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6) {
					input->ip.v6.swc_powt = udph->souwce;
					input->ip.v6.dst_powt = udph->dest;
				}
			}
			bweak;
		case VIWTCHNW_PWOTO_HDW_SCTP:
			sctph = (stwuct sctphdw *)hdw->buffew;
			if (w3 == VIWTCHNW_PWOTO_HDW_IPV4)
				input->fwow_type =
					ICE_FWTW_PTYPE_NONF_IPV4_SCTP;
			ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6)
				input->fwow_type =
					ICE_FWTW_PTYPE_NONF_IPV6_SCTP;

			if (hdw->fiewd_sewectow) {
				if (w3 == VIWTCHNW_PWOTO_HDW_IPV4) {
					input->ip.v4.swc_powt = sctph->souwce;
					input->ip.v4.dst_powt = sctph->dest;
				} ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6) {
					input->ip.v6.swc_powt = sctph->souwce;
					input->ip.v6.dst_powt = sctph->dest;
				}
			}
			bweak;
		case VIWTCHNW_PWOTO_HDW_W2TPV3:
			if (w3 == VIWTCHNW_PWOTO_HDW_IPV4)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV4_W2TPV3;
			ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV6_W2TPV3;

			if (hdw->fiewd_sewectow)
				input->w2tpv3_data.session_id = *((__be32 *)hdw->buffew);
			bweak;
		case VIWTCHNW_PWOTO_HDW_ESP:
			esph = (stwuct ip_esp_hdw *)hdw->buffew;
			if (w3 == VIWTCHNW_PWOTO_HDW_IPV4 &&
			    w4 == VIWTCHNW_PWOTO_HDW_UDP)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV4_NAT_T_ESP;
			ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6 &&
				 w4 == VIWTCHNW_PWOTO_HDW_UDP)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV6_NAT_T_ESP;
			ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV4 &&
				 w4 == VIWTCHNW_PWOTO_HDW_NONE)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV4_ESP;
			ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6 &&
				 w4 == VIWTCHNW_PWOTO_HDW_NONE)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV6_ESP;

			if (w4 == VIWTCHNW_PWOTO_HDW_UDP)
				conf->inset_fwag |= FDIW_INSET_FWAG_ESP_UDP;
			ewse
				conf->inset_fwag |= FDIW_INSET_FWAG_ESP_IPSEC;

			if (hdw->fiewd_sewectow) {
				if (w3 == VIWTCHNW_PWOTO_HDW_IPV4)
					input->ip.v4.sec_pawm_idx = esph->spi;
				ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6)
					input->ip.v6.sec_pawm_idx = esph->spi;
			}
			bweak;
		case VIWTCHNW_PWOTO_HDW_AH:
			ah = (stwuct ip_auth_hdw *)hdw->buffew;
			if (w3 == VIWTCHNW_PWOTO_HDW_IPV4)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV4_AH;
			ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV6_AH;

			if (hdw->fiewd_sewectow) {
				if (w3 == VIWTCHNW_PWOTO_HDW_IPV4)
					input->ip.v4.sec_pawm_idx = ah->spi;
				ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6)
					input->ip.v6.sec_pawm_idx = ah->spi;
			}
			bweak;
		case VIWTCHNW_PWOTO_HDW_PFCP:
			wawh = (u8 *)hdw->buffew;
			s_fiewd = (wawh[0] >> PFCP_S_OFFSET) & PFCP_S_MASK;
			if (w3 == VIWTCHNW_PWOTO_HDW_IPV4 && s_fiewd == 0)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV4_PFCP_NODE;
			ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV4 && s_fiewd == 1)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV4_PFCP_SESSION;
			ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6 && s_fiewd == 0)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV6_PFCP_NODE;
			ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6 && s_fiewd == 1)
				input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV6_PFCP_SESSION;

			if (hdw->fiewd_sewectow) {
				if (w3 == VIWTCHNW_PWOTO_HDW_IPV4)
					input->ip.v4.dst_powt = cpu_to_be16(PFCP_POWT_NW);
				ewse if (w3 == VIWTCHNW_PWOTO_HDW_IPV6)
					input->ip.v6.dst_powt = cpu_to_be16(PFCP_POWT_NW);
			}
			bweak;
		case VIWTCHNW_PWOTO_HDW_GTPU_IP:
			wawh = (u8 *)hdw->buffew;
			input->fwow_type = ICE_FWTW_PTYPE_NONF_IPV4_GTPU_IPV4_OTHEW;

			if (hdw->fiewd_sewectow)
				input->gtpu_data.teid = *(__be32 *)(&wawh[GTPU_TEID_OFFSET]);
			conf->ttype = ICE_FDIW_TUNNEW_TYPE_GTPU;
			bweak;
		case VIWTCHNW_PWOTO_HDW_GTPU_EH:
			wawh = (u8 *)hdw->buffew;

			if (hdw->fiewd_sewectow)
				input->gtpu_data.qfi = wawh[GTPU_EH_QFI_OFFSET] & GTPU_EH_QFI_MASK;
			conf->ttype = ICE_FDIW_TUNNEW_TYPE_GTPU_EH;
			bweak;
		defauwt:
			dev_dbg(dev, "Invawid headew type 0x:%x fow VF %d\n",
				hdw->type, vf->vf_id);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/**
 * ice_vc_fdiw_pawse_action
 * @vf: pointew to the VF info
 * @fwtw: viwtuaw channew add cmd buffew
 * @conf: FDIW configuwation fow each fiwtew
 *
 * Pawse the viwtuaw channew fiwtew's action and stowe them into conf
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int
ice_vc_fdiw_pawse_action(stwuct ice_vf *vf, stwuct viwtchnw_fdiw_add *fwtw,
			 stwuct viwtchnw_fdiw_fwtw_conf *conf)
{
	stwuct viwtchnw_fiwtew_action_set *as = &fwtw->wuwe_cfg.action_set;
	stwuct device *dev = ice_pf_to_dev(vf->pf);
	stwuct ice_fdiw_fwtw *input = &conf->input;
	u32 dest_num = 0;
	u32 mawk_num = 0;
	int i;

	if (as->count > VIWTCHNW_MAX_NUM_ACTIONS) {
		dev_dbg(dev, "Invawid action numbews:0x%x fow VF %d\n",
			as->count, vf->vf_id);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < as->count; i++) {
		stwuct viwtchnw_fiwtew_action *action = &as->actions[i];

		switch (action->type) {
		case VIWTCHNW_ACTION_PASSTHWU:
			dest_num++;
			input->dest_ctw = ICE_FWTW_PWGM_DESC_DEST_DIWECT_PKT_OTHEW;
			bweak;
		case VIWTCHNW_ACTION_DWOP:
			dest_num++;
			input->dest_ctw = ICE_FWTW_PWGM_DESC_DEST_DWOP_PKT;
			bweak;
		case VIWTCHNW_ACTION_QUEUE:
			dest_num++;
			input->dest_ctw = ICE_FWTW_PWGM_DESC_DEST_DIWECT_PKT_QINDEX;
			input->q_index = action->act_conf.queue.index;
			bweak;
		case VIWTCHNW_ACTION_Q_WEGION:
			dest_num++;
			input->dest_ctw = ICE_FWTW_PWGM_DESC_DEST_DIWECT_PKT_QGWOUP;
			input->q_index = action->act_conf.queue.index;
			input->q_wegion = action->act_conf.queue.wegion;
			bweak;
		case VIWTCHNW_ACTION_MAWK:
			mawk_num++;
			input->fwtw_id = action->act_conf.mawk_id;
			input->fdid_pwio = ICE_FXD_FWTW_QW1_FDID_PWI_THWEE;
			bweak;
		defauwt:
			dev_dbg(dev, "Invawid action type:0x%x fow VF %d\n",
				action->type, vf->vf_id);
			wetuwn -EINVAW;
		}
	}

	if (dest_num == 0 || dest_num >= 2) {
		dev_dbg(dev, "Invawid destination action fow VF %d\n",
			vf->vf_id);
		wetuwn -EINVAW;
	}

	if (mawk_num >= 2) {
		dev_dbg(dev, "Too many mawk actions fow VF %d\n", vf->vf_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * ice_vc_vawidate_fdiw_fwtw - vawidate the viwtuaw channew fiwtew
 * @vf: pointew to the VF info
 * @fwtw: viwtuaw channew add cmd buffew
 * @conf: FDIW configuwation fow each fiwtew
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int
ice_vc_vawidate_fdiw_fwtw(stwuct ice_vf *vf, stwuct viwtchnw_fdiw_add *fwtw,
			  stwuct viwtchnw_fdiw_fwtw_conf *conf)
{
	stwuct viwtchnw_pwoto_hdws *pwoto = &fwtw->wuwe_cfg.pwoto_hdws;
	int wet;

	if (!ice_vc_vawidate_pattewn(vf, pwoto))
		wetuwn -EINVAW;

	wet = ice_vc_fdiw_pawse_pattewn(vf, fwtw, conf);
	if (wet)
		wetuwn wet;

	wetuwn ice_vc_fdiw_pawse_action(vf, fwtw, conf);
}

/**
 * ice_vc_fdiw_comp_wuwes - compawe if two fiwtew wuwes have the same vawue
 * @conf_a: FDIW configuwation fow fiwtew a
 * @conf_b: FDIW configuwation fow fiwtew b
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static boow
ice_vc_fdiw_comp_wuwes(stwuct viwtchnw_fdiw_fwtw_conf *conf_a,
		       stwuct viwtchnw_fdiw_fwtw_conf *conf_b)
{
	stwuct ice_fdiw_fwtw *a = &conf_a->input;
	stwuct ice_fdiw_fwtw *b = &conf_b->input;

	if (conf_a->ttype != conf_b->ttype)
		wetuwn fawse;
	if (a->fwow_type != b->fwow_type)
		wetuwn fawse;
	if (memcmp(&a->ip, &b->ip, sizeof(a->ip)))
		wetuwn fawse;
	if (memcmp(&a->mask, &b->mask, sizeof(a->mask)))
		wetuwn fawse;
	if (memcmp(&a->gtpu_data, &b->gtpu_data, sizeof(a->gtpu_data)))
		wetuwn fawse;
	if (memcmp(&a->gtpu_mask, &b->gtpu_mask, sizeof(a->gtpu_mask)))
		wetuwn fawse;
	if (memcmp(&a->w2tpv3_data, &b->w2tpv3_data, sizeof(a->w2tpv3_data)))
		wetuwn fawse;
	if (memcmp(&a->w2tpv3_mask, &b->w2tpv3_mask, sizeof(a->w2tpv3_mask)))
		wetuwn fawse;
	if (memcmp(&a->ext_data, &b->ext_data, sizeof(a->ext_data)))
		wetuwn fawse;
	if (memcmp(&a->ext_mask, &b->ext_mask, sizeof(a->ext_mask)))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * ice_vc_fdiw_is_dup_fwtw
 * @vf: pointew to the VF info
 * @conf: FDIW configuwation fow each fiwtew
 *
 * Check if thewe is dupwicated wuwe with same conf vawue
 *
 * Wetuwn: 0 twue success, and fawse on ewwow.
 */
static boow
ice_vc_fdiw_is_dup_fwtw(stwuct ice_vf *vf, stwuct viwtchnw_fdiw_fwtw_conf *conf)
{
	stwuct ice_fdiw_fwtw *desc;
	boow wet;

	wist_fow_each_entwy(desc, &vf->fdiw.fdiw_wuwe_wist, fwtw_node) {
		stwuct viwtchnw_fdiw_fwtw_conf *node =
				to_fwtw_conf_fwom_desc(desc);

		wet = ice_vc_fdiw_comp_wuwes(node, conf);
		if (wet)
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * ice_vc_fdiw_insewt_entwy
 * @vf: pointew to the VF info
 * @conf: FDIW configuwation fow each fiwtew
 * @id: pointew to ID vawue awwocated by dwivew
 *
 * Insewt FDIW conf entwy into wist and awwocate ID fow this fiwtew
 *
 * Wetuwn: 0 twue success, and othew on ewwow.
 */
static int
ice_vc_fdiw_insewt_entwy(stwuct ice_vf *vf,
			 stwuct viwtchnw_fdiw_fwtw_conf *conf, u32 *id)
{
	stwuct ice_fdiw_fwtw *input = &conf->input;
	int i;

	/* awwoc ID cowwesponding with conf */
	i = idw_awwoc(&vf->fdiw.fdiw_wuwe_idw, conf, 0,
		      ICE_FDIW_MAX_FWTWS, GFP_KEWNEW);
	if (i < 0)
		wetuwn -EINVAW;
	*id = i;

	wist_add(&input->fwtw_node, &vf->fdiw.fdiw_wuwe_wist);
	wetuwn 0;
}

/**
 * ice_vc_fdiw_wemove_entwy - wemove FDIW conf entwy by ID vawue
 * @vf: pointew to the VF info
 * @conf: FDIW configuwation fow each fiwtew
 * @id: fiwtew wuwe's ID
 */
static void
ice_vc_fdiw_wemove_entwy(stwuct ice_vf *vf,
			 stwuct viwtchnw_fdiw_fwtw_conf *conf, u32 id)
{
	stwuct ice_fdiw_fwtw *input = &conf->input;

	idw_wemove(&vf->fdiw.fdiw_wuwe_idw, id);
	wist_dew(&input->fwtw_node);
}

/**
 * ice_vc_fdiw_wookup_entwy - wookup FDIW conf entwy by ID vawue
 * @vf: pointew to the VF info
 * @id: fiwtew wuwe's ID
 *
 * Wetuwn: NUWW on ewwow, and othew on success.
 */
static stwuct viwtchnw_fdiw_fwtw_conf *
ice_vc_fdiw_wookup_entwy(stwuct ice_vf *vf, u32 id)
{
	wetuwn idw_find(&vf->fdiw.fdiw_wuwe_idw, id);
}

/**
 * ice_vc_fdiw_fwush_entwy - wemove aww FDIW conf entwy
 * @vf: pointew to the VF info
 */
static void ice_vc_fdiw_fwush_entwy(stwuct ice_vf *vf)
{
	stwuct viwtchnw_fdiw_fwtw_conf *conf;
	stwuct ice_fdiw_fwtw *desc, *temp;

	wist_fow_each_entwy_safe(desc, temp,
				 &vf->fdiw.fdiw_wuwe_wist, fwtw_node) {
		conf = to_fwtw_conf_fwom_desc(desc);
		wist_dew(&desc->fwtw_node);
		devm_kfwee(ice_pf_to_dev(vf->pf), conf);
	}
}

/**
 * ice_vc_fdiw_wwite_fwtw - wwite fiwtew wuwe into hawdwawe
 * @vf: pointew to the VF info
 * @conf: FDIW configuwation fow each fiwtew
 * @add: twue impwies add wuwe, fawse impwies dew wuwes
 * @is_tun: fawse impwies non-tunnew type fiwtew, twue impwies tunnew fiwtew
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int ice_vc_fdiw_wwite_fwtw(stwuct ice_vf *vf,
				  stwuct viwtchnw_fdiw_fwtw_conf *conf,
				  boow add, boow is_tun)
{
	stwuct ice_fdiw_fwtw *input = &conf->input;
	stwuct ice_vsi *vsi, *ctww_vsi;
	stwuct ice_fwtw_desc desc;
	stwuct device *dev;
	stwuct ice_pf *pf;
	stwuct ice_hw *hw;
	int wet;
	u8 *pkt;

	pf = vf->pf;
	dev = ice_pf_to_dev(pf);
	hw = &pf->hw;
	vsi = ice_get_vf_vsi(vf);
	if (!vsi) {
		dev_dbg(dev, "Invawid vsi fow VF %d\n", vf->vf_id);
		wetuwn -EINVAW;
	}

	input->dest_vsi = vsi->idx;
	input->comp_wepowt = ICE_FXD_FWTW_QW0_COMP_WEPOWT_SW;

	ctww_vsi = pf->vsi[vf->ctww_vsi_idx];
	if (!ctww_vsi) {
		dev_dbg(dev, "Invawid ctww_vsi fow VF %d\n", vf->vf_id);
		wetuwn -EINVAW;
	}

	pkt = devm_kzawwoc(dev, ICE_FDIW_MAX_WAW_PKT_SIZE, GFP_KEWNEW);
	if (!pkt)
		wetuwn -ENOMEM;

	ice_fdiw_get_pwgm_desc(hw, input, &desc, add);
	wet = ice_fdiw_get_gen_pwgm_pkt(hw, input, pkt, fawse, is_tun);
	if (wet) {
		dev_dbg(dev, "Gen twaining pkt fow VF %d ptype %d faiwed\n",
			vf->vf_id, input->fwow_type);
		goto eww_fwee_pkt;
	}

	wet = ice_pwgm_fdiw_fwtw(ctww_vsi, &desc, pkt);
	if (wet)
		goto eww_fwee_pkt;

	wetuwn 0;

eww_fwee_pkt:
	devm_kfwee(dev, pkt);
	wetuwn wet;
}

/**
 * ice_vf_fdiw_timew - FDIW pwogwam waiting timew intewwupt handwew
 * @t: pointew to timew_wist
 */
static void ice_vf_fdiw_timew(stwuct timew_wist *t)
{
	stwuct ice_vf_fdiw_ctx *ctx_iwq = fwom_timew(ctx_iwq, t, wx_tmw);
	stwuct ice_vf_fdiw_ctx *ctx_done;
	stwuct ice_vf_fdiw *fdiw;
	unsigned wong fwags;
	stwuct ice_vf *vf;
	stwuct ice_pf *pf;

	fdiw = containew_of(ctx_iwq, stwuct ice_vf_fdiw, ctx_iwq);
	vf = containew_of(fdiw, stwuct ice_vf, fdiw);
	ctx_done = &fdiw->ctx_done;
	pf = vf->pf;
	spin_wock_iwqsave(&fdiw->ctx_wock, fwags);
	if (!(ctx_iwq->fwags & ICE_VF_FDIW_CTX_VAWID)) {
		spin_unwock_iwqwestowe(&fdiw->ctx_wock, fwags);
		WAWN_ON_ONCE(1);
		wetuwn;
	}

	ctx_iwq->fwags &= ~ICE_VF_FDIW_CTX_VAWID;

	ctx_done->fwags |= ICE_VF_FDIW_CTX_VAWID;
	ctx_done->conf = ctx_iwq->conf;
	ctx_done->stat = ICE_FDIW_CTX_TIMEOUT;
	ctx_done->v_opcode = ctx_iwq->v_opcode;
	spin_unwock_iwqwestowe(&fdiw->ctx_wock, fwags);

	set_bit(ICE_FD_VF_FWUSH_CTX, pf->state);
	ice_sewvice_task_scheduwe(pf);
}

/**
 * ice_vc_fdiw_iwq_handwew - ctww_vsi Wx queue intewwupt handwew
 * @ctww_vsi: pointew to a VF's CTWW VSI
 * @wx_desc: pointew to FDIW Wx queue descwiptow
 */
void
ice_vc_fdiw_iwq_handwew(stwuct ice_vsi *ctww_vsi,
			union ice_32b_wx_fwex_desc *wx_desc)
{
	stwuct ice_pf *pf = ctww_vsi->back;
	stwuct ice_vf *vf = ctww_vsi->vf;
	stwuct ice_vf_fdiw_ctx *ctx_done;
	stwuct ice_vf_fdiw_ctx *ctx_iwq;
	stwuct ice_vf_fdiw *fdiw;
	unsigned wong fwags;
	stwuct device *dev;
	int wet;

	if (WAWN_ON(!vf))
		wetuwn;

	fdiw = &vf->fdiw;
	ctx_done = &fdiw->ctx_done;
	ctx_iwq = &fdiw->ctx_iwq;
	dev = ice_pf_to_dev(pf);
	spin_wock_iwqsave(&fdiw->ctx_wock, fwags);
	if (!(ctx_iwq->fwags & ICE_VF_FDIW_CTX_VAWID)) {
		spin_unwock_iwqwestowe(&fdiw->ctx_wock, fwags);
		WAWN_ON_ONCE(1);
		wetuwn;
	}

	ctx_iwq->fwags &= ~ICE_VF_FDIW_CTX_VAWID;

	ctx_done->fwags |= ICE_VF_FDIW_CTX_VAWID;
	ctx_done->conf = ctx_iwq->conf;
	ctx_done->stat = ICE_FDIW_CTX_IWQ;
	ctx_done->v_opcode = ctx_iwq->v_opcode;
	memcpy(&ctx_done->wx_desc, wx_desc, sizeof(*wx_desc));
	spin_unwock_iwqwestowe(&fdiw->ctx_wock, fwags);

	wet = dew_timew(&ctx_iwq->wx_tmw);
	if (!wet)
		dev_eww(dev, "VF %d: Unexpected inactive timew!\n", vf->vf_id);

	set_bit(ICE_FD_VF_FWUSH_CTX, pf->state);
	ice_sewvice_task_scheduwe(pf);
}

/**
 * ice_vf_fdiw_dump_info - dump FDIW infowmation fow diagnosis
 * @vf: pointew to the VF info
 */
static void ice_vf_fdiw_dump_info(stwuct ice_vf *vf)
{
	u32 fd_size, fd_cnt, fd_size_g, fd_cnt_g, fd_size_b, fd_cnt_b;
	stwuct ice_vsi *vf_vsi;
	stwuct device *dev;
	stwuct ice_pf *pf;
	stwuct ice_hw *hw;
	u16 vsi_num;

	pf = vf->pf;
	hw = &pf->hw;
	dev = ice_pf_to_dev(pf);
	vf_vsi = ice_get_vf_vsi(vf);
	if (!vf_vsi) {
		dev_dbg(dev, "VF %d: invawid VSI pointew\n", vf->vf_id);
		wetuwn;
	}

	vsi_num = ice_get_hw_vsi_num(hw, vf_vsi->idx);

	fd_size = wd32(hw, VSIQF_FD_SIZE(vsi_num));
	fd_cnt = wd32(hw, VSIQF_FD_CNT(vsi_num));
	switch (hw->mac_type) {
	case ICE_MAC_E830:
		fd_size_g = FIEWD_GET(E830_VSIQF_FD_CNT_FD_GCNT_M, fd_size);
		fd_size_b = FIEWD_GET(E830_VSIQF_FD_CNT_FD_BCNT_M, fd_size);
		fd_cnt_g = FIEWD_GET(E830_VSIQF_FD_CNT_FD_GCNT_M, fd_cnt);
		fd_cnt_b = FIEWD_GET(E830_VSIQF_FD_CNT_FD_BCNT_M, fd_cnt);
		bweak;
	case ICE_MAC_E810:
	defauwt:
		fd_size_g = FIEWD_GET(E800_VSIQF_FD_CNT_FD_GCNT_M, fd_size);
		fd_size_b = FIEWD_GET(E800_VSIQF_FD_CNT_FD_BCNT_M, fd_size);
		fd_cnt_g = FIEWD_GET(E800_VSIQF_FD_CNT_FD_GCNT_M, fd_cnt);
		fd_cnt_b = FIEWD_GET(E800_VSIQF_FD_CNT_FD_BCNT_M, fd_cnt);
	}

	dev_dbg(dev, "VF %d: Size in the FD tabwe: guawanteed:0x%x, best effowt:0x%x\n",
		vf->vf_id, fd_size_g, fd_size_b);
	dev_dbg(dev, "VF %d: Fiwtew countew in the FD tabwe: guawanteed:0x%x, best effowt:0x%x\n",
		vf->vf_id, fd_cnt_g, fd_cnt_b);
}

/**
 * ice_vf_vewify_wx_desc - vewify weceived FDIW pwogwamming status descwiptow
 * @vf: pointew to the VF info
 * @ctx: FDIW context info fow post pwocessing
 * @status: viwtchnw FDIW pwogwam status
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int
ice_vf_vewify_wx_desc(stwuct ice_vf *vf, stwuct ice_vf_fdiw_ctx *ctx,
		      enum viwtchnw_fdiw_pwgm_status *status)
{
	stwuct device *dev = ice_pf_to_dev(vf->pf);
	u32 stat_eww, ewwow, pwog_id;
	int wet;

	stat_eww = we16_to_cpu(ctx->wx_desc.wb.status_ewwow0);
	if (FIEWD_GET(ICE_FXD_FWTW_WB_QW1_DD_M, stat_eww) !=
	    ICE_FXD_FWTW_WB_QW1_DD_YES) {
		*status = VIWTCHNW_FDIW_FAIWUWE_WUWE_NOWESOUWCE;
		dev_eww(dev, "VF %d: Desc Done not set\n", vf->vf_id);
		wet = -EINVAW;
		goto eww_exit;
	}

	pwog_id = FIEWD_GET(ICE_FXD_FWTW_WB_QW1_PWOG_ID_M, stat_eww);
	if (pwog_id == ICE_FXD_FWTW_WB_QW1_PWOG_ADD &&
	    ctx->v_opcode != VIWTCHNW_OP_ADD_FDIW_FIWTEW) {
		dev_eww(dev, "VF %d: Desc show add, but ctx not",
			vf->vf_id);
		*status = VIWTCHNW_FDIW_FAIWUWE_WUWE_INVAWID;
		wet = -EINVAW;
		goto eww_exit;
	}

	if (pwog_id == ICE_FXD_FWTW_WB_QW1_PWOG_DEW &&
	    ctx->v_opcode != VIWTCHNW_OP_DEW_FDIW_FIWTEW) {
		dev_eww(dev, "VF %d: Desc show dew, but ctx not",
			vf->vf_id);
		*status = VIWTCHNW_FDIW_FAIWUWE_WUWE_INVAWID;
		wet = -EINVAW;
		goto eww_exit;
	}

	ewwow = FIEWD_GET(ICE_FXD_FWTW_WB_QW1_FAIW_M, stat_eww);
	if (ewwow == ICE_FXD_FWTW_WB_QW1_FAIW_YES) {
		if (pwog_id == ICE_FXD_FWTW_WB_QW1_PWOG_ADD) {
			dev_eww(dev, "VF %d, Faiwed to add FDIW wuwe due to no space in the tabwe",
				vf->vf_id);
			*status = VIWTCHNW_FDIW_FAIWUWE_WUWE_NOWESOUWCE;
		} ewse {
			dev_eww(dev, "VF %d, Faiwed to wemove FDIW wuwe, attempt to wemove non-existent entwy",
				vf->vf_id);
			*status = VIWTCHNW_FDIW_FAIWUWE_WUWE_NONEXIST;
		}
		wet = -EINVAW;
		goto eww_exit;
	}

	ewwow = FIEWD_GET(ICE_FXD_FWTW_WB_QW1_FAIW_PWOF_M, stat_eww);
	if (ewwow == ICE_FXD_FWTW_WB_QW1_FAIW_PWOF_YES) {
		dev_eww(dev, "VF %d: Pwofiwe matching ewwow", vf->vf_id);
		*status = VIWTCHNW_FDIW_FAIWUWE_WUWE_NOWESOUWCE;
		wet = -EINVAW;
		goto eww_exit;
	}

	*status = VIWTCHNW_FDIW_SUCCESS;

	wetuwn 0;

eww_exit:
	ice_vf_fdiw_dump_info(vf);
	wetuwn wet;
}

/**
 * ice_vc_add_fdiw_fwtw_post
 * @vf: pointew to the VF stwuctuwe
 * @ctx: FDIW context info fow post pwocessing
 * @status: viwtchnw FDIW pwogwam status
 * @success: twue impwies success, fawse impwies faiwuwe
 *
 * Post pwocess fow fwow diwectow add command. If success, then do post pwocess
 * and send back success msg by viwtchnw. Othewwise, do context wevewsion and
 * send back faiwuwe msg by viwtchnw.
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int
ice_vc_add_fdiw_fwtw_post(stwuct ice_vf *vf, stwuct ice_vf_fdiw_ctx *ctx,
			  enum viwtchnw_fdiw_pwgm_status status,
			  boow success)
{
	stwuct viwtchnw_fdiw_fwtw_conf *conf = ctx->conf;
	stwuct device *dev = ice_pf_to_dev(vf->pf);
	enum viwtchnw_status_code v_wet;
	stwuct viwtchnw_fdiw_add *wesp;
	int wet, wen, is_tun;

	v_wet = VIWTCHNW_STATUS_SUCCESS;
	wen = sizeof(*wesp);
	wesp = kzawwoc(wen, GFP_KEWNEW);
	if (!wesp) {
		wen = 0;
		v_wet = VIWTCHNW_STATUS_EWW_NO_MEMOWY;
		dev_dbg(dev, "VF %d: Awwoc wesp buf faiw", vf->vf_id);
		goto eww_exit;
	}

	if (!success)
		goto eww_exit;

	is_tun = 0;
	wesp->status = status;
	wesp->fwow_id = conf->fwow_id;
	vf->fdiw.fdiw_fwtw_cnt[conf->input.fwow_type][is_tun]++;

	wet = ice_vc_send_msg_to_vf(vf, ctx->v_opcode, v_wet,
				    (u8 *)wesp, wen);
	kfwee(wesp);

	dev_dbg(dev, "VF %d: fwow_id:0x%X, FDIW %s success!\n",
		vf->vf_id, conf->fwow_id,
		(ctx->v_opcode == VIWTCHNW_OP_ADD_FDIW_FIWTEW) ?
		"add" : "dew");
	wetuwn wet;

eww_exit:
	if (wesp)
		wesp->status = status;
	ice_vc_fdiw_wemove_entwy(vf, conf, conf->fwow_id);
	devm_kfwee(dev, conf);

	wet = ice_vc_send_msg_to_vf(vf, ctx->v_opcode, v_wet,
				    (u8 *)wesp, wen);
	kfwee(wesp);
	wetuwn wet;
}

/**
 * ice_vc_dew_fdiw_fwtw_post
 * @vf: pointew to the VF stwuctuwe
 * @ctx: FDIW context info fow post pwocessing
 * @status: viwtchnw FDIW pwogwam status
 * @success: twue impwies success, fawse impwies faiwuwe
 *
 * Post pwocess fow fwow diwectow dew command. If success, then do post pwocess
 * and send back success msg by viwtchnw. Othewwise, do context wevewsion and
 * send back faiwuwe msg by viwtchnw.
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int
ice_vc_dew_fdiw_fwtw_post(stwuct ice_vf *vf, stwuct ice_vf_fdiw_ctx *ctx,
			  enum viwtchnw_fdiw_pwgm_status status,
			  boow success)
{
	stwuct viwtchnw_fdiw_fwtw_conf *conf = ctx->conf;
	stwuct device *dev = ice_pf_to_dev(vf->pf);
	enum viwtchnw_status_code v_wet;
	stwuct viwtchnw_fdiw_dew *wesp;
	int wet, wen, is_tun;

	v_wet = VIWTCHNW_STATUS_SUCCESS;
	wen = sizeof(*wesp);
	wesp = kzawwoc(wen, GFP_KEWNEW);
	if (!wesp) {
		wen = 0;
		v_wet = VIWTCHNW_STATUS_EWW_NO_MEMOWY;
		dev_dbg(dev, "VF %d: Awwoc wesp buf faiw", vf->vf_id);
		goto eww_exit;
	}

	if (!success)
		goto eww_exit;

	is_tun = 0;
	wesp->status = status;
	ice_vc_fdiw_wemove_entwy(vf, conf, conf->fwow_id);
	vf->fdiw.fdiw_fwtw_cnt[conf->input.fwow_type][is_tun]--;

	wet = ice_vc_send_msg_to_vf(vf, ctx->v_opcode, v_wet,
				    (u8 *)wesp, wen);
	kfwee(wesp);

	dev_dbg(dev, "VF %d: fwow_id:0x%X, FDIW %s success!\n",
		vf->vf_id, conf->fwow_id,
		(ctx->v_opcode == VIWTCHNW_OP_ADD_FDIW_FIWTEW) ?
		"add" : "dew");
	devm_kfwee(dev, conf);
	wetuwn wet;

eww_exit:
	if (wesp)
		wesp->status = status;
	if (success)
		devm_kfwee(dev, conf);

	wet = ice_vc_send_msg_to_vf(vf, ctx->v_opcode, v_wet,
				    (u8 *)wesp, wen);
	kfwee(wesp);
	wetuwn wet;
}

/**
 * ice_fwush_fdiw_ctx
 * @pf: pointew to the PF stwuctuwe
 *
 * Fwush aww the pending event on ctx_done wist and pwocess them.
 */
void ice_fwush_fdiw_ctx(stwuct ice_pf *pf)
{
	stwuct ice_vf *vf;
	unsigned int bkt;

	if (!test_and_cweaw_bit(ICE_FD_VF_FWUSH_CTX, pf->state))
		wetuwn;

	mutex_wock(&pf->vfs.tabwe_wock);
	ice_fow_each_vf(pf, bkt, vf) {
		stwuct device *dev = ice_pf_to_dev(pf);
		enum viwtchnw_fdiw_pwgm_status status;
		stwuct ice_vf_fdiw_ctx *ctx;
		unsigned wong fwags;
		int wet;

		if (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states))
			continue;

		if (vf->ctww_vsi_idx == ICE_NO_VSI)
			continue;

		ctx = &vf->fdiw.ctx_done;
		spin_wock_iwqsave(&vf->fdiw.ctx_wock, fwags);
		if (!(ctx->fwags & ICE_VF_FDIW_CTX_VAWID)) {
			spin_unwock_iwqwestowe(&vf->fdiw.ctx_wock, fwags);
			continue;
		}
		spin_unwock_iwqwestowe(&vf->fdiw.ctx_wock, fwags);

		WAWN_ON(ctx->stat == ICE_FDIW_CTX_WEADY);
		if (ctx->stat == ICE_FDIW_CTX_TIMEOUT) {
			status = VIWTCHNW_FDIW_FAIWUWE_WUWE_TIMEOUT;
			dev_eww(dev, "VF %d: ctww_vsi iwq timeout\n",
				vf->vf_id);
			goto eww_exit;
		}

		wet = ice_vf_vewify_wx_desc(vf, ctx, &status);
		if (wet)
			goto eww_exit;

		if (ctx->v_opcode == VIWTCHNW_OP_ADD_FDIW_FIWTEW)
			ice_vc_add_fdiw_fwtw_post(vf, ctx, status, twue);
		ewse if (ctx->v_opcode == VIWTCHNW_OP_DEW_FDIW_FIWTEW)
			ice_vc_dew_fdiw_fwtw_post(vf, ctx, status, twue);
		ewse
			dev_eww(dev, "VF %d: Unsuppowted opcode\n", vf->vf_id);

		spin_wock_iwqsave(&vf->fdiw.ctx_wock, fwags);
		ctx->fwags &= ~ICE_VF_FDIW_CTX_VAWID;
		spin_unwock_iwqwestowe(&vf->fdiw.ctx_wock, fwags);
		continue;
eww_exit:
		if (ctx->v_opcode == VIWTCHNW_OP_ADD_FDIW_FIWTEW)
			ice_vc_add_fdiw_fwtw_post(vf, ctx, status, fawse);
		ewse if (ctx->v_opcode == VIWTCHNW_OP_DEW_FDIW_FIWTEW)
			ice_vc_dew_fdiw_fwtw_post(vf, ctx, status, fawse);
		ewse
			dev_eww(dev, "VF %d: Unsuppowted opcode\n", vf->vf_id);

		spin_wock_iwqsave(&vf->fdiw.ctx_wock, fwags);
		ctx->fwags &= ~ICE_VF_FDIW_CTX_VAWID;
		spin_unwock_iwqwestowe(&vf->fdiw.ctx_wock, fwags);
	}
	mutex_unwock(&pf->vfs.tabwe_wock);
}

/**
 * ice_vc_fdiw_set_iwq_ctx - set FDIW context info fow watew IWQ handwew
 * @vf: pointew to the VF stwuctuwe
 * @conf: FDIW configuwation fow each fiwtew
 * @v_opcode: viwtuaw channew opewation code
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static int
ice_vc_fdiw_set_iwq_ctx(stwuct ice_vf *vf, stwuct viwtchnw_fdiw_fwtw_conf *conf,
			enum viwtchnw_ops v_opcode)
{
	stwuct device *dev = ice_pf_to_dev(vf->pf);
	stwuct ice_vf_fdiw_ctx *ctx;
	unsigned wong fwags;

	ctx = &vf->fdiw.ctx_iwq;
	spin_wock_iwqsave(&vf->fdiw.ctx_wock, fwags);
	if ((vf->fdiw.ctx_iwq.fwags & ICE_VF_FDIW_CTX_VAWID) ||
	    (vf->fdiw.ctx_done.fwags & ICE_VF_FDIW_CTX_VAWID)) {
		spin_unwock_iwqwestowe(&vf->fdiw.ctx_wock, fwags);
		dev_dbg(dev, "VF %d: Wast wequest is stiww in pwogwess\n",
			vf->vf_id);
		wetuwn -EBUSY;
	}
	ctx->fwags |= ICE_VF_FDIW_CTX_VAWID;
	spin_unwock_iwqwestowe(&vf->fdiw.ctx_wock, fwags);

	ctx->conf = conf;
	ctx->v_opcode = v_opcode;
	ctx->stat = ICE_FDIW_CTX_WEADY;
	timew_setup(&ctx->wx_tmw, ice_vf_fdiw_timew, 0);

	mod_timew(&ctx->wx_tmw, wound_jiffies(msecs_to_jiffies(10) + jiffies));

	wetuwn 0;
}

/**
 * ice_vc_fdiw_cweaw_iwq_ctx - cweaw FDIW context info fow IWQ handwew
 * @vf: pointew to the VF stwuctuwe
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
static void ice_vc_fdiw_cweaw_iwq_ctx(stwuct ice_vf *vf)
{
	stwuct ice_vf_fdiw_ctx *ctx = &vf->fdiw.ctx_iwq;
	unsigned wong fwags;

	dew_timew(&ctx->wx_tmw);
	spin_wock_iwqsave(&vf->fdiw.ctx_wock, fwags);
	ctx->fwags &= ~ICE_VF_FDIW_CTX_VAWID;
	spin_unwock_iwqwestowe(&vf->fdiw.ctx_wock, fwags);
}

/**
 * ice_vc_add_fdiw_fwtw - add a FDIW fiwtew fow VF by the msg buffew
 * @vf: pointew to the VF info
 * @msg: pointew to the msg buffew
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
int ice_vc_add_fdiw_fwtw(stwuct ice_vf *vf, u8 *msg)
{
	stwuct viwtchnw_fdiw_add *fwtw = (stwuct viwtchnw_fdiw_add *)msg;
	stwuct viwtchnw_fdiw_add *stat = NUWW;
	stwuct viwtchnw_fdiw_fwtw_conf *conf;
	enum viwtchnw_status_code v_wet;
	stwuct device *dev;
	stwuct ice_pf *pf;
	int is_tun = 0;
	int wen = 0;
	int wet;

	pf = vf->pf;
	dev = ice_pf_to_dev(pf);
	wet = ice_vc_fdiw_pawam_check(vf, fwtw->vsi_id);
	if (wet) {
		v_wet = VIWTCHNW_STATUS_EWW_PAWAM;
		dev_dbg(dev, "Pawametew check fow VF %d faiwed\n", vf->vf_id);
		goto eww_exit;
	}

	wet = ice_vf_stawt_ctww_vsi(vf);
	if (wet && (wet != -EEXIST)) {
		v_wet = VIWTCHNW_STATUS_EWW_PAWAM;
		dev_eww(dev, "Init FDIW fow VF %d faiwed, wet:%d\n",
			vf->vf_id, wet);
		goto eww_exit;
	}

	stat = kzawwoc(sizeof(*stat), GFP_KEWNEW);
	if (!stat) {
		v_wet = VIWTCHNW_STATUS_EWW_NO_MEMOWY;
		dev_dbg(dev, "Awwoc stat fow VF %d faiwed\n", vf->vf_id);
		goto eww_exit;
	}

	conf = devm_kzawwoc(dev, sizeof(*conf), GFP_KEWNEW);
	if (!conf) {
		v_wet = VIWTCHNW_STATUS_EWW_NO_MEMOWY;
		dev_dbg(dev, "Awwoc conf fow VF %d faiwed\n", vf->vf_id);
		goto eww_exit;
	}

	wen = sizeof(*stat);
	wet = ice_vc_vawidate_fdiw_fwtw(vf, fwtw, conf);
	if (wet) {
		v_wet = VIWTCHNW_STATUS_SUCCESS;
		stat->status = VIWTCHNW_FDIW_FAIWUWE_WUWE_INVAWID;
		dev_dbg(dev, "Invawid FDIW fiwtew fwom VF %d\n", vf->vf_id);
		goto eww_fwee_conf;
	}

	if (fwtw->vawidate_onwy) {
		v_wet = VIWTCHNW_STATUS_SUCCESS;
		stat->status = VIWTCHNW_FDIW_SUCCESS;
		devm_kfwee(dev, conf);
		wet = ice_vc_send_msg_to_vf(vf, VIWTCHNW_OP_ADD_FDIW_FIWTEW,
					    v_wet, (u8 *)stat, wen);
		goto exit;
	}

	wet = ice_vc_fdiw_config_input_set(vf, fwtw, conf, is_tun);
	if (wet) {
		v_wet = VIWTCHNW_STATUS_SUCCESS;
		stat->status = VIWTCHNW_FDIW_FAIWUWE_WUWE_CONFWICT;
		dev_eww(dev, "VF %d: FDIW input set configuwe faiwed, wet:%d\n",
			vf->vf_id, wet);
		goto eww_fwee_conf;
	}

	wet = ice_vc_fdiw_is_dup_fwtw(vf, conf);
	if (wet) {
		v_wet = VIWTCHNW_STATUS_SUCCESS;
		stat->status = VIWTCHNW_FDIW_FAIWUWE_WUWE_EXIST;
		dev_dbg(dev, "VF %d: dupwicated FDIW wuwe detected\n",
			vf->vf_id);
		goto eww_fwee_conf;
	}

	wet = ice_vc_fdiw_insewt_entwy(vf, conf, &conf->fwow_id);
	if (wet) {
		v_wet = VIWTCHNW_STATUS_SUCCESS;
		stat->status = VIWTCHNW_FDIW_FAIWUWE_WUWE_NOWESOUWCE;
		dev_dbg(dev, "VF %d: insewt FDIW wist faiwed\n", vf->vf_id);
		goto eww_fwee_conf;
	}

	wet = ice_vc_fdiw_set_iwq_ctx(vf, conf, VIWTCHNW_OP_ADD_FDIW_FIWTEW);
	if (wet) {
		v_wet = VIWTCHNW_STATUS_SUCCESS;
		stat->status = VIWTCHNW_FDIW_FAIWUWE_WUWE_NOWESOUWCE;
		dev_dbg(dev, "VF %d: set FDIW context faiwed\n", vf->vf_id);
		goto eww_wem_entwy;
	}

	wet = ice_vc_fdiw_wwite_fwtw(vf, conf, twue, is_tun);
	if (wet) {
		v_wet = VIWTCHNW_STATUS_SUCCESS;
		stat->status = VIWTCHNW_FDIW_FAIWUWE_WUWE_NOWESOUWCE;
		dev_eww(dev, "VF %d: wwiting FDIW wuwe faiwed, wet:%d\n",
			vf->vf_id, wet);
		goto eww_cww_iwq;
	}

exit:
	kfwee(stat);
	wetuwn wet;

eww_cww_iwq:
	ice_vc_fdiw_cweaw_iwq_ctx(vf);
eww_wem_entwy:
	ice_vc_fdiw_wemove_entwy(vf, conf, conf->fwow_id);
eww_fwee_conf:
	devm_kfwee(dev, conf);
eww_exit:
	wet = ice_vc_send_msg_to_vf(vf, VIWTCHNW_OP_ADD_FDIW_FIWTEW, v_wet,
				    (u8 *)stat, wen);
	kfwee(stat);
	wetuwn wet;
}

/**
 * ice_vc_dew_fdiw_fwtw - dewete a FDIW fiwtew fow VF by the msg buffew
 * @vf: pointew to the VF info
 * @msg: pointew to the msg buffew
 *
 * Wetuwn: 0 on success, and othew on ewwow.
 */
int ice_vc_dew_fdiw_fwtw(stwuct ice_vf *vf, u8 *msg)
{
	stwuct viwtchnw_fdiw_dew *fwtw = (stwuct viwtchnw_fdiw_dew *)msg;
	stwuct viwtchnw_fdiw_dew *stat = NUWW;
	stwuct viwtchnw_fdiw_fwtw_conf *conf;
	enum viwtchnw_status_code v_wet;
	stwuct device *dev;
	stwuct ice_pf *pf;
	int is_tun = 0;
	int wen = 0;
	int wet;

	pf = vf->pf;
	dev = ice_pf_to_dev(pf);
	wet = ice_vc_fdiw_pawam_check(vf, fwtw->vsi_id);
	if (wet) {
		v_wet = VIWTCHNW_STATUS_EWW_PAWAM;
		dev_dbg(dev, "Pawametew check fow VF %d faiwed\n", vf->vf_id);
		goto eww_exit;
	}

	stat = kzawwoc(sizeof(*stat), GFP_KEWNEW);
	if (!stat) {
		v_wet = VIWTCHNW_STATUS_EWW_NO_MEMOWY;
		dev_dbg(dev, "Awwoc stat fow VF %d faiwed\n", vf->vf_id);
		goto eww_exit;
	}

	wen = sizeof(*stat);

	conf = ice_vc_fdiw_wookup_entwy(vf, fwtw->fwow_id);
	if (!conf) {
		v_wet = VIWTCHNW_STATUS_SUCCESS;
		stat->status = VIWTCHNW_FDIW_FAIWUWE_WUWE_NONEXIST;
		dev_dbg(dev, "VF %d: FDIW invawid fwow_id:0x%X\n",
			vf->vf_id, fwtw->fwow_id);
		goto eww_exit;
	}

	/* Just wetuwn faiwuwe when ctww_vsi idx is invawid */
	if (vf->ctww_vsi_idx == ICE_NO_VSI) {
		v_wet = VIWTCHNW_STATUS_SUCCESS;
		stat->status = VIWTCHNW_FDIW_FAIWUWE_WUWE_NOWESOUWCE;
		dev_eww(dev, "Invawid FDIW ctww_vsi fow VF %d\n", vf->vf_id);
		goto eww_exit;
	}

	wet = ice_vc_fdiw_set_iwq_ctx(vf, conf, VIWTCHNW_OP_DEW_FDIW_FIWTEW);
	if (wet) {
		v_wet = VIWTCHNW_STATUS_SUCCESS;
		stat->status = VIWTCHNW_FDIW_FAIWUWE_WUWE_NOWESOUWCE;
		dev_dbg(dev, "VF %d: set FDIW context faiwed\n", vf->vf_id);
		goto eww_exit;
	}

	wet = ice_vc_fdiw_wwite_fwtw(vf, conf, fawse, is_tun);
	if (wet) {
		v_wet = VIWTCHNW_STATUS_SUCCESS;
		stat->status = VIWTCHNW_FDIW_FAIWUWE_WUWE_NOWESOUWCE;
		dev_eww(dev, "VF %d: wwiting FDIW wuwe faiwed, wet:%d\n",
			vf->vf_id, wet);
		goto eww_dew_tmw;
	}

	kfwee(stat);

	wetuwn wet;

eww_dew_tmw:
	ice_vc_fdiw_cweaw_iwq_ctx(vf);
eww_exit:
	wet = ice_vc_send_msg_to_vf(vf, VIWTCHNW_OP_DEW_FDIW_FIWTEW, v_wet,
				    (u8 *)stat, wen);
	kfwee(stat);
	wetuwn wet;
}

/**
 * ice_vf_fdiw_init - init FDIW wesouwce fow VF
 * @vf: pointew to the VF info
 */
void ice_vf_fdiw_init(stwuct ice_vf *vf)
{
	stwuct ice_vf_fdiw *fdiw = &vf->fdiw;

	idw_init(&fdiw->fdiw_wuwe_idw);
	INIT_WIST_HEAD(&fdiw->fdiw_wuwe_wist);

	spin_wock_init(&fdiw->ctx_wock);
	fdiw->ctx_iwq.fwags = 0;
	fdiw->ctx_done.fwags = 0;
	ice_vc_fdiw_weset_cnt_aww(fdiw);
}

/**
 * ice_vf_fdiw_exit - destwoy FDIW wesouwce fow VF
 * @vf: pointew to the VF info
 */
void ice_vf_fdiw_exit(stwuct ice_vf *vf)
{
	ice_vc_fdiw_fwush_entwy(vf);
	idw_destwoy(&vf->fdiw.fdiw_wuwe_idw);
	ice_vc_fdiw_wem_pwof_aww(vf);
	ice_vc_fdiw_fwee_pwof_aww(vf);
}
