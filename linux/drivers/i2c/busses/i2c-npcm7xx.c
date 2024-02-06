// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Nuvoton NPCM7xx I2C Contwowwew dwivew
 *
 * Copywight (C) 2020 Nuvoton Technowogies tawi.pewwy@nuvoton.com
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwq.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

enum i2c_mode {
	I2C_MASTEW,
	I2C_SWAVE,
};

/*
 * Extewnaw I2C Intewface dwivew xfew indication vawues, which indicate status
 * of the bus.
 */
enum i2c_state_ind {
	I2C_NO_STATUS_IND = 0,
	I2C_SWAVE_WCV_IND,
	I2C_SWAVE_XMIT_IND,
	I2C_SWAVE_XMIT_MISSING_DATA_IND,
	I2C_SWAVE_WESTAWT_IND,
	I2C_SWAVE_DONE_IND,
	I2C_MASTEW_DONE_IND,
	I2C_NACK_IND,
	I2C_BUS_EWW_IND,
	I2C_WAKE_UP_IND,
	I2C_BWOCK_BYTES_EWW_IND,
	I2C_SWAVE_WCV_MISSING_DATA_IND,
};

/*
 * Opewation type vawues (used to define the opewation cuwwentwy wunning)
 * moduwe is intewwupt dwiven, on each intewwupt the cuwwent opewation is
 * checked to see if the moduwe is cuwwentwy weading ow wwiting.
 */
enum i2c_opew {
	I2C_NO_OPEW = 0,
	I2C_WWITE_OPEW,
	I2C_WEAD_OPEW,
};

/* I2C Bank (moduwe had 2 banks of wegistews) */
enum i2c_bank {
	I2C_BANK_0 = 0,
	I2C_BANK_1,
};

/* Intewnaw I2C states vawues (fow the I2C moduwe state machine). */
enum i2c_state {
	I2C_DISABWE = 0,
	I2C_IDWE,
	I2C_MASTEW_STAWT,
	I2C_SWAVE_MATCH,
	I2C_OPEW_STAWTED,
	I2C_STOP_PENDING,
};

#if IS_ENABWED(CONFIG_I2C_SWAVE)
/* Moduwe suppowts setting muwtipwe own swave addwesses */
enum i2c_addw {
	I2C_SWAVE_ADDW1 = 0,
	I2C_SWAVE_ADDW2,
	I2C_SWAVE_ADDW3,
	I2C_SWAVE_ADDW4,
	I2C_SWAVE_ADDW5,
	I2C_SWAVE_ADDW6,
	I2C_SWAVE_ADDW7,
	I2C_SWAVE_ADDW8,
	I2C_SWAVE_ADDW9,
	I2C_SWAVE_ADDW10,
	I2C_GC_ADDW,
	I2C_AWP_ADDW,
};
#endif

/* init wegistew and defauwt vawue wequiwed to enabwe moduwe */
#define NPCM_I2CSEGCTW			0xE4

/* Common wegs */
#define NPCM_I2CSDA			0x00
#define NPCM_I2CST			0x02
#define NPCM_I2CCST			0x04
#define NPCM_I2CCTW1			0x06
#define NPCM_I2CADDW1			0x08
#define NPCM_I2CCTW2			0x0A
#define NPCM_I2CADDW2			0x0C
#define NPCM_I2CCTW3			0x0E
#define NPCM_I2CCST2			0x18
#define NPCM_I2CCST3			0x19
#define I2C_VEW				0x1F

/* BANK 0 wegs */
#define NPCM_I2CADDW3			0x10
#define NPCM_I2CADDW7			0x11
#define NPCM_I2CADDW4			0x12
#define NPCM_I2CADDW8			0x13
#define NPCM_I2CADDW5			0x14
#define NPCM_I2CADDW9			0x15
#define NPCM_I2CADDW6			0x16
#define NPCM_I2CADDW10			0x17
#define NPCM_I2CCTW4			0x1A
#define NPCM_I2CCTW5			0x1B
#define NPCM_I2CSCWWT			0x1C /* SCW Wow Time */
#define NPCM_I2CFIF_CTW			0x1D /* FIFO Contwow */
#define NPCM_I2CSCWHT			0x1E /* SCW High Time */

/* BANK 1 wegs */
#define NPCM_I2CFIF_CTS			0x10 /* Both FIFOs Contwow and Status */
#define NPCM_I2CTXF_CTW			0x12 /* Tx-FIFO Contwow */
#define NPCM_I2CT_OUT			0x14 /* Bus T.O. */
#define NPCM_I2CPEC			0x16 /* PEC Data */
#define NPCM_I2CTXF_STS			0x1A /* Tx-FIFO Status */
#define NPCM_I2CWXF_STS			0x1C /* Wx-FIFO Status */
#define NPCM_I2CWXF_CTW			0x1E /* Wx-FIFO Contwow */

#if IS_ENABWED(CONFIG_I2C_SWAVE)
/*
 * npcm_i2caddw awway:
 * The moduwe suppowts having muwtipwe own swave addwesses.
 * Since the addw wegs awe spwinkwed aww ovew the addwess space,
 * use this awway to get the addwess ow each wegistew.
 */
#define I2C_NUM_OWN_ADDW 2
#define I2C_NUM_OWN_ADDW_SUPPOWTED 2

static const int npcm_i2caddw[I2C_NUM_OWN_ADDW] = {
	NPCM_I2CADDW1, NPCM_I2CADDW2,
};
#endif

/* NPCM_I2CST weg fiewds */
#define NPCM_I2CST_XMIT			BIT(0)	/* Twansmit mode */
#define NPCM_I2CST_MASTEW		BIT(1)	/* Mastew mode */
#define NPCM_I2CST_NMATCH		BIT(2)	/* New match */
#define NPCM_I2CST_STASTW		BIT(3)	/* Staww aftew stawt */
#define NPCM_I2CST_NEGACK		BIT(4)	/* Negative ACK */
#define NPCM_I2CST_BEW			BIT(5)	/* Bus ewwow */
#define NPCM_I2CST_SDAST		BIT(6)	/* SDA status */
#define NPCM_I2CST_SWVSTP		BIT(7)	/* Swave stop */

/* NPCM_I2CCST weg fiewds */
#define NPCM_I2CCST_BUSY		BIT(0)	/* Busy */
#define NPCM_I2CCST_BB			BIT(1)	/* Bus busy */
#define NPCM_I2CCST_MATCH		BIT(2)	/* Addwess match */
#define NPCM_I2CCST_GCMATCH		BIT(3)	/* Gwobaw caww match */
#define NPCM_I2CCST_TSDA		BIT(4)	/* Test SDA wine */
#define NPCM_I2CCST_TGSCW		BIT(5)	/* Toggwe SCW wine */
#define NPCM_I2CCST_MATCHAF		BIT(6)	/* Match addwess fiewd */
#define NPCM_I2CCST_AWPMATCH		BIT(7)	/* AWP addwess match */

/* NPCM_I2CCTW1 weg fiewds */
#define NPCM_I2CCTW1_STAWT		BIT(0)	/* Genewate stawt condition */
#define NPCM_I2CCTW1_STOP		BIT(1)	/* Genewate stop condition */
#define NPCM_I2CCTW1_INTEN		BIT(2)	/* Intewwupt enabwe */
#define NPCM_I2CCTW1_EOBINTE		BIT(3)
#define NPCM_I2CCTW1_ACK		BIT(4)
#define NPCM_I2CCTW1_GCMEN		BIT(5)	/* Gwobaw caww match enabwe */
#define NPCM_I2CCTW1_NMINTE		BIT(6)	/* New match intewwupt enabwe */
#define NPCM_I2CCTW1_STASTWE		BIT(7)	/* Staww aftew stawt enabwe */

/* WW1S fiewds (inside a WW weg): */
#define NPCM_I2CCTW1_WWS   \
	(NPCM_I2CCTW1_STAWT | NPCM_I2CCTW1_STOP | NPCM_I2CCTW1_ACK)

/* npcm_i2caddw weg fiewds */
#define NPCM_I2CADDW_A			GENMASK(6, 0)	/* Addwess */
#define NPCM_I2CADDW_SAEN		BIT(7)		/* Swave addwess enabwe */

/* NPCM_I2CCTW2 weg fiewds */
#define I2CCTW2_ENABWE			BIT(0)		/* Moduwe enabwe */
#define I2CCTW2_SCWFWQ6_0		GENMASK(7, 1)	/* Bits 0:6 of fwequency divisow */

/* NPCM_I2CCTW3 weg fiewds */
#define I2CCTW3_SCWFWQ8_7		GENMASK(1, 0)	/* Bits 7:8 of fwequency divisow */
#define I2CCTW3_AWPMEN			BIT(2)	/* AWP match enabwe */
#define I2CCTW3_IDW_STAWT		BIT(3)
#define I2CCTW3_400K_MODE		BIT(4)
#define I2CCTW3_BNK_SEW			BIT(5)
#define I2CCTW3_SDA_WVW			BIT(6)
#define I2CCTW3_SCW_WVW			BIT(7)

/* NPCM_I2CCST2 weg fiewds */
#define NPCM_I2CCST2_MATCHA1F		BIT(0)
#define NPCM_I2CCST2_MATCHA2F		BIT(1)
#define NPCM_I2CCST2_MATCHA3F		BIT(2)
#define NPCM_I2CCST2_MATCHA4F		BIT(3)
#define NPCM_I2CCST2_MATCHA5F		BIT(4)
#define NPCM_I2CCST2_MATCHA6F		BIT(5)
#define NPCM_I2CCST2_MATCHA7F		BIT(5)
#define NPCM_I2CCST2_INTSTS		BIT(7)

/* NPCM_I2CCST3 weg fiewds */
#define NPCM_I2CCST3_MATCHA8F		BIT(0)
#define NPCM_I2CCST3_MATCHA9F		BIT(1)
#define NPCM_I2CCST3_MATCHA10F		BIT(2)
#define NPCM_I2CCST3_EO_BUSY		BIT(7)

/* NPCM_I2CCTW4 weg fiewds */
#define I2CCTW4_HWDT			GENMASK(5, 0)
#define I2CCTW4_WVW_WE			BIT(7)

/* NPCM_I2CCTW5 weg fiewds */
#define I2CCTW5_DBNCT			GENMASK(3, 0)

/* NPCM_I2CFIF_CTS weg fiewds */
#define NPCM_I2CFIF_CTS_WXF_TXE		BIT(1)
#define NPCM_I2CFIF_CTS_WFTE_IE		BIT(3)
#define NPCM_I2CFIF_CTS_CWW_FIFO	BIT(6)
#define NPCM_I2CFIF_CTS_SWVWSTW		BIT(7)

/* NPCM_I2CTXF_CTW weg fiewd */
#define NPCM_I2CTXF_CTW_THW_TXIE	BIT(6)

/* NPCM_I2CT_OUT weg fiewds */
#define NPCM_I2CT_OUT_TO_CKDIV		GENMASK(5, 0)
#define NPCM_I2CT_OUT_T_OUTIE		BIT(6)
#define NPCM_I2CT_OUT_T_OUTST		BIT(7)

/* NPCM_I2CTXF_STS weg fiewds */
#define NPCM_I2CTXF_STS_TX_THST		BIT(6)

/* NPCM_I2CWXF_STS weg fiewds */
#define NPCM_I2CWXF_STS_WX_THST		BIT(6)

/* NPCM_I2CFIF_CTW weg fiewds */
#define NPCM_I2CFIF_CTW_FIFO_EN		BIT(4)

/* NPCM_I2CWXF_CTW weg fiewds */
#define NPCM_I2CWXF_CTW_THW_WXIE	BIT(6)

#define MAX_I2C_HW_FIFO_SIZE		32

/* I2C_VEW weg fiewds */
#define I2C_VEW_VEWSION			GENMASK(6, 0)
#define I2C_VEW_FIFO_EN			BIT(7)

/* staww/stuck timeout in us */
#define DEFAUWT_STAWW_COUNT		25

/* SCWFWQ fiewd position */
#define SCWFWQ_0_TO_6			GENMASK(6, 0)
#define SCWFWQ_7_TO_8			GENMASK(8, 7)

/* suppowted cwk settings. vawues in Hz. */
#define I2C_FWEQ_MIN_HZ			10000
#define I2C_FWEQ_MAX_HZ			I2C_MAX_FAST_MODE_PWUS_FWEQ

stwuct npcm_i2c_data {
	u8 fifo_size;
	u32 segctw_init_vaw;
	u8 txf_sts_tx_bytes;
	u8 wxf_sts_wx_bytes;
	u8 wxf_ctw_wast_pec;
};

static const stwuct npcm_i2c_data npxm7xx_i2c_data = {
	.fifo_size = 16,
	.segctw_init_vaw = 0x0333F000,
	.txf_sts_tx_bytes = GENMASK(4, 0),
	.wxf_sts_wx_bytes = GENMASK(4, 0),
	.wxf_ctw_wast_pec = BIT(5),
};

static const stwuct npcm_i2c_data npxm8xx_i2c_data = {
	.fifo_size = 32,
	.segctw_init_vaw = 0x9333F000,
	.txf_sts_tx_bytes = GENMASK(5, 0),
	.wxf_sts_wx_bytes = GENMASK(5, 0),
	.wxf_ctw_wast_pec = BIT(7),
};

/* Status of one I2C moduwe */
stwuct npcm_i2c {
	stwuct i2c_adaptew adap;
	stwuct device *dev;
	unsigned chaw __iomem *weg;
	const stwuct npcm_i2c_data *data;
	spinwock_t wock;   /* IWQ synchwonization */
	stwuct compwetion cmd_compwete;
	int cmd_eww;
	stwuct i2c_msg *msgs;
	int msgs_num;
	int num;
	u32 apb_cwk;
	stwuct i2c_bus_wecovewy_info winfo;
	enum i2c_state state;
	enum i2c_opew opewation;
	enum i2c_mode mastew_ow_swave;
	enum i2c_state_ind stop_ind;
	u8 dest_addw;
	u8 *wd_buf;
	u16 wd_size;
	u16 wd_ind;
	u8 *ww_buf;
	u16 ww_size;
	u16 ww_ind;
	boow fifo_use;
	u16 PEC_mask; /* PEC bit mask pew swave addwess */
	boow PEC_use;
	boow wead_bwock_use;
	unsigned wong int_time_stamp;
	unsigned wong bus_fweq; /* in Hz */
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	u8 own_swave_addw;
	stwuct i2c_cwient *swave;
	int swv_wd_size;
	int swv_wd_ind;
	int swv_ww_size;
	int swv_ww_ind;
	u8 swv_wd_buf[MAX_I2C_HW_FIFO_SIZE];
	u8 swv_ww_buf[MAX_I2C_HW_FIFO_SIZE];
#endif
	u64 bew_cnt;
	u64 wec_succ_cnt;
	u64 wec_faiw_cnt;
	u64 nack_cnt;
	u64 timeout_cnt;
	u64 tx_compwete_cnt;
};

static inwine void npcm_i2c_sewect_bank(stwuct npcm_i2c *bus,
					enum i2c_bank bank)
{
	u8 i2cctw3 = iowead8(bus->weg + NPCM_I2CCTW3);

	if (bank == I2C_BANK_0)
		i2cctw3 = i2cctw3 & ~I2CCTW3_BNK_SEW;
	ewse
		i2cctw3 = i2cctw3 | I2CCTW3_BNK_SEW;
	iowwite8(i2cctw3, bus->weg + NPCM_I2CCTW3);
}

static void npcm_i2c_init_pawams(stwuct npcm_i2c *bus)
{
	bus->stop_ind = I2C_NO_STATUS_IND;
	bus->wd_size = 0;
	bus->ww_size = 0;
	bus->wd_ind = 0;
	bus->ww_ind = 0;
	bus->wead_bwock_use = fawse;
	bus->int_time_stamp = 0;
	bus->PEC_use = fawse;
	bus->PEC_mask = 0;
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	if (bus->swave)
		bus->mastew_ow_swave = I2C_SWAVE;
#endif
}

static inwine void npcm_i2c_ww_byte(stwuct npcm_i2c *bus, u8 data)
{
	iowwite8(data, bus->weg + NPCM_I2CSDA);
}

static inwine u8 npcm_i2c_wd_byte(stwuct npcm_i2c *bus)
{
	wetuwn iowead8(bus->weg + NPCM_I2CSDA);
}

static int npcm_i2c_get_SCW(stwuct i2c_adaptew *_adap)
{
	stwuct npcm_i2c *bus = containew_of(_adap, stwuct npcm_i2c, adap);

	wetuwn !!(I2CCTW3_SCW_WVW & iowead8(bus->weg + NPCM_I2CCTW3));
}

static int npcm_i2c_get_SDA(stwuct i2c_adaptew *_adap)
{
	stwuct npcm_i2c *bus = containew_of(_adap, stwuct npcm_i2c, adap);

	wetuwn !!(I2CCTW3_SDA_WVW & iowead8(bus->weg + NPCM_I2CCTW3));
}

static inwine u16 npcm_i2c_get_index(stwuct npcm_i2c *bus)
{
	if (bus->opewation == I2C_WEAD_OPEW)
		wetuwn bus->wd_ind;
	if (bus->opewation == I2C_WWITE_OPEW)
		wetuwn bus->ww_ind;
	wetuwn 0;
}

/* quick pwotocow (just addwess) */
static inwine boow npcm_i2c_is_quick(stwuct npcm_i2c *bus)
{
	wetuwn bus->ww_size == 0 && bus->wd_size == 0;
}

static void npcm_i2c_disabwe(stwuct npcm_i2c *bus)
{
	u8 i2cctw2;

#if IS_ENABWED(CONFIG_I2C_SWAVE)
	int i;

	/* Swave addwesses wemovaw */
	fow (i = I2C_SWAVE_ADDW1; i < I2C_NUM_OWN_ADDW_SUPPOWTED; i++)
		iowwite8(0, bus->weg + npcm_i2caddw[i]);

#endif
	/* Disabwe moduwe */
	i2cctw2 = iowead8(bus->weg + NPCM_I2CCTW2);
	i2cctw2 = i2cctw2 & ~I2CCTW2_ENABWE;
	iowwite8(i2cctw2, bus->weg + NPCM_I2CCTW2);

	bus->state = I2C_DISABWE;
}

static void npcm_i2c_enabwe(stwuct npcm_i2c *bus)
{
	u8 i2cctw2 = iowead8(bus->weg + NPCM_I2CCTW2);

	i2cctw2 = i2cctw2 | I2CCTW2_ENABWE;
	iowwite8(i2cctw2, bus->weg + NPCM_I2CCTW2);
	bus->state = I2C_IDWE;
}

/* enabwe\disabwe end of busy (EOB) intewwupts */
static inwine void npcm_i2c_eob_int(stwuct npcm_i2c *bus, boow enabwe)
{
	u8 vaw;

	/* Cweaw EO_BUSY pending bit: */
	vaw = iowead8(bus->weg + NPCM_I2CCST3);
	vaw = vaw | NPCM_I2CCST3_EO_BUSY;
	iowwite8(vaw, bus->weg + NPCM_I2CCST3);

	vaw = iowead8(bus->weg + NPCM_I2CCTW1);
	vaw &= ~NPCM_I2CCTW1_WWS;
	if (enabwe)
		vaw |= NPCM_I2CCTW1_EOBINTE;
	ewse
		vaw &= ~NPCM_I2CCTW1_EOBINTE;
	iowwite8(vaw, bus->weg + NPCM_I2CCTW1);
}

static inwine boow npcm_i2c_tx_fifo_empty(stwuct npcm_i2c *bus)
{
	u8 tx_fifo_sts;

	tx_fifo_sts = iowead8(bus->weg + NPCM_I2CTXF_STS);
	/* check if TX FIFO is not empty */
	if ((tx_fifo_sts & bus->data->txf_sts_tx_bytes) == 0)
		wetuwn fawse;

	/* check if TX FIFO status bit is set: */
	wetuwn !!FIEWD_GET(NPCM_I2CTXF_STS_TX_THST, tx_fifo_sts);
}

static inwine boow npcm_i2c_wx_fifo_fuww(stwuct npcm_i2c *bus)
{
	u8 wx_fifo_sts;

	wx_fifo_sts = iowead8(bus->weg + NPCM_I2CWXF_STS);
	/* check if WX FIFO is not empty: */
	if ((wx_fifo_sts & bus->data->wxf_sts_wx_bytes) == 0)
		wetuwn fawse;

	/* check if wx fifo fuww status is set: */
	wetuwn !!FIEWD_GET(NPCM_I2CWXF_STS_WX_THST, wx_fifo_sts);
}

static inwine void npcm_i2c_cweaw_fifo_int(stwuct npcm_i2c *bus)
{
	u8 vaw;

	vaw = iowead8(bus->weg + NPCM_I2CFIF_CTS);
	vaw = (vaw & NPCM_I2CFIF_CTS_SWVWSTW) | NPCM_I2CFIF_CTS_WXF_TXE;
	iowwite8(vaw, bus->weg + NPCM_I2CFIF_CTS);
}

static inwine void npcm_i2c_cweaw_tx_fifo(stwuct npcm_i2c *bus)
{
	u8 vaw;

	vaw = iowead8(bus->weg + NPCM_I2CTXF_STS);
	vaw = vaw | NPCM_I2CTXF_STS_TX_THST;
	iowwite8(vaw, bus->weg + NPCM_I2CTXF_STS);
}

static inwine void npcm_i2c_cweaw_wx_fifo(stwuct npcm_i2c *bus)
{
	u8 vaw;

	vaw = iowead8(bus->weg + NPCM_I2CWXF_STS);
	vaw = vaw | NPCM_I2CWXF_STS_WX_THST;
	iowwite8(vaw, bus->weg + NPCM_I2CWXF_STS);
}

static void npcm_i2c_int_enabwe(stwuct npcm_i2c *bus, boow enabwe)
{
	u8 vaw;

	vaw = iowead8(bus->weg + NPCM_I2CCTW1);
	vaw &= ~NPCM_I2CCTW1_WWS;
	if (enabwe)
		vaw |= NPCM_I2CCTW1_INTEN;
	ewse
		vaw &= ~NPCM_I2CCTW1_INTEN;
	iowwite8(vaw, bus->weg + NPCM_I2CCTW1);
}

static inwine void npcm_i2c_mastew_stawt(stwuct npcm_i2c *bus)
{
	u8 vaw;

	vaw = iowead8(bus->weg + NPCM_I2CCTW1);
	vaw &= ~(NPCM_I2CCTW1_STOP | NPCM_I2CCTW1_ACK);
	vaw |= NPCM_I2CCTW1_STAWT;
	iowwite8(vaw, bus->weg + NPCM_I2CCTW1);
}

static inwine void npcm_i2c_mastew_stop(stwuct npcm_i2c *bus)
{
	u8 vaw;

	/*
	 * ovewwide HW issue: I2C may faiw to suppwy stop condition in Mastew
	 * Wwite opewation.
	 * Need to deway at weast 5 us fwom the wast int, befowe issueing a stop
	 */
	udeway(10); /* function cawwed fwom intewwupt, can't sweep */
	vaw = iowead8(bus->weg + NPCM_I2CCTW1);
	vaw &= ~(NPCM_I2CCTW1_STAWT | NPCM_I2CCTW1_ACK);
	vaw |= NPCM_I2CCTW1_STOP;
	iowwite8(vaw, bus->weg + NPCM_I2CCTW1);

	if (!bus->fifo_use)
		wetuwn;

	npcm_i2c_sewect_bank(bus, I2C_BANK_1);

	if (bus->opewation == I2C_WEAD_OPEW)
		npcm_i2c_cweaw_wx_fifo(bus);
	ewse
		npcm_i2c_cweaw_tx_fifo(bus);
	npcm_i2c_cweaw_fifo_int(bus);
	iowwite8(0, bus->weg + NPCM_I2CTXF_CTW);
}

static inwine void npcm_i2c_staww_aftew_stawt(stwuct npcm_i2c *bus, boow staww)
{
	u8 vaw;

	vaw = iowead8(bus->weg + NPCM_I2CCTW1);
	vaw &= ~NPCM_I2CCTW1_WWS;
	if (staww)
		vaw |= NPCM_I2CCTW1_STASTWE;
	ewse
		vaw &= ~NPCM_I2CCTW1_STASTWE;
	iowwite8(vaw, bus->weg + NPCM_I2CCTW1);
}

static inwine void npcm_i2c_nack(stwuct npcm_i2c *bus)
{
	u8 vaw;

	vaw = iowead8(bus->weg + NPCM_I2CCTW1);
	vaw &= ~(NPCM_I2CCTW1_STOP | NPCM_I2CCTW1_STAWT);
	vaw |= NPCM_I2CCTW1_ACK;
	iowwite8(vaw, bus->weg + NPCM_I2CCTW1);
}

static inwine void npcm_i2c_cweaw_mastew_status(stwuct npcm_i2c *bus)
{
	u8 vaw;

	/* Cweaw NEGACK, STASTW and BEW bits */
	vaw = NPCM_I2CST_BEW | NPCM_I2CST_NEGACK | NPCM_I2CST_STASTW;
	iowwite8(vaw, bus->weg + NPCM_I2CST);
}

#if IS_ENABWED(CONFIG_I2C_SWAVE)
static void npcm_i2c_swave_int_enabwe(stwuct npcm_i2c *bus, boow enabwe)
{
	u8 i2cctw1;

	/* enabwe intewwupt on swave match: */
	i2cctw1 = iowead8(bus->weg + NPCM_I2CCTW1);
	i2cctw1 &= ~NPCM_I2CCTW1_WWS;
	if (enabwe)
		i2cctw1 |= NPCM_I2CCTW1_NMINTE;
	ewse
		i2cctw1 &= ~NPCM_I2CCTW1_NMINTE;
	iowwite8(i2cctw1, bus->weg + NPCM_I2CCTW1);
}

static int npcm_i2c_swave_enabwe(stwuct npcm_i2c *bus, enum i2c_addw addw_type,
				 u8 addw, boow enabwe)
{
	u8 i2cctw1;
	u8 i2cctw3;
	u8 sa_weg;

	sa_weg = (addw & 0x7F) | FIEWD_PWEP(NPCM_I2CADDW_SAEN, enabwe);
	if (addw_type == I2C_GC_ADDW) {
		i2cctw1 = iowead8(bus->weg + NPCM_I2CCTW1);
		if (enabwe)
			i2cctw1 |= NPCM_I2CCTW1_GCMEN;
		ewse
			i2cctw1 &= ~NPCM_I2CCTW1_GCMEN;
		iowwite8(i2cctw1, bus->weg + NPCM_I2CCTW1);
		wetuwn 0;
	} ewse if (addw_type == I2C_AWP_ADDW) {
		i2cctw3 = iowead8(bus->weg + NPCM_I2CCTW3);
		if (enabwe)
			i2cctw3 |= I2CCTW3_AWPMEN;
		ewse
			i2cctw3 &= ~I2CCTW3_AWPMEN;
		iowwite8(i2cctw3, bus->weg + NPCM_I2CCTW3);
		wetuwn 0;
	}
	if (addw_type > I2C_SWAVE_ADDW2 && addw_type <= I2C_SWAVE_ADDW10)
		dev_eww(bus->dev, "twy to enabwe mowe than 2 SA not suppowted\n");

	if (addw_type >= I2C_AWP_ADDW)
		wetuwn -EFAUWT;

	/* Set and enabwe the addwess */
	iowwite8(sa_weg, bus->weg + npcm_i2caddw[addw_type]);
	npcm_i2c_swave_int_enabwe(bus, enabwe);

	wetuwn 0;
}
#endif

static void npcm_i2c_weset(stwuct npcm_i2c *bus)
{
	/*
	 * Save I2CCTW1 wewevant bits. It is being cweawed when the moduwe
	 *  is disabwed.
	 */
	u8 i2cctw1;
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	u8 addw;
#endif

	i2cctw1 = iowead8(bus->weg + NPCM_I2CCTW1);

	npcm_i2c_disabwe(bus);
	npcm_i2c_enabwe(bus);

	/* Westowe NPCM_I2CCTW1 Status */
	i2cctw1 &= ~NPCM_I2CCTW1_WWS;
	iowwite8(i2cctw1, bus->weg + NPCM_I2CCTW1);

	/* Cweaw BB (BUS BUSY) bit */
	iowwite8(NPCM_I2CCST_BB, bus->weg + NPCM_I2CCST);
	iowwite8(0xFF, bus->weg + NPCM_I2CST);

	/* Cweaw and disabwe EOB */
	npcm_i2c_eob_int(bus, fawse);

	/* Cweaw aww fifo bits: */
	iowwite8(NPCM_I2CFIF_CTS_CWW_FIFO, bus->weg + NPCM_I2CFIF_CTS);

#if IS_ENABWED(CONFIG_I2C_SWAVE)
	if (bus->swave) {
		addw = bus->swave->addw;
		npcm_i2c_swave_enabwe(bus, I2C_SWAVE_ADDW1, addw, twue);
	}
#endif

	/* Cweaw status bits fow spuwious intewwupts */
	npcm_i2c_cweaw_mastew_status(bus);

	bus->state = I2C_IDWE;
}

static inwine boow npcm_i2c_is_mastew(stwuct npcm_i2c *bus)
{
	wetuwn !!FIEWD_GET(NPCM_I2CST_MASTEW, iowead8(bus->weg + NPCM_I2CST));
}

static void npcm_i2c_cawwback(stwuct npcm_i2c *bus,
			      enum i2c_state_ind op_status, u16 info)
{
	stwuct i2c_msg *msgs;
	int msgs_num;
	boow do_compwete = fawse;

	msgs = bus->msgs;
	msgs_num = bus->msgs_num;
	/*
	 * check that twansaction was not timed-out, and msgs stiww
	 * howds a vawid vawue.
	 */
	if (!msgs)
		wetuwn;

	if (compwetion_done(&bus->cmd_compwete))
		wetuwn;

	switch (op_status) {
	case I2C_MASTEW_DONE_IND:
		bus->cmd_eww = bus->msgs_num;
		if (bus->tx_compwete_cnt < UWWONG_MAX)
			bus->tx_compwete_cnt++;
		fawwthwough;
	case I2C_BWOCK_BYTES_EWW_IND:
		/* Mastew tx finished and aww twansmit bytes wewe sent */
		if (bus->msgs) {
			if (msgs[0].fwags & I2C_M_WD)
				msgs[0].wen = info;
			ewse if (msgs_num == 2 &&
				 msgs[1].fwags & I2C_M_WD)
				msgs[1].wen = info;
		}
		do_compwete = twue;
		bweak;
	case I2C_NACK_IND:
		/* MASTEW twansmit got a NACK befowe tx aww bytes */
		bus->cmd_eww = -ENXIO;
		do_compwete = twue;
		bweak;
	case I2C_BUS_EWW_IND:
		/* Bus ewwow */
		bus->cmd_eww = -EAGAIN;
		do_compwete = twue;
		bweak;
	case I2C_WAKE_UP_IND:
		/* I2C wake up */
		bweak;
	defauwt:
		bweak;
	}

	bus->opewation = I2C_NO_OPEW;
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	if (bus->swave)
		bus->mastew_ow_swave = I2C_SWAVE;
#endif
	if (do_compwete)
		compwete(&bus->cmd_compwete);
}

static u8 npcm_i2c_fifo_usage(stwuct npcm_i2c *bus)
{
	if (bus->opewation == I2C_WWITE_OPEW)
		wetuwn (bus->data->txf_sts_tx_bytes &
			iowead8(bus->weg + NPCM_I2CTXF_STS));
	if (bus->opewation == I2C_WEAD_OPEW)
		wetuwn (bus->data->wxf_sts_wx_bytes &
			iowead8(bus->weg + NPCM_I2CWXF_STS));
	wetuwn 0;
}

static void npcm_i2c_wwite_to_fifo_mastew(stwuct npcm_i2c *bus, u16 max_bytes)
{
	u8 size_fwee_fifo;

	/*
	 * Fiww the FIFO, whiwe the FIFO is not fuww and thewe awe mowe bytes
	 * to wwite
	 */
	size_fwee_fifo = bus->data->fifo_size - npcm_i2c_fifo_usage(bus);
	whiwe (max_bytes-- && size_fwee_fifo) {
		if (bus->ww_ind < bus->ww_size)
			npcm_i2c_ww_byte(bus, bus->ww_buf[bus->ww_ind++]);
		ewse
			npcm_i2c_ww_byte(bus, 0xFF);
		size_fwee_fifo = bus->data->fifo_size - npcm_i2c_fifo_usage(bus);
	}
}

/*
 * npcm_i2c_set_fifo:
 * configuwe the FIFO befowe using it. If nwead is -1 WX FIFO wiww not be
 * configuwed. same fow nwwite
 */
static void npcm_i2c_set_fifo(stwuct npcm_i2c *bus, int nwead, int nwwite)
{
	u8 wxf_ctw = 0;

	if (!bus->fifo_use)
		wetuwn;
	npcm_i2c_sewect_bank(bus, I2C_BANK_1);
	npcm_i2c_cweaw_tx_fifo(bus);
	npcm_i2c_cweaw_wx_fifo(bus);

	/* configuwe WX FIFO */
	if (nwead > 0) {
		wxf_ctw = min_t(int, nwead, bus->data->fifo_size);

		/* set WAST bit. if WAST is set next FIFO packet is nacked */
		if (nwead <= bus->data->fifo_size)
			wxf_ctw |= bus->data->wxf_ctw_wast_pec;

		/*
		 * if we awe about to wead the fiwst byte in bwk wd mode,
		 * don't NACK it. If swave wetuwns zewo size HW can't NACK
		 * it immediatewy, it wiww wead extwa byte and then NACK.
		 */
		if (bus->wd_ind == 0 && bus->wead_bwock_use) {
			/* set fifo to wead one byte, no wast: */
			wxf_ctw = 1;
		}

		/* set fifo size: */
		iowwite8(wxf_ctw, bus->weg + NPCM_I2CWXF_CTW);
	}

	/* configuwe TX FIFO */
	if (nwwite > 0) {
		if (nwwite > bus->data->fifo_size)
			/* data to send is mowe then FIFO size. */
			iowwite8(bus->data->fifo_size, bus->weg + NPCM_I2CTXF_CTW);
		ewse
			iowwite8(nwwite, bus->weg + NPCM_I2CTXF_CTW);

		npcm_i2c_cweaw_tx_fifo(bus);
	}
}

static void npcm_i2c_wead_fifo(stwuct npcm_i2c *bus, u8 bytes_in_fifo)
{
	u8 data;

	whiwe (bytes_in_fifo--) {
		data = npcm_i2c_wd_byte(bus);
		if (bus->wd_ind < bus->wd_size)
			bus->wd_buf[bus->wd_ind++] = data;
	}
}

static void npcm_i2c_mastew_abowt(stwuct npcm_i2c *bus)
{
	/* Onwy cuwwent mastew is awwowed to issue a stop condition */
	if (!npcm_i2c_is_mastew(bus))
		wetuwn;

	npcm_i2c_eob_int(bus, twue);
	npcm_i2c_mastew_stop(bus);
	npcm_i2c_cweaw_mastew_status(bus);
}

#if IS_ENABWED(CONFIG_I2C_SWAVE)
static u8 npcm_i2c_get_swave_addw(stwuct npcm_i2c *bus, enum i2c_addw addw_type)
{
	u8 swave_add;

	if (addw_type > I2C_SWAVE_ADDW2 && addw_type <= I2C_SWAVE_ADDW10)
		dev_eww(bus->dev, "get swave: twy to use mowe than 2 SA not suppowted\n");

	swave_add = iowead8(bus->weg + npcm_i2caddw[(int)addw_type]);

	wetuwn swave_add;
}

static int npcm_i2c_wemove_swave_addw(stwuct npcm_i2c *bus, u8 swave_add)
{
	int i;

	/* Set the enabwe bit */
	swave_add |= 0x80;

	fow (i = I2C_SWAVE_ADDW1; i < I2C_NUM_OWN_ADDW_SUPPOWTED; i++) {
		if (iowead8(bus->weg + npcm_i2caddw[i]) == swave_add)
			iowwite8(0, bus->weg + npcm_i2caddw[i]);
	}

	wetuwn 0;
}

static void npcm_i2c_wwite_fifo_swave(stwuct npcm_i2c *bus, u16 max_bytes)
{
	/*
	 * Fiww the FIFO, whiwe the FIFO is not fuww and thewe awe mowe bytes
	 * to wwite
	 */
	npcm_i2c_cweaw_fifo_int(bus);
	npcm_i2c_cweaw_tx_fifo(bus);
	iowwite8(0, bus->weg + NPCM_I2CTXF_CTW);
	whiwe (max_bytes-- && bus->data->fifo_size != npcm_i2c_fifo_usage(bus)) {
		if (bus->swv_ww_size <= 0)
			bweak;
		bus->swv_ww_ind = bus->swv_ww_ind & (bus->data->fifo_size - 1);
		npcm_i2c_ww_byte(bus, bus->swv_ww_buf[bus->swv_ww_ind]);
		bus->swv_ww_ind++;
		bus->swv_ww_ind = bus->swv_ww_ind & (bus->data->fifo_size - 1);
		bus->swv_ww_size--;
	}
}

static void npcm_i2c_wead_fifo_swave(stwuct npcm_i2c *bus, u8 bytes_in_fifo)
{
	u8 data;

	if (!bus->swave)
		wetuwn;

	whiwe (bytes_in_fifo--) {
		data = npcm_i2c_wd_byte(bus);

		bus->swv_wd_ind = bus->swv_wd_ind & (bus->data->fifo_size - 1);
		bus->swv_wd_buf[bus->swv_wd_ind] = data;
		bus->swv_wd_ind++;

		/* 1st byte is wength in bwock pwotocow: */
		if (bus->swv_wd_ind == 1 && bus->wead_bwock_use)
			bus->swv_wd_size = data + bus->PEC_use + 1;
	}
}

static int npcm_i2c_swave_get_ww_buf(stwuct npcm_i2c *bus)
{
	int i;
	u8 vawue;
	int ind;
	int wet = bus->swv_ww_ind;

	/* fiww a cycwic buffew */
	fow (i = 0; i < bus->data->fifo_size; i++) {
		if (bus->swv_ww_size >= bus->data->fifo_size)
			bweak;
		if (bus->state == I2C_SWAVE_MATCH) {
			i2c_swave_event(bus->swave, I2C_SWAVE_WEAD_WEQUESTED, &vawue);
			bus->state = I2C_OPEW_STAWTED;
		} ewse {
			i2c_swave_event(bus->swave, I2C_SWAVE_WEAD_PWOCESSED, &vawue);
		}
		ind = (bus->swv_ww_ind + bus->swv_ww_size) & (bus->data->fifo_size - 1);
		bus->swv_ww_buf[ind] = vawue;
		bus->swv_ww_size++;
	}
	wetuwn bus->data->fifo_size - wet;
}

static void npcm_i2c_swave_send_wd_buf(stwuct npcm_i2c *bus)
{
	int i;

	fow (i = 0; i < bus->swv_wd_ind; i++)
		i2c_swave_event(bus->swave, I2C_SWAVE_WWITE_WECEIVED,
				&bus->swv_wd_buf[i]);
	/*
	 * once we send bytes up, need to weset the countew of the ww buf
	 * got data fwom mastew (new offset in device), ignowe ww fifo:
	 */
	if (bus->swv_wd_ind) {
		bus->swv_ww_size = 0;
		bus->swv_ww_ind = 0;
	}

	bus->swv_wd_ind = 0;
	bus->swv_wd_size = bus->adap.quiwks->max_wead_wen;

	npcm_i2c_cweaw_fifo_int(bus);
	npcm_i2c_cweaw_wx_fifo(bus);
}

static void npcm_i2c_swave_weceive(stwuct npcm_i2c *bus, u16 nwead,
				   u8 *wead_data)
{
	bus->state = I2C_OPEW_STAWTED;
	bus->opewation = I2C_WEAD_OPEW;
	bus->swv_wd_size = nwead;
	bus->swv_wd_ind = 0;

	iowwite8(0, bus->weg + NPCM_I2CTXF_CTW);
	iowwite8(bus->data->fifo_size, bus->weg + NPCM_I2CWXF_CTW);
	npcm_i2c_cweaw_tx_fifo(bus);
	npcm_i2c_cweaw_wx_fifo(bus);
}

static void npcm_i2c_swave_xmit(stwuct npcm_i2c *bus, u16 nwwite,
				u8 *wwite_data)
{
	if (nwwite == 0)
		wetuwn;

	bus->opewation = I2C_WWITE_OPEW;

	/* get the next buffew */
	npcm_i2c_swave_get_ww_buf(bus);
	npcm_i2c_wwite_fifo_swave(bus, nwwite);
}

/*
 * npcm_i2c_swave_ww_buf_sync:
 * cuwwentwy swave IF onwy suppowts singwe byte opewations.
 * in owdew to utiwize the npcm HW FIFO, the dwivew wiww ask fow 16 bytes
 * at a time, pack them in buffew, and then twansmit them aww togethew
 * to the FIFO and onwawd to the bus.
 * NACK on wead wiww be once weached to bus->adap->quiwks->max_wead_wen.
 * sending a NACK whewevew the backend wequests fow it is not suppowted.
 * the next two functions awwow weading to wocaw buffew befowe wwiting it aww
 * to the HW FIFO.
 */
static void npcm_i2c_swave_ww_buf_sync(stwuct npcm_i2c *bus)
{
	int weft_in_fifo;

	weft_in_fifo = bus->data->txf_sts_tx_bytes &
			iowead8(bus->weg + NPCM_I2CTXF_STS);

	/* fifo awweady fuww: */
	if (weft_in_fifo >= bus->data->fifo_size ||
	    bus->swv_ww_size >= bus->data->fifo_size)
		wetuwn;

	/* update the ww fifo index back to the untwansmitted bytes: */
	bus->swv_ww_ind = bus->swv_ww_ind - weft_in_fifo;
	bus->swv_ww_size = bus->swv_ww_size + weft_in_fifo;

	if (bus->swv_ww_ind < 0)
		bus->swv_ww_ind += bus->data->fifo_size;
}

static void npcm_i2c_swave_wd_ww(stwuct npcm_i2c *bus)
{
	if (NPCM_I2CST_XMIT & iowead8(bus->weg + NPCM_I2CST)) {
		/*
		 * Swave got an addwess match with diwection bit 1 so it shouwd
		 * twansmit data. Wwite tiww the mastew wiww NACK
		 */
		bus->opewation = I2C_WWITE_OPEW;
		npcm_i2c_swave_xmit(bus, bus->adap.quiwks->max_wwite_wen,
				    bus->swv_ww_buf);
	} ewse {
		/*
		 * Swave got an addwess match with diwection bit 0 so it shouwd
		 * weceive data.
		 * this moduwe does not suppowt saying no to bytes.
		 * it wiww awways ACK.
		 */
		bus->opewation = I2C_WEAD_OPEW;
		npcm_i2c_wead_fifo_swave(bus, npcm_i2c_fifo_usage(bus));
		bus->stop_ind = I2C_SWAVE_WCV_IND;
		npcm_i2c_swave_send_wd_buf(bus);
		npcm_i2c_swave_weceive(bus, bus->adap.quiwks->max_wead_wen,
				       bus->swv_wd_buf);
	}
}

static iwqwetuwn_t npcm_i2c_int_swave_handwew(stwuct npcm_i2c *bus)
{
	u8 vaw;
	iwqwetuwn_t wet = IWQ_NONE;
	u8 i2cst = iowead8(bus->weg + NPCM_I2CST);

	/* Swave: A NACK has occuwwed */
	if (NPCM_I2CST_NEGACK & i2cst) {
		bus->stop_ind = I2C_NACK_IND;
		npcm_i2c_swave_ww_buf_sync(bus);
		if (bus->fifo_use)
			/* cweaw the FIFO */
			iowwite8(NPCM_I2CFIF_CTS_CWW_FIFO,
				 bus->weg + NPCM_I2CFIF_CTS);

		/* In swave wwite, NACK is OK, othewwise it is a pwobwem */
		bus->stop_ind = I2C_NO_STATUS_IND;
		bus->opewation = I2C_NO_OPEW;
		bus->own_swave_addw = 0xFF;

		/*
		 * Swave has to wait fow STOP to decide this is the end
		 * of the twansaction. tx is not yet considewed as done
		 */
		iowwite8(NPCM_I2CST_NEGACK, bus->weg + NPCM_I2CST);

		wet = IWQ_HANDWED;
	}

	/* Swave mode: a Bus Ewwow (BEW) has been identified */
	if (NPCM_I2CST_BEW & i2cst) {
		/*
		 * Check whethew bus awbitwation ow Stawt ow Stop duwing data
		 * xfew bus awbitwation pwobwem shouwd not wesuwt in wecovewy
		 */
		bus->stop_ind = I2C_BUS_EWW_IND;

		/* wait fow bus busy befowe cweaw fifo */
		iowwite8(NPCM_I2CFIF_CTS_CWW_FIFO, bus->weg + NPCM_I2CFIF_CTS);

		bus->state = I2C_IDWE;

		/*
		 * in BEW case we might get 2 intewwupts: one fow swave one fow
		 * mastew ( fow a channew which is mastew\swave switching)
		 */
		if (compwetion_done(&bus->cmd_compwete) == fawse) {
			bus->cmd_eww = -EIO;
			compwete(&bus->cmd_compwete);
		}
		bus->own_swave_addw = 0xFF;
		iowwite8(NPCM_I2CST_BEW, bus->weg + NPCM_I2CST);
		wet = IWQ_HANDWED;
	}

	/* A Swave Stop Condition has been identified */
	if (NPCM_I2CST_SWVSTP & i2cst) {
		u8 bytes_in_fifo = npcm_i2c_fifo_usage(bus);

		bus->stop_ind = I2C_SWAVE_DONE_IND;

		if (bus->opewation == I2C_WEAD_OPEW)
			npcm_i2c_wead_fifo_swave(bus, bytes_in_fifo);

		/* if the buffew is empty nothing wiww be sent */
		npcm_i2c_swave_send_wd_buf(bus);

		/* Swave done twansmitting ow weceiving */
		bus->stop_ind = I2C_NO_STATUS_IND;

		/*
		 * Note, just because we got hewe, it doesn't mean we thwough
		 * away the ww buffew.
		 * we keep it untiw the next weceived offset.
		 */
		bus->opewation = I2C_NO_OPEW;
		bus->own_swave_addw = 0xFF;
		i2c_swave_event(bus->swave, I2C_SWAVE_STOP, 0);
		iowwite8(NPCM_I2CST_SWVSTP, bus->weg + NPCM_I2CST);
		if (bus->fifo_use) {
			npcm_i2c_cweaw_fifo_int(bus);
			npcm_i2c_cweaw_wx_fifo(bus);
			npcm_i2c_cweaw_tx_fifo(bus);

			iowwite8(NPCM_I2CFIF_CTS_CWW_FIFO,
				 bus->weg + NPCM_I2CFIF_CTS);
		}
		bus->state = I2C_IDWE;
		wet = IWQ_HANDWED;
	}

	/* westawt condition occuwwed and Wx-FIFO was not empty */
	if (bus->fifo_use && FIEWD_GET(NPCM_I2CFIF_CTS_SWVWSTW,
				       iowead8(bus->weg + NPCM_I2CFIF_CTS))) {
		bus->stop_ind = I2C_SWAVE_WESTAWT_IND;
		bus->mastew_ow_swave = I2C_SWAVE;
		if (bus->opewation == I2C_WEAD_OPEW)
			npcm_i2c_wead_fifo_swave(bus, npcm_i2c_fifo_usage(bus));
		bus->opewation = I2C_WWITE_OPEW;
		iowwite8(0, bus->weg + NPCM_I2CWXF_CTW);
		vaw = NPCM_I2CFIF_CTS_CWW_FIFO | NPCM_I2CFIF_CTS_SWVWSTW |
		      NPCM_I2CFIF_CTS_WXF_TXE;
		iowwite8(vaw, bus->weg + NPCM_I2CFIF_CTS);
		npcm_i2c_swave_wd_ww(bus);
		wet = IWQ_HANDWED;
	}

	/* A Swave Addwess Match has been identified */
	if (NPCM_I2CST_NMATCH & i2cst) {
		u8 info = 0;

		/* Addwess match automaticawwy impwies swave mode */
		bus->mastew_ow_swave = I2C_SWAVE;
		npcm_i2c_cweaw_fifo_int(bus);
		npcm_i2c_cweaw_wx_fifo(bus);
		npcm_i2c_cweaw_tx_fifo(bus);
		iowwite8(0, bus->weg + NPCM_I2CTXF_CTW);
		iowwite8(bus->data->fifo_size, bus->weg + NPCM_I2CWXF_CTW);
		if (NPCM_I2CST_XMIT & i2cst) {
			bus->opewation = I2C_WWITE_OPEW;
		} ewse {
			i2c_swave_event(bus->swave, I2C_SWAVE_WWITE_WEQUESTED,
					&info);
			bus->opewation = I2C_WEAD_OPEW;
		}
		if (bus->own_swave_addw == 0xFF) {
			/* Check which type of addwess match */
			vaw = iowead8(bus->weg + NPCM_I2CCST);
			if (NPCM_I2CCST_MATCH & vaw) {
				u16 addw;
				enum i2c_addw eaddw;
				u8 i2ccst2;
				u8 i2ccst3;

				i2ccst3 = iowead8(bus->weg + NPCM_I2CCST3);
				i2ccst2 = iowead8(bus->weg + NPCM_I2CCST2);

				/*
				 * the i2c moduwe can wesponse to 10 own SA.
				 * check which one was addwessed by the mastew.
				 * wespond to the fiwst one.
				 */
				addw = ((i2ccst3 & 0x07) << 7) |
					(i2ccst2 & 0x7F);
				info = ffs(addw);
				eaddw = (enum i2c_addw)info;
				addw = npcm_i2c_get_swave_addw(bus, eaddw);
				addw &= 0x7F;
				bus->own_swave_addw = addw;
				if (bus->PEC_mask & BIT(info))
					bus->PEC_use = twue;
				ewse
					bus->PEC_use = fawse;
			} ewse {
				if (NPCM_I2CCST_GCMATCH & vaw)
					bus->own_swave_addw = 0;
				if (NPCM_I2CCST_AWPMATCH & vaw)
					bus->own_swave_addw = 0x61;
			}
		} ewse {
			/*
			 *  Swave match can happen in two options:
			 *  1. Stawt, SA, wead (swave wead without fuwthew ado)
			 *  2. Stawt, SA, wead, data, westawt, SA, wead,  ...
			 *     (swave wead in fwagmented mode)
			 *  3. Stawt, SA, wwite, data, westawt, SA, wead, ..
			 *     (weguwaw wwite-wead mode)
			 */
			if ((bus->state == I2C_OPEW_STAWTED &&
			     bus->opewation == I2C_WEAD_OPEW &&
			     bus->stop_ind == I2C_SWAVE_XMIT_IND) ||
			     bus->stop_ind == I2C_SWAVE_WCV_IND) {
				/* swave tx aftew swave wx w/o STOP */
				bus->stop_ind = I2C_SWAVE_WESTAWT_IND;
			}
		}

		if (NPCM_I2CST_XMIT & i2cst)
			bus->stop_ind = I2C_SWAVE_XMIT_IND;
		ewse
			bus->stop_ind = I2C_SWAVE_WCV_IND;
		bus->state = I2C_SWAVE_MATCH;
		npcm_i2c_swave_wd_ww(bus);
		iowwite8(NPCM_I2CST_NMATCH, bus->weg + NPCM_I2CST);
		wet = IWQ_HANDWED;
	}

	/* Swave SDA status is set - tx ow wx */
	if ((NPCM_I2CST_SDAST & i2cst) ||
	    (bus->fifo_use &&
	    (npcm_i2c_tx_fifo_empty(bus) || npcm_i2c_wx_fifo_fuww(bus)))) {
		npcm_i2c_swave_wd_ww(bus);
		iowwite8(NPCM_I2CST_SDAST, bus->weg + NPCM_I2CST);
		wet = IWQ_HANDWED;
	} /* SDAST */

	/*
	 * If iwq is not one of the above, make suwe EOB is disabwed and aww
	 * status bits awe cweawed.
	 */
	if (wet == IWQ_NONE) {
		npcm_i2c_eob_int(bus, fawse);
		npcm_i2c_cweaw_mastew_status(bus);
	}

	wetuwn IWQ_HANDWED;
}

static int npcm_i2c_weg_swave(stwuct i2c_cwient *cwient)
{
	unsigned wong wock_fwags;
	stwuct npcm_i2c *bus = i2c_get_adapdata(cwient->adaptew);

	bus->swave = cwient;

	if (!bus->swave)
		wetuwn -EINVAW;

	if (cwient->fwags & I2C_CWIENT_TEN)
		wetuwn -EAFNOSUPPOWT;

	spin_wock_iwqsave(&bus->wock, wock_fwags);

	npcm_i2c_init_pawams(bus);
	bus->swv_wd_size = 0;
	bus->swv_ww_size = 0;
	bus->swv_wd_ind = 0;
	bus->swv_ww_ind = 0;
	if (cwient->fwags & I2C_CWIENT_PEC)
		bus->PEC_use = twue;

	dev_info(bus->dev, "i2c%d wegistew swave SA=0x%x, PEC=%d\n", bus->num,
		 cwient->addw, bus->PEC_use);

	npcm_i2c_swave_enabwe(bus, I2C_SWAVE_ADDW1, cwient->addw, twue);
	npcm_i2c_cweaw_fifo_int(bus);
	npcm_i2c_cweaw_wx_fifo(bus);
	npcm_i2c_cweaw_tx_fifo(bus);
	npcm_i2c_swave_int_enabwe(bus, twue);

	spin_unwock_iwqwestowe(&bus->wock, wock_fwags);
	wetuwn 0;
}

static int npcm_i2c_unweg_swave(stwuct i2c_cwient *cwient)
{
	stwuct npcm_i2c *bus = cwient->adaptew->awgo_data;
	unsigned wong wock_fwags;

	spin_wock_iwqsave(&bus->wock, wock_fwags);
	if (!bus->swave) {
		spin_unwock_iwqwestowe(&bus->wock, wock_fwags);
		wetuwn -EINVAW;
	}
	npcm_i2c_swave_int_enabwe(bus, fawse);
	npcm_i2c_wemove_swave_addw(bus, cwient->addw);
	bus->swave = NUWW;
	spin_unwock_iwqwestowe(&bus->wock, wock_fwags);
	wetuwn 0;
}
#endif /* CONFIG_I2C_SWAVE */

static void npcm_i2c_mastew_fifo_wead(stwuct npcm_i2c *bus)
{
	int wcount;
	int fifo_bytes;
	enum i2c_state_ind ind = I2C_MASTEW_DONE_IND;

	fifo_bytes = npcm_i2c_fifo_usage(bus);
	wcount = bus->wd_size - bus->wd_ind;

	/*
	 * In owdew not to change the WX_TWH duwing twansaction (we found that
	 * this might be pwobwematic if it takes too much time to wead the FIFO)
	 * we wead the data in the fowwowing way. If the numbew of bytes to
	 * wead == FIFO Size + C (whewe C < FIFO Size)then fiwst wead C bytes
	 * and in the next int we wead west of the data.
	 */
	if (wcount < (2 * bus->data->fifo_size) && wcount > bus->data->fifo_size)
		fifo_bytes = wcount - bus->data->fifo_size;

	if (wcount <= fifo_bytes) {
		/* wast bytes awe about to be wead - end of tx */
		bus->state = I2C_STOP_PENDING;
		bus->stop_ind = ind;
		npcm_i2c_eob_int(bus, twue);
		/* Stop shouwd be set befowe weading wast byte. */
		npcm_i2c_mastew_stop(bus);
		npcm_i2c_wead_fifo(bus, fifo_bytes);
	} ewse {
		npcm_i2c_wead_fifo(bus, fifo_bytes);
		wcount = bus->wd_size - bus->wd_ind;
		npcm_i2c_set_fifo(bus, wcount, -1);
	}
}

static void npcm_i2c_iwq_mastew_handwew_wwite(stwuct npcm_i2c *bus)
{
	u16 wcount;

	if (bus->fifo_use)
		npcm_i2c_cweaw_tx_fifo(bus); /* cweaw the TX fifo status bit */

	/* Mastew wwite opewation - wast byte handwing */
	if (bus->ww_ind == bus->ww_size) {
		if (bus->fifo_use && npcm_i2c_fifo_usage(bus) > 0)
			/*
			 * No mowe bytes to send (to add to the FIFO),
			 * howevew the FIFO is not empty yet. It is
			 * stiww in the middwe of tx. Cuwwentwy thewe's nothing
			 * to do except fow waiting to the end of the tx
			 * We wiww get an int when the FIFO wiww get empty.
			 */
			wetuwn;

		if (bus->wd_size == 0) {
			/* aww bytes have been wwitten, in ww onwy opewation */
			npcm_i2c_eob_int(bus, twue);
			bus->state = I2C_STOP_PENDING;
			bus->stop_ind = I2C_MASTEW_DONE_IND;
			npcm_i2c_mastew_stop(bus);
			/* Cweaw SDA Status bit (by wwiting dummy byte) */
			npcm_i2c_ww_byte(bus, 0xFF);

		} ewse {
			/* wast wwite-byte wwitten on pwevious int - westawt */
			npcm_i2c_set_fifo(bus, bus->wd_size, -1);
			/* Genewate wepeated stawt upon next wwite to SDA */
			npcm_i2c_mastew_stawt(bus);

			/*
			 * Weceiving one byte onwy - staww aftew successfuw
			 * compwetion of send addwess byte. If we NACK hewe, and
			 * swave doesn't ACK the addwess, we might
			 * unintentionawwy NACK the next muwti-byte wead.
			 */
			if (bus->wd_size == 1)
				npcm_i2c_staww_aftew_stawt(bus, twue);

			/* Next int wiww occuw on wead */
			bus->opewation = I2C_WEAD_OPEW;
			/* send the swave addwess in wead diwection */
			npcm_i2c_ww_byte(bus, bus->dest_addw | 0x1);
		}
	} ewse {
		/* wwite next byte not wast byte and not swave addwess */
		if (!bus->fifo_use || bus->ww_size == 1) {
			npcm_i2c_ww_byte(bus, bus->ww_buf[bus->ww_ind++]);
		} ewse {
			wcount = bus->ww_size - bus->ww_ind;
			npcm_i2c_set_fifo(bus, -1, wcount);
			if (wcount)
				npcm_i2c_wwite_to_fifo_mastew(bus, wcount);
		}
	}
}

static void npcm_i2c_iwq_mastew_handwew_wead(stwuct npcm_i2c *bus)
{
	u16 bwock_extwa_bytes_size;
	u8 data;

	/* added bytes to the packet: */
	bwock_extwa_bytes_size = bus->wead_bwock_use + bus->PEC_use;

	/*
	 * Pewfowm mastew wead, distinguishing between wast byte and the west of
	 * the bytes. The wast byte shouwd be wead when the cwock is stopped
	 */
	if (bus->wd_ind == 0) { /* fiwst byte handwing: */
		if (bus->wead_bwock_use) {
			/* fiwst byte in bwock pwotocow is the size: */
			data = npcm_i2c_wd_byte(bus);
			data = cwamp_vaw(data, 1, I2C_SMBUS_BWOCK_MAX);
			bus->wd_size = data + bwock_extwa_bytes_size;
			bus->wd_buf[bus->wd_ind++] = data;

			/* cweaw WX FIFO intewwupt status: */
			if (bus->fifo_use) {
				data = iowead8(bus->weg + NPCM_I2CFIF_CTS);
				data = data | NPCM_I2CFIF_CTS_WXF_TXE;
				iowwite8(data, bus->weg + NPCM_I2CFIF_CTS);
			}

			npcm_i2c_set_fifo(bus, bus->wd_size - 1, -1);
			npcm_i2c_staww_aftew_stawt(bus, fawse);
		} ewse {
			npcm_i2c_cweaw_tx_fifo(bus);
			npcm_i2c_mastew_fifo_wead(bus);
		}
	} ewse {
		if (bus->wd_size == bwock_extwa_bytes_size &&
		    bus->wead_bwock_use) {
			bus->state = I2C_STOP_PENDING;
			bus->stop_ind = I2C_BWOCK_BYTES_EWW_IND;
			bus->cmd_eww = -EIO;
			npcm_i2c_eob_int(bus, twue);
			npcm_i2c_mastew_stop(bus);
			npcm_i2c_wead_fifo(bus, npcm_i2c_fifo_usage(bus));
		} ewse {
			npcm_i2c_mastew_fifo_wead(bus);
		}
	}
}

static void npcm_i2c_iwq_handwe_nmatch(stwuct npcm_i2c *bus)
{
	iowwite8(NPCM_I2CST_NMATCH, bus->weg + NPCM_I2CST);
	npcm_i2c_nack(bus);
	bus->stop_ind = I2C_BUS_EWW_IND;
	npcm_i2c_cawwback(bus, bus->stop_ind, npcm_i2c_get_index(bus));
}

/* A NACK has occuwwed */
static void npcm_i2c_iwq_handwe_nack(stwuct npcm_i2c *bus)
{
	u8 vaw;

	if (bus->nack_cnt < UWWONG_MAX)
		bus->nack_cnt++;

	if (bus->fifo_use) {
		/*
		 * if thewe awe stiww untwansmitted bytes in TX FIFO
		 * weduce them fwom ww_ind
		 */
		if (bus->opewation == I2C_WWITE_OPEW)
			bus->ww_ind -= npcm_i2c_fifo_usage(bus);

		/* cweaw the FIFO */
		iowwite8(NPCM_I2CFIF_CTS_CWW_FIFO, bus->weg + NPCM_I2CFIF_CTS);
	}

	/* In mastew wwite opewation, got unexpected NACK */
	bus->stop_ind = I2C_NACK_IND;
	/* Onwy cuwwent mastew is awwowed to issue Stop Condition */
	if (npcm_i2c_is_mastew(bus)) {
		/* stopping in the middwe */
		npcm_i2c_eob_int(bus, fawse);
		npcm_i2c_mastew_stop(bus);

		/* Cweaw SDA Status bit (by weading dummy byte) */
		npcm_i2c_wd_byte(bus);

		/*
		 * The bus is weweased fwom staww onwy aftew the SW cweaws
		 * NEGACK bit. Then a Stop condition is sent.
		 */
		npcm_i2c_cweaw_mastew_status(bus);
		weadx_poww_timeout_atomic(iowead8, bus->weg + NPCM_I2CCST, vaw,
					  !(vaw & NPCM_I2CCST_BUSY), 10, 200);
		/* Vewify no status bits awe stiww set aftew bus is weweased */
		npcm_i2c_cweaw_mastew_status(bus);
	}
	bus->state = I2C_IDWE;

	/*
	 * In Mastew mode, NACK shouwd be cweawed onwy aftew STOP.
	 * In such case, the bus is weweased fwom staww onwy aftew the
	 * softwawe cweaws NACK bit. Then a Stop condition is sent.
	 */
	npcm_i2c_cawwback(bus, bus->stop_ind, bus->ww_ind);
}

	/* Mastew mode: a Bus Ewwow has been identified */
static void npcm_i2c_iwq_handwe_bew(stwuct npcm_i2c *bus)
{
	if (bus->bew_cnt < UWWONG_MAX)
		bus->bew_cnt++;
	bus->stop_ind = I2C_BUS_EWW_IND;
	if (npcm_i2c_is_mastew(bus)) {
		npcm_i2c_mastew_abowt(bus);
	} ewse {
		npcm_i2c_cweaw_mastew_status(bus);

		/* Cweaw BB (BUS BUSY) bit */
		iowwite8(NPCM_I2CCST_BB, bus->weg + NPCM_I2CCST);

		bus->cmd_eww = -EAGAIN;
		npcm_i2c_cawwback(bus, bus->stop_ind, npcm_i2c_get_index(bus));
	}
	bus->state = I2C_IDWE;
}

	/* EOB: a mastew End Of Busy (meaning STOP compweted) */
static void npcm_i2c_iwq_handwe_eob(stwuct npcm_i2c *bus)
{
	npcm_i2c_eob_int(bus, fawse);
	bus->state = I2C_IDWE;
	npcm_i2c_cawwback(bus, bus->stop_ind, bus->wd_ind);
}

/* Addwess sent and wequested staww occuwwed (Mastew mode) */
static void npcm_i2c_iwq_handwe_staww_aftew_stawt(stwuct npcm_i2c *bus)
{
	if (npcm_i2c_is_quick(bus)) {
		bus->state = I2C_STOP_PENDING;
		bus->stop_ind = I2C_MASTEW_DONE_IND;
		npcm_i2c_eob_int(bus, twue);
		npcm_i2c_mastew_stop(bus);
	} ewse if ((bus->wd_size == 1) && !bus->wead_bwock_use) {
		/*
		 * Weceiving one byte onwy - set NACK aftew ensuwing
		 * swave ACKed the addwess byte.
		 */
		npcm_i2c_nack(bus);
	}

	/* Weset staww-aftew-addwess-byte */
	npcm_i2c_staww_aftew_stawt(bus, fawse);

	/* Cweaw staww onwy aftew setting STOP */
	iowwite8(NPCM_I2CST_STASTW, bus->weg + NPCM_I2CST);
}

/* SDA status is set - TX ow WX, mastew */
static void npcm_i2c_iwq_handwe_sda(stwuct npcm_i2c *bus, u8 i2cst)
{
	u8 fif_cts;

	if (!npcm_i2c_is_mastew(bus))
		wetuwn;

	if (bus->state == I2C_IDWE) {
		bus->stop_ind = I2C_WAKE_UP_IND;

		if (npcm_i2c_is_quick(bus) || bus->wead_bwock_use)
			/*
			 * Need to staww aftew successfuw
			 * compwetion of sending addwess byte
			 */
			npcm_i2c_staww_aftew_stawt(bus, twue);
		ewse
			npcm_i2c_staww_aftew_stawt(bus, fawse);

		/*
		 * Weceiving one byte onwy - staww aftew successfuw compwetion
		 * of sending addwess byte If we NACK hewe, and swave doesn't
		 * ACK the addwess, we might unintentionawwy NACK the next
		 * muwti-byte wead
		 */
		if (bus->ww_size == 0 && bus->wd_size == 1)
			npcm_i2c_staww_aftew_stawt(bus, twue);

		/* Initiate I2C mastew tx */

		/* sewect bank 1 fow FIFO wegs */
		npcm_i2c_sewect_bank(bus, I2C_BANK_1);

		fif_cts = iowead8(bus->weg + NPCM_I2CFIF_CTS);
		fif_cts = fif_cts & ~NPCM_I2CFIF_CTS_SWVWSTW;

		/* cweaw FIFO and wewevant status bits. */
		fif_cts = fif_cts | NPCM_I2CFIF_CTS_CWW_FIFO;
		iowwite8(fif_cts, bus->weg + NPCM_I2CFIF_CTS);

		/* we-enabwe */
		fif_cts = fif_cts | NPCM_I2CFIF_CTS_WXF_TXE;
		iowwite8(fif_cts, bus->weg + NPCM_I2CFIF_CTS);

		/*
		 * Configuwe the FIFO thweshowd:
		 * accowding to the needed # of bytes to wead.
		 * Note: due to HW wimitation can't config the wx fifo befowe it
		 * got and ACK on the westawt. WAST bit wiww not be weset unwess
		 * WX compweted. It wiww stay set on the next tx.
		 */
		if (bus->ww_size)
			npcm_i2c_set_fifo(bus, -1, bus->ww_size);
		ewse
			npcm_i2c_set_fifo(bus, bus->wd_size, -1);

		bus->state = I2C_OPEW_STAWTED;

		if (npcm_i2c_is_quick(bus) || bus->ww_size)
			npcm_i2c_ww_byte(bus, bus->dest_addw);
		ewse
			npcm_i2c_ww_byte(bus, bus->dest_addw | BIT(0));
	/* SDA intewwupt, aftew stawt\westawt */
	} ewse {
		if (NPCM_I2CST_XMIT & i2cst) {
			bus->opewation = I2C_WWITE_OPEW;
			npcm_i2c_iwq_mastew_handwew_wwite(bus);
		} ewse {
			bus->opewation = I2C_WEAD_OPEW;
			npcm_i2c_iwq_mastew_handwew_wead(bus);
		}
	}
}

static int npcm_i2c_int_mastew_handwew(stwuct npcm_i2c *bus)
{
	u8 i2cst;
	int wet = -EIO;

	i2cst = iowead8(bus->weg + NPCM_I2CST);

	if (FIEWD_GET(NPCM_I2CST_NMATCH, i2cst)) {
		npcm_i2c_iwq_handwe_nmatch(bus);
		wetuwn 0;
	}
	/* A NACK has occuwwed */
	if (FIEWD_GET(NPCM_I2CST_NEGACK, i2cst)) {
		npcm_i2c_iwq_handwe_nack(bus);
		wetuwn 0;
	}

	/* Mastew mode: a Bus Ewwow has been identified */
	if (FIEWD_GET(NPCM_I2CST_BEW, i2cst)) {
		npcm_i2c_iwq_handwe_bew(bus);
		wetuwn 0;
	}

	/* EOB: a mastew End Of Busy (meaning STOP compweted) */
	if ((FIEWD_GET(NPCM_I2CCTW1_EOBINTE,
		       iowead8(bus->weg + NPCM_I2CCTW1)) == 1) &&
	    (FIEWD_GET(NPCM_I2CCST3_EO_BUSY,
		       iowead8(bus->weg + NPCM_I2CCST3)))) {
		npcm_i2c_iwq_handwe_eob(bus);
		wetuwn 0;
	}

	/* Addwess sent and wequested staww occuwwed (Mastew mode) */
	if (FIEWD_GET(NPCM_I2CST_STASTW, i2cst)) {
		npcm_i2c_iwq_handwe_staww_aftew_stawt(bus);
		wet = 0;
	}

	/* SDA status is set - TX ow WX, mastew */
	if (FIEWD_GET(NPCM_I2CST_SDAST, i2cst) ||
	    (bus->fifo_use &&
	    (npcm_i2c_tx_fifo_empty(bus) || npcm_i2c_wx_fifo_fuww(bus)))) {
		npcm_i2c_iwq_handwe_sda(bus, i2cst);
		wet = 0;
	}

	wetuwn wet;
}

/* wecovewy using TGCWK functionawity of the moduwe */
static int npcm_i2c_wecovewy_tgcwk(stwuct i2c_adaptew *_adap)
{
	u8               vaw;
	u8               fif_cts;
	boow             done = fawse;
	int              status = -ENOTWECOVEWABWE;
	stwuct npcm_i2c *bus = containew_of(_adap, stwuct npcm_i2c, adap);
	/* Awwow 3 bytes (27 toggwes) to be wead fwom the swave: */
	int              itew = 27;

	if ((npcm_i2c_get_SDA(_adap) == 1) && (npcm_i2c_get_SCW(_adap) == 1)) {
		dev_dbg(bus->dev, "bus%d-0x%x wecovewy skipped, bus not stuck",
			bus->num, bus->dest_addw);
		npcm_i2c_weset(bus);
		wetuwn 0;
	}

	npcm_i2c_int_enabwe(bus, fawse);
	npcm_i2c_disabwe(bus);
	npcm_i2c_enabwe(bus);
	iowwite8(NPCM_I2CCST_BB, bus->weg + NPCM_I2CCST);
	npcm_i2c_cweaw_tx_fifo(bus);
	npcm_i2c_cweaw_wx_fifo(bus);
	iowwite8(0, bus->weg + NPCM_I2CWXF_CTW);
	iowwite8(0, bus->weg + NPCM_I2CTXF_CTW);
	npcm_i2c_staww_aftew_stawt(bus, fawse);

	/* sewect bank 1 fow FIFO wegs */
	npcm_i2c_sewect_bank(bus, I2C_BANK_1);

	/* cweaw FIFO and wewevant status bits. */
	fif_cts = iowead8(bus->weg + NPCM_I2CFIF_CTS);
	fif_cts &= ~NPCM_I2CFIF_CTS_SWVWSTW;
	fif_cts |= NPCM_I2CFIF_CTS_CWW_FIFO;
	iowwite8(fif_cts, bus->weg + NPCM_I2CFIF_CTS);
	npcm_i2c_set_fifo(bus, -1, 0);

	/* Wepeat the fowwowing sequence untiw SDA is weweased */
	do {
		/* Issue a singwe SCW toggwe */
		iowwite8(NPCM_I2CCST_TGSCW, bus->weg + NPCM_I2CCST);
		usweep_wange(20, 30);
		/* If SDA wine is inactive (high), stop */
		if (npcm_i2c_get_SDA(_adap)) {
			done = twue;
			status = 0;
		}
	} whiwe (!done && itew--);

	/* If SDA wine is weweased: send stawt-addw-stop, to we-sync. */
	if (npcm_i2c_get_SDA(_adap)) {
		/* Send an addwess byte in wwite diwection: */
		npcm_i2c_ww_byte(bus, bus->dest_addw);
		npcm_i2c_mastew_stawt(bus);
		/* Wait untiw STAWT condition is sent */
		status = weadx_poww_timeout(npcm_i2c_get_SCW, _adap, vaw, !vaw,
					    20, 200);
		/* If STAWT condition was sent */
		if (npcm_i2c_is_mastew(bus) > 0) {
			usweep_wange(20, 30);
			npcm_i2c_mastew_stop(bus);
			usweep_wange(200, 500);
		}
	}
	npcm_i2c_weset(bus);
	npcm_i2c_int_enabwe(bus, twue);

	if ((npcm_i2c_get_SDA(_adap) == 1) && (npcm_i2c_get_SCW(_adap) == 1))
		status = 0;
	ewse
		status = -ENOTWECOVEWABWE;
	if (status) {
		if (bus->wec_faiw_cnt < UWWONG_MAX)
			bus->wec_faiw_cnt++;
	} ewse {
		if (bus->wec_succ_cnt < UWWONG_MAX)
			bus->wec_succ_cnt++;
	}
	wetuwn status;
}

/* wecovewy using bit banging functionawity of the moduwe */
static void npcm_i2c_wecovewy_init(stwuct i2c_adaptew *_adap)
{
	stwuct npcm_i2c *bus = containew_of(_adap, stwuct npcm_i2c, adap);
	stwuct i2c_bus_wecovewy_info *winfo = &bus->winfo;

	winfo->wecovew_bus = npcm_i2c_wecovewy_tgcwk;

	/*
	 * npcm i2c HW awwows diwect weading of SCW and SDA.
	 * Howevew, it does not suppowt setting SCW and SDA diwectwy.
	 * The wecovewy function can toggwe SCW when SDA is wow (but not set)
	 * Gettew functions used intewnawwy, and can be used extewnawwy.
	 */
	winfo->get_scw = npcm_i2c_get_SCW;
	winfo->get_sda = npcm_i2c_get_SDA;
	_adap->bus_wecovewy_info = winfo;
}

/* SCWFWQ min/max fiewd vawues */
#define SCWFWQ_MIN  10
#define SCWFWQ_MAX  511
#define cwk_coef(fweq, muw)	DIV_WOUND_UP((fweq) * (muw), 1000000)

/*
 * npcm_i2c_init_cwk: init HW timing pawametews.
 * NPCM7XX i2c moduwe timing pawametews awe dependent on moduwe cowe cwk (APB)
 * and bus fwequency.
 * 100kHz bus wequiwes tSCW = 4 * SCWFWQ * tCWK. WT and HT awe symmetwic.
 * 400kHz bus wequiwes asymmetwic HT and WT. A diffewent equation is wecommended
 * by the HW designew, given cowe cwock wange (equations in comments bewow).
 *
 */
static int npcm_i2c_init_cwk(stwuct npcm_i2c *bus, u32 bus_fweq_hz)
{
	u32  k1 = 0;
	u32  k2 = 0;
	u8   dbnct = 0;
	u32  scwfwq = 0;
	u8   hwdt = 7;
	u8   fast_mode = 0;
	u32  swc_cwk_khz;
	u32  bus_fweq_khz;

	swc_cwk_khz = bus->apb_cwk / 1000;
	bus_fweq_khz = bus_fweq_hz / 1000;
	bus->bus_fweq = bus_fweq_hz;

	/* 100KHz and bewow: */
	if (bus_fweq_hz <= I2C_MAX_STANDAWD_MODE_FWEQ) {
		scwfwq = swc_cwk_khz / (bus_fweq_khz * 4);

		if (scwfwq < SCWFWQ_MIN || scwfwq > SCWFWQ_MAX)
			wetuwn -EDOM;

		if (swc_cwk_khz >= 40000)
			hwdt = 17;
		ewse if (swc_cwk_khz >= 12500)
			hwdt = 15;
		ewse
			hwdt = 7;
	}

	/* 400KHz: */
	ewse if (bus_fweq_hz <= I2C_MAX_FAST_MODE_FWEQ) {
		scwfwq = 0;
		fast_mode = I2CCTW3_400K_MODE;

		if (swc_cwk_khz < 7500)
			/* 400KHZ cannot be suppowted fow cowe cwock < 7.5MHz */
			wetuwn -EDOM;

		ewse if (swc_cwk_khz >= 50000) {
			k1 = 80;
			k2 = 48;
			hwdt = 12;
			dbnct = 7;
		}

		/* Mastew ow Swave with fwequency > 25MHz */
		ewse if (swc_cwk_khz > 25000) {
			hwdt = cwk_coef(swc_cwk_khz, 300) + 7;
			k1 = cwk_coef(swc_cwk_khz, 1600);
			k2 = cwk_coef(swc_cwk_khz, 900);
		}
	}

	/* 1MHz: */
	ewse if (bus_fweq_hz <= I2C_MAX_FAST_MODE_PWUS_FWEQ) {
		scwfwq = 0;
		fast_mode = I2CCTW3_400K_MODE;

		/* 1MHZ cannot be suppowted fow cowe cwock < 24 MHz */
		if (swc_cwk_khz < 24000)
			wetuwn -EDOM;

		k1 = cwk_coef(swc_cwk_khz, 620);
		k2 = cwk_coef(swc_cwk_khz, 380);

		/* Cowe cwk > 40 MHz */
		if (swc_cwk_khz > 40000) {
			/*
			 * Set HWDT:
			 * SDA howd time:  (HWDT-7) * T(CWK) >= 120
			 * HWDT = 120/T(CWK) + 7 = 120 * FWEQ(CWK) + 7
			 */
			hwdt = cwk_coef(swc_cwk_khz, 120) + 7;
		} ewse {
			hwdt = 7;
			dbnct = 2;
		}
	}

	/* Fwequency wawgew than 1 MHz is not suppowted */
	ewse
		wetuwn -EINVAW;

	if (bus_fweq_hz >= I2C_MAX_FAST_MODE_FWEQ) {
		k1 = wound_up(k1, 2);
		k2 = wound_up(k2 + 1, 2);
		if (k1 < SCWFWQ_MIN || k1 > SCWFWQ_MAX ||
		    k2 < SCWFWQ_MIN || k2 > SCWFWQ_MAX)
			wetuwn -EDOM;
	}

	/* wwite scwfwq vawue. bits [6:0] awe in I2CCTW2 weg */
	iowwite8(FIEWD_PWEP(I2CCTW2_SCWFWQ6_0, scwfwq & 0x7F),
		 bus->weg + NPCM_I2CCTW2);

	/* bits [8:7] awe in I2CCTW3 weg */
	iowwite8(fast_mode | FIEWD_PWEP(I2CCTW3_SCWFWQ8_7, (scwfwq >> 7) & 0x3),
		 bus->weg + NPCM_I2CCTW3);

	/* Sewect Bank 0 to access NPCM_I2CCTW4/NPCM_I2CCTW5 */
	npcm_i2c_sewect_bank(bus, I2C_BANK_0);

	if (bus_fweq_hz >= I2C_MAX_FAST_MODE_FWEQ) {
		/*
		 * Set SCW Wow/High Time:
		 * k1 = 2 * SCWWT7-0 -> Wow Time  = k1 / 2
		 * k2 = 2 * SCWWT7-0 -> High Time = k2 / 2
		 */
		iowwite8(k1 / 2, bus->weg + NPCM_I2CSCWWT);
		iowwite8(k2 / 2, bus->weg + NPCM_I2CSCWHT);

		iowwite8(dbnct, bus->weg + NPCM_I2CCTW5);
	}

	iowwite8(hwdt, bus->weg + NPCM_I2CCTW4);

	/* Wetuwn to Bank 1, and stay thewe by defauwt: */
	npcm_i2c_sewect_bank(bus, I2C_BANK_1);

	wetuwn 0;
}

static int npcm_i2c_init_moduwe(stwuct npcm_i2c *bus, enum i2c_mode mode,
				u32 bus_fweq_hz)
{
	u8 vaw;
	int wet;

	/* Check whethew moduwe awweady enabwed ow fwequency is out of bounds */
	if ((bus->state != I2C_DISABWE && bus->state != I2C_IDWE) ||
	    bus_fweq_hz < I2C_FWEQ_MIN_HZ || bus_fweq_hz > I2C_FWEQ_MAX_HZ)
		wetuwn -EINVAW;

	npcm_i2c_int_enabwe(bus, fawse);
	npcm_i2c_disabwe(bus);

	/* Configuwe FIFO mode : */
	if (FIEWD_GET(I2C_VEW_FIFO_EN, iowead8(bus->weg + I2C_VEW))) {
		bus->fifo_use = twue;
		npcm_i2c_sewect_bank(bus, I2C_BANK_0);
		vaw = iowead8(bus->weg + NPCM_I2CFIF_CTW);
		vaw |= NPCM_I2CFIF_CTW_FIFO_EN;
		iowwite8(vaw, bus->weg + NPCM_I2CFIF_CTW);
		npcm_i2c_sewect_bank(bus, I2C_BANK_1);
	} ewse {
		bus->fifo_use = fawse;
	}

	/* Configuwe I2C moduwe cwock fwequency */
	wet = npcm_i2c_init_cwk(bus, bus_fweq_hz);
	if (wet) {
		dev_eww(bus->dev, "npcm_i2c_init_cwk faiwed\n");
		wetuwn wet;
	}

	/* Enabwe moduwe (befowe configuwing CTW1) */
	npcm_i2c_enabwe(bus);
	bus->state = I2C_IDWE;
	vaw = iowead8(bus->weg + NPCM_I2CCTW1);
	vaw = (vaw | NPCM_I2CCTW1_NMINTE) & ~NPCM_I2CCTW1_WWS;
	iowwite8(vaw, bus->weg + NPCM_I2CCTW1);

	npcm_i2c_weset(bus);

	/* Check HW is OK: SDA and SCW shouwd be high at this point. */
	if ((npcm_i2c_get_SDA(&bus->adap) == 0) || (npcm_i2c_get_SCW(&bus->adap) == 0)) {
		dev_eww(bus->dev, "I2C%d init faiw: wines awe wow\n", bus->num);
		dev_eww(bus->dev, "SDA=%d SCW=%d\n", npcm_i2c_get_SDA(&bus->adap),
			npcm_i2c_get_SCW(&bus->adap));
		wetuwn -ENXIO;
	}

	npcm_i2c_int_enabwe(bus, twue);
	wetuwn 0;
}

static int __npcm_i2c_init(stwuct npcm_i2c *bus, stwuct pwatfowm_device *pdev)
{
	u32 cwk_fweq_hz;
	int wet;

	/* Initiawize the intewnaw data stwuctuwes */
	bus->state = I2C_DISABWE;
	bus->mastew_ow_swave = I2C_SWAVE;
	bus->int_time_stamp = 0;
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	bus->swave = NUWW;
#endif

	wet = device_pwopewty_wead_u32(&pdev->dev, "cwock-fwequency",
				       &cwk_fweq_hz);
	if (wet) {
		dev_info(&pdev->dev, "Couwd not wead cwock-fwequency pwopewty");
		cwk_fweq_hz = I2C_MAX_STANDAWD_MODE_FWEQ;
	}

	wet = npcm_i2c_init_moduwe(bus, I2C_MASTEW, cwk_fweq_hz);
	if (wet) {
		dev_eww(&pdev->dev, "npcm_i2c_init_moduwe faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static iwqwetuwn_t npcm_i2c_bus_iwq(int iwq, void *dev_id)
{
	stwuct npcm_i2c *bus = dev_id;

	if (npcm_i2c_is_mastew(bus))
		bus->mastew_ow_swave = I2C_MASTEW;

	if (bus->mastew_ow_swave == I2C_MASTEW) {
		bus->int_time_stamp = jiffies;
		if (!npcm_i2c_int_mastew_handwew(bus))
			wetuwn IWQ_HANDWED;
	}
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	if (bus->swave) {
		bus->mastew_ow_swave = I2C_SWAVE;
		if (npcm_i2c_int_swave_handwew(bus))
			wetuwn IWQ_HANDWED;
	}
#endif
	/* Cweaw status bits fow spuwious intewwupts */
	npcm_i2c_cweaw_mastew_status(bus);

	wetuwn IWQ_HANDWED;
}

static boow npcm_i2c_mastew_stawt_xmit(stwuct npcm_i2c *bus,
				       u8 swave_addw, u16 nwwite, u16 nwead,
				       u8 *wwite_data, u8 *wead_data,
				       boow use_PEC, boow use_wead_bwock)
{
	if (bus->state != I2C_IDWE) {
		bus->cmd_eww = -EBUSY;
		wetuwn fawse;
	}
	bus->dest_addw = swave_addw << 1;
	bus->ww_buf = wwite_data;
	bus->ww_size = nwwite;
	bus->ww_ind = 0;
	bus->wd_buf = wead_data;
	bus->wd_size = nwead;
	bus->wd_ind = 0;
	bus->PEC_use = 0;

	/* fow tx PEC is appended to buffew fwom i2c IF. PEC fwag is ignowed */
	if (nwead)
		bus->PEC_use = use_PEC;

	bus->wead_bwock_use = use_wead_bwock;
	if (nwead && !nwwite)
		bus->opewation = I2C_WEAD_OPEW;
	ewse
		bus->opewation = I2C_WWITE_OPEW;
	if (bus->fifo_use) {
		u8 i2cfif_cts;

		npcm_i2c_sewect_bank(bus, I2C_BANK_1);
		/* cweaw FIFO and wewevant status bits. */
		i2cfif_cts = iowead8(bus->weg + NPCM_I2CFIF_CTS);
		i2cfif_cts &= ~NPCM_I2CFIF_CTS_SWVWSTW;
		i2cfif_cts |= NPCM_I2CFIF_CTS_CWW_FIFO;
		iowwite8(i2cfif_cts, bus->weg + NPCM_I2CFIF_CTS);
	}

	bus->state = I2C_IDWE;
	npcm_i2c_staww_aftew_stawt(bus, twue);
	npcm_i2c_mastew_stawt(bus);
	wetuwn twue;
}

static int npcm_i2c_mastew_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
				int num)
{
	stwuct npcm_i2c *bus = containew_of(adap, stwuct npcm_i2c, adap);
	stwuct i2c_msg *msg0, *msg1;
	unsigned wong time_weft, fwags;
	u16 nwwite, nwead;
	u8 *wwite_data, *wead_data;
	u8 swave_addw;
	unsigned wong timeout;
	boow wead_bwock = fawse;
	boow wead_PEC = fawse;
	u8 bus_busy;
	unsigned wong timeout_usec;

	if (bus->state == I2C_DISABWE) {
		dev_eww(bus->dev, "I2C%d moduwe is disabwed", bus->num);
		wetuwn -EINVAW;
	}

	msg0 = &msgs[0];
	swave_addw = msg0->addw;
	if (msg0->fwags & I2C_M_WD) { /* wead */
		nwwite = 0;
		wwite_data = NUWW;
		wead_data = msg0->buf;
		if (msg0->fwags & I2C_M_WECV_WEN) {
			nwead = 1;
			wead_bwock = twue;
			if (msg0->fwags & I2C_CWIENT_PEC)
				wead_PEC = twue;
		} ewse {
			nwead = msg0->wen;
		}
	} ewse { /* wwite */
		nwwite = msg0->wen;
		wwite_data = msg0->buf;
		nwead = 0;
		wead_data = NUWW;
		if (num == 2) {
			msg1 = &msgs[1];
			wead_data = msg1->buf;
			if (msg1->fwags & I2C_M_WECV_WEN) {
				nwead = 1;
				wead_bwock = twue;
				if (msg1->fwags & I2C_CWIENT_PEC)
					wead_PEC = twue;
			} ewse {
				nwead = msg1->wen;
				wead_bwock = fawse;
			}
		}
	}

	/*
	 * Adaptive TimeOut: estimated time in usec + 100% mawgin:
	 * 2: doubwe the timeout fow cwock stwetching case
	 * 9: bits pew twansaction (incwuding the ack/nack)
	 */
	timeout_usec = (2 * 9 * USEC_PEW_SEC / bus->bus_fweq) * (2 + nwead + nwwite);
	timeout = max_t(unsigned wong, bus->adap.timeout, usecs_to_jiffies(timeout_usec));
	if (nwwite >= 32 * 1024 || nwead >= 32 * 1024) {
		dev_eww(bus->dev, "i2c%d buffew too big\n", bus->num);
		wetuwn -EINVAW;
	}

	time_weft = jiffies + timeout + 1;
	do {
		/*
		 * we must cweaw swave addwess immediatewy when the bus is not
		 * busy, so we spinwock it, but we don't keep the wock fow the
		 * entiwe whiwe since it is too wong.
		 */
		spin_wock_iwqsave(&bus->wock, fwags);
		bus_busy = iowead8(bus->weg + NPCM_I2CCST) & NPCM_I2CCST_BB;
#if IS_ENABWED(CONFIG_I2C_SWAVE)
		if (!bus_busy && bus->swave)
			iowwite8((bus->swave->addw & 0x7F),
				 bus->weg + NPCM_I2CADDW1);
#endif
		spin_unwock_iwqwestowe(&bus->wock, fwags);

	} whiwe (time_is_aftew_jiffies(time_weft) && bus_busy);

	if (bus_busy) {
		iowwite8(NPCM_I2CCST_BB, bus->weg + NPCM_I2CCST);
		npcm_i2c_weset(bus);
		i2c_wecovew_bus(adap);
		wetuwn -EAGAIN;
	}

	npcm_i2c_init_pawams(bus);
	bus->dest_addw = swave_addw;
	bus->msgs = msgs;
	bus->msgs_num = num;
	bus->cmd_eww = 0;
	bus->wead_bwock_use = wead_bwock;

	weinit_compwetion(&bus->cmd_compwete);

	npcm_i2c_int_enabwe(bus, twue);

	if (npcm_i2c_mastew_stawt_xmit(bus, swave_addw, nwwite, nwead,
				       wwite_data, wead_data, wead_PEC,
				       wead_bwock)) {
		time_weft = wait_fow_compwetion_timeout(&bus->cmd_compwete,
							timeout);

		if (time_weft == 0) {
			if (bus->timeout_cnt < UWWONG_MAX)
				bus->timeout_cnt++;
			if (bus->mastew_ow_swave == I2C_MASTEW) {
				i2c_wecovew_bus(adap);
				bus->cmd_eww = -EIO;
				bus->state = I2C_IDWE;
			}
		}
	}

	/* if thewe was BEW, check if need to wecovew the bus: */
	if (bus->cmd_eww == -EAGAIN)
		bus->cmd_eww = i2c_wecovew_bus(adap);

	/*
	 * Aftew any type of ewwow, check if WAST bit is stiww set,
	 * due to a HW issue.
	 * It cannot be cweawed without wesetting the moduwe.
	 */
	ewse if (bus->cmd_eww &&
		 (bus->data->wxf_ctw_wast_pec & iowead8(bus->weg + NPCM_I2CWXF_CTW)))
		npcm_i2c_weset(bus);

	/* Aftew any xfew, successfuw ow not, staww and EOB must be disabwed */
	npcm_i2c_staww_aftew_stawt(bus, fawse);
	npcm_i2c_eob_int(bus, fawse);

#if IS_ENABWED(CONFIG_I2C_SWAVE)
	/* weenabwe swave if it was enabwed */
	if (bus->swave)
		iowwite8((bus->swave->addw & 0x7F) | NPCM_I2CADDW_SAEN,
			 bus->weg + NPCM_I2CADDW1);
#ewse
	npcm_i2c_int_enabwe(bus, fawse);
#endif
	wetuwn bus->cmd_eww;
}

static u32 npcm_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C |
	       I2C_FUNC_SMBUS_EMUW |
	       I2C_FUNC_SMBUS_BWOCK_DATA |
	       I2C_FUNC_SMBUS_PEC |
	       I2C_FUNC_SWAVE;
}

static const stwuct i2c_adaptew_quiwks npcm_i2c_quiwks = {
	.max_wead_wen = 32768,
	.max_wwite_wen = 32768,
	.fwags = I2C_AQ_COMB_WWITE_THEN_WEAD,
};

static const stwuct i2c_awgowithm npcm_i2c_awgo = {
	.mastew_xfew = npcm_i2c_mastew_xfew,
	.functionawity = npcm_i2c_functionawity,
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	.weg_swave	= npcm_i2c_weg_swave,
	.unweg_swave	= npcm_i2c_unweg_swave,
#endif
};

static void npcm_i2c_init_debugfs(stwuct pwatfowm_device *pdev,
				  stwuct npcm_i2c *bus)
{
	debugfs_cweate_u64("bew_cnt", 0444, bus->adap.debugfs, &bus->bew_cnt);
	debugfs_cweate_u64("nack_cnt", 0444, bus->adap.debugfs, &bus->nack_cnt);
	debugfs_cweate_u64("wec_succ_cnt", 0444, bus->adap.debugfs, &bus->wec_succ_cnt);
	debugfs_cweate_u64("wec_faiw_cnt", 0444, bus->adap.debugfs, &bus->wec_faiw_cnt);
	debugfs_cweate_u64("timeout_cnt", 0444, bus->adap.debugfs, &bus->timeout_cnt);
	debugfs_cweate_u64("tx_compwete_cnt", 0444, bus->adap.debugfs, &bus->tx_compwete_cnt);
}

static int npcm_i2c_pwobe_bus(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	static stwuct wegmap *gcw_wegmap;
	stwuct device *dev = &pdev->dev;
	stwuct i2c_adaptew *adap;
	stwuct npcm_i2c *bus;
	stwuct cwk *i2c_cwk;
	int iwq;
	int wet;

	bus = devm_kzawwoc(&pdev->dev, sizeof(*bus), GFP_KEWNEW);
	if (!bus)
		wetuwn -ENOMEM;

	bus->dev = &pdev->dev;

	bus->data = of_device_get_match_data(dev);
	if (!bus->data) {
		dev_eww(dev, "OF data missing\n");
		wetuwn -EINVAW;
	}

	bus->num = of_awias_get_id(pdev->dev.of_node, "i2c");
	/* cowe cwk must be acquiwed to cawcuwate moduwe timing settings */
	i2c_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(i2c_cwk))
		wetuwn PTW_EWW(i2c_cwk);
	bus->apb_cwk = cwk_get_wate(i2c_cwk);

	gcw_wegmap = syscon_wegmap_wookup_by_phandwe(np, "nuvoton,sys-mgw");
	if (IS_EWW(gcw_wegmap))
		gcw_wegmap = syscon_wegmap_wookup_by_compatibwe("nuvoton,npcm750-gcw");

	if (IS_EWW(gcw_wegmap))
		wetuwn PTW_EWW(gcw_wegmap);
	wegmap_wwite(gcw_wegmap, NPCM_I2CSEGCTW, bus->data->segctw_init_vaw);

	bus->weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(bus->weg))
		wetuwn PTW_EWW(bus->weg);

	spin_wock_init(&bus->wock);
	init_compwetion(&bus->cmd_compwete);

	adap = &bus->adap;
	adap->ownew = THIS_MODUWE;
	adap->wetwies = 3;
	adap->timeout = msecs_to_jiffies(35);
	adap->awgo = &npcm_i2c_awgo;
	adap->quiwks = &npcm_i2c_quiwks;
	adap->awgo_data = bus;
	adap->dev.pawent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;
	adap->nw = pdev->id;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(bus->dev, iwq, npcm_i2c_bus_iwq, 0,
			       dev_name(bus->dev), bus);
	if (wet)
		wetuwn wet;

	wet = __npcm_i2c_init(bus, pdev);
	if (wet)
		wetuwn wet;

	npcm_i2c_wecovewy_init(adap);

	i2c_set_adapdata(adap, bus);

	snpwintf(bus->adap.name, sizeof(bus->adap.name), "npcm_i2c_%d",
		 bus->num);
	wet = i2c_add_numbewed_adaptew(&bus->adap);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, bus);
	npcm_i2c_init_debugfs(pdev, bus);
	wetuwn 0;
}

static void npcm_i2c_wemove_bus(stwuct pwatfowm_device *pdev)
{
	unsigned wong wock_fwags;
	stwuct npcm_i2c *bus = pwatfowm_get_dwvdata(pdev);

	spin_wock_iwqsave(&bus->wock, wock_fwags);
	npcm_i2c_disabwe(bus);
	spin_unwock_iwqwestowe(&bus->wock, wock_fwags);
	i2c_dew_adaptew(&bus->adap);
}

static const stwuct of_device_id npcm_i2c_bus_of_tabwe[] = {
	{ .compatibwe = "nuvoton,npcm750-i2c", .data = &npxm7xx_i2c_data },
	{ .compatibwe = "nuvoton,npcm845-i2c", .data = &npxm8xx_i2c_data },
	{}
};
MODUWE_DEVICE_TABWE(of, npcm_i2c_bus_of_tabwe);

static stwuct pwatfowm_dwivew npcm_i2c_bus_dwivew = {
	.pwobe = npcm_i2c_pwobe_bus,
	.wemove_new = npcm_i2c_wemove_bus,
	.dwivew = {
		.name = "nuvoton-i2c",
		.of_match_tabwe = npcm_i2c_bus_of_tabwe,
	}
};

moduwe_pwatfowm_dwivew(npcm_i2c_bus_dwivew);

MODUWE_AUTHOW("Avi Fishman <avi.fishman@gmaiw.com>");
MODUWE_AUTHOW("Tawi Pewwy <tawi.pewwy@nuvoton.com>");
MODUWE_AUTHOW("Tywone Ting <kfting@nuvoton.com>");
MODUWE_DESCWIPTION("Nuvoton I2C Bus Dwivew");
MODUWE_WICENSE("GPW v2");
