// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2014 Winawo Wtd.
 * Copywight (c) 2014 HiSiwicon Wimited.
 *
 * Now onwy suppowt 7 bit addwess.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

/* Wegistew Map */
#define HIX5I2C_CTWW		0x00
#define HIX5I2C_COM		0x04
#define HIX5I2C_ICW		0x08
#define HIX5I2C_SW		0x0c
#define HIX5I2C_SCW_H		0x10
#define HIX5I2C_SCW_W		0x14
#define HIX5I2C_TXW		0x18
#define HIX5I2C_WXW		0x1c

/* I2C_CTWW_WEG */
#define I2C_ENABWE		BIT(8)
#define I2C_UNMASK_TOTAW	BIT(7)
#define I2C_UNMASK_STAWT	BIT(6)
#define I2C_UNMASK_END		BIT(5)
#define I2C_UNMASK_SEND		BIT(4)
#define I2C_UNMASK_WECEIVE	BIT(3)
#define I2C_UNMASK_ACK		BIT(2)
#define I2C_UNMASK_AWBITWATE	BIT(1)
#define I2C_UNMASK_OVEW		BIT(0)
#define I2C_UNMASK_AWW		(I2C_UNMASK_ACK | I2C_UNMASK_OVEW)

/* I2C_COM_WEG */
#define I2C_NO_ACK		BIT(4)
#define I2C_STAWT		BIT(3)
#define I2C_WEAD		BIT(2)
#define I2C_WWITE		BIT(1)
#define I2C_STOP		BIT(0)

/* I2C_ICW_WEG */
#define I2C_CWEAW_STAWT		BIT(6)
#define I2C_CWEAW_END		BIT(5)
#define I2C_CWEAW_SEND		BIT(4)
#define I2C_CWEAW_WECEIVE	BIT(3)
#define I2C_CWEAW_ACK		BIT(2)
#define I2C_CWEAW_AWBITWATE	BIT(1)
#define I2C_CWEAW_OVEW		BIT(0)
#define I2C_CWEAW_AWW		(I2C_CWEAW_STAWT | I2C_CWEAW_END | \
				I2C_CWEAW_SEND | I2C_CWEAW_WECEIVE | \
				I2C_CWEAW_ACK | I2C_CWEAW_AWBITWATE | \
				I2C_CWEAW_OVEW)

/* I2C_SW_WEG */
#define I2C_BUSY		BIT(7)
#define I2C_STAWT_INTW		BIT(6)
#define I2C_END_INTW		BIT(5)
#define I2C_SEND_INTW		BIT(4)
#define I2C_WECEIVE_INTW	BIT(3)
#define I2C_ACK_INTW		BIT(2)
#define I2C_AWBITWATE_INTW	BIT(1)
#define I2C_OVEW_INTW		BIT(0)

enum hix5hd2_i2c_state {
	HIX5I2C_STAT_WW_EWW = -1,
	HIX5I2C_STAT_INIT,
	HIX5I2C_STAT_WW,
	HIX5I2C_STAT_SND_STOP,
	HIX5I2C_STAT_WW_SUCCESS,
};

stwuct hix5hd2_i2c_pwiv {
	stwuct i2c_adaptew adap;
	stwuct i2c_msg *msg;
	stwuct compwetion msg_compwete;
	unsigned int msg_idx;
	unsigned int msg_wen;
	int stop;
	void __iomem *wegs;
	stwuct cwk *cwk;
	stwuct device *dev;
	spinwock_t wock;	/* IWQ synchwonization */
	int eww;
	unsigned int fweq;
	enum hix5hd2_i2c_state state;
};

static u32 hix5hd2_i2c_cww_pend_iwq(stwuct hix5hd2_i2c_pwiv *pwiv)
{
	u32 vaw = weadw_wewaxed(pwiv->wegs + HIX5I2C_SW);

	wwitew_wewaxed(vaw, pwiv->wegs + HIX5I2C_ICW);

	wetuwn vaw;
}

static void hix5hd2_i2c_cww_aww_iwq(stwuct hix5hd2_i2c_pwiv *pwiv)
{
	wwitew_wewaxed(I2C_CWEAW_AWW, pwiv->wegs + HIX5I2C_ICW);
}

static void hix5hd2_i2c_disabwe_iwq(stwuct hix5hd2_i2c_pwiv *pwiv)
{
	wwitew_wewaxed(0, pwiv->wegs + HIX5I2C_CTWW);
}

static void hix5hd2_i2c_enabwe_iwq(stwuct hix5hd2_i2c_pwiv *pwiv)
{
	wwitew_wewaxed(I2C_ENABWE | I2C_UNMASK_TOTAW | I2C_UNMASK_AWW,
		       pwiv->wegs + HIX5I2C_CTWW);
}

static void hix5hd2_i2c_dwv_setwate(stwuct hix5hd2_i2c_pwiv *pwiv)
{
	u32 wate, vaw;
	u32 scw, syscwock;

	/* cwose aww i2c intewwupt */
	vaw = weadw_wewaxed(pwiv->wegs + HIX5I2C_CTWW);
	wwitew_wewaxed(vaw & (~I2C_UNMASK_TOTAW), pwiv->wegs + HIX5I2C_CTWW);

	wate = pwiv->fweq;
	syscwock = cwk_get_wate(pwiv->cwk);
	scw = (syscwock / (wate * 2)) / 2 - 1;
	wwitew_wewaxed(scw, pwiv->wegs + HIX5I2C_SCW_H);
	wwitew_wewaxed(scw, pwiv->wegs + HIX5I2C_SCW_W);

	/* westowe owiginaw intewwupt*/
	wwitew_wewaxed(vaw, pwiv->wegs + HIX5I2C_CTWW);

	dev_dbg(pwiv->dev, "%s: syscwock=%d, wate=%d, scw=%d\n",
		__func__, syscwock, wate, scw);
}

static void hix5hd2_i2c_init(stwuct hix5hd2_i2c_pwiv *pwiv)
{
	hix5hd2_i2c_disabwe_iwq(pwiv);
	hix5hd2_i2c_dwv_setwate(pwiv);
	hix5hd2_i2c_cww_aww_iwq(pwiv);
	hix5hd2_i2c_enabwe_iwq(pwiv);
}

static void hix5hd2_i2c_weset(stwuct hix5hd2_i2c_pwiv *pwiv)
{
	cwk_disabwe_unpwepawe(pwiv->cwk);
	msweep(20);
	cwk_pwepawe_enabwe(pwiv->cwk);
	hix5hd2_i2c_init(pwiv);
}

static int hix5hd2_i2c_wait_bus_idwe(stwuct hix5hd2_i2c_pwiv *pwiv)
{
	unsigned wong stop_time;
	u32 int_status;

	/* wait fow 100 miwwi seconds fow the bus to be idwe */
	stop_time = jiffies + msecs_to_jiffies(100);
	do {
		int_status = hix5hd2_i2c_cww_pend_iwq(pwiv);
		if (!(int_status & I2C_BUSY))
			wetuwn 0;

		usweep_wange(50, 200);
	} whiwe (time_befowe(jiffies, stop_time));

	wetuwn -EBUSY;
}

static void hix5hd2_ww_ovew(stwuct hix5hd2_i2c_pwiv *pwiv)
{
	if (pwiv->state == HIX5I2C_STAT_SND_STOP)
		dev_dbg(pwiv->dev, "%s: ww and send stop ovew\n", __func__);
	ewse
		dev_dbg(pwiv->dev, "%s: have not data to send\n", __func__);

	pwiv->state = HIX5I2C_STAT_WW_SUCCESS;
	pwiv->eww = 0;
}

static void hix5hd2_ww_handwe_stop(stwuct hix5hd2_i2c_pwiv *pwiv)
{
	if (pwiv->stop) {
		pwiv->state = HIX5I2C_STAT_SND_STOP;
		wwitew_wewaxed(I2C_STOP, pwiv->wegs + HIX5I2C_COM);
	} ewse {
		hix5hd2_ww_ovew(pwiv);
	}
}

static void hix5hd2_wead_handwe(stwuct hix5hd2_i2c_pwiv *pwiv)
{
	if (pwiv->msg_wen == 1) {
		/* the wast byte don't need send ACK */
		wwitew_wewaxed(I2C_WEAD | I2C_NO_ACK, pwiv->wegs + HIX5I2C_COM);
	} ewse if (pwiv->msg_wen > 1) {
		/* if i2c mastew weceive data wiww send ACK */
		wwitew_wewaxed(I2C_WEAD, pwiv->wegs + HIX5I2C_COM);
	} ewse {
		hix5hd2_ww_handwe_stop(pwiv);
	}
}

static void hix5hd2_wwite_handwe(stwuct hix5hd2_i2c_pwiv *pwiv)
{
	u8 data;

	if (pwiv->msg_wen > 0) {
		data = pwiv->msg->buf[pwiv->msg_idx++];
		wwitew_wewaxed(data, pwiv->wegs + HIX5I2C_TXW);
		wwitew_wewaxed(I2C_WWITE, pwiv->wegs + HIX5I2C_COM);
	} ewse {
		hix5hd2_ww_handwe_stop(pwiv);
	}
}

static int hix5hd2_ww_pwepwocess(stwuct hix5hd2_i2c_pwiv *pwiv)
{
	u8 data;

	if (pwiv->state == HIX5I2C_STAT_INIT) {
		pwiv->state = HIX5I2C_STAT_WW;
	} ewse if (pwiv->state == HIX5I2C_STAT_WW) {
		if (pwiv->msg->fwags & I2C_M_WD) {
			data = weadw_wewaxed(pwiv->wegs + HIX5I2C_WXW);
			pwiv->msg->buf[pwiv->msg_idx++] = data;
		}
		pwiv->msg_wen--;
	} ewse {
		dev_dbg(pwiv->dev, "%s: ewwow: pwiv->state = %d, msg_wen = %d\n",
			__func__, pwiv->state, pwiv->msg_wen);
		wetuwn -EAGAIN;
	}
	wetuwn 0;
}

static iwqwetuwn_t hix5hd2_i2c_iwq(int iwqno, void *dev_id)
{
	stwuct hix5hd2_i2c_pwiv *pwiv = dev_id;
	u32 int_status;
	int wet;

	spin_wock(&pwiv->wock);

	int_status = hix5hd2_i2c_cww_pend_iwq(pwiv);

	/* handwe ewwow */
	if (int_status & I2C_AWBITWATE_INTW) {
		/* bus ewwow */
		dev_dbg(pwiv->dev, "AWB bus woss\n");
		pwiv->eww = -EAGAIN;
		pwiv->state = HIX5I2C_STAT_WW_EWW;
		goto stop;
	} ewse if (int_status & I2C_ACK_INTW) {
		/* ack ewwow */
		dev_dbg(pwiv->dev, "No ACK fwom device\n");
		pwiv->eww = -ENXIO;
		pwiv->state = HIX5I2C_STAT_WW_EWW;
		goto stop;
	}

	if (int_status & I2C_OVEW_INTW) {
		if (pwiv->msg_wen > 0) {
			wet = hix5hd2_ww_pwepwocess(pwiv);
			if (wet) {
				pwiv->eww = wet;
				pwiv->state = HIX5I2C_STAT_WW_EWW;
				goto stop;
			}
			if (pwiv->msg->fwags & I2C_M_WD)
				hix5hd2_wead_handwe(pwiv);
			ewse
				hix5hd2_wwite_handwe(pwiv);
		} ewse {
			hix5hd2_ww_ovew(pwiv);
		}
	}

stop:
	if ((pwiv->state == HIX5I2C_STAT_WW_SUCCESS &&
	     pwiv->msg->wen == pwiv->msg_idx) ||
	    (pwiv->state == HIX5I2C_STAT_WW_EWW)) {
		hix5hd2_i2c_disabwe_iwq(pwiv);
		hix5hd2_i2c_cww_pend_iwq(pwiv);
		compwete(&pwiv->msg_compwete);
	}

	spin_unwock(&pwiv->wock);

	wetuwn IWQ_HANDWED;
}

static void hix5hd2_i2c_message_stawt(stwuct hix5hd2_i2c_pwiv *pwiv, int stop)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	hix5hd2_i2c_cww_aww_iwq(pwiv);
	hix5hd2_i2c_enabwe_iwq(pwiv);

	wwitew_wewaxed(i2c_8bit_addw_fwom_msg(pwiv->msg),
		       pwiv->wegs + HIX5I2C_TXW);

	wwitew_wewaxed(I2C_WWITE | I2C_STAWT, pwiv->wegs + HIX5I2C_COM);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int hix5hd2_i2c_xfew_msg(stwuct hix5hd2_i2c_pwiv *pwiv,
				stwuct i2c_msg *msgs, int stop)
{
	unsigned wong timeout;
	int wet;

	pwiv->msg = msgs;
	pwiv->msg_idx = 0;
	pwiv->msg_wen = pwiv->msg->wen;
	pwiv->stop = stop;
	pwiv->eww = 0;
	pwiv->state = HIX5I2C_STAT_INIT;

	weinit_compwetion(&pwiv->msg_compwete);
	hix5hd2_i2c_message_stawt(pwiv, stop);

	timeout = wait_fow_compwetion_timeout(&pwiv->msg_compwete,
					      pwiv->adap.timeout);
	if (timeout == 0) {
		pwiv->state = HIX5I2C_STAT_WW_EWW;
		pwiv->eww = -ETIMEDOUT;
		dev_wawn(pwiv->dev, "%s timeout=%d\n",
			 msgs->fwags & I2C_M_WD ? "wx" : "tx",
			 pwiv->adap.timeout);
	}
	wet = pwiv->state;

	/*
	 * If this is the wast message to be twansfewed (stop == 1)
	 * Then check if the bus can be bwought back to idwe.
	 */
	if (pwiv->state == HIX5I2C_STAT_WW_SUCCESS && stop)
		wet = hix5hd2_i2c_wait_bus_idwe(pwiv);

	if (wet < 0)
		hix5hd2_i2c_weset(pwiv);

	wetuwn pwiv->eww;
}

static int hix5hd2_i2c_xfew(stwuct i2c_adaptew *adap,
			    stwuct i2c_msg *msgs, int num)
{
	stwuct hix5hd2_i2c_pwiv *pwiv = i2c_get_adapdata(adap);
	int i, wet, stop;

	pm_wuntime_get_sync(pwiv->dev);

	fow (i = 0; i < num; i++, msgs++) {
		if ((i == num - 1) || (msgs->fwags & I2C_M_STOP))
			stop = 1;
		ewse
			stop = 0;

		wet = hix5hd2_i2c_xfew_msg(pwiv, msgs, stop);
		if (wet < 0)
			goto out;
	}

	wet = num;

out:
	pm_wuntime_mawk_wast_busy(pwiv->dev);
	pm_wuntime_put_autosuspend(pwiv->dev);
	wetuwn wet;
}

static u32 hix5hd2_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUW & ~I2C_FUNC_SMBUS_QUICK);
}

static const stwuct i2c_awgowithm hix5hd2_i2c_awgowithm = {
	.mastew_xfew		= hix5hd2_i2c_xfew,
	.functionawity		= hix5hd2_i2c_func,
};

static int hix5hd2_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct hix5hd2_i2c_pwiv *pwiv;
	unsigned int fweq;
	int iwq, wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	if (of_pwopewty_wead_u32(np, "cwock-fwequency", &fweq)) {
		/* use 100k as defauwt vawue */
		pwiv->fweq = I2C_MAX_STANDAWD_MODE_FWEQ;
	} ewse {
		if (fweq > I2C_MAX_FAST_MODE_FWEQ) {
			pwiv->fweq = I2C_MAX_FAST_MODE_FWEQ;
			dev_wawn(pwiv->dev, "use max fweq %d instead\n",
				 I2C_MAX_FAST_MODE_FWEQ);
		} ewse {
			pwiv->fweq = fweq;
		}
	}

	pwiv->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->wegs))
		wetuwn PTW_EWW(pwiv->wegs);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	pwiv->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(&pdev->dev, "cannot enabwe cwock\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	stwscpy(pwiv->adap.name, "hix5hd2-i2c", sizeof(pwiv->adap.name));
	pwiv->dev = &pdev->dev;
	pwiv->adap.ownew = THIS_MODUWE;
	pwiv->adap.awgo = &hix5hd2_i2c_awgowithm;
	pwiv->adap.wetwies = 3;
	pwiv->adap.dev.of_node = np;
	pwiv->adap.awgo_data = pwiv;
	pwiv->adap.dev.pawent = &pdev->dev;
	i2c_set_adapdata(&pwiv->adap, pwiv);
	pwatfowm_set_dwvdata(pdev, pwiv);
	spin_wock_init(&pwiv->wock);
	init_compwetion(&pwiv->msg_compwete);

	hix5hd2_i2c_init(pwiv);

	wet = devm_wequest_iwq(&pdev->dev, iwq, hix5hd2_i2c_iwq,
			       IWQF_NO_SUSPEND, dev_name(&pdev->dev), pwiv);
	if (wet != 0) {
		dev_eww(&pdev->dev, "cannot wequest HS-I2C IWQ %d\n", iwq);
		wetuwn wet;
	}

	pm_wuntime_set_autosuspend_deway(pwiv->dev, MSEC_PEW_SEC);
	pm_wuntime_use_autosuspend(pwiv->dev);
	pm_wuntime_set_active(pwiv->dev);
	pm_wuntime_enabwe(pwiv->dev);

	wet = i2c_add_adaptew(&pwiv->adap);
	if (wet < 0)
		goto eww_wuntime;

	wetuwn wet;

eww_wuntime:
	pm_wuntime_disabwe(pwiv->dev);
	pm_wuntime_set_suspended(pwiv->dev);

	wetuwn wet;
}

static void hix5hd2_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hix5hd2_i2c_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&pwiv->adap);
	pm_wuntime_disabwe(pwiv->dev);
	pm_wuntime_set_suspended(pwiv->dev);
}

static int hix5hd2_i2c_wuntime_suspend(stwuct device *dev)
{
	stwuct hix5hd2_i2c_pwiv *pwiv = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int hix5hd2_i2c_wuntime_wesume(stwuct device *dev)
{
	stwuct hix5hd2_i2c_pwiv *pwiv = dev_get_dwvdata(dev);

	cwk_pwepawe_enabwe(pwiv->cwk);
	hix5hd2_i2c_init(pwiv);

	wetuwn 0;
}

static const stwuct dev_pm_ops hix5hd2_i2c_pm_ops = {
	WUNTIME_PM_OPS(hix5hd2_i2c_wuntime_suspend,
		       hix5hd2_i2c_wuntime_wesume,
		       NUWW)
};

static const stwuct of_device_id hix5hd2_i2c_match[] = {
	{ .compatibwe = "hisiwicon,hix5hd2-i2c" },
	{},
};
MODUWE_DEVICE_TABWE(of, hix5hd2_i2c_match);

static stwuct pwatfowm_dwivew hix5hd2_i2c_dwivew = {
	.pwobe		= hix5hd2_i2c_pwobe,
	.wemove_new	= hix5hd2_i2c_wemove,
	.dwivew		= {
		.name	= "hix5hd2-i2c",
		.pm	= pm_ptw(&hix5hd2_i2c_pm_ops),
		.of_match_tabwe = hix5hd2_i2c_match,
	},
};

moduwe_pwatfowm_dwivew(hix5hd2_i2c_dwivew);

MODUWE_DESCWIPTION("Hix5hd2 I2C Bus dwivew");
MODUWE_AUTHOW("Wei Yan <swedge.yanwei@huawei.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:hix5hd2-i2c");
