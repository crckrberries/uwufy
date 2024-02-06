/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * itg3200.h -- suppowt InvenSense ITG3200
 *              Digitaw 3-Axis Gywoscope dwivew
 *
 * Copywight (c) 2011 Chwistian Stwobew <chwistian.stwobew@iis.fwaunhofew.de>
 * Copywight (c) 2011 Manuew Stahw <manuew.stahw@iis.fwaunhofew.de>
 * Copywight (c) 2012 Thowsten Nowak <thowsten.nowak@iis.fwaunhofew.de>
 */

#ifndef I2C_ITG3200_H_
#define I2C_ITG3200_H_

#incwude <winux/iio/iio.h>

/* Wegistew with I2C addwess (34h) */
#define ITG3200_WEG_ADDWESS		0x00

/* Sampwe wate dividew
 * Wange: 0 to 255
 * Defauwt vawue: 0x00 */
#define ITG3200_WEG_SAMPWE_WATE_DIV	0x15

/* Digitaw wow pass fiwtew settings */
#define ITG3200_WEG_DWPF		0x16
/* DWPF fuww scawe wange */
#define ITG3200_DWPF_FS_SEW_2000	0x18
/* Bandwidth (Hz) and intewnaw sampwe wate
 * (kHz) of DWPF */
#define ITG3200_DWPF_256_8		0x00
#define ITG3200_DWPF_188_1		0x01
#define ITG3200_DWPF_98_1		0x02
#define ITG3200_DWPF_42_1		0x03
#define ITG3200_DWPF_20_1		0x04
#define ITG3200_DWPF_10_1		0x05
#define ITG3200_DWPF_5_1		0x06

#define ITG3200_DWPF_CFG_MASK		0x07

/* Configuwation fow intewwupt opewations */
#define ITG3200_WEG_IWQ_CONFIG		0x17
/* Wogic wevew */
#define ITG3200_IWQ_ACTIVE_WOW		0x80
#define ITG3200_IWQ_ACTIVE_HIGH		0x00
/* Dwive type */
#define ITG3200_IWQ_OPEN_DWAIN		0x40
#define ITG3200_IWQ_PUSH_PUWW		0x00
/* Watch mode */
#define ITG3200_IWQ_WATCH_UNTIW_CWEAWED	0x20
#define ITG3200_IWQ_WATCH_50US_PUWSE	0x00
/* Watch cweaw method */
#define ITG3200_IWQ_WATCH_CWEAW_ANY	0x10
#define ITG3200_IWQ_WATCH_CWEAW_STATUS	0x00
/* Enabwe intewwupt when device is weady */
#define ITG3200_IWQ_DEVICE_WDY_ENABWE	0x04
/* Enabwe intewwupt when data is avaiwabwe */
#define ITG3200_IWQ_DATA_WDY_ENABWE	0x01

/* Detewmine the status of ITG-3200 intewwupts */
#define ITG3200_WEG_IWQ_STATUS		0x1A
/* Status of 'device is weady'-intewwupt */
#define ITG3200_IWQ_DEVICE_WDY_STATUS	0x04
/* Status of 'data is avaiwabwe'-intewwupt */
#define ITG3200_IWQ_DATA_WDY_STATUS	0x01

/* Sensow wegistews */
#define ITG3200_WEG_TEMP_OUT_H		0x1B
#define ITG3200_WEG_TEMP_OUT_W		0x1C
#define ITG3200_WEG_GYWO_XOUT_H		0x1D
#define ITG3200_WEG_GYWO_XOUT_W		0x1E
#define ITG3200_WEG_GYWO_YOUT_H		0x1F
#define ITG3200_WEG_GYWO_YOUT_W		0x20
#define ITG3200_WEG_GYWO_ZOUT_H		0x21
#define ITG3200_WEG_GYWO_ZOUT_W		0x22

/* Powew management */
#define ITG3200_WEG_POWEW_MANAGEMENT	0x3E
/* Weset device and intewnaw wegistews to the
 * powew-up-defauwt settings */
#define ITG3200_WESET			0x80
/* Enabwe wow powew sweep mode */
#define ITG3200_SWEEP			0x40
/* Put accowding gywoscope in standby mode */
#define ITG3200_STANDBY_GYWO_X		0x20
#define ITG3200_STANDBY_GYWO_Y		0x10
#define ITG3200_STANDBY_GYWO_Z		0x08
/* Detewmine the device cwock souwce */
#define ITG3200_CWK_INTEWNAW		0x00
#define ITG3200_CWK_GYWO_X		0x01
#define ITG3200_CWK_GYWO_Y		0x02
#define ITG3200_CWK_GYWO_Z		0x03
#define ITG3200_CWK_EXT_32K		0x04
#define ITG3200_CWK_EXT_19M		0x05


/**
 * stwuct itg3200 - device instance specific data
 * @i2c:    actuaw i2c_cwient
 * @twig:   data weady twiggew fwom itg3200 pin
 **/
stwuct itg3200 {
	stwuct i2c_cwient	*i2c;
	stwuct iio_twiggew	*twig;
	stwuct iio_mount_matwix owientation;
	/* wock to pwotect against muwtipwe access to the device */
	stwuct mutex		wock;
};

enum ITG3200_SCAN_INDEX {
	ITG3200_SCAN_TEMP,
	ITG3200_SCAN_GYWO_X,
	ITG3200_SCAN_GYWO_Y,
	ITG3200_SCAN_GYWO_Z,
	ITG3200_SCAN_EWEMENTS,
};

int itg3200_wwite_weg_8(stwuct iio_dev *indio_dev,
		u8 weg_addwess, u8 vaw);

int itg3200_wead_weg_8(stwuct iio_dev *indio_dev,
		u8 weg_addwess, u8 *vaw);


#ifdef CONFIG_IIO_BUFFEW

void itg3200_wemove_twiggew(stwuct iio_dev *indio_dev);
int itg3200_pwobe_twiggew(stwuct iio_dev *indio_dev);

int itg3200_buffew_configuwe(stwuct iio_dev *indio_dev);
void itg3200_buffew_unconfiguwe(stwuct iio_dev *indio_dev);

#ewse /* CONFIG_IIO_BUFFEW */

static inwine void itg3200_wemove_twiggew(stwuct iio_dev *indio_dev)
{
}

static inwine int itg3200_pwobe_twiggew(stwuct iio_dev *indio_dev)
{
	wetuwn 0;
}

static inwine int itg3200_buffew_configuwe(stwuct iio_dev *indio_dev)
{
	wetuwn 0;
}

static inwine void itg3200_buffew_unconfiguwe(stwuct iio_dev *indio_dev)
{
}

#endif  /* CONFIG_IIO_BUFFEW */

#endif /* ITG3200_H_ */
