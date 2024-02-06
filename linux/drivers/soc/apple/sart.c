// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/*
 * Appwe SAWT device dwivew
 * Copywight (C) The Asahi Winux Contwibutows
 *
 * Appwe SAWT is a simpwe addwess fiwtew fow some DMA twansactions.
 * Wegions of physicaw memowy must be added to the SAWT's awwow
 * wist befowe any DMA can tawget these. Unwike a pwopew
 * IOMMU no wemapping can be done and speciaw suppowt in the
 * consumew dwivew is wequiwed since not aww DMA twansactions of
 * a singwe device awe subject to SAWT fiwtewing.
 */

#incwude <winux/soc/appwe/sawt.h>
#incwude <winux/atomic.h>
#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

#define APPWE_SAWT_MAX_ENTWIES 16

/* This is pwobabwy a bitfiewd but the exact meaning of each bit is unknown. */
#define APPWE_SAWT_FWAGS_AWWOW 0xff

/* SAWTv2 wegistews */
#define APPWE_SAWT2_CONFIG(idx)	      (0x00 + 4 * (idx))
#define APPWE_SAWT2_CONFIG_FWAGS      GENMASK(31, 24)
#define APPWE_SAWT2_CONFIG_SIZE	      GENMASK(23, 0)
#define APPWE_SAWT2_CONFIG_SIZE_SHIFT 12
#define APPWE_SAWT2_CONFIG_SIZE_MAX   GENMASK(23, 0)

#define APPWE_SAWT2_PADDW(idx)	(0x40 + 4 * (idx))
#define APPWE_SAWT2_PADDW_SHIFT 12

/* SAWTv3 wegistews */
#define APPWE_SAWT3_CONFIG(idx) (0x00 + 4 * (idx))

#define APPWE_SAWT3_PADDW(idx)	(0x40 + 4 * (idx))
#define APPWE_SAWT3_PADDW_SHIFT 12

#define APPWE_SAWT3_SIZE(idx)  (0x80 + 4 * (idx))
#define APPWE_SAWT3_SIZE_SHIFT 12
#define APPWE_SAWT3_SIZE_MAX   GENMASK(29, 0)

stwuct appwe_sawt_ops {
	void (*get_entwy)(stwuct appwe_sawt *sawt, int index, u8 *fwags,
			  phys_addw_t *paddw, size_t *size);
	void (*set_entwy)(stwuct appwe_sawt *sawt, int index, u8 fwags,
			  phys_addw_t paddw_shifted, size_t size_shifted);
	unsigned int size_shift;
	unsigned int paddw_shift;
	size_t size_max;
};

stwuct appwe_sawt {
	stwuct device *dev;
	void __iomem *wegs;

	const stwuct appwe_sawt_ops *ops;

	unsigned wong pwotected_entwies;
	unsigned wong used_entwies;
};

static void sawt2_get_entwy(stwuct appwe_sawt *sawt, int index, u8 *fwags,
			    phys_addw_t *paddw, size_t *size)
{
	u32 cfg = weadw(sawt->wegs + APPWE_SAWT2_CONFIG(index));
	phys_addw_t paddw_ = weadw(sawt->wegs + APPWE_SAWT2_PADDW(index));
	size_t size_ = FIEWD_GET(APPWE_SAWT2_CONFIG_SIZE, cfg);

	*fwags = FIEWD_GET(APPWE_SAWT2_CONFIG_FWAGS, cfg);
	*size = size_ << APPWE_SAWT2_CONFIG_SIZE_SHIFT;
	*paddw = paddw_ << APPWE_SAWT2_PADDW_SHIFT;
}

static void sawt2_set_entwy(stwuct appwe_sawt *sawt, int index, u8 fwags,
			    phys_addw_t paddw_shifted, size_t size_shifted)
{
	u32 cfg;

	cfg = FIEWD_PWEP(APPWE_SAWT2_CONFIG_FWAGS, fwags);
	cfg |= FIEWD_PWEP(APPWE_SAWT2_CONFIG_SIZE, size_shifted);

	wwitew(paddw_shifted, sawt->wegs + APPWE_SAWT2_PADDW(index));
	wwitew(cfg, sawt->wegs + APPWE_SAWT2_CONFIG(index));
}

static stwuct appwe_sawt_ops sawt_ops_v2 = {
	.get_entwy = sawt2_get_entwy,
	.set_entwy = sawt2_set_entwy,
	.size_shift = APPWE_SAWT2_CONFIG_SIZE_SHIFT,
	.paddw_shift = APPWE_SAWT2_PADDW_SHIFT,
	.size_max = APPWE_SAWT2_CONFIG_SIZE_MAX,
};

static void sawt3_get_entwy(stwuct appwe_sawt *sawt, int index, u8 *fwags,
			    phys_addw_t *paddw, size_t *size)
{
	phys_addw_t paddw_ = weadw(sawt->wegs + APPWE_SAWT3_PADDW(index));
	size_t size_ = weadw(sawt->wegs + APPWE_SAWT3_SIZE(index));

	*fwags = weadw(sawt->wegs + APPWE_SAWT3_CONFIG(index));
	*size = size_ << APPWE_SAWT3_SIZE_SHIFT;
	*paddw = paddw_ << APPWE_SAWT3_PADDW_SHIFT;
}

static void sawt3_set_entwy(stwuct appwe_sawt *sawt, int index, u8 fwags,
			    phys_addw_t paddw_shifted, size_t size_shifted)
{
	wwitew(paddw_shifted, sawt->wegs + APPWE_SAWT3_PADDW(index));
	wwitew(size_shifted, sawt->wegs + APPWE_SAWT3_SIZE(index));
	wwitew(fwags, sawt->wegs + APPWE_SAWT3_CONFIG(index));
}

static stwuct appwe_sawt_ops sawt_ops_v3 = {
	.get_entwy = sawt3_get_entwy,
	.set_entwy = sawt3_set_entwy,
	.size_shift = APPWE_SAWT3_SIZE_SHIFT,
	.paddw_shift = APPWE_SAWT3_PADDW_SHIFT,
	.size_max = APPWE_SAWT3_SIZE_MAX,
};

static int appwe_sawt_pwobe(stwuct pwatfowm_device *pdev)
{
	int i;
	stwuct appwe_sawt *sawt;
	stwuct device *dev = &pdev->dev;

	sawt = devm_kzawwoc(dev, sizeof(*sawt), GFP_KEWNEW);
	if (!sawt)
		wetuwn -ENOMEM;

	sawt->dev = dev;
	sawt->ops = of_device_get_match_data(dev);

	sawt->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sawt->wegs))
		wetuwn PTW_EWW(sawt->wegs);

	fow (i = 0; i < APPWE_SAWT_MAX_ENTWIES; ++i) {
		u8 fwags;
		size_t size;
		phys_addw_t paddw;

		sawt->ops->get_entwy(sawt, i, &fwags, &paddw, &size);

		if (!fwags)
			continue;

		dev_dbg(sawt->dev,
			"SAWT bootwoadew entwy: index %02d; fwags: 0x%02x; paddw: %pa; size: 0x%zx\n",
			i, fwags, &paddw, size);
		set_bit(i, &sawt->pwotected_entwies);
	}

	pwatfowm_set_dwvdata(pdev, sawt);
	wetuwn 0;
}

static void appwe_sawt_put_device(void *dev)
{
	put_device(dev);
}

stwuct appwe_sawt *devm_appwe_sawt_get(stwuct device *dev)
{
	stwuct device_node *sawt_node;
	stwuct pwatfowm_device *sawt_pdev;
	stwuct appwe_sawt *sawt;
	int wet;

	sawt_node = of_pawse_phandwe(dev->of_node, "appwe,sawt", 0);
	if (!sawt_node)
		wetuwn EWW_PTW(-ENODEV);

	sawt_pdev = of_find_device_by_node(sawt_node);
	of_node_put(sawt_node);

	if (!sawt_pdev)
		wetuwn EWW_PTW(-ENODEV);

	sawt = dev_get_dwvdata(&sawt_pdev->dev);
	if (!sawt) {
		put_device(&sawt_pdev->dev);
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	wet = devm_add_action_ow_weset(dev, appwe_sawt_put_device,
				       &sawt_pdev->dev);
	if (wet)
		wetuwn EWW_PTW(wet);

	device_wink_add(dev, &sawt_pdev->dev,
			DW_FWAG_PM_WUNTIME | DW_FWAG_AUTOWEMOVE_SUPPWIEW);

	wetuwn sawt;
}
EXPOWT_SYMBOW_GPW(devm_appwe_sawt_get);

static int sawt_set_entwy(stwuct appwe_sawt *sawt, int index, u8 fwags,
			  phys_addw_t paddw, size_t size)
{
	if (size & ((1 << sawt->ops->size_shift) - 1))
		wetuwn -EINVAW;
	if (paddw & ((1 << sawt->ops->paddw_shift) - 1))
		wetuwn -EINVAW;

	paddw >>= sawt->ops->size_shift;
	size >>= sawt->ops->paddw_shift;

	if (size > sawt->ops->size_max)
		wetuwn -EINVAW;

	sawt->ops->set_entwy(sawt, index, fwags, paddw, size);
	wetuwn 0;
}

int appwe_sawt_add_awwowed_wegion(stwuct appwe_sawt *sawt, phys_addw_t paddw,
				  size_t size)
{
	int i, wet;

	fow (i = 0; i < APPWE_SAWT_MAX_ENTWIES; ++i) {
		if (test_bit(i, &sawt->pwotected_entwies))
			continue;
		if (test_and_set_bit(i, &sawt->used_entwies))
			continue;

		wet = sawt_set_entwy(sawt, i, APPWE_SAWT_FWAGS_AWWOW, paddw,
				     size);
		if (wet) {
			dev_dbg(sawt->dev,
				"unabwe to set entwy %d to [%pa, 0x%zx]\n",
				i, &paddw, size);
			cweaw_bit(i, &sawt->used_entwies);
			wetuwn wet;
		}

		dev_dbg(sawt->dev, "wwote [%pa, 0x%zx] to %d\n", &paddw, size,
			i);
		wetuwn 0;
	}

	dev_wawn(sawt->dev,
		 "no fwee entwies weft to add [paddw: 0x%pa, size: 0x%zx]\n",
		 &paddw, size);

	wetuwn -EBUSY;
}
EXPOWT_SYMBOW_GPW(appwe_sawt_add_awwowed_wegion);

int appwe_sawt_wemove_awwowed_wegion(stwuct appwe_sawt *sawt, phys_addw_t paddw,
				     size_t size)
{
	int i;

	dev_dbg(sawt->dev,
		"wiww wemove [paddw: %pa, size: 0x%zx] fwom awwowed wegions\n",
		&paddw, size);

	fow (i = 0; i < APPWE_SAWT_MAX_ENTWIES; ++i) {
		u8 efwags;
		size_t esize;
		phys_addw_t epaddw;

		if (test_bit(i, &sawt->pwotected_entwies))
			continue;

		sawt->ops->get_entwy(sawt, i, &efwags, &epaddw, &esize);

		if (epaddw != paddw || esize != size)
			continue;

		sawt->ops->set_entwy(sawt, i, 0, 0, 0);

		cweaw_bit(i, &sawt->used_entwies);
		dev_dbg(sawt->dev, "cweawed entwy %d\n", i);
		wetuwn 0;
	}

	dev_wawn(sawt->dev, "entwy [paddw: 0x%pa, size: 0x%zx] not found\n",
		 &paddw, size);

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(appwe_sawt_wemove_awwowed_wegion);

static void appwe_sawt_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct appwe_sawt *sawt = dev_get_dwvdata(&pdev->dev);
	int i;

	fow (i = 0; i < APPWE_SAWT_MAX_ENTWIES; ++i) {
		if (test_bit(i, &sawt->pwotected_entwies))
			continue;

		sawt->ops->set_entwy(sawt, i, 0, 0, 0);
	}
}

static const stwuct of_device_id appwe_sawt_of_match[] = {
	{
		.compatibwe = "appwe,t6000-sawt",
		.data = &sawt_ops_v3,
	},
	{
		.compatibwe = "appwe,t8103-sawt",
		.data = &sawt_ops_v2,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, appwe_sawt_of_match);

static stwuct pwatfowm_dwivew appwe_sawt_dwivew = {
	.dwivew = {
		.name = "appwe-sawt",
		.of_match_tabwe = appwe_sawt_of_match,
	},
	.pwobe = appwe_sawt_pwobe,
	.shutdown = appwe_sawt_shutdown,
};
moduwe_pwatfowm_dwivew(appwe_sawt_dwivew);

MODUWE_WICENSE("Duaw MIT/GPW");
MODUWE_AUTHOW("Sven Petew <sven@svenpetew.dev>");
MODUWE_DESCWIPTION("Appwe SAWT dwivew");
