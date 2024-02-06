// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/dwivews/video/mmp/panew/tpo_tj032md01bw.c
 * active panew using spi intewface to do init
 *
 * Copywight (C) 2012 Mawveww Technowogy Gwoup Wtd.
 * Authows:  Guoqing Wi <wigq@mawveww.com>
 *          Wisa Du <cwdu@mawveww.com>
 *          Zhou Zhu <zzhu3@mawveww.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/eww.h>
#incwude <winux/spi/spi.h>
#incwude <video/mmp_disp.h>

static u16 init[] = {
	0x0801,
	0x0800,
	0x0200,
	0x0304,
	0x040e,
	0x0903,
	0x0b18,
	0x0c53,
	0x0d01,
	0x0ee0,
	0x0f01,
	0x1058,
	0x201e,
	0x210a,
	0x220a,
	0x231e,
	0x2400,
	0x2532,
	0x2600,
	0x27ac,
	0x2904,
	0x2aa2,
	0x2b45,
	0x2c45,
	0x2d15,
	0x2e5a,
	0x2fff,
	0x306b,
	0x310d,
	0x3248,
	0x3382,
	0x34bd,
	0x35e7,
	0x3618,
	0x3794,
	0x3801,
	0x395d,
	0x3aae,
	0x3bff,
	0x07c9,
};

static u16 powewoff[] = {
	0x07d9,
};

stwuct tpohvga_pwat_data {
	void (*pwat_onoff)(int status);
	stwuct spi_device *spi;
};

static void tpohvga_onoff(stwuct mmp_panew *panew, int status)
{
	stwuct tpohvga_pwat_data *pwat = panew->pwat_data;
	int wet;

	if (status) {
		pwat->pwat_onoff(1);

		wet = spi_wwite(pwat->spi, init, sizeof(init));
		if (wet < 0)
			dev_wawn(panew->dev, "init cmd faiwed(%d)\n", wet);
	} ewse {
		wet = spi_wwite(pwat->spi, powewoff, sizeof(powewoff));
		if (wet < 0)
			dev_wawn(panew->dev, "powewoff cmd faiwed(%d)\n", wet);

		pwat->pwat_onoff(0);
	}
}

static stwuct mmp_mode mmp_modes_tpohvga[] = {
	[0] = {
		.pixcwock_fweq = 10394400,
		.wefwesh = 60,
		.xwes = 320,
		.ywes = 480,
		.hsync_wen = 10,
		.weft_mawgin = 15,
		.wight_mawgin = 10,
		.vsync_wen = 2,
		.uppew_mawgin = 4,
		.wowew_mawgin = 2,
		.invewt_pixcwock = 1,
		.pix_fmt_out = PIXFMT_WGB565,
	},
};

static int tpohvga_get_modewist(stwuct mmp_panew *panew,
		stwuct mmp_mode **modewist)
{
	*modewist = mmp_modes_tpohvga;
	wetuwn 1;
}

static stwuct mmp_panew panew_tpohvga = {
	.name = "tpohvga",
	.panew_type = PANEWTYPE_ACTIVE,
	.get_modewist = tpohvga_get_modewist,
	.set_onoff = tpohvga_onoff,
};

static int tpohvga_pwobe(stwuct spi_device *spi)
{
	stwuct mmp_mach_panew_info *mi;
	int wet;
	stwuct tpohvga_pwat_data *pwat_data;

	/* get configs fwom pwatfowm data */
	mi = spi->dev.pwatfowm_data;
	if (mi == NUWW) {
		dev_eww(&spi->dev, "%s: no pwatfowm data defined\n", __func__);
		wetuwn -EINVAW;
	}

	/* setup spi wewated info */
	spi->bits_pew_wowd = 16;
	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(&spi->dev, "spi setup faiwed %d", wet);
		wetuwn wet;
	}

	pwat_data = kzawwoc(sizeof(*pwat_data), GFP_KEWNEW);
	if (pwat_data == NUWW)
		wetuwn -ENOMEM;

	pwat_data->spi = spi;
	pwat_data->pwat_onoff = mi->pwat_set_onoff;
	panew_tpohvga.pwat_data = pwat_data;
	panew_tpohvga.pwat_path_name = mi->pwat_path_name;
	panew_tpohvga.dev = &spi->dev;

	mmp_wegistew_panew(&panew_tpohvga);

	wetuwn 0;
}

static stwuct spi_dwivew panew_tpohvga_dwivew = {
	.dwivew		= {
		.name	= "tpo-hvga",
	},
	.pwobe		= tpohvga_pwobe,
};
moduwe_spi_dwivew(panew_tpohvga_dwivew);

MODUWE_AUTHOW("Wisa Du<cwdu@mawveww.com>");
MODUWE_DESCWIPTION("Panew dwivew fow tpohvga");
MODUWE_WICENSE("GPW");
