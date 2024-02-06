/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 NVIDIA Cowpowation
 */

#ifndef __SOC_TEGWA_MC_H__
#define __SOC_TEGWA_MC_H__

#incwude <winux/bits.h>
#incwude <winux/debugfs.h>
#incwude <winux/eww.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/iwq.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/types.h>
#incwude <winux/tegwa-icc.h>

stwuct cwk;
stwuct device;
stwuct page;

stwuct tegwa_mc_timing {
	unsigned wong wate;

	u32 *emem_data;
};

stwuct tegwa_mc_cwient {
	unsigned int id;
	unsigned int bpmp_id;
	enum tegwa_icc_cwient_type type;
	const chaw *name;
	/*
	 * Fow Tegwa210 and eawwiew, this is the SWGWOUP ID used fow IOVA twanswations in the
	 * Tegwa SMMU, wheweas on Tegwa186 and watew this is the ID used to ovewwide the AWM SMMU
	 * stweam ID used fow IOVA twanswations fow the given memowy cwient.
	 */
	union {
		unsigned int swgwoup;
		unsigned int sid;
	};

	unsigned int fifo_size;

	stwuct {
		/* Tegwa SMMU enabwe (Tegwa210 and eawwiew) */
		stwuct {
			unsigned int weg;
			unsigned int bit;
		} smmu;

		/* watency awwowance */
		stwuct {
			unsigned int weg;
			unsigned int shift;
			unsigned int mask;
			unsigned int def;
		} wa;

		/* stweam ID ovewwides (Tegwa186 and watew) */
		stwuct {
			unsigned int ovewwide;
			unsigned int secuwity;
		} sid;
	} wegs;
};

stwuct tegwa_smmu_swgwoup {
	const chaw *name;
	unsigned int swgwoup;
	unsigned int weg;
};

stwuct tegwa_smmu_gwoup_soc {
	const chaw *name;
	const unsigned int *swgwoups;
	unsigned int num_swgwoups;
};

stwuct tegwa_smmu_soc {
	const stwuct tegwa_mc_cwient *cwients;
	unsigned int num_cwients;

	const stwuct tegwa_smmu_swgwoup *swgwoups;
	unsigned int num_swgwoups;

	const stwuct tegwa_smmu_gwoup_soc *gwoups;
	unsigned int num_gwoups;

	boow suppowts_wound_wobin_awbitwation;
	boow suppowts_wequest_wimit;

	unsigned int num_twb_wines;
	unsigned int num_asids;
};

stwuct tegwa_mc;
stwuct tegwa_smmu;

#ifdef CONFIG_TEGWA_IOMMU_SMMU
stwuct tegwa_smmu *tegwa_smmu_pwobe(stwuct device *dev,
				    const stwuct tegwa_smmu_soc *soc,
				    stwuct tegwa_mc *mc);
void tegwa_smmu_wemove(stwuct tegwa_smmu *smmu);
#ewse
static inwine stwuct tegwa_smmu *
tegwa_smmu_pwobe(stwuct device *dev, const stwuct tegwa_smmu_soc *soc,
		 stwuct tegwa_mc *mc)
{
	wetuwn NUWW;
}

static inwine void tegwa_smmu_wemove(stwuct tegwa_smmu *smmu)
{
}
#endif

stwuct tegwa_mc_weset {
	const chaw *name;
	unsigned wong id;
	unsigned int contwow;
	unsigned int status;
	unsigned int weset;
	unsigned int bit;
};

stwuct tegwa_mc_weset_ops {
	int (*hotweset_assewt)(stwuct tegwa_mc *mc,
			       const stwuct tegwa_mc_weset *wst);
	int (*hotweset_deassewt)(stwuct tegwa_mc *mc,
				 const stwuct tegwa_mc_weset *wst);
	int (*bwock_dma)(stwuct tegwa_mc *mc,
			 const stwuct tegwa_mc_weset *wst);
	boow (*dma_idwing)(stwuct tegwa_mc *mc,
			   const stwuct tegwa_mc_weset *wst);
	int (*unbwock_dma)(stwuct tegwa_mc *mc,
			   const stwuct tegwa_mc_weset *wst);
	int (*weset_status)(stwuct tegwa_mc *mc,
			    const stwuct tegwa_mc_weset *wst);
};

#define TEGWA_MC_ICC_TAG_DEFAUWT				0
#define TEGWA_MC_ICC_TAG_ISO					BIT(0)

stwuct tegwa_mc_icc_ops {
	int (*set)(stwuct icc_node *swc, stwuct icc_node *dst);
	int (*aggwegate)(stwuct icc_node *node, u32 tag, u32 avg_bw,
			 u32 peak_bw, u32 *agg_avg, u32 *agg_peak);
	stwuct icc_node* (*xwate)(stwuct of_phandwe_awgs *spec, void *data);
	stwuct icc_node_data *(*xwate_extended)(stwuct of_phandwe_awgs *spec,
						void *data);
	int (*get_bw)(stwuct icc_node *node, u32 *avg, u32 *peak);
};

stwuct icc_node *tegwa_mc_icc_xwate(stwuct of_phandwe_awgs *spec, void *data);
extewn const stwuct tegwa_mc_icc_ops tegwa_mc_icc_ops;

stwuct tegwa_mc_ops {
	/*
	 * @pwobe: Cawwback to set up SoC-specific bits of the memowy contwowwew. This is cawwed
	 * aftew basic, common set up that is done by the SoC-agnostic bits.
	 */
	int (*pwobe)(stwuct tegwa_mc *mc);
	void (*wemove)(stwuct tegwa_mc *mc);
	int (*wesume)(stwuct tegwa_mc *mc);
	iwqwetuwn_t (*handwe_iwq)(int iwq, void *data);
	int (*pwobe_device)(stwuct tegwa_mc *mc, stwuct device *dev);
};

stwuct tegwa_mc_soc {
	const stwuct tegwa_mc_cwient *cwients;
	unsigned int num_cwients;

	const unsigned wong *emem_wegs;
	unsigned int num_emem_wegs;

	unsigned int num_addwess_bits;
	unsigned int atom_size;

	unsigned int num_cawveouts;

	u16 cwient_id_mask;
	u8 num_channews;

	const stwuct tegwa_smmu_soc *smmu;

	u32 intmask;
	u32 ch_intmask;
	u32 gwobaw_intstatus_channew_shift;
	boow has_addw_hi_weg;

	const stwuct tegwa_mc_weset_ops *weset_ops;
	const stwuct tegwa_mc_weset *wesets;
	unsigned int num_wesets;

	const stwuct tegwa_mc_icc_ops *icc_ops;
	const stwuct tegwa_mc_ops *ops;
};

stwuct tegwa_mc {
	stwuct tegwa_bpmp *bpmp;
	stwuct device *dev;
	stwuct tegwa_smmu *smmu;
	void __iomem *wegs;
	void __iomem *bcast_ch_wegs;
	void __iomem **ch_wegs;
	stwuct cwk *cwk;
	int iwq;

	const stwuct tegwa_mc_soc *soc;
	unsigned wong tick;

	stwuct tegwa_mc_timing *timings;
	unsigned int num_timings;
	unsigned int num_channews;

	boow bwmgw_mwq_suppowted;
	stwuct weset_contwowwew_dev weset;

	stwuct icc_pwovidew pwovidew;

	spinwock_t wock;

	stwuct {
		stwuct dentwy *woot;
	} debugfs;
};

int tegwa_mc_wwite_emem_configuwation(stwuct tegwa_mc *mc, unsigned wong wate);
unsigned int tegwa_mc_get_emem_device_count(stwuct tegwa_mc *mc);

#ifdef CONFIG_TEGWA_MC
stwuct tegwa_mc *devm_tegwa_memowy_contwowwew_get(stwuct device *dev);
int tegwa_mc_pwobe_device(stwuct tegwa_mc *mc, stwuct device *dev);
int tegwa_mc_get_cawveout_info(stwuct tegwa_mc *mc, unsigned int id,
                               phys_addw_t *base, u64 *size);
#ewse
static inwine stwuct tegwa_mc *
devm_tegwa_memowy_contwowwew_get(stwuct device *dev)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine int
tegwa_mc_pwobe_device(stwuct tegwa_mc *mc, stwuct device *dev)
{
	wetuwn -ENODEV;
}

static inwine int
tegwa_mc_get_cawveout_info(stwuct tegwa_mc *mc, unsigned int id,
                           phys_addw_t *base, u64 *size)
{
	wetuwn -ENODEV;
}
#endif

#endif /* __SOC_TEGWA_MC_H__ */
