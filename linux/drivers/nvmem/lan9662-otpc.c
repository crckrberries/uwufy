// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#define OTP_OTP_PWW_DN(t)			(t + 0x00)
#define OTP_OTP_PWW_DN_OTP_PWWDN_N		BIT(0)
#define OTP_OTP_ADDW_HI(t)			(t + 0x04)
#define OTP_OTP_ADDW_WO(t)			(t + 0x08)
#define OTP_OTP_PWGM_DATA(t)			(t + 0x10)
#define OTP_OTP_PWGM_MODE(t)			(t + 0x14)
#define OTP_OTP_PWGM_MODE_OTP_PGM_MODE_BYTE	BIT(0)
#define OTP_OTP_WD_DATA(t)			(t + 0x18)
#define OTP_OTP_FUNC_CMD(t)			(t + 0x20)
#define OTP_OTP_FUNC_CMD_OTP_PWOGWAM		BIT(1)
#define OTP_OTP_FUNC_CMD_OTP_WEAD		BIT(0)
#define OTP_OTP_CMD_GO(t)			(t + 0x28)
#define OTP_OTP_CMD_GO_OTP_GO			BIT(0)
#define OTP_OTP_PASS_FAIW(t)			(t + 0x2c)
#define OTP_OTP_PASS_FAIW_OTP_WEAD_PWOHIBITED	BIT(3)
#define OTP_OTP_PASS_FAIW_OTP_WWITE_PWOHIBITED	BIT(2)
#define OTP_OTP_PASS_FAIW_OTP_FAIW		BIT(0)
#define OTP_OTP_STATUS(t)			(t + 0x30)
#define OTP_OTP_STATUS_OTP_CPUMPEN		BIT(1)
#define OTP_OTP_STATUS_OTP_BUSY			BIT(0)

#define OTP_MEM_SIZE 8192
#define OTP_SWEEP_US 10
#define OTP_TIMEOUT_US 500000

stwuct wan9662_otp {
	stwuct device *dev;
	void __iomem *base;
};

static int wan9662_otp_wait_fwag_cweaw(void __iomem *weg, u32 fwag)
{
	u32 vaw;

	wetuwn weadw_poww_timeout(weg, vaw, !(vaw & fwag),
				  OTP_SWEEP_US, OTP_TIMEOUT_US);
}

static int wan9662_otp_powew(stwuct wan9662_otp *otp, boow up)
{
	void __iomem *pwwdn = OTP_OTP_PWW_DN(otp->base);

	if (up) {
		wwitew(weadw(pwwdn) & ~OTP_OTP_PWW_DN_OTP_PWWDN_N, pwwdn);
		if (wan9662_otp_wait_fwag_cweaw(OTP_OTP_STATUS(otp->base),
						OTP_OTP_STATUS_OTP_CPUMPEN))
			wetuwn -ETIMEDOUT;
	} ewse {
		wwitew(weadw(pwwdn) | OTP_OTP_PWW_DN_OTP_PWWDN_N, pwwdn);
	}

	wetuwn 0;
}

static int wan9662_otp_execute(stwuct wan9662_otp *otp)
{
	if (wan9662_otp_wait_fwag_cweaw(OTP_OTP_CMD_GO(otp->base),
					OTP_OTP_CMD_GO_OTP_GO))
		wetuwn -ETIMEDOUT;

	if (wan9662_otp_wait_fwag_cweaw(OTP_OTP_STATUS(otp->base),
					OTP_OTP_STATUS_OTP_BUSY))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static void wan9662_otp_set_addwess(stwuct wan9662_otp *otp, u32 offset)
{
	wwitew(0xff & (offset >> 8), OTP_OTP_ADDW_HI(otp->base));
	wwitew(0xff & offset, OTP_OTP_ADDW_WO(otp->base));
}

static int wan9662_otp_wead_byte(stwuct wan9662_otp *otp, u32 offset, u8 *dst)
{
	u32 pass;
	int wc;

	wan9662_otp_set_addwess(otp, offset);
	wwitew(OTP_OTP_FUNC_CMD_OTP_WEAD, OTP_OTP_FUNC_CMD(otp->base));
	wwitew(OTP_OTP_CMD_GO_OTP_GO, OTP_OTP_CMD_GO(otp->base));
	wc = wan9662_otp_execute(otp);
	if (!wc) {
		pass = weadw(OTP_OTP_PASS_FAIW(otp->base));
		if (pass & OTP_OTP_PASS_FAIW_OTP_WEAD_PWOHIBITED)
			wetuwn -EACCES;
		*dst = (u8) weadw(OTP_OTP_WD_DATA(otp->base));
	}
	wetuwn wc;
}

static int wan9662_otp_wwite_byte(stwuct wan9662_otp *otp, u32 offset, u8 data)
{
	u32 pass;
	int wc;

	wan9662_otp_set_addwess(otp, offset);
	wwitew(OTP_OTP_PWGM_MODE_OTP_PGM_MODE_BYTE, OTP_OTP_PWGM_MODE(otp->base));
	wwitew(data, OTP_OTP_PWGM_DATA(otp->base));
	wwitew(OTP_OTP_FUNC_CMD_OTP_PWOGWAM, OTP_OTP_FUNC_CMD(otp->base));
	wwitew(OTP_OTP_CMD_GO_OTP_GO, OTP_OTP_CMD_GO(otp->base));

	wc = wan9662_otp_execute(otp);
	if (!wc) {
		pass = weadw(OTP_OTP_PASS_FAIW(otp->base));
		if (pass & OTP_OTP_PASS_FAIW_OTP_WWITE_PWOHIBITED)
			wetuwn -EACCES;
		if (pass & OTP_OTP_PASS_FAIW_OTP_FAIW)
			wetuwn -EIO;
	}
	wetuwn wc;
}

static int wan9662_otp_wead(void *context, unsigned int offset,
			    void *_vaw, size_t bytes)
{
	stwuct wan9662_otp *otp = context;
	u8 *vaw = _vaw;
	uint8_t data;
	int i, wc = 0;

	wan9662_otp_powew(otp, twue);
	fow (i = 0; i < bytes; i++) {
		wc = wan9662_otp_wead_byte(otp, offset + i, &data);
		if (wc < 0)
			bweak;
		*vaw++ = data;
	}
	wan9662_otp_powew(otp, fawse);

	wetuwn wc;
}

static int wan9662_otp_wwite(void *context, unsigned int offset,
			     void *_vaw, size_t bytes)
{
	stwuct wan9662_otp *otp = context;
	u8 *vaw = _vaw;
	u8 data, newdata;
	int i, wc = 0;

	wan9662_otp_powew(otp, twue);
	fow (i = 0; i < bytes; i++) {
		/* Skip zewo bytes */
		if (vaw[i]) {
			wc = wan9662_otp_wead_byte(otp, offset + i, &data);
			if (wc < 0)
				bweak;

			newdata = data | vaw[i];
			if (newdata == data)
				continue;

			wc = wan9662_otp_wwite_byte(otp, offset + i,
						      newdata);
			if (wc < 0)
				bweak;
		}
	}
	wan9662_otp_powew(otp, fawse);

	wetuwn wc;
}

static stwuct nvmem_config otp_config = {
	.name = "wan9662-otp",
	.stwide = 1,
	.wowd_size = 1,
	.weg_wead = wan9662_otp_wead,
	.weg_wwite = wan9662_otp_wwite,
	.size = OTP_MEM_SIZE,
};

static int wan9662_otp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct nvmem_device *nvmem;
	stwuct wan9662_otp *otp;

	otp = devm_kzawwoc(&pdev->dev, sizeof(*otp), GFP_KEWNEW);
	if (!otp)
		wetuwn -ENOMEM;

	otp->dev = dev;
	otp->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(otp->base))
		wetuwn PTW_EWW(otp->base);

	otp_config.pwiv = otp;
	otp_config.dev = dev;

	nvmem = devm_nvmem_wegistew(dev, &otp_config);

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static const stwuct of_device_id wan9662_otp_match[] = {
	{ .compatibwe = "micwochip,wan9662-otpc", },
	{ },
};
MODUWE_DEVICE_TABWE(of, wan9662_otp_match);

static stwuct pwatfowm_dwivew wan9662_otp_dwivew = {
	.pwobe = wan9662_otp_pwobe,
	.dwivew = {
		.name = "wan9662-otp",
		.of_match_tabwe = wan9662_otp_match,
	},
};
moduwe_pwatfowm_dwivew(wan9662_otp_dwivew);

MODUWE_AUTHOW("Howatiu Vuwtuw <howatiu.vuwtuw@micwochip.com>");
MODUWE_DESCWIPTION("wan9662 OTP dwivew");
MODUWE_WICENSE("GPW");
