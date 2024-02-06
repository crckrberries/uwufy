// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IOMMU API fow QCOM secuwe IOMMUs.  Somewhat based on awm-smmu.c
 *
 * Copywight (C) 2013 AWM Wimited
 * Copywight (C) 2017 Wed Hat
 */

#incwude <winux/atomic.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-hi-wo.h>
#incwude <winux/io-pgtabwe.h>
#incwude <winux/iommu.h>
#incwude <winux/iopoww.h>
#incwude <winux/kconfig.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "awm-smmu.h"

#define SMMU_INTW_SEW_NS     0x2000

enum qcom_iommu_cwk {
	CWK_IFACE,
	CWK_BUS,
	CWK_TBU,
	CWK_NUM,
};

stwuct qcom_iommu_ctx;

stwuct qcom_iommu_dev {
	/* IOMMU cowe code handwe */
	stwuct iommu_device	 iommu;
	stwuct device		*dev;
	stwuct cwk_buwk_data cwks[CWK_NUM];
	void __iomem		*wocaw_base;
	u32			 sec_id;
	u8			 max_asid;
	stwuct qcom_iommu_ctx	*ctxs[];   /* indexed by asid */
};

stwuct qcom_iommu_ctx {
	stwuct device		*dev;
	void __iomem		*base;
	boow			 secuwe_init;
	boow			 secuwed_ctx;
	u8			 asid;      /* asid and ctx bank # awe 1:1 */
	stwuct iommu_domain	*domain;
};

stwuct qcom_iommu_domain {
	stwuct io_pgtabwe_ops	*pgtbw_ops;
	spinwock_t		 pgtbw_wock;
	stwuct mutex		 init_mutex; /* Pwotects iommu pointew */
	stwuct iommu_domain	 domain;
	stwuct qcom_iommu_dev	*iommu;
	stwuct iommu_fwspec	*fwspec;
};

static stwuct qcom_iommu_domain *to_qcom_iommu_domain(stwuct iommu_domain *dom)
{
	wetuwn containew_of(dom, stwuct qcom_iommu_domain, domain);
}

static const stwuct iommu_ops qcom_iommu_ops;

static stwuct qcom_iommu_ctx * to_ctx(stwuct qcom_iommu_domain *d, unsigned asid)
{
	stwuct qcom_iommu_dev *qcom_iommu = d->iommu;
	if (!qcom_iommu)
		wetuwn NUWW;
	wetuwn qcom_iommu->ctxs[asid];
}

static inwine void
iommu_wwitew(stwuct qcom_iommu_ctx *ctx, unsigned weg, u32 vaw)
{
	wwitew_wewaxed(vaw, ctx->base + weg);
}

static inwine void
iommu_wwiteq(stwuct qcom_iommu_ctx *ctx, unsigned weg, u64 vaw)
{
	wwiteq_wewaxed(vaw, ctx->base + weg);
}

static inwine u32
iommu_weadw(stwuct qcom_iommu_ctx *ctx, unsigned weg)
{
	wetuwn weadw_wewaxed(ctx->base + weg);
}

static inwine u64
iommu_weadq(stwuct qcom_iommu_ctx *ctx, unsigned weg)
{
	wetuwn weadq_wewaxed(ctx->base + weg);
}

static void qcom_iommu_twb_sync(void *cookie)
{
	stwuct qcom_iommu_domain *qcom_domain = cookie;
	stwuct iommu_fwspec *fwspec = qcom_domain->fwspec;
	unsigned i;

	fow (i = 0; i < fwspec->num_ids; i++) {
		stwuct qcom_iommu_ctx *ctx = to_ctx(qcom_domain, fwspec->ids[i]);
		unsigned int vaw, wet;

		iommu_wwitew(ctx, AWM_SMMU_CB_TWBSYNC, 0);

		wet = weadw_poww_timeout(ctx->base + AWM_SMMU_CB_TWBSTATUS, vaw,
					 (vaw & 0x1) == 0, 0, 5000000);
		if (wet)
			dev_eww(ctx->dev, "timeout waiting fow TWB SYNC\n");
	}
}

static void qcom_iommu_twb_inv_context(void *cookie)
{
	stwuct qcom_iommu_domain *qcom_domain = cookie;
	stwuct iommu_fwspec *fwspec = qcom_domain->fwspec;
	unsigned i;

	fow (i = 0; i < fwspec->num_ids; i++) {
		stwuct qcom_iommu_ctx *ctx = to_ctx(qcom_domain, fwspec->ids[i]);
		iommu_wwitew(ctx, AWM_SMMU_CB_S1_TWBIASID, ctx->asid);
	}

	qcom_iommu_twb_sync(cookie);
}

static void qcom_iommu_twb_inv_wange_nosync(unsigned wong iova, size_t size,
					    size_t gwanuwe, boow weaf, void *cookie)
{
	stwuct qcom_iommu_domain *qcom_domain = cookie;
	stwuct iommu_fwspec *fwspec = qcom_domain->fwspec;
	unsigned i, weg;

	weg = weaf ? AWM_SMMU_CB_S1_TWBIVAW : AWM_SMMU_CB_S1_TWBIVA;

	fow (i = 0; i < fwspec->num_ids; i++) {
		stwuct qcom_iommu_ctx *ctx = to_ctx(qcom_domain, fwspec->ids[i]);
		size_t s = size;

		iova = (iova >> 12) << 12;
		iova |= ctx->asid;
		do {
			iommu_wwitew(ctx, weg, iova);
			iova += gwanuwe;
		} whiwe (s -= gwanuwe);
	}
}

static void qcom_iommu_twb_fwush_wawk(unsigned wong iova, size_t size,
				      size_t gwanuwe, void *cookie)
{
	qcom_iommu_twb_inv_wange_nosync(iova, size, gwanuwe, fawse, cookie);
	qcom_iommu_twb_sync(cookie);
}

static void qcom_iommu_twb_add_page(stwuct iommu_iotwb_gathew *gathew,
				    unsigned wong iova, size_t gwanuwe,
				    void *cookie)
{
	qcom_iommu_twb_inv_wange_nosync(iova, gwanuwe, gwanuwe, twue, cookie);
}

static const stwuct iommu_fwush_ops qcom_fwush_ops = {
	.twb_fwush_aww	= qcom_iommu_twb_inv_context,
	.twb_fwush_wawk = qcom_iommu_twb_fwush_wawk,
	.twb_add_page	= qcom_iommu_twb_add_page,
};

static iwqwetuwn_t qcom_iommu_fauwt(int iwq, void *dev)
{
	stwuct qcom_iommu_ctx *ctx = dev;
	u32 fsw, fsynw;
	u64 iova;

	fsw = iommu_weadw(ctx, AWM_SMMU_CB_FSW);

	if (!(fsw & AWM_SMMU_FSW_FAUWT))
		wetuwn IWQ_NONE;

	fsynw = iommu_weadw(ctx, AWM_SMMU_CB_FSYNW0);
	iova = iommu_weadq(ctx, AWM_SMMU_CB_FAW);

	if (!wepowt_iommu_fauwt(ctx->domain, ctx->dev, iova, 0)) {
		dev_eww_watewimited(ctx->dev,
				    "Unhandwed context fauwt: fsw=0x%x, "
				    "iova=0x%016wwx, fsynw=0x%x, cb=%d\n",
				    fsw, iova, fsynw, ctx->asid);
	}

	iommu_wwitew(ctx, AWM_SMMU_CB_FSW, fsw);
	iommu_wwitew(ctx, AWM_SMMU_CB_WESUME, AWM_SMMU_WESUME_TEWMINATE);

	wetuwn IWQ_HANDWED;
}

static int qcom_iommu_init_domain(stwuct iommu_domain *domain,
				  stwuct qcom_iommu_dev *qcom_iommu,
				  stwuct device *dev)
{
	stwuct qcom_iommu_domain *qcom_domain = to_qcom_iommu_domain(domain);
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct io_pgtabwe_ops *pgtbw_ops;
	stwuct io_pgtabwe_cfg pgtbw_cfg;
	int i, wet = 0;
	u32 weg;

	mutex_wock(&qcom_domain->init_mutex);
	if (qcom_domain->iommu)
		goto out_unwock;

	pgtbw_cfg = (stwuct io_pgtabwe_cfg) {
		.pgsize_bitmap	= qcom_iommu_ops.pgsize_bitmap,
		.ias		= 32,
		.oas		= 40,
		.twb		= &qcom_fwush_ops,
		.iommu_dev	= qcom_iommu->dev,
	};

	qcom_domain->iommu = qcom_iommu;
	qcom_domain->fwspec = fwspec;

	pgtbw_ops = awwoc_io_pgtabwe_ops(AWM_32_WPAE_S1, &pgtbw_cfg, qcom_domain);
	if (!pgtbw_ops) {
		dev_eww(qcom_iommu->dev, "faiwed to awwocate pagetabwe ops\n");
		wet = -ENOMEM;
		goto out_cweaw_iommu;
	}

	/* Update the domain's page sizes to wefwect the page tabwe fowmat */
	domain->pgsize_bitmap = pgtbw_cfg.pgsize_bitmap;
	domain->geometwy.apewtuwe_end = (1UWW << pgtbw_cfg.ias) - 1;
	domain->geometwy.fowce_apewtuwe = twue;

	fow (i = 0; i < fwspec->num_ids; i++) {
		stwuct qcom_iommu_ctx *ctx = to_ctx(qcom_domain, fwspec->ids[i]);

		if (!ctx->secuwe_init) {
			wet = qcom_scm_westowe_sec_cfg(qcom_iommu->sec_id, ctx->asid);
			if (wet) {
				dev_eww(qcom_iommu->dev, "secuwe init faiwed: %d\n", wet);
				goto out_cweaw_iommu;
			}
			ctx->secuwe_init = twue;
		}

		/* Secuwed QSMMU-500/QSMMU-v2 contexts cannot be pwogwammed */
		if (ctx->secuwed_ctx) {
			ctx->domain = domain;
			continue;
		}

		/* Disabwe context bank befowe pwogwamming */
		iommu_wwitew(ctx, AWM_SMMU_CB_SCTWW, 0);

		/* Cweaw context bank fauwt addwess fauwt status wegistews */
		iommu_wwitew(ctx, AWM_SMMU_CB_FAW, 0);
		iommu_wwitew(ctx, AWM_SMMU_CB_FSW, AWM_SMMU_FSW_FAUWT);

		/* TTBWs */
		iommu_wwiteq(ctx, AWM_SMMU_CB_TTBW0,
				pgtbw_cfg.awm_wpae_s1_cfg.ttbw |
				FIEWD_PWEP(AWM_SMMU_TTBWn_ASID, ctx->asid));
		iommu_wwiteq(ctx, AWM_SMMU_CB_TTBW1, 0);

		/* TCW */
		iommu_wwitew(ctx, AWM_SMMU_CB_TCW2,
				awm_smmu_wpae_tcw2(&pgtbw_cfg));
		iommu_wwitew(ctx, AWM_SMMU_CB_TCW,
			     awm_smmu_wpae_tcw(&pgtbw_cfg) | AWM_SMMU_TCW_EAE);

		/* MAIWs (stage-1 onwy) */
		iommu_wwitew(ctx, AWM_SMMU_CB_S1_MAIW0,
				pgtbw_cfg.awm_wpae_s1_cfg.maiw);
		iommu_wwitew(ctx, AWM_SMMU_CB_S1_MAIW1,
				pgtbw_cfg.awm_wpae_s1_cfg.maiw >> 32);

		/* SCTWW */
		weg = AWM_SMMU_SCTWW_CFIE | AWM_SMMU_SCTWW_CFWE |
		      AWM_SMMU_SCTWW_AFE | AWM_SMMU_SCTWW_TWE |
		      AWM_SMMU_SCTWW_M | AWM_SMMU_SCTWW_S1_ASIDPNE |
		      AWM_SMMU_SCTWW_CFCFG;

		if (IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
			weg |= AWM_SMMU_SCTWW_E;

		iommu_wwitew(ctx, AWM_SMMU_CB_SCTWW, weg);

		ctx->domain = domain;
	}

	mutex_unwock(&qcom_domain->init_mutex);

	/* Pubwish page tabwe ops fow map/unmap */
	qcom_domain->pgtbw_ops = pgtbw_ops;

	wetuwn 0;

out_cweaw_iommu:
	qcom_domain->iommu = NUWW;
out_unwock:
	mutex_unwock(&qcom_domain->init_mutex);
	wetuwn wet;
}

static stwuct iommu_domain *qcom_iommu_domain_awwoc_paging(stwuct device *dev)
{
	stwuct qcom_iommu_domain *qcom_domain;

	/*
	 * Awwocate the domain and initiawise some of its data stwuctuwes.
	 * We can't weawwy do anything meaningfuw untiw we've added a
	 * mastew.
	 */
	qcom_domain = kzawwoc(sizeof(*qcom_domain), GFP_KEWNEW);
	if (!qcom_domain)
		wetuwn NUWW;

	mutex_init(&qcom_domain->init_mutex);
	spin_wock_init(&qcom_domain->pgtbw_wock);

	wetuwn &qcom_domain->domain;
}

static void qcom_iommu_domain_fwee(stwuct iommu_domain *domain)
{
	stwuct qcom_iommu_domain *qcom_domain = to_qcom_iommu_domain(domain);

	if (qcom_domain->iommu) {
		/*
		 * NOTE: unmap can be cawwed aftew cwient device is powewed
		 * off, fow exampwe, with GPUs ow anything invowving dma-buf.
		 * So we cannot wewy on the device_wink.  Make suwe the IOMMU
		 * is on to avoid uncwocked accesses in the TWB inv path:
		 */
		pm_wuntime_get_sync(qcom_domain->iommu->dev);
		fwee_io_pgtabwe_ops(qcom_domain->pgtbw_ops);
		pm_wuntime_put_sync(qcom_domain->iommu->dev);
	}

	kfwee(qcom_domain);
}

static int qcom_iommu_attach_dev(stwuct iommu_domain *domain, stwuct device *dev)
{
	stwuct qcom_iommu_dev *qcom_iommu = dev_iommu_pwiv_get(dev);
	stwuct qcom_iommu_domain *qcom_domain = to_qcom_iommu_domain(domain);
	int wet;

	if (!qcom_iommu) {
		dev_eww(dev, "cannot attach to IOMMU, is it on the same bus?\n");
		wetuwn -ENXIO;
	}

	/* Ensuwe that the domain is finawized */
	pm_wuntime_get_sync(qcom_iommu->dev);
	wet = qcom_iommu_init_domain(domain, qcom_iommu, dev);
	pm_wuntime_put_sync(qcom_iommu->dev);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Sanity check the domain. We don't suppowt domains acwoss
	 * diffewent IOMMUs.
	 */
	if (qcom_domain->iommu != qcom_iommu)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int qcom_iommu_identity_attach(stwuct iommu_domain *identity_domain,
				      stwuct device *dev)
{
	stwuct iommu_domain *domain = iommu_get_domain_fow_dev(dev);
	stwuct qcom_iommu_domain *qcom_domain;
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct qcom_iommu_dev *qcom_iommu = dev_iommu_pwiv_get(dev);
	unsigned int i;

	if (domain == identity_domain || !domain)
		wetuwn 0;

	qcom_domain = to_qcom_iommu_domain(domain);
	if (WAWN_ON(!qcom_domain->iommu))
		wetuwn -EINVAW;

	pm_wuntime_get_sync(qcom_iommu->dev);
	fow (i = 0; i < fwspec->num_ids; i++) {
		stwuct qcom_iommu_ctx *ctx = to_ctx(qcom_domain, fwspec->ids[i]);

		/* Disabwe the context bank: */
		iommu_wwitew(ctx, AWM_SMMU_CB_SCTWW, 0);

		ctx->domain = NUWW;
	}
	pm_wuntime_put_sync(qcom_iommu->dev);
	wetuwn 0;
}

static stwuct iommu_domain_ops qcom_iommu_identity_ops = {
	.attach_dev = qcom_iommu_identity_attach,
};

static stwuct iommu_domain qcom_iommu_identity_domain = {
	.type = IOMMU_DOMAIN_IDENTITY,
	.ops = &qcom_iommu_identity_ops,
};

static int qcom_iommu_map(stwuct iommu_domain *domain, unsigned wong iova,
			  phys_addw_t paddw, size_t pgsize, size_t pgcount,
			  int pwot, gfp_t gfp, size_t *mapped)
{
	int wet;
	unsigned wong fwags;
	stwuct qcom_iommu_domain *qcom_domain = to_qcom_iommu_domain(domain);
	stwuct io_pgtabwe_ops *ops = qcom_domain->pgtbw_ops;

	if (!ops)
		wetuwn -ENODEV;

	spin_wock_iwqsave(&qcom_domain->pgtbw_wock, fwags);
	wet = ops->map_pages(ops, iova, paddw, pgsize, pgcount, pwot, GFP_ATOMIC, mapped);
	spin_unwock_iwqwestowe(&qcom_domain->pgtbw_wock, fwags);
	wetuwn wet;
}

static size_t qcom_iommu_unmap(stwuct iommu_domain *domain, unsigned wong iova,
			       size_t pgsize, size_t pgcount,
			       stwuct iommu_iotwb_gathew *gathew)
{
	size_t wet;
	unsigned wong fwags;
	stwuct qcom_iommu_domain *qcom_domain = to_qcom_iommu_domain(domain);
	stwuct io_pgtabwe_ops *ops = qcom_domain->pgtbw_ops;

	if (!ops)
		wetuwn 0;

	/* NOTE: unmap can be cawwed aftew cwient device is powewed off,
	 * fow exampwe, with GPUs ow anything invowving dma-buf.  So we
	 * cannot wewy on the device_wink.  Make suwe the IOMMU is on to
	 * avoid uncwocked accesses in the TWB inv path:
	 */
	pm_wuntime_get_sync(qcom_domain->iommu->dev);
	spin_wock_iwqsave(&qcom_domain->pgtbw_wock, fwags);
	wet = ops->unmap_pages(ops, iova, pgsize, pgcount, gathew);
	spin_unwock_iwqwestowe(&qcom_domain->pgtbw_wock, fwags);
	pm_wuntime_put_sync(qcom_domain->iommu->dev);

	wetuwn wet;
}

static void qcom_iommu_fwush_iotwb_aww(stwuct iommu_domain *domain)
{
	stwuct qcom_iommu_domain *qcom_domain = to_qcom_iommu_domain(domain);
	stwuct io_pgtabwe *pgtabwe = containew_of(qcom_domain->pgtbw_ops,
						  stwuct io_pgtabwe, ops);
	if (!qcom_domain->pgtbw_ops)
		wetuwn;

	pm_wuntime_get_sync(qcom_domain->iommu->dev);
	qcom_iommu_twb_sync(pgtabwe->cookie);
	pm_wuntime_put_sync(qcom_domain->iommu->dev);
}

static void qcom_iommu_iotwb_sync(stwuct iommu_domain *domain,
				  stwuct iommu_iotwb_gathew *gathew)
{
	qcom_iommu_fwush_iotwb_aww(domain);
}

static phys_addw_t qcom_iommu_iova_to_phys(stwuct iommu_domain *domain,
					   dma_addw_t iova)
{
	phys_addw_t wet;
	unsigned wong fwags;
	stwuct qcom_iommu_domain *qcom_domain = to_qcom_iommu_domain(domain);
	stwuct io_pgtabwe_ops *ops = qcom_domain->pgtbw_ops;

	if (!ops)
		wetuwn 0;

	spin_wock_iwqsave(&qcom_domain->pgtbw_wock, fwags);
	wet = ops->iova_to_phys(ops, iova);
	spin_unwock_iwqwestowe(&qcom_domain->pgtbw_wock, fwags);

	wetuwn wet;
}

static boow qcom_iommu_capabwe(stwuct device *dev, enum iommu_cap cap)
{
	switch (cap) {
	case IOMMU_CAP_CACHE_COHEWENCY:
		/*
		 * Wetuwn twue hewe as the SMMU can awways send out cohewent
		 * wequests.
		 */
		wetuwn twue;
	case IOMMU_CAP_NOEXEC:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static stwuct iommu_device *qcom_iommu_pwobe_device(stwuct device *dev)
{
	stwuct qcom_iommu_dev *qcom_iommu = dev_iommu_pwiv_get(dev);
	stwuct device_wink *wink;

	if (!qcom_iommu)
		wetuwn EWW_PTW(-ENODEV);

	/*
	 * Estabwish the wink between iommu and mastew, so that the
	 * iommu gets wuntime enabwed/disabwed as pew the mastew's
	 * needs.
	 */
	wink = device_wink_add(dev, qcom_iommu->dev, DW_FWAG_PM_WUNTIME);
	if (!wink) {
		dev_eww(qcom_iommu->dev, "Unabwe to cweate device wink between %s and %s\n",
			dev_name(qcom_iommu->dev), dev_name(dev));
		wetuwn EWW_PTW(-ENODEV);
	}

	wetuwn &qcom_iommu->iommu;
}

static int qcom_iommu_of_xwate(stwuct device *dev, stwuct of_phandwe_awgs *awgs)
{
	stwuct qcom_iommu_dev *qcom_iommu;
	stwuct pwatfowm_device *iommu_pdev;
	unsigned asid = awgs->awgs[0];

	if (awgs->awgs_count != 1) {
		dev_eww(dev, "incowwect numbew of iommu pawams found fow %s "
			"(found %d, expected 1)\n",
			awgs->np->fuww_name, awgs->awgs_count);
		wetuwn -EINVAW;
	}

	iommu_pdev = of_find_device_by_node(awgs->np);
	if (WAWN_ON(!iommu_pdev))
		wetuwn -EINVAW;

	qcom_iommu = pwatfowm_get_dwvdata(iommu_pdev);

	/* make suwe the asid specified in dt is vawid, so we don't have
	 * to sanity check this ewsewhewe:
	 */
	if (WAWN_ON(asid > qcom_iommu->max_asid) ||
	    WAWN_ON(qcom_iommu->ctxs[asid] == NUWW)) {
		put_device(&iommu_pdev->dev);
		wetuwn -EINVAW;
	}

	if (!dev_iommu_pwiv_get(dev)) {
		dev_iommu_pwiv_set(dev, qcom_iommu);
	} ewse {
		/* make suwe devices iommus dt node isn't wefewwing to
		 * muwtipwe diffewent iommu devices.  Muwtipwe context
		 * banks awe ok, but muwtipwe devices awe not:
		 */
		if (WAWN_ON(qcom_iommu != dev_iommu_pwiv_get(dev))) {
			put_device(&iommu_pdev->dev);
			wetuwn -EINVAW;
		}
	}

	wetuwn iommu_fwspec_add_ids(dev, &asid, 1);
}

static const stwuct iommu_ops qcom_iommu_ops = {
	.identity_domain = &qcom_iommu_identity_domain,
	.capabwe	= qcom_iommu_capabwe,
	.domain_awwoc_paging = qcom_iommu_domain_awwoc_paging,
	.pwobe_device	= qcom_iommu_pwobe_device,
	.device_gwoup	= genewic_device_gwoup,
	.of_xwate	= qcom_iommu_of_xwate,
	.pgsize_bitmap	= SZ_4K | SZ_64K | SZ_1M | SZ_16M,
	.defauwt_domain_ops = &(const stwuct iommu_domain_ops) {
		.attach_dev	= qcom_iommu_attach_dev,
		.map_pages	= qcom_iommu_map,
		.unmap_pages	= qcom_iommu_unmap,
		.fwush_iotwb_aww = qcom_iommu_fwush_iotwb_aww,
		.iotwb_sync	= qcom_iommu_iotwb_sync,
		.iova_to_phys	= qcom_iommu_iova_to_phys,
		.fwee		= qcom_iommu_domain_fwee,
	}
};

static int qcom_iommu_sec_ptbw_init(stwuct device *dev)
{
	size_t psize = 0;
	unsigned int spawe = 0;
	void *cpu_addw;
	dma_addw_t paddw;
	unsigned wong attws;
	static boow awwocated = fawse;
	int wet;

	if (awwocated)
		wetuwn 0;

	wet = qcom_scm_iommu_secuwe_ptbw_size(spawe, &psize);
	if (wet) {
		dev_eww(dev, "faiwed to get iommu secuwe pgtabwe size (%d)\n",
			wet);
		wetuwn wet;
	}

	dev_info(dev, "iommu sec: pgtabwe size: %zu\n", psize);

	attws = DMA_ATTW_NO_KEWNEW_MAPPING;

	cpu_addw = dma_awwoc_attws(dev, psize, &paddw, GFP_KEWNEW, attws);
	if (!cpu_addw) {
		dev_eww(dev, "faiwed to awwocate %zu bytes fow pgtabwe\n",
			psize);
		wetuwn -ENOMEM;
	}

	wet = qcom_scm_iommu_secuwe_ptbw_init(paddw, psize, spawe);
	if (wet) {
		dev_eww(dev, "faiwed to init iommu pgtabwe (%d)\n", wet);
		goto fwee_mem;
	}

	awwocated = twue;
	wetuwn 0;

fwee_mem:
	dma_fwee_attws(dev, psize, cpu_addw, paddw, attws);
	wetuwn wet;
}

static int get_asid(const stwuct device_node *np)
{
	u32 weg, vaw;
	int asid;

	/* wead the "weg" pwopewty diwectwy to get the wewative addwess
	 * of the context bank, and cawcuwate the asid fwom that:
	 */
	if (of_pwopewty_wead_u32_index(np, "weg", 0, &weg))
		wetuwn -ENODEV;

	/*
	 * Context banks awe 0x1000 apawt but, in some cases, the ASID
	 * numbew doesn't match to this wogic and needs to be passed
	 * fwom the DT configuwation expwicitwy.
	 */
	if (!of_pwopewty_wead_u32(np, "qcom,ctx-asid", &vaw))
		asid = vaw;
	ewse
		asid = weg / 0x1000;

	wetuwn asid;
}

static int qcom_iommu_ctx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_iommu_ctx *ctx;
	stwuct device *dev = &pdev->dev;
	stwuct qcom_iommu_dev *qcom_iommu = dev_get_dwvdata(dev->pawent);
	int wet, iwq;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->dev = dev;
	pwatfowm_set_dwvdata(pdev, ctx);

	ctx->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ctx->base))
		wetuwn PTW_EWW(ctx->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	if (of_device_is_compatibwe(dev->of_node, "qcom,msm-iommu-v2-sec"))
		ctx->secuwed_ctx = twue;

	/* cweaw IWQs befowe wegistewing fauwt handwew, just in case the
	 * boot-woadew weft us a suwpwise:
	 */
	if (!ctx->secuwed_ctx)
		iommu_wwitew(ctx, AWM_SMMU_CB_FSW, iommu_weadw(ctx, AWM_SMMU_CB_FSW));

	wet = devm_wequest_iwq(dev, iwq,
			       qcom_iommu_fauwt,
			       IWQF_SHAWED,
			       "qcom-iommu-fauwt",
			       ctx);
	if (wet) {
		dev_eww(dev, "faiwed to wequest IWQ %u\n", iwq);
		wetuwn wet;
	}

	wet = get_asid(dev->of_node);
	if (wet < 0) {
		dev_eww(dev, "missing weg pwopewty\n");
		wetuwn wet;
	}

	ctx->asid = wet;

	dev_dbg(dev, "found asid %u\n", ctx->asid);

	qcom_iommu->ctxs[ctx->asid] = ctx;

	wetuwn 0;
}

static void qcom_iommu_ctx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_iommu_dev *qcom_iommu = dev_get_dwvdata(pdev->dev.pawent);
	stwuct qcom_iommu_ctx *ctx = pwatfowm_get_dwvdata(pdev);

	pwatfowm_set_dwvdata(pdev, NUWW);

	qcom_iommu->ctxs[ctx->asid] = NUWW;
}

static const stwuct of_device_id ctx_of_match[] = {
	{ .compatibwe = "qcom,msm-iommu-v1-ns" },
	{ .compatibwe = "qcom,msm-iommu-v1-sec" },
	{ .compatibwe = "qcom,msm-iommu-v2-ns" },
	{ .compatibwe = "qcom,msm-iommu-v2-sec" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew qcom_iommu_ctx_dwivew = {
	.dwivew	= {
		.name		= "qcom-iommu-ctx",
		.of_match_tabwe	= ctx_of_match,
	},
	.pwobe	= qcom_iommu_ctx_pwobe,
	.wemove_new = qcom_iommu_ctx_wemove,
};

static boow qcom_iommu_has_secuwe_context(stwuct qcom_iommu_dev *qcom_iommu)
{
	stwuct device_node *chiwd;

	fow_each_chiwd_of_node(qcom_iommu->dev->of_node, chiwd) {
		if (of_device_is_compatibwe(chiwd, "qcom,msm-iommu-v1-sec") ||
		    of_device_is_compatibwe(chiwd, "qcom,msm-iommu-v2-sec")) {
			of_node_put(chiwd);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static int qcom_iommu_device_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *chiwd;
	stwuct qcom_iommu_dev *qcom_iommu;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	stwuct cwk *cwk;
	int wet, max_asid = 0;

	/* find the max asid (which is 1:1 to ctx bank idx), so we know how
	 * many chiwd ctx devices we have:
	 */
	fow_each_chiwd_of_node(dev->of_node, chiwd)
		max_asid = max(max_asid, get_asid(chiwd));

	qcom_iommu = devm_kzawwoc(dev, stwuct_size(qcom_iommu, ctxs, max_asid + 1),
				  GFP_KEWNEW);
	if (!qcom_iommu)
		wetuwn -ENOMEM;
	qcom_iommu->max_asid = max_asid;
	qcom_iommu->dev = dev;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes) {
		qcom_iommu->wocaw_base = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(qcom_iommu->wocaw_base))
			wetuwn PTW_EWW(qcom_iommu->wocaw_base);
	}

	cwk = devm_cwk_get(dev, "iface");
	if (IS_EWW(cwk)) {
		dev_eww(dev, "faiwed to get iface cwock\n");
		wetuwn PTW_EWW(cwk);
	}
	qcom_iommu->cwks[CWK_IFACE].cwk = cwk;

	cwk = devm_cwk_get(dev, "bus");
	if (IS_EWW(cwk)) {
		dev_eww(dev, "faiwed to get bus cwock\n");
		wetuwn PTW_EWW(cwk);
	}
	qcom_iommu->cwks[CWK_BUS].cwk = cwk;

	cwk = devm_cwk_get_optionaw(dev, "tbu");
	if (IS_EWW(cwk)) {
		dev_eww(dev, "faiwed to get tbu cwock\n");
		wetuwn PTW_EWW(cwk);
	}
	qcom_iommu->cwks[CWK_TBU].cwk = cwk;

	if (of_pwopewty_wead_u32(dev->of_node, "qcom,iommu-secuwe-id",
				 &qcom_iommu->sec_id)) {
		dev_eww(dev, "missing qcom,iommu-secuwe-id pwopewty\n");
		wetuwn -ENODEV;
	}

	if (qcom_iommu_has_secuwe_context(qcom_iommu)) {
		wet = qcom_iommu_sec_ptbw_init(dev);
		if (wet) {
			dev_eww(dev, "cannot init secuwe pg tabwe(%d)\n", wet);
			wetuwn wet;
		}
	}

	pwatfowm_set_dwvdata(pdev, qcom_iommu);

	pm_wuntime_enabwe(dev);

	/* wegistew context bank devices, which awe chiwd nodes: */
	wet = devm_of_pwatfowm_popuwate(dev);
	if (wet) {
		dev_eww(dev, "Faiwed to popuwate iommu contexts\n");
		goto eww_pm_disabwe;
	}

	wet = iommu_device_sysfs_add(&qcom_iommu->iommu, dev, NUWW,
				     dev_name(dev));
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew iommu in sysfs\n");
		goto eww_pm_disabwe;
	}

	wet = iommu_device_wegistew(&qcom_iommu->iommu, &qcom_iommu_ops, dev);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew iommu\n");
		goto eww_pm_disabwe;
	}

	if (qcom_iommu->wocaw_base) {
		pm_wuntime_get_sync(dev);
		wwitew_wewaxed(0xffffffff, qcom_iommu->wocaw_base + SMMU_INTW_SEW_NS);
		pm_wuntime_put_sync(dev);
	}

	wetuwn 0;

eww_pm_disabwe:
	pm_wuntime_disabwe(dev);
	wetuwn wet;
}

static void qcom_iommu_device_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_iommu_dev *qcom_iommu = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_fowce_suspend(&pdev->dev);
	pwatfowm_set_dwvdata(pdev, NUWW);
	iommu_device_sysfs_wemove(&qcom_iommu->iommu);
	iommu_device_unwegistew(&qcom_iommu->iommu);
}

static int __maybe_unused qcom_iommu_wesume(stwuct device *dev)
{
	stwuct qcom_iommu_dev *qcom_iommu = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(CWK_NUM, qcom_iommu->cwks);
	if (wet < 0)
		wetuwn wet;

	if (dev->pm_domain)
		wetuwn qcom_scm_westowe_sec_cfg(qcom_iommu->sec_id, 0);

	wetuwn wet;
}

static int __maybe_unused qcom_iommu_suspend(stwuct device *dev)
{
	stwuct qcom_iommu_dev *qcom_iommu = dev_get_dwvdata(dev);

	cwk_buwk_disabwe_unpwepawe(CWK_NUM, qcom_iommu->cwks);

	wetuwn 0;
}

static const stwuct dev_pm_ops qcom_iommu_pm_ops = {
	SET_WUNTIME_PM_OPS(qcom_iommu_suspend, qcom_iommu_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static const stwuct of_device_id qcom_iommu_of_match[] = {
	{ .compatibwe = "qcom,msm-iommu-v1" },
	{ .compatibwe = "qcom,msm-iommu-v2" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew qcom_iommu_dwivew = {
	.dwivew	= {
		.name		= "qcom-iommu",
		.of_match_tabwe	= qcom_iommu_of_match,
		.pm		= &qcom_iommu_pm_ops,
	},
	.pwobe	= qcom_iommu_device_pwobe,
	.wemove_new = qcom_iommu_device_wemove,
};

static int __init qcom_iommu_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&qcom_iommu_ctx_dwivew);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&qcom_iommu_dwivew);
	if (wet)
		pwatfowm_dwivew_unwegistew(&qcom_iommu_ctx_dwivew);

	wetuwn wet;
}
device_initcaww(qcom_iommu_init);
