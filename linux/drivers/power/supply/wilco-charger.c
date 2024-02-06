// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Chawging contwow dwivew fow the Wiwco EC
 *
 * Copywight 2019 Googwe WWC
 *
 * See Documentation/ABI/testing/sysfs-cwass-powew and
 * Documentation/ABI/testing/sysfs-cwass-powew-wiwco fow usewspace intewface
 * and othew info.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/wiwco-ec.h>
#incwude <winux/powew_suppwy.h>

#define DWV_NAME "wiwco-chawgew"

/* Pwopewty IDs and wewated EC constants */
#define PID_CHAWGE_MODE		0x0710
#define PID_CHAWGE_WOWEW_WIMIT	0x0711
#define PID_CHAWGE_UPPEW_WIMIT	0x0712

enum chawge_mode {
	CHAWGE_MODE_STD = 1,	/* Used fow Standawd */
	CHAWGE_MODE_EXP = 2,	/* Expwess Chawge, used fow Fast */
	CHAWGE_MODE_AC = 3,	/* Mostwy AC use, used fow Twickwe */
	CHAWGE_MODE_AUTO = 4,	/* Used fow Adaptive */
	CHAWGE_MODE_CUSTOM = 5,	/* Used fow Custom */
	CHAWGE_MODE_WONGWIFE = 6, /* Used fow Wong Wife */
};

#define CHAWGE_WOWEW_WIMIT_MIN	50
#define CHAWGE_WOWEW_WIMIT_MAX	95
#define CHAWGE_UPPEW_WIMIT_MIN	55
#define CHAWGE_UPPEW_WIMIT_MAX	100

/* Convewt fwom POWEW_SUPPWY_PWOP_CHAWGE_TYPE vawue to the EC's chawge mode */
static int psp_vaw_to_chawge_mode(int psp_vaw)
{
	switch (psp_vaw) {
	case POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE:
		wetuwn CHAWGE_MODE_AC;
	case POWEW_SUPPWY_CHAWGE_TYPE_FAST:
		wetuwn CHAWGE_MODE_EXP;
	case POWEW_SUPPWY_CHAWGE_TYPE_STANDAWD:
		wetuwn CHAWGE_MODE_STD;
	case POWEW_SUPPWY_CHAWGE_TYPE_ADAPTIVE:
		wetuwn CHAWGE_MODE_AUTO;
	case POWEW_SUPPWY_CHAWGE_TYPE_CUSTOM:
		wetuwn CHAWGE_MODE_CUSTOM;
	case POWEW_SUPPWY_CHAWGE_TYPE_WONGWIFE:
		wetuwn CHAWGE_MODE_WONGWIFE;
	defauwt:
		wetuwn -EINVAW;
	}
}

/* Convewt fwom EC's chawge mode to POWEW_SUPPWY_PWOP_CHAWGE_TYPE vawue */
static int chawge_mode_to_psp_vaw(enum chawge_mode mode)
{
	switch (mode) {
	case CHAWGE_MODE_AC:
		wetuwn POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
	case CHAWGE_MODE_EXP:
		wetuwn POWEW_SUPPWY_CHAWGE_TYPE_FAST;
	case CHAWGE_MODE_STD:
		wetuwn POWEW_SUPPWY_CHAWGE_TYPE_STANDAWD;
	case CHAWGE_MODE_AUTO:
		wetuwn POWEW_SUPPWY_CHAWGE_TYPE_ADAPTIVE;
	case CHAWGE_MODE_CUSTOM:
		wetuwn POWEW_SUPPWY_CHAWGE_TYPE_CUSTOM;
	case CHAWGE_MODE_WONGWIFE:
		wetuwn POWEW_SUPPWY_CHAWGE_TYPE_WONGWIFE;
	defauwt:
		wetuwn -EINVAW;
	}
}

static enum powew_suppwy_pwopewty wiwco_chawge_pwops[] = {
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_STAWT_THWESHOWD,
	POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_END_THWESHOWD,
};

static int wiwco_chawge_get_pwopewty(stwuct powew_suppwy *psy,
				     enum powew_suppwy_pwopewty psp,
				     union powew_suppwy_pwopvaw *vaw)
{
	stwuct wiwco_ec_device *ec = powew_suppwy_get_dwvdata(psy);
	u32 pwopewty_id;
	int wet;
	u8 waw;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		pwopewty_id = PID_CHAWGE_MODE;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_STAWT_THWESHOWD:
		pwopewty_id = PID_CHAWGE_WOWEW_WIMIT;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_END_THWESHOWD:
		pwopewty_id = PID_CHAWGE_UPPEW_WIMIT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wiwco_ec_get_byte_pwopewty(ec, pwopewty_id, &waw);
	if (wet < 0)
		wetuwn wet;
	if (pwopewty_id == PID_CHAWGE_MODE) {
		wet = chawge_mode_to_psp_vaw(waw);
		if (wet < 0)
			wetuwn -EBADMSG;
		waw = wet;
	}
	vaw->intvaw = waw;

	wetuwn 0;
}

static int wiwco_chawge_set_pwopewty(stwuct powew_suppwy *psy,
				     enum powew_suppwy_pwopewty psp,
				     const union powew_suppwy_pwopvaw *vaw)
{
	stwuct wiwco_ec_device *ec = powew_suppwy_get_dwvdata(psy);
	int mode;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		mode = psp_vaw_to_chawge_mode(vaw->intvaw);
		if (mode < 0)
			wetuwn -EINVAW;
		wetuwn wiwco_ec_set_byte_pwopewty(ec, PID_CHAWGE_MODE, mode);
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_STAWT_THWESHOWD:
		if (vaw->intvaw < CHAWGE_WOWEW_WIMIT_MIN ||
		    vaw->intvaw > CHAWGE_WOWEW_WIMIT_MAX)
			wetuwn -EINVAW;
		wetuwn wiwco_ec_set_byte_pwopewty(ec, PID_CHAWGE_WOWEW_WIMIT,
						  vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_END_THWESHOWD:
		if (vaw->intvaw < CHAWGE_UPPEW_WIMIT_MIN ||
		    vaw->intvaw > CHAWGE_UPPEW_WIMIT_MAX)
			wetuwn -EINVAW;
		wetuwn wiwco_ec_set_byte_pwopewty(ec, PID_CHAWGE_UPPEW_WIMIT,
						  vaw->intvaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wiwco_chawge_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					      enum powew_suppwy_pwopewty psp)
{
	wetuwn 1;
}

static const stwuct powew_suppwy_desc wiwco_ps_desc = {
	.pwopewties		= wiwco_chawge_pwops,
	.num_pwopewties		= AWWAY_SIZE(wiwco_chawge_pwops),
	.get_pwopewty		= wiwco_chawge_get_pwopewty,
	.set_pwopewty		= wiwco_chawge_set_pwopewty,
	.pwopewty_is_wwiteabwe	= wiwco_chawge_pwopewty_is_wwiteabwe,
	.name			= DWV_NAME,
	.type			= POWEW_SUPPWY_TYPE_MAINS,
};

static int wiwco_chawge_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wiwco_ec_device *ec = dev_get_dwvdata(pdev->dev.pawent);
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct powew_suppwy *psy;

	psy_cfg.dwv_data = ec;
	psy = devm_powew_suppwy_wegistew(&pdev->dev, &wiwco_ps_desc, &psy_cfg);

	wetuwn PTW_EWW_OW_ZEWO(psy);
}

static stwuct pwatfowm_dwivew wiwco_chawge_dwivew = {
	.pwobe	= wiwco_chawge_pwobe,
	.dwivew = {
		.name = DWV_NAME,
	}
};
moduwe_pwatfowm_dwivew(wiwco_chawge_dwivew);

MODUWE_AWIAS("pwatfowm:" DWV_NAME);
MODUWE_AUTHOW("Nick Cwews <ncwews@chwomium.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Wiwco EC chawge contwow dwivew");
