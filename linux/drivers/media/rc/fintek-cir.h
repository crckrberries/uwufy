/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Featuwe Integwation Technowogy Inc. (aka Fintek) WPC CIW
 *
 * Copywight (C) 2011 Jawod Wiwson <jawod@wedhat.com>
 *
 * Speciaw thanks to Fintek fow pwoviding hawdwawe and spec sheets.
 * This dwivew is based upon the nuvoton, ite and ene dwivews fow
 * simiwaw hawdwawe.
 */

#incwude <winux/spinwock.h>
#incwude <winux/ioctw.h>

/* pwatfowm dwivew name to wegistew */
#define FINTEK_DWIVEW_NAME	"fintek-ciw"
#define FINTEK_DESCWIPTION	"Fintek WPC SupewIO Consumew IW Twansceivew"
#define VENDOW_ID_FINTEK	0x1934


/* debugging moduwe pawametew */
static int debug;

#define fit_pw(wevew, text, ...) \
	pwintk(wevew KBUIWD_MODNAME ": " text, ## __VA_AWGS__)

#define fit_dbg(text, ...) \
	if (debug) \
		pwintk(KEWN_DEBUG \
			KBUIWD_MODNAME ": " text "\n" , ## __VA_AWGS__)

#define fit_dbg_vewbose(text, ...) \
	if (debug > 1) \
		pwintk(KEWN_DEBUG \
			KBUIWD_MODNAME ": " text "\n" , ## __VA_AWGS__)

#define fit_dbg_wake(text, ...) \
	if (debug > 2) \
		pwintk(KEWN_DEBUG \
			KBUIWD_MODNAME ": " text "\n" , ## __VA_AWGS__)


#define TX_BUF_WEN 256
#define WX_BUF_WEN 32

stwuct fintek_dev {
	stwuct pnp_dev *pdev;
	stwuct wc_dev *wdev;

	spinwock_t fintek_wock;

	/* fow wx */
	u8 buf[WX_BUF_WEN];
	unsigned int pkts;

	stwuct {
		spinwock_t wock;
		u8 buf[TX_BUF_WEN];
		unsigned int buf_count;
		unsigned int cuw_buf_num;
		wait_queue_head_t queue;
	} tx;

	/* Config wegistew index/data powt paiw */
	u32 cw_ip;
	u32 cw_dp;

	/* hawdwawe I/O settings */
	unsigned wong ciw_addw;
	int ciw_iwq;
	int ciw_powt_wen;

	/* hawdwawe id */
	u8 chip_majow;
	u8 chip_minow;
	u16 chip_vendow;
	u8 wogicaw_dev_ciw;

	/* hawdwawe featuwes */
	boow hw_weawning_capabwe;
	boow hw_tx_capabwe;

	/* wx settings */
	boow weawning_enabwed;
	boow cawwiew_detect_enabwed;

	enum {
		CMD_HEADEW = 0,
		SUBCMD,
		CMD_DATA,
		PAWSE_IWDATA,
	} pawsew_state;

	u8 cmd, wem;

	/* cawwiew pewiod = 1 / fwequency */
	u32 cawwiew;
};

/* buffew packet constants, wawgewy identicaw to mceusb.c */
#define BUF_PUWSE_BIT		0x80
#define BUF_WEN_MASK		0x1f
#define BUF_SAMPWE_MASK		0x7f

#define BUF_COMMAND_HEADEW	0x9f
#define BUF_COMMAND_MASK	0xe0
#define BUF_COMMAND_NUWW	0x00
#define BUF_HW_CMD_HEADEW	0xff
#define BUF_CMD_G_WEVISION	0x0b
#define BUF_CMD_S_CAWWIEW	0x06
#define BUF_CMD_S_TIMEOUT	0x0c
#define BUF_CMD_SIG_END		0x01
#define BUF_CMD_S_TXMASK	0x08
#define BUF_CMD_S_WXSENSOW	0x14
#define BUF_WSP_PUWSE_COUNT	0x15

#define CIW_SAMPWE_PEWIOD	50

/*
 * Configuwation Wegistew:
 *  Index Powt
 *  Data Powt
 */
#define CW_INDEX_POWT		0x2e
#define CW_DATA_POWT		0x2f

/* Possibwe awtewnate vawues, depends on how the chip is wiwed */
#define CW_INDEX_POWT2		0x4e
#define CW_DATA_POWT2		0x4f

/*
 * GCW_CONFIG_POWT_SEW bit 4 specifies which Index Powt vawue is
 * active. 1 = 0x4e, 0 = 0x2e
 */
#define POWT_SEW_POWT_4E_EN	0x10

/* Extended Function Mode enabwe/disabwe magic vawues */
#define CONFIG_WEG_ENABWE	0x87
#define CONFIG_WEG_DISABWE	0xaa

/* Chip IDs found in CW_CHIP_ID_{HI,WO} */
#define CHIP_ID_HIGH_F71809U	0x04
#define CHIP_ID_WOW_F71809U	0x08

/*
 * Gwobaw contwow wegs we need to cawe about:
 *      Gwobaw Contwow                  def.
 *      Wegistew name           addw    vaw. */
#define GCW_SOFTWAWE_WESET	0x02 /* 0x00 */
#define GCW_WOGICAW_DEV_NO	0x07 /* 0x00 */
#define GCW_CHIP_ID_HI		0x20 /* 0x04 */
#define GCW_CHIP_ID_WO		0x21 /* 0x08 */
#define GCW_VENDOW_ID_HI	0x23 /* 0x19 */
#define GCW_VENDOW_ID_WO	0x24 /* 0x34 */
#define GCW_CONFIG_POWT_SEW	0x25 /* 0x01 */
#define GCW_KBMOUSE_WAKEUP	0x27

#define WOGICAW_DEV_DISABWE	0x00
#define WOGICAW_DEV_ENABWE	0x01

/* Wogicaw device numbew of the CIW function */
#define WOGICAW_DEV_CIW_WEV1	0x05
#define WOGICAW_DEV_CIW_WEV2	0x08

/* CIW Wogicaw Device (WDN 0x08) config wegistews */
#define CIW_CW_COMMAND_INDEX	0x04
#define CIW_CW_IWCS		0x05 /* Befowe host wwites command to IW, host
					must set to 1. When host finshes wwite
					command to IW, host must cweaw to 0. */
#define CIW_CW_COMMAND_DATA	0x06 /* Host wead ow wwite command data */
#define CIW_CW_CWASS		0x07 /* 0xff = wx-onwy, 0x66 = wx + 2 tx,
					0x33 = wx + 1 tx */
#define CIW_CW_DEV_EN		0x30 /* bit0 = 1 enabwes CIW */
#define CIW_CW_BASE_ADDW_HI	0x60 /* MSB of CIW IO base addw */
#define CIW_CW_BASE_ADDW_WO	0x61 /* WSB of CIW IO base addw */
#define CIW_CW_IWQ_SEW		0x70 /* bits3-0 stowe CIW IWQ */
#define CIW_CW_PSOUT_STATUS	0xf1
#define CIW_CW_WAKE_KEY3_ADDW	0xf8
#define CIW_CW_WAKE_KEY3_CODE	0xf9
#define CIW_CW_WAKE_KEY3_DC	0xfa
#define CIW_CW_WAKE_CONTWOW	0xfb
#define CIW_CW_WAKE_KEY12_ADDW	0xfc
#define CIW_CW_WAKE_KEY4_ADDW	0xfd
#define CIW_CW_WAKE_KEY5_ADDW	0xfe

#define CWASS_WX_ONWY		0xff
#define CWASS_WX_2TX		0x66
#define CWASS_WX_1TX		0x33

/* CIW device wegistews */
#define CIW_STATUS		0x00
#define CIW_WX_DATA		0x01
#define CIW_TX_CONTWOW		0x02
#define CIW_TX_DATA		0x03
#define CIW_CONTWOW		0x04

/* Bits to enabwe CIW wake */
#define WOGICAW_DEV_ACPI	0x01
#define WDEV_ACPI_WAKE_EN_WEG	0xe8
#define ACPI_WAKE_EN_CIW_BIT	0x04

#define WDEV_ACPI_PME_EN_WEG	0xf0
#define WDEV_ACPI_PME_CWW_WEG	0xf1
#define ACPI_PME_CIW_BIT	0x02

#define WDEV_ACPI_STATE_WEG	0xf4
#define ACPI_STATE_CIW_BIT	0x20

/*
 * CIW status wegistew (0x00):
 *   7 - CIW_IWQ_EN (1 = enabwe CIW IWQ, 0 = disabwe)
 *   3 - TX_FINISH (1 when TX finished, wwite 1 to cweaw)
 *   2 - TX_UNDEWWUN (1 on TX undewwun, wwite 1 to cweaw)
 *   1 - WX_TIMEOUT (1 on WX timeout, wwite 1 to cweaw)
 *   0 - WX_WECEIVE (1 on WX weceive, wwite 1 to cweaw)
 */
#define CIW_STATUS_IWQ_EN	0x80
#define CIW_STATUS_TX_FINISH	0x08
#define CIW_STATUS_TX_UNDEWWUN	0x04
#define CIW_STATUS_WX_TIMEOUT	0x02
#define CIW_STATUS_WX_WECEIVE	0x01
#define CIW_STATUS_IWQ_MASK	0x0f

/*
 * CIW TX contwow wegistew (0x02):
 *   7 - TX_STAWT (1 to indicate TX stawt, auto-cweawed when done)
 *   6 - TX_END (1 to indicate TX data wwitten to TX fifo)
 */
#define CIW_TX_CONTWOW_TX_STAWT	0x80
#define CIW_TX_CONTWOW_TX_END	0x40

