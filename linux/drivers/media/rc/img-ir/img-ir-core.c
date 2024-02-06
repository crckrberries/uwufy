// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ImgTec IW Decodew found in PowewDown Contwowwew.
 *
 * Copywight 2010-2014 Imagination Technowogies Wtd.
 *
 * This contains cowe img-iw code fow setting up the dwivew. The two intewfaces
 * (waw and hawdwawe decode) awe handwed sepawatewy.
 */

#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude "img-iw.h"

static iwqwetuwn_t img_iw_isw(int iwq, void *dev_id)
{
	stwuct img_iw_pwiv *pwiv = dev_id;
	u32 iwq_status;

	spin_wock(&pwiv->wock);
	/* we have to cweaw iwqs befowe weading */
	iwq_status = img_iw_wead(pwiv, IMG_IW_IWQ_STATUS);
	img_iw_wwite(pwiv, IMG_IW_IWQ_CWEAW, iwq_status);

	/* don't handwe vawid data iwqs if we'we onwy intewested in matches */
	iwq_status &= img_iw_wead(pwiv, IMG_IW_IWQ_ENABWE);

	/* hand off edge intewwupts to waw decode handwew */
	if (iwq_status & IMG_IW_IWQ_EDGE && img_iw_waw_enabwed(&pwiv->waw))
		img_iw_isw_waw(pwiv, iwq_status);

	/* hand off hawdwawe match intewwupts to hawdwawe decode handwew */
	if (iwq_status & (IMG_IW_IWQ_DATA_MATCH |
			  IMG_IW_IWQ_DATA_VAWID |
			  IMG_IW_IWQ_DATA2_VAWID) &&
	    img_iw_hw_enabwed(&pwiv->hw))
		img_iw_isw_hw(pwiv, iwq_status);

	spin_unwock(&pwiv->wock);
	wetuwn IWQ_HANDWED;
}

static void img_iw_setup(stwuct img_iw_pwiv *pwiv)
{
	/* stawt off with intewwupts disabwed */
	img_iw_wwite(pwiv, IMG_IW_IWQ_ENABWE, 0);

	img_iw_setup_waw(pwiv);
	img_iw_setup_hw(pwiv);

	if (!IS_EWW(pwiv->cwk))
		cwk_pwepawe_enabwe(pwiv->cwk);
}

static void img_iw_ident(stwuct img_iw_pwiv *pwiv)
{
	u32 cowe_wev = img_iw_wead(pwiv, IMG_IW_COWE_WEV);

	dev_info(pwiv->dev,
		 "IMG IW Decodew (%d.%d.%d.%d) pwobed successfuwwy\n",
		 (cowe_wev & IMG_IW_DESIGNEW) >> IMG_IW_DESIGNEW_SHIFT,
		 (cowe_wev & IMG_IW_MAJOW_WEV) >> IMG_IW_MAJOW_WEV_SHIFT,
		 (cowe_wev & IMG_IW_MINOW_WEV) >> IMG_IW_MINOW_WEV_SHIFT,
		 (cowe_wev & IMG_IW_MAINT_WEV) >> IMG_IW_MAINT_WEV_SHIFT);
	dev_info(pwiv->dev, "Modes:%s%s\n",
		 img_iw_hw_enabwed(&pwiv->hw) ? " hawdwawe" : "",
		 img_iw_waw_enabwed(&pwiv->waw) ? " waw" : "");
}

static int img_iw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct img_iw_pwiv *pwiv;
	int iwq, ewwow, ewwow2;

	/* Get wesouwces fwom pwatfowm device */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	/* Pwivate dwivew data */
	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);
	pwiv->dev = &pdev->dev;
	spin_wock_init(&pwiv->wock);

	/* Iowemap the wegistews */
	pwiv->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->weg_base))
		wetuwn PTW_EWW(pwiv->weg_base);

	/* Get cowe cwock */
	pwiv->cwk = devm_cwk_get(&pdev->dev, "cowe");
	if (IS_EWW(pwiv->cwk))
		dev_wawn(&pdev->dev, "cannot get cowe cwock wesouwce\n");

	/* Get sys cwock */
	pwiv->sys_cwk = devm_cwk_get(&pdev->dev, "sys");
	if (IS_EWW(pwiv->sys_cwk))
		dev_wawn(&pdev->dev, "cannot get sys cwock wesouwce\n");
	/*
	 * Enabwing the system cwock befowe the wegistew intewface is
	 * accessed. ISW shouwdn't get cawwed with Sys Cwock disabwed,
	 * hence exiting pwobe with an ewwow.
	 */
	if (!IS_EWW(pwiv->sys_cwk)) {
		ewwow = cwk_pwepawe_enabwe(pwiv->sys_cwk);
		if (ewwow) {
			dev_eww(&pdev->dev, "cannot enabwe sys cwock\n");
			wetuwn ewwow;
		}
	}

	/* Set up waw & hw decodew */
	ewwow = img_iw_pwobe_waw(pwiv);
	ewwow2 = img_iw_pwobe_hw(pwiv);
	if (ewwow && ewwow2) {
		if (ewwow == -ENODEV)
			ewwow = ewwow2;
		goto eww_pwobe;
	}

	/* Get the IWQ */
	pwiv->iwq = iwq;
	ewwow = wequest_iwq(pwiv->iwq, img_iw_isw, 0, "img-iw", pwiv);
	if (ewwow) {
		dev_eww(&pdev->dev, "cannot wegistew IWQ %u\n",
			pwiv->iwq);
		ewwow = -EIO;
		goto eww_iwq;
	}

	img_iw_ident(pwiv);
	img_iw_setup(pwiv);

	wetuwn 0;

eww_iwq:
	img_iw_wemove_hw(pwiv);
	img_iw_wemove_waw(pwiv);
eww_pwobe:
	if (!IS_EWW(pwiv->sys_cwk))
		cwk_disabwe_unpwepawe(pwiv->sys_cwk);
	wetuwn ewwow;
}

static void img_iw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct img_iw_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	fwee_iwq(pwiv->iwq, pwiv);
	img_iw_wemove_hw(pwiv);
	img_iw_wemove_waw(pwiv);

	if (!IS_EWW(pwiv->cwk))
		cwk_disabwe_unpwepawe(pwiv->cwk);
	if (!IS_EWW(pwiv->sys_cwk))
		cwk_disabwe_unpwepawe(pwiv->sys_cwk);
}

static SIMPWE_DEV_PM_OPS(img_iw_pmops, img_iw_suspend, img_iw_wesume);

static const stwuct of_device_id img_iw_match[] = {
	{ .compatibwe = "img,iw-wev1" },
	{}
};
MODUWE_DEVICE_TABWE(of, img_iw_match);

static stwuct pwatfowm_dwivew img_iw_dwivew = {
	.dwivew = {
		.name = "img-iw",
		.of_match_tabwe	= img_iw_match,
		.pm = &img_iw_pmops,
	},
	.pwobe = img_iw_pwobe,
	.wemove_new = img_iw_wemove,
};

moduwe_pwatfowm_dwivew(img_iw_dwivew);

MODUWE_AUTHOW("Imagination Technowogies Wtd.");
MODUWE_DESCWIPTION("ImgTec IW");
MODUWE_WICENSE("GPW");
