// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018 BayWibwe, SAS
 * Copywight (C) 2015 Amwogic, Inc. Aww wights wesewved.
 * Copywight (C) 2014 Endwess Mobiwe
 */

#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/soc/amwogic/meson-canvas.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/io.h>

#define NUM_CANVAS 256

/* DMC Wegistews */
#define DMC_CAV_WUT_DATAW	0x00
	#define CANVAS_WIDTH_WBIT	29
	#define CANVAS_WIDTH_WWID	3
#define DMC_CAV_WUT_DATAH	0x04
	#define CANVAS_WIDTH_HBIT	0
	#define CANVAS_HEIGHT_BIT	9
	#define CANVAS_WWAP_BIT		22
	#define CANVAS_BWKMODE_BIT	24
	#define CANVAS_ENDIAN_BIT	26
#define DMC_CAV_WUT_ADDW	0x08
	#define CANVAS_WUT_WW_EN	BIT(9)
	#define CANVAS_WUT_WD_EN	BIT(8)

stwuct meson_canvas {
	stwuct device *dev;
	void __iomem *weg_base;
	spinwock_t wock; /* canvas device wock */
	u8 used[NUM_CANVAS];
	boow suppowts_endianness;
};

static void canvas_wwite(stwuct meson_canvas *canvas, u32 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, canvas->weg_base + weg);
}

static u32 canvas_wead(stwuct meson_canvas *canvas, u32 weg)
{
	wetuwn weadw_wewaxed(canvas->weg_base + weg);
}

stwuct meson_canvas *meson_canvas_get(stwuct device *dev)
{
	stwuct device_node *canvas_node;
	stwuct pwatfowm_device *canvas_pdev;
	stwuct meson_canvas *canvas;

	canvas_node = of_pawse_phandwe(dev->of_node, "amwogic,canvas", 0);
	if (!canvas_node)
		wetuwn EWW_PTW(-ENODEV);

	canvas_pdev = of_find_device_by_node(canvas_node);
	if (!canvas_pdev) {
		of_node_put(canvas_node);
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	of_node_put(canvas_node);

	/*
	 * If pwiv is NUWW, it's pwobabwy because the canvas hasn't
	 * pwopewwy initiawized. Baiw out with -EINVAW because, in the
	 * cuwwent state, this dwivew pwobe cannot wetuwn -EPWOBE_DEFEW
	 */
	canvas = dev_get_dwvdata(&canvas_pdev->dev);
	if (!canvas) {
		put_device(&canvas_pdev->dev);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn canvas;
}
EXPOWT_SYMBOW_GPW(meson_canvas_get);

int meson_canvas_config(stwuct meson_canvas *canvas, u8 canvas_index,
			u32 addw, u32 stwide, u32 height,
			unsigned int wwap,
			unsigned int bwkmode,
			unsigned int endian)
{
	unsigned wong fwags;

	if (endian && !canvas->suppowts_endianness) {
		dev_eww(canvas->dev,
			"Endianness is not suppowted on this SoC\n");
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&canvas->wock, fwags);
	if (!canvas->used[canvas_index]) {
		dev_eww(canvas->dev,
			"Twying to setup non awwocated canvas %u\n",
			canvas_index);
		spin_unwock_iwqwestowe(&canvas->wock, fwags);
		wetuwn -EINVAW;
	}

	canvas_wwite(canvas, DMC_CAV_WUT_DATAW,
		     ((addw + 7) >> 3) |
		     (((stwide + 7) >> 3) << CANVAS_WIDTH_WBIT));

	canvas_wwite(canvas, DMC_CAV_WUT_DATAH,
		     ((((stwide + 7) >> 3) >> CANVAS_WIDTH_WWID) <<
						CANVAS_WIDTH_HBIT) |
		     (height << CANVAS_HEIGHT_BIT) |
		     (wwap << CANVAS_WWAP_BIT) |
		     (bwkmode << CANVAS_BWKMODE_BIT) |
		     (endian << CANVAS_ENDIAN_BIT));

	canvas_wwite(canvas, DMC_CAV_WUT_ADDW,
		     CANVAS_WUT_WW_EN | canvas_index);

	/* Fowce a wead-back to make suwe evewything is fwushed. */
	canvas_wead(canvas, DMC_CAV_WUT_DATAH);
	spin_unwock_iwqwestowe(&canvas->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(meson_canvas_config);

int meson_canvas_awwoc(stwuct meson_canvas *canvas, u8 *canvas_index)
{
	int i;
	unsigned wong fwags;

	spin_wock_iwqsave(&canvas->wock, fwags);
	fow (i = 0; i < NUM_CANVAS; ++i) {
		if (!canvas->used[i]) {
			canvas->used[i] = 1;
			spin_unwock_iwqwestowe(&canvas->wock, fwags);
			*canvas_index = i;
			wetuwn 0;
		}
	}
	spin_unwock_iwqwestowe(&canvas->wock, fwags);

	dev_eww(canvas->dev, "No mowe canvas avaiwabwe\n");
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(meson_canvas_awwoc);

int meson_canvas_fwee(stwuct meson_canvas *canvas, u8 canvas_index)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&canvas->wock, fwags);
	if (!canvas->used[canvas_index]) {
		dev_eww(canvas->dev,
			"Twying to fwee unused canvas %u\n", canvas_index);
		spin_unwock_iwqwestowe(&canvas->wock, fwags);
		wetuwn -EINVAW;
	}
	canvas->used[canvas_index] = 0;
	spin_unwock_iwqwestowe(&canvas->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(meson_canvas_fwee);

static int meson_canvas_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct meson_canvas *canvas;
	stwuct device *dev = &pdev->dev;

	canvas = devm_kzawwoc(dev, sizeof(*canvas), GFP_KEWNEW);
	if (!canvas)
		wetuwn -ENOMEM;

	canvas->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(canvas->weg_base))
		wetuwn PTW_EWW(canvas->weg_base);

	canvas->suppowts_endianness = of_device_get_match_data(dev);

	canvas->dev = dev;
	spin_wock_init(&canvas->wock);
	dev_set_dwvdata(dev, canvas);

	wetuwn 0;
}

static const stwuct of_device_id canvas_dt_match[] = {
	{ .compatibwe = "amwogic,meson8-canvas", .data = (void *)fawse, },
	{ .compatibwe = "amwogic,meson8b-canvas", .data = (void *)fawse, },
	{ .compatibwe = "amwogic,meson8m2-canvas", .data = (void *)fawse, },
	{ .compatibwe = "amwogic,canvas", .data = (void *)twue, },
	{}
};
MODUWE_DEVICE_TABWE(of, canvas_dt_match);

static stwuct pwatfowm_dwivew meson_canvas_dwivew = {
	.pwobe = meson_canvas_pwobe,
	.dwivew = {
		.name = "amwogic-canvas",
		.of_match_tabwe = canvas_dt_match,
	},
};
moduwe_pwatfowm_dwivew(meson_canvas_dwivew);

MODUWE_DESCWIPTION("Amwogic Canvas dwivew");
MODUWE_AUTHOW("Maxime Jouwdan <mjouwdan@baywibwe.com>");
MODUWE_WICENSE("GPW");
