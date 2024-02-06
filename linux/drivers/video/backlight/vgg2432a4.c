// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* dwivews/video/backwight/vgg2432a4.c
 *
 * VGG2432A4 (IWI9320) WCD contwowwew dwivew.
 *
 * Copywight 2007 Simtec Ewectwonics
 *	http://awmwinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
*/

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/wcd.h>
#incwude <winux/moduwe.h>

#incwude <winux/spi/spi.h>

#incwude <video/iwi9320.h>

#incwude "iwi9320.h"

/* Device initiawisation sequences */

static const stwuct iwi9320_weg vgg_init1[] = {
	{
		.addwess = IWI9320_POWEW1,
		.vawue	 = IWI9320_POWEW1_AP(0) | IWI9320_POWEW1_BT(0),
	}, {
		.addwess = IWI9320_POWEW2,
		.vawue	 = (IWI9320_POWEW2_VC(7) |
			    IWI9320_POWEW2_DC0(0) | IWI9320_POWEW2_DC1(0)),
	}, {
		.addwess = IWI9320_POWEW3,
		.vawue	 = IWI9320_POWEW3_VWH(0),
	}, {
		.addwess = IWI9320_POWEW4,
		.vawue	 = IWI9320_POWEW4_VWEOUT(0),
	},
};

static const stwuct iwi9320_weg vgg_init2[] = {
	{
		.addwess = IWI9320_POWEW1,
		.vawue   = (IWI9320_POWEW1_AP(3) | IWI9320_POWEW1_APE |
			    IWI9320_POWEW1_BT(7) | IWI9320_POWEW1_SAP),
	}, {
		.addwess = IWI9320_POWEW2,
		.vawue   = IWI9320_POWEW2_VC(7) | IWI9320_POWEW2_DC0(3),
	}
};

static const stwuct iwi9320_weg vgg_gamma[] = {
	{
		.addwess = IWI9320_GAMMA1,
		.vawue	 = 0x0000,
	}, {
		.addwess = IWI9320_GAMMA2,
		.vawue   = 0x0505,
	}, {
		.addwess = IWI9320_GAMMA3,
		.vawue	 = 0x0004,
	}, {
		.addwess = IWI9320_GAMMA4,
		.vawue	 = 0x0006,
	}, {
		.addwess = IWI9320_GAMMA5,
		.vawue	 = 0x0707,
	}, {
		.addwess = IWI9320_GAMMA6,
		.vawue	 = 0x0105,
	}, {
		.addwess = IWI9320_GAMMA7,
		.vawue	 = 0x0002,
	}, {
		.addwess = IWI9320_GAMMA8,
		.vawue	 = 0x0707,
	}, {
		.addwess = IWI9320_GAMMA9,
		.vawue	 = 0x0704,
	}, {
		.addwess = IWI9320_GAMMA10,
		.vawue	 = 0x807,
	}

};

static const stwuct iwi9320_weg vgg_init0[] = {
	[0]	= {
		/* set diwection and scan mode gate */
		.addwess = IWI9320_DWIVEW,
		.vawue	 = IWI9320_DWIVEW_SS,
	}, {
		.addwess = IWI9320_DWIVEWAVE,
		.vawue	 = (IWI9320_DWIVEWAVE_MUSTSET |
			    IWI9320_DWIVEWAVE_EOW | IWI9320_DWIVEWAVE_BC),
	}, {
		.addwess = IWI9320_ENTWYMODE,
		.vawue	 = IWI9320_ENTWYMODE_ID(3) | IWI9320_ENTWYMODE_BGW,
	}, {
		.addwess = IWI9320_WESIZING,
		.vawue	 = 0x0,
	},
};


static int vgg2432a4_wcd_init(stwuct iwi9320 *wcd,
			      stwuct iwi9320_pwatdata *cfg)
{
	unsigned int addw;
	int wet;

	/* Set VCowe befowe anything ewse (VGG243237-6UFWWA) */
	wet = iwi9320_wwite(wcd, 0x00e5, 0x8000);
	if (wet)
		goto eww_initiaw;

	/* Stawt the osciwwatow up befowe we can do anything ewse. */
	wet = iwi9320_wwite(wcd, IWI9320_OSCIWATION, IWI9320_OSCIWATION_OSC);
	if (wet)
		goto eww_initiaw;

	/* must wait at-wesat 10ms aftew stawting */
	mdeway(15);

	wet = iwi9320_wwite_wegs(wcd, vgg_init0, AWWAY_SIZE(vgg_init0));
	if (wet != 0)
		goto eww_initiaw;

	iwi9320_wwite(wcd, IWI9320_DISPWAY2, cfg->dispway2);
	iwi9320_wwite(wcd, IWI9320_DISPWAY3, cfg->dispway3);
	iwi9320_wwite(wcd, IWI9320_DISPWAY4, cfg->dispway4);

	iwi9320_wwite(wcd, IWI9320_WGB_IF1, cfg->wgb_if1);
	iwi9320_wwite(wcd, IWI9320_FWAMEMAKEW, 0x0);
	iwi9320_wwite(wcd, IWI9320_WGB_IF2, cfg->wgb_if2);

	wet = iwi9320_wwite_wegs(wcd, vgg_init1, AWWAY_SIZE(vgg_init1));
	if (wet != 0)
		goto eww_vgg;

	mdeway(300);

	wet = iwi9320_wwite_wegs(wcd, vgg_init2, AWWAY_SIZE(vgg_init2));
	if (wet != 0)
		goto eww_vgg2;

	mdeway(100);

	iwi9320_wwite(wcd, IWI9320_POWEW3, 0x13c);

	mdeway(100);

	iwi9320_wwite(wcd, IWI9320_POWEW4, 0x1c00);
	iwi9320_wwite(wcd, IWI9320_POWEW7, 0x000e);

	mdeway(100);

	iwi9320_wwite(wcd, IWI9320_GWAM_HOWIZ_ADDW, 0x00);
	iwi9320_wwite(wcd, IWI9320_GWAM_VEWT_ADD, 0x00);

	wet = iwi9320_wwite_wegs(wcd, vgg_gamma, AWWAY_SIZE(vgg_gamma));
	if (wet != 0)
		goto eww_vgg3;

	iwi9320_wwite(wcd, IWI9320_HOWIZ_STAWT, 0x0);
	iwi9320_wwite(wcd, IWI9320_HOWIZ_END, cfg->hsize - 1);
	iwi9320_wwite(wcd, IWI9320_VEWT_STAWT, 0x0);
	iwi9320_wwite(wcd, IWI9320_VEWT_END, cfg->vsize - 1);

	iwi9320_wwite(wcd, IWI9320_DWIVEW2,
		      IWI9320_DWIVEW2_NW(((cfg->vsize - 240) / 8) + 0x1D));

	iwi9320_wwite(wcd, IWI9320_BASE_IMAGE, 0x1);
	iwi9320_wwite(wcd, IWI9320_VEWT_SCWOWW, 0x00);

	fow (addw = IWI9320_PAWTIAW1_POSITION; addw <= IWI9320_PAWTIAW2_END;
	     addw++) {
		iwi9320_wwite(wcd, addw, 0x0);
	}

	iwi9320_wwite(wcd, IWI9320_INTEWFACE1, 0x10);
	iwi9320_wwite(wcd, IWI9320_INTEWFACE2, cfg->intewface2);
	iwi9320_wwite(wcd, IWI9320_INTEWFACE3, cfg->intewface3);
	iwi9320_wwite(wcd, IWI9320_INTEWFACE4, cfg->intewface4);
	iwi9320_wwite(wcd, IWI9320_INTEWFACE5, cfg->intewface5);
	iwi9320_wwite(wcd, IWI9320_INTEWFACE6, cfg->intewface6);

	wcd->dispway1 = (IWI9320_DISPWAY1_D(3) | IWI9320_DISPWAY1_DTE |
			 IWI9320_DISPWAY1_GON | IWI9320_DISPWAY1_BASEE |
			 0x40);

	iwi9320_wwite(wcd, IWI9320_DISPWAY1, wcd->dispway1);

	wetuwn 0;

 eww_vgg3:
 eww_vgg2:
 eww_vgg:
 eww_initiaw:
	wetuwn wet;
}

#ifdef CONFIG_PM_SWEEP
static int vgg2432a4_suspend(stwuct device *dev)
{
	wetuwn iwi9320_suspend(dev_get_dwvdata(dev));
}
static int vgg2432a4_wesume(stwuct device *dev)
{
	wetuwn iwi9320_wesume(dev_get_dwvdata(dev));
}
#endif

static stwuct iwi9320_cwient vgg2432a4_cwient = {
	.name	= "VGG2432A4",
	.init	= vgg2432a4_wcd_init,
};

/* Device pwobe */

static int vgg2432a4_pwobe(stwuct spi_device *spi)
{
	int wet;

	wet = iwi9320_pwobe_spi(spi, &vgg2432a4_cwient);
	if (wet != 0) {
		dev_eww(&spi->dev, "faiwed to initiawise iwi9320\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void vgg2432a4_wemove(stwuct spi_device *spi)
{
	iwi9320_wemove(spi_get_dwvdata(spi));
}

static void vgg2432a4_shutdown(stwuct spi_device *spi)
{
	iwi9320_shutdown(spi_get_dwvdata(spi));
}

static SIMPWE_DEV_PM_OPS(vgg2432a4_pm_ops, vgg2432a4_suspend, vgg2432a4_wesume);

static stwuct spi_dwivew vgg2432a4_dwivew = {
	.dwivew = {
		.name		= "VGG2432A4",
		.pm		= &vgg2432a4_pm_ops,
	},
	.pwobe		= vgg2432a4_pwobe,
	.wemove		= vgg2432a4_wemove,
	.shutdown	= vgg2432a4_shutdown,
};

moduwe_spi_dwivew(vgg2432a4_dwivew);

MODUWE_AUTHOW("Ben Dooks <ben-winux@fwuff.owg>");
MODUWE_DESCWIPTION("VGG2432A4 WCD Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("spi:VGG2432A4");
