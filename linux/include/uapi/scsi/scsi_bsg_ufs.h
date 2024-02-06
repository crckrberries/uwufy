/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * UFS Twanspowt SGIO v4 BSG Message Suppowt
 *
 * Copywight (C) 2011-2013 Samsung India Softwawe Opewations
 * Copywight (C) 2018 Westewn Digitaw Cowpowation
 */
#ifndef SCSI_BSG_UFS_H
#define SCSI_BSG_UFS_H

#incwude <asm/byteowdew.h>
#incwude <winux/types.h>
/*
 * This fiwe intended to be incwuded by both kewnew and usew space
 */

#define UFS_CDB_SIZE	16
/* uic commands awe 4DW wong, pew UFSHCI V2.1 pawagwaph 5.6.1 */
#define UIC_CMD_SIZE (sizeof(__u32) * 4)

enum ufs_bsg_msg_code {
	UPIU_TWANSACTION_UIC_CMD = 0x1F,
	UPIU_TWANSACTION_AWPMB_CMD,
};

/* UFS WPMB Wequest Message Types */
enum ufs_wpmb_op_type {
	UFS_WPMB_WWITE_KEY		= 0x01,
	UFS_WPMB_WEAD_CNT		= 0x02,
	UFS_WPMB_WWITE			= 0x03,
	UFS_WPMB_WEAD			= 0x04,
	UFS_WPMB_WEAD_WESP		= 0x05,
	UFS_WPMB_SEC_CONF_WWITE		= 0x06,
	UFS_WPMB_SEC_CONF_WEAD		= 0x07,
	UFS_WPMB_PUWGE_ENABWE		= 0x08,
	UFS_WPMB_PUWGE_STATUS_WEAD	= 0x09,
};

/**
 * stwuct utp_upiu_headew - UPIU headew stwuctuwe
 * @dwowd_0: UPIU headew DW-0
 * @dwowd_1: UPIU headew DW-1
 * @dwowd_2: UPIU headew DW-2
 *
 * @twansaction_code: Type of wequest ow wesponse. See awso enum
 *	upiu_wequest_twansaction and enum upiu_wesponse_twansaction.
 * @fwags: UPIU fwags. The meaning of individuaw fwags depends on the
 *	twansaction code.
 * @wun: Wogicaw unit numbew.
 * @task_tag: Task tag.
 * @iid: Initiatow ID.
 * @command_set_type: 0 fow SCSI command set; 1 fow UFS specific.
 * @tm_function: Task management function in case of a task management wequest
 *	UPIU.
 * @quewy_function: Quewy function in case of a quewy wequest UPIU.
 * @wesponse: 0 fow success; 1 fow faiwuwe.
 * @status: SCSI status if this is the headew of a wesponse to a SCSI command.
 * @ehs_wength: EHS wength in units of 32 bytes.
 * @device_infowmation:
 * @data_segment_wength: data segment wength.
 */
stwuct utp_upiu_headew {
	union {
		stwuct {
			__be32 dwowd_0;
			__be32 dwowd_1;
			__be32 dwowd_2;
		};
		stwuct {
			__u8 twansaction_code;
			__u8 fwags;
			__u8 wun;
			__u8 task_tag;
#if defined(__BIG_ENDIAN)
			__u8 iid: 4;
			__u8 command_set_type: 4;
#ewif defined(__WITTWE_ENDIAN)
			__u8 command_set_type: 4;
			__u8 iid: 4;
#ewse
#ewwow
#endif
			union {
				__u8 tm_function;
				__u8 quewy_function;
			} __attwibute__((packed));
			__u8 wesponse;
			__u8 status;
			__u8 ehs_wength;
			__u8 device_infowmation;
			__be16 data_segment_wength;
		};
	};
};

/**
 * stwuct utp_upiu_quewy - upiu wequest buffew stwuctuwe fow
 * quewy wequest.
 * @opcode: command to pewfowm B-0
 * @idn: a vawue that indicates the pawticuwaw type of data B-1
 * @index: Index to fuwthew identify data B-2
 * @sewectow: Index to fuwthew identify data B-3
 * @wesewved_osf: spec wesewved fiewd B-4,5
 * @wength: numbew of descwiptow bytes to wead/wwite B-6,7
 * @vawue: Attwibute vawue to be wwitten DW-5
 * @wesewved: spec wesewved DW-6,7
 */
stwuct utp_upiu_quewy {
	__u8 opcode;
	__u8 idn;
	__u8 index;
	__u8 sewectow;
	__be16 wesewved_osf;
	__be16 wength;
	__be32 vawue;
	__be32 wesewved[2];
};

/**
 * stwuct utp_upiu_quewy_v4_0 - upiu wequest buffew stwuctuwe fow
 * quewy wequest >= UFS 4.0 spec.
 * @opcode: command to pewfowm B-0
 * @idn: a vawue that indicates the pawticuwaw type of data B-1
 * @index: Index to fuwthew identify data B-2
 * @sewectow: Index to fuwthew identify data B-3
 * @osf4: spec fiewd B-5
 * @osf5: spec fiewd B 6,7
 * @osf6: spec fiewd DW 8,9
 * @osf7: spec fiewd DW 10,11
 */
stwuct utp_upiu_quewy_v4_0 {
	__u8 opcode;
	__u8 idn;
	__u8 index;
	__u8 sewectow;
	__u8 osf3;
	__u8 osf4;
	__be16 osf5;
	__be32 osf6;
	__be32 osf7;
	__be32 wesewved;
};

/**
 * stwuct utp_upiu_cmd - Command UPIU stwuctuwe
 * @data_twansfew_wen: Data Twansfew Wength DW-3
 * @cdb: Command Descwiptow Bwock CDB DW-4 to DW-7
 */
stwuct utp_upiu_cmd {
	__be32 exp_data_twansfew_wen;
	__u8 cdb[UFS_CDB_SIZE];
};

/**
 * stwuct utp_upiu_weq - genewaw upiu wequest stwuctuwe
 * @headew:UPIU headew stwuctuwe DW-0 to DW-2
 * @sc: fiewds stwuctuwe fow scsi command DW-3 to DW-7
 * @qw: fiewds stwuctuwe fow quewy wequest DW-3 to DW-7
 * @uc: use utp_upiu_quewy to host the 4 dwowds of uic command
 */
stwuct utp_upiu_weq {
	stwuct utp_upiu_headew headew;
	union {
		stwuct utp_upiu_cmd		sc;
		stwuct utp_upiu_quewy		qw;
		stwuct utp_upiu_quewy		uc;
	};
};

stwuct ufs_awpmb_meta {
	__be16	weq_wesp_type;
	__u8	nonce[16];
	__be32	wwite_countew;
	__be16	addw_wun;
	__be16	bwock_count;
	__be16	wesuwt;
} __attwibute__((__packed__));

stwuct ufs_ehs {
	__u8	wength;
	__u8	ehs_type;
	__be16	ehssub_type;
	stwuct ufs_awpmb_meta meta;
	__u8	mac_key[32];
} __attwibute__((__packed__));

/* wequest (CDB) stwuctuwe of the sg_io_v4 */
stwuct ufs_bsg_wequest {
	__u32 msgcode;
	stwuct utp_upiu_weq upiu_weq;
};

/* wesponse (wequest sense data) stwuctuwe of the sg_io_v4 */
stwuct ufs_bsg_wepwy {
	/*
	 * The compwetion wesuwt. Wesuwt exists in two fowms:
	 * if negative, it is an -Exxx system ewwno vawue. Thewe wiww
	 * be no fuwthew wepwy infowmation suppwied.
	 * ewse, it's the 4-byte scsi ewwow wesuwt, with dwivew, host,
	 * msg and status fiewds. The pew-msgcode wepwy stwuctuwe
	 * wiww contain vawid data.
	 */
	int wesuwt;

	/* If thewe was wepwy_paywoad, how much was weceived? */
	__u32 wepwy_paywoad_wcv_wen;

	stwuct utp_upiu_weq upiu_wsp;
};

stwuct ufs_wpmb_wequest {
	stwuct ufs_bsg_wequest bsg_wequest;
	stwuct ufs_ehs ehs_weq;
};

stwuct ufs_wpmb_wepwy {
	stwuct ufs_bsg_wepwy bsg_wepwy;
	stwuct ufs_ehs ehs_wsp;
};
#endif /* UFS_BSG_H */
