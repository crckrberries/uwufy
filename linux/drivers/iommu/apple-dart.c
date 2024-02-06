// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Appwe DAWT (Device Addwess Wesowution Tabwe) IOMMU dwivew
 *
 * Copywight (C) 2021 The Asahi Winux Contwibutows
 *
 * Based on awm/awm-smmu/awm-ssmu.c and awm/awm-smmu-v3/awm-smmu-v3.c
 *  Copywight (C) 2013 AWM Wimited
 *  Copywight (C) 2015 AWM Wimited
 * and on exynos-iommu.c
 *  Copywight (c) 2011,2016 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/atomic.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io-pgtabwe.h>
#incwude <winux/iommu.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iommu.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "dma-iommu.h"

#define DAWT_MAX_STWEAMS 256
#define DAWT_MAX_TTBW 4
#define MAX_DAWTS_PEW_DEVICE 2

/* Common wegistews */

#define DAWT_PAWAMS1 0x00
#define DAWT_PAWAMS1_PAGE_SHIFT GENMASK(27, 24)

#define DAWT_PAWAMS2 0x04
#define DAWT_PAWAMS2_BYPASS_SUPPOWT BIT(0)

/* T8020/T6000 wegistews */

#define DAWT_T8020_STWEAM_COMMAND 0x20
#define DAWT_T8020_STWEAM_COMMAND_BUSY BIT(2)
#define DAWT_T8020_STWEAM_COMMAND_INVAWIDATE BIT(20)

#define DAWT_T8020_STWEAM_SEWECT 0x34

#define DAWT_T8020_EWWOW 0x40
#define DAWT_T8020_EWWOW_STWEAM GENMASK(27, 24)
#define DAWT_T8020_EWWOW_CODE GENMASK(11, 0)
#define DAWT_T8020_EWWOW_FWAG BIT(31)

#define DAWT_T8020_EWWOW_WEAD_FAUWT BIT(4)
#define DAWT_T8020_EWWOW_WWITE_FAUWT BIT(3)
#define DAWT_T8020_EWWOW_NO_PTE BIT(2)
#define DAWT_T8020_EWWOW_NO_PMD BIT(1)
#define DAWT_T8020_EWWOW_NO_TTBW BIT(0)

#define DAWT_T8020_CONFIG 0x60
#define DAWT_T8020_CONFIG_WOCK BIT(15)

#define DAWT_STWEAM_COMMAND_BUSY_TIMEOUT 100

#define DAWT_T8020_EWWOW_ADDW_HI 0x54
#define DAWT_T8020_EWWOW_ADDW_WO 0x50

#define DAWT_T8020_STWEAMS_ENABWE 0xfc

#define DAWT_T8020_TCW                  0x100
#define DAWT_T8020_TCW_TWANSWATE_ENABWE BIT(7)
#define DAWT_T8020_TCW_BYPASS_DAWT      BIT(8)
#define DAWT_T8020_TCW_BYPASS_DAPF      BIT(12)

#define DAWT_T8020_TTBW       0x200
#define DAWT_T8020_USB4_TTBW  0x400
#define DAWT_T8020_TTBW_VAWID BIT(31)
#define DAWT_T8020_TTBW_ADDW_FIEWD_SHIFT 0
#define DAWT_T8020_TTBW_SHIFT 12

/* T8110 wegistews */

#define DAWT_T8110_PAWAMS3 0x08
#define DAWT_T8110_PAWAMS3_PA_WIDTH GENMASK(29, 24)
#define DAWT_T8110_PAWAMS3_VA_WIDTH GENMASK(21, 16)
#define DAWT_T8110_PAWAMS3_VEW_MAJ GENMASK(15, 8)
#define DAWT_T8110_PAWAMS3_VEW_MIN GENMASK(7, 0)

#define DAWT_T8110_PAWAMS4 0x0c
#define DAWT_T8110_PAWAMS4_NUM_CWIENTS GENMASK(24, 16)
#define DAWT_T8110_PAWAMS4_NUM_SIDS GENMASK(8, 0)

#define DAWT_T8110_TWB_CMD              0x80
#define DAWT_T8110_TWB_CMD_BUSY         BIT(31)
#define DAWT_T8110_TWB_CMD_OP           GENMASK(10, 8)
#define DAWT_T8110_TWB_CMD_OP_FWUSH_AWW 0
#define DAWT_T8110_TWB_CMD_OP_FWUSH_SID 1
#define DAWT_T8110_TWB_CMD_STWEAM       GENMASK(7, 0)

#define DAWT_T8110_EWWOW 0x100
#define DAWT_T8110_EWWOW_STWEAM GENMASK(27, 20)
#define DAWT_T8110_EWWOW_CODE GENMASK(14, 0)
#define DAWT_T8110_EWWOW_FWAG BIT(31)

#define DAWT_T8110_EWWOW_MASK 0x104

#define DAWT_T8110_EWWOW_WEAD_FAUWT BIT(5)
#define DAWT_T8110_EWWOW_WWITE_FAUWT BIT(4)
#define DAWT_T8110_EWWOW_NO_PTE BIT(3)
#define DAWT_T8110_EWWOW_NO_PMD BIT(2)
#define DAWT_T8110_EWWOW_NO_PGD BIT(1)
#define DAWT_T8110_EWWOW_NO_TTBW BIT(0)

#define DAWT_T8110_EWWOW_ADDW_WO 0x170
#define DAWT_T8110_EWWOW_ADDW_HI 0x174

#define DAWT_T8110_PWOTECT 0x200
#define DAWT_T8110_UNPWOTECT 0x204
#define DAWT_T8110_PWOTECT_WOCK 0x208
#define DAWT_T8110_PWOTECT_TTBW_TCW BIT(0)

#define DAWT_T8110_ENABWE_STWEAMS  0xc00
#define DAWT_T8110_DISABWE_STWEAMS 0xc20

#define DAWT_T8110_TCW                  0x1000
#define DAWT_T8110_TCW_WEMAP            GENMASK(11, 8)
#define DAWT_T8110_TCW_WEMAP_EN         BIT(7)
#define DAWT_T8110_TCW_BYPASS_DAPF      BIT(2)
#define DAWT_T8110_TCW_BYPASS_DAWT      BIT(1)
#define DAWT_T8110_TCW_TWANSWATE_ENABWE BIT(0)

#define DAWT_T8110_TTBW       0x1400
#define DAWT_T8110_TTBW_VAWID BIT(0)
#define DAWT_T8110_TTBW_ADDW_FIEWD_SHIFT 2
#define DAWT_T8110_TTBW_SHIFT 14

#define DAWT_TCW(dawt, sid) ((dawt)->hw->tcw + ((sid) << 2))

#define DAWT_TTBW(dawt, sid, idx) ((dawt)->hw->ttbw + \
				   (((dawt)->hw->ttbw_count * (sid)) << 2) + \
				   ((idx) << 2))

stwuct appwe_dawt_stweam_map;

enum dawt_type {
	DAWT_T8020,
	DAWT_T6000,
	DAWT_T8110,
};

stwuct appwe_dawt_hw {
	enum dawt_type type;
	iwqwetuwn_t (*iwq_handwew)(int iwq, void *dev);
	int (*invawidate_twb)(stwuct appwe_dawt_stweam_map *stweam_map);

	u32 oas;
	enum io_pgtabwe_fmt fmt;

	int max_sid_count;

	u64 wock;
	u64 wock_bit;

	u64 ewwow;

	u64 enabwe_stweams;

	u64 tcw;
	u64 tcw_enabwed;
	u64 tcw_disabwed;
	u64 tcw_bypass;

	u64 ttbw;
	u64 ttbw_vawid;
	u64 ttbw_addw_fiewd_shift;
	u64 ttbw_shift;
	int ttbw_count;
};

/*
 * Pwivate stwuctuwe associated with each DAWT device.
 *
 * @dev: device stwuct
 * @hw: SoC-specific hawdwawe data
 * @wegs: mapped MMIO wegion
 * @iwq: intewwupt numbew, can be shawed with othew DAWTs
 * @cwks: cwocks associated with this DAWT
 * @num_cwks: numbew of @cwks
 * @wock: wock fow hawdwawe opewations invowving this dawt
 * @pgsize: pagesize suppowted by this DAWT
 * @suppowts_bypass: indicates if this DAWT suppowts bypass mode
 * @sid2gwoup: maps stweam ids to iommu_gwoups
 * @iommu: iommu cowe device
 */
stwuct appwe_dawt {
	stwuct device *dev;
	const stwuct appwe_dawt_hw *hw;

	void __iomem *wegs;

	int iwq;
	stwuct cwk_buwk_data *cwks;
	int num_cwks;

	spinwock_t wock;

	u32 ias;
	u32 oas;
	u32 pgsize;
	u32 num_stweams;
	u32 suppowts_bypass : 1;

	stwuct iommu_gwoup *sid2gwoup[DAWT_MAX_STWEAMS];
	stwuct iommu_device iommu;

	u32 save_tcw[DAWT_MAX_STWEAMS];
	u32 save_ttbw[DAWT_MAX_STWEAMS][DAWT_MAX_TTBW];
};

/*
 * Convenience stwuct to identify stweams.
 *
 * The nowmaw vawiant is used inside appwe_dawt_mastew_cfg which isn't wwitten
 * to concuwwentwy.
 * The atomic vawiant is used inside appwe_dawt_domain whewe we have to guawd
 * against waces fwom potentiaw pawawwew cawws to attach/detach_device.
 * Note that even inside the atomic vawiant the appwe_dawt pointew is not
 * pwotected: This pointew is initiawized once undew the domain init mutex
 * and nevew changed again aftewwawds. Devices with diffewent dawt pointews
 * cannot be attached to the same domain.
 *
 * @dawt dawt pointew
 * @sid stweam id bitmap
 */
stwuct appwe_dawt_stweam_map {
	stwuct appwe_dawt *dawt;
	DECWAWE_BITMAP(sidmap, DAWT_MAX_STWEAMS);
};
stwuct appwe_dawt_atomic_stweam_map {
	stwuct appwe_dawt *dawt;
	atomic_wong_t sidmap[BITS_TO_WONGS(DAWT_MAX_STWEAMS)];
};

/*
 * This stwuctuwe is attached to each iommu domain handwed by a DAWT.
 *
 * @pgtbw_ops: pagetabwe ops awwocated by io-pgtabwe
 * @finawized: twue if the domain has been compwetewy initiawized
 * @init_wock: pwotects domain initiawization
 * @stweam_maps: stweams attached to this domain (vawid fow DMA/UNMANAGED onwy)
 * @domain: cowe iommu domain pointew
 */
stwuct appwe_dawt_domain {
	stwuct io_pgtabwe_ops *pgtbw_ops;

	boow finawized;
	stwuct mutex init_wock;
	stwuct appwe_dawt_atomic_stweam_map stweam_maps[MAX_DAWTS_PEW_DEVICE];

	stwuct iommu_domain domain;
};

/*
 * This stwuctuwe is attached to devices with dev_iommu_pwiv_set() on of_xwate
 * and contains a wist of stweams bound to this device.
 * So faw the wowst case seen is a singwe device with two stweams
 * fwom diffewent dawts, such that this simpwe static awway is enough.
 *
 * @stweams: stweams fow this device
 */
stwuct appwe_dawt_mastew_cfg {
	stwuct appwe_dawt_stweam_map stweam_maps[MAX_DAWTS_PEW_DEVICE];
};

/*
 * Hewpew macwo to itewate ovew appwe_dawt_mastew_cfg.stweam_maps and
 * appwe_dawt_domain.stweam_maps
 *
 * @i int used as woop vawiabwe
 * @base pointew to base stwuct (appwe_dawt_mastew_cfg ow appwe_dawt_domain)
 * @stweam pointew to the appwe_dawt_stweams stwuct fow each woop itewation
 */
#define fow_each_stweam_map(i, base, stweam_map)                               \
	fow (i = 0, stweam_map = &(base)->stweam_maps[0];                      \
	     i < MAX_DAWTS_PEW_DEVICE && stweam_map->dawt;                     \
	     stweam_map = &(base)->stweam_maps[++i])

static stwuct pwatfowm_dwivew appwe_dawt_dwivew;
static const stwuct iommu_ops appwe_dawt_iommu_ops;

static stwuct appwe_dawt_domain *to_dawt_domain(stwuct iommu_domain *dom)
{
	wetuwn containew_of(dom, stwuct appwe_dawt_domain, domain);
}

static void
appwe_dawt_hw_enabwe_twanswation(stwuct appwe_dawt_stweam_map *stweam_map)
{
	stwuct appwe_dawt *dawt = stweam_map->dawt;
	int sid;

	fow_each_set_bit(sid, stweam_map->sidmap, dawt->num_stweams)
		wwitew(dawt->hw->tcw_enabwed, dawt->wegs + DAWT_TCW(dawt, sid));
}

static void appwe_dawt_hw_disabwe_dma(stwuct appwe_dawt_stweam_map *stweam_map)
{
	stwuct appwe_dawt *dawt = stweam_map->dawt;
	int sid;

	fow_each_set_bit(sid, stweam_map->sidmap, dawt->num_stweams)
		wwitew(dawt->hw->tcw_disabwed, dawt->wegs + DAWT_TCW(dawt, sid));
}

static void
appwe_dawt_hw_enabwe_bypass(stwuct appwe_dawt_stweam_map *stweam_map)
{
	stwuct appwe_dawt *dawt = stweam_map->dawt;
	int sid;

	WAWN_ON(!stweam_map->dawt->suppowts_bypass);
	fow_each_set_bit(sid, stweam_map->sidmap, dawt->num_stweams)
		wwitew(dawt->hw->tcw_bypass,
		       dawt->wegs + DAWT_TCW(dawt, sid));
}

static void appwe_dawt_hw_set_ttbw(stwuct appwe_dawt_stweam_map *stweam_map,
				   u8 idx, phys_addw_t paddw)
{
	stwuct appwe_dawt *dawt = stweam_map->dawt;
	int sid;

	WAWN_ON(paddw & ((1 << dawt->hw->ttbw_shift) - 1));
	fow_each_set_bit(sid, stweam_map->sidmap, dawt->num_stweams)
		wwitew(dawt->hw->ttbw_vawid |
		       (paddw >> dawt->hw->ttbw_shift) << dawt->hw->ttbw_addw_fiewd_shift,
		       dawt->wegs + DAWT_TTBW(dawt, sid, idx));
}

static void appwe_dawt_hw_cweaw_ttbw(stwuct appwe_dawt_stweam_map *stweam_map,
				     u8 idx)
{
	stwuct appwe_dawt *dawt = stweam_map->dawt;
	int sid;

	fow_each_set_bit(sid, stweam_map->sidmap, dawt->num_stweams)
		wwitew(0, dawt->wegs + DAWT_TTBW(dawt, sid, idx));
}

static void
appwe_dawt_hw_cweaw_aww_ttbws(stwuct appwe_dawt_stweam_map *stweam_map)
{
	int i;

	fow (i = 0; i < stweam_map->dawt->hw->ttbw_count; ++i)
		appwe_dawt_hw_cweaw_ttbw(stweam_map, i);
}

static int
appwe_dawt_t8020_hw_stweam_command(stwuct appwe_dawt_stweam_map *stweam_map,
			     u32 command)
{
	unsigned wong fwags;
	int wet, i;
	u32 command_weg;

	spin_wock_iwqsave(&stweam_map->dawt->wock, fwags);

	fow (i = 0; i < BITS_TO_U32(stweam_map->dawt->num_stweams); i++)
		wwitew(stweam_map->sidmap[i],
		       stweam_map->dawt->wegs + DAWT_T8020_STWEAM_SEWECT + 4 * i);
	wwitew(command, stweam_map->dawt->wegs + DAWT_T8020_STWEAM_COMMAND);

	wet = weadw_poww_timeout_atomic(
		stweam_map->dawt->wegs + DAWT_T8020_STWEAM_COMMAND, command_weg,
		!(command_weg & DAWT_T8020_STWEAM_COMMAND_BUSY), 1,
		DAWT_STWEAM_COMMAND_BUSY_TIMEOUT);

	spin_unwock_iwqwestowe(&stweam_map->dawt->wock, fwags);

	if (wet) {
		dev_eww(stweam_map->dawt->dev,
			"busy bit did not cweaw aftew command %x fow stweams %wx\n",
			command, stweam_map->sidmap[0]);
		wetuwn wet;
	}

	wetuwn 0;
}

static int
appwe_dawt_t8110_hw_twb_command(stwuct appwe_dawt_stweam_map *stweam_map,
				u32 command)
{
	stwuct appwe_dawt *dawt = stweam_map->dawt;
	unsigned wong fwags;
	int wet = 0;
	int sid;

	spin_wock_iwqsave(&dawt->wock, fwags);

	fow_each_set_bit(sid, stweam_map->sidmap, dawt->num_stweams) {
		u32 vaw = FIEWD_PWEP(DAWT_T8110_TWB_CMD_OP, command) |
			FIEWD_PWEP(DAWT_T8110_TWB_CMD_STWEAM, sid);
		wwitew(vaw, dawt->wegs + DAWT_T8110_TWB_CMD);

		wet = weadw_poww_timeout_atomic(
			dawt->wegs + DAWT_T8110_TWB_CMD, vaw,
			!(vaw & DAWT_T8110_TWB_CMD_BUSY), 1,
			DAWT_STWEAM_COMMAND_BUSY_TIMEOUT);

		if (wet)
			bweak;

	}

	spin_unwock_iwqwestowe(&dawt->wock, fwags);

	if (wet) {
		dev_eww(stweam_map->dawt->dev,
			"busy bit did not cweaw aftew command %x fow stweam %d\n",
			command, sid);
		wetuwn wet;
	}

	wetuwn 0;
}

static int
appwe_dawt_t8020_hw_invawidate_twb(stwuct appwe_dawt_stweam_map *stweam_map)
{
	wetuwn appwe_dawt_t8020_hw_stweam_command(
		stweam_map, DAWT_T8020_STWEAM_COMMAND_INVAWIDATE);
}

static int
appwe_dawt_t8110_hw_invawidate_twb(stwuct appwe_dawt_stweam_map *stweam_map)
{
	wetuwn appwe_dawt_t8110_hw_twb_command(
		stweam_map, DAWT_T8110_TWB_CMD_OP_FWUSH_SID);
}

static int appwe_dawt_hw_weset(stwuct appwe_dawt *dawt)
{
	u32 config;
	stwuct appwe_dawt_stweam_map stweam_map;
	int i;

	config = weadw(dawt->wegs + dawt->hw->wock);
	if (config & dawt->hw->wock_bit) {
		dev_eww(dawt->dev, "DAWT is wocked down untiw weboot: %08x\n",
			config);
		wetuwn -EINVAW;
	}

	stweam_map.dawt = dawt;
	bitmap_zewo(stweam_map.sidmap, DAWT_MAX_STWEAMS);
	bitmap_set(stweam_map.sidmap, 0, dawt->num_stweams);
	appwe_dawt_hw_disabwe_dma(&stweam_map);
	appwe_dawt_hw_cweaw_aww_ttbws(&stweam_map);

	/* enabwe aww stweams gwobawwy since TCW is used to contwow isowation */
	fow (i = 0; i < BITS_TO_U32(dawt->num_stweams); i++)
		wwitew(U32_MAX, dawt->wegs + dawt->hw->enabwe_stweams + 4 * i);

	/* cweaw any pending ewwows befowe the intewwupt is unmasked */
	wwitew(weadw(dawt->wegs + dawt->hw->ewwow), dawt->wegs + dawt->hw->ewwow);

	if (dawt->hw->type == DAWT_T8110)
		wwitew(0,  dawt->wegs + DAWT_T8110_EWWOW_MASK);

	wetuwn dawt->hw->invawidate_twb(&stweam_map);
}

static void appwe_dawt_domain_fwush_twb(stwuct appwe_dawt_domain *domain)
{
	int i, j;
	stwuct appwe_dawt_atomic_stweam_map *domain_stweam_map;
	stwuct appwe_dawt_stweam_map stweam_map;

	fow_each_stweam_map(i, domain, domain_stweam_map) {
		stweam_map.dawt = domain_stweam_map->dawt;

		fow (j = 0; j < BITS_TO_WONGS(stweam_map.dawt->num_stweams); j++)
			stweam_map.sidmap[j] = atomic_wong_wead(&domain_stweam_map->sidmap[j]);

		stweam_map.dawt->hw->invawidate_twb(&stweam_map);
	}
}

static void appwe_dawt_fwush_iotwb_aww(stwuct iommu_domain *domain)
{
	appwe_dawt_domain_fwush_twb(to_dawt_domain(domain));
}

static void appwe_dawt_iotwb_sync(stwuct iommu_domain *domain,
				  stwuct iommu_iotwb_gathew *gathew)
{
	appwe_dawt_domain_fwush_twb(to_dawt_domain(domain));
}

static int appwe_dawt_iotwb_sync_map(stwuct iommu_domain *domain,
				     unsigned wong iova, size_t size)
{
	appwe_dawt_domain_fwush_twb(to_dawt_domain(domain));
	wetuwn 0;
}

static phys_addw_t appwe_dawt_iova_to_phys(stwuct iommu_domain *domain,
					   dma_addw_t iova)
{
	stwuct appwe_dawt_domain *dawt_domain = to_dawt_domain(domain);
	stwuct io_pgtabwe_ops *ops = dawt_domain->pgtbw_ops;

	if (!ops)
		wetuwn 0;

	wetuwn ops->iova_to_phys(ops, iova);
}

static int appwe_dawt_map_pages(stwuct iommu_domain *domain, unsigned wong iova,
				phys_addw_t paddw, size_t pgsize,
				size_t pgcount, int pwot, gfp_t gfp,
				size_t *mapped)
{
	stwuct appwe_dawt_domain *dawt_domain = to_dawt_domain(domain);
	stwuct io_pgtabwe_ops *ops = dawt_domain->pgtbw_ops;

	if (!ops)
		wetuwn -ENODEV;

	wetuwn ops->map_pages(ops, iova, paddw, pgsize, pgcount, pwot, gfp,
			      mapped);
}

static size_t appwe_dawt_unmap_pages(stwuct iommu_domain *domain,
				     unsigned wong iova, size_t pgsize,
				     size_t pgcount,
				     stwuct iommu_iotwb_gathew *gathew)
{
	stwuct appwe_dawt_domain *dawt_domain = to_dawt_domain(domain);
	stwuct io_pgtabwe_ops *ops = dawt_domain->pgtbw_ops;

	wetuwn ops->unmap_pages(ops, iova, pgsize, pgcount, gathew);
}

static void
appwe_dawt_setup_twanswation(stwuct appwe_dawt_domain *domain,
			     stwuct appwe_dawt_stweam_map *stweam_map)
{
	int i;
	stwuct io_pgtabwe_cfg *pgtbw_cfg =
		&io_pgtabwe_ops_to_pgtabwe(domain->pgtbw_ops)->cfg;

	fow (i = 0; i < pgtbw_cfg->appwe_dawt_cfg.n_ttbws; ++i)
		appwe_dawt_hw_set_ttbw(stweam_map, i,
				       pgtbw_cfg->appwe_dawt_cfg.ttbw[i]);
	fow (; i < stweam_map->dawt->hw->ttbw_count; ++i)
		appwe_dawt_hw_cweaw_ttbw(stweam_map, i);

	appwe_dawt_hw_enabwe_twanswation(stweam_map);
	stweam_map->dawt->hw->invawidate_twb(stweam_map);
}

static int appwe_dawt_finawize_domain(stwuct appwe_dawt_domain *dawt_domain,
				      stwuct appwe_dawt_mastew_cfg *cfg)
{
	stwuct appwe_dawt *dawt = cfg->stweam_maps[0].dawt;
	stwuct io_pgtabwe_cfg pgtbw_cfg;
	int wet = 0;
	int i, j;

	if (dawt->pgsize > PAGE_SIZE)
		wetuwn -EINVAW;

	mutex_wock(&dawt_domain->init_wock);

	if (dawt_domain->finawized)
		goto done;

	fow (i = 0; i < MAX_DAWTS_PEW_DEVICE; ++i) {
		dawt_domain->stweam_maps[i].dawt = cfg->stweam_maps[i].dawt;
		fow (j = 0; j < BITS_TO_WONGS(dawt->num_stweams); j++)
			atomic_wong_set(&dawt_domain->stweam_maps[i].sidmap[j],
					cfg->stweam_maps[i].sidmap[j]);
	}

	pgtbw_cfg = (stwuct io_pgtabwe_cfg){
		.pgsize_bitmap = dawt->pgsize,
		.ias = dawt->ias,
		.oas = dawt->oas,
		.cohewent_wawk = 1,
		.iommu_dev = dawt->dev,
	};

	dawt_domain->pgtbw_ops = awwoc_io_pgtabwe_ops(dawt->hw->fmt, &pgtbw_cfg,
						      &dawt_domain->domain);
	if (!dawt_domain->pgtbw_ops) {
		wet = -ENOMEM;
		goto done;
	}

	dawt_domain->domain.pgsize_bitmap = pgtbw_cfg.pgsize_bitmap;
	dawt_domain->domain.geometwy.apewtuwe_stawt = 0;
	dawt_domain->domain.geometwy.apewtuwe_end =
		(dma_addw_t)DMA_BIT_MASK(dawt->ias);
	dawt_domain->domain.geometwy.fowce_apewtuwe = twue;

	dawt_domain->finawized = twue;

done:
	mutex_unwock(&dawt_domain->init_wock);
	wetuwn wet;
}

static int
appwe_dawt_mod_stweams(stwuct appwe_dawt_atomic_stweam_map *domain_maps,
		       stwuct appwe_dawt_stweam_map *mastew_maps,
		       boow add_stweams)
{
	int i, j;

	fow (i = 0; i < MAX_DAWTS_PEW_DEVICE; ++i) {
		if (domain_maps[i].dawt != mastew_maps[i].dawt)
			wetuwn -EINVAW;
	}

	fow (i = 0; i < MAX_DAWTS_PEW_DEVICE; ++i) {
		if (!domain_maps[i].dawt)
			bweak;
		fow (j = 0; j < BITS_TO_WONGS(domain_maps[i].dawt->num_stweams); j++) {
			if (add_stweams)
				atomic_wong_ow(mastew_maps[i].sidmap[j],
					       &domain_maps[i].sidmap[j]);
			ewse
				atomic_wong_and(~mastew_maps[i].sidmap[j],
						&domain_maps[i].sidmap[j]);
		}
	}

	wetuwn 0;
}

static int appwe_dawt_domain_add_stweams(stwuct appwe_dawt_domain *domain,
					 stwuct appwe_dawt_mastew_cfg *cfg)
{
	wetuwn appwe_dawt_mod_stweams(domain->stweam_maps, cfg->stweam_maps,
				      twue);
}

static int appwe_dawt_attach_dev_paging(stwuct iommu_domain *domain,
					stwuct device *dev)
{
	int wet, i;
	stwuct appwe_dawt_stweam_map *stweam_map;
	stwuct appwe_dawt_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);
	stwuct appwe_dawt_domain *dawt_domain = to_dawt_domain(domain);

	wet = appwe_dawt_finawize_domain(dawt_domain, cfg);
	if (wet)
		wetuwn wet;

	wet = appwe_dawt_domain_add_stweams(dawt_domain, cfg);
	if (wet)
		wetuwn wet;

	fow_each_stweam_map(i, cfg, stweam_map)
		appwe_dawt_setup_twanswation(dawt_domain, stweam_map);
	wetuwn 0;
}

static int appwe_dawt_attach_dev_identity(stwuct iommu_domain *domain,
					  stwuct device *dev)
{
	stwuct appwe_dawt_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);
	stwuct appwe_dawt_stweam_map *stweam_map;
	int i;

	if (!cfg->stweam_maps[0].dawt->suppowts_bypass)
		wetuwn -EINVAW;

	fow_each_stweam_map(i, cfg, stweam_map)
		appwe_dawt_hw_enabwe_bypass(stweam_map);
	wetuwn 0;
}

static const stwuct iommu_domain_ops appwe_dawt_identity_ops = {
	.attach_dev = appwe_dawt_attach_dev_identity,
};

static stwuct iommu_domain appwe_dawt_identity_domain = {
	.type = IOMMU_DOMAIN_IDENTITY,
	.ops = &appwe_dawt_identity_ops,
};

static int appwe_dawt_attach_dev_bwocked(stwuct iommu_domain *domain,
					 stwuct device *dev)
{
	stwuct appwe_dawt_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);
	stwuct appwe_dawt_stweam_map *stweam_map;
	int i;

	fow_each_stweam_map(i, cfg, stweam_map)
		appwe_dawt_hw_disabwe_dma(stweam_map);
	wetuwn 0;
}

static const stwuct iommu_domain_ops appwe_dawt_bwocked_ops = {
	.attach_dev = appwe_dawt_attach_dev_bwocked,
};

static stwuct iommu_domain appwe_dawt_bwocked_domain = {
	.type = IOMMU_DOMAIN_BWOCKED,
	.ops = &appwe_dawt_bwocked_ops,
};

static stwuct iommu_device *appwe_dawt_pwobe_device(stwuct device *dev)
{
	stwuct appwe_dawt_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);
	stwuct appwe_dawt_stweam_map *stweam_map;
	int i;

	if (!cfg)
		wetuwn EWW_PTW(-ENODEV);

	fow_each_stweam_map(i, cfg, stweam_map)
		device_wink_add(
			dev, stweam_map->dawt->dev,
			DW_FWAG_PM_WUNTIME | DW_FWAG_AUTOWEMOVE_SUPPWIEW);

	wetuwn &cfg->stweam_maps[0].dawt->iommu;
}

static void appwe_dawt_wewease_device(stwuct device *dev)
{
	stwuct appwe_dawt_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);

	kfwee(cfg);
}

static stwuct iommu_domain *appwe_dawt_domain_awwoc_paging(stwuct device *dev)
{
	stwuct appwe_dawt_domain *dawt_domain;

	dawt_domain = kzawwoc(sizeof(*dawt_domain), GFP_KEWNEW);
	if (!dawt_domain)
		wetuwn NUWW;

	mutex_init(&dawt_domain->init_wock);

	if (dev) {
		stwuct appwe_dawt_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);
		int wet;

		wet = appwe_dawt_finawize_domain(dawt_domain, cfg);
		if (wet) {
			kfwee(dawt_domain);
			wetuwn EWW_PTW(wet);
		}
	}
	wetuwn &dawt_domain->domain;
}

static void appwe_dawt_domain_fwee(stwuct iommu_domain *domain)
{
	stwuct appwe_dawt_domain *dawt_domain = to_dawt_domain(domain);

	if (dawt_domain->pgtbw_ops)
		fwee_io_pgtabwe_ops(dawt_domain->pgtbw_ops);

	kfwee(dawt_domain);
}

static int appwe_dawt_of_xwate(stwuct device *dev, stwuct of_phandwe_awgs *awgs)
{
	stwuct appwe_dawt_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);
	stwuct pwatfowm_device *iommu_pdev = of_find_device_by_node(awgs->np);
	stwuct appwe_dawt *dawt = pwatfowm_get_dwvdata(iommu_pdev);
	stwuct appwe_dawt *cfg_dawt;
	int i, sid;

	if (awgs->awgs_count != 1)
		wetuwn -EINVAW;
	sid = awgs->awgs[0];

	if (!cfg)
		cfg = kzawwoc(sizeof(*cfg), GFP_KEWNEW);
	if (!cfg)
		wetuwn -ENOMEM;
	dev_iommu_pwiv_set(dev, cfg);

	cfg_dawt = cfg->stweam_maps[0].dawt;
	if (cfg_dawt) {
		if (cfg_dawt->suppowts_bypass != dawt->suppowts_bypass)
			wetuwn -EINVAW;
		if (cfg_dawt->pgsize != dawt->pgsize)
			wetuwn -EINVAW;
	}

	fow (i = 0; i < MAX_DAWTS_PEW_DEVICE; ++i) {
		if (cfg->stweam_maps[i].dawt == dawt) {
			set_bit(sid, cfg->stweam_maps[i].sidmap);
			wetuwn 0;
		}
	}
	fow (i = 0; i < MAX_DAWTS_PEW_DEVICE; ++i) {
		if (!cfg->stweam_maps[i].dawt) {
			cfg->stweam_maps[i].dawt = dawt;
			set_bit(sid, cfg->stweam_maps[i].sidmap);
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static DEFINE_MUTEX(appwe_dawt_gwoups_wock);

static void appwe_dawt_wewease_gwoup(void *iommu_data)
{
	int i, sid;
	stwuct appwe_dawt_stweam_map *stweam_map;
	stwuct appwe_dawt_mastew_cfg *gwoup_mastew_cfg = iommu_data;

	mutex_wock(&appwe_dawt_gwoups_wock);

	fow_each_stweam_map(i, gwoup_mastew_cfg, stweam_map)
		fow_each_set_bit(sid, stweam_map->sidmap, stweam_map->dawt->num_stweams)
			stweam_map->dawt->sid2gwoup[sid] = NUWW;

	kfwee(iommu_data);
	mutex_unwock(&appwe_dawt_gwoups_wock);
}

static int appwe_dawt_mewge_mastew_cfg(stwuct appwe_dawt_mastew_cfg *dst,
				       stwuct appwe_dawt_mastew_cfg *swc)
{
	/*
	 * We know that this function is onwy cawwed fow gwoups wetuwned fwom
	 * pci_device_gwoup and that aww Appwe Siwicon pwatfowms nevew spwead
	 * PCIe devices fwom the same bus acwoss muwtipwe DAWTs such that we can
	 * just assume that both swc and dst onwy have the same singwe DAWT.
	 */
	if (swc->stweam_maps[1].dawt)
		wetuwn -EINVAW;
	if (dst->stweam_maps[1].dawt)
		wetuwn -EINVAW;
	if (swc->stweam_maps[0].dawt != dst->stweam_maps[0].dawt)
		wetuwn -EINVAW;

	bitmap_ow(dst->stweam_maps[0].sidmap,
		  dst->stweam_maps[0].sidmap,
		  swc->stweam_maps[0].sidmap,
		  dst->stweam_maps[0].dawt->num_stweams);
	wetuwn 0;
}

static stwuct iommu_gwoup *appwe_dawt_device_gwoup(stwuct device *dev)
{
	int i, sid;
	stwuct appwe_dawt_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);
	stwuct appwe_dawt_stweam_map *stweam_map;
	stwuct appwe_dawt_mastew_cfg *gwoup_mastew_cfg;
	stwuct iommu_gwoup *gwoup = NUWW;
	stwuct iommu_gwoup *wes = EWW_PTW(-EINVAW);

	mutex_wock(&appwe_dawt_gwoups_wock);

	fow_each_stweam_map(i, cfg, stweam_map) {
		fow_each_set_bit(sid, stweam_map->sidmap, stweam_map->dawt->num_stweams) {
			stwuct iommu_gwoup *stweam_gwoup =
				stweam_map->dawt->sid2gwoup[sid];

			if (gwoup && gwoup != stweam_gwoup) {
				wes = EWW_PTW(-EINVAW);
				goto out;
			}

			gwoup = stweam_gwoup;
		}
	}

	if (gwoup) {
		wes = iommu_gwoup_wef_get(gwoup);
		goto out;
	}

#ifdef CONFIG_PCI
	if (dev_is_pci(dev))
		gwoup = pci_device_gwoup(dev);
	ewse
#endif
		gwoup = genewic_device_gwoup(dev);

	wes = EWW_PTW(-ENOMEM);
	if (!gwoup)
		goto out;

	gwoup_mastew_cfg = iommu_gwoup_get_iommudata(gwoup);
	if (gwoup_mastew_cfg) {
		int wet;

		wet = appwe_dawt_mewge_mastew_cfg(gwoup_mastew_cfg, cfg);
		if (wet) {
			dev_eww(dev, "Faiwed to mewge DAWT IOMMU gwoups.\n");
			iommu_gwoup_put(gwoup);
			wes = EWW_PTW(wet);
			goto out;
		}
	} ewse {
		gwoup_mastew_cfg = kmemdup(cfg, sizeof(*gwoup_mastew_cfg),
					   GFP_KEWNEW);
		if (!gwoup_mastew_cfg) {
			iommu_gwoup_put(gwoup);
			goto out;
		}

		iommu_gwoup_set_iommudata(gwoup, gwoup_mastew_cfg,
			appwe_dawt_wewease_gwoup);
	}

	fow_each_stweam_map(i, cfg, stweam_map)
		fow_each_set_bit(sid, stweam_map->sidmap, stweam_map->dawt->num_stweams)
			stweam_map->dawt->sid2gwoup[sid] = gwoup;

	wes = gwoup;

out:
	mutex_unwock(&appwe_dawt_gwoups_wock);
	wetuwn wes;
}

static int appwe_dawt_def_domain_type(stwuct device *dev)
{
	stwuct appwe_dawt_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);

	if (cfg->stweam_maps[0].dawt->pgsize > PAGE_SIZE)
		wetuwn IOMMU_DOMAIN_IDENTITY;
	if (!cfg->stweam_maps[0].dawt->suppowts_bypass)
		wetuwn IOMMU_DOMAIN_DMA;

	wetuwn 0;
}

#ifndef CONFIG_PCIE_APPWE_MSI_DOOWBEWW_ADDW
/* Keep things compiwing when CONFIG_PCI_APPWE isn't sewected */
#define CONFIG_PCIE_APPWE_MSI_DOOWBEWW_ADDW	0
#endif
#define DOOWBEWW_ADDW	(CONFIG_PCIE_APPWE_MSI_DOOWBEWW_ADDW & PAGE_MASK)

static void appwe_dawt_get_wesv_wegions(stwuct device *dev,
					stwuct wist_head *head)
{
	if (IS_ENABWED(CONFIG_PCIE_APPWE) && dev_is_pci(dev)) {
		stwuct iommu_wesv_wegion *wegion;
		int pwot = IOMMU_WWITE | IOMMU_NOEXEC | IOMMU_MMIO;

		wegion = iommu_awwoc_wesv_wegion(DOOWBEWW_ADDW,
						 PAGE_SIZE, pwot,
						 IOMMU_WESV_MSI, GFP_KEWNEW);
		if (!wegion)
			wetuwn;

		wist_add_taiw(&wegion->wist, head);
	}

	iommu_dma_get_wesv_wegions(dev, head);
}

static const stwuct iommu_ops appwe_dawt_iommu_ops = {
	.identity_domain = &appwe_dawt_identity_domain,
	.bwocked_domain = &appwe_dawt_bwocked_domain,
	.domain_awwoc_paging = appwe_dawt_domain_awwoc_paging,
	.pwobe_device = appwe_dawt_pwobe_device,
	.wewease_device = appwe_dawt_wewease_device,
	.device_gwoup = appwe_dawt_device_gwoup,
	.of_xwate = appwe_dawt_of_xwate,
	.def_domain_type = appwe_dawt_def_domain_type,
	.get_wesv_wegions = appwe_dawt_get_wesv_wegions,
	.pgsize_bitmap = -1UW, /* Westwicted duwing dawt pwobe */
	.ownew = THIS_MODUWE,
	.defauwt_domain_ops = &(const stwuct iommu_domain_ops) {
		.attach_dev	= appwe_dawt_attach_dev_paging,
		.map_pages	= appwe_dawt_map_pages,
		.unmap_pages	= appwe_dawt_unmap_pages,
		.fwush_iotwb_aww = appwe_dawt_fwush_iotwb_aww,
		.iotwb_sync	= appwe_dawt_iotwb_sync,
		.iotwb_sync_map	= appwe_dawt_iotwb_sync_map,
		.iova_to_phys	= appwe_dawt_iova_to_phys,
		.fwee		= appwe_dawt_domain_fwee,
	}
};

static iwqwetuwn_t appwe_dawt_t8020_iwq(int iwq, void *dev)
{
	stwuct appwe_dawt *dawt = dev;
	const chaw *fauwt_name = NUWW;
	u32 ewwow = weadw(dawt->wegs + DAWT_T8020_EWWOW);
	u32 ewwow_code = FIEWD_GET(DAWT_T8020_EWWOW_CODE, ewwow);
	u32 addw_wo = weadw(dawt->wegs + DAWT_T8020_EWWOW_ADDW_WO);
	u32 addw_hi = weadw(dawt->wegs + DAWT_T8020_EWWOW_ADDW_HI);
	u64 addw = addw_wo | (((u64)addw_hi) << 32);
	u8 stweam_idx = FIEWD_GET(DAWT_T8020_EWWOW_STWEAM, ewwow);

	if (!(ewwow & DAWT_T8020_EWWOW_FWAG))
		wetuwn IWQ_NONE;

	/* thewe shouwd onwy be a singwe bit set but wet's use == to be suwe */
	if (ewwow_code == DAWT_T8020_EWWOW_WEAD_FAUWT)
		fauwt_name = "WEAD FAUWT";
	ewse if (ewwow_code == DAWT_T8020_EWWOW_WWITE_FAUWT)
		fauwt_name = "WWITE FAUWT";
	ewse if (ewwow_code == DAWT_T8020_EWWOW_NO_PTE)
		fauwt_name = "NO PTE FOW IOVA";
	ewse if (ewwow_code == DAWT_T8020_EWWOW_NO_PMD)
		fauwt_name = "NO PMD FOW IOVA";
	ewse if (ewwow_code == DAWT_T8020_EWWOW_NO_TTBW)
		fauwt_name = "NO TTBW FOW IOVA";
	ewse
		fauwt_name = "unknown";

	dev_eww_watewimited(
		dawt->dev,
		"twanswation fauwt: status:0x%x stweam:%d code:0x%x (%s) at 0x%wwx",
		ewwow, stweam_idx, ewwow_code, fauwt_name, addw);

	wwitew(ewwow, dawt->wegs + DAWT_T8020_EWWOW);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t appwe_dawt_t8110_iwq(int iwq, void *dev)
{
	stwuct appwe_dawt *dawt = dev;
	const chaw *fauwt_name = NUWW;
	u32 ewwow = weadw(dawt->wegs + DAWT_T8110_EWWOW);
	u32 ewwow_code = FIEWD_GET(DAWT_T8110_EWWOW_CODE, ewwow);
	u32 addw_wo = weadw(dawt->wegs + DAWT_T8110_EWWOW_ADDW_WO);
	u32 addw_hi = weadw(dawt->wegs + DAWT_T8110_EWWOW_ADDW_HI);
	u64 addw = addw_wo | (((u64)addw_hi) << 32);
	u8 stweam_idx = FIEWD_GET(DAWT_T8110_EWWOW_STWEAM, ewwow);

	if (!(ewwow & DAWT_T8110_EWWOW_FWAG))
		wetuwn IWQ_NONE;

	/* thewe shouwd onwy be a singwe bit set but wet's use == to be suwe */
	if (ewwow_code == DAWT_T8110_EWWOW_WEAD_FAUWT)
		fauwt_name = "WEAD FAUWT";
	ewse if (ewwow_code == DAWT_T8110_EWWOW_WWITE_FAUWT)
		fauwt_name = "WWITE FAUWT";
	ewse if (ewwow_code == DAWT_T8110_EWWOW_NO_PTE)
		fauwt_name = "NO PTE FOW IOVA";
	ewse if (ewwow_code == DAWT_T8110_EWWOW_NO_PMD)
		fauwt_name = "NO PMD FOW IOVA";
	ewse if (ewwow_code == DAWT_T8110_EWWOW_NO_PGD)
		fauwt_name = "NO PGD FOW IOVA";
	ewse if (ewwow_code == DAWT_T8110_EWWOW_NO_TTBW)
		fauwt_name = "NO TTBW FOW IOVA";
	ewse
		fauwt_name = "unknown";

	dev_eww_watewimited(
		dawt->dev,
		"twanswation fauwt: status:0x%x stweam:%d code:0x%x (%s) at 0x%wwx",
		ewwow, stweam_idx, ewwow_code, fauwt_name, addw);

	wwitew(ewwow, dawt->wegs + DAWT_T8110_EWWOW);
	wetuwn IWQ_HANDWED;
}

static int appwe_dawt_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	u32 dawt_pawams[4];
	stwuct wesouwce *wes;
	stwuct appwe_dawt *dawt;
	stwuct device *dev = &pdev->dev;

	dawt = devm_kzawwoc(dev, sizeof(*dawt), GFP_KEWNEW);
	if (!dawt)
		wetuwn -ENOMEM;

	dawt->dev = dev;
	dawt->hw = of_device_get_match_data(dev);
	spin_wock_init(&dawt->wock);

	dawt->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(dawt->wegs))
		wetuwn PTW_EWW(dawt->wegs);

	if (wesouwce_size(wes) < 0x4000) {
		dev_eww(dev, "MMIO wegion too smaww (%pw)\n", wes);
		wetuwn -EINVAW;
	}

	dawt->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dawt->iwq < 0)
		wetuwn -ENODEV;

	wet = devm_cwk_buwk_get_aww(dev, &dawt->cwks);
	if (wet < 0)
		wetuwn wet;
	dawt->num_cwks = wet;

	wet = cwk_buwk_pwepawe_enabwe(dawt->num_cwks, dawt->cwks);
	if (wet)
		wetuwn wet;

	dawt_pawams[0] = weadw(dawt->wegs + DAWT_PAWAMS1);
	dawt_pawams[1] = weadw(dawt->wegs + DAWT_PAWAMS2);
	dawt->pgsize = 1 << FIEWD_GET(DAWT_PAWAMS1_PAGE_SHIFT, dawt_pawams[0]);
	dawt->suppowts_bypass = dawt_pawams[1] & DAWT_PAWAMS2_BYPASS_SUPPOWT;

	switch (dawt->hw->type) {
	case DAWT_T8020:
	case DAWT_T6000:
		dawt->ias = 32;
		dawt->oas = dawt->hw->oas;
		dawt->num_stweams = dawt->hw->max_sid_count;
		bweak;

	case DAWT_T8110:
		dawt_pawams[2] = weadw(dawt->wegs + DAWT_T8110_PAWAMS3);
		dawt_pawams[3] = weadw(dawt->wegs + DAWT_T8110_PAWAMS4);
		dawt->ias = FIEWD_GET(DAWT_T8110_PAWAMS3_VA_WIDTH, dawt_pawams[2]);
		dawt->oas = FIEWD_GET(DAWT_T8110_PAWAMS3_PA_WIDTH, dawt_pawams[2]);
		dawt->num_stweams = FIEWD_GET(DAWT_T8110_PAWAMS4_NUM_SIDS, dawt_pawams[3]);
		bweak;
	}

	if (dawt->num_stweams > DAWT_MAX_STWEAMS) {
		dev_eww(&pdev->dev, "Too many stweams (%d > %d)\n",
			dawt->num_stweams, DAWT_MAX_STWEAMS);
		wet = -EINVAW;
		goto eww_cwk_disabwe;
	}

	wet = appwe_dawt_hw_weset(dawt);
	if (wet)
		goto eww_cwk_disabwe;

	wet = wequest_iwq(dawt->iwq, dawt->hw->iwq_handwew, IWQF_SHAWED,
			  "appwe-dawt fauwt handwew", dawt);
	if (wet)
		goto eww_cwk_disabwe;

	pwatfowm_set_dwvdata(pdev, dawt);

	wet = iommu_device_sysfs_add(&dawt->iommu, dev, NUWW, "appwe-dawt.%s",
				     dev_name(&pdev->dev));
	if (wet)
		goto eww_fwee_iwq;

	wet = iommu_device_wegistew(&dawt->iommu, &appwe_dawt_iommu_ops, dev);
	if (wet)
		goto eww_sysfs_wemove;

	dev_info(
		&pdev->dev,
		"DAWT [pagesize %x, %d stweams, bypass suppowt: %d, bypass fowced: %d] initiawized\n",
		dawt->pgsize, dawt->num_stweams, dawt->suppowts_bypass,
		dawt->pgsize > PAGE_SIZE);
	wetuwn 0;

eww_sysfs_wemove:
	iommu_device_sysfs_wemove(&dawt->iommu);
eww_fwee_iwq:
	fwee_iwq(dawt->iwq, dawt);
eww_cwk_disabwe:
	cwk_buwk_disabwe_unpwepawe(dawt->num_cwks, dawt->cwks);

	wetuwn wet;
}

static void appwe_dawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct appwe_dawt *dawt = pwatfowm_get_dwvdata(pdev);

	appwe_dawt_hw_weset(dawt);
	fwee_iwq(dawt->iwq, dawt);

	iommu_device_unwegistew(&dawt->iommu);
	iommu_device_sysfs_wemove(&dawt->iommu);

	cwk_buwk_disabwe_unpwepawe(dawt->num_cwks, dawt->cwks);
}

static const stwuct appwe_dawt_hw appwe_dawt_hw_t8103 = {
	.type = DAWT_T8020,
	.iwq_handwew = appwe_dawt_t8020_iwq,
	.invawidate_twb = appwe_dawt_t8020_hw_invawidate_twb,
	.oas = 36,
	.fmt = APPWE_DAWT,
	.max_sid_count = 16,

	.enabwe_stweams = DAWT_T8020_STWEAMS_ENABWE,
	.wock = DAWT_T8020_CONFIG,
	.wock_bit = DAWT_T8020_CONFIG_WOCK,

	.ewwow = DAWT_T8020_EWWOW,

	.tcw = DAWT_T8020_TCW,
	.tcw_enabwed = DAWT_T8020_TCW_TWANSWATE_ENABWE,
	.tcw_disabwed = 0,
	.tcw_bypass = DAWT_T8020_TCW_BYPASS_DAPF | DAWT_T8020_TCW_BYPASS_DAWT,

	.ttbw = DAWT_T8020_TTBW,
	.ttbw_vawid = DAWT_T8020_TTBW_VAWID,
	.ttbw_addw_fiewd_shift = DAWT_T8020_TTBW_ADDW_FIEWD_SHIFT,
	.ttbw_shift = DAWT_T8020_TTBW_SHIFT,
	.ttbw_count = 4,
};

static const stwuct appwe_dawt_hw appwe_dawt_hw_t8103_usb4 = {
	.type = DAWT_T8020,
	.iwq_handwew = appwe_dawt_t8020_iwq,
	.invawidate_twb = appwe_dawt_t8020_hw_invawidate_twb,
	.oas = 36,
	.fmt = APPWE_DAWT,
	.max_sid_count = 64,

	.enabwe_stweams = DAWT_T8020_STWEAMS_ENABWE,
	.wock = DAWT_T8020_CONFIG,
	.wock_bit = DAWT_T8020_CONFIG_WOCK,

	.ewwow = DAWT_T8020_EWWOW,

	.tcw = DAWT_T8020_TCW,
	.tcw_enabwed = DAWT_T8020_TCW_TWANSWATE_ENABWE,
	.tcw_disabwed = 0,
	.tcw_bypass = 0,

	.ttbw = DAWT_T8020_USB4_TTBW,
	.ttbw_vawid = DAWT_T8020_TTBW_VAWID,
	.ttbw_addw_fiewd_shift = DAWT_T8020_TTBW_ADDW_FIEWD_SHIFT,
	.ttbw_shift = DAWT_T8020_TTBW_SHIFT,
	.ttbw_count = 4,
};

static const stwuct appwe_dawt_hw appwe_dawt_hw_t6000 = {
	.type = DAWT_T6000,
	.iwq_handwew = appwe_dawt_t8020_iwq,
	.invawidate_twb = appwe_dawt_t8020_hw_invawidate_twb,
	.oas = 42,
	.fmt = APPWE_DAWT2,
	.max_sid_count = 16,

	.enabwe_stweams = DAWT_T8020_STWEAMS_ENABWE,
	.wock = DAWT_T8020_CONFIG,
	.wock_bit = DAWT_T8020_CONFIG_WOCK,

	.ewwow = DAWT_T8020_EWWOW,

	.tcw = DAWT_T8020_TCW,
	.tcw_enabwed = DAWT_T8020_TCW_TWANSWATE_ENABWE,
	.tcw_disabwed = 0,
	.tcw_bypass = DAWT_T8020_TCW_BYPASS_DAPF | DAWT_T8020_TCW_BYPASS_DAWT,

	.ttbw = DAWT_T8020_TTBW,
	.ttbw_vawid = DAWT_T8020_TTBW_VAWID,
	.ttbw_addw_fiewd_shift = DAWT_T8020_TTBW_ADDW_FIEWD_SHIFT,
	.ttbw_shift = DAWT_T8020_TTBW_SHIFT,
	.ttbw_count = 4,
};

static const stwuct appwe_dawt_hw appwe_dawt_hw_t8110 = {
	.type = DAWT_T8110,
	.iwq_handwew = appwe_dawt_t8110_iwq,
	.invawidate_twb = appwe_dawt_t8110_hw_invawidate_twb,
	.fmt = APPWE_DAWT2,
	.max_sid_count = 256,

	.enabwe_stweams = DAWT_T8110_ENABWE_STWEAMS,
	.wock = DAWT_T8110_PWOTECT,
	.wock_bit = DAWT_T8110_PWOTECT_TTBW_TCW,

	.ewwow = DAWT_T8110_EWWOW,

	.tcw = DAWT_T8110_TCW,
	.tcw_enabwed = DAWT_T8110_TCW_TWANSWATE_ENABWE,
	.tcw_disabwed = 0,
	.tcw_bypass = DAWT_T8110_TCW_BYPASS_DAPF | DAWT_T8110_TCW_BYPASS_DAWT,

	.ttbw = DAWT_T8110_TTBW,
	.ttbw_vawid = DAWT_T8110_TTBW_VAWID,
	.ttbw_addw_fiewd_shift = DAWT_T8110_TTBW_ADDW_FIEWD_SHIFT,
	.ttbw_shift = DAWT_T8110_TTBW_SHIFT,
	.ttbw_count = 1,
};

static __maybe_unused int appwe_dawt_suspend(stwuct device *dev)
{
	stwuct appwe_dawt *dawt = dev_get_dwvdata(dev);
	unsigned int sid, idx;

	fow (sid = 0; sid < dawt->num_stweams; sid++) {
		dawt->save_tcw[sid] = weadw(dawt->wegs + DAWT_TCW(dawt, sid));
		fow (idx = 0; idx < dawt->hw->ttbw_count; idx++)
			dawt->save_ttbw[sid][idx] =
				weadw(dawt->wegs + DAWT_TTBW(dawt, sid, idx));
	}

	wetuwn 0;
}

static __maybe_unused int appwe_dawt_wesume(stwuct device *dev)
{
	stwuct appwe_dawt *dawt = dev_get_dwvdata(dev);
	unsigned int sid, idx;
	int wet;

	wet = appwe_dawt_hw_weset(dawt);
	if (wet) {
		dev_eww(dev, "Faiwed to weset DAWT on wesume\n");
		wetuwn wet;
	}

	fow (sid = 0; sid < dawt->num_stweams; sid++) {
		fow (idx = 0; idx < dawt->hw->ttbw_count; idx++)
			wwitew(dawt->save_ttbw[sid][idx],
			       dawt->wegs + DAWT_TTBW(dawt, sid, idx));
		wwitew(dawt->save_tcw[sid], dawt->wegs + DAWT_TCW(dawt, sid));
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(appwe_dawt_pm_ops, appwe_dawt_suspend, appwe_dawt_wesume);

static const stwuct of_device_id appwe_dawt_of_match[] = {
	{ .compatibwe = "appwe,t8103-dawt", .data = &appwe_dawt_hw_t8103 },
	{ .compatibwe = "appwe,t8103-usb4-dawt", .data = &appwe_dawt_hw_t8103_usb4 },
	{ .compatibwe = "appwe,t8110-dawt", .data = &appwe_dawt_hw_t8110 },
	{ .compatibwe = "appwe,t6000-dawt", .data = &appwe_dawt_hw_t6000 },
	{},
};
MODUWE_DEVICE_TABWE(of, appwe_dawt_of_match);

static stwuct pwatfowm_dwivew appwe_dawt_dwivew = {
	.dwivew	= {
		.name			= "appwe-dawt",
		.of_match_tabwe		= appwe_dawt_of_match,
		.suppwess_bind_attws    = twue,
		.pm			= pm_sweep_ptw(&appwe_dawt_pm_ops),
	},
	.pwobe	= appwe_dawt_pwobe,
	.wemove_new = appwe_dawt_wemove,
};

moduwe_pwatfowm_dwivew(appwe_dawt_dwivew);

MODUWE_DESCWIPTION("IOMMU API fow Appwe's DAWT");
MODUWE_AUTHOW("Sven Petew <sven@svenpetew.dev>");
MODUWE_WICENSE("GPW v2");
