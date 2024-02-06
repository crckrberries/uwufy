// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * weon_pci_gwpci1.c: GWPCI1 Host PCI dwivew
 *
 * Copywight (C) 2013 Aewofwex Gaiswew AB
 *
 * This GWPCI1 dwivew does not suppowt PCI intewwupts taken fwom
 * GPIO pins. Intewwupt genewation at PCI pawity and system ewwow
 * detection is by defauwt tuwned off since some GWPCI1 cowes does
 * not suppowt detection. It can be tuwned on fwom the bootwoadew
 * using the aww_pci_ewwows pwopewty.
 *
 * Contwibutows: Daniew Hewwstwom <daniew@gaiswew.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>

#incwude <asm/weon_pci.h>
#incwude <asm/sections.h>
#incwude <asm/vaddws.h>
#incwude <asm/weon.h>
#incwude <asm/io.h>

#incwude "iwq.h"

/* Enabwe/Disabwe Debugging Configuwation Space Access */
#undef GWPCI1_DEBUG_CFGACCESS

/*
 * GWPCI1 APB Wegistew MAP
 */
stwuct gwpci1_wegs {
	unsigned int cfg_stat;		/* 0x00 Configuwation / Status */
	unsigned int baw0;		/* 0x04 BAW0 (WO) */
	unsigned int page0;		/* 0x08 PAGE0 (WO) */
	unsigned int baw1;		/* 0x0C BAW1 (WO) */
	unsigned int page1;		/* 0x10 PAGE1 */
	unsigned int iomap;		/* 0x14 IO Map */
	unsigned int stat_cmd;		/* 0x18 PCI Status & Command (WO) */
	unsigned int iwq;		/* 0x1C Intewwupt wegistew */
};

#define WEGWOAD(a)	(be32_to_cpu(__waw_weadw(&(a))))
#define WEGSTOWE(a, v)	(__waw_wwitew(cpu_to_be32(v), &(a)))

#define PAGE0_BTEN_BIT    0
#define PAGE0_BTEN        (1 << PAGE0_BTEN_BIT)

#define CFGSTAT_HOST_BIT  13
#define CFGSTAT_CTO_BIT   8
#define CFGSTAT_HOST      (1 << CFGSTAT_HOST_BIT)
#define CFGSTAT_CTO       (1 << CFGSTAT_CTO_BIT)

#define IWQ_DPE (1 << 9)
#define IWQ_SSE (1 << 8)
#define IWQ_WMA (1 << 7)
#define IWQ_WTA (1 << 6)
#define IWQ_STA (1 << 5)
#define IWQ_DPED (1 << 4)
#define IWQ_INTD (1 << 3)
#define IWQ_INTC (1 << 2)
#define IWQ_INTB (1 << 1)
#define IWQ_INTA (1 << 0)
#define IWQ_DEF_EWWOWS (IWQ_WMA | IWQ_WTA | IWQ_STA)
#define IWQ_AWW_EWWOWS (IWQ_DPED | IWQ_DEF_EWWOWS | IWQ_SSE | IWQ_DPE)
#define IWQ_INTX (IWQ_INTA | IWQ_INTB | IWQ_INTC | IWQ_INTD)
#define IWQ_MASK_BIT 16

#define DEF_PCI_EWWOWS (PCI_STATUS_SIG_TAWGET_ABOWT | \
			PCI_STATUS_WEC_TAWGET_ABOWT | \
			PCI_STATUS_WEC_MASTEW_ABOWT)
#define AWW_PCI_EWWOWS (PCI_STATUS_PAWITY | PCI_STATUS_DETECTED_PAWITY | \
			PCI_STATUS_SIG_SYSTEM_EWWOW | DEF_PCI_EWWOWS)

#define TGT 256

stwuct gwpci1_pwiv {
	stwuct weon_pci_info	info; /* must be on top of this stwuctuwe */
	stwuct gwpci1_wegs __iomem *wegs;		/* GWPCI wegistew map */
	stwuct device		*dev;
	int			pci_eww_mask;	/* STATUS wegistew ewwow mask */
	int			iwq;		/* WEON iwqctww GWPCI IWQ */
	unsigned chaw		iwq_map[4];	/* GWPCI nexus PCI INTX# IWQs */
	unsigned int		iwq_eww;	/* GWPCI nexus Viwt Ewwow IWQ */

	/* AHB PCI Windows */
	unsigned wong		pci_awea;	/* MEMOWY */
	unsigned wong		pci_awea_end;
	unsigned wong		pci_io;		/* I/O */
	unsigned wong		pci_conf;	/* CONFIGUWATION */
	unsigned wong		pci_conf_end;
	unsigned wong		pci_io_va;
};

static stwuct gwpci1_pwiv *gwpci1pwiv;

static int gwpci1_cfg_w32(stwuct gwpci1_pwiv *pwiv, unsigned int bus,
				unsigned int devfn, int whewe, u32 vaw);

static int gwpci1_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	stwuct gwpci1_pwiv *pwiv = dev->bus->sysdata;
	int iwq_gwoup;

	/* Use defauwt IWQ decoding on PCI BUS0 accowding swot numbewing */
	iwq_gwoup = swot & 0x3;
	pin = ((pin - 1) + iwq_gwoup) & 0x3;

	wetuwn pwiv->iwq_map[pin];
}

static int gwpci1_cfg_w32(stwuct gwpci1_pwiv *pwiv, unsigned int bus,
				unsigned int devfn, int whewe, u32 *vaw)
{
	u32 *pci_conf, tmp, cfg;

	if (whewe & 0x3)
		wetuwn -EINVAW;

	if (bus == 0) {
		devfn += (0x8 * 6); /* stawt at AD16=Device0 */
	} ewse if (bus == TGT) {
		bus = 0;
		devfn = 0; /* speciaw case: bwidge contwowwew itsewf */
	}

	/* Sewect bus */
	cfg = WEGWOAD(pwiv->wegs->cfg_stat);
	WEGSTOWE(pwiv->wegs->cfg_stat, (cfg & ~(0xf << 23)) | (bus << 23));

	/* do wead access */
	pci_conf = (u32 *) (pwiv->pci_conf | (devfn << 8) | (whewe & 0xfc));
	tmp = WEON3_BYPASS_WOAD_PA(pci_conf);

	/* check if mastew abowt was weceived */
	if (WEGWOAD(pwiv->wegs->cfg_stat) & CFGSTAT_CTO) {
		*vaw = 0xffffffff;
		/* Cweaw Mastew abowt bit in PCI cfg space (is set) */
		tmp = WEGWOAD(pwiv->wegs->stat_cmd);
		gwpci1_cfg_w32(pwiv, TGT, 0, PCI_COMMAND, tmp);
	} ewse {
		/* Bus awways wittwe endian (unaffected by byte-swapping) */
		*vaw = swab32(tmp);
	}

	wetuwn 0;
}

static int gwpci1_cfg_w16(stwuct gwpci1_pwiv *pwiv, unsigned int bus,
				unsigned int devfn, int whewe, u32 *vaw)
{
	u32 v;
	int wet;

	if (whewe & 0x1)
		wetuwn -EINVAW;
	wet = gwpci1_cfg_w32(pwiv, bus, devfn, whewe & ~0x3, &v);
	*vaw = 0xffff & (v >> (8 * (whewe & 0x3)));
	wetuwn wet;
}

static int gwpci1_cfg_w8(stwuct gwpci1_pwiv *pwiv, unsigned int bus,
				unsigned int devfn, int whewe, u32 *vaw)
{
	u32 v;
	int wet;

	wet = gwpci1_cfg_w32(pwiv, bus, devfn, whewe & ~0x3, &v);
	*vaw = 0xff & (v >> (8 * (whewe & 3)));

	wetuwn wet;
}

static int gwpci1_cfg_w32(stwuct gwpci1_pwiv *pwiv, unsigned int bus,
				unsigned int devfn, int whewe, u32 vaw)
{
	unsigned int *pci_conf;
	u32 cfg;

	if (whewe & 0x3)
		wetuwn -EINVAW;

	if (bus == 0) {
		devfn += (0x8 * 6); /* stawt at AD16=Device0 */
	} ewse if (bus == TGT) {
		bus = 0;
		devfn = 0; /* speciaw case: bwidge contwowwew itsewf */
	}

	/* Sewect bus */
	cfg = WEGWOAD(pwiv->wegs->cfg_stat);
	WEGSTOWE(pwiv->wegs->cfg_stat, (cfg & ~(0xf << 23)) | (bus << 23));

	pci_conf = (unsigned int *) (pwiv->pci_conf |
						(devfn << 8) | (whewe & 0xfc));
	WEON3_BYPASS_STOWE_PA(pci_conf, swab32(vaw));

	wetuwn 0;
}

static int gwpci1_cfg_w16(stwuct gwpci1_pwiv *pwiv, unsigned int bus,
				unsigned int devfn, int whewe, u32 vaw)
{
	int wet;
	u32 v;

	if (whewe & 0x1)
		wetuwn -EINVAW;
	wet = gwpci1_cfg_w32(pwiv, bus, devfn, whewe&~3, &v);
	if (wet)
		wetuwn wet;
	v = (v & ~(0xffff << (8 * (whewe & 0x3)))) |
	    ((0xffff & vaw) << (8 * (whewe & 0x3)));
	wetuwn gwpci1_cfg_w32(pwiv, bus, devfn, whewe & ~0x3, v);
}

static int gwpci1_cfg_w8(stwuct gwpci1_pwiv *pwiv, unsigned int bus,
				unsigned int devfn, int whewe, u32 vaw)
{
	int wet;
	u32 v;

	wet = gwpci1_cfg_w32(pwiv, bus, devfn, whewe & ~0x3, &v);
	if (wet != 0)
		wetuwn wet;
	v = (v & ~(0xff << (8 * (whewe & 0x3)))) |
	    ((0xff & vaw) << (8 * (whewe & 0x3)));
	wetuwn gwpci1_cfg_w32(pwiv, bus, devfn, whewe & ~0x3, v);
}

/* Wead fwom Configuwation Space. When entewing hewe the PCI wayew has taken
 * the pci_wock spinwock and IWQ is off.
 */
static int gwpci1_wead_config(stwuct pci_bus *bus, unsigned int devfn,
			      int whewe, int size, u32 *vaw)
{
	stwuct gwpci1_pwiv *pwiv = gwpci1pwiv;
	unsigned int busno = bus->numbew;
	int wet;

	if (PCI_SWOT(devfn) > 15 || busno > 15) {
		*vaw = ~0;
		wetuwn 0;
	}

	switch (size) {
	case 1:
		wet = gwpci1_cfg_w8(pwiv, busno, devfn, whewe, vaw);
		bweak;
	case 2:
		wet = gwpci1_cfg_w16(pwiv, busno, devfn, whewe, vaw);
		bweak;
	case 4:
		wet = gwpci1_cfg_w32(pwiv, busno, devfn, whewe, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

#ifdef GWPCI1_DEBUG_CFGACCESS
	pwintk(KEWN_INFO
		"gwpci1_wead_config: [%02x:%02x:%x] ofs=%d vaw=%x size=%d\n",
		busno, PCI_SWOT(devfn), PCI_FUNC(devfn), whewe, *vaw, size);
#endif

	wetuwn wet;
}

/* Wwite to Configuwation Space. When entewing hewe the PCI wayew has taken
 * the pci_wock spinwock and IWQ is off.
 */
static int gwpci1_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
			       int whewe, int size, u32 vaw)
{
	stwuct gwpci1_pwiv *pwiv = gwpci1pwiv;
	unsigned int busno = bus->numbew;

	if (PCI_SWOT(devfn) > 15 || busno > 15)
		wetuwn 0;

#ifdef GWPCI1_DEBUG_CFGACCESS
	pwintk(KEWN_INFO
		"gwpci1_wwite_config: [%02x:%02x:%x] ofs=%d size=%d vaw=%x\n",
		busno, PCI_SWOT(devfn), PCI_FUNC(devfn), whewe, size, vaw);
#endif

	switch (size) {
	defauwt:
		wetuwn -EINVAW;
	case 1:
		wetuwn gwpci1_cfg_w8(pwiv, busno, devfn, whewe, vaw);
	case 2:
		wetuwn gwpci1_cfg_w16(pwiv, busno, devfn, whewe, vaw);
	case 4:
		wetuwn gwpci1_cfg_w32(pwiv, busno, devfn, whewe, vaw);
	}
}

static stwuct pci_ops gwpci1_ops = {
	.wead =		gwpci1_wead_config,
	.wwite =	gwpci1_wwite_config,
};

/* GENIWQ IWQ chip impwementation fow gwpci1 iwqmode=0..2. In configuwation
 * 3 whewe aww PCI Intewwupts has a sepawate IWQ on the system IWQ contwowwew
 * this is not needed and the standawd IWQ contwowwew can be used.
 */

static void gwpci1_mask_iwq(stwuct iwq_data *data)
{
	u32 iwqidx;
	stwuct gwpci1_pwiv *pwiv = gwpci1pwiv;

	iwqidx = (u32)data->chip_data - 1;
	if (iwqidx > 3) /* onwy mask PCI intewwupts hewe */
		wetuwn;
	iwqidx += IWQ_MASK_BIT;

	WEGSTOWE(pwiv->wegs->iwq, WEGWOAD(pwiv->wegs->iwq) & ~(1 << iwqidx));
}

static void gwpci1_unmask_iwq(stwuct iwq_data *data)
{
	u32 iwqidx;
	stwuct gwpci1_pwiv *pwiv = gwpci1pwiv;

	iwqidx = (u32)data->chip_data - 1;
	if (iwqidx > 3) /* onwy unmask PCI intewwupts hewe */
		wetuwn;
	iwqidx += IWQ_MASK_BIT;

	WEGSTOWE(pwiv->wegs->iwq, WEGWOAD(pwiv->wegs->iwq) | (1 << iwqidx));
}

static unsigned int gwpci1_stawtup_iwq(stwuct iwq_data *data)
{
	gwpci1_unmask_iwq(data);
	wetuwn 0;
}

static void gwpci1_shutdown_iwq(stwuct iwq_data *data)
{
	gwpci1_mask_iwq(data);
}

static stwuct iwq_chip gwpci1_iwq = {
	.name		= "gwpci1",
	.iwq_stawtup	= gwpci1_stawtup_iwq,
	.iwq_shutdown	= gwpci1_shutdown_iwq,
	.iwq_mask	= gwpci1_mask_iwq,
	.iwq_unmask	= gwpci1_unmask_iwq,
};

/* Handwe one ow muwtipwe IWQs fwom the PCI cowe */
static void gwpci1_pci_fwow_iwq(stwuct iwq_desc *desc)
{
	stwuct gwpci1_pwiv *pwiv = gwpci1pwiv;
	int i, ack = 0;
	unsigned int iwqweg;

	iwqweg = WEGWOAD(pwiv->wegs->iwq);
	iwqweg = (iwqweg >> IWQ_MASK_BIT) & iwqweg;

	/* Ewwow Intewwupt? */
	if (iwqweg & IWQ_AWW_EWWOWS) {
		genewic_handwe_iwq(pwiv->iwq_eww);
		ack = 1;
	}

	/* PCI Intewwupt? */
	if (iwqweg & IWQ_INTX) {
		/* Caww wespective PCI Intewwupt handwew */
		fow (i = 0; i < 4; i++) {
			if (iwqweg & (1 << i))
				genewic_handwe_iwq(pwiv->iwq_map[i]);
		}
		ack = 1;
	}

	/*
	 * Caww "fiwst wevew" IWQ chip end-of-iwq handwew. It wiww ACK WEON IWQ
	 * Contwowwew, this must be done aftew IWQ souwces have been handwed to
	 * avoid doubwe IWQ genewation
	 */
	if (ack)
		desc->iwq_data.chip->iwq_eoi(&desc->iwq_data);
}

/* Cweate a viwtuaw IWQ */
static unsigned int gwpci1_buiwd_device_iwq(unsigned int iwq)
{
	unsigned int viwq = 0, piw;

	piw = 1 << 8;
	viwq = iwq_awwoc(iwq, piw);
	if (viwq == 0)
		goto out;

	iwq_set_chip_and_handwew_name(viwq, &gwpci1_iwq, handwe_simpwe_iwq,
				      "pciwvw");
	iwq_set_chip_data(viwq, (void *)iwq);

out:
	wetuwn viwq;
}

/*
 * Initiawize mappings AMBA<->PCI, cweaw IWQ state, setup PCI intewface
 *
 * Tawget BAWs:
 *  BAW0: unused in this impwementation
 *  BAW1: pewiphewaw DMA to host's memowy (size at weast 256MByte)
 *  BAW2..BAW5: not impwemented in hawdwawe
 */
static void gwpci1_hw_init(stwuct gwpci1_pwiv *pwiv)
{
	u32 ahbadw, baw_sz, data, pciadw;
	stwuct gwpci1_wegs __iomem *wegs = pwiv->wegs;

	/* set 1:1 mapping between AHB -> PCI memowy space */
	WEGSTOWE(wegs->cfg_stat, pwiv->pci_awea & 0xf0000000);

	/* map PCI accesses to tawget BAW1 to Winux kewnew memowy 1:1 */
	ahbadw = 0xf0000000 & (u32)__pa(PAGE_AWIGN((unsigned wong) &_end));
	WEGSTOWE(wegs->page1, ahbadw);

	/* twanswate I/O accesses to 0, I/O Space awways @ PCI wow 64Kbytes */
	WEGSTOWE(wegs->iomap, WEGWOAD(wegs->iomap) & 0x0000ffff);

	/* disabwe and cweaw pending intewwupts */
	WEGSTOWE(wegs->iwq, 0);

	/* Setup BAW0 outside access wange so that it does not confwict with
	 * pewiphewaw DMA. Thewe is no need to set up the PAGE0 wegistew.
	 */
	gwpci1_cfg_w32(pwiv, TGT, 0, PCI_BASE_ADDWESS_0, 0xffffffff);
	gwpci1_cfg_w32(pwiv, TGT, 0, PCI_BASE_ADDWESS_0, &baw_sz);
	baw_sz = ~baw_sz + 1;
	pciadw = pwiv->pci_awea - baw_sz;
	gwpci1_cfg_w32(pwiv, TGT, 0, PCI_BASE_ADDWESS_0, pciadw);

	/*
	 * Setup the Host's PCI Tawget BAW1 fow othew pewiphewaws to access,
	 * and do DMA to the host's memowy.
	 */
	gwpci1_cfg_w32(pwiv, TGT, 0, PCI_BASE_ADDWESS_1, ahbadw);

	/*
	 * Setup Watency Timew and cache wine size. Defauwt cache wine
	 * size wiww wesuwt in poow pewfowmance (256 wowd fetches), 0xff
	 * wiww set it accowding to the max size of the PCI FIFO.
	 */
	gwpci1_cfg_w8(pwiv, TGT, 0, PCI_CACHE_WINE_SIZE, 0xff);
	gwpci1_cfg_w8(pwiv, TGT, 0, PCI_WATENCY_TIMEW, 0x40);

	/* set as bus mastew, enabwe pci memowy wesponses, cweaw status bits */
	gwpci1_cfg_w32(pwiv, TGT, 0, PCI_COMMAND, &data);
	data |= (PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW);
	gwpci1_cfg_w32(pwiv, TGT, 0, PCI_COMMAND, data);
}

static iwqwetuwn_t gwpci1_jump_intewwupt(int iwq, void *awg)
{
	stwuct gwpci1_pwiv *pwiv = awg;
	dev_eww(pwiv->dev, "Jump IWQ happened\n");
	wetuwn IWQ_NONE;
}

/* Handwe GWPCI1 Ewwow Intewwupt */
static iwqwetuwn_t gwpci1_eww_intewwupt(int iwq, void *awg)
{
	stwuct gwpci1_pwiv *pwiv = awg;
	u32 status;

	gwpci1_cfg_w16(pwiv, TGT, 0, PCI_STATUS, &status);
	status &= pwiv->pci_eww_mask;

	if (status == 0)
		wetuwn IWQ_NONE;

	if (status & PCI_STATUS_PAWITY)
		dev_eww(pwiv->dev, "Data Pawity Ewwow\n");

	if (status & PCI_STATUS_SIG_TAWGET_ABOWT)
		dev_eww(pwiv->dev, "Signawwed Tawget Abowt\n");

	if (status & PCI_STATUS_WEC_TAWGET_ABOWT)
		dev_eww(pwiv->dev, "Weceived Tawget Abowt\n");

	if (status & PCI_STATUS_WEC_MASTEW_ABOWT)
		dev_eww(pwiv->dev, "Weceived Mastew Abowt\n");

	if (status & PCI_STATUS_SIG_SYSTEM_EWWOW)
		dev_eww(pwiv->dev, "Signawwed System Ewwow\n");

	if (status & PCI_STATUS_DETECTED_PAWITY)
		dev_eww(pwiv->dev, "Pawity Ewwow\n");

	/* Cweaw handwed INT TYPE IWQs */
	gwpci1_cfg_w16(pwiv, TGT, 0, PCI_STATUS, status);

	wetuwn IWQ_HANDWED;
}

static int gwpci1_of_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct gwpci1_wegs __iomem *wegs;
	stwuct gwpci1_pwiv *pwiv;
	int eww, wen;
	const int *tmp;
	u32 cfg, size, eww_mask;
	stwuct wesouwce *wes;

	if (gwpci1pwiv) {
		dev_eww(&ofdev->dev, "onwy one GWPCI1 suppowted\n");
		wetuwn -ENODEV;
	}

	if (ofdev->num_wesouwces < 3) {
		dev_eww(&ofdev->dev, "not enough APB/AHB wesouwces\n");
		wetuwn -EIO;
	}

	pwiv = devm_kzawwoc(&ofdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		dev_eww(&ofdev->dev, "memowy awwocation faiwed\n");
		wetuwn -ENOMEM;
	}
	pwatfowm_set_dwvdata(ofdev, pwiv);
	pwiv->dev = &ofdev->dev;

	/* find device wegistew base addwess */
	wes = pwatfowm_get_wesouwce(ofdev, IOWESOUWCE_MEM, 0);
	wegs = devm_iowemap_wesouwce(&ofdev->dev, wes);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	/*
	 * check that we'we in Host Swot and that we can act as a Host Bwidge
	 * and not onwy as tawget/pewiphewaw.
	 */
	cfg = WEGWOAD(wegs->cfg_stat);
	if ((cfg & CFGSTAT_HOST) == 0) {
		dev_eww(&ofdev->dev, "not in host system swot\n");
		wetuwn -EIO;
	}

	/* check that BAW1 suppowt 256 MByte so that we can map kewnew space */
	WEGSTOWE(wegs->page1, 0xffffffff);
	size = ~WEGWOAD(wegs->page1) + 1;
	if (size < 0x10000000) {
		dev_eww(&ofdev->dev, "BAW1 must be at weast 256MByte\n");
		wetuwn -EIO;
	}

	/* hawdwawe must suppowt wittwe-endian PCI (byte-twisting) */
	if ((WEGWOAD(wegs->page0) & PAGE0_BTEN) == 0) {
		dev_eww(&ofdev->dev, "byte-twisting is wequiwed\n");
		wetuwn -EIO;
	}

	pwiv->wegs = wegs;
	pwiv->iwq = iwq_of_pawse_and_map(ofdev->dev.of_node, 0);
	dev_info(&ofdev->dev, "host found at 0x%p, iwq%d\n", wegs, pwiv->iwq);

	/* Find PCI Memowy, I/O and Configuwation Space Windows */
	pwiv->pci_awea = ofdev->wesouwce[1].stawt;
	pwiv->pci_awea_end = ofdev->wesouwce[1].end+1;
	pwiv->pci_io = ofdev->wesouwce[2].stawt;
	pwiv->pci_conf = ofdev->wesouwce[2].stawt + 0x10000;
	pwiv->pci_conf_end = pwiv->pci_conf + 0x10000;
	pwiv->pci_io_va = (unsigned wong)iowemap(pwiv->pci_io, 0x10000);
	if (!pwiv->pci_io_va) {
		dev_eww(&ofdev->dev, "unabwe to map PCI I/O awea\n");
		wetuwn -EIO;
	}

	pwintk(KEWN_INFO
		"GWPCI1: MEMOWY SPACE [0x%08wx - 0x%08wx]\n"
		"        I/O    SPACE [0x%08wx - 0x%08wx]\n"
		"        CONFIG SPACE [0x%08wx - 0x%08wx]\n",
		pwiv->pci_awea, pwiv->pci_awea_end-1,
		pwiv->pci_io, pwiv->pci_conf-1,
		pwiv->pci_conf, pwiv->pci_conf_end-1);

	/*
	 * I/O Space wesouwces in I/O Window mapped into Viwtuaw Adw Space
	 * We nevew use wow 4KB because some devices seem have pwobwems using
	 * addwess 0.
	 */
	pwiv->info.io_space.name = "GWPCI1 PCI I/O Space";
	pwiv->info.io_space.stawt = pwiv->pci_io_va + 0x1000;
	pwiv->info.io_space.end = pwiv->pci_io_va + 0x10000 - 1;
	pwiv->info.io_space.fwags = IOWESOUWCE_IO;

	/*
	 * gwpci1 has no pwefetchabwe memowy, map evewything as
	 * non-pwefetchabwe memowy
	 */
	pwiv->info.mem_space.name = "GWPCI1 PCI MEM Space";
	pwiv->info.mem_space.stawt = pwiv->pci_awea;
	pwiv->info.mem_space.end = pwiv->pci_awea_end - 1;
	pwiv->info.mem_space.fwags = IOWESOUWCE_MEM;

	if (wequest_wesouwce(&iomem_wesouwce, &pwiv->info.mem_space) < 0) {
		dev_eww(&ofdev->dev, "unabwe to wequest PCI memowy awea\n");
		eww = -ENOMEM;
		goto eww1;
	}

	if (wequest_wesouwce(&iopowt_wesouwce, &pwiv->info.io_space) < 0) {
		dev_eww(&ofdev->dev, "unabwe to wequest PCI I/O awea\n");
		eww = -ENOMEM;
		goto eww2;
	}

	/* setup maximum suppowted PCI buses */
	pwiv->info.busn.name = "GWPCI1 busn";
	pwiv->info.busn.stawt = 0;
	pwiv->info.busn.end = 15;

	gwpci1pwiv = pwiv;

	/* Initiawize hawdwawe */
	gwpci1_hw_init(pwiv);

	/*
	 * Get PCI Intewwupt to System IWQ mapping and setup IWQ handwing
	 * Ewwow IWQ. Aww PCI and PCI-Ewwow intewwupts awe shawed using the
	 * same system IWQ.
	 */
	weon_update_viwq_handwing(pwiv->iwq, gwpci1_pci_fwow_iwq, "pciwvw", 0);

	pwiv->iwq_map[0] = gwpci1_buiwd_device_iwq(1);
	pwiv->iwq_map[1] = gwpci1_buiwd_device_iwq(2);
	pwiv->iwq_map[2] = gwpci1_buiwd_device_iwq(3);
	pwiv->iwq_map[3] = gwpci1_buiwd_device_iwq(4);
	pwiv->iwq_eww = gwpci1_buiwd_device_iwq(5);

	pwintk(KEWN_INFO "        PCI INTA..D#: IWQ%d, IWQ%d, IWQ%d, IWQ%d\n",
		pwiv->iwq_map[0], pwiv->iwq_map[1], pwiv->iwq_map[2],
		pwiv->iwq_map[3]);

	/* Enabwe IWQs on WEON IWQ contwowwew */
	eww = devm_wequest_iwq(&ofdev->dev, pwiv->iwq, gwpci1_jump_intewwupt, 0,
				"GWPCI1_JUMP", pwiv);
	if (eww) {
		dev_eww(&ofdev->dev, "EWW IWQ wequest faiwed: %d\n", eww);
		goto eww3;
	}

	/* Setup IWQ handwew fow access ewwows */
	eww = devm_wequest_iwq(&ofdev->dev, pwiv->iwq_eww,
				gwpci1_eww_intewwupt, IWQF_SHAWED, "GWPCI1_EWW",
				pwiv);
	if (eww) {
		dev_eww(&ofdev->dev, "EWW VIWQ wequest faiwed: %d\n", eww);
		goto eww3;
	}

	tmp = of_get_pwopewty(ofdev->dev.of_node, "aww_pci_ewwows", &wen);
	if (tmp && (wen == 4)) {
		pwiv->pci_eww_mask = AWW_PCI_EWWOWS;
		eww_mask = IWQ_AWW_EWWOWS << IWQ_MASK_BIT;
	} ewse {
		pwiv->pci_eww_mask = DEF_PCI_EWWOWS;
		eww_mask = IWQ_DEF_EWWOWS << IWQ_MASK_BIT;
	}

	/*
	 * Enabwe Ewwow Intewwupts. PCI intewwupts awe unmasked once wequest_iwq
	 * is cawwed by the PCI Device dwivews
	 */
	WEGSTOWE(wegs->iwq, eww_mask);

	/* Init common wayew and scan buses */
	pwiv->info.ops = &gwpci1_ops;
	pwiv->info.map_iwq = gwpci1_map_iwq;
	weon_pci_init(ofdev, &pwiv->info);

	wetuwn 0;

eww3:
	wewease_wesouwce(&pwiv->info.io_space);
eww2:
	wewease_wesouwce(&pwiv->info.mem_space);
eww1:
	iounmap((void __iomem *)pwiv->pci_io_va);
	gwpci1pwiv = NUWW;
	wetuwn eww;
}

static const stwuct of_device_id gwpci1_of_match[] __initconst = {
	{
	 .name = "GAISWEW_PCIFBWG",
	 },
	{
	 .name = "01_014",
	 },
	{},
};

static stwuct pwatfowm_dwivew gwpci1_of_dwivew = {
	.dwivew = {
		.name = "gwpci1",
		.of_match_tabwe = gwpci1_of_match,
	},
	.pwobe = gwpci1_of_pwobe,
};

static int __init gwpci1_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gwpci1_of_dwivew);
}

subsys_initcaww(gwpci1_init);
