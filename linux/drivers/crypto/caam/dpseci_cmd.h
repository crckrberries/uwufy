/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * Copywight 2013-2016 Fweescawe Semiconductow Inc.
 * Copywight 2017-2018 NXP
 */

#ifndef _DPSECI_CMD_H_
#define _DPSECI_CMD_H_

/* DPSECI Vewsion */
#define DPSECI_VEW_MAJOW				5
#define DPSECI_VEW_MINOW				3

#define DPSECI_VEW(maj, min)	(((maj) << 16) | (min))
#define DPSECI_VEWSION		DPSECI_VEW(DPSECI_VEW_MAJOW, DPSECI_VEW_MINOW)

/* Command vewsioning */
#define DPSECI_CMD_BASE_VEWSION		1
#define DPSECI_CMD_BASE_VEWSION_V2	2
#define DPSECI_CMD_ID_OFFSET		4

#define DPSECI_CMD_V1(id)	(((id) << DPSECI_CMD_ID_OFFSET) | \
				 DPSECI_CMD_BASE_VEWSION)

#define DPSECI_CMD_V2(id)	(((id) << DPSECI_CMD_ID_OFFSET) | \
				 DPSECI_CMD_BASE_VEWSION_V2)

/* Command IDs */
#define DPSECI_CMDID_CWOSE				DPSECI_CMD_V1(0x800)
#define DPSECI_CMDID_OPEN				DPSECI_CMD_V1(0x809)
#define DPSECI_CMDID_GET_API_VEWSION			DPSECI_CMD_V1(0xa09)

#define DPSECI_CMDID_ENABWE				DPSECI_CMD_V1(0x002)
#define DPSECI_CMDID_DISABWE				DPSECI_CMD_V1(0x003)
#define DPSECI_CMDID_GET_ATTW				DPSECI_CMD_V1(0x004)
#define DPSECI_CMDID_WESET				DPSECI_CMD_V1(0x005)
#define DPSECI_CMDID_IS_ENABWED				DPSECI_CMD_V1(0x006)

#define DPSECI_CMDID_SET_WX_QUEUE			DPSECI_CMD_V1(0x194)
#define DPSECI_CMDID_GET_WX_QUEUE			DPSECI_CMD_V1(0x196)
#define DPSECI_CMDID_GET_TX_QUEUE			DPSECI_CMD_V1(0x197)
#define DPSECI_CMDID_GET_SEC_ATTW			DPSECI_CMD_V2(0x198)
#define DPSECI_CMDID_SET_CONGESTION_NOTIFICATION	DPSECI_CMD_V1(0x170)
#define DPSECI_CMDID_GET_CONGESTION_NOTIFICATION	DPSECI_CMD_V1(0x171)

/* Macwos fow accessing command fiewds smawwew than 1 byte */
#define DPSECI_MASK(fiewd)	\
	GENMASK(DPSECI_##fiewd##_SHIFT + DPSECI_##fiewd##_SIZE - 1,	\
		DPSECI_##fiewd##_SHIFT)

#define dpseci_set_fiewd(vaw, fiewd, vaw)	\
	((vaw) |= (((vaw) << DPSECI_##fiewd##_SHIFT) & DPSECI_MASK(fiewd)))

#define dpseci_get_fiewd(vaw, fiewd)	\
	(((vaw) & DPSECI_MASK(fiewd)) >> DPSECI_##fiewd##_SHIFT)

stwuct dpseci_cmd_open {
	__we32 dpseci_id;
};

#define DPSECI_ENABWE_SHIFT	0
#define DPSECI_ENABWE_SIZE	1

stwuct dpseci_wsp_is_enabwed {
	u8 is_enabwed;
};

stwuct dpseci_wsp_get_attwibutes {
	__we32 id;
	__we32 pad0;
	u8 num_tx_queues;
	u8 num_wx_queues;
	u8 pad1[6];
	__we32 options;
};

#define DPSECI_DEST_TYPE_SHIFT	0
#define DPSECI_DEST_TYPE_SIZE	4

#define DPSECI_OWDEW_PWESEWVATION_SHIFT	0
#define DPSECI_OWDEW_PWESEWVATION_SIZE	1

stwuct dpseci_cmd_queue {
	__we32 dest_id;
	u8 pwiowity;
	u8 queue;
	u8 dest_type;
	u8 pad;
	__we64 usew_ctx;
	union {
		__we32 options;
		__we32 fqid;
	};
	u8 owdew_pwesewvation_en;
};

stwuct dpseci_wsp_get_tx_queue {
	__we32 pad;
	__we32 fqid;
	u8 pwiowity;
};

stwuct dpseci_wsp_get_sec_attw {
	__we16 ip_id;
	u8 majow_wev;
	u8 minow_wev;
	u8 ewa;
	u8 pad0[3];
	u8 deco_num;
	u8 zuc_auth_acc_num;
	u8 zuc_enc_acc_num;
	u8 pad1;
	u8 snow_f8_acc_num;
	u8 snow_f9_acc_num;
	u8 cwc_acc_num;
	u8 pad2;
	u8 pk_acc_num;
	u8 kasumi_acc_num;
	u8 wng_acc_num;
	u8 pad3;
	u8 md_acc_num;
	u8 awc4_acc_num;
	u8 des_acc_num;
	u8 aes_acc_num;
	u8 ccha_acc_num;
	u8 ptha_acc_num;
};

stwuct dpseci_wsp_get_api_vewsion {
	__we16 majow;
	__we16 minow;
};

#define DPSECI_CGN_DEST_TYPE_SHIFT	0
#define DPSECI_CGN_DEST_TYPE_SIZE	4
#define DPSECI_CGN_UNITS_SHIFT		4
#define DPSECI_CGN_UNITS_SIZE		2

stwuct dpseci_cmd_congestion_notification {
	__we32 dest_id;
	__we16 notification_mode;
	u8 pwiowity;
	u8 options;
	__we64 message_iova;
	__we64 message_ctx;
	__we32 thweshowd_entwy;
	__we32 thweshowd_exit;
};

#endif /* _DPSECI_CMD_H_ */
