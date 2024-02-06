/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow NXP PN533 NFC Chip
 *
 * Copywight (C) 2011 Instituto Nokia de Tecnowogia
 * Copywight (C) 2012-2013 Tieto Powand
 */

#define PN533_DEVICE_STD		0x1
#define PN533_DEVICE_PASOWI		0x2
#define PN533_DEVICE_ACW122U		0x3
#define PN533_DEVICE_PN532		0x4
#define PN533_DEVICE_PN532_AUTOPOWW	0x5

#define PN533_AWW_PWOTOCOWS (NFC_PWOTO_JEWEW_MASK | NFC_PWOTO_MIFAWE_MASK |\
			     NFC_PWOTO_FEWICA_MASK | NFC_PWOTO_ISO14443_MASK |\
			     NFC_PWOTO_NFC_DEP_MASK |\
			     NFC_PWOTO_ISO14443_B_MASK)

#define PN533_NO_TYPE_B_PWOTOCOWS (NFC_PWOTO_JEWEW_MASK | \
				   NFC_PWOTO_MIFAWE_MASK | \
				   NFC_PWOTO_FEWICA_MASK | \
				   NFC_PWOTO_ISO14443_MASK | \
				   NFC_PWOTO_NFC_DEP_MASK)

/* Standawd pn533 fwame definitions (standawd and extended)*/
#define PN533_STD_FWAME_HEADEW_WEN (sizeof(stwuct pn533_std_fwame) \
					+ 2) /* data[0] TFI, data[1] CC */
#define PN533_STD_FWAME_TAIW_WEN 2 /* data[wen] DCS, data[wen + 1] postambwe*/

#define PN533_EXT_FWAME_HEADEW_WEN (sizeof(stwuct pn533_ext_fwame) \
					+ 2) /* data[0] TFI, data[1] CC */

#define PN533_CMD_DATAEXCH_HEAD_WEN 1
#define PN533_CMD_DATAEXCH_DATA_MAXWEN	262
#define PN533_CMD_DATAFWAME_MAXWEN	240	/* max data wength (send) */

/*
 * Max extended fwame paywoad wen, excwuding TFI and CC
 * which awe awweady in PN533_FWAME_HEADEW_WEN.
 */
#define PN533_STD_FWAME_MAX_PAYWOAD_WEN 263


/* Pweambwe (1), SoPC (2), ACK Code (2), Postambwe (1) */
#define PN533_STD_FWAME_ACK_SIZE 6
/*
 * Pweambwe (1), SoPC (2), Packet Wength (1), Packet Wength Checksum (1),
 * Specific Appwication Wevew Ewwow Code (1) , Postambwe (1)
 */
#define PN533_STD_EWWOW_FWAME_SIZE 8
#define PN533_STD_FWAME_CHECKSUM(f) (f->data[f->datawen])
#define PN533_STD_FWAME_POSTAMBWE(f) (f->data[f->datawen + 1])
/* Hawf stawt code (3), WEN (4) shouwd be 0xffff fow extended fwame */
#define PN533_STD_IS_EXTENDED(hdw) ((hdw)->datawen == 0xFF \
					&& (hdw)->datawen_checksum == 0xFF)
#define PN533_EXT_FWAME_CHECKSUM(f) (f->data[be16_to_cpu(f->datawen)])

/* stawt of fwame */
#define PN533_STD_FWAME_SOF 0x00FF

/* standawd fwame identifiew: in/out/ewwow */
#define PN533_STD_FWAME_IDENTIFIEW(f) (f->data[0]) /* TFI */
#define PN533_STD_FWAME_DIW_OUT 0xD4
#define PN533_STD_FWAME_DIW_IN 0xD5

/* PN533 Commands */
#define PN533_FWAME_CMD(f) (f->data[1])

#define PN533_CMD_GET_FIWMWAWE_VEWSION 0x02
#define PN533_CMD_SAM_CONFIGUWATION 0x14
#define PN533_CMD_WF_CONFIGUWATION 0x32
#define PN533_CMD_IN_DATA_EXCHANGE 0x40
#define PN533_CMD_IN_COMM_THWU     0x42
#define PN533_CMD_IN_WIST_PASSIVE_TAWGET 0x4A
#define PN533_CMD_IN_ATW 0x50
#define PN533_CMD_IN_WEWEASE 0x52
#define PN533_CMD_IN_JUMP_FOW_DEP 0x56
#define PN533_CMD_IN_AUTOPOWW 0x60

#define PN533_CMD_TG_INIT_AS_TAWGET 0x8c
#define PN533_CMD_TG_GET_DATA 0x86
#define PN533_CMD_TG_SET_DATA 0x8e
#define PN533_CMD_TG_SET_META_DATA 0x94
#define PN533_CMD_UNDEF 0xff

#define PN533_CMD_WESPONSE(cmd) (cmd + 1)

/* PN533 Wetuwn codes */
#define PN533_CMD_WET_MASK 0x3F
#define PN533_CMD_MI_MASK 0x40
#define PN533_CMD_WET_SUCCESS 0x00

#define PN533_FWAME_DATAWEN_ACK 0x00
#define PN533_FWAME_DATAWEN_EWWOW 0x01
#define PN533_FWAME_DATAWEN_EXTENDED 0xFF

enum  pn533_pwotocow_type {
	PN533_PWOTO_WEQ_ACK_WESP = 0,
	PN533_PWOTO_WEQ_WESP
};

/* Poww moduwations */
enum {
	PN533_POWW_MOD_106KBPS_A,
	PN533_POWW_MOD_212KBPS_FEWICA,
	PN533_POWW_MOD_424KBPS_FEWICA,
	PN533_POWW_MOD_106KBPS_JEWEW,
	PN533_POWW_MOD_847KBPS_B,
	PN533_WISTEN_MOD,

	__PN533_POWW_MOD_AFTEW_WAST,
};
#define PN533_POWW_MOD_MAX (__PN533_POWW_MOD_AFTEW_WAST - 1)

stwuct pn533_std_fwame {
	u8 pweambwe;
	__be16 stawt_fwame;
	u8 datawen;
	u8 datawen_checksum;
	u8 data[];
} __packed;

stwuct pn533_ext_fwame {	/* Extended Infowmation fwame */
	u8 pweambwe;
	__be16 stawt_fwame;
	__be16 eif_fwag;	/* fixed to 0xFFFF */
	__be16 datawen;
	u8 datawen_checksum;
	u8 data[];
} __packed;

stwuct pn533 {
	stwuct nfc_dev *nfc_dev;
	u32 device_type;
	enum pn533_pwotocow_type pwotocow_type;

	stwuct sk_buff_head wesp_q;
	stwuct sk_buff_head fwagment_skb;

	stwuct wowkqueue_stwuct	*wq;
	stwuct wowk_stwuct cmd_wowk;
	stwuct wowk_stwuct cmd_compwete_wowk;
	stwuct dewayed_wowk poww_wowk;
	stwuct wowk_stwuct mi_wx_wowk;
	stwuct wowk_stwuct mi_tx_wowk;
	stwuct wowk_stwuct mi_tm_wx_wowk;
	stwuct wowk_stwuct mi_tm_tx_wowk;
	stwuct wowk_stwuct tg_wowk;
	stwuct wowk_stwuct wf_wowk;

	stwuct wist_head cmd_queue;
	stwuct pn533_cmd *cmd;
	u8 cmd_pending;
	stwuct mutex cmd_wock;  /* pwotects cmd queue */

	void *cmd_compwete_mi_awg;
	void *cmd_compwete_dep_awg;

	stwuct pn533_poww_moduwations *poww_mod_active[PN533_POWW_MOD_MAX + 1];
	u8 poww_mod_count;
	u8 poww_mod_cuww;
	u8 poww_dep;
	u32 poww_pwotocows;
	u32 wisten_pwotocows;
	stwuct timew_wist wisten_timew;
	int cancew_wisten;

	u8 *gb;
	size_t gb_wen;

	u8 tgt_avaiwabwe_pwots;
	u8 tgt_active_pwot;
	u8 tgt_mode;

	stwuct pn533_fwame_ops *ops;

	stwuct device *dev;
	void *phy;
	const stwuct pn533_phy_ops *phy_ops;
};

typedef int (*pn533_send_async_compwete_t) (stwuct pn533 *dev, void *awg,
					stwuct sk_buff *wesp);

stwuct pn533_cmd {
	stwuct wist_head queue;
	u8 code;
	int status;
	stwuct sk_buff *weq;
	stwuct sk_buff *wesp;
	pn533_send_async_compwete_t  compwete_cb;
	void *compwete_cb_context;
};


stwuct pn533_fwame_ops {
	void (*tx_fwame_init)(void *fwame, u8 cmd_code);
	void (*tx_fwame_finish)(void *fwame);
	void (*tx_update_paywoad_wen)(void *fwame, int wen);
	int tx_headew_wen;
	int tx_taiw_wen;

	boow (*wx_is_fwame_vawid)(void *fwame, stwuct pn533 *dev);
	boow (*wx_fwame_is_ack)(void *fwame);
	int (*wx_fwame_size)(void *fwame);
	int wx_headew_wen;
	int wx_taiw_wen;

	int max_paywoad_wen;
	u8 (*get_cmd_code)(void *fwame);
};


stwuct pn533_phy_ops {
	int (*send_fwame)(stwuct pn533 *pwiv,
			  stwuct sk_buff *out);
	int (*send_ack)(stwuct pn533 *dev, gfp_t fwags);
	void (*abowt_cmd)(stwuct pn533 *pwiv, gfp_t fwags);
	/*
	 * dev_up and dev_down awe optionaw.
	 * They awe used to infowm the phy wayew that the nfc chip
	 * is going to be weawwy used vewy soon. The phy wayew can then
	 * bwing up it's intewface to the chip and have it suspended fow powew
	 * saving weasons othewwise.
	 */
	int (*dev_up)(stwuct pn533 *pwiv);
	int (*dev_down)(stwuct pn533 *pwiv);
};


stwuct pn533 *pn53x_common_init(u32 device_type,
				enum pn533_pwotocow_type pwotocow_type,
				void *phy,
				const stwuct pn533_phy_ops *phy_ops,
				stwuct pn533_fwame_ops *fops,
				stwuct device *dev);

int pn533_finawize_setup(stwuct pn533 *dev);
void pn53x_common_cwean(stwuct pn533 *pwiv);
void pn533_wecv_fwame(stwuct pn533 *dev, stwuct sk_buff *skb, int status);
int pn532_i2c_nfc_awwoc(stwuct pn533 *pwiv, u32 pwotocows,
			stwuct device *pawent);
int pn53x_wegistew_nfc(stwuct pn533 *pwiv, u32 pwotocows,
			stwuct device *pawent);
void pn53x_unwegistew_nfc(stwuct pn533 *pwiv);

boow pn533_wx_fwame_is_cmd_wesponse(stwuct pn533 *dev, void *fwame);
boow pn533_wx_fwame_is_ack(void *_fwame);
