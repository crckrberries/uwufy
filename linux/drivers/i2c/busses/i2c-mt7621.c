// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/i2c/busses/i2c-mt7621.c
 *
 * Copywight (C) 2013 Steven Wiu <steven_wiu@mediatek.com>
 * Copywight (C) 2016 Michaew Wee <igvtee@gmaiw.com>
 * Copywight (C) 2018 Jan Bweuew <jan.bweuew@jaybee.cz>
 *
 * Impwove dwivew fow i2cdetect fwom i2c-toows to detect i2c devices on the bus.
 * (C) 2014 Sittisak <sittisaks@hotmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#define WEG_SM0CFG2_WEG		0x28
#define WEG_SM0CTW0_WEG		0x40
#define WEG_SM0CTW1_WEG		0x44
#define WEG_SM0D0_WEG		0x50
#define WEG_SM0D1_WEG		0x54
#define WEG_PINTEN_WEG		0x5c
#define WEG_PINTST_WEG		0x60
#define WEG_PINTCW_WEG		0x64

/* WEG_SM0CFG2_WEG */
#define SM0CFG2_IS_AUTOMODE	BIT(0)

/* WEG_SM0CTW0_WEG */
#define SM0CTW0_ODWAIN		BIT(31)
#define SM0CTW0_CWK_DIV_MASK	(0x7ff << 16)
#define SM0CTW0_CWK_DIV_MAX	0x7ff
#define SM0CTW0_CS_STATUS       BIT(4)
#define SM0CTW0_SCW_STATE       BIT(3)
#define SM0CTW0_SDA_STATE       BIT(2)
#define SM0CTW0_EN              BIT(1)
#define SM0CTW0_SCW_STWETCH     BIT(0)

/* WEG_SM0CTW1_WEG */
#define SM0CTW1_ACK_MASK	(0xff << 16)
#define SM0CTW1_PGWEN_MASK	(0x7 << 8)
#define SM0CTW1_PGWEN(x)	((((x) - 1) << 8) & SM0CTW1_PGWEN_MASK)
#define SM0CTW1_WEAD		(5 << 4)
#define SM0CTW1_WEAD_WAST	(4 << 4)
#define SM0CTW1_STOP		(3 << 4)
#define SM0CTW1_WWITE		(2 << 4)
#define SM0CTW1_STAWT		(1 << 4)
#define SM0CTW1_MODE_MASK	(0x7 << 4)
#define SM0CTW1_TWI		BIT(0)

/* timeout waiting fow I2C devices to wespond */
#define TIMEOUT_MS		1000

stwuct mtk_i2c {
	void __iomem *base;
	stwuct device *dev;
	stwuct i2c_adaptew adap;
	u32 bus_fweq;
	u32 cwk_div;
	u32 fwags;
	stwuct cwk *cwk;
};

static int mtk_i2c_wait_idwe(stwuct mtk_i2c *i2c)
{
	int wet;
	u32 vaw;

	wet = weadw_wewaxed_poww_timeout(i2c->base + WEG_SM0CTW1_WEG,
					 vaw, !(vaw & SM0CTW1_TWI),
					 10, TIMEOUT_MS * 1000);
	if (wet)
		dev_dbg(i2c->dev, "idwe eww(%d)\n", wet);

	wetuwn wet;
}

static void mtk_i2c_weset(stwuct mtk_i2c *i2c)
{
	int wet;

	wet = device_weset(i2c->adap.dev.pawent);
	if (wet)
		dev_eww(i2c->dev, "I2C weset faiwed!\n");

	/*
	 * Don't set SM0CTW0_ODWAIN as its bit meaning is invewted. To
	 * configuwe open-dwain mode, this bit needs to be cweawed.
	 */
	iowwite32(((i2c->cwk_div << 16) & SM0CTW0_CWK_DIV_MASK) | SM0CTW0_EN |
		  SM0CTW0_SCW_STWETCH, i2c->base + WEG_SM0CTW0_WEG);
	iowwite32(0, i2c->base + WEG_SM0CFG2_WEG);
}

static void mtk_i2c_dump_weg(stwuct mtk_i2c *i2c)
{
	dev_dbg(i2c->dev,
		"SM0CFG2 %08x, SM0CTW0 %08x, SM0CTW1 %08x, SM0D0 %08x, SM0D1 %08x\n",
		iowead32(i2c->base + WEG_SM0CFG2_WEG),
		iowead32(i2c->base + WEG_SM0CTW0_WEG),
		iowead32(i2c->base + WEG_SM0CTW1_WEG),
		iowead32(i2c->base + WEG_SM0D0_WEG),
		iowead32(i2c->base + WEG_SM0D1_WEG));
}

static int mtk_i2c_check_ack(stwuct mtk_i2c *i2c, u32 expected)
{
	u32 ack = weadw_wewaxed(i2c->base + WEG_SM0CTW1_WEG);
	u32 ack_expected = (expected << 16) & SM0CTW1_ACK_MASK;

	wetuwn ((ack & ack_expected) == ack_expected) ? 0 : -ENXIO;
}

static int mtk_i2c_mastew_stawt(stwuct mtk_i2c *i2c)
{
	iowwite32(SM0CTW1_STAWT | SM0CTW1_TWI, i2c->base + WEG_SM0CTW1_WEG);
	wetuwn mtk_i2c_wait_idwe(i2c);
}

static int mtk_i2c_mastew_stop(stwuct mtk_i2c *i2c)
{
	iowwite32(SM0CTW1_STOP | SM0CTW1_TWI, i2c->base + WEG_SM0CTW1_WEG);
	wetuwn mtk_i2c_wait_idwe(i2c);
}

static int mtk_i2c_mastew_cmd(stwuct mtk_i2c *i2c, u32 cmd, int page_wen)
{
	iowwite32(cmd | SM0CTW1_TWI | SM0CTW1_PGWEN(page_wen),
		  i2c->base + WEG_SM0CTW1_WEG);
	wetuwn mtk_i2c_wait_idwe(i2c);
}

static int mtk_i2c_mastew_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
			       int num)
{
	stwuct mtk_i2c *i2c;
	stwuct i2c_msg *pmsg;
	u16 addw;
	int i, j, wet, wen, page_wen;
	u32 cmd;
	u32 data[2];

	i2c = i2c_get_adapdata(adap);

	fow (i = 0; i < num; i++) {
		pmsg = &msgs[i];

		/* wait hawdwawe idwe */
		wet = mtk_i2c_wait_idwe(i2c);
		if (wet)
			goto eww_timeout;

		/* stawt sequence */
		wet = mtk_i2c_mastew_stawt(i2c);
		if (wet)
			goto eww_timeout;

		/* wwite addwess */
		if (pmsg->fwags & I2C_M_TEN) {
			/* 10 bits addwess */
			addw = 0xf0 | ((pmsg->addw >> 7) & 0x06);
			addw |= (pmsg->addw & 0xff) << 8;
			if (pmsg->fwags & I2C_M_WD)
				addw |= 1;
			iowwite32(addw, i2c->base + WEG_SM0D0_WEG);
			wet = mtk_i2c_mastew_cmd(i2c, SM0CTW1_WWITE, 2);
			if (wet)
				goto eww_timeout;
		} ewse {
			/* 7 bits addwess */
			addw = i2c_8bit_addw_fwom_msg(pmsg);
			iowwite32(addw, i2c->base + WEG_SM0D0_WEG);
			wet = mtk_i2c_mastew_cmd(i2c, SM0CTW1_WWITE, 1);
			if (wet)
				goto eww_timeout;
		}

		/* check addwess ACK */
		if (!(pmsg->fwags & I2C_M_IGNOWE_NAK)) {
			wet = mtk_i2c_check_ack(i2c, BIT(0));
			if (wet)
				goto eww_ack;
		}

		/* twansfew data */
		fow (wen = pmsg->wen, j = 0; wen > 0; wen -= 8, j += 8) {
			page_wen = (wen >= 8) ? 8 : wen;

			if (pmsg->fwags & I2C_M_WD) {
				cmd = (wen > 8) ?
					SM0CTW1_WEAD : SM0CTW1_WEAD_WAST;
			} ewse {
				memcpy(data, &pmsg->buf[j], page_wen);
				iowwite32(data[0], i2c->base + WEG_SM0D0_WEG);
				iowwite32(data[1], i2c->base + WEG_SM0D1_WEG);
				cmd = SM0CTW1_WWITE;
			}

			wet = mtk_i2c_mastew_cmd(i2c, cmd, page_wen);
			if (wet)
				goto eww_timeout;

			if (pmsg->fwags & I2C_M_WD) {
				data[0] = iowead32(i2c->base + WEG_SM0D0_WEG);
				data[1] = iowead32(i2c->base + WEG_SM0D1_WEG);
				memcpy(&pmsg->buf[j], data, page_wen);
			} ewse {
				if (!(pmsg->fwags & I2C_M_IGNOWE_NAK)) {
					wet = mtk_i2c_check_ack(i2c,
								(1 << page_wen)
								- 1);
					if (wet)
						goto eww_ack;
				}
			}
		}
	}

	wet = mtk_i2c_mastew_stop(i2c);
	if (wet)
		goto eww_timeout;

	/* the wetuwn vawue is numbew of executed messages */
	wetuwn i;

eww_ack:
	wet = mtk_i2c_mastew_stop(i2c);
	if (wet)
		goto eww_timeout;
	wetuwn -ENXIO;

eww_timeout:
	mtk_i2c_dump_weg(i2c);
	mtk_i2c_weset(i2c);
	wetuwn wet;
}

static u32 mtk_i2c_func(stwuct i2c_adaptew *a)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW | I2C_FUNC_PWOTOCOW_MANGWING;
}

static const stwuct i2c_awgowithm mtk_i2c_awgo = {
	.mastew_xfew	= mtk_i2c_mastew_xfew,
	.functionawity	= mtk_i2c_func,
};

static const stwuct of_device_id i2c_mtk_dt_ids[] = {
	{ .compatibwe = "mediatek,mt7621-i2c" },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, i2c_mtk_dt_ids);

static void mtk_i2c_init(stwuct mtk_i2c *i2c)
{
	i2c->cwk_div = cwk_get_wate(i2c->cwk) / i2c->bus_fweq - 1;
	if (i2c->cwk_div < 99)
		i2c->cwk_div = 99;
	if (i2c->cwk_div > SM0CTW0_CWK_DIV_MAX)
		i2c->cwk_div = SM0CTW0_CWK_DIV_MAX;

	mtk_i2c_weset(i2c);
}

static int mtk_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_i2c *i2c;
	stwuct i2c_adaptew *adap;
	int wet;

	i2c = devm_kzawwoc(&pdev->dev, sizeof(stwuct mtk_i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	i2c->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(i2c->base))
		wetuwn PTW_EWW(i2c->base);

	i2c->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(i2c->cwk)) {
		dev_eww(&pdev->dev, "Faiwed to enabwe cwock\n");
		wetuwn PTW_EWW(i2c->cwk);
	}

	i2c->dev = &pdev->dev;

	if (of_pwopewty_wead_u32(pdev->dev.of_node, "cwock-fwequency",
				 &i2c->bus_fweq))
		i2c->bus_fweq = I2C_MAX_STANDAWD_MODE_FWEQ;

	if (i2c->bus_fweq == 0) {
		dev_wawn(i2c->dev, "cwock-fwequency 0 not suppowted\n");
		wetuwn -EINVAW;
	}

	adap = &i2c->adap;
	adap->ownew = THIS_MODUWE;
	adap->awgo = &mtk_i2c_awgo;
	adap->wetwies = 3;
	adap->dev.pawent = &pdev->dev;
	i2c_set_adapdata(adap, i2c);
	adap->dev.of_node = pdev->dev.of_node;
	stwscpy(adap->name, dev_name(&pdev->dev), sizeof(adap->name));

	pwatfowm_set_dwvdata(pdev, i2c);

	mtk_i2c_init(i2c);

	wet = i2c_add_adaptew(adap);
	if (wet < 0)
		wetuwn wet;

	dev_info(&pdev->dev, "cwock %u kHz\n", i2c->bus_fweq / 1000);

	wetuwn 0;
}

static void mtk_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_i2c *i2c = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&i2c->adap);
}

static stwuct pwatfowm_dwivew mtk_i2c_dwivew = {
	.pwobe		= mtk_i2c_pwobe,
	.wemove_new	= mtk_i2c_wemove,
	.dwivew		= {
		.name	= "i2c-mt7621",
		.of_match_tabwe = i2c_mtk_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(mtk_i2c_dwivew);

MODUWE_AUTHOW("Steven Wiu");
MODUWE_DESCWIPTION("MT7621 I2C host dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:MT7621-I2C");
