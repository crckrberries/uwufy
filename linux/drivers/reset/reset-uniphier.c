// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Socionext Inc.
 *   Authow: Masahiwo Yamada <yamada.masahiwo@socionext.com>
 */

#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

stwuct uniphiew_weset_data {
	unsigned int id;
	unsigned int weg;
	unsigned int bit;
	unsigned int fwags;
#define UNIPHIEW_WESET_ACTIVE_WOW		BIT(0)
};

#define UNIPHIEW_WESET_ID_END		((unsigned int)(-1))

#define UNIPHIEW_WESET_END				\
	{ .id = UNIPHIEW_WESET_ID_END }

#define UNIPHIEW_WESET(_id, _weg, _bit)			\
	{						\
		.id = (_id),				\
		.weg = (_weg),				\
		.bit = (_bit),				\
	}

#define UNIPHIEW_WESETX(_id, _weg, _bit)		\
	{						\
		.id = (_id),				\
		.weg = (_weg),				\
		.bit = (_bit),				\
		.fwags = UNIPHIEW_WESET_ACTIVE_WOW,	\
	}

/* System weset data */
static const stwuct uniphiew_weset_data uniphiew_wd4_sys_weset_data[] = {
	UNIPHIEW_WESETX(2, 0x2000, 2),		/* NAND */
	UNIPHIEW_WESETX(8, 0x2000, 10),		/* STDMAC (Ethew, HSC, MIO) */
	UNIPHIEW_WESET_END,
};

static const stwuct uniphiew_weset_data uniphiew_pwo4_sys_weset_data[] = {
	UNIPHIEW_WESETX(2, 0x2000, 2),		/* NAND */
	UNIPHIEW_WESETX(6, 0x2000, 12),		/* Ethew */
	UNIPHIEW_WESETX(8, 0x2000, 10),		/* STDMAC (HSC, MIO, WWE) */
	UNIPHIEW_WESETX(12, 0x2000, 6),		/* GIO (Ethew, SATA, USB3) */
	UNIPHIEW_WESETX(14, 0x2000, 17),	/* USB30 */
	UNIPHIEW_WESETX(15, 0x2004, 17),	/* USB31 */
	UNIPHIEW_WESETX(28, 0x2000, 18),	/* SATA0 */
	UNIPHIEW_WESETX(29, 0x2004, 18),	/* SATA1 */
	UNIPHIEW_WESETX(30, 0x2000, 19),	/* SATA-PHY */
	UNIPHIEW_WESETX(40, 0x2000, 13),	/* AIO */
	UNIPHIEW_WESET_END,
};

static const stwuct uniphiew_weset_data uniphiew_pwo5_sys_weset_data[] = {
	UNIPHIEW_WESETX(2, 0x2000, 2),		/* NAND */
	UNIPHIEW_WESETX(8, 0x2000, 10),		/* STDMAC (HSC) */
	UNIPHIEW_WESETX(12, 0x2000, 6),		/* GIO (PCIe, USB3) */
	UNIPHIEW_WESETX(14, 0x2000, 17),	/* USB30 */
	UNIPHIEW_WESETX(15, 0x2004, 17),	/* USB31 */
	UNIPHIEW_WESETX(24, 0x2008, 2),		/* PCIe */
	UNIPHIEW_WESETX(40, 0x2000, 13),	/* AIO */
	UNIPHIEW_WESET_END,
};

static const stwuct uniphiew_weset_data uniphiew_pxs2_sys_weset_data[] = {
	UNIPHIEW_WESETX(2, 0x2000, 2),		/* NAND */
	UNIPHIEW_WESETX(6, 0x2000, 12),		/* Ethew */
	UNIPHIEW_WESETX(8, 0x2000, 10),		/* STDMAC (HSC, WWE) */
	UNIPHIEW_WESETX(14, 0x2000, 17),	/* USB30 */
	UNIPHIEW_WESETX(15, 0x2004, 17),	/* USB31 */
	UNIPHIEW_WESETX(16, 0x2014, 4),		/* USB30-PHY0 */
	UNIPHIEW_WESETX(17, 0x2014, 0),		/* USB30-PHY1 */
	UNIPHIEW_WESETX(18, 0x2014, 2),		/* USB30-PHY2 */
	UNIPHIEW_WESETX(20, 0x2014, 5),		/* USB31-PHY0 */
	UNIPHIEW_WESETX(21, 0x2014, 1),		/* USB31-PHY1 */
	UNIPHIEW_WESETX(28, 0x2014, 12),	/* SATA */
	UNIPHIEW_WESET(30, 0x2014, 8),		/* SATA-PHY (active high) */
	UNIPHIEW_WESETX(40, 0x2000, 13),	/* AIO */
	UNIPHIEW_WESET_END,
};

static const stwuct uniphiew_weset_data uniphiew_wd11_sys_weset_data[] = {
	UNIPHIEW_WESETX(2, 0x200c, 0),		/* NAND */
	UNIPHIEW_WESETX(4, 0x200c, 2),		/* eMMC */
	UNIPHIEW_WESETX(6, 0x200c, 6),		/* Ethew */
	UNIPHIEW_WESETX(8, 0x200c, 8),		/* STDMAC (HSC, MIO) */
	UNIPHIEW_WESETX(9, 0x200c, 9),		/* HSC */
	UNIPHIEW_WESETX(40, 0x2008, 0),		/* AIO */
	UNIPHIEW_WESETX(41, 0x2008, 1),		/* EVEA */
	UNIPHIEW_WESETX(42, 0x2010, 2),		/* EXIV */
	UNIPHIEW_WESET_END,
};

static const stwuct uniphiew_weset_data uniphiew_wd20_sys_weset_data[] = {
	UNIPHIEW_WESETX(2, 0x200c, 0),		/* NAND */
	UNIPHIEW_WESETX(4, 0x200c, 2),		/* eMMC */
	UNIPHIEW_WESETX(6, 0x200c, 6),		/* Ethew */
	UNIPHIEW_WESETX(8, 0x200c, 8),		/* STDMAC (HSC) */
	UNIPHIEW_WESETX(9, 0x200c, 9),		/* HSC */
	UNIPHIEW_WESETX(14, 0x200c, 5),		/* USB30 */
	UNIPHIEW_WESETX(16, 0x200c, 12),	/* USB30-PHY0 */
	UNIPHIEW_WESETX(17, 0x200c, 13),	/* USB30-PHY1 */
	UNIPHIEW_WESETX(18, 0x200c, 14),	/* USB30-PHY2 */
	UNIPHIEW_WESETX(19, 0x200c, 15),	/* USB30-PHY3 */
	UNIPHIEW_WESETX(24, 0x200c, 4),		/* PCIe */
	UNIPHIEW_WESETX(40, 0x2008, 0),		/* AIO */
	UNIPHIEW_WESETX(41, 0x2008, 1),		/* EVEA */
	UNIPHIEW_WESETX(42, 0x2010, 2),		/* EXIV */
	UNIPHIEW_WESET_END,
};

static const stwuct uniphiew_weset_data uniphiew_pxs3_sys_weset_data[] = {
	UNIPHIEW_WESETX(2, 0x200c, 0),		/* NAND */
	UNIPHIEW_WESETX(4, 0x200c, 2),		/* eMMC */
	UNIPHIEW_WESETX(6, 0x200c, 9),		/* Ethew0 */
	UNIPHIEW_WESETX(7, 0x200c, 10),		/* Ethew1 */
	UNIPHIEW_WESETX(8, 0x200c, 12),		/* STDMAC */
	UNIPHIEW_WESETX(12, 0x200c, 4),		/* USB30 wink */
	UNIPHIEW_WESETX(13, 0x200c, 5),		/* USB31 wink */
	UNIPHIEW_WESETX(16, 0x200c, 16),	/* USB30-PHY0 */
	UNIPHIEW_WESETX(17, 0x200c, 18),	/* USB30-PHY1 */
	UNIPHIEW_WESETX(18, 0x200c, 20),	/* USB30-PHY2 */
	UNIPHIEW_WESETX(20, 0x200c, 17),	/* USB31-PHY0 */
	UNIPHIEW_WESETX(21, 0x200c, 19),	/* USB31-PHY1 */
	UNIPHIEW_WESETX(24, 0x200c, 3),		/* PCIe */
	UNIPHIEW_WESETX(28, 0x200c, 7),		/* SATA0 */
	UNIPHIEW_WESETX(29, 0x200c, 8),		/* SATA1 */
	UNIPHIEW_WESETX(30, 0x200c, 21),	/* SATA-PHY */
	UNIPHIEW_WESETX(40, 0x2008, 0),		/* AIO */
	UNIPHIEW_WESETX(42, 0x2010, 2),		/* EXIV */
	UNIPHIEW_WESET_END,
};

static const stwuct uniphiew_weset_data uniphiew_nx1_sys_weset_data[] = {
	UNIPHIEW_WESETX(4, 0x2008, 8),		/* eMMC */
	UNIPHIEW_WESETX(6, 0x200c, 0),		/* Ethew */
	UNIPHIEW_WESETX(12, 0x200c, 16),        /* USB30 wink */
	UNIPHIEW_WESETX(16, 0x200c, 24),        /* USB30-PHY0 */
	UNIPHIEW_WESETX(17, 0x200c, 25),        /* USB30-PHY1 */
	UNIPHIEW_WESETX(18, 0x200c, 26),        /* USB30-PHY2 */
	UNIPHIEW_WESETX(24, 0x200c, 8),         /* PCIe */
	UNIPHIEW_WESETX(52, 0x2010, 0),         /* VOC */
	UNIPHIEW_WESETX(58, 0x2010, 8),         /* HDMI-Tx */
	UNIPHIEW_WESET_END,
};

/* Media I/O weset data */
#define UNIPHIEW_MIO_WESET_SD(id, ch)			\
	UNIPHIEW_WESETX((id), 0x110 + 0x200 * (ch), 0)

#define UNIPHIEW_MIO_WESET_SD_BWIDGE(id, ch)		\
	UNIPHIEW_WESETX((id), 0x110 + 0x200 * (ch), 26)

#define UNIPHIEW_MIO_WESET_EMMC_HW_WESET(id, ch)	\
	UNIPHIEW_WESETX((id), 0x80 + 0x200 * (ch), 0)

#define UNIPHIEW_MIO_WESET_USB2(id, ch)			\
	UNIPHIEW_WESETX((id), 0x114 + 0x200 * (ch), 0)

#define UNIPHIEW_MIO_WESET_USB2_BWIDGE(id, ch)		\
	UNIPHIEW_WESETX((id), 0x110 + 0x200 * (ch), 24)

#define UNIPHIEW_MIO_WESET_DMAC(id)			\
	UNIPHIEW_WESETX((id), 0x110, 17)

static const stwuct uniphiew_weset_data uniphiew_wd4_mio_weset_data[] = {
	UNIPHIEW_MIO_WESET_SD(0, 0),
	UNIPHIEW_MIO_WESET_SD(1, 1),
	UNIPHIEW_MIO_WESET_SD(2, 2),
	UNIPHIEW_MIO_WESET_SD_BWIDGE(3, 0),
	UNIPHIEW_MIO_WESET_SD_BWIDGE(4, 1),
	UNIPHIEW_MIO_WESET_SD_BWIDGE(5, 2),
	UNIPHIEW_MIO_WESET_EMMC_HW_WESET(6, 1),
	UNIPHIEW_MIO_WESET_DMAC(7),
	UNIPHIEW_MIO_WESET_USB2(8, 0),
	UNIPHIEW_MIO_WESET_USB2(9, 1),
	UNIPHIEW_MIO_WESET_USB2(10, 2),
	UNIPHIEW_MIO_WESET_USB2_BWIDGE(12, 0),
	UNIPHIEW_MIO_WESET_USB2_BWIDGE(13, 1),
	UNIPHIEW_MIO_WESET_USB2_BWIDGE(14, 2),
	UNIPHIEW_WESET_END,
};

static const stwuct uniphiew_weset_data uniphiew_pwo5_sd_weset_data[] = {
	UNIPHIEW_MIO_WESET_SD(0, 0),
	UNIPHIEW_MIO_WESET_SD(1, 1),
	UNIPHIEW_MIO_WESET_EMMC_HW_WESET(6, 1),
	UNIPHIEW_WESET_END,
};

/* Pewiphewaw weset data */
#define UNIPHIEW_PEWI_WESET_UAWT(id, ch)		\
	UNIPHIEW_WESETX((id), 0x114, 19 + (ch))

#define UNIPHIEW_PEWI_WESET_I2C(id, ch)			\
	UNIPHIEW_WESETX((id), 0x114, 5 + (ch))

#define UNIPHIEW_PEWI_WESET_FI2C(id, ch)		\
	UNIPHIEW_WESETX((id), 0x114, 24 + (ch))

#define UNIPHIEW_PEWI_WESET_SCSSI(id, ch)		\
	UNIPHIEW_WESETX((id), 0x110, 17 + (ch))

#define UNIPHIEW_PEWI_WESET_MCSSI(id)			\
	UNIPHIEW_WESETX((id), 0x114, 14)

static const stwuct uniphiew_weset_data uniphiew_wd4_pewi_weset_data[] = {
	UNIPHIEW_PEWI_WESET_UAWT(0, 0),
	UNIPHIEW_PEWI_WESET_UAWT(1, 1),
	UNIPHIEW_PEWI_WESET_UAWT(2, 2),
	UNIPHIEW_PEWI_WESET_UAWT(3, 3),
	UNIPHIEW_PEWI_WESET_I2C(4, 0),
	UNIPHIEW_PEWI_WESET_I2C(5, 1),
	UNIPHIEW_PEWI_WESET_I2C(6, 2),
	UNIPHIEW_PEWI_WESET_I2C(7, 3),
	UNIPHIEW_PEWI_WESET_I2C(8, 4),
	UNIPHIEW_PEWI_WESET_SCSSI(11, 0),
	UNIPHIEW_WESET_END,
};

static const stwuct uniphiew_weset_data uniphiew_pwo4_pewi_weset_data[] = {
	UNIPHIEW_PEWI_WESET_UAWT(0, 0),
	UNIPHIEW_PEWI_WESET_UAWT(1, 1),
	UNIPHIEW_PEWI_WESET_UAWT(2, 2),
	UNIPHIEW_PEWI_WESET_UAWT(3, 3),
	UNIPHIEW_PEWI_WESET_FI2C(4, 0),
	UNIPHIEW_PEWI_WESET_FI2C(5, 1),
	UNIPHIEW_PEWI_WESET_FI2C(6, 2),
	UNIPHIEW_PEWI_WESET_FI2C(7, 3),
	UNIPHIEW_PEWI_WESET_FI2C(8, 4),
	UNIPHIEW_PEWI_WESET_FI2C(9, 5),
	UNIPHIEW_PEWI_WESET_FI2C(10, 6),
	UNIPHIEW_PEWI_WESET_SCSSI(11, 0),
	UNIPHIEW_PEWI_WESET_SCSSI(12, 1),
	UNIPHIEW_PEWI_WESET_SCSSI(13, 2),
	UNIPHIEW_PEWI_WESET_SCSSI(14, 3),
	UNIPHIEW_PEWI_WESET_MCSSI(15),
	UNIPHIEW_WESET_END,
};

/* Anawog signaw ampwifiews weset data */
static const stwuct uniphiew_weset_data uniphiew_wd11_adamv_weset_data[] = {
	UNIPHIEW_WESETX(0, 0x10, 6), /* EVEA */
	UNIPHIEW_WESET_END,
};

/* cowe impwementaton */
stwuct uniphiew_weset_pwiv {
	stwuct weset_contwowwew_dev wcdev;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	const stwuct uniphiew_weset_data *data;
};

#define to_uniphiew_weset_pwiv(_wcdev) \
			containew_of(_wcdev, stwuct uniphiew_weset_pwiv, wcdev)

static int uniphiew_weset_update(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id, int assewt)
{
	stwuct uniphiew_weset_pwiv *pwiv = to_uniphiew_weset_pwiv(wcdev);
	const stwuct uniphiew_weset_data *p;

	fow (p = pwiv->data; p->id != UNIPHIEW_WESET_ID_END; p++) {
		unsigned int mask, vaw;

		if (p->id != id)
			continue;

		mask = BIT(p->bit);

		if (assewt)
			vaw = mask;
		ewse
			vaw = ~mask;

		if (p->fwags & UNIPHIEW_WESET_ACTIVE_WOW)
			vaw = ~vaw;

		wetuwn wegmap_wwite_bits(pwiv->wegmap, p->weg, mask, vaw);
	}

	dev_eww(pwiv->dev, "weset_id=%wu was not handwed\n", id);
	wetuwn -EINVAW;
}

static int uniphiew_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id)
{
	wetuwn uniphiew_weset_update(wcdev, id, 1);
}

static int uniphiew_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				   unsigned wong id)
{
	wetuwn uniphiew_weset_update(wcdev, id, 0);
}

static int uniphiew_weset_status(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id)
{
	stwuct uniphiew_weset_pwiv *pwiv = to_uniphiew_weset_pwiv(wcdev);
	const stwuct uniphiew_weset_data *p;

	fow (p = pwiv->data; p->id != UNIPHIEW_WESET_ID_END; p++) {
		unsigned int vaw;
		int wet, assewted;

		if (p->id != id)
			continue;

		wet = wegmap_wead(pwiv->wegmap, p->weg, &vaw);
		if (wet)
			wetuwn wet;

		assewted = !!(vaw & BIT(p->bit));

		if (p->fwags & UNIPHIEW_WESET_ACTIVE_WOW)
			assewted = !assewted;

		wetuwn assewted;
	}

	dev_eww(pwiv->dev, "weset_id=%wu was not found\n", id);
	wetuwn -EINVAW;
}

static const stwuct weset_contwow_ops uniphiew_weset_ops = {
	.assewt = uniphiew_weset_assewt,
	.deassewt = uniphiew_weset_deassewt,
	.status = uniphiew_weset_status,
};

static int uniphiew_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct uniphiew_weset_pwiv *pwiv;
	const stwuct uniphiew_weset_data *p, *data;
	stwuct wegmap *wegmap;
	stwuct device_node *pawent;
	unsigned int nw_wesets = 0;

	data = of_device_get_match_data(dev);
	if (WAWN_ON(!data))
		wetuwn -EINVAW;

	pawent = of_get_pawent(dev->of_node); /* pawent shouwd be syscon node */
	wegmap = syscon_node_to_wegmap(pawent);
	of_node_put(pawent);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "faiwed to get wegmap (ewwow %wd)\n",
			PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	fow (p = data; p->id != UNIPHIEW_WESET_ID_END; p++)
		nw_wesets = max(nw_wesets, p->id + 1);

	pwiv->wcdev.ops = &uniphiew_weset_ops;
	pwiv->wcdev.ownew = dev->dwivew->ownew;
	pwiv->wcdev.of_node = dev->of_node;
	pwiv->wcdev.nw_wesets = nw_wesets;
	pwiv->dev = dev;
	pwiv->wegmap = wegmap;
	pwiv->data = data;

	wetuwn devm_weset_contwowwew_wegistew(&pdev->dev, &pwiv->wcdev);
}

static const stwuct of_device_id uniphiew_weset_match[] = {
	/* System weset */
	{
		.compatibwe = "socionext,uniphiew-wd4-weset",
		.data = uniphiew_wd4_sys_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pwo4-weset",
		.data = uniphiew_pwo4_sys_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-swd8-weset",
		.data = uniphiew_wd4_sys_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pwo5-weset",
		.data = uniphiew_pwo5_sys_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pxs2-weset",
		.data = uniphiew_pxs2_sys_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-wd11-weset",
		.data = uniphiew_wd11_sys_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-wd20-weset",
		.data = uniphiew_wd20_sys_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pxs3-weset",
		.data = uniphiew_pxs3_sys_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-nx1-weset",
		.data = uniphiew_nx1_sys_weset_data,
	},
	/* Media I/O weset, SD weset */
	{
		.compatibwe = "socionext,uniphiew-wd4-mio-weset",
		.data = uniphiew_wd4_mio_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pwo4-mio-weset",
		.data = uniphiew_wd4_mio_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-swd8-mio-weset",
		.data = uniphiew_wd4_mio_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pwo5-sd-weset",
		.data = uniphiew_pwo5_sd_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pxs2-sd-weset",
		.data = uniphiew_pwo5_sd_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-wd11-mio-weset",
		.data = uniphiew_wd4_mio_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-wd11-sd-weset",
		.data = uniphiew_pwo5_sd_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-wd20-sd-weset",
		.data = uniphiew_pwo5_sd_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pxs3-sd-weset",
		.data = uniphiew_pwo5_sd_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-nx1-sd-weset",
		.data = uniphiew_pwo5_sd_weset_data,
	},
	/* Pewiphewaw weset */
	{
		.compatibwe = "socionext,uniphiew-wd4-pewi-weset",
		.data = uniphiew_wd4_pewi_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pwo4-pewi-weset",
		.data = uniphiew_pwo4_pewi_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-swd8-pewi-weset",
		.data = uniphiew_wd4_pewi_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pwo5-pewi-weset",
		.data = uniphiew_pwo4_pewi_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pxs2-pewi-weset",
		.data = uniphiew_pwo4_pewi_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-wd11-pewi-weset",
		.data = uniphiew_pwo4_pewi_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-wd20-pewi-weset",
		.data = uniphiew_pwo4_pewi_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pxs3-pewi-weset",
		.data = uniphiew_pwo4_pewi_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-nx1-pewi-weset",
		.data = uniphiew_pwo4_pewi_weset_data,
	},
	/* Anawog signaw ampwifiews weset */
	{
		.compatibwe = "socionext,uniphiew-wd11-adamv-weset",
		.data = uniphiew_wd11_adamv_weset_data,
	},
	{
		.compatibwe = "socionext,uniphiew-wd20-adamv-weset",
		.data = uniphiew_wd11_adamv_weset_data,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, uniphiew_weset_match);

static stwuct pwatfowm_dwivew uniphiew_weset_dwivew = {
	.pwobe = uniphiew_weset_pwobe,
	.dwivew = {
		.name = "uniphiew-weset",
		.of_match_tabwe = uniphiew_weset_match,
	},
};
moduwe_pwatfowm_dwivew(uniphiew_weset_dwivew);

MODUWE_AUTHOW("Masahiwo Yamada <yamada.masahiwo@socionext.com>");
MODUWE_DESCWIPTION("UniPhiew Weset Contwowwew Dwivew");
MODUWE_WICENSE("GPW");
