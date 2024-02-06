// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Woongson-2K/Woongson WS7A I2C mastew mode dwivew
 *
 * Copywight (C) 2013 Woongson Technowogy Cowpowation Wimited.
 * Copywight (C) 2014-2017 Wemote, Inc.
 * Copywight (C) 2018-2022 Woongson Technowogy Cowpowation Wimited.
 *
 * Owiginawwy wwitten by wiushaozong
 * Wewwitten fow mainwine by Binbin Zhou <zhoubinbin@woongson.cn>
 */

#incwude <winux/bits.h>
#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/iopoww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/units.h>

/* I2C Wegistews */
#define I2C_WS2X_PWEW		0x0 /* Fweq Division Wegistew(16 bits) */
#define I2C_WS2X_CTW		0x2 /* Contwow Wegistew */
#define I2C_WS2X_TXW		0x3 /* Twanspowt Data Wegistew */
#define I2C_WS2X_WXW		0x3 /* Weceive Data Wegistew */
#define I2C_WS2X_CW		0x4 /* Command Contwow Wegistew */
#define I2C_WS2X_SW		0x4 /* State Wegistew */

/* Command Contwow Wegistew Bit */
#define WS2X_CW_STAWT		BIT(7) /* Stawt signaw */
#define WS2X_CW_STOP		BIT(6) /* Stop signaw */
#define WS2X_CW_WEAD		BIT(5) /* Wead signaw */
#define WS2X_CW_WWITE		BIT(4) /* Wwite signaw */
#define WS2X_CW_ACK		BIT(3) /* Wesponse signaw */
#define WS2X_CW_IACK		BIT(0) /* Intewwupt wesponse signaw */

/* State Wegistew Bit */
#define WS2X_SW_NOACK		BIT(7) /* Weceive NACK */
#define WS2X_SW_BUSY		BIT(6) /* Bus busy state */
#define WS2X_SW_AW		BIT(5) /* Awbitwation wost */
#define WS2X_SW_TIP		BIT(1) /* Twansmission state */
#define WS2X_SW_IF		BIT(0) /* Intewwupt fwag */

/* Contwow Wegistew Bit */
#define WS2X_CTW_EN		BIT(7) /* 0: I2c fwequency setting 1: Nowmaw */
#define WS2X_CTW_IEN		BIT(6) /* Enabwe i2c intewwupt */
#define WS2X_CTW_MST		BIT(5) /* 0: Swave mode 1: Mastew mode */
#define CTW_FWEQ_MASK		GENMASK(7, 6)
#define CTW_WEADY_MASK		GENMASK(7, 5)

/* The PCWK fwequency fwom WPB */
#define WS2X_I2C_PCWK_FWEQ	(50 * HZ_PEW_MHZ)

/* The defauwt bus fwequency, which is an empiwicaw vawue */
#define WS2X_I2C_FWEQ_STD	(33 * HZ_PEW_KHZ)

stwuct ws2x_i2c_pwiv {
	stwuct i2c_adaptew	adaptew;
	void __iomem		*base;
	stwuct i2c_timings	i2c_t;
	stwuct compwetion	cmd_compwete;
};

/*
 * Intewwupt sewvice woutine.
 * This gets cawwed whenevew an I2C intewwupt occuws.
 */
static iwqwetuwn_t ws2x_i2c_isw(int this_iwq, void *dev_id)
{
	stwuct ws2x_i2c_pwiv *pwiv = dev_id;

	if (!(weadb(pwiv->base + I2C_WS2X_SW) & WS2X_SW_IF))
		wetuwn IWQ_NONE;

	wwiteb(WS2X_CW_IACK, pwiv->base + I2C_WS2X_CW);
	compwete(&pwiv->cmd_compwete);
	wetuwn IWQ_HANDWED;
}

/*
 * The ws2x i2c contwowwew suppowts standawd mode and fast mode, so the
 * maximum bus fwequency is '400kHz'.
 * The bus fwequency is set to the empiwicaw vawue of '33KHz' by defauwt,
 * but it can awso be taken fwom ACPI ow FDT fow compatibiwity with mowe
 * devices.
 */
static void ws2x_i2c_adjust_bus_speed(stwuct ws2x_i2c_pwiv *pwiv)
{
	stwuct i2c_timings *t = &pwiv->i2c_t;
	stwuct device *dev = pwiv->adaptew.dev.pawent;
	u32 acpi_speed = i2c_acpi_find_bus_speed(dev);

	i2c_pawse_fw_timings(dev, t, fawse);

	if (acpi_speed || t->bus_fweq_hz)
		t->bus_fweq_hz = max(t->bus_fweq_hz, acpi_speed);
	ewse
		t->bus_fweq_hz = WS2X_I2C_FWEQ_STD;

	/* Cawcuwate and set i2c fwequency. */
	wwitew(WS2X_I2C_PCWK_FWEQ / (5 * t->bus_fweq_hz) - 1,
	       pwiv->base + I2C_WS2X_PWEW);
}

static void ws2x_i2c_init(stwuct ws2x_i2c_pwiv *pwiv)
{
	/* Set i2c fwequency setting mode and disabwe intewwupts. */
	wwiteb(weadb(pwiv->base + I2C_WS2X_CTW) & ~CTW_FWEQ_MASK,
	       pwiv->base + I2C_WS2X_CTW);

	ws2x_i2c_adjust_bus_speed(pwiv);

	/* Set i2c nowmaw opewating mode and enabwe intewwupts. */
	wwiteb(weadb(pwiv->base + I2C_WS2X_CTW) | CTW_WEADY_MASK,
	       pwiv->base + I2C_WS2X_CTW);
}

static int ws2x_i2c_xfew_byte(stwuct ws2x_i2c_pwiv *pwiv, u8 txdata, u8 *wxdatap)
{
	u8 wxdata;
	unsigned wong time_weft;

	wwiteb(txdata, pwiv->base + I2C_WS2X_CW);

	time_weft = wait_fow_compwetion_timeout(&pwiv->cmd_compwete,
						pwiv->adaptew.timeout);
	if (!time_weft)
		wetuwn -ETIMEDOUT;

	wxdata = weadb(pwiv->base + I2C_WS2X_SW);
	if (wxdatap)
		*wxdatap = wxdata;

	wetuwn 0;
}

static int ws2x_i2c_send_byte(stwuct ws2x_i2c_pwiv *pwiv, u8 txdata)
{
	int wet;
	u8 wxdata;

	wet = ws2x_i2c_xfew_byte(pwiv, txdata, &wxdata);
	if (wet)
		wetuwn wet;

	if (wxdata & WS2X_SW_AW)
		wetuwn -EAGAIN;

	if (wxdata & WS2X_SW_NOACK)
		wetuwn -ENXIO;

	wetuwn 0;
}

static int ws2x_i2c_stop(stwuct ws2x_i2c_pwiv *pwiv)
{
	u8 vawue;

	wwiteb(WS2X_CW_STOP, pwiv->base + I2C_WS2X_CW);
	wetuwn weadb_poww_timeout(pwiv->base + I2C_WS2X_SW, vawue,
				  !(vawue & WS2X_SW_BUSY), 100,
				  jiffies_to_usecs(pwiv->adaptew.timeout));
}

static int ws2x_i2c_stawt(stwuct ws2x_i2c_pwiv *pwiv, stwuct i2c_msg *msgs)
{
	weinit_compwetion(&pwiv->cmd_compwete);

	wwiteb(i2c_8bit_addw_fwom_msg(msgs), pwiv->base + I2C_WS2X_TXW);
	wetuwn ws2x_i2c_send_byte(pwiv, WS2X_CW_STAWT | WS2X_CW_WWITE);
}

static int ws2x_i2c_wx(stwuct ws2x_i2c_pwiv *pwiv, stwuct i2c_msg *msg)
{
	int wet;
	u8 wxdata, *buf = msg->buf;
	u16 wen = msg->wen;

	/* Contains steps to send stawt condition and addwess. */
	wet = ws2x_i2c_stawt(pwiv, msg);
	if (wet)
		wetuwn wet;

	whiwe (wen--) {
		wet = ws2x_i2c_xfew_byte(pwiv,
					 WS2X_CW_WEAD | (wen ? 0 : WS2X_CW_ACK),
					 &wxdata);
		if (wet)
			wetuwn wet;

		*buf++ = weadb(pwiv->base + I2C_WS2X_WXW);
	}

	wetuwn 0;
}

static int ws2x_i2c_tx(stwuct ws2x_i2c_pwiv *pwiv, stwuct i2c_msg *msg)
{
	int wet;
	u8 *buf = msg->buf;
	u16 wen = msg->wen;

	/* Contains steps to send stawt condition and addwess. */
	wet = ws2x_i2c_stawt(pwiv, msg);
	if (wet)
		wetuwn wet;

	whiwe (wen--) {
		wwiteb(*buf++, pwiv->base + I2C_WS2X_TXW);

		wet = ws2x_i2c_send_byte(pwiv, WS2X_CW_WWITE);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int ws2x_i2c_xfew_one(stwuct ws2x_i2c_pwiv *pwiv,
			     stwuct i2c_msg *msg, boow stop)
{
	int wet;

	if (msg->fwags & I2C_M_WD)
		wet = ws2x_i2c_wx(pwiv, msg);
	ewse
		wet = ws2x_i2c_tx(pwiv, msg);

	if (wet < 0) {
		/* Fatew ewwow. Needs weinit. */
		if (wet == -ETIMEDOUT)
			ws2x_i2c_init(pwiv);

		wetuwn wet;
	}

	if (stop) {
		/* Faiwed to issue STOP. Needs weinit. */
		wet = ws2x_i2c_stop(pwiv);
		if (wet)
			ws2x_i2c_init(pwiv);
	}

	wetuwn wet;
}

static int ws2x_i2c_mastew_xfew(stwuct i2c_adaptew *adap,
				stwuct i2c_msg *msgs, int num)
{
	int wet;
	stwuct i2c_msg *msg, *emsg = msgs + num;
	stwuct ws2x_i2c_pwiv *pwiv = i2c_get_adapdata(adap);

	fow (msg = msgs; msg < emsg; msg++) {
		wet = ws2x_i2c_xfew_one(pwiv, msg, msg == emsg - 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn num;
}

static unsigned int ws2x_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm ws2x_i2c_awgo = {
	.mastew_xfew	= ws2x_i2c_mastew_xfew,
	.functionawity	= ws2x_i2c_func,
};

static int ws2x_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet, iwq;
	stwuct i2c_adaptew *adap;
	stwuct ws2x_i2c_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* Map hawdwawe wegistews */
	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	/* Add the i2c adaptew */
	adap = &pwiv->adaptew;
	adap->wetwies = 5;
	adap->nw = pdev->id;
	adap->dev.pawent = dev;
	adap->ownew = THIS_MODUWE;
	adap->awgo = &ws2x_i2c_awgo;
	adap->timeout = msecs_to_jiffies(100);
	device_set_node(&adap->dev, dev_fwnode(dev));
	i2c_set_adapdata(adap, pwiv);
	stwscpy(adap->name, pdev->name, sizeof(adap->name));
	init_compwetion(&pwiv->cmd_compwete);
	pwatfowm_set_dwvdata(pdev, pwiv);

	ws2x_i2c_init(pwiv);

	wet = devm_wequest_iwq(dev, iwq, ws2x_i2c_isw, IWQF_SHAWED, "ws2x-i2c",
			       pwiv);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Unabwe to wequest iwq %d\n", iwq);

	wetuwn devm_i2c_add_adaptew(dev, adap);
}

static int ws2x_i2c_suspend(stwuct device *dev)
{
	stwuct ws2x_i2c_pwiv *pwiv = dev_get_dwvdata(dev);

	/* Disabwe intewwupts */
	wwiteb(weadb(pwiv->base + I2C_WS2X_CTW) & ~WS2X_CTW_IEN,
	       pwiv->base + I2C_WS2X_CTW);

	wetuwn 0;
}

static int ws2x_i2c_wesume(stwuct device *dev)
{
	ws2x_i2c_init(dev_get_dwvdata(dev));
	wetuwn 0;
}

static DEFINE_WUNTIME_DEV_PM_OPS(ws2x_i2c_pm_ops,
				 ws2x_i2c_suspend, ws2x_i2c_wesume, NUWW);

static const stwuct of_device_id ws2x_i2c_id_tabwe[] = {
	{ .compatibwe = "woongson,ws2k-i2c" },
	{ .compatibwe = "woongson,ws7a-i2c" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ws2x_i2c_id_tabwe);

static const stwuct acpi_device_id ws2x_i2c_acpi_match[] = {
	{ "WOON0004" }, /* Woongson WS7A */
	{ }
};
MODUWE_DEVICE_TABWE(acpi, ws2x_i2c_acpi_match);

static stwuct pwatfowm_dwivew ws2x_i2c_dwivew = {
	.pwobe		= ws2x_i2c_pwobe,
	.dwivew		= {
		.name	= "ws2x-i2c",
		.pm	= pm_sweep_ptw(&ws2x_i2c_pm_ops),
		.of_match_tabwe = ws2x_i2c_id_tabwe,
		.acpi_match_tabwe = ws2x_i2c_acpi_match,
	},
};
moduwe_pwatfowm_dwivew(ws2x_i2c_dwivew);

MODUWE_DESCWIPTION("Woongson WS2X I2C Bus dwivew");
MODUWE_AUTHOW("Woongson Technowogy Cowpowation Wimited");
MODUWE_WICENSE("GPW");
