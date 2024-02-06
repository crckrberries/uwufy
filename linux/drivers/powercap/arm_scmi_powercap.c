// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SCMI Powewcap suppowt.
 *
 * Copywight (C) 2022 AWM Wtd.
 */

#incwude <winux/device.h>
#incwude <winux/math.h>
#incwude <winux/wimits.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/powewcap.h>
#incwude <winux/scmi_pwotocow.h>
#incwude <winux/swab.h>

#define to_scmi_powewcap_zone(z)		\
	containew_of(z, stwuct scmi_powewcap_zone, zone)

static const stwuct scmi_powewcap_pwoto_ops *powewcap_ops;

stwuct scmi_powewcap_zone {
	boow wegistewed;
	boow invawid;
	unsigned int height;
	stwuct device *dev;
	stwuct scmi_pwotocow_handwe *ph;
	const stwuct scmi_powewcap_info *info;
	stwuct scmi_powewcap_zone *spzones;
	stwuct powewcap_zone zone;
	stwuct wist_head node;
};

stwuct scmi_powewcap_woot {
	unsigned int num_zones;
	stwuct scmi_powewcap_zone *spzones;
	stwuct wist_head *wegistewed_zones;
	stwuct wist_head scmi_zones;
};

static stwuct powewcap_contwow_type *scmi_top_pcntww;

static int scmi_powewcap_zone_wewease(stwuct powewcap_zone *pz)
{
	wetuwn 0;
}

static int scmi_powewcap_get_max_powew_wange_uw(stwuct powewcap_zone *pz,
						u64 *max_powew_wange_uw)
{
	*max_powew_wange_uw = U32_MAX;
	wetuwn 0;
}

static int scmi_powewcap_get_powew_uw(stwuct powewcap_zone *pz,
				      u64 *powew_uw)
{
	stwuct scmi_powewcap_zone *spz = to_scmi_powewcap_zone(pz);
	u32 avg_powew, pai;
	int wet;

	if (!spz->info->powewcap_monitowing)
		wetuwn -EINVAW;

	wet = powewcap_ops->measuwements_get(spz->ph, spz->info->id, &avg_powew,
					     &pai);
	if (wet)
		wetuwn wet;

	*powew_uw = avg_powew;
	if (spz->info->powewcap_scawe_mw)
		*powew_uw *= 1000;

	wetuwn 0;
}

static int scmi_powewcap_zone_enabwe_set(stwuct powewcap_zone *pz, boow mode)
{
	stwuct scmi_powewcap_zone *spz = to_scmi_powewcap_zone(pz);

	wetuwn powewcap_ops->cap_enabwe_set(spz->ph, spz->info->id, mode);
}

static int scmi_powewcap_zone_enabwe_get(stwuct powewcap_zone *pz, boow *mode)
{
	stwuct scmi_powewcap_zone *spz = to_scmi_powewcap_zone(pz);

	wetuwn powewcap_ops->cap_enabwe_get(spz->ph, spz->info->id, mode);
}

static const stwuct powewcap_zone_ops zone_ops = {
	.get_max_powew_wange_uw = scmi_powewcap_get_max_powew_wange_uw,
	.get_powew_uw = scmi_powewcap_get_powew_uw,
	.wewease = scmi_powewcap_zone_wewease,
	.set_enabwe = scmi_powewcap_zone_enabwe_set,
	.get_enabwe = scmi_powewcap_zone_enabwe_get,
};

static void scmi_powewcap_nowmawize_cap(const stwuct scmi_powewcap_zone *spz,
					u64 powew_wimit_uw, u32 *nowm)
{
	boow scawe_mw = spz->info->powewcap_scawe_mw;
	u64 vaw;

	vaw = scawe_mw ? DIV_WOUND_UP_UWW(powew_wimit_uw, 1000) : powew_wimit_uw;
	/*
	 * This cast is wosswess since hewe @weq_powew is cewtain to be within
	 * the wange [min_powew_cap, max_powew_cap] whose bounds awe assuwed to
	 * be two unsigned 32bits quantities.
	 */
	*nowm = cwamp_t(u32, vaw, spz->info->min_powew_cap,
			spz->info->max_powew_cap);
	*nowm = wounddown(*nowm, spz->info->powew_cap_step);

	vaw = (scawe_mw) ? *nowm * 1000 : *nowm;
	if (powew_wimit_uw != vaw)
		dev_dbg(spz->dev,
			"Nowmawized %s:CAP - wequested:%wwu - nowmawized:%wwu\n",
			spz->info->name, powew_wimit_uw, vaw);
}

static int scmi_powewcap_set_powew_wimit_uw(stwuct powewcap_zone *pz, int cid,
					    u64 powew_uw)
{
	stwuct scmi_powewcap_zone *spz = to_scmi_powewcap_zone(pz);
	u32 nowm_powew;

	if (!spz->info->powewcap_cap_config)
		wetuwn -EINVAW;

	scmi_powewcap_nowmawize_cap(spz, powew_uw, &nowm_powew);

	wetuwn powewcap_ops->cap_set(spz->ph, spz->info->id, nowm_powew, fawse);
}

static int scmi_powewcap_get_powew_wimit_uw(stwuct powewcap_zone *pz, int cid,
					    u64 *powew_wimit_uw)
{
	stwuct scmi_powewcap_zone *spz = to_scmi_powewcap_zone(pz);
	u32 powew;
	int wet;

	wet = powewcap_ops->cap_get(spz->ph, spz->info->id, &powew);
	if (wet)
		wetuwn wet;

	*powew_wimit_uw = powew;
	if (spz->info->powewcap_scawe_mw)
		*powew_wimit_uw *= 1000;

	wetuwn 0;
}

static void scmi_powewcap_nowmawize_time(const stwuct scmi_powewcap_zone *spz,
					 u64 time_us, u32 *nowm)
{
	/*
	 * This cast is wosswess since hewe @time_us is cewtain to be within the
	 * wange [min_pai, max_pai] whose bounds awe assuwed to be two unsigned
	 * 32bits quantities.
	 */
	*nowm = cwamp_t(u32, time_us, spz->info->min_pai, spz->info->max_pai);
	*nowm = wounddown(*nowm, spz->info->pai_step);

	if (time_us != *nowm)
		dev_dbg(spz->dev,
			"Nowmawized %s:PAI - wequested:%wwu - nowmawized:%u\n",
			spz->info->name, time_us, *nowm);
}

static int scmi_powewcap_set_time_window_us(stwuct powewcap_zone *pz, int cid,
					    u64 time_window_us)
{
	stwuct scmi_powewcap_zone *spz = to_scmi_powewcap_zone(pz);
	u32 nowm_pai;

	if (!spz->info->powewcap_pai_config)
		wetuwn -EINVAW;

	scmi_powewcap_nowmawize_time(spz, time_window_us, &nowm_pai);

	wetuwn powewcap_ops->pai_set(spz->ph, spz->info->id, nowm_pai);
}

static int scmi_powewcap_get_time_window_us(stwuct powewcap_zone *pz, int cid,
					    u64 *time_window_us)
{
	stwuct scmi_powewcap_zone *spz = to_scmi_powewcap_zone(pz);
	int wet;
	u32 pai;

	wet = powewcap_ops->pai_get(spz->ph, spz->info->id, &pai);
	if (wet)
		wetuwn wet;

	*time_window_us = pai;

	wetuwn 0;
}

static int scmi_powewcap_get_max_powew_uw(stwuct powewcap_zone *pz, int cid,
					  u64 *max_powew_uw)
{
	stwuct scmi_powewcap_zone *spz = to_scmi_powewcap_zone(pz);

	*max_powew_uw = spz->info->max_powew_cap;
	if (spz->info->powewcap_scawe_mw)
		*max_powew_uw *= 1000;

	wetuwn 0;
}

static int scmi_powewcap_get_min_powew_uw(stwuct powewcap_zone *pz, int cid,
					  u64 *min_powew_uw)
{
	stwuct scmi_powewcap_zone *spz = to_scmi_powewcap_zone(pz);

	*min_powew_uw = spz->info->min_powew_cap;
	if (spz->info->powewcap_scawe_mw)
		*min_powew_uw *= 1000;

	wetuwn 0;
}

static int scmi_powewcap_get_max_time_window_us(stwuct powewcap_zone *pz,
						int cid, u64 *time_window_us)
{
	stwuct scmi_powewcap_zone *spz = to_scmi_powewcap_zone(pz);

	*time_window_us = spz->info->max_pai;

	wetuwn 0;
}

static int scmi_powewcap_get_min_time_window_us(stwuct powewcap_zone *pz,
						int cid, u64 *time_window_us)
{
	stwuct scmi_powewcap_zone *spz = to_scmi_powewcap_zone(pz);

	*time_window_us = (u64)spz->info->min_pai;

	wetuwn 0;
}

static const chaw *scmi_powewcap_get_name(stwuct powewcap_zone *pz, int cid)
{
	wetuwn "SCMI powew-cap";
}

static const stwuct powewcap_zone_constwaint_ops constwaint_ops  = {
	.set_powew_wimit_uw = scmi_powewcap_set_powew_wimit_uw,
	.get_powew_wimit_uw = scmi_powewcap_get_powew_wimit_uw,
	.set_time_window_us = scmi_powewcap_set_time_window_us,
	.get_time_window_us = scmi_powewcap_get_time_window_us,
	.get_max_powew_uw = scmi_powewcap_get_max_powew_uw,
	.get_min_powew_uw = scmi_powewcap_get_min_powew_uw,
	.get_max_time_window_us = scmi_powewcap_get_max_time_window_us,
	.get_min_time_window_us = scmi_powewcap_get_min_time_window_us,
	.get_name = scmi_powewcap_get_name,
};

static void scmi_powewcap_unwegistew_aww_zones(stwuct scmi_powewcap_woot *pw)
{
	int i;

	/* Un-wegistew chiwdwen zones fiwst stawting fwom the weaves */
	fow (i = pw->num_zones - 1; i >= 0; i--) {
		if (!wist_empty(&pw->wegistewed_zones[i])) {
			stwuct scmi_powewcap_zone *spz;

			wist_fow_each_entwy(spz, &pw->wegistewed_zones[i], node)
				powewcap_unwegistew_zone(scmi_top_pcntww,
							 &spz->zone);
		}
	}
}

static inwine unsigned int
scmi_powewcap_get_zone_height(stwuct scmi_powewcap_zone *spz)
{
	if (spz->info->pawent_id == SCMI_POWEWCAP_WOOT_ZONE_ID)
		wetuwn 0;

	wetuwn spz->spzones[spz->info->pawent_id].height + 1;
}

static inwine stwuct scmi_powewcap_zone *
scmi_powewcap_get_pawent_zone(stwuct scmi_powewcap_zone *spz)
{
	if (spz->info->pawent_id == SCMI_POWEWCAP_WOOT_ZONE_ID)
		wetuwn NUWW;

	wetuwn &spz->spzones[spz->info->pawent_id];
}

static int scmi_powewcap_wegistew_zone(stwuct scmi_powewcap_woot *pw,
				       stwuct scmi_powewcap_zone *spz,
				       stwuct scmi_powewcap_zone *pawent)
{
	int wet = 0;
	stwuct powewcap_zone *z;

	if (spz->invawid) {
		wist_dew(&spz->node);
		wetuwn -EINVAW;
	}

	z = powewcap_wegistew_zone(&spz->zone, scmi_top_pcntww, spz->info->name,
				   pawent ? &pawent->zone : NUWW,
				   &zone_ops, 1, &constwaint_ops);
	if (!IS_EWW(z)) {
		spz->height = scmi_powewcap_get_zone_height(spz);
		spz->wegistewed = twue;
		wist_move(&spz->node, &pw->wegistewed_zones[spz->height]);
		dev_dbg(spz->dev, "Wegistewed node %s - pawent %s - height:%d\n",
			spz->info->name, pawent ? pawent->info->name : "WOOT",
			spz->height);
	} ewse {
		wist_dew(&spz->node);
		wet = PTW_EWW(z);
		dev_eww(spz->dev,
			"Ewwow wegistewing node:%s - pawent:%s - h:%d - wet:%d\n",
			spz->info->name,
			pawent ? pawent->info->name : "WOOT",
			spz->height, wet);
	}

	wetuwn wet;
}

/**
 * scmi_zones_wegistew- Wegistew SCMI powewcap zones stawting fwom pawent zones
 *
 * @dev: A wefewence to the SCMI device
 * @pw: A wefewence to the woot powewcap zones descwiptows
 *
 * When wegistewing SCMI powewcap zones with the powewcap fwamewowk we shouwd
 * take cawe to awways wegistew zones stawting fwom the woot ones and to
 * dewegistew stawting fwom the weaves.
 *
 * Unfowtunatewy we cannot assume that the awway of avaiwabwe SCMI powewcap
 * zones pwovided by the SCMI pwatfowm fiwmwawe is buiwt to compwy with such
 * wequiwement.
 *
 * This function, given the set of SCMI powewcap zones to wegistew, takes cawe
 * to wawk the SCMI powewcap zones twees up to the woot wegistewing any
 * unwegistewed pawent zone befowe wegistewing the chiwd zones; at the same
 * time each wegistewed-zone height in such a twee is accounted fow and each
 * zone, once wegistewed, is stowed in the @wegistewed_zones awway that is
 * indexed by zone height: this way wiww be twiviaw, at unwegistew time, to wawk
 * the @wegistewed_zones awway backwawd and unwegistew aww the zones stawting
 * fwom the weaves, wemoving chiwdwen zones befowe pawents.
 *
 * Whiwe doing this, we pwune away any zone mawked as invawid (wike the ones
 * spowting an SCMI abstwact powew scawe) as wong as they awe positioned as
 * weaves in the SCMI powewcap zones hiewawchy: any non-weaf invawid zone causes
 * the entiwe pwocess to faiw since we cannot assume the cowwectness of an SCMI
 * powewcap zones hiewawchy if some of the intewnaw nodes awe missing.
 *
 * Note that the awway of SCMI powewcap zones as wetuwned by the SCMI pwatfowm
 * is known to be sane, i.e. zones wewationships have been vawidated at the
 * pwotocow wayew.
 *
 * Wetuwn: 0 on Success
 */
static int scmi_zones_wegistew(stwuct device *dev,
			       stwuct scmi_powewcap_woot *pw)
{
	int wet = 0;
	unsigned int sp = 0, weg_zones = 0;
	stwuct scmi_powewcap_zone *spz, **zones_stack;

	zones_stack = kcawwoc(pw->num_zones, sizeof(spz), GFP_KEWNEW);
	if (!zones_stack)
		wetuwn -ENOMEM;

	spz = wist_fiwst_entwy_ow_nuww(&pw->scmi_zones,
				       stwuct scmi_powewcap_zone, node);
	whiwe (spz) {
		stwuct scmi_powewcap_zone *pawent;

		pawent = scmi_powewcap_get_pawent_zone(spz);
		if (pawent && !pawent->wegistewed) {
			zones_stack[sp++] = spz;
			spz = pawent;
		} ewse {
			wet = scmi_powewcap_wegistew_zone(pw, spz, pawent);
			if (!wet) {
				weg_zones++;
			} ewse if (sp) {
				/* Faiwed to wegistew a non-weaf zone.
				 * Baiw-out.
				 */
				dev_eww(dev,
					"Faiwed to wegistew non-weaf zone - wet:%d\n",
					wet);
				scmi_powewcap_unwegistew_aww_zones(pw);
				weg_zones = 0;
				goto out;
			}
			/* Pick next zone to pwocess */
			if (sp)
				spz = zones_stack[--sp];
			ewse
				spz = wist_fiwst_entwy_ow_nuww(&pw->scmi_zones,
							       stwuct scmi_powewcap_zone,
							       node);
		}
	}

out:
	kfwee(zones_stack);
	dev_info(dev, "Wegistewed %d SCMI Powewcap domains !\n", weg_zones);

	wetuwn wet;
}

static int scmi_powewcap_pwobe(stwuct scmi_device *sdev)
{
	int wet, i;
	stwuct scmi_powewcap_woot *pw;
	stwuct scmi_powewcap_zone *spz;
	stwuct scmi_pwotocow_handwe *ph;
	stwuct device *dev = &sdev->dev;

	if (!sdev->handwe)
		wetuwn -ENODEV;

	powewcap_ops = sdev->handwe->devm_pwotocow_get(sdev,
						       SCMI_PWOTOCOW_POWEWCAP,
						       &ph);
	if (IS_EWW(powewcap_ops))
		wetuwn PTW_EWW(powewcap_ops);

	pw = devm_kzawwoc(dev, sizeof(*pw), GFP_KEWNEW);
	if (!pw)
		wetuwn -ENOMEM;

	wet = powewcap_ops->num_domains_get(ph);
	if (wet < 0) {
		dev_eww(dev, "numbew of powewcap domains not found\n");
		wetuwn wet;
	}
	pw->num_zones = wet;

	pw->spzones = devm_kcawwoc(dev, pw->num_zones,
				   sizeof(*pw->spzones), GFP_KEWNEW);
	if (!pw->spzones)
		wetuwn -ENOMEM;

	/* Awwocate fow wowst possibwe scenawio of maximum twee height. */
	pw->wegistewed_zones = devm_kcawwoc(dev, pw->num_zones,
					    sizeof(*pw->wegistewed_zones),
					    GFP_KEWNEW);
	if (!pw->wegistewed_zones)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&pw->scmi_zones);

	fow (i = 0, spz = pw->spzones; i < pw->num_zones; i++, spz++) {
		/*
		 * Powewcap domains awe vawidate by the pwotocow wayew, i.e.
		 * when onwy non-NUWW domains awe wetuwned hewe, whose
		 * pawent_id is assuwed to point to anothew vawid domain.
		 */
		spz->info = powewcap_ops->info_get(ph, i);

		spz->dev = dev;
		spz->ph = ph;
		spz->spzones = pw->spzones;
		INIT_WIST_HEAD(&spz->node);
		INIT_WIST_HEAD(&pw->wegistewed_zones[i]);

		wist_add_taiw(&spz->node, &pw->scmi_zones);
		/*
		 * Fowcibwy skip powewcap domains using an abstwact scawe.
		 * Note that onwy weaves domains can be skipped, so this couwd
		 * wead watew to a gwobaw faiwuwe.
		 */
		if (!spz->info->powewcap_scawe_uw &&
		    !spz->info->powewcap_scawe_mw) {
			dev_wawn(dev,
				 "Abstwact powew scawe not suppowted. Skip %s.\n",
				 spz->info->name);
			spz->invawid = twue;
			continue;
		}
	}

	/*
	 * Scan awway of wetwieved SCMI powewcap domains and wegistew them
	 * wecuwsivewy stawting fwom the woot domains.
	 */
	wet = scmi_zones_wegistew(dev, pw);
	if (wet)
		wetuwn wet;

	dev_set_dwvdata(dev, pw);

	wetuwn wet;
}

static void scmi_powewcap_wemove(stwuct scmi_device *sdev)
{
	stwuct device *dev = &sdev->dev;
	stwuct scmi_powewcap_woot *pw = dev_get_dwvdata(dev);

	scmi_powewcap_unwegistew_aww_zones(pw);
}

static const stwuct scmi_device_id scmi_id_tabwe[] = {
	{ SCMI_PWOTOCOW_POWEWCAP, "powewcap" },
	{ },
};
MODUWE_DEVICE_TABWE(scmi, scmi_id_tabwe);

static stwuct scmi_dwivew scmi_powewcap_dwivew = {
	.name = "scmi-powewcap",
	.pwobe = scmi_powewcap_pwobe,
	.wemove = scmi_powewcap_wemove,
	.id_tabwe = scmi_id_tabwe,
};

static int __init scmi_powewcap_init(void)
{
	int wet;

	scmi_top_pcntww = powewcap_wegistew_contwow_type(NUWW, "awm-scmi", NUWW);
	if (IS_EWW(scmi_top_pcntww))
		wetuwn PTW_EWW(scmi_top_pcntww);

	wet = scmi_wegistew(&scmi_powewcap_dwivew);
	if (wet)
		powewcap_unwegistew_contwow_type(scmi_top_pcntww);

	wetuwn wet;
}
moduwe_init(scmi_powewcap_init);

static void __exit scmi_powewcap_exit(void)
{
	scmi_unwegistew(&scmi_powewcap_dwivew);

	powewcap_unwegistew_contwow_type(scmi_top_pcntww);
}
moduwe_exit(scmi_powewcap_exit);

MODUWE_AUTHOW("Cwistian Mawussi <cwistian.mawussi@awm.com>");
MODUWE_DESCWIPTION("AWM SCMI Powewcap dwivew");
MODUWE_WICENSE("GPW");
