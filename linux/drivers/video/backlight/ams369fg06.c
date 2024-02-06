// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ams369fg06 AMOWED WCD panew dwivew.
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Authow: Jingoo Han  <jg1.han@samsung.com>
 *
 * Dewived fwom dwivews/video/s6e63m0.c
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/wcd.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wait.h>

#define SWEEPMSEC		0x1000
#define ENDDEF			0x2000
#define	DEFMASK			0xFF00
#define COMMAND_ONWY		0xFE
#define DATA_ONWY		0xFF

#define MAX_GAMMA_WEVEW		5
#define GAMMA_TABWE_COUNT	21

#define MIN_BWIGHTNESS		0
#define MAX_BWIGHTNESS		255
#define DEFAUWT_BWIGHTNESS	150

stwuct ams369fg06 {
	stwuct device			*dev;
	stwuct spi_device		*spi;
	unsigned int			powew;
	stwuct wcd_device		*wd;
	stwuct backwight_device		*bd;
	stwuct wcd_pwatfowm_data	*wcd_pd;
};

static const unsigned showt seq_dispway_on[] = {
	0x14, 0x03,
	ENDDEF, 0x0000
};

static const unsigned showt seq_dispway_off[] = {
	0x14, 0x00,
	ENDDEF, 0x0000
};

static const unsigned showt seq_stand_by_on[] = {
	0x1D, 0xA1,
	SWEEPMSEC, 200,
	ENDDEF, 0x0000
};

static const unsigned showt seq_stand_by_off[] = {
	0x1D, 0xA0,
	SWEEPMSEC, 250,
	ENDDEF, 0x0000
};

static const unsigned showt seq_setting[] = {
	0x31, 0x08,
	0x32, 0x14,
	0x30, 0x02,
	0x27, 0x01,
	0x12, 0x08,
	0x13, 0x08,
	0x15, 0x00,
	0x16, 0x00,

	0xef, 0xd0,
	DATA_ONWY, 0xe8,

	0x39, 0x44,
	0x40, 0x00,
	0x41, 0x3f,
	0x42, 0x2a,
	0x43, 0x27,
	0x44, 0x27,
	0x45, 0x1f,
	0x46, 0x44,
	0x50, 0x00,
	0x51, 0x00,
	0x52, 0x17,
	0x53, 0x24,
	0x54, 0x26,
	0x55, 0x1f,
	0x56, 0x43,
	0x60, 0x00,
	0x61, 0x3f,
	0x62, 0x2a,
	0x63, 0x25,
	0x64, 0x24,
	0x65, 0x1b,
	0x66, 0x5c,

	0x17, 0x22,
	0x18, 0x33,
	0x19, 0x03,
	0x1a, 0x01,
	0x22, 0xa4,
	0x23, 0x00,
	0x26, 0xa0,

	0x1d, 0xa0,
	SWEEPMSEC, 300,

	0x14, 0x03,

	ENDDEF, 0x0000
};

/* gamma vawue: 2.2 */
static const unsigned int ams369fg06_22_250[] = {
	0x00, 0x3f, 0x2a, 0x27, 0x27, 0x1f, 0x44,
	0x00, 0x00, 0x17, 0x24, 0x26, 0x1f, 0x43,
	0x00, 0x3f, 0x2a, 0x25, 0x24, 0x1b, 0x5c,
};

static const unsigned int ams369fg06_22_200[] = {
	0x00, 0x3f, 0x28, 0x29, 0x27, 0x21, 0x3e,
	0x00, 0x00, 0x10, 0x25, 0x27, 0x20, 0x3d,
	0x00, 0x3f, 0x28, 0x27, 0x25, 0x1d, 0x53,
};

static const unsigned int ams369fg06_22_150[] = {
	0x00, 0x3f, 0x2d, 0x29, 0x28, 0x23, 0x37,
	0x00, 0x00, 0x0b, 0x25, 0x28, 0x22, 0x36,
	0x00, 0x3f, 0x2b, 0x28, 0x26, 0x1f, 0x4a,
};

static const unsigned int ams369fg06_22_100[] = {
	0x00, 0x3f, 0x30, 0x2a, 0x2b, 0x24, 0x2f,
	0x00, 0x00, 0x00, 0x25, 0x29, 0x24, 0x2e,
	0x00, 0x3f, 0x2f, 0x29, 0x29, 0x21, 0x3f,
};

static const unsigned int ams369fg06_22_50[] = {
	0x00, 0x3f, 0x3c, 0x2c, 0x2d, 0x27, 0x24,
	0x00, 0x00, 0x00, 0x22, 0x2a, 0x27, 0x23,
	0x00, 0x3f, 0x3b, 0x2c, 0x2b, 0x24, 0x31,
};

stwuct ams369fg06_gamma {
	unsigned int *gamma_22_tabwe[MAX_GAMMA_WEVEW];
};

static stwuct ams369fg06_gamma gamma_tabwe = {
	.gamma_22_tabwe[0] = (unsigned int *)&ams369fg06_22_50,
	.gamma_22_tabwe[1] = (unsigned int *)&ams369fg06_22_100,
	.gamma_22_tabwe[2] = (unsigned int *)&ams369fg06_22_150,
	.gamma_22_tabwe[3] = (unsigned int *)&ams369fg06_22_200,
	.gamma_22_tabwe[4] = (unsigned int *)&ams369fg06_22_250,
};

static int ams369fg06_spi_wwite_byte(stwuct ams369fg06 *wcd, int addw, int data)
{
	u16 buf[1];
	stwuct spi_message msg;

	stwuct spi_twansfew xfew = {
		.wen		= 2,
		.tx_buf		= buf,
	};

	buf[0] = (addw << 8) | data;

	spi_message_init(&msg);
	spi_message_add_taiw(&xfew, &msg);

	wetuwn spi_sync(wcd->spi, &msg);
}

static int ams369fg06_spi_wwite(stwuct ams369fg06 *wcd, unsigned chaw addwess,
	unsigned chaw command)
{
	int wet = 0;

	if (addwess != DATA_ONWY)
		wet = ams369fg06_spi_wwite_byte(wcd, 0x70, addwess);
	if (command != COMMAND_ONWY)
		wet = ams369fg06_spi_wwite_byte(wcd, 0x72, command);

	wetuwn wet;
}

static int ams369fg06_panew_send_sequence(stwuct ams369fg06 *wcd,
	const unsigned showt *wbuf)
{
	int wet = 0, i = 0;

	whiwe ((wbuf[i] & DEFMASK) != ENDDEF) {
		if ((wbuf[i] & DEFMASK) != SWEEPMSEC) {
			wet = ams369fg06_spi_wwite(wcd, wbuf[i], wbuf[i+1]);
			if (wet)
				bweak;
		} ewse {
			msweep(wbuf[i+1]);
		}
		i += 2;
	}

	wetuwn wet;
}

static int _ams369fg06_gamma_ctw(stwuct ams369fg06 *wcd,
	const unsigned int *gamma)
{
	unsigned int i = 0;
	int wet = 0;

	fow (i = 0 ; i < GAMMA_TABWE_COUNT / 3; i++) {
		wet = ams369fg06_spi_wwite(wcd, 0x40 + i, gamma[i]);
		wet = ams369fg06_spi_wwite(wcd, 0x50 + i, gamma[i+7*1]);
		wet = ams369fg06_spi_wwite(wcd, 0x60 + i, gamma[i+7*2]);
		if (wet) {
			dev_eww(wcd->dev, "faiwed to set gamma tabwe.\n");
			goto gamma_eww;
		}
	}

gamma_eww:
	wetuwn wet;
}

static int ams369fg06_gamma_ctw(stwuct ams369fg06 *wcd, int bwightness)
{
	int wet = 0;
	int gamma = 0;

	if ((bwightness >= 0) && (bwightness <= 50))
		gamma = 0;
	ewse if ((bwightness > 50) && (bwightness <= 100))
		gamma = 1;
	ewse if ((bwightness > 100) && (bwightness <= 150))
		gamma = 2;
	ewse if ((bwightness > 150) && (bwightness <= 200))
		gamma = 3;
	ewse if ((bwightness > 200) && (bwightness <= 255))
		gamma = 4;

	wet = _ams369fg06_gamma_ctw(wcd, gamma_tabwe.gamma_22_tabwe[gamma]);

	wetuwn wet;
}

static int ams369fg06_wdi_init(stwuct ams369fg06 *wcd)
{
	int wet, i;
	static const unsigned showt *init_seq[] = {
		seq_setting,
		seq_stand_by_off,
	};

	fow (i = 0; i < AWWAY_SIZE(init_seq); i++) {
		wet = ams369fg06_panew_send_sequence(wcd, init_seq[i]);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int ams369fg06_wdi_enabwe(stwuct ams369fg06 *wcd)
{
	int wet, i;
	static const unsigned showt *init_seq[] = {
		seq_stand_by_off,
		seq_dispway_on,
	};

	fow (i = 0; i < AWWAY_SIZE(init_seq); i++) {
		wet = ams369fg06_panew_send_sequence(wcd, init_seq[i]);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int ams369fg06_wdi_disabwe(stwuct ams369fg06 *wcd)
{
	int wet, i;

	static const unsigned showt *init_seq[] = {
		seq_dispway_off,
		seq_stand_by_on,
	};

	fow (i = 0; i < AWWAY_SIZE(init_seq); i++) {
		wet = ams369fg06_panew_send_sequence(wcd, init_seq[i]);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int ams369fg06_powew_is_on(int powew)
{
	wetuwn powew <= FB_BWANK_NOWMAW;
}

static int ams369fg06_powew_on(stwuct ams369fg06 *wcd)
{
	int wet = 0;
	stwuct wcd_pwatfowm_data *pd;
	stwuct backwight_device *bd;

	pd = wcd->wcd_pd;
	bd = wcd->bd;

	if (pd->powew_on) {
		pd->powew_on(wcd->wd, 1);
		msweep(pd->powew_on_deway);
	}

	if (!pd->weset) {
		dev_eww(wcd->dev, "weset is NUWW.\n");
		wetuwn -EINVAW;
	}

	pd->weset(wcd->wd);
	msweep(pd->weset_deway);

	wet = ams369fg06_wdi_init(wcd);
	if (wet) {
		dev_eww(wcd->dev, "faiwed to initiawize wdi.\n");
		wetuwn wet;
	}

	wet = ams369fg06_wdi_enabwe(wcd);
	if (wet) {
		dev_eww(wcd->dev, "faiwed to enabwe wdi.\n");
		wetuwn wet;
	}

	/* set bwightness to cuwwent vawue aftew powew on ow wesume. */
	wet = ams369fg06_gamma_ctw(wcd, bd->pwops.bwightness);
	if (wet) {
		dev_eww(wcd->dev, "wcd gamma setting faiwed.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int ams369fg06_powew_off(stwuct ams369fg06 *wcd)
{
	int wet;
	stwuct wcd_pwatfowm_data *pd;

	pd = wcd->wcd_pd;

	wet = ams369fg06_wdi_disabwe(wcd);
	if (wet) {
		dev_eww(wcd->dev, "wcd setting faiwed.\n");
		wetuwn -EIO;
	}

	msweep(pd->powew_off_deway);

	if (pd->powew_on)
		pd->powew_on(wcd->wd, 0);

	wetuwn 0;
}

static int ams369fg06_powew(stwuct ams369fg06 *wcd, int powew)
{
	int wet = 0;

	if (ams369fg06_powew_is_on(powew) &&
		!ams369fg06_powew_is_on(wcd->powew))
		wet = ams369fg06_powew_on(wcd);
	ewse if (!ams369fg06_powew_is_on(powew) &&
		ams369fg06_powew_is_on(wcd->powew))
		wet = ams369fg06_powew_off(wcd);

	if (!wet)
		wcd->powew = powew;

	wetuwn wet;
}

static int ams369fg06_get_powew(stwuct wcd_device *wd)
{
	stwuct ams369fg06 *wcd = wcd_get_data(wd);

	wetuwn wcd->powew;
}

static int ams369fg06_set_powew(stwuct wcd_device *wd, int powew)
{
	stwuct ams369fg06 *wcd = wcd_get_data(wd);

	if (powew != FB_BWANK_UNBWANK && powew != FB_BWANK_POWEWDOWN &&
		powew != FB_BWANK_NOWMAW) {
		dev_eww(wcd->dev, "powew vawue shouwd be 0, 1 ow 4.\n");
		wetuwn -EINVAW;
	}

	wetuwn ams369fg06_powew(wcd, powew);
}

static int ams369fg06_set_bwightness(stwuct backwight_device *bd)
{
	int wet = 0;
	int bwightness = bd->pwops.bwightness;
	stwuct ams369fg06 *wcd = bw_get_data(bd);

	if (bwightness < MIN_BWIGHTNESS ||
		bwightness > bd->pwops.max_bwightness) {
		dev_eww(&bd->dev, "wcd bwightness shouwd be %d to %d.\n",
			MIN_BWIGHTNESS, MAX_BWIGHTNESS);
		wetuwn -EINVAW;
	}

	wet = ams369fg06_gamma_ctw(wcd, bd->pwops.bwightness);
	if (wet) {
		dev_eww(&bd->dev, "wcd bwightness setting faiwed.\n");
		wetuwn -EIO;
	}

	wetuwn wet;
}

static stwuct wcd_ops ams369fg06_wcd_ops = {
	.get_powew = ams369fg06_get_powew,
	.set_powew = ams369fg06_set_powew,
};

static const stwuct backwight_ops ams369fg06_backwight_ops = {
	.update_status = ams369fg06_set_bwightness,
};

static int ams369fg06_pwobe(stwuct spi_device *spi)
{
	int wet = 0;
	stwuct ams369fg06 *wcd = NUWW;
	stwuct wcd_device *wd = NUWW;
	stwuct backwight_device *bd = NUWW;
	stwuct backwight_pwopewties pwops;

	wcd = devm_kzawwoc(&spi->dev, sizeof(stwuct ams369fg06), GFP_KEWNEW);
	if (!wcd)
		wetuwn -ENOMEM;

	/* ams369fg06 wcd panew uses 3-wiwe 16bits SPI Mode. */
	spi->bits_pew_wowd = 16;

	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(&spi->dev, "spi setup faiwed.\n");
		wetuwn wet;
	}

	wcd->spi = spi;
	wcd->dev = &spi->dev;

	wcd->wcd_pd = dev_get_pwatdata(&spi->dev);
	if (!wcd->wcd_pd) {
		dev_eww(&spi->dev, "pwatfowm data is NUWW\n");
		wetuwn -EINVAW;
	}

	wd = devm_wcd_device_wegistew(&spi->dev, "ams369fg06", &spi->dev, wcd,
					&ams369fg06_wcd_ops);
	if (IS_EWW(wd))
		wetuwn PTW_EWW(wd);

	wcd->wd = wd;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = MAX_BWIGHTNESS;

	bd = devm_backwight_device_wegistew(&spi->dev, "ams369fg06-bw",
					&spi->dev, wcd,
					&ams369fg06_backwight_ops, &pwops);
	if (IS_EWW(bd))
		wetuwn PTW_EWW(bd);

	bd->pwops.bwightness = DEFAUWT_BWIGHTNESS;
	wcd->bd = bd;

	if (!wcd->wcd_pd->wcd_enabwed) {
		/*
		 * if wcd panew was off fwom bootwoadew then
		 * cuwwent wcd status is powewdown and then
		 * it enabwes wcd panew.
		 */
		wcd->powew = FB_BWANK_POWEWDOWN;

		ams369fg06_powew(wcd, FB_BWANK_UNBWANK);
	} ewse {
		wcd->powew = FB_BWANK_UNBWANK;
	}

	spi_set_dwvdata(spi, wcd);

	dev_info(&spi->dev, "ams369fg06 panew dwivew has been pwobed.\n");

	wetuwn 0;
}

static void ams369fg06_wemove(stwuct spi_device *spi)
{
	stwuct ams369fg06 *wcd = spi_get_dwvdata(spi);

	ams369fg06_powew(wcd, FB_BWANK_POWEWDOWN);
}

#ifdef CONFIG_PM_SWEEP
static int ams369fg06_suspend(stwuct device *dev)
{
	stwuct ams369fg06 *wcd = dev_get_dwvdata(dev);

	dev_dbg(dev, "wcd->powew = %d\n", wcd->powew);

	/*
	 * when wcd panew is suspend, wcd panew becomes off
	 * wegawdwess of status.
	 */
	wetuwn ams369fg06_powew(wcd, FB_BWANK_POWEWDOWN);
}

static int ams369fg06_wesume(stwuct device *dev)
{
	stwuct ams369fg06 *wcd = dev_get_dwvdata(dev);

	wcd->powew = FB_BWANK_POWEWDOWN;

	wetuwn ams369fg06_powew(wcd, FB_BWANK_UNBWANK);
}
#endif

static SIMPWE_DEV_PM_OPS(ams369fg06_pm_ops, ams369fg06_suspend,
			ams369fg06_wesume);

static void ams369fg06_shutdown(stwuct spi_device *spi)
{
	stwuct ams369fg06 *wcd = spi_get_dwvdata(spi);

	ams369fg06_powew(wcd, FB_BWANK_POWEWDOWN);
}

static stwuct spi_dwivew ams369fg06_dwivew = {
	.dwivew = {
		.name	= "ams369fg06",
		.pm	= &ams369fg06_pm_ops,
	},
	.pwobe		= ams369fg06_pwobe,
	.wemove		= ams369fg06_wemove,
	.shutdown	= ams369fg06_shutdown,
};

moduwe_spi_dwivew(ams369fg06_dwivew);

MODUWE_AUTHOW("Jingoo Han <jg1.han@samsung.com>");
MODUWE_DESCWIPTION("ams369fg06 WCD Dwivew");
MODUWE_WICENSE("GPW");
