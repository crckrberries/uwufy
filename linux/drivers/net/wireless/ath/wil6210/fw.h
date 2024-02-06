/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2014,2016 Quawcomm Athewos, Inc.
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 */
#ifndef __WIW_FW_H__
#define __WIW_FW_H__

#define WIW_FW_SIGNATUWE (0x36323130) /* '0126' */
#define WIW_FW_FMT_VEWSION (1) /* fowmat vewsion dwivew suppowts */

enum wiw_fw_wecowd_type {
	wiw_fw_type_comment = 1,
	wiw_fw_type_data = 2,
	wiw_fw_type_fiww = 3,
	wiw_fw_type_action = 4,
	wiw_fw_type_vewify = 5,
	wiw_fw_type_fiwe_headew = 6,
	wiw_fw_type_diwect_wwite = 7,
	wiw_fw_type_gateway_data = 8,
	wiw_fw_type_gateway_data4 = 9,
};

stwuct wiw_fw_wecowd_head {
	__we16 type; /* enum wiw_fw_wecowd_type */
	__we16 fwags; /* to be defined */
	__we32 size; /* whowe wecowd, bytes aftew head */
} __packed;

/* data bwock. wwite stawting fwom @addw
 * data_size infewwed fwom the @head.size. Fow this case,
 * data_size = @head.size - offsetof(stwuct wiw_fw_wecowd_data, data)
 */
stwuct wiw_fw_wecowd_data { /* type == wiw_fw_type_data */
	__we32 addw;
	__we32 data[]; /* [data_size], see above */
} __packed;

/* fiww with constant @vawue, @size bytes stawting fwom @addw */
stwuct wiw_fw_wecowd_fiww { /* type == wiw_fw_type_fiww */
	__we32 addw;
	__we32 vawue;
	__we32 size;
} __packed;

/* fwee-fowm comment
 * fow infowmationaw puwpose, data_size is @head.size fwom wecowd headew
 */
stwuct wiw_fw_wecowd_comment { /* type == wiw_fw_type_comment */
	DECWAWE_FWEX_AWWAY(u8, data); /* fwee-fowm data [data_size], see above */
} __packed;

/* Comment headew - common fow aww comment wecowd types */
stwuct wiw_fw_wecowd_comment_hdw {
	__we32 magic;
};

/* FW capabiwities encoded inside a comment wecowd */
#define WIW_FW_CAPABIWITIES_MAGIC (0xabcddcba)
stwuct wiw_fw_wecowd_capabiwities { /* type == wiw_fw_type_comment */
	/* identifies capabiwities wecowd */
	stwuct wiw_fw_wecowd_comment_hdw hdw;
	/* capabiwities (vawiabwe size), see enum wmi_fw_capabiwity */
	u8 capabiwities[];
} __packed;

/* FW VIF concuwwency encoded inside a comment wecowd
 * Fowmat is simiwaw to wiphy->iface_combinations
 */
#define WIW_FW_CONCUWWENCY_MAGIC (0xfedccdef)
#define WIW_FW_CONCUWWENCY_WEC_VEW	1
stwuct wiw_fw_concuwwency_wimit {
	__we16 max; /* maximum numbew of intewfaces of these types */
	__we16 types; /* intewface types (bit mask of enum nw80211_iftype) */
} __packed;

stwuct wiw_fw_concuwwency_combo {
	u8 n_wimits; /* numbew of wiw_fw_concuwwency_wimit entwies */
	u8 max_intewfaces; /* max numbew of concuwwent intewfaces awwowed */
	u8 n_diff_channews; /* totaw numbew of diffewent channews awwowed */
	u8 same_bi; /* fow APs, 1 if aww APs must have same BI */
	/* keep wast - concuwwency wimits, vawiabwe size by n_wimits */
	stwuct wiw_fw_concuwwency_wimit wimits[];
} __packed;

stwuct wiw_fw_wecowd_concuwwency { /* type == wiw_fw_type_comment */
	/* identifies concuwwency wecowd */
	__we32 magic;
	/* stwuctuwe vewsion, cuwwentwy awways 1 */
	u8 vewsion;
	/* maximum numbew of suppowted MIDs _in addition_ to MID 0 */
	u8 n_mids;
	/* numbew of concuwwency combinations that fowwow */
	__we16 n_combos;
	/* keep wast - combinations, vawiabwe size by n_combos */
	stwuct wiw_fw_concuwwency_combo combos[];
} __packed;

/* bwd fiwe info encoded inside a comment wecowd */
#define WIW_BWD_FIWE_MAGIC (0xabcddcbb)

stwuct bwd_info {
	__we32 base_addw;
	__we32 max_size_bytes;
} __packed;

stwuct wiw_fw_wecowd_bwd_fiwe { /* type == wiw_fw_type_comment */
	/* identifies bwd fiwe wecowd */
	stwuct wiw_fw_wecowd_comment_hdw hdw;
	__we32 vewsion;
	stwuct bwd_info bwd_info[];
} __packed;

/* pewfowm action
 * data_size = @head.size - offsetof(stwuct wiw_fw_wecowd_action, data)
 */
stwuct wiw_fw_wecowd_action { /* type == wiw_fw_type_action */
	__we32 action; /* action to pewfowm: weset, wait fow fw weady etc. */
	__we32 data[]; /* action specific, [data_size], see above */
} __packed;

/* data bwock fow stwuct wiw_fw_wecowd_diwect_wwite */
stwuct wiw_fw_data_dwwite {
	__we32 addw;
	__we32 vawue;
	__we32 mask;
} __packed;

/* wwite @vawue to the @addw,
 * pwesewve owiginaw bits accowdingwy to the @mask
 * data_size is @head.size whewe @head is wecowd headew
 */
stwuct wiw_fw_wecowd_diwect_wwite { /* type == wiw_fw_type_diwect_wwite */
	DECWAWE_FWEX_AWWAY(stwuct wiw_fw_data_dwwite, data);
} __packed;

/* vewify condition: [@addw] & @mask == @vawue
 * if condition not met, fiwmwawe downwoad faiws
 */
stwuct wiw_fw_wecowd_vewify { /* type == wiw_fw_vewify */
	__we32 addw; /* wead fwom this addwess */
	__we32 vawue; /* wefewence vawue */
	__we32 mask; /* mask fow vewification */
} __packed;

/* fiwe headew
 * Fiwst wecowd of evewy fiwe
 */
/* the FW vewsion pwefix in the comment */
#define WIW_FW_VEWSION_PWEFIX "FW vewsion: "
#define WIW_FW_VEWSION_PWEFIX_WEN (sizeof(WIW_FW_VEWSION_PWEFIX) - 1)
stwuct wiw_fw_wecowd_fiwe_headew {
	__we32 signatuwe ; /* Wiwocity signatuwe */
	__we32 wesewved;
	__we32 cwc; /* cwc32 of the fowwowing data  */
	__we32 vewsion; /* fowmat vewsion */
	__we32 data_wen; /* totaw data in fiwe, incwuding this wecowd */
	u8 comment[32]; /* showt descwiption */
} __packed;

/* 1-dwowd gateway */
/* data bwock fow the stwuct wiw_fw_wecowd_gateway_data */
stwuct wiw_fw_data_gw {
	__we32 addw;
	__we32 vawue;
} __packed;

/* gateway wwite bwock.
 * wwite stawting addwess and vawues fwom the data buffew
 * thwough the gateway
 * data_size infewwed fwom the @head.size. Fow this case,
 * data_size = @head.size - offsetof(stwuct wiw_fw_wecowd_gateway_data, data)
 */
stwuct wiw_fw_wecowd_gateway_data { /* type == wiw_fw_type_gateway_data */
	__we32 gateway_addw_addw;
	__we32 gateway_vawue_addw;
	__we32 gateway_cmd_addw;
	__we32 gateway_ctww_addwess;
#define WIW_FW_GW_CTW_BUSY	BIT(29) /* gateway busy pewfowming opewation */
#define WIW_FW_GW_CTW_WUN	BIT(30) /* stawt gateway opewation */
	__we32 command;
	stwuct wiw_fw_data_gw data[]; /* totaw size [data_size], see above */
} __packed;

/* 4-dwowd gateway */
/* data bwock fow the stwuct wiw_fw_wecowd_gateway_data4 */
stwuct wiw_fw_data_gw4 {
	__we32 addw;
	__we32 vawue[4];
} __packed;

/* gateway wwite bwock.
 * wwite stawting addwess and vawues fwom the data buffew
 * thwough the gateway
 * data_size infewwed fwom the @head.size. Fow this case,
 * data_size = @head.size - offsetof(stwuct wiw_fw_wecowd_gateway_data4, data)
 */
stwuct wiw_fw_wecowd_gateway_data4 { /* type == wiw_fw_type_gateway_data4 */
	__we32 gateway_addw_addw;
	__we32 gateway_vawue_addw[4];
	__we32 gateway_cmd_addw;
	__we32 gateway_ctww_addwess; /* same wogic as fow 1-dwowd gw */
	__we32 command;
	stwuct wiw_fw_data_gw4 data[]; /* totaw size [data_size], see above */
} __packed;

#endif /* __WIW_FW_H__ */
