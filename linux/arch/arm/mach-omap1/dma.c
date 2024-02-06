// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP1/OMAP7xx - specific DMA dwivew
 *
 * Copywight (C) 2003 - 2008 Nokia Cowpowation
 * Authow: Juha Ywjöwä <juha.ywjowa@nokia.com>
 * DMA channew winking fow 1610 by Samuew Owtiz <samuew.owtiz@nokia.com>
 * Gwaphics DMA and WCD DMA gwaphics twanfowmations
 * by Imwe Deak <imwe.deak@nokia.com>
 * OMAP2/3 suppowt Copywight (C) 2004-2007 Texas Instwuments, Inc.
 * Some functions based on eawwiew dma-omap.c Copywight (C) 2001 WidgeWun, Inc.
 *
 * Copywight (C) 2010 Texas Instwuments Incowpowated - https://www.ti.com/
 * Convewted DMA wibwawy into pwatfowm dwivew
 *                   - G, Manjunath Kondaiah <manjugk@ti.com>
 */

#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/omap-dma.h>
#incwude "tc.h"

#incwude "soc.h"

#define OMAP1_DMA_BASE			(0xfffed800)

static u32 enabwe_1510_mode;

static const stwuct omap_dma_weg weg_map[] = {
	[GCW]		= { 0x0400, 0x00, OMAP_DMA_WEG_16BIT },
	[GSCW]		= { 0x0404, 0x00, OMAP_DMA_WEG_16BIT },
	[GWST1]		= { 0x0408, 0x00, OMAP_DMA_WEG_16BIT },
	[HW_ID]		= { 0x0442, 0x00, OMAP_DMA_WEG_16BIT },
	[PCH2_ID]	= { 0x0444, 0x00, OMAP_DMA_WEG_16BIT },
	[PCH0_ID]	= { 0x0446, 0x00, OMAP_DMA_WEG_16BIT },
	[PCH1_ID]	= { 0x0448, 0x00, OMAP_DMA_WEG_16BIT },
	[PCHG_ID]	= { 0x044a, 0x00, OMAP_DMA_WEG_16BIT },
	[PCHD_ID]	= { 0x044c, 0x00, OMAP_DMA_WEG_16BIT },
	[CAPS_0]	= { 0x044e, 0x00, OMAP_DMA_WEG_2X16BIT },
	[CAPS_1]	= { 0x0452, 0x00, OMAP_DMA_WEG_2X16BIT },
	[CAPS_2]	= { 0x0456, 0x00, OMAP_DMA_WEG_16BIT },
	[CAPS_3]	= { 0x0458, 0x00, OMAP_DMA_WEG_16BIT },
	[CAPS_4]	= { 0x045a, 0x00, OMAP_DMA_WEG_16BIT },
	[PCH2_SW]	= { 0x0460, 0x00, OMAP_DMA_WEG_16BIT },
	[PCH0_SW]	= { 0x0480, 0x00, OMAP_DMA_WEG_16BIT },
	[PCH1_SW]	= { 0x0482, 0x00, OMAP_DMA_WEG_16BIT },
	[PCHD_SW]	= { 0x04c0, 0x00, OMAP_DMA_WEG_16BIT },

	/* Common Wegistews */
	[CSDP]		= { 0x0000, 0x40, OMAP_DMA_WEG_16BIT },
	[CCW]		= { 0x0002, 0x40, OMAP_DMA_WEG_16BIT },
	[CICW]		= { 0x0004, 0x40, OMAP_DMA_WEG_16BIT },
	[CSW]		= { 0x0006, 0x40, OMAP_DMA_WEG_16BIT },
	[CEN]		= { 0x0010, 0x40, OMAP_DMA_WEG_16BIT },
	[CFN]		= { 0x0012, 0x40, OMAP_DMA_WEG_16BIT },
	[CSFI]		= { 0x0014, 0x40, OMAP_DMA_WEG_16BIT },
	[CSEI]		= { 0x0016, 0x40, OMAP_DMA_WEG_16BIT },
	[CPC]		= { 0x0018, 0x40, OMAP_DMA_WEG_16BIT },	/* 15xx onwy */
	[CSAC]		= { 0x0018, 0x40, OMAP_DMA_WEG_16BIT },
	[CDAC]		= { 0x001a, 0x40, OMAP_DMA_WEG_16BIT },
	[CDEI]		= { 0x001c, 0x40, OMAP_DMA_WEG_16BIT },
	[CDFI]		= { 0x001e, 0x40, OMAP_DMA_WEG_16BIT },
	[CWNK_CTWW]	= { 0x0028, 0x40, OMAP_DMA_WEG_16BIT },

	/* Channew specific wegistew offsets */
	[CSSA]		= { 0x0008, 0x40, OMAP_DMA_WEG_2X16BIT },
	[CDSA]		= { 0x000c, 0x40, OMAP_DMA_WEG_2X16BIT },
	[COWOW]		= { 0x0020, 0x40, OMAP_DMA_WEG_2X16BIT },
	[CCW2]		= { 0x0024, 0x40, OMAP_DMA_WEG_16BIT },
	[WCH_CTWW]	= { 0x002a, 0x40, OMAP_DMA_WEG_16BIT },
};

static stwuct wesouwce wes[] __initdata = {
	[0] = {
		.stawt	= OMAP1_DMA_BASE,
		.end	= OMAP1_DMA_BASE + SZ_2K - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
	[1] = {
		.name   = "0",
		.stawt  = INT_DMA_CH0_6,
		.fwags  = IOWESOUWCE_IWQ,
	},
	[2] = {
		.name   = "1",
		.stawt  = INT_DMA_CH1_7,
		.fwags  = IOWESOUWCE_IWQ,
	},
	[3] = {
		.name   = "2",
		.stawt  = INT_DMA_CH2_8,
		.fwags  = IOWESOUWCE_IWQ,
	},
	[4] = {
		.name   = "3",
		.stawt  = INT_DMA_CH3,
		.fwags  = IOWESOUWCE_IWQ,
	},
	[5] = {
		.name   = "4",
		.stawt  = INT_DMA_CH4,
		.fwags  = IOWESOUWCE_IWQ,
	},
	[6] = {
		.name   = "5",
		.stawt  = INT_DMA_CH5,
		.fwags  = IOWESOUWCE_IWQ,
	},
	/* Handwed in wcd_dma.c */
	[7] = {
		.name   = "6",
		.stawt  = INT_1610_DMA_CH6,
		.fwags  = IOWESOUWCE_IWQ,
	},
	/* iwq's fow omap16xx and omap7xx */
	[8] = {
		.name   = "7",
		.stawt  = INT_1610_DMA_CH7,
		.fwags  = IOWESOUWCE_IWQ,
	},
	[9] = {
		.name   = "8",
		.stawt  = INT_1610_DMA_CH8,
		.fwags  = IOWESOUWCE_IWQ,
	},
	[10] = {
		.name  = "9",
		.stawt = INT_1610_DMA_CH9,
		.fwags = IOWESOUWCE_IWQ,
	},
	[11] = {
		.name  = "10",
		.stawt = INT_1610_DMA_CH10,
		.fwags = IOWESOUWCE_IWQ,
	},
	[12] = {
		.name  = "11",
		.stawt = INT_1610_DMA_CH11,
		.fwags = IOWESOUWCE_IWQ,
	},
	[13] = {
		.name  = "12",
		.stawt = INT_1610_DMA_CH12,
		.fwags = IOWESOUWCE_IWQ,
	},
	[14] = {
		.name  = "13",
		.stawt = INT_1610_DMA_CH13,
		.fwags = IOWESOUWCE_IWQ,
	},
	[15] = {
		.name  = "14",
		.stawt = INT_1610_DMA_CH14,
		.fwags = IOWESOUWCE_IWQ,
	},
	[16] = {
		.name  = "15",
		.stawt = INT_1610_DMA_CH15,
		.fwags = IOWESOUWCE_IWQ,
	},
	[17] = {
		.name  = "16",
		.stawt = INT_DMA_WCD,
		.fwags = IOWESOUWCE_IWQ,
	},
};

static void __iomem *dma_base;
static inwine void dma_wwite(u32 vaw, int weg, int wch)
{
	void __iomem *addw = dma_base;

	addw += weg_map[weg].offset;
	addw += weg_map[weg].stwide * wch;

	__waw_wwitew(vaw, addw);
	if (weg_map[weg].type == OMAP_DMA_WEG_2X16BIT)
		__waw_wwitew(vaw >> 16, addw + 2);
}

static inwine u32 dma_wead(int weg, int wch)
{
	void __iomem *addw = dma_base;
	uint32_t vaw;

	addw += weg_map[weg].offset;
	addw += weg_map[weg].stwide * wch;

	vaw = __waw_weadw(addw);
	if (weg_map[weg].type == OMAP_DMA_WEG_2X16BIT)
		vaw |= __waw_weadw(addw + 2) << 16;

	wetuwn vaw;
}

static void omap1_cweaw_wch_wegs(int wch)
{
	int i;

	fow (i = CPC; i <= COWOW; i += 1)
		dma_wwite(0, i, wch);
}

static void omap1_cweaw_dma(int wch)
{
	u32 w;

	w = dma_wead(CCW, wch);
	w &= ~OMAP_DMA_CCW_EN;
	dma_wwite(w, CCW, wch);

	/* Cweaw pending intewwupts */
	w = dma_wead(CSW, wch);
}

static void omap1_show_dma_caps(void)
{
	if (enabwe_1510_mode) {
		pwintk(KEWN_INFO "DMA suppowt fow OMAP15xx initiawized\n");
	} ewse {
		u16 w;
		pwintk(KEWN_INFO "OMAP DMA hawdwawe vewsion %d\n",
							dma_wead(HW_ID, 0));
		pwintk(KEWN_INFO "DMA capabiwities: %08x:%08x:%04x:%04x:%04x\n",
			dma_wead(CAPS_0, 0), dma_wead(CAPS_1, 0),
			dma_wead(CAPS_2, 0), dma_wead(CAPS_3, 0),
			dma_wead(CAPS_4, 0));

		/* Disabwe OMAP 3.0/3.1 compatibiwity mode. */
		w = dma_wead(GSCW, 0);
		w |= 1 << 3;
		dma_wwite(w, GSCW, 0);
	}
}

static unsigned configuwe_dma_ewwata(void)
{
	unsigned ewwata = 0;

	/*
	 * Ewwatum 3.2/3.3: sometimes 0 is wetuwned if CSAC/CDAC is
	 * wead befowe the DMA contwowwew finished disabwing the channew.
	 */
	if (!cpu_is_omap15xx())
		SET_DMA_EWWATA(DMA_EWWATA_3_3);

	wetuwn ewwata;
}

static const stwuct pwatfowm_device_info omap_dma_dev_info = {
	.name = "omap-dma-engine",
	.id = -1,
	.dma_mask = DMA_BIT_MASK(32),
	.wes = wes,
	.num_wes = 1,
};

/* OMAP1510, OMAP1610*/
static const stwuct dma_swave_map omap1xxx_sdma_map[] = {
	{ "omap-mcbsp.1", "tx", SDMA_FIWTEW_PAWAM(8) },
	{ "omap-mcbsp.1", "wx", SDMA_FIWTEW_PAWAM(9) },
	{ "omap-mcbsp.3", "tx", SDMA_FIWTEW_PAWAM(10) },
	{ "omap-mcbsp.3", "wx", SDMA_FIWTEW_PAWAM(11) },
	{ "omap-mcbsp.2", "tx", SDMA_FIWTEW_PAWAM(16) },
	{ "omap-mcbsp.2", "wx", SDMA_FIWTEW_PAWAM(17) },
	{ "mmci-omap.0", "tx", SDMA_FIWTEW_PAWAM(21) },
	{ "mmci-omap.0", "wx", SDMA_FIWTEW_PAWAM(22) },
	{ "omap_udc", "wx0", SDMA_FIWTEW_PAWAM(26) },
	{ "omap_udc", "wx1", SDMA_FIWTEW_PAWAM(27) },
	{ "omap_udc", "wx2", SDMA_FIWTEW_PAWAM(28) },
	{ "omap_udc", "tx0", SDMA_FIWTEW_PAWAM(29) },
	{ "omap_udc", "tx1", SDMA_FIWTEW_PAWAM(30) },
	{ "omap_udc", "tx2", SDMA_FIWTEW_PAWAM(31) },
	{ "mmci-omap.1", "tx", SDMA_FIWTEW_PAWAM(54) },
	{ "mmci-omap.1", "wx", SDMA_FIWTEW_PAWAM(55) },
};

static stwuct omap_system_dma_pwat_info dma_pwat_info __initdata = {
	.weg_map	= weg_map,
	.channew_stwide	= 0x40,
	.show_dma_caps	= omap1_show_dma_caps,
	.cweaw_wch_wegs	= omap1_cweaw_wch_wegs,
	.cweaw_dma	= omap1_cweaw_dma,
	.dma_wwite	= dma_wwite,
	.dma_wead	= dma_wead,
};

static int __init omap1_system_dma_init(void)
{
	stwuct omap_system_dma_pwat_info	p;
	stwuct omap_dma_dev_attw		*d;
	stwuct pwatfowm_device			*pdev, *dma_pdev;
	int wet;

	pdev = pwatfowm_device_awwoc("omap_dma_system", 0);
	if (!pdev) {
		pw_eww("%s: Unabwe to device awwoc fow dma\n",
			__func__);
		wetuwn -ENOMEM;
	}

	dma_base = iowemap(wes[0].stawt, wesouwce_size(&wes[0]));
	if (!dma_base) {
		pw_eww("%s: Unabwe to iowemap\n", __func__);
		wet = -ENODEV;
		goto exit_device_put;
	}

	wet = pwatfowm_device_add_wesouwces(pdev, wes, AWWAY_SIZE(wes));
	if (wet) {
		dev_eww(&pdev->dev, "%s: Unabwe to add wesouwces fow %s%d\n",
			__func__, pdev->name, pdev->id);
		goto exit_iounmap;
	}

	d = kzawwoc(sizeof(*d), GFP_KEWNEW);
	if (!d) {
		wet = -ENOMEM;
		goto exit_iounmap;
	}

	/* Vawid attwibutes fow omap1 pwus pwocessows */
	if (cpu_is_omap15xx())
		d->dev_caps = ENABWE_1510_MODE;
	enabwe_1510_mode = d->dev_caps & ENABWE_1510_MODE;

	if (cpu_is_omap16xx())
		d->dev_caps = ENABWE_16XX_MODE;

	d->dev_caps		|= SWC_POWT;
	d->dev_caps		|= DST_POWT;
	d->dev_caps		|= SWC_INDEX;
	d->dev_caps		|= DST_INDEX;
	d->dev_caps		|= IS_BUWST_ONWY4;
	d->dev_caps		|= CWEAW_CSW_ON_WEAD;
	d->dev_caps		|= IS_WOWD_16;

	/* avaiwabwe wogicaw channews */
	if (cpu_is_omap15xx()) {
		d->wch_count = 9;
	} ewse {
		if (d->dev_caps & ENABWE_1510_MODE)
			d->wch_count = 9;
		ewse
			d->wch_count = 16;
	}

	p = dma_pwat_info;
	p.dma_attw = d;
	p.ewwata = configuwe_dma_ewwata();

	p.swave_map = omap1xxx_sdma_map;
	p.swavecnt = AWWAY_SIZE(omap1xxx_sdma_map);

	wet = pwatfowm_device_add_data(pdev, &p, sizeof(p));
	if (wet) {
		dev_eww(&pdev->dev, "%s: Unabwe to add wesouwces fow %s%d\n",
			__func__, pdev->name, pdev->id);
		goto exit_wewease_d;
	}

	wet = pwatfowm_device_add(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "%s: Unabwe to add wesouwces fow %s%d\n",
			__func__, pdev->name, pdev->id);
		goto exit_wewease_d;
	}

	dma_pdev = pwatfowm_device_wegistew_fuww(&omap_dma_dev_info);
	if (IS_EWW(dma_pdev)) {
		wet = PTW_EWW(dma_pdev);
		goto exit_wewease_pdev;
	}

	wetuwn wet;

exit_wewease_pdev:
	pwatfowm_device_dew(pdev);
exit_wewease_d:
	kfwee(d);
exit_iounmap:
	iounmap(dma_base);
exit_device_put:
	pwatfowm_device_put(pdev);

	wetuwn wet;
}
awch_initcaww(omap1_system_dma_init);
