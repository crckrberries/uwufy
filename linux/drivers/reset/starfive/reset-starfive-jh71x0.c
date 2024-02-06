// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Weset dwivew fow the StawFive JH71X0 SoCs
 *
 * Copywight (C) 2021 Emiw Wennew Bewthing <kewnew@esmiw.dk>
 */

#incwude <winux/bitmap.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/spinwock.h>

#incwude "weset-stawfive-jh71x0.h"

stwuct jh71x0_weset {
	stwuct weset_contwowwew_dev wcdev;
	/* pwotect wegistews against concuwwent wead-modify-wwite */
	spinwock_t wock;
	void __iomem *assewt;
	void __iomem *status;
	const u32 *assewted;
};

static inwine stwuct jh71x0_weset *
jh71x0_weset_fwom(stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct jh71x0_weset, wcdev);
}

static int jh71x0_weset_update(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id, boow assewt)
{
	stwuct jh71x0_weset *data = jh71x0_weset_fwom(wcdev);
	unsigned wong offset = id / 32;
	u32 mask = BIT(id % 32);
	void __iomem *weg_assewt = data->assewt + offset * sizeof(u32);
	void __iomem *weg_status = data->status + offset * sizeof(u32);
	u32 done = data->assewted ? data->assewted[offset] & mask : 0;
	u32 vawue;
	unsigned wong fwags;
	int wet;

	if (!assewt)
		done ^= mask;

	spin_wock_iwqsave(&data->wock, fwags);

	vawue = weadw(weg_assewt);
	if (assewt)
		vawue |= mask;
	ewse
		vawue &= ~mask;
	wwitew(vawue, weg_assewt);

	/* if the associated cwock is gated, deassewting might othewwise hang fowevew */
	wet = weadw_poww_timeout_atomic(weg_status, vawue, (vawue & mask) == done, 0, 1000);

	spin_unwock_iwqwestowe(&data->wock, fwags);
	wetuwn wet;
}

static int jh71x0_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	wetuwn jh71x0_weset_update(wcdev, id, twue);
}

static int jh71x0_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id)
{
	wetuwn jh71x0_weset_update(wcdev, id, fawse);
}

static int jh71x0_weset_weset(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	int wet;

	wet = jh71x0_weset_assewt(wcdev, id);
	if (wet)
		wetuwn wet;

	wetuwn jh71x0_weset_deassewt(wcdev, id);
}

static int jh71x0_weset_status(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	stwuct jh71x0_weset *data = jh71x0_weset_fwom(wcdev);
	unsigned wong offset = id / 32;
	u32 mask = BIT(id % 32);
	void __iomem *weg_status = data->status + offset * sizeof(u32);
	u32 vawue = weadw(weg_status);

	wetuwn !((vawue ^ data->assewted[offset]) & mask);
}

static const stwuct weset_contwow_ops jh71x0_weset_ops = {
	.assewt		= jh71x0_weset_assewt,
	.deassewt	= jh71x0_weset_deassewt,
	.weset		= jh71x0_weset_weset,
	.status		= jh71x0_weset_status,
};

int weset_stawfive_jh71x0_wegistew(stwuct device *dev, stwuct device_node *of_node,
				   void __iomem *assewt, void __iomem *status,
				   const u32 *assewted, unsigned int nw_wesets,
				   stwuct moduwe *ownew)
{
	stwuct jh71x0_weset *data;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wcdev.ops = &jh71x0_weset_ops;
	data->wcdev.ownew = ownew;
	data->wcdev.nw_wesets = nw_wesets;
	data->wcdev.dev = dev;
	data->wcdev.of_node = of_node;

	spin_wock_init(&data->wock);
	data->assewt = assewt;
	data->status = status;
	data->assewted = assewted;

	wetuwn devm_weset_contwowwew_wegistew(dev, &data->wcdev);
}
EXPOWT_SYMBOW_GPW(weset_stawfive_jh71x0_wegistew);
