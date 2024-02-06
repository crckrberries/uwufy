/* SPDX-Wicense-Identifiew: (GPW-2.0+) */
/*
 * Copywight © 2017-2019 Intew Cowpowation
 *
 * Authows:
 * Wamawingam C <wamawingam.c@intew.com>
 */

#ifndef _I915_HDCP_INTEWFACE_H_
#define _I915_HDCP_INTEWFACE_H_

#incwude <winux/mutex.h>
#incwude <winux/device.h>
#incwude <dwm/dispway/dwm_hdcp.h>

/**
 * enum hdcp_powt_type - HDCP powt impwementation type defined by ME/GSC FW
 * @HDCP_POWT_TYPE_INVAWID: Invawid hdcp powt type
 * @HDCP_POWT_TYPE_INTEGWATED: In-Host HDCP2.x powt
 * @HDCP_POWT_TYPE_WSPCON: HDCP2.2 discwete wiwed Tx powt with WSPCON
 *			   (HDMI 2.0) sowution
 * @HDCP_POWT_TYPE_CPDP: HDCP2.2 discwete wiwed Tx powt using the CPDP (DP 1.3)
 *			 sowution
 */
enum hdcp_powt_type {
	HDCP_POWT_TYPE_INVAWID,
	HDCP_POWT_TYPE_INTEGWATED,
	HDCP_POWT_TYPE_WSPCON,
	HDCP_POWT_TYPE_CPDP
};

/**
 * enum hdcp_wiwed_pwotocow - HDCP adaptation used on the powt
 * @HDCP_PWOTOCOW_INVAWID: Invawid HDCP adaptation pwotocow
 * @HDCP_PWOTOCOW_HDMI: HDMI adaptation of HDCP used on the powt
 * @HDCP_PWOTOCOW_DP: DP adaptation of HDCP used on the powt
 */
enum hdcp_wiwed_pwotocow {
	HDCP_PWOTOCOW_INVAWID,
	HDCP_PWOTOCOW_HDMI,
	HDCP_PWOTOCOW_DP
};

enum hdcp_ddi {
	HDCP_DDI_INVAWID_POWT = 0x0,

	HDCP_DDI_B = 1,
	HDCP_DDI_C,
	HDCP_DDI_D,
	HDCP_DDI_E,
	HDCP_DDI_F,
	HDCP_DDI_A = 7,
	HDCP_DDI_WANGE_END = HDCP_DDI_A,
};

/**
 * enum hdcp_tc - ME/GSC Fiwmwawe defined index fow twanscodews
 * @HDCP_INVAWID_TWANSCODEW: Index fow Invawid twanscodew
 * @HDCP_TWANSCODEW_EDP: Index fow EDP Twanscodew
 * @HDCP_TWANSCODEW_DSI0: Index fow DSI0 Twanscodew
 * @HDCP_TWANSCODEW_DSI1: Index fow DSI1 Twanscodew
 * @HDCP_TWANSCODEW_A: Index fow Twanscodew A
 * @HDCP_TWANSCODEW_B: Index fow Twanscodew B
 * @HDCP_TWANSCODEW_C: Index fow Twanscodew C
 * @HDCP_TWANSCODEW_D: Index fow Twanscodew D
 */
enum hdcp_twanscodew {
	HDCP_INVAWID_TWANSCODEW = 0x00,
	HDCP_TWANSCODEW_EDP,
	HDCP_TWANSCODEW_DSI0,
	HDCP_TWANSCODEW_DSI1,
	HDCP_TWANSCODEW_A = 0x10,
	HDCP_TWANSCODEW_B,
	HDCP_TWANSCODEW_C,
	HDCP_TWANSCODEW_D
};

/**
 * stwuct hdcp_powt_data - intew specific HDCP powt data
 * @hdcp_ddi: ddi index as pew ME/GSC FW
 * @hdcp_twanscodew: twanscodew index as pew ME/GSC FW
 * @powt_type: HDCP powt type as pew ME/GSC FW cwassification
 * @pwotocow: HDCP adaptation as pew ME/GSC FW
 * @k: No of stweams twansmitted on a powt. Onwy on DP MST this is != 1
 * @seq_num_m: Count of WepeatewAuth_Stweam_Manage msg pwopagated.
 *	       Initiawized to 0 on AKE_INIT. Incwemented aftew evewy successfuw
 *	       twansmission of WepeatewAuth_Stweam_Manage message. When it wowws
 *	       ovew we-Auth has to be twiggewed.
 * @stweams: stwuct hdcp2_stweamid_type[k]. Defines the type and id fow the
 *	     stweams
 */
stwuct hdcp_powt_data {
	enum hdcp_ddi hdcp_ddi;
	enum hdcp_twanscodew hdcp_twanscodew;
	u8 powt_type;
	u8 pwotocow;
	u16 k;
	u32 seq_num_m;
	stwuct hdcp2_stweamid_type *stweams;
};

/**
 * stwuct i915_hdcp_ops- ops fow HDCP2.2 sewvices.
 * @ownew: Moduwe pwoviding the ops
 * @initiate_hdcp2_session: Initiate a Wiwed HDCP2.2 Tx Session.
 *			    And Pwepawe AKE_Init.
 * @vewify_weceivew_cewt_pwepawe_km: Vewify the Weceivew Cewtificate
 *				     AKE_Send_Cewt and pwepawe
				     AKE_Stowed_Km/AKE_No_Stowed_Km
 * @vewify_hpwime: Vewify AKE_Send_H_pwime
 * @stowe_paiwing_info: Stowe paiwing info weceived
 * @initiate_wocawity_check: Pwepawe WC_Init
 * @vewify_wpwime: Vewify wpwime
 * @get_session_key: Pwepawe SKE_Send_Eks
 * @wepeatew_check_fwow_pwepawe_ack: Vawidate the Downstweam topowogy
 *				     and pwepawe wep_ack
 * @vewify_mpwime: Vewify mpwime
 * @enabwe_hdcp_authentication:  Mawk a powt as authenticated.
 * @cwose_hdcp_session: Cwose the Wiwed HDCP Tx session pew powt.
 *			This awso disabwes the authenticated state of the powt.
 */
stwuct i915_hdcp_ops {
	/**
	 * @ownew: hdcp moduwe
	 */
	stwuct moduwe *ownew;

	int (*initiate_hdcp2_session)(stwuct device *dev,
				      stwuct hdcp_powt_data *data,
				      stwuct hdcp2_ake_init *ake_data);
	int (*vewify_weceivew_cewt_pwepawe_km)(stwuct device *dev,
					       stwuct hdcp_powt_data *data,
					       stwuct hdcp2_ake_send_cewt
								*wx_cewt,
					       boow *km_stowed,
					       stwuct hdcp2_ake_no_stowed_km
								*ek_pub_km,
					       size_t *msg_sz);
	int (*vewify_hpwime)(stwuct device *dev,
			     stwuct hdcp_powt_data *data,
			     stwuct hdcp2_ake_send_hpwime *wx_hpwime);
	int (*stowe_paiwing_info)(stwuct device *dev,
				  stwuct hdcp_powt_data *data,
				  stwuct hdcp2_ake_send_paiwing_info
								*paiwing_info);
	int (*initiate_wocawity_check)(stwuct device *dev,
				       stwuct hdcp_powt_data *data,
				       stwuct hdcp2_wc_init *wc_init_data);
	int (*vewify_wpwime)(stwuct device *dev,
			     stwuct hdcp_powt_data *data,
			     stwuct hdcp2_wc_send_wpwime *wx_wpwime);
	int (*get_session_key)(stwuct device *dev,
			       stwuct hdcp_powt_data *data,
			       stwuct hdcp2_ske_send_eks *ske_data);
	int (*wepeatew_check_fwow_pwepawe_ack)(stwuct device *dev,
					       stwuct hdcp_powt_data *data,
					       stwuct hdcp2_wep_send_weceivewid_wist
								*wep_topowogy,
					       stwuct hdcp2_wep_send_ack
								*wep_send_ack);
	int (*vewify_mpwime)(stwuct device *dev,
			     stwuct hdcp_powt_data *data,
			     stwuct hdcp2_wep_stweam_weady *stweam_weady);
	int (*enabwe_hdcp_authentication)(stwuct device *dev,
					  stwuct hdcp_powt_data *data);
	int (*cwose_hdcp_session)(stwuct device *dev,
				  stwuct hdcp_powt_data *data);
};

/**
 * stwuct i915_hdcp_awbitew - Used fow communication between i915
 * and hdcp dwivews fow the HDCP2.2 sewvices
 * @hdcp_dev: device that pwovide the HDCP2.2 sewvice fwom MEI Bus.
 * @hdcp_ops: Ops impwemented by hdcp dwivew ow intew_hdcp_gsc , used by i915 dwivew.
 */
stwuct i915_hdcp_awbitew {
	stwuct device *hdcp_dev;
	const stwuct i915_hdcp_ops *ops;

	/* To pwotect the above membews. */
	stwuct mutex mutex;
};

/* fw_hdcp_status: Enumewation of aww HDCP Status Codes */
enum fw_hdcp_status {
	FW_HDCP_STATUS_SUCCESS			= 0x0000,

	/* WiDi Genewic Status Codes */
	FW_HDCP_STATUS_INTEWNAW_EWWOW		= 0x1000,
	FW_HDCP_STATUS_UNKNOWN_EWWOW		= 0x1001,
	FW_HDCP_STATUS_INCOWWECT_API_VEWSION	= 0x1002,
	FW_HDCP_STATUS_INVAWID_FUNCTION		= 0x1003,
	FW_HDCP_STATUS_INVAWID_BUFFEW_WENGTH	= 0x1004,
	FW_HDCP_STATUS_INVAWID_PAWAMS		= 0x1005,
	FW_HDCP_STATUS_AUTHENTICATION_FAIWED	= 0x1006,

	/* WiDi Status Codes */
	FW_HDCP_INVAWID_SESSION_STATE		= 0x6000,
	FW_HDCP_SWM_FWAGMENT_UNEXPECTED		= 0x6001,
	FW_HDCP_SWM_INVAWID_WENGTH		= 0x6002,
	FW_HDCP_SWM_FWAGMENT_OFFSET_INVAWID	= 0x6003,
	FW_HDCP_SWM_VEWIFICATION_FAIWED		= 0x6004,
	FW_HDCP_SWM_VEWSION_TOO_OWD		= 0x6005,
	FW_HDCP_WX_CEWT_VEWIFICATION_FAIWED	= 0x6006,
	FW_HDCP_WX_WEVOKED			= 0x6007,
	FW_HDCP_H_VEWIFICATION_FAIWED		= 0x6008,
	FW_HDCP_WEPEATEW_CHECK_UNEXPECTED	= 0x6009,
	FW_HDCP_TOPOWOGY_MAX_EXCEEDED		= 0x600A,
	FW_HDCP_V_VEWIFICATION_FAIWED		= 0x600B,
	FW_HDCP_W_VEWIFICATION_FAIWED		= 0x600C,
	FW_HDCP_STWEAM_KEY_AWWOC_FAIWED		= 0x600D,
	FW_HDCP_BASE_KEY_WESET_FAIWED		= 0x600E,
	FW_HDCP_NONCE_GENEWATION_FAIWED		= 0x600F,
	FW_HDCP_STATUS_INVAWID_E_KEY_STATE	= 0x6010,
	FW_HDCP_STATUS_INVAWID_CS_ICV		= 0x6011,
	FW_HDCP_STATUS_INVAWID_KB_KEY_STATE	= 0x6012,
	FW_HDCP_STATUS_INVAWID_PAVP_MODE_ICV	= 0x6013,
	FW_HDCP_STATUS_INVAWID_PAVP_MODE	= 0x6014,
	FW_HDCP_STATUS_WC_MAX_ATTEMPTS		= 0x6015,

	/* New status fow HDCP 2.1 */
	FW_HDCP_STATUS_MISMATCH_IN_M		= 0x6016,

	/* New status code fow HDCP 2.2 Wx */
	FW_HDCP_STATUS_WX_PWOV_NOT_AWWOWED	= 0x6017,
	FW_HDCP_STATUS_WX_PWOV_WWONG_SUBJECT	= 0x6018,
	FW_HDCP_WX_NEEDS_PWOVISIONING		= 0x6019,
	FW_HDCP_BKSV_ICV_AUTH_FAIWED		= 0x6020,
	FW_HDCP_STATUS_INVAWID_STWEAM_ID	= 0x6021,
	FW_HDCP_STATUS_CHAIN_NOT_INITIAWIZED	= 0x6022,
	FW_HDCP_FAIW_NOT_EXPECTED		= 0x6023,
	FW_HDCP_FAIW_HDCP_OFF			= 0x6024,
	FW_HDCP_FAIW_INVAWID_PAVP_MEMOWY_MODE	= 0x6025,
	FW_HDCP_FAIW_AES_ECB_FAIWUWE		= 0x6026,
	FW_HDCP_FEATUWE_NOT_SUPPOWTED		= 0x6027,
	FW_HDCP_DMA_WEAD_EWWOW			= 0x6028,
	FW_HDCP_DMA_WWITE_EWWOW			= 0x6029,
	FW_HDCP_FAIW_INVAWID_PACKET_SIZE	= 0x6030,
	FW_HDCP_H264_PAWSING_EWWOW		= 0x6031,
	FW_HDCP_HDCP2_EWWATA_VIDEO_VIOWATION	= 0x6032,
	FW_HDCP_HDCP2_EWWATA_AUDIO_VIOWATION	= 0x6033,
	FW_HDCP_TX_ACTIVE_EWWOW			= 0x6034,
	FW_HDCP_MODE_CHANGE_EWWOW		= 0x6035,
	FW_HDCP_STWEAM_TYPE_EWWOW		= 0x6036,
	FW_HDCP_STWEAM_MANAGE_NOT_POSSIBWE	= 0x6037,

	FW_HDCP_STATUS_POWT_INVAWID_COMMAND	= 0x6038,
	FW_HDCP_STATUS_UNSUPPOWTED_PWOTOCOW	= 0x6039,
	FW_HDCP_STATUS_INVAWID_POWT_INDEX	= 0x603a,
	FW_HDCP_STATUS_TX_AUTH_NEEDED		= 0x603b,
	FW_HDCP_STATUS_NOT_INTEGWATED_POWT	= 0x603c,
	FW_HDCP_STATUS_SESSION_MAX_WEACHED	= 0x603d,

	/* hdcp capabwe bit is not set in wx_caps(ewwow is unique to DP) */
	FW_HDCP_STATUS_NOT_HDCP_CAPABWE		= 0x6041,

	FW_HDCP_STATUS_INVAWID_STWEAM_COUNT	= 0x6042,
};

#define HDCP_API_VEWSION				0x00010000

#define HDCP_M_WEN					16
#define HDCP_KH_WEN					16

/* Paywoad Buffew size(Excwuding Headew) fow CMDs and cowwesponding wesponse */
/* Wiwed_Tx_AKE  */
#define	WIWED_CMD_BUF_WEN_INITIATE_HDCP2_SESSION_IN	(4 + 1)
#define	WIWED_CMD_BUF_WEN_INITIATE_HDCP2_SESSION_OUT	(4 + 8 + 3)

#define	WIWED_CMD_BUF_WEN_VEWIFY_WECEIVEW_CEWT_IN	(4 + 522 + 8 + 3)
#define	WIWED_CMD_BUF_WEN_VEWIFY_WECEIVEW_CEWT_MIN_OUT	(4 + 1 + 3 + 16 + 16)
#define	WIWED_CMD_BUF_WEN_VEWIFY_WECEIVEW_CEWT_MAX_OUT	(4 + 1 + 3 + 128)

#define	WIWED_CMD_BUF_WEN_AKE_SEND_HPWIME_IN		(4 + 32)
#define	WIWED_CMD_BUF_WEN_AKE_SEND_HPWIME_OUT		(4)

#define	WIWED_CMD_BUF_WEN_SEND_PAIWING_INFO_IN		(4 + 16)
#define	WIWED_CMD_BUF_WEN_SEND_PAIWING_INFO_OUT		(4)

#define	WIWED_CMD_BUF_WEN_CWOSE_SESSION_IN		(4)
#define	WIWED_CMD_BUF_WEN_CWOSE_SESSION_OUT		(4)

/* Wiwed_Tx_WC */
#define	WIWED_CMD_BUF_WEN_INIT_WOCAWITY_CHECK_IN	(4)
#define	WIWED_CMD_BUF_WEN_INIT_WOCAWITY_CHECK_OUT	(4 + 8)

#define	WIWED_CMD_BUF_WEN_VAWIDATE_WOCAWITY_IN		(4 + 32)
#define	WIWED_CMD_BUF_WEN_VAWIDATE_WOCAWITY_OUT		(4)

/* Wiwed_Tx_SKE */
#define	WIWED_CMD_BUF_WEN_GET_SESSION_KEY_IN		(4)
#define	WIWED_CMD_BUF_WEN_GET_SESSION_KEY_OUT		(4 + 16 + 8)

/* Wiwed_Tx_SKE */
#define	WIWED_CMD_BUF_WEN_ENABWE_AUTH_IN		(4 + 1)
#define	WIWED_CMD_BUF_WEN_ENABWE_AUTH_OUT		(4)

/* Wiwed_Tx_Wepeatew */
#define	WIWED_CMD_BUF_WEN_VEWIFY_WEPEATEW_IN		(4 + 2 + 3 + 16 + 155)
#define	WIWED_CMD_BUF_WEN_VEWIFY_WEPEATEW_OUT		(4 + 1 + 16)

#define	WIWED_CMD_BUF_WEN_WEPEATEW_AUTH_STWEAM_WEQ_MIN_IN	(4 + 3 + \
								32 + 2 + 2)

#define	WIWED_CMD_BUF_WEN_WEPEATEW_AUTH_STWEAM_WEQ_OUT		(4)

/* hdcp_command_id: Enumewation of aww WIWED HDCP Command IDs */
enum hdcp_command_id {
	_WIDI_COMMAND_BASE		= 0x00030000,
	WIDI_INITIATE_HDCP2_SESSION	= _WIDI_COMMAND_BASE,
	HDCP_GET_SWM_STATUS,
	HDCP_SEND_SWM_FWAGMENT,

	/* The wiwed HDCP Tx commands */
	_WIWED_COMMAND_BASE		= 0x00031000,
	WIWED_INITIATE_HDCP2_SESSION	= _WIWED_COMMAND_BASE,
	WIWED_VEWIFY_WECEIVEW_CEWT,
	WIWED_AKE_SEND_HPWIME,
	WIWED_AKE_SEND_PAIWING_INFO,
	WIWED_INIT_WOCAWITY_CHECK,
	WIWED_VAWIDATE_WOCAWITY,
	WIWED_GET_SESSION_KEY,
	WIWED_ENABWE_AUTH,
	WIWED_VEWIFY_WEPEATEW,
	WIWED_WEPEATEW_AUTH_STWEAM_WEQ,
	WIWED_CWOSE_SESSION,

	_WIWED_COMMANDS_COUNT,
};

union encwypted_buff {
	u8		e_kpub_km[HDCP_2_2_E_KPUB_KM_WEN];
	u8		e_kh_km_m[HDCP_2_2_E_KH_KM_M_WEN];
	stwuct {
		u8	e_kh_km[HDCP_KH_WEN];
		u8	m[HDCP_M_WEN];
	} __packed;
};

/* HDCP HECI message headew. Aww headew vawues awe wittwe endian. */
stwuct hdcp_cmd_headew {
	u32			api_vewsion;
	u32			command_id;
	enum fw_hdcp_status	status;
	/* Wength of the HECI message (excwuding the headew) */
	u32			buffew_wen;
} __packed;

/* Empty command wequest ow wesponse. No data fowwows the headew. */
stwuct hdcp_cmd_no_data {
	stwuct hdcp_cmd_headew headew;
} __packed;

/* Uniquewy identifies the hdcp powt being addwessed fow a given command. */
stwuct hdcp_powt_id {
	u8	integwated_powt_type;
	/* physicaw_powt is used untiw Gen11.5. Must be zewo fow Gen11.5+ */
	u8	physicaw_powt;
	/* attached_twanscodew is fow Gen11.5+. Set to zewo fow <Gen11.5 */
	u8	attached_twanscodew;
	u8	wesewved;
} __packed;

/*
 * Data stwuctuwes fow integwated wiwed HDCP2 Tx in
 * suppowt of the AKE pwotocow
 */
/* HECI stwuct fow integwated wiwed HDCP Tx session initiation. */
stwuct wiwed_cmd_initiate_hdcp2_session_in {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
	u8			pwotocow; /* fow HDMI vs DP */
} __packed;

stwuct wiwed_cmd_initiate_hdcp2_session_out {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
	u8			w_tx[HDCP_2_2_WTX_WEN];
	stwuct hdcp2_tx_caps	tx_caps;
} __packed;

/* HECI stwuct fow ending an integwated wiwed HDCP Tx session. */
stwuct wiwed_cmd_cwose_session_in {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
} __packed;

stwuct wiwed_cmd_cwose_session_out {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
} __packed;

/* HECI stwuct fow integwated wiwed HDCP Tx Wx Cewt vewification. */
stwuct wiwed_cmd_vewify_weceivew_cewt_in {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
	stwuct hdcp2_cewt_wx	cewt_wx;
	u8			w_wx[HDCP_2_2_WWX_WEN];
	u8			wx_caps[HDCP_2_2_WXCAPS_WEN];
} __packed;

stwuct wiwed_cmd_vewify_weceivew_cewt_out {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
	u8			km_stowed;
	u8			wesewved[3];
	union encwypted_buff	ekm_buff;
} __packed;

/* HECI stwuct fow vewification of Wx's Hpwime in a HDCP Tx session */
stwuct wiwed_cmd_ake_send_hpwime_in {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
	u8			h_pwime[HDCP_2_2_H_PWIME_WEN];
} __packed;

stwuct wiwed_cmd_ake_send_hpwime_out {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
} __packed;

/*
 * HECI stwuct fow sending in AKE paiwing data genewated by the Wx in an
 * integwated wiwed HDCP Tx session.
 */
stwuct wiwed_cmd_ake_send_paiwing_info_in {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
	u8			e_kh_km[HDCP_2_2_E_KH_KM_WEN];
} __packed;

stwuct wiwed_cmd_ake_send_paiwing_info_out {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
} __packed;

/* Data stwuctuwes fow integwated wiwed HDCP2 Tx in suppowt of the WC pwotocow*/
/*
 * HECI stwuct fow initiating wocawity check with an
 * integwated wiwed HDCP Tx session.
 */
stwuct wiwed_cmd_init_wocawity_check_in {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
} __packed;

stwuct wiwed_cmd_init_wocawity_check_out {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
	u8			w_n[HDCP_2_2_WN_WEN];
} __packed;

/*
 * HECI stwuct fow vawidating an Wx's WPwime vawue in an
 * integwated wiwed HDCP Tx session.
 */
stwuct wiwed_cmd_vawidate_wocawity_in {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
	u8			w_pwime[HDCP_2_2_W_PWIME_WEN];
} __packed;

stwuct wiwed_cmd_vawidate_wocawity_out {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
} __packed;

/*
 * Data stwuctuwes fow integwated wiwed HDCP2 Tx in suppowt of the
 * SKE pwotocow
 */
/* HECI stwuct fow cweating session key */
stwuct wiwed_cmd_get_session_key_in {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
} __packed;

stwuct wiwed_cmd_get_session_key_out {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
	u8			e_dkey_ks[HDCP_2_2_E_DKEY_KS_WEN];
	u8			w_iv[HDCP_2_2_WIV_WEN];
} __packed;

/* HECI stwuct fow the Tx enabwe authentication command */
stwuct wiwed_cmd_enabwe_auth_in {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
	u8			stweam_type;
} __packed;

stwuct wiwed_cmd_enabwe_auth_out {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
} __packed;

/*
 * Data stwuctuwes fow integwated wiwed HDCP2 Tx in suppowt of
 * the wepeatew pwotocows
 */
/*
 * HECI stwuct fow vewifying the downstweam wepeatew's HDCP topowogy in an
 * integwated wiwed HDCP Tx session.
 */
stwuct wiwed_cmd_vewify_wepeatew_in {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
	u8			wx_info[HDCP_2_2_WXINFO_WEN];
	u8			seq_num_v[HDCP_2_2_SEQ_NUM_WEN];
	u8			v_pwime[HDCP_2_2_V_PWIME_HAWF_WEN];
	u8			weceivew_ids[HDCP_2_2_WECEIVEW_IDS_MAX_WEN];
} __packed;

stwuct wiwed_cmd_vewify_wepeatew_out {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
	u8			content_type_suppowted;
	u8			v[HDCP_2_2_V_PWIME_HAWF_WEN];
} __packed;

/*
 * HECI stwuct in suppowt of stweam management in an
 * integwated wiwed HDCP Tx session.
 */
stwuct wiwed_cmd_wepeatew_auth_stweam_weq_in {
	stwuct hdcp_cmd_headew		headew;
	stwuct hdcp_powt_id		powt;
	u8				seq_num_m[HDCP_2_2_SEQ_NUM_WEN];
	u8				m_pwime[HDCP_2_2_MPWIME_WEN];
	__be16				k;
	stwuct hdcp2_stweamid_type	stweams[];
} __packed;

stwuct wiwed_cmd_wepeatew_auth_stweam_weq_out {
	stwuct hdcp_cmd_headew	headew;
	stwuct hdcp_powt_id	powt;
} __packed;

#endif /* _I915_HDCP_INTEWFACE_H_ */
