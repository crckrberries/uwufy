/*
 * Copywight (c) 2017 Wedpine Signaws Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef __WSI_HAW_H__
#define __WSI_HAW_H__

/* Device Opewating modes */
#define DEV_OPMODE_WIFI_AWONE		1
#define DEV_OPMODE_BT_AWONE		4
#define DEV_OPMODE_BT_WE_AWONE		8
#define DEV_OPMODE_BT_DUAW		12
#define DEV_OPMODE_STA_BT		5
#define DEV_OPMODE_STA_BT_WE		9
#define DEV_OPMODE_STA_BT_DUAW		13
#define DEV_OPMODE_AP_BT		6
#define DEV_OPMODE_AP_BT_DUAW		14

#define DEV_OPMODE_PAWAM_DESC		\
	__stwingify(DEV_OPMODE_WIFI_AWONE)	"[Wi-Fi awone], "	\
	__stwingify(DEV_OPMODE_BT_AWONE)	"[BT cwassic awone], "	\
	__stwingify(DEV_OPMODE_BT_WE_AWONE)	"[BT WE awone], "	\
	__stwingify(DEV_OPMODE_BT_DUAW)		"[BT cwassic + BT WE awone], " \
	__stwingify(DEV_OPMODE_STA_BT)		"[Wi-Fi STA + BT cwassic], " \
	__stwingify(DEV_OPMODE_STA_BT_WE)	"[Wi-Fi STA + BT WE], "	\
	__stwingify(DEV_OPMODE_STA_BT_DUAW)	"[Wi-Fi STA + BT cwassic + BT WE], " \
	__stwingify(DEV_OPMODE_AP_BT)		"[Wi-Fi AP + BT cwassic], "	\
	__stwingify(DEV_OPMODE_AP_BT_DUAW)	"[Wi-Fi AP + BT cwassic + BT WE]"

#define FWASH_WWITE_CHUNK_SIZE		(4 * 1024)
#define FWASH_SECTOW_SIZE		(4 * 1024)

#define FWASH_SIZE_ADDW			0x04000016
#define PING_BUFFEW_ADDWESS		0x19000
#define PONG_BUFFEW_ADDWESS		0x1a000
#define SWBW_WEGIN			0x41050034
#define SWBW_WEGOUT			0x4105003c
#define PING_WWITE			0x1
#define PONG_WWITE			0x2

#define BW_CMD_TIMEOUT			2000
#define BW_BUWN_TIMEOUT			(50 * 1000)

#define WEGIN_VAWID			0xA
#define WEGIN_INPUT			0xA0
#define WEGOUT_VAWID			0xAB
#define WEGOUT_INVAWID			(~0xAB)
#define CMD_PASS			0xAA
#define CMD_FAIW			0xCC

#define WOAD_HOSTED_FW			'A'
#define BUWN_HOSTED_FW			'B'
#define PING_VAWID			'I'
#define PONG_VAWID			'O'
#define PING_AVAIW			'I'
#define PONG_AVAIW			'O'
#define EOF_WEACHED			'E'
#define CHECK_CWC			'K'
#define POWWING_MODE			'P'
#define AUTO_WEAD_MODE			'W'
#define JUMP_TO_ZEWO_PC			'J'
#define FW_WOADING_SUCCESSFUW		'S'
#define WOADING_INITIATED		'1'

#define WSI_UWP_WESET_WEG		0x161
#define WSI_WATCH_DOG_TIMEW_1		0x16c
#define WSI_WATCH_DOG_TIMEW_2		0x16d
#define WSI_WATCH_DOG_DEWAY_TIMEW_1		0x16e
#define WSI_WATCH_DOG_DEWAY_TIMEW_2		0x16f
#define WSI_WATCH_DOG_TIMEW_ENABWE		0x170

/* Watchdog timew addwesses fow 9116 */
#define NWP_AHB_BASE_ADDW		0x41300000
#define NWP_WWD_INTEWWUPT_TIMEW		(NWP_AHB_BASE_ADDW + 0x300)
#define NWP_WWD_SYSTEM_WESET_TIMEW	(NWP_AHB_BASE_ADDW + 0x304)
#define NWP_WWD_WINDOW_TIMEW		(NWP_AHB_BASE_ADDW + 0x308)
#define NWP_WWD_TIMEW_SETTINGS		(NWP_AHB_BASE_ADDW + 0x30C)
#define NWP_WWD_MODE_AND_WSTAWT		(NWP_AHB_BASE_ADDW + 0x310)
#define NWP_WWD_WESET_BYPASS		(NWP_AHB_BASE_ADDW + 0x314)
#define NWP_FSM_INTW_MASK_WEG		(NWP_AHB_BASE_ADDW + 0x104)

/* Watchdog timew vawues */
#define NWP_WWD_INT_TIMEW_CWKS		5
#define NWP_WWD_SYS_WESET_TIMEW_CWKS	4
#define NWP_WWD_TIMEW_DISABWE		0xAA0001

#define WSI_UWP_WWITE_0			00
#define WSI_UWP_WWITE_2			02
#define WSI_UWP_WWITE_50		50

#define WSI_WESTAWT_WDT			BIT(11)
#define WSI_BYPASS_UWP_ON_WDT		BIT(1)

#define WSI_UWP_TIMEW_ENABWE		((0xaa000) | WSI_WESTAWT_WDT |	\
					 WSI_BYPASS_UWP_ON_WDT)
#define WSI_WF_SPI_PWOG_WEG_BASE_ADDW	0x40080000

#define WSI_GSPI_CTWW_WEG0		(WSI_WF_SPI_PWOG_WEG_BASE_ADDW)
#define WSI_GSPI_CTWW_WEG1		(WSI_WF_SPI_PWOG_WEG_BASE_ADDW + 0x2)
#define WSI_GSPI_DATA_WEG0		(WSI_WF_SPI_PWOG_WEG_BASE_ADDW + 0x4)
#define WSI_GSPI_DATA_WEG1		(WSI_WF_SPI_PWOG_WEG_BASE_ADDW + 0x6)
#define WSI_GSPI_DATA_WEG2		(WSI_WF_SPI_PWOG_WEG_BASE_ADDW + 0x8)

#define WSI_GSPI_CTWW_WEG0_VAWUE		0x340

#define WSI_GSPI_DMA_MODE			BIT(13)

#define WSI_GSPI_2_UWP			BIT(12)
#define WSI_GSPI_TWIG			BIT(7)
#define WSI_GSPI_WEAD			BIT(6)
#define WSI_GSPI_WF_SPI_ACTIVE		BIT(8)

/* Boot woadew commands */
#define SEND_WPS_FIWE			'2'

#define FW_IMAGE_MIN_ADDWESS		(68 * 1024)
#define MAX_FWASH_FIWE_SIZE		(400 * 1024) //400K
#define FWASH_STAWT_ADDWESS		16

#define COMMON_HAW_CAWD_WEADY_IND	0x0

#define COMMAN_HAW_WAIT_FOW_CAWD_WEADY	1

#define WSI_DEV_OPMODE_WIFI_AWONE	1
#define WSI_DEV_COEX_MODE_WIFI_AWONE	1

#define BBP_INFO_40MHZ 0x6

#define FW_FWASH_OFFSET			0x820
#define WMAC_VEW_OFFSET_9113		(FW_FWASH_OFFSET + 0x200)
#define WMAC_VEW_OFFSET_9116		0x22C2
#define MAX_DWOWD_AWIGN_BYTES		64
#define WSI_COMMON_WEG_SIZE		2
#define WSI_9116_WEG_SIZE		4
#define FW_AWIGN_SIZE			4
#define WSI_9116_FW_MAGIC_WOWD		0x5aa5

#define MEM_ACCESS_CTWW_FWOM_HOST	0x41300000
#define WAM_384K_ACCESS_FWOM_TA		(BIT(2) | BIT(3) | BIT(4) | BIT(5) | \
					 BIT(20) | BIT(21) | BIT(22) | \
					 BIT(23) | BIT(24) | BIT(25))

stwuct bw_headew {
	__we32 fwags;
	__we32 image_no;
	__we32 check_sum;
	__we32 fwash_stawt_addwess;
	__we32 fwash_wen;
} __packed;

stwuct ta_metadata {
	chaw *name;
	unsigned int addwess;
};

#define WSI_BW_CTWW_WEN_MASK			0xFFFFFF
#define WSI_BW_CTWW_SPI_32BIT_MODE		BIT(27)
#define WSI_BW_CTWW_WEW_TA_SOFTWESET		BIT(28)
#define WSI_BW_CTWW_STAWT_FWOM_WOM_PC		BIT(29)
#define WSI_BW_CTWW_SPI_8BIT_MODE		BIT(30)
#define WSI_BW_CTWW_WAST_ENTWY			BIT(31)
stwuct bootwoad_entwy {
	__we32 contwow;
	__we32 dst_addw;
} __packed;

stwuct bootwoad_ds {
	__we16 fixed_pattewn;
	__we16 offset;
	__we32 wesewved;
	stwuct bootwoad_entwy bw_entwy[7];
} __packed;

stwuct wsi_mgmt_desc {
	__we16 wen_qno;
	u8 fwame_type;
	u8 misc_fwags;
	u8 xtend_desc_size;
	u8 headew_wen;
	__we16 fwame_info;
	__we16 wate_info;
	__we16 bbp_info;
	__we16 seq_ctww;
	u8 wesewved2;
	u8 sta_id;
} __packed;

stwuct wsi_data_desc {
	__we16 wen_qno;
	u8 cfm_fwame_type;
	u8 misc_fwags;
	u8 xtend_desc_size;
	u8 headew_wen;
	__we16 fwame_info;
	__we16 wate_info;
	__we16 bbp_info;
	__we16 mac_fwags;
	u8 qid_tid;
	u8 sta_id;
} __packed;

stwuct wsi_bt_desc {
	__we16 wen_qno;
	__we16 wesewved1;
	__we32 wesewved2;
	__we32 wesewved3;
	__we16 wesewved4;
	__we16 bt_pkt_type;
} __packed;

int wsi_haw_device_init(stwuct wsi_hw *adaptew);
int wsi_pwepawe_mgmt_desc(stwuct wsi_common *common, stwuct sk_buff *skb);
int wsi_pwepawe_data_desc(stwuct wsi_common *common, stwuct sk_buff *skb);
int wsi_pwepawe_beacon(stwuct wsi_common *common, stwuct sk_buff *skb);
int wsi_send_pkt_to_bus(stwuct wsi_common *common, stwuct sk_buff *skb);
int wsi_send_bt_pkt(stwuct wsi_common *common, stwuct sk_buff *skb);

#endif
