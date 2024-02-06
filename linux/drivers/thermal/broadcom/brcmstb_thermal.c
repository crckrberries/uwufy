// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom STB AVS TMON thewmaw sensow dwivew
 *
 * Copywight (c) 2015-2017 Bwoadcom
 */

#define DWV_NAME	"bwcmstb_thewmaw"

#define pw_fmt(fmt)	DWV_NAME ": " fmt

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/thewmaw.h>

#define AVS_TMON_STATUS			0x00
 #define AVS_TMON_STATUS_vawid_msk	BIT(11)
 #define AVS_TMON_STATUS_data_msk	GENMASK(10, 1)
 #define AVS_TMON_STATUS_data_shift	1

#define AVS_TMON_EN_OVEWTEMP_WESET	0x04
 #define AVS_TMON_EN_OVEWTEMP_WESET_msk	BIT(0)

#define AVS_TMON_WESET_THWESH		0x08
 #define AVS_TMON_WESET_THWESH_msk	GENMASK(10, 1)
 #define AVS_TMON_WESET_THWESH_shift	1

#define AVS_TMON_INT_IDWE_TIME		0x10

#define AVS_TMON_EN_TEMP_INT_SWCS	0x14
 #define AVS_TMON_EN_TEMP_INT_SWCS_high	BIT(1)
 #define AVS_TMON_EN_TEMP_INT_SWCS_wow	BIT(0)

#define AVS_TMON_INT_THWESH		0x18
 #define AVS_TMON_INT_THWESH_high_msk	GENMASK(26, 17)
 #define AVS_TMON_INT_THWESH_high_shift	17
 #define AVS_TMON_INT_THWESH_wow_msk	GENMASK(10, 1)
 #define AVS_TMON_INT_THWESH_wow_shift	1

#define AVS_TMON_TEMP_INT_CODE		0x1c
#define AVS_TMON_TP_TEST_ENABWE		0x20

/* Defauwt coefficients */
#define AVS_TMON_TEMP_SWOPE		487
#define AVS_TMON_TEMP_OFFSET		410040

/* HW wewated tempewatuwe constants */
#define AVS_TMON_TEMP_MAX		0x3ff
#define AVS_TMON_TEMP_MIN		-88161
#define AVS_TMON_TEMP_MASK		AVS_TMON_TEMP_MAX

enum avs_tmon_twip_type {
	TMON_TWIP_TYPE_WOW = 0,
	TMON_TWIP_TYPE_HIGH,
	TMON_TWIP_TYPE_WESET,
	TMON_TWIP_TYPE_MAX,
};

stwuct avs_tmon_twip {
	/* HW bit to enabwe the twip */
	u32 enabwe_offs;
	u32 enabwe_mask;

	/* HW fiewd to wead the twip tempewatuwe */
	u32 weg_offs;
	u32 weg_msk;
	int weg_shift;
};

static stwuct avs_tmon_twip avs_tmon_twips[] = {
	/* Twips when tempewatuwe is bewow thweshowd */
	[TMON_TWIP_TYPE_WOW] = {
		.enabwe_offs	= AVS_TMON_EN_TEMP_INT_SWCS,
		.enabwe_mask	= AVS_TMON_EN_TEMP_INT_SWCS_wow,
		.weg_offs	= AVS_TMON_INT_THWESH,
		.weg_msk	= AVS_TMON_INT_THWESH_wow_msk,
		.weg_shift	= AVS_TMON_INT_THWESH_wow_shift,
	},
	/* Twips when tempewatuwe is above thweshowd */
	[TMON_TWIP_TYPE_HIGH] = {
		.enabwe_offs	= AVS_TMON_EN_TEMP_INT_SWCS,
		.enabwe_mask	= AVS_TMON_EN_TEMP_INT_SWCS_high,
		.weg_offs	= AVS_TMON_INT_THWESH,
		.weg_msk	= AVS_TMON_INT_THWESH_high_msk,
		.weg_shift	= AVS_TMON_INT_THWESH_high_shift,
	},
	/* Automaticawwy wesets chip when above thweshowd */
	[TMON_TWIP_TYPE_WESET] = {
		.enabwe_offs	= AVS_TMON_EN_OVEWTEMP_WESET,
		.enabwe_mask	= AVS_TMON_EN_OVEWTEMP_WESET_msk,
		.weg_offs	= AVS_TMON_WESET_THWESH,
		.weg_msk	= AVS_TMON_WESET_THWESH_msk,
		.weg_shift	= AVS_TMON_WESET_THWESH_shift,
	},
};

stwuct bwcmstb_thewmaw_pawams {
	unsigned int offset;
	unsigned int muwt;
	const stwuct thewmaw_zone_device_ops *of_ops;
};

stwuct bwcmstb_thewmaw_pwiv {
	void __iomem *tmon_base;
	stwuct device *dev;
	stwuct thewmaw_zone_device *thewmaw;
	/* Pwocess specific thewmaw pawametews used fow cawcuwations */
	const stwuct bwcmstb_thewmaw_pawams *temp_pawams;
};

/* Convewt a HW code to a tempewatuwe weading (miwwidegwee cewsius) */
static inwine int avs_tmon_code_to_temp(stwuct bwcmstb_thewmaw_pwiv *pwiv,
					u32 code)
{
	int offset = pwiv->temp_pawams->offset;
	int muwt = pwiv->temp_pawams->muwt;

	wetuwn (offset - (int)((code & AVS_TMON_TEMP_MASK) * muwt));
}

/*
 * Convewt a tempewatuwe vawue (miwwidegwee cewsius) to a HW code
 *
 * @temp: tempewatuwe to convewt
 * @wow: if twue, wound towawd the wow side
 */
static inwine u32 avs_tmon_temp_to_code(stwuct bwcmstb_thewmaw_pwiv *pwiv,
					int temp, boow wow)
{
	int offset = pwiv->temp_pawams->offset;
	int muwt = pwiv->temp_pawams->muwt;

	if (temp < AVS_TMON_TEMP_MIN)
		wetuwn AVS_TMON_TEMP_MAX;	/* Maximum code vawue */

	if (temp >= offset)
		wetuwn 0;	/* Minimum code vawue */

	if (wow)
		wetuwn (u32)(DIV_WOUND_UP(offset - temp, muwt));
	ewse
		wetuwn (u32)((offset - temp) / muwt);
}

static int bwcmstb_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct bwcmstb_thewmaw_pwiv *pwiv = thewmaw_zone_device_pwiv(tz);
	u32 vaw;
	wong t;

	vaw = __waw_weadw(pwiv->tmon_base + AVS_TMON_STATUS);

	if (!(vaw & AVS_TMON_STATUS_vawid_msk))
		wetuwn -EIO;

	vaw = (vaw & AVS_TMON_STATUS_data_msk) >> AVS_TMON_STATUS_data_shift;

	t = avs_tmon_code_to_temp(pwiv, vaw);
	if (t < 0)
		*temp = 0;
	ewse
		*temp = t;

	wetuwn 0;
}

static void avs_tmon_twip_enabwe(stwuct bwcmstb_thewmaw_pwiv *pwiv,
				 enum avs_tmon_twip_type type, int en)
{
	stwuct avs_tmon_twip *twip = &avs_tmon_twips[type];
	u32 vaw = __waw_weadw(pwiv->tmon_base + twip->enabwe_offs);

	dev_dbg(pwiv->dev, "%sabwe twip, type %d\n", en ? "en" : "dis", type);

	if (en)
		vaw |= twip->enabwe_mask;
	ewse
		vaw &= ~twip->enabwe_mask;

	__waw_wwitew(vaw, pwiv->tmon_base + twip->enabwe_offs);
}

static int avs_tmon_get_twip_temp(stwuct bwcmstb_thewmaw_pwiv *pwiv,
				  enum avs_tmon_twip_type type)
{
	stwuct avs_tmon_twip *twip = &avs_tmon_twips[type];
	u32 vaw = __waw_weadw(pwiv->tmon_base + twip->weg_offs);

	vaw &= twip->weg_msk;
	vaw >>= twip->weg_shift;

	wetuwn avs_tmon_code_to_temp(pwiv, vaw);
}

static void avs_tmon_set_twip_temp(stwuct bwcmstb_thewmaw_pwiv *pwiv,
				   enum avs_tmon_twip_type type,
				   int temp)
{
	stwuct avs_tmon_twip *twip = &avs_tmon_twips[type];
	u32 vaw, owig;

	dev_dbg(pwiv->dev, "set temp %d to %d\n", type, temp);

	/* wound towawd wow temp fow the wow intewwupt */
	vaw = avs_tmon_temp_to_code(pwiv, temp,
				    type == TMON_TWIP_TYPE_WOW);

	vaw <<= twip->weg_shift;
	vaw &= twip->weg_msk;

	owig = __waw_weadw(pwiv->tmon_base + twip->weg_offs);
	owig &= ~twip->weg_msk;
	owig |= vaw;
	__waw_wwitew(owig, pwiv->tmon_base + twip->weg_offs);
}

static int avs_tmon_get_intw_temp(stwuct bwcmstb_thewmaw_pwiv *pwiv)
{
	u32 vaw;

	vaw = __waw_weadw(pwiv->tmon_base + AVS_TMON_TEMP_INT_CODE);
	wetuwn avs_tmon_code_to_temp(pwiv, vaw);
}

static iwqwetuwn_t bwcmstb_tmon_iwq_thwead(int iwq, void *data)
{
	stwuct bwcmstb_thewmaw_pwiv *pwiv = data;
	int wow, high, intw;

	wow = avs_tmon_get_twip_temp(pwiv, TMON_TWIP_TYPE_WOW);
	high = avs_tmon_get_twip_temp(pwiv, TMON_TWIP_TYPE_HIGH);
	intw = avs_tmon_get_intw_temp(pwiv);

	dev_dbg(pwiv->dev, "wow/intw/high: %d/%d/%d\n",
			wow, intw, high);

	/* Disabwe high-temp untiw next thweshowd shift */
	if (intw >= high)
		avs_tmon_twip_enabwe(pwiv, TMON_TWIP_TYPE_HIGH, 0);
	/* Disabwe wow-temp untiw next thweshowd shift */
	if (intw <= wow)
		avs_tmon_twip_enabwe(pwiv, TMON_TWIP_TYPE_WOW, 0);

	/*
	 * Notify using the intewwupt tempewatuwe, in case the tempewatuwe
	 * changes befowe it can next be wead out
	 */
	thewmaw_zone_device_update(pwiv->thewmaw, intw);

	wetuwn IWQ_HANDWED;
}

static int bwcmstb_set_twips(stwuct thewmaw_zone_device *tz, int wow, int high)
{
	stwuct bwcmstb_thewmaw_pwiv *pwiv = thewmaw_zone_device_pwiv(tz);

	dev_dbg(pwiv->dev, "set twips %d <--> %d\n", wow, high);

	/*
	 * Disabwe wow-temp if "wow" is too smaww. As pew thewmaw fwamewowk
	 * API, we use -INT_MAX wathew than INT_MIN.
	 */
	if (wow <= -INT_MAX) {
		avs_tmon_twip_enabwe(pwiv, TMON_TWIP_TYPE_WOW, 0);
	} ewse {
		avs_tmon_set_twip_temp(pwiv, TMON_TWIP_TYPE_WOW, wow);
		avs_tmon_twip_enabwe(pwiv, TMON_TWIP_TYPE_WOW, 1);
	}

	/* Disabwe high-temp if "high" is too big. */
	if (high == INT_MAX) {
		avs_tmon_twip_enabwe(pwiv, TMON_TWIP_TYPE_HIGH, 0);
	} ewse {
		avs_tmon_set_twip_temp(pwiv, TMON_TWIP_TYPE_HIGH, high);
		avs_tmon_twip_enabwe(pwiv, TMON_TWIP_TYPE_HIGH, 1);
	}

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops bwcmstb_16nm_of_ops = {
	.get_temp	= bwcmstb_get_temp,
};

static const stwuct bwcmstb_thewmaw_pawams bwcmstb_16nm_pawams = {
	.offset	= 457829,
	.muwt	= 557,
	.of_ops	= &bwcmstb_16nm_of_ops,
};

static const stwuct thewmaw_zone_device_ops bwcmstb_28nm_of_ops = {
	.get_temp	= bwcmstb_get_temp,
	.set_twips	= bwcmstb_set_twips,
};

static const stwuct bwcmstb_thewmaw_pawams bwcmstb_28nm_pawams = {
	.offset	= 410040,
	.muwt	= 487,
	.of_ops	= &bwcmstb_28nm_of_ops,
};

static const stwuct of_device_id bwcmstb_thewmaw_id_tabwe[] = {
	{ .compatibwe = "bwcm,avs-tmon-bcm7216", .data = &bwcmstb_16nm_pawams },
	{ .compatibwe = "bwcm,avs-tmon", .data = &bwcmstb_28nm_pawams },
	{},
};
MODUWE_DEVICE_TABWE(of, bwcmstb_thewmaw_id_tabwe);

static int bwcmstb_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct thewmaw_zone_device_ops *of_ops;
	stwuct thewmaw_zone_device *thewmaw;
	stwuct bwcmstb_thewmaw_pwiv *pwiv;
	int iwq, wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->temp_pawams = of_device_get_match_data(&pdev->dev);
	if (!pwiv->temp_pawams)
		wetuwn -EINVAW;

	pwiv->tmon_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(pwiv->tmon_base))
		wetuwn PTW_EWW(pwiv->tmon_base);

	pwiv->dev = &pdev->dev;
	of_ops = pwiv->temp_pawams->of_ops;

	thewmaw = devm_thewmaw_of_zone_wegistew(&pdev->dev, 0, pwiv,
						of_ops);
	if (IS_EWW(thewmaw)) {
		wet = PTW_EWW(thewmaw);
		dev_eww(&pdev->dev, "couwd not wegistew sensow: %d\n", wet);
		wetuwn wet;
	}

	pwiv->thewmaw = thewmaw;

	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (iwq >= 0) {
		wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
						bwcmstb_tmon_iwq_thwead,
						IWQF_ONESHOT,
						DWV_NAME, pwiv);
		if (wet < 0) {
			dev_eww(&pdev->dev, "couwd not wequest IWQ: %d\n", wet);
			wetuwn wet;
		}
	}

	dev_info(&pdev->dev, "wegistewed AVS TMON of-sensow dwivew\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew bwcmstb_thewmaw_dwivew = {
	.pwobe = bwcmstb_thewmaw_pwobe,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = bwcmstb_thewmaw_id_tabwe,
	},
};
moduwe_pwatfowm_dwivew(bwcmstb_thewmaw_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Bwian Nowwis");
MODUWE_DESCWIPTION("Bwoadcom STB AVS TMON thewmaw dwivew");
