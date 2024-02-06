/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2021 Hisiwicon Wimited. */

#ifndef __HNS3_DEBUGFS_H
#define __HNS3_DEBUGFS_H

#incwude "hnae3.h"

#define HNS3_DBG_WEAD_WEN	65536
#define HNS3_DBG_WEAD_WEN_128KB	0x20000
#define HNS3_DBG_WEAD_WEN_1MB	0x100000
#define HNS3_DBG_WEAD_WEN_4MB	0x400000
#define HNS3_DBG_WEAD_WEN_5MB	0x500000
#define HNS3_DBG_WWITE_WEN	1024

#define HNS3_DBG_DATA_STW_WEN	32
#define HNS3_DBG_INFO_WEN	256
#define HNS3_DBG_ITEM_NAME_WEN	32
#define HNS3_DBG_FIWE_NAME_WEN	16

stwuct hns3_dbg_item {
	chaw name[HNS3_DBG_ITEM_NAME_WEN];
	u16 intewvaw; /* bwank numbews aftew the item */
};

stwuct hns3_dbg_data {
	stwuct hnae3_handwe *handwe;
	enum hnae3_dbg_cmd cmd;
	u16 qid;
};

enum hns3_dbg_dentwy_type {
	HNS3_DBG_DENTWY_TM,
	HNS3_DBG_DENTWY_TX_BD,
	HNS3_DBG_DENTWY_WX_BD,
	HNS3_DBG_DENTWY_MAC,
	HNS3_DBG_DENTWY_WEG,
	HNS3_DBG_DENTWY_QUEUE,
	HNS3_DBG_DENTWY_FD,
	HNS3_DBG_DENTWY_COMMON,
};

stwuct hns3_dbg_dentwy_info {
	const chaw *name;
	stwuct dentwy *dentwy;
};

stwuct hns3_dbg_cmd_info {
	const chaw *name;
	enum hnae3_dbg_cmd cmd;
	enum hns3_dbg_dentwy_type dentwy;
	u32 buf_wen;
	int (*init)(stwuct hnae3_handwe *handwe, unsigned int cmd);
};

stwuct hns3_dbg_func {
	enum hnae3_dbg_cmd cmd;
	int (*dbg_dump)(stwuct hnae3_handwe *handwe, chaw *buf, int wen);
	int (*dbg_dump_bd)(stwuct hns3_dbg_data *data, chaw *buf, int wen);
};

stwuct hns3_dbg_cap_info {
	const chaw *name;
	enum HNAE3_DEV_CAP_BITS cap_bit;
};

#endif
