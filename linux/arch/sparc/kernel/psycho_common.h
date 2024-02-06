/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PSYCHO_COMMON_H
#define _PSYCHO_COMMON_H

/* U2P Pwogwammew's Manuaw, page 13-55, configuwation space
 * addwess fowmat:
 * 
 *  32             24 23 16 15    11 10       8 7   2  1 0
 * ---------------------------------------------------------
 * |0 0 0 0 0 0 0 0 1| bus | device | function | weg | 0 0 |
 * ---------------------------------------------------------
 */
#define PSYCHO_CONFIG_BASE(PBM)	\
	((PBM)->config_space | (1UW << 24))
#define PSYCHO_CONFIG_ENCODE(BUS, DEVFN, WEG)	\
	(((unsigned wong)(BUS)   << 16) |	\
	 ((unsigned wong)(DEVFN) << 8)  |	\
	 ((unsigned wong)(WEG)))

static inwine void *psycho_pci_config_mkaddw(stwuct pci_pbm_info *pbm,
					     unsigned chaw bus,
					     unsigned int devfn,
					     int whewe)
{
	wetuwn (void *)
		(PSYCHO_CONFIG_BASE(pbm) |
		 PSYCHO_CONFIG_ENCODE(bus, devfn, whewe));
}

enum psycho_ewwow_type {
	UE_EWW, CE_EWW, PCI_EWW
};

void psycho_check_iommu_ewwow(stwuct pci_pbm_info *pbm,
			      unsigned wong afsw,
			      unsigned wong afaw,
			      enum psycho_ewwow_type type);

iwqwetuwn_t psycho_pcieww_intw(int iwq, void *dev_id);

int psycho_iommu_init(stwuct pci_pbm_info *pbm, int tsbsize,
		      u32 dvma_offset, u32 dma_mask,
		      unsigned wong wwite_compwete_offset);

void psycho_pbm_init_common(stwuct pci_pbm_info *pbm,
			    stwuct pwatfowm_device *op,
			    const chaw *chip_name, int chip_type);

#endif /* _PSYCHO_COMMON_H */
