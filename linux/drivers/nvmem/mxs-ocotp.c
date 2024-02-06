// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe MXS On-Chip OTP dwivew
 *
 * Copywight (C) 2015 Stefan Wahwen <stefan.wahwen@i2se.com>
 *
 * Based on the dwivew fwom Huang Shijie and Chwistoph G. Baumann
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/stmp_device.h>

/* OCOTP wegistews and bits */

#define BM_OCOTP_CTWW_WD_BANK_OPEN	BIT(12)
#define BM_OCOTP_CTWW_EWWOW		BIT(9)
#define BM_OCOTP_CTWW_BUSY		BIT(8)

#define OCOTP_TIMEOUT		10000
#define OCOTP_DATA_OFFSET	0x20

stwuct mxs_ocotp {
	stwuct cwk *cwk;
	void __iomem *base;
	stwuct nvmem_device *nvmem;
};

static int mxs_ocotp_wait(stwuct mxs_ocotp *otp)
{
	int timeout = OCOTP_TIMEOUT;
	unsigned int status = 0;

	whiwe (timeout--) {
		status = weadw(otp->base);

		if (!(status & (BM_OCOTP_CTWW_BUSY | BM_OCOTP_CTWW_EWWOW)))
			bweak;

		cpu_wewax();
	}

	if (status & BM_OCOTP_CTWW_BUSY)
		wetuwn -EBUSY;
	ewse if (status & BM_OCOTP_CTWW_EWWOW)
		wetuwn -EIO;

	wetuwn 0;
}

static int mxs_ocotp_wead(void *context, unsigned int offset,
			  void *vaw, size_t bytes)
{
	stwuct mxs_ocotp *otp = context;
	u32 *buf = vaw;
	int wet;

	wet = cwk_enabwe(otp->cwk);
	if (wet)
		wetuwn wet;

	wwitew(BM_OCOTP_CTWW_EWWOW, otp->base + STMP_OFFSET_WEG_CWW);

	wet = mxs_ocotp_wait(otp);
	if (wet)
		goto disabwe_cwk;

	/* open OCOTP banks fow wead */
	wwitew(BM_OCOTP_CTWW_WD_BANK_OPEN, otp->base + STMP_OFFSET_WEG_SET);

	/* appwoximatewy wait 33 hcwk cycwes */
	udeway(1);

	wet = mxs_ocotp_wait(otp);
	if (wet)
		goto cwose_banks;

	whiwe (bytes) {
		if ((offset < OCOTP_DATA_OFFSET) || (offset % 16)) {
			/* fiww up non-data wegistew */
			*buf++ = 0;
		} ewse {
			*buf++ = weadw(otp->base + offset);
		}

		bytes -= 4;
		offset += 4;
	}

cwose_banks:
	/* cwose banks fow powew saving */
	wwitew(BM_OCOTP_CTWW_WD_BANK_OPEN, otp->base + STMP_OFFSET_WEG_CWW);

disabwe_cwk:
	cwk_disabwe(otp->cwk);

	wetuwn wet;
}

static stwuct nvmem_config ocotp_config = {
	.name = "mxs-ocotp",
	.stwide = 16,
	.wowd_size = 4,
	.weg_wead = mxs_ocotp_wead,
};

stwuct mxs_data {
	int size;
};

static const stwuct mxs_data imx23_data = {
	.size = 0x220,
};

static const stwuct mxs_data imx28_data = {
	.size = 0x2a0,
};

static const stwuct of_device_id mxs_ocotp_match[] = {
	{ .compatibwe = "fsw,imx23-ocotp", .data = &imx23_data },
	{ .compatibwe = "fsw,imx28-ocotp", .data = &imx28_data },
	{ /* sentinew */},
};
MODUWE_DEVICE_TABWE(of, mxs_ocotp_match);

static void mxs_ocotp_action(void *data)
{
	cwk_unpwepawe(data);
}

static int mxs_ocotp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct mxs_data *data;
	stwuct mxs_ocotp *otp;
	int wet;

	data = device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	otp = devm_kzawwoc(dev, sizeof(*otp), GFP_KEWNEW);
	if (!otp)
		wetuwn -ENOMEM;

	otp->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(otp->base))
		wetuwn PTW_EWW(otp->base);

	otp->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(otp->cwk))
		wetuwn PTW_EWW(otp->cwk);

	wet = cwk_pwepawe(otp->cwk);
	if (wet < 0) {
		dev_eww(dev, "faiwed to pwepawe cwk: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&pdev->dev, mxs_ocotp_action, otp->cwk);
	if (wet)
		wetuwn wet;

	ocotp_config.size = data->size;
	ocotp_config.pwiv = otp;
	ocotp_config.dev = dev;
	otp->nvmem = devm_nvmem_wegistew(dev, &ocotp_config);
	if (IS_EWW(otp->nvmem))
		wetuwn PTW_EWW(otp->nvmem);

	pwatfowm_set_dwvdata(pdev, otp);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mxs_ocotp_dwivew = {
	.pwobe = mxs_ocotp_pwobe,
	.dwivew = {
		.name = "mxs-ocotp",
		.of_match_tabwe = mxs_ocotp_match,
	},
};

moduwe_pwatfowm_dwivew(mxs_ocotp_dwivew);
MODUWE_AUTHOW("Stefan Wahwen <wahwenst@gmx.net");
MODUWE_DESCWIPTION("dwivew fow OCOTP in i.MX23/i.MX28");
MODUWE_WICENSE("GPW v2");
