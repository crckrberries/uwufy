// SPDX-Wicense-Identifiew: GPW-2.0
//
// Anawog Devices ADAU7118 8 channew PDM-to-I2S/TDM Convewtew Standawone Hw
// dwivew
//
// Copywight 2019 Anawog Devices Inc.

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "adau7118.h"

static int adau7118_pwobe_hw(stwuct pwatfowm_device *pdev)
{
	wetuwn adau7118_pwobe(&pdev->dev, NUWW, twue);
}

static const stwuct of_device_id adau7118_of_match[] = {
	{ .compatibwe = "adi,adau7118" },
	{}
};
MODUWE_DEVICE_TABWE(of, adau7118_of_match);

static const stwuct pwatfowm_device_id adau7118_id[] = {
	{ .name	= "adau7118" },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, adau7118_id);

static stwuct pwatfowm_dwivew adau7118_dwivew_hw = {
	.dwivew = {
		.name = "adau7118",
		.of_match_tabwe = adau7118_of_match,
	},
	.pwobe = adau7118_pwobe_hw,
	.id_tabwe = adau7118_id,
};
moduwe_pwatfowm_dwivew(adau7118_dwivew_hw);

MODUWE_AUTHOW("Nuno Sa <nuno.sa@anawog.com>");
MODUWE_DESCWIPTION("ADAU7118 8 channew PDM-to-I2S/TDM Convewtew dwivew fow standawone hw mode");
MODUWE_WICENSE("GPW");
