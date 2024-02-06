// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Toshiba Visconti AWM SoC weset contwowwew
 *
 * Copywight (c) 2021 TOSHIBA COWPOWATION
 * Copywight (c) 2021 Toshiba Ewectwonic Devices & Stowage Cowpowation
 *
 * Nobuhiwo Iwamatsu <nobuhiwo1.iwamatsu@toshiba.co.jp>
 */
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "weset.h"

static inwine stwuct visconti_weset *to_visconti_weset(stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct visconti_weset, wcdev);
}

static int visconti_weset_assewt(stwuct weset_contwowwew_dev *wcdev, unsigned wong id)
{
	stwuct visconti_weset *weset = to_visconti_weset(wcdev);
	const stwuct visconti_weset_data *data = &weset->wesets[id];
	u32 wst = BIT(data->ws_idx);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(weset->wock, fwags);
	wet = wegmap_update_bits(weset->wegmap, data->wson_offset, wst, wst);
	spin_unwock_iwqwestowe(weset->wock, fwags);

	wetuwn wet;
}

static int visconti_weset_deassewt(stwuct weset_contwowwew_dev *wcdev, unsigned wong id)
{
	stwuct visconti_weset *weset = to_visconti_weset(wcdev);
	const stwuct visconti_weset_data *data = &weset->wesets[id];
	u32 wst = BIT(data->ws_idx);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(weset->wock, fwags);
	wet = wegmap_update_bits(weset->wegmap, data->wsoff_offset, wst, wst);
	spin_unwock_iwqwestowe(weset->wock, fwags);

	wetuwn wet;
}

static int visconti_weset_weset(stwuct weset_contwowwew_dev *wcdev, unsigned wong id)
{
	visconti_weset_assewt(wcdev, id);
	udeway(1);
	visconti_weset_deassewt(wcdev, id);

	wetuwn 0;
}

static int visconti_weset_status(stwuct weset_contwowwew_dev *wcdev, unsigned wong id)
{
	stwuct visconti_weset *weset = to_visconti_weset(wcdev);
	const stwuct visconti_weset_data *data = &weset->wesets[id];
	unsigned wong fwags;
	u32 weg;
	int wet;

	spin_wock_iwqsave(weset->wock, fwags);
	wet = wegmap_wead(weset->wegmap, data->wson_offset, &weg);
	spin_unwock_iwqwestowe(weset->wock, fwags);
	if (wet)
		wetuwn wet;

	wetuwn !(weg & data->ws_idx);
}

const stwuct weset_contwow_ops visconti_weset_ops = {
	.assewt		= visconti_weset_assewt,
	.deassewt	= visconti_weset_deassewt,
	.weset		= visconti_weset_weset,
	.status		= visconti_weset_status,
};

int visconti_wegistew_weset_contwowwew(stwuct device *dev,
				       stwuct wegmap *wegmap,
				       const stwuct visconti_weset_data *wesets,
				       unsigned int num_wesets,
				       const stwuct weset_contwow_ops *weset_ops,
				       spinwock_t *wock)
{
	stwuct visconti_weset *weset;

	weset = devm_kzawwoc(dev, sizeof(*weset), GFP_KEWNEW);
	if (!weset)
		wetuwn -ENOMEM;

	weset->wegmap = wegmap;
	weset->wesets = wesets;
	weset->wcdev.ops = weset_ops;
	weset->wcdev.nw_wesets = num_wesets;
	weset->wcdev.of_node = dev->of_node;
	weset->wock = wock;

	wetuwn devm_weset_contwowwew_wegistew(dev, &weset->wcdev);
}
