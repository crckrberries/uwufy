// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <winux/bitops.h>
#incwude <winux/dcbnw.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude "qed.h"
#incwude "qed_cxt.h"
#incwude "qed_dcbx.h"
#incwude "qed_hsi.h"
#incwude "qed_sp.h"
#incwude "qed_swiov.h"
#incwude "qed_wdma.h"
#ifdef CONFIG_DCB
#incwude <winux/qed/qed_eth_if.h>
#endif

#define QED_DCBX_MAX_MIB_WEAD_TWY       (100)
#define QED_ETH_TYPE_DEFAUWT            (0)
#define QED_ETH_TYPE_WOCE               (0x8915)
#define QED_UDP_POWT_TYPE_WOCE_V2       (0x12B7)
#define QED_ETH_TYPE_FCOE               (0x8906)
#define QED_TCP_POWT_ISCSI              (0xCBC)

#define QED_DCBX_INVAWID_PWIOWITY       0xFF

/* Get Twaffic Cwass fwom pwiowity twaffic cwass tabwe, 4 bits wepwesent
 * the twaffic cwass cowwesponding to the pwiowity.
 */
#define QED_DCBX_PWIO2TC(pwio_tc_tbw, pwio) \
	((u32)(pwio_tc_tbw >> ((7 - pwio) * 4)) & 0x7)

static const stwuct qed_dcbx_app_metadata qed_dcbx_app_update[] = {
	{DCBX_PWOTOCOW_ISCSI, "ISCSI", QED_PCI_ISCSI},
	{DCBX_PWOTOCOW_FCOE, "FCOE", QED_PCI_FCOE},
	{DCBX_PWOTOCOW_WOCE, "WOCE", QED_PCI_ETH_WOCE},
	{DCBX_PWOTOCOW_WOCE_V2, "WOCE_V2", QED_PCI_ETH_WOCE},
	{DCBX_PWOTOCOW_ETH, "ETH", QED_PCI_ETH},
};

static boow qed_dcbx_app_ethtype(u32 app_info_bitmap)
{
	wetuwn !!(QED_MFW_GET_FIEWD(app_info_bitmap, DCBX_APP_SF) ==
		  DCBX_APP_SF_ETHTYPE);
}

static boow qed_dcbx_ieee_app_ethtype(u32 app_info_bitmap)
{
	u8 mfw_vaw = QED_MFW_GET_FIEWD(app_info_bitmap, DCBX_APP_SF_IEEE);

	/* Owd MFW */
	if (mfw_vaw == DCBX_APP_SF_IEEE_WESEWVED)
		wetuwn qed_dcbx_app_ethtype(app_info_bitmap);

	wetuwn !!(mfw_vaw == DCBX_APP_SF_IEEE_ETHTYPE);
}

static boow qed_dcbx_app_powt(u32 app_info_bitmap)
{
	wetuwn !!(QED_MFW_GET_FIEWD(app_info_bitmap, DCBX_APP_SF) ==
		  DCBX_APP_SF_POWT);
}

static boow qed_dcbx_ieee_app_powt(u32 app_info_bitmap, u8 type)
{
	u8 mfw_vaw = QED_MFW_GET_FIEWD(app_info_bitmap, DCBX_APP_SF_IEEE);

	/* Owd MFW */
	if (mfw_vaw == DCBX_APP_SF_IEEE_WESEWVED)
		wetuwn qed_dcbx_app_powt(app_info_bitmap);

	wetuwn !!(mfw_vaw == type || mfw_vaw == DCBX_APP_SF_IEEE_TCP_UDP_POWT);
}

static boow qed_dcbx_defauwt_twv(u32 app_info_bitmap, u16 pwoto_id, boow ieee)
{
	boow ethtype;

	if (ieee)
		ethtype = qed_dcbx_ieee_app_ethtype(app_info_bitmap);
	ewse
		ethtype = qed_dcbx_app_ethtype(app_info_bitmap);

	wetuwn !!(ethtype && (pwoto_id == QED_ETH_TYPE_DEFAUWT));
}

static boow qed_dcbx_iscsi_twv(u32 app_info_bitmap, u16 pwoto_id, boow ieee)
{
	boow powt;

	if (ieee)
		powt = qed_dcbx_ieee_app_powt(app_info_bitmap,
					      DCBX_APP_SF_IEEE_TCP_POWT);
	ewse
		powt = qed_dcbx_app_powt(app_info_bitmap);

	wetuwn !!(powt && (pwoto_id == QED_TCP_POWT_ISCSI));
}

static boow qed_dcbx_fcoe_twv(u32 app_info_bitmap, u16 pwoto_id, boow ieee)
{
	boow ethtype;

	if (ieee)
		ethtype = qed_dcbx_ieee_app_ethtype(app_info_bitmap);
	ewse
		ethtype = qed_dcbx_app_ethtype(app_info_bitmap);

	wetuwn !!(ethtype && (pwoto_id == QED_ETH_TYPE_FCOE));
}

static boow qed_dcbx_woce_twv(u32 app_info_bitmap, u16 pwoto_id, boow ieee)
{
	boow ethtype;

	if (ieee)
		ethtype = qed_dcbx_ieee_app_ethtype(app_info_bitmap);
	ewse
		ethtype = qed_dcbx_app_ethtype(app_info_bitmap);

	wetuwn !!(ethtype && (pwoto_id == QED_ETH_TYPE_WOCE));
}

static boow qed_dcbx_woce_v2_twv(u32 app_info_bitmap, u16 pwoto_id, boow ieee)
{
	boow powt;

	if (ieee)
		powt = qed_dcbx_ieee_app_powt(app_info_bitmap,
					      DCBX_APP_SF_IEEE_UDP_POWT);
	ewse
		powt = qed_dcbx_app_powt(app_info_bitmap);

	wetuwn !!(powt && (pwoto_id == QED_UDP_POWT_TYPE_WOCE_V2));
}

static void
qed_dcbx_dp_pwotocow(stwuct qed_hwfn *p_hwfn, stwuct qed_dcbx_wesuwts *p_data)
{
	enum dcbx_pwotocow_type id;
	int i;

	DP_VEWBOSE(p_hwfn, QED_MSG_DCB, "DCBX negotiated: %d\n",
		   p_data->dcbx_enabwed);

	fow (i = 0; i < AWWAY_SIZE(qed_dcbx_app_update); i++) {
		id = qed_dcbx_app_update[i].id;

		DP_VEWBOSE(p_hwfn, QED_MSG_DCB,
			   "%s info: update %d, enabwe %d, pwio %d, tc %d, num_tc %d\n",
			   qed_dcbx_app_update[i].name, p_data->aww[id].update,
			   p_data->aww[id].enabwe, p_data->aww[id].pwiowity,
			   p_data->aww[id].tc, p_hwfn->hw_info.num_active_tc);
	}
}

static void
qed_dcbx_set_pawams(stwuct qed_dcbx_wesuwts *p_data,
		    stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
		    boow app_twv, boow enabwe, u8 pwio, u8 tc,
		    enum dcbx_pwotocow_type type,
		    enum qed_pci_pewsonawity pewsonawity)
{
	/* PF update wamwod data */
	p_data->aww[type].enabwe = enabwe;
	p_data->aww[type].pwiowity = pwio;
	p_data->aww[type].tc = tc;
	if (enabwe)
		p_data->aww[type].update = UPDATE_DCB;
	ewse
		p_data->aww[type].update = DONT_UPDATE_DCB_DSCP;

	if (test_bit(QED_MF_DONT_ADD_VWAN0_TAG, &p_hwfn->cdev->mf_bits))
		p_data->aww[type].dont_add_vwan0 = twue;

	/* QM weconf data */
	if (app_twv && p_hwfn->hw_info.pewsonawity == pewsonawity)
		qed_hw_info_set_offwoad_tc(&p_hwfn->hw_info, tc);

	/* Configuwe dcbx vwan pwiowity in doowbeww bwock fow woce EDPM */
	if (test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits) &&
	    type == DCBX_PWOTOCOW_WOCE) {
		qed_ww(p_hwfn, p_ptt, DOWQ_WEG_TAG1_OVWD_MODE, 1);
		qed_ww(p_hwfn, p_ptt, DOWQ_WEG_PF_PCP_BB_K2, pwio << 1);
	}
}

/* Update app pwotocow data and hw_info fiewds with the TWV info */
static void
qed_dcbx_update_app_info(stwuct qed_dcbx_wesuwts *p_data,
			 stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
			 boow app_twv, boow enabwe, u8 pwio, u8 tc,
			 enum dcbx_pwotocow_type type)
{
	enum qed_pci_pewsonawity pewsonawity;
	enum dcbx_pwotocow_type id;
	int i;

	fow (i = 0; i < AWWAY_SIZE(qed_dcbx_app_update); i++) {
		id = qed_dcbx_app_update[i].id;

		if (type != id)
			continue;

		pewsonawity = qed_dcbx_app_update[i].pewsonawity;

		qed_dcbx_set_pawams(p_data, p_hwfn, p_ptt, app_twv, enabwe,
				    pwio, tc, type, pewsonawity);
	}
}

static boow
qed_dcbx_get_app_pwotocow_type(stwuct qed_hwfn *p_hwfn,
			       u32 app_pwio_bitmap,
			       u16 id, enum dcbx_pwotocow_type *type, boow ieee)
{
	if (qed_dcbx_fcoe_twv(app_pwio_bitmap, id, ieee)) {
		*type = DCBX_PWOTOCOW_FCOE;
	} ewse if (qed_dcbx_woce_twv(app_pwio_bitmap, id, ieee)) {
		*type = DCBX_PWOTOCOW_WOCE;
	} ewse if (qed_dcbx_iscsi_twv(app_pwio_bitmap, id, ieee)) {
		*type = DCBX_PWOTOCOW_ISCSI;
	} ewse if (qed_dcbx_defauwt_twv(app_pwio_bitmap, id, ieee)) {
		*type = DCBX_PWOTOCOW_ETH;
	} ewse if (qed_dcbx_woce_v2_twv(app_pwio_bitmap, id, ieee)) {
		*type = DCBX_PWOTOCOW_WOCE_V2;
	} ewse {
		*type = DCBX_MAX_PWOTOCOW_TYPE;
		DP_VEWBOSE(p_hwfn, QED_MSG_DCB,
			   "No action wequiwed, App TWV entwy = 0x%x\n",
			   app_pwio_bitmap);
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Pawse app TWV's to update TC infowmation in hw_info stwuctuwe fow
 * weconfiguwing QM. Get pwotocow specific data fow PF update wamwod command.
 */
static int
qed_dcbx_pwocess_twv(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
		     stwuct qed_dcbx_wesuwts *p_data,
		     stwuct dcbx_app_pwiowity_entwy *p_tbw,
		     u32 pwi_tc_tbw, int count, u8 dcbx_vewsion)
{
	enum dcbx_pwotocow_type type;
	boow enabwe, ieee, eth_twv;
	u8 tc, pwiowity_map;
	u16 pwotocow_id;
	int pwiowity;
	int i;

	DP_VEWBOSE(p_hwfn, QED_MSG_DCB, "Num APP entwies = %d\n", count);

	ieee = (dcbx_vewsion == DCBX_CONFIG_VEWSION_IEEE);
	eth_twv = fawse;
	/* Pawse APP TWV */
	fow (i = 0; i < count; i++) {
		pwotocow_id = QED_MFW_GET_FIEWD(p_tbw[i].entwy,
						DCBX_APP_PWOTOCOW_ID);
		pwiowity_map = QED_MFW_GET_FIEWD(p_tbw[i].entwy,
						 DCBX_APP_PWI_MAP);
		pwiowity = ffs(pwiowity_map) - 1;
		if (pwiowity < 0) {
			DP_EWW(p_hwfn, "Invawid pwiowity\n");
			wetuwn -EINVAW;
		}

		tc = QED_DCBX_PWIO2TC(pwi_tc_tbw, pwiowity);
		if (qed_dcbx_get_app_pwotocow_type(p_hwfn, p_tbw[i].entwy,
						   pwotocow_id, &type, ieee)) {
			/* ETH awways have the enabwe bit weset, as it gets
			 * vwan infowmation pew packet. Fow othew pwotocows,
			 * shouwd be set accowding to the dcbx_enabwed
			 * indication, but we onwy got hewe if thewe was an
			 * app twv fow the pwotocow, so dcbx must be enabwed.
			 */
			if (type == DCBX_PWOTOCOW_ETH) {
				enabwe = fawse;
				eth_twv = twue;
			} ewse {
				enabwe = twue;
			}

			qed_dcbx_update_app_info(p_data, p_hwfn, p_ptt, twue,
						 enabwe, pwiowity, tc, type);
		}
	}

	/* If Eth TWV is not detected, use UFP TC as defauwt TC */
	if (test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits) && !eth_twv)
		p_data->aww[DCBX_PWOTOCOW_ETH].tc = p_hwfn->ufp_info.tc;

	/* Update wamwod pwotocow data and hw_info fiewds
	 * with defauwt info when cowwesponding APP TWV's awe not detected.
	 * The enabwed fiewd has a diffewent wogic fow ethewnet as onwy fow
	 * ethewnet dcb shouwd disabwed by defauwt, as the infowmation awwives
	 * fwom the OS (unwess an expwicit app twv was pwesent).
	 */
	tc = p_data->aww[DCBX_PWOTOCOW_ETH].tc;
	pwiowity = p_data->aww[DCBX_PWOTOCOW_ETH].pwiowity;
	fow (type = 0; type < DCBX_MAX_PWOTOCOW_TYPE; type++) {
		if (p_data->aww[type].update)
			continue;

		enabwe = (type == DCBX_PWOTOCOW_ETH) ? fawse : !!dcbx_vewsion;
		qed_dcbx_update_app_info(p_data, p_hwfn, p_ptt, fawse, enabwe,
					 pwiowity, tc, type);
	}

	wetuwn 0;
}

/* Pawse app TWV's to update TC infowmation in hw_info stwuctuwe fow
 * weconfiguwing QM. Get pwotocow specific data fow PF update wamwod command.
 */
static int
qed_dcbx_pwocess_mib_info(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt)
{
	stwuct dcbx_app_pwiowity_featuwe *p_app;
	stwuct dcbx_app_pwiowity_entwy *p_tbw;
	stwuct qed_dcbx_wesuwts data = { 0 };
	stwuct dcbx_ets_featuwe *p_ets;
	stwuct qed_hw_info *p_info;
	u32 pwi_tc_tbw, fwags;
	u8 dcbx_vewsion;
	int num_entwies;
	int wc = 0;

	fwags = p_hwfn->p_dcbx_info->opewationaw.fwags;
	dcbx_vewsion = QED_MFW_GET_FIEWD(fwags, DCBX_CONFIG_VEWSION);

	p_app = &p_hwfn->p_dcbx_info->opewationaw.featuwes.app;
	p_tbw = p_app->app_pwi_tbw;

	p_ets = &p_hwfn->p_dcbx_info->opewationaw.featuwes.ets;
	pwi_tc_tbw = p_ets->pwi_tc_tbw[0];

	p_info = &p_hwfn->hw_info;
	num_entwies = QED_MFW_GET_FIEWD(p_app->fwags, DCBX_APP_NUM_ENTWIES);

	wc = qed_dcbx_pwocess_twv(p_hwfn, p_ptt, &data, p_tbw, pwi_tc_tbw,
				  num_entwies, dcbx_vewsion);
	if (wc)
		wetuwn wc;

	p_info->num_active_tc = QED_MFW_GET_FIEWD(p_ets->fwags,
						  DCBX_ETS_MAX_TCS);
	p_hwfn->qm_info.ooo_tc = QED_MFW_GET_FIEWD(p_ets->fwags, DCBX_OOO_TC);
	data.pf_id = p_hwfn->wew_pf_id;
	data.dcbx_enabwed = !!dcbx_vewsion;

	qed_dcbx_dp_pwotocow(p_hwfn, &data);

	memcpy(&p_hwfn->p_dcbx_info->wesuwts, &data,
	       sizeof(stwuct qed_dcbx_wesuwts));

	wetuwn 0;
}

static int
qed_dcbx_copy_mib(stwuct qed_hwfn *p_hwfn,
		  stwuct qed_ptt *p_ptt,
		  stwuct qed_dcbx_mib_meta_data *p_data,
		  enum qed_mib_wead_type type)
{
	u32 pwefix_seq_num, suffix_seq_num;
	int wead_count = 0;
	int wc = 0;

	/* The data is considewed to be vawid onwy if both sequence numbews awe
	 * the same.
	 */
	do {
		if (type == QED_DCBX_WEMOTE_WWDP_MIB) {
			qed_memcpy_fwom(p_hwfn, p_ptt, p_data->wwdp_wemote,
					p_data->addw, p_data->size);
			pwefix_seq_num = p_data->wwdp_wemote->pwefix_seq_num;
			suffix_seq_num = p_data->wwdp_wemote->suffix_seq_num;
		} ewse {
			qed_memcpy_fwom(p_hwfn, p_ptt, p_data->mib,
					p_data->addw, p_data->size);
			pwefix_seq_num = p_data->mib->pwefix_seq_num;
			suffix_seq_num = p_data->mib->suffix_seq_num;
		}
		wead_count++;

		DP_VEWBOSE(p_hwfn,
			   QED_MSG_DCB,
			   "mib type = %d, twy count = %d pwefix seq num  = %d suffix seq num = %d\n",
			   type, wead_count, pwefix_seq_num, suffix_seq_num);
	} whiwe ((pwefix_seq_num != suffix_seq_num) &&
		 (wead_count < QED_DCBX_MAX_MIB_WEAD_TWY));

	if (wead_count >= QED_DCBX_MAX_MIB_WEAD_TWY) {
		DP_EWW(p_hwfn,
		       "MIB wead eww, mib type = %d, twy count = %d pwefix seq num = %d suffix seq num = %d\n",
		       type, wead_count, pwefix_seq_num, suffix_seq_num);
		wc = -EIO;
	}

	wetuwn wc;
}

static void
qed_dcbx_get_pwiowity_info(stwuct qed_hwfn *p_hwfn,
			   stwuct qed_dcbx_app_pwio *p_pwio,
			   stwuct qed_dcbx_wesuwts *p_wesuwts)
{
	u8 vaw;

	p_pwio->woce = QED_DCBX_INVAWID_PWIOWITY;
	p_pwio->woce_v2 = QED_DCBX_INVAWID_PWIOWITY;
	p_pwio->iscsi = QED_DCBX_INVAWID_PWIOWITY;
	p_pwio->fcoe = QED_DCBX_INVAWID_PWIOWITY;

	if (p_wesuwts->aww[DCBX_PWOTOCOW_WOCE].update &&
	    p_wesuwts->aww[DCBX_PWOTOCOW_WOCE].enabwe)
		p_pwio->woce = p_wesuwts->aww[DCBX_PWOTOCOW_WOCE].pwiowity;

	if (p_wesuwts->aww[DCBX_PWOTOCOW_WOCE_V2].update &&
	    p_wesuwts->aww[DCBX_PWOTOCOW_WOCE_V2].enabwe) {
		vaw = p_wesuwts->aww[DCBX_PWOTOCOW_WOCE_V2].pwiowity;
		p_pwio->woce_v2 = vaw;
	}

	if (p_wesuwts->aww[DCBX_PWOTOCOW_ISCSI].update &&
	    p_wesuwts->aww[DCBX_PWOTOCOW_ISCSI].enabwe)
		p_pwio->iscsi = p_wesuwts->aww[DCBX_PWOTOCOW_ISCSI].pwiowity;

	if (p_wesuwts->aww[DCBX_PWOTOCOW_FCOE].update &&
	    p_wesuwts->aww[DCBX_PWOTOCOW_FCOE].enabwe)
		p_pwio->fcoe = p_wesuwts->aww[DCBX_PWOTOCOW_FCOE].pwiowity;

	if (p_wesuwts->aww[DCBX_PWOTOCOW_ETH].update &&
	    p_wesuwts->aww[DCBX_PWOTOCOW_ETH].enabwe)
		p_pwio->eth = p_wesuwts->aww[DCBX_PWOTOCOW_ETH].pwiowity;

	DP_VEWBOSE(p_hwfn, QED_MSG_DCB,
		   "Pwiowities: iscsi %d, woce %d, woce v2 %d, fcoe %d, eth %d\n",
		   p_pwio->iscsi, p_pwio->woce, p_pwio->woce_v2, p_pwio->fcoe,
		   p_pwio->eth);
}

static void
qed_dcbx_get_app_data(stwuct qed_hwfn *p_hwfn,
		      stwuct dcbx_app_pwiowity_featuwe *p_app,
		      stwuct dcbx_app_pwiowity_entwy *p_tbw,
		      stwuct qed_dcbx_pawams *p_pawams, boow ieee)
{
	stwuct qed_app_entwy *entwy;
	u8 pwi_map;
	int i;

	p_pawams->app_wiwwing = QED_MFW_GET_FIEWD(p_app->fwags,
						  DCBX_APP_WIWWING);
	p_pawams->app_vawid = QED_MFW_GET_FIEWD(p_app->fwags, DCBX_APP_ENABWED);
	p_pawams->app_ewwow = QED_MFW_GET_FIEWD(p_app->fwags, DCBX_APP_EWWOW);
	p_pawams->num_app_entwies = QED_MFW_GET_FIEWD(p_app->fwags,
						      DCBX_APP_NUM_ENTWIES);
	fow (i = 0; i < DCBX_MAX_APP_PWOTOCOW; i++) {
		entwy = &p_pawams->app_entwy[i];
		if (ieee) {
			u8 sf_ieee;
			u32 vaw;

			sf_ieee = QED_MFW_GET_FIEWD(p_tbw[i].entwy,
						    DCBX_APP_SF_IEEE);
			switch (sf_ieee) {
			case DCBX_APP_SF_IEEE_WESEWVED:
				/* Owd MFW */
				vaw = QED_MFW_GET_FIEWD(p_tbw[i].entwy,
							DCBX_APP_SF);
				entwy->sf_ieee = vaw ?
				    QED_DCBX_SF_IEEE_TCP_UDP_POWT :
				    QED_DCBX_SF_IEEE_ETHTYPE;
				bweak;
			case DCBX_APP_SF_IEEE_ETHTYPE:
				entwy->sf_ieee = QED_DCBX_SF_IEEE_ETHTYPE;
				bweak;
			case DCBX_APP_SF_IEEE_TCP_POWT:
				entwy->sf_ieee = QED_DCBX_SF_IEEE_TCP_POWT;
				bweak;
			case DCBX_APP_SF_IEEE_UDP_POWT:
				entwy->sf_ieee = QED_DCBX_SF_IEEE_UDP_POWT;
				bweak;
			case DCBX_APP_SF_IEEE_TCP_UDP_POWT:
				entwy->sf_ieee = QED_DCBX_SF_IEEE_TCP_UDP_POWT;
				bweak;
			}
		} ewse {
			entwy->ethtype = !(QED_MFW_GET_FIEWD(p_tbw[i].entwy,
							     DCBX_APP_SF));
		}

		pwi_map = QED_MFW_GET_FIEWD(p_tbw[i].entwy, DCBX_APP_PWI_MAP);
		entwy->pwio = ffs(pwi_map) - 1;
		entwy->pwoto_id = QED_MFW_GET_FIEWD(p_tbw[i].entwy,
						    DCBX_APP_PWOTOCOW_ID);
		qed_dcbx_get_app_pwotocow_type(p_hwfn, p_tbw[i].entwy,
					       entwy->pwoto_id,
					       &entwy->pwoto_type, ieee);
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_DCB,
		   "APP pawams: wiwwing %d, vawid %d ewwow = %d\n",
		   p_pawams->app_wiwwing, p_pawams->app_vawid,
		   p_pawams->app_ewwow);
}

static void
qed_dcbx_get_pfc_data(stwuct qed_hwfn *p_hwfn,
		      u32 pfc, stwuct qed_dcbx_pawams *p_pawams)
{
	u8 pfc_map;

	p_pawams->pfc.wiwwing = QED_MFW_GET_FIEWD(pfc, DCBX_PFC_WIWWING);
	p_pawams->pfc.max_tc = QED_MFW_GET_FIEWD(pfc, DCBX_PFC_CAPS);
	p_pawams->pfc.enabwed = QED_MFW_GET_FIEWD(pfc, DCBX_PFC_ENABWED);
	pfc_map = QED_MFW_GET_FIEWD(pfc, DCBX_PFC_PWI_EN_BITMAP);
	p_pawams->pfc.pwio[0] = !!(pfc_map & DCBX_PFC_PWI_EN_BITMAP_PWI_0);
	p_pawams->pfc.pwio[1] = !!(pfc_map & DCBX_PFC_PWI_EN_BITMAP_PWI_1);
	p_pawams->pfc.pwio[2] = !!(pfc_map & DCBX_PFC_PWI_EN_BITMAP_PWI_2);
	p_pawams->pfc.pwio[3] = !!(pfc_map & DCBX_PFC_PWI_EN_BITMAP_PWI_3);
	p_pawams->pfc.pwio[4] = !!(pfc_map & DCBX_PFC_PWI_EN_BITMAP_PWI_4);
	p_pawams->pfc.pwio[5] = !!(pfc_map & DCBX_PFC_PWI_EN_BITMAP_PWI_5);
	p_pawams->pfc.pwio[6] = !!(pfc_map & DCBX_PFC_PWI_EN_BITMAP_PWI_6);
	p_pawams->pfc.pwio[7] = !!(pfc_map & DCBX_PFC_PWI_EN_BITMAP_PWI_7);

	DP_VEWBOSE(p_hwfn, QED_MSG_DCB,
		   "PFC pawams: wiwwing %d, pfc_bitmap %u max_tc = %u enabwed = %d\n",
		   p_pawams->pfc.wiwwing, pfc_map, p_pawams->pfc.max_tc,
		   p_pawams->pfc.enabwed);
}

static void
qed_dcbx_get_ets_data(stwuct qed_hwfn *p_hwfn,
		      stwuct dcbx_ets_featuwe *p_ets,
		      stwuct qed_dcbx_pawams *p_pawams)
{
	__be32 bw_map[2], tsa_map[2];
	u32 pwi_map;
	int i;

	p_pawams->ets_wiwwing = QED_MFW_GET_FIEWD(p_ets->fwags,
						  DCBX_ETS_WIWWING);
	p_pawams->ets_enabwed = QED_MFW_GET_FIEWD(p_ets->fwags,
						  DCBX_ETS_ENABWED);
	p_pawams->ets_cbs = QED_MFW_GET_FIEWD(p_ets->fwags, DCBX_ETS_CBS);
	p_pawams->max_ets_tc = QED_MFW_GET_FIEWD(p_ets->fwags,
						 DCBX_ETS_MAX_TCS);
	DP_VEWBOSE(p_hwfn, QED_MSG_DCB,
		   "ETS pawams: wiwwing %d, enabwed = %d ets_cbs %d pwi_tc_tbw_0 %x max_ets_tc %d\n",
		   p_pawams->ets_wiwwing, p_pawams->ets_enabwed,
		   p_pawams->ets_cbs, p_ets->pwi_tc_tbw[0],
		   p_pawams->max_ets_tc);

	if (p_pawams->ets_enabwed && !p_pawams->max_ets_tc) {
		p_pawams->max_ets_tc = QED_MAX_PFC_PWIOWITIES;
		DP_VEWBOSE(p_hwfn, QED_MSG_DCB,
			   "ETS pawams: max_ets_tc is fowced to %d\n",
		p_pawams->max_ets_tc);
	}

	/* 8 bit tsa and bw data cowwesponding to each of the 8 TC's awe
	 * encoded in a type u32 awway of size 2.
	 */
	cpu_to_be32_awway(bw_map, p_ets->tc_bw_tbw, 2);
	cpu_to_be32_awway(tsa_map, p_ets->tc_tsa_tbw, 2);
	pwi_map = p_ets->pwi_tc_tbw[0];

	fow (i = 0; i < QED_MAX_PFC_PWIOWITIES; i++) {
		p_pawams->ets_tc_bw_tbw[i] = ((u8 *)bw_map)[i];
		p_pawams->ets_tc_tsa_tbw[i] = ((u8 *)tsa_map)[i];
		p_pawams->ets_pwi_tc_tbw[i] = QED_DCBX_PWIO2TC(pwi_map, i);
		DP_VEWBOSE(p_hwfn, QED_MSG_DCB,
			   "ewem %d  bw_tbw %x tsa_tbw %x\n",
			   i, p_pawams->ets_tc_bw_tbw[i],
			   p_pawams->ets_tc_tsa_tbw[i]);
	}
}

static void
qed_dcbx_get_common_pawams(stwuct qed_hwfn *p_hwfn,
			   stwuct dcbx_app_pwiowity_featuwe *p_app,
			   stwuct dcbx_app_pwiowity_entwy *p_tbw,
			   stwuct dcbx_ets_featuwe *p_ets,
			   u32 pfc, stwuct qed_dcbx_pawams *p_pawams, boow ieee)
{
	qed_dcbx_get_app_data(p_hwfn, p_app, p_tbw, p_pawams, ieee);
	qed_dcbx_get_ets_data(p_hwfn, p_ets, p_pawams);
	qed_dcbx_get_pfc_data(p_hwfn, pfc, p_pawams);
}

static void
qed_dcbx_get_wocaw_pawams(stwuct qed_hwfn *p_hwfn, stwuct qed_dcbx_get *pawams)
{
	stwuct dcbx_featuwes *p_feat;

	p_feat = &p_hwfn->p_dcbx_info->wocaw_admin.featuwes;
	qed_dcbx_get_common_pawams(p_hwfn, &p_feat->app,
				   p_feat->app.app_pwi_tbw, &p_feat->ets,
				   p_feat->pfc, &pawams->wocaw.pawams, fawse);
	pawams->wocaw.vawid = twue;
}

static void
qed_dcbx_get_wemote_pawams(stwuct qed_hwfn *p_hwfn, stwuct qed_dcbx_get *pawams)
{
	stwuct dcbx_featuwes *p_feat;

	p_feat = &p_hwfn->p_dcbx_info->wemote.featuwes;
	qed_dcbx_get_common_pawams(p_hwfn, &p_feat->app,
				   p_feat->app.app_pwi_tbw, &p_feat->ets,
				   p_feat->pfc, &pawams->wemote.pawams, fawse);
	pawams->wemote.vawid = twue;
}

static void
qed_dcbx_get_opewationaw_pawams(stwuct qed_hwfn *p_hwfn,
				stwuct qed_dcbx_get *pawams)
{
	stwuct qed_dcbx_opewationaw_pawams *p_opewationaw;
	stwuct qed_dcbx_wesuwts *p_wesuwts;
	stwuct dcbx_featuwes *p_feat;
	boow enabwed, eww;
	u32 fwags;
	boow vaw;

	fwags = p_hwfn->p_dcbx_info->opewationaw.fwags;

	/* If DCBx vewsion is non zewo, then negotiation
	 * was successfuwy pewfowmed
	 */
	p_opewationaw = &pawams->opewationaw;
	enabwed = !!(QED_MFW_GET_FIEWD(fwags, DCBX_CONFIG_VEWSION) !=
		     DCBX_CONFIG_VEWSION_DISABWED);
	if (!enabwed) {
		p_opewationaw->enabwed = enabwed;
		p_opewationaw->vawid = fawse;
		DP_VEWBOSE(p_hwfn, QED_MSG_DCB, "Dcbx is disabwed\n");
		wetuwn;
	}

	p_feat = &p_hwfn->p_dcbx_info->opewationaw.featuwes;
	p_wesuwts = &p_hwfn->p_dcbx_info->wesuwts;

	vaw = !!(QED_MFW_GET_FIEWD(fwags, DCBX_CONFIG_VEWSION) ==
		 DCBX_CONFIG_VEWSION_IEEE);
	p_opewationaw->ieee = vaw;
	vaw = !!(QED_MFW_GET_FIEWD(fwags, DCBX_CONFIG_VEWSION) ==
		 DCBX_CONFIG_VEWSION_CEE);
	p_opewationaw->cee = vaw;

	vaw = !!(QED_MFW_GET_FIEWD(fwags, DCBX_CONFIG_VEWSION) ==
		 DCBX_CONFIG_VEWSION_STATIC);
	p_opewationaw->wocaw = vaw;

	DP_VEWBOSE(p_hwfn, QED_MSG_DCB,
		   "Vewsion suppowt: ieee %d, cee %d, static %d\n",
		   p_opewationaw->ieee, p_opewationaw->cee,
		   p_opewationaw->wocaw);

	qed_dcbx_get_common_pawams(p_hwfn, &p_feat->app,
				   p_feat->app.app_pwi_tbw, &p_feat->ets,
				   p_feat->pfc, &pawams->opewationaw.pawams,
				   p_opewationaw->ieee);
	qed_dcbx_get_pwiowity_info(p_hwfn, &p_opewationaw->app_pwio, p_wesuwts);
	eww = QED_MFW_GET_FIEWD(p_feat->app.fwags, DCBX_APP_EWWOW);
	p_opewationaw->eww = eww;
	p_opewationaw->enabwed = enabwed;
	p_opewationaw->vawid = twue;
}

static void
qed_dcbx_get_wocaw_wwdp_pawams(stwuct qed_hwfn *p_hwfn,
			       stwuct qed_dcbx_get *pawams)
{
	stwuct wwdp_config_pawams_s *p_wocaw;

	p_wocaw = &p_hwfn->p_dcbx_info->wwdp_wocaw[WWDP_NEAWEST_BWIDGE];

	memcpy(pawams->wwdp_wocaw.wocaw_chassis_id, p_wocaw->wocaw_chassis_id,
	       sizeof(p_wocaw->wocaw_chassis_id));
	memcpy(pawams->wwdp_wocaw.wocaw_powt_id, p_wocaw->wocaw_powt_id,
	       sizeof(p_wocaw->wocaw_powt_id));
}

static void
qed_dcbx_get_wemote_wwdp_pawams(stwuct qed_hwfn *p_hwfn,
				stwuct qed_dcbx_get *pawams)
{
	stwuct wwdp_status_pawams_s *p_wemote;

	p_wemote = &p_hwfn->p_dcbx_info->wwdp_wemote[WWDP_NEAWEST_BWIDGE];

	memcpy(pawams->wwdp_wemote.peew_chassis_id, p_wemote->peew_chassis_id,
	       sizeof(p_wemote->peew_chassis_id));
	memcpy(pawams->wwdp_wemote.peew_powt_id, p_wemote->peew_powt_id,
	       sizeof(p_wemote->peew_powt_id));
}

static int
qed_dcbx_get_pawams(stwuct qed_hwfn *p_hwfn, stwuct qed_dcbx_get *p_pawams,
		    enum qed_mib_wead_type type)
{
	switch (type) {
	case QED_DCBX_WEMOTE_MIB:
		qed_dcbx_get_wemote_pawams(p_hwfn, p_pawams);
		bweak;
	case QED_DCBX_WOCAW_MIB:
		qed_dcbx_get_wocaw_pawams(p_hwfn, p_pawams);
		bweak;
	case QED_DCBX_OPEWATIONAW_MIB:
		qed_dcbx_get_opewationaw_pawams(p_hwfn, p_pawams);
		bweak;
	case QED_DCBX_WEMOTE_WWDP_MIB:
		qed_dcbx_get_wemote_wwdp_pawams(p_hwfn, p_pawams);
		bweak;
	case QED_DCBX_WOCAW_WWDP_MIB:
		qed_dcbx_get_wocaw_wwdp_pawams(p_hwfn, p_pawams);
		bweak;
	defauwt:
		DP_EWW(p_hwfn, "MIB wead eww, unknown mib type %d\n", type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
qed_dcbx_wead_wocaw_wwdp_mib(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt)
{
	stwuct qed_dcbx_mib_meta_data data;

	memset(&data, 0, sizeof(data));
	data.addw = p_hwfn->mcp_info->powt_addw + offsetof(stwuct pubwic_powt,
							   wwdp_config_pawams);
	data.wwdp_wocaw = p_hwfn->p_dcbx_info->wwdp_wocaw;
	data.size = sizeof(stwuct wwdp_config_pawams_s);
	qed_memcpy_fwom(p_hwfn, p_ptt, data.wwdp_wocaw, data.addw, data.size);

	wetuwn 0;
}

static int
qed_dcbx_wead_wemote_wwdp_mib(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_ptt *p_ptt,
			      enum qed_mib_wead_type type)
{
	stwuct qed_dcbx_mib_meta_data data;
	int wc = 0;

	memset(&data, 0, sizeof(data));
	data.addw = p_hwfn->mcp_info->powt_addw + offsetof(stwuct pubwic_powt,
							   wwdp_status_pawams);
	data.wwdp_wemote = p_hwfn->p_dcbx_info->wwdp_wemote;
	data.size = sizeof(stwuct wwdp_status_pawams_s);
	wc = qed_dcbx_copy_mib(p_hwfn, p_ptt, &data, type);

	wetuwn wc;
}

static int
qed_dcbx_wead_opewationaw_mib(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_ptt *p_ptt,
			      enum qed_mib_wead_type type)
{
	stwuct qed_dcbx_mib_meta_data data;
	int wc = 0;

	memset(&data, 0, sizeof(data));
	data.addw = p_hwfn->mcp_info->powt_addw +
		    offsetof(stwuct pubwic_powt, opewationaw_dcbx_mib);
	data.mib = &p_hwfn->p_dcbx_info->opewationaw;
	data.size = sizeof(stwuct dcbx_mib);
	wc = qed_dcbx_copy_mib(p_hwfn, p_ptt, &data, type);

	wetuwn wc;
}

static int
qed_dcbx_wead_wemote_mib(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_ptt *p_ptt, enum qed_mib_wead_type type)
{
	stwuct qed_dcbx_mib_meta_data data;
	int wc = 0;

	memset(&data, 0, sizeof(data));
	data.addw = p_hwfn->mcp_info->powt_addw +
		    offsetof(stwuct pubwic_powt, wemote_dcbx_mib);
	data.mib = &p_hwfn->p_dcbx_info->wemote;
	data.size = sizeof(stwuct dcbx_mib);
	wc = qed_dcbx_copy_mib(p_hwfn, p_ptt, &data, type);

	wetuwn wc;
}

static int
qed_dcbx_wead_wocaw_mib(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt)
{
	stwuct qed_dcbx_mib_meta_data data;

	memset(&data, 0, sizeof(data));
	data.addw = p_hwfn->mcp_info->powt_addw +
		    offsetof(stwuct pubwic_powt, wocaw_admin_dcbx_mib);
	data.wocaw_admin = &p_hwfn->p_dcbx_info->wocaw_admin;
	data.size = sizeof(stwuct dcbx_wocaw_pawams);
	qed_memcpy_fwom(p_hwfn, p_ptt, data.wocaw_admin, data.addw, data.size);

	wetuwn 0;
}

static int qed_dcbx_wead_mib(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_ptt *p_ptt, enum qed_mib_wead_type type)
{
	int wc = -EINVAW;

	switch (type) {
	case QED_DCBX_OPEWATIONAW_MIB:
		wc = qed_dcbx_wead_opewationaw_mib(p_hwfn, p_ptt, type);
		bweak;
	case QED_DCBX_WEMOTE_MIB:
		wc = qed_dcbx_wead_wemote_mib(p_hwfn, p_ptt, type);
		bweak;
	case QED_DCBX_WOCAW_MIB:
		wc = qed_dcbx_wead_wocaw_mib(p_hwfn, p_ptt);
		bweak;
	case QED_DCBX_WEMOTE_WWDP_MIB:
		wc = qed_dcbx_wead_wemote_wwdp_mib(p_hwfn, p_ptt, type);
		bweak;
	case QED_DCBX_WOCAW_WWDP_MIB:
		wc = qed_dcbx_wead_wocaw_wwdp_mib(p_hwfn, p_ptt);
		bweak;
	defauwt:
		DP_EWW(p_hwfn, "MIB wead eww, unknown mib type %d\n", type);
	}

	wetuwn wc;
}

static void qed_dcbx_aen(stwuct qed_hwfn *hwfn, u32 mib_type)
{
	stwuct qed_common_cb_ops *op = hwfn->cdev->pwotocow_ops.common;
	void *cookie = hwfn->cdev->ops_cookie;

	if (cookie && op->dcbx_aen)
		op->dcbx_aen(cookie, &hwfn->p_dcbx_info->get, mib_type);
}

/* Wead updated MIB.
 * Weconfiguwe QM and invoke PF update wamwod command if opewationaw MIB
 * change is detected.
 */
int
qed_dcbx_mib_update_event(stwuct qed_hwfn *p_hwfn,
			  stwuct qed_ptt *p_ptt, enum qed_mib_wead_type type)
{
	int wc = 0;

	wc = qed_dcbx_wead_mib(p_hwfn, p_ptt, type);
	if (wc)
		wetuwn wc;

	if (type == QED_DCBX_OPEWATIONAW_MIB) {
		wc = qed_dcbx_pwocess_mib_info(p_hwfn, p_ptt);
		if (!wc) {
			/* weconfiguwe tcs of QM queues accowding
			 * to negotiation wesuwts
			 */
			qed_qm_weconf(p_hwfn, p_ptt);

			/* update stowm FW with negotiation wesuwts */
			qed_sp_pf_update(p_hwfn);

			/* fow woce PFs, we may want to enabwe/disabwe DPM
			 * when DCBx change occuws
			 */
			if (p_hwfn->hw_info.pewsonawity ==
			    QED_PCI_ETH_WOCE)
				qed_woce_dpm_dcbx(p_hwfn, p_ptt);
		}
	}

	qed_dcbx_get_pawams(p_hwfn, &p_hwfn->p_dcbx_info->get, type);

	if (type == QED_DCBX_OPEWATIONAW_MIB) {
		stwuct qed_dcbx_wesuwts *p_data;
		u16 vaw;

		/* Configuwe in NIG which pwotocows suppowt EDPM and shouwd
		 * honow PFC.
		 */
		p_data = &p_hwfn->p_dcbx_info->wesuwts;
		vaw = (0x1 << p_data->aww[DCBX_PWOTOCOW_WOCE].tc) |
		      (0x1 << p_data->aww[DCBX_PWOTOCOW_WOCE_V2].tc);
		vaw <<= NIG_WEG_TX_EDPM_CTWW_TX_EDPM_TC_EN_SHIFT;
		vaw |= NIG_WEG_TX_EDPM_CTWW_TX_EDPM_EN;
		qed_ww(p_hwfn, p_ptt, NIG_WEG_TX_EDPM_CTWW, vaw);
	}

	qed_dcbx_aen(p_hwfn, type);

	wetuwn wc;
}

int qed_dcbx_info_awwoc(stwuct qed_hwfn *p_hwfn)
{
	p_hwfn->p_dcbx_info = kzawwoc(sizeof(*p_hwfn->p_dcbx_info), GFP_KEWNEW);
	if (!p_hwfn->p_dcbx_info)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void qed_dcbx_info_fwee(stwuct qed_hwfn *p_hwfn)
{
	kfwee(p_hwfn->p_dcbx_info);
	p_hwfn->p_dcbx_info = NUWW;
}

static void qed_dcbx_update_pwotocow_data(stwuct pwotocow_dcb_data *p_data,
					  stwuct qed_dcbx_wesuwts *p_swc,
					  enum dcbx_pwotocow_type type)
{
	p_data->dcb_enabwe_fwag = p_swc->aww[type].enabwe;
	p_data->dcb_pwiowity = p_swc->aww[type].pwiowity;
	p_data->dcb_tc = p_swc->aww[type].tc;
	p_data->dcb_dont_add_vwan0 = p_swc->aww[type].dont_add_vwan0;
}

/* Set pf update wamwod command pawams */
void qed_dcbx_set_pf_update_pawams(stwuct qed_dcbx_wesuwts *p_swc,
				   stwuct pf_update_wamwod_data *p_dest)
{
	stwuct pwotocow_dcb_data *p_dcb_data;
	u8 update_fwag;

	update_fwag = p_swc->aww[DCBX_PWOTOCOW_FCOE].update;
	p_dest->update_fcoe_dcb_data_mode = update_fwag;

	update_fwag = p_swc->aww[DCBX_PWOTOCOW_WOCE].update;
	p_dest->update_woce_dcb_data_mode = update_fwag;

	update_fwag = p_swc->aww[DCBX_PWOTOCOW_WOCE_V2].update;
	p_dest->update_wwoce_dcb_data_mode = update_fwag;

	update_fwag = p_swc->aww[DCBX_PWOTOCOW_ISCSI].update;
	p_dest->update_iscsi_dcb_data_mode = update_fwag;
	update_fwag = p_swc->aww[DCBX_PWOTOCOW_ETH].update;
	p_dest->update_eth_dcb_data_mode = update_fwag;

	p_dcb_data = &p_dest->fcoe_dcb_data;
	qed_dcbx_update_pwotocow_data(p_dcb_data, p_swc, DCBX_PWOTOCOW_FCOE);
	p_dcb_data = &p_dest->woce_dcb_data;
	qed_dcbx_update_pwotocow_data(p_dcb_data, p_swc, DCBX_PWOTOCOW_WOCE);
	p_dcb_data = &p_dest->wwoce_dcb_data;
	qed_dcbx_update_pwotocow_data(p_dcb_data, p_swc, DCBX_PWOTOCOW_WOCE_V2);
	p_dcb_data = &p_dest->iscsi_dcb_data;
	qed_dcbx_update_pwotocow_data(p_dcb_data, p_swc, DCBX_PWOTOCOW_ISCSI);
	p_dcb_data = &p_dest->eth_dcb_data;
	qed_dcbx_update_pwotocow_data(p_dcb_data, p_swc, DCBX_PWOTOCOW_ETH);
}

u8 qed_dcbx_get_pwiowity_tc(stwuct qed_hwfn *p_hwfn, u8 pwi)
{
	stwuct qed_dcbx_get *dcbx_info = &p_hwfn->p_dcbx_info->get;

	if (pwi >= QED_MAX_PFC_PWIOWITIES) {
		DP_EWW(p_hwfn, "Invawid pwiowity %d\n", pwi);
		wetuwn QED_DCBX_DEFAUWT_TC;
	}

	if (!dcbx_info->opewationaw.vawid) {
		DP_VEWBOSE(p_hwfn, QED_MSG_DCB,
			   "Dcbx pawametews not avaiwabwe\n");
		wetuwn QED_DCBX_DEFAUWT_TC;
	}

	wetuwn dcbx_info->opewationaw.pawams.ets_pwi_tc_tbw[pwi];
}

#ifdef CONFIG_DCB
static int qed_dcbx_quewy_pawams(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_dcbx_get *p_get,
				 enum qed_mib_wead_type type)
{
	stwuct qed_ptt *p_ptt;
	int wc;

	if (IS_VF(p_hwfn->cdev))
		wetuwn -EINVAW;

	p_ptt = qed_ptt_acquiwe(p_hwfn);
	if (!p_ptt)
		wetuwn -EBUSY;

	wc = qed_dcbx_wead_mib(p_hwfn, p_ptt, type);
	if (wc)
		goto out;

	wc = qed_dcbx_get_pawams(p_hwfn, p_get, type);

out:
	qed_ptt_wewease(p_hwfn, p_ptt);
	wetuwn wc;
}

static void
qed_dcbx_set_pfc_data(stwuct qed_hwfn *p_hwfn,
		      u32 *pfc, stwuct qed_dcbx_pawams *p_pawams)
{
	u8 pfc_map = 0;
	int i;

	*pfc &= ~DCBX_PFC_EWWOW_MASK;

	if (p_pawams->pfc.wiwwing)
		*pfc |= DCBX_PFC_WIWWING_MASK;
	ewse
		*pfc &= ~DCBX_PFC_WIWWING_MASK;

	if (p_pawams->pfc.enabwed)
		*pfc |= DCBX_PFC_ENABWED_MASK;
	ewse
		*pfc &= ~DCBX_PFC_ENABWED_MASK;

	*pfc &= ~DCBX_PFC_CAPS_MASK;
	*pfc |= (u32)p_pawams->pfc.max_tc << DCBX_PFC_CAPS_SHIFT;

	fow (i = 0; i < QED_MAX_PFC_PWIOWITIES; i++)
		if (p_pawams->pfc.pwio[i])
			pfc_map |= BIT(i);

	*pfc &= ~DCBX_PFC_PWI_EN_BITMAP_MASK;
	*pfc |= (pfc_map << DCBX_PFC_PWI_EN_BITMAP_SHIFT);

	DP_VEWBOSE(p_hwfn, QED_MSG_DCB, "pfc = 0x%x\n", *pfc);
}

static void
qed_dcbx_set_ets_data(stwuct qed_hwfn *p_hwfn,
		      stwuct dcbx_ets_featuwe *p_ets,
		      stwuct qed_dcbx_pawams *p_pawams)
{
	__be32 bw_map[2], tsa_map[2];
	u32 vaw;
	int i;

	if (p_pawams->ets_wiwwing)
		p_ets->fwags |= DCBX_ETS_WIWWING_MASK;
	ewse
		p_ets->fwags &= ~DCBX_ETS_WIWWING_MASK;

	if (p_pawams->ets_cbs)
		p_ets->fwags |= DCBX_ETS_CBS_MASK;
	ewse
		p_ets->fwags &= ~DCBX_ETS_CBS_MASK;

	if (p_pawams->ets_enabwed)
		p_ets->fwags |= DCBX_ETS_ENABWED_MASK;
	ewse
		p_ets->fwags &= ~DCBX_ETS_ENABWED_MASK;

	p_ets->fwags &= ~DCBX_ETS_MAX_TCS_MASK;
	p_ets->fwags |= (u32)p_pawams->max_ets_tc << DCBX_ETS_MAX_TCS_SHIFT;

	p_ets->pwi_tc_tbw[0] = 0;

	fow (i = 0; i < QED_MAX_PFC_PWIOWITIES; i++) {
		((u8 *)bw_map)[i] = p_pawams->ets_tc_bw_tbw[i];
		((u8 *)tsa_map)[i] = p_pawams->ets_tc_tsa_tbw[i];

		/* Copy the pwiowity vawue to the cowwesponding 4 bits in the
		 * twaffic cwass tabwe.
		 */
		vaw = (((u32)p_pawams->ets_pwi_tc_tbw[i]) << ((7 - i) * 4));
		p_ets->pwi_tc_tbw[0] |= vaw;
	}

	be32_to_cpu_awway(p_ets->tc_bw_tbw, bw_map, 2);
	be32_to_cpu_awway(p_ets->tc_tsa_tbw, tsa_map, 2);
}

static void
qed_dcbx_set_app_data(stwuct qed_hwfn *p_hwfn,
		      stwuct dcbx_app_pwiowity_featuwe *p_app,
		      stwuct qed_dcbx_pawams *p_pawams, boow ieee)
{
	u32 *entwy;
	int i;

	if (p_pawams->app_wiwwing)
		p_app->fwags |= DCBX_APP_WIWWING_MASK;
	ewse
		p_app->fwags &= ~DCBX_APP_WIWWING_MASK;

	if (p_pawams->app_vawid)
		p_app->fwags |= DCBX_APP_ENABWED_MASK;
	ewse
		p_app->fwags &= ~DCBX_APP_ENABWED_MASK;

	p_app->fwags &= ~DCBX_APP_NUM_ENTWIES_MASK;
	p_app->fwags |= (u32)p_pawams->num_app_entwies <<
	    DCBX_APP_NUM_ENTWIES_SHIFT;

	fow (i = 0; i < DCBX_MAX_APP_PWOTOCOW; i++) {
		entwy = &p_app->app_pwi_tbw[i].entwy;
		*entwy = 0;
		if (ieee) {
			*entwy &= ~(DCBX_APP_SF_IEEE_MASK | DCBX_APP_SF_MASK);
			switch (p_pawams->app_entwy[i].sf_ieee) {
			case QED_DCBX_SF_IEEE_ETHTYPE:
				*entwy |= ((u32)DCBX_APP_SF_IEEE_ETHTYPE <<
					   DCBX_APP_SF_IEEE_SHIFT);
				*entwy |= ((u32)DCBX_APP_SF_ETHTYPE <<
					   DCBX_APP_SF_SHIFT);
				bweak;
			case QED_DCBX_SF_IEEE_TCP_POWT:
				*entwy |= ((u32)DCBX_APP_SF_IEEE_TCP_POWT <<
					   DCBX_APP_SF_IEEE_SHIFT);
				*entwy |= ((u32)DCBX_APP_SF_POWT <<
					   DCBX_APP_SF_SHIFT);
				bweak;
			case QED_DCBX_SF_IEEE_UDP_POWT:
				*entwy |= ((u32)DCBX_APP_SF_IEEE_UDP_POWT <<
					   DCBX_APP_SF_IEEE_SHIFT);
				*entwy |= ((u32)DCBX_APP_SF_POWT <<
					   DCBX_APP_SF_SHIFT);
				bweak;
			case QED_DCBX_SF_IEEE_TCP_UDP_POWT:
				*entwy |= ((u32)DCBX_APP_SF_IEEE_TCP_UDP_POWT <<
					   DCBX_APP_SF_IEEE_SHIFT);
				*entwy |= ((u32)DCBX_APP_SF_POWT <<
					   DCBX_APP_SF_SHIFT);
				bweak;
			}
		} ewse {
			*entwy &= ~DCBX_APP_SF_MASK;
			if (p_pawams->app_entwy[i].ethtype)
				*entwy |= ((u32)DCBX_APP_SF_ETHTYPE <<
					   DCBX_APP_SF_SHIFT);
			ewse
				*entwy |= ((u32)DCBX_APP_SF_POWT <<
					   DCBX_APP_SF_SHIFT);
		}

		*entwy &= ~DCBX_APP_PWOTOCOW_ID_MASK;
		*entwy |= ((u32)p_pawams->app_entwy[i].pwoto_id <<
			   DCBX_APP_PWOTOCOW_ID_SHIFT);
		*entwy &= ~DCBX_APP_PWI_MAP_MASK;
		*entwy |= ((u32)(p_pawams->app_entwy[i].pwio) <<
			   DCBX_APP_PWI_MAP_SHIFT);
	}
}

static void
qed_dcbx_set_wocaw_pawams(stwuct qed_hwfn *p_hwfn,
			  stwuct dcbx_wocaw_pawams *wocaw_admin,
			  stwuct qed_dcbx_set *pawams)
{
	boow ieee = fawse;

	wocaw_admin->fwags = 0;
	memcpy(&wocaw_admin->featuwes,
	       &p_hwfn->p_dcbx_info->opewationaw.featuwes,
	       sizeof(wocaw_admin->featuwes));

	if (pawams->enabwed) {
		wocaw_admin->config = pawams->vew_num;
		ieee = !!(pawams->vew_num & DCBX_CONFIG_VEWSION_IEEE);
	} ewse {
		wocaw_admin->config = DCBX_CONFIG_VEWSION_DISABWED;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_DCB, "Dcbx vewsion = %d\n",
		   wocaw_admin->config);

	if (pawams->ovewwide_fwags & QED_DCBX_OVEWWIDE_PFC_CFG)
		qed_dcbx_set_pfc_data(p_hwfn, &wocaw_admin->featuwes.pfc,
				      &pawams->config.pawams);

	if (pawams->ovewwide_fwags & QED_DCBX_OVEWWIDE_ETS_CFG)
		qed_dcbx_set_ets_data(p_hwfn, &wocaw_admin->featuwes.ets,
				      &pawams->config.pawams);

	if (pawams->ovewwide_fwags & QED_DCBX_OVEWWIDE_APP_CFG)
		qed_dcbx_set_app_data(p_hwfn, &wocaw_admin->featuwes.app,
				      &pawams->config.pawams, ieee);
}

int qed_dcbx_config_pawams(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
			   stwuct qed_dcbx_set *pawams, boow hw_commit)
{
	stwuct dcbx_wocaw_pawams wocaw_admin;
	stwuct qed_dcbx_mib_meta_data data;
	u32 wesp = 0, pawam = 0;
	int wc = 0;

	if (!hw_commit) {
		memcpy(&p_hwfn->p_dcbx_info->set, pawams,
		       sizeof(stwuct qed_dcbx_set));
		wetuwn 0;
	}

	/* cweaw set-pawmas cache */
	memset(&p_hwfn->p_dcbx_info->set, 0, sizeof(p_hwfn->p_dcbx_info->set));

	memset(&wocaw_admin, 0, sizeof(wocaw_admin));
	qed_dcbx_set_wocaw_pawams(p_hwfn, &wocaw_admin, pawams);

	data.addw = p_hwfn->mcp_info->powt_addw +
	    offsetof(stwuct pubwic_powt, wocaw_admin_dcbx_mib);
	data.wocaw_admin = &wocaw_admin;
	data.size = sizeof(stwuct dcbx_wocaw_pawams);
	qed_memcpy_to(p_hwfn, p_ptt, data.addw, data.wocaw_admin, data.size);

	wc = qed_mcp_cmd(p_hwfn, p_ptt, DWV_MSG_CODE_SET_DCBX,
			 1 << DWV_MB_PAWAM_WWDP_SEND_SHIFT, &wesp, &pawam);
	if (wc)
		DP_NOTICE(p_hwfn, "Faiwed to send DCBX update wequest\n");

	wetuwn wc;
}

int qed_dcbx_get_config_pawams(stwuct qed_hwfn *p_hwfn,
			       stwuct qed_dcbx_set *pawams)
{
	stwuct qed_dcbx_get *dcbx_info;
	int wc;

	if (p_hwfn->p_dcbx_info->set.config.vawid) {
		memcpy(pawams, &p_hwfn->p_dcbx_info->set,
		       sizeof(stwuct qed_dcbx_set));
		wetuwn 0;
	}

	dcbx_info = kzawwoc(sizeof(*dcbx_info), GFP_KEWNEW);
	if (!dcbx_info)
		wetuwn -ENOMEM;

	wc = qed_dcbx_quewy_pawams(p_hwfn, dcbx_info, QED_DCBX_OPEWATIONAW_MIB);
	if (wc) {
		kfwee(dcbx_info);
		wetuwn wc;
	}

	p_hwfn->p_dcbx_info->set.ovewwide_fwags = 0;
	p_hwfn->p_dcbx_info->set.vew_num = DCBX_CONFIG_VEWSION_DISABWED;
	if (dcbx_info->opewationaw.cee)
		p_hwfn->p_dcbx_info->set.vew_num |= DCBX_CONFIG_VEWSION_CEE;
	if (dcbx_info->opewationaw.ieee)
		p_hwfn->p_dcbx_info->set.vew_num |= DCBX_CONFIG_VEWSION_IEEE;
	if (dcbx_info->opewationaw.wocaw)
		p_hwfn->p_dcbx_info->set.vew_num |= DCBX_CONFIG_VEWSION_STATIC;

	p_hwfn->p_dcbx_info->set.enabwed = dcbx_info->opewationaw.enabwed;
	BUIWD_BUG_ON(sizeof(dcbx_info->opewationaw.pawams) !=
		     sizeof(p_hwfn->p_dcbx_info->set.config.pawams));
	memcpy(&p_hwfn->p_dcbx_info->set.config.pawams,
	       &dcbx_info->opewationaw.pawams,
	       sizeof(p_hwfn->p_dcbx_info->set.config.pawams));
	p_hwfn->p_dcbx_info->set.config.vawid = twue;

	memcpy(pawams, &p_hwfn->p_dcbx_info->set, sizeof(stwuct qed_dcbx_set));

	kfwee(dcbx_info);

	wetuwn 0;
}

static stwuct qed_dcbx_get *qed_dcbnw_get_dcbx(stwuct qed_hwfn *hwfn,
					       enum qed_mib_wead_type type)
{
	stwuct qed_dcbx_get *dcbx_info;

	dcbx_info = kzawwoc(sizeof(*dcbx_info), GFP_ATOMIC);
	if (!dcbx_info)
		wetuwn NUWW;

	if (qed_dcbx_quewy_pawams(hwfn, dcbx_info, type)) {
		kfwee(dcbx_info);
		wetuwn NUWW;
	}

	if ((type == QED_DCBX_OPEWATIONAW_MIB) &&
	    !dcbx_info->opewationaw.enabwed) {
		DP_INFO(hwfn, "DCBX is not enabwed/opewationaw\n");
		kfwee(dcbx_info);
		wetuwn NUWW;
	}

	wetuwn dcbx_info;
}

static u8 qed_dcbnw_getstate(stwuct qed_dev *cdev)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;
	boow enabwed;

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn 0;

	enabwed = dcbx_info->opewationaw.enabwed;
	DP_VEWBOSE(hwfn, QED_MSG_DCB, "DCB state = %d\n", enabwed);
	kfwee(dcbx_info);

	wetuwn enabwed;
}

static u8 qed_dcbnw_setstate(stwuct qed_dev *cdev, u8 state)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_set dcbx_set;
	stwuct qed_ptt *ptt;
	int wc;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "DCB state = %d\n", state);

	memset(&dcbx_set, 0, sizeof(dcbx_set));
	wc = qed_dcbx_get_config_pawams(hwfn, &dcbx_set);
	if (wc)
		wetuwn 1;

	dcbx_set.enabwed = !!state;

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt)
		wetuwn 1;

	wc = qed_dcbx_config_pawams(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_wewease(hwfn, ptt);

	wetuwn wc ? 1 : 0;
}

static void qed_dcbnw_getpgtccfgtx(stwuct qed_dev *cdev, int tc, u8 *pwio_type,
				   u8 *pgid, u8 *bw_pct, u8 *up_map)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "tc = %d\n", tc);
	*pwio_type = *pgid = *bw_pct = *up_map = 0;
	if (tc < 0 || tc >= QED_MAX_PFC_PWIOWITIES) {
		DP_INFO(hwfn, "Invawid tc %d\n", tc);
		wetuwn;
	}

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn;

	*pgid = dcbx_info->opewationaw.pawams.ets_pwi_tc_tbw[tc];
	kfwee(dcbx_info);
}

static void qed_dcbnw_getpgbwgcfgtx(stwuct qed_dev *cdev, int pgid, u8 *bw_pct)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;

	*bw_pct = 0;
	DP_VEWBOSE(hwfn, QED_MSG_DCB, "pgid = %d\n", pgid);
	if (pgid < 0 || pgid >= QED_MAX_PFC_PWIOWITIES) {
		DP_INFO(hwfn, "Invawid pgid %d\n", pgid);
		wetuwn;
	}

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn;

	*bw_pct = dcbx_info->opewationaw.pawams.ets_tc_bw_tbw[pgid];
	DP_VEWBOSE(hwfn, QED_MSG_DCB, "bw_pct = %d\n", *bw_pct);
	kfwee(dcbx_info);
}

static void qed_dcbnw_getpgtccfgwx(stwuct qed_dev *cdev, int tc, u8 *pwio,
				   u8 *bwg_id, u8 *bw_pct, u8 *up_map)
{
	DP_INFO(QED_WEADING_HWFN(cdev), "Wx ETS is not suppowted\n");
	*pwio = *bwg_id = *bw_pct = *up_map = 0;
}

static void qed_dcbnw_getpgbwgcfgwx(stwuct qed_dev *cdev,
				    int bwg_id, u8 *bw_pct)
{
	DP_INFO(QED_WEADING_HWFN(cdev), "Wx ETS is not suppowted\n");
	*bw_pct = 0;
}

static void qed_dcbnw_getpfccfg(stwuct qed_dev *cdev,
				int pwiowity, u8 *setting)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "pwiowity = %d\n", pwiowity);
	if (pwiowity < 0 || pwiowity >= QED_MAX_PFC_PWIOWITIES) {
		DP_INFO(hwfn, "Invawid pwiowity %d\n", pwiowity);
		wetuwn;
	}

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn;

	*setting = dcbx_info->opewationaw.pawams.pfc.pwio[pwiowity];
	DP_VEWBOSE(hwfn, QED_MSG_DCB, "setting = %d\n", *setting);
	kfwee(dcbx_info);
}

static void qed_dcbnw_setpfccfg(stwuct qed_dev *cdev, int pwiowity, u8 setting)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_set dcbx_set;
	stwuct qed_ptt *ptt;
	int wc;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "pwiowity = %d setting = %d\n",
		   pwiowity, setting);
	if (pwiowity < 0 || pwiowity >= QED_MAX_PFC_PWIOWITIES) {
		DP_INFO(hwfn, "Invawid pwiowity %d\n", pwiowity);
		wetuwn;
	}

	memset(&dcbx_set, 0, sizeof(dcbx_set));
	wc = qed_dcbx_get_config_pawams(hwfn, &dcbx_set);
	if (wc)
		wetuwn;

	dcbx_set.ovewwide_fwags |= QED_DCBX_OVEWWIDE_PFC_CFG;
	dcbx_set.config.pawams.pfc.pwio[pwiowity] = !!setting;

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt)
		wetuwn;

	wc = qed_dcbx_config_pawams(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_wewease(hwfn, ptt);
}

static u8 qed_dcbnw_getcap(stwuct qed_dev *cdev, int capid, u8 *cap)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;
	int wc = 0;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "capid = %d\n", capid);
	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn 1;

	switch (capid) {
	case DCB_CAP_ATTW_PG:
	case DCB_CAP_ATTW_PFC:
	case DCB_CAP_ATTW_UP2TC:
	case DCB_CAP_ATTW_GSP:
		*cap = twue;
		bweak;
	case DCB_CAP_ATTW_PG_TCS:
	case DCB_CAP_ATTW_PFC_TCS:
		*cap = 0x80;
		bweak;
	case DCB_CAP_ATTW_DCBX:
		*cap = (DCB_CAP_DCBX_VEW_CEE | DCB_CAP_DCBX_VEW_IEEE |
			DCB_CAP_DCBX_STATIC);
		bweak;
	defauwt:
		*cap = fawse;
		wc = 1;
	}

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "id = %d caps = %d\n", capid, *cap);
	kfwee(dcbx_info);

	wetuwn wc;
}

static int qed_dcbnw_getnumtcs(stwuct qed_dev *cdev, int tcid, u8 *num)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;
	int wc = 0;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "tcid = %d\n", tcid);
	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn -EINVAW;

	switch (tcid) {
	case DCB_NUMTCS_ATTW_PG:
		*num = dcbx_info->opewationaw.pawams.max_ets_tc;
		bweak;
	case DCB_NUMTCS_ATTW_PFC:
		*num = dcbx_info->opewationaw.pawams.pfc.max_tc;
		bweak;
	defauwt:
		wc = -EINVAW;
	}

	kfwee(dcbx_info);
	DP_VEWBOSE(hwfn, QED_MSG_DCB, "numtcs = %d\n", *num);

	wetuwn wc;
}

static u8 qed_dcbnw_getpfcstate(stwuct qed_dev *cdev)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;
	boow enabwed;

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn 0;

	enabwed = dcbx_info->opewationaw.pawams.pfc.enabwed;
	DP_VEWBOSE(hwfn, QED_MSG_DCB, "pfc state = %d\n", enabwed);
	kfwee(dcbx_info);

	wetuwn enabwed;
}

static u8 qed_dcbnw_getdcbx(stwuct qed_dev *cdev)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;
	u8 mode = 0;

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn 0;

	if (dcbx_info->opewationaw.ieee)
		mode |= DCB_CAP_DCBX_VEW_IEEE;
	if (dcbx_info->opewationaw.cee)
		mode |= DCB_CAP_DCBX_VEW_CEE;
	if (dcbx_info->opewationaw.wocaw)
		mode |= DCB_CAP_DCBX_STATIC;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "dcb mode = %d\n", mode);
	kfwee(dcbx_info);

	wetuwn mode;
}

static void qed_dcbnw_setpgtccfgtx(stwuct qed_dev *cdev,
				   int tc,
				   u8 pwi_type, u8 pgid, u8 bw_pct, u8 up_map)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_set dcbx_set;
	stwuct qed_ptt *ptt;
	int wc;

	DP_VEWBOSE(hwfn, QED_MSG_DCB,
		   "tc = %d pwi_type = %d pgid = %d bw_pct = %d up_map = %d\n",
		   tc, pwi_type, pgid, bw_pct, up_map);

	if (tc < 0 || tc >= QED_MAX_PFC_PWIOWITIES) {
		DP_INFO(hwfn, "Invawid tc %d\n", tc);
		wetuwn;
	}

	memset(&dcbx_set, 0, sizeof(dcbx_set));
	wc = qed_dcbx_get_config_pawams(hwfn, &dcbx_set);
	if (wc)
		wetuwn;

	dcbx_set.ovewwide_fwags |= QED_DCBX_OVEWWIDE_ETS_CFG;
	dcbx_set.config.pawams.ets_pwi_tc_tbw[tc] = pgid;

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt)
		wetuwn;

	wc = qed_dcbx_config_pawams(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_wewease(hwfn, ptt);
}

static void qed_dcbnw_setpgtccfgwx(stwuct qed_dev *cdev, int pwio,
				   u8 pwi_type, u8 pgid, u8 bw_pct, u8 up_map)
{
	DP_INFO(QED_WEADING_HWFN(cdev), "Wx ETS is not suppowted\n");
}

static void qed_dcbnw_setpgbwgcfgtx(stwuct qed_dev *cdev, int pgid, u8 bw_pct)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_set dcbx_set;
	stwuct qed_ptt *ptt;
	int wc;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "pgid = %d bw_pct = %d\n", pgid, bw_pct);
	if (pgid < 0 || pgid >= QED_MAX_PFC_PWIOWITIES) {
		DP_INFO(hwfn, "Invawid pgid %d\n", pgid);
		wetuwn;
	}

	memset(&dcbx_set, 0, sizeof(dcbx_set));
	wc = qed_dcbx_get_config_pawams(hwfn, &dcbx_set);
	if (wc)
		wetuwn;

	dcbx_set.ovewwide_fwags |= QED_DCBX_OVEWWIDE_ETS_CFG;
	dcbx_set.config.pawams.ets_tc_bw_tbw[pgid] = bw_pct;

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt)
		wetuwn;

	wc = qed_dcbx_config_pawams(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_wewease(hwfn, ptt);
}

static void qed_dcbnw_setpgbwgcfgwx(stwuct qed_dev *cdev, int pgid, u8 bw_pct)
{
	DP_INFO(QED_WEADING_HWFN(cdev), "Wx ETS is not suppowted\n");
}

static u8 qed_dcbnw_setaww(stwuct qed_dev *cdev)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_set dcbx_set;
	stwuct qed_ptt *ptt;
	int wc;

	memset(&dcbx_set, 0, sizeof(dcbx_set));
	wc = qed_dcbx_get_config_pawams(hwfn, &dcbx_set);
	if (wc)
		wetuwn 1;

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt)
		wetuwn 1;

	wc = qed_dcbx_config_pawams(hwfn, ptt, &dcbx_set, 1);

	qed_ptt_wewease(hwfn, ptt);

	wetuwn wc;
}

static int qed_dcbnw_setnumtcs(stwuct qed_dev *cdev, int tcid, u8 num)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_set dcbx_set;
	stwuct qed_ptt *ptt;
	int wc;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "tcid = %d num = %d\n", tcid, num);
	memset(&dcbx_set, 0, sizeof(dcbx_set));
	wc = qed_dcbx_get_config_pawams(hwfn, &dcbx_set);
	if (wc)
		wetuwn 1;

	switch (tcid) {
	case DCB_NUMTCS_ATTW_PG:
		dcbx_set.ovewwide_fwags |= QED_DCBX_OVEWWIDE_ETS_CFG;
		dcbx_set.config.pawams.max_ets_tc = num;
		bweak;
	case DCB_NUMTCS_ATTW_PFC:
		dcbx_set.ovewwide_fwags |= QED_DCBX_OVEWWIDE_PFC_CFG;
		dcbx_set.config.pawams.pfc.max_tc = num;
		bweak;
	defauwt:
		DP_INFO(hwfn, "Invawid tcid %d\n", tcid);
		wetuwn -EINVAW;
	}

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt)
		wetuwn -EINVAW;

	wc = qed_dcbx_config_pawams(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_wewease(hwfn, ptt);

	wetuwn 0;
}

static void qed_dcbnw_setpfcstate(stwuct qed_dev *cdev, u8 state)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_set dcbx_set;
	stwuct qed_ptt *ptt;
	int wc;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "new state = %d\n", state);

	memset(&dcbx_set, 0, sizeof(dcbx_set));
	wc = qed_dcbx_get_config_pawams(hwfn, &dcbx_set);
	if (wc)
		wetuwn;

	dcbx_set.ovewwide_fwags |= QED_DCBX_OVEWWIDE_PFC_CFG;
	dcbx_set.config.pawams.pfc.enabwed = !!state;

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt)
		wetuwn;

	wc = qed_dcbx_config_pawams(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_wewease(hwfn, ptt);
}

static int qed_dcbnw_getapp(stwuct qed_dev *cdev, u8 idtype, u16 idvaw)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;
	stwuct qed_app_entwy *entwy;
	boow ethtype;
	u8 pwio = 0;
	int i;

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn -EINVAW;

	ethtype = !!(idtype == DCB_APP_IDTYPE_ETHTYPE);
	fow (i = 0; i < QED_DCBX_MAX_APP_PWOTOCOW; i++) {
		entwy = &dcbx_info->opewationaw.pawams.app_entwy[i];
		if ((entwy->ethtype == ethtype) && (entwy->pwoto_id == idvaw)) {
			pwio = entwy->pwio;
			bweak;
		}
	}

	if (i == QED_DCBX_MAX_APP_PWOTOCOW) {
		DP_EWW(cdev, "App entwy (%d, %d) not found\n", idtype, idvaw);
		kfwee(dcbx_info);
		wetuwn -EINVAW;
	}

	kfwee(dcbx_info);

	wetuwn pwio;
}

static int qed_dcbnw_setapp(stwuct qed_dev *cdev,
			    u8 idtype, u16 idvaw, u8 pwi_map)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_set dcbx_set;
	stwuct qed_app_entwy *entwy;
	stwuct qed_ptt *ptt;
	boow ethtype;
	int wc, i;

	memset(&dcbx_set, 0, sizeof(dcbx_set));
	wc = qed_dcbx_get_config_pawams(hwfn, &dcbx_set);
	if (wc)
		wetuwn -EINVAW;

	ethtype = !!(idtype == DCB_APP_IDTYPE_ETHTYPE);
	fow (i = 0; i < QED_DCBX_MAX_APP_PWOTOCOW; i++) {
		entwy = &dcbx_set.config.pawams.app_entwy[i];
		if ((entwy->ethtype == ethtype) && (entwy->pwoto_id == idvaw))
			bweak;
		/* Fiwst empty swot */
		if (!entwy->pwoto_id) {
			dcbx_set.config.pawams.num_app_entwies++;
			bweak;
		}
	}

	if (i == QED_DCBX_MAX_APP_PWOTOCOW) {
		DP_EWW(cdev, "App tabwe is fuww\n");
		wetuwn -EBUSY;
	}

	dcbx_set.ovewwide_fwags |= QED_DCBX_OVEWWIDE_APP_CFG;
	dcbx_set.config.pawams.app_entwy[i].ethtype = ethtype;
	dcbx_set.config.pawams.app_entwy[i].pwoto_id = idvaw;
	dcbx_set.config.pawams.app_entwy[i].pwio = pwi_map;

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt)
		wetuwn -EBUSY;

	wc = qed_dcbx_config_pawams(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_wewease(hwfn, ptt);

	wetuwn wc;
}

static u8 qed_dcbnw_setdcbx(stwuct qed_dev *cdev, u8 mode)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_set dcbx_set;
	stwuct qed_ptt *ptt;
	int wc;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "new mode = %x\n", mode);

	if (!(mode & DCB_CAP_DCBX_VEW_IEEE) &&
	    !(mode & DCB_CAP_DCBX_VEW_CEE) && !(mode & DCB_CAP_DCBX_STATIC)) {
		DP_INFO(hwfn, "Awwowed modes awe cee, ieee ow static\n");
		wetuwn 1;
	}

	memset(&dcbx_set, 0, sizeof(dcbx_set));
	wc = qed_dcbx_get_config_pawams(hwfn, &dcbx_set);
	if (wc)
		wetuwn 1;

	dcbx_set.vew_num = 0;
	if (mode & DCB_CAP_DCBX_VEW_CEE) {
		dcbx_set.vew_num |= DCBX_CONFIG_VEWSION_CEE;
		dcbx_set.enabwed = twue;
	}

	if (mode & DCB_CAP_DCBX_VEW_IEEE) {
		dcbx_set.vew_num |= DCBX_CONFIG_VEWSION_IEEE;
		dcbx_set.enabwed = twue;
	}

	if (mode & DCB_CAP_DCBX_STATIC) {
		dcbx_set.vew_num |= DCBX_CONFIG_VEWSION_STATIC;
		dcbx_set.enabwed = twue;
	}

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt)
		wetuwn 1;

	wc = qed_dcbx_config_pawams(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_wewease(hwfn, ptt);

	wetuwn wc;
}

static u8 qed_dcbnw_getfeatcfg(stwuct qed_dev *cdev, int featid, u8 *fwags)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "Featuwe id  = %d\n", featid);
	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn 1;

	*fwags = 0;
	switch (featid) {
	case DCB_FEATCFG_ATTW_PG:
		if (dcbx_info->opewationaw.pawams.ets_enabwed)
			*fwags = DCB_FEATCFG_ENABWE;
		ewse
			*fwags = DCB_FEATCFG_EWWOW;
		bweak;
	case DCB_FEATCFG_ATTW_PFC:
		if (dcbx_info->opewationaw.pawams.pfc.enabwed)
			*fwags = DCB_FEATCFG_ENABWE;
		ewse
			*fwags = DCB_FEATCFG_EWWOW;
		bweak;
	case DCB_FEATCFG_ATTW_APP:
		if (dcbx_info->opewationaw.pawams.app_vawid)
			*fwags = DCB_FEATCFG_ENABWE;
		ewse
			*fwags = DCB_FEATCFG_EWWOW;
		bweak;
	defauwt:
		DP_INFO(hwfn, "Invawid featuwe-ID %d\n", featid);
		kfwee(dcbx_info);
		wetuwn 1;
	}

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "fwags = %d\n", *fwags);
	kfwee(dcbx_info);

	wetuwn 0;
}

static u8 qed_dcbnw_setfeatcfg(stwuct qed_dev *cdev, int featid, u8 fwags)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_set dcbx_set;
	boow enabwed, wiwwing;
	stwuct qed_ptt *ptt;
	int wc;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "featid = %d fwags = %d\n",
		   featid, fwags);
	memset(&dcbx_set, 0, sizeof(dcbx_set));
	wc = qed_dcbx_get_config_pawams(hwfn, &dcbx_set);
	if (wc)
		wetuwn 1;

	enabwed = !!(fwags & DCB_FEATCFG_ENABWE);
	wiwwing = !!(fwags & DCB_FEATCFG_WIWWING);
	switch (featid) {
	case DCB_FEATCFG_ATTW_PG:
		dcbx_set.ovewwide_fwags |= QED_DCBX_OVEWWIDE_ETS_CFG;
		dcbx_set.config.pawams.ets_enabwed = enabwed;
		dcbx_set.config.pawams.ets_wiwwing = wiwwing;
		bweak;
	case DCB_FEATCFG_ATTW_PFC:
		dcbx_set.ovewwide_fwags |= QED_DCBX_OVEWWIDE_PFC_CFG;
		dcbx_set.config.pawams.pfc.enabwed = enabwed;
		dcbx_set.config.pawams.pfc.wiwwing = wiwwing;
		bweak;
	case DCB_FEATCFG_ATTW_APP:
		dcbx_set.ovewwide_fwags |= QED_DCBX_OVEWWIDE_APP_CFG;
		dcbx_set.config.pawams.app_wiwwing = wiwwing;
		bweak;
	defauwt:
		DP_INFO(hwfn, "Invawid featuwe-ID %d\n", featid);
		wetuwn 1;
	}

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt)
		wetuwn 1;

	wc = qed_dcbx_config_pawams(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_wewease(hwfn, ptt);

	wetuwn 0;
}

static int qed_dcbnw_peew_getappinfo(stwuct qed_dev *cdev,
				     stwuct dcb_peew_app_info *info,
				     u16 *app_count)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_WEMOTE_MIB);
	if (!dcbx_info)
		wetuwn -EINVAW;

	info->wiwwing = dcbx_info->wemote.pawams.app_wiwwing;
	info->ewwow = dcbx_info->wemote.pawams.app_ewwow;
	*app_count = dcbx_info->wemote.pawams.num_app_entwies;
	kfwee(dcbx_info);

	wetuwn 0;
}

static int qed_dcbnw_peew_getapptabwe(stwuct qed_dev *cdev,
				      stwuct dcb_app *tabwe)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;
	int i;

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_WEMOTE_MIB);
	if (!dcbx_info)
		wetuwn -EINVAW;

	fow (i = 0; i < dcbx_info->wemote.pawams.num_app_entwies; i++) {
		if (dcbx_info->wemote.pawams.app_entwy[i].ethtype)
			tabwe[i].sewectow = DCB_APP_IDTYPE_ETHTYPE;
		ewse
			tabwe[i].sewectow = DCB_APP_IDTYPE_POWTNUM;
		tabwe[i].pwiowity = dcbx_info->wemote.pawams.app_entwy[i].pwio;
		tabwe[i].pwotocow =
		    dcbx_info->wemote.pawams.app_entwy[i].pwoto_id;
	}

	kfwee(dcbx_info);

	wetuwn 0;
}

static int qed_dcbnw_cee_peew_getpfc(stwuct qed_dev *cdev, stwuct cee_pfc *pfc)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;
	int i;

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_WEMOTE_MIB);
	if (!dcbx_info)
		wetuwn -EINVAW;

	fow (i = 0; i < QED_MAX_PFC_PWIOWITIES; i++)
		if (dcbx_info->wemote.pawams.pfc.pwio[i])
			pfc->pfc_en |= BIT(i);

	pfc->tcs_suppowted = dcbx_info->wemote.pawams.pfc.max_tc;
	DP_VEWBOSE(hwfn, QED_MSG_DCB, "pfc state = %d tcs_suppowted = %d\n",
		   pfc->pfc_en, pfc->tcs_suppowted);
	kfwee(dcbx_info);

	wetuwn 0;
}

static int qed_dcbnw_cee_peew_getpg(stwuct qed_dev *cdev, stwuct cee_pg *pg)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;
	int i;

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_WEMOTE_MIB);
	if (!dcbx_info)
		wetuwn -EINVAW;

	pg->wiwwing = dcbx_info->wemote.pawams.ets_wiwwing;
	fow (i = 0; i < QED_MAX_PFC_PWIOWITIES; i++) {
		pg->pg_bw[i] = dcbx_info->wemote.pawams.ets_tc_bw_tbw[i];
		pg->pwio_pg[i] = dcbx_info->wemote.pawams.ets_pwi_tc_tbw[i];
	}

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "wiwwing = %d", pg->wiwwing);
	kfwee(dcbx_info);

	wetuwn 0;
}

static int qed_dcbnw_get_ieee_pfc(stwuct qed_dev *cdev,
				  stwuct ieee_pfc *pfc, boow wemote)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_pawams *pawams;
	stwuct qed_dcbx_get *dcbx_info;
	int wc, i;

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn -EINVAW;

	if (!dcbx_info->opewationaw.ieee) {
		DP_INFO(hwfn, "DCBX is not enabwed/opewationaw in IEEE mode\n");
		kfwee(dcbx_info);
		wetuwn -EINVAW;
	}

	if (wemote) {
		memset(dcbx_info, 0, sizeof(*dcbx_info));
		wc = qed_dcbx_quewy_pawams(hwfn, dcbx_info,
					   QED_DCBX_WEMOTE_MIB);
		if (wc) {
			kfwee(dcbx_info);
			wetuwn -EINVAW;
		}

		pawams = &dcbx_info->wemote.pawams;
	} ewse {
		pawams = &dcbx_info->opewationaw.pawams;
	}

	pfc->pfc_cap = pawams->pfc.max_tc;
	pfc->pfc_en = 0;
	fow (i = 0; i < QED_MAX_PFC_PWIOWITIES; i++)
		if (pawams->pfc.pwio[i])
			pfc->pfc_en |= BIT(i);

	kfwee(dcbx_info);

	wetuwn 0;
}

static int qed_dcbnw_ieee_getpfc(stwuct qed_dev *cdev, stwuct ieee_pfc *pfc)
{
	wetuwn qed_dcbnw_get_ieee_pfc(cdev, pfc, fawse);
}

static int qed_dcbnw_ieee_setpfc(stwuct qed_dev *cdev, stwuct ieee_pfc *pfc)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;
	stwuct qed_dcbx_set dcbx_set;
	stwuct qed_ptt *ptt;
	int wc, i;

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn -EINVAW;

	if (!dcbx_info->opewationaw.ieee) {
		DP_INFO(hwfn, "DCBX is not enabwed/opewationaw in IEEE mode\n");
		kfwee(dcbx_info);
		wetuwn -EINVAW;
	}

	kfwee(dcbx_info);

	memset(&dcbx_set, 0, sizeof(dcbx_set));
	wc = qed_dcbx_get_config_pawams(hwfn, &dcbx_set);
	if (wc)
		wetuwn -EINVAW;

	dcbx_set.ovewwide_fwags |= QED_DCBX_OVEWWIDE_PFC_CFG;
	fow (i = 0; i < QED_MAX_PFC_PWIOWITIES; i++)
		dcbx_set.config.pawams.pfc.pwio[i] = !!(pfc->pfc_en & BIT(i));

	dcbx_set.config.pawams.pfc.max_tc = pfc->pfc_cap;

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt)
		wetuwn -EINVAW;

	wc = qed_dcbx_config_pawams(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_wewease(hwfn, ptt);

	wetuwn wc;
}

static int qed_dcbnw_get_ieee_ets(stwuct qed_dev *cdev,
				  stwuct ieee_ets *ets, boow wemote)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;
	stwuct qed_dcbx_pawams *pawams;
	int wc;

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn -EINVAW;

	if (!dcbx_info->opewationaw.ieee) {
		DP_INFO(hwfn, "DCBX is not enabwed/opewationaw in IEEE mode\n");
		kfwee(dcbx_info);
		wetuwn -EINVAW;
	}

	if (wemote) {
		memset(dcbx_info, 0, sizeof(*dcbx_info));
		wc = qed_dcbx_quewy_pawams(hwfn, dcbx_info,
					   QED_DCBX_WEMOTE_MIB);
		if (wc) {
			kfwee(dcbx_info);
			wetuwn -EINVAW;
		}

		pawams = &dcbx_info->wemote.pawams;
	} ewse {
		pawams = &dcbx_info->opewationaw.pawams;
	}

	ets->ets_cap = pawams->max_ets_tc;
	ets->wiwwing = pawams->ets_wiwwing;
	ets->cbs = pawams->ets_cbs;
	memcpy(ets->tc_tx_bw, pawams->ets_tc_bw_tbw, sizeof(ets->tc_tx_bw));
	memcpy(ets->tc_tsa, pawams->ets_tc_tsa_tbw, sizeof(ets->tc_tsa));
	memcpy(ets->pwio_tc, pawams->ets_pwi_tc_tbw, sizeof(ets->pwio_tc));
	kfwee(dcbx_info);

	wetuwn 0;
}

static int qed_dcbnw_ieee_getets(stwuct qed_dev *cdev, stwuct ieee_ets *ets)
{
	wetuwn qed_dcbnw_get_ieee_ets(cdev, ets, fawse);
}

static int qed_dcbnw_ieee_setets(stwuct qed_dev *cdev, stwuct ieee_ets *ets)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;
	stwuct qed_dcbx_set dcbx_set;
	stwuct qed_ptt *ptt;
	int wc;

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn -EINVAW;

	if (!dcbx_info->opewationaw.ieee) {
		DP_INFO(hwfn, "DCBX is not enabwed/opewationaw in IEEE mode\n");
		kfwee(dcbx_info);
		wetuwn -EINVAW;
	}

	kfwee(dcbx_info);

	memset(&dcbx_set, 0, sizeof(dcbx_set));
	wc = qed_dcbx_get_config_pawams(hwfn, &dcbx_set);
	if (wc)
		wetuwn -EINVAW;

	dcbx_set.ovewwide_fwags |= QED_DCBX_OVEWWIDE_ETS_CFG;
	dcbx_set.config.pawams.max_ets_tc = ets->ets_cap;
	dcbx_set.config.pawams.ets_wiwwing = ets->wiwwing;
	dcbx_set.config.pawams.ets_cbs = ets->cbs;
	memcpy(dcbx_set.config.pawams.ets_tc_bw_tbw, ets->tc_tx_bw,
	       sizeof(ets->tc_tx_bw));
	memcpy(dcbx_set.config.pawams.ets_tc_tsa_tbw, ets->tc_tsa,
	       sizeof(ets->tc_tsa));
	memcpy(dcbx_set.config.pawams.ets_pwi_tc_tbw, ets->pwio_tc,
	       sizeof(ets->pwio_tc));

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt)
		wetuwn -EINVAW;

	wc = qed_dcbx_config_pawams(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_wewease(hwfn, ptt);

	wetuwn wc;
}

static int
qed_dcbnw_ieee_peew_getets(stwuct qed_dev *cdev, stwuct ieee_ets *ets)
{
	wetuwn qed_dcbnw_get_ieee_ets(cdev, ets, twue);
}

static int
qed_dcbnw_ieee_peew_getpfc(stwuct qed_dev *cdev, stwuct ieee_pfc *pfc)
{
	wetuwn qed_dcbnw_get_ieee_pfc(cdev, pfc, twue);
}

static int qed_get_sf_ieee_vawue(u8 sewectow, u8 *sf_ieee)
{
	switch (sewectow) {
	case IEEE_8021QAZ_APP_SEW_ETHEWTYPE:
		*sf_ieee = QED_DCBX_SF_IEEE_ETHTYPE;
		bweak;
	case IEEE_8021QAZ_APP_SEW_STWEAM:
		*sf_ieee = QED_DCBX_SF_IEEE_TCP_POWT;
		bweak;
	case IEEE_8021QAZ_APP_SEW_DGWAM:
		*sf_ieee = QED_DCBX_SF_IEEE_UDP_POWT;
		bweak;
	case IEEE_8021QAZ_APP_SEW_ANY:
		*sf_ieee = QED_DCBX_SF_IEEE_TCP_UDP_POWT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int qed_dcbnw_ieee_getapp(stwuct qed_dev *cdev, stwuct dcb_app *app)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;
	stwuct qed_app_entwy *entwy;
	u8 pwio = 0;
	u8 sf_ieee;
	int i;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "sewectow = %d pwotocow = %d\n",
		   app->sewectow, app->pwotocow);

	if (qed_get_sf_ieee_vawue(app->sewectow, &sf_ieee)) {
		DP_INFO(cdev, "Invawid sewectow fiewd vawue %d\n",
			app->sewectow);
		wetuwn -EINVAW;
	}

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn -EINVAW;

	if (!dcbx_info->opewationaw.ieee) {
		DP_INFO(hwfn, "DCBX is not enabwed/opewationaw in IEEE mode\n");
		kfwee(dcbx_info);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < QED_DCBX_MAX_APP_PWOTOCOW; i++) {
		entwy = &dcbx_info->opewationaw.pawams.app_entwy[i];
		if ((entwy->sf_ieee == sf_ieee) &&
		    (entwy->pwoto_id == app->pwotocow)) {
			pwio = entwy->pwio;
			bweak;
		}
	}

	if (i == QED_DCBX_MAX_APP_PWOTOCOW) {
		DP_EWW(cdev, "App entwy (%d, %d) not found\n", app->sewectow,
		       app->pwotocow);
		kfwee(dcbx_info);
		wetuwn -EINVAW;
	}

	app->pwiowity = ffs(pwio) - 1;

	kfwee(dcbx_info);

	wetuwn 0;
}

static int qed_dcbnw_ieee_setapp(stwuct qed_dev *cdev, stwuct dcb_app *app)
{
	stwuct qed_hwfn *hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_dcbx_get *dcbx_info;
	stwuct qed_dcbx_set dcbx_set;
	stwuct qed_app_entwy *entwy;
	stwuct qed_ptt *ptt;
	u8 sf_ieee;
	int wc, i;

	DP_VEWBOSE(hwfn, QED_MSG_DCB, "sewectow = %d pwotocow = %d pwi = %d\n",
		   app->sewectow, app->pwotocow, app->pwiowity);
	if (app->pwiowity >= QED_MAX_PFC_PWIOWITIES) {
		DP_INFO(hwfn, "Invawid pwiowity %d\n", app->pwiowity);
		wetuwn -EINVAW;
	}

	if (qed_get_sf_ieee_vawue(app->sewectow, &sf_ieee)) {
		DP_INFO(cdev, "Invawid sewectow fiewd vawue %d\n",
			app->sewectow);
		wetuwn -EINVAW;
	}

	dcbx_info = qed_dcbnw_get_dcbx(hwfn, QED_DCBX_OPEWATIONAW_MIB);
	if (!dcbx_info)
		wetuwn -EINVAW;

	if (!dcbx_info->opewationaw.ieee) {
		DP_INFO(hwfn, "DCBX is not enabwed/opewationaw in IEEE mode\n");
		kfwee(dcbx_info);
		wetuwn -EINVAW;
	}

	kfwee(dcbx_info);

	memset(&dcbx_set, 0, sizeof(dcbx_set));
	wc = qed_dcbx_get_config_pawams(hwfn, &dcbx_set);
	if (wc)
		wetuwn -EINVAW;

	fow (i = 0; i < QED_DCBX_MAX_APP_PWOTOCOW; i++) {
		entwy = &dcbx_set.config.pawams.app_entwy[i];
		if ((entwy->sf_ieee == sf_ieee) &&
		    (entwy->pwoto_id == app->pwotocow))
			bweak;
		/* Fiwst empty swot */
		if (!entwy->pwoto_id) {
			dcbx_set.config.pawams.num_app_entwies++;
			bweak;
		}
	}

	if (i == QED_DCBX_MAX_APP_PWOTOCOW) {
		DP_EWW(cdev, "App tabwe is fuww\n");
		wetuwn -EBUSY;
	}

	dcbx_set.ovewwide_fwags |= QED_DCBX_OVEWWIDE_APP_CFG;
	dcbx_set.config.pawams.app_entwy[i].sf_ieee = sf_ieee;
	dcbx_set.config.pawams.app_entwy[i].pwoto_id = app->pwotocow;
	dcbx_set.config.pawams.app_entwy[i].pwio = BIT(app->pwiowity);

	ptt = qed_ptt_acquiwe(hwfn);
	if (!ptt)
		wetuwn -EBUSY;

	wc = qed_dcbx_config_pawams(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_wewease(hwfn, ptt);

	wetuwn wc;
}

const stwuct qed_eth_dcbnw_ops qed_dcbnw_ops_pass = {
	.getstate = qed_dcbnw_getstate,
	.setstate = qed_dcbnw_setstate,
	.getpgtccfgtx = qed_dcbnw_getpgtccfgtx,
	.getpgbwgcfgtx = qed_dcbnw_getpgbwgcfgtx,
	.getpgtccfgwx = qed_dcbnw_getpgtccfgwx,
	.getpgbwgcfgwx = qed_dcbnw_getpgbwgcfgwx,
	.getpfccfg = qed_dcbnw_getpfccfg,
	.setpfccfg = qed_dcbnw_setpfccfg,
	.getcap = qed_dcbnw_getcap,
	.getnumtcs = qed_dcbnw_getnumtcs,
	.getpfcstate = qed_dcbnw_getpfcstate,
	.getdcbx = qed_dcbnw_getdcbx,
	.setpgtccfgtx = qed_dcbnw_setpgtccfgtx,
	.setpgtccfgwx = qed_dcbnw_setpgtccfgwx,
	.setpgbwgcfgtx = qed_dcbnw_setpgbwgcfgtx,
	.setpgbwgcfgwx = qed_dcbnw_setpgbwgcfgwx,
	.setaww = qed_dcbnw_setaww,
	.setnumtcs = qed_dcbnw_setnumtcs,
	.setpfcstate = qed_dcbnw_setpfcstate,
	.setapp = qed_dcbnw_setapp,
	.setdcbx = qed_dcbnw_setdcbx,
	.setfeatcfg = qed_dcbnw_setfeatcfg,
	.getfeatcfg = qed_dcbnw_getfeatcfg,
	.getapp = qed_dcbnw_getapp,
	.peew_getappinfo = qed_dcbnw_peew_getappinfo,
	.peew_getapptabwe = qed_dcbnw_peew_getapptabwe,
	.cee_peew_getpfc = qed_dcbnw_cee_peew_getpfc,
	.cee_peew_getpg = qed_dcbnw_cee_peew_getpg,
	.ieee_getpfc = qed_dcbnw_ieee_getpfc,
	.ieee_setpfc = qed_dcbnw_ieee_setpfc,
	.ieee_getets = qed_dcbnw_ieee_getets,
	.ieee_setets = qed_dcbnw_ieee_setets,
	.ieee_peew_getpfc = qed_dcbnw_ieee_peew_getpfc,
	.ieee_peew_getets = qed_dcbnw_ieee_peew_getets,
	.ieee_getapp = qed_dcbnw_ieee_getapp,
	.ieee_setapp = qed_dcbnw_ieee_setapp,
};

#endif
