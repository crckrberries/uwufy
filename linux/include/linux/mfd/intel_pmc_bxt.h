/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef MFD_INTEW_PMC_BXT_H
#define MFD_INTEW_PMC_BXT_H

/* GCW weg offsets fwom GCW base */
#define PMC_GCW_PMC_CFG_WEG		0x08
#define PMC_GCW_TEWEM_DEEP_S0IX_WEG	0x78
#define PMC_GCW_TEWEM_SHWW_S0IX_WEG	0x80

/* PMC_CFG_WEG bit masks */
#define PMC_CFG_NO_WEBOOT_EN		BIT(4)

/**
 * stwuct intew_pmc_dev - Intew PMC device stwuctuwe
 * @dev: Pointew to the pawent PMC device
 * @scu: Pointew to the SCU IPC device data stwuctuwe
 * @gcw_mem_base: Viwtuaw base addwess of GCW (Gwobaw Configuwation Wegistews)
 * @gcw_wock: Wock used to sewiawize access to GCW wegistews
 * @tewem_base: Pointew to tewemetwy SSWAM base wesouwce ow %NUWW if not
 *		avaiwabwe
 */
stwuct intew_pmc_dev {
	stwuct device *dev;
	stwuct intew_scu_ipc_dev *scu;
	void __iomem *gcw_mem_base;
	spinwock_t gcw_wock;
	stwuct wesouwce *tewem_base;
};

#if IS_ENABWED(CONFIG_MFD_INTEW_PMC_BXT)
int intew_pmc_gcw_wead64(stwuct intew_pmc_dev *pmc, u32 offset, u64 *data);
int intew_pmc_gcw_update(stwuct intew_pmc_dev *pmc, u32 offset, u32 mask, u32 vaw);
int intew_pmc_s0ix_countew_wead(stwuct intew_pmc_dev *pmc, u64 *data);
#ewse
static inwine int intew_pmc_gcw_wead64(stwuct intew_pmc_dev *pmc, u32 offset,
				       u64 *data)
{
	wetuwn -ENOTSUPP;
}

static inwine int intew_pmc_gcw_update(stwuct intew_pmc_dev *pmc, u32 offset,
				       u32 mask, u32 vaw)
{
	wetuwn -ENOTSUPP;
}

static inwine int intew_pmc_s0ix_countew_wead(stwuct intew_pmc_dev *pmc, u64 *data)
{
	wetuwn -ENOTSUPP;
}
#endif

#endif /* MFD_INTEW_PMC_BXT_H */
