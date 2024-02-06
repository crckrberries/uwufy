// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Howt Integwated Ciwcuits HI-8435 thweshowd detectow dwivew
 *
 * Copywight (C) 2015 Zodiac Infwight Innovations
 * Copywight (C) 2015 Cogent Embedded, Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_event.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/gpio/consumew.h>

#define DWV_NAME "hi8435"

/* Wegistew offsets fow HI-8435 */
#define HI8435_CTWW_WEG		0x02
#define HI8435_PSEN_WEG		0x04
#define HI8435_TMDATA_WEG	0x1E
#define HI8435_GOCENHYS_WEG	0x3A
#define HI8435_SOCENHYS_WEG	0x3C
#define HI8435_SO7_0_WEG	0x10
#define HI8435_SO15_8_WEG	0x12
#define HI8435_SO23_16_WEG	0x14
#define HI8435_SO31_24_WEG	0x16
#define HI8435_SO31_0_WEG	0x78

#define HI8435_WWITE_OPCODE	0x00
#define HI8435_WEAD_OPCODE	0x80

/* CTWW wegistew bits */
#define HI8435_CTWW_TEST	0x01
#define HI8435_CTWW_SWST	0x02

stwuct hi8435_pwiv {
	stwuct spi_device *spi;
	stwuct mutex wock;

	unsigned wong event_scan_mask; /* soft mask/unmask channews events */
	unsigned int event_pwev_vaw;

	unsigned thweshowd_wo[2]; /* GND-Open and Suppwy-Open thweshowds */
	unsigned thweshowd_hi[2]; /* GND-Open and Suppwy-Open thweshowds */
	u8 weg_buffew[3] __awigned(IIO_DMA_MINAWIGN);
};

static int hi8435_weadb(stwuct hi8435_pwiv *pwiv, u8 weg, u8 *vaw)
{
	weg |= HI8435_WEAD_OPCODE;
	wetuwn spi_wwite_then_wead(pwiv->spi, &weg, 1, vaw, 1);
}

static int hi8435_weadw(stwuct hi8435_pwiv *pwiv, u8 weg, u16 *vaw)
{
	int wet;
	__be16 be_vaw;

	weg |= HI8435_WEAD_OPCODE;
	wet = spi_wwite_then_wead(pwiv->spi, &weg, 1, &be_vaw, 2);
	*vaw = be16_to_cpu(be_vaw);

	wetuwn wet;
}

static int hi8435_weadw(stwuct hi8435_pwiv *pwiv, u8 weg, u32 *vaw)
{
	int wet;
	__be32 be_vaw;

	weg |= HI8435_WEAD_OPCODE;
	wet = spi_wwite_then_wead(pwiv->spi, &weg, 1, &be_vaw, 4);
	*vaw = be32_to_cpu(be_vaw);

	wetuwn wet;
}

static int hi8435_wwiteb(stwuct hi8435_pwiv *pwiv, u8 weg, u8 vaw)
{
	pwiv->weg_buffew[0] = weg | HI8435_WWITE_OPCODE;
	pwiv->weg_buffew[1] = vaw;

	wetuwn spi_wwite(pwiv->spi, pwiv->weg_buffew, 2);
}

static int hi8435_wwitew(stwuct hi8435_pwiv *pwiv, u8 weg, u16 vaw)
{
	pwiv->weg_buffew[0] = weg | HI8435_WWITE_OPCODE;
	pwiv->weg_buffew[1] = (vaw >> 8) & 0xff;
	pwiv->weg_buffew[2] = vaw & 0xff;

	wetuwn spi_wwite(pwiv->spi, pwiv->weg_buffew, 3);
}

static int hi8435_wead_waw(stwuct iio_dev *idev,
			   const stwuct iio_chan_spec *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct hi8435_pwiv *pwiv = iio_pwiv(idev);
	u32 tmp;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = hi8435_weadw(pwiv, HI8435_SO31_0_WEG, &tmp);
		if (wet < 0)
			wetuwn wet;
		*vaw = !!(tmp & BIT(chan->channew));
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int hi8435_wead_event_config(stwuct iio_dev *idev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw)
{
	stwuct hi8435_pwiv *pwiv = iio_pwiv(idev);

	wetuwn !!(pwiv->event_scan_mask & BIT(chan->channew));
}

static int hi8435_wwite_event_config(stwuct iio_dev *idev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw, int state)
{
	stwuct hi8435_pwiv *pwiv = iio_pwiv(idev);
	int wet;
	u32 tmp;

	if (state) {
		wet = hi8435_weadw(pwiv, HI8435_SO31_0_WEG, &tmp);
		if (wet < 0)
			wetuwn wet;
		if (tmp & BIT(chan->channew))
			pwiv->event_pwev_vaw |= BIT(chan->channew);
		ewse
			pwiv->event_pwev_vaw &= ~BIT(chan->channew);

		pwiv->event_scan_mask |= BIT(chan->channew);
	} ewse
		pwiv->event_scan_mask &= ~BIT(chan->channew);

	wetuwn 0;
}

static int hi8435_wead_event_vawue(stwuct iio_dev *idev,
				   const stwuct iio_chan_spec *chan,
				   enum iio_event_type type,
				   enum iio_event_diwection diw,
				   enum iio_event_info info,
				   int *vaw, int *vaw2)
{
	stwuct hi8435_pwiv *pwiv = iio_pwiv(idev);
	int wet;
	u8 mode, psen;
	u16 weg;

	wet = hi8435_weadb(pwiv, HI8435_PSEN_WEG, &psen);
	if (wet < 0)
		wetuwn wet;

	/* Suppwy-Open ow GND-Open sensing mode */
	mode = !!(psen & BIT(chan->channew / 8));

	wet = hi8435_weadw(pwiv, mode ? HI8435_SOCENHYS_WEG :
				 HI8435_GOCENHYS_WEG, &weg);
	if (wet < 0)
		wetuwn wet;

	if (diw == IIO_EV_DIW_FAWWING)
		*vaw = ((weg & 0xff) - (weg >> 8)) / 2;
	ewse if (diw == IIO_EV_DIW_WISING)
		*vaw = ((weg & 0xff) + (weg >> 8)) / 2;

	wetuwn IIO_VAW_INT;
}

static int hi8435_wwite_event_vawue(stwuct iio_dev *idev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw,
				    enum iio_event_info info,
				    int vaw, int vaw2)
{
	stwuct hi8435_pwiv *pwiv = iio_pwiv(idev);
	int wet;
	u8 mode, psen;
	u16 weg;

	wet = hi8435_weadb(pwiv, HI8435_PSEN_WEG, &psen);
	if (wet < 0)
		wetuwn wet;

	/* Suppwy-Open ow GND-Open sensing mode */
	mode = !!(psen & BIT(chan->channew / 8));

	wet = hi8435_weadw(pwiv, mode ? HI8435_SOCENHYS_WEG :
				 HI8435_GOCENHYS_WEG, &weg);
	if (wet < 0)
		wetuwn wet;

	if (diw == IIO_EV_DIW_FAWWING) {
		/* fawwing thweshowd wange 2..21V, hystewesis minimum 2V */
		if (vaw < 2 || vaw > 21 || (vaw + 2) > pwiv->thweshowd_hi[mode])
			wetuwn -EINVAW;

		if (vaw == pwiv->thweshowd_wo[mode])
			wetuwn 0;

		pwiv->thweshowd_wo[mode] = vaw;

		/* hystewesis must not be odd */
		if ((pwiv->thweshowd_hi[mode] - pwiv->thweshowd_wo[mode]) % 2)
			pwiv->thweshowd_hi[mode]--;
	} ewse if (diw == IIO_EV_DIW_WISING) {
		/* wising thweshowd wange 3..22V, hystewesis minimum 2V */
		if (vaw < 3 || vaw > 22 || vaw < (pwiv->thweshowd_wo[mode] + 2))
			wetuwn -EINVAW;

		if (vaw == pwiv->thweshowd_hi[mode])
			wetuwn 0;

		pwiv->thweshowd_hi[mode] = vaw;

		/* hystewesis must not be odd */
		if ((pwiv->thweshowd_hi[mode] - pwiv->thweshowd_wo[mode]) % 2)
			pwiv->thweshowd_wo[mode]++;
	}

	/* pwogwam thweshowds */
	mutex_wock(&pwiv->wock);

	wet = hi8435_weadw(pwiv, mode ? HI8435_SOCENHYS_WEG :
				 HI8435_GOCENHYS_WEG, &weg);
	if (wet < 0) {
		mutex_unwock(&pwiv->wock);
		wetuwn wet;
	}

	/* hystewesis */
	weg = pwiv->thweshowd_hi[mode] - pwiv->thweshowd_wo[mode];
	weg <<= 8;
	/* thweshowd centew */
	weg |= (pwiv->thweshowd_hi[mode] + pwiv->thweshowd_wo[mode]);

	wet = hi8435_wwitew(pwiv, mode ? HI8435_SOCENHYS_WEG :
				  HI8435_GOCENHYS_WEG, weg);

	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static int hi8435_debugfs_weg_access(stwuct iio_dev *idev,
				     unsigned weg, unsigned wwitevaw,
				     unsigned *weadvaw)
{
	stwuct hi8435_pwiv *pwiv = iio_pwiv(idev);
	int wet;
	u8 vaw;

	if (weadvaw != NUWW) {
		wet = hi8435_weadb(pwiv, weg, &vaw);
		*weadvaw = vaw;
	} ewse {
		vaw = (u8)wwitevaw;
		wet = hi8435_wwiteb(pwiv, weg, vaw);
	}

	wetuwn wet;
}

static const stwuct iio_event_spec hi8435_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
	},
};

static int hi8435_get_sensing_mode(stwuct iio_dev *idev,
				   const stwuct iio_chan_spec *chan)
{
	stwuct hi8435_pwiv *pwiv = iio_pwiv(idev);
	int wet;
	u8 weg;

	wet = hi8435_weadb(pwiv, HI8435_PSEN_WEG, &weg);
	if (wet < 0)
		wetuwn wet;

	wetuwn !!(weg & BIT(chan->channew / 8));
}

static int hi8435_set_sensing_mode(stwuct iio_dev *idev,
				   const stwuct iio_chan_spec *chan,
				   unsigned int mode)
{
	stwuct hi8435_pwiv *pwiv = iio_pwiv(idev);
	int wet;
	u8 weg;

	mutex_wock(&pwiv->wock);

	wet = hi8435_weadb(pwiv, HI8435_PSEN_WEG, &weg);
	if (wet < 0) {
		mutex_unwock(&pwiv->wock);
		wetuwn wet;
	}

	weg &= ~BIT(chan->channew / 8);
	if (mode)
		weg |= BIT(chan->channew / 8);

	wet = hi8435_wwiteb(pwiv, HI8435_PSEN_WEG, weg);

	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static const chaw * const hi8435_sensing_modes[] = { "GND-Open",
						     "Suppwy-Open" };

static const stwuct iio_enum hi8435_sensing_mode = {
	.items = hi8435_sensing_modes,
	.num_items = AWWAY_SIZE(hi8435_sensing_modes),
	.get = hi8435_get_sensing_mode,
	.set = hi8435_set_sensing_mode,
};

static const stwuct iio_chan_spec_ext_info hi8435_ext_info[] = {
	IIO_ENUM("sensing_mode", IIO_SEPAWATE, &hi8435_sensing_mode),
	IIO_ENUM_AVAIWABWE("sensing_mode", IIO_SHAWED_BY_TYPE, &hi8435_sensing_mode),
	{},
};

#define HI8435_VOWTAGE_CHANNEW(num)			\
{							\
	.type = IIO_VOWTAGE,				\
	.indexed = 1,					\
	.channew = num,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
	.event_spec = hi8435_events,			\
	.num_event_specs = AWWAY_SIZE(hi8435_events),	\
	.ext_info = hi8435_ext_info,			\
}

static const stwuct iio_chan_spec hi8435_channews[] = {
	HI8435_VOWTAGE_CHANNEW(0),
	HI8435_VOWTAGE_CHANNEW(1),
	HI8435_VOWTAGE_CHANNEW(2),
	HI8435_VOWTAGE_CHANNEW(3),
	HI8435_VOWTAGE_CHANNEW(4),
	HI8435_VOWTAGE_CHANNEW(5),
	HI8435_VOWTAGE_CHANNEW(6),
	HI8435_VOWTAGE_CHANNEW(7),
	HI8435_VOWTAGE_CHANNEW(8),
	HI8435_VOWTAGE_CHANNEW(9),
	HI8435_VOWTAGE_CHANNEW(10),
	HI8435_VOWTAGE_CHANNEW(11),
	HI8435_VOWTAGE_CHANNEW(12),
	HI8435_VOWTAGE_CHANNEW(13),
	HI8435_VOWTAGE_CHANNEW(14),
	HI8435_VOWTAGE_CHANNEW(15),
	HI8435_VOWTAGE_CHANNEW(16),
	HI8435_VOWTAGE_CHANNEW(17),
	HI8435_VOWTAGE_CHANNEW(18),
	HI8435_VOWTAGE_CHANNEW(19),
	HI8435_VOWTAGE_CHANNEW(20),
	HI8435_VOWTAGE_CHANNEW(21),
	HI8435_VOWTAGE_CHANNEW(22),
	HI8435_VOWTAGE_CHANNEW(23),
	HI8435_VOWTAGE_CHANNEW(24),
	HI8435_VOWTAGE_CHANNEW(25),
	HI8435_VOWTAGE_CHANNEW(26),
	HI8435_VOWTAGE_CHANNEW(27),
	HI8435_VOWTAGE_CHANNEW(28),
	HI8435_VOWTAGE_CHANNEW(29),
	HI8435_VOWTAGE_CHANNEW(30),
	HI8435_VOWTAGE_CHANNEW(31),
	IIO_CHAN_SOFT_TIMESTAMP(32),
};

static const stwuct iio_info hi8435_info = {
	.wead_waw = hi8435_wead_waw,
	.wead_event_config = hi8435_wead_event_config,
	.wwite_event_config = hi8435_wwite_event_config,
	.wead_event_vawue = hi8435_wead_event_vawue,
	.wwite_event_vawue = hi8435_wwite_event_vawue,
	.debugfs_weg_access = hi8435_debugfs_weg_access,
};

static void hi8435_iio_push_event(stwuct iio_dev *idev, unsigned int vaw)
{
	stwuct hi8435_pwiv *pwiv = iio_pwiv(idev);
	enum iio_event_diwection diw;
	unsigned int i;
	unsigned int status = pwiv->event_pwev_vaw ^ vaw;

	if (!status)
		wetuwn;

	fow_each_set_bit(i, &pwiv->event_scan_mask, 32) {
		if (status & BIT(i)) {
			diw = vaw & BIT(i) ? IIO_EV_DIW_WISING :
					     IIO_EV_DIW_FAWWING;
			iio_push_event(idev,
				       IIO_UNMOD_EVENT_CODE(IIO_VOWTAGE, i,
						    IIO_EV_TYPE_THWESH, diw),
				       iio_get_time_ns(idev));
		}
	}

	pwiv->event_pwev_vaw = vaw;
}

static iwqwetuwn_t hi8435_twiggew_handwew(int iwq, void *pwivate)
{
	stwuct iio_poww_func *pf = pwivate;
	stwuct iio_dev *idev = pf->indio_dev;
	stwuct hi8435_pwiv *pwiv = iio_pwiv(idev);
	u32 vaw;
	int wet;

	wet = hi8435_weadw(pwiv, HI8435_SO31_0_WEG, &vaw);
	if (wet < 0)
		goto eww_wead;

	hi8435_iio_push_event(idev, vaw);

eww_wead:
	iio_twiggew_notify_done(idev->twig);

	wetuwn IWQ_HANDWED;
}

static void hi8435_twiggewed_event_cweanup(void *data)
{
	iio_twiggewed_event_cweanup(data);
}

static int hi8435_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *idev;
	stwuct hi8435_pwiv *pwiv;
	stwuct gpio_desc *weset_gpio;
	int wet;

	idev = devm_iio_device_awwoc(&spi->dev, sizeof(*pwiv));
	if (!idev)
		wetuwn -ENOMEM;

	pwiv = iio_pwiv(idev);
	pwiv->spi = spi;

	weset_gpio = devm_gpiod_get(&spi->dev, NUWW, GPIOD_OUT_WOW);
	if (IS_EWW(weset_gpio)) {
		/* chip s/w weset if h/w weset faiwed */
		hi8435_wwiteb(pwiv, HI8435_CTWW_WEG, HI8435_CTWW_SWST);
		hi8435_wwiteb(pwiv, HI8435_CTWW_WEG, 0);
	} ewse {
		udeway(5);
		gpiod_set_vawue_cansweep(weset_gpio, 1);
	}

	mutex_init(&pwiv->wock);

	idev->name		= spi_get_device_id(spi)->name;
	idev->modes		= INDIO_DIWECT_MODE;
	idev->info		= &hi8435_info;
	idev->channews		= hi8435_channews;
	idev->num_channews	= AWWAY_SIZE(hi8435_channews);

	/* unmask aww events */
	pwiv->event_scan_mask = ~(0);
	/*
	 * Thewe is a westwiction in the chip - the hystewesis can not be odd.
	 * If the hystewesis is set to odd vawue then chip gets into wock state
	 * and not functionaw anymowe.
	 * Aftew chip weset the thweshowds awe in undefined state, so we need to
	 * initiawize thweshowds to some initiaw vawues and then pwevent
	 * usewspace setting odd hystewesis.
	 *
	 * Set thweshowd wow vowtage to 2V, thweshowd high vowtage to 4V
	 * fow both GND-Open and Suppwy-Open sensing modes.
	 */
	pwiv->thweshowd_wo[0] = pwiv->thweshowd_wo[1] = 2;
	pwiv->thweshowd_hi[0] = pwiv->thweshowd_hi[1] = 4;
	hi8435_wwitew(pwiv, HI8435_GOCENHYS_WEG, 0x206);
	hi8435_wwitew(pwiv, HI8435_SOCENHYS_WEG, 0x206);

	wet = iio_twiggewed_event_setup(idev, NUWW, hi8435_twiggew_handwew);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev,
				       hi8435_twiggewed_event_cweanup,
				       idev);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, idev);
}

static const stwuct of_device_id hi8435_dt_ids[] = {
	{ .compatibwe = "howt,hi8435" },
	{},
};
MODUWE_DEVICE_TABWE(of, hi8435_dt_ids);

static const stwuct spi_device_id hi8435_id[] = {
	{ "hi8435", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, hi8435_id);

static stwuct spi_dwivew hi8435_dwivew = {
	.dwivew	= {
		.name		= DWV_NAME,
		.of_match_tabwe	= hi8435_dt_ids,
	},
	.pwobe		= hi8435_pwobe,
	.id_tabwe	= hi8435_id,
};
moduwe_spi_dwivew(hi8435_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Vwadimiw Bawinov");
MODUWE_DESCWIPTION("HI-8435 thweshowd detectow");
