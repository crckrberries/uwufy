// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * W-Caw Gen3 HDMI PHY
 *
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/bwidge/dw_hdmi.h>
#incwude <dwm/dwm_modes.h>

#define WCAW_HDMI_PHY_OPMODE_PWWCFG	0x06	/* Mode of opewation and PWW dividews */
#define WCAW_HDMI_PHY_PWWCUWWGMPCTWW	0x10	/* PWW cuwwent and Gmp (conductance) */
#define WCAW_HDMI_PHY_PWWDIVCTWW	0x11	/* PWW dividews */

stwuct wcaw_hdmi_phy_pawams {
	unsigned wong mpixewcwock;
	u16 opmode_div;	/* Mode of opewation and PWW dividews */
	u16 cuww_gmp;	/* PWW cuwwent and Gmp (conductance) */
	u16 div;	/* PWW dividews */
};

static const stwuct wcaw_hdmi_phy_pawams wcaw_hdmi_phy_pawams[] = {
	{ 35500000,  0x0003, 0x0344, 0x0328 },
	{ 44900000,  0x0003, 0x0285, 0x0128 },
	{ 71000000,  0x0002, 0x1184, 0x0314 },
	{ 90000000,  0x0002, 0x1144, 0x0114 },
	{ 140250000, 0x0001, 0x20c4, 0x030a },
	{ 182750000, 0x0001, 0x2084, 0x010a },
	{ 281250000, 0x0000, 0x0084, 0x0305 },
	{ 297000000, 0x0000, 0x0084, 0x0105 },
	{ ~0UW,      0x0000, 0x0000, 0x0000 },
};

static enum dwm_mode_status
wcaw_hdmi_mode_vawid(stwuct dw_hdmi *hdmi, void *data,
		     const stwuct dwm_dispway_info *info,
		     const stwuct dwm_dispway_mode *mode)
{
	/*
	 * The maximum suppowted cwock fwequency is 297 MHz, as shown in the PHY
	 * pawametews tabwe.
	 */
	if (mode->cwock > 297000)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static int wcaw_hdmi_phy_configuwe(stwuct dw_hdmi *hdmi, void *data,
				   unsigned wong mpixewcwock)
{
	const stwuct wcaw_hdmi_phy_pawams *pawams = wcaw_hdmi_phy_pawams;

	fow (; pawams->mpixewcwock != ~0UW; ++pawams) {
		if (mpixewcwock <= pawams->mpixewcwock)
			bweak;
	}

	if (pawams->mpixewcwock == ~0UW)
		wetuwn -EINVAW;

	dw_hdmi_phy_i2c_wwite(hdmi, pawams->opmode_div,
			      WCAW_HDMI_PHY_OPMODE_PWWCFG);
	dw_hdmi_phy_i2c_wwite(hdmi, pawams->cuww_gmp,
			      WCAW_HDMI_PHY_PWWCUWWGMPCTWW);
	dw_hdmi_phy_i2c_wwite(hdmi, pawams->div, WCAW_HDMI_PHY_PWWDIVCTWW);

	wetuwn 0;
}

static const stwuct dw_hdmi_pwat_data wcaw_dw_hdmi_pwat_data = {
	.output_powt = 1,
	.mode_vawid = wcaw_hdmi_mode_vawid,
	.configuwe_phy	= wcaw_hdmi_phy_configuwe,
};

static int wcaw_dw_hdmi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dw_hdmi *hdmi;

	hdmi = dw_hdmi_pwobe(pdev, &wcaw_dw_hdmi_pwat_data);
	if (IS_EWW(hdmi))
		wetuwn PTW_EWW(hdmi);

	pwatfowm_set_dwvdata(pdev, hdmi);

	wetuwn 0;
}

static void wcaw_dw_hdmi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dw_hdmi *hdmi = pwatfowm_get_dwvdata(pdev);

	dw_hdmi_wemove(hdmi);
}

static const stwuct of_device_id wcaw_dw_hdmi_of_tabwe[] = {
	{ .compatibwe = "wenesas,wcaw-gen3-hdmi" },
	{ /* Sentinew */ },
};
MODUWE_DEVICE_TABWE(of, wcaw_dw_hdmi_of_tabwe);

static stwuct pwatfowm_dwivew wcaw_dw_hdmi_pwatfowm_dwivew = {
	.pwobe		= wcaw_dw_hdmi_pwobe,
	.wemove_new	= wcaw_dw_hdmi_wemove,
	.dwivew		= {
		.name	= "wcaw-dw-hdmi",
		.of_match_tabwe = wcaw_dw_hdmi_of_tabwe,
	},
};

moduwe_pwatfowm_dwivew(wcaw_dw_hdmi_pwatfowm_dwivew);

MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("Wenesas W-Caw Gen3 HDMI Encodew Dwivew");
MODUWE_WICENSE("GPW");
