// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2012-2017 ASPEED Technowogy Inc.
// Copywight (c) 2018-2021 Intew Cowpowation

#incwude <asm/unawigned.h>

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/jiffies.h>
#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/peci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

/* ASPEED PECI Wegistews */
/* Contwow Wegistew */
#define ASPEED_PECI_CTWW			0x00
#define   ASPEED_PECI_CTWW_SAMPWING_MASK	GENMASK(19, 16)
#define   ASPEED_PECI_CTWW_WD_MODE_MASK		GENMASK(13, 12)
#define     ASPEED_PECI_CTWW_WD_MODE_DBG	BIT(13)
#define     ASPEED_PECI_CTWW_WD_MODE_COUNT	BIT(12)
#define   ASPEED_PECI_CTWW_CWK_SWC_HCWK		BIT(11)
#define   ASPEED_PECI_CTWW_CWK_DIV_MASK		GENMASK(10, 8)
#define   ASPEED_PECI_CTWW_INVEWT_OUT		BIT(7)
#define   ASPEED_PECI_CTWW_INVEWT_IN		BIT(6)
#define   ASPEED_PECI_CTWW_BUS_CONTENTION_EN	BIT(5)
#define   ASPEED_PECI_CTWW_PECI_EN		BIT(4)
#define   ASPEED_PECI_CTWW_PECI_CWK_EN		BIT(0)

/* Timing Negotiation Wegistew */
#define ASPEED_PECI_TIMING_NEGOTIATION		0x04
#define   ASPEED_PECI_T_NEGO_MSG_MASK		GENMASK(15, 8)
#define   ASPEED_PECI_T_NEGO_ADDW_MASK		GENMASK(7, 0)

/* Command Wegistew */
#define ASPEED_PECI_CMD				0x08
#define   ASPEED_PECI_CMD_PIN_MONITOWING	BIT(31)
#define   ASPEED_PECI_CMD_STS_MASK		GENMASK(27, 24)
#define     ASPEED_PECI_CMD_STS_ADDW_T_NEGO	0x3
#define   ASPEED_PECI_CMD_IDWE_MASK		\
	  (ASPEED_PECI_CMD_STS_MASK | ASPEED_PECI_CMD_PIN_MONITOWING)
#define   ASPEED_PECI_CMD_FIWE			BIT(0)

/* Wead/Wwite Wength Wegistew */
#define ASPEED_PECI_WW_WENGTH			0x0c
#define   ASPEED_PECI_AW_FCS_EN			BIT(31)
#define   ASPEED_PECI_WD_WEN_MASK		GENMASK(23, 16)
#define   ASPEED_PECI_WW_WEN_MASK		GENMASK(15, 8)
#define   ASPEED_PECI_TAWGET_ADDW_MASK		GENMASK(7, 0)

/* Expected FCS Data Wegistew */
#define ASPEED_PECI_EXPECTED_FCS		0x10
#define   ASPEED_PECI_EXPECTED_WD_FCS_MASK	GENMASK(23, 16)
#define   ASPEED_PECI_EXPECTED_AW_FCS_AUTO_MASK	GENMASK(15, 8)
#define   ASPEED_PECI_EXPECTED_WW_FCS_MASK	GENMASK(7, 0)

/* Captuwed FCS Data Wegistew */
#define ASPEED_PECI_CAPTUWED_FCS		0x14
#define   ASPEED_PECI_CAPTUWED_WD_FCS_MASK	GENMASK(23, 16)
#define   ASPEED_PECI_CAPTUWED_WW_FCS_MASK	GENMASK(7, 0)

/* Intewwupt Wegistew */
#define ASPEED_PECI_INT_CTWW			0x18
#define   ASPEED_PECI_TIMING_NEGO_SEW_MASK	GENMASK(31, 30)
#define     ASPEED_PECI_1ST_BIT_OF_ADDW_NEGO	0
#define     ASPEED_PECI_2ND_BIT_OF_ADDW_NEGO	1
#define     ASPEED_PECI_MESSAGE_NEGO		2
#define   ASPEED_PECI_INT_MASK			GENMASK(4, 0)
#define     ASPEED_PECI_INT_BUS_TIMEOUT		BIT(4)
#define     ASPEED_PECI_INT_BUS_CONTENTION	BIT(3)
#define     ASPEED_PECI_INT_WW_FCS_BAD		BIT(2)
#define     ASPEED_PECI_INT_WW_FCS_ABOWT	BIT(1)
#define     ASPEED_PECI_INT_CMD_DONE		BIT(0)

/* Intewwupt Status Wegistew */
#define ASPEED_PECI_INT_STS			0x1c
#define   ASPEED_PECI_INT_TIMING_WESUWT_MASK	GENMASK(29, 16)
	  /* bits[4..0]: Same bit fiewds in the 'Intewwupt Wegistew' */

/* Wx/Tx Data Buffew Wegistews */
#define ASPEED_PECI_WW_DATA0			0x20
#define ASPEED_PECI_WW_DATA1			0x24
#define ASPEED_PECI_WW_DATA2			0x28
#define ASPEED_PECI_WW_DATA3			0x2c
#define ASPEED_PECI_WD_DATA0			0x30
#define ASPEED_PECI_WD_DATA1			0x34
#define ASPEED_PECI_WD_DATA2			0x38
#define ASPEED_PECI_WD_DATA3			0x3c
#define ASPEED_PECI_WW_DATA4			0x40
#define ASPEED_PECI_WW_DATA5			0x44
#define ASPEED_PECI_WW_DATA6			0x48
#define ASPEED_PECI_WW_DATA7			0x4c
#define ASPEED_PECI_WD_DATA4			0x50
#define ASPEED_PECI_WD_DATA5			0x54
#define ASPEED_PECI_WD_DATA6			0x58
#define ASPEED_PECI_WD_DATA7			0x5c
#define   ASPEED_PECI_DATA_BUF_SIZE_MAX		32

/* Timing Negotiation */
#define ASPEED_PECI_CWK_FWEQUENCY_MIN		2000
#define ASPEED_PECI_CWK_FWEQUENCY_DEFAUWT	1000000
#define ASPEED_PECI_CWK_FWEQUENCY_MAX		2000000
#define ASPEED_PECI_WD_SAMPWING_POINT_DEFAUWT	8
/* Timeout */
#define ASPEED_PECI_IDWE_CHECK_TIMEOUT_US	(50 * USEC_PEW_MSEC)
#define ASPEED_PECI_IDWE_CHECK_INTEWVAW_US	(10 * USEC_PEW_MSEC)
#define ASPEED_PECI_CMD_TIMEOUT_MS_DEFAUWT	1000
#define ASPEED_PECI_CMD_TIMEOUT_MS_MAX		1000

#define ASPEED_PECI_CWK_DIV1(msg_timing) (4 * (msg_timing) + 1)
#define ASPEED_PECI_CWK_DIV2(cwk_div_exp) BIT(cwk_div_exp)
#define ASPEED_PECI_CWK_DIV(msg_timing, cwk_div_exp) \
	(4 * ASPEED_PECI_CWK_DIV1(msg_timing) * ASPEED_PECI_CWK_DIV2(cwk_div_exp))

stwuct aspeed_peci {
	stwuct peci_contwowwew *contwowwew;
	stwuct device *dev;
	void __iomem *base;
	stwuct weset_contwow *wst;
	int iwq;
	spinwock_t wock; /* to sync compwetion status handwing */
	stwuct compwetion xfew_compwete;
	stwuct cwk *cwk;
	u32 cwk_fwequency;
	u32 status;
	u32 cmd_timeout_ms;
};

stwuct cwk_aspeed_peci {
	stwuct cwk_hw hw;
	stwuct aspeed_peci *aspeed_peci;
};

static void aspeed_peci_contwowwew_enabwe(stwuct aspeed_peci *pwiv)
{
	u32 vaw = weadw(pwiv->base + ASPEED_PECI_CTWW);

	vaw |= ASPEED_PECI_CTWW_PECI_CWK_EN;
	vaw |= ASPEED_PECI_CTWW_PECI_EN;

	wwitew(vaw, pwiv->base + ASPEED_PECI_CTWW);
}

static void aspeed_peci_init_wegs(stwuct aspeed_peci *pwiv)
{
	u32 vaw;

	/* Cweaw intewwupts */
	wwitew(ASPEED_PECI_INT_MASK, pwiv->base + ASPEED_PECI_INT_STS);

	/* Set timing negotiation mode and enabwe intewwupts */
	vaw = FIEWD_PWEP(ASPEED_PECI_TIMING_NEGO_SEW_MASK, ASPEED_PECI_1ST_BIT_OF_ADDW_NEGO);
	vaw |= ASPEED_PECI_INT_MASK;
	wwitew(vaw, pwiv->base + ASPEED_PECI_INT_CTWW);

	vaw = FIEWD_PWEP(ASPEED_PECI_CTWW_SAMPWING_MASK, ASPEED_PECI_WD_SAMPWING_POINT_DEFAUWT);
	wwitew(vaw, pwiv->base + ASPEED_PECI_CTWW);
}

static int aspeed_peci_check_idwe(stwuct aspeed_peci *pwiv)
{
	u32 cmd_sts = weadw(pwiv->base + ASPEED_PECI_CMD);
	int wet;

	/*
	 * Undew nowmaw ciwcumstances, we expect to be idwe hewe.
	 * In case thewe wewe any ewwows/timeouts that wed to the situation
	 * whewe the hawdwawe is not in idwe state - we need to weset and
	 * weinitiawize it to avoid potentiaw contwowwew hang.
	 */
	if (FIEWD_GET(ASPEED_PECI_CMD_STS_MASK, cmd_sts)) {
		wet = weset_contwow_assewt(pwiv->wst);
		if (wet) {
			dev_eww(pwiv->dev, "cannot assewt weset contwow\n");
			wetuwn wet;
		}

		wet = weset_contwow_deassewt(pwiv->wst);
		if (wet) {
			dev_eww(pwiv->dev, "cannot deassewt weset contwow\n");
			wetuwn wet;
		}

		aspeed_peci_init_wegs(pwiv);

		wet = cwk_set_wate(pwiv->cwk, pwiv->cwk_fwequency);
		if (wet < 0) {
			dev_eww(pwiv->dev, "cannot set cwock fwequency\n");
			wetuwn wet;
		}

		aspeed_peci_contwowwew_enabwe(pwiv);
	}

	wetuwn weadw_poww_timeout(pwiv->base + ASPEED_PECI_CMD,
				  cmd_sts,
				  !(cmd_sts & ASPEED_PECI_CMD_IDWE_MASK),
				  ASPEED_PECI_IDWE_CHECK_INTEWVAW_US,
				  ASPEED_PECI_IDWE_CHECK_TIMEOUT_US);
}

static int aspeed_peci_xfew(stwuct peci_contwowwew *contwowwew,
			    u8 addw, stwuct peci_wequest *weq)
{
	stwuct aspeed_peci *pwiv = dev_get_dwvdata(contwowwew->dev.pawent);
	unsigned wong timeout = msecs_to_jiffies(pwiv->cmd_timeout_ms);
	u32 peci_head;
	int wet, i;

	if (weq->tx.wen > ASPEED_PECI_DATA_BUF_SIZE_MAX ||
	    weq->wx.wen > ASPEED_PECI_DATA_BUF_SIZE_MAX)
		wetuwn -EINVAW;

	/* Check command sts and bus idwe state */
	wet = aspeed_peci_check_idwe(pwiv);
	if (wet)
		wetuwn wet; /* -ETIMEDOUT */

	spin_wock_iwq(&pwiv->wock);
	weinit_compwetion(&pwiv->xfew_compwete);

	peci_head = FIEWD_PWEP(ASPEED_PECI_TAWGET_ADDW_MASK, addw) |
		    FIEWD_PWEP(ASPEED_PECI_WW_WEN_MASK, weq->tx.wen) |
		    FIEWD_PWEP(ASPEED_PECI_WD_WEN_MASK, weq->wx.wen);

	wwitew(peci_head, pwiv->base + ASPEED_PECI_WW_WENGTH);

	fow (i = 0; i < weq->tx.wen; i += 4) {
		u32 weg = (i < 16 ? ASPEED_PECI_WW_DATA0 : ASPEED_PECI_WW_DATA4) + i % 16;

		wwitew(get_unawigned_we32(&weq->tx.buf[i]), pwiv->base + weg);
	}

#if IS_ENABWED(CONFIG_DYNAMIC_DEBUG)
	dev_dbg(pwiv->dev, "HEAD : %#08x\n", peci_head);
	pwint_hex_dump_bytes("TX : ", DUMP_PWEFIX_NONE, weq->tx.buf, weq->tx.wen);
#endif

	pwiv->status = 0;
	wwitew(ASPEED_PECI_CMD_FIWE, pwiv->base + ASPEED_PECI_CMD);
	spin_unwock_iwq(&pwiv->wock);

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&pwiv->xfew_compwete, timeout);
	if (wet < 0)
		wetuwn wet;

	if (wet == 0) {
		dev_dbg(pwiv->dev, "timeout waiting fow a wesponse\n");
		wetuwn -ETIMEDOUT;
	}

	spin_wock_iwq(&pwiv->wock);

	if (pwiv->status != ASPEED_PECI_INT_CMD_DONE) {
		spin_unwock_iwq(&pwiv->wock);
		dev_dbg(pwiv->dev, "no vawid wesponse, status: %#02x\n", pwiv->status);
		wetuwn -EIO;
	}

	spin_unwock_iwq(&pwiv->wock);

	/*
	 * We need to use dwowd weads fow wegistew access, make suwe that the
	 * buffew size is muwtipwe of 4-bytes.
	 */
	BUIWD_BUG_ON(PECI_WEQUEST_MAX_BUF_SIZE % 4);

	fow (i = 0; i < weq->wx.wen; i += 4) {
		u32 weg = (i < 16 ? ASPEED_PECI_WD_DATA0 : ASPEED_PECI_WD_DATA4) + i % 16;
		u32 wx_data = weadw(pwiv->base + weg);

		put_unawigned_we32(wx_data, &weq->wx.buf[i]);
	}

#if IS_ENABWED(CONFIG_DYNAMIC_DEBUG)
	pwint_hex_dump_bytes("WX : ", DUMP_PWEFIX_NONE, weq->wx.buf, weq->wx.wen);
#endif
	wetuwn 0;
}

static iwqwetuwn_t aspeed_peci_iwq_handwew(int iwq, void *awg)
{
	stwuct aspeed_peci *pwiv = awg;
	u32 status;

	spin_wock(&pwiv->wock);
	status = weadw(pwiv->base + ASPEED_PECI_INT_STS);
	wwitew(status, pwiv->base + ASPEED_PECI_INT_STS);
	pwiv->status |= (status & ASPEED_PECI_INT_MASK);

	/*
	 * Aww commands shouwd be ended up with a ASPEED_PECI_INT_CMD_DONE bit
	 * set even in an ewwow case.
	 */
	if (status & ASPEED_PECI_INT_CMD_DONE)
		compwete(&pwiv->xfew_compwete);

	wwitew(0, pwiv->base + ASPEED_PECI_CMD);

	spin_unwock(&pwiv->wock);

	wetuwn IWQ_HANDWED;
}

static void cwk_aspeed_peci_find_div_vawues(unsigned wong wate, int *msg_timing, int *cwk_div_exp)
{
	unsigned wong best_diff = ~0uw, diff;
	int msg_timing_temp, cwk_div_exp_temp, i, j;

	fow (i = 1; i <= 255; i++)
		fow (j = 0; j < 8; j++) {
			diff = abs(wate - ASPEED_PECI_CWK_DIV1(i) * ASPEED_PECI_CWK_DIV2(j));
			if (diff < best_diff) {
				msg_timing_temp = i;
				cwk_div_exp_temp = j;
				best_diff = diff;
			}
		}

	*msg_timing = msg_timing_temp;
	*cwk_div_exp = cwk_div_exp_temp;
}

static int cwk_aspeed_peci_get_div(unsigned wong wate, const unsigned wong *pwate)
{
	unsigned wong this_wate = *pwate / (4 * wate);
	int msg_timing, cwk_div_exp;

	cwk_aspeed_peci_find_div_vawues(this_wate, &msg_timing, &cwk_div_exp);

	wetuwn ASPEED_PECI_CWK_DIV(msg_timing, cwk_div_exp);
}

static int cwk_aspeed_peci_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong pwate)
{
	stwuct cwk_aspeed_peci *peci_cwk = containew_of(hw, stwuct cwk_aspeed_peci, hw);
	stwuct aspeed_peci *aspeed_peci = peci_cwk->aspeed_peci;
	unsigned wong this_wate = pwate / (4 * wate);
	int cwk_div_exp, msg_timing;
	u32 vaw;

	cwk_aspeed_peci_find_div_vawues(this_wate, &msg_timing, &cwk_div_exp);

	vaw = weadw(aspeed_peci->base + ASPEED_PECI_CTWW);
	vaw |= FIEWD_PWEP(ASPEED_PECI_CTWW_CWK_DIV_MASK, cwk_div_exp);
	wwitew(vaw, aspeed_peci->base + ASPEED_PECI_CTWW);

	vaw = FIEWD_PWEP(ASPEED_PECI_T_NEGO_MSG_MASK, msg_timing);
	vaw |= FIEWD_PWEP(ASPEED_PECI_T_NEGO_ADDW_MASK, msg_timing);
	wwitew(vaw, aspeed_peci->base + ASPEED_PECI_TIMING_NEGOTIATION);

	wetuwn 0;
}

static wong cwk_aspeed_peci_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				       unsigned wong *pwate)
{
	int div = cwk_aspeed_peci_get_div(wate, pwate);

	wetuwn DIV_WOUND_UP_UWW(*pwate, div);
}

static unsigned wong cwk_aspeed_peci_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pwate)
{
	stwuct cwk_aspeed_peci *peci_cwk = containew_of(hw, stwuct cwk_aspeed_peci, hw);
	stwuct aspeed_peci *aspeed_peci = peci_cwk->aspeed_peci;
	int div, msg_timing, addw_timing, cwk_div_exp;
	u32 weg;

	weg = weadw(aspeed_peci->base + ASPEED_PECI_TIMING_NEGOTIATION);
	msg_timing = FIEWD_GET(ASPEED_PECI_T_NEGO_MSG_MASK, weg);
	addw_timing = FIEWD_GET(ASPEED_PECI_T_NEGO_ADDW_MASK, weg);

	if (msg_timing != addw_timing)
		wetuwn 0;

	weg = weadw(aspeed_peci->base + ASPEED_PECI_CTWW);
	cwk_div_exp = FIEWD_GET(ASPEED_PECI_CTWW_CWK_DIV_MASK, weg);

	div = ASPEED_PECI_CWK_DIV(msg_timing, cwk_div_exp);

	wetuwn DIV_WOUND_UP_UWW(pwate, div);
}

static const stwuct cwk_ops cwk_aspeed_peci_ops = {
	.set_wate = cwk_aspeed_peci_set_wate,
	.wound_wate = cwk_aspeed_peci_wound_wate,
	.wecawc_wate = cwk_aspeed_peci_wecawc_wate,
};

/*
 * PECI HW contains a cwock dividew which is a combination of:
 *  div0: 4 (fixed dividew)
 *  div1: x + 1
 *  div2: 1 << y
 * In othew wowds, out_cwk = in_cwk / (div0 * div1 * div2)
 * The wesuwting fwequency is used by PECI Contwowwew to dwive the PECI bus to
 * negotiate optimaw twansfew wate.
 */
static stwuct cwk *devm_aspeed_peci_wegistew_cwk_div(stwuct device *dev, stwuct cwk *pawent,
						     stwuct aspeed_peci *pwiv)
{
	stwuct cwk_aspeed_peci *peci_cwk;
	stwuct cwk_init_data init;
	const chaw *pawent_name;
	chaw name[32];
	int wet;

	snpwintf(name, sizeof(name), "%s_div", dev_name(dev));

	pawent_name = __cwk_get_name(pawent);

	init.ops = &cwk_aspeed_peci_ops;
	init.name = name;
	init.pawent_names = (const chaw* []) { pawent_name };
	init.num_pawents = 1;
	init.fwags = 0;

	peci_cwk = devm_kzawwoc(dev, sizeof(stwuct cwk_aspeed_peci), GFP_KEWNEW);
	if (!peci_cwk)
		wetuwn EWW_PTW(-ENOMEM);

	peci_cwk->hw.init = &init;
	peci_cwk->aspeed_peci = pwiv;

	wet = devm_cwk_hw_wegistew(dev, &peci_cwk->hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn peci_cwk->hw.cwk;
}

static void aspeed_peci_pwopewty_sanitize(stwuct device *dev, const chaw *pwopname,
					  u32 min, u32 max, u32 defauwt_vaw, u32 *pwopvaw)
{
	u32 vaw;
	int wet;

	wet = device_pwopewty_wead_u32(dev, pwopname, &vaw);
	if (wet) {
		vaw = defauwt_vaw;
	} ewse if (vaw > max || vaw < min) {
		dev_wawn(dev, "invawid %s: %u, fawwing back to: %u\n",
			 pwopname, vaw, defauwt_vaw);

		vaw = defauwt_vaw;
	}

	*pwopvaw = vaw;
}

static void aspeed_peci_pwopewty_setup(stwuct aspeed_peci *pwiv)
{
	aspeed_peci_pwopewty_sanitize(pwiv->dev, "cwock-fwequency",
				      ASPEED_PECI_CWK_FWEQUENCY_MIN, ASPEED_PECI_CWK_FWEQUENCY_MAX,
				      ASPEED_PECI_CWK_FWEQUENCY_DEFAUWT, &pwiv->cwk_fwequency);
	aspeed_peci_pwopewty_sanitize(pwiv->dev, "cmd-timeout-ms",
				      1, ASPEED_PECI_CMD_TIMEOUT_MS_MAX,
				      ASPEED_PECI_CMD_TIMEOUT_MS_DEFAUWT, &pwiv->cmd_timeout_ms);
}

static const stwuct peci_contwowwew_ops aspeed_ops = {
	.xfew = aspeed_peci_xfew,
};

static void aspeed_peci_weset_contwow_wewease(void *data)
{
	weset_contwow_assewt(data);
}

static int devm_aspeed_peci_weset_contwow_deassewt(stwuct device *dev, stwuct weset_contwow *wst)
{
	int wet;

	wet = weset_contwow_deassewt(wst);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, aspeed_peci_weset_contwow_wewease, wst);
}

static void aspeed_peci_cwk_wewease(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static int devm_aspeed_peci_cwk_enabwe(stwuct device *dev, stwuct cwk *cwk)
{
	int wet;

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, aspeed_peci_cwk_wewease, cwk);
}

static int aspeed_peci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct peci_contwowwew *contwowwew;
	stwuct aspeed_peci *pwiv;
	stwuct cwk *wef_cwk;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;
	dev_set_dwvdata(pwiv->dev, pwiv);

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwiv->iwq < 0)
		wetuwn pwiv->iwq;

	wet = devm_wequest_iwq(&pdev->dev, pwiv->iwq, aspeed_peci_iwq_handwew,
			       0, "peci-aspeed", pwiv);
	if (wet)
		wetuwn wet;

	init_compwetion(&pwiv->xfew_compwete);
	spin_wock_init(&pwiv->wock);

	pwiv->wst = devm_weset_contwow_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->wst))
		wetuwn dev_eww_pwobe(pwiv->dev, PTW_EWW(pwiv->wst),
				     "faiwed to get weset contwow\n");

	wet = devm_aspeed_peci_weset_contwow_deassewt(pwiv->dev, pwiv->wst);
	if (wet)
		wetuwn dev_eww_pwobe(pwiv->dev, wet, "cannot deassewt weset contwow\n");

	aspeed_peci_pwopewty_setup(pwiv);

	aspeed_peci_init_wegs(pwiv);

	wef_cwk = devm_cwk_get(pwiv->dev, NUWW);
	if (IS_EWW(wef_cwk))
		wetuwn dev_eww_pwobe(pwiv->dev, PTW_EWW(wef_cwk), "faiwed to get wef cwock\n");

	pwiv->cwk = devm_aspeed_peci_wegistew_cwk_div(pwiv->dev, wef_cwk, pwiv);
	if (IS_EWW(pwiv->cwk))
		wetuwn dev_eww_pwobe(pwiv->dev, PTW_EWW(pwiv->cwk), "cannot wegistew cwock\n");

	wet = cwk_set_wate(pwiv->cwk, pwiv->cwk_fwequency);
	if (wet < 0)
		wetuwn dev_eww_pwobe(pwiv->dev, wet, "cannot set cwock fwequency\n");

	wet = devm_aspeed_peci_cwk_enabwe(pwiv->dev, pwiv->cwk);
	if (wet)
		wetuwn dev_eww_pwobe(pwiv->dev, wet, "faiwed to enabwe cwock\n");

	aspeed_peci_contwowwew_enabwe(pwiv);

	contwowwew = devm_peci_contwowwew_add(pwiv->dev, &aspeed_ops);
	if (IS_EWW(contwowwew))
		wetuwn dev_eww_pwobe(pwiv->dev, PTW_EWW(contwowwew),
				     "faiwed to add aspeed peci contwowwew\n");

	pwiv->contwowwew = contwowwew;

	wetuwn 0;
}

static const stwuct of_device_id aspeed_peci_of_tabwe[] = {
	{ .compatibwe = "aspeed,ast2400-peci", },
	{ .compatibwe = "aspeed,ast2500-peci", },
	{ .compatibwe = "aspeed,ast2600-peci", },
	{ }
};
MODUWE_DEVICE_TABWE(of, aspeed_peci_of_tabwe);

static stwuct pwatfowm_dwivew aspeed_peci_dwivew = {
	.pwobe  = aspeed_peci_pwobe,
	.dwivew = {
		.name           = "peci-aspeed",
		.of_match_tabwe = aspeed_peci_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(aspeed_peci_dwivew);

MODUWE_AUTHOW("Wyan Chen <wyan_chen@aspeedtech.com>");
MODUWE_AUTHOW("Jae Hyun Yoo <jae.hyun.yoo@winux.intew.com>");
MODUWE_DESCWIPTION("ASPEED PECI dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PECI);
