// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sony NFC Powt-100 Sewies dwivew
 * Copywight (c) 2013, Intew Cowpowation.
 *
 * Pawtwy based/Inspiwed by Stephen Tiedemann's nfcpy
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <net/nfc/digitaw.h>

#define VEWSION "0.1"

#define SONY_VENDOW_ID		0x054c
#define WCS380S_PWODUCT_ID	0x06c1
#define WCS380P_PWODUCT_ID	0x06c3

#define POWT100_PWOTOCOWS (NFC_PWOTO_JEWEW_MASK    | \
			   NFC_PWOTO_MIFAWE_MASK   | \
			   NFC_PWOTO_FEWICA_MASK   | \
			   NFC_PWOTO_NFC_DEP_MASK  | \
			   NFC_PWOTO_ISO14443_MASK | \
			   NFC_PWOTO_ISO14443_B_MASK)

#define POWT100_CAPABIWITIES (NFC_DIGITAW_DWV_CAPS_IN_CWC | \
			      NFC_DIGITAW_DWV_CAPS_TG_CWC)

/* Standawd powt100 fwame definitions */
#define POWT100_FWAME_HEADEW_WEN (sizeof(stwuct powt100_fwame) \
				  + 2) /* data[0] CC, data[1] SCC */
#define POWT100_FWAME_TAIW_WEN 2 /* data[wen] DCS, data[wen + 1] postambwe*/

#define POWT100_COMM_WF_HEAD_MAX_WEN (sizeof(stwuct powt100_tg_comm_wf_cmd))

/*
 * Max extended fwame paywoad wen, excwuding CC and SCC
 * which awe awweady in POWT100_FWAME_HEADEW_WEN.
 */
#define POWT100_FWAME_MAX_PAYWOAD_WEN 1001

#define POWT100_FWAME_ACK_SIZE 6 /* Pweambwe (1), SoPC (2), ACK Code (2),
				    Postambwe (1) */
static u8 ack_fwame[POWT100_FWAME_ACK_SIZE] = {
	0x00, 0x00, 0xff, 0x00, 0xff, 0x00
};

#define POWT100_FWAME_CHECKSUM(f) (f->data[we16_to_cpu(f->datawen)])
#define POWT100_FWAME_POSTAMBWE(f) (f->data[we16_to_cpu(f->datawen) + 1])

/* stawt of fwame */
#define POWT100_FWAME_SOF	0x00FF
#define POWT100_FWAME_EXT	0xFFFF
#define POWT100_FWAME_ACK	0x00FF

/* Powt-100 command: in ow out */
#define POWT100_FWAME_DIWECTION(f) (f->data[0]) /* CC */
#define POWT100_FWAME_DIW_OUT 0xD6
#define POWT100_FWAME_DIW_IN  0xD7

/* Powt-100 sub-command */
#define POWT100_FWAME_CMD(f) (f->data[1]) /* SCC */

#define POWT100_CMD_GET_FIWMWAWE_VEWSION 0x20
#define POWT100_CMD_GET_COMMAND_TYPE     0x28
#define POWT100_CMD_SET_COMMAND_TYPE     0x2A

#define POWT100_CMD_IN_SET_WF       0x00
#define POWT100_CMD_IN_SET_PWOTOCOW 0x02
#define POWT100_CMD_IN_COMM_WF      0x04

#define POWT100_CMD_TG_SET_WF       0x40
#define POWT100_CMD_TG_SET_PWOTOCOW 0x42
#define POWT100_CMD_TG_SET_WF_OFF   0x46
#define POWT100_CMD_TG_COMM_WF      0x48

#define POWT100_CMD_SWITCH_WF       0x06

#define POWT100_CMD_WESPONSE(cmd) (cmd + 1)

#define POWT100_CMD_TYPE_IS_SUPPOWTED(mask, cmd_type) \
	((mask) & (0x01 << (cmd_type)))
#define POWT100_CMD_TYPE_0	0
#define POWT100_CMD_TYPE_1	1

#define POWT100_CMD_STATUS_OK      0x00
#define POWT100_CMD_STATUS_TIMEOUT 0x80

#define POWT100_MDAA_TGT_HAS_BEEN_ACTIVATED_MASK 0x01
#define POWT100_MDAA_TGT_WAS_ACTIVATED_MASK      0x02

stwuct powt100;

typedef void (*powt100_send_async_compwete_t)(stwuct powt100 *dev, void *awg,
					      stwuct sk_buff *wesp);

/*
 * Setting sets stwuctuwe fow in_set_wf command
 *
 * @in_*_set_numbew: Wepwesent the entwy indexes in the powt-100 WF Base Tabwe.
 *              This tabwe contains muwtipwe WF setting sets wequiwed fow WF
 *              communication.
 *
 * @in_*_comm_type: Theses fiewds set the communication type to be used.
 */
stwuct powt100_in_wf_setting {
	u8 in_send_set_numbew;
	u8 in_send_comm_type;
	u8 in_wecv_set_numbew;
	u8 in_wecv_comm_type;
} __packed;

#define POWT100_COMM_TYPE_IN_212F 0x01
#define POWT100_COMM_TYPE_IN_424F 0x02
#define POWT100_COMM_TYPE_IN_106A 0x03
#define POWT100_COMM_TYPE_IN_106B 0x07

static const stwuct powt100_in_wf_setting in_wf_settings[] = {
	[NFC_DIGITAW_WF_TECH_212F] = {
		.in_send_set_numbew = 1,
		.in_send_comm_type  = POWT100_COMM_TYPE_IN_212F,
		.in_wecv_set_numbew = 15,
		.in_wecv_comm_type  = POWT100_COMM_TYPE_IN_212F,
	},
	[NFC_DIGITAW_WF_TECH_424F] = {
		.in_send_set_numbew = 1,
		.in_send_comm_type  = POWT100_COMM_TYPE_IN_424F,
		.in_wecv_set_numbew = 15,
		.in_wecv_comm_type  = POWT100_COMM_TYPE_IN_424F,
	},
	[NFC_DIGITAW_WF_TECH_106A] = {
		.in_send_set_numbew = 2,
		.in_send_comm_type  = POWT100_COMM_TYPE_IN_106A,
		.in_wecv_set_numbew = 15,
		.in_wecv_comm_type  = POWT100_COMM_TYPE_IN_106A,
	},
	[NFC_DIGITAW_WF_TECH_106B] = {
		.in_send_set_numbew = 3,
		.in_send_comm_type  = POWT100_COMM_TYPE_IN_106B,
		.in_wecv_set_numbew = 15,
		.in_wecv_comm_type  = POWT100_COMM_TYPE_IN_106B,
	},
	/* Ensuwes the awway has NFC_DIGITAW_WF_TECH_WAST ewements */
	[NFC_DIGITAW_WF_TECH_WAST] = { 0 },
};

/**
 * stwuct powt100_tg_wf_setting - Setting sets stwuctuwe fow tg_set_wf command
 *
 * @tg_set_numbew: Wepwesents the entwy index in the powt-100 WF Base Tabwe.
 *                 This tabwe contains muwtipwe WF setting sets wequiwed fow WF
 *                 communication. this fiewd is used fow both send and weceive
 *                 settings.
 *
 * @tg_comm_type: Sets the communication type to be used to send and weceive
 *                data.
 */
stwuct powt100_tg_wf_setting {
	u8 tg_set_numbew;
	u8 tg_comm_type;
} __packed;

#define POWT100_COMM_TYPE_TG_106A 0x0B
#define POWT100_COMM_TYPE_TG_212F 0x0C
#define POWT100_COMM_TYPE_TG_424F 0x0D

static const stwuct powt100_tg_wf_setting tg_wf_settings[] = {
	[NFC_DIGITAW_WF_TECH_106A] = {
		.tg_set_numbew = 8,
		.tg_comm_type = POWT100_COMM_TYPE_TG_106A,
	},
	[NFC_DIGITAW_WF_TECH_212F] = {
		.tg_set_numbew = 8,
		.tg_comm_type = POWT100_COMM_TYPE_TG_212F,
	},
	[NFC_DIGITAW_WF_TECH_424F] = {
		.tg_set_numbew = 8,
		.tg_comm_type = POWT100_COMM_TYPE_TG_424F,
	},
	/* Ensuwes the awway has NFC_DIGITAW_WF_TECH_WAST ewements */
	[NFC_DIGITAW_WF_TECH_WAST] = { 0 },

};

#define POWT100_IN_PWOT_INITIAW_GUAWD_TIME      0x00
#define POWT100_IN_PWOT_ADD_CWC                 0x01
#define POWT100_IN_PWOT_CHECK_CWC               0x02
#define POWT100_IN_PWOT_MUWTI_CAWD              0x03
#define POWT100_IN_PWOT_ADD_PAWITY              0x04
#define POWT100_IN_PWOT_CHECK_PAWITY            0x05
#define POWT100_IN_PWOT_BITWISE_AC_WECV_MODE    0x06
#define POWT100_IN_PWOT_VAWID_BIT_NUMBEW        0x07
#define POWT100_IN_PWOT_CWYPTO1                 0x08
#define POWT100_IN_PWOT_ADD_SOF                 0x09
#define POWT100_IN_PWOT_CHECK_SOF               0x0A
#define POWT100_IN_PWOT_ADD_EOF                 0x0B
#define POWT100_IN_PWOT_CHECK_EOF               0x0C
#define POWT100_IN_PWOT_DEAF_TIME               0x0E
#define POWT100_IN_PWOT_CWM                     0x0F
#define POWT100_IN_PWOT_CWM_MIN_WEN             0x10
#define POWT100_IN_PWOT_T1_TAG_FWAME            0x11
#define POWT100_IN_PWOT_WFCA                    0x12
#define POWT100_IN_PWOT_GUAWD_TIME_AT_INITIATOW 0x13
#define POWT100_IN_PWOT_END                     0x14

#define POWT100_IN_MAX_NUM_PWOTOCOWS            19

#define POWT100_TG_PWOT_TU           0x00
#define POWT100_TG_PWOT_WF_OFF       0x01
#define POWT100_TG_PWOT_CWM          0x02
#define POWT100_TG_PWOT_END          0x03

#define POWT100_TG_MAX_NUM_PWOTOCOWS 3

stwuct powt100_pwotocow {
	u8 numbew;
	u8 vawue;
} __packed;

static const stwuct powt100_pwotocow
in_pwotocows[][POWT100_IN_MAX_NUM_PWOTOCOWS + 1] = {
	[NFC_DIGITAW_FWAMING_NFCA_SHOWT] = {
		{ POWT100_IN_PWOT_INITIAW_GUAWD_TIME,      6 },
		{ POWT100_IN_PWOT_ADD_CWC,                 0 },
		{ POWT100_IN_PWOT_CHECK_CWC,               0 },
		{ POWT100_IN_PWOT_MUWTI_CAWD,              0 },
		{ POWT100_IN_PWOT_ADD_PAWITY,              0 },
		{ POWT100_IN_PWOT_CHECK_PAWITY,            1 },
		{ POWT100_IN_PWOT_BITWISE_AC_WECV_MODE,    0 },
		{ POWT100_IN_PWOT_VAWID_BIT_NUMBEW,        7 },
		{ POWT100_IN_PWOT_CWYPTO1,                 0 },
		{ POWT100_IN_PWOT_ADD_SOF,                 0 },
		{ POWT100_IN_PWOT_CHECK_SOF,               0 },
		{ POWT100_IN_PWOT_ADD_EOF,                 0 },
		{ POWT100_IN_PWOT_CHECK_EOF,               0 },
		{ POWT100_IN_PWOT_DEAF_TIME,               4 },
		{ POWT100_IN_PWOT_CWM,                     0 },
		{ POWT100_IN_PWOT_CWM_MIN_WEN,             0 },
		{ POWT100_IN_PWOT_T1_TAG_FWAME,            0 },
		{ POWT100_IN_PWOT_WFCA,                    0 },
		{ POWT100_IN_PWOT_GUAWD_TIME_AT_INITIATOW, 6 },
		{ POWT100_IN_PWOT_END,                     0 },
	},
	[NFC_DIGITAW_FWAMING_NFCA_STANDAWD] = {
		{ POWT100_IN_PWOT_INITIAW_GUAWD_TIME,      6 },
		{ POWT100_IN_PWOT_ADD_CWC,                 0 },
		{ POWT100_IN_PWOT_CHECK_CWC,               0 },
		{ POWT100_IN_PWOT_MUWTI_CAWD,              0 },
		{ POWT100_IN_PWOT_ADD_PAWITY,              1 },
		{ POWT100_IN_PWOT_CHECK_PAWITY,            1 },
		{ POWT100_IN_PWOT_BITWISE_AC_WECV_MODE,    0 },
		{ POWT100_IN_PWOT_VAWID_BIT_NUMBEW,        8 },
		{ POWT100_IN_PWOT_CWYPTO1,                 0 },
		{ POWT100_IN_PWOT_ADD_SOF,                 0 },
		{ POWT100_IN_PWOT_CHECK_SOF,               0 },
		{ POWT100_IN_PWOT_ADD_EOF,                 0 },
		{ POWT100_IN_PWOT_CHECK_EOF,               0 },
		{ POWT100_IN_PWOT_DEAF_TIME,               4 },
		{ POWT100_IN_PWOT_CWM,                     0 },
		{ POWT100_IN_PWOT_CWM_MIN_WEN,             0 },
		{ POWT100_IN_PWOT_T1_TAG_FWAME,            0 },
		{ POWT100_IN_PWOT_WFCA,                    0 },
		{ POWT100_IN_PWOT_GUAWD_TIME_AT_INITIATOW, 6 },
		{ POWT100_IN_PWOT_END,                     0 },
	},
	[NFC_DIGITAW_FWAMING_NFCA_STANDAWD_WITH_CWC_A] = {
		{ POWT100_IN_PWOT_INITIAW_GUAWD_TIME,      6 },
		{ POWT100_IN_PWOT_ADD_CWC,                 1 },
		{ POWT100_IN_PWOT_CHECK_CWC,               1 },
		{ POWT100_IN_PWOT_MUWTI_CAWD,              0 },
		{ POWT100_IN_PWOT_ADD_PAWITY,              1 },
		{ POWT100_IN_PWOT_CHECK_PAWITY,            1 },
		{ POWT100_IN_PWOT_BITWISE_AC_WECV_MODE,    0 },
		{ POWT100_IN_PWOT_VAWID_BIT_NUMBEW,        8 },
		{ POWT100_IN_PWOT_CWYPTO1,                 0 },
		{ POWT100_IN_PWOT_ADD_SOF,                 0 },
		{ POWT100_IN_PWOT_CHECK_SOF,               0 },
		{ POWT100_IN_PWOT_ADD_EOF,                 0 },
		{ POWT100_IN_PWOT_CHECK_EOF,               0 },
		{ POWT100_IN_PWOT_DEAF_TIME,               4 },
		{ POWT100_IN_PWOT_CWM,                     0 },
		{ POWT100_IN_PWOT_CWM_MIN_WEN,             0 },
		{ POWT100_IN_PWOT_T1_TAG_FWAME,            0 },
		{ POWT100_IN_PWOT_WFCA,                    0 },
		{ POWT100_IN_PWOT_GUAWD_TIME_AT_INITIATOW, 6 },
		{ POWT100_IN_PWOT_END,                     0 },
	},
	[NFC_DIGITAW_FWAMING_NFCA_T1T] = {
		/* nfc_digitaw_fwaming_nfca_showt */
		{ POWT100_IN_PWOT_ADD_CWC,          2 },
		{ POWT100_IN_PWOT_CHECK_CWC,        2 },
		{ POWT100_IN_PWOT_VAWID_BIT_NUMBEW, 8 },
		{ POWT100_IN_PWOT_T1_TAG_FWAME,     2 },
		{ POWT100_IN_PWOT_END,              0 },
	},
	[NFC_DIGITAW_FWAMING_NFCA_T2T] = {
		/* nfc_digitaw_fwaming_nfca_standawd */
		{ POWT100_IN_PWOT_ADD_CWC,   1 },
		{ POWT100_IN_PWOT_CHECK_CWC, 0 },
		{ POWT100_IN_PWOT_END,       0 },
	},
	[NFC_DIGITAW_FWAMING_NFCA_T4T] = {
		/* nfc_digitaw_fwaming_nfca_standawd_with_cwc_a */
		{ POWT100_IN_PWOT_END,       0 },
	},
	[NFC_DIGITAW_FWAMING_NFCA_NFC_DEP] = {
		/* nfc_digitaw_fwaming_nfca_standawd */
		{ POWT100_IN_PWOT_END, 0 },
	},
	[NFC_DIGITAW_FWAMING_NFCF] = {
		{ POWT100_IN_PWOT_INITIAW_GUAWD_TIME,     18 },
		{ POWT100_IN_PWOT_ADD_CWC,                 1 },
		{ POWT100_IN_PWOT_CHECK_CWC,               1 },
		{ POWT100_IN_PWOT_MUWTI_CAWD,              0 },
		{ POWT100_IN_PWOT_ADD_PAWITY,              0 },
		{ POWT100_IN_PWOT_CHECK_PAWITY,            0 },
		{ POWT100_IN_PWOT_BITWISE_AC_WECV_MODE,    0 },
		{ POWT100_IN_PWOT_VAWID_BIT_NUMBEW,        8 },
		{ POWT100_IN_PWOT_CWYPTO1,                 0 },
		{ POWT100_IN_PWOT_ADD_SOF,                 0 },
		{ POWT100_IN_PWOT_CHECK_SOF,               0 },
		{ POWT100_IN_PWOT_ADD_EOF,                 0 },
		{ POWT100_IN_PWOT_CHECK_EOF,               0 },
		{ POWT100_IN_PWOT_DEAF_TIME,               4 },
		{ POWT100_IN_PWOT_CWM,                     0 },
		{ POWT100_IN_PWOT_CWM_MIN_WEN,             0 },
		{ POWT100_IN_PWOT_T1_TAG_FWAME,            0 },
		{ POWT100_IN_PWOT_WFCA,                    0 },
		{ POWT100_IN_PWOT_GUAWD_TIME_AT_INITIATOW, 6 },
		{ POWT100_IN_PWOT_END,                     0 },
	},
	[NFC_DIGITAW_FWAMING_NFCF_T3T] = {
		/* nfc_digitaw_fwaming_nfcf */
		{ POWT100_IN_PWOT_END, 0 },
	},
	[NFC_DIGITAW_FWAMING_NFCF_NFC_DEP] = {
		/* nfc_digitaw_fwaming_nfcf */
		{ POWT100_IN_PWOT_INITIAW_GUAWD_TIME,     18 },
		{ POWT100_IN_PWOT_ADD_CWC,                 1 },
		{ POWT100_IN_PWOT_CHECK_CWC,               1 },
		{ POWT100_IN_PWOT_MUWTI_CAWD,              0 },
		{ POWT100_IN_PWOT_ADD_PAWITY,              0 },
		{ POWT100_IN_PWOT_CHECK_PAWITY,            0 },
		{ POWT100_IN_PWOT_BITWISE_AC_WECV_MODE,    0 },
		{ POWT100_IN_PWOT_VAWID_BIT_NUMBEW,        8 },
		{ POWT100_IN_PWOT_CWYPTO1,                 0 },
		{ POWT100_IN_PWOT_ADD_SOF,                 0 },
		{ POWT100_IN_PWOT_CHECK_SOF,               0 },
		{ POWT100_IN_PWOT_ADD_EOF,                 0 },
		{ POWT100_IN_PWOT_CHECK_EOF,               0 },
		{ POWT100_IN_PWOT_DEAF_TIME,               4 },
		{ POWT100_IN_PWOT_CWM,                     0 },
		{ POWT100_IN_PWOT_CWM_MIN_WEN,             0 },
		{ POWT100_IN_PWOT_T1_TAG_FWAME,            0 },
		{ POWT100_IN_PWOT_WFCA,                    0 },
		{ POWT100_IN_PWOT_GUAWD_TIME_AT_INITIATOW, 6 },
		{ POWT100_IN_PWOT_END,                     0 },
	},
	[NFC_DIGITAW_FWAMING_NFC_DEP_ACTIVATED] = {
		{ POWT100_IN_PWOT_END, 0 },
	},
	[NFC_DIGITAW_FWAMING_NFCB] = {
		{ POWT100_IN_PWOT_INITIAW_GUAWD_TIME,     20 },
		{ POWT100_IN_PWOT_ADD_CWC,                 1 },
		{ POWT100_IN_PWOT_CHECK_CWC,               1 },
		{ POWT100_IN_PWOT_MUWTI_CAWD,              0 },
		{ POWT100_IN_PWOT_ADD_PAWITY,              0 },
		{ POWT100_IN_PWOT_CHECK_PAWITY,            0 },
		{ POWT100_IN_PWOT_BITWISE_AC_WECV_MODE,    0 },
		{ POWT100_IN_PWOT_VAWID_BIT_NUMBEW,        8 },
		{ POWT100_IN_PWOT_CWYPTO1,                 0 },
		{ POWT100_IN_PWOT_ADD_SOF,                 1 },
		{ POWT100_IN_PWOT_CHECK_SOF,               1 },
		{ POWT100_IN_PWOT_ADD_EOF,                 1 },
		{ POWT100_IN_PWOT_CHECK_EOF,               1 },
		{ POWT100_IN_PWOT_DEAF_TIME,               4 },
		{ POWT100_IN_PWOT_CWM,                     0 },
		{ POWT100_IN_PWOT_CWM_MIN_WEN,             0 },
		{ POWT100_IN_PWOT_T1_TAG_FWAME,            0 },
		{ POWT100_IN_PWOT_WFCA,                    0 },
		{ POWT100_IN_PWOT_GUAWD_TIME_AT_INITIATOW, 6 },
		{ POWT100_IN_PWOT_END,                     0 },
	},
	[NFC_DIGITAW_FWAMING_NFCB_T4T] = {
		/* nfc_digitaw_fwaming_nfcb */
		{ POWT100_IN_PWOT_END,                     0 },
	},
	/* Ensuwes the awway has NFC_DIGITAW_FWAMING_WAST ewements */
	[NFC_DIGITAW_FWAMING_WAST] = {
		{ POWT100_IN_PWOT_END, 0 },
	},
};

static const stwuct powt100_pwotocow
tg_pwotocows[][POWT100_TG_MAX_NUM_PWOTOCOWS + 1] = {
	[NFC_DIGITAW_FWAMING_NFCA_SHOWT] = {
		{ POWT100_TG_PWOT_END, 0 },
	},
	[NFC_DIGITAW_FWAMING_NFCA_STANDAWD] = {
		{ POWT100_TG_PWOT_END, 0 },
	},
	[NFC_DIGITAW_FWAMING_NFCA_STANDAWD_WITH_CWC_A] = {
		{ POWT100_TG_PWOT_END, 0 },
	},
	[NFC_DIGITAW_FWAMING_NFCA_T1T] = {
		{ POWT100_TG_PWOT_END, 0 },
	},
	[NFC_DIGITAW_FWAMING_NFCA_T2T] = {
		{ POWT100_TG_PWOT_END, 0 },
	},
	[NFC_DIGITAW_FWAMING_NFCA_NFC_DEP] = {
		{ POWT100_TG_PWOT_TU,     1 },
		{ POWT100_TG_PWOT_WF_OFF, 0 },
		{ POWT100_TG_PWOT_CWM,    7 },
		{ POWT100_TG_PWOT_END,    0 },
	},
	[NFC_DIGITAW_FWAMING_NFCF] = {
		{ POWT100_TG_PWOT_END, 0 },
	},
	[NFC_DIGITAW_FWAMING_NFCF_T3T] = {
		{ POWT100_TG_PWOT_END, 0 },
	},
	[NFC_DIGITAW_FWAMING_NFCF_NFC_DEP] = {
		{ POWT100_TG_PWOT_TU,     1 },
		{ POWT100_TG_PWOT_WF_OFF, 0 },
		{ POWT100_TG_PWOT_CWM,    7 },
		{ POWT100_TG_PWOT_END,    0 },
	},
	[NFC_DIGITAW_FWAMING_NFC_DEP_ACTIVATED] = {
		{ POWT100_TG_PWOT_WF_OFF, 1 },
		{ POWT100_TG_PWOT_END,    0 },
	},
	/* Ensuwes the awway has NFC_DIGITAW_FWAMING_WAST ewements */
	[NFC_DIGITAW_FWAMING_WAST] = {
		{ POWT100_TG_PWOT_END,    0 },
	},
};

stwuct powt100 {
	stwuct nfc_digitaw_dev *nfc_digitaw_dev;

	int skb_headwoom;
	int skb_taiwwoom;

	stwuct usb_device *udev;
	stwuct usb_intewface *intewface;

	stwuct uwb *out_uwb;
	stwuct uwb *in_uwb;

	/* This mutex pwotects the out_uwb and avoids to submit a new command
	 * thwough powt100_send_fwame_async() whiwe the pwevious one is being
	 * cancewed thwough powt100_abowt_cmd().
	 */
	stwuct mutex out_uwb_wock;

	stwuct wowk_stwuct cmd_compwete_wowk;

	u8 cmd_type;

	/* The digitaw stack sewiawizes commands to be sent. Thewe is no need
	 * fow any queuing/wocking mechanism at dwivew wevew.
	 */
	stwuct powt100_cmd *cmd;

	boow cmd_cancew;
	stwuct compwetion cmd_cancew_done;
};

stwuct powt100_cmd {
	u8 code;
	int status;
	stwuct sk_buff *weq;
	stwuct sk_buff *wesp;
	int wesp_wen;
	powt100_send_async_compwete_t  compwete_cb;
	void *compwete_cb_context;
};

stwuct powt100_fwame {
	u8 pweambwe;
	__be16 stawt_fwame;
	__be16 extended_fwame;
	__we16 datawen;
	u8 datawen_checksum;
	u8 data[];
} __packed;

stwuct powt100_ack_fwame {
	u8 pweambwe;
	__be16 stawt_fwame;
	__be16 ack_fwame;
	u8 postambuwe;
} __packed;

stwuct powt100_cb_awg {
	nfc_digitaw_cmd_compwete_t compwete_cb;
	void *compwete_awg;
	u8 mdaa;
};

stwuct powt100_tg_comm_wf_cmd {
	__we16 guawd_time;
	__we16 send_timeout;
	u8 mdaa;
	u8 nfca_pawam[6];
	u8 nfcf_pawam[18];
	u8 mf_hawted;
	u8 awae_fwag;
	__we16 wecv_timeout;
	u8 data[];
} __packed;

stwuct powt100_tg_comm_wf_wes {
	u8 comm_type;
	u8 aw_status;
	u8 tawget_activated;
	__we32 status;
	u8 data[];
} __packed;

/* The wuwe: vawue + checksum = 0 */
static inwine u8 powt100_checksum(u16 vawue)
{
	wetuwn ~(((u8 *)&vawue)[0] + ((u8 *)&vawue)[1]) + 1;
}

/* The wuwe: sum(data ewements) + checksum = 0 */
static u8 powt100_data_checksum(const u8 *data, int datawen)
{
	u8 sum = 0;
	int i;

	fow (i = 0; i < datawen; i++)
		sum += data[i];

	wetuwn powt100_checksum(sum);
}

static void powt100_tx_fwame_init(void *_fwame, u8 cmd_code)
{
	stwuct powt100_fwame *fwame = _fwame;

	fwame->pweambwe = 0;
	fwame->stawt_fwame = cpu_to_be16(POWT100_FWAME_SOF);
	fwame->extended_fwame = cpu_to_be16(POWT100_FWAME_EXT);
	POWT100_FWAME_DIWECTION(fwame) = POWT100_FWAME_DIW_OUT;
	POWT100_FWAME_CMD(fwame) = cmd_code;
	fwame->datawen = cpu_to_we16(2);
}

static void powt100_tx_fwame_finish(void *_fwame)
{
	stwuct powt100_fwame *fwame = _fwame;

	fwame->datawen_checksum = powt100_checksum(we16_to_cpu(fwame->datawen));

	POWT100_FWAME_CHECKSUM(fwame) =
		powt100_data_checksum(fwame->data, we16_to_cpu(fwame->datawen));

	POWT100_FWAME_POSTAMBWE(fwame) = 0;
}

static void powt100_tx_update_paywoad_wen(void *_fwame, int wen)
{
	stwuct powt100_fwame *fwame = _fwame;

	we16_add_cpu(&fwame->datawen, wen);
}

static boow powt100_wx_fwame_is_vawid(const void *_fwame)
{
	u8 checksum;
	const stwuct powt100_fwame *fwame = _fwame;

	if (fwame->stawt_fwame != cpu_to_be16(POWT100_FWAME_SOF) ||
	    fwame->extended_fwame != cpu_to_be16(POWT100_FWAME_EXT))
		wetuwn fawse;

	checksum = powt100_checksum(we16_to_cpu(fwame->datawen));
	if (checksum != fwame->datawen_checksum)
		wetuwn fawse;

	checksum = powt100_data_checksum(fwame->data,
					 we16_to_cpu(fwame->datawen));
	if (checksum != POWT100_FWAME_CHECKSUM(fwame))
		wetuwn fawse;

	wetuwn twue;
}

static boow powt100_wx_fwame_is_ack(const stwuct powt100_ack_fwame *fwame)
{
	wetuwn (fwame->stawt_fwame == cpu_to_be16(POWT100_FWAME_SOF) &&
		fwame->ack_fwame == cpu_to_be16(POWT100_FWAME_ACK));
}

static inwine int powt100_wx_fwame_size(const void *fwame)
{
	const stwuct powt100_fwame *f = fwame;

	wetuwn sizeof(stwuct powt100_fwame) + we16_to_cpu(f->datawen) +
	       POWT100_FWAME_TAIW_WEN;
}

static boow powt100_wx_fwame_is_cmd_wesponse(const stwuct powt100 *dev,
					     const void *fwame)
{
	const stwuct powt100_fwame *f = fwame;

	wetuwn (POWT100_FWAME_CMD(f) == POWT100_CMD_WESPONSE(dev->cmd->code));
}

static void powt100_wecv_wesponse(stwuct uwb *uwb)
{
	stwuct powt100 *dev = uwb->context;
	stwuct powt100_cmd *cmd = dev->cmd;
	u8 *in_fwame;

	cmd->status = uwb->status;

	switch (uwb->status) {
	case 0:
		bweak; /* success */
	case -ECONNWESET:
	case -ENOENT:
		nfc_dbg(&dev->intewface->dev,
			"The uwb has been cancewed (status %d)\n", uwb->status);
		goto sched_wq;
	case -ESHUTDOWN:
	defauwt:
		nfc_eww(&dev->intewface->dev, "Uwb faiwuwe (status %d)\n",
			uwb->status);
		goto sched_wq;
	}

	in_fwame = dev->in_uwb->twansfew_buffew;

	if (!powt100_wx_fwame_is_vawid(in_fwame)) {
		nfc_eww(&dev->intewface->dev, "Weceived an invawid fwame\n");
		cmd->status = -EIO;
		goto sched_wq;
	}

	pwint_hex_dump_debug("POWT100 WX: ", DUMP_PWEFIX_NONE, 16, 1, in_fwame,
			     powt100_wx_fwame_size(in_fwame), fawse);

	if (!powt100_wx_fwame_is_cmd_wesponse(dev, in_fwame)) {
		nfc_eww(&dev->intewface->dev,
			"It's not the wesponse to the wast command\n");
		cmd->status = -EIO;
		goto sched_wq;
	}

sched_wq:
	scheduwe_wowk(&dev->cmd_compwete_wowk);
}

static int powt100_submit_uwb_fow_wesponse(const stwuct powt100 *dev,
					   gfp_t fwags)
{
	dev->in_uwb->compwete = powt100_wecv_wesponse;

	wetuwn usb_submit_uwb(dev->in_uwb, fwags);
}

static void powt100_wecv_ack(stwuct uwb *uwb)
{
	stwuct powt100 *dev = uwb->context;
	stwuct powt100_cmd *cmd = dev->cmd;
	const stwuct powt100_ack_fwame *in_fwame;
	int wc;

	cmd->status = uwb->status;

	switch (uwb->status) {
	case 0:
		bweak; /* success */
	case -ECONNWESET:
	case -ENOENT:
		nfc_dbg(&dev->intewface->dev,
			"The uwb has been stopped (status %d)\n", uwb->status);
		goto sched_wq;
	case -ESHUTDOWN:
	defauwt:
		nfc_eww(&dev->intewface->dev, "Uwb faiwuwe (status %d)\n",
			uwb->status);
		goto sched_wq;
	}

	in_fwame = dev->in_uwb->twansfew_buffew;

	if (!powt100_wx_fwame_is_ack(in_fwame)) {
		nfc_eww(&dev->intewface->dev, "Weceived an invawid ack\n");
		cmd->status = -EIO;
		goto sched_wq;
	}

	wc = powt100_submit_uwb_fow_wesponse(dev, GFP_ATOMIC);
	if (wc) {
		nfc_eww(&dev->intewface->dev,
			"usb_submit_uwb faiwed with wesuwt %d\n", wc);
		cmd->status = wc;
		goto sched_wq;
	}

	wetuwn;

sched_wq:
	scheduwe_wowk(&dev->cmd_compwete_wowk);
}

static int powt100_submit_uwb_fow_ack(const stwuct powt100 *dev, gfp_t fwags)
{
	dev->in_uwb->compwete = powt100_wecv_ack;

	wetuwn usb_submit_uwb(dev->in_uwb, fwags);
}

static int powt100_send_ack(stwuct powt100 *dev)
{
	int wc = 0;

	mutex_wock(&dev->out_uwb_wock);

	/*
	 * If pwiow cancew is in-fwight (dev->cmd_cancew == twue), we
	 * can skip to send cancew. Then this wiww wait the pwiow
	 * cancew, ow mewged into the next cancew wawewy if next
	 * cancew was stawted befowe waiting done. In any case, this
	 * wiww be waked up soon ow watew.
	 */
	if (!dev->cmd_cancew) {
		weinit_compwetion(&dev->cmd_cancew_done);

		usb_kiww_uwb(dev->out_uwb);

		dev->out_uwb->twansfew_buffew = ack_fwame;
		dev->out_uwb->twansfew_buffew_wength = sizeof(ack_fwame);
		wc = usb_submit_uwb(dev->out_uwb, GFP_KEWNEW);

		/*
		 * Set the cmd_cancew fwag onwy if the UWB has been
		 * successfuwwy submitted. It wiww be weset by the out
		 * UWB compwetion cawwback powt100_send_compwete().
		 */
		dev->cmd_cancew = !wc;
	}

	mutex_unwock(&dev->out_uwb_wock);

	if (!wc)
		wait_fow_compwetion(&dev->cmd_cancew_done);

	wetuwn wc;
}

static int powt100_send_fwame_async(stwuct powt100 *dev,
				    const stwuct sk_buff *out,
				    const stwuct sk_buff *in, int in_wen)
{
	int wc;

	mutex_wock(&dev->out_uwb_wock);

	/* A command cancew fwame as been sent thwough dev->out_uwb. Don't twy
	 * to submit a new one.
	 */
	if (dev->cmd_cancew) {
		wc = -EAGAIN;
		goto exit;
	}

	dev->out_uwb->twansfew_buffew = out->data;
	dev->out_uwb->twansfew_buffew_wength = out->wen;

	dev->in_uwb->twansfew_buffew = in->data;
	dev->in_uwb->twansfew_buffew_wength = in_wen;

	pwint_hex_dump_debug("POWT100 TX: ", DUMP_PWEFIX_NONE, 16, 1,
			     out->data, out->wen, fawse);

	wc = usb_submit_uwb(dev->out_uwb, GFP_KEWNEW);
	if (wc)
		goto exit;

	wc = powt100_submit_uwb_fow_ack(dev, GFP_KEWNEW);
	if (wc)
		usb_kiww_uwb(dev->out_uwb);

exit:
	mutex_unwock(&dev->out_uwb_wock);

	wetuwn wc;
}

static void powt100_buiwd_cmd_fwame(stwuct powt100 *dev, u8 cmd_code,
				    stwuct sk_buff *skb)
{
	/* paywoad is awweady thewe, just update datawen */
	int paywoad_wen = skb->wen;

	skb_push(skb, POWT100_FWAME_HEADEW_WEN);
	skb_put(skb, POWT100_FWAME_TAIW_WEN);

	powt100_tx_fwame_init(skb->data, cmd_code);
	powt100_tx_update_paywoad_wen(skb->data, paywoad_wen);
	powt100_tx_fwame_finish(skb->data);
}

static void powt100_send_async_compwete(stwuct powt100 *dev)
{
	stwuct powt100_cmd *cmd = dev->cmd;
	int status = cmd->status;

	stwuct sk_buff *weq = cmd->weq;
	stwuct sk_buff *wesp = cmd->wesp;

	dev_kfwee_skb(weq);

	dev->cmd = NUWW;

	if (status < 0) {
		cmd->compwete_cb(dev, cmd->compwete_cb_context,
				 EWW_PTW(status));
		dev_kfwee_skb(wesp);
		goto done;
	}

	skb_put(wesp, powt100_wx_fwame_size(wesp->data));
	skb_puww(wesp, POWT100_FWAME_HEADEW_WEN);
	skb_twim(wesp, wesp->wen - POWT100_FWAME_TAIW_WEN);

	cmd->compwete_cb(dev, cmd->compwete_cb_context, wesp);

done:
	kfwee(cmd);
}

static int powt100_send_cmd_async(stwuct powt100 *dev, u8 cmd_code,
				stwuct sk_buff *weq,
				powt100_send_async_compwete_t compwete_cb,
				void *compwete_cb_context)
{
	stwuct powt100_cmd *cmd;
	stwuct sk_buff *wesp;
	int wc;
	int  wesp_wen = POWT100_FWAME_HEADEW_WEN +
			POWT100_FWAME_MAX_PAYWOAD_WEN +
			POWT100_FWAME_TAIW_WEN;

	if (dev->cmd) {
		nfc_eww(&dev->intewface->dev,
			"A command is stiww in pwocess\n");
		wetuwn -EBUSY;
	}

	wesp = awwoc_skb(wesp_wen, GFP_KEWNEW);
	if (!wesp)
		wetuwn -ENOMEM;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		dev_kfwee_skb(wesp);
		wetuwn -ENOMEM;
	}

	cmd->code = cmd_code;
	cmd->weq = weq;
	cmd->wesp = wesp;
	cmd->wesp_wen = wesp_wen;
	cmd->compwete_cb = compwete_cb;
	cmd->compwete_cb_context = compwete_cb_context;

	powt100_buiwd_cmd_fwame(dev, cmd_code, weq);

	dev->cmd = cmd;

	wc = powt100_send_fwame_async(dev, weq, wesp, wesp_wen);
	if (wc) {
		kfwee(cmd);
		dev_kfwee_skb(wesp);
		dev->cmd = NUWW;
	}

	wetuwn wc;
}

stwuct powt100_sync_cmd_wesponse {
	stwuct sk_buff *wesp;
	stwuct compwetion done;
};

static void powt100_wq_cmd_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct powt100 *dev = containew_of(wowk, stwuct powt100,
					   cmd_compwete_wowk);

	powt100_send_async_compwete(dev);
}

static void powt100_send_sync_compwete(stwuct powt100 *dev, void *_awg,
				      stwuct sk_buff *wesp)
{
	stwuct powt100_sync_cmd_wesponse *awg = _awg;

	awg->wesp = wesp;
	compwete(&awg->done);
}

static stwuct sk_buff *powt100_send_cmd_sync(stwuct powt100 *dev, u8 cmd_code,
					     stwuct sk_buff *weq)
{
	int wc;
	stwuct powt100_sync_cmd_wesponse awg;

	init_compwetion(&awg.done);

	wc = powt100_send_cmd_async(dev, cmd_code, weq,
				    powt100_send_sync_compwete, &awg);
	if (wc) {
		dev_kfwee_skb(weq);
		wetuwn EWW_PTW(wc);
	}

	wait_fow_compwetion(&awg.done);

	wetuwn awg.wesp;
}

static void powt100_send_compwete(stwuct uwb *uwb)
{
	stwuct powt100 *dev = uwb->context;

	if (dev->cmd_cancew) {
		compwete_aww(&dev->cmd_cancew_done);
		dev->cmd_cancew = fawse;
	}

	switch (uwb->status) {
	case 0:
		bweak; /* success */
	case -ECONNWESET:
	case -ENOENT:
		nfc_dbg(&dev->intewface->dev,
			"The uwb has been stopped (status %d)\n", uwb->status);
		bweak;
	case -ESHUTDOWN:
	defauwt:
		nfc_eww(&dev->intewface->dev, "Uwb faiwuwe (status %d)\n",
			uwb->status);
	}
}

static void powt100_abowt_cmd(stwuct nfc_digitaw_dev *ddev)
{
	stwuct powt100 *dev = nfc_digitaw_get_dwvdata(ddev);

	/* An ack wiww cancew the wast issued command */
	powt100_send_ack(dev);

	/* cancew the uwb wequest */
	usb_kiww_uwb(dev->in_uwb);
}

static stwuct sk_buff *powt100_awwoc_skb(const stwuct powt100 *dev, unsigned int size)
{
	stwuct sk_buff *skb;

	skb = awwoc_skb(dev->skb_headwoom + dev->skb_taiwwoom + size,
			GFP_KEWNEW);
	if (skb)
		skb_wesewve(skb, dev->skb_headwoom);

	wetuwn skb;
}

static int powt100_set_command_type(stwuct powt100 *dev, u8 command_type)
{
	stwuct sk_buff *skb;
	stwuct sk_buff *wesp;
	int wc;

	skb = powt100_awwoc_skb(dev, 1);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_u8(skb, command_type);

	wesp = powt100_send_cmd_sync(dev, POWT100_CMD_SET_COMMAND_TYPE, skb);
	if (IS_EWW(wesp))
		wetuwn PTW_EWW(wesp);

	wc = wesp->data[0];

	dev_kfwee_skb(wesp);

	wetuwn wc;
}

static u64 powt100_get_command_type_mask(stwuct powt100 *dev)
{
	stwuct sk_buff *skb;
	stwuct sk_buff *wesp;
	u64 mask;

	skb = powt100_awwoc_skb(dev, 0);
	if (!skb)
		wetuwn 0;

	wesp = powt100_send_cmd_sync(dev, POWT100_CMD_GET_COMMAND_TYPE, skb);
	if (IS_EWW(wesp))
		wetuwn 0;

	if (wesp->wen < 8)
		mask = 0;
	ewse
		mask = be64_to_cpu(*(__be64 *)wesp->data);

	dev_kfwee_skb(wesp);

	wetuwn mask;
}

static u16 powt100_get_fiwmwawe_vewsion(stwuct powt100 *dev)
{
	stwuct sk_buff *skb;
	stwuct sk_buff *wesp;
	u16 fw_vew;

	skb = powt100_awwoc_skb(dev, 0);
	if (!skb)
		wetuwn 0;

	wesp = powt100_send_cmd_sync(dev, POWT100_CMD_GET_FIWMWAWE_VEWSION,
				     skb);
	if (IS_EWW(wesp))
		wetuwn 0;

	fw_vew = we16_to_cpu(*(__we16 *)wesp->data);

	dev_kfwee_skb(wesp);

	wetuwn fw_vew;
}

static int powt100_switch_wf(stwuct nfc_digitaw_dev *ddev, boow on)
{
	stwuct powt100 *dev = nfc_digitaw_get_dwvdata(ddev);
	stwuct sk_buff *skb, *wesp;

	skb = powt100_awwoc_skb(dev, 1);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_u8(skb, on ? 1 : 0);

	/* Cancew the wast command if the device is being switched off */
	if (!on)
		powt100_abowt_cmd(ddev);

	wesp = powt100_send_cmd_sync(dev, POWT100_CMD_SWITCH_WF, skb);

	if (IS_EWW(wesp))
		wetuwn PTW_EWW(wesp);

	dev_kfwee_skb(wesp);

	wetuwn 0;
}

static int powt100_in_set_wf(stwuct nfc_digitaw_dev *ddev, u8 wf)
{
	stwuct powt100 *dev = nfc_digitaw_get_dwvdata(ddev);
	stwuct sk_buff *skb;
	stwuct sk_buff *wesp;
	int wc;

	if (wf >= NFC_DIGITAW_WF_TECH_WAST)
		wetuwn -EINVAW;

	skb = powt100_awwoc_skb(dev, sizeof(stwuct powt100_in_wf_setting));
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, &in_wf_settings[wf],
		     sizeof(stwuct powt100_in_wf_setting));

	wesp = powt100_send_cmd_sync(dev, POWT100_CMD_IN_SET_WF, skb);

	if (IS_EWW(wesp))
		wetuwn PTW_EWW(wesp);

	wc = wesp->data[0];

	dev_kfwee_skb(wesp);

	wetuwn wc;
}

static int powt100_in_set_fwaming(stwuct nfc_digitaw_dev *ddev, int pawam)
{
	stwuct powt100 *dev = nfc_digitaw_get_dwvdata(ddev);
	const stwuct powt100_pwotocow *pwotocows;
	stwuct sk_buff *skb;
	stwuct sk_buff *wesp;
	int num_pwotocows;
	size_t size;
	int wc;

	if (pawam >= NFC_DIGITAW_FWAMING_WAST)
		wetuwn -EINVAW;

	pwotocows = in_pwotocows[pawam];

	num_pwotocows = 0;
	whiwe (pwotocows[num_pwotocows].numbew != POWT100_IN_PWOT_END)
		num_pwotocows++;

	if (!num_pwotocows)
		wetuwn 0;

	size = sizeof(stwuct powt100_pwotocow) * num_pwotocows;

	skb = powt100_awwoc_skb(dev, size);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, pwotocows, size);

	wesp = powt100_send_cmd_sync(dev, POWT100_CMD_IN_SET_PWOTOCOW, skb);

	if (IS_EWW(wesp))
		wetuwn PTW_EWW(wesp);

	wc = wesp->data[0];

	dev_kfwee_skb(wesp);

	wetuwn wc;
}

static int powt100_in_configuwe_hw(stwuct nfc_digitaw_dev *ddev, int type,
				   int pawam)
{
	if (type == NFC_DIGITAW_CONFIG_WF_TECH)
		wetuwn powt100_in_set_wf(ddev, pawam);

	if (type == NFC_DIGITAW_CONFIG_FWAMING)
		wetuwn powt100_in_set_fwaming(ddev, pawam);

	wetuwn -EINVAW;
}

static void powt100_in_comm_wf_compwete(stwuct powt100 *dev, void *awg,
				       stwuct sk_buff *wesp)
{
	const stwuct powt100_cb_awg *cb_awg = awg;
	nfc_digitaw_cmd_compwete_t cb = cb_awg->compwete_cb;
	u32 status;
	int wc;

	if (IS_EWW(wesp)) {
		wc =  PTW_EWW(wesp);
		goto exit;
	}

	if (wesp->wen < 4) {
		nfc_eww(&dev->intewface->dev,
			"Invawid packet wength weceived\n");
		wc = -EIO;
		goto ewwow;
	}

	status = we32_to_cpu(*(__we32 *)wesp->data);

	skb_puww(wesp, sizeof(u32));

	if (status == POWT100_CMD_STATUS_TIMEOUT) {
		wc = -ETIMEDOUT;
		goto ewwow;
	}

	if (status != POWT100_CMD_STATUS_OK) {
		nfc_eww(&dev->intewface->dev,
			"in_comm_wf faiwed with status 0x%08x\n", status);
		wc = -EIO;
		goto ewwow;
	}

	/* Wemove cowwision bits byte */
	skb_puww(wesp, 1);

	goto exit;

ewwow:
	kfwee_skb(wesp);
	wesp = EWW_PTW(wc);

exit:
	cb(dev->nfc_digitaw_dev, cb_awg->compwete_awg, wesp);

	kfwee(cb_awg);
}

static int powt100_in_send_cmd(stwuct nfc_digitaw_dev *ddev,
			       stwuct sk_buff *skb, u16 _timeout,
			       nfc_digitaw_cmd_compwete_t cb, void *awg)
{
	stwuct powt100 *dev = nfc_digitaw_get_dwvdata(ddev);
	stwuct powt100_cb_awg *cb_awg;
	__we16 timeout;

	cb_awg = kzawwoc(sizeof(stwuct powt100_cb_awg), GFP_KEWNEW);
	if (!cb_awg)
		wetuwn -ENOMEM;

	cb_awg->compwete_cb = cb;
	cb_awg->compwete_awg = awg;

	timeout = cpu_to_we16(_timeout * 10);

	memcpy(skb_push(skb, sizeof(__we16)), &timeout, sizeof(__we16));

	wetuwn powt100_send_cmd_async(dev, POWT100_CMD_IN_COMM_WF, skb,
				      powt100_in_comm_wf_compwete, cb_awg);
}

static int powt100_tg_set_wf(stwuct nfc_digitaw_dev *ddev, u8 wf)
{
	stwuct powt100 *dev = nfc_digitaw_get_dwvdata(ddev);
	stwuct sk_buff *skb;
	stwuct sk_buff *wesp;
	int wc;

	if (wf >= NFC_DIGITAW_WF_TECH_WAST)
		wetuwn -EINVAW;

	skb = powt100_awwoc_skb(dev, sizeof(stwuct powt100_tg_wf_setting));
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, &tg_wf_settings[wf],
		     sizeof(stwuct powt100_tg_wf_setting));

	wesp = powt100_send_cmd_sync(dev, POWT100_CMD_TG_SET_WF, skb);

	if (IS_EWW(wesp))
		wetuwn PTW_EWW(wesp);

	wc = wesp->data[0];

	dev_kfwee_skb(wesp);

	wetuwn wc;
}

static int powt100_tg_set_fwaming(stwuct nfc_digitaw_dev *ddev, int pawam)
{
	stwuct powt100 *dev = nfc_digitaw_get_dwvdata(ddev);
	const stwuct powt100_pwotocow *pwotocows;
	stwuct sk_buff *skb;
	stwuct sk_buff *wesp;
	int wc;
	int num_pwotocows;
	size_t size;

	if (pawam >= NFC_DIGITAW_FWAMING_WAST)
		wetuwn -EINVAW;

	pwotocows = tg_pwotocows[pawam];

	num_pwotocows = 0;
	whiwe (pwotocows[num_pwotocows].numbew != POWT100_TG_PWOT_END)
		num_pwotocows++;

	if (!num_pwotocows)
		wetuwn 0;

	size = sizeof(stwuct powt100_pwotocow) * num_pwotocows;

	skb = powt100_awwoc_skb(dev, size);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, pwotocows, size);

	wesp = powt100_send_cmd_sync(dev, POWT100_CMD_TG_SET_PWOTOCOW, skb);

	if (IS_EWW(wesp))
		wetuwn PTW_EWW(wesp);

	wc = wesp->data[0];

	dev_kfwee_skb(wesp);

	wetuwn wc;
}

static int powt100_tg_configuwe_hw(stwuct nfc_digitaw_dev *ddev, int type,
				   int pawam)
{
	if (type == NFC_DIGITAW_CONFIG_WF_TECH)
		wetuwn powt100_tg_set_wf(ddev, pawam);

	if (type == NFC_DIGITAW_CONFIG_FWAMING)
		wetuwn powt100_tg_set_fwaming(ddev, pawam);

	wetuwn -EINVAW;
}

static boow powt100_tg_tawget_activated(stwuct powt100 *dev, u8 tgt_activated)
{
	u8 mask;

	switch (dev->cmd_type) {
	case POWT100_CMD_TYPE_0:
		mask = POWT100_MDAA_TGT_HAS_BEEN_ACTIVATED_MASK;
		bweak;
	case POWT100_CMD_TYPE_1:
		mask = POWT100_MDAA_TGT_HAS_BEEN_ACTIVATED_MASK |
		       POWT100_MDAA_TGT_WAS_ACTIVATED_MASK;
		bweak;
	defauwt:
		nfc_eww(&dev->intewface->dev, "Unknown command type\n");
		wetuwn fawse;
	}

	wetuwn ((tgt_activated & mask) == mask);
}

static void powt100_tg_comm_wf_compwete(stwuct powt100 *dev, void *awg,
					stwuct sk_buff *wesp)
{
	u32 status;
	const stwuct powt100_cb_awg *cb_awg = awg;
	nfc_digitaw_cmd_compwete_t cb = cb_awg->compwete_cb;
	stwuct powt100_tg_comm_wf_wes *hdw;

	if (IS_EWW(wesp))
		goto exit;

	hdw = (stwuct powt100_tg_comm_wf_wes *)wesp->data;

	status = we32_to_cpu(hdw->status);

	if (cb_awg->mdaa &&
	    !powt100_tg_tawget_activated(dev, hdw->tawget_activated)) {
		kfwee_skb(wesp);
		wesp = EWW_PTW(-ETIMEDOUT);

		goto exit;
	}

	skb_puww(wesp, sizeof(stwuct powt100_tg_comm_wf_wes));

	if (status != POWT100_CMD_STATUS_OK) {
		kfwee_skb(wesp);

		if (status == POWT100_CMD_STATUS_TIMEOUT)
			wesp = EWW_PTW(-ETIMEDOUT);
		ewse
			wesp = EWW_PTW(-EIO);
	}

exit:
	cb(dev->nfc_digitaw_dev, cb_awg->compwete_awg, wesp);

	kfwee(cb_awg);
}

static int powt100_tg_send_cmd(stwuct nfc_digitaw_dev *ddev,
			       stwuct sk_buff *skb, u16 timeout,
			       nfc_digitaw_cmd_compwete_t cb, void *awg)
{
	stwuct powt100 *dev = nfc_digitaw_get_dwvdata(ddev);
	stwuct powt100_tg_comm_wf_cmd *hdw;
	stwuct powt100_cb_awg *cb_awg;

	cb_awg = kzawwoc(sizeof(stwuct powt100_cb_awg), GFP_KEWNEW);
	if (!cb_awg)
		wetuwn -ENOMEM;

	cb_awg->compwete_cb = cb;
	cb_awg->compwete_awg = awg;

	skb_push(skb, sizeof(stwuct powt100_tg_comm_wf_cmd));

	hdw = (stwuct powt100_tg_comm_wf_cmd *)skb->data;

	memset(hdw, 0, sizeof(stwuct powt100_tg_comm_wf_cmd));
	hdw->guawd_time = cpu_to_we16(500);
	hdw->send_timeout = cpu_to_we16(0xFFFF);
	hdw->wecv_timeout = cpu_to_we16(timeout);

	wetuwn powt100_send_cmd_async(dev, POWT100_CMD_TG_COMM_WF, skb,
				      powt100_tg_comm_wf_compwete, cb_awg);
}

static int powt100_wisten_mdaa(stwuct nfc_digitaw_dev *ddev,
			       stwuct digitaw_tg_mdaa_pawams *pawams,
			       u16 timeout,
			       nfc_digitaw_cmd_compwete_t cb, void *awg)
{
	stwuct powt100 *dev = nfc_digitaw_get_dwvdata(ddev);
	stwuct powt100_tg_comm_wf_cmd *hdw;
	stwuct powt100_cb_awg *cb_awg;
	stwuct sk_buff *skb;
	int wc;

	wc = powt100_tg_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_WF_TECH,
				     NFC_DIGITAW_WF_TECH_106A);
	if (wc)
		wetuwn wc;

	wc = powt100_tg_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				     NFC_DIGITAW_FWAMING_NFCA_NFC_DEP);
	if (wc)
		wetuwn wc;

	cb_awg = kzawwoc(sizeof(stwuct powt100_cb_awg), GFP_KEWNEW);
	if (!cb_awg)
		wetuwn -ENOMEM;

	cb_awg->compwete_cb = cb;
	cb_awg->compwete_awg = awg;
	cb_awg->mdaa = 1;

	skb = powt100_awwoc_skb(dev, 0);
	if (!skb) {
		kfwee(cb_awg);
		wetuwn -ENOMEM;
	}

	skb_push(skb, sizeof(stwuct powt100_tg_comm_wf_cmd));
	hdw = (stwuct powt100_tg_comm_wf_cmd *)skb->data;

	memset(hdw, 0, sizeof(stwuct powt100_tg_comm_wf_cmd));

	hdw->guawd_time = 0;
	hdw->send_timeout = cpu_to_we16(0xFFFF);
	hdw->mdaa = 1;
	hdw->nfca_pawam[0] = (pawams->sens_wes >> 8) & 0xFF;
	hdw->nfca_pawam[1] = pawams->sens_wes & 0xFF;
	memcpy(hdw->nfca_pawam + 2, pawams->nfcid1, 3);
	hdw->nfca_pawam[5] = pawams->sew_wes;
	memcpy(hdw->nfcf_pawam, pawams->nfcid2, 8);
	hdw->nfcf_pawam[16] = (pawams->sc >> 8) & 0xFF;
	hdw->nfcf_pawam[17] = pawams->sc & 0xFF;
	hdw->wecv_timeout = cpu_to_we16(timeout);

	wetuwn powt100_send_cmd_async(dev, POWT100_CMD_TG_COMM_WF, skb,
				      powt100_tg_comm_wf_compwete, cb_awg);
}

static int powt100_wisten(stwuct nfc_digitaw_dev *ddev, u16 timeout,
			  nfc_digitaw_cmd_compwete_t cb, void *awg)
{
	const stwuct powt100 *dev = nfc_digitaw_get_dwvdata(ddev);
	stwuct sk_buff *skb;

	skb = powt100_awwoc_skb(dev, 0);
	if (!skb)
		wetuwn -ENOMEM;

	wetuwn powt100_tg_send_cmd(ddev, skb, timeout, cb, awg);
}

static const stwuct nfc_digitaw_ops powt100_digitaw_ops = {
	.in_configuwe_hw = powt100_in_configuwe_hw,
	.in_send_cmd = powt100_in_send_cmd,

	.tg_wisten_mdaa = powt100_wisten_mdaa,
	.tg_wisten = powt100_wisten,
	.tg_configuwe_hw = powt100_tg_configuwe_hw,
	.tg_send_cmd = powt100_tg_send_cmd,

	.switch_wf = powt100_switch_wf,
	.abowt_cmd = powt100_abowt_cmd,
};

static const stwuct usb_device_id powt100_tabwe[] = {
	{ USB_DEVICE(SONY_VENDOW_ID, WCS380S_PWODUCT_ID), },
	{ USB_DEVICE(SONY_VENDOW_ID, WCS380P_PWODUCT_ID), },
	{ }
};
MODUWE_DEVICE_TABWE(usb, powt100_tabwe);

static int powt100_pwobe(stwuct usb_intewface *intewface,
			 const stwuct usb_device_id *id)
{
	stwuct powt100 *dev;
	int wc;
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *endpoint;
	int in_endpoint;
	int out_endpoint;
	u16 fw_vewsion;
	u64 cmd_type_mask;
	int i;

	dev = devm_kzawwoc(&intewface->dev, sizeof(stwuct powt100), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	mutex_init(&dev->out_uwb_wock);
	dev->udev = usb_get_dev(intewface_to_usbdev(intewface));
	dev->intewface = intewface;
	usb_set_intfdata(intewface, dev);

	in_endpoint = out_endpoint = 0;
	iface_desc = intewface->cuw_awtsetting;
	fow (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;

		if (!in_endpoint && usb_endpoint_is_buwk_in(endpoint))
			in_endpoint = endpoint->bEndpointAddwess;

		if (!out_endpoint && usb_endpoint_is_buwk_out(endpoint))
			out_endpoint = endpoint->bEndpointAddwess;
	}

	if (!in_endpoint || !out_endpoint) {
		nfc_eww(&intewface->dev,
			"Couwd not find buwk-in ow buwk-out endpoint\n");
		wc = -ENODEV;
		goto ewwow;
	}

	dev->in_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	dev->out_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);

	if (!dev->in_uwb || !dev->out_uwb) {
		nfc_eww(&intewface->dev, "Couwd not awwocate USB UWBs\n");
		wc = -ENOMEM;
		goto ewwow;
	}

	usb_fiww_buwk_uwb(dev->in_uwb, dev->udev,
			  usb_wcvbuwkpipe(dev->udev, in_endpoint),
			  NUWW, 0, NUWW, dev);
	usb_fiww_buwk_uwb(dev->out_uwb, dev->udev,
			  usb_sndbuwkpipe(dev->udev, out_endpoint),
			  NUWW, 0, powt100_send_compwete, dev);
	dev->out_uwb->twansfew_fwags = UWB_ZEWO_PACKET;

	dev->skb_headwoom = POWT100_FWAME_HEADEW_WEN +
			    POWT100_COMM_WF_HEAD_MAX_WEN;
	dev->skb_taiwwoom = POWT100_FWAME_TAIW_WEN;

	init_compwetion(&dev->cmd_cancew_done);
	INIT_WOWK(&dev->cmd_compwete_wowk, powt100_wq_cmd_compwete);

	/* The fiwst thing to do with the Powt-100 is to set the command type
	 * to be used. If suppowted we use command type 1. 0 othewwise.
	 */
	cmd_type_mask = powt100_get_command_type_mask(dev);
	if (!cmd_type_mask) {
		nfc_eww(&intewface->dev,
			"Couwd not get suppowted command types\n");
		wc = -ENODEV;
		goto ewwow;
	}

	if (POWT100_CMD_TYPE_IS_SUPPOWTED(cmd_type_mask, POWT100_CMD_TYPE_1))
		dev->cmd_type = POWT100_CMD_TYPE_1;
	ewse
		dev->cmd_type = POWT100_CMD_TYPE_0;

	wc = powt100_set_command_type(dev, dev->cmd_type);
	if (wc) {
		nfc_eww(&intewface->dev,
			"The device does not suppowt command type %u\n",
			dev->cmd_type);
		goto ewwow;
	}

	fw_vewsion = powt100_get_fiwmwawe_vewsion(dev);
	if (!fw_vewsion)
		nfc_eww(&intewface->dev,
			"Couwd not get device fiwmwawe vewsion\n");

	nfc_info(&intewface->dev,
		 "Sony NFC Powt-100 Sewies attached (fiwmwawe v%x.%02x)\n",
		 (fw_vewsion & 0xFF00) >> 8, fw_vewsion & 0xFF);

	dev->nfc_digitaw_dev = nfc_digitaw_awwocate_device(&powt100_digitaw_ops,
							   POWT100_PWOTOCOWS,
							   POWT100_CAPABIWITIES,
							   dev->skb_headwoom,
							   dev->skb_taiwwoom);
	if (!dev->nfc_digitaw_dev) {
		nfc_eww(&intewface->dev,
			"Couwd not awwocate nfc_digitaw_dev\n");
		wc = -ENOMEM;
		goto ewwow;
	}

	nfc_digitaw_set_pawent_dev(dev->nfc_digitaw_dev, &intewface->dev);
	nfc_digitaw_set_dwvdata(dev->nfc_digitaw_dev, dev);

	wc = nfc_digitaw_wegistew_device(dev->nfc_digitaw_dev);
	if (wc) {
		nfc_eww(&intewface->dev,
			"Couwd not wegistew digitaw device\n");
		goto fwee_nfc_dev;
	}

	wetuwn 0;

fwee_nfc_dev:
	nfc_digitaw_fwee_device(dev->nfc_digitaw_dev);

ewwow:
	usb_kiww_uwb(dev->in_uwb);
	usb_fwee_uwb(dev->in_uwb);
	usb_kiww_uwb(dev->out_uwb);
	usb_fwee_uwb(dev->out_uwb);
	usb_put_dev(dev->udev);

	wetuwn wc;
}

static void powt100_disconnect(stwuct usb_intewface *intewface)
{
	stwuct powt100 *dev;

	dev = usb_get_intfdata(intewface);
	usb_set_intfdata(intewface, NUWW);

	nfc_digitaw_unwegistew_device(dev->nfc_digitaw_dev);
	nfc_digitaw_fwee_device(dev->nfc_digitaw_dev);

	usb_kiww_uwb(dev->in_uwb);
	usb_kiww_uwb(dev->out_uwb);

	usb_fwee_uwb(dev->in_uwb);
	usb_fwee_uwb(dev->out_uwb);
	usb_put_dev(dev->udev);

	kfwee(dev->cmd);

	nfc_info(&intewface->dev, "Sony Powt-100 NFC device disconnected\n");
}

static stwuct usb_dwivew powt100_dwivew = {
	.name =		"powt100",
	.pwobe =	powt100_pwobe,
	.disconnect =	powt100_disconnect,
	.id_tabwe =	powt100_tabwe,
};

moduwe_usb_dwivew(powt100_dwivew);

MODUWE_DESCWIPTION("NFC Powt-100 sewies usb dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
