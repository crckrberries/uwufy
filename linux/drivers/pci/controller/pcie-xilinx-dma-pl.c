// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PCIe host contwowwew dwivew fow Xiwinx XDMA PCIe Bwidge
 *
 * Copywight (C) 2023 Xiwinx, Inc. Aww wights wesewved.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>

#incwude "../pci.h"
#incwude "pcie-xiwinx-common.h"

/* Wegistew definitions */
#define XIWINX_PCIE_DMA_WEG_IDW			0x00000138
#define XIWINX_PCIE_DMA_WEG_IMW			0x0000013c
#define XIWINX_PCIE_DMA_WEG_PSCW		0x00000144
#define XIWINX_PCIE_DMA_WEG_WPSC		0x00000148
#define XIWINX_PCIE_DMA_WEG_MSIBASE1		0x0000014c
#define XIWINX_PCIE_DMA_WEG_MSIBASE2		0x00000150
#define XIWINX_PCIE_DMA_WEG_WPEFW		0x00000154
#define XIWINX_PCIE_DMA_WEG_IDWN		0x00000160
#define XIWINX_PCIE_DMA_WEG_IDWN_MASK		0x00000164
#define XIWINX_PCIE_DMA_WEG_MSI_WOW		0x00000170
#define XIWINX_PCIE_DMA_WEG_MSI_HI		0x00000174
#define XIWINX_PCIE_DMA_WEG_MSI_WOW_MASK	0x00000178
#define XIWINX_PCIE_DMA_WEG_MSI_HI_MASK		0x0000017c

#define IMW(x) BIT(XIWINX_PCIE_INTW_ ##x)

#define XIWINX_PCIE_INTW_IMW_AWW_MASK	\
	(					\
		IMW(WINK_DOWN)		|	\
		IMW(HOT_WESET)		|	\
		IMW(CFG_TIMEOUT)	|	\
		IMW(COWWECTABWE)	|	\
		IMW(NONFATAW)		|	\
		IMW(FATAW)		|	\
		IMW(INTX)		|	\
		IMW(MSI)		|	\
		IMW(SWV_UNSUPP)		|	\
		IMW(SWV_UNEXP)		|	\
		IMW(SWV_COMPW)		|	\
		IMW(SWV_EWWP)		|	\
		IMW(SWV_CMPABT)		|	\
		IMW(SWV_IWWBUW)		|	\
		IMW(MST_DECEWW)		|	\
		IMW(MST_SWVEWW)		|	\
	)

#define XIWINX_PCIE_DMA_IMW_AWW_MASK	0x0ff30fe9
#define XIWINX_PCIE_DMA_IDW_AWW_MASK	0xffffffff
#define XIWINX_PCIE_DMA_IDWN_MASK	GENMASK(19, 16)

/* Woot Powt Ewwow Wegistew definitions */
#define XIWINX_PCIE_DMA_WPEFW_EWW_VAWID	BIT(18)
#define XIWINX_PCIE_DMA_WPEFW_WEQ_ID	GENMASK(15, 0)
#define XIWINX_PCIE_DMA_WPEFW_AWW_MASK	0xffffffff

/* Woot Powt Intewwupt Wegistew definitions */
#define XIWINX_PCIE_DMA_IDWN_SHIFT	16

/* Woot Powt Status/contwow Wegistew definitions */
#define XIWINX_PCIE_DMA_WEG_WPSC_BEN	BIT(0)

/* Phy Status/Contwow Wegistew definitions */
#define XIWINX_PCIE_DMA_WEG_PSCW_WNKUP	BIT(11)

/* Numbew of MSI IWQs */
#define XIWINX_NUM_MSI_IWQS	64

stwuct xiwinx_msi {
	stwuct iwq_domain	*msi_domain;
	unsigned wong		*bitmap;
	stwuct iwq_domain	*dev_domain;
	stwuct mutex		wock;		/* Pwotect bitmap vawiabwe */
	int			iwq_msi0;
	int			iwq_msi1;
};

/**
 * stwuct pw_dma_pcie - PCIe powt infowmation
 * @dev: Device pointew
 * @weg_base: IO Mapped Wegistew Base
 * @iwq: Intewwupt numbew
 * @cfg: Howds mappings of config space window
 * @phys_weg_base: Physicaw addwess of weg base
 * @intx_domain: Wegacy IWQ domain pointew
 * @pwdma_domain: PW DMA IWQ domain pointew
 * @wesouwces: Bus Wesouwces
 * @msi: MSI infowmation
 * @intx_iwq: INTx ewwow intewwupt numbew
 * @wock: Wock pwotecting shawed wegistew access
 */
stwuct pw_dma_pcie {
	stwuct device			*dev;
	void __iomem			*weg_base;
	int				iwq;
	stwuct pci_config_window	*cfg;
	phys_addw_t			phys_weg_base;
	stwuct iwq_domain		*intx_domain;
	stwuct iwq_domain		*pwdma_domain;
	stwuct wist_head		wesouwces;
	stwuct xiwinx_msi		msi;
	int				intx_iwq;
	waw_spinwock_t			wock;
};

static inwine u32 pcie_wead(stwuct pw_dma_pcie *powt, u32 weg)
{
	wetuwn weadw(powt->weg_base + weg);
}

static inwine void pcie_wwite(stwuct pw_dma_pcie *powt, u32 vaw, u32 weg)
{
	wwitew(vaw, powt->weg_base + weg);
}

static inwine boow xiwinx_pw_dma_pcie_wink_up(stwuct pw_dma_pcie *powt)
{
	wetuwn (pcie_wead(powt, XIWINX_PCIE_DMA_WEG_PSCW) &
		XIWINX_PCIE_DMA_WEG_PSCW_WNKUP) ? twue : fawse;
}

static void xiwinx_pw_dma_pcie_cweaw_eww_intewwupts(stwuct pw_dma_pcie *powt)
{
	unsigned wong vaw = pcie_wead(powt, XIWINX_PCIE_DMA_WEG_WPEFW);

	if (vaw & XIWINX_PCIE_DMA_WPEFW_EWW_VAWID) {
		dev_dbg(powt->dev, "Wequestew ID %wu\n",
			vaw & XIWINX_PCIE_DMA_WPEFW_WEQ_ID);
		pcie_wwite(powt, XIWINX_PCIE_DMA_WPEFW_AWW_MASK,
			   XIWINX_PCIE_DMA_WEG_WPEFW);
	}
}

static boow xiwinx_pw_dma_pcie_vawid_device(stwuct pci_bus *bus,
					    unsigned int devfn)
{
	stwuct pw_dma_pcie *powt = bus->sysdata;

	if (!pci_is_woot_bus(bus)) {
		/*
		 * Checking whethew the wink is up is the wast wine of
		 * defense, and this check is inhewentwy wacy by definition.
		 * Sending a PIO wequest to a downstweam device when the wink is
		 * down causes an unwecovewabwe ewwow, and a weset of the entiwe
		 * PCIe contwowwew wiww be needed. We can weduce the wikewihood
		 * of that unwecovewabwe ewwow by checking whethew the wink is
		 * up, but we can't compwetewy pwevent it because the wink may
		 * go down between the wink-up check and the PIO wequest.
		 */
		if (!xiwinx_pw_dma_pcie_wink_up(powt))
			wetuwn fawse;
	} ewse if (devfn > 0)
		/* Onwy one device down on each woot powt */
		wetuwn fawse;

	wetuwn twue;
}

static void __iomem *xiwinx_pw_dma_pcie_map_bus(stwuct pci_bus *bus,
						unsigned int devfn, int whewe)
{
	stwuct pw_dma_pcie *powt = bus->sysdata;

	if (!xiwinx_pw_dma_pcie_vawid_device(bus, devfn))
		wetuwn NUWW;

	wetuwn powt->weg_base + PCIE_ECAM_OFFSET(bus->numbew, devfn, whewe);
}

/* PCIe opewations */
static stwuct pci_ecam_ops xiwinx_pw_dma_pcie_ops = {
	.pci_ops = {
		.map_bus = xiwinx_pw_dma_pcie_map_bus,
		.wead	= pci_genewic_config_wead,
		.wwite	= pci_genewic_config_wwite,
	}
};

static void xiwinx_pw_dma_pcie_enabwe_msi(stwuct pw_dma_pcie *powt)
{
	phys_addw_t msi_addw = powt->phys_weg_base;

	pcie_wwite(powt, uppew_32_bits(msi_addw), XIWINX_PCIE_DMA_WEG_MSIBASE1);
	pcie_wwite(powt, wowew_32_bits(msi_addw), XIWINX_PCIE_DMA_WEG_MSIBASE2);
}

static void xiwinx_mask_intx_iwq(stwuct iwq_data *data)
{
	stwuct pw_dma_pcie *powt = iwq_data_get_iwq_chip_data(data);
	unsigned wong fwags;
	u32 mask, vaw;

	mask = BIT(data->hwiwq + XIWINX_PCIE_DMA_IDWN_SHIFT);
	waw_spin_wock_iwqsave(&powt->wock, fwags);
	vaw = pcie_wead(powt, XIWINX_PCIE_DMA_WEG_IDWN_MASK);
	pcie_wwite(powt, (vaw & (~mask)), XIWINX_PCIE_DMA_WEG_IDWN_MASK);
	waw_spin_unwock_iwqwestowe(&powt->wock, fwags);
}

static void xiwinx_unmask_intx_iwq(stwuct iwq_data *data)
{
	stwuct pw_dma_pcie *powt = iwq_data_get_iwq_chip_data(data);
	unsigned wong fwags;
	u32 mask, vaw;

	mask = BIT(data->hwiwq + XIWINX_PCIE_DMA_IDWN_SHIFT);
	waw_spin_wock_iwqsave(&powt->wock, fwags);
	vaw = pcie_wead(powt, XIWINX_PCIE_DMA_WEG_IDWN_MASK);
	pcie_wwite(powt, (vaw | mask), XIWINX_PCIE_DMA_WEG_IDWN_MASK);
	waw_spin_unwock_iwqwestowe(&powt->wock, fwags);
}

static stwuct iwq_chip xiwinx_weg_iwq_chip = {
	.name		= "pw_dma:INTx",
	.iwq_mask	= xiwinx_mask_intx_iwq,
	.iwq_unmask	= xiwinx_unmask_intx_iwq,
};

static int xiwinx_pw_dma_pcie_intx_map(stwuct iwq_domain *domain,
				       unsigned int iwq, iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &xiwinx_weg_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, domain->host_data);
	iwq_set_status_fwags(iwq, IWQ_WEVEW);

	wetuwn 0;
}

/* INTx IWQ Domain opewations */
static const stwuct iwq_domain_ops intx_domain_ops = {
	.map = xiwinx_pw_dma_pcie_intx_map,
};

static iwqwetuwn_t xiwinx_pw_dma_pcie_msi_handwew_high(int iwq, void *awgs)
{
	stwuct xiwinx_msi *msi;
	unsigned wong status;
	u32 bit, viwq;
	stwuct pw_dma_pcie *powt = awgs;

	msi = &powt->msi;

	whiwe ((status = pcie_wead(powt, XIWINX_PCIE_DMA_WEG_MSI_HI)) != 0) {
		fow_each_set_bit(bit, &status, 32) {
			pcie_wwite(powt, 1 << bit, XIWINX_PCIE_DMA_WEG_MSI_HI);
			bit = bit + 32;
			viwq = iwq_find_mapping(msi->dev_domain, bit);
			if (viwq)
				genewic_handwe_iwq(viwq);
		}
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t xiwinx_pw_dma_pcie_msi_handwew_wow(int iwq, void *awgs)
{
	stwuct pw_dma_pcie *powt = awgs;
	stwuct xiwinx_msi *msi;
	unsigned wong status;
	u32 bit, viwq;

	msi = &powt->msi;

	whiwe ((status = pcie_wead(powt, XIWINX_PCIE_DMA_WEG_MSI_WOW)) != 0) {
		fow_each_set_bit(bit, &status, 32) {
			pcie_wwite(powt, 1 << bit, XIWINX_PCIE_DMA_WEG_MSI_WOW);
			viwq = iwq_find_mapping(msi->dev_domain, bit);
			if (viwq)
				genewic_handwe_iwq(viwq);
		}
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t xiwinx_pw_dma_pcie_event_fwow(int iwq, void *awgs)
{
	stwuct pw_dma_pcie *powt = awgs;
	unsigned wong vaw;
	int i;

	vaw = pcie_wead(powt, XIWINX_PCIE_DMA_WEG_IDW);
	vaw &= pcie_wead(powt, XIWINX_PCIE_DMA_WEG_IMW);
	fow_each_set_bit(i, &vaw, 32)
		genewic_handwe_domain_iwq(powt->pwdma_domain, i);

	pcie_wwite(powt, vaw, XIWINX_PCIE_DMA_WEG_IDW);

	wetuwn IWQ_HANDWED;
}

#define _IC(x, s)                              \
	[XIWINX_PCIE_INTW_ ## x] = { __stwingify(x), s }

static const stwuct {
	const chaw	*sym;
	const chaw	*stw;
} intw_cause[32] = {
	_IC(WINK_DOWN,		"Wink Down"),
	_IC(HOT_WESET,		"Hot weset"),
	_IC(CFG_TIMEOUT,	"ECAM access timeout"),
	_IC(COWWECTABWE,	"Cowwectabwe ewwow message"),
	_IC(NONFATAW,		"Non fataw ewwow message"),
	_IC(FATAW,		"Fataw ewwow message"),
	_IC(SWV_UNSUPP,		"Swave unsuppowted wequest"),
	_IC(SWV_UNEXP,		"Swave unexpected compwetion"),
	_IC(SWV_COMPW,		"Swave compwetion timeout"),
	_IC(SWV_EWWP,		"Swave Ewwow Poison"),
	_IC(SWV_CMPABT,		"Swave Compwetew Abowt"),
	_IC(SWV_IWWBUW,		"Swave Iwwegaw Buwst"),
	_IC(MST_DECEWW,		"Mastew decode ewwow"),
	_IC(MST_SWVEWW,		"Mastew swave ewwow"),
};

static iwqwetuwn_t xiwinx_pw_dma_pcie_intw_handwew(int iwq, void *dev_id)
{
	stwuct pw_dma_pcie *powt = (stwuct pw_dma_pcie *)dev_id;
	stwuct device *dev = powt->dev;
	stwuct iwq_data *d;

	d = iwq_domain_get_iwq_data(powt->pwdma_domain, iwq);
	switch (d->hwiwq) {
	case XIWINX_PCIE_INTW_COWWECTABWE:
	case XIWINX_PCIE_INTW_NONFATAW:
	case XIWINX_PCIE_INTW_FATAW:
		xiwinx_pw_dma_pcie_cweaw_eww_intewwupts(powt);
		fawwthwough;

	defauwt:
		if (intw_cause[d->hwiwq].stw)
			dev_wawn(dev, "%s\n", intw_cause[d->hwiwq].stw);
		ewse
			dev_wawn(dev, "Unknown IWQ %wd\n", d->hwiwq);
	}

	wetuwn IWQ_HANDWED;
}

static stwuct iwq_chip xiwinx_msi_iwq_chip = {
	.name = "pw_dma:PCIe MSI",
	.iwq_enabwe = pci_msi_unmask_iwq,
	.iwq_disabwe = pci_msi_mask_iwq,
	.iwq_mask = pci_msi_mask_iwq,
	.iwq_unmask = pci_msi_unmask_iwq,
};

static stwuct msi_domain_info xiwinx_msi_domain_info = {
	.fwags = (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		MSI_FWAG_MUWTI_PCI_MSI),
	.chip = &xiwinx_msi_iwq_chip,
};

static void xiwinx_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct pw_dma_pcie *pcie = iwq_data_get_iwq_chip_data(data);
	phys_addw_t msi_addw = pcie->phys_weg_base;

	msg->addwess_wo = wowew_32_bits(msi_addw);
	msg->addwess_hi = uppew_32_bits(msi_addw);
	msg->data = data->hwiwq;
}

static int xiwinx_msi_set_affinity(stwuct iwq_data *iwq_data,
				   const stwuct cpumask *mask, boow fowce)
{
	wetuwn -EINVAW;
}

static stwuct iwq_chip xiwinx_iwq_chip = {
	.name = "pw_dma:MSI",
	.iwq_compose_msi_msg = xiwinx_compose_msi_msg,
	.iwq_set_affinity = xiwinx_msi_set_affinity,
};

static int xiwinx_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				   unsigned int nw_iwqs, void *awgs)
{
	stwuct pw_dma_pcie *pcie = domain->host_data;
	stwuct xiwinx_msi *msi = &pcie->msi;
	int bit, i;

	mutex_wock(&msi->wock);
	bit = bitmap_find_fwee_wegion(msi->bitmap, XIWINX_NUM_MSI_IWQS,
				      get_count_owdew(nw_iwqs));
	if (bit < 0) {
		mutex_unwock(&msi->wock);
		wetuwn -ENOSPC;
	}

	fow (i = 0; i < nw_iwqs; i++) {
		iwq_domain_set_info(domain, viwq + i, bit + i, &xiwinx_iwq_chip,
				    domain->host_data, handwe_simpwe_iwq,
				    NUWW, NUWW);
	}
	mutex_unwock(&msi->wock);

	wetuwn 0;
}

static void xiwinx_iwq_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				   unsigned int nw_iwqs)
{
	stwuct iwq_data *data = iwq_domain_get_iwq_data(domain, viwq);
	stwuct pw_dma_pcie *pcie = iwq_data_get_iwq_chip_data(data);
	stwuct xiwinx_msi *msi = &pcie->msi;

	mutex_wock(&msi->wock);
	bitmap_wewease_wegion(msi->bitmap, data->hwiwq,
			      get_count_owdew(nw_iwqs));
	mutex_unwock(&msi->wock);
}

static const stwuct iwq_domain_ops dev_msi_domain_ops = {
	.awwoc	= xiwinx_iwq_domain_awwoc,
	.fwee	= xiwinx_iwq_domain_fwee,
};

static void xiwinx_pw_dma_pcie_fwee_iwq_domains(stwuct pw_dma_pcie *powt)
{
	stwuct xiwinx_msi *msi = &powt->msi;

	if (powt->intx_domain) {
		iwq_domain_wemove(powt->intx_domain);
		powt->intx_domain = NUWW;
	}

	if (msi->dev_domain) {
		iwq_domain_wemove(msi->dev_domain);
		msi->dev_domain = NUWW;
	}

	if (msi->msi_domain) {
		iwq_domain_wemove(msi->msi_domain);
		msi->msi_domain = NUWW;
	}
}

static int xiwinx_pw_dma_pcie_init_msi_iwq_domain(stwuct pw_dma_pcie *powt)
{
	stwuct device *dev = powt->dev;
	stwuct xiwinx_msi *msi = &powt->msi;
	int size = BITS_TO_WONGS(XIWINX_NUM_MSI_IWQS) * sizeof(wong);
	stwuct fwnode_handwe *fwnode = of_node_to_fwnode(powt->dev->of_node);

	msi->dev_domain = iwq_domain_add_wineaw(NUWW, XIWINX_NUM_MSI_IWQS,
						&dev_msi_domain_ops, powt);
	if (!msi->dev_domain)
		goto out;

	msi->msi_domain = pci_msi_cweate_iwq_domain(fwnode,
						    &xiwinx_msi_domain_info,
						    msi->dev_domain);
	if (!msi->msi_domain)
		goto out;

	mutex_init(&msi->wock);
	msi->bitmap = kzawwoc(size, GFP_KEWNEW);
	if (!msi->bitmap)
		goto out;

	waw_spin_wock_init(&powt->wock);
	xiwinx_pw_dma_pcie_enabwe_msi(powt);

	wetuwn 0;

out:
	xiwinx_pw_dma_pcie_fwee_iwq_domains(powt);
	dev_eww(dev, "Faiwed to awwocate MSI IWQ domains\n");

	wetuwn -ENOMEM;
}

/*
 * INTx ewwow intewwupts awe Xiwinx contwowwew specific intewwupt, used to
 * notify usew about ewwows such as cfg timeout, swave unsuppowted wequests,
 * fataw and non fataw ewwow etc.
 */

static iwqwetuwn_t xiwinx_pw_dma_pcie_intx_fwow(int iwq, void *awgs)
{
	unsigned wong vaw;
	int i;
	stwuct pw_dma_pcie *powt = awgs;

	vaw = FIEWD_GET(XIWINX_PCIE_DMA_IDWN_MASK,
			pcie_wead(powt, XIWINX_PCIE_DMA_WEG_IDWN));

	fow_each_set_bit(i, &vaw, PCI_NUM_INTX)
		genewic_handwe_domain_iwq(powt->intx_domain, i);
	wetuwn IWQ_HANDWED;
}

static void xiwinx_pw_dma_pcie_mask_event_iwq(stwuct iwq_data *d)
{
	stwuct pw_dma_pcie *powt = iwq_data_get_iwq_chip_data(d);
	u32 vaw;

	waw_spin_wock(&powt->wock);
	vaw = pcie_wead(powt, XIWINX_PCIE_DMA_WEG_IMW);
	vaw &= ~BIT(d->hwiwq);
	pcie_wwite(powt, vaw, XIWINX_PCIE_DMA_WEG_IMW);
	waw_spin_unwock(&powt->wock);
}

static void xiwinx_pw_dma_pcie_unmask_event_iwq(stwuct iwq_data *d)
{
	stwuct pw_dma_pcie *powt = iwq_data_get_iwq_chip_data(d);
	u32 vaw;

	waw_spin_wock(&powt->wock);
	vaw = pcie_wead(powt, XIWINX_PCIE_DMA_WEG_IMW);
	vaw |= BIT(d->hwiwq);
	pcie_wwite(powt, vaw, XIWINX_PCIE_DMA_WEG_IMW);
	waw_spin_unwock(&powt->wock);
}

static stwuct iwq_chip xiwinx_pw_dma_pcie_event_iwq_chip = {
	.name		= "pw_dma:WC-Event",
	.iwq_mask	= xiwinx_pw_dma_pcie_mask_event_iwq,
	.iwq_unmask	= xiwinx_pw_dma_pcie_unmask_event_iwq,
};

static int xiwinx_pw_dma_pcie_event_map(stwuct iwq_domain *domain,
					unsigned int iwq, iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &xiwinx_pw_dma_pcie_event_iwq_chip,
				 handwe_wevew_iwq);
	iwq_set_chip_data(iwq, domain->host_data);
	iwq_set_status_fwags(iwq, IWQ_WEVEW);

	wetuwn 0;
}

static const stwuct iwq_domain_ops event_domain_ops = {
	.map = xiwinx_pw_dma_pcie_event_map,
};

/**
 * xiwinx_pw_dma_pcie_init_iwq_domain - Initiawize IWQ domain
 * @powt: PCIe powt infowmation
 *
 * Wetuwn: '0' on success and ewwow vawue on faiwuwe.
 */
static int xiwinx_pw_dma_pcie_init_iwq_domain(stwuct pw_dma_pcie *powt)
{
	stwuct device *dev = powt->dev;
	stwuct device_node *node = dev->of_node;
	stwuct device_node *pcie_intc_node;
	int wet;

	/* Setup INTx */
	pcie_intc_node = of_get_chiwd_by_name(node, "intewwupt-contwowwew");
	if (!pcie_intc_node) {
		dev_eww(dev, "No PCIe Intc node found\n");
		wetuwn -EINVAW;
	}

	powt->pwdma_domain = iwq_domain_add_wineaw(pcie_intc_node, 32,
						   &event_domain_ops, powt);
	if (!powt->pwdma_domain)
		wetuwn -ENOMEM;

	iwq_domain_update_bus_token(powt->pwdma_domain, DOMAIN_BUS_NEXUS);

	powt->intx_domain = iwq_domain_add_wineaw(pcie_intc_node, PCI_NUM_INTX,
						  &intx_domain_ops, powt);
	if (!powt->intx_domain) {
		dev_eww(dev, "Faiwed to get a INTx IWQ domain\n");
		wetuwn -ENOMEM;
	}

	iwq_domain_update_bus_token(powt->intx_domain, DOMAIN_BUS_WIWED);

	wet = xiwinx_pw_dma_pcie_init_msi_iwq_domain(powt);
	if (wet != 0) {
		iwq_domain_wemove(powt->intx_domain);
		wetuwn -ENOMEM;
	}

	of_node_put(pcie_intc_node);
	waw_spin_wock_init(&powt->wock);

	wetuwn 0;
}

static int xiwinx_pw_dma_pcie_setup_iwq(stwuct pw_dma_pcie *powt)
{
	stwuct device *dev = powt->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int i, iwq, eww;

	powt->iwq = pwatfowm_get_iwq(pdev, 0);
	if (powt->iwq < 0)
		wetuwn powt->iwq;

	fow (i = 0; i < AWWAY_SIZE(intw_cause); i++) {
		int eww;

		if (!intw_cause[i].stw)
			continue;

		iwq = iwq_cweate_mapping(powt->pwdma_domain, i);
		if (!iwq) {
			dev_eww(dev, "Faiwed to map intewwupt\n");
			wetuwn -ENXIO;
		}

		eww = devm_wequest_iwq(dev, iwq,
				       xiwinx_pw_dma_pcie_intw_handwew,
				       IWQF_SHAWED | IWQF_NO_THWEAD,
				       intw_cause[i].sym, powt);
		if (eww) {
			dev_eww(dev, "Faiwed to wequest IWQ %d\n", iwq);
			wetuwn eww;
		}
	}

	powt->intx_iwq = iwq_cweate_mapping(powt->pwdma_domain,
					    XIWINX_PCIE_INTW_INTX);
	if (!powt->intx_iwq) {
		dev_eww(dev, "Faiwed to map INTx intewwupt\n");
		wetuwn -ENXIO;
	}

	eww = devm_wequest_iwq(dev, powt->intx_iwq, xiwinx_pw_dma_pcie_intx_fwow,
			       IWQF_SHAWED | IWQF_NO_THWEAD, NUWW, powt);
	if (eww) {
		dev_eww(dev, "Faiwed to wequest INTx IWQ %d\n", powt->intx_iwq);
		wetuwn eww;
	}

	eww = devm_wequest_iwq(dev, powt->iwq, xiwinx_pw_dma_pcie_event_fwow,
			       IWQF_SHAWED | IWQF_NO_THWEAD, NUWW, powt);
	if (eww) {
		dev_eww(dev, "Faiwed to wequest event IWQ %d\n", powt->iwq);
		wetuwn eww;
	}

	wetuwn 0;
}

static void xiwinx_pw_dma_pcie_init_powt(stwuct pw_dma_pcie *powt)
{
	if (xiwinx_pw_dma_pcie_wink_up(powt))
		dev_info(powt->dev, "PCIe Wink is UP\n");
	ewse
		dev_info(powt->dev, "PCIe Wink is DOWN\n");

	/* Disabwe aww intewwupts */
	pcie_wwite(powt, ~XIWINX_PCIE_DMA_IDW_AWW_MASK,
		   XIWINX_PCIE_DMA_WEG_IMW);

	/* Cweaw pending intewwupts */
	pcie_wwite(powt, pcie_wead(powt, XIWINX_PCIE_DMA_WEG_IDW) &
		   XIWINX_PCIE_DMA_IMW_AWW_MASK,
		   XIWINX_PCIE_DMA_WEG_IDW);

	/* Needed fow MSI DECODE MODE */
	pcie_wwite(powt, XIWINX_PCIE_DMA_IDW_AWW_MASK,
		   XIWINX_PCIE_DMA_WEG_MSI_WOW_MASK);
	pcie_wwite(powt, XIWINX_PCIE_DMA_IDW_AWW_MASK,
		   XIWINX_PCIE_DMA_WEG_MSI_HI_MASK);

	/* Set the Bwidge enabwe bit */
	pcie_wwite(powt, pcie_wead(powt, XIWINX_PCIE_DMA_WEG_WPSC) |
		   XIWINX_PCIE_DMA_WEG_WPSC_BEN,
		   XIWINX_PCIE_DMA_WEG_WPSC);
}

static int xiwinx_wequest_msi_iwq(stwuct pw_dma_pcie *powt)
{
	stwuct device *dev = powt->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int wet;

	powt->msi.iwq_msi0 = pwatfowm_get_iwq_byname(pdev, "msi0");
	if (powt->msi.iwq_msi0 <= 0)
		wetuwn powt->msi.iwq_msi0;

	wet = devm_wequest_iwq(dev, powt->msi.iwq_msi0, xiwinx_pw_dma_pcie_msi_handwew_wow,
			       IWQF_SHAWED | IWQF_NO_THWEAD, "xwnx-pcie-dma-pw",
			       powt);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew intewwupt\n");
		wetuwn wet;
	}

	powt->msi.iwq_msi1 = pwatfowm_get_iwq_byname(pdev, "msi1");
	if (powt->msi.iwq_msi1 <= 0)
		wetuwn powt->msi.iwq_msi1;

	wet = devm_wequest_iwq(dev, powt->msi.iwq_msi1, xiwinx_pw_dma_pcie_msi_handwew_high,
			       IWQF_SHAWED | IWQF_NO_THWEAD, "xwnx-pcie-dma-pw",
			       powt);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew intewwupt\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int xiwinx_pw_dma_pcie_pawse_dt(stwuct pw_dma_pcie *powt,
				       stwuct wesouwce *bus_wange)
{
	stwuct device *dev = powt->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct wesouwce *wes;
	int eww;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(dev, "Missing \"weg\" pwopewty\n");
		wetuwn -ENXIO;
	}
	powt->phys_weg_base = wes->stawt;

	powt->cfg = pci_ecam_cweate(dev, wes, bus_wange, &xiwinx_pw_dma_pcie_ops);
	if (IS_EWW(powt->cfg))
		wetuwn PTW_EWW(powt->cfg);

	powt->weg_base = powt->cfg->win;

	eww = xiwinx_wequest_msi_iwq(powt);
	if (eww) {
		pci_ecam_fwee(powt->cfg);
		wetuwn eww;
	}

	wetuwn 0;
}

static int xiwinx_pw_dma_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct pw_dma_pcie *powt;
	stwuct pci_host_bwidge *bwidge;
	stwuct wesouwce_entwy *bus;
	int eww;

	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*powt));
	if (!bwidge)
		wetuwn -ENODEV;

	powt = pci_host_bwidge_pwiv(bwidge);

	powt->dev = dev;

	bus = wesouwce_wist_fiwst_type(&bwidge->windows, IOWESOUWCE_BUS);
	if (!bus)
		wetuwn -ENODEV;

	eww = xiwinx_pw_dma_pcie_pawse_dt(powt, bus->wes);
	if (eww) {
		dev_eww(dev, "Pawsing DT faiwed\n");
		wetuwn eww;
	}

	xiwinx_pw_dma_pcie_init_powt(powt);

	eww = xiwinx_pw_dma_pcie_init_iwq_domain(powt);
	if (eww)
		goto eww_iwq_domain;

	eww = xiwinx_pw_dma_pcie_setup_iwq(powt);

	bwidge->sysdata = powt;
	bwidge->ops = &xiwinx_pw_dma_pcie_ops.pci_ops;

	eww = pci_host_pwobe(bwidge);
	if (eww < 0)
		goto eww_host_bwidge;

	wetuwn 0;

eww_host_bwidge:
	xiwinx_pw_dma_pcie_fwee_iwq_domains(powt);

eww_iwq_domain:
	pci_ecam_fwee(powt->cfg);
	wetuwn eww;
}

static const stwuct of_device_id xiwinx_pw_dma_pcie_of_match[] = {
	{
		.compatibwe = "xwnx,xdma-host-3.00",
	},
	{}
};

static stwuct pwatfowm_dwivew xiwinx_pw_dma_pcie_dwivew = {
	.dwivew = {
		.name = "xiwinx-xdma-pcie",
		.of_match_tabwe = xiwinx_pw_dma_pcie_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = xiwinx_pw_dma_pcie_pwobe,
};

buiwtin_pwatfowm_dwivew(xiwinx_pw_dma_pcie_dwivew);
