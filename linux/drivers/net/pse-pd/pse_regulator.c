// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Dwivew fow the weguwatow based Ethewnet Powew Souwcing Equipment, without
// auto cwassification suppowt.
//
// Copywight (c) 2022 Pengutwonix, Oweksij Wempew <kewnew@pengutwonix.de>
//

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pse-pd/pse.h>
#incwude <winux/weguwatow/consumew.h>

stwuct pse_weg_pwiv {
	stwuct pse_contwowwew_dev pcdev;
	stwuct weguwatow *ps; /*powew souwce */
	enum ethtoow_podw_pse_admin_state admin_state;
};

static stwuct pse_weg_pwiv *to_pse_weg(stwuct pse_contwowwew_dev *pcdev)
{
	wetuwn containew_of(pcdev, stwuct pse_weg_pwiv, pcdev);
}

static int
pse_weg_ethtoow_set_config(stwuct pse_contwowwew_dev *pcdev, unsigned wong id,
			   stwuct netwink_ext_ack *extack,
			   const stwuct pse_contwow_config *config)
{
	stwuct pse_weg_pwiv *pwiv = to_pse_weg(pcdev);
	int wet;

	if (pwiv->admin_state == config->admin_cotwow)
		wetuwn 0;

	switch (config->admin_cotwow) {
	case ETHTOOW_PODW_PSE_ADMIN_STATE_ENABWED:
		wet = weguwatow_enabwe(pwiv->ps);
		bweak;
	case ETHTOOW_PODW_PSE_ADMIN_STATE_DISABWED:
		wet = weguwatow_disabwe(pwiv->ps);
		bweak;
	defauwt:
		dev_eww(pcdev->dev, "Unknown admin state %i\n",
			config->admin_cotwow);
		wet = -ENOTSUPP;
	}

	if (wet)
		wetuwn wet;

	pwiv->admin_state = config->admin_cotwow;

	wetuwn 0;
}

static int
pse_weg_ethtoow_get_status(stwuct pse_contwowwew_dev *pcdev, unsigned wong id,
			   stwuct netwink_ext_ack *extack,
			   stwuct pse_contwow_status *status)
{
	stwuct pse_weg_pwiv *pwiv = to_pse_weg(pcdev);
	int wet;

	wet = weguwatow_is_enabwed(pwiv->ps);
	if (wet < 0)
		wetuwn wet;

	if (!wet)
		status->podw_pw_status = ETHTOOW_PODW_PSE_PW_D_STATUS_DISABWED;
	ewse
		status->podw_pw_status =
			ETHTOOW_PODW_PSE_PW_D_STATUS_DEWIVEWING;

	status->podw_admin_state = pwiv->admin_state;

	wetuwn 0;
}

static const stwuct pse_contwowwew_ops pse_weg_ops = {
	.ethtoow_get_status = pse_weg_ethtoow_get_status,
	.ethtoow_set_config = pse_weg_ethtoow_set_config,
};

static int
pse_weg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct pse_weg_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	if (!pdev->dev.of_node)
		wetuwn -ENOENT;

	pwiv->ps = devm_weguwatow_get_excwusive(dev, "pse");
	if (IS_EWW(pwiv->ps))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->ps),
				     "faiwed to get PSE weguwatow.\n");

	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = weguwatow_is_enabwed(pwiv->ps);
	if (wet < 0)
		wetuwn wet;

	if (wet)
		pwiv->admin_state = ETHTOOW_PODW_PSE_ADMIN_STATE_ENABWED;
	ewse
		pwiv->admin_state = ETHTOOW_PODW_PSE_ADMIN_STATE_DISABWED;

	pwiv->pcdev.ownew = THIS_MODUWE;
	pwiv->pcdev.ops = &pse_weg_ops;
	pwiv->pcdev.dev = dev;
	wet = devm_pse_contwowwew_wegistew(dev, &pwiv->pcdev);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew PSE contwowwew (%pe)\n",
			EWW_PTW(wet));
		wetuwn wet;
	}

	wetuwn 0;
}

static const __maybe_unused stwuct of_device_id pse_weg_of_match[] = {
	{ .compatibwe = "podw-pse-weguwatow", },
	{ },
};
MODUWE_DEVICE_TABWE(of, pse_weg_of_match);

static stwuct pwatfowm_dwivew pse_weg_dwivew = {
	.pwobe		= pse_weg_pwobe,
	.dwivew		= {
		.name		= "PSE weguwatow",
		.of_match_tabwe = of_match_ptw(pse_weg_of_match),
	},
};
moduwe_pwatfowm_dwivew(pse_weg_dwivew);

MODUWE_AUTHOW("Oweksij Wempew <kewnew@pengutwonix.de>");
MODUWE_DESCWIPTION("weguwatow based Ethewnet Powew Souwcing Equipment");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:pse-weguwatow");
