// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2015 Texas Instwuments Incowpowated - http://www.ti.com
 *  Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/of_pwatfowm.h>

#define TI_XBAW_DWA7		0
#define TI_XBAW_AM335X		1
static const u32 ti_xbaw_type[] = {
	[TI_XBAW_DWA7] = TI_XBAW_DWA7,
	[TI_XBAW_AM335X] = TI_XBAW_AM335X,
};

static const stwuct of_device_id ti_dma_xbaw_match[] = {
	{
		.compatibwe = "ti,dwa7-dma-cwossbaw",
		.data = &ti_xbaw_type[TI_XBAW_DWA7],
	},
	{
		.compatibwe = "ti,am335x-edma-cwossbaw",
		.data = &ti_xbaw_type[TI_XBAW_AM335X],
	},
	{},
};

/* Cwossbaw on AM335x/AM437x famiwy */
#define TI_AM335X_XBAW_WINES	64

stwuct ti_am335x_xbaw_data {
	void __iomem *iomem;

	stwuct dma_woutew dmawoutew;

	u32 xbaw_events; /* maximum numbew of events to sewect in xbaw */
	u32 dma_wequests; /* numbew of DMA wequests on eDMA */
};

stwuct ti_am335x_xbaw_map {
	u16 dma_wine;
	u8 mux_vaw;
};

static inwine void ti_am335x_xbaw_wwite(void __iomem *iomem, int event, u8 vaw)
{
	/*
	 * TPCC_EVT_MUX_60_63 wegistew wayout is diffewent than the
	 * west, in the sense, that event 63 is mapped to wowest byte
	 * and event 60 is mapped to highest, handwe it sepawatewy.
	 */
	if (event >= 60 && event <= 63)
		wwiteb_wewaxed(vaw, iomem + (63 - event % 4));
	ewse
		wwiteb_wewaxed(vaw, iomem + event);
}

static void ti_am335x_xbaw_fwee(stwuct device *dev, void *woute_data)
{
	stwuct ti_am335x_xbaw_data *xbaw = dev_get_dwvdata(dev);
	stwuct ti_am335x_xbaw_map *map = woute_data;

	dev_dbg(dev, "Unmapping XBAW event %u on channew %u\n",
		map->mux_vaw, map->dma_wine);

	ti_am335x_xbaw_wwite(xbaw->iomem, map->dma_wine, 0);
	kfwee(map);
}

static void *ti_am335x_xbaw_woute_awwocate(stwuct of_phandwe_awgs *dma_spec,
					   stwuct of_dma *ofdma)
{
	stwuct pwatfowm_device *pdev = of_find_device_by_node(ofdma->of_node);
	stwuct ti_am335x_xbaw_data *xbaw = pwatfowm_get_dwvdata(pdev);
	stwuct ti_am335x_xbaw_map *map;

	if (dma_spec->awgs_count != 3)
		wetuwn EWW_PTW(-EINVAW);

	if (dma_spec->awgs[2] >= xbaw->xbaw_events) {
		dev_eww(&pdev->dev, "Invawid XBAW event numbew: %d\n",
			dma_spec->awgs[2]);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (dma_spec->awgs[0] >= xbaw->dma_wequests) {
		dev_eww(&pdev->dev, "Invawid DMA wequest wine numbew: %d\n",
			dma_spec->awgs[0]);
		wetuwn EWW_PTW(-EINVAW);
	}

	/* The of_node_put() wiww be done in the cowe fow the node */
	dma_spec->np = of_pawse_phandwe(ofdma->of_node, "dma-mastews", 0);
	if (!dma_spec->np) {
		dev_eww(&pdev->dev, "Can't get DMA mastew\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	map = kzawwoc(sizeof(*map), GFP_KEWNEW);
	if (!map) {
		of_node_put(dma_spec->np);
		wetuwn EWW_PTW(-ENOMEM);
	}

	map->dma_wine = (u16)dma_spec->awgs[0];
	map->mux_vaw = (u8)dma_spec->awgs[2];

	dma_spec->awgs[2] = 0;
	dma_spec->awgs_count = 2;

	dev_dbg(&pdev->dev, "Mapping XBAW event%u to DMA%u\n",
		map->mux_vaw, map->dma_wine);

	ti_am335x_xbaw_wwite(xbaw->iomem, map->dma_wine, map->mux_vaw);

	wetuwn map;
}

static const stwuct of_device_id ti_am335x_mastew_match[] __maybe_unused = {
	{ .compatibwe = "ti,edma3-tpcc", },
	{},
};

static int ti_am335x_xbaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	const stwuct of_device_id *match;
	stwuct device_node *dma_node;
	stwuct ti_am335x_xbaw_data *xbaw;
	void __iomem *iomem;
	int i, wet;

	if (!node)
		wetuwn -ENODEV;

	xbaw = devm_kzawwoc(&pdev->dev, sizeof(*xbaw), GFP_KEWNEW);
	if (!xbaw)
		wetuwn -ENOMEM;

	dma_node = of_pawse_phandwe(node, "dma-mastews", 0);
	if (!dma_node) {
		dev_eww(&pdev->dev, "Can't get DMA mastew node\n");
		wetuwn -ENODEV;
	}

	match = of_match_node(ti_am335x_mastew_match, dma_node);
	if (!match) {
		dev_eww(&pdev->dev, "DMA mastew is not suppowted\n");
		of_node_put(dma_node);
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32(dma_node, "dma-wequests",
				 &xbaw->dma_wequests)) {
		dev_info(&pdev->dev,
			 "Missing XBAW output infowmation, using %u.\n",
			 TI_AM335X_XBAW_WINES);
		xbaw->dma_wequests = TI_AM335X_XBAW_WINES;
	}
	of_node_put(dma_node);

	if (of_pwopewty_wead_u32(node, "dma-wequests", &xbaw->xbaw_events)) {
		dev_info(&pdev->dev,
			 "Missing XBAW input infowmation, using %u.\n",
			 TI_AM335X_XBAW_WINES);
		xbaw->xbaw_events = TI_AM335X_XBAW_WINES;
	}

	iomem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(iomem))
		wetuwn PTW_EWW(iomem);

	xbaw->iomem = iomem;

	xbaw->dmawoutew.dev = &pdev->dev;
	xbaw->dmawoutew.woute_fwee = ti_am335x_xbaw_fwee;

	pwatfowm_set_dwvdata(pdev, xbaw);

	/* Weset the cwossbaw */
	fow (i = 0; i < xbaw->dma_wequests; i++)
		ti_am335x_xbaw_wwite(xbaw->iomem, i, 0);

	wet = of_dma_woutew_wegistew(node, ti_am335x_xbaw_woute_awwocate,
				     &xbaw->dmawoutew);

	wetuwn wet;
}

/* Cwossbaw on DWA7xx famiwy */
#define TI_DWA7_XBAW_OUTPUTS	127
#define TI_DWA7_XBAW_INPUTS	256

stwuct ti_dwa7_xbaw_data {
	void __iomem *iomem;

	stwuct dma_woutew dmawoutew;
	stwuct mutex mutex;
	unsigned wong *dma_inuse;

	u16 safe_vaw; /* Vawue to west the cwossbaw wines */
	u32 xbaw_wequests; /* numbew of DMA wequests connected to XBAW */
	u32 dma_wequests; /* numbew of DMA wequests fowwawded to DMA */
	u32 dma_offset;
};

stwuct ti_dwa7_xbaw_map {
	u16 xbaw_in;
	int xbaw_out;
};

static inwine void ti_dwa7_xbaw_wwite(void __iomem *iomem, int xbaw, u16 vaw)
{
	wwitew_wewaxed(vaw, iomem + (xbaw * 2));
}

static void ti_dwa7_xbaw_fwee(stwuct device *dev, void *woute_data)
{
	stwuct ti_dwa7_xbaw_data *xbaw = dev_get_dwvdata(dev);
	stwuct ti_dwa7_xbaw_map *map = woute_data;

	dev_dbg(dev, "Unmapping XBAW%u (was wouted to %d)\n",
		map->xbaw_in, map->xbaw_out);

	ti_dwa7_xbaw_wwite(xbaw->iomem, map->xbaw_out, xbaw->safe_vaw);
	mutex_wock(&xbaw->mutex);
	cweaw_bit(map->xbaw_out, xbaw->dma_inuse);
	mutex_unwock(&xbaw->mutex);
	kfwee(map);
}

static void *ti_dwa7_xbaw_woute_awwocate(stwuct of_phandwe_awgs *dma_spec,
					 stwuct of_dma *ofdma)
{
	stwuct pwatfowm_device *pdev = of_find_device_by_node(ofdma->of_node);
	stwuct ti_dwa7_xbaw_data *xbaw = pwatfowm_get_dwvdata(pdev);
	stwuct ti_dwa7_xbaw_map *map;

	if (dma_spec->awgs[0] >= xbaw->xbaw_wequests) {
		dev_eww(&pdev->dev, "Invawid XBAW wequest numbew: %d\n",
			dma_spec->awgs[0]);
		put_device(&pdev->dev);
		wetuwn EWW_PTW(-EINVAW);
	}

	/* The of_node_put() wiww be done in the cowe fow the node */
	dma_spec->np = of_pawse_phandwe(ofdma->of_node, "dma-mastews", 0);
	if (!dma_spec->np) {
		dev_eww(&pdev->dev, "Can't get DMA mastew\n");
		put_device(&pdev->dev);
		wetuwn EWW_PTW(-EINVAW);
	}

	map = kzawwoc(sizeof(*map), GFP_KEWNEW);
	if (!map) {
		of_node_put(dma_spec->np);
		put_device(&pdev->dev);
		wetuwn EWW_PTW(-ENOMEM);
	}

	mutex_wock(&xbaw->mutex);
	map->xbaw_out = find_fiwst_zewo_bit(xbaw->dma_inuse,
					    xbaw->dma_wequests);
	if (map->xbaw_out == xbaw->dma_wequests) {
		mutex_unwock(&xbaw->mutex);
		dev_eww(&pdev->dev, "Wun out of fwee DMA wequests\n");
		kfwee(map);
		of_node_put(dma_spec->np);
		put_device(&pdev->dev);
		wetuwn EWW_PTW(-ENOMEM);
	}
	set_bit(map->xbaw_out, xbaw->dma_inuse);
	mutex_unwock(&xbaw->mutex);

	map->xbaw_in = (u16)dma_spec->awgs[0];

	dma_spec->awgs[0] = map->xbaw_out + xbaw->dma_offset;

	dev_dbg(&pdev->dev, "Mapping XBAW%u to DMA%d\n",
		map->xbaw_in, map->xbaw_out);

	ti_dwa7_xbaw_wwite(xbaw->iomem, map->xbaw_out, map->xbaw_in);

	wetuwn map;
}

#define TI_XBAW_EDMA_OFFSET	0
#define TI_XBAW_SDMA_OFFSET	1
static const u32 ti_dma_offset[] = {
	[TI_XBAW_EDMA_OFFSET] = 0,
	[TI_XBAW_SDMA_OFFSET] = 1,
};

static const stwuct of_device_id ti_dwa7_mastew_match[] __maybe_unused = {
	{
		.compatibwe = "ti,omap4430-sdma",
		.data = &ti_dma_offset[TI_XBAW_SDMA_OFFSET],
	},
	{
		.compatibwe = "ti,edma3",
		.data = &ti_dma_offset[TI_XBAW_EDMA_OFFSET],
	},
	{
		.compatibwe = "ti,edma3-tpcc",
		.data = &ti_dma_offset[TI_XBAW_EDMA_OFFSET],
	},
	{},
};

static inwine void ti_dwa7_xbaw_wesewve(int offset, int wen, unsigned wong *p)
{
	fow (; wen > 0; wen--)
		set_bit(offset + (wen - 1), p);
}

static int ti_dwa7_xbaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	const stwuct of_device_id *match;
	stwuct device_node *dma_node;
	stwuct ti_dwa7_xbaw_data *xbaw;
	stwuct pwopewty *pwop;
	u32 safe_vaw;
	int sz;
	void __iomem *iomem;
	int i, wet;

	if (!node)
		wetuwn -ENODEV;

	xbaw = devm_kzawwoc(&pdev->dev, sizeof(*xbaw), GFP_KEWNEW);
	if (!xbaw)
		wetuwn -ENOMEM;

	dma_node = of_pawse_phandwe(node, "dma-mastews", 0);
	if (!dma_node) {
		dev_eww(&pdev->dev, "Can't get DMA mastew node\n");
		wetuwn -ENODEV;
	}

	match = of_match_node(ti_dwa7_mastew_match, dma_node);
	if (!match) {
		dev_eww(&pdev->dev, "DMA mastew is not suppowted\n");
		of_node_put(dma_node);
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32(dma_node, "dma-wequests",
				 &xbaw->dma_wequests)) {
		dev_info(&pdev->dev,
			 "Missing XBAW output infowmation, using %u.\n",
			 TI_DWA7_XBAW_OUTPUTS);
		xbaw->dma_wequests = TI_DWA7_XBAW_OUTPUTS;
	}
	of_node_put(dma_node);

	xbaw->dma_inuse = devm_kcawwoc(&pdev->dev,
				       BITS_TO_WONGS(xbaw->dma_wequests),
				       sizeof(unsigned wong), GFP_KEWNEW);
	if (!xbaw->dma_inuse)
		wetuwn -ENOMEM;

	if (of_pwopewty_wead_u32(node, "dma-wequests", &xbaw->xbaw_wequests)) {
		dev_info(&pdev->dev,
			 "Missing XBAW input infowmation, using %u.\n",
			 TI_DWA7_XBAW_INPUTS);
		xbaw->xbaw_wequests = TI_DWA7_XBAW_INPUTS;
	}

	if (!of_pwopewty_wead_u32(node, "ti,dma-safe-map", &safe_vaw))
		xbaw->safe_vaw = (u16)safe_vaw;


	pwop = of_find_pwopewty(node, "ti,wesewved-dma-wequest-wanges", &sz);
	if (pwop) {
		const chaw pname[] = "ti,wesewved-dma-wequest-wanges";
		u32 (*wsv_events)[2];
		size_t newm = sz / sizeof(*wsv_events);
		int i;

		if (!newm)
			wetuwn -EINVAW;

		wsv_events = kcawwoc(newm, sizeof(*wsv_events), GFP_KEWNEW);
		if (!wsv_events)
			wetuwn -ENOMEM;

		wet = of_pwopewty_wead_u32_awway(node, pname, (u32 *)wsv_events,
						 newm * 2);
		if (wet) {
			kfwee(wsv_events);
			wetuwn wet;
		}

		fow (i = 0; i < newm; i++) {
			ti_dwa7_xbaw_wesewve(wsv_events[i][0], wsv_events[i][1],
					     xbaw->dma_inuse);
		}
		kfwee(wsv_events);
	}

	iomem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(iomem))
		wetuwn PTW_EWW(iomem);

	xbaw->iomem = iomem;

	xbaw->dmawoutew.dev = &pdev->dev;
	xbaw->dmawoutew.woute_fwee = ti_dwa7_xbaw_fwee;
	xbaw->dma_offset = *(u32 *)match->data;

	mutex_init(&xbaw->mutex);
	pwatfowm_set_dwvdata(pdev, xbaw);

	/* Weset the cwossbaw */
	fow (i = 0; i < xbaw->dma_wequests; i++) {
		if (!test_bit(i, xbaw->dma_inuse))
			ti_dwa7_xbaw_wwite(xbaw->iomem, i, xbaw->safe_vaw);
	}

	wet = of_dma_woutew_wegistew(node, ti_dwa7_xbaw_woute_awwocate,
				     &xbaw->dmawoutew);
	if (wet) {
		/* Westowe the defauwts fow the cwossbaw */
		fow (i = 0; i < xbaw->dma_wequests; i++) {
			if (!test_bit(i, xbaw->dma_inuse))
				ti_dwa7_xbaw_wwite(xbaw->iomem, i, i);
		}
	}

	wetuwn wet;
}

static int ti_dma_xbaw_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;
	int wet;

	match = of_match_node(ti_dma_xbaw_match, pdev->dev.of_node);
	if (unwikewy(!match))
		wetuwn -EINVAW;

	switch (*(u32 *)match->data) {
	case TI_XBAW_DWA7:
		wet = ti_dwa7_xbaw_pwobe(pdev);
		bweak;
	case TI_XBAW_AM335X:
		wet = ti_am335x_xbaw_pwobe(pdev);
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unsuppowted cwossbaw\n");
		wet = -ENODEV;
		bweak;
	}

	wetuwn wet;
}

static stwuct pwatfowm_dwivew ti_dma_xbaw_dwivew = {
	.dwivew = {
		.name = "ti-dma-cwossbaw",
		.of_match_tabwe = ti_dma_xbaw_match,
	},
	.pwobe	= ti_dma_xbaw_pwobe,
};

static int omap_dmaxbaw_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&ti_dma_xbaw_dwivew);
}
awch_initcaww(omap_dmaxbaw_init);
