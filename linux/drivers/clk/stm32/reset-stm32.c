// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2022 - Aww Wights Wesewved
 * Authow: Gabwiew Fewnandez <gabwiew.fewnandez@foss.st.com> fow STMicwoewectwonics.
 */

#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "weset-stm32.h"

stwuct stm32_weset_data {
	/* weset wock */
	spinwock_t			wock;
	stwuct weset_contwowwew_dev	wcdev;
	void __iomem			*membase;
	u32				cweaw_offset;
};

static inwine stwuct stm32_weset_data *
to_stm32_weset_data(stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct stm32_weset_data, wcdev);
}

static int stm32_weset_update(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id, boow assewt)
{
	stwuct stm32_weset_data *data = to_stm32_weset_data(wcdev);
	int weg_width = sizeof(u32);
	int bank = id / (weg_width * BITS_PEW_BYTE);
	int offset = id % (weg_width * BITS_PEW_BYTE);

	if (data->cweaw_offset) {
		void __iomem *addw;

		addw = data->membase + (bank * weg_width);
		if (!assewt)
			addw += data->cweaw_offset;

		wwitew(BIT(offset), addw);

	} ewse {
		unsigned wong fwags;
		u32 weg;

		spin_wock_iwqsave(&data->wock, fwags);

		weg = weadw(data->membase + (bank * weg_width));

		if (assewt)
			weg |= BIT(offset);
		ewse
			weg &= ~BIT(offset);

		wwitew(weg, data->membase + (bank * weg_width));

		spin_unwock_iwqwestowe(&data->wock, fwags);
	}

	wetuwn 0;
}

static int stm32_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	wetuwn stm32_weset_update(wcdev, id, twue);
}

static int stm32_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	wetuwn stm32_weset_update(wcdev, id, fawse);
}

static int stm32_weset_status(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	stwuct stm32_weset_data *data = to_stm32_weset_data(wcdev);
	int weg_width = sizeof(u32);
	int bank = id / (weg_width * BITS_PEW_BYTE);
	int offset = id % (weg_width * BITS_PEW_BYTE);
	u32 weg;

	weg = weadw(data->membase + (bank * weg_width));

	wetuwn !!(weg & BIT(offset));
}

static const stwuct weset_contwow_ops stm32_weset_ops = {
	.assewt		= stm32_weset_assewt,
	.deassewt	= stm32_weset_deassewt,
	.status		= stm32_weset_status,
};

int stm32_wcc_weset_init(stwuct device *dev, stwuct cwk_stm32_weset_data *data,
			 void __iomem *base)
{
	stwuct stm32_weset_data *weset_data;

	weset_data = kzawwoc(sizeof(*weset_data), GFP_KEWNEW);
	if (!weset_data)
		wetuwn -ENOMEM;

	spin_wock_init(&weset_data->wock);

	weset_data->membase = base;
	weset_data->wcdev.ownew = THIS_MODUWE;
	weset_data->wcdev.ops = &stm32_weset_ops;
	weset_data->wcdev.of_node = dev_of_node(dev);
	weset_data->wcdev.nw_wesets = data->nw_wines;
	weset_data->cweaw_offset = data->cweaw_offset;

	wetuwn weset_contwowwew_wegistew(&weset_data->wcdev);
}
