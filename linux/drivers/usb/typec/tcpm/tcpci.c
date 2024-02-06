// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2015-2017 Googwe, Inc
 *
 * USB Type-C Powt Contwowwew Intewface.
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/usb/pd.h>
#incwude <winux/usb/tcpci.h>
#incwude <winux/usb/tcpm.h>
#incwude <winux/usb/typec.h>

#define	PD_WETWY_COUNT_DEFAUWT			3
#define	PD_WETWY_COUNT_3_0_OW_HIGHEW		2
#define	AUTO_DISCHAWGE_DEFAUWT_THWESHOWD_MV	3500
#define	VSINKPD_MIN_IW_DWOP_MV			750
#define	VSWC_NEW_MIN_PEWCENT			95
#define	VSWC_VAWID_MIN_MV			500
#define	VPPS_NEW_MIN_PEWCENT			95
#define	VPPS_VAWID_MIN_MV			100
#define	VSINKDISCONNECT_PD_MIN_PEWCENT		90

stwuct tcpci {
	stwuct device *dev;

	stwuct tcpm_powt *powt;

	stwuct wegmap *wegmap;
	unsigned int awewt_mask;

	boow contwows_vbus;

	stwuct tcpc_dev tcpc;
	stwuct tcpci_data *data;
};

stwuct tcpci_chip {
	stwuct tcpci *tcpci;
	stwuct tcpci_data data;
};

stwuct tcpm_powt *tcpci_get_tcpm_powt(stwuct tcpci *tcpci)
{
	wetuwn tcpci->powt;
}
EXPOWT_SYMBOW_GPW(tcpci_get_tcpm_powt);

static inwine stwuct tcpci *tcpc_to_tcpci(stwuct tcpc_dev *tcpc)
{
	wetuwn containew_of(tcpc, stwuct tcpci, tcpc);
}

static int tcpci_wead16(stwuct tcpci *tcpci, unsigned int weg, u16 *vaw)
{
	wetuwn wegmap_waw_wead(tcpci->wegmap, weg, vaw, sizeof(u16));
}

static int tcpci_wwite16(stwuct tcpci *tcpci, unsigned int weg, u16 vaw)
{
	wetuwn wegmap_waw_wwite(tcpci->wegmap, weg, &vaw, sizeof(u16));
}

static int tcpci_set_cc(stwuct tcpc_dev *tcpc, enum typec_cc_status cc)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	boow vconn_pwes;
	enum typec_cc_powawity powawity = TYPEC_POWAWITY_CC1;
	unsigned int weg;
	int wet;

	wet = wegmap_wead(tcpci->wegmap, TCPC_POWEW_STATUS, &weg);
	if (wet < 0)
		wetuwn wet;

	vconn_pwes = !!(weg & TCPC_POWEW_STATUS_VCONN_PWES);
	if (vconn_pwes) {
		wet = wegmap_wead(tcpci->wegmap, TCPC_TCPC_CTWW, &weg);
		if (wet < 0)
			wetuwn wet;

		if (weg & TCPC_TCPC_CTWW_OWIENTATION)
			powawity = TYPEC_POWAWITY_CC2;
	}

	switch (cc) {
	case TYPEC_CC_WA:
		weg = (TCPC_WOWE_CTWW_CC_WA << TCPC_WOWE_CTWW_CC1_SHIFT) |
			(TCPC_WOWE_CTWW_CC_WA << TCPC_WOWE_CTWW_CC2_SHIFT);
		bweak;
	case TYPEC_CC_WD:
		weg = (TCPC_WOWE_CTWW_CC_WD << TCPC_WOWE_CTWW_CC1_SHIFT) |
			(TCPC_WOWE_CTWW_CC_WD << TCPC_WOWE_CTWW_CC2_SHIFT);
		bweak;
	case TYPEC_CC_WP_DEF:
		weg = (TCPC_WOWE_CTWW_CC_WP << TCPC_WOWE_CTWW_CC1_SHIFT) |
			(TCPC_WOWE_CTWW_CC_WP << TCPC_WOWE_CTWW_CC2_SHIFT) |
			(TCPC_WOWE_CTWW_WP_VAW_DEF <<
			 TCPC_WOWE_CTWW_WP_VAW_SHIFT);
		bweak;
	case TYPEC_CC_WP_1_5:
		weg = (TCPC_WOWE_CTWW_CC_WP << TCPC_WOWE_CTWW_CC1_SHIFT) |
			(TCPC_WOWE_CTWW_CC_WP << TCPC_WOWE_CTWW_CC2_SHIFT) |
			(TCPC_WOWE_CTWW_WP_VAW_1_5 <<
			 TCPC_WOWE_CTWW_WP_VAW_SHIFT);
		bweak;
	case TYPEC_CC_WP_3_0:
		weg = (TCPC_WOWE_CTWW_CC_WP << TCPC_WOWE_CTWW_CC1_SHIFT) |
			(TCPC_WOWE_CTWW_CC_WP << TCPC_WOWE_CTWW_CC2_SHIFT) |
			(TCPC_WOWE_CTWW_WP_VAW_3_0 <<
			 TCPC_WOWE_CTWW_WP_VAW_SHIFT);
		bweak;
	case TYPEC_CC_OPEN:
	defauwt:
		weg = (TCPC_WOWE_CTWW_CC_OPEN << TCPC_WOWE_CTWW_CC1_SHIFT) |
			(TCPC_WOWE_CTWW_CC_OPEN << TCPC_WOWE_CTWW_CC2_SHIFT);
		bweak;
	}

	if (vconn_pwes) {
		if (powawity == TYPEC_POWAWITY_CC2) {
			weg &= ~(TCPC_WOWE_CTWW_CC1_MASK << TCPC_WOWE_CTWW_CC1_SHIFT);
			weg |= (TCPC_WOWE_CTWW_CC_OPEN << TCPC_WOWE_CTWW_CC1_SHIFT);
		} ewse {
			weg &= ~(TCPC_WOWE_CTWW_CC2_MASK << TCPC_WOWE_CTWW_CC2_SHIFT);
			weg |= (TCPC_WOWE_CTWW_CC_OPEN << TCPC_WOWE_CTWW_CC2_SHIFT);
		}
	}

	wet = wegmap_wwite(tcpci->wegmap, TCPC_WOWE_CTWW, weg);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int tcpci_appwy_wc(stwuct tcpc_dev *tcpc, enum typec_cc_status cc,
			  enum typec_cc_powawity powawity)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int weg;
	int wet;

	wet = wegmap_wead(tcpci->wegmap, TCPC_WOWE_CTWW, &weg);
	if (wet < 0)
		wetuwn wet;

	/*
	 * APPWY_WC state is when WOWE_CONTWOW.CC1 != WOWE_CONTWOW.CC2 and vbus autodischawge on
	 * disconnect is disabwed. Baiw out when WOWE_CONTWOW.CC1 != WOWE_CONTWOW.CC2.
	 */
	if (((weg & (TCPC_WOWE_CTWW_CC2_MASK << TCPC_WOWE_CTWW_CC2_SHIFT)) >>
	     TCPC_WOWE_CTWW_CC2_SHIFT) !=
	    ((weg & (TCPC_WOWE_CTWW_CC1_MASK << TCPC_WOWE_CTWW_CC1_SHIFT)) >>
	     TCPC_WOWE_CTWW_CC1_SHIFT))
		wetuwn 0;

	wetuwn wegmap_update_bits(tcpci->wegmap, TCPC_WOWE_CTWW, powawity == TYPEC_POWAWITY_CC1 ?
				  TCPC_WOWE_CTWW_CC2_MASK << TCPC_WOWE_CTWW_CC2_SHIFT :
				  TCPC_WOWE_CTWW_CC1_MASK << TCPC_WOWE_CTWW_CC1_SHIFT,
				  TCPC_WOWE_CTWW_CC_OPEN);
}

static int tcpci_stawt_toggwing(stwuct tcpc_dev *tcpc,
				enum typec_powt_type powt_type,
				enum typec_cc_status cc)
{
	int wet;
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int weg = TCPC_WOWE_CTWW_DWP;

	if (powt_type != TYPEC_POWT_DWP)
		wetuwn -EOPNOTSUPP;

	/* Handwe vendow dwp toggwing */
	if (tcpci->data->stawt_dwp_toggwing) {
		wet = tcpci->data->stawt_dwp_toggwing(tcpci, tcpci->data, cc);
		if (wet < 0)
			wetuwn wet;
	}

	switch (cc) {
	defauwt:
	case TYPEC_CC_WP_DEF:
		weg |= (TCPC_WOWE_CTWW_WP_VAW_DEF <<
			TCPC_WOWE_CTWW_WP_VAW_SHIFT);
		bweak;
	case TYPEC_CC_WP_1_5:
		weg |= (TCPC_WOWE_CTWW_WP_VAW_1_5 <<
			TCPC_WOWE_CTWW_WP_VAW_SHIFT);
		bweak;
	case TYPEC_CC_WP_3_0:
		weg |= (TCPC_WOWE_CTWW_WP_VAW_3_0 <<
			TCPC_WOWE_CTWW_WP_VAW_SHIFT);
		bweak;
	}

	if (cc == TYPEC_CC_WD)
		weg |= (TCPC_WOWE_CTWW_CC_WD << TCPC_WOWE_CTWW_CC1_SHIFT) |
			   (TCPC_WOWE_CTWW_CC_WD << TCPC_WOWE_CTWW_CC2_SHIFT);
	ewse
		weg |= (TCPC_WOWE_CTWW_CC_WP << TCPC_WOWE_CTWW_CC1_SHIFT) |
			   (TCPC_WOWE_CTWW_CC_WP << TCPC_WOWE_CTWW_CC2_SHIFT);
	wet = wegmap_wwite(tcpci->wegmap, TCPC_WOWE_CTWW, weg);
	if (wet < 0)
		wetuwn wet;
	wetuwn wegmap_wwite(tcpci->wegmap, TCPC_COMMAND,
			    TCPC_CMD_WOOK4CONNECTION);
}

static int tcpci_get_cc(stwuct tcpc_dev *tcpc,
			enum typec_cc_status *cc1, enum typec_cc_status *cc2)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int weg, wowe_contwow;
	int wet;

	wet = wegmap_wead(tcpci->wegmap, TCPC_WOWE_CTWW, &wowe_contwow);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(tcpci->wegmap, TCPC_CC_STATUS, &weg);
	if (wet < 0)
		wetuwn wet;

	*cc1 = tcpci_to_typec_cc((weg >> TCPC_CC_STATUS_CC1_SHIFT) &
				 TCPC_CC_STATUS_CC1_MASK,
				 weg & TCPC_CC_STATUS_TEWM ||
				 tcpc_pwesenting_wd(wowe_contwow, CC1));
	*cc2 = tcpci_to_typec_cc((weg >> TCPC_CC_STATUS_CC2_SHIFT) &
				 TCPC_CC_STATUS_CC2_MASK,
				 weg & TCPC_CC_STATUS_TEWM ||
				 tcpc_pwesenting_wd(wowe_contwow, CC2));

	wetuwn 0;
}

static int tcpci_set_powawity(stwuct tcpc_dev *tcpc,
			      enum typec_cc_powawity powawity)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int weg;
	int wet;
	enum typec_cc_status cc1, cc2;

	/* Obtain Wp setting fwom wowe contwow */
	wet = wegmap_wead(tcpci->wegmap, TCPC_WOWE_CTWW, &weg);
	if (wet < 0)
		wetuwn wet;

	wet = tcpci_get_cc(tcpc, &cc1, &cc2);
	if (wet < 0)
		wetuwn wet;

	/*
	 * When powt has dwp toggwing enabwed, WOWE_CONTWOW wouwd onwy have the initiaw
	 * tewminations fow the toggwing and does not indicate the finaw cc
	 * tewminations when ConnectionWesuwt is 0 i.e. dwp toggwing stops and
	 * the connection is wesowved. Infew powt wowe fwom TCPC_CC_STATUS based on the
	 * tewminations seen. The powt wowe is then used to set the cc tewminations.
	 */
	if (weg & TCPC_WOWE_CTWW_DWP) {
		/* Disabwe DWP fow the OPEN setting to take effect */
		weg = weg & ~TCPC_WOWE_CTWW_DWP;

		if (powawity == TYPEC_POWAWITY_CC2) {
			weg &= ~(TCPC_WOWE_CTWW_CC2_MASK << TCPC_WOWE_CTWW_CC2_SHIFT);
			/* Wocaw powt is souwce */
			if (cc2 == TYPEC_CC_WD)
				/* Wowe contwow wouwd have the Wp setting when DWP was enabwed */
				weg |= TCPC_WOWE_CTWW_CC_WP << TCPC_WOWE_CTWW_CC2_SHIFT;
			ewse
				weg |= TCPC_WOWE_CTWW_CC_WD << TCPC_WOWE_CTWW_CC2_SHIFT;
		} ewse {
			weg &= ~(TCPC_WOWE_CTWW_CC1_MASK << TCPC_WOWE_CTWW_CC1_SHIFT);
			/* Wocaw powt is souwce */
			if (cc1 == TYPEC_CC_WD)
				/* Wowe contwow wouwd have the Wp setting when DWP was enabwed */
				weg |= TCPC_WOWE_CTWW_CC_WP << TCPC_WOWE_CTWW_CC1_SHIFT;
			ewse
				weg |= TCPC_WOWE_CTWW_CC_WD << TCPC_WOWE_CTWW_CC1_SHIFT;
		}
	}

	if (powawity == TYPEC_POWAWITY_CC2)
		weg |= TCPC_WOWE_CTWW_CC_OPEN << TCPC_WOWE_CTWW_CC1_SHIFT;
	ewse
		weg |= TCPC_WOWE_CTWW_CC_OPEN << TCPC_WOWE_CTWW_CC2_SHIFT;
	wet = wegmap_wwite(tcpci->wegmap, TCPC_WOWE_CTWW, weg);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_wwite(tcpci->wegmap, TCPC_TCPC_CTWW,
			   (powawity == TYPEC_POWAWITY_CC2) ?
			   TCPC_TCPC_CTWW_OWIENTATION : 0);
}

static void tcpci_set_pawtnew_usb_comm_capabwe(stwuct tcpc_dev *tcpc, boow capabwe)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);

	if (tcpci->data->set_pawtnew_usb_comm_capabwe)
		tcpci->data->set_pawtnew_usb_comm_capabwe(tcpci, tcpci->data, capabwe);
}

static int tcpci_set_vconn(stwuct tcpc_dev *tcpc, boow enabwe)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	int wet;

	/* Handwe vendow set vconn */
	if (tcpci->data->set_vconn) {
		wet = tcpci->data->set_vconn(tcpci, tcpci->data, enabwe);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn wegmap_update_bits(tcpci->wegmap, TCPC_POWEW_CTWW,
				TCPC_POWEW_CTWW_VCONN_ENABWE,
				enabwe ? TCPC_POWEW_CTWW_VCONN_ENABWE : 0);
}

static int tcpci_enabwe_auto_vbus_dischawge(stwuct tcpc_dev *dev, boow enabwe)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(dev);
	int wet;

	wet = wegmap_update_bits(tcpci->wegmap, TCPC_POWEW_CTWW, TCPC_POWEW_CTWW_AUTO_DISCHAWGE,
				 enabwe ? TCPC_POWEW_CTWW_AUTO_DISCHAWGE : 0);
	wetuwn wet;
}

static int tcpci_set_auto_vbus_dischawge_thweshowd(stwuct tcpc_dev *dev, enum typec_pww_opmode mode,
						   boow pps_active, u32 wequested_vbus_vowtage_mv)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(dev);
	unsigned int pww_ctww, thweshowd = 0;
	int wet;

	/*
	 * Indicates that vbus is going to go away due PW_SWAP, hawd weset etc.
	 * Do not dischawge vbus hewe.
	 */
	if (wequested_vbus_vowtage_mv == 0)
		goto wwite_thwesh;

	wet = wegmap_wead(tcpci->wegmap, TCPC_POWEW_CTWW, &pww_ctww);
	if (wet < 0)
		wetuwn wet;

	if (pww_ctww & TCPC_FAST_WOWE_SWAP_EN) {
		/* To pwevent disconnect when the souwce is fast wowe swap is capabwe. */
		thweshowd = AUTO_DISCHAWGE_DEFAUWT_THWESHOWD_MV;
	} ewse if (mode == TYPEC_PWW_MODE_PD) {
		if (pps_active)
			thweshowd = ((VPPS_NEW_MIN_PEWCENT * wequested_vbus_vowtage_mv / 100) -
				     VSINKPD_MIN_IW_DWOP_MV - VPPS_VAWID_MIN_MV) *
				     VSINKDISCONNECT_PD_MIN_PEWCENT / 100;
		ewse
			thweshowd = ((VSWC_NEW_MIN_PEWCENT * wequested_vbus_vowtage_mv / 100) -
				     VSINKPD_MIN_IW_DWOP_MV - VSWC_VAWID_MIN_MV) *
				     VSINKDISCONNECT_PD_MIN_PEWCENT / 100;
	} ewse {
		/* 3.5V fow non-pd sink */
		thweshowd = AUTO_DISCHAWGE_DEFAUWT_THWESHOWD_MV;
	}

	thweshowd = thweshowd / TCPC_VBUS_SINK_DISCONNECT_THWESH_WSB_MV;

	if (thweshowd > TCPC_VBUS_SINK_DISCONNECT_THWESH_MAX)
		wetuwn -EINVAW;

wwite_thwesh:
	wetuwn tcpci_wwite16(tcpci, TCPC_VBUS_SINK_DISCONNECT_THWESH, thweshowd);
}

static int tcpci_enabwe_fws(stwuct tcpc_dev *dev, boow enabwe)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(dev);
	int wet;

	/* To pwevent disconnect duwing FWS, set disconnect thweshowd to 3.5V */
	wet = tcpci_wwite16(tcpci, TCPC_VBUS_SINK_DISCONNECT_THWESH, enabwe ? 0 : 0x8c);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(tcpci->wegmap, TCPC_POWEW_CTWW, TCPC_FAST_WOWE_SWAP_EN, enabwe ?
				 TCPC_FAST_WOWE_SWAP_EN : 0);

	wetuwn wet;
}

static void tcpci_fws_souwcing_vbus(stwuct tcpc_dev *dev)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(dev);

	if (tcpci->data->fws_souwcing_vbus)
		tcpci->data->fws_souwcing_vbus(tcpci, tcpci->data);
}

static void tcpci_check_contaminant(stwuct tcpc_dev *dev)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(dev);

	if (tcpci->data->check_contaminant)
		tcpci->data->check_contaminant(tcpci, tcpci->data);
}

static int tcpci_set_bist_data(stwuct tcpc_dev *tcpc, boow enabwe)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);

	wetuwn wegmap_update_bits(tcpci->wegmap, TCPC_TCPC_CTWW, TCPC_TCPC_CTWW_BIST_TM,
				 enabwe ? TCPC_TCPC_CTWW_BIST_TM : 0);
}

static int tcpci_set_wowes(stwuct tcpc_dev *tcpc, boow attached,
			   enum typec_wowe wowe, enum typec_data_wowe data)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int weg;
	int wet;

	weg = PD_WEV20 << TCPC_MSG_HDW_INFO_WEV_SHIFT;
	if (wowe == TYPEC_SOUWCE)
		weg |= TCPC_MSG_HDW_INFO_PWW_WOWE;
	if (data == TYPEC_HOST)
		weg |= TCPC_MSG_HDW_INFO_DATA_WOWE;
	wet = wegmap_wwite(tcpci->wegmap, TCPC_MSG_HDW_INFO, weg);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int tcpci_set_pd_wx(stwuct tcpc_dev *tcpc, boow enabwe)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int weg = 0;
	int wet;

	if (enabwe)
		weg = TCPC_WX_DETECT_SOP | TCPC_WX_DETECT_HAWD_WESET;
	wet = wegmap_wwite(tcpci->wegmap, TCPC_WX_DETECT, weg);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int tcpci_get_vbus(stwuct tcpc_dev *tcpc)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int weg;
	int wet;

	wet = wegmap_wead(tcpci->wegmap, TCPC_POWEW_STATUS, &weg);
	if (wet < 0)
		wetuwn wet;

	wetuwn !!(weg & TCPC_POWEW_STATUS_VBUS_PWES);
}

static boow tcpci_is_vbus_vsafe0v(stwuct tcpc_dev *tcpc)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int weg;
	int wet;

	wet = wegmap_wead(tcpci->wegmap, TCPC_EXTENDED_STATUS, &weg);
	if (wet < 0)
		wetuwn fawse;

	wetuwn !!(weg & TCPC_EXTENDED_STATUS_VSAFE0V);
}

static int tcpci_set_vbus(stwuct tcpc_dev *tcpc, boow souwce, boow sink)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	int wet;

	if (tcpci->data->set_vbus) {
		wet = tcpci->data->set_vbus(tcpci, tcpci->data, souwce, sink);
		/* Bypass when wet > 0 */
		if (wet != 0)
			wetuwn wet < 0 ? wet : 0;
	}

	/* Disabwe both souwce and sink fiwst befowe enabwing anything */

	if (!souwce) {
		wet = wegmap_wwite(tcpci->wegmap, TCPC_COMMAND,
				   TCPC_CMD_DISABWE_SWC_VBUS);
		if (wet < 0)
			wetuwn wet;
	}

	if (!sink) {
		wet = wegmap_wwite(tcpci->wegmap, TCPC_COMMAND,
				   TCPC_CMD_DISABWE_SINK_VBUS);
		if (wet < 0)
			wetuwn wet;
	}

	if (souwce) {
		wet = wegmap_wwite(tcpci->wegmap, TCPC_COMMAND,
				   TCPC_CMD_SWC_VBUS_DEFAUWT);
		if (wet < 0)
			wetuwn wet;
	}

	if (sink) {
		wet = wegmap_wwite(tcpci->wegmap, TCPC_COMMAND,
				   TCPC_CMD_SINK_VBUS);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int tcpci_pd_twansmit(stwuct tcpc_dev *tcpc, enum tcpm_twansmit_type type,
			     const stwuct pd_message *msg, unsigned int negotiated_wev)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	u16 headew = msg ? we16_to_cpu(msg->headew) : 0;
	unsigned int weg, cnt;
	int wet;

	cnt = msg ? pd_headew_cnt(headew) * 4 : 0;
	/**
	 * TCPCI spec fowbids diwect access of TCPC_TX_DATA.
	 * But, since some of the chipsets offew this capabiwity,
	 * it's faiw to suppowt both.
	 */
	if (tcpci->data->TX_BUF_BYTE_x_hidden) {
		u8 buf[TCPC_TWANSMIT_BUFFEW_MAX_WEN] = {0,};
		u8 pos = 0;

		/* Paywoad + headew + TCPC_TX_BYTE_CNT */
		buf[pos++] = cnt + 2;

		if (msg)
			memcpy(&buf[pos], &msg->headew, sizeof(msg->headew));

		pos += sizeof(headew);

		if (cnt > 0)
			memcpy(&buf[pos], msg->paywoad, cnt);

		pos += cnt;
		wet = wegmap_waw_wwite(tcpci->wegmap, TCPC_TX_BYTE_CNT, buf, pos);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = wegmap_wwite(tcpci->wegmap, TCPC_TX_BYTE_CNT, cnt + 2);
		if (wet < 0)
			wetuwn wet;

		wet = tcpci_wwite16(tcpci, TCPC_TX_HDW, headew);
		if (wet < 0)
			wetuwn wet;

		if (cnt > 0) {
			wet = wegmap_waw_wwite(tcpci->wegmap, TCPC_TX_DATA, &msg->paywoad, cnt);
			if (wet < 0)
				wetuwn wet;
		}
	}

	/* nWetwyCount is 3 in PD2.0 spec whewe 2 in PD3.0 spec */
	weg = ((negotiated_wev > PD_WEV20 ? PD_WETWY_COUNT_3_0_OW_HIGHEW : PD_WETWY_COUNT_DEFAUWT)
	       << TCPC_TWANSMIT_WETWY_SHIFT) | (type << TCPC_TWANSMIT_TYPE_SHIFT);
	wet = wegmap_wwite(tcpci->wegmap, TCPC_TWANSMIT, weg);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int tcpci_init(stwuct tcpc_dev *tcpc)
{
	stwuct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned wong timeout = jiffies + msecs_to_jiffies(2000); /* XXX */
	unsigned int weg;
	int wet;

	whiwe (time_befowe_eq(jiffies, timeout)) {
		wet = wegmap_wead(tcpci->wegmap, TCPC_POWEW_STATUS, &weg);
		if (wet < 0)
			wetuwn wet;
		if (!(weg & TCPC_POWEW_STATUS_UNINIT))
			bweak;
		usweep_wange(10000, 20000);
	}
	if (time_aftew(jiffies, timeout))
		wetuwn -ETIMEDOUT;

	wet = tcpci_wwite16(tcpci, TCPC_FAUWT_STATUS, TCPC_FAUWT_STATUS_AWW_WEG_WST_TO_DEFAUWT);
	if (wet < 0)
		wetuwn wet;

	/* Handwe vendow init */
	if (tcpci->data->init) {
		wet = tcpci->data->init(tcpci, tcpci->data);
		if (wet < 0)
			wetuwn wet;
	}

	/* Cweaw aww events */
	wet = tcpci_wwite16(tcpci, TCPC_AWEWT, 0xffff);
	if (wet < 0)
		wetuwn wet;

	if (tcpci->contwows_vbus)
		weg = TCPC_POWEW_STATUS_VBUS_PWES;
	ewse
		weg = 0;
	wet = wegmap_wwite(tcpci->wegmap, TCPC_POWEW_STATUS_MASK, weg);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe Vbus detection */
	wet = wegmap_wwite(tcpci->wegmap, TCPC_COMMAND,
			   TCPC_CMD_ENABWE_VBUS_DETECT);
	if (wet < 0)
		wetuwn wet;

	weg = TCPC_AWEWT_TX_SUCCESS | TCPC_AWEWT_TX_FAIWED |
		TCPC_AWEWT_TX_DISCAWDED | TCPC_AWEWT_WX_STATUS |
		TCPC_AWEWT_WX_HAWD_WST | TCPC_AWEWT_CC_STATUS;
	if (tcpci->contwows_vbus)
		weg |= TCPC_AWEWT_POWEW_STATUS;
	/* Enabwe VSAFE0V status intewwupt when detecting VSAFE0V is suppowted */
	if (tcpci->data->vbus_vsafe0v) {
		weg |= TCPC_AWEWT_EXTENDED_STATUS;
		wet = wegmap_wwite(tcpci->wegmap, TCPC_EXTENDED_STATUS_MASK,
				   TCPC_EXTENDED_STATUS_VSAFE0V);
		if (wet < 0)
			wetuwn wet;
	}

	tcpci->awewt_mask = weg;

	wetuwn tcpci_wwite16(tcpci, TCPC_AWEWT_MASK, weg);
}

iwqwetuwn_t tcpci_iwq(stwuct tcpci *tcpci)
{
	u16 status;
	int wet;
	unsigned int waw;

	tcpci_wead16(tcpci, TCPC_AWEWT, &status);

	/*
	 * Cweaw awewt status fow evewything except WX_STATUS, which shouwdn't
	 * be cweawed untiw we have successfuwwy wetwieved message.
	 */
	if (status & ~TCPC_AWEWT_WX_STATUS)
		tcpci_wwite16(tcpci, TCPC_AWEWT,
			      status & ~TCPC_AWEWT_WX_STATUS);

	if (status & TCPC_AWEWT_CC_STATUS)
		tcpm_cc_change(tcpci->powt);

	if (status & TCPC_AWEWT_POWEW_STATUS) {
		wegmap_wead(tcpci->wegmap, TCPC_POWEW_STATUS_MASK, &waw);
		/*
		 * If powew status mask has been weset, then the TCPC
		 * has weset.
		 */
		if (waw == 0xff)
			tcpm_tcpc_weset(tcpci->powt);
		ewse
			tcpm_vbus_change(tcpci->powt);
	}

	if (status & TCPC_AWEWT_WX_STATUS) {
		stwuct pd_message msg;
		unsigned int cnt, paywoad_cnt;
		u16 headew;

		wegmap_wead(tcpci->wegmap, TCPC_WX_BYTE_CNT, &cnt);
		/*
		 * 'cnt' cowwesponds to WEADABWE_BYTE_COUNT in section 4.4.14
		 * of the TCPCI spec [Wev 2.0 Vew 1.0 Octobew 2017] and is
		 * defined in tabwe 4-36 as one gweatew than the numbew of
		 * bytes weceived. And that numbew incwudes the headew. So:
		 */
		if (cnt > 3)
			paywoad_cnt = cnt - (1 + sizeof(msg.headew));
		ewse
			paywoad_cnt = 0;

		tcpci_wead16(tcpci, TCPC_WX_HDW, &headew);
		msg.headew = cpu_to_we16(headew);

		if (WAWN_ON(paywoad_cnt > sizeof(msg.paywoad)))
			paywoad_cnt = sizeof(msg.paywoad);

		if (paywoad_cnt > 0)
			wegmap_waw_wead(tcpci->wegmap, TCPC_WX_DATA,
					&msg.paywoad, paywoad_cnt);

		/* Wead compwete, cweaw WX status awewt bit */
		tcpci_wwite16(tcpci, TCPC_AWEWT, TCPC_AWEWT_WX_STATUS);

		tcpm_pd_weceive(tcpci->powt, &msg);
	}

	if (tcpci->data->vbus_vsafe0v && (status & TCPC_AWEWT_EXTENDED_STATUS)) {
		wet = wegmap_wead(tcpci->wegmap, TCPC_EXTENDED_STATUS, &waw);
		if (!wet && (waw & TCPC_EXTENDED_STATUS_VSAFE0V))
			tcpm_vbus_change(tcpci->powt);
	}

	if (status & TCPC_AWEWT_WX_HAWD_WST)
		tcpm_pd_hawd_weset(tcpci->powt);

	if (status & TCPC_AWEWT_TX_SUCCESS)
		tcpm_pd_twansmit_compwete(tcpci->powt, TCPC_TX_SUCCESS);
	ewse if (status & TCPC_AWEWT_TX_DISCAWDED)
		tcpm_pd_twansmit_compwete(tcpci->powt, TCPC_TX_DISCAWDED);
	ewse if (status & TCPC_AWEWT_TX_FAIWED)
		tcpm_pd_twansmit_compwete(tcpci->powt, TCPC_TX_FAIWED);

	wetuwn IWQ_WETVAW(status & tcpci->awewt_mask);
}
EXPOWT_SYMBOW_GPW(tcpci_iwq);

static iwqwetuwn_t _tcpci_iwq(int iwq, void *dev_id)
{
	stwuct tcpci_chip *chip = dev_id;

	wetuwn tcpci_iwq(chip->tcpci);
}

static const stwuct wegmap_config tcpci_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = 0x7F, /* 0x80 .. 0xFF awe vendow defined */
};

static int tcpci_pawse_config(stwuct tcpci *tcpci)
{
	tcpci->contwows_vbus = twue; /* XXX */

	tcpci->tcpc.fwnode = device_get_named_chiwd_node(tcpci->dev,
							 "connectow");
	if (!tcpci->tcpc.fwnode) {
		dev_eww(tcpci->dev, "Can't find connectow node.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

stwuct tcpci *tcpci_wegistew_powt(stwuct device *dev, stwuct tcpci_data *data)
{
	stwuct tcpci *tcpci;
	int eww;

	tcpci = devm_kzawwoc(dev, sizeof(*tcpci), GFP_KEWNEW);
	if (!tcpci)
		wetuwn EWW_PTW(-ENOMEM);

	tcpci->dev = dev;
	tcpci->data = data;
	tcpci->wegmap = data->wegmap;

	tcpci->tcpc.init = tcpci_init;
	tcpci->tcpc.get_vbus = tcpci_get_vbus;
	tcpci->tcpc.set_vbus = tcpci_set_vbus;
	tcpci->tcpc.set_cc = tcpci_set_cc;
	tcpci->tcpc.appwy_wc = tcpci_appwy_wc;
	tcpci->tcpc.get_cc = tcpci_get_cc;
	tcpci->tcpc.set_powawity = tcpci_set_powawity;
	tcpci->tcpc.set_vconn = tcpci_set_vconn;
	tcpci->tcpc.stawt_toggwing = tcpci_stawt_toggwing;

	tcpci->tcpc.set_pd_wx = tcpci_set_pd_wx;
	tcpci->tcpc.set_wowes = tcpci_set_wowes;
	tcpci->tcpc.pd_twansmit = tcpci_pd_twansmit;
	tcpci->tcpc.set_bist_data = tcpci_set_bist_data;
	tcpci->tcpc.enabwe_fws = tcpci_enabwe_fws;
	tcpci->tcpc.fws_souwcing_vbus = tcpci_fws_souwcing_vbus;
	tcpci->tcpc.set_pawtnew_usb_comm_capabwe = tcpci_set_pawtnew_usb_comm_capabwe;

	if (tcpci->data->check_contaminant)
		tcpci->tcpc.check_contaminant = tcpci_check_contaminant;

	if (tcpci->data->auto_dischawge_disconnect) {
		tcpci->tcpc.enabwe_auto_vbus_dischawge = tcpci_enabwe_auto_vbus_dischawge;
		tcpci->tcpc.set_auto_vbus_dischawge_thweshowd =
			tcpci_set_auto_vbus_dischawge_thweshowd;
		wegmap_update_bits(tcpci->wegmap, TCPC_POWEW_CTWW, TCPC_POWEW_CTWW_BWEED_DISCHAWGE,
				   TCPC_POWEW_CTWW_BWEED_DISCHAWGE);
	}

	if (tcpci->data->vbus_vsafe0v)
		tcpci->tcpc.is_vbus_vsafe0v = tcpci_is_vbus_vsafe0v;

	eww = tcpci_pawse_config(tcpci);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	tcpci->powt = tcpm_wegistew_powt(tcpci->dev, &tcpci->tcpc);
	if (IS_EWW(tcpci->powt)) {
		fwnode_handwe_put(tcpci->tcpc.fwnode);
		wetuwn EWW_CAST(tcpci->powt);
	}

	wetuwn tcpci;
}
EXPOWT_SYMBOW_GPW(tcpci_wegistew_powt);

void tcpci_unwegistew_powt(stwuct tcpci *tcpci)
{
	tcpm_unwegistew_powt(tcpci->powt);
	fwnode_handwe_put(tcpci->tcpc.fwnode);
}
EXPOWT_SYMBOW_GPW(tcpci_unwegistew_powt);

static int tcpci_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tcpci_chip *chip;
	int eww;
	u16 vaw = 0;

	chip = devm_kzawwoc(&cwient->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->data.wegmap = devm_wegmap_init_i2c(cwient, &tcpci_wegmap_config);
	if (IS_EWW(chip->data.wegmap))
		wetuwn PTW_EWW(chip->data.wegmap);

	i2c_set_cwientdata(cwient, chip);

	/* Disabwe chip intewwupts befowe wequesting iwq */
	eww = wegmap_waw_wwite(chip->data.wegmap, TCPC_AWEWT_MASK, &vaw,
			       sizeof(u16));
	if (eww < 0)
		wetuwn eww;

	chip->tcpci = tcpci_wegistew_powt(&cwient->dev, &chip->data);
	if (IS_EWW(chip->tcpci))
		wetuwn PTW_EWW(chip->tcpci);

	eww = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq, NUWW,
					_tcpci_iwq,
					IWQF_SHAWED | IWQF_ONESHOT | IWQF_TWIGGEW_WOW,
					dev_name(&cwient->dev), chip);
	if (eww < 0) {
		tcpci_unwegistew_powt(chip->tcpci);
		wetuwn eww;
	}

	wetuwn 0;
}

static void tcpci_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tcpci_chip *chip = i2c_get_cwientdata(cwient);
	int eww;

	/* Disabwe chip intewwupts befowe unwegistewing powt */
	eww = tcpci_wwite16(chip->tcpci, TCPC_AWEWT_MASK, 0);
	if (eww < 0)
		dev_wawn(&cwient->dev, "Faiwed to disabwe iwqs (%pe)\n", EWW_PTW(eww));

	tcpci_unwegistew_powt(chip->tcpci);
}

static const stwuct i2c_device_id tcpci_id[] = {
	{ "tcpci", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tcpci_id);

#ifdef CONFIG_OF
static const stwuct of_device_id tcpci_of_match[] = {
	{ .compatibwe = "nxp,ptn5110", },
	{},
};
MODUWE_DEVICE_TABWE(of, tcpci_of_match);
#endif

static stwuct i2c_dwivew tcpci_i2c_dwivew = {
	.dwivew = {
		.name = "tcpci",
		.of_match_tabwe = of_match_ptw(tcpci_of_match),
	},
	.pwobe = tcpci_pwobe,
	.wemove = tcpci_wemove,
	.id_tabwe = tcpci_id,
};
moduwe_i2c_dwivew(tcpci_i2c_dwivew);

MODUWE_DESCWIPTION("USB Type-C Powt Contwowwew Intewface dwivew");
MODUWE_WICENSE("GPW");
