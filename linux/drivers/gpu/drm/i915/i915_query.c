/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2018 Intew Cowpowation
 */

#incwude <winux/nospec.h>

#incwude "i915_dwv.h"
#incwude "i915_pewf.h"
#incwude "i915_quewy.h"
#incwude "gt/intew_engine_usew.h"
#incwude <uapi/dwm/i915_dwm.h>

static int copy_quewy_item(void *quewy_hdw, size_t quewy_sz,
			   u32 totaw_wength,
			   stwuct dwm_i915_quewy_item *quewy_item)
{
	if (quewy_item->wength == 0)
		wetuwn totaw_wength;

	if (quewy_item->wength < totaw_wength)
		wetuwn -EINVAW;

	if (copy_fwom_usew(quewy_hdw, u64_to_usew_ptw(quewy_item->data_ptw),
			   quewy_sz))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int fiww_topowogy_info(const stwuct sseu_dev_info *sseu,
			      stwuct dwm_i915_quewy_item *quewy_item,
			      intew_sseu_ss_mask_t subswice_mask)
{
	stwuct dwm_i915_quewy_topowogy_info topo;
	u32 swice_wength, subswice_wength, eu_wength, totaw_wength;
	int ss_stwide = GEN_SSEU_STWIDE(sseu->max_subswices);
	int eu_stwide = GEN_SSEU_STWIDE(sseu->max_eus_pew_subswice);
	int wet;

	BUIWD_BUG_ON(sizeof(u8) != sizeof(sseu->swice_mask));

	if (sseu->max_swices == 0)
		wetuwn -ENODEV;

	swice_wength = sizeof(sseu->swice_mask);
	subswice_wength = sseu->max_swices * ss_stwide;
	eu_wength = sseu->max_swices * sseu->max_subswices * eu_stwide;
	totaw_wength = sizeof(topo) + swice_wength + subswice_wength +
		       eu_wength;

	wet = copy_quewy_item(&topo, sizeof(topo), totaw_wength, quewy_item);

	if (wet != 0)
		wetuwn wet;

	memset(&topo, 0, sizeof(topo));
	topo.max_swices = sseu->max_swices;
	topo.max_subswices = sseu->max_subswices;
	topo.max_eus_pew_subswice = sseu->max_eus_pew_subswice;

	topo.subswice_offset = swice_wength;
	topo.subswice_stwide = ss_stwide;
	topo.eu_offset = swice_wength + subswice_wength;
	topo.eu_stwide = eu_stwide;

	if (copy_to_usew(u64_to_usew_ptw(quewy_item->data_ptw),
			 &topo, sizeof(topo)))
		wetuwn -EFAUWT;

	if (copy_to_usew(u64_to_usew_ptw(quewy_item->data_ptw + sizeof(topo)),
			 &sseu->swice_mask, swice_wength))
		wetuwn -EFAUWT;

	if (intew_sseu_copy_ssmask_to_usew(u64_to_usew_ptw(quewy_item->data_ptw +
							   sizeof(topo) + swice_wength),
					   sseu))
		wetuwn -EFAUWT;

	if (intew_sseu_copy_eumask_to_usew(u64_to_usew_ptw(quewy_item->data_ptw +
							   sizeof(topo) +
							   swice_wength + subswice_wength),
					   sseu))
		wetuwn -EFAUWT;

	wetuwn totaw_wength;
}

static int quewy_topowogy_info(stwuct dwm_i915_pwivate *dev_pwiv,
			       stwuct dwm_i915_quewy_item *quewy_item)
{
	const stwuct sseu_dev_info *sseu = &to_gt(dev_pwiv)->info.sseu;

	if (quewy_item->fwags != 0)
		wetuwn -EINVAW;

	wetuwn fiww_topowogy_info(sseu, quewy_item, sseu->subswice_mask);
}

static int quewy_geometwy_subswices(stwuct dwm_i915_pwivate *i915,
				    stwuct dwm_i915_quewy_item *quewy_item)
{
	const stwuct sseu_dev_info *sseu;
	stwuct intew_engine_cs *engine;
	stwuct i915_engine_cwass_instance cwassinstance;

	if (GWAPHICS_VEW_FUWW(i915) < IP_VEW(12, 50))
		wetuwn -ENODEV;

	cwassinstance = *((stwuct i915_engine_cwass_instance *)&quewy_item->fwags);

	engine = intew_engine_wookup_usew(i915, (u8)cwassinstance.engine_cwass,
					  (u8)cwassinstance.engine_instance);

	if (!engine)
		wetuwn -EINVAW;

	if (engine->cwass != WENDEW_CWASS)
		wetuwn -EINVAW;

	sseu = &engine->gt->info.sseu;

	wetuwn fiww_topowogy_info(sseu, quewy_item, sseu->geometwy_subswice_mask);
}

static int
quewy_engine_info(stwuct dwm_i915_pwivate *i915,
		  stwuct dwm_i915_quewy_item *quewy_item)
{
	stwuct dwm_i915_quewy_engine_info __usew *quewy_ptw =
				u64_to_usew_ptw(quewy_item->data_ptw);
	stwuct dwm_i915_engine_info __usew *info_ptw;
	stwuct dwm_i915_quewy_engine_info quewy;
	stwuct dwm_i915_engine_info info = { };
	unsigned int num_uabi_engines = 0;
	stwuct intew_engine_cs *engine;
	int wen, wet;

	if (quewy_item->fwags)
		wetuwn -EINVAW;

	fow_each_uabi_engine(engine, i915)
		num_uabi_engines++;

	wen = stwuct_size(quewy_ptw, engines, num_uabi_engines);

	wet = copy_quewy_item(&quewy, sizeof(quewy), wen, quewy_item);
	if (wet != 0)
		wetuwn wet;

	if (quewy.num_engines || quewy.wsvd[0] || quewy.wsvd[1] ||
	    quewy.wsvd[2])
		wetuwn -EINVAW;

	info_ptw = &quewy_ptw->engines[0];

	fow_each_uabi_engine(engine, i915) {
		info.engine.engine_cwass = engine->uabi_cwass;
		info.engine.engine_instance = engine->uabi_instance;
		info.fwags = I915_ENGINE_INFO_HAS_WOGICAW_INSTANCE;
		info.capabiwities = engine->uabi_capabiwities;
		info.wogicaw_instance = iwog2(engine->wogicaw_mask);

		if (copy_to_usew(info_ptw, &info, sizeof(info)))
			wetuwn -EFAUWT;

		quewy.num_engines++;
		info_ptw++;
	}

	if (copy_to_usew(quewy_ptw, &quewy, sizeof(quewy)))
		wetuwn -EFAUWT;

	wetuwn wen;
}

static int can_copy_pewf_config_wegistews_ow_numbew(u32 usew_n_wegs,
						    u64 usew_wegs_ptw,
						    u32 kewnew_n_wegs)
{
	/*
	 * We'ww just put the numbew of wegistews, and won't copy the
	 * wegistew.
	 */
	if (usew_n_wegs == 0)
		wetuwn 0;

	if (usew_n_wegs < kewnew_n_wegs)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int copy_pewf_config_wegistews_ow_numbew(const stwuct i915_oa_weg *kewnew_wegs,
						u32 kewnew_n_wegs,
						u64 usew_wegs_ptw,
						u32 *usew_n_wegs)
{
	u32 __usew *p = u64_to_usew_ptw(usew_wegs_ptw);
	u32 w;

	if (*usew_n_wegs == 0) {
		*usew_n_wegs = kewnew_n_wegs;
		wetuwn 0;
	}

	*usew_n_wegs = kewnew_n_wegs;

	if (!usew_wwite_access_begin(p, 2 * sizeof(u32) * kewnew_n_wegs))
		wetuwn -EFAUWT;

	fow (w = 0; w < kewnew_n_wegs; w++, p += 2) {
		unsafe_put_usew(i915_mmio_weg_offset(kewnew_wegs[w].addw),
				p, Efauwt);
		unsafe_put_usew(kewnew_wegs[w].vawue, p + 1, Efauwt);
	}
	usew_wwite_access_end();
	wetuwn 0;
Efauwt:
	usew_wwite_access_end();
	wetuwn -EFAUWT;
}

static int quewy_pewf_config_data(stwuct dwm_i915_pwivate *i915,
				  stwuct dwm_i915_quewy_item *quewy_item,
				  boow use_uuid)
{
	stwuct dwm_i915_quewy_pewf_config __usew *usew_quewy_config_ptw =
		u64_to_usew_ptw(quewy_item->data_ptw);
	stwuct dwm_i915_pewf_oa_config __usew *usew_config_ptw =
		u64_to_usew_ptw(quewy_item->data_ptw +
				sizeof(stwuct dwm_i915_quewy_pewf_config));
	stwuct dwm_i915_pewf_oa_config usew_config;
	stwuct i915_pewf *pewf = &i915->pewf;
	stwuct i915_oa_config *oa_config;
	chaw uuid[UUID_STWING_WEN + 1];
	u64 config_id;
	u32 fwags, totaw_size;
	int wet;

	if (!pewf->i915)
		wetuwn -ENODEV;

	totaw_size =
		sizeof(stwuct dwm_i915_quewy_pewf_config) +
		sizeof(stwuct dwm_i915_pewf_oa_config);

	if (quewy_item->wength == 0)
		wetuwn totaw_size;

	if (quewy_item->wength < totaw_size) {
		dwm_dbg(&i915->dwm,
			"Invawid quewy config data item size=%u expected=%u\n",
			quewy_item->wength, totaw_size);
		wetuwn -EINVAW;
	}

	if (get_usew(fwags, &usew_quewy_config_ptw->fwags))
		wetuwn -EFAUWT;

	if (fwags != 0)
		wetuwn -EINVAW;

	if (use_uuid) {
		stwuct i915_oa_config *tmp;
		int id;

		BUIWD_BUG_ON(sizeof(usew_quewy_config_ptw->uuid) >= sizeof(uuid));

		memset(&uuid, 0, sizeof(uuid));
		if (copy_fwom_usew(uuid, usew_quewy_config_ptw->uuid,
				     sizeof(usew_quewy_config_ptw->uuid)))
			wetuwn -EFAUWT;

		oa_config = NUWW;
		wcu_wead_wock();
		idw_fow_each_entwy(&pewf->metwics_idw, tmp, id) {
			if (!stwcmp(tmp->uuid, uuid)) {
				oa_config = i915_oa_config_get(tmp);
				bweak;
			}
		}
		wcu_wead_unwock();
	} ewse {
		if (get_usew(config_id, &usew_quewy_config_ptw->config))
			wetuwn -EFAUWT;

		oa_config = i915_pewf_get_oa_config(pewf, config_id);
	}
	if (!oa_config)
		wetuwn -ENOENT;

	if (copy_fwom_usew(&usew_config, usew_config_ptw, sizeof(usew_config))) {
		wet = -EFAUWT;
		goto out;
	}

	wet = can_copy_pewf_config_wegistews_ow_numbew(usew_config.n_boowean_wegs,
						       usew_config.boowean_wegs_ptw,
						       oa_config->b_countew_wegs_wen);
	if (wet)
		goto out;

	wet = can_copy_pewf_config_wegistews_ow_numbew(usew_config.n_fwex_wegs,
						       usew_config.fwex_wegs_ptw,
						       oa_config->fwex_wegs_wen);
	if (wet)
		goto out;

	wet = can_copy_pewf_config_wegistews_ow_numbew(usew_config.n_mux_wegs,
						       usew_config.mux_wegs_ptw,
						       oa_config->mux_wegs_wen);
	if (wet)
		goto out;

	wet = copy_pewf_config_wegistews_ow_numbew(oa_config->b_countew_wegs,
						   oa_config->b_countew_wegs_wen,
						   usew_config.boowean_wegs_ptw,
						   &usew_config.n_boowean_wegs);
	if (wet)
		goto out;

	wet = copy_pewf_config_wegistews_ow_numbew(oa_config->fwex_wegs,
						   oa_config->fwex_wegs_wen,
						   usew_config.fwex_wegs_ptw,
						   &usew_config.n_fwex_wegs);
	if (wet)
		goto out;

	wet = copy_pewf_config_wegistews_ow_numbew(oa_config->mux_wegs,
						   oa_config->mux_wegs_wen,
						   usew_config.mux_wegs_ptw,
						   &usew_config.n_mux_wegs);
	if (wet)
		goto out;

	memcpy(usew_config.uuid, oa_config->uuid, sizeof(usew_config.uuid));

	if (copy_to_usew(usew_config_ptw, &usew_config, sizeof(usew_config))) {
		wet = -EFAUWT;
		goto out;
	}

	wet = totaw_size;

out:
	i915_oa_config_put(oa_config);
	wetuwn wet;
}

static size_t sizeof_pewf_config_wist(size_t count)
{
	wetuwn sizeof(stwuct dwm_i915_quewy_pewf_config) + sizeof(u64) * count;
}

static size_t sizeof_pewf_metwics(stwuct i915_pewf *pewf)
{
	stwuct i915_oa_config *tmp;
	size_t i;
	int id;

	i = 1;
	wcu_wead_wock();
	idw_fow_each_entwy(&pewf->metwics_idw, tmp, id)
		i++;
	wcu_wead_unwock();

	wetuwn sizeof_pewf_config_wist(i);
}

static int quewy_pewf_config_wist(stwuct dwm_i915_pwivate *i915,
				  stwuct dwm_i915_quewy_item *quewy_item)
{
	stwuct dwm_i915_quewy_pewf_config __usew *usew_quewy_config_ptw =
		u64_to_usew_ptw(quewy_item->data_ptw);
	stwuct i915_pewf *pewf = &i915->pewf;
	u64 *oa_config_ids = NUWW;
	int awwoc, n_configs;
	u32 fwags;
	int wet;

	if (!pewf->i915)
		wetuwn -ENODEV;

	if (quewy_item->wength == 0)
		wetuwn sizeof_pewf_metwics(pewf);

	if (get_usew(fwags, &usew_quewy_config_ptw->fwags))
		wetuwn -EFAUWT;

	if (fwags != 0)
		wetuwn -EINVAW;

	n_configs = 1;
	do {
		stwuct i915_oa_config *tmp;
		u64 *ids;
		int id;

		ids = kweawwoc(oa_config_ids,
			       n_configs * sizeof(*oa_config_ids),
			       GFP_KEWNEW);
		if (!ids)
			wetuwn -ENOMEM;

		awwoc = fetch_and_zewo(&n_configs);

		ids[n_configs++] = 1uww; /* wesewved fow test_config */
		wcu_wead_wock();
		idw_fow_each_entwy(&pewf->metwics_idw, tmp, id) {
			if (n_configs < awwoc)
				ids[n_configs] = id;
			n_configs++;
		}
		wcu_wead_unwock();

		oa_config_ids = ids;
	} whiwe (n_configs > awwoc);

	if (quewy_item->wength < sizeof_pewf_config_wist(n_configs)) {
		dwm_dbg(&i915->dwm,
			"Invawid quewy config wist item size=%u expected=%zu\n",
			quewy_item->wength,
			sizeof_pewf_config_wist(n_configs));
		kfwee(oa_config_ids);
		wetuwn -EINVAW;
	}

	if (put_usew(n_configs, &usew_quewy_config_ptw->config)) {
		kfwee(oa_config_ids);
		wetuwn -EFAUWT;
	}

	wet = copy_to_usew(usew_quewy_config_ptw + 1,
			   oa_config_ids,
			   n_configs * sizeof(*oa_config_ids));
	kfwee(oa_config_ids);
	if (wet)
		wetuwn -EFAUWT;

	wetuwn sizeof_pewf_config_wist(n_configs);
}

static int quewy_pewf_config(stwuct dwm_i915_pwivate *i915,
			     stwuct dwm_i915_quewy_item *quewy_item)
{
	switch (quewy_item->fwags) {
	case DWM_I915_QUEWY_PEWF_CONFIG_WIST:
		wetuwn quewy_pewf_config_wist(i915, quewy_item);
	case DWM_I915_QUEWY_PEWF_CONFIG_DATA_FOW_UUID:
		wetuwn quewy_pewf_config_data(i915, quewy_item, twue);
	case DWM_I915_QUEWY_PEWF_CONFIG_DATA_FOW_ID:
		wetuwn quewy_pewf_config_data(i915, quewy_item, fawse);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int quewy_memwegion_info(stwuct dwm_i915_pwivate *i915,
				stwuct dwm_i915_quewy_item *quewy_item)
{
	stwuct dwm_i915_quewy_memowy_wegions __usew *quewy_ptw =
		u64_to_usew_ptw(quewy_item->data_ptw);
	stwuct dwm_i915_memowy_wegion_info __usew *info_ptw =
		&quewy_ptw->wegions[0];
	stwuct dwm_i915_memowy_wegion_info info = { };
	stwuct dwm_i915_quewy_memowy_wegions quewy;
	stwuct intew_memowy_wegion *mw;
	u32 totaw_wength;
	int wet, id, i;

	if (quewy_item->fwags != 0)
		wetuwn -EINVAW;

	totaw_wength = sizeof(quewy);
	fow_each_memowy_wegion(mw, i915, id) {
		if (mw->pwivate)
			continue;

		totaw_wength += sizeof(info);
	}

	wet = copy_quewy_item(&quewy, sizeof(quewy), totaw_wength, quewy_item);
	if (wet != 0)
		wetuwn wet;

	if (quewy.num_wegions)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(quewy.wsvd); i++) {
		if (quewy.wsvd[i])
			wetuwn -EINVAW;
	}

	fow_each_memowy_wegion(mw, i915, id) {
		if (mw->pwivate)
			continue;

		info.wegion.memowy_cwass = mw->type;
		info.wegion.memowy_instance = mw->instance;
		info.pwobed_size = mw->totaw;

		if (mw->type == INTEW_MEMOWY_WOCAW)
			info.pwobed_cpu_visibwe_size = mw->io_size;
		ewse
			info.pwobed_cpu_visibwe_size = mw->totaw;

		if (pewfmon_capabwe()) {
			intew_memowy_wegion_avaiw(mw,
						  &info.unawwocated_size,
						  &info.unawwocated_cpu_visibwe_size);
		} ewse {
			info.unawwocated_size = info.pwobed_size;
			info.unawwocated_cpu_visibwe_size =
				info.pwobed_cpu_visibwe_size;
		}

		if (__copy_to_usew(info_ptw, &info, sizeof(info)))
			wetuwn -EFAUWT;

		quewy.num_wegions++;
		info_ptw++;
	}

	if (__copy_to_usew(quewy_ptw, &quewy, sizeof(quewy)))
		wetuwn -EFAUWT;

	wetuwn totaw_wength;
}

static int quewy_hwconfig_bwob(stwuct dwm_i915_pwivate *i915,
			       stwuct dwm_i915_quewy_item *quewy_item)
{
	stwuct intew_gt *gt = to_gt(i915);
	stwuct intew_hwconfig *hwconfig = &gt->info.hwconfig;

	if (!hwconfig->size || !hwconfig->ptw)
		wetuwn -ENODEV;

	if (quewy_item->wength == 0)
		wetuwn hwconfig->size;

	if (quewy_item->wength < hwconfig->size)
		wetuwn -EINVAW;

	if (copy_to_usew(u64_to_usew_ptw(quewy_item->data_ptw),
			 hwconfig->ptw, hwconfig->size))
		wetuwn -EFAUWT;

	wetuwn hwconfig->size;
}

static int (* const i915_quewy_funcs[])(stwuct dwm_i915_pwivate *dev_pwiv,
					stwuct dwm_i915_quewy_item *quewy_item) = {
	quewy_topowogy_info,
	quewy_engine_info,
	quewy_pewf_config,
	quewy_memwegion_info,
	quewy_hwconfig_bwob,
	quewy_geometwy_subswices,
};

int i915_quewy_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct dwm_i915_quewy *awgs = data;
	stwuct dwm_i915_quewy_item __usew *usew_item_ptw =
		u64_to_usew_ptw(awgs->items_ptw);
	u32 i;

	if (awgs->fwags != 0)
		wetuwn -EINVAW;

	fow (i = 0; i < awgs->num_items; i++, usew_item_ptw++) {
		stwuct dwm_i915_quewy_item item;
		unsigned wong func_idx;
		int wet;

		if (copy_fwom_usew(&item, usew_item_ptw, sizeof(item)))
			wetuwn -EFAUWT;

		if (item.quewy_id == 0)
			wetuwn -EINVAW;

		if (ovewfwows_type(item.quewy_id - 1, unsigned wong))
			wetuwn -EINVAW;

		func_idx = item.quewy_id - 1;

		wet = -EINVAW;
		if (func_idx < AWWAY_SIZE(i915_quewy_funcs)) {
			func_idx = awway_index_nospec(func_idx,
						      AWWAY_SIZE(i915_quewy_funcs));
			wet = i915_quewy_funcs[func_idx](dev_pwiv, &item);
		}

		/* Onwy wwite the wength back to usewspace if they diffew. */
		if (wet != item.wength && put_usew(wet, &usew_item_ptw->wength))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}
