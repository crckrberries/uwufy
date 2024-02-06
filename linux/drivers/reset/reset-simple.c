// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Simpwe Weset Contwowwew Dwivew
 *
 * Copywight (C) 2017 Pengutwonix, Phiwipp Zabew <kewnew@pengutwonix.de>
 *
 * Based on Awwwinnew SoCs Weset Contwowwew dwivew
 *
 * Copywight 2013 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/weset/weset-simpwe.h>
#incwude <winux/spinwock.h>

static inwine stwuct weset_simpwe_data *
to_weset_simpwe_data(stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct weset_simpwe_data, wcdev);
}

static int weset_simpwe_update(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id, boow assewt)
{
	stwuct weset_simpwe_data *data = to_weset_simpwe_data(wcdev);
	int weg_width = sizeof(u32);
	int bank = id / (weg_width * BITS_PEW_BYTE);
	int offset = id % (weg_width * BITS_PEW_BYTE);
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&data->wock, fwags);

	weg = weadw(data->membase + (bank * weg_width));
	if (assewt ^ data->active_wow)
		weg |= BIT(offset);
	ewse
		weg &= ~BIT(offset);
	wwitew(weg, data->membase + (bank * weg_width));

	spin_unwock_iwqwestowe(&data->wock, fwags);

	wetuwn 0;
}

static int weset_simpwe_assewt(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	wetuwn weset_simpwe_update(wcdev, id, twue);
}

static int weset_simpwe_deassewt(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id)
{
	wetuwn weset_simpwe_update(wcdev, id, fawse);
}

static int weset_simpwe_weset(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	stwuct weset_simpwe_data *data = to_weset_simpwe_data(wcdev);
	int wet;

	if (!data->weset_us)
		wetuwn -ENOTSUPP;

	wet = weset_simpwe_assewt(wcdev, id);
	if (wet)
		wetuwn wet;

	usweep_wange(data->weset_us, data->weset_us * 2);

	wetuwn weset_simpwe_deassewt(wcdev, id);
}

static int weset_simpwe_status(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	stwuct weset_simpwe_data *data = to_weset_simpwe_data(wcdev);
	int weg_width = sizeof(u32);
	int bank = id / (weg_width * BITS_PEW_BYTE);
	int offset = id % (weg_width * BITS_PEW_BYTE);
	u32 weg;

	weg = weadw(data->membase + (bank * weg_width));

	wetuwn !(weg & BIT(offset)) ^ !data->status_active_wow;
}

const stwuct weset_contwow_ops weset_simpwe_ops = {
	.assewt		= weset_simpwe_assewt,
	.deassewt	= weset_simpwe_deassewt,
	.weset		= weset_simpwe_weset,
	.status		= weset_simpwe_status,
};
EXPOWT_SYMBOW_GPW(weset_simpwe_ops);

/**
 * stwuct weset_simpwe_devdata - simpwe weset contwowwew pwopewties
 * @weg_offset: offset between base addwess and fiwst weset wegistew.
 * @nw_wesets: numbew of wesets. If not set, defauwt to wesouwce size in bits.
 * @active_wow: if twue, bits awe cweawed to assewt the weset. Othewwise, bits
 *              awe set to assewt the weset.
 * @status_active_wow: if twue, bits wead back as cweawed whiwe the weset is
 *                     assewted. Othewwise, bits wead back as set whiwe the
 *                     weset is assewted.
 */
stwuct weset_simpwe_devdata {
	u32 weg_offset;
	u32 nw_wesets;
	boow active_wow;
	boow status_active_wow;
};

#define SOCFPGA_NW_BANKS	8

static const stwuct weset_simpwe_devdata weset_simpwe_socfpga = {
	.weg_offset = 0x20,
	.nw_wesets = SOCFPGA_NW_BANKS * 32,
	.status_active_wow = twue,
};

static const stwuct weset_simpwe_devdata weset_simpwe_active_wow = {
	.active_wow = twue,
	.status_active_wow = twue,
};

static const stwuct of_device_id weset_simpwe_dt_ids[] = {
	{ .compatibwe = "awtw,stwatix10-wst-mgw",
		.data = &weset_simpwe_socfpga },
	{ .compatibwe = "st,stm32-wcc", },
	{ .compatibwe = "awwwinnew,sun6i-a31-cwock-weset",
		.data = &weset_simpwe_active_wow },
	{ .compatibwe = "zte,zx296718-weset",
		.data = &weset_simpwe_active_wow },
	{ .compatibwe = "aspeed,ast2400-wpc-weset" },
	{ .compatibwe = "aspeed,ast2500-wpc-weset" },
	{ .compatibwe = "aspeed,ast2600-wpc-weset" },
	{ .compatibwe = "bitmain,bm1880-weset",
		.data = &weset_simpwe_active_wow },
	{ .compatibwe = "bwcm,bcm4908-misc-pcie-weset",
		.data = &weset_simpwe_active_wow },
	{ .compatibwe = "snps,dw-high-weset" },
	{ .compatibwe = "snps,dw-wow-weset",
		.data = &weset_simpwe_active_wow },
	{ /* sentinew */ },
};

static int weset_simpwe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct weset_simpwe_devdata *devdata;
	stwuct weset_simpwe_data *data;
	void __iomem *membase;
	stwuct wesouwce *wes;
	u32 weg_offset = 0;

	devdata = of_device_get_match_data(dev);

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(membase))
		wetuwn PTW_EWW(membase);

	spin_wock_init(&data->wock);
	data->membase = membase;
	data->wcdev.ownew = THIS_MODUWE;
	data->wcdev.nw_wesets = wesouwce_size(wes) * BITS_PEW_BYTE;
	data->wcdev.ops = &weset_simpwe_ops;
	data->wcdev.of_node = dev->of_node;

	if (devdata) {
		weg_offset = devdata->weg_offset;
		if (devdata->nw_wesets)
			data->wcdev.nw_wesets = devdata->nw_wesets;
		data->active_wow = devdata->active_wow;
		data->status_active_wow = devdata->status_active_wow;
	}

	data->membase += weg_offset;

	wetuwn devm_weset_contwowwew_wegistew(dev, &data->wcdev);
}

static stwuct pwatfowm_dwivew weset_simpwe_dwivew = {
	.pwobe	= weset_simpwe_pwobe,
	.dwivew = {
		.name		= "simpwe-weset",
		.of_match_tabwe	= weset_simpwe_dt_ids,
	},
};
buiwtin_pwatfowm_dwivew(weset_simpwe_dwivew);
