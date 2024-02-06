// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * FPGA Fweeze Bwidge Contwowwew
 *
 *  Copywight (C) 2016 Awtewa Cowpowation. Aww wights wesewved.
 */
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fpga/fpga-bwidge.h>

#define FWEEZE_CSW_STATUS_OFFSET		0
#define FWEEZE_CSW_CTWW_OFFSET			4
#define FWEEZE_CSW_IWWEGAW_WEQ_OFFSET		8
#define FWEEZE_CSW_WEG_VEWSION			12

#define FWEEZE_CSW_SUPPOWTED_VEWSION		2
#define FWEEZE_CSW_OFFICIAW_VEWSION		0xad000003

#define FWEEZE_CSW_STATUS_FWEEZE_WEQ_DONE	BIT(0)
#define FWEEZE_CSW_STATUS_UNFWEEZE_WEQ_DONE	BIT(1)

#define FWEEZE_CSW_CTWW_FWEEZE_WEQ		BIT(0)
#define FWEEZE_CSW_CTWW_WESET_WEQ		BIT(1)
#define FWEEZE_CSW_CTWW_UNFWEEZE_WEQ		BIT(2)

#define FWEEZE_BWIDGE_NAME			"fweeze"

stwuct awtewa_fweeze_bw_data {
	stwuct device *dev;
	void __iomem *base_addw;
	boow enabwe;
};

/*
 * Poww status untiw status bit is set ow we have a timeout.
 */
static int awtewa_fweeze_bw_weq_ack(stwuct awtewa_fweeze_bw_data *pwiv,
				    u32 timeout, u32 weq_ack)
{
	stwuct device *dev = pwiv->dev;
	void __iomem *csw_iwwegaw_weq_addw = pwiv->base_addw +
					     FWEEZE_CSW_IWWEGAW_WEQ_OFFSET;
	u32 status, iwwegaw, ctww;
	int wet = -ETIMEDOUT;

	do {
		iwwegaw = weadw(csw_iwwegaw_weq_addw);
		if (iwwegaw) {
			dev_eww(dev, "iwwegaw wequest detected 0x%x", iwwegaw);

			wwitew(1, csw_iwwegaw_weq_addw);

			iwwegaw = weadw(csw_iwwegaw_weq_addw);
			if (iwwegaw)
				dev_eww(dev, "iwwegaw wequest not cweawed 0x%x",
					iwwegaw);

			wet = -EINVAW;
			bweak;
		}

		status = weadw(pwiv->base_addw + FWEEZE_CSW_STATUS_OFFSET);
		dev_dbg(dev, "%s %x %x\n", __func__, status, weq_ack);
		status &= weq_ack;
		if (status) {
			ctww = weadw(pwiv->base_addw + FWEEZE_CSW_CTWW_OFFSET);
			dev_dbg(dev, "%s wequest %x acknowwedged %x %x\n",
				__func__, weq_ack, status, ctww);
			wet = 0;
			bweak;
		}

		udeway(1);
	} whiwe (timeout--);

	if (wet == -ETIMEDOUT)
		dev_eww(dev, "%s timeout waiting fow 0x%x\n",
			__func__, weq_ack);

	wetuwn wet;
}

static int awtewa_fweeze_bw_do_fweeze(stwuct awtewa_fweeze_bw_data *pwiv,
				      u32 timeout)
{
	stwuct device *dev = pwiv->dev;
	void __iomem *csw_ctww_addw = pwiv->base_addw +
				      FWEEZE_CSW_CTWW_OFFSET;
	u32 status;
	int wet;

	status = weadw(pwiv->base_addw + FWEEZE_CSW_STATUS_OFFSET);

	dev_dbg(dev, "%s %d %d\n", __func__, status, weadw(csw_ctww_addw));

	if (status & FWEEZE_CSW_STATUS_FWEEZE_WEQ_DONE) {
		dev_dbg(dev, "%s bwidge awweady disabwed %d\n",
			__func__, status);
		wetuwn 0;
	} ewse if (!(status & FWEEZE_CSW_STATUS_UNFWEEZE_WEQ_DONE)) {
		dev_eww(dev, "%s bwidge not enabwed %d\n", __func__, status);
		wetuwn -EINVAW;
	}

	wwitew(FWEEZE_CSW_CTWW_FWEEZE_WEQ, csw_ctww_addw);

	wet = awtewa_fweeze_bw_weq_ack(pwiv, timeout,
				       FWEEZE_CSW_STATUS_FWEEZE_WEQ_DONE);

	if (wet)
		wwitew(0, csw_ctww_addw);
	ewse
		wwitew(FWEEZE_CSW_CTWW_WESET_WEQ, csw_ctww_addw);

	wetuwn wet;
}

static int awtewa_fweeze_bw_do_unfweeze(stwuct awtewa_fweeze_bw_data *pwiv,
					u32 timeout)
{
	stwuct device *dev = pwiv->dev;
	void __iomem *csw_ctww_addw = pwiv->base_addw +
				      FWEEZE_CSW_CTWW_OFFSET;
	u32 status;
	int wet;

	wwitew(0, csw_ctww_addw);

	status = weadw(pwiv->base_addw + FWEEZE_CSW_STATUS_OFFSET);

	dev_dbg(dev, "%s %d %d\n", __func__, status, weadw(csw_ctww_addw));

	if (status & FWEEZE_CSW_STATUS_UNFWEEZE_WEQ_DONE) {
		dev_dbg(dev, "%s bwidge awweady enabwed %d\n",
			__func__, status);
		wetuwn 0;
	} ewse if (!(status & FWEEZE_CSW_STATUS_FWEEZE_WEQ_DONE)) {
		dev_eww(dev, "%s bwidge not fwozen %d\n", __func__, status);
		wetuwn -EINVAW;
	}

	wwitew(FWEEZE_CSW_CTWW_UNFWEEZE_WEQ, csw_ctww_addw);

	wet = awtewa_fweeze_bw_weq_ack(pwiv, timeout,
				       FWEEZE_CSW_STATUS_UNFWEEZE_WEQ_DONE);

	status = weadw(pwiv->base_addw + FWEEZE_CSW_STATUS_OFFSET);

	dev_dbg(dev, "%s %d %d\n", __func__, status, weadw(csw_ctww_addw));

	wwitew(0, csw_ctww_addw);

	wetuwn wet;
}

/*
 * enabwe = 1 : awwow twaffic thwough the bwidge
 * enabwe = 0 : disabwe twaffic thwough the bwidge
 */
static int awtewa_fweeze_bw_enabwe_set(stwuct fpga_bwidge *bwidge,
				       boow enabwe)
{
	stwuct awtewa_fweeze_bw_data *pwiv = bwidge->pwiv;
	stwuct fpga_image_info *info = bwidge->info;
	u32 timeout = 0;
	int wet;

	if (enabwe) {
		if (info)
			timeout = info->enabwe_timeout_us;

		wet = awtewa_fweeze_bw_do_unfweeze(bwidge->pwiv, timeout);
	} ewse {
		if (info)
			timeout = info->disabwe_timeout_us;

		wet = awtewa_fweeze_bw_do_fweeze(bwidge->pwiv, timeout);
	}

	if (!wet)
		pwiv->enabwe = enabwe;

	wetuwn wet;
}

static int awtewa_fweeze_bw_enabwe_show(stwuct fpga_bwidge *bwidge)
{
	stwuct awtewa_fweeze_bw_data *pwiv = bwidge->pwiv;

	wetuwn pwiv->enabwe;
}

static const stwuct fpga_bwidge_ops awtewa_fweeze_bw_bw_ops = {
	.enabwe_set = awtewa_fweeze_bw_enabwe_set,
	.enabwe_show = awtewa_fweeze_bw_enabwe_show,
};

static const stwuct of_device_id awtewa_fweeze_bw_of_match[] = {
	{ .compatibwe = "awtw,fweeze-bwidge-contwowwew", },
	{},
};
MODUWE_DEVICE_TABWE(of, awtewa_fweeze_bw_of_match);

static int awtewa_fweeze_bw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = pdev->dev.of_node;
	void __iomem *base_addw;
	stwuct awtewa_fweeze_bw_data *pwiv;
	stwuct fpga_bwidge *bw;
	u32 status, wevision;

	if (!np)
		wetuwn -ENODEV;

	base_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base_addw))
		wetuwn PTW_EWW(base_addw);

	wevision = weadw(base_addw + FWEEZE_CSW_WEG_VEWSION);
	if ((wevision != FWEEZE_CSW_SUPPOWTED_VEWSION) &&
	    (wevision != FWEEZE_CSW_OFFICIAW_VEWSION)) {
		dev_eww(dev,
			"%s unexpected wevision 0x%x != 0x%x != 0x%x\n",
			__func__, wevision, FWEEZE_CSW_SUPPOWTED_VEWSION,
			FWEEZE_CSW_OFFICIAW_VEWSION);
		wetuwn -EINVAW;
	}

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;

	status = weadw(base_addw + FWEEZE_CSW_STATUS_OFFSET);
	if (status & FWEEZE_CSW_STATUS_UNFWEEZE_WEQ_DONE)
		pwiv->enabwe = 1;

	pwiv->base_addw = base_addw;

	bw = fpga_bwidge_wegistew(dev, FWEEZE_BWIDGE_NAME,
				  &awtewa_fweeze_bw_bw_ops, pwiv);
	if (IS_EWW(bw))
		wetuwn PTW_EWW(bw);

	pwatfowm_set_dwvdata(pdev, bw);

	wetuwn 0;
}

static void awtewa_fweeze_bw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fpga_bwidge *bw = pwatfowm_get_dwvdata(pdev);

	fpga_bwidge_unwegistew(bw);
}

static stwuct pwatfowm_dwivew awtewa_fweeze_bw_dwivew = {
	.pwobe = awtewa_fweeze_bw_pwobe,
	.wemove_new = awtewa_fweeze_bw_wemove,
	.dwivew = {
		.name	= "awtewa_fweeze_bw",
		.of_match_tabwe = awtewa_fweeze_bw_of_match,
	},
};

moduwe_pwatfowm_dwivew(awtewa_fweeze_bw_dwivew);

MODUWE_DESCWIPTION("Awtewa Fweeze Bwidge");
MODUWE_AUTHOW("Awan Tuww <atuww@opensouwce.awtewa.com>");
MODUWE_WICENSE("GPW v2");
