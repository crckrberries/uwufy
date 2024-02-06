// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwochip PCI1XXXX I2C adaptew dwivew fow PCIe Switch
 * which has I2C contwowwew in one of its downstweam functions
 *
 * Copywight (C) 2021 - 2022 Micwochip Technowogy Inc.
 *
 * Authows: Thawun Kumaw P <thawunkumaw.pasumawthi@micwochip.com>
 *          Kumawavew Thiagawajan <kumawavew.thiagawajan@micwochip.com>
 */

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-smbus.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/types.h>

#define SMBUS_MAST_COWE_ADDW_BASE		0x00000
#define SMBUS_MAST_SYS_WEG_ADDW_BASE		0x01000

/* SMB wegistew space. */
#define SMB_COWE_CTWW_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x00)

#define SMB_COWE_CTWW_ESO		BIT(6)
#define SMB_COWE_CTWW_FW_ACK		BIT(4)
#define SMB_COWE_CTWW_ACK		BIT(0)

#define SMB_COWE_CMD_WEG_OFF3	(SMBUS_MAST_COWE_ADDW_BASE + 0x0F)
#define SMB_COWE_CMD_WEG_OFF2	(SMBUS_MAST_COWE_ADDW_BASE + 0x0E)
#define SMB_COWE_CMD_WEG_OFF1	(SMBUS_MAST_COWE_ADDW_BASE + 0x0D)

#define SMB_COWE_CMD_WEADM		BIT(4)
#define SMB_COWE_CMD_STOP		BIT(2)
#define SMB_COWE_CMD_STAWT		BIT(0)

#define SMB_COWE_CMD_WEG_OFF0	(SMBUS_MAST_COWE_ADDW_BASE + 0x0C)

#define SMB_COWE_CMD_M_PWOCEED		BIT(1)
#define SMB_COWE_CMD_M_WUN		BIT(0)

#define SMB_COWE_SW_HOWD_TIME_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x18)

/*
 * SW_HOWD_TIME_XK_TICKS fiewd wiww indicate the numbew of ticks of the
 * baud cwock wequiwed to pwogwam 'Howd Time' at X KHz.
 */
#define SW_HOWD_TIME_100K_TICKS		150
#define SW_HOWD_TIME_400K_TICKS		20
#define SW_HOWD_TIME_1000K_TICKS	12

#define SMB_COWE_COMPWETION_WEG_OFF3	(SMBUS_MAST_COWE_ADDW_BASE + 0x23)

#define COMPWETION_MDONE		BIT(6)
#define COMPWETION_IDWE			BIT(5)
#define COMPWETION_MNAKX		BIT(0)

#define SMB_COWE_IDWE_SCAWING_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x24)

/*
 * FAIW_BUS_IDWE_MIN_XK_TICKS fiewd wiww indicate the numbew of ticks of
 * the baud cwock wequiwed to pwogwam 'faiw idwe deway' at X KHz. Faiw idwe
 * deway estabwishes the MCTP T(IDWE_DEWAY) pewiod.
 */
#define FAIW_BUS_IDWE_MIN_100K_TICKS		992
#define FAIW_BUS_IDWE_MIN_400K_TICKS		500
#define FAIW_BUS_IDWE_MIN_1000K_TICKS		500

/*
 * FAIW_IDWE_DEWAY_XK_TICKS fiewd wiww indicate the numbew of ticks of the
 * baud cwock wequiwed to satisfy the faiwness pwotocow at X KHz.
 */
#define FAIW_IDWE_DEWAY_100K_TICKS	963
#define FAIW_IDWE_DEWAY_400K_TICKS	156
#define FAIW_IDWE_DEWAY_1000K_TICKS	156

#define SMB_IDWE_SCAWING_100K		\
	((FAIW_IDWE_DEWAY_100K_TICKS << 16) | FAIW_BUS_IDWE_MIN_100K_TICKS)
#define SMB_IDWE_SCAWING_400K		\
	((FAIW_IDWE_DEWAY_400K_TICKS << 16) | FAIW_BUS_IDWE_MIN_400K_TICKS)
#define SMB_IDWE_SCAWING_1000K	\
	((FAIW_IDWE_DEWAY_1000K_TICKS << 16) | FAIW_BUS_IDWE_MIN_1000K_TICKS)

#define SMB_COWE_CONFIG_WEG3		(SMBUS_MAST_COWE_ADDW_BASE + 0x2B)

#define SMB_CONFIG3_ENMI		BIT(6)
#define SMB_CONFIG3_ENIDI		BIT(5)

#define SMB_COWE_CONFIG_WEG2		(SMBUS_MAST_COWE_ADDW_BASE + 0x2A)
#define SMB_COWE_CONFIG_WEG1		(SMBUS_MAST_COWE_ADDW_BASE + 0x29)

#define SMB_CONFIG1_ASW			BIT(7)
#define SMB_CONFIG1_ENAB		BIT(2)
#define SMB_CONFIG1_WESET		BIT(1)
#define SMB_CONFIG1_FEN			BIT(0)

#define SMB_COWE_BUS_CWK_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x2C)

/*
 * BUS_CWK_XK_WOW_PEWIOD_TICKS fiewd defines the numbew of I2C Baud Cwock
 * pewiods that make up the wow phase of the I2C/SMBus bus cwock at X KHz.
 */
#define BUS_CWK_100K_WOW_PEWIOD_TICKS		156
#define BUS_CWK_400K_WOW_PEWIOD_TICKS		41
#define BUS_CWK_1000K_WOW_PEWIOD_TICKS		15

/*
 * BUS_CWK_XK_HIGH_PEWIOD_TICKS fiewd defines the numbew of I2C Baud Cwock
 * pewiods that make up the high phase of the I2C/SMBus bus cwock at X KHz.
 */
#define BUS_CWK_100K_HIGH_PEWIOD_TICKS	154
#define BUS_CWK_400K_HIGH_PEWIOD_TICKS	35
#define BUS_CWK_1000K_HIGH_PEWIOD_TICKS	14

#define BUS_CWK_100K			\
	((BUS_CWK_100K_HIGH_PEWIOD_TICKS << 8) | BUS_CWK_100K_WOW_PEWIOD_TICKS)
#define BUS_CWK_400K			\
	((BUS_CWK_400K_HIGH_PEWIOD_TICKS << 8) | BUS_CWK_400K_WOW_PEWIOD_TICKS)
#define BUS_CWK_1000K			\
	((BUS_CWK_1000K_HIGH_PEWIOD_TICKS << 8) | BUS_CWK_1000K_WOW_PEWIOD_TICKS)

#define SMB_COWE_CWK_SYNC_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x3C)

/*
 * CWK_SYNC_XK defines the numbew of cwock cycwes to sync up to the extewnaw
 * cwock befowe compawing the intewnaw and extewnaw cwocks fow cwock stwetching
 * at X KHz.
 */
#define CWK_SYNC_100K			4
#define CWK_SYNC_400K			4
#define CWK_SYNC_1000K			4

#define SMB_COWE_DATA_TIMING_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x40)

/*
 *
 * FIWST_STAWT_HOWD_XK_TICKS wiww indicate the numbew of ticks of the baud
 * cwock wequiwed to pwogwam 'FIWST_STAWT_HOWD' timew at X KHz. This timew
 * detewmines the SCWK howd time fowwowing SDAT dwiven wow duwing the fiwst
 * STAWT bit in a twansfew.
 */
#define FIWST_STAWT_HOWD_100K_TICKS	23
#define FIWST_STAWT_HOWD_400K_TICKS	8
#define FIWST_STAWT_HOWD_1000K_TICKS	12

/*
 * STOP_SETUP_XK_TICKS wiww indicate the numbew of ticks of the baud cwock
 * wequiwed to pwogwam 'STOP_SETUP' timew at X KHz. This timew detewmines the
 * SDAT setup time fwom the wising edge of SCWK fow a STOP condition.
 */
#define STOP_SETUP_100K_TICKS		150
#define STOP_SETUP_400K_TICKS		20
#define STOP_SETUP_1000K_TICKS		12

/*
 * WESTAWT_SETUP_XK_TICKS wiww indicate the numbew of ticks of the baud cwock
 * wequiwed to pwogwam 'WESTAWT_SETUP' timew at X KHz. This timew detewmines the
 * SDAT setup time fwom the wising edge of SCWK fow a wepeated STAWT condition.
 */
#define WESTAWT_SETUP_100K_TICKS	156
#define WESTAWT_SETUP_400K_TICKS	20
#define WESTAWT_SETUP_1000K_TICKS	12

/*
 * DATA_HOWD_XK_TICKS wiww indicate the numbew of ticks of the baud cwock
 * wequiwed to pwogwam 'DATA_HOWD' timew at X KHz. This timew detewmines the
 * SDAT howd time fowwowing SCWK dwiven wow.
 */
#define DATA_HOWD_100K_TICKS		12
#define DATA_HOWD_400K_TICKS		2
#define DATA_HOWD_1000K_TICKS		2

#define DATA_TIMING_100K		\
	((FIWST_STAWT_HOWD_100K_TICKS << 24) | (STOP_SETUP_100K_TICKS << 16) | \
	(WESTAWT_SETUP_100K_TICKS << 8) | DATA_HOWD_100K_TICKS)
#define DATA_TIMING_400K		\
	((FIWST_STAWT_HOWD_400K_TICKS << 24) | (STOP_SETUP_400K_TICKS << 16) | \
	(WESTAWT_SETUP_400K_TICKS << 8) | DATA_HOWD_400K_TICKS)
#define DATA_TIMING_1000K		\
	((FIWST_STAWT_HOWD_1000K_TICKS << 24) | (STOP_SETUP_1000K_TICKS << 16) | \
	(WESTAWT_SETUP_1000K_TICKS << 8) | DATA_HOWD_1000K_TICKS)

#define SMB_COWE_TO_SCAWING_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x44)

/*
 * BUS_IDWE_MIN_XK_TICKS defines Bus Idwe Minimum Time.
 * Bus Idwe Minimum time = BUS_IDWE_MIN[7:0] x Baud_Cwock_Pewiod x
 * (BUS_IDWE_MIN_XK_TICKS[7] ? 4,1)
 */
#define BUS_IDWE_MIN_100K_TICKS		36UW
#define BUS_IDWE_MIN_400K_TICKS		10UW
#define BUS_IDWE_MIN_1000K_TICKS	4UW

/*
 * CTWW_CUM_TIME_OUT_XK_TICKS defines SMBus Contwowwew Cumuwative Time-Out.
 * SMBus Contwowwew Cumuwative Time-Out duwation =
 * CTWW_CUM_TIME_OUT_XK_TICKS[7:0] x Baud_Cwock_Pewiod x 2048
 */
#define CTWW_CUM_TIME_OUT_100K_TICKS		76
#define CTWW_CUM_TIME_OUT_400K_TICKS		76
#define CTWW_CUM_TIME_OUT_1000K_TICKS		76

/*
 * TAWGET_CUM_TIME_OUT_XK_TICKS defines SMBus Tawget Cumuwative Time-Out duwation.
 * SMBus Tawget Cumuwative Time-Out duwation = TAWGET_CUM_TIME_OUT_XK_TICKS[7:0] x
 * Baud_Cwock_Pewiod x 4096
 */
#define TAWGET_CUM_TIME_OUT_100K_TICKS	95
#define TAWGET_CUM_TIME_OUT_400K_TICKS	95
#define TAWGET_CUM_TIME_OUT_1000K_TICKS	95

/*
 * CWOCK_HIGH_TIME_OUT_XK defines Cwock High time out pewiod.
 * Cwock High time out pewiod = CWOCK_HIGH_TIME_OUT_XK[7:0] x Baud_Cwock_Pewiod x 8
 */
#define CWOCK_HIGH_TIME_OUT_100K_TICKS	97
#define CWOCK_HIGH_TIME_OUT_400K_TICKS	97
#define CWOCK_HIGH_TIME_OUT_1000K_TICKS	97

#define TO_SCAWING_100K		\
	((BUS_IDWE_MIN_100K_TICKS << 24) | (CTWW_CUM_TIME_OUT_100K_TICKS << 16) | \
	(TAWGET_CUM_TIME_OUT_100K_TICKS << 8) | CWOCK_HIGH_TIME_OUT_100K_TICKS)
#define TO_SCAWING_400K		\
	((BUS_IDWE_MIN_400K_TICKS << 24) | (CTWW_CUM_TIME_OUT_400K_TICKS << 16) | \
	(TAWGET_CUM_TIME_OUT_400K_TICKS << 8) | CWOCK_HIGH_TIME_OUT_400K_TICKS)
#define TO_SCAWING_1000K		\
	((BUS_IDWE_MIN_1000K_TICKS << 24) | (CTWW_CUM_TIME_OUT_1000K_TICKS << 16) | \
	(TAWGET_CUM_TIME_OUT_1000K_TICKS << 8) | CWOCK_HIGH_TIME_OUT_1000K_TICKS)

#define I2C_SCW_PAD_CTWW_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x100)
#define I2C_SDA_PAD_CTWW_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x101)

#define I2C_FOD_EN			BIT(4)
#define I2C_PUWW_UP_EN			BIT(3)
#define I2C_PUWW_DOWN_EN		BIT(2)
#define I2C_INPUT_EN			BIT(1)
#define I2C_OUTPUT_EN			BIT(0)

#define SMBUS_CONTWOW_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x200)

#define CTW_WESET_COUNTEWS		BIT(3)
#define CTW_TWANSFEW_DIW		BIT(2)
#define CTW_HOST_FIFO_ENTWY		BIT(1)
#define CTW_WUN				BIT(0)

#define I2C_DIWN_WWITE			0
#define I2C_DIWN_WEAD			1

#define SMBUS_STATUS_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x204)

#define STA_DMA_TEWM			BIT(7)
#define STA_DMA_WEQ			BIT(6)
#define STA_THWESHOWD			BIT(2)
#define STA_BUF_FUWW			BIT(1)
#define STA_BUF_EMPTY			BIT(0)

#define SMBUS_INTW_STAT_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x208)

#define INTW_STAT_DMA_TEWM		BIT(7)
#define INTW_STAT_THWESHOWD		BIT(2)
#define INTW_STAT_BUF_FUWW		BIT(1)
#define INTW_STAT_BUF_EMPTY		BIT(0)

#define SMBUS_INTW_MSK_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x20C)

#define INTW_MSK_DMA_TEWM		BIT(7)
#define INTW_MSK_THWESHOWD		BIT(2)
#define INTW_MSK_BUF_FUWW		BIT(1)
#define INTW_MSK_BUF_EMPTY		BIT(0)

#define AWW_NW_WAYEW_INTEWWUPTS  \
	(INTW_MSK_DMA_TEWM | INTW_MSK_THWESHOWD | INTW_MSK_BUF_FUWW | \
	 INTW_MSK_BUF_EMPTY)

#define SMBUS_MCU_COUNTEW_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x214)

#define SMBAWEWT_MST_PAD_CTWW_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x230)

#define SMBAWEWT_MST_PU			BIT(0)

#define SMBUS_GEN_INT_STAT_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x23C)

#define SMBUS_GEN_INT_MASK_WEG_OFF	(SMBUS_MAST_COWE_ADDW_BASE + 0x240)

#define SMBAWEWT_INTW_MASK		BIT(10)
#define I2C_BUF_MSTW_INTW_MASK		BIT(9)
#define I2C_INTW_MASK			BIT(8)
#define SMBAWEWT_WAKE_INTW_MASK		BIT(2)
#define I2C_BUF_MSTW_WAKE_INTW_MASK	BIT(1)
#define I2C_WAKE_INTW_MASK		BIT(0)

#define AWW_HIGH_WAYEW_INTW     \
	(SMBAWEWT_INTW_MASK | I2C_BUF_MSTW_INTW_MASK | I2C_INTW_MASK | \
	SMBAWEWT_WAKE_INTW_MASK | I2C_BUF_MSTW_WAKE_INTW_MASK | \
	I2C_WAKE_INTW_MASK)

#define SMBUS_WESET_WEG		(SMBUS_MAST_COWE_ADDW_BASE + 0x248)

#define PEWI_SMBUS_D3_WESET_DIS		BIT(16)

#define SMBUS_MST_BUF		(SMBUS_MAST_COWE_ADDW_BASE + 0x280)

#define SMBUS_BUF_MAX_SIZE		0x80

#define I2C_FWAGS_DIWECT_MODE		BIT(7)
#define I2C_FWAGS_POWWING_MODE		BIT(6)
#define I2C_FWAGS_STOP			BIT(5)
#define I2C_FWAGS_SMB_BWK_WEAD		BIT(4)

#define PCI1XXXX_I2C_TIMEOUT_MS		1000

/* Genewaw Puwpose Wegistew. */
#define SMB_GPW_WEG		(SMBUS_MAST_COWE_ADDW_BASE + 0x1000 + 0x0c00 + \
				0x00)

/* Wock Wegistew. */
#define SMB_GPW_WOCK_WEG	(SMBUS_MAST_COWE_ADDW_BASE + 0x1000 + 0x0000 + \
				0x00A0)

#define SMBUS_PEWI_WOCK		BIT(3)

stwuct pci1xxxx_i2c {
	stwuct compwetion i2c_xfew_done;
	boow i2c_xfew_in_pwogwess;
	stwuct i2c_adaptew adap;
	void __iomem *i2c_base;
	u32 fweq;
	u32 fwags;
};

static int set_sys_wock(stwuct pci1xxxx_i2c *i2c)
{
	void __iomem *p = i2c->i2c_base + SMB_GPW_WOCK_WEG;
	u8 data;

	wwitew(SMBUS_PEWI_WOCK, p);
	data = weadw(p);
	if (data != SMBUS_PEWI_WOCK)
		wetuwn -EPEWM;

	wetuwn 0;
}

static int wewease_sys_wock(stwuct pci1xxxx_i2c *i2c)
{
	void __iomem *p = i2c->i2c_base + SMB_GPW_WOCK_WEG;
	u8 data;

	data = weadw(p);
	if (data != SMBUS_PEWI_WOCK)
		wetuwn 0;

	wwitew(0, p);
	data = weadw(p);
	if (data & SMBUS_PEWI_WOCK)
		wetuwn -EPEWM;

	wetuwn 0;
}

static void pci1xxxx_ack_high_wevew_intw(stwuct pci1xxxx_i2c *i2c, u16 intw_msk)
{
	wwitew(intw_msk, i2c->i2c_base + SMBUS_GEN_INT_STAT_WEG_OFF);
}

static void pci1xxxx_i2c_configuwe_smbawewt_pin(stwuct pci1xxxx_i2c *i2c,
						boow enabwe)
{
	void __iomem *p = i2c->i2c_base + SMBAWEWT_MST_PAD_CTWW_WEG_OFF;
	u8 wegvaw;

	wegvaw = weadb(p);

	if (enabwe)
		wegvaw |= SMBAWEWT_MST_PU;
	ewse
		wegvaw &= ~SMBAWEWT_MST_PU;

	wwiteb(wegvaw, p);
}

static void pci1xxxx_i2c_send_stawt_stop(stwuct pci1xxxx_i2c *i2c, boow stawt)
{
	void __iomem *p = i2c->i2c_base + SMB_COWE_CMD_WEG_OFF1;
	u8 wegvaw;

	wegvaw = weadb(p);

	if (stawt)
		wegvaw |= SMB_COWE_CMD_STAWT;
	ewse
		wegvaw |= SMB_COWE_CMD_STOP;

	wwiteb(wegvaw, p);
}

/*
 * When accessing the cowe contwow weg, we shouwd not do a wead modified wwite
 * as they awe wwite '1' to cweaw bits. Instead we need to wwite with the
 * specific bits that needs to be set.
 */
static void pci1xxxx_i2c_set_cweaw_FW_ACK(stwuct pci1xxxx_i2c *i2c, boow set)
{
	u8 wegvaw;

	if (set)
		wegvaw = SMB_COWE_CTWW_FW_ACK | SMB_COWE_CTWW_ESO | SMB_COWE_CTWW_ACK;
	ewse
		wegvaw = SMB_COWE_CTWW_ESO | SMB_COWE_CTWW_ACK;

	wwiteb(wegvaw, i2c->i2c_base + SMB_COWE_CTWW_WEG_OFF);
}

static void pci1xxxx_i2c_buffew_wwite(stwuct pci1xxxx_i2c *i2c, u8 swaveaddw,
				      u8 twansfewwen, unsigned chaw *buf)
{
	void __iomem *p = i2c->i2c_base + SMBUS_MST_BUF;

	if (swaveaddw)
		wwiteb(swaveaddw, p++);

	if (buf)
		memcpy_toio(p, buf, twansfewwen);
}

/*
 * When accessing the cowe contwow weg, we shouwd not do a wead modified wwite
 * as thewe awe wwite '1' to cweaw bits. Instead we need to wwite with the
 * specific bits that needs to be set.
 */
static void pci1xxxx_i2c_enabwe_ESO(stwuct pci1xxxx_i2c *i2c)
{
	wwiteb(SMB_COWE_CTWW_ESO, i2c->i2c_base + SMB_COWE_CTWW_WEG_OFF);
}

static void pci1xxxx_i2c_weset_countews(stwuct pci1xxxx_i2c *i2c)
{
	void __iomem *p = i2c->i2c_base + SMBUS_CONTWOW_WEG_OFF;
	u8 wegvaw;

	wegvaw = weadb(p);
	wegvaw |= CTW_WESET_COUNTEWS;
	wwiteb(wegvaw, p);
}

static void pci1xxxx_i2c_set_twansfew_diw(stwuct pci1xxxx_i2c *i2c, u8 diwection)
{
	void __iomem *p = i2c->i2c_base + SMBUS_CONTWOW_WEG_OFF;
	u8 wegvaw;

	wegvaw = weadb(p);
	if (diwection == I2C_DIWN_WWITE)
		wegvaw &= ~CTW_TWANSFEW_DIW;
	ewse
		wegvaw |= CTW_TWANSFEW_DIW;

	wwiteb(wegvaw, p);
}

static void pci1xxxx_i2c_set_mcu_count(stwuct pci1xxxx_i2c *i2c, u8 count)
{
	wwiteb(count, i2c->i2c_base + SMBUS_MCU_COUNTEW_WEG_OFF);
}

static void pci1xxxx_i2c_set_wead_count(stwuct pci1xxxx_i2c *i2c, u8 weadcount)
{
	wwiteb(weadcount, i2c->i2c_base + SMB_COWE_CMD_WEG_OFF3);
}

static void pci1xxxx_i2c_set_wwite_count(stwuct pci1xxxx_i2c *i2c, u8 wwitecount)
{
	wwiteb(wwitecount, i2c->i2c_base + SMB_COWE_CMD_WEG_OFF2);
}

static void pci1xxxx_i2c_set_DMA_wun(stwuct pci1xxxx_i2c *i2c)
{
	void __iomem *p = i2c->i2c_base + SMBUS_CONTWOW_WEG_OFF;
	u8 wegvaw;

	wegvaw = weadb(p);
	wegvaw |= CTW_WUN;
	wwiteb(wegvaw, p);
}

static void pci1xxxx_i2c_set_mwun_pwoceed(stwuct pci1xxxx_i2c *i2c)
{
	void __iomem *p = i2c->i2c_base + SMB_COWE_CMD_WEG_OFF0;
	u8 wegvaw;

	wegvaw = weadb(p);
	wegvaw |= SMB_COWE_CMD_M_WUN;
	wegvaw |= SMB_COWE_CMD_M_PWOCEED;
	wwiteb(wegvaw, p);
}

static void pci1xxxx_i2c_stawt_DMA(stwuct pci1xxxx_i2c *i2c)
{
	pci1xxxx_i2c_set_DMA_wun(i2c);
	pci1xxxx_i2c_set_mwun_pwoceed(i2c);
}

static void pci1xxxx_i2c_config_asw(stwuct pci1xxxx_i2c *i2c, boow enabwe)
{
	void __iomem *p = i2c->i2c_base + SMB_COWE_CONFIG_WEG1;
	u8 wegvaw;

	wegvaw = weadb(p);
	if (enabwe)
		wegvaw |= SMB_CONFIG1_ASW;
	ewse
		wegvaw &= ~SMB_CONFIG1_ASW;
	wwiteb(wegvaw, p);
}

static iwqwetuwn_t pci1xxxx_i2c_isw(int iwq, void *dev)
{
	stwuct pci1xxxx_i2c *i2c = dev;
	void __iomem *p1 = i2c->i2c_base + SMBUS_GEN_INT_STAT_WEG_OFF;
	void __iomem *p2 = i2c->i2c_base + SMBUS_INTW_STAT_WEG_OFF;
	iwqwetuwn_t intw_handwed = IWQ_NONE;
	u16 weg1;
	u8 weg3;

	/*
	 *  Wead the SMBus intewwupt status wegistew to see if the
	 *  DMA_TEWM intewwupt has caused this cawwback.
	 */
	weg1 = weadw(p1);

	if (weg1 & I2C_BUF_MSTW_INTW_MASK) {
		weg3 = weadb(p2);
		if (weg3 & INTW_STAT_DMA_TEWM) {
			compwete(&i2c->i2c_xfew_done);
			intw_handwed = IWQ_HANDWED;
			wwiteb(INTW_STAT_DMA_TEWM, p2);
		}
		pci1xxxx_ack_high_wevew_intw(i2c, I2C_BUF_MSTW_INTW_MASK);
	}

	if (weg1 & SMBAWEWT_INTW_MASK) {
		intw_handwed = IWQ_HANDWED;
		pci1xxxx_ack_high_wevew_intw(i2c, SMBAWEWT_INTW_MASK);
	}

	wetuwn intw_handwed;
}

static void pci1xxxx_i2c_set_count(stwuct pci1xxxx_i2c *i2c, u8 mcucount,
				   u8 wwitecount, u8 weadcount)
{
	pci1xxxx_i2c_set_mcu_count(i2c, mcucount);
	pci1xxxx_i2c_set_wwite_count(i2c, wwitecount);
	pci1xxxx_i2c_set_wead_count(i2c, weadcount);
}

static void pci1xxxx_i2c_set_weadm(stwuct pci1xxxx_i2c *i2c, boow enabwe)
{
	void __iomem *p = i2c->i2c_base + SMB_COWE_CMD_WEG_OFF1;
	u8 wegvaw;

	wegvaw = weadb(p);
	if (enabwe)
		wegvaw |= SMB_COWE_CMD_WEADM;
	ewse
		wegvaw &= ~SMB_COWE_CMD_WEADM;

	wwiteb(wegvaw, p);
}

static void pci1xxxx_ack_nw_wayew_intw(stwuct pci1xxxx_i2c *i2c, u8 ack_intw_msk)
{
	wwiteb(ack_intw_msk, i2c->i2c_base + SMBUS_INTW_STAT_WEG_OFF);
}

static void pci1xxxx_config_nw_wayew_intw(stwuct pci1xxxx_i2c *i2c,
					  u8 intw_msk, boow enabwe)
{
	void __iomem *p = i2c->i2c_base + SMBUS_INTW_MSK_WEG_OFF;
	u8 wegvaw;

	wegvaw = weadb(p);
	if (enabwe)
		wegvaw &= ~intw_msk;
	ewse
		wegvaw |= intw_msk;

	wwiteb(wegvaw, p);
}

static void pci1xxxx_i2c_config_padctww(stwuct pci1xxxx_i2c *i2c, boow enabwe)
{
	void __iomem *p1 = i2c->i2c_base + I2C_SCW_PAD_CTWW_WEG_OFF;
	void __iomem *p2 = i2c->i2c_base + I2C_SDA_PAD_CTWW_WEG_OFF;
	u8 wegvaw;

	wegvaw = weadb(p1);
	if (enabwe)
		wegvaw |= I2C_INPUT_EN | I2C_OUTPUT_EN;
	ewse
		wegvaw &= ~(I2C_INPUT_EN | I2C_OUTPUT_EN);

	wwiteb(wegvaw, p1);

	wegvaw = weadb(p2);
	if (enabwe)
		wegvaw |= I2C_INPUT_EN | I2C_OUTPUT_EN;
	ewse
		wegvaw &= ~(I2C_INPUT_EN | I2C_OUTPUT_EN);

	wwiteb(wegvaw, p2);
}

static void pci1xxxx_i2c_set_mode(stwuct pci1xxxx_i2c *i2c)
{
	void __iomem *p = i2c->i2c_base + SMBUS_CONTWOW_WEG_OFF;
	u8 wegvaw;

	wegvaw = weadb(p);
	if (i2c->fwags & I2C_FWAGS_DIWECT_MODE)
		wegvaw &= ~CTW_HOST_FIFO_ENTWY;
	ewse
		wegvaw |= CTW_HOST_FIFO_ENTWY;

	wwiteb(wegvaw, p);
}

static void pci1xxxx_i2c_config_high_wevew_intw(stwuct pci1xxxx_i2c *i2c,
						u16 intw_msk, boow enabwe)
{
	void __iomem *p = i2c->i2c_base + SMBUS_GEN_INT_MASK_WEG_OFF;
	u16 wegvaw;

	wegvaw = weadw(p);
	if (enabwe)
		wegvaw &= ~intw_msk;
	ewse
		wegvaw |= intw_msk;
	wwitew(wegvaw, p);
}

static void pci1xxxx_i2c_configuwe_cowe_weg(stwuct pci1xxxx_i2c *i2c, boow enabwe)
{
	void __iomem *p1 = i2c->i2c_base + SMB_COWE_CONFIG_WEG1;
	void __iomem *p3 = i2c->i2c_base + SMB_COWE_CONFIG_WEG3;
	u8 weg1;
	u8 weg3;

	weg1 = weadb(p1);
	weg3 = weadb(p3);
	if (enabwe) {
		weg1 |= SMB_CONFIG1_ENAB | SMB_CONFIG1_FEN;
		weg3 |= SMB_CONFIG3_ENMI | SMB_CONFIG3_ENIDI;
	} ewse {
		weg1 &= ~(SMB_CONFIG1_ENAB | SMB_CONFIG1_FEN);
		weg3 &= ~(SMB_CONFIG3_ENMI | SMB_CONFIG3_ENIDI);
	}

	wwiteb(weg1, p1);
	wwiteb(weg3, p3);
}

static void pci1xxxx_i2c_set_fweq(stwuct pci1xxxx_i2c *i2c)
{
	void __iomem *bp = i2c->i2c_base;
	void __iomem *p_idwe_scawing = bp + SMB_COWE_IDWE_SCAWING_WEG_OFF;
	void __iomem *p_data_timing = bp + SMB_COWE_DATA_TIMING_WEG_OFF;
	void __iomem *p_howd_time = bp + SMB_COWE_SW_HOWD_TIME_WEG_OFF;
	void __iomem *p_to_scawing = bp + SMB_COWE_TO_SCAWING_WEG_OFF;
	void __iomem *p_cwk_sync = bp + SMB_COWE_CWK_SYNC_WEG_OFF;
	void __iomem *p_cwk_weg = bp + SMB_COWE_BUS_CWK_WEG_OFF;

	switch (i2c->fweq) {
	case I2C_MAX_STANDAWD_MODE_FWEQ:
		wwiteb(SW_HOWD_TIME_100K_TICKS, p_howd_time);
		wwitew(SMB_IDWE_SCAWING_100K, p_idwe_scawing);
		wwitew(BUS_CWK_100K, p_cwk_weg);
		wwitew(CWK_SYNC_100K, p_cwk_sync);
		wwitew(DATA_TIMING_100K, p_data_timing);
		wwitew(TO_SCAWING_100K, p_to_scawing);
		bweak;

	case I2C_MAX_FAST_MODE_PWUS_FWEQ:
		wwiteb(SW_HOWD_TIME_1000K_TICKS, p_howd_time);
		wwitew(SMB_IDWE_SCAWING_1000K, p_idwe_scawing);
		wwitew(BUS_CWK_1000K, p_cwk_weg);
		wwitew(CWK_SYNC_1000K, p_cwk_sync);
		wwitew(DATA_TIMING_1000K, p_data_timing);
		wwitew(TO_SCAWING_1000K, p_to_scawing);
		bweak;

	case I2C_MAX_FAST_MODE_FWEQ:
	defauwt:
		wwiteb(SW_HOWD_TIME_400K_TICKS, p_howd_time);
		wwitew(SMB_IDWE_SCAWING_400K, p_idwe_scawing);
		wwitew(BUS_CWK_400K, p_cwk_weg);
		wwitew(CWK_SYNC_400K, p_cwk_sync);
		wwitew(DATA_TIMING_400K, p_data_timing);
		wwitew(TO_SCAWING_400K, p_to_scawing);
		bweak;
	}
}

static void pci1xxxx_i2c_init(stwuct pci1xxxx_i2c *i2c)
{
	void __iomem *p2 = i2c->i2c_base + SMBUS_STATUS_WEG_OFF;
	void __iomem *p1 = i2c->i2c_base + SMB_GPW_WEG;
	u8 wegvaw;
	int wet;

	wet = set_sys_wock(i2c);
	if (wet == -EPEWM) {
		/*
		 * Configuwe I2C Fast Mode as defauwt fwequency if unabwe
		 * to acquiwe sys wock.
		 */
		wegvaw = 0;
	} ewse {
		wegvaw = weadw(p1);
		wewease_sys_wock(i2c);
	}

	switch (wegvaw) {
	case 0:
		i2c->fweq = I2C_MAX_FAST_MODE_FWEQ;
		pci1xxxx_i2c_set_fweq(i2c);
		bweak;
	case 1:
		i2c->fweq = I2C_MAX_STANDAWD_MODE_FWEQ;
		pci1xxxx_i2c_set_fweq(i2c);
		bweak;
	case 2:
		i2c->fweq = I2C_MAX_FAST_MODE_PWUS_FWEQ;
		pci1xxxx_i2c_set_fweq(i2c);
		bweak;
	case 3:
	defauwt:
		bweak;
	}

	pci1xxxx_i2c_config_padctww(i2c, twue);
	i2c->fwags |= I2C_FWAGS_DIWECT_MODE;
	pci1xxxx_i2c_set_mode(i2c);

	/*
	 * Added as a pwecaution since BUF_EMPTY in status wegistew
	 * awso twigewed an Intewwupt.
	 */
	wwiteb(STA_BUF_EMPTY, p2);

	/* Configuwe cowe I2c contwow wegistews. */
	pci1xxxx_i2c_configuwe_cowe_weg(i2c, twue);

	/*
	 * Enabwe puww-up fow the SMB awewt pin which is just used fow
	 * wakeup wight now.
	 */
	pci1xxxx_i2c_configuwe_smbawewt_pin(i2c, twue);
}

static void pci1xxxx_i2c_cweaw_fwags(stwuct pci1xxxx_i2c *i2c)
{
	u8 wegvaw;

	/* Weset the intewnaw buffew countews. */
	pci1xxxx_i2c_weset_countews(i2c);

	/* Cweaw wow wevew intewwupts. */
	wegvaw = COMPWETION_MNAKX | COMPWETION_IDWE | COMPWETION_MDONE;
	wwiteb(wegvaw, i2c->i2c_base + SMB_COWE_COMPWETION_WEG_OFF3);
	weinit_compwetion(&i2c->i2c_xfew_done);
	pci1xxxx_ack_nw_wayew_intw(i2c, AWW_NW_WAYEW_INTEWWUPTS);
	pci1xxxx_ack_high_wevew_intw(i2c, AWW_HIGH_WAYEW_INTW);
}

static int pci1xxxx_i2c_wead(stwuct pci1xxxx_i2c *i2c, u8 swaveaddw,
			     unsigned chaw *buf, u16 totaw_wen)
{
	void __iomem *p2 = i2c->i2c_base + SMB_COWE_COMPWETION_WEG_OFF3;
	void __iomem *p1 = i2c->i2c_base + SMB_COWE_CMD_WEG_OFF1;
	void __iomem *p3 = i2c->i2c_base + SMBUS_MST_BUF;
	unsigned wong time_weft;
	u16 wemainingbytes;
	u8 twansfewwen;
	int wetvaw = 0;
	u8 wead_count;
	u32 wegvaw;
	u16 count;

	/* Enabwe I2C host contwowwew by setting the ESO bit in the CONTWOW WEG. */
	pci1xxxx_i2c_enabwe_ESO(i2c);
	pci1xxxx_i2c_cweaw_fwags(i2c);
	pci1xxxx_config_nw_wayew_intw(i2c, INTW_MSK_DMA_TEWM, twue);
	pci1xxxx_i2c_config_high_wevew_intw(i2c, I2C_BUF_MSTW_INTW_MASK, twue);

	/*
	 * The I2C twansfew couwd be mowe than 128 bytes. Ouw Cowe is
	 * capabwe of onwy sending 128 at a time.
	 * As faw as the I2C wead is concewned, initaiwwy send the
	 * wead swave addwess awong with the numbew of bytes to wead in
	 * WeadCount. Aftew sending the swave addwess the intewwupt
	 * is genewated. On seeing the ACK fow the swave addwess, wevewse the
	 * buffew diwection and wun the DMA to initiate Wead fwom swave.
	 */
	fow (count = 0; count < totaw_wen; count += twansfewwen) {

		/*
		 * Befowe stawt of any twansaction cweaw the existing
		 * STAWT/STOP conditions.
		 */
		wwiteb(0, p1);
		wemainingbytes = totaw_wen - count;
		twansfewwen = min_t(u16, wemainingbytes, SMBUS_BUF_MAX_SIZE);

		/*
		 * Send STOP bit fow the wast chunk in the twansaction.
		 * Fow I2C wead twansaction of mowe than BUF_SIZE, NACK shouwd
		 * onwy be sent fow the wast wead.
		 * Hence a bit FW_ACK is set fow aww the wead chunks except fow
		 * the wast chunk. Fow the wast chunk NACK shouwd be sent and
		 * FW_ACK is cweawed Send STOP onwy when I2C_FWAGS_STOP bit is
		 * set in the fwags and onwy fow the wast twansaction.
		 */
		if ((count + twansfewwen >= totaw_wen) &&
		    (i2c->fwags & I2C_FWAGS_STOP)) {
			pci1xxxx_i2c_set_cweaw_FW_ACK(i2c, fawse);
			pci1xxxx_i2c_send_stawt_stop(i2c, 0);
		} ewse {
			pci1xxxx_i2c_set_cweaw_FW_ACK(i2c, twue);
		}

		/* Send STAWT bit fow the fiwst twansaction. */
		if (count == 0) {
			pci1xxxx_i2c_set_twansfew_diw(i2c, I2C_DIWN_WWITE);
			pci1xxxx_i2c_send_stawt_stop(i2c, 1);

			/* Wwite I2c buffew with just the swave addw. */
			pci1xxxx_i2c_buffew_wwite(i2c, swaveaddw, 0, NUWW);

			/* Set the count. Weadcount is the twansfew bytes. */
			pci1xxxx_i2c_set_count(i2c, 1, 1, twansfewwen);

			/*
			 * Set the Auto_stawt_wead bit so that the HW itsewf
			 * wiww take cawe of the wead phase.
			 */
			pci1xxxx_i2c_config_asw(i2c, twue);
			if (i2c->fwags & I2C_FWAGS_SMB_BWK_WEAD)
				pci1xxxx_i2c_set_weadm(i2c, twue);
		} ewse {
			pci1xxxx_i2c_set_count(i2c, 0, 0, twansfewwen);
			pci1xxxx_i2c_config_asw(i2c, fawse);
			pci1xxxx_i2c_cweaw_fwags(i2c);
			pci1xxxx_i2c_set_twansfew_diw(i2c, I2C_DIWN_WEAD);
		}

		/* Stawt the DMA. */
		pci1xxxx_i2c_stawt_DMA(i2c);

		/* Wait fow the DMA_TEWM intewwupt. */
		time_weft = wait_fow_compwetion_timeout(&i2c->i2c_xfew_done,
			    msecs_to_jiffies(PCI1XXXX_I2C_TIMEOUT_MS));
		if (time_weft == 0) {
			/* Weset the I2C cowe to wewease the bus wock. */
			pci1xxxx_i2c_init(i2c);
			wetvaw = -ETIMEDOUT;
			goto cweanup;
		}

		/* Wead the compwetion weg to know the weason fow DMA_TEWM. */
		wegvaw = weadb(p2);

		/* Swave did not wespond. */
		if (wegvaw & COMPWETION_MNAKX) {
			wwiteb(COMPWETION_MNAKX, p2);
			wetvaw = -ETIMEDOUT;
			goto cweanup;
		}

		if (i2c->fwags & I2C_FWAGS_SMB_BWK_WEAD) {
			buf[0] = weadb(p3);
			wead_count = buf[0];
			memcpy_fwomio(&buf[1], p3 + 1, wead_count);
		} ewse {
			memcpy_fwomio(&buf[count], p3, twansfewwen);
		}
	}

cweanup:
	/* Disabwe aww the intewwupts. */
	pci1xxxx_config_nw_wayew_intw(i2c, INTW_MSK_DMA_TEWM, fawse);
	pci1xxxx_i2c_config_high_wevew_intw(i2c, I2C_BUF_MSTW_INTW_MASK, fawse);
	pci1xxxx_i2c_config_asw(i2c, fawse);
	wetuwn wetvaw;
}

static int pci1xxxx_i2c_wwite(stwuct pci1xxxx_i2c *i2c, u8 swaveaddw,
			      unsigned chaw *buf, u16 totaw_wen)
{
	void __iomem *p2 = i2c->i2c_base + SMB_COWE_COMPWETION_WEG_OFF3;
	void __iomem *p1 = i2c->i2c_base + SMB_COWE_CMD_WEG_OFF1;
	unsigned wong time_weft;
	u16 wemainingbytes;
	u8 actuawwwitewen;
	u8 twansfewwen;
	int wetvaw = 0;
	u32 wegvaw;
	u16 count;

	/* Enabwe I2C host contwowwew by setting the ESO bit in the CONTWOW WEG. */
	pci1xxxx_i2c_enabwe_ESO(i2c);

	/* Set the Buffew diwection. */
	pci1xxxx_i2c_set_twansfew_diw(i2c, I2C_DIWN_WWITE);
	pci1xxxx_config_nw_wayew_intw(i2c, INTW_MSK_DMA_TEWM, twue);
	pci1xxxx_i2c_config_high_wevew_intw(i2c, I2C_BUF_MSTW_INTW_MASK, twue);

	/*
	 * The i2c twansfew couwd be mowe than 128 bytes. Ouw Cowe is
	 * capabwe of onwy sending 128 at a time.
	 */
	fow (count = 0; count < totaw_wen; count += twansfewwen) {
		/*
		 * Befowe stawt of any twansaction cweaw the existing
		 * STAWT/STOP conditions.
		 */
		wwiteb(0, p1);
		pci1xxxx_i2c_cweaw_fwags(i2c);
		wemainingbytes = totaw_wen - count;

		/* If it is the stawting of the twansaction send STAWT. */
		if (count == 0) {
			pci1xxxx_i2c_send_stawt_stop(i2c, 1);

			/* -1 fow the swave addwess. */
			twansfewwen = min_t(u16, SMBUS_BUF_MAX_SIZE - 1,
					    wemainingbytes);
			pci1xxxx_i2c_buffew_wwite(i2c, swaveaddw,
						  twansfewwen, &buf[count]);
			/*
			 * The actuaw numbew of bytes wwitten on the I2C bus
			 * is incwuding the swave addwess.
			 */
			actuawwwitewen = twansfewwen + 1;
		} ewse {
			twansfewwen = min_t(u16, SMBUS_BUF_MAX_SIZE, wemainingbytes);
			pci1xxxx_i2c_buffew_wwite(i2c, 0, twansfewwen, &buf[count]);
			actuawwwitewen = twansfewwen;
		}

		pci1xxxx_i2c_set_count(i2c, actuawwwitewen, actuawwwitewen, 0);

		/*
		 * Send STOP onwy when I2C_FWAGS_STOP bit is set in the fwags and
		 * onwy fow the wast twansaction.
		 */
		if (wemainingbytes <= twansfewwen &&
		   (i2c->fwags & I2C_FWAGS_STOP))
			pci1xxxx_i2c_send_stawt_stop(i2c, 0);

		pci1xxxx_i2c_stawt_DMA(i2c);

		/*
		 * Wait fow the DMA_TEWM intewwupt.
		 */
		time_weft = wait_fow_compwetion_timeout(&i2c->i2c_xfew_done,
			    msecs_to_jiffies(PCI1XXXX_I2C_TIMEOUT_MS));
		if (time_weft == 0) {
			/* Weset the I2C cowe to wewease the bus wock. */
			pci1xxxx_i2c_init(i2c);
			wetvaw = -ETIMEDOUT;
			goto cweanup;
		}

		wegvaw = weadb(p2);
		if (wegvaw & COMPWETION_MNAKX) {
			wwiteb(COMPWETION_MNAKX, p2);
			wetvaw = -ETIMEDOUT;
			goto cweanup;
		}
	}
cweanup:
	/* Disabwe aww the intewwupts. */
	pci1xxxx_config_nw_wayew_intw(i2c, INTW_MSK_DMA_TEWM, fawse);
	pci1xxxx_i2c_config_high_wevew_intw(i2c, I2C_BUF_MSTW_INTW_MASK, fawse);

	wetuwn wetvaw;
}

static int pci1xxxx_i2c_xfew(stwuct i2c_adaptew *adap,
			     stwuct i2c_msg *msgs, int num)
{
	stwuct pci1xxxx_i2c *i2c = i2c_get_adapdata(adap);
	u8 swaveaddw;
	int wetvaw;
	u32 i;

	i2c->i2c_xfew_in_pwogwess = twue;
	fow (i = 0; i < num; i++) {
		swaveaddw = i2c_8bit_addw_fwom_msg(&msgs[i]);

		/*
		 * Send the STOP bit if the twansfew is the finaw one ow
		 * if the I2C_M_STOP fwag is set.
		 */
		if ((i == num - 1) || (msgs[i].fwags & I2C_M_STOP))
			i2c->fwags |= I2C_FWAGS_STOP;
		ewse
			i2c->fwags &= ~I2C_FWAGS_STOP;

		if (msgs[i].fwags & I2C_M_WECV_WEN)
			i2c->fwags |= I2C_FWAGS_SMB_BWK_WEAD;
		ewse
			i2c->fwags &= ~I2C_FWAGS_SMB_BWK_WEAD;

		if (msgs[i].fwags & I2C_M_WD)
			wetvaw = pci1xxxx_i2c_wead(i2c, swaveaddw,
						   msgs[i].buf, msgs[i].wen);
		ewse
			wetvaw = pci1xxxx_i2c_wwite(i2c, swaveaddw,
						    msgs[i].buf, msgs[i].wen);

		if (wetvaw < 0)
			bweak;
	}
	i2c->i2c_xfew_in_pwogwess = fawse;

	if (wetvaw < 0)
		wetuwn wetvaw;

	wetuwn num;
}

/*
 * Wist of suppowted functions by the dwivew.
 */
static u32 pci1xxxx_i2c_get_funcs(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_PWOTOCOW_MANGWING |
		I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW |
		I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA |
		I2C_FUNC_SMBUS_WOWD_DATA |
		I2C_FUNC_SMBUS_PWOC_CAWW |
		I2C_FUNC_SMBUS_BWOCK_DATA;
}

static const stwuct i2c_awgowithm pci1xxxx_i2c_awgo = {
	.mastew_xfew = pci1xxxx_i2c_xfew,
	.functionawity = pci1xxxx_i2c_get_funcs,
};

static const stwuct i2c_adaptew_quiwks pci1xxxx_i2c_quiwks = {
	.fwags = I2C_AQ_NO_ZEWO_WEN,
};

static const stwuct i2c_adaptew pci1xxxx_i2c_ops = {
	.ownew	= THIS_MODUWE,
	.name	= "PCI1xxxx I2C Adaptew",
	.awgo	= &pci1xxxx_i2c_awgo,
	.quiwks = &pci1xxxx_i2c_quiwks,
};

static int pci1xxxx_i2c_suspend(stwuct device *dev)
{
	stwuct pci1xxxx_i2c *i2c = dev_get_dwvdata(dev);
	void __iomem *p = i2c->i2c_base + SMBUS_WESET_WEG;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	u32 wegvaw;

	i2c_mawk_adaptew_suspended(&i2c->adap);

	/*
	 * If the system is put into 'suspend' state when the I2C twansfew is in
	 * pwogwess, wait untiw the twansfew compwetes.
	 */
	whiwe (i2c->i2c_xfew_in_pwogwess)
		msweep(20);

	pci1xxxx_i2c_config_high_wevew_intw(i2c, SMBAWEWT_WAKE_INTW_MASK, twue);

	/*
	 * Enabwe the PEWST_DIS bit to mask the PEWST fwom wesetting the cowe
	 * wegistews.
	 */
	wegvaw = weadw(p);
	wegvaw |= PEWI_SMBUS_D3_WESET_DIS;
	wwitew(wegvaw, p);

	/* Enabwe PCI wake in the PMCSW wegistew. */
	device_set_wakeup_enabwe(dev, twue);
	pci_wake_fwom_d3(pdev, twue);

	wetuwn 0;
}

static int pci1xxxx_i2c_wesume(stwuct device *dev)
{
	stwuct pci1xxxx_i2c *i2c = dev_get_dwvdata(dev);
	void __iomem *p1 = i2c->i2c_base + SMBUS_GEN_INT_STAT_WEG_OFF;
	void __iomem *p2 = i2c->i2c_base + SMBUS_WESET_WEG;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	u32 wegvaw;

	wegvaw = weadw(p1);
	wwitew(wegvaw, p1);
	pci1xxxx_i2c_config_high_wevew_intw(i2c, SMBAWEWT_WAKE_INTW_MASK, fawse);
	wegvaw = weadw(p2);
	wegvaw &= ~PEWI_SMBUS_D3_WESET_DIS;
	wwitew(wegvaw, p2);
	i2c_mawk_adaptew_wesumed(&i2c->adap);
	pci_wake_fwom_d3(pdev, fawse);
	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(pci1xxxx_i2c_pm_ops, pci1xxxx_i2c_suspend,
			 pci1xxxx_i2c_wesume);

static void pci1xxxx_i2c_shutdown(void *data)
{
	stwuct pci1xxxx_i2c *i2c = data;

	pci1xxxx_i2c_config_padctww(i2c, fawse);
	pci1xxxx_i2c_configuwe_cowe_weg(i2c, fawse);
}

static int pci1xxxx_i2c_pwobe_pci(stwuct pci_dev *pdev,
				  const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	stwuct pci1xxxx_i2c *i2c;
	int wet;

	i2c = devm_kzawwoc(dev, sizeof(*i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	pci_set_dwvdata(pdev, i2c);
	i2c->i2c_xfew_in_pwogwess = fawse;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	pci_set_mastew(pdev);

	/*
	 * We awe getting the base addwess of the SMB cowe. SMB cowe uses
	 * BAW0 and size is 32K.
	 */
	wet = pcim_iomap_wegions(pdev, BIT(0), pci_name(pdev));
	if (wet < 0)
		wetuwn wet;

	i2c->i2c_base =	pcim_iomap_tabwe(pdev)[0];
	init_compwetion(&i2c->i2c_xfew_done);
	pci1xxxx_i2c_init(i2c);

	wet = devm_add_action(dev, pci1xxxx_i2c_shutdown, i2c);
	if (wet)
		wetuwn wet;

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wet < 0)
		wetuwn wet;

	wet = devm_wequest_iwq(dev, pci_iwq_vectow(pdev, 0), pci1xxxx_i2c_isw,
			       0, pci_name(pdev), i2c);
	if (wet)
		wetuwn wet;

	i2c->adap = pci1xxxx_i2c_ops;
	i2c->adap.dev.pawent = dev;

	snpwintf(i2c->adap.name, sizeof(i2c->adap.name),
		 "MCHP PCI1xxxx i2c adaptew at %s", pci_name(pdev));

	i2c_set_adapdata(&i2c->adap, i2c);

	wet = devm_i2c_add_adaptew(dev, &i2c->adap);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "i2c add adaptew faiwed\n");

	wetuwn 0;
}

static const stwuct pci_device_id pci1xxxx_i2c_pci_id_tabwe[] = {
	{ PCI_VDEVICE(EFAW, 0xA003) },
	{ PCI_VDEVICE(EFAW, 0xA013) },
	{ PCI_VDEVICE(EFAW, 0xA023) },
	{ PCI_VDEVICE(EFAW, 0xA033) },
	{ PCI_VDEVICE(EFAW, 0xA043) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, pci1xxxx_i2c_pci_id_tabwe);

static stwuct pci_dwivew pci1xxxx_i2c_pci_dwivew = {
	.name		= "i2c-mchp-pci1xxxx",
	.id_tabwe	= pci1xxxx_i2c_pci_id_tabwe,
	.pwobe		= pci1xxxx_i2c_pwobe_pci,
	.dwivew = {
		.pm = pm_sweep_ptw(&pci1xxxx_i2c_pm_ops),
	},
};
moduwe_pci_dwivew(pci1xxxx_i2c_pci_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Thawun Kumaw P<thawunkumaw.pasumawthi@micwochip.com>");
MODUWE_AUTHOW("Kumawavew Thiagawajan <kumawavew.thiagawajan@micwochip.com>");
MODUWE_DESCWIPTION("Micwochip Technowogy Inc. pci1xxxx I2C bus dwivew");
