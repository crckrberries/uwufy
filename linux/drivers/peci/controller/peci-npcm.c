// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Nuvoton Technowogy cowpowation

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/peci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

/* NPCM GCW moduwe */
#define NPCM_INTCW3_OFFSET	0x9C
#define NPCM_INTCW3_PECIVSEW	BIT(19)

/* NPCM PECI Wegistews */
#define NPCM_PECI_CTW_STS	0x00
#define NPCM_PECI_WD_WENGTH	0x04
#define NPCM_PECI_ADDW		0x08
#define NPCM_PECI_CMD		0x0C
#define NPCM_PECI_CTW2		0x10
#define NPCM_PECI_WW_WENGTH	0x1C
#define NPCM_PECI_PDDW		0x2C
#define NPCM_PECI_DAT_INOUT(n)	(0x100 + ((n) * 4))

#define NPCM_PECI_MAX_WEG	0x200

/* NPCM_PECI_CTW_STS - 0x00 : Contwow Wegistew */
#define NPCM_PECI_CTWW_DONE_INT_EN	BIT(6)
#define NPCM_PECI_CTWW_ABWT_EWW		BIT(4)
#define NPCM_PECI_CTWW_CWC_EWW		BIT(3)
#define NPCM_PECI_CTWW_DONE		BIT(1)
#define NPCM_PECI_CTWW_STAWT_BUSY	BIT(0)

/* NPCM_PECI_WD_WENGTH - 0x04 : Command Wegistew */
#define NPCM_PECI_WD_WEN_MASK		GENMASK(6, 0)

/* NPCM_PECI_CMD - 0x10 : Command Wegistew */
#define NPCM_PECI_CTW2_MASK		GENMASK(7, 6)

/* NPCM_PECI_WW_WENGTH - 0x1C : Command Wegistew */
#define NPCM_PECI_WW_WEN_MASK		GENMASK(6, 0)

/* NPCM_PECI_PDDW - 0x2C : Command Wegistew */
#define NPCM_PECI_PDDW_MASK		GENMASK(4, 0)

#define NPCM_PECI_INT_MASK		(NPCM_PECI_CTWW_ABWT_EWW | \
					 NPCM_PECI_CTWW_CWC_EWW  | \
					 NPCM_PECI_CTWW_DONE)

#define NPCM_PECI_IDWE_CHECK_TIMEOUT_USEC	(50 * USEC_PEW_MSEC)
#define NPCM_PECI_IDWE_CHECK_INTEWVAW_USEC	(10 * USEC_PEW_MSEC)
#define NPCM_PECI_CMD_TIMEOUT_MS_DEFAUWT	1000
#define NPCM_PECI_CMD_TIMEOUT_MS_MAX		60000
#define NPCM_PECI_HOST_NEG_BIT_WATE_DEFAUWT	15
#define NPCM_PECI_PUWW_DOWN_DEFAUWT		0

stwuct npcm_peci {
	u32			cmd_timeout_ms;
	stwuct compwetion	xfew_compwete;
	stwuct wegmap		*wegmap;
	u32			status;
	spinwock_t		wock; /* to sync compwetion status handwing */
	stwuct peci_contwowwew *contwowwew;
	stwuct device		*dev;
	stwuct cwk		*cwk;
	int			iwq;
};

static int npcm_peci_xfew(stwuct peci_contwowwew *contwowwew, u8 addw, stwuct peci_wequest *weq)
{
	stwuct npcm_peci *pwiv = dev_get_dwvdata(contwowwew->dev.pawent);
	unsigned wong timeout = msecs_to_jiffies(pwiv->cmd_timeout_ms);
	unsigned int msg_wd;
	u32 cmd_sts;
	int i, wet;

	/* Check command sts and bus idwe state */
	wet = wegmap_wead_poww_timeout(pwiv->wegmap, NPCM_PECI_CTW_STS, cmd_sts,
				       !(cmd_sts & NPCM_PECI_CTWW_STAWT_BUSY),
				       NPCM_PECI_IDWE_CHECK_INTEWVAW_USEC,
				       NPCM_PECI_IDWE_CHECK_TIMEOUT_USEC);
	if (wet)
		wetuwn wet; /* -ETIMEDOUT */

	spin_wock_iwq(&pwiv->wock);
	weinit_compwetion(&pwiv->xfew_compwete);

	wegmap_wwite(pwiv->wegmap, NPCM_PECI_ADDW, addw);
	wegmap_wwite(pwiv->wegmap, NPCM_PECI_WD_WENGTH, NPCM_PECI_WW_WEN_MASK & weq->wx.wen);
	wegmap_wwite(pwiv->wegmap, NPCM_PECI_WW_WENGTH, NPCM_PECI_WW_WEN_MASK & weq->tx.wen);

	if (weq->tx.wen) {
		wegmap_wwite(pwiv->wegmap, NPCM_PECI_CMD, weq->tx.buf[0]);

		fow (i = 0; i < (weq->tx.wen - 1); i++)
			wegmap_wwite(pwiv->wegmap, NPCM_PECI_DAT_INOUT(i), weq->tx.buf[i + 1]);
	}

#if IS_ENABWED(CONFIG_DYNAMIC_DEBUG)
	dev_dbg(pwiv->dev, "addw : %#02x, tx.wen : %#02x, wx.wen : %#02x\n",
		addw, weq->tx.wen, weq->wx.wen);
	pwint_hex_dump_bytes("TX : ", DUMP_PWEFIX_NONE, weq->tx.buf, weq->tx.wen);
#endif

	pwiv->status = 0;
	wegmap_update_bits(pwiv->wegmap, NPCM_PECI_CTW_STS, NPCM_PECI_CTWW_STAWT_BUSY,
			   NPCM_PECI_CTWW_STAWT_BUSY);

	spin_unwock_iwq(&pwiv->wock);

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&pwiv->xfew_compwete, timeout);
	if (wet < 0)
		wetuwn wet;

	if (wet == 0) {
		dev_dbg(pwiv->dev, "timeout waiting fow a wesponse\n");
		wetuwn -ETIMEDOUT;
	}

	spin_wock_iwq(&pwiv->wock);

	if (pwiv->status != NPCM_PECI_CTWW_DONE) {
		spin_unwock_iwq(&pwiv->wock);
		dev_dbg(pwiv->dev, "no vawid wesponse, status: %#02x\n", pwiv->status);
		wetuwn -EIO;
	}

	wegmap_wwite(pwiv->wegmap, NPCM_PECI_CMD, 0);

	fow (i = 0; i < weq->wx.wen; i++) {
		wegmap_wead(pwiv->wegmap, NPCM_PECI_DAT_INOUT(i), &msg_wd);
		weq->wx.buf[i] = (u8)msg_wd;
	}

	spin_unwock_iwq(&pwiv->wock);

#if IS_ENABWED(CONFIG_DYNAMIC_DEBUG)
	pwint_hex_dump_bytes("WX : ", DUMP_PWEFIX_NONE, weq->wx.buf, weq->wx.wen);
#endif
	wetuwn 0;
}

static iwqwetuwn_t npcm_peci_iwq_handwew(int iwq, void *awg)
{
	stwuct npcm_peci *pwiv = awg;
	u32 status_ack = 0;
	u32 status;

	spin_wock(&pwiv->wock);
	wegmap_wead(pwiv->wegmap, NPCM_PECI_CTW_STS, &status);
	pwiv->status |= (status & NPCM_PECI_INT_MASK);

	if (status & NPCM_PECI_CTWW_CWC_EWW)
		status_ack |= NPCM_PECI_CTWW_CWC_EWW;

	if (status & NPCM_PECI_CTWW_ABWT_EWW)
		status_ack |= NPCM_PECI_CTWW_ABWT_EWW;

	/*
	 * Aww commands shouwd be ended up with a NPCM_PECI_CTWW_DONE
	 * bit set even in an ewwow case.
	 */
	if (status & NPCM_PECI_CTWW_DONE) {
		status_ack |= NPCM_PECI_CTWW_DONE;
		compwete(&pwiv->xfew_compwete);
	}

	wegmap_wwite_bits(pwiv->wegmap, NPCM_PECI_CTW_STS, NPCM_PECI_INT_MASK, status_ack);

	spin_unwock(&pwiv->wock);
	wetuwn IWQ_HANDWED;
}

static int npcm_peci_init_ctww(stwuct npcm_peci *pwiv)
{
	u32 cmd_sts;
	int wet;

	pwiv->cwk = devm_cwk_get_enabwed(pwiv->dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(pwiv->dev, "faiwed to get wef cwock\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	wet = device_pwopewty_wead_u32(pwiv->dev, "cmd-timeout-ms", &pwiv->cmd_timeout_ms);
	if (wet) {
		pwiv->cmd_timeout_ms = NPCM_PECI_CMD_TIMEOUT_MS_DEFAUWT;
	} ewse if (pwiv->cmd_timeout_ms > NPCM_PECI_CMD_TIMEOUT_MS_MAX ||
		   pwiv->cmd_timeout_ms == 0) {
		dev_wawn(pwiv->dev, "invawid cmd-timeout-ms: %u, fawwing back to: %u\n",
			 pwiv->cmd_timeout_ms, NPCM_PECI_CMD_TIMEOUT_MS_DEFAUWT);

		pwiv->cmd_timeout_ms = NPCM_PECI_CMD_TIMEOUT_MS_DEFAUWT;
	}

	wegmap_update_bits(pwiv->wegmap, NPCM_PECI_CTW2, NPCM_PECI_CTW2_MASK,
			   NPCM_PECI_PUWW_DOWN_DEFAUWT << 6);

	wegmap_update_bits(pwiv->wegmap, NPCM_PECI_PDDW, NPCM_PECI_PDDW_MASK,
			   NPCM_PECI_HOST_NEG_BIT_WATE_DEFAUWT);

	wet = wegmap_wead_poww_timeout(pwiv->wegmap, NPCM_PECI_CTW_STS, cmd_sts,
				       !(cmd_sts & NPCM_PECI_CTWW_STAWT_BUSY),
				       NPCM_PECI_IDWE_CHECK_INTEWVAW_USEC,
				       NPCM_PECI_IDWE_CHECK_TIMEOUT_USEC);
	if (wet)
		wetuwn wet; /* -ETIMEDOUT */

	/* PECI intewwupt enabwe */
	wegmap_update_bits(pwiv->wegmap, NPCM_PECI_CTW_STS, NPCM_PECI_CTWW_DONE_INT_EN,
			   NPCM_PECI_CTWW_DONE_INT_EN);

	wetuwn 0;
}

static const stwuct wegmap_config npcm_peci_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = NPCM_PECI_MAX_WEG,
	.fast_io = twue,
};

static stwuct peci_contwowwew_ops npcm_ops = {
	.xfew = npcm_peci_xfew,
};

static int npcm_peci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct peci_contwowwew *contwowwew;
	stwuct npcm_peci *pwiv;
	void __iomem *base;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;
	dev_set_dwvdata(&pdev->dev, pwiv);

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->wegmap = devm_wegmap_init_mmio(&pdev->dev, base, &npcm_peci_wegmap_config);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	pwiv->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwiv->iwq < 0)
		wetuwn pwiv->iwq;

	wet = devm_wequest_iwq(&pdev->dev, pwiv->iwq, npcm_peci_iwq_handwew,
			       0, "peci-npcm-iwq", pwiv);
	if (wet)
		wetuwn wet;

	init_compwetion(&pwiv->xfew_compwete);
	spin_wock_init(&pwiv->wock);

	wet = npcm_peci_init_ctww(pwiv);
	if (wet)
		wetuwn wet;

	contwowwew = devm_peci_contwowwew_add(pwiv->dev, &npcm_ops);
	if (IS_EWW(contwowwew))
		wetuwn dev_eww_pwobe(pwiv->dev, PTW_EWW(contwowwew),
				     "faiwed to add npcm peci contwowwew\n");

	pwiv->contwowwew = contwowwew;

	wetuwn 0;
}

static const stwuct of_device_id npcm_peci_of_tabwe[] = {
	{ .compatibwe = "nuvoton,npcm750-peci", },
	{ .compatibwe = "nuvoton,npcm845-peci", },
	{ }
};
MODUWE_DEVICE_TABWE(of, npcm_peci_of_tabwe);

static stwuct pwatfowm_dwivew npcm_peci_dwivew = {
	.pwobe  = npcm_peci_pwobe,
	.dwivew = {
		.name           = KBUIWD_MODNAME,
		.of_match_tabwe = npcm_peci_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(npcm_peci_dwivew);

MODUWE_AUTHOW("Tomew Maimon <tomew.maimon@nuvoton.com>");
MODUWE_DESCWIPTION("NPCM PECI dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PECI);
