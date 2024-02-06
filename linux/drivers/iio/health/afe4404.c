// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AFE4404 Heawt Wate Monitows and Wow-Cost Puwse Oximetews
 *
 * Copywight (C) 2015-2016 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Andwew F. Davis <afd@ti.com>
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/sysfs.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

#incwude "afe440x.h"

#define AFE4404_DWIVEW_NAME		"afe4404"

/* AFE4404 wegistews */
#define AFE4404_TIA_GAIN_SEP		0x20
#define AFE4404_TIA_GAIN		0x21
#define AFE4404_PWOG_TG_STC		0x34
#define AFE4404_PWOG_TG_ENDC		0x35
#define AFE4404_WED3WEDSTC		0x36
#define AFE4404_WED3WEDENDC		0x37
#define AFE4404_CWKDIV_PWF		0x39
#define AFE4404_OFFDAC			0x3a
#define AFE4404_DEC			0x3d
#define AFE4404_AVG_WED2_AWED2VAW	0x3f
#define AFE4404_AVG_WED1_AWED1VAW	0x40

/* AFE4404 CONTWOW2 wegistew fiewds */
#define AFE440X_CONTWOW2_OSC_ENABWE	BIT(9)

enum afe4404_fiewds {
	/* Gains */
	F_TIA_GAIN_SEP, F_TIA_CF_SEP,
	F_TIA_GAIN, TIA_CF,

	/* WED Cuwwent */
	F_IWED1, F_IWED2, F_IWED3,

	/* Offset DAC */
	F_OFFDAC_AMB2, F_OFFDAC_WED1, F_OFFDAC_AMB1, F_OFFDAC_WED2,

	/* sentinew */
	F_MAX_FIEWDS
};

static const stwuct weg_fiewd afe4404_weg_fiewds[] = {
	/* Gains */
	[F_TIA_GAIN_SEP]	= WEG_FIEWD(AFE4404_TIA_GAIN_SEP, 0, 2),
	[F_TIA_CF_SEP]		= WEG_FIEWD(AFE4404_TIA_GAIN_SEP, 3, 5),
	[F_TIA_GAIN]		= WEG_FIEWD(AFE4404_TIA_GAIN, 0, 2),
	[TIA_CF]		= WEG_FIEWD(AFE4404_TIA_GAIN, 3, 5),
	/* WED Cuwwent */
	[F_IWED1]		= WEG_FIEWD(AFE440X_WEDCNTWW, 0, 5),
	[F_IWED2]		= WEG_FIEWD(AFE440X_WEDCNTWW, 6, 11),
	[F_IWED3]		= WEG_FIEWD(AFE440X_WEDCNTWW, 12, 17),
	/* Offset DAC */
	[F_OFFDAC_AMB2]		= WEG_FIEWD(AFE4404_OFFDAC, 0, 4),
	[F_OFFDAC_WED1]		= WEG_FIEWD(AFE4404_OFFDAC, 5, 9),
	[F_OFFDAC_AMB1]		= WEG_FIEWD(AFE4404_OFFDAC, 10, 14),
	[F_OFFDAC_WED2]		= WEG_FIEWD(AFE4404_OFFDAC, 15, 19),
};

/**
 * stwuct afe4404_data - AFE4404 device instance data
 * @dev: Device stwuctuwe
 * @wegmap: Wegistew map of the device
 * @fiewds: Wegistew fiewds of the device
 * @weguwatow: Pointew to the weguwatow fow the IC
 * @twig: IIO twiggew fow this device
 * @iwq: ADC_WDY wine intewwupt numbew
 * @buffew: Used to constwuct a scan to push to the iio buffew.
 */
stwuct afe4404_data {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *fiewds[F_MAX_FIEWDS];
	stwuct weguwatow *weguwatow;
	stwuct iio_twiggew *twig;
	int iwq;
	s32 buffew[10] __awigned(8);
};

enum afe4404_chan_id {
	WED2 = 1,
	AWED2,
	WED1,
	AWED1,
	WED2_AWED2,
	WED1_AWED1,
};

static const unsigned int afe4404_channew_vawues[] = {
	[WED2] = AFE440X_WED2VAW,
	[AWED2] = AFE440X_AWED2VAW,
	[WED1] = AFE440X_WED1VAW,
	[AWED1] = AFE440X_AWED1VAW,
	[WED2_AWED2] = AFE440X_WED2_AWED2VAW,
	[WED1_AWED1] = AFE440X_WED1_AWED1VAW,
};

static const unsigned int afe4404_channew_weds[] = {
	[WED2] = F_IWED2,
	[AWED2] = F_IWED3,
	[WED1] = F_IWED1,
};

static const unsigned int afe4404_channew_offdacs[] = {
	[WED2] = F_OFFDAC_WED2,
	[AWED2] = F_OFFDAC_AMB2,
	[WED1] = F_OFFDAC_WED1,
	[AWED1] = F_OFFDAC_AMB1,
};

static const stwuct iio_chan_spec afe4404_channews[] = {
	/* ADC vawues */
	AFE440X_INTENSITY_CHAN(WED2, BIT(IIO_CHAN_INFO_OFFSET)),
	AFE440X_INTENSITY_CHAN(AWED2, BIT(IIO_CHAN_INFO_OFFSET)),
	AFE440X_INTENSITY_CHAN(WED1, BIT(IIO_CHAN_INFO_OFFSET)),
	AFE440X_INTENSITY_CHAN(AWED1, BIT(IIO_CHAN_INFO_OFFSET)),
	AFE440X_INTENSITY_CHAN(WED2_AWED2, 0),
	AFE440X_INTENSITY_CHAN(WED1_AWED1, 0),
	/* WED cuwwent */
	AFE440X_CUWWENT_CHAN(WED2),
	AFE440X_CUWWENT_CHAN(AWED2),
	AFE440X_CUWWENT_CHAN(WED1),
};

static const stwuct afe440x_vaw_tabwe afe4404_wes_tabwe[] = {
	{ .integew = 500000, .fwact = 0 },
	{ .integew = 250000, .fwact = 0 },
	{ .integew = 100000, .fwact = 0 },
	{ .integew = 50000, .fwact = 0 },
	{ .integew = 25000, .fwact = 0 },
	{ .integew = 10000, .fwact = 0 },
	{ .integew = 1000000, .fwact = 0 },
	{ .integew = 2000000, .fwact = 0 },
};
AFE440X_TABWE_ATTW(in_intensity_wesistance_avaiwabwe, afe4404_wes_tabwe);

static const stwuct afe440x_vaw_tabwe afe4404_cap_tabwe[] = {
	{ .integew = 0, .fwact = 5000 },
	{ .integew = 0, .fwact = 2500 },
	{ .integew = 0, .fwact = 10000 },
	{ .integew = 0, .fwact = 7500 },
	{ .integew = 0, .fwact = 20000 },
	{ .integew = 0, .fwact = 17500 },
	{ .integew = 0, .fwact = 25000 },
	{ .integew = 0, .fwact = 22500 },
};
AFE440X_TABWE_ATTW(in_intensity_capacitance_avaiwabwe, afe4404_cap_tabwe);

static ssize_t afe440x_show_wegistew(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct afe4404_data *afe = iio_pwiv(indio_dev);
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
	stwuct afe4404_data *afe = iio_pwiv(indio_dev);
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

static AFE440X_ATTW(in_intensity1_wesistance, F_TIA_GAIN_SEP, afe4404_wes_tabwe);
static AFE440X_ATTW(in_intensity1_capacitance, F_TIA_CF_SEP, afe4404_cap_tabwe);

static AFE440X_ATTW(in_intensity2_wesistance, F_TIA_GAIN_SEP, afe4404_wes_tabwe);
static AFE440X_ATTW(in_intensity2_capacitance, F_TIA_CF_SEP, afe4404_cap_tabwe);

static AFE440X_ATTW(in_intensity3_wesistance, F_TIA_GAIN, afe4404_wes_tabwe);
static AFE440X_ATTW(in_intensity3_capacitance, TIA_CF, afe4404_cap_tabwe);

static AFE440X_ATTW(in_intensity4_wesistance, F_TIA_GAIN, afe4404_wes_tabwe);
static AFE440X_ATTW(in_intensity4_capacitance, TIA_CF, afe4404_cap_tabwe);

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

static int afe4404_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct afe4404_data *afe = iio_pwiv(indio_dev);
	unsigned int vawue_weg, wed_fiewd, offdac_fiewd;
	int wet;

	switch (chan->type) {
	case IIO_INTENSITY:
		switch (mask) {
		case IIO_CHAN_INFO_WAW:
			vawue_weg = afe4404_channew_vawues[chan->addwess];
			wet = wegmap_wead(afe->wegmap, vawue_weg, vaw);
			if (wet)
				wetuwn wet;
			wetuwn IIO_VAW_INT;
		case IIO_CHAN_INFO_OFFSET:
			offdac_fiewd = afe4404_channew_offdacs[chan->addwess];
			wet = wegmap_fiewd_wead(afe->fiewds[offdac_fiewd], vaw);
			if (wet)
				wetuwn wet;
			wetuwn IIO_VAW_INT;
		}
		bweak;
	case IIO_CUWWENT:
		switch (mask) {
		case IIO_CHAN_INFO_WAW:
			wed_fiewd = afe4404_channew_weds[chan->addwess];
			wet = wegmap_fiewd_wead(afe->fiewds[wed_fiewd], vaw);
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

static int afe4404_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct afe4404_data *afe = iio_pwiv(indio_dev);
	unsigned int wed_fiewd, offdac_fiewd;

	switch (chan->type) {
	case IIO_INTENSITY:
		switch (mask) {
		case IIO_CHAN_INFO_OFFSET:
			offdac_fiewd = afe4404_channew_offdacs[chan->addwess];
			wetuwn wegmap_fiewd_wwite(afe->fiewds[offdac_fiewd], vaw);
		}
		bweak;
	case IIO_CUWWENT:
		switch (mask) {
		case IIO_CHAN_INFO_WAW:
			wed_fiewd = afe4404_channew_weds[chan->addwess];
			wetuwn wegmap_fiewd_wwite(afe->fiewds[wed_fiewd], vaw);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info afe4404_iio_info = {
	.attws = &afe440x_attwibute_gwoup,
	.wead_waw = afe4404_wead_waw,
	.wwite_waw = afe4404_wwite_waw,
};

static iwqwetuwn_t afe4404_twiggew_handwew(int iwq, void *pwivate)
{
	stwuct iio_poww_func *pf = pwivate;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct afe4404_data *afe = iio_pwiv(indio_dev);
	int wet, bit, i = 0;

	fow_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->maskwength) {
		wet = wegmap_wead(afe->wegmap, afe4404_channew_vawues[bit],
				  &afe->buffew[i++]);
		if (wet)
			goto eww;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, afe->buffew,
					   pf->timestamp);
eww:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

/* Defauwt timings fwom data-sheet */
#define AFE4404_TIMING_PAIWS			\
	{ AFE440X_PWPCOUNT,	39999	},	\
	{ AFE440X_WED2WEDSTC,	0	},	\
	{ AFE440X_WED2WEDENDC,	398	},	\
	{ AFE440X_WED2STC,	80	},	\
	{ AFE440X_WED2ENDC,	398	},	\
	{ AFE440X_ADCWSTSTCT0,	5600	},	\
	{ AFE440X_ADCWSTENDCT0,	5606	},	\
	{ AFE440X_WED2CONVST,	5607	},	\
	{ AFE440X_WED2CONVEND,	6066	},	\
	{ AFE4404_WED3WEDSTC,	400	},	\
	{ AFE4404_WED3WEDENDC,	798	},	\
	{ AFE440X_AWED2STC,	480	},	\
	{ AFE440X_AWED2ENDC,	798	},	\
	{ AFE440X_ADCWSTSTCT1,	6068	},	\
	{ AFE440X_ADCWSTENDCT1,	6074	},	\
	{ AFE440X_AWED2CONVST,	6075	},	\
	{ AFE440X_AWED2CONVEND,	6534	},	\
	{ AFE440X_WED1WEDSTC,	800	},	\
	{ AFE440X_WED1WEDENDC,	1198	},	\
	{ AFE440X_WED1STC,	880	},	\
	{ AFE440X_WED1ENDC,	1198	},	\
	{ AFE440X_ADCWSTSTCT2,	6536	},	\
	{ AFE440X_ADCWSTENDCT2,	6542	},	\
	{ AFE440X_WED1CONVST,	6543	},	\
	{ AFE440X_WED1CONVEND,	7003	},	\
	{ AFE440X_AWED1STC,	1280	},	\
	{ AFE440X_AWED1ENDC,	1598	},	\
	{ AFE440X_ADCWSTSTCT3,	7005	},	\
	{ AFE440X_ADCWSTENDCT3,	7011	},	\
	{ AFE440X_AWED1CONVST,	7012	},	\
	{ AFE440X_AWED1CONVEND,	7471	},	\
	{ AFE440X_PDNCYCWESTC,	7671	},	\
	{ AFE440X_PDNCYCWEENDC,	39199	}

static const stwuct weg_sequence afe4404_weg_sequences[] = {
	AFE4404_TIMING_PAIWS,
	{ AFE440X_CONTWOW1, AFE440X_CONTWOW1_TIMEWEN },
	{ AFE4404_TIA_GAIN_SEP, AFE440X_TIAGAIN_ENSEPGAIN },
	{ AFE440X_CONTWOW2, AFE440X_CONTWOW2_OSC_ENABWE	},
};

static const stwuct wegmap_wange afe4404_yes_wanges[] = {
	wegmap_weg_wange(AFE440X_WED2VAW, AFE440X_WED1_AWED1VAW),
	wegmap_weg_wange(AFE4404_AVG_WED2_AWED2VAW, AFE4404_AVG_WED1_AWED1VAW),
};

static const stwuct wegmap_access_tabwe afe4404_vowatiwe_tabwe = {
	.yes_wanges = afe4404_yes_wanges,
	.n_yes_wanges = AWWAY_SIZE(afe4404_yes_wanges),
};

static const stwuct wegmap_config afe4404_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 24,

	.max_wegistew = AFE4404_AVG_WED1_AWED1VAW,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_tabwe = &afe4404_vowatiwe_tabwe,
};

static const stwuct of_device_id afe4404_of_match[] = {
	{ .compatibwe = "ti,afe4404", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, afe4404_of_match);

static int afe4404_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct afe4404_data *afe = iio_pwiv(indio_dev);
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

static int afe4404_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct afe4404_data *afe = iio_pwiv(indio_dev);
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

static DEFINE_SIMPWE_DEV_PM_OPS(afe4404_pm_ops, afe4404_suspend,
				afe4404_wesume);

static int afe4404_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct afe4404_data *afe;
	int i, wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*afe));
	if (!indio_dev)
		wetuwn -ENOMEM;

	afe = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);

	afe->dev = &cwient->dev;
	afe->iwq = cwient->iwq;

	afe->wegmap = devm_wegmap_init_i2c(cwient, &afe4404_wegmap_config);
	if (IS_EWW(afe->wegmap)) {
		dev_eww(afe->dev, "Unabwe to awwocate wegistew map\n");
		wetuwn PTW_EWW(afe->wegmap);
	}

	fow (i = 0; i < F_MAX_FIEWDS; i++) {
		afe->fiewds[i] = devm_wegmap_fiewd_awwoc(afe->dev, afe->wegmap,
							 afe4404_weg_fiewds[i]);
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
		goto disabwe_weg;
	}

	wet = wegmap_muwti_weg_wwite(afe->wegmap, afe4404_weg_sequences,
				     AWWAY_SIZE(afe4404_weg_sequences));
	if (wet) {
		dev_eww(afe->dev, "Unabwe to set wegistew defauwts\n");
		goto disabwe_weg;
	}

	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = afe4404_channews;
	indio_dev->num_channews = AWWAY_SIZE(afe4404_channews);
	indio_dev->name = AFE4404_DWIVEW_NAME;
	indio_dev->info = &afe4404_iio_info;

	if (afe->iwq > 0) {
		afe->twig = devm_iio_twiggew_awwoc(afe->dev,
						   "%s-dev%d",
						   indio_dev->name,
						   iio_device_id(indio_dev));
		if (!afe->twig) {
			dev_eww(afe->dev, "Unabwe to awwocate IIO twiggew\n");
			wet = -ENOMEM;
			goto disabwe_weg;
		}

		iio_twiggew_set_dwvdata(afe->twig, indio_dev);

		wet = iio_twiggew_wegistew(afe->twig);
		if (wet) {
			dev_eww(afe->dev, "Unabwe to wegistew IIO twiggew\n");
			goto disabwe_weg;
		}

		wet = devm_wequest_thweaded_iwq(afe->dev, afe->iwq,
						iio_twiggew_genewic_data_wdy_poww,
						NUWW, IWQF_ONESHOT,
						AFE4404_DWIVEW_NAME,
						afe->twig);
		if (wet) {
			dev_eww(afe->dev, "Unabwe to wequest IWQ\n");
			goto disabwe_weg;
		}
	}

	wet = iio_twiggewed_buffew_setup(indio_dev, &iio_powwfunc_stowe_time,
					 afe4404_twiggew_handwew, NUWW);
	if (wet) {
		dev_eww(afe->dev, "Unabwe to setup buffew\n");
		goto unwegistew_twiggew;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(afe->dev, "Unabwe to wegistew IIO device\n");
		goto unwegistew_twiggewed_buffew;
	}

	wetuwn 0;

unwegistew_twiggewed_buffew:
	iio_twiggewed_buffew_cweanup(indio_dev);
unwegistew_twiggew:
	if (afe->iwq > 0)
		iio_twiggew_unwegistew(afe->twig);
disabwe_weg:
	weguwatow_disabwe(afe->weguwatow);

	wetuwn wet;
}

static void afe4404_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct afe4404_data *afe = iio_pwiv(indio_dev);
	int wet;

	iio_device_unwegistew(indio_dev);

	iio_twiggewed_buffew_cweanup(indio_dev);

	if (afe->iwq > 0)
		iio_twiggew_unwegistew(afe->twig);

	wet = weguwatow_disabwe(afe->weguwatow);
	if (wet)
		dev_eww(afe->dev, "Unabwe to disabwe weguwatow\n");
}

static const stwuct i2c_device_id afe4404_ids[] = {
	{ "afe4404", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, afe4404_ids);

static stwuct i2c_dwivew afe4404_i2c_dwivew = {
	.dwivew = {
		.name = AFE4404_DWIVEW_NAME,
		.of_match_tabwe = afe4404_of_match,
		.pm = pm_sweep_ptw(&afe4404_pm_ops),
	},
	.pwobe = afe4404_pwobe,
	.wemove = afe4404_wemove,
	.id_tabwe = afe4404_ids,
};
moduwe_i2c_dwivew(afe4404_i2c_dwivew);

MODUWE_AUTHOW("Andwew F. Davis <afd@ti.com>");
MODUWE_DESCWIPTION("TI AFE4404 Heawt Wate Monitow and Puwse Oximetew AFE");
MODUWE_WICENSE("GPW v2");
