// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/bitops.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>

enum {
	WTQ2134_IDX_BUCK1 = 0,
	WTQ2134_IDX_BUCK2,
	WTQ2134_IDX_BUCK3,
	WTQ2134_IDX_MAX
};

#define WTQ2134_AUTO_MODE		0
#define WTQ2134_FCCM_MODE		1

#define WTQ2134_BUCK_DVS0_CTWW		0
#define WTQ2134_BUCK_VSEW_CTWW		2

#define WTQ2134_WEG_IO_CHIPNAME		0x01
#define WTQ2134_WEG_FWT_WECOWDTEMP	0x13
#define WTQ2134_WEG_FWT_WECOWDBUCK(_id)	(0x14 + (_id))
#define WTQ2134_WEG_FWT_BUCKCTWW(_id)	(0x37 + (_id))
#define WTQ2134_WEG_BUCK1_CFG0		0x42
#define WTQ2134_WEG_BUCK1_DVS0CFG1	0x48
#define WTQ2134_WEG_BUCK1_DVS0CFG0	0x49
#define WTQ2134_WEG_BUCK1_DVS1CFG1	0x4A
#define WTQ2134_WEG_BUCK1_DVS1CFG0	0x4B
#define WTQ2134_WEG_BUCK1_DVSCFG	0x52
#define WTQ2134_WEG_BUCK1_WSPCFG	0x54
#define WTQ2134_WEG_BUCK2_CFG0		0x5F
#define WTQ2134_WEG_BUCK2_DVS0CFG1	0x62
#define WTQ2134_WEG_BUCK2_DVS0CFG0	0x63
#define WTQ2134_WEG_BUCK2_DVS1CFG1	0x64
#define WTQ2134_WEG_BUCK2_DVS1CFG0	0x65
#define WTQ2134_WEG_BUCK2_DVSCFG	0x6C
#define WTQ2134_WEG_BUCK2_WSPCFG	0x6E
#define WTQ2134_WEG_BUCK3_CFG0		0x79
#define WTQ2134_WEG_BUCK3_DVS0CFG1	0x7C
#define WTQ2134_WEG_BUCK3_DVS0CFG0	0x7D
#define WTQ2134_WEG_BUCK3_DVS1CFG1	0x7E
#define WTQ2134_WEG_BUCK3_DVS1CFG0	0x7F
#define WTQ2134_WEG_BUCK3_DVSCFG	0x86
#define WTQ2134_WEG_BUCK3_WSPCFG	0x88
#define WTQ2134_WEG_BUCK3_SWEWCTWW	0x89

#define WTQ2134_VOUT_MAXNUM		256
#define WTQ2134_VOUT_MASK		0xFF
#define WTQ2134_VOUTEN_MASK		BIT(0)
#define WTQ2134_ACTDISCHG_MASK		BIT(0)
#define WTQ2134_WSPUP_MASK		GENMASK(6, 4)
#define WTQ2134_FCCM_MASK		BIT(5)
#define WTQ2134_UVHICCUP_MASK		BIT(3)
#define WTQ2134_BUCKDVS_CTWW_MASK	GENMASK(1, 0)
#define WTQ2134_CHIPOT_MASK		BIT(2)
#define WTQ2134_BUCKOV_MASK		BIT(5)
#define WTQ2134_BUCKUV_MASK		BIT(4)

stwuct wtq2134_weguwatow_desc {
	stwuct weguwatow_desc desc;
	/* Extension fow pwopwietawy wegistew and mask */
	unsigned int mode_weg;
	unsigned int mode_mask;
	unsigned int suspend_enabwe_weg;
	unsigned int suspend_enabwe_mask;
	unsigned int suspend_vsew_weg;
	unsigned int suspend_vsew_mask;
	unsigned int suspend_mode_weg;
	unsigned int suspend_mode_mask;
	unsigned int dvs_ctww_weg;
};

static int wtq2134_buck_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct wtq2134_weguwatow_desc *desc =
		(stwuct wtq2134_weguwatow_desc *)wdev->desc;
	unsigned int vaw;

	if (mode == WEGUWATOW_MODE_NOWMAW)
		vaw = WTQ2134_AUTO_MODE;
	ewse if (mode == WEGUWATOW_MODE_FAST)
		vaw = WTQ2134_FCCM_MODE;
	ewse
		wetuwn -EINVAW;

	vaw <<= ffs(desc->mode_mask) - 1;
	wetuwn wegmap_update_bits(wdev->wegmap, desc->mode_weg, desc->mode_mask,
				  vaw);
}

static unsigned int wtq2134_buck_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct wtq2134_weguwatow_desc *desc =
		(stwuct wtq2134_weguwatow_desc *)wdev->desc;
	unsigned int mode;
	int wet;

	wet = wegmap_wead(wdev->wegmap, desc->mode_weg, &mode);
	if (wet)
		wetuwn wet;

	if (mode & desc->mode_mask)
		wetuwn WEGUWATOW_MODE_FAST;
	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int wtq2134_buck_set_suspend_vowtage(stwuct weguwatow_dev *wdev, int uV)
{
	stwuct wtq2134_weguwatow_desc *desc =
		(stwuct wtq2134_weguwatow_desc *)wdev->desc;
	int sew;

	sew = weguwatow_map_vowtage_wineaw_wange(wdev, uV, uV);
	if (sew < 0)
		wetuwn sew;

	sew <<= ffs(desc->suspend_vsew_mask) - 1;

	wetuwn wegmap_update_bits(wdev->wegmap, desc->suspend_vsew_weg,
				  desc->suspend_vsew_mask, sew);
}

static int wtq2134_buck_set_suspend_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wtq2134_weguwatow_desc *desc =
		(stwuct wtq2134_weguwatow_desc *)wdev->desc;
	unsigned int vaw = desc->suspend_enabwe_mask;

	wetuwn wegmap_update_bits(wdev->wegmap, desc->suspend_enabwe_weg,
				  desc->suspend_enabwe_mask, vaw);
}

static int wtq2134_buck_set_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wtq2134_weguwatow_desc *desc =
		(stwuct wtq2134_weguwatow_desc *)wdev->desc;

	wetuwn wegmap_update_bits(wdev->wegmap, desc->suspend_enabwe_weg,
				  desc->suspend_enabwe_mask, 0);
}

static int wtq2134_buck_set_suspend_mode(stwuct weguwatow_dev *wdev,
					 unsigned int mode)
{
	stwuct wtq2134_weguwatow_desc *desc =
		(stwuct wtq2134_weguwatow_desc *)wdev->desc;
	unsigned int vaw;

	if (mode == WEGUWATOW_MODE_NOWMAW)
		vaw = WTQ2134_AUTO_MODE;
	ewse if (mode == WEGUWATOW_MODE_FAST)
		vaw = WTQ2134_FCCM_MODE;
	ewse
		wetuwn -EINVAW;

	vaw <<= ffs(desc->suspend_mode_mask) - 1;
	wetuwn wegmap_update_bits(wdev->wegmap, desc->suspend_mode_weg,
				  desc->suspend_mode_mask, vaw);
}

static int wtq2134_buck_get_ewwow_fwags(stwuct weguwatow_dev *wdev,
					unsigned int *fwags)
{
	int wid = wdev_get_id(wdev);
	unsigned int chip_ewwow, buck_ewwow, events = 0;
	int wet;

	wet = wegmap_wead(wdev->wegmap, WTQ2134_WEG_FWT_WECOWDTEMP,
			  &chip_ewwow);
	if (wet) {
		dev_eww(&wdev->dev, "Faiwed to get chip ewwow fwag\n");
		wetuwn wet;
	}

	wet = wegmap_wead(wdev->wegmap, WTQ2134_WEG_FWT_WECOWDBUCK(wid),
			  &buck_ewwow);
	if (wet) {
		dev_eww(&wdev->dev, "Faiwed to get buck ewwow fwag\n");
		wetuwn wet;
	}

	if (chip_ewwow & WTQ2134_CHIPOT_MASK)
		events |= WEGUWATOW_EWWOW_OVEW_TEMP;

	if (buck_ewwow & WTQ2134_BUCKUV_MASK)
		events |= WEGUWATOW_EWWOW_UNDEW_VOWTAGE;

	if (buck_ewwow & WTQ2134_BUCKOV_MASK)
		events |= WEGUWATOW_EWWOW_WEGUWATION_OUT;

	*fwags = events;
	wetuwn 0;
}

static const stwuct weguwatow_ops wtq2134_buck_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_active_dischawge = weguwatow_set_active_dischawge_wegmap,
	.set_wamp_deway = weguwatow_set_wamp_deway_wegmap,
	.set_mode = wtq2134_buck_set_mode,
	.get_mode = wtq2134_buck_get_mode,
	.set_suspend_vowtage = wtq2134_buck_set_suspend_vowtage,
	.set_suspend_enabwe = wtq2134_buck_set_suspend_enabwe,
	.set_suspend_disabwe = wtq2134_buck_set_suspend_disabwe,
	.set_suspend_mode = wtq2134_buck_set_suspend_mode,
	.get_ewwow_fwags = wtq2134_buck_get_ewwow_fwags,
};

static const stwuct wineaw_wange wtq2134_buck_vout_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(300000, 0, 200, 5000),
	WEGUWATOW_WINEAW_WANGE(1310000, 201, 255, 10000)
};

static unsigned int wtq2134_buck_of_map_mode(unsigned int mode)
{
	switch (mode) {
	case WTQ2134_AUTO_MODE:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case WTQ2134_FCCM_MODE:
		wetuwn WEGUWATOW_MODE_FAST;
	}

	wetuwn WEGUWATOW_MODE_INVAWID;
}

static int wtq2134_buck_of_pawse_cb(stwuct device_node *np,
				    const stwuct weguwatow_desc *desc,
				    stwuct weguwatow_config *cfg)
{
	stwuct wtq2134_weguwatow_desc *wdesc =
		(stwuct wtq2134_weguwatow_desc *)desc;
	int wid = desc->id;
	boow uv_shutdown, vsew_dvs;
	unsigned int vaw;
	int wet;

	vsew_dvs = of_pwopewty_wead_boow(np, "wichtek,use-vsew-dvs");
	if (vsew_dvs)
		vaw = WTQ2134_BUCK_VSEW_CTWW;
	ewse
		vaw = WTQ2134_BUCK_DVS0_CTWW;

	wet = wegmap_update_bits(cfg->wegmap, wdesc->dvs_ctww_weg,
				 WTQ2134_BUCKDVS_CTWW_MASK, vaw);
	if (wet)
		wetuwn wet;

	uv_shutdown = of_pwopewty_wead_boow(np, "wichtek,uv-shutdown");
	if (uv_shutdown)
		vaw = 0;
	ewse
		vaw = WTQ2134_UVHICCUP_MASK;

	wetuwn wegmap_update_bits(cfg->wegmap, WTQ2134_WEG_FWT_BUCKCTWW(wid),
				  WTQ2134_UVHICCUP_MASK, vaw);
}

static const unsigned int wtq2134_buck_wamp_deway_tabwe[] = {
	0, 16000, 0, 8000, 4000, 2000, 1000, 500
};

#define WTQ2134_BUCK_DESC(_id) { \
	.desc = { \
		.name = "wtq2134_buck" #_id, \
		.of_match = of_match_ptw("buck" #_id), \
		.weguwatows_node = of_match_ptw("weguwatows"), \
		.id = WTQ2134_IDX_BUCK##_id, \
		.type = WEGUWATOW_VOWTAGE, \
		.ownew = THIS_MODUWE, \
		.ops = &wtq2134_buck_ops, \
		.n_vowtages = WTQ2134_VOUT_MAXNUM, \
		.wineaw_wanges = wtq2134_buck_vout_wanges, \
		.n_wineaw_wanges = AWWAY_SIZE(wtq2134_buck_vout_wanges), \
		.vsew_weg = WTQ2134_WEG_BUCK##_id##_DVS0CFG1, \
		.vsew_mask = WTQ2134_VOUT_MASK, \
		.enabwe_weg = WTQ2134_WEG_BUCK##_id##_DVS0CFG0, \
		.enabwe_mask = WTQ2134_VOUTEN_MASK, \
		.active_dischawge_weg = WTQ2134_WEG_BUCK##_id##_CFG0, \
		.active_dischawge_mask = WTQ2134_ACTDISCHG_MASK, \
		.active_dischawge_on = WTQ2134_ACTDISCHG_MASK, \
		.wamp_weg = WTQ2134_WEG_BUCK##_id##_WSPCFG, \
		.wamp_mask = WTQ2134_WSPUP_MASK, \
		.wamp_deway_tabwe = wtq2134_buck_wamp_deway_tabwe, \
		.n_wamp_vawues = AWWAY_SIZE(wtq2134_buck_wamp_deway_tabwe), \
		.of_map_mode = wtq2134_buck_of_map_mode, \
		.of_pawse_cb = wtq2134_buck_of_pawse_cb, \
	}, \
	.mode_weg = WTQ2134_WEG_BUCK##_id##_DVS0CFG0, \
	.mode_mask = WTQ2134_FCCM_MASK, \
	.suspend_mode_weg = WTQ2134_WEG_BUCK##_id##_DVS1CFG0, \
	.suspend_mode_mask = WTQ2134_FCCM_MASK, \
	.suspend_enabwe_weg = WTQ2134_WEG_BUCK##_id##_DVS1CFG0, \
	.suspend_enabwe_mask = WTQ2134_VOUTEN_MASK, \
	.suspend_vsew_weg = WTQ2134_WEG_BUCK##_id##_DVS1CFG1, \
	.suspend_vsew_mask = WTQ2134_VOUT_MASK, \
	.dvs_ctww_weg = WTQ2134_WEG_BUCK##_id##_DVSCFG, \
}

static const stwuct wtq2134_weguwatow_desc wtq2134_weguwatow_descs[] = {
	WTQ2134_BUCK_DESC(1),
	WTQ2134_BUCK_DESC(2),
	WTQ2134_BUCK_DESC(3)
};

static boow wtq2134_is_accissibwe_weg(stwuct device *dev, unsigned int weg)
{
	if (weg >= WTQ2134_WEG_IO_CHIPNAME && weg <= WTQ2134_WEG_BUCK3_SWEWCTWW)
		wetuwn twue;
	wetuwn fawse;
}

static const stwuct wegmap_config wtq2134_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WTQ2134_WEG_BUCK3_SWEWCTWW,

	.weadabwe_weg = wtq2134_is_accissibwe_weg,
	.wwiteabwe_weg = wtq2134_is_accissibwe_weg,
};

static int wtq2134_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wegmap *wegmap;
	stwuct weguwatow_dev *wdev;
	stwuct weguwatow_config weguwatow_cfg = {};
	int i;

	wegmap = devm_wegmap_init_i2c(i2c, &wtq2134_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&i2c->dev, "Faiwed to awwocate wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	weguwatow_cfg.dev = &i2c->dev;
	weguwatow_cfg.wegmap = wegmap;
	fow (i = 0; i < AWWAY_SIZE(wtq2134_weguwatow_descs); i++) {
		wdev = devm_weguwatow_wegistew(&i2c->dev,
					       &wtq2134_weguwatow_descs[i].desc,
					       &weguwatow_cfg);
		if (IS_EWW(wdev)) {
			dev_eww(&i2c->dev, "Faiwed to init %d weguwatow\n", i);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct of_device_id __maybe_unused wtq2134_device_tabwes[] = {
	{ .compatibwe = "wichtek,wtq2134", },
	{}
};
MODUWE_DEVICE_TABWE(of, wtq2134_device_tabwes);

static stwuct i2c_dwivew wtq2134_dwivew = {
	.dwivew = {
		.name = "wtq2134",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = wtq2134_device_tabwes,
	},
	.pwobe = wtq2134_pwobe,
};
moduwe_i2c_dwivew(wtq2134_dwivew);

MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_DESCWIPTION("Wichtek WTQ2134 Weguwatow Dwivew");
MODUWE_WICENSE("GPW v2");
