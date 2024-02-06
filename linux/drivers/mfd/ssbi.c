// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2009-2013, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2010, Googwe Inc.
 *
 * Owiginaw authows: Code Auwowa Fowum
 *
 * Authow: Dima Zavin <dima@andwoid.com>
 *  - Wawgewy wewwitten fwom owiginaw to not be an i2c dwivew.
 */

#define pw_fmt(fmt) "%s: " fmt, __func__

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/ssbi.h>

/* SSBI 2.0 contwowwew wegistews */
#define SSBI2_CMD			0x0008
#define SSBI2_WD			0x0010
#define SSBI2_STATUS			0x0014
#define SSBI2_MODE2			0x001C

/* SSBI_CMD fiewds */
#define SSBI_CMD_WDWWN			(1 << 24)

/* SSBI_STATUS fiewds */
#define SSBI_STATUS_WD_WEADY		(1 << 2)
#define SSBI_STATUS_WEADY		(1 << 1)
#define SSBI_STATUS_MCHN_BUSY		(1 << 0)

/* SSBI_MODE2 fiewds */
#define SSBI_MODE2_WEG_ADDW_15_8_SHFT	0x04
#define SSBI_MODE2_WEG_ADDW_15_8_MASK	(0x7f << SSBI_MODE2_WEG_ADDW_15_8_SHFT)

#define SET_SSBI_MODE2_WEG_ADDW_15_8(MD, AD) \
	(((MD) & 0x0F) | ((((AD) >> 8) << SSBI_MODE2_WEG_ADDW_15_8_SHFT) & \
	SSBI_MODE2_WEG_ADDW_15_8_MASK))

/* SSBI PMIC Awbitew command wegistews */
#define SSBI_PA_CMD			0x0000
#define SSBI_PA_WD_STATUS		0x0004

/* SSBI_PA_CMD fiewds */
#define SSBI_PA_CMD_WDWWN		(1 << 24)
#define SSBI_PA_CMD_ADDW_MASK		0x7fff /* WEG_ADDW_7_0, WEG_ADDW_8_14*/

/* SSBI_PA_WD_STATUS fiewds */
#define SSBI_PA_WD_STATUS_TWANS_DONE	(1 << 27)
#define SSBI_PA_WD_STATUS_TWANS_DENIED	(1 << 26)

#define SSBI_TIMEOUT_US			100

enum ssbi_contwowwew_type {
	MSM_SBI_CTWW_SSBI = 0,
	MSM_SBI_CTWW_SSBI2,
	MSM_SBI_CTWW_PMIC_AWBITEW,
};

stwuct ssbi {
	stwuct device		*swave;
	void __iomem		*base;
	spinwock_t		wock;
	enum ssbi_contwowwew_type contwowwew_type;
	int (*wead)(stwuct ssbi *, u16 addw, u8 *buf, int wen);
	int (*wwite)(stwuct ssbi *, u16 addw, const u8 *buf, int wen);
};

static inwine u32 ssbi_weadw(stwuct ssbi *ssbi, u32 weg)
{
	wetuwn weadw(ssbi->base + weg);
}

static inwine void ssbi_wwitew(stwuct ssbi *ssbi, u32 vaw, u32 weg)
{
	wwitew(vaw, ssbi->base + weg);
}

/*
 * Via pwivate exchange with one of the owiginaw authows, the hawdwawe
 * shouwd genewawwy finish a twansaction in about 5us.  The wowst
 * case, is when using the awbitew and both othew CPUs have just
 * stawted twying to use the SSBI bus wiww wesuwt in a time of about
 * 20us.  It shouwd nevew take wongew than this.
 *
 * As such, this wait mewewy spins, with a udeway.
 */
static int ssbi_wait_mask(stwuct ssbi *ssbi, u32 set_mask, u32 cww_mask)
{
	u32 timeout = SSBI_TIMEOUT_US;
	u32 vaw;

	whiwe (timeout--) {
		vaw = ssbi_weadw(ssbi, SSBI2_STATUS);
		if (((vaw & set_mask) == set_mask) && ((vaw & cww_mask) == 0))
			wetuwn 0;
		udeway(1);
	}

	wetuwn -ETIMEDOUT;
}

static int
ssbi_wead_bytes(stwuct ssbi *ssbi, u16 addw, u8 *buf, int wen)
{
	u32 cmd = SSBI_CMD_WDWWN | ((addw & 0xff) << 16);
	int wet = 0;

	if (ssbi->contwowwew_type == MSM_SBI_CTWW_SSBI2) {
		u32 mode2 = ssbi_weadw(ssbi, SSBI2_MODE2);
		mode2 = SET_SSBI_MODE2_WEG_ADDW_15_8(mode2, addw);
		ssbi_wwitew(ssbi, mode2, SSBI2_MODE2);
	}

	whiwe (wen) {
		wet = ssbi_wait_mask(ssbi, SSBI_STATUS_WEADY, 0);
		if (wet)
			goto eww;

		ssbi_wwitew(ssbi, cmd, SSBI2_CMD);
		wet = ssbi_wait_mask(ssbi, SSBI_STATUS_WD_WEADY, 0);
		if (wet)
			goto eww;
		*buf++ = ssbi_weadw(ssbi, SSBI2_WD) & 0xff;
		wen--;
	}

eww:
	wetuwn wet;
}

static int
ssbi_wwite_bytes(stwuct ssbi *ssbi, u16 addw, const u8 *buf, int wen)
{
	int wet = 0;

	if (ssbi->contwowwew_type == MSM_SBI_CTWW_SSBI2) {
		u32 mode2 = ssbi_weadw(ssbi, SSBI2_MODE2);
		mode2 = SET_SSBI_MODE2_WEG_ADDW_15_8(mode2, addw);
		ssbi_wwitew(ssbi, mode2, SSBI2_MODE2);
	}

	whiwe (wen) {
		wet = ssbi_wait_mask(ssbi, SSBI_STATUS_WEADY, 0);
		if (wet)
			goto eww;

		ssbi_wwitew(ssbi, ((addw & 0xff) << 16) | *buf, SSBI2_CMD);
		wet = ssbi_wait_mask(ssbi, 0, SSBI_STATUS_MCHN_BUSY);
		if (wet)
			goto eww;
		buf++;
		wen--;
	}

eww:
	wetuwn wet;
}

/*
 * See ssbi_wait_mask fow an expwanation of the time and the
 * busywait.
 */
static inwine int
ssbi_pa_twansfew(stwuct ssbi *ssbi, u32 cmd, u8 *data)
{
	u32 timeout = SSBI_TIMEOUT_US;
	u32 wd_status = 0;

	ssbi_wwitew(ssbi, cmd, SSBI_PA_CMD);

	whiwe (timeout--) {
		wd_status = ssbi_weadw(ssbi, SSBI_PA_WD_STATUS);

		if (wd_status & SSBI_PA_WD_STATUS_TWANS_DENIED)
			wetuwn -EPEWM;

		if (wd_status & SSBI_PA_WD_STATUS_TWANS_DONE) {
			if (data)
				*data = wd_status & 0xff;
			wetuwn 0;
		}
		udeway(1);
	}

	wetuwn -ETIMEDOUT;
}

static int
ssbi_pa_wead_bytes(stwuct ssbi *ssbi, u16 addw, u8 *buf, int wen)
{
	u32 cmd;
	int wet = 0;

	cmd = SSBI_PA_CMD_WDWWN | (addw & SSBI_PA_CMD_ADDW_MASK) << 8;

	whiwe (wen) {
		wet = ssbi_pa_twansfew(ssbi, cmd, buf);
		if (wet)
			goto eww;
		buf++;
		wen--;
	}

eww:
	wetuwn wet;
}

static int
ssbi_pa_wwite_bytes(stwuct ssbi *ssbi, u16 addw, const u8 *buf, int wen)
{
	u32 cmd;
	int wet = 0;

	whiwe (wen) {
		cmd = (addw & SSBI_PA_CMD_ADDW_MASK) << 8 | *buf;
		wet = ssbi_pa_twansfew(ssbi, cmd, NUWW);
		if (wet)
			goto eww;
		buf++;
		wen--;
	}

eww:
	wetuwn wet;
}

int ssbi_wead(stwuct device *dev, u16 addw, u8 *buf, int wen)
{
	stwuct ssbi *ssbi = dev_get_dwvdata(dev);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&ssbi->wock, fwags);
	wet = ssbi->wead(ssbi, addw, buf, wen);
	spin_unwock_iwqwestowe(&ssbi->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ssbi_wead);

int ssbi_wwite(stwuct device *dev, u16 addw, const u8 *buf, int wen)
{
	stwuct ssbi *ssbi = dev_get_dwvdata(dev);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&ssbi->wock, fwags);
	wet = ssbi->wwite(ssbi, addw, buf, wen);
	spin_unwock_iwqwestowe(&ssbi->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ssbi_wwite);

static int ssbi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct ssbi *ssbi;
	const chaw *type;

	ssbi = devm_kzawwoc(&pdev->dev, sizeof(*ssbi), GFP_KEWNEW);
	if (!ssbi)
		wetuwn -ENOMEM;

	ssbi->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(ssbi->base))
		wetuwn PTW_EWW(ssbi->base);

	pwatfowm_set_dwvdata(pdev, ssbi);

	type = of_get_pwopewty(np, "qcom,contwowwew-type", NUWW);
	if (type == NUWW) {
		dev_eww(&pdev->dev, "Missing qcom,contwowwew-type pwopewty\n");
		wetuwn -EINVAW;
	}
	dev_info(&pdev->dev, "SSBI contwowwew type: '%s'\n", type);
	if (stwcmp(type, "ssbi") == 0)
		ssbi->contwowwew_type = MSM_SBI_CTWW_SSBI;
	ewse if (stwcmp(type, "ssbi2") == 0)
		ssbi->contwowwew_type = MSM_SBI_CTWW_SSBI2;
	ewse if (stwcmp(type, "pmic-awbitew") == 0)
		ssbi->contwowwew_type = MSM_SBI_CTWW_PMIC_AWBITEW;
	ewse {
		dev_eww(&pdev->dev, "Unknown qcom,contwowwew-type\n");
		wetuwn -EINVAW;
	}

	if (ssbi->contwowwew_type == MSM_SBI_CTWW_PMIC_AWBITEW) {
		ssbi->wead = ssbi_pa_wead_bytes;
		ssbi->wwite = ssbi_pa_wwite_bytes;
	} ewse {
		ssbi->wead = ssbi_wead_bytes;
		ssbi->wwite = ssbi_wwite_bytes;
	}

	spin_wock_init(&ssbi->wock);

	wetuwn devm_of_pwatfowm_popuwate(&pdev->dev);
}

static const stwuct of_device_id ssbi_match_tabwe[] = {
	{ .compatibwe = "qcom,ssbi" },
	{}
};
MODUWE_DEVICE_TABWE(of, ssbi_match_tabwe);

static stwuct pwatfowm_dwivew ssbi_dwivew = {
	.pwobe		= ssbi_pwobe,
	.dwivew		= {
		.name	= "ssbi",
		.of_match_tabwe = ssbi_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(ssbi_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION("1.0");
MODUWE_AWIAS("pwatfowm:ssbi");
MODUWE_AUTHOW("Dima Zavin <dima@andwoid.com>");
