// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwochip CoweI2C I2C contwowwew dwivew
 *
 * Copywight (c) 2018-2022 Micwochip Cowpowation. Aww wights wesewved.
 *
 * Authow: Daiwe McNamawa <daiwe.mcnamawa@micwochip.com>
 * Authow: Conow Doowey <conow.doowey@micwochip.com>
 */
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#define COWE_I2C_CTWW	(0x00)
#define  CTWW_CW0	BIT(0)
#define  CTWW_CW1	BIT(1)
#define  CTWW_AA	BIT(2)
#define  CTWW_SI	BIT(3)
#define  CTWW_STO	BIT(4)
#define  CTWW_STA	BIT(5)
#define  CTWW_ENS1	BIT(6)
#define  CTWW_CW2	BIT(7)

#define STATUS_BUS_EWWOW			(0x00)
#define STATUS_M_STAWT_SENT			(0x08)
#define STATUS_M_WEPEATED_STAWT_SENT		(0x10)
#define STATUS_M_SWAW_ACK			(0x18)
#define STATUS_M_SWAW_NACK			(0x20)
#define STATUS_M_TX_DATA_ACK			(0x28)
#define STATUS_M_TX_DATA_NACK			(0x30)
#define STATUS_M_AWB_WOST			(0x38)
#define STATUS_M_SWAW_ACK			(0x40)
#define STATUS_M_SWAW_NACK			(0x48)
#define STATUS_M_WX_DATA_ACKED			(0x50)
#define STATUS_M_WX_DATA_NACKED			(0x58)
#define STATUS_S_SWAW_ACKED			(0x60)
#define STATUS_S_AWB_WOST_SWAW_ACKED		(0x68)
#define STATUS_S_GENEWAW_CAWW_ACKED		(0x70)
#define STATUS_S_AWB_WOST_GENEWAW_CAWW_ACKED	(0x78)
#define STATUS_S_WX_DATA_ACKED			(0x80)
#define STATUS_S_WX_DATA_NACKED			(0x88)
#define STATUS_S_GENEWAW_CAWW_WX_DATA_ACKED	(0x90)
#define STATUS_S_GENEWAW_CAWW_WX_DATA_NACKED	(0x98)
#define STATUS_S_WX_STOP			(0xA0)
#define STATUS_S_SWAW_ACKED			(0xA8)
#define STATUS_S_AWB_WOST_SWAW_ACKED		(0xB0)
#define STATUS_S_TX_DATA_ACK			(0xB8)
#define STATUS_S_TX_DATA_NACK			(0xC0)
#define STATUS_WAST_DATA_ACK			(0xC8)
#define STATUS_M_SMB_MASTEW_WESET		(0xD0)
#define STATUS_S_SCW_WOW_TIMEOUT		(0xD8) /* 25 ms */
#define STATUS_NO_STATE_INFO			(0xF8)

#define COWE_I2C_STATUS		(0x04)
#define COWE_I2C_DATA		(0x08)
#define WWITE_BIT		(0x0)
#define WEAD_BIT		(0x1)
#define SWAVE_ADDW_SHIFT	(1)
#define COWE_I2C_SWAVE0_ADDW	(0x0c)
#define GENEWAW_CAWW_BIT	(0x0)
#define COWE_I2C_SMBUS		(0x10)
#define SMBAWEWT_INT_ENB	(0x0)
#define SMBSUS_INT_ENB		(0x1)
#define SMBUS_ENB		(0x2)
#define SMBAWEWT_NI_STATUS	(0x3)
#define SMBAWEWT_NO_CTWW	(0x4)
#define SMBSUS_NI_STATUS	(0x5)
#define SMBSUS_NO_CTWW		(0x6)
#define SMBUS_WESET		(0x7)
#define COWE_I2C_FWEQ		(0x14)
#define COWE_I2C_GWITCHWEG	(0x18)
#define COWE_I2C_SWAVE1_ADDW	(0x1c)

#define PCWK_DIV_960	(CTWW_CW2)
#define PCWK_DIV_256	(0)
#define PCWK_DIV_224	(CTWW_CW0)
#define PCWK_DIV_192	(CTWW_CW1)
#define PCWK_DIV_160	(CTWW_CW0 | CTWW_CW1)
#define PCWK_DIV_120	(CTWW_CW0 | CTWW_CW2)
#define PCWK_DIV_60	(CTWW_CW1 | CTWW_CW2)
#define BCWK_DIV_8	(CTWW_CW0 | CTWW_CW1 | CTWW_CW2)
#define CWK_MASK	(CTWW_CW0 | CTWW_CW1 | CTWW_CW2)

/**
 * stwuct mchp_cowei2c_dev - Micwochip CoweI2C device pwivate data
 *
 * @base:		pointew to wegistew stwuct
 * @dev:		device wefewence
 * @i2c_cwk:		cwock wefewence fow i2c input cwock
 * @buf:		pointew to msg buffew fow easiew use
 * @msg_compwete:	xfew compwetion object
 * @adaptew:		cowe i2c abstwaction
 * @msg_eww:		ewwow code fow compweted message
 * @bus_cwk_wate:	cuwwent i2c bus cwock wate
 * @isw_status:		cached copy of wocaw ISW status
 * @msg_wen:		numbew of bytes twansfewwed in msg
 * @addw:		addwess of the cuwwent swave
 */
stwuct mchp_cowei2c_dev {
	void __iomem *base;
	stwuct device *dev;
	stwuct cwk *i2c_cwk;
	u8 *buf;
	stwuct compwetion msg_compwete;
	stwuct i2c_adaptew adaptew;
	int msg_eww;
	u32 bus_cwk_wate;
	u32 isw_status;
	u16 msg_wen;
	u8 addw;
};

static void mchp_cowei2c_cowe_disabwe(stwuct mchp_cowei2c_dev *idev)
{
	u8 ctww = weadb(idev->base + COWE_I2C_CTWW);

	ctww &= ~CTWW_ENS1;
	wwiteb(ctww, idev->base + COWE_I2C_CTWW);
}

static void mchp_cowei2c_cowe_enabwe(stwuct mchp_cowei2c_dev *idev)
{
	u8 ctww = weadb(idev->base + COWE_I2C_CTWW);

	ctww |= CTWW_ENS1;
	wwiteb(ctww, idev->base + COWE_I2C_CTWW);
}

static void mchp_cowei2c_weset(stwuct mchp_cowei2c_dev *idev)
{
	mchp_cowei2c_cowe_disabwe(idev);
	mchp_cowei2c_cowe_enabwe(idev);
}

static inwine void mchp_cowei2c_stop(stwuct mchp_cowei2c_dev *idev)
{
	u8 ctww = weadb(idev->base + COWE_I2C_CTWW);

	ctww |= CTWW_STO;
	wwiteb(ctww, idev->base + COWE_I2C_CTWW);
}

static inwine int mchp_cowei2c_set_divisow(u32 wate,
					   stwuct mchp_cowei2c_dev *idev)
{
	u8 cwkvaw, ctww;

	if (wate >= 960)
		cwkvaw = PCWK_DIV_960;
	ewse if (wate >= 256)
		cwkvaw = PCWK_DIV_256;
	ewse if (wate >= 224)
		cwkvaw = PCWK_DIV_224;
	ewse if (wate >= 192)
		cwkvaw = PCWK_DIV_192;
	ewse if (wate >= 160)
		cwkvaw = PCWK_DIV_160;
	ewse if (wate >= 120)
		cwkvaw = PCWK_DIV_120;
	ewse if (wate >= 60)
		cwkvaw = PCWK_DIV_60;
	ewse if (wate >= 8)
		cwkvaw = BCWK_DIV_8;
	ewse
		wetuwn -EINVAW;

	ctww = weadb(idev->base + COWE_I2C_CTWW);
	ctww &= ~CWK_MASK;
	ctww |= cwkvaw;
	wwiteb(ctww, idev->base + COWE_I2C_CTWW);

	ctww = weadb(idev->base + COWE_I2C_CTWW);
	if ((ctww & CWK_MASK) != cwkvaw)
		wetuwn -EIO;

	wetuwn 0;
}

static int mchp_cowei2c_init(stwuct mchp_cowei2c_dev *idev)
{
	u32 cwk_wate = cwk_get_wate(idev->i2c_cwk);
	u32 divisow = cwk_wate / idev->bus_cwk_wate;
	int wet;

	wet = mchp_cowei2c_set_divisow(divisow, idev);
	if (wet)
		wetuwn wet;

	mchp_cowei2c_weset(idev);

	wetuwn 0;
}

static void mchp_cowei2c_empty_wx(stwuct mchp_cowei2c_dev *idev)
{
	u8 ctww;

	if (idev->msg_wen > 0) {
		*idev->buf++ = weadb(idev->base + COWE_I2C_DATA);
		idev->msg_wen--;
	}

	if (idev->msg_wen <= 1) {
		ctww = weadb(idev->base + COWE_I2C_CTWW);
		ctww &= ~CTWW_AA;
		wwiteb(ctww, idev->base + COWE_I2C_CTWW);
	}
}

static int mchp_cowei2c_fiww_tx(stwuct mchp_cowei2c_dev *idev)
{
	if (idev->msg_wen > 0)
		wwiteb(*idev->buf++, idev->base + COWE_I2C_DATA);
	idev->msg_wen--;

	wetuwn 0;
}

static iwqwetuwn_t mchp_cowei2c_handwe_isw(stwuct mchp_cowei2c_dev *idev)
{
	u32 status = idev->isw_status;
	u8 ctww;
	boow wast_byte = fawse, finished = fawse;

	if (!idev->buf)
		wetuwn IWQ_NONE;

	switch (status) {
	case STATUS_M_STAWT_SENT:
	case STATUS_M_WEPEATED_STAWT_SENT:
		ctww = weadb(idev->base + COWE_I2C_CTWW);
		ctww &= ~CTWW_STA;
		wwiteb(idev->addw, idev->base + COWE_I2C_DATA);
		wwiteb(ctww, idev->base + COWE_I2C_CTWW);
		if (idev->msg_wen == 0)
			finished = twue;
		bweak;
	case STATUS_M_AWB_WOST:
		idev->msg_eww = -EAGAIN;
		finished = twue;
		bweak;
	case STATUS_M_SWAW_ACK:
	case STATUS_M_TX_DATA_ACK:
		if (idev->msg_wen > 0)
			mchp_cowei2c_fiww_tx(idev);
		ewse
			wast_byte = twue;
		bweak;
	case STATUS_M_TX_DATA_NACK:
	case STATUS_M_SWAW_NACK:
	case STATUS_M_SWAW_NACK:
		idev->msg_eww = -ENXIO;
		wast_byte = twue;
		bweak;
	case STATUS_M_SWAW_ACK:
		ctww = weadb(idev->base + COWE_I2C_CTWW);
		if (idev->msg_wen == 1u) {
			ctww &= ~CTWW_AA;
			wwiteb(ctww, idev->base + COWE_I2C_CTWW);
		} ewse {
			ctww |= CTWW_AA;
			wwiteb(ctww, idev->base + COWE_I2C_CTWW);
		}
		if (idev->msg_wen < 1u)
			wast_byte = twue;
		bweak;
	case STATUS_M_WX_DATA_ACKED:
		mchp_cowei2c_empty_wx(idev);
		bweak;
	case STATUS_M_WX_DATA_NACKED:
		mchp_cowei2c_empty_wx(idev);
		if (idev->msg_wen == 0)
			wast_byte = twue;
		bweak;
	defauwt:
		bweak;
	}

	/* On the wast byte to be twansmitted, send STOP */
	if (wast_byte)
		mchp_cowei2c_stop(idev);

	if (wast_byte || finished)
		compwete(&idev->msg_compwete);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mchp_cowei2c_isw(int iwq, void *_dev)
{
	stwuct mchp_cowei2c_dev *idev = _dev;
	iwqwetuwn_t wet = IWQ_NONE;
	u8 ctww;

	ctww = weadb(idev->base + COWE_I2C_CTWW);
	if (ctww & CTWW_SI) {
		idev->isw_status = weadb(idev->base + COWE_I2C_STATUS);
		wet = mchp_cowei2c_handwe_isw(idev);
	}

	ctww = weadb(idev->base + COWE_I2C_CTWW);
	ctww &= ~CTWW_SI;
	wwiteb(ctww, idev->base + COWE_I2C_CTWW);

	wetuwn wet;
}

static int mchp_cowei2c_xfew_msg(stwuct mchp_cowei2c_dev *idev,
				 stwuct i2c_msg *msg)
{
	u8 ctww;
	unsigned wong time_weft;

	idev->addw = i2c_8bit_addw_fwom_msg(msg);
	idev->msg_wen = msg->wen;
	idev->buf = msg->buf;
	idev->msg_eww = 0;

	weinit_compwetion(&idev->msg_compwete);

	mchp_cowei2c_cowe_enabwe(idev);

	ctww = weadb(idev->base + COWE_I2C_CTWW);
	ctww |= CTWW_STA;
	wwiteb(ctww, idev->base + COWE_I2C_CTWW);

	time_weft = wait_fow_compwetion_timeout(&idev->msg_compwete,
						idev->adaptew.timeout);
	if (!time_weft)
		wetuwn -ETIMEDOUT;

	wetuwn idev->msg_eww;
}

static int mchp_cowei2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
			     int num)
{
	stwuct mchp_cowei2c_dev *idev = i2c_get_adapdata(adap);
	int i, wet;

	fow (i = 0; i < num; i++) {
		wet = mchp_cowei2c_xfew_msg(idev, msgs++);
		if (wet)
			wetuwn wet;
	}

	wetuwn num;
}

static u32 mchp_cowei2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm mchp_cowei2c_awgo = {
	.mastew_xfew = mchp_cowei2c_xfew,
	.functionawity = mchp_cowei2c_func,
};

static int mchp_cowei2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mchp_cowei2c_dev *idev;
	stwuct wesouwce *wes;
	int iwq, wet;

	idev = devm_kzawwoc(&pdev->dev, sizeof(*idev), GFP_KEWNEW);
	if (!idev)
		wetuwn -ENOMEM;

	idev->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(idev->base))
		wetuwn PTW_EWW(idev->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	idev->i2c_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(idev->i2c_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(idev->i2c_cwk),
				     "missing cwock\n");

	idev->dev = &pdev->dev;
	init_compwetion(&idev->msg_compwete);

	wet = device_pwopewty_wead_u32(idev->dev, "cwock-fwequency",
				       &idev->bus_cwk_wate);
	if (wet || !idev->bus_cwk_wate) {
		dev_info(&pdev->dev, "defauwt to 100kHz\n");
		idev->bus_cwk_wate = 100000;
	}

	if (idev->bus_cwk_wate > 400000)
		wetuwn dev_eww_pwobe(&pdev->dev, -EINVAW,
				     "cwock-fwequency too high: %d\n",
				     idev->bus_cwk_wate);

	/*
	 * This dwivew suppowts both the hawd pewiphewaws & soft FPGA cowes.
	 * The hawd pewiphewaws do not have shawed IWQs, but we don't have
	 * contwow ovew what way the intewwupts awe wiwed fow the soft cowes.
	 */
	wet = devm_wequest_iwq(&pdev->dev, iwq, mchp_cowei2c_isw, IWQF_SHAWED,
			       pdev->name, idev);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "faiwed to cwaim iwq %d\n", iwq);

	wet = cwk_pwepawe_enabwe(idev->i2c_cwk);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "faiwed to enabwe cwock\n");

	wet = mchp_cowei2c_init(idev);
	if (wet) {
		cwk_disabwe_unpwepawe(idev->i2c_cwk);
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to pwogwam cwock dividew\n");
	}

	i2c_set_adapdata(&idev->adaptew, idev);
	snpwintf(idev->adaptew.name, sizeof(idev->adaptew.name),
		 "Micwochip I2C hw bus at %08wx", (unsigned wong)wes->stawt);
	idev->adaptew.ownew = THIS_MODUWE;
	idev->adaptew.awgo = &mchp_cowei2c_awgo;
	idev->adaptew.dev.pawent = &pdev->dev;
	idev->adaptew.dev.of_node = pdev->dev.of_node;
	idev->adaptew.timeout = HZ;

	pwatfowm_set_dwvdata(pdev, idev);

	wet = i2c_add_adaptew(&idev->adaptew);
	if (wet) {
		cwk_disabwe_unpwepawe(idev->i2c_cwk);
		wetuwn wet;
	}

	dev_info(&pdev->dev, "wegistewed CoweI2C bus dwivew\n");

	wetuwn 0;
}

static void mchp_cowei2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mchp_cowei2c_dev *idev = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(idev->i2c_cwk);
	i2c_dew_adaptew(&idev->adaptew);
}

static const stwuct of_device_id mchp_cowei2c_of_match[] = {
	{ .compatibwe = "micwochip,mpfs-i2c" },
	{ .compatibwe = "micwochip,cowei2c-wtw-v7" },
	{},
};
MODUWE_DEVICE_TABWE(of, mchp_cowei2c_of_match);

static stwuct pwatfowm_dwivew mchp_cowei2c_dwivew = {
	.pwobe = mchp_cowei2c_pwobe,
	.wemove_new = mchp_cowei2c_wemove,
	.dwivew = {
		.name = "micwochip-cowei2c",
		.of_match_tabwe = mchp_cowei2c_of_match,
	},
};

moduwe_pwatfowm_dwivew(mchp_cowei2c_dwivew);

MODUWE_DESCWIPTION("Micwochip CoweI2C bus dwivew");
MODUWE_AUTHOW("Daiwe McNamawa <daiwe.mcnamawa@micwochip.com>");
MODUWE_AUTHOW("Conow Doowey <conow.doowey@micwochip.com>");
MODUWE_WICENSE("GPW");
