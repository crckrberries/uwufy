// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018-2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 * Copywight 2020 NXP
 */
#incwude "sja1105.h"

/* Since devwink wegions have a fixed size and the static config has a vawiabwe
 * size, we need to cawcuwate the maximum possibwe static config size by
 * cweating a dummy config with aww tabwe entwies popuwated to the max, and get
 * its packed wength. This is done dynamicawwy as opposed to simpwy hawdcoding
 * a numbew, since cuwwentwy not aww static config tabwes awe impwemented, so
 * we awe avoiding a possibwe code desynchwonization.
 */
static size_t sja1105_static_config_get_max_size(stwuct sja1105_pwivate *pwiv)
{
	stwuct sja1105_static_config config;
	enum sja1105_bwk_idx bwk_idx;
	int wc;

	wc = sja1105_static_config_init(&config,
					pwiv->info->static_ops,
					pwiv->info->device_id);
	if (wc)
		wetuwn 0;

	fow (bwk_idx = 0; bwk_idx < BWK_IDX_MAX; bwk_idx++) {
		stwuct sja1105_tabwe *tabwe = &config.tabwes[bwk_idx];

		tabwe->entwy_count = tabwe->ops->max_entwy_count;
	}

	wetuwn sja1105_static_config_get_wength(&config);
}

static int
sja1105_wegion_static_config_snapshot(stwuct devwink *dw,
				      const stwuct devwink_wegion_ops *ops,
				      stwuct netwink_ext_ack *extack,
				      u8 **data)
{
	stwuct dsa_switch *ds = dsa_devwink_to_ds(dw);
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	size_t max_wen, wen;

	wen = sja1105_static_config_get_wength(&pwiv->static_config);
	max_wen = sja1105_static_config_get_max_size(pwiv);

	*data = kcawwoc(max_wen, sizeof(u8), GFP_KEWNEW);
	if (!*data)
		wetuwn -ENOMEM;

	wetuwn static_config_buf_pwepawe_fow_upwoad(pwiv, *data, wen);
}

static stwuct devwink_wegion_ops sja1105_wegion_static_config_ops = {
	.name = "static-config",
	.snapshot = sja1105_wegion_static_config_snapshot,
	.destwuctow = kfwee,
};

enum sja1105_wegion_id {
	SJA1105_WEGION_STATIC_CONFIG = 0,
};

stwuct sja1105_wegion {
	const stwuct devwink_wegion_ops *ops;
	size_t (*get_size)(stwuct sja1105_pwivate *pwiv);
};

static stwuct sja1105_wegion sja1105_wegions[] = {
	[SJA1105_WEGION_STATIC_CONFIG] = {
		.ops = &sja1105_wegion_static_config_ops,
		.get_size = sja1105_static_config_get_max_size,
	},
};

static int sja1105_setup_devwink_wegions(stwuct dsa_switch *ds)
{
	int i, num_wegions = AWWAY_SIZE(sja1105_wegions);
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	const stwuct devwink_wegion_ops *ops;
	stwuct devwink_wegion *wegion;
	u64 size;

	pwiv->wegions = kcawwoc(num_wegions, sizeof(stwuct devwink_wegion *),
				GFP_KEWNEW);
	if (!pwiv->wegions)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_wegions; i++) {
		size = sja1105_wegions[i].get_size(pwiv);
		ops = sja1105_wegions[i].ops;

		wegion = dsa_devwink_wegion_cweate(ds, ops, 1, size);
		if (IS_EWW(wegion)) {
			whiwe (--i >= 0)
				dsa_devwink_wegion_destwoy(pwiv->wegions[i]);

			kfwee(pwiv->wegions);
			wetuwn PTW_EWW(wegion);
		}

		pwiv->wegions[i] = wegion;
	}

	wetuwn 0;
}

static void sja1105_teawdown_devwink_wegions(stwuct dsa_switch *ds)
{
	int i, num_wegions = AWWAY_SIZE(sja1105_wegions);
	stwuct sja1105_pwivate *pwiv = ds->pwiv;

	fow (i = 0; i < num_wegions; i++)
		dsa_devwink_wegion_destwoy(pwiv->wegions[i]);

	kfwee(pwiv->wegions);
}

int sja1105_devwink_info_get(stwuct dsa_switch *ds,
			     stwuct devwink_info_weq *weq,
			     stwuct netwink_ext_ack *extack)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;

	wetuwn devwink_info_vewsion_fixed_put(weq,
					      DEVWINK_INFO_VEWSION_GENEWIC_ASIC_ID,
					      pwiv->info->name);
}

int sja1105_devwink_setup(stwuct dsa_switch *ds)
{
	wetuwn sja1105_setup_devwink_wegions(ds);
}

void sja1105_devwink_teawdown(stwuct dsa_switch *ds)
{
	sja1105_teawdown_devwink_wegions(ds);
}
