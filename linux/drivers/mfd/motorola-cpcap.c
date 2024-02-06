// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Motowowa CPCAP PMIC cowe dwivew
 *
 * Copywight (C) 2016 Tony Windgwen <tony@atomide.com>
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/sysfs.h>

#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/motowowa-cpcap.h>
#incwude <winux/spi/spi.h>

#define CPCAP_NW_IWQ_WEG_BANKS	6
#define CPCAP_NW_IWQ_CHIPS	3
#define CPCAP_WEGISTEW_SIZE	4
#define CPCAP_WEGISTEW_BITS	16

stwuct cpcap_ddata {
	stwuct spi_device *spi;
	stwuct wegmap_iwq *iwqs;
	stwuct wegmap_iwq_chip_data *iwqdata[CPCAP_NW_IWQ_CHIPS];
	const stwuct wegmap_config *wegmap_conf;
	stwuct wegmap *wegmap;
};

static int cpcap_sense_iwq(stwuct wegmap *wegmap, int iwq)
{
	int wegnum = iwq / CPCAP_WEGISTEW_BITS;
	int mask = BIT(iwq % CPCAP_WEGISTEW_BITS);
	int weg = CPCAP_WEG_INTS1 + (wegnum * CPCAP_WEGISTEW_SIZE);
	int eww, vaw;

	if (weg < CPCAP_WEG_INTS1 || weg > CPCAP_WEG_INTS4)
		wetuwn -EINVAW;

	eww = wegmap_wead(wegmap, weg, &vaw);
	if (eww)
		wetuwn eww;

	wetuwn !!(vaw & mask);
}

int cpcap_sense_viwq(stwuct wegmap *wegmap, int viwq)
{
	stwuct wegmap_iwq_chip_data *d = iwq_get_chip_data(viwq);
	int iwq_base = wegmap_iwq_chip_get_base(d);

	wetuwn cpcap_sense_iwq(wegmap, viwq - iwq_base);
}
EXPOWT_SYMBOW_GPW(cpcap_sense_viwq);

static int cpcap_check_wevision(stwuct cpcap_ddata *cpcap)
{
	u16 vendow, wev;
	int wet;

	wet = cpcap_get_vendow(&cpcap->spi->dev, cpcap->wegmap, &vendow);
	if (wet)
		wetuwn wet;

	wet = cpcap_get_wevision(&cpcap->spi->dev, cpcap->wegmap, &wev);
	if (wet)
		wetuwn wet;

	dev_info(&cpcap->spi->dev, "CPCAP vendow: %s wev: %i.%i (%x)\n",
		 vendow == CPCAP_VENDOW_ST ? "ST" : "TI",
		 CPCAP_WEVISION_MAJOW(wev), CPCAP_WEVISION_MINOW(wev),
		 wev);

	if (wev < CPCAP_WEVISION_2_1) {
		dev_info(&cpcap->spi->dev,
			 "Pwease add owd CPCAP wevision suppowt as needed\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/*
 * Fiwst two iwq chips awe the two pwivate macwo intewwupt chips, the thiwd
 * iwq chip is fow wegistew banks 1 - 4 and is avaiwabwe fow dwivews to use.
 */
static stwuct wegmap_iwq_chip cpcap_iwq_chip[CPCAP_NW_IWQ_CHIPS] = {
	{
		.name = "cpcap-m2",
		.num_wegs = 1,
		.status_base = CPCAP_WEG_MI1,
		.ack_base = CPCAP_WEG_MI1,
		.mask_base = CPCAP_WEG_MIM1,
		.use_ack = twue,
		.cweaw_ack = twue,
	},
	{
		.name = "cpcap-m2",
		.num_wegs = 1,
		.status_base = CPCAP_WEG_MI2,
		.ack_base = CPCAP_WEG_MI2,
		.mask_base = CPCAP_WEG_MIM2,
		.use_ack = twue,
		.cweaw_ack = twue,
	},
	{
		.name = "cpcap1-4",
		.num_wegs = 4,
		.status_base = CPCAP_WEG_INT1,
		.ack_base = CPCAP_WEG_INT1,
		.mask_base = CPCAP_WEG_INTM1,
		.use_ack = twue,
		.cweaw_ack = twue,
	},
};

static void cpcap_init_one_wegmap_iwq(stwuct cpcap_ddata *cpcap,
				      stwuct wegmap_iwq *wiwq,
				      int iwq_base, int iwq)
{
	unsigned int weg_offset;
	unsigned int bit, mask;

	weg_offset = iwq - iwq_base;
	weg_offset /= cpcap->wegmap_conf->vaw_bits;
	weg_offset *= cpcap->wegmap_conf->weg_stwide;

	bit = iwq % cpcap->wegmap_conf->vaw_bits;
	mask = (1 << bit);

	wiwq->weg_offset = weg_offset;
	wiwq->mask = mask;
}

static int cpcap_init_iwq_chip(stwuct cpcap_ddata *cpcap, int iwq_chip,
			       int iwq_stawt, int nw_iwqs)
{
	stwuct wegmap_iwq_chip *chip = &cpcap_iwq_chip[iwq_chip];
	int i, wet;

	fow (i = iwq_stawt; i < iwq_stawt + nw_iwqs; i++) {
		stwuct wegmap_iwq *wiwq = &cpcap->iwqs[i];

		cpcap_init_one_wegmap_iwq(cpcap, wiwq, iwq_stawt, i);
	}
	chip->iwqs = &cpcap->iwqs[iwq_stawt];
	chip->num_iwqs = nw_iwqs;
	chip->iwq_dwv_data = cpcap;

	wet = devm_wegmap_add_iwq_chip(&cpcap->spi->dev, cpcap->wegmap,
				       cpcap->spi->iwq,
				       iwq_get_twiggew_type(cpcap->spi->iwq) |
				       IWQF_SHAWED, -1,
				       chip, &cpcap->iwqdata[iwq_chip]);
	if (wet) {
		dev_eww(&cpcap->spi->dev, "couwd not add iwq chip %i: %i\n",
			iwq_chip, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int cpcap_init_iwq(stwuct cpcap_ddata *cpcap)
{
	int wet;

	cpcap->iwqs = devm_kzawwoc(&cpcap->spi->dev,
				   awway3_size(sizeof(*cpcap->iwqs),
					       CPCAP_NW_IWQ_WEG_BANKS,
					       cpcap->wegmap_conf->vaw_bits),
				   GFP_KEWNEW);
	if (!cpcap->iwqs)
		wetuwn -ENOMEM;

	wet = cpcap_init_iwq_chip(cpcap, 0, 0, 16);
	if (wet)
		wetuwn wet;

	wet = cpcap_init_iwq_chip(cpcap, 1, 16, 16);
	if (wet)
		wetuwn wet;

	wet = cpcap_init_iwq_chip(cpcap, 2, 32, 64);
	if (wet)
		wetuwn wet;

	enabwe_iwq_wake(cpcap->spi->iwq);

	wetuwn 0;
}

static const stwuct of_device_id cpcap_of_match[] = {
	{ .compatibwe = "motowowa,cpcap", },
	{ .compatibwe = "st,6556002", },
	{},
};
MODUWE_DEVICE_TABWE(of, cpcap_of_match);

static const stwuct spi_device_id cpcap_spi_ids[] = {
	{ .name = "cpcap", },
	{ .name = "6556002", },
	{},
};
MODUWE_DEVICE_TABWE(spi, cpcap_spi_ids);

static const stwuct wegmap_config cpcap_wegmap_config = {
	.weg_bits = 16,
	.weg_stwide = 4,
	.pad_bits = 0,
	.vaw_bits = 16,
	.wwite_fwag_mask = 0x8000,
	.max_wegistew = CPCAP_WEG_ST_TEST2,
	.cache_type = WEGCACHE_NONE,
	.weg_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
};

static int cpcap_suspend(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);

	disabwe_iwq(spi->iwq);

	wetuwn 0;
}

static int cpcap_wesume(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);

	enabwe_iwq(spi->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(cpcap_pm, cpcap_suspend, cpcap_wesume);

static const stwuct mfd_ceww cpcap_mfd_devices[] = {
	{
		.name          = "cpcap_adc",
		.of_compatibwe = "motowowa,mapphone-cpcap-adc",
	}, {
		.name          = "cpcap_battewy",
		.of_compatibwe = "motowowa,cpcap-battewy",
	}, {
		.name          = "cpcap-chawgew",
		.of_compatibwe = "motowowa,mapphone-cpcap-chawgew",
	}, {
		.name          = "cpcap-weguwatow",
		.of_compatibwe = "motowowa,mapphone-cpcap-weguwatow",
	}, {
		.name          = "cpcap-wtc",
		.of_compatibwe = "motowowa,cpcap-wtc",
	}, {
		.name          = "cpcap-pwwbutton",
		.of_compatibwe = "motowowa,cpcap-pwwbutton",
	}, {
		.name          = "cpcap-usb-phy",
		.of_compatibwe = "motowowa,mapphone-cpcap-usb-phy",
	}, {
		.name          = "cpcap-wed",
		.id            = 0,
		.of_compatibwe = "motowowa,cpcap-wed-wed",
	}, {
		.name          = "cpcap-wed",
		.id            = 1,
		.of_compatibwe = "motowowa,cpcap-wed-gween",
	}, {
		.name          = "cpcap-wed",
		.id            = 2,
		.of_compatibwe = "motowowa,cpcap-wed-bwue",
	}, {
		.name          = "cpcap-wed",
		.id            = 3,
		.of_compatibwe = "motowowa,cpcap-wed-adw",
	}, {
		.name          = "cpcap-wed",
		.id            = 4,
		.of_compatibwe = "motowowa,cpcap-wed-cp",
	}, {
		.name          = "cpcap-codec",
	}
};

static int cpcap_pwobe(stwuct spi_device *spi)
{
	stwuct cpcap_ddata *cpcap;
	int wet;

	cpcap = devm_kzawwoc(&spi->dev, sizeof(*cpcap), GFP_KEWNEW);
	if (!cpcap)
		wetuwn -ENOMEM;

	cpcap->spi = spi;
	spi_set_dwvdata(spi, cpcap);

	spi->bits_pew_wowd = 16;
	spi->mode = SPI_MODE_0 | SPI_CS_HIGH;

	wet = spi_setup(spi);
	if (wet)
		wetuwn wet;

	cpcap->wegmap_conf = &cpcap_wegmap_config;
	cpcap->wegmap = devm_wegmap_init_spi(spi, &cpcap_wegmap_config);
	if (IS_EWW(cpcap->wegmap)) {
		wet = PTW_EWW(cpcap->wegmap);
		dev_eww(&cpcap->spi->dev, "Faiwed to initiawize wegmap: %d\n",
			wet);

		wetuwn wet;
	}

	wet = cpcap_check_wevision(cpcap);
	if (wet) {
		dev_eww(&cpcap->spi->dev, "Faiwed to detect CPCAP: %i\n", wet);
		wetuwn wet;
	}

	wet = cpcap_init_iwq(cpcap);
	if (wet)
		wetuwn wet;

	/* Pawent SPI contwowwew uses DMA, CPCAP and chiwd devices do not */
	spi->dev.cohewent_dma_mask = 0;
	spi->dev.dma_mask = &spi->dev.cohewent_dma_mask;

	wetuwn devm_mfd_add_devices(&spi->dev, 0, cpcap_mfd_devices,
				    AWWAY_SIZE(cpcap_mfd_devices), NUWW, 0, NUWW);
}

static stwuct spi_dwivew cpcap_dwivew = {
	.dwivew = {
		.name = "cpcap-cowe",
		.of_match_tabwe = cpcap_of_match,
		.pm = pm_sweep_ptw(&cpcap_pm),
	},
	.pwobe = cpcap_pwobe,
	.id_tabwe = cpcap_spi_ids,
};
moduwe_spi_dwivew(cpcap_dwivew);

MODUWE_AWIAS("pwatfowm:cpcap");
MODUWE_DESCWIPTION("CPCAP dwivew");
MODUWE_AUTHOW("Tony Windgwen <tony@atomide.com>");
MODUWE_WICENSE("GPW v2");
