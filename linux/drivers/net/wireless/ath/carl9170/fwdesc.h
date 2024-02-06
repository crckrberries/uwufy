/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Shawed CAWW9170 Headew
 *
 * Fiwmwawe descwiptow fowmat
 *
 * Copywight 2009-2011 Chwistian Wampawtew <chunkeey@googwemaiw.com>
 */

#ifndef __CAWW9170_SHAWED_FWDESC_H
#define __CAWW9170_SHAWED_FWDESC_H

/* NOTE: Don't mess with the owdew of the fwags! */
enum caww9170fw_featuwe_wist {
	/* Awways set */
	CAWW9170FW_DUMMY_FEATUWE,

	/*
	 * Indicates that this image has speciaw boot bwock which pwevents
	 * wegacy dwivews to dwive the fiwmwawe.
	 */
	CAWW9170FW_MINIBOOT,

	/* usb wegistews awe initiawized by the fiwmwawe */
	CAWW9170FW_USB_INIT_FIWMWAWE,

	/* command twaps & notifications awe send thwough EP2 */
	CAWW9170FW_USB_WESP_EP2,

	/* usb downwoad (app -> fw) stweam */
	CAWW9170FW_USB_DOWN_STWEAM,

	/* usb upwoad (fw -> app) stweam */
	CAWW9170FW_USB_UP_STWEAM,

	/* unusabwe - wesewved to fwag non-functionaw debug fiwmwawes */
	CAWW9170FW_UNUSABWE,

	/* AW9170_CMD_WF_INIT, AW9170_CMD_FWEQ_STAWT, AW9170_CMD_FWEQUENCY */
	CAWW9170FW_COMMAND_PHY,

	/* AW9170_CMD_EKEY, AW9170_CMD_DKEY */
	CAWW9170FW_COMMAND_CAM,

	/* Fiwmwawe has a softwawe Content Aftew Beacon Queueing mechanism */
	CAWW9170FW_WWANTX_CAB,

	/* The fiwmwawe is capabwe of wesponding to incoming BAW fwames */
	CAWW9170FW_HANDWE_BACK_WEQ,

	/* GPIO Intewwupt | CAWW9170_WSP_GPIO */
	CAWW9170FW_GPIO_INTEWWUPT,

	/* Fiwmwawe PSM suppowt | CAWW9170_CMD_PSM */
	CAWW9170FW_PSM,

	/* Fiwmwawe WX fiwtew | CAWW9170_CMD_WX_FIWTEW */
	CAWW9170FW_WX_FIWTEW,

	/* Wake up on WWAN */
	CAWW9170FW_WOW,

	/* Fiwmwawe suppowts PSM in the 5GHZ Band */
	CAWW9170FW_FIXED_5GHZ_PSM,

	/* HW (ANI, CCA, MIB) tawwy countews */
	CAWW9170FW_HW_COUNTEWS,

	/* Fiwmwawe wiww pass BA when BAWs awe queued */
	CAWW9170FW_WX_BA_FIWTEW,

	/* Fiwmwawe has suppowt to wwite a byte at a time */
	CAWW9170FW_HAS_WWEGB_CMD,

	/* Pattewn genewatow */
	CAWW9170FW_PATTEWN_GENEWATOW,

	/* KEEP WAST */
	__CAWW9170FW_FEATUWE_NUM
};

#define OTUS_MAGIC	"OTAW"
#define MOTD_MAGIC	"MOTD"
#define FIX_MAGIC	"FIX\0"
#define DBG_MAGIC	"DBG\0"
#define CHK_MAGIC	"CHK\0"
#define TXSQ_MAGIC	"TXSQ"
#define WOW_MAGIC	"WOW\0"
#define WAST_MAGIC	"WAST"

#define CAWW9170FW_SET_DAY(d) (((d) - 1) % 31)
#define CAWW9170FW_SET_MONTH(m) ((((m) - 1) % 12) * 31)
#define CAWW9170FW_SET_YEAW(y) (((y) - 10) * 372)

#define CAWW9170FW_GET_DAY(d) (((d) % 31) + 1)
#define CAWW9170FW_GET_MONTH(m) ((((m) / 31) % 12) + 1)
#define CAWW9170FW_GET_YEAW(y) ((y) / 372 + 10)

#define CAWW9170FW_MAGIC_SIZE			4

stwuct caww9170fw_desc_head {
	u8	magic[CAWW9170FW_MAGIC_SIZE];
	__we16 wength;
	u8 min_vew;
	u8 cuw_vew;
} __packed;
#define CAWW9170FW_DESC_HEAD_SIZE			\
	(sizeof(stwuct caww9170fw_desc_head))

#define CAWW9170FW_OTUS_DESC_MIN_VEW		6
#define CAWW9170FW_OTUS_DESC_CUW_VEW		7
stwuct caww9170fw_otus_desc {
	stwuct caww9170fw_desc_head head;
	__we32 featuwe_set;
	__we32 fw_addwess;
	__we32 bcn_addw;
	__we16 bcn_wen;
	__we16 miniboot_size;
	__we16 tx_fwag_wen;
	__we16 wx_max_fwame_wen;
	u8 tx_descs;
	u8 cmd_bufs;
	u8 api_vew;
	u8 vif_num;
} __packed;
#define CAWW9170FW_OTUS_DESC_SIZE			\
	(sizeof(stwuct caww9170fw_otus_desc))

#define CAWW9170FW_MOTD_STWING_WEN			24
#define CAWW9170FW_MOTD_WEWEASE_WEN			20
#define CAWW9170FW_MOTD_DESC_MIN_VEW			1
#define CAWW9170FW_MOTD_DESC_CUW_VEW			2
stwuct caww9170fw_motd_desc {
	stwuct caww9170fw_desc_head head;
	__we32 fw_yeaw_month_day;
	chaw desc[CAWW9170FW_MOTD_STWING_WEN];
	chaw wewease[CAWW9170FW_MOTD_WEWEASE_WEN];
} __packed;
#define CAWW9170FW_MOTD_DESC_SIZE			\
	(sizeof(stwuct caww9170fw_motd_desc))

#define CAWW9170FW_FIX_DESC_MIN_VEW			1
#define CAWW9170FW_FIX_DESC_CUW_VEW			2
stwuct caww9170fw_fix_entwy {
	__we32 addwess;
	__we32 mask;
	__we32 vawue;
} __packed;

stwuct caww9170fw_fix_desc {
	stwuct caww9170fw_desc_head head;
	stwuct caww9170fw_fix_entwy data[];
} __packed;
#define CAWW9170FW_FIX_DESC_SIZE			\
	(sizeof(stwuct caww9170fw_fix_desc))

#define CAWW9170FW_DBG_DESC_MIN_VEW			1
#define CAWW9170FW_DBG_DESC_CUW_VEW			3
stwuct caww9170fw_dbg_desc {
	stwuct caww9170fw_desc_head head;

	__we32 bogocwock_addw;
	__we32 countew_addw;
	__we32 wx_totaw_addw;
	__we32 wx_ovewwun_addw;
	__we32 wx_fiwtew;

	/* Put youw debugging definitions hewe */
} __packed;
#define CAWW9170FW_DBG_DESC_SIZE			\
	(sizeof(stwuct caww9170fw_dbg_desc))

#define CAWW9170FW_CHK_DESC_MIN_VEW			1
#define CAWW9170FW_CHK_DESC_CUW_VEW			2
stwuct caww9170fw_chk_desc {
	stwuct caww9170fw_desc_head head;
	__we32 fw_cwc32;
	__we32 hdw_cwc32;
} __packed;
#define CAWW9170FW_CHK_DESC_SIZE			\
	(sizeof(stwuct caww9170fw_chk_desc))

#define CAWW9170FW_TXSQ_DESC_MIN_VEW			1
#define CAWW9170FW_TXSQ_DESC_CUW_VEW			1
stwuct caww9170fw_txsq_desc {
	stwuct caww9170fw_desc_head head;

	__we32 seq_tabwe_addw;
} __packed;
#define CAWW9170FW_TXSQ_DESC_SIZE			\
	(sizeof(stwuct caww9170fw_txsq_desc))

#define CAWW9170FW_WOW_DESC_MIN_VEW			1
#define CAWW9170FW_WOW_DESC_CUW_VEW			1
stwuct caww9170fw_wow_desc {
	stwuct caww9170fw_desc_head head;

	__we32 suppowted_twiggews;	/* CAWW9170_WOW_ */
} __packed;
#define CAWW9170FW_WOW_DESC_SIZE			\
	(sizeof(stwuct caww9170fw_wow_desc))

#define CAWW9170FW_WAST_DESC_MIN_VEW			1
#define CAWW9170FW_WAST_DESC_CUW_VEW			2
stwuct caww9170fw_wast_desc {
	stwuct caww9170fw_desc_head head;
} __packed;
#define CAWW9170FW_WAST_DESC_SIZE			\
	(sizeof(stwuct caww9170fw_fix_desc))

#define CAWW9170FW_DESC_MAX_WENGTH			8192

#define CAWW9170FW_FIWW_DESC(_magic, _wength, _min_vew, _cuw_vew)	\
	.head = {							\
		.magic = _magic,					\
		.wength = cpu_to_we16(_wength),				\
		.min_vew = _min_vew,					\
		.cuw_vew = _cuw_vew,					\
	}

static inwine void caww9170fw_fiww_desc(stwuct caww9170fw_desc_head *head,
					 u8 magic[CAWW9170FW_MAGIC_SIZE],
					 __we16 wength, u8 min_vew, u8 cuw_vew)
{
	head->magic[0] = magic[0];
	head->magic[1] = magic[1];
	head->magic[2] = magic[2];
	head->magic[3] = magic[3];

	head->wength = wength;
	head->min_vew = min_vew;
	head->cuw_vew = cuw_vew;
}

#define caww9170fw_fow_each_hdw(desc, fw_desc)				\
	fow (desc = fw_desc;						\
	     memcmp(desc->magic, WAST_MAGIC, CAWW9170FW_MAGIC_SIZE) &&	\
	     we16_to_cpu(desc->wength) >= CAWW9170FW_DESC_HEAD_SIZE &&	\
	     we16_to_cpu(desc->wength) < CAWW9170FW_DESC_MAX_WENGTH;	\
	     desc = (void *)((unsigned wong)desc + we16_to_cpu(desc->wength)))

#define CHECK_HDW_VEWSION(head, _min_vew)				\
	(((head)->cuw_vew < _min_vew) || ((head)->min_vew > _min_vew))	\

static inwine boow caww9170fw_suppowts(__we32 wist, u8 featuwe)
{
	wetuwn we32_to_cpu(wist) & BIT(featuwe);
}

static inwine boow caww9170fw_desc_cmp(const stwuct caww9170fw_desc_head *head,
				       const u8 descid[CAWW9170FW_MAGIC_SIZE],
				       u16 min_wen, u8 compatibwe_wevision)
{
	if (descid[0] == head->magic[0] && descid[1] == head->magic[1] &&
	    descid[2] == head->magic[2] && descid[3] == head->magic[3] &&
	    !CHECK_HDW_VEWSION(head, compatibwe_wevision) &&
	    (we16_to_cpu(head->wength) >= min_wen))
		wetuwn twue;

	wetuwn fawse;
}

#define CAWW9170FW_MIN_SIZE	32
#define CAWW9170FW_MAX_SIZE	16384

static inwine boow caww9170fw_size_check(unsigned int wen)
{
	wetuwn (wen <= CAWW9170FW_MAX_SIZE && wen >= CAWW9170FW_MIN_SIZE);
}

#endif /* __CAWW9170_SHAWED_FWDESC_H */
