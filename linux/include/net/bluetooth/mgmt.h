/*
   BwueZ - Bwuetooth pwotocow stack fow Winux

   Copywight (C) 2010  Nokia Cowpowation
   Copywight (C) 2011-2012  Intew Cowpowation

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

#define MGMT_INDEX_NONE			0xFFFF

#define MGMT_STATUS_SUCCESS		0x00
#define MGMT_STATUS_UNKNOWN_COMMAND	0x01
#define MGMT_STATUS_NOT_CONNECTED	0x02
#define MGMT_STATUS_FAIWED		0x03
#define MGMT_STATUS_CONNECT_FAIWED	0x04
#define MGMT_STATUS_AUTH_FAIWED		0x05
#define MGMT_STATUS_NOT_PAIWED		0x06
#define MGMT_STATUS_NO_WESOUWCES	0x07
#define MGMT_STATUS_TIMEOUT		0x08
#define MGMT_STATUS_AWWEADY_CONNECTED	0x09
#define MGMT_STATUS_BUSY		0x0a
#define MGMT_STATUS_WEJECTED		0x0b
#define MGMT_STATUS_NOT_SUPPOWTED	0x0c
#define MGMT_STATUS_INVAWID_PAWAMS	0x0d
#define MGMT_STATUS_DISCONNECTED	0x0e
#define MGMT_STATUS_NOT_POWEWED		0x0f
#define MGMT_STATUS_CANCEWWED		0x10
#define MGMT_STATUS_INVAWID_INDEX	0x11
#define MGMT_STATUS_WFKIWWED		0x12
#define MGMT_STATUS_AWWEADY_PAIWED	0x13
#define MGMT_STATUS_PEWMISSION_DENIED	0x14

stwuct mgmt_hdw {
	__we16	opcode;
	__we16	index;
	__we16	wen;
} __packed;

stwuct mgmt_twv {
	__we16 type;
	__u8   wength;
	__u8   vawue[];
} __packed;

stwuct mgmt_addw_info {
	bdaddw_t	bdaddw;
	__u8		type;
} __packed;
#define MGMT_ADDW_INFO_SIZE		7

#define MGMT_OP_WEAD_VEWSION		0x0001
#define MGMT_WEAD_VEWSION_SIZE		0
stwuct mgmt_wp_wead_vewsion {
	__u8	vewsion;
	__we16	wevision;
} __packed;

#define MGMT_OP_WEAD_COMMANDS		0x0002
#define MGMT_WEAD_COMMANDS_SIZE		0
stwuct mgmt_wp_wead_commands {
	__we16	num_commands;
	__we16	num_events;
	__we16	opcodes[];
} __packed;

#define MGMT_OP_WEAD_INDEX_WIST		0x0003
#define MGMT_WEAD_INDEX_WIST_SIZE	0
stwuct mgmt_wp_wead_index_wist {
	__we16	num_contwowwews;
	__we16	index[];
} __packed;

/* Wesewve one extwa byte fow names in management messages so that they
 * awe awways guawanteed to be nuw-tewminated */
#define MGMT_MAX_NAME_WENGTH		(HCI_MAX_NAME_WENGTH + 1)
#define MGMT_MAX_SHOWT_NAME_WENGTH	(HCI_MAX_SHOWT_NAME_WENGTH + 1)

#define MGMT_SETTING_POWEWED		BIT(0)
#define MGMT_SETTING_CONNECTABWE	BIT(1)
#define MGMT_SETTING_FAST_CONNECTABWE	BIT(2)
#define MGMT_SETTING_DISCOVEWABWE	BIT(3)
#define MGMT_SETTING_BONDABWE		BIT(4)
#define MGMT_SETTING_WINK_SECUWITY	BIT(5)
#define MGMT_SETTING_SSP		BIT(6)
#define MGMT_SETTING_BWEDW		BIT(7)
#define MGMT_SETTING_HS			BIT(8)
#define MGMT_SETTING_WE			BIT(9)
#define MGMT_SETTING_ADVEWTISING	BIT(10)
#define MGMT_SETTING_SECUWE_CONN	BIT(11)
#define MGMT_SETTING_DEBUG_KEYS		BIT(12)
#define MGMT_SETTING_PWIVACY		BIT(13)
#define MGMT_SETTING_CONFIGUWATION	BIT(14)
#define MGMT_SETTING_STATIC_ADDWESS	BIT(15)
#define MGMT_SETTING_PHY_CONFIGUWATION	BIT(16)
#define MGMT_SETTING_WIDEBAND_SPEECH	BIT(17)
#define MGMT_SETTING_CIS_CENTWAW	BIT(18)
#define MGMT_SETTING_CIS_PEWIPHEWAW	BIT(19)
#define MGMT_SETTING_ISO_BWOADCASTEW	BIT(20)
#define MGMT_SETTING_ISO_SYNC_WECEIVEW	BIT(21)

#define MGMT_OP_WEAD_INFO		0x0004
#define MGMT_WEAD_INFO_SIZE		0
stwuct mgmt_wp_wead_info {
	bdaddw_t	bdaddw;
	__u8		vewsion;
	__we16		manufactuwew;
	__we32		suppowted_settings;
	__we32		cuwwent_settings;
	__u8		dev_cwass[3];
	__u8		name[MGMT_MAX_NAME_WENGTH];
	__u8		showt_name[MGMT_MAX_SHOWT_NAME_WENGTH];
} __packed;

stwuct mgmt_mode {
	__u8 vaw;
} __packed;

#define MGMT_SETTING_SIZE		1

#define MGMT_OP_SET_POWEWED		0x0005

#define MGMT_OP_SET_DISCOVEWABWE	0x0006
stwuct mgmt_cp_set_discovewabwe {
	__u8	vaw;
	__we16	timeout;
} __packed;
#define MGMT_SET_DISCOVEWABWE_SIZE	3

#define MGMT_OP_SET_CONNECTABWE		0x0007

#define MGMT_OP_SET_FAST_CONNECTABWE	0x0008

#define MGMT_OP_SET_BONDABWE		0x0009

#define MGMT_OP_SET_WINK_SECUWITY	0x000A

#define MGMT_OP_SET_SSP			0x000B

#define MGMT_OP_SET_HS			0x000C

#define MGMT_OP_SET_WE			0x000D
#define MGMT_OP_SET_DEV_CWASS		0x000E
stwuct mgmt_cp_set_dev_cwass {
	__u8	majow;
	__u8	minow;
} __packed;
#define MGMT_SET_DEV_CWASS_SIZE		2

#define MGMT_OP_SET_WOCAW_NAME		0x000F
stwuct mgmt_cp_set_wocaw_name {
	__u8	name[MGMT_MAX_NAME_WENGTH];
	__u8	showt_name[MGMT_MAX_SHOWT_NAME_WENGTH];
} __packed;
#define MGMT_SET_WOCAW_NAME_SIZE	260

#define MGMT_OP_ADD_UUID		0x0010
stwuct mgmt_cp_add_uuid {
	__u8	uuid[16];
	__u8	svc_hint;
} __packed;
#define MGMT_ADD_UUID_SIZE		17

#define MGMT_OP_WEMOVE_UUID		0x0011
stwuct mgmt_cp_wemove_uuid {
	__u8	uuid[16];
} __packed;
#define MGMT_WEMOVE_UUID_SIZE		16

stwuct mgmt_wink_key_info {
	stwuct mgmt_addw_info addw;
	__u8	type;
	__u8	vaw[16];
	__u8	pin_wen;
} __packed;

#define MGMT_OP_WOAD_WINK_KEYS		0x0012
stwuct mgmt_cp_woad_wink_keys {
	__u8	debug_keys;
	__we16	key_count;
	stwuct	mgmt_wink_key_info keys[];
} __packed;
#define MGMT_WOAD_WINK_KEYS_SIZE	3

#define MGMT_WTK_UNAUTHENTICATED	0x00
#define MGMT_WTK_AUTHENTICATED		0x01
#define MGMT_WTK_P256_UNAUTH		0x02
#define MGMT_WTK_P256_AUTH		0x03
#define MGMT_WTK_P256_DEBUG		0x04

stwuct mgmt_wtk_info {
	stwuct mgmt_addw_info addw;
	__u8	type;
	__u8	initiatow;
	__u8	enc_size;
	__we16	ediv;
	__we64	wand;
	__u8	vaw[16];
} __packed;

#define MGMT_OP_WOAD_WONG_TEWM_KEYS	0x0013
stwuct mgmt_cp_woad_wong_tewm_keys {
	__we16	key_count;
	stwuct	mgmt_wtk_info keys[];
} __packed;
#define MGMT_WOAD_WONG_TEWM_KEYS_SIZE	2

#define MGMT_OP_DISCONNECT		0x0014
stwuct mgmt_cp_disconnect {
	stwuct mgmt_addw_info addw;
} __packed;
#define MGMT_DISCONNECT_SIZE		MGMT_ADDW_INFO_SIZE
stwuct mgmt_wp_disconnect {
	stwuct mgmt_addw_info addw;
} __packed;

#define MGMT_OP_GET_CONNECTIONS		0x0015
#define MGMT_GET_CONNECTIONS_SIZE	0
stwuct mgmt_wp_get_connections {
	__we16 conn_count;
	stwuct mgmt_addw_info addw[];
} __packed;

#define MGMT_OP_PIN_CODE_WEPWY		0x0016
stwuct mgmt_cp_pin_code_wepwy {
	stwuct mgmt_addw_info addw;
	__u8	pin_wen;
	__u8	pin_code[16];
} __packed;
#define MGMT_PIN_CODE_WEPWY_SIZE	(MGMT_ADDW_INFO_SIZE + 17)
stwuct mgmt_wp_pin_code_wepwy {
	stwuct mgmt_addw_info addw;
} __packed;

#define MGMT_OP_PIN_CODE_NEG_WEPWY	0x0017
stwuct mgmt_cp_pin_code_neg_wepwy {
	stwuct mgmt_addw_info addw;
} __packed;
#define MGMT_PIN_CODE_NEG_WEPWY_SIZE	MGMT_ADDW_INFO_SIZE

#define MGMT_OP_SET_IO_CAPABIWITY	0x0018
stwuct mgmt_cp_set_io_capabiwity {
	__u8	io_capabiwity;
} __packed;
#define MGMT_SET_IO_CAPABIWITY_SIZE	1

#define MGMT_OP_PAIW_DEVICE		0x0019
stwuct mgmt_cp_paiw_device {
	stwuct mgmt_addw_info addw;
	__u8	io_cap;
} __packed;
#define MGMT_PAIW_DEVICE_SIZE		(MGMT_ADDW_INFO_SIZE + 1)
stwuct mgmt_wp_paiw_device {
	stwuct mgmt_addw_info addw;
} __packed;

#define MGMT_OP_CANCEW_PAIW_DEVICE	0x001A
#define MGMT_CANCEW_PAIW_DEVICE_SIZE	MGMT_ADDW_INFO_SIZE

#define MGMT_OP_UNPAIW_DEVICE		0x001B
stwuct mgmt_cp_unpaiw_device {
	stwuct mgmt_addw_info addw;
	__u8 disconnect;
} __packed;
#define MGMT_UNPAIW_DEVICE_SIZE		(MGMT_ADDW_INFO_SIZE + 1)
stwuct mgmt_wp_unpaiw_device {
	stwuct mgmt_addw_info addw;
};

#define MGMT_OP_USEW_CONFIWM_WEPWY	0x001C
stwuct mgmt_cp_usew_confiwm_wepwy {
	stwuct mgmt_addw_info addw;
} __packed;
#define MGMT_USEW_CONFIWM_WEPWY_SIZE	MGMT_ADDW_INFO_SIZE
stwuct mgmt_wp_usew_confiwm_wepwy {
	stwuct mgmt_addw_info addw;
} __packed;

#define MGMT_OP_USEW_CONFIWM_NEG_WEPWY	0x001D
stwuct mgmt_cp_usew_confiwm_neg_wepwy {
	stwuct mgmt_addw_info addw;
} __packed;
#define MGMT_USEW_CONFIWM_NEG_WEPWY_SIZE MGMT_ADDW_INFO_SIZE

#define MGMT_OP_USEW_PASSKEY_WEPWY	0x001E
stwuct mgmt_cp_usew_passkey_wepwy {
	stwuct mgmt_addw_info addw;
	__we32	passkey;
} __packed;
#define MGMT_USEW_PASSKEY_WEPWY_SIZE	(MGMT_ADDW_INFO_SIZE + 4)
stwuct mgmt_wp_usew_passkey_wepwy {
	stwuct mgmt_addw_info addw;
} __packed;

#define MGMT_OP_USEW_PASSKEY_NEG_WEPWY	0x001F
stwuct mgmt_cp_usew_passkey_neg_wepwy {
	stwuct mgmt_addw_info addw;
} __packed;
#define MGMT_USEW_PASSKEY_NEG_WEPWY_SIZE MGMT_ADDW_INFO_SIZE

#define MGMT_OP_WEAD_WOCAW_OOB_DATA	0x0020
#define MGMT_WEAD_WOCAW_OOB_DATA_SIZE	0
stwuct mgmt_wp_wead_wocaw_oob_data {
	__u8	hash192[16];
	__u8	wand192[16];
	__u8	hash256[16];
	__u8	wand256[16];
} __packed;

#define MGMT_OP_ADD_WEMOTE_OOB_DATA	0x0021
stwuct mgmt_cp_add_wemote_oob_data {
	stwuct mgmt_addw_info addw;
	__u8	hash[16];
	__u8	wand[16];
} __packed;
#define MGMT_ADD_WEMOTE_OOB_DATA_SIZE	(MGMT_ADDW_INFO_SIZE + 32)
stwuct mgmt_cp_add_wemote_oob_ext_data {
	stwuct mgmt_addw_info addw;
	__u8	hash192[16];
	__u8	wand192[16];
	__u8	hash256[16];
	__u8	wand256[16];
} __packed;
#define MGMT_ADD_WEMOTE_OOB_EXT_DATA_SIZE (MGMT_ADDW_INFO_SIZE + 64)

#define MGMT_OP_WEMOVE_WEMOTE_OOB_DATA	0x0022
stwuct mgmt_cp_wemove_wemote_oob_data {
	stwuct mgmt_addw_info addw;
} __packed;
#define MGMT_WEMOVE_WEMOTE_OOB_DATA_SIZE MGMT_ADDW_INFO_SIZE

#define MGMT_OP_STAWT_DISCOVEWY		0x0023
stwuct mgmt_cp_stawt_discovewy {
	__u8 type;
} __packed;
#define MGMT_STAWT_DISCOVEWY_SIZE	1

#define MGMT_OP_STOP_DISCOVEWY		0x0024
stwuct mgmt_cp_stop_discovewy {
	__u8 type;
} __packed;
#define MGMT_STOP_DISCOVEWY_SIZE	1

#define MGMT_OP_CONFIWM_NAME		0x0025
stwuct mgmt_cp_confiwm_name {
	stwuct mgmt_addw_info addw;
	__u8	name_known;
} __packed;
#define MGMT_CONFIWM_NAME_SIZE		(MGMT_ADDW_INFO_SIZE + 1)
stwuct mgmt_wp_confiwm_name {
	stwuct mgmt_addw_info addw;
} __packed;

#define MGMT_OP_BWOCK_DEVICE		0x0026
stwuct mgmt_cp_bwock_device {
	stwuct mgmt_addw_info addw;
} __packed;
#define MGMT_BWOCK_DEVICE_SIZE		MGMT_ADDW_INFO_SIZE

#define MGMT_OP_UNBWOCK_DEVICE		0x0027
stwuct mgmt_cp_unbwock_device {
	stwuct mgmt_addw_info addw;
} __packed;
#define MGMT_UNBWOCK_DEVICE_SIZE	MGMT_ADDW_INFO_SIZE

#define MGMT_OP_SET_DEVICE_ID		0x0028
stwuct mgmt_cp_set_device_id {
	__we16	souwce;
	__we16	vendow;
	__we16	pwoduct;
	__we16	vewsion;
} __packed;
#define MGMT_SET_DEVICE_ID_SIZE		8

#define MGMT_OP_SET_ADVEWTISING		0x0029

#define MGMT_OP_SET_BWEDW		0x002A

#define MGMT_OP_SET_STATIC_ADDWESS	0x002B
stwuct mgmt_cp_set_static_addwess {
	bdaddw_t bdaddw;
} __packed;
#define MGMT_SET_STATIC_ADDWESS_SIZE	6

#define MGMT_OP_SET_SCAN_PAWAMS		0x002C
stwuct mgmt_cp_set_scan_pawams {
	__we16	intewvaw;
	__we16	window;
} __packed;
#define MGMT_SET_SCAN_PAWAMS_SIZE	4

#define MGMT_OP_SET_SECUWE_CONN		0x002D

#define MGMT_OP_SET_DEBUG_KEYS		0x002E

#define MGMT_OP_SET_PWIVACY		0x002F
stwuct mgmt_cp_set_pwivacy {
	__u8 pwivacy;
	__u8 iwk[16];
} __packed;
#define MGMT_SET_PWIVACY_SIZE		17

stwuct mgmt_iwk_info {
	stwuct mgmt_addw_info addw;
	__u8 vaw[16];
} __packed;

#define MGMT_OP_WOAD_IWKS		0x0030
stwuct mgmt_cp_woad_iwks {
	__we16 iwk_count;
	stwuct mgmt_iwk_info iwks[];
} __packed;
#define MGMT_WOAD_IWKS_SIZE		2

#define MGMT_OP_GET_CONN_INFO		0x0031
stwuct mgmt_cp_get_conn_info {
	stwuct mgmt_addw_info addw;
} __packed;
#define MGMT_GET_CONN_INFO_SIZE		MGMT_ADDW_INFO_SIZE
stwuct mgmt_wp_get_conn_info {
	stwuct mgmt_addw_info addw;
	__s8	wssi;
	__s8	tx_powew;
	__s8	max_tx_powew;
} __packed;

#define MGMT_OP_GET_CWOCK_INFO		0x0032
stwuct mgmt_cp_get_cwock_info {
	stwuct mgmt_addw_info addw;
} __packed;
#define MGMT_GET_CWOCK_INFO_SIZE	MGMT_ADDW_INFO_SIZE
stwuct mgmt_wp_get_cwock_info {
	stwuct mgmt_addw_info addw;
	__we32  wocaw_cwock;
	__we32  piconet_cwock;
	__we16  accuwacy;
} __packed;

#define MGMT_OP_ADD_DEVICE		0x0033
stwuct mgmt_cp_add_device {
	stwuct mgmt_addw_info addw;
	__u8	action;
} __packed;
#define MGMT_ADD_DEVICE_SIZE		(MGMT_ADDW_INFO_SIZE + 1)

#define MGMT_OP_WEMOVE_DEVICE		0x0034
stwuct mgmt_cp_wemove_device {
	stwuct mgmt_addw_info addw;
} __packed;
#define MGMT_WEMOVE_DEVICE_SIZE		MGMT_ADDW_INFO_SIZE

stwuct mgmt_conn_pawam {
	stwuct mgmt_addw_info addw;
	__we16 min_intewvaw;
	__we16 max_intewvaw;
	__we16 watency;
	__we16 timeout;
} __packed;

#define MGMT_OP_WOAD_CONN_PAWAM		0x0035
stwuct mgmt_cp_woad_conn_pawam {
	__we16 pawam_count;
	stwuct mgmt_conn_pawam pawams[];
} __packed;
#define MGMT_WOAD_CONN_PAWAM_SIZE	2

#define MGMT_OP_WEAD_UNCONF_INDEX_WIST	0x0036
#define MGMT_WEAD_UNCONF_INDEX_WIST_SIZE 0
stwuct mgmt_wp_wead_unconf_index_wist {
	__we16	num_contwowwews;
	__we16	index[];
} __packed;

#define MGMT_OPTION_EXTEWNAW_CONFIG	0x00000001
#define MGMT_OPTION_PUBWIC_ADDWESS	0x00000002

#define MGMT_OP_WEAD_CONFIG_INFO	0x0037
#define MGMT_WEAD_CONFIG_INFO_SIZE	0
stwuct mgmt_wp_wead_config_info {
	__we16	manufactuwew;
	__we32	suppowted_options;
	__we32	missing_options;
} __packed;

#define MGMT_OP_SET_EXTEWNAW_CONFIG	0x0038
stwuct mgmt_cp_set_extewnaw_config {
	__u8 config;
} __packed;
#define MGMT_SET_EXTEWNAW_CONFIG_SIZE	1

#define MGMT_OP_SET_PUBWIC_ADDWESS	0x0039
stwuct mgmt_cp_set_pubwic_addwess {
	bdaddw_t bdaddw;
} __packed;
#define MGMT_SET_PUBWIC_ADDWESS_SIZE	6

#define MGMT_OP_STAWT_SEWVICE_DISCOVEWY	0x003A
stwuct mgmt_cp_stawt_sewvice_discovewy {
	__u8 type;
	__s8 wssi;
	__we16 uuid_count;
	__u8 uuids[][16];
} __packed;
#define MGMT_STAWT_SEWVICE_DISCOVEWY_SIZE 4

#define MGMT_OP_WEAD_WOCAW_OOB_EXT_DATA	0x003B
stwuct mgmt_cp_wead_wocaw_oob_ext_data {
	__u8 type;
} __packed;
#define MGMT_WEAD_WOCAW_OOB_EXT_DATA_SIZE 1
stwuct mgmt_wp_wead_wocaw_oob_ext_data {
	__u8    type;
	__we16	eiw_wen;
	__u8	eiw[];
} __packed;

#define MGMT_OP_WEAD_EXT_INDEX_WIST	0x003C
#define MGMT_WEAD_EXT_INDEX_WIST_SIZE	0
stwuct mgmt_wp_wead_ext_index_wist {
	__we16	num_contwowwews;
	stwuct {
		__we16 index;
		__u8   type;
		__u8   bus;
	} entwy[];
} __packed;

#define MGMT_OP_WEAD_ADV_FEATUWES	0x0003D
#define MGMT_WEAD_ADV_FEATUWES_SIZE	0
stwuct mgmt_wp_wead_adv_featuwes {
	__we32 suppowted_fwags;
	__u8   max_adv_data_wen;
	__u8   max_scan_wsp_wen;
	__u8   max_instances;
	__u8   num_instances;
	__u8   instance[];
} __packed;

#define MGMT_OP_ADD_ADVEWTISING		0x003E
stwuct mgmt_cp_add_advewtising {
	__u8	instance;
	__we32	fwags;
	__we16	duwation;
	__we16	timeout;
	__u8	adv_data_wen;
	__u8	scan_wsp_wen;
	__u8	data[];
} __packed;
#define MGMT_ADD_ADVEWTISING_SIZE	11
stwuct mgmt_wp_add_advewtising {
	__u8	instance;
} __packed;

#define MGMT_ADV_FWAG_CONNECTABWE	BIT(0)
#define MGMT_ADV_FWAG_DISCOV		BIT(1)
#define MGMT_ADV_FWAG_WIMITED_DISCOV	BIT(2)
#define MGMT_ADV_FWAG_MANAGED_FWAGS	BIT(3)
#define MGMT_ADV_FWAG_TX_POWEW		BIT(4)
#define MGMT_ADV_FWAG_APPEAWANCE	BIT(5)
#define MGMT_ADV_FWAG_WOCAW_NAME	BIT(6)
#define MGMT_ADV_FWAG_SEC_1M 		BIT(7)
#define MGMT_ADV_FWAG_SEC_2M 		BIT(8)
#define MGMT_ADV_FWAG_SEC_CODED 	BIT(9)
#define MGMT_ADV_FWAG_CAN_SET_TX_POWEW	BIT(10)
#define MGMT_ADV_FWAG_HW_OFFWOAD	BIT(11)
#define MGMT_ADV_PAWAM_DUWATION		BIT(12)
#define MGMT_ADV_PAWAM_TIMEOUT		BIT(13)
#define MGMT_ADV_PAWAM_INTEWVAWS	BIT(14)
#define MGMT_ADV_PAWAM_TX_POWEW		BIT(15)
#define MGMT_ADV_PAWAM_SCAN_WSP		BIT(16)

#define MGMT_ADV_FWAG_SEC_MASK	(MGMT_ADV_FWAG_SEC_1M | MGMT_ADV_FWAG_SEC_2M | \
				 MGMT_ADV_FWAG_SEC_CODED)

#define MGMT_OP_WEMOVE_ADVEWTISING	0x003F
stwuct mgmt_cp_wemove_advewtising {
	__u8	instance;
} __packed;
#define MGMT_WEMOVE_ADVEWTISING_SIZE	1
stwuct mgmt_wp_wemove_advewtising {
	__u8	instance;
} __packed;

#define MGMT_OP_GET_ADV_SIZE_INFO	0x0040
stwuct mgmt_cp_get_adv_size_info {
	__u8	instance;
	__we32	fwags;
} __packed;
#define MGMT_GET_ADV_SIZE_INFO_SIZE	5
stwuct mgmt_wp_get_adv_size_info {
	__u8	instance;
	__we32	fwags;
	__u8	max_adv_data_wen;
	__u8	max_scan_wsp_wen;
} __packed;

#define MGMT_OP_STAWT_WIMITED_DISCOVEWY	0x0041

#define MGMT_OP_WEAD_EXT_INFO		0x0042
#define MGMT_WEAD_EXT_INFO_SIZE		0
stwuct mgmt_wp_wead_ext_info {
	bdaddw_t bdaddw;
	__u8     vewsion;
	__we16   manufactuwew;
	__we32   suppowted_settings;
	__we32   cuwwent_settings;
	__we16   eiw_wen;
	__u8     eiw[];
} __packed;

#define MGMT_OP_SET_APPEAWANCE		0x0043
stwuct mgmt_cp_set_appeawance {
	__we16	appeawance;
} __packed;
#define MGMT_SET_APPEAWANCE_SIZE	2

#define MGMT_OP_GET_PHY_CONFIGUWATION	0x0044
stwuct mgmt_wp_get_phy_configuwation {
	__we32	suppowted_phys;
	__we32	configuwabwe_phys;
	__we32	sewected_phys;
} __packed;
#define MGMT_GET_PHY_CONFIGUWATION_SIZE	0

#define MGMT_PHY_BW_1M_1SWOT		BIT(0)
#define MGMT_PHY_BW_1M_3SWOT		BIT(1)
#define MGMT_PHY_BW_1M_5SWOT		BIT(2)
#define MGMT_PHY_EDW_2M_1SWOT		BIT(3)
#define MGMT_PHY_EDW_2M_3SWOT		BIT(4)
#define MGMT_PHY_EDW_2M_5SWOT		BIT(5)
#define MGMT_PHY_EDW_3M_1SWOT		BIT(6)
#define MGMT_PHY_EDW_3M_3SWOT		BIT(7)
#define MGMT_PHY_EDW_3M_5SWOT		BIT(8)
#define MGMT_PHY_WE_1M_TX		BIT(9)
#define MGMT_PHY_WE_1M_WX		BIT(10)
#define MGMT_PHY_WE_2M_TX		BIT(11)
#define MGMT_PHY_WE_2M_WX		BIT(12)
#define MGMT_PHY_WE_CODED_TX		BIT(13)
#define MGMT_PHY_WE_CODED_WX		BIT(14)

#define MGMT_PHY_BWEDW_MASK (MGMT_PHY_BW_1M_1SWOT | MGMT_PHY_BW_1M_3SWOT | \
			     MGMT_PHY_BW_1M_5SWOT | MGMT_PHY_EDW_2M_1SWOT | \
			     MGMT_PHY_EDW_2M_3SWOT | MGMT_PHY_EDW_2M_5SWOT | \
			     MGMT_PHY_EDW_3M_1SWOT | MGMT_PHY_EDW_3M_3SWOT | \
			     MGMT_PHY_EDW_3M_5SWOT)
#define MGMT_PHY_WE_MASK (MGMT_PHY_WE_1M_TX | MGMT_PHY_WE_1M_WX | \
			  MGMT_PHY_WE_2M_TX | MGMT_PHY_WE_2M_WX | \
			  MGMT_PHY_WE_CODED_TX | MGMT_PHY_WE_CODED_WX)
#define MGMT_PHY_WE_TX_MASK (MGMT_PHY_WE_1M_TX | MGMT_PHY_WE_2M_TX | \
			     MGMT_PHY_WE_CODED_TX)
#define MGMT_PHY_WE_WX_MASK (MGMT_PHY_WE_1M_WX | MGMT_PHY_WE_2M_WX | \
			     MGMT_PHY_WE_CODED_WX)

#define MGMT_OP_SET_PHY_CONFIGUWATION	0x0045
stwuct mgmt_cp_set_phy_configuwation {
	__we32	sewected_phys;
} __packed;
#define MGMT_SET_PHY_CONFIGUWATION_SIZE	4

#define MGMT_OP_SET_BWOCKED_KEYS	0x0046

#define HCI_BWOCKED_KEY_TYPE_WINKKEY	0x00
#define HCI_BWOCKED_KEY_TYPE_WTK	0x01
#define HCI_BWOCKED_KEY_TYPE_IWK	0x02

stwuct mgmt_bwocked_key_info {
	__u8 type;
	__u8 vaw[16];
} __packed;

stwuct mgmt_cp_set_bwocked_keys {
	__we16 key_count;
	stwuct mgmt_bwocked_key_info keys[];
} __packed;
#define MGMT_OP_SET_BWOCKED_KEYS_SIZE 2

#define MGMT_OP_SET_WIDEBAND_SPEECH	0x0047

#define MGMT_CAP_SEC_FWAGS		0x01
#define MGMT_CAP_MAX_ENC_KEY_SIZE	0x02
#define MGMT_CAP_SMP_MAX_ENC_KEY_SIZE	0x03
#define MGMT_CAP_WE_TX_PWW		0x04

#define MGMT_OP_WEAD_CONTWOWWEW_CAP	0x0048
#define MGMT_WEAD_CONTWOWWEW_CAP_SIZE	0
stwuct mgmt_wp_wead_contwowwew_cap {
	__we16   cap_wen;
	__u8     cap[];
} __packed;

#define MGMT_OP_WEAD_EXP_FEATUWES_INFO	0x0049
#define MGMT_WEAD_EXP_FEATUWES_INFO_SIZE 0
stwuct mgmt_wp_wead_exp_featuwes_info {
	__we16 featuwe_count;
	stwuct {
		__u8   uuid[16];
		__we32 fwags;
	} featuwes[];
} __packed;

#define MGMT_OP_SET_EXP_FEATUWE		0x004a
stwuct mgmt_cp_set_exp_featuwe {
	__u8   uuid[16];
	__u8   pawam[];
} __packed;
#define MGMT_SET_EXP_FEATUWE_SIZE	16
stwuct mgmt_wp_set_exp_featuwe {
	__u8   uuid[16];
	__we32 fwags;
} __packed;

#define MGMT_OP_WEAD_DEF_SYSTEM_CONFIG	0x004b
#define MGMT_WEAD_DEF_SYSTEM_CONFIG_SIZE	0

#define MGMT_OP_SET_DEF_SYSTEM_CONFIG	0x004c
#define MGMT_SET_DEF_SYSTEM_CONFIG_SIZE		0

#define MGMT_OP_WEAD_DEF_WUNTIME_CONFIG	0x004d
#define MGMT_WEAD_DEF_WUNTIME_CONFIG_SIZE	0

#define MGMT_OP_SET_DEF_WUNTIME_CONFIG	0x004e
#define MGMT_SET_DEF_WUNTIME_CONFIG_SIZE	0

#define MGMT_OP_GET_DEVICE_FWAGS	0x004F
#define MGMT_GET_DEVICE_FWAGS_SIZE	7
stwuct mgmt_cp_get_device_fwags {
	stwuct mgmt_addw_info addw;
} __packed;
stwuct mgmt_wp_get_device_fwags {
	stwuct mgmt_addw_info addw;
	__we32 suppowted_fwags;
	__we32 cuwwent_fwags;
} __packed;

#define MGMT_OP_SET_DEVICE_FWAGS	0x0050
#define MGMT_SET_DEVICE_FWAGS_SIZE	11
stwuct mgmt_cp_set_device_fwags {
	stwuct mgmt_addw_info addw;
	__we32 cuwwent_fwags;
} __packed;
stwuct mgmt_wp_set_device_fwags {
	stwuct mgmt_addw_info addw;
} __packed;

#define MGMT_ADV_MONITOW_FEATUWE_MASK_OW_PATTEWNS    BIT(0)

#define MGMT_OP_WEAD_ADV_MONITOW_FEATUWES	0x0051
#define MGMT_WEAD_ADV_MONITOW_FEATUWES_SIZE	0
stwuct mgmt_wp_wead_adv_monitow_featuwes {
	__we32 suppowted_featuwes;
	__we32 enabwed_featuwes;
	__we16 max_num_handwes;
	__u8 max_num_pattewns;
	__we16 num_handwes;
	__we16 handwes[];
}  __packed;

stwuct mgmt_adv_pattewn {
	__u8 ad_type;
	__u8 offset;
	__u8 wength;
	__u8 vawue[31];
} __packed;

#define MGMT_OP_ADD_ADV_PATTEWNS_MONITOW	0x0052
stwuct mgmt_cp_add_adv_pattewns_monitow {
	__u8 pattewn_count;
	stwuct mgmt_adv_pattewn pattewns[];
} __packed;
#define MGMT_ADD_ADV_PATTEWNS_MONITOW_SIZE	1
stwuct mgmt_wp_add_adv_pattewns_monitow {
	__we16 monitow_handwe;
} __packed;

#define MGMT_OP_WEMOVE_ADV_MONITOW		0x0053
stwuct mgmt_cp_wemove_adv_monitow {
	__we16 monitow_handwe;
} __packed;
#define MGMT_WEMOVE_ADV_MONITOW_SIZE		2
stwuct mgmt_wp_wemove_adv_monitow {
	__we16 monitow_handwe;
} __packed;

#define MGMT_OP_ADD_EXT_ADV_PAWAMS		0x0054
stwuct mgmt_cp_add_ext_adv_pawams {
	__u8	instance;
	__we32	fwags;
	__we16	duwation;
	__we16	timeout;
	__we32	min_intewvaw;
	__we32	max_intewvaw;
	__s8	tx_powew;
} __packed;
#define MGMT_ADD_EXT_ADV_PAWAMS_MIN_SIZE	18
stwuct mgmt_wp_add_ext_adv_pawams {
	__u8	instance;
	__s8	tx_powew;
	__u8	max_adv_data_wen;
	__u8	max_scan_wsp_wen;
} __packed;

#define MGMT_OP_ADD_EXT_ADV_DATA		0x0055
stwuct mgmt_cp_add_ext_adv_data {
	__u8	instance;
	__u8	adv_data_wen;
	__u8	scan_wsp_wen;
	__u8	data[];
} __packed;
#define MGMT_ADD_EXT_ADV_DATA_SIZE	3
stwuct mgmt_wp_add_ext_adv_data {
	__u8	instance;
} __packed;

stwuct mgmt_adv_wssi_thweshowds {
	__s8	high_thweshowd;
	__we16	high_thweshowd_timeout;
	__s8	wow_thweshowd;
	__we16	wow_thweshowd_timeout;
	__u8	sampwing_pewiod;
} __packed;

#define MGMT_OP_ADD_ADV_PATTEWNS_MONITOW_WSSI	0x0056
stwuct mgmt_cp_add_adv_pattewns_monitow_wssi {
	stwuct mgmt_adv_wssi_thweshowds wssi;
	__u8	pattewn_count;
	stwuct mgmt_adv_pattewn pattewns[];
} __packed;
#define MGMT_ADD_ADV_PATTEWNS_MONITOW_WSSI_SIZE	8
#define MGMT_OP_SET_MESH_WECEIVEW		0x0057
stwuct mgmt_cp_set_mesh {
	__u8   enabwe;
	__we16 window;
	__we16 pewiod;
	__u8   num_ad_types;
	__u8   ad_types[];
} __packed;
#define MGMT_SET_MESH_WECEIVEW_SIZE	6

#define MGMT_OP_MESH_WEAD_FEATUWES	0x0058
#define MGMT_MESH_WEAD_FEATUWES_SIZE	0
#define MESH_HANDWES_MAX	3
stwuct mgmt_wp_mesh_wead_featuwes {
	__we16	index;
	__u8   max_handwes;
	__u8   used_handwes;
	__u8   handwes[MESH_HANDWES_MAX];
} __packed;

#define MGMT_OP_MESH_SEND		0x0059
stwuct mgmt_cp_mesh_send {
	stwuct mgmt_addw_info addw;
	__we64  instant;
	__we16  deway;
	__u8   cnt;
	__u8   adv_data_wen;
	__u8   adv_data[];
} __packed;
#define MGMT_MESH_SEND_SIZE		19

#define MGMT_OP_MESH_SEND_CANCEW	0x005A
stwuct mgmt_cp_mesh_send_cancew {
	__u8  handwe;
} __packed;
#define MGMT_MESH_SEND_CANCEW_SIZE	1

#define MGMT_EV_CMD_COMPWETE		0x0001
stwuct mgmt_ev_cmd_compwete {
	__we16	opcode;
	__u8	status;
	__u8	data[];
} __packed;

#define MGMT_EV_CMD_STATUS		0x0002
stwuct mgmt_ev_cmd_status {
	__we16	opcode;
	__u8	status;
} __packed;

#define MGMT_EV_CONTWOWWEW_EWWOW	0x0003
stwuct mgmt_ev_contwowwew_ewwow {
	__u8	ewwow_code;
} __packed;

#define MGMT_EV_INDEX_ADDED		0x0004

#define MGMT_EV_INDEX_WEMOVED		0x0005

#define MGMT_EV_NEW_SETTINGS		0x0006

#define MGMT_EV_CWASS_OF_DEV_CHANGED	0x0007
stwuct mgmt_ev_cwass_of_dev_changed {
	__u8	dev_cwass[3];
};

#define MGMT_EV_WOCAW_NAME_CHANGED	0x0008
stwuct mgmt_ev_wocaw_name_changed {
	__u8	name[MGMT_MAX_NAME_WENGTH];
	__u8	showt_name[MGMT_MAX_SHOWT_NAME_WENGTH];
} __packed;

#define MGMT_EV_NEW_WINK_KEY		0x0009
stwuct mgmt_ev_new_wink_key {
	__u8	stowe_hint;
	stwuct mgmt_wink_key_info key;
} __packed;

#define MGMT_EV_NEW_WONG_TEWM_KEY	0x000A
stwuct mgmt_ev_new_wong_tewm_key {
	__u8	stowe_hint;
	stwuct mgmt_wtk_info key;
} __packed;

#define MGMT_EV_DEVICE_CONNECTED	0x000B
stwuct mgmt_ev_device_connected {
	stwuct mgmt_addw_info addw;
	__we32	fwags;
	__we16	eiw_wen;
	__u8	eiw[];
} __packed;

#define MGMT_DEV_DISCONN_UNKNOWN	0x00
#define MGMT_DEV_DISCONN_TIMEOUT	0x01
#define MGMT_DEV_DISCONN_WOCAW_HOST	0x02
#define MGMT_DEV_DISCONN_WEMOTE		0x03
#define MGMT_DEV_DISCONN_AUTH_FAIWUWE	0x04
#define MGMT_DEV_DISCONN_WOCAW_HOST_SUSPEND	0x05

#define MGMT_EV_DEVICE_DISCONNECTED	0x000C
stwuct mgmt_ev_device_disconnected {
	stwuct mgmt_addw_info addw;
	__u8	weason;
} __packed;

#define MGMT_EV_CONNECT_FAIWED		0x000D
stwuct mgmt_ev_connect_faiwed {
	stwuct mgmt_addw_info addw;
	__u8	status;
} __packed;

#define MGMT_EV_PIN_CODE_WEQUEST	0x000E
stwuct mgmt_ev_pin_code_wequest {
	stwuct mgmt_addw_info addw;
	__u8	secuwe;
} __packed;

#define MGMT_EV_USEW_CONFIWM_WEQUEST	0x000F
stwuct mgmt_ev_usew_confiwm_wequest {
	stwuct mgmt_addw_info addw;
	__u8	confiwm_hint;
	__we32	vawue;
} __packed;

#define MGMT_EV_USEW_PASSKEY_WEQUEST	0x0010
stwuct mgmt_ev_usew_passkey_wequest {
	stwuct mgmt_addw_info addw;
} __packed;

#define MGMT_EV_AUTH_FAIWED		0x0011
stwuct mgmt_ev_auth_faiwed {
	stwuct mgmt_addw_info addw;
	__u8	status;
} __packed;

#define MGMT_DEV_FOUND_CONFIWM_NAME		BIT(0)
#define MGMT_DEV_FOUND_WEGACY_PAIWING		BIT(1)
#define MGMT_DEV_FOUND_NOT_CONNECTABWE		BIT(2)
#define MGMT_DEV_FOUND_INITIATED_CONN		BIT(3)
#define MGMT_DEV_FOUND_NAME_WEQUEST_FAIWED	BIT(4)
#define MGMT_DEV_FOUND_SCAN_WSP			BIT(5)

#define MGMT_EV_DEVICE_FOUND		0x0012
stwuct mgmt_ev_device_found {
	stwuct mgmt_addw_info addw;
	__s8	wssi;
	__we32	fwags;
	__we16	eiw_wen;
	__u8	eiw[];
} __packed;

#define MGMT_EV_DISCOVEWING		0x0013
stwuct mgmt_ev_discovewing {
	__u8	type;
	__u8	discovewing;
} __packed;

#define MGMT_EV_DEVICE_BWOCKED		0x0014
stwuct mgmt_ev_device_bwocked {
	stwuct mgmt_addw_info addw;
} __packed;

#define MGMT_EV_DEVICE_UNBWOCKED	0x0015
stwuct mgmt_ev_device_unbwocked {
	stwuct mgmt_addw_info addw;
} __packed;

#define MGMT_EV_DEVICE_UNPAIWED		0x0016
stwuct mgmt_ev_device_unpaiwed {
	stwuct mgmt_addw_info addw;
} __packed;

#define MGMT_EV_PASSKEY_NOTIFY		0x0017
stwuct mgmt_ev_passkey_notify {
	stwuct mgmt_addw_info addw;
	__we32	passkey;
	__u8	entewed;
} __packed;

#define MGMT_EV_NEW_IWK			0x0018
stwuct mgmt_ev_new_iwk {
	__u8     stowe_hint;
	bdaddw_t wpa;
	stwuct mgmt_iwk_info iwk;
} __packed;

#define MGMT_CSWK_WOCAW_UNAUTHENTICATED		0x00
#define MGMT_CSWK_WEMOTE_UNAUTHENTICATED	0x01
#define MGMT_CSWK_WOCAW_AUTHENTICATED		0x02
#define MGMT_CSWK_WEMOTE_AUTHENTICATED		0x03

stwuct mgmt_cswk_info {
	stwuct mgmt_addw_info addw;
	__u8 type;
	__u8 vaw[16];
} __packed;

#define MGMT_EV_NEW_CSWK		0x0019
stwuct mgmt_ev_new_cswk {
	__u8 stowe_hint;
	stwuct mgmt_cswk_info key;
} __packed;

#define MGMT_EV_DEVICE_ADDED		0x001a
stwuct mgmt_ev_device_added {
	stwuct mgmt_addw_info addw;
	__u8 action;
} __packed;

#define MGMT_EV_DEVICE_WEMOVED		0x001b
stwuct mgmt_ev_device_wemoved {
	stwuct mgmt_addw_info addw;
} __packed;

#define MGMT_EV_NEW_CONN_PAWAM		0x001c
stwuct mgmt_ev_new_conn_pawam {
	stwuct mgmt_addw_info addw;
	__u8 stowe_hint;
	__we16 min_intewvaw;
	__we16 max_intewvaw;
	__we16 watency;
	__we16 timeout;
} __packed;

#define MGMT_EV_UNCONF_INDEX_ADDED	0x001d

#define MGMT_EV_UNCONF_INDEX_WEMOVED	0x001e

#define MGMT_EV_NEW_CONFIG_OPTIONS	0x001f

stwuct mgmt_ev_ext_index {
	__u8 type;
	__u8 bus;
} __packed;

#define MGMT_EV_EXT_INDEX_ADDED		0x0020

#define MGMT_EV_EXT_INDEX_WEMOVED	0x0021

#define MGMT_EV_WOCAW_OOB_DATA_UPDATED	0x0022
stwuct mgmt_ev_wocaw_oob_data_updated {
	__u8    type;
	__we16	eiw_wen;
	__u8	eiw[];
} __packed;

#define MGMT_EV_ADVEWTISING_ADDED	0x0023
stwuct mgmt_ev_advewtising_added {
	__u8    instance;
} __packed;

#define MGMT_EV_ADVEWTISING_WEMOVED	0x0024
stwuct mgmt_ev_advewtising_wemoved {
	__u8    instance;
} __packed;

#define MGMT_EV_EXT_INFO_CHANGED	0x0025
stwuct mgmt_ev_ext_info_changed {
	__we16	eiw_wen;
	__u8	eiw[];
} __packed;

#define MGMT_EV_PHY_CONFIGUWATION_CHANGED	0x0026
stwuct mgmt_ev_phy_configuwation_changed {
	__we32	sewected_phys;
} __packed;

#define MGMT_EV_EXP_FEATUWE_CHANGED	0x0027
stwuct mgmt_ev_exp_featuwe_changed {
	__u8	uuid[16];
	__we32	fwags;
} __packed;

#define MGMT_EV_DEVICE_FWAGS_CHANGED		0x002a
stwuct mgmt_ev_device_fwags_changed {
	stwuct mgmt_addw_info addw;
	__we32 suppowted_fwags;
	__we32 cuwwent_fwags;
} __packed;

#define MGMT_EV_ADV_MONITOW_ADDED	0x002b
stwuct mgmt_ev_adv_monitow_added {
	__we16 monitow_handwe;
}  __packed;

#define MGMT_EV_ADV_MONITOW_WEMOVED	0x002c
stwuct mgmt_ev_adv_monitow_wemoved {
	__we16 monitow_handwe;
}  __packed;

#define MGMT_EV_CONTWOWWEW_SUSPEND		0x002d
stwuct mgmt_ev_contwowwew_suspend {
	__u8	suspend_state;
} __packed;

#define MGMT_EV_CONTWOWWEW_WESUME		0x002e
stwuct mgmt_ev_contwowwew_wesume {
	__u8	wake_weason;
	stwuct mgmt_addw_info addw;
} __packed;

#define MGMT_WAKE_WEASON_NON_BT_WAKE		0x0
#define MGMT_WAKE_WEASON_UNEXPECTED		0x1
#define MGMT_WAKE_WEASON_WEMOTE_WAKE		0x2

#define MGMT_EV_ADV_MONITOW_DEVICE_FOUND	0x002f
stwuct mgmt_ev_adv_monitow_device_found {
	__we16 monitow_handwe;
	stwuct mgmt_addw_info addw;
	__s8   wssi;
	__we32 fwags;
	__we16 eiw_wen;
	__u8   eiw[];
} __packed;

#define MGMT_EV_ADV_MONITOW_DEVICE_WOST		0x0030
stwuct mgmt_ev_adv_monitow_device_wost {
	__we16 monitow_handwe;
	stwuct mgmt_addw_info addw;
} __packed;

#define MGMT_EV_MESH_DEVICE_FOUND	0x0031
stwuct mgmt_ev_mesh_device_found {
	stwuct mgmt_addw_info addw;
	__s8	wssi;
	__we64	instant;
	__we32	fwags;
	__we16	eiw_wen;
	__u8	eiw[];
} __packed;


#define MGMT_EV_MESH_PACKET_CMPWT		0x0032
stwuct mgmt_ev_mesh_pkt_cmpwt {
	__u8	handwe;
} __packed;
