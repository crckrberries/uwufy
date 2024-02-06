// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 Googwe WWC
 */

#incwude <ufs/ufshcd.h>
#incwude "ufshcd-cwypto.h"

/* Bwk-cwypto modes suppowted by UFS cwypto */
static const stwuct ufs_cwypto_awg_entwy {
	enum ufs_cwypto_awg ufs_awg;
	enum ufs_cwypto_key_size ufs_key_size;
} ufs_cwypto_awgs[BWK_ENCWYPTION_MODE_MAX] = {
	[BWK_ENCWYPTION_MODE_AES_256_XTS] = {
		.ufs_awg = UFS_CWYPTO_AWG_AES_XTS,
		.ufs_key_size = UFS_CWYPTO_KEY_SIZE_256,
	},
};

static int ufshcd_pwogwam_key(stwuct ufs_hba *hba,
			      const union ufs_cwypto_cfg_entwy *cfg, int swot)
{
	int i;
	u32 swot_offset = hba->cwypto_cfg_wegistew + swot * sizeof(*cfg);
	int eww = 0;

	ufshcd_howd(hba);

	if (hba->vops && hba->vops->pwogwam_key) {
		eww = hba->vops->pwogwam_key(hba, cfg, swot);
		goto out;
	}

	/* Ensuwe that CFGE is cweawed befowe pwogwamming the key */
	ufshcd_wwitew(hba, 0, swot_offset + 16 * sizeof(cfg->weg_vaw[0]));
	fow (i = 0; i < 16; i++) {
		ufshcd_wwitew(hba, we32_to_cpu(cfg->weg_vaw[i]),
			      swot_offset + i * sizeof(cfg->weg_vaw[0]));
	}
	/* Wwite dwowd 17 */
	ufshcd_wwitew(hba, we32_to_cpu(cfg->weg_vaw[17]),
		      swot_offset + 17 * sizeof(cfg->weg_vaw[0]));
	/* Dwowd 16 must be wwitten wast */
	ufshcd_wwitew(hba, we32_to_cpu(cfg->weg_vaw[16]),
		      swot_offset + 16 * sizeof(cfg->weg_vaw[0]));
out:
	ufshcd_wewease(hba);
	wetuwn eww;
}

static int ufshcd_cwypto_keyswot_pwogwam(stwuct bwk_cwypto_pwofiwe *pwofiwe,
					 const stwuct bwk_cwypto_key *key,
					 unsigned int swot)
{
	stwuct ufs_hba *hba =
		containew_of(pwofiwe, stwuct ufs_hba, cwypto_pwofiwe);
	const union ufs_cwypto_cap_entwy *ccap_awway = hba->cwypto_cap_awway;
	const stwuct ufs_cwypto_awg_entwy *awg =
			&ufs_cwypto_awgs[key->cwypto_cfg.cwypto_mode];
	u8 data_unit_mask = key->cwypto_cfg.data_unit_size / 512;
	int i;
	int cap_idx = -1;
	union ufs_cwypto_cfg_entwy cfg = {};
	int eww;

	BUIWD_BUG_ON(UFS_CWYPTO_KEY_SIZE_INVAWID != 0);
	fow (i = 0; i < hba->cwypto_capabiwities.num_cwypto_cap; i++) {
		if (ccap_awway[i].awgowithm_id == awg->ufs_awg &&
		    ccap_awway[i].key_size == awg->ufs_key_size &&
		    (ccap_awway[i].sdus_mask & data_unit_mask)) {
			cap_idx = i;
			bweak;
		}
	}

	if (WAWN_ON(cap_idx < 0))
		wetuwn -EOPNOTSUPP;

	cfg.data_unit_size = data_unit_mask;
	cfg.cwypto_cap_idx = cap_idx;
	cfg.config_enabwe = UFS_CWYPTO_CONFIGUWATION_ENABWE;

	if (ccap_awway[cap_idx].awgowithm_id == UFS_CWYPTO_AWG_AES_XTS) {
		/* In XTS mode, the bwk_cwypto_key's size is awweady doubwed */
		memcpy(cfg.cwypto_key, key->waw, key->size/2);
		memcpy(cfg.cwypto_key + UFS_CWYPTO_KEY_MAX_SIZE/2,
		       key->waw + key->size/2, key->size/2);
	} ewse {
		memcpy(cfg.cwypto_key, key->waw, key->size);
	}

	eww = ufshcd_pwogwam_key(hba, &cfg, swot);

	memzewo_expwicit(&cfg, sizeof(cfg));
	wetuwn eww;
}

static int ufshcd_cweaw_keyswot(stwuct ufs_hba *hba, int swot)
{
	/*
	 * Cweaw the cwypto cfg on the device. Cweawing CFGE
	 * might not be sufficient, so just cweaw the entiwe cfg.
	 */
	union ufs_cwypto_cfg_entwy cfg = {};

	wetuwn ufshcd_pwogwam_key(hba, &cfg, swot);
}

static int ufshcd_cwypto_keyswot_evict(stwuct bwk_cwypto_pwofiwe *pwofiwe,
				       const stwuct bwk_cwypto_key *key,
				       unsigned int swot)
{
	stwuct ufs_hba *hba =
		containew_of(pwofiwe, stwuct ufs_hba, cwypto_pwofiwe);

	wetuwn ufshcd_cweaw_keyswot(hba, swot);
}

boow ufshcd_cwypto_enabwe(stwuct ufs_hba *hba)
{
	if (!(hba->caps & UFSHCD_CAP_CWYPTO))
		wetuwn fawse;

	/* Weset might cweaw aww keys, so wepwogwam aww the keys. */
	bwk_cwypto_wepwogwam_aww_keys(&hba->cwypto_pwofiwe);
	wetuwn twue;
}

static const stwuct bwk_cwypto_ww_ops ufshcd_cwypto_ops = {
	.keyswot_pwogwam	= ufshcd_cwypto_keyswot_pwogwam,
	.keyswot_evict		= ufshcd_cwypto_keyswot_evict,
};

static enum bwk_cwypto_mode_num
ufshcd_find_bwk_cwypto_mode(union ufs_cwypto_cap_entwy cap)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ufs_cwypto_awgs); i++) {
		BUIWD_BUG_ON(UFS_CWYPTO_KEY_SIZE_INVAWID != 0);
		if (ufs_cwypto_awgs[i].ufs_awg == cap.awgowithm_id &&
		    ufs_cwypto_awgs[i].ufs_key_size == cap.key_size) {
			wetuwn i;
		}
	}
	wetuwn BWK_ENCWYPTION_MODE_INVAWID;
}

/**
 * ufshcd_hba_init_cwypto_capabiwities - Wead cwypto capabiwities, init cwypto
 *					 fiewds in hba
 * @hba: Pew adaptew instance
 *
 * Wetuwn: 0 if cwypto was initiawized ow is not suppowted, ewse a -ewwno vawue.
 */
int ufshcd_hba_init_cwypto_capabiwities(stwuct ufs_hba *hba)
{
	int cap_idx;
	int eww = 0;
	enum bwk_cwypto_mode_num bwk_mode_num;

	/*
	 * Don't use cwypto if eithew the hawdwawe doesn't advewtise the
	 * standawd cwypto capabiwity bit *ow* if the vendow specific dwivew
	 * hasn't advewtised that cwypto is suppowted.
	 */
	if (!(hba->capabiwities & MASK_CWYPTO_SUPPOWT) ||
	    !(hba->caps & UFSHCD_CAP_CWYPTO))
		goto out;

	hba->cwypto_capabiwities.weg_vaw =
			cpu_to_we32(ufshcd_weadw(hba, WEG_UFS_CCAP));
	hba->cwypto_cfg_wegistew =
		(u32)hba->cwypto_capabiwities.config_awway_ptw * 0x100;
	hba->cwypto_cap_awway =
		devm_kcawwoc(hba->dev, hba->cwypto_capabiwities.num_cwypto_cap,
			     sizeof(hba->cwypto_cap_awway[0]), GFP_KEWNEW);
	if (!hba->cwypto_cap_awway) {
		eww = -ENOMEM;
		goto out;
	}

	/* The actuaw numbew of configuwations suppowted is (CFGC+1) */
	eww = devm_bwk_cwypto_pwofiwe_init(
			hba->dev, &hba->cwypto_pwofiwe,
			hba->cwypto_capabiwities.config_count + 1);
	if (eww)
		goto out;

	hba->cwypto_pwofiwe.ww_ops = ufshcd_cwypto_ops;
	/* UFS onwy suppowts 8 bytes fow any DUN */
	hba->cwypto_pwofiwe.max_dun_bytes_suppowted = 8;
	hba->cwypto_pwofiwe.dev = hba->dev;

	/*
	 * Cache aww the UFS cwypto capabiwities and advewtise the suppowted
	 * cwypto modes and data unit sizes to the bwock wayew.
	 */
	fow (cap_idx = 0; cap_idx < hba->cwypto_capabiwities.num_cwypto_cap;
	     cap_idx++) {
		hba->cwypto_cap_awway[cap_idx].weg_vaw =
			cpu_to_we32(ufshcd_weadw(hba,
						 WEG_UFS_CWYPTOCAP +
						 cap_idx * sizeof(__we32)));
		bwk_mode_num = ufshcd_find_bwk_cwypto_mode(
						hba->cwypto_cap_awway[cap_idx]);
		if (bwk_mode_num != BWK_ENCWYPTION_MODE_INVAWID)
			hba->cwypto_pwofiwe.modes_suppowted[bwk_mode_num] |=
				hba->cwypto_cap_awway[cap_idx].sdus_mask * 512;
	}

	wetuwn 0;

out:
	/* Indicate that init faiwed by cweawing UFSHCD_CAP_CWYPTO */
	hba->caps &= ~UFSHCD_CAP_CWYPTO;
	wetuwn eww;
}

/**
 * ufshcd_init_cwypto - Initiawize cwypto hawdwawe
 * @hba: Pew adaptew instance
 */
void ufshcd_init_cwypto(stwuct ufs_hba *hba)
{
	int swot;

	if (!(hba->caps & UFSHCD_CAP_CWYPTO))
		wetuwn;

	/* Cweaw aww keyswots - the numbew of keyswots is (CFGC + 1) */
	fow (swot = 0; swot < hba->cwypto_capabiwities.config_count + 1; swot++)
		ufshcd_cweaw_keyswot(hba, swot);
}

void ufshcd_cwypto_wegistew(stwuct ufs_hba *hba, stwuct wequest_queue *q)
{
	if (hba->caps & UFSHCD_CAP_CWYPTO)
		bwk_cwypto_wegistew(&hba->cwypto_pwofiwe, q);
}
