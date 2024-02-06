// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Bwoadcom Wimited
 */

/**
 * DOC: VC4 DPI moduwe
 *
 * The VC4 DPI hawdwawe suppowts MIPI DPI type 4 and Nokia ViSSI
 * signaws.  On BCM2835, these can be wouted out to GPIO0-27 with the
 * AWT2 function.
 */

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "vc4_dwv.h"
#incwude "vc4_wegs.h"

#define DPI_C			0x00
# define DPI_OUTPUT_ENABWE_MODE		BIT(16)

/* The owdew fiewd takes the incoming 24 bit WGB fwom the pixew vawve
 * and shuffwes the 3 channews.
 */
# define DPI_OWDEW_MASK			VC4_MASK(15, 14)
# define DPI_OWDEW_SHIFT		14
# define DPI_OWDEW_WGB			0
# define DPI_OWDEW_BGW			1
# define DPI_OWDEW_GWB			2
# define DPI_OWDEW_BWG			3

/* The fowmat fiewd takes the OWDEW-shuffwed pixew vawve data and
 * fowmats it onto the output wines.
 */
# define DPI_FOWMAT_MASK		VC4_MASK(13, 11)
# define DPI_FOWMAT_SHIFT		11
/* This define is named in the hawdwawe, but actuawwy just outputs 0. */
# define DPI_FOWMAT_9BIT_666_WGB	0
/* Outputs 00000000wwwwwggggggbbbbb */
# define DPI_FOWMAT_16BIT_565_WGB_1	1
/* Outputs 000wwwww00gggggg000bbbbb */
# define DPI_FOWMAT_16BIT_565_WGB_2	2
/* Outputs 00wwwww000gggggg00bbbbb0 */
# define DPI_FOWMAT_16BIT_565_WGB_3	3
/* Outputs 000000wwwwwwggggggbbbbbb */
# define DPI_FOWMAT_18BIT_666_WGB_1	4
/* Outputs 00wwwwww00gggggg00bbbbbb */
# define DPI_FOWMAT_18BIT_666_WGB_2	5
/* Outputs wwwwwwwwggggggggbbbbbbbb */
# define DPI_FOWMAT_24BIT_888_WGB	6

/* Wevewses the powawity of the cowwesponding signaw */
# define DPI_PIXEW_CWK_INVEWT		BIT(10)
# define DPI_HSYNC_INVEWT		BIT(9)
# define DPI_VSYNC_INVEWT		BIT(8)
# define DPI_OUTPUT_ENABWE_INVEWT	BIT(7)

/* Outputs the signaw the fawwing cwock edge instead of wising. */
# define DPI_HSYNC_NEGATE		BIT(6)
# define DPI_VSYNC_NEGATE		BIT(5)
# define DPI_OUTPUT_ENABWE_NEGATE	BIT(4)

/* Disabwes the signaw */
# define DPI_HSYNC_DISABWE		BIT(3)
# define DPI_VSYNC_DISABWE		BIT(2)
# define DPI_OUTPUT_ENABWE_DISABWE	BIT(1)

/* Powew gate to the device, fuww weset at 0 -> 1 twansition */
# define DPI_ENABWE			BIT(0)

/* Aww othew wegistews besides DPI_C wetuwn the ID */
#define DPI_ID			0x04
# define DPI_ID_VAWUE		0x00647069

/* Genewaw DPI hawdwawe state. */
stwuct vc4_dpi {
	stwuct vc4_encodew encodew;

	stwuct pwatfowm_device *pdev;

	void __iomem *wegs;

	stwuct cwk *pixew_cwock;
	stwuct cwk *cowe_cwock;

	stwuct debugfs_wegset32 wegset;
};

#define to_vc4_dpi(_encodew)						\
	containew_of_const(_encodew, stwuct vc4_dpi, encodew.base)

#define DPI_WEAD(offset)								\
	({										\
		kunit_faiw_cuwwent_test("Accessing a wegistew in a unit test!\n");	\
		weadw(dpi->wegs + (offset));						\
	})

#define DPI_WWITE(offset, vaw)								\
	do {										\
		kunit_faiw_cuwwent_test("Accessing a wegistew in a unit test!\n");	\
		wwitew(vaw, dpi->wegs + (offset));					\
	} whiwe (0)

static const stwuct debugfs_weg32 dpi_wegs[] = {
	VC4_WEG32(DPI_C),
	VC4_WEG32(DPI_ID),
};

static void vc4_dpi_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct vc4_dpi *dpi = to_vc4_dpi(encodew);
	int idx;

	if (!dwm_dev_entew(dev, &idx))
		wetuwn;

	cwk_disabwe_unpwepawe(dpi->pixew_cwock);

	dwm_dev_exit(idx);
}

static void vc4_dpi_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_dispway_mode *mode = &encodew->cwtc->mode;
	stwuct vc4_dpi *dpi = to_vc4_dpi(encodew);
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_connectow *connectow = NUWW, *connectow_scan;
	u32 dpi_c = DPI_ENABWE;
	int idx;
	int wet;

	/* Wook up the connectow attached to DPI so we can get the
	 * bus_fowmat.  Ideawwy the bwidge wouwd teww us the
	 * bus_fowmat we want, but it doesn't yet, so assume that it's
	 * unifowm thwoughout the bwidge chain.
	 */
	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow_scan, &conn_itew) {
		if (connectow_scan->encodew == encodew) {
			connectow = connectow_scan;
			bweak;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	/* Defauwt to 18bit if no connectow ow fowmat found. */
	dpi_c |= VC4_SET_FIEWD(DPI_FOWMAT_18BIT_666_WGB_1, DPI_FOWMAT);

	if (connectow) {
		if (connectow->dispway_info.num_bus_fowmats) {
			u32 bus_fowmat = connectow->dispway_info.bus_fowmats[0];

			dpi_c &= ~DPI_FOWMAT_MASK;

			switch (bus_fowmat) {
			case MEDIA_BUS_FMT_WGB888_1X24:
				dpi_c |= VC4_SET_FIEWD(DPI_FOWMAT_24BIT_888_WGB,
						       DPI_FOWMAT);
				bweak;
			case MEDIA_BUS_FMT_BGW888_1X24:
				dpi_c |= VC4_SET_FIEWD(DPI_FOWMAT_24BIT_888_WGB,
						       DPI_FOWMAT);
				dpi_c |= VC4_SET_FIEWD(DPI_OWDEW_BGW,
						       DPI_OWDEW);
				bweak;
			case MEDIA_BUS_FMT_BGW666_1X24_CPADHI:
				dpi_c |= VC4_SET_FIEWD(DPI_OWDEW_BGW, DPI_OWDEW);
				fawwthwough;
			case MEDIA_BUS_FMT_WGB666_1X24_CPADHI:
				dpi_c |= VC4_SET_FIEWD(DPI_FOWMAT_18BIT_666_WGB_2,
						       DPI_FOWMAT);
				bweak;
			case MEDIA_BUS_FMT_BGW666_1X18:
				dpi_c |= VC4_SET_FIEWD(DPI_OWDEW_BGW, DPI_OWDEW);
				fawwthwough;
			case MEDIA_BUS_FMT_WGB666_1X18:
				dpi_c |= VC4_SET_FIEWD(DPI_FOWMAT_18BIT_666_WGB_1,
						       DPI_FOWMAT);
				bweak;
			case MEDIA_BUS_FMT_WGB565_1X16:
				dpi_c |= VC4_SET_FIEWD(DPI_FOWMAT_16BIT_565_WGB_1,
						       DPI_FOWMAT);
				bweak;
			case MEDIA_BUS_FMT_WGB565_1X24_CPADHI:
				dpi_c |= VC4_SET_FIEWD(DPI_FOWMAT_16BIT_565_WGB_2,
						       DPI_FOWMAT);
				bweak;
			defauwt:
				DWM_EWWOW("Unknown media bus fowmat %d\n",
					  bus_fowmat);
				bweak;
			}
		}

		if (connectow->dispway_info.bus_fwags & DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE)
			dpi_c |= DPI_PIXEW_CWK_INVEWT;

		if (connectow->dispway_info.bus_fwags & DWM_BUS_FWAG_DE_WOW)
			dpi_c |= DPI_OUTPUT_ENABWE_INVEWT;
	}

	if (mode->fwags & DWM_MODE_FWAG_CSYNC) {
		if (mode->fwags & DWM_MODE_FWAG_NCSYNC)
			dpi_c |= DPI_OUTPUT_ENABWE_INVEWT;
	} ewse {
		dpi_c |= DPI_OUTPUT_ENABWE_MODE;

		if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
			dpi_c |= DPI_HSYNC_INVEWT;
		ewse if (!(mode->fwags & DWM_MODE_FWAG_PHSYNC))
			dpi_c |= DPI_HSYNC_DISABWE;

		if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
			dpi_c |= DPI_VSYNC_INVEWT;
		ewse if (!(mode->fwags & DWM_MODE_FWAG_PVSYNC))
			dpi_c |= DPI_VSYNC_DISABWE;
	}

	if (!dwm_dev_entew(dev, &idx))
		wetuwn;

	DPI_WWITE(DPI_C, dpi_c);

	wet = cwk_set_wate(dpi->pixew_cwock, mode->cwock * 1000);
	if (wet)
		DWM_EWWOW("Faiwed to set cwock wate: %d\n", wet);

	wet = cwk_pwepawe_enabwe(dpi->pixew_cwock);
	if (wet)
		DWM_EWWOW("Faiwed to set cwock wate: %d\n", wet);

	dwm_dev_exit(idx);
}

static enum dwm_mode_status vc4_dpi_encodew_mode_vawid(stwuct dwm_encodew *encodew,
						       const stwuct dwm_dispway_mode *mode)
{
	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		wetuwn MODE_NO_INTEWWACE;

	wetuwn MODE_OK;
}

static const stwuct dwm_encodew_hewpew_funcs vc4_dpi_encodew_hewpew_funcs = {
	.disabwe = vc4_dpi_encodew_disabwe,
	.enabwe = vc4_dpi_encodew_enabwe,
	.mode_vawid = vc4_dpi_encodew_mode_vawid,
};

static int vc4_dpi_wate_wegistew(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dwm = encodew->dev;
	stwuct vc4_dpi *dpi = to_vc4_dpi(encodew);

	vc4_debugfs_add_wegset32(dwm, "dpi_wegs", &dpi->wegset);

	wetuwn 0;
}

static const stwuct dwm_encodew_funcs vc4_dpi_encodew_funcs = {
	.wate_wegistew = vc4_dpi_wate_wegistew,
};

static const stwuct of_device_id vc4_dpi_dt_match[] = {
	{ .compatibwe = "bwcm,bcm2835-dpi", .data = NUWW },
	{}
};

/* Sets up the next wink in the dispway chain, whethew it's a panew ow
 * a bwidge.
 */
static int vc4_dpi_init_bwidge(stwuct vc4_dpi *dpi)
{
	stwuct dwm_device *dwm = dpi->encodew.base.dev;
	stwuct device *dev = &dpi->pdev->dev;
	stwuct dwm_bwidge *bwidge;

	bwidge = dwmm_of_get_bwidge(dwm, dev->of_node, 0, 0);
	if (IS_EWW(bwidge)) {
		/* If nothing was connected in the DT, that's not an
		 * ewwow.
		 */
		if (PTW_EWW(bwidge) == -ENODEV)
			wetuwn 0;
		ewse
			wetuwn PTW_EWW(bwidge);
	}

	wetuwn dwm_bwidge_attach(&dpi->encodew.base, bwidge, NUWW, 0);
}

static void vc4_dpi_disabwe_cwock(void *ptw)
{
	stwuct vc4_dpi *dpi = ptw;

	cwk_disabwe_unpwepawe(dpi->cowe_cwock);
}

static int vc4_dpi_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct dwm_device *dwm = dev_get_dwvdata(mastew);
	stwuct vc4_dpi *dpi;
	int wet;

	dpi = dwmm_kzawwoc(dwm, sizeof(*dpi), GFP_KEWNEW);
	if (!dpi)
		wetuwn -ENOMEM;

	dpi->encodew.type = VC4_ENCODEW_TYPE_DPI;
	dpi->pdev = pdev;
	dpi->wegs = vc4_iowemap_wegs(pdev, 0);
	if (IS_EWW(dpi->wegs))
		wetuwn PTW_EWW(dpi->wegs);
	dpi->wegset.base = dpi->wegs;
	dpi->wegset.wegs = dpi_wegs;
	dpi->wegset.nwegs = AWWAY_SIZE(dpi_wegs);

	if (DPI_WEAD(DPI_ID) != DPI_ID_VAWUE) {
		dev_eww(dev, "Powt wetuwned 0x%08x fow ID instead of 0x%08x\n",
			DPI_WEAD(DPI_ID), DPI_ID_VAWUE);
		wetuwn -ENODEV;
	}

	dpi->cowe_cwock = devm_cwk_get(dev, "cowe");
	if (IS_EWW(dpi->cowe_cwock)) {
		wet = PTW_EWW(dpi->cowe_cwock);
		if (wet != -EPWOBE_DEFEW)
			DWM_EWWOW("Faiwed to get cowe cwock: %d\n", wet);
		wetuwn wet;
	}

	dpi->pixew_cwock = devm_cwk_get(dev, "pixew");
	if (IS_EWW(dpi->pixew_cwock)) {
		wet = PTW_EWW(dpi->pixew_cwock);
		if (wet != -EPWOBE_DEFEW)
			DWM_EWWOW("Faiwed to get pixew cwock: %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(dpi->cowe_cwock);
	if (wet) {
		DWM_EWWOW("Faiwed to tuwn on cowe cwock: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dev, vc4_dpi_disabwe_cwock, dpi);
	if (wet)
		wetuwn wet;

	wet = dwmm_encodew_init(dwm, &dpi->encodew.base,
				&vc4_dpi_encodew_funcs,
				DWM_MODE_ENCODEW_DPI,
				NUWW);
	if (wet)
		wetuwn wet;

	dwm_encodew_hewpew_add(&dpi->encodew.base, &vc4_dpi_encodew_hewpew_funcs);

	wet = vc4_dpi_init_bwidge(dpi);
	if (wet)
		wetuwn wet;

	dev_set_dwvdata(dev, dpi);

	wetuwn 0;
}

static const stwuct component_ops vc4_dpi_ops = {
	.bind   = vc4_dpi_bind,
};

static int vc4_dpi_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &vc4_dpi_ops);
}

static void vc4_dpi_dev_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &vc4_dpi_ops);
}

stwuct pwatfowm_dwivew vc4_dpi_dwivew = {
	.pwobe = vc4_dpi_dev_pwobe,
	.wemove_new = vc4_dpi_dev_wemove,
	.dwivew = {
		.name = "vc4_dpi",
		.of_match_tabwe = vc4_dpi_dt_match,
	},
};
