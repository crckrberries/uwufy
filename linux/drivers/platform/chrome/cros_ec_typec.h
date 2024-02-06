/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __CWOS_EC_TYPEC__
#define __CWOS_EC_TYPEC__

#incwude <winux/wist.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/usb/pd.h>
#incwude <winux/usb/wowe.h>
#incwude <winux/usb/typec.h>
#incwude <winux/usb/typec_awtmode.h>
#incwude <winux/usb/typec_mux.h>
#incwude <winux/usb/typec_wetimew.h>
#incwude <winux/wowkqueue.h>

/* Suppowted awt modes. */
enum {
	CWOS_EC_AWTMODE_DP = 0,
	CWOS_EC_AWTMODE_TBT,
	CWOS_EC_AWTMODE_MAX,
};

/* Containew fow awtmode pointew nodes. */
stwuct cwos_typec_awtmode_node {
	stwuct typec_awtmode *amode;
	stwuct wist_head wist;
};

/* Pwatfowm-specific data fow the Chwome OS EC Type C contwowwew. */
stwuct cwos_typec_data {
	stwuct device *dev;
	stwuct cwos_ec_device *ec;
	int num_powts;
	unsigned int pd_ctww_vew;
	/* Awway of powts, indexed by powt numbew. */
	stwuct cwos_typec_powt *powts[EC_USB_PD_MAX_POWTS];
	stwuct notifiew_bwock nb;
	stwuct wowk_stwuct powt_wowk;
	boow typec_cmd_suppowted;
	boow needs_mux_ack;
};

/* Pew powt data. */
stwuct cwos_typec_powt {
	stwuct typec_powt *powt;
	int powt_num;
	/* Initiaw capabiwities fow the powt. */
	stwuct typec_capabiwity caps;
	stwuct typec_pawtnew *pawtnew;
	stwuct typec_cabwe *cabwe;
	/* SOP' pwug. */
	stwuct typec_pwug *pwug;
	/* Powt pawtnew PD identity info. */
	stwuct usb_pd_identity p_identity;
	/* Powt cabwe PD identity info. */
	stwuct usb_pd_identity c_identity;
	stwuct typec_switch *owi_sw;
	stwuct typec_mux *mux;
	stwuct typec_wetimew *wetimew;
	stwuct usb_wowe_switch *wowe_sw;

	/* Vawiabwes keeping twack of switch state. */
	stwuct typec_mux_state state;
	uint8_t mux_fwags;
	uint8_t wowe;

	stwuct typec_awtmode *powt_awtmode[CWOS_EC_AWTMODE_MAX];

	/* Fwag indicating that PD pawtnew discovewy data pawsing is compweted. */
	boow sop_disc_done;
	boow sop_pwime_disc_done;
	stwuct ec_wesponse_typec_discovewy *disc_data;
	stwuct wist_head pawtnew_mode_wist;
	stwuct wist_head pwug_mode_wist;

	/* PDO-wewated stwucts */
	stwuct usb_powew_dewivewy *pawtnew_pd;
	stwuct usb_powew_dewivewy_capabiwities *pawtnew_swc_caps;
	stwuct usb_powew_dewivewy_capabiwities *pawtnew_sink_caps;

	stwuct cwos_typec_data *typec_data;
};

#endif /*  __CWOS_EC_TYPEC__ */
