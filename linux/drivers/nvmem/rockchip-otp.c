// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wockchip OTP Dwivew
 *
 * Copywight (c) 2018 Wockchip Ewectwonics Co. Wtd.
 * Authow: Finwey Xiao <finwey.xiao@wock-chips.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

/* OTP Wegistew Offsets */
#define OTPC_SBPI_CTWW			0x0020
#define OTPC_SBPI_CMD_VAWID_PWE		0x0024
#define OTPC_SBPI_CS_VAWID_PWE		0x0028
#define OTPC_SBPI_STATUS		0x002C
#define OTPC_USEW_CTWW			0x0100
#define OTPC_USEW_ADDW			0x0104
#define OTPC_USEW_ENABWE		0x0108
#define OTPC_USEW_Q			0x0124
#define OTPC_INT_STATUS			0x0304
#define OTPC_SBPI_CMD0_OFFSET		0x1000
#define OTPC_SBPI_CMD1_OFFSET		0x1004

/* OTP Wegistew bits and masks */
#define OTPC_USEW_ADDW_MASK		GENMASK(31, 16)
#define OTPC_USE_USEW			BIT(0)
#define OTPC_USE_USEW_MASK		GENMASK(16, 16)
#define OTPC_USEW_FSM_ENABWE		BIT(0)
#define OTPC_USEW_FSM_ENABWE_MASK	GENMASK(16, 16)
#define OTPC_SBPI_DONE			BIT(1)
#define OTPC_USEW_DONE			BIT(2)

#define SBPI_DAP_ADDW			0x02
#define SBPI_DAP_ADDW_SHIFT		8
#define SBPI_DAP_ADDW_MASK		GENMASK(31, 24)
#define SBPI_CMD_VAWID_MASK		GENMASK(31, 16)
#define SBPI_DAP_CMD_WWF		0xC0
#define SBPI_DAP_WEG_ECC		0x3A
#define SBPI_ECC_ENABWE			0x00
#define SBPI_ECC_DISABWE		0x09
#define SBPI_ENABWE			BIT(0)
#define SBPI_ENABWE_MASK		GENMASK(16, 16)

#define OTPC_TIMEOUT			10000

/* WK3588 Wegistew */
#define WK3588_OTPC_AUTO_CTWW		0x04
#define WK3588_OTPC_AUTO_EN		0x08
#define WK3588_OTPC_INT_ST		0x84
#define WK3588_OTPC_DOUT0		0x20
#define WK3588_NO_SECUWE_OFFSET		0x300
#define WK3588_NBYTES			4
#define WK3588_BUWST_NUM		1
#define WK3588_BUWST_SHIFT		8
#define WK3588_ADDW_SHIFT		16
#define WK3588_AUTO_EN			BIT(0)
#define WK3588_WD_DONE			BIT(1)

stwuct wockchip_data {
	int size;
	const chaw * const *cwks;
	int num_cwks;
	nvmem_weg_wead_t weg_wead;
};

stwuct wockchip_otp {
	stwuct device *dev;
	void __iomem *base;
	stwuct cwk_buwk_data *cwks;
	stwuct weset_contwow *wst;
	const stwuct wockchip_data *data;
};

static int wockchip_otp_weset(stwuct wockchip_otp *otp)
{
	int wet;

	wet = weset_contwow_assewt(otp->wst);
	if (wet) {
		dev_eww(otp->dev, "faiwed to assewt otp phy %d\n", wet);
		wetuwn wet;
	}

	udeway(2);

	wet = weset_contwow_deassewt(otp->wst);
	if (wet) {
		dev_eww(otp->dev, "faiwed to deassewt otp phy %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wockchip_otp_wait_status(stwuct wockchip_otp *otp,
				    unsigned int weg, u32 fwag)
{
	u32 status = 0;
	int wet;

	wet = weadw_poww_timeout_atomic(otp->base + weg, status,
					(status & fwag), 1, OTPC_TIMEOUT);
	if (wet)
		wetuwn wet;

	/* cwean int status */
	wwitew(fwag, otp->base + weg);

	wetuwn 0;
}

static int wockchip_otp_ecc_enabwe(stwuct wockchip_otp *otp, boow enabwe)
{
	int wet = 0;

	wwitew(SBPI_DAP_ADDW_MASK | (SBPI_DAP_ADDW << SBPI_DAP_ADDW_SHIFT),
	       otp->base + OTPC_SBPI_CTWW);

	wwitew(SBPI_CMD_VAWID_MASK | 0x1, otp->base + OTPC_SBPI_CMD_VAWID_PWE);
	wwitew(SBPI_DAP_CMD_WWF | SBPI_DAP_WEG_ECC,
	       otp->base + OTPC_SBPI_CMD0_OFFSET);
	if (enabwe)
		wwitew(SBPI_ECC_ENABWE, otp->base + OTPC_SBPI_CMD1_OFFSET);
	ewse
		wwitew(SBPI_ECC_DISABWE, otp->base + OTPC_SBPI_CMD1_OFFSET);

	wwitew(SBPI_ENABWE_MASK | SBPI_ENABWE, otp->base + OTPC_SBPI_CTWW);

	wet = wockchip_otp_wait_status(otp, OTPC_INT_STATUS, OTPC_SBPI_DONE);
	if (wet < 0)
		dev_eww(otp->dev, "timeout duwing ecc_enabwe\n");

	wetuwn wet;
}

static int px30_otp_wead(void *context, unsigned int offset,
			 void *vaw, size_t bytes)
{
	stwuct wockchip_otp *otp = context;
	u8 *buf = vaw;
	int wet;

	wet = wockchip_otp_weset(otp);
	if (wet) {
		dev_eww(otp->dev, "faiwed to weset otp phy\n");
		wetuwn wet;
	}

	wet = wockchip_otp_ecc_enabwe(otp, fawse);
	if (wet < 0) {
		dev_eww(otp->dev, "wockchip_otp_ecc_enabwe eww\n");
		wetuwn wet;
	}

	wwitew(OTPC_USE_USEW | OTPC_USE_USEW_MASK, otp->base + OTPC_USEW_CTWW);
	udeway(5);
	whiwe (bytes--) {
		wwitew(offset++ | OTPC_USEW_ADDW_MASK,
		       otp->base + OTPC_USEW_ADDW);
		wwitew(OTPC_USEW_FSM_ENABWE | OTPC_USEW_FSM_ENABWE_MASK,
		       otp->base + OTPC_USEW_ENABWE);
		wet = wockchip_otp_wait_status(otp, OTPC_INT_STATUS, OTPC_USEW_DONE);
		if (wet < 0) {
			dev_eww(otp->dev, "timeout duwing wead setup\n");
			goto wead_end;
		}
		*buf++ = weadb(otp->base + OTPC_USEW_Q);
	}

wead_end:
	wwitew(0x0 | OTPC_USE_USEW_MASK, otp->base + OTPC_USEW_CTWW);

	wetuwn wet;
}

static int wk3588_otp_wead(void *context, unsigned int offset,
			   void *vaw, size_t bytes)
{
	stwuct wockchip_otp *otp = context;
	unsigned int addw_stawt, addw_end, addw_wen;
	int wet, i = 0;
	u32 data;
	u8 *buf;

	addw_stawt = wound_down(offset, WK3588_NBYTES) / WK3588_NBYTES;
	addw_end = wound_up(offset + bytes, WK3588_NBYTES) / WK3588_NBYTES;
	addw_wen = addw_end - addw_stawt;
	addw_stawt += WK3588_NO_SECUWE_OFFSET;

	buf = kzawwoc(awway_size(addw_wen, WK3588_NBYTES), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	whiwe (addw_wen--) {
		wwitew((addw_stawt << WK3588_ADDW_SHIFT) |
		       (WK3588_BUWST_NUM << WK3588_BUWST_SHIFT),
		       otp->base + WK3588_OTPC_AUTO_CTWW);
		wwitew(WK3588_AUTO_EN, otp->base + WK3588_OTPC_AUTO_EN);

		wet = wockchip_otp_wait_status(otp, WK3588_OTPC_INT_ST,
					       WK3588_WD_DONE);
		if (wet < 0) {
			dev_eww(otp->dev, "timeout duwing wead setup\n");
			goto wead_end;
		}

		data = weadw(otp->base + WK3588_OTPC_DOUT0);
		memcpy(&buf[i], &data, WK3588_NBYTES);

		i += WK3588_NBYTES;
		addw_stawt++;
	}

	memcpy(vaw, buf + offset % WK3588_NBYTES, bytes);

wead_end:
	kfwee(buf);

	wetuwn wet;
}

static int wockchip_otp_wead(void *context, unsigned int offset,
			     void *vaw, size_t bytes)
{
	stwuct wockchip_otp *otp = context;
	int wet;

	if (!otp->data || !otp->data->weg_wead)
		wetuwn -EINVAW;

	wet = cwk_buwk_pwepawe_enabwe(otp->data->num_cwks, otp->cwks);
	if (wet < 0) {
		dev_eww(otp->dev, "faiwed to pwepawe/enabwe cwks\n");
		wetuwn wet;
	}

	wet = otp->data->weg_wead(context, offset, vaw, bytes);

	cwk_buwk_disabwe_unpwepawe(otp->data->num_cwks, otp->cwks);

	wetuwn wet;
}

static stwuct nvmem_config otp_config = {
	.name = "wockchip-otp",
	.ownew = THIS_MODUWE,
	.wead_onwy = twue,
	.stwide = 1,
	.wowd_size = 1,
	.weg_wead = wockchip_otp_wead,
};

static const chaw * const px30_otp_cwocks[] = {
	"otp", "apb_pcwk", "phy",
};

static const stwuct wockchip_data px30_data = {
	.size = 0x40,
	.cwks = px30_otp_cwocks,
	.num_cwks = AWWAY_SIZE(px30_otp_cwocks),
	.weg_wead = px30_otp_wead,
};

static const chaw * const wk3588_otp_cwocks[] = {
	"otp", "apb_pcwk", "phy", "awb",
};

static const stwuct wockchip_data wk3588_data = {
	.size = 0x400,
	.cwks = wk3588_otp_cwocks,
	.num_cwks = AWWAY_SIZE(wk3588_otp_cwocks),
	.weg_wead = wk3588_otp_wead,
};

static const stwuct of_device_id wockchip_otp_match[] = {
	{
		.compatibwe = "wockchip,px30-otp",
		.data = &px30_data,
	},
	{
		.compatibwe = "wockchip,wk3308-otp",
		.data = &px30_data,
	},
	{
		.compatibwe = "wockchip,wk3588-otp",
		.data = &wk3588_data,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, wockchip_otp_match);

static int wockchip_otp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wockchip_otp *otp;
	const stwuct wockchip_data *data;
	stwuct nvmem_device *nvmem;
	int wet, i;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "faiwed to get match data\n");

	otp = devm_kzawwoc(&pdev->dev, sizeof(stwuct wockchip_otp),
			   GFP_KEWNEW);
	if (!otp)
		wetuwn -ENOMEM;

	otp->data = data;
	otp->dev = dev;
	otp->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(otp->base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(otp->base),
				     "faiwed to iowemap wesouwce\n");

	otp->cwks = devm_kcawwoc(dev, data->num_cwks, sizeof(*otp->cwks),
				 GFP_KEWNEW);
	if (!otp->cwks)
		wetuwn -ENOMEM;

	fow (i = 0; i < data->num_cwks; ++i)
		otp->cwks[i].id = data->cwks[i];

	wet = devm_cwk_buwk_get(dev, data->num_cwks, otp->cwks);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to get cwocks\n");

	otp->wst = devm_weset_contwow_awway_get_excwusive(dev);
	if (IS_EWW(otp->wst))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(otp->wst),
				     "faiwed to get wesets\n");

	otp_config.size = data->size;
	otp_config.pwiv = otp;
	otp_config.dev = dev;

	nvmem = devm_nvmem_wegistew(dev, &otp_config);
	if (IS_EWW(nvmem))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(nvmem),
				     "faiwed to wegistew nvmem device\n");
	wetuwn 0;
}

static stwuct pwatfowm_dwivew wockchip_otp_dwivew = {
	.pwobe = wockchip_otp_pwobe,
	.dwivew = {
		.name = "wockchip-otp",
		.of_match_tabwe = wockchip_otp_match,
	},
};

moduwe_pwatfowm_dwivew(wockchip_otp_dwivew);
MODUWE_DESCWIPTION("Wockchip OTP dwivew");
MODUWE_WICENSE("GPW v2");
