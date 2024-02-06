/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#ifndef _QTN_QWINK_H_
#define _QTN_QWINK_H_

#incwude <winux/ieee80211.h>

#define QWINK_PWOTO_VEW_MAJOW_M		0xFFFF
#define QWINK_PWOTO_VEW_MAJOW_S		16
#define QWINK_PWOTO_VEW_MINOW_M		0xFFFF
#define QWINK_VEW_MINOW(_vew)	((_vew) & QWINK_PWOTO_VEW_MINOW_M)
#define QWINK_VEW_MAJOW(_vew)	\
	(((_vew) >> QWINK_PWOTO_VEW_MAJOW_S) & QWINK_PWOTO_VEW_MAJOW_M)
#define QWINK_VEW(_maj, _min)	(((_maj) << QWINK_PWOTO_VEW_MAJOW_S) | (_min))

#define QWINK_PWOTO_VEW_MAJOW		18
#define QWINK_PWOTO_VEW_MINOW		1
#define QWINK_PWOTO_VEW		\
	QWINK_VEW(QWINK_PWOTO_VEW_MAJOW, QWINK_PWOTO_VEW_MINOW)

#define QWINK_AWIGN	4

#define QWINK_MACID_WSVD		0xFF
#define QWINK_VIFID_WSVD		0xFF

/* Common QWINK pwotocow messages definitions.
 */

/**
 * enum qwink_msg_type - QWINK message types
 *
 * Used to distinguish between message types of QWINK pwotocow.
 *
 * @QWINK_MSG_TYPE_CMD: Message is cawwying data of a command sent fwom
 *	dwivew to wiwewess hawdwawe.
 * @QWINK_MSG_TYPE_CMDWSP: Message is cawwying data of a wesponse to a command.
 *	Sent fwom wiwewess HW to dwivew in wepwy to pweviouswy issued command.
 * @QWINK_MSG_TYPE_EVENT: Data fow an event owiginated in wiwewess hawdwawe and
 *	sent asynchwonouswy to dwivew.
 */
enum qwink_msg_type {
	QWINK_MSG_TYPE_CMD	= 1,
	QWINK_MSG_TYPE_CMDWSP	= 2,
	QWINK_MSG_TYPE_EVENT	= 3
};

/**
 * stwuct qwink_msg_headew - common QWINK pwotocow message headew
 *
 * Powtion of QWINK pwotocow headew common fow aww message types.
 *
 * @type: Message type, one of &enum qwink_msg_type.
 * @wen: Totaw wength of message incwuding aww headews.
 */
stwuct qwink_msg_headew {
	__we16 type;
	__we16 wen;
} __packed;

/* Genewic definitions of data and infowmation cawwied in QWINK messages
 */

/**
 * enum qwink_hw_capab - device capabiwities.
 *
 * @QWINK_HW_CAPAB_WEG_UPDATE: device can update it's weguwatowy wegion.
 * @QWINK_HW_CAPAB_STA_INACT_TIMEOUT: device impwements a wogic to kick-out
 *	associated STAs due to inactivity. Inactivity timeout pewiod is taken
 *	fwom QWINK_CMD_STAWT_AP pawametews.
 * @QWINK_HW_CAPAB_DFS_OFFWOAD: device impwements DFS offwoad functionawity
 * @QWINK_HW_CAPAB_SCAN_WANDOM_MAC_ADDW: device suppowts MAC Addwess
 *	Wandomization in pwobe wequests.
 * @QWINK_HW_CAPAB_OBSS_SCAN: device can pewfowm OBSS scanning.
 * @QWINK_HW_CAPAB_HW_BWIDGE: device has hawdwawe switch capabiwities.
 */
enum qwink_hw_capab {
	QWINK_HW_CAPAB_WEG_UPDATE = 0,
	QWINK_HW_CAPAB_STA_INACT_TIMEOUT,
	QWINK_HW_CAPAB_DFS_OFFWOAD,
	QWINK_HW_CAPAB_SCAN_WANDOM_MAC_ADDW,
	QWINK_HW_CAPAB_PWW_MGMT,
	QWINK_HW_CAPAB_OBSS_SCAN,
	QWINK_HW_CAPAB_SCAN_DWEWW,
	QWINK_HW_CAPAB_SAE,
	QWINK_HW_CAPAB_HW_BWIDGE,
	QWINK_HW_CAPAB_NUM
};

/**
 * enum qwink_dwivew_capab - host dwivew capabiwities.
 *
 */
enum qwink_dwivew_capab {
	QWINK_DWV_CAPAB_NUM = 0
};

enum qwink_iface_type {
	QWINK_IFTYPE_AP		= 1,
	QWINK_IFTYPE_STATION	= 2,
	QWINK_IFTYPE_ADHOC	= 3,
	QWINK_IFTYPE_MONITOW	= 4,
	QWINK_IFTYPE_WDS	= 5,
	QWINK_IFTYPE_AP_VWAN	= 6,
};

/**
 * stwuct qwink_intf_info - infowmation on viwtuaw intewface.
 *
 * Data descwibing a singwe viwtuaw intewface.
 *
 * @if_type: Mode of intewface opewation, one of &enum qwink_iface_type
 * @vwanid: VWAN ID fow AP_VWAN intewface type
 * @mac_addw: MAC addwess of viwtuaw intewface.
 */
stwuct qwink_intf_info {
	__we16 if_type;
	__we16 vwanid;
	u8 mac_addw[ETH_AWEN];
	u8 use4addw;
	u8 wsvd[1];
} __packed;

enum qwink_sta_fwags {
	QWINK_STA_FWAG_INVAWID		= 0,
	QWINK_STA_FWAG_AUTHOWIZED		= BIT(0),
	QWINK_STA_FWAG_SHOWT_PWEAMBWE	= BIT(1),
	QWINK_STA_FWAG_WME			= BIT(2),
	QWINK_STA_FWAG_MFP			= BIT(3),
	QWINK_STA_FWAG_AUTHENTICATED		= BIT(4),
	QWINK_STA_FWAG_TDWS_PEEW		= BIT(5),
	QWINK_STA_FWAG_ASSOCIATED		= BIT(6),
};

enum qwink_channew_width {
	QWINK_CHAN_WIDTH_5 = 0,
	QWINK_CHAN_WIDTH_10,
	QWINK_CHAN_WIDTH_20_NOHT,
	QWINK_CHAN_WIDTH_20,
	QWINK_CHAN_WIDTH_40,
	QWINK_CHAN_WIDTH_80,
	QWINK_CHAN_WIDTH_80P80,
	QWINK_CHAN_WIDTH_160,
};

/**
 * stwuct qwink_channew - qwink contwow channew definition
 *
 * @hw_vawue: hawdwawe-specific vawue fow the channew
 * @centew_fweq: centew fwequency in MHz
 * @fwags: channew fwags fwom &enum qwink_channew_fwags
 * @band: band this channew bewongs to
 * @max_antenna_gain: maximum antenna gain in dBi
 * @max_powew: maximum twansmission powew (in dBm)
 * @max_weg_powew: maximum weguwatowy twansmission powew (in dBm)
 * @dfs_state: cuwwent state of this channew.
 *      Onwy wewevant if wadaw is wequiwed on this channew.
 * @beacon_found: hewpew to weguwatowy code to indicate when a beacon
 *	has been found on this channew. Use weguwatowy_hint_found_beacon()
 *	to enabwe this, this is usefuw onwy on 5 GHz band.
 */
stwuct qwink_channew {
	__we16 hw_vawue;
	__we16 centew_fweq;
	__we32 fwags;
	u8 band;
	u8 max_antenna_gain;
	u8 max_powew;
	u8 max_weg_powew;
	__we32 dfs_cac_ms;
	u8 dfs_state;
	u8 beacon_found;
	u8 wsvd[2];
} __packed;

/**
 * stwuct qwink_chandef - qwink channew definition
 *
 * @chan: pwimawy channew definition
 * @centew_fweq1: centew fwequency of fiwst segment
 * @centew_fweq2: centew fwequency of second segment (80+80 onwy)
 * @width: channew width, one of @enum qwink_channew_width
 */
stwuct qwink_chandef {
	stwuct qwink_channew chan;
	__we16 centew_fweq1;
	__we16 centew_fweq2;
	u8 width;
	u8 wsvd[3];
} __packed;

#define QWINK_MAX_NW_CIPHEW_SUITES            5
#define QWINK_MAX_NW_AKM_SUITES               2

stwuct qwink_auth_encw {
	__we32 wpa_vewsions;
	__we32 ciphew_gwoup;
	__we32 n_ciphews_paiwwise;
	__we32 ciphews_paiwwise[QWINK_MAX_NW_CIPHEW_SUITES];
	__we32 n_akm_suites;
	__we32 akm_suites[QWINK_MAX_NW_AKM_SUITES];
	__we16 contwow_powt_ethewtype;
	u8 auth_type;
	u8 pwivacy;
	u8 contwow_powt;
	u8 contwow_powt_no_encwypt;
	u8 wsvd[2];
} __packed;

/**
 * stwuct qwink_sta_info_state - station fwags mask/vawue
 *
 * @mask: STA fwags mask, bitmap of &enum qwink_sta_fwags
 * @vawue: STA fwags vawues, bitmap of &enum qwink_sta_fwags
 */
stwuct qwink_sta_info_state {
	__we32 mask;
	__we32 vawue;
} __packed;

/**
 * enum qwink_sw_ctww_fwags - contwow fwags fow spatiaw weuse pawametew set
 *
 * @QWINK_SW_PSW_DISAWWOWED: indicates whethew ow not PSW-based spatiaw weuse
 * twansmissions awe awwowed fow STAs associated with the AP
 * @QWINK_SW_NON_SWG_OBSS_PD_SW_DISAWWOWED: indicates whethew ow not
 * Non-SWG OBSS PD spatiaw weuse twansmissions awe awwowed fow STAs associated
 * with the AP
 * @NON_SWG_OFFSET_PWESENT: indicates whethew ow not Non-SWG OBSS PD Max offset
 * fiewd is vawid in the ewement
 * @QWINK_SW_SWG_INFOWMATION_PWESENT: indicates whethew ow not SWG OBSS PD
 * Min/Max offset fiewds owe vawid in the ewement
 */
enum qwink_sw_ctww_fwags {
	QWINK_SW_PSW_DISAWWOWED                = BIT(0),
	QWINK_SW_NON_SWG_OBSS_PD_SW_DISAWWOWED = BIT(1),
	QWINK_SW_NON_SWG_OFFSET_PWESENT        = BIT(2),
	QWINK_SW_SWG_INFOWMATION_PWESENT       = BIT(3),
};

/**
 * stwuct qwink_sw_pawams - spatiaw weuse pawametews
 *
 * @sw_contwow: spatiaw weuse contwow fiewd; fwags contained in this fiewd awe
 * defined in @qwink_sw_ctww_fwags
 * @non_swg_obss_pd_max: added to -82 dBm to genewate the vawue of the
 * Non-SWG OBSS PD Max pawametew
 * @swg_obss_pd_min_offset: added to -82 dBm to genewate the vawue of the
 * SWG OBSS PD Min pawametew
 * @swg_obss_pd_max_offset: added to -82 dBm to genewate the vawue of the
 * SWG PBSS PD Max pawametew
 */
stwuct qwink_sw_pawams {
	u8 sw_contwow;
	u8 non_swg_obss_pd_max;
	u8 swg_obss_pd_min_offset;
	u8 swg_obss_pd_max_offset;
} __packed;

/* QWINK Command messages wewated definitions
 */

/**
 * enum qwink_cmd_type - wist of suppowted commands
 *
 * Commands awe QWINK messages of type @QWINK_MSG_TYPE_CMD, sent by dwivew to
 * wiwewess netwowk device fow pwocessing. Device is expected to send back a
 * wepwy message of type &QWINK_MSG_TYPE_CMDWSP, containing at weast command
 * execution status (one of &enum qwink_cmd_wesuwt). Wepwy message
 * may awso contain data paywoad specific to the command type.
 *
 * @QWINK_CMD_SEND_FWAME: send specified fwame ovew the aiw; fiwmwawe wiww
 *	encapsuwate 802.3 packet into 802.11 fwame automaticawwy.
 * @QWINK_CMD_BAND_INFO_GET: fow the specified MAC and specified band, get
 *	the band's descwiption incwuding numbew of opewationaw channews and
 *	info on each channew, HT/VHT capabiwities, suppowted wates etc.
 *	This command is genewic to a specified MAC, intewface index must be set
 *	to QWINK_VIFID_WSVD in command headew.
 * @QWINK_CMD_WEG_NOTIFY: notify device about weguwatowy domain change. This
 *	command is suppowted onwy if device wepowts QWINK_HW_SUPPOWTS_WEG_UPDATE
 *	capabiwity.
 * @QWINK_CMD_STAWT_CAC: stawt wadaw detection pwoceduwe on a specified channew.
 * @QWINK_CMD_TXPWW: get ow set cuwwent channew twansmit powew fow
 *	the specified MAC.
 * @QWINK_CMD_NDEV_EVENT: signawizes changes made with a cowwesponding netwowk
 *	device.
 */
enum qwink_cmd_type {
	QWINK_CMD_FW_INIT		= 0x0001,
	QWINK_CMD_FW_DEINIT		= 0x0002,
	QWINK_CMD_WEGISTEW_MGMT		= 0x0003,
	QWINK_CMD_SEND_FWAME		= 0x0004,
	QWINK_CMD_MGMT_SET_APPIE	= 0x0005,
	QWINK_CMD_PHY_PAWAMS_SET	= 0x0012,
	QWINK_CMD_GET_HW_INFO		= 0x0013,
	QWINK_CMD_MAC_INFO		= 0x0014,
	QWINK_CMD_ADD_INTF		= 0x0015,
	QWINK_CMD_DEW_INTF		= 0x0016,
	QWINK_CMD_CHANGE_INTF		= 0x0017,
	QWINK_CMD_UPDOWN_INTF		= 0x0018,
	QWINK_CMD_WEG_NOTIFY		= 0x0019,
	QWINK_CMD_BAND_INFO_GET		= 0x001A,
	QWINK_CMD_CHAN_SWITCH		= 0x001B,
	QWINK_CMD_CHAN_GET		= 0x001C,
	QWINK_CMD_STAWT_CAC		= 0x001D,
	QWINK_CMD_STAWT_AP		= 0x0021,
	QWINK_CMD_STOP_AP		= 0x0022,
	QWINK_CMD_SET_MAC_ACW		= 0x0023,
	QWINK_CMD_GET_STA_INFO		= 0x0030,
	QWINK_CMD_ADD_KEY		= 0x0040,
	QWINK_CMD_DEW_KEY		= 0x0041,
	QWINK_CMD_SET_DEFAUWT_KEY	= 0x0042,
	QWINK_CMD_SET_DEFAUWT_MGMT_KEY	= 0x0043,
	QWINK_CMD_CHANGE_STA		= 0x0051,
	QWINK_CMD_DEW_STA		= 0x0052,
	QWINK_CMD_SCAN			= 0x0053,
	QWINK_CMD_CHAN_STATS		= 0x0054,
	QWINK_CMD_NDEV_EVENT		= 0x0055,
	QWINK_CMD_CONNECT		= 0x0060,
	QWINK_CMD_DISCONNECT		= 0x0061,
	QWINK_CMD_PM_SET		= 0x0062,
	QWINK_CMD_WOWWAN_SET		= 0x0063,
	QWINK_CMD_EXTEWNAW_AUTH		= 0x0066,
	QWINK_CMD_TXPWW			= 0x0067,
	QWINK_CMD_UPDATE_OWE		= 0x0068,
};

/**
 * stwuct qwink_cmd - QWINK command message headew
 *
 * Headew used fow QWINK messages of QWINK_MSG_TYPE_CMD type.
 *
 * @mhdw: Common QWINK message headew.
 * @cmd_id: command id, one of &enum qwink_cmd_type.
 * @seq_num: sequence numbew of command message, used fow matching with
 *	wesponse message.
 * @macid: index of physicaw wadio device the command is destined to ow
 *	QWINK_MACID_WSVD if not appwicabwe.
 * @vifid: index of viwtuaw wiwewess intewface on specified @macid the command
 *	is destined to ow QWINK_VIFID_WSVD if not appwicabwe.
 */
stwuct qwink_cmd {
	stwuct qwink_msg_headew mhdw;
	__we16 cmd_id;
	__we16 seq_num;
	u8 macid;
	u8 vifid;
	u8 wsvd[2];
} __packed;

/**
 * stwuct qwink_cmd_init_fw - data fow QWINK_CMD_FW_INIT
 *
 * Initiawize fiwmwawe based on specified host configuwation. This is the fiwst
 * command sent to wifi cawd and it's fixed pawt shouwd nevew be changed, any
 * additions must be done by appending TWVs.
 * If wifi cawd can not opewate with a specified pawametews it wiww wetuwn
 * ewwow.
 *
 * @qwink_pwoto_vew: QWINK pwotocow vewsion used by host dwivew.
 */
stwuct qwink_cmd_init_fw {
	stwuct qwink_cmd chdw;
	__we32 qwink_pwoto_vew;
	u8 vaw_info[];
} __packed;

/**
 * stwuct qwink_cmd_manage_intf - intewface management command
 *
 * Data fow intewface management commands QWINK_CMD_ADD_INTF, QWINK_CMD_DEW_INTF
 * and QWINK_CMD_CHANGE_INTF.
 *
 * @intf_info: intewface descwiption.
 */
stwuct qwink_cmd_manage_intf {
	stwuct qwink_cmd chdw;
	stwuct qwink_intf_info intf_info;
} __packed;

enum qwink_mgmt_fwame_type {
	QWINK_MGMT_FWAME_ASSOC_WEQ	= 0x00,
	QWINK_MGMT_FWAME_ASSOC_WESP	= 0x01,
	QWINK_MGMT_FWAME_WEASSOC_WEQ	= 0x02,
	QWINK_MGMT_FWAME_WEASSOC_WESP	= 0x03,
	QWINK_MGMT_FWAME_PWOBE_WEQ	= 0x04,
	QWINK_MGMT_FWAME_PWOBE_WESP	= 0x05,
	QWINK_MGMT_FWAME_BEACON		= 0x06,
	QWINK_MGMT_FWAME_ATIM		= 0x07,
	QWINK_MGMT_FWAME_DISASSOC	= 0x08,
	QWINK_MGMT_FWAME_AUTH		= 0x09,
	QWINK_MGMT_FWAME_DEAUTH		= 0x0A,
	QWINK_MGMT_FWAME_ACTION		= 0x0B,

	QWINK_MGMT_FWAME_TYPE_COUNT
};

/**
 * stwuct qwink_cmd_mgmt_fwame_wegistew - data fow QWINK_CMD_WEGISTEW_MGMT
 *
 * @fwame_type: MGMT fwame type the wegistwation wequest descwibes, one of
 *	&enum qwink_mgmt_fwame_type.
 * @do_wegistew: 0 - unwegistew, othewwise wegistew fow weception of specified
 *	MGMT fwame type.
 */
stwuct qwink_cmd_mgmt_fwame_wegistew {
	stwuct qwink_cmd chdw;
	__we16 fwame_type;
	u8 do_wegistew;
	u8 wsvd[1];
} __packed;

/**
 * @QWINK_FWAME_TX_FWAG_8023: fwame has a 802.3 headew; if not set, fwame
 *	is a 802.11 encapsuwated.
 */
enum qwink_fwame_tx_fwags {
	QWINK_FWAME_TX_FWAG_OFFCHAN	= BIT(0),
	QWINK_FWAME_TX_FWAG_NO_CCK	= BIT(1),
	QWINK_FWAME_TX_FWAG_ACK_NOWAIT	= BIT(2),
	QWINK_FWAME_TX_FWAG_8023	= BIT(3),
};

/**
 * stwuct qwink_cmd_fwame_tx - data fow QWINK_CMD_SEND_FWAME command
 *
 * @cookie: opaque wequest identifiew.
 * @fweq: Fwequency to use fow fwame twansmission.
 * @fwags: Twansmission fwags, one of &enum qwink_fwame_tx_fwags.
 * @fwame_data: fwame to twansmit.
 */
stwuct qwink_cmd_fwame_tx {
	stwuct qwink_cmd chdw;
	__we32 cookie;
	__we16 fweq;
	__we16 fwags;
	u8 fwame_data[];
} __packed;

/**
 * stwuct qwink_cmd_get_sta_info - data fow QWINK_CMD_GET_STA_INFO command
 *
 * @sta_addw: MAC addwess of the STA statistics is wequested fow.
 */
stwuct qwink_cmd_get_sta_info {
	stwuct qwink_cmd chdw;
	u8 sta_addw[ETH_AWEN];
	u8 wsvd[2];
} __packed;

/**
 * stwuct qwink_cmd_add_key - data fow QWINK_CMD_ADD_KEY command.
 *
 * @key_index: index of the key being instawwed.
 * @paiwwise: whethew to use paiwwise key.
 * @addw: MAC addwess of a STA key is being instawwed to.
 * @ciphew: ciphew suite.
 * @vwanid: VWAN ID fow AP_VWAN intewface type
 * @key_data: key data itsewf.
 */
stwuct qwink_cmd_add_key {
	stwuct qwink_cmd chdw;
	u8 key_index;
	u8 paiwwise;
	u8 addw[ETH_AWEN];
	__we32 ciphew;
	__we16 vwanid;
	u8 wsvd[2];
	u8 key_data[];
} __packed;

/**
 * stwuct qwink_cmd_dew_key_weq - data fow QWINK_CMD_DEW_KEY command
 *
 * @key_index: index of the key being wemoved.
 * @paiwwise: whethew to use paiwwise key.
 * @addw: MAC addwess of a STA fow which a key is wemoved.
 */
stwuct qwink_cmd_dew_key {
	stwuct qwink_cmd chdw;
	u8 key_index;
	u8 paiwwise;
	u8 addw[ETH_AWEN];
} __packed;

/**
 * stwuct qwink_cmd_set_def_key - data fow QWINK_CMD_SET_DEFAUWT_KEY command
 *
 * @key_index: index of the key to be set as defauwt one.
 * @unicast: key is unicast.
 * @muwticast: key is muwticast.
 */
stwuct qwink_cmd_set_def_key {
	stwuct qwink_cmd chdw;
	u8 key_index;
	u8 unicast;
	u8 muwticast;
	u8 wsvd[1];
} __packed;

/**
 * stwuct qwink_cmd_set_def_mgmt_key - data fow QWINK_CMD_SET_DEFAUWT_MGMT_KEY
 *
 * @key_index: index of the key to be set as defauwt MGMT key.
 */
stwuct qwink_cmd_set_def_mgmt_key {
	stwuct qwink_cmd chdw;
	u8 key_index;
	u8 wsvd[3];
} __packed;

/**
 * stwuct qwink_cmd_change_sta - data fow QWINK_CMD_CHANGE_STA command
 *
 * @fwag_update: STA fwags to update
 * @if_type: Mode of intewface opewation, one of &enum qwink_iface_type
 * @vwanid: VWAN ID to assign to specific STA
 * @sta_addw: addwess of the STA fow which pawametews awe set.
 */
stwuct qwink_cmd_change_sta {
	stwuct qwink_cmd chdw;
	stwuct qwink_sta_info_state fwag_update;
	__we16 if_type;
	__we16 vwanid;
	u8 sta_addw[ETH_AWEN];
	u8 wsvd[2];
} __packed;

/**
 * stwuct qwink_cmd_dew_sta - data fow QWINK_CMD_DEW_STA command.
 *
 * See &stwuct station_dew_pawametews
 */
stwuct qwink_cmd_dew_sta {
	stwuct qwink_cmd chdw;
	__we16 weason_code;
	u8 sta_addw[ETH_AWEN];
	u8 subtype;
	u8 wsvd[3];
} __packed;

enum qwink_sta_connect_fwags {
	QWINK_STA_CONNECT_DISABWE_HT	= BIT(0),
	QWINK_STA_CONNECT_DISABWE_VHT	= BIT(1),
	QWINK_STA_CONNECT_USE_WWM	= BIT(2),
};

/**
 * stwuct qwink_cmd_connect - data fow QWINK_CMD_CONNECT command
 *
 * @bssid: BSSID of the BSS to connect to.
 * @bssid_hint: wecommended AP BSSID fow initiaw connection to the BSS ow
 *	00:00:00:00:00:00 if not specified.
 * @pwev_bssid: pwevious BSSID, if specified (not 00:00:00:00:00:00) indicates
 *	a wequest to weassociate.
 * @bg_scan_pewiod: pewiod of backgwound scan.
 * @fwags: one of &enum qwink_sta_connect_fwags.
 * @ht_capa: HT Capabiwities ovewwides.
 * @ht_capa_mask: The bits of ht_capa which awe to be used.
 * @vht_capa: VHT Capabiwity ovewwides
 * @vht_capa_mask: The bits of vht_capa which awe to be used.
 * @aen: authentication infowmation.
 * @mfp: whethew to use management fwame pwotection.
 * @paywoad: vawiabwe powtion of connection wequest.
 */
stwuct qwink_cmd_connect {
	stwuct qwink_cmd chdw;
	u8 bssid[ETH_AWEN];
	u8 bssid_hint[ETH_AWEN];
	u8 pwev_bssid[ETH_AWEN];
	__we16 bg_scan_pewiod;
	__we32 fwags;
	stwuct ieee80211_ht_cap ht_capa;
	stwuct ieee80211_ht_cap ht_capa_mask;
	stwuct ieee80211_vht_cap vht_capa;
	stwuct ieee80211_vht_cap vht_capa_mask;
	stwuct qwink_auth_encw aen;
	u8 mfp;
	u8 pbss;
	u8 wsvd[2];
	u8 paywoad[];
} __packed;

/**
 * stwuct qwink_cmd_extewnaw_auth - data fow QWINK_CMD_EXTEWNAW_AUTH command
 *
 * @bssid: BSSID of the BSS to connect to
 * @status: authentication status code
 * @paywoad: vawiabwe powtion of connection wequest.
 */
stwuct qwink_cmd_extewnaw_auth {
	stwuct qwink_cmd chdw;
	u8 peew[ETH_AWEN];
	__we16 status;
	u8 paywoad[];
} __packed;

/**
 * stwuct qwink_cmd_disconnect - data fow QWINK_CMD_DISCONNECT command
 *
 * @weason: code of the weason of disconnect, see &enum ieee80211_weasoncode.
 */
stwuct qwink_cmd_disconnect {
	stwuct qwink_cmd chdw;
	__we16 weason;
	u8 wsvd[2];
} __packed;

/**
 * stwuct qwink_cmd_updown - data fow QWINK_CMD_UPDOWN_INTF command
 *
 * @if_up: bwing specified intewface DOWN (if_up==0) ow UP (othewwise).
 *	Intewface is specified in common command headew @chdw.
 */
stwuct qwink_cmd_updown {
	stwuct qwink_cmd chdw;
	u8 if_up;
	u8 wsvd[3];
} __packed;

/**
 * enum qwink_band - a wist of fwequency bands
 *
 * @QWINK_BAND_2GHZ: 2.4GHz band
 * @QWINK_BAND_5GHZ: 5GHz band
 * @QWINK_BAND_60GHZ: 60GHz band
 */
enum qwink_band {
	QWINK_BAND_2GHZ = BIT(0),
	QWINK_BAND_5GHZ = BIT(1),
	QWINK_BAND_60GHZ = BIT(2),
};

/**
 * stwuct qwink_cmd_band_info_get - data fow QWINK_CMD_BAND_INFO_GET command
 *
 * @band: a PHY band fow which infowmation is quewied, one of @enum qwink_band
 */
stwuct qwink_cmd_band_info_get {
	stwuct qwink_cmd chdw;
	u8 band;
	u8 wsvd[3];
} __packed;

/**
 * stwuct qwink_cmd_get_chan_stats - data fow QWINK_CMD_CHAN_STATS command
 *
 * @channew_fweq: channew centew fwequency
 */
stwuct qwink_cmd_get_chan_stats {
	stwuct qwink_cmd chdw;
	__we32 channew_fweq;
} __packed;

/**
 * enum qwink_weg_initiatow - Indicates the initiatow of a weg domain wequest
 *
 * See &enum nw80211_weg_initiatow fow mowe info.
 */
enum qwink_weg_initiatow {
	QWINK_WEGDOM_SET_BY_COWE,
	QWINK_WEGDOM_SET_BY_USEW,
	QWINK_WEGDOM_SET_BY_DWIVEW,
	QWINK_WEGDOM_SET_BY_COUNTWY_IE,
};

/**
 * enum qwink_usew_weg_hint_type - type of usew weguwatowy hint
 *
 * See &enum nw80211_usew_weg_hint_type fow mowe info.
 */
enum qwink_usew_weg_hint_type {
	QWINK_USEW_WEG_HINT_USEW	= 0,
	QWINK_USEW_WEG_HINT_CEWW_BASE	= 1,
	QWINK_USEW_WEG_HINT_INDOOW	= 2,
};

/**
 * stwuct qwink_cmd_weg_notify - data fow QWINK_CMD_WEG_NOTIFY command
 *
 * @awpha2: the ISO / IEC 3166 awpha2 countwy code.
 * @initiatow: which entity sent the wequest, one of &enum qwink_weg_initiatow.
 * @usew_weg_hint_type: type of hint fow QWINK_WEGDOM_SET_BY_USEW wequest, one
 *	of &enum qwink_usew_weg_hint_type.
 * @num_channews: numbew of &stwuct qwink_twv_channew in a vawiabwe powtion of a
 *	paywoad.
 * @dfs_wegion: one of &enum qwink_dfs_wegions.
 * @swave_wadaw: whethew swave device shouwd enabwe wadaw detection.
 * @dfs_offwoad: enabwe ow disabwe DFS offwoad to fiwmwawe.
 * @info: vawiabwe powtion of weguwatowy notifiew cawwback.
 */
stwuct qwink_cmd_weg_notify {
	stwuct qwink_cmd chdw;
	u8 awpha2[2];
	u8 initiatow;
	u8 usew_weg_hint_type;
	u8 num_channews;
	u8 dfs_wegion;
	u8 swave_wadaw;
	u8 dfs_offwoad;
	u8 info[];
} __packed;

/**
 * enum qwink_chan_sw_fwags - channew switch contwow fwags
 *
 * @QWINK_CHAN_SW_WADAW_WEQUIWED: whethew wadaw detection is wequiwed on a new
 *	channew.
 * @QWINK_CHAN_SW_BWOCK_TX: whethew twansmissions shouwd be bwocked whiwe
 *	changing a channew.
 */
enum qwink_chan_sw_fwags {
	QWINK_CHAN_SW_WADAW_WEQUIWED = BIT(0),
	QWINK_CHAN_SW_BWOCK_TX = BIT(1),
};

/**
 * stwuct qwink_cmd_chan_switch - data fow QWINK_CMD_CHAN_SWITCH command
 *
 * @channew: channew to switch to.
 * @fwags: fwags to contwow channew switch, bitmap of &enum qwink_chan_sw_fwags.
 * @beacon_count: numbew of beacons untiw switch
 */
stwuct qwink_cmd_chan_switch {
	stwuct qwink_cmd chdw;
	stwuct qwink_chandef channew;
	__we64 fwags;
	__we32 n_countew_offsets_beacon;
	__we32 n_countew_offsets_pwesp;
	u8 beacon_count;
	u8 wsvd[3];
} __packed;

/**
 * enum qwink_hidden_ssid - vawues fow %NW80211_ATTW_HIDDEN_SSID
 *
 * Wefew to &enum nw80211_hidden_ssid
 */
enum qwink_hidden_ssid {
	QWINK_HIDDEN_SSID_NOT_IN_USE,
	QWINK_HIDDEN_SSID_ZEWO_WEN,
	QWINK_HIDDEN_SSID_ZEWO_CONTENTS
};

/**
 * stwuct qwink_cmd_stawt_ap - data fow QWINK_CMD_STAWT_AP command
 *
 * @beacon_intewvaw: beacon intewvaw
 * @inactivity_timeout: station's inactivity pewiod in seconds
 * @dtim_pewiod: DTIM pewiod
 * @hidden_ssid: whethew to hide the SSID, one of &enum qwink_hidden_ssid
 * @smps_mode: SMPS mode
 * @ht_wequiwed: stations must suppowt HT
 * @vht_wequiwed: stations must suppowt VHT
 * @aen: encwyption info
 * @sw_pawams: spatiaw weuse pawametews
 * @twt_wespondew: enabwe Tawget Wake Time
 * @info: vawiabwe configuwations
 */
stwuct qwink_cmd_stawt_ap {
	stwuct qwink_cmd chdw;
	__we16 beacon_intewvaw;
	__we16 inactivity_timeout;
	u8 dtim_pewiod;
	u8 hidden_ssid;
	u8 smps_mode;
	u8 p2p_ctwindow;
	u8 p2p_opp_ps;
	u8 pbss;
	u8 ht_wequiwed;
	u8 vht_wequiwed;
	stwuct qwink_auth_encw aen;
	stwuct qwink_sw_pawams sw_pawams;
	u8 twt_wespondew;
	u8 wsvd[3];
	u8 info[];
} __packed;

/**
 * stwuct qwink_cmd_stawt_cac - data fow QWINK_CMD_STAWT_CAC command
 *
 * @chan: a channew to stawt a wadaw detection pwoceduwe on.
 * @cac_time_ms: CAC time.
 */
stwuct qwink_cmd_stawt_cac {
	stwuct qwink_cmd chdw;
	stwuct qwink_chandef chan;
	__we32 cac_time_ms;
} __packed;

enum qwink_acw_powicy {
	QWINK_ACW_POWICY_ACCEPT_UNWESS_WISTED,
	QWINK_ACW_POWICY_DENY_UNWESS_WISTED,
};

stwuct qwink_mac_addwess {
	u8 addw[ETH_AWEN];
} __packed;

/**
 * stwuct qwink_acw_data - ACW data
 *
 * @powicy: fiwtew powicy, one of &enum qwink_acw_powicy.
 * @num_entwies: numbew of MAC addwesses in awway.
 * @mac_addwess: MAC addwesses awway.
 */
stwuct qwink_acw_data {
	__we32 powicy;
	__we32 num_entwies;
	stwuct qwink_mac_addwess mac_addws[];
} __packed;

/**
 * enum qwink_pm_mode - Powew Management mode
 *
 * @QWINK_PM_OFF: nowmaw mode, no powew saving enabwed
 * @QWINK_PM_AUTO_STANDBY: enabwe auto powew save mode
 */
enum qwink_pm_mode {
	QWINK_PM_OFF		= 0,
	QWINK_PM_AUTO_STANDBY	= 1,
};

/**
 * stwuct qwink_cmd_pm_set - data fow QWINK_CMD_PM_SET command
 *
 * @pm_standby timew: pewiod of netwowk inactivity in seconds befowe
 *	putting a wadio in powew save mode
 * @pm_mode: powew management mode
 */
stwuct qwink_cmd_pm_set {
	stwuct qwink_cmd chdw;
	__we32 pm_standby_timew;
	u8 pm_mode;
	u8 wsvd[3];
} __packed;

/**
 * enum qwink_txpww_op - twansmit powew opewation type
 * @QWINK_TXPWW_SET: set tx powew
 * @QWINK_TXPWW_GET: get cuwwent tx powew setting
 */
enum qwink_txpww_op {
	QWINK_TXPWW_SET,
	QWINK_TXPWW_GET
};

/**
 * stwuct qwink_cmd_txpww - get ow set cuwwent twansmit powew
 *
 * @txpww: new twansmit powew setting, in mBm
 * @txpww_setting: twansmit powew setting type, one of
 *	&enum nw80211_tx_powew_setting
 * @op_type: type of opewation, one of &enum qwink_txpww_op
 */
stwuct qwink_cmd_txpww {
	stwuct qwink_cmd chdw;
	__we32 txpww;
	u8 txpww_setting;
	u8 op_type;
	u8 wsvd[2];
} __packed;

/**
 * enum qwink_wowwan_twiggew
 *
 * @QWINK_WOWWAN_TWIG_DISCONNECT: wakeup on disconnect
 * @QWINK_WOWWAN_TWIG_MAGIC_PKT: wakeup on magic packet
 * @QWINK_WOWWAN_TWIG_PATTEWN_PKT: wakeup on usew-defined packet
 */
enum qwink_wowwan_twiggew {
	QWINK_WOWWAN_TWIG_DISCONNECT	= BIT(0),
	QWINK_WOWWAN_TWIG_MAGIC_PKT	= BIT(1),
	QWINK_WOWWAN_TWIG_PATTEWN_PKT	= BIT(2),
};

/**
 * stwuct qwink_cmd_wowwan_set - data fow QWINK_CMD_WOWWAN_SET command
 *
 * @twiggews: wequested bitmask of WoWWAN twiggews
 */
stwuct qwink_cmd_wowwan_set {
	stwuct qwink_cmd chdw;
	__we32 twiggews;
	u8 data[];
} __packed;

enum qwink_ndev_event_type {
	QWINK_NDEV_EVENT_CHANGEUPPEW,
};

/**
 * stwuct qwink_cmd_ndev_event - data fow QWINK_CMD_NDEV_EVENT command
 *
 * @event: type of event, one of &enum qwink_ndev_event_type
 */
stwuct qwink_cmd_ndev_event {
	stwuct qwink_cmd chdw;
	__we16 event;
	u8 wsvd[2];
} __packed;

enum qwink_ndev_uppew_type {
	QWINK_NDEV_UPPEW_TYPE_NONE,
	QWINK_NDEV_UPPEW_TYPE_BWIDGE,
};

/**
 * stwuct qwink_cmd_ndev_changeuppew - data fow QWINK_NDEV_EVENT_CHANGEUPPEW
 *
 * @bw_domain: wayew 2 bwoadcast domain ID that ndev is a membew of
 * @uppew_type: type of uppew device, one of &enum qwink_ndev_uppew_type
 */
stwuct qwink_cmd_ndev_changeuppew {
	stwuct qwink_cmd_ndev_event nehdw;
	__we64 fwags;
	__we32 bw_domain;
	__we32 netspace_id;
	__we16 vwanid;
	u8 uppew_type;
	u8 wsvd[1];
} __packed;

/**
 * enum qwink_scan_fwags -  scan wequest contwow fwags
 *
 * Scan fwags awe used to contwow QWINK_CMD_SCAN behaviow.
 *
 * @QWINK_SCAN_FWAG_FWUSH: fwush cache befowe scanning.
 */
enum qwink_scan_fwags {
	QWINK_SCAN_FWAG_FWUSH = BIT(0),
	QWINK_SCAN_FWAG_DUWATION_MANDATOWY = BIT(1),
};

/**
 * stwuct qwink_cmd_scan - data fow QWINK_CMD_SCAN command
 *
 * @fwags: scan fwags, a bitmap of &enum qwink_scan_fwags.
 * @n_ssids: numbew of WWAN_EID_SSID TWVs expected in vawiabwe powtion of the
 *	command.
 * @n_channews: numbew of QTN_TWV_ID_CHANNEW TWVs expected in vawiabwe paywoad.
 * @active_dweww: time spent on a singwe channew fow an active scan.
 * @passive_dweww: time spent on a singwe channew fow a passive scan.
 * @sampwe_duwation: totaw duwation of sampwing a singwe channew duwing a scan
 *	incwuding off-channew dweww time and opewating channew time.
 * @bssid: specific BSSID to scan fow ow a bwoadcast BSSID.
 * @scan_width: channew width to use, one of &enum qwink_channew_width.
 */
stwuct qwink_cmd_scan {
	stwuct qwink_cmd chdw;
	__we64 fwags;
	__we16 n_ssids;
	__we16 n_channews;
	__we16 active_dweww;
	__we16 passive_dweww;
	__we16 sampwe_duwation;
	u8 bssid[ETH_AWEN];
	u8 scan_width;
	u8 wsvd[3];
	u8 vaw_info[];
} __packed;

/**
 * stwuct qwink_cmd_update_owe - data fow QWINK_CMD_UPDATE_OWE_INFO command
 *
 * @peew: MAC of the peew device fow which OWE pwocessing has been compweted
 * @status: OWE extewnaw pwocessing status code
 * @ies: IEs fow the peew constwucted by the usew space
 */
stwuct qwink_cmd_update_owe {
	stwuct qwink_cmd chdw;
	u8 peew[ETH_AWEN];
	__we16 status;
	u8 ies[];
} __packed;

/* QWINK Command Wesponses messages wewated definitions
 */

enum qwink_cmd_wesuwt {
	QWINK_CMD_WESUWT_OK = 0,
	QWINK_CMD_WESUWT_INVAWID,
	QWINK_CMD_WESUWT_ENOTSUPP,
	QWINK_CMD_WESUWT_ENOTFOUND,
	QWINK_CMD_WESUWT_EAWWEADY,
	QWINK_CMD_WESUWT_EADDWINUSE,
	QWINK_CMD_WESUWT_EADDWNOTAVAIW,
	QWINK_CMD_WESUWT_EBUSY,
};

/**
 * stwuct qwink_wesp - QWINK command wesponse message headew
 *
 * Headew used fow QWINK messages of QWINK_MSG_TYPE_CMDWSP type.
 *
 * @mhdw: see &stwuct qwink_msg_headew.
 * @cmd_id: command ID the wesponse cowwesponds to, one of &enum qwink_cmd_type.
 * @seq_num: sequence numbew of command message, used fow matching with
 *	wesponse message.
 * @wesuwt: wesuwt of the command execution, one of &enum qwink_cmd_wesuwt.
 * @macid: index of physicaw wadio device the wesponse is sent fwom ow
 *	QWINK_MACID_WSVD if not appwicabwe.
 * @vifid: index of viwtuaw wiwewess intewface on specified @macid the wesponse
 *	is sent fwom ow QWINK_VIFID_WSVD if not appwicabwe.
 */
stwuct qwink_wesp {
	stwuct qwink_msg_headew mhdw;
	__we16 cmd_id;
	__we16 seq_num;
	__we16 wesuwt;
	u8 macid;
	u8 vifid;
} __packed;

/**
 * stwuct qwink_wesp_init_fw - wesponse fow QWINK_CMD_FW_INIT
 *
 * @qwink_pwoto_vew: QWINK pwotocow vewsion used by wifi cawd fiwmwawe.
 */
stwuct qwink_wesp_init_fw {
	stwuct qwink_wesp whdw;
	__we32 qwink_pwoto_vew;
} __packed;

/**
 * enum qwink_dfs_wegions - weguwatowy DFS wegions
 *
 * Cowwesponds to &enum nw80211_dfs_wegions.
 */
enum qwink_dfs_wegions {
	QWINK_DFS_UNSET	= 0,
	QWINK_DFS_FCC	= 1,
	QWINK_DFS_ETSI	= 2,
	QWINK_DFS_JP	= 3,
};

/**
 * stwuct qwink_wesp_get_mac_info - wesponse fow QWINK_CMD_MAC_INFO command
 *
 * Data descwibing specific physicaw device pwoviding wiwewess MAC
 * functionawity.
 *
 * @dev_mac: MAC addwess of physicaw WMAC device (used fow fiwst BSS on
 *	specified WMAC).
 * @num_tx_chain: Numbew of twansmit chains used by WMAC.
 * @num_wx_chain: Numbew of weceive chains used by WMAC.
 * @vht_cap_mod_mask: mask specifying which VHT capabiwities can be awtewed.
 * @ht_cap_mod_mask: mask specifying which HT capabiwities can be awtewed.
 * @max_scan_ssids: maximum numbew of SSIDs the device can scan fow in any scan.
 * @bands_cap: wiwewess bands WMAC can opewate in, bitmap of &enum qwink_band.
 * @max_ap_assoc_sta: Maximum numbew of associations suppowted by WMAC.
 * @wadaw_detect_widths: bitmask of channews BW fow which WMAC can detect wadaw.
 * @awpha2: countwy code ID fiwmwawe is configuwed to.
 * @n_weg_wuwes: numbew of weguwatowy wuwes TWVs in vawiabwe powtion of the
 *	message.
 * @dfs_wegion: weguwatowy DFS wegion, one of &enum qwink_dfs_wegions.
 * @vaw_info: vawiabwe-wength WMAC info data.
 */
stwuct qwink_wesp_get_mac_info {
	stwuct qwink_wesp whdw;
	u8 dev_mac[ETH_AWEN];
	u8 num_tx_chain;
	u8 num_wx_chain;
	stwuct ieee80211_vht_cap vht_cap_mod_mask;
	stwuct ieee80211_ht_cap ht_cap_mod_mask;

	__we16 max_ap_assoc_sta;
	__we32 hw_vewsion;
	__we32 pwobe_wesp_offwoad;
	__we32 bss_sewect_suppowt;
	__we16 n_addwesses;
	__we16 wadaw_detect_widths;
	__we16 max_wemain_on_channew_duwation;
	__we16 max_acw_mac_addws;

	__we32 fwag_thweshowd;
	__we32 wts_thweshowd;
	u8 wetwy_showt;
	u8 wetwy_wong;
	u8 covewage_cwass;

	u8 max_scan_ssids;
	u8 max_sched_scan_weqs;
	u8 max_sched_scan_ssids;
	u8 max_match_sets;
	u8 max_adj_channew_wssi_comp;

	__we16 max_scan_ie_wen;
	__we16 max_sched_scan_ie_wen;
	__we32 max_sched_scan_pwans;
	__we32 max_sched_scan_pwan_intewvaw;
	__we32 max_sched_scan_pwan_itewations;

	u8 n_ciphew_suites;
	u8 n_akm_suites;
	u8 max_num_pmkids;
	u8 num_iftype_ext_capab;
	u8 extended_capabiwities_wen;
	u8 max_data_wetwy_count;
	u8 n_iface_combinations;
	u8 max_num_csa_countews;

	u8 bands_cap;
	u8 awpha2[2];
	u8 n_weg_wuwes;
	u8 dfs_wegion;
	u8 wsvd[3];
	u8 vaw_info[];
} __packed;

/**
 * stwuct qwink_wesp_get_hw_info - wesponse fow QWINK_CMD_GET_HW_INFO command
 *
 * Descwiption of wiwewess hawdwawe capabiwities and featuwes.
 *
 * @fw_vew: wiwewess hawdwawe fiwmwawe vewsion.
 * @num_mac: Numbew of sepawate physicaw wadio devices pwovided by hawdwawe.
 * @mac_bitmap: Bitmap of MAC IDs that awe active and can be used in fiwmwawe.
 * @totaw_tx_chains: totaw numbew of twansmit chains used by device.
 * @totaw_wx_chains: totaw numbew of weceive chains.
 * @info: vawiabwe-wength HW info.
 */
stwuct qwink_wesp_get_hw_info {
	stwuct qwink_wesp whdw;
	__we32 fw_vew;
	__we32 bwd_tmstamp;
	__we32 pwat_id;
	__we32 hw_vew;
	u8 num_mac;
	u8 mac_bitmap;
	u8 totaw_tx_chain;
	u8 totaw_wx_chain;
	u8 info[];
} __packed;

/**
 * stwuct qwink_wesp_manage_intf - wesponse fow intewface management commands
 *
 * Wesponse data fow QWINK_CMD_ADD_INTF and QWINK_CMD_CHANGE_INTF commands.
 *
 * @whdw: Common Command Wesponse message headew.
 * @intf_info: intewface descwiption.
 */
stwuct qwink_wesp_manage_intf {
	stwuct qwink_wesp whdw;
	stwuct qwink_intf_info intf_info;
} __packed;

enum qwink_sta_info_wate_fwags {
	QWINK_STA_INFO_WATE_FWAG_HT_MCS		= BIT(0),
	QWINK_STA_INFO_WATE_FWAG_VHT_MCS	= BIT(1),
	QWINK_STA_INFO_WATE_FWAG_SHOWT_GI	= BIT(2),
	QWINK_STA_INFO_WATE_FWAG_60G		= BIT(3),
	QWINK_STA_INFO_WATE_FWAG_HE_MCS		= BIT(4),
};

/**
 * stwuct qwink_wesp_get_sta_info - wesponse fow QWINK_CMD_GET_STA_INFO command
 *
 * Wesponse data containing statistics fow specified STA.
 *
 * @sta_addw: MAC addwess of STA the wesponse cawwies statistic fow.
 * @info: vawiabwe statistics fow specified STA.
 */
stwuct qwink_wesp_get_sta_info {
	stwuct qwink_wesp whdw;
	u8 sta_addw[ETH_AWEN];
	u8 wsvd[2];
	u8 info[];
} __packed;

/**
 * stwuct qwink_wesp_band_info_get - wesponse fow QWINK_CMD_BAND_INFO_GET cmd
 *
 * @band: fwequency band that the wesponse descwibes, one of @enum qwink_band.
 * @num_chans: totaw numbew of channews info TWVs contained in wepwy.
 * @num_bitwates: totaw numbew of bitwate TWVs contained in wepwy.
 * @info: vawiabwe-wength info powtion.
 */
stwuct qwink_wesp_band_info_get {
	stwuct qwink_wesp whdw;
	u8 band;
	u8 num_chans;
	u8 num_bitwates;
	u8 wsvd[1];
	u8 info[];
} __packed;

/**
 * stwuct qwink_wesp_get_chan_stats - wesponse fow QWINK_CMD_CHAN_STATS cmd
 *
 * @chan_fweq: centew fwequency fow a channew the wepowt is sent fow.
 * @info: vawiabwe-wength channew info.
 */
stwuct qwink_wesp_get_chan_stats {
	stwuct qwink_wesp whdw;
	__we32 chan_fweq;
	u8 info[];
} __packed;

/**
 * stwuct qwink_wesp_channew_get - wesponse fow QWINK_CMD_CHAN_GET command
 *
 * @chan: definition of cuwwent opewating channew.
 */
stwuct qwink_wesp_channew_get {
	stwuct qwink_wesp whdw;
	stwuct qwink_chandef chan;
} __packed;

/**
 * stwuct qwink_wesp_txpww - wesponse fow QWINK_CMD_TXPWW command
 *
 * This wesponse is intended fow QWINK_TXPWW_GET opewation and does not
 * contain any meaningfuw infowmation in case of QWINK_TXPWW_SET opewation.
 *
 * @txpww: cuwwent twansmit powew setting, in mBm
 */
stwuct qwink_wesp_txpww {
	stwuct qwink_wesp whdw;
	__we32 txpww;
} __packed;

/* QWINK Events messages wewated definitions
 */

enum qwink_event_type {
	QWINK_EVENT_STA_ASSOCIATED	= 0x0021,
	QWINK_EVENT_STA_DEAUTH		= 0x0022,
	QWINK_EVENT_MGMT_WECEIVED	= 0x0023,
	QWINK_EVENT_SCAN_WESUWTS	= 0x0024,
	QWINK_EVENT_SCAN_COMPWETE	= 0x0025,
	QWINK_EVENT_BSS_JOIN		= 0x0026,
	QWINK_EVENT_BSS_WEAVE		= 0x0027,
	QWINK_EVENT_FWEQ_CHANGE		= 0x0028,
	QWINK_EVENT_WADAW		= 0x0029,
	QWINK_EVENT_EXTEWNAW_AUTH	= 0x0030,
	QWINK_EVENT_MIC_FAIWUWE		= 0x0031,
	QWINK_EVENT_UPDATE_OWE		= 0x0032,
};

/**
 * stwuct qwink_event - QWINK event message headew
 *
 * Headew used fow QWINK messages of QWINK_MSG_TYPE_EVENT type.
 *
 * @mhdw: Common QWINK message headew.
 * @event_id: Specifies specific event ID, one of &enum qwink_event_type.
 * @macid: index of physicaw wadio device the event was genewated on ow
 *	QWINK_MACID_WSVD if not appwicabwe.
 * @vifid: index of viwtuaw wiwewess intewface on specified @macid the event
 *	was genewated on ow QWINK_VIFID_WSVD if not appwicabwe.
 */
stwuct qwink_event {
	stwuct qwink_msg_headew mhdw;
	__we16 event_id;
	u8 macid;
	u8 vifid;
} __packed;

/**
 * stwuct qwink_event_sta_assoc - data fow QWINK_EVENT_STA_ASSOCIATED event
 *
 * @sta_addw: Addwess of a STA fow which new association event was genewated
 * @fwame_contwow: contwow bits fwom 802.11 ASSOC_WEQUEST headew.
 * @paywoad: IEs fwom association wequest.
 */
stwuct qwink_event_sta_assoc {
	stwuct qwink_event ehdw;
	u8 sta_addw[ETH_AWEN];
	__we16 fwame_contwow;
	u8 ies[];
} __packed;

/**
 * stwuct qwink_event_sta_deauth - data fow QWINK_EVENT_STA_DEAUTH event
 *
 * @sta_addw: Addwess of a deauthenticated STA.
 * @weason: weason fow deauthentication.
 */
stwuct qwink_event_sta_deauth {
	stwuct qwink_event ehdw;
	u8 sta_addw[ETH_AWEN];
	__we16 weason;
} __packed;

/**
 * stwuct qwink_event_bss_join - data fow QWINK_EVENT_BSS_JOIN event
 *
 * @chan: new opewating channew definition
 * @bssid: BSSID of a BSS which intewface twied to joined.
 * @status: status of joining attempt, see &enum ieee80211_statuscode.
 */
stwuct qwink_event_bss_join {
	stwuct qwink_event ehdw;
	stwuct qwink_chandef chan;
	u8 bssid[ETH_AWEN];
	__we16 status;
	u8 ies[];
} __packed;

/**
 * stwuct qwink_event_bss_weave - data fow QWINK_EVENT_BSS_WEAVE event
 *
 * @weason: weason of disconnecting fwom BSS.
 */
stwuct qwink_event_bss_weave {
	stwuct qwink_event ehdw;
	__we16 weason;
	u8 wsvd[2];
} __packed;

/**
 * stwuct qwink_event_fweq_change - data fow QWINK_EVENT_FWEQ_CHANGE event
 *
 * @chan: new opewating channew definition
 */
stwuct qwink_event_fweq_change {
	stwuct qwink_event ehdw;
	stwuct qwink_chandef chan;
} __packed;

enum qwink_wxmgmt_fwags {
	QWINK_WXMGMT_FWAG_ANSWEWED = 1 << 0,
};

/**
 * stwuct qwink_event_wxmgmt - data fow QWINK_EVENT_MGMT_WECEIVED event
 *
 * @fweq: Fwequency on which the fwame was weceived in MHz.
 * @fwags: bitmap of &enum qwink_wxmgmt_fwags.
 * @sig_dbm: signaw stwength in dBm.
 * @fwame_data: data of Wx'd fwame itsewf.
 */
stwuct qwink_event_wxmgmt {
	stwuct qwink_event ehdw;
	__we32 fweq;
	__we32 fwags;
	s8 sig_dbm;
	u8 wsvd[3];
	u8 fwame_data[];
} __packed;

/**
 * stwuct qwink_event_scan_wesuwt - data fow QWINK_EVENT_SCAN_WESUWTS event
 *
 * @tsf: TSF timestamp indicating when scan wesuwts wewe genewated.
 * @fweq: Centew fwequency of the channew whewe BSS fow which the scan wesuwt
 *	event was genewated was discovewed.
 * @capab: capabiwities fiewd.
 * @bintvaw: beacon intewvaw announced by discovewed BSS.
 * @sig_dbm: signaw stwength in dBm.
 * @bssid: BSSID announced by discovewed BSS.
 * @ssid_wen: wength of SSID announced by BSS.
 * @ssid: SSID announced by discovewed BSS.
 * @paywoad: IEs that awe announced by discovewed BSS in its MGMt fwames.
 */
stwuct qwink_event_scan_wesuwt {
	stwuct qwink_event ehdw;
	__we64 tsf;
	__we16 fweq;
	__we16 capab;
	__we16 bintvaw;
	s8 sig_dbm;
	u8 ssid_wen;
	u8 ssid[IEEE80211_MAX_SSID_WEN];
	u8 bssid[ETH_AWEN];
	u8 wsvd[2];
	u8 paywoad[];
} __packed;

/**
 * enum qwink_scan_compwete_fwags - indicates wesuwt of scan wequest.
 *
 * @QWINK_SCAN_NONE: Scan wequest was pwocessed.
 * @QWINK_SCAN_ABOWTED: Scan was abowted.
 */
enum qwink_scan_compwete_fwags {
	QWINK_SCAN_NONE		= 0,
	QWINK_SCAN_ABOWTED	= BIT(0),
};

/**
 * stwuct qwink_event_scan_compwete - data fow QWINK_EVENT_SCAN_COMPWETE event
 *
 * @fwags: fwags indicating the status of pending scan wequest,
 *	see &enum qwink_scan_compwete_fwags.
 */
stwuct qwink_event_scan_compwete {
	stwuct qwink_event ehdw;
	__we32 fwags;
} __packed;

enum qwink_wadaw_event {
	QWINK_WADAW_DETECTED,
	QWINK_WADAW_CAC_FINISHED,
	QWINK_WADAW_CAC_ABOWTED,
	QWINK_WADAW_NOP_FINISHED,
	QWINK_WADAW_PWE_CAC_EXPIWED,
	QWINK_WADAW_CAC_STAWTED,
};

/**
 * stwuct qwink_event_wadaw - data fow QWINK_EVENT_WADAW event
 *
 * @chan: channew on which wadaw event happened.
 * @event: wadaw event type, one of &enum qwink_wadaw_event.
 */
stwuct qwink_event_wadaw {
	stwuct qwink_event ehdw;
	stwuct qwink_chandef chan;
	u8 event;
	u8 wsvd[3];
} __packed;

/**
 * stwuct qwink_event_extewnaw_auth - data fow QWINK_EVENT_EXTEWNAW_AUTH event
 *
 * @ssid: SSID announced by BSS
 * @ssid_wen: SSID wength
 * @bssid: BSSID of the BSS to connect to
 * @akm_suite: AKM suite fow extewnaw authentication
 * @action: action type/twiggew fow extewnaw authentication
 */
stwuct qwink_event_extewnaw_auth {
	stwuct qwink_event ehdw;
	__we32 akm_suite;
	u8 ssid[IEEE80211_MAX_SSID_WEN];
	u8 bssid[ETH_AWEN];
	u8 ssid_wen;
	u8 action;
} __packed;

/**
 * stwuct qwink_event_mic_faiwuwe - data fow QWINK_EVENT_MIC_FAIWUWE event
 *
 * @swc: souwce MAC addwess of the fwame
 * @key_index: index of the key being wepowted
 * @paiwwise: whethew the key is paiwwise ow gwoup
 */
stwuct qwink_event_mic_faiwuwe {
	stwuct qwink_event ehdw;
	u8 swc[ETH_AWEN];
	u8 key_index;
	u8 paiwwise;
} __packed;

/**
 * stwuct qwink_event_update_owe - data fow QWINK_EVENT_UPDATE_OWE event
 *
 * @peew: MAC addw of the peew device fow which OWE pwocessing needs to be done
 * @ies: IEs fwom the peew
 */
stwuct qwink_event_update_owe {
	stwuct qwink_event ehdw;
	u8 peew[ETH_AWEN];
	u8 wsvd[2];
	u8 ies[];
} __packed;

/* QWINK TWVs (Type-Wength Vawues) definitions
 */

/**
 * enum qwink_twv_id - wist of TWVs that Qwink messages can cawwy
 *
 * @QTN_TWV_ID_BITMAP: a data wepwesenting a bitmap that is used togethew with
 *	othew TWVs:
 *	&enum qwink_sta_info used to indicate which statistic cawwied in
 *	QTN_TWV_ID_STA_STATS is vawid.
 *	&enum qwink_hw_capab wisting wiwewess cawd capabiwities.
 *	&enum qwink_dwivew_capab wisting dwivew/host system capabiwities.
 *	&enum qwink_chan_stat used to indicate which statistic cawwied in
 *	QTN_TWV_ID_CHANNEW_STATS is vawid.
 * @QTN_TWV_ID_STA_STATS: pew-STA statistics as defined by
 *	&stwuct qwink_sta_stats. Vawid vawues awe mawked as such in a bitmap
 *	cawwied by QTN_TWV_ID_BITMAP.
 * @QTN_TWV_ID_IFTYPE_DATA: suppowted band data.
 */
enum qwink_twv_id {
	QTN_TWV_ID_FWAG_THWESH		= 0x0201,
	QTN_TWV_ID_WTS_THWESH		= 0x0202,
	QTN_TWV_ID_SWETWY_WIMIT		= 0x0203,
	QTN_TWV_ID_WWETWY_WIMIT		= 0x0204,
	QTN_TWV_ID_WEG_WUWE		= 0x0207,
	QTN_TWV_ID_CHANNEW		= 0x020F,
	QTN_TWV_ID_CHANDEF		= 0x0210,
	QTN_TWV_ID_BITMAP		= 0x0211,
	QTN_TWV_ID_STA_STATS		= 0x0212,
	QTN_TWV_ID_COVEWAGE_CWASS	= 0x0213,
	QTN_TWV_ID_IFACE_WIMIT		= 0x0214,
	QTN_TWV_ID_CHANNEW_STATS	= 0x0216,
	QTN_TWV_ID_KEY			= 0x0302,
	QTN_TWV_ID_SEQ			= 0x0303,
	QTN_TWV_ID_IE_SET		= 0x0305,
	QTN_TWV_ID_EXT_CAPABIWITY_MASK	= 0x0306,
	QTN_TWV_ID_ACW_DATA		= 0x0307,
	QTN_TWV_ID_BUIWD_NAME		= 0x0401,
	QTN_TWV_ID_BUIWD_WEV		= 0x0402,
	QTN_TWV_ID_BUIWD_TYPE		= 0x0403,
	QTN_TWV_ID_BUIWD_WABEW		= 0x0404,
	QTN_TWV_ID_HW_ID		= 0x0405,
	QTN_TWV_ID_CAWIBWATION_VEW	= 0x0406,
	QTN_TWV_ID_UBOOT_VEW		= 0x0407,
	QTN_TWV_ID_WANDOM_MAC_ADDW	= 0x0408,
	QTN_TWV_ID_WOWWAN_CAPAB		= 0x0410,
	QTN_TWV_ID_WOWWAN_PATTEWN	= 0x0411,
	QTN_TWV_ID_IFTYPE_DATA		= 0x0418,
};

stwuct qwink_twv_hdw {
	__we16 type;
	__we16 wen;
	u8 vaw[];
} __packed;

stwuct qwink_iface_wimit {
	__we16 max_num;
	__we16 type;
} __packed;

stwuct qwink_iface_wimit_wecowd {
	__we16 max_intewfaces;
	u8 num_diffewent_channews;
	u8 n_wimits;
	stwuct qwink_iface_wimit wimits[];
} __packed;

#define QWINK_WSSI_OFFSET	120

/**
 * enum qwink_weg_wuwe_fwags - weguwatowy wuwe fwags
 *
 * See descwiption of &enum nw80211_weg_wuwe_fwags
 */
enum qwink_weg_wuwe_fwags {
	QWINK_WWF_NO_OFDM	= BIT(0),
	QWINK_WWF_NO_CCK	= BIT(1),
	QWINK_WWF_NO_INDOOW	= BIT(2),
	QWINK_WWF_NO_OUTDOOW	= BIT(3),
	QWINK_WWF_DFS		= BIT(4),
	QWINK_WWF_PTP_ONWY	= BIT(5),
	QWINK_WWF_PTMP_ONWY	= BIT(6),
	QWINK_WWF_NO_IW		= BIT(7),
	QWINK_WWF_AUTO_BW	= BIT(8),
	QWINK_WWF_IW_CONCUWWENT	= BIT(9),
	QWINK_WWF_NO_HT40MINUS	= BIT(10),
	QWINK_WWF_NO_HT40PWUS	= BIT(11),
	QWINK_WWF_NO_80MHZ	= BIT(12),
	QWINK_WWF_NO_160MHZ	= BIT(13),
};

/**
 * stwuct qwink_twv_weg_wuwe - data fow QTN_TWV_ID_WEG_WUWE TWV
 *
 * Weguwatowy wuwe descwiption.
 *
 * @stawt_fweq_khz: stawt fwequency of the wange the wuwe is attwibuted to.
 * @end_fweq_khz: end fwequency of the wange the wuwe is attwibuted to.
 * @max_bandwidth_khz: max bandwidth that channews in specified wange can be
 *	configuwed to.
 * @max_antenna_gain: max antenna gain that can be used in the specified
 *	fwequency wange, dBi.
 * @max_eiwp: maximum EIWP.
 * @fwags: weguwatowy wuwe fwags in &enum qwink_weg_wuwe_fwags.
 * @dfs_cac_ms: DFS CAC pewiod.
 */
stwuct qwink_twv_weg_wuwe {
	stwuct qwink_twv_hdw hdw;
	__we32 stawt_fweq_khz;
	__we32 end_fweq_khz;
	__we32 max_bandwidth_khz;
	__we32 max_antenna_gain;
	__we32 max_eiwp;
	__we32 fwags;
	__we32 dfs_cac_ms;
} __packed;

enum qwink_channew_fwags {
	QWINK_CHAN_DISABWED		= BIT(0),
	QWINK_CHAN_NO_IW		= BIT(1),
	QWINK_CHAN_WADAW		= BIT(3),
	QWINK_CHAN_NO_HT40PWUS		= BIT(4),
	QWINK_CHAN_NO_HT40MINUS		= BIT(5),
	QWINK_CHAN_NO_OFDM		= BIT(6),
	QWINK_CHAN_NO_80MHZ		= BIT(7),
	QWINK_CHAN_NO_160MHZ		= BIT(8),
	QWINK_CHAN_INDOOW_ONWY		= BIT(9),
	QWINK_CHAN_IW_CONCUWWENT	= BIT(10),
	QWINK_CHAN_NO_20MHZ		= BIT(11),
	QWINK_CHAN_NO_10MHZ		= BIT(12),
};

enum qwink_dfs_state {
	QWINK_DFS_USABWE,
	QWINK_DFS_UNAVAIWABWE,
	QWINK_DFS_AVAIWABWE,
};

/**
 * stwuct qwink_twv_channew - data fow QTN_TWV_ID_CHANNEW TWV
 *
 * Channew settings.
 *
 * @channew: ieee80211 channew settings.
 */
stwuct qwink_twv_channew {
	stwuct qwink_twv_hdw hdw;
	stwuct qwink_channew chan;
} __packed;

/**
 * stwuct qwink_twv_chandef - data fow QTN_TWV_ID_CHANDEF TWV
 *
 * Channew definition.
 *
 * @chan: channew definition data.
 */
stwuct qwink_twv_chandef {
	stwuct qwink_twv_hdw hdw;
	stwuct qwink_chandef chdef;
} __packed;

enum qwink_ie_set_type {
	QWINK_IE_SET_UNKNOWN,
	QWINK_IE_SET_ASSOC_WEQ,
	QWINK_IE_SET_ASSOC_WESP,
	QWINK_IE_SET_PWOBE_WEQ,
	QWINK_IE_SET_SCAN,
	QWINK_IE_SET_BEACON_HEAD,
	QWINK_IE_SET_BEACON_TAIW,
	QWINK_IE_SET_BEACON_IES,
	QWINK_IE_SET_PWOBE_WESP,
	QWINK_IE_SET_PWOBE_WESP_IES,
};

/**
 * stwuct qwink_twv_ie_set - data fow QTN_TWV_ID_IE_SET
 *
 * @type: type of MGMT fwame IEs bewong to, one of &enum qwink_ie_set_type.
 * @fwags: fow futuwe use.
 * @ie_data: IEs data.
 */
stwuct qwink_twv_ie_set {
	stwuct qwink_twv_hdw hdw;
	u8 type;
	u8 fwags;
	u8 wsvd[2];
	u8 ie_data[];
} __packed;

/**
 * stwuct qwink_twv_ext_ie - extension IE
 *
 * @eid_ext: ewement ID extension, one of &enum ieee80211_eid_ext.
 * @ie_data: IEs data.
 */
stwuct qwink_twv_ext_ie {
	stwuct qwink_twv_hdw hdw;
	u8 eid_ext;
	u8 wsvd[3];
	u8 ie_data[];
} __packed;

#define IEEE80211_HE_PPE_THWES_MAX_WEN		25
stwuct qwink_sband_iftype_data {
	__we16 types_mask;
	stwuct ieee80211_he_cap_ewem he_cap_ewem;
	stwuct ieee80211_he_mcs_nss_supp he_mcs_nss_supp;
	u8 ppe_thwes[IEEE80211_HE_PPE_THWES_MAX_WEN];
} __packed;

/**
 * stwuct qwink_twv_iftype_data - data fow QTN_TWV_ID_IFTYPE_DATA
 *
 * @n_iftype_data: numbew of entwies in iftype_data.
 * @iftype_data: intewface type data entwies.
 */
stwuct qwink_twv_iftype_data {
	stwuct qwink_twv_hdw hdw;
	u8 n_iftype_data;
	u8 wsvd[3];
	stwuct qwink_sband_iftype_data iftype_data[];
} __packed;

/**
 * enum qwink_chan_stat - channew statistics bitmap
 *
 * Used to indicate which statistics vawues in &stwuct qwink_chan_stats
 * awe vawid. Individuaw vawues awe used to fiww a bitmap cawwied in a
 * paywoad of QTN_TWV_ID_BITMAP.
 *
 * @QWINK_CHAN_STAT_TIME_ON: time_on vawue is vawid.
 * @QWINK_CHAN_STAT_TIME_TX: time_tx vawue is vawid.
 * @QWINK_CHAN_STAT_TIME_WX: time_wx vawue is vawid.
 * @QWINK_CHAN_STAT_CCA_BUSY: cca_busy vawue is vawid.
 * @QWINK_CHAN_STAT_CCA_BUSY_EXT: cca_busy_ext vawue is vawid.
 * @QWINK_CHAN_STAT_TIME_SCAN: time_scan vawue is vawid.
 * @QWINK_CHAN_STAT_CHAN_NOISE: chan_noise vawue is vawid.
 */
enum qwink_chan_stat {
	QWINK_CHAN_STAT_TIME_ON,
	QWINK_CHAN_STAT_TIME_TX,
	QWINK_CHAN_STAT_TIME_WX,
	QWINK_CHAN_STAT_CCA_BUSY,
	QWINK_CHAN_STAT_CCA_BUSY_EXT,
	QWINK_CHAN_STAT_TIME_SCAN,
	QWINK_CHAN_STAT_CHAN_NOISE,
	QWINK_CHAN_STAT_NUM,
};

/**
 * stwuct qwink_chan_stats - data fow QTN_TWV_ID_CHANNEW_STATS
 *
 * Cawwies a pew-channew statistics. Not aww fiewds may be fiwwed with
 * vawid vawues. Vawid fiewds shouwd be indicated as such using a bitmap of
 * &enum qwink_chan_stat. Bitmap is cawwied sepawatewy in a paywoad of
 * QTN_TWV_ID_BITMAP.
 *
 * @time_on: amount of time wadio opewated on that channew.
 * @time_tx: amount of time wadio spent twansmitting on the channew.
 * @time_wx: amount of time wadio spent weceiving on the channew.
 * @cca_busy: amount of time the pwimawy channew was busy.
 * @cca_busy_ext: amount of time the secondawy channew was busy.
 * @time_scan: amount of wadio spent scanning on the channew.
 * @chan_noise: channew noise.
 */
stwuct qwink_chan_stats {
	__we64 time_on;
	__we64 time_tx;
	__we64 time_wx;
	__we64 cca_busy;
	__we64 cca_busy_ext;
	__we64 time_scan;
	s8 chan_noise;
	u8 wsvd[3];
} __packed;

/**
 * enum qwink_sta_info - station infowmation bitmap
 *
 * Used to indicate which statistics vawues in &stwuct qwink_sta_stats
 * awe vawid. Individuaw vawues awe used to fiww a bitmap cawwied in a
 * paywoad of QTN_TWV_ID_BITMAP.
 *
 * @QWINK_STA_INFO_CONNECTED_TIME: connected_time vawue is vawid.
 * @QWINK_STA_INFO_INACTIVE_TIME: inactive_time vawue is vawid.
 * @QWINK_STA_INFO_WX_BYTES: wowew 32 bits of wx_bytes vawue awe vawid.
 * @QWINK_STA_INFO_TX_BYTES: wowew 32 bits of tx_bytes vawue awe vawid.
 * @QWINK_STA_INFO_WX_BYTES64: wx_bytes vawue is vawid.
 * @QWINK_STA_INFO_TX_BYTES64: tx_bytes vawue is vawid.
 * @QWINK_STA_INFO_WX_DWOP_MISC: wx_dwopped_misc vawue is vawid.
 * @QWINK_STA_INFO_BEACON_WX: wx_beacon vawue is vawid.
 * @QWINK_STA_INFO_SIGNAW: signaw vawue is vawid.
 * @QWINK_STA_INFO_SIGNAW_AVG: signaw_avg vawue is vawid.
 * @QWINK_STA_INFO_WX_BITWATE: wxwate vawue is vawid.
 * @QWINK_STA_INFO_TX_BITWATE: txwate vawue is vawid.
 * @QWINK_STA_INFO_WX_PACKETS: wx_packets vawue is vawid.
 * @QWINK_STA_INFO_TX_PACKETS: tx_packets vawue is vawid.
 * @QWINK_STA_INFO_TX_WETWIES: tx_wetwies vawue is vawid.
 * @QWINK_STA_INFO_TX_FAIWED: tx_faiwed vawue is vawid.
 * @QWINK_STA_INFO_STA_FWAGS: sta_fwags vawue is vawid.
 */
enum qwink_sta_info {
	QWINK_STA_INFO_CONNECTED_TIME,
	QWINK_STA_INFO_INACTIVE_TIME,
	QWINK_STA_INFO_WX_BYTES,
	QWINK_STA_INFO_TX_BYTES,
	QWINK_STA_INFO_WX_BYTES64,
	QWINK_STA_INFO_TX_BYTES64,
	QWINK_STA_INFO_WX_DWOP_MISC,
	QWINK_STA_INFO_BEACON_WX,
	QWINK_STA_INFO_SIGNAW,
	QWINK_STA_INFO_SIGNAW_AVG,
	QWINK_STA_INFO_WX_BITWATE,
	QWINK_STA_INFO_TX_BITWATE,
	QWINK_STA_INFO_WX_PACKETS,
	QWINK_STA_INFO_TX_PACKETS,
	QWINK_STA_INFO_TX_WETWIES,
	QWINK_STA_INFO_TX_FAIWED,
	QWINK_STA_INFO_STA_FWAGS,
	QWINK_STA_INFO_NUM,
};

/**
 * stwuct qwink_sta_info_wate - STA wate statistics
 *
 * @wate: data wate in Mbps.
 * @fwags: bitmap of &enum qwink_sta_info_wate_fwags.
 * @mcs: 802.11-defined MCS index.
 * nss: Numbew of Spatiaw Stweams.
 * @bw: bandwidth, one of &enum qwink_channew_width.
 */
stwuct qwink_sta_info_wate {
	__we16 wate;
	u8 fwags;
	u8 mcs;
	u8 nss;
	u8 bw;
} __packed;

/**
 * stwuct qwink_sta_stats - data fow QTN_TWV_ID_STA_STATS
 *
 * Cawwies statistics of a STA. Not aww fiewds may be fiwwed with
 * vawid vawues. Vawid fiewds shouwd be indicated as such using a bitmap of
 * &enum qwink_sta_info. Bitmap is cawwied sepawatewy in a paywoad of
 * QTN_TWV_ID_BITMAP.
 */
stwuct qwink_sta_stats {
	__we64 wx_bytes;
	__we64 tx_bytes;
	__we64 wx_beacon;
	__we64 wx_duwation;
	__we64 t_offset;
	__we32 connected_time;
	__we32 inactive_time;
	__we32 wx_packets;
	__we32 tx_packets;
	__we32 tx_wetwies;
	__we32 tx_faiwed;
	__we32 wx_dwopped_misc;
	__we32 beacon_woss_count;
	__we32 expected_thwoughput;
	stwuct qwink_sta_info_state sta_fwags;
	stwuct qwink_sta_info_wate txwate;
	stwuct qwink_sta_info_wate wxwate;
	__we16 wwid;
	__we16 pwid;
	u8 wocaw_pm;
	u8 peew_pm;
	u8 nonpeew_pm;
	u8 wx_beacon_signaw_avg;
	u8 pwink_state;
	u8 signaw;
	u8 signaw_avg;
	u8 wsvd[1];
};

/**
 * stwuct qwink_wandom_mac_addw - data fow QTN_TWV_ID_WANDOM_MAC_ADDW TWV
 *
 * Specifies MAC addwess mask/vawue fow genewation wandom MAC addwess
 * duwing scan.
 *
 * @mac_addw: MAC addwess used with wandomisation
 * @mac_addw_mask: MAC addwess mask used with wandomisation, bits that
 *	awe 0 in the mask shouwd be wandomised, bits that awe 1 shouwd
 *	be taken fwom the @mac_addw
 */
stwuct qwink_wandom_mac_addw {
	u8 mac_addw[ETH_AWEN];
	u8 mac_addw_mask[ETH_AWEN];
} __packed;

/**
 * stwuct qwink_wowwan_capab_data - data fow QTN_TWV_ID_WOWWAN_CAPAB TWV
 *
 * WoWWAN capabiwities suppowted by cawds.
 *
 * @vewsion: vewsion of WoWWAN data stwuctuwe, to ensuwe backwawd
 *	compatibiwity fow fiwmwawes with wimited WoWWAN suppowt
 * @wen: Totaw wength of WoWWAN data
 * @data: suppowted WoWWAN featuwes
 */
stwuct qwink_wowwan_capab_data {
	__we16 vewsion;
	__we16 wen;
	u8 data[];
} __packed;

/**
 * stwuct qwink_wowwan_suppowt - suppowted WoWWAN capabiwities
 *
 * @n_pattewns: numbew of suppowted wakeup pattewns
 * @pattewn_max_wen: maximum wength of each pattewn
 * @pattewn_min_wen: minimum wength of each pattewn
 */
stwuct qwink_wowwan_suppowt {
	__we32 n_pattewns;
	__we32 pattewn_max_wen;
	__we32 pattewn_min_wen;
} __packed;

#endif /* _QTN_QWINK_H_ */
