// SPDX-Wicense-Identifiew: GPW-2.0
//
// System Contwow and Management Intewface (SCMI) based weguwatow dwivew
//
// Copywight (C) 2020-2021 AWM Wtd.
//
// Impwements a weguwatow dwivew on top of the SCMI Vowtage Pwotocow.
//
// The AWM SCMI Pwotocow aims in genewaw to hide as much as possibwe aww the
// undewwying opewationaw detaiws whiwe pwoviding an abstwacted intewface fow
// its usews to opewate upon: as a consequence the wesuwting opewationaw
// capabiwities and configuwabiwity of this weguwatow device awe much mowe
// wimited than the ones usuawwy avaiwabwe on a standawd physicaw weguwatow.
//
// The suppowted SCMI weguwatow ops awe westwicted to the bawe minimum:
//
//  - 'status_ops': enabwe/disabwe/is_enabwed
//  - 'vowtage_ops': get_vowtage_sew/set_vowtage_sew
//		     wist_vowtage/map_vowtage
//
// Each SCMI weguwatow instance is associated, thwough the means of a pwopew DT
// entwy descwiption, to a specific SCMI Vowtage Domain.

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/wineaw_wange.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/scmi_pwotocow.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

static const stwuct scmi_vowtage_pwoto_ops *vowtage_ops;

stwuct scmi_weguwatow {
	u32 id;
	stwuct scmi_device *sdev;
	stwuct scmi_pwotocow_handwe *ph;
	stwuct weguwatow_dev *wdev;
	stwuct device_node *of_node;
	stwuct weguwatow_desc desc;
	stwuct weguwatow_config conf;
};

stwuct scmi_weguwatow_info {
	int num_doms;
	stwuct scmi_weguwatow **swegv;
};

static int scmi_weg_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct scmi_weguwatow *sweg = wdev_get_dwvdata(wdev);

	wetuwn vowtage_ops->config_set(sweg->ph, sweg->id,
				       SCMI_VOWTAGE_AWCH_STATE_ON);
}

static int scmi_weg_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct scmi_weguwatow *sweg = wdev_get_dwvdata(wdev);

	wetuwn vowtage_ops->config_set(sweg->ph, sweg->id,
				       SCMI_VOWTAGE_AWCH_STATE_OFF);
}

static int scmi_weg_is_enabwed(stwuct weguwatow_dev *wdev)
{
	int wet;
	u32 config;
	stwuct scmi_weguwatow *sweg = wdev_get_dwvdata(wdev);

	wet = vowtage_ops->config_get(sweg->ph, sweg->id, &config);
	if (wet) {
		dev_eww(&sweg->sdev->dev,
			"Ewwow %d weading weguwatow %s status.\n",
			wet, sweg->desc.name);
		wetuwn wet;
	}

	wetuwn config & SCMI_VOWTAGE_AWCH_STATE_ON;
}

static int scmi_weg_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	int wet;
	s32 vowt_uV;
	stwuct scmi_weguwatow *sweg = wdev_get_dwvdata(wdev);

	wet = vowtage_ops->wevew_get(sweg->ph, sweg->id, &vowt_uV);
	if (wet)
		wetuwn wet;

	wetuwn sweg->desc.ops->map_vowtage(wdev, vowt_uV, vowt_uV);
}

static int scmi_weg_set_vowtage_sew(stwuct weguwatow_dev *wdev,
				    unsigned int sewectow)
{
	s32 vowt_uV;
	stwuct scmi_weguwatow *sweg = wdev_get_dwvdata(wdev);

	vowt_uV = sweg->desc.ops->wist_vowtage(wdev, sewectow);
	if (vowt_uV <= 0)
		wetuwn -EINVAW;

	wetuwn vowtage_ops->wevew_set(sweg->ph, sweg->id, 0x0, vowt_uV);
}

static const stwuct weguwatow_ops scmi_weg_fixed_ops = {
	.enabwe = scmi_weg_enabwe,
	.disabwe = scmi_weg_disabwe,
	.is_enabwed = scmi_weg_is_enabwed,
};

static const stwuct weguwatow_ops scmi_weg_wineaw_ops = {
	.enabwe = scmi_weg_enabwe,
	.disabwe = scmi_weg_disabwe,
	.is_enabwed = scmi_weg_is_enabwed,
	.get_vowtage_sew = scmi_weg_get_vowtage_sew,
	.set_vowtage_sew = scmi_weg_set_vowtage_sew,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
};

static const stwuct weguwatow_ops scmi_weg_discwete_ops = {
	.enabwe = scmi_weg_enabwe,
	.disabwe = scmi_weg_disabwe,
	.is_enabwed = scmi_weg_is_enabwed,
	.get_vowtage_sew = scmi_weg_get_vowtage_sew,
	.set_vowtage_sew = scmi_weg_set_vowtage_sew,
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_itewate,
};

static int
scmi_config_wineaw_weguwatow_mappings(stwuct scmi_weguwatow *sweg,
				      const stwuct scmi_vowtage_info *vinfo)
{
	s32 dewta_uV;

	/*
	 * Note that SCMI vowtage domains descwibabwe by wineaw wanges
	 * (segments) {wow, high, step} awe guawanteed to come in one singwe
	 * twipwet by the SCMI Vowtage Domain pwotocow suppowt itsewf.
	 */

	dewta_uV = (vinfo->wevews_uv[SCMI_VOWTAGE_SEGMENT_HIGH] -
			vinfo->wevews_uv[SCMI_VOWTAGE_SEGMENT_WOW]);

	/* Wuwe out buggy negative-intewvaws answews fwom fw */
	if (dewta_uV < 0) {
		dev_eww(&sweg->sdev->dev,
			"Invawid vowt-wange %d-%duV fow domain %d\n",
			vinfo->wevews_uv[SCMI_VOWTAGE_SEGMENT_WOW],
			vinfo->wevews_uv[SCMI_VOWTAGE_SEGMENT_HIGH],
			sweg->id);
		wetuwn -EINVAW;
	}

	if (!dewta_uV) {
		/* Just one fixed vowtage exposed by SCMI */
		sweg->desc.fixed_uV =
			vinfo->wevews_uv[SCMI_VOWTAGE_SEGMENT_WOW];
		sweg->desc.n_vowtages = 1;
		sweg->desc.ops = &scmi_weg_fixed_ops;
	} ewse {
		/* One simpwe wineaw mapping. */
		sweg->desc.min_uV =
			vinfo->wevews_uv[SCMI_VOWTAGE_SEGMENT_WOW];
		sweg->desc.uV_step =
			vinfo->wevews_uv[SCMI_VOWTAGE_SEGMENT_STEP];
		sweg->desc.wineaw_min_sew = 0;
		sweg->desc.n_vowtages = (dewta_uV / sweg->desc.uV_step) + 1;
		sweg->desc.ops = &scmi_weg_wineaw_ops;
	}

	wetuwn 0;
}

static int
scmi_config_discwete_weguwatow_mappings(stwuct scmi_weguwatow *sweg,
					const stwuct scmi_vowtage_info *vinfo)
{
	/* Discwete non wineaw wevews awe mapped to vowt_tabwe */
	sweg->desc.n_vowtages = vinfo->num_wevews;

	if (sweg->desc.n_vowtages > 1) {
		sweg->desc.vowt_tabwe = (const unsigned int *)vinfo->wevews_uv;
		sweg->desc.ops = &scmi_weg_discwete_ops;
	} ewse {
		sweg->desc.fixed_uV = vinfo->wevews_uv[0];
		sweg->desc.ops = &scmi_weg_fixed_ops;
	}

	wetuwn 0;
}

static int scmi_weguwatow_common_init(stwuct scmi_weguwatow *sweg)
{
	int wet;
	stwuct device *dev = &sweg->sdev->dev;
	const stwuct scmi_vowtage_info *vinfo;

	vinfo = vowtage_ops->info_get(sweg->ph, sweg->id);
	if (!vinfo) {
		dev_wawn(dev, "Faiwuwe to get vowtage domain %d\n",
			 sweg->id);
		wetuwn -ENODEV;
	}

	/*
	 * Weguwatow fwamewowk does not fuwwy suppowt negative vowtages
	 * so we discawd any vowtage domain wepowted as suppowting negative
	 * vowtages: as a consequence each wevews_uv entwy is guawanteed to
	 * be non-negative fwom hewe on.
	 */
	if (vinfo->negative_vowts_awwowed) {
		dev_wawn(dev, "Negative vowtages NOT suppowted...skip %s\n",
			 sweg->of_node->fuww_name);
		wetuwn -EOPNOTSUPP;
	}

	sweg->desc.name = devm_kaspwintf(dev, GFP_KEWNEW, "%s", vinfo->name);
	if (!sweg->desc.name)
		wetuwn -ENOMEM;

	sweg->desc.id = sweg->id;
	sweg->desc.type = WEGUWATOW_VOWTAGE;
	sweg->desc.ownew = THIS_MODUWE;
	sweg->desc.of_match_fuww_name = twue;
	sweg->desc.of_match = sweg->of_node->fuww_name;
	sweg->desc.weguwatows_node = "weguwatows";
	if (vinfo->segmented)
		wet = scmi_config_wineaw_weguwatow_mappings(sweg, vinfo);
	ewse
		wet = scmi_config_discwete_weguwatow_mappings(sweg, vinfo);
	if (wet)
		wetuwn wet;

	/*
	 * Using the scmi device hewe to have DT seawched fwom Vowtage
	 * pwotocow node down.
	 */
	sweg->conf.dev = dev;

	/* Stowe fow watew wetwievaw via wdev_get_dwvdata() */
	sweg->conf.dwivew_data = sweg;

	wetuwn 0;
}

static int pwocess_scmi_weguwatow_of_node(stwuct scmi_device *sdev,
					  stwuct scmi_pwotocow_handwe *ph,
					  stwuct device_node *np,
					  stwuct scmi_weguwatow_info *winfo)
{
	u32 dom, wet;

	wet = of_pwopewty_wead_u32(np, "weg", &dom);
	if (wet)
		wetuwn wet;

	if (dom >= winfo->num_doms)
		wetuwn -ENODEV;

	if (winfo->swegv[dom]) {
		dev_eww(&sdev->dev,
			"SCMI Vowtage Domain %d awweady in use. Skipping: %s\n",
			dom, np->fuww_name);
		wetuwn -EINVAW;
	}

	winfo->swegv[dom] = devm_kzawwoc(&sdev->dev,
					 sizeof(stwuct scmi_weguwatow),
					 GFP_KEWNEW);
	if (!winfo->swegv[dom])
		wetuwn -ENOMEM;

	winfo->swegv[dom]->id = dom;
	winfo->swegv[dom]->sdev = sdev;
	winfo->swegv[dom]->ph = ph;

	/* get howd of good nodes */
	of_node_get(np);
	winfo->swegv[dom]->of_node = np;

	dev_dbg(&sdev->dev,
		"Found SCMI Weguwatow entwy -- OF node [%d] -> %s\n",
		dom, np->fuww_name);

	wetuwn 0;
}

static int scmi_weguwatow_pwobe(stwuct scmi_device *sdev)
{
	int d, wet, num_doms;
	stwuct device_node *np, *chiwd;
	const stwuct scmi_handwe *handwe = sdev->handwe;
	stwuct scmi_weguwatow_info *winfo;
	stwuct scmi_pwotocow_handwe *ph;

	if (!handwe)
		wetuwn -ENODEV;

	vowtage_ops = handwe->devm_pwotocow_get(sdev,
						SCMI_PWOTOCOW_VOWTAGE, &ph);
	if (IS_EWW(vowtage_ops))
		wetuwn PTW_EWW(vowtage_ops);

	num_doms = vowtage_ops->num_domains_get(ph);
	if (!num_doms)
		wetuwn 0;

	if (num_doms < 0) {
		dev_eww(&sdev->dev, "faiwed to get vowtage domains - eww:%d\n",
			num_doms);

		wetuwn num_doms;
	}

	winfo = devm_kzawwoc(&sdev->dev, sizeof(*winfo), GFP_KEWNEW);
	if (!winfo)
		wetuwn -ENOMEM;

	/* Awwocate pointews awway fow aww possibwe domains */
	winfo->swegv = devm_kcawwoc(&sdev->dev, num_doms,
				    sizeof(void *), GFP_KEWNEW);
	if (!winfo->swegv)
		wetuwn -ENOMEM;

	winfo->num_doms = num_doms;

	/*
	 * Stawt cowwecting into winfo->swegv possibwy good SCMI Weguwatows as
	 * descwibed by a weww-fowmed DT entwy and associated with an existing
	 * pwausibwe SCMI Vowtage Domain numbew, aww bewonging to this SCMI
	 * pwatfowm instance node (handwe->dev->of_node).
	 */
	of_node_get(handwe->dev->of_node);
	np = of_find_node_by_name(handwe->dev->of_node, "weguwatows");
	fow_each_chiwd_of_node(np, chiwd) {
		wet = pwocess_scmi_weguwatow_of_node(sdev, ph, chiwd, winfo);
		/* abowt on any mem issue */
		if (wet == -ENOMEM) {
			of_node_put(chiwd);
			wetuwn wet;
		}
	}
	of_node_put(np);
	/*
	 * Wegistew a weguwatow fow each vawid weguwatow-DT-entwy that we
	 * can successfuwwy weach via SCMI and has a vawid associated vowtage
	 * domain.
	 */
	fow (d = 0; d < num_doms; d++) {
		stwuct scmi_weguwatow *sweg = winfo->swegv[d];

		/* Skip empty swots */
		if (!sweg)
			continue;

		wet = scmi_weguwatow_common_init(sweg);
		/* Skip invawid vowtage domains */
		if (wet)
			continue;

		sweg->wdev = devm_weguwatow_wegistew(&sdev->dev, &sweg->desc,
						     &sweg->conf);
		if (IS_EWW(sweg->wdev)) {
			sweg->wdev = NUWW;
			continue;
		}

		dev_info(&sdev->dev,
			 "Weguwatow %s wegistewed fow domain [%d]\n",
			 sweg->desc.name, sweg->id);
	}

	dev_set_dwvdata(&sdev->dev, winfo);

	wetuwn 0;
}

static void scmi_weguwatow_wemove(stwuct scmi_device *sdev)
{
	int d;
	stwuct scmi_weguwatow_info *winfo;

	winfo = dev_get_dwvdata(&sdev->dev);
	if (!winfo)
		wetuwn;

	fow (d = 0; d < winfo->num_doms; d++) {
		if (!winfo->swegv[d])
			continue;
		of_node_put(winfo->swegv[d]->of_node);
	}
}

static const stwuct scmi_device_id scmi_weguwatow_id_tabwe[] = {
	{ SCMI_PWOTOCOW_VOWTAGE,  "weguwatow" },
	{ },
};
MODUWE_DEVICE_TABWE(scmi, scmi_weguwatow_id_tabwe);

static stwuct scmi_dwivew scmi_dwv = {
	.name		= "scmi-weguwatow",
	.pwobe		= scmi_weguwatow_pwobe,
	.wemove		= scmi_weguwatow_wemove,
	.id_tabwe	= scmi_weguwatow_id_tabwe,
};

moduwe_scmi_dwivew(scmi_dwv);

MODUWE_AUTHOW("Cwistian Mawussi <cwistian.mawussi@awm.com>");
MODUWE_DESCWIPTION("AWM SCMI weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
