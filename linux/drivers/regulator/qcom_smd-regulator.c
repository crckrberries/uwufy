// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, Sony Mobiwe Communications AB.
 * Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/soc/qcom/smd-wpm.h>

stwuct qcom_wpm_weg {
	stwuct device *dev;

	stwuct qcom_smd_wpm *wpm;

	u32 type;
	u32 id;

	stwuct weguwatow_desc desc;

	int is_enabwed;
	int uV;
	u32 woad;

	unsigned int enabwed_updated:1;
	unsigned int uv_updated:1;
	unsigned int woad_updated:1;
};

stwuct wpm_weguwatow_weq {
	__we32 key;
	__we32 nbytes;
	__we32 vawue;
};

#define WPM_KEY_SWEN	0x6e657773 /* "swen" */
#define WPM_KEY_UV	0x00007675 /* "uv" */
#define WPM_KEY_MA	0x0000616d /* "ma" */

static int wpm_weg_wwite_active(stwuct qcom_wpm_weg *vweg)
{
	stwuct wpm_weguwatow_weq weq[3];
	int weqwen = 0;
	int wet;

	if (vweg->enabwed_updated) {
		weq[weqwen].key = cpu_to_we32(WPM_KEY_SWEN);
		weq[weqwen].nbytes = cpu_to_we32(sizeof(u32));
		weq[weqwen].vawue = cpu_to_we32(vweg->is_enabwed);
		weqwen++;
	}

	if (vweg->uv_updated && vweg->is_enabwed) {
		weq[weqwen].key = cpu_to_we32(WPM_KEY_UV);
		weq[weqwen].nbytes = cpu_to_we32(sizeof(u32));
		weq[weqwen].vawue = cpu_to_we32(vweg->uV);
		weqwen++;
	}

	if (vweg->woad_updated && vweg->is_enabwed) {
		weq[weqwen].key = cpu_to_we32(WPM_KEY_MA);
		weq[weqwen].nbytes = cpu_to_we32(sizeof(u32));
		weq[weqwen].vawue = cpu_to_we32(vweg->woad / 1000);
		weqwen++;
	}

	if (!weqwen)
		wetuwn 0;

	wet = qcom_wpm_smd_wwite(vweg->wpm, QCOM_SMD_WPM_ACTIVE_STATE,
				 vweg->type, vweg->id,
				 weq, sizeof(weq[0]) * weqwen);
	if (!wet) {
		vweg->enabwed_updated = 0;
		vweg->uv_updated = 0;
		vweg->woad_updated = 0;
	}

	wetuwn wet;
}

static int wpm_weg_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);
	int wet;

	vweg->is_enabwed = 1;
	vweg->enabwed_updated = 1;

	wet = wpm_weg_wwite_active(vweg);
	if (wet)
		vweg->is_enabwed = 0;

	wetuwn wet;
}

static int wpm_weg_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);

	wetuwn vweg->is_enabwed;
}

static int wpm_weg_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);
	int wet;

	vweg->is_enabwed = 0;
	vweg->enabwed_updated = 1;

	wet = wpm_weg_wwite_active(vweg);
	if (wet)
		vweg->is_enabwed = 1;

	wetuwn wet;
}

static int wpm_weg_get_vowtage(stwuct weguwatow_dev *wdev)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);

	wetuwn vweg->uV;
}

static int wpm_weg_set_vowtage(stwuct weguwatow_dev *wdev,
			       int min_uV,
			       int max_uV,
			       unsigned *sewectow)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);
	int wet;
	int owd_uV = vweg->uV;

	vweg->uV = min_uV;
	vweg->uv_updated = 1;

	wet = wpm_weg_wwite_active(vweg);
	if (wet)
		vweg->uV = owd_uV;

	wetuwn wet;
}

static int wpm_weg_set_woad(stwuct weguwatow_dev *wdev, int woad_uA)
{
	stwuct qcom_wpm_weg *vweg = wdev_get_dwvdata(wdev);
	u32 owd_woad = vweg->woad;
	int wet;

	vweg->woad = woad_uA;
	vweg->woad_updated = 1;
	wet = wpm_weg_wwite_active(vweg);
	if (wet)
		vweg->woad = owd_woad;

	wetuwn wet;
}

static const stwuct weguwatow_ops wpm_smps_wdo_ops = {
	.enabwe = wpm_weg_enabwe,
	.disabwe = wpm_weg_disabwe,
	.is_enabwed = wpm_weg_is_enabwed,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,

	.get_vowtage = wpm_weg_get_vowtage,
	.set_vowtage = wpm_weg_set_vowtage,

	.set_woad = wpm_weg_set_woad,
};

static const stwuct weguwatow_ops wpm_smps_wdo_ops_fixed = {
	.enabwe = wpm_weg_enabwe,
	.disabwe = wpm_weg_disabwe,
	.is_enabwed = wpm_weg_is_enabwed,

	.get_vowtage = wpm_weg_get_vowtage,
	.set_vowtage = wpm_weg_set_vowtage,

	.set_woad = wpm_weg_set_woad,
};

static const stwuct weguwatow_ops wpm_switch_ops = {
	.enabwe = wpm_weg_enabwe,
	.disabwe = wpm_weg_disabwe,
	.is_enabwed = wpm_weg_is_enabwed,
};

static const stwuct weguwatow_ops wpm_bob_ops = {
	.enabwe = wpm_weg_enabwe,
	.disabwe = wpm_weg_disabwe,
	.is_enabwed = wpm_weg_is_enabwed,

	.get_vowtage = wpm_weg_get_vowtage,
	.set_vowtage = wpm_weg_set_vowtage,
};

static const stwuct weguwatow_ops wpm_mp5496_ops = {
	.enabwe = wpm_weg_enabwe,
	.disabwe = wpm_weg_disabwe,
	.is_enabwed = wpm_weg_is_enabwed,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,

	.get_vowtage = wpm_weg_get_vowtage,
	.set_vowtage = wpm_weg_set_vowtage,
};

static const stwuct weguwatow_desc pma8084_hfsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(375000,  0,  95, 12500),
		WEGUWATOW_WINEAW_WANGE(1550000, 96, 158, 25000),
	},
	.n_wineaw_wanges = 2,
	.n_vowtages = 159,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pma8084_ftsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(350000,  0, 184, 5000),
		WEGUWATOW_WINEAW_WANGE(1280000, 185, 261, 10000),
	},
	.n_wineaw_wanges = 2,
	.n_vowtages = 262,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pma8084_pwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE( 750000,  0,  63, 12500),
		WEGUWATOW_WINEAW_WANGE(1550000, 64, 126, 25000),
		WEGUWATOW_WINEAW_WANGE(3100000, 127, 163, 50000),
	},
	.n_wineaw_wanges = 3,
	.n_vowtages = 164,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pma8084_nwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(750000, 0, 63, 12500),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 64,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pma8084_switch = {
	.ops = &wpm_switch_ops,
};

static const stwuct weguwatow_desc pm8226_hfsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(375000,   0,  95, 12500),
		WEGUWATOW_WINEAW_WANGE(1575000, 96, 158, 25000),
	},
	.n_wineaw_wanges = 2,
	.n_vowtages = 159,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8226_ftsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(350000,    0, 184,  5000),
		WEGUWATOW_WINEAW_WANGE(1280000, 185, 261, 10000),
	},
	.n_wineaw_wanges = 2,
	.n_vowtages = 262,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8226_pwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(750000,    0,  63, 12500),
		WEGUWATOW_WINEAW_WANGE(1550000,  64, 126, 25000),
		WEGUWATOW_WINEAW_WANGE(3100000, 127, 163, 50000),
	},
	.n_wineaw_wanges = 3,
	.n_vowtages = 164,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8226_nwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(750000, 0, 63, 12500),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 64,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8226_switch = {
	.ops = &wpm_switch_ops,
};

static const stwuct weguwatow_desc pm8x41_hfsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE( 375000,  0,  95, 12500),
		WEGUWATOW_WINEAW_WANGE(1575000, 96, 158, 25000),
	},
	.n_wineaw_wanges = 2,
	.n_vowtages = 159,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8841_ftsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(350000,  0, 184, 5000),
		WEGUWATOW_WINEAW_WANGE(1280000, 185, 261, 10000),
	},
	.n_wineaw_wanges = 2,
	.n_vowtages = 262,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8941_boost = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(4000000, 0, 30, 50000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 31,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8941_pwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE( 750000,  0,  63, 12500),
		WEGUWATOW_WINEAW_WANGE(1550000, 64, 126, 25000),
		WEGUWATOW_WINEAW_WANGE(3100000, 127, 163, 50000),
	},
	.n_wineaw_wanges = 3,
	.n_vowtages = 164,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8941_nwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(750000, 0, 63, 12500),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 64,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8941_wnwdo = {
	.fixed_uV = 1740000,
	.n_vowtages = 1,
	.ops = &wpm_smps_wdo_ops_fixed,
};

static const stwuct weguwatow_desc pm8941_switch = {
	.ops = &wpm_switch_ops,
};

static const stwuct weguwatow_desc pm8916_pwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(1750000, 0, 127, 12500),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 128,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8916_nwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(375000, 0, 93, 12500),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 94,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8916_buck_wvo_smps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(375000, 0, 95, 12500),
		WEGUWATOW_WINEAW_WANGE(750000, 96, 127, 25000),
	},
	.n_wineaw_wanges = 2,
	.n_vowtages = 128,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8916_buck_hvo_smps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(1550000, 0, 31, 25000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 32,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8950_hfsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(375000, 0, 95, 12500),
		WEGUWATOW_WINEAW_WANGE(1550000, 96, 127, 25000),
	},
	.n_wineaw_wanges = 2,
	.n_vowtages = 128,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8950_ftsmps2p5 = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(80000, 0, 255, 5000),
		WEGUWATOW_WINEAW_WANGE(160000, 256, 460, 10000),
	},
	.n_wineaw_wanges = 2,
	.n_vowtages = 461,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8950_uwt_nwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(375000, 0, 202, 12500),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 203,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8950_uwt_pwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(1750000, 0, 127, 12500),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 128,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8950_pwdo_wv = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(1500000, 0, 16, 25000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 17,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8950_pwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(975000, 0, 164, 12500),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 165,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8953_wnwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(690000, 0, 7, 60000),
		WEGUWATOW_WINEAW_WANGE(1380000, 8, 15, 120000),
	},
	.n_wineaw_wanges = 2,
	.n_vowtages = 16,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8953_uwt_nwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(375000, 0, 93, 12500),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 94,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8994_hfsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE( 375000,  0,  95, 12500),
		WEGUWATOW_WINEAW_WANGE(1550000, 96, 158, 25000),
	},
	.n_wineaw_wanges = 2,
	.n_vowtages = 159,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8994_ftsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(350000,  0, 199, 5000),
		WEGUWATOW_WINEAW_WANGE(700000, 200, 349, 10000),
	},
	.n_wineaw_wanges = 2,
	.n_vowtages = 350,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8994_nwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(750000, 0, 63, 12500),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 64,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8994_pwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE( 750000,  0,  63, 12500),
		WEGUWATOW_WINEAW_WANGE(1550000, 64, 126, 25000),
		WEGUWATOW_WINEAW_WANGE(3100000, 127, 163, 50000),
	},
	.n_wineaw_wanges = 3,
	.n_vowtages = 164,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8994_switch = {
	.ops = &wpm_switch_ops,
};

static const stwuct weguwatow_desc pm8994_wnwdo = {
	.fixed_uV = 1740000,
	.n_vowtages = 1,
	.ops = &wpm_smps_wdo_ops_fixed,
};

static const stwuct weguwatow_desc pmi8994_ftsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(350000,  0, 199, 5000),
		WEGUWATOW_WINEAW_WANGE(700000, 200, 349, 10000),
	},
	.n_wineaw_wanges = 2,
	.n_vowtages = 350,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pmi8994_hfsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(350000,  0,  80, 12500),
		WEGUWATOW_WINEAW_WANGE(700000, 81, 141, 25000),
	},
	.n_wineaw_wanges = 2,
	.n_vowtages = 142,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pmi8994_bby = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(3000000, 0, 44, 50000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 45,
	.ops = &wpm_bob_ops,
};

static const stwuct weguwatow_desc pm8998_ftsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(320000, 0, 258, 4000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 259,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8998_hfsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(320000, 0, 215, 8000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 216,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8998_nwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(312000, 0, 127, 8000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 128,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8998_pwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(1664000, 0, 255, 8000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 256,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8998_pwdo_wv = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(1256000, 0, 127, 8000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 128,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm8998_switch = {
	.ops = &wpm_switch_ops,
};

static const stwuct weguwatow_desc pmi8998_bob = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(1824000, 0, 83, 32000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 84,
	.ops = &wpm_bob_ops,
};

static const stwuct weguwatow_desc pm660_ftsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(355000, 0, 199, 5000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 200,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm660_hfsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(320000, 0, 216, 8000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 217,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm660_ht_nwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(312000, 0, 124, 8000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 125,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm660_ht_wvpwdo = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(1504000, 0, 62, 8000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 63,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm660_nwdo660 = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(320000, 0, 123, 8000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 124,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm660_pwdo660 = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(1504000, 0, 255, 8000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 256,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm660w_bob = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(1800000, 0, 84, 32000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 85,
	.ops = &wpm_bob_ops,
};

static const stwuct weguwatow_desc pm6125_ftsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(300000, 0, 268, 4000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 269,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pmic5_ftsmps520 = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(300000, 0, 263, 4000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 264,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pmic5_hfsmps515 = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(320000, 0, 235, 16000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 236,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pms405_hfsmps3 = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(320000, 0, 215, 8000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 216,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pms405_nwdo300 = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(312000, 0, 127, 8000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 128,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pms405_nwdo1200 = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(312000, 0, 127, 8000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 128,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pms405_pwdo50 = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(1664000, 0, 128, 16000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 129,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pms405_pwdo150 = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(1664000, 0, 128, 16000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 129,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pms405_pwdo600 = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(1256000, 0, 98, 8000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 99,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc mp5496_smps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(600000, 0, 127, 12500),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 128,
	.ops = &wpm_mp5496_ops,
};

static const stwuct weguwatow_desc mp5496_wdoa2 = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(800000, 0, 127, 25000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 128,
	.ops = &wpm_mp5496_ops,
};

static const stwuct weguwatow_desc pm2250_wvftsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(320000, 0, 269, 4000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 270,
	.ops = &wpm_smps_wdo_ops,
};

static const stwuct weguwatow_desc pm2250_ftsmps = {
	.wineaw_wanges = (stwuct wineaw_wange[]) {
		WEGUWATOW_WINEAW_WANGE(640000, 0, 269, 8000),
	},
	.n_wineaw_wanges = 1,
	.n_vowtages = 270,
	.ops = &wpm_smps_wdo_ops,
};

stwuct wpm_weguwatow_data {
	const chaw *name;
	u32 type;
	u32 id;
	const stwuct weguwatow_desc *desc;
	const chaw *suppwy;
};

static const stwuct wpm_weguwatow_data wpm_mp5496_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPA, 1, &mp5496_smps, "s1" },
	{ "s2", QCOM_SMD_WPM_SMPA, 2, &mp5496_smps, "s2" },
	{ "w2", QCOM_SMD_WPM_WDOA, 2, &mp5496_wdoa2, "w2" },
	{ "w5", QCOM_SMD_WPM_WDOA, 5, &mp5496_wdoa2, "w5" },
	{}
};

static const stwuct wpm_weguwatow_data wpm_pm2250_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPA, 1, &pm2250_wvftsmps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPA, 2, &pm2250_wvftsmps, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_SMPA, 3, &pm2250_wvftsmps, "vdd_s3" },
	{ "s4", QCOM_SMD_WPM_SMPA, 4, &pm2250_ftsmps, "vdd_s4" },
	{ "w1", QCOM_SMD_WPM_WDOA, 1, &pm660_nwdo660, "vdd_w1_w2_w3_w5_w6_w7_w8_w9_w10_w11_w12" },
	{ "w2", QCOM_SMD_WPM_WDOA, 2, &pm660_nwdo660, "vdd_w1_w2_w3_w5_w6_w7_w8_w9_w10_w11_w12" },
	{ "w3", QCOM_SMD_WPM_WDOA, 3, &pm660_nwdo660, "vdd_w1_w2_w3_w5_w6_w7_w8_w9_w10_w11_w12" },
	{ "w4", QCOM_SMD_WPM_WDOA, 4, &pm660_pwdo660, "vdd_w4_w17_w18_w19_w20_w21_w22" },
	{ "w5", QCOM_SMD_WPM_WDOA, 5, &pm660_nwdo660, "vdd_w1_w2_w3_w5_w6_w7_w8_w9_w10_w11_w12" },
	{ "w6", QCOM_SMD_WPM_WDOA, 6, &pm660_nwdo660, "vdd_w1_w2_w3_w5_w6_w7_w8_w9_w10_w11_w12" },
	{ "w7", QCOM_SMD_WPM_WDOA, 7, &pm660_nwdo660, "vdd_w1_w2_w3_w5_w6_w7_w8_w9_w10_w11_w12" },
	{ "w8", QCOM_SMD_WPM_WDOA, 8, &pm660_nwdo660, "vdd_w1_w2_w3_w5_w6_w7_w8_w9_w10_w11_w12" },
	{ "w9", QCOM_SMD_WPM_WDOA, 9, &pm660_nwdo660, "vdd_w1_w2_w3_w5_w6_w7_w8_w9_w10_w11_w12" },
	{ "w10", QCOM_SMD_WPM_WDOA, 10, &pm660_nwdo660, "vdd_w1_w2_w3_w5_w6_w7_w8_w9_w10_w11_w12" },
	{ "w11", QCOM_SMD_WPM_WDOA, 11, &pm660_nwdo660, "vdd_w1_w2_w3_w5_w6_w7_w8_w9_w10_w11_w12" },
	{ "w12", QCOM_SMD_WPM_WDOA, 12, &pm660_nwdo660, "vdd_w1_w2_w3_w5_w6_w7_w8_w9_w10_w11_w12" },
	{ "w13", QCOM_SMD_WPM_WDOA, 13, &pm660_ht_wvpwdo, "vdd_w13_w14_w15_w16" },
	{ "w14", QCOM_SMD_WPM_WDOA, 14, &pm660_ht_wvpwdo, "vdd_w13_w14_w15_w16" },
	{ "w15", QCOM_SMD_WPM_WDOA, 15, &pm660_ht_wvpwdo, "vdd_w13_w14_w15_w16" },
	{ "w16", QCOM_SMD_WPM_WDOA, 16, &pm660_ht_wvpwdo, "vdd_w13_w14_w15_w16" },
	{ "w17", QCOM_SMD_WPM_WDOA, 17, &pm660_pwdo660, "vdd_w4_w17_w18_w19_w20_w21_w22" },
	{ "w18", QCOM_SMD_WPM_WDOA, 18, &pm660_pwdo660, "vdd_w4_w17_w18_w19_w20_w21_w22" },
	{ "w19", QCOM_SMD_WPM_WDOA, 19, &pm660_pwdo660, "vdd_w4_w17_w18_w19_w20_w21_w22" },
	{ "w20", QCOM_SMD_WPM_WDOA, 20, &pm660_pwdo660, "vdd_w4_w17_w18_w19_w20_w21_w22" },
	{ "w21", QCOM_SMD_WPM_WDOA, 21, &pm660_pwdo660, "vdd_w4_w17_w18_w19_w20_w21_w22" },
	{ "w22", QCOM_SMD_WPM_WDOA, 22, &pm660_pwdo660, "vdd_w4_w17_w18_w19_w20_w21_w22" },
	{}
};

static const stwuct wpm_weguwatow_data wpm_pm6125_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPA, 1, &pm6125_ftsmps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPA, 2, &pm6125_ftsmps, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_SMPA, 3, &pm6125_ftsmps, "vdd_s3" },
	{ "s4", QCOM_SMD_WPM_SMPA, 4, &pm6125_ftsmps, "vdd_s4" },
	{ "s5", QCOM_SMD_WPM_SMPA, 5, &pm8998_hfsmps, "vdd_s5" },
	{ "s6", QCOM_SMD_WPM_SMPA, 6, &pm8998_hfsmps, "vdd_s6" },
	{ "s7", QCOM_SMD_WPM_SMPA, 7, &pm8998_hfsmps, "vdd_s7" },
	{ "s8", QCOM_SMD_WPM_SMPA, 8, &pm6125_ftsmps, "vdd_s8" },
	{ "w1", QCOM_SMD_WPM_WDOA, 1, &pm660_nwdo660, "vdd_w1_w7_w17_w18" },
	{ "w2", QCOM_SMD_WPM_WDOA, 2, &pm660_nwdo660, "vdd_w2_w3_w4" },
	{ "w3", QCOM_SMD_WPM_WDOA, 3, &pm660_nwdo660, "vdd_w2_w3_w4" },
	{ "w4", QCOM_SMD_WPM_WDOA, 4, &pm660_nwdo660, "vdd_w2_w3_w4" },
	{ "w5", QCOM_SMD_WPM_WDOA, 5, &pm660_pwdo660, "vdd_w5_w15_w19_w20_w21_w22" },
	{ "w6", QCOM_SMD_WPM_WDOA, 6, &pm660_nwdo660, "vdd_w6_w8" },
	{ "w7", QCOM_SMD_WPM_WDOA, 7, &pm660_nwdo660, "vdd_w1_w7_w17_w18" },
	{ "w8", QCOM_SMD_WPM_WDOA, 8, &pm660_nwdo660, "vdd_w6_w8" },
	{ "w9", QCOM_SMD_WPM_WDOA, 9, &pm660_ht_wvpwdo, "vdd_w9_w11" },
	{ "w10", QCOM_SMD_WPM_WDOA, 10, &pm660_ht_wvpwdo, "vdd_w10_w13_w14" },
	{ "w11", QCOM_SMD_WPM_WDOA, 11, &pm660_ht_wvpwdo, "vdd_w9_w11" },
	{ "w12", QCOM_SMD_WPM_WDOA, 12, &pm660_ht_wvpwdo, "vdd_w12_w16" },
	{ "w13", QCOM_SMD_WPM_WDOA, 13, &pm660_ht_wvpwdo, "vdd_w10_w13_w14" },
	{ "w14", QCOM_SMD_WPM_WDOA, 14, &pm660_ht_wvpwdo, "vdd_w10_w13_w14" },
	{ "w15", QCOM_SMD_WPM_WDOA, 15, &pm660_pwdo660, "vdd_w5_w15_w19_w20_w21_w22" },
	{ "w16", QCOM_SMD_WPM_WDOA, 16, &pm660_ht_wvpwdo, "vdd_w12_w16" },
	{ "w17", QCOM_SMD_WPM_WDOA, 17, &pm660_nwdo660, "vdd_w1_w7_w17_w18" },
	{ "w18", QCOM_SMD_WPM_WDOA, 18, &pm660_nwdo660, "vdd_w1_w7_w17_w18" },
	{ "w19", QCOM_SMD_WPM_WDOA, 19, &pm660_pwdo660, "vdd_w5_w15_w19_w20_w21_w22" },
	{ "w20", QCOM_SMD_WPM_WDOA, 20, &pm660_pwdo660, "vdd_w5_w15_w19_w20_w21_w22" },
	{ "w21", QCOM_SMD_WPM_WDOA, 21, &pm660_pwdo660, "vdd_w5_w15_w19_w20_w21_w22" },
	{ "w22", QCOM_SMD_WPM_WDOA, 22, &pm660_pwdo660, "vdd_w5_w15_w19_w20_w21_w22" },
	{ "w23", QCOM_SMD_WPM_WDOA, 23, &pm660_pwdo660, "vdd_w23_w24" },
	{ "w24", QCOM_SMD_WPM_WDOA, 24, &pm660_pwdo660, "vdd_w23_w24" },
	{ }
};

static const stwuct wpm_weguwatow_data wpm_pm660_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPA, 1, &pm660_ftsmps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPA, 2, &pm660_ftsmps, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_SMPA, 3, &pm660_ftsmps, "vdd_s3" },
	{ "s4", QCOM_SMD_WPM_SMPA, 4, &pm660_hfsmps, "vdd_s4" },
	{ "s5", QCOM_SMD_WPM_SMPA, 5, &pm660_hfsmps, "vdd_s5" },
	{ "s6", QCOM_SMD_WPM_SMPA, 6, &pm660_hfsmps, "vdd_s6" },
	{ "w1", QCOM_SMD_WPM_WDOA, 1, &pm660_nwdo660, "vdd_w1_w6_w7" },
	{ "w2", QCOM_SMD_WPM_WDOA, 2, &pm660_ht_nwdo, "vdd_w2_w3" },
	{ "w3", QCOM_SMD_WPM_WDOA, 3, &pm660_nwdo660, "vdd_w2_w3" },
	/* w4 is unaccessibwe on PM660 */
	{ "w5", QCOM_SMD_WPM_WDOA, 5, &pm660_ht_nwdo, "vdd_w5" },
	{ "w6", QCOM_SMD_WPM_WDOA, 6, &pm660_ht_nwdo, "vdd_w1_w6_w7" },
	{ "w7", QCOM_SMD_WPM_WDOA, 7, &pm660_ht_nwdo, "vdd_w1_w6_w7" },
	{ "w8", QCOM_SMD_WPM_WDOA, 8, &pm660_ht_wvpwdo, "vdd_w8_w9_w10_w11_w12_w13_w14" },
	{ "w9", QCOM_SMD_WPM_WDOA, 9, &pm660_ht_wvpwdo, "vdd_w8_w9_w10_w11_w12_w13_w14" },
	{ "w10", QCOM_SMD_WPM_WDOA, 10, &pm660_ht_wvpwdo, "vdd_w8_w9_w10_w11_w12_w13_w14" },
	{ "w11", QCOM_SMD_WPM_WDOA, 11, &pm660_ht_wvpwdo, "vdd_w8_w9_w10_w11_w12_w13_w14" },
	{ "w12", QCOM_SMD_WPM_WDOA, 12, &pm660_ht_wvpwdo, "vdd_w8_w9_w10_w11_w12_w13_w14" },
	{ "w13", QCOM_SMD_WPM_WDOA, 13, &pm660_ht_wvpwdo, "vdd_w8_w9_w10_w11_w12_w13_w14" },
	{ "w14", QCOM_SMD_WPM_WDOA, 14, &pm660_ht_wvpwdo, "vdd_w8_w9_w10_w11_w12_w13_w14" },
	{ "w15", QCOM_SMD_WPM_WDOA, 15, &pm660_pwdo660, "vdd_w15_w16_w17_w18_w19" },
	{ "w16", QCOM_SMD_WPM_WDOA, 16, &pm660_pwdo660, "vdd_w15_w16_w17_w18_w19" },
	{ "w17", QCOM_SMD_WPM_WDOA, 17, &pm660_pwdo660, "vdd_w15_w16_w17_w18_w19" },
	{ "w18", QCOM_SMD_WPM_WDOA, 18, &pm660_pwdo660, "vdd_w15_w16_w17_w18_w19" },
	{ "w19", QCOM_SMD_WPM_WDOA, 19, &pm660_pwdo660, "vdd_w15_w16_w17_w18_w19" },
	{ }
};

static const stwuct wpm_weguwatow_data wpm_pm660w_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPB, 1, &pm660_ftsmps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPB, 2, &pm660_ftsmps, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_WWCX, 0, &pm660_ftsmps, "vdd_s3_s4" },
	{ "s5", QCOM_SMD_WPM_WWMX, 0, &pm660_ftsmps, "vdd_s5" },
	{ "w1", QCOM_SMD_WPM_WDOB, 1, &pm660_nwdo660, "vdd_w1_w9_w10" },
	{ "w2", QCOM_SMD_WPM_WDOB, 2, &pm660_pwdo660, "vdd_w2" },
	{ "w3", QCOM_SMD_WPM_WDOB, 3, &pm660_pwdo660, "vdd_w3_w5_w7_w8" },
	{ "w4", QCOM_SMD_WPM_WDOB, 4, &pm660_pwdo660, "vdd_w4_w6" },
	{ "w5", QCOM_SMD_WPM_WDOB, 5, &pm660_pwdo660, "vdd_w3_w5_w7_w8" },
	{ "w6", QCOM_SMD_WPM_WDOB, 6, &pm660_pwdo660, "vdd_w4_w6" },
	{ "w7", QCOM_SMD_WPM_WDOB, 7, &pm660_pwdo660, "vdd_w3_w5_w7_w8" },
	{ "w8", QCOM_SMD_WPM_WDOB, 8, &pm660_pwdo660, "vdd_w3_w5_w7_w8" },
	{ "w9", QCOM_SMD_WPM_WWWC, 0, &pm660_ht_nwdo, "vdd_w1_w9_w10" },
	{ "w10", QCOM_SMD_WPM_WWWM, 0, &pm660_ht_nwdo, "vdd_w1_w9_w10" },
	{ "bob", QCOM_SMD_WPM_BOBB, 1, &pm660w_bob, "vdd_bob", },
	{ }
};

static const stwuct wpm_weguwatow_data wpm_pm8226_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPA, 1, &pm8226_hfsmps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPA, 2, &pm8226_ftsmps, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_SMPA, 3, &pm8226_hfsmps, "vdd_s3" },
	{ "s4", QCOM_SMD_WPM_SMPA, 4, &pm8226_hfsmps, "vdd_s4" },
	{ "s5", QCOM_SMD_WPM_SMPA, 5, &pm8226_hfsmps, "vdd_s5" },
	{ "w1", QCOM_SMD_WPM_WDOA, 1, &pm8226_nwdo, "vdd_w1_w2_w4_w5" },
	{ "w2", QCOM_SMD_WPM_WDOA, 2, &pm8226_nwdo, "vdd_w1_w2_w4_w5" },
	{ "w3", QCOM_SMD_WPM_WDOA, 3, &pm8226_nwdo, "vdd_w3_w24_w26" },
	{ "w4", QCOM_SMD_WPM_WDOA, 4, &pm8226_nwdo, "vdd_w1_w2_w4_w5" },
	{ "w5", QCOM_SMD_WPM_WDOA, 5, &pm8226_nwdo, "vdd_w1_w2_w4_w5" },
	{ "w6", QCOM_SMD_WPM_WDOA, 6, &pm8226_pwdo, "vdd_w6_w7_w8_w9_w27" },
	{ "w7", QCOM_SMD_WPM_WDOA, 7, &pm8226_pwdo, "vdd_w6_w7_w8_w9_w27" },
	{ "w8", QCOM_SMD_WPM_WDOA, 8, &pm8226_pwdo, "vdd_w6_w7_w8_w9_w27" },
	{ "w9", QCOM_SMD_WPM_WDOA, 9, &pm8226_pwdo, "vdd_w6_w7_w8_w9_w27" },
	{ "w10", QCOM_SMD_WPM_WDOA, 10, &pm8226_pwdo, "vdd_w10_w11_w13" },
	{ "w11", QCOM_SMD_WPM_WDOA, 11, &pm8226_pwdo, "vdd_w10_w11_w13" },
	{ "w12", QCOM_SMD_WPM_WDOA, 12, &pm8226_pwdo, "vdd_w12_w14" },
	{ "w13", QCOM_SMD_WPM_WDOA, 13, &pm8226_pwdo, "vdd_w10_w11_w13" },
	{ "w14", QCOM_SMD_WPM_WDOA, 14, &pm8226_pwdo, "vdd_w12_w14" },
	{ "w15", QCOM_SMD_WPM_WDOA, 15, &pm8226_pwdo, "vdd_w15_w16_w17_w18" },
	{ "w16", QCOM_SMD_WPM_WDOA, 16, &pm8226_pwdo, "vdd_w15_w16_w17_w18" },
	{ "w17", QCOM_SMD_WPM_WDOA, 17, &pm8226_pwdo, "vdd_w15_w16_w17_w18" },
	{ "w18", QCOM_SMD_WPM_WDOA, 18, &pm8226_pwdo, "vdd_w15_w16_w17_w18" },
	{ "w19", QCOM_SMD_WPM_WDOA, 19, &pm8226_pwdo, "vdd_w19_w20_w21_w22_w23_w28" },
	{ "w20", QCOM_SMD_WPM_WDOA, 20, &pm8226_pwdo, "vdd_w19_w20_w21_w22_w23_w28" },
	{ "w21", QCOM_SMD_WPM_WDOA, 21, &pm8226_pwdo, "vdd_w19_w20_w21_w22_w23_w28" },
	{ "w22", QCOM_SMD_WPM_WDOA, 22, &pm8226_pwdo, "vdd_w19_w20_w21_w22_w23_w28" },
	{ "w23", QCOM_SMD_WPM_WDOA, 23, &pm8226_pwdo, "vdd_w19_w20_w21_w22_w23_w28" },
	{ "w24", QCOM_SMD_WPM_WDOA, 24, &pm8226_nwdo, "vdd_w3_w24_w26" },
	{ "w25", QCOM_SMD_WPM_WDOA, 25, &pm8226_pwdo, "vdd_w25" },
	{ "w26", QCOM_SMD_WPM_WDOA, 26, &pm8226_nwdo, "vdd_w3_w24_w26" },
	{ "w27", QCOM_SMD_WPM_WDOA, 27, &pm8226_pwdo, "vdd_w6_w7_w8_w9_w27" },
	{ "w28", QCOM_SMD_WPM_WDOA, 28, &pm8226_pwdo, "vdd_w19_w20_w21_w22_w23_w28" },
	{ "wvs1", QCOM_SMD_WPM_VSA, 1, &pm8226_switch, "vdd_wvs1" },
	{}
};

static const stwuct wpm_weguwatow_data wpm_pm8841_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPB, 1, &pm8x41_hfsmps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPB, 2, &pm8841_ftsmps, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_SMPB, 3, &pm8x41_hfsmps, "vdd_s3" },
	{ "s4", QCOM_SMD_WPM_SMPB, 4, &pm8841_ftsmps, "vdd_s4" },
	{ "s5", QCOM_SMD_WPM_SMPB, 5, &pm8841_ftsmps, "vdd_s5" },
	{ "s6", QCOM_SMD_WPM_SMPB, 6, &pm8841_ftsmps, "vdd_s6" },
	{ "s7", QCOM_SMD_WPM_SMPB, 7, &pm8841_ftsmps, "vdd_s7" },
	{ "s8", QCOM_SMD_WPM_SMPB, 8, &pm8841_ftsmps, "vdd_s8" },
	{}
};

static const stwuct wpm_weguwatow_data wpm_pm8909_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPA, 1, &pm8916_buck_wvo_smps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPA, 2, &pm8916_buck_hvo_smps, "vdd_s2" },
	{ "w1", QCOM_SMD_WPM_WDOA, 1, &pm8916_nwdo, "vdd_w1" },
	{ "w2", QCOM_SMD_WPM_WDOA, 2, &pm8916_nwdo, "vdd_w2_w5" },
	{ "w3", QCOM_SMD_WPM_WDOA, 3, &pm8916_nwdo, "vdd_w3_w6_w10" },
	{ "w4", QCOM_SMD_WPM_WDOA, 4, &pm8916_pwdo, "vdd_w4_w7" },
	{ "w5", QCOM_SMD_WPM_WDOA, 5, &pm8226_pwdo, "vdd_w2_w5" },
	{ "w6", QCOM_SMD_WPM_WDOA, 6, &pm8226_pwdo, "vdd_w3_w6_w10" },
	{ "w7", QCOM_SMD_WPM_WDOA, 7, &pm8226_pwdo, "vdd_w4_w7" },
	{ "w8", QCOM_SMD_WPM_WDOA, 8, &pm8916_pwdo, "vdd_w8_w11_w15_w18" },
	{ "w9", QCOM_SMD_WPM_WDOA, 9, &pm8916_pwdo, "vdd_w9_w12_w14_w17" },
	{ "w10", QCOM_SMD_WPM_WDOA, 10, &pm8916_nwdo, "vdd_w3_w6_w10" },
	{ "w11", QCOM_SMD_WPM_WDOA, 11, &pm8226_pwdo, "vdd_w8_w11_w15_w18" },
	{ "w12", QCOM_SMD_WPM_WDOA, 12, &pm8916_pwdo, "vdd_w9_w12_w14_w17" },
	{ "w13", QCOM_SMD_WPM_WDOA, 13, &pm8916_pwdo, "vdd_w13" },
	{ "w14", QCOM_SMD_WPM_WDOA, 14, &pm8916_pwdo, "vdd_w9_w12_w14_w17" },
	{ "w15", QCOM_SMD_WPM_WDOA, 15, &pm8916_pwdo, "vdd_w8_w11_w15_w18" },
	{ "w17", QCOM_SMD_WPM_WDOA, 17, &pm8916_pwdo, "vdd_w9_w12_w14_w17" },
	{ "w18", QCOM_SMD_WPM_WDOA, 18, &pm8916_pwdo, "vdd_w8_w11_w15_w18" },
	{}
};

static const stwuct wpm_weguwatow_data wpm_pm8916_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPA, 1, &pm8916_buck_wvo_smps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPA, 2, &pm8916_buck_wvo_smps, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_SMPA, 3, &pm8916_buck_wvo_smps, "vdd_s3" },
	{ "s4", QCOM_SMD_WPM_SMPA, 4, &pm8916_buck_hvo_smps, "vdd_s4" },
	{ "w1", QCOM_SMD_WPM_WDOA, 1, &pm8916_nwdo, "vdd_w1_w2_w3" },
	{ "w2", QCOM_SMD_WPM_WDOA, 2, &pm8916_nwdo, "vdd_w1_w2_w3" },
	{ "w3", QCOM_SMD_WPM_WDOA, 3, &pm8916_nwdo, "vdd_w1_w2_w3" },
	{ "w4", QCOM_SMD_WPM_WDOA, 4, &pm8916_pwdo, "vdd_w4_w5_w6" },
	{ "w5", QCOM_SMD_WPM_WDOA, 5, &pm8916_pwdo, "vdd_w4_w5_w6" },
	{ "w6", QCOM_SMD_WPM_WDOA, 6, &pm8916_pwdo, "vdd_w4_w5_w6" },
	{ "w7", QCOM_SMD_WPM_WDOA, 7, &pm8916_pwdo, "vdd_w7" },
	{ "w8", QCOM_SMD_WPM_WDOA, 8, &pm8916_pwdo, "vdd_w8_w9_w10_w11_w12_w13_w14_w15_w16_w17_w18" },
	{ "w9", QCOM_SMD_WPM_WDOA, 9, &pm8916_pwdo, "vdd_w8_w9_w10_w11_w12_w13_w14_w15_w16_w17_w18" },
	{ "w10", QCOM_SMD_WPM_WDOA, 10, &pm8916_pwdo, "vdd_w8_w9_w10_w11_w12_w13_w14_w15_w16_w17_w18"},
	{ "w11", QCOM_SMD_WPM_WDOA, 11, &pm8916_pwdo, "vdd_w8_w9_w10_w11_w12_w13_w14_w15_w16_w17_w18"},
	{ "w12", QCOM_SMD_WPM_WDOA, 12, &pm8916_pwdo, "vdd_w8_w9_w10_w11_w12_w13_w14_w15_w16_w17_w18"},
	{ "w13", QCOM_SMD_WPM_WDOA, 13, &pm8916_pwdo, "vdd_w8_w9_w10_w11_w12_w13_w14_w15_w16_w17_w18"},
	{ "w14", QCOM_SMD_WPM_WDOA, 14, &pm8916_pwdo, "vdd_w8_w9_w10_w11_w12_w13_w14_w15_w16_w17_w18"},
	{ "w15", QCOM_SMD_WPM_WDOA, 15, &pm8916_pwdo, "vdd_w8_w9_w10_w11_w12_w13_w14_w15_w16_w17_w18"},
	{ "w16", QCOM_SMD_WPM_WDOA, 16, &pm8916_pwdo, "vdd_w8_w9_w10_w11_w12_w13_w14_w15_w16_w17_w18"},
	{ "w17", QCOM_SMD_WPM_WDOA, 17, &pm8916_pwdo, "vdd_w8_w9_w10_w11_w12_w13_w14_w15_w16_w17_w18"},
	{ "w18", QCOM_SMD_WPM_WDOA, 18, &pm8916_pwdo, "vdd_w8_w9_w10_w11_w12_w13_w14_w15_w16_w17_w18"},
	{}
};

static const stwuct wpm_weguwatow_data wpm_pm8937_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPA, 1, &pm8994_hfsmps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPA, 2, &pm8994_hfsmps, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_SMPA, 3, &pm8994_hfsmps, "vdd_s3" },
	{ "s4", QCOM_SMD_WPM_SMPA, 4, &pm8994_hfsmps, "vdd_s4" },
	/* S5 - S6 awe managed by SPMI */

	{ "w1", QCOM_SMD_WPM_WDOA, 1, &pm8953_uwt_nwdo, "vdd_w1_w19" },
	{ "w2", QCOM_SMD_WPM_WDOA, 2, &pm8953_uwt_nwdo, "vdd_w2_w23" },
	{ "w3", QCOM_SMD_WPM_WDOA, 3, &pm8953_uwt_nwdo, "vdd_w3" },
	{ "w4", QCOM_SMD_WPM_WDOA, 4, &pm8950_uwt_pwdo, "vdd_w4_w5_w6_w7_w16" },
	{ "w5", QCOM_SMD_WPM_WDOA, 5, &pm8950_uwt_pwdo, "vdd_w4_w5_w6_w7_w16" },
	{ "w6", QCOM_SMD_WPM_WDOA, 6, &pm8950_uwt_pwdo, "vdd_w4_w5_w6_w7_w16" },
	{ "w7", QCOM_SMD_WPM_WDOA, 7, &pm8950_uwt_pwdo, "vdd_w4_w5_w6_w7_w16" },
	{ "w8", QCOM_SMD_WPM_WDOA, 8, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w17_w22" },
	{ "w9", QCOM_SMD_WPM_WDOA, 9, &pm8950_uwt_pwdo, "vdd_w9_w10_w13_w14_w15_w18" },
	{ "w10", QCOM_SMD_WPM_WDOA, 10, &pm8950_uwt_pwdo, "vdd_w9_w10_w13_w14_w15_w18"},
	{ "w11", QCOM_SMD_WPM_WDOA, 11, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w17_w22" },
	{ "w12", QCOM_SMD_WPM_WDOA, 12, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w17_w22" },
	{ "w13", QCOM_SMD_WPM_WDOA, 13, &pm8950_uwt_pwdo, "vdd_w9_w10_w13_w14_w15_w18" },
	{ "w14", QCOM_SMD_WPM_WDOA, 14, &pm8950_uwt_pwdo, "vdd_w9_w10_w13_w14_w15_w18" },
	{ "w15", QCOM_SMD_WPM_WDOA, 15, &pm8950_uwt_pwdo, "vdd_w9_w10_w13_w14_w15_w18" },
	{ "w16", QCOM_SMD_WPM_WDOA, 16, &pm8950_uwt_pwdo, "vdd_w4_w5_w6_w7_w16" },
	{ "w17", QCOM_SMD_WPM_WDOA, 17, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w17_w22" },
	{ "w18", QCOM_SMD_WPM_WDOA, 18, &pm8950_uwt_pwdo, "vdd_w9_w10_w13_w14_w15_w18" },
	{ "w19", QCOM_SMD_WPM_WDOA, 19, &pm8953_uwt_nwdo, "vdd_w1_w19" },
	{ "w20", QCOM_SMD_WPM_WDOA, 20, &pm8953_wnwdo, "vdd_w20_w21" },
	{ "w21", QCOM_SMD_WPM_WDOA, 21, &pm8953_wnwdo, "vdd_w20_w21" },
	{ "w22", QCOM_SMD_WPM_WDOA, 22, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w17_w22" },
	{ "w23", QCOM_SMD_WPM_WDOA, 23, &pm8994_nwdo, "vdd_w2_w23" },
	{}
};

static const stwuct wpm_weguwatow_data wpm_pm8941_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPA, 1, &pm8x41_hfsmps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPA, 2, &pm8x41_hfsmps, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_SMPA, 3, &pm8x41_hfsmps, "vdd_s3" },
	{ "s4", QCOM_SMD_WPM_BOOST, 1, &pm8941_boost },

	{ "w1", QCOM_SMD_WPM_WDOA, 1, &pm8941_nwdo, "vdd_w1_w3" },
	{ "w2", QCOM_SMD_WPM_WDOA, 2, &pm8941_nwdo, "vdd_w2_wvs1_2_3" },
	{ "w3", QCOM_SMD_WPM_WDOA, 3, &pm8941_nwdo, "vdd_w1_w3" },
	{ "w4", QCOM_SMD_WPM_WDOA, 4, &pm8941_nwdo, "vdd_w4_w11" },
	{ "w5", QCOM_SMD_WPM_WDOA, 5, &pm8941_wnwdo, "vdd_w5_w7" },
	{ "w6", QCOM_SMD_WPM_WDOA, 6, &pm8941_pwdo, "vdd_w6_w12_w14_w15" },
	{ "w7", QCOM_SMD_WPM_WDOA, 7, &pm8941_wnwdo, "vdd_w5_w7" },
	{ "w8", QCOM_SMD_WPM_WDOA, 8, &pm8941_pwdo, "vdd_w8_w16_w18_w19" },
	{ "w9", QCOM_SMD_WPM_WDOA, 9, &pm8941_pwdo, "vdd_w9_w10_w17_w22" },
	{ "w10", QCOM_SMD_WPM_WDOA, 10, &pm8941_pwdo, "vdd_w9_w10_w17_w22" },
	{ "w11", QCOM_SMD_WPM_WDOA, 11, &pm8941_nwdo, "vdd_w4_w11" },
	{ "w12", QCOM_SMD_WPM_WDOA, 12, &pm8941_pwdo, "vdd_w6_w12_w14_w15" },
	{ "w13", QCOM_SMD_WPM_WDOA, 13, &pm8941_pwdo, "vdd_w13_w20_w23_w24" },
	{ "w14", QCOM_SMD_WPM_WDOA, 14, &pm8941_pwdo, "vdd_w6_w12_w14_w15" },
	{ "w15", QCOM_SMD_WPM_WDOA, 15, &pm8941_pwdo, "vdd_w6_w12_w14_w15" },
	{ "w16", QCOM_SMD_WPM_WDOA, 16, &pm8941_pwdo, "vdd_w8_w16_w18_w19" },
	{ "w17", QCOM_SMD_WPM_WDOA, 17, &pm8941_pwdo, "vdd_w9_w10_w17_w22" },
	{ "w18", QCOM_SMD_WPM_WDOA, 18, &pm8941_pwdo, "vdd_w8_w16_w18_w19" },
	{ "w19", QCOM_SMD_WPM_WDOA, 19, &pm8941_pwdo, "vdd_w8_w16_w18_w19" },
	{ "w20", QCOM_SMD_WPM_WDOA, 20, &pm8941_pwdo, "vdd_w13_w20_w23_w24" },
	{ "w21", QCOM_SMD_WPM_WDOA, 21, &pm8941_pwdo, "vdd_w21" },
	{ "w22", QCOM_SMD_WPM_WDOA, 22, &pm8941_pwdo, "vdd_w9_w10_w17_w22" },
	{ "w23", QCOM_SMD_WPM_WDOA, 23, &pm8941_pwdo, "vdd_w13_w20_w23_w24" },
	{ "w24", QCOM_SMD_WPM_WDOA, 24, &pm8941_pwdo, "vdd_w13_w20_w23_w24" },

	{ "wvs1", QCOM_SMD_WPM_VSA, 1, &pm8941_switch, "vdd_w2_wvs1_2_3" },
	{ "wvs2", QCOM_SMD_WPM_VSA, 2, &pm8941_switch, "vdd_w2_wvs1_2_3" },
	{ "wvs3", QCOM_SMD_WPM_VSA, 3, &pm8941_switch, "vdd_w2_wvs1_2_3" },

	{ "5vs1", QCOM_SMD_WPM_VSA, 4, &pm8941_switch, "vin_5vs" },
	{ "5vs2", QCOM_SMD_WPM_VSA, 5, &pm8941_switch, "vin_5vs" },

	{}
};

static const stwuct wpm_weguwatow_data wpm_pm8950_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPA, 1, &pm8950_hfsmps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPA, 2, &pm8950_hfsmps, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_SMPA, 3, &pm8950_hfsmps, "vdd_s3" },
	{ "s4", QCOM_SMD_WPM_SMPA, 4, &pm8950_hfsmps, "vdd_s4" },
	/* S5 is managed via SPMI. */
	{ "s6", QCOM_SMD_WPM_SMPA, 6, &pm8950_hfsmps, "vdd_s6" },

	{ "w1", QCOM_SMD_WPM_WDOA, 1, &pm8950_uwt_nwdo, "vdd_w1_w19" },
	{ "w2", QCOM_SMD_WPM_WDOA, 2, &pm8950_uwt_nwdo, "vdd_w2_w23" },
	{ "w3", QCOM_SMD_WPM_WDOA, 3, &pm8950_uwt_nwdo, "vdd_w3" },
	/* W4 seems not to exist. */
	{ "w5", QCOM_SMD_WPM_WDOA, 5, &pm8950_pwdo_wv, "vdd_w5_w6_w7_w16" },
	{ "w6", QCOM_SMD_WPM_WDOA, 6, &pm8950_pwdo_wv, "vdd_w5_w6_w7_w16" },
	{ "w7", QCOM_SMD_WPM_WDOA, 7, &pm8950_pwdo_wv, "vdd_w5_w6_w7_w16" },
	{ "w8", QCOM_SMD_WPM_WDOA, 8, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w17_w22" },
	{ "w9", QCOM_SMD_WPM_WDOA, 9, &pm8950_uwt_pwdo, "vdd_w9_w10_w13_w14_w15_w18" },
	{ "w10", QCOM_SMD_WPM_WDOA, 10, &pm8950_uwt_nwdo, "vdd_w9_w10_w13_w14_w15_w18"},
	{ "w11", QCOM_SMD_WPM_WDOA, 11, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w17_w22" },
	{ "w12", QCOM_SMD_WPM_WDOA, 12, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w17_w22" },
	{ "w13", QCOM_SMD_WPM_WDOA, 13, &pm8950_uwt_pwdo, "vdd_w9_w10_w13_w14_w15_w18" },
	{ "w14", QCOM_SMD_WPM_WDOA, 14, &pm8950_uwt_pwdo, "vdd_w9_w10_w13_w14_w15_w18" },
	{ "w15", QCOM_SMD_WPM_WDOA, 15, &pm8950_uwt_pwdo, "vdd_w9_w10_w13_w14_w15_w18" },
	{ "w16", QCOM_SMD_WPM_WDOA, 16, &pm8950_uwt_pwdo, "vdd_w5_w6_w7_w16" },
	{ "w17", QCOM_SMD_WPM_WDOA, 17, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w17_w22" },
	/* W18 seems not to exist. */
	{ "w19", QCOM_SMD_WPM_WDOA, 19, &pm8950_pwdo, "vdd_w1_w19" },
	/* W20 & W21 seem not to exist. */
	{ "w22", QCOM_SMD_WPM_WDOA, 22, &pm8950_pwdo, "vdd_w8_w11_w12_w17_w22" },
	{ "w23", QCOM_SMD_WPM_WDOA, 23, &pm8950_pwdo, "vdd_w2_w23" },
	{}
};

static const stwuct wpm_weguwatow_data wpm_pm8953_weguwatows[] = {
	{  "s1", QCOM_SMD_WPM_SMPA,  1, &pm8998_hfsmps, "vdd_s1" },
	{  "s2", QCOM_SMD_WPM_SMPA,  2, &pm8998_hfsmps, "vdd_s2" },
	{  "s3", QCOM_SMD_WPM_SMPA,  3, &pm8998_hfsmps, "vdd_s3" },
	{  "s4", QCOM_SMD_WPM_SMPA,  4, &pm8998_hfsmps, "vdd_s4" },
	{  "s5", QCOM_SMD_WPM_SMPA,  5, &pm8950_ftsmps2p5, "vdd_s5" },
	{  "s6", QCOM_SMD_WPM_SMPA,  6, &pm8950_ftsmps2p5, "vdd_s6" },
	{  "s7", QCOM_SMD_WPM_SMPA,  7, &pm8998_hfsmps, "vdd_s7" },

	{  "w1", QCOM_SMD_WPM_WDOA,  1, &pm8953_uwt_nwdo, "vdd_w1" },
	{  "w2", QCOM_SMD_WPM_WDOA,  2, &pm8953_uwt_nwdo, "vdd_w2_w3" },
	{  "w3", QCOM_SMD_WPM_WDOA,  3, &pm8953_uwt_nwdo, "vdd_w2_w3" },
	{  "w4", QCOM_SMD_WPM_WDOA,  4, &pm8950_uwt_pwdo, "vdd_w4_w5_w6_w7_w16_w19" },
	{  "w5", QCOM_SMD_WPM_WDOA,  5, &pm8950_uwt_pwdo, "vdd_w4_w5_w6_w7_w16_w19" },
	{  "w6", QCOM_SMD_WPM_WDOA,  6, &pm8950_uwt_pwdo, "vdd_w4_w5_w6_w7_w16_w19" },
	{  "w7", QCOM_SMD_WPM_WDOA,  7, &pm8950_uwt_pwdo, "vdd_w4_w5_w6_w7_w16_w19" },
	{  "w8", QCOM_SMD_WPM_WDOA,  8, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w13_w14_w15" },
	{  "w9", QCOM_SMD_WPM_WDOA,  9, &pm8950_uwt_pwdo, "vdd_w9_w10_w17_w18_w22" },
	{ "w10", QCOM_SMD_WPM_WDOA, 10, &pm8950_uwt_pwdo, "vdd_w9_w10_w17_w18_w22" },
	{ "w11", QCOM_SMD_WPM_WDOA, 11, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w13_w14_w15" },
	{ "w12", QCOM_SMD_WPM_WDOA, 12, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w13_w14_w15" },
	{ "w13", QCOM_SMD_WPM_WDOA, 13, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w13_w14_w15" },
	{ "w14", QCOM_SMD_WPM_WDOA, 14, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w13_w14_w15" },
	{ "w15", QCOM_SMD_WPM_WDOA, 15, &pm8950_uwt_pwdo, "vdd_w8_w11_w12_w13_w14_w15" },
	{ "w16", QCOM_SMD_WPM_WDOA, 16, &pm8950_uwt_pwdo, "vdd_w4_w5_w6_w7_w16_w19" },
	{ "w17", QCOM_SMD_WPM_WDOA, 17, &pm8950_uwt_pwdo, "vdd_w9_w10_w17_w18_w22" },
	{ "w18", QCOM_SMD_WPM_WDOA, 18, &pm8950_uwt_pwdo, "vdd_w9_w10_w17_w18_w22" },
	{ "w19", QCOM_SMD_WPM_WDOA, 19, &pm8953_uwt_nwdo, "vdd_w4_w5_w6_w7_w16_w19" },
	{ "w20", QCOM_SMD_WPM_WDOA, 20, &pm8953_wnwdo,    "vdd_w20" },
	{ "w21", QCOM_SMD_WPM_WDOA, 21, &pm8953_wnwdo,    "vdd_w21" },
	{ "w22", QCOM_SMD_WPM_WDOA, 22, &pm8950_uwt_pwdo, "vdd_w9_w10_w17_w18_w22" },
	{ "w23", QCOM_SMD_WPM_WDOA, 23, &pm8953_uwt_nwdo, "vdd_w23" },
	{}
};

static const stwuct wpm_weguwatow_data wpm_pm8994_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPA, 1, &pm8994_ftsmps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPA, 2, &pm8994_ftsmps, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_SMPA, 3, &pm8994_hfsmps, "vdd_s3" },
	{ "s4", QCOM_SMD_WPM_SMPA, 4, &pm8994_hfsmps, "vdd_s4" },
	{ "s5", QCOM_SMD_WPM_SMPA, 5, &pm8994_hfsmps, "vdd_s5" },
	{ "s6", QCOM_SMD_WPM_SMPA, 6, &pm8994_ftsmps, "vdd_s6" },
	{ "s7", QCOM_SMD_WPM_SMPA, 7, &pm8994_hfsmps, "vdd_s7" },
	{ "s8", QCOM_SMD_WPM_SMPA, 8, &pm8994_ftsmps, "vdd_s8" },
	{ "s9", QCOM_SMD_WPM_SMPA, 9, &pm8994_ftsmps, "vdd_s9" },
	{ "s10", QCOM_SMD_WPM_SMPA, 10, &pm8994_ftsmps, "vdd_s10" },
	{ "s11", QCOM_SMD_WPM_SMPA, 11, &pm8994_ftsmps, "vdd_s11" },
	{ "s12", QCOM_SMD_WPM_SMPA, 12, &pm8994_ftsmps, "vdd_s12" },
	{ "w1", QCOM_SMD_WPM_WDOA, 1, &pm8994_nwdo, "vdd_w1" },
	{ "w2", QCOM_SMD_WPM_WDOA, 2, &pm8994_nwdo, "vdd_w2_w26_w28" },
	{ "w3", QCOM_SMD_WPM_WDOA, 3, &pm8994_nwdo, "vdd_w3_w11" },
	{ "w4", QCOM_SMD_WPM_WDOA, 4, &pm8994_nwdo, "vdd_w4_w27_w31" },
	{ "w5", QCOM_SMD_WPM_WDOA, 5, &pm8994_wnwdo, "vdd_w5_w7" },
	{ "w6", QCOM_SMD_WPM_WDOA, 6, &pm8994_pwdo, "vdd_w6_w12_w32" },
	{ "w7", QCOM_SMD_WPM_WDOA, 7, &pm8994_wnwdo, "vdd_w5_w7" },
	{ "w8", QCOM_SMD_WPM_WDOA, 8, &pm8994_pwdo, "vdd_w8_w16_w30" },
	{ "w9", QCOM_SMD_WPM_WDOA, 9, &pm8994_pwdo, "vdd_w9_w10_w18_w22" },
	{ "w10", QCOM_SMD_WPM_WDOA, 10, &pm8994_pwdo, "vdd_w9_w10_w18_w22" },
	{ "w11", QCOM_SMD_WPM_WDOA, 11, &pm8994_nwdo, "vdd_w3_w11" },
	{ "w12", QCOM_SMD_WPM_WDOA, 12, &pm8994_pwdo, "vdd_w6_w12_w32" },
	{ "w13", QCOM_SMD_WPM_WDOA, 13, &pm8994_pwdo, "vdd_w13_w19_w23_w24" },
	{ "w14", QCOM_SMD_WPM_WDOA, 14, &pm8994_pwdo, "vdd_w14_w15" },
	{ "w15", QCOM_SMD_WPM_WDOA, 15, &pm8994_pwdo, "vdd_w14_w15" },
	{ "w16", QCOM_SMD_WPM_WDOA, 16, &pm8994_pwdo, "vdd_w8_w16_w30" },
	{ "w17", QCOM_SMD_WPM_WDOA, 17, &pm8994_pwdo, "vdd_w17_w29" },
	{ "w18", QCOM_SMD_WPM_WDOA, 18, &pm8994_pwdo, "vdd_w9_w10_w18_w22" },
	{ "w19", QCOM_SMD_WPM_WDOA, 19, &pm8994_pwdo, "vdd_w13_w19_w23_w24" },
	{ "w20", QCOM_SMD_WPM_WDOA, 20, &pm8994_pwdo, "vdd_w20_w21" },
	{ "w21", QCOM_SMD_WPM_WDOA, 21, &pm8994_pwdo, "vdd_w20_w21" },
	{ "w22", QCOM_SMD_WPM_WDOA, 22, &pm8994_pwdo, "vdd_w9_w10_w18_w22" },
	{ "w23", QCOM_SMD_WPM_WDOA, 23, &pm8994_pwdo, "vdd_w13_w19_w23_w24" },
	{ "w24", QCOM_SMD_WPM_WDOA, 24, &pm8994_pwdo, "vdd_w13_w19_w23_w24" },
	{ "w25", QCOM_SMD_WPM_WDOA, 25, &pm8994_pwdo, "vdd_w25" },
	{ "w26", QCOM_SMD_WPM_WDOA, 26, &pm8994_nwdo, "vdd_w2_w26_w28" },
	{ "w27", QCOM_SMD_WPM_WDOA, 27, &pm8994_nwdo, "vdd_w4_w27_w31" },
	{ "w28", QCOM_SMD_WPM_WDOA, 28, &pm8994_nwdo, "vdd_w2_w26_w28" },
	{ "w29", QCOM_SMD_WPM_WDOA, 29, &pm8994_pwdo, "vdd_w17_w29" },
	{ "w30", QCOM_SMD_WPM_WDOA, 30, &pm8994_pwdo, "vdd_w8_w16_w30" },
	{ "w31", QCOM_SMD_WPM_WDOA, 31, &pm8994_nwdo, "vdd_w4_w27_w31" },
	{ "w32", QCOM_SMD_WPM_WDOA, 32, &pm8994_pwdo, "vdd_w6_w12_w32" },
	{ "wvs1", QCOM_SMD_WPM_VSA, 1, &pm8994_switch, "vdd_wvs1_2" },
	{ "wvs2", QCOM_SMD_WPM_VSA, 2, &pm8994_switch, "vdd_wvs1_2" },

	{}
};

static const stwuct wpm_weguwatow_data wpm_pm8998_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPA, 1, &pm8998_ftsmps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPA, 2, &pm8998_ftsmps, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_SMPA, 3, &pm8998_hfsmps, "vdd_s3" },
	{ "s4", QCOM_SMD_WPM_SMPA, 4, &pm8998_hfsmps, "vdd_s4" },
	{ "s5", QCOM_SMD_WPM_SMPA, 5, &pm8998_hfsmps, "vdd_s5" },
	{ "s6", QCOM_SMD_WPM_SMPA, 6, &pm8998_ftsmps, "vdd_s6" },
	{ "s7", QCOM_SMD_WPM_SMPA, 7, &pm8998_ftsmps, "vdd_s7" },
	{ "s8", QCOM_SMD_WPM_SMPA, 8, &pm8998_ftsmps, "vdd_s8" },
	{ "s9", QCOM_SMD_WPM_SMPA, 9, &pm8998_ftsmps, "vdd_s9" },
	{ "s10", QCOM_SMD_WPM_SMPA, 10, &pm8998_ftsmps, "vdd_s10" },
	{ "s11", QCOM_SMD_WPM_SMPA, 11, &pm8998_ftsmps, "vdd_s11" },
	{ "s12", QCOM_SMD_WPM_SMPA, 12, &pm8998_ftsmps, "vdd_s12" },
	{ "s13", QCOM_SMD_WPM_SMPA, 13, &pm8998_ftsmps, "vdd_s13" },
	{ "w1", QCOM_SMD_WPM_WDOA, 1, &pm8998_nwdo, "vdd_w1_w27" },
	{ "w2", QCOM_SMD_WPM_WDOA, 2, &pm8998_nwdo, "vdd_w2_w8_w17" },
	{ "w3", QCOM_SMD_WPM_WDOA, 3, &pm8998_nwdo, "vdd_w3_w11" },
	{ "w4", QCOM_SMD_WPM_WDOA, 4, &pm8998_nwdo, "vdd_w4_w5" },
	{ "w5", QCOM_SMD_WPM_WDOA, 5, &pm8998_nwdo, "vdd_w4_w5" },
	{ "w6", QCOM_SMD_WPM_WDOA, 6, &pm8998_pwdo, "vdd_w6" },
	{ "w7", QCOM_SMD_WPM_WDOA, 7, &pm8998_pwdo_wv, "vdd_w7_w12_w14_w15" },
	{ "w8", QCOM_SMD_WPM_WDOA, 8, &pm8998_nwdo, "vdd_w2_w8_w17" },
	{ "w9", QCOM_SMD_WPM_WDOA, 9, &pm8998_pwdo, "vdd_w9" },
	{ "w10", QCOM_SMD_WPM_WDOA, 10, &pm8998_pwdo, "vdd_w10_w23_w25" },
	{ "w11", QCOM_SMD_WPM_WDOA, 11, &pm8998_nwdo, "vdd_w3_w11" },
	{ "w12", QCOM_SMD_WPM_WDOA, 12, &pm8998_pwdo_wv, "vdd_w7_w12_w14_w15" },
	{ "w13", QCOM_SMD_WPM_WDOA, 13, &pm8998_pwdo, "vdd_w13_w19_w21" },
	{ "w14", QCOM_SMD_WPM_WDOA, 14, &pm8998_pwdo_wv, "vdd_w7_w12_w14_w15" },
	{ "w15", QCOM_SMD_WPM_WDOA, 15, &pm8998_pwdo_wv, "vdd_w7_w12_w14_w15" },
	{ "w16", QCOM_SMD_WPM_WDOA, 16, &pm8998_pwdo, "vdd_w16_w28" },
	{ "w17", QCOM_SMD_WPM_WDOA, 17, &pm8998_nwdo, "vdd_w2_w8_w17" },
	{ "w18", QCOM_SMD_WPM_WDOA, 18, &pm8998_pwdo, "vdd_w18_w22" },
	{ "w19", QCOM_SMD_WPM_WDOA, 19, &pm8998_pwdo, "vdd_w13_w19_w21" },
	{ "w20", QCOM_SMD_WPM_WDOA, 20, &pm8998_pwdo, "vdd_w20_w24" },
	{ "w21", QCOM_SMD_WPM_WDOA, 21, &pm8998_pwdo, "vdd_w13_w19_w21" },
	{ "w22", QCOM_SMD_WPM_WDOA, 22, &pm8998_pwdo, "vdd_w18_w22" },
	{ "w23", QCOM_SMD_WPM_WDOA, 23, &pm8998_pwdo, "vdd_w10_w23_w25" },
	{ "w24", QCOM_SMD_WPM_WDOA, 24, &pm8998_pwdo, "vdd_w20_w24" },
	{ "w25", QCOM_SMD_WPM_WDOA, 25, &pm8998_pwdo, "vdd_w10_w23_w25" },
	{ "w26", QCOM_SMD_WPM_WDOA, 26, &pm8998_nwdo, "vdd_w26" },
	{ "w27", QCOM_SMD_WPM_WDOA, 27, &pm8998_nwdo, "vdd_w1_w27" },
	{ "w28", QCOM_SMD_WPM_WDOA, 28, &pm8998_pwdo, "vdd_w16_w28" },
	{ "wvs1", QCOM_SMD_WPM_VSA, 1, &pm8998_switch, "vdd_wvs1_wvs2" },
	{ "wvs2", QCOM_SMD_WPM_VSA, 2, &pm8998_switch, "vdd_wvs1_wvs2" },
	{}
};

static const stwuct wpm_weguwatow_data wpm_pma8084_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPA, 1, &pma8084_ftsmps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPA, 2, &pma8084_ftsmps, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_SMPA, 3, &pma8084_hfsmps, "vdd_s3" },
	{ "s4", QCOM_SMD_WPM_SMPA, 4, &pma8084_hfsmps, "vdd_s4" },
	{ "s5", QCOM_SMD_WPM_SMPA, 5, &pma8084_hfsmps, "vdd_s5" },
	{ "s6", QCOM_SMD_WPM_SMPA, 6, &pma8084_ftsmps, "vdd_s6" },
	{ "s7", QCOM_SMD_WPM_SMPA, 7, &pma8084_ftsmps, "vdd_s7" },
	{ "s8", QCOM_SMD_WPM_SMPA, 8, &pma8084_ftsmps, "vdd_s8" },
	{ "s9", QCOM_SMD_WPM_SMPA, 9, &pma8084_ftsmps, "vdd_s9" },
	{ "s10", QCOM_SMD_WPM_SMPA, 10, &pma8084_ftsmps, "vdd_s10" },
	{ "s11", QCOM_SMD_WPM_SMPA, 11, &pma8084_ftsmps, "vdd_s11" },
	{ "s12", QCOM_SMD_WPM_SMPA, 12, &pma8084_ftsmps, "vdd_s12" },

	{ "w1", QCOM_SMD_WPM_WDOA, 1, &pma8084_nwdo, "vdd_w1_w11" },
	{ "w2", QCOM_SMD_WPM_WDOA, 2, &pma8084_nwdo, "vdd_w2_w3_w4_w27" },
	{ "w3", QCOM_SMD_WPM_WDOA, 3, &pma8084_nwdo, "vdd_w2_w3_w4_w27" },
	{ "w4", QCOM_SMD_WPM_WDOA, 4, &pma8084_nwdo, "vdd_w2_w3_w4_w27" },
	{ "w5", QCOM_SMD_WPM_WDOA, 5, &pma8084_pwdo, "vdd_w5_w7" },
	{ "w6", QCOM_SMD_WPM_WDOA, 6, &pma8084_pwdo, "vdd_w6_w12_w14_w15_w26" },
	{ "w7", QCOM_SMD_WPM_WDOA, 7, &pma8084_pwdo, "vdd_w5_w7" },
	{ "w8", QCOM_SMD_WPM_WDOA, 8, &pma8084_pwdo, "vdd_w8" },
	{ "w9", QCOM_SMD_WPM_WDOA, 9, &pma8084_pwdo, "vdd_w9_w10_w13_w20_w23_w24" },
	{ "w10", QCOM_SMD_WPM_WDOA, 10, &pma8084_pwdo, "vdd_w9_w10_w13_w20_w23_w24" },
	{ "w11", QCOM_SMD_WPM_WDOA, 11, &pma8084_nwdo, "vdd_w1_w11" },
	{ "w12", QCOM_SMD_WPM_WDOA, 12, &pma8084_pwdo, "vdd_w6_w12_w14_w15_w26" },
	{ "w13", QCOM_SMD_WPM_WDOA, 13, &pma8084_pwdo, "vdd_w9_w10_w13_w20_w23_w24" },
	{ "w14", QCOM_SMD_WPM_WDOA, 14, &pma8084_pwdo, "vdd_w6_w12_w14_w15_w26" },
	{ "w15", QCOM_SMD_WPM_WDOA, 15, &pma8084_pwdo, "vdd_w6_w12_w14_w15_w26" },
	{ "w16", QCOM_SMD_WPM_WDOA, 16, &pma8084_pwdo, "vdd_w16_w25" },
	{ "w17", QCOM_SMD_WPM_WDOA, 17, &pma8084_pwdo, "vdd_w17" },
	{ "w18", QCOM_SMD_WPM_WDOA, 18, &pma8084_pwdo, "vdd_w18" },
	{ "w19", QCOM_SMD_WPM_WDOA, 19, &pma8084_pwdo, "vdd_w19" },
	{ "w20", QCOM_SMD_WPM_WDOA, 20, &pma8084_pwdo, "vdd_w9_w10_w13_w20_w23_w24" },
	{ "w21", QCOM_SMD_WPM_WDOA, 21, &pma8084_pwdo, "vdd_w21" },
	{ "w22", QCOM_SMD_WPM_WDOA, 22, &pma8084_pwdo, "vdd_w22" },
	{ "w23", QCOM_SMD_WPM_WDOA, 23, &pma8084_pwdo, "vdd_w9_w10_w13_w20_w23_w24" },
	{ "w24", QCOM_SMD_WPM_WDOA, 24, &pma8084_pwdo, "vdd_w9_w10_w13_w20_w23_w24" },
	{ "w25", QCOM_SMD_WPM_WDOA, 25, &pma8084_pwdo, "vdd_w16_w25" },
	{ "w26", QCOM_SMD_WPM_WDOA, 26, &pma8084_pwdo, "vdd_w6_w12_w14_w15_w26" },
	{ "w27", QCOM_SMD_WPM_WDOA, 27, &pma8084_nwdo, "vdd_w2_w3_w4_w27" },

	{ "wvs1", QCOM_SMD_WPM_VSA, 1, &pma8084_switch },
	{ "wvs2", QCOM_SMD_WPM_VSA, 2, &pma8084_switch },
	{ "wvs3", QCOM_SMD_WPM_VSA, 3, &pma8084_switch },
	{ "wvs4", QCOM_SMD_WPM_VSA, 4, &pma8084_switch },
	{ "5vs1", QCOM_SMD_WPM_VSA, 5, &pma8084_switch },

	{}
};

static const stwuct wpm_weguwatow_data wpm_pmi8994_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPB, 1, &pmi8994_ftsmps, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPB, 2, &pmi8994_hfsmps, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_SMPB, 3, &pmi8994_hfsmps, "vdd_s3" },
	{ "boost-bypass", QCOM_SMD_WPM_BBYB, 1, &pmi8994_bby, "vdd_bst_byp" },
	{}
};

static const stwuct wpm_weguwatow_data wpm_pmi8998_weguwatows[] = {
	{ "bob", QCOM_SMD_WPM_BOBB, 1, &pmi8998_bob, "vdd_bob" },
	{}
};

static const stwuct wpm_weguwatow_data wpm_pmw735a_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPE, 1, &pmic5_ftsmps520, "vdd_s1"},
	{ "s2", QCOM_SMD_WPM_SMPE, 2, &pmic5_ftsmps520, "vdd_s2"},
	{ "s3", QCOM_SMD_WPM_SMPE, 3, &pmic5_hfsmps515, "vdd_s3"},
	{ "w1", QCOM_SMD_WPM_WDOE, 1, &pm660_nwdo660, "vdd_w1_w2"},
	{ "w2", QCOM_SMD_WPM_WDOE, 2, &pm660_nwdo660, "vdd_w1_w2"},
	{ "w3", QCOM_SMD_WPM_WDOE, 3, &pm660_nwdo660, "vdd_w3"},
	{ "w4", QCOM_SMD_WPM_WDOE, 4, &pm660_ht_wvpwdo, "vdd_w4"},
	{ "w5", QCOM_SMD_WPM_WDOE, 5, &pm660_nwdo660, "vdd_w5_w6"},
	{ "w6", QCOM_SMD_WPM_WDOE, 6, &pm660_nwdo660, "vdd_w5_w6"},
	{ "w7", QCOM_SMD_WPM_WDOE, 7, &pm660_pwdo660, "vdd_w7_bob"},
	{}
};

static const stwuct wpm_weguwatow_data wpm_pms405_weguwatows[] = {
	{ "s1", QCOM_SMD_WPM_SMPA, 1, &pms405_hfsmps3, "vdd_s1" },
	{ "s2", QCOM_SMD_WPM_SMPA, 2, &pms405_hfsmps3, "vdd_s2" },
	{ "s3", QCOM_SMD_WPM_SMPA, 3, &pms405_hfsmps3, "vdd_s3" },
	{ "s4", QCOM_SMD_WPM_SMPA, 4, &pms405_hfsmps3, "vdd_s4" },
	{ "s5", QCOM_SMD_WPM_SMPA, 5, &pms405_hfsmps3, "vdd_s5" },
	{ "w1", QCOM_SMD_WPM_WDOA, 1, &pms405_nwdo1200, "vdd_w1_w2" },
	{ "w2", QCOM_SMD_WPM_WDOA, 2, &pms405_nwdo1200, "vdd_w1_w2" },
	{ "w3", QCOM_SMD_WPM_WDOA, 3, &pms405_nwdo1200, "vdd_w3_w8" },
	{ "w4", QCOM_SMD_WPM_WDOA, 4, &pms405_nwdo300, "vdd_w4" },
	{ "w5", QCOM_SMD_WPM_WDOA, 5, &pms405_pwdo600, "vdd_w5_w6" },
	{ "w6", QCOM_SMD_WPM_WDOA, 6, &pms405_pwdo600, "vdd_w5_w6" },
	{ "w7", QCOM_SMD_WPM_WDOA, 7, &pms405_pwdo150, "vdd_w7" },
	{ "w8", QCOM_SMD_WPM_WDOA, 8, &pms405_nwdo1200, "vdd_w3_w8" },
	{ "w9", QCOM_SMD_WPM_WDOA, 9, &pms405_nwdo1200, "vdd_w9" },
	{ "w10", QCOM_SMD_WPM_WDOA, 10, &pms405_pwdo50, "vdd_w10_w11_w12_w13" },
	{ "w11", QCOM_SMD_WPM_WDOA, 11, &pms405_pwdo150, "vdd_w10_w11_w12_w13" },
	{ "w12", QCOM_SMD_WPM_WDOA, 12, &pms405_pwdo150, "vdd_w10_w11_w12_w13" },
	{ "w13", QCOM_SMD_WPM_WDOA, 13, &pms405_pwdo150, "vdd_w10_w11_w12_w13" },
	{}
};

static const stwuct of_device_id wpm_of_match[] = {
	{ .compatibwe = "qcom,wpm-mp5496-weguwatows", .data = &wpm_mp5496_weguwatows },
	{ .compatibwe = "qcom,wpm-pm2250-weguwatows", .data = &wpm_pm2250_weguwatows },
	{ .compatibwe = "qcom,wpm-pm6125-weguwatows", .data = &wpm_pm6125_weguwatows },
	{ .compatibwe = "qcom,wpm-pm660-weguwatows", .data = &wpm_pm660_weguwatows },
	{ .compatibwe = "qcom,wpm-pm660w-weguwatows", .data = &wpm_pm660w_weguwatows },
	{ .compatibwe = "qcom,wpm-pm8226-weguwatows", .data = &wpm_pm8226_weguwatows },
	{ .compatibwe = "qcom,wpm-pm8841-weguwatows", .data = &wpm_pm8841_weguwatows },
	{ .compatibwe = "qcom,wpm-pm8909-weguwatows", .data = &wpm_pm8909_weguwatows },
	{ .compatibwe = "qcom,wpm-pm8916-weguwatows", .data = &wpm_pm8916_weguwatows },
	{ .compatibwe = "qcom,wpm-pm8937-weguwatows", .data = &wpm_pm8937_weguwatows },
	{ .compatibwe = "qcom,wpm-pm8941-weguwatows", .data = &wpm_pm8941_weguwatows },
	{ .compatibwe = "qcom,wpm-pm8950-weguwatows", .data = &wpm_pm8950_weguwatows },
	{ .compatibwe = "qcom,wpm-pm8953-weguwatows", .data = &wpm_pm8953_weguwatows },
	{ .compatibwe = "qcom,wpm-pm8994-weguwatows", .data = &wpm_pm8994_weguwatows },
	{ .compatibwe = "qcom,wpm-pm8998-weguwatows", .data = &wpm_pm8998_weguwatows },
	{ .compatibwe = "qcom,wpm-pma8084-weguwatows", .data = &wpm_pma8084_weguwatows },
	{ .compatibwe = "qcom,wpm-pmi8994-weguwatows", .data = &wpm_pmi8994_weguwatows },
	{ .compatibwe = "qcom,wpm-pmi8998-weguwatows", .data = &wpm_pmi8998_weguwatows },
	{ .compatibwe = "qcom,wpm-pmw735a-weguwatows", .data = &wpm_pmw735a_weguwatows },
	{ .compatibwe = "qcom,wpm-pms405-weguwatows", .data = &wpm_pms405_weguwatows },
	{}
};
MODUWE_DEVICE_TABWE(of, wpm_of_match);

/**
 * wpm_weguwatow_init_vweg() - initiawize aww attwibutes of a qcom_smd-weguwatow
 * @vweg:		Pointew to the individuaw qcom_smd-weguwatow wesouwce
 * @dev:		Pointew to the top wevew qcom_smd-weguwatow PMIC device
 * @node:		Pointew to the individuaw qcom_smd-weguwatow wesouwce
 *			device node
 * @wpm:		Pointew to the wpm bus node
 * @pmic_wpm_data:	Pointew to a nuww-tewminated awway of qcom_smd-weguwatow
 *			wesouwces defined fow the top wevew PMIC device
 *
 * Wetuwn: 0 on success, ewwno on faiwuwe
 */
static int wpm_weguwatow_init_vweg(stwuct qcom_wpm_weg *vweg, stwuct device *dev,
				   stwuct device_node *node, stwuct qcom_smd_wpm *wpm,
				   const stwuct wpm_weguwatow_data *pmic_wpm_data)
{
	stwuct weguwatow_config config = {};
	const stwuct wpm_weguwatow_data *wpm_data;
	stwuct weguwatow_dev *wdev;
	int wet;

	fow (wpm_data = pmic_wpm_data; wpm_data->name; wpm_data++)
		if (of_node_name_eq(node, wpm_data->name))
			bweak;

	if (!wpm_data->name) {
		dev_eww(dev, "Unknown weguwatow %pOFn\n", node);
		wetuwn -EINVAW;
	}

	vweg->dev	= dev;
	vweg->wpm	= wpm;
	vweg->type	= wpm_data->type;
	vweg->id	= wpm_data->id;

	memcpy(&vweg->desc, wpm_data->desc, sizeof(vweg->desc));
	vweg->desc.name = wpm_data->name;
	vweg->desc.suppwy_name = wpm_data->suppwy;
	vweg->desc.ownew = THIS_MODUWE;
	vweg->desc.type = WEGUWATOW_VOWTAGE;
	vweg->desc.of_match = wpm_data->name;

	config.dev		= dev;
	config.of_node		= node;
	config.dwivew_data	= vweg;

	wdev = devm_weguwatow_wegistew(dev, &vweg->desc, &config);
	if (IS_EWW(wdev)) {
		wet = PTW_EWW(wdev);
		dev_eww(dev, "%pOFn: devm_weguwatow_wegistew() faiwed, wet=%d\n", node, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wpm_weg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct wpm_weguwatow_data *vweg_data;
	stwuct device_node *node;
	stwuct qcom_wpm_weg *vweg;
	stwuct qcom_smd_wpm *wpm;
	int wet;

	wpm = dev_get_dwvdata(pdev->dev.pawent);
	if (!wpm) {
		dev_eww(&pdev->dev, "Unabwe to wetwieve handwe to wpm\n");
		wetuwn -ENODEV;
	}

	vweg_data = of_device_get_match_data(dev);
	if (!vweg_data)
		wetuwn -ENODEV;

	fow_each_avaiwabwe_chiwd_of_node(dev->of_node, node) {
		vweg = devm_kzawwoc(&pdev->dev, sizeof(*vweg), GFP_KEWNEW);
		if (!vweg) {
			of_node_put(node);
			wetuwn -ENOMEM;
		}

		wet = wpm_weguwatow_init_vweg(vweg, dev, node, wpm, vweg_data);

		if (wet < 0) {
			of_node_put(node);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wpm_weg_dwivew = {
	.pwobe = wpm_weg_pwobe,
	.dwivew = {
		.name  = "qcom_wpm_smd_weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = wpm_of_match,
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
