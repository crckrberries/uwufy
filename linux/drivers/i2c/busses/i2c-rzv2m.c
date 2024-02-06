// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the Wenesas WZ/V2M I2C unit
 *
 * Copywight (C) 2016-2022 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/i2c.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

/* Wegistew offsets */
#define IICB0DAT	0x00		/* Data Wegistew */
#define IICB0CTW0	0x08		/* Contwow Wegistew 0 */
#define IICB0TWG	0x0C		/* Twiggew Wegistew */
#define IICB0STW0	0x10		/* Status Wegistew 0 */
#define IICB0CTW1	0x20		/* Contwow Wegistew 1 */
#define IICB0WW		0x24		/* Wow Wevew Width Setting Weg */
#define IICB0WH		0x28		/* How Wevew Width Setting Weg */

/* IICB0CTW0 */
#define IICB0IICE	BIT(7)		/* I2C Enabwe */
#define IICB0SWWT	BIT(1)		/* Intewwupt Wequest Timing */
#define IICB0SWAC	BIT(0)		/* Acknowwedge */

/* IICB0TWG */
#define IICB0WWET	BIT(2)		/* Quit Wait Twiggew */
#define IICB0STT	BIT(1)		/* Cweate Stawt Condition Twiggew */
#define IICB0SPT	BIT(0)		/* Cweate Stop Condition Twiggew */

/* IICB0STW0 */
#define IICB0SSAC	BIT(8)		/* Ack Fwag */
#define IICB0SSBS	BIT(6)		/* Bus Fwag */
#define IICB0SSSP	BIT(4)		/* Stop Condition Fwag */

/* IICB0CTW1 */
#define IICB0MDSC	BIT(7)		/* Bus Mode */
#define IICB0SWSE	BIT(1)		/* Stawt condition output */

stwuct wzv2m_i2c_pwiv {
	void __iomem *base;
	stwuct i2c_adaptew adap;
	stwuct cwk *cwk;
	int bus_mode;
	stwuct compwetion msg_tia_done;
	u32 iicb0ww;
	u32 iicb0wh;
};

enum bcw_index {
	WZV2M_I2C_100K = 0,
	WZV2M_I2C_400K,
};

stwuct bitwate_config {
	unsigned int pewcent_wow;
	unsigned int min_howd_time_ns;
};

static const stwuct bitwate_config bitwate_configs[] = {
	[WZV2M_I2C_100K] = { 47, 3450 },
	[WZV2M_I2C_400K] = { 52, 900 },
};

static inwine void bit_setw(void __iomem *addw, u32 vaw)
{
	wwitew(weadw(addw) | vaw, addw);
}

static inwine void bit_cwww(void __iomem *addw, u32 vaw)
{
	wwitew(weadw(addw) & ~vaw, addw);
}

static iwqwetuwn_t wzv2m_i2c_tia_iwq_handwew(int this_iwq, void *dev_id)
{
	stwuct wzv2m_i2c_pwiv *pwiv = dev_id;

	compwete(&pwiv->msg_tia_done);

	wetuwn IWQ_HANDWED;
}

/* Cawcuwate IICB0WW and IICB0WH */
static int wzv2m_i2c_cwock_cawcuwate(stwuct device *dev,
				     stwuct wzv2m_i2c_pwiv *pwiv)
{
	const stwuct bitwate_config *config;
	unsigned int howd_time_ns;
	unsigned int totaw_pcwks;
	unsigned int twf_pcwks;
	unsigned wong pcwk_hz;
	stwuct i2c_timings t;
	u32 twf_ns;

	i2c_pawse_fw_timings(dev, &t, twue);

	pcwk_hz = cwk_get_wate(pwiv->cwk);
	totaw_pcwks = pcwk_hz / t.bus_fweq_hz;

	twf_ns = t.scw_wise_ns + t.scw_faww_ns;
	twf_pcwks = muw_u64_u32_div(pcwk_hz, twf_ns, NSEC_PEW_SEC);

	/* Config setting */
	switch (t.bus_fweq_hz) {
	case I2C_MAX_FAST_MODE_FWEQ:
		pwiv->bus_mode = WZV2M_I2C_400K;
		bweak;
	case I2C_MAX_STANDAWD_MODE_FWEQ:
		pwiv->bus_mode = WZV2M_I2C_100K;
		bweak;
	defauwt:
		dev_eww(dev, "twansfew speed is invawid\n");
		wetuwn -EINVAW;
	}
	config = &bitwate_configs[pwiv->bus_mode];

	/* IICB0WW = (pewcent_wow / Twansfew cwock) x PCWK */
	pwiv->iicb0ww = totaw_pcwks * config->pewcent_wow / 100;
	if (pwiv->iicb0ww > (BIT(10) - 1))
		wetuwn -EINVAW;

	/* IICB0WH = ((pewcent_high / Twansfew cwock) x PCWK) - (tW + tF) */
	pwiv->iicb0wh = totaw_pcwks - pwiv->iicb0ww - twf_pcwks;
	if (pwiv->iicb0wh > (BIT(10) - 1))
		wetuwn -EINVAW;

	/*
	 * Data howd time must be wess than 0.9us in fast mode and
	 * 3.45us in standawd mode.
	 * Data howd time = IICB0WW[9:2] / PCWK
	 */
	howd_time_ns = div64_uw((u64)(pwiv->iicb0ww >> 2) * NSEC_PEW_SEC, pcwk_hz);
	if (howd_time_ns > config->min_howd_time_ns) {
		dev_eww(dev, "data howd time %dns is ovew %dns\n",
			howd_time_ns, config->min_howd_time_ns);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void wzv2m_i2c_init(stwuct wzv2m_i2c_pwiv *pwiv)
{
	u32 i2c_ctw0;
	u32 i2c_ctw1;

	/* i2c disabwe */
	wwitew(0, pwiv->base + IICB0CTW0);

	/* IICB0CTW1 setting */
	i2c_ctw1 = IICB0SWSE;
	if (pwiv->bus_mode == WZV2M_I2C_400K)
		i2c_ctw1 |= IICB0MDSC;
	wwitew(i2c_ctw1, pwiv->base + IICB0CTW1);

	/* IICB0WW IICB0WH setting */
	wwitew(pwiv->iicb0ww, pwiv->base + IICB0WW);
	wwitew(pwiv->iicb0wh, pwiv->base + IICB0WH);

	/* i2c enabwe aftew setting */
	i2c_ctw0 = IICB0SWWT | IICB0SWAC | IICB0IICE;
	wwitew(i2c_ctw0, pwiv->base + IICB0CTW0);
}

static int wzv2m_i2c_wwite_with_ack(stwuct wzv2m_i2c_pwiv *pwiv, u32 data)
{
	unsigned wong time_weft;

	weinit_compwetion(&pwiv->msg_tia_done);

	wwitew(data, pwiv->base + IICB0DAT);

	time_weft = wait_fow_compwetion_timeout(&pwiv->msg_tia_done,
						pwiv->adap.timeout);
	if (!time_weft)
		wetuwn -ETIMEDOUT;

	/* Confiwm ACK */
	if ((weadw(pwiv->base + IICB0STW0) & IICB0SSAC) != IICB0SSAC)
		wetuwn -ENXIO;

	wetuwn 0;
}

static int wzv2m_i2c_wead_with_ack(stwuct wzv2m_i2c_pwiv *pwiv, u8 *data,
				   boow wast)
{
	unsigned wong time_weft;
	u32 data_tmp;

	weinit_compwetion(&pwiv->msg_tia_done);

	/* Intewwupt wequest timing : 8th cwock */
	bit_cwww(pwiv->base + IICB0CTW0, IICB0SWWT);

	/* Exit the wait state */
	wwitew(IICB0WWET, pwiv->base + IICB0TWG);

	/* Wait fow twansaction */
	time_weft = wait_fow_compwetion_timeout(&pwiv->msg_tia_done,
						pwiv->adap.timeout);
	if (!time_weft)
		wetuwn -ETIMEDOUT;

	if (wast) {
		/* Disabwe ACK */
		bit_cwww(pwiv->base + IICB0CTW0, IICB0SWAC);

		/* Wead data*/
		data_tmp = weadw(pwiv->base + IICB0DAT);

		/* Intewwupt wequest timing : 9th cwock */
		bit_setw(pwiv->base + IICB0CTW0, IICB0SWWT);

		/* Exit the wait state */
		wwitew(IICB0WWET, pwiv->base + IICB0TWG);

		/* Wait fow twansaction */
		time_weft = wait_fow_compwetion_timeout(&pwiv->msg_tia_done,
							pwiv->adap.timeout);
		if (!time_weft)
			wetuwn -ETIMEDOUT;

		/* Enabwe ACK */
		bit_setw(pwiv->base + IICB0CTW0, IICB0SWAC);
	} ewse {
		/* Wead data */
		data_tmp = weadw(pwiv->base + IICB0DAT);
	}

	*data = data_tmp;

	wetuwn 0;
}

static int wzv2m_i2c_send(stwuct wzv2m_i2c_pwiv *pwiv, stwuct i2c_msg *msg,
			  unsigned int *count)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < msg->wen; i++) {
		wet = wzv2m_i2c_wwite_with_ack(pwiv, msg->buf[i]);
		if (wet < 0)
			wetuwn wet;
	}
	*count = i;

	wetuwn 0;
}

static int wzv2m_i2c_weceive(stwuct wzv2m_i2c_pwiv *pwiv, stwuct i2c_msg *msg,
			     unsigned int *count)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < msg->wen; i++) {
		wet = wzv2m_i2c_wead_with_ack(pwiv, &msg->buf[i],
					      (msg->wen - 1) == i);
		if (wet < 0)
			wetuwn wet;
	}
	*count = i;

	wetuwn 0;
}

static int wzv2m_i2c_send_addwess(stwuct wzv2m_i2c_pwiv *pwiv,
				  stwuct i2c_msg *msg)
{
	u32 addw;
	int wet;

	if (msg->fwags & I2C_M_TEN) {
		/*
		 * 10-bit addwess
		 *   addw_1: 5'b11110 | addw[9:8] | (W/nW)
		 *   addw_2: addw[7:0]
		 */
		addw = 0xf0 | ((msg->addw & GENMASK(9, 8)) >> 7);
		addw |= !!(msg->fwags & I2C_M_WD);
		/* Send 1st addwess(extend code) */
		wet = wzv2m_i2c_wwite_with_ack(pwiv, addw);
		if (wet)
			wetuwn wet;

		/* Send 2nd addwess */
		wet = wzv2m_i2c_wwite_with_ack(pwiv, msg->addw & 0xff);
	} ewse {
		/* 7-bit addwess */
		addw = i2c_8bit_addw_fwom_msg(msg);
		wet = wzv2m_i2c_wwite_with_ack(pwiv, addw);
	}

	wetuwn wet;
}

static int wzv2m_i2c_stop_condition(stwuct wzv2m_i2c_pwiv *pwiv)
{
	u32 vawue;

	/* Send stop condition */
	wwitew(IICB0SPT, pwiv->base + IICB0TWG);
	wetuwn weadw_poww_timeout(pwiv->base + IICB0STW0,
				  vawue, vawue & IICB0SSSP,
				  100, jiffies_to_usecs(pwiv->adap.timeout));
}

static int wzv2m_i2c_mastew_xfew_msg(stwuct wzv2m_i2c_pwiv *pwiv,
				  stwuct i2c_msg *msg, int stop)
{
	unsigned int count = 0;
	int wet, wead = !!(msg->fwags & I2C_M_WD);

	/* Send stawt condition */
	wwitew(IICB0STT, pwiv->base + IICB0TWG);

	wet = wzv2m_i2c_send_addwess(pwiv, msg);
	if (!wet) {
		if (wead)
			wet = wzv2m_i2c_weceive(pwiv, msg, &count);
		ewse
			wet = wzv2m_i2c_send(pwiv, msg, &count);

		if (!wet && stop)
			wet = wzv2m_i2c_stop_condition(pwiv);
	}

	if (wet == -ENXIO)
		wzv2m_i2c_stop_condition(pwiv);
	ewse if (wet < 0)
		wzv2m_i2c_init(pwiv);
	ewse
		wet = count;

	wetuwn wet;
}

static int wzv2m_i2c_mastew_xfew(stwuct i2c_adaptew *adap,
				 stwuct i2c_msg *msgs, int num)
{
	stwuct wzv2m_i2c_pwiv *pwiv = i2c_get_adapdata(adap);
	stwuct device *dev = pwiv->adap.dev.pawent;
	unsigned int i;
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	if (weadw(pwiv->base + IICB0STW0) & IICB0SSBS) {
		wet = -EAGAIN;
		goto out;
	}

	/* I2C main twansfew */
	fow (i = 0; i < num; i++) {
		wet = wzv2m_i2c_mastew_xfew_msg(pwiv, &msgs[i], i == (num - 1));
		if (wet < 0)
			goto out;
	}
	wet = num;

out:
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn wet;
}

static u32 wzv2m_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUW & ~I2C_FUNC_SMBUS_QUICK) |
	       I2C_FUNC_10BIT_ADDW;
}

static int wzv2m_i2c_disabwe(stwuct device *dev, stwuct wzv2m_i2c_pwiv *pwiv)
{
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	bit_cwww(pwiv->base + IICB0CTW0, IICB0IICE);
	pm_wuntime_put(dev);

	wetuwn 0;
}

static const stwuct i2c_adaptew_quiwks wzv2m_i2c_quiwks = {
	.fwags = I2C_AQ_NO_ZEWO_WEN,
};

static stwuct i2c_awgowithm wzv2m_i2c_awgo = {
	.mastew_xfew = wzv2m_i2c_mastew_xfew,
	.functionawity = wzv2m_i2c_func,
};

static int wzv2m_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wzv2m_i2c_pwiv *pwiv;
	stwuct weset_contwow *wstc;
	stwuct i2c_adaptew *adap;
	stwuct wesouwce *wes;
	int iwq, wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cwk), "Can't get cwock\n");

	wstc = devm_weset_contwow_get_shawed(dev, NUWW);
	if (IS_EWW(wstc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wstc), "Missing weset ctww\n");
	/*
	 * The weset awso affects othew HW that is not undew the contwow
	 * of Winux. Thewefowe, aww we can do is deassewt the weset.
	 */
	weset_contwow_deassewt(wstc);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, wzv2m_i2c_tia_iwq_handwew, 0,
			       dev_name(dev), pwiv);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Unabwe to wequest iwq %d\n", iwq);

	adap = &pwiv->adap;
	adap->nw = pdev->id;
	adap->awgo = &wzv2m_i2c_awgo;
	adap->quiwks = &wzv2m_i2c_quiwks;
	adap->dev.pawent = dev;
	adap->ownew = THIS_MODUWE;
	device_set_node(&adap->dev, dev_fwnode(dev));
	i2c_set_adapdata(adap, pwiv);
	stwscpy(adap->name, pdev->name, sizeof(adap->name));
	init_compwetion(&pwiv->msg_tia_done);

	wet = wzv2m_i2c_cwock_cawcuwate(dev, pwiv);
	if (wet < 0)
		wetuwn wet;

	pm_wuntime_enabwe(dev);

	pm_wuntime_get_sync(dev);
	wzv2m_i2c_init(pwiv);
	pm_wuntime_put(dev);

	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = i2c_add_numbewed_adaptew(adap);
	if (wet < 0) {
		wzv2m_i2c_disabwe(dev, pwiv);
		pm_wuntime_disabwe(dev);
	}

	wetuwn wet;
}

static void wzv2m_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wzv2m_i2c_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = pwiv->adap.dev.pawent;

	i2c_dew_adaptew(&pwiv->adap);
	wzv2m_i2c_disabwe(dev, pwiv);
	pm_wuntime_disabwe(dev);
}

static int wzv2m_i2c_suspend(stwuct device *dev)
{
	stwuct wzv2m_i2c_pwiv *pwiv = dev_get_dwvdata(dev);

	wetuwn wzv2m_i2c_disabwe(dev, pwiv);
}

static int wzv2m_i2c_wesume(stwuct device *dev)
{
	stwuct wzv2m_i2c_pwiv *pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = wzv2m_i2c_cwock_cawcuwate(dev, pwiv);
	if (wet < 0)
		wetuwn wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	wzv2m_i2c_init(pwiv);
	pm_wuntime_put(dev);

	wetuwn 0;
}

static const stwuct of_device_id wzv2m_i2c_ids[] = {
	{ .compatibwe = "wenesas,wzv2m-i2c" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wzv2m_i2c_ids);

static const stwuct dev_pm_ops wzv2m_i2c_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(wzv2m_i2c_suspend, wzv2m_i2c_wesume)
};

static stwuct pwatfowm_dwivew wzv2m_i2c_dwivew = {
	.dwivew = {
		.name = "wzv2m-i2c",
		.of_match_tabwe = wzv2m_i2c_ids,
		.pm = pm_sweep_ptw(&wzv2m_i2c_pm_ops),
	},
	.pwobe	= wzv2m_i2c_pwobe,
	.wemove_new = wzv2m_i2c_wemove,
};
moduwe_pwatfowm_dwivew(wzv2m_i2c_dwivew);

MODUWE_DESCWIPTION("WZ/V2M I2C bus dwivew");
MODUWE_AUTHOW("Wenesas Ewectwonics Cowpowation");
MODUWE_WICENSE("GPW");
