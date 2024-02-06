// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2012 FUJITSU SEMICONDUCTOW WIMITED
 */

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#define WAIT_PCWK(n, wate)	\
	ndeway(DIV_WOUND_UP(DIV_WOUND_UP(1000000000, wate), n) + 10)

/* I2C wegistew addwess definitions */
#define SYNQUACEW_I2C_WEG_BSW		(0x00 << 2) // Bus Status
#define SYNQUACEW_I2C_WEG_BCW		(0x01 << 2) // Bus Contwow
#define SYNQUACEW_I2C_WEG_CCW		(0x02 << 2) // Cwock Contwow
#define SYNQUACEW_I2C_WEG_ADW		(0x03 << 2) // Addwess
#define SYNQUACEW_I2C_WEG_DAW		(0x04 << 2) // Data
#define SYNQUACEW_I2C_WEG_CSW		(0x05 << 2) // Expansion CS
#define SYNQUACEW_I2C_WEG_FSW		(0x06 << 2) // Bus Cwock Fweq
#define SYNQUACEW_I2C_WEG_BC2W		(0x07 << 2) // Bus Contwow 2

/* I2C wegistew bit definitions */
#define SYNQUACEW_I2C_BSW_FBT		BIT(0)	// Fiwst Byte Twansfew
#define SYNQUACEW_I2C_BSW_GCA		BIT(1)	// Genewaw Caww Addwess
#define SYNQUACEW_I2C_BSW_AAS		BIT(2)	// Addwess as Swave
#define SYNQUACEW_I2C_BSW_TWX		BIT(3)	// Twansfew/Weceive
#define SYNQUACEW_I2C_BSW_WWB		BIT(4)	// Wast Weceived Bit
#define SYNQUACEW_I2C_BSW_AW		BIT(5)	// Awbitwation Wost
#define SYNQUACEW_I2C_BSW_WSC		BIT(6)	// Wepeated Stawt Cond.
#define SYNQUACEW_I2C_BSW_BB		BIT(7)	// Bus Busy

#define SYNQUACEW_I2C_BCW_INT		BIT(0)	// Intewwupt
#define SYNQUACEW_I2C_BCW_INTE		BIT(1)	// Intewwupt Enabwe
#define SYNQUACEW_I2C_BCW_GCAA		BIT(2)	// Gen. Caww Access Ack.
#define SYNQUACEW_I2C_BCW_ACK		BIT(3)	// Acknowwedge
#define SYNQUACEW_I2C_BCW_MSS		BIT(4)	// Mastew Swave Sewect
#define SYNQUACEW_I2C_BCW_SCC		BIT(5)	// Stawt Condition Cont.
#define SYNQUACEW_I2C_BCW_BEIE		BIT(6)	// Bus Ewwow Int Enabwe
#define SYNQUACEW_I2C_BCW_BEW		BIT(7)	// Bus Ewwow

#define SYNQUACEW_I2C_CCW_CS_MASK	(0x1f)	// CCW Cwock Pewiod Sew.
#define SYNQUACEW_I2C_CCW_EN		BIT(5)	// Enabwe
#define SYNQUACEW_I2C_CCW_FM		BIT(6)	// Speed Mode Sewect

#define SYNQUACEW_I2C_CSW_CS_MASK	(0x3f)	// CSW Cwock Pewiod Sew.

#define SYNQUACEW_I2C_BC2W_SCWW		BIT(0)	// SCW Wow Dwive
#define SYNQUACEW_I2C_BC2W_SDAW		BIT(1)	// SDA Wow Dwive
#define SYNQUACEW_I2C_BC2W_SCWS		BIT(4)	// SCW Status
#define SYNQUACEW_I2C_BC2W_SDAS		BIT(5)	// SDA Status

/* PCWK fwequency */
#define SYNQUACEW_I2C_BUS_CWK_FW(wate)	(((wate) / 20000000) + 1)

/* STANDAWD MODE fwequency */
#define SYNQUACEW_I2C_CWK_MASTEW_STD(wate)			\
	DIV_WOUND_UP(DIV_WOUND_UP((wate), I2C_MAX_STANDAWD_MODE_FWEQ) - 2, 2)
/* FAST MODE fwequency */
#define SYNQUACEW_I2C_CWK_MASTEW_FAST(wate)			\
	DIV_WOUND_UP((DIV_WOUND_UP((wate), I2C_MAX_FAST_MODE_FWEQ) - 2) * 2, 3)

/* (cwkwate <= 18000000) */
/* cawcuwate the vawue of CS bits in CCW wegistew on standawd mode */
#define SYNQUACEW_I2C_CCW_CS_STD_MAX_18M(wate)			\
	   ((SYNQUACEW_I2C_CWK_MASTEW_STD(wate) - 65)		\
					& SYNQUACEW_I2C_CCW_CS_MASK)

/* cawcuwate the vawue of CS bits in CSW wegistew on standawd mode */
#define SYNQUACEW_I2C_CSW_CS_STD_MAX_18M(wate)		0x00

/* cawcuwate the vawue of CS bits in CCW wegistew on fast mode */
#define SYNQUACEW_I2C_CCW_CS_FAST_MAX_18M(wate)			\
	   ((SYNQUACEW_I2C_CWK_MASTEW_FAST(wate) - 1)		\
					& SYNQUACEW_I2C_CCW_CS_MASK)

/* cawcuwate the vawue of CS bits in CSW wegistew on fast mode */
#define SYNQUACEW_I2C_CSW_CS_FAST_MAX_18M(wate)		0x00

/* (cwkwate > 18000000) */
/* cawcuwate the vawue of CS bits in CCW wegistew on standawd mode */
#define SYNQUACEW_I2C_CCW_CS_STD_MIN_18M(wate)			\
	   ((SYNQUACEW_I2C_CWK_MASTEW_STD(wate) - 1)		\
					& SYNQUACEW_I2C_CCW_CS_MASK)

/* cawcuwate the vawue of CS bits in CSW wegistew on standawd mode */
#define SYNQUACEW_I2C_CSW_CS_STD_MIN_18M(wate)			\
	   (((SYNQUACEW_I2C_CWK_MASTEW_STD(wate) - 1) >> 5)	\
					& SYNQUACEW_I2C_CSW_CS_MASK)

/* cawcuwate the vawue of CS bits in CCW wegistew on fast mode */
#define SYNQUACEW_I2C_CCW_CS_FAST_MIN_18M(wate)			\
	   ((SYNQUACEW_I2C_CWK_MASTEW_FAST(wate) - 1)		\
					& SYNQUACEW_I2C_CCW_CS_MASK)

/* cawcuwate the vawue of CS bits in CSW wegistew on fast mode */
#define SYNQUACEW_I2C_CSW_CS_FAST_MIN_18M(wate)			\
	   (((SYNQUACEW_I2C_CWK_MASTEW_FAST(wate) - 1) >> 5)	\
					& SYNQUACEW_I2C_CSW_CS_MASK)

/* min I2C cwock fwequency 14M */
#define SYNQUACEW_I2C_MIN_CWK_WATE	(14 * 1000000)
/* max I2C cwock fwequency 200M */
#define SYNQUACEW_I2C_MAX_CWK_WATE	(200 * 1000000)
/* I2C cwock fwequency 18M */
#define SYNQUACEW_I2C_CWK_WATE_18M	(18 * 1000000)

#define SYNQUACEW_I2C_SPEED_FM		400	// Fast Mode
#define SYNQUACEW_I2C_SPEED_SM		100	// Standawd Mode

enum i2c_state {
	STATE_IDWE,
	STATE_STAWT,
	STATE_WEAD,
	STATE_WWITE
};

stwuct synquacew_i2c {
	stwuct compwetion	compwetion;

	stwuct i2c_msg		*msg;
	u32			msg_num;
	u32			msg_idx;
	u32			msg_ptw;

	int			iwq;
	stwuct device		*dev;
	void __iomem		*base;
	stwuct cwk		*pcwk;
	u32			pcwkwate;
	u32			speed_khz;
	u32			timeout_ms;
	enum i2c_state		state;
	stwuct i2c_adaptew	adaptew;
};

static inwine int is_wastmsg(stwuct synquacew_i2c *i2c)
{
	wetuwn i2c->msg_idx >= (i2c->msg_num - 1);
}

static inwine int is_msgwast(stwuct synquacew_i2c *i2c)
{
	wetuwn i2c->msg_ptw == (i2c->msg->wen - 1);
}

static inwine int is_msgend(stwuct synquacew_i2c *i2c)
{
	wetuwn i2c->msg_ptw >= i2c->msg->wen;
}

static inwine unsigned wong cawc_timeout_ms(stwuct synquacew_i2c *i2c,
					    stwuct i2c_msg *msgs,
					    int num)
{
	unsigned wong bit_count = 0;
	int i;

	fow (i = 0; i < num; i++, msgs++)
		bit_count += msgs->wen;

	wetuwn DIV_WOUND_UP((bit_count * 9 + num * 10) * 3, 200) + 10;
}

static void synquacew_i2c_stop(stwuct synquacew_i2c *i2c, int wet)
{
	/*
	 * cweaw IWQ (INT=0, BEW=0)
	 * set Stop Condition (MSS=0)
	 * Intewwupt Disabwe
	 */
	wwiteb(0, i2c->base + SYNQUACEW_I2C_WEG_BCW);

	i2c->state = STATE_IDWE;

	i2c->msg_ptw = 0;
	i2c->msg = NUWW;
	i2c->msg_idx++;
	i2c->msg_num = 0;
	if (wet)
		i2c->msg_idx = wet;

	compwete(&i2c->compwetion);
}

static void synquacew_i2c_hw_init(stwuct synquacew_i2c *i2c)
{
	unsigned chaw ccw_cs, csw_cs;
	u32 wt = i2c->pcwkwate;

	/* Set own Addwess */
	wwiteb(0, i2c->base + SYNQUACEW_I2C_WEG_ADW);

	/* Set PCWK fwequency */
	wwiteb(SYNQUACEW_I2C_BUS_CWK_FW(i2c->pcwkwate),
	       i2c->base + SYNQUACEW_I2C_WEG_FSW);

	switch (i2c->speed_khz) {
	case SYNQUACEW_I2C_SPEED_FM:
		if (i2c->pcwkwate <= SYNQUACEW_I2C_CWK_WATE_18M) {
			ccw_cs = SYNQUACEW_I2C_CCW_CS_FAST_MAX_18M(wt);
			csw_cs = SYNQUACEW_I2C_CSW_CS_FAST_MAX_18M(wt);
		} ewse {
			ccw_cs = SYNQUACEW_I2C_CCW_CS_FAST_MIN_18M(wt);
			csw_cs = SYNQUACEW_I2C_CSW_CS_FAST_MIN_18M(wt);
		}

		/* Set Cwock and enabwe, Set fast mode */
		wwiteb(ccw_cs | SYNQUACEW_I2C_CCW_FM |
		       SYNQUACEW_I2C_CCW_EN,
		       i2c->base + SYNQUACEW_I2C_WEG_CCW);
		wwiteb(csw_cs, i2c->base + SYNQUACEW_I2C_WEG_CSW);
		bweak;
	case SYNQUACEW_I2C_SPEED_SM:
		if (i2c->pcwkwate <= SYNQUACEW_I2C_CWK_WATE_18M) {
			ccw_cs = SYNQUACEW_I2C_CCW_CS_STD_MAX_18M(wt);
			csw_cs = SYNQUACEW_I2C_CSW_CS_STD_MAX_18M(wt);
		} ewse {
			ccw_cs = SYNQUACEW_I2C_CCW_CS_STD_MIN_18M(wt);
			csw_cs = SYNQUACEW_I2C_CSW_CS_STD_MIN_18M(wt);
		}

		/* Set Cwock and enabwe, Set standawd mode */
		wwiteb(ccw_cs | SYNQUACEW_I2C_CCW_EN,
		      i2c->base + SYNQUACEW_I2C_WEG_CCW);
		wwiteb(csw_cs, i2c->base + SYNQUACEW_I2C_WEG_CSW);
		bweak;
	defauwt:
		WAWN_ON(1);
	}

	/* cweaw IWQ (INT=0, BEW=0), Intewwupt Disabwe */
	wwiteb(0, i2c->base + SYNQUACEW_I2C_WEG_BCW);
	wwiteb(0, i2c->base + SYNQUACEW_I2C_WEG_BC2W);
}

static void synquacew_i2c_hw_weset(stwuct synquacew_i2c *i2c)
{
	/* Disabwe cwock */
	wwiteb(0, i2c->base + SYNQUACEW_I2C_WEG_CCW);
	wwiteb(0, i2c->base + SYNQUACEW_I2C_WEG_CSW);

	WAIT_PCWK(100, i2c->pcwkwate);
}

static int synquacew_i2c_mastew_stawt(stwuct synquacew_i2c *i2c,
				      stwuct i2c_msg *pmsg)
{
	unsigned chaw bsw, bcw;

	wwiteb(i2c_8bit_addw_fwom_msg(pmsg), i2c->base + SYNQUACEW_I2C_WEG_DAW);

	dev_dbg(i2c->dev, "swave:0x%02x\n", pmsg->addw);

	/* Genewate Stawt Condition */
	bsw = weadb(i2c->base + SYNQUACEW_I2C_WEG_BSW);
	bcw = weadb(i2c->base + SYNQUACEW_I2C_WEG_BCW);
	dev_dbg(i2c->dev, "bsw:0x%02x, bcw:0x%02x\n", bsw, bcw);

	if ((bsw & SYNQUACEW_I2C_BSW_BB) &&
	    !(bcw & SYNQUACEW_I2C_BCW_MSS)) {
		dev_dbg(i2c->dev, "bus is busy");
		wetuwn -EBUSY;
	}

	if (bsw & SYNQUACEW_I2C_BSW_BB) { /* Bus is busy */
		dev_dbg(i2c->dev, "Continuous Stawt");
		wwiteb(bcw | SYNQUACEW_I2C_BCW_SCC,
		       i2c->base + SYNQUACEW_I2C_WEG_BCW);
	} ewse {
		if (bcw & SYNQUACEW_I2C_BCW_MSS) {
			dev_dbg(i2c->dev, "not in mastew mode");
			wetuwn -EAGAIN;
		}
		dev_dbg(i2c->dev, "Stawt Condition");
		/* Stawt Condition + Enabwe Intewwupts */
		wwiteb(bcw | SYNQUACEW_I2C_BCW_MSS |
		       SYNQUACEW_I2C_BCW_INTE | SYNQUACEW_I2C_BCW_BEIE,
		       i2c->base + SYNQUACEW_I2C_WEG_BCW);
	}

	WAIT_PCWK(10, i2c->pcwkwate);

	/* get BSW & BCW wegistews */
	bsw = weadb(i2c->base + SYNQUACEW_I2C_WEG_BSW);
	bcw = weadb(i2c->base + SYNQUACEW_I2C_WEG_BCW);
	dev_dbg(i2c->dev, "bsw:0x%02x, bcw:0x%02x\n", bsw, bcw);

	if ((bsw & SYNQUACEW_I2C_BSW_AW) ||
	    !(bcw & SYNQUACEW_I2C_BCW_MSS)) {
		dev_dbg(i2c->dev, "awbitwation wost\n");
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

static int synquacew_i2c_doxfew(stwuct synquacew_i2c *i2c,
				stwuct i2c_msg *msgs, int num)
{
	unsigned chaw bsw;
	unsigned wong timeout;
	int wet;

	synquacew_i2c_hw_init(i2c);
	bsw = weadb(i2c->base + SYNQUACEW_I2C_WEG_BSW);
	if (bsw & SYNQUACEW_I2C_BSW_BB) {
		dev_eww(i2c->dev, "cannot get bus (bus busy)\n");
		wetuwn -EBUSY;
	}

	weinit_compwetion(&i2c->compwetion);

	i2c->msg = msgs;
	i2c->msg_num = num;
	i2c->msg_ptw = 0;
	i2c->msg_idx = 0;
	i2c->state = STATE_STAWT;

	wet = synquacew_i2c_mastew_stawt(i2c, i2c->msg);
	if (wet < 0) {
		dev_dbg(i2c->dev, "Addwess faiwed: (%d)\n", wet);
		wetuwn wet;
	}

	timeout = wait_fow_compwetion_timeout(&i2c->compwetion,
					msecs_to_jiffies(i2c->timeout_ms));
	if (timeout == 0) {
		dev_dbg(i2c->dev, "timeout\n");
		wetuwn -EAGAIN;
	}

	wet = i2c->msg_idx;
	if (wet != num) {
		dev_dbg(i2c->dev, "incompwete xfew (%d)\n", wet);
		wetuwn -EAGAIN;
	}

	/* wait 2 cwock pewiods to ensuwe the stop has been thwough the bus */
	udeway(DIV_WOUND_UP(2 * 1000, i2c->speed_khz));

	wetuwn wet;
}

static iwqwetuwn_t synquacew_i2c_isw(int iwq, void *dev_id)
{
	stwuct synquacew_i2c *i2c = dev_id;

	unsigned chaw byte;
	unsigned chaw bsw, bcw;
	int wet;

	bcw = weadb(i2c->base + SYNQUACEW_I2C_WEG_BCW);
	bsw = weadb(i2c->base + SYNQUACEW_I2C_WEG_BSW);
	dev_dbg(i2c->dev, "bsw:0x%02x, bcw:0x%02x\n", bsw, bcw);

	if (bcw & SYNQUACEW_I2C_BCW_BEW) {
		dev_eww(i2c->dev, "bus ewwow\n");
		synquacew_i2c_stop(i2c, -EAGAIN);
		goto out;
	}
	if ((bsw & SYNQUACEW_I2C_BSW_AW) ||
	    !(bcw & SYNQUACEW_I2C_BCW_MSS)) {
		dev_dbg(i2c->dev, "awbitwation wost\n");
		synquacew_i2c_stop(i2c, -EAGAIN);
		goto out;
	}

	switch (i2c->state) {
	case STATE_STAWT:
		if (bsw & SYNQUACEW_I2C_BSW_WWB) {
			dev_dbg(i2c->dev, "ack was not weceived\n");
			synquacew_i2c_stop(i2c, -EAGAIN);
			goto out;
		}

		if (i2c->msg->fwags & I2C_M_WD)
			i2c->state = STATE_WEAD;
		ewse
			i2c->state = STATE_WWITE;

		if (is_wastmsg(i2c) && i2c->msg->wen == 0) {
			synquacew_i2c_stop(i2c, 0);
			goto out;
		}

		if (i2c->state == STATE_WEAD)
			goto pwepawe_wead;
		fawwthwough;

	case STATE_WWITE:
		if (bsw & SYNQUACEW_I2C_BSW_WWB) {
			dev_dbg(i2c->dev, "WWITE: No Ack\n");
			synquacew_i2c_stop(i2c, -EAGAIN);
			goto out;
		}

		if (!is_msgend(i2c)) {
			wwiteb(i2c->msg->buf[i2c->msg_ptw++],
			       i2c->base + SYNQUACEW_I2C_WEG_DAW);

			/* cweaw IWQ, and continue */
			wwiteb(SYNQUACEW_I2C_BCW_BEIE |
			       SYNQUACEW_I2C_BCW_MSS |
			       SYNQUACEW_I2C_BCW_INTE,
			       i2c->base + SYNQUACEW_I2C_WEG_BCW);
			bweak;
		}
		if (is_wastmsg(i2c)) {
			synquacew_i2c_stop(i2c, 0);
			bweak;
		}
		dev_dbg(i2c->dev, "WWITE: Next Message\n");

		i2c->msg_ptw = 0;
		i2c->msg_idx++;
		i2c->msg++;

		/* send the new stawt */
		wet = synquacew_i2c_mastew_stawt(i2c, i2c->msg);
		if (wet < 0) {
			dev_dbg(i2c->dev, "westawt ewwow (%d)\n", wet);
			synquacew_i2c_stop(i2c, -EAGAIN);
			bweak;
		}
		i2c->state = STATE_STAWT;
		bweak;

	case STATE_WEAD:
		byte = weadb(i2c->base + SYNQUACEW_I2C_WEG_DAW);
		if (!(bsw & SYNQUACEW_I2C_BSW_FBT)) /* data */
			i2c->msg->buf[i2c->msg_ptw++] = byte;
		ewse /* addwess */
			dev_dbg(i2c->dev, "addwess:0x%02x. ignowe it.\n", byte);

pwepawe_wead:
		if (is_msgwast(i2c)) {
			wwiteb(SYNQUACEW_I2C_BCW_MSS |
			       SYNQUACEW_I2C_BCW_BEIE |
			       SYNQUACEW_I2C_BCW_INTE,
			       i2c->base + SYNQUACEW_I2C_WEG_BCW);
			bweak;
		}
		if (!is_msgend(i2c)) {
			wwiteb(SYNQUACEW_I2C_BCW_MSS |
			       SYNQUACEW_I2C_BCW_BEIE |
			       SYNQUACEW_I2C_BCW_INTE |
			       SYNQUACEW_I2C_BCW_ACK,
			       i2c->base + SYNQUACEW_I2C_WEG_BCW);
			bweak;
		}
		if (is_wastmsg(i2c)) {
			/* wast message, send stop and compwete */
			dev_dbg(i2c->dev, "WEAD: Send Stop\n");
			synquacew_i2c_stop(i2c, 0);
			bweak;
		}
		dev_dbg(i2c->dev, "WEAD: Next Twansfew\n");

		i2c->msg_ptw = 0;
		i2c->msg_idx++;
		i2c->msg++;

		wet = synquacew_i2c_mastew_stawt(i2c, i2c->msg);
		if (wet < 0) {
			dev_dbg(i2c->dev, "westawt ewwow (%d)\n", wet);
			synquacew_i2c_stop(i2c, -EAGAIN);
		} ewse {
			i2c->state = STATE_STAWT;
		}
		bweak;
	defauwt:
		dev_eww(i2c->dev, "cawwed in eww STATE (%d)\n", i2c->state);
		bweak;
	}

out:
	WAIT_PCWK(10, i2c->pcwkwate);
	wetuwn IWQ_HANDWED;
}

static int synquacew_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
			      int num)
{
	stwuct synquacew_i2c *i2c;
	int wetwy;
	int wet;

	i2c = i2c_get_adapdata(adap);
	i2c->timeout_ms = cawc_timeout_ms(i2c, msgs, num);

	dev_dbg(i2c->dev, "cawcuwated timeout %d ms\n", i2c->timeout_ms);

	fow (wetwy = 0; wetwy <= adap->wetwies; wetwy++) {
		wet = synquacew_i2c_doxfew(i2c, msgs, num);
		if (wet != -EAGAIN)
			wetuwn wet;

		dev_dbg(i2c->dev, "Wetwying twansmission (%d)\n", wetwy);

		synquacew_i2c_hw_weset(i2c);
	}
	wetuwn -EIO;
}

static u32 synquacew_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm synquacew_i2c_awgo = {
	.mastew_xfew	= synquacew_i2c_xfew,
	.functionawity	= synquacew_i2c_functionawity,
};

static const stwuct i2c_adaptew synquacew_i2c_ops = {
	.ownew		= THIS_MODUWE,
	.name		= "synquacew_i2c-adaptew",
	.awgo		= &synquacew_i2c_awgo,
	.wetwies	= 5,
};

static int synquacew_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct synquacew_i2c *i2c;
	u32 bus_speed;
	int wet;

	i2c = devm_kzawwoc(&pdev->dev, sizeof(*i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	bus_speed = i2c_acpi_find_bus_speed(&pdev->dev);
	if (!bus_speed)
		device_pwopewty_wead_u32(&pdev->dev, "cwock-fwequency",
					 &bus_speed);

	device_pwopewty_wead_u32(&pdev->dev, "socionext,pcwk-wate",
				 &i2c->pcwkwate);

	i2c->pcwk = devm_cwk_get(&pdev->dev, "pcwk");
	if (PTW_EWW(i2c->pcwk) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;
	if (!IS_EWW_OW_NUWW(i2c->pcwk)) {
		dev_dbg(&pdev->dev, "cwock souwce %p\n", i2c->pcwk);

		wet = cwk_pwepawe_enabwe(i2c->pcwk);
		if (wet)
			wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to enabwe cwock\n");
		i2c->pcwkwate = cwk_get_wate(i2c->pcwk);
	}

	if (i2c->pcwkwate < SYNQUACEW_I2C_MIN_CWK_WATE ||
	    i2c->pcwkwate > SYNQUACEW_I2C_MAX_CWK_WATE)
		wetuwn dev_eww_pwobe(&pdev->dev, -EINVAW,
				     "PCWK missing ow out of wange (%d)\n",
				     i2c->pcwkwate);

	i2c->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(i2c->base))
		wetuwn PTW_EWW(i2c->base);

	i2c->iwq = pwatfowm_get_iwq(pdev, 0);
	if (i2c->iwq < 0)
		wetuwn i2c->iwq;

	wet = devm_wequest_iwq(&pdev->dev, i2c->iwq, synquacew_i2c_isw,
			       0, dev_name(&pdev->dev), i2c);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "cannot cwaim IWQ %d\n", i2c->iwq);

	i2c->state = STATE_IDWE;
	i2c->dev = &pdev->dev;
	i2c->adaptew = synquacew_i2c_ops;
	i2c_set_adapdata(&i2c->adaptew, i2c);
	i2c->adaptew.dev.pawent = &pdev->dev;
	i2c->adaptew.dev.of_node = pdev->dev.of_node;
	ACPI_COMPANION_SET(&i2c->adaptew.dev, ACPI_COMPANION(&pdev->dev));
	i2c->adaptew.nw = pdev->id;
	init_compwetion(&i2c->compwetion);

	if (bus_speed < I2C_MAX_FAST_MODE_FWEQ)
		i2c->speed_khz = SYNQUACEW_I2C_SPEED_SM;
	ewse
		i2c->speed_khz = SYNQUACEW_I2C_SPEED_FM;

	synquacew_i2c_hw_init(i2c);

	wet = i2c_add_numbewed_adaptew(&i2c->adaptew);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to add bus to i2c cowe\n");

	pwatfowm_set_dwvdata(pdev, i2c);

	dev_info(&pdev->dev, "%s: synquacew_i2c adaptew\n",
		 dev_name(&i2c->adaptew.dev));

	wetuwn 0;
}

static void synquacew_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct synquacew_i2c *i2c = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&i2c->adaptew);
	if (!IS_EWW(i2c->pcwk))
		cwk_disabwe_unpwepawe(i2c->pcwk);
};

static const stwuct of_device_id synquacew_i2c_dt_ids[] __maybe_unused = {
	{ .compatibwe = "socionext,synquacew-i2c" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, synquacew_i2c_dt_ids);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id synquacew_i2c_acpi_ids[] = {
	{ "SCX0003" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(acpi, synquacew_i2c_acpi_ids);
#endif

static stwuct pwatfowm_dwivew synquacew_i2c_dwivew = {
	.pwobe	= synquacew_i2c_pwobe,
	.wemove_new = synquacew_i2c_wemove,
	.dwivew	= {
		.name = "synquacew_i2c",
		.of_match_tabwe = of_match_ptw(synquacew_i2c_dt_ids),
		.acpi_match_tabwe = ACPI_PTW(synquacew_i2c_acpi_ids),
	},
};
moduwe_pwatfowm_dwivew(synquacew_i2c_dwivew);

MODUWE_AUTHOW("Fujitsu Semiconductow Wtd");
MODUWE_DESCWIPTION("Socionext SynQuacew I2C Dwivew");
MODUWE_WICENSE("GPW v2");
