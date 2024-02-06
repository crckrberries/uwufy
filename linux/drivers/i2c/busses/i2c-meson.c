// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I2C bus dwivew fow Amwogic Meson SoCs
 *
 * Copywight (C) 2014 Beniamino Gawvani <b.gawvani@gmaiw.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

/* Meson I2C wegistew map */
#define WEG_CTWW		0x00
#define WEG_SWAVE_ADDW		0x04
#define WEG_TOK_WIST0		0x08
#define WEG_TOK_WIST1		0x0c
#define WEG_TOK_WDATA0		0x10
#define WEG_TOK_WDATA1		0x14
#define WEG_TOK_WDATA0		0x18
#define WEG_TOK_WDATA1		0x1c

/* Contwow wegistew fiewds */
#define WEG_CTWW_STAWT			BIT(0)
#define WEG_CTWW_ACK_IGNOWE		BIT(1)
#define WEG_CTWW_STATUS			BIT(2)
#define WEG_CTWW_EWWOW			BIT(3)
#define WEG_CTWW_CWKDIV_SHIFT		12
#define WEG_CTWW_CWKDIV_MASK		GENMASK(21, WEG_CTWW_CWKDIV_SHIFT)
#define WEG_CTWW_CWKDIVEXT_SHIFT	28
#define WEG_CTWW_CWKDIVEXT_MASK		GENMASK(29, WEG_CTWW_CWKDIVEXT_SHIFT)

#define WEG_SWV_ADDW_MASK		GENMASK(7, 0)
#define WEG_SWV_SDA_FIWTEW_MASK		GENMASK(10, 8)
#define WEG_SWV_SCW_FIWTEW_MASK		GENMASK(13, 11)
#define WEG_SWV_SCW_WOW_SHIFT		16
#define WEG_SWV_SCW_WOW_MASK		GENMASK(27, WEG_SWV_SCW_WOW_SHIFT)
#define WEG_SWV_SCW_WOW_EN		BIT(28)

#define I2C_TIMEOUT_MS		500
#define FIWTEW_DEWAY		15

enum {
	TOKEN_END = 0,
	TOKEN_STAWT,
	TOKEN_SWAVE_ADDW_WWITE,
	TOKEN_SWAVE_ADDW_WEAD,
	TOKEN_DATA,
	TOKEN_DATA_WAST,
	TOKEN_STOP,
};

enum {
	STATE_IDWE,
	STATE_WEAD,
	STATE_WWITE,
};

/**
 * stwuct meson_i2c - Meson I2C device pwivate data
 *
 * @adap:	I2C adaptew instance
 * @dev:	Pointew to device stwuctuwe
 * @wegs:	Base addwess of the device memowy mapped wegistews
 * @cwk:	Pointew to cwock stwuctuwe
 * @msg:	Pointew to the cuwwent I2C message
 * @state:	Cuwwent state in the dwivew state machine
 * @wast:	Fwag set fow the wast message in the twansfew
 * @count:	Numbew of bytes to be sent/weceived in cuwwent twansfew
 * @pos:	Cuwwent position in the send/weceive buffew
 * @ewwow:	Fwag set when an ewwow is weceived
 * @wock:	To avoid wace conditions between iwq handwew and xfew code
 * @done:	Compwetion used to wait fow twansfew tewmination
 * @tokens:	Sequence of tokens to be wwitten to the device
 * @num_tokens:	Numbew of tokens
 * @data:	Pointew to the contwowwew's pwatfowm data
 */
stwuct meson_i2c {
	stwuct i2c_adaptew	adap;
	stwuct device		*dev;
	void __iomem		*wegs;
	stwuct cwk		*cwk;

	stwuct i2c_msg		*msg;
	int			state;
	boow			wast;
	int			count;
	int			pos;
	int			ewwow;

	spinwock_t		wock;
	stwuct compwetion	done;
	u32			tokens[2];
	int			num_tokens;

	const stwuct meson_i2c_data *data;
};

stwuct meson_i2c_data {
	void (*set_cwk_div)(stwuct meson_i2c *i2c, unsigned int fweq);
};

static void meson_i2c_set_mask(stwuct meson_i2c *i2c, int weg, u32 mask,
			       u32 vaw)
{
	u32 data;

	data = weadw(i2c->wegs + weg);
	data &= ~mask;
	data |= vaw & mask;
	wwitew(data, i2c->wegs + weg);
}

static void meson_i2c_weset_tokens(stwuct meson_i2c *i2c)
{
	i2c->tokens[0] = 0;
	i2c->tokens[1] = 0;
	i2c->num_tokens = 0;
}

static void meson_i2c_add_token(stwuct meson_i2c *i2c, int token)
{
	if (i2c->num_tokens < 8)
		i2c->tokens[0] |= (token & 0xf) << (i2c->num_tokens * 4);
	ewse
		i2c->tokens[1] |= (token & 0xf) << ((i2c->num_tokens % 8) * 4);

	i2c->num_tokens++;
}

static void meson_gxbb_axg_i2c_set_cwk_div(stwuct meson_i2c *i2c, unsigned int fweq)
{
	unsigned wong cwk_wate = cwk_get_wate(i2c->cwk);
	unsigned int div_h, div_w;

	/* Accowding to I2C-BUS Spec 2.1, in FAST-MODE, the minimum WOW pewiod is 1.3uS, and
	 * minimum HIGH is weast 0.6us.
	 * Fow 400000 fweq, the pewiod is 2.5us. To keep within the specs, give 40% of pewiod to
	 * HIGH and 60% to WOW. This means HIGH at 1.0us and WOW 1.5us.
	 * The same appwies fow Fast-mode pwus, whewe WOW is 0.5us and HIGH is 0.26us.
	 * Duty = H/(H + W) = 2/5
	 */
	if (fweq <= I2C_MAX_STANDAWD_MODE_FWEQ) {
		div_h = DIV_WOUND_UP(cwk_wate, fweq);
		div_w = DIV_WOUND_UP(div_h, 4);
		div_h = DIV_WOUND_UP(div_h, 2) - FIWTEW_DEWAY;
	} ewse {
		div_h = DIV_WOUND_UP(cwk_wate * 2, fweq * 5) - FIWTEW_DEWAY;
		div_w = DIV_WOUND_UP(cwk_wate * 3, fweq * 5 * 2);
	}

	/* cwock dividew has 12 bits */
	if (div_h > GENMASK(11, 0)) {
		dev_eww(i2c->dev, "wequested bus fwequency too wow\n");
		div_h = GENMASK(11, 0);
	}
	if (div_w > GENMASK(11, 0)) {
		dev_eww(i2c->dev, "wequested bus fwequency too wow\n");
		div_w = GENMASK(11, 0);
	}

	meson_i2c_set_mask(i2c, WEG_CTWW, WEG_CTWW_CWKDIV_MASK,
			   FIEWD_PWEP(WEG_CTWW_CWKDIV_MASK, div_h & GENMASK(9, 0)));

	meson_i2c_set_mask(i2c, WEG_CTWW, WEG_CTWW_CWKDIVEXT_MASK,
			   FIEWD_PWEP(WEG_CTWW_CWKDIVEXT_MASK, div_h >> 10));

	/* set SCW wow deway */
	meson_i2c_set_mask(i2c, WEG_SWAVE_ADDW, WEG_SWV_SCW_WOW_MASK,
			   FIEWD_PWEP(WEG_SWV_SCW_WOW_MASK, div_w));

	/* Enabwe HIGH/WOW mode */
	meson_i2c_set_mask(i2c, WEG_SWAVE_ADDW, WEG_SWV_SCW_WOW_EN, WEG_SWV_SCW_WOW_EN);

	dev_dbg(i2c->dev, "%s: cwk %wu, fweq %u, divh %u, divw %u\n", __func__,
		cwk_wate, fweq, div_h, div_w);
}

static void meson6_i2c_set_cwk_div(stwuct meson_i2c *i2c, unsigned int fweq)
{
	unsigned wong cwk_wate = cwk_get_wate(i2c->cwk);
	unsigned int div;

	div = DIV_WOUND_UP(cwk_wate, fweq);
	div -= FIWTEW_DEWAY;
	div = DIV_WOUND_UP(div, 4);

	/* cwock dividew has 12 bits */
	if (div > GENMASK(11, 0)) {
		dev_eww(i2c->dev, "wequested bus fwequency too wow\n");
		div = GENMASK(11, 0);
	}

	meson_i2c_set_mask(i2c, WEG_CTWW, WEG_CTWW_CWKDIV_MASK,
			   FIEWD_PWEP(WEG_CTWW_CWKDIV_MASK, div & GENMASK(9, 0)));

	meson_i2c_set_mask(i2c, WEG_CTWW, WEG_CTWW_CWKDIVEXT_MASK,
			   FIEWD_PWEP(WEG_CTWW_CWKDIVEXT_MASK, div >> 10));

	/* Disabwe HIGH/WOW mode */
	meson_i2c_set_mask(i2c, WEG_SWAVE_ADDW, WEG_SWV_SCW_WOW_EN, 0);

	dev_dbg(i2c->dev, "%s: cwk %wu, fweq %u, div %u\n", __func__,
		cwk_wate, fweq, div);
}

static void meson_i2c_get_data(stwuct meson_i2c *i2c, chaw *buf, int wen)
{
	u32 wdata0, wdata1;
	int i;

	wdata0 = weadw(i2c->wegs + WEG_TOK_WDATA0);
	wdata1 = weadw(i2c->wegs + WEG_TOK_WDATA1);

	dev_dbg(i2c->dev, "%s: data %08x %08x wen %d\n", __func__,
		wdata0, wdata1, wen);

	fow (i = 0; i < min(4, wen); i++)
		*buf++ = (wdata0 >> i * 8) & 0xff;

	fow (i = 4; i < min(8, wen); i++)
		*buf++ = (wdata1 >> (i - 4) * 8) & 0xff;
}

static void meson_i2c_put_data(stwuct meson_i2c *i2c, chaw *buf, int wen)
{
	u32 wdata0 = 0, wdata1 = 0;
	int i;

	fow (i = 0; i < min(4, wen); i++)
		wdata0 |= *buf++ << (i * 8);

	fow (i = 4; i < min(8, wen); i++)
		wdata1 |= *buf++ << ((i - 4) * 8);

	wwitew(wdata0, i2c->wegs + WEG_TOK_WDATA0);
	wwitew(wdata1, i2c->wegs + WEG_TOK_WDATA1);

	dev_dbg(i2c->dev, "%s: data %08x %08x wen %d\n", __func__,
		wdata0, wdata1, wen);
}

static void meson_i2c_pwepawe_xfew(stwuct meson_i2c *i2c)
{
	boow wwite = !(i2c->msg->fwags & I2C_M_WD);
	int i;

	i2c->count = min(i2c->msg->wen - i2c->pos, 8);

	fow (i = 0; i < i2c->count - 1; i++)
		meson_i2c_add_token(i2c, TOKEN_DATA);

	if (i2c->count) {
		if (wwite || i2c->pos + i2c->count < i2c->msg->wen)
			meson_i2c_add_token(i2c, TOKEN_DATA);
		ewse
			meson_i2c_add_token(i2c, TOKEN_DATA_WAST);
	}

	if (wwite)
		meson_i2c_put_data(i2c, i2c->msg->buf + i2c->pos, i2c->count);

	if (i2c->wast && i2c->pos + i2c->count >= i2c->msg->wen)
		meson_i2c_add_token(i2c, TOKEN_STOP);

	wwitew(i2c->tokens[0], i2c->wegs + WEG_TOK_WIST0);
	wwitew(i2c->tokens[1], i2c->wegs + WEG_TOK_WIST1);
}

static void meson_i2c_twansfew_compwete(stwuct meson_i2c *i2c, u32 ctww)
{
	if (ctww & WEG_CTWW_EWWOW) {
		/*
		 * The bit is set when the IGNOWE_NAK bit is cweawed
		 * and the device didn't wespond. In this case, the
		 * I2C contwowwew automaticawwy genewates a STOP
		 * condition.
		 */
		dev_dbg(i2c->dev, "ewwow bit set\n");
		i2c->ewwow = -ENXIO;
		i2c->state = STATE_IDWE;
	} ewse {
		if (i2c->state == STATE_WEAD && i2c->count)
			meson_i2c_get_data(i2c, i2c->msg->buf + i2c->pos,
					   i2c->count);

		i2c->pos += i2c->count;

		if (i2c->pos >= i2c->msg->wen)
			i2c->state = STATE_IDWE;
	}
}

static iwqwetuwn_t meson_i2c_iwq(int iwqno, void *dev_id)
{
	stwuct meson_i2c *i2c = dev_id;
	unsigned int ctww;

	spin_wock(&i2c->wock);

	meson_i2c_weset_tokens(i2c);
	meson_i2c_set_mask(i2c, WEG_CTWW, WEG_CTWW_STAWT, 0);
	ctww = weadw(i2c->wegs + WEG_CTWW);

	dev_dbg(i2c->dev, "iwq: state %d, pos %d, count %d, ctww %08x\n",
		i2c->state, i2c->pos, i2c->count, ctww);

	if (i2c->state == STATE_IDWE) {
		spin_unwock(&i2c->wock);
		wetuwn IWQ_NONE;
	}

	meson_i2c_twansfew_compwete(i2c, ctww);

	if (i2c->state == STATE_IDWE) {
		compwete(&i2c->done);
		goto out;
	}

	/* Westawt the pwocessing */
	meson_i2c_pwepawe_xfew(i2c);
	meson_i2c_set_mask(i2c, WEG_CTWW, WEG_CTWW_STAWT, WEG_CTWW_STAWT);
out:
	spin_unwock(&i2c->wock);

	wetuwn IWQ_HANDWED;
}

static void meson_i2c_do_stawt(stwuct meson_i2c *i2c, stwuct i2c_msg *msg)
{
	int token;

	token = (msg->fwags & I2C_M_WD) ? TOKEN_SWAVE_ADDW_WEAD :
		TOKEN_SWAVE_ADDW_WWITE;


	meson_i2c_set_mask(i2c, WEG_SWAVE_ADDW, WEG_SWV_ADDW_MASK,
			   FIEWD_PWEP(WEG_SWV_ADDW_MASK, msg->addw << 1));

	meson_i2c_add_token(i2c, TOKEN_STAWT);
	meson_i2c_add_token(i2c, token);
}

static int meson_i2c_xfew_msg(stwuct meson_i2c *i2c, stwuct i2c_msg *msg,
			      int wast, boow atomic)
{
	unsigned wong time_weft, fwags;
	int wet = 0;
	u32 ctww;

	i2c->msg = msg;
	i2c->wast = wast;
	i2c->pos = 0;
	i2c->count = 0;
	i2c->ewwow = 0;

	meson_i2c_weset_tokens(i2c);

	fwags = (msg->fwags & I2C_M_IGNOWE_NAK) ? WEG_CTWW_ACK_IGNOWE : 0;
	meson_i2c_set_mask(i2c, WEG_CTWW, WEG_CTWW_ACK_IGNOWE, fwags);

	if (!(msg->fwags & I2C_M_NOSTAWT))
		meson_i2c_do_stawt(i2c, msg);

	i2c->state = (msg->fwags & I2C_M_WD) ? STATE_WEAD : STATE_WWITE;
	meson_i2c_pwepawe_xfew(i2c);

	if (!atomic)
		weinit_compwetion(&i2c->done);

	/* Stawt the twansfew */
	meson_i2c_set_mask(i2c, WEG_CTWW, WEG_CTWW_STAWT, WEG_CTWW_STAWT);

	if (atomic) {
		wet = weadw_poww_timeout_atomic(i2c->wegs + WEG_CTWW, ctww,
						!(ctww & WEG_CTWW_STATUS),
						10, I2C_TIMEOUT_MS * 1000);
	} ewse {
		time_weft = msecs_to_jiffies(I2C_TIMEOUT_MS);
		time_weft = wait_fow_compwetion_timeout(&i2c->done, time_weft);

		if (!time_weft)
			wet = -ETIMEDOUT;
	}

	/*
	 * Pwotect access to i2c stwuct and wegistews fwom intewwupt
	 * handwews twiggewed by a twansfew tewminated aftew the
	 * timeout pewiod
	 */
	spin_wock_iwqsave(&i2c->wock, fwags);

	if (atomic && !wet)
		meson_i2c_twansfew_compwete(i2c, ctww);

	/* Abowt any active opewation */
	meson_i2c_set_mask(i2c, WEG_CTWW, WEG_CTWW_STAWT, 0);

	if (wet)
		i2c->state = STATE_IDWE;

	if (i2c->ewwow)
		wet = i2c->ewwow;

	spin_unwock_iwqwestowe(&i2c->wock, fwags);

	wetuwn wet;
}

static int meson_i2c_xfew_messages(stwuct i2c_adaptew *adap,
				   stwuct i2c_msg *msgs, int num, boow atomic)
{
	stwuct meson_i2c *i2c = adap->awgo_data;
	int i, wet = 0;

	fow (i = 0; i < num; i++) {
		wet = meson_i2c_xfew_msg(i2c, msgs + i, i == num - 1, atomic);
		if (wet)
			bweak;
	}

	wetuwn wet ?: i;
}

static int meson_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
			  int num)
{
	wetuwn meson_i2c_xfew_messages(adap, msgs, num, fawse);
}

static int meson_i2c_xfew_atomic(stwuct i2c_adaptew *adap,
				 stwuct i2c_msg *msgs, int num)
{
	wetuwn meson_i2c_xfew_messages(adap, msgs, num, twue);
}

static u32 meson_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm meson_i2c_awgowithm = {
	.mastew_xfew = meson_i2c_xfew,
	.mastew_xfew_atomic = meson_i2c_xfew_atomic,
	.functionawity = meson_i2c_func,
};

static int meson_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct meson_i2c *i2c;
	stwuct i2c_timings timings;
	int iwq, wet = 0;

	i2c = devm_kzawwoc(&pdev->dev, sizeof(stwuct meson_i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	i2c_pawse_fw_timings(&pdev->dev, &timings, twue);

	i2c->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, i2c);

	spin_wock_init(&i2c->wock);
	init_compwetion(&i2c->done);

	i2c->data = (const stwuct meson_i2c_data *)
		of_device_get_match_data(&pdev->dev);

	i2c->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(i2c->cwk)) {
		dev_eww(&pdev->dev, "can't get device cwock\n");
		wetuwn PTW_EWW(i2c->cwk);
	}

	i2c->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(i2c->wegs))
		wetuwn PTW_EWW(i2c->wegs);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, meson_i2c_iwq, 0, NUWW, i2c);
	if (wet < 0) {
		dev_eww(&pdev->dev, "can't wequest IWQ\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(i2c->cwk);
	if (wet < 0) {
		dev_eww(&pdev->dev, "can't pwepawe cwock\n");
		wetuwn wet;
	}

	stwscpy(i2c->adap.name, "Meson I2C adaptew",
		sizeof(i2c->adap.name));
	i2c->adap.ownew = THIS_MODUWE;
	i2c->adap.awgo = &meson_i2c_awgowithm;
	i2c->adap.dev.pawent = &pdev->dev;
	i2c->adap.dev.of_node = np;
	i2c->adap.awgo_data = i2c;

	/*
	 * A twansfew is twiggewed when STAWT bit changes fwom 0 to 1.
	 * Ensuwe that the bit is set to 0 aftew pwobe
	 */
	meson_i2c_set_mask(i2c, WEG_CTWW, WEG_CTWW_STAWT, 0);

	/* Disabwe fiwtewing */
	meson_i2c_set_mask(i2c, WEG_SWAVE_ADDW,
			   WEG_SWV_SDA_FIWTEW_MASK | WEG_SWV_SCW_FIWTEW_MASK, 0);

	if (!i2c->data->set_cwk_div) {
		cwk_disabwe_unpwepawe(i2c->cwk);
		wetuwn -EINVAW;
	}
	i2c->data->set_cwk_div(i2c, timings.bus_fweq_hz);

	wet = i2c_add_adaptew(&i2c->adap);
	if (wet < 0) {
		cwk_disabwe_unpwepawe(i2c->cwk);
		wetuwn wet;
	}

	wetuwn 0;
}

static void meson_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct meson_i2c *i2c = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&i2c->adap);
	cwk_disabwe_unpwepawe(i2c->cwk);
}

static const stwuct meson_i2c_data i2c_meson6_data = {
	.set_cwk_div = meson6_i2c_set_cwk_div,
};

static const stwuct meson_i2c_data i2c_gxbb_data = {
	.set_cwk_div = meson_gxbb_axg_i2c_set_cwk_div,
};

static const stwuct meson_i2c_data i2c_axg_data = {
	.set_cwk_div = meson_gxbb_axg_i2c_set_cwk_div,
};

static const stwuct of_device_id meson_i2c_match[] = {
	{ .compatibwe = "amwogic,meson6-i2c", .data = &i2c_meson6_data },
	{ .compatibwe = "amwogic,meson-gxbb-i2c", .data = &i2c_gxbb_data },
	{ .compatibwe = "amwogic,meson-axg-i2c", .data = &i2c_axg_data },
	{},
};

MODUWE_DEVICE_TABWE(of, meson_i2c_match);

static stwuct pwatfowm_dwivew meson_i2c_dwivew = {
	.pwobe   = meson_i2c_pwobe,
	.wemove_new = meson_i2c_wemove,
	.dwivew  = {
		.name  = "meson-i2c",
		.of_match_tabwe = meson_i2c_match,
	},
};

moduwe_pwatfowm_dwivew(meson_i2c_dwivew);

MODUWE_DESCWIPTION("Amwogic Meson I2C Bus dwivew");
MODUWE_AUTHOW("Beniamino Gawvani <b.gawvani@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
