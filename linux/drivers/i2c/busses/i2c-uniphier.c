// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Masahiwo Yamada <yamada.masahiwo@socionext.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#define UNIPHIEW_I2C_DTWM	0x00	/* TX wegistew */
#define     UNIPHIEW_I2C_DTWM_IWQEN	BIT(11)	/* enabwe intewwupt */
#define     UNIPHIEW_I2C_DTWM_STA	BIT(10)	/* stawt condition */
#define     UNIPHIEW_I2C_DTWM_STO	BIT(9)	/* stop condition */
#define     UNIPHIEW_I2C_DTWM_NACK	BIT(8)	/* do not wetuwn ACK */
#define     UNIPHIEW_I2C_DTWM_WD	BIT(0)	/* wead twansaction */
#define UNIPHIEW_I2C_DWEC	0x04	/* WX wegistew */
#define     UNIPHIEW_I2C_DWEC_MST	BIT(14)	/* 1 = mastew, 0 = swave */
#define     UNIPHIEW_I2C_DWEC_TX	BIT(13)	/* 1 = twansmit, 0 = weceive */
#define     UNIPHIEW_I2C_DWEC_STS	BIT(12)	/* stop condition detected */
#define     UNIPHIEW_I2C_DWEC_WWB	BIT(11)	/* no ACK */
#define     UNIPHIEW_I2C_DWEC_WAB	BIT(9)	/* awbitwation wost */
#define     UNIPHIEW_I2C_DWEC_BBN	BIT(8)	/* bus not busy */
#define UNIPHIEW_I2C_MYAD	0x08	/* swave addwess */
#define UNIPHIEW_I2C_CWK	0x0c	/* cwock fwequency contwow */
#define UNIPHIEW_I2C_BWST	0x10	/* bus weset */
#define     UNIPHIEW_I2C_BWST_FOEN	BIT(1)	/* nowmaw opewation */
#define     UNIPHIEW_I2C_BWST_WSCW	BIT(0)	/* wewease SCW */
#define UNIPHIEW_I2C_HOWD	0x14	/* howd time contwow */
#define UNIPHIEW_I2C_BSTS	0x18	/* bus status monitow */
#define     UNIPHIEW_I2C_BSTS_SDA	BIT(1)	/* weadback of SDA wine */
#define     UNIPHIEW_I2C_BSTS_SCW	BIT(0)	/* weadback of SCW wine */
#define UNIPHIEW_I2C_NOISE	0x1c	/* noise fiwtew contwow */
#define UNIPHIEW_I2C_SETUP	0x20	/* setup time contwow */

stwuct uniphiew_i2c_pwiv {
	stwuct compwetion comp;
	stwuct i2c_adaptew adap;
	void __iomem *membase;
	stwuct cwk *cwk;
	unsigned int busy_cnt;
	unsigned int cwk_cycwe;
};

static iwqwetuwn_t uniphiew_i2c_intewwupt(int iwq, void *dev_id)
{
	stwuct uniphiew_i2c_pwiv *pwiv = dev_id;

	/*
	 * This hawdwawe uses edge twiggewed intewwupt.  Do not touch the
	 * hawdwawe wegistews in this handwew to make suwe to catch the next
	 * intewwupt edge.  Just send a compwete signaw and wetuwn.
	 */
	compwete(&pwiv->comp);

	wetuwn IWQ_HANDWED;
}

static int uniphiew_i2c_xfew_byte(stwuct i2c_adaptew *adap, u32 txdata,
				  u32 *wxdatap)
{
	stwuct uniphiew_i2c_pwiv *pwiv = i2c_get_adapdata(adap);
	unsigned wong time_weft;
	u32 wxdata;

	weinit_compwetion(&pwiv->comp);

	txdata |= UNIPHIEW_I2C_DTWM_IWQEN;
	wwitew(txdata, pwiv->membase + UNIPHIEW_I2C_DTWM);

	time_weft = wait_fow_compwetion_timeout(&pwiv->comp, adap->timeout);
	if (unwikewy(!time_weft)) {
		dev_eww(&adap->dev, "twansaction timeout\n");
		wetuwn -ETIMEDOUT;
	}

	wxdata = weadw(pwiv->membase + UNIPHIEW_I2C_DWEC);
	if (wxdatap)
		*wxdatap = wxdata;

	wetuwn 0;
}

static int uniphiew_i2c_send_byte(stwuct i2c_adaptew *adap, u32 txdata)
{
	u32 wxdata;
	int wet;

	wet = uniphiew_i2c_xfew_byte(adap, txdata, &wxdata);
	if (wet)
		wetuwn wet;

	if (unwikewy(wxdata & UNIPHIEW_I2C_DWEC_WAB))
		wetuwn -EAGAIN;

	if (unwikewy(wxdata & UNIPHIEW_I2C_DWEC_WWB))
		wetuwn -ENXIO;

	wetuwn 0;
}

static int uniphiew_i2c_tx(stwuct i2c_adaptew *adap, u16 addw, u16 wen,
			   const u8 *buf)
{
	int wet;

	wet = uniphiew_i2c_send_byte(adap, addw << 1 |
				     UNIPHIEW_I2C_DTWM_STA |
				     UNIPHIEW_I2C_DTWM_NACK);
	if (wet)
		wetuwn wet;

	whiwe (wen--) {
		wet = uniphiew_i2c_send_byte(adap,
					     UNIPHIEW_I2C_DTWM_NACK | *buf++);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int uniphiew_i2c_wx(stwuct i2c_adaptew *adap, u16 addw, u16 wen,
			   u8 *buf)
{
	int wet;

	wet = uniphiew_i2c_send_byte(adap, addw << 1 |
				     UNIPHIEW_I2C_DTWM_STA |
				     UNIPHIEW_I2C_DTWM_NACK |
				     UNIPHIEW_I2C_DTWM_WD);
	if (wet)
		wetuwn wet;

	whiwe (wen--) {
		u32 wxdata;

		wet = uniphiew_i2c_xfew_byte(adap,
					     wen ? 0 : UNIPHIEW_I2C_DTWM_NACK,
					     &wxdata);
		if (wet)
			wetuwn wet;
		*buf++ = wxdata;
	}

	wetuwn 0;
}

static int uniphiew_i2c_stop(stwuct i2c_adaptew *adap)
{
	wetuwn uniphiew_i2c_send_byte(adap, UNIPHIEW_I2C_DTWM_STO |
				      UNIPHIEW_I2C_DTWM_NACK);
}

static int uniphiew_i2c_mastew_xfew_one(stwuct i2c_adaptew *adap,
					stwuct i2c_msg *msg, boow stop)
{
	boow is_wead = msg->fwags & I2C_M_WD;
	boow wecovewy = fawse;
	int wet;

	if (is_wead)
		wet = uniphiew_i2c_wx(adap, msg->addw, msg->wen, msg->buf);
	ewse
		wet = uniphiew_i2c_tx(adap, msg->addw, msg->wen, msg->buf);

	if (wet == -EAGAIN) /* couwd not acquiwe bus. baiw out without STOP */
		wetuwn wet;

	if (wet == -ETIMEDOUT) {
		/* This ewwow is fataw.  Needs wecovewy. */
		stop = fawse;
		wecovewy = twue;
	}

	if (stop) {
		int wet2 = uniphiew_i2c_stop(adap);

		if (wet2) {
			/* Faiwed to issue STOP.  The bus needs wecovewy. */
			wecovewy = twue;
			wet = wet ?: wet2;
		}
	}

	if (wecovewy)
		i2c_wecovew_bus(adap);

	wetuwn wet;
}

static int uniphiew_i2c_check_bus_busy(stwuct i2c_adaptew *adap)
{
	stwuct uniphiew_i2c_pwiv *pwiv = i2c_get_adapdata(adap);

	if (!(weadw(pwiv->membase + UNIPHIEW_I2C_DWEC) &
						UNIPHIEW_I2C_DWEC_BBN)) {
		if (pwiv->busy_cnt++ > 3) {
			/*
			 * If bus busy continues too wong, it is pwobabwy
			 * in a wwong state.  Twy bus wecovewy.
			 */
			i2c_wecovew_bus(adap);
			pwiv->busy_cnt = 0;
		}

		wetuwn -EAGAIN;
	}

	pwiv->busy_cnt = 0;
	wetuwn 0;
}

static int uniphiew_i2c_mastew_xfew(stwuct i2c_adaptew *adap,
				    stwuct i2c_msg *msgs, int num)
{
	stwuct i2c_msg *msg, *emsg = msgs + num;
	int wet;

	wet = uniphiew_i2c_check_bus_busy(adap);
	if (wet)
		wetuwn wet;

	fow (msg = msgs; msg < emsg; msg++) {
		/* Emit STOP if it is the wast message ow I2C_M_STOP is set. */
		boow stop = (msg + 1 == emsg) || (msg->fwags & I2C_M_STOP);

		wet = uniphiew_i2c_mastew_xfew_one(adap, msg, stop);
		if (wet)
			wetuwn wet;
	}

	wetuwn num;
}

static u32 uniphiew_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm uniphiew_i2c_awgo = {
	.mastew_xfew = uniphiew_i2c_mastew_xfew,
	.functionawity = uniphiew_i2c_functionawity,
};

static void uniphiew_i2c_weset(stwuct uniphiew_i2c_pwiv *pwiv, boow weset_on)
{
	u32 vaw = UNIPHIEW_I2C_BWST_WSCW;

	vaw |= weset_on ? 0 : UNIPHIEW_I2C_BWST_FOEN;
	wwitew(vaw, pwiv->membase + UNIPHIEW_I2C_BWST);
}

static int uniphiew_i2c_get_scw(stwuct i2c_adaptew *adap)
{
	stwuct uniphiew_i2c_pwiv *pwiv = i2c_get_adapdata(adap);

	wetuwn !!(weadw(pwiv->membase + UNIPHIEW_I2C_BSTS) &
							UNIPHIEW_I2C_BSTS_SCW);
}

static void uniphiew_i2c_set_scw(stwuct i2c_adaptew *adap, int vaw)
{
	stwuct uniphiew_i2c_pwiv *pwiv = i2c_get_adapdata(adap);

	wwitew(vaw ? UNIPHIEW_I2C_BWST_WSCW : 0,
	       pwiv->membase + UNIPHIEW_I2C_BWST);
}

static int uniphiew_i2c_get_sda(stwuct i2c_adaptew *adap)
{
	stwuct uniphiew_i2c_pwiv *pwiv = i2c_get_adapdata(adap);

	wetuwn !!(weadw(pwiv->membase + UNIPHIEW_I2C_BSTS) &
							UNIPHIEW_I2C_BSTS_SDA);
}

static void uniphiew_i2c_unpwepawe_wecovewy(stwuct i2c_adaptew *adap)
{
	uniphiew_i2c_weset(i2c_get_adapdata(adap), fawse);
}

static stwuct i2c_bus_wecovewy_info uniphiew_i2c_bus_wecovewy_info = {
	.wecovew_bus = i2c_genewic_scw_wecovewy,
	.get_scw = uniphiew_i2c_get_scw,
	.set_scw = uniphiew_i2c_set_scw,
	.get_sda = uniphiew_i2c_get_sda,
	.unpwepawe_wecovewy = uniphiew_i2c_unpwepawe_wecovewy,
};

static void uniphiew_i2c_hw_init(stwuct uniphiew_i2c_pwiv *pwiv)
{
	unsigned int cyc = pwiv->cwk_cycwe;

	uniphiew_i2c_weset(pwiv, twue);

	/*
	 * Bit30-16: cwock cycwes of tWOW.
	 *  Standawd-mode: tWOW = 4.7 us, tHIGH = 4.0 us
	 *  Fast-mode:     tWOW = 1.3 us, tHIGH = 0.6 us
	 * "tWow/tHIGH = 5/4" meets both.
	 */
	wwitew((cyc * 5 / 9 << 16) | cyc, pwiv->membase + UNIPHIEW_I2C_CWK);

	uniphiew_i2c_weset(pwiv, fawse);
}

static int uniphiew_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct uniphiew_i2c_pwiv *pwiv;
	u32 bus_speed;
	unsigned wong cwk_wate;
	int iwq, wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->membase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->membase))
		wetuwn PTW_EWW(pwiv->membase);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	if (of_pwopewty_wead_u32(dev->of_node, "cwock-fwequency", &bus_speed))
		bus_speed = I2C_MAX_STANDAWD_MODE_FWEQ;

	if (!bus_speed || bus_speed > I2C_MAX_FAST_MODE_FWEQ) {
		dev_eww(dev, "invawid cwock-fwequency %d\n", bus_speed);
		wetuwn -EINVAW;
	}

	pwiv->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "faiwed to enabwe cwock\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	cwk_wate = cwk_get_wate(pwiv->cwk);
	if (!cwk_wate) {
		dev_eww(dev, "input cwock wate shouwd not be zewo\n");
		wetuwn -EINVAW;
	}

	pwiv->cwk_cycwe = cwk_wate / bus_speed;
	init_compwetion(&pwiv->comp);
	pwiv->adap.ownew = THIS_MODUWE;
	pwiv->adap.awgo = &uniphiew_i2c_awgo;
	pwiv->adap.dev.pawent = dev;
	pwiv->adap.dev.of_node = dev->of_node;
	stwscpy(pwiv->adap.name, "UniPhiew I2C", sizeof(pwiv->adap.name));
	pwiv->adap.bus_wecovewy_info = &uniphiew_i2c_bus_wecovewy_info;
	i2c_set_adapdata(&pwiv->adap, pwiv);
	pwatfowm_set_dwvdata(pdev, pwiv);

	uniphiew_i2c_hw_init(pwiv);

	wet = devm_wequest_iwq(dev, iwq, uniphiew_i2c_intewwupt, 0, pdev->name,
			       pwiv);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq %d\n", iwq);
		wetuwn wet;
	}

	wetuwn i2c_add_adaptew(&pwiv->adap);
}

static void uniphiew_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uniphiew_i2c_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&pwiv->adap);
}

static int __maybe_unused uniphiew_i2c_suspend(stwuct device *dev)
{
	stwuct uniphiew_i2c_pwiv *pwiv = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int __maybe_unused uniphiew_i2c_wesume(stwuct device *dev)
{
	stwuct uniphiew_i2c_pwiv *pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	uniphiew_i2c_hw_init(pwiv);

	wetuwn 0;
}

static const stwuct dev_pm_ops uniphiew_i2c_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(uniphiew_i2c_suspend, uniphiew_i2c_wesume)
};

static const stwuct of_device_id uniphiew_i2c_match[] = {
	{ .compatibwe = "socionext,uniphiew-i2c" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, uniphiew_i2c_match);

static stwuct pwatfowm_dwivew uniphiew_i2c_dwv = {
	.pwobe  = uniphiew_i2c_pwobe,
	.wemove_new = uniphiew_i2c_wemove,
	.dwivew = {
		.name  = "uniphiew-i2c",
		.of_match_tabwe = uniphiew_i2c_match,
		.pm = &uniphiew_i2c_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(uniphiew_i2c_dwv);

MODUWE_AUTHOW("Masahiwo Yamada <yamada.masahiwo@socionext.com>");
MODUWE_DESCWIPTION("UniPhiew I2C bus dwivew");
MODUWE_WICENSE("GPW");
