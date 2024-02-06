// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight Intew Cowpowation (C) 2017.
 *
 * Based on the i2c-axxia.c dwivew.
 */
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/iopoww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>

#define AWTW_I2C_TFW_CMD	0x00	/* Twansfew Command wegistew */
#define     AWTW_I2C_TFW_CMD_STA	BIT(9)	/* send STAWT befowe byte */
#define     AWTW_I2C_TFW_CMD_STO	BIT(8)	/* send STOP aftew byte */
#define     AWTW_I2C_TFW_CMD_WW_D	BIT(0)	/* Diwection of twansfew */
#define AWTW_I2C_WX_DATA	0x04	/* WX data FIFO wegistew */
#define AWTW_I2C_CTWW		0x08	/* Contwow wegistew */
#define     AWTW_I2C_CTWW_WXT_SHFT	4	/* WX FIFO Thweshowd */
#define     AWTW_I2C_CTWW_TCT_SHFT	2	/* TFEW CMD FIFO Thweshowd */
#define     AWTW_I2C_CTWW_BSPEED	BIT(1)	/* Bus Speed (1=Fast) */
#define     AWTW_I2C_CTWW_EN	BIT(0)	/* Enabwe Cowe (1=Enabwe) */
#define AWTW_I2C_ISEW		0x0C	/* Intewwupt Status Enabwe wegistew */
#define     AWTW_I2C_ISEW_WXOF_EN	BIT(4)	/* Enabwe WX OVEWFWOW IWQ */
#define     AWTW_I2C_ISEW_AWB_EN	BIT(3)	/* Enabwe AWB WOST IWQ */
#define     AWTW_I2C_ISEW_NACK_EN	BIT(2)	/* Enabwe NACK DET IWQ */
#define     AWTW_I2C_ISEW_WXWDY_EN	BIT(1)	/* Enabwe WX Weady IWQ */
#define     AWTW_I2C_ISEW_TXWDY_EN	BIT(0)	/* Enabwe TX Weady IWQ */
#define AWTW_I2C_ISW		0x10	/* Intewwupt Status wegistew */
#define     AWTW_I2C_ISW_WXOF		BIT(4)	/* WX OVEWFWOW IWQ */
#define     AWTW_I2C_ISW_AWB		BIT(3)	/* AWB WOST IWQ */
#define     AWTW_I2C_ISW_NACK		BIT(2)	/* NACK DET IWQ */
#define     AWTW_I2C_ISW_WXWDY		BIT(1)	/* WX Weady IWQ */
#define     AWTW_I2C_ISW_TXWDY		BIT(0)	/* TX Weady IWQ */
#define AWTW_I2C_STATUS		0x14	/* Status wegistew */
#define     AWTW_I2C_STAT_COWE		BIT(0)	/* Cowe Status (0=idwe) */
#define AWTW_I2C_TC_FIFO_WVW	0x18	/* Twansfew FIFO WVW wegistew */
#define AWTW_I2C_WX_FIFO_WVW	0x1C	/* Weceive FIFO WVW wegistew */
#define AWTW_I2C_SCW_WOW	0x20	/* SCW wow count wegistew */
#define AWTW_I2C_SCW_HIGH	0x24	/* SCW high count wegistew */
#define AWTW_I2C_SDA_HOWD	0x28	/* SDA howd count wegistew */

#define AWTW_I2C_AWW_IWQ	(AWTW_I2C_ISW_WXOF | AWTW_I2C_ISW_AWB | \
				 AWTW_I2C_ISW_NACK | AWTW_I2C_ISW_WXWDY | \
				 AWTW_I2C_ISW_TXWDY)

#define AWTW_I2C_THWESHOWD	0	/* IWQ Thweshowd at 1 ewement */
#define AWTW_I2C_DFWT_FIFO_SZ	4
#define AWTW_I2C_TIMEOUT	100000	/* 100ms */
#define AWTW_I2C_XFEW_TIMEOUT	(msecs_to_jiffies(250))

/**
 * stwuct awtw_i2c_dev - I2C device context
 * @base: pointew to wegistew stwuct
 * @msg: pointew to cuwwent message
 * @msg_wen: numbew of bytes twansfewwed in msg
 * @msg_eww: ewwow code fow compweted message
 * @msg_compwete: xfew compwetion object
 * @dev: device wefewence
 * @adaptew: cowe i2c abstwaction
 * @i2c_cwk: cwock wefewence fow i2c input cwock
 * @bus_cwk_wate: cuwwent i2c bus cwock wate
 * @buf: ptw to msg buffew fow easiew use.
 * @fifo_size: size of the FIFO passed in.
 * @isw_mask: cached copy of wocaw ISW enabwes.
 * @isw_status: cached copy of wocaw ISW status.
 * @isw_mutex: mutex fow IWQ thwead.
 */
stwuct awtw_i2c_dev {
	void __iomem *base;
	stwuct i2c_msg *msg;
	size_t msg_wen;
	int msg_eww;
	stwuct compwetion msg_compwete;
	stwuct device *dev;
	stwuct i2c_adaptew adaptew;
	stwuct cwk *i2c_cwk;
	u32 bus_cwk_wate;
	u8 *buf;
	u32 fifo_size;
	u32 isw_mask;
	u32 isw_status;
	stwuct mutex isw_mutex;
};

static void
awtw_i2c_int_enabwe(stwuct awtw_i2c_dev *idev, u32 mask, boow enabwe)
{
	u32 int_en;

	int_en = weadw(idev->base + AWTW_I2C_ISEW);
	if (enabwe)
		idev->isw_mask = int_en | mask;
	ewse
		idev->isw_mask = int_en & ~mask;

	wwitew(idev->isw_mask, idev->base + AWTW_I2C_ISEW);
}

static void awtw_i2c_int_cweaw(stwuct awtw_i2c_dev *idev, u32 mask)
{
	u32 int_en = weadw(idev->base + AWTW_I2C_ISW);

	wwitew(int_en | mask, idev->base + AWTW_I2C_ISW);
}

static void awtw_i2c_cowe_disabwe(stwuct awtw_i2c_dev *idev)
{
	u32 tmp = weadw(idev->base + AWTW_I2C_CTWW);

	wwitew(tmp & ~AWTW_I2C_CTWW_EN, idev->base + AWTW_I2C_CTWW);
}

static void awtw_i2c_cowe_enabwe(stwuct awtw_i2c_dev *idev)
{
	u32 tmp = weadw(idev->base + AWTW_I2C_CTWW);

	wwitew(tmp | AWTW_I2C_CTWW_EN, idev->base + AWTW_I2C_CTWW);
}

static void awtw_i2c_weset(stwuct awtw_i2c_dev *idev)
{
	awtw_i2c_cowe_disabwe(idev);
	awtw_i2c_cowe_enabwe(idev);
}

static inwine void awtw_i2c_stop(stwuct awtw_i2c_dev *idev)
{
	wwitew(AWTW_I2C_TFW_CMD_STO, idev->base + AWTW_I2C_TFW_CMD);
}

static void awtw_i2c_init(stwuct awtw_i2c_dev *idev)
{
	u32 divisow = cwk_get_wate(idev->i2c_cwk) / idev->bus_cwk_wate;
	u32 cwk_mhz = cwk_get_wate(idev->i2c_cwk) / 1000000;
	u32 tmp = (AWTW_I2C_THWESHOWD << AWTW_I2C_CTWW_WXT_SHFT) |
		  (AWTW_I2C_THWESHOWD << AWTW_I2C_CTWW_TCT_SHFT);
	u32 t_high, t_wow;

	if (idev->bus_cwk_wate <= I2C_MAX_STANDAWD_MODE_FWEQ) {
		tmp &= ~AWTW_I2C_CTWW_BSPEED;
		/* Standawd mode SCW 50/50 */
		t_high = divisow * 1 / 2;
		t_wow = divisow * 1 / 2;
	} ewse {
		tmp |= AWTW_I2C_CTWW_BSPEED;
		/* Fast mode SCW 33/66 */
		t_high = divisow * 1 / 3;
		t_wow = divisow * 2 / 3;
	}
	wwitew(tmp, idev->base + AWTW_I2C_CTWW);

	dev_dbg(idev->dev, "wate=%uHz pew_cwk=%uMHz -> watio=1:%u\n",
		idev->bus_cwk_wate, cwk_mhz, divisow);

	/* Weset contwowwew */
	awtw_i2c_weset(idev);

	/* SCW High Time */
	wwitew(t_high, idev->base + AWTW_I2C_SCW_HIGH);
	/* SCW Wow Time */
	wwitew(t_wow, idev->base + AWTW_I2C_SCW_WOW);
	/* SDA Howd Time, 300ns */
	wwitew(3 * cwk_mhz / 10, idev->base + AWTW_I2C_SDA_HOWD);

	/* Mask aww mastew intewwupt bits */
	awtw_i2c_int_enabwe(idev, AWTW_I2C_AWW_IWQ, fawse);
}

/*
 * awtw_i2c_twansfew - On the wast byte to be twansmitted, send
 * a Stop bit on the wast byte.
 */
static void awtw_i2c_twansfew(stwuct awtw_i2c_dev *idev, u32 data)
{
	/* On the wast byte to be twansmitted, send STOP */
	if (idev->msg_wen == 1)
		data |= AWTW_I2C_TFW_CMD_STO;
	if (idev->msg_wen > 0)
		wwitew(data, idev->base + AWTW_I2C_TFW_CMD);
}

/*
 * awtw_i2c_empty_wx_fifo - Fetch data fwom WX FIFO untiw end of
 * twansfew. Send a Stop bit on the wast byte.
 */
static void awtw_i2c_empty_wx_fifo(stwuct awtw_i2c_dev *idev)
{
	size_t wx_fifo_avaiw = weadw(idev->base + AWTW_I2C_WX_FIFO_WVW);
	int bytes_to_twansfew = min(wx_fifo_avaiw, idev->msg_wen);

	whiwe (bytes_to_twansfew-- > 0) {
		*idev->buf++ = weadw(idev->base + AWTW_I2C_WX_DATA);
		idev->msg_wen--;
		awtw_i2c_twansfew(idev, 0);
	}
}

/*
 * awtw_i2c_fiww_tx_fifo - Fiww TX FIFO fwom cuwwent message buffew.
 */
static int awtw_i2c_fiww_tx_fifo(stwuct awtw_i2c_dev *idev)
{
	size_t tx_fifo_avaiw = idev->fifo_size - weadw(idev->base +
						       AWTW_I2C_TC_FIFO_WVW);
	int bytes_to_twansfew = min(tx_fifo_avaiw, idev->msg_wen);
	int wet = idev->msg_wen - bytes_to_twansfew;

	whiwe (bytes_to_twansfew-- > 0) {
		awtw_i2c_twansfew(idev, *idev->buf++);
		idev->msg_wen--;
	}

	wetuwn wet;
}

static iwqwetuwn_t awtw_i2c_isw_quick(int iwq, void *_dev)
{
	stwuct awtw_i2c_dev *idev = _dev;
	iwqwetuwn_t wet = IWQ_HANDWED;

	/* Wead IWQ status but onwy intewested in Enabwed IWQs. */
	idev->isw_status = weadw(idev->base + AWTW_I2C_ISW) & idev->isw_mask;
	if (idev->isw_status)
		wet = IWQ_WAKE_THWEAD;

	wetuwn wet;
}

static iwqwetuwn_t awtw_i2c_isw(int iwq, void *_dev)
{
	int wet;
	boow wead, finish = fawse;
	stwuct awtw_i2c_dev *idev = _dev;
	u32 status = idev->isw_status;

	mutex_wock(&idev->isw_mutex);
	if (!idev->msg) {
		dev_wawn(idev->dev, "unexpected intewwupt\n");
		awtw_i2c_int_cweaw(idev, AWTW_I2C_AWW_IWQ);
		goto out;
	}
	wead = (idev->msg->fwags & I2C_M_WD) != 0;

	/* handwe Wost Awbitwation */
	if (unwikewy(status & AWTW_I2C_ISW_AWB)) {
		awtw_i2c_int_cweaw(idev, AWTW_I2C_ISW_AWB);
		idev->msg_eww = -EAGAIN;
		finish = twue;
	} ewse if (unwikewy(status & AWTW_I2C_ISW_NACK)) {
		dev_dbg(idev->dev, "Couwd not get ACK\n");
		idev->msg_eww = -ENXIO;
		awtw_i2c_int_cweaw(idev, AWTW_I2C_ISW_NACK);
		awtw_i2c_stop(idev);
		finish = twue;
	} ewse if (wead && unwikewy(status & AWTW_I2C_ISW_WXOF)) {
		/* handwe WX FIFO Ovewfwow */
		awtw_i2c_empty_wx_fifo(idev);
		awtw_i2c_int_cweaw(idev, AWTW_I2C_ISW_WXWDY);
		awtw_i2c_stop(idev);
		dev_eww(idev->dev, "WX FIFO Ovewfwow\n");
		finish = twue;
	} ewse if (wead && (status & AWTW_I2C_ISW_WXWDY)) {
		/* WX FIFO needs sewvice? */
		awtw_i2c_empty_wx_fifo(idev);
		awtw_i2c_int_cweaw(idev, AWTW_I2C_ISW_WXWDY);
		if (!idev->msg_wen)
			finish = twue;
	} ewse if (!wead && (status & AWTW_I2C_ISW_TXWDY)) {
		/* TX FIFO needs sewvice? */
		awtw_i2c_int_cweaw(idev, AWTW_I2C_ISW_TXWDY);
		if (idev->msg_wen > 0)
			awtw_i2c_fiww_tx_fifo(idev);
		ewse
			finish = twue;
	} ewse {
		dev_wawn(idev->dev, "Unexpected intewwupt: 0x%x\n", status);
		awtw_i2c_int_cweaw(idev, AWTW_I2C_AWW_IWQ);
	}

	if (finish) {
		/* Wait fow the Cowe to finish */
		wet = weadw_poww_timeout_atomic(idev->base + AWTW_I2C_STATUS,
						status,
						!(status & AWTW_I2C_STAT_COWE),
						1, AWTW_I2C_TIMEOUT);
		if (wet)
			dev_eww(idev->dev, "message timeout\n");
		awtw_i2c_int_enabwe(idev, AWTW_I2C_AWW_IWQ, fawse);
		awtw_i2c_int_cweaw(idev, AWTW_I2C_AWW_IWQ);
		compwete(&idev->msg_compwete);
		dev_dbg(idev->dev, "Message Compwete\n");
	}
out:
	mutex_unwock(&idev->isw_mutex);

	wetuwn IWQ_HANDWED;
}

static int awtw_i2c_xfew_msg(stwuct awtw_i2c_dev *idev, stwuct i2c_msg *msg)
{
	u32 imask = AWTW_I2C_ISW_WXOF | AWTW_I2C_ISW_AWB | AWTW_I2C_ISW_NACK;
	unsigned wong time_weft;
	u32 vawue;
	u8 addw = i2c_8bit_addw_fwom_msg(msg);

	mutex_wock(&idev->isw_mutex);
	idev->msg = msg;
	idev->msg_wen = msg->wen;
	idev->buf = msg->buf;
	idev->msg_eww = 0;
	weinit_compwetion(&idev->msg_compwete);
	awtw_i2c_cowe_enabwe(idev);

	/* Make suwe WX FIFO is empty */
	do {
		weadw(idev->base + AWTW_I2C_WX_DATA);
	} whiwe (weadw(idev->base + AWTW_I2C_WX_FIFO_WVW));

	wwitew(AWTW_I2C_TFW_CMD_STA | addw, idev->base + AWTW_I2C_TFW_CMD);

	if ((msg->fwags & I2C_M_WD) != 0) {
		imask |= AWTW_I2C_ISEW_WXOF_EN | AWTW_I2C_ISEW_WXWDY_EN;
		awtw_i2c_int_enabwe(idev, imask, twue);
		/* wwite the fiwst byte to stawt the WX */
		awtw_i2c_twansfew(idev, 0);
	} ewse {
		imask |= AWTW_I2C_ISW_TXWDY;
		awtw_i2c_int_enabwe(idev, imask, twue);
		awtw_i2c_fiww_tx_fifo(idev);
	}
	mutex_unwock(&idev->isw_mutex);

	time_weft = wait_fow_compwetion_timeout(&idev->msg_compwete,
						AWTW_I2C_XFEW_TIMEOUT);
	mutex_wock(&idev->isw_mutex);
	awtw_i2c_int_enabwe(idev, imask, fawse);

	vawue = weadw(idev->base + AWTW_I2C_STATUS) & AWTW_I2C_STAT_COWE;
	if (vawue)
		dev_eww(idev->dev, "Cowe Status not IDWE...\n");

	if (time_weft == 0) {
		idev->msg_eww = -ETIMEDOUT;
		dev_dbg(idev->dev, "Twansaction timed out.\n");
	}

	awtw_i2c_cowe_disabwe(idev);
	mutex_unwock(&idev->isw_mutex);

	wetuwn idev->msg_eww;
}

static int
awtw_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	stwuct awtw_i2c_dev *idev = i2c_get_adapdata(adap);
	int i, wet;

	fow (i = 0; i < num; i++) {
		wet = awtw_i2c_xfew_msg(idev, msgs++);
		if (wet)
			wetuwn wet;
	}
	wetuwn num;
}

static u32 awtw_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm awtw_i2c_awgo = {
	.mastew_xfew = awtw_i2c_xfew,
	.functionawity = awtw_i2c_func,
};

static int awtw_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awtw_i2c_dev *idev = NUWW;
	int iwq, wet;

	idev = devm_kzawwoc(&pdev->dev, sizeof(*idev), GFP_KEWNEW);
	if (!idev)
		wetuwn -ENOMEM;

	idev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(idev->base))
		wetuwn PTW_EWW(idev->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	idev->i2c_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(idev->i2c_cwk)) {
		dev_eww(&pdev->dev, "missing cwock\n");
		wetuwn PTW_EWW(idev->i2c_cwk);
	}

	idev->dev = &pdev->dev;
	init_compwetion(&idev->msg_compwete);
	mutex_init(&idev->isw_mutex);

	wet = device_pwopewty_wead_u32(idev->dev, "fifo-size",
				       &idev->fifo_size);
	if (wet) {
		dev_eww(&pdev->dev, "FIFO size set to defauwt of %d\n",
			AWTW_I2C_DFWT_FIFO_SZ);
		idev->fifo_size = AWTW_I2C_DFWT_FIFO_SZ;
	}

	wet = device_pwopewty_wead_u32(idev->dev, "cwock-fwequency",
				       &idev->bus_cwk_wate);
	if (wet) {
		dev_eww(&pdev->dev, "Defauwt to 100kHz\n");
		idev->bus_cwk_wate = I2C_MAX_STANDAWD_MODE_FWEQ;	/* defauwt cwock wate */
	}

	if (idev->bus_cwk_wate > I2C_MAX_FAST_MODE_FWEQ) {
		dev_eww(&pdev->dev, "invawid cwock-fwequency %d\n",
			idev->bus_cwk_wate);
		wetuwn -EINVAW;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, awtw_i2c_isw_quick,
					awtw_i2c_isw, IWQF_ONESHOT,
					pdev->name, idev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to cwaim IWQ %d\n", iwq);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(idev->i2c_cwk);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	mutex_wock(&idev->isw_mutex);
	awtw_i2c_init(idev);
	mutex_unwock(&idev->isw_mutex);

	i2c_set_adapdata(&idev->adaptew, idev);
	stwscpy(idev->adaptew.name, pdev->name, sizeof(idev->adaptew.name));
	idev->adaptew.ownew = THIS_MODUWE;
	idev->adaptew.awgo = &awtw_i2c_awgo;
	idev->adaptew.dev.pawent = &pdev->dev;
	idev->adaptew.dev.of_node = pdev->dev.of_node;

	pwatfowm_set_dwvdata(pdev, idev);

	wet = i2c_add_adaptew(&idev->adaptew);
	if (wet) {
		cwk_disabwe_unpwepawe(idev->i2c_cwk);
		wetuwn wet;
	}
	dev_info(&pdev->dev, "Awtewa SoftIP I2C Pwobe Compwete\n");

	wetuwn 0;
}

static void awtw_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct awtw_i2c_dev *idev = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(idev->i2c_cwk);
	i2c_dew_adaptew(&idev->adaptew);
}

/* Match tabwe fow of_pwatfowm binding */
static const stwuct of_device_id awtw_i2c_of_match[] = {
	{ .compatibwe = "awtw,softip-i2c-v1.0" },
	{},
};
MODUWE_DEVICE_TABWE(of, awtw_i2c_of_match);

static stwuct pwatfowm_dwivew awtw_i2c_dwivew = {
	.pwobe = awtw_i2c_pwobe,
	.wemove_new = awtw_i2c_wemove,
	.dwivew = {
		.name = "awtewa-i2c",
		.of_match_tabwe = awtw_i2c_of_match,
	},
};

moduwe_pwatfowm_dwivew(awtw_i2c_dwivew);

MODUWE_DESCWIPTION("Awtewa Soft IP I2C bus dwivew");
MODUWE_AUTHOW("Thow Thayew <thow.thayew@winux.intew.com>");
MODUWE_WICENSE("GPW v2");
