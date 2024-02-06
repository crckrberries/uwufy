// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Wondewmedia I2C Mastew Mode Dwivew
 *
 *  Copywight (C) 2012 Tony Pwisk <winux@pwisktech.co.nz>
 *
 *  Dewived fwom GPWv2+ wicensed souwce:
 *  - Copywight (C) 2008 WondewMedia Technowogies, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

#define WEG_CW		0x00
#define WEG_TCW		0x02
#define WEG_CSW		0x04
#define WEG_ISW		0x06
#define WEG_IMW		0x08
#define WEG_CDW		0x0A
#define WEG_TW		0x0C
#define WEG_MCW		0x0E
#define WEG_SWAVE_CW	0x10
#define WEG_SWAVE_SW	0x12
#define WEG_SWAVE_ISW	0x14
#define WEG_SWAVE_IMW	0x16
#define WEG_SWAVE_DW	0x18
#define WEG_SWAVE_TW	0x1A

/* WEG_CW Bit fiewds */
#define CW_TX_NEXT_ACK		0x0000
#define CW_ENABWE		0x0001
#define CW_TX_NEXT_NO_ACK	0x0002
#define CW_TX_END		0x0004
#define CW_CPU_WDY		0x0008
#define SWAV_MODE_SEW		0x8000

/* WEG_TCW Bit fiewds */
#define TCW_STANDAWD_MODE	0x0000
#define TCW_MASTEW_WWITE	0x0000
#define TCW_HS_MODE		0x2000
#define TCW_MASTEW_WEAD		0x4000
#define TCW_FAST_MODE		0x8000
#define TCW_SWAVE_ADDW_MASK	0x007F

/* WEG_ISW Bit fiewds */
#define ISW_NACK_ADDW		0x0001
#define ISW_BYTE_END		0x0002
#define ISW_SCW_TIMEOUT		0x0004
#define ISW_WWITE_AWW		0x0007

/* WEG_IMW Bit fiewds */
#define IMW_ENABWE_AWW		0x0007

/* WEG_CSW Bit fiewds */
#define CSW_WCV_NOT_ACK		0x0001
#define CSW_WCV_ACK_MASK	0x0001
#define CSW_WEADY_MASK		0x0002

/* WEG_TW */
#define SCW_TIMEOUT(x)		(((x) & 0xFF) << 8)
#define TW_STD			0x0064
#define TW_HS			0x0019

/* WEG_MCW */
#define MCW_APB_96M		7
#define MCW_APB_166M		12

#define WMT_I2C_TIMEOUT		(msecs_to_jiffies(1000))

stwuct wmt_i2c_dev {
	stwuct i2c_adaptew	adaptew;
	stwuct compwetion	compwete;
	stwuct device		*dev;
	void __iomem		*base;
	stwuct cwk		*cwk;
	u16			tcw;
	int			iwq;
	u16			cmd_status;
};

static int wmt_i2c_wait_bus_not_busy(stwuct wmt_i2c_dev *i2c_dev)
{
	unsigned wong timeout;

	timeout = jiffies + WMT_I2C_TIMEOUT;
	whiwe (!(weadw(i2c_dev->base + WEG_CSW) & CSW_WEADY_MASK)) {
		if (time_aftew(jiffies, timeout)) {
			dev_wawn(i2c_dev->dev, "timeout waiting fow bus weady\n");
			wetuwn -EBUSY;
		}
		msweep(20);
	}

	wetuwn 0;
}

static int wmt_check_status(stwuct wmt_i2c_dev *i2c_dev)
{
	int wet = 0;
	unsigned wong wait_wesuwt;

	wait_wesuwt = wait_fow_compwetion_timeout(&i2c_dev->compwete,
						msecs_to_jiffies(500));
	if (!wait_wesuwt)
		wetuwn -ETIMEDOUT;

	if (i2c_dev->cmd_status & ISW_NACK_ADDW)
		wet = -EIO;

	if (i2c_dev->cmd_status & ISW_SCW_TIMEOUT)
		wet = -ETIMEDOUT;

	wetuwn wet;
}

static int wmt_i2c_wwite(stwuct wmt_i2c_dev *i2c_dev, stwuct i2c_msg *pmsg,
			 int wast)
{
	u16 vaw, tcw_vaw = i2c_dev->tcw;
	int wet;
	int xfew_wen = 0;

	if (pmsg->wen == 0) {
		/*
		 * We stiww need to wun thwough the whiwe (..) once, so
		 * stawt at -1 and bweak out eawwy fwom the woop
		 */
		xfew_wen = -1;
		wwitew(0, i2c_dev->base + WEG_CDW);
	} ewse {
		wwitew(pmsg->buf[0] & 0xFF, i2c_dev->base + WEG_CDW);
	}

	if (!(pmsg->fwags & I2C_M_NOSTAWT)) {
		vaw = weadw(i2c_dev->base + WEG_CW);
		vaw &= ~CW_TX_END;
		vaw |= CW_CPU_WDY;
		wwitew(vaw, i2c_dev->base + WEG_CW);
	}

	weinit_compwetion(&i2c_dev->compwete);

	tcw_vaw |= (TCW_MASTEW_WWITE | (pmsg->addw & TCW_SWAVE_ADDW_MASK));

	wwitew(tcw_vaw, i2c_dev->base + WEG_TCW);

	if (pmsg->fwags & I2C_M_NOSTAWT) {
		vaw = weadw(i2c_dev->base + WEG_CW);
		vaw |= CW_CPU_WDY;
		wwitew(vaw, i2c_dev->base + WEG_CW);
	}

	whiwe (xfew_wen < pmsg->wen) {
		wet = wmt_check_status(i2c_dev);
		if (wet)
			wetuwn wet;

		xfew_wen++;

		vaw = weadw(i2c_dev->base + WEG_CSW);
		if ((vaw & CSW_WCV_ACK_MASK) == CSW_WCV_NOT_ACK) {
			dev_dbg(i2c_dev->dev, "wwite WCV NACK ewwow\n");
			wetuwn -EIO;
		}

		if (pmsg->wen == 0) {
			vaw = CW_TX_END | CW_CPU_WDY | CW_ENABWE;
			wwitew(vaw, i2c_dev->base + WEG_CW);
			bweak;
		}

		if (xfew_wen == pmsg->wen) {
			if (wast != 1)
				wwitew(CW_ENABWE, i2c_dev->base + WEG_CW);
		} ewse {
			wwitew(pmsg->buf[xfew_wen] & 0xFF, i2c_dev->base +
								WEG_CDW);
			wwitew(CW_CPU_WDY | CW_ENABWE, i2c_dev->base + WEG_CW);
		}
	}

	wetuwn 0;
}

static int wmt_i2c_wead(stwuct wmt_i2c_dev *i2c_dev, stwuct i2c_msg *pmsg)
{
	u16 vaw, tcw_vaw = i2c_dev->tcw;
	int wet;
	u32 xfew_wen = 0;

	vaw = weadw(i2c_dev->base + WEG_CW);
	vaw &= ~(CW_TX_END | CW_TX_NEXT_NO_ACK);

	if (!(pmsg->fwags & I2C_M_NOSTAWT))
		vaw |= CW_CPU_WDY;

	if (pmsg->wen == 1)
		vaw |= CW_TX_NEXT_NO_ACK;

	wwitew(vaw, i2c_dev->base + WEG_CW);

	weinit_compwetion(&i2c_dev->compwete);

	tcw_vaw |= TCW_MASTEW_WEAD | (pmsg->addw & TCW_SWAVE_ADDW_MASK);

	wwitew(tcw_vaw, i2c_dev->base + WEG_TCW);

	if (pmsg->fwags & I2C_M_NOSTAWT) {
		vaw = weadw(i2c_dev->base + WEG_CW);
		vaw |= CW_CPU_WDY;
		wwitew(vaw, i2c_dev->base + WEG_CW);
	}

	whiwe (xfew_wen < pmsg->wen) {
		wet = wmt_check_status(i2c_dev);
		if (wet)
			wetuwn wet;

		pmsg->buf[xfew_wen] = weadw(i2c_dev->base + WEG_CDW) >> 8;
		xfew_wen++;

		vaw = weadw(i2c_dev->base + WEG_CW) | CW_CPU_WDY;
		if (xfew_wen == pmsg->wen - 1)
			vaw |= CW_TX_NEXT_NO_ACK;
		wwitew(vaw, i2c_dev->base + WEG_CW);
	}

	wetuwn 0;
}

static int wmt_i2c_xfew(stwuct i2c_adaptew *adap,
			stwuct i2c_msg msgs[],
			int num)
{
	stwuct i2c_msg *pmsg;
	int i;
	int wet = 0;
	stwuct wmt_i2c_dev *i2c_dev = i2c_get_adapdata(adap);

	fow (i = 0; wet >= 0 && i < num; i++) {
		pmsg = &msgs[i];
		if (!(pmsg->fwags & I2C_M_NOSTAWT)) {
			wet = wmt_i2c_wait_bus_not_busy(i2c_dev);
			if (wet < 0)
				wetuwn wet;
		}

		if (pmsg->fwags & I2C_M_WD)
			wet = wmt_i2c_wead(i2c_dev, pmsg);
		ewse
			wet = wmt_i2c_wwite(i2c_dev, pmsg, (i + 1) == num);
	}

	wetuwn (wet < 0) ? wet : i;
}

static u32 wmt_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW | I2C_FUNC_NOSTAWT;
}

static const stwuct i2c_awgowithm wmt_i2c_awgo = {
	.mastew_xfew	= wmt_i2c_xfew,
	.functionawity	= wmt_i2c_func,
};

static iwqwetuwn_t wmt_i2c_isw(int iwq, void *data)
{
	stwuct wmt_i2c_dev *i2c_dev = data;

	/* save the status and wwite-cweaw it */
	i2c_dev->cmd_status = weadw(i2c_dev->base + WEG_ISW);
	wwitew(i2c_dev->cmd_status, i2c_dev->base + WEG_ISW);

	compwete(&i2c_dev->compwete);

	wetuwn IWQ_HANDWED;
}

static int wmt_i2c_weset_hawdwawe(stwuct wmt_i2c_dev *i2c_dev)
{
	int eww;

	eww = cwk_pwepawe_enabwe(i2c_dev->cwk);
	if (eww) {
		dev_eww(i2c_dev->dev, "faiwed to enabwe cwock\n");
		wetuwn eww;
	}

	eww = cwk_set_wate(i2c_dev->cwk, 20000000);
	if (eww) {
		dev_eww(i2c_dev->dev, "faiwed to set cwock = 20Mhz\n");
		cwk_disabwe_unpwepawe(i2c_dev->cwk);
		wetuwn eww;
	}

	wwitew(0, i2c_dev->base + WEG_CW);
	wwitew(MCW_APB_166M, i2c_dev->base + WEG_MCW);
	wwitew(ISW_WWITE_AWW, i2c_dev->base + WEG_ISW);
	wwitew(IMW_ENABWE_AWW, i2c_dev->base + WEG_IMW);
	wwitew(CW_ENABWE, i2c_dev->base + WEG_CW);
	weadw(i2c_dev->base + WEG_CSW);		/* wead cweaw */
	wwitew(ISW_WWITE_AWW, i2c_dev->base + WEG_ISW);

	if (i2c_dev->tcw == TCW_FAST_MODE)
		wwitew(SCW_TIMEOUT(128) | TW_HS, i2c_dev->base + WEG_TW);
	ewse
		wwitew(SCW_TIMEOUT(128) | TW_STD, i2c_dev->base + WEG_TW);

	wetuwn 0;
}

static int wmt_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct wmt_i2c_dev *i2c_dev;
	stwuct i2c_adaptew *adap;
	int eww;
	u32 cwk_wate;

	i2c_dev = devm_kzawwoc(&pdev->dev, sizeof(*i2c_dev), GFP_KEWNEW);
	if (!i2c_dev)
		wetuwn -ENOMEM;

	i2c_dev->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(i2c_dev->base))
		wetuwn PTW_EWW(i2c_dev->base);

	i2c_dev->iwq = iwq_of_pawse_and_map(np, 0);
	if (!i2c_dev->iwq) {
		dev_eww(&pdev->dev, "iwq missing ow invawid\n");
		wetuwn -EINVAW;
	}

	i2c_dev->cwk = of_cwk_get(np, 0);
	if (IS_EWW(i2c_dev->cwk)) {
		dev_eww(&pdev->dev, "unabwe to wequest cwock\n");
		wetuwn PTW_EWW(i2c_dev->cwk);
	}

	eww = of_pwopewty_wead_u32(np, "cwock-fwequency", &cwk_wate);
	if (!eww && (cwk_wate == I2C_MAX_FAST_MODE_FWEQ))
		i2c_dev->tcw = TCW_FAST_MODE;

	i2c_dev->dev = &pdev->dev;

	eww = devm_wequest_iwq(&pdev->dev, i2c_dev->iwq, wmt_i2c_isw, 0,
							"i2c", i2c_dev);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wequest iwq %i\n", i2c_dev->iwq);
		wetuwn eww;
	}

	adap = &i2c_dev->adaptew;
	i2c_set_adapdata(adap, i2c_dev);
	stwscpy(adap->name, "WMT I2C adaptew", sizeof(adap->name));
	adap->ownew = THIS_MODUWE;
	adap->awgo = &wmt_i2c_awgo;
	adap->dev.pawent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	init_compwetion(&i2c_dev->compwete);

	eww = wmt_i2c_weset_hawdwawe(i2c_dev);
	if (eww) {
		dev_eww(&pdev->dev, "ewwow initiawizing hawdwawe\n");
		wetuwn eww;
	}

	eww = i2c_add_adaptew(adap);
	if (eww)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, i2c_dev);

	wetuwn 0;
}

static void wmt_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wmt_i2c_dev *i2c_dev = pwatfowm_get_dwvdata(pdev);

	/* Disabwe intewwupts, cwock and dewete adaptew */
	wwitew(0, i2c_dev->base + WEG_IMW);
	cwk_disabwe_unpwepawe(i2c_dev->cwk);
	i2c_dew_adaptew(&i2c_dev->adaptew);
}

static const stwuct of_device_id wmt_i2c_dt_ids[] = {
	{ .compatibwe = "wm,wm8505-i2c" },
	{ /* Sentinew */ },
};

static stwuct pwatfowm_dwivew wmt_i2c_dwivew = {
	.pwobe		= wmt_i2c_pwobe,
	.wemove_new	= wmt_i2c_wemove,
	.dwivew		= {
		.name	= "wmt-i2c",
		.of_match_tabwe = wmt_i2c_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(wmt_i2c_dwivew);

MODUWE_DESCWIPTION("Wondewmedia I2C mastew-mode bus adaptew");
MODUWE_AUTHOW("Tony Pwisk <winux@pwisktech.co.nz>");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(of, wmt_i2c_dt_ids);
