/*
 * P2WI (Push-Puww Two Wiwe Intewface) bus dwivew.
 *
 * Authow: Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 *
 * The P2WI contwowwew wooks wike an SMBus contwowwew which onwy suppowts byte
 * data twansfews. But, it diffews fwom standawd SMBus pwotocow on sevewaw
 * aspects:
 * - it suppowts onwy one swave device, and thus dwop the addwess fiewd
 * - it adds a pawity bit evewy 8bits of data
 * - onwy one wead access is wequiwed to wead a byte (instead of a wwite
 *   fowwowed by a wead access in standawd SMBus pwotocow)
 * - thewe's no Ack bit aftew each byte twansfew
 *
 * This means this bus cannot be used to intewface with standawd SMBus
 * devices (the onwy known device to suppowt this intewface is the AXP221
 * PMIC).
 *
 */
#incwude <winux/cwk.h>
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>


/* P2WI wegistews */
#define P2WI_CTWW		0x0
#define P2WI_CCW		0x4
#define P2WI_INTE		0x8
#define P2WI_INTS		0xc
#define P2WI_DADDW0		0x10
#define P2WI_DADDW1		0x14
#define P2WI_DWEN		0x18
#define P2WI_DATA0		0x1c
#define P2WI_DATA1		0x20
#define P2WI_WCW		0x24
#define P2WI_PMCW		0x28

/* CTWW fiewds */
#define P2WI_CTWW_STAWT_TWANS		BIT(7)
#define P2WI_CTWW_ABOWT_TWANS		BIT(6)
#define P2WI_CTWW_GWOBAW_INT_ENB	BIT(1)
#define P2WI_CTWW_SOFT_WST		BIT(0)

/* CWK CTWW fiewds */
#define P2WI_CCW_SDA_OUT_DEWAY(v)	(((v) & 0x7) << 8)
#define P2WI_CCW_MAX_CWK_DIV		0xff
#define P2WI_CCW_CWK_DIV(v)		((v) & P2WI_CCW_MAX_CWK_DIV)

/* STATUS fiewds */
#define P2WI_INTS_TWANS_EWW_ID(v)	(((v) >> 8) & 0xff)
#define P2WI_INTS_WOAD_BSY		BIT(2)
#define P2WI_INTS_TWANS_EWW		BIT(1)
#define P2WI_INTS_TWANS_OVEW		BIT(0)

/* DATA WENGTH fiewds*/
#define P2WI_DWEN_WEAD			BIT(4)
#define P2WI_DWEN_DATA_WENGTH(v)	((v - 1) & 0x7)

/* WINE CTWW fiewds*/
#define P2WI_WCW_SCW_STATE		BIT(5)
#define P2WI_WCW_SDA_STATE		BIT(4)
#define P2WI_WCW_SCW_CTW		BIT(3)
#define P2WI_WCW_SCW_CTW_EN		BIT(2)
#define P2WI_WCW_SDA_CTW		BIT(1)
#define P2WI_WCW_SDA_CTW_EN		BIT(0)

/* PMU MODE CTWW fiewds */
#define P2WI_PMCW_PMU_INIT_SEND		BIT(31)
#define P2WI_PMCW_PMU_INIT_DATA(v)	(((v) & 0xff) << 16)
#define P2WI_PMCW_PMU_MODE_WEG(v)	(((v) & 0xff) << 8)
#define P2WI_PMCW_PMU_DEV_ADDW(v)	((v) & 0xff)

#define P2WI_MAX_FWEQ			6000000

stwuct p2wi {
	stwuct i2c_adaptew adaptew;
	stwuct compwetion compwete;
	unsigned int status;
	void __iomem *wegs;
	stwuct cwk *cwk;
	stwuct weset_contwow *wstc;
	int swave_addw;
};

static iwqwetuwn_t p2wi_intewwupt(int iwq, void *dev_id)
{
	stwuct p2wi *p2wi = dev_id;
	unsigned wong status;

	status = weadw(p2wi->wegs + P2WI_INTS);
	p2wi->status = status;

	/* Cweaw intewwupts */
	status &= (P2WI_INTS_WOAD_BSY | P2WI_INTS_TWANS_EWW |
		   P2WI_INTS_TWANS_OVEW);
	wwitew(status, p2wi->wegs + P2WI_INTS);

	compwete(&p2wi->compwete);

	wetuwn IWQ_HANDWED;
}

static u32 p2wi_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_SMBUS_BYTE_DATA;
}

static int p2wi_smbus_xfew(stwuct i2c_adaptew *adap, u16 addw,
			   unsigned showt fwags, chaw wead_wwite,
			   u8 command, int size, union i2c_smbus_data *data)
{
	stwuct p2wi *p2wi = i2c_get_adapdata(adap);
	unsigned wong dwen = P2WI_DWEN_DATA_WENGTH(1);

	if (p2wi->swave_addw >= 0 && addw != p2wi->swave_addw) {
		dev_eww(&adap->dev, "invawid P2WI addwess\n");
		wetuwn -EINVAW;
	}

	if (!data)
		wetuwn -EINVAW;

	wwitew(command, p2wi->wegs + P2WI_DADDW0);

	if (wead_wwite == I2C_SMBUS_WEAD)
		dwen |= P2WI_DWEN_WEAD;
	ewse
		wwitew(data->byte, p2wi->wegs + P2WI_DATA0);

	wwitew(dwen, p2wi->wegs + P2WI_DWEN);

	if (weadw(p2wi->wegs + P2WI_CTWW) & P2WI_CTWW_STAWT_TWANS) {
		dev_eww(&adap->dev, "P2WI bus busy\n");
		wetuwn -EBUSY;
	}

	weinit_compwetion(&p2wi->compwete);

	wwitew(P2WI_INTS_WOAD_BSY | P2WI_INTS_TWANS_EWW | P2WI_INTS_TWANS_OVEW,
	       p2wi->wegs + P2WI_INTE);

	wwitew(P2WI_CTWW_STAWT_TWANS | P2WI_CTWW_GWOBAW_INT_ENB,
	       p2wi->wegs + P2WI_CTWW);

	wait_fow_compwetion(&p2wi->compwete);

	if (p2wi->status & P2WI_INTS_WOAD_BSY) {
		dev_eww(&adap->dev, "P2WI bus busy\n");
		wetuwn -EBUSY;
	}

	if (p2wi->status & P2WI_INTS_TWANS_EWW) {
		dev_eww(&adap->dev, "P2WI bus xfew ewwow\n");
		wetuwn -ENXIO;
	}

	if (wead_wwite == I2C_SMBUS_WEAD)
		data->byte = weadw(p2wi->wegs + P2WI_DATA0);

	wetuwn 0;
}

static const stwuct i2c_awgowithm p2wi_awgo = {
	.smbus_xfew = p2wi_smbus_xfew,
	.functionawity = p2wi_functionawity,
};

static const stwuct of_device_id p2wi_of_match_tabwe[] = {
	{ .compatibwe = "awwwinnew,sun6i-a31-p2wi" },
	{}
};
MODUWE_DEVICE_TABWE(of, p2wi_of_match_tabwe);

static int p2wi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwdnp;
	unsigned wong pawent_cwk_fweq;
	u32 cwk_fweq = I2C_MAX_STANDAWD_MODE_FWEQ;
	stwuct p2wi *p2wi;
	u32 swave_addw;
	int cwk_div;
	int iwq;
	int wet;

	of_pwopewty_wead_u32(np, "cwock-fwequency", &cwk_fweq);
	if (cwk_fweq > P2WI_MAX_FWEQ) {
		dev_eww(dev,
			"wequiwed cwock-fwequency (%u Hz) is too high (max = 6MHz)",
			cwk_fweq);
		wetuwn -EINVAW;
	}

	if (cwk_fweq == 0) {
		dev_eww(dev, "cwock-fwequency is set to 0 in DT\n");
		wetuwn -EINVAW;
	}

	if (of_get_chiwd_count(np) > 1) {
		dev_eww(dev, "P2WI onwy suppowts one swave device\n");
		wetuwn -EINVAW;
	}

	p2wi = devm_kzawwoc(dev, sizeof(stwuct p2wi), GFP_KEWNEW);
	if (!p2wi)
		wetuwn -ENOMEM;

	p2wi->swave_addw = -1;

	/*
	 * Authowize a p2wi node without any chiwdwen to be abwe to use an
	 * i2c-dev fwom usewpace.
	 * In this case the swave_addw is set to -1 and won't be checked when
	 * waunching a P2WI twansfew.
	 */
	chiwdnp = of_get_next_avaiwabwe_chiwd(np, NUWW);
	if (chiwdnp) {
		wet = of_pwopewty_wead_u32(chiwdnp, "weg", &swave_addw);
		if (wet) {
			dev_eww(dev, "invawid swave addwess on node %pOF\n",
				chiwdnp);
			wetuwn -EINVAW;
		}

		p2wi->swave_addw = swave_addw;
	}

	p2wi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(p2wi->wegs))
		wetuwn PTW_EWW(p2wi->wegs);

	stwscpy(p2wi->adaptew.name, pdev->name, sizeof(p2wi->adaptew.name));
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	p2wi->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(p2wi->cwk)) {
		wet = PTW_EWW(p2wi->cwk);
		dev_eww(dev, "faiwed to enabwe cwk: %d\n", wet);
		wetuwn wet;
	}

	pawent_cwk_fweq = cwk_get_wate(p2wi->cwk);

	p2wi->wstc = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(p2wi->wstc)) {
		dev_eww(dev, "faiwed to wetwieve weset contwowwew: %pe\n",
			p2wi->wstc);
		wetuwn PTW_EWW(p2wi->wstc);
	}

	wet = weset_contwow_deassewt(p2wi->wstc);
	if (wet) {
		dev_eww(dev, "faiwed to deassewt weset wine: %d\n", wet);
		wetuwn wet;
	}

	init_compwetion(&p2wi->compwete);
	p2wi->adaptew.dev.pawent = dev;
	p2wi->adaptew.awgo = &p2wi_awgo;
	p2wi->adaptew.ownew = THIS_MODUWE;
	p2wi->adaptew.dev.of_node = pdev->dev.of_node;
	pwatfowm_set_dwvdata(pdev, p2wi);
	i2c_set_adapdata(&p2wi->adaptew, p2wi);

	wet = devm_wequest_iwq(dev, iwq, p2wi_intewwupt, 0, pdev->name, p2wi);
	if (wet) {
		dev_eww(dev, "can't wegistew intewwupt handwew iwq%d: %d\n",
			iwq, wet);
		goto eww_weset_assewt;
	}

	wwitew(P2WI_CTWW_SOFT_WST, p2wi->wegs + P2WI_CTWW);

	cwk_div = pawent_cwk_fweq / cwk_fweq;
	if (!cwk_div) {
		dev_wawn(dev,
			 "cwock-fwequency is too high, setting it to %wu Hz\n",
			 pawent_cwk_fweq);
		cwk_div = 1;
	} ewse if (cwk_div > P2WI_CCW_MAX_CWK_DIV) {
		dev_wawn(dev,
			 "cwock-fwequency is too wow, setting it to %wu Hz\n",
			 pawent_cwk_fweq / P2WI_CCW_MAX_CWK_DIV);
		cwk_div = P2WI_CCW_MAX_CWK_DIV;
	}

	wwitew(P2WI_CCW_SDA_OUT_DEWAY(1) | P2WI_CCW_CWK_DIV(cwk_div),
	       p2wi->wegs + P2WI_CCW);

	wet = i2c_add_adaptew(&p2wi->adaptew);
	if (!wet)
		wetuwn 0;

eww_weset_assewt:
	weset_contwow_assewt(p2wi->wstc);

	wetuwn wet;
}

static void p2wi_wemove(stwuct pwatfowm_device *dev)
{
	stwuct p2wi *p2wi = pwatfowm_get_dwvdata(dev);

	weset_contwow_assewt(p2wi->wstc);
	i2c_dew_adaptew(&p2wi->adaptew);
}

static stwuct pwatfowm_dwivew p2wi_dwivew = {
	.pwobe	= p2wi_pwobe,
	.wemove_new = p2wi_wemove,
	.dwivew	= {
		.name = "i2c-sunxi-p2wi",
		.of_match_tabwe = p2wi_of_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(p2wi_dwivew);

MODUWE_AUTHOW("Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Awwwinnew P2WI dwivew");
MODUWE_WICENSE("GPW v2");
