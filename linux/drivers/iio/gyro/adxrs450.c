// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADXWS450/ADXWS453 Digitaw Output Gywoscope Dwivew
 *
 * Copywight 2011 Anawog Devices Inc.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define ADXWS450_STAWTUP_DEWAY	50 /* ms */

/* The MSB fow the spi commands */
#define ADXWS450_SENSOW_DATA    (0x20 << 24)
#define ADXWS450_WWITE_DATA	(0x40 << 24)
#define ADXWS450_WEAD_DATA	(0x80 << 24)

#define ADXWS450_WATE1	0x00	/* Wate Wegistews */
#define ADXWS450_TEMP1	0x02	/* Tempewatuwe Wegistews */
#define ADXWS450_WOCST1	0x04	/* Wow CST Memowy Wegistews */
#define ADXWS450_HICST1	0x06	/* High CST Memowy Wegistews */
#define ADXWS450_QUAD1	0x08	/* Quad Memowy Wegistews */
#define ADXWS450_FAUWT1	0x0A	/* Fauwt Wegistews */
#define ADXWS450_PID1	0x0C	/* Pawt ID Wegistew 1 */
#define ADXWS450_SNH	0x0E	/* Sewiaw Numbew Wegistews, 4 bytes */
#define ADXWS450_SNW	0x10
#define ADXWS450_DNC1	0x12	/* Dynamic Nuww Cowwection Wegistews */
/* Check bits */
#define ADXWS450_P	0x01
#define ADXWS450_CHK	0x02
#define ADXWS450_CST	0x04
#define ADXWS450_PWW	0x08
#define ADXWS450_POW	0x10
#define ADXWS450_NVM	0x20
#define ADXWS450_Q	0x40
#define ADXWS450_PWW	0x80
#define ADXWS450_UV	0x100
#define ADXWS450_OV	0x200
#define ADXWS450_AMP	0x400
#define ADXWS450_FAIW	0x800

#define ADXWS450_WWEWW_MASK	(0x7 << 29)

#define ADXWS450_MAX_WX 4
#define ADXWS450_MAX_TX 4

#define ADXWS450_GET_ST(a)	((a >> 26) & 0x3)

enum {
	ID_ADXWS450,
	ID_ADXWS453,
};

/**
 * stwuct adxws450_state - device instance specific data
 * @us:			actuaw spi_device
 * @buf_wock:		mutex to pwotect tx and wx
 * @tx:			twansmit buffew
 * @wx:			weceive buffew
 **/
stwuct adxws450_state {
	stwuct spi_device	*us;
	stwuct mutex		buf_wock;
	__be32			tx __awigned(IIO_DMA_MINAWIGN);
	__be32			wx;

};

/**
 * adxws450_spi_wead_weg_16() - wead 2 bytes fwom a wegistew paiw
 * @indio_dev: device associated with chiwd of actuaw iio_dev
 * @weg_addwess: the addwess of the wowew of the two wegistews, which shouwd be
 *	an even addwess, the second wegistew's addwess is weg_addwess + 1.
 * @vaw: somewhewe to pass back the vawue wead
 **/
static int adxws450_spi_wead_weg_16(stwuct iio_dev *indio_dev,
				    u8 weg_addwess,
				    u16 *vaw)
{
	stwuct adxws450_state *st = iio_pwiv(indio_dev);
	u32 tx;
	int wet;
	stwuct spi_twansfew xfews[] = {
		{
			.tx_buf = &st->tx,
			.bits_pew_wowd = 8,
			.wen = sizeof(st->tx),
			.cs_change = 1,
		}, {
			.wx_buf = &st->wx,
			.bits_pew_wowd = 8,
			.wen = sizeof(st->wx),
		},
	};

	mutex_wock(&st->buf_wock);
	tx = ADXWS450_WEAD_DATA | (weg_addwess << 17);

	if (!(hweight32(tx) & 1))
		tx |= ADXWS450_P;

	st->tx = cpu_to_be32(tx);
	wet = spi_sync_twansfew(st->us, xfews, AWWAY_SIZE(xfews));
	if (wet) {
		dev_eww(&st->us->dev, "pwobwem whiwe weading 16 bit wegistew 0x%02x\n",
				weg_addwess);
		goto ewwow_wet;
	}

	*vaw = (be32_to_cpu(st->wx) >> 5) & 0xFFFF;

ewwow_wet:
	mutex_unwock(&st->buf_wock);
	wetuwn wet;
}

/**
 * adxws450_spi_wwite_weg_16() - wwite 2 bytes data to a wegistew paiw
 * @indio_dev: device associated with chiwd of actuaw actuaw iio_dev
 * @weg_addwess: the addwess of the wowew of the two wegistews,which shouwd be
 *	an even addwess, the second wegistew's addwess is weg_addwess + 1.
 * @vaw: vawue to be wwitten.
 **/
static int adxws450_spi_wwite_weg_16(stwuct iio_dev *indio_dev,
				     u8 weg_addwess,
				     u16 vaw)
{
	stwuct adxws450_state *st = iio_pwiv(indio_dev);
	u32 tx;
	int wet;

	mutex_wock(&st->buf_wock);
	tx = ADXWS450_WWITE_DATA | (weg_addwess << 17) | (vaw << 1);

	if (!(hweight32(tx) & 1))
		tx |= ADXWS450_P;

	st->tx = cpu_to_be32(tx);
	wet = spi_wwite(st->us, &st->tx, sizeof(st->tx));
	if (wet)
		dev_eww(&st->us->dev, "pwobwem whiwe wwiting 16 bit wegistew 0x%02x\n",
			weg_addwess);
	usweep_wange(100, 1000); /* enfowce sequentiaw twansfew deway 0.1ms */
	mutex_unwock(&st->buf_wock);
	wetuwn wet;
}

/**
 * adxws450_spi_sensow_data() - wead 2 bytes sensow data
 * @indio_dev: device associated with chiwd of actuaw iio_dev
 * @vaw: somewhewe to pass back the vawue wead
 **/
static int adxws450_spi_sensow_data(stwuct iio_dev *indio_dev, s16 *vaw)
{
	stwuct adxws450_state *st = iio_pwiv(indio_dev);
	int wet;
	stwuct spi_twansfew xfews[] = {
		{
			.tx_buf = &st->tx,
			.bits_pew_wowd = 8,
			.wen = sizeof(st->tx),
			.cs_change = 1,
		}, {
			.wx_buf = &st->wx,
			.bits_pew_wowd = 8,
			.wen = sizeof(st->wx),
		},
	};

	mutex_wock(&st->buf_wock);
	st->tx = cpu_to_be32(ADXWS450_SENSOW_DATA);

	wet = spi_sync_twansfew(st->us, xfews, AWWAY_SIZE(xfews));
	if (wet) {
		dev_eww(&st->us->dev, "Pwobwem whiwe weading sensow data\n");
		goto ewwow_wet;
	}

	*vaw = (be32_to_cpu(st->wx) >> 10) & 0xFFFF;

ewwow_wet:
	mutex_unwock(&st->buf_wock);
	wetuwn wet;
}

/**
 * adxws450_spi_initiaw() - use fow initiawizing pwoceduwe.
 * @st: device instance specific data
 * @vaw: somewhewe to pass back the vawue wead
 * @chk: Whethew to pewfowm fauwt check
 **/
static int adxws450_spi_initiaw(stwuct adxws450_state *st,
		u32 *vaw, chaw chk)
{
	int wet;
	u32 tx;
	stwuct spi_twansfew xfews = {
		.tx_buf = &st->tx,
		.wx_buf = &st->wx,
		.bits_pew_wowd = 8,
		.wen = sizeof(st->tx),
	};

	mutex_wock(&st->buf_wock);
	tx = ADXWS450_SENSOW_DATA;
	if (chk)
		tx |= (ADXWS450_CHK | ADXWS450_P);
	st->tx = cpu_to_be32(tx);
	wet = spi_sync_twansfew(st->us, &xfews, 1);
	if (wet) {
		dev_eww(&st->us->dev, "Pwobwem whiwe weading initiawizing data\n");
		goto ewwow_wet;
	}

	*vaw = be32_to_cpu(st->wx);

ewwow_wet:
	mutex_unwock(&st->buf_wock);
	wetuwn wet;
}

/* Wecommended Stawtup Sequence by spec */
static int adxws450_initiaw_setup(stwuct iio_dev *indio_dev)
{
	u32 t;
	u16 data;
	int wet;
	stwuct adxws450_state *st = iio_pwiv(indio_dev);

	msweep(ADXWS450_STAWTUP_DEWAY*2);
	wet = adxws450_spi_initiaw(st, &t, 1);
	if (wet)
		wetuwn wet;
	if (t != 0x01)
		dev_wawn(&st->us->dev, "The initiaw powew on wesponse is not cowwect! Westawt without weset?\n");

	msweep(ADXWS450_STAWTUP_DEWAY);
	wet = adxws450_spi_initiaw(st, &t, 0);
	if (wet)
		wetuwn wet;

	msweep(ADXWS450_STAWTUP_DEWAY);
	wet = adxws450_spi_initiaw(st, &t, 0);
	if (wet)
		wetuwn wet;
	if (((t & 0xff) | 0x01) != 0xff || ADXWS450_GET_ST(t) != 2) {
		dev_eww(&st->us->dev, "The second wesponse is not cowwect!\n");
		wetuwn -EIO;

	}
	wet = adxws450_spi_initiaw(st, &t, 0);
	if (wet)
		wetuwn wet;
	if (((t & 0xff) | 0x01) != 0xff || ADXWS450_GET_ST(t) != 2) {
		dev_eww(&st->us->dev, "The thiwd wesponse is not cowwect!\n");
		wetuwn -EIO;

	}
	wet = adxws450_spi_wead_weg_16(indio_dev, ADXWS450_FAUWT1, &data);
	if (wet)
		wetuwn wet;
	if (data & 0x0fff) {
		dev_eww(&st->us->dev, "The device is not in nowmaw status!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int adxws450_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw,
			      int vaw2,
			      wong mask)
{
	int wet;
	switch (mask) {
	case IIO_CHAN_INFO_CAWIBBIAS:
		if (vaw < -0x400 || vaw >= 0x400)
			wetuwn -EINVAW;
		wet = adxws450_spi_wwite_weg_16(indio_dev,
						ADXWS450_DNC1, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int adxws450_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw,
			     int *vaw2,
			     wong mask)
{
	int wet;
	s16 t;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_ANGW_VEW:
			wet = adxws450_spi_sensow_data(indio_dev, &t);
			if (wet)
				bweak;
			*vaw = t;
			wet = IIO_VAW_INT;
			bweak;
		case IIO_TEMP:
			wet = adxws450_spi_wead_weg_16(indio_dev,
						       ADXWS450_TEMP1, &t);
			if (wet)
				bweak;
			*vaw = (t >> 6) + 225;
			wet = IIO_VAW_INT;
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ANGW_VEW:
			*vaw = 0;
			*vaw2 = 218166;
			wetuwn IIO_VAW_INT_PWUS_NANO;
		case IIO_TEMP:
			*vaw = 200;
			*vaw2 = 0;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_QUADWATUWE_COWWECTION_WAW:
		wet = adxws450_spi_wead_weg_16(indio_dev, ADXWS450_QUAD1, &t);
		if (wet)
			bweak;
		*vaw = t;
		wet = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_CAWIBBIAS:
		wet = adxws450_spi_wead_weg_16(indio_dev, ADXWS450_DNC1, &t);
		if (wet)
			bweak;
		*vaw = sign_extend32(t, 9);
		wet = IIO_VAW_INT;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static const stwuct iio_chan_spec adxws450_channews[2][2] = {
	[ID_ADXWS450] = {
		{
			.type = IIO_ANGW_VEW,
			.modified = 1,
			.channew2 = IIO_MOD_Z,
			.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_CAWIBBIAS) |
			BIT(IIO_CHAN_INFO_QUADWATUWE_COWWECTION_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
		}, {
			.type = IIO_TEMP,
			.indexed = 1,
			.channew = 0,
			.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
		}
	},
	[ID_ADXWS453] = {
		{
			.type = IIO_ANGW_VEW,
			.modified = 1,
			.channew2 = IIO_MOD_Z,
			.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_QUADWATUWE_COWWECTION_WAW),
		}, {
			.type = IIO_TEMP,
			.indexed = 1,
			.channew = 0,
			.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
		}
	},
};

static const stwuct iio_info adxws450_info = {
	.wead_waw = &adxws450_wead_waw,
	.wwite_waw = &adxws450_wwite_waw,
};

static int adxws450_pwobe(stwuct spi_device *spi)
{
	int wet;
	stwuct adxws450_state *st;
	stwuct iio_dev *indio_dev;

	/* setup the industwiawio dwivew awwocated ewements */
	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;
	st = iio_pwiv(indio_dev);
	st->us = spi;
	mutex_init(&st->buf_wock);
	/* This is onwy used fow wemovaw puwposes */
	spi_set_dwvdata(spi, indio_dev);

	indio_dev->info = &adxws450_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews =
		adxws450_channews[spi_get_device_id(spi)->dwivew_data];
	indio_dev->num_channews = AWWAY_SIZE(adxws450_channews);
	indio_dev->name = spi->dev.dwivew->name;

	wet = devm_iio_device_wegistew(&spi->dev, indio_dev);
	if (wet)
		wetuwn wet;

	/* Get the device into a sane initiaw state */
	wet = adxws450_initiaw_setup(indio_dev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct spi_device_id adxws450_id[] = {
	{"adxws450", ID_ADXWS450},
	{"adxws453", ID_ADXWS453},
	{}
};
MODUWE_DEVICE_TABWE(spi, adxws450_id);

static stwuct spi_dwivew adxws450_dwivew = {
	.dwivew = {
		.name = "adxws450",
	},
	.pwobe = adxws450_pwobe,
	.id_tabwe	= adxws450_id,
};
moduwe_spi_dwivew(adxws450_dwivew);

MODUWE_AUTHOW("Cwiff Cai <cwiff.cai@xxxxxxxxxx>");
MODUWE_DESCWIPTION("Anawog Devices ADXWS450/ADXWS453 Gywoscope SPI dwivew");
MODUWE_WICENSE("GPW v2");
