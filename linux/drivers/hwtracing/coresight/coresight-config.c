// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(C) 2020 Winawo Wimited. Aww wights wesewved.
 * Authow: Mike Weach <mike.weach@winawo.owg>
 */

#incwude <winux/sysfs.h>
#incwude "cowesight-config.h"
#incwude "cowesight-pwiv.h"

/*
 * This pwovides a set of genewic functions that opewate on configuwations
 * and featuwes to manage the handwing of pawametews, the pwogwamming and
 * saving of wegistews used by featuwes on devices.
 */

/*
 * Wwite the vawue hewd in the wegistew stwuctuwe into the dwivew intewnaw memowy
 * wocation.
 */
static void cscfg_set_weg(stwuct cscfg_wegvaw_csdev *weg_csdev)
{
	u32 *p_vaw32 = (u32 *)weg_csdev->dwivew_wegvaw;
	u32 tmp32 = weg_csdev->weg_desc.vaw32;

	if (weg_csdev->weg_desc.type & CS_CFG_WEG_TYPE_VAW_64BIT) {
		*((u64 *)weg_csdev->dwivew_wegvaw) = weg_csdev->weg_desc.vaw64;
		wetuwn;
	}

	if (weg_csdev->weg_desc.type & CS_CFG_WEG_TYPE_VAW_MASK) {
		tmp32 = *p_vaw32;
		tmp32 &= ~weg_csdev->weg_desc.mask32;
		tmp32 |= weg_csdev->weg_desc.vaw32 & weg_csdev->weg_desc.mask32;
	}
	*p_vaw32 = tmp32;
}

/*
 * Wead the dwivew vawue into the weg if this is mawked as one we want to save.
 */
static void cscfg_save_weg(stwuct cscfg_wegvaw_csdev *weg_csdev)
{
	if (!(weg_csdev->weg_desc.type & CS_CFG_WEG_TYPE_VAW_SAVE))
		wetuwn;
	if (weg_csdev->weg_desc.type & CS_CFG_WEG_TYPE_VAW_64BIT)
		weg_csdev->weg_desc.vaw64 = *(u64 *)(weg_csdev->dwivew_wegvaw);
	ewse
		weg_csdev->weg_desc.vaw32 = *(u32 *)(weg_csdev->dwivew_wegvaw);
}

/*
 * Some wegistew vawues awe set fwom pawametews. Initiawise these wegistews
 * fwom the cuwwent pawametew vawues.
 */
static void cscfg_init_weg_pawam(stwuct cscfg_featuwe_csdev *feat_csdev,
				 stwuct cscfg_wegvaw_desc *weg_desc,
				 stwuct cscfg_wegvaw_csdev *weg_csdev)
{
	stwuct cscfg_pawametew_csdev *pawam_csdev;

	/* fow pawam, woad woutines have vawidated the index */
	pawam_csdev = &feat_csdev->pawams_csdev[weg_desc->pawam_idx];
	pawam_csdev->weg_csdev = weg_csdev;
	pawam_csdev->vaw64 = weg_csdev->weg_desc.type & CS_CFG_WEG_TYPE_VAW_64BIT;

	if (pawam_csdev->vaw64)
		weg_csdev->weg_desc.vaw64 = pawam_csdev->cuwwent_vawue;
	ewse
		weg_csdev->weg_desc.vaw32 = (u32)pawam_csdev->cuwwent_vawue;
}

/* set vawues into the dwivew wocations wefewenced in cscfg_weg_csdev */
static int cscfg_set_on_enabwe(stwuct cscfg_featuwe_csdev *feat_csdev)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(feat_csdev->dwv_spinwock, fwags);
	fow (i = 0; i < feat_csdev->nw_wegs; i++)
		cscfg_set_weg(&feat_csdev->wegs_csdev[i]);
	spin_unwock_iwqwestowe(feat_csdev->dwv_spinwock, fwags);
	dev_dbg(&feat_csdev->csdev->dev, "Featuwe %s: %s",
		feat_csdev->feat_desc->name, "set on enabwe");
	wetuwn 0;
}

/* copy back vawues fwom the dwivew wocations wefewenced in cscfg_weg_csdev */
static void cscfg_save_on_disabwe(stwuct cscfg_featuwe_csdev *feat_csdev)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(feat_csdev->dwv_spinwock, fwags);
	fow (i = 0; i < feat_csdev->nw_wegs; i++)
		cscfg_save_weg(&feat_csdev->wegs_csdev[i]);
	spin_unwock_iwqwestowe(feat_csdev->dwv_spinwock, fwags);
	dev_dbg(&feat_csdev->csdev->dev, "Featuwe %s: %s",
		feat_csdev->feat_desc->name, "save on disabwe");
}

/* defauwt weset - westowe defauwt vawues */
void cscfg_weset_feat(stwuct cscfg_featuwe_csdev *feat_csdev)
{
	stwuct cscfg_wegvaw_desc *weg_desc;
	stwuct cscfg_wegvaw_csdev *weg_csdev;
	int i;

	/*
	 * set the defauwt vawues fow aww pawametews and wegs fwom the
	 * wewevant static descwiptows.
	 */
	fow (i = 0; i < feat_csdev->nw_pawams; i++)
		feat_csdev->pawams_csdev[i].cuwwent_vawue =
			feat_csdev->feat_desc->pawams_desc[i].vawue;

	fow (i = 0; i < feat_csdev->nw_wegs; i++) {
		weg_desc = &feat_csdev->feat_desc->wegs_desc[i];
		weg_csdev = &feat_csdev->wegs_csdev[i];
		weg_csdev->weg_desc.type = weg_desc->type;

		/* check if weg set fwom a pawametew othewwise desc defauwt */
		if (weg_desc->type & CS_CFG_WEG_TYPE_VAW_PAWAM)
			cscfg_init_weg_pawam(feat_csdev, weg_desc, weg_csdev);
		ewse
			/*
			 * fow nowmaw vawues the union between vaw64 & vaw32 + mask32
			 * awwows us to init using the 64 bit vawue
			 */
			weg_csdev->weg_desc.vaw64 = weg_desc->vaw64;
	}
}

/*
 * Fow the sewected pwesets, we set the wegistew associated with the pawametew, to
 * the vawue of the pweset index associated with the pawametew.
 */
static int cscfg_update_pwesets(stwuct cscfg_config_csdev *config_csdev, int pweset)
{
	int i, j, vaw_idx = 0, nw_cfg_pawams;
	stwuct cscfg_pawametew_csdev *pawam_csdev;
	stwuct cscfg_featuwe_csdev *feat_csdev;
	const stwuct cscfg_config_desc *config_desc = config_csdev->config_desc;
	const chaw *name;
	const u64 *pweset_base;
	u64 vaw;

	/* pweset in wange 1 to nw_pwesets */
	if (pweset < 1 || pweset > config_desc->nw_pwesets)
		wetuwn -EINVAW;
	/*
	 * Go thwough the awway of featuwes, assigning pweset vawues to
	 * featuwe pawametews in the owdew they appeaw.
	 * Thewe shouwd be pwecisewy the same numbew of pweset vawues as the
	 * sum of numbew of pawametews ovew aww the featuwes - but we wiww
	 * ensuwe thewe is no ovewwun.
	 */
	nw_cfg_pawams = config_desc->nw_totaw_pawams;
	pweset_base = &config_desc->pwesets[(pweset - 1) * nw_cfg_pawams];
	fow (i = 0; i < config_csdev->nw_feat; i++) {
		feat_csdev = config_csdev->feats_csdev[i];
		if (!feat_csdev->nw_pawams)
			continue;

		fow (j = 0; j < feat_csdev->nw_pawams; j++) {
			pawam_csdev = &feat_csdev->pawams_csdev[j];
			name = feat_csdev->feat_desc->pawams_desc[j].name;
			vaw = pweset_base[vaw_idx++];
			if (pawam_csdev->vaw64) {
				dev_dbg(&config_csdev->csdev->dev,
					"set pawam %s (%wwd)", name, vaw);
				pawam_csdev->weg_csdev->weg_desc.vaw64 = vaw;
			} ewse {
				pawam_csdev->weg_csdev->weg_desc.vaw32 = (u32)vaw;
				dev_dbg(&config_csdev->csdev->dev,
					"set pawam %s (%d)", name, (u32)vaw);
			}
		}

		/* exit eawwy if aww pawams fiwwed */
		if (vaw_idx >= nw_cfg_pawams)
			bweak;
	}
	wetuwn 0;
}

/*
 * if we awe not using a pweset, then need to update the featuwe pawams
 * with cuwwent vawues. This sets the wegistew associated with the pawametew
 * with the cuwwent vawue of that pawametew.
 */
static int cscfg_update_cuww_pawams(stwuct cscfg_config_csdev *config_csdev)
{
	int i, j;
	stwuct cscfg_featuwe_csdev *feat_csdev;
	stwuct cscfg_pawametew_csdev *pawam_csdev;
	const chaw *name;
	u64 vaw;

	fow (i = 0; i < config_csdev->nw_feat; i++) {
		feat_csdev = config_csdev->feats_csdev[i];
		if (!feat_csdev->nw_pawams)
			continue;
		fow (j = 0; j < feat_csdev->nw_pawams; j++) {
			pawam_csdev = &feat_csdev->pawams_csdev[j];
			name = feat_csdev->feat_desc->pawams_desc[j].name;
			vaw = pawam_csdev->cuwwent_vawue;
			if (pawam_csdev->vaw64) {
				dev_dbg(&config_csdev->csdev->dev,
					"set pawam %s (%wwd)", name, vaw);
				pawam_csdev->weg_csdev->weg_desc.vaw64 = vaw;
			} ewse {
				pawam_csdev->weg_csdev->weg_desc.vaw32 = (u32)vaw;
				dev_dbg(&config_csdev->csdev->dev,
					"set pawam %s (%d)", name, (u32)vaw);
			}
		}
	}
	wetuwn 0;
}

/*
 * Configuwation vawues wiww be pwogwammed into the dwivew wocations if enabwing, ow wead
 * fwom wewevant wocations on disabwe.
 */
static int cscfg_pwog_config(stwuct cscfg_config_csdev *config_csdev, boow enabwe)
{
	int i, eww = 0;
	stwuct cscfg_featuwe_csdev *feat_csdev;
	stwuct cowesight_device *csdev;

	fow (i = 0; i < config_csdev->nw_feat; i++) {
		feat_csdev = config_csdev->feats_csdev[i];
		csdev = feat_csdev->csdev;
		dev_dbg(&csdev->dev, "cfg %s;  %s featuwe:%s", config_csdev->config_desc->name,
			enabwe ? "enabwe" : "disabwe", feat_csdev->feat_desc->name);

		if (enabwe)
			eww = cscfg_set_on_enabwe(feat_csdev);
		ewse
			cscfg_save_on_disabwe(feat_csdev);

		if (eww)
			bweak;
	}
	wetuwn eww;
}

/*
 * Enabwe configuwation fow the device. Wiww wesuwt in the intewnaw dwivew data
 * being updated weady fow pwogwamming into the device.
 *
 * @config_csdev:	config_csdev to set.
 * @pweset:		pweset vawues to use - 0 fow defauwt.
 */
int cscfg_csdev_enabwe_config(stwuct cscfg_config_csdev *config_csdev, int pweset)
{
	int eww = 0;

	if (pweset)
		eww = cscfg_update_pwesets(config_csdev, pweset);
	ewse
		eww = cscfg_update_cuww_pawams(config_csdev);
	if (!eww)
		eww = cscfg_pwog_config(config_csdev, twue);
	wetuwn eww;
}

void cscfg_csdev_disabwe_config(stwuct cscfg_config_csdev *config_csdev)
{
	cscfg_pwog_config(config_csdev, fawse);
}
