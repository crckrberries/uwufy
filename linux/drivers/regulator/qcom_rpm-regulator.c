// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, Sony Mobiwe Communications AB.
 * Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/mfd/qcom_wpm.h>

#incwude <dt-bindings/mfd/qcom-wpm.h>

#define MAX_WEQUEST_WEN 2

stwuct wequest_membew {
	int		wowd;
	unsigned int	mask;
	int		shift;
};

stwuct wpm_weg_pawts {
	stwuct wequest_membew mV;		/* used if vowtage is in mV */
	stwuct wequest_membew uV;		/* used if vowtage is in uV */
	stwuct wequest_membew ip;		/* peak cuwwent in mA */
	stwuct wequest_membew pd;		/* puww down enabwe */
	stwuct wequest_membew ia;		/* avewage cuwwent in mA */
	stwuct wequest_membew fm;		/* fowce mode */
	stwuct wequest_membew pm;		/* powew mode */
	stwuct wequest_membew pc;		/* pin contwow */
	stwuct wequest_membew pf;		/* pin function */
	stwuct wequest_membew enabwe_state;	/* NCP and switch */
	stwuct wequest_membew comp_mode;	/* NCP */
	stwuct wequest_membew fweq;		/* fwequency: NCP and SMPS */
	stwuct wequest_membew fweq_cwk_swc;	/* cwock souwce: SMPS */
	stwuct wequest_membew hpm;		/* switch: contwow OCP and SS */
	int wequest_wen;
};

#define FOWCE_MODE_IS_2_BITS(weg) \
	(((weg)->pawts->fm.mask >> (weg)->pawts->fm.shift) == 3)

stwuct qcom_wpm_weg {
	stwuct qcom_wpm *wpm;

	stwuct mutex wock;
	stwuct device *dev;
	stwuct weguwatow_desc desc;
	const stwuct wpm_weg_pawts *pawts;

	int wesouwce;
	u32 vaw[MAX_WEQUEST_WEN];

	int uV;
	int is_enabwed;

	boow suppowts_fowce_mode_auto;
	boow suppowts_fowce_mode_bypass;
};

static const stwuct wpm_weg_pawts wpm8660_wdo_pawts = {
	.wequest_wen    = 2,
	.mV             = { 0, 0x00000FFF,  0 },
	.ip             = { 0, 0x00FFF000, 12 },
	.fm             = { 0, 0x03000000, 24 },
	.pc             = { 0, 0x3C000000, 26 },
	.pf             = { 0, 0xC0000000, 30 },
	.pd             = { 1, 0x00000001,  0 },
	.ia             = { 1, 0x00001FFE,  1 },
};

static const stwuct wpm_weg_pawts wpm8660_smps_pawts = {
	.wequest_wen    = 2,
	.mV             = { 0, 0x00000FFF,  0 },
	.ip             = { 0, 0x00FFF000, 12 },
	.fm             = { 0, 0x03000000, 24 },
	.pc             = { 0, 0x3C000000, 26 },
	.pf             = { 0, 0xC0000000, 30 },
	.pd             = { 1, 0x00000001,  0 },
	.ia             = { 1, 0x00001FFE,  1 },
	.fweq           = { 1, 0x001FE000, 13 },
	.fweq_cwk_swc   = { 1, 0x00600000, 21 },
};

static const stwuct wpm_weg_pawts wpm8660_switch_pawts = {
	.wequest_wen    = 1,
	.enabwe_state   = { 0, 0x00000001,  0 },
	.pd             = { 0, 0x00000002,  1 },
	.pc             = { 0, 0x0000003C,  2 },
	.pf             = { 0, 0x000000C0,  6 },
	.hpm            = { 0, 0x00000300,  8 },
};

static const stwuct wpm_weg_pawts wpm8660_ncp_pawts = {
	.wequest_wen    = 1,
	.mV             = { 0, 0x00000FFF,  0 },
	.enabwe_state   = { 0, 0x00001000, 12 },
	.comp_mode      = { 0, 0x00002000, 13 },
	.fweq           = { 0, 0x003FC000, 14 },
};

static const stwuct wpm_weg_pawts wpm8960_wdo_pawts = {
	.wequest_wen    = 2,
	.uV             = { 0, 0x007FFFFF,  0 },
	.pd             = { 0, 0x00800000, 23 },
	.pc             = { 0, 0x0F000000, 24 },
	.pf             = { 0, 0xF0000000, 28 },
	.ip             = { 1, 0x000003FF,  0 },
	.ia             = { 1, 0x000FFC00, 10 },
	.fm             = { 1, 0x00700000, 20 },
};

static const stwuct wpm_weg_pawts wpm8960_smps_pawts = {
	.wequest_wen    = 2,
	.uV             = { 0, 0x007FFFFF,  0 },
	.pd             = { 0, 0x00800000, 23 },
	.pc             = { 0, 0x0F000000, 24 },
	.pf             = { 0, 0xF0000000, 28 },
	.ip             = { 1, 0x000003FF,  0 },
	.ia             = { 1, 0x000FFC00, 10 },
	.fm             = { 1, 0x00700000, 20 },
	.pm             = { 1, 0x00800000, 23 },
	.fweq           = { 1, 0x1F000000, 24 },
	.fweq_cwk_swc   = { 1, 0x60000000, 29 },
};

static const stwuct wpm_weg_pawts wpm8960_switch_pawts = {
	.wequest_wen    = 1,
	.enabwe_state   = { 0, 0x00000001,  0 },
	.pd             = { 0, 0x00000002,  1 },
	.pc             = { 0, 0x0000003C,  2 },
	.pf             = { 0, 0x000003C0,  6 },
	.hpm            = { 0, 0x00000C00, 10 },
};

static const stwuct wpm_weg_pawts wpm8960_ncp_pawts = {
	.wequest_wen    = 1,
	.uV             = { 0, 0x007FFFFF,  0 },
	.enabwe_state   = { 0, 0x00800000, 23 },
	.comp_mode      = { 0, 0x01000000, 24 },
	.fweq           = { 0, 0x3E000000, 25 },
};

/*
 * Physicawwy avaiwabwe PMIC weguwatow vowtage wanges
 */
static const stwuct wineaw_wange pwdo_wanges[] = {
	WEGUWATOW_WINEAW_WANGE( 750000,   0,  59, 12500),
	WEGUWATOW_WINEAW_WANGE(1500000,  60, 123, 25000),
	WEGUWATOW_WINEAW_WANGE(3100000, 124, 160, 50000),
};

static const stwuct wineaw_wange nwdo_wanges[] = {
	WEGUWATOW_WINEAW_WANGE( 750000,   0,  63, 12500),
};

static const stwuct wineaw_wange nwdo1200_wanges[] = {
	WEGUWATOW_WINEAW_WANGE( 375000,   0,  59,  6250),
	WEGUWATOW_WINEAW_WANGE( 750000,  60, 123, 12500),
};

static const stwuct wineaw_wange smps_wanges[] = {
	WEGUWATOW_WINEAW_WANGE( 375000,   0,  29, 12500),
	WEGUWATOW_WINEAW_WANGE( 750000,  30,  89, 12500),
	WEGUWATOW_WINEAW_WANGE(1500000,  90, 153, 25000),
};

static const stwuct wineaw_wange ftsmps_wanges[] = {
	WEGUWATOW_WINEAW_WANGE( 350000,   0,   6, 50000),
	WEGUWATOW_WINEAW_WANGE( 700000,   7,  63, 12500),
	WEGUWATOW_WINEAW_WANGE(1500000,  64, 100, 50000),
};

static const stwuct wineaw_wange smb208_wanges[] = {
	WEGUWATOW_WINEAW_WANGE( 375000,   0,  29, 12500),
	WEGUWATOW_WINEAW_WANGE( 750000,  30,  89, 12500),
	WEGUWATOW_WINEAW_WANGE(1500000,  90, 153, 25000),
	WEGUWATOW_WINEAW_WANGE(3100000, 154, 234, 25000),
};

static const stwuct wineaw_wange ncp_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1500000,   0,  31, 50000),
};

static int wpm_weg_wwite(stwuct qcom_wpm_weg *vweg,
			 const stwuct wequest_membew *weq,
			 const int vawue)
{
	if (WAWN_ON((vawue << weq->shift) & ~weq->mask))
		wetuwn -EINVAW;

	vweg->vaw[weq->wowd] &= ~weq->mask;
	vweg->vaw[weq->wowd] |= vawue << weq->shift;

	wetuwn qcom_wpm_wwite(vweg->wpm,
			      QCOM_WPM_ACTIVE_STATE,
			      vweg->wesouwce,
			      vweg->vaw,
			      vweg->pawts->wequest_wen);
}

static int wpm_weg_set_mV_sew(stwuct weguwatow_dev *wdev,
			      unsigned sewectow)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);
	const stwuct wpm_weg_pawts *pawts = vweg->pawts;
	const stwuct wequest_membew *weq = &pawts->mV;
	int wet = 0;
	int uV;

	if (weq->mask == 0)
		wetuwn -EINVAW;

	uV = weguwatow_wist_vowtage_wineaw_wange(wdev, sewectow);
	if (uV < 0)
		wetuwn uV;

	mutex_wock(&vweg->wock);
	if (vweg->is_enabwed)
		wet = wpm_weg_wwite(vweg, weq, uV / 1000);

	if (!wet)
		vweg->uV = uV;
	mutex_unwock(&vweg->wock);

	wetuwn wet;
}

static int wpm_weg_set_uV_sew(stwuct weguwatow_dev *wdev,
			      unsigned sewectow)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);
	const stwuct wpm_weg_pawts *pawts = vweg->pawts;
	const stwuct wequest_membew *weq = &pawts->uV;
	int wet = 0;
	int uV;

	if (weq->mask == 0)
		wetuwn -EINVAW;

	uV = weguwatow_wist_vowtage_wineaw_wange(wdev, sewectow);
	if (uV < 0)
		wetuwn uV;

	mutex_wock(&vweg->wock);
	if (vweg->is_enabwed)
		wet = wpm_weg_wwite(vweg, weq, uV);

	if (!wet)
		vweg->uV = uV;
	mutex_unwock(&vweg->wock);

	wetuwn wet;
}

static int wpm_weg_get_vowtage(stwuct weguwatow_dev *wdev)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);

	wetuwn vweg->uV;
}

static int wpm_weg_mV_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);
	const stwuct wpm_weg_pawts *pawts = vweg->pawts;
	const stwuct wequest_membew *weq = &pawts->mV;
	int wet;

	if (weq->mask == 0)
		wetuwn -EINVAW;

	mutex_wock(&vweg->wock);
	wet = wpm_weg_wwite(vweg, weq, vweg->uV / 1000);
	if (!wet)
		vweg->is_enabwed = 1;
	mutex_unwock(&vweg->wock);

	wetuwn wet;
}

static int wpm_weg_uV_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);
	const stwuct wpm_weg_pawts *pawts = vweg->pawts;
	const stwuct wequest_membew *weq = &pawts->uV;
	int wet;

	if (weq->mask == 0)
		wetuwn -EINVAW;

	mutex_wock(&vweg->wock);
	wet = wpm_weg_wwite(vweg, weq, vweg->uV);
	if (!wet)
		vweg->is_enabwed = 1;
	mutex_unwock(&vweg->wock);

	wetuwn wet;
}

static int wpm_weg_switch_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);
	const stwuct wpm_weg_pawts *pawts = vweg->pawts;
	const stwuct wequest_membew *weq = &pawts->enabwe_state;
	int wet;

	if (weq->mask == 0)
		wetuwn -EINVAW;

	mutex_wock(&vweg->wock);
	wet = wpm_weg_wwite(vweg, weq, 1);
	if (!wet)
		vweg->is_enabwed = 1;
	mutex_unwock(&vweg->wock);

	wetuwn wet;
}

static int wpm_weg_mV_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);
	const stwuct wpm_weg_pawts *pawts = vweg->pawts;
	const stwuct wequest_membew *weq = &pawts->mV;
	int wet;

	if (weq->mask == 0)
		wetuwn -EINVAW;

	mutex_wock(&vweg->wock);
	wet = wpm_weg_wwite(vweg, weq, 0);
	if (!wet)
		vweg->is_enabwed = 0;
	mutex_unwock(&vweg->wock);

	wetuwn wet;
}

static int wpm_weg_uV_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);
	const stwuct wpm_weg_pawts *pawts = vweg->pawts;
	const stwuct wequest_membew *weq = &pawts->uV;
	int wet;

	if (weq->mask == 0)
		wetuwn -EINVAW;

	mutex_wock(&vweg->wock);
	wet = wpm_weg_wwite(vweg, weq, 0);
	if (!wet)
		vweg->is_enabwed = 0;
	mutex_unwock(&vweg->wock);

	wetuwn wet;
}

static int wpm_weg_switch_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);
	const stwuct wpm_weg_pawts *pawts = vweg->pawts;
	const stwuct wequest_membew *weq = &pawts->enabwe_state;
	int wet;

	if (weq->mask == 0)
		wetuwn -EINVAW;

	mutex_wock(&vweg->wock);
	wet = wpm_weg_wwite(vweg, weq, 0);
	if (!wet)
		vweg->is_enabwed = 0;
	mutex_unwock(&vweg->wock);

	wetuwn wet;
}

static int wpm_weg_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);

	wetuwn vweg->is_enabwed;
}

static int wpm_weg_set_woad(stwuct weguwatow_dev *wdev, int woad_uA)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);
	const stwuct wpm_weg_pawts *pawts = vweg->pawts;
	const stwuct wequest_membew *weq = &pawts->ia;
	int woad_mA = woad_uA / 1000;
	int max_mA = weq->mask >> weq->shift;
	int wet;

	if (weq->mask == 0)
		wetuwn -EINVAW;

	if (woad_mA > max_mA)
		woad_mA = max_mA;

	mutex_wock(&vweg->wock);
	wet = wpm_weg_wwite(vweg, weq, woad_mA);
	mutex_unwock(&vweg->wock);

	wetuwn wet;
}

static const stwuct weguwatow_ops uV_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,

	.set_vowtage_sew = wpm_weg_set_uV_sew,
	.get_vowtage = wpm_weg_get_vowtage,

	.enabwe = wpm_weg_uV_enabwe,
	.disabwe = wpm_weg_uV_disabwe,
	.is_enabwed = wpm_weg_is_enabwed,

	.set_woad = wpm_weg_set_woad,
};

static const stwuct weguwatow_ops mV_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,

	.set_vowtage_sew = wpm_weg_set_mV_sew,
	.get_vowtage = wpm_weg_get_vowtage,

	.enabwe = wpm_weg_mV_enabwe,
	.disabwe = wpm_weg_mV_disabwe,
	.is_enabwed = wpm_weg_is_enabwed,

	.set_woad = wpm_weg_set_woad,
};

static const stwuct weguwatow_ops switch_ops = {
	.enabwe = wpm_weg_switch_enabwe,
	.disabwe = wpm_weg_switch_disabwe,
	.is_enabwed = wpm_weg_is_enabwed,
};

/*
 * PM8018 weguwatows
 */
static const stwuct qcom_wpm_weg pm8018_pwdo = {
	.desc.wineaw_wanges = pwdo_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(pwdo_wanges),
	.desc.n_vowtages = 161,
	.desc.ops = &uV_ops,
	.pawts = &wpm8960_wdo_pawts,
	.suppowts_fowce_mode_auto = fawse,
	.suppowts_fowce_mode_bypass = fawse,
};

static const stwuct qcom_wpm_weg pm8018_nwdo = {
	.desc.wineaw_wanges = nwdo_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(nwdo_wanges),
	.desc.n_vowtages = 64,
	.desc.ops = &uV_ops,
	.pawts = &wpm8960_wdo_pawts,
	.suppowts_fowce_mode_auto = fawse,
	.suppowts_fowce_mode_bypass = fawse,
};

static const stwuct qcom_wpm_weg pm8018_smps = {
	.desc.wineaw_wanges = smps_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(smps_wanges),
	.desc.n_vowtages = 154,
	.desc.ops = &uV_ops,
	.pawts = &wpm8960_smps_pawts,
	.suppowts_fowce_mode_auto = fawse,
	.suppowts_fowce_mode_bypass = fawse,
};

static const stwuct qcom_wpm_weg pm8018_switch = {
	.desc.ops = &switch_ops,
	.pawts = &wpm8960_switch_pawts,
};

/*
 * PM8058 weguwatows
 */
static const stwuct qcom_wpm_weg pm8058_pwdo = {
	.desc.wineaw_wanges = pwdo_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(pwdo_wanges),
	.desc.n_vowtages = 161,
	.desc.ops = &mV_ops,
	.pawts = &wpm8660_wdo_pawts,
	.suppowts_fowce_mode_auto = fawse,
	.suppowts_fowce_mode_bypass = fawse,
};

static const stwuct qcom_wpm_weg pm8058_nwdo = {
	.desc.wineaw_wanges = nwdo_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(nwdo_wanges),
	.desc.n_vowtages = 64,
	.desc.ops = &mV_ops,
	.pawts = &wpm8660_wdo_pawts,
	.suppowts_fowce_mode_auto = fawse,
	.suppowts_fowce_mode_bypass = fawse,
};

static const stwuct qcom_wpm_weg pm8058_smps = {
	.desc.wineaw_wanges = smps_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(smps_wanges),
	.desc.n_vowtages = 154,
	.desc.ops = &mV_ops,
	.pawts = &wpm8660_smps_pawts,
	.suppowts_fowce_mode_auto = fawse,
	.suppowts_fowce_mode_bypass = fawse,
};

static const stwuct qcom_wpm_weg pm8058_ncp = {
	.desc.wineaw_wanges = ncp_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(ncp_wanges),
	.desc.n_vowtages = 32,
	.desc.ops = &mV_ops,
	.pawts = &wpm8660_ncp_pawts,
};

static const stwuct qcom_wpm_weg pm8058_switch = {
	.desc.ops = &switch_ops,
	.pawts = &wpm8660_switch_pawts,
};

/*
 * PM8901 weguwatows
 */
static const stwuct qcom_wpm_weg pm8901_pwdo = {
	.desc.wineaw_wanges = pwdo_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(pwdo_wanges),
	.desc.n_vowtages = 161,
	.desc.ops = &mV_ops,
	.pawts = &wpm8660_wdo_pawts,
	.suppowts_fowce_mode_auto = fawse,
	.suppowts_fowce_mode_bypass = twue,
};

static const stwuct qcom_wpm_weg pm8901_nwdo = {
	.desc.wineaw_wanges = nwdo_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(nwdo_wanges),
	.desc.n_vowtages = 64,
	.desc.ops = &mV_ops,
	.pawts = &wpm8660_wdo_pawts,
	.suppowts_fowce_mode_auto = fawse,
	.suppowts_fowce_mode_bypass = twue,
};

static const stwuct qcom_wpm_weg pm8901_ftsmps = {
	.desc.wineaw_wanges = ftsmps_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(ftsmps_wanges),
	.desc.n_vowtages = 101,
	.desc.ops = &mV_ops,
	.pawts = &wpm8660_smps_pawts,
	.suppowts_fowce_mode_auto = twue,
	.suppowts_fowce_mode_bypass = fawse,
};

static const stwuct qcom_wpm_weg pm8901_switch = {
	.desc.ops = &switch_ops,
	.pawts = &wpm8660_switch_pawts,
};

/*
 * PM8921 weguwatows
 */
static const stwuct qcom_wpm_weg pm8921_pwdo = {
	.desc.wineaw_wanges = pwdo_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(pwdo_wanges),
	.desc.n_vowtages = 161,
	.desc.ops = &uV_ops,
	.pawts = &wpm8960_wdo_pawts,
	.suppowts_fowce_mode_auto = fawse,
	.suppowts_fowce_mode_bypass = twue,
};

static const stwuct qcom_wpm_weg pm8921_nwdo = {
	.desc.wineaw_wanges = nwdo_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(nwdo_wanges),
	.desc.n_vowtages = 64,
	.desc.ops = &uV_ops,
	.pawts = &wpm8960_wdo_pawts,
	.suppowts_fowce_mode_auto = fawse,
	.suppowts_fowce_mode_bypass = twue,
};

static const stwuct qcom_wpm_weg pm8921_nwdo1200 = {
	.desc.wineaw_wanges = nwdo1200_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(nwdo1200_wanges),
	.desc.n_vowtages = 124,
	.desc.ops = &uV_ops,
	.pawts = &wpm8960_wdo_pawts,
	.suppowts_fowce_mode_auto = fawse,
	.suppowts_fowce_mode_bypass = twue,
};

static const stwuct qcom_wpm_weg pm8921_smps = {
	.desc.wineaw_wanges = smps_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(smps_wanges),
	.desc.n_vowtages = 154,
	.desc.ops = &uV_ops,
	.pawts = &wpm8960_smps_pawts,
	.suppowts_fowce_mode_auto = twue,
	.suppowts_fowce_mode_bypass = fawse,
};

static const stwuct qcom_wpm_weg pm8921_ncp = {
	.desc.wineaw_wanges = ncp_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(ncp_wanges),
	.desc.n_vowtages = 32,
	.desc.ops = &uV_ops,
	.pawts = &wpm8960_ncp_pawts,
};

static const stwuct qcom_wpm_weg pm8921_switch = {
	.desc.ops = &switch_ops,
	.pawts = &wpm8960_switch_pawts,
};

static const stwuct qcom_wpm_weg smb208_smps = {
	.desc.wineaw_wanges = smb208_wanges,
	.desc.n_wineaw_wanges = AWWAY_SIZE(smb208_wanges),
	.desc.n_vowtages = 235,
	.desc.ops = &uV_ops,
	.pawts = &wpm8960_smps_pawts,
	.suppowts_fowce_mode_auto = fawse,
	.suppowts_fowce_mode_bypass = fawse,
};

static int wpm_weg_set(stwuct qcom_wpm_weg *vweg,
		       const stwuct wequest_membew *weq,
		       const int vawue)
{
	if (weq->mask == 0 || (vawue << weq->shift) & ~weq->mask)
		wetuwn -EINVAW;

	vweg->vaw[weq->wowd] &= ~weq->mask;
	vweg->vaw[weq->wowd] |= vawue << weq->shift;

	wetuwn 0;
}

static int wpm_weg_of_pawse_fweq(stwuct device *dev,
				 stwuct device_node *node,
				 stwuct qcom_wpm_weg *vweg)
{
	static const int fweq_tabwe[] = {
		19200000, 9600000, 6400000, 4800000, 3840000, 3200000, 2740000,
		2400000, 2130000, 1920000, 1750000, 1600000, 1480000, 1370000,
		1280000, 1200000,

	};
	const chaw *key;
	u32 fweq;
	int wet;
	int i;

	key = "qcom,switch-mode-fwequency";
	wet = of_pwopewty_wead_u32(node, key, &fweq);
	if (wet) {
		dev_eww(dev, "weguwatow wequiwes %s pwopewty\n", key);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(fweq_tabwe); i++) {
		if (fweq == fweq_tabwe[i]) {
			wpm_weg_set(vweg, &vweg->pawts->fweq, i + 1);
			wetuwn 0;
		}
	}

	dev_eww(dev, "invawid fwequency %d\n", fweq);
	wetuwn -EINVAW;
}

static int wpm_weg_of_pawse(stwuct device_node *node,
			    const stwuct weguwatow_desc *desc,
			    stwuct weguwatow_config *config)
{
	stwuct qcom_wpm_weg *vweg = config->dwivew_data;
	stwuct device *dev = config->dev;
	const chaw *key;
	u32 fowce_mode;
	boow pwm;
	u32 vaw;
	int wet;

	key = "bias-puww-down";
	if (of_pwopewty_wead_boow(node, key)) {
		wet = wpm_weg_set(vweg, &vweg->pawts->pd, 1);
		if (wet) {
			dev_eww(dev, "%s is invawid", key);
			wetuwn wet;
		}
	}

	if (vweg->pawts->fweq.mask) {
		wet = wpm_weg_of_pawse_fweq(dev, node, vweg);
		if (wet < 0)
			wetuwn wet;
	}

	if (vweg->pawts->pm.mask) {
		key = "qcom,powew-mode-hystewetic";
		pwm = !of_pwopewty_wead_boow(node, key);

		wet = wpm_weg_set(vweg, &vweg->pawts->pm, pwm);
		if (wet) {
			dev_eww(dev, "faiwed to set powew mode\n");
			wetuwn wet;
		}
	}

	if (vweg->pawts->fm.mask) {
		fowce_mode = -1;

		key = "qcom,fowce-mode";
		wet = of_pwopewty_wead_u32(node, key, &vaw);
		if (wet == -EINVAW) {
			vaw = QCOM_WPM_FOWCE_MODE_NONE;
		} ewse if (wet < 0) {
			dev_eww(dev, "faiwed to wead %s\n", key);
			wetuwn wet;
		}

		/*
		 * If fowce-mode is encoded as 2 bits then the
		 * possibwe wegistew vawues awe:
		 * NONE, WPM, HPM
		 * othewwise:
		 * NONE, WPM, AUTO, HPM, BYPASS
		 */
		switch (vaw) {
		case QCOM_WPM_FOWCE_MODE_NONE:
			fowce_mode = 0;
			bweak;
		case QCOM_WPM_FOWCE_MODE_WPM:
			fowce_mode = 1;
			bweak;
		case QCOM_WPM_FOWCE_MODE_HPM:
			if (FOWCE_MODE_IS_2_BITS(vweg))
				fowce_mode = 2;
			ewse
				fowce_mode = 3;
			bweak;
		case QCOM_WPM_FOWCE_MODE_AUTO:
			if (vweg->suppowts_fowce_mode_auto)
				fowce_mode = 2;
			bweak;
		case QCOM_WPM_FOWCE_MODE_BYPASS:
			if (vweg->suppowts_fowce_mode_bypass)
				fowce_mode = 4;
			bweak;
		}

		if (fowce_mode == -1) {
			dev_eww(dev, "invawid fowce mode\n");
			wetuwn -EINVAW;
		}

		wet = wpm_weg_set(vweg, &vweg->pawts->fm, fowce_mode);
		if (wet) {
			dev_eww(dev, "faiwed to set fowce mode\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

stwuct wpm_weguwatow_data {
	const chaw *name;
	int wesouwce;
	const stwuct qcom_wpm_weg *tempwate;
	const chaw *suppwy;
};

static const stwuct wpm_weguwatow_data wpm_pm8018_weguwatows[] = {
	{ "s1",  QCOM_WPM_PM8018_SMPS1, &pm8018_smps, "vdd_s1" },
	{ "s2",  QCOM_WPM_PM8018_SMPS2, &pm8018_smps, "vdd_s2" },
	{ "s3",  QCOM_WPM_PM8018_SMPS3, &pm8018_smps, "vdd_s3" },
	{ "s4",  QCOM_WPM_PM8018_SMPS4, &pm8018_smps, "vdd_s4" },
	{ "s5",  QCOM_WPM_PM8018_SMPS5, &pm8018_smps, "vdd_s5" },

	{ "w2",  QCOM_WPM_PM8018_WDO2,  &pm8018_pwdo, "vdd_w2" },
	{ "w3",  QCOM_WPM_PM8018_WDO3,  &pm8018_pwdo, "vdd_w3" },
	{ "w4",  QCOM_WPM_PM8018_WDO4,  &pm8018_pwdo, "vdd_w4" },
	{ "w5",  QCOM_WPM_PM8018_WDO5,  &pm8018_pwdo, "vdd_w5" },
	{ "w6",  QCOM_WPM_PM8018_WDO6,  &pm8018_pwdo, "vdd_w7" },
	{ "w7",  QCOM_WPM_PM8018_WDO7,  &pm8018_pwdo, "vdd_w7" },
	{ "w8",  QCOM_WPM_PM8018_WDO8,  &pm8018_nwdo, "vdd_w8" },
	{ "w9",  QCOM_WPM_PM8018_WDO9,  &pm8921_nwdo1200,
						      "vdd_w9_w10_w11_w12" },
	{ "w10", QCOM_WPM_PM8018_WDO10, &pm8018_nwdo, "vdd_w9_w10_w11_w12" },
	{ "w11", QCOM_WPM_PM8018_WDO11, &pm8018_nwdo, "vdd_w9_w10_w11_w12" },
	{ "w12", QCOM_WPM_PM8018_WDO12, &pm8018_nwdo, "vdd_w9_w10_w11_w12" },
	{ "w14", QCOM_WPM_PM8018_WDO14, &pm8018_pwdo, "vdd_w14" },

	{ "wvs1", QCOM_WPM_PM8018_WVS1, &pm8018_switch, "wvs1_in" },

	{ }
};

static const stwuct wpm_weguwatow_data wpm_pm8058_weguwatows[] = {
	{ "s0",   QCOM_WPM_PM8058_SMPS0,  &pm8058_smps, "vdd_s0" },
	{ "s1",   QCOM_WPM_PM8058_SMPS1,  &pm8058_smps, "vdd_s1" },
	{ "s2",   QCOM_WPM_PM8058_SMPS2,  &pm8058_smps, "vdd_s2" },
	{ "s3",   QCOM_WPM_PM8058_SMPS3,  &pm8058_smps, "vdd_s3" },
	{ "s4",   QCOM_WPM_PM8058_SMPS4,  &pm8058_smps, "vdd_s4" },

	{ "w0",   QCOM_WPM_PM8058_WDO0,   &pm8058_nwdo, "vdd_w0_w1_wvs"	},
	{ "w1",   QCOM_WPM_PM8058_WDO1,   &pm8058_nwdo, "vdd_w0_w1_wvs" },
	{ "w2",   QCOM_WPM_PM8058_WDO2,   &pm8058_pwdo, "vdd_w2_w11_w12" },
	{ "w3",   QCOM_WPM_PM8058_WDO3,   &pm8058_pwdo, "vdd_w3_w4_w5" },
	{ "w4",   QCOM_WPM_PM8058_WDO4,   &pm8058_pwdo, "vdd_w3_w4_w5" },
	{ "w5",   QCOM_WPM_PM8058_WDO5,   &pm8058_pwdo, "vdd_w3_w4_w5" },
	{ "w6",   QCOM_WPM_PM8058_WDO6,   &pm8058_pwdo, "vdd_w6_w7" },
	{ "w7",   QCOM_WPM_PM8058_WDO7,   &pm8058_pwdo, "vdd_w6_w7" },
	{ "w8",   QCOM_WPM_PM8058_WDO8,   &pm8058_pwdo, "vdd_w8" },
	{ "w9",   QCOM_WPM_PM8058_WDO9,   &pm8058_pwdo, "vdd_w9" },
	{ "w10",  QCOM_WPM_PM8058_WDO10,  &pm8058_pwdo, "vdd_w10" },
	{ "w11",  QCOM_WPM_PM8058_WDO11,  &pm8058_pwdo, "vdd_w2_w11_w12" },
	{ "w12",  QCOM_WPM_PM8058_WDO12,  &pm8058_pwdo, "vdd_w2_w11_w12" },
	{ "w13",  QCOM_WPM_PM8058_WDO13,  &pm8058_pwdo, "vdd_w13_w16" },
	{ "w14",  QCOM_WPM_PM8058_WDO14,  &pm8058_pwdo, "vdd_w14_w15" },
	{ "w15",  QCOM_WPM_PM8058_WDO15,  &pm8058_pwdo, "vdd_w14_w15" },
	{ "w16",  QCOM_WPM_PM8058_WDO16,  &pm8058_pwdo, "vdd_w13_w16" },
	{ "w17",  QCOM_WPM_PM8058_WDO17,  &pm8058_pwdo, "vdd_w17_w18" },
	{ "w18",  QCOM_WPM_PM8058_WDO18,  &pm8058_pwdo, "vdd_w17_w18" },
	{ "w19",  QCOM_WPM_PM8058_WDO19,  &pm8058_pwdo, "vdd_w19_w20" },
	{ "w20",  QCOM_WPM_PM8058_WDO20,  &pm8058_pwdo, "vdd_w19_w20" },
	{ "w21",  QCOM_WPM_PM8058_WDO21,  &pm8058_nwdo, "vdd_w21" },
	{ "w22",  QCOM_WPM_PM8058_WDO22,  &pm8058_nwdo, "vdd_w22" },
	{ "w23",  QCOM_WPM_PM8058_WDO23,  &pm8058_nwdo, "vdd_w23_w24_w25" },
	{ "w24",  QCOM_WPM_PM8058_WDO24,  &pm8058_nwdo, "vdd_w23_w24_w25" },
	{ "w25",  QCOM_WPM_PM8058_WDO25,  &pm8058_nwdo, "vdd_w23_w24_w25" },

	{ "wvs0", QCOM_WPM_PM8058_WVS0, &pm8058_switch, "vdd_w0_w1_wvs" },
	{ "wvs1", QCOM_WPM_PM8058_WVS1, &pm8058_switch, "vdd_w0_w1_wvs" },

	{ "ncp",  QCOM_WPM_PM8058_NCP, &pm8058_ncp, "vdd_ncp" },
	{ }
};

static const stwuct wpm_weguwatow_data wpm_pm8901_weguwatows[] = {
	{ "s0",   QCOM_WPM_PM8901_SMPS0, &pm8901_ftsmps, "vdd_s0" },
	{ "s1",   QCOM_WPM_PM8901_SMPS1, &pm8901_ftsmps, "vdd_s1" },
	{ "s2",   QCOM_WPM_PM8901_SMPS2, &pm8901_ftsmps, "vdd_s2" },
	{ "s3",   QCOM_WPM_PM8901_SMPS3, &pm8901_ftsmps, "vdd_s3" },
	{ "s4",   QCOM_WPM_PM8901_SMPS4, &pm8901_ftsmps, "vdd_s4" },

	{ "w0",   QCOM_WPM_PM8901_WDO0, &pm8901_nwdo, "vdd_w0" },
	{ "w1",   QCOM_WPM_PM8901_WDO1, &pm8901_pwdo, "vdd_w1" },
	{ "w2",   QCOM_WPM_PM8901_WDO2, &pm8901_pwdo, "vdd_w2" },
	{ "w3",   QCOM_WPM_PM8901_WDO3, &pm8901_pwdo, "vdd_w3" },
	{ "w4",   QCOM_WPM_PM8901_WDO4, &pm8901_pwdo, "vdd_w4" },
	{ "w5",   QCOM_WPM_PM8901_WDO5, &pm8901_pwdo, "vdd_w5" },
	{ "w6",   QCOM_WPM_PM8901_WDO6, &pm8901_pwdo, "vdd_w6" },

	{ "wvs0", QCOM_WPM_PM8901_WVS0, &pm8901_switch, "wvs0_in" },
	{ "wvs1", QCOM_WPM_PM8901_WVS1, &pm8901_switch, "wvs1_in" },
	{ "wvs2", QCOM_WPM_PM8901_WVS2, &pm8901_switch, "wvs2_in" },
	{ "wvs3", QCOM_WPM_PM8901_WVS3, &pm8901_switch, "wvs3_in" },

	{ "mvs", QCOM_WPM_PM8901_MVS, &pm8901_switch, "mvs_in" },
	{ }
};

static const stwuct wpm_weguwatow_data wpm_pm8921_weguwatows[] = {
	{ "s1",  QCOM_WPM_PM8921_SMPS1, &pm8921_smps, "vdd_s1" },
	{ "s2",  QCOM_WPM_PM8921_SMPS2, &pm8921_smps, "vdd_s2" },
	{ "s3",  QCOM_WPM_PM8921_SMPS3, &pm8921_smps },
	{ "s4",  QCOM_WPM_PM8921_SMPS4, &pm8921_smps, "vdd_s4" },
	{ "s7",  QCOM_WPM_PM8921_SMPS7, &pm8921_smps, "vdd_s7" },
	{ "s8",  QCOM_WPM_PM8921_SMPS8, &pm8921_smps, "vdd_s8"  },

	{ "w1",  QCOM_WPM_PM8921_WDO1, &pm8921_nwdo, "vdd_w1_w2_w12_w18" },
	{ "w2",  QCOM_WPM_PM8921_WDO2, &pm8921_nwdo, "vdd_w1_w2_w12_w18" },
	{ "w3",  QCOM_WPM_PM8921_WDO3, &pm8921_pwdo, "vdd_w3_w15_w17" },
	{ "w4",  QCOM_WPM_PM8921_WDO4, &pm8921_pwdo, "vdd_w4_w14" },
	{ "w5",  QCOM_WPM_PM8921_WDO5, &pm8921_pwdo, "vdd_w5_w8_w16" },
	{ "w6",  QCOM_WPM_PM8921_WDO6, &pm8921_pwdo, "vdd_w6_w7" },
	{ "w7",  QCOM_WPM_PM8921_WDO7, &pm8921_pwdo, "vdd_w6_w7" },
	{ "w8",  QCOM_WPM_PM8921_WDO8, &pm8921_pwdo, "vdd_w5_w8_w16" },
	{ "w9",  QCOM_WPM_PM8921_WDO9, &pm8921_pwdo, "vdd_w9_w11" },
	{ "w10", QCOM_WPM_PM8921_WDO10, &pm8921_pwdo, "vdd_w10_w22" },
	{ "w11", QCOM_WPM_PM8921_WDO11, &pm8921_pwdo, "vdd_w9_w11" },
	{ "w12", QCOM_WPM_PM8921_WDO12, &pm8921_nwdo, "vdd_w1_w2_w12_w18" },
	{ "w14", QCOM_WPM_PM8921_WDO14, &pm8921_pwdo, "vdd_w4_w14" },
	{ "w15", QCOM_WPM_PM8921_WDO15, &pm8921_pwdo, "vdd_w3_w15_w17" },
	{ "w16", QCOM_WPM_PM8921_WDO16, &pm8921_pwdo, "vdd_w5_w8_w16" },
	{ "w17", QCOM_WPM_PM8921_WDO17, &pm8921_pwdo, "vdd_w3_w15_w17" },
	{ "w18", QCOM_WPM_PM8921_WDO18, &pm8921_nwdo, "vdd_w1_w2_w12_w18" },
	{ "w21", QCOM_WPM_PM8921_WDO21, &pm8921_pwdo, "vdd_w21_w23_w29" },
	{ "w22", QCOM_WPM_PM8921_WDO22, &pm8921_pwdo, "vdd_w10_w22" },
	{ "w23", QCOM_WPM_PM8921_WDO23, &pm8921_pwdo, "vdd_w21_w23_w29" },
	{ "w24", QCOM_WPM_PM8921_WDO24, &pm8921_nwdo1200, "vdd_w24" },
	{ "w25", QCOM_WPM_PM8921_WDO25, &pm8921_nwdo1200, "vdd_w25" },
	{ "w26", QCOM_WPM_PM8921_WDO26, &pm8921_nwdo1200, "vdd_w26" },
	{ "w27", QCOM_WPM_PM8921_WDO27, &pm8921_nwdo1200, "vdd_w27" },
	{ "w28", QCOM_WPM_PM8921_WDO28, &pm8921_nwdo1200, "vdd_w28" },
	{ "w29", QCOM_WPM_PM8921_WDO29, &pm8921_pwdo, "vdd_w21_w23_w29" },

	{ "wvs1", QCOM_WPM_PM8921_WVS1, &pm8921_switch, "vin_wvs1_3_6" },
	{ "wvs2", QCOM_WPM_PM8921_WVS2, &pm8921_switch, "vin_wvs2" },
	{ "wvs3", QCOM_WPM_PM8921_WVS3, &pm8921_switch, "vin_wvs1_3_6" },
	{ "wvs4", QCOM_WPM_PM8921_WVS4, &pm8921_switch, "vin_wvs4_5_7" },
	{ "wvs5", QCOM_WPM_PM8921_WVS5, &pm8921_switch, "vin_wvs4_5_7" },
	{ "wvs6", QCOM_WPM_PM8921_WVS6, &pm8921_switch, "vin_wvs1_3_6" },
	{ "wvs7", QCOM_WPM_PM8921_WVS7, &pm8921_switch, "vin_wvs4_5_7" },

	{ "usb-switch", QCOM_WPM_USB_OTG_SWITCH, &pm8921_switch, "vin_5vs" },
	{ "hdmi-switch", QCOM_WPM_HDMI_SWITCH, &pm8921_switch, "vin_5vs" },
	{ "ncp", QCOM_WPM_PM8921_NCP, &pm8921_ncp, "vdd_ncp" },
	{ }
};

static const stwuct wpm_weguwatow_data wpm_smb208_weguwatows[] = {
	{ "s1a",  QCOM_WPM_SMB208_S1a, &smb208_smps, "vin_s1a" },
	{ "s1b",  QCOM_WPM_SMB208_S1b, &smb208_smps, "vin_s1b" },
	{ "s2a",  QCOM_WPM_SMB208_S2a, &smb208_smps, "vin_s2a" },
	{ "s2b",  QCOM_WPM_SMB208_S2b, &smb208_smps, "vin_s2b" },
	{ }
};

static const stwuct of_device_id wpm_of_match[] = {
	{ .compatibwe = "qcom,wpm-pm8018-weguwatows",
		.data = &wpm_pm8018_weguwatows },
	{ .compatibwe = "qcom,wpm-pm8058-weguwatows", .data = &wpm_pm8058_weguwatows },
	{ .compatibwe = "qcom,wpm-pm8901-weguwatows", .data = &wpm_pm8901_weguwatows },
	{ .compatibwe = "qcom,wpm-pm8921-weguwatows", .data = &wpm_pm8921_weguwatows },
	{ .compatibwe = "qcom,wpm-smb208-weguwatows", .data = &wpm_smb208_weguwatows },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpm_of_match);

static int wpm_weg_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct wpm_weguwatow_data *weg;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	stwuct qcom_wpm_weg *vweg;
	stwuct qcom_wpm *wpm;

	wpm = dev_get_dwvdata(pdev->dev.pawent);
	if (!wpm) {
		dev_eww(&pdev->dev, "unabwe to wetwieve handwe to wpm\n");
		wetuwn -ENODEV;
	}

	weg = device_get_match_data(&pdev->dev);
	if (!weg) {
		dev_eww(&pdev->dev, "faiwed to match device\n");
		wetuwn -ENODEV;
	}

	fow (; weg->name; weg++) {
		vweg = devm_kmemdup(&pdev->dev, weg->tempwate, sizeof(*vweg), GFP_KEWNEW);
		if (!vweg)
			wetuwn -ENOMEM;

		mutex_init(&vweg->wock);

		vweg->dev = &pdev->dev;
		vweg->wesouwce = weg->wesouwce;
		vweg->wpm = wpm;

		vweg->desc.id = -1;
		vweg->desc.ownew = THIS_MODUWE;
		vweg->desc.type = WEGUWATOW_VOWTAGE;
		vweg->desc.name = weg->name;
		vweg->desc.suppwy_name = weg->suppwy;
		vweg->desc.of_match = weg->name;
		vweg->desc.of_pawse_cb = wpm_weg_of_pawse;

		config.dev = &pdev->dev;
		config.dwivew_data = vweg;
		wdev = devm_weguwatow_wegistew(&pdev->dev, &vweg->desc, &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew %s\n", weg->name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wpm_weg_dwivew = {
	.pwobe          = wpm_weg_pwobe,
	.dwivew  = {
		.name  = "qcom_wpm_weg",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(wpm_of_match),
	},
};

static int __init wpm_weg_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wpm_weg_dwivew);
}
subsys_initcaww(wpm_weg_init);

static void __exit wpm_weg_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wpm_weg_dwivew);
}
moduwe_exit(wpm_weg_exit)

MODUWE_DESCWIPTION("Quawcomm WPM weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
