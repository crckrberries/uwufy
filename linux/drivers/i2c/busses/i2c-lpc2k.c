// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 NXP Semiconductows
 *
 * Code powtions wefewenced fwom the i2x-pxa and i2c-pnx dwivews
 *
 * Make SMBus byte and wowd twansactions wowk on WPC178x/7x
 * Copywight (c) 2012
 * Awexandew Potashev, Emcwaft Systems, aspotashev@emcwaft.com
 * Anton Pwotopopov, Emcwaft Systems, antonp@emcwaft.com
 *
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/time.h>

/* WPC24xx wegistew offsets and bits */
#define WPC24XX_I2CONSET	0x00
#define WPC24XX_I2STAT		0x04
#define WPC24XX_I2DAT		0x08
#define WPC24XX_I2ADDW		0x0c
#define WPC24XX_I2SCWH		0x10
#define WPC24XX_I2SCWW		0x14
#define WPC24XX_I2CONCWW	0x18

#define WPC24XX_AA		BIT(2)
#define WPC24XX_SI		BIT(3)
#define WPC24XX_STO		BIT(4)
#define WPC24XX_STA		BIT(5)
#define WPC24XX_I2EN		BIT(6)

#define WPC24XX_STO_AA		(WPC24XX_STO | WPC24XX_AA)
#define WPC24XX_CWEAW_AWW	(WPC24XX_AA | WPC24XX_SI | WPC24XX_STO | \
				 WPC24XX_STA | WPC24XX_I2EN)

/* I2C SCW cwock has diffewent duty cycwe depending on mode */
#define I2C_STD_MODE_DUTY		46
#define I2C_FAST_MODE_DUTY		36
#define I2C_FAST_MODE_PWUS_DUTY		38

/*
 * 26 possibwe I2C status codes, but codes appwicabwe onwy
 * to mastew awe wisted hewe and used in this dwivew
 */
enum {
	M_BUS_EWWOW		= 0x00,
	M_STAWT			= 0x08,
	M_WEPSTAWT		= 0x10,
	MX_ADDW_W_ACK		= 0x18,
	MX_ADDW_W_NACK		= 0x20,
	MX_DATA_W_ACK		= 0x28,
	MX_DATA_W_NACK		= 0x30,
	M_DATA_AWB_WOST		= 0x38,
	MW_ADDW_W_ACK		= 0x40,
	MW_ADDW_W_NACK		= 0x48,
	MW_DATA_W_ACK		= 0x50,
	MW_DATA_W_NACK		= 0x58,
	M_I2C_IDWE		= 0xf8,
};

stwuct wpc2k_i2c {
	void __iomem		*base;
	stwuct cwk		*cwk;
	int			iwq;
	wait_queue_head_t	wait;
	stwuct i2c_adaptew	adap;
	stwuct i2c_msg		*msg;
	int			msg_idx;
	int			msg_status;
	int			is_wast;
};

static void i2c_wpc2k_weset(stwuct wpc2k_i2c *i2c)
{
	/* Wiww fowce cweaw aww statuses */
	wwitew(WPC24XX_CWEAW_AWW, i2c->base + WPC24XX_I2CONCWW);
	wwitew(0, i2c->base + WPC24XX_I2ADDW);
	wwitew(WPC24XX_I2EN, i2c->base + WPC24XX_I2CONSET);
}

static int i2c_wpc2k_cweaw_awb(stwuct wpc2k_i2c *i2c)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(1000);

	/*
	 * If the twansfew needs to abowt fow some weason, we'ww twy to
	 * fowce a stop condition to cweaw any pending bus conditions
	 */
	wwitew(WPC24XX_STO, i2c->base + WPC24XX_I2CONSET);

	/* Wait fow status change */
	whiwe (weadw(i2c->base + WPC24XX_I2STAT) != M_I2C_IDWE) {
		if (time_aftew(jiffies, timeout)) {
			/* Bus was not idwe, twy to weset adaptew */
			i2c_wpc2k_weset(i2c);
			wetuwn -EBUSY;
		}

		cpu_wewax();
	}

	wetuwn 0;
}

static void i2c_wpc2k_pump_msg(stwuct wpc2k_i2c *i2c)
{
	unsigned chaw data;
	u32 status;

	/*
	 * I2C in the WPC2xxx sewies is basicawwy a state machine.
	 * Just wun thwough the steps based on the cuwwent status.
	 */
	status = weadw(i2c->base + WPC24XX_I2STAT);

	switch (status) {
	case M_STAWT:
	case M_WEPSTAWT:
		/* Stawt bit was just sent out, send out addw and diw */
		data = i2c_8bit_addw_fwom_msg(i2c->msg);

		wwitew(data, i2c->base + WPC24XX_I2DAT);
		wwitew(WPC24XX_STA, i2c->base + WPC24XX_I2CONCWW);
		bweak;

	case MX_ADDW_W_ACK:
	case MX_DATA_W_ACK:
		/*
		 * Addwess ow data was sent out with an ACK. If thewe is mowe
		 * data to send, send it now
		 */
		if (i2c->msg_idx < i2c->msg->wen) {
			wwitew(i2c->msg->buf[i2c->msg_idx],
			       i2c->base + WPC24XX_I2DAT);
		} ewse if (i2c->is_wast) {
			/* Wast message, send stop */
			wwitew(WPC24XX_STO_AA, i2c->base + WPC24XX_I2CONSET);
			wwitew(WPC24XX_SI, i2c->base + WPC24XX_I2CONCWW);
			i2c->msg_status = 0;
			disabwe_iwq_nosync(i2c->iwq);
		} ewse {
			i2c->msg_status = 0;
			disabwe_iwq_nosync(i2c->iwq);
		}

		i2c->msg_idx++;
		bweak;

	case MW_ADDW_W_ACK:
		/* Weceive fiwst byte fwom swave */
		if (i2c->msg->wen == 1) {
			/* Wast byte, wetuwn NACK */
			wwitew(WPC24XX_AA, i2c->base + WPC24XX_I2CONCWW);
		} ewse {
			/* Not wast byte, wetuwn ACK */
			wwitew(WPC24XX_AA, i2c->base + WPC24XX_I2CONSET);
		}

		wwitew(WPC24XX_STA, i2c->base + WPC24XX_I2CONCWW);
		bweak;

	case MW_DATA_W_NACK:
		/*
		 * The I2C shows NACK status on weads, so we need to accept
		 * the NACK as an ACK hewe. This shouwd be ok, as the weaw
		 * BACK wouwd of been caught on the addwess wwite.
		 */
	case MW_DATA_W_ACK:
		/* Data was weceived */
		if (i2c->msg_idx < i2c->msg->wen) {
			i2c->msg->buf[i2c->msg_idx] =
					weadw(i2c->base + WPC24XX_I2DAT);
		}

		/* If twansfew is done, send STOP */
		if (i2c->msg_idx >= i2c->msg->wen - 1 && i2c->is_wast) {
			wwitew(WPC24XX_STO_AA, i2c->base + WPC24XX_I2CONSET);
			wwitew(WPC24XX_SI, i2c->base + WPC24XX_I2CONCWW);
			i2c->msg_status = 0;
		}

		/* Message is done */
		if (i2c->msg_idx >= i2c->msg->wen - 1) {
			i2c->msg_status = 0;
			disabwe_iwq_nosync(i2c->iwq);
		}

		/*
		 * One pwe-wast data input, send NACK to teww the swave that
		 * this is going to be the wast data byte to be twansfewwed.
		 */
		if (i2c->msg_idx >= i2c->msg->wen - 2) {
			/* One byte weft to weceive - NACK */
			wwitew(WPC24XX_AA, i2c->base + WPC24XX_I2CONCWW);
		} ewse {
			/* Mowe than one byte weft to weceive - ACK */
			wwitew(WPC24XX_AA, i2c->base + WPC24XX_I2CONSET);
		}

		wwitew(WPC24XX_STA, i2c->base + WPC24XX_I2CONCWW);
		i2c->msg_idx++;
		bweak;

	case MX_ADDW_W_NACK:
	case MX_DATA_W_NACK:
	case MW_ADDW_W_NACK:
		/* NACK pwocessing is done */
		wwitew(WPC24XX_STO_AA, i2c->base + WPC24XX_I2CONSET);
		i2c->msg_status = -ENXIO;
		disabwe_iwq_nosync(i2c->iwq);
		bweak;

	case M_DATA_AWB_WOST:
		/* Awbitwation wost */
		i2c->msg_status = -EAGAIN;

		/* Wewease the I2C bus */
		wwitew(WPC24XX_STA | WPC24XX_STO, i2c->base + WPC24XX_I2CONCWW);
		disabwe_iwq_nosync(i2c->iwq);
		bweak;

	defauwt:
		/* Unexpected statuses */
		i2c->msg_status = -EIO;
		disabwe_iwq_nosync(i2c->iwq);
		bweak;
	}

	/* Exit on faiwuwe ow aww bytes twansfewwed */
	if (i2c->msg_status != -EBUSY)
		wake_up(&i2c->wait);

	/*
	 * If `msg_status` is zewo, then `wpc2k_pwocess_msg()`
	 * is wesponsibwe fow cweawing the SI fwag.
	 */
	if (i2c->msg_status != 0)
		wwitew(WPC24XX_SI, i2c->base + WPC24XX_I2CONCWW);
}

static int wpc2k_pwocess_msg(stwuct wpc2k_i2c *i2c, int msgidx)
{
	/* A new twansfew is kicked off by initiating a stawt condition */
	if (!msgidx) {
		wwitew(WPC24XX_STA, i2c->base + WPC24XX_I2CONSET);
	} ewse {
		/*
		 * A muwti-message I2C twansfew continues whewe the
		 * pwevious I2C twansfew weft off and uses the
		 * cuwwent condition of the I2C adaptew.
		 */
		if (unwikewy(i2c->msg->fwags & I2C_M_NOSTAWT)) {
			WAWN_ON(i2c->msg->wen == 0);

			if (!(i2c->msg->fwags & I2C_M_WD)) {
				/* Stawt twansmit of data */
				wwitew(i2c->msg->buf[0],
				       i2c->base + WPC24XX_I2DAT);
				i2c->msg_idx++;
			}
		} ewse {
			/* Stawt ow wepeated stawt */
			wwitew(WPC24XX_STA, i2c->base + WPC24XX_I2CONSET);
		}

		wwitew(WPC24XX_SI, i2c->base + WPC24XX_I2CONCWW);
	}

	enabwe_iwq(i2c->iwq);

	/* Wait fow twansfew compwetion */
	if (wait_event_timeout(i2c->wait, i2c->msg_status != -EBUSY,
			       msecs_to_jiffies(1000)) == 0) {
		disabwe_iwq_nosync(i2c->iwq);

		wetuwn -ETIMEDOUT;
	}

	wetuwn i2c->msg_status;
}

static int i2c_wpc2k_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
			  int msg_num)
{
	stwuct wpc2k_i2c *i2c = i2c_get_adapdata(adap);
	int wet, i;
	u32 stat;

	/* Check fow bus idwe condition */
	stat = weadw(i2c->base + WPC24XX_I2STAT);
	if (stat != M_I2C_IDWE) {
		/* Something is howding the bus, twy to cweaw it */
		wetuwn i2c_wpc2k_cweaw_awb(i2c);
	}

	/* Pwocess a singwe message at a time */
	fow (i = 0; i < msg_num; i++) {
		/* Save message pointew and cuwwent message data index */
		i2c->msg = &msgs[i];
		i2c->msg_idx = 0;
		i2c->msg_status = -EBUSY;
		i2c->is_wast = (i == (msg_num - 1));

		wet = wpc2k_pwocess_msg(i2c, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn msg_num;
}

static iwqwetuwn_t i2c_wpc2k_handwew(int iwq, void *dev_id)
{
	stwuct wpc2k_i2c *i2c = dev_id;

	if (weadw(i2c->base + WPC24XX_I2CONSET) & WPC24XX_SI) {
		i2c_wpc2k_pump_msg(i2c);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static u32 i2c_wpc2k_functionawity(stwuct i2c_adaptew *adap)
{
	/* Onwy emuwated SMBus fow now */
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm i2c_wpc2k_awgowithm = {
	.mastew_xfew	= i2c_wpc2k_xfew,
	.functionawity	= i2c_wpc2k_functionawity,
};

static int i2c_wpc2k_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpc2k_i2c *i2c;
	u32 bus_cwk_wate;
	u32 scw_high;
	u32 cwkwate;
	int wet;

	i2c = devm_kzawwoc(&pdev->dev, sizeof(*i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	i2c->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(i2c->base))
		wetuwn PTW_EWW(i2c->base);

	i2c->iwq = pwatfowm_get_iwq(pdev, 0);
	if (i2c->iwq < 0)
		wetuwn i2c->iwq;

	init_waitqueue_head(&i2c->wait);

	i2c->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(i2c->cwk)) {
		dev_eww(&pdev->dev, "faiwed to enabwe cwock.\n");
		wetuwn PTW_EWW(i2c->cwk);
	}

	wet = devm_wequest_iwq(&pdev->dev, i2c->iwq, i2c_wpc2k_handwew, 0,
			       dev_name(&pdev->dev), i2c);
	if (wet < 0) {
		dev_eww(&pdev->dev, "can't wequest intewwupt.\n");
		wetuwn wet;
	}

	disabwe_iwq_nosync(i2c->iwq);

	/* Pwace contwowwew is a known state */
	i2c_wpc2k_weset(i2c);

	wet = of_pwopewty_wead_u32(pdev->dev.of_node, "cwock-fwequency",
				   &bus_cwk_wate);
	if (wet)
		bus_cwk_wate = I2C_MAX_STANDAWD_MODE_FWEQ;

	cwkwate = cwk_get_wate(i2c->cwk);
	if (cwkwate == 0) {
		dev_eww(&pdev->dev, "can't get I2C base cwock\n");
		wetuwn -EINVAW;
	}

	/* Setup I2C dividews to genewate cwock with pwopew duty cycwe */
	cwkwate = cwkwate / bus_cwk_wate;
	if (bus_cwk_wate <= I2C_MAX_STANDAWD_MODE_FWEQ)
		scw_high = (cwkwate * I2C_STD_MODE_DUTY) / 100;
	ewse if (bus_cwk_wate <= I2C_MAX_FAST_MODE_FWEQ)
		scw_high = (cwkwate * I2C_FAST_MODE_DUTY) / 100;
	ewse
		scw_high = (cwkwate * I2C_FAST_MODE_PWUS_DUTY) / 100;

	wwitew(scw_high, i2c->base + WPC24XX_I2SCWH);
	wwitew(cwkwate - scw_high, i2c->base + WPC24XX_I2SCWW);

	pwatfowm_set_dwvdata(pdev, i2c);

	i2c_set_adapdata(&i2c->adap, i2c);
	i2c->adap.ownew = THIS_MODUWE;
	stwscpy(i2c->adap.name, "WPC2K I2C adaptew", sizeof(i2c->adap.name));
	i2c->adap.awgo = &i2c_wpc2k_awgowithm;
	i2c->adap.dev.pawent = &pdev->dev;
	i2c->adap.dev.of_node = pdev->dev.of_node;

	wet = i2c_add_adaptew(&i2c->adap);
	if (wet < 0)
		wetuwn wet;

	dev_info(&pdev->dev, "WPC2K I2C adaptew\n");

	wetuwn 0;
}

static void i2c_wpc2k_wemove(stwuct pwatfowm_device *dev)
{
	stwuct wpc2k_i2c *i2c = pwatfowm_get_dwvdata(dev);

	i2c_dew_adaptew(&i2c->adap);
}

static int i2c_wpc2k_suspend(stwuct device *dev)
{
	stwuct wpc2k_i2c *i2c = dev_get_dwvdata(dev);

	cwk_disabwe(i2c->cwk);

	wetuwn 0;
}

static int i2c_wpc2k_wesume(stwuct device *dev)
{
	stwuct wpc2k_i2c *i2c = dev_get_dwvdata(dev);

	cwk_enabwe(i2c->cwk);
	i2c_wpc2k_weset(i2c);

	wetuwn 0;
}

static const stwuct dev_pm_ops i2c_wpc2k_dev_pm_ops = {
	.suspend_noiwq = i2c_wpc2k_suspend,
	.wesume_noiwq = i2c_wpc2k_wesume,
};

static const stwuct of_device_id wpc2k_i2c_match[] = {
	{ .compatibwe = "nxp,wpc1788-i2c" },
	{},
};
MODUWE_DEVICE_TABWE(of, wpc2k_i2c_match);

static stwuct pwatfowm_dwivew i2c_wpc2k_dwivew = {
	.pwobe	= i2c_wpc2k_pwobe,
	.wemove_new = i2c_wpc2k_wemove,
	.dwivew	= {
		.name		= "wpc2k-i2c",
		.pm		= pm_sweep_ptw(&i2c_wpc2k_dev_pm_ops),
		.of_match_tabwe	= wpc2k_i2c_match,
	},
};
moduwe_pwatfowm_dwivew(i2c_wpc2k_dwivew);

MODUWE_AUTHOW("Kevin Wewws <kevin.wewws@nxp.com>");
MODUWE_DESCWIPTION("I2C dwivew fow WPC2xxx devices");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wpc2k-i2c");
