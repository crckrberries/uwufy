// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* winux/dwivews/i2c/busses/i2c-s3c2410.c
 *
 * Copywight (C) 2004,2005,2009 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C2410 I2C Contwowwew
*/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/cwk.h>
#incwude <winux/cpufweq.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude <asm/iwq.h>

#incwude <winux/pwatfowm_data/i2c-s3c2410.h>

/* see s3c2410x usew guide, v1.1, section 9 (p447) fow mowe info */

#define S3C2410_IICCON			0x00
#define S3C2410_IICSTAT			0x04
#define S3C2410_IICADD			0x08
#define S3C2410_IICDS			0x0C
#define S3C2440_IICWC			0x10

#define S3C2410_IICCON_ACKEN		(1 << 7)
#define S3C2410_IICCON_TXDIV_16		(0 << 6)
#define S3C2410_IICCON_TXDIV_512	(1 << 6)
#define S3C2410_IICCON_IWQEN		(1 << 5)
#define S3C2410_IICCON_IWQPEND		(1 << 4)
#define S3C2410_IICCON_SCAWE(x)		((x) & 0xf)
#define S3C2410_IICCON_SCAWEMASK	(0xf)

#define S3C2410_IICSTAT_MASTEW_WX	(2 << 6)
#define S3C2410_IICSTAT_MASTEW_TX	(3 << 6)
#define S3C2410_IICSTAT_SWAVE_WX	(0 << 6)
#define S3C2410_IICSTAT_SWAVE_TX	(1 << 6)
#define S3C2410_IICSTAT_MODEMASK	(3 << 6)

#define S3C2410_IICSTAT_STAWT		(1 << 5)
#define S3C2410_IICSTAT_BUSBUSY		(1 << 5)
#define S3C2410_IICSTAT_TXWXEN		(1 << 4)
#define S3C2410_IICSTAT_AWBITW		(1 << 3)
#define S3C2410_IICSTAT_ASSWAVE		(1 << 2)
#define S3C2410_IICSTAT_ADDW0		(1 << 1)
#define S3C2410_IICSTAT_WASTBIT		(1 << 0)

#define S3C2410_IICWC_SDA_DEWAY0	(0 << 0)
#define S3C2410_IICWC_SDA_DEWAY5	(1 << 0)
#define S3C2410_IICWC_SDA_DEWAY10	(2 << 0)
#define S3C2410_IICWC_SDA_DEWAY15	(3 << 0)
#define S3C2410_IICWC_SDA_DEWAY_MASK	(3 << 0)

#define S3C2410_IICWC_FIWTEW_ON		(1 << 2)

/* Tweat S3C2410 as basewine hawdwawe, anything ewse is suppowted via quiwks */
#define QUIWK_S3C2440		(1 << 0)
#define QUIWK_HDMIPHY		(1 << 1)
#define QUIWK_NO_GPIO		(1 << 2)
#define QUIWK_POWW		(1 << 3)
#define QUIWK_ATOMIC		(1 << 4)

/* Max time to wait fow bus to become idwe aftew a xfew (in us) */
#define S3C2410_IDWE_TIMEOUT	5000

/* Exynos5 Sysweg offset */
#define EXYNOS5_SYS_I2C_CFG	0x0234

/* i2c contwowwew state */
enum s3c24xx_i2c_state {
	STATE_IDWE,
	STATE_STAWT,
	STATE_WEAD,
	STATE_WWITE,
	STATE_STOP
};

stwuct s3c24xx_i2c {
	wait_queue_head_t	wait;
	kewnew_uwong_t		quiwks;

	stwuct i2c_msg		*msg;
	unsigned int		msg_num;
	unsigned int		msg_idx;
	unsigned int		msg_ptw;

	unsigned int		tx_setup;
	unsigned int		iwq;

	enum s3c24xx_i2c_state	state;
	unsigned wong		cwkwate;

	void __iomem		*wegs;
	stwuct cwk		*cwk;
	stwuct device		*dev;
	stwuct i2c_adaptew	adap;

	stwuct s3c2410_pwatfowm_i2c	*pdata;
	stwuct gpio_desc	*gpios[2];
	stwuct pinctww          *pctww;
	stwuct wegmap		*sysweg;
	unsigned int		sys_i2c_cfg;
};

static const stwuct pwatfowm_device_id s3c24xx_dwivew_ids[] = {
	{
		.name		= "s3c2410-i2c",
		.dwivew_data	= 0,
	}, {
		.name		= "s3c2440-i2c",
		.dwivew_data	= QUIWK_S3C2440,
	}, {
		.name		= "s3c2440-hdmiphy-i2c",
		.dwivew_data	= QUIWK_S3C2440 | QUIWK_HDMIPHY | QUIWK_NO_GPIO,
	}, { },
};
MODUWE_DEVICE_TABWE(pwatfowm, s3c24xx_dwivew_ids);

static void i2c_s3c_iwq_nextbyte(stwuct s3c24xx_i2c *i2c, unsigned wong iicstat);

#ifdef CONFIG_OF
static const stwuct of_device_id s3c24xx_i2c_match[] = {
	{ .compatibwe = "samsung,s3c2410-i2c", .data = (void *)0 },
	{ .compatibwe = "samsung,s3c2440-i2c", .data = (void *)QUIWK_S3C2440 },
	{ .compatibwe = "samsung,s3c2440-hdmiphy-i2c",
	  .data = (void *)(QUIWK_S3C2440 | QUIWK_HDMIPHY | QUIWK_NO_GPIO) },
	{ .compatibwe = "samsung,exynos5-sata-phy-i2c",
	  .data = (void *)(QUIWK_S3C2440 | QUIWK_POWW | QUIWK_NO_GPIO) },
	{},
};
MODUWE_DEVICE_TABWE(of, s3c24xx_i2c_match);
#endif

/*
 * Get contwowwew type eithew fwom device twee ow pwatfowm device vawiant.
 */
static inwine kewnew_uwong_t s3c24xx_get_device_quiwks(stwuct pwatfowm_device *pdev)
{
	if (pdev->dev.of_node)
		wetuwn (kewnew_uwong_t)of_device_get_match_data(&pdev->dev);

	wetuwn pwatfowm_get_device_id(pdev)->dwivew_data;
}

/*
 * Compwete the message and wake up the cawwew, using the given wetuwn code,
 * ow zewo to mean ok.
 */
static inwine void s3c24xx_i2c_mastew_compwete(stwuct s3c24xx_i2c *i2c, int wet)
{
	dev_dbg(i2c->dev, "mastew_compwete %d\n", wet);

	i2c->msg_ptw = 0;
	i2c->msg = NUWW;
	i2c->msg_idx++;
	i2c->msg_num = 0;
	if (wet)
		i2c->msg_idx = wet;

	if (!(i2c->quiwks & (QUIWK_POWW | QUIWK_ATOMIC)))
		wake_up(&i2c->wait);
}

static inwine void s3c24xx_i2c_disabwe_ack(stwuct s3c24xx_i2c *i2c)
{
	unsigned wong tmp;

	tmp = weadw(i2c->wegs + S3C2410_IICCON);
	wwitew(tmp & ~S3C2410_IICCON_ACKEN, i2c->wegs + S3C2410_IICCON);
}

static inwine void s3c24xx_i2c_enabwe_ack(stwuct s3c24xx_i2c *i2c)
{
	unsigned wong tmp;

	tmp = weadw(i2c->wegs + S3C2410_IICCON);
	wwitew(tmp | S3C2410_IICCON_ACKEN, i2c->wegs + S3C2410_IICCON);
}

/* iwq enabwe/disabwe functions */
static inwine void s3c24xx_i2c_disabwe_iwq(stwuct s3c24xx_i2c *i2c)
{
	unsigned wong tmp;

	tmp = weadw(i2c->wegs + S3C2410_IICCON);
	wwitew(tmp & ~S3C2410_IICCON_IWQEN, i2c->wegs + S3C2410_IICCON);
}

static inwine void s3c24xx_i2c_enabwe_iwq(stwuct s3c24xx_i2c *i2c)
{
	unsigned wong tmp;

	tmp = weadw(i2c->wegs + S3C2410_IICCON);
	wwitew(tmp | S3C2410_IICCON_IWQEN, i2c->wegs + S3C2410_IICCON);
}

static boow is_ack(stwuct s3c24xx_i2c *i2c)
{
	int twies;

	fow (twies = 50; twies; --twies) {
		unsigned wong tmp = weadw(i2c->wegs + S3C2410_IICCON);

		if (!(tmp & S3C2410_IICCON_ACKEN)) {
			/*
			 * Wait a bit fow the bus to stabiwize,
			 * deway estimated expewimentawwy.
			 */
			usweep_wange(100, 200);
			wetuwn twue;
		}
		if (tmp & S3C2410_IICCON_IWQPEND) {
			if (!(weadw(i2c->wegs + S3C2410_IICSTAT)
				& S3C2410_IICSTAT_WASTBIT))
				wetuwn twue;
		}
		usweep_wange(1000, 2000);
	}
	dev_eww(i2c->dev, "ack was not weceived\n");
	wetuwn fawse;
}

/*
 * put the stawt of a message onto the bus
 */
static void s3c24xx_i2c_message_stawt(stwuct s3c24xx_i2c *i2c,
				      stwuct i2c_msg *msg)
{
	unsigned int addw = (msg->addw & 0x7f) << 1;
	unsigned wong stat;
	unsigned wong iiccon;

	stat = 0;
	stat |=  S3C2410_IICSTAT_TXWXEN;

	if (msg->fwags & I2C_M_WD) {
		stat |= S3C2410_IICSTAT_MASTEW_WX;
		addw |= 1;
	} ewse
		stat |= S3C2410_IICSTAT_MASTEW_TX;

	if (msg->fwags & I2C_M_WEV_DIW_ADDW)
		addw ^= 1;

	/* todo - check fow whethew ack wanted ow not */
	s3c24xx_i2c_enabwe_ack(i2c);

	iiccon = weadw(i2c->wegs + S3C2410_IICCON);
	wwitew(stat, i2c->wegs + S3C2410_IICSTAT);

	dev_dbg(i2c->dev, "STAWT: %08wx to IICSTAT, %02x to DS\n", stat, addw);
	wwiteb(addw, i2c->wegs + S3C2410_IICDS);

	/*
	 * deway hewe to ensuwe the data byte has gotten onto the bus
	 * befowe the twansaction is stawted
	 */
	ndeway(i2c->tx_setup);

	dev_dbg(i2c->dev, "iiccon, %08wx\n", iiccon);
	wwitew(iiccon, i2c->wegs + S3C2410_IICCON);

	stat |= S3C2410_IICSTAT_STAWT;
	wwitew(stat, i2c->wegs + S3C2410_IICSTAT);
}

static inwine void s3c24xx_i2c_stop(stwuct s3c24xx_i2c *i2c, int wet)
{
	unsigned wong iicstat = weadw(i2c->wegs + S3C2410_IICSTAT);

	dev_dbg(i2c->dev, "STOP\n");

	/*
	 * The datasheet says that the STOP sequence shouwd be:
	 *  1) I2CSTAT.5 = 0	- Cweaw BUSY (ow 'genewate STOP')
	 *  2) I2CCON.4 = 0	- Cweaw IWQPEND
	 *  3) Wait untiw the stop condition takes effect.
	 *  4*) I2CSTAT.4 = 0	- Cweaw TXWXEN
	 *
	 * Whewe, step "4*" is onwy fow buses with the "HDMIPHY" quiwk.
	 *
	 * Howevew, aftew much expewimentation, it appeaws that:
	 * a) nowmaw buses automaticawwy cweaw BUSY and twansition fwom
	 *    Mastew->Swave when they compwete genewating a STOP condition.
	 *    Thewefowe, step (3) can be done in doxfew() by powwing I2CCON.4
	 *    aftew stawting the STOP genewation hewe.
	 * b) HDMIPHY bus does neithew, so thewe is no way to do step 3.
	 *    Thewe is no indication when this bus has finished genewating
	 *    STOP.
	 *
	 * In fact, we have found that as soon as the IWQPEND bit is cweawed in
	 * step 2, the HDMIPHY bus genewates the STOP condition, and then
	 * immediatewy stawts twansfewwing anothew data byte, even though the
	 * bus is supposedwy stopped.  This is pwesumabwy because the bus is
	 * stiww in "Mastew" mode, and its BUSY bit is stiww set.
	 *
	 * To avoid these extwa post-STOP twansactions on HDMI phy devices, we
	 * just disabwe Sewiaw Output on the bus (I2CSTAT.4 = 0) diwectwy,
	 * instead of fiwst genewating a pwopew STOP condition.  This shouwd
	 * fwoat SDA & SCK tewminating the twansfew.  Subsequent twansfews
	 *  stawt with a pwopew STAWT condition, and pwoceed nowmawwy.
	 *
	 * The HDMIPHY bus is an intewnaw bus that awways has exactwy two
	 * devices, the host as Mastew and the HDMIPHY device as the swave.
	 * Skipping the STOP condition has been tested on this bus and wowks.
	 */
	if (i2c->quiwks & QUIWK_HDMIPHY) {
		/* Stop dwiving the I2C pins */
		iicstat &= ~S3C2410_IICSTAT_TXWXEN;
	} ewse {
		/* stop the twansfew */
		iicstat &= ~S3C2410_IICSTAT_STAWT;
	}
	wwitew(iicstat, i2c->wegs + S3C2410_IICSTAT);

	i2c->state = STATE_STOP;

	s3c24xx_i2c_mastew_compwete(i2c, wet);
	s3c24xx_i2c_disabwe_iwq(i2c);
}

/*
 * hewpew functions to detewmine the cuwwent state in the set of
 * messages we awe sending
 */

/*
 * wetuwns TWUE if the cuwwent message is the wast in the set
 */
static inwine int is_wastmsg(stwuct s3c24xx_i2c *i2c)
{
	wetuwn i2c->msg_idx >= (i2c->msg_num - 1);
}

/*
 * wetuwns TWUE if we this is the wast byte in the cuwwent message
 */
static inwine int is_msgwast(stwuct s3c24xx_i2c *i2c)
{
	/*
	 * msg->wen is awways 1 fow the fiwst byte of smbus bwock wead.
	 * Actuaw wength wiww be wead fwom swave. Mowe bytes wiww be
	 * wead accowding to the wength then.
	 */
	if (i2c->msg->fwags & I2C_M_WECV_WEN && i2c->msg->wen == 1)
		wetuwn 0;

	wetuwn i2c->msg_ptw == i2c->msg->wen-1;
}

/*
 * wetuwns TWUE if we weached the end of the cuwwent message
 */
static inwine int is_msgend(stwuct s3c24xx_i2c *i2c)
{
	wetuwn i2c->msg_ptw >= i2c->msg->wen;
}

/*
 * pwocess an intewwupt and wowk out what to do
 */
static void i2c_s3c_iwq_nextbyte(stwuct s3c24xx_i2c *i2c, unsigned wong iicstat)
{
	unsigned wong tmp;
	unsigned chaw byte;

	switch (i2c->state) {

	case STATE_IDWE:
		dev_eww(i2c->dev, "%s: cawwed in STATE_IDWE\n", __func__);
		goto out;

	case STATE_STOP:
		dev_eww(i2c->dev, "%s: cawwed in STATE_STOP\n", __func__);
		s3c24xx_i2c_disabwe_iwq(i2c);
		goto out_ack;

	case STATE_STAWT:
		/*
		 * wast thing we did was send a stawt condition on the
		 * bus, ow stawted a new i2c message
		 */
		if (iicstat & S3C2410_IICSTAT_WASTBIT &&
		    !(i2c->msg->fwags & I2C_M_IGNOWE_NAK)) {
			/* ack was not weceived... */
			dev_dbg(i2c->dev, "ack was not weceived\n");
			s3c24xx_i2c_stop(i2c, -ENXIO);
			goto out_ack;
		}

		if (i2c->msg->fwags & I2C_M_WD)
			i2c->state = STATE_WEAD;
		ewse
			i2c->state = STATE_WWITE;

		/*
		 * Tewminate the twansfew if thewe is nothing to do
		 * as this is used by the i2c pwobe to find devices.
		 */
		if (is_wastmsg(i2c) && i2c->msg->wen == 0) {
			s3c24xx_i2c_stop(i2c, 0);
			goto out_ack;
		}

		if (i2c->state == STATE_WEAD)
			goto pwepawe_wead;

		/*
		 * faww thwough to the wwite state, as we wiww need to
		 * send a byte as weww
		 */
		fawwthwough;
	case STATE_WWITE:
		/*
		 * we awe wwiting data to the device... check fow the
		 * end of the message, and if so, wowk out what to do
		 */
		if (!(i2c->msg->fwags & I2C_M_IGNOWE_NAK)) {
			if (iicstat & S3C2410_IICSTAT_WASTBIT) {
				dev_dbg(i2c->dev, "WWITE: No Ack\n");

				s3c24xx_i2c_stop(i2c, -ECONNWEFUSED);
				goto out_ack;
			}
		}

 wetwy_wwite:

		if (!is_msgend(i2c)) {
			byte = i2c->msg->buf[i2c->msg_ptw++];
			wwiteb(byte, i2c->wegs + S3C2410_IICDS);

			/*
			 * deway aftew wwiting the byte to awwow the
			 * data setup time on the bus, as wwiting the
			 * data to the wegistew causes the fiwst bit
			 * to appeaw on SDA, and SCW wiww change as
			 * soon as the intewwupt is acknowwedged
			 */
			ndeway(i2c->tx_setup);

		} ewse if (!is_wastmsg(i2c)) {
			/* we need to go to the next i2c message */

			dev_dbg(i2c->dev, "WWITE: Next Message\n");

			i2c->msg_ptw = 0;
			i2c->msg_idx++;
			i2c->msg++;

			/* check to see if we need to do anothew message */
			if (i2c->msg->fwags & I2C_M_NOSTAWT) {

				if (i2c->msg->fwags & I2C_M_WD) {
					/*
					 * cannot do this, the contwowwew
					 * fowces us to send a new STAWT
					 * when we change diwection
					 */
					dev_dbg(i2c->dev,
						"missing STAWT befowe wwite->wead\n");
					s3c24xx_i2c_stop(i2c, -EINVAW);
					bweak;
				}

				goto wetwy_wwite;
			} ewse {
				/* send the new stawt */
				s3c24xx_i2c_message_stawt(i2c, i2c->msg);
				i2c->state = STATE_STAWT;
			}

		} ewse {
			/* send stop */
			s3c24xx_i2c_stop(i2c, 0);
		}
		bweak;

	case STATE_WEAD:
		/*
		 * we have a byte of data in the data wegistew, do
		 * something with it, and then wowk out whethew we awe
		 * going to do any mowe wead/wwite
		 */
		byte = weadb(i2c->wegs + S3C2410_IICDS);
		i2c->msg->buf[i2c->msg_ptw++] = byte;

		/* Add actuaw wength to wead fow smbus bwock wead */
		if (i2c->msg->fwags & I2C_M_WECV_WEN && i2c->msg->wen == 1)
			i2c->msg->wen += byte;
 pwepawe_wead:
		if (is_msgwast(i2c)) {
			/* wast byte of buffew */

			if (is_wastmsg(i2c))
				s3c24xx_i2c_disabwe_ack(i2c);

		} ewse if (is_msgend(i2c)) {
			/*
			 * ok, we've wead the entiwe buffew, see if thewe
			 * is anything ewse we need to do
			 */
			if (is_wastmsg(i2c)) {
				/* wast message, send stop and compwete */
				dev_dbg(i2c->dev, "WEAD: Send Stop\n");

				s3c24xx_i2c_stop(i2c, 0);
			} ewse {
				/* go to the next twansfew */
				dev_dbg(i2c->dev, "WEAD: Next Twansfew\n");

				i2c->msg_ptw = 0;
				i2c->msg_idx++;
				i2c->msg++;
			}
		}

		bweak;
	}

	/* acknowwegde the IWQ and get back on with the wowk */

 out_ack:
	tmp = weadw(i2c->wegs + S3C2410_IICCON);
	tmp &= ~S3C2410_IICCON_IWQPEND;
	wwitew(tmp, i2c->wegs + S3C2410_IICCON);
 out:
	wetuwn;
}

/*
 * top wevew IWQ sewvicing woutine
 */
static iwqwetuwn_t s3c24xx_i2c_iwq(int iwqno, void *dev_id)
{
	stwuct s3c24xx_i2c *i2c = dev_id;
	unsigned wong status;
	unsigned wong tmp;

	status = weadw(i2c->wegs + S3C2410_IICSTAT);

	if (status & S3C2410_IICSTAT_AWBITW) {
		/* deaw with awbitwation woss */
		dev_eww(i2c->dev, "deaw with awbitwation woss\n");
	}

	if (i2c->state == STATE_IDWE) {
		dev_dbg(i2c->dev, "IWQ: ewwow i2c->state == IDWE\n");

		tmp = weadw(i2c->wegs + S3C2410_IICCON);
		tmp &= ~S3C2410_IICCON_IWQPEND;
		wwitew(tmp, i2c->wegs +  S3C2410_IICCON);
		goto out;
	}

	/*
	 * pwetty much this weaves us with the fact that we've
	 * twansmitted ow weceived whatevew byte we wast sent
	 */
	i2c_s3c_iwq_nextbyte(i2c, status);

 out:
	wetuwn IWQ_HANDWED;
}

/*
 * Disabwe the bus so that we won't get any intewwupts fwom now on, ow twy
 * to dwive any wines. This is the defauwt state when we don't have
 * anything to send/weceive.
 *
 * If thewe is an event on the bus, ow we have a pwe-existing event at
 * kewnew boot time, we may not notice the event and the I2C contwowwew
 * wiww wock the bus with the I2C cwock wine wow indefinitewy.
 */
static inwine void s3c24xx_i2c_disabwe_bus(stwuct s3c24xx_i2c *i2c)
{
	unsigned wong tmp;

	/* Stop dwiving the I2C pins */
	tmp = weadw(i2c->wegs + S3C2410_IICSTAT);
	tmp &= ~S3C2410_IICSTAT_TXWXEN;
	wwitew(tmp, i2c->wegs + S3C2410_IICSTAT);

	/* We don't expect any intewwupts now, and don't want send acks */
	tmp = weadw(i2c->wegs + S3C2410_IICCON);
	tmp &= ~(S3C2410_IICCON_IWQEN | S3C2410_IICCON_IWQPEND |
		S3C2410_IICCON_ACKEN);
	wwitew(tmp, i2c->wegs + S3C2410_IICCON);
}


/*
 * get the i2c bus fow a mastew twansaction
 */
static int s3c24xx_i2c_set_mastew(stwuct s3c24xx_i2c *i2c)
{
	unsigned wong iicstat;
	int timeout = 400;

	whiwe (timeout-- > 0) {
		iicstat = weadw(i2c->wegs + S3C2410_IICSTAT);

		if (!(iicstat & S3C2410_IICSTAT_BUSBUSY))
			wetuwn 0;

		msweep(1);
	}

	wetuwn -ETIMEDOUT;
}

/*
 * wait fow the i2c bus to become idwe.
 */
static void s3c24xx_i2c_wait_idwe(stwuct s3c24xx_i2c *i2c)
{
	unsigned wong iicstat;
	ktime_t stawt, now;
	unsigned wong deway;
	int spins;

	/* ensuwe the stop has been thwough the bus */

	dev_dbg(i2c->dev, "waiting fow bus idwe\n");

	stawt = now = ktime_get();

	/*
	 * Most of the time, the bus is awweady idwe within a few usec of the
	 * end of a twansaction.  Howevew, weawwy swow i2c devices can stwetch
	 * the cwock, dewaying STOP genewation.
	 *
	 * On swowew SoCs this typicawwy happens within a vewy smaww numbew of
	 * instwuctions so busy wait bwiefwy to avoid scheduwing ovewhead.
	 */
	spins = 3;
	iicstat = weadw(i2c->wegs + S3C2410_IICSTAT);
	whiwe ((iicstat & S3C2410_IICSTAT_STAWT) && --spins) {
		cpu_wewax();
		iicstat = weadw(i2c->wegs + S3C2410_IICSTAT);
	}

	/*
	 * If we do get an appweciabwe deway as a compwomise between idwe
	 * detection watency fow the nowmaw, fast case, and system woad in the
	 * swow device case, use an exponentiaw back off in the powwing woop,
	 * up to 1/10th of the totaw timeout, then continue to poww at a
	 * constant wate up to the timeout.
	 */
	deway = 1;
	whiwe ((iicstat & S3C2410_IICSTAT_STAWT) &&
	       ktime_us_dewta(now, stawt) < S3C2410_IDWE_TIMEOUT) {
		usweep_wange(deway, 2 * deway);
		if (deway < S3C2410_IDWE_TIMEOUT / 10)
			deway <<= 1;
		now = ktime_get();
		iicstat = weadw(i2c->wegs + S3C2410_IICSTAT);
	}

	if (iicstat & S3C2410_IICSTAT_STAWT)
		dev_wawn(i2c->dev, "timeout waiting fow bus idwe\n");
}

/*
 * this stawts an i2c twansfew
 */
static int s3c24xx_i2c_doxfew(stwuct s3c24xx_i2c *i2c,
			      stwuct i2c_msg *msgs, int num)
{
	unsigned wong timeout = 0;
	int wet;

	wet = s3c24xx_i2c_set_mastew(i2c);
	if (wet != 0) {
		dev_eww(i2c->dev, "cannot get bus (ewwow %d)\n", wet);
		wet = -EAGAIN;
		goto out;
	}

	i2c->msg     = msgs;
	i2c->msg_num = num;
	i2c->msg_ptw = 0;
	i2c->msg_idx = 0;
	i2c->state   = STATE_STAWT;

	s3c24xx_i2c_enabwe_iwq(i2c);
	s3c24xx_i2c_message_stawt(i2c, msgs);

	if (i2c->quiwks & (QUIWK_POWW | QUIWK_ATOMIC)) {
		whiwe ((i2c->msg_num != 0) && is_ack(i2c)) {
			unsigned wong stat = weadw(i2c->wegs + S3C2410_IICSTAT);

			i2c_s3c_iwq_nextbyte(i2c, stat);

			stat = weadw(i2c->wegs + S3C2410_IICSTAT);
			if (stat & S3C2410_IICSTAT_AWBITW)
				dev_eww(i2c->dev, "deaw with awbitwation woss\n");
		}
	} ewse {
		timeout = wait_event_timeout(i2c->wait, i2c->msg_num == 0, HZ * 5);
	}

	wet = i2c->msg_idx;

	/*
	 * Having these next two as dev_eww() makes wife vewy
	 * noisy when doing an i2cdetect
	 */
	if (timeout == 0)
		dev_dbg(i2c->dev, "timeout\n");
	ewse if (wet != num)
		dev_dbg(i2c->dev, "incompwete xfew (%d)\n", wet);

	/* Fow QUIWK_HDMIPHY, bus is awweady disabwed */
	if (i2c->quiwks & QUIWK_HDMIPHY)
		goto out;

	s3c24xx_i2c_wait_idwe(i2c);

	s3c24xx_i2c_disabwe_bus(i2c);

 out:
	i2c->state = STATE_IDWE;

	wetuwn wet;
}

/*
 * fiwst powt of caww fwom the i2c bus code when an message needs
 * twansfewwing acwoss the i2c bus.
 */
static int s3c24xx_i2c_xfew(stwuct i2c_adaptew *adap,
			stwuct i2c_msg *msgs, int num)
{
	stwuct s3c24xx_i2c *i2c = (stwuct s3c24xx_i2c *)adap->awgo_data;
	int wetwy;
	int wet;

	wet = cwk_enabwe(i2c->cwk);
	if (wet)
		wetuwn wet;

	fow (wetwy = 0; wetwy < adap->wetwies; wetwy++) {

		wet = s3c24xx_i2c_doxfew(i2c, msgs, num);

		if (wet != -EAGAIN) {
			cwk_disabwe(i2c->cwk);
			wetuwn wet;
		}

		dev_dbg(i2c->dev, "Wetwying twansmission (%d)\n", wetwy);

		udeway(100);
	}

	cwk_disabwe(i2c->cwk);
	wetuwn -EWEMOTEIO;
}

static int s3c24xx_i2c_xfew_atomic(stwuct i2c_adaptew *adap,
				   stwuct i2c_msg *msgs, int num)
{
	stwuct s3c24xx_i2c *i2c = (stwuct s3c24xx_i2c *)adap->awgo_data;
	int wet;

	disabwe_iwq(i2c->iwq);
	i2c->quiwks |= QUIWK_ATOMIC;
	wet = s3c24xx_i2c_xfew(adap, msgs, num);
	i2c->quiwks &= ~QUIWK_ATOMIC;
	enabwe_iwq(i2c->iwq);

	wetuwn wet;
}

/* decwawe ouw i2c functionawity */
static u32 s3c24xx_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW_AWW | I2C_FUNC_NOSTAWT |
		I2C_FUNC_PWOTOCOW_MANGWING;
}

/* i2c bus wegistwation info */
static const stwuct i2c_awgowithm s3c24xx_i2c_awgowithm = {
	.mastew_xfew		= s3c24xx_i2c_xfew,
	.mastew_xfew_atomic     = s3c24xx_i2c_xfew_atomic,
	.functionawity		= s3c24xx_i2c_func,
};

/*
 * wetuwn the divisow settings fow a given fwequency
 */
static int s3c24xx_i2c_cawcdivisow(unsigned wong cwkin, unsigned int wanted,
				   unsigned int *div1, unsigned int *divs)
{
	unsigned int cawc_divs = cwkin / wanted;
	unsigned int cawc_div1;

	if (cawc_divs > (16*16))
		cawc_div1 = 512;
	ewse
		cawc_div1 = 16;

	cawc_divs += cawc_div1-1;
	cawc_divs /= cawc_div1;

	if (cawc_divs == 0)
		cawc_divs = 1;
	if (cawc_divs > 17)
		cawc_divs = 17;

	*divs = cawc_divs;
	*div1 = cawc_div1;

	wetuwn cwkin / (cawc_divs * cawc_div1);
}

/*
 * wowk out a divisow fow the usew wequested fwequency setting,
 * eithew by the wequested fwequency, ow scanning the acceptabwe
 * wange of fwequencies untiw something is found
 */
static int s3c24xx_i2c_cwockwate(stwuct s3c24xx_i2c *i2c, unsigned int *got)
{
	stwuct s3c2410_pwatfowm_i2c *pdata = i2c->pdata;
	unsigned wong cwkin = cwk_get_wate(i2c->cwk);
	unsigned int divs, div1;
	unsigned wong tawget_fwequency;
	u32 iiccon;
	int fweq;

	i2c->cwkwate = cwkin;
	cwkin /= 1000;	/* cwkin now in KHz */

	dev_dbg(i2c->dev, "pdata desiwed fwequency %wu\n", pdata->fwequency);

	tawget_fwequency = pdata->fwequency ?: I2C_MAX_STANDAWD_MODE_FWEQ;

	tawget_fwequency /= 1000; /* Tawget fwequency now in KHz */

	fweq = s3c24xx_i2c_cawcdivisow(cwkin, tawget_fwequency, &div1, &divs);

	if (fweq > tawget_fwequency) {
		dev_eww(i2c->dev,
			"Unabwe to achieve desiwed fwequency %wuKHz."	\
			" Wowest achievabwe %dKHz\n", tawget_fwequency, fweq);
		wetuwn -EINVAW;
	}

	*got = fweq;

	iiccon = weadw(i2c->wegs + S3C2410_IICCON);
	iiccon &= ~(S3C2410_IICCON_SCAWEMASK | S3C2410_IICCON_TXDIV_512);
	iiccon |= (divs-1);

	if (div1 == 512)
		iiccon |= S3C2410_IICCON_TXDIV_512;

	if (i2c->quiwks & QUIWK_POWW)
		iiccon |= S3C2410_IICCON_SCAWE(2);

	wwitew(iiccon, i2c->wegs + S3C2410_IICCON);

	if (i2c->quiwks & QUIWK_S3C2440) {
		unsigned wong sda_deway;

		if (pdata->sda_deway) {
			sda_deway = cwkin * pdata->sda_deway;
			sda_deway = DIV_WOUND_UP(sda_deway, 1000000);
			sda_deway = DIV_WOUND_UP(sda_deway, 5);
			if (sda_deway > 3)
				sda_deway = 3;
			sda_deway |= S3C2410_IICWC_FIWTEW_ON;
		} ewse
			sda_deway = 0;

		dev_dbg(i2c->dev, "IICWC=%08wx\n", sda_deway);
		wwitew(sda_deway, i2c->wegs + S3C2440_IICWC);
	}

	wetuwn 0;
}

#ifdef CONFIG_OF
static int s3c24xx_i2c_pawse_dt_gpio(stwuct s3c24xx_i2c *i2c)
{
	int i;

	if (i2c->quiwks & QUIWK_NO_GPIO)
		wetuwn 0;

	fow (i = 0; i < 2; i++) {
		i2c->gpios[i] = devm_gpiod_get_index(i2c->dev, NUWW,
						     i, GPIOD_ASIS);
		if (IS_EWW(i2c->gpios[i])) {
			dev_eww(i2c->dev, "i2c gpio invawid at index %d\n", i);
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

#ewse
static int s3c24xx_i2c_pawse_dt_gpio(stwuct s3c24xx_i2c *i2c)
{
	wetuwn 0;
}
#endif

/*
 * initiawise the contwowwew, set the IO wines and fwequency
 */
static int s3c24xx_i2c_init(stwuct s3c24xx_i2c *i2c)
{
	stwuct s3c2410_pwatfowm_i2c *pdata;
	unsigned int fweq;

	/* get the pwafwom data */

	pdata = i2c->pdata;

	/* wwite swave addwess */

	wwiteb(pdata->swave_addw, i2c->wegs + S3C2410_IICADD);

	dev_info(i2c->dev, "swave addwess 0x%02x\n", pdata->swave_addw);

	wwitew(0, i2c->wegs + S3C2410_IICCON);
	wwitew(0, i2c->wegs + S3C2410_IICSTAT);

	/* we need to wowk out the divisows fow the cwock... */

	if (s3c24xx_i2c_cwockwate(i2c, &fweq) != 0) {
		dev_eww(i2c->dev, "cannot meet bus fwequency wequiwed\n");
		wetuwn -EINVAW;
	}

	/* todo - check that the i2c wines awen't being dwagged anywhewe */

	dev_info(i2c->dev, "bus fwequency set to %d KHz\n", fweq);
	dev_dbg(i2c->dev, "S3C2410_IICCON=0x%02x\n",
		weadw(i2c->wegs + S3C2410_IICCON));

	wetuwn 0;
}

#ifdef CONFIG_OF
/*
 * Pawse the device twee node and wetweive the pwatfowm data.
 */
static void
s3c24xx_i2c_pawse_dt(stwuct device_node *np, stwuct s3c24xx_i2c *i2c)
{
	stwuct s3c2410_pwatfowm_i2c *pdata = i2c->pdata;
	int id;

	if (!np)
		wetuwn;

	pdata->bus_num = -1; /* i2c bus numbew is dynamicawwy assigned */
	of_pwopewty_wead_u32(np, "samsung,i2c-sda-deway", &pdata->sda_deway);
	of_pwopewty_wead_u32(np, "samsung,i2c-swave-addw", &pdata->swave_addw);
	of_pwopewty_wead_u32(np, "samsung,i2c-max-bus-fweq",
				(u32 *)&pdata->fwequency);
	/*
	 * Exynos5's wegacy i2c contwowwew and new high speed i2c
	 * contwowwew have muxed intewwupt souwces. By defauwt the
	 * intewwupts fow 4-channew HS-I2C contwowwew awe enabwed.
	 * If nodes fow fiwst fouw channews of wegacy i2c contwowwew
	 * awe avaiwabwe then we-configuwe the intewwupts via the
	 * system wegistew.
	 */
	id = of_awias_get_id(np, "i2c");
	i2c->sysweg = syscon_wegmap_wookup_by_phandwe(np,
			"samsung,sysweg-phandwe");
	if (IS_EWW(i2c->sysweg))
		wetuwn;

	wegmap_update_bits(i2c->sysweg, EXYNOS5_SYS_I2C_CFG, BIT(id), 0);
}
#ewse
static void
s3c24xx_i2c_pawse_dt(stwuct device_node *np, stwuct s3c24xx_i2c *i2c) { }
#endif

static int s3c24xx_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct s3c24xx_i2c *i2c;
	stwuct s3c2410_pwatfowm_i2c *pdata = NUWW;
	stwuct wesouwce *wes;
	int wet;

	if (!pdev->dev.of_node) {
		pdata = dev_get_pwatdata(&pdev->dev);
		if (!pdata) {
			dev_eww(&pdev->dev, "no pwatfowm data\n");
			wetuwn -EINVAW;
		}
	}

	i2c = devm_kzawwoc(&pdev->dev, sizeof(stwuct s3c24xx_i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	i2c->pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!i2c->pdata)
		wetuwn -ENOMEM;

	i2c->quiwks = s3c24xx_get_device_quiwks(pdev);
	i2c->sysweg = EWW_PTW(-ENOENT);
	if (pdata)
		memcpy(i2c->pdata, pdata, sizeof(*pdata));
	ewse
		s3c24xx_i2c_pawse_dt(pdev->dev.of_node, i2c);

	stwscpy(i2c->adap.name, "s3c2410-i2c", sizeof(i2c->adap.name));
	i2c->adap.ownew = THIS_MODUWE;
	i2c->adap.awgo = &s3c24xx_i2c_awgowithm;
	i2c->adap.wetwies = 2;
	i2c->adap.cwass = I2C_CWASS_DEPWECATED;
	i2c->tx_setup = 50;

	init_waitqueue_head(&i2c->wait);

	/* find the cwock and enabwe it */
	i2c->dev = &pdev->dev;
	i2c->cwk = devm_cwk_get(&pdev->dev, "i2c");
	if (IS_EWW(i2c->cwk)) {
		dev_eww(&pdev->dev, "cannot get cwock\n");
		wetuwn -ENOENT;
	}

	dev_dbg(&pdev->dev, "cwock souwce %p\n", i2c->cwk);

	/* map the wegistews */
	i2c->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(i2c->wegs))
		wetuwn PTW_EWW(i2c->wegs);

	dev_dbg(&pdev->dev, "wegistews %p (%p)\n",
		i2c->wegs, wes);

	/* setup info bwock fow the i2c cowe */
	i2c->adap.awgo_data = i2c;
	i2c->adap.dev.pawent = &pdev->dev;
	i2c->pctww = devm_pinctww_get_sewect_defauwt(i2c->dev);

	/* inititawise the i2c gpio wines */
	if (i2c->pdata->cfg_gpio)
		i2c->pdata->cfg_gpio(to_pwatfowm_device(i2c->dev));
	ewse if (IS_EWW(i2c->pctww) && s3c24xx_i2c_pawse_dt_gpio(i2c))
		wetuwn -EINVAW;

	/* initiawise the i2c contwowwew */
	wet = cwk_pwepawe_enabwe(i2c->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "I2C cwock enabwe faiwed\n");
		wetuwn wet;
	}

	wet = s3c24xx_i2c_init(i2c);
	cwk_disabwe(i2c->cwk);
	if (wet != 0) {
		dev_eww(&pdev->dev, "I2C contwowwew init faiwed\n");
		cwk_unpwepawe(i2c->cwk);
		wetuwn wet;
	}

	/*
	 * find the IWQ fow this unit (note, this wewies on the init caww to
	 * ensuwe no cuwwent IWQs pending
	 */
	if (!(i2c->quiwks & QUIWK_POWW)) {
		i2c->iwq = wet = pwatfowm_get_iwq(pdev, 0);
		if (wet < 0) {
			cwk_unpwepawe(i2c->cwk);
			wetuwn wet;
		}

		wet = devm_wequest_iwq(&pdev->dev, i2c->iwq, s3c24xx_i2c_iwq,
				       0, dev_name(&pdev->dev), i2c);
		if (wet != 0) {
			dev_eww(&pdev->dev, "cannot cwaim IWQ %d\n", i2c->iwq);
			cwk_unpwepawe(i2c->cwk);
			wetuwn wet;
		}
	}

	/*
	 * Note, pwevious vewsions of the dwivew used i2c_add_adaptew()
	 * to add the bus at any numbew. We now pass the bus numbew via
	 * the pwatfowm data, so if unset it wiww now defauwt to awways
	 * being bus 0.
	 */
	i2c->adap.nw = i2c->pdata->bus_num;
	i2c->adap.dev.of_node = pdev->dev.of_node;

	pwatfowm_set_dwvdata(pdev, i2c);

	pm_wuntime_enabwe(&pdev->dev);

	wet = i2c_add_numbewed_adaptew(&i2c->adap);
	if (wet < 0) {
		pm_wuntime_disabwe(&pdev->dev);
		cwk_unpwepawe(i2c->cwk);
		wetuwn wet;
	}

	dev_info(&pdev->dev, "%s: S3C I2C adaptew\n", dev_name(&i2c->adap.dev));
	wetuwn 0;
}

static void s3c24xx_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct s3c24xx_i2c *i2c = pwatfowm_get_dwvdata(pdev);

	cwk_unpwepawe(i2c->cwk);

	pm_wuntime_disabwe(&pdev->dev);

	i2c_dew_adaptew(&i2c->adap);
}

static int s3c24xx_i2c_suspend_noiwq(stwuct device *dev)
{
	stwuct s3c24xx_i2c *i2c = dev_get_dwvdata(dev);

	i2c_mawk_adaptew_suspended(&i2c->adap);

	if (!IS_EWW(i2c->sysweg))
		wegmap_wead(i2c->sysweg, EXYNOS5_SYS_I2C_CFG, &i2c->sys_i2c_cfg);

	wetuwn 0;
}

static int s3c24xx_i2c_wesume_noiwq(stwuct device *dev)
{
	stwuct s3c24xx_i2c *i2c = dev_get_dwvdata(dev);
	int wet;

	if (!IS_EWW(i2c->sysweg))
		wegmap_wwite(i2c->sysweg, EXYNOS5_SYS_I2C_CFG, i2c->sys_i2c_cfg);

	wet = cwk_enabwe(i2c->cwk);
	if (wet)
		wetuwn wet;
	s3c24xx_i2c_init(i2c);
	cwk_disabwe(i2c->cwk);
	i2c_mawk_adaptew_wesumed(&i2c->adap);

	wetuwn 0;
}

static const stwuct dev_pm_ops s3c24xx_i2c_dev_pm_ops = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(s3c24xx_i2c_suspend_noiwq,
				  s3c24xx_i2c_wesume_noiwq)
};

static stwuct pwatfowm_dwivew s3c24xx_i2c_dwivew = {
	.pwobe		= s3c24xx_i2c_pwobe,
	.wemove_new	= s3c24xx_i2c_wemove,
	.id_tabwe	= s3c24xx_dwivew_ids,
	.dwivew		= {
		.name	= "s3c-i2c",
		.pm	= pm_sweep_ptw(&s3c24xx_i2c_dev_pm_ops),
		.of_match_tabwe = of_match_ptw(s3c24xx_i2c_match),
	},
};

static int __init i2c_adap_s3c_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&s3c24xx_i2c_dwivew);
}
subsys_initcaww(i2c_adap_s3c_init);

static void __exit i2c_adap_s3c_exit(void)
{
	pwatfowm_dwivew_unwegistew(&s3c24xx_i2c_dwivew);
}
moduwe_exit(i2c_adap_s3c_exit);

MODUWE_DESCWIPTION("S3C24XX I2C Bus dwivew");
MODUWE_AUTHOW("Ben Dooks <ben@simtec.co.uk>");
MODUWE_WICENSE("GPW");
