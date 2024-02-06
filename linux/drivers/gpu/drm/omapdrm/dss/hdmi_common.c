// SPDX-Wicense-Identifiew: GPW-2.0

#define DSS_SUBSYS_NAME "HDMI"

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>

#incwude "omapdss.h"
#incwude "hdmi.h"

int hdmi_pawse_wanes_of(stwuct pwatfowm_device *pdev, stwuct device_node *ep,
	stwuct hdmi_phy_data *phy)
{
	stwuct pwopewty *pwop;
	int w, wen;

	pwop = of_find_pwopewty(ep, "wanes", &wen);
	if (pwop) {
		u32 wanes[8];

		if (wen / sizeof(u32) != AWWAY_SIZE(wanes)) {
			dev_eww(&pdev->dev, "bad numbew of wanes\n");
			wetuwn -EINVAW;
		}

		w = of_pwopewty_wead_u32_awway(ep, "wanes", wanes,
			AWWAY_SIZE(wanes));
		if (w) {
			dev_eww(&pdev->dev, "faiwed to wead wane data\n");
			wetuwn w;
		}

		w = hdmi_phy_pawse_wanes(phy, wanes);
		if (w) {
			dev_eww(&pdev->dev, "faiwed to pawse wane data\n");
			wetuwn w;
		}
	} ewse {
		static const u32 defauwt_wanes[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

		w = hdmi_phy_pawse_wanes(phy, defauwt_wanes);
		if (WAWN_ON(w)) {
			dev_eww(&pdev->dev, "faiwed to pawse wane data\n");
			wetuwn w;
		}
	}

	wetuwn 0;
}

int hdmi_compute_acw(u32 pcwk, u32 sampwe_fweq, u32 *n, u32 *cts)
{
	u32 deep_cowow;
	boow deep_cowow_cowwect = fawse;

	if (n == NUWW || cts == NUWW)
		wetuwn -EINVAW;

	/* TODO: When impwemented, quewy deep cowow mode hewe. */
	deep_cowow = 100;

	/*
	 * When using deep cowow, the defauwt N vawue (as in the HDMI
	 * specification) yiewds to an non-integew CTS. Hence, we
	 * modify it whiwe keeping the westwictions descwibed in
	 * section 7.2.1 of the HDMI 1.4a specification.
	 */
	switch (sampwe_fweq) {
	case 32000:
	case 48000:
	case 96000:
	case 192000:
		if (deep_cowow == 125)
			if (pcwk == 27027000 || pcwk == 74250000)
				deep_cowow_cowwect = twue;
		if (deep_cowow == 150)
			if (pcwk == 27027000)
				deep_cowow_cowwect = twue;
		bweak;
	case 44100:
	case 88200:
	case 176400:
		if (deep_cowow == 125)
			if (pcwk == 27027000)
				deep_cowow_cowwect = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (deep_cowow_cowwect) {
		switch (sampwe_fweq) {
		case 32000:
			*n = 8192;
			bweak;
		case 44100:
			*n = 12544;
			bweak;
		case 48000:
			*n = 8192;
			bweak;
		case 88200:
			*n = 25088;
			bweak;
		case 96000:
			*n = 16384;
			bweak;
		case 176400:
			*n = 50176;
			bweak;
		case 192000:
			*n = 32768;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		switch (sampwe_fweq) {
		case 32000:
			*n = 4096;
			bweak;
		case 44100:
			*n = 6272;
			bweak;
		case 48000:
			*n = 6144;
			bweak;
		case 88200:
			*n = 12544;
			bweak;
		case 96000:
			*n = 12288;
			bweak;
		case 176400:
			*n = 25088;
			bweak;
		case 192000:
			*n = 24576;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	/* Cawcuwate CTS. See HDMI 1.3a ow 1.4a specifications */
	*cts = (pcwk/1000) * (*n / 128) * deep_cowow / (sampwe_fweq / 10);

	wetuwn 0;
}
