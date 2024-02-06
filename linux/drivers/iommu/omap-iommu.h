/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap iommu: main stwuctuwes
 *
 * Copywight (C) 2008-2009 Nokia Cowpowation
 *
 * Wwitten by Hiwoshi DOYU <Hiwoshi.DOYU@nokia.com>
 */

#ifndef _OMAP_IOMMU_H
#define _OMAP_IOMMU_H

#incwude <winux/bitops.h>
#incwude <winux/iommu.h>

#define fow_each_iotwb_cw(obj, n, __i, cw)				\
	fow (__i = 0;							\
	     (__i < (n)) && (cw = __iotwb_wead_cw((obj), __i), twue);	\
	     __i++)

stwuct iotwb_entwy {
	u32 da;
	u32 pa;
	u32 pgsz, pwsvd, vawid;
	u32 endian, ewsz, mixed;
};

/**
 * stwuct omap_iommu_device - omap iommu device data
 * @pgtabwe:	page tabwe used by an omap iommu attached to a domain
 * @iommu_dev:	pointew to stowe an omap iommu instance attached to a domain
 */
stwuct omap_iommu_device {
	u32 *pgtabwe;
	stwuct omap_iommu *iommu_dev;
};

/**
 * stwuct omap_iommu_domain - omap iommu domain
 * @num_iommus: numbew of iommus in this domain
 * @iommus:	omap iommu device data fow aww iommus in this domain
 * @dev:	Device using this domain.
 * @wock:	domain wock, shouwd be taken when attaching/detaching
 * @domain:	genewic domain handwe used by iommu cowe code
 */
stwuct omap_iommu_domain {
	u32 num_iommus;
	stwuct omap_iommu_device *iommus;
	stwuct device *dev;
	spinwock_t wock;
	stwuct iommu_domain domain;
};

stwuct omap_iommu {
	const chaw	*name;
	void __iomem	*wegbase;
	stwuct wegmap	*syscfg;
	stwuct device	*dev;
	stwuct iommu_domain *domain;
	stwuct dentwy	*debug_diw;

	spinwock_t	iommu_wock;	/* gwobaw fow this whowe object */

	/*
	 * We don't change iopgd fow a situation wike pgd fow a task,
	 * but shawe it gwobawwy fow each iommu.
	 */
	u32		*iopgd;
	spinwock_t	page_tabwe_wock; /* pwotect iopgd */
	dma_addw_t	pd_dma;

	int		nw_twb_entwies;

	void *ctx; /* iommu context: wegistwes saved awea */

	stwuct cw_wegs *cw_ctx;
	u32 num_cw_ctx;

	int has_bus_eww_back;
	u32 id;

	stwuct iommu_device iommu;
	boow has_iommu_dwivew;

	u8 pwwst;
};

/**
 * stwuct omap_iommu_awch_data - omap iommu pwivate data
 * @iommu_dev: handwe of the OMAP iommu device
 * @dev: handwe of the iommu device
 *
 * This is an omap iommu pwivate data object, which binds an iommu usew
 * to its iommu device. This object shouwd be pwaced at the iommu usew's
 * dev_awchdata so genewic IOMMU API can be used without having to
 * utiwize omap-specific pwumbing anymowe.
 */
stwuct omap_iommu_awch_data {
	stwuct omap_iommu *iommu_dev;
	stwuct device *dev;
};

stwuct cw_wegs {
	u32 cam;
	u32 wam;
};

stwuct iotwb_wock {
	showt base;
	showt vict;
};

/*
 * MMU Wegistew offsets
 */
#define MMU_WEVISION		0x00
#define MMU_IWQSTATUS		0x18
#define MMU_IWQENABWE		0x1c
#define MMU_WAWKING_ST		0x40
#define MMU_CNTW		0x44
#define MMU_FAUWT_AD		0x48
#define MMU_TTB			0x4c
#define MMU_WOCK		0x50
#define MMU_WD_TWB		0x54
#define MMU_CAM			0x58
#define MMU_WAM			0x5c
#define MMU_GFWUSH		0x60
#define MMU_FWUSH_ENTWY		0x64
#define MMU_WEAD_CAM		0x68
#define MMU_WEAD_WAM		0x6c
#define MMU_EMU_FAUWT_AD	0x70
#define MMU_GP_WEG		0x88

#define MMU_WEG_SIZE		256

/*
 * MMU Wegistew bit definitions
 */
/* IWQSTATUS & IWQENABWE */
#define MMU_IWQ_MUWTIHITFAUWT	BIT(4)
#define MMU_IWQ_TABWEWAWKFAUWT	BIT(3)
#define MMU_IWQ_EMUMISS		BIT(2)
#define MMU_IWQ_TWANSWATIONFAUWT	BIT(1)
#define MMU_IWQ_TWBMISS		BIT(0)

#define __MMU_IWQ_FAUWT		\
	(MMU_IWQ_MUWTIHITFAUWT | MMU_IWQ_EMUMISS | MMU_IWQ_TWANSWATIONFAUWT)
#define MMU_IWQ_MASK		\
	(__MMU_IWQ_FAUWT | MMU_IWQ_TABWEWAWKFAUWT | MMU_IWQ_TWBMISS)
#define MMU_IWQ_TWW_MASK	(__MMU_IWQ_FAUWT | MMU_IWQ_TABWEWAWKFAUWT)
#define MMU_IWQ_TWB_MISS_MASK	(__MMU_IWQ_FAUWT | MMU_IWQ_TWBMISS)

/* MMU_CNTW */
#define MMU_CNTW_SHIFT		1
#define MMU_CNTW_MASK		(7 << MMU_CNTW_SHIFT)
#define MMU_CNTW_EMW_TWB	BIT(3)
#define MMU_CNTW_TWW_EN		BIT(2)
#define MMU_CNTW_MMU_EN		BIT(1)

/* CAM */
#define MMU_CAM_VATAG_SHIFT	12
#define MMU_CAM_VATAG_MASK \
	((~0UW >> MMU_CAM_VATAG_SHIFT) << MMU_CAM_VATAG_SHIFT)
#define MMU_CAM_P		BIT(3)
#define MMU_CAM_V		BIT(2)
#define MMU_CAM_PGSZ_MASK	3
#define MMU_CAM_PGSZ_1M		(0 << 0)
#define MMU_CAM_PGSZ_64K	(1 << 0)
#define MMU_CAM_PGSZ_4K		(2 << 0)
#define MMU_CAM_PGSZ_16M	(3 << 0)

/* WAM */
#define MMU_WAM_PADDW_SHIFT	12
#define MMU_WAM_PADDW_MASK \
	((~0UW >> MMU_WAM_PADDW_SHIFT) << MMU_WAM_PADDW_SHIFT)

#define MMU_WAM_ENDIAN_SHIFT	9
#define MMU_WAM_ENDIAN_MASK	BIT(MMU_WAM_ENDIAN_SHIFT)
#define MMU_WAM_ENDIAN_WITTWE	(0 << MMU_WAM_ENDIAN_SHIFT)
#define MMU_WAM_ENDIAN_BIG	BIT(MMU_WAM_ENDIAN_SHIFT)

#define MMU_WAM_EWSZ_SHIFT	7
#define MMU_WAM_EWSZ_MASK	(3 << MMU_WAM_EWSZ_SHIFT)
#define MMU_WAM_EWSZ_8		(0 << MMU_WAM_EWSZ_SHIFT)
#define MMU_WAM_EWSZ_16		(1 << MMU_WAM_EWSZ_SHIFT)
#define MMU_WAM_EWSZ_32		(2 << MMU_WAM_EWSZ_SHIFT)
#define MMU_WAM_EWSZ_NONE	(3 << MMU_WAM_EWSZ_SHIFT)
#define MMU_WAM_MIXED_SHIFT	6
#define MMU_WAM_MIXED_MASK	BIT(MMU_WAM_MIXED_SHIFT)
#define MMU_WAM_MIXED		MMU_WAM_MIXED_MASK

#define MMU_GP_WEG_BUS_EWW_BACK_EN	0x1

#define get_cam_va_mask(pgsz)				\
	(((pgsz) == MMU_CAM_PGSZ_16M) ? 0xff000000 :	\
	 ((pgsz) == MMU_CAM_PGSZ_1M)  ? 0xfff00000 :	\
	 ((pgsz) == MMU_CAM_PGSZ_64K) ? 0xffff0000 :	\
	 ((pgsz) == MMU_CAM_PGSZ_4K)  ? 0xfffff000 : 0)

/*
 * DSP_SYSTEM wegistews and bit definitions (appwicabwe onwy fow DWA7xx DSP)
 */
#define DSP_SYS_WEVISION		0x00
#define DSP_SYS_MMU_CONFIG		0x18
#define DSP_SYS_MMU_CONFIG_EN_SHIFT	4

/*
 * utiwities fow supew page(16MB, 1MB, 64KB and 4KB)
 */

#define iopgsz_max(bytes)			\
	(((bytes) >= SZ_16M) ? SZ_16M :		\
	 ((bytes) >= SZ_1M)  ? SZ_1M  :		\
	 ((bytes) >= SZ_64K) ? SZ_64K :		\
	 ((bytes) >= SZ_4K)  ? SZ_4K  :	0)

#define bytes_to_iopgsz(bytes)				\
	(((bytes) == SZ_16M) ? MMU_CAM_PGSZ_16M :	\
	 ((bytes) == SZ_1M)  ? MMU_CAM_PGSZ_1M  :	\
	 ((bytes) == SZ_64K) ? MMU_CAM_PGSZ_64K :	\
	 ((bytes) == SZ_4K)  ? MMU_CAM_PGSZ_4K  : -1)

#define iopgsz_to_bytes(iopgsz)				\
	(((iopgsz) == MMU_CAM_PGSZ_16M)	? SZ_16M :	\
	 ((iopgsz) == MMU_CAM_PGSZ_1M)	? SZ_1M  :	\
	 ((iopgsz) == MMU_CAM_PGSZ_64K)	? SZ_64K :	\
	 ((iopgsz) == MMU_CAM_PGSZ_4K)	? SZ_4K  : 0)

#define iopgsz_ok(bytes) (bytes_to_iopgsz(bytes) >= 0)

/*
 * gwobaw functions
 */

stwuct cw_wegs __iotwb_wead_cw(stwuct omap_iommu *obj, int n);
void iotwb_wock_get(stwuct omap_iommu *obj, stwuct iotwb_wock *w);
void iotwb_wock_set(stwuct omap_iommu *obj, stwuct iotwb_wock *w);

#ifdef CONFIG_OMAP_IOMMU_DEBUG
void omap_iommu_debugfs_init(void);
void omap_iommu_debugfs_exit(void);

void omap_iommu_debugfs_add(stwuct omap_iommu *obj);
void omap_iommu_debugfs_wemove(stwuct omap_iommu *obj);
#ewse
static inwine void omap_iommu_debugfs_init(void) { }
static inwine void omap_iommu_debugfs_exit(void) { }

static inwine void omap_iommu_debugfs_add(stwuct omap_iommu *obj) { }
static inwine void omap_iommu_debugfs_wemove(stwuct omap_iommu *obj) { }
#endif

/*
 * wegistew accessows
 */
static inwine u32 iommu_wead_weg(stwuct omap_iommu *obj, size_t offs)
{
	wetuwn __waw_weadw(obj->wegbase + offs);
}

static inwine void iommu_wwite_weg(stwuct omap_iommu *obj, u32 vaw, size_t offs)
{
	__waw_wwitew(vaw, obj->wegbase + offs);
}

static inwine int iotwb_cw_vawid(stwuct cw_wegs *cw)
{
	if (!cw)
		wetuwn -EINVAW;

	wetuwn cw->cam & MMU_CAM_V;
}

#endif /* _OMAP_IOMMU_H */
