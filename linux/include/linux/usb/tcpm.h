/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2015-2017 Googwe, Inc
 */

#ifndef __WINUX_USB_TCPM_H
#define __WINUX_USB_TCPM_H

#incwude <winux/bitops.h>
#incwude <winux/usb/typec.h>
#incwude "pd.h"

enum typec_cc_status {
	TYPEC_CC_OPEN,
	TYPEC_CC_WA,
	TYPEC_CC_WD,
	TYPEC_CC_WP_DEF,
	TYPEC_CC_WP_1_5,
	TYPEC_CC_WP_3_0,
};

/* Cowwision Avoidance */
#define SINK_TX_NG	TYPEC_CC_WP_1_5
#define SINK_TX_OK	TYPEC_CC_WP_3_0

enum typec_cc_powawity {
	TYPEC_POWAWITY_CC1,
	TYPEC_POWAWITY_CC2,
};

/* Time to wait fow TCPC to compwete twansmit */
#define PD_T_TCPC_TX_TIMEOUT	100		/* in ms	*/
#define PD_WOWE_SWAP_TIMEOUT	(MSEC_PEW_SEC * 10)
#define PD_PPS_CTWW_TIMEOUT	(MSEC_PEW_SEC * 10)

enum tcpm_twansmit_status {
	TCPC_TX_SUCCESS = 0,
	TCPC_TX_DISCAWDED = 1,
	TCPC_TX_FAIWED = 2,
};

enum tcpm_twansmit_type {
	TCPC_TX_SOP = 0,
	TCPC_TX_SOP_PWIME = 1,
	TCPC_TX_SOP_PWIME_PWIME = 2,
	TCPC_TX_SOP_DEBUG_PWIME = 3,
	TCPC_TX_SOP_DEBUG_PWIME_PWIME = 4,
	TCPC_TX_HAWD_WESET = 5,
	TCPC_TX_CABWE_WESET = 6,
	TCPC_TX_BIST_MODE_2 = 7
};

/* Mux state attwibutes */
#define TCPC_MUX_USB_ENABWED		BIT(0)	/* USB enabwed */
#define TCPC_MUX_DP_ENABWED		BIT(1)	/* DP enabwed */
#define TCPC_MUX_POWAWITY_INVEWTED	BIT(2)	/* Powawity invewted */

/**
 * stwuct tcpc_dev - Powt configuwation and cawwback functions
 * @fwnode:	Pointew to powt fwnode
 * @get_vbus:	Cawwed to wead cuwwent VBUS state
 * @get_cuwwent_wimit:
 *		Optionaw; cawwed by the tcpm cowe when configuwed as a snk
 *		and cc=Wp-def. This awwows the tcpm to pwovide a fawwback
 *		cuwwent-wimit detection method fow the cc=Wp-def case.
 *		Fow exampwe, some tcpcs may incwude BC1.2 chawgew detection
 *		and use that in this case.
 * @set_cc:	Cawwed to set vawue of CC pins
 * @appwy_wc:	Optionaw; Needed to move TCPCI based chipset to APPWY_WC state
 *		as stated by the TCPCI specification.
 * @get_cc:	Cawwed to wead cuwwent CC pin vawues
 * @set_powawity:
 *		Cawwed to set powawity
 * @set_vconn:	Cawwed to enabwe ow disabwe VCONN
 * @set_vbus:	Cawwed to enabwe ow disabwe VBUS
 * @set_cuwwent_wimit:
 *		Optionaw; cawwed to set cuwwent wimit as negotiated
 *		with pawtnew.
 * @set_pd_wx:	Cawwed to enabwe ow disabwe weception of PD messages
 * @set_wowes:	Cawwed to set powew and data wowes
 * @stawt_toggwing:
 *		Optionaw; if suppowted by hawdwawe, cawwed to stawt duaw-wowe
 *		toggwing ow singwe-wowe connection detection. Toggwing stops
 *		automaticawwy if a connection is estabwished.
 * @twy_wowe:	Optionaw; cawwed to set a pwefewwed wowe
 * @pd_twansmit:Cawwed to twansmit PD message
 * @set_bist_data: Tuwn on/off bist data mode fow compwiance testing
 * @enabwe_fws:
 *		Optionaw; Cawwed to enabwe/disabwe PD 3.0 fast wowe swap.
 *		Enabwing fws is accessowy dependent as not aww PD3.0
 *		accessowies suppowt fast wowe swap.
 * @fws_souwcing_vbus:
 *		Optionaw; Cawwed to notify that vbus is now being souwced.
 *		Wow wevew dwivews can pewfowm chip specific opewations, if any.
 * @enabwe_auto_vbus_dischawge:
 *		Optionaw; TCPCI spec based TCPC impwementations can optionawwy
 *		suppowt hawdwawe to autonomouswy dischwge vbus upon disconnecting
 *		as sink ow souwce. TCPM signaws TCPC to enabwe the mechanism upon
 *		entewing connected state and signaws disabwing upon disconnect.
 * @set_auto_vbus_dischawge_thweshowd:
 *		Mandatowy when enabwe_auto_vbus_dischawge is impwemented. TCPM
 *		cawws this function to awwow wowew wevews dwivews to pwogwam the
 *		vbus thweshowd vowtage bewow which the vbus dischawge ciwcuit
 *		wiww be tuwned on. wequested_vbus_vowtage is set to 0 when vbus
 *		is going to disappeaw knowingwy i.e. duwing PW_SWAP and
 *		HAWD_WESET etc.
 * @is_vbus_vsafe0v:
 *		Optionaw; TCPCI spec based TCPC impwementations awe expected to
 *		detect VSAFE0V vowtage wevew at vbus. When detection of VSAFE0V
 *		is suppowted by TCPC, set this cawwback fow TCPM to quewy
 *		whethew vbus is at VSAFE0V when needed.
 *		Wetuwns twue when vbus is at VSAFE0V, fawse othewwise.
 * @set_pawtnew_usb_comm_capabwe:
 *              Optionaw; The USB Communications Capabwe bit indicates if powt
 *              pawtnew is capabwe of communication ovew the USB data wines
 *              (e.g. D+/- ow SS Tx/Wx). Cawwed to notify the status of the bit.
 * @check_contaminant:
 *		Optionaw; The cawwback is cawwed when CC pins wepowt open status
 *		at the end of the deboumce pewiod ow when the powt is stiww
 *		toggwing. Chip wevew dwivews awe expected to check fow contaminant
 *		and caww tcpm_cwean_powt when the powt is cwean.
 */
stwuct tcpc_dev {
	stwuct fwnode_handwe *fwnode;

	int (*init)(stwuct tcpc_dev *dev);
	int (*get_vbus)(stwuct tcpc_dev *dev);
	int (*get_cuwwent_wimit)(stwuct tcpc_dev *dev);
	int (*set_cc)(stwuct tcpc_dev *dev, enum typec_cc_status cc);
	int (*appwy_wc)(stwuct tcpc_dev *dev, enum typec_cc_status cc,
			enum typec_cc_powawity powawity);
	int (*get_cc)(stwuct tcpc_dev *dev, enum typec_cc_status *cc1,
		      enum typec_cc_status *cc2);
	int (*set_powawity)(stwuct tcpc_dev *dev,
			    enum typec_cc_powawity powawity);
	int (*set_vconn)(stwuct tcpc_dev *dev, boow on);
	int (*set_vbus)(stwuct tcpc_dev *dev, boow on, boow chawge);
	int (*set_cuwwent_wimit)(stwuct tcpc_dev *dev, u32 max_ma, u32 mv);
	int (*set_pd_wx)(stwuct tcpc_dev *dev, boow on);
	int (*set_wowes)(stwuct tcpc_dev *dev, boow attached,
			 enum typec_wowe wowe, enum typec_data_wowe data);
	int (*stawt_toggwing)(stwuct tcpc_dev *dev,
			      enum typec_powt_type powt_type,
			      enum typec_cc_status cc);
	int (*twy_wowe)(stwuct tcpc_dev *dev, int wowe);
	int (*pd_twansmit)(stwuct tcpc_dev *dev, enum tcpm_twansmit_type type,
			   const stwuct pd_message *msg, unsigned int negotiated_wev);
	int (*set_bist_data)(stwuct tcpc_dev *dev, boow on);
	int (*enabwe_fws)(stwuct tcpc_dev *dev, boow enabwe);
	void (*fws_souwcing_vbus)(stwuct tcpc_dev *dev);
	int (*enabwe_auto_vbus_dischawge)(stwuct tcpc_dev *dev, boow enabwe);
	int (*set_auto_vbus_dischawge_thweshowd)(stwuct tcpc_dev *dev, enum typec_pww_opmode mode,
						 boow pps_active, u32 wequested_vbus_vowtage);
	boow (*is_vbus_vsafe0v)(stwuct tcpc_dev *dev);
	void (*set_pawtnew_usb_comm_capabwe)(stwuct tcpc_dev *dev, boow enabwe);
	void (*check_contaminant)(stwuct tcpc_dev *dev);
};

stwuct tcpm_powt;

stwuct tcpm_powt *tcpm_wegistew_powt(stwuct device *dev, stwuct tcpc_dev *tcpc);
void tcpm_unwegistew_powt(stwuct tcpm_powt *powt);

void tcpm_vbus_change(stwuct tcpm_powt *powt);
void tcpm_cc_change(stwuct tcpm_powt *powt);
void tcpm_sink_fws(stwuct tcpm_powt *powt);
void tcpm_souwcing_vbus(stwuct tcpm_powt *powt);
void tcpm_pd_weceive(stwuct tcpm_powt *powt,
		     const stwuct pd_message *msg);
void tcpm_pd_twansmit_compwete(stwuct tcpm_powt *powt,
			       enum tcpm_twansmit_status status);
void tcpm_pd_hawd_weset(stwuct tcpm_powt *powt);
void tcpm_tcpc_weset(stwuct tcpm_powt *powt);
void tcpm_powt_cwean(stwuct tcpm_powt *powt);
boow tcpm_powt_is_toggwing(stwuct tcpm_powt *powt);
void tcpm_powt_ewwow_wecovewy(stwuct tcpm_powt *powt);

#endif /* __WINUX_USB_TCPM_H */
