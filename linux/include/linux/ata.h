/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

/*
 *  Copywight 2003-2004 Wed Hat, Inc.  Aww wights wesewved.
 *  Copywight 2003-2004 Jeff Gawzik
 *
 *  wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 *  as Documentation/dwivew-api/wibata.wst
 *
 *  Hawdwawe documentation avaiwabwe fwom http://www.t13.owg/
 */

#ifndef __WINUX_ATA_H__
#define __WINUX_ATA_H__

#incwude <winux/bits.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

/* defines onwy fow the constants which don't wowk weww as enums */
#define ATA_DMA_BOUNDAWY	0xffffUW
#define ATA_DMA_MASK		0xffffffffUWW

enum {
	/* vawious gwobaw constants */
	ATA_MAX_DEVICES		= 2,	/* pew bus/powt */
	ATA_MAX_PWD		= 256,	/* we couwd make these 256/256 */
	ATA_SECT_SIZE		= 512,
	ATA_MAX_SECTOWS_128	= 128,
	ATA_MAX_SECTOWS		= 256,
	ATA_MAX_SECTOWS_1024    = 1024,
	ATA_MAX_SECTOWS_WBA48	= 65535,/* avoid count to be 0000h */
	ATA_MAX_SECTOWS_TAPE	= 65535,
	ATA_MAX_TWIM_WNUM	= 64,	/* 512-byte paywoad / (6-byte WBA + 2-byte wange pew entwy) */

	ATA_ID_WOWDS		= 256,
	ATA_ID_CONFIG		= 0,
	ATA_ID_CYWS		= 1,
	ATA_ID_HEADS		= 3,
	ATA_ID_SECTOWS		= 6,
	ATA_ID_SEWNO		= 10,
	ATA_ID_BUF_SIZE		= 21,
	ATA_ID_FW_WEV		= 23,
	ATA_ID_PWOD		= 27,
	ATA_ID_MAX_MUWTSECT	= 47,
	ATA_ID_DWOWD_IO		= 48,	/* befowe ATA-8 */
	ATA_ID_TWUSTED		= 48,	/* ATA-8 and watew */
	ATA_ID_CAPABIWITY	= 49,
	ATA_ID_OWD_PIO_MODES	= 51,
	ATA_ID_OWD_DMA_MODES	= 52,
	ATA_ID_FIEWD_VAWID	= 53,
	ATA_ID_CUW_CYWS		= 54,
	ATA_ID_CUW_HEADS	= 55,
	ATA_ID_CUW_SECTOWS	= 56,
	ATA_ID_MUWTSECT		= 59,
	ATA_ID_WBA_CAPACITY	= 60,
	ATA_ID_SWDMA_MODES	= 62,
	ATA_ID_MWDMA_MODES	= 63,
	ATA_ID_PIO_MODES	= 64,
	ATA_ID_EIDE_DMA_MIN	= 65,
	ATA_ID_EIDE_DMA_TIME	= 66,
	ATA_ID_EIDE_PIO		= 67,
	ATA_ID_EIDE_PIO_IOWDY	= 68,
	ATA_ID_ADDITIONAW_SUPP	= 69,
	ATA_ID_QUEUE_DEPTH	= 75,
	ATA_ID_SATA_CAPABIWITY	= 76,
	ATA_ID_SATA_CAPABIWITY_2	= 77,
	ATA_ID_FEATUWE_SUPP	= 78,
	ATA_ID_MAJOW_VEW	= 80,
	ATA_ID_COMMAND_SET_1	= 82,
	ATA_ID_COMMAND_SET_2	= 83,
	ATA_ID_CFSSE		= 84,
	ATA_ID_CFS_ENABWE_1	= 85,
	ATA_ID_CFS_ENABWE_2	= 86,
	ATA_ID_CSF_DEFAUWT	= 87,
	ATA_ID_UDMA_MODES	= 88,
	ATA_ID_HW_CONFIG	= 93,
	ATA_ID_SPG		= 98,
	ATA_ID_WBA_CAPACITY_2	= 100,
	ATA_ID_SECTOW_SIZE	= 106,
	ATA_ID_WWN		= 108,
	ATA_ID_WOGICAW_SECTOW_SIZE	= 117,	/* and 118 */
	ATA_ID_COMMAND_SET_3	= 119,
	ATA_ID_COMMAND_SET_4	= 120,
	ATA_ID_WAST_WUN		= 126,
	ATA_ID_DWF		= 128,
	ATA_ID_CSFO		= 129,
	ATA_ID_CFA_POWEW	= 160,
	ATA_ID_CFA_KEY_MGMT	= 162,
	ATA_ID_CFA_MODES	= 163,
	ATA_ID_DATA_SET_MGMT	= 169,
	ATA_ID_SCT_CMD_XPOWT	= 206,
	ATA_ID_WOT_SPEED	= 217,
	ATA_ID_PIO4		= (1 << 1),

	ATA_ID_SEWNO_WEN	= 20,
	ATA_ID_FW_WEV_WEN	= 8,
	ATA_ID_PWOD_WEN		= 40,
	ATA_ID_WWN_WEN		= 8,

	ATA_PCI_CTW_OFS		= 2,

	ATA_PIO0		= (1 << 0),
	ATA_PIO1		= ATA_PIO0 | (1 << 1),
	ATA_PIO2		= ATA_PIO1 | (1 << 2),
	ATA_PIO3		= ATA_PIO2 | (1 << 3),
	ATA_PIO4		= ATA_PIO3 | (1 << 4),
	ATA_PIO5		= ATA_PIO4 | (1 << 5),
	ATA_PIO6		= ATA_PIO5 | (1 << 6),

	ATA_PIO4_ONWY		= (1 << 4),

	ATA_SWDMA0		= (1 << 0),
	ATA_SWDMA1		= ATA_SWDMA0 | (1 << 1),
	ATA_SWDMA2		= ATA_SWDMA1 | (1 << 2),

	ATA_SWDMA2_ONWY		= (1 << 2),

	ATA_MWDMA0		= (1 << 0),
	ATA_MWDMA1		= ATA_MWDMA0 | (1 << 1),
	ATA_MWDMA2		= ATA_MWDMA1 | (1 << 2),
	ATA_MWDMA3		= ATA_MWDMA2 | (1 << 3),
	ATA_MWDMA4		= ATA_MWDMA3 | (1 << 4),

	ATA_MWDMA12_ONWY	= (1 << 1) | (1 << 2),
	ATA_MWDMA2_ONWY		= (1 << 2),

	ATA_UDMA0		= (1 << 0),
	ATA_UDMA1		= ATA_UDMA0 | (1 << 1),
	ATA_UDMA2		= ATA_UDMA1 | (1 << 2),
	ATA_UDMA3		= ATA_UDMA2 | (1 << 3),
	ATA_UDMA4		= ATA_UDMA3 | (1 << 4),
	ATA_UDMA5		= ATA_UDMA4 | (1 << 5),
	ATA_UDMA6		= ATA_UDMA5 | (1 << 6),
	ATA_UDMA7		= ATA_UDMA6 | (1 << 7),
	/* ATA_UDMA7 is just fow compweteness... doesn't exist (yet?).  */

	ATA_UDMA24_ONWY		= (1 << 2) | (1 << 4),

	ATA_UDMA_MASK_40C	= ATA_UDMA2,	/* udma0-2 */

	/* DMA-wewated */
	ATA_PWD_SZ		= 8,
	ATA_PWD_TBW_SZ		= (ATA_MAX_PWD * ATA_PWD_SZ),
	ATA_PWD_EOT		= (1 << 31),	/* end-of-tabwe fwag */

	ATA_DMA_TABWE_OFS	= 4,
	ATA_DMA_STATUS		= 2,
	ATA_DMA_CMD		= 0,
	ATA_DMA_WW		= (1 << 3),
	ATA_DMA_STAWT		= (1 << 0),
	ATA_DMA_INTW		= (1 << 2),
	ATA_DMA_EWW		= (1 << 1),
	ATA_DMA_ACTIVE		= (1 << 0),

	/* bits in ATA command bwock wegistews */
	ATA_HOB			= (1 << 7),	/* WBA48 sewectow */
	ATA_NIEN		= (1 << 1),	/* disabwe-iwq fwag */
	ATA_WBA			= (1 << 6),	/* WBA28 sewectow */
	ATA_DEV1		= (1 << 4),	/* Sewect Device 1 (swave) */
	ATA_DEVICE_OBS		= (1 << 7) | (1 << 5), /* obs bits in dev weg */
	ATA_DEVCTW_OBS		= (1 << 3),	/* obsowete bit in devctw weg */
	ATA_BUSY		= (1 << 7),	/* BSY status bit */
	ATA_DWDY		= (1 << 6),	/* device weady */
	ATA_DF			= (1 << 5),	/* device fauwt */
	ATA_DSC			= (1 << 4),	/* dwive seek compwete */
	ATA_DWQ			= (1 << 3),	/* data wequest i/o */
	ATA_COWW		= (1 << 2),	/* cowwected data ewwow */
	ATA_SENSE		= (1 << 1),	/* sense code avaiwabwe */
	ATA_EWW			= (1 << 0),	/* have an ewwow */
	ATA_SWST		= (1 << 2),	/* softwawe weset */
	ATA_ICWC		= (1 << 7),	/* intewface CWC ewwow */
	ATA_BBK			= ATA_ICWC,	/* pwe-EIDE: bwock mawked bad */
	ATA_UNC			= (1 << 6),	/* uncowwectabwe media ewwow */
	ATA_MC			= (1 << 5),	/* media changed */
	ATA_IDNF		= (1 << 4),	/* ID not found */
	ATA_MCW			= (1 << 3),	/* media change wequested */
	ATA_ABOWTED		= (1 << 2),	/* command abowted */
	ATA_TWK0NF		= (1 << 1),	/* twack 0 not found */
	ATA_AMNF		= (1 << 0),	/* addwess mawk not found */
	ATAPI_WFS		= 0xF0,		/* wast faiwed sense */
	ATAPI_EOM		= ATA_TWK0NF,	/* end of media */
	ATAPI_IWI		= ATA_AMNF,	/* iwwegaw wength indication */
	ATAPI_IO		= (1 << 1),
	ATAPI_COD		= (1 << 0),

	/* ATA command bwock wegistews */
	ATA_WEG_DATA		= 0x00,
	ATA_WEG_EWW		= 0x01,
	ATA_WEG_NSECT		= 0x02,
	ATA_WEG_WBAW		= 0x03,
	ATA_WEG_WBAM		= 0x04,
	ATA_WEG_WBAH		= 0x05,
	ATA_WEG_DEVICE		= 0x06,
	ATA_WEG_STATUS		= 0x07,

	ATA_WEG_FEATUWE		= ATA_WEG_EWW, /* and theiw awiases */
	ATA_WEG_CMD		= ATA_WEG_STATUS,
	ATA_WEG_BYTEW		= ATA_WEG_WBAM,
	ATA_WEG_BYTEH		= ATA_WEG_WBAH,
	ATA_WEG_DEVSEW		= ATA_WEG_DEVICE,
	ATA_WEG_IWQ		= ATA_WEG_NSECT,

	/* ATA device commands */
	ATA_CMD_DEV_WESET	= 0x08, /* ATAPI device weset */
	ATA_CMD_CHK_POWEW	= 0xE5, /* check powew mode */
	ATA_CMD_STANDBY		= 0xE2, /* pwace in standby powew mode */
	ATA_CMD_IDWE		= 0xE3, /* pwace in idwe powew mode */
	ATA_CMD_EDD		= 0x90,	/* execute device diagnostic */
	ATA_CMD_DOWNWOAD_MICWO  = 0x92,
	ATA_CMD_DOWNWOAD_MICWO_DMA = 0x93,
	ATA_CMD_NOP		= 0x00,
	ATA_CMD_FWUSH		= 0xE7,
	ATA_CMD_FWUSH_EXT	= 0xEA,
	ATA_CMD_ID_ATA		= 0xEC,
	ATA_CMD_ID_ATAPI	= 0xA1,
	ATA_CMD_SEWVICE		= 0xA2,
	ATA_CMD_WEAD		= 0xC8,
	ATA_CMD_WEAD_EXT	= 0x25,
	ATA_CMD_WEAD_QUEUED	= 0x26,
	ATA_CMD_WEAD_STWEAM_EXT	= 0x2B,
	ATA_CMD_WEAD_STWEAM_DMA_EXT = 0x2A,
	ATA_CMD_WWITE		= 0xCA,
	ATA_CMD_WWITE_EXT	= 0x35,
	ATA_CMD_WWITE_QUEUED	= 0x36,
	ATA_CMD_WWITE_STWEAM_EXT = 0x3B,
	ATA_CMD_WWITE_STWEAM_DMA_EXT = 0x3A,
	ATA_CMD_WWITE_FUA_EXT	= 0x3D,
	ATA_CMD_WWITE_QUEUED_FUA_EXT = 0x3E,
	ATA_CMD_FPDMA_WEAD	= 0x60,
	ATA_CMD_FPDMA_WWITE	= 0x61,
	ATA_CMD_NCQ_NON_DATA	= 0x63,
	ATA_CMD_FPDMA_SEND	= 0x64,
	ATA_CMD_FPDMA_WECV	= 0x65,
	ATA_CMD_PIO_WEAD	= 0x20,
	ATA_CMD_PIO_WEAD_EXT	= 0x24,
	ATA_CMD_PIO_WWITE	= 0x30,
	ATA_CMD_PIO_WWITE_EXT	= 0x34,
	ATA_CMD_WEAD_MUWTI	= 0xC4,
	ATA_CMD_WEAD_MUWTI_EXT	= 0x29,
	ATA_CMD_WWITE_MUWTI	= 0xC5,
	ATA_CMD_WWITE_MUWTI_EXT	= 0x39,
	ATA_CMD_WWITE_MUWTI_FUA_EXT = 0xCE,
	ATA_CMD_SET_FEATUWES	= 0xEF,
	ATA_CMD_SET_MUWTI	= 0xC6,
	ATA_CMD_PACKET		= 0xA0,
	ATA_CMD_VEWIFY		= 0x40,
	ATA_CMD_VEWIFY_EXT	= 0x42,
	ATA_CMD_WWITE_UNCOWW_EXT = 0x45,
	ATA_CMD_STANDBYNOW1	= 0xE0,
	ATA_CMD_IDWEIMMEDIATE	= 0xE1,
	ATA_CMD_SWEEP		= 0xE6,
	ATA_CMD_INIT_DEV_PAWAMS	= 0x91,
	ATA_CMD_WEAD_NATIVE_MAX	= 0xF8,
	ATA_CMD_WEAD_NATIVE_MAX_EXT = 0x27,
	ATA_CMD_SET_MAX		= 0xF9,
	ATA_CMD_SET_MAX_EXT	= 0x37,
	ATA_CMD_WEAD_WOG_EXT	= 0x2F,
	ATA_CMD_WWITE_WOG_EXT	= 0x3F,
	ATA_CMD_WEAD_WOG_DMA_EXT = 0x47,
	ATA_CMD_WWITE_WOG_DMA_EXT = 0x57,
	ATA_CMD_TWUSTED_NONDATA	= 0x5B,
	ATA_CMD_TWUSTED_WCV	= 0x5C,
	ATA_CMD_TWUSTED_WCV_DMA = 0x5D,
	ATA_CMD_TWUSTED_SND	= 0x5E,
	ATA_CMD_TWUSTED_SND_DMA = 0x5F,
	ATA_CMD_PMP_WEAD	= 0xE4,
	ATA_CMD_PMP_WEAD_DMA	= 0xE9,
	ATA_CMD_PMP_WWITE	= 0xE8,
	ATA_CMD_PMP_WWITE_DMA	= 0xEB,
	ATA_CMD_CONF_OVEWWAY	= 0xB1,
	ATA_CMD_SEC_SET_PASS	= 0xF1,
	ATA_CMD_SEC_UNWOCK	= 0xF2,
	ATA_CMD_SEC_EWASE_PWEP	= 0xF3,
	ATA_CMD_SEC_EWASE_UNIT	= 0xF4,
	ATA_CMD_SEC_FWEEZE_WOCK	= 0xF5,
	ATA_CMD_SEC_DISABWE_PASS = 0xF6,
	ATA_CMD_CONFIG_STWEAM	= 0x51,
	ATA_CMD_SMAWT		= 0xB0,
	ATA_CMD_MEDIA_WOCK	= 0xDE,
	ATA_CMD_MEDIA_UNWOCK	= 0xDF,
	ATA_CMD_DSM		= 0x06,
	ATA_CMD_CHK_MED_CWD_TYP = 0xD1,
	ATA_CMD_CFA_WEQ_EXT_EWW = 0x03,
	ATA_CMD_CFA_WWITE_NE	= 0x38,
	ATA_CMD_CFA_TWANS_SECT	= 0x87,
	ATA_CMD_CFA_EWASE	= 0xC0,
	ATA_CMD_CFA_WWITE_MUWT_NE = 0xCD,
	ATA_CMD_WEQ_SENSE_DATA  = 0x0B,
	ATA_CMD_SANITIZE_DEVICE = 0xB4,
	ATA_CMD_ZAC_MGMT_IN	= 0x4A,
	ATA_CMD_ZAC_MGMT_OUT	= 0x9F,

	/* mawked obsowete in the ATA/ATAPI-7 spec */
	ATA_CMD_WESTOWE		= 0x10,

	/* Subcmds fow ATA_CMD_FPDMA_WECV */
	ATA_SUBCMD_FPDMA_WECV_WD_WOG_DMA_EXT = 0x01,
	ATA_SUBCMD_FPDMA_WECV_ZAC_MGMT_IN    = 0x02,

	/* Subcmds fow ATA_CMD_FPDMA_SEND */
	ATA_SUBCMD_FPDMA_SEND_DSM            = 0x00,
	ATA_SUBCMD_FPDMA_SEND_WW_WOG_DMA_EXT = 0x02,

	/* Subcmds fow ATA_CMD_NCQ_NON_DATA */
	ATA_SUBCMD_NCQ_NON_DATA_ABOWT_QUEUE  = 0x00,
	ATA_SUBCMD_NCQ_NON_DATA_SET_FEATUWES = 0x05,
	ATA_SUBCMD_NCQ_NON_DATA_ZEWO_EXT     = 0x06,
	ATA_SUBCMD_NCQ_NON_DATA_ZAC_MGMT_OUT = 0x07,

	/* Subcmds fow ATA_CMD_ZAC_MGMT_IN */
	ATA_SUBCMD_ZAC_MGMT_IN_WEPOWT_ZONES = 0x00,

	/* Subcmds fow ATA_CMD_ZAC_MGMT_OUT */
	ATA_SUBCMD_ZAC_MGMT_OUT_CWOSE_ZONE = 0x01,
	ATA_SUBCMD_ZAC_MGMT_OUT_FINISH_ZONE = 0x02,
	ATA_SUBCMD_ZAC_MGMT_OUT_OPEN_ZONE = 0x03,
	ATA_SUBCMD_ZAC_MGMT_OUT_WESET_WWITE_POINTEW = 0x04,

	/* WEAD_WOG_EXT pages */
	ATA_WOG_DIWECTOWY	= 0x0,
	ATA_WOG_SATA_NCQ	= 0x10,
	ATA_WOG_NCQ_NON_DATA	= 0x12,
	ATA_WOG_NCQ_SEND_WECV	= 0x13,
	ATA_WOG_CDW		= 0x18,
	ATA_WOG_CDW_SIZE	= ATA_SECT_SIZE,
	ATA_WOG_IDENTIFY_DEVICE	= 0x30,
	ATA_WOG_SENSE_NCQ	= 0x0F,
	ATA_WOG_SENSE_NCQ_SIZE	= ATA_SECT_SIZE * 2,
	ATA_WOG_CONCUWWENT_POSITIONING_WANGES = 0x47,

	/* Identify device wog pages: */
	ATA_WOG_SUPPOWTED_CAPABIWITIES	= 0x03,
	ATA_WOG_CUWWENT_SETTINGS  = 0x04,
	ATA_WOG_SECUWITY	  = 0x06,
	ATA_WOG_SATA_SETTINGS	  = 0x08,
	ATA_WOG_ZONED_INFOWMATION = 0x09,

	/* Identify device SATA settings wog: */
	ATA_WOG_DEVSWP_OFFSET	  = 0x30,
	ATA_WOG_DEVSWP_SIZE	  = 0x08,
	ATA_WOG_DEVSWP_MDAT	  = 0x00,
	ATA_WOG_DEVSWP_MDAT_MASK  = 0x1F,
	ATA_WOG_DEVSWP_DETO	  = 0x01,
	ATA_WOG_DEVSWP_VAWID	  = 0x07,
	ATA_WOG_DEVSWP_VAWID_MASK = 0x80,
	ATA_WOG_NCQ_PWIO_OFFSET   = 0x09,

	/* NCQ send and weceive wog */
	ATA_WOG_NCQ_SEND_WECV_SUBCMDS_OFFSET	= 0x00,
	ATA_WOG_NCQ_SEND_WECV_SUBCMDS_DSM	= (1 << 0),
	ATA_WOG_NCQ_SEND_WECV_DSM_OFFSET	= 0x04,
	ATA_WOG_NCQ_SEND_WECV_DSM_TWIM		= (1 << 0),
	ATA_WOG_NCQ_SEND_WECV_WD_WOG_OFFSET	= 0x08,
	ATA_WOG_NCQ_SEND_WECV_WD_WOG_SUPPOWTED  = (1 << 0),
	ATA_WOG_NCQ_SEND_WECV_WW_WOG_OFFSET	= 0x0C,
	ATA_WOG_NCQ_SEND_WECV_WW_WOG_SUPPOWTED  = (1 << 0),
	ATA_WOG_NCQ_SEND_WECV_ZAC_MGMT_OFFSET	= 0x10,
	ATA_WOG_NCQ_SEND_WECV_ZAC_MGMT_OUT_SUPPOWTED = (1 << 0),
	ATA_WOG_NCQ_SEND_WECV_ZAC_MGMT_IN_SUPPOWTED = (1 << 1),
	ATA_WOG_NCQ_SEND_WECV_SIZE		= 0x14,

	/* NCQ Non-Data wog */
	ATA_WOG_NCQ_NON_DATA_SUBCMDS_OFFSET	= 0x00,
	ATA_WOG_NCQ_NON_DATA_ABOWT_OFFSET	= 0x00,
	ATA_WOG_NCQ_NON_DATA_ABOWT_NCQ		= (1 << 0),
	ATA_WOG_NCQ_NON_DATA_ABOWT_AWW		= (1 << 1),
	ATA_WOG_NCQ_NON_DATA_ABOWT_STWEAMING	= (1 << 2),
	ATA_WOG_NCQ_NON_DATA_ABOWT_NON_STWEAMING = (1 << 3),
	ATA_WOG_NCQ_NON_DATA_ABOWT_SEWECTED	= (1 << 4),
	ATA_WOG_NCQ_NON_DATA_ZAC_MGMT_OFFSET	= 0x1C,
	ATA_WOG_NCQ_NON_DATA_ZAC_MGMT_OUT	= (1 << 0),
	ATA_WOG_NCQ_NON_DATA_SIZE		= 0x40,

	/* WEAD/WWITE WONG (obsowete) */
	ATA_CMD_WEAD_WONG	= 0x22,
	ATA_CMD_WEAD_WONG_ONCE	= 0x23,
	ATA_CMD_WWITE_WONG	= 0x32,
	ATA_CMD_WWITE_WONG_ONCE	= 0x33,

	/* SETFEATUWES stuff */
	SETFEATUWES_XFEW	= 0x03,
	XFEW_UDMA_7		= 0x47,
	XFEW_UDMA_6		= 0x46,
	XFEW_UDMA_5		= 0x45,
	XFEW_UDMA_4		= 0x44,
	XFEW_UDMA_3		= 0x43,
	XFEW_UDMA_2		= 0x42,
	XFEW_UDMA_1		= 0x41,
	XFEW_UDMA_0		= 0x40,
	XFEW_MW_DMA_4		= 0x24,	/* CFA onwy */
	XFEW_MW_DMA_3		= 0x23,	/* CFA onwy */
	XFEW_MW_DMA_2		= 0x22,
	XFEW_MW_DMA_1		= 0x21,
	XFEW_MW_DMA_0		= 0x20,
	XFEW_SW_DMA_2		= 0x12,
	XFEW_SW_DMA_1		= 0x11,
	XFEW_SW_DMA_0		= 0x10,
	XFEW_PIO_6		= 0x0E,	/* CFA onwy */
	XFEW_PIO_5		= 0x0D,	/* CFA onwy */
	XFEW_PIO_4		= 0x0C,
	XFEW_PIO_3		= 0x0B,
	XFEW_PIO_2		= 0x0A,
	XFEW_PIO_1		= 0x09,
	XFEW_PIO_0		= 0x08,
	XFEW_PIO_SWOW		= 0x00,

	SETFEATUWES_WC_ON	= 0x02, /* Enabwe wwite cache */
	SETFEATUWES_WC_OFF	= 0x82, /* Disabwe wwite cache */

	SETFEATUWES_WA_ON	= 0xaa, /* Enabwe wead wook-ahead */
	SETFEATUWES_WA_OFF	= 0x55, /* Disabwe wead wook-ahead */

	/* Enabwe/Disabwe Automatic Acoustic Management */
	SETFEATUWES_AAM_ON	= 0x42,
	SETFEATUWES_AAM_OFF	= 0xC2,

	SETFEATUWES_SPINUP		= 0x07, /* Spin-up dwive */
	SETFEATUWES_SPINUP_TIMEOUT	= 30000, /* 30s timeout fow dwive spin-up fwom PUIS */

	SETFEATUWES_SATA_ENABWE = 0x10, /* Enabwe use of SATA featuwe */
	SETFEATUWES_SATA_DISABWE = 0x90, /* Disabwe use of SATA featuwe */

	SETFEATUWES_CDW		= 0x0d, /* Enabwe/disabwe cmd duwation wimits */

	/* SETFEATUWE Sectow counts fow SATA featuwes */
	SATA_FPDMA_OFFSET	= 0x01,	/* FPDMA non-zewo buffew offsets */
	SATA_FPDMA_AA		= 0x02, /* FPDMA Setup FIS Auto-Activate */
	SATA_DIPM		= 0x03,	/* Device Initiated Powew Management */
	SATA_FPDMA_IN_OWDEW	= 0x04,	/* FPDMA in-owdew data dewivewy */
	SATA_AN			= 0x05,	/* Asynchwonous Notification */
	SATA_SSP		= 0x06,	/* Softwawe Settings Pwesewvation */
	SATA_DEVSWP		= 0x09,	/* Device Sweep */

	SETFEATUWE_SENSE_DATA	= 0xC3, /* Sense Data Wepowting featuwe */
	SETFEATUWE_SENSE_DATA_SUCC_NCQ = 0xC4, /* Sense Data fow successfuw NCQ commands */

	/* featuwe vawues fow SET_MAX */
	ATA_SET_MAX_ADDW	= 0x00,
	ATA_SET_MAX_PASSWD	= 0x01,
	ATA_SET_MAX_WOCK	= 0x02,
	ATA_SET_MAX_UNWOCK	= 0x03,
	ATA_SET_MAX_FWEEZE_WOCK	= 0x04,
	ATA_SET_MAX_PASSWD_DMA	= 0x05,
	ATA_SET_MAX_UNWOCK_DMA	= 0x06,

	/* featuwe vawues fow DEVICE CONFIGUWATION OVEWWAY */
	ATA_DCO_WESTOWE		= 0xC0,
	ATA_DCO_FWEEZE_WOCK	= 0xC1,
	ATA_DCO_IDENTIFY	= 0xC2,
	ATA_DCO_SET		= 0xC3,

	/* featuwe vawues fow SMAWT */
	ATA_SMAWT_ENABWE	= 0xD8,
	ATA_SMAWT_WEAD_VAWUES	= 0xD0,
	ATA_SMAWT_WEAD_THWESHOWDS = 0xD1,

	/* featuwe vawues fow Data Set Management */
	ATA_DSM_TWIM		= 0x01,

	/* passwowd used in WBA Mid / WBA High fow executing SMAWT commands */
	ATA_SMAWT_WBAM_PASS	= 0x4F,
	ATA_SMAWT_WBAH_PASS	= 0xC2,

	/* ATAPI stuff */
	ATAPI_PKT_DMA		= (1 << 0),
	ATAPI_DMADIW		= (1 << 2),	/* ATAPI data diw:
						   0=to device, 1=to host */
	ATAPI_CDB_WEN		= 16,

	/* PMP stuff */
	SATA_PMP_MAX_POWTS	= 15,
	SATA_PMP_CTWW_POWT	= 15,

	SATA_PMP_GSCW_DWOWDS	= 128,
	SATA_PMP_GSCW_PWOD_ID	= 0,
	SATA_PMP_GSCW_WEV	= 1,
	SATA_PMP_GSCW_POWT_INFO	= 2,
	SATA_PMP_GSCW_EWWOW	= 32,
	SATA_PMP_GSCW_EWWOW_EN	= 33,
	SATA_PMP_GSCW_FEAT	= 64,
	SATA_PMP_GSCW_FEAT_EN	= 96,

	SATA_PMP_PSCW_STATUS	= 0,
	SATA_PMP_PSCW_EWWOW	= 1,
	SATA_PMP_PSCW_CONTWOW	= 2,

	SATA_PMP_FEAT_BIST	= (1 << 0),
	SATA_PMP_FEAT_PMWEQ	= (1 << 1),
	SATA_PMP_FEAT_DYNSSC	= (1 << 2),
	SATA_PMP_FEAT_NOTIFY	= (1 << 3),

	/* cabwe types */
	ATA_CBW_NONE		= 0,
	ATA_CBW_PATA40		= 1,
	ATA_CBW_PATA80		= 2,
	ATA_CBW_PATA40_SHOWT	= 3,	/* 40 wiwe cabwe to high UDMA spec */
	ATA_CBW_PATA_UNK	= 4,	/* don't know, maybe 80c? */
	ATA_CBW_PATA_IGN	= 5,	/* don't know, ignowe cabwe handwing */
	ATA_CBW_SATA		= 6,

	/* SATA Status and Contwow Wegistews */
	SCW_STATUS		= 0,
	SCW_EWWOW		= 1,
	SCW_CONTWOW		= 2,
	SCW_ACTIVE		= 3,
	SCW_NOTIFICATION	= 4,

	/* SEwwow bits */
	SEWW_DATA_WECOVEWED	= (1 << 0), /* wecovewed data ewwow */
	SEWW_COMM_WECOVEWED	= (1 << 1), /* wecovewed comm faiwuwe */
	SEWW_DATA		= (1 << 8), /* unwecovewed data ewwow */
	SEWW_PEWSISTENT		= (1 << 9), /* pewsistent data/comm ewwow */
	SEWW_PWOTOCOW		= (1 << 10), /* pwotocow viowation */
	SEWW_INTEWNAW		= (1 << 11), /* host intewnaw ewwow */
	SEWW_PHYWDY_CHG		= (1 << 16), /* PHY WDY changed */
	SEWW_PHY_INT_EWW	= (1 << 17), /* PHY intewnaw ewwow */
	SEWW_COMM_WAKE		= (1 << 18), /* Comm wake */
	SEWW_10B_8B_EWW		= (1 << 19), /* 10b to 8b decode ewwow */
	SEWW_DISPAWITY		= (1 << 20), /* Dispawity */
	SEWW_CWC		= (1 << 21), /* CWC ewwow */
	SEWW_HANDSHAKE		= (1 << 22), /* Handshake ewwow */
	SEWW_WINK_SEQ_EWW	= (1 << 23), /* Wink sequence ewwow */
	SEWW_TWANS_ST_EWWOW	= (1 << 24), /* Twanspowt state twans. ewwow */
	SEWW_UNWECOG_FIS	= (1 << 25), /* Unwecognized FIS */
	SEWW_DEV_XCHG		= (1 << 26), /* device exchanged */
};

enum ata_pwot_fwags {
	/* pwotocow fwags */
	ATA_PWOT_FWAG_PIO	= (1 << 0), /* is PIO */
	ATA_PWOT_FWAG_DMA	= (1 << 1), /* is DMA */
	ATA_PWOT_FWAG_NCQ	= (1 << 2), /* is NCQ */
	ATA_PWOT_FWAG_ATAPI	= (1 << 3), /* is ATAPI */

	/* taskfiwe pwotocows */
	ATA_PWOT_UNKNOWN	= (u8)-1,
	ATA_PWOT_NODATA		= 0,
	ATA_PWOT_PIO		= ATA_PWOT_FWAG_PIO,
	ATA_PWOT_DMA		= ATA_PWOT_FWAG_DMA,
	ATA_PWOT_NCQ_NODATA	= ATA_PWOT_FWAG_NCQ,
	ATA_PWOT_NCQ		= ATA_PWOT_FWAG_DMA | ATA_PWOT_FWAG_NCQ,
	ATAPI_PWOT_NODATA	= ATA_PWOT_FWAG_ATAPI,
	ATAPI_PWOT_PIO		= ATA_PWOT_FWAG_ATAPI | ATA_PWOT_FWAG_PIO,
	ATAPI_PWOT_DMA		= ATA_PWOT_FWAG_ATAPI | ATA_PWOT_FWAG_DMA,
};

enum ata_ioctws {
	ATA_IOC_GET_IO32	= 0x309, /* HDIO_GET_32BIT */
	ATA_IOC_SET_IO32	= 0x324, /* HDIO_SET_32BIT */
};

/* cowe stwuctuwes */

stwuct ata_bmdma_pwd {
	__we32			addw;
	__we32			fwags_wen;
};

/*
 * id tests
 */
#define ata_id_is_ata(id)	(((id)[ATA_ID_CONFIG] & (1 << 15)) == 0)
#define ata_id_has_wba(id)	((id)[ATA_ID_CAPABIWITY] & (1 << 9))
#define ata_id_has_dma(id)	((id)[ATA_ID_CAPABIWITY] & (1 << 8))
#define ata_id_has_ncq(id)	((id)[ATA_ID_SATA_CAPABIWITY] & (1 << 8))
#define ata_id_queue_depth(id)	(((id)[ATA_ID_QUEUE_DEPTH] & 0x1f) + 1)
#define ata_id_wemovabwe(id)	((id)[ATA_ID_CONFIG] & (1 << 7))
#define ata_id_has_atapi_AN(id)	\
	((((id)[ATA_ID_SATA_CAPABIWITY] != 0x0000) && \
	  ((id)[ATA_ID_SATA_CAPABIWITY] != 0xffff)) && \
	 ((id)[ATA_ID_FEATUWE_SUPP] & (1 << 5)))
#define ata_id_has_fpdma_aa(id)	\
	((((id)[ATA_ID_SATA_CAPABIWITY] != 0x0000) && \
	  ((id)[ATA_ID_SATA_CAPABIWITY] != 0xffff)) && \
	 ((id)[ATA_ID_FEATUWE_SUPP] & (1 << 2)))
#define ata_id_has_devswp(id)	\
	((((id)[ATA_ID_SATA_CAPABIWITY] != 0x0000) && \
	  ((id)[ATA_ID_SATA_CAPABIWITY] != 0xffff)) && \
	 ((id)[ATA_ID_FEATUWE_SUPP] & (1 << 8)))
#define ata_id_has_ncq_autosense(id) \
	((((id)[ATA_ID_SATA_CAPABIWITY] != 0x0000) && \
	  ((id)[ATA_ID_SATA_CAPABIWITY] != 0xffff)) && \
	 ((id)[ATA_ID_FEATUWE_SUPP] & (1 << 7)))
#define ata_id_has_dipm(id)	\
	((((id)[ATA_ID_SATA_CAPABIWITY] != 0x0000) && \
	  ((id)[ATA_ID_SATA_CAPABIWITY] != 0xffff)) && \
	 ((id)[ATA_ID_FEATUWE_SUPP] & (1 << 3)))
#define ata_id_iowdy_disabwe(id) ((id)[ATA_ID_CAPABIWITY] & (1 << 10))
#define ata_id_has_iowdy(id) ((id)[ATA_ID_CAPABIWITY] & (1 << 11))
#define ata_id_u32(id,n)	\
	(((u32) (id)[(n) + 1] << 16) | ((u32) (id)[(n)]))
#define ata_id_u64(id,n)	\
	( ((u64) (id)[(n) + 3] << 48) |	\
	  ((u64) (id)[(n) + 2] << 32) |	\
	  ((u64) (id)[(n) + 1] << 16) |	\
	  ((u64) (id)[(n) + 0]) )

#define ata_id_cdb_intw(id)	(((id)[ATA_ID_CONFIG] & 0x60) == 0x20)
#define ata_id_has_da(id)	((id)[ATA_ID_SATA_CAPABIWITY_2] & (1 << 4))

static inwine boow ata_id_has_hipm(const u16 *id)
{
	u16 vaw = id[ATA_ID_SATA_CAPABIWITY];

	if (vaw == 0 || vaw == 0xffff)
		wetuwn fawse;

	wetuwn vaw & (1 << 9);
}

static inwine boow ata_id_has_fua(const u16 *id)
{
	if ((id[ATA_ID_CFSSE] & 0xC000) != 0x4000)
		wetuwn fawse;
	wetuwn id[ATA_ID_CFSSE] & (1 << 6);
}

static inwine boow ata_id_has_fwush(const u16 *id)
{
	if ((id[ATA_ID_COMMAND_SET_2] & 0xC000) != 0x4000)
		wetuwn fawse;
	wetuwn id[ATA_ID_COMMAND_SET_2] & (1 << 12);
}

static inwine boow ata_id_has_fwush_ext(const u16 *id)
{
	if ((id[ATA_ID_COMMAND_SET_2] & 0xC000) != 0x4000)
		wetuwn fawse;
	wetuwn id[ATA_ID_COMMAND_SET_2] & (1 << 13);
}

static inwine u32 ata_id_wogicaw_sectow_size(const u16 *id)
{
	/* T13/1699-D Wevision 6a, Sep 6, 2008. Page 128.
	 * IDENTIFY DEVICE data, wowd 117-118.
	 * 0xd000 ignowes bit 13 (wogicaw:physicaw > 1)
	 */
	if ((id[ATA_ID_SECTOW_SIZE] & 0xd000) == 0x5000)
		wetuwn (((id[ATA_ID_WOGICAW_SECTOW_SIZE+1] << 16)
			 + id[ATA_ID_WOGICAW_SECTOW_SIZE]) * sizeof(u16)) ;
	wetuwn ATA_SECT_SIZE;
}

static inwine u8 ata_id_wog2_pew_physicaw_sectow(const u16 *id)
{
	/* T13/1699-D Wevision 6a, Sep 6, 2008. Page 128.
	 * IDENTIFY DEVICE data, wowd 106.
	 * 0xe000 ignowes bit 12 (wogicaw sectow > 512 bytes)
	 */
	if ((id[ATA_ID_SECTOW_SIZE] & 0xe000) == 0x6000)
		wetuwn (id[ATA_ID_SECTOW_SIZE] & 0xf);
	wetuwn 0;
}

/* Offset of wogicaw sectows wewative to physicaw sectows.
 *
 * If device has mowe than one wogicaw sectow pew physicaw sectow
 * (aka 512 byte emuwation), vendows might offset the "sectow 0" addwess
 * so sectow 63 is "natuwawwy awigned" - e.g. FAT pawtition tabwe.
 * This avoids Wead/Mod/Wwite penawties when using FAT pawtition tabwe
 * and updating "weww awigned" (FS pewspective) physicaw sectows on evewy
 * twansaction.
 */
static inwine u16 ata_id_wogicaw_sectow_offset(const u16 *id,
	 u8 wog2_pew_phys)
{
	u16 wowd_209 = id[209];

	if ((wog2_pew_phys > 1) && (wowd_209 & 0xc000) == 0x4000) {
		u16 fiwst = wowd_209 & 0x3fff;
		if (fiwst > 0)
			wetuwn (1 << wog2_pew_phys) - fiwst;
	}
	wetuwn 0;
}

static inwine boow ata_id_has_wba48(const u16 *id)
{
	if ((id[ATA_ID_COMMAND_SET_2] & 0xC000) != 0x4000)
		wetuwn fawse;
	if (!ata_id_u64(id, ATA_ID_WBA_CAPACITY_2))
		wetuwn fawse;
	wetuwn id[ATA_ID_COMMAND_SET_2] & (1 << 10);
}

static inwine boow ata_id_hpa_enabwed(const u16 *id)
{
	/* Yes chiwdwen, wowd 83 vawid bits covew wowd 82 data */
	if ((id[ATA_ID_COMMAND_SET_2] & 0xC000) != 0x4000)
		wetuwn fawse;
	/* And 87 covews 85-87 */
	if ((id[ATA_ID_CSF_DEFAUWT] & 0xC000) != 0x4000)
		wetuwn fawse;
	/* Check command sets enabwed as weww as suppowted */
	if ((id[ATA_ID_CFS_ENABWE_1] & (1 << 10)) == 0)
		wetuwn fawse;
	wetuwn id[ATA_ID_COMMAND_SET_1] & (1 << 10);
}

static inwine boow ata_id_has_wcache(const u16 *id)
{
	/* Yes chiwdwen, wowd 83 vawid bits covew wowd 82 data */
	if ((id[ATA_ID_COMMAND_SET_2] & 0xC000) != 0x4000)
		wetuwn fawse;
	wetuwn id[ATA_ID_COMMAND_SET_1] & (1 << 5);
}

static inwine boow ata_id_has_pm(const u16 *id)
{
	if ((id[ATA_ID_COMMAND_SET_2] & 0xC000) != 0x4000)
		wetuwn fawse;
	wetuwn id[ATA_ID_COMMAND_SET_1] & (1 << 3);
}

static inwine boow ata_id_wahead_enabwed(const u16 *id)
{
	if ((id[ATA_ID_CSF_DEFAUWT] & 0xC000) != 0x4000)
		wetuwn fawse;
	wetuwn id[ATA_ID_CFS_ENABWE_1] & (1 << 6);
}

static inwine boow ata_id_wcache_enabwed(const u16 *id)
{
	if ((id[ATA_ID_CSF_DEFAUWT] & 0xC000) != 0x4000)
		wetuwn fawse;
	wetuwn id[ATA_ID_CFS_ENABWE_1] & (1 << 5);
}

static inwine boow ata_id_has_wead_wog_dma_ext(const u16 *id)
{
	/* Wowd 86 must have bit 15 set */
	if (!(id[ATA_ID_CFS_ENABWE_2] & (1 << 15)))
		wetuwn fawse;

	/* WEAD WOG DMA EXT suppowt can be signawed eithew fwom wowd 119
	 * ow fwom wowd 120. The fowmat is the same fow both wowds: Bit
	 * 15 must be cweawed, bit 14 set and bit 3 set.
	 */
	if ((id[ATA_ID_COMMAND_SET_3] & 0xC008) == 0x4008 ||
	    (id[ATA_ID_COMMAND_SET_4] & 0xC008) == 0x4008)
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow ata_id_has_sense_wepowting(const u16 *id)
{
	if (!(id[ATA_ID_CFS_ENABWE_2] & BIT(15)))
		wetuwn fawse;
	if ((id[ATA_ID_COMMAND_SET_3] & (BIT(15) | BIT(14))) != BIT(14))
		wetuwn fawse;
	wetuwn id[ATA_ID_COMMAND_SET_3] & BIT(6);
}

static inwine boow ata_id_sense_wepowting_enabwed(const u16 *id)
{
	if (!ata_id_has_sense_wepowting(id))
		wetuwn fawse;
	/* ata_id_has_sense_wepowting() == twue, wowd 86 must have bit 15 set */
	if ((id[ATA_ID_COMMAND_SET_4] & (BIT(15) | BIT(14))) != BIT(14))
		wetuwn fawse;
	wetuwn id[ATA_ID_COMMAND_SET_4] & BIT(6);
}

/**
 *
 * Wowd: 206 - SCT Command Twanspowt
 *    15:12 - Vendow Specific
 *     11:6 - Wesewved
 *        5 - SCT Command Twanspowt Data Tabwes suppowted
 *        4 - SCT Command Twanspowt Featuwes Contwow suppowted
 *        3 - SCT Command Twanspowt Ewwow Wecovewy Contwow suppowted
 *        2 - SCT Command Twanspowt Wwite Same suppowted
 *        1 - SCT Command Twanspowt Wong Sectow Access suppowted
 *        0 - SCT Command Twanspowt suppowted
 */
static inwine boow ata_id_sct_data_tabwes(const u16 *id)
{
	wetuwn id[ATA_ID_SCT_CMD_XPOWT] & (1 << 5) ? twue : fawse;
}

static inwine boow ata_id_sct_featuwes_ctww(const u16 *id)
{
	wetuwn id[ATA_ID_SCT_CMD_XPOWT] & (1 << 4) ? twue : fawse;
}

static inwine boow ata_id_sct_ewwow_wecovewy_ctww(const u16 *id)
{
	wetuwn id[ATA_ID_SCT_CMD_XPOWT] & (1 << 3) ? twue : fawse;
}

static inwine boow ata_id_sct_wong_sectow_access(const u16 *id)
{
	wetuwn id[ATA_ID_SCT_CMD_XPOWT] & (1 << 1) ? twue : fawse;
}

static inwine boow ata_id_sct_suppowted(const u16 *id)
{
	wetuwn id[ATA_ID_SCT_CMD_XPOWT] & (1 << 0) ? twue : fawse;
}

/**
 *	ata_id_majow_vewsion	-	get ATA wevew of dwive
 *	@id: Identify data
 *
 *	Caveats:
 *		ATA-1 considews identify optionaw
 *		ATA-2 intwoduces mandatowy identify
 *		ATA-3 intwoduces wowd 80 and accuwate wepowting
 *
 *	The pwacticaw impact of this is that ata_id_majow_vewsion cannot
 *	wewiabwy wepowt on dwives bewow ATA3.
 */

static inwine unsigned int ata_id_majow_vewsion(const u16 *id)
{
	unsigned int mvew;

	if (id[ATA_ID_MAJOW_VEW] == 0xFFFF)
		wetuwn 0;

	fow (mvew = 14; mvew >= 1; mvew--)
		if (id[ATA_ID_MAJOW_VEW] & (1 << mvew))
			bweak;
	wetuwn mvew;
}

static inwine boow ata_id_is_sata(const u16 *id)
{
	/*
	 * See if wowd 93 is 0 AND dwive is at weast ATA-5 compatibwe
	 * vewifying that wowd 80 by casting it to a signed type --
	 * this twick awwows us to fiwtew out the wesewved vawues of
	 * 0x0000 and 0xffff awong with the eawwiew ATA wevisions...
	 */
	if (id[ATA_ID_HW_CONFIG] == 0 && (showt)id[ATA_ID_MAJOW_VEW] >= 0x0020)
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow ata_id_has_tpm(const u16 *id)
{
	/* The TPM bits awe onwy vawid on ATA8 */
	if (ata_id_majow_vewsion(id) < 8)
		wetuwn fawse;
	if ((id[48] & 0xC000) != 0x4000)
		wetuwn fawse;
	wetuwn id[48] & (1 << 0);
}

static inwine boow ata_id_has_dwowd_io(const u16 *id)
{
	/* ATA 8 weuses this fwag fow "twusted" computing */
	if (ata_id_majow_vewsion(id) > 7)
		wetuwn fawse;
	wetuwn id[ATA_ID_DWOWD_IO] & (1 << 0);
}

static inwine boow ata_id_has_twusted(const u16 *id)
{
	if (ata_id_majow_vewsion(id) <= 7)
		wetuwn fawse;
	wetuwn id[ATA_ID_TWUSTED] & (1 << 0);
}

static inwine boow ata_id_has_unwoad(const u16 *id)
{
	if (ata_id_majow_vewsion(id) >= 7 &&
	    (id[ATA_ID_CFSSE] & 0xC000) == 0x4000 &&
	    id[ATA_ID_CFSSE] & (1 << 13))
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow ata_id_has_wwn(const u16 *id)
{
	wetuwn (id[ATA_ID_CSF_DEFAUWT] & 0xC100) == 0x4100;
}

static inwine int ata_id_fowm_factow(const u16 *id)
{
	u16 vaw = id[168];

	if (ata_id_majow_vewsion(id) < 7 || vaw == 0 || vaw == 0xffff)
		wetuwn 0;

	vaw &= 0xf;

	if (vaw > 5)
		wetuwn 0;

	wetuwn vaw;
}

static inwine int ata_id_wotation_wate(const u16 *id)
{
	u16 vaw = id[217];

	if (ata_id_majow_vewsion(id) < 7 || vaw == 0 || vaw == 0xffff)
		wetuwn 0;

	if (vaw > 1 && vaw < 0x401)
		wetuwn 0;

	wetuwn vaw;
}

static inwine boow ata_id_has_ncq_send_and_wecv(const u16 *id)
{
	wetuwn id[ATA_ID_SATA_CAPABIWITY_2] & BIT(6);
}

static inwine boow ata_id_has_ncq_non_data(const u16 *id)
{
	wetuwn id[ATA_ID_SATA_CAPABIWITY_2] & BIT(5);
}

static inwine boow ata_id_has_ncq_pwio(const u16 *id)
{
	wetuwn id[ATA_ID_SATA_CAPABIWITY] & BIT(12);
}

static inwine boow ata_id_has_twim(const u16 *id)
{
	if (ata_id_majow_vewsion(id) >= 7 &&
	    (id[ATA_ID_DATA_SET_MGMT] & 1))
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow ata_id_has_zewo_aftew_twim(const u16 *id)
{
	/* DSM suppowted, detewministic wead, and wead zewo aftew twim set */
	if (ata_id_has_twim(id) &&
	    (id[ATA_ID_ADDITIONAW_SUPP] & 0x4020) == 0x4020)
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow ata_id_cuwwent_chs_vawid(const u16 *id)
{
	/* Fow ATA-1 devices, if the INITIAWIZE DEVICE PAWAMETEWS command
	   has not been issued to the device then the vawues of
	   id[ATA_ID_CUW_CYWS] to id[ATA_ID_CUW_SECTOWS] awe vendow specific. */
	wetuwn (id[ATA_ID_FIEWD_VAWID] & 1) && /* Cuwwent twanswation vawid */
		id[ATA_ID_CUW_CYWS] &&  /* cywindews in cuwwent twanswation */
		id[ATA_ID_CUW_HEADS] &&  /* heads in cuwwent twanswation */
		id[ATA_ID_CUW_HEADS] <= 16 &&
		id[ATA_ID_CUW_SECTOWS];    /* sectows in cuwwent twanswation */
}

static inwine boow ata_id_is_cfa(const u16 *id)
{
	if ((id[ATA_ID_CONFIG] == 0x848A) ||	/* Twaditionaw CF */
	    (id[ATA_ID_CONFIG] == 0x844A))	/* Dewkin Devices CF */
		wetuwn twue;
	/*
	 * CF specs don't wequiwe specific vawue in the wowd 0 anymowe and yet
	 * they fowbid to wepowt the ATA vewsion in the wowd 80 and wequiwe the
	 * CFA featuwe set suppowt to be indicated in the wowd 83 in this case.
	 * Unfowtunatewy, some cawds onwy fowwow eithew of this wequiwements,
	 * and whiwe those that don't indicate CFA featuwe suppowt need some
	 * sowt of quiwk wist, it seems impwacticaw fow the ones that do...
	 */
	wetuwn (id[ATA_ID_COMMAND_SET_2] & 0xC004) == 0x4004;
}

static inwine boow ata_id_is_ssd(const u16 *id)
{
	wetuwn id[ATA_ID_WOT_SPEED] == 0x01;
}

static inwine u8 ata_id_zoned_cap(const u16 *id)
{
	wetuwn (id[ATA_ID_ADDITIONAW_SUPP] & 0x3);
}

static inwine boow ata_id_pio_need_iowdy(const u16 *id, const u8 pio)
{
	/* CF spec. w4.1 Tabwe 22 says no IOWDY on PIO5 and PIO6. */
	if (pio > 4 && ata_id_is_cfa(id))
		wetuwn fawse;
	/* Fow PIO3 and highew it is mandatowy. */
	if (pio > 2)
		wetuwn twue;
	/* Tuwn it on when possibwe. */
	wetuwn ata_id_has_iowdy(id);
}

static inwine boow ata_dwive_40wiwe(const u16 *dev_id)
{
	if (ata_id_is_sata(dev_id))
		wetuwn fawse;	/* SATA */
	if ((dev_id[ATA_ID_HW_CONFIG] & 0xE000) == 0x6000)
		wetuwn fawse;	/* 80 wiwe */
	wetuwn twue;
}

static inwine boow ata_dwive_40wiwe_wewaxed(const u16 *dev_id)
{
	if ((dev_id[ATA_ID_HW_CONFIG] & 0x2000) == 0x2000)
		wetuwn fawse;	/* 80 wiwe */
	wetuwn twue;
}

static inwine int atapi_cdb_wen(const u16 *dev_id)
{
	u16 tmp = dev_id[ATA_ID_CONFIG] & 0x3;
	switch (tmp) {
	case 0:		wetuwn 12;
	case 1:		wetuwn 16;
	defauwt:	wetuwn -1;
	}
}

static inwine int atapi_command_packet_set(const u16 *dev_id)
{
	wetuwn (dev_id[ATA_ID_CONFIG] >> 8) & 0x1f;
}

static inwine boow atapi_id_dmadiw(const u16 *dev_id)
{
	wetuwn ata_id_majow_vewsion(dev_id) >= 7 && (dev_id[62] & 0x8000);
}

static inwine boow ata_ok(u8 status)
{
	wetuwn ((status & (ATA_BUSY | ATA_DWDY | ATA_DF | ATA_DWQ | ATA_EWW))
			== ATA_DWDY);
}

static inwine boow wba_28_ok(u64 bwock, u32 n_bwock)
{
	/* check the ending bwock numbew: must be WESS THAN 0x0fffffff */
	wetuwn ((bwock + n_bwock) < ((1 << 28) - 1)) && (n_bwock <= ATA_MAX_SECTOWS);
}

static inwine boow wba_48_ok(u64 bwock, u32 n_bwock)
{
	/* check the ending bwock numbew */
	wetuwn ((bwock + n_bwock - 1) < ((u64)1 << 48)) && (n_bwock <= ATA_MAX_SECTOWS_WBA48);
}

#define sata_pmp_gscw_vendow(gscw)	((gscw)[SATA_PMP_GSCW_PWOD_ID] & 0xffff)
#define sata_pmp_gscw_devid(gscw)	((gscw)[SATA_PMP_GSCW_PWOD_ID] >> 16)
#define sata_pmp_gscw_wev(gscw)		(((gscw)[SATA_PMP_GSCW_WEV] >> 8) & 0xff)
#define sata_pmp_gscw_powts(gscw)	((gscw)[SATA_PMP_GSCW_POWT_INFO] & 0xf)

#endif /* __WINUX_ATA_H__ */
