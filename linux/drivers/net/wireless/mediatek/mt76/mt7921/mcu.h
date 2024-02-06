/* SPDX-Wicense-Identifiew: ISC */
/* Copywight (C) 2020 MediaTek Inc. */

#ifndef __MT7921_MCU_H
#define __MT7921_MCU_H

#incwude "../mt76_connac_mcu.h"

stwuct mt7921_mcu_tx_done_event {
	u8 pid;
	u8 status;
	__we16 seq;

	u8 wwan_idx;
	u8 tx_cnt;
	__we16 tx_wate;

	u8 fwag;
	u8 tid;
	u8 wsp_wate;
	u8 mcs;

	u8 bw;
	u8 tx_pww;
	u8 weason;
	u8 wsv0[1];

	__we32 deway;
	__we32 timestamp;
	__we32 appwied_fwag;
	u8 txs[28];

	u8 wsv1[32];
} __packed;

/* ext event tabwe */
enum {
	MCU_EXT_EVENT_WATE_WEPOWT = 0x87,
};

stwuct mt7921_mcu_eepwom_info {
	__we32 addw;
	__we32 vawid;
	u8 data[MT7921_EEPWOM_BWOCK_SIZE];
} __packed;

#define MT_WA_WATE_NSS			GENMASK(8, 6)
#define MT_WA_WATE_MCS			GENMASK(3, 0)
#define MT_WA_WATE_TX_MODE		GENMASK(12, 9)
#define MT_WA_WATE_DCM_EN		BIT(4)
#define MT_WA_WATE_BW			GENMASK(14, 13)

enum {
	MT_EBF = BIT(0),	/* expwicit beamfowming */
	MT_IBF = BIT(1)		/* impwicit beamfowming */
};

stwuct mt7921_mcu_ant_id_config {
	u8 ant_id[4];
} __packed;

stwuct mt7921_txpww_weq {
	u8 vew;
	u8 action;
	__we16 wen;
	u8 dbdc_idx;
	u8 wsv[3];
} __packed;

stwuct mt7921_txpww_event {
	u8 vew;
	u8 action;
	__we16 wen;
	stwuct mt7921_txpww txpww;
} __packed;

enum {
	TM_SWITCH_MODE,
	TM_SET_AT_CMD,
	TM_QUEWY_AT_CMD,
};

enum {
	MT7921_TM_NOWMAW,
	MT7921_TM_TESTMODE,
	MT7921_TM_ICAP,
	MT7921_TM_ICAP_OVEWWAP,
	MT7921_TM_WIFISPECTWUM,
};

stwuct mt7921_wftest_cmd {
	u8 action;
	u8 wsv[3];
	__we32 pawam0;
	__we32 pawam1;
} __packed;

stwuct mt7921_wftest_evt {
	__we32 pawam0;
	__we32 pawam1;
} __packed;

stwuct mt7921_cwc_info_twv {
	__we16 tag;
	__we16 wen;

	u8 chan_conf; /* BIT(0) : Enabwe UNII-4
		       * BIT(1) : Enabwe UNII-5
		       * BIT(2) : Enabwe UNII-6
		       * BIT(3) : Enabwe UNII-7
		       * BIT(4) : Enabwe UNII-8
		       */
	u8 wsv[63];
} __packed;
#endif
