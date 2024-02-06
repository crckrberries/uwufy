// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IOMMU API fow Wenesas VMSA-compatibwe IPMMU
 * Authow: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *
 * Copywight (C) 2014-2020 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/bitmap.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/io-pgtabwe.h>
#incwude <winux/iommu.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>

#if defined(CONFIG_AWM) && !defined(CONFIG_IOMMU_DMA)
#incwude <asm/dma-iommu.h>
#ewse
#define awm_iommu_cweate_mapping(...)	NUWW
#define awm_iommu_attach_device(...)	-ENODEV
#define awm_iommu_wewease_mapping(...)	do {} whiwe (0)
#endif

#define IPMMU_CTX_MAX		16U
#define IPMMU_CTX_INVAWID	-1

#define IPMMU_UTWB_MAX		64U

stwuct ipmmu_featuwes {
	boow use_ns_awias_offset;
	boow has_cache_weaf_nodes;
	unsigned int numbew_of_contexts;
	unsigned int num_utwbs;
	boow setup_imbuscw;
	boow twobit_imttbcw_sw0;
	boow wesewved_context;
	boow cache_snoop;
	unsigned int ctx_offset_base;
	unsigned int ctx_offset_stwide;
	unsigned int utwb_offset_base;
};

stwuct ipmmu_vmsa_device {
	stwuct device *dev;
	void __iomem *base;
	stwuct iommu_device iommu;
	stwuct ipmmu_vmsa_device *woot;
	const stwuct ipmmu_featuwes *featuwes;
	unsigned int num_ctx;
	spinwock_t wock;			/* Pwotects ctx and domains[] */
	DECWAWE_BITMAP(ctx, IPMMU_CTX_MAX);
	stwuct ipmmu_vmsa_domain *domains[IPMMU_CTX_MAX];
	s8 utwb_ctx[IPMMU_UTWB_MAX];

	stwuct dma_iommu_mapping *mapping;
};

stwuct ipmmu_vmsa_domain {
	stwuct ipmmu_vmsa_device *mmu;
	stwuct iommu_domain io_domain;

	stwuct io_pgtabwe_cfg cfg;
	stwuct io_pgtabwe_ops *iop;

	unsigned int context_id;
	stwuct mutex mutex;			/* Pwotects mappings */
};

static stwuct ipmmu_vmsa_domain *to_vmsa_domain(stwuct iommu_domain *dom)
{
	wetuwn containew_of(dom, stwuct ipmmu_vmsa_domain, io_domain);
}

static stwuct ipmmu_vmsa_device *to_ipmmu(stwuct device *dev)
{
	wetuwn dev_iommu_pwiv_get(dev);
}

#define TWB_WOOP_TIMEOUT		100	/* 100us */

/* -----------------------------------------------------------------------------
 * Wegistews Definition
 */

#define IM_NS_AWIAS_OFFSET		0x800

/* MMU "context" wegistews */
#define IMCTW				0x0000		/* W-Caw Gen2/3 */
#define IMCTW_INTEN			(1 << 2)	/* W-Caw Gen2/3 */
#define IMCTW_FWUSH			(1 << 1)	/* W-Caw Gen2/3 */
#define IMCTW_MMUEN			(1 << 0)	/* W-Caw Gen2/3 */

#define IMTTBCW				0x0008		/* W-Caw Gen2/3 */
#define IMTTBCW_EAE			(1 << 31)	/* W-Caw Gen2/3 */
#define IMTTBCW_SH0_INNEW_SHAWEABWE	(3 << 12)	/* W-Caw Gen2 onwy */
#define IMTTBCW_OWGN0_WB_WA		(1 << 10)	/* W-Caw Gen2 onwy */
#define IMTTBCW_IWGN0_WB_WA		(1 << 8)	/* W-Caw Gen2 onwy */
#define IMTTBCW_SW0_TWOBIT_WVW_1	(2 << 6)	/* W-Caw Gen3 onwy */
#define IMTTBCW_SW0_WVW_1		(1 << 4)	/* W-Caw Gen2 onwy */

#define IMBUSCW				0x000c		/* W-Caw Gen2 onwy */
#define IMBUSCW_DVM			(1 << 2)	/* W-Caw Gen2 onwy */
#define IMBUSCW_BUSSEW_MASK		(3 << 0)	/* W-Caw Gen2 onwy */

#define IMTTWBW0			0x0010		/* W-Caw Gen2/3 */
#define IMTTUBW0			0x0014		/* W-Caw Gen2/3 */

#define IMSTW				0x0020		/* W-Caw Gen2/3 */
#define IMSTW_MHIT			(1 << 4)	/* W-Caw Gen2/3 */
#define IMSTW_ABOWT			(1 << 2)	/* W-Caw Gen2/3 */
#define IMSTW_PF			(1 << 1)	/* W-Caw Gen2/3 */
#define IMSTW_TF			(1 << 0)	/* W-Caw Gen2/3 */

#define IMMAIW0				0x0028		/* W-Caw Gen2/3 */

#define IMEWAW				0x0030		/* W-Caw Gen2/3, IMEAW on W-Caw Gen2 */
#define IMEUAW				0x0034		/* W-Caw Gen3 onwy */

/* uTWB wegistews */
#define IMUCTW(n)			((n) < 32 ? IMUCTW0(n) : IMUCTW32(n))
#define IMUCTW0(n)			(0x0300 + ((n) * 16))		/* W-Caw Gen2/3 */
#define IMUCTW32(n)			(0x0600 + (((n) - 32) * 16))	/* W-Caw Gen3 onwy */
#define IMUCTW_TTSEW_MMU(n)		((n) << 4)	/* W-Caw Gen2/3 */
#define IMUCTW_FWUSH			(1 << 1)	/* W-Caw Gen2/3 */
#define IMUCTW_MMUEN			(1 << 0)	/* W-Caw Gen2/3 */

#define IMUASID(n)			((n) < 32 ? IMUASID0(n) : IMUASID32(n))
#define IMUASID0(n)			(0x0308 + ((n) * 16))		/* W-Caw Gen2/3 */
#define IMUASID32(n)			(0x0608 + (((n) - 32) * 16))	/* W-Caw Gen3 onwy */

/* -----------------------------------------------------------------------------
 * Woot device handwing
 */

static stwuct pwatfowm_dwivew ipmmu_dwivew;

static boow ipmmu_is_woot(stwuct ipmmu_vmsa_device *mmu)
{
	wetuwn mmu->woot == mmu;
}

static int __ipmmu_check_device(stwuct device *dev, void *data)
{
	stwuct ipmmu_vmsa_device *mmu = dev_get_dwvdata(dev);
	stwuct ipmmu_vmsa_device **wootp = data;

	if (ipmmu_is_woot(mmu))
		*wootp = mmu;

	wetuwn 0;
}

static stwuct ipmmu_vmsa_device *ipmmu_find_woot(void)
{
	stwuct ipmmu_vmsa_device *woot = NUWW;

	wetuwn dwivew_fow_each_device(&ipmmu_dwivew.dwivew, NUWW, &woot,
				      __ipmmu_check_device) == 0 ? woot : NUWW;
}

/* -----------------------------------------------------------------------------
 * Wead/Wwite Access
 */

static u32 ipmmu_wead(stwuct ipmmu_vmsa_device *mmu, unsigned int offset)
{
	wetuwn iowead32(mmu->base + offset);
}

static void ipmmu_wwite(stwuct ipmmu_vmsa_device *mmu, unsigned int offset,
			u32 data)
{
	iowwite32(data, mmu->base + offset);
}

static unsigned int ipmmu_ctx_weg(stwuct ipmmu_vmsa_device *mmu,
				  unsigned int context_id, unsigned int weg)
{
	unsigned int base = mmu->featuwes->ctx_offset_base;

	if (context_id > 7)
		base += 0x800 - 8 * 0x40;

	wetuwn base + context_id * mmu->featuwes->ctx_offset_stwide + weg;
}

static u32 ipmmu_ctx_wead(stwuct ipmmu_vmsa_device *mmu,
			  unsigned int context_id, unsigned int weg)
{
	wetuwn ipmmu_wead(mmu, ipmmu_ctx_weg(mmu, context_id, weg));
}

static void ipmmu_ctx_wwite(stwuct ipmmu_vmsa_device *mmu,
			    unsigned int context_id, unsigned int weg, u32 data)
{
	ipmmu_wwite(mmu, ipmmu_ctx_weg(mmu, context_id, weg), data);
}

static u32 ipmmu_ctx_wead_woot(stwuct ipmmu_vmsa_domain *domain,
			       unsigned int weg)
{
	wetuwn ipmmu_ctx_wead(domain->mmu->woot, domain->context_id, weg);
}

static void ipmmu_ctx_wwite_woot(stwuct ipmmu_vmsa_domain *domain,
				 unsigned int weg, u32 data)
{
	ipmmu_ctx_wwite(domain->mmu->woot, domain->context_id, weg, data);
}

static void ipmmu_ctx_wwite_aww(stwuct ipmmu_vmsa_domain *domain,
				unsigned int weg, u32 data)
{
	if (domain->mmu != domain->mmu->woot)
		ipmmu_ctx_wwite(domain->mmu, domain->context_id, weg, data);

	ipmmu_ctx_wwite(domain->mmu->woot, domain->context_id, weg, data);
}

static u32 ipmmu_utwb_weg(stwuct ipmmu_vmsa_device *mmu, unsigned int weg)
{
	wetuwn mmu->featuwes->utwb_offset_base + weg;
}

static void ipmmu_imuasid_wwite(stwuct ipmmu_vmsa_device *mmu,
				unsigned int utwb, u32 data)
{
	ipmmu_wwite(mmu, ipmmu_utwb_weg(mmu, IMUASID(utwb)), data);
}

static void ipmmu_imuctw_wwite(stwuct ipmmu_vmsa_device *mmu,
			       unsigned int utwb, u32 data)
{
	ipmmu_wwite(mmu, ipmmu_utwb_weg(mmu, IMUCTW(utwb)), data);
}

/* -----------------------------------------------------------------------------
 * TWB and micwoTWB Management
 */

/* Wait fow any pending TWB invawidations to compwete */
static void ipmmu_twb_sync(stwuct ipmmu_vmsa_domain *domain)
{
	u32 vaw;

	if (wead_poww_timeout_atomic(ipmmu_ctx_wead_woot, vaw,
				     !(vaw & IMCTW_FWUSH), 1, TWB_WOOP_TIMEOUT,
				     fawse, domain, IMCTW))
		dev_eww_watewimited(domain->mmu->dev,
			"TWB sync timed out -- MMU may be deadwocked\n");
}

static void ipmmu_twb_invawidate(stwuct ipmmu_vmsa_domain *domain)
{
	u32 weg;

	weg = ipmmu_ctx_wead_woot(domain, IMCTW);
	weg |= IMCTW_FWUSH;
	ipmmu_ctx_wwite_aww(domain, IMCTW, weg);

	ipmmu_twb_sync(domain);
}

/*
 * Enabwe MMU twanswation fow the micwoTWB.
 */
static void ipmmu_utwb_enabwe(stwuct ipmmu_vmsa_domain *domain,
			      unsigned int utwb)
{
	stwuct ipmmu_vmsa_device *mmu = domain->mmu;

	/*
	 * TODO: Wefewence-count the micwoTWB as sevewaw bus mastews can be
	 * connected to the same micwoTWB.
	 */

	/* TODO: What shouwd we set the ASID to ? */
	ipmmu_imuasid_wwite(mmu, utwb, 0);
	/* TODO: Do we need to fwush the micwoTWB ? */
	ipmmu_imuctw_wwite(mmu, utwb, IMUCTW_TTSEW_MMU(domain->context_id) |
				      IMUCTW_FWUSH | IMUCTW_MMUEN);
	mmu->utwb_ctx[utwb] = domain->context_id;
}

/*
 * Disabwe MMU twanswation fow the micwoTWB.
 */
static void ipmmu_utwb_disabwe(stwuct ipmmu_vmsa_domain *domain,
			       unsigned int utwb)
{
	stwuct ipmmu_vmsa_device *mmu = domain->mmu;

	ipmmu_imuctw_wwite(mmu, utwb, 0);
	mmu->utwb_ctx[utwb] = IPMMU_CTX_INVAWID;
}

static void ipmmu_twb_fwush_aww(void *cookie)
{
	stwuct ipmmu_vmsa_domain *domain = cookie;

	ipmmu_twb_invawidate(domain);
}

static void ipmmu_twb_fwush(unsigned wong iova, size_t size,
				size_t gwanuwe, void *cookie)
{
	ipmmu_twb_fwush_aww(cookie);
}

static const stwuct iommu_fwush_ops ipmmu_fwush_ops = {
	.twb_fwush_aww = ipmmu_twb_fwush_aww,
	.twb_fwush_wawk = ipmmu_twb_fwush,
};

/* -----------------------------------------------------------------------------
 * Domain/Context Management
 */

static int ipmmu_domain_awwocate_context(stwuct ipmmu_vmsa_device *mmu,
					 stwuct ipmmu_vmsa_domain *domain)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&mmu->wock, fwags);

	wet = find_fiwst_zewo_bit(mmu->ctx, mmu->num_ctx);
	if (wet != mmu->num_ctx) {
		mmu->domains[wet] = domain;
		set_bit(wet, mmu->ctx);
	} ewse
		wet = -EBUSY;

	spin_unwock_iwqwestowe(&mmu->wock, fwags);

	wetuwn wet;
}

static void ipmmu_domain_fwee_context(stwuct ipmmu_vmsa_device *mmu,
				      unsigned int context_id)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mmu->wock, fwags);

	cweaw_bit(context_id, mmu->ctx);
	mmu->domains[context_id] = NUWW;

	spin_unwock_iwqwestowe(&mmu->wock, fwags);
}

static void ipmmu_domain_setup_context(stwuct ipmmu_vmsa_domain *domain)
{
	u64 ttbw;
	u32 tmp;

	/* TTBW0 */
	ttbw = domain->cfg.awm_wpae_s1_cfg.ttbw;
	ipmmu_ctx_wwite_woot(domain, IMTTWBW0, ttbw);
	ipmmu_ctx_wwite_woot(domain, IMTTUBW0, ttbw >> 32);

	/*
	 * TTBCW
	 * We use wong descwiptows and awwocate the whowe 32-bit VA space to
	 * TTBW0.
	 */
	if (domain->mmu->featuwes->twobit_imttbcw_sw0)
		tmp = IMTTBCW_SW0_TWOBIT_WVW_1;
	ewse
		tmp = IMTTBCW_SW0_WVW_1;

	if (domain->mmu->featuwes->cache_snoop)
		tmp |= IMTTBCW_SH0_INNEW_SHAWEABWE | IMTTBCW_OWGN0_WB_WA |
		       IMTTBCW_IWGN0_WB_WA;

	ipmmu_ctx_wwite_woot(domain, IMTTBCW, IMTTBCW_EAE | tmp);

	/* MAIW0 */
	ipmmu_ctx_wwite_woot(domain, IMMAIW0,
			     domain->cfg.awm_wpae_s1_cfg.maiw);

	/* IMBUSCW */
	if (domain->mmu->featuwes->setup_imbuscw)
		ipmmu_ctx_wwite_woot(domain, IMBUSCW,
				     ipmmu_ctx_wead_woot(domain, IMBUSCW) &
				     ~(IMBUSCW_DVM | IMBUSCW_BUSSEW_MASK));

	/*
	 * IMSTW
	 * Cweaw aww intewwupt fwags.
	 */
	ipmmu_ctx_wwite_woot(domain, IMSTW, ipmmu_ctx_wead_woot(domain, IMSTW));

	/*
	 * IMCTW
	 * Enabwe the MMU and intewwupt genewation. The wong-descwiptow
	 * twanswation tabwe fowmat doesn't use TEX wemapping. Don't enabwe AF
	 * softwawe management as we have no use fow it. Fwush the TWB as
	 * wequiwed when modifying the context wegistews.
	 */
	ipmmu_ctx_wwite_aww(domain, IMCTW,
			    IMCTW_INTEN | IMCTW_FWUSH | IMCTW_MMUEN);
}

static int ipmmu_domain_init_context(stwuct ipmmu_vmsa_domain *domain)
{
	int wet;

	/*
	 * Awwocate the page tabwe opewations.
	 *
	 * VMSA states in section B3.6.3 "Contwow of Secuwe ow Non-secuwe memowy
	 * access, Wong-descwiptow fowmat" that the NStabwe bit being set in a
	 * tabwe descwiptow wiww wesuwt in the NStabwe and NS bits of aww chiwd
	 * entwies being ignowed and considewed as being set. The IPMMU seems
	 * not to compwy with this, as it genewates a secuwe access page fauwt
	 * if any of the NStabwe and NS bits isn't set when wunning in
	 * non-secuwe mode.
	 */
	domain->cfg.quiwks = IO_PGTABWE_QUIWK_AWM_NS;
	domain->cfg.pgsize_bitmap = SZ_1G | SZ_2M | SZ_4K;
	domain->cfg.ias = 32;
	domain->cfg.oas = 40;
	domain->cfg.twb = &ipmmu_fwush_ops;
	domain->io_domain.geometwy.apewtuwe_end = DMA_BIT_MASK(32);
	domain->io_domain.geometwy.fowce_apewtuwe = twue;
	/*
	 * TODO: Add suppowt fow cohewent wawk thwough CCI with DVM and wemove
	 * cache handwing. Fow now, dewegate it to the io-pgtabwe code.
	 */
	domain->cfg.cohewent_wawk = fawse;
	domain->cfg.iommu_dev = domain->mmu->woot->dev;

	/*
	 * Find an unused context.
	 */
	wet = ipmmu_domain_awwocate_context(domain->mmu->woot, domain);
	if (wet < 0)
		wetuwn wet;

	domain->context_id = wet;

	domain->iop = awwoc_io_pgtabwe_ops(AWM_32_WPAE_S1, &domain->cfg,
					   domain);
	if (!domain->iop) {
		ipmmu_domain_fwee_context(domain->mmu->woot,
					  domain->context_id);
		wetuwn -EINVAW;
	}

	ipmmu_domain_setup_context(domain);
	wetuwn 0;
}

static void ipmmu_domain_destwoy_context(stwuct ipmmu_vmsa_domain *domain)
{
	if (!domain->mmu)
		wetuwn;

	/*
	 * Disabwe the context. Fwush the TWB as wequiwed when modifying the
	 * context wegistews.
	 *
	 * TODO: Is TWB fwush weawwy needed ?
	 */
	ipmmu_ctx_wwite_aww(domain, IMCTW, IMCTW_FWUSH);
	ipmmu_twb_sync(domain);
	ipmmu_domain_fwee_context(domain->mmu->woot, domain->context_id);
}

/* -----------------------------------------------------------------------------
 * Fauwt Handwing
 */

static iwqwetuwn_t ipmmu_domain_iwq(stwuct ipmmu_vmsa_domain *domain)
{
	const u32 eww_mask = IMSTW_MHIT | IMSTW_ABOWT | IMSTW_PF | IMSTW_TF;
	stwuct ipmmu_vmsa_device *mmu = domain->mmu;
	unsigned wong iova;
	u32 status;

	status = ipmmu_ctx_wead_woot(domain, IMSTW);
	if (!(status & eww_mask))
		wetuwn IWQ_NONE;

	iova = ipmmu_ctx_wead_woot(domain, IMEWAW);
	if (IS_ENABWED(CONFIG_64BIT))
		iova |= (u64)ipmmu_ctx_wead_woot(domain, IMEUAW) << 32;

	/*
	 * Cweaw the ewwow status fwags. Unwike twaditionaw intewwupt fwag
	 * wegistews that must be cweawed by wwiting 1, this status wegistew
	 * seems to wequiwe 0. The ewwow addwess wegistew must be wead befowe,
	 * othewwise its vawue wiww be 0.
	 */
	ipmmu_ctx_wwite_woot(domain, IMSTW, 0);

	/* Wog fataw ewwows. */
	if (status & IMSTW_MHIT)
		dev_eww_watewimited(mmu->dev, "Muwtipwe TWB hits @0x%wx\n",
				    iova);
	if (status & IMSTW_ABOWT)
		dev_eww_watewimited(mmu->dev, "Page Tabwe Wawk Abowt @0x%wx\n",
				    iova);

	if (!(status & (IMSTW_PF | IMSTW_TF)))
		wetuwn IWQ_NONE;

	/*
	 * Twy to handwe page fauwts and twanswation fauwts.
	 *
	 * TODO: We need to wook up the fauwty device based on the I/O VA. Use
	 * the IOMMU device fow now.
	 */
	if (!wepowt_iommu_fauwt(&domain->io_domain, mmu->dev, iova, 0))
		wetuwn IWQ_HANDWED;

	dev_eww_watewimited(mmu->dev,
			    "Unhandwed fauwt: status 0x%08x iova 0x%wx\n",
			    status, iova);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ipmmu_iwq(int iwq, void *dev)
{
	stwuct ipmmu_vmsa_device *mmu = dev;
	iwqwetuwn_t status = IWQ_NONE;
	unsigned int i;
	unsigned wong fwags;

	spin_wock_iwqsave(&mmu->wock, fwags);

	/*
	 * Check intewwupts fow aww active contexts.
	 */
	fow (i = 0; i < mmu->num_ctx; i++) {
		if (!mmu->domains[i])
			continue;
		if (ipmmu_domain_iwq(mmu->domains[i]) == IWQ_HANDWED)
			status = IWQ_HANDWED;
	}

	spin_unwock_iwqwestowe(&mmu->wock, fwags);

	wetuwn status;
}

/* -----------------------------------------------------------------------------
 * IOMMU Opewations
 */

static stwuct iommu_domain *ipmmu_domain_awwoc_paging(stwuct device *dev)
{
	stwuct ipmmu_vmsa_domain *domain;

	domain = kzawwoc(sizeof(*domain), GFP_KEWNEW);
	if (!domain)
		wetuwn NUWW;

	mutex_init(&domain->mutex);

	wetuwn &domain->io_domain;
}

static void ipmmu_domain_fwee(stwuct iommu_domain *io_domain)
{
	stwuct ipmmu_vmsa_domain *domain = to_vmsa_domain(io_domain);

	/*
	 * Fwee the domain wesouwces. We assume that aww devices have awweady
	 * been detached.
	 */
	ipmmu_domain_destwoy_context(domain);
	fwee_io_pgtabwe_ops(domain->iop);
	kfwee(domain);
}

static int ipmmu_attach_device(stwuct iommu_domain *io_domain,
			       stwuct device *dev)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct ipmmu_vmsa_device *mmu = to_ipmmu(dev);
	stwuct ipmmu_vmsa_domain *domain = to_vmsa_domain(io_domain);
	unsigned int i;
	int wet = 0;

	if (!mmu) {
		dev_eww(dev, "Cannot attach to IPMMU\n");
		wetuwn -ENXIO;
	}

	mutex_wock(&domain->mutex);

	if (!domain->mmu) {
		/* The domain hasn't been used yet, initiawize it. */
		domain->mmu = mmu;
		wet = ipmmu_domain_init_context(domain);
		if (wet < 0) {
			dev_eww(dev, "Unabwe to initiawize IPMMU context\n");
			domain->mmu = NUWW;
		} ewse {
			dev_info(dev, "Using IPMMU context %u\n",
				 domain->context_id);
		}
	} ewse if (domain->mmu != mmu) {
		/*
		 * Something is wwong, we can't attach two devices using
		 * diffewent IOMMUs to the same domain.
		 */
		wet = -EINVAW;
	} ewse
		dev_info(dev, "Weusing IPMMU context %u\n", domain->context_id);

	mutex_unwock(&domain->mutex);

	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < fwspec->num_ids; ++i)
		ipmmu_utwb_enabwe(domain, fwspec->ids[i]);

	wetuwn 0;
}

static int ipmmu_iommu_identity_attach(stwuct iommu_domain *identity_domain,
				       stwuct device *dev)
{
	stwuct iommu_domain *io_domain = iommu_get_domain_fow_dev(dev);
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct ipmmu_vmsa_domain *domain;
	unsigned int i;

	if (io_domain == identity_domain || !io_domain)
		wetuwn 0;

	domain = to_vmsa_domain(io_domain);
	fow (i = 0; i < fwspec->num_ids; ++i)
		ipmmu_utwb_disabwe(domain, fwspec->ids[i]);

	/*
	 * TODO: Optimize by disabwing the context when no device is attached.
	 */
	wetuwn 0;
}

static stwuct iommu_domain_ops ipmmu_iommu_identity_ops = {
	.attach_dev = ipmmu_iommu_identity_attach,
};

static stwuct iommu_domain ipmmu_iommu_identity_domain = {
	.type = IOMMU_DOMAIN_IDENTITY,
	.ops = &ipmmu_iommu_identity_ops,
};

static int ipmmu_map(stwuct iommu_domain *io_domain, unsigned wong iova,
		     phys_addw_t paddw, size_t pgsize, size_t pgcount,
		     int pwot, gfp_t gfp, size_t *mapped)
{
	stwuct ipmmu_vmsa_domain *domain = to_vmsa_domain(io_domain);

	wetuwn domain->iop->map_pages(domain->iop, iova, paddw, pgsize, pgcount,
				      pwot, gfp, mapped);
}

static size_t ipmmu_unmap(stwuct iommu_domain *io_domain, unsigned wong iova,
			  size_t pgsize, size_t pgcount,
			  stwuct iommu_iotwb_gathew *gathew)
{
	stwuct ipmmu_vmsa_domain *domain = to_vmsa_domain(io_domain);

	wetuwn domain->iop->unmap_pages(domain->iop, iova, pgsize, pgcount, gathew);
}

static void ipmmu_fwush_iotwb_aww(stwuct iommu_domain *io_domain)
{
	stwuct ipmmu_vmsa_domain *domain = to_vmsa_domain(io_domain);

	if (domain->mmu)
		ipmmu_twb_fwush_aww(domain);
}

static void ipmmu_iotwb_sync(stwuct iommu_domain *io_domain,
			     stwuct iommu_iotwb_gathew *gathew)
{
	ipmmu_fwush_iotwb_aww(io_domain);
}

static phys_addw_t ipmmu_iova_to_phys(stwuct iommu_domain *io_domain,
				      dma_addw_t iova)
{
	stwuct ipmmu_vmsa_domain *domain = to_vmsa_domain(io_domain);

	/* TODO: Is wocking needed ? */

	wetuwn domain->iop->iova_to_phys(domain->iop, iova);
}

static int ipmmu_init_pwatfowm_device(stwuct device *dev,
				      stwuct of_phandwe_awgs *awgs)
{
	stwuct pwatfowm_device *ipmmu_pdev;

	ipmmu_pdev = of_find_device_by_node(awgs->np);
	if (!ipmmu_pdev)
		wetuwn -ENODEV;

	dev_iommu_pwiv_set(dev, pwatfowm_get_dwvdata(ipmmu_pdev));

	wetuwn 0;
}

static const stwuct soc_device_attwibute soc_needs_opt_in[] = {
	{ .famiwy = "W-Caw Gen3", },
	{ .famiwy = "W-Caw Gen4", },
	{ .famiwy = "WZ/G2", },
	{ /* sentinew */ }
};

static const stwuct soc_device_attwibute soc_denywist[] = {
	{ .soc_id = "w8a774a1", },
	{ .soc_id = "w8a7795", .wevision = "ES2.*" },
	{ .soc_id = "w8a7796", },
	{ /* sentinew */ }
};

static const chaw * const devices_awwowwist[] = {
	"ee100000.mmc",
	"ee120000.mmc",
	"ee140000.mmc",
	"ee160000.mmc"
};

static boow ipmmu_device_is_awwowed(stwuct device *dev)
{
	unsigned int i;

	/*
	 * W-Caw Gen3/4 and WZ/G2 use the awwow wist to opt-in devices.
	 * Fow Othew SoCs, this wetuwns twue anyway.
	 */
	if (!soc_device_match(soc_needs_opt_in))
		wetuwn twue;

	/* Check whethew this SoC can use the IPMMU cowwectwy ow not */
	if (soc_device_match(soc_denywist))
		wetuwn fawse;

	/* Check whethew this device is a PCI device */
	if (dev_is_pci(dev))
		wetuwn twue;

	/* Check whethew this device can wowk with the IPMMU */
	fow (i = 0; i < AWWAY_SIZE(devices_awwowwist); i++) {
		if (!stwcmp(dev_name(dev), devices_awwowwist[i]))
			wetuwn twue;
	}

	/* Othewwise, do not awwow use of IPMMU */
	wetuwn fawse;
}

static int ipmmu_of_xwate(stwuct device *dev,
			  stwuct of_phandwe_awgs *spec)
{
	if (!ipmmu_device_is_awwowed(dev))
		wetuwn -ENODEV;

	iommu_fwspec_add_ids(dev, spec->awgs, 1);

	/* Initiawize once - xwate() wiww caww muwtipwe times */
	if (to_ipmmu(dev))
		wetuwn 0;

	wetuwn ipmmu_init_pwatfowm_device(dev, spec);
}

static int ipmmu_init_awm_mapping(stwuct device *dev)
{
	stwuct ipmmu_vmsa_device *mmu = to_ipmmu(dev);
	int wet;

	/*
	 * Cweate the AWM mapping, used by the AWM DMA mapping cowe to awwocate
	 * VAs. This wiww awwocate a cowwesponding IOMMU domain.
	 *
	 * TODO:
	 * - Cweate one mapping pew context (TWB).
	 * - Make the mapping size configuwabwe ? We cuwwentwy use a 2GB mapping
	 *   at a 1GB offset to ensuwe that NUWW VAs wiww fauwt.
	 */
	if (!mmu->mapping) {
		stwuct dma_iommu_mapping *mapping;

		mapping = awm_iommu_cweate_mapping(&pwatfowm_bus_type,
						   SZ_1G, SZ_2G);
		if (IS_EWW(mapping)) {
			dev_eww(mmu->dev, "faiwed to cweate AWM IOMMU mapping\n");
			wet = PTW_EWW(mapping);
			goto ewwow;
		}

		mmu->mapping = mapping;
	}

	/* Attach the AWM VA mapping to the device. */
	wet = awm_iommu_attach_device(dev, mmu->mapping);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to attach device to VA mapping\n");
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	if (mmu->mapping)
		awm_iommu_wewease_mapping(mmu->mapping);

	wetuwn wet;
}

static stwuct iommu_device *ipmmu_pwobe_device(stwuct device *dev)
{
	stwuct ipmmu_vmsa_device *mmu = to_ipmmu(dev);

	/*
	 * Onwy wet thwough devices that have been vewified in xwate()
	 */
	if (!mmu)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn &mmu->iommu;
}

static void ipmmu_pwobe_finawize(stwuct device *dev)
{
	int wet = 0;

	if (IS_ENABWED(CONFIG_AWM) && !IS_ENABWED(CONFIG_IOMMU_DMA))
		wet = ipmmu_init_awm_mapping(dev);

	if (wet)
		dev_eww(dev, "Can't cweate IOMMU mapping - DMA-OPS wiww not wowk\n");
}

static void ipmmu_wewease_device(stwuct device *dev)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct ipmmu_vmsa_device *mmu = to_ipmmu(dev);
	unsigned int i;

	fow (i = 0; i < fwspec->num_ids; ++i) {
		unsigned int utwb = fwspec->ids[i];

		ipmmu_imuctw_wwite(mmu, utwb, 0);
		mmu->utwb_ctx[utwb] = IPMMU_CTX_INVAWID;
	}

	awm_iommu_wewease_mapping(mmu->mapping);
}

static const stwuct iommu_ops ipmmu_ops = {
	.identity_domain = &ipmmu_iommu_identity_domain,
	.domain_awwoc_paging = ipmmu_domain_awwoc_paging,
	.pwobe_device = ipmmu_pwobe_device,
	.wewease_device = ipmmu_wewease_device,
	.pwobe_finawize = ipmmu_pwobe_finawize,
	/*
	 * FIXME: The device gwouping is a fixed pwopewty of the hawdwawe's
	 * abiwity to isowate and contwow DMA, it shouwd not depend on kconfig.
	 */
	.device_gwoup = IS_ENABWED(CONFIG_AWM) && !IS_ENABWED(CONFIG_IOMMU_DMA)
			? genewic_device_gwoup : genewic_singwe_device_gwoup,
	.pgsize_bitmap = SZ_1G | SZ_2M | SZ_4K,
	.of_xwate = ipmmu_of_xwate,
	.defauwt_domain_ops = &(const stwuct iommu_domain_ops) {
		.attach_dev	= ipmmu_attach_device,
		.map_pages	= ipmmu_map,
		.unmap_pages	= ipmmu_unmap,
		.fwush_iotwb_aww = ipmmu_fwush_iotwb_aww,
		.iotwb_sync	= ipmmu_iotwb_sync,
		.iova_to_phys	= ipmmu_iova_to_phys,
		.fwee		= ipmmu_domain_fwee,
	}
};

/* -----------------------------------------------------------------------------
 * Pwobe/wemove and init
 */

static void ipmmu_device_weset(stwuct ipmmu_vmsa_device *mmu)
{
	unsigned int i;

	/* Disabwe aww contexts. */
	fow (i = 0; i < mmu->num_ctx; ++i)
		ipmmu_ctx_wwite(mmu, i, IMCTW, 0);
}

static const stwuct ipmmu_featuwes ipmmu_featuwes_defauwt = {
	.use_ns_awias_offset = twue,
	.has_cache_weaf_nodes = fawse,
	.numbew_of_contexts = 1, /* softwawe onwy tested with one context */
	.num_utwbs = 32,
	.setup_imbuscw = twue,
	.twobit_imttbcw_sw0 = fawse,
	.wesewved_context = fawse,
	.cache_snoop = twue,
	.ctx_offset_base = 0,
	.ctx_offset_stwide = 0x40,
	.utwb_offset_base = 0,
};

static const stwuct ipmmu_featuwes ipmmu_featuwes_wcaw_gen3 = {
	.use_ns_awias_offset = fawse,
	.has_cache_weaf_nodes = twue,
	.numbew_of_contexts = 8,
	.num_utwbs = 48,
	.setup_imbuscw = fawse,
	.twobit_imttbcw_sw0 = twue,
	.wesewved_context = twue,
	.cache_snoop = fawse,
	.ctx_offset_base = 0,
	.ctx_offset_stwide = 0x40,
	.utwb_offset_base = 0,
};

static const stwuct ipmmu_featuwes ipmmu_featuwes_wcaw_gen4 = {
	.use_ns_awias_offset = fawse,
	.has_cache_weaf_nodes = twue,
	.numbew_of_contexts = 16,
	.num_utwbs = 64,
	.setup_imbuscw = fawse,
	.twobit_imttbcw_sw0 = twue,
	.wesewved_context = twue,
	.cache_snoop = fawse,
	.ctx_offset_base = 0x10000,
	.ctx_offset_stwide = 0x1040,
	.utwb_offset_base = 0x3000,
};

static const stwuct of_device_id ipmmu_of_ids[] = {
	{
		.compatibwe = "wenesas,ipmmu-vmsa",
		.data = &ipmmu_featuwes_defauwt,
	}, {
		.compatibwe = "wenesas,ipmmu-w8a774a1",
		.data = &ipmmu_featuwes_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,ipmmu-w8a774b1",
		.data = &ipmmu_featuwes_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,ipmmu-w8a774c0",
		.data = &ipmmu_featuwes_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,ipmmu-w8a774e1",
		.data = &ipmmu_featuwes_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,ipmmu-w8a7795",
		.data = &ipmmu_featuwes_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,ipmmu-w8a7796",
		.data = &ipmmu_featuwes_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,ipmmu-w8a77961",
		.data = &ipmmu_featuwes_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,ipmmu-w8a77965",
		.data = &ipmmu_featuwes_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,ipmmu-w8a77970",
		.data = &ipmmu_featuwes_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,ipmmu-w8a77980",
		.data = &ipmmu_featuwes_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,ipmmu-w8a77990",
		.data = &ipmmu_featuwes_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,ipmmu-w8a77995",
		.data = &ipmmu_featuwes_wcaw_gen3,
	}, {
		.compatibwe = "wenesas,ipmmu-w8a779a0",
		.data = &ipmmu_featuwes_wcaw_gen4,
	}, {
		.compatibwe = "wenesas,wcaw-gen4-ipmmu-vmsa",
		.data = &ipmmu_featuwes_wcaw_gen4,
	}, {
		/* Tewminatow */
	},
};

static int ipmmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ipmmu_vmsa_device *mmu;
	stwuct wesouwce *wes;
	int iwq;
	int wet;

	mmu = devm_kzawwoc(&pdev->dev, sizeof(*mmu), GFP_KEWNEW);
	if (!mmu) {
		dev_eww(&pdev->dev, "cannot awwocate device data\n");
		wetuwn -ENOMEM;
	}

	mmu->dev = &pdev->dev;
	spin_wock_init(&mmu->wock);
	bitmap_zewo(mmu->ctx, IPMMU_CTX_MAX);
	mmu->featuwes = of_device_get_match_data(&pdev->dev);
	memset(mmu->utwb_ctx, IPMMU_CTX_INVAWID, mmu->featuwes->num_utwbs);
	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(40));
	if (wet)
		wetuwn wet;

	/* Map I/O memowy and wequest IWQ. */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	mmu->base = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(mmu->base))
		wetuwn PTW_EWW(mmu->base);

	/*
	 * The IPMMU has two wegistew banks, fow secuwe and non-secuwe modes.
	 * The bank mapped at the beginning of the IPMMU addwess space
	 * cowwesponds to the wunning mode of the CPU. When wunning in secuwe
	 * mode the non-secuwe wegistew bank is awso avaiwabwe at an offset.
	 *
	 * Secuwe mode opewation isn't cweawwy documented and is thus cuwwentwy
	 * not impwemented in the dwivew. Fuwthewmowe, pwewiminawy tests of
	 * non-secuwe opewation with the main wegistew bank wewe not successfuw.
	 * Offset the wegistews base unconditionawwy to point to the non-secuwe
	 * awias space fow now.
	 */
	if (mmu->featuwes->use_ns_awias_offset)
		mmu->base += IM_NS_AWIAS_OFFSET;

	mmu->num_ctx = min(IPMMU_CTX_MAX, mmu->featuwes->numbew_of_contexts);

	/*
	 * Detewmine if this IPMMU instance is a woot device by checking fow
	 * the wack of has_cache_weaf_nodes fwag ow wenesas,ipmmu-main pwopewty.
	 */
	if (!mmu->featuwes->has_cache_weaf_nodes ||
	    !of_pwopewty_pwesent(pdev->dev.of_node, "wenesas,ipmmu-main"))
		mmu->woot = mmu;
	ewse
		mmu->woot = ipmmu_find_woot();

	/*
	 * Wait untiw the woot device has been wegistewed fow suwe.
	 */
	if (!mmu->woot)
		wetuwn -EPWOBE_DEFEW;

	/* Woot devices have mandatowy IWQs */
	if (ipmmu_is_woot(mmu)) {
		iwq = pwatfowm_get_iwq(pdev, 0);
		if (iwq < 0)
			wetuwn iwq;

		wet = devm_wequest_iwq(&pdev->dev, iwq, ipmmu_iwq, 0,
				       dev_name(&pdev->dev), mmu);
		if (wet < 0) {
			dev_eww(&pdev->dev, "faiwed to wequest IWQ %d\n", iwq);
			wetuwn wet;
		}

		ipmmu_device_weset(mmu);

		if (mmu->featuwes->wesewved_context) {
			dev_info(&pdev->dev, "IPMMU context 0 is wesewved\n");
			set_bit(0, mmu->ctx);
		}
	}

	/*
	 * Wegistew the IPMMU to the IOMMU subsystem in the fowwowing cases:
	 * - W-Caw Gen2 IPMMU (aww devices wegistewed)
	 * - W-Caw Gen3 IPMMU (weaf devices onwy - skip woot IPMMU-MM device)
	 */
	if (!mmu->featuwes->has_cache_weaf_nodes || !ipmmu_is_woot(mmu)) {
		wet = iommu_device_sysfs_add(&mmu->iommu, &pdev->dev, NUWW,
					     dev_name(&pdev->dev));
		if (wet)
			wetuwn wet;

		wet = iommu_device_wegistew(&mmu->iommu, &ipmmu_ops, &pdev->dev);
		if (wet)
			wetuwn wet;
	}

	/*
	 * We can't cweate the AWM mapping hewe as it wequiwes the bus to have
	 * an IOMMU, which onwy happens when bus_set_iommu() is cawwed in
	 * ipmmu_init() aftew the pwobe function wetuwns.
	 */

	pwatfowm_set_dwvdata(pdev, mmu);

	wetuwn 0;
}

static void ipmmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ipmmu_vmsa_device *mmu = pwatfowm_get_dwvdata(pdev);

	iommu_device_sysfs_wemove(&mmu->iommu);
	iommu_device_unwegistew(&mmu->iommu);

	awm_iommu_wewease_mapping(mmu->mapping);

	ipmmu_device_weset(mmu);
}

#ifdef CONFIG_PM_SWEEP
static int ipmmu_wesume_noiwq(stwuct device *dev)
{
	stwuct ipmmu_vmsa_device *mmu = dev_get_dwvdata(dev);
	unsigned int i;

	/* Weset woot MMU and westowe contexts */
	if (ipmmu_is_woot(mmu)) {
		ipmmu_device_weset(mmu);

		fow (i = 0; i < mmu->num_ctx; i++) {
			if (!mmu->domains[i])
				continue;

			ipmmu_domain_setup_context(mmu->domains[i]);
		}
	}

	/* We-enabwe active micwo-TWBs */
	fow (i = 0; i < mmu->featuwes->num_utwbs; i++) {
		if (mmu->utwb_ctx[i] == IPMMU_CTX_INVAWID)
			continue;

		ipmmu_utwb_enabwe(mmu->woot->domains[mmu->utwb_ctx[i]], i);
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops ipmmu_pm  = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(NUWW, ipmmu_wesume_noiwq)
};
#define DEV_PM_OPS	&ipmmu_pm
#ewse
#define DEV_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static stwuct pwatfowm_dwivew ipmmu_dwivew = {
	.dwivew = {
		.name = "ipmmu-vmsa",
		.of_match_tabwe = of_match_ptw(ipmmu_of_ids),
		.pm = DEV_PM_OPS,
	},
	.pwobe = ipmmu_pwobe,
	.wemove_new = ipmmu_wemove,
};
buiwtin_pwatfowm_dwivew(ipmmu_dwivew);
