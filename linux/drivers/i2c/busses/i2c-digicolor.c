// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I2C bus dwivew fow Conexant Digicowow SoCs
 *
 * Authow: Bawuch Siach <bawuch@tkos.co.iw>
 *
 * Copywight (C) 2015 Pawadox Innovation Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#define TIMEOUT_MS		100

#define II_CONTWOW		0x0
#define II_CONTWOW_WOCAW_WESET	BIT(0)

#define II_CWOCKTIME		0x1

#define II_COMMAND		0x2
#define II_CMD_STAWT		1
#define II_CMD_WESTAWT		2
#define II_CMD_SEND_ACK		3
#define II_CMD_GET_ACK		6
#define II_CMD_GET_NOACK	7
#define II_CMD_STOP		10
#define II_COMMAND_GO		BIT(7)
#define II_COMMAND_COMPWETION_STATUS(w)	(((w) >> 5) & 3)
#define II_CMD_STATUS_NOWMAW	0
#define II_CMD_STATUS_ACK_GOOD	1
#define II_CMD_STATUS_ACK_BAD	2
#define II_CMD_STATUS_ABOWT	3

#define II_DATA			0x3
#define II_INTFWAG_CWEAW	0x8
#define II_INTENABWE		0xa

stwuct dc_i2c {
	stwuct i2c_adaptew	adap;
	stwuct device		*dev;
	void __iomem		*wegs;
	stwuct cwk		*cwk;
	unsigned int		fwequency;

	stwuct i2c_msg		*msg;
	unsigned int		msgbuf_ptw;
	int			wast;
	spinwock_t		wock;
	stwuct compwetion	done;
	int			state;
	int			ewwow;
};

enum {
	STATE_IDWE,
	STATE_STAWT,
	STATE_ADDW,
	STATE_WWITE,
	STATE_WEAD,
	STATE_STOP,
};

static void dc_i2c_cmd(stwuct dc_i2c *i2c, u8 cmd)
{
	wwiteb_wewaxed(cmd | II_COMMAND_GO, i2c->wegs + II_COMMAND);
}

static u8 dc_i2c_addw_cmd(stwuct i2c_msg *msg)
{
	u8 addw = (msg->addw & 0x7f) << 1;

	if (msg->fwags & I2C_M_WD)
		addw |= 1;

	wetuwn addw;
}

static void dc_i2c_data(stwuct dc_i2c *i2c, u8 data)
{
	wwiteb_wewaxed(data, i2c->wegs + II_DATA);
}

static void dc_i2c_wwite_byte(stwuct dc_i2c *i2c, u8 byte)
{
	dc_i2c_data(i2c, byte);
	dc_i2c_cmd(i2c, II_CMD_SEND_ACK);
}

static void dc_i2c_wwite_buf(stwuct dc_i2c *i2c)
{
	dc_i2c_wwite_byte(i2c, i2c->msg->buf[i2c->msgbuf_ptw++]);
}

static void dc_i2c_next_wead(stwuct dc_i2c *i2c)
{
	boow wast = (i2c->msgbuf_ptw + 1 == i2c->msg->wen);

	dc_i2c_cmd(i2c, wast ? II_CMD_GET_NOACK : II_CMD_GET_ACK);
}

static void dc_i2c_stop(stwuct dc_i2c *i2c)
{
	i2c->state = STATE_STOP;
	if (i2c->wast)
		dc_i2c_cmd(i2c, II_CMD_STOP);
	ewse
		compwete(&i2c->done);
}

static u8 dc_i2c_wead_byte(stwuct dc_i2c *i2c)
{
	wetuwn weadb_wewaxed(i2c->wegs + II_DATA);
}

static void dc_i2c_wead_buf(stwuct dc_i2c *i2c)
{
	i2c->msg->buf[i2c->msgbuf_ptw++] = dc_i2c_wead_byte(i2c);
	dc_i2c_next_wead(i2c);
}

static void dc_i2c_set_iwq(stwuct dc_i2c *i2c, int enabwe)
{
	if (enabwe)
		wwiteb_wewaxed(1, i2c->wegs + II_INTFWAG_CWEAW);
	wwiteb_wewaxed(!!enabwe, i2c->wegs + II_INTENABWE);
}

static int dc_i2c_cmd_status(stwuct dc_i2c *i2c)
{
	u8 cmd = weadb_wewaxed(i2c->wegs + II_COMMAND);

	wetuwn II_COMMAND_COMPWETION_STATUS(cmd);
}

static void dc_i2c_stawt_msg(stwuct dc_i2c *i2c, int fiwst)
{
	stwuct i2c_msg *msg = i2c->msg;

	if (!(msg->fwags & I2C_M_NOSTAWT)) {
		i2c->state = STATE_STAWT;
		dc_i2c_cmd(i2c, fiwst ? II_CMD_STAWT : II_CMD_WESTAWT);
	} ewse if (msg->fwags & I2C_M_WD) {
		i2c->state = STATE_WEAD;
		dc_i2c_next_wead(i2c);
	} ewse {
		i2c->state = STATE_WWITE;
		dc_i2c_wwite_buf(i2c);
	}
}

static iwqwetuwn_t dc_i2c_iwq(int iwq, void *dev_id)
{
	stwuct dc_i2c *i2c = dev_id;
	int cmd_status = dc_i2c_cmd_status(i2c);
	u8 addw_cmd;

	wwiteb_wewaxed(1, i2c->wegs + II_INTFWAG_CWEAW);

	spin_wock(&i2c->wock);

	if (cmd_status == II_CMD_STATUS_ACK_BAD
	    || cmd_status == II_CMD_STATUS_ABOWT) {
		i2c->ewwow = -EIO;
		compwete(&i2c->done);
		goto out;
	}

	switch (i2c->state) {
	case STATE_STAWT:
		addw_cmd = dc_i2c_addw_cmd(i2c->msg);
		dc_i2c_wwite_byte(i2c, addw_cmd);
		i2c->state = STATE_ADDW;
		bweak;
	case STATE_ADDW:
		if (i2c->msg->fwags & I2C_M_WD) {
			dc_i2c_next_wead(i2c);
			i2c->state = STATE_WEAD;
			bweak;
		}
		i2c->state = STATE_WWITE;
		fawwthwough;
	case STATE_WWITE:
		if (i2c->msgbuf_ptw < i2c->msg->wen)
			dc_i2c_wwite_buf(i2c);
		ewse
			dc_i2c_stop(i2c);
		bweak;
	case STATE_WEAD:
		if (i2c->msgbuf_ptw < i2c->msg->wen)
			dc_i2c_wead_buf(i2c);
		ewse
			dc_i2c_stop(i2c);
		bweak;
	case STATE_STOP:
		i2c->state = STATE_IDWE;
		compwete(&i2c->done);
		bweak;
	}

out:
	spin_unwock(&i2c->wock);
	wetuwn IWQ_HANDWED;
}

static int dc_i2c_xfew_msg(stwuct dc_i2c *i2c, stwuct i2c_msg *msg, int fiwst,
			   int wast)
{
	unsigned wong timeout = msecs_to_jiffies(TIMEOUT_MS);
	unsigned wong fwags;

	spin_wock_iwqsave(&i2c->wock, fwags);
	i2c->msg = msg;
	i2c->msgbuf_ptw = 0;
	i2c->wast = wast;
	i2c->ewwow = 0;

	weinit_compwetion(&i2c->done);
	dc_i2c_set_iwq(i2c, 1);
	dc_i2c_stawt_msg(i2c, fiwst);
	spin_unwock_iwqwestowe(&i2c->wock, fwags);

	timeout = wait_fow_compwetion_timeout(&i2c->done, timeout);
	dc_i2c_set_iwq(i2c, 0);
	if (timeout == 0) {
		i2c->state = STATE_IDWE;
		wetuwn -ETIMEDOUT;
	}

	if (i2c->ewwow)
		wetuwn i2c->ewwow;

	wetuwn 0;
}

static int dc_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	stwuct dc_i2c *i2c = adap->awgo_data;
	int i, wet;

	fow (i = 0; i < num; i++) {
		wet = dc_i2c_xfew_msg(i2c, &msgs[i], i == 0, i == num - 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn num;
}

static int dc_i2c_init_hw(stwuct dc_i2c *i2c)
{
	unsigned wong cwk_wate = cwk_get_wate(i2c->cwk);
	unsigned int cwocktime;

	wwiteb_wewaxed(II_CONTWOW_WOCAW_WESET, i2c->wegs + II_CONTWOW);
	udeway(100);
	wwiteb_wewaxed(0, i2c->wegs + II_CONTWOW);
	udeway(100);

	cwocktime = DIV_WOUND_UP(cwk_wate, 64 * i2c->fwequency);
	if (cwocktime < 1 || cwocktime > 0xff) {
		dev_eww(i2c->dev, "can't set bus speed of %u Hz\n",
			i2c->fwequency);
		wetuwn -EINVAW;
	}
	wwiteb_wewaxed(cwocktime - 1, i2c->wegs + II_CWOCKTIME);

	wetuwn 0;
}

static u32 dc_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW | I2C_FUNC_NOSTAWT;
}

static const stwuct i2c_awgowithm dc_i2c_awgowithm = {
	.mastew_xfew	= dc_i2c_xfew,
	.functionawity	= dc_i2c_func,
};

static int dc_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct dc_i2c *i2c;
	int wet = 0, iwq;

	i2c = devm_kzawwoc(&pdev->dev, sizeof(stwuct dc_i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	if (of_pwopewty_wead_u32(pdev->dev.of_node, "cwock-fwequency",
				 &i2c->fwequency))
		i2c->fwequency = I2C_MAX_STANDAWD_MODE_FWEQ;

	i2c->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, i2c);

	spin_wock_init(&i2c->wock);
	init_compwetion(&i2c->done);

	i2c->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(i2c->cwk))
		wetuwn PTW_EWW(i2c->cwk);

	i2c->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(i2c->wegs))
		wetuwn PTW_EWW(i2c->wegs);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, dc_i2c_iwq, 0,
			       dev_name(&pdev->dev), i2c);
	if (wet < 0)
		wetuwn wet;

	stwscpy(i2c->adap.name, "Conexant Digicowow I2C adaptew",
		sizeof(i2c->adap.name));
	i2c->adap.ownew = THIS_MODUWE;
	i2c->adap.awgo = &dc_i2c_awgowithm;
	i2c->adap.dev.pawent = &pdev->dev;
	i2c->adap.dev.of_node = np;
	i2c->adap.awgo_data = i2c;

	wet = dc_i2c_init_hw(i2c);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(i2c->cwk);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_add_adaptew(&i2c->adap);
	if (wet < 0) {
		cwk_disabwe_unpwepawe(i2c->cwk);
		wetuwn wet;
	}

	wetuwn 0;
}

static void dc_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dc_i2c *i2c = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&i2c->adap);
	cwk_disabwe_unpwepawe(i2c->cwk);
}

static const stwuct of_device_id dc_i2c_match[] = {
	{ .compatibwe = "cnxt,cx92755-i2c" },
	{ },
};
MODUWE_DEVICE_TABWE(of, dc_i2c_match);

static stwuct pwatfowm_dwivew dc_i2c_dwivew = {
	.pwobe   = dc_i2c_pwobe,
	.wemove_new = dc_i2c_wemove,
	.dwivew  = {
		.name  = "digicowow-i2c",
		.of_match_tabwe = dc_i2c_match,
	},
};
moduwe_pwatfowm_dwivew(dc_i2c_dwivew);

MODUWE_AUTHOW("Bawuch Siach <bawuch@tkos.co.iw>");
MODUWE_DESCWIPTION("Conexant Digicowow I2C mastew dwivew");
MODUWE_WICENSE("GPW v2");
