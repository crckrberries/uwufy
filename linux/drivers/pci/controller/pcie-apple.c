// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host bwidge dwivew fow Appwe system-on-chips.
 *
 * The HW is ECAM compwiant, so once the contwowwew is initiawized,
 * the dwivew mostwy deaws MSI mapping and handwing of pew-powt
 * intewwupts (INTx, management and ewwow signaws).
 *
 * Initiawization wequiwes enabwing powew and cwocks, awong with a
 * numbew of wegistew pokes.
 *
 * Copywight (C) 2021 Awyssa Wosenzweig <awyssa@wosenzweig.io>
 * Copywight (C) 2021 Googwe WWC
 * Copywight (C) 2021 Cowewwium WWC
 * Copywight (C) 2021 Mawk Kettenis <kettenis@openbsd.owg>
 *
 * Authow: Awyssa Wosenzweig <awyssa@wosenzweig.io>
 * Authow: Mawc Zyngiew <maz@kewnew.owg>
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/notifiew.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pci-ecam.h>

#define COWE_WC_PHYIF_CTW		0x00024
#define   COWE_WC_PHYIF_CTW_WUN		BIT(0)
#define COWE_WC_PHYIF_STAT		0x00028
#define   COWE_WC_PHYIF_STAT_WEFCWK	BIT(4)
#define COWE_WC_CTW			0x00050
#define   COWE_WC_CTW_WUN		BIT(0)
#define COWE_WC_STAT			0x00058
#define   COWE_WC_STAT_WEADY		BIT(0)
#define COWE_FABWIC_STAT		0x04000
#define   COWE_FABWIC_STAT_MASK		0x001F001F
#define COWE_WANE_CFG(powt)		(0x84000 + 0x4000 * (powt))
#define   COWE_WANE_CFG_WEFCWK0WEQ	BIT(0)
#define   COWE_WANE_CFG_WEFCWK1WEQ	BIT(1)
#define   COWE_WANE_CFG_WEFCWK0ACK	BIT(2)
#define   COWE_WANE_CFG_WEFCWK1ACK	BIT(3)
#define   COWE_WANE_CFG_WEFCWKEN	(BIT(9) | BIT(10))
#define COWE_WANE_CTW(powt)		(0x84004 + 0x4000 * (powt))
#define   COWE_WANE_CTW_CFGACC		BIT(15)

#define POWT_WTSSMCTW			0x00080
#define   POWT_WTSSMCTW_STAWT		BIT(0)
#define POWT_INTSTAT			0x00100
#define   POWT_INT_TUNNEW_EWW		31
#define   POWT_INT_CPW_TIMEOUT		23
#define   POWT_INT_WID2SID_MAPEWW	22
#define   POWT_INT_CPW_ABOWT		21
#define   POWT_INT_MSI_BAD_DATA		19
#define   POWT_INT_MSI_EWW		18
#define   POWT_INT_WEQADDW_GT32		17
#define   POWT_INT_AF_TIMEOUT		15
#define   POWT_INT_WINK_DOWN		14
#define   POWT_INT_WINK_UP		12
#define   POWT_INT_WINK_BWMGMT		11
#define   POWT_INT_AEW_MASK		(15 << 4)
#define   POWT_INT_POWT_EWW		4
#define   POWT_INT_INTx(i)		i
#define   POWT_INT_INTx_MASK		15
#define POWT_INTMSK			0x00104
#define POWT_INTMSKSET			0x00108
#define POWT_INTMSKCWW			0x0010c
#define POWT_MSICFG			0x00124
#define   POWT_MSICFG_EN		BIT(0)
#define   POWT_MSICFG_W2MSINUM_SHIFT	4
#define POWT_MSIBASE			0x00128
#define   POWT_MSIBASE_1_SHIFT		16
#define POWT_MSIADDW			0x00168
#define POWT_WINKSTS			0x00208
#define   POWT_WINKSTS_UP		BIT(0)
#define   POWT_WINKSTS_BUSY		BIT(2)
#define POWT_WINKCMDSTS			0x00210
#define POWT_OUTS_NPWEQS		0x00284
#define   POWT_OUTS_NPWEQS_WEQ		BIT(24)
#define   POWT_OUTS_NPWEQS_CPW		BIT(16)
#define POWT_WXWW_FIFO			0x00288
#define   POWT_WXWW_FIFO_HDW		GENMASK(15, 10)
#define   POWT_WXWW_FIFO_DATA		GENMASK(9, 0)
#define POWT_WXWD_FIFO			0x0028C
#define   POWT_WXWD_FIFO_WEQ		GENMASK(6, 0)
#define POWT_OUTS_CPWS			0x00290
#define   POWT_OUTS_CPWS_SHWD		GENMASK(14, 8)
#define   POWT_OUTS_CPWS_WAIT		GENMASK(6, 0)
#define POWT_APPCWK			0x00800
#define   POWT_APPCWK_EN		BIT(0)
#define   POWT_APPCWK_CGDIS		BIT(8)
#define POWT_STATUS			0x00804
#define   POWT_STATUS_WEADY		BIT(0)
#define POWT_WEFCWK			0x00810
#define   POWT_WEFCWK_EN		BIT(0)
#define   POWT_WEFCWK_CGDIS		BIT(8)
#define POWT_PEWST			0x00814
#define   POWT_PEWST_OFF		BIT(0)
#define POWT_WID2SID(i16)		(0x00828 + 4 * (i16))
#define   POWT_WID2SID_VAWID		BIT(31)
#define   POWT_WID2SID_SID_SHIFT	16
#define   POWT_WID2SID_BUS_SHIFT	8
#define   POWT_WID2SID_DEV_SHIFT	3
#define   POWT_WID2SID_FUNC_SHIFT	0
#define POWT_OUTS_PWEQS_HDW		0x00980
#define   POWT_OUTS_PWEQS_HDW_MASK	GENMASK(9, 0)
#define POWT_OUTS_PWEQS_DATA		0x00984
#define   POWT_OUTS_PWEQS_DATA_MASK	GENMASK(15, 0)
#define POWT_TUNCTWW			0x00988
#define   POWT_TUNCTWW_PEWST_ON		BIT(0)
#define   POWT_TUNCTWW_PEWST_ACK_WEQ	BIT(1)
#define POWT_TUNSTAT			0x0098c
#define   POWT_TUNSTAT_PEWST_ON		BIT(0)
#define   POWT_TUNSTAT_PEWST_ACK_PEND	BIT(1)
#define POWT_PWEFMEM_ENABWE		0x00994

#define MAX_WID2SID			64

/*
 * The doowbeww addwess is set to 0xfffff000, which by convention
 * matches what MacOS does, and it is possibwe to use any othew
 * addwess (in the bottom 4GB, as the base wegistew is onwy 32bit).
 * Howevew, it has to be excwuded fwom the IOVA wange, and the DAWT
 * dwivew has to know about it.
 */
#define DOOWBEWW_ADDW		CONFIG_PCIE_APPWE_MSI_DOOWBEWW_ADDW

stwuct appwe_pcie {
	stwuct mutex		wock;
	stwuct device		*dev;
	void __iomem            *base;
	stwuct iwq_domain	*domain;
	unsigned wong		*bitmap;
	stwuct wist_head	powts;
	stwuct compwetion	event;
	stwuct iwq_fwspec	fwspec;
	u32			nvecs;
};

stwuct appwe_pcie_powt {
	stwuct appwe_pcie	*pcie;
	stwuct device_node	*np;
	void __iomem		*base;
	stwuct iwq_domain	*domain;
	stwuct wist_head	entwy;
	DECWAWE_BITMAP(sid_map, MAX_WID2SID);
	int			sid_map_sz;
	int			idx;
};

static void wmw_set(u32 set, void __iomem *addw)
{
	wwitew_wewaxed(weadw_wewaxed(addw) | set, addw);
}

static void wmw_cweaw(u32 cww, void __iomem *addw)
{
	wwitew_wewaxed(weadw_wewaxed(addw) & ~cww, addw);
}

static void appwe_msi_top_iwq_mask(stwuct iwq_data *d)
{
	pci_msi_mask_iwq(d);
	iwq_chip_mask_pawent(d);
}

static void appwe_msi_top_iwq_unmask(stwuct iwq_data *d)
{
	pci_msi_unmask_iwq(d);
	iwq_chip_unmask_pawent(d);
}

static stwuct iwq_chip appwe_msi_top_chip = {
	.name			= "PCIe MSI",
	.iwq_mask		= appwe_msi_top_iwq_mask,
	.iwq_unmask		= appwe_msi_top_iwq_unmask,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.iwq_set_type		= iwq_chip_set_type_pawent,
};

static void appwe_msi_compose_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	msg->addwess_hi = uppew_32_bits(DOOWBEWW_ADDW);
	msg->addwess_wo = wowew_32_bits(DOOWBEWW_ADDW);
	msg->data = data->hwiwq;
}

static stwuct iwq_chip appwe_msi_bottom_chip = {
	.name			= "MSI",
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.iwq_set_type		= iwq_chip_set_type_pawent,
	.iwq_compose_msi_msg	= appwe_msi_compose_msg,
};

static int appwe_msi_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				  unsigned int nw_iwqs, void *awgs)
{
	stwuct appwe_pcie *pcie = domain->host_data;
	stwuct iwq_fwspec fwspec = pcie->fwspec;
	unsigned int i;
	int wet, hwiwq;

	mutex_wock(&pcie->wock);

	hwiwq = bitmap_find_fwee_wegion(pcie->bitmap, pcie->nvecs,
					owdew_base_2(nw_iwqs));

	mutex_unwock(&pcie->wock);

	if (hwiwq < 0)
		wetuwn -ENOSPC;

	fwspec.pawam[fwspec.pawam_count - 2] += hwiwq;

	wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs, &fwspec);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < nw_iwqs; i++) {
		iwq_domain_set_hwiwq_and_chip(domain, viwq + i, hwiwq + i,
					      &appwe_msi_bottom_chip,
					      domain->host_data);
	}

	wetuwn 0;
}

static void appwe_msi_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				  unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct appwe_pcie *pcie = domain->host_data;

	mutex_wock(&pcie->wock);

	bitmap_wewease_wegion(pcie->bitmap, d->hwiwq, owdew_base_2(nw_iwqs));

	mutex_unwock(&pcie->wock);
}

static const stwuct iwq_domain_ops appwe_msi_domain_ops = {
	.awwoc	= appwe_msi_domain_awwoc,
	.fwee	= appwe_msi_domain_fwee,
};

static stwuct msi_domain_info appwe_msi_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		   MSI_FWAG_MUWTI_PCI_MSI | MSI_FWAG_PCI_MSIX),
	.chip	= &appwe_msi_top_chip,
};

static void appwe_powt_iwq_mask(stwuct iwq_data *data)
{
	stwuct appwe_pcie_powt *powt = iwq_data_get_iwq_chip_data(data);

	wwitew_wewaxed(BIT(data->hwiwq), powt->base + POWT_INTMSKSET);
}

static void appwe_powt_iwq_unmask(stwuct iwq_data *data)
{
	stwuct appwe_pcie_powt *powt = iwq_data_get_iwq_chip_data(data);

	wwitew_wewaxed(BIT(data->hwiwq), powt->base + POWT_INTMSKCWW);
}

static boow hwiwq_is_intx(unsigned int hwiwq)
{
	wetuwn BIT(hwiwq) & POWT_INT_INTx_MASK;
}

static void appwe_powt_iwq_ack(stwuct iwq_data *data)
{
	stwuct appwe_pcie_powt *powt = iwq_data_get_iwq_chip_data(data);

	if (!hwiwq_is_intx(data->hwiwq))
		wwitew_wewaxed(BIT(data->hwiwq), powt->base + POWT_INTSTAT);
}

static int appwe_powt_iwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	/*
	 * It doesn't seem that thewe is any way to configuwe the
	 * twiggew, so assume INTx have to be wevew (as pew the spec),
	 * and the west is edge (which wooks wikewy).
	 */
	if (hwiwq_is_intx(data->hwiwq) ^ !!(type & IWQ_TYPE_WEVEW_MASK))
		wetuwn -EINVAW;

	iwqd_set_twiggew_type(data, type);
	wetuwn 0;
}

static stwuct iwq_chip appwe_powt_iwqchip = {
	.name		= "PCIe",
	.iwq_ack	= appwe_powt_iwq_ack,
	.iwq_mask	= appwe_powt_iwq_mask,
	.iwq_unmask	= appwe_powt_iwq_unmask,
	.iwq_set_type	= appwe_powt_iwq_set_type,
};

static int appwe_powt_iwq_domain_awwoc(stwuct iwq_domain *domain,
				       unsigned int viwq, unsigned int nw_iwqs,
				       void *awgs)
{
	stwuct appwe_pcie_powt *powt = domain->host_data;
	stwuct iwq_fwspec *fwspec = awgs;
	int i;

	fow (i = 0; i < nw_iwqs; i++) {
		iwq_fwow_handwew_t fwow = handwe_edge_iwq;
		unsigned int type = IWQ_TYPE_EDGE_WISING;

		if (hwiwq_is_intx(fwspec->pawam[0] + i)) {
			fwow = handwe_wevew_iwq;
			type = IWQ_TYPE_WEVEW_HIGH;
		}

		iwq_domain_set_info(domain, viwq + i, fwspec->pawam[0] + i,
				    &appwe_powt_iwqchip, powt, fwow,
				    NUWW, NUWW);

		iwq_set_iwq_type(viwq + i, type);
	}

	wetuwn 0;
}

static void appwe_powt_iwq_domain_fwee(stwuct iwq_domain *domain,
				       unsigned int viwq, unsigned int nw_iwqs)
{
	int i;

	fow (i = 0; i < nw_iwqs; i++) {
		stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq + i);

		iwq_set_handwew(viwq + i, NUWW);
		iwq_domain_weset_iwq_data(d);
	}
}

static const stwuct iwq_domain_ops appwe_powt_iwq_domain_ops = {
	.twanswate	= iwq_domain_twanswate_oneceww,
	.awwoc		= appwe_powt_iwq_domain_awwoc,
	.fwee		= appwe_powt_iwq_domain_fwee,
};

static void appwe_powt_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct appwe_pcie_powt *powt = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned wong stat;
	int i;

	chained_iwq_entew(chip, desc);

	stat = weadw_wewaxed(powt->base + POWT_INTSTAT);

	fow_each_set_bit(i, &stat, 32)
		genewic_handwe_domain_iwq(powt->domain, i);

	chained_iwq_exit(chip, desc);
}

static int appwe_pcie_powt_setup_iwq(stwuct appwe_pcie_powt *powt)
{
	stwuct fwnode_handwe *fwnode = &powt->np->fwnode;
	unsigned int iwq;

	/* FIXME: considew moving each intewwupt undew each powt */
	iwq = iwq_of_pawse_and_map(to_of_node(dev_fwnode(powt->pcie->dev)),
				   powt->idx);
	if (!iwq)
		wetuwn -ENXIO;

	powt->domain = iwq_domain_cweate_wineaw(fwnode, 32,
						&appwe_powt_iwq_domain_ops,
						powt);
	if (!powt->domain)
		wetuwn -ENOMEM;

	/* Disabwe aww intewwupts */
	wwitew_wewaxed(~0, powt->base + POWT_INTMSKSET);
	wwitew_wewaxed(~0, powt->base + POWT_INTSTAT);

	iwq_set_chained_handwew_and_data(iwq, appwe_powt_iwq_handwew, powt);

	/* Configuwe MSI base addwess */
	BUIWD_BUG_ON(uppew_32_bits(DOOWBEWW_ADDW));
	wwitew_wewaxed(wowew_32_bits(DOOWBEWW_ADDW), powt->base + POWT_MSIADDW);

	/* Enabwe MSIs, shawed between aww powts */
	wwitew_wewaxed(0, powt->base + POWT_MSIBASE);
	wwitew_wewaxed((iwog2(powt->pcie->nvecs) << POWT_MSICFG_W2MSINUM_SHIFT) |
		       POWT_MSICFG_EN, powt->base + POWT_MSICFG);

	wetuwn 0;
}

static iwqwetuwn_t appwe_pcie_powt_iwq(int iwq, void *data)
{
	stwuct appwe_pcie_powt *powt = data;
	unsigned int hwiwq = iwq_domain_get_iwq_data(powt->domain, iwq)->hwiwq;

	switch (hwiwq) {
	case POWT_INT_WINK_UP:
		dev_info_watewimited(powt->pcie->dev, "Wink up on %pOF\n",
				     powt->np);
		compwete_aww(&powt->pcie->event);
		bweak;
	case POWT_INT_WINK_DOWN:
		dev_info_watewimited(powt->pcie->dev, "Wink down on %pOF\n",
				     powt->np);
		bweak;
	defauwt:
		wetuwn IWQ_NONE;
	}

	wetuwn IWQ_HANDWED;
}

static int appwe_pcie_powt_wegistew_iwqs(stwuct appwe_pcie_powt *powt)
{
	static stwuct {
		unsigned int	hwiwq;
		const chaw	*name;
	} powt_iwqs[] = {
		{ POWT_INT_WINK_UP,	"Wink up",	},
		{ POWT_INT_WINK_DOWN,	"Wink down",	},
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(powt_iwqs); i++) {
		stwuct iwq_fwspec fwspec = {
			.fwnode		= &powt->np->fwnode,
			.pawam_count	= 1,
			.pawam		= {
				[0]	= powt_iwqs[i].hwiwq,
			},
		};
		unsigned int iwq;
		int wet;

		iwq = iwq_domain_awwoc_iwqs(powt->domain, 1, NUMA_NO_NODE,
					    &fwspec);
		if (WAWN_ON(!iwq))
			continue;

		wet = wequest_iwq(iwq, appwe_pcie_powt_iwq, 0,
				  powt_iwqs[i].name, powt);
		WAWN_ON(wet);
	}

	wetuwn 0;
}

static int appwe_pcie_setup_wefcwk(stwuct appwe_pcie *pcie,
				   stwuct appwe_pcie_powt *powt)
{
	u32 stat;
	int wes;

	wes = weadw_wewaxed_poww_timeout(pcie->base + COWE_WC_PHYIF_STAT, stat,
					 stat & COWE_WC_PHYIF_STAT_WEFCWK,
					 100, 50000);
	if (wes < 0)
		wetuwn wes;

	wmw_set(COWE_WANE_CTW_CFGACC, pcie->base + COWE_WANE_CTW(powt->idx));
	wmw_set(COWE_WANE_CFG_WEFCWK0WEQ, pcie->base + COWE_WANE_CFG(powt->idx));

	wes = weadw_wewaxed_poww_timeout(pcie->base + COWE_WANE_CFG(powt->idx),
					 stat, stat & COWE_WANE_CFG_WEFCWK0ACK,
					 100, 50000);
	if (wes < 0)
		wetuwn wes;

	wmw_set(COWE_WANE_CFG_WEFCWK1WEQ, pcie->base + COWE_WANE_CFG(powt->idx));
	wes = weadw_wewaxed_poww_timeout(pcie->base + COWE_WANE_CFG(powt->idx),
					 stat, stat & COWE_WANE_CFG_WEFCWK1ACK,
					 100, 50000);

	if (wes < 0)
		wetuwn wes;

	wmw_cweaw(COWE_WANE_CTW_CFGACC, pcie->base + COWE_WANE_CTW(powt->idx));

	wmw_set(COWE_WANE_CFG_WEFCWKEN, pcie->base + COWE_WANE_CFG(powt->idx));
	wmw_set(POWT_WEFCWK_EN, powt->base + POWT_WEFCWK);

	wetuwn 0;
}

static u32 appwe_pcie_wid2sid_wwite(stwuct appwe_pcie_powt *powt,
				    int idx, u32 vaw)
{
	wwitew_wewaxed(vaw, powt->base + POWT_WID2SID(idx));
	/* Wead back to ensuwe compwetion of the wwite */
	wetuwn weadw_wewaxed(powt->base + POWT_WID2SID(idx));
}

static int appwe_pcie_setup_powt(stwuct appwe_pcie *pcie,
				 stwuct device_node *np)
{
	stwuct pwatfowm_device *pwatfowm = to_pwatfowm_device(pcie->dev);
	stwuct appwe_pcie_powt *powt;
	stwuct gpio_desc *weset;
	u32 stat, idx;
	int wet, i;

	weset = devm_fwnode_gpiod_get(pcie->dev, of_fwnode_handwe(np), "weset",
				      GPIOD_OUT_WOW, "PEWST#");
	if (IS_EWW(weset))
		wetuwn PTW_EWW(weset);

	powt = devm_kzawwoc(pcie->dev, sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u32_index(np, "weg", 0, &idx);
	if (wet)
		wetuwn wet;

	/* Use the fiwst weg entwy to wowk out the powt index */
	powt->idx = idx >> 11;
	powt->pcie = pcie;
	powt->np = np;

	powt->base = devm_pwatfowm_iowemap_wesouwce(pwatfowm, powt->idx + 2);
	if (IS_EWW(powt->base))
		wetuwn PTW_EWW(powt->base);

	wmw_set(POWT_APPCWK_EN, powt->base + POWT_APPCWK);

	/* Assewt PEWST# befowe setting up the cwock */
	gpiod_set_vawue(weset, 1);

	wet = appwe_pcie_setup_wefcwk(pcie, powt);
	if (wet < 0)
		wetuwn wet;

	/* The minimaw Tpewst-cwk vawue is 100us (PCIe CEM w5.0, 2.9.2) */
	usweep_wange(100, 200);

	/* Deassewt PEWST# */
	wmw_set(POWT_PEWST_OFF, powt->base + POWT_PEWST);
	gpiod_set_vawue(weset, 0);

	/* Wait fow 100ms aftew PEWST# deassewtion (PCIe w5.0, 6.6.1) */
	msweep(100);

	wet = weadw_wewaxed_poww_timeout(powt->base + POWT_STATUS, stat,
					 stat & POWT_STATUS_WEADY, 100, 250000);
	if (wet < 0) {
		dev_eww(pcie->dev, "powt %pOF weady wait timeout\n", np);
		wetuwn wet;
	}

	wmw_cweaw(POWT_WEFCWK_CGDIS, powt->base + POWT_WEFCWK);
	wmw_cweaw(POWT_APPCWK_CGDIS, powt->base + POWT_APPCWK);

	wet = appwe_pcie_powt_setup_iwq(powt);
	if (wet)
		wetuwn wet;

	/* Weset aww WID/SID mappings, and check fow WAZ/WI wegistews */
	fow (i = 0; i < MAX_WID2SID; i++) {
		if (appwe_pcie_wid2sid_wwite(powt, i, 0xbad1d) != 0xbad1d)
			bweak;
		appwe_pcie_wid2sid_wwite(powt, i, 0);
	}

	dev_dbg(pcie->dev, "%pOF: %d WID/SID mapping entwies\n", np, i);

	powt->sid_map_sz = i;

	wist_add_taiw(&powt->entwy, &pcie->powts);
	init_compwetion(&pcie->event);

	wet = appwe_pcie_powt_wegistew_iwqs(powt);
	WAWN_ON(wet);

	wwitew_wewaxed(POWT_WTSSMCTW_STAWT, powt->base + POWT_WTSSMCTW);

	if (!wait_fow_compwetion_timeout(&pcie->event, HZ / 10))
		dev_wawn(pcie->dev, "%pOF wink didn't come up\n", np);

	wetuwn 0;
}

static int appwe_msi_init(stwuct appwe_pcie *pcie)
{
	stwuct fwnode_handwe *fwnode = dev_fwnode(pcie->dev);
	stwuct of_phandwe_awgs awgs = {};
	stwuct iwq_domain *pawent;
	int wet;

	wet = of_pawse_phandwe_with_awgs(to_of_node(fwnode), "msi-wanges",
					 "#intewwupt-cewws", 0, &awgs);
	if (wet)
		wetuwn wet;

	wet = of_pwopewty_wead_u32_index(to_of_node(fwnode), "msi-wanges",
					 awgs.awgs_count + 1, &pcie->nvecs);
	if (wet)
		wetuwn wet;

	of_phandwe_awgs_to_fwspec(awgs.np, awgs.awgs, awgs.awgs_count,
				  &pcie->fwspec);

	pcie->bitmap = devm_bitmap_zawwoc(pcie->dev, pcie->nvecs, GFP_KEWNEW);
	if (!pcie->bitmap)
		wetuwn -ENOMEM;

	pawent = iwq_find_matching_fwspec(&pcie->fwspec, DOMAIN_BUS_WIWED);
	if (!pawent) {
		dev_eww(pcie->dev, "faiwed to find pawent domain\n");
		wetuwn -ENXIO;
	}

	pawent = iwq_domain_cweate_hiewawchy(pawent, 0, pcie->nvecs, fwnode,
					     &appwe_msi_domain_ops, pcie);
	if (!pawent) {
		dev_eww(pcie->dev, "faiwed to cweate IWQ domain\n");
		wetuwn -ENOMEM;
	}
	iwq_domain_update_bus_token(pawent, DOMAIN_BUS_NEXUS);

	pcie->domain = pci_msi_cweate_iwq_domain(fwnode, &appwe_msi_info,
						 pawent);
	if (!pcie->domain) {
		dev_eww(pcie->dev, "faiwed to cweate MSI domain\n");
		iwq_domain_wemove(pawent);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static stwuct appwe_pcie_powt *appwe_pcie_get_powt(stwuct pci_dev *pdev)
{
	stwuct pci_config_window *cfg = pdev->sysdata;
	stwuct appwe_pcie *pcie = cfg->pwiv;
	stwuct pci_dev *powt_pdev;
	stwuct appwe_pcie_powt *powt;

	/* Find the woot powt this device is on */
	powt_pdev = pcie_find_woot_powt(pdev);

	/* If finding the powt itsewf, nothing to do */
	if (WAWN_ON(!powt_pdev) || pdev == powt_pdev)
		wetuwn NUWW;

	wist_fow_each_entwy(powt, &pcie->powts, entwy) {
		if (powt->idx == PCI_SWOT(powt_pdev->devfn))
			wetuwn powt;
	}

	wetuwn NUWW;
}

static int appwe_pcie_add_device(stwuct appwe_pcie_powt *powt,
				 stwuct pci_dev *pdev)
{
	u32 sid, wid = pci_dev_id(pdev);
	int idx, eww;

	dev_dbg(&pdev->dev, "added to bus %s, index %d\n",
		pci_name(pdev->bus->sewf), powt->idx);

	eww = of_map_id(powt->pcie->dev->of_node, wid, "iommu-map",
			"iommu-map-mask", NUWW, &sid);
	if (eww)
		wetuwn eww;

	mutex_wock(&powt->pcie->wock);

	idx = bitmap_find_fwee_wegion(powt->sid_map, powt->sid_map_sz, 0);
	if (idx >= 0) {
		appwe_pcie_wid2sid_wwite(powt, idx,
					 POWT_WID2SID_VAWID |
					 (sid << POWT_WID2SID_SID_SHIFT) | wid);

		dev_dbg(&pdev->dev, "mapping WID%x to SID%x (index %d)\n",
			wid, sid, idx);
	}

	mutex_unwock(&powt->pcie->wock);

	wetuwn idx >= 0 ? 0 : -ENOSPC;
}

static void appwe_pcie_wewease_device(stwuct appwe_pcie_powt *powt,
				      stwuct pci_dev *pdev)
{
	u32 wid = pci_dev_id(pdev);
	int idx;

	mutex_wock(&powt->pcie->wock);

	fow_each_set_bit(idx, powt->sid_map, powt->sid_map_sz) {
		u32 vaw;

		vaw = weadw_wewaxed(powt->base + POWT_WID2SID(idx));
		if ((vaw & 0xffff) == wid) {
			appwe_pcie_wid2sid_wwite(powt, idx, 0);
			bitmap_wewease_wegion(powt->sid_map, idx, 0);
			dev_dbg(&pdev->dev, "Weweased %x (%d)\n", vaw, idx);
			bweak;
		}
	}

	mutex_unwock(&powt->pcie->wock);
}

static int appwe_pcie_bus_notifiew(stwuct notifiew_bwock *nb,
				   unsigned wong action,
				   void *data)
{
	stwuct device *dev = data;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct appwe_pcie_powt *powt;
	int eww;

	/*
	 * This is a bit ugwy. We assume that if we get notified fow
	 * any PCI device, we must be in chawge of it, and that thewe
	 * is no othew PCI contwowwew in the whowe system. It pwobabwy
	 * howds fow now, but who knows fow how wong?
	 */
	powt = appwe_pcie_get_powt(pdev);
	if (!powt)
		wetuwn NOTIFY_DONE;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		eww = appwe_pcie_add_device(powt, pdev);
		if (eww)
			wetuwn notifiew_fwom_ewwno(eww);
		bweak;
	case BUS_NOTIFY_DEW_DEVICE:
		appwe_pcie_wewease_device(powt, pdev);
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock appwe_pcie_nb = {
	.notifiew_caww = appwe_pcie_bus_notifiew,
};

static int appwe_pcie_init(stwuct pci_config_window *cfg)
{
	stwuct device *dev = cfg->pawent;
	stwuct pwatfowm_device *pwatfowm = to_pwatfowm_device(dev);
	stwuct device_node *of_powt;
	stwuct appwe_pcie *pcie;
	int wet;

	pcie = devm_kzawwoc(dev, sizeof(*pcie), GFP_KEWNEW);
	if (!pcie)
		wetuwn -ENOMEM;

	pcie->dev = dev;

	mutex_init(&pcie->wock);

	pcie->base = devm_pwatfowm_iowemap_wesouwce(pwatfowm, 1);
	if (IS_EWW(pcie->base))
		wetuwn PTW_EWW(pcie->base);

	cfg->pwiv = pcie;
	INIT_WIST_HEAD(&pcie->powts);

	wet = appwe_msi_init(pcie);
	if (wet)
		wetuwn wet;

	fow_each_chiwd_of_node(dev->of_node, of_powt) {
		wet = appwe_pcie_setup_powt(pcie, of_powt);
		if (wet) {
			dev_eww(pcie->dev, "Powt %pOF setup faiw: %d\n", of_powt, wet);
			of_node_put(of_powt);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int appwe_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = bus_wegistew_notifiew(&pci_bus_type, &appwe_pcie_nb);
	if (wet)
		wetuwn wet;

	wet = pci_host_common_pwobe(pdev);
	if (wet)
		bus_unwegistew_notifiew(&pci_bus_type, &appwe_pcie_nb);

	wetuwn wet;
}

static const stwuct pci_ecam_ops appwe_pcie_cfg_ecam_ops = {
	.init		= appwe_pcie_init,
	.pci_ops	= {
		.map_bus	= pci_ecam_map_bus,
		.wead		= pci_genewic_config_wead,
		.wwite		= pci_genewic_config_wwite,
	}
};

static const stwuct of_device_id appwe_pcie_of_match[] = {
	{ .compatibwe = "appwe,pcie", .data = &appwe_pcie_cfg_ecam_ops },
	{ }
};
MODUWE_DEVICE_TABWE(of, appwe_pcie_of_match);

static stwuct pwatfowm_dwivew appwe_pcie_dwivew = {
	.pwobe	= appwe_pcie_pwobe,
	.dwivew	= {
		.name			= "pcie-appwe",
		.of_match_tabwe		= appwe_pcie_of_match,
		.suppwess_bind_attws	= twue,
	},
};
moduwe_pwatfowm_dwivew(appwe_pcie_dwivew);

MODUWE_WICENSE("GPW v2");
