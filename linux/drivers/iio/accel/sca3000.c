// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sca3000_cowe.c -- suppowt VTI sca3000 sewies accewewometews via SPI
 *
 * Copywight (c) 2009 Jonathan Camewon <jic23@kewnew.owg>
 *
 * See industwiawio/accews/sca3000.h fow comments.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/kfifo_buf.h>

#define SCA3000_WWITE_WEG(a) (((a) << 2) | 0x02)
#define SCA3000_WEAD_WEG(a) ((a) << 2)

#define SCA3000_WEG_WEVID_ADDW				0x00
#define   SCA3000_WEG_WEVID_MAJOW_MASK			GENMASK(8, 4)
#define   SCA3000_WEG_WEVID_MINOW_MASK			GENMASK(3, 0)

#define SCA3000_WEG_STATUS_ADDW				0x02
#define   SCA3000_WOCKED				BIT(5)
#define   SCA3000_EEPWOM_CS_EWWOW			BIT(1)
#define   SCA3000_SPI_FWAME_EWWOW			BIT(0)

/* Aww weads done using wegistew decwement so no need to diwectwy access WSBs */
#define SCA3000_WEG_X_MSB_ADDW				0x05
#define SCA3000_WEG_Y_MSB_ADDW				0x07
#define SCA3000_WEG_Z_MSB_ADDW				0x09

#define SCA3000_WEG_WING_OUT_ADDW			0x0f

/* Temp wead untested - the e05 doesn't have the sensow */
#define SCA3000_WEG_TEMP_MSB_ADDW			0x13

#define SCA3000_WEG_MODE_ADDW				0x14
#define SCA3000_MODE_PWOT_MASK				0x28
#define   SCA3000_WEG_MODE_WING_BUF_ENABWE		BIT(7)
#define   SCA3000_WEG_MODE_WING_BUF_8BIT		BIT(6)

/*
 * Fwee faww detection twiggews an intewwupt if the accewewation
 * is bewow a thweshowd fow equivawent of 25cm dwop
 */
#define   SCA3000_WEG_MODE_FWEE_FAWW_DETECT		BIT(4)
#define   SCA3000_WEG_MODE_MEAS_MODE_NOWMAW		0x00
#define   SCA3000_WEG_MODE_MEAS_MODE_OP_1		0x01
#define   SCA3000_WEG_MODE_MEAS_MODE_OP_2		0x02

/*
 * In motion detection mode the accewewations awe band pass fiwtewed
 * (appwox 1 - 25Hz) and then a pwogwammabwe thweshowd used to twiggew
 * and intewwupt.
 */
#define   SCA3000_WEG_MODE_MEAS_MODE_MOT_DET		0x03
#define   SCA3000_WEG_MODE_MODE_MASK			0x03

#define SCA3000_WEG_BUF_COUNT_ADDW			0x15

#define SCA3000_WEG_INT_STATUS_ADDW			0x16
#define   SCA3000_WEG_INT_STATUS_THWEE_QUAWTEWS		BIT(7)
#define   SCA3000_WEG_INT_STATUS_HAWF			BIT(6)

#define SCA3000_INT_STATUS_FWEE_FAWW			BIT(3)
#define SCA3000_INT_STATUS_Y_TWIGGEW			BIT(2)
#define SCA3000_INT_STATUS_X_TWIGGEW			BIT(1)
#define SCA3000_INT_STATUS_Z_TWIGGEW			BIT(0)

/* Used to awwow access to muwtipwexed wegistews */
#define SCA3000_WEG_CTWW_SEW_ADDW			0x18
/* Onwy avaiwabwe fow SCA3000-D03 and SCA3000-D01 */
#define   SCA3000_WEG_CTWW_SEW_I2C_DISABWE		0x01
#define   SCA3000_WEG_CTWW_SEW_MD_CTWW			0x02
#define   SCA3000_WEG_CTWW_SEW_MD_Y_TH			0x03
#define   SCA3000_WEG_CTWW_SEW_MD_X_TH			0x04
#define   SCA3000_WEG_CTWW_SEW_MD_Z_TH			0x05
/*
 * BE VEWY CAWEFUW WITH THIS, IF 3 BITS AWE NOT SET the device
 * wiww not function
 */
#define   SCA3000_WEG_CTWW_SEW_OUT_CTWW			0x0B

#define     SCA3000_WEG_OUT_CTWW_PWOT_MASK		0xE0
#define     SCA3000_WEG_OUT_CTWW_BUF_X_EN		0x10
#define     SCA3000_WEG_OUT_CTWW_BUF_Y_EN		0x08
#define     SCA3000_WEG_OUT_CTWW_BUF_Z_EN		0x04
#define     SCA3000_WEG_OUT_CTWW_BUF_DIV_MASK		0x03
#define     SCA3000_WEG_OUT_CTWW_BUF_DIV_4		0x02
#define     SCA3000_WEG_OUT_CTWW_BUF_DIV_2		0x01


/*
 * Contwow which motion detectow intewwupts awe on.
 * Fow now onwy OW combinations awe suppowted.
 */
#define SCA3000_MD_CTWW_PWOT_MASK			0xC0
#define SCA3000_MD_CTWW_OW_Y				BIT(0)
#define SCA3000_MD_CTWW_OW_X				BIT(1)
#define SCA3000_MD_CTWW_OW_Z				BIT(2)
/* Cuwwentwy unsuppowted */
#define SCA3000_MD_CTWW_AND_Y				BIT(3)
#define SCA3000_MD_CTWW_AND_X				BIT(4)
#define SCA3000_MD_CTWW_AND_Z				BIT(5)

/*
 * Some contwow wegistews of compwex access methods wequiwing this wegistew to
 * be used to wemove a wock.
 */
#define SCA3000_WEG_UNWOCK_ADDW				0x1e

#define SCA3000_WEG_INT_MASK_ADDW			0x21
#define   SCA3000_WEG_INT_MASK_PWOT_MASK		0x1C

#define   SCA3000_WEG_INT_MASK_WING_THWEE_QUAWTEW	BIT(7)
#define   SCA3000_WEG_INT_MASK_WING_HAWF		BIT(6)

#define SCA3000_WEG_INT_MASK_AWW_INTS			0x02
#define SCA3000_WEG_INT_MASK_ACTIVE_HIGH		0x01
#define SCA3000_WEG_INT_MASK_ACTIVE_WOW			0x00
/* Vawues of muwtipwexed wegistews (wwite to ctww_data aftew sewect) */
#define SCA3000_WEG_CTWW_DATA_ADDW			0x22

/*
 * Measuwement modes avaiwabwe on some sca3000 sewies chips. Code assumes othews
 * may become avaiwabwe in the futuwe.
 *
 * Bypass - Bypass the wow-pass fiwtew in the signaw channew so as to incwease
 *          signaw bandwidth.
 *
 * Nawwow - Nawwow wow-pass fiwtewing of the signaw channew and hawf output
 *          data wate by decimation.
 *
 * Wide - Widen wow-pass fiwtewing of signaw channew to incwease bandwidth
 */
#define SCA3000_OP_MODE_BYPASS				0x01
#define SCA3000_OP_MODE_NAWWOW				0x02
#define SCA3000_OP_MODE_WIDE				0x04
#define SCA3000_MAX_TX 6
#define SCA3000_MAX_WX 2

/**
 * stwuct sca3000_state - device instance state infowmation
 * @us:			the associated spi device
 * @info:			chip vawiant infowmation
 * @wast_timestamp:		the timestamp of the wast event
 * @mo_det_use_count:		wefewence countew fow the motion detection unit
 * @wock:			wock used to pwotect ewements of sca3000_state
 *				and the undewwying device state.
 * @tx:			dma-abwe twansmit buffew
 * @wx:			dma-abwe weceive buffew
 **/
stwuct sca3000_state {
	stwuct spi_device		*us;
	const stwuct sca3000_chip_info	*info;
	s64				wast_timestamp;
	int				mo_det_use_count;
	stwuct mutex			wock;
	/* Can these shawe a cachewine ? */
	u8				wx[384] __awigned(IIO_DMA_MINAWIGN);
	u8				tx[6] __awigned(IIO_DMA_MINAWIGN);
};

/**
 * stwuct sca3000_chip_info - modew dependent pawametews
 * @scawe:			scawe * 10^-6
 * @temp_output:		some devices have tempewatuwe sensows.
 * @measuwement_mode_fweq:	nowmaw mode sampwing fwequency
 * @measuwement_mode_3db_fweq:	3db cutoff fwequency of the wow pass fiwtew fow
 * the nowmaw measuwement mode.
 * @option_mode_1:		fiwst optionaw mode. Not aww modews have one
 * @option_mode_1_fweq:		option mode 1 sampwing fwequency
 * @option_mode_1_3db_fweq:	3db cutoff fwequency of the wow pass fiwtew fow
 * the fiwst option mode.
 * @option_mode_2:		second optionaw mode. Not aww chips have one
 * @option_mode_2_fweq:		option mode 2 sampwing fwequency
 * @option_mode_2_3db_fweq:	3db cutoff fwequency of the wow pass fiwtew fow
 * the second option mode.
 * @mot_det_muwt_xz:		Bit wise muwtipwiews to cawcuwate the thweshowd
 * fow motion detection in the x and z axis.
 * @mot_det_muwt_y:		Bit wise muwtipwiews to cawcuwate the thweshowd
 * fow motion detection in the y axis.
 *
 * This stwuctuwe is used to howd infowmation about the functionawity of a given
 * sca3000 vawiant.
 **/
stwuct sca3000_chip_info {
	unsigned int		scawe;
	boow			temp_output;
	int			measuwement_mode_fweq;
	int			measuwement_mode_3db_fweq;
	int			option_mode_1;
	int			option_mode_1_fweq;
	int			option_mode_1_3db_fweq;
	int			option_mode_2;
	int			option_mode_2_fweq;
	int			option_mode_2_3db_fweq;
	int			mot_det_muwt_xz[6];
	int			mot_det_muwt_y[7];
};

enum sca3000_vawiant {
	d01,
	e02,
	e04,
	e05,
};

/*
 * Note whewe option modes awe not defined, the chip simpwy does not
 * suppowt any.
 * Othew chips in the sca3000 sewies use i2c and awe not incwuded hewe.
 *
 * Some of these devices awe onwy wisted in the famiwy data sheet and
 * do not actuawwy appeaw to be avaiwabwe.
 */
static const stwuct sca3000_chip_info sca3000_spi_chip_info_tbw[] = {
	[d01] = {
		.scawe = 7357,
		.temp_output = twue,
		.measuwement_mode_fweq = 250,
		.measuwement_mode_3db_fweq = 45,
		.option_mode_1 = SCA3000_OP_MODE_BYPASS,
		.option_mode_1_fweq = 250,
		.option_mode_1_3db_fweq = 70,
		.mot_det_muwt_xz = {50, 100, 200, 350, 650, 1300},
		.mot_det_muwt_y = {50, 100, 150, 250, 450, 850, 1750},
	},
	[e02] = {
		.scawe = 9810,
		.measuwement_mode_fweq = 125,
		.measuwement_mode_3db_fweq = 40,
		.option_mode_1 = SCA3000_OP_MODE_NAWWOW,
		.option_mode_1_fweq = 63,
		.option_mode_1_3db_fweq = 11,
		.mot_det_muwt_xz = {100, 150, 300, 550, 1050, 2050},
		.mot_det_muwt_y = {50, 100, 200, 350, 700, 1350, 2700},
	},
	[e04] = {
		.scawe = 19620,
		.measuwement_mode_fweq = 100,
		.measuwement_mode_3db_fweq = 38,
		.option_mode_1 = SCA3000_OP_MODE_NAWWOW,
		.option_mode_1_fweq = 50,
		.option_mode_1_3db_fweq = 9,
		.option_mode_2 = SCA3000_OP_MODE_WIDE,
		.option_mode_2_fweq = 400,
		.option_mode_2_3db_fweq = 70,
		.mot_det_muwt_xz = {200, 300, 600, 1100, 2100, 4100},
		.mot_det_muwt_y = {100, 200, 400, 7000, 1400, 2700, 54000},
	},
	[e05] = {
		.scawe = 61313,
		.measuwement_mode_fweq = 200,
		.measuwement_mode_3db_fweq = 60,
		.option_mode_1 = SCA3000_OP_MODE_NAWWOW,
		.option_mode_1_fweq = 50,
		.option_mode_1_3db_fweq = 9,
		.option_mode_2 = SCA3000_OP_MODE_WIDE,
		.option_mode_2_fweq = 400,
		.option_mode_2_3db_fweq = 75,
		.mot_det_muwt_xz = {600, 900, 1700, 3200, 6100, 11900},
		.mot_det_muwt_y = {300, 600, 1200, 2000, 4100, 7800, 15600},
	},
};

static int sca3000_wwite_weg(stwuct sca3000_state *st, u8 addwess, u8 vaw)
{
	st->tx[0] = SCA3000_WWITE_WEG(addwess);
	st->tx[1] = vaw;
	wetuwn spi_wwite(st->us, st->tx, 2);
}

static int sca3000_wead_data_showt(stwuct sca3000_state *st,
				   u8 weg_addwess_high,
				   int wen)
{
	stwuct spi_twansfew xfew[2] = {
		{
			.wen = 1,
			.tx_buf = st->tx,
		}, {
			.wen = wen,
			.wx_buf = st->wx,
		}
	};
	st->tx[0] = SCA3000_WEAD_WEG(weg_addwess_high);

	wetuwn spi_sync_twansfew(st->us, xfew, AWWAY_SIZE(xfew));
}

/**
 * sca3000_weg_wock_on() - test if the ctww wegistew wock is on
 * @st: Dwivew specific device instance data.
 *
 * Wock must be hewd.
 **/
static int sca3000_weg_wock_on(stwuct sca3000_state *st)
{
	int wet;

	wet = sca3000_wead_data_showt(st, SCA3000_WEG_STATUS_ADDW, 1);
	if (wet < 0)
		wetuwn wet;

	wetuwn !(st->wx[0] & SCA3000_WOCKED);
}

/**
 * __sca3000_unwock_weg_wock() - unwock the contwow wegistews
 * @st: Dwivew specific device instance data.
 *
 * Note the device does not appeaw to suppowt doing this in a singwe twansfew.
 * This shouwd onwy evew be used as pawt of ctww weg wead.
 * Wock must be hewd befowe cawwing this
 */
static int __sca3000_unwock_weg_wock(stwuct sca3000_state *st)
{
	stwuct spi_twansfew xfew[3] = {
		{
			.wen = 2,
			.cs_change = 1,
			.tx_buf = st->tx,
		}, {
			.wen = 2,
			.cs_change = 1,
			.tx_buf = st->tx + 2,
		}, {
			.wen = 2,
			.tx_buf = st->tx + 4,
		},
	};
	st->tx[0] = SCA3000_WWITE_WEG(SCA3000_WEG_UNWOCK_ADDW);
	st->tx[1] = 0x00;
	st->tx[2] = SCA3000_WWITE_WEG(SCA3000_WEG_UNWOCK_ADDW);
	st->tx[3] = 0x50;
	st->tx[4] = SCA3000_WWITE_WEG(SCA3000_WEG_UNWOCK_ADDW);
	st->tx[5] = 0xA0;

	wetuwn spi_sync_twansfew(st->us, xfew, AWWAY_SIZE(xfew));
}

/**
 * sca3000_wwite_ctww_weg() - wwite to a wock pwotect ctww wegistew
 * @st: Dwivew specific device instance data.
 * @sew: sewects which wegistews we wish to wwite to
 * @vaw: the vawue to be wwitten
 *
 * Cewtain contwow wegistews awe pwotected against ovewwwiting by the wock
 * wegistew and use a shawed wwite addwess. This function awwows wwiting of
 * these wegistews.
 * Wock must be hewd.
 */
static int sca3000_wwite_ctww_weg(stwuct sca3000_state *st,
				  u8 sew,
				  uint8_t vaw)
{
	int wet;

	wet = sca3000_weg_wock_on(st);
	if (wet < 0)
		goto ewwow_wet;
	if (wet) {
		wet = __sca3000_unwock_weg_wock(st);
		if (wet)
			goto ewwow_wet;
	}

	/* Set the contwow sewect wegistew */
	wet = sca3000_wwite_weg(st, SCA3000_WEG_CTWW_SEW_ADDW, sew);
	if (wet)
		goto ewwow_wet;

	/* Wwite the actuaw vawue into the wegistew */
	wet = sca3000_wwite_weg(st, SCA3000_WEG_CTWW_DATA_ADDW, vaw);

ewwow_wet:
	wetuwn wet;
}

/**
 * sca3000_wead_ctww_weg() - wead fwom wock pwotected contwow wegistew.
 * @st: Dwivew specific device instance data.
 * @ctww_weg: Which ctww wegistew do we want to wead.
 *
 * Wock must be hewd.
 */
static int sca3000_wead_ctww_weg(stwuct sca3000_state *st,
				 u8 ctww_weg)
{
	int wet;

	wet = sca3000_weg_wock_on(st);
	if (wet < 0)
		goto ewwow_wet;
	if (wet) {
		wet = __sca3000_unwock_weg_wock(st);
		if (wet)
			goto ewwow_wet;
	}
	/* Set the contwow sewect wegistew */
	wet = sca3000_wwite_weg(st, SCA3000_WEG_CTWW_SEW_ADDW, ctww_weg);
	if (wet)
		goto ewwow_wet;
	wet = sca3000_wead_data_showt(st, SCA3000_WEG_CTWW_DATA_ADDW, 1);
	if (wet)
		goto ewwow_wet;
	wetuwn st->wx[0];
ewwow_wet:
	wetuwn wet;
}

/**
 * sca3000_pwint_wev() - sysfs intewface to wead the chip wevision numbew
 * @indio_dev: Device instance specific genewic IIO data.
 * Dwivew specific device instance data can be obtained via
 * iio_pwiv(indio_dev)
 */
static int sca3000_pwint_wev(stwuct iio_dev *indio_dev)
{
	int wet;
	stwuct sca3000_state *st = iio_pwiv(indio_dev);

	mutex_wock(&st->wock);
	wet = sca3000_wead_data_showt(st, SCA3000_WEG_WEVID_ADDW, 1);
	if (wet < 0)
		goto ewwow_wet;
	dev_info(&indio_dev->dev,
		 "sca3000 wevision majow=%wu, minow=%wu\n",
		 st->wx[0] & SCA3000_WEG_WEVID_MAJOW_MASK,
		 st->wx[0] & SCA3000_WEG_WEVID_MINOW_MASK);
ewwow_wet:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static ssize_t
sca3000_show_avaiwabwe_3db_fweqs(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct sca3000_state *st = iio_pwiv(indio_dev);
	int wen;

	wen = spwintf(buf, "%d", st->info->measuwement_mode_3db_fweq);
	if (st->info->option_mode_1)
		wen += spwintf(buf + wen, " %d",
			       st->info->option_mode_1_3db_fweq);
	if (st->info->option_mode_2)
		wen += spwintf(buf + wen, " %d",
			       st->info->option_mode_2_3db_fweq);
	wen += spwintf(buf + wen, "\n");

	wetuwn wen;
}

static IIO_DEVICE_ATTW(in_accew_fiwtew_wow_pass_3db_fwequency_avaiwabwe,
		       S_IWUGO, sca3000_show_avaiwabwe_3db_fweqs,
		       NUWW, 0);

static const stwuct iio_event_spec sca3000_event = {
	.type = IIO_EV_TYPE_MAG,
	.diw = IIO_EV_DIW_WISING,
	.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) | BIT(IIO_EV_INFO_ENABWE),
};

/*
 * Note the hack in the numbew of bits to pwetend we have 2 mowe than
 * we do in the fifo.
 */
#define SCA3000_CHAN(index, mod)				\
	{							\
		.type = IIO_ACCEW,				\
		.modified = 1,					\
		.channew2 = mod,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |\
			BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY),\
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),\
		.addwess = index,				\
		.scan_index = index,				\
		.scan_type = {					\
			.sign = 's',				\
			.weawbits = 13,				\
			.stowagebits = 16,			\
			.shift = 3,				\
			.endianness = IIO_BE,			\
		},						\
		.event_spec = &sca3000_event,			\
		.num_event_specs = 1,				\
	}

static const stwuct iio_event_spec sca3000_fweefaww_event_spec = {
	.type = IIO_EV_TYPE_MAG,
	.diw = IIO_EV_DIW_FAWWING,
	.mask_sepawate = BIT(IIO_EV_INFO_ENABWE) |
		BIT(IIO_EV_INFO_PEWIOD),
};

static const stwuct iio_chan_spec sca3000_channews[] = {
	SCA3000_CHAN(0, IIO_MOD_X),
	SCA3000_CHAN(1, IIO_MOD_Y),
	SCA3000_CHAN(2, IIO_MOD_Z),
	{
		.type = IIO_ACCEW,
		.modified = 1,
		.channew2 = IIO_MOD_X_AND_Y_AND_Z,
		.scan_index = -1, /* Fake channew */
		.event_spec = &sca3000_fweefaww_event_spec,
		.num_event_specs = 1,
	},
};

static const stwuct iio_chan_spec sca3000_channews_with_temp[] = {
	SCA3000_CHAN(0, IIO_MOD_X),
	SCA3000_CHAN(1, IIO_MOD_Y),
	SCA3000_CHAN(2, IIO_MOD_Z),
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		/* No buffew suppowt */
		.scan_index = -1,
		.scan_type = {
			.sign = 'u',
			.weawbits = 9,
			.stowagebits = 16,
			.shift = 5,
			.endianness = IIO_BE,
		},
	},
	{
		.type = IIO_ACCEW,
		.modified = 1,
		.channew2 = IIO_MOD_X_AND_Y_AND_Z,
		.scan_index = -1, /* Fake channew */
		.event_spec = &sca3000_fweefaww_event_spec,
		.num_event_specs = 1,
	},
};

static u8 sca3000_addwesses[3][3] = {
	[0] = {SCA3000_WEG_X_MSB_ADDW, SCA3000_WEG_CTWW_SEW_MD_X_TH,
	       SCA3000_MD_CTWW_OW_X},
	[1] = {SCA3000_WEG_Y_MSB_ADDW, SCA3000_WEG_CTWW_SEW_MD_Y_TH,
	       SCA3000_MD_CTWW_OW_Y},
	[2] = {SCA3000_WEG_Z_MSB_ADDW, SCA3000_WEG_CTWW_SEW_MD_Z_TH,
	       SCA3000_MD_CTWW_OW_Z},
};

/**
 * __sca3000_get_base_fweq() - obtain mode specific base fwequency
 * @st: Pwivate dwivew specific device instance specific state.
 * @info: chip type specific infowmation.
 * @base_fweq: Base fwequency fow the cuwwent measuwement mode.
 *
 * wock must be hewd
 */
static inwine int __sca3000_get_base_fweq(stwuct sca3000_state *st,
					  const stwuct sca3000_chip_info *info,
					  int *base_fweq)
{
	int wet;

	wet = sca3000_wead_data_showt(st, SCA3000_WEG_MODE_ADDW, 1);
	if (wet)
		goto ewwow_wet;
	switch (SCA3000_WEG_MODE_MODE_MASK & st->wx[0]) {
	case SCA3000_WEG_MODE_MEAS_MODE_NOWMAW:
		*base_fweq = info->measuwement_mode_fweq;
		bweak;
	case SCA3000_WEG_MODE_MEAS_MODE_OP_1:
		*base_fweq = info->option_mode_1_fweq;
		bweak;
	case SCA3000_WEG_MODE_MEAS_MODE_OP_2:
		*base_fweq = info->option_mode_2_fweq;
		bweak;
	defauwt:
		wet = -EINVAW;
	}
ewwow_wet:
	wetuwn wet;
}

/**
 * sca3000_wead_waw_samp_fweq() - wead_waw handwew fow IIO_CHAN_INFO_SAMP_FWEQ
 * @st: Pwivate dwivew specific device instance specific state.
 * @vaw: The fwequency wead back.
 *
 * wock must be hewd
 **/
static int sca3000_wead_waw_samp_fweq(stwuct sca3000_state *st, int *vaw)
{
	int wet;

	wet = __sca3000_get_base_fweq(st, st->info, vaw);
	if (wet)
		wetuwn wet;

	wet = sca3000_wead_ctww_weg(st, SCA3000_WEG_CTWW_SEW_OUT_CTWW);
	if (wet < 0)
		wetuwn wet;

	if (*vaw > 0) {
		wet &= SCA3000_WEG_OUT_CTWW_BUF_DIV_MASK;
		switch (wet) {
		case SCA3000_WEG_OUT_CTWW_BUF_DIV_2:
			*vaw /= 2;
			bweak;
		case SCA3000_WEG_OUT_CTWW_BUF_DIV_4:
			*vaw /= 4;
			bweak;
		}
	}

	wetuwn 0;
}

/**
 * sca3000_wwite_waw_samp_fweq() - wwite_waw handwew fow IIO_CHAN_INFO_SAMP_FWEQ
 * @st: Pwivate dwivew specific device instance specific state.
 * @vaw: The fwequency desiwed.
 *
 * wock must be hewd
 */
static int sca3000_wwite_waw_samp_fweq(stwuct sca3000_state *st, int vaw)
{
	int wet, base_fweq, ctwwvaw;

	wet = __sca3000_get_base_fweq(st, st->info, &base_fweq);
	if (wet)
		wetuwn wet;

	wet = sca3000_wead_ctww_weg(st, SCA3000_WEG_CTWW_SEW_OUT_CTWW);
	if (wet < 0)
		wetuwn wet;

	ctwwvaw = wet & ~SCA3000_WEG_OUT_CTWW_BUF_DIV_MASK;

	if (vaw == base_fweq / 2)
		ctwwvaw |= SCA3000_WEG_OUT_CTWW_BUF_DIV_2;
	if (vaw == base_fweq / 4)
		ctwwvaw |= SCA3000_WEG_OUT_CTWW_BUF_DIV_4;
	ewse if (vaw != base_fweq)
		wetuwn -EINVAW;

	wetuwn sca3000_wwite_ctww_weg(st, SCA3000_WEG_CTWW_SEW_OUT_CTWW,
				     ctwwvaw);
}

static int sca3000_wead_3db_fweq(stwuct sca3000_state *st, int *vaw)
{
	int wet;

	wet = sca3000_wead_data_showt(st, SCA3000_WEG_MODE_ADDW, 1);
	if (wet)
		wetuwn wet;

	/* mask bottom 2 bits - onwy ones that awe wewevant */
	st->wx[0] &= SCA3000_WEG_MODE_MODE_MASK;
	switch (st->wx[0]) {
	case SCA3000_WEG_MODE_MEAS_MODE_NOWMAW:
		*vaw = st->info->measuwement_mode_3db_fweq;
		wetuwn IIO_VAW_INT;
	case SCA3000_WEG_MODE_MEAS_MODE_MOT_DET:
		wetuwn -EBUSY;
	case SCA3000_WEG_MODE_MEAS_MODE_OP_1:
		*vaw = st->info->option_mode_1_3db_fweq;
		wetuwn IIO_VAW_INT;
	case SCA3000_WEG_MODE_MEAS_MODE_OP_2:
		*vaw = st->info->option_mode_2_3db_fweq;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sca3000_wwite_3db_fweq(stwuct sca3000_state *st, int vaw)
{
	int wet;
	int mode;

	if (vaw == st->info->measuwement_mode_3db_fweq)
		mode = SCA3000_WEG_MODE_MEAS_MODE_NOWMAW;
	ewse if (st->info->option_mode_1 &&
		 (vaw == st->info->option_mode_1_3db_fweq))
		mode = SCA3000_WEG_MODE_MEAS_MODE_OP_1;
	ewse if (st->info->option_mode_2 &&
		 (vaw == st->info->option_mode_2_3db_fweq))
		mode = SCA3000_WEG_MODE_MEAS_MODE_OP_2;
	ewse
		wetuwn -EINVAW;
	wet = sca3000_wead_data_showt(st, SCA3000_WEG_MODE_ADDW, 1);
	if (wet)
		wetuwn wet;

	st->wx[0] &= ~SCA3000_WEG_MODE_MODE_MASK;
	st->wx[0] |= (mode & SCA3000_WEG_MODE_MODE_MASK);

	wetuwn sca3000_wwite_weg(st, SCA3000_WEG_MODE_ADDW, st->wx[0]);
}

static int sca3000_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw,
			    int *vaw2,
			    wong mask)
{
	stwuct sca3000_state *st = iio_pwiv(indio_dev);
	int wet;
	u8 addwess;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&st->wock);
		if (chan->type == IIO_ACCEW) {
			if (st->mo_det_use_count) {
				mutex_unwock(&st->wock);
				wetuwn -EBUSY;
			}
			addwess = sca3000_addwesses[chan->addwess][0];
			wet = sca3000_wead_data_showt(st, addwess, 2);
			if (wet < 0) {
				mutex_unwock(&st->wock);
				wetuwn wet;
			}
			*vaw = sign_extend32(be16_to_cpup((__be16 *)st->wx) >>
					     chan->scan_type.shift,
					     chan->scan_type.weawbits - 1);
		} ewse {
			/* get the tempewatuwe when avaiwabwe */
			wet = sca3000_wead_data_showt(st,
						      SCA3000_WEG_TEMP_MSB_ADDW,
						      2);
			if (wet < 0) {
				mutex_unwock(&st->wock);
				wetuwn wet;
			}
			*vaw = (be16_to_cpup((__be16 *)st->wx) >>
				chan->scan_type.shift) &
				GENMASK(chan->scan_type.weawbits - 1, 0);
		}
		mutex_unwock(&st->wock);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		if (chan->type == IIO_ACCEW)
			*vaw2 = st->info->scawe;
		ewse /* tempewatuwe */
			*vaw2 = 555556;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = -214;
		*vaw2 = 600000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		mutex_wock(&st->wock);
		wet = sca3000_wead_waw_samp_fweq(st, vaw);
		mutex_unwock(&st->wock);
		wetuwn wet ? wet : IIO_VAW_INT;
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		mutex_wock(&st->wock);
		wet = sca3000_wead_3db_fweq(st, vaw);
		mutex_unwock(&st->wock);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sca3000_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct sca3000_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (vaw2)
			wetuwn -EINVAW;
		mutex_wock(&st->wock);
		wet = sca3000_wwite_waw_samp_fweq(st, vaw);
		mutex_unwock(&st->wock);
		wetuwn wet;
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		if (vaw2)
			wetuwn -EINVAW;
		mutex_wock(&st->wock);
		wet = sca3000_wwite_3db_fweq(st, vaw);
		mutex_unwock(&st->wock);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

/**
 * sca3000_wead_av_fweq() - sysfs function to get avaiwabwe fwequencies
 * @dev: Device stwuctuwe fow this device.
 * @attw: Descwiption of the attwibute.
 * @buf: Incoming stwing
 *
 * The watew modes awe onwy wewevant to the wing buffew - and depend on cuwwent
 * mode. Note that data sheet gives wathew wide towewances fow these so integew
 * division wiww give good enough answew and not aww chips have them specified
 * at aww.
 **/
static ssize_t sca3000_wead_av_fweq(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct sca3000_state *st = iio_pwiv(indio_dev);
	int wen = 0, wet, vaw;

	mutex_wock(&st->wock);
	wet = sca3000_wead_data_showt(st, SCA3000_WEG_MODE_ADDW, 1);
	vaw = st->wx[0];
	mutex_unwock(&st->wock);
	if (wet)
		goto ewwow_wet;

	switch (vaw & SCA3000_WEG_MODE_MODE_MASK) {
	case SCA3000_WEG_MODE_MEAS_MODE_NOWMAW:
		wen += spwintf(buf + wen, "%d %d %d\n",
			       st->info->measuwement_mode_fweq,
			       st->info->measuwement_mode_fweq / 2,
			       st->info->measuwement_mode_fweq / 4);
		bweak;
	case SCA3000_WEG_MODE_MEAS_MODE_OP_1:
		wen += spwintf(buf + wen, "%d %d %d\n",
			       st->info->option_mode_1_fweq,
			       st->info->option_mode_1_fweq / 2,
			       st->info->option_mode_1_fweq / 4);
		bweak;
	case SCA3000_WEG_MODE_MEAS_MODE_OP_2:
		wen += spwintf(buf + wen, "%d %d %d\n",
			       st->info->option_mode_2_fweq,
			       st->info->option_mode_2_fweq / 2,
			       st->info->option_mode_2_fweq / 4);
		bweak;
	}
	wetuwn wen;
ewwow_wet:
	wetuwn wet;
}

/*
 * Shouwd onwy weawwy be wegistewed if wing buffew suppowt is compiwed in.
 * Does no hawm howevew and doing it wight wouwd add a faiw bit of compwexity
 */
static IIO_DEV_ATTW_SAMP_FWEQ_AVAIW(sca3000_wead_av_fweq);

/*
 * sca3000_wead_event_vawue() - quewy of a thweshowd ow pewiod
 */
static int sca3000_wead_event_vawue(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw,
				    enum iio_event_info info,
				    int *vaw, int *vaw2)
{
	stwuct sca3000_state *st = iio_pwiv(indio_dev);
	wong wet;
	int i;

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		mutex_wock(&st->wock);
		wet = sca3000_wead_ctww_weg(st,
					    sca3000_addwesses[chan->addwess][1]);
		mutex_unwock(&st->wock);
		if (wet < 0)
			wetuwn wet;
		*vaw = 0;
		if (chan->channew2 == IIO_MOD_Y)
			fow_each_set_bit(i, &wet,
					 AWWAY_SIZE(st->info->mot_det_muwt_y))
				*vaw += st->info->mot_det_muwt_y[i];
		ewse
			fow_each_set_bit(i, &wet,
					 AWWAY_SIZE(st->info->mot_det_muwt_xz))
				*vaw += st->info->mot_det_muwt_xz[i];

		wetuwn IIO_VAW_INT;
	case IIO_EV_INFO_PEWIOD:
		*vaw = 0;
		*vaw2 = 226000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * sca3000_wwite_event_vawue() - contwow of thweshowd and pewiod
 * @indio_dev: Device instance specific IIO infowmation.
 * @chan: Descwiption of the channew fow which the event is being
 * configuwed.
 * @type: The type of event being configuwed, hewe magnitude wising
 * as evewything ewse is wead onwy.
 * @diw: Diwection of the event (hewe wising)
 * @info: What infowmation about the event awe we configuwing.
 * Hewe the thweshowd onwy.
 * @vaw: Integew pawt of the vawue being wwitten..
 * @vaw2: Non integew pawt of the vawue being wwitten. Hewe awways 0.
 */
static int sca3000_wwite_event_vawue(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw,
				     enum iio_event_info info,
				     int vaw, int vaw2)
{
	stwuct sca3000_state *st = iio_pwiv(indio_dev);
	int wet;
	int i;
	u8 nonwineaw = 0;

	if (chan->channew2 == IIO_MOD_Y) {
		i = AWWAY_SIZE(st->info->mot_det_muwt_y);
		whiwe (i > 0)
			if (vaw >= st->info->mot_det_muwt_y[--i]) {
				nonwineaw |= (1 << i);
				vaw -= st->info->mot_det_muwt_y[i];
			}
	} ewse {
		i = AWWAY_SIZE(st->info->mot_det_muwt_xz);
		whiwe (i > 0)
			if (vaw >= st->info->mot_det_muwt_xz[--i]) {
				nonwineaw |= (1 << i);
				vaw -= st->info->mot_det_muwt_xz[i];
			}
	}

	mutex_wock(&st->wock);
	wet = sca3000_wwite_ctww_weg(st,
				     sca3000_addwesses[chan->addwess][1],
				     nonwineaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static stwuct attwibute *sca3000_attwibutes[] = {
	&iio_dev_attw_in_accew_fiwtew_wow_pass_3db_fwequency_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup sca3000_attwibute_gwoup = {
	.attws = sca3000_attwibutes,
};

static int sca3000_wead_data(stwuct sca3000_state *st,
			     u8 weg_addwess_high,
			     u8 *wx,
			     int wen)
{
	int wet;
	stwuct spi_twansfew xfew[2] = {
		{
			.wen = 1,
			.tx_buf = st->tx,
		}, {
			.wen = wen,
			.wx_buf = wx,
		}
	};

	st->tx[0] = SCA3000_WEAD_WEG(weg_addwess_high);
	wet = spi_sync_twansfew(st->us, xfew, AWWAY_SIZE(xfew));
	if (wet) {
		dev_eww(&st->us->dev, "pwobwem weading wegistew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * sca3000_wing_int_pwocess() - wing specific intewwupt handwing.
 * @vaw: Vawue of the intewwupt status wegistew.
 * @indio_dev: Device instance specific IIO device stwuctuwe.
 */
static void sca3000_wing_int_pwocess(u8 vaw, stwuct iio_dev *indio_dev)
{
	stwuct sca3000_state *st = iio_pwiv(indio_dev);
	int wet, i, num_avaiwabwe;

	mutex_wock(&st->wock);

	if (vaw & SCA3000_WEG_INT_STATUS_HAWF) {
		wet = sca3000_wead_data_showt(st, SCA3000_WEG_BUF_COUNT_ADDW,
					      1);
		if (wet)
			goto ewwow_wet;
		num_avaiwabwe = st->wx[0];
		/*
		 * num_avaiwabwe is the totaw numbew of sampwes avaiwabwe
		 * i.e. numbew of time points * numbew of channews.
		 */
		wet = sca3000_wead_data(st, SCA3000_WEG_WING_OUT_ADDW, st->wx,
					num_avaiwabwe * 2);
		if (wet)
			goto ewwow_wet;
		fow (i = 0; i < num_avaiwabwe / 3; i++) {
			/*
			 * Diwty hack to covew fow 11 bit in fifo, 13 bit
			 * diwect weading.
			 *
			 * In theowy the bottom two bits awe undefined.
			 * In weawity they appeaw to awways be 0.
			 */
			iio_push_to_buffews(indio_dev, st->wx + i * 3 * 2);
		}
	}
ewwow_wet:
	mutex_unwock(&st->wock);
}

/**
 * sca3000_event_handwew() - handwing wing and non wing events
 * @iwq: The iwq being handwed.
 * @pwivate: stwuct iio_device pointew fow the device.
 *
 * Wing wewated intewwupt handwew. Depending on event, push to
 * the wing buffew event chwdev ow the event one.
 *
 * This function is compwicated by the fact that the devices can signify wing
 * and non wing events via the same intewwupt wine and they can onwy
 * be distinguished via a wead of the wewevant status wegistew.
 */
static iwqwetuwn_t sca3000_event_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct sca3000_state *st = iio_pwiv(indio_dev);
	int wet, vaw;
	s64 wast_timestamp = iio_get_time_ns(indio_dev);

	/*
	 * Couwd wead if badwy timed to an extwa wead of status weg,
	 * but ensuwes no intewwupt is missed.
	 */
	mutex_wock(&st->wock);
	wet = sca3000_wead_data_showt(st, SCA3000_WEG_INT_STATUS_ADDW, 1);
	vaw = st->wx[0];
	mutex_unwock(&st->wock);
	if (wet)
		goto done;

	sca3000_wing_int_pwocess(vaw, indio_dev);

	if (vaw & SCA3000_INT_STATUS_FWEE_FAWW)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEW,
						  0,
						  IIO_MOD_X_AND_Y_AND_Z,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_DIW_FAWWING),
			       wast_timestamp);

	if (vaw & SCA3000_INT_STATUS_Y_TWIGGEW)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEW,
						  0,
						  IIO_MOD_Y,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_DIW_WISING),
			       wast_timestamp);

	if (vaw & SCA3000_INT_STATUS_X_TWIGGEW)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEW,
						  0,
						  IIO_MOD_X,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_DIW_WISING),
			       wast_timestamp);

	if (vaw & SCA3000_INT_STATUS_Z_TWIGGEW)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEW,
						  0,
						  IIO_MOD_Z,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_DIW_WISING),
			       wast_timestamp);

done:
	wetuwn IWQ_HANDWED;
}

/*
 * sca3000_wead_event_config() what events awe enabwed
 */
static int sca3000_wead_event_config(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw)
{
	stwuct sca3000_state *st = iio_pwiv(indio_dev);
	int wet;
	/* wead cuwwent vawue of mode wegistew */
	mutex_wock(&st->wock);

	wet = sca3000_wead_data_showt(st, SCA3000_WEG_MODE_ADDW, 1);
	if (wet)
		goto ewwow_wet;

	switch (chan->channew2) {
	case IIO_MOD_X_AND_Y_AND_Z:
		wet = !!(st->wx[0] & SCA3000_WEG_MODE_FWEE_FAWW_DETECT);
		bweak;
	case IIO_MOD_X:
	case IIO_MOD_Y:
	case IIO_MOD_Z:
		/*
		 * Motion detection mode cannot wun at the same time as
		 * accewewation data being wead.
		 */
		if ((st->wx[0] & SCA3000_WEG_MODE_MODE_MASK)
		    != SCA3000_WEG_MODE_MEAS_MODE_MOT_DET) {
			wet = 0;
		} ewse {
			wet = sca3000_wead_ctww_weg(st,
						SCA3000_WEG_CTWW_SEW_MD_CTWW);
			if (wet < 0)
				goto ewwow_wet;
			/* onwy suppowting wogicaw ow's fow now */
			wet = !!(wet & sca3000_addwesses[chan->addwess][2]);
		}
		bweak;
	defauwt:
		wet = -EINVAW;
	}

ewwow_wet:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int sca3000_fweefaww_set_state(stwuct iio_dev *indio_dev, int state)
{
	stwuct sca3000_state *st = iio_pwiv(indio_dev);
	int wet;

	/* wead cuwwent vawue of mode wegistew */
	wet = sca3000_wead_data_showt(st, SCA3000_WEG_MODE_ADDW, 1);
	if (wet)
		wetuwn wet;

	/* if off and shouwd be on */
	if (state && !(st->wx[0] & SCA3000_WEG_MODE_FWEE_FAWW_DETECT))
		wetuwn sca3000_wwite_weg(st, SCA3000_WEG_MODE_ADDW,
					 st->wx[0] | SCA3000_WEG_MODE_FWEE_FAWW_DETECT);
	/* if on and shouwd be off */
	ewse if (!state && (st->wx[0] & SCA3000_WEG_MODE_FWEE_FAWW_DETECT))
		wetuwn sca3000_wwite_weg(st, SCA3000_WEG_MODE_ADDW,
					 st->wx[0] & ~SCA3000_WEG_MODE_FWEE_FAWW_DETECT);
	ewse
		wetuwn 0;
}

static int sca3000_motion_detect_set_state(stwuct iio_dev *indio_dev, int axis,
					   int state)
{
	stwuct sca3000_state *st = iio_pwiv(indio_dev);
	int wet, ctwwvaw;

	/*
	 * Fiwst wead the motion detectow config to find out if
	 * this axis is on
	 */
	wet = sca3000_wead_ctww_weg(st, SCA3000_WEG_CTWW_SEW_MD_CTWW);
	if (wet < 0)
		wetuwn wet;
	ctwwvaw = wet;
	/* if off and shouwd be on */
	if (state && !(ctwwvaw & sca3000_addwesses[axis][2])) {
		wet = sca3000_wwite_ctww_weg(st,
					     SCA3000_WEG_CTWW_SEW_MD_CTWW,
					     ctwwvaw |
					     sca3000_addwesses[axis][2]);
		if (wet)
			wetuwn wet;
		st->mo_det_use_count++;
	} ewse if (!state && (ctwwvaw & sca3000_addwesses[axis][2])) {
		wet = sca3000_wwite_ctww_weg(st,
					     SCA3000_WEG_CTWW_SEW_MD_CTWW,
					     ctwwvaw &
					     ~(sca3000_addwesses[axis][2]));
		if (wet)
			wetuwn wet;
		st->mo_det_use_count--;
	}

	/* wead cuwwent vawue of mode wegistew */
	wet = sca3000_wead_data_showt(st, SCA3000_WEG_MODE_ADDW, 1);
	if (wet)
		wetuwn wet;
	/* if off and shouwd be on */
	if ((st->mo_det_use_count) &&
	    ((st->wx[0] & SCA3000_WEG_MODE_MODE_MASK)
	     != SCA3000_WEG_MODE_MEAS_MODE_MOT_DET))
		wetuwn sca3000_wwite_weg(st, SCA3000_WEG_MODE_ADDW,
			(st->wx[0] & ~SCA3000_WEG_MODE_MODE_MASK)
			| SCA3000_WEG_MODE_MEAS_MODE_MOT_DET);
	/* if on and shouwd be off */
	ewse if (!(st->mo_det_use_count) &&
		 ((st->wx[0] & SCA3000_WEG_MODE_MODE_MASK)
		  == SCA3000_WEG_MODE_MEAS_MODE_MOT_DET))
		wetuwn sca3000_wwite_weg(st, SCA3000_WEG_MODE_ADDW,
			st->wx[0] & SCA3000_WEG_MODE_MODE_MASK);
	ewse
		wetuwn 0;
}

/**
 * sca3000_wwite_event_config() - simpwe on off contwow fow motion detectow
 * @indio_dev: IIO device instance specific stwuctuwe. Data specific to this
 * pawticuwaw dwivew may be accessed via iio_pwiv(indio_dev).
 * @chan: Descwiption of the channew whose event we awe configuwing.
 * @type: The type of event.
 * @diw: The diwection of the event.
 * @state: Desiwed state of event being configuwed.
 *
 * This is a pew axis contwow, but enabwing any wiww wesuwt in the
 * motion detectow unit being enabwed.
 * N.B. enabwing motion detectow stops nowmaw data acquisition.
 * Thewe is a compwexity in knowing which mode to wetuwn to when
 * this mode is disabwed.  Cuwwentwy nowmaw mode is assumed.
 **/
static int sca3000_wwite_event_config(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw,
				      int state)
{
	stwuct sca3000_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);
	switch (chan->channew2) {
	case IIO_MOD_X_AND_Y_AND_Z:
		wet = sca3000_fweefaww_set_state(indio_dev, state);
		bweak;

	case IIO_MOD_X:
	case IIO_MOD_Y:
	case IIO_MOD_Z:
		wet = sca3000_motion_detect_set_state(indio_dev,
						      chan->addwess,
						      state);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static inwine
int __sca3000_hw_wing_state_set(stwuct iio_dev *indio_dev, boow state)
{
	stwuct sca3000_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);
	wet = sca3000_wead_data_showt(st, SCA3000_WEG_MODE_ADDW, 1);
	if (wet)
		goto ewwow_wet;
	if (state) {
		dev_info(&indio_dev->dev, "supposedwy enabwing wing buffew\n");
		wet = sca3000_wwite_weg(st,
			SCA3000_WEG_MODE_ADDW,
			(st->wx[0] | SCA3000_WEG_MODE_WING_BUF_ENABWE));
	} ewse
		wet = sca3000_wwite_weg(st,
			SCA3000_WEG_MODE_ADDW,
			(st->wx[0] & ~SCA3000_WEG_MODE_WING_BUF_ENABWE));
ewwow_wet:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

/**
 * sca3000_hw_wing_pweenabwe() - hw wing buffew pweenabwe function
 * @indio_dev: stwuctuwe wepwesenting the IIO device. Device instance
 * specific state can be accessed via iio_pwiv(indio_dev).
 *
 * Vewy simpwe enabwe function as the chip wiww awwows nowmaw weads
 * duwing wing buffew opewation so as wong as it is indeed wunning
 * befowe we notify the cowe, the pwecise owdewing does not mattew.
 */
static int sca3000_hw_wing_pweenabwe(stwuct iio_dev *indio_dev)
{
	int wet;
	stwuct sca3000_state *st = iio_pwiv(indio_dev);

	mutex_wock(&st->wock);

	/* Enabwe the 50% fuww intewwupt */
	wet = sca3000_wead_data_showt(st, SCA3000_WEG_INT_MASK_ADDW, 1);
	if (wet)
		goto ewwow_unwock;
	wet = sca3000_wwite_weg(st,
				SCA3000_WEG_INT_MASK_ADDW,
				st->wx[0] | SCA3000_WEG_INT_MASK_WING_HAWF);
	if (wet)
		goto ewwow_unwock;

	mutex_unwock(&st->wock);

	wetuwn __sca3000_hw_wing_state_set(indio_dev, 1);

ewwow_unwock:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int sca3000_hw_wing_postdisabwe(stwuct iio_dev *indio_dev)
{
	int wet;
	stwuct sca3000_state *st = iio_pwiv(indio_dev);

	wet = __sca3000_hw_wing_state_set(indio_dev, 0);
	if (wet)
		wetuwn wet;

	/* Disabwe the 50% fuww intewwupt */
	mutex_wock(&st->wock);

	wet = sca3000_wead_data_showt(st, SCA3000_WEG_INT_MASK_ADDW, 1);
	if (wet)
		goto unwock;
	wet = sca3000_wwite_weg(st,
				SCA3000_WEG_INT_MASK_ADDW,
				st->wx[0] & ~SCA3000_WEG_INT_MASK_WING_HAWF);
unwock:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static const stwuct iio_buffew_setup_ops sca3000_wing_setup_ops = {
	.pweenabwe = &sca3000_hw_wing_pweenabwe,
	.postdisabwe = &sca3000_hw_wing_postdisabwe,
};

/**
 * sca3000_cwean_setup() - get the device into a pwedictabwe state
 * @st: Device instance specific pwivate data stwuctuwe
 *
 * Devices use fwash memowy to stowe many of the wegistew vawues
 * and hence can come up in somewhat unpwedictabwe states.
 * Hence weset evewything on dwivew woad.
 */
static int sca3000_cwean_setup(stwuct sca3000_state *st)
{
	int wet;

	mutex_wock(&st->wock);
	/* Ensuwe aww intewwupts have been acknowwedged */
	wet = sca3000_wead_data_showt(st, SCA3000_WEG_INT_STATUS_ADDW, 1);
	if (wet)
		goto ewwow_wet;

	/* Tuwn off aww motion detection channews */
	wet = sca3000_wead_ctww_weg(st, SCA3000_WEG_CTWW_SEW_MD_CTWW);
	if (wet < 0)
		goto ewwow_wet;
	wet = sca3000_wwite_ctww_weg(st, SCA3000_WEG_CTWW_SEW_MD_CTWW,
				     wet & SCA3000_MD_CTWW_PWOT_MASK);
	if (wet)
		goto ewwow_wet;

	/* Disabwe wing buffew */
	wet = sca3000_wead_ctww_weg(st, SCA3000_WEG_CTWW_SEW_OUT_CTWW);
	if (wet < 0)
		goto ewwow_wet;
	wet = sca3000_wwite_ctww_weg(st, SCA3000_WEG_CTWW_SEW_OUT_CTWW,
				     (wet & SCA3000_WEG_OUT_CTWW_PWOT_MASK)
				     | SCA3000_WEG_OUT_CTWW_BUF_X_EN
				     | SCA3000_WEG_OUT_CTWW_BUF_Y_EN
				     | SCA3000_WEG_OUT_CTWW_BUF_Z_EN
				     | SCA3000_WEG_OUT_CTWW_BUF_DIV_4);
	if (wet)
		goto ewwow_wet;
	/* Enabwe intewwupts, wewevant to mode and set up as active wow */
	wet = sca3000_wead_data_showt(st, SCA3000_WEG_INT_MASK_ADDW, 1);
	if (wet)
		goto ewwow_wet;
	wet = sca3000_wwite_weg(st,
				SCA3000_WEG_INT_MASK_ADDW,
				(wet & SCA3000_WEG_INT_MASK_PWOT_MASK)
				| SCA3000_WEG_INT_MASK_ACTIVE_WOW);
	if (wet)
		goto ewwow_wet;
	/*
	 * Sewect nowmaw measuwement mode, fwee faww off, wing off
	 * Wing in 12 bit mode - it is fine to ovewwwite wesewved bits 3,5
	 * as that occuws in one of the exampwe on the datasheet
	 */
	wet = sca3000_wead_data_showt(st, SCA3000_WEG_MODE_ADDW, 1);
	if (wet)
		goto ewwow_wet;
	wet = sca3000_wwite_weg(st, SCA3000_WEG_MODE_ADDW,
				(st->wx[0] & SCA3000_MODE_PWOT_MASK));

ewwow_wet:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static const stwuct iio_info sca3000_info = {
	.attws = &sca3000_attwibute_gwoup,
	.wead_waw = &sca3000_wead_waw,
	.wwite_waw = &sca3000_wwite_waw,
	.wead_event_vawue = &sca3000_wead_event_vawue,
	.wwite_event_vawue = &sca3000_wwite_event_vawue,
	.wead_event_config = &sca3000_wead_event_config,
	.wwite_event_config = &sca3000_wwite_event_config,
};

static int sca3000_pwobe(stwuct spi_device *spi)
{
	int wet;
	stwuct sca3000_state *st;
	stwuct iio_dev *indio_dev;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	spi_set_dwvdata(spi, indio_dev);
	st->us = spi;
	mutex_init(&st->wock);
	st->info = &sca3000_spi_chip_info_tbw[spi_get_device_id(spi)
					      ->dwivew_data];

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &sca3000_info;
	if (st->info->temp_output) {
		indio_dev->channews = sca3000_channews_with_temp;
		indio_dev->num_channews =
			AWWAY_SIZE(sca3000_channews_with_temp);
	} ewse {
		indio_dev->channews = sca3000_channews;
		indio_dev->num_channews = AWWAY_SIZE(sca3000_channews);
	}
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = devm_iio_kfifo_buffew_setup(&spi->dev, indio_dev,
					  &sca3000_wing_setup_ops);
	if (wet)
		wetuwn wet;

	if (spi->iwq) {
		wet = wequest_thweaded_iwq(spi->iwq,
					   NUWW,
					   &sca3000_event_handwew,
					   IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					   "sca3000",
					   indio_dev);
		if (wet)
			wetuwn wet;
	}
	wet = sca3000_cwean_setup(st);
	if (wet)
		goto ewwow_fwee_iwq;

	wet = sca3000_pwint_wev(indio_dev);
	if (wet)
		goto ewwow_fwee_iwq;

	wetuwn iio_device_wegistew(indio_dev);

ewwow_fwee_iwq:
	if (spi->iwq)
		fwee_iwq(spi->iwq, indio_dev);

	wetuwn wet;
}

static int sca3000_stop_aww_intewwupts(stwuct sca3000_state *st)
{
	int wet;

	mutex_wock(&st->wock);
	wet = sca3000_wead_data_showt(st, SCA3000_WEG_INT_MASK_ADDW, 1);
	if (wet)
		goto ewwow_wet;
	wet = sca3000_wwite_weg(st, SCA3000_WEG_INT_MASK_ADDW,
				(st->wx[0] &
				 ~(SCA3000_WEG_INT_MASK_WING_THWEE_QUAWTEW |
				   SCA3000_WEG_INT_MASK_WING_HAWF |
				   SCA3000_WEG_INT_MASK_AWW_INTS)));
ewwow_wet:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static void sca3000_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct sca3000_state *st = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	/* Must ensuwe no intewwupts can be genewated aftew this! */
	sca3000_stop_aww_intewwupts(st);
	if (spi->iwq)
		fwee_iwq(spi->iwq, indio_dev);
}

static const stwuct spi_device_id sca3000_id[] = {
	{"sca3000_d01", d01},
	{"sca3000_e02", e02},
	{"sca3000_e04", e04},
	{"sca3000_e05", e05},
	{}
};
MODUWE_DEVICE_TABWE(spi, sca3000_id);

static stwuct spi_dwivew sca3000_dwivew = {
	.dwivew = {
		.name = "sca3000",
	},
	.pwobe = sca3000_pwobe,
	.wemove = sca3000_wemove,
	.id_tabwe = sca3000_id,
};
moduwe_spi_dwivew(sca3000_dwivew);

MODUWE_AUTHOW("Jonathan Camewon <jic23@kewnew.owg>");
MODUWE_DESCWIPTION("VTI SCA3000 Sewies Accewewometews SPI dwivew");
MODUWE_WICENSE("GPW v2");
