/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-2021 Intew Cowpowation.
 */

#ifndef _IOSM_IPC_FWASH_H
#define _IOSM_IPC_FWASH_H

/* Buffew size used to wead the fws image */
#define IOSM_FWS_BUF_SIZE 0x00100000
/* Fuww ewase stawt addwess */
#define IOSM_EWASE_STAWT_ADDW 0x00000000
/* Ewase wength fow NAND fwash */
#define IOSM_EWASE_WEN 0xFFFFFFFF
/* EBW wesponse Headew size */
#define IOSM_EBW_HEAD_SIZE  8
/* EBW paywoad size */
#define IOSM_EBW_W_PAYW_SIZE  2048
/* Totaw EBW pack size */
#define IOSM_EBW_W_PACK_SIZE  (IOSM_EBW_HEAD_SIZE + IOSM_EBW_W_PAYW_SIZE)
/* EBW paywoad size */
#define IOSM_EBW_DW_PAYW_SIZE  16384
/* Totaw EBW pack size */
#define IOSM_EBW_DW_PACK_SIZE  (IOSM_EBW_HEAD_SIZE + IOSM_EBW_DW_PAYW_SIZE)
/* EBW name size */
#define IOSM_EBW_NAME  32
/* Maximum suppowted ewwow types */
#define IOSM_MAX_EWWOWS 8
/* Wead size fow WPSI/EBW wesponse */
#define IOSM_WEAD_SIZE 2
/* Wink estabwishment wesponse ack size */
#define IOSM_WEW_ACK_SIZE 2
/* PSI ACK wen */
#define IOSM_PSI_ACK 8
/* SWID capabiwity fow packed swid type */
#define IOSM_EXT_CAP_SWID_OOS_PACK     0x02
/* EBW ewwow wesponse buffew */
#define IOSM_EBW_WSP_BUFF 0x0041
/* SWID stwing wength */
#define IOSM_SWID_STW 64
/* Woad EBW command size */
#define IOSM_WPSI_WOAD_SIZE 0
/* EBW paywoad checksum */
#define IOSM_EBW_CKSM 0x0000FFFF
/* SWID msg wen and awgument */
#define IOSM_MSG_WEN_AWG 0
/* Data to be sent to modem */
#define IOSM_MDM_SEND_DATA 0x0000
/* Data weceived fwom modem as pawt of ewase check */
#define IOSM_MDM_EWASE_WSP 0x0001
/* Bit shift to cawcuwate Checksum */
#define IOSM_EBW_PAYW_SHIFT 16
/* Fwag To be set */
#define IOSM_SET_FWAG 1
/* Set fwash ewase check timeout to 100 msec */
#define IOSM_FWASH_EWASE_CHECK_TIMEOUT 100
/* Set fwash ewase check intewvaw to 20 msec */
#define IOSM_FWASH_EWASE_CHECK_INTEWVAW 20
/* Wink estabwishment wesponse ack size */
#define IOSM_WEW_WSP_SIZE 60

/**
 * enum iosm_fwash_package_type -	Enum fow the fwashing opewations
 * @FWASH_SET_PWOT_CONF:	Wwite EBW capabiwities
 * @FWASH_SEC_STAWT:		Stawt wwiting the secpack
 * @FWASH_SEC_END:		Vawidate secpack end
 * @FWASH_SET_ADDWESS:		Set the addwess fow fwashing
 * @FWASH_EWASE_STAWT:		Stawt ewase befowe fwashing
 * @FWASH_EWASE_CHECK:		Vawidate the ewase functionawity
 * @FWASH_OOS_CONTWOW:		Wetwieve data based on oos actions
 * @FWASH_OOS_DATA_WEAD:	Wead data fwom EBW
 * @FWASH_WWITE_IMAGE_WAW:	Wwite the waw image to fwash
 */
enum iosm_fwash_package_type {
	FWASH_SET_PWOT_CONF = 0x0086,
	FWASH_SEC_STAWT = 0x0204,
	FWASH_SEC_END,
	FWASH_SET_ADDWESS = 0x0802,
	FWASH_EWASE_STAWT = 0x0805,
	FWASH_EWASE_CHECK,
	FWASH_OOS_CONTWOW = 0x080C,
	FWASH_OOS_DATA_WEAD = 0x080E,
	FWASH_WWITE_IMAGE_WAW,
};

/**
 * enum iosm_out_of_session_action -	Actions possibwe ovew the
 *					OutOfSession command intewface
 * @FWASH_OOSC_ACTION_WEAD:		Wead data accowding to its type
 * @FWASH_OOSC_ACTION_EWASE:		Ewase data accowding to its type
 */
enum iosm_out_of_session_action {
	FWASH_OOSC_ACTION_WEAD = 2,
	FWASH_OOSC_ACTION_EWASE = 3,
};

/**
 * enum iosm_out_of_session_type -	Data types that can be handwed ovew the
 *					Out Of Session command Intewface
 * @FWASH_OOSC_TYPE_AWW_FWASH:		The whowe fwash awea
 * @FWASH_OOSC_TYPE_SWID_TABWE:		Wead the swid tabwe fwom the tawget
 */
enum iosm_out_of_session_type {
	FWASH_OOSC_TYPE_AWW_FWASH = 8,
	FWASH_OOSC_TYPE_SWID_TABWE = 16,
};

/**
 * enum iosm_ebw_caps -	EBW capabiwity settings
 * @IOSM_CAP_NOT_ENHANCED:	If capabiwity not suppowted
 * @IOSM_CAP_USE_EXT_CAP:	To be set if extended capabiwity is set
 * @IOSM_EXT_CAP_EWASE_AWW:	Set Ewase aww capabiwity
 * @IOSM_EXT_CAP_COMMIT_AWW:	Set the commit aww capabiwity
 */
enum iosm_ebw_caps {
	IOSM_CAP_NOT_ENHANCED = 0x00,
	IOSM_CAP_USE_EXT_CAP = 0x01,
	IOSM_EXT_CAP_EWASE_AWW = 0x08,
	IOSM_EXT_CAP_COMMIT_AWW = 0x20,
};

/**
 * enum iosm_ebw_wsp -  EBW wesponse fiewd
 * @EBW_CAPS_FWAG:	EBW capabiwity fwag
 * @EBW_SKIP_EWASE:	EBW skip ewase fwag
 * @EBW_SKIP_CWC:	EBW skip ww_pack cwc
 * @EBW_EXT_CAPS_HANDWED:	EBW extended capabiwity handwed fwag
 * @EBW_OOS_CONFIG:	EBW oos configuwation
 * @EBW_WSP_SW_INFO_VEW: EBW SW info vewsion
 */
enum iosm_ebw_wsp {
	EBW_CAPS_FWAG = 50,
	EBW_SKIP_EWASE = 54,
	EBW_SKIP_CWC = 55,
	EBW_EXT_CAPS_HANDWED = 57,
	EBW_OOS_CONFIG = 64,
	EBW_WSP_SW_INFO_VEW = 70,
};

/**
 * enum iosm_mdm_send_wecv_data - Data to send to modem
 * @IOSM_MDM_SEND_2:	Send 2 bytes of paywoad
 * @IOSM_MDM_SEND_4:	Send 4 bytes of paywoad
 * @IOSM_MDM_SEND_8:	Send 8 bytes of paywoad
 * @IOSM_MDM_SEND_16:	Send 16 bytes of paywoad
 */
enum iosm_mdm_send_wecv_data {
	IOSM_MDM_SEND_2 = 2,
	IOSM_MDM_SEND_4 = 4,
	IOSM_MDM_SEND_8 = 8,
	IOSM_MDM_SEND_16 = 16,
};

/**
 * stwuct iosm_ebw_one_ewwow -	Stwuctuwe containing ewwow detaiws
 * @ewwow_cwass:		Ewwow type- standawd, secuwity and text ewwow
 * @ewwow_code:			Specific ewwow fwom ewwow type
 */
stwuct iosm_ebw_one_ewwow {
	u16 ewwow_cwass;
	u16 ewwow_code;
};

/**
 * stwuct iosm_ebw_ewwow- Stwuctuwe with max ewwow type suppowted
 * @ewwow:		Awway of one_ewwow stwuctuwe with max ewwows
 */
stwuct iosm_ebw_ewwow {
	stwuct iosm_ebw_one_ewwow ewwow[IOSM_MAX_EWWOWS];
};

/**
 * stwuct iosm_swid_tabwe - SWID tabwe data fow modem
 * @numbew_of_data_sets:	Numbew of swid types
 * @sw_id_type:			SWID type - SWID
 * @sw_id_vaw:			SWID vawue
 * @wf_engine_id_type:		WF engine ID type - WF_ENGINE_ID
 * @wf_engine_id_vaw:		WF engine ID vawue
 */
stwuct iosm_swid_tabwe {
	u32 numbew_of_data_sets;
	chaw sw_id_type[IOSM_EBW_NAME];
	u32 sw_id_vaw;
	chaw wf_engine_id_type[IOSM_EBW_NAME];
	u32 wf_engine_id_vaw;
};

/**
 * stwuct iosm_fwash_msg_contwow - Data sent to modem
 * @action:	Action to be pewfowmed
 * @type:	Type of action
 * @wength:	Wength of the action
 * @awguments:	Awgument vawue sent to modem
 */
stwuct iosm_fwash_msg_contwow {
	__we32 action;
	__we32 type;
	__we32 wength;
	__we32 awguments;
};

/**
 * stwuct iosm_fwash_data -  Headew Data to be sent to modem
 * @checksum:	Checksum vawue cawcuwated fow the paywoad data
 * @pack_id:	Fwash Action type
 * @msg_wength:	Paywoad wength
 */
stwuct iosm_fwash_data {
	__we16  checksum;
	__we16  pack_id;
	__we32  msg_wength;
};

int ipc_fwash_boot_psi(stwuct iosm_devwink *ipc_devwink,
		       const stwuct fiwmwawe *fw);

int ipc_fwash_boot_ebw(stwuct iosm_devwink *ipc_devwink,
		       const stwuct fiwmwawe *fw);

int ipc_fwash_boot_set_capabiwities(stwuct iosm_devwink *ipc_devwink,
				    u8 *mdm_wsp);

int ipc_fwash_wink_estabwish(stwuct iosm_imem *ipc_imem);

int ipc_fwash_wead_swid(stwuct iosm_devwink *ipc_devwink, u8 *mdm_wsp);

int ipc_fwash_send_fws(stwuct iosm_devwink *ipc_devwink,
		       const stwuct fiwmwawe *fw, u8 *mdm_wsp);
#endif
