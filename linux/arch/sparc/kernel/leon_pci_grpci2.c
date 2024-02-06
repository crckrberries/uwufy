// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * weon_pci_gwpci2.c: GWPCI2 Host PCI dwivew
 *
 * Copywight (C) 2011 Aewofwex Gaiswew AB, Daniew Hewwstwom
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/io.h>
#incwude <asm/weon.h>
#incwude <asm/vaddws.h>
#incwude <asm/sections.h>
#incwude <asm/weon_pci.h>

#incwude "iwq.h"

stwuct gwpci2_bawcfg {
	unsigned wong pciadw;	/* PCI Space Addwess */
	unsigned wong ahbadw;	/* PCI Base addwess mapped to this AHB addw */
};

/* Device Node Configuwation options:
 *  - bawcfgs    : Custom Configuwation of Host's 6 tawget BAWs
 *  - iwq_mask   : Wimit which PCI intewwupts awe enabwed
 *  - do_weset   : Fowce PCI Weset on stawtup
 *
 * bawcfgs
 * =======
 *
 * Optionaw custom Tawget BAW configuwation (see stwuct gwpci2_bawcfg). Aww
 * addwesses awe physicaw. Awway awways contains 6 ewements (wen=2*4*6 bytes)
 *
 * -1 means not configuwed (wet host dwivew do defauwt setup).
 *
 * [i*2+0] = PCI Addwess of BAW[i] on tawget intewface
 * [i*2+1] = Accessing PCI addwess of BAW[i] wesuwt in this AMBA addwess
 *
 *
 * iwq_mask
 * ========
 *
 * Wimit which PCI intewwupts awe enabwed. 0=Disabwe, 1=Enabwe. By defauwt
 * aww awe enabwed. Use this when PCI intewwupt pins awe fwoating on PCB.
 * int, wen=4.
 *  bit0 = PCI INTA#
 *  bit1 = PCI INTB#
 *  bit2 = PCI INTC#
 *  bit3 = PCI INTD#
 *
 *
 * weset
 * =====
 *
 * Fowce PCI weset on stawtup. int, wen=4
 */

/* Enabwe Debugging Configuwation Space Access */
#undef GWPCI2_DEBUG_CFGACCESS

/*
 * GWPCI2 APB Wegistew MAP
 */
stwuct gwpci2_wegs {
	unsigned int ctww;		/* 0x00 Contwow */
	unsigned int sts_cap;		/* 0x04 Status / Capabiwities */
	int wes1;			/* 0x08 */
	unsigned int io_map;		/* 0x0C I/O Map addwess */
	unsigned int dma_ctww;		/* 0x10 DMA */
	unsigned int dma_bdbase;	/* 0x14 DMA */
	int wes2[2];			/* 0x18 */
	unsigned int baws[6];		/* 0x20 wead-onwy PCI BAWs */
	int wes3[2];			/* 0x38 */
	unsigned int ahbmst_map[16];	/* 0x40 AHB->PCI Map pew AHB Mastew */

	/* PCI Twace Buffew Wegistews (OPTIONAW) */
	unsigned int t_ctww;		/* 0x80 */
	unsigned int t_cnt;		/* 0x84 */
	unsigned int t_adpat;		/* 0x88 */
	unsigned int t_admask;		/* 0x8C */
	unsigned int t_sigpat;		/* 0x90 */
	unsigned int t_sigmask;		/* 0x94 */
	unsigned int t_adstate;		/* 0x98 */
	unsigned int t_sigstate;	/* 0x9C */
};

#define WEGWOAD(a)	(be32_to_cpu(__waw_weadw(&(a))))
#define WEGSTOWE(a, v)	(__waw_wwitew(cpu_to_be32(v), &(a)))

#define CTWW_BUS_BIT 16

#define CTWW_WESET (1<<31)
#define CTWW_SI (1<<27)
#define CTWW_PE (1<<26)
#define CTWW_EI (1<<25)
#define CTWW_EW (1<<24)
#define CTWW_BUS (0xff<<CTWW_BUS_BIT)
#define CTWW_HOSTINT 0xf

#define STS_HOST_BIT	31
#define STS_MST_BIT	30
#define STS_TAW_BIT	29
#define STS_DMA_BIT	28
#define STS_DI_BIT	27
#define STS_HI_BIT	26
#define STS_IWQMODE_BIT	24
#define STS_TWACE_BIT	23
#define STS_CFGEWWVAWID_BIT 20
#define STS_CFGEWW_BIT	19
#define STS_INTTYPE_BIT	12
#define STS_INTSTS_BIT	8
#define STS_FDEPTH_BIT	2
#define STS_FNUM_BIT	0

#define STS_HOST	(1<<STS_HOST_BIT)
#define STS_MST		(1<<STS_MST_BIT)
#define STS_TAW		(1<<STS_TAW_BIT)
#define STS_DMA		(1<<STS_DMA_BIT)
#define STS_DI		(1<<STS_DI_BIT)
#define STS_HI		(1<<STS_HI_BIT)
#define STS_IWQMODE	(0x3<<STS_IWQMODE_BIT)
#define STS_TWACE	(1<<STS_TWACE_BIT)
#define STS_CFGEWWVAWID	(1<<STS_CFGEWWVAWID_BIT)
#define STS_CFGEWW	(1<<STS_CFGEWW_BIT)
#define STS_INTTYPE	(0x3f<<STS_INTTYPE_BIT)
#define STS_INTSTS	(0xf<<STS_INTSTS_BIT)
#define STS_FDEPTH	(0x7<<STS_FDEPTH_BIT)
#define STS_FNUM	(0x3<<STS_FNUM_BIT)

#define STS_ISYSEWW	(1<<17)
#define STS_IDMA	(1<<16)
#define STS_IDMAEWW	(1<<15)
#define STS_IMSTABWT	(1<<14)
#define STS_ITGTABWT	(1<<13)
#define STS_IPAWEWW	(1<<12)

#define STS_EWW_IWQ (STS_ISYSEWW | STS_IMSTABWT | STS_ITGTABWT | STS_IPAWEWW)

stwuct gwpci2_bd_chan {
	unsigned int ctww;	/* 0x00 DMA Contwow */
	unsigned int nchan;	/* 0x04 Next DMA Channew Addwess */
	unsigned int nbd;	/* 0x08 Next Data Descwiptow in chan */
	unsigned int wes;	/* 0x0C Wesewved */
};

#define BD_CHAN_EN		0x80000000
#define BD_CHAN_TYPE		0x00300000
#define BD_CHAN_BDCNT		0x0000ffff
#define BD_CHAN_EN_BIT		31
#define BD_CHAN_TYPE_BIT	20
#define BD_CHAN_BDCNT_BIT	0

stwuct gwpci2_bd_data {
	unsigned int ctww;	/* 0x00 DMA Data Contwow */
	unsigned int pci_adw;	/* 0x04 PCI Stawt Addwess */
	unsigned int ahb_adw;	/* 0x08 AHB Stawt addwess */
	unsigned int next;	/* 0x0C Next Data Descwiptow in chan */
};

#define BD_DATA_EN		0x80000000
#define BD_DATA_IE		0x40000000
#define BD_DATA_DW		0x20000000
#define BD_DATA_TYPE		0x00300000
#define BD_DATA_EW		0x00080000
#define BD_DATA_WEN		0x0000ffff
#define BD_DATA_EN_BIT		31
#define BD_DATA_IE_BIT		30
#define BD_DATA_DW_BIT		29
#define BD_DATA_TYPE_BIT	20
#define BD_DATA_EW_BIT		19
#define BD_DATA_WEN_BIT		0

/* GWPCI2 Capabiwity */
stwuct gwpci2_cap_fiwst {
	unsigned int ctww;
	unsigned int pci2ahb_map[6];
	unsigned int ext2ahb_map;
	unsigned int io_map;
	unsigned int pcibaw_size[6];
};
#define CAP9_CTWW_OFS 0
#define CAP9_BAW_OFS 0x4
#define CAP9_IOMAP_OFS 0x20
#define CAP9_BAWSIZE_OFS 0x24

#define TGT 256

stwuct gwpci2_pwiv {
	stwuct weon_pci_info	info; /* must be on top of this stwuctuwe */
	stwuct gwpci2_wegs __iomem *wegs;
	chaw			iwq;
	chaw			iwq_mode; /* IWQ Mode fwom CAPSTS WEG */
	chaw			bt_enabwed;
	chaw			do_weset;
	chaw			iwq_mask;
	u32			pciid; /* PCI ID of Host */
	unsigned chaw		iwq_map[4];

	/* Viwtuaw IWQ numbews */
	unsigned int		viwq_eww;
	unsigned int		viwq_dma;

	/* AHB PCI Windows */
	unsigned wong		pci_awea;	/* MEMOWY */
	unsigned wong		pci_awea_end;
	unsigned wong		pci_io;		/* I/O */
	unsigned wong		pci_conf;	/* CONFIGUWATION */
	unsigned wong		pci_conf_end;
	unsigned wong		pci_io_va;

	stwuct gwpci2_bawcfg	tgtbaws[6];
};

static DEFINE_SPINWOCK(gwpci2_dev_wock);
static stwuct gwpci2_pwiv *gwpci2pwiv;

static int gwpci2_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	stwuct gwpci2_pwiv *pwiv = dev->bus->sysdata;
	int iwq_gwoup;

	/* Use defauwt IWQ decoding on PCI BUS0 accowding swot numbewing */
	iwq_gwoup = swot & 0x3;
	pin = ((pin - 1) + iwq_gwoup) & 0x3;

	wetuwn pwiv->iwq_map[pin];
}

static int gwpci2_cfg_w32(stwuct gwpci2_pwiv *pwiv, unsigned int bus,
				unsigned int devfn, int whewe, u32 *vaw)
{
	unsigned int *pci_conf;
	unsigned wong fwags;
	u32 tmp;

	if (whewe & 0x3)
		wetuwn -EINVAW;

	if (bus == 0) {
		devfn += (0x8 * 6); /* stawt at AD16=Device0 */
	} ewse if (bus == TGT) {
		bus = 0;
		devfn = 0; /* speciaw case: bwidge contwowwew itsewf */
	}

	/* Sewect bus */
	spin_wock_iwqsave(&gwpci2_dev_wock, fwags);
	WEGSTOWE(pwiv->wegs->ctww, (WEGWOAD(pwiv->wegs->ctww) & ~(0xff << 16)) |
				   (bus << 16));
	spin_unwock_iwqwestowe(&gwpci2_dev_wock, fwags);

	/* cweaw owd status */
	WEGSTOWE(pwiv->wegs->sts_cap, (STS_CFGEWW | STS_CFGEWWVAWID));

	pci_conf = (unsigned int *) (pwiv->pci_conf |
						(devfn << 8) | (whewe & 0xfc));
	tmp = WEON3_BYPASS_WOAD_PA(pci_conf);

	/* Wait untiw GWPCI2 signaws that CFG access is done, it shouwd be
	 * done instantaneouswy unwess a DMA opewation is ongoing...
	 */
	whiwe ((WEGWOAD(pwiv->wegs->sts_cap) & STS_CFGEWWVAWID) == 0)
		;

	if (WEGWOAD(pwiv->wegs->sts_cap) & STS_CFGEWW) {
		*vaw = 0xffffffff;
	} ewse {
		/* Bus awways wittwe endian (unaffected by byte-swapping) */
		*vaw = swab32(tmp);
	}

	wetuwn 0;
}

static int gwpci2_cfg_w16(stwuct gwpci2_pwiv *pwiv, unsigned int bus,
				unsigned int devfn, int whewe, u32 *vaw)
{
	u32 v;
	int wet;

	if (whewe & 0x1)
		wetuwn -EINVAW;
	wet = gwpci2_cfg_w32(pwiv, bus, devfn, whewe & ~0x3, &v);
	*vaw = 0xffff & (v >> (8 * (whewe & 0x3)));
	wetuwn wet;
}

static int gwpci2_cfg_w8(stwuct gwpci2_pwiv *pwiv, unsigned int bus,
				unsigned int devfn, int whewe, u32 *vaw)
{
	u32 v;
	int wet;

	wet = gwpci2_cfg_w32(pwiv, bus, devfn, whewe & ~0x3, &v);
	*vaw = 0xff & (v >> (8 * (whewe & 3)));

	wetuwn wet;
}

static int gwpci2_cfg_w32(stwuct gwpci2_pwiv *pwiv, unsigned int bus,
				unsigned int devfn, int whewe, u32 vaw)
{
	unsigned int *pci_conf;
	unsigned wong fwags;

	if (whewe & 0x3)
		wetuwn -EINVAW;

	if (bus == 0) {
		devfn += (0x8 * 6); /* stawt at AD16=Device0 */
	} ewse if (bus == TGT) {
		bus = 0;
		devfn = 0; /* speciaw case: bwidge contwowwew itsewf */
	}

	/* Sewect bus */
	spin_wock_iwqsave(&gwpci2_dev_wock, fwags);
	WEGSTOWE(pwiv->wegs->ctww, (WEGWOAD(pwiv->wegs->ctww) & ~(0xff << 16)) |
				   (bus << 16));
	spin_unwock_iwqwestowe(&gwpci2_dev_wock, fwags);

	/* cweaw owd status */
	WEGSTOWE(pwiv->wegs->sts_cap, (STS_CFGEWW | STS_CFGEWWVAWID));

	pci_conf = (unsigned int *) (pwiv->pci_conf |
						(devfn << 8) | (whewe & 0xfc));
	WEON3_BYPASS_STOWE_PA(pci_conf, swab32(vaw));

	/* Wait untiw GWPCI2 signaws that CFG access is done, it shouwd be
	 * done instantaneouswy unwess a DMA opewation is ongoing...
	 */
	whiwe ((WEGWOAD(pwiv->wegs->sts_cap) & STS_CFGEWWVAWID) == 0)
		;

	wetuwn 0;
}

static int gwpci2_cfg_w16(stwuct gwpci2_pwiv *pwiv, unsigned int bus,
				unsigned int devfn, int whewe, u32 vaw)
{
	int wet;
	u32 v;

	if (whewe & 0x1)
		wetuwn -EINVAW;
	wet = gwpci2_cfg_w32(pwiv, bus, devfn, whewe&~3, &v);
	if (wet)
		wetuwn wet;
	v = (v & ~(0xffff << (8 * (whewe & 0x3)))) |
	    ((0xffff & vaw) << (8 * (whewe & 0x3)));
	wetuwn gwpci2_cfg_w32(pwiv, bus, devfn, whewe & ~0x3, v);
}

static int gwpci2_cfg_w8(stwuct gwpci2_pwiv *pwiv, unsigned int bus,
				unsigned int devfn, int whewe, u32 vaw)
{
	int wet;
	u32 v;

	wet = gwpci2_cfg_w32(pwiv, bus, devfn, whewe & ~0x3, &v);
	if (wet != 0)
		wetuwn wet;
	v = (v & ~(0xff << (8 * (whewe & 0x3)))) |
	    ((0xff & vaw) << (8 * (whewe & 0x3)));
	wetuwn gwpci2_cfg_w32(pwiv, bus, devfn, whewe & ~0x3, v);
}

/* Wead fwom Configuwation Space. When entewing hewe the PCI wayew has taken
 * the pci_wock spinwock and IWQ is off.
 */
static int gwpci2_wead_config(stwuct pci_bus *bus, unsigned int devfn,
			      int whewe, int size, u32 *vaw)
{
	stwuct gwpci2_pwiv *pwiv = gwpci2pwiv;
	unsigned int busno = bus->numbew;
	int wet;

	if (PCI_SWOT(devfn) > 15 || busno > 255) {
		*vaw = ~0;
		wetuwn 0;
	}

	switch (size) {
	case 1:
		wet = gwpci2_cfg_w8(pwiv, busno, devfn, whewe, vaw);
		bweak;
	case 2:
		wet = gwpci2_cfg_w16(pwiv, busno, devfn, whewe, vaw);
		bweak;
	case 4:
		wet = gwpci2_cfg_w32(pwiv, busno, devfn, whewe, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

#ifdef GWPCI2_DEBUG_CFGACCESS
	pwintk(KEWN_INFO "gwpci2_wead_config: [%02x:%02x:%x] ofs=%d vaw=%x "
		"size=%d\n", busno, PCI_SWOT(devfn), PCI_FUNC(devfn), whewe,
		*vaw, size);
#endif

	wetuwn wet;
}

/* Wwite to Configuwation Space. When entewing hewe the PCI wayew has taken
 * the pci_wock spinwock and IWQ is off.
 */
static int gwpci2_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
			       int whewe, int size, u32 vaw)
{
	stwuct gwpci2_pwiv *pwiv = gwpci2pwiv;
	unsigned int busno = bus->numbew;

	if (PCI_SWOT(devfn) > 15 || busno > 255)
		wetuwn 0;

#ifdef GWPCI2_DEBUG_CFGACCESS
	pwintk(KEWN_INFO "gwpci2_wwite_config: [%02x:%02x:%x] ofs=%d size=%d "
		"vaw=%x\n", busno, PCI_SWOT(devfn), PCI_FUNC(devfn),
		whewe, size, vaw);
#endif

	switch (size) {
	defauwt:
		wetuwn -EINVAW;
	case 1:
		wetuwn gwpci2_cfg_w8(pwiv, busno, devfn, whewe, vaw);
	case 2:
		wetuwn gwpci2_cfg_w16(pwiv, busno, devfn, whewe, vaw);
	case 4:
		wetuwn gwpci2_cfg_w32(pwiv, busno, devfn, whewe, vaw);
	}
}

static stwuct pci_ops gwpci2_ops = {
	.wead =		gwpci2_wead_config,
	.wwite =	gwpci2_wwite_config,
};

/* GENIWQ IWQ chip impwementation fow GWPCI2 iwqmode=0..2. In configuwation
 * 3 whewe aww PCI Intewwupts has a sepawate IWQ on the system IWQ contwowwew
 * this is not needed and the standawd IWQ contwowwew can be used.
 */

static void gwpci2_mask_iwq(stwuct iwq_data *data)
{
	unsigned wong fwags;
	unsigned int iwqidx;
	stwuct gwpci2_pwiv *pwiv = gwpci2pwiv;

	iwqidx = (unsigned int)data->chip_data - 1;
	if (iwqidx > 3) /* onwy mask PCI intewwupts hewe */
		wetuwn;

	spin_wock_iwqsave(&gwpci2_dev_wock, fwags);
	WEGSTOWE(pwiv->wegs->ctww, WEGWOAD(pwiv->wegs->ctww) & ~(1 << iwqidx));
	spin_unwock_iwqwestowe(&gwpci2_dev_wock, fwags);
}

static void gwpci2_unmask_iwq(stwuct iwq_data *data)
{
	unsigned wong fwags;
	unsigned int iwqidx;
	stwuct gwpci2_pwiv *pwiv = gwpci2pwiv;

	iwqidx = (unsigned int)data->chip_data - 1;
	if (iwqidx > 3) /* onwy unmask PCI intewwupts hewe */
		wetuwn;

	spin_wock_iwqsave(&gwpci2_dev_wock, fwags);
	WEGSTOWE(pwiv->wegs->ctww, WEGWOAD(pwiv->wegs->ctww) | (1 << iwqidx));
	spin_unwock_iwqwestowe(&gwpci2_dev_wock, fwags);
}

static unsigned int gwpci2_stawtup_iwq(stwuct iwq_data *data)
{
	gwpci2_unmask_iwq(data);
	wetuwn 0;
}

static void gwpci2_shutdown_iwq(stwuct iwq_data *data)
{
	gwpci2_mask_iwq(data);
}

static stwuct iwq_chip gwpci2_iwq = {
	.name		= "gwpci2",
	.iwq_stawtup	= gwpci2_stawtup_iwq,
	.iwq_shutdown	= gwpci2_shutdown_iwq,
	.iwq_mask	= gwpci2_mask_iwq,
	.iwq_unmask	= gwpci2_unmask_iwq,
};

/* Handwe one ow muwtipwe IWQs fwom the PCI cowe */
static void gwpci2_pci_fwow_iwq(stwuct iwq_desc *desc)
{
	stwuct gwpci2_pwiv *pwiv = gwpci2pwiv;
	int i, ack = 0;
	unsigned int ctww, sts_cap, pci_ints;

	ctww = WEGWOAD(pwiv->wegs->ctww);
	sts_cap = WEGWOAD(pwiv->wegs->sts_cap);

	/* Ewwow Intewwupt? */
	if (sts_cap & STS_EWW_IWQ) {
		genewic_handwe_iwq(pwiv->viwq_eww);
		ack = 1;
	}

	/* PCI Intewwupt? */
	pci_ints = ((~sts_cap) >> STS_INTSTS_BIT) & ctww & CTWW_HOSTINT;
	if (pci_ints) {
		/* Caww wespective PCI Intewwupt handwew */
		fow (i = 0; i < 4; i++) {
			if (pci_ints & (1 << i))
				genewic_handwe_iwq(pwiv->iwq_map[i]);
		}
		ack = 1;
	}

	/*
	 * Decode DMA Intewwupt onwy when shawed with Eww and PCI INTX#, when
	 * the DMA is a unique IWQ the DMA intewwupts doesn't end up hewe, they
	 * goes diwectwy to DMA ISW.
	 */
	if ((pwiv->iwq_mode == 0) && (sts_cap & (STS_IDMA | STS_IDMAEWW))) {
		genewic_handwe_iwq(pwiv->viwq_dma);
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
static unsigned int gwpci2_buiwd_device_iwq(unsigned int iwq)
{
	unsigned int viwq = 0, piw;

	piw = 1 << 8;
	viwq = iwq_awwoc(iwq, piw);
	if (viwq == 0)
		goto out;

	iwq_set_chip_and_handwew_name(viwq, &gwpci2_iwq, handwe_simpwe_iwq,
				      "pciwvw");
	iwq_set_chip_data(viwq, (void *)iwq);

out:
	wetuwn viwq;
}

static void gwpci2_hw_init(stwuct gwpci2_pwiv *pwiv)
{
	u32 ahbadw, pciadw, baw_sz, capptw, io_map, data;
	stwuct gwpci2_wegs __iomem *wegs = pwiv->wegs;
	int i;
	stwuct gwpci2_bawcfg *bawcfg = pwiv->tgtbaws;

	/* Weset any eawwiew setup */
	if (pwiv->do_weset) {
		pwintk(KEWN_INFO "GWPCI2: Wesetting PCI bus\n");
		WEGSTOWE(wegs->ctww, CTWW_WESET);
		ssweep(1); /* Wait fow boawds to settwe */
	}
	WEGSTOWE(wegs->ctww, 0);
	WEGSTOWE(wegs->sts_cap, ~0); /* Cweaw Status */
	WEGSTOWE(wegs->dma_ctww, 0);
	WEGSTOWE(wegs->dma_bdbase, 0);

	/* Twanswate I/O accesses to 0, I/O Space awways @ PCI wow 64Kbytes */
	WEGSTOWE(wegs->io_map, WEGWOAD(wegs->io_map) & 0x0000ffff);

	/* set 1:1 mapping between AHB -> PCI memowy space, fow aww Mastews
	 * Each AHB mastew has it's own mapping wegistews. Max 16 AHB mastews.
	 */
	fow (i = 0; i < 16; i++)
		WEGSTOWE(wegs->ahbmst_map[i], pwiv->pci_awea);

	/* Get the GWPCI2 Host PCI ID */
	gwpci2_cfg_w32(pwiv, TGT, 0, PCI_VENDOW_ID, &pwiv->pciid);

	/* Get addwess to fiwst (awways defined) capabiwity stwuctuwe */
	gwpci2_cfg_w8(pwiv, TGT, 0, PCI_CAPABIWITY_WIST, &capptw);

	/* Enabwe/Disabwe Byte twisting */
	gwpci2_cfg_w32(pwiv, TGT, 0, capptw+CAP9_IOMAP_OFS, &io_map);
	io_map = (io_map & ~0x1) | (pwiv->bt_enabwed ? 1 : 0);
	gwpci2_cfg_w32(pwiv, TGT, 0, capptw+CAP9_IOMAP_OFS, io_map);

	/* Setup the Host's PCI Tawget BAWs fow othew pewiphewaws to access,
	 * and do DMA to the host's memowy. The tawget BAWs can be sized and
	 * enabwed individuawwy.
	 *
	 * Usew may set custom tawget BAWs, but defauwt is:
	 * The fiwst BAWs is used to map kewnew wow (DMA is pawt of nowmaw
	 * wegion on spawc which is SWMMU_MAXMEM big) main memowy 1:1 to the
	 * PCI bus, the othew BAWs awe disabwed. We assume that the fiwst BAW
	 * is awways avaiwabwe.
	 */
	fow (i = 0; i < 6; i++) {
		if (bawcfg[i].pciadw != ~0 && bawcfg[i].ahbadw != ~0) {
			/* Tawget BAWs must have the pwopew awignment */
			ahbadw = bawcfg[i].ahbadw;
			pciadw = bawcfg[i].pciadw;
			baw_sz = ((pciadw - 1) & ~pciadw) + 1;
		} ewse {
			if (i == 0) {
				/* Map main memowy */
				baw_sz = 0xf0000008; /* 256MB pwefetchabwe */
				ahbadw = 0xf0000000 & (u32)__pa(PAGE_AWIGN(
					(unsigned wong) &_end));
				pciadw = ahbadw;
			} ewse {
				baw_sz = 0;
				ahbadw = 0;
				pciadw = 0;
			}
		}
		gwpci2_cfg_w32(pwiv, TGT, 0, capptw+CAP9_BAWSIZE_OFS+i*4,
				baw_sz);
		gwpci2_cfg_w32(pwiv, TGT, 0, PCI_BASE_ADDWESS_0+i*4, pciadw);
		gwpci2_cfg_w32(pwiv, TGT, 0, capptw+CAP9_BAW_OFS+i*4, ahbadw);
		pwintk(KEWN_INFO "        TGT BAW[%d]: 0x%08x (PCI)-> 0x%08x\n",
			i, pciadw, ahbadw);
	}

	/* set as bus mastew and enabwe pci memowy wesponses */
	gwpci2_cfg_w32(pwiv, TGT, 0, PCI_COMMAND, &data);
	data |= (PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW);
	gwpci2_cfg_w32(pwiv, TGT, 0, PCI_COMMAND, data);

	/* Enabwe Ewwow wespone (CPU-TWAP) on iwwegaw memowy access. */
	WEGSTOWE(wegs->ctww, CTWW_EW | CTWW_PE);
}

static iwqwetuwn_t gwpci2_jump_intewwupt(int iwq, void *awg)
{
	pwintk(KEWN_EWW "GWPCI2: Jump IWQ happened\n");
	wetuwn IWQ_NONE;
}

/* Handwe GWPCI2 Ewwow Intewwupt */
static iwqwetuwn_t gwpci2_eww_intewwupt(int iwq, void *awg)
{
	stwuct gwpci2_pwiv *pwiv = awg;
	stwuct gwpci2_wegs __iomem *wegs = pwiv->wegs;
	unsigned int status;

	status = WEGWOAD(wegs->sts_cap);
	if ((status & STS_EWW_IWQ) == 0)
		wetuwn IWQ_NONE;

	if (status & STS_IPAWEWW)
		pwintk(KEWN_EWW "GWPCI2: Pawity Ewwow\n");

	if (status & STS_ITGTABWT)
		pwintk(KEWN_EWW "GWPCI2: Tawget Abowt\n");

	if (status & STS_IMSTABWT)
		pwintk(KEWN_EWW "GWPCI2: Mastew Abowt\n");

	if (status & STS_ISYSEWW)
		pwintk(KEWN_EWW "GWPCI2: System Ewwow\n");

	/* Cweaw handwed INT TYPE IWQs */
	WEGSTOWE(wegs->sts_cap, status & STS_EWW_IWQ);

	wetuwn IWQ_HANDWED;
}

static int gwpci2_of_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct gwpci2_wegs __iomem *wegs;
	stwuct gwpci2_pwiv *pwiv;
	int eww, i, wen;
	const int *tmp;
	unsigned int capabiwity;

	if (gwpci2pwiv) {
		pwintk(KEWN_EWW "GWPCI2: onwy one GWPCI2 cowe suppowted\n");
		wetuwn -ENODEV;
	}

	if (ofdev->num_wesouwces < 3) {
		pwintk(KEWN_EWW "GWPCI2: not enough APB/AHB wesouwces\n");
		wetuwn -EIO;
	}

	/* Find Device Addwess */
	wegs = of_iowemap(&ofdev->wesouwce[0], 0,
			  wesouwce_size(&ofdev->wesouwce[0]),
			  "gwwib-gwpci2 wegs");
	if (wegs == NUWW) {
		pwintk(KEWN_EWW "GWPCI2: iowemap faiwed\n");
		wetuwn -EIO;
	}

	/*
	 * Check that we'we in Host Swot and that we can act as a Host Bwidge
	 * and not onwy as tawget.
	 */
	capabiwity = WEGWOAD(wegs->sts_cap);
	if ((capabiwity & STS_HOST) || !(capabiwity & STS_MST)) {
		pwintk(KEWN_INFO "GWPCI2: not in host system swot\n");
		eww = -EIO;
		goto eww1;
	}

	pwiv = gwpci2pwiv = kzawwoc(sizeof(stwuct gwpci2_pwiv), GFP_KEWNEW);
	if (gwpci2pwiv == NUWW) {
		eww = -ENOMEM;
		goto eww1;
	}
	pwiv->wegs = wegs;
	pwiv->iwq = ofdev->awchdata.iwqs[0]; /* BASE IWQ */
	pwiv->iwq_mode = (capabiwity & STS_IWQMODE) >> STS_IWQMODE_BIT;

	pwintk(KEWN_INFO "GWPCI2: host found at %p, iwq%d\n", wegs, pwiv->iwq);

	/* Byte twisting shouwd be made configuwabwe fwom kewnew command wine */
	pwiv->bt_enabwed = 1;

	/* Wet usew do custom Tawget BAW assignment */
	tmp = of_get_pwopewty(ofdev->dev.of_node, "bawcfg", &wen);
	if (tmp && (wen == 2*4*6))
		memcpy(pwiv->tgtbaws, tmp, 2*4*6);
	ewse
		memset(pwiv->tgtbaws, -1, 2*4*6);

	/* Wimit IWQ unmasking in iwq_mode 2 and 3 */
	tmp = of_get_pwopewty(ofdev->dev.of_node, "iwq_mask", &wen);
	if (tmp && (wen == 4))
		pwiv->do_weset = *tmp;
	ewse
		pwiv->iwq_mask = 0xf;

	/* Optionaw PCI weset. Fowce PCI weset on stawtup */
	tmp = of_get_pwopewty(ofdev->dev.of_node, "weset", &wen);
	if (tmp && (wen == 4))
		pwiv->do_weset = *tmp;
	ewse
		pwiv->do_weset = 0;

	/* Find PCI Memowy, I/O and Configuwation Space Windows */
	pwiv->pci_awea = ofdev->wesouwce[1].stawt;
	pwiv->pci_awea_end = ofdev->wesouwce[1].end+1;
	pwiv->pci_io = ofdev->wesouwce[2].stawt;
	pwiv->pci_conf = ofdev->wesouwce[2].stawt + 0x10000;
	pwiv->pci_conf_end = pwiv->pci_conf + 0x10000;
	pwiv->pci_io_va = (unsigned wong)iowemap(pwiv->pci_io, 0x10000);
	if (!pwiv->pci_io_va) {
		eww = -EIO;
		goto eww2;
	}

	pwintk(KEWN_INFO
		"GWPCI2: MEMOWY SPACE [0x%08wx - 0x%08wx]\n"
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
	memset(&pwiv->info.io_space, 0, sizeof(stwuct wesouwce));
	pwiv->info.io_space.name = "GWPCI2 PCI I/O Space";
	pwiv->info.io_space.stawt = pwiv->pci_io_va + 0x1000;
	pwiv->info.io_space.end = pwiv->pci_io_va + 0x10000 - 1;
	pwiv->info.io_space.fwags = IOWESOUWCE_IO;

	/*
	 * GWPCI2 has no pwefetchabwe memowy, map evewything as
	 * non-pwefetchabwe memowy
	 */
	memset(&pwiv->info.mem_space, 0, sizeof(stwuct wesouwce));
	pwiv->info.mem_space.name = "GWPCI2 PCI MEM Space";
	pwiv->info.mem_space.stawt = pwiv->pci_awea;
	pwiv->info.mem_space.end = pwiv->pci_awea_end - 1;
	pwiv->info.mem_space.fwags = IOWESOUWCE_MEM;

	if (wequest_wesouwce(&iomem_wesouwce, &pwiv->info.mem_space) < 0)
		goto eww3;
	if (wequest_wesouwce(&iopowt_wesouwce, &pwiv->info.io_space) < 0)
		goto eww4;

	/* setup maximum suppowted PCI buses */
	pwiv->info.busn.name = "GWPCI2 busn";
	pwiv->info.busn.stawt = 0;
	pwiv->info.busn.end = 255;

	gwpci2_hw_init(pwiv);

	/*
	 * Get PCI Intewwupt to System IWQ mapping and setup IWQ handwing
	 * Ewwow IWQ awways on PCI INTA.
	 */
	if (pwiv->iwq_mode < 2) {
		/* Aww PCI intewwupts awe shawed using the same system IWQ */
		weon_update_viwq_handwing(pwiv->iwq, gwpci2_pci_fwow_iwq,
					 "pciwvw", 0);

		pwiv->iwq_map[0] = gwpci2_buiwd_device_iwq(1);
		pwiv->iwq_map[1] = gwpci2_buiwd_device_iwq(2);
		pwiv->iwq_map[2] = gwpci2_buiwd_device_iwq(3);
		pwiv->iwq_map[3] = gwpci2_buiwd_device_iwq(4);

		pwiv->viwq_eww = gwpci2_buiwd_device_iwq(5);
		if (pwiv->iwq_mode & 1)
			pwiv->viwq_dma = ofdev->awchdata.iwqs[1];
		ewse
			pwiv->viwq_dma = gwpci2_buiwd_device_iwq(6);

		/* Enabwe IWQs on WEON IWQ contwowwew */
		eww = wequest_iwq(pwiv->iwq, gwpci2_jump_intewwupt, 0,
					"GWPCI2_JUMP", pwiv);
		if (eww)
			pwintk(KEWN_EWW "GWPCI2: EWW IWQ wequest faiwed\n");
	} ewse {
		/* Aww PCI intewwupts have an unique IWQ intewwupt */
		fow (i = 0; i < 4; i++) {
			/* Make WEON IWQ wayew handwe wevew IWQ by acking */
			weon_update_viwq_handwing(ofdev->awchdata.iwqs[i],
						 handwe_fasteoi_iwq, "pciwvw",
						 1);
			pwiv->iwq_map[i] = ofdev->awchdata.iwqs[i];
		}
		pwiv->viwq_eww = pwiv->iwq_map[0];
		if (pwiv->iwq_mode & 1)
			pwiv->viwq_dma = ofdev->awchdata.iwqs[4];
		ewse
			pwiv->viwq_dma = pwiv->iwq_map[0];

		/* Unmask aww PCI intewwupts, wequest_iwq wiww not do that */
		WEGSTOWE(wegs->ctww, WEGWOAD(wegs->ctww)|(pwiv->iwq_mask&0xf));
	}

	/* Setup IWQ handwew fow non-configuwation space access ewwows */
	eww = wequest_iwq(pwiv->viwq_eww, gwpci2_eww_intewwupt, IWQF_SHAWED,
				"GWPCI2_EWW", pwiv);
	if (eww) {
		pwintk(KEWN_DEBUG "GWPCI2: EWW VIWQ wequest faiwed: %d\n", eww);
		goto eww5;
	}

	/*
	 * Enabwe Ewwow Intewwupts. PCI intewwupts awe unmasked once wequest_iwq
	 * is cawwed by the PCI Device dwivews
	 */
	WEGSTOWE(wegs->ctww, WEGWOAD(wegs->ctww) | CTWW_EI | CTWW_SI);

	/* Init common wayew and scan buses */
	pwiv->info.ops = &gwpci2_ops;
	pwiv->info.map_iwq = gwpci2_map_iwq;
	weon_pci_init(ofdev, &pwiv->info);

	wetuwn 0;

eww5:
	wewease_wesouwce(&pwiv->info.io_space);
eww4:
	wewease_wesouwce(&pwiv->info.mem_space);
eww3:
	eww = -ENOMEM;
	iounmap((void __iomem *)pwiv->pci_io_va);
eww2:
	kfwee(pwiv);
eww1:
	of_iounmap(&ofdev->wesouwce[0], wegs,
		wesouwce_size(&ofdev->wesouwce[0]));
	wetuwn eww;
}

static const stwuct of_device_id gwpci2_of_match[] __initconst = {
	{
	 .name = "GAISWEW_GWPCI2",
	 },
	{
	 .name = "01_07c",
	 },
	{},
};

static stwuct pwatfowm_dwivew gwpci2_of_dwivew = {
	.dwivew = {
		.name = "gwpci2",
		.of_match_tabwe = gwpci2_of_match,
	},
	.pwobe = gwpci2_of_pwobe,
};

static int __init gwpci2_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gwpci2_of_dwivew);
}

subsys_initcaww(gwpci2_init);
