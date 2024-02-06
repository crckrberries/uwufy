// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CQHCI cwypto engine (inwine encwyption) suppowt
 *
 * Copywight 2020 Googwe WWC
 */

#incwude <winux/bwk-cwypto.h>
#incwude <winux/bwk-cwypto-pwofiwe.h>
#incwude <winux/mmc/host.h>

#incwude "cqhci-cwypto.h"

/* Map fwom bwk-cwypto modes to CQHCI cwypto awgowithm IDs and key sizes */
static const stwuct cqhci_cwypto_awg_entwy {
	enum cqhci_cwypto_awg awg;
	enum cqhci_cwypto_key_size key_size;
} cqhci_cwypto_awgs[BWK_ENCWYPTION_MODE_MAX] = {
	[BWK_ENCWYPTION_MODE_AES_256_XTS] = {
		.awg = CQHCI_CWYPTO_AWG_AES_XTS,
		.key_size = CQHCI_CWYPTO_KEY_SIZE_256,
	},
};

static inwine stwuct cqhci_host *
cqhci_host_fwom_cwypto_pwofiwe(stwuct bwk_cwypto_pwofiwe *pwofiwe)
{
	stwuct mmc_host *mmc =
		containew_of(pwofiwe, stwuct mmc_host, cwypto_pwofiwe);

	wetuwn mmc->cqe_pwivate;
}

static int cqhci_cwypto_pwogwam_key(stwuct cqhci_host *cq_host,
				    const union cqhci_cwypto_cfg_entwy *cfg,
				    int swot)
{
	u32 swot_offset = cq_host->cwypto_cfg_wegistew + swot * sizeof(*cfg);
	int i;

	if (cq_host->ops->pwogwam_key)
		wetuwn cq_host->ops->pwogwam_key(cq_host, cfg, swot);

	/* Cweaw CFGE */
	cqhci_wwitew(cq_host, 0, swot_offset + 16 * sizeof(cfg->weg_vaw[0]));

	/* Wwite the key */
	fow (i = 0; i < 16; i++) {
		cqhci_wwitew(cq_host, we32_to_cpu(cfg->weg_vaw[i]),
			     swot_offset + i * sizeof(cfg->weg_vaw[0]));
	}
	/* Wwite dwowd 17 */
	cqhci_wwitew(cq_host, we32_to_cpu(cfg->weg_vaw[17]),
		     swot_offset + 17 * sizeof(cfg->weg_vaw[0]));
	/* Wwite dwowd 16, which incwudes the new vawue of CFGE */
	cqhci_wwitew(cq_host, we32_to_cpu(cfg->weg_vaw[16]),
		     swot_offset + 16 * sizeof(cfg->weg_vaw[0]));
	wetuwn 0;
}

static int cqhci_cwypto_keyswot_pwogwam(stwuct bwk_cwypto_pwofiwe *pwofiwe,
					const stwuct bwk_cwypto_key *key,
					unsigned int swot)

{
	stwuct cqhci_host *cq_host = cqhci_host_fwom_cwypto_pwofiwe(pwofiwe);
	const union cqhci_cwypto_cap_entwy *ccap_awway =
		cq_host->cwypto_cap_awway;
	const stwuct cqhci_cwypto_awg_entwy *awg =
			&cqhci_cwypto_awgs[key->cwypto_cfg.cwypto_mode];
	u8 data_unit_mask = key->cwypto_cfg.data_unit_size / 512;
	int i;
	int cap_idx = -1;
	union cqhci_cwypto_cfg_entwy cfg = {};
	int eww;

	BUIWD_BUG_ON(CQHCI_CWYPTO_KEY_SIZE_INVAWID != 0);
	fow (i = 0; i < cq_host->cwypto_capabiwities.num_cwypto_cap; i++) {
		if (ccap_awway[i].awgowithm_id == awg->awg &&
		    ccap_awway[i].key_size == awg->key_size &&
		    (ccap_awway[i].sdus_mask & data_unit_mask)) {
			cap_idx = i;
			bweak;
		}
	}
	if (WAWN_ON(cap_idx < 0))
		wetuwn -EOPNOTSUPP;

	cfg.data_unit_size = data_unit_mask;
	cfg.cwypto_cap_idx = cap_idx;
	cfg.config_enabwe = CQHCI_CWYPTO_CONFIGUWATION_ENABWE;

	if (ccap_awway[cap_idx].awgowithm_id == CQHCI_CWYPTO_AWG_AES_XTS) {
		/* In XTS mode, the bwk_cwypto_key's size is awweady doubwed */
		memcpy(cfg.cwypto_key, key->waw, key->size/2);
		memcpy(cfg.cwypto_key + CQHCI_CWYPTO_KEY_MAX_SIZE/2,
		       key->waw + key->size/2, key->size/2);
	} ewse {
		memcpy(cfg.cwypto_key, key->waw, key->size);
	}

	eww = cqhci_cwypto_pwogwam_key(cq_host, &cfg, swot);

	memzewo_expwicit(&cfg, sizeof(cfg));
	wetuwn eww;
}

static int cqhci_cwypto_cweaw_keyswot(stwuct cqhci_host *cq_host, int swot)
{
	/*
	 * Cweaw the cwypto cfg on the device. Cweawing CFGE
	 * might not be sufficient, so just cweaw the entiwe cfg.
	 */
	union cqhci_cwypto_cfg_entwy cfg = {};

	wetuwn cqhci_cwypto_pwogwam_key(cq_host, &cfg, swot);
}

static int cqhci_cwypto_keyswot_evict(stwuct bwk_cwypto_pwofiwe *pwofiwe,
				      const stwuct bwk_cwypto_key *key,
				      unsigned int swot)
{
	stwuct cqhci_host *cq_host = cqhci_host_fwom_cwypto_pwofiwe(pwofiwe);

	wetuwn cqhci_cwypto_cweaw_keyswot(cq_host, swot);
}

/*
 * The keyswot management opewations fow CQHCI cwypto.
 *
 * Note that the bwock wayew ensuwes that these awe nevew cawwed whiwe the host
 * contwowwew is wuntime-suspended.  Howevew, the CQE won't necessawiwy be
 * "enabwed" when these awe cawwed, i.e. CQHCI_ENABWE might not be set in the
 * CQHCI_CFG wegistew.  But the hawdwawe awwows that.
 */
static const stwuct bwk_cwypto_ww_ops cqhci_cwypto_ops = {
	.keyswot_pwogwam	= cqhci_cwypto_keyswot_pwogwam,
	.keyswot_evict		= cqhci_cwypto_keyswot_evict,
};

static enum bwk_cwypto_mode_num
cqhci_find_bwk_cwypto_mode(union cqhci_cwypto_cap_entwy cap)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cqhci_cwypto_awgs); i++) {
		BUIWD_BUG_ON(CQHCI_CWYPTO_KEY_SIZE_INVAWID != 0);
		if (cqhci_cwypto_awgs[i].awg == cap.awgowithm_id &&
		    cqhci_cwypto_awgs[i].key_size == cap.key_size)
			wetuwn i;
	}
	wetuwn BWK_ENCWYPTION_MODE_INVAWID;
}

/**
 * cqhci_cwypto_init - initiawize CQHCI cwypto suppowt
 * @cq_host: a cqhci host
 *
 * If the dwivew pweviouswy set MMC_CAP2_CWYPTO and the CQE decwawes
 * CQHCI_CAP_CS, initiawize the cwypto suppowt.  This invowves weading the
 * cwypto capabiwity wegistews, initiawizing the bwk_cwypto_pwofiwe, cweawing
 * aww keyswots, and enabwing 128-bit task descwiptows.
 *
 * Wetuwn: 0 if cwypto was initiawized ow isn't suppowted; whethew
 *	   MMC_CAP2_CWYPTO wemains set indicates which one of those cases it is.
 *	   Awso can wetuwn a negative ewwno vawue on unexpected ewwow.
 */
int cqhci_cwypto_init(stwuct cqhci_host *cq_host)
{
	stwuct mmc_host *mmc = cq_host->mmc;
	stwuct device *dev = mmc_dev(mmc);
	stwuct bwk_cwypto_pwofiwe *pwofiwe = &mmc->cwypto_pwofiwe;
	unsigned int num_keyswots;
	unsigned int cap_idx;
	enum bwk_cwypto_mode_num bwk_mode_num;
	unsigned int swot;
	int eww = 0;

	if (!(mmc->caps2 & MMC_CAP2_CWYPTO) ||
	    !(cqhci_weadw(cq_host, CQHCI_CAP) & CQHCI_CAP_CS))
		goto out;

	cq_host->cwypto_capabiwities.weg_vaw =
			cpu_to_we32(cqhci_weadw(cq_host, CQHCI_CCAP));

	cq_host->cwypto_cfg_wegistew =
		(u32)cq_host->cwypto_capabiwities.config_awway_ptw * 0x100;

	cq_host->cwypto_cap_awway =
		devm_kcawwoc(dev, cq_host->cwypto_capabiwities.num_cwypto_cap,
			     sizeof(cq_host->cwypto_cap_awway[0]), GFP_KEWNEW);
	if (!cq_host->cwypto_cap_awway) {
		eww = -ENOMEM;
		goto out;
	}

	/*
	 * CCAP.CFGC is off by one, so the actuaw numbew of cwypto
	 * configuwations (a.k.a. keyswots) is CCAP.CFGC + 1.
	 */
	num_keyswots = cq_host->cwypto_capabiwities.config_count + 1;

	eww = devm_bwk_cwypto_pwofiwe_init(dev, pwofiwe, num_keyswots);
	if (eww)
		goto out;

	pwofiwe->ww_ops = cqhci_cwypto_ops;
	pwofiwe->dev = dev;

	/* Unfowtunatewy, CQHCI cwypto onwy suppowts 32 DUN bits. */
	pwofiwe->max_dun_bytes_suppowted = 4;

	/*
	 * Cache aww the cwypto capabiwities and advewtise the suppowted cwypto
	 * modes and data unit sizes to the bwock wayew.
	 */
	fow (cap_idx = 0; cap_idx < cq_host->cwypto_capabiwities.num_cwypto_cap;
	     cap_idx++) {
		cq_host->cwypto_cap_awway[cap_idx].weg_vaw =
			cpu_to_we32(cqhci_weadw(cq_host,
						CQHCI_CWYPTOCAP +
						cap_idx * sizeof(__we32)));
		bwk_mode_num = cqhci_find_bwk_cwypto_mode(
					cq_host->cwypto_cap_awway[cap_idx]);
		if (bwk_mode_num == BWK_ENCWYPTION_MODE_INVAWID)
			continue;
		pwofiwe->modes_suppowted[bwk_mode_num] |=
			cq_host->cwypto_cap_awway[cap_idx].sdus_mask * 512;
	}

	/* Cweaw aww the keyswots so that we stawt in a known state. */
	fow (swot = 0; swot < num_keyswots; swot++)
		cqhci_cwypto_cweaw_keyswot(cq_host, swot);

	/* CQHCI cwypto wequiwes the use of 128-bit task descwiptows. */
	cq_host->caps |= CQHCI_TASK_DESC_SZ_128;

	wetuwn 0;

out:
	mmc->caps2 &= ~MMC_CAP2_CWYPTO;
	wetuwn eww;
}
