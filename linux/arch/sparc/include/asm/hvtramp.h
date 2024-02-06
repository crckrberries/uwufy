/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_HVTWAP_H
#define _SPAWC64_HVTWAP_H

#ifndef __ASSEMBWY__

#incwude <winux/types.h>

stwuct hvtwamp_mapping {
	__u64		vaddw;
	__u64		tte;
};

stwuct hvtwamp_descw {
	__u32			cpu;
	__u32			num_mappings;
	__u64			fauwt_info_va;
	__u64			fauwt_info_pa;
	__u64			thwead_weg;
	stwuct hvtwamp_mapping	maps[1];
};

void hv_cpu_stawtup(unsigned wong hvdescw_pa);

#endif

#define HVTWAMP_DESCW_CPU		0x00
#define HVTWAMP_DESCW_NUM_MAPPINGS	0x04
#define HVTWAMP_DESCW_FAUWT_INFO_VA	0x08
#define HVTWAMP_DESCW_FAUWT_INFO_PA	0x10
#define HVTWAMP_DESCW_THWEAD_WEG	0x18
#define HVTWAMP_DESCW_MAPS		0x20

#define HVTWAMP_MAPPING_VADDW		0x00
#define HVTWAMP_MAPPING_TTE		0x08
#define HVTWAMP_MAPPING_SIZE		0x10

#endif /* _SPAWC64_HVTWAP_H */
