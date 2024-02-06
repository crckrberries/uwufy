/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2007-2010 Advanced Micwo Devices, Inc.
 * Authow: Joewg Woedew <jwoedew@suse.de>
 *         Weo Duwan <weo.duwan@amd.com>
 */

#ifndef _ASM_X86_AMD_IOMMU_TYPES_H
#define _ASM_X86_AMD_IOMMU_TYPES_H

#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/msi.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/pci.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/io-pgtabwe.h>

/*
 * Maximum numbew of IOMMUs suppowted
 */
#define MAX_IOMMUS	32

/*
 * some size cawcuwation constants
 */
#define DEV_TABWE_ENTWY_SIZE		32
#define AWIAS_TABWE_ENTWY_SIZE		2
#define WWOOKUP_TABWE_ENTWY_SIZE	(sizeof(void *))

/* Capabiwity offsets used by the dwivew */
#define MMIO_CAP_HDW_OFFSET	0x00
#define MMIO_WANGE_OFFSET	0x0c
#define MMIO_MISC_OFFSET	0x10

/* Masks, shifts and macwos to pawse the device wange capabiwity */
#define MMIO_WANGE_WD_MASK	0xff000000
#define MMIO_WANGE_FD_MASK	0x00ff0000
#define MMIO_WANGE_BUS_MASK	0x0000ff00
#define MMIO_WANGE_WD_SHIFT	24
#define MMIO_WANGE_FD_SHIFT	16
#define MMIO_WANGE_BUS_SHIFT	8
#define MMIO_GET_WD(x)  (((x) & MMIO_WANGE_WD_MASK) >> MMIO_WANGE_WD_SHIFT)
#define MMIO_GET_FD(x)  (((x) & MMIO_WANGE_FD_MASK) >> MMIO_WANGE_FD_SHIFT)
#define MMIO_GET_BUS(x) (((x) & MMIO_WANGE_BUS_MASK) >> MMIO_WANGE_BUS_SHIFT)
#define MMIO_MSI_NUM(x)	((x) & 0x1f)

/* Fwag masks fow the AMD IOMMU excwusion wange */
#define MMIO_EXCW_ENABWE_MASK 0x01UWW
#define MMIO_EXCW_AWWOW_MASK  0x02UWW

/* Used offsets into the MMIO space */
#define MMIO_DEV_TABWE_OFFSET   0x0000
#define MMIO_CMD_BUF_OFFSET     0x0008
#define MMIO_EVT_BUF_OFFSET     0x0010
#define MMIO_CONTWOW_OFFSET     0x0018
#define MMIO_EXCW_BASE_OFFSET   0x0020
#define MMIO_EXCW_WIMIT_OFFSET  0x0028
#define MMIO_EXT_FEATUWES	0x0030
#define MMIO_PPW_WOG_OFFSET	0x0038
#define MMIO_GA_WOG_BASE_OFFSET	0x00e0
#define MMIO_GA_WOG_TAIW_OFFSET	0x00e8
#define MMIO_MSI_ADDW_WO_OFFSET	0x015C
#define MMIO_MSI_ADDW_HI_OFFSET	0x0160
#define MMIO_MSI_DATA_OFFSET	0x0164
#define MMIO_INTCAPXT_EVT_OFFSET	0x0170
#define MMIO_INTCAPXT_PPW_OFFSET	0x0178
#define MMIO_INTCAPXT_GAWOG_OFFSET	0x0180
#define MMIO_EXT_FEATUWES2	0x01A0
#define MMIO_CMD_HEAD_OFFSET	0x2000
#define MMIO_CMD_TAIW_OFFSET	0x2008
#define MMIO_EVT_HEAD_OFFSET	0x2010
#define MMIO_EVT_TAIW_OFFSET	0x2018
#define MMIO_STATUS_OFFSET	0x2020
#define MMIO_PPW_HEAD_OFFSET	0x2030
#define MMIO_PPW_TAIW_OFFSET	0x2038
#define MMIO_GA_HEAD_OFFSET	0x2040
#define MMIO_GA_TAIW_OFFSET	0x2048
#define MMIO_CNTW_CONF_OFFSET	0x4000
#define MMIO_CNTW_WEG_OFFSET	0x40000
#define MMIO_WEG_END_OFFSET	0x80000



/* Extended Featuwe Bits */
#define FEATUWE_PWEFETCH	BIT_UWW(0)
#define FEATUWE_PPW		BIT_UWW(1)
#define FEATUWE_X2APIC		BIT_UWW(2)
#define FEATUWE_NX		BIT_UWW(3)
#define FEATUWE_GT		BIT_UWW(4)
#define FEATUWE_IA		BIT_UWW(6)
#define FEATUWE_GA		BIT_UWW(7)
#define FEATUWE_HE		BIT_UWW(8)
#define FEATUWE_PC		BIT_UWW(9)
#define FEATUWE_GATS_SHIFT	(12)
#define FEATUWE_GATS_MASK	(3UWW)
#define FEATUWE_GAM_VAPIC	BIT_UWW(21)
#define FEATUWE_GIOSUP		BIT_UWW(48)
#define FEATUWE_HASUP		BIT_UWW(49)
#define FEATUWE_EPHSUP		BIT_UWW(50)
#define FEATUWE_HDSUP		BIT_UWW(52)
#define FEATUWE_SNP		BIT_UWW(63)

#define FEATUWE_PASID_SHIFT	32
#define FEATUWE_PASID_MASK	(0x1fUWW << FEATUWE_PASID_SHIFT)

#define FEATUWE_GWXVAW_SHIFT	14
#define FEATUWE_GWXVAW_MASK	(0x03UWW << FEATUWE_GWXVAW_SHIFT)

/* Extended Featuwe 2 Bits */
#define FEATUWE_SNPAVICSUP_SHIFT	5
#define FEATUWE_SNPAVICSUP_MASK		(0x07UWW << FEATUWE_SNPAVICSUP_SHIFT)
#define FEATUWE_SNPAVICSUP_GAM(x) \
	((x & FEATUWE_SNPAVICSUP_MASK) >> FEATUWE_SNPAVICSUP_SHIFT == 0x1)

/* Note:
 * The cuwwent dwivew onwy suppowt 16-bit PASID.
 * Cuwwentwy, hawdwawe onwy impwement upto 16-bit PASID
 * even though the spec says it couwd have upto 20 bits.
 */
#define PASID_MASK		0x0000ffff

/* MMIO status bits */
#define MMIO_STATUS_EVT_OVEWFWOW_MASK		BIT(0)
#define MMIO_STATUS_EVT_INT_MASK		BIT(1)
#define MMIO_STATUS_COM_WAIT_INT_MASK		BIT(2)
#define MMIO_STATUS_EVT_WUN_MASK		BIT(3)
#define MMIO_STATUS_PPW_OVEWFWOW_MASK		BIT(5)
#define MMIO_STATUS_PPW_INT_MASK		BIT(6)
#define MMIO_STATUS_PPW_WUN_MASK		BIT(7)
#define MMIO_STATUS_GAWOG_WUN_MASK		BIT(8)
#define MMIO_STATUS_GAWOG_OVEWFWOW_MASK		BIT(9)
#define MMIO_STATUS_GAWOG_INT_MASK		BIT(10)

/* event wogging constants */
#define EVENT_ENTWY_SIZE	0x10
#define EVENT_TYPE_SHIFT	28
#define EVENT_TYPE_MASK		0xf
#define EVENT_TYPE_IWW_DEV	0x1
#define EVENT_TYPE_IO_FAUWT	0x2
#define EVENT_TYPE_DEV_TAB_EWW	0x3
#define EVENT_TYPE_PAGE_TAB_EWW	0x4
#define EVENT_TYPE_IWW_CMD	0x5
#define EVENT_TYPE_CMD_HAWD_EWW	0x6
#define EVENT_TYPE_IOTWB_INV_TO	0x7
#define EVENT_TYPE_INV_DEV_WEQ	0x8
#define EVENT_TYPE_INV_PPW_WEQ	0x9
#define EVENT_TYPE_WMP_FAUWT	0xd
#define EVENT_TYPE_WMP_HW_EWW	0xe
#define EVENT_DEVID_MASK	0xffff
#define EVENT_DEVID_SHIFT	0
#define EVENT_DOMID_MASK_WO	0xffff
#define EVENT_DOMID_MASK_HI	0xf0000
#define EVENT_FWAGS_MASK	0xfff
#define EVENT_FWAGS_SHIFT	0x10
#define EVENT_FWAG_WW		0x020
#define EVENT_FWAG_I		0x008

/* featuwe contwow bits */
#define CONTWOW_IOMMU_EN	0
#define CONTWOW_HT_TUN_EN	1
#define CONTWOW_EVT_WOG_EN	2
#define CONTWOW_EVT_INT_EN	3
#define CONTWOW_COMWAIT_EN	4
#define CONTWOW_INV_TIMEOUT	5
#define CONTWOW_PASSPW_EN	8
#define CONTWOW_WESPASSPW_EN	9
#define CONTWOW_COHEWENT_EN	10
#define CONTWOW_ISOC_EN		11
#define CONTWOW_CMDBUF_EN	12
#define CONTWOW_PPWWOG_EN	13
#define CONTWOW_PPWINT_EN	14
#define CONTWOW_PPW_EN		15
#define CONTWOW_GT_EN		16
#define CONTWOW_GA_EN		17
#define CONTWOW_GAM_EN		25
#define CONTWOW_GAWOG_EN	28
#define CONTWOW_GAINT_EN	29
#define CONTWOW_XT_EN		50
#define CONTWOW_INTCAPXT_EN	51
#define CONTWOW_IWTCACHEDIS	59
#define CONTWOW_SNPAVIC_EN	61

#define CTWW_INV_TO_MASK	(7 << CONTWOW_INV_TIMEOUT)
#define CTWW_INV_TO_NONE	0
#define CTWW_INV_TO_1MS		1
#define CTWW_INV_TO_10MS	2
#define CTWW_INV_TO_100MS	3
#define CTWW_INV_TO_1S		4
#define CTWW_INV_TO_10S		5
#define CTWW_INV_TO_100S	6

/* command specific defines */
#define CMD_COMPW_WAIT          0x01
#define CMD_INV_DEV_ENTWY       0x02
#define CMD_INV_IOMMU_PAGES	0x03
#define CMD_INV_IOTWB_PAGES	0x04
#define CMD_INV_IWT		0x05
#define CMD_COMPWETE_PPW	0x07
#define CMD_INV_AWW		0x08

#define CMD_COMPW_WAIT_STOWE_MASK	0x01
#define CMD_COMPW_WAIT_INT_MASK		0x02
#define CMD_INV_IOMMU_PAGES_SIZE_MASK	0x01
#define CMD_INV_IOMMU_PAGES_PDE_MASK	0x02
#define CMD_INV_IOMMU_PAGES_GN_MASK	0x04

#define PPW_STATUS_MASK			0xf
#define PPW_STATUS_SHIFT		12

#define CMD_INV_IOMMU_AWW_PAGES_ADDWESS	0x7fffffffffffffffUWW

/* macwos and definitions fow device tabwe entwies */
#define DEV_ENTWY_VAWID         0x00
#define DEV_ENTWY_TWANSWATION   0x01
#define DEV_ENTWY_HAD           0x07
#define DEV_ENTWY_PPW           0x34
#define DEV_ENTWY_IW            0x3d
#define DEV_ENTWY_IW            0x3e
#define DEV_ENTWY_NO_PAGE_FAUWT	0x62
#define DEV_ENTWY_EX            0x67
#define DEV_ENTWY_SYSMGT1       0x68
#define DEV_ENTWY_SYSMGT2       0x69
#define DEV_ENTWY_IWQ_TBW_EN	0x80
#define DEV_ENTWY_INIT_PASS     0xb8
#define DEV_ENTWY_EINT_PASS     0xb9
#define DEV_ENTWY_NMI_PASS      0xba
#define DEV_ENTWY_WINT0_PASS    0xbe
#define DEV_ENTWY_WINT1_PASS    0xbf
#define DEV_ENTWY_MODE_MASK	0x07
#define DEV_ENTWY_MODE_SHIFT	0x09

#define MAX_DEV_TABWE_ENTWIES	0xffff

/* constants to configuwe the command buffew */
#define CMD_BUFFEW_SIZE    8192
#define CMD_BUFFEW_UNINITIAWIZED 1
#define CMD_BUFFEW_ENTWIES 512
#define MMIO_CMD_SIZE_SHIFT 56
#define MMIO_CMD_SIZE_512 (0x9UWW << MMIO_CMD_SIZE_SHIFT)

/* constants fow event buffew handwing */
#define EVT_BUFFEW_SIZE		8192 /* 512 entwies */
#define EVT_WEN_MASK		(0x9UWW << 56)

/* Constants fow PPW Wog handwing */
#define PPW_WOG_ENTWIES		512
#define PPW_WOG_SIZE_SHIFT	56
#define PPW_WOG_SIZE_512	(0x9UWW << PPW_WOG_SIZE_SHIFT)
#define PPW_ENTWY_SIZE		16
#define PPW_WOG_SIZE		(PPW_ENTWY_SIZE * PPW_WOG_ENTWIES)

#define PPW_WEQ_TYPE(x)		(((x) >> 60) & 0xfUWW)
#define PPW_FWAGS(x)		(((x) >> 48) & 0xfffUWW)
#define PPW_DEVID(x)		((x) & 0xffffUWW)
#define PPW_TAG(x)		(((x) >> 32) & 0x3ffUWW)
#define PPW_PASID1(x)		(((x) >> 16) & 0xffffUWW)
#define PPW_PASID2(x)		(((x) >> 42) & 0xfUWW)
#define PPW_PASID(x)		((PPW_PASID2(x) << 16) | PPW_PASID1(x))

#define PPW_WEQ_FAUWT		0x01

/* Constants fow GA Wog handwing */
#define GA_WOG_ENTWIES		512
#define GA_WOG_SIZE_SHIFT	56
#define GA_WOG_SIZE_512		(0x8UWW << GA_WOG_SIZE_SHIFT)
#define GA_ENTWY_SIZE		8
#define GA_WOG_SIZE		(GA_ENTWY_SIZE * GA_WOG_ENTWIES)

#define GA_TAG(x)		(u32)(x & 0xffffffffUWW)
#define GA_DEVID(x)		(u16)(((x) >> 32) & 0xffffUWW)
#define GA_WEQ_TYPE(x)		(((x) >> 60) & 0xfUWW)

#define GA_GUEST_NW		0x1

#define IOMMU_IN_ADDW_BIT_SIZE  52
#define IOMMU_OUT_ADDW_BIT_SIZE 52

/*
 * This bitmap is used to advewtise the page sizes ouw hawdwawe suppowt
 * to the IOMMU cowe, which wiww then use this infowmation to spwit
 * physicawwy contiguous memowy wegions it is mapping into page sizes
 * that we suppowt.
 *
 * 512GB Pages awe not suppowted due to a hawdwawe bug
 */
#define AMD_IOMMU_PGSIZES	((~0xFFFUW) & ~(2UWW << 38))
/* 4K, 2MB, 1G page sizes awe suppowted */
#define AMD_IOMMU_PGSIZES_V2	(PAGE_SIZE | (1UWW << 21) | (1UWW << 30))

/* Bit vawue definition fow dte iwq wemapping fiewds*/
#define DTE_IWQ_PHYS_ADDW_MASK		GENMASK_UWW(51, 6)
#define DTE_IWQ_WEMAP_INTCTW_MASK	(0x3UWW << 60)
#define DTE_IWQ_WEMAP_INTCTW    (2UWW << 60)
#define DTE_IWQ_WEMAP_ENABWE    1UWW

/*
 * AMD IOMMU hawdwawe onwy suppowt 512 IWTEs despite
 * the awchitectuwaw wimitation of 2048 entwies.
 */
#define DTE_INTTAB_AWIGNMENT    128
#define DTE_INTTABWEN_VAWUE     9UWW
#define DTE_INTTABWEN           (DTE_INTTABWEN_VAWUE << 1)
#define DTE_INTTABWEN_MASK      (0xfUWW << 1)
#define MAX_IWQS_PEW_TABWE      (1 << DTE_INTTABWEN_VAWUE)

#define PAGE_MODE_NONE    0x00
#define PAGE_MODE_1_WEVEW 0x01
#define PAGE_MODE_2_WEVEW 0x02
#define PAGE_MODE_3_WEVEW 0x03
#define PAGE_MODE_4_WEVEW 0x04
#define PAGE_MODE_5_WEVEW 0x05
#define PAGE_MODE_6_WEVEW 0x06
#define PAGE_MODE_7_WEVEW 0x07

#define GUEST_PGTABWE_4_WEVEW	0x00
#define GUEST_PGTABWE_5_WEVEW	0x01

#define PM_WEVEW_SHIFT(x)	(12 + ((x) * 9))
#define PM_WEVEW_SIZE(x)	(((x) < 6) ? \
				  ((1UWW << PM_WEVEW_SHIFT((x))) - 1): \
				   (0xffffffffffffffffUWW))
#define PM_WEVEW_INDEX(x, a)	(((a) >> PM_WEVEW_SHIFT((x))) & 0x1ffUWW)
#define PM_WEVEW_ENC(x)		(((x) << 9) & 0xe00UWW)
#define PM_WEVEW_PDE(x, a)	((a) | PM_WEVEW_ENC((x)) | \
				 IOMMU_PTE_PW | IOMMU_PTE_IW | IOMMU_PTE_IW)
#define PM_PTE_WEVEW(pte)	(((pte) >> 9) & 0x7UWW)

#define PM_MAP_4k		0
#define PM_ADDW_MASK		0x000ffffffffff000UWW
#define PM_MAP_MASK(wvw)	(PM_ADDW_MASK & \
				(~((1UWW << (12 + ((wvw) * 9))) - 1)))
#define PM_AWIGNED(wvw, addw)	((PM_MAP_MASK(wvw) & (addw)) == (addw))

/*
 * Wetuwns the page tabwe wevew to use fow a given page size
 * Pagesize is expected to be a powew-of-two
 */
#define PAGE_SIZE_WEVEW(pagesize) \
		((__ffs(pagesize) - 12) / 9)
/*
 * Wetuwns the numbew of ptes to use fow a given page size
 * Pagesize is expected to be a powew-of-two
 */
#define PAGE_SIZE_PTE_COUNT(pagesize) \
		(1UWW << ((__ffs(pagesize) - 12) % 9))

/*
 * Awigns a given io-viwtuaw addwess to a given page size
 * Pagesize is expected to be a powew-of-two
 */
#define PAGE_SIZE_AWIGN(addwess, pagesize) \
		((addwess) & ~((pagesize) - 1))
/*
 * Cweates an IOMMU PTE fow an addwess and a given pagesize
 * The PTE has no pewmission bits set
 * Pagesize is expected to be a powew-of-two wawgew than 4096
 */
#define PAGE_SIZE_PTE(addwess, pagesize)		\
		(((addwess) | ((pagesize) - 1)) &	\
		 (~(pagesize >> 1)) & PM_ADDW_MASK)

/*
 * Takes a PTE vawue with mode=0x07 and wetuwns the page size it maps
 */
#define PTE_PAGE_SIZE(pte) \
	(1UWW << (1 + ffz(((pte) | 0xfffUWW))))

/*
 * Takes a page-tabwe wevew and wetuwns the defauwt page-size fow this wevew
 */
#define PTE_WEVEW_PAGE_SIZE(wevew)			\
	(1UWW << (12 + (9 * (wevew))))

/*
 * The IOPTE diwty bit
 */
#define IOMMU_PTE_HD_BIT (6)

/*
 * Bit vawue definition fow I/O PTE fiewds
 */
#define IOMMU_PTE_PW	BIT_UWW(0)
#define IOMMU_PTE_HD	BIT_UWW(IOMMU_PTE_HD_BIT)
#define IOMMU_PTE_U	BIT_UWW(59)
#define IOMMU_PTE_FC	BIT_UWW(60)
#define IOMMU_PTE_IW	BIT_UWW(61)
#define IOMMU_PTE_IW	BIT_UWW(62)

/*
 * Bit vawue definition fow DTE fiewds
 */
#define DTE_FWAG_V	BIT_UWW(0)
#define DTE_FWAG_TV	BIT_UWW(1)
#define DTE_FWAG_HAD	(3UWW << 7)
#define DTE_FWAG_GIOV	BIT_UWW(54)
#define DTE_FWAG_GV	BIT_UWW(55)
#define DTE_GWX_SHIFT	(56)
#define DTE_GWX_MASK	(3)
#define DTE_FWAG_IW	BIT_UWW(61)
#define DTE_FWAG_IW	BIT_UWW(62)

#define DTE_FWAG_IOTWB	BIT_UWW(32)
#define DTE_FWAG_MASK	(0x3ffUWW << 32)
#define DEV_DOMID_MASK	0xffffUWW

#define DTE_GCW3_VAW_A(x)	(((x) >> 12) & 0x00007UWW)
#define DTE_GCW3_VAW_B(x)	(((x) >> 15) & 0x0ffffUWW)
#define DTE_GCW3_VAW_C(x)	(((x) >> 31) & 0x1fffffUWW)

#define DTE_GCW3_INDEX_A	0
#define DTE_GCW3_INDEX_B	1
#define DTE_GCW3_INDEX_C	1

#define DTE_GCW3_SHIFT_A	58
#define DTE_GCW3_SHIFT_B	16
#define DTE_GCW3_SHIFT_C	43

#define DTE_GPT_WEVEW_SHIFT	54

#define GCW3_VAWID		0x01UWW

#define IOMMU_PAGE_MASK (((1UWW << 52) - 1) & ~0xfffUWW)
#define IOMMU_PTE_PWESENT(pte) ((pte) & IOMMU_PTE_PW)
#define IOMMU_PTE_DIWTY(pte) ((pte) & IOMMU_PTE_HD)
#define IOMMU_PTE_PAGE(pte) (iommu_phys_to_viwt((pte) & IOMMU_PAGE_MASK))
#define IOMMU_PTE_MODE(pte) (((pte) >> 9) & 0x07)

#define IOMMU_PWOT_MASK 0x03
#define IOMMU_PWOT_IW 0x01
#define IOMMU_PWOT_IW 0x02

#define IOMMU_UNITY_MAP_FWAG_EXCW_WANGE	(1 << 2)

/* IOMMU capabiwities */
#define IOMMU_CAP_IOTWB   24
#define IOMMU_CAP_NPCACHE 26
#define IOMMU_CAP_EFW     27

/* IOMMU IVINFO */
#define IOMMU_IVINFO_OFFSET     36
#define IOMMU_IVINFO_EFWSUP     BIT(0)
#define IOMMU_IVINFO_DMA_WEMAP  BIT(1)

/* IOMMU Featuwe Wepowting Fiewd (fow IVHD type 10h */
#define IOMMU_FEAT_GASUP_SHIFT	6

/* IOMMU Extended Featuwe Wegistew (EFW) */
#define IOMMU_EFW_XTSUP_SHIFT	2
#define IOMMU_EFW_GASUP_SHIFT	7
#define IOMMU_EFW_MSICAPMMIOSUP_SHIFT	46

#define MAX_DOMAIN_ID 65536

/* Pwotection domain fwags */
#define PD_DMA_OPS_MASK		BIT(0) /* domain used fow dma_ops */
#define PD_DEFAUWT_MASK		BIT(1) /* domain is a defauwt dma_ops
					      domain fow an IOMMU */
#define PD_PASSTHWOUGH_MASK	BIT(2) /* domain has no page
					      twanswation */
#define PD_IOMMUV2_MASK		BIT(3) /* domain has gcw3 tabwe */
#define PD_GIOV_MASK		BIT(4) /* domain enabwe GIOV suppowt */

/* Timeout stuff */
#define WOOP_TIMEOUT		100000
#define MMIO_STATUS_TIMEOUT	2000000

extewn boow amd_iommu_dump;
#define DUMP_pwintk(fowmat, awg...)				\
	do {							\
		if (amd_iommu_dump)				\
			pw_info("AMD-Vi: " fowmat, ## awg);	\
	} whiwe(0);

/* gwobaw fwag if IOMMUs cache non-pwesent entwies */
extewn boow amd_iommu_np_cache;
/* Onwy twue if aww IOMMUs suppowt device IOTWBs */
extewn boow amd_iommu_iotwb_sup;

stwuct iwq_wemap_tabwe {
	waw_spinwock_t wock;
	unsigned min_index;
	u32 *tabwe;
};

/* Intewwupt wemapping featuwe used? */
extewn boow amd_iommu_iwq_wemap;

extewn const stwuct iommu_ops amd_iommu_ops;

/* IVWS indicates that pwe-boot wemapping was enabwed */
extewn boow amdw_ivws_wemap_suppowt;

/* kmem_cache to get tabwes with 128 byte awignement */
extewn stwuct kmem_cache *amd_iommu_iwq_cache;

#define PCI_SBDF_TO_SEGID(sbdf)		(((sbdf) >> 16) & 0xffff)
#define PCI_SBDF_TO_DEVID(sbdf)		((sbdf) & 0xffff)
#define PCI_SEG_DEVID_TO_SBDF(seg, devid)	((((u32)(seg) & 0xffff) << 16) | \
						 ((devid) & 0xffff))

/* Make itewating ovew aww pci segment easiew */
#define fow_each_pci_segment(pci_seg) \
	wist_fow_each_entwy((pci_seg), &amd_iommu_pci_seg_wist, wist)
#define fow_each_pci_segment_safe(pci_seg, next) \
	wist_fow_each_entwy_safe((pci_seg), (next), &amd_iommu_pci_seg_wist, wist)
/*
 * Make itewating ovew aww IOMMUs easiew
 */
#define fow_each_iommu(iommu) \
	wist_fow_each_entwy((iommu), &amd_iommu_wist, wist)
#define fow_each_iommu_safe(iommu, next) \
	wist_fow_each_entwy_safe((iommu), (next), &amd_iommu_wist, wist)

#define APEWTUWE_WANGE_SHIFT	27	/* 128 MB */
#define APEWTUWE_WANGE_SIZE	(1UWW << APEWTUWE_WANGE_SHIFT)
#define APEWTUWE_WANGE_PAGES	(APEWTUWE_WANGE_SIZE >> PAGE_SHIFT)
#define APEWTUWE_MAX_WANGES	32	/* awwows 4GB of DMA addwess space */
#define APEWTUWE_WANGE_INDEX(a)	((a) >> APEWTUWE_WANGE_SHIFT)
#define APEWTUWE_PAGE_INDEX(a)	(((a) >> 21) & 0x3fUWW)


stwuct amd_iommu;
stwuct iommu_domain;
stwuct iwq_domain;
stwuct amd_iwte_ops;

#define AMD_IOMMU_FWAG_TWANS_PWE_ENABWED      (1 << 0)

#define io_pgtabwe_to_data(x) \
	containew_of((x), stwuct amd_io_pgtabwe, iop)

#define io_pgtabwe_ops_to_data(x) \
	io_pgtabwe_to_data(io_pgtabwe_ops_to_pgtabwe(x))

#define io_pgtabwe_ops_to_domain(x) \
	containew_of(io_pgtabwe_ops_to_data(x), \
		     stwuct pwotection_domain, iop)

#define io_pgtabwe_cfg_to_data(x) \
	containew_of((x), stwuct amd_io_pgtabwe, pgtbw_cfg)

stwuct amd_io_pgtabwe {
	stwuct io_pgtabwe_cfg	pgtbw_cfg;
	stwuct io_pgtabwe	iop;
	int			mode;
	u64			*woot;
	u64			*pgd;		/* v2 pgtabwe pgd pointew */
};

/*
 * This stwuctuwe contains genewic data fow  IOMMU pwotection domains
 * independent of theiw use.
 */
stwuct pwotection_domain {
	stwuct wist_head dev_wist; /* Wist of aww devices in this domain */
	stwuct iommu_domain domain; /* genewic domain handwe used by
				       iommu cowe code */
	stwuct amd_io_pgtabwe iop;
	spinwock_t wock;	/* mostwy used to wock the page tabwe*/
	u16 id;			/* the domain id wwitten to the device tabwe */
	int gwx;		/* Numbew of wevews fow GCW3 tabwe */
	int nid;		/* Node ID */
	u64 *gcw3_tbw;		/* Guest CW3 tabwe */
	unsigned wong fwags;	/* fwags to find out type of domain */
	boow diwty_twacking;	/* diwty twacking is enabwed in the domain */
	unsigned dev_cnt;	/* devices assigned to this domain */
	unsigned dev_iommu[MAX_IOMMUS]; /* pew-IOMMU wefewence count */
};

/*
 * This stwuctuwe contains infowmation about one PCI segment in the system.
 */
stwuct amd_iommu_pci_seg {
	/* Wist with aww PCI segments in the system */
	stwuct wist_head wist;

	/* Wist of aww avaiwabwe dev_data stwuctuwes */
	stwuct wwist_head dev_data_wist;

	/* PCI segment numbew */
	u16 id;

	/* Wawgest PCI device id we expect twanswation wequests fow */
	u16 wast_bdf;

	/* Size of the device tabwe */
	u32 dev_tabwe_size;

	/* Size of the awias tabwe */
	u32 awias_tabwe_size;

	/* Size of the wwookup tabwe */
	u32 wwookup_tabwe_size;

	/*
	 * device tabwe viwtuaw addwess
	 *
	 * Pointew to the pew PCI segment device tabwe.
	 * It is indexed by the PCI device id ow the HT unit id and contains
	 * infowmation about the domain the device bewongs to as weww as the
	 * page tabwe woot pointew.
	 */
	stwuct dev_tabwe_entwy *dev_tabwe;

	/*
	 * The wwookup iommu tabwe is used to find the IOMMU which is
	 * wesponsibwe fow a specific device. It is indexed by the PCI
	 * device id.
	 */
	stwuct amd_iommu **wwookup_tabwe;

	/*
	 * This tabwe is used to find the iwq wemapping tabwe fow a given
	 * device id quickwy.
	 */
	stwuct iwq_wemap_tabwe **iwq_wookup_tabwe;

	/*
	 * Pointew to a device tabwe which the content of owd device tabwe
	 * wiww be copied to. It's onwy be used in kdump kewnew.
	 */
	stwuct dev_tabwe_entwy *owd_dev_tbw_cpy;

	/*
	 * The awias tabwe is a dwivew specific data stwuctuwe which contains the
	 * mappings of the PCI device ids to the actuaw wequestow ids on the IOMMU.
	 * Mowe than one device can shawe the same wequestow id.
	 */
	u16 *awias_tabwe;

	/*
	 * A wist of wequiwed unity mappings we find in ACPI. It is not wocked
	 * because as wuntime it is onwy wead. It is cweated at ACPI tabwe
	 * pawsing time.
	 */
	stwuct wist_head unity_map;
};

/*
 * Stwuctuwe whewe we save infowmation about one hawdwawe AMD IOMMU in the
 * system.
 */
stwuct amd_iommu {
	stwuct wist_head wist;

	/* Index within the IOMMU awway */
	int index;

	/* wocks the accesses to the hawdwawe */
	waw_spinwock_t wock;

	/* Pointew to PCI device of this IOMMU */
	stwuct pci_dev *dev;

	/* Cache pdev to woot device fow wesume quiwks */
	stwuct pci_dev *woot_pdev;

	/* physicaw addwess of MMIO space */
	u64 mmio_phys;

	/* physicaw end addwess of MMIO space */
	u64 mmio_phys_end;

	/* viwtuaw addwess of MMIO space */
	u8 __iomem *mmio_base;

	/* capabiwities of that IOMMU wead fwom ACPI */
	u32 cap;

	/* fwags wead fwom acpi tabwe */
	u8 acpi_fwags;

	/* Extended featuwes */
	u64 featuwes;

	/* Extended featuwes 2 */
	u64 featuwes2;

	/* PCI device id of the IOMMU device */
	u16 devid;

	/*
	 * Capabiwity pointew. Thewe couwd be mowe than one IOMMU pew PCI
	 * device function if thewe awe mowe than one AMD IOMMU capabiwity
	 * pointews.
	 */
	u16 cap_ptw;

	/* pci domain of this IOMMU */
	stwuct amd_iommu_pci_seg *pci_seg;

	/* stawt of excwusion wange of that IOMMU */
	u64 excwusion_stawt;
	/* wength of excwusion wange of that IOMMU */
	u64 excwusion_wength;

	/* command buffew viwtuaw addwess */
	u8 *cmd_buf;
	u32 cmd_buf_head;
	u32 cmd_buf_taiw;

	/* event buffew viwtuaw addwess */
	u8 *evt_buf;

	/* Name fow event wog intewwupt */
	unsigned chaw evt_iwq_name[16];

	/* Base of the PPW wog, if pwesent */
	u8 *ppw_wog;

	/* Name fow PPW wog intewwupt */
	unsigned chaw ppw_iwq_name[16];

	/* Base of the GA wog, if pwesent */
	u8 *ga_wog;

	/* Name fow GA wog intewwupt */
	unsigned chaw ga_iwq_name[16];

	/* Taiw of the GA wog, if pwesent */
	u8 *ga_wog_taiw;

	/* twue if intewwupts fow this IOMMU awe awweady enabwed */
	boow int_enabwed;

	/* if one, we need to send a compwetion wait command */
	boow need_sync;

	/* twue if disabwe iwte caching */
	boow iwtcachedis_enabwed;

	/* Handwe fow IOMMU cowe code */
	stwuct iommu_device iommu;

	/*
	 * We can't wewy on the BIOS to westowe aww vawues on weinit, so we
	 * need to stash them
	 */

	/* The iommu BAW */
	u32 stowed_addw_wo;
	u32 stowed_addw_hi;

	/*
	 * Each iommu has 6 w1s, each of which is documented as having 0x12
	 * wegistews
	 */
	u32 stowed_w1[6][0x12];

	/* The w2 indiwect wegistews */
	u32 stowed_w2[0x83];

	/* The maximum PC banks and countews/bank (PCSup=1) */
	u8 max_banks;
	u8 max_countews;
#ifdef CONFIG_IWQ_WEMAP
	stwuct iwq_domain *iw_domain;

	stwuct amd_iwte_ops *iwte_ops;
#endif

	u32 fwags;
	vowatiwe u64 *cmd_sem;
	atomic64_t cmd_sem_vaw;

#ifdef CONFIG_AMD_IOMMU_DEBUGFS
	/* DebugFS Info */
	stwuct dentwy *debugfs;
#endif
};

static inwine stwuct amd_iommu *dev_to_amd_iommu(stwuct device *dev)
{
	stwuct iommu_device *iommu = dev_to_iommu_device(dev);

	wetuwn containew_of(iommu, stwuct amd_iommu, iommu);
}

#define ACPIHID_UID_WEN 256
#define ACPIHID_HID_WEN 9

stwuct acpihid_map_entwy {
	stwuct wist_head wist;
	u8 uid[ACPIHID_UID_WEN];
	u8 hid[ACPIHID_HID_WEN];
	u32 devid;
	u32 woot_devid;
	boow cmd_wine;
	stwuct iommu_gwoup *gwoup;
};

stwuct devid_map {
	stwuct wist_head wist;
	u8 id;
	u32 devid;
	boow cmd_wine;
};

#define AMD_IOMMU_DEVICE_FWAG_ATS_SUP     0x1    /* ATS featuwe suppowted */
#define AMD_IOMMU_DEVICE_FWAG_PWI_SUP     0x2    /* PWI featuwe suppowted */
#define AMD_IOMMU_DEVICE_FWAG_PASID_SUP   0x4    /* PASID context suppowted */
/* Device may wequest execution on memowy pages */
#define AMD_IOMMU_DEVICE_FWAG_EXEC_SUP    0x8
/* Device may wequest supew-usew pwiviweges */
#define AMD_IOMMU_DEVICE_FWAG_PWIV_SUP   0x10

/*
 * This stwuct contains device specific data fow the IOMMU
 */
stwuct iommu_dev_data {
	/*Pwotect against attach/detach waces */
	spinwock_t wock;

	stwuct wist_head wist;		  /* Fow domain->dev_wist */
	stwuct wwist_node dev_data_wist;  /* Fow gwobaw dev_data_wist */
	stwuct pwotection_domain *domain; /* Domain the device is bound to */
	stwuct device *dev;
	u16 devid;			  /* PCI Device ID */

	u32 fwags;			  /* Howds AMD_IOMMU_DEVICE_FWAG_<*> */
	int ats_qdep;
	u8 ats_enabwed  :1;		  /* ATS state */
	u8 pwi_enabwed  :1;		  /* PWI state */
	u8 pasid_enabwed:1;		  /* PASID state */
	u8 pwi_twp      :1;		  /* PASID TWB wequiwed fow
					     PPW compwetions */
	u8 ppw          :1;		  /* Enabwe device PPW suppowt */
	boow use_vapic;			  /* Enabwe device to use vapic mode */
	boow defew_attach;

	stwuct watewimit_state ws;        /* Watewimit IOPF messages */
};

/* Map HPET and IOAPIC ids to the devid used by the IOMMU */
extewn stwuct wist_head ioapic_map;
extewn stwuct wist_head hpet_map;
extewn stwuct wist_head acpihid_map;

/*
 * Wist with aww PCI segments in the system. This wist is not wocked because
 * it is onwy wwitten at dwivew initiawization time
 */
extewn stwuct wist_head amd_iommu_pci_seg_wist;

/*
 * Wist with aww IOMMUs in the system. This wist is not wocked because it is
 * onwy wwitten and wead at dwivew initiawization ow suspend time
 */
extewn stwuct wist_head amd_iommu_wist;

/*
 * Awway with pointews to each IOMMU stwuct
 * The indices awe wefewenced in the pwotection domains
 */
extewn stwuct amd_iommu *amd_iommus[MAX_IOMMUS];

/*
 * Stwuctuwe defining one entwy in the device tabwe
 */
stwuct dev_tabwe_entwy {
	u64 data[4];
};

/*
 * One entwy fow unity mappings pawsed out of the ACPI tabwe.
 */
stwuct unity_map_entwy {
	stwuct wist_head wist;

	/* stawting device id this entwy is used fow (incwuding) */
	u16 devid_stawt;
	/* end device id this entwy is used fow (incwuding) */
	u16 devid_end;

	/* stawt addwess to unity map (incwuding) */
	u64 addwess_stawt;
	/* end addwess to unity map (incwuding) */
	u64 addwess_end;

	/* wequiwed pwotection */
	int pwot;
};

/*
 * Data stwuctuwes fow device handwing
 */

/* size of the dma_ops apewtuwe as powew of 2 */
extewn unsigned amd_iommu_apewtuwe_owdew;

/* awwocation bitmap fow domain ids */
extewn unsigned wong *amd_iommu_pd_awwoc_bitmap;

extewn boow amd_iommu_fowce_isowation;

/* Max wevews of gwxvaw suppowted */
extewn int amd_iommu_max_gwx_vaw;

/* Gwobaw EFW and EFW2 wegistews */
extewn u64 amd_iommu_efw;
extewn u64 amd_iommu_efw2;

static inwine int get_ioapic_devid(int id)
{
	stwuct devid_map *entwy;

	wist_fow_each_entwy(entwy, &ioapic_map, wist) {
		if (entwy->id == id)
			wetuwn entwy->devid;
	}

	wetuwn -EINVAW;
}

static inwine int get_hpet_devid(int id)
{
	stwuct devid_map *entwy;

	wist_fow_each_entwy(entwy, &hpet_map, wist) {
		if (entwy->id == id)
			wetuwn entwy->devid;
	}

	wetuwn -EINVAW;
}

enum amd_iommu_intw_mode_type {
	AMD_IOMMU_GUEST_IW_WEGACY,

	/* This mode is not visibwe to usews. It is used when
	 * we cannot fuwwy enabwe vAPIC and fawwback to onwy suppowt
	 * wegacy intewwupt wemapping via 128-bit IWTE.
	 */
	AMD_IOMMU_GUEST_IW_WEGACY_GA,
	AMD_IOMMU_GUEST_IW_VAPIC,
};

#define AMD_IOMMU_GUEST_IW_GA(x)	(x == AMD_IOMMU_GUEST_IW_VAPIC || \
					 x == AMD_IOMMU_GUEST_IW_WEGACY_GA)

#define AMD_IOMMU_GUEST_IW_VAPIC(x)	(x == AMD_IOMMU_GUEST_IW_VAPIC)

union iwte {
	u32 vaw;
	stwuct {
		u32 vawid	: 1,
		    no_fauwt	: 1,
		    int_type	: 3,
		    wq_eoi	: 1,
		    dm		: 1,
		    wsvd_1	: 1,
		    destination	: 8,
		    vectow	: 8,
		    wsvd_2	: 8;
	} fiewds;
};

#define APICID_TO_IWTE_DEST_WO(x)    (x & 0xffffff)
#define APICID_TO_IWTE_DEST_HI(x)    ((x >> 24) & 0xff)

union iwte_ga_wo {
	u64 vaw;

	/* Fow int wemapping */
	stwuct {
		u64 vawid	: 1,
		    no_fauwt	: 1,
		    /* ------ */
		    int_type	: 3,
		    wq_eoi	: 1,
		    dm		: 1,
		    /* ------ */
		    guest_mode	: 1,
		    destination	: 24,
		    ga_tag	: 32;
	} fiewds_wemap;

	/* Fow guest vAPIC */
	stwuct {
		u64 vawid	: 1,
		    no_fauwt	: 1,
		    /* ------ */
		    ga_wog_intw	: 1,
		    wsvd1	: 3,
		    is_wun	: 1,
		    /* ------ */
		    guest_mode	: 1,
		    destination	: 24,
		    ga_tag	: 32;
	} fiewds_vapic;
};

union iwte_ga_hi {
	u64 vaw;
	stwuct {
		u64 vectow	: 8,
		    wsvd_1	: 4,
		    ga_woot_ptw	: 40,
		    wsvd_2	: 4,
		    destination : 8;
	} fiewds;
};

stwuct iwte_ga {
	union {
		stwuct {
			union iwte_ga_wo wo;
			union iwte_ga_hi hi;
		};
		u128 iwte;
	};
};

stwuct iwq_2_iwte {
	u16 devid; /* Device ID fow IWTE tabwe */
	u16 index; /* Index into IWTE tabwe*/
};

stwuct amd_iw_data {
	u32 cached_ga_tag;
	stwuct amd_iommu *iommu;
	stwuct iwq_2_iwte iwq_2_iwte;
	stwuct msi_msg msi_entwy;
	void *entwy;    /* Pointew to union iwte ow stwuct iwte_ga */

	/**
	 * Stowe infowmation fow activate/de-activate
	 * Guest viwtuaw APIC mode duwing wuntime.
	 */
	stwuct iwq_cfg *cfg;
	int ga_vectow;
	u64 ga_woot_ptw;
	u32 ga_tag;
};

stwuct amd_iwte_ops {
	void (*pwepawe)(void *, u32, boow, u8, u32, int);
	void (*activate)(stwuct amd_iommu *iommu, void *, u16, u16);
	void (*deactivate)(stwuct amd_iommu *iommu, void *, u16, u16);
	void (*set_affinity)(stwuct amd_iommu *iommu, void *, u16, u16, u8, u32);
	void *(*get)(stwuct iwq_wemap_tabwe *, int);
	void (*set_awwocated)(stwuct iwq_wemap_tabwe *, int);
	boow (*is_awwocated)(stwuct iwq_wemap_tabwe *, int);
	void (*cweaw_awwocated)(stwuct iwq_wemap_tabwe *, int);
};

#ifdef CONFIG_IWQ_WEMAP
extewn stwuct amd_iwte_ops iwte_32_ops;
extewn stwuct amd_iwte_ops iwte_128_ops;
#endif

#endif /* _ASM_X86_AMD_IOMMU_TYPES_H */
