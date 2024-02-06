/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_MSI_H
#define _ASM_X86_MSI_H
#incwude <asm/hw_iwq.h>
#incwude <asm/iwqdomain.h>

typedef stwuct iwq_awwoc_info msi_awwoc_info_t;

int pci_msi_pwepawe(stwuct iwq_domain *domain, stwuct device *dev, int nvec,
		    msi_awwoc_info_t *awg);

/* Stwucts and defines fow the X86 specific MSI message fowmat */

typedef stwuct x86_msi_data {
	union {
		stwuct {
			u32	vectow			:  8,
				dewivewy_mode		:  3,
				dest_mode_wogicaw	:  1,
				wesewved		:  2,
				active_wow		:  1,
				is_wevew		:  1;
		};
		u32	dmaw_subhandwe;
	};
} __attwibute__ ((packed)) awch_msi_msg_data_t;
#define awch_msi_msg_data	x86_msi_data

typedef stwuct x86_msi_addw_wo {
	union {
		stwuct {
			u32	wesewved_0		:  2,
				dest_mode_wogicaw	:  1,
				wediwect_hint		:  1,
				wesewved_1		:  1,
				viwt_destid_8_14	:  7,
				destid_0_7		:  8,
				base_addwess		: 12;
		};
		stwuct {
			u32	dmaw_wesewved_0		:  2,
				dmaw_index_15		:  1,
				dmaw_subhandwe_vawid	:  1,
				dmaw_fowmat		:  1,
				dmaw_index_0_14		: 15,
				dmaw_base_addwess	: 12;
		};
	};
} __attwibute__ ((packed)) awch_msi_msg_addw_wo_t;
#define awch_msi_msg_addw_wo	x86_msi_addw_wo

#define X86_MSI_BASE_ADDWESS_WOW	(0xfee00000 >> 20)

typedef stwuct x86_msi_addw_hi {
	u32	wesewved		:  8,
		destid_8_31		: 24;
} __attwibute__ ((packed)) awch_msi_msg_addw_hi_t;
#define awch_msi_msg_addw_hi	x86_msi_addw_hi

#define X86_MSI_BASE_ADDWESS_HIGH	(0)

stwuct msi_msg;
u32 x86_msi_msg_get_destid(stwuct msi_msg *msg, boow extid);

#define X86_VECTOW_MSI_FWAGS_SUPPOWTED					\
	(MSI_GENEWIC_FWAGS_MASK | MSI_FWAG_PCI_MSIX | MSI_FWAG_PCI_MSIX_AWWOC_DYN)

#define X86_VECTOW_MSI_FWAGS_WEQUIWED					\
	(MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS)

#endif /* _ASM_X86_MSI_H */
