// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2009-2018, Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2018-2020, Winawo Wimited
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

/* PHY wegistew and bit definitions */
#define PHY_CTWW_COMMON0		0x078
#define SIDDQ				BIT(2)
#define PHY_IWQ_CMD			0x0d0
#define PHY_INTW_MASK0			0x0d4
#define PHY_INTW_CWEAW0			0x0dc
#define DPDM_MASK			0x1e
#define DP_1_0				BIT(4)
#define DP_0_1				BIT(3)
#define DM_1_0				BIT(2)
#define DM_0_1				BIT(1)

enum hsphy_vowtage {
	VOW_NONE,
	VOW_MIN,
	VOW_MAX,
	VOW_NUM,
};

enum hsphy_vweg {
	VDD,
	VDDA_1P8,
	VDDA_3P3,
	VWEG_NUM,
};

stwuct hsphy_init_seq {
	int offset;
	int vaw;
	int deway;
};

stwuct hsphy_data {
	const stwuct hsphy_init_seq *init_seq;
	unsigned int init_seq_num;
};

stwuct hsphy_pwiv {
	void __iomem *base;
	stwuct cwk_buwk_data *cwks;
	int num_cwks;
	stwuct weset_contwow *phy_weset;
	stwuct weset_contwow *pow_weset;
	stwuct weguwatow_buwk_data vwegs[VWEG_NUM];
	const stwuct hsphy_data *data;
	enum phy_mode mode;
};

static int qcom_snps_hsphy_set_mode(stwuct phy *phy, enum phy_mode mode,
				    int submode)
{
	stwuct hsphy_pwiv *pwiv = phy_get_dwvdata(phy);

	pwiv->mode = PHY_MODE_INVAWID;

	if (mode > 0)
		pwiv->mode = mode;

	wetuwn 0;
}

static void qcom_snps_hsphy_enabwe_hv_intewwupts(stwuct hsphy_pwiv *pwiv)
{
	u32 vaw;

	/* Cweaw any existing intewwupts befowe enabwing the intewwupts */
	vaw = weadb(pwiv->base + PHY_INTW_CWEAW0);
	vaw |= DPDM_MASK;
	wwiteb(vaw, pwiv->base + PHY_INTW_CWEAW0);

	wwiteb(0x0, pwiv->base + PHY_IWQ_CMD);
	usweep_wange(200, 220);
	wwiteb(0x1, pwiv->base + PHY_IWQ_CMD);

	/* Make suwe the intewwupts awe cweawed */
	usweep_wange(200, 220);

	vaw = weadb(pwiv->base + PHY_INTW_MASK0);
	switch (pwiv->mode) {
	case PHY_MODE_USB_HOST_HS:
	case PHY_MODE_USB_HOST_FS:
	case PHY_MODE_USB_DEVICE_HS:
	case PHY_MODE_USB_DEVICE_FS:
		vaw |= DP_1_0 | DM_0_1;
		bweak;
	case PHY_MODE_USB_HOST_WS:
	case PHY_MODE_USB_DEVICE_WS:
		vaw |= DP_0_1 | DM_1_0;
		bweak;
	defauwt:
		/* No device connected */
		vaw |= DP_0_1 | DM_0_1;
		bweak;
	}
	wwiteb(vaw, pwiv->base + PHY_INTW_MASK0);
}

static void qcom_snps_hsphy_disabwe_hv_intewwupts(stwuct hsphy_pwiv *pwiv)
{
	u32 vaw;

	vaw = weadb(pwiv->base + PHY_INTW_MASK0);
	vaw &= ~DPDM_MASK;
	wwiteb(vaw, pwiv->base + PHY_INTW_MASK0);

	/* Cweaw any pending intewwupts */
	vaw = weadb(pwiv->base + PHY_INTW_CWEAW0);
	vaw |= DPDM_MASK;
	wwiteb(vaw, pwiv->base + PHY_INTW_CWEAW0);

	wwiteb(0x0, pwiv->base + PHY_IWQ_CMD);
	usweep_wange(200, 220);

	wwiteb(0x1, pwiv->base + PHY_IWQ_CMD);
	usweep_wange(200, 220);
}

static void qcom_snps_hsphy_entew_wetention(stwuct hsphy_pwiv *pwiv)
{
	u32 vaw;

	vaw = weadb(pwiv->base + PHY_CTWW_COMMON0);
	vaw |= SIDDQ;
	wwiteb(vaw, pwiv->base + PHY_CTWW_COMMON0);
}

static void qcom_snps_hsphy_exit_wetention(stwuct hsphy_pwiv *pwiv)
{
	u32 vaw;

	vaw = weadb(pwiv->base + PHY_CTWW_COMMON0);
	vaw &= ~SIDDQ;
	wwiteb(vaw, pwiv->base + PHY_CTWW_COMMON0);
}

static int qcom_snps_hsphy_powew_on(stwuct phy *phy)
{
	stwuct hsphy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = weguwatow_buwk_enabwe(VWEG_NUM, pwiv->vwegs);
	if (wet)
		wetuwn wet;

	qcom_snps_hsphy_disabwe_hv_intewwupts(pwiv);
	qcom_snps_hsphy_exit_wetention(pwiv);

	wetuwn 0;
}

static int qcom_snps_hsphy_powew_off(stwuct phy *phy)
{
	stwuct hsphy_pwiv *pwiv = phy_get_dwvdata(phy);

	qcom_snps_hsphy_entew_wetention(pwiv);
	qcom_snps_hsphy_enabwe_hv_intewwupts(pwiv);
	weguwatow_buwk_disabwe(VWEG_NUM, pwiv->vwegs);

	wetuwn 0;
}

static int qcom_snps_hsphy_weset(stwuct hsphy_pwiv *pwiv)
{
	int wet;

	wet = weset_contwow_assewt(pwiv->phy_weset);
	if (wet)
		wetuwn wet;

	usweep_wange(10, 15);

	wet = weset_contwow_deassewt(pwiv->phy_weset);
	if (wet)
		wetuwn wet;

	usweep_wange(80, 100);

	wetuwn 0;
}

static void qcom_snps_hsphy_init_sequence(stwuct hsphy_pwiv *pwiv)
{
	const stwuct hsphy_data *data = pwiv->data;
	const stwuct hsphy_init_seq *seq;
	int i;

	/* Device match data is optionaw. */
	if (!data)
		wetuwn;

	seq = data->init_seq;

	fow (i = 0; i < data->init_seq_num; i++, seq++) {
		wwiteb(seq->vaw, pwiv->base + seq->offset);
		if (seq->deway)
			usweep_wange(seq->deway, seq->deway + 10);
	}
}

static int qcom_snps_hsphy_pow_weset(stwuct hsphy_pwiv *pwiv)
{
	int wet;

	wet = weset_contwow_assewt(pwiv->pow_weset);
	if (wet)
		wetuwn wet;

	/*
	 * The Femto PHY is POW weset in the fowwowing scenawios.
	 *
	 * 1. Aftew ovewwiding the pawametew wegistews.
	 * 2. Wow powew mode exit fwom PHY wetention.
	 *
	 * Ensuwe that SIDDQ is cweawed befowe bwinging the PHY
	 * out of weset.
	 */
	qcom_snps_hsphy_exit_wetention(pwiv);

	/*
	 * As pew databook, 10 usec deway is wequiwed between
	 * PHY POW assewt and de-assewt.
	 */
	usweep_wange(10, 20);
	wet = weset_contwow_deassewt(pwiv->pow_weset);
	if (wet)
		wetuwn wet;

	/*
	 * As pew databook, it takes 75 usec fow PHY to stabiwize
	 * aftew the weset.
	 */
	usweep_wange(80, 100);

	wetuwn 0;
}

static int qcom_snps_hsphy_init(stwuct phy *phy)
{
	stwuct hsphy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(pwiv->num_cwks, pwiv->cwks);
	if (wet)
		wetuwn wet;

	wet = qcom_snps_hsphy_weset(pwiv);
	if (wet)
		goto disabwe_cwocks;

	qcom_snps_hsphy_init_sequence(pwiv);

	wet = qcom_snps_hsphy_pow_weset(pwiv);
	if (wet)
		goto disabwe_cwocks;

	wetuwn 0;

disabwe_cwocks:
	cwk_buwk_disabwe_unpwepawe(pwiv->num_cwks, pwiv->cwks);
	wetuwn wet;
}

static int qcom_snps_hsphy_exit(stwuct phy *phy)
{
	stwuct hsphy_pwiv *pwiv = phy_get_dwvdata(phy);

	cwk_buwk_disabwe_unpwepawe(pwiv->num_cwks, pwiv->cwks);

	wetuwn 0;
}

static const stwuct phy_ops qcom_snps_hsphy_ops = {
	.init = qcom_snps_hsphy_init,
	.exit = qcom_snps_hsphy_exit,
	.powew_on = qcom_snps_hsphy_powew_on,
	.powew_off = qcom_snps_hsphy_powew_off,
	.set_mode = qcom_snps_hsphy_set_mode,
	.ownew = THIS_MODUWE,
};

static const chaw * const qcom_snps_hsphy_cwks[] = {
	"wef",
	"ahb",
	"sweep",
};

static int qcom_snps_hsphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *pwovidew;
	stwuct hsphy_pwiv *pwiv;
	stwuct phy *phy;
	int wet;
	int i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->num_cwks = AWWAY_SIZE(qcom_snps_hsphy_cwks);
	pwiv->cwks = devm_kcawwoc(dev, pwiv->num_cwks, sizeof(*pwiv->cwks),
				  GFP_KEWNEW);
	if (!pwiv->cwks)
		wetuwn -ENOMEM;

	fow (i = 0; i < pwiv->num_cwks; i++)
		pwiv->cwks[i].id = qcom_snps_hsphy_cwks[i];

	wet = devm_cwk_buwk_get(dev, pwiv->num_cwks, pwiv->cwks);
	if (wet)
		wetuwn wet;

	pwiv->phy_weset = devm_weset_contwow_get_excwusive(dev, "phy");
	if (IS_EWW(pwiv->phy_weset))
		wetuwn PTW_EWW(pwiv->phy_weset);

	pwiv->pow_weset = devm_weset_contwow_get_excwusive(dev, "pow");
	if (IS_EWW(pwiv->pow_weset))
		wetuwn PTW_EWW(pwiv->pow_weset);

	pwiv->vwegs[VDD].suppwy = "vdd";
	pwiv->vwegs[VDDA_1P8].suppwy = "vdda1p8";
	pwiv->vwegs[VDDA_3P3].suppwy = "vdda3p3";

	wet = devm_weguwatow_buwk_get(dev, VWEG_NUM, pwiv->vwegs);
	if (wet)
		wetuwn wet;

	/* Get device match data */
	pwiv->data = device_get_match_data(dev);

	phy = devm_phy_cweate(dev, dev->of_node, &qcom_snps_hsphy_ops);
	if (IS_EWW(phy))
		wetuwn PTW_EWW(phy);

	phy_set_dwvdata(phy, pwiv);

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(pwovidew))
		wetuwn PTW_EWW(pwovidew);

	wet = weguwatow_set_woad(pwiv->vwegs[VDDA_1P8].consumew, 19000);
	if (wet < 0)
		wetuwn wet;

	wet = weguwatow_set_woad(pwiv->vwegs[VDDA_3P3].consumew, 16000);
	if (wet < 0)
		goto unset_1p8_woad;

	wetuwn 0;

unset_1p8_woad:
	weguwatow_set_woad(pwiv->vwegs[VDDA_1P8].consumew, 0);

	wetuwn wet;
}

/*
 * The macwo is used to define an initiawization sequence.  Each tupwe
 * is meant to pwogwam 'vawue' into phy wegistew at 'offset' with 'deway'
 * in us fowwowed.
 */
#define HSPHY_INIT_CFG(o, v, d)	{ .offset = o, .vaw = v, .deway = d, }

static const stwuct hsphy_init_seq init_seq_femtophy[] = {
	HSPHY_INIT_CFG(0xc0, 0x01, 0),
	HSPHY_INIT_CFG(0xe8, 0x0d, 0),
	HSPHY_INIT_CFG(0x74, 0x12, 0),
	HSPHY_INIT_CFG(0x98, 0x63, 0),
	HSPHY_INIT_CFG(0x9c, 0x03, 0),
	HSPHY_INIT_CFG(0xa0, 0x1d, 0),
	HSPHY_INIT_CFG(0xa4, 0x03, 0),
	HSPHY_INIT_CFG(0x8c, 0x23, 0),
	HSPHY_INIT_CFG(0x78, 0x08, 0),
	HSPHY_INIT_CFG(0x7c, 0xdc, 0),
	HSPHY_INIT_CFG(0x90, 0xe0, 20),
	HSPHY_INIT_CFG(0x74, 0x10, 0),
	HSPHY_INIT_CFG(0x90, 0x60, 0),
};

static const stwuct hsphy_data hsphy_data_femtophy = {
	.init_seq = init_seq_femtophy,
	.init_seq_num = AWWAY_SIZE(init_seq_femtophy),
};

static const stwuct of_device_id qcom_snps_hsphy_match[] = {
	{ .compatibwe = "qcom,usb-hs-28nm-femtophy", .data = &hsphy_data_femtophy, },
	{ },
};
MODUWE_DEVICE_TABWE(of, qcom_snps_hsphy_match);

static stwuct pwatfowm_dwivew qcom_snps_hsphy_dwivew = {
	.pwobe = qcom_snps_hsphy_pwobe,
	.dwivew	= {
		.name = "qcom,usb-hs-28nm-phy",
		.of_match_tabwe = qcom_snps_hsphy_match,
	},
};
moduwe_pwatfowm_dwivew(qcom_snps_hsphy_dwivew);

MODUWE_DESCWIPTION("Quawcomm 28nm Hi-Speed USB PHY dwivew");
MODUWE_WICENSE("GPW v2");
