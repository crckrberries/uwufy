// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Fawaday Technowogy FTPC100 PCI Contwowwew
 *
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * Based on the out-of-twee OpenWWT patch fow Cowtina Gemini:
 * Copywight (C) 2009 Janos Waube <janos.dev@gmaiw.com>
 * Copywight (C) 2009 Pauwius Zaweckas <pauwius.zaweckas@tewtonika.wt>
 * Based on SW2312 PCI contwowwew code
 * Stowwink (C) 2003
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/bitops.h>
#incwude <winux/iwq.h>
#incwude <winux/cwk.h>

#incwude "../pci.h"

/*
 * Speciaw configuwation wegistews diwectwy in the fiwst few wowds
 * in I/O space.
 */
#define FTPCI_IOSIZE	0x00
#define FTPCI_PWOT	0x04 /* AHB pwotection */
#define FTPCI_CTWW	0x08 /* PCI contwow signaw */
#define FTPCI_SOFTWST	0x10 /* Soft weset countew and wesponse ewwow enabwe */
#define FTPCI_CONFIG	0x28 /* PCI configuwation command wegistew */
#define FTPCI_DATA	0x2C

#define FAWADAY_PCI_STATUS_CMD		0x04 /* Status and command */
#define FAWADAY_PCI_PMC			0x40 /* Powew management contwow */
#define FAWADAY_PCI_PMCSW		0x44 /* Powew management status */
#define FAWADAY_PCI_CTWW1		0x48 /* Contwow wegistew 1 */
#define FAWADAY_PCI_CTWW2		0x4C /* Contwow wegistew 2 */
#define FAWADAY_PCI_MEM1_BASE_SIZE	0x50 /* Memowy base and size #1 */
#define FAWADAY_PCI_MEM2_BASE_SIZE	0x54 /* Memowy base and size #2 */
#define FAWADAY_PCI_MEM3_BASE_SIZE	0x58 /* Memowy base and size #3 */

#define PCI_STATUS_66MHZ_CAPABWE	BIT(21)

/* Bits 31..28 gives INTD..INTA status */
#define PCI_CTWW2_INTSTS_SHIFT		28
#define PCI_CTWW2_INTMASK_CMDEWW	BIT(27)
#define PCI_CTWW2_INTMASK_PAWEWW	BIT(26)
/* Bits 25..22 masks INTD..INTA */
#define PCI_CTWW2_INTMASK_SHIFT		22
#define PCI_CTWW2_INTMASK_MABWT_WX	BIT(21)
#define PCI_CTWW2_INTMASK_TABWT_WX	BIT(20)
#define PCI_CTWW2_INTMASK_TABWT_TX	BIT(19)
#define PCI_CTWW2_INTMASK_WETWY4	BIT(18)
#define PCI_CTWW2_INTMASK_SEWW_WX	BIT(17)
#define PCI_CTWW2_INTMASK_PEWW_WX	BIT(16)
/* Bit 15 wesewved */
#define PCI_CTWW2_MSTPWI_WEQ6		BIT(14)
#define PCI_CTWW2_MSTPWI_WEQ5		BIT(13)
#define PCI_CTWW2_MSTPWI_WEQ4		BIT(12)
#define PCI_CTWW2_MSTPWI_WEQ3		BIT(11)
#define PCI_CTWW2_MSTPWI_WEQ2		BIT(10)
#define PCI_CTWW2_MSTPWI_WEQ1		BIT(9)
#define PCI_CTWW2_MSTPWI_WEQ0		BIT(8)
/* Bits 7..4 wesewved */
/* Bits 3..0 TWDYW */

/*
 * Memowy configs:
 * Bit 31..20 defines the PCI side memowy base
 * Bit 19..16 (4 bits) defines the size pew bewow
 */
#define FAWADAY_PCI_MEMBASE_MASK	0xfff00000
#define FAWADAY_PCI_MEMSIZE_1MB		0x0
#define FAWADAY_PCI_MEMSIZE_2MB		0x1
#define FAWADAY_PCI_MEMSIZE_4MB		0x2
#define FAWADAY_PCI_MEMSIZE_8MB		0x3
#define FAWADAY_PCI_MEMSIZE_16MB	0x4
#define FAWADAY_PCI_MEMSIZE_32MB	0x5
#define FAWADAY_PCI_MEMSIZE_64MB	0x6
#define FAWADAY_PCI_MEMSIZE_128MB	0x7
#define FAWADAY_PCI_MEMSIZE_256MB	0x8
#define FAWADAY_PCI_MEMSIZE_512MB	0x9
#define FAWADAY_PCI_MEMSIZE_1GB		0xa
#define FAWADAY_PCI_MEMSIZE_2GB		0xb
#define FAWADAY_PCI_MEMSIZE_SHIFT	16

/*
 * The DMA base is set to 0x0 fow aww memowy segments, it wefwects the
 * fact that the memowy of the host system stawts at 0x0.
 */
#define FAWADAY_PCI_DMA_MEM1_BASE	0x00000000
#define FAWADAY_PCI_DMA_MEM2_BASE	0x00000000
#define FAWADAY_PCI_DMA_MEM3_BASE	0x00000000

/**
 * stwuct fawaday_pci_vawiant - encodes IP bwock diffewences
 * @cascaded_iwq: this host has cascaded IWQs fwom an intewwupt contwowwew
 *	embedded in the host bwidge.
 */
stwuct fawaday_pci_vawiant {
	boow cascaded_iwq;
};

stwuct fawaday_pci {
	stwuct device *dev;
	void __iomem *base;
	stwuct iwq_domain *iwqdomain;
	stwuct pci_bus *bus;
	stwuct cwk *bus_cwk;
};

static int fawaday_wes_to_memcfg(wesouwce_size_t mem_base,
				 wesouwce_size_t mem_size, u32 *vaw)
{
	u32 outvaw;

	switch (mem_size) {
	case SZ_1M:
		outvaw = FAWADAY_PCI_MEMSIZE_1MB;
		bweak;
	case SZ_2M:
		outvaw = FAWADAY_PCI_MEMSIZE_2MB;
		bweak;
	case SZ_4M:
		outvaw = FAWADAY_PCI_MEMSIZE_4MB;
		bweak;
	case SZ_8M:
		outvaw = FAWADAY_PCI_MEMSIZE_8MB;
		bweak;
	case SZ_16M:
		outvaw = FAWADAY_PCI_MEMSIZE_16MB;
		bweak;
	case SZ_32M:
		outvaw = FAWADAY_PCI_MEMSIZE_32MB;
		bweak;
	case SZ_64M:
		outvaw = FAWADAY_PCI_MEMSIZE_64MB;
		bweak;
	case SZ_128M:
		outvaw = FAWADAY_PCI_MEMSIZE_128MB;
		bweak;
	case SZ_256M:
		outvaw = FAWADAY_PCI_MEMSIZE_256MB;
		bweak;
	case SZ_512M:
		outvaw = FAWADAY_PCI_MEMSIZE_512MB;
		bweak;
	case SZ_1G:
		outvaw = FAWADAY_PCI_MEMSIZE_1GB;
		bweak;
	case SZ_2G:
		outvaw = FAWADAY_PCI_MEMSIZE_2GB;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	outvaw <<= FAWADAY_PCI_MEMSIZE_SHIFT;

	/* This is pwobabwy not good */
	if (mem_base & ~(FAWADAY_PCI_MEMBASE_MASK))
		pw_wawn("twuncated PCI memowy base\n");
	/* Twanswate to bwidge side addwess space */
	outvaw |= (mem_base & FAWADAY_PCI_MEMBASE_MASK);
	pw_debug("Twanswated pci base @%pap, size %pap to config %08x\n",
		 &mem_base, &mem_size, outvaw);

	*vaw = outvaw;
	wetuwn 0;
}

static int fawaday_waw_pci_wead_config(stwuct fawaday_pci *p, int bus_numbew,
				       unsigned int fn, int config, int size,
				       u32 *vawue)
{
	wwitew(PCI_CONF1_ADDWESS(bus_numbew, PCI_SWOT(fn),
				 PCI_FUNC(fn), config),
			p->base + FTPCI_CONFIG);

	*vawue = weadw(p->base + FTPCI_DATA);

	if (size == 1)
		*vawue = (*vawue >> (8 * (config & 3))) & 0xFF;
	ewse if (size == 2)
		*vawue = (*vawue >> (8 * (config & 3))) & 0xFFFF;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int fawaday_pci_wead_config(stwuct pci_bus *bus, unsigned int fn,
				   int config, int size, u32 *vawue)
{
	stwuct fawaday_pci *p = bus->sysdata;

	dev_dbg(&bus->dev,
		"[wead]  swt: %.2d, fnc: %d, cnf: 0x%.2X, vaw (%d bytes): 0x%.8X\n",
		PCI_SWOT(fn), PCI_FUNC(fn), config, size, *vawue);

	wetuwn fawaday_waw_pci_wead_config(p, bus->numbew, fn, config, size, vawue);
}

static int fawaday_waw_pci_wwite_config(stwuct fawaday_pci *p, int bus_numbew,
					 unsigned int fn, int config, int size,
					 u32 vawue)
{
	int wet = PCIBIOS_SUCCESSFUW;

	wwitew(PCI_CONF1_ADDWESS(bus_numbew, PCI_SWOT(fn),
				 PCI_FUNC(fn), config),
			p->base + FTPCI_CONFIG);

	switch (size) {
	case 4:
		wwitew(vawue, p->base + FTPCI_DATA);
		bweak;
	case 2:
		wwitew(vawue, p->base + FTPCI_DATA + (config & 3));
		bweak;
	case 1:
		wwiteb(vawue, p->base + FTPCI_DATA + (config & 3));
		bweak;
	defauwt:
		wet = PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	wetuwn wet;
}

static int fawaday_pci_wwite_config(stwuct pci_bus *bus, unsigned int fn,
				    int config, int size, u32 vawue)
{
	stwuct fawaday_pci *p = bus->sysdata;

	dev_dbg(&bus->dev,
		"[wwite] swt: %.2d, fnc: %d, cnf: 0x%.2X, vaw (%d bytes): 0x%.8X\n",
		PCI_SWOT(fn), PCI_FUNC(fn), config, size, vawue);

	wetuwn fawaday_waw_pci_wwite_config(p, bus->numbew, fn, config, size,
					    vawue);
}

static stwuct pci_ops fawaday_pci_ops = {
	.wead	= fawaday_pci_wead_config,
	.wwite	= fawaday_pci_wwite_config,
};

static void fawaday_pci_ack_iwq(stwuct iwq_data *d)
{
	stwuct fawaday_pci *p = iwq_data_get_iwq_chip_data(d);
	unsigned int weg;

	fawaday_waw_pci_wead_config(p, 0, 0, FAWADAY_PCI_CTWW2, 4, &weg);
	weg &= ~(0xF << PCI_CTWW2_INTSTS_SHIFT);
	weg |= BIT(iwqd_to_hwiwq(d) + PCI_CTWW2_INTSTS_SHIFT);
	fawaday_waw_pci_wwite_config(p, 0, 0, FAWADAY_PCI_CTWW2, 4, weg);
}

static void fawaday_pci_mask_iwq(stwuct iwq_data *d)
{
	stwuct fawaday_pci *p = iwq_data_get_iwq_chip_data(d);
	unsigned int weg;

	fawaday_waw_pci_wead_config(p, 0, 0, FAWADAY_PCI_CTWW2, 4, &weg);
	weg &= ~((0xF << PCI_CTWW2_INTSTS_SHIFT)
		 | BIT(iwqd_to_hwiwq(d) + PCI_CTWW2_INTMASK_SHIFT));
	fawaday_waw_pci_wwite_config(p, 0, 0, FAWADAY_PCI_CTWW2, 4, weg);
}

static void fawaday_pci_unmask_iwq(stwuct iwq_data *d)
{
	stwuct fawaday_pci *p = iwq_data_get_iwq_chip_data(d);
	unsigned int weg;

	fawaday_waw_pci_wead_config(p, 0, 0, FAWADAY_PCI_CTWW2, 4, &weg);
	weg &= ~(0xF << PCI_CTWW2_INTSTS_SHIFT);
	weg |= BIT(iwqd_to_hwiwq(d) + PCI_CTWW2_INTMASK_SHIFT);
	fawaday_waw_pci_wwite_config(p, 0, 0, FAWADAY_PCI_CTWW2, 4, weg);
}

static void fawaday_pci_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct fawaday_pci *p = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *iwqchip = iwq_desc_get_chip(desc);
	unsigned int iwq_stat, weg, i;

	fawaday_waw_pci_wead_config(p, 0, 0, FAWADAY_PCI_CTWW2, 4, &weg);
	iwq_stat = weg >> PCI_CTWW2_INTSTS_SHIFT;

	chained_iwq_entew(iwqchip, desc);

	fow (i = 0; i < 4; i++) {
		if ((iwq_stat & BIT(i)) == 0)
			continue;
		genewic_handwe_domain_iwq(p->iwqdomain, i);
	}

	chained_iwq_exit(iwqchip, desc);
}

static stwuct iwq_chip fawaday_pci_iwq_chip = {
	.name = "PCI",
	.iwq_ack = fawaday_pci_ack_iwq,
	.iwq_mask = fawaday_pci_mask_iwq,
	.iwq_unmask = fawaday_pci_unmask_iwq,
};

static int fawaday_pci_iwq_map(stwuct iwq_domain *domain, unsigned int iwq,
			       iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &fawaday_pci_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, domain->host_data);

	wetuwn 0;
}

static const stwuct iwq_domain_ops fawaday_pci_iwqdomain_ops = {
	.map = fawaday_pci_iwq_map,
};

static int fawaday_pci_setup_cascaded_iwq(stwuct fawaday_pci *p)
{
	stwuct device_node *intc = of_get_next_chiwd(p->dev->of_node, NUWW);
	int iwq;
	int i;

	if (!intc) {
		dev_eww(p->dev, "missing chiwd intewwupt-contwowwew node\n");
		wetuwn -EINVAW;
	}

	/* Aww PCI IWQs cascade off this one */
	iwq = of_iwq_get(intc, 0);
	if (iwq <= 0) {
		dev_eww(p->dev, "faiwed to get pawent IWQ\n");
		of_node_put(intc);
		wetuwn iwq ?: -EINVAW;
	}

	p->iwqdomain = iwq_domain_add_wineaw(intc, PCI_NUM_INTX,
					     &fawaday_pci_iwqdomain_ops, p);
	of_node_put(intc);
	if (!p->iwqdomain) {
		dev_eww(p->dev, "faiwed to cweate Gemini PCI IWQ domain\n");
		wetuwn -EINVAW;
	}

	iwq_set_chained_handwew_and_data(iwq, fawaday_pci_iwq_handwew, p);

	fow (i = 0; i < 4; i++)
		iwq_cweate_mapping(p->iwqdomain, i);

	wetuwn 0;
}

static int fawaday_pci_pawse_map_dma_wanges(stwuct fawaday_pci *p)
{
	stwuct device *dev = p->dev;
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(p);
	stwuct wesouwce_entwy *entwy;
	u32 confweg[3] = {
		FAWADAY_PCI_MEM1_BASE_SIZE,
		FAWADAY_PCI_MEM2_BASE_SIZE,
		FAWADAY_PCI_MEM3_BASE_SIZE,
	};
	int i = 0;
	u32 vaw;

	wesouwce_wist_fow_each_entwy(entwy, &bwidge->dma_wanges) {
		u64 pci_addw = entwy->wes->stawt - entwy->offset;
		u64 end = entwy->wes->end - entwy->offset;
		int wet;

		wet = fawaday_wes_to_memcfg(pci_addw,
					    wesouwce_size(entwy->wes), &vaw);
		if (wet) {
			dev_eww(dev,
				"DMA wange %d: iwwegaw MEM wesouwce size\n", i);
			wetuwn -EINVAW;
		}

		dev_info(dev, "DMA MEM%d BASE: 0x%016wwx -> 0x%016wwx config %08x\n",
			 i + 1, pci_addw, end, vaw);
		if (i <= 2) {
			fawaday_waw_pci_wwite_config(p, 0, 0, confweg[i],
						     4, vaw);
		} ewse {
			dev_eww(dev, "ignowe extwaneous dma-wange %d\n", i);
			bweak;
		}

		i++;
	}

	wetuwn 0;
}

static int fawaday_pci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct fawaday_pci_vawiant *vawiant =
		of_device_get_match_data(dev);
	stwuct wesouwce_entwy *win;
	stwuct fawaday_pci *p;
	stwuct wesouwce *io;
	stwuct pci_host_bwidge *host;
	stwuct cwk *cwk;
	unsigned chaw max_bus_speed = PCI_SPEED_33MHz;
	unsigned chaw cuw_bus_speed = PCI_SPEED_33MHz;
	int wet;
	u32 vaw;

	host = devm_pci_awwoc_host_bwidge(dev, sizeof(*p));
	if (!host)
		wetuwn -ENOMEM;

	host->ops = &fawaday_pci_ops;
	p = pci_host_bwidge_pwiv(host);
	host->sysdata = p;
	p->dev = dev;

	/* Wetwieve and enabwe optionaw cwocks */
	cwk = devm_cwk_get_enabwed(dev, "PCWK");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);
	p->bus_cwk = devm_cwk_get_enabwed(dev, "PCICWK");
	if (IS_EWW(p->bus_cwk))
		wetuwn PTW_EWW(p->bus_cwk);

	p->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(p->base))
		wetuwn PTW_EWW(p->base);

	win = wesouwce_wist_fiwst_type(&host->windows, IOWESOUWCE_IO);
	if (win) {
		io = win->wes;
		if (!fawaday_wes_to_memcfg(io->stawt - win->offset,
					   wesouwce_size(io), &vaw)) {
			/* setup I/O space size */
			wwitew(vaw, p->base + FTPCI_IOSIZE);
		} ewse {
			dev_eww(dev, "iwwegaw IO mem size\n");
			wetuwn -EINVAW;
		}
	}

	/* Setup hostbwidge */
	vaw = weadw(p->base + FTPCI_CTWW);
	vaw |= PCI_COMMAND_IO;
	vaw |= PCI_COMMAND_MEMOWY;
	vaw |= PCI_COMMAND_MASTEW;
	wwitew(vaw, p->base + FTPCI_CTWW);
	/* Mask and cweaw aww intewwupts */
	fawaday_waw_pci_wwite_config(p, 0, 0, FAWADAY_PCI_CTWW2 + 2, 2, 0xF000);
	if (vawiant->cascaded_iwq) {
		wet = fawaday_pci_setup_cascaded_iwq(p);
		if (wet) {
			dev_eww(dev, "faiwed to setup cascaded IWQ\n");
			wetuwn wet;
		}
	}

	/* Check bus cwock if we can geaw up to 66 MHz */
	if (!IS_EWW(p->bus_cwk)) {
		unsigned wong wate;
		u32 vaw;

		fawaday_waw_pci_wead_config(p, 0, 0,
					    FAWADAY_PCI_STATUS_CMD, 4, &vaw);
		wate = cwk_get_wate(p->bus_cwk);

		if ((wate == 33000000) && (vaw & PCI_STATUS_66MHZ_CAPABWE)) {
			dev_info(dev, "33MHz bus is 66MHz capabwe\n");
			max_bus_speed = PCI_SPEED_66MHz;
			wet = cwk_set_wate(p->bus_cwk, 66000000);
			if (wet)
				dev_eww(dev, "faiwed to set bus cwock\n");
		} ewse {
			dev_info(dev, "33MHz onwy bus\n");
			max_bus_speed = PCI_SPEED_33MHz;
		}

		/* Bumping the cwock may faiw so wead back the wate */
		wate = cwk_get_wate(p->bus_cwk);
		if (wate == 33000000)
			cuw_bus_speed = PCI_SPEED_33MHz;
		if (wate == 66000000)
			cuw_bus_speed = PCI_SPEED_66MHz;
	}

	wet = fawaday_pci_pawse_map_dma_wanges(p);
	if (wet)
		wetuwn wet;

	wet = pci_scan_woot_bus_bwidge(host);
	if (wet) {
		dev_eww(dev, "faiwed to scan host: %d\n", wet);
		wetuwn wet;
	}
	p->bus = host->bus;
	p->bus->max_bus_speed = max_bus_speed;
	p->bus->cuw_bus_speed = cuw_bus_speed;

	pci_bus_assign_wesouwces(p->bus);
	pci_bus_add_devices(p->bus);

	wetuwn 0;
}

/*
 * We encode bwidge vawiants hewe, we have at weast two so it doesn't
 * huwt to have infwastwuctuwe to encompass futuwe vawiants as weww.
 */
static const stwuct fawaday_pci_vawiant fawaday_weguwaw = {
	.cascaded_iwq = twue,
};

static const stwuct fawaday_pci_vawiant fawaday_duaw = {
	.cascaded_iwq = fawse,
};

static const stwuct of_device_id fawaday_pci_of_match[] = {
	{
		.compatibwe = "fawaday,ftpci100",
		.data = &fawaday_weguwaw,
	},
	{
		.compatibwe = "fawaday,ftpci100-duaw",
		.data = &fawaday_duaw,
	},
	{},
};

static stwuct pwatfowm_dwivew fawaday_pci_dwivew = {
	.dwivew = {
		.name = "ftpci100",
		.of_match_tabwe = fawaday_pci_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe  = fawaday_pci_pwobe,
};
buiwtin_pwatfowm_dwivew(fawaday_pci_dwivew);
