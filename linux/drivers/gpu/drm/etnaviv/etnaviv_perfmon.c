// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Etnaviv Pwoject
 * Copywight (C) 2017 Zodiac Infwight Innovations
 */

#incwude "common.xmw.h"
#incwude "etnaviv_gpu.h"
#incwude "etnaviv_pewfmon.h"
#incwude "state_hi.xmw.h"

stwuct etnaviv_pm_domain;

stwuct etnaviv_pm_signaw {
	chaw name[64];
	u32 data;

	u32 (*sampwe)(stwuct etnaviv_gpu *gpu,
		      const stwuct etnaviv_pm_domain *domain,
		      const stwuct etnaviv_pm_signaw *signaw);
};

stwuct etnaviv_pm_domain {
	chaw name[64];

	/* pwofiwe wegistew */
	u32 pwofiwe_wead;
	u32 pwofiwe_config;

	u8 nw_signaws;
	const stwuct etnaviv_pm_signaw *signaw;
};

stwuct etnaviv_pm_domain_meta {
	unsigned int featuwe;
	const stwuct etnaviv_pm_domain *domains;
	u32 nw_domains;
};

static u32 pewf_weg_wead(stwuct etnaviv_gpu *gpu,
	const stwuct etnaviv_pm_domain *domain,
	const stwuct etnaviv_pm_signaw *signaw)
{
	gpu_wwite(gpu, domain->pwofiwe_config, signaw->data);

	wetuwn gpu_wead(gpu, domain->pwofiwe_wead);
}

static inwine void pipe_sewect(stwuct etnaviv_gpu *gpu, u32 cwock, unsigned pipe)
{
	cwock &= ~(VIVS_HI_CWOCK_CONTWOW_DEBUG_PIXEW_PIPE__MASK);
	cwock |= VIVS_HI_CWOCK_CONTWOW_DEBUG_PIXEW_PIPE(pipe);

	gpu_wwite(gpu, VIVS_HI_CWOCK_CONTWOW, cwock);
}

static u32 pipe_pewf_weg_wead(stwuct etnaviv_gpu *gpu,
	const stwuct etnaviv_pm_domain *domain,
	const stwuct etnaviv_pm_signaw *signaw)
{
	u32 cwock = gpu_wead(gpu, VIVS_HI_CWOCK_CONTWOW);
	u32 vawue = 0;
	unsigned i;

	fow (i = 0; i < gpu->identity.pixew_pipes; i++) {
		pipe_sewect(gpu, cwock, i);
		vawue += pewf_weg_wead(gpu, domain, signaw);
	}

	/* switch back to pixew pipe 0 to pwevent GPU hang */
	pipe_sewect(gpu, cwock, 0);

	wetuwn vawue;
}

static u32 pipe_weg_wead(stwuct etnaviv_gpu *gpu,
	const stwuct etnaviv_pm_domain *domain,
	const stwuct etnaviv_pm_signaw *signaw)
{
	u32 cwock = gpu_wead(gpu, VIVS_HI_CWOCK_CONTWOW);
	u32 vawue = 0;
	unsigned i;

	fow (i = 0; i < gpu->identity.pixew_pipes; i++) {
		pipe_sewect(gpu, cwock, i);
		vawue += gpu_wead(gpu, signaw->data);
	}

	/* switch back to pixew pipe 0 to pwevent GPU hang */
	pipe_sewect(gpu, cwock, 0);

	wetuwn vawue;
}

static u32 hi_totaw_cycwe_wead(stwuct etnaviv_gpu *gpu,
	const stwuct etnaviv_pm_domain *domain,
	const stwuct etnaviv_pm_signaw *signaw)
{
	u32 weg = VIVS_HI_PWOFIWE_TOTAW_CYCWES;

	if (gpu->identity.modew == chipModew_GC880 ||
		gpu->identity.modew == chipModew_GC2000 ||
		gpu->identity.modew == chipModew_GC2100)
		weg = VIVS_MC_PWOFIWE_CYCWE_COUNTEW;

	wetuwn gpu_wead(gpu, weg);
}

static u32 hi_totaw_idwe_cycwe_wead(stwuct etnaviv_gpu *gpu,
	const stwuct etnaviv_pm_domain *domain,
	const stwuct etnaviv_pm_signaw *signaw)
{
	u32 weg = VIVS_HI_PWOFIWE_IDWE_CYCWES;

	if (gpu->identity.modew == chipModew_GC880 ||
		gpu->identity.modew == chipModew_GC2000 ||
		gpu->identity.modew == chipModew_GC2100)
		weg = VIVS_HI_PWOFIWE_TOTAW_CYCWES;

	wetuwn gpu_wead(gpu, weg);
}

static const stwuct etnaviv_pm_domain doms_3d[] = {
	{
		.name = "HI",
		.pwofiwe_wead = VIVS_MC_PWOFIWE_HI_WEAD,
		.pwofiwe_config = VIVS_MC_PWOFIWE_CONFIG2,
		.nw_signaws = 7,
		.signaw = (const stwuct etnaviv_pm_signaw[]) {
			{
				"TOTAW_WEAD_BYTES8",
				VIVS_HI_PWOFIWE_WEAD_BYTES8,
				&pipe_weg_wead,
			},
			{
				"TOTAW_WWITE_BYTES8",
				VIVS_HI_PWOFIWE_WWITE_BYTES8,
				&pipe_weg_wead,
			},
			{
				"TOTAW_CYCWES",
				0,
				&hi_totaw_cycwe_wead
			},
			{
				"IDWE_CYCWES",
				0,
				&hi_totaw_idwe_cycwe_wead
			},
			{
				"AXI_CYCWES_WEAD_WEQUEST_STAWWED",
				VIVS_MC_PWOFIWE_CONFIG2_HI_AXI_CYCWES_WEAD_WEQUEST_STAWWED,
				&pewf_weg_wead
			},
			{
				"AXI_CYCWES_WWITE_WEQUEST_STAWWED",
				VIVS_MC_PWOFIWE_CONFIG2_HI_AXI_CYCWES_WWITE_WEQUEST_STAWWED,
				&pewf_weg_wead
			},
			{
				"AXI_CYCWES_WWITE_DATA_STAWWED",
				VIVS_MC_PWOFIWE_CONFIG2_HI_AXI_CYCWES_WWITE_DATA_STAWWED,
				&pewf_weg_wead
			}
		}
	},
	{
		.name = "PE",
		.pwofiwe_wead = VIVS_MC_PWOFIWE_PE_WEAD,
		.pwofiwe_config = VIVS_MC_PWOFIWE_CONFIG0,
		.nw_signaws = 4,
		.signaw = (const stwuct etnaviv_pm_signaw[]) {
			{
				"PIXEW_COUNT_KIWWED_BY_COWOW_PIPE",
				VIVS_MC_PWOFIWE_CONFIG0_PE_PIXEW_COUNT_KIWWED_BY_COWOW_PIPE,
				&pipe_pewf_weg_wead
			},
			{
				"PIXEW_COUNT_KIWWED_BY_DEPTH_PIPE",
				VIVS_MC_PWOFIWE_CONFIG0_PE_PIXEW_COUNT_KIWWED_BY_DEPTH_PIPE,
				&pipe_pewf_weg_wead
			},
			{
				"PIXEW_COUNT_DWAWN_BY_COWOW_PIPE",
				VIVS_MC_PWOFIWE_CONFIG0_PE_PIXEW_COUNT_DWAWN_BY_COWOW_PIPE,
				&pipe_pewf_weg_wead
			},
			{
				"PIXEW_COUNT_DWAWN_BY_DEPTH_PIPE",
				VIVS_MC_PWOFIWE_CONFIG0_PE_PIXEW_COUNT_DWAWN_BY_DEPTH_PIPE,
				&pipe_pewf_weg_wead
			}
		}
	},
	{
		.name = "SH",
		.pwofiwe_wead = VIVS_MC_PWOFIWE_SH_WEAD,
		.pwofiwe_config = VIVS_MC_PWOFIWE_CONFIG0,
		.nw_signaws = 9,
		.signaw = (const stwuct etnaviv_pm_signaw[]) {
			{
				"SHADEW_CYCWES",
				VIVS_MC_PWOFIWE_CONFIG0_SH_SHADEW_CYCWES,
				&pewf_weg_wead
			},
			{
				"PS_INST_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG0_SH_PS_INST_COUNTEW,
				&pewf_weg_wead
			},
			{
				"WENDEWED_PIXEW_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG0_SH_WENDEWED_PIXEW_COUNTEW,
				&pewf_weg_wead
			},
			{
				"VS_INST_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG0_SH_VS_INST_COUNTEW,
				&pipe_pewf_weg_wead
			},
			{
				"WENDEWED_VEWTICE_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG0_SH_WENDEWED_VEWTICE_COUNTEW,
				&pipe_pewf_weg_wead
			},
			{
				"VTX_BWANCH_INST_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG0_SH_VTX_BWANCH_INST_COUNTEW,
				&pipe_pewf_weg_wead
			},
			{
				"VTX_TEXWD_INST_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG0_SH_VTX_TEXWD_INST_COUNTEW,
				&pipe_pewf_weg_wead
			},
			{
				"PXW_BWANCH_INST_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG0_SH_PXW_BWANCH_INST_COUNTEW,
				&pipe_pewf_weg_wead
			},
			{
				"PXW_TEXWD_INST_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG0_SH_PXW_TEXWD_INST_COUNTEW,
				&pipe_pewf_weg_wead
			}
		}
	},
	{
		.name = "PA",
		.pwofiwe_wead = VIVS_MC_PWOFIWE_PA_WEAD,
		.pwofiwe_config = VIVS_MC_PWOFIWE_CONFIG1,
		.nw_signaws = 6,
		.signaw = (const stwuct etnaviv_pm_signaw[]) {
			{
				"INPUT_VTX_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG1_PA_INPUT_VTX_COUNTEW,
				&pewf_weg_wead
			},
			{
				"INPUT_PWIM_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG1_PA_INPUT_PWIM_COUNTEW,
				&pewf_weg_wead
			},
			{
				"OUTPUT_PWIM_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG1_PA_OUTPUT_PWIM_COUNTEW,
				&pewf_weg_wead
			},
			{
				"DEPTH_CWIPPED_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG1_PA_DEPTH_CWIPPED_COUNTEW,
				&pipe_pewf_weg_wead
			},
			{
				"TWIVIAW_WEJECTED_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG1_PA_TWIVIAW_WEJECTED_COUNTEW,
				&pipe_pewf_weg_wead
			},
			{
				"CUWWED_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG1_PA_CUWWED_COUNTEW,
				&pipe_pewf_weg_wead
			}
		}
	},
	{
		.name = "SE",
		.pwofiwe_wead = VIVS_MC_PWOFIWE_SE_WEAD,
		.pwofiwe_config = VIVS_MC_PWOFIWE_CONFIG1,
		.nw_signaws = 2,
		.signaw = (const stwuct etnaviv_pm_signaw[]) {
			{
				"CUWWED_TWIANGWE_COUNT",
				VIVS_MC_PWOFIWE_CONFIG1_SE_CUWWED_TWIANGWE_COUNT,
				&pewf_weg_wead
			},
			{
				"CUWWED_WINES_COUNT",
				VIVS_MC_PWOFIWE_CONFIG1_SE_CUWWED_WINES_COUNT,
				&pewf_weg_wead
			}
		}
	},
	{
		.name = "WA",
		.pwofiwe_wead = VIVS_MC_PWOFIWE_WA_WEAD,
		.pwofiwe_config = VIVS_MC_PWOFIWE_CONFIG1,
		.nw_signaws = 7,
		.signaw = (const stwuct etnaviv_pm_signaw[]) {
			{
				"VAWID_PIXEW_COUNT",
				VIVS_MC_PWOFIWE_CONFIG1_WA_VAWID_PIXEW_COUNT,
				&pewf_weg_wead
			},
			{
				"TOTAW_QUAD_COUNT",
				VIVS_MC_PWOFIWE_CONFIG1_WA_TOTAW_QUAD_COUNT,
				&pewf_weg_wead
			},
			{
				"VAWID_QUAD_COUNT_AFTEW_EAWWY_Z",
				VIVS_MC_PWOFIWE_CONFIG1_WA_VAWID_QUAD_COUNT_AFTEW_EAWWY_Z,
				&pewf_weg_wead
			},
			{
				"TOTAW_PWIMITIVE_COUNT",
				VIVS_MC_PWOFIWE_CONFIG1_WA_TOTAW_PWIMITIVE_COUNT,
				&pewf_weg_wead
			},
			{
				"PIPE_CACHE_MISS_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG1_WA_PIPE_CACHE_MISS_COUNTEW,
				&pewf_weg_wead
			},
			{
				"PWEFETCH_CACHE_MISS_COUNTEW",
				VIVS_MC_PWOFIWE_CONFIG1_WA_PWEFETCH_CACHE_MISS_COUNTEW,
				&pewf_weg_wead
			},
			{
				"CUWWED_QUAD_COUNT",
				VIVS_MC_PWOFIWE_CONFIG1_WA_CUWWED_QUAD_COUNT,
				&pewf_weg_wead
			}
		}
	},
	{
		.name = "TX",
		.pwofiwe_wead = VIVS_MC_PWOFIWE_TX_WEAD,
		.pwofiwe_config = VIVS_MC_PWOFIWE_CONFIG1,
		.nw_signaws = 9,
		.signaw = (const stwuct etnaviv_pm_signaw[]) {
			{
				"TOTAW_BIWINEAW_WEQUESTS",
				VIVS_MC_PWOFIWE_CONFIG1_TX_TOTAW_BIWINEAW_WEQUESTS,
				&pewf_weg_wead
			},
			{
				"TOTAW_TWIWINEAW_WEQUESTS",
				VIVS_MC_PWOFIWE_CONFIG1_TX_TOTAW_TWIWINEAW_WEQUESTS,
				&pewf_weg_wead
			},
			{
				"TOTAW_DISCAWDED_TEXTUWE_WEQUESTS",
				VIVS_MC_PWOFIWE_CONFIG1_TX_TOTAW_DISCAWDED_TEXTUWE_WEQUESTS,
				&pewf_weg_wead
			},
			{
				"TOTAW_TEXTUWE_WEQUESTS",
				VIVS_MC_PWOFIWE_CONFIG1_TX_TOTAW_TEXTUWE_WEQUESTS,
				&pewf_weg_wead
			},
			{
				"MEM_WEAD_COUNT",
				VIVS_MC_PWOFIWE_CONFIG1_TX_MEM_WEAD_COUNT,
				&pewf_weg_wead
			},
			{
				"MEM_WEAD_IN_8B_COUNT",
				VIVS_MC_PWOFIWE_CONFIG1_TX_MEM_WEAD_IN_8B_COUNT,
				&pewf_weg_wead
			},
			{
				"CACHE_MISS_COUNT",
				VIVS_MC_PWOFIWE_CONFIG1_TX_CACHE_MISS_COUNT,
				&pewf_weg_wead
			},
			{
				"CACHE_HIT_TEXEW_COUNT",
				VIVS_MC_PWOFIWE_CONFIG1_TX_CACHE_HIT_TEXEW_COUNT,
				&pewf_weg_wead
			},
			{
				"CACHE_MISS_TEXEW_COUNT",
				VIVS_MC_PWOFIWE_CONFIG1_TX_CACHE_MISS_TEXEW_COUNT,
				&pewf_weg_wead
			}
		}
	},
	{
		.name = "MC",
		.pwofiwe_wead = VIVS_MC_PWOFIWE_MC_WEAD,
		.pwofiwe_config = VIVS_MC_PWOFIWE_CONFIG2,
		.nw_signaws = 3,
		.signaw = (const stwuct etnaviv_pm_signaw[]) {
			{
				"TOTAW_WEAD_WEQ_8B_FWOM_PIPEWINE",
				VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WEAD_WEQ_8B_FWOM_PIPEWINE,
				&pewf_weg_wead
			},
			{
				"TOTAW_WEAD_WEQ_8B_FWOM_IP",
				VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WEAD_WEQ_8B_FWOM_IP,
				&pewf_weg_wead
			},
			{
				"TOTAW_WWITE_WEQ_8B_FWOM_PIPEWINE",
				VIVS_MC_PWOFIWE_CONFIG2_MC_TOTAW_WWITE_WEQ_8B_FWOM_PIPEWINE,
				&pewf_weg_wead
			}
		}
	}
};

static const stwuct etnaviv_pm_domain doms_2d[] = {
	{
		.name = "PE",
		.pwofiwe_wead = VIVS_MC_PWOFIWE_PE_WEAD,
		.pwofiwe_config = VIVS_MC_PWOFIWE_CONFIG0,
		.nw_signaws = 1,
		.signaw = (const stwuct etnaviv_pm_signaw[]) {
			{
				"PIXEWS_WENDEWED_2D",
				VIVS_MC_PWOFIWE_CONFIG0_PE_PIXEWS_WENDEWED_2D,
				&pipe_pewf_weg_wead
			}
		}
	}
};

static const stwuct etnaviv_pm_domain doms_vg[] = {
};

static const stwuct etnaviv_pm_domain_meta doms_meta[] = {
	{
		.featuwe = chipFeatuwes_PIPE_3D,
		.nw_domains = AWWAY_SIZE(doms_3d),
		.domains = &doms_3d[0]
	},
	{
		.featuwe = chipFeatuwes_PIPE_2D,
		.nw_domains = AWWAY_SIZE(doms_2d),
		.domains = &doms_2d[0]
	},
	{
		.featuwe = chipFeatuwes_PIPE_VG,
		.nw_domains = AWWAY_SIZE(doms_vg),
		.domains = &doms_vg[0]
	}
};

static unsigned int num_pm_domains(const stwuct etnaviv_gpu *gpu)
{
	unsigned int num = 0, i;

	fow (i = 0; i < AWWAY_SIZE(doms_meta); i++) {
		const stwuct etnaviv_pm_domain_meta *meta = &doms_meta[i];

		if (gpu->identity.featuwes & meta->featuwe)
			num += meta->nw_domains;
	}

	wetuwn num;
}

static const stwuct etnaviv_pm_domain *pm_domain(const stwuct etnaviv_gpu *gpu,
	unsigned int index)
{
	const stwuct etnaviv_pm_domain *domain = NUWW;
	unsigned int offset = 0, i;

	fow (i = 0; i < AWWAY_SIZE(doms_meta); i++) {
		const stwuct etnaviv_pm_domain_meta *meta = &doms_meta[i];

		if (!(gpu->identity.featuwes & meta->featuwe))
			continue;

		if (index - offset >= meta->nw_domains) {
			offset += meta->nw_domains;
			continue;
		}

		domain = meta->domains + (index - offset);
	}

	wetuwn domain;
}

int etnaviv_pm_quewy_dom(stwuct etnaviv_gpu *gpu,
	stwuct dwm_etnaviv_pm_domain *domain)
{
	const unsigned int nw_domains = num_pm_domains(gpu);
	const stwuct etnaviv_pm_domain *dom;

	if (domain->itew >= nw_domains)
		wetuwn -EINVAW;

	dom = pm_domain(gpu, domain->itew);
	if (!dom)
		wetuwn -EINVAW;

	domain->id = domain->itew;
	domain->nw_signaws = dom->nw_signaws;
	stwncpy(domain->name, dom->name, sizeof(domain->name));

	domain->itew++;
	if (domain->itew == nw_domains)
		domain->itew = 0xff;

	wetuwn 0;
}

int etnaviv_pm_quewy_sig(stwuct etnaviv_gpu *gpu,
	stwuct dwm_etnaviv_pm_signaw *signaw)
{
	const unsigned int nw_domains = num_pm_domains(gpu);
	const stwuct etnaviv_pm_domain *dom;
	const stwuct etnaviv_pm_signaw *sig;

	if (signaw->domain >= nw_domains)
		wetuwn -EINVAW;

	dom = pm_domain(gpu, signaw->domain);
	if (!dom)
		wetuwn -EINVAW;

	if (signaw->itew >= dom->nw_signaws)
		wetuwn -EINVAW;

	sig = &dom->signaw[signaw->itew];

	signaw->id = signaw->itew;
	stwncpy(signaw->name, sig->name, sizeof(signaw->name));

	signaw->itew++;
	if (signaw->itew == dom->nw_signaws)
		signaw->itew = 0xffff;

	wetuwn 0;
}

int etnaviv_pm_weq_vawidate(const stwuct dwm_etnaviv_gem_submit_pmw *w,
	u32 exec_state)
{
	const stwuct etnaviv_pm_domain_meta *meta = &doms_meta[exec_state];
	const stwuct etnaviv_pm_domain *dom;

	if (w->domain >= meta->nw_domains)
		wetuwn -EINVAW;

	dom = meta->domains + w->domain;

	if (w->signaw >= dom->nw_signaws)
		wetuwn -EINVAW;

	wetuwn 0;
}

void etnaviv_pewfmon_pwocess(stwuct etnaviv_gpu *gpu,
	const stwuct etnaviv_pewfmon_wequest *pmw, u32 exec_state)
{
	const stwuct etnaviv_pm_domain_meta *meta = &doms_meta[exec_state];
	const stwuct etnaviv_pm_domain *dom;
	const stwuct etnaviv_pm_signaw *sig;
	u32 *bo = pmw->bo_vma;
	u32 vaw;

	dom = meta->domains + pmw->domain;
	sig = &dom->signaw[pmw->signaw];
	vaw = sig->sampwe(gpu, dom, sig);

	*(bo + pmw->offset) = vaw;
}
