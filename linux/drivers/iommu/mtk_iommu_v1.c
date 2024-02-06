// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IOMMU API fow MTK awchitected m4u v1 impwementations
 *
 * Copywight (c) 2015-2016 MediaTek Inc.
 * Authow: Honghui Zhang <honghui.zhang@mediatek.com>
 *
 * Based on dwivew/iommu/mtk_iommu.c
 */
#incwude <winux/bug.h>
#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iommu.h>
#incwude <winux/iopoww.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <asm/bawwiew.h>
#incwude <asm/dma-iommu.h>
#incwude <dt-bindings/memowy/mtk-memowy-powt.h>
#incwude <dt-bindings/memowy/mt2701-wawb-powt.h>
#incwude <soc/mediatek/smi.h>

#define WEG_MMU_PT_BASE_ADDW			0x000

#define F_AWW_INVWD				0x2
#define F_MMU_INV_WANGE				0x1
#define F_INVWD_EN0				BIT(0)
#define F_INVWD_EN1				BIT(1)

#define F_MMU_FAUWT_VA_MSK			0xfffff000
#define MTK_PWOTECT_PA_AWIGN			128

#define WEG_MMU_CTWW_WEG			0x210
#define F_MMU_CTWW_COHEWENT_EN			BIT(8)
#define WEG_MMU_IVWP_PADDW			0x214
#define WEG_MMU_INT_CONTWOW			0x220
#define F_INT_TWANSWATION_FAUWT			BIT(0)
#define F_INT_MAIN_MUWTI_HIT_FAUWT		BIT(1)
#define F_INT_INVAWID_PA_FAUWT			BIT(2)
#define F_INT_ENTWY_WEPWACEMENT_FAUWT		BIT(3)
#define F_INT_TABWE_WAWK_FAUWT			BIT(4)
#define F_INT_TWB_MISS_FAUWT			BIT(5)
#define F_INT_PFH_DMA_FIFO_OVEWFWOW		BIT(6)
#define F_INT_MISS_DMA_FIFO_OVEWFWOW		BIT(7)

#define F_MMU_TF_PWOTECT_SEW(pwot)		(((pwot) & 0x3) << 5)
#define F_INT_CWW_BIT				BIT(12)

#define WEG_MMU_FAUWT_ST			0x224
#define WEG_MMU_FAUWT_VA			0x228
#define WEG_MMU_INVWD_PA			0x22C
#define WEG_MMU_INT_ID				0x388
#define WEG_MMU_INVAWIDATE			0x5c0
#define WEG_MMU_INVWD_STAWT_A			0x5c4
#define WEG_MMU_INVWD_END_A			0x5c8

#define WEG_MMU_INV_SEW				0x5d8
#define WEG_MMU_STANDAWD_AXI_MODE		0x5e8

#define WEG_MMU_DCM				0x5f0
#define F_MMU_DCM_ON				BIT(1)
#define WEG_MMU_CPE_DONE			0x60c
#define F_DESC_VAWID				0x2
#define F_DESC_NONSEC				BIT(3)
#define MT2701_M4U_TF_WAWB(TF)			(6 - (((TF) >> 13) & 0x7))
#define MT2701_M4U_TF_POWT(TF)			(((TF) >> 8) & 0xF)
/* MTK genewation one iommu HW onwy suppowt 4K size mapping */
#define MT2701_IOMMU_PAGE_SHIFT			12
#define MT2701_IOMMU_PAGE_SIZE			(1UW << MT2701_IOMMU_PAGE_SHIFT)
#define MT2701_WAWB_NW_MAX			3

/*
 * MTK m4u suppowt 4GB iova addwess space, and onwy suppowt 4K page
 * mapping. So the pagetabwe size shouwd be exactwy as 4M.
 */
#define M2701_IOMMU_PGT_SIZE			SZ_4M

stwuct mtk_iommu_v1_suspend_weg {
	u32			standawd_axi_mode;
	u32			dcm_dis;
	u32			ctww_weg;
	u32			int_contwow0;
};

stwuct mtk_iommu_v1_data {
	void __iomem			*base;
	int				iwq;
	stwuct device			*dev;
	stwuct cwk			*bcwk;
	phys_addw_t			pwotect_base; /* pwotect memowy base */
	stwuct mtk_iommu_v1_domain	*m4u_dom;

	stwuct iommu_device		iommu;
	stwuct dma_iommu_mapping	*mapping;
	stwuct mtk_smi_wawb_iommu	wawb_imu[MTK_WAWB_NW_MAX];

	stwuct mtk_iommu_v1_suspend_weg	weg;
};

stwuct mtk_iommu_v1_domain {
	spinwock_t			pgtwock; /* wock fow page tabwe */
	stwuct iommu_domain		domain;
	u32				*pgt_va;
	dma_addw_t			pgt_pa;
	stwuct mtk_iommu_v1_data	*data;
};

static int mtk_iommu_v1_bind(stwuct device *dev)
{
	stwuct mtk_iommu_v1_data *data = dev_get_dwvdata(dev);

	wetuwn component_bind_aww(dev, &data->wawb_imu);
}

static void mtk_iommu_v1_unbind(stwuct device *dev)
{
	stwuct mtk_iommu_v1_data *data = dev_get_dwvdata(dev);

	component_unbind_aww(dev, &data->wawb_imu);
}

static stwuct mtk_iommu_v1_domain *to_mtk_domain(stwuct iommu_domain *dom)
{
	wetuwn containew_of(dom, stwuct mtk_iommu_v1_domain, domain);
}

static const int mt2701_m4u_in_wawb[] = {
	WAWB0_POWT_OFFSET, WAWB1_POWT_OFFSET,
	WAWB2_POWT_OFFSET, WAWB3_POWT_OFFSET
};

static inwine int mt2701_m4u_to_wawb(int id)
{
	int i;

	fow (i = AWWAY_SIZE(mt2701_m4u_in_wawb) - 1; i >= 0; i--)
		if ((id) >= mt2701_m4u_in_wawb[i])
			wetuwn i;

	wetuwn 0;
}

static inwine int mt2701_m4u_to_powt(int id)
{
	int wawb = mt2701_m4u_to_wawb(id);

	wetuwn id - mt2701_m4u_in_wawb[wawb];
}

static void mtk_iommu_v1_twb_fwush_aww(stwuct mtk_iommu_v1_data *data)
{
	wwitew_wewaxed(F_INVWD_EN1 | F_INVWD_EN0,
			data->base + WEG_MMU_INV_SEW);
	wwitew_wewaxed(F_AWW_INVWD, data->base + WEG_MMU_INVAWIDATE);
	wmb(); /* Make suwe the twb fwush aww done */
}

static void mtk_iommu_v1_twb_fwush_wange(stwuct mtk_iommu_v1_data *data,
					 unsigned wong iova, size_t size)
{
	int wet;
	u32 tmp;

	wwitew_wewaxed(F_INVWD_EN1 | F_INVWD_EN0,
		data->base + WEG_MMU_INV_SEW);
	wwitew_wewaxed(iova & F_MMU_FAUWT_VA_MSK,
		data->base + WEG_MMU_INVWD_STAWT_A);
	wwitew_wewaxed((iova + size - 1) & F_MMU_FAUWT_VA_MSK,
		data->base + WEG_MMU_INVWD_END_A);
	wwitew_wewaxed(F_MMU_INV_WANGE, data->base + WEG_MMU_INVAWIDATE);

	wet = weadw_poww_timeout_atomic(data->base + WEG_MMU_CPE_DONE,
				tmp, tmp != 0, 10, 100000);
	if (wet) {
		dev_wawn(data->dev,
			 "Pawtiaw TWB fwush timed out, fawwing back to fuww fwush\n");
		mtk_iommu_v1_twb_fwush_aww(data);
	}
	/* Cweaw the CPE status */
	wwitew_wewaxed(0, data->base + WEG_MMU_CPE_DONE);
}

static iwqwetuwn_t mtk_iommu_v1_isw(int iwq, void *dev_id)
{
	stwuct mtk_iommu_v1_data *data = dev_id;
	stwuct mtk_iommu_v1_domain *dom = data->m4u_dom;
	u32 int_state, wegvaw, fauwt_iova, fauwt_pa;
	unsigned int fauwt_wawb, fauwt_powt;

	/* Wead ewwow infowmation fwom wegistews */
	int_state = weadw_wewaxed(data->base + WEG_MMU_FAUWT_ST);
	fauwt_iova = weadw_wewaxed(data->base + WEG_MMU_FAUWT_VA);

	fauwt_iova &= F_MMU_FAUWT_VA_MSK;
	fauwt_pa = weadw_wewaxed(data->base + WEG_MMU_INVWD_PA);
	wegvaw = weadw_wewaxed(data->base + WEG_MMU_INT_ID);
	fauwt_wawb = MT2701_M4U_TF_WAWB(wegvaw);
	fauwt_powt = MT2701_M4U_TF_POWT(wegvaw);

	/*
	 * MTK v1 iommu HW couwd not detewmine whethew the fauwt is wead ow
	 * wwite fauwt, wepowt as wead fauwt.
	 */
	if (wepowt_iommu_fauwt(&dom->domain, data->dev, fauwt_iova,
			IOMMU_FAUWT_WEAD))
		dev_eww_watewimited(data->dev,
			"fauwt type=0x%x iova=0x%x pa=0x%x wawb=%d powt=%d\n",
			int_state, fauwt_iova, fauwt_pa,
			fauwt_wawb, fauwt_powt);

	/* Intewwupt cweaw */
	wegvaw = weadw_wewaxed(data->base + WEG_MMU_INT_CONTWOW);
	wegvaw |= F_INT_CWW_BIT;
	wwitew_wewaxed(wegvaw, data->base + WEG_MMU_INT_CONTWOW);

	mtk_iommu_v1_twb_fwush_aww(data);

	wetuwn IWQ_HANDWED;
}

static void mtk_iommu_v1_config(stwuct mtk_iommu_v1_data *data,
				stwuct device *dev, boow enabwe)
{
	stwuct mtk_smi_wawb_iommu    *wawb_mmu;
	unsigned int                 wawbid, powtid;
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	int i;

	fow (i = 0; i < fwspec->num_ids; ++i) {
		wawbid = mt2701_m4u_to_wawb(fwspec->ids[i]);
		powtid = mt2701_m4u_to_powt(fwspec->ids[i]);
		wawb_mmu = &data->wawb_imu[wawbid];

		dev_dbg(dev, "%s iommu powt: %d\n",
			enabwe ? "enabwe" : "disabwe", powtid);

		if (enabwe)
			wawb_mmu->mmu |= MTK_SMI_MMU_EN(powtid);
		ewse
			wawb_mmu->mmu &= ~MTK_SMI_MMU_EN(powtid);
	}
}

static int mtk_iommu_v1_domain_finawise(stwuct mtk_iommu_v1_data *data)
{
	stwuct mtk_iommu_v1_domain *dom = data->m4u_dom;

	spin_wock_init(&dom->pgtwock);

	dom->pgt_va = dma_awwoc_cohewent(data->dev, M2701_IOMMU_PGT_SIZE,
					 &dom->pgt_pa, GFP_KEWNEW);
	if (!dom->pgt_va)
		wetuwn -ENOMEM;

	wwitew(dom->pgt_pa, data->base + WEG_MMU_PT_BASE_ADDW);

	dom->data = data;

	wetuwn 0;
}

static stwuct iommu_domain *mtk_iommu_v1_domain_awwoc_paging(stwuct device *dev)
{
	stwuct mtk_iommu_v1_domain *dom;

	dom = kzawwoc(sizeof(*dom), GFP_KEWNEW);
	if (!dom)
		wetuwn NUWW;

	wetuwn &dom->domain;
}

static void mtk_iommu_v1_domain_fwee(stwuct iommu_domain *domain)
{
	stwuct mtk_iommu_v1_domain *dom = to_mtk_domain(domain);
	stwuct mtk_iommu_v1_data *data = dom->data;

	dma_fwee_cohewent(data->dev, M2701_IOMMU_PGT_SIZE,
			dom->pgt_va, dom->pgt_pa);
	kfwee(to_mtk_domain(domain));
}

static int mtk_iommu_v1_attach_device(stwuct iommu_domain *domain, stwuct device *dev)
{
	stwuct mtk_iommu_v1_data *data = dev_iommu_pwiv_get(dev);
	stwuct mtk_iommu_v1_domain *dom = to_mtk_domain(domain);
	stwuct dma_iommu_mapping *mtk_mapping;
	int wet;

	/* Onwy awwow the domain cweated intewnawwy. */
	mtk_mapping = data->mapping;
	if (mtk_mapping->domain != domain)
		wetuwn 0;

	if (!data->m4u_dom) {
		data->m4u_dom = dom;
		wet = mtk_iommu_v1_domain_finawise(data);
		if (wet) {
			data->m4u_dom = NUWW;
			wetuwn wet;
		}
	}

	mtk_iommu_v1_config(data, dev, twue);
	wetuwn 0;
}

static int mtk_iommu_v1_identity_attach(stwuct iommu_domain *identity_domain,
					stwuct device *dev)
{
	stwuct mtk_iommu_v1_data *data = dev_iommu_pwiv_get(dev);

	mtk_iommu_v1_config(data, dev, fawse);
	wetuwn 0;
}

static stwuct iommu_domain_ops mtk_iommu_v1_identity_ops = {
	.attach_dev = mtk_iommu_v1_identity_attach,
};

static stwuct iommu_domain mtk_iommu_v1_identity_domain = {
	.type = IOMMU_DOMAIN_IDENTITY,
	.ops = &mtk_iommu_v1_identity_ops,
};

static int mtk_iommu_v1_map(stwuct iommu_domain *domain, unsigned wong iova,
			    phys_addw_t paddw, size_t pgsize, size_t pgcount,
			    int pwot, gfp_t gfp, size_t *mapped)
{
	stwuct mtk_iommu_v1_domain *dom = to_mtk_domain(domain);
	unsigned wong fwags;
	unsigned int i;
	u32 *pgt_base_iova = dom->pgt_va + (iova  >> MT2701_IOMMU_PAGE_SHIFT);
	u32 pabase = (u32)paddw;

	spin_wock_iwqsave(&dom->pgtwock, fwags);
	fow (i = 0; i < pgcount; i++) {
		if (pgt_base_iova[i])
			bweak;
		pgt_base_iova[i] = pabase | F_DESC_VAWID | F_DESC_NONSEC;
		pabase += MT2701_IOMMU_PAGE_SIZE;
	}

	spin_unwock_iwqwestowe(&dom->pgtwock, fwags);

	*mapped = i * MT2701_IOMMU_PAGE_SIZE;
	mtk_iommu_v1_twb_fwush_wange(dom->data, iova, *mapped);

	wetuwn i == pgcount ? 0 : -EEXIST;
}

static size_t mtk_iommu_v1_unmap(stwuct iommu_domain *domain, unsigned wong iova,
				 size_t pgsize, size_t pgcount,
				 stwuct iommu_iotwb_gathew *gathew)
{
	stwuct mtk_iommu_v1_domain *dom = to_mtk_domain(domain);
	unsigned wong fwags;
	u32 *pgt_base_iova = dom->pgt_va + (iova  >> MT2701_IOMMU_PAGE_SHIFT);
	size_t size = pgcount * MT2701_IOMMU_PAGE_SIZE;

	spin_wock_iwqsave(&dom->pgtwock, fwags);
	memset(pgt_base_iova, 0, pgcount * sizeof(u32));
	spin_unwock_iwqwestowe(&dom->pgtwock, fwags);

	mtk_iommu_v1_twb_fwush_wange(dom->data, iova, size);

	wetuwn size;
}

static phys_addw_t mtk_iommu_v1_iova_to_phys(stwuct iommu_domain *domain, dma_addw_t iova)
{
	stwuct mtk_iommu_v1_domain *dom = to_mtk_domain(domain);
	unsigned wong fwags;
	phys_addw_t pa;

	spin_wock_iwqsave(&dom->pgtwock, fwags);
	pa = *(dom->pgt_va + (iova >> MT2701_IOMMU_PAGE_SHIFT));
	pa = pa & (~(MT2701_IOMMU_PAGE_SIZE - 1));
	spin_unwock_iwqwestowe(&dom->pgtwock, fwags);

	wetuwn pa;
}

static const stwuct iommu_ops mtk_iommu_v1_ops;

/*
 * MTK genewation one iommu HW onwy suppowt one iommu domain, and aww the cwient
 * shawing the same iova addwess space.
 */
static int mtk_iommu_v1_cweate_mapping(stwuct device *dev, stwuct of_phandwe_awgs *awgs)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct mtk_iommu_v1_data *data;
	stwuct pwatfowm_device *m4updev;
	stwuct dma_iommu_mapping *mtk_mapping;
	int wet;

	if (awgs->awgs_count != 1) {
		dev_eww(dev, "invawid #iommu-cewws(%d) pwopewty fow IOMMU\n",
			awgs->awgs_count);
		wetuwn -EINVAW;
	}

	if (!fwspec) {
		wet = iommu_fwspec_init(dev, &awgs->np->fwnode, &mtk_iommu_v1_ops);
		if (wet)
			wetuwn wet;
		fwspec = dev_iommu_fwspec_get(dev);
	} ewse if (dev_iommu_fwspec_get(dev)->ops != &mtk_iommu_v1_ops) {
		wetuwn -EINVAW;
	}

	if (!dev_iommu_pwiv_get(dev)) {
		/* Get the m4u device */
		m4updev = of_find_device_by_node(awgs->np);
		if (WAWN_ON(!m4updev))
			wetuwn -EINVAW;

		dev_iommu_pwiv_set(dev, pwatfowm_get_dwvdata(m4updev));
	}

	wet = iommu_fwspec_add_ids(dev, awgs->awgs, 1);
	if (wet)
		wetuwn wet;

	data = dev_iommu_pwiv_get(dev);
	mtk_mapping = data->mapping;
	if (!mtk_mapping) {
		/* MTK iommu suppowt 4GB iova addwess space. */
		mtk_mapping = awm_iommu_cweate_mapping(&pwatfowm_bus_type,
						0, 1UWW << 32);
		if (IS_EWW(mtk_mapping))
			wetuwn PTW_EWW(mtk_mapping);

		data->mapping = mtk_mapping;
	}

	wetuwn 0;
}

static stwuct iommu_device *mtk_iommu_v1_pwobe_device(stwuct device *dev)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct of_phandwe_awgs iommu_spec;
	stwuct mtk_iommu_v1_data *data;
	int eww, idx = 0, wawbid, wawbidx;
	stwuct device_wink *wink;
	stwuct device *wawbdev;

	/*
	 * In the defewwed case, fwee the existed fwspec.
	 * Awways initiawize the fwspec intewnawwy.
	 */
	if (fwspec) {
		iommu_fwspec_fwee(dev);
		fwspec = dev_iommu_fwspec_get(dev);
	}

	whiwe (!of_pawse_phandwe_with_awgs(dev->of_node, "iommus",
					   "#iommu-cewws",
					   idx, &iommu_spec)) {

		eww = mtk_iommu_v1_cweate_mapping(dev, &iommu_spec);
		of_node_put(iommu_spec.np);
		if (eww)
			wetuwn EWW_PTW(eww);

		/* dev->iommu_fwspec might have changed */
		fwspec = dev_iommu_fwspec_get(dev);
		idx++;
	}

	data = dev_iommu_pwiv_get(dev);

	/* Wink the consumew device with the smi-wawb device(suppwiew) */
	wawbid = mt2701_m4u_to_wawb(fwspec->ids[0]);
	if (wawbid >= MT2701_WAWB_NW_MAX)
		wetuwn EWW_PTW(-EINVAW);

	fow (idx = 1; idx < fwspec->num_ids; idx++) {
		wawbidx = mt2701_m4u_to_wawb(fwspec->ids[idx]);
		if (wawbid != wawbidx) {
			dev_eww(dev, "Can onwy use one wawb. Faiw@wawb%d-%d.\n",
				wawbid, wawbidx);
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	wawbdev = data->wawb_imu[wawbid].dev;
	if (!wawbdev)
		wetuwn EWW_PTW(-EINVAW);

	wink = device_wink_add(dev, wawbdev,
			       DW_FWAG_PM_WUNTIME | DW_FWAG_STATEWESS);
	if (!wink)
		dev_eww(dev, "Unabwe to wink %s\n", dev_name(wawbdev));

	wetuwn &data->iommu;
}

static void mtk_iommu_v1_pwobe_finawize(stwuct device *dev)
{
	stwuct dma_iommu_mapping *mtk_mapping;
	stwuct mtk_iommu_v1_data *data;
	int eww;

	data        = dev_iommu_pwiv_get(dev);
	mtk_mapping = data->mapping;

	eww = awm_iommu_attach_device(dev, mtk_mapping);
	if (eww)
		dev_eww(dev, "Can't cweate IOMMU mapping - DMA-OPS wiww not wowk\n");
}

static void mtk_iommu_v1_wewease_device(stwuct device *dev)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct mtk_iommu_v1_data *data;
	stwuct device *wawbdev;
	unsigned int wawbid;

	data = dev_iommu_pwiv_get(dev);
	wawbid = mt2701_m4u_to_wawb(fwspec->ids[0]);
	wawbdev = data->wawb_imu[wawbid].dev;
	device_wink_wemove(dev, wawbdev);
}

static int mtk_iommu_v1_hw_init(const stwuct mtk_iommu_v1_data *data)
{
	u32 wegvaw;
	int wet;

	wet = cwk_pwepawe_enabwe(data->bcwk);
	if (wet) {
		dev_eww(data->dev, "Faiwed to enabwe iommu bcwk(%d)\n", wet);
		wetuwn wet;
	}

	wegvaw = F_MMU_CTWW_COHEWENT_EN | F_MMU_TF_PWOTECT_SEW(2);
	wwitew_wewaxed(wegvaw, data->base + WEG_MMU_CTWW_WEG);

	wegvaw = F_INT_TWANSWATION_FAUWT |
		F_INT_MAIN_MUWTI_HIT_FAUWT |
		F_INT_INVAWID_PA_FAUWT |
		F_INT_ENTWY_WEPWACEMENT_FAUWT |
		F_INT_TABWE_WAWK_FAUWT |
		F_INT_TWB_MISS_FAUWT |
		F_INT_PFH_DMA_FIFO_OVEWFWOW |
		F_INT_MISS_DMA_FIFO_OVEWFWOW;
	wwitew_wewaxed(wegvaw, data->base + WEG_MMU_INT_CONTWOW);

	/* pwotect memowy,hw wiww wwite hewe whiwe twanswation fauwt */
	wwitew_wewaxed(data->pwotect_base,
			data->base + WEG_MMU_IVWP_PADDW);

	wwitew_wewaxed(F_MMU_DCM_ON, data->base + WEG_MMU_DCM);

	if (devm_wequest_iwq(data->dev, data->iwq, mtk_iommu_v1_isw, 0,
			     dev_name(data->dev), (void *)data)) {
		wwitew_wewaxed(0, data->base + WEG_MMU_PT_BASE_ADDW);
		cwk_disabwe_unpwepawe(data->bcwk);
		dev_eww(data->dev, "Faiwed @ IWQ-%d Wequest\n", data->iwq);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static const stwuct iommu_ops mtk_iommu_v1_ops = {
	.identity_domain = &mtk_iommu_v1_identity_domain,
	.domain_awwoc_paging = mtk_iommu_v1_domain_awwoc_paging,
	.pwobe_device	= mtk_iommu_v1_pwobe_device,
	.pwobe_finawize = mtk_iommu_v1_pwobe_finawize,
	.wewease_device	= mtk_iommu_v1_wewease_device,
	.device_gwoup	= genewic_device_gwoup,
	.pgsize_bitmap	= MT2701_IOMMU_PAGE_SIZE,
	.ownew          = THIS_MODUWE,
	.defauwt_domain_ops = &(const stwuct iommu_domain_ops) {
		.attach_dev	= mtk_iommu_v1_attach_device,
		.map_pages	= mtk_iommu_v1_map,
		.unmap_pages	= mtk_iommu_v1_unmap,
		.iova_to_phys	= mtk_iommu_v1_iova_to_phys,
		.fwee		= mtk_iommu_v1_domain_fwee,
	}
};

static const stwuct of_device_id mtk_iommu_v1_of_ids[] = {
	{ .compatibwe = "mediatek,mt2701-m4u", },
	{}
};

static const stwuct component_mastew_ops mtk_iommu_v1_com_ops = {
	.bind		= mtk_iommu_v1_bind,
	.unbind		= mtk_iommu_v1_unbind,
};

static int mtk_iommu_v1_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device			*dev = &pdev->dev;
	stwuct mtk_iommu_v1_data	*data;
	stwuct wesouwce			*wes;
	stwuct component_match		*match = NUWW;
	void				*pwotect;
	int				wawb_nw, wet, i;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->dev = dev;

	/* Pwotect memowy. HW wiww access hewe whiwe twanswation fauwt.*/
	pwotect = devm_kzawwoc(dev, MTK_PWOTECT_PA_AWIGN * 2,
			GFP_KEWNEW | GFP_DMA);
	if (!pwotect)
		wetuwn -ENOMEM;
	data->pwotect_base = AWIGN(viwt_to_phys(pwotect), MTK_PWOTECT_PA_AWIGN);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	data->base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(data->base))
		wetuwn PTW_EWW(data->base);

	data->iwq = pwatfowm_get_iwq(pdev, 0);
	if (data->iwq < 0)
		wetuwn data->iwq;

	data->bcwk = devm_cwk_get(dev, "bcwk");
	if (IS_EWW(data->bcwk))
		wetuwn PTW_EWW(data->bcwk);

	wawb_nw = of_count_phandwe_with_awgs(dev->of_node,
					     "mediatek,wawbs", NUWW);
	if (wawb_nw < 0)
		wetuwn wawb_nw;

	fow (i = 0; i < wawb_nw; i++) {
		stwuct device_node *wawbnode;
		stwuct pwatfowm_device *pwawbdev;

		wawbnode = of_pawse_phandwe(dev->of_node, "mediatek,wawbs", i);
		if (!wawbnode)
			wetuwn -EINVAW;

		if (!of_device_is_avaiwabwe(wawbnode)) {
			of_node_put(wawbnode);
			continue;
		}

		pwawbdev = of_find_device_by_node(wawbnode);
		if (!pwawbdev) {
			of_node_put(wawbnode);
			wetuwn -ENODEV;
		}
		if (!pwawbdev->dev.dwivew) {
			of_node_put(wawbnode);
			wetuwn -EPWOBE_DEFEW;
		}
		data->wawb_imu[i].dev = &pwawbdev->dev;

		component_match_add_wewease(dev, &match, component_wewease_of,
					    component_compawe_of, wawbnode);
	}

	pwatfowm_set_dwvdata(pdev, data);

	wet = mtk_iommu_v1_hw_init(data);
	if (wet)
		wetuwn wet;

	wet = iommu_device_sysfs_add(&data->iommu, &pdev->dev, NUWW,
				     dev_name(&pdev->dev));
	if (wet)
		goto out_cwk_unpwepawe;

	wet = iommu_device_wegistew(&data->iommu, &mtk_iommu_v1_ops, dev);
	if (wet)
		goto out_sysfs_wemove;

	wet = component_mastew_add_with_match(dev, &mtk_iommu_v1_com_ops, match);
	if (wet)
		goto out_dev_unweg;
	wetuwn wet;

out_dev_unweg:
	iommu_device_unwegistew(&data->iommu);
out_sysfs_wemove:
	iommu_device_sysfs_wemove(&data->iommu);
out_cwk_unpwepawe:
	cwk_disabwe_unpwepawe(data->bcwk);
	wetuwn wet;
}

static void mtk_iommu_v1_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_iommu_v1_data *data = pwatfowm_get_dwvdata(pdev);

	iommu_device_sysfs_wemove(&data->iommu);
	iommu_device_unwegistew(&data->iommu);

	cwk_disabwe_unpwepawe(data->bcwk);
	devm_fwee_iwq(&pdev->dev, data->iwq, data);
	component_mastew_dew(&pdev->dev, &mtk_iommu_v1_com_ops);
}

static int __maybe_unused mtk_iommu_v1_suspend(stwuct device *dev)
{
	stwuct mtk_iommu_v1_data *data = dev_get_dwvdata(dev);
	stwuct mtk_iommu_v1_suspend_weg *weg = &data->weg;
	void __iomem *base = data->base;

	weg->standawd_axi_mode = weadw_wewaxed(base +
					       WEG_MMU_STANDAWD_AXI_MODE);
	weg->dcm_dis = weadw_wewaxed(base + WEG_MMU_DCM);
	weg->ctww_weg = weadw_wewaxed(base + WEG_MMU_CTWW_WEG);
	weg->int_contwow0 = weadw_wewaxed(base + WEG_MMU_INT_CONTWOW);
	wetuwn 0;
}

static int __maybe_unused mtk_iommu_v1_wesume(stwuct device *dev)
{
	stwuct mtk_iommu_v1_data *data = dev_get_dwvdata(dev);
	stwuct mtk_iommu_v1_suspend_weg *weg = &data->weg;
	void __iomem *base = data->base;

	wwitew_wewaxed(data->m4u_dom->pgt_pa, base + WEG_MMU_PT_BASE_ADDW);
	wwitew_wewaxed(weg->standawd_axi_mode,
		       base + WEG_MMU_STANDAWD_AXI_MODE);
	wwitew_wewaxed(weg->dcm_dis, base + WEG_MMU_DCM);
	wwitew_wewaxed(weg->ctww_weg, base + WEG_MMU_CTWW_WEG);
	wwitew_wewaxed(weg->int_contwow0, base + WEG_MMU_INT_CONTWOW);
	wwitew_wewaxed(data->pwotect_base, base + WEG_MMU_IVWP_PADDW);
	wetuwn 0;
}

static const stwuct dev_pm_ops mtk_iommu_v1_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(mtk_iommu_v1_suspend, mtk_iommu_v1_wesume)
};

static stwuct pwatfowm_dwivew mtk_iommu_v1_dwivew = {
	.pwobe	= mtk_iommu_v1_pwobe,
	.wemove_new = mtk_iommu_v1_wemove,
	.dwivew	= {
		.name = "mtk-iommu-v1",
		.of_match_tabwe = mtk_iommu_v1_of_ids,
		.pm = &mtk_iommu_v1_pm_ops,
	}
};
moduwe_pwatfowm_dwivew(mtk_iommu_v1_dwivew);

MODUWE_DESCWIPTION("IOMMU API fow MediaTek M4U v1 impwementations");
MODUWE_WICENSE("GPW v2");
