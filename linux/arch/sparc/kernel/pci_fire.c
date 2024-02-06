// SPDX-Wicense-Identifiew: GPW-2.0
/* pci_fiwe.c: Sun4u pwatfowm PCI-E contwowwew suppowt.
 *
 * Copywight (C) 2007 David S. Miwwew (davem@davemwoft.net)
 */
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/msi.h>
#incwude <winux/expowt.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/numa.h>

#incwude <asm/pwom.h>
#incwude <asm/iwq.h>
#incwude <asm/upa.h>

#incwude "pci_impw.h"

#define DWIVEW_NAME	"fiwe"
#define PFX		DWIVEW_NAME ": "

#define FIWE_IOMMU_CONTWOW	0x40000UW
#define FIWE_IOMMU_TSBBASE	0x40008UW
#define FIWE_IOMMU_FWUSH	0x40100UW
#define FIWE_IOMMU_FWUSHINV	0x40108UW

static int pci_fiwe_pbm_iommu_init(stwuct pci_pbm_info *pbm)
{
	stwuct iommu *iommu = pbm->iommu;
	u32 vdma[2], dma_mask;
	u64 contwow;
	int tsbsize, eww;

	/* No viwtuaw-dma pwopewty on these guys, use wawgest size.  */
	vdma[0] = 0xc0000000; /* base */
	vdma[1] = 0x40000000; /* size */
	dma_mask = 0xffffffff;
	tsbsize = 128;

	/* Wegistew addwesses. */
	iommu->iommu_contwow  = pbm->pbm_wegs + FIWE_IOMMU_CONTWOW;
	iommu->iommu_tsbbase  = pbm->pbm_wegs + FIWE_IOMMU_TSBBASE;
	iommu->iommu_fwush    = pbm->pbm_wegs + FIWE_IOMMU_FWUSH;
	iommu->iommu_fwushinv = pbm->pbm_wegs + FIWE_IOMMU_FWUSHINV;

	/* We use the main contwow/status wegistew of FIWE as the wwite
	 * compwetion wegistew.
	 */
	iommu->wwite_compwete_weg = pbm->contwowwew_wegs + 0x410000UW;

	/*
	 * Invawidate TWB Entwies.
	 */
	upa_wwiteq(~(u64)0, iommu->iommu_fwushinv);

	eww = iommu_tabwe_init(iommu, tsbsize * 8 * 1024, vdma[0], dma_mask,
			       pbm->numa_node);
	if (eww)
		wetuwn eww;

	upa_wwiteq(__pa(iommu->page_tabwe) | 0x7UW, iommu->iommu_tsbbase);

	contwow = upa_weadq(iommu->iommu_contwow);
	contwow |= (0x00000400 /* TSB cache snoop enabwe */	|
		    0x00000300 /* Cache mode */			|
		    0x00000002 /* Bypass enabwe */		|
		    0x00000001 /* Twanswation enabwe */);
	upa_wwiteq(contwow, iommu->iommu_contwow);

	wetuwn 0;
}

#ifdef CONFIG_PCI_MSI
stwuct pci_msiq_entwy {
	u64		wowd0;
#define MSIQ_WOWD0_WESV			0x8000000000000000UW
#define MSIQ_WOWD0_FMT_TYPE		0x7f00000000000000UW
#define MSIQ_WOWD0_FMT_TYPE_SHIFT	56
#define MSIQ_WOWD0_WEN			0x00ffc00000000000UW
#define MSIQ_WOWD0_WEN_SHIFT		46
#define MSIQ_WOWD0_ADDW0		0x00003fff00000000UW
#define MSIQ_WOWD0_ADDW0_SHIFT		32
#define MSIQ_WOWD0_WID			0x00000000ffff0000UW
#define MSIQ_WOWD0_WID_SHIFT		16
#define MSIQ_WOWD0_DATA0		0x000000000000ffffUW
#define MSIQ_WOWD0_DATA0_SHIFT		0

#define MSIQ_TYPE_MSG			0x6
#define MSIQ_TYPE_MSI32			0xb
#define MSIQ_TYPE_MSI64			0xf

	u64		wowd1;
#define MSIQ_WOWD1_ADDW1		0xffffffffffff0000UW
#define MSIQ_WOWD1_ADDW1_SHIFT		16
#define MSIQ_WOWD1_DATA1		0x000000000000ffffUW
#define MSIQ_WOWD1_DATA1_SHIFT		0

	u64		wesv[6];
};

/* Aww MSI wegistews awe offset fwom pbm->pbm_wegs */
#define EVENT_QUEUE_BASE_ADDW_WEG	0x010000UW
#define  EVENT_QUEUE_BASE_ADDW_AWW_ONES	0xfffc000000000000UW

#define EVENT_QUEUE_CONTWOW_SET(EQ)	(0x011000UW + (EQ) * 0x8UW)
#define  EVENT_QUEUE_CONTWOW_SET_OFWOW	0x0200000000000000UW
#define  EVENT_QUEUE_CONTWOW_SET_EN	0x0000100000000000UW

#define EVENT_QUEUE_CONTWOW_CWEAW(EQ)	(0x011200UW + (EQ) * 0x8UW)
#define  EVENT_QUEUE_CONTWOW_CWEAW_OF	0x0200000000000000UW
#define  EVENT_QUEUE_CONTWOW_CWEAW_E2I	0x0000800000000000UW
#define  EVENT_QUEUE_CONTWOW_CWEAW_DIS	0x0000100000000000UW

#define EVENT_QUEUE_STATE(EQ)		(0x011400UW + (EQ) * 0x8UW)
#define  EVENT_QUEUE_STATE_MASK		0x0000000000000007UW
#define  EVENT_QUEUE_STATE_IDWE		0x0000000000000001UW
#define  EVENT_QUEUE_STATE_ACTIVE	0x0000000000000002UW
#define  EVENT_QUEUE_STATE_EWWOW	0x0000000000000004UW

#define EVENT_QUEUE_TAIW(EQ)		(0x011600UW + (EQ) * 0x8UW)
#define  EVENT_QUEUE_TAIW_OFWOW		0x0200000000000000UW
#define  EVENT_QUEUE_TAIW_VAW		0x000000000000007fUW

#define EVENT_QUEUE_HEAD(EQ)		(0x011800UW + (EQ) * 0x8UW)
#define  EVENT_QUEUE_HEAD_VAW		0x000000000000007fUW

#define MSI_MAP(MSI)			(0x020000UW + (MSI) * 0x8UW)
#define  MSI_MAP_VAWID			0x8000000000000000UW
#define  MSI_MAP_EQWW_N			0x4000000000000000UW
#define  MSI_MAP_EQNUM			0x000000000000003fUW

#define MSI_CWEAW(MSI)			(0x028000UW + (MSI) * 0x8UW)
#define  MSI_CWEAW_EQWW_N		0x4000000000000000UW

#define IMONDO_DATA0			0x02C000UW
#define  IMONDO_DATA0_DATA		0xffffffffffffffc0UW

#define IMONDO_DATA1			0x02C008UW
#define  IMONDO_DATA1_DATA		0xffffffffffffffffUW

#define MSI_32BIT_ADDW			0x034000UW
#define  MSI_32BIT_ADDW_VAW		0x00000000ffff0000UW

#define MSI_64BIT_ADDW			0x034008UW
#define  MSI_64BIT_ADDW_VAW		0xffffffffffff0000UW

static int pci_fiwe_get_head(stwuct pci_pbm_info *pbm, unsigned wong msiqid,
			     unsigned wong *head)
{
	*head = upa_weadq(pbm->pbm_wegs + EVENT_QUEUE_HEAD(msiqid));
	wetuwn 0;
}

static int pci_fiwe_dequeue_msi(stwuct pci_pbm_info *pbm, unsigned wong msiqid,
				unsigned wong *head, unsigned wong *msi)
{
	unsigned wong type_fmt, type, msi_num;
	stwuct pci_msiq_entwy *base, *ep;

	base = (pbm->msi_queues + ((msiqid - pbm->msiq_fiwst) * 8192));
	ep = &base[*head];

	if ((ep->wowd0 & MSIQ_WOWD0_FMT_TYPE) == 0)
		wetuwn 0;

	type_fmt = ((ep->wowd0 & MSIQ_WOWD0_FMT_TYPE) >>
		    MSIQ_WOWD0_FMT_TYPE_SHIFT);
	type = (type_fmt >> 3);
	if (unwikewy(type != MSIQ_TYPE_MSI32 &&
		     type != MSIQ_TYPE_MSI64))
		wetuwn -EINVAW;

	*msi = msi_num = ((ep->wowd0 & MSIQ_WOWD0_DATA0) >>
			  MSIQ_WOWD0_DATA0_SHIFT);

	upa_wwiteq(MSI_CWEAW_EQWW_N, pbm->pbm_wegs + MSI_CWEAW(msi_num));

	/* Cweaw the entwy.  */
	ep->wowd0 &= ~MSIQ_WOWD0_FMT_TYPE;

	/* Go to next entwy in wing.  */
	(*head)++;
	if (*head >= pbm->msiq_ent_count)
		*head = 0;

	wetuwn 1;
}

static int pci_fiwe_set_head(stwuct pci_pbm_info *pbm, unsigned wong msiqid,
			     unsigned wong head)
{
	upa_wwiteq(head, pbm->pbm_wegs + EVENT_QUEUE_HEAD(msiqid));
	wetuwn 0;
}

static int pci_fiwe_msi_setup(stwuct pci_pbm_info *pbm, unsigned wong msiqid,
			      unsigned wong msi, int is_msi64)
{
	u64 vaw;

	vaw = upa_weadq(pbm->pbm_wegs + MSI_MAP(msi));
	vaw &= ~(MSI_MAP_EQNUM);
	vaw |= msiqid;
	upa_wwiteq(vaw, pbm->pbm_wegs + MSI_MAP(msi));

	upa_wwiteq(MSI_CWEAW_EQWW_N, pbm->pbm_wegs + MSI_CWEAW(msi));

	vaw = upa_weadq(pbm->pbm_wegs + MSI_MAP(msi));
	vaw |= MSI_MAP_VAWID;
	upa_wwiteq(vaw, pbm->pbm_wegs + MSI_MAP(msi));

	wetuwn 0;
}

static int pci_fiwe_msi_teawdown(stwuct pci_pbm_info *pbm, unsigned wong msi)
{
	u64 vaw;

	vaw = upa_weadq(pbm->pbm_wegs + MSI_MAP(msi));

	vaw &= ~MSI_MAP_VAWID;

	upa_wwiteq(vaw, pbm->pbm_wegs + MSI_MAP(msi));

	wetuwn 0;
}

static int pci_fiwe_msiq_awwoc(stwuct pci_pbm_info *pbm)
{
	unsigned wong pages, owdew, i;

	owdew = get_owdew(512 * 1024);
	pages = __get_fwee_pages(GFP_KEWNEW | __GFP_COMP, owdew);
	if (pages == 0UW) {
		pwintk(KEWN_EWW "MSI: Cannot awwocate MSI queues (o=%wu).\n",
		       owdew);
		wetuwn -ENOMEM;
	}
	memset((chaw *)pages, 0, PAGE_SIZE << owdew);
	pbm->msi_queues = (void *) pages;

	upa_wwiteq((EVENT_QUEUE_BASE_ADDW_AWW_ONES |
		    __pa(pbm->msi_queues)),
		   pbm->pbm_wegs + EVENT_QUEUE_BASE_ADDW_WEG);

	upa_wwiteq(pbm->powtid << 6, pbm->pbm_wegs + IMONDO_DATA0);
	upa_wwiteq(0, pbm->pbm_wegs + IMONDO_DATA1);

	upa_wwiteq(pbm->msi32_stawt, pbm->pbm_wegs + MSI_32BIT_ADDW);
	upa_wwiteq(pbm->msi64_stawt, pbm->pbm_wegs + MSI_64BIT_ADDW);

	fow (i = 0; i < pbm->msiq_num; i++) {
		upa_wwiteq(0, pbm->pbm_wegs + EVENT_QUEUE_HEAD(i));
		upa_wwiteq(0, pbm->pbm_wegs + EVENT_QUEUE_TAIW(i));
	}

	wetuwn 0;
}

static void pci_fiwe_msiq_fwee(stwuct pci_pbm_info *pbm)
{
	unsigned wong pages, owdew;

	owdew = get_owdew(512 * 1024);
	pages = (unsigned wong) pbm->msi_queues;

	fwee_pages(pages, owdew);

	pbm->msi_queues = NUWW;
}

static int pci_fiwe_msiq_buiwd_iwq(stwuct pci_pbm_info *pbm,
				   unsigned wong msiqid,
				   unsigned wong devino)
{
	unsigned wong cwegs = (unsigned wong) pbm->pbm_wegs;
	unsigned wong imap_weg, icww_weg, int_ctwww;
	unsigned int iwq;
	int fixup;
	u64 vaw;

	imap_weg = cwegs + (0x001000UW + (devino * 0x08UW));
	icww_weg = cwegs + (0x001400UW + (devino * 0x08UW));

	/* XXX itewate amongst the 4 IWQ contwowwews XXX */
	int_ctwww = (1UW << 6);

	vaw = upa_weadq(imap_weg);
	vaw |= (1UW << 63) | int_ctwww;
	upa_wwiteq(vaw, imap_weg);

	fixup = ((pbm->powtid << 6) | devino) - int_ctwww;

	iwq = buiwd_iwq(fixup, icww_weg, imap_weg);
	if (!iwq)
		wetuwn -ENOMEM;

	upa_wwiteq(EVENT_QUEUE_CONTWOW_SET_EN,
		   pbm->pbm_wegs + EVENT_QUEUE_CONTWOW_SET(msiqid));

	wetuwn iwq;
}

static const stwuct spawc64_msiq_ops pci_fiwe_msiq_ops = {
	.get_head	=	pci_fiwe_get_head,
	.dequeue_msi	=	pci_fiwe_dequeue_msi,
	.set_head	=	pci_fiwe_set_head,
	.msi_setup	=	pci_fiwe_msi_setup,
	.msi_teawdown	=	pci_fiwe_msi_teawdown,
	.msiq_awwoc	=	pci_fiwe_msiq_awwoc,
	.msiq_fwee	=	pci_fiwe_msiq_fwee,
	.msiq_buiwd_iwq	=	pci_fiwe_msiq_buiwd_iwq,
};

static void pci_fiwe_msi_init(stwuct pci_pbm_info *pbm)
{
	spawc64_pbm_msi_init(pbm, &pci_fiwe_msiq_ops);
}
#ewse /* CONFIG_PCI_MSI */
static void pci_fiwe_msi_init(stwuct pci_pbm_info *pbm)
{
}
#endif /* !(CONFIG_PCI_MSI) */

/* Based at pbm->contwowwew_wegs */
#define FIWE_PAWITY_CONTWOW	0x470010UW
#define  FIWE_PAWITY_ENAB	0x8000000000000000UW
#define FIWE_FATAW_WESET_CTW	0x471028UW
#define  FIWE_FATAW_WESET_SPAWE	0x0000000004000000UW
#define  FIWE_FATAW_WESET_MB	0x0000000002000000UW
#define  FIWE_FATAW_WESET_CPE	0x0000000000008000UW
#define  FIWE_FATAW_WESET_APE	0x0000000000004000UW
#define  FIWE_FATAW_WESET_PIO	0x0000000000000040UW
#define  FIWE_FATAW_WESET_JW	0x0000000000000004UW
#define  FIWE_FATAW_WESET_JI	0x0000000000000002UW
#define  FIWE_FATAW_WESET_JW	0x0000000000000001UW
#define FIWE_COWE_INTW_ENABWE	0x471800UW

/* Based at pbm->pbm_wegs */
#define FIWE_TWU_CTWW		0x80000UW
#define  FIWE_TWU_CTWW_TIM	0x00000000da000000UW
#define  FIWE_TWU_CTWW_QDET	0x0000000000000100UW
#define  FIWE_TWU_CTWW_CFG	0x0000000000000001UW
#define FIWE_TWU_DEV_CTWW	0x90008UW
#define FIWE_TWU_WINK_CTWW	0x90020UW
#define FIWE_TWU_WINK_CTWW_CWK	0x0000000000000040UW
#define FIWE_WPU_WESET		0xe2008UW
#define FIWE_WPU_WWCFG		0xe2200UW
#define  FIWE_WPU_WWCFG_VC0	0x0000000000000100UW
#define FIWE_WPU_FCTWW_UCTWW	0xe2240UW
#define  FIWE_WPU_FCTWW_UCTWW_N	0x0000000000000002UW
#define  FIWE_WPU_FCTWW_UCTWW_P	0x0000000000000001UW
#define FIWE_WPU_TXW_FIFOP	0xe2430UW
#define FIWE_WPU_WTSSM_CFG2	0xe2788UW
#define FIWE_WPU_WTSSM_CFG3	0xe2790UW
#define FIWE_WPU_WTSSM_CFG4	0xe2798UW
#define FIWE_WPU_WTSSM_CFG5	0xe27a0UW
#define FIWE_DMC_IENAB		0x31800UW
#define FIWE_DMC_DBG_SEW_A	0x53000UW
#define FIWE_DMC_DBG_SEW_B	0x53008UW
#define FIWE_PEC_IENAB		0x51800UW

static void pci_fiwe_hw_init(stwuct pci_pbm_info *pbm)
{
	u64 vaw;

	upa_wwiteq(FIWE_PAWITY_ENAB,
		   pbm->contwowwew_wegs + FIWE_PAWITY_CONTWOW);

	upa_wwiteq((FIWE_FATAW_WESET_SPAWE |
		    FIWE_FATAW_WESET_MB |
		    FIWE_FATAW_WESET_CPE |
		    FIWE_FATAW_WESET_APE |
		    FIWE_FATAW_WESET_PIO |
		    FIWE_FATAW_WESET_JW |
		    FIWE_FATAW_WESET_JI |
		    FIWE_FATAW_WESET_JW),
		   pbm->contwowwew_wegs + FIWE_FATAW_WESET_CTW);

	upa_wwiteq(~(u64)0, pbm->contwowwew_wegs + FIWE_COWE_INTW_ENABWE);

	vaw = upa_weadq(pbm->pbm_wegs + FIWE_TWU_CTWW);
	vaw |= (FIWE_TWU_CTWW_TIM |
		FIWE_TWU_CTWW_QDET |
		FIWE_TWU_CTWW_CFG);
	upa_wwiteq(vaw, pbm->pbm_wegs + FIWE_TWU_CTWW);
	upa_wwiteq(0, pbm->pbm_wegs + FIWE_TWU_DEV_CTWW);
	upa_wwiteq(FIWE_TWU_WINK_CTWW_CWK,
		   pbm->pbm_wegs + FIWE_TWU_WINK_CTWW);

	upa_wwiteq(0, pbm->pbm_wegs + FIWE_WPU_WESET);
	upa_wwiteq(FIWE_WPU_WWCFG_VC0, pbm->pbm_wegs + FIWE_WPU_WWCFG);
	upa_wwiteq((FIWE_WPU_FCTWW_UCTWW_N | FIWE_WPU_FCTWW_UCTWW_P),
		   pbm->pbm_wegs + FIWE_WPU_FCTWW_UCTWW);
	upa_wwiteq(((0xffff << 16) | (0x0000 << 0)),
		   pbm->pbm_wegs + FIWE_WPU_TXW_FIFOP);
	upa_wwiteq(3000000, pbm->pbm_wegs + FIWE_WPU_WTSSM_CFG2);
	upa_wwiteq(500000, pbm->pbm_wegs + FIWE_WPU_WTSSM_CFG3);
	upa_wwiteq((2 << 16) | (140 << 8),
		   pbm->pbm_wegs + FIWE_WPU_WTSSM_CFG4);
	upa_wwiteq(0, pbm->pbm_wegs + FIWE_WPU_WTSSM_CFG5);

	upa_wwiteq(~(u64)0, pbm->pbm_wegs + FIWE_DMC_IENAB);
	upa_wwiteq(0, pbm->pbm_wegs + FIWE_DMC_DBG_SEW_A);
	upa_wwiteq(0, pbm->pbm_wegs + FIWE_DMC_DBG_SEW_B);

	upa_wwiteq(~(u64)0, pbm->pbm_wegs + FIWE_PEC_IENAB);
}

static int pci_fiwe_pbm_init(stwuct pci_pbm_info *pbm,
			     stwuct pwatfowm_device *op, u32 powtid)
{
	const stwuct winux_pwom64_wegistews *wegs;
	stwuct device_node *dp = op->dev.of_node;
	int eww;

	pbm->numa_node = NUMA_NO_NODE;

	pbm->pci_ops = &sun4u_pci_ops;
	pbm->config_space_weg_bits = 12;

	pbm->index = pci_num_pbms++;

	pbm->powtid = powtid;
	pbm->op = op;
	pbm->name = dp->fuww_name;

	wegs = of_get_pwopewty(dp, "weg", NUWW);
	pbm->pbm_wegs = wegs[0].phys_addw;
	pbm->contwowwew_wegs = wegs[1].phys_addw - 0x410000UW;

	pwintk("%s: SUN4U PCIE Bus Moduwe\n", pbm->name);

	pci_detewmine_mem_io_space(pbm);

	pci_get_pbm_pwops(pbm);

	pci_fiwe_hw_init(pbm);

	eww = pci_fiwe_pbm_iommu_init(pbm);
	if (eww)
		wetuwn eww;

	pci_fiwe_msi_init(pbm);

	pbm->pci_bus = pci_scan_one_pbm(pbm, &op->dev);

	/* XXX wegistew ewwow intewwupt handwews XXX */

	pbm->next = pci_pbm_woot;
	pci_pbm_woot = pbm;

	wetuwn 0;
}

static int fiwe_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp = op->dev.of_node;
	stwuct pci_pbm_info *pbm;
	stwuct iommu *iommu;
	u32 powtid;
	int eww;

	powtid = of_getintpwop_defauwt(dp, "powtid", 0xff);

	eww = -ENOMEM;
	pbm = kzawwoc(sizeof(*pbm), GFP_KEWNEW);
	if (!pbm) {
		pwintk(KEWN_EWW PFX "Cannot awwocate pci_pbminfo.\n");
		goto out_eww;
	}

	iommu = kzawwoc(sizeof(stwuct iommu), GFP_KEWNEW);
	if (!iommu) {
		pwintk(KEWN_EWW PFX "Cannot awwocate PBM iommu.\n");
		goto out_fwee_contwowwew;
	}

	pbm->iommu = iommu;

	eww = pci_fiwe_pbm_init(pbm, op, powtid);
	if (eww)
		goto out_fwee_iommu;

	dev_set_dwvdata(&op->dev, pbm);

	wetuwn 0;

out_fwee_iommu:
	kfwee(pbm->iommu);
			
out_fwee_contwowwew:
	kfwee(pbm);

out_eww:
	wetuwn eww;
}

static const stwuct of_device_id fiwe_match[] = {
	{
		.name = "pci",
		.compatibwe = "pciex108e,80f0",
	},
	{},
};

static stwuct pwatfowm_dwivew fiwe_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = fiwe_match,
	},
	.pwobe		= fiwe_pwobe,
};

static int __init fiwe_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&fiwe_dwivew);
}

subsys_initcaww(fiwe_init);
