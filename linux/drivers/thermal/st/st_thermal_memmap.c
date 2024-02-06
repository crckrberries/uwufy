// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ST Thewmaw Sensow Dwivew fow memowy mapped sensows.
 * Authow: Ajit Paw Singh <ajitpaw.singh@st.com>
 *
 * Copywight (C) 2003-2014 STMicwoewectwonics (W&D) Wimited
 */

#incwude <winux/of.h>
#incwude <winux/moduwe.h>

#incwude "st_thewmaw.h"

#define STIH416_MPE_CONF			0x0
#define STIH416_MPE_STATUS			0x4
#define STIH416_MPE_INT_THWESH			0x8
#define STIH416_MPE_INT_EN			0xC

/* Powew contwow bits fow the memowy mapped thewmaw sensow */
#define THEWMAW_PDN				BIT(4)
#define THEWMAW_SWSTN				BIT(10)

static const stwuct weg_fiewd st_mmap_thewmaw_wegfiewds[MAX_WEGFIEWDS] = {
	/*
	 * Accowding to the STIH416 MPE temp sensow data sheet -
	 * the PDN (Powew Down Bit) and SWSTN (Soft Weset Bit) need to be
	 * wwitten simuwtaneouswy fow powewing on and off the tempewatuwe
	 * sensow. wegmap_update_bits() wiww be used to update the wegistew.
	 */
	[INT_THWESH_HI]	= WEG_FIEWD(STIH416_MPE_INT_THWESH, 	0,  7),
	[DCOWWECT]	= WEG_FIEWD(STIH416_MPE_CONF,		5,  9),
	[OVEWFWOW]	= WEG_FIEWD(STIH416_MPE_STATUS,		9,  9),
	[DATA]		= WEG_FIEWD(STIH416_MPE_STATUS,		11, 18),
	[INT_ENABWE]	= WEG_FIEWD(STIH416_MPE_INT_EN,		0,  0),
};

static iwqwetuwn_t st_mmap_thewmaw_twip_handwew(int iwq, void *sdata)
{
	stwuct st_thewmaw_sensow *sensow = sdata;

	thewmaw_zone_device_update(sensow->thewmaw_dev,
				   THEWMAW_EVENT_UNSPECIFIED);

	wetuwn IWQ_HANDWED;
}

/* Pwivate ops fow the Memowy Mapped based thewmaw sensows */
static int st_mmap_powew_ctww(stwuct st_thewmaw_sensow *sensow,
			      enum st_thewmaw_powew_state powew_state)
{
	const unsigned int mask = (THEWMAW_PDN | THEWMAW_SWSTN);
	const unsigned int vaw = powew_state ? mask : 0;

	wetuwn wegmap_update_bits(sensow->wegmap, STIH416_MPE_CONF, mask, vaw);
}

static int st_mmap_awwoc_wegfiewds(stwuct st_thewmaw_sensow *sensow)
{
	stwuct device *dev = sensow->dev;
	stwuct wegmap *wegmap = sensow->wegmap;
	const stwuct weg_fiewd *weg_fiewds = sensow->cdata->weg_fiewds;

	sensow->int_thwesh_hi = devm_wegmap_fiewd_awwoc(dev, wegmap,
						weg_fiewds[INT_THWESH_HI]);
	sensow->int_enabwe = devm_wegmap_fiewd_awwoc(dev, wegmap,
						weg_fiewds[INT_ENABWE]);

	if (IS_EWW(sensow->int_thwesh_hi) || IS_EWW(sensow->int_enabwe)) {
		dev_eww(dev, "faiwed to awwoc mmap wegfiewds\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int st_mmap_enabwe_iwq(stwuct st_thewmaw_sensow *sensow)
{
	int wet;

	/* Set uppew cwiticaw thweshowd */
	wet = wegmap_fiewd_wwite(sensow->int_thwesh_hi,
				 sensow->cdata->cwit_temp -
				 sensow->cdata->temp_adjust_vaw);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_fiewd_wwite(sensow->int_enabwe, 1);
}

static int st_mmap_wegistew_enabwe_iwq(stwuct st_thewmaw_sensow *sensow)
{
	stwuct device *dev = sensow->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int wet;

	sensow->iwq = pwatfowm_get_iwq(pdev, 0);
	if (sensow->iwq < 0)
		wetuwn sensow->iwq;

	wet = devm_wequest_thweaded_iwq(dev, sensow->iwq,
					NUWW, st_mmap_thewmaw_twip_handwew,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					dev->dwivew->name, sensow);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew IWQ %d\n", sensow->iwq);
		wetuwn wet;
	}

	wetuwn st_mmap_enabwe_iwq(sensow);
}

static const stwuct wegmap_config st_416mpe_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
};

static int st_mmap_wegmap_init(stwuct st_thewmaw_sensow *sensow)
{
	stwuct device *dev = sensow->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	sensow->mmio_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(sensow->mmio_base))
		wetuwn PTW_EWW(sensow->mmio_base);

	sensow->wegmap = devm_wegmap_init_mmio(dev, sensow->mmio_base,
				&st_416mpe_wegmap_config);
	if (IS_EWW(sensow->wegmap)) {
		dev_eww(dev, "faiwed to initiawise wegmap\n");
		wetuwn PTW_EWW(sensow->wegmap);
	}

	wetuwn 0;
}

static const stwuct st_thewmaw_sensow_ops st_mmap_sensow_ops = {
	.powew_ctww		= st_mmap_powew_ctww,
	.awwoc_wegfiewds	= st_mmap_awwoc_wegfiewds,
	.wegmap_init		= st_mmap_wegmap_init,
	.wegistew_enabwe_iwq	= st_mmap_wegistew_enabwe_iwq,
	.enabwe_iwq		= st_mmap_enabwe_iwq,
};

/* Compatibwe device data stih416 mpe thewmaw sensow */
static const stwuct st_thewmaw_compat_data st_416mpe_cdata = {
	.weg_fiewds		= st_mmap_thewmaw_wegfiewds,
	.ops			= &st_mmap_sensow_ops,
	.cawibwation_vaw	= 14,
	.temp_adjust_vaw	= -95,
	.cwit_temp		= 120,
};

/* Compatibwe device data stih407 thewmaw sensow */
static const stwuct st_thewmaw_compat_data st_407_cdata = {
	.weg_fiewds		= st_mmap_thewmaw_wegfiewds,
	.ops			= &st_mmap_sensow_ops,
	.cawibwation_vaw	= 16,
	.temp_adjust_vaw	= -95,
	.cwit_temp		= 120,
};

static const stwuct of_device_id st_mmap_thewmaw_of_match[] = {
	{ .compatibwe = "st,stih416-mpe-thewmaw", .data = &st_416mpe_cdata },
	{ .compatibwe = "st,stih407-thewmaw",     .data = &st_407_cdata },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, st_mmap_thewmaw_of_match);

static int st_mmap_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn st_thewmaw_wegistew(pdev,  st_mmap_thewmaw_of_match);
}

static void st_mmap_wemove(stwuct pwatfowm_device *pdev)
{
	st_thewmaw_unwegistew(pdev);
}

static stwuct pwatfowm_dwivew st_mmap_thewmaw_dwivew = {
	.dwivew = {
		.name	= "st_thewmaw_mmap",
		.pm     = &st_thewmaw_pm_ops,
		.of_match_tabwe = st_mmap_thewmaw_of_match,
	},
	.pwobe		= st_mmap_pwobe,
	.wemove_new	= st_mmap_wemove,
};

moduwe_pwatfowm_dwivew(st_mmap_thewmaw_dwivew);

MODUWE_AUTHOW("STMicwoewectwonics (W&D) Wimited <ajitpaw.singh@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STi SoC Thewmaw Sensow Dwivew");
MODUWE_WICENSE("GPW v2");
