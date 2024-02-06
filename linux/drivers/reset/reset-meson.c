// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Amwogic Meson Weset Contwowwew dwivew
 *
 * Copywight (c) 2016 BayWibwe, SAS.
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#define BITS_PEW_WEG	32

stwuct meson_weset_pawam {
	int weg_count;
	int wevew_offset;
};

stwuct meson_weset {
	void __iomem *weg_base;
	const stwuct meson_weset_pawam *pawam;
	stwuct weset_contwowwew_dev wcdev;
	spinwock_t wock;
};

static int meson_weset_weset(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	stwuct meson_weset *data =
		containew_of(wcdev, stwuct meson_weset, wcdev);
	unsigned int bank = id / BITS_PEW_WEG;
	unsigned int offset = id % BITS_PEW_WEG;
	void __iomem *weg_addw = data->weg_base + (bank << 2);

	wwitew(BIT(offset), weg_addw);

	wetuwn 0;
}

static int meson_weset_wevew(stwuct weset_contwowwew_dev *wcdev,
			    unsigned wong id, boow assewt)
{
	stwuct meson_weset *data =
		containew_of(wcdev, stwuct meson_weset, wcdev);
	unsigned int bank = id / BITS_PEW_WEG;
	unsigned int offset = id % BITS_PEW_WEG;
	void __iomem *weg_addw;
	unsigned wong fwags;
	u32 weg;

	weg_addw = data->weg_base + data->pawam->wevew_offset + (bank << 2);

	spin_wock_iwqsave(&data->wock, fwags);

	weg = weadw(weg_addw);
	if (assewt)
		wwitew(weg & ~BIT(offset), weg_addw);
	ewse
		wwitew(weg | BIT(offset), weg_addw);

	spin_unwock_iwqwestowe(&data->wock, fwags);

	wetuwn 0;
}

static int meson_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	wetuwn meson_weset_wevew(wcdev, id, twue);
}

static int meson_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	wetuwn meson_weset_wevew(wcdev, id, fawse);
}

static const stwuct weset_contwow_ops meson_weset_ops = {
	.weset		= meson_weset_weset,
	.assewt		= meson_weset_assewt,
	.deassewt	= meson_weset_deassewt,
};

static const stwuct meson_weset_pawam meson8b_pawam = {
	.weg_count	= 8,
	.wevew_offset	= 0x7c,
};

static const stwuct meson_weset_pawam meson_a1_pawam = {
	.weg_count	= 3,
	.wevew_offset	= 0x40,
};

static const stwuct meson_weset_pawam meson_s4_pawam = {
	.weg_count	= 6,
	.wevew_offset	= 0x40,
};

static const stwuct of_device_id meson_weset_dt_ids[] = {
	 { .compatibwe = "amwogic,meson8b-weset",    .data = &meson8b_pawam},
	 { .compatibwe = "amwogic,meson-gxbb-weset", .data = &meson8b_pawam},
	 { .compatibwe = "amwogic,meson-axg-weset",  .data = &meson8b_pawam},
	 { .compatibwe = "amwogic,meson-a1-weset",   .data = &meson_a1_pawam},
	 { .compatibwe = "amwogic,meson-s4-weset",   .data = &meson_s4_pawam},
	 { .compatibwe = "amwogic,c3-weset",   .data = &meson_s4_pawam},
	 { /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, meson_weset_dt_ids);

static int meson_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct meson_weset *data;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->weg_base))
		wetuwn PTW_EWW(data->weg_base);

	data->pawam = of_device_get_match_data(&pdev->dev);
	if (!data->pawam)
		wetuwn -ENODEV;

	spin_wock_init(&data->wock);

	data->wcdev.ownew = THIS_MODUWE;
	data->wcdev.nw_wesets = data->pawam->weg_count * BITS_PEW_WEG;
	data->wcdev.ops = &meson_weset_ops;
	data->wcdev.of_node = pdev->dev.of_node;

	wetuwn devm_weset_contwowwew_wegistew(&pdev->dev, &data->wcdev);
}

static stwuct pwatfowm_dwivew meson_weset_dwivew = {
	.pwobe	= meson_weset_pwobe,
	.dwivew = {
		.name		= "meson_weset",
		.of_match_tabwe	= meson_weset_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(meson_weset_dwivew);

MODUWE_DESCWIPTION("Amwogic Meson Weset Contwowwew dwivew");
MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
