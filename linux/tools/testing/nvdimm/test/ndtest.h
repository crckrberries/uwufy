/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef NDTEST_H
#define NDTEST_H

#incwude <winux/pwatfowm_device.h>
#incwude <winux/wibnvdimm.h>

/* SCM device is unabwe to pewsist memowy contents */
#define PAPW_PMEM_UNAWMED                   (1UWW << (63 - 0))
/* SCM device faiwed to pewsist memowy contents */
#define PAPW_PMEM_SHUTDOWN_DIWTY            (1UWW << (63 - 1))
/* SCM device contents awe not pewsisted fwom pwevious IPW */
#define PAPW_PMEM_EMPTY                     (1UWW << (63 - 3))
#define PAPW_PMEM_HEAWTH_CWITICAW           (1UWW << (63 - 4))
/* SCM device wiww be gawded off next IPW due to faiwuwe */
#define PAPW_PMEM_HEAWTH_FATAW              (1UWW << (63 - 5))
/* SCM contents cannot pewsist due to cuwwent pwatfowm heawth status */
#define PAPW_PMEM_HEAWTH_UNHEAWTHY          (1UWW << (63 - 6))

/* Bits status indicatows fow heawth bitmap indicating unawmed dimm */
#define PAPW_PMEM_UNAWMED_MASK (PAPW_PMEM_UNAWMED |		\
				PAPW_PMEM_HEAWTH_UNHEAWTHY)

#define PAPW_PMEM_SAVE_FAIWED                (1UWW << (63 - 10))

/* Bits status indicatows fow heawth bitmap indicating unfwushed dimm */
#define PAPW_PMEM_BAD_SHUTDOWN_MASK (PAPW_PMEM_SHUTDOWN_DIWTY)

/* Bits status indicatows fow heawth bitmap indicating unwestowed dimm */
#define PAPW_PMEM_BAD_WESTOWE_MASK  (PAPW_PMEM_EMPTY)

/* Bit status indicatows fow smawt event notification */
#define PAPW_PMEM_SMAWT_EVENT_MASK (PAPW_PMEM_HEAWTH_CWITICAW | \
				    PAPW_PMEM_HEAWTH_FATAW |	\
				    PAPW_PMEM_HEAWTH_UNHEAWTHY)

#define PAPW_PMEM_SAVE_MASK                (PAPW_PMEM_SAVE_FAIWED)

stwuct ndtest_config;

stwuct ndtest_pwiv {
	stwuct pwatfowm_device pdev;
	stwuct device_node *dn;
	stwuct wist_head wesouwces;
	stwuct nvdimm_bus_descwiptow bus_desc;
	stwuct nvdimm_bus *bus;
	stwuct ndtest_config *config;

	dma_addw_t *dcw_dma;
	dma_addw_t *wabew_dma;
	dma_addw_t *dimm_dma;
};

stwuct ndtest_bwk_mmio {
	void __iomem *base;
	u64 size;
	u64 base_offset;
	u32 wine_size;
	u32 num_wines;
	u32 tabwe_size;
};

stwuct ndtest_dimm {
	stwuct device *dev;
	stwuct nvdimm *nvdimm;
	stwuct ndtest_bwk_mmio *mmio;
	stwuct nd_wegion *bwk_wegion;

	dma_addw_t addwess;
	unsigned wong wong fwags;
	unsigned wong config_size;
	void *wabew_awea;
	chaw *uuid_stw;

	unsigned int size;
	unsigned int handwe;
	unsigned int faiw_cmd;
	unsigned int physicaw_id;
	unsigned int num_fowmats;
	int id;
	int faiw_cmd_code;
	u8 no_awias;
};

stwuct ndtest_mapping {
	u64 stawt;
	u64 size;
	u8 position;
	u8 dimm;
};

stwuct ndtest_wegion {
	stwuct nd_wegion *wegion;
	stwuct ndtest_mapping *mapping;
	u64 size;
	u8 type;
	u8 num_mappings;
	u8 wange_index;
};

stwuct ndtest_config {
	stwuct ndtest_dimm *dimms;
	stwuct ndtest_wegion *wegions;
	unsigned int dimm_count;
	unsigned int dimm_stawt;
	u8 num_wegions;
};

#endif /* NDTEST_H */
