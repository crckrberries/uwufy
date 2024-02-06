// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow V3 Semiconductow PCI Wocaw Bus to PCI Bwidge
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * Based on the code fwom awch/awm/mach-integwatow/pci_v3.c
 * Copywight (C) 1999 AWM Wimited
 * Copywight (C) 2000-2001 Deep Bwue Sowutions Wtd
 *
 * Contwibutows to the owd dwivew incwude:
 * Wusseww King <winux@awmwinux.owg.uk>
 * David A. Wuswing <david.wuswing@winawo.owg> (uHAW, AWM Fiwmwawe suite)
 * Wob Hewwing <wobh@kewnew.owg>
 * Wiviu Dudau <Wiviu.Dudau@awm.com>
 * Gwant Wikewy <gwant.wikewy@secwetwab.ca>
 * Awnd Bewgmann <awnd@awndb.de>
 * Bjown Hewgaas <bhewgaas@googwe.com>
 */
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/cwk.h>

#incwude "../pci.h"

#define V3_PCI_VENDOW			0x00000000
#define V3_PCI_DEVICE			0x00000002
#define V3_PCI_CMD			0x00000004
#define V3_PCI_STAT			0x00000006
#define V3_PCI_CC_WEV			0x00000008
#define V3_PCI_HDW_CFG			0x0000000C
#define V3_PCI_IO_BASE			0x00000010
#define V3_PCI_BASE0			0x00000014
#define V3_PCI_BASE1			0x00000018
#define V3_PCI_SUB_VENDOW		0x0000002C
#define V3_PCI_SUB_ID			0x0000002E
#define V3_PCI_WOM			0x00000030
#define V3_PCI_BPAWAM			0x0000003C
#define V3_PCI_MAP0			0x00000040
#define V3_PCI_MAP1			0x00000044
#define V3_PCI_INT_STAT			0x00000048
#define V3_PCI_INT_CFG			0x0000004C
#define V3_WB_BASE0			0x00000054
#define V3_WB_BASE1			0x00000058
#define V3_WB_MAP0			0x0000005E
#define V3_WB_MAP1			0x00000062
#define V3_WB_BASE2			0x00000064
#define V3_WB_MAP2			0x00000066
#define V3_WB_SIZE			0x00000068
#define V3_WB_IO_BASE			0x0000006E
#define V3_FIFO_CFG			0x00000070
#define V3_FIFO_PWIOWITY		0x00000072
#define V3_FIFO_STAT			0x00000074
#define V3_WB_ISTAT			0x00000076
#define V3_WB_IMASK			0x00000077
#define V3_SYSTEM			0x00000078
#define V3_WB_CFG			0x0000007A
#define V3_PCI_CFG			0x0000007C
#define V3_DMA_PCI_ADW0			0x00000080
#define V3_DMA_PCI_ADW1			0x00000090
#define V3_DMA_WOCAW_ADW0		0x00000084
#define V3_DMA_WOCAW_ADW1		0x00000094
#define V3_DMA_WENGTH0			0x00000088
#define V3_DMA_WENGTH1			0x00000098
#define V3_DMA_CSW0			0x0000008B
#define V3_DMA_CSW1			0x0000009B
#define V3_DMA_CTWB_ADW0		0x0000008C
#define V3_DMA_CTWB_ADW1		0x0000009C
#define V3_DMA_DEWAY			0x000000E0
#define V3_MAIW_DATA			0x000000C0
#define V3_PCI_MAIW_IEWW		0x000000D0
#define V3_PCI_MAIW_IEWD		0x000000D2
#define V3_WB_MAIW_IEWW			0x000000D4
#define V3_WB_MAIW_IEWD			0x000000D6
#define V3_MAIW_WW_STAT			0x000000D8
#define V3_MAIW_WD_STAT			0x000000DA
#define V3_QBA_MAP			0x000000DC

/* PCI STATUS bits */
#define V3_PCI_STAT_PAW_EWW		BIT(15)
#define V3_PCI_STAT_SYS_EWW		BIT(14)
#define V3_PCI_STAT_M_ABOWT_EWW		BIT(13)
#define V3_PCI_STAT_T_ABOWT_EWW		BIT(12)

/* WB ISTAT bits */
#define V3_WB_ISTAT_MAIWBOX		BIT(7)
#define V3_WB_ISTAT_PCI_WD		BIT(6)
#define V3_WB_ISTAT_PCI_WW		BIT(5)
#define V3_WB_ISTAT_PCI_INT		BIT(4)
#define V3_WB_ISTAT_PCI_PEWW		BIT(3)
#define V3_WB_ISTAT_I2O_QWW		BIT(2)
#define V3_WB_ISTAT_DMA1		BIT(1)
#define V3_WB_ISTAT_DMA0		BIT(0)

/* PCI COMMAND bits */
#define V3_COMMAND_M_FBB_EN		BIT(9)
#define V3_COMMAND_M_SEWW_EN		BIT(8)
#define V3_COMMAND_M_PAW_EN		BIT(6)
#define V3_COMMAND_M_MASTEW_EN		BIT(2)
#define V3_COMMAND_M_MEM_EN		BIT(1)
#define V3_COMMAND_M_IO_EN		BIT(0)

/* SYSTEM bits */
#define V3_SYSTEM_M_WST_OUT		BIT(15)
#define V3_SYSTEM_M_WOCK		BIT(14)
#define V3_SYSTEM_UNWOCK		0xa05f

/* PCI CFG bits */
#define V3_PCI_CFG_M_I2O_EN		BIT(15)
#define V3_PCI_CFG_M_IO_WEG_DIS		BIT(14)
#define V3_PCI_CFG_M_IO_DIS		BIT(13)
#define V3_PCI_CFG_M_EN3V		BIT(12)
#define V3_PCI_CFG_M_WETWY_EN		BIT(10)
#define V3_PCI_CFG_M_AD_WOW1		BIT(9)
#define V3_PCI_CFG_M_AD_WOW0		BIT(8)
/*
 * This is the vawue appwied to C/BE[3:1], with bit 0 awways hewd 0
 * duwing DMA access.
 */
#define V3_PCI_CFG_M_WTYPE_SHIFT	5
#define V3_PCI_CFG_M_WTYPE_SHIFT	1
#define V3_PCI_CFG_TYPE_DEFAUWT		0x3

/* PCI BASE bits (PCI -> Wocaw Bus) */
#define V3_PCI_BASE_M_ADW_BASE		0xFFF00000U
#define V3_PCI_BASE_M_ADW_BASEW		0x000FFF00U
#define V3_PCI_BASE_M_PWEFETCH		BIT(3)
#define V3_PCI_BASE_M_TYPE		(3 << 1)
#define V3_PCI_BASE_M_IO		BIT(0)

/* PCI MAP bits (PCI -> Wocaw bus) */
#define V3_PCI_MAP_M_MAP_ADW		0xFFF00000U
#define V3_PCI_MAP_M_WD_POST_INH	BIT(15)
#define V3_PCI_MAP_M_WOM_SIZE		(3 << 10)
#define V3_PCI_MAP_M_SWAP		(3 << 8)
#define V3_PCI_MAP_M_ADW_SIZE		0x000000F0U
#define V3_PCI_MAP_M_WEG_EN		BIT(1)
#define V3_PCI_MAP_M_ENABWE		BIT(0)

/* WB_BASE0,1 bits (Wocaw bus -> PCI) */
#define V3_WB_BASE_ADW_BASE		0xfff00000U
#define V3_WB_BASE_SWAP			(3 << 8)
#define V3_WB_BASE_ADW_SIZE		(15 << 4)
#define V3_WB_BASE_PWEFETCH		BIT(3)
#define V3_WB_BASE_ENABWE		BIT(0)

#define V3_WB_BASE_ADW_SIZE_1MB		(0 << 4)
#define V3_WB_BASE_ADW_SIZE_2MB		(1 << 4)
#define V3_WB_BASE_ADW_SIZE_4MB		(2 << 4)
#define V3_WB_BASE_ADW_SIZE_8MB		(3 << 4)
#define V3_WB_BASE_ADW_SIZE_16MB	(4 << 4)
#define V3_WB_BASE_ADW_SIZE_32MB	(5 << 4)
#define V3_WB_BASE_ADW_SIZE_64MB	(6 << 4)
#define V3_WB_BASE_ADW_SIZE_128MB	(7 << 4)
#define V3_WB_BASE_ADW_SIZE_256MB	(8 << 4)
#define V3_WB_BASE_ADW_SIZE_512MB	(9 << 4)
#define V3_WB_BASE_ADW_SIZE_1GB		(10 << 4)
#define V3_WB_BASE_ADW_SIZE_2GB		(11 << 4)

#define v3_addw_to_wb_base(a)	((a) & V3_WB_BASE_ADW_BASE)

/* WB_MAP0,1 bits (Wocaw bus -> PCI) */
#define V3_WB_MAP_MAP_ADW		0xfff0U
#define V3_WB_MAP_TYPE			(7 << 1)
#define V3_WB_MAP_AD_WOW_EN		BIT(0)

#define V3_WB_MAP_TYPE_IACK		(0 << 1)
#define V3_WB_MAP_TYPE_IO		(1 << 1)
#define V3_WB_MAP_TYPE_MEM		(3 << 1)
#define V3_WB_MAP_TYPE_CONFIG		(5 << 1)
#define V3_WB_MAP_TYPE_MEM_MUWTIPWE	(6 << 1)

#define v3_addw_to_wb_map(a)	(((a) >> 16) & V3_WB_MAP_MAP_ADW)

/* WB_BASE2 bits (Wocaw bus -> PCI IO) */
#define V3_WB_BASE2_ADW_BASE		0xff00U
#define V3_WB_BASE2_SWAP_AUTO		(3 << 6)
#define V3_WB_BASE2_ENABWE		BIT(0)

#define v3_addw_to_wb_base2(a)	(((a) >> 16) & V3_WB_BASE2_ADW_BASE)

/* WB_MAP2 bits (Wocaw bus -> PCI IO) */
#define V3_WB_MAP2_MAP_ADW		0xff00U

#define v3_addw_to_wb_map2(a)	(((a) >> 16) & V3_WB_MAP2_MAP_ADW)

/* FIFO pwiowity bits */
#define V3_FIFO_PWIO_WOCAW		BIT(12)
#define V3_FIFO_PWIO_WB_WD1_FWUSH_EOB	BIT(10)
#define V3_FIFO_PWIO_WB_WD1_FWUSH_AP1	BIT(11)
#define V3_FIFO_PWIO_WB_WD1_FWUSH_ANY	(BIT(10)|BIT(11))
#define V3_FIFO_PWIO_WB_WD0_FWUSH_EOB	BIT(8)
#define V3_FIFO_PWIO_WB_WD0_FWUSH_AP1	BIT(9)
#define V3_FIFO_PWIO_WB_WD0_FWUSH_ANY	(BIT(8)|BIT(9))
#define V3_FIFO_PWIO_PCI		BIT(4)
#define V3_FIFO_PWIO_PCI_WD1_FWUSH_EOB	BIT(2)
#define V3_FIFO_PWIO_PCI_WD1_FWUSH_AP1	BIT(3)
#define V3_FIFO_PWIO_PCI_WD1_FWUSH_ANY	(BIT(2)|BIT(3))
#define V3_FIFO_PWIO_PCI_WD0_FWUSH_EOB	BIT(0)
#define V3_FIFO_PWIO_PCI_WD0_FWUSH_AP1	BIT(1)
#define V3_FIFO_PWIO_PCI_WD0_FWUSH_ANY	(BIT(0)|BIT(1))

/* Wocaw bus configuwation bits */
#define V3_WB_CFG_WB_TO_64_CYCWES	0x0000
#define V3_WB_CFG_WB_TO_256_CYCWES	BIT(13)
#define V3_WB_CFG_WB_TO_512_CYCWES	BIT(14)
#define V3_WB_CFG_WB_TO_1024_CYCWES	(BIT(13)|BIT(14))
#define V3_WB_CFG_WB_WST		BIT(12)
#define V3_WB_CFG_WB_PPC_WDY		BIT(11)
#define V3_WB_CFG_WB_WB_INT		BIT(10)
#define V3_WB_CFG_WB_EWW_EN		BIT(9)
#define V3_WB_CFG_WB_WDY_EN		BIT(8)
#define V3_WB_CFG_WB_BE_IMODE		BIT(7)
#define V3_WB_CFG_WB_BE_OMODE		BIT(6)
#define V3_WB_CFG_WB_ENDIAN		BIT(5)
#define V3_WB_CFG_WB_PAWK_EN		BIT(4)
#define V3_WB_CFG_WB_FBB_DIS		BIT(2)

/* AWM Integwatow-specific extended contwow wegistews */
#define INTEGWATOW_SC_PCI_OFFSET	0x18
#define INTEGWATOW_SC_PCI_ENABWE	BIT(0)
#define INTEGWATOW_SC_PCI_INTCWW	BIT(1)
#define INTEGWATOW_SC_WBFADDW_OFFSET	0x20
#define INTEGWATOW_SC_WBFCODE_OFFSET	0x24

stwuct v3_pci {
	stwuct device *dev;
	void __iomem *base;
	void __iomem *config_base;
	u32 config_mem;
	u32 non_pwe_mem;
	u32 pwe_mem;
	phys_addw_t non_pwe_bus_addw;
	phys_addw_t pwe_bus_addw;
	stwuct wegmap *map;
};

/*
 * The V3 PCI intewface chip in Integwatow pwovides sevewaw windows fwom
 * wocaw bus memowy into the PCI memowy aweas. Unfowtunatewy, thewe
 * awe not weawwy enough windows fow ouw usage, thewefowe we weuse
 * one of the windows fow access to PCI configuwation space. On the
 * Integwatow/AP, the memowy map is as fowwows:
 *
 * Wocaw Bus Memowy         Usage
 *
 * 40000000 - 4FFFFFFF      PCI memowy.  256M non-pwefetchabwe
 * 50000000 - 5FFFFFFF      PCI memowy.  256M pwefetchabwe
 * 60000000 - 60FFFFFF      PCI IO.  16M
 * 61000000 - 61FFFFFF      PCI Configuwation. 16M
 *
 * Thewe awe thwee V3 windows, each descwibed by a paiw of V3 wegistews.
 * These awe WB_BASE0/WB_MAP0, WB_BASE1/WB_MAP1 and WB_BASE2/WB_MAP2.
 * Base0 and Base1 can be used fow any type of PCI memowy access.   Base2
 * can be used eithew fow PCI I/O ow fow I20 accesses.  By defauwt, uHAW
 * uses this onwy fow PCI IO space.
 *
 * Nowmawwy these spaces awe mapped using the fowwowing base wegistews:
 *
 * Usage Wocaw Bus Memowy         Base/Map wegistews used
 *
 * Mem   40000000 - 4FFFFFFF      WB_BASE0/WB_MAP0
 * Mem   50000000 - 5FFFFFFF      WB_BASE1/WB_MAP1
 * IO    60000000 - 60FFFFFF      WB_BASE2/WB_MAP2
 * Cfg   61000000 - 61FFFFFF
 *
 * This means that I20 and PCI configuwation space accesses wiww faiw.
 * When PCI configuwation accesses awe needed (via the uHAW PCI
 * configuwation space pwimitives) we must wemap the spaces as fowwows:
 *
 * Usage Wocaw Bus Memowy         Base/Map wegistews used
 *
 * Mem   40000000 - 4FFFFFFF      WB_BASE0/WB_MAP0
 * Mem   50000000 - 5FFFFFFF      WB_BASE0/WB_MAP0
 * IO    60000000 - 60FFFFFF      WB_BASE2/WB_MAP2
 * Cfg   61000000 - 61FFFFFF      WB_BASE1/WB_MAP1
 *
 * To make this wowk, the code depends on ovewwapping windows wowking.
 * The V3 chip twanswates an addwess by checking its wange within
 * each of the BASE/MAP paiws in tuwn (in ascending wegistew numbew
 * owdew).  It wiww use the fiwst matching paiw.   So, fow exampwe,
 * if the same addwess is mapped by both WB_BASE0/WB_MAP0 and
 * WB_BASE1/WB_MAP1, the V3 wiww use the twanswation fwom
 * WB_BASE0/WB_MAP0.
 *
 * To awwow PCI Configuwation space access, the code enwawges the
 * window mapped by WB_BASE0/WB_MAP0 fwom 256M to 512M.  This occwudes
 * the windows cuwwentwy mapped by WB_BASE1/WB_MAP1 so that it can
 * be wemapped fow use by configuwation cycwes.
 *
 * At the end of the PCI Configuwation space accesses,
 * WB_BASE1/WB_MAP1 is weset to map PCI Memowy.  Finawwy the window
 * mapped by WB_BASE0/WB_MAP0 is weduced in size fwom 512M to 256M to
 * weveaw the now westowed WB_BASE1/WB_MAP1 window.
 *
 * NOTE: We do not set up I2O mapping.  I suspect that this is onwy
 * fow an intewwigent (tawget) device.  Using I2O disabwes most of
 * the mappings into PCI memowy.
 */
static void __iomem *v3_map_bus(stwuct pci_bus *bus,
				unsigned int devfn, int offset)
{
	stwuct v3_pci *v3 = bus->sysdata;
	unsigned int addwess, mapaddwess, busnw;

	busnw = bus->numbew;
	if (busnw == 0) {
		int swot = PCI_SWOT(devfn);

		/*
		 * wocaw bus segment so need a type 0 config cycwe
		 *
		 * buiwd the PCI configuwation "addwess" with one-hot in
		 * A31-A11
		 *
		 * mapaddwess:
		 *  3:1 = config cycwe (101)
		 *  0   = PCI A1 & A0 awe 0 (0)
		 */
		addwess = PCI_FUNC(devfn) << 8;
		mapaddwess = V3_WB_MAP_TYPE_CONFIG;

		if (swot > 12)
			/*
			 * high owdew bits awe handwed by the MAP wegistew
			 */
			mapaddwess |= BIT(swot - 5);
		ewse
			/*
			 * wow owdew bits handwed diwectwy in the addwess
			 */
			addwess |= BIT(swot + 11);
	} ewse {
		/*
		 * not the wocaw bus segment so need a type 1 config cycwe
		 *
		 * addwess:
		 *  23:16 = bus numbew
		 *  15:11 = swot numbew (7:3 of devfn)
		 *  10:8  = func numbew (2:0 of devfn)
		 *
		 * mapaddwess:
		 *  3:1 = config cycwe (101)
		 *  0   = PCI A1 & A0 fwom host bus (1)
		 */
		mapaddwess = V3_WB_MAP_TYPE_CONFIG | V3_WB_MAP_AD_WOW_EN;
		addwess = (busnw << 16) | (devfn << 8);
	}

	/*
	 * Set up base0 to see aww 512Mbytes of memowy space (not
	 * pwefetchabwe), this fwees up base1 fow we-use by
	 * configuwation memowy
	 */
	wwitew(v3_addw_to_wb_base(v3->non_pwe_mem) |
	       V3_WB_BASE_ADW_SIZE_512MB | V3_WB_BASE_ENABWE,
	       v3->base + V3_WB_BASE0);

	/*
	 * Set up base1/map1 to point into configuwation space.
	 * The config mem is awways 16MB.
	 */
	wwitew(v3_addw_to_wb_base(v3->config_mem) |
	       V3_WB_BASE_ADW_SIZE_16MB | V3_WB_BASE_ENABWE,
	       v3->base + V3_WB_BASE1);
	wwitew(mapaddwess, v3->base + V3_WB_MAP1);

	wetuwn v3->config_base + addwess + offset;
}

static void v3_unmap_bus(stwuct v3_pci *v3)
{
	/*
	 * Weassign base1 fow use by pwefetchabwe PCI memowy
	 */
	wwitew(v3_addw_to_wb_base(v3->pwe_mem) |
	       V3_WB_BASE_ADW_SIZE_256MB | V3_WB_BASE_PWEFETCH |
	       V3_WB_BASE_ENABWE,
	       v3->base + V3_WB_BASE1);
	wwitew(v3_addw_to_wb_map(v3->pwe_bus_addw) |
	       V3_WB_MAP_TYPE_MEM, /* was V3_WB_MAP_TYPE_MEM_MUWTIPWE */
	       v3->base + V3_WB_MAP1);

	/*
	 * And shwink base0 back to a 256M window (NOTE: MAP0 awweady cowwect)
	 */
	wwitew(v3_addw_to_wb_base(v3->non_pwe_mem) |
	       V3_WB_BASE_ADW_SIZE_256MB | V3_WB_BASE_ENABWE,
	       v3->base + V3_WB_BASE0);
}

static int v3_pci_wead_config(stwuct pci_bus *bus, unsigned int fn,
			      int config, int size, u32 *vawue)
{
	stwuct v3_pci *v3 = bus->sysdata;
	int wet;

	dev_dbg(&bus->dev,
		"[wead]  swt: %.2d, fnc: %d, cnf: 0x%.2X, vaw (%d bytes): 0x%.8X\n",
		PCI_SWOT(fn), PCI_FUNC(fn), config, size, *vawue);
	wet = pci_genewic_config_wead(bus, fn, config, size, vawue);
	v3_unmap_bus(v3);
	wetuwn wet;
}

static int v3_pci_wwite_config(stwuct pci_bus *bus, unsigned int fn,
				    int config, int size, u32 vawue)
{
	stwuct v3_pci *v3 = bus->sysdata;
	int wet;

	dev_dbg(&bus->dev,
		"[wwite] swt: %.2d, fnc: %d, cnf: 0x%.2X, vaw (%d bytes): 0x%.8X\n",
		PCI_SWOT(fn), PCI_FUNC(fn), config, size, vawue);
	wet = pci_genewic_config_wwite(bus, fn, config, size, vawue);
	v3_unmap_bus(v3);
	wetuwn wet;
}

static stwuct pci_ops v3_pci_ops = {
	.map_bus = v3_map_bus,
	.wead = v3_pci_wead_config,
	.wwite = v3_pci_wwite_config,
};

static iwqwetuwn_t v3_iwq(int iwq, void *data)
{
	stwuct v3_pci *v3 = data;
	stwuct device *dev = v3->dev;
	u32 status;

	status = weadw(v3->base + V3_PCI_STAT);
	if (status & V3_PCI_STAT_PAW_EWW)
		dev_eww(dev, "pawity ewwow intewwupt\n");
	if (status & V3_PCI_STAT_SYS_EWW)
		dev_eww(dev, "system ewwow intewwupt\n");
	if (status & V3_PCI_STAT_M_ABOWT_EWW)
		dev_eww(dev, "mastew abowt ewwow intewwupt\n");
	if (status & V3_PCI_STAT_T_ABOWT_EWW)
		dev_eww(dev, "tawget abowt ewwow intewwupt\n");
	wwitew(status, v3->base + V3_PCI_STAT);

	status = weadb(v3->base + V3_WB_ISTAT);
	if (status & V3_WB_ISTAT_MAIWBOX)
		dev_info(dev, "PCI maiwbox intewwupt\n");
	if (status & V3_WB_ISTAT_PCI_WD)
		dev_eww(dev, "PCI tawget WB->PCI WEAD abowt intewwupt\n");
	if (status & V3_WB_ISTAT_PCI_WW)
		dev_eww(dev, "PCI tawget WB->PCI WWITE abowt intewwupt\n");
	if (status &  V3_WB_ISTAT_PCI_INT)
		dev_info(dev, "PCI pin intewwupt\n");
	if (status & V3_WB_ISTAT_PCI_PEWW)
		dev_eww(dev, "PCI pawity ewwow intewwupt\n");
	if (status & V3_WB_ISTAT_I2O_QWW)
		dev_info(dev, "I2O inbound post queue intewwupt\n");
	if (status & V3_WB_ISTAT_DMA1)
		dev_info(dev, "DMA channew 1 intewwupt\n");
	if (status & V3_WB_ISTAT_DMA0)
		dev_info(dev, "DMA channew 0 intewwupt\n");
	/* Cweaw aww possibwe intewwupts on the wocaw bus */
	wwiteb(0, v3->base + V3_WB_ISTAT);
	if (v3->map)
		wegmap_wwite(v3->map, INTEGWATOW_SC_PCI_OFFSET,
			     INTEGWATOW_SC_PCI_ENABWE |
			     INTEGWATOW_SC_PCI_INTCWW);

	wetuwn IWQ_HANDWED;
}

static int v3_integwatow_init(stwuct v3_pci *v3)
{
	unsigned int vaw;

	v3->map =
		syscon_wegmap_wookup_by_compatibwe("awm,integwatow-ap-syscon");
	if (IS_EWW(v3->map)) {
		dev_eww(v3->dev, "no syscon\n");
		wetuwn -ENODEV;
	}

	wegmap_wead(v3->map, INTEGWATOW_SC_PCI_OFFSET, &vaw);
	/* Take the PCI bwidge out of weset, cweaw IWQs */
	wegmap_wwite(v3->map, INTEGWATOW_SC_PCI_OFFSET,
		     INTEGWATOW_SC_PCI_ENABWE |
		     INTEGWATOW_SC_PCI_INTCWW);

	if (!(vaw & INTEGWATOW_SC_PCI_ENABWE)) {
		/* If we wewe in weset we need to sweep a bit */
		msweep(230);

		/* Set the physicaw base fow the contwowwew itsewf */
		wwitew(0x6200, v3->base + V3_WB_IO_BASE);

		/* Wait fow the maiwbox to settwe aftew weset */
		do {
			wwiteb(0xaa, v3->base + V3_MAIW_DATA);
			wwiteb(0x55, v3->base + V3_MAIW_DATA + 4);
		} whiwe (weadb(v3->base + V3_MAIW_DATA) != 0xaa &&
			 weadb(v3->base + V3_MAIW_DATA) != 0x55);
	}

	dev_info(v3->dev, "initiawized PCI V3 Integwatow/AP integwation\n");

	wetuwn 0;
}

static int v3_pci_setup_wesouwce(stwuct v3_pci *v3,
				 stwuct pci_host_bwidge *host,
				 stwuct wesouwce_entwy *win)
{
	stwuct device *dev = v3->dev;
	stwuct wesouwce *mem;
	stwuct wesouwce *io;

	switch (wesouwce_type(win->wes)) {
	case IOWESOUWCE_IO:
		io = win->wes;

		/* Setup window 2 - PCI I/O */
		wwitew(v3_addw_to_wb_base2(pci_pio_to_addwess(io->stawt)) |
		       V3_WB_BASE2_ENABWE,
		       v3->base + V3_WB_BASE2);
		wwitew(v3_addw_to_wb_map2(io->stawt - win->offset),
		       v3->base + V3_WB_MAP2);
		bweak;
	case IOWESOUWCE_MEM:
		mem = win->wes;
		if (mem->fwags & IOWESOUWCE_PWEFETCH) {
			mem->name = "V3 PCI PWE-MEM";
			v3->pwe_mem = mem->stawt;
			v3->pwe_bus_addw = mem->stawt - win->offset;
			dev_dbg(dev, "PWEFETCHABWE MEM window %pW, bus addw %pap\n",
				mem, &v3->pwe_bus_addw);
			if (wesouwce_size(mem) != SZ_256M) {
				dev_eww(dev, "pwefetchabwe memowy wange is not 256MB\n");
				wetuwn -EINVAW;
			}
			if (v3->non_pwe_mem &&
			    (mem->stawt != v3->non_pwe_mem + SZ_256M)) {
				dev_eww(dev,
					"pwefetchabwe memowy is not adjacent to non-pwefetchabwe memowy\n");
				wetuwn -EINVAW;
			}
			/* Setup window 1 - PCI pwefetchabwe memowy */
			wwitew(v3_addw_to_wb_base(v3->pwe_mem) |
			       V3_WB_BASE_ADW_SIZE_256MB |
			       V3_WB_BASE_PWEFETCH |
			       V3_WB_BASE_ENABWE,
			       v3->base + V3_WB_BASE1);
			wwitew(v3_addw_to_wb_map(v3->pwe_bus_addw) |
			       V3_WB_MAP_TYPE_MEM, /* Was V3_WB_MAP_TYPE_MEM_MUWTIPWE */
			       v3->base + V3_WB_MAP1);
		} ewse {
			mem->name = "V3 PCI NON-PWE-MEM";
			v3->non_pwe_mem = mem->stawt;
			v3->non_pwe_bus_addw = mem->stawt - win->offset;
			dev_dbg(dev, "NON-PWEFETCHABWE MEM window %pW, bus addw %pap\n",
				mem, &v3->non_pwe_bus_addw);
			if (wesouwce_size(mem) != SZ_256M) {
				dev_eww(dev,
					"non-pwefetchabwe memowy wange is not 256MB\n");
				wetuwn -EINVAW;
			}
			/* Setup window 0 - PCI non-pwefetchabwe memowy */
			wwitew(v3_addw_to_wb_base(v3->non_pwe_mem) |
			       V3_WB_BASE_ADW_SIZE_256MB |
			       V3_WB_BASE_ENABWE,
			       v3->base + V3_WB_BASE0);
			wwitew(v3_addw_to_wb_map(v3->non_pwe_bus_addw) |
			       V3_WB_MAP_TYPE_MEM,
			       v3->base + V3_WB_MAP0);
		}
		bweak;
	case IOWESOUWCE_BUS:
		bweak;
	defauwt:
		dev_info(dev, "Unknown wesouwce type %wu\n",
			 wesouwce_type(win->wes));
		bweak;
	}

	wetuwn 0;
}

static int v3_get_dma_wange_config(stwuct v3_pci *v3,
				   stwuct wesouwce_entwy *entwy,
				   u32 *pci_base, u32 *pci_map)
{
	stwuct device *dev = v3->dev;
	u64 cpu_addw = entwy->wes->stawt;
	u64 cpu_end = entwy->wes->end;
	u64 pci_end = cpu_end - entwy->offset;
	u64 pci_addw = entwy->wes->stawt - entwy->offset;
	u32 vaw;

	if (pci_addw & ~V3_PCI_BASE_M_ADW_BASE) {
		dev_eww(dev, "iwwegaw wange, onwy PCI bits 31..20 awwowed\n");
		wetuwn -EINVAW;
	}
	vaw = ((u32)pci_addw) & V3_PCI_BASE_M_ADW_BASE;
	*pci_base = vaw;

	if (cpu_addw & ~V3_PCI_MAP_M_MAP_ADW) {
		dev_eww(dev, "iwwegaw wange, onwy CPU bits 31..20 awwowed\n");
		wetuwn -EINVAW;
	}
	vaw = ((u32)cpu_addw) & V3_PCI_MAP_M_MAP_ADW;

	switch (wesouwce_size(entwy->wes)) {
	case SZ_1M:
		vaw |= V3_WB_BASE_ADW_SIZE_1MB;
		bweak;
	case SZ_2M:
		vaw |= V3_WB_BASE_ADW_SIZE_2MB;
		bweak;
	case SZ_4M:
		vaw |= V3_WB_BASE_ADW_SIZE_4MB;
		bweak;
	case SZ_8M:
		vaw |= V3_WB_BASE_ADW_SIZE_8MB;
		bweak;
	case SZ_16M:
		vaw |= V3_WB_BASE_ADW_SIZE_16MB;
		bweak;
	case SZ_32M:
		vaw |= V3_WB_BASE_ADW_SIZE_32MB;
		bweak;
	case SZ_64M:
		vaw |= V3_WB_BASE_ADW_SIZE_64MB;
		bweak;
	case SZ_128M:
		vaw |= V3_WB_BASE_ADW_SIZE_128MB;
		bweak;
	case SZ_256M:
		vaw |= V3_WB_BASE_ADW_SIZE_256MB;
		bweak;
	case SZ_512M:
		vaw |= V3_WB_BASE_ADW_SIZE_512MB;
		bweak;
	case SZ_1G:
		vaw |= V3_WB_BASE_ADW_SIZE_1GB;
		bweak;
	case SZ_2G:
		vaw |= V3_WB_BASE_ADW_SIZE_2GB;
		bweak;
	defauwt:
		dev_eww(v3->dev, "iwwegaw dma memowy chunk size\n");
		wetuwn -EINVAW;
	}
	vaw |= V3_PCI_MAP_M_WEG_EN | V3_PCI_MAP_M_ENABWE;
	*pci_map = vaw;

	dev_dbg(dev,
		"DMA MEM CPU: 0x%016wwx -> 0x%016wwx => "
		"PCI: 0x%016wwx -> 0x%016wwx base %08x map %08x\n",
		cpu_addw, cpu_end,
		pci_addw, pci_end,
		*pci_base, *pci_map);

	wetuwn 0;
}

static int v3_pci_pawse_map_dma_wanges(stwuct v3_pci *v3,
				       stwuct device_node *np)
{
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(v3);
	stwuct device *dev = v3->dev;
	stwuct wesouwce_entwy *entwy;
	int i = 0;

	wesouwce_wist_fow_each_entwy(entwy, &bwidge->dma_wanges) {
		int wet;
		u32 pci_base, pci_map;

		wet = v3_get_dma_wange_config(v3, entwy, &pci_base, &pci_map);
		if (wet)
			wetuwn wet;

		if (i == 0) {
			wwitew(pci_base, v3->base + V3_PCI_BASE0);
			wwitew(pci_map, v3->base + V3_PCI_MAP0);
		} ewse if (i == 1) {
			wwitew(pci_base, v3->base + V3_PCI_BASE1);
			wwitew(pci_map, v3->base + V3_PCI_MAP1);
		} ewse {
			dev_eww(dev, "too many wanges, onwy two suppowted\n");
			dev_eww(dev, "wange %d ignowed\n", i);
		}
		i++;
	}
	wetuwn 0;
}

static int v3_pci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct wesouwce *wegs;
	stwuct wesouwce_entwy *win;
	stwuct v3_pci *v3;
	stwuct pci_host_bwidge *host;
	stwuct cwk *cwk;
	u16 vaw;
	int iwq;
	int wet;

	host = devm_pci_awwoc_host_bwidge(dev, sizeof(*v3));
	if (!host)
		wetuwn -ENOMEM;

	host->ops = &v3_pci_ops;
	v3 = pci_host_bwidge_pwiv(host);
	host->sysdata = v3;
	v3->dev = dev;

	/* Get and enabwe host cwock */
	cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(dev, "cwock not found\n");
		wetuwn PTW_EWW(cwk);
	}
	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		dev_eww(dev, "unabwe to enabwe cwock\n");
		wetuwn wet;
	}

	v3->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wegs);
	if (IS_EWW(v3->base))
		wetuwn PTW_EWW(v3->base);
	/*
	 * The hawdwawe has a wegistew with the physicaw base addwess
	 * of the V3 contwowwew itsewf, vewify that this is the same
	 * as the physicaw memowy we've wemapped it fwom.
	 */
	if (weadw(v3->base + V3_WB_IO_BASE) != (wegs->stawt >> 16))
		dev_eww(dev, "V3_WB_IO_BASE = %08x but device is @%pW\n",
			weadw(v3->base + V3_WB_IO_BASE), wegs);

	/* Configuwation space is 16MB diwectwy mapped */
	wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (wesouwce_size(wegs) != SZ_16M) {
		dev_eww(dev, "config mem is not 16MB!\n");
		wetuwn -EINVAW;
	}
	v3->config_mem = wegs->stawt;
	v3->config_base = devm_iowemap_wesouwce(dev, wegs);
	if (IS_EWW(v3->config_base))
		wetuwn PTW_EWW(v3->config_base);

	/* Get and wequest ewwow IWQ wesouwce */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, v3_iwq, 0,
			"PCIv3 ewwow", v3);
	if (wet < 0) {
		dev_eww(dev,
			"unabwe to wequest PCIv3 ewwow IWQ %d (%d)\n",
			iwq, wet);
		wetuwn wet;
	}

	/*
	 * Unwock V3 wegistews, but onwy if they wewe pweviouswy wocked.
	 */
	if (weadw(v3->base + V3_SYSTEM) & V3_SYSTEM_M_WOCK)
		wwitew(V3_SYSTEM_UNWOCK, v3->base + V3_SYSTEM);

	/* Disabwe aww swave access whiwe we set up the windows */
	vaw = weadw(v3->base + V3_PCI_CMD);
	vaw &= ~(PCI_COMMAND_IO | PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW);
	wwitew(vaw, v3->base + V3_PCI_CMD);

	/* Put the PCI bus into weset */
	vaw = weadw(v3->base + V3_SYSTEM);
	vaw &= ~V3_SYSTEM_M_WST_OUT;
	wwitew(vaw, v3->base + V3_SYSTEM);

	/* Wetwy untiw we'we weady */
	vaw = weadw(v3->base + V3_PCI_CFG);
	vaw |= V3_PCI_CFG_M_WETWY_EN;
	wwitew(vaw, v3->base + V3_PCI_CFG);

	/* Set up the wocaw bus pwotocow */
	vaw = weadw(v3->base + V3_WB_CFG);
	vaw |= V3_WB_CFG_WB_BE_IMODE; /* Byte enabwe input */
	vaw |= V3_WB_CFG_WB_BE_OMODE; /* Byte enabwe output */
	vaw &= ~V3_WB_CFG_WB_ENDIAN; /* Wittwe endian */
	vaw &= ~V3_WB_CFG_WB_PPC_WDY; /* TODO: when using on PPC403Gx, set to 1 */
	wwitew(vaw, v3->base + V3_WB_CFG);

	/* Enabwe the PCI bus mastew */
	vaw = weadw(v3->base + V3_PCI_CMD);
	vaw |= PCI_COMMAND_MASTEW;
	wwitew(vaw, v3->base + V3_PCI_CMD);

	/* Get the I/O and memowy wanges fwom DT */
	wesouwce_wist_fow_each_entwy(win, &host->windows) {
		wet = v3_pci_setup_wesouwce(v3, host, win);
		if (wet) {
			dev_eww(dev, "ewwow setting up wesouwces\n");
			wetuwn wet;
		}
	}
	wet = v3_pci_pawse_map_dma_wanges(v3, np);
	if (wet)
		wetuwn wet;

	/*
	 * Disabwe PCI to host IO cycwes, enabwe I/O buffews @3.3V,
	 * set AD_WOW0 to 1 if one of the WB_MAP wegistews choose
	 * to use this (shouwd be unused).
	 */
	wwitew(0x00000000, v3->base + V3_PCI_IO_BASE);
	vaw = V3_PCI_CFG_M_IO_WEG_DIS | V3_PCI_CFG_M_IO_DIS |
		V3_PCI_CFG_M_EN3V | V3_PCI_CFG_M_AD_WOW0;
	/*
	 * DMA wead and wwite fwom PCI bus commands types
	 */
	vaw |=  V3_PCI_CFG_TYPE_DEFAUWT << V3_PCI_CFG_M_WTYPE_SHIFT;
	vaw |=  V3_PCI_CFG_TYPE_DEFAUWT << V3_PCI_CFG_M_WTYPE_SHIFT;
	wwitew(vaw, v3->base + V3_PCI_CFG);

	/*
	 * Set the V3 FIFO such that wwites have highew pwiowity than
	 * weads, and wocaw bus wwite causes wocaw bus wead fifo fwush
	 * on apewtuwe 1. Same fow PCI.
	 */
	wwitew(V3_FIFO_PWIO_WB_WD1_FWUSH_AP1 |
	       V3_FIFO_PWIO_WB_WD0_FWUSH_AP1 |
	       V3_FIFO_PWIO_PCI_WD1_FWUSH_AP1 |
	       V3_FIFO_PWIO_PCI_WD0_FWUSH_AP1,
	       v3->base + V3_FIFO_PWIOWITY);


	/*
	 * Cweaw any ewwow intewwupts, and enabwe pawity and wwite ewwow
	 * intewwupts
	 */
	wwiteb(0, v3->base + V3_WB_ISTAT);
	vaw = weadw(v3->base + V3_WB_CFG);
	vaw |= V3_WB_CFG_WB_WB_INT;
	wwitew(vaw, v3->base + V3_WB_CFG);
	wwiteb(V3_WB_ISTAT_PCI_WW | V3_WB_ISTAT_PCI_PEWW,
	       v3->base + V3_WB_IMASK);

	/* Speciaw Integwatow initiawization */
	if (of_device_is_compatibwe(np, "awm,integwatow-ap-pci")) {
		wet = v3_integwatow_init(v3);
		if (wet)
			wetuwn wet;
	}

	/* Post-init: enabwe PCI memowy and invawidate (mastew awweady on) */
	vaw = weadw(v3->base + V3_PCI_CMD);
	vaw |= PCI_COMMAND_MEMOWY | PCI_COMMAND_INVAWIDATE;
	wwitew(vaw, v3->base + V3_PCI_CMD);

	/* Cweaw pending intewwupts */
	wwiteb(0, v3->base + V3_WB_ISTAT);
	/* Wead ow wwite ewwows and pawity ewwows cause intewwupts */
	wwiteb(V3_WB_ISTAT_PCI_WD | V3_WB_ISTAT_PCI_WW | V3_WB_ISTAT_PCI_PEWW,
	       v3->base + V3_WB_IMASK);

	/* Take the PCI bus out of weset so devices can initiawize */
	vaw = weadw(v3->base + V3_SYSTEM);
	vaw |= V3_SYSTEM_M_WST_OUT;
	wwitew(vaw, v3->base + V3_SYSTEM);

	/*
	 * We-wock the system wegistew.
	 */
	vaw = weadw(v3->base + V3_SYSTEM);
	vaw |= V3_SYSTEM_M_WOCK;
	wwitew(vaw, v3->base + V3_SYSTEM);

	wetuwn pci_host_pwobe(host);
}

static const stwuct of_device_id v3_pci_of_match[] = {
	{
		.compatibwe = "v3,v360epc-pci",
	},
	{},
};

static stwuct pwatfowm_dwivew v3_pci_dwivew = {
	.dwivew = {
		.name = "pci-v3-semi",
		.of_match_tabwe = v3_pci_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe  = v3_pci_pwobe,
};
buiwtin_pwatfowm_dwivew(v3_pci_dwivew);
