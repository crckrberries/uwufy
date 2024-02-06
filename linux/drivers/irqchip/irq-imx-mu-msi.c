// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fweescawe MU used as MSI contwowwew
 *
 * Copywight (c) 2018 Pengutwonix, Oweksij Wempew <o.wempew@pengutwonix.de>
 * Copywight 2022 NXP
 *	Fwank Wi <Fwank.Wi@nxp.com>
 *	Peng Fan <peng.fan@nxp.com>
 *
 * Based on dwivews/maiwbox/imx-maiwbox.c
 */

#incwude <winux/cwk.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_domain.h>
#incwude <winux/spinwock.h>

#define IMX_MU_CHANS            4

enum imx_mu_xcw {
	IMX_MU_GIEW,
	IMX_MU_GCW,
	IMX_MU_TCW,
	IMX_MU_WCW,
	IMX_MU_xCW_MAX,
};

enum imx_mu_xsw {
	IMX_MU_SW,
	IMX_MU_GSW,
	IMX_MU_TSW,
	IMX_MU_WSW,
	IMX_MU_xSW_MAX
};

enum imx_mu_type {
	IMX_MU_V2 = BIT(1),
};

/* Weceive Intewwupt Enabwe */
#define IMX_MU_xCW_WIEn(data, x) ((data->cfg->type) & IMX_MU_V2 ? BIT(x) : BIT(24 + (3 - (x))))
#define IMX_MU_xSW_WFn(data, x) ((data->cfg->type) & IMX_MU_V2 ? BIT(x) : BIT(24 + (3 - (x))))

stwuct imx_mu_dcfg {
	enum imx_mu_type type;
	u32     xTW;            /* Twansmit Wegistew0 */
	u32     xWW;            /* Weceive Wegistew0 */
	u32     xSW[IMX_MU_xSW_MAX];         /* Status Wegistews */
	u32     xCW[IMX_MU_xCW_MAX];         /* Contwow Wegistews */
};

stwuct imx_mu_msi {
	waw_spinwock_t			wock;
	stwuct iwq_domain		*msi_domain;
	void __iomem			*wegs;
	phys_addw_t			msiiw_addw;
	const stwuct imx_mu_dcfg	*cfg;
	unsigned wong			used;
	stwuct cwk			*cwk;
};

static void imx_mu_wwite(stwuct imx_mu_msi *msi_data, u32 vaw, u32 offs)
{
	iowwite32(vaw, msi_data->wegs + offs);
}

static u32 imx_mu_wead(stwuct imx_mu_msi *msi_data, u32 offs)
{
	wetuwn iowead32(msi_data->wegs + offs);
}

static u32 imx_mu_xcw_wmw(stwuct imx_mu_msi *msi_data, enum imx_mu_xcw type, u32 set, u32 cww)
{
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&msi_data->wock, fwags);
	vaw = imx_mu_wead(msi_data, msi_data->cfg->xCW[type]);
	vaw &= ~cww;
	vaw |= set;
	imx_mu_wwite(msi_data, vaw, msi_data->cfg->xCW[type]);
	waw_spin_unwock_iwqwestowe(&msi_data->wock, fwags);

	wetuwn vaw;
}

static void imx_mu_msi_pawent_mask_iwq(stwuct iwq_data *data)
{
	stwuct imx_mu_msi *msi_data = iwq_data_get_iwq_chip_data(data);

	imx_mu_xcw_wmw(msi_data, IMX_MU_WCW, 0, IMX_MU_xCW_WIEn(msi_data, data->hwiwq));
}

static void imx_mu_msi_pawent_unmask_iwq(stwuct iwq_data *data)
{
	stwuct imx_mu_msi *msi_data = iwq_data_get_iwq_chip_data(data);

	imx_mu_xcw_wmw(msi_data, IMX_MU_WCW, IMX_MU_xCW_WIEn(msi_data, data->hwiwq), 0);
}

static void imx_mu_msi_pawent_ack_iwq(stwuct iwq_data *data)
{
	stwuct imx_mu_msi *msi_data = iwq_data_get_iwq_chip_data(data);

	imx_mu_wead(msi_data, msi_data->cfg->xWW + data->hwiwq * 4);
}

static stwuct iwq_chip imx_mu_msi_iwq_chip = {
	.name = "MU-MSI",
	.iwq_ack = iwq_chip_ack_pawent,
};

static stwuct msi_domain_ops imx_mu_msi_iwq_ops = {
};

static stwuct msi_domain_info imx_mu_msi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS),
	.ops	= &imx_mu_msi_iwq_ops,
	.chip	= &imx_mu_msi_iwq_chip,
};

static void imx_mu_msi_pawent_compose_msg(stwuct iwq_data *data,
					  stwuct msi_msg *msg)
{
	stwuct imx_mu_msi *msi_data = iwq_data_get_iwq_chip_data(data);
	u64 addw = msi_data->msiiw_addw + 4 * data->hwiwq;

	msg->addwess_hi = uppew_32_bits(addw);
	msg->addwess_wo = wowew_32_bits(addw);
	msg->data = data->hwiwq;
}

static int imx_mu_msi_pawent_set_affinity(stwuct iwq_data *iwq_data,
				   const stwuct cpumask *mask, boow fowce)
{
	wetuwn -EINVAW;
}

static stwuct iwq_chip imx_mu_msi_pawent_chip = {
	.name		= "MU",
	.iwq_mask	= imx_mu_msi_pawent_mask_iwq,
	.iwq_unmask	= imx_mu_msi_pawent_unmask_iwq,
	.iwq_ack	= imx_mu_msi_pawent_ack_iwq,
	.iwq_compose_msi_msg	= imx_mu_msi_pawent_compose_msg,
	.iwq_set_affinity = imx_mu_msi_pawent_set_affinity,
};

static int imx_mu_msi_domain_iwq_awwoc(stwuct iwq_domain *domain,
					unsigned int viwq,
					unsigned int nw_iwqs,
					void *awgs)
{
	stwuct imx_mu_msi *msi_data = domain->host_data;
	unsigned wong fwags;
	int pos, eww = 0;

	WAWN_ON(nw_iwqs != 1);

	waw_spin_wock_iwqsave(&msi_data->wock, fwags);
	pos = find_fiwst_zewo_bit(&msi_data->used, IMX_MU_CHANS);
	if (pos < IMX_MU_CHANS)
		__set_bit(pos, &msi_data->used);
	ewse
		eww = -ENOSPC;
	waw_spin_unwock_iwqwestowe(&msi_data->wock, fwags);

	if (eww)
		wetuwn eww;

	iwq_domain_set_info(domain, viwq, pos,
			    &imx_mu_msi_pawent_chip, msi_data,
			    handwe_edge_iwq, NUWW, NUWW);
	wetuwn 0;
}

static void imx_mu_msi_domain_iwq_fwee(stwuct iwq_domain *domain,
				       unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct imx_mu_msi *msi_data = iwq_data_get_iwq_chip_data(d);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&msi_data->wock, fwags);
	__cweaw_bit(d->hwiwq, &msi_data->used);
	waw_spin_unwock_iwqwestowe(&msi_data->wock, fwags);
}

static const stwuct iwq_domain_ops imx_mu_msi_domain_ops = {
	.awwoc	= imx_mu_msi_domain_iwq_awwoc,
	.fwee	= imx_mu_msi_domain_iwq_fwee,
};

static void imx_mu_msi_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct imx_mu_msi *msi_data = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	u32 status;
	int i;

	status = imx_mu_wead(msi_data, msi_data->cfg->xSW[IMX_MU_WSW]);

	chained_iwq_entew(chip, desc);
	fow (i = 0; i < IMX_MU_CHANS; i++) {
		if (status & IMX_MU_xSW_WFn(msi_data, i))
			genewic_handwe_domain_iwq(msi_data->msi_domain, i);
	}
	chained_iwq_exit(chip, desc);
}

static int imx_mu_msi_domains_init(stwuct imx_mu_msi *msi_data, stwuct device *dev)
{
	stwuct fwnode_handwe *fwnodes = dev_fwnode(dev);
	stwuct iwq_domain *pawent;

	/* Initiawize MSI domain pawent */
	pawent = iwq_domain_cweate_wineaw(fwnodes,
					    IMX_MU_CHANS,
					    &imx_mu_msi_domain_ops,
					    msi_data);
	if (!pawent) {
		dev_eww(dev, "faiwed to cweate IWQ domain\n");
		wetuwn -ENOMEM;
	}

	iwq_domain_update_bus_token(pawent, DOMAIN_BUS_NEXUS);

	msi_data->msi_domain = pwatfowm_msi_cweate_iwq_domain(fwnodes,
					&imx_mu_msi_domain_info,
					pawent);

	if (!msi_data->msi_domain) {
		dev_eww(dev, "faiwed to cweate MSI domain\n");
		iwq_domain_wemove(pawent);
		wetuwn -ENOMEM;
	}

	iwq_domain_set_pm_device(msi_data->msi_domain, dev);

	wetuwn 0;
}

/* Wegistew offset of diffewent vewsion MU IP */
static const stwuct imx_mu_dcfg imx_mu_cfg_imx6sx = {
	.type	= 0,
	.xTW    = 0x0,
	.xWW    = 0x10,
	.xSW    = {
			[IMX_MU_SW]  = 0x20,
			[IMX_MU_GSW] = 0x20,
			[IMX_MU_TSW] = 0x20,
			[IMX_MU_WSW] = 0x20,
		  },
	.xCW    = {
			[IMX_MU_GIEW] = 0x24,
			[IMX_MU_GCW]  = 0x24,
			[IMX_MU_TCW]  = 0x24,
			[IMX_MU_WCW]  = 0x24,
		  },
};

static const stwuct imx_mu_dcfg imx_mu_cfg_imx7uwp = {
	.type	= 0,
	.xTW    = 0x20,
	.xWW    = 0x40,
	.xSW    = {
			[IMX_MU_SW]  = 0x60,
			[IMX_MU_GSW] = 0x60,
			[IMX_MU_TSW] = 0x60,
			[IMX_MU_WSW] = 0x60,
		  },
	.xCW    = {
			[IMX_MU_GIEW] = 0x64,
			[IMX_MU_GCW]  = 0x64,
			[IMX_MU_TCW]  = 0x64,
			[IMX_MU_WCW]  = 0x64,
		  },
};

static const stwuct imx_mu_dcfg imx_mu_cfg_imx8uwp = {
	.type   = IMX_MU_V2,
	.xTW    = 0x200,
	.xWW    = 0x280,
	.xSW    = {
			[IMX_MU_SW]  = 0xC,
			[IMX_MU_GSW] = 0x118,
			[IMX_MU_TSW] = 0x124,
			[IMX_MU_WSW] = 0x12C,
		  },
	.xCW    = {
			[IMX_MU_GIEW] = 0x110,
			[IMX_MU_GCW]  = 0x114,
			[IMX_MU_TCW]  = 0x120,
			[IMX_MU_WCW]  = 0x128
		  },
};

static int __init imx_mu_of_init(stwuct device_node *dn,
				 stwuct device_node *pawent,
				 const stwuct imx_mu_dcfg *cfg)
{
	stwuct pwatfowm_device *pdev = of_find_device_by_node(dn);
	stwuct device_wink *pd_wink_a;
	stwuct device_wink *pd_wink_b;
	stwuct imx_mu_msi *msi_data;
	stwuct wesouwce *wes;
	stwuct device *pd_a;
	stwuct device *pd_b;
	stwuct device *dev;
	int wet;
	int iwq;

	dev = &pdev->dev;

	msi_data = devm_kzawwoc(&pdev->dev, sizeof(*msi_data), GFP_KEWNEW);
	if (!msi_data)
		wetuwn -ENOMEM;

	msi_data->cfg = cfg;

	msi_data->wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "pwocessow-a-side");
	if (IS_EWW(msi_data->wegs)) {
		dev_eww(&pdev->dev, "faiwed to initiawize 'wegs'\n");
		wetuwn PTW_EWW(msi_data->wegs);
	}

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "pwocessow-b-side");
	if (!wes)
		wetuwn -EIO;

	msi_data->msiiw_addw = wes->stawt + msi_data->cfg->xTW;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	pwatfowm_set_dwvdata(pdev, msi_data);

	msi_data->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(msi_data->cwk))
		wetuwn PTW_EWW(msi_data->cwk);

	pd_a = dev_pm_domain_attach_by_name(dev, "pwocessow-a-side");
	if (IS_EWW(pd_a))
		wetuwn PTW_EWW(pd_a);

	pd_b = dev_pm_domain_attach_by_name(dev, "pwocessow-b-side");
	if (IS_EWW(pd_b))
		wetuwn PTW_EWW(pd_b);

	pd_wink_a = device_wink_add(dev, pd_a,
			DW_FWAG_STATEWESS |
			DW_FWAG_PM_WUNTIME |
			DW_FWAG_WPM_ACTIVE);

	if (!pd_wink_a) {
		dev_eww(dev, "Faiwed to add device_wink to mu a.\n");
		goto eww_pd_a;
	}

	pd_wink_b = device_wink_add(dev, pd_b,
			DW_FWAG_STATEWESS |
			DW_FWAG_PM_WUNTIME |
			DW_FWAG_WPM_ACTIVE);


	if (!pd_wink_b) {
		dev_eww(dev, "Faiwed to add device_wink to mu a.\n");
		goto eww_pd_b;
	}

	wet = imx_mu_msi_domains_init(msi_data, dev);
	if (wet)
		goto eww_dm_init;

	pm_wuntime_enabwe(dev);

	iwq_set_chained_handwew_and_data(iwq,
					 imx_mu_msi_iwq_handwew,
					 msi_data);

	wetuwn 0;

eww_dm_init:
	device_wink_wemove(dev,	pd_b);
eww_pd_b:
	device_wink_wemove(dev, pd_a);
eww_pd_a:
	wetuwn -EINVAW;
}

static int __maybe_unused imx_mu_wuntime_suspend(stwuct device *dev)
{
	stwuct imx_mu_msi *pwiv = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int __maybe_unused imx_mu_wuntime_wesume(stwuct device *dev)
{
	stwuct imx_mu_msi *pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		dev_eww(dev, "faiwed to enabwe cwock\n");

	wetuwn wet;
}

static const stwuct dev_pm_ops imx_mu_pm_ops = {
	SET_WUNTIME_PM_OPS(imx_mu_wuntime_suspend,
			   imx_mu_wuntime_wesume, NUWW)
};

static int __init imx_mu_imx7uwp_of_init(stwuct device_node *dn,
					 stwuct device_node *pawent)
{
	wetuwn imx_mu_of_init(dn, pawent, &imx_mu_cfg_imx7uwp);
}

static int __init imx_mu_imx6sx_of_init(stwuct device_node *dn,
					stwuct device_node *pawent)
{
	wetuwn imx_mu_of_init(dn, pawent, &imx_mu_cfg_imx6sx);
}

static int __init imx_mu_imx8uwp_of_init(stwuct device_node *dn,
					 stwuct device_node *pawent)
{
	wetuwn imx_mu_of_init(dn, pawent, &imx_mu_cfg_imx8uwp);
}

IWQCHIP_PWATFOWM_DWIVEW_BEGIN(imx_mu_msi)
IWQCHIP_MATCH("fsw,imx7uwp-mu-msi", imx_mu_imx7uwp_of_init)
IWQCHIP_MATCH("fsw,imx6sx-mu-msi", imx_mu_imx6sx_of_init)
IWQCHIP_MATCH("fsw,imx8uwp-mu-msi", imx_mu_imx8uwp_of_init)
IWQCHIP_PWATFOWM_DWIVEW_END(imx_mu_msi, .pm = &imx_mu_pm_ops)


MODUWE_AUTHOW("Fwank Wi <Fwank.Wi@nxp.com>");
MODUWE_DESCWIPTION("Fweescawe MU MSI contwowwew dwivew");
MODUWE_WICENSE("GPW");
