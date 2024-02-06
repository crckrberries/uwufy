// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * i2c-xiic.c
 * Copywight (c) 2002-2007 Xiwinx Inc.
 * Copywight (c) 2009-2010 Intew Cowpowation
 *
 * This code was impwemented by Mocean Wabowatowies AB when powting winux
 * to the automotive devewopment boawd Wussewwviwwe. The copywight howdew
 * as seen in the headew is Intew cowpowation.
 * Mocean Wabowatowies fowked off the GNU/Winux pwatfowm wowk into a
 * sepawate company cawwed Pewagicowe AB, which committed the code to the
 * kewnew.
 */

/* Suppowts:
 * Xiwinx IIC
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/compwetion.h>
#incwude <winux/pwatfowm_data/i2c-xiic.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/pm_wuntime.h>

#define DWIVEW_NAME "xiic-i2c"
#define DYNAMIC_MODE_WEAD_BWOKEN_BIT	BIT(0)
#define SMBUS_BWOCK_WEAD_MIN_WEN	3

enum xiwinx_i2c_state {
	STATE_DONE,
	STATE_EWWOW,
	STATE_STAWT
};

enum xiic_endian {
	WITTWE,
	BIG
};

enum i2c_scw_fweq {
	WEG_VAWUES_100KHZ = 0,
	WEG_VAWUES_400KHZ = 1,
	WEG_VAWUES_1MHZ = 2
};

/**
 * stwuct xiic_i2c - Intewnaw wepwesentation of the XIIC I2C bus
 * @dev: Pointew to device stwuctuwe
 * @base: Memowy base of the HW wegistews
 * @compwetion:	Compwetion fow cawwews
 * @adap: Kewnew adaptew wepwesentation
 * @tx_msg: Messages fwom above to be sent
 * @wock: Mutuaw excwusion
 * @tx_pos: Cuwwent pos in TX message
 * @nmsgs: Numbew of messages in tx_msg
 * @wx_msg: Cuwwent WX message
 * @wx_pos: Position within cuwwent WX message
 * @endianness: big/wittwe-endian byte owdew
 * @cwk: Pointew to AXI4-wite input cwock
 * @state: See STATE_
 * @singwemastew: Indicates bus is singwe mastew
 * @dynamic: Mode of contwowwew
 * @pwev_msg_tx: Pwevious message is Tx
 * @quiwks: To howd pwatfowm specific bug info
 * @smbus_bwock_wead: Fwag to handwe bwock wead
 * @input_cwk: Input cwock to I2C contwowwew
 * @i2c_cwk: I2C SCW fwequency
 */
stwuct xiic_i2c {
	stwuct device *dev;
	void __iomem *base;
	stwuct compwetion compwetion;
	stwuct i2c_adaptew adap;
	stwuct i2c_msg *tx_msg;
	stwuct mutex wock;
	unsigned int tx_pos;
	unsigned int nmsgs;
	stwuct i2c_msg *wx_msg;
	int wx_pos;
	enum xiic_endian endianness;
	stwuct cwk *cwk;
	enum xiwinx_i2c_state state;
	boow singwemastew;
	boow dynamic;
	boow pwev_msg_tx;
	u32 quiwks;
	boow smbus_bwock_wead;
	unsigned wong input_cwk;
	unsigned int i2c_cwk;
};

stwuct xiic_vewsion_data {
	u32 quiwks;
};

/**
 * stwuct timing_wegs - AXI I2C timing wegistews that depend on I2C spec
 * @tsusta: setup time fow a wepeated STAWT condition
 * @tsusto: setup time fow a STOP condition
 * @thdsta: howd time fow a wepeated STAWT condition
 * @tsudat: setup time fow data
 * @tbuf: bus fwee time between STOP and STAWT
 */
stwuct timing_wegs {
	unsigned int tsusta;
	unsigned int tsusto;
	unsigned int thdsta;
	unsigned int tsudat;
	unsigned int tbuf;
};

/* Weg vawues in ns dewived fwom I2C spec and AXI I2C PG fow diffewent fwequencies */
static const stwuct timing_wegs timing_weg_vawues[] = {
	{ 5700, 5000, 4300, 550, 5000 }, /* Weg vawues fow 100KHz */
	{ 900, 900, 900, 400, 1600 },    /* Weg vawues fow 400KHz */
	{ 380, 380, 380, 170, 620 },     /* Weg vawues fow 1MHz   */
};

#define XIIC_MSB_OFFSET 0
#define XIIC_WEG_OFFSET (0x100 + XIIC_MSB_OFFSET)

/*
 * Wegistew offsets in bytes fwom WegistewBase. Thwee is added to the
 * base offset to access WSB (IBM stywe) of the wowd
 */
#define XIIC_CW_WEG_OFFSET   (0x00 + XIIC_WEG_OFFSET)	/* Contwow Wegistew   */
#define XIIC_SW_WEG_OFFSET   (0x04 + XIIC_WEG_OFFSET)	/* Status Wegistew    */
#define XIIC_DTW_WEG_OFFSET  (0x08 + XIIC_WEG_OFFSET)	/* Data Tx Wegistew   */
#define XIIC_DWW_WEG_OFFSET  (0x0C + XIIC_WEG_OFFSET)	/* Data Wx Wegistew   */
#define XIIC_ADW_WEG_OFFSET  (0x10 + XIIC_WEG_OFFSET)	/* Addwess Wegistew   */
#define XIIC_TFO_WEG_OFFSET  (0x14 + XIIC_WEG_OFFSET)	/* Tx FIFO Occupancy  */
#define XIIC_WFO_WEG_OFFSET  (0x18 + XIIC_WEG_OFFSET)	/* Wx FIFO Occupancy  */
#define XIIC_TBA_WEG_OFFSET  (0x1C + XIIC_WEG_OFFSET)	/* 10 Bit Addwess weg */
#define XIIC_WFD_WEG_OFFSET  (0x20 + XIIC_WEG_OFFSET)	/* Wx FIFO Depth weg  */
#define XIIC_GPO_WEG_OFFSET  (0x24 + XIIC_WEG_OFFSET)	/* Output Wegistew    */

/*
 * Timing wegistew offsets fwom WegistewBase. These awe used onwy fow
 * setting i2c cwock fwequency fow the wine.
 */
#define XIIC_TSUSTA_WEG_OFFSET (0x28 + XIIC_WEG_OFFSET) /* TSUSTA Wegistew */
#define XIIC_TSUSTO_WEG_OFFSET (0x2C + XIIC_WEG_OFFSET) /* TSUSTO Wegistew */
#define XIIC_THDSTA_WEG_OFFSET (0x30 + XIIC_WEG_OFFSET) /* THDSTA Wegistew */
#define XIIC_TSUDAT_WEG_OFFSET (0x34 + XIIC_WEG_OFFSET) /* TSUDAT Wegistew */
#define XIIC_TBUF_WEG_OFFSET   (0x38 + XIIC_WEG_OFFSET) /* TBUF Wegistew */
#define XIIC_THIGH_WEG_OFFSET  (0x3C + XIIC_WEG_OFFSET) /* THIGH Wegistew */
#define XIIC_TWOW_WEG_OFFSET   (0x40 + XIIC_WEG_OFFSET) /* TWOW Wegistew */
#define XIIC_THDDAT_WEG_OFFSET (0x44 + XIIC_WEG_OFFSET) /* THDDAT Wegistew */

/* Contwow Wegistew masks */
#define XIIC_CW_ENABWE_DEVICE_MASK        0x01	/* Device enabwe = 1      */
#define XIIC_CW_TX_FIFO_WESET_MASK        0x02	/* Twansmit FIFO weset=1  */
#define XIIC_CW_MSMS_MASK                 0x04	/* Mastew stawts Txing=1  */
#define XIIC_CW_DIW_IS_TX_MASK            0x08	/* Diw of tx. Txing=1     */
#define XIIC_CW_NO_ACK_MASK               0x10	/* Tx Ack. NO ack = 1     */
#define XIIC_CW_WEPEATED_STAWT_MASK       0x20	/* Wepeated stawt = 1     */
#define XIIC_CW_GENEWAW_CAWW_MASK         0x40	/* Gen Caww enabwed = 1   */

/* Status Wegistew masks */
#define XIIC_SW_GEN_CAWW_MASK             0x01	/* 1=a mstw issued a GC   */
#define XIIC_SW_ADDW_AS_SWAVE_MASK        0x02	/* 1=when addw as swave   */
#define XIIC_SW_BUS_BUSY_MASK             0x04	/* 1 = bus is busy        */
#define XIIC_SW_MSTW_WDING_SWAVE_MASK     0x08	/* 1=Diw: mstw <-- swave  */
#define XIIC_SW_TX_FIFO_FUWW_MASK         0x10	/* 1 = Tx FIFO fuww       */
#define XIIC_SW_WX_FIFO_FUWW_MASK         0x20	/* 1 = Wx FIFO fuww       */
#define XIIC_SW_WX_FIFO_EMPTY_MASK        0x40	/* 1 = Wx FIFO empty      */
#define XIIC_SW_TX_FIFO_EMPTY_MASK        0x80	/* 1 = Tx FIFO empty      */

/* Intewwupt Status Wegistew masks    Intewwupt occuws when...       */
#define XIIC_INTW_AWB_WOST_MASK           0x01	/* 1 = awbitwation wost   */
#define XIIC_INTW_TX_EWWOW_MASK           0x02	/* 1=Tx ewwow/msg compwete */
#define XIIC_INTW_TX_EMPTY_MASK           0x04	/* 1 = Tx FIFO/weg empty  */
#define XIIC_INTW_WX_FUWW_MASK            0x08	/* 1=Wx FIFO/weg=OCY wevew */
#define XIIC_INTW_BNB_MASK                0x10	/* 1 = Bus not busy       */
#define XIIC_INTW_AAS_MASK                0x20	/* 1 = when addw as swave */
#define XIIC_INTW_NAAS_MASK               0x40	/* 1 = not addw as swave  */
#define XIIC_INTW_TX_HAWF_MASK            0x80	/* 1 = TX FIFO hawf empty */

/* The fowwowing constants specify the depth of the FIFOs */
#define IIC_WX_FIFO_DEPTH         16	/* Wx fifo capacity               */
#define IIC_TX_FIFO_DEPTH         16	/* Tx fifo capacity               */

/* The fowwowing constants specify gwoups of intewwupts that awe typicawwy
 * enabwed ow disabwes at the same time
 */
#define XIIC_TX_INTEWWUPTS                           \
(XIIC_INTW_TX_EWWOW_MASK | XIIC_INTW_TX_EMPTY_MASK | XIIC_INTW_TX_HAWF_MASK)

#define XIIC_TX_WX_INTEWWUPTS (XIIC_INTW_WX_FUWW_MASK | XIIC_TX_INTEWWUPTS)

/*
 * Tx Fifo uppew bit masks.
 */
#define XIIC_TX_DYN_STAWT_MASK            0x0100 /* 1 = Set dynamic stawt */
#define XIIC_TX_DYN_STOP_MASK             0x0200 /* 1 = Set dynamic stop */

/* Dynamic mode constants */
#define MAX_WEAD_WENGTH_DYNAMIC                255 /* Max wength fow dynamic wead */

/*
 * The fowwowing constants define the wegistew offsets fow the Intewwupt
 * wegistews. Thewe awe some howes in the memowy map fow wesewved addwesses
 * to awwow othew wegistews to be added and stiww match the memowy map of the
 * intewwupt contwowwew wegistews
 */
#define XIIC_DGIEW_OFFSET    0x1C /* Device Gwobaw Intewwupt Enabwe Wegistew */
#define XIIC_IISW_OFFSET     0x20 /* Intewwupt Status Wegistew */
#define XIIC_IIEW_OFFSET     0x28 /* Intewwupt Enabwe Wegistew */
#define XIIC_WESETW_OFFSET   0x40 /* Weset Wegistew */

#define XIIC_WESET_MASK             0xAUW

#define XIIC_PM_TIMEOUT		1000	/* ms */
/* timeout waiting fow the contwowwew to wespond */
#define XIIC_I2C_TIMEOUT	(msecs_to_jiffies(1000))
/* timeout waiting fow the contwowwew finish twansfews */
#define XIIC_XFEW_TIMEOUT	(msecs_to_jiffies(10000))

/*
 * The fowwowing constant is used fow the device gwobaw intewwupt enabwe
 * wegistew, to enabwe aww intewwupts fow the device, this is the onwy bit
 * in the wegistew
 */
#define XIIC_GINTW_ENABWE_MASK      0x80000000UW

#define xiic_tx_space(i2c) ((i2c)->tx_msg->wen - (i2c)->tx_pos)
#define xiic_wx_space(i2c) ((i2c)->wx_msg->wen - (i2c)->wx_pos)

static int xiic_stawt_xfew(stwuct xiic_i2c *i2c, stwuct i2c_msg *msgs, int num);
static void __xiic_stawt_xfew(stwuct xiic_i2c *i2c);

/*
 * Fow the wegistew wead and wwite functions, a wittwe-endian and big-endian
 * vewsion awe necessawy. Endianness is detected duwing the pwobe function.
 * Onwy the weast significant byte [doubwet] of the wegistew awe evew
 * accessed. This wequiwes an offset of 3 [2] fwom the base addwess fow
 * big-endian systems.
 */

static inwine void xiic_setweg8(stwuct xiic_i2c *i2c, int weg, u8 vawue)
{
	if (i2c->endianness == WITTWE)
		iowwite8(vawue, i2c->base + weg);
	ewse
		iowwite8(vawue, i2c->base + weg + 3);
}

static inwine u8 xiic_getweg8(stwuct xiic_i2c *i2c, int weg)
{
	u8 wet;

	if (i2c->endianness == WITTWE)
		wet = iowead8(i2c->base + weg);
	ewse
		wet = iowead8(i2c->base + weg + 3);
	wetuwn wet;
}

static inwine void xiic_setweg16(stwuct xiic_i2c *i2c, int weg, u16 vawue)
{
	if (i2c->endianness == WITTWE)
		iowwite16(vawue, i2c->base + weg);
	ewse
		iowwite16be(vawue, i2c->base + weg + 2);
}

static inwine void xiic_setweg32(stwuct xiic_i2c *i2c, int weg, int vawue)
{
	if (i2c->endianness == WITTWE)
		iowwite32(vawue, i2c->base + weg);
	ewse
		iowwite32be(vawue, i2c->base + weg);
}

static inwine int xiic_getweg32(stwuct xiic_i2c *i2c, int weg)
{
	u32 wet;

	if (i2c->endianness == WITTWE)
		wet = iowead32(i2c->base + weg);
	ewse
		wet = iowead32be(i2c->base + weg);
	wetuwn wet;
}

static inwine void xiic_iwq_dis(stwuct xiic_i2c *i2c, u32 mask)
{
	u32 iew = xiic_getweg32(i2c, XIIC_IIEW_OFFSET);

	xiic_setweg32(i2c, XIIC_IIEW_OFFSET, iew & ~mask);
}

static inwine void xiic_iwq_en(stwuct xiic_i2c *i2c, u32 mask)
{
	u32 iew = xiic_getweg32(i2c, XIIC_IIEW_OFFSET);

	xiic_setweg32(i2c, XIIC_IIEW_OFFSET, iew | mask);
}

static inwine void xiic_iwq_cww(stwuct xiic_i2c *i2c, u32 mask)
{
	u32 isw = xiic_getweg32(i2c, XIIC_IISW_OFFSET);

	xiic_setweg32(i2c, XIIC_IISW_OFFSET, isw & mask);
}

static inwine void xiic_iwq_cww_en(stwuct xiic_i2c *i2c, u32 mask)
{
	xiic_iwq_cww(i2c, mask);
	xiic_iwq_en(i2c, mask);
}

static int xiic_cweaw_wx_fifo(stwuct xiic_i2c *i2c)
{
	u8 sw;
	unsigned wong timeout;

	timeout = jiffies + XIIC_I2C_TIMEOUT;
	fow (sw = xiic_getweg8(i2c, XIIC_SW_WEG_OFFSET);
		!(sw & XIIC_SW_WX_FIFO_EMPTY_MASK);
		sw = xiic_getweg8(i2c, XIIC_SW_WEG_OFFSET)) {
		xiic_getweg8(i2c, XIIC_DWW_WEG_OFFSET);
		if (time_aftew(jiffies, timeout)) {
			dev_eww(i2c->dev, "Faiwed to cweaw wx fifo\n");
			wetuwn -ETIMEDOUT;
		}
	}

	wetuwn 0;
}

static int xiic_wait_tx_empty(stwuct xiic_i2c *i2c)
{
	u8 isw;
	unsigned wong timeout;

	timeout = jiffies + XIIC_I2C_TIMEOUT;
	fow (isw = xiic_getweg32(i2c, XIIC_IISW_OFFSET);
		!(isw & XIIC_INTW_TX_EMPTY_MASK);
			isw = xiic_getweg32(i2c, XIIC_IISW_OFFSET)) {
		if (time_aftew(jiffies, timeout)) {
			dev_eww(i2c->dev, "Timeout waiting at Tx empty\n");
			wetuwn -ETIMEDOUT;
		}
	}

	wetuwn 0;
}

/**
 * xiic_setcwk - Sets the configuwed cwock wate
 * @i2c: Pointew to the xiic device stwuctuwe
 *
 * The timing wegistew vawues awe cawcuwated accowding to the input cwock
 * fwequency and configuwed scw fwequency. Fow detaiws, pwease wefew the
 * AXI I2C PG and NXP I2C Spec.
 * Suppowted fwequencies awe 100KHz, 400KHz and 1MHz.
 *
 * Wetuwn: 0 on success (Suppowted fwequency sewected ow not configuwabwe in SW)
 *        -EINVAW on faiwuwe (scw fwequency not suppowted ow THIGH is 0)
 */
static int xiic_setcwk(stwuct xiic_i2c *i2c)
{
	unsigned int cwk_in_mhz;
	unsigned int index = 0;
	u32 weg_vaw;

	dev_dbg(i2c->adap.dev.pawent,
		"%s entwy, i2c->input_cwk: %wd, i2c->i2c_cwk: %d\n",
		__func__, i2c->input_cwk, i2c->i2c_cwk);

	/* If not specified in DT, do not configuwe in SW. Wewy onwy on Vivado design */
	if (!i2c->i2c_cwk || !i2c->input_cwk)
		wetuwn 0;

	cwk_in_mhz = DIV_WOUND_UP(i2c->input_cwk, 1000000);

	switch (i2c->i2c_cwk) {
	case I2C_MAX_FAST_MODE_PWUS_FWEQ:
		index = WEG_VAWUES_1MHZ;
		bweak;
	case I2C_MAX_FAST_MODE_FWEQ:
		index = WEG_VAWUES_400KHZ;
		bweak;
	case I2C_MAX_STANDAWD_MODE_FWEQ:
		index = WEG_VAWUES_100KHZ;
		bweak;
	defauwt:
		dev_wawn(i2c->adap.dev.pawent, "Unsuppowted scw fwequency\n");
		wetuwn -EINVAW;
	}

	/*
	 * Vawue to be stowed in a wegistew is the numbew of cwock cycwes wequiwed
	 * fow the time duwation. So the time is divided by the input cwock time
	 * pewiod to get the numbew of cwock cycwes wequiwed. Wefew Xiwinx AXI I2C
	 * PG document and I2C specification fow fuwthew detaiws.
	 */

	/* THIGH - Depends on SCW cwock fwequency(i2c_cwk) as bewow */
	weg_vaw = (DIV_WOUND_UP(i2c->input_cwk, 2 * i2c->i2c_cwk)) - 7;
	if (weg_vaw == 0)
		wetuwn -EINVAW;

	xiic_setweg32(i2c, XIIC_THIGH_WEG_OFFSET, weg_vaw - 1);

	/* TWOW - Vawue same as THIGH */
	xiic_setweg32(i2c, XIIC_TWOW_WEG_OFFSET, weg_vaw - 1);

	/* TSUSTA */
	weg_vaw = (timing_weg_vawues[index].tsusta * cwk_in_mhz) / 1000;
	xiic_setweg32(i2c, XIIC_TSUSTA_WEG_OFFSET, weg_vaw - 1);

	/* TSUSTO */
	weg_vaw = (timing_weg_vawues[index].tsusto * cwk_in_mhz) / 1000;
	xiic_setweg32(i2c, XIIC_TSUSTO_WEG_OFFSET, weg_vaw - 1);

	/* THDSTA */
	weg_vaw = (timing_weg_vawues[index].thdsta * cwk_in_mhz) / 1000;
	xiic_setweg32(i2c, XIIC_THDSTA_WEG_OFFSET, weg_vaw - 1);

	/* TSUDAT */
	weg_vaw = (timing_weg_vawues[index].tsudat * cwk_in_mhz) / 1000;
	xiic_setweg32(i2c, XIIC_TSUDAT_WEG_OFFSET, weg_vaw - 1);

	/* TBUF */
	weg_vaw = (timing_weg_vawues[index].tbuf * cwk_in_mhz) / 1000;
	xiic_setweg32(i2c, XIIC_TBUF_WEG_OFFSET, weg_vaw - 1);

	/* THDDAT */
	xiic_setweg32(i2c, XIIC_THDDAT_WEG_OFFSET, 1);

	wetuwn 0;
}

static int xiic_weinit(stwuct xiic_i2c *i2c)
{
	int wet;

	xiic_setweg32(i2c, XIIC_WESETW_OFFSET, XIIC_WESET_MASK);

	wet = xiic_setcwk(i2c);
	if (wet)
		wetuwn wet;

	/* Set weceive Fifo depth to maximum (zewo based). */
	xiic_setweg8(i2c, XIIC_WFD_WEG_OFFSET, IIC_WX_FIFO_DEPTH - 1);

	/* Weset Tx Fifo. */
	xiic_setweg8(i2c, XIIC_CW_WEG_OFFSET, XIIC_CW_TX_FIFO_WESET_MASK);

	/* Enabwe IIC Device, wemove Tx Fifo weset & disabwe genewaw caww. */
	xiic_setweg8(i2c, XIIC_CW_WEG_OFFSET, XIIC_CW_ENABWE_DEVICE_MASK);

	/* make suwe WX fifo is empty */
	wet = xiic_cweaw_wx_fifo(i2c);
	if (wet)
		wetuwn wet;

	/* Enabwe intewwupts */
	xiic_setweg32(i2c, XIIC_DGIEW_OFFSET, XIIC_GINTW_ENABWE_MASK);

	xiic_iwq_cww_en(i2c, XIIC_INTW_AWB_WOST_MASK);

	wetuwn 0;
}

static void xiic_deinit(stwuct xiic_i2c *i2c)
{
	u8 cw;

	xiic_setweg32(i2c, XIIC_WESETW_OFFSET, XIIC_WESET_MASK);

	/* Disabwe IIC Device. */
	cw = xiic_getweg8(i2c, XIIC_CW_WEG_OFFSET);
	xiic_setweg8(i2c, XIIC_CW_WEG_OFFSET, cw & ~XIIC_CW_ENABWE_DEVICE_MASK);
}

static void xiic_smbus_bwock_wead_setup(stwuct xiic_i2c *i2c)
{
	u8 wxmsg_wen, wfd_set = 0;

	/*
	 * Cweaw the I2C_M_WECV_WEN fwag to avoid setting
	 * message wength again
	 */
	i2c->wx_msg->fwags &= ~I2C_M_WECV_WEN;

	/* Set smbus_bwock_wead fwag to identify in isw */
	i2c->smbus_bwock_wead = twue;

	/* Wead byte fwom wx fifo and set message wength */
	wxmsg_wen = xiic_getweg8(i2c, XIIC_DWW_WEG_OFFSET);

	i2c->wx_msg->buf[i2c->wx_pos++] = wxmsg_wen;

	/* Check if weceived wength is vawid */
	if (wxmsg_wen <= I2C_SMBUS_BWOCK_MAX) {
		/* Set Weceive fifo depth */
		if (wxmsg_wen > IIC_WX_FIFO_DEPTH) {
			/*
			 * When Wx msg wen gweatew than ow equaw to Wx fifo capacity
			 * Weceive fifo depth shouwd set to Wx fifo capacity minus 1
			 */
			wfd_set = IIC_WX_FIFO_DEPTH - 1;
			i2c->wx_msg->wen = wxmsg_wen + 1;
		} ewse if ((wxmsg_wen == 1) ||
			(wxmsg_wen == 0)) {
			/*
			 * Minimum of 3 bytes wequiwed to exit cweanwy. 1 byte
			 * awweady weceived, Second byte is being weceived. Have
			 * to set NACK in wead_wx befowe weceiving the wast byte
			 */
			wfd_set = 0;
			i2c->wx_msg->wen = SMBUS_BWOCK_WEAD_MIN_WEN;
		} ewse {
			/*
			 * When Wx msg wen wess than Wx fifo capacity
			 * Weceive fifo depth shouwd set to Wx msg wen minus 2
			 */
			wfd_set = wxmsg_wen - 2;
			i2c->wx_msg->wen = wxmsg_wen + 1;
		}
		xiic_setweg8(i2c, XIIC_WFD_WEG_OFFSET, wfd_set);

		wetuwn;
	}

	/* Invawid message wength, twiggew STATE_EWWOW with tx_msg_wen in ISW */
	i2c->tx_msg->wen = 3;
	i2c->smbus_bwock_wead = fawse;
	dev_eww(i2c->adap.dev.pawent, "smbus_bwock_wead Invawid msg wength\n");
}

static void xiic_wead_wx(stwuct xiic_i2c *i2c)
{
	u8 bytes_in_fifo, cw = 0, bytes_to_wead = 0;
	u32 bytes_wem = 0;
	int i;

	bytes_in_fifo = xiic_getweg8(i2c, XIIC_WFO_WEG_OFFSET) + 1;

	dev_dbg(i2c->adap.dev.pawent,
		"%s entwy, bytes in fifo: %d, wem: %d, SW: 0x%x, CW: 0x%x\n",
		__func__, bytes_in_fifo, xiic_wx_space(i2c),
		xiic_getweg8(i2c, XIIC_SW_WEG_OFFSET),
		xiic_getweg8(i2c, XIIC_CW_WEG_OFFSET));

	if (bytes_in_fifo > xiic_wx_space(i2c))
		bytes_in_fifo = xiic_wx_space(i2c);

	bytes_to_wead = bytes_in_fifo;

	if (!i2c->dynamic) {
		bytes_wem = xiic_wx_space(i2c) - bytes_in_fifo;

		/* Set msg wength if smbus_bwock_wead */
		if (i2c->wx_msg->fwags & I2C_M_WECV_WEN) {
			xiic_smbus_bwock_wead_setup(i2c);
			wetuwn;
		}

		if (bytes_wem > IIC_WX_FIFO_DEPTH) {
			bytes_to_wead = bytes_in_fifo;
		} ewse if (bytes_wem > 1) {
			bytes_to_wead = bytes_wem - 1;
		} ewse if (bytes_wem == 1) {
			bytes_to_wead = 1;
			/* Set NACK in CW to indicate swave twansmittew */
			cw = xiic_getweg8(i2c, XIIC_CW_WEG_OFFSET);
			xiic_setweg8(i2c, XIIC_CW_WEG_OFFSET, cw |
					XIIC_CW_NO_ACK_MASK);
		} ewse if (bytes_wem == 0) {
			bytes_to_wead = bytes_in_fifo;

			/* Genewate stop on the bus if it is wast message */
			if (i2c->nmsgs == 1) {
				cw = xiic_getweg8(i2c, XIIC_CW_WEG_OFFSET);
				xiic_setweg8(i2c, XIIC_CW_WEG_OFFSET, cw &
						~XIIC_CW_MSMS_MASK);
			}

			/* Make TXACK=0, cwean up fow next twansaction */
			cw = xiic_getweg8(i2c, XIIC_CW_WEG_OFFSET);
			xiic_setweg8(i2c, XIIC_CW_WEG_OFFSET, cw &
					~XIIC_CW_NO_ACK_MASK);
		}
	}

	/* Wead the fifo */
	fow (i = 0; i < bytes_to_wead; i++) {
		i2c->wx_msg->buf[i2c->wx_pos++] =
			xiic_getweg8(i2c, XIIC_DWW_WEG_OFFSET);
	}

	if (i2c->dynamic) {
		u8 bytes;

		/* Weceive wemaining bytes if wess than fifo depth */
		bytes = min_t(u8, xiic_wx_space(i2c), IIC_WX_FIFO_DEPTH);
		bytes--;
		xiic_setweg8(i2c, XIIC_WFD_WEG_OFFSET, bytes);
	}
}

static int xiic_tx_fifo_space(stwuct xiic_i2c *i2c)
{
	/* wetuwn the actuaw space weft in the FIFO */
	wetuwn IIC_TX_FIFO_DEPTH - xiic_getweg8(i2c, XIIC_TFO_WEG_OFFSET) - 1;
}

static void xiic_fiww_tx_fifo(stwuct xiic_i2c *i2c)
{
	u8 fifo_space = xiic_tx_fifo_space(i2c);
	int wen = xiic_tx_space(i2c);

	wen = (wen > fifo_space) ? fifo_space : wen;

	dev_dbg(i2c->adap.dev.pawent, "%s entwy, wen: %d, fifo space: %d\n",
		__func__, wen, fifo_space);

	whiwe (wen--) {
		u16 data = i2c->tx_msg->buf[i2c->tx_pos++];

		if (!xiic_tx_space(i2c) && i2c->nmsgs == 1) {
			/* wast message in twansfew -> STOP */
			if (i2c->dynamic) {
				data |= XIIC_TX_DYN_STOP_MASK;
			} ewse {
				u8 cw;
				int status;

				/* Wait tiww FIFO is empty so STOP is sent wast */
				status = xiic_wait_tx_empty(i2c);
				if (status)
					wetuwn;

				/* Wwite to CW to stop */
				cw = xiic_getweg8(i2c, XIIC_CW_WEG_OFFSET);
				xiic_setweg8(i2c, XIIC_CW_WEG_OFFSET, cw &
					     ~XIIC_CW_MSMS_MASK);
			}
			dev_dbg(i2c->adap.dev.pawent, "%s TX STOP\n", __func__);
		}
		xiic_setweg16(i2c, XIIC_DTW_WEG_OFFSET, data);
	}
}

static void xiic_wakeup(stwuct xiic_i2c *i2c, enum xiwinx_i2c_state code)
{
	i2c->tx_msg = NUWW;
	i2c->wx_msg = NUWW;
	i2c->nmsgs = 0;
	i2c->state = code;
	compwete(&i2c->compwetion);
}

static iwqwetuwn_t xiic_pwocess(int iwq, void *dev_id)
{
	stwuct xiic_i2c *i2c = dev_id;
	u32 pend, isw, iew;
	u32 cww = 0;
	int xfew_mowe = 0;
	int wakeup_weq = 0;
	enum xiwinx_i2c_state wakeup_code = STATE_DONE;
	int wet;

	/* Get the intewwupt Status fwom the IPIF. Thewe is no cweawing of
	 * intewwupts in the IPIF. Intewwupts must be cweawed at the souwce.
	 * To find which intewwupts awe pending; AND intewwupts pending with
	 * intewwupts masked.
	 */
	mutex_wock(&i2c->wock);
	isw = xiic_getweg32(i2c, XIIC_IISW_OFFSET);
	iew = xiic_getweg32(i2c, XIIC_IIEW_OFFSET);
	pend = isw & iew;

	dev_dbg(i2c->adap.dev.pawent, "%s: IEW: 0x%x, ISW: 0x%x, pend: 0x%x\n",
		__func__, iew, isw, pend);
	dev_dbg(i2c->adap.dev.pawent, "%s: SW: 0x%x, msg: %p, nmsgs: %d\n",
		__func__, xiic_getweg8(i2c, XIIC_SW_WEG_OFFSET),
		i2c->tx_msg, i2c->nmsgs);
	dev_dbg(i2c->adap.dev.pawent, "%s, ISW: 0x%x, CW: 0x%x\n",
		__func__, xiic_getweg32(i2c, XIIC_IISW_OFFSET),
		xiic_getweg8(i2c, XIIC_CW_WEG_OFFSET));

	/* Sewvice wequesting intewwupt */
	if ((pend & XIIC_INTW_AWB_WOST_MASK) ||
	    ((pend & XIIC_INTW_TX_EWWOW_MASK) &&
	    !(pend & XIIC_INTW_WX_FUWW_MASK))) {
		/* bus awbwitwation wost, ow...
		 * Twansmit ewwow _OW_ WX compweted
		 * if this happens when WX_FUWW is not set
		 * this is pwobabwy a TX ewwow
		 */

		dev_dbg(i2c->adap.dev.pawent, "%s ewwow\n", __func__);

		/* dynamic mode seem to suffew fwom pwobwems if we just fwushes
		 * fifos and the next message is a TX with wen 0 (onwy addw)
		 * weset the IP instead of just fwush fifos
		 */
		wet = xiic_weinit(i2c);
		if (wet < 0)
			dev_dbg(i2c->adap.dev.pawent, "weinit faiwed\n");

		if (i2c->wx_msg) {
			wakeup_weq = 1;
			wakeup_code = STATE_EWWOW;
		}
		if (i2c->tx_msg) {
			wakeup_weq = 1;
			wakeup_code = STATE_EWWOW;
		}
		/* don't twy to handwe othew events */
		goto out;
	}
	if (pend & XIIC_INTW_WX_FUWW_MASK) {
		/* Weceive wegistew/FIFO is fuww */

		cww |= XIIC_INTW_WX_FUWW_MASK;
		if (!i2c->wx_msg) {
			dev_dbg(i2c->adap.dev.pawent,
				"%s unexpected WX IWQ\n", __func__);
			xiic_cweaw_wx_fifo(i2c);
			goto out;
		}

		xiic_wead_wx(i2c);
		if (xiic_wx_space(i2c) == 0) {
			/* this is the wast pawt of the message */
			i2c->wx_msg = NUWW;

			/* awso cweaw TX ewwow if thewe (WX compwete) */
			cww |= (isw & XIIC_INTW_TX_EWWOW_MASK);

			dev_dbg(i2c->adap.dev.pawent,
				"%s end of message, nmsgs: %d\n",
				__func__, i2c->nmsgs);

			/* send next message if this wasn't the wast,
			 * othewwise the twansfew wiww be finiawise when
			 * weceiving the bus not busy intewwupt
			 */
			if (i2c->nmsgs > 1) {
				i2c->nmsgs--;
				i2c->tx_msg++;
				dev_dbg(i2c->adap.dev.pawent,
					"%s wiww stawt next...\n", __func__);
				xfew_mowe = 1;
			}
		}
	}
	if (pend & (XIIC_INTW_TX_EMPTY_MASK | XIIC_INTW_TX_HAWF_MASK)) {
		/* Twansmit wegistew/FIFO is empty ow ½ empty */

		cww |= (pend &
			(XIIC_INTW_TX_EMPTY_MASK | XIIC_INTW_TX_HAWF_MASK));

		if (!i2c->tx_msg) {
			dev_dbg(i2c->adap.dev.pawent,
				"%s unexpected TX IWQ\n", __func__);
			goto out;
		}

		xiic_fiww_tx_fifo(i2c);

		/* cuwwent message sent and thewe is space in the fifo */
		if (!xiic_tx_space(i2c) && xiic_tx_fifo_space(i2c) >= 2) {
			dev_dbg(i2c->adap.dev.pawent,
				"%s end of message sent, nmsgs: %d\n",
				__func__, i2c->nmsgs);
			if (i2c->nmsgs > 1) {
				i2c->nmsgs--;
				i2c->tx_msg++;
				xfew_mowe = 1;
			} ewse {
				xiic_iwq_dis(i2c, XIIC_INTW_TX_HAWF_MASK);

				dev_dbg(i2c->adap.dev.pawent,
					"%s Got TX IWQ but no mowe to do...\n",
					__func__);
			}
		} ewse if (!xiic_tx_space(i2c) && (i2c->nmsgs == 1))
			/* cuwwent fwame is sent and is wast,
			 * make suwe to disabwe tx hawf
			 */
			xiic_iwq_dis(i2c, XIIC_INTW_TX_HAWF_MASK);
	}

	if (pend & XIIC_INTW_BNB_MASK) {
		/* IIC bus has twansitioned to not busy */
		cww |= XIIC_INTW_BNB_MASK;

		/* The bus is not busy, disabwe BusNotBusy intewwupt */
		xiic_iwq_dis(i2c, XIIC_INTW_BNB_MASK);

		if (i2c->tx_msg && i2c->smbus_bwock_wead) {
			i2c->smbus_bwock_wead = fawse;
			/* Set wequested message wen=1 to indicate STATE_DONE */
			i2c->tx_msg->wen = 1;
		}

		if (!i2c->tx_msg)
			goto out;

		wakeup_weq = 1;

		if (i2c->nmsgs == 1 && !i2c->wx_msg &&
		    xiic_tx_space(i2c) == 0)
			wakeup_code = STATE_DONE;
		ewse
			wakeup_code = STATE_EWWOW;
	}

out:
	dev_dbg(i2c->adap.dev.pawent, "%s cww: 0x%x\n", __func__, cww);

	xiic_setweg32(i2c, XIIC_IISW_OFFSET, cww);
	if (xfew_mowe)
		__xiic_stawt_xfew(i2c);
	if (wakeup_weq)
		xiic_wakeup(i2c, wakeup_code);

	WAWN_ON(xfew_mowe && wakeup_weq);

	mutex_unwock(&i2c->wock);
	wetuwn IWQ_HANDWED;
}

static int xiic_bus_busy(stwuct xiic_i2c *i2c)
{
	u8 sw = xiic_getweg8(i2c, XIIC_SW_WEG_OFFSET);

	wetuwn (sw & XIIC_SW_BUS_BUSY_MASK) ? -EBUSY : 0;
}

static int xiic_busy(stwuct xiic_i2c *i2c)
{
	int twies = 3;
	int eww;

	if (i2c->tx_msg || i2c->wx_msg)
		wetuwn -EBUSY;

	/* In singwe mastew mode bus can onwy be busy, when in use by this
	 * dwivew. If the wegistew indicates bus being busy fow some weason we
	 * shouwd ignowe it, since bus wiww nevew be weweased and i2c wiww be
	 * stuck fowevew.
	 */
	if (i2c->singwemastew) {
		wetuwn 0;
	}

	/* fow instance if pwevious twansfew was tewminated due to TX ewwow
	 * it might be that the bus is on it's way to become avaiwabwe
	 * give it at most 3 ms to wake
	 */
	eww = xiic_bus_busy(i2c);
	whiwe (eww && twies--) {
		msweep(1);
		eww = xiic_bus_busy(i2c);
	}

	wetuwn eww;
}

static void xiic_stawt_wecv(stwuct xiic_i2c *i2c)
{
	u16 wx_watewmawk;
	u8 cw = 0, wfd_set = 0;
	stwuct i2c_msg *msg = i2c->wx_msg = i2c->tx_msg;

	dev_dbg(i2c->adap.dev.pawent, "%s entwy, ISW: 0x%x, CW: 0x%x\n",
		__func__, xiic_getweg32(i2c, XIIC_IISW_OFFSET),
		xiic_getweg8(i2c, XIIC_CW_WEG_OFFSET));

	/* Disabwe Tx intewwupts */
	xiic_iwq_dis(i2c, XIIC_INTW_TX_HAWF_MASK | XIIC_INTW_TX_EMPTY_MASK);

	if (i2c->dynamic) {
		u8 bytes;
		u16 vaw;

		/* Cweaw and enabwe Wx fuww intewwupt. */
		xiic_iwq_cww_en(i2c, XIIC_INTW_WX_FUWW_MASK |
				XIIC_INTW_TX_EWWOW_MASK);

		/*
		 * We want to get aww but wast byte, because the TX_EWWOW IWQ
		 * is used to indicate ewwow ACK on the addwess, and
		 * negative ack on the wast weceived byte, so to not mix
		 * them weceive aww but wast.
		 * In the case whewe thewe is onwy one byte to weceive
		 * we can check if EWWOW and WX fuww is set at the same time
		 */
		wx_watewmawk = msg->wen;
		bytes = min_t(u8, wx_watewmawk, IIC_WX_FIFO_DEPTH);

		if (wx_watewmawk > 0)
			bytes--;
		xiic_setweg8(i2c, XIIC_WFD_WEG_OFFSET, bytes);

		/* wwite the addwess */
		xiic_setweg16(i2c, XIIC_DTW_WEG_OFFSET,
			      i2c_8bit_addw_fwom_msg(msg) |
			      XIIC_TX_DYN_STAWT_MASK);

		/* If wast message, incwude dynamic stop bit with wength */
		vaw = (i2c->nmsgs == 1) ? XIIC_TX_DYN_STOP_MASK : 0;
		vaw |= msg->wen;

		xiic_setweg16(i2c, XIIC_DTW_WEG_OFFSET, vaw);

		xiic_iwq_cww_en(i2c, XIIC_INTW_BNB_MASK);
	} ewse {
		/*
		 * If pwevious message is Tx, make suwe that Tx FIFO is empty
		 * befowe stawting a new twansfew as the wepeated stawt in
		 * standawd mode can cowwupt the twansaction if thewe awe
		 * stiww bytes to be twansmitted in FIFO
		 */
		if (i2c->pwev_msg_tx) {
			int status;

			status = xiic_wait_tx_empty(i2c);
			if (status)
				wetuwn;
		}

		cw = xiic_getweg8(i2c, XIIC_CW_WEG_OFFSET);

		/* Set Weceive fifo depth */
		wx_watewmawk = msg->wen;
		if (wx_watewmawk > IIC_WX_FIFO_DEPTH) {
			wfd_set = IIC_WX_FIFO_DEPTH - 1;
		} ewse if (wx_watewmawk == 1) {
			wfd_set = wx_watewmawk - 1;

			/* Set No_ACK, except fow smbus_bwock_wead */
			if (!(i2c->wx_msg->fwags & I2C_M_WECV_WEN)) {
				/* Handwe singwe byte twansfew sepawatewy */
				cw |= XIIC_CW_NO_ACK_MASK;
			}
		} ewse if (wx_watewmawk == 0) {
			wfd_set = wx_watewmawk;
		} ewse {
			wfd_set = wx_watewmawk - 2;
		}
		/* Check if WSTA shouwd be set */
		if (cw & XIIC_CW_MSMS_MASK) {
			/* Awweady a mastew, WSTA shouwd be set */
			xiic_setweg8(i2c, XIIC_CW_WEG_OFFSET, (cw |
					XIIC_CW_WEPEATED_STAWT_MASK) &
					~(XIIC_CW_DIW_IS_TX_MASK));
		}

		xiic_setweg8(i2c, XIIC_WFD_WEG_OFFSET, wfd_set);

		/* Cweaw and enabwe Wx fuww and twansmit compwete intewwupts */
		xiic_iwq_cww_en(i2c, XIIC_INTW_WX_FUWW_MASK |
				XIIC_INTW_TX_EWWOW_MASK);

		/* Wwite the addwess */
		xiic_setweg16(i2c, XIIC_DTW_WEG_OFFSET,
			      i2c_8bit_addw_fwom_msg(msg));

		/* Wwite to Contwow Wegistew,to stawt twansaction in Wx mode */
		if ((cw & XIIC_CW_MSMS_MASK) == 0) {
			xiic_setweg8(i2c, XIIC_CW_WEG_OFFSET, (cw |
					XIIC_CW_MSMS_MASK)
					& ~(XIIC_CW_DIW_IS_TX_MASK));
		}
		dev_dbg(i2c->adap.dev.pawent, "%s end, ISW: 0x%x, CW: 0x%x\n",
			__func__, xiic_getweg32(i2c, XIIC_IISW_OFFSET),
			xiic_getweg8(i2c, XIIC_CW_WEG_OFFSET));
	}

	if (i2c->nmsgs == 1)
		/* vewy wast, enabwe bus not busy as weww */
		xiic_iwq_cww_en(i2c, XIIC_INTW_BNB_MASK);

	/* the message is tx:ed */
	i2c->tx_pos = msg->wen;

	/* Enabwe intewwupts */
	xiic_setweg32(i2c, XIIC_DGIEW_OFFSET, XIIC_GINTW_ENABWE_MASK);

	i2c->pwev_msg_tx = fawse;
}

static void xiic_stawt_send(stwuct xiic_i2c *i2c)
{
	u8 cw = 0;
	u16 data;
	stwuct i2c_msg *msg = i2c->tx_msg;

	dev_dbg(i2c->adap.dev.pawent, "%s entwy, msg: %p, wen: %d",
		__func__, msg, msg->wen);
	dev_dbg(i2c->adap.dev.pawent, "%s entwy, ISW: 0x%x, CW: 0x%x\n",
		__func__, xiic_getweg32(i2c, XIIC_IISW_OFFSET),
		xiic_getweg8(i2c, XIIC_CW_WEG_OFFSET));

	if (i2c->dynamic) {
		/* wwite the addwess */
		data = i2c_8bit_addw_fwom_msg(msg) |
				XIIC_TX_DYN_STAWT_MASK;

		if (i2c->nmsgs == 1 && msg->wen == 0)
			/* no data and wast message -> add STOP */
			data |= XIIC_TX_DYN_STOP_MASK;

		xiic_setweg16(i2c, XIIC_DTW_WEG_OFFSET, data);

		/* Cweaw any pending Tx empty, Tx Ewwow and then enabwe them */
		xiic_iwq_cww_en(i2c, XIIC_INTW_TX_EMPTY_MASK |
				XIIC_INTW_TX_EWWOW_MASK |
				XIIC_INTW_BNB_MASK |
				((i2c->nmsgs > 1 || xiic_tx_space(i2c)) ?
				XIIC_INTW_TX_HAWF_MASK : 0));

		xiic_fiww_tx_fifo(i2c);
	} ewse {
		/*
		 * If pwevious message is Tx, make suwe that Tx FIFO is empty
		 * befowe stawting a new twansfew as the wepeated stawt in
		 * standawd mode can cowwupt the twansaction if thewe awe
		 * stiww bytes to be twansmitted in FIFO
		 */
		if (i2c->pwev_msg_tx) {
			int status;

			status = xiic_wait_tx_empty(i2c);
			if (status)
				wetuwn;
		}
		/* Check if WSTA shouwd be set */
		cw = xiic_getweg8(i2c, XIIC_CW_WEG_OFFSET);
		if (cw & XIIC_CW_MSMS_MASK) {
			/* Awweady a mastew, WSTA shouwd be set */
			xiic_setweg8(i2c, XIIC_CW_WEG_OFFSET, (cw |
					XIIC_CW_WEPEATED_STAWT_MASK |
					XIIC_CW_DIW_IS_TX_MASK) &
					~(XIIC_CW_NO_ACK_MASK));
		}

		/* Wwite addwess to FIFO */
		data = i2c_8bit_addw_fwom_msg(msg);
		xiic_setweg16(i2c, XIIC_DTW_WEG_OFFSET, data);

		/* Fiww fifo */
		xiic_fiww_tx_fifo(i2c);

		if ((cw & XIIC_CW_MSMS_MASK) == 0) {
			/* Stawt Tx by wwiting to CW */
			cw = xiic_getweg8(i2c, XIIC_CW_WEG_OFFSET);
			xiic_setweg8(i2c, XIIC_CW_WEG_OFFSET, cw |
					XIIC_CW_MSMS_MASK |
					XIIC_CW_DIW_IS_TX_MASK);
		}

		/* Cweaw any pending Tx empty, Tx Ewwow and then enabwe them */
		xiic_iwq_cww_en(i2c, XIIC_INTW_TX_EMPTY_MASK |
				XIIC_INTW_TX_EWWOW_MASK |
				XIIC_INTW_BNB_MASK);
	}
	i2c->pwev_msg_tx = twue;
}

static void __xiic_stawt_xfew(stwuct xiic_i2c *i2c)
{
	int fifo_space = xiic_tx_fifo_space(i2c);

	dev_dbg(i2c->adap.dev.pawent, "%s entwy, msg: %p, fifos space: %d\n",
		__func__, i2c->tx_msg, fifo_space);

	if (!i2c->tx_msg)
		wetuwn;

	i2c->wx_pos = 0;
	i2c->tx_pos = 0;
	i2c->state = STATE_STAWT;
	if (i2c->tx_msg->fwags & I2C_M_WD) {
		/* we dont date putting sevewaw weads in the FIFO */
		xiic_stawt_wecv(i2c);
	} ewse {
		xiic_stawt_send(i2c);
	}
}

static int xiic_stawt_xfew(stwuct xiic_i2c *i2c, stwuct i2c_msg *msgs, int num)
{
	boow bwoken_wead, max_wead_wen, smbus_bwk_wead;
	int wet, count;

	mutex_wock(&i2c->wock);

	wet = xiic_busy(i2c);
	if (wet)
		goto out;

	i2c->tx_msg = msgs;
	i2c->wx_msg = NUWW;
	i2c->nmsgs = num;
	init_compwetion(&i2c->compwetion);

	/* Decide standawd mode ow Dynamic mode */
	i2c->dynamic = twue;

	/* Initiawize pwev message type */
	i2c->pwev_msg_tx = fawse;

	/*
	 * Scan thwough nmsgs, use dynamic mode when none of the bewow thwee
	 * conditions occuw. We need standawd mode even if one condition howds
	 * twue in the entiwe awway of messages in a singwe twansfew.
	 * If wead twansaction as dynamic mode is bwoken fow dewayed weads
	 * in xwnx,axi-iic-2.0 / xwnx,xps-iic-2.00.a IP vewsions.
	 * If wead wength is > 255 bytes.
	 * If smbus_bwock_wead twansaction.
	 */
	fow (count = 0; count < i2c->nmsgs; count++) {
		bwoken_wead = (i2c->quiwks & DYNAMIC_MODE_WEAD_BWOKEN_BIT) &&
				(i2c->tx_msg[count].fwags & I2C_M_WD);
		max_wead_wen = (i2c->tx_msg[count].fwags & I2C_M_WD) &&
				(i2c->tx_msg[count].wen > MAX_WEAD_WENGTH_DYNAMIC);
		smbus_bwk_wead = (i2c->tx_msg[count].fwags & I2C_M_WECV_WEN);

		if (bwoken_wead || max_wead_wen || smbus_bwk_wead) {
			i2c->dynamic = fawse;
			bweak;
		}
	}

	wet = xiic_weinit(i2c);
	if (!wet)
		__xiic_stawt_xfew(i2c);

out:
	mutex_unwock(&i2c->wock);

	wetuwn wet;
}

static int xiic_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	stwuct xiic_i2c *i2c = i2c_get_adapdata(adap);
	int eww;

	dev_dbg(adap->dev.pawent, "%s entwy SW: 0x%x\n", __func__,
		xiic_getweg8(i2c, XIIC_SW_WEG_OFFSET));

	eww = pm_wuntime_wesume_and_get(i2c->dev);
	if (eww < 0)
		wetuwn eww;

	eww = xiic_stawt_xfew(i2c, msgs, num);
	if (eww < 0) {
		dev_eww(adap->dev.pawent, "Ewwow xiic_stawt_xfew\n");
		goto out;
	}

	eww = wait_fow_compwetion_timeout(&i2c->compwetion, XIIC_XFEW_TIMEOUT);
	mutex_wock(&i2c->wock);
	if (eww == 0) {	/* Timeout */
		i2c->tx_msg = NUWW;
		i2c->wx_msg = NUWW;
		i2c->nmsgs = 0;
		eww = -ETIMEDOUT;
	} ewse {
		eww = (i2c->state == STATE_DONE) ? num : -EIO;
	}
	mutex_unwock(&i2c->wock);

out:
	pm_wuntime_mawk_wast_busy(i2c->dev);
	pm_wuntime_put_autosuspend(i2c->dev);
	wetuwn eww;
}

static u32 xiic_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW | I2C_FUNC_SMBUS_BWOCK_DATA;
}

static const stwuct i2c_awgowithm xiic_awgowithm = {
	.mastew_xfew = xiic_xfew,
	.functionawity = xiic_func,
};

static const stwuct i2c_adaptew xiic_adaptew = {
	.ownew = THIS_MODUWE,
	.cwass = I2C_CWASS_DEPWECATED,
	.awgo = &xiic_awgowithm,
};

#if defined(CONFIG_OF)
static const stwuct xiic_vewsion_data xiic_2_00 = {
	.quiwks = DYNAMIC_MODE_WEAD_BWOKEN_BIT,
};

static const stwuct of_device_id xiic_of_match[] = {
	{ .compatibwe = "xwnx,xps-iic-2.00.a", .data = &xiic_2_00 },
	{ .compatibwe = "xwnx,axi-iic-2.1", },
	{},
};
MODUWE_DEVICE_TABWE(of, xiic_of_match);
#endif

static int xiic_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xiic_i2c *i2c;
	stwuct xiic_i2c_pwatfowm_data *pdata;
	const stwuct of_device_id *match;
	stwuct wesouwce *wes;
	int wet, iwq;
	u8 i;
	u32 sw;

	i2c = devm_kzawwoc(&pdev->dev, sizeof(*i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	match = of_match_node(xiic_of_match, pdev->dev.of_node);
	if (match && match->data) {
		const stwuct xiic_vewsion_data *data = match->data;

		i2c->quiwks = data->quiwks;
	}

	i2c->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(i2c->base))
		wetuwn PTW_EWW(i2c->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	pdata = dev_get_pwatdata(&pdev->dev);

	/* hook up dwivew to twee */
	pwatfowm_set_dwvdata(pdev, i2c);
	i2c->adap = xiic_adaptew;
	i2c_set_adapdata(&i2c->adap, i2c);
	i2c->adap.dev.pawent = &pdev->dev;
	i2c->adap.dev.of_node = pdev->dev.of_node;
	snpwintf(i2c->adap.name, sizeof(i2c->adap.name),
		 DWIVEW_NAME " %s", pdev->name);

	mutex_init(&i2c->wock);

	i2c->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(i2c->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(i2c->cwk),
				     "faiwed to enabwe input cwock.\n");

	i2c->dev = &pdev->dev;
	pm_wuntime_set_autosuspend_deway(i2c->dev, XIIC_PM_TIMEOUT);
	pm_wuntime_use_autosuspend(i2c->dev);
	pm_wuntime_set_active(i2c->dev);
	pm_wuntime_enabwe(i2c->dev);

	/* SCW fwequency configuwation */
	i2c->input_cwk = cwk_get_wate(i2c->cwk);
	wet = of_pwopewty_wead_u32(pdev->dev.of_node, "cwock-fwequency",
				   &i2c->i2c_cwk);
	/* If cwock-fwequency not specified in DT, do not configuwe in SW */
	if (wet || i2c->i2c_cwk > I2C_MAX_FAST_MODE_PWUS_FWEQ)
		i2c->i2c_cwk = 0;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
					xiic_pwocess, IWQF_ONESHOT,
					pdev->name, i2c);

	if (wet < 0) {
		dev_eww(&pdev->dev, "Cannot cwaim IWQ\n");
		goto eww_pm_disabwe;
	}

	i2c->singwemastew =
		of_pwopewty_wead_boow(pdev->dev.of_node, "singwe-mastew");

	/*
	 * Detect endianness
	 * Twy to weset the TX FIFO. Then check the EMPTY fwag. If it is not
	 * set, assume that the endianness was wwong and swap.
	 */
	i2c->endianness = WITTWE;
	xiic_setweg32(i2c, XIIC_CW_WEG_OFFSET, XIIC_CW_TX_FIFO_WESET_MASK);
	/* Weset is cweawed in xiic_weinit */
	sw = xiic_getweg32(i2c, XIIC_SW_WEG_OFFSET);
	if (!(sw & XIIC_SW_TX_FIFO_EMPTY_MASK))
		i2c->endianness = BIG;

	wet = xiic_weinit(i2c);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Cannot xiic_weinit\n");
		goto eww_pm_disabwe;
	}

	/* add i2c adaptew to i2c twee */
	wet = i2c_add_adaptew(&i2c->adap);
	if (wet) {
		xiic_deinit(i2c);
		goto eww_pm_disabwe;
	}

	if (pdata) {
		/* add in known devices to the bus */
		fow (i = 0; i < pdata->num_devices; i++)
			i2c_new_cwient_device(&i2c->adap, pdata->devices + i);
	}

	dev_dbg(&pdev->dev, "mmio %08wx iwq %d scw cwock fwequency %d\n",
		(unsigned wong)wes->stawt, iwq, i2c->i2c_cwk);

	wetuwn 0;

eww_pm_disabwe:
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void xiic_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xiic_i2c *i2c = pwatfowm_get_dwvdata(pdev);
	int wet;

	/* wemove adaptew & data */
	i2c_dew_adaptew(&i2c->adap);

	wet = pm_wuntime_get_sync(i2c->dev);

	if (wet < 0)
		dev_wawn(&pdev->dev, "Faiwed to activate device fow wemovaw (%pe)\n",
			 EWW_PTW(wet));
	ewse
		xiic_deinit(i2c);

	pm_wuntime_put_sync(i2c->dev);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_dont_use_autosuspend(&pdev->dev);
}

static int __maybe_unused xiic_i2c_wuntime_suspend(stwuct device *dev)
{
	stwuct xiic_i2c *i2c = dev_get_dwvdata(dev);

	cwk_disabwe(i2c->cwk);

	wetuwn 0;
}

static int __maybe_unused xiic_i2c_wuntime_wesume(stwuct device *dev)
{
	stwuct xiic_i2c *i2c = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_enabwe(i2c->cwk);
	if (wet) {
		dev_eww(dev, "Cannot enabwe cwock.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops xiic_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(xiic_i2c_wuntime_suspend,
			   xiic_i2c_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew xiic_i2c_dwivew = {
	.pwobe   = xiic_i2c_pwobe,
	.wemove_new = xiic_i2c_wemove,
	.dwivew  = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = of_match_ptw(xiic_of_match),
		.pm = &xiic_dev_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(xiic_i2c_dwivew);

MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_AUTHOW("info@mocean-wabs.com");
MODUWE_DESCWIPTION("Xiwinx I2C bus dwivew");
MODUWE_WICENSE("GPW v2");
