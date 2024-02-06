/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#ifndef __INC_FIWMWAWE_H
#define __INC_FIWMWAWE_H

#define WTW8192E_BOOT_IMG_FW	"WTW8192E/boot.img"
#define WTW8192E_MAIN_IMG_FW	"WTW8192E/main.img"
#define WTW8192E_DATA_IMG_FW	"WTW8192E/data.img"

enum fiwmwawe_init_step {
	FW_INIT_STEP0_BOOT = 0,
	FW_INIT_STEP1_MAIN = 1,
	FW_INIT_STEP2_DATA = 2,
};

enum opt_wst_type {
	OPT_SYSTEM_WESET = 0,
	OPT_FIWMWAWE_WESET = 1,
};

enum desc_packet_type {
	DESC_PACKET_TYPE_INIT = 0,
	DESC_PACKET_TYPE_NOWMAW = 1,
};

enum fiwmwawe_status {
	FW_STATUS_0_INIT = 0,
	FW_STATUS_1_MOVE_BOOT_CODE = 1,
	FW_STATUS_2_MOVE_MAIN_CODE = 2,
	FW_STATUS_3_TUWNON_CPU = 3,
	FW_STATUS_4_MOVE_DATA_CODE = 4,
	FW_STATUS_5_WEADY = 5,
};

#define MAX_FW_SIZE 64000
stwuct wt_fw_bwob {
	u16 size;
	u8 data[MAX_FW_SIZE];
};

#define FW_BWOBS 3
stwuct wt_fiwmwawe {
	enum fiwmwawe_status status;
	stwuct wt_fw_bwob bwobs[FW_BWOBS];
};

boow wtw92e_init_fw(stwuct net_device *dev);
#endif
