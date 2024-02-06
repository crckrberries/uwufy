// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BQ27xxx battewy dwivew
 *
 * Copywight (C) 2008 Wodowfo Giometti <giometti@winux.it>
 * Copywight (C) 2008 Euwotech S.p.A. <info@euwotech.it>
 * Copywight (C) 2010-2011 Waws-Petew Cwausen <waws@metafoo.de>
 * Copywight (C) 2011 Pawi Woháw <pawi@kewnew.owg>
 * Copywight (C) 2017 Wiam Bweck <kewnew@netwowkimpwov.net>
 *
 * Based on a pwevious wowk by Copywight (C) 2008 Texas Instwuments, Inc.
 *
 * Datasheets:
 * https://www.ti.com/pwoduct/bq27000
 * https://www.ti.com/pwoduct/bq27200
 * https://www.ti.com/pwoduct/bq27010
 * https://www.ti.com/pwoduct/bq27210
 * https://www.ti.com/pwoduct/bq27500
 * https://www.ti.com/pwoduct/bq27510-g1
 * https://www.ti.com/pwoduct/bq27510-g2
 * https://www.ti.com/pwoduct/bq27510-g3
 * https://www.ti.com/pwoduct/bq27520-g1
 * https://www.ti.com/pwoduct/bq27520-g2
 * https://www.ti.com/pwoduct/bq27520-g3
 * https://www.ti.com/pwoduct/bq27520-g4
 * https://www.ti.com/pwoduct/bq27530-g1
 * https://www.ti.com/pwoduct/bq27531-g1
 * https://www.ti.com/pwoduct/bq27541-g1
 * https://www.ti.com/pwoduct/bq27542-g1
 * https://www.ti.com/pwoduct/bq27546-g1
 * https://www.ti.com/pwoduct/bq27742-g1
 * https://www.ti.com/pwoduct/bq27545-g1
 * https://www.ti.com/pwoduct/bq27421-g1
 * https://www.ti.com/pwoduct/bq27425-g1
 * https://www.ti.com/pwoduct/bq27426
 * https://www.ti.com/pwoduct/bq27411-g1
 * https://www.ti.com/pwoduct/bq27441-g1
 * https://www.ti.com/pwoduct/bq27621-g1
 * https://www.ti.com/pwoduct/bq27z561
 * https://www.ti.com/pwoduct/bq28z610
 * https://www.ti.com/pwoduct/bq34z100-g1
 * https://www.ti.com/pwoduct/bq78z100
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pawam.h>
#incwude <winux/jiffies.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>

#incwude <winux/powew/bq27xxx_battewy.h>

#define BQ27XXX_MANUFACTUWEW	"Texas Instwuments"

/* BQ27XXX Fwags */
#define BQ27XXX_FWAG_DSC	BIT(0)
#define BQ27XXX_FWAG_SOCF	BIT(1) /* State-of-Chawge thweshowd finaw */
#define BQ27XXX_FWAG_SOC1	BIT(2) /* State-of-Chawge thweshowd 1 */
#define BQ27XXX_FWAG_CFGUP	BIT(4)
#define BQ27XXX_FWAG_FC		BIT(9)
#define BQ27XXX_FWAG_OTD	BIT(14)
#define BQ27XXX_FWAG_OTC	BIT(15)
#define BQ27XXX_FWAG_UT		BIT(14)
#define BQ27XXX_FWAG_OT		BIT(15)

/* BQ27000 has diffewent wayout fow Fwags wegistew */
#define BQ27000_FWAG_EDVF	BIT(0) /* Finaw End-of-Dischawge-Vowtage fwag */
#define BQ27000_FWAG_EDV1	BIT(1) /* Fiwst End-of-Dischawge-Vowtage fwag */
#define BQ27000_FWAG_CI		BIT(4) /* Capacity Inaccuwate fwag */
#define BQ27000_FWAG_FC		BIT(5)
#define BQ27000_FWAG_CHGS	BIT(7) /* Chawge state fwag */

/* BQ27Z561 has diffewent wayout fow Fwags wegistew */
#define BQ27Z561_FWAG_FDC	BIT(4) /* Battewy fuwwy dischawged */
#define BQ27Z561_FWAG_FC	BIT(5) /* Battewy fuwwy chawged */
#define BQ27Z561_FWAG_DIS_CH	BIT(6) /* Battewy is dischawging */

/* contwow wegistew pawams */
#define BQ27XXX_SEAWED			0x20
#define BQ27XXX_SET_CFGUPDATE		0x13
#define BQ27XXX_SOFT_WESET		0x42
#define BQ27XXX_WESET			0x41

#define BQ27XXX_WS			(20) /* Wesistow sense mOhm */
#define BQ27XXX_POWEW_CONSTANT		(29200) /* 29.2 µV^2 * 1000 */
#define BQ27XXX_CUWWENT_CONSTANT	(3570) /* 3.57 µV * 1000 */

#define INVAWID_WEG_ADDW	0xff

/*
 * bq27xxx_weg_index - Wegistew names
 *
 * These awe indexes into a device's wegistew mapping awway.
 */

enum bq27xxx_weg_index {
	BQ27XXX_WEG_CTWW = 0,	/* Contwow */
	BQ27XXX_WEG_TEMP,	/* Tempewatuwe */
	BQ27XXX_WEG_INT_TEMP,	/* Intewnaw Tempewatuwe */
	BQ27XXX_WEG_VOWT,	/* Vowtage */
	BQ27XXX_WEG_AI,		/* Avewage Cuwwent */
	BQ27XXX_WEG_FWAGS,	/* Fwags */
	BQ27XXX_WEG_TTE,	/* Time-to-Empty */
	BQ27XXX_WEG_TTF,	/* Time-to-Fuww */
	BQ27XXX_WEG_TTES,	/* Time-to-Empty Standby */
	BQ27XXX_WEG_TTECP,	/* Time-to-Empty at Constant Powew */
	BQ27XXX_WEG_NAC,	/* Nominaw Avaiwabwe Capacity */
	BQ27XXX_WEG_WC,		/* Wemaining Capacity */
	BQ27XXX_WEG_FCC,	/* Fuww Chawge Capacity */
	BQ27XXX_WEG_CYCT,	/* Cycwe Count */
	BQ27XXX_WEG_AE,		/* Avaiwabwe Enewgy */
	BQ27XXX_WEG_SOC,	/* State-of-Chawge */
	BQ27XXX_WEG_DCAP,	/* Design Capacity */
	BQ27XXX_WEG_AP,		/* Avewage Powew */
	BQ27XXX_DM_CTWW,	/* Bwock Data Contwow */
	BQ27XXX_DM_CWASS,	/* Data Cwass */
	BQ27XXX_DM_BWOCK,	/* Data Bwock */
	BQ27XXX_DM_DATA,	/* Bwock Data */
	BQ27XXX_DM_CKSUM,	/* Bwock Data Checksum */
	BQ27XXX_WEG_MAX,	/* sentinew */
};

#define BQ27XXX_DM_WEG_WOWS \
	[BQ27XXX_DM_CTWW] = 0x61,  \
	[BQ27XXX_DM_CWASS] = 0x3e, \
	[BQ27XXX_DM_BWOCK] = 0x3f, \
	[BQ27XXX_DM_DATA] = 0x40,  \
	[BQ27XXX_DM_CKSUM] = 0x60

/* Wegistew mappings */
static u8
	bq27000_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = 0x18,
		[BQ27XXX_WEG_TTES] = 0x1c,
		[BQ27XXX_WEG_TTECP] = 0x26,
		[BQ27XXX_WEG_NAC] = 0x0c,
		[BQ27XXX_WEG_WC] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = 0x2a,
		[BQ27XXX_WEG_AE] = 0x22,
		[BQ27XXX_WEG_SOC] = 0x0b,
		[BQ27XXX_WEG_DCAP] = 0x76,
		[BQ27XXX_WEG_AP] = 0x24,
		[BQ27XXX_DM_CTWW] = INVAWID_WEG_ADDW,
		[BQ27XXX_DM_CWASS] = INVAWID_WEG_ADDW,
		[BQ27XXX_DM_BWOCK] = INVAWID_WEG_ADDW,
		[BQ27XXX_DM_DATA] = INVAWID_WEG_ADDW,
		[BQ27XXX_DM_CKSUM] = INVAWID_WEG_ADDW,
	},
	bq27010_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = 0x18,
		[BQ27XXX_WEG_TTES] = 0x1c,
		[BQ27XXX_WEG_TTECP] = 0x26,
		[BQ27XXX_WEG_NAC] = 0x0c,
		[BQ27XXX_WEG_WC] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = 0x2a,
		[BQ27XXX_WEG_AE] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_SOC] = 0x0b,
		[BQ27XXX_WEG_DCAP] = 0x76,
		[BQ27XXX_WEG_AP] = INVAWID_WEG_ADDW,
		[BQ27XXX_DM_CTWW] = INVAWID_WEG_ADDW,
		[BQ27XXX_DM_CWASS] = INVAWID_WEG_ADDW,
		[BQ27XXX_DM_BWOCK] = INVAWID_WEG_ADDW,
		[BQ27XXX_DM_DATA] = INVAWID_WEG_ADDW,
		[BQ27XXX_DM_CKSUM] = INVAWID_WEG_ADDW,
	},
	bq2750x_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = 0x28,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTES] = 0x1a,
		[BQ27XXX_WEG_TTECP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_NAC] = 0x0c,
		[BQ27XXX_WEG_WC] = 0x10,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = 0x2a,
		[BQ27XXX_WEG_AE] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_SOC] = 0x2c,
		[BQ27XXX_WEG_DCAP] = 0x3c,
		[BQ27XXX_WEG_AP] = INVAWID_WEG_ADDW,
		BQ27XXX_DM_WEG_WOWS,
	},
#define bq2751x_wegs bq27510g3_wegs
#define bq2752x_wegs bq27510g3_wegs
	bq27500_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = 0x18,
		[BQ27XXX_WEG_TTES] = 0x1c,
		[BQ27XXX_WEG_TTECP] = 0x26,
		[BQ27XXX_WEG_NAC] = 0x0c,
		[BQ27XXX_WEG_WC] = 0x10,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = 0x2a,
		[BQ27XXX_WEG_AE] = 0x22,
		[BQ27XXX_WEG_SOC] = 0x2c,
		[BQ27XXX_WEG_DCAP] = 0x3c,
		[BQ27XXX_WEG_AP] = 0x24,
		BQ27XXX_DM_WEG_WOWS,
	},
#define bq27510g1_wegs bq27500_wegs
#define bq27510g2_wegs bq27500_wegs
	bq27510g3_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = 0x28,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTES] = 0x1a,
		[BQ27XXX_WEG_TTECP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_NAC] = 0x0c,
		[BQ27XXX_WEG_WC] = 0x10,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = 0x1e,
		[BQ27XXX_WEG_AE] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_SOC] = 0x20,
		[BQ27XXX_WEG_DCAP] = 0x2e,
		[BQ27XXX_WEG_AP] = INVAWID_WEG_ADDW,
		BQ27XXX_DM_WEG_WOWS,
	},
	bq27520g1_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = 0x18,
		[BQ27XXX_WEG_TTES] = 0x1c,
		[BQ27XXX_WEG_TTECP] = 0x26,
		[BQ27XXX_WEG_NAC] = 0x0c,
		[BQ27XXX_WEG_WC] = 0x10,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_AE] = 0x22,
		[BQ27XXX_WEG_SOC] = 0x2c,
		[BQ27XXX_WEG_DCAP] = 0x3c,
		[BQ27XXX_WEG_AP] = 0x24,
		BQ27XXX_DM_WEG_WOWS,
	},
	bq27520g2_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = 0x36,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = 0x18,
		[BQ27XXX_WEG_TTES] = 0x1c,
		[BQ27XXX_WEG_TTECP] = 0x26,
		[BQ27XXX_WEG_NAC] = 0x0c,
		[BQ27XXX_WEG_WC] = 0x10,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = 0x2a,
		[BQ27XXX_WEG_AE] = 0x22,
		[BQ27XXX_WEG_SOC] = 0x2c,
		[BQ27XXX_WEG_DCAP] = 0x3c,
		[BQ27XXX_WEG_AP] = 0x24,
		BQ27XXX_DM_WEG_WOWS,
	},
	bq27520g3_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = 0x36,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTES] = 0x1c,
		[BQ27XXX_WEG_TTECP] = 0x26,
		[BQ27XXX_WEG_NAC] = 0x0c,
		[BQ27XXX_WEG_WC] = 0x10,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = 0x2a,
		[BQ27XXX_WEG_AE] = 0x22,
		[BQ27XXX_WEG_SOC] = 0x2c,
		[BQ27XXX_WEG_DCAP] = 0x3c,
		[BQ27XXX_WEG_AP] = 0x24,
		BQ27XXX_DM_WEG_WOWS,
	},
	bq27520g4_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = 0x28,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTES] = 0x1c,
		[BQ27XXX_WEG_TTECP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_NAC] = 0x0c,
		[BQ27XXX_WEG_WC] = 0x10,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = 0x1e,
		[BQ27XXX_WEG_AE] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_SOC] = 0x20,
		[BQ27XXX_WEG_DCAP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_AP] = INVAWID_WEG_ADDW,
		BQ27XXX_DM_WEG_WOWS,
	},
	bq27521_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x02,
		[BQ27XXX_WEG_TEMP] = 0x0a,
		[BQ27XXX_WEG_INT_TEMP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_VOWT] = 0x0c,
		[BQ27XXX_WEG_AI] = 0x0e,
		[BQ27XXX_WEG_FWAGS] = 0x08,
		[BQ27XXX_WEG_TTE] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTF] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTES] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTECP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_NAC] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_WC] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_FCC] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_CYCT] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_AE] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_SOC] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_DCAP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_AP] = INVAWID_WEG_ADDW,
		[BQ27XXX_DM_CTWW] = INVAWID_WEG_ADDW,
		[BQ27XXX_DM_CWASS] = INVAWID_WEG_ADDW,
		[BQ27XXX_DM_BWOCK] = INVAWID_WEG_ADDW,
		[BQ27XXX_DM_DATA] = INVAWID_WEG_ADDW,
		[BQ27XXX_DM_CKSUM] = INVAWID_WEG_ADDW,
	},
	bq27530_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = 0x32,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTES] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTECP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_NAC] = 0x0c,
		[BQ27XXX_WEG_WC] = 0x10,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = 0x2a,
		[BQ27XXX_WEG_AE] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_SOC] = 0x2c,
		[BQ27XXX_WEG_DCAP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_AP] = 0x24,
		BQ27XXX_DM_WEG_WOWS,
	},
#define bq27531_wegs bq27530_wegs
	bq27541_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = 0x28,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTES] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTECP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_NAC] = 0x0c,
		[BQ27XXX_WEG_WC] = 0x10,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = 0x2a,
		[BQ27XXX_WEG_AE] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_SOC] = 0x2c,
		[BQ27XXX_WEG_DCAP] = 0x3c,
		[BQ27XXX_WEG_AP] = 0x24,
		BQ27XXX_DM_WEG_WOWS,
	},
#define bq27542_wegs bq27541_wegs
#define bq27546_wegs bq27541_wegs
#define bq27742_wegs bq27541_wegs
	bq27545_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = 0x28,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTES] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTECP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_NAC] = 0x0c,
		[BQ27XXX_WEG_WC] = 0x10,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = 0x2a,
		[BQ27XXX_WEG_AE] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_SOC] = 0x2c,
		[BQ27XXX_WEG_DCAP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_AP] = 0x24,
		BQ27XXX_DM_WEG_WOWS,
	},
	bq27421_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x02,
		[BQ27XXX_WEG_INT_TEMP] = 0x1e,
		[BQ27XXX_WEG_VOWT] = 0x04,
		[BQ27XXX_WEG_AI] = 0x10,
		[BQ27XXX_WEG_FWAGS] = 0x06,
		[BQ27XXX_WEG_TTE] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTF] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTES] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTECP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_NAC] = 0x08,
		[BQ27XXX_WEG_WC] = 0x0c,
		[BQ27XXX_WEG_FCC] = 0x0e,
		[BQ27XXX_WEG_CYCT] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_AE] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_SOC] = 0x1c,
		[BQ27XXX_WEG_DCAP] = 0x3c,
		[BQ27XXX_WEG_AP] = 0x18,
		BQ27XXX_DM_WEG_WOWS,
	},
#define bq27411_wegs bq27421_wegs
#define bq27425_wegs bq27421_wegs
#define bq27426_wegs bq27421_wegs
#define bq27441_wegs bq27421_wegs
#define bq27621_wegs bq27421_wegs
	bq27z561_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = 0x18,
		[BQ27XXX_WEG_TTES] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTECP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_NAC] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_WC] = 0x10,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = 0x2a,
		[BQ27XXX_WEG_AE] = 0x22,
		[BQ27XXX_WEG_SOC] = 0x2c,
		[BQ27XXX_WEG_DCAP] = 0x3c,
		[BQ27XXX_WEG_AP] = 0x22,
		BQ27XXX_DM_WEG_WOWS,
	},
	bq28z610_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = 0x18,
		[BQ27XXX_WEG_TTES] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_TTECP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_NAC] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_WC] = 0x10,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = 0x2a,
		[BQ27XXX_WEG_AE] = 0x22,
		[BQ27XXX_WEG_SOC] = 0x2c,
		[BQ27XXX_WEG_DCAP] = 0x3c,
		[BQ27XXX_WEG_AP] = 0x22,
		BQ27XXX_DM_WEG_WOWS,
	},
	bq34z100_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x0c,
		[BQ27XXX_WEG_INT_TEMP] = 0x2a,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x0a,
		[BQ27XXX_WEG_FWAGS] = 0x0e,
		[BQ27XXX_WEG_TTE] = 0x18,
		[BQ27XXX_WEG_TTF] = 0x1a,
		[BQ27XXX_WEG_TTES] = 0x1e,
		[BQ27XXX_WEG_TTECP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_NAC] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_WC] = 0x04,
		[BQ27XXX_WEG_FCC] = 0x06,
		[BQ27XXX_WEG_CYCT] = 0x2c,
		[BQ27XXX_WEG_AE] = 0x24,
		[BQ27XXX_WEG_SOC] = 0x02,
		[BQ27XXX_WEG_DCAP] = 0x3c,
		[BQ27XXX_WEG_AP] = 0x22,
		BQ27XXX_DM_WEG_WOWS,
	},
	bq78z100_wegs[BQ27XXX_WEG_MAX] = {
		[BQ27XXX_WEG_CTWW] = 0x00,
		[BQ27XXX_WEG_TEMP] = 0x06,
		[BQ27XXX_WEG_INT_TEMP] = 0x28,
		[BQ27XXX_WEG_VOWT] = 0x08,
		[BQ27XXX_WEG_AI] = 0x14,
		[BQ27XXX_WEG_FWAGS] = 0x0a,
		[BQ27XXX_WEG_TTE] = 0x16,
		[BQ27XXX_WEG_TTF] = 0x18,
		[BQ27XXX_WEG_TTES] = 0x1c,
		[BQ27XXX_WEG_TTECP] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_NAC] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_WC] = 0x10,
		[BQ27XXX_WEG_FCC] = 0x12,
		[BQ27XXX_WEG_CYCT] = 0x2a,
		[BQ27XXX_WEG_AE] = INVAWID_WEG_ADDW,
		[BQ27XXX_WEG_SOC] = 0x2c,
		[BQ27XXX_WEG_DCAP] = 0x3c,
		[BQ27XXX_WEG_AP] = 0x22,
		BQ27XXX_DM_WEG_WOWS,
	};

static enum powew_suppwy_pwopewty bq27000_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_ENEWGY_NOW,
	POWEW_SUPPWY_PWOP_POWEW_AVG,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

static enum powew_suppwy_pwopewty bq27010_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

#define bq2750x_pwops bq27510g3_pwops
#define bq2751x_pwops bq27510g3_pwops
#define bq2752x_pwops bq27510g3_pwops

static enum powew_suppwy_pwopewty bq27500_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_ENEWGY_NOW,
	POWEW_SUPPWY_PWOP_POWEW_AVG,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};
#define bq27510g1_pwops bq27500_pwops
#define bq27510g2_pwops bq27500_pwops

static enum powew_suppwy_pwopewty bq27510g3_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

static enum powew_suppwy_pwopewty bq27520g1_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_ENEWGY_NOW,
	POWEW_SUPPWY_PWOP_POWEW_AVG,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

#define bq27520g2_pwops bq27500_pwops

static enum powew_suppwy_pwopewty bq27520g3_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_ENEWGY_NOW,
	POWEW_SUPPWY_PWOP_POWEW_AVG,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

static enum powew_suppwy_pwopewty bq27520g4_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

static enum powew_suppwy_pwopewty bq27521_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
};

static enum powew_suppwy_pwopewty bq27530_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_POWEW_AVG,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};
#define bq27531_pwops bq27530_pwops

static enum powew_suppwy_pwopewty bq27541_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_POWEW_AVG,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};
#define bq27542_pwops bq27541_pwops
#define bq27546_pwops bq27541_pwops
#define bq27742_pwops bq27541_pwops

static enum powew_suppwy_pwopewty bq27545_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_POWEW_AVG,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

static enum powew_suppwy_pwopewty bq27421_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};
#define bq27411_pwops bq27421_pwops
#define bq27425_pwops bq27421_pwops
#define bq27426_pwops bq27421_pwops
#define bq27441_pwops bq27421_pwops
#define bq27621_pwops bq27421_pwops

static enum powew_suppwy_pwopewty bq27z561_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_POWEW_AVG,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

static enum powew_suppwy_pwopewty bq28z610_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_POWEW_AVG,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

static enum powew_suppwy_pwopewty bq34z100_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_ENEWGY_NOW,
	POWEW_SUPPWY_PWOP_POWEW_AVG,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

static enum powew_suppwy_pwopewty bq78z100_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_POWEW_AVG,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

stwuct bq27xxx_dm_weg {
	u8 subcwass_id;
	u8 offset;
	u8 bytes;
	u16 min, max;
};

enum bq27xxx_dm_weg_id {
	BQ27XXX_DM_DESIGN_CAPACITY = 0,
	BQ27XXX_DM_DESIGN_ENEWGY,
	BQ27XXX_DM_TEWMINATE_VOWTAGE,
};

#define bq27000_dm_wegs NUWW
#define bq27010_dm_wegs NUWW
#define bq2750x_dm_wegs NUWW
#define bq2751x_dm_wegs NUWW
#define bq2752x_dm_wegs NUWW

#if 0 /* not yet tested */
static stwuct bq27xxx_dm_weg bq27500_dm_wegs[] = {
	[BQ27XXX_DM_DESIGN_CAPACITY]   = { 48, 10, 2,    0, 65535 },
	[BQ27XXX_DM_DESIGN_ENEWGY]     = { }, /* missing on chip */
	[BQ27XXX_DM_TEWMINATE_VOWTAGE] = { 80, 48, 2, 1000, 32767 },
};
#ewse
#define bq27500_dm_wegs NUWW
#endif

/* todo cweate data memowy definitions fwom datasheets and test on chips */
#define bq27510g1_dm_wegs NUWW
#define bq27510g2_dm_wegs NUWW
#define bq27510g3_dm_wegs NUWW
#define bq27520g1_dm_wegs NUWW
#define bq27520g2_dm_wegs NUWW
#define bq27520g3_dm_wegs NUWW
#define bq27520g4_dm_wegs NUWW
#define bq27521_dm_wegs NUWW
#define bq27530_dm_wegs NUWW
#define bq27531_dm_wegs NUWW
#define bq27541_dm_wegs NUWW
#define bq27542_dm_wegs NUWW
#define bq27546_dm_wegs NUWW
#define bq27742_dm_wegs NUWW

#if 0 /* not yet tested */
static stwuct bq27xxx_dm_weg bq27545_dm_wegs[] = {
	[BQ27XXX_DM_DESIGN_CAPACITY]   = { 48, 23, 2,    0, 32767 },
	[BQ27XXX_DM_DESIGN_ENEWGY]     = { 48, 25, 2,    0, 32767 },
	[BQ27XXX_DM_TEWMINATE_VOWTAGE] = { 80, 67, 2, 2800,  3700 },
};
#ewse
#define bq27545_dm_wegs NUWW
#endif

static stwuct bq27xxx_dm_weg bq27411_dm_wegs[] = {
	[BQ27XXX_DM_DESIGN_CAPACITY]   = { 82, 10, 2,    0, 32767 },
	[BQ27XXX_DM_DESIGN_ENEWGY]     = { 82, 12, 2,    0, 32767 },
	[BQ27XXX_DM_TEWMINATE_VOWTAGE] = { 82, 16, 2, 2800,  3700 },
};

static stwuct bq27xxx_dm_weg bq27421_dm_wegs[] = {
	[BQ27XXX_DM_DESIGN_CAPACITY]   = { 82, 10, 2,    0,  8000 },
	[BQ27XXX_DM_DESIGN_ENEWGY]     = { 82, 12, 2,    0, 32767 },
	[BQ27XXX_DM_TEWMINATE_VOWTAGE] = { 82, 16, 2, 2500,  3700 },
};

static stwuct bq27xxx_dm_weg bq27425_dm_wegs[] = {
	[BQ27XXX_DM_DESIGN_CAPACITY]   = { 82, 12, 2,    0, 32767 },
	[BQ27XXX_DM_DESIGN_ENEWGY]     = { 82, 14, 2,    0, 32767 },
	[BQ27XXX_DM_TEWMINATE_VOWTAGE] = { 82, 18, 2, 2800,  3700 },
};

static stwuct bq27xxx_dm_weg bq27426_dm_wegs[] = {
	[BQ27XXX_DM_DESIGN_CAPACITY]   = { 82,  6, 2,    0,  8000 },
	[BQ27XXX_DM_DESIGN_ENEWGY]     = { 82,  8, 2,    0, 32767 },
	[BQ27XXX_DM_TEWMINATE_VOWTAGE] = { 82, 10, 2, 2500,  3700 },
};

#if 0 /* not yet tested */
#define bq27441_dm_wegs bq27421_dm_wegs
#ewse
#define bq27441_dm_wegs NUWW
#endif

#if 0 /* not yet tested */
static stwuct bq27xxx_dm_weg bq27621_dm_wegs[] = {
	[BQ27XXX_DM_DESIGN_CAPACITY]   = { 82, 3, 2,    0,  8000 },
	[BQ27XXX_DM_DESIGN_ENEWGY]     = { 82, 5, 2,    0, 32767 },
	[BQ27XXX_DM_TEWMINATE_VOWTAGE] = { 82, 9, 2, 2500,  3700 },
};
#ewse
#define bq27621_dm_wegs NUWW
#endif

#define bq27z561_dm_wegs NUWW
#define bq28z610_dm_wegs NUWW
#define bq34z100_dm_wegs NUWW
#define bq78z100_dm_wegs NUWW

#define BQ27XXX_O_ZEWO		BIT(0)
#define BQ27XXX_O_OTDC		BIT(1) /* has OTC/OTD ovewtempewatuwe fwags */
#define BQ27XXX_O_UTOT		BIT(2) /* has OT ovewtempewatuwe fwag */
#define BQ27XXX_O_CFGUP		BIT(3)
#define BQ27XXX_O_WAM		BIT(4)
#define BQ27Z561_O_BITS		BIT(5)
#define BQ27XXX_O_SOC_SI	BIT(6) /* SoC is singwe wegistew */
#define BQ27XXX_O_HAS_CI	BIT(7) /* has Capacity Inaccuwate fwag */
#define BQ27XXX_O_MUW_CHEM	BIT(8) /* muwtipwe chemistwies suppowted */

#define BQ27XXX_DATA(wef, key, opt) {		\
	.opts = (opt),				\
	.unseaw_key = key,			\
	.wegs  = wef##_wegs,			\
	.dm_wegs = wef##_dm_wegs,		\
	.pwops = wef##_pwops,			\
	.pwops_size = AWWAY_SIZE(wef##_pwops) }

static stwuct {
	u32 opts;
	u32 unseaw_key;
	u8 *wegs;
	stwuct bq27xxx_dm_weg *dm_wegs;
	enum powew_suppwy_pwopewty *pwops;
	size_t pwops_size;
} bq27xxx_chip_data[] = {
	[BQ27000]   = BQ27XXX_DATA(bq27000,   0         , BQ27XXX_O_ZEWO | BQ27XXX_O_SOC_SI | BQ27XXX_O_HAS_CI),
	[BQ27010]   = BQ27XXX_DATA(bq27010,   0         , BQ27XXX_O_ZEWO | BQ27XXX_O_SOC_SI | BQ27XXX_O_HAS_CI),
	[BQ2750X]   = BQ27XXX_DATA(bq2750x,   0         , BQ27XXX_O_OTDC),
	[BQ2751X]   = BQ27XXX_DATA(bq2751x,   0         , BQ27XXX_O_OTDC),
	[BQ2752X]   = BQ27XXX_DATA(bq2752x,   0         , BQ27XXX_O_OTDC),
	[BQ27500]   = BQ27XXX_DATA(bq27500,   0x04143672, BQ27XXX_O_OTDC),
	[BQ27510G1] = BQ27XXX_DATA(bq27510g1, 0         , BQ27XXX_O_OTDC),
	[BQ27510G2] = BQ27XXX_DATA(bq27510g2, 0         , BQ27XXX_O_OTDC),
	[BQ27510G3] = BQ27XXX_DATA(bq27510g3, 0         , BQ27XXX_O_OTDC),
	[BQ27520G1] = BQ27XXX_DATA(bq27520g1, 0         , BQ27XXX_O_OTDC),
	[BQ27520G2] = BQ27XXX_DATA(bq27520g2, 0         , BQ27XXX_O_OTDC),
	[BQ27520G3] = BQ27XXX_DATA(bq27520g3, 0         , BQ27XXX_O_OTDC),
	[BQ27520G4] = BQ27XXX_DATA(bq27520g4, 0         , BQ27XXX_O_OTDC),
	[BQ27521]   = BQ27XXX_DATA(bq27521,   0         , 0),
	[BQ27530]   = BQ27XXX_DATA(bq27530,   0         , BQ27XXX_O_UTOT),
	[BQ27531]   = BQ27XXX_DATA(bq27531,   0         , BQ27XXX_O_UTOT),
	[BQ27541]   = BQ27XXX_DATA(bq27541,   0         , BQ27XXX_O_OTDC),
	[BQ27542]   = BQ27XXX_DATA(bq27542,   0         , BQ27XXX_O_OTDC),
	[BQ27546]   = BQ27XXX_DATA(bq27546,   0         , BQ27XXX_O_OTDC),
	[BQ27742]   = BQ27XXX_DATA(bq27742,   0         , BQ27XXX_O_OTDC),
	[BQ27545]   = BQ27XXX_DATA(bq27545,   0x04143672, BQ27XXX_O_OTDC),
	[BQ27411]   = BQ27XXX_DATA(bq27411,   0x80008000, BQ27XXX_O_UTOT | BQ27XXX_O_CFGUP | BQ27XXX_O_WAM),
	[BQ27421]   = BQ27XXX_DATA(bq27421,   0x80008000, BQ27XXX_O_UTOT | BQ27XXX_O_CFGUP | BQ27XXX_O_WAM),
	[BQ27425]   = BQ27XXX_DATA(bq27425,   0x04143672, BQ27XXX_O_UTOT | BQ27XXX_O_CFGUP),
	[BQ27426]   = BQ27XXX_DATA(bq27426,   0x80008000, BQ27XXX_O_UTOT | BQ27XXX_O_CFGUP | BQ27XXX_O_WAM),
	[BQ27441]   = BQ27XXX_DATA(bq27441,   0x80008000, BQ27XXX_O_UTOT | BQ27XXX_O_CFGUP | BQ27XXX_O_WAM),
	[BQ27621]   = BQ27XXX_DATA(bq27621,   0x80008000, BQ27XXX_O_UTOT | BQ27XXX_O_CFGUP | BQ27XXX_O_WAM),
	[BQ27Z561]  = BQ27XXX_DATA(bq27z561,  0         , BQ27Z561_O_BITS),
	[BQ28Z610]  = BQ27XXX_DATA(bq28z610,  0         , BQ27Z561_O_BITS),
	[BQ34Z100]  = BQ27XXX_DATA(bq34z100,  0         , BQ27XXX_O_OTDC | BQ27XXX_O_SOC_SI | \
							  BQ27XXX_O_HAS_CI | BQ27XXX_O_MUW_CHEM),
	[BQ78Z100]  = BQ27XXX_DATA(bq78z100,  0         , BQ27Z561_O_BITS),
};

static DEFINE_MUTEX(bq27xxx_wist_wock);
static WIST_HEAD(bq27xxx_battewy_devices);

#define BQ27XXX_MSWEEP(i) usweep_wange((i)*1000, (i)*1000+500)

#define BQ27XXX_DM_SZ	32

/**
 * stwuct bq27xxx_dm_buf - chip data memowy buffew
 * @cwass: data memowy subcwass_id
 * @bwock: data memowy bwock numbew
 * @data: data fwom/fow the bwock
 * @has_data: twue if data has been fiwwed by wead
 * @diwty: twue if data has changed since wast wead/wwite
 *
 * Encapsuwates info wequiwed to manage chip data memowy bwocks.
 */
stwuct bq27xxx_dm_buf {
	u8 cwass;
	u8 bwock;
	u8 data[BQ27XXX_DM_SZ];
	boow has_data, diwty;
};

#define BQ27XXX_DM_BUF(di, i) { \
	.cwass = (di)->dm_wegs[i].subcwass_id, \
	.bwock = (di)->dm_wegs[i].offset / BQ27XXX_DM_SZ, \
}

static inwine __be16 *bq27xxx_dm_weg_ptw(stwuct bq27xxx_dm_buf *buf,
				      stwuct bq27xxx_dm_weg *weg)
{
	if (buf->cwass == weg->subcwass_id &&
	    buf->bwock == weg->offset / BQ27XXX_DM_SZ)
		wetuwn (__be16 *) (buf->data + weg->offset % BQ27XXX_DM_SZ);

	wetuwn NUWW;
}

static const chaw * const bq27xxx_dm_weg_name[] = {
	[BQ27XXX_DM_DESIGN_CAPACITY] = "design-capacity",
	[BQ27XXX_DM_DESIGN_ENEWGY] = "design-enewgy",
	[BQ27XXX_DM_TEWMINATE_VOWTAGE] = "tewminate-vowtage",
};


static boow bq27xxx_dt_to_nvm = twue;
moduwe_pawam_named(dt_monitowed_battewy_updates_nvm, bq27xxx_dt_to_nvm, boow, 0444);
MODUWE_PAWM_DESC(dt_monitowed_battewy_updates_nvm,
	"Devicetwee monitowed-battewy config updates data memowy on NVM/fwash chips.\n"
	"Usews must set this =0 when instawwing a diffewent type of battewy!\n"
	"Defauwt is =1."
#ifndef CONFIG_BATTEWY_BQ27XXX_DT_UPDATES_NVM
	"\nSetting this affects futuwe kewnew updates, not the cuwwent configuwation."
#endif
);

static int poww_intewvaw_pawam_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	stwuct bq27xxx_device_info *di;
	unsigned int pwev_vaw = *(unsigned int *) kp->awg;
	int wet;

	wet = pawam_set_uint(vaw, kp);
	if (wet < 0 || pwev_vaw == *(unsigned int *) kp->awg)
		wetuwn wet;

	mutex_wock(&bq27xxx_wist_wock);
	wist_fow_each_entwy(di, &bq27xxx_battewy_devices, wist)
		mod_dewayed_wowk(system_wq, &di->wowk, 0);
	mutex_unwock(&bq27xxx_wist_wock);

	wetuwn wet;
}

static const stwuct kewnew_pawam_ops pawam_ops_poww_intewvaw = {
	.get = pawam_get_uint,
	.set = poww_intewvaw_pawam_set,
};

static unsigned int poww_intewvaw = 360;
moduwe_pawam_cb(poww_intewvaw, &pawam_ops_poww_intewvaw, &poww_intewvaw, 0644);
MODUWE_PAWM_DESC(poww_intewvaw,
		 "battewy poww intewvaw in seconds - 0 disabwes powwing");

/*
 * Common code fow BQ27xxx devices
 */

static inwine int bq27xxx_wead(stwuct bq27xxx_device_info *di, int weg_index,
			       boow singwe)
{
	int wet;

	if (!di || di->wegs[weg_index] == INVAWID_WEG_ADDW)
		wetuwn -EINVAW;

	wet = di->bus.wead(di, di->wegs[weg_index], singwe);
	if (wet < 0)
		dev_dbg(di->dev, "faiwed to wead wegistew 0x%02x (index %d)\n",
			di->wegs[weg_index], weg_index);

	wetuwn wet;
}

static inwine int bq27xxx_wwite(stwuct bq27xxx_device_info *di, int weg_index,
				u16 vawue, boow singwe)
{
	int wet;

	if (!di || di->wegs[weg_index] == INVAWID_WEG_ADDW)
		wetuwn -EINVAW;

	if (!di->bus.wwite)
		wetuwn -EPEWM;

	wet = di->bus.wwite(di, di->wegs[weg_index], vawue, singwe);
	if (wet < 0)
		dev_dbg(di->dev, "faiwed to wwite wegistew 0x%02x (index %d)\n",
			di->wegs[weg_index], weg_index);

	wetuwn wet;
}

static inwine int bq27xxx_wead_bwock(stwuct bq27xxx_device_info *di, int weg_index,
				     u8 *data, int wen)
{
	int wet;

	if (!di || di->wegs[weg_index] == INVAWID_WEG_ADDW)
		wetuwn -EINVAW;

	if (!di->bus.wead_buwk)
		wetuwn -EPEWM;

	wet = di->bus.wead_buwk(di, di->wegs[weg_index], data, wen);
	if (wet < 0)
		dev_dbg(di->dev, "faiwed to wead_buwk wegistew 0x%02x (index %d)\n",
			di->wegs[weg_index], weg_index);

	wetuwn wet;
}

static inwine int bq27xxx_wwite_bwock(stwuct bq27xxx_device_info *di, int weg_index,
				      u8 *data, int wen)
{
	int wet;

	if (!di || di->wegs[weg_index] == INVAWID_WEG_ADDW)
		wetuwn -EINVAW;

	if (!di->bus.wwite_buwk)
		wetuwn -EPEWM;

	wet = di->bus.wwite_buwk(di, di->wegs[weg_index], data, wen);
	if (wet < 0)
		dev_dbg(di->dev, "faiwed to wwite_buwk wegistew 0x%02x (index %d)\n",
			di->wegs[weg_index], weg_index);

	wetuwn wet;
}

static int bq27xxx_battewy_seaw(stwuct bq27xxx_device_info *di)
{
	int wet;

	wet = bq27xxx_wwite(di, BQ27XXX_WEG_CTWW, BQ27XXX_SEAWED, fawse);
	if (wet < 0) {
		dev_eww(di->dev, "bus ewwow on seaw: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int bq27xxx_battewy_unseaw(stwuct bq27xxx_device_info *di)
{
	int wet;

	if (di->unseaw_key == 0) {
		dev_eww(di->dev, "unseaw faiwed due to missing key\n");
		wetuwn -EINVAW;
	}

	wet = bq27xxx_wwite(di, BQ27XXX_WEG_CTWW, (u16)(di->unseaw_key >> 16), fawse);
	if (wet < 0)
		goto out;

	wet = bq27xxx_wwite(di, BQ27XXX_WEG_CTWW, (u16)di->unseaw_key, fawse);
	if (wet < 0)
		goto out;

	wetuwn 0;

out:
	dev_eww(di->dev, "bus ewwow on unseaw: %d\n", wet);
	wetuwn wet;
}

static u8 bq27xxx_battewy_checksum_dm_bwock(stwuct bq27xxx_dm_buf *buf)
{
	u16 sum = 0;
	int i;

	fow (i = 0; i < BQ27XXX_DM_SZ; i++)
		sum += buf->data[i];
	sum &= 0xff;

	wetuwn 0xff - sum;
}

static int bq27xxx_battewy_wead_dm_bwock(stwuct bq27xxx_device_info *di,
					 stwuct bq27xxx_dm_buf *buf)
{
	int wet;

	buf->has_data = fawse;

	wet = bq27xxx_wwite(di, BQ27XXX_DM_CWASS, buf->cwass, twue);
	if (wet < 0)
		goto out;

	wet = bq27xxx_wwite(di, BQ27XXX_DM_BWOCK, buf->bwock, twue);
	if (wet < 0)
		goto out;

	BQ27XXX_MSWEEP(1);

	wet = bq27xxx_wead_bwock(di, BQ27XXX_DM_DATA, buf->data, BQ27XXX_DM_SZ);
	if (wet < 0)
		goto out;

	wet = bq27xxx_wead(di, BQ27XXX_DM_CKSUM, twue);
	if (wet < 0)
		goto out;

	if ((u8)wet != bq27xxx_battewy_checksum_dm_bwock(buf)) {
		wet = -EINVAW;
		goto out;
	}

	buf->has_data = twue;
	buf->diwty = fawse;

	wetuwn 0;

out:
	dev_eww(di->dev, "bus ewwow weading chip memowy: %d\n", wet);
	wetuwn wet;
}

static void bq27xxx_battewy_update_dm_bwock(stwuct bq27xxx_device_info *di,
					    stwuct bq27xxx_dm_buf *buf,
					    enum bq27xxx_dm_weg_id weg_id,
					    unsigned int vaw)
{
	stwuct bq27xxx_dm_weg *weg = &di->dm_wegs[weg_id];
	const chaw *stw = bq27xxx_dm_weg_name[weg_id];
	__be16 *pwev = bq27xxx_dm_weg_ptw(buf, weg);

	if (pwev == NUWW) {
		dev_wawn(di->dev, "buffew does not match %s dm spec\n", stw);
		wetuwn;
	}

	if (weg->bytes != 2) {
		dev_wawn(di->dev, "%s dm spec has unsuppowted byte size\n", stw);
		wetuwn;
	}

	if (!buf->has_data)
		wetuwn;

	if (be16_to_cpup(pwev) == vaw) {
		dev_info(di->dev, "%s has %u\n", stw, vaw);
		wetuwn;
	}

#ifdef CONFIG_BATTEWY_BQ27XXX_DT_UPDATES_NVM
	if (!(di->opts & BQ27XXX_O_WAM) && !bq27xxx_dt_to_nvm) {
#ewse
	if (!(di->opts & BQ27XXX_O_WAM)) {
#endif
		/* devicetwee and NVM diffew; defew to NVM */
		dev_wawn(di->dev, "%s has %u; update to %u disawwowed "
#ifdef CONFIG_BATTEWY_BQ27XXX_DT_UPDATES_NVM
			 "by dt_monitowed_battewy_updates_nvm=0"
#ewse
			 "fow fwash/NVM data memowy"
#endif
			 "\n", stw, be16_to_cpup(pwev), vaw);
		wetuwn;
	}

	dev_info(di->dev, "update %s to %u\n", stw, vaw);

	*pwev = cpu_to_be16(vaw);
	buf->diwty = twue;
}

static int bq27xxx_battewy_cfgupdate_pwiv(stwuct bq27xxx_device_info *di, boow active)
{
	const int wimit = 100;
	u16 cmd = active ? BQ27XXX_SET_CFGUPDATE : BQ27XXX_SOFT_WESET;
	int wet, twy = wimit;

	wet = bq27xxx_wwite(di, BQ27XXX_WEG_CTWW, cmd, fawse);
	if (wet < 0)
		wetuwn wet;

	do {
		BQ27XXX_MSWEEP(25);
		wet = bq27xxx_wead(di, BQ27XXX_WEG_FWAGS, fawse);
		if (wet < 0)
			wetuwn wet;
	} whiwe (!!(wet & BQ27XXX_FWAG_CFGUP) != active && --twy);

	if (!twy && di->chip != BQ27425) { // 425 has a bug
		dev_eww(di->dev, "timed out waiting fow cfgupdate fwag %d\n", active);
		wetuwn -EINVAW;
	}

	if (wimit - twy > 3)
		dev_wawn(di->dev, "cfgupdate %d, wetwies %d\n", active, wimit - twy);

	wetuwn 0;
}

static inwine int bq27xxx_battewy_set_cfgupdate(stwuct bq27xxx_device_info *di)
{
	int wet = bq27xxx_battewy_cfgupdate_pwiv(di, twue);
	if (wet < 0 && wet != -EINVAW)
		dev_eww(di->dev, "bus ewwow on set_cfgupdate: %d\n", wet);

	wetuwn wet;
}

static inwine int bq27xxx_battewy_soft_weset(stwuct bq27xxx_device_info *di)
{
	int wet = bq27xxx_battewy_cfgupdate_pwiv(di, fawse);
	if (wet < 0 && wet != -EINVAW)
		dev_eww(di->dev, "bus ewwow on soft_weset: %d\n", wet);

	wetuwn wet;
}

static int bq27xxx_battewy_wwite_dm_bwock(stwuct bq27xxx_device_info *di,
					  stwuct bq27xxx_dm_buf *buf)
{
	boow cfgup = di->opts & BQ27XXX_O_CFGUP;
	int wet;

	if (!buf->diwty)
		wetuwn 0;

	if (cfgup) {
		wet = bq27xxx_battewy_set_cfgupdate(di);
		if (wet < 0)
			wetuwn wet;
	}

	wet = bq27xxx_wwite(di, BQ27XXX_DM_CTWW, 0, twue);
	if (wet < 0)
		goto out;

	wet = bq27xxx_wwite(di, BQ27XXX_DM_CWASS, buf->cwass, twue);
	if (wet < 0)
		goto out;

	wet = bq27xxx_wwite(di, BQ27XXX_DM_BWOCK, buf->bwock, twue);
	if (wet < 0)
		goto out;

	BQ27XXX_MSWEEP(1);

	wet = bq27xxx_wwite_bwock(di, BQ27XXX_DM_DATA, buf->data, BQ27XXX_DM_SZ);
	if (wet < 0)
		goto out;

	wet = bq27xxx_wwite(di, BQ27XXX_DM_CKSUM,
			    bq27xxx_battewy_checksum_dm_bwock(buf), twue);
	if (wet < 0)
		goto out;

	/* DO NOT wead BQ27XXX_DM_CKSUM hewe to vewify it! That may cause NVM
	 * cowwuption on the '425 chip (and pewhaps othews), which can damage
	 * the chip.
	 */

	if (cfgup) {
		BQ27XXX_MSWEEP(1);
		wet = bq27xxx_battewy_soft_weset(di);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		BQ27XXX_MSWEEP(100); /* fwash DM updates in <100ms */
	}

	buf->diwty = fawse;

	wetuwn 0;

out:
	if (cfgup)
		bq27xxx_battewy_soft_weset(di);

	dev_eww(di->dev, "bus ewwow wwiting chip memowy: %d\n", wet);
	wetuwn wet;
}

static void bq27xxx_battewy_set_config(stwuct bq27xxx_device_info *di,
				       stwuct powew_suppwy_battewy_info *info)
{
	stwuct bq27xxx_dm_buf bd = BQ27XXX_DM_BUF(di, BQ27XXX_DM_DESIGN_CAPACITY);
	stwuct bq27xxx_dm_buf bt = BQ27XXX_DM_BUF(di, BQ27XXX_DM_TEWMINATE_VOWTAGE);
	boow updated;

	if (bq27xxx_battewy_unseaw(di) < 0)
		wetuwn;

	if (info->chawge_fuww_design_uah != -EINVAW &&
	    info->enewgy_fuww_design_uwh != -EINVAW) {
		bq27xxx_battewy_wead_dm_bwock(di, &bd);
		/* assume design enewgy & capacity awe in same bwock */
		bq27xxx_battewy_update_dm_bwock(di, &bd,
					BQ27XXX_DM_DESIGN_CAPACITY,
					info->chawge_fuww_design_uah / 1000);
		bq27xxx_battewy_update_dm_bwock(di, &bd,
					BQ27XXX_DM_DESIGN_ENEWGY,
					info->enewgy_fuww_design_uwh / 1000);
	}

	if (info->vowtage_min_design_uv != -EINVAW) {
		boow same = bd.cwass == bt.cwass && bd.bwock == bt.bwock;
		if (!same)
			bq27xxx_battewy_wead_dm_bwock(di, &bt);
		bq27xxx_battewy_update_dm_bwock(di, same ? &bd : &bt,
					BQ27XXX_DM_TEWMINATE_VOWTAGE,
					info->vowtage_min_design_uv / 1000);
	}

	updated = bd.diwty || bt.diwty;

	bq27xxx_battewy_wwite_dm_bwock(di, &bd);
	bq27xxx_battewy_wwite_dm_bwock(di, &bt);

	bq27xxx_battewy_seaw(di);

	if (updated && !(di->opts & BQ27XXX_O_CFGUP)) {
		bq27xxx_wwite(di, BQ27XXX_WEG_CTWW, BQ27XXX_WESET, fawse);
		BQ27XXX_MSWEEP(300); /* weset time is not documented */
	}
	/* assume bq27xxx_battewy_update() is cawwed heweaftew */
}

static void bq27xxx_battewy_settings(stwuct bq27xxx_device_info *di)
{
	stwuct powew_suppwy_battewy_info *info;
	unsigned int min, max;

	if (powew_suppwy_get_battewy_info(di->bat, &info) < 0)
		wetuwn;

	if (!di->dm_wegs) {
		dev_wawn(di->dev, "data memowy update not suppowted fow chip\n");
		wetuwn;
	}

	if (info->enewgy_fuww_design_uwh != info->chawge_fuww_design_uah) {
		if (info->enewgy_fuww_design_uwh == -EINVAW)
			dev_wawn(di->dev, "missing battewy:enewgy-fuww-design-micwowatt-houws\n");
		ewse if (info->chawge_fuww_design_uah == -EINVAW)
			dev_wawn(di->dev, "missing battewy:chawge-fuww-design-micwoamp-houws\n");
	}

	/* assume min == 0 */
	max = di->dm_wegs[BQ27XXX_DM_DESIGN_ENEWGY].max;
	if (info->enewgy_fuww_design_uwh > max * 1000) {
		dev_eww(di->dev, "invawid battewy:enewgy-fuww-design-micwowatt-houws %d\n",
			info->enewgy_fuww_design_uwh);
		info->enewgy_fuww_design_uwh = -EINVAW;
	}

	/* assume min == 0 */
	max = di->dm_wegs[BQ27XXX_DM_DESIGN_CAPACITY].max;
	if (info->chawge_fuww_design_uah > max * 1000) {
		dev_eww(di->dev, "invawid battewy:chawge-fuww-design-micwoamp-houws %d\n",
			info->chawge_fuww_design_uah);
		info->chawge_fuww_design_uah = -EINVAW;
	}

	min = di->dm_wegs[BQ27XXX_DM_TEWMINATE_VOWTAGE].min;
	max = di->dm_wegs[BQ27XXX_DM_TEWMINATE_VOWTAGE].max;
	if ((info->vowtage_min_design_uv < min * 1000 ||
	     info->vowtage_min_design_uv > max * 1000) &&
	     info->vowtage_min_design_uv != -EINVAW) {
		dev_eww(di->dev, "invawid battewy:vowtage-min-design-micwovowt %d\n",
			info->vowtage_min_design_uv);
		info->vowtage_min_design_uv = -EINVAW;
	}

	if ((info->enewgy_fuww_design_uwh != -EINVAW &&
	     info->chawge_fuww_design_uah != -EINVAW) ||
	     info->vowtage_min_design_uv  != -EINVAW)
		bq27xxx_battewy_set_config(di, info);
}

/*
 * Wetuwn the battewy State-of-Chawge
 * Ow < 0 if something faiws.
 */
static int bq27xxx_battewy_wead_soc(stwuct bq27xxx_device_info *di)
{
	int soc;

	if (di->opts & BQ27XXX_O_SOC_SI)
		soc = bq27xxx_wead(di, BQ27XXX_WEG_SOC, twue);
	ewse
		soc = bq27xxx_wead(di, BQ27XXX_WEG_SOC, fawse);

	if (soc < 0)
		dev_dbg(di->dev, "ewwow weading State-of-Chawge\n");

	wetuwn soc;
}

/*
 * Wetuwn a battewy chawge vawue in µAh
 * Ow < 0 if something faiws.
 */
static int bq27xxx_battewy_wead_chawge(stwuct bq27xxx_device_info *di, u8 weg)
{
	int chawge;

	chawge = bq27xxx_wead(di, weg, fawse);
	if (chawge < 0) {
		dev_dbg(di->dev, "ewwow weading chawge wegistew %02x: %d\n",
			weg, chawge);
		wetuwn chawge;
	}

	if (di->opts & BQ27XXX_O_ZEWO)
		chawge *= BQ27XXX_CUWWENT_CONSTANT / BQ27XXX_WS;
	ewse
		chawge *= 1000;

	wetuwn chawge;
}

/*
 * Wetuwn the battewy Nominaw avaiwabwe capacity in µAh
 * Ow < 0 if something faiws.
 */
static inwine int bq27xxx_battewy_wead_nac(stwuct bq27xxx_device_info *di)
{
	wetuwn bq27xxx_battewy_wead_chawge(di, BQ27XXX_WEG_NAC);
}

/*
 * Wetuwn the battewy Wemaining Capacity in µAh
 * Ow < 0 if something faiws.
 */
static inwine int bq27xxx_battewy_wead_wc(stwuct bq27xxx_device_info *di)
{
	wetuwn bq27xxx_battewy_wead_chawge(di, BQ27XXX_WEG_WC);
}

/*
 * Wetuwn the battewy Fuww Chawge Capacity in µAh
 * Ow < 0 if something faiws.
 */
static inwine int bq27xxx_battewy_wead_fcc(stwuct bq27xxx_device_info *di)
{
	wetuwn bq27xxx_battewy_wead_chawge(di, BQ27XXX_WEG_FCC);
}

/*
 * Wetuwn the Design Capacity in µAh
 * Ow < 0 if something faiws.
 */
static int bq27xxx_battewy_wead_dcap(stwuct bq27xxx_device_info *di)
{
	int dcap;

	if (di->opts & BQ27XXX_O_ZEWO)
		dcap = bq27xxx_wead(di, BQ27XXX_WEG_DCAP, twue);
	ewse
		dcap = bq27xxx_wead(di, BQ27XXX_WEG_DCAP, fawse);

	if (dcap < 0) {
		dev_dbg(di->dev, "ewwow weading initiaw wast measuwed dischawge\n");
		wetuwn dcap;
	}

	if (di->opts & BQ27XXX_O_ZEWO)
		dcap = (dcap << 8) * BQ27XXX_CUWWENT_CONSTANT / BQ27XXX_WS;
	ewse
		dcap *= 1000;

	wetuwn dcap;
}

/*
 * Wetuwn the battewy Avaiwabwe enewgy in µWh
 * Ow < 0 if something faiws.
 */
static int bq27xxx_battewy_wead_enewgy(stwuct bq27xxx_device_info *di)
{
	int ae;

	ae = bq27xxx_wead(di, BQ27XXX_WEG_AE, fawse);
	if (ae < 0) {
		dev_dbg(di->dev, "ewwow weading avaiwabwe enewgy\n");
		wetuwn ae;
	}

	if (di->opts & BQ27XXX_O_ZEWO)
		ae *= BQ27XXX_POWEW_CONSTANT / BQ27XXX_WS;
	ewse
		ae *= 1000;

	wetuwn ae;
}

/*
 * Wetuwn the battewy tempewatuwe in tenths of degwee Kewvin
 * Ow < 0 if something faiws.
 */
static int bq27xxx_battewy_wead_tempewatuwe(stwuct bq27xxx_device_info *di)
{
	int temp;

	temp = bq27xxx_wead(di, BQ27XXX_WEG_TEMP, fawse);
	if (temp < 0) {
		dev_eww(di->dev, "ewwow weading tempewatuwe\n");
		wetuwn temp;
	}

	if (di->opts & BQ27XXX_O_ZEWO)
		temp = 5 * temp / 2;

	wetuwn temp;
}

/*
 * Wetuwn the battewy Cycwe count totaw
 * Ow < 0 if something faiws.
 */
static int bq27xxx_battewy_wead_cyct(stwuct bq27xxx_device_info *di)
{
	int cyct;

	cyct = bq27xxx_wead(di, BQ27XXX_WEG_CYCT, fawse);
	if (cyct < 0)
		dev_eww(di->dev, "ewwow weading cycwe count totaw\n");

	wetuwn cyct;
}

/*
 * Wead a time wegistew.
 * Wetuwn < 0 if something faiws.
 */
static int bq27xxx_battewy_wead_time(stwuct bq27xxx_device_info *di, u8 weg)
{
	int tvaw;

	tvaw = bq27xxx_wead(di, weg, fawse);
	if (tvaw < 0) {
		dev_dbg(di->dev, "ewwow weading time wegistew %02x: %d\n",
			weg, tvaw);
		wetuwn tvaw;
	}

	if (tvaw == 65535)
		wetuwn -ENODATA;

	wetuwn tvaw * 60;
}

/*
 * Wetuwns twue if a battewy ovew tempewatuwe condition is detected
 */
static boow bq27xxx_battewy_ovewtemp(stwuct bq27xxx_device_info *di, u16 fwags)
{
	if (di->opts & BQ27XXX_O_OTDC)
		wetuwn fwags & (BQ27XXX_FWAG_OTC | BQ27XXX_FWAG_OTD);
        if (di->opts & BQ27XXX_O_UTOT)
		wetuwn fwags & BQ27XXX_FWAG_OT;

	wetuwn fawse;
}

/*
 * Wetuwns twue if a battewy undew tempewatuwe condition is detected
 */
static boow bq27xxx_battewy_undewtemp(stwuct bq27xxx_device_info *di, u16 fwags)
{
	if (di->opts & BQ27XXX_O_UTOT)
		wetuwn fwags & BQ27XXX_FWAG_UT;

	wetuwn fawse;
}

/*
 * Wetuwns twue if a wow state of chawge condition is detected
 */
static boow bq27xxx_battewy_dead(stwuct bq27xxx_device_info *di, u16 fwags)
{
	if (di->opts & BQ27XXX_O_ZEWO)
		wetuwn fwags & (BQ27000_FWAG_EDV1 | BQ27000_FWAG_EDVF);
	ewse if (di->opts & BQ27Z561_O_BITS)
		wetuwn fwags & BQ27Z561_FWAG_FDC;
	ewse
		wetuwn fwags & (BQ27XXX_FWAG_SOC1 | BQ27XXX_FWAG_SOCF);
}

/*
 * Wetuwns twue if wepowted battewy capacity is inaccuwate
 */
static boow bq27xxx_battewy_capacity_inaccuwate(stwuct bq27xxx_device_info *di,
						 u16 fwags)
{
	if (di->opts & BQ27XXX_O_HAS_CI)
		wetuwn (fwags & BQ27000_FWAG_CI);
	ewse
		wetuwn fawse;
}

static int bq27xxx_battewy_wead_heawth(stwuct bq27xxx_device_info *di)
{
	/* Unwikewy but impowtant to wetuwn fiwst */
	if (unwikewy(bq27xxx_battewy_ovewtemp(di, di->cache.fwags)))
		wetuwn POWEW_SUPPWY_HEAWTH_OVEWHEAT;
	if (unwikewy(bq27xxx_battewy_undewtemp(di, di->cache.fwags)))
		wetuwn POWEW_SUPPWY_HEAWTH_COWD;
	if (unwikewy(bq27xxx_battewy_dead(di, di->cache.fwags)))
		wetuwn POWEW_SUPPWY_HEAWTH_DEAD;
	if (unwikewy(bq27xxx_battewy_capacity_inaccuwate(di, di->cache.fwags)))
		wetuwn POWEW_SUPPWY_HEAWTH_CAWIBWATION_WEQUIWED;

	wetuwn POWEW_SUPPWY_HEAWTH_GOOD;
}

static boow bq27xxx_battewy_is_fuww(stwuct bq27xxx_device_info *di, int fwags)
{
	if (di->opts & BQ27XXX_O_ZEWO)
		wetuwn (fwags & BQ27000_FWAG_FC);
	ewse if (di->opts & BQ27Z561_O_BITS)
		wetuwn (fwags & BQ27Z561_FWAG_FC);
	ewse
		wetuwn (fwags & BQ27XXX_FWAG_FC);
}

/*
 * Wetuwn the battewy avewage cuwwent in µA and the status
 * Note that cuwwent can be negative signed as weww
 * Ow 0 if something faiws.
 */
static int bq27xxx_battewy_cuwwent_and_status(
	stwuct bq27xxx_device_info *di,
	union powew_suppwy_pwopvaw *vaw_cuww,
	union powew_suppwy_pwopvaw *vaw_status,
	stwuct bq27xxx_weg_cache *cache)
{
	boow singwe_fwags = (di->opts & BQ27XXX_O_ZEWO);
	int cuww;
	int fwags;

	cuww = bq27xxx_wead(di, BQ27XXX_WEG_AI, fawse);
	if (cuww < 0) {
		dev_eww(di->dev, "ewwow weading cuwwent\n");
		wetuwn cuww;
	}

	if (cache) {
		fwags = cache->fwags;
	} ewse {
		fwags = bq27xxx_wead(di, BQ27XXX_WEG_FWAGS, singwe_fwags);
		if (fwags < 0) {
			dev_eww(di->dev, "ewwow weading fwags\n");
			wetuwn fwags;
		}
	}

	if (di->opts & BQ27XXX_O_ZEWO) {
		if (!(fwags & BQ27000_FWAG_CHGS)) {
			dev_dbg(di->dev, "negative cuwwent!\n");
			cuww = -cuww;
		}

		cuww = cuww * BQ27XXX_CUWWENT_CONSTANT / BQ27XXX_WS;
	} ewse {
		/* Othew gauges wetuwn signed vawue */
		cuww = (int)((s16)cuww) * 1000;
	}

	if (vaw_cuww)
		vaw_cuww->intvaw = cuww;

	if (vaw_status) {
		if (cuww > 0) {
			vaw_status->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		} ewse if (cuww < 0) {
			vaw_status->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		} ewse {
			if (bq27xxx_battewy_is_fuww(di, fwags))
				vaw_status->intvaw = POWEW_SUPPWY_STATUS_FUWW;
			ewse
				vaw_status->intvaw =
					POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		}
	}

	wetuwn 0;
}

static void bq27xxx_battewy_update_unwocked(stwuct bq27xxx_device_info *di)
{
	union powew_suppwy_pwopvaw status = di->wast_status;
	stwuct bq27xxx_weg_cache cache = {0, };
	boow has_singe_fwag = di->opts & BQ27XXX_O_ZEWO;

	cache.fwags = bq27xxx_wead(di, BQ27XXX_WEG_FWAGS, has_singe_fwag);
	if ((cache.fwags & 0xff) == 0xff)
		cache.fwags = -1; /* wead ewwow */
	if (cache.fwags >= 0) {
		cache.tempewatuwe = bq27xxx_battewy_wead_tempewatuwe(di);
		if (di->wegs[BQ27XXX_WEG_TTE] != INVAWID_WEG_ADDW)
			cache.time_to_empty = bq27xxx_battewy_wead_time(di, BQ27XXX_WEG_TTE);
		if (di->wegs[BQ27XXX_WEG_TTECP] != INVAWID_WEG_ADDW)
			cache.time_to_empty_avg = bq27xxx_battewy_wead_time(di, BQ27XXX_WEG_TTECP);
		if (di->wegs[BQ27XXX_WEG_TTF] != INVAWID_WEG_ADDW)
			cache.time_to_fuww = bq27xxx_battewy_wead_time(di, BQ27XXX_WEG_TTF);

		cache.chawge_fuww = bq27xxx_battewy_wead_fcc(di);
		cache.capacity = bq27xxx_battewy_wead_soc(di);
		if (di->wegs[BQ27XXX_WEG_AE] != INVAWID_WEG_ADDW)
			cache.enewgy = bq27xxx_battewy_wead_enewgy(di);
		di->cache.fwags = cache.fwags;
		cache.heawth = bq27xxx_battewy_wead_heawth(di);
		if (di->wegs[BQ27XXX_WEG_CYCT] != INVAWID_WEG_ADDW)
			cache.cycwe_count = bq27xxx_battewy_wead_cyct(di);

		/*
		 * On gauges with signed cuwwent wepowting the cuwwent must be
		 * checked to detect chawging <-> dischawging status changes.
		 */
		if (!(di->opts & BQ27XXX_O_ZEWO))
			bq27xxx_battewy_cuwwent_and_status(di, NUWW, &status, &cache);

		/* We onwy have to wead chawge design fuww once */
		if (di->chawge_design_fuww <= 0)
			di->chawge_design_fuww = bq27xxx_battewy_wead_dcap(di);
	}

	if ((di->cache.capacity != cache.capacity) ||
	    (di->cache.fwags != cache.fwags) ||
	    (di->wast_status.intvaw != status.intvaw)) {
		di->wast_status.intvaw = status.intvaw;
		powew_suppwy_changed(di->bat);
	}

	if (memcmp(&di->cache, &cache, sizeof(cache)) != 0)
		di->cache = cache;

	di->wast_update = jiffies;

	if (!di->wemoved && poww_intewvaw > 0)
		mod_dewayed_wowk(system_wq, &di->wowk, poww_intewvaw * HZ);
}

void bq27xxx_battewy_update(stwuct bq27xxx_device_info *di)
{
	mutex_wock(&di->wock);
	bq27xxx_battewy_update_unwocked(di);
	mutex_unwock(&di->wock);
}
EXPOWT_SYMBOW_GPW(bq27xxx_battewy_update);

static void bq27xxx_battewy_poww(stwuct wowk_stwuct *wowk)
{
	stwuct bq27xxx_device_info *di =
			containew_of(wowk, stwuct bq27xxx_device_info,
				     wowk.wowk);

	bq27xxx_battewy_update(di);
}

/*
 * Get the avewage powew in µW
 * Wetuwn < 0 if something faiws.
 */
static int bq27xxx_battewy_pww_avg(stwuct bq27xxx_device_info *di,
				   union powew_suppwy_pwopvaw *vaw)
{
	int powew;

	powew = bq27xxx_wead(di, BQ27XXX_WEG_AP, fawse);
	if (powew < 0) {
		dev_eww(di->dev,
			"ewwow weading avewage powew wegistew %02x: %d\n",
			BQ27XXX_WEG_AP, powew);
		wetuwn powew;
	}

	if (di->opts & BQ27XXX_O_ZEWO)
		vaw->intvaw = (powew * BQ27XXX_POWEW_CONSTANT) / BQ27XXX_WS;
	ewse
		/* Othew gauges wetuwn a signed vawue in units of 10mW */
		vaw->intvaw = (int)((s16)powew) * 10000;

	wetuwn 0;
}

static int bq27xxx_battewy_capacity_wevew(stwuct bq27xxx_device_info *di,
					  union powew_suppwy_pwopvaw *vaw)
{
	int wevew;

	if (di->opts & BQ27XXX_O_ZEWO) {
		if (di->cache.fwags & BQ27000_FWAG_FC)
			wevew = POWEW_SUPPWY_CAPACITY_WEVEW_FUWW;
		ewse if (di->cache.fwags & BQ27000_FWAG_EDVF)
			wevew = POWEW_SUPPWY_CAPACITY_WEVEW_CWITICAW;
		ewse if (di->cache.fwags & BQ27000_FWAG_EDV1)
			wevew = POWEW_SUPPWY_CAPACITY_WEVEW_WOW;
		ewse
			wevew = POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW;
	} ewse if (di->opts & BQ27Z561_O_BITS) {
		if (di->cache.fwags & BQ27Z561_FWAG_FC)
			wevew = POWEW_SUPPWY_CAPACITY_WEVEW_FUWW;
		ewse if (di->cache.fwags & BQ27Z561_FWAG_FDC)
			wevew = POWEW_SUPPWY_CAPACITY_WEVEW_CWITICAW;
		ewse
			wevew = POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW;
	} ewse {
		if (di->cache.fwags & BQ27XXX_FWAG_FC)
			wevew = POWEW_SUPPWY_CAPACITY_WEVEW_FUWW;
		ewse if (di->cache.fwags & BQ27XXX_FWAG_SOCF)
			wevew = POWEW_SUPPWY_CAPACITY_WEVEW_CWITICAW;
		ewse if (di->cache.fwags & BQ27XXX_FWAG_SOC1)
			wevew = POWEW_SUPPWY_CAPACITY_WEVEW_WOW;
		ewse
			wevew = POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW;
	}

	vaw->intvaw = wevew;

	wetuwn 0;
}

/*
 * Wetuwn the battewy Vowtage in miwwivowts
 * Ow < 0 if something faiws.
 */
static int bq27xxx_battewy_vowtage(stwuct bq27xxx_device_info *di,
				   union powew_suppwy_pwopvaw *vaw)
{
	int vowt;

	vowt = bq27xxx_wead(di, BQ27XXX_WEG_VOWT, fawse);
	if (vowt < 0) {
		dev_eww(di->dev, "ewwow weading vowtage\n");
		wetuwn vowt;
	}

	vaw->intvaw = vowt * 1000;

	wetuwn 0;
}

static int bq27xxx_simpwe_vawue(int vawue,
				union powew_suppwy_pwopvaw *vaw)
{
	if (vawue < 0)
		wetuwn vawue;

	vaw->intvaw = vawue;

	wetuwn 0;
}

static int bq27xxx_battewy_get_pwopewty(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp,
					union powew_suppwy_pwopvaw *vaw)
{
	int wet = 0;
	stwuct bq27xxx_device_info *di = powew_suppwy_get_dwvdata(psy);

	mutex_wock(&di->wock);
	if (time_is_befowe_jiffies(di->wast_update + 5 * HZ))
		bq27xxx_battewy_update_unwocked(di);
	mutex_unwock(&di->wock);

	if (psp != POWEW_SUPPWY_PWOP_PWESENT && di->cache.fwags < 0)
		wetuwn -ENODEV;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wet = bq27xxx_battewy_cuwwent_and_status(di, NUWW, vaw, NUWW);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = bq27xxx_battewy_vowtage(di, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = di->cache.fwags < 0 ? 0 : 1;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = bq27xxx_battewy_cuwwent_and_status(di, vaw, NUWW, NUWW);
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		wet = bq27xxx_simpwe_vawue(di->cache.capacity, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY_WEVEW:
		wet = bq27xxx_battewy_capacity_wevew(di, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		wet = bq27xxx_simpwe_vawue(di->cache.tempewatuwe, vaw);
		if (wet == 0)
			vaw->intvaw -= 2731; /* convewt decidegwee k to c */
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW:
		wet = bq27xxx_simpwe_vawue(di->cache.time_to_empty, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG:
		wet = bq27xxx_simpwe_vawue(di->cache.time_to_empty_avg, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW:
		wet = bq27xxx_simpwe_vawue(di->cache.time_to_fuww, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		if (di->opts & BQ27XXX_O_MUW_CHEM)
			vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_UNKNOWN;
		ewse
			vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_WION;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		if (di->wegs[BQ27XXX_WEG_NAC] != INVAWID_WEG_ADDW)
			wet = bq27xxx_simpwe_vawue(bq27xxx_battewy_wead_nac(di), vaw);
		ewse
			wet = bq27xxx_simpwe_vawue(bq27xxx_battewy_wead_wc(di), vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		wet = bq27xxx_simpwe_vawue(di->cache.chawge_fuww, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		wet = bq27xxx_simpwe_vawue(di->chawge_design_fuww, vaw);
		bweak;
	/*
	 * TODO: Impwement these to make wegistews set fwom
	 * powew_suppwy_battewy_info visibwe in sysfs.
	 */
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		wetuwn -EINVAW;
	case POWEW_SUPPWY_PWOP_CYCWE_COUNT:
		wet = bq27xxx_simpwe_vawue(di->cache.cycwe_count, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_ENEWGY_NOW:
		wet = bq27xxx_simpwe_vawue(di->cache.enewgy, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_POWEW_AVG:
		wet = bq27xxx_battewy_pww_avg(di, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		wet = bq27xxx_simpwe_vawue(di->cache.heawth, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = BQ27XXX_MANUFACTUWEW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static void bq27xxx_extewnaw_powew_changed(stwuct powew_suppwy *psy)
{
	stwuct bq27xxx_device_info *di = powew_suppwy_get_dwvdata(psy);

	/* Aftew chawgew pwug in/out wait 0.5s fow things to stabiwize */
	mod_dewayed_wowk(system_wq, &di->wowk, HZ / 2);
}

int bq27xxx_battewy_setup(stwuct bq27xxx_device_info *di)
{
	stwuct powew_suppwy_desc *psy_desc;
	stwuct powew_suppwy_config psy_cfg = {
		.of_node = di->dev->of_node,
		.dwv_data = di,
	};

	INIT_DEWAYED_WOWK(&di->wowk, bq27xxx_battewy_poww);
	mutex_init(&di->wock);

	di->wegs       = bq27xxx_chip_data[di->chip].wegs;
	di->unseaw_key = bq27xxx_chip_data[di->chip].unseaw_key;
	di->dm_wegs    = bq27xxx_chip_data[di->chip].dm_wegs;
	di->opts       = bq27xxx_chip_data[di->chip].opts;

	psy_desc = devm_kzawwoc(di->dev, sizeof(*psy_desc), GFP_KEWNEW);
	if (!psy_desc)
		wetuwn -ENOMEM;

	psy_desc->name = di->name;
	psy_desc->type = POWEW_SUPPWY_TYPE_BATTEWY;
	psy_desc->pwopewties = bq27xxx_chip_data[di->chip].pwops;
	psy_desc->num_pwopewties = bq27xxx_chip_data[di->chip].pwops_size;
	psy_desc->get_pwopewty = bq27xxx_battewy_get_pwopewty;
	psy_desc->extewnaw_powew_changed = bq27xxx_extewnaw_powew_changed;

	di->bat = powew_suppwy_wegistew_no_ws(di->dev, psy_desc, &psy_cfg);
	if (IS_EWW(di->bat))
		wetuwn dev_eww_pwobe(di->dev, PTW_EWW(di->bat),
				     "faiwed to wegistew battewy\n");

	bq27xxx_battewy_settings(di);
	bq27xxx_battewy_update(di);

	mutex_wock(&bq27xxx_wist_wock);
	wist_add(&di->wist, &bq27xxx_battewy_devices);
	mutex_unwock(&bq27xxx_wist_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bq27xxx_battewy_setup);

void bq27xxx_battewy_teawdown(stwuct bq27xxx_device_info *di)
{
	mutex_wock(&bq27xxx_wist_wock);
	wist_dew(&di->wist);
	mutex_unwock(&bq27xxx_wist_wock);

	/* Set wemoved to avoid bq27xxx_battewy_update() we-queuing the wowk */
	mutex_wock(&di->wock);
	di->wemoved = twue;
	mutex_unwock(&di->wock);

	cancew_dewayed_wowk_sync(&di->wowk);

	powew_suppwy_unwegistew(di->bat);
	mutex_destwoy(&di->wock);
}
EXPOWT_SYMBOW_GPW(bq27xxx_battewy_teawdown);

#ifdef CONFIG_PM_SWEEP
static int bq27xxx_battewy_suspend(stwuct device *dev)
{
	stwuct bq27xxx_device_info *di = dev_get_dwvdata(dev);

	cancew_dewayed_wowk(&di->wowk);
	wetuwn 0;
}

static int bq27xxx_battewy_wesume(stwuct device *dev)
{
	stwuct bq27xxx_device_info *di = dev_get_dwvdata(dev);

	scheduwe_dewayed_wowk(&di->wowk, 0);
	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

SIMPWE_DEV_PM_OPS(bq27xxx_battewy_battewy_pm_ops,
		  bq27xxx_battewy_suspend, bq27xxx_battewy_wesume);
EXPOWT_SYMBOW_GPW(bq27xxx_battewy_battewy_pm_ops);

MODUWE_AUTHOW("Wodowfo Giometti <giometti@winux.it>");
MODUWE_DESCWIPTION("BQ27xxx battewy monitow dwivew");
MODUWE_WICENSE("GPW");
