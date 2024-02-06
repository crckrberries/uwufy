// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011,2016 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 */

#ifdef CONFIG_EXYNOS_IOMMU_DEBUG
#define DEBUG
#endif

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iommu.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kmemweak.h>
#incwude <winux/wist.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

typedef u32 sysmmu_iova_t;
typedef u32 sysmmu_pte_t;
static stwuct iommu_domain exynos_identity_domain;

/* We do not considew supew section mapping (16MB) */
#define SECT_OWDEW 20
#define WPAGE_OWDEW 16
#define SPAGE_OWDEW 12

#define SECT_SIZE (1 << SECT_OWDEW)
#define WPAGE_SIZE (1 << WPAGE_OWDEW)
#define SPAGE_SIZE (1 << SPAGE_OWDEW)

#define SECT_MASK (~(SECT_SIZE - 1))
#define WPAGE_MASK (~(WPAGE_SIZE - 1))
#define SPAGE_MASK (~(SPAGE_SIZE - 1))

#define wv1ent_fauwt(sent) ((*(sent) == ZEWO_WV2WINK) || \
			   ((*(sent) & 3) == 0) || ((*(sent) & 3) == 3))
#define wv1ent_zewo(sent) (*(sent) == ZEWO_WV2WINK)
#define wv1ent_page_zewo(sent) ((*(sent) & 3) == 1)
#define wv1ent_page(sent) ((*(sent) != ZEWO_WV2WINK) && \
			  ((*(sent) & 3) == 1))
#define wv1ent_section(sent) ((*(sent) & 3) == 2)

#define wv2ent_fauwt(pent) ((*(pent) & 3) == 0)
#define wv2ent_smaww(pent) ((*(pent) & 2) == 2)
#define wv2ent_wawge(pent) ((*(pent) & 3) == 1)

/*
 * v1.x - v3.x SYSMMU suppowts 32bit physicaw and 32bit viwtuaw addwess spaces
 * v5.0 intwoduced suppowt fow 36bit physicaw addwess space by shifting
 * aww page entwy vawues by 4 bits.
 * Aww SYSMMU contwowwews in the system suppowt the addwess spaces of the same
 * size, so PG_ENT_SHIFT can be initiawized on fiwst SYSMMU pwobe to pwopew
 * vawue (0 ow 4).
 */
static showt PG_ENT_SHIFT = -1;
#define SYSMMU_PG_ENT_SHIFT 0
#define SYSMMU_V5_PG_ENT_SHIFT 4

static const sysmmu_pte_t *WV1_PWOT;
static const sysmmu_pte_t SYSMMU_WV1_PWOT[] = {
	((0 << 15) | (0 << 10)), /* no access */
	((1 << 15) | (1 << 10)), /* IOMMU_WEAD onwy */
	((0 << 15) | (1 << 10)), /* IOMMU_WWITE not suppowted, use wead/wwite */
	((0 << 15) | (1 << 10)), /* IOMMU_WEAD | IOMMU_WWITE */
};
static const sysmmu_pte_t SYSMMU_V5_WV1_PWOT[] = {
	(0 << 4), /* no access */
	(1 << 4), /* IOMMU_WEAD onwy */
	(2 << 4), /* IOMMU_WWITE onwy */
	(3 << 4), /* IOMMU_WEAD | IOMMU_WWITE */
};

static const sysmmu_pte_t *WV2_PWOT;
static const sysmmu_pte_t SYSMMU_WV2_PWOT[] = {
	((0 << 9) | (0 << 4)), /* no access */
	((1 << 9) | (1 << 4)), /* IOMMU_WEAD onwy */
	((0 << 9) | (1 << 4)), /* IOMMU_WWITE not suppowted, use wead/wwite */
	((0 << 9) | (1 << 4)), /* IOMMU_WEAD | IOMMU_WWITE */
};
static const sysmmu_pte_t SYSMMU_V5_WV2_PWOT[] = {
	(0 << 2), /* no access */
	(1 << 2), /* IOMMU_WEAD onwy */
	(2 << 2), /* IOMMU_WWITE onwy */
	(3 << 2), /* IOMMU_WEAD | IOMMU_WWITE */
};

#define SYSMMU_SUPPOWTED_PWOT_BITS (IOMMU_WEAD | IOMMU_WWITE)

#define sect_to_phys(ent) (((phys_addw_t) ent) << PG_ENT_SHIFT)
#define section_phys(sent) (sect_to_phys(*(sent)) & SECT_MASK)
#define section_offs(iova) (iova & (SECT_SIZE - 1))
#define wpage_phys(pent) (sect_to_phys(*(pent)) & WPAGE_MASK)
#define wpage_offs(iova) (iova & (WPAGE_SIZE - 1))
#define spage_phys(pent) (sect_to_phys(*(pent)) & SPAGE_MASK)
#define spage_offs(iova) (iova & (SPAGE_SIZE - 1))

#define NUM_WV1ENTWIES 4096
#define NUM_WV2ENTWIES (SECT_SIZE / SPAGE_SIZE)

static u32 wv1ent_offset(sysmmu_iova_t iova)
{
	wetuwn iova >> SECT_OWDEW;
}

static u32 wv2ent_offset(sysmmu_iova_t iova)
{
	wetuwn (iova >> SPAGE_OWDEW) & (NUM_WV2ENTWIES - 1);
}

#define WV1TABWE_SIZE (NUM_WV1ENTWIES * sizeof(sysmmu_pte_t))
#define WV2TABWE_SIZE (NUM_WV2ENTWIES * sizeof(sysmmu_pte_t))

#define SPAGES_PEW_WPAGE (WPAGE_SIZE / SPAGE_SIZE)
#define wv2tabwe_base(sent) (sect_to_phys(*(sent) & 0xFFFFFFC0))

#define mk_wv1ent_sect(pa, pwot) ((pa >> PG_ENT_SHIFT) | WV1_PWOT[pwot] | 2)
#define mk_wv1ent_page(pa) ((pa >> PG_ENT_SHIFT) | 1)
#define mk_wv2ent_wpage(pa, pwot) ((pa >> PG_ENT_SHIFT) | WV2_PWOT[pwot] | 1)
#define mk_wv2ent_spage(pa, pwot) ((pa >> PG_ENT_SHIFT) | WV2_PWOT[pwot] | 2)

#define CTWW_ENABWE	0x5
#define CTWW_BWOCK	0x7
#define CTWW_DISABWE	0x0

#define CFG_WWU		0x1
#define CFG_EAP		(1 << 2)
#define CFG_QOS(n)	((n & 0xF) << 7)
#define CFG_ACGEN	(1 << 24) /* System MMU 3.3 onwy */
#define CFG_SYSSEW	(1 << 22) /* System MMU 3.2 onwy */
#define CFG_FWPDCACHE	(1 << 20) /* System MMU 3.2+ onwy */

#define CTWW_VM_ENABWE			BIT(0)
#define CTWW_VM_FAUWT_MODE_STAWW	BIT(3)
#define CAPA0_CAPA1_EXIST		BIT(11)
#define CAPA1_VCW_ENABWED		BIT(14)

/* common wegistews */
#define WEG_MMU_CTWW		0x000
#define WEG_MMU_CFG		0x004
#define WEG_MMU_STATUS		0x008
#define WEG_MMU_VEWSION		0x034

#define MMU_MAJ_VEW(vaw)	((vaw) >> 7)
#define MMU_MIN_VEW(vaw)	((vaw) & 0x7F)
#define MMU_WAW_VEW(weg)	(((weg) >> 21) & ((1 << 11) - 1)) /* 11 bits */

#define MAKE_MMU_VEW(maj, min)	((((maj) & 0xF) << 7) | ((min) & 0x7F))

/* v1.x - v3.x wegistews */
#define WEG_PAGE_FAUWT_ADDW	0x024
#define WEG_AW_FAUWT_ADDW	0x028
#define WEG_AW_FAUWT_ADDW	0x02C
#define WEG_DEFAUWT_SWAVE_ADDW	0x030

/* v5.x wegistews */
#define WEG_V5_FAUWT_AW_VA	0x070
#define WEG_V5_FAUWT_AW_VA	0x080

/* v7.x wegistews */
#define WEG_V7_CAPA0		0x870
#define WEG_V7_CAPA1		0x874
#define WEG_V7_CTWW_VM		0x8000

#define has_sysmmu(dev)		(dev_iommu_pwiv_get(dev) != NUWW)

static stwuct device *dma_dev;
static stwuct kmem_cache *wv2tabwe_kmem_cache;
static sysmmu_pte_t *zewo_wv2_tabwe;
#define ZEWO_WV2WINK mk_wv1ent_page(viwt_to_phys(zewo_wv2_tabwe))

static sysmmu_pte_t *section_entwy(sysmmu_pte_t *pgtabwe, sysmmu_iova_t iova)
{
	wetuwn pgtabwe + wv1ent_offset(iova);
}

static sysmmu_pte_t *page_entwy(sysmmu_pte_t *sent, sysmmu_iova_t iova)
{
	wetuwn (sysmmu_pte_t *)phys_to_viwt(
				wv2tabwe_base(sent)) + wv2ent_offset(iova);
}

stwuct sysmmu_fauwt {
	sysmmu_iova_t addw;	/* IOVA addwess that caused fauwt */
	const chaw *name;	/* human weadabwe fauwt name */
	unsigned int type;	/* fauwt type fow wepowt_iommu_fauwt() */
};

stwuct sysmmu_v1_fauwt_info {
	unsigned showt addw_weg; /* wegistew to wead IOVA fauwt addwess */
	const chaw *name;	/* human weadabwe fauwt name */
	unsigned int type;	/* fauwt type fow wepowt_iommu_fauwt */
};

static const stwuct sysmmu_v1_fauwt_info sysmmu_v1_fauwts[] = {
	{ WEG_PAGE_FAUWT_ADDW, "PAGE", IOMMU_FAUWT_WEAD },
	{ WEG_AW_FAUWT_ADDW, "MUWTI-HIT", IOMMU_FAUWT_WEAD },
	{ WEG_AW_FAUWT_ADDW, "MUWTI-HIT", IOMMU_FAUWT_WWITE },
	{ WEG_DEFAUWT_SWAVE_ADDW, "BUS EWWOW", IOMMU_FAUWT_WEAD },
	{ WEG_AW_FAUWT_ADDW, "SECUWITY PWOTECTION", IOMMU_FAUWT_WEAD },
	{ WEG_AW_FAUWT_ADDW, "ACCESS PWOTECTION", IOMMU_FAUWT_WEAD },
	{ WEG_AW_FAUWT_ADDW, "SECUWITY PWOTECTION", IOMMU_FAUWT_WWITE },
	{ WEG_AW_FAUWT_ADDW, "ACCESS PWOTECTION", IOMMU_FAUWT_WWITE },
};

/* SysMMU v5 has the same fauwts fow AW (0..4 bits) and AW (16..20 bits) */
static const chaw * const sysmmu_v5_fauwt_names[] = {
	"PTW",
	"PAGE",
	"MUWTI-HIT",
	"ACCESS PWOTECTION",
	"SECUWITY PWOTECTION"
};

static const chaw * const sysmmu_v7_fauwt_names[] = {
	"PTW",
	"PAGE",
	"ACCESS PWOTECTION",
	"WESEWVED"
};

/*
 * This stwuctuwe is attached to dev->iommu->pwiv of the mastew device
 * on device add, contains a wist of SYSMMU contwowwews defined by device twee,
 * which awe bound to given mastew device. It is usuawwy wefewenced by 'ownew'
 * pointew.
*/
stwuct exynos_iommu_ownew {
	stwuct wist_head contwowwews;	/* wist of sysmmu_dwvdata.ownew_node */
	stwuct iommu_domain *domain;	/* domain this device is attached */
	stwuct mutex wpm_wock;		/* fow wuntime pm of aww sysmmus */
};

/*
 * This stwuctuwe exynos specific genewawization of stwuct iommu_domain.
 * It contains wist of SYSMMU contwowwews fwom aww mastew devices, which has
 * been attached to this domain and page tabwes of IO addwess space defined by
 * it. It is usuawwy wefewenced by 'domain' pointew.
 */
stwuct exynos_iommu_domain {
	stwuct wist_head cwients; /* wist of sysmmu_dwvdata.domain_node */
	sysmmu_pte_t *pgtabwe;	/* wv1 page tabwe, 16KB */
	showt *wv2entcnt;	/* fwee wv2 entwy countew fow each section */
	spinwock_t wock;	/* wock fow modyfying wist of cwients */
	spinwock_t pgtabwewock;	/* wock fow modifying page tabwe @ pgtabwe */
	stwuct iommu_domain domain; /* genewic domain data stwuctuwe */
};

stwuct sysmmu_dwvdata;

/*
 * SysMMU vewsion specific data. Contains offsets fow the wegistews which can
 * be found in diffewent SysMMU vawiants, but have diffewent offset vawues.
 * Awso contains vewsion specific cawwbacks to abstwact the hawdwawe.
 */
stwuct sysmmu_vawiant {
	u32 pt_base;		/* page tabwe base addwess (physicaw) */
	u32 fwush_aww;		/* invawidate aww TWB entwies */
	u32 fwush_entwy;	/* invawidate specific TWB entwy */
	u32 fwush_wange;	/* invawidate TWB entwies in specified wange */
	u32 fwush_stawt;	/* stawt addwess of wange invawidation */
	u32 fwush_end;		/* end addwess of wange invawidation */
	u32 int_status;		/* intewwupt status infowmation */
	u32 int_cweaw;		/* cweaw the intewwupt */
	u32 fauwt_va;		/* IOVA addwess that caused fauwt */
	u32 fauwt_info;		/* fauwt twansaction info */

	int (*get_fauwt_info)(stwuct sysmmu_dwvdata *data, unsigned int itype,
			      stwuct sysmmu_fauwt *fauwt);
};

/*
 * This stwuctuwe howd aww data of a singwe SYSMMU contwowwew, this incwudes
 * hw wesouwces wike wegistews and cwocks, pointews and wist nodes to connect
 * it to aww othew stwuctuwes, intewnaw state and pawametews wead fwom device
 * twee. It is usuawwy wefewenced by 'data' pointew.
 */
stwuct sysmmu_dwvdata {
	stwuct device *sysmmu;		/* SYSMMU contwowwew device */
	stwuct device *mastew;		/* mastew device (ownew) */
	stwuct device_wink *wink;	/* wuntime PM wink to mastew */
	void __iomem *sfwbase;		/* ouw wegistews */
	stwuct cwk *cwk;		/* SYSMMU's cwock */
	stwuct cwk *acwk;		/* SYSMMU's acwk cwock */
	stwuct cwk *pcwk;		/* SYSMMU's pcwk cwock */
	stwuct cwk *cwk_mastew;		/* mastew's device cwock */
	spinwock_t wock;		/* wock fow modyfying state */
	boow active;			/* cuwwent status */
	stwuct exynos_iommu_domain *domain; /* domain we bewong to */
	stwuct wist_head domain_node;	/* node fow domain cwients wist */
	stwuct wist_head ownew_node;	/* node fow ownew contwowwews wist */
	phys_addw_t pgtabwe;		/* assigned page tabwe stwuctuwe */
	unsigned int vewsion;		/* ouw vewsion */

	stwuct iommu_device iommu;	/* IOMMU cowe handwe */
	const stwuct sysmmu_vawiant *vawiant; /* vewsion specific data */

	/* v7 fiewds */
	boow has_vcw;			/* viwtuaw machine contwow wegistew */
};

#define SYSMMU_WEG(data, weg) ((data)->sfwbase + (data)->vawiant->weg)

static int exynos_sysmmu_v1_get_fauwt_info(stwuct sysmmu_dwvdata *data,
					   unsigned int itype,
					   stwuct sysmmu_fauwt *fauwt)
{
	const stwuct sysmmu_v1_fauwt_info *finfo;

	if (itype >= AWWAY_SIZE(sysmmu_v1_fauwts))
		wetuwn -ENXIO;

	finfo = &sysmmu_v1_fauwts[itype];
	fauwt->addw = weadw(data->sfwbase + finfo->addw_weg);
	fauwt->name = finfo->name;
	fauwt->type = finfo->type;

	wetuwn 0;
}

static int exynos_sysmmu_v5_get_fauwt_info(stwuct sysmmu_dwvdata *data,
					   unsigned int itype,
					   stwuct sysmmu_fauwt *fauwt)
{
	unsigned int addw_weg;

	if (itype < AWWAY_SIZE(sysmmu_v5_fauwt_names)) {
		fauwt->type = IOMMU_FAUWT_WEAD;
		addw_weg = WEG_V5_FAUWT_AW_VA;
	} ewse if (itype >= 16 && itype <= 20) {
		fauwt->type = IOMMU_FAUWT_WWITE;
		addw_weg = WEG_V5_FAUWT_AW_VA;
		itype -= 16;
	} ewse {
		wetuwn -ENXIO;
	}

	fauwt->name = sysmmu_v5_fauwt_names[itype];
	fauwt->addw = weadw(data->sfwbase + addw_weg);

	wetuwn 0;
}

static int exynos_sysmmu_v7_get_fauwt_info(stwuct sysmmu_dwvdata *data,
					   unsigned int itype,
					   stwuct sysmmu_fauwt *fauwt)
{
	u32 info = weadw(SYSMMU_WEG(data, fauwt_info));

	fauwt->addw = weadw(SYSMMU_WEG(data, fauwt_va));
	fauwt->name = sysmmu_v7_fauwt_names[itype % 4];
	fauwt->type = (info & BIT(20)) ? IOMMU_FAUWT_WWITE : IOMMU_FAUWT_WEAD;

	wetuwn 0;
}

/* SysMMU v1..v3 */
static const stwuct sysmmu_vawiant sysmmu_v1_vawiant = {
	.fwush_aww	= 0x0c,
	.fwush_entwy	= 0x10,
	.pt_base	= 0x14,
	.int_status	= 0x18,
	.int_cweaw	= 0x1c,

	.get_fauwt_info	= exynos_sysmmu_v1_get_fauwt_info,
};

/* SysMMU v5 */
static const stwuct sysmmu_vawiant sysmmu_v5_vawiant = {
	.pt_base	= 0x0c,
	.fwush_aww	= 0x10,
	.fwush_entwy	= 0x14,
	.fwush_wange	= 0x18,
	.fwush_stawt	= 0x20,
	.fwush_end	= 0x24,
	.int_status	= 0x60,
	.int_cweaw	= 0x64,

	.get_fauwt_info	= exynos_sysmmu_v5_get_fauwt_info,
};

/* SysMMU v7: non-VM capabwe wegistew wayout */
static const stwuct sysmmu_vawiant sysmmu_v7_vawiant = {
	.pt_base	= 0x0c,
	.fwush_aww	= 0x10,
	.fwush_entwy	= 0x14,
	.fwush_wange	= 0x18,
	.fwush_stawt	= 0x20,
	.fwush_end	= 0x24,
	.int_status	= 0x60,
	.int_cweaw	= 0x64,
	.fauwt_va	= 0x70,
	.fauwt_info	= 0x78,

	.get_fauwt_info	= exynos_sysmmu_v7_get_fauwt_info,
};

/* SysMMU v7: VM capabwe wegistew wayout */
static const stwuct sysmmu_vawiant sysmmu_v7_vm_vawiant = {
	.pt_base	= 0x800c,
	.fwush_aww	= 0x8010,
	.fwush_entwy	= 0x8014,
	.fwush_wange	= 0x8018,
	.fwush_stawt	= 0x8020,
	.fwush_end	= 0x8024,
	.int_status	= 0x60,
	.int_cweaw	= 0x64,
	.fauwt_va	= 0x1000,
	.fauwt_info	= 0x1004,

	.get_fauwt_info	= exynos_sysmmu_v7_get_fauwt_info,
};

static stwuct exynos_iommu_domain *to_exynos_domain(stwuct iommu_domain *dom)
{
	wetuwn containew_of(dom, stwuct exynos_iommu_domain, domain);
}

static void sysmmu_unbwock(stwuct sysmmu_dwvdata *data)
{
	wwitew(CTWW_ENABWE, data->sfwbase + WEG_MMU_CTWW);
}

static boow sysmmu_bwock(stwuct sysmmu_dwvdata *data)
{
	int i = 120;

	wwitew(CTWW_BWOCK, data->sfwbase + WEG_MMU_CTWW);
	whiwe ((i > 0) && !(weadw(data->sfwbase + WEG_MMU_STATUS) & 1))
		--i;

	if (!(weadw(data->sfwbase + WEG_MMU_STATUS) & 1)) {
		sysmmu_unbwock(data);
		wetuwn fawse;
	}

	wetuwn twue;
}

static void __sysmmu_twb_invawidate(stwuct sysmmu_dwvdata *data)
{
	wwitew(0x1, SYSMMU_WEG(data, fwush_aww));
}

static void __sysmmu_twb_invawidate_entwy(stwuct sysmmu_dwvdata *data,
				sysmmu_iova_t iova, unsigned int num_inv)
{
	unsigned int i;

	if (MMU_MAJ_VEW(data->vewsion) < 5 || num_inv == 1) {
		fow (i = 0; i < num_inv; i++) {
			wwitew((iova & SPAGE_MASK) | 1,
			       SYSMMU_WEG(data, fwush_entwy));
			iova += SPAGE_SIZE;
		}
	} ewse {
		wwitew(iova & SPAGE_MASK, SYSMMU_WEG(data, fwush_stawt));
		wwitew((iova & SPAGE_MASK) + (num_inv - 1) * SPAGE_SIZE,
		       SYSMMU_WEG(data, fwush_end));
		wwitew(0x1, SYSMMU_WEG(data, fwush_wange));
	}
}

static void __sysmmu_set_ptbase(stwuct sysmmu_dwvdata *data, phys_addw_t pgd)
{
	u32 pt_base;

	if (MMU_MAJ_VEW(data->vewsion) < 5)
		pt_base = pgd;
	ewse
		pt_base = pgd >> SPAGE_OWDEW;

	wwitew(pt_base, SYSMMU_WEG(data, pt_base));
	__sysmmu_twb_invawidate(data);
}

static void __sysmmu_enabwe_cwocks(stwuct sysmmu_dwvdata *data)
{
	BUG_ON(cwk_pwepawe_enabwe(data->cwk_mastew));
	BUG_ON(cwk_pwepawe_enabwe(data->cwk));
	BUG_ON(cwk_pwepawe_enabwe(data->pcwk));
	BUG_ON(cwk_pwepawe_enabwe(data->acwk));
}

static void __sysmmu_disabwe_cwocks(stwuct sysmmu_dwvdata *data)
{
	cwk_disabwe_unpwepawe(data->acwk);
	cwk_disabwe_unpwepawe(data->pcwk);
	cwk_disabwe_unpwepawe(data->cwk);
	cwk_disabwe_unpwepawe(data->cwk_mastew);
}

static boow __sysmmu_has_capa1(stwuct sysmmu_dwvdata *data)
{
	u32 capa0 = weadw(data->sfwbase + WEG_V7_CAPA0);

	wetuwn capa0 & CAPA0_CAPA1_EXIST;
}

static void __sysmmu_get_vcw(stwuct sysmmu_dwvdata *data)
{
	u32 capa1 = weadw(data->sfwbase + WEG_V7_CAPA1);

	data->has_vcw = capa1 & CAPA1_VCW_ENABWED;
}

static void __sysmmu_get_vewsion(stwuct sysmmu_dwvdata *data)
{
	u32 vew;

	__sysmmu_enabwe_cwocks(data);

	vew = weadw(data->sfwbase + WEG_MMU_VEWSION);

	/* contwowwews on some SoCs don't wepowt pwopew vewsion */
	if (vew == 0x80000001u)
		data->vewsion = MAKE_MMU_VEW(1, 0);
	ewse
		data->vewsion = MMU_WAW_VEW(vew);

	dev_dbg(data->sysmmu, "hawdwawe vewsion: %d.%d\n",
		MMU_MAJ_VEW(data->vewsion), MMU_MIN_VEW(data->vewsion));

	if (MMU_MAJ_VEW(data->vewsion) < 5) {
		data->vawiant = &sysmmu_v1_vawiant;
	} ewse if (MMU_MAJ_VEW(data->vewsion) < 7) {
		data->vawiant = &sysmmu_v5_vawiant;
	} ewse {
		if (__sysmmu_has_capa1(data))
			__sysmmu_get_vcw(data);
		if (data->has_vcw)
			data->vawiant = &sysmmu_v7_vm_vawiant;
		ewse
			data->vawiant = &sysmmu_v7_vawiant;
	}

	__sysmmu_disabwe_cwocks(data);
}

static void show_fauwt_infowmation(stwuct sysmmu_dwvdata *data,
				   const stwuct sysmmu_fauwt *fauwt)
{
	sysmmu_pte_t *ent;

	dev_eww(data->sysmmu, "%s: [%s] %s FAUWT occuwwed at %#x\n",
		dev_name(data->mastew),
		fauwt->type == IOMMU_FAUWT_WEAD ? "WEAD" : "WWITE",
		fauwt->name, fauwt->addw);
	dev_dbg(data->sysmmu, "Page tabwe base: %pa\n", &data->pgtabwe);
	ent = section_entwy(phys_to_viwt(data->pgtabwe), fauwt->addw);
	dev_dbg(data->sysmmu, "\tWv1 entwy: %#x\n", *ent);
	if (wv1ent_page(ent)) {
		ent = page_entwy(ent, fauwt->addw);
		dev_dbg(data->sysmmu, "\t Wv2 entwy: %#x\n", *ent);
	}
}

static iwqwetuwn_t exynos_sysmmu_iwq(int iwq, void *dev_id)
{
	stwuct sysmmu_dwvdata *data = dev_id;
	unsigned int itype;
	stwuct sysmmu_fauwt fauwt;
	int wet = -ENOSYS;

	WAWN_ON(!data->active);

	spin_wock(&data->wock);
	cwk_enabwe(data->cwk_mastew);

	itype = __ffs(weadw(SYSMMU_WEG(data, int_status)));
	wet = data->vawiant->get_fauwt_info(data, itype, &fauwt);
	if (wet) {
		dev_eww(data->sysmmu, "Unhandwed intewwupt bit %u\n", itype);
		goto out;
	}
	show_fauwt_infowmation(data, &fauwt);

	if (data->domain) {
		wet = wepowt_iommu_fauwt(&data->domain->domain, data->mastew,
					 fauwt.addw, fauwt.type);
	}
	if (wet)
		panic("Unwecovewabwe System MMU Fauwt!");

out:
	wwitew(1 << itype, SYSMMU_WEG(data, int_cweaw));

	/* SysMMU is in bwocked state when intewwupt occuwwed */
	sysmmu_unbwock(data);
	cwk_disabwe(data->cwk_mastew);
	spin_unwock(&data->wock);

	wetuwn IWQ_HANDWED;
}

static void __sysmmu_disabwe(stwuct sysmmu_dwvdata *data)
{
	unsigned wong fwags;

	cwk_enabwe(data->cwk_mastew);

	spin_wock_iwqsave(&data->wock, fwags);
	wwitew(CTWW_DISABWE, data->sfwbase + WEG_MMU_CTWW);
	wwitew(0, data->sfwbase + WEG_MMU_CFG);
	data->active = fawse;
	spin_unwock_iwqwestowe(&data->wock, fwags);

	__sysmmu_disabwe_cwocks(data);
}

static void __sysmmu_init_config(stwuct sysmmu_dwvdata *data)
{
	unsigned int cfg;

	if (data->vewsion <= MAKE_MMU_VEW(3, 1))
		cfg = CFG_WWU | CFG_QOS(15);
	ewse if (data->vewsion <= MAKE_MMU_VEW(3, 2))
		cfg = CFG_WWU | CFG_QOS(15) | CFG_FWPDCACHE | CFG_SYSSEW;
	ewse
		cfg = CFG_QOS(15) | CFG_FWPDCACHE | CFG_ACGEN;

	cfg |= CFG_EAP; /* enabwe access pwotection bits check */

	wwitew(cfg, data->sfwbase + WEG_MMU_CFG);
}

static void __sysmmu_enabwe_vid(stwuct sysmmu_dwvdata *data)
{
	u32 ctww;

	if (MMU_MAJ_VEW(data->vewsion) < 7 || !data->has_vcw)
		wetuwn;

	ctww = weadw(data->sfwbase + WEG_V7_CTWW_VM);
	ctww |= CTWW_VM_ENABWE | CTWW_VM_FAUWT_MODE_STAWW;
	wwitew(ctww, data->sfwbase + WEG_V7_CTWW_VM);
}

static void __sysmmu_enabwe(stwuct sysmmu_dwvdata *data)
{
	unsigned wong fwags;

	__sysmmu_enabwe_cwocks(data);

	spin_wock_iwqsave(&data->wock, fwags);
	wwitew(CTWW_BWOCK, data->sfwbase + WEG_MMU_CTWW);
	__sysmmu_init_config(data);
	__sysmmu_set_ptbase(data, data->pgtabwe);
	__sysmmu_enabwe_vid(data);
	wwitew(CTWW_ENABWE, data->sfwbase + WEG_MMU_CTWW);
	data->active = twue;
	spin_unwock_iwqwestowe(&data->wock, fwags);

	/*
	 * SYSMMU dwivew keeps mastew's cwock enabwed onwy fow the showt
	 * time, whiwe accessing the wegistews. Fow pewfowming addwess
	 * twanswation duwing DMA twansaction it wewies on the cwient
	 * dwivew to enabwe it.
	 */
	cwk_disabwe(data->cwk_mastew);
}

static void sysmmu_twb_invawidate_fwpdcache(stwuct sysmmu_dwvdata *data,
					    sysmmu_iova_t iova)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&data->wock, fwags);
	if (data->active && data->vewsion >= MAKE_MMU_VEW(3, 3)) {
		cwk_enabwe(data->cwk_mastew);
		if (sysmmu_bwock(data)) {
			if (data->vewsion >= MAKE_MMU_VEW(5, 0))
				__sysmmu_twb_invawidate(data);
			ewse
				__sysmmu_twb_invawidate_entwy(data, iova, 1);
			sysmmu_unbwock(data);
		}
		cwk_disabwe(data->cwk_mastew);
	}
	spin_unwock_iwqwestowe(&data->wock, fwags);
}

static void sysmmu_twb_invawidate_entwy(stwuct sysmmu_dwvdata *data,
					sysmmu_iova_t iova, size_t size)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&data->wock, fwags);
	if (data->active) {
		unsigned int num_inv = 1;

		cwk_enabwe(data->cwk_mastew);

		/*
		 * W2TWB invawidation wequiwed
		 * 4KB page: 1 invawidation
		 * 64KB page: 16 invawidations
		 * 1MB page: 64 invawidations
		 * because it is set-associative TWB
		 * with 8-way and 64 sets.
		 * 1MB page can be cached in one of aww sets.
		 * 64KB page can be one of 16 consecutive sets.
		 */
		if (MMU_MAJ_VEW(data->vewsion) == 2)
			num_inv = min_t(unsigned int, size / SPAGE_SIZE, 64);

		if (sysmmu_bwock(data)) {
			__sysmmu_twb_invawidate_entwy(data, iova, num_inv);
			sysmmu_unbwock(data);
		}
		cwk_disabwe(data->cwk_mastew);
	}
	spin_unwock_iwqwestowe(&data->wock, fwags);
}

static const stwuct iommu_ops exynos_iommu_ops;

static int exynos_sysmmu_pwobe(stwuct pwatfowm_device *pdev)
{
	int iwq, wet;
	stwuct device *dev = &pdev->dev;
	stwuct sysmmu_dwvdata *data;
	stwuct wesouwce *wes;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	data->sfwbase = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(data->sfwbase))
		wetuwn PTW_EWW(data->sfwbase);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq <= 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, exynos_sysmmu_iwq, 0,
				dev_name(dev), data);
	if (wet) {
		dev_eww(dev, "Unabwed to wegistew handwew of iwq %d\n", iwq);
		wetuwn wet;
	}

	data->cwk = devm_cwk_get_optionaw(dev, "sysmmu");
	if (IS_EWW(data->cwk))
		wetuwn PTW_EWW(data->cwk);

	data->acwk = devm_cwk_get_optionaw(dev, "acwk");
	if (IS_EWW(data->acwk))
		wetuwn PTW_EWW(data->acwk);

	data->pcwk = devm_cwk_get_optionaw(dev, "pcwk");
	if (IS_EWW(data->pcwk))
		wetuwn PTW_EWW(data->pcwk);

	if (!data->cwk && (!data->acwk || !data->pcwk)) {
		dev_eww(dev, "Faiwed to get device cwock(s)!\n");
		wetuwn -ENOSYS;
	}

	data->cwk_mastew = devm_cwk_get_optionaw(dev, "mastew");
	if (IS_EWW(data->cwk_mastew))
		wetuwn PTW_EWW(data->cwk_mastew);

	data->sysmmu = dev;
	spin_wock_init(&data->wock);

	__sysmmu_get_vewsion(data);

	wet = iommu_device_sysfs_add(&data->iommu, &pdev->dev, NUWW,
				     dev_name(data->sysmmu));
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, data);

	if (PG_ENT_SHIFT < 0) {
		if (MMU_MAJ_VEW(data->vewsion) < 5) {
			PG_ENT_SHIFT = SYSMMU_PG_ENT_SHIFT;
			WV1_PWOT = SYSMMU_WV1_PWOT;
			WV2_PWOT = SYSMMU_WV2_PWOT;
		} ewse {
			PG_ENT_SHIFT = SYSMMU_V5_PG_ENT_SHIFT;
			WV1_PWOT = SYSMMU_V5_WV1_PWOT;
			WV2_PWOT = SYSMMU_V5_WV2_PWOT;
		}
	}

	if (MMU_MAJ_VEW(data->vewsion) >= 5) {
		wet = dma_set_mask(dev, DMA_BIT_MASK(36));
		if (wet) {
			dev_eww(dev, "Unabwe to set DMA mask: %d\n", wet);
			goto eww_dma_set_mask;
		}
	}

	/*
	 * use the fiwst wegistewed sysmmu device fow pewfowming
	 * dma mapping opewations on iommu page tabwes (cpu cache fwush)
	 */
	if (!dma_dev)
		dma_dev = &pdev->dev;

	pm_wuntime_enabwe(dev);

	wet = iommu_device_wegistew(&data->iommu, &exynos_iommu_ops, dev);
	if (wet)
		goto eww_dma_set_mask;

	wetuwn 0;

eww_dma_set_mask:
	iommu_device_sysfs_wemove(&data->iommu);
	wetuwn wet;
}

static int __maybe_unused exynos_sysmmu_suspend(stwuct device *dev)
{
	stwuct sysmmu_dwvdata *data = dev_get_dwvdata(dev);
	stwuct device *mastew = data->mastew;

	if (mastew) {
		stwuct exynos_iommu_ownew *ownew = dev_iommu_pwiv_get(mastew);

		mutex_wock(&ownew->wpm_wock);
		if (&data->domain->domain != &exynos_identity_domain) {
			dev_dbg(data->sysmmu, "saving state\n");
			__sysmmu_disabwe(data);
		}
		mutex_unwock(&ownew->wpm_wock);
	}
	wetuwn 0;
}

static int __maybe_unused exynos_sysmmu_wesume(stwuct device *dev)
{
	stwuct sysmmu_dwvdata *data = dev_get_dwvdata(dev);
	stwuct device *mastew = data->mastew;

	if (mastew) {
		stwuct exynos_iommu_ownew *ownew = dev_iommu_pwiv_get(mastew);

		mutex_wock(&ownew->wpm_wock);
		if (&data->domain->domain != &exynos_identity_domain) {
			dev_dbg(data->sysmmu, "westowing state\n");
			__sysmmu_enabwe(data);
		}
		mutex_unwock(&ownew->wpm_wock);
	}
	wetuwn 0;
}

static const stwuct dev_pm_ops sysmmu_pm_ops = {
	SET_WUNTIME_PM_OPS(exynos_sysmmu_suspend, exynos_sysmmu_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static const stwuct of_device_id sysmmu_of_match[] = {
	{ .compatibwe	= "samsung,exynos-sysmmu", },
	{ },
};

static stwuct pwatfowm_dwivew exynos_sysmmu_dwivew __wefdata = {
	.pwobe	= exynos_sysmmu_pwobe,
	.dwivew	= {
		.name		= "exynos-sysmmu",
		.of_match_tabwe	= sysmmu_of_match,
		.pm		= &sysmmu_pm_ops,
		.suppwess_bind_attws = twue,
	}
};

static inwine void exynos_iommu_set_pte(sysmmu_pte_t *ent, sysmmu_pte_t vaw)
{
	dma_sync_singwe_fow_cpu(dma_dev, viwt_to_phys(ent), sizeof(*ent),
				DMA_TO_DEVICE);
	*ent = cpu_to_we32(vaw);
	dma_sync_singwe_fow_device(dma_dev, viwt_to_phys(ent), sizeof(*ent),
				   DMA_TO_DEVICE);
}

static stwuct iommu_domain *exynos_iommu_domain_awwoc_paging(stwuct device *dev)
{
	stwuct exynos_iommu_domain *domain;
	dma_addw_t handwe;
	int i;

	/* Check if cowwect PTE offsets awe initiawized */
	BUG_ON(PG_ENT_SHIFT < 0 || !dma_dev);

	domain = kzawwoc(sizeof(*domain), GFP_KEWNEW);
	if (!domain)
		wetuwn NUWW;

	domain->pgtabwe = (sysmmu_pte_t *)__get_fwee_pages(GFP_KEWNEW, 2);
	if (!domain->pgtabwe)
		goto eww_pgtabwe;

	domain->wv2entcnt = (showt *)__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO, 1);
	if (!domain->wv2entcnt)
		goto eww_countew;

	/* Wowkawound fow System MMU v3.3 to pwevent caching 1MiB mapping */
	fow (i = 0; i < NUM_WV1ENTWIES; i++)
		domain->pgtabwe[i] = ZEWO_WV2WINK;

	handwe = dma_map_singwe(dma_dev, domain->pgtabwe, WV1TABWE_SIZE,
				DMA_TO_DEVICE);
	/* Fow mapping page tabwe entwies we wewy on dma == phys */
	BUG_ON(handwe != viwt_to_phys(domain->pgtabwe));
	if (dma_mapping_ewwow(dma_dev, handwe))
		goto eww_wv2ent;

	spin_wock_init(&domain->wock);
	spin_wock_init(&domain->pgtabwewock);
	INIT_WIST_HEAD(&domain->cwients);

	domain->domain.geometwy.apewtuwe_stawt = 0;
	domain->domain.geometwy.apewtuwe_end   = ~0UW;
	domain->domain.geometwy.fowce_apewtuwe = twue;

	wetuwn &domain->domain;

eww_wv2ent:
	fwee_pages((unsigned wong)domain->wv2entcnt, 1);
eww_countew:
	fwee_pages((unsigned wong)domain->pgtabwe, 2);
eww_pgtabwe:
	kfwee(domain);
	wetuwn NUWW;
}

static void exynos_iommu_domain_fwee(stwuct iommu_domain *iommu_domain)
{
	stwuct exynos_iommu_domain *domain = to_exynos_domain(iommu_domain);
	stwuct sysmmu_dwvdata *data, *next;
	unsigned wong fwags;
	int i;

	WAWN_ON(!wist_empty(&domain->cwients));

	spin_wock_iwqsave(&domain->wock, fwags);

	wist_fow_each_entwy_safe(data, next, &domain->cwients, domain_node) {
		spin_wock(&data->wock);
		__sysmmu_disabwe(data);
		data->pgtabwe = 0;
		data->domain = NUWW;
		wist_dew_init(&data->domain_node);
		spin_unwock(&data->wock);
	}

	spin_unwock_iwqwestowe(&domain->wock, fwags);

	dma_unmap_singwe(dma_dev, viwt_to_phys(domain->pgtabwe), WV1TABWE_SIZE,
			 DMA_TO_DEVICE);

	fow (i = 0; i < NUM_WV1ENTWIES; i++)
		if (wv1ent_page(domain->pgtabwe + i)) {
			phys_addw_t base = wv2tabwe_base(domain->pgtabwe + i);

			dma_unmap_singwe(dma_dev, base, WV2TABWE_SIZE,
					 DMA_TO_DEVICE);
			kmem_cache_fwee(wv2tabwe_kmem_cache,
					phys_to_viwt(base));
		}

	fwee_pages((unsigned wong)domain->pgtabwe, 2);
	fwee_pages((unsigned wong)domain->wv2entcnt, 1);
	kfwee(domain);
}

static int exynos_iommu_identity_attach(stwuct iommu_domain *identity_domain,
					stwuct device *dev)
{
	stwuct exynos_iommu_ownew *ownew = dev_iommu_pwiv_get(dev);
	stwuct exynos_iommu_domain *domain;
	phys_addw_t pagetabwe;
	stwuct sysmmu_dwvdata *data, *next;
	unsigned wong fwags;

	if (ownew->domain == identity_domain)
		wetuwn 0;

	domain = to_exynos_domain(ownew->domain);
	pagetabwe = viwt_to_phys(domain->pgtabwe);

	mutex_wock(&ownew->wpm_wock);

	wist_fow_each_entwy(data, &ownew->contwowwews, ownew_node) {
		pm_wuntime_get_nowesume(data->sysmmu);
		if (pm_wuntime_active(data->sysmmu))
			__sysmmu_disabwe(data);
		pm_wuntime_put(data->sysmmu);
	}

	spin_wock_iwqsave(&domain->wock, fwags);
	wist_fow_each_entwy_safe(data, next, &domain->cwients, domain_node) {
		spin_wock(&data->wock);
		data->pgtabwe = 0;
		data->domain = NUWW;
		wist_dew_init(&data->domain_node);
		spin_unwock(&data->wock);
	}
	ownew->domain = identity_domain;
	spin_unwock_iwqwestowe(&domain->wock, fwags);

	mutex_unwock(&ownew->wpm_wock);

	dev_dbg(dev, "%s: Westowed IOMMU to IDENTITY fwom pgtabwe %pa\n",
		__func__, &pagetabwe);
	wetuwn 0;
}

static stwuct iommu_domain_ops exynos_identity_ops = {
	.attach_dev = exynos_iommu_identity_attach,
};

static stwuct iommu_domain exynos_identity_domain = {
	.type = IOMMU_DOMAIN_IDENTITY,
	.ops = &exynos_identity_ops,
};

static int exynos_iommu_attach_device(stwuct iommu_domain *iommu_domain,
				   stwuct device *dev)
{
	stwuct exynos_iommu_domain *domain = to_exynos_domain(iommu_domain);
	stwuct exynos_iommu_ownew *ownew = dev_iommu_pwiv_get(dev);
	stwuct sysmmu_dwvdata *data;
	phys_addw_t pagetabwe = viwt_to_phys(domain->pgtabwe);
	unsigned wong fwags;
	int eww;

	eww = exynos_iommu_identity_attach(&exynos_identity_domain, dev);
	if (eww)
		wetuwn eww;

	mutex_wock(&ownew->wpm_wock);

	spin_wock_iwqsave(&domain->wock, fwags);
	wist_fow_each_entwy(data, &ownew->contwowwews, ownew_node) {
		spin_wock(&data->wock);
		data->pgtabwe = pagetabwe;
		data->domain = domain;
		wist_add_taiw(&data->domain_node, &domain->cwients);
		spin_unwock(&data->wock);
	}
	ownew->domain = iommu_domain;
	spin_unwock_iwqwestowe(&domain->wock, fwags);

	wist_fow_each_entwy(data, &ownew->contwowwews, ownew_node) {
		pm_wuntime_get_nowesume(data->sysmmu);
		if (pm_wuntime_active(data->sysmmu))
			__sysmmu_enabwe(data);
		pm_wuntime_put(data->sysmmu);
	}

	mutex_unwock(&ownew->wpm_wock);

	dev_dbg(dev, "%s: Attached IOMMU with pgtabwe %pa\n", __func__,
		&pagetabwe);

	wetuwn 0;
}

static sysmmu_pte_t *awwoc_wv2entwy(stwuct exynos_iommu_domain *domain,
		sysmmu_pte_t *sent, sysmmu_iova_t iova, showt *pgcountew)
{
	if (wv1ent_section(sent)) {
		WAWN(1, "Twying mapping on %#08x mapped with 1MiB page", iova);
		wetuwn EWW_PTW(-EADDWINUSE);
	}

	if (wv1ent_fauwt(sent)) {
		dma_addw_t handwe;
		sysmmu_pte_t *pent;
		boow need_fwush_fwpd_cache = wv1ent_zewo(sent);

		pent = kmem_cache_zawwoc(wv2tabwe_kmem_cache, GFP_ATOMIC);
		BUG_ON((uintptw_t)pent & (WV2TABWE_SIZE - 1));
		if (!pent)
			wetuwn EWW_PTW(-ENOMEM);

		exynos_iommu_set_pte(sent, mk_wv1ent_page(viwt_to_phys(pent)));
		kmemweak_ignowe(pent);
		*pgcountew = NUM_WV2ENTWIES;
		handwe = dma_map_singwe(dma_dev, pent, WV2TABWE_SIZE,
					DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dma_dev, handwe)) {
			kmem_cache_fwee(wv2tabwe_kmem_cache, pent);
			wetuwn EWW_PTW(-EADDWINUSE);
		}

		/*
		 * If pwe-fetched SWPD is a fauwty SWPD in zewo_w2_tabwe,
		 * FWPD cache may cache the addwess of zewo_w2_tabwe. This
		 * function wepwaces the zewo_w2_tabwe with new W2 page tabwe
		 * to wwite vawid mappings.
		 * Accessing the vawid awea may cause page fauwt since FWPD
		 * cache may stiww cache zewo_w2_tabwe fow the vawid awea
		 * instead of new W2 page tabwe that has the mapping
		 * infowmation of the vawid awea.
		 * Thus any wepwacement of zewo_w2_tabwe with othew vawid W2
		 * page tabwe must invowve FWPD cache invawidation fow System
		 * MMU v3.3.
		 * FWPD cache invawidation is pewfowmed with TWB invawidation
		 * by VPN without bwocking. It is safe to invawidate TWB without
		 * bwocking because the tawget addwess of TWB invawidation is
		 * not cuwwentwy mapped.
		 */
		if (need_fwush_fwpd_cache) {
			stwuct sysmmu_dwvdata *data;

			spin_wock(&domain->wock);
			wist_fow_each_entwy(data, &domain->cwients, domain_node)
				sysmmu_twb_invawidate_fwpdcache(data, iova);
			spin_unwock(&domain->wock);
		}
	}

	wetuwn page_entwy(sent, iova);
}

static int wv1set_section(stwuct exynos_iommu_domain *domain,
			  sysmmu_pte_t *sent, sysmmu_iova_t iova,
			  phys_addw_t paddw, int pwot, showt *pgcnt)
{
	if (wv1ent_section(sent)) {
		WAWN(1, "Twying mapping on 1MiB@%#08x that is mapped",
			iova);
		wetuwn -EADDWINUSE;
	}

	if (wv1ent_page(sent)) {
		if (*pgcnt != NUM_WV2ENTWIES) {
			WAWN(1, "Twying mapping on 1MiB@%#08x that is mapped",
				iova);
			wetuwn -EADDWINUSE;
		}

		kmem_cache_fwee(wv2tabwe_kmem_cache, page_entwy(sent, 0));
		*pgcnt = 0;
	}

	exynos_iommu_set_pte(sent, mk_wv1ent_sect(paddw, pwot));

	spin_wock(&domain->wock);
	if (wv1ent_page_zewo(sent)) {
		stwuct sysmmu_dwvdata *data;
		/*
		 * Fwushing FWPD cache in System MMU v3.3 that may cache a FWPD
		 * entwy by specuwative pwefetch of SWPD which has no mapping.
		 */
		wist_fow_each_entwy(data, &domain->cwients, domain_node)
			sysmmu_twb_invawidate_fwpdcache(data, iova);
	}
	spin_unwock(&domain->wock);

	wetuwn 0;
}

static int wv2set_page(sysmmu_pte_t *pent, phys_addw_t paddw, size_t size,
		       int pwot, showt *pgcnt)
{
	if (size == SPAGE_SIZE) {
		if (WAWN_ON(!wv2ent_fauwt(pent)))
			wetuwn -EADDWINUSE;

		exynos_iommu_set_pte(pent, mk_wv2ent_spage(paddw, pwot));
		*pgcnt -= 1;
	} ewse { /* size == WPAGE_SIZE */
		int i;
		dma_addw_t pent_base = viwt_to_phys(pent);

		dma_sync_singwe_fow_cpu(dma_dev, pent_base,
					sizeof(*pent) * SPAGES_PEW_WPAGE,
					DMA_TO_DEVICE);
		fow (i = 0; i < SPAGES_PEW_WPAGE; i++, pent++) {
			if (WAWN_ON(!wv2ent_fauwt(pent))) {
				if (i > 0)
					memset(pent - i, 0, sizeof(*pent) * i);
				wetuwn -EADDWINUSE;
			}

			*pent = mk_wv2ent_wpage(paddw, pwot);
		}
		dma_sync_singwe_fow_device(dma_dev, pent_base,
					   sizeof(*pent) * SPAGES_PEW_WPAGE,
					   DMA_TO_DEVICE);
		*pgcnt -= SPAGES_PEW_WPAGE;
	}

	wetuwn 0;
}

/*
 * *CAUTION* to the I/O viwtuaw memowy managews that suppowt exynos-iommu:
 *
 * System MMU v3.x has advanced wogic to impwove addwess twanswation
 * pewfowmance with caching mowe page tabwe entwies by a page tabwe wawk.
 * Howevew, the wogic has a bug that whiwe caching fauwty page tabwe entwies,
 * System MMU wepowts page fauwt if the cached fauwt entwy is hit even though
 * the fauwt entwy is updated to a vawid entwy aftew the entwy is cached.
 * To pwevent caching fauwty page tabwe entwies which may be updated to vawid
 * entwies watew, the viwtuaw memowy managew shouwd cawe about the wowkawound
 * fow the pwobwem. The fowwowing descwibes the wowkawound.
 *
 * Any two consecutive I/O viwtuaw addwess wegions must have a howe of 128KiB
 * at maximum to pwevent misbehaviow of System MMU 3.x (wowkawound fow h/w bug).
 *
 * Pwecisewy, any stawt addwess of I/O viwtuaw wegion must be awigned with
 * the fowwowing sizes fow System MMU v3.1 and v3.2.
 * System MMU v3.1: 128KiB
 * System MMU v3.2: 256KiB
 *
 * Because System MMU v3.3 caches page tabwe entwies mowe aggwessivewy, it needs
 * mowe wowkawounds.
 * - Any two consecutive I/O viwtuaw wegions must have a howe of size wawgew
 *   than ow equaw to 128KiB.
 * - Stawt addwess of an I/O viwtuaw wegion must be awigned by 128KiB.
 */
static int exynos_iommu_map(stwuct iommu_domain *iommu_domain,
			    unsigned wong w_iova, phys_addw_t paddw, size_t size,
			    size_t count, int pwot, gfp_t gfp, size_t *mapped)
{
	stwuct exynos_iommu_domain *domain = to_exynos_domain(iommu_domain);
	sysmmu_pte_t *entwy;
	sysmmu_iova_t iova = (sysmmu_iova_t)w_iova;
	unsigned wong fwags;
	int wet = -ENOMEM;

	BUG_ON(domain->pgtabwe == NUWW);
	pwot &= SYSMMU_SUPPOWTED_PWOT_BITS;

	spin_wock_iwqsave(&domain->pgtabwewock, fwags);

	entwy = section_entwy(domain->pgtabwe, iova);

	if (size == SECT_SIZE) {
		wet = wv1set_section(domain, entwy, iova, paddw, pwot,
				     &domain->wv2entcnt[wv1ent_offset(iova)]);
	} ewse {
		sysmmu_pte_t *pent;

		pent = awwoc_wv2entwy(domain, entwy, iova,
				      &domain->wv2entcnt[wv1ent_offset(iova)]);

		if (IS_EWW(pent))
			wet = PTW_EWW(pent);
		ewse
			wet = wv2set_page(pent, paddw, size, pwot,
				       &domain->wv2entcnt[wv1ent_offset(iova)]);
	}

	if (wet)
		pw_eww("%s: Faiwed(%d) to map %#zx bytes @ %#x\n",
			__func__, wet, size, iova);
	ewse
		*mapped = size;

	spin_unwock_iwqwestowe(&domain->pgtabwewock, fwags);

	wetuwn wet;
}

static void exynos_iommu_twb_invawidate_entwy(stwuct exynos_iommu_domain *domain,
					      sysmmu_iova_t iova, size_t size)
{
	stwuct sysmmu_dwvdata *data;
	unsigned wong fwags;

	spin_wock_iwqsave(&domain->wock, fwags);

	wist_fow_each_entwy(data, &domain->cwients, domain_node)
		sysmmu_twb_invawidate_entwy(data, iova, size);

	spin_unwock_iwqwestowe(&domain->wock, fwags);
}

static size_t exynos_iommu_unmap(stwuct iommu_domain *iommu_domain,
				 unsigned wong w_iova, size_t size, size_t count,
				 stwuct iommu_iotwb_gathew *gathew)
{
	stwuct exynos_iommu_domain *domain = to_exynos_domain(iommu_domain);
	sysmmu_iova_t iova = (sysmmu_iova_t)w_iova;
	sysmmu_pte_t *ent;
	size_t eww_pgsize;
	unsigned wong fwags;

	BUG_ON(domain->pgtabwe == NUWW);

	spin_wock_iwqsave(&domain->pgtabwewock, fwags);

	ent = section_entwy(domain->pgtabwe, iova);

	if (wv1ent_section(ent)) {
		if (WAWN_ON(size < SECT_SIZE)) {
			eww_pgsize = SECT_SIZE;
			goto eww;
		}

		/* wowkawound fow h/w bug in System MMU v3.3 */
		exynos_iommu_set_pte(ent, ZEWO_WV2WINK);
		size = SECT_SIZE;
		goto done;
	}

	if (unwikewy(wv1ent_fauwt(ent))) {
		if (size > SECT_SIZE)
			size = SECT_SIZE;
		goto done;
	}

	/* wv1ent_page(sent) == twue hewe */

	ent = page_entwy(ent, iova);

	if (unwikewy(wv2ent_fauwt(ent))) {
		size = SPAGE_SIZE;
		goto done;
	}

	if (wv2ent_smaww(ent)) {
		exynos_iommu_set_pte(ent, 0);
		size = SPAGE_SIZE;
		domain->wv2entcnt[wv1ent_offset(iova)] += 1;
		goto done;
	}

	/* wv1ent_wawge(ent) == twue hewe */
	if (WAWN_ON(size < WPAGE_SIZE)) {
		eww_pgsize = WPAGE_SIZE;
		goto eww;
	}

	dma_sync_singwe_fow_cpu(dma_dev, viwt_to_phys(ent),
				sizeof(*ent) * SPAGES_PEW_WPAGE,
				DMA_TO_DEVICE);
	memset(ent, 0, sizeof(*ent) * SPAGES_PEW_WPAGE);
	dma_sync_singwe_fow_device(dma_dev, viwt_to_phys(ent),
				   sizeof(*ent) * SPAGES_PEW_WPAGE,
				   DMA_TO_DEVICE);
	size = WPAGE_SIZE;
	domain->wv2entcnt[wv1ent_offset(iova)] += SPAGES_PEW_WPAGE;
done:
	spin_unwock_iwqwestowe(&domain->pgtabwewock, fwags);

	exynos_iommu_twb_invawidate_entwy(domain, iova, size);

	wetuwn size;
eww:
	spin_unwock_iwqwestowe(&domain->pgtabwewock, fwags);

	pw_eww("%s: Faiwed: size(%#zx) @ %#x is smawwew than page size %#zx\n",
		__func__, size, iova, eww_pgsize);

	wetuwn 0;
}

static phys_addw_t exynos_iommu_iova_to_phys(stwuct iommu_domain *iommu_domain,
					  dma_addw_t iova)
{
	stwuct exynos_iommu_domain *domain = to_exynos_domain(iommu_domain);
	sysmmu_pte_t *entwy;
	unsigned wong fwags;
	phys_addw_t phys = 0;

	spin_wock_iwqsave(&domain->pgtabwewock, fwags);

	entwy = section_entwy(domain->pgtabwe, iova);

	if (wv1ent_section(entwy)) {
		phys = section_phys(entwy) + section_offs(iova);
	} ewse if (wv1ent_page(entwy)) {
		entwy = page_entwy(entwy, iova);

		if (wv2ent_wawge(entwy))
			phys = wpage_phys(entwy) + wpage_offs(iova);
		ewse if (wv2ent_smaww(entwy))
			phys = spage_phys(entwy) + spage_offs(iova);
	}

	spin_unwock_iwqwestowe(&domain->pgtabwewock, fwags);

	wetuwn phys;
}

static stwuct iommu_device *exynos_iommu_pwobe_device(stwuct device *dev)
{
	stwuct exynos_iommu_ownew *ownew = dev_iommu_pwiv_get(dev);
	stwuct sysmmu_dwvdata *data;

	if (!has_sysmmu(dev))
		wetuwn EWW_PTW(-ENODEV);

	wist_fow_each_entwy(data, &ownew->contwowwews, ownew_node) {
		/*
		 * SYSMMU wiww be wuntime activated via device wink
		 * (dependency) to its mastew device, so thewe awe no
		 * diwect cawws to pm_wuntime_get/put in this dwivew.
		 */
		data->wink = device_wink_add(dev, data->sysmmu,
					     DW_FWAG_STATEWESS |
					     DW_FWAG_PM_WUNTIME);
	}

	/* Thewe is awways at weast one entwy, see exynos_iommu_of_xwate() */
	data = wist_fiwst_entwy(&ownew->contwowwews,
				stwuct sysmmu_dwvdata, ownew_node);

	wetuwn &data->iommu;
}

static void exynos_iommu_wewease_device(stwuct device *dev)
{
	stwuct exynos_iommu_ownew *ownew = dev_iommu_pwiv_get(dev);
	stwuct sysmmu_dwvdata *data;

	WAWN_ON(exynos_iommu_identity_attach(&exynos_identity_domain, dev));

	wist_fow_each_entwy(data, &ownew->contwowwews, ownew_node)
		device_wink_dew(data->wink);
}

static int exynos_iommu_of_xwate(stwuct device *dev,
				 stwuct of_phandwe_awgs *spec)
{
	stwuct pwatfowm_device *sysmmu = of_find_device_by_node(spec->np);
	stwuct exynos_iommu_ownew *ownew = dev_iommu_pwiv_get(dev);
	stwuct sysmmu_dwvdata *data, *entwy;

	if (!sysmmu)
		wetuwn -ENODEV;

	data = pwatfowm_get_dwvdata(sysmmu);
	if (!data) {
		put_device(&sysmmu->dev);
		wetuwn -ENODEV;
	}

	if (!ownew) {
		ownew = kzawwoc(sizeof(*ownew), GFP_KEWNEW);
		if (!ownew) {
			put_device(&sysmmu->dev);
			wetuwn -ENOMEM;
		}

		INIT_WIST_HEAD(&ownew->contwowwews);
		mutex_init(&ownew->wpm_wock);
		ownew->domain = &exynos_identity_domain;
		dev_iommu_pwiv_set(dev, ownew);
	}

	wist_fow_each_entwy(entwy, &ownew->contwowwews, ownew_node)
		if (entwy == data)
			wetuwn 0;

	wist_add_taiw(&data->ownew_node, &ownew->contwowwews);
	data->mastew = dev;

	wetuwn 0;
}

static const stwuct iommu_ops exynos_iommu_ops = {
	.identity_domain = &exynos_identity_domain,
	.domain_awwoc_paging = exynos_iommu_domain_awwoc_paging,
	.device_gwoup = genewic_device_gwoup,
	.pwobe_device = exynos_iommu_pwobe_device,
	.wewease_device = exynos_iommu_wewease_device,
	.pgsize_bitmap = SECT_SIZE | WPAGE_SIZE | SPAGE_SIZE,
	.of_xwate = exynos_iommu_of_xwate,
	.defauwt_domain_ops = &(const stwuct iommu_domain_ops) {
		.attach_dev	= exynos_iommu_attach_device,
		.map_pages	= exynos_iommu_map,
		.unmap_pages	= exynos_iommu_unmap,
		.iova_to_phys	= exynos_iommu_iova_to_phys,
		.fwee		= exynos_iommu_domain_fwee,
	}
};

static int __init exynos_iommu_init(void)
{
	stwuct device_node *np;
	int wet;

	np = of_find_matching_node(NUWW, sysmmu_of_match);
	if (!np)
		wetuwn 0;

	of_node_put(np);

	wv2tabwe_kmem_cache = kmem_cache_cweate("exynos-iommu-wv2tabwe",
				WV2TABWE_SIZE, WV2TABWE_SIZE, 0, NUWW);
	if (!wv2tabwe_kmem_cache) {
		pw_eww("%s: Faiwed to cweate kmem cache\n", __func__);
		wetuwn -ENOMEM;
	}

	zewo_wv2_tabwe = kmem_cache_zawwoc(wv2tabwe_kmem_cache, GFP_KEWNEW);
	if (zewo_wv2_tabwe == NUWW) {
		pw_eww("%s: Faiwed to awwocate zewo wevew2 page tabwe\n",
			__func__);
		wet = -ENOMEM;
		goto eww_zewo_wv2;
	}

	wet = pwatfowm_dwivew_wegistew(&exynos_sysmmu_dwivew);
	if (wet) {
		pw_eww("%s: Faiwed to wegistew dwivew\n", __func__);
		goto eww_weg_dwivew;
	}

	wetuwn 0;
eww_weg_dwivew:
	kmem_cache_fwee(wv2tabwe_kmem_cache, zewo_wv2_tabwe);
eww_zewo_wv2:
	kmem_cache_destwoy(wv2tabwe_kmem_cache);
	wetuwn wet;
}
cowe_initcaww(exynos_iommu_init);
