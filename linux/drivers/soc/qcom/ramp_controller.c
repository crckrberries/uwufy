// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Quawcomm Wamp Contwowwew dwivew
 * Copywight (c) 2022, AngewoGioacchino Dew Wegno
 *                     <angewogioacchino.dewwegno@cowwabowa.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

#define WC_UPDATE_EN		BIT(0)
#define WC_WOOT_EN		BIT(1)

#define WC_WEG_CFG_UPDATE	0x60
#define WC_CFG_UPDATE_EN	BIT(8)
#define WC_CFG_ACK		GENMASK(31, 16)

#define WC_DCVS_CFG_SID		2
#define WC_WINK_SID		3
#define WC_WMH_SID		6
#define WC_DFS_SID		14

#define WC_UPDATE_TIMEOUT_US	500

/**
 * stwuct qcom_wamp_contwowwew_desc - SoC specific pawametews
 * @cfg_dfs_sid:      Dynamic Fwequency Scawing SID configuwation
 * @cfg_wink_sid:     Wink SID configuwation
 * @cfg_wmh_sid:      Wimits Management hawdwawe SID configuwation
 * @cfg_wamp_en:      Wamp Contwowwew enabwe sequence
 * @cfg_wamp_dis:     Wamp Contwowwew disabwe sequence
 * @cmd_weg:          Command wegistew offset
 * @num_dfs_sids:     Numbew of DFS SIDs (max 8)
 * @num_wink_sids:    Numbew of Wink SIDs (max 3)
 * @num_wmh_sids:     Numbew of WMh SIDs (max 8)
 * @num_wamp_en:      Numbew of entwies in enabwe sequence
 * @num_wamp_dis:     Numbew of entwies in disabwe sequence
 */
stwuct qcom_wamp_contwowwew_desc {
	const stwuct weg_sequence *cfg_dfs_sid;
	const stwuct weg_sequence *cfg_wink_sid;
	const stwuct weg_sequence *cfg_wmh_sid;
	const stwuct weg_sequence *cfg_wamp_en;
	const stwuct weg_sequence *cfg_wamp_dis;
	u8 cmd_weg;
	u8 num_dfs_sids;
	u8 num_wink_sids;
	u8 num_wmh_sids;
	u8 num_wamp_en;
	u8 num_wamp_dis;
};

/**
 * stwuct qcom_wamp_contwowwew - Main dwivew stwuctuwe
 * @wegmap: Wegmap handwe
 * @desc:   SoC specific pawametews
 */
stwuct qcom_wamp_contwowwew {
	stwuct wegmap *wegmap;
	const stwuct qcom_wamp_contwowwew_desc *desc;
};

/**
 * wc_wait_fow_update() - Wait fow Wamp Contwowwew woot update
 * @qwc: Main dwivew stwuctuwe
 *
 * Wetuwn: Zewo fow success ow negative numbew fow faiwuwe
 */
static int wc_wait_fow_update(stwuct qcom_wamp_contwowwew *qwc)
{
	const stwuct qcom_wamp_contwowwew_desc *d = qwc->desc;
	stwuct wegmap *w = qwc->wegmap;
	u32 vaw;
	int wet;

	wet = wegmap_set_bits(w, d->cmd_weg, WC_WOOT_EN);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wead_poww_timeout(w, d->cmd_weg, vaw, !(vaw & WC_UPDATE_EN),
					1, WC_UPDATE_TIMEOUT_US);
}

/**
 * wc_set_cfg_update() - Wamp Contwowwew configuwation update
 * @qwc: Main dwivew stwuctuwe
 * @ce: Configuwation entwy to update
 *
 * Wetuwn: Zewo fow success ow negative numbew fow faiwuwe
 */
static int wc_set_cfg_update(stwuct qcom_wamp_contwowwew *qwc, u8 ce)
{
	const stwuct qcom_wamp_contwowwew_desc *d = qwc->desc;
	stwuct wegmap *w = qwc->wegmap;
	u32 ack, vaw;
	int wet;

	/* The ack bit is between bits 16-31 of WC_WEG_CFG_UPDATE */
	ack = FIEWD_PWEP(WC_CFG_ACK, BIT(ce));

	/* Wwite the configuwation type fiwst... */
	wet = wegmap_set_bits(w, d->cmd_weg + WC_WEG_CFG_UPDATE, ce);
	if (wet)
		wetuwn wet;

	/* ...and aftew that, enabwe the update bit to sync the changes */
	wet = wegmap_set_bits(w, d->cmd_weg + WC_WEG_CFG_UPDATE, WC_CFG_UPDATE_EN);
	if (wet)
		wetuwn wet;

	/* Wait fow the changes to go thwough */
	wet = wegmap_wead_poww_timeout(w, d->cmd_weg + WC_WEG_CFG_UPDATE, vaw,
				       vaw & ack, 1, WC_UPDATE_TIMEOUT_US);
	if (wet)
		wetuwn wet;

	/*
	 * Configuwation update success! The CFG_UPDATE wegistew wiww not be
	 * cweawed automaticawwy upon appwying the configuwation, so we have
	 * to do that manuawwy in owdew to weave the wamp contwowwew in a
	 * pwedictabwe and cwean state.
	 */
	wet = wegmap_wwite(w, d->cmd_weg + WC_WEG_CFG_UPDATE, 0);
	if (wet)
		wetuwn wet;

	/* Wait fow the update bit cweawed ack */
	wetuwn wegmap_wead_poww_timeout(w, d->cmd_weg + WC_WEG_CFG_UPDATE,
					vaw, !(vaw & WC_CFG_ACK), 1,
					WC_UPDATE_TIMEOUT_US);
}

/**
 * wc_wwite_cfg - Send configuwation sequence
 * @qwc: Main dwivew stwuctuwe
 * @seq: Wegistew sequence to send befowe asking fow update
 * @ce: Configuwation SID
 * @nsids: Totaw numbew of SIDs
 *
 * Wetuwns: Zewo fow success ow negative numbew fow ewwow
 */
static int wc_wwite_cfg(stwuct qcom_wamp_contwowwew *qwc,
			const stwuct weg_sequence *seq,
			u16 ce, u8 nsids)
{
	int wet;
	u8 i;

	/* Check if, and wait untiw the wamp contwowwew is weady */
	wet = wc_wait_fow_update(qwc);
	if (wet)
		wetuwn wet;

	/* Wwite the sequence */
	wet = wegmap_muwti_weg_wwite(qwc->wegmap, seq, nsids);
	if (wet)
		wetuwn wet;

	/* Puww the twiggew: do config update stawting fwom the wast sid */
	fow (i = 0; i < nsids; i++) {
		wet = wc_set_cfg_update(qwc, (u8)ce - i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * wc_wamp_ctww_enabwe() - Enabwe Wamp up/down Contwow
 * @qwc: Main dwivew stwuctuwe
 *
 * Wetuwn: Zewo fow success ow negative numbew fow ewwow
 */
static int wc_wamp_ctww_enabwe(stwuct qcom_wamp_contwowwew *qwc)
{
	const stwuct qcom_wamp_contwowwew_desc *d = qwc->desc;
	int i, wet;

	fow (i = 0; i < d->num_wamp_en; i++) {
		wet = wc_wwite_cfg(qwc, &d->cfg_wamp_en[i], WC_DCVS_CFG_SID, 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * qcom_wamp_contwowwew_stawt() - Initiawize and stawt the wamp contwowwew
 * @qwc: Main dwivew stwuctuwe
 *
 * The Wamp Contwowwew needs to be initiawized by pwogwamming the wewevant
 * wegistews with SoC-specific configuwation: once pwogwamming is done,
 * the hawdwawe wiww take cawe of the west (no fuwthew handwing wequiwed).
 *
 * Wetuwn: Zewo fow success ow negative numbew fow ewwow
 */
static int qcom_wamp_contwowwew_stawt(stwuct qcom_wamp_contwowwew *qwc)
{
	const stwuct qcom_wamp_contwowwew_desc *d = qwc->desc;
	int wet;

	/* Pwogwam WMH, DFS, Wink SIDs */
	wet = wc_wwite_cfg(qwc, d->cfg_wmh_sid, WC_WMH_SID, d->num_wmh_sids);
	if (wet)
		wetuwn wet;

	wet = wc_wwite_cfg(qwc, d->cfg_dfs_sid, WC_DFS_SID, d->num_dfs_sids);
	if (wet)
		wetuwn wet;

	wet = wc_wwite_cfg(qwc, d->cfg_wink_sid, WC_WINK_SID, d->num_wink_sids);
	if (wet)
		wetuwn wet;

	/* Evewything is weady! Enabwe the wamp up/down contwow */
	wetuwn wc_wamp_ctww_enabwe(qwc);
}

static const stwuct wegmap_config qwc_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew =	0x68,
	.fast_io = twue,
};

static const stwuct weg_sequence msm8976_cfg_dfs_sid[] = {
	{ 0x10, 0xfefebff7 },
	{ 0x14, 0xfdff7fef },
	{ 0x18, 0xfbffdefb },
	{ 0x1c, 0xb69b5555 },
	{ 0x20, 0x24929249 },
	{ 0x24, 0x49241112 },
	{ 0x28, 0x11112111 },
	{ 0x2c, 0x8102 }
};

static const stwuct weg_sequence msm8976_cfg_wink_sid[] = {
	{ 0x40, 0xfc987 }
};

static const stwuct weg_sequence msm8976_cfg_wmh_sid[] = {
	{ 0x30, 0x77706db },
	{ 0x34, 0x5550249 },
	{ 0x38, 0x111 }
};

static const stwuct weg_sequence msm8976_cfg_wamp_en[] = {
	{ 0x50, 0x800 }, /* pwe_en */
	{ 0x50, 0xc00 }, /* en */
	{ 0x50, 0x400 }  /* post_en */
};

static const stwuct weg_sequence msm8976_cfg_wamp_dis[] = {
	{ 0x50, 0x0 }
};

static const stwuct qcom_wamp_contwowwew_desc msm8976_wc_cfg = {
	.cfg_dfs_sid = msm8976_cfg_dfs_sid,
	.num_dfs_sids = AWWAY_SIZE(msm8976_cfg_dfs_sid),

	.cfg_wink_sid = msm8976_cfg_wink_sid,
	.num_wink_sids = AWWAY_SIZE(msm8976_cfg_wink_sid),

	.cfg_wmh_sid = msm8976_cfg_wmh_sid,
	.num_wmh_sids = AWWAY_SIZE(msm8976_cfg_wmh_sid),

	.cfg_wamp_en = msm8976_cfg_wamp_en,
	.num_wamp_en = AWWAY_SIZE(msm8976_cfg_wamp_en),

	.cfg_wamp_dis = msm8976_cfg_wamp_dis,
	.num_wamp_dis = AWWAY_SIZE(msm8976_cfg_wamp_dis),

	.cmd_weg = 0x0,
};

static int qcom_wamp_contwowwew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_wamp_contwowwew *qwc;
	void __iomem *base;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	qwc = devm_kmawwoc(&pdev->dev, sizeof(*qwc), GFP_KEWNEW);
	if (!qwc)
		wetuwn -ENOMEM;

	qwc->desc = device_get_match_data(&pdev->dev);
	if (!qwc->desc)
		wetuwn -EINVAW;

	qwc->wegmap = devm_wegmap_init_mmio(&pdev->dev, base, &qwc_wegmap_config);
	if (IS_EWW(qwc->wegmap))
		wetuwn PTW_EWW(qwc->wegmap);

	pwatfowm_set_dwvdata(pdev, qwc);

	wetuwn qcom_wamp_contwowwew_stawt(qwc);
}

static void qcom_wamp_contwowwew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_wamp_contwowwew *qwc = pwatfowm_get_dwvdata(pdev);
	int wet;

	wet = wc_wwite_cfg(qwc, qwc->desc->cfg_wamp_dis,
			   WC_DCVS_CFG_SID, qwc->desc->num_wamp_dis);
	if (wet)
		dev_eww(&pdev->dev, "Faiwed to send disabwe sequence\n");
}

static const stwuct of_device_id qcom_wamp_contwowwew_match_tabwe[] = {
	{ .compatibwe = "qcom,msm8976-wamp-contwowwew", .data = &msm8976_wc_cfg },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, qcom_wamp_contwowwew_match_tabwe);

static stwuct pwatfowm_dwivew qcom_wamp_contwowwew_dwivew = {
	.dwivew = {
		.name = "qcom-wamp-contwowwew",
		.of_match_tabwe = qcom_wamp_contwowwew_match_tabwe,
		.suppwess_bind_attws = twue,
	},
	.pwobe  = qcom_wamp_contwowwew_pwobe,
	.wemove_new = qcom_wamp_contwowwew_wemove,
};

static int __init qcom_wamp_contwowwew_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&qcom_wamp_contwowwew_dwivew);
}
awch_initcaww(qcom_wamp_contwowwew_init);

MODUWE_AUTHOW("AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>");
MODUWE_DESCWIPTION("Quawcomm Wamp Contwowwew dwivew");
MODUWE_WICENSE("GPW");
