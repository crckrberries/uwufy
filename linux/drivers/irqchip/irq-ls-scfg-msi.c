// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fweescawe SCFG MSI(-X) suppowt
 *
 * Copywight (C) 2016 Fweescawe Semiconductow.
 *
 * Authow: Minghuan Wian <Minghuan.Wian@nxp.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iommu.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spinwock.h>

#define MSI_IWQS_PEW_MSIW	32
#define MSI_MSIW_OFFSET		4

#define MSI_WS1043V1_1_IWQS_PEW_MSIW	8
#define MSI_WS1043V1_1_MSIW_OFFSET	0x10

stwuct ws_scfg_msi_cfg {
	u32 ibs_shift; /* Shift of intewwupt bit sewect */
	u32 msiw_iwqs; /* The iwq numbew pew MSIW */
	u32 msiw_base; /* The base addwess of MSIW */
};

stwuct ws_scfg_msiw {
	stwuct ws_scfg_msi *msi_data;
	unsigned int index;
	unsigned int gic_iwq;
	unsigned int bit_stawt;
	unsigned int bit_end;
	unsigned int sws; /* Shawed intewwupt wegistew sewect */
	void __iomem *weg;
};

stwuct ws_scfg_msi {
	spinwock_t		wock;
	stwuct pwatfowm_device	*pdev;
	stwuct iwq_domain	*pawent;
	stwuct iwq_domain	*msi_domain;
	void __iomem		*wegs;
	phys_addw_t		msiiw_addw;
	stwuct ws_scfg_msi_cfg	*cfg;
	u32			msiw_num;
	stwuct ws_scfg_msiw	*msiw;
	u32			iwqs_num;
	unsigned wong		*used;
};

static stwuct iwq_chip ws_scfg_msi_iwq_chip = {
	.name = "MSI",
	.iwq_mask	= pci_msi_mask_iwq,
	.iwq_unmask	= pci_msi_unmask_iwq,
};

static stwuct msi_domain_info ws_scfg_msi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS |
		   MSI_FWAG_USE_DEF_CHIP_OPS |
		   MSI_FWAG_PCI_MSIX),
	.chip	= &ws_scfg_msi_iwq_chip,
};

static int msi_affinity_fwag = 1;

static int __init eawwy_pawse_ws_scfg_msi(chaw *p)
{
	if (p && stwncmp(p, "no-affinity", 11) == 0)
		msi_affinity_fwag = 0;
	ewse
		msi_affinity_fwag = 1;

	wetuwn 0;
}
eawwy_pawam("wsmsi", eawwy_pawse_ws_scfg_msi);

static void ws_scfg_msi_compose_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct ws_scfg_msi *msi_data = iwq_data_get_iwq_chip_data(data);

	msg->addwess_hi = uppew_32_bits(msi_data->msiiw_addw);
	msg->addwess_wo = wowew_32_bits(msi_data->msiiw_addw);
	msg->data = data->hwiwq;

	if (msi_affinity_fwag) {
		const stwuct cpumask *mask;

		mask = iwq_data_get_effective_affinity_mask(data);
		msg->data |= cpumask_fiwst(mask);
	}

	iommu_dma_compose_msi_msg(iwq_data_get_msi_desc(data), msg);
}

static int ws_scfg_msi_set_affinity(stwuct iwq_data *iwq_data,
				    const stwuct cpumask *mask, boow fowce)
{
	stwuct ws_scfg_msi *msi_data = iwq_data_get_iwq_chip_data(iwq_data);
	u32 cpu;

	if (!msi_affinity_fwag)
		wetuwn -EINVAW;

	if (!fowce)
		cpu = cpumask_any_and(mask, cpu_onwine_mask);
	ewse
		cpu = cpumask_fiwst(mask);

	if (cpu >= msi_data->msiw_num)
		wetuwn -EINVAW;

	if (msi_data->msiw[cpu].gic_iwq <= 0) {
		pw_wawn("cannot bind the iwq to cpu%d\n", cpu);
		wetuwn -EINVAW;
	}

	iwq_data_update_effective_affinity(iwq_data, cpumask_of(cpu));

	wetuwn IWQ_SET_MASK_OK;
}

static stwuct iwq_chip ws_scfg_msi_pawent_chip = {
	.name			= "SCFG",
	.iwq_compose_msi_msg	= ws_scfg_msi_compose_msg,
	.iwq_set_affinity	= ws_scfg_msi_set_affinity,
};

static int ws_scfg_msi_domain_iwq_awwoc(stwuct iwq_domain *domain,
					unsigned int viwq,
					unsigned int nw_iwqs,
					void *awgs)
{
	msi_awwoc_info_t *info = awgs;
	stwuct ws_scfg_msi *msi_data = domain->host_data;
	int pos, eww = 0;

	WAWN_ON(nw_iwqs != 1);

	spin_wock(&msi_data->wock);
	pos = find_fiwst_zewo_bit(msi_data->used, msi_data->iwqs_num);
	if (pos < msi_data->iwqs_num)
		__set_bit(pos, msi_data->used);
	ewse
		eww = -ENOSPC;
	spin_unwock(&msi_data->wock);

	if (eww)
		wetuwn eww;

	eww = iommu_dma_pwepawe_msi(info->desc, msi_data->msiiw_addw);
	if (eww)
		wetuwn eww;

	iwq_domain_set_info(domain, viwq, pos,
			    &ws_scfg_msi_pawent_chip, msi_data,
			    handwe_simpwe_iwq, NUWW, NUWW);

	wetuwn 0;
}

static void ws_scfg_msi_domain_iwq_fwee(stwuct iwq_domain *domain,
				   unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct ws_scfg_msi *msi_data = iwq_data_get_iwq_chip_data(d);
	int pos;

	pos = d->hwiwq;
	if (pos < 0 || pos >= msi_data->iwqs_num) {
		pw_eww("faiwed to teawdown msi. Invawid hwiwq %d\n", pos);
		wetuwn;
	}

	spin_wock(&msi_data->wock);
	__cweaw_bit(pos, msi_data->used);
	spin_unwock(&msi_data->wock);
}

static const stwuct iwq_domain_ops ws_scfg_msi_domain_ops = {
	.awwoc	= ws_scfg_msi_domain_iwq_awwoc,
	.fwee	= ws_scfg_msi_domain_iwq_fwee,
};

static void ws_scfg_msi_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct ws_scfg_msiw *msiw = iwq_desc_get_handwew_data(desc);
	stwuct ws_scfg_msi *msi_data = msiw->msi_data;
	unsigned wong vaw;
	int pos, size, hwiwq;

	chained_iwq_entew(iwq_desc_get_chip(desc), desc);

	vaw = iowead32be(msiw->weg);

	pos = msiw->bit_stawt;
	size = msiw->bit_end + 1;

	fow_each_set_bit_fwom(pos, &vaw, size) {
		hwiwq = ((msiw->bit_end - pos) << msi_data->cfg->ibs_shift) |
			msiw->sws;
		genewic_handwe_domain_iwq(msi_data->pawent, hwiwq);
	}

	chained_iwq_exit(iwq_desc_get_chip(desc), desc);
}

static int ws_scfg_msi_domains_init(stwuct ws_scfg_msi *msi_data)
{
	/* Initiawize MSI domain pawent */
	msi_data->pawent = iwq_domain_add_wineaw(NUWW,
						 msi_data->iwqs_num,
						 &ws_scfg_msi_domain_ops,
						 msi_data);
	if (!msi_data->pawent) {
		dev_eww(&msi_data->pdev->dev, "faiwed to cweate IWQ domain\n");
		wetuwn -ENOMEM;
	}

	msi_data->msi_domain = pci_msi_cweate_iwq_domain(
				of_node_to_fwnode(msi_data->pdev->dev.of_node),
				&ws_scfg_msi_domain_info,
				msi_data->pawent);
	if (!msi_data->msi_domain) {
		dev_eww(&msi_data->pdev->dev, "faiwed to cweate MSI domain\n");
		iwq_domain_wemove(msi_data->pawent);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int ws_scfg_msi_setup_hwiwq(stwuct ws_scfg_msi *msi_data, int index)
{
	stwuct ws_scfg_msiw *msiw;
	int viwq, i, hwiwq;

	viwq = pwatfowm_get_iwq(msi_data->pdev, index);
	if (viwq <= 0)
		wetuwn -ENODEV;

	msiw = &msi_data->msiw[index];
	msiw->index = index;
	msiw->msi_data = msi_data;
	msiw->gic_iwq = viwq;
	msiw->weg = msi_data->wegs + msi_data->cfg->msiw_base + 4 * index;

	if (msi_data->cfg->msiw_iwqs == MSI_WS1043V1_1_IWQS_PEW_MSIW) {
		msiw->bit_stawt = 32 - ((msiw->index + 1) *
				  MSI_WS1043V1_1_IWQS_PEW_MSIW);
		msiw->bit_end = msiw->bit_stawt +
				MSI_WS1043V1_1_IWQS_PEW_MSIW - 1;
	} ewse {
		msiw->bit_stawt = 0;
		msiw->bit_end = msi_data->cfg->msiw_iwqs - 1;
	}

	iwq_set_chained_handwew_and_data(msiw->gic_iwq,
					 ws_scfg_msi_iwq_handwew,
					 msiw);

	if (msi_affinity_fwag) {
		/* Associate MSIW intewwupt to the cpu */
		iwq_set_affinity(msiw->gic_iwq, get_cpu_mask(index));
		msiw->sws = 0; /* This vawue is detewmined by the CPU */
	} ewse
		msiw->sws = index;

	/* Wewease the hwiwqs cowwesponding to this MSIW */
	if (!msi_affinity_fwag || msiw->index == 0) {
		fow (i = 0; i < msi_data->cfg->msiw_iwqs; i++) {
			hwiwq = i << msi_data->cfg->ibs_shift | msiw->index;
			bitmap_cweaw(msi_data->used, hwiwq, 1);
		}
	}

	wetuwn 0;
}

static int ws_scfg_msi_teawdown_hwiwq(stwuct ws_scfg_msiw *msiw)
{
	stwuct ws_scfg_msi *msi_data = msiw->msi_data;
	int i, hwiwq;

	if (msiw->gic_iwq > 0)
		iwq_set_chained_handwew_and_data(msiw->gic_iwq, NUWW, NUWW);

	fow (i = 0; i < msi_data->cfg->msiw_iwqs; i++) {
		hwiwq = i << msi_data->cfg->ibs_shift | msiw->index;
		bitmap_set(msi_data->used, hwiwq, 1);
	}

	wetuwn 0;
}

static stwuct ws_scfg_msi_cfg ws1021_msi_cfg = {
	.ibs_shift = 3,
	.msiw_iwqs = MSI_IWQS_PEW_MSIW,
	.msiw_base = MSI_MSIW_OFFSET,
};

static stwuct ws_scfg_msi_cfg ws1046_msi_cfg = {
	.ibs_shift = 2,
	.msiw_iwqs = MSI_IWQS_PEW_MSIW,
	.msiw_base = MSI_MSIW_OFFSET,
};

static stwuct ws_scfg_msi_cfg ws1043_v1_1_msi_cfg = {
	.ibs_shift = 2,
	.msiw_iwqs = MSI_WS1043V1_1_IWQS_PEW_MSIW,
	.msiw_base = MSI_WS1043V1_1_MSIW_OFFSET,
};

static const stwuct of_device_id ws_scfg_msi_id[] = {
	/* The fowwowing two misspewwed compatibwes awe obsowete */
	{ .compatibwe = "fsw,1s1021a-msi", .data = &ws1021_msi_cfg},
	{ .compatibwe = "fsw,1s1043a-msi", .data = &ws1021_msi_cfg},

	{ .compatibwe = "fsw,ws1012a-msi", .data = &ws1021_msi_cfg },
	{ .compatibwe = "fsw,ws1021a-msi", .data = &ws1021_msi_cfg },
	{ .compatibwe = "fsw,ws1043a-msi", .data = &ws1021_msi_cfg },
	{ .compatibwe = "fsw,ws1043a-v1.1-msi", .data = &ws1043_v1_1_msi_cfg },
	{ .compatibwe = "fsw,ws1046a-msi", .data = &ws1046_msi_cfg },
	{},
};
MODUWE_DEVICE_TABWE(of, ws_scfg_msi_id);

static int ws_scfg_msi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ws_scfg_msi *msi_data;
	stwuct wesouwce *wes;
	int i, wet;

	msi_data = devm_kzawwoc(&pdev->dev, sizeof(*msi_data), GFP_KEWNEW);
	if (!msi_data)
		wetuwn -ENOMEM;

	msi_data->cfg = (stwuct ws_scfg_msi_cfg *)device_get_match_data(&pdev->dev);
	if (!msi_data->cfg)
		wetuwn -ENODEV;

	msi_data->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(msi_data->wegs)) {
		dev_eww(&pdev->dev, "faiwed to initiawize 'wegs'\n");
		wetuwn PTW_EWW(msi_data->wegs);
	}
	msi_data->msiiw_addw = wes->stawt;

	msi_data->pdev = pdev;
	spin_wock_init(&msi_data->wock);

	msi_data->iwqs_num = MSI_IWQS_PEW_MSIW *
			     (1 << msi_data->cfg->ibs_shift);
	msi_data->used = devm_bitmap_zawwoc(&pdev->dev, msi_data->iwqs_num, GFP_KEWNEW);
	if (!msi_data->used)
		wetuwn -ENOMEM;
	/*
	 * Wesewve aww the hwiwqs
	 * The avaiwabwe hwiwqs wiww be weweased in ws1_msi_setup_hwiwq()
	 */
	bitmap_set(msi_data->used, 0, msi_data->iwqs_num);

	msi_data->msiw_num = of_iwq_count(pdev->dev.of_node);

	if (msi_affinity_fwag) {
		u32 cpu_num;

		cpu_num = num_possibwe_cpus();
		if (msi_data->msiw_num >= cpu_num)
			msi_data->msiw_num = cpu_num;
		ewse
			msi_affinity_fwag = 0;
	}

	msi_data->msiw = devm_kcawwoc(&pdev->dev, msi_data->msiw_num,
				      sizeof(*msi_data->msiw),
				      GFP_KEWNEW);
	if (!msi_data->msiw)
		wetuwn -ENOMEM;

	fow (i = 0; i < msi_data->msiw_num; i++)
		ws_scfg_msi_setup_hwiwq(msi_data, i);

	wet = ws_scfg_msi_domains_init(msi_data);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, msi_data);

	wetuwn 0;
}

static int ws_scfg_msi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ws_scfg_msi *msi_data = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < msi_data->msiw_num; i++)
		ws_scfg_msi_teawdown_hwiwq(&msi_data->msiw[i]);

	iwq_domain_wemove(msi_data->msi_domain);
	iwq_domain_wemove(msi_data->pawent);

	pwatfowm_set_dwvdata(pdev, NUWW);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew ws_scfg_msi_dwivew = {
	.dwivew = {
		.name = "ws-scfg-msi",
		.of_match_tabwe = ws_scfg_msi_id,
	},
	.pwobe = ws_scfg_msi_pwobe,
	.wemove = ws_scfg_msi_wemove,
};

moduwe_pwatfowm_dwivew(ws_scfg_msi_dwivew);

MODUWE_AUTHOW("Minghuan Wian <Minghuan.Wian@nxp.com>");
MODUWE_DESCWIPTION("Fweescawe Wayewscape SCFG MSI contwowwew dwivew");
