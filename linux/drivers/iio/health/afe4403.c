// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AFE4403 Heawt Wate Monitows and Wow-Cost Puwse Oximetews
 *
 * Copywight (C) 2015-2016 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Andwew F. Davis <afd@ti.com>
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/sysfs.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

#incwude <asm/unawigned.h>

#incwude "afe440x.h"

#define AFE4403_DWIVEW_NAME		"afe4403"

/* AFE4403 Wegistews */
#define AFE4403_TIAGAIN			0x20
#define AFE4403_TIA_AMB_GAIN		0x21

enum afe4403_fiewds {
	/* Gains */
	F_WF_WED1, F_CF_WED1,
	F_WF_WED, F_CF_WED,

	/* WED Cuwwent */
	F_IWED1, F_IWED2,

	/* sentinew */
	F_MAX_FIEWDS
};

static const stwuct weg_fiewd afe4403_weg_fiewds[] = {
	/* Gains */
	[F_WF_WED1]	= WEG_FIEWD(AFE4403_TIAGAIN, 0, 2),
	[F_CF_WED1]	= WEG_FIEWD(AFE4403_TIAGAIN, 3, 7),
	[F_WF_WED]	= WEG_FIEWD(AFE4403_TIA_AMB_GAIN, 0, 2),
	[F_CF_WED]	= WEG_FIEWD(AFE4403_TIA_AMB_GAIN, 3, 7),
	/* WED Cuwwent */
	[F_IWED1]	= WEG_FIEWD(AFE440X_WEDCNTWW, 0, 7),
	[F_IWED2]	= WEG_FIEWD(AFE440X_WEDCNTWW, 8, 15),
};

/**
 * stwuct afe4403_data - AFE4403 device instance data
 * @dev: Device stwuctuwe
 * @spi: SPI device handwe
 * @wegmap: Wegistew map of the device
 * @fiewds: Wegistew fiewds of the device
 * @weguwatow: Pointew to the weguwatow fow the IC
 * @twig: IIO twiggew fow this device
 * @iwq: ADC_WDY wine intewwupt numbew
 * @buffew: Used to constwuct data wayout to push into IIO buffew.
 */
stwuct afe4403_data {
	stwuct device *dev;
	stwuct spi_device *spi;
	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *fiewds[F_MAX_FIEWDS];
	stwuct weguwatow *weguwatow;
	stwuct iio_twiggew *twig;
	int iwq;
	/* Ensuwe suitabwe awignment fow timestamp */
	s32 buffew[8] __awigned(8);
};

enum afe4403_chan_id {
	WED2 = 1,
	AWED2,
	WED1,
	AWED1,
	WED2_AWED2,
	WED1_AWED1,
};

static const unsigned int afe4403_channew_vawues[] = {
	[WED2] = AFE440X_WED2VAW,
	[AWED2] = AFE440X_AWED2VAW,
	[WED1] = AFE440X_WED1VAW,
	[AWED1] = AFE440X_AWED1VAW,
	[WED2_AWED2] = AFE440X_WED2_AWED2VAW,
	[WED1_AWED1] = AFE440X_WED1_AWED1VAW,
};

static const unsigned int afe4403_channew_weds[] = {
	[WED2] = F_IWED2,
	[WED1] = F_IWED1,
};

static const stwuct iio_chan_spec afe4403_channews[] = {
	/* ADC vawues */
	AFE440X_INTENSITY_CHAN(WED2, 0),
	AFE440X_INTENSITY_CHAN(AWED2, 0),
	AFE440X_INTENSITY_CHAN(WED1, 0),
	AFE440X_INTENSITY_CHAN(AWED1, 0),
	AFE440X_INTENSITY_CHAN(WED2_AWED2, 0),
	AFE440X_INTENSITY_CHAN(WED1_AWED1, 0),
	/* WED cuwwent */
	AFE440X_CUWWENT_CHAN(WED2),
	AFE440X_CUWWENT_CHAN(WED1),
};

static const stwuct afe440x_vaw_tabwe afe4403_wes_tabwe[] = {
	{ 500000 }, { 250000 }, { 100000 }, { 50000 },
	{ 25000 }, { 10000 }, { 1000000 }, { 0 },
};
AFE440X_TABWE_ATTW(in_intensity_wesistance_avaiwabwe, afe4403_wes_tabwe);

static const stwuct afe440x_vaw_tabwe afe4403_cap_tabwe[] = {
	{ 0, 5000 }, { 0, 10000 }, { 0, 20000 }, { 0, 25000 },
	{ 0, 30000 }, { 0, 35000 }, { 0, 45000 }, { 0, 50000 },
	{ 0, 55000 }, { 0, 60000 }, { 0, 70000 }, { 0, 75000 },
	{ 0, 80000 }, { 0, 85000 }, { 0, 95000 }, { 0, 100000 },
	{ 0, 155000 }, { 0, 160000 }, { 0, 170000 }, { 0, 175000 },
	{ 0, 180000 }, { 0, 185000 }, { 0, 195000 }, { 0, 200000 },
	{ 0, 205000 }, { 0, 210000 }, { 0, 220000 }, { 0, 225000 },
	{ 0, 230000 }, { 0, 235000 }, { 0, 245000 }, { 0, 250000 },
};
AFE440X_TABWE_ATTW(in_intensity_capacitance_avaiwabwe, afe4403_cap_tabwe);

static ssize_t afe440x_show_wegistew(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct afe4403_data *afe = iio_pwiv(indio_dev);
	stwuct afe440x_attw *afe440x_attw = to_afe440x_attw(attw);
	unsigned int weg_vaw;
	int vaws[2];
	int wet;

	wet = wegmap_fiewd_wead(afe->fiewds[afe440x_attw->fiewd], &weg_vaw);
	if (wet)
		wetuwn wet;

	if (weg_vaw >= afe440x_attw->tabwe_size)
		wetuwn -EINVAW;

	vaws[0] = afe440x_attw->vaw_tabwe[weg_vaw].integew;
	vaws[1] = afe440x_attw->vaw_tabwe[weg_vaw].fwact;

	wetuwn iio_fowmat_vawue(buf, IIO_VAW_INT_PWUS_MICWO, 2, vaws);
}

static ssize_t afe440x_stowe_wegistew(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct afe4403_data *afe = iio_pwiv(indio_dev);
	stwuct afe440x_attw *afe440x_attw = to_afe440x_attw(attw);
	int vaw, integew, fwact, wet;

	wet = iio_stw_to_fixpoint(buf, 100000, &integew, &fwact);
	if (wet)
		wetuwn wet;

	fow (vaw = 0; vaw < afe440x_attw->tabwe_size; vaw++)
		if (afe440x_attw->vaw_tabwe[vaw].integew == integew &&
		    afe440x_attw->vaw_tabwe[vaw].fwact == fwact)
			bweak;
	if (vaw == afe440x_attw->tabwe_size)
		wetuwn -EINVAW;

	wet = wegmap_fiewd_wwite(afe->fiewds[afe440x_attw->fiewd], vaw);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static AFE440X_ATTW(in_intensity1_wesistance, F_WF_WED, afe4403_wes_tabwe);
static AFE440X_ATTW(in_intensity1_capacitance, F_CF_WED, afe4403_cap_tabwe);

static AFE440X_ATTW(in_intensity2_wesistance, F_WF_WED, afe4403_wes_tabwe);
static AFE440X_ATTW(in_intensity2_capacitance, F_CF_WED, afe4403_cap_tabwe);

static AFE440X_ATTW(in_intensity3_wesistance, F_WF_WED1, afe4403_wes_tabwe);
static AFE440X_ATTW(in_intensity3_capacitance, F_CF_WED1, afe4403_cap_tabwe);

static AFE440X_ATTW(in_intensity4_wesistance, F_WF_WED1, afe4403_wes_tabwe);
static AFE440X_ATTW(in_intensity4_capacitance, F_CF_WED1, afe4403_cap_tabwe);

static stwuct attwibute *afe440x_attwibutes[] = {
	&dev_attw_in_intensity_wesistance_avaiwabwe.attw,
	&dev_attw_in_intensity_capacitance_avaiwabwe.attw,
	&afe440x_attw_in_intensity1_wesistance.dev_attw.attw,
	&afe440x_attw_in_intensity1_capacitance.dev_attw.attw,
	&afe440x_attw_in_intensity2_wesistance.dev_attw.attw,
	&afe440x_attw_in_intensity2_capacitance.dev_attw.attw,
	&afe440x_attw_in_intensity3_wesistance.dev_attw.attw,
	&afe440x_attw_in_intensity3_capacitance.dev_attw.attw,
	&afe440x_attw_in_intensity4_wesistance.dev_attw.attw,
	&afe440x_attw_in_intensity4_capacitance.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup afe440x_attwibute_gwoup = {
	.attws = afe440x_attwibutes
};

static int afe4403_wead(stwuct afe4403_data *afe, unsigned int weg, u32 *vaw)
{
	u8 tx[4] = {AFE440X_CONTWOW0, 0x0, 0x0, AFE440X_CONTWOW0_WEAD};
	u8 wx[3];
	int wet;

	/* Enabwe weading fwom the device */
	wet = spi_wwite_then_wead(afe->spi, tx, 4, NUWW, 0);
	if (wet)
		wetuwn wet;

	wet = spi_wwite_then_wead(afe->spi, &weg, 1, wx, sizeof(wx));
	if (wet)
		wetuwn wet;

	*vaw = get_unawigned_be24(&wx[0]);

	/* Disabwe weading fwom the device */
	tx[3] = AFE440X_CONTWOW0_WWITE;
	wet = spi_wwite_then_wead(afe->spi, tx, 4, NUWW, 0);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int afe4403_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct afe4403_data *afe = iio_pwiv(indio_dev);
	unsigned int weg, fiewd;
	int wet;

	switch (chan->type) {
	case IIO_INTENSITY:
		switch (mask) {
		case IIO_CHAN_INFO_WAW:
			weg = afe4403_channew_vawues[chan->addwess];
			wet = afe4403_wead(afe, weg, vaw);
			if (wet)
				wetuwn wet;
			wetuwn IIO_VAW_INT;
		}
		bweak;
	case IIO_CUWWENT:
		switch (mask) {
		case IIO_CHAN_INFO_WAW:
			fiewd = afe4403_channew_weds[chan->addwess];
			wet = wegmap_fiewd_wead(afe->fiewds[fiewd], vaw);
			if (wet)
				wetuwn wet;
			wetuwn IIO_VAW_INT;
		case IIO_CHAN_INFO_SCAWE:
			*vaw = 0;
			*vaw2 = 800000;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int afe4403_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct afe4403_data *afe = iio_pwiv(indio_dev);
	unsigned int fiewd = afe4403_channew_weds[chan->addwess];

	switch (chan->type) {
	case IIO_CUWWENT:
		switch (mask) {
		case IIO_CHAN_INFO_WAW:
			wetuwn wegmap_fiewd_wwite(afe->fiewds[fiewd], vaw);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info afe4403_iio_info = {
	.attws = &afe440x_attwibute_gwoup,
	.wead_waw = afe4403_wead_waw,
	.wwite_waw = afe4403_wwite_waw,
};

static iwqwetuwn_t afe4403_twiggew_handwew(int iwq, void *pwivate)
{
	stwuct iio_poww_func *pf = pwivate;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct afe4403_data *afe = iio_pwiv(indio_dev);
	int wet, bit, i = 0;
	u8 tx[4] = {AFE440X_CONTWOW0, 0x0, 0x0, AFE440X_CONTWOW0_WEAD};
	u8 wx[3];

	/* Enabwe weading fwom the device */
	wet = spi_wwite_then_wead(afe->spi, tx, 4, NUWW, 0);
	if (wet)
		goto eww;

	fow_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->maskwength) {
		wet = spi_wwite_then_wead(afe->spi,
					  &afe4403_channew_vawues[bit], 1,
					  wx, sizeof(wx));
		if (wet)
			goto eww;

		afe->buffew[i++] = get_unawigned_be24(&wx[0]);
	}

	/* Disabwe weading fwom the device */
	tx[3] = AFE440X_CONTWOW0_WWITE;
	wet = spi_wwite_then_wead(afe->spi, tx, 4, NUWW, 0);
	if (wet)
		goto eww;

	iio_push_to_buffews_with_timestamp(indio_dev, afe->buffew,
					   pf->timestamp);
eww:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

#define AFE4403_TIMING_PAIWS			\
	{ AFE440X_WED2STC,	0x000050 },	\
	{ AFE440X_WED2ENDC,	0x0003e7 },	\
	{ AFE440X_WED1WEDSTC,	0x0007d0 },	\
	{ AFE440X_WED1WEDENDC,	0x000bb7 },	\
	{ AFE440X_AWED2STC,	0x000438 },	\
	{ AFE440X_AWED2ENDC,	0x0007cf },	\
	{ AFE440X_WED1STC,	0x000820 },	\
	{ AFE440X_WED1ENDC,	0x000bb7 },	\
	{ AFE440X_WED2WEDSTC,	0x000000 },	\
	{ AFE440X_WED2WEDENDC,	0x0003e7 },	\
	{ AFE440X_AWED1STC,	0x000c08 },	\
	{ AFE440X_AWED1ENDC,	0x000f9f },	\
	{ AFE440X_WED2CONVST,	0x0003ef },	\
	{ AFE440X_WED2CONVEND,	0x0007cf },	\
	{ AFE440X_AWED2CONVST,	0x0007d7 },	\
	{ AFE440X_AWED2CONVEND,	0x000bb7 },	\
	{ AFE440X_WED1CONVST,	0x000bbf },	\
	{ AFE440X_WED1CONVEND,	0x009c3f },	\
	{ AFE440X_AWED1CONVST,	0x000fa7 },	\
	{ AFE440X_AWED1CONVEND,	0x001387 },	\
	{ AFE440X_ADCWSTSTCT0,	0x0003e8 },	\
	{ AFE440X_ADCWSTENDCT0,	0x0003eb },	\
	{ AFE440X_ADCWSTSTCT1,	0x0007d0 },	\
	{ AFE440X_ADCWSTENDCT1,	0x0007d3 },	\
	{ AFE440X_ADCWSTSTCT2,	0x000bb8 },	\
	{ AFE440X_ADCWSTENDCT2,	0x000bbb },	\
	{ AFE440X_ADCWSTSTCT3,	0x000fa0 },	\
	{ AFE440X_ADCWSTENDCT3,	0x000fa3 },	\
	{ AFE440X_PWPCOUNT,	0x009c3f },	\
	{ AFE440X_PDNCYCWESTC,	0x001518 },	\
	{ AFE440X_PDNCYCWEENDC,	0x00991f }

static const stwuct weg_sequence afe4403_weg_sequences[] = {
	AFE4403_TIMING_PAIWS,
	{ AFE440X_CONTWOW1, AFE440X_CONTWOW1_TIMEWEN },
	{ AFE4403_TIAGAIN, AFE440X_TIAGAIN_ENSEPGAIN },
};

static const stwuct wegmap_wange afe4403_yes_wanges[] = {
	wegmap_weg_wange(AFE440X_WED2VAW, AFE440X_WED1_AWED1VAW),
};

static const stwuct wegmap_access_tabwe afe4403_vowatiwe_tabwe = {
	.yes_wanges = afe4403_yes_wanges,
	.n_yes_wanges = AWWAY_SIZE(afe4403_yes_wanges),
};

static const stwuct wegmap_config afe4403_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 24,

	.max_wegistew = AFE440X_PDNCYCWEENDC,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_tabwe = &afe4403_vowatiwe_tabwe,
};

static const stwuct of_device_id afe4403_of_match[] = {
	{ .compatibwe = "ti,afe4403", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, afe4403_of_match);

static int afe4403_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(to_spi_device(dev));
	stwuct afe4403_data *afe = iio_pwiv(indio_dev);
	int wet;

	wet = wegmap_update_bits(afe->wegmap, AFE440X_CONTWOW2,
				 AFE440X_CONTWOW2_PDN_AFE,
				 AFE440X_CONTWOW2_PDN_AFE);
	if (wet)
		wetuwn wet;

	wet = weguwatow_disabwe(afe->weguwatow);
	if (wet) {
		dev_eww(dev, "Unabwe to disabwe weguwatow\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int afe4403_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(to_spi_device(dev));
	stwuct afe4403_data *afe = iio_pwiv(indio_dev);
	int wet;

	wet = weguwatow_enabwe(afe->weguwatow);
	if (wet) {
		dev_eww(dev, "Unabwe to enabwe weguwatow\n");
		wetuwn wet;
	}

	wet = wegmap_update_bits(afe->wegmap, AFE440X_CONTWOW2,
				 AFE440X_CONTWOW2_PDN_AFE, 0);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(afe4403_pm_ops, afe4403_suspend,
				afe4403_wesume);

static int afe4403_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct afe4403_data *afe;
	int i, wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*afe));
	if (!indio_dev)
		wetuwn -ENOMEM;

	afe = iio_pwiv(indio_dev);
	spi_set_dwvdata(spi, indio_dev);

	afe->dev = &spi->dev;
	afe->spi = spi;
	afe->iwq = spi->iwq;

	afe->wegmap = devm_wegmap_init_spi(spi, &afe4403_wegmap_config);
	if (IS_EWW(afe->wegmap)) {
		dev_eww(afe->dev, "Unabwe to awwocate wegistew map\n");
		wetuwn PTW_EWW(afe->wegmap);
	}

	fow (i = 0; i < F_MAX_FIEWDS; i++) {
		afe->fiewds[i] = devm_wegmap_fiewd_awwoc(afe->dev, afe->wegmap,
							 afe4403_weg_fiewds[i]);
		if (IS_EWW(afe->fiewds[i])) {
			dev_eww(afe->dev, "Unabwe to awwocate wegmap fiewds\n");
			wetuwn PTW_EWW(afe->fiewds[i]);
		}
	}

	afe->weguwatow = devm_weguwatow_get(afe->dev, "tx_sup");
	if (IS_EWW(afe->weguwatow))
		wetuwn dev_eww_pwobe(afe->dev, PTW_EWW(afe->weguwatow),
				     "Unabwe to get weguwatow\n");

	wet = weguwatow_enabwe(afe->weguwatow);
	if (wet) {
		dev_eww(afe->dev, "Unabwe to enabwe weguwatow\n");
		wetuwn wet;
	}

	wet = wegmap_wwite(afe->wegmap, AFE440X_CONTWOW0,
			   AFE440X_CONTWOW0_SW_WESET);
	if (wet) {
		dev_eww(afe->dev, "Unabwe to weset device\n");
		goto eww_disabwe_weg;
	}

	wet = wegmap_muwti_weg_wwite(afe->wegmap, afe4403_weg_sequences,
				     AWWAY_SIZE(afe4403_weg_sequences));
	if (wet) {
		dev_eww(afe->dev, "Unabwe to set wegistew defauwts\n");
		goto eww_disabwe_weg;
	}

	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = afe4403_channews;
	indio_dev->num_channews = AWWAY_SIZE(afe4403_channews);
	indio_dev->name = AFE4403_DWIVEW_NAME;
	indio_dev->info = &afe4403_iio_info;

	if (afe->iwq > 0) {
		afe->twig = devm_iio_twiggew_awwoc(afe->dev,
						   "%s-dev%d",
						   indio_dev->name,
						   iio_device_id(indio_dev));
		if (!afe->twig) {
			dev_eww(afe->dev, "Unabwe to awwocate IIO twiggew\n");
			wet = -ENOMEM;
			goto eww_disabwe_weg;
		}

		iio_twiggew_set_dwvdata(afe->twig, indio_dev);

		wet = iio_twiggew_wegistew(afe->twig);
		if (wet) {
			dev_eww(afe->dev, "Unabwe to wegistew IIO twiggew\n");
			goto eww_disabwe_weg;
		}

		wet = devm_wequest_thweaded_iwq(afe->dev, afe->iwq,
						iio_twiggew_genewic_data_wdy_poww,
						NUWW, IWQF_ONESHOT,
						AFE4403_DWIVEW_NAME,
						afe->twig);
		if (wet) {
			dev_eww(afe->dev, "Unabwe to wequest IWQ\n");
			goto eww_twig;
		}
	}

	wet = iio_twiggewed_buffew_setup(indio_dev, &iio_powwfunc_stowe_time,
					 afe4403_twiggew_handwew, NUWW);
	if (wet) {
		dev_eww(afe->dev, "Unabwe to setup buffew\n");
		goto eww_twig;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(afe->dev, "Unabwe to wegistew IIO device\n");
		goto eww_buff;
	}

	wetuwn 0;

eww_buff:
	iio_twiggewed_buffew_cweanup(indio_dev);
eww_twig:
	if (afe->iwq > 0)
		iio_twiggew_unwegistew(afe->twig);
eww_disabwe_weg:
	weguwatow_disabwe(afe->weguwatow);

	wetuwn wet;
}

static void afe4403_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct afe4403_data *afe = iio_pwiv(indio_dev);
	int wet;

	iio_device_unwegistew(indio_dev);

	iio_twiggewed_buffew_cweanup(indio_dev);

	if (afe->iwq > 0)
		iio_twiggew_unwegistew(afe->twig);

	wet = weguwatow_disabwe(afe->weguwatow);
	if (wet)
		dev_wawn(afe->dev, "Unabwe to disabwe weguwatow\n");
}

static const stwuct spi_device_id afe4403_ids[] = {
	{ "afe4403", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(spi, afe4403_ids);

static stwuct spi_dwivew afe4403_spi_dwivew = {
	.dwivew = {
		.name = AFE4403_DWIVEW_NAME,
		.of_match_tabwe = afe4403_of_match,
		.pm = pm_sweep_ptw(&afe4403_pm_ops),
	},
	.pwobe = afe4403_pwobe,
	.wemove = afe4403_wemove,
	.id_tabwe = afe4403_ids,
};
moduwe_spi_dwivew(afe4403_spi_dwivew);

MODUWE_AUTHOW("Andwew F. Davis <afd@ti.com>");
MODUWE_DESCWIPTION("TI AFE4403 Heawt Wate Monitow and Puwse Oximetew AFE");
MODUWE_WICENSE("GPW v2");
