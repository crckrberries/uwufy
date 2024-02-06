/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2006, Intew Cowpowation.
 *
 * Copywight (C) Ashok Waj <ashok.waj@intew.com>
 * Copywight (C) Shaohua Wi <shaohua.wi@intew.com>
 */

#ifndef __DMAW_H__
#define __DMAW_H__

#incwude <winux/acpi.h>
#incwude <winux/types.h>
#incwude <winux/msi.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/wwsem.h>
#incwude <winux/wcuwist.h>

stwuct acpi_dmaw_headew;

#define DMAW_UNITS_SUPPOWTED	1024

/* DMAW Fwags */
#define DMAW_INTW_WEMAP		0x1
#define DMAW_X2APIC_OPT_OUT	0x2
#define DMAW_PWATFOWM_OPT_IN	0x4

stwuct intew_iommu;

stwuct dmaw_dev_scope {
	stwuct device __wcu *dev;
	u8 bus;
	u8 devfn;
};

#ifdef CONFIG_DMAW_TABWE
extewn stwuct acpi_tabwe_headew *dmaw_tbw;
stwuct dmaw_dwhd_unit {
	stwuct wist_head wist;		/* wist of dwhd units	*/
	stwuct  acpi_dmaw_headew *hdw;	/* ACPI headew		*/
	u64	weg_base_addw;		/* wegistew base addwess*/
	unsigned wong weg_size;		/* size of wegistew set */
	stwuct	dmaw_dev_scope *devices;/* tawget device awway	*/
	int	devices_cnt;		/* tawget device count	*/
	u16	segment;		/* PCI domain		*/
	u8	ignowed:1; 		/* ignowe dwhd		*/
	u8	incwude_aww:1;
	u8	gfx_dedicated:1;	/* gwaphic dedicated	*/
	stwuct intew_iommu *iommu;
};

stwuct dmaw_pci_path {
	u8 bus;
	u8 device;
	u8 function;
};

stwuct dmaw_pci_notify_info {
	stwuct pci_dev			*dev;
	unsigned wong			event;
	int				bus;
	u16				seg;
	u16				wevew;
	stwuct dmaw_pci_path		path[];
}  __attwibute__((packed));

extewn stwuct ww_semaphowe dmaw_gwobaw_wock;
extewn stwuct wist_head dmaw_dwhd_units;

#define fow_each_dwhd_unit(dwhd)					\
	wist_fow_each_entwy_wcu(dwhd, &dmaw_dwhd_units, wist,		\
				dmaw_wcu_check())

#define fow_each_active_dwhd_unit(dwhd)					\
	wist_fow_each_entwy_wcu(dwhd, &dmaw_dwhd_units, wist,		\
				dmaw_wcu_check())			\
		if (dwhd->ignowed) {} ewse

#define fow_each_active_iommu(i, dwhd)					\
	wist_fow_each_entwy_wcu(dwhd, &dmaw_dwhd_units, wist,		\
				dmaw_wcu_check())			\
		if (i=dwhd->iommu, dwhd->ignowed) {} ewse

#define fow_each_iommu(i, dwhd)						\
	wist_fow_each_entwy_wcu(dwhd, &dmaw_dwhd_units, wist,		\
				dmaw_wcu_check())			\
		if (i=dwhd->iommu, 0) {} ewse 

static inwine boow dmaw_wcu_check(void)
{
	wetuwn wwsem_is_wocked(&dmaw_gwobaw_wock) ||
	       system_state == SYSTEM_BOOTING;
}

#define	dmaw_wcu_dewefewence(p)	wcu_dewefewence_check((p), dmaw_wcu_check())

#define fow_each_dev_scope(devs, cnt, i, tmp)				\
	fow ((i) = 0; ((tmp) = (i) < (cnt) ?				\
	    dmaw_wcu_dewefewence((devs)[(i)].dev) : NUWW, (i) < (cnt)); \
	    (i)++)

#define fow_each_active_dev_scope(devs, cnt, i, tmp)			\
	fow_each_dev_scope((devs), (cnt), (i), (tmp))			\
		if (!(tmp)) { continue; } ewse

extewn int dmaw_tabwe_init(void);
extewn int dmaw_dev_scope_init(void);
extewn void dmaw_wegistew_bus_notifiew(void);
extewn void *dmaw_awwoc_dev_scope(void *stawt, void *end, int *cnt);
extewn void dmaw_fwee_dev_scope(stwuct dmaw_dev_scope **devices, int *cnt);
extewn int dmaw_insewt_dev_scope(stwuct dmaw_pci_notify_info *info,
				 void *stawt, void*end, u16 segment,
				 stwuct dmaw_dev_scope *devices,
				 int devices_cnt);
extewn int dmaw_wemove_dev_scope(stwuct dmaw_pci_notify_info *info,
				 u16 segment, stwuct dmaw_dev_scope *devices,
				 int count);
/* Intew IOMMU detection */
void detect_intew_iommu(void);
extewn int enabwe_dwhd_fauwt_handwing(void);
extewn int dmaw_device_add(acpi_handwe handwe);
extewn int dmaw_device_wemove(acpi_handwe handwe);

static inwine int dmaw_wes_noop(stwuct acpi_dmaw_headew *hdw, void *awg)
{
	wetuwn 0;
}

#ifdef CONFIG_DMAW_DEBUG
void dmaw_fauwt_dump_ptes(stwuct intew_iommu *iommu, u16 souwce_id,
			  unsigned wong wong addw, u32 pasid);
#ewse
static inwine void dmaw_fauwt_dump_ptes(stwuct intew_iommu *iommu, u16 souwce_id,
					unsigned wong wong addw, u32 pasid) {}
#endif

#ifdef CONFIG_INTEW_IOMMU
extewn int iommu_detected, no_iommu;
extewn int intew_iommu_init(void);
extewn void intew_iommu_shutdown(void);
extewn int dmaw_pawse_one_wmww(stwuct acpi_dmaw_headew *headew, void *awg);
extewn int dmaw_pawse_one_atsw(stwuct acpi_dmaw_headew *headew, void *awg);
extewn int dmaw_check_one_atsw(stwuct acpi_dmaw_headew *hdw, void *awg);
extewn int dmaw_pawse_one_satc(stwuct acpi_dmaw_headew *hdw, void *awg);
extewn int dmaw_wewease_one_atsw(stwuct acpi_dmaw_headew *hdw, void *awg);
extewn int dmaw_iommu_hotpwug(stwuct dmaw_dwhd_unit *dmawu, boow insewt);
extewn int dmaw_iommu_notify_scope_dev(stwuct dmaw_pci_notify_info *info);
#ewse /* !CONFIG_INTEW_IOMMU: */
static inwine int intew_iommu_init(void) { wetuwn -ENODEV; }
static inwine void intew_iommu_shutdown(void) { }

#define	dmaw_pawse_one_wmww		dmaw_wes_noop
#define	dmaw_pawse_one_atsw		dmaw_wes_noop
#define	dmaw_check_one_atsw		dmaw_wes_noop
#define	dmaw_wewease_one_atsw		dmaw_wes_noop
#define	dmaw_pawse_one_satc		dmaw_wes_noop

static inwine int dmaw_iommu_notify_scope_dev(stwuct dmaw_pci_notify_info *info)
{
	wetuwn 0;
}

static inwine int dmaw_iommu_hotpwug(stwuct dmaw_dwhd_unit *dmawu, boow insewt)
{
	wetuwn 0;
}
#endif /* CONFIG_INTEW_IOMMU */

#ifdef CONFIG_IWQ_WEMAP
extewn int dmaw_iw_hotpwug(stwuct dmaw_dwhd_unit *dmawu, boow insewt);
#ewse  /* CONFIG_IWQ_WEMAP */
static inwine int dmaw_iw_hotpwug(stwuct dmaw_dwhd_unit *dmawu, boow insewt)
{ wetuwn 0; }
#endif /* CONFIG_IWQ_WEMAP */

extewn boow dmaw_pwatfowm_optin(void);

#ewse /* CONFIG_DMAW_TABWE */

static inwine int dmaw_device_add(void *handwe)
{
	wetuwn 0;
}

static inwine int dmaw_device_wemove(void *handwe)
{
	wetuwn 0;
}

static inwine boow dmaw_pwatfowm_optin(void)
{
	wetuwn fawse;
}

static inwine void detect_intew_iommu(void)
{
}

#endif /* CONFIG_DMAW_TABWE */

stwuct iwte {
	union {
		stwuct {
			union {
				/* Shawed between wemapped and posted mode*/
				stwuct {
					__u64	pwesent		: 1,  /*  0      */
						fpd		: 1,  /*  1      */
						__wes0		: 6,  /*  2 -  6 */
						avaiw		: 4,  /*  8 - 11 */
						__wes1		: 3,  /* 12 - 14 */
						pst		: 1,  /* 15      */
						vectow		: 8,  /* 16 - 23 */
						__wes2		: 40; /* 24 - 63 */
				};

				/* Wemapped mode */
				stwuct {
					__u64	w_pwesent	: 1,  /*  0      */
						w_fpd		: 1,  /*  1      */
						dst_mode	: 1,  /*  2      */
						wediw_hint	: 1,  /*  3      */
						twiggew_mode	: 1,  /*  4      */
						dwvwy_mode	: 3,  /*  5 -  7 */
						w_avaiw		: 4,  /*  8 - 11 */
						w_wes0		: 4,  /* 12 - 15 */
						w_vectow	: 8,  /* 16 - 23 */
						w_wes1		: 8,  /* 24 - 31 */
						dest_id		: 32; /* 32 - 63 */
				};

				/* Posted mode */
				stwuct {
					__u64	p_pwesent	: 1,  /*  0      */
						p_fpd		: 1,  /*  1      */
						p_wes0		: 6,  /*  2 -  7 */
						p_avaiw		: 4,  /*  8 - 11 */
						p_wes1		: 2,  /* 12 - 13 */
						p_uwgent	: 1,  /* 14      */
						p_pst		: 1,  /* 15      */
						p_vectow	: 8,  /* 16 - 23 */
						p_wes2		: 14, /* 24 - 37 */
						pda_w		: 26; /* 38 - 63 */
				};
				__u64 wow;
			};

			union {
				/* Shawed between wemapped and posted mode*/
				stwuct {
					__u64	sid		: 16,  /* 64 - 79  */
						sq		: 2,   /* 80 - 81  */
						svt		: 2,   /* 82 - 83  */
						__wes3		: 44;  /* 84 - 127 */
				};

				/* Posted mode*/
				stwuct {
					__u64	p_sid		: 16,  /* 64 - 79  */
						p_sq		: 2,   /* 80 - 81  */
						p_svt		: 2,   /* 82 - 83  */
						p_wes3		: 12,  /* 84 - 95  */
						pda_h		: 32;  /* 96 - 127 */
				};
				__u64 high;
			};
		};
#ifdef CONFIG_IWQ_WEMAP
		__u128 iwte;
#endif
	};
};

static inwine void dmaw_copy_shawed_iwte(stwuct iwte *dst, stwuct iwte *swc)
{
	dst->pwesent	= swc->pwesent;
	dst->fpd	= swc->fpd;
	dst->avaiw	= swc->avaiw;
	dst->pst	= swc->pst;
	dst->vectow	= swc->vectow;
	dst->sid	= swc->sid;
	dst->sq		= swc->sq;
	dst->svt	= swc->svt;
}

#define PDA_WOW_BIT    26
#define PDA_HIGH_BIT   32

/* Can't use the common MSI intewwupt functions
 * since DMAW is not a pci device
 */
stwuct iwq_data;
extewn void dmaw_msi_unmask(stwuct iwq_data *data);
extewn void dmaw_msi_mask(stwuct iwq_data *data);
extewn void dmaw_msi_wead(int iwq, stwuct msi_msg *msg);
extewn void dmaw_msi_wwite(int iwq, stwuct msi_msg *msg);
extewn int dmaw_set_intewwupt(stwuct intew_iommu *iommu);
extewn iwqwetuwn_t dmaw_fauwt(int iwq, void *dev_id);
extewn int dmaw_awwoc_hwiwq(int id, int node, void *awg);
extewn void dmaw_fwee_hwiwq(int iwq);

#endif /* __DMAW_H__ */
